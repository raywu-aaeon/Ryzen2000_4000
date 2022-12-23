//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SdioInt13.c
    Sdio driver for Legacy mode

**/

//----------------------------------------------------------------------

#include <Protocol/SdioInt13Protocol.h>
#include <Protocol/ComponentName.h>
#include <Protocol/LegacyBiosExt.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/SdioBus.h>
#include "SdioInt13.h"
#include "Token.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

//----------------------------------------------------------------------

EFI_LEGACY_BIOS_EXT_PROTOCOL        *gBiosExtensions = NULL;
UINT13_DATA                         *gI13BinData = NULL;
EFI_SDIO_PROTOCOL                   gAmiSdio;
UINT8                               gBootOverrideDeviceIndx = 0;
#ifdef  SW_SMI_IO_ADDRESS
UINT32   gSwSmiPort = SW_SMI_IO_ADDRESS;
#else
// Default Sw Smi port 
UINT32   gSwSmiPort = 0xB2;
#endif

/**
    SDIO INT13 driver entry point. Installs call back notification on 
    gEfiSdioProtocolGuid installation.

    @param  ImageHandle
    @param  SystemTable

    @retval  EFI_STATUS

**/

EFI_STATUS
EFIAPI
SdioInt13EntryPoint (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  SdioHandle = NULL;

    Status = InitInt13RuntimeImage();
    if (EFI_ERROR(Status)) return Status;

    gAmiSdio.SdioInstallLegacyDevice      = SdioInstallLegacyDevice;
    gAmiSdio.InstallSdioLegacyBootDevices = InstallSdioLegacyBootDevices;
    
     Status = gBS->InstallProtocolInterface (
                                    &SdioHandle,
                                    &gEfiSdioProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gAmiSdio
                                    );

    return Status;
}

/**
    Initialization of data structures and placement of runtime
    code of SDIO INT13

    @param  ImageHandle
    @param  SystemTable

    @retval  EFI_STATUS

**/

EFI_STATUS
InitInt13RuntimeImage()
{
    EFI_STATUS  Status;
    VOID        *Image;
    UINTN       ImageSize = 0;

    //
    // Get the SDIO INT13 runtime image
    //
    Status = gBS->LocateProtocol (
                           &gEfiLegacyBiosExtProtocolGuid,
                           NULL,
                           (VOID **)&gBiosExtensions);
    if (EFI_ERROR(Status))
        return Status;

    Status = gBiosExtensions->GetEmbeddedRom (
                                       CSM16_MODULEID,
                                       CSM16_VENDORID,
                                       CSM16_SDIO_RT_DID,
                                       &Image,
                                       &ImageSize);
    if (EFI_ERROR(Status))
        return Status;

    //
    // Do the necessary RT data initialization here using Image before it is shadowed
    //..............................
    {
#pragma pack(push, 1)
        // Update SDIO SMI information
        typedef struct _SDIO_SMM_RTS {
            UINT8   MiscInfo;
            UINT16  SmmAttr;
            UINT32  SmmPort;
            UINT32  SmmData;
        } SDIO_SMM_RTS;

        SDIO_SMM_RTS SdioSmmRt;
        SdioSmmRt.MiscInfo = 1;
        SdioSmmRt.SmmAttr = 0;
        SdioSmmRt.SmmPort = gSwSmiPort;
        SdioSmmRt.SmmData = SDIO_SWSMI;    
        
        *(SDIO_SMM_RTS*)((UINTN)Image + ((UINT13_DATA*)Image)->SdioSmmDataOffset) = SdioSmmRt;
#pragma pack(pop)
    }

    // Copy image to shadow E000/F000 area
    gI13BinData = (UINT13_DATA*)((UINTN)gBiosExtensions->CopyLegacyTable (Image, (UINT16)ImageSize, 0x10, 2));

    return EFI_SUCCESS;
}

/**
    This function retrieves SDIO device name, copies it into
    lower memory and returns a pointer to the string.

    @param  DevIndex
    @param  DevNameStringSrc
    @param  StringDestinationSegment
    @param  StringDestinationOffset
    @param  MfgStringDestinationSegment
    @param  MfgStringDestinationOffset

    @retval  EFI_STATUS
**/

