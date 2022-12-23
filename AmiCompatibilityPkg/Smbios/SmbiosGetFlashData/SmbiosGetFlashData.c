//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SmbiosGetFlashData.c
    This file provides AMI Smbios GetFlashData Protocols

**/

#include <Token.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmiRomLayoutLib.h>
#include <Protocol/SmbiosGetFlashDataProtocol.h>
#include <AmiRomLayout.h>

#pragma pack(1)

#define DMIEDIT_WRITE_ONCE      0x01
#define DMIEDIT_DELETE_STRUC    0x02
#define DMIEDIT_ADD_STRUC       0x04
#define DMIEDIT_EXTENDED_HDR    0x80

/**
    DMI data record
**/
typedef struct {
    UINT8   Type;
    UINT8   Offset;     // Structure field offset, or string number for Type 11 and 12
    UINT8   Reserved;   // Size of string including \0 or UUID (16)
    UINT8   Flags;      // Bit0 = Write Once
                        // Bit1 = Delete Structure
                        // Bit2 = Add structure
                        // Bit7 = Extended Header
    UINT8   HdrLength;
    UINT16  Size;
    UINT16  Handle;
} TABLE_INFO;

/**
    DMI Data Table Header
**/
typedef struct {
    UINT32  Signature;
    UINT32  Size;
} ROM_INFO;

#pragma pack()

#define SMBIOS_STATIC_TABLE_DATA_FFS_GUID \
                {0xFD44820B, 0xF1AB, 0x41C0, {0xAE, 0x4E, 0x0C, 0x55, 0x55, 0x6E, 0xB9, 0xBD}};

ROM_INFO    gRomInfo;
VOID        *gRomData;

/**
    Get Flash Data location and size.

    @param This     Pointer to EFI_SMBIOS_FLASH_DATA_PROTOCOL protocol
    @param Location Pointer to hold the location of flash data
    @param Size     Pointer to flash data size

    @return EFI_STATUS

**/
EFI_STATUS
GetFlashTableInfo (
    IN      EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
    IN OUT  VOID                            **Location,
    IN OUT  UINT32                          *Size
)
{
    *Location = gRomData;
    *Size = gRomInfo.Size;
    return EFI_SUCCESS;
}

/**
    Get Flash Data Field

    @param This     Pointer to EFI_SMBIOS_FLASH_DATA_PROTOCOL protocol
    @param Table
    @param Offset
    @param Field

    @return EFI_STATUS

**/
EFI_STATUS
GetField (
    IN EFI_SMBIOS_FLASH_DATA_PROTOCOL  *This,
    IN UINT8                           Table,
    IN UINT8                           Offset,
    IN VOID                            **Field
)
{
    TABLE_INFO *Ptr = gRomData;

    while ( Ptr->Offset != 0xFF && (Ptr->Type != Table || Ptr->Offset != Offset)) {
        Ptr = (TABLE_INFO*)((UINT8*)(Ptr+1) + Ptr->Size);
    }

    if (Ptr->Offset != 0xFF) {
        *Field = Ptr + 1;
        return EFI_SUCCESS;
    }

    *Field = 0;
    return EFI_NOT_FOUND;
}


EFI_SMBIOS_FLASH_DATA_PROTOCOL gSmbiosFlashDataProtocol = {
    GetFlashTableInfo,
    GetField
};

/**
    Find the RAW section

    @param Section
    @param End

    @return Pointer to Raw Section if found

**/
VOID*
FindRawSection (
    IN VOID *Section,
    IN VOID *End
)
{
    EFI_COMMON_SECTION_HEADER *Ptr = Section;
    
    while ((UINTN)Ptr < (UINTN)End) {   //Use signed because 0 = 0x100000000
        if (Ptr->Type == EFI_SECTION_RAW) {
            return (Ptr + 1);
        }

        if (ALIGN_VALUE(SECTION_SIZE(Ptr), 4) == 0x0) {
            return 0;               // Section size = 0 indicates data is corrupted
        }

        Ptr = (EFI_COMMON_SECTION_HEADER*)((UINT8*)Ptr + ALIGN_VALUE(SECTION_SIZE(Ptr), 4));
    }
    return 0;
}

