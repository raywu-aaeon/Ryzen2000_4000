//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <AmiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Pci.h>
#include <Protocol/PciIo.h>
#include <Library/PciLib.h>
#include <Library/AmdSocBaseLib.h>

#include <CrbSmbios.h>

EFI_SMBIOS_PROTOCOL         static  *EfiSmbios = NULL;
    
#if (CRB_SMBIOS_UPDATE == 1) && (TYPE8_STRUCTURE == 0)
SMBIOS_TYPE_8 PortConnectorInfo[] = {
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x0F, 0x0D}, "J2304/J2300", "Keyboard"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x0F, 0x0E}, "J3811", "Touch pad"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x12, 0x10}, "J1504", "USB 3.0"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x12, 0x10}, "J1500", "USB 3.1"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x12, 0x10}, "J1502", "USB 3.1"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x12, 0x10}, "J1501", "USB 3.1 Type-C"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x12, 0x10}, "J1503", "USB 3.1 Type-C"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x0B, 0x1F}, "J1300", "Network"},
        {{{8, 0x09, 0}, 1, 0x22, 2, 0x00, 0x20}, "J1701", "Sata HDD"},
        {{{8, 0x09, 0}, 1, 0x22, 2, 0x00, 0x20}, "J1703", "Sata ODD"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x00, 0x1C}, "J1101", "DP0"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x00, 0x1C}, "J1100", "DP1"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x1F, 0x1D}, "J2103", "Microphone"},
        {{{8, 0x09, 0}, 1, 0x00, 2, 0x1F, 0x1D}, "J2105", "Headphone"},
};
#endif

SMBIOS_TYPE_9 SystemSlotsInfo[] = {
        // The number of this matrix must match token "NUMBER_OF_SYSTEM_SLOTS"
        {{{9, 0x11, 0}, 1, SYS_SLOT_PCIE_X8,    DBW_8X, 3, 3, 1, 0x04, 3, 0x200,    0, 0x09}, "J3604", L"PciRoot(0x0)/Pci(0x1,0x1)"}, //checked: x8
        //{{{9, 0x11, 0}, 1, SYS_SLOT_PCIE_X4,    DBW_4X, 3, 3, 2, 0x04, 3, 0x200,    0, 0x0E}, "J3606", L"PciRoot(0x0)/Pci(0x1,0x6)"}, //default disabled by CPM: x4 
        {{{9, 0x11, 0}, 1, SYS_SLOT_M2_SK1_SD,  DBW_1X, 3, 3, 3, 0x04, 3, 0x200,    0, 0x0A}, "J3711", L"PciRoot(0x0)/Pci(0x1,0x2)"}, //checked: M.2 WLAN/BT
        //{{{9, 0x11, 0}, 1, SYS_SLOT_M2_SK2,     DBW_1X, 3, 3, 4, 0x04, 3, 0x200,    0, 0x0C}, "J3712", L"PciRoot(0x0)/Pci(0x1,0x4)"}, //slot can't work, need to rework board
        {{{9, 0x11, 0}, 1, SYS_SLOT_M2_SK3,     DBW_2X, 3, 3, 5, 0x04, 3, 0x200,    0, 0x0F}, "J3704", L"PciRoot(0x0)/Pci(0x1,0x7)"}, //checked: M.2 Nvme
        {{{9, 0x11, 0}, 1, SYS_SLOT_M2_SK1_SD,  DBW_1X, 3, 3, 6, 0x04, 3, 0x200,    0, 0x0D}, "J3709", L"PciRoot(0x0)/Pci(0x1,0x5)"}, //checked: M.2 WLAN/BT
};

SMBIOS_TYPE_41  OnboardDevsInfo[] = {
        {{{41, 0x0B, 0}, 1, OBD_ETHERNET, 1, 0,    0, 3}, "Onboard LAN Brodcom", L"PciRoot(0x0)/Pci(0x1,0x3)/Pci(0x0,0x0)"},
        {{{41, 0x0B, 0}, 1,    OBD_SOUND, 1, 0, 0x0A, 5}, "HD Audio Controller", L"PciRoot(0x0)/Pci(0x8,0x1)/Pci(0x0,0x6)"},
};