EFI_STATUS
CreateDeviceName (
    UINT8  DevIndex,
    UINT8  *DevNameStringSrc,
    UINT16 *StringDestinationSegment,
    UINT16 *StringDestinationOffset,
    UINT16 *MfgStringDestinationSegment,
    UINT16 *MfgStringDestinationOffset
)
{
    UINT8 *DevName = (gI13BinData->SdioMassI13Dev)[DevIndex].DeviceNameString;
    UINT8 Index;

    //
    // Copy the string, compact it on the way (no more that one ' ' in a row)
    //
    for (Index = 0; Index < 31 && *DevNameStringSrc != 0; Index++, DevNameStringSrc++)
    {
        if ((*DevNameStringSrc == 0x20) && (*(DevNameStringSrc-1) == 0x20))
            continue;
        *DevName++ = *DevNameStringSrc;  // DevNameStringSrc incremented unconditionally
    }
    *DevName = 0;   // string terminator

    DevName = (gI13BinData->SdioMassI13Dev)[DevIndex].DeviceNameString;

    *StringDestinationSegment = (UINT16)(((UINTN)DevName & 0xf0000) >> 4);
    *StringDestinationOffset = (UINT16)((UINTN)DevName & 0xffff);

    *MfgStringDestinationSegment = (UINT16)(((UINTN)gI13BinData->MfgGenericName & 0xf0000) >> 4);
    *MfgStringDestinationOffset = (UINT16)((UINTN)gI13BinData->MfgGenericName & 0xffff);

    return EFI_SUCCESS;
}

/**
  Returns the Pointer to the Sdio_DEVICE_INTERFACE for the given Port.
    
  @param  	SdioBusInterface  Pointer to the AMI_SDIO_BUS_PROTOCOL
  @param    Port  			  Port number.

  @return   Sdio_DEVICE_INTERFACE*

**/

SDIO_DEVICE_INTERFACE *
GetSdioDevInterface (
    IN  AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface,
    IN  UINT8                   Slot
)
{

    LIST_ENTRY                   *DLink = NULL;
    SDIO_DEVICE_INTERFACE        *SdioDevInterface = NULL;

 
    for (DLink = SdioBusInterface->SdioDeviceList.ForwardLink;
           DLink != &SdioBusInterface->SdioDeviceList;
           DLink = DLink->ForwardLink ) {

        SdioDevInterface = BASE_CR(DLink, SDIO_DEVICE_INTERFACE, SdioDeviceLink);

        if (SdioDevInterface->SlotNumber == Slot) {
            break;
        }
        SdioDevInterface = NULL;
    }
    return SdioDevInterface;
}


/**
    This function takes the device index within SDIOMASS_INT13_DEV 
    list and prepares BBS entry for this device.

    @param  DevIndex
    @param  SdioMassDevice
    @param  BbsEntry

    @retval  EFI_STATUS
**/

EFI_STATUS
CreateBbsEntry (
    UINT8  DevIndex,
    IN     SDIO_MASS_DEV *SdioMassDevice,
    OUT    BBS_TABLE     *BbsEntry
)
{
    EFI_STATUS       Status;
    UINT8            Handle;
    UINT8            DevAndSysType;
    UINT8            BaidDeviceType = BBS_UNKNOWN;
    BBS_STATUS_FLAGS StatusFlags;

    ASSERT(DevIndex < SDIODEVS_MAX_ENTRIES);

    if (gBiosExtensions == NULL)
        return EFI_NOT_FOUND;

    gBS->SetMem (BbsEntry, sizeof(BBS_TABLE), 0);
    ZeroMem (&StatusFlags, sizeof(BBS_STATUS_FLAGS));
    //
    // Get the HC PCI location
    //
    BbsEntry->Bus = (UINT32)(SdioMassDevice->PciBDF >> 8);
    BbsEntry->Device = (UINT32)((SdioMassDevice->PciBDF & 0xFF) >> 3);
    BbsEntry->Function = (UINT32)(SdioMassDevice->PciBDF & 7);

    //
    // Update class/subclass information
    //
    BbsEntry->Class = PCI_CL_SYSTEM_PERIPHERALS;
    BbsEntry->SubClass = PCI_CL_SYSTEM_PERIPHERALS_SCL_SD;

    StatusFlags.Enabled = 1;
    StatusFlags.MediaPresent = 1;
    BbsEntry->StatusFlags = StatusFlags;  // Enabled, Unknown media

    //
    // Copy the device name string into low memory at gLegacyMemoryAddress, and
    // update the string pointer in BBS table entry
    //
    Status = CreateDeviceName (
                          DevIndex,
                          SdioMassDevice->DevString,
                          &BbsEntry->DescStringSegment,
                          &BbsEntry->DescStringOffset,
                          &BbsEntry->MfgStringSegment,
                          &BbsEntry->MfgStringOffset);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status))
        return Status;

    DevAndSysType = (SYSTYPE_ATA << 4) + DEVTYPE_SYS;
    Handle = (UINT8)SdioMassDevice->LogicalAddress;

    switch (SdioMassDevice->StorageType) {

        case SDIO_MASS_DEV_HDD:
            BbsEntry->DeviceType = BBS_HARDDISK;
            BaidDeviceType = BAID_TYPE_RMD_HDD;
            Handle |= 0x80;
            BbsEntry->BootHandlerSegment = (UINT16)((UINTN)gI13BinData >> 4);
            BbsEntry->BootHandlerOffset = gI13BinData->BcvOffset + DevIndex*4;
            break;
        case SDIO_MASS_DEV_ARMD:
            BbsEntry->DeviceType = BBS_FLOPPY;
            BaidDeviceType = BAID_TYPE_RMD_FDD;
            BbsEntry->BootHandlerSegment = (UINT16)((UINTN)gI13BinData >> 4);
            BbsEntry->BootHandlerOffset = gI13BinData->BcvOffset + DevIndex*4;
            break;
        default:
            BbsEntry->DeviceType = BBS_UNKNOWN;
    }

    BbsEntry->InitPerReserved = ((UINT32)BaidDeviceType<<24)
                        +((UINT32)Handle<<8)
                        +(UINT32)DevAndSysType;

    *(UINTN*)(&BbsEntry->IBV1) = (UINTN)SdioMassDevice->Handle;

    return EFI_SUCCESS;
}


