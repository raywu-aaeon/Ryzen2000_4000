//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file UsbIrq.c
    This file for USB IRQ support.
**/

// Module specific Includes
#include <Token.h>

// Consumed Protocols
#include "Uhcd.h"
#include <Protocol/Cpu.h>
#include <Protocol/Legacy8259.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/PciIo.h>
#include <Protocol/LegacyBios.h>
#include <Library/AmiShadowLib.h>
#include "UsbIrq.h"

EFI_LEGACY_8259_PROTOCOL  *gLegacy8259;
EFI_CPU_ARCH_PROTOCOL     *gCpuArch;
EFI_USB_PROTOCOL          *gAmiUsbController;
USB_GLOBAL_DATA           *gUsbData;
UINT16                    gIrqEnableStore;
URP_STRUC                 *gParameters = NULL;
USB_DATA_LIST             *gUsbDataList = NULL;
HC_STRUC                  **gHcTable = NULL;
EFI_SMM_CONTROL2_PROTOCOL *gSmmCtl = NULL;
URP_STRUC                 *gUrpBuffer=NULL;
UINT8                     gUefiIsrInstall = FALSE;
UINT8                     gLegacyIsrInstall = FALSE;
UINT8                     gLegacyBiosInstall = FALSE;
EFI_LEGACY_BIOS_PROTOCOL  *gLegacyBios = NULL;

#ifndef SLAVE_8259_IRQ
#define SLAVE_8259_IRQ    0x02
#endif

#define LEGACY_HOST_INFO_STRUCT          0x24245548  //$$UH
#define LEGACY_HOST_INFO_STRUCT_SIZE     0x4
#define URP_COUNT_SIZE                   0x1
#define URP_INFO_SIZE                    0x5
#define MEMORY_OFFSET_1M                 0x100000
#define MEMORY_OFFSET_896K               0xe0000
#define IRQ0_LEGACY_INT_OFFSET           0x08
#define IRQ8_LEGACY_INT_OFFSET           0x70


#define LEGACY_ISR_TABLE_STRUCT1         0x24245531  //$$U1
#define LEGACY_ISR_TABLE_STRUCT1_SIZE    0x04
#define LEGACY_ISR_TABLE_STRUCT2         0x24245532  //$$U2
#define LEGACY_ISR_TABLE_STRUCT2_SIZE    0x04

#define GenericIrqHandler(x) VOID UsbInterruptHandler##x (\
    IN EFI_EXCEPTION_TYPE   InterruptType,\
    IN EFI_SYSTEM_CONTEXT   SystemContext\
)\
{\
    UsbInterruptHandler(x);\
}

typedef VOID (INTERRUPT_HANDLER_MAP)(
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext );



/**
  USB IRQ Interrupt Handler

  @param Irq           - USB IRQ number.

*/

VOID
EFIAPI
UsbInterruptHandler(
    EFI_8259_IRQ    Irq
)
{
    EFI_TPL     OldTpl;
    UINTN       Index;
    UINT8       SwSmiValue = gUsbData->UsbSwSmi;
    UINT8       DataSize = 1;

    OldTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);

    // clear the interrupt flag
    gLegacy8259->EndOfInterrupt(gLegacy8259, Irq);


    //Find Usb Host & exectue interrupt.
    for (Index = 0; Index < gUsbDataList->NumOfHc; Index++) {
        if (gHcTable[Index]->Irq == Irq) {
            gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
            gParameters->FuncNumber = USB_API_HC_PROC;
            gParameters->SubFunc = AmiUsbHc_ProcessInterrupt;
            gParameters->RetValue = USB_ERROR;
            gParameters->ApiData.HcProc.ParamBuffer = &gHcTable[Index];
            gParameters->ApiData.HcProc.ParamSize = sizeof(VOID*) * 1;
            gParameters->ApiData.HcProc.HcType = gHcTable[Index]->HcType;
            gParameters->ApiData.HcProc.RetVal = 0;
            if (gAmiUsbController->UsbInvokeApi) {
                gAmiUsbController->UsbInvokeApi(gParameters);
            } else {
                if (gUsbData->UsbRuntimeDriverInSmm) {
                    if (gSmmCtl != NULL)
                        gSmmCtl->Trigger(gSmmCtl, &SwSmiValue, &DataSize, 0, 0);
                }
            }
        }
    }

    gBS->RestoreTPL(OldTpl);
}