#if (CRB_SMBIOS_UPDATE == 1) && (TYPE8_STRUCTURE == 0)
/**
  Function to update SMBIOS type 8 for Port Connector Information

  @param None
  @return EFI_STATUS
  
**/
VOID
EFIAPI
UpdateSmbiosType8 (VOID)
{
    EFI_STATUS                          Status;
    SMBIOS_TYPE_8                       *Type8;
    UINT8                               Index = 0;
    UINT8                               *p;
    
    for (Index = 0; Index < (sizeof(PortConnectorInfo)/sizeof(SMBIOS_TYPE_8)); Index++)
    {
        Type8 = AllocateZeroPool (sizeof(SMBIOS_PORT_CONN_INFO) + AsciiStrLen(PortConnectorInfo[Index].sIntRefDesig) + AsciiStrLen(PortConnectorInfo[Index].sExtRefDesig) + 3);
        MemCpy(Type8, &PortConnectorInfo[Index], sizeof(SMBIOS_PORT_CONN_INFO));
        Type8->PortInfo.StructureType.Handle = 0xFFFE;
        p = (UINT8*)Type8 + sizeof(SMBIOS_PORT_CONN_INFO);
        MemCpy(p, PortConnectorInfo[Index].sIntRefDesig, AsciiStrLen(PortConnectorInfo[Index].sIntRefDesig));
        if(PortConnectorInfo[Index].PortInfo.ExtRefDesig == 2)
        {
            p = p + AsciiStrLen(PortConnectorInfo[Index].sIntRefDesig) + 1;
            MemCpy(p, PortConnectorInfo[Index].sExtRefDesig, AsciiStrLen(PortConnectorInfo[Index].sExtRefDesig));
        }
        Status = EfiSmbios->Add(EfiSmbios, NULL, &Type8->PortInfo.StructureType.Handle, (EFI_SMBIOS_TABLE_HEADER *) Type8);
        DEBUG ((DEBUG_INFO , "Add SMBIOS type 8, Index %x, Status %r\n", Index, Status));
    }
    return;
}
#endif

