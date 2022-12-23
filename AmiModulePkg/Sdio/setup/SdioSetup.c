//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SdioSetup.c
    Sdio driver setup related functions implementation.

**/

#include <SdioElink.h>
#include <Library/HiiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/DevicePathLib.h>
#include <Protocol/SdioBus.h>
#include <Protocol/AmiSdEmmcControllerInitProtocol.h>


//----------------------------------------------------------------------

#define ADVANCED_FORM_SET_CLASS   0x01
#define STRING_SIZE     0x100      

typedef struct{
    UINT16  ManufactureId;
    UINT16  ManufactureCode;
    CHAR8   VendorString[30];
}SDIO_MANUFACTURE_DETAILS;

//
// SD I/O device Vendor List.
//
SDIO_MANUFACTURE_DETAILS ManuFactureDetails[] = {
    SDIO_MANUFACTURE_DEVICE_LIST
    {0xFFFF, 0xFFFF, "Unknown Vendor"}
};
#pragma pack(1)
typedef struct{
    UINT8  SdEmul;
    UINT64 SdMmcAddress;
}SDMMC_EMULATION;

typedef struct {
    UINT8           SdioMode;
    UINT8           SdioMassDevNum;
    UINT8           IoDeviceType[8];
    SDMMC_EMULATION SdioEmu[8];
} SDIO_DEV_CONFIGURATION;
#pragma pack()


/**
    This function is eLink'ed with the chain executed right before
    the Setup.

**/

