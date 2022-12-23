//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  PcdRecoveryLib library class
**/
#include <PiDxe.h>
#include <Guid/PcdDataBaseHobGuid.h>
#include <Guid/PcdDataBaseSignatureGuid.h>
#include <Guid/HobList.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/DevicePath.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Fid.h>
#include <AmiHobs.h>
#include <Token.h>
#include "PcdRecovery.h"
#include <AmiDxeLib.h>

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

extern VOID *gHobList; // global variable from DXE Core

AMI_PCD_RECOVERY_HOB    *gAmiPcdRecoveryHob = NULL;

/**
  This function returns NEW image PeiPcd database somewhere in NEW DXE FV and data size.

  @param  Buffer      Pointer to the Pointer where to store PeiPcd database.
  @param  PcdSize     Pointer where to the size of PeiPcd database.

**/
EFI_STATUS
LoadPeiPcdSectionDefault (
  VOID      **Buffer,
  UINTN     *PcdSize
  )
{
    EFI_GUID                      EfiPeiPcdPeim = {0x9B3ADA4F, 0xAE56, 0x4c24, {0x8D, 0xEA, 0xF0, 0x3B, 0x75, 0x58, 0xAE, 0x50}};
    UINTN                         FvCount,i;
    EFI_HANDLE                    *FvHandle;
    EFI_STATUS                    Status;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
    UINT32                        AuthStatus;

    Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &FvCount, &FvHandle);
    if (EFI_ERROR(Status))
        return Status;

    Status = EFI_NOT_FOUND;
    for(i=0; i<FvCount; i++)
    {

        Status = gBS->HandleProtocol(FvHandle[i], &gEfiFirmwareVolume2ProtocolGuid, (VOID**)&Fv);
        if (EFI_ERROR(Status))
            continue;

        Status = Fv->ReadSection(
            Fv, 
            &EfiPeiPcdPeim, 
            EFI_SECTION_RAW,
            0,
            Buffer,
            PcdSize,
            &AuthStatus
        );
        if (!EFI_ERROR(Status))
        {
            DEBUG((DEBUG_VERBOSE,"[PcdRecoveryLib] Found PCD=%r, size=0x%x, dword[0]=%x, FvCount:%d\n", Status, *PcdSize, *(UINT32*)*Buffer, FvCount));
            break;
        }
    }

    gBS->FreePool(FvHandle);

    return Status;
}

/**
  This function returns NEW image PeiPcd database in known FV and data size.

  @param  Buffer      Pointer to the Pointer where to store PeiPcd database.
  @param  PcdSize     Pointer where to the size of PeiPcd database.

**/
EFI_STATUS
LoadPeiPcdSection (
  VOID      **Buffer,
  UINTN     *PcdSize
  )
{
    EFI_GUID                      EfiPeiPcdPeim = {0x9B3ADA4F, 0xAE56, 0x4c24, {0x8D, 0xEA, 0xF0, 0x3B, 0x75, 0x58, 0xAE, 0x50}};
    EFI_STATUS                    Status;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
    UINT32                        AuthStatus;
    
    EFI_HANDLE                    Handle;
    EFI_DEVICE_PATH_PROTOCOL      *Dp;
    struct {
      MEDIA_FW_VOL_DEVICE_PATH            FwVolDp;
      EFI_DEVICE_PATH_PROTOCOL            End;
    } LocatedDp = {
        {{MEDIA_DEVICE_PATH, MEDIA_PIWG_FW_VOL_DP, {sizeof(MEDIA_FW_VOL_DEVICE_PATH), 0}}, PCD_RECOVERY_FV_GUID},
        {END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, {sizeof(EFI_DEVICE_PATH_PROTOCOL), 0}}
    };

    Dp = &(LocatedDp.FwVolDp.Header);
    Status = gBS->LocateDevicePath(&gEfiFirmwareVolume2ProtocolGuid, &Dp, &Handle);
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_VERBOSE,"[PcdRecoveryLib] Locate FV failed, going on the default searching."));
        return LoadPeiPcdSectionDefault(Buffer, PcdSize);
    }

    Status = gBS->HandleProtocol (Handle, &gEfiFirmwareVolume2ProtocolGuid, (VOID **)&Fv);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = Fv->ReadSection(
        Fv, 
        &EfiPeiPcdPeim, 
        EFI_SECTION_RAW,
        0,
        Buffer,
        PcdSize,
        &AuthStatus
    );

    return Status;
}