//
// Usb Interrutp Handler
//
    GenericIrqHandler(0)
    GenericIrqHandler(1)
    GenericIrqHandler(2)
    GenericIrqHandler(3)
    GenericIrqHandler(4)
    GenericIrqHandler(5)
    GenericIrqHandler(6)
    GenericIrqHandler(7)
    GenericIrqHandler(8)
    GenericIrqHandler(9)
    GenericIrqHandler(10)
    GenericIrqHandler(11)
    GenericIrqHandler(12)
    GenericIrqHandler(13)
    GenericIrqHandler(14)
    GenericIrqHandler(15)

//
// Usb Interrupt Handler list
//
INTERRUPT_HANDLER_MAP* UsbInterruptHandlerList[] = {
    UsbInterruptHandler0,
    UsbInterruptHandler1,
    UsbInterruptHandler2,
    UsbInterruptHandler3,
    UsbInterruptHandler4,
    UsbInterruptHandler5,
    UsbInterruptHandler6,
    UsbInterruptHandler7,
    UsbInterruptHandler8,
    UsbInterruptHandler9,
    UsbInterruptHandler10,
    UsbInterruptHandler11,
    UsbInterruptHandler12,
    UsbInterruptHandler13,
    UsbInterruptHandler14,
    UsbInterruptHandler15,
    NULL };

/**
    The Eevent wait for Legacy Bios protocol ready.

    @param Event      Efi event occurred upon Legacy Bios protocol ready.
    @param Context    Not used

    @retval None

**/
    
VOID
EFIAPI
CsmReadyEvent (
    IN    EFI_EVENT     Event,
    IN    VOID          *Context
)
{
    gLegacyBiosInstall = TRUE;
}

/**
    Read To Boot Callback routine for init USB legacy ISR.

    @param Event     Efi event occurred upon Read To Boot
    @param Context   Not used

    @retval None

**/

VOID
EFIAPI
UsbIsrReadyToBoot (
    IN    EFI_EVENT     Event,
    IN    VOID          *Context
)
{
    UINT32      UsbIsrStructOffset;
    UINT32      UrpTempOffset = (UINT32)gUrpBuffer;
    UINTN       Index;
    URP_STRUC   *Parameters;
    UINT32      IntTableOffset, IsrSegment;
    UINT16      IrqEnableTemp1 = 0;
    UINT16      IrqEnableTemp2;

    // check gLegacyBios protocol ready.
    if (gLegacyBiosInstall == FALSE) return;
    // Check Usb Legacy Isr install.
    if (gLegacyIsrInstall == TRUE) return;
    
    gLegacyIsrInstall = TRUE;
    
    //Open shadow
    NbRuntimeShadowRamWrite(TRUE);
    
    // seek e0000~100000 memory to find '$$UH'
    for (UsbIsrStructOffset = MEMORY_OFFSET_896K; UsbIsrStructOffset < MEMORY_OFFSET_1M; ++UsbIsrStructOffset) {
        if (*(UINT32*)UsbIsrStructOffset == LEGACY_HOST_INFO_STRUCT) break;
    }
    UsbIsrStructOffset += LEGACY_HOST_INFO_STRUCT_SIZE;
    
    // Set Urp info to shadow ram. 
    *(UINT8*)UsbIsrStructOffset = gUsbDataList->NumOfHc;
    UsbIsrStructOffset += URP_COUNT_SIZE;

    for (Index = 0; Index < gUsbDataList->NumOfHc; Index++){
        Parameters = (URP_STRUC*)UrpTempOffset;
        Parameters->ApiData.HcProc.ParamBuffer = &gHcTable[Index];
        *(UINT8*)UsbIsrStructOffset = gHcTable[Index]->Irq;
        *(UINT32*)(UsbIsrStructOffset + 1) = UrpTempOffset;
        UsbIsrStructOffset += URP_INFO_SIZE;
        UrpTempOffset += sizeof(URP_STRUC);
    }

    // close shodow
    NbRuntimeShadowRamWrite(FALSE);

    // seek e0000~100000 memory to find '$$U1'
    for (UsbIsrStructOffset = MEMORY_OFFSET_896K; UsbIsrStructOffset < MEMORY_OFFSET_1M; ++UsbIsrStructOffset) {
        if (*(UINT32*)UsbIsrStructOffset == LEGACY_ISR_TABLE_STRUCT1) break;
    }
    UsbIsrStructOffset += LEGACY_ISR_TABLE_STRUCT1_SIZE;

    // seek e0000~100000 memory to find '$$U2'
    for (IsrSegment = MEMORY_OFFSET_896K; IsrSegment < MEMORY_OFFSET_1M; ++IsrSegment) {
        if (*(UINT32*)IsrSegment == LEGACY_ISR_TABLE_STRUCT2) break;
    }
    IsrSegment += LEGACY_ISR_TABLE_STRUCT2_SIZE;
    IsrSegment = IsrSegment - (UINT16)*(UINT16*)UsbIsrStructOffset;
    IsrSegment = IsrSegment >> 4;

    for (Index = 0; Index < gUsbDataList->NumOfHc; Index++) {

        IrqEnableTemp2 = 1 << (gHcTable[Index]->Irq);

        if (!(IrqEnableTemp2 & IrqEnableTemp1)) {
            IrqEnableTemp1 |= 1 << (gHcTable[Index]->Irq);
            
            IntTableOffset = (UINT32)gHcTable[Index]->Irq;
            if (gHcTable[Index]->Irq < 8) {
                IntTableOffset = (IntTableOffset + IRQ0_LEGACY_INT_OFFSET) * 4;
            } else {
                IntTableOffset = (IntTableOffset - 8 + IRQ8_LEGACY_INT_OFFSET) * 4;
            }
            *(UINT16*)IntTableOffset = *(UINT16*)(gHcTable[Index]->Irq * 2 + UsbIsrStructOffset);
            *(UINT16*)(IntTableOffset + 2) = (UINT16)IsrSegment;
        }
    }
}