VOID InitSdioStrings(
        EFI_HII_HANDLE HiiHandle,
        UINT16 Class)
{
    UINT16  SdioDev[8] = {
        STRING_TOKEN(STR_SDIO_DEVICE1),
        STRING_TOKEN(STR_SDIO_DEVICE2),
        STRING_TOKEN(STR_SDIO_DEVICE3),
        STRING_TOKEN(STR_SDIO_DEVICE4),
        STRING_TOKEN(STR_SDIO_DEVICE5),
        STRING_TOKEN(STR_SDIO_DEVICE6),
        STRING_TOKEN(STR_SDIO_DEVICE7),
        STRING_TOKEN(STR_SDIO_DEVICE8)
    };
    
    UINT16  IoDevName[8] = {
        STRING_TOKEN(STR_IO_DEVICE1_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE2_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE3_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE4_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE5_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE6_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE7_DETAILS),
        STRING_TOKEN(STR_IO_DEVICE8_DETAILS)
    };

    UINT16  SdioDevLocation[8] = {
        STRING_TOKEN(STR_SDIO_DEVICE1_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE2_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE3_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE4_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE5_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE6_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE7_LOCATION),
        STRING_TOKEN(STR_SDIO_DEVICE8_LOCATION)
    };

    EFI_STATUS                            Status;
    UINTN                                 HandleCount;
    EFI_HANDLE                            *HandleBuffer;
    AMI_SDIO_BUS_PROTOCOL                 *SdioBusInterface;
    LIST_ENTRY                            *DLink = NULL;
    SDIO_DEVICE_INTERFACE                 *SdioDevInterface = NULL;
    UINT8                                 SdioDevIndex = 0;
    CHAR16                                SName[55];
    CHAR16                                VendorName[30];
    CHAR16                                CardSize[30];
    UINT8                                 Index;
    UINT8                                 Index1;
    UINT8                                 Index2;
    CHAR16                                *NewStringTemp;
    UINTN                                 Seg;
    UINTN                                 Bus;
    UINTN                                 Dev;
    UINTN                                 Func;
    EFI_GUID                              gSetupGuid = SETUP_GUID;
    UINTN                                 VariableSize;
    SDIO_DEV_CONFIGURATION                SdioConfiguration;
    UINT64                                TotalBytes;
    UINT32                                DriveSizeInGB;
    UINT64                                NumTenthsOfGB;
    UINT64                                RemainderInBytes;
    UINT16                                ManufactureId = 0;
    EFI_PCI_IO_PROTOCOL                   *PciIo = NULL;
    AMI_SD_EMMC_VENDOR_DEVICE_PATH        *AmiSdEmmcVendorDpNode = NULL;
    AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL  *AmiSdEmmcControllerInitProtocol = NULL;
    EFI_DEVICE_PATH_PROTOCOL              *DevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL              *TruncatedDevicePath = NULL;

    if (Class != ADVANCED_FORM_SET_CLASS)
        return;

    //
    // Assume no line strings is longer than 256 bytes.
    //
    Status = gBS->AllocatePool (
                         EfiBootServicesData,
                         STRING_SIZE,
                         (VOID**)&NewStringTemp);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->LocateHandleBuffer (
                                ByProtocol,
                                &gSdioBusInitProtocolGuid,
                                NULL,
                                &HandleCount,
                                &HandleBuffer);
    if (EFI_ERROR(Status))
        HandleCount = 0;
    
    VariableSize = sizeof(SDIO_DEV_CONFIGURATION);
    Status = gRT->GetVariable ( \
                    L"SdioDevConfiguration", \
                    &gSetupGuid, \
                    NULL, \
                    &VariableSize, \
                    &SdioConfiguration );

    if (EFI_ERROR(Status)) {
        //
        // If Error, Set default values and save "SdioConfiguration" variable.
        //
        gBS->SetMem(&SdioConfiguration, sizeof(SDIO_DEV_CONFIGURATION), 0);
    }

    for (Index = 0; Index < HandleCount; Index++) {
        Status = gBS->HandleProtocol (
                                    HandleBuffer[Index],
                                    &gSdioBusInitProtocolGuid,
                                    (VOID**)&SdioBusInterface
                                    );

        ASSERT_EFI_ERROR(Status);

        DLink = SdioBusInterface->SdioDeviceList.ForwardLink;
        if (DLink == &SdioBusInterface->SdioDeviceList) {
            continue;
        }
        do {
            SdioDevInterface = BASE_CR(DLink, SDIO_DEVICE_INTERFACE, SdioDeviceLink);
            DLink = DLink->ForwardLink;

            if (SdioDevInterface->MassStorageDevice == TRUE) {
                // Get the ManufactureId
                ManufactureId = (UINT16)((SdioDevInterface->SdioDevInfo->d4CID[3] >> 24) & 0xff);
                gBS->SetMem (VendorName, 30, 0);
                for (Index2 = 0; ManuFactureDetails[Index2].ManufactureId != 0xFFFF; Index2++) {
                    if (ManuFactureDetails[Index2].ManufactureId == ManufactureId) {
                        for (Index1 = 0; Index1 < 30; Index1++) {
                            VendorName[Index1] = (CHAR16)ManuFactureDetails[Index2].VendorString[Index1];
                        }
                        break;
                    }
                }
                
                for (Index1 = 0; Index1 < 27; Index1++) {
                    SName[Index1] = (CHAR16)SdioDevInterface->SdioDevInfo->PNM[Index1];
                }
                
                //
                // The toal byes is the multiplication of block size and 
                // maximum number of block.
                //
                TotalBytes = MultU64x64(((UINT64)SdioDevInterface->SdioDevInfo->dMaxLBA),\
                		((UINT64)SdioDevInterface->SdioDevInfo->wBlockSize));
                
                DriveSizeInGB = (UINT32) DivU64x64Remainder (TotalBytes, 1000000000, &RemainderInBytes);
                
                //
                //Convert the Remainder, which is in bytes, to number of tenths of a Decimal GB.
                //
                NumTenthsOfGB = DivU64x64Remainder (RemainderInBytes, 100000000, NULL);
                //
                // Print the Size in GB
                //
                gBS->SetMem (CardSize, 60, 0);
                UnicodeSPrint (&CardSize[0], 60, L"(%d.%dGB)", DriveSizeInGB, NumTenthsOfGB);
                gBS->SetMem (NewStringTemp, STRING_SIZE, 0);
                if (VendorName[0] != '0'){
                    // Displays the manufacturer name along with PNM
                    UnicodeSPrint (NewStringTemp, STRING_SIZE, L"%s %s%s", &VendorName[0], &SName[0], &CardSize[0]);
                } else {
                    UnicodeSPrint (NewStringTemp, STRING_SIZE, L"%s%s", &SName[0], &CardSize[0]); 
                }  
                HiiSetString (HiiHandle, SdioDev[SdioDevIndex], NewStringTemp, NULL);
                SdioConfiguration.SdioEmu[SdioDevIndex].SdMmcAddress = SdioDevInterface->SdioDevInfo->SdioBaseAddress;
                SdioConfiguration.IoDeviceType[SdioDevIndex] = 0;
            } else {

                //
                // SD slot has an IO device. Map the Manufacture ID into the table
                // and get the Vendor name and display it in Setup
                //

                ManufactureId = (UINT16)((UINT16)(SdioDevInterface->SdioDevInfo->SdIOManufactureId[1] << 8)
                                        + ((UINT16)SdioDevInterface->SdioDevInfo->SdIOManufactureId[0]));

                for ( Index2 = 0; ManuFactureDetails[Index2].ManufactureId != 0xFFFF; Index2++) {
                    if (ManuFactureDetails[Index2].ManufactureId == ManufactureId) {
                        for ( Index1 = 0; Index1 < 30; Index1++) {
                            SName[Index1] = (CHAR16)ManuFactureDetails[Index2].VendorString[Index1];
                        }
                        break;
                    }
                }
                //
                // Manufacture Id not Found. Initialize to Unknown Vendor.
                //
                if (ManuFactureDetails[Index2].ManufactureId == 0xFFFF) {
                    for ( Index1 = 0; Index1 < 30; Index1++) {
                        SName[Index1] = (CHAR16)ManuFactureDetails[Index2].VendorString[Index1];
                    }
                }
                
                gBS->SetMem (NewStringTemp, STRING_SIZE, 0);
                UnicodeSPrint (NewStringTemp, STRING_SIZE, L"IO - %s", &SName[0]);
                HiiSetString (HiiHandle, IoDevName[SdioDevIndex], NewStringTemp, NULL);
                SdioConfiguration.IoDeviceType[SdioDevIndex] = 1;
            }
            
            // Get the Device Location Info
            gBS->SetMem (NewStringTemp, STRING_SIZE, 0);
            
            if (SdioBusInterface->ControllerType == PciIoType) {
                PciIo = (EFI_PCI_IO_PROTOCOL*)SdioBusInterface->ControllerInterface;
                Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Func);
                ASSERT_EFI_ERROR(Status);
                UnicodeSPrint(NewStringTemp, STRING_SIZE, L"Bus %x Dev %x Func %x", Bus, Dev, Func);
            } else {
                AmiSdEmmcControllerInitProtocol = (AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL*)SdioBusInterface->ControllerInterface;
                Status = AmiSdEmmcControllerInitProtocol->GetDeviceName (
                                                                 AmiSdEmmcControllerInitProtocol,
                                                                 NewStringTemp);
                if (EFI_ERROR(Status)) {
                    // If GetDeviceName is not implemented get it from DevicePath
                    Status = gBS->HandleProtocol ( 
                                             HandleBuffer[Index],
                                             &gEfiDevicePathProtocolGuid,
                                            (VOID**)&DevicePath);
                                                 
                    if (!EFI_ERROR(Status)) {
                        // Traverse to last node and check for AMI_SD_EMMC_VENDOR_DEVICE_PATH node.
                        for ( ; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode(DevicePath))
                            TruncatedDevicePath = DevicePath;

                        AmiSdEmmcVendorDpNode = (AMI_SD_EMMC_VENDOR_DEVICE_PATH *)TruncatedDevicePath;
                        UnicodeSPrint (NewStringTemp, STRING_SIZE, L"Non Pci Device %X", AmiSdEmmcVendorDpNode->UID);
                    }
                }
            }

            HiiSetString (HiiHandle, SdioDevLocation[SdioDevIndex], NewStringTemp, NULL);
            SdioDevIndex++;
        } while (DLink != &SdioBusInterface->SdioDeviceList );

    }
    //
    // Update "SdioMassDevNum" setup variable according to the number
    // of installed mass storage devices 
    //
    SdioConfiguration.SdioMassDevNum = SdioDevIndex;
    Status = gRT->SetVariable( \
                 L"SdioDevConfiguration",
                 &gSetupGuid, \
                 EFI_VARIABLE_NON_VOLATILE | \
                 EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                 VariableSize,
                 &SdioConfiguration );
    
    ASSERT_EFI_ERROR(Status);

    if (HandleBuffer) {
        gBS->FreePool (HandleBuffer);
    }

    gBS->FreePool (NewStringTemp);

    return;
}