/**
  Invalidate original PcdDataBase hobs.
**/
VOID InvalidateOldPeiPcd ()
{
    EFI_HOB_GUID_TYPE   *GuidHob;

    while ( (GuidHob = GetFirstGuidHob (&gPcdDataBaseHobGuid)) != NULL )
    {
        GuidHob->Header.HobType=EFI_HOB_TYPE_UNUSED;   // make it unused
    }
    
}

/**
  Add a new HOB to the HOB List.

  @param   Length                Length of the new HOB (no header) to allocate.
  @param   Hob                   Pointer to the new HOB.

  @retval  EFI_SUCCESS           Success to create hob.
  @retval  EFI_INVALID_PARAMETER if Hob is NULL

**/
EFI_STATUS
EFIAPI
CreateNewPeiPcdHob (
  IN UINT16            Length,
  IN OUT VOID          **Hob

  )
{
    EFI_HOB_GENERIC_HEADER               *HobEnd;
    EFI_PEI_HOB_POINTERS                 HobList;

    HobList.Raw = *Hob;

    //
    // Check Length to avoid data overflow. 
    //
    if (0x10000 - Length <= 0x7) {
        return EFI_INVALID_PARAMETER;
    }
    Length     = (UINT16)((Length + 0x7) & (~0x7));

    // scan for the last hob
    while (1)
    {
        if (END_OF_HOB_LIST (HobList))
            break;
        HobList.Raw = GET_NEXT_HOB (HobList);
    };

    // Append the new hob
    HobList.Header->HobType   = EFI_HOB_TYPE_GUID_EXTENSION;
    HobList.Header->HobLength = Length;
    HobList.Header->Reserved  = 0;
    HobEnd = (EFI_HOB_GENERIC_HEADER*) ((UINTN) HobList.Raw + Length);

    *Hob = HobList.Raw; // update output

    // set the last hob
    HobEnd->HobType   = EFI_HOB_TYPE_END_OF_HOB_LIST;
    HobEnd->HobLength = (UINT16) sizeof (EFI_HOB_GENERIC_HEADER);
    HobEnd->Reserved  = 0;
    HobEnd++;

    return EFI_SUCCESS;   
}

