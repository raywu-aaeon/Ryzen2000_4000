//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
 
//**********************************************************************
//
/** @file AmiPspDxe.c
    PSP Device driver   

**/

#include "Token.h"
#include <Pci.h>
#include <AmiDxeLib.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <BootScriptCommon.h>
#include <AmiChipsetIoLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspApobLib.h>
#include <Library/AmdCapsuleLib.h>

EFI_STATUS
EFIAPI
PspDxeEntryPoint (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
);

EFI_STATUS
EFIAPI AmiPspDriverSupported (
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
);

EFI_STATUS
EFIAPI AmiPspDriverStart (
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
);

EFI_STATUS
EFIAPI AmiPspDriverStop (
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    UINTN                       NumberOfChildren,
  IN    EFI_HANDLE                  *ChildHandleBuffer
);

typedef struct {
    UINT64                  Address;
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;

#define PSP_PCI_CFG_ADDRESS(bus, dev, func, reg) \
         (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
         ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xFFFFFFFF)

#define PSP_REG(Reg)    PSP_PCI_CFG_ADDRESS(0, 8, 0, Reg)




// EFI Driver Binding Protocol Instance
EFI_DRIVER_BINDING_PROTOCOL AmiPspDriverBinding = {
    AmiPspDriverSupported,
    AmiPspDriverStart,
    AmiPspDriverStop,
    0x10,
    NULL,
    NULL
};

EFI_S3_SAVE_STATE_PROTOCOL      *BootScriptSave = NULL;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
EFI_EVENT                       ReadyToBootEvent;

//
// ready to boot call back boot script table
//
BOOT_SCRIPT_PCI_REGISTER_SAVE ReadyToBootPspScriptTbl[] = {
//-    PSP_REG(0x48), EfiBootScriptWidthUint32,          // BAR control
    PSP_REG(0x10), EfiBootScriptWidthUint32,          // BAR64
    PSP_REG(0x18), EfiBootScriptWidthUint32,          // BAR1
    PSP_REG(0x1C), EfiBootScriptWidthUint32,          // BAR2
    PSP_REG(0x24), EfiBootScriptWidthUint32,          // MSIX
    PSP_REG(0x3C), EfiBootScriptWidthUint32,          // Int line
//-    PSP_REG(0x04), EfiBootScriptWidthUint32,          // Command
};
UINTN   ReadyToBootPspScriptSize = sizeof (ReadyToBootPspScriptTbl) /
         sizeof (BOOT_SCRIPT_PCI_REGISTER_SAVE);

/**
    PSP Driver Supported function
    This function is a part of DriverBinding protocol

        
    @param This 
    @param ControllerHandle 
    @param RemainingDevicePath 

         
    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI AmiPspDriverSupported(
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{
    EFI_STATUS          Status;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    PCI_STD_DEVICE      Pci;

    // Get PciIo pointer
    Status = pBS->OpenProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
                   (void **)&PciIo, This->DriverBindingHandle,
                   ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER);

    if (EFI_ERROR (Status))
        return  EFI_UNSUPPORTED;
    
    Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint32, 0,
                         sizeof (Pci) / sizeof (UINT32), &Pci);

    if (EFI_ERROR (Status))
    {
        pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle, ControllerHandle);
        return  EFI_UNSUPPORTED;
    }
    
    // Check if this is PSP device
    if ((Pci.Header.VendorId != 0x1022) || (Pci.Header.DeviceId != 0x1578))
    {
        pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle, ControllerHandle);
        return  EFI_UNSUPPORTED;
    }

    return  Status;
}

/**
    PSP Driver Start function
				

        
    @param This 
    @param ControllerHandle 
    @param RemainingDevicePath 

         
    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI AmiPspDriverStart(
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
)
{
    EFI_STATUS          Status;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    UINT64              Attributes;

    // Open PCI I/O Protocol
    Status = pBS->OpenProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
                   (void **)&PciIo, This->DriverBindingHandle, ControllerHandle,
                   EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR (Status))
        if ((Status != EFI_ALREADY_STARTED) || (PciIo == NULL))
            return Status;
    if ((EFI_ERROR (Status)) && (Status != EFI_ALREADY_STARTED))
    {
        pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle, ControllerHandle);
        return Status;
    }
    
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationGet, 0, &Attributes);
    if (EFI_ERROR (Status))
    {
        pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle, ControllerHandle);
        return Status;
    }
    
    if ((Attributes & EFI_PCI_IO_ATTRIBUTE_MEMORY) != 0)
    {
        Status = EFI_ALREADY_STARTED;
        return Status;
    }
    
    Attributes = EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER;
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationEnable, Attributes, NULL);
    if(EFI_ERROR(Status))
    {
        pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle, ControllerHandle);
        return  Status;
    }

    return  Status;
}
 
/**
    PSP Driver Stop function
				

        
    @param This 
    @param ControllerHandle 
    @param NumberOfChildren 
    @param ChildHandleBuffer 

         
    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI AmiPspDriverStop(
  IN    EFI_DRIVER_BINDING_PROTOCOL *This,
  IN    EFI_HANDLE                  ControllerHandle,
  IN    UINTN                       NumberOfChildren,
  IN    EFI_HANDLE                  *ChildHandleBuffer
)
{
    EFI_STATUS          Status;
    UINT64              Attributes;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    
    // Open PCI I/O Protocol
    Status = pBS->OpenProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
                   (void **)&PciIo, This->DriverBindingHandle, ControllerHandle,
                   EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR (Status))
        if ((Status != EFI_ALREADY_STARTED) || (PciIo == NULL))
            return Status;
    
    Attributes = EFI_PCI_IO_ATTRIBUTE_MEMORY;
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationDisable, Attributes, NULL);
    
    // Close protocols, opened in Start function
    pBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid,
          This->DriverBindingHandle, ControllerHandle);

    return  Status;
}  

/**
    PSP Driver Start function
				

        
    @param This 
    @param ControllerHandle 
    @param RemainingDevicePath 

         
    @retval EFI_STATUS Return the EFI  Status

**/

VOID    
AmiPspReadyToBootCallBack(
  IN    EFI_EVENT   Event, 
  IN    VOID        *Context
)
{
    EFI_STATUS  Status;
    UINTN       i;
    UINT64      Buffer;

    if (PciRootBridgeIo == NULL)
    {
        Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL,
                       &PciRootBridgeIo);
        ASSERT_EFI_ERROR (Status);
    }

    if (BootScriptSave == NULL) {
        Status = pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid, NULL,
                       &BootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }

    for (i = 0; i < ReadyToBootPspScriptSize; i++) {
        PciRootBridgeIo->Pci.Read(
                          PciRootBridgeIo,
                          ReadyToBootPspScriptTbl[i].Width,
                          ReadyToBootPspScriptTbl[i].Address,
                          1,
                          &Buffer);
                        
        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                        ReadyToBootPspScriptTbl[i].Width,
                        ReadyToBootPspScriptTbl[i].Address,
                        1,
                        &Buffer);
    }

    pBS->CloseEvent(Event);
}