/**
    Find file in the FV with the input GUID

    @param Guid
    @param File
    @param EndOfFiles

    @return Pointer to File if found

**/
VOID*
FindFile (
    IN EFI_GUID *Guid,
    IN VOID     *File,
    IN VOID     *EndOfFiles
)
{
    EFI_FFS_FILE_HEADER *Ptr = File;
    VOID                *StartPtr = File;
    UINT32              FfsSize;
    UINT32              HeaderSize;
    VOID                *FilePtr;

    while ((UINTN)Ptr < (UINTN)EndOfFiles) {
        
        if (IS_FFS_FILE2(Ptr)) {
            HeaderSize = sizeof (EFI_FFS_FILE_HEADER2);
            FfsSize    = FFS_FILE2_SIZE(Ptr);
            if(FfsSize == MAX_UINT32) {
                // Once all FFS processed, remaining free space in FV will be filled with 0xFF.
                // If size is MAX_UINT32, then return
                break;
            }
        } else {
            HeaderSize = sizeof (EFI_FFS_FILE_HEADER);
            FfsSize    = FFS_FILE_SIZE(Ptr);
        }
        
        FilePtr = (UINT8*)Ptr + HeaderSize;
        
        if (CompareGuid (Guid, &Ptr->Name)) {
            // Found File.
            return FindRawSection (
                                FilePtr,
                                (UINT8*)FilePtr + FfsSize - HeaderSize - 1 );
        }

        Ptr = (EFI_FFS_FILE_HEADER*)((UINT8*)Ptr + ALIGN_VALUE(FfsSize, 8));
        if ((UINTN)Ptr < (UINTN)StartPtr) {
            // In 32 bit build, there is a chance of pointer overflow
            // If overflow occurs, break the loop to avoid deadloop
            break;
        }
    }

    return NULL;
}

/**
    Reads SMBIOS Table from FV

    @param None

    @return EFI_STATUS

**/
EFI_STATUS
GetTableLocation()
{
    AMI_ROM_AREA                      *RomLayout;
    EFI_FIRMWARE_VOLUME_HEADER        *FvHeader;
    EFI_FIRMWARE_VOLUME_EXT_HEADER    *FvExtHeader;
    VOID                              *TablePtr;
    VOID                              *FirstFfs;
    EFI_GUID                          SmbiosStaticTableGuid = SMBIOS_STATIC_TABLE_DATA_FFS_GUID;
    
    for (RomLayout = AmiGetFirstRomArea(); 
         RomLayout != NULL; 
         RomLayout = AmiGetNextRomArea(RomLayout)) {
        
        if (RomLayout->Type != AmiRomAreaTypeFv) 
		    continue;
			
        FvHeader = (EFI_FIRMWARE_VOLUME_HEADER*)RomLayout->Address;
        if (FvHeader->ExtHeaderOffset != 0) {
            // Searching for files starts on an 8 byte aligned boundary 
            // after the end of the Extended Header if it exists.
            FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER*)((UINT8*)FvHeader + FvHeader->ExtHeaderOffset);
            FirstFfs    = (EFI_FFS_FILE_HEADER *)((UINT8*)FvExtHeader + FvExtHeader->ExtHeaderSize);
        } else {
            FirstFfs = (EFI_FFS_FILE_HEADER *)((UINT8 *)FvHeader + FvHeader->HeaderLength);
        }
        
        FirstFfs = (EFI_FFS_FILE_HEADER*)ALIGN_POINTER (FirstFfs, 8);
        
        TablePtr = FindFile (
                        &SmbiosStaticTableGuid, 
                        FirstFfs, 
                        (VOID*)((UINT8*)FvHeader + FvHeader->FvLength - 1) );
        if (TablePtr == NULL) {
            continue;
        }
        
        // Store top memory address directly. Because, SmbiosDmiEdit module part will use this address
        // to update SMBIOS table using Flash protocol
        gRomInfo = *(ROM_INFO*)TablePtr;
        gRomData = (ROM_INFO*)TablePtr + 1;
        
        return EFI_SUCCESS;
    }
    
    return EFI_NOT_FOUND;
}

/**
    Driver entry point for SmbiosGetFlashData

    @param ImageHandle
    @param SystemTable

    @return EFI_STATUS
**/
EFI_STATUS
EFIAPI
SmbiosGetFlashDataInstall (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS  Status;

    Status = GetTableLocation();
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return gBS->InstallMultipleProtocolInterfaces (
                                        &ImageHandle,
                                        &gAmiSmbiosFlashDataProtocolGuid,
                                        &gSmbiosFlashDataProtocol,
                                        NULL );
}