/**
  Modify the HOB List Table from the EFI System Table.

  @param  NewTable    Pointer to the configuration table for the entry to update.

  @retval EFI_SUCCESS               HOB List Table updated.
  @retval EFI_INVALID_PARAMETER     Input NewTable is NULL.
  @retval EFI_NOT_FOUND             No matching gEfiHobListGuid were found.

**/
EFI_STATUS
EFIAPI
ChangeHobListSystemConfigurationTable (
  VOID *NewTable
)
{
    UINTN             Index;

    if (NewTable == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Search all the table for an entry that matches gEfiHobListGuid
    //
    for (Index = 0; Index < gST->NumberOfTableEntries; Index++)
    {
        if (CompareGuid (&gEfiHobListGuid, &(gST->ConfigurationTable[Index].VendorGuid)))
        {
            //
            // A match was found, so Modify the table entry and return.
            //
            gST->ConfigurationTable[Index].VendorTable = NewTable;
            return EFI_SUCCESS;
        }
    }

    //
    // No matching gEfiHobListGuid were found.
    //
    return EFI_NOT_FOUND;
}

/**
  This function returns current FID descriptor

  @param  Fid         Pointer where to store FID descriptor

  @retval EFI_SUCCESS Layout returned successfully
  @retval other       error occurred during execution

**/
EFI_STATUS
PcdGetFidFromFv(
    OUT VOID *Fid
)
{
    static EFI_GUID               FidFileName = FID_FFS_FILE_NAME_GUID;
    EFI_STATUS                    Status;
    EFI_HANDLE                    *FvHandle;
    UINTN                         FvCount;
    UINTN                         i;
    UINTN                         BufferSize;
    VOID                          *Buffer;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
    UINT32                        AuthStatus;

    Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiFirmwareVolume2ProtocolGuid, NULL, &FvCount, &FvHandle);
    if (EFI_ERROR(Status))
        return Status;

    for(i = 0; i < FvCount; i++)
    {
        Status = gBS->HandleProtocol(FvHandle[i], &gEfiFirmwareVolume2ProtocolGuid, (VOID**)&Fv);
        if (EFI_ERROR(Status))
            continue;

        Buffer = 0;
        BufferSize = 0;
        Status = Fv->ReadSection(Fv, &FidFileName, EFI_SECTION_FREEFORM_SUBTYPE_GUID, 0, &Buffer, &BufferSize, &AuthStatus);
        if (!EFI_ERROR(Status))
        {
            DEBUG((DEBUG_INFO ,"[PcdRecoveryLib] extracted section with guid %g\n", (EFI_GUID *)Buffer));
            Buffer = (UINT8 *)Buffer + sizeof(EFI_GUID);
            CopyMem(Fid, Buffer, sizeof(FW_VERSION));
            Buffer = (UINT8 *)Buffer - sizeof(EFI_GUID);
            gBS->FreePool(Buffer);
            return EFI_SUCCESS;
        }
    }

    gBS->FreePool(FvHandle);
    return EFI_NOT_FOUND;
}

/**
  This function returns FID descriptor stored in provided buffer

  @param  Fid     Pointer where to store FID descriptor
  @param  Buffer  Pointer to the buffer to be searched

  @retval EFI_SUCCESS       Layout returned successfully
  @retval EFI_NOT_FOUND     There is no FID descriptor in buffer

**/
EFI_STATUS
PcdGetFidFromBuffer(
  IN  VOID *Buffer,
  OUT VOID *Fid
)
{
    static EFI_GUID    FidSectionGuid = FID_FFS_FILE_SECTION_GUID;
    UINT32             Signature;
    UINT32             *SearchPointer;

    SearchPointer = (UINT32 *)((UINT8 *)Buffer - sizeof(EFI_GUID) + FLASH_SIZE);
    Signature = FidSectionGuid.Data1;

    do {
        if(*SearchPointer == Signature)
        {
            if(CompareGuid(&FidSectionGuid, (EFI_GUID *)SearchPointer)) {
                SearchPointer = (UINT32 *)((UINT8 *)SearchPointer + sizeof(EFI_GUID));
                CopyMem(Fid, SearchPointer, sizeof(FW_VERSION));
                return EFI_SUCCESS;
            }
        }
    } while(SearchPointer-- >= (UINT32 *)Buffer);

    return EFI_NOT_FOUND;
}

/**
  This function returns firmware version from FID descriptor

  @param Image   Pointer to the recovery image (or NULL if current
                 image to be used)

  @return Firmware version

**/
UINT32
PcdGetVersionFromFid(
  IN  VOID *Image OPTIONAL
)
{
    FW_VERSION Fid;
    EFI_STATUS Status;
    CHAR16     ProjectVersion[5];

    if(Image == NULL)
        Status = PcdGetFidFromFv(&Fid);
    else
        Status = PcdGetFidFromBuffer(Image, &Fid);

    if(EFI_ERROR(Status))
        return 0;

    ProjectVersion[0] = Fid.ProjectMajorVersion[0];
    ProjectVersion[1] = Fid.ProjectMajorVersion[1];
    ProjectVersion[2] = Fid.ProjectMinorVersion[0];
    ProjectVersion[3] = Fid.ProjectMinorVersion[1];
    ProjectVersion[4] = 0;

    return (UINT32)StrDecimalToUintn(ProjectVersion);
}