/**
  This function call to install the USB Legacy Irq handler.

  @param     This                    The AMI_USB_ISR_PROTOCOL instance.

  @retval    EFI_SUCCESS             The USB handler was installed.
  @retval    EFI_UNSUPPORTED         The platform does not support Usb irq interrupts.
  @retval    EFI_DEVICE_ERROR        The Usb irq handler could not be registered.

*/

EFI_STATUS
EFIAPI
InstallUsbLegacyInterrupt (
    IN AMI_USB_ISR_PROTOCOL    *This
)
{
    if (gUefiIsrInstall == FALSE) return EFI_SUCCESS;
    UsbIsrReadyToBoot(NULL, NULL);
    return EFI_SUCCESS;
}

/**
  This function call to install the USB Irq handler.

  @param     This                    The AMI_USB_ISR_PROTOCOL instance.

  @retval    EFI_SUCCESS             The USB handler was installed.
  @retval    EFI_UNSUPPORTED         The platform does not support Usb irq interrupts.
  @retval    EFI_DEVICE_ERROR        The Usb irq handler could not be registered.

*/

EFI_STATUS
EFIAPI
InstallUsbInterrupt (
    IN AMI_USB_ISR_PROTOCOL    *This
)
{
    EFI_STATUS            Status;
    UINT32                UsbVector = 0;
    VOID                  *InterruptHandlerAddr;
    UINT16                IrqEnableTemp = 1 << (gHcTable[gUsbDataList->NumOfHc-1]->Irq);
    UINT32                UrpTempOffset = (UINT32)gUrpBuffer;

    if (gUefiIsrInstall == FALSE) gUefiIsrInstall = TRUE;
   
    // Init URP_STRUC data.
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_HC_PROC;
    gParameters->SubFunc = AmiUsbHc_ProcessInterrupt;
    gParameters->RetValue = USB_ERROR;
    gParameters->ApiData.HcProc.ParamBuffer = &gHcTable[gUsbDataList->NumOfHc - 1];
    gParameters->ApiData.HcProc.ParamSize = sizeof(VOID*)*1;
    gParameters->ApiData.HcProc.HcType = gHcTable[gUsbDataList->NumOfHc - 1]->HcType;
    gParameters->ApiData.HcProc.RetVal = 0;
    UrpTempOffset += sizeof(URP_STRUC) * (gUsbDataList->NumOfHc - 1);
    // Check this USB Host IRQ Handle has been installed.
    if (gIrqEnableStore&IrqEnableTemp) {
        CopyMem((UINT32*)UrpTempOffset, gParameters, sizeof(URP_STRUC));
        return EFI_SUCCESS;
    }

    if (gUsbData->UsbRuntimeDriverInSmm) {
        if (!gSmmCtl) {
            Status = gBS->LocateProtocol(&gEfiSmmControl2ProtocolGuid, NULL, (VOID**)&gSmmCtl);
            ASSERT_EFI_ERROR(Status);
        }
    }

    // Get Interrupt vector.
    Status = gLegacy8259->GetVector(gLegacy8259, gHcTable[gUsbDataList->NumOfHc-1]->Irq, (UINT8 *)&UsbVector);
    ASSERT_EFI_ERROR(Status);

    // Get Usb Interrupt handler address.
    InterruptHandlerAddr = (VOID*)UsbInterruptHandlerList[gHcTable[gUsbDataList->NumOfHc-1]->Irq];

    // Register USB interrupt handler
    Status = gCpuArch->RegisterInterruptHandler(gCpuArch, UsbVector, InterruptHandlerAddr);
    ASSERT_EFI_ERROR(Status);
    
    if (!EFI_ERROR(Status)) {
        gIrqEnableStore |= 1 << (gHcTable[gUsbDataList->NumOfHc-1]->Irq);

        // Enable USB Irq.
        gLegacy8259->EnableIrq(gLegacy8259, gHcTable[gUsbDataList->NumOfHc-1]->Irq, FALSE);
    
        // Enable slave 8259.   
        if (gHcTable[gUsbDataList->NumOfHc-1]->Irq > 7)
            gLegacy8259->EnableIrq(gLegacy8259, SLAVE_8259_IRQ, FALSE);
            
        CopyMem((UINT32*)UrpTempOffset, gParameters, sizeof(URP_STRUC));
    }
  
    return Status;
}