/**
  Function to update SMBIOS type 9 for system slot information

  @param None
  @return EFI_STATUS
  
**/
VOID
EFIAPI
UpdateSmbiosType9 (VOID)
{
    EFI_STATUS                          Status;
    SMBIOS_TYPE_9                       *Type9;
    UINT8                               CurSlot;
    EFI_HANDLE                          Handle;
    EFI_DEVICE_PATH_PROTOCOL            *SlotDevs[NUMBER_OF_SYSTEM_SLOTS];
    EFI_PCI_IO_PROTOCOL                 *PciIo;
    UINTN                               SegNum;
    UINTN                               BusNum;
    UINTN                               DevNum;
    UINTN                               FuncNum;
    UINT8                               SecondaryBus;
    
    for (CurSlot = 0; CurSlot < NUMBER_OF_SYSTEM_SLOTS; CurSlot++)
    {
        SlotDevs[CurSlot] = ConvertTextToDevicePath(SystemSlotsInfo[CurSlot].DevicePathText);
        Status = gBS->LocateDevicePath (
                          &gEfiDevicePathProtocolGuid,
                          &SlotDevs[CurSlot],
                          &Handle);
        if (!EFI_ERROR(Status)) {
            Status = gBS->OpenProtocol(
                        Handle,
                        &gEfiPciIoProtocolGuid,
                        &PciIo,
                        NULL,
                        NULL,
                        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
            if (!EFI_ERROR(Status)) {
                Status = PciIo->GetLocation(
                        PciIo, 
                        &SegNum, 
                        &BusNum, 
                        &DevNum, 
                        &FuncNum);
                PciIo->Pci.Read(
                        PciIo,
                        EfiPciIoWidthUint8,
                        PCI_SBUS,
                        1,
                        &SecondaryBus);
                if (PciRead16 (PCI_LIB_ADDRESS (SecondaryBus, 0, 0, PCI_VID)) != 0xFFFF){
                    SystemSlotsInfo[CurSlot].SlotInfo.CurrentUsage = 0x4;
                    SystemSlotsInfo[CurSlot].SlotInfo.SegGroupNumber = (UINT16)SegNum;
                    SystemSlotsInfo[CurSlot].SlotInfo.BusNumber = (UINT8)BusNum;
                    SystemSlotsInfo[CurSlot].SlotInfo.DevFuncNumber = (UINT8)((DevNum << 3) + FuncNum);
                    DEBUG ((DEBUG_INFO , "Slot implement with Bus %x Dev %x Func %x\n", BusNum, DevNum, FuncNum));
                }
            }
        }
        Type9 = AllocateZeroPool (sizeof(SMBIOS_SYSTEM_SLOTS_INFO) + AsciiStrLen(SystemSlotsInfo[CurSlot].sSlotDes) + 2);
        MemCpy(Type9, &SystemSlotsInfo[CurSlot], sizeof(SMBIOS_SYSTEM_SLOTS_INFO));
        Type9->SlotInfo.StructureType.Handle = 0xFFFE;
        MemCpy(((UINT8*)Type9 + sizeof(SMBIOS_SYSTEM_SLOTS_INFO)), SystemSlotsInfo[CurSlot].sSlotDes, AsciiStrLen(SystemSlotsInfo[CurSlot].sSlotDes));
        Status = EfiSmbios->Add(EfiSmbios, NULL, &Type9->SlotInfo.StructureType.Handle, (EFI_SMBIOS_TABLE_HEADER *) Type9);
        DEBUG ((DEBUG_INFO , "Add SMBIOS type 9, CurSlot %x, Status %r\n", CurSlot, Status));
    }
    return;
}

/**
  Function to update SMBIOS type 41 for Onboard Devices Extended Information

  @param None
  @return EFI_STATUS
  
**/
VOID
EFIAPI
UpdateSmbiosType41 (VOID)
{
    EFI_STATUS                          Status;
    SMBIOS_TYPE_41                      *Type41;
    UINT8                               Index;
    EFI_HANDLE                          Handle;
    EFI_DEVICE_PATH_PROTOCOL            *OnboardDevs;
    EFI_PCI_IO_PROTOCOL                 *PciIo;
    UINTN                               SegNum;
    UINTN                               BusNum;
    UINTN                               DevNum;
    UINTN                               FuncNum;
    
    for (Index = 0; Index < (sizeof(OnboardDevsInfo)/sizeof(SMBIOS_TYPE_41)); Index++)
    {
        OnboardDevs = ConvertTextToDevicePath(OnboardDevsInfo[Index].DevicePathText);
        Status = gBS->LocateDevicePath (
                          &gEfiDevicePathProtocolGuid,
                          &OnboardDevs,
                          &Handle);
        if (!EFI_ERROR(Status)) {
            Status = gBS->OpenProtocol(
                        Handle,
                        &gEfiPciIoProtocolGuid,
                        &PciIo,
                        NULL,
                        NULL,
                        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
            if (!EFI_ERROR(Status)) {
                Status = PciIo->GetLocation(
                        PciIo, 
                        &SegNum, 
                        &BusNum, 
                        &DevNum, 
                        &FuncNum);
                if (PciRead16 (PCI_LIB_ADDRESS (BusNum, DevNum, FuncNum, PCI_VID)) != 0xFFFF){
                    OnboardDevsInfo[Index].OnboardDevExtInfo.DeviceType |= 0x80;
                    OnboardDevsInfo[Index].OnboardDevExtInfo.SegGroupNumber = (UINT16)SegNum;
                    OnboardDevsInfo[Index].OnboardDevExtInfo.BusNumber = (UINT8)BusNum;
                    OnboardDevsInfo[Index].OnboardDevExtInfo.DevFuncNumber = (UINT8)((DevNum << 3) + FuncNum);
                    DEBUG ((DEBUG_INFO , "Slot implement with Bus %x Dev %x Func %x\n", BusNum, DevNum, FuncNum));
                }
            }
        }
        Type41 = AllocateZeroPool (sizeof(SMBIOS_ONBOARD_DEV_EXT_INFO) + AsciiStrLen(OnboardDevsInfo[Index].sRefDesignation) + 2);
        MemCpy(Type41, &OnboardDevsInfo[Index], sizeof(SMBIOS_ONBOARD_DEV_EXT_INFO));
        Type41->OnboardDevExtInfo.StructureType.Handle = 0xFFFE;
        MemCpy(((UINT8*)Type41 + sizeof(SMBIOS_ONBOARD_DEV_EXT_INFO)), OnboardDevsInfo[Index].sRefDesignation, AsciiStrLen(OnboardDevsInfo[Index].sRefDesignation));
        Status = EfiSmbios->Add(EfiSmbios, NULL, &Type41->OnboardDevExtInfo.StructureType.Handle, (EFI_SMBIOS_TABLE_HEADER *) Type41);
        DEBUG ((DEBUG_INFO , "Add SMBIOS type 41, Index %x, Status %r\n", Index, Status));
    }
    return;
}
/**
  Callback function executed when the EndOfDxe event group is signaled.

  @param[in] Event      Event whose notification function is being invoked.
  @param[in] Context    The pointer to the notification function's context, which
                        is implementation-dependent.
**/
VOID
EFIAPI
UpdateSmbiosOnEndOfDxe (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
    EFI_STATUS          Status;
    
    Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &EfiSmbios);
    if (EFI_ERROR (Status))
    {
        DEBUG ((DEBUG_ERROR , "gBS->LocateProtocol(gEfiSmbiosProtocolGuid)... ERROR\n"));
        return;
    }
#if (CRB_SMBIOS_UPDATE == 1) && (TYPE8_STRUCTURE == 0)
    UpdateSmbiosType8();
#endif
    
#if (CRB_SMBIOS_UPDATE == 1) && (SYSTEM_SLOT_INFO == 0)
    UpdateSmbiosType9();
#endif
    
#if (CRB_SMBIOS_UPDATE == 1) && (TYPE41_STRUCTURE == 0)
    UpdateSmbiosType41();
#endif
    
    Status = gBS->CloseEvent (Event);
    ASSERT_EFI_ERROR (Status);
    return;
}
/**
   The entry function of the CrbSmbios driver.

   This function updates SMBIOS for different board design.

   @param[in] ImageHandle  The firmware allocated handle for the EFI image.
   @param[in] SystemTable  A pointer to the EFI System Table.

   @retval EFI_SUCCESS     The entry point is executed successfully.
   @retval EFI_UNSUPPORTED Do not support ACPI S3.
   @retval other           Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
CrbSmbiosInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS    Status;
    EFI_EVENT     EndOfDxeEvent;
    
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    UpdateSmbiosOnEndOfDxe,
                    NULL,
                    &gEfiEndOfDxeEventGroupGuid,
                    &EndOfDxeEvent
                    );
    ASSERT_EFI_ERROR (Status);
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