/**
  This function returns firmware version from FID descriptor
  Get FID from AMI Pcd Recovery HOB.

  @return Firmware version

**/
UINT32
PcdGetVersionFromAmiPcdRecoveryHob(VOID)
{
    FW_VERSION           Fid;
    CHAR16               ProjectVersion[5];

    if (gAmiPcdRecoveryHob == NULL) {
        DEBUG ((DEBUG_ERROR, "[PcdRecoveryLib] Get gAmiPcdRecoveryHob fail\n"));
        return 0;
    }

    CopyMem(&Fid, &gAmiPcdRecoveryHob->FwVersionData, sizeof(FW_VERSION));

    ProjectVersion[0] = Fid.ProjectMajorVersion[0];
    ProjectVersion[1] = Fid.ProjectMajorVersion[1];
    ProjectVersion[2] = Fid.ProjectMinorVersion[0];
    ProjectVersion[3] = Fid.ProjectMinorVersion[1];
    ProjectVersion[4] = 0;

    return (UINT32)StrDecimalToUintn(ProjectVersion);
}

/**
  This function checks two firmware versions from FID descriptor.
  One is current FID descriptor. Another is from recovery image.

  @retval TRUE  Two firmware versions are the same.
  @retval FALSE Two firmware versions are different.

**/
BOOLEAN
IsEqualFwRevision(VOID)
{
    RECOVERY_IMAGE_HOB  *RecoveryHob = NULL;
    UINT32              ProjectVersion = 0;
    UINT32              NewProjectVersion = 0;

    //We do not get FID from FV since old FV HOB would be removed by RomlayoutPei during Recovery.
    //So, we record old FID on HOB in PcdRecoveryPei before old FV HOB is removed.
    ProjectVersion = PcdGetVersionFromAmiPcdRecoveryHob();
    DEBUG((DEBUG_VERBOSE,"[PcdRecoveryLib] ProjectVersion=%x\n", ProjectVersion));

    RecoveryHob = GetFirstGuidHob(&gAmiRecoveryImageHobGuid);
    if(RecoveryHob != NULL)
    {
        NewProjectVersion = PcdGetVersionFromFid((VOID *)(UINTN)RecoveryHob->Address); //Get Fid From recovery image
        DEBUG((DEBUG_VERBOSE,"[PcdRecoveryLib] NewProjectVersion=%x\n", NewProjectVersion));
    }

    if(ProjectVersion == NewProjectVersion)
    {
        return TRUE;
    }

    return FALSE;
}
VOID 
EFIAPI
RestoreSkuId (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    //
    //  The old hob has cleared.
    //
    gAmiPcdRecoveryHob = GetFirstGuidHob(&gAmiPcdRecoveryHobGuid);
    if (gAmiPcdRecoveryHob != NULL)
    {
        LibPcdSetSku(gAmiPcdRecoveryHob->SkuId);
	}

    gBS->CloseEvent(Event);
}
/**
  Replace the original PCD by new PCD in gPcdDataBaseHobGuid HOB during recovery mode.

  @param ImageHandle Pointer to the handle that corresponds to this image
  @param SystemTable Pointer to the EFI_SYSTEM_TABLE

  @retval EFI_SUCCESS This function executes correctly
**/
EFI_STATUS
PcdRecoveryInit (
  IN     EFI_HANDLE             ImageHandle,
  IN     EFI_SYSTEM_TABLE       *SystemTable
  )
{
    VOID                        *PcdPeiBuffer = NULL;  // NULL so that the buffer will be allocated by ReadSection
    UINTN                       PcdSize = 0;
    EFI_STATUS                  Status;
    EFI_BOOT_MODE               BootMode;
    EFI_HOB_GUID_TYPE           *NewHob;
    EFI_PEI_HOB_POINTERS        Hob;
    VOID                        *HobStart;
    UINTN                       OrgHobListLength = 0;
    UINTN                       NewHobListLength = 0;
    UINT8                       *NewHobList;
    PEI_PCD_DATABASE            *BackupPeiDatabase;
    UINTN                       BackupPeiDataLength = 0;
    UINT8                       IsRecovery = 0;
    EFI_EVENT                   Event = NULL;
    VOID                        *Registration = NULL;

    // Determine boot mode
    BootMode = GetBootModeHob();

    gAmiPcdRecoveryHob = GetFirstGuidHob(&gAmiPcdRecoveryHobGuid);

    if (gAmiPcdRecoveryHob != NULL)
    {
        IsRecovery = gAmiPcdRecoveryHob->IsRecovery;
    }
    else
    {
        //For old image PEI does not have PcdRecoveryPei yet.
        if (BootMode == BOOT_IN_RECOVERY_MODE)
        {
            IsRecovery = 1;
        }
    }

    if (!((IsRecovery == 1)||(BootMode == BOOT_ON_FLASH_UPDATE && PcdGetBool(PcdUseNewImageOnFlashUpdate))))
    {
        return EFI_SUCCESS;
    }

#if PCD_RECOVERY_SKIP_FW_VERSION_CHECK == 0
    // Skip PcdRecovery if Fw version of current BIOS is the same as Fw version of recovery image.
    if (IsEqualFwRevision() == TRUE)
    {
        return EFI_SUCCESS;
    }
#endif

    // Get new image PeiPcd database
    Status = LoadPeiPcdSection (&PcdPeiBuffer, &PcdSize);
    if (EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_ERROR, "Not found new image PeiPcd database: %r\n", Status));
        return Status;
    }

    BackupPeiDatabase = (PEI_PCD_DATABASE *) PcdPeiBuffer;

    //Total PeiPcd Data Length
    BackupPeiDataLength = BackupPeiDatabase->Length + BackupPeiDatabase->UninitDataBaseSize;

    HobStart = GetHobList ();
    DEBUG((DEBUG_VERBOSE ,"[PcdRecoveryLib] Original HobStart =0x%X\n", HobStart ));

    Hob.Raw = (UINT8 *) HobStart;

    // calculate length of hobs
    while (1)
    {
        OrgHobListLength += GET_HOB_LENGTH (Hob);
        if (END_OF_HOB_LIST (Hob))
            break;
        Hob.Raw = GET_NEXT_HOB (Hob);
    };
    
    NewHobListLength = OrgHobListLength + BackupPeiDataLength + sizeof (EFI_HOB_GUID_TYPE);

    // All allocations are eight-byte aligned.
    Status = gBS->AllocatePool (EfiBootServicesData, NewHobListLength, (VOID**)&NewHobList);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    gBS->SetMem ( NewHobList, NewHobListLength, 0 ); // initial zero

    // Make original PcdDataBase hobs invalid
    InvalidateOldPeiPcd ();

    gBS->CopyMem ( NewHobList, HobStart, OrgHobListLength ); // copy to new location

    // Update HobList new start address
    Status = ChangeHobListSystemConfigurationTable ( NewHobList );
    if (EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_ERROR, "Change HobList SystemConfigurationTable fail: %r\n", Status));
    }

    gHobList = NewHobList; // update variable inside HobLib

    NewHob = (EFI_HOB_GUID_TYPE*) NewHobList;
    DEBUG((DEBUG_VERBOSE,"[PcdRecoveryLib] NewHob=%x\n", NewHob));
    
    CreateNewPeiPcdHob ((UINT16)(BackupPeiDataLength + sizeof (EFI_HOB_GUID_TYPE) ), (VOID**)&NewHob);
    // fill with PCD PEI data base
    gBS->CopyMem (&NewHob->Name, &gPcdDataBaseHobGuid, sizeof(EFI_GUID));
    gBS->CopyMem (NewHob+1, PcdPeiBuffer, BackupPeiDatabase->Length);

    gBS->FreePool(PcdPeiBuffer);    // free buffer allocated by LoadPeiPcdSection() -> ReadSection
    gBS->SetMem ( HobStart, OrgHobListLength, 0 ); //clear original hob
    
    RegisterProtocolCallback( 
           &gPcdProtocolGuid, 
           RestoreSkuId, 
           NULL, 
           &Event, 
           &Registration );

    return EFI_SUCCESS;
}