/**
    This function installs SDIO INT13 device

    @param  SdioMassDevice

    @retval  EFI_STATUS
**/

EFI_STATUS
EFIAPI
SdioInstallLegacyDevice (
    SDIO_MASS_DEV    *SdioMassDevice
)
{
    BBS_TABLE     BbsEntry;
    EFI_STATUS    Status;
    UINT8         EntryNumber = 0xff;
    UINT8         Index;
    SDIO_DEV_INFO *Device = (SDIO_DEV_INFO*)SdioMassDevice->DevInfo;

    DEBUG((DEBUG_INFO, "Installing SDIO INT13 device %x\n", SdioMassDevice));

    // If the device Block size is not equal to 512 bytes 
    // Don't add the device as the INT13 device ( Legacy supported device). 
    if (Device->wBlockSize != 512 ) {
        return EFI_SUCCESS;
    }
    
    //
    // See if device is already in the list, if yes - return error.
    //
    for (Index = 0; Index < SDIODEVS_MAX_ENTRIES; Index++) {
        if ((gI13BinData->SdioMassI13Dev)[Index].Handle == (UINT8)SdioMassDevice->LogicalAddress) {
            ASSERT(FALSE);  // ERROR: Device already exists
            return EFI_INVALID_PARAMETER;
        }
    }
    //
    // Look for an empty slot in BcvLookupTable
    //
    for (Index = 0; Index < SDIODEVS_MAX_ENTRIES; Index++) {
        if  ((gI13BinData->SdioMassI13Dev)[Index].Handle == 0)
            break;
    }
    ASSERT(Index<SDIODEVS_MAX_ENTRIES);

    if (Index == SDIODEVS_MAX_ENTRIES) {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = gBiosExtensions->UnlockShadow(0, 0, 0, 0);
    ASSERT_EFI_ERROR(Status);

    Status = CreateBbsEntry (Index, SdioMassDevice, &BbsEntry);
    ASSERT_EFI_ERROR(Status);

    Status = gBiosExtensions->InsertBbsEntryAt (
                                           gBiosExtensions,
                                           &BbsEntry,
                                           &EntryNumber);
    ASSERT_EFI_ERROR(Status);

    //
    // Entry has been successfully added, update the lookup table
    //
    (gI13BinData->SdioMassI13Dev)[Index].Handle = (UINT8)SdioMassDevice->LogicalAddress;
    (gI13BinData->SdioMassI13Dev)[Index].BbsEntryNo = EntryNumber;
    (gI13BinData->SdioMassI13Dev)[Index].DevBaidType = (UINT8)(BbsEntry.InitPerReserved>>24);

    //
    // Update device geometry related information
    //
    (gI13BinData->SdioMassI13Dev)[Index].NumHeads = Device->bNonLBAHeads;
    (gI13BinData->SdioMassI13Dev)[Index].LBANumHeads = Device->bHeads;
    (gI13BinData->SdioMassI13Dev)[Index].NumCylinders = Device->wNonLBACylinders;
    (gI13BinData->SdioMassI13Dev)[Index].LBANumCyls = Device->wCylinders;
    (gI13BinData->SdioMassI13Dev)[Index].NumSectors = Device->bNonLBASectors;
    (gI13BinData->SdioMassI13Dev)[Index].LBANumSectors = Device->bSectors;
    (gI13BinData->SdioMassI13Dev)[Index].BytesPerSector = Device->wBlockSize;
//    (gI13BinData->SdioMassI13Dev)[Index].MediaType = Device->bMediaType;
    (gI13BinData->SdioMassI13Dev)[Index].LastLBA = Device->dMaxLba;

    Status = gBiosExtensions->LockShadow (0, 0);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}

/**
    This function installs Sdio INT13 devices
     
    @param   VOID

    @retval  EFI_SUCCESS  INT13 support for the Sdio device is installed successfully.

**/

EFI_STATUS
EFIAPI
InstallSdioLegacyBootDevices(
    VOID
)
{
    UINTN                  Index;
    UINT8                  SlotNo = 0;
    UINTN                  NumHandles = 0;
    UINTN                  PciSeg, PciBus, PciDev, PciFunc;
    EFI_STATUS             Status;
    SDIO_DEV_INFO          SdioDevInfo;
    SDIO_MASS_DEV          SdioMassDevInfo;
    EFI_HANDLE             *HandleBuffer = NULL;
    SDIO_DEVICE_INTERFACE  *SdioDevInterface = NULL;
    AMI_SDIO_BUS_PROTOCOL  *SdioBusInterface = NULL;
    EFI_PCI_IO_PROTOCOL    *PciIo = NULL;
   
    Status = gBS->LocateHandleBuffer (ByProtocol, &gSdioBusInitProtocolGuid, NULL, &NumHandles, &HandleBuffer);
    if (EFI_ERROR(Status)) {
        // Return if no SDIO controller found in the system. 
        return Status;
    }    
        
    for (Index = 0; Index < NumHandles; ++Index) {
            
        gBS->HandleProtocol (HandleBuffer[Index], &gSdioBusInitProtocolGuid, (VOID**)&SdioBusInterface);
            
        if (SdioBusInterface) {
            // installs Sdio INT13 devices
            for (SlotNo = 0; SlotNo < SdioBusInterface->NumberOfSlotsImplemented; SlotNo++) {
                    
                SdioDevInterface = GetSdioDevInterface (SdioBusInterface, SlotNo);
                
                if (SdioDevInterface && (SdioDevInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY)) {
                        
                    SdioDevInfo.wBlockSize = SdioDevInterface->SdioDevInfo->wBlockSize;
                    SdioDevInfo.dMaxLba = SdioDevInterface->SdioDevInfo->dMaxLBA;
                    SdioDevInfo.bHeads = SdioDevInterface->SdioDevInfo->NumHeads;
                    SdioDevInfo.bSectors = SdioDevInterface->SdioDevInfo->NumSectors;
                    SdioDevInfo.wCylinders = SdioDevInterface->SdioDevInfo->NumCylinders;
                    SdioDevInfo.bNonLBAHeads = SdioDevInterface->SdioDevInfo->LBANumHeads;
                    SdioDevInfo.bNonLBASectors = SdioDevInterface->SdioDevInfo->LBANumSectors;
                    SdioDevInfo.wNonLBACylinders = SdioDevInterface->SdioDevInfo->LBANumCyls;

                    //
                    // Get the SDIO controller Bus,Dev and Fun
                    //
                    if (SdioBusInterface->ControllerType == PciIoType) {
                        PciIo = (EFI_PCI_IO_PROTOCOL*)SdioBusInterface->ControllerInterface;
                        PciIo->GetLocation (PciIo, &PciSeg, &PciBus, &PciDev, &PciFunc);

                        SdioMassDevInfo.PciBDF=(UINT16)((PciBus << 8)+(PciDev << 3) + PciFunc);
                    }
                    SdioMassDevInfo.DevString = &SdioDevInterface->SdioDevInfo->PNM[0];
                    SdioMassDevInfo.DevInfo = (VOID*)&SdioDevInfo;
                    SdioMassDevInfo.LogicalAddress = SdioDevInterface->SdioDevInfo->DeviceAddress;
                    SdioMassDevInfo.StorageType = SdioDevInterface->SdioDevInfo->bStorageType;
                    SdioMassDevInfo.Handle = SdioDevInterface->SdioDeviceHandle;
                    SdioInstallLegacyDevice (&SdioMassDevInfo);
                }   
            }
        }
    }

    if (HandleBuffer != NULL) {
        gBS->FreePool (HandleBuffer);
    }

    return EFI_SUCCESS;
}