//
// USB isr protocol
//
AMI_USB_ISR_PROTOCOL gAmiUsbIsrProtocol =
{
    InstallUsbInterrupt,
    InstallUsbLegacyInterrupt
};

/**
  Initialize the USB IRQ driver

  @param  ImageHandle - ImageHandle of the loaded driver
  @param  SystemTable - Pointer to the System Table

  @retval  EFI_SUCCESS           - USB ISR Protocol created
  @retval  EFI_OUT_OF_RESOURCES  - Not enough resources available to initialize driver.
  @retval  EFI_DEVICE_ERROR      - A device error occured attempting to initialize the driver.

*/

EFI_STATUS
EFIAPI 
UsbIrqInitEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    EFI_STATUS            Status;
    EFI_EVENT             ReadyToBoot;
    EFI_EVENT             LegacyBiosEvent;
    VOID                  *LegacyBiosReg;

    // Find the Legacy Interrupt(8259) Protocol
    Status = gBS->LocateProtocol(&gEfiLegacy8259ProtocolGuid, 0, (VOID**)&gLegacy8259);
    ASSERT_EFI_ERROR(Status);

    // Find the CPU Arch Protocol
    Status = gBS->LocateProtocol(&gEfiCpuArchProtocolGuid, 0, (VOID**)&gCpuArch);
    ASSERT_EFI_ERROR(Status);

    // Find the AMI USB protocol.
    Status = gBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, (VOID**)&gAmiUsbController);
    ASSERT_EFI_ERROR(Status);

    gUsbData = gAmiUsbController->USBDataPtr;
    
    gParameters = gUsbData->UsbDataList->UsbUrp;
    gUsbDataList = gUsbData->UsbDataList;
    gHcTable = gUsbDataList->HcTable;

    gUrpBuffer = (URP_STRUC*) 0xFFFFFFFF;
    Status = gBS->AllocatePages(
                 AllocateMaxAddress,
                 EfiRuntimeServicesData,
                 EFI_SIZE_TO_PAGES(sizeof(URP_STRUC) * 8),
                 (EFI_PHYSICAL_ADDRESS*)&gUrpBuffer);
    ASSERT_EFI_ERROR(Status);
    
    // Find the Legacy Bios Protocol
    Status = gBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, 0, (VOID**)&gLegacyBios);
    if (!EFI_ERROR(Status)) {
         gLegacyBiosInstall = TRUE;
    } else {
        Status = gBS->CreateEvent(
                        EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK, 
                        CsmReadyEvent,
                        NULL,
                        &LegacyBiosEvent
                        );
        if (!EFI_ERROR(Status)){
            Status = gBS->RegisterProtocolNotify(
                            &gEfiLegacyBiosProtocolGuid,
                            LegacyBiosEvent,
                            &LegacyBiosReg
                            );
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
    }
    // A event for init USB legacy isr.
    Status = EfiCreateEventReadyToBootEx(
                 TPL_CALLBACK, UsbIsrReadyToBoot,
                 NULL, &ReadyToBoot);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Status = gBS->InstallProtocolInterface(
                    &ImageHandle,
                    &gAmiUsbIsrProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gAmiUsbIsrProtocol );

    return Status;
}
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************