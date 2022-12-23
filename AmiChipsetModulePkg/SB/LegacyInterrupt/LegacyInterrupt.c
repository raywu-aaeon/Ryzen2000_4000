//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file LegacyInterrupt.c
    Interface and implementation of LegacyInterrupt protocol

**/
//**********************************************************************

#include <Library/AmiPirqRouterLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>

extern  UINT8   bMaxPIRQ;
extern  UINT8   bRouterBus;
extern  UINT8   bRouterDevice;
extern  UINT8   bRouterFunction;

//
// Handle for the Legacy Interrupt Protocol instance produced by this driver
//
EFI_HANDLE                    mLegacyInterruptHandle = NULL;


/**

  @brief
  Return the number of PIRQs supported by this chipset.

  @param[in]  This                 Pointer to LegacyInterrupt Protocol
  @param[out] NumberPirqs          The pointer which point to the max IRQ number supported by this SC.

  @retval EFI_SUCCESS             Legacy BIOS protocol installed

**/
EFI_STATUS
EFIAPI
GetNumberPirqs (
    IN  EFI_LEGACY_INTERRUPT_PROTOCOL  *This,
    OUT UINT8                          *NumberPirqs
  )
{
    *NumberPirqs = bMaxPIRQ;
    return EFI_SUCCESS;
}

/**

  @brief
  Return PCI location of this device. $PIR table requires this info.

  @param[in]  This                 Protocol instance pointer.
  @param[out] Bus                  PCI Bus
  @param[out] Device               PCI Device
  @param[out] Function             PCI Function

  @retval EFI_SUCCESS             Bus/Device/Function returned

**/
EFI_STATUS
EFIAPI
GetLocation (
    IN  EFI_LEGACY_INTERRUPT_PROTOCOL  *This,
    OUT UINT8                          *Bus,
    OUT UINT8                          *Device,
    OUT UINT8                          *Function
  )
{
    *Bus        = bRouterBus;
    *Device     = bRouterDevice;
    *Function   = bRouterFunction;
    return EFI_SUCCESS;
}


//
// The Legacy Interrupt Protocol instance produced by this driver
//

EFI_LEGACY_INTERRUPT_PROTOCOL mLegacyInterruptProtocol =
{
    GetNumberPirqs,
    GetLocation,
    SbGenReadPirq,
    SbGenWritePirq
};

/**

  @brief
  Install Driver to produce Legacy Interrupt protocol.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             Legacy Interrupt protocol installed
  @retval Other                   No protocol installed, unload driver.

**/
EFI_STATUS
EFIAPI
InitializeLegacyInterrupt (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                      Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;

    DEBUG ((EFI_D_INFO, "InitializeLegacyInterrupt() Start\n"));

    Status = gBS->LocateProtocol(
                    &gEfiPciRootBridgeIoProtocolGuid,
                    NULL,
                    &PciRootBridgeIo
                    );
    if (EFI_ERROR(Status)) return Status;

    //
    // Initialize router registers buffer
    //
    Status = SbGenInitializeRouterRegisters (PciRootBridgeIo);
    if (EFI_ERROR(Status)) return Status;

    //
    // Make a new handle and install the protocol
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &mLegacyInterruptHandle,
                    &gEfiLegacyInterruptProtocolGuid,
                    &mLegacyInterruptProtocol,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  
    DEBUG ((EFI_D_INFO, "InitializeLegacyInterrupt() End\n"));
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