/**
    PSP Device driver entry point

               
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI
PspDxeEntryPoint (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    PeiFvHighMem;
    SOC_ID_STRUCT           SocId;

    InitAmiLib(ImageHandle, SystemTable);

    AmiPspDriverBinding.DriverBindingHandle = ImageHandle;
    AmiPspDriverBinding.ImageHandle = ImageHandle;

    Status = pBS->InstallMultipleProtocolInterfaces(
                   &AmiPspDriverBinding.DriverBindingHandle,
                   &gEfiDriverBindingProtocolGuid, &AmiPspDriverBinding,
//                   &ComponentNameProtocolGuid, &AmiPspDriverName,
                   NULL);
    ASSERT_EFI_ERROR (Status);

    //
    // Create event for boot script
    //
    Status = CreateReadyToBootEvent (TPL_NOTIFY, AmiPspReadyToBootCallBack,
              NULL, &ReadyToBootEvent);
    ASSERT_EFI_ERROR (Status);

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (!SocHardwareIdentificationCheck(&SocId))
    {
    	UINTN FvBbSize =
					#ifdef PSP_FV_BB_SIZE
    					PSP_FV_BB_SIZE;
					#else
    					FV_BB_SIZE;
					#endif
        // Only F17 needs to reserve this area
        PeiFvHighMem = HIGH_MEMORY_REGION_BB_BASE;
        Status = pBS->AllocatePages(AllocateAddress,
                                    EfiReservedMemoryType,
                                    FvBbSize / 4096,  // The number of contiguous 4 KB pages to allocate.
                                    &PeiFvHighMem );
        DEBUG ((DEBUG_INFO, "AllocatePages PeiFvHighMem status = %r\n", Status));
        DEBUG ((DEBUG_INFO, "PeiFvHighMem = %16lx\n", PeiFvHighMem));


    }
   
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
