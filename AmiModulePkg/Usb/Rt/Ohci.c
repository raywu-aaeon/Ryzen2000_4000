//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Ohci.c
    AMI USB OHCI driver source file

**/

#include "AmiUsb.h"
#include "UsbKbd.h"
#include <Library/AmiUsbHcdLib.h>




UINT8   Ohci_FillHCDEntries(HCD_HEADER*);
UINT8   EFIAPI Ohci_Start (HC_STRUC*);
UINT8   EFIAPI Ohci_Stop (HC_STRUC*);
UINT8   EFIAPI Ohci_DisableInterrupts (HC_STRUC*);
UINT8   EFIAPI Ohci_EnableInterrupts (HC_STRUC*);
UINT8   EFIAPI Ohci_ProcessInterrupt(HC_STRUC*);
UINT32  EFIAPI Ohci_GetRootHubStatus (HC_STRUC*, UINT8, BOOLEAN);
UINT8   EFIAPI Ohci_DisableRootHub (HC_STRUC*,UINT8);
UINT8   EFIAPI Ohci_EnableRootHub (HC_STRUC*,UINT8);
UINT16  EFIAPI Ohci_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  EFIAPI Ohci_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  EFIAPI Ohci_InterruptTransfer (HC_STRUC*, DEV_INFO*, UINT8, UINT16, UINT8*, UINT16);
UINT8   EFIAPI Ohci_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EFIAPI Ohci_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EFIAPI Ohci_DisableKeyRepeat (HC_STRUC*);
UINT8   EFIAPI Ohci_EnableKeyRepeat (HC_STRUC*);
UINT8   EFIAPI Ohci_ResetRootHub (HC_STRUC*,UINT8);
UINT8   EFIAPI Ohci_GlobalSuspend (HC_STRUC*); 
UINT8   EFIAPI OhciSmiControl(HC_STRUC*, BOOLEAN);

UINT8   EFIAPI Ohci_EnumeratePorts(HC_STRUC*);
UINT8   Ohci_StartEDSchedule(HC_STRUC*);
UINT8   OhciAddPeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   OhciRemovePeriodicEd (HC_STRUC*, OHCI_ED*);
UINT8   EFIAPI Ohci_RepeatTDCallBack(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   Ohci_ResetHC(HC_STRUC*);
UINT8   Ohci_StopUnsupportedHC(HC_STRUC*);
UINT32  Ohci_ProcessRootHubStatusChange(HC_STRUC*);
UINT8   OhciWaitForTransferComplete(HC_STRUC*, OHCI_ED*, OHCI_TD*,DEV_INFO*);
UINT8   EFIAPI Ohci_ControlTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    Ohci_ProcessTD(HC_STRUC*, OHCI_TD*);
UINT8   EFIAPI Ohci_GeneralTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   EFIAPI Ohci_PollingTDCallback(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
VOID    StopControllerType(UINT8);
UINT8   USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
VOID    Ohci_FreeAllStruc(HC_STRUC* HcStruc);  
BOOLEAN OhciIsHalted(HC_STRUC*);
UINT8   OhciTranslateInterval(UINT8);

UINT8   UsbGetDataToggle(DEV_INFO*,UINT8);
VOID    UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

extern  USB_GLOBAL_DATA     *gUsbData;
extern  BOOLEAN gCheckUsbApiParameter;

extern  void        USB_InitFrameList (HC_STRUC*, UINT32);

UINT32  EFIAPI HcReadPciReg(HC_STRUC*, UINT32);
VOID    EFIAPI HcWritePciReg(HC_STRUC*, UINT32, UINT32);
UINT32  EFIAPI HcReadHcMem(HC_STRUC*, UINT32);
VOID    EFIAPI HcWriteHcMem(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcClearHcMem(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcSetHcMem(HC_STRUC*, UINT32, UINT32);
UINT32  EFIAPI HcReadOpReg(HC_STRUC*, UINT32);
VOID    EFIAPI HcWriteOpReg(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcClearOpReg(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcSetOpReg(HC_STRUC*, UINT32, UINT32);
UINT8   EFIAPI HcDmaMap(HC_STRUC*, UINT8, UINT8*, UINT32, UINT8**, VOID**);
UINT8   EFIAPI HcDmaUnmap(HC_STRUC*, VOID*);

extern  void        EFIAPI FixedDelay(UINTN);
extern  void*       USB_MemAlloc (UINT16);
extern  UINT8       EFIAPI USB_InstallCallBackFunction (CALLBACK_FUNC);
extern  DEV_INFO*   EFIAPI USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
extern  UINT8       USB_MemFree(void _FAR_*, UINT16);
extern  UINT8       USB_DisconnectDevice(HC_STRUC*, UINT8, UINT8);  

extern  void        EFIAPI USBKBDPeriodicInterruptHandler(HC_STRUC*);
extern  void        EFIAPI USBKeyRepeat(HC_STRUC*, UINT8);


extern  USB_DATA_LIST   *gUsbDataList;
extern HC_STRUC        **gHcTable;

/**
    This function fills the host controller driver
    routine pointers

    @param HcdHeader     Pointer to the host controller header structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
Ohci_FillHCDEntries(
    HCD_HEADER *HcdHeader
)
{
    //
    // Fill the routines here
    //
    HcdHeader->FnHcdStart                = Ohci_Start;
    HcdHeader->FnHcdStop                 = Ohci_Stop;
    HcdHeader->FnHcdEnumeratePorts       = Ohci_EnumeratePorts;
    HcdHeader->FnHcdDisableInterrupts    = Ohci_DisableInterrupts;
    HcdHeader->FnHcdEnableInterrupts     = Ohci_EnableInterrupts;
    HcdHeader->FnHcdProcessInterrupt     = Ohci_ProcessInterrupt;
    HcdHeader->FnHcdGetRootHubStatus     = Ohci_GetRootHubStatus;
    HcdHeader->FnHcdDisableRootHub       = Ohci_DisableRootHub;
    HcdHeader->FnHcdEnableRootHub        = Ohci_EnableRootHub;
    HcdHeader->FnHcdControlTransfer      = Ohci_ControlTransfer;
    HcdHeader->FnHcdBulkTransfer         = Ohci_BulkTransfer;
    HcdHeader->FnHcdIsocTransfer         = UsbHcdIsocTransferDummy;
    HcdHeader->FnHcdInterruptTransfer    = Ohci_InterruptTransfer;
    HcdHeader->FnHcdDeactivatePolling    = Ohci_DeactivatePolling;
    HcdHeader->FnHcdActivatePolling      = Ohci_ActivatePolling;
    HcdHeader->FnHcdDisableKeyRepeat     = Ohci_DisableKeyRepeat;
    HcdHeader->FnHcdEnableKeyRepeat      = Ohci_EnableKeyRepeat;
    HcdHeader->FnHcdEnableEndpoints      = UsbHcdEnableEndpointsDummy;
    HcdHeader->FnHcdInitDeviceData       = UsbHcdInitDeviceDataDummy;
    HcdHeader->FnHcdDeinitDeviceData     = UsbHcdDeinitDeviceDataDummy;
    HcdHeader->FnHcdResetRootHub         = Ohci_ResetRootHub;
    HcdHeader->FnHcdClearEndpointState   = UsbHcdClearEndpointStateDummy;
    HcdHeader->FnHcdGlobalSuspend        = Ohci_GlobalSuspend; 
    HcdHeader->FnHcdSmiControl           = OhciSmiControl;

    USB_InstallCallBackFunction(Ohci_ControlTDCallback);
    USB_InstallCallBackFunction(Ohci_GeneralTDCallback);
    USB_InstallCallBackFunction(Ohci_PollingTDCallback);
    USB_InstallCallBackFunction(Ohci_RepeatTDCallBack);

    return  USB_SUCCESS;
}


/**
    This API function is called to start a OHCI host controller.
    The input to the routine is the pointer to the HC structure
    that defines this host controller

    @param HcStruc   Pointer to the host controller structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure


**/

UINT8
EFIAPI
Ohci_Start(
    HC_STRUC*   HcStruc
)
{
//    UINT32          OhciControlReg = 0;
    UINT32          BaseAddr;
    UINT32          HcFmInterval;
    EFI_STATUS      Status;
    UINT32          UsbHcClassCode;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    // The address offset of class code register is in 09-0Bh, we get the value
    // from offset 08h for alignment and shift right 8 bits.
    UsbHcClassCode = HcReadPciReg(HcStruc, USB_REG_REVISION_ID);  
    UsbHcClassCode = UsbHcClassCode >> 8;

    if (UsbHcClassCode != OHCI_CLASS_CODE) {
        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "OHCI HC Class Code is wrong: %x\n", UsbHcClassCode);
        return USB_ERROR;
    }

    HcStruc->AsyncListSize = OHCI_FRAME_LIST_SIZE;
    HcStruc->MaxBulkDataSize = MAX_OHCI_BULK_DATA_SIZE;

    //
    // Get memory base address of the HC and store it in the HCStruc
    //
    BaseAddr = HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS);
    BaseAddr &= 0xFFFFFFF0;    // Mask lower bits
    

    Status = AmiUsbValidateMmioBuffer((VOID*)(UINTN)BaseAddr, HcStruc->BaseAddressSize);
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Usb Mmio address is invalid, it is in SMRAM\n");
        return USB_ERROR;
    }
    Status = AmiUsbValidateMemoryBuffer((VOID*)HcStruc->FrameList, 0x100);
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
        return USB_ERROR;
    }

    
    HcStruc->BaseAddress = BaseAddr;

    //
    // Get the number of ports supported by the host controller (Offset 48h)
    //
    HcStruc->NumPorts = (UINT8)HcReadHcMem(HcStruc, OHCI_RH_DESCRIPTOR_A);

    USB_InitFrameList(HcStruc, 0);

    //
    // Enable the ED schedules
    //
    if (Ohci_StartEDSchedule(HcStruc) == USB_ERROR) {
        return USB_ERROR;
    }

    //
    // First stop the host controller if it is at all active
    //
    if (Ohci_DisableInterrupts(HcStruc) == USB_ERROR) {
        return USB_ERROR;
    }

    // Save the contents of the HcFmInterval register
    HcFmInterval = HcReadHcMem(HcStruc, OHCI_FRAME_INTERVAL);
    HcFmInterval &= 0x3FFF;
    if (HcFmInterval != 0x2EDF) {
      USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "OHCI: HcFmInterval %x\n", HcFmInterval);
    }
    HcFmInterval |= (((6 * (HcFmInterval - 210)) / 7) & 0x7FFF) << 16;

    // Issue a controller reset
    if (Ohci_ResetHC(HcStruc) != USB_SUCCESS) {
      return USB_ERROR;
    }
  
    // Restore the value of the HcFmInterval register
    HcWriteHcMem(HcStruc, OHCI_FRAME_INTERVAL, HcFmInterval);

    //
    // Program the frame list base address register
    //
    HcWriteHcMem(HcStruc, OHCI_HCCA_REG, (UINT32)(UINTN)HcStruc->FrameList);

    //
    // Set the periodic start time = 2A27h (10% off from HcFmInterval-2EDFh)
    //
    HcWriteHcMem(HcStruc, OHCI_PERIODIC_START, (((HcFmInterval & 0x3FFF) * 9) / 10) & 0x3FFF);

    //
    // Start the host controller for periodic list and control list.
    //
    OhciEnableControlReg(HcStruc);
    //
    // Enable interrupts from the host controller, enable SOF, WDH, RHSC interrupts
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE,
        MASTER_INTERRUPT_ENABLE | WRITEBACK_DONEHEAD_ENABLE |
        RH_STATUS_CHANGE_ENABLE | OWNERSHIP_CHANGE_ENABLE);

    //
    // Set the HC state to running
    //
    HcStruc->HcFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->UsbStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->UsbStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

    return  USB_SUCCESS;
}


/**
    This API function is called to stop the OHCI controller.
    The input to the routine is the pointer to the HC structure
    that defines this host controller.


    @param HcStruc   Pointer to the host controller structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_Stop(
    HC_STRUC* HcStruc
)
{
    UINT8 Port;
    EFI_STATUS  Status;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }


    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    for (Port = 1; Port <= HcStruc->NumPorts; Port++) {
        USB_DisconnectDevice(HcStruc, (UINT8)(HcStruc->HcNumber | BIT7), Port); 
    }

    //
    // Reset Host Controller
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, USBRESET);
    FixedDelay(gUsbDataList->UsbTimingPolicy->OhciHcResetDelay * 1000);   // Wait 10ms for assertion of reset

    //
    // Disable interrupts
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, 0xffffffff);

    //
    // Disable OHCI KBC Emulation
    //
    HcWriteHcMem(HcStruc, OHCI_HCE_CONTROL, 0);

    USB_InitFrameList(HcStruc, 0);
    Ohci_FreeAllStruc(HcStruc);  

    USBKeyRepeat(HcStruc, 3);

    HcStruc->HcFlag &= ~HC_STATE_RUNNING;

    CheckBiosOwnedHc();

    return USB_SUCCESS;
}


/**
    This function is called when TdRepeat/TD32ms completes
    a transaction.  This TD runs a dummy interrupt transaction
    to a non-existant device address for the purpose of
    generating a periodic timeout interrupt which in turn
    is used to generate keyboard repeat or update LED status.

    @param HcStruc     Pointer to the HCStruc structure
    @param DevInfo     NULL (DevInfo is not valid)
    @param Td          Pointer to the TD that completed
    @param Buffer      Not used
    @param DataLength  Data length

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_RepeatTDCallBack(
    HC_STRUC  *HcStruc,
    DEV_INFO  *DevInfo,
    UINT8    *Td,
    UINT8    *Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS  *DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;
    UINT8           *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs->TDRepeat < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->TDRepeat + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    DescPtrs->TDRepeat->ActiveFlag = FALSE;


    if ((gUsbData->UsbDevSupport & USB_KB_DEV_SUPPORT) == USB_KB_DEV_SUPPORT)
        USBKBDPeriodicInterruptHandler(HcStruc);


    if (((UINTN)DescPtrs->EDRepeat < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->EDRepeat + sizeof(OHCI_ED)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

  if (!(DescPtrs->EDRepeat->Control & ED_SKIP_TDQ)) {
      //
      // Rebind the TD to its parent ED
      //
      DescPtrs->EDRepeat->HeadPointer = (UINT32)(UINTN)DescPtrs->TDRepeat;

      //
      // Clear the link pointer. It may point to some other TD
      //
      DescPtrs->TDRepeat->LinkPointer = OHCI_TERMINATE;

      //
      // Reactivate the TD
      //
      DescPtrs->TDRepeat->ControlStatus = DescPtrs->TDRepeat->CSReloadValue;
      DescPtrs->TDRepeat->ActiveFlag = TRUE;
   }

    return USB_SUCCESS;
}


/**
    This API function is called to disable the interrupts
    generated by the OHCI host controller. The input to the
    routine is the pointer to the HC structure that defines this
    host controller.  This routine will stop the HC to avoid
    further interrupts.

     @param HcStruc     Pointer to the HCStruc structure

     @retval USB_SUCCESS    Success
     @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_DisableInterrupts(
    HC_STRUC* HcStruc
)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Disable interrupt generation (global) bit (Set bit31)
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, MASTER_INTERRUPT_ENABLE);
    //
    // Disable periodic, isochronous, control and bulk list processing, reset bits 2 to 5
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, BIT2 + BIT3 + BIT4 + BIT5);

    return USB_SUCCESS;
}


/**
    This function enables the HC interrupts

    @param HcStruc     Pointer to the HCStruc structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_EnableInterrupts(
    HC_STRUC* HcStruc
)
{
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Enable periodic, control and bulk list processing
    // Set bit 2, 4 & 5
    //
    HcSetHcMem(HcStruc, OHCI_CONTROL_REG, BIT2 + BIT4 + BIT5);
    //
    // Enable interrupt generation (global) bit
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    return  USB_SUCCESS;
}


/**
    This function is called when the USB interrupt bit is
    set. This function will parse through the TDs and QHs to
    find out completed TDs and call their respective call
    back functions

    @param  HcStruc      Pointer to the HCStruc structure

    @retval USB_ERROR    Interrupt not processed
    @retval USB_SUCCESS  Interrupt processed

**/

UINT8
EFIAPI
Ohci_ProcessInterrupt(
    HC_STRUC* HcStruc
)
{
    OHCI_TD *Td;
    OHCI_TD *NextTd;
    UINT8 IntProcessFlag = USB_ERROR;  // Set as interrupt not processed
    EFI_STATUS  Status;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    // Make sure MEMIO & Bus mastering are enabled
    if (((UINT8)HcReadPciReg(HcStruc, USB_REG_COMMAND) & 0x6) != 0x6) {
        return IntProcessFlag;
    }

    if ((HcReadPciReg(HcStruc, USB_MEM_BASE_ADDRESS) & ~(0x7F)) != 
        (UINT32)HcStruc->BaseAddress) {
        return IntProcessFlag;
    }
    //
    // Check the interrupt status register for an ownership change.  If this bit
    // is set, it means that the O/S USB device driver is attempting to takeover
    // control of the host controller. In this case the host controller is
    // shut down and the interrupt routing bit in the control register is cleared
    // (this disables SMI generation and enebles standard IRQ generation from
    // the USB host controller.
    //
    if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & OWNERSHIP_CHANGE) {
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, OWNERSHIP_CHANGE);
        if (HcReadHcMem(HcStruc, OHCI_HCCA_REG) == (UINT32)(UINTN)HcStruc->FrameList) {
            //
            // OS tries to take the control over HC
            //
            gUsbData->UsbStateFlag &= (~USB_FLAG_ENABLE_BEEP_MESSAGE);

            Ohci_StopUnsupportedHC(HcStruc);

            Ohci_Stop(HcStruc);
            return USB_SUCCESS; // Set interrupt as processed
        } else {    // Ownership comes back to the driver - reinit
            gUsbData->HandOverInProgress = FALSE;
            gUsbData->UsbStateFlag  |= (USB_FLAG_ENABLE_BEEP_MESSAGE);
            Ohci_Start(HcStruc);
            return USB_SUCCESS; // Set interrupt as processed
        }
    }   // ownership change

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
        // Clear All bits of the interrupt status
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, 
            HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS));
        return IntProcessFlag;
    }
    //
    // Check whether the controller is still under BIOS control
    // Read the base address of the Periodic Frame List to the OHCI HCCA
    // register and compare with stored value
    //
    if ((HcReadHcMem(HcStruc, OHCI_HCCA_REG) & 0xFFFFFF00) !=
            (UINT32)(UINTN)HcStruc->FrameList) {
        return IntProcessFlag;
    }
    //
    // Check the interrupt status register for a root hub status change.  If
    // this bit is set, then a device has been attached or removed from one of
    // the ports on the root hub.
    //
    if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & RH_STATUS_CHANGE) {
        //
        // Stop the periodic list processing to avoid more interrupts from HC
        //
        HcClearHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
//        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "before Ohci_ProcessRootHubStatusChange\n");
        // Handle root hub change
        IntProcessFlag = (UINT8)Ohci_ProcessRootHubStatusChange(HcStruc);
        if(IntProcessFlag != USB_SUCCESS){
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Ohci_ProcessRootHubStatusChange error!\n");
        }
//        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "after Ohci_ProcessRootHubStatusChange\n");
        //
        // Re-enable the periodic list processing
        //
        HcSetHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);
    }
    //
    // Check the interrupt status register for a one or more TDs completing.
    //
    if (!(HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & WRITEBACK_DONEHEAD)) {
        return USB_SUCCESS;
    }

    //
    // The memory dword at HCCADONEHEAD has been updated to contain the head
    // pointer of the linked list of TDs that have completed.  Walk through
    // this list processing TDs as we go.
    //
    for (;;) {
        Td = (OHCI_TD*)(UINTN)(((OHCI_HCCA_PTRS*)HcStruc->FrameList)->HccaDoneHead);
        ((OHCI_HCCA_PTRS*)HcStruc->FrameList)->HccaDoneHead = 0;

        //
        // Clear the WRITEBACK_DONEHEAD bit of the interrupt status register
        // in the host controller
        //
        HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, WRITEBACK_DONEHEAD);

        if (!Td) {
            break;   // no TDs in the list
        }

        do {
            Td = (OHCI_TD*)((UINTN)Td & 0xfffffff0);

            Status = AmiUsbValidateMemoryBuffer((VOID*)Td, sizeof(OHCI_TD));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) {
                return USB_ERROR;
            }

            NextTd = (OHCI_TD*)(UINTN)Td->LinkPointer;
            Ohci_ProcessTD(HcStruc, Td);
            // Host controllers might change NextTD pointer to Td, then it causes
            // infinite loop in this routing. Break this loop if NextTd is the same as Td.
            if (Td == NextTd) {
                break;
            }
            Td = NextTd;
        } while (Td);
    }   // Check if any TDs completed while processing

    return USB_SUCCESS;
}


/**
    This function returns the port connect status for the
    root hub port

    @param HcStruc          Pointer to the HCStruc structure
    @param PortNum          Port in the HC whose status is requested
    @param ClearChangeBits  TRUE: Clear change status bits
    @retval RhStatus        the port connect status for the root hub port
**/

UINT32
EFIAPI
Ohci_GetRootHubStatus(
    HC_STRUC*   HcStruc, 
    UINT8       PortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT32  RhStatus = USB_PORT_STAT_DEV_OWNER;
    UINT32  PortStatus;
    UINT16  PortReg = ((UINT16)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
    PortStatus = HcReadHcMem(HcStruc, PortReg);
    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Ohci port[%d] status: %08x\n", PortNum, PortStatus);

    if (PortStatus & CURRENT_CONNECT_STATUS) {
        RhStatus |= USB_PORT_STAT_DEV_CONNECTED;
        if (PortStatus & PORT_ENABLE_STATUS) {
          RhStatus |= USB_PORT_STAT_DEV_ENABLED;
        }
    }

    RhStatus |= USB_PORT_STAT_DEV_FULLSPEED;   // Assume full speed and set the flag
    if (PortStatus & LOW_SPEED_DEVICE_ATTACHED) {
        RhStatus &= ~USB_PORT_STAT_DEV_FULLSPEED;  // Reset full speed
        RhStatus |= USB_PORT_STAT_DEV_LOWSPEED;    // Set low speed flag
    }

    if (PortStatus & CONNECT_STATUS_CHANGE) {
        if (ClearChangeBits == TRUE) {
            HcWriteHcMem(HcStruc, PortReg, CONNECT_STATUS_CHANGE);
        }
        RhStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED; // Set connect status change flag
    }

  if (PortStatus & PORT_ENABLE_STATUS_CHANGE) {
      RhStatus |= USB_PORT_STAT_DEV_ENABLE_CHANGED;
      if (ClearChangeBits == TRUE) {
          HcWriteHcMem(HcStruc, PortReg, PORT_ENABLE_STATUS_CHANGE);
      }
  }

    if (PortStatus & PORT_SUSPEND_STATUS) {
        RhStatus |= USB_PORT_STAT_DEV_SUSPEND;
    }
    if (PortStatus & PORT_OVERCURRENT) {
        RhStatus |= USB_PORT_STAT_DEV_OVERCURRENT;
    }
    if (PortStatus & PORT_RESET_STATUS) {
        RhStatus |= USB_PORT_STAT_DEV_RESET;
    }
    if (PortStatus & PORT_POWER_STATUS) {
        RhStatus |= USB_PORT_STAT_DEV_POWER;
    }
    if (PortStatus & PORT_SUSPEND_STATUS_CHANGE) {
        RhStatus |= USB_PORT_STAT_DEV_SUSPEND_CHANGED;
    }
    if (PortStatus & PORT_OVERCURRENT_CHANGE) {
        RhStatus |= USB_PORT_STAT_DEV_OVERCURRENT_CHANGED;
    }
    if (PortStatus & PORT_RESET_STATUS_CHANGE) {
        RhStatus |= USB_PORT_STAT_DEV_RESET_CHANGED;
    }
    return RhStatus;
}


/**
    This function disables the specified root hub port.

    @param HcStruc          Pointer to the HCStruc structure
    @param PortNum          Port in the HC whose status is requested

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_DisableRootHub(
    HC_STRUC*   HcStruc,
    UINT8       PortNum
)
{
    UINT32 PortReg = ((UINT32)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
    HcWriteHcMem(HcStruc, (UINT16)PortReg, CLEAR_PORT_ENABLE);
    
    return USB_SUCCESS;
}


/**
    This function enables the specified root hub port.

    @param HcStruc          Pointer to the HCStruc structure
    @param PortNum          Port in the HC whose status is requested

    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure

**/

UINT8
EFIAPI
Ohci_EnableRootHub(
    HC_STRUC    *HcStruc,
    UINT8       PortNum
)
{
    return  USB_SUCCESS;
}

/**
    This function resets the specified root hub port.

    @param HcStruc          Pointer to the HCStruc structure
    @param PortNum          Port in the HC whose status is requested

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_ResetRootHub (
    HC_STRUC*   HcStruc, 
    UINT8       PortNum
)
{
    UINT16  PortReg = ((UINT16)PortNum << 2) + (OHCI_RH_PORT1_STATUS - 4);
    UINT32  Index;
    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
  
    HcWriteHcMem(HcStruc, PortReg, SET_PORT_RESET);    // Reset the port

    // The reset signaling must be driven for a minimum of 10ms
    FixedDelay(10 * 1000);

    //
    // Wait for reset to complete
    //
    for (Index = 0; Index < 500; Index++) {
    if (HcReadHcMem(HcStruc, PortReg) & PORT_RESET_STATUS_CHANGE) {
      break;
    }
        FixedDelay(100);       // 100 us delay
    }

    if (!(HcReadHcMem(HcStruc, PortReg) & PORT_RESET_STATUS_CHANGE)) {
      USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "OHCI: port reset timeout, status: %08x\n", 
      HcReadHcMem(HcStruc, PortReg));
      return USB_ERROR;
  }

    //
    // Clear the reset status change status
    //
    HcWriteHcMem(HcStruc, PortReg, PORT_RESET_STATUS_CHANGE);

    // Some devices need a delay here
    FixedDelay(3 * 1000);  // 3 ms delay

    return  USB_SUCCESS;
}


/**
    This function suspend the OHCI HC.

    @param HcStruc          Pointer to the HCStruc structure
    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure
**/
UINT8
EFIAPI
Ohci_GlobalSuspend(
    HC_STRUC*  HcStruc
)
{
    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }
    
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, RESUME_DETECTED_ENABLE);
    
    FixedDelay(40 * 1000);
    
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, USBSUSPEND | REMOTE_WAKEUP_ENABLE);
    
    FixedDelay(20 * 1000);

    HcStruc->HcFlag &= ~(HC_STATE_RUNNING);
    HcStruc->HcFlag |= HC_STATE_SUSPEND;

    return  USB_SUCCESS;
}

/**
    Set Ohci SMI Control

    @param HcStruc          Pointer to the HCStruc structure
    @param Enable           TRUE : Enable
    
    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure
**/
UINT8
EFIAPI
OhciSmiControl(
    HC_STRUC* HcStruc,
    BOOLEAN Enable
)
{
    EFI_STATUS EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }
    
    if (HcStruc->HwSmiHandle == NULL) {
        return USB_SUCCESS;
    }
 
    if (Enable == TRUE) {
        HcSetHcMem(HcStruc, OHCI_CONTROL_REG, INTERRUPT_ROUTING);
    } else {
        HcClearHcMem(HcStruc, OHCI_CONTROL_REG, INTERRUPT_ROUTING);   
    }
    
    return USB_SUCCESS;
}

/**
    This function executes a device request command transaction
    on the USB. One setup packet is generated containing the
    device request parameters supplied by the caller.  The setup
    packet may be followed by data in or data out packets
    containing data sent from the host to the device
    or vice-versa. This function will not return until the
    request either completes successfully or completes in error
    (due to time out, etc.)

    @param HcStruc   Pointer to HCStruc of the host controller
    @param DevInfo    DeviceInfo structure (if available else 0)
    @param Request    Request type (low byte)
                      Bit 7   : Data direction
                                0 = Host sending data to device
                                1 = Device sending data to host
                      Bit 6-5 : Type
                                00 = Standard USB request
                                01 = Class specific
                                10 = Vendor specific
                                11 = Reserved
                      Bit 4-0 : Recipient
                                00000 = Device
                                00001 = Interface
                                00010 = Endpoint
                                00100 - 11111 = Reserved
                      Request code, a one byte code describing
                      the actual device request to be executed
                      (ex: Get Configuration, Set Address etc)
    @param Index      wIndex request parameter (meaning varies)
    @param Value      wValue request parameter (meaning varies)
    @param Buffer     Buffer containing data to be sent to the
                      device or buffer to be used to receive data
    @param Length     wLength request parameter, number of bytes
                      of data to be transferred in or out
                      of the host controller


    @retval Data      Number of bytes transferred


    @note  Do not use USB_SUCCESS or USB_ERROR as returned values

**/

UINT16
EFIAPI
Ohci_ControlTransfer (
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
)
{
    UINT16  *SetupData;
    OHCI_DESC_PTRS *DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;
    OHCI_ED *Ed;
    OHCI_TD *Td;
    UINT32  Packet;
    UINT16  Data;
    UINT8   CompletionCode;
    UINT32  TransferLength;
    UINT8   *BufPhyAddr = NULL;
    VOID    *BufferMapping = NULL;
    UINT8   *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));
    EFI_STATUS  Status;
    
    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return 0;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return 0;
    }


    if (gCheckUsbApiParameter) {
        if (Length != 0) {
            Status = AmiUsbValidateMemoryBuffer((VOID*)Buffer, Length);
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
                USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Ohci ControlTransfer Invalid Pointer, Buffer is in SMRAM.\n");
                return 0;
            }
        }
        gCheckUsbApiParameter = FALSE;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }

    if (OhciIsHalted(HcStruc)) {
      return 0;
    }
    //FixedDelay(5 * 1000);    // 5 ms delay is necessary for OHCI host controllers

    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return 0;
    }
    if (((UINTN)DescPtrs->EDControl < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->EDControl + sizeof(OHCI_ED)) > (UINTN)MemBlockEnd)) {
        return 0;
    }
    if (((UINTN)DescPtrs->TDControlSetup < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->TDControlSetup + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
        return 0;
    }
    if (((UINTN)DescPtrs->TDControlData < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->TDControlData + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
        return 0;
    }
    if (((UINTN)DescPtrs->TDControlStatus < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->TDControlStatus + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
        return 0;
    }
    DevInfo->UsbLastCommandStatusExtended = 0;

    //
    // Build the device request in the data area of the control setup qTD
    //
    SetupData = (UINT16*)DescPtrs->TDControlSetup->SetupData;
    *SetupData++ = Request;
    *SetupData++ = Value;
    *SetupData++ = Index;
    *SetupData++ = Length;
    //*(UINTN*)Data = (UINTN)BufPhyAddr;
    //
    // Prepare some registers that will be used in building the TDs below.
    // wLength  contains the data length.
    // FpBuffer contains the absolute address of the data buffer.
    // wRequest contains the request type (bit 7 = 0/1 for Out/In).
    // FpDevInfo will contain a pointer to the DeviceInfo structure for the given device.
    //
    // Ready the EDControl for the control transfer.
    //
    Ed = DescPtrs->EDControl;
    //
    // The ED control field will be set so
    //   Function address & Endpoint number = ESI,
    //   Direction = From TD,
    //   Speed = DeviceInfo.EndpointSpeed,
    //   Skip = 1, Format = 0,
    //   Max packet size  = DeviceInfo.Endp0MaxPacket
    // The HeadPointer field will be set to TDControlSetup
    // The TailPointer field will be set to OHCI_TERMINATE
    // The LinkPointer field will be set to OHCI_TERMINATE
    //
    Packet = (UINT32)DevInfo->Endp0MaxPacket;
    if (Packet > 0x40) Packet = 0x40; // Force the max packet size to 64 bytes
    Packet <<= 16;                   // dData[26:16] = device's packet size
    Data = (UINT16)DevInfo->EndpointSpeed;  // 00/01/10 for HI/LO/FULL
    Data = (Data & 1) << 13;      // wData[13] = full/low speed flag
    Data |= DevInfo->DeviceAddress | ED_SKIP_TDQ;
    Ed->Control = Packet | Data;
    Ed->TailPointer = 0;
    Ed->EDLinkPointer = 0;

    Td = DescPtrs->TDControlSetup;
    //
    // The ControlStatus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_SETUP_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_SETUP_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to the TD's SetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The BufferEnd field will point to the last byte of the TD's SetupData
    //   buffer.
    // The LinkPointer field will point to the TDControlData if data will
    //   be sent/received or to the TDControlStatus if no data is expected.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the Ohci_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EDControl.
    //
    Td->ControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_SETUP_PACKET | GTD_SETUP_TOGGLE |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));

    Td->CurrentBufferPointer = (UINT32)(UINTN)Td->SetupData;
    Td->BufferEnd = (UINT32)(UINTN)Td->SetupData + 7; // size of aSetupData - 1

    Data = Length ;                   //(EIP67230)

    if (Length) {  // some data to transfer
        Td = DescPtrs->TDControlData;     // Fill in various fields in the TDControlData.
        //
        // The ControlStatus field will be set so
        //   Buffer Rounding = 1,
        //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
        //   Delay Interrupt = GTD_IntD,
        //   Data Toggle = GTD_DATA1_TOGGLE,
        //   Error Count = GTD_NO_ERRORS,
        //   Condition Code = GTD_NOT_ACCESSED
        // The CurrentBufferPointer field will point to the caller's buffer
        //   which is now in EBP.
        // The BufferEnd field will point to the last byte of the caller's buffer.
        // The LinkPointer field will point to the TDControlStatus.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the Ohci_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.
        // The DeviceAddress field does not need to be set since the Control TDs do
        //   not need rebinding to the EDControl.
        // The CSReloadValue field will contain 0 because this is a "one shot" packet.
        // The pCallback will be set to point to the Ohci_ControlTDCallback routine.
        // The ActiveFlag field will be set to TRUE.    return  USB_SUCCESS;
        // The DeviceAddress field does not need to be set since the Control TDs do}
        //   not need rebinding to the EDControl.
        //
        HcDmaMap(HcStruc, (UINT8)(Request & BIT7), Buffer, Length, 
                &BufPhyAddr, &BufferMapping);
        Packet = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
        Packet = (Request & BIT7)? (Packet | GTD_IN_PACKET | GTD_IntD) : (Packet | GTD_OUT_PACKET);
        Td->ControlStatus = Packet;
        Td->CurrentBufferPointer = (UINT32)(UINTN)BufPhyAddr;
        Td->BufferEnd = (UINT32)((UINTN)Buffer + Data - 1);
    }
    Td = DescPtrs->TDControlStatus;   // Fill in various fields in the TDControlStatus.
    //
    // The ControlStaus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
    //   Delay Interrupt = GTD_IntD,
    //   Data Toggle = GTD_DATA1_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to NULL
    // The BufferEnd field will point to NULL.
    // The LinkPointer field will point to OHCI_TERMINATE.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the Ohci_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs do
    //   not need rebinding to the EdControl.
    //
    // Note: For OUT control transfer status should be IN and
    //       for IN cotrol transfer, status should be OUT.
    //
    Packet = (UINT32)(GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
    Packet = (Request & BIT7)? (Packet | GTD_OUT_PACKET) : (Packet | GTD_IN_PACKET | GTD_IntD);
    Td->ControlStatus = Packet;
    Td->CurrentBufferPointer = 0;
    Td->BufferEnd = 0;
    Td->LinkPointer = 0;
    //
    // Link all the pointers together
    //
    Td = DescPtrs->TDControlSetup;
    Ed->HeadPointer = (UINT32)(UINTN)Td;
    if (Length) {  // chain in data TD
        Td->LinkPointer = (UINT32)(UINTN)DescPtrs->TDControlData;
        Td = DescPtrs->TDControlData;
    }
    Td->LinkPointer = (UINT32)(UINTN)DescPtrs->TDControlStatus;

    DescPtrs->TDControlStatus->LinkPointer = 0;

    Td = DescPtrs->TDControlSetup;
    do {
        Td->CSReloadValue = 0;
        Td->CallBackIndex = USB_InstallCallBackFunction(Ohci_ControlTDCallback);
        Td->ActiveFlag = TRUE;
        Td = (OHCI_TD*)(UINTN)Td->LinkPointer;
    } while (Td);
    //
    // Now control queue is complete, so set ED_SKIP_TDQ=0
    //
    Ed->Control &= ~ED_SKIP_TDQ;
    //
    // Set the HcControlHeadED register to point to the EDControl.
    //
    HcWriteHcMem(HcStruc, OHCI_CONTROL_HEAD_ED, (UINT32)(UINTN)Ed);
    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the ControllListFilled field of HcCommandStatus reg.
    // This will cause the HC to execute the transaction in the next active frame.
    //
    HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, CONTROL_LIST_FILLED);
    //
    // Now wait for the control status TD to complete.  When it has completed,
    // the Ohci_ControlTDCallback will set its active flag to FALSE.
    //
    OhciWaitForTransferComplete(HcStruc, Ed, DescPtrs->TDControlStatus, DevInfo);
    //
    // Stop the HC from processing the EDControl by setting its Skip bit.
    //
    Ed->Control |= ED_SKIP_TDQ;

    //
    // Finally check for any error bits set in both the TDControlStatus.
    // If the TD did not complete successfully, return STC.
    //
    CompletionCode = (UINT8)(DescPtrs->TDControlStatus->ControlStatus >> 28);    // dData[3:0] = Completion status
    gUsbData->UsbLastCommandStatus &= ~USB_CONTROL_STALLED;

    Td = DescPtrs->TDControlData;
    TransferLength = Length ; 
    if( Td->CurrentBufferPointer != 0){
        TransferLength = Td->CurrentBufferPointer - (UINT32)(UINTN)Buffer;
    }


    Data = 0;
    switch (CompletionCode) {
        case GTD_NO_ERROR:
            Data = (UINT16)TransferLength;
            break;
        case GTD_STALL:
            gUsbData->UsbLastCommandStatus |= USB_CONTROL_STALLED;
            DevInfo->UsbLastCommandStatusExtended |= USB_TRSFR_STALLED;
            break;
        case GTD_NOT_ACCESSED:
            DevInfo->UsbLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
            break;
        default:
            break;
  }
    
    if (Length) {
        HcDmaUnmap(HcStruc, BufferMapping);
    }

    return Data;
}


/**
    This function executes a bulk transaction on the USB. The
    transfer may be either DATA_IN or DATA_OUT packets containing
    data sent from the host to the device or vice-versa. This
    function wil not return until the request either completes
    successfully or completes with error (due to time out, etc.)
    Size of data can be upto 64K

    @param HcStruc    Pointer to HCStruc of the host controller
    @param DevInfo    DeviceInfo structure (if available else 0)
    @param XferDir    Transfer direction
                      Bit 7: Data direction
                             0 Host sending data to device
                             1 Device sending data to host
                      Bit 6-0 : Reserved
    @param Buffer     Buffer containing data to be sent to the
                      device or buffer to be used to receive data
                      value in Segment:Offset format
    @param Length     dwLength request parameter, number of bytes
                      of data to be transferred in or out
                      of the host controller

    @retval BytesTransferred  Amount of data transferred

**/

UINT32
EFIAPI
Ohci_BulkTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length
)
{
    UINT32      Data;
    UINT8       ControlStatus;
    OHCI_DESC_PTRS *DescPtrs;
    UINT16      MaxPkt;
    UINT8       Endp;
    UINT8       DatToggle;
    UINT32      BytesToTransfer;
    UINT32      BytesRemaining;
    UINT32      BytesTransferred;
    UINT32      Tmp;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
    EFI_STATUS  Status;
    UINT8       *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return 0;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return 0;
    }


    if (gCheckUsbApiParameter) {
        Status = AmiUsbValidateMemoryBuffer((VOID*)Buffer, Length);
        if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Ohci BulkTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }


    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }

    if (OhciIsHalted(HcStruc)) {
      return 0;
    }
    
    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

    DevInfo->UsbLastCommandStatusExtended = 0;

    DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;
    
    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return 0;
    }

    if (((UINTN)DescPtrs->EDBulk < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->EDBulk + sizeof(OHCI_ED)) > (UINTN)MemBlockEnd)) {
        return 0;
    } 

    if (((UINTN)DescPtrs->TDBulkData < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->TDBulkData + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
        return 0;
    } 
    
    MaxPkt = (XferDir & 0x80)? DevInfo->BulkInMaxPkt : DevInfo->BulkOutMaxPkt;
    Endp = (XferDir & 0x80)? DevInfo->BulkInEndpoint : DevInfo->BulkOutEndpoint;
    DatToggle = UsbGetDataToggle(DevInfo, Endp | XferDir);

    if (MaxPkt == 0) {
        return 0;
    }

    BytesRemaining = Length;
    BytesTransferred = 0;
    BytesToTransfer = 0;

    HcDmaMap(HcStruc, XferDir, Buffer, Length, &BufPhyAddr, &BufferMapping);

    for (;BytesRemaining != 0; BytesRemaining -= BytesToTransfer) {
        BytesToTransfer = (BytesRemaining < gUsbData->FullSpeedMaxBulkDataSizePerFrame)?
                           BytesRemaining : gUsbData->FullSpeedMaxBulkDataSizePerFrame;

        Tmp = (UINT32)(UINTN)BufPhyAddr + BytesTransferred;

        //
        //  Set the SKIP bit in the EdBulk to avoid accidental scheduling
        //
        DescPtrs->EDBulk->Control = ED_SKIP_TDQ;
        //
        // Set the ED's head pointer field to bulk data TD and tail pointer field to
        // OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
        //
        DescPtrs->EDBulk->HeadPointer = (UINT32)(UINTN)DescPtrs->TDBulkData;
        DescPtrs->EDBulk->TailPointer = OHCI_TERMINATE;
        DescPtrs->EDBulk->EDLinkPointer = OHCI_TERMINATE;
        //
        // Form the data needed for ED's control field with the available information
        //
        Data = (XferDir & 0x80)? ED_IN_PACKET : ED_OUT_PACKET;
        Data |= DevInfo->DeviceAddress;
        Data |= (UINT16)Endp << 7;
        Data |= (UINT32)MaxPkt << 16;
        //
        // Update the ED's control field with the data formed
        // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
        //
        DescPtrs->EDBulk->Control = Data;
        //
        // Fill the general bulk data TD with relevant information.  Set the
        //  TD's control field with buffer rounding set to 1, direction PID to
        //  don't care, delay interrupt to INTD, data toggle to the latest data
        //  toggle value, error count to no errors and condition code to not accessed.
        //
        // Set the data toggle to DATA0 (SETUP_TOGGLE)
        DescPtrs->TDBulkData->ControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET |
            GTD_IntD | GTD_SETUP_TOGGLE | GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
        DescPtrs->TDBulkData->ControlStatus |= (UINT32)DatToggle << 24;
        //
        // GTD current buffer pointer field will point to the caller's buffer which
        // now in the variable FpBuffer
        //
        DescPtrs->TDBulkData->CurrentBufferPointer = Tmp;
        DescPtrs->TDBulkData->BufferEnd = Tmp + BytesToTransfer - 1;
        DescPtrs->TDBulkData->LinkPointer = OHCI_TERMINATE;
        //
        // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
        //
        DescPtrs->TDBulkData->CSReloadValue = 0;
        DescPtrs->TDBulkData->CallBackIndex = USB_InstallCallBackFunction(Ohci_GeneralTDCallback);
        DescPtrs->TDBulkData->ActiveFlag = TRUE;
    
        DescPtrs->EDBulk->Control &= ~ED_SKIP_TDQ;
        //
        // Set the HCBulkHeadED register to point to the bulk ED
        //
        HcWriteHcMem(HcStruc, OHCI_BULK_HEAD_ED, (UINT32)(UINTN)DescPtrs->EDBulk);
        //
        // Clear bulk stall/time out condition flag
        //
        gUsbData->UsbLastCommandStatus &= ~(USB_BULK_STALLED + USB_BULK_TIMEDOUT);
        //
        // Enable the bulk list processing
        //
        HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, BULK_LIST_FILLED);
    
        OhciWaitForTransferComplete(HcStruc, DescPtrs->EDBulk, DescPtrs->TDBulkData, DevInfo);
        //
        // Stop the HC from processing the EDBulk by setting its Skip bit.
        //
        DescPtrs->EDBulk->Control |= ED_SKIP_TDQ;
        //
        // Update the data toggle value into the mass info structure
        //
        UsbUpdateDataToggle(DevInfo, Endp | XferDir, 
          (UINT8)(((DescPtrs->TDBulkData->ControlStatus & GTD_DATA_TOGGLE) >> 24) & 1));
        //
        // Check for the error conditions - if possible recover from them
        //
        ControlStatus = (UINT8)(DescPtrs->TDBulkData->ControlStatus >> 28);
        switch (ControlStatus) {
          case GTD_STALL:
            gUsbData->UsbLastCommandStatus |= USB_BULK_STALLED;
            DevInfo->UsbLastCommandStatusExtended |= USB_TRSFR_STALLED;
            break;
          case GTD_NOT_ACCESSED:
            gUsbData->UsbLastCommandStatus |= USB_BULK_TIMEDOUT;
            DevInfo->UsbLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
            break;
          default:
            break;
    }

    if (ControlStatus != GTD_NO_ERROR) {
      break;
    }

        //
        // Get the size of data transferred
        //
        Data = DescPtrs->TDBulkData->CurrentBufferPointer;
        if (Data != 0)
        {
            //
            // Device sent less data than requested, calculate the
            // transferred size and exit
            //
            //BytesTransferred += (UINT32)(UINTN)DescPtrs->TDBulkData->BufferEnd - Data; //(EIP55025-)
            BytesTransferred += Data - Tmp;   //Short Packet (OHCI Spec 4.3.1.3.5  Transfer Completion, Pg.23)  
            break;
        }

        //
        // CurrentBufferPointer equals 0. This indicates the successfull TD completion,
        // all data is transferred. Adjust the total amount and continue.
        //
        BytesTransferred += BytesToTransfer;
    }

    HcDmaUnmap(HcStruc, BufferMapping);
    
    return  BytesTransferred;
}


/**
    This function executes an interrupt transaction on the USB.
    The data transfer direction is always DATA_IN. This
    function wil not return until the request either completes
    successfully or completes in error (due to time out, etc.)

    @param HcStruc             Pointer to HCStruc of the host controller
    @param DevInfo             DeviceInfo structure (if available else 0)
    @param EndpointAddress     The destination USB device endpoint to which the device request 
                               is being sent.
    @param MaxPktSize          Indicates the maximum packet size the target endpoint is capable 
                               of sending or receiving.
    @param Buffer              Buffer containing data to be sent to the
                               device or buffer to be used to receive data
    @param Length              wLength request parameter, number of bytes
                               of data to be transferred in

    @retval BytesTransferred   Number of bytes transferred


    @note  DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is
              statically allocated and linked with other items in the
              1ms schedule

**/

UINT16
EFIAPI
Ohci_InterruptTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *Buffer,
    UINT16      Length
)
{
    UINT8 DatToggle;
    UINT32 Data;
    OHCI_ED *IntEd;
    OHCI_TD *IntTd;
    UINT8 CompletionCode;
    UINT32 BytesTransferred;
    UINT8 *BufPhyAddr = NULL;
    VOID *BufferMapping = NULL;
    EFI_STATUS  Status;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return 0;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return 0;
    }


    if (gCheckUsbApiParameter) {
        Status = AmiUsbValidateMemoryBuffer((VOID*)Buffer, Length);
        if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Ohci InterruptTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }


    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }
  
    if (OhciIsHalted(HcStruc)) {
      return 0;
    }

    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

    DevInfo->UsbLastCommandStatusExtended = 0;

    IntEd = USB_MemAlloc(GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

    if (IntEd == NULL) {
      return 0;
    }

    IntTd = (OHCI_TD*)((UINTN)IntEd + sizeof(OHCI_ED));

    //
    // Set the SKIP bit to avoid accidental scheduling
    //
    IntEd->Control = ED_SKIP_TDQ;
    //
    // Set the ED's head pointer field to interrupt data TD and tail pointer
    // field to OHCI_TERMINATE. Also set ED's link pointer to OHCI_TERMINATE.
    //
    IntEd->HeadPointer = (UINT32)(UINTN)IntTd;
    IntEd->TailPointer = OHCI_TERMINATE;
    IntEd->EDLinkPointer = OHCI_TERMINATE;
    IntEd->Interval = OhciTranslateInterval(DevInfo->PollInterval);

    //
    // Get maximum packet size from device info structure
    //
    DatToggle = UsbGetDataToggle(DevInfo, EndpointAddress);
  
    //
    // Form the data needed for ED's control field with the available information
    //
    Data = (EndpointAddress & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    Data |= DevInfo->DeviceAddress | ((UINT16)EndpointAddress << 7);
    Data |= ((UINT32)MaxPktSize << 16);
    Data |= (UINT32)(DevInfo->EndpointSpeed & 1) << 13;
    //
    // Update the ED's control field with the data formed
    // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
    //
    IntEd->Control = Data;
    //
    // Fill the general interrupt data TD with relevant information.  Set the
    //  TD's control field with buffer rounding set to 1, direction PID to
    //  don't care, delay interrupt to INTD, data toggle to the latest data
    //  toggle value, error count to no errors and condition code to not accessed.
    //
    // Set the data toggle to DATA0 (SETUP_TOGGLE)
    //
    Data = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET  | GTD_IntD | GTD_SETUP_TOGGLE |
        GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
    IntTd->ControlStatus = Data;
    //
    // Set the data toggle depending on the bDatToggle value
    //
    IntTd->ControlStatus |= ((UINT32)DatToggle << 24);
    //
    // GTD current buffer pointer field will point to the caller's buffer
    //
    HcDmaMap(HcStruc, EndpointAddress & BIT7, Buffer, Length, 
    &BufPhyAddr, &BufferMapping);
    IntTd->CurrentBufferPointer = (UINT32)(UINTN)BufPhyAddr;
    //
    // GTD's buffer end field will point to the last byte of the caller's buffer
    //
    IntTd->BufferEnd = (UINT32)(UINTN)(BufPhyAddr + Length - 1);
    //
    // GTD's link pointer field will be set to OHCI_TERMINATE
    //
    IntTd->LinkPointer = OHCI_TERMINATE;
    //
    // GTD's CSReloadValue field will contain 0 because this is a "one shot" packet
    //
    IntTd->CSReloadValue = 0;
    //
    // GTD's pCallback will point to the Ohci_GeneralTDCallback routine
    //
    IntTd->CallBackIndex = USB_InstallCallBackFunction(Ohci_GeneralTDCallback);
    //
    // GTD's ActiveFlag field will be set to TRUE.
    //
    OhciAddPeriodicEd(HcStruc, IntEd);

    IntTd->ActiveFlag = TRUE;
    IntEd->Control &= ~ED_SKIP_TDQ;

    //
    // Now wait for the interrupt data TD to complete.
    //
    OhciWaitForTransferComplete(HcStruc, IntEd, IntTd, DevInfo);
    //
    // Stop the HC from processing the EDInterrupt by setting its Skip bit.
    //
    OhciRemovePeriodicEd(HcStruc, IntEd);
    //
    // Get appropriate data sync shift value
    //
    DatToggle = (UINT8)((IntTd->ControlStatus & GTD_DATA_TOGGLE) >> 24) & 1;
    UsbUpdateDataToggle(DevInfo, EndpointAddress, DatToggle);
  
    //
    // Check for the error conditions - if possible recover from them
    //
    CompletionCode = (UINT8)(IntTd->ControlStatus >> 28);
    switch (CompletionCode) {
      case GTD_STALL:
          DevInfo->UsbLastCommandStatusExtended |= USB_TRSFR_STALLED;
        break;
      case GTD_NOT_ACCESSED:
          DevInfo->UsbLastCommandStatusExtended |= USB_TRNSFR_TIMEOUT;
        break;
      default:
        break;
    }

  BytesTransferred = IntTd->CurrentBufferPointer == 0 ? Length :
    IntTd->CurrentBufferPointer - (UINT32)(UINTN)BufPhyAddr;

    HcDmaUnmap(HcStruc, BufferMapping);

    USB_MemFree(IntEd, GET_MEM_BLK_COUNT(sizeof(OHCI_ED) + sizeof(OHCI_TD)));

    return (UINT16)BytesTransferred;
}


/**
    This function activates the polling TD for the requested
    device. The device may be a USB keyboard or USB hub

    @param HcStruc   Pointer to the HC structure
    @param DevInfo   Pointer to the device information structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

    @note  For the keyboard device this routine allocates TDRepeat
              also, if it is not already allocated. This routine allocate
              a polling TD and schedule it to 8ms schedule for keyboards
              and to 1024ms schedule for hubs.
**/

UINT8
EFIAPI
Ohci_ActivatePolling(
    HC_STRUC* HcStruc,
    DEV_INFO* DevInfo
)
{
    UINT32     Data;
    UINT8      *Ptr;
    UINT8      DatToggle;
    EFI_STATUS Status;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    Status = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }
   
    if (!VALID_DEVINFO(DevInfo)) {
        return USB_ERROR;
    }

    DatToggle = UsbGetDataToggle(DevInfo, DevInfo->IntInEndpoint);

    Ptr = USB_MemAlloc(1);
    ASSERT(Ptr);
    DevInfo->PollEdPtr  = Ptr;
    Ptr = USB_MemAlloc(1);
    ASSERT(Ptr);
    DevInfo->PollTdPtr  = Ptr;

    Data = (DevInfo->IntInEndpoint & BIT7)? ED_IN_PACKET : ED_OUT_PACKET;
    Data |= (UINT32)DevInfo->DeviceAddress | ((DevInfo->IntInEndpoint & 0xF) << 7);
    Data |= ((UINT32)DevInfo->IntInMaxPkt << 16);
    Data |= (UINT32)(DevInfo->EndpointSpeed & 1) << 13;
    Data |= ED_SKIP_TDQ;

    ((OHCI_ED*)DevInfo->PollEdPtr)->Control = Data;
    ((OHCI_ED*)DevInfo->PollEdPtr)->HeadPointer = (UINT32)(UINTN)DevInfo->PollTdPtr;
    ((OHCI_ED*)DevInfo->PollEdPtr)->HeadPointer |= DatToggle << 1;
    ((OHCI_ED*)DevInfo->PollEdPtr)->EDLinkPointer = OHCI_TERMINATE;
    ((OHCI_ED*)DevInfo->PollEdPtr)->TailPointer = OHCI_TERMINATE;
    ((OHCI_ED*)DevInfo->PollEdPtr)->Interval = OhciTranslateInterval(DevInfo->PollInterval);

    DevInfo->PollDataBuffer = USB_MemAlloc(GET_MEM_BLK_COUNT(DevInfo->PollingLength));  
    ASSERT(DevInfo->PollDataBuffer);

    ((OHCI_TD*)DevInfo->PollTdPtr)->ControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
    ((OHCI_TD*)DevInfo->PollTdPtr)->CSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
                GTD_NO_ERRORS | (GTD_NOT_ACCESSED_32));
    ((OHCI_TD*)DevInfo->PollTdPtr)->CurrentBufferPointer = (UINT32)(UINTN)(DevInfo->PollDataBuffer); 
     ((OHCI_TD*)DevInfo->PollTdPtr)->BufferEnd  = (UINT32)(UINTN)(DevInfo->PollDataBuffer + DevInfo->PollingLength - 1);
    ((OHCI_TD*)DevInfo->PollTdPtr)->LinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)DevInfo->PollTdPtr)->CallBackIndex = USB_InstallCallBackFunction(Ohci_PollingTDCallback);

    OhciAddPeriodicEd(HcStruc, (OHCI_ED*)DevInfo->PollEdPtr);

    ((OHCI_TD*)DevInfo->PollTdPtr)->ActiveFlag = TRUE;
    ((OHCI_ED*)DevInfo->PollEdPtr)->Control &= ~ED_SKIP_TDQ;

    return  USB_SUCCESS;
}

/**
    This function de-activates the polling TD for the requested
    device. The device may be a USB keyboard or USB hub

    @param HcStruc   Pointer to the HC structure
    @param DevInfo   Pointer to the device information structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_DeactivatePolling (
    HC_STRUC* HcStruc,
    DEV_INFO* DevInfo
)
{
    OHCI_ED *OhciEd = (OHCI_ED*)DevInfo->PollEdPtr;
    OHCI_TD *OhciTd = (OHCI_TD*)DevInfo->PollTdPtr;
    EFI_STATUS  EfiStatus;
    
    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    EfiStatus = UsbDevInfoValidation(DevInfo);

    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }
  
    if (!OhciEd) {
        return USB_SUCCESS;
    }

    OhciTd->ControlStatus = 0;
    OhciTd->CSReloadValue = 0;
    OhciTd->ActiveFlag    = FALSE;

    OhciRemovePeriodicEd(HcStruc, OhciEd);

    UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
      (UINT8)((OhciEd->HeadPointer & ED_TOGGLE_CARRY) >> 1));

    USB_MemFree(OhciTd, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    DevInfo->PollTdPtr = NULL;

    USB_MemFree(OhciEd, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    DevInfo->PollEdPtr = NULL;

    if (DevInfo->PollDataBuffer) {
      USB_MemFree(DevInfo->PollDataBuffer, 
                  GET_MEM_BLK_COUNT(DevInfo->PollingLength)); 
      DevInfo->PollDataBuffer = 0;
    } 

    return  USB_SUCCESS;
}

/**
    This function is called when a polling TD from the TD pool
    completes an interrupt transaction to its assigned device.
    This routine should process any data in the TD's data buffer,
    handle any errors, and then copy the TD's CSReloadValue
    field into its control status field to put the TD back
    into service.

    @param HcStruc     Pointer to the HCStruc structure
    @param DevInfo     NULL (DevInfo is not valid)
    @param Td          Pointer to the TD that completed
    @param Buffer      Not used
    @param DataLength  Data length

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_PollingTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    UINT8   Index;
    UINT16  BytesTransferred;
    
    if (((OHCI_TD*)Td)->ActiveFlag == FALSE) {
        return USB_SUCCESS;
    }

    ((OHCI_TD*)Td)->ActiveFlag = FALSE;
    HcClearHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    for (Index = 1; Index < gUsbData->MaxDevCount; Index++) {
        DevInfo = &gUsbDataList->DevInfoTable[Index];
        if (DevInfo->Flag & DEV_INFO_DEV_PRESENT) {
            if (DevInfo->PollTdPtr == Td) {
                break;
            }
        }
    }

    if (Index == gUsbData->MaxDevCount) {
        return USB_ERROR;
    }

    UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
      (UINT8)((((OHCI_ED*)DevInfo->PollEdPtr)->HeadPointer & ED_TOGGLE_CARRY) >> 1));


    if ((((OHCI_TD*)Td)->ControlStatus & GTD_STATUS_FIELD) == GTD_NO_ERROR) {
        //
        // Get the size of data transferred
        //
        if (((OHCI_TD*)Td)->CurrentBufferPointer != 0) {
            BytesTransferred = (UINT16)(((OHCI_TD*)Td)->CurrentBufferPointer -
                               (UINT32)(UINTN)(DevInfo->PollDataBuffer));
        } else {
            BytesTransferred = DevInfo->PollingLength;
        }
        if ((DevInfo->CallBackIndex) && (DevInfo->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
            if (gAmiUsbCallBackFunTbl[DevInfo->CallBackIndex - 1 + CALLBACK_FUNCTION_START]) {
                (*gAmiUsbCallBackFunTbl[DevInfo->CallBackIndex - 1+ CALLBACK_FUNCTION_START])(
                  HcStruc,
                  DevInfo,
                  (UINT8*)Td,
                  DevInfo->PollDataBuffer,
                  BytesTransferred);
            }
        }
    }
                  
    HcSetHcMem(HcStruc, OHCI_CONTROL_REG, PERIODIC_LIST_ENABLE);

    // Clear the link pointer. It may point to some other TD
    ((OHCI_TD*)Td)->LinkPointer = OHCI_TERMINATE;
    ((OHCI_TD*)Td)->ControlStatus = ((OHCI_TD*)Td)->CSReloadValue;
    ((OHCI_TD*)Td)->CurrentBufferPointer = (UINT32)(UINTN)(DevInfo->PollDataBuffer);  
    ((OHCI_ED*)DevInfo->PollEdPtr)->HeadPointer &= ED_TOGGLE_CARRY;
    ((OHCI_ED*)DevInfo->PollEdPtr)->HeadPointer |= (UINTN)((OHCI_TD*)Td);
    ((OHCI_TD*)Td)->ActiveFlag = TRUE;
    // Reset the TD's control and buffer pointer fields to their original values.
    return USB_SUCCESS;
}

/**
    This function disables the keyboard repeat rate logic by
    enabling the repeat TD

    @param HcStruc   Pointer to the HCStruc structure
    
    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_DisableKeyRepeat (
    HC_STRUC  *HcStruc
)
{
    OHCI_DESC_PTRS      *DescPtrs;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }
    
    DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;

    if (DescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }
    
    if (DescPtrs->EDRepeat == NULL) {
      return USB_ERROR;
    }

    if (((UINTN)DescPtrs->EDRepeat < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->EDRepeat + sizeof(OHCI_ED)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    DescPtrs->EDRepeat->Control |= ED_SKIP_TDQ;    // Inactive
    DescPtrs->TDRepeat->ActiveFlag = FALSE;

    return  USB_SUCCESS;
}


/**
    This function enables the keyboard repeat rate logic by
    enabling the repeat TD

    @param HcStruc   Pointer to the HC_STRUC structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_EnableKeyRepeat(
    HC_STRUC  *HcStruc
)
{
    OHCI_DESC_PTRS      *DescPtrs;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;

    if (DescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (DescPtrs->EDRepeat == NULL) {
      return USB_ERROR;
    }

    if (((UINTN)DescPtrs->EDRepeat < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->EDRepeat + sizeof(OHCI_ED)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    DescPtrs->TDRepeat->LinkPointer = OHCI_TERMINATE;
    DescPtrs->EDRepeat->HeadPointer = (UINT32)(UINTN)DescPtrs->TDRepeat;
    DescPtrs->TDRepeat->ControlStatus = DescPtrs->TDRepeat->CSReloadValue;
    DescPtrs->TDRepeat->ActiveFlag = TRUE;
    DescPtrs->EDRepeat->Control &= (~ED_SKIP_TDQ); // Active

    return  USB_SUCCESS;
}


/**
    This API function is called to enumerate the root hub ports
    in the OHCI controller. The input to the routine is the
    pointer to the HC structure  that defines this host controller

    @param HcStruc   Pointer to the HC_STRUC structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure
**/

UINT8
EFIAPI
Ohci_EnumeratePorts(
    HC_STRUC* HcStruc
)
{
    UINT32  RhDescriptorA = 0;
    UINT8  PowerOnDelay;
    UINT8  Index;
    UINT16  PortReg = OHCI_RH_PORT1_STATUS;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (OhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    RhDescriptorA = HcReadHcMem(HcStruc, OHCI_RH_DESCRIPTOR_A);
    if (!(RhDescriptorA & NO_POWER_SWITCH)) {
      if (!(RhDescriptorA & POWER_SWITCH_MODE)) {
      // All ports are powered at the same time, enable global port power
        HcWriteHcMem(HcStruc, OHCI_RH_STATUS, SET_GLOBAL_POWER);
      } else {
         // Each port is powered individually, enable individual port's power
         for (Index = 0; Index < HcStruc->NumPorts; PortReg+=4, Index++) {
                // Set PortPowerControlMask bit 
                HcSetHcMem(HcStruc, OHCI_RH_DESCRIPTOR_B, ((1 << (Index + 1)) << 16));
                // Set PortPower bit
                HcWriteHcMem(HcStruc, PortReg, SET_PORT_POWER);
        }
      }
      PowerOnDelay = ((RhDescriptorA & POWERON2POWERGOOD_TIME) >> 24) << 1;
      FixedDelay(PowerOnDelay * 1000);
  }

    Ohci_ProcessRootHubStatusChange(HcStruc);

    return  USB_SUCCESS;
}


/**
    This function adds a ED to the frame list

    @param HcStruc    Pointer to the host controller structure
    @param Ed         ED will be added in periodic schedule

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
OhciAddPeriodicEd (
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = 0; Index < HcStruc->AsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->FrameList[Index]; 
        Current = (OHCI_ED*)(UINTN)(*PrevPtr);

        while (Current != NULL) {

            Status = AmiUsbValidateMemoryBuffer((VOID*)Current, sizeof(OHCI_ED));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
                return USB_ERROR;
            }

            if (Current->Interval <= Ed->Interval) {
                break;
            }

            PrevPtr = &Current->EDLinkPointer; 
            Current = (OHCI_ED*)(UINTN)Current->EDLinkPointer;
        }

        if (Current == Ed) {
            continue;
        }
        Ed->EDLinkPointer = (UINT32)(UINTN)Current;

        Status = AmiUsbValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
            return USB_ERROR;
        }

        *PrevPtr = (UINT32)(UINTN)Ed;
    }

    return USB_SUCCESS;
}

/**
    This function removes a ED from the frame list

    @param HcStruc    Pointer to the host controller structure
    @param Ed         ED will be added in periodic schedule

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
OhciRemovePeriodicEd(
    HC_STRUC    *HcStruc,
    OHCI_ED     *Ed
)
{
    UINT16  Index;
    UINT32  *PrevPtr;
    OHCI_ED *Current;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (Ed == NULL || Ed->Interval == 0) {
        return USB_ERROR;
    }

    Ed->Control |= ED_SKIP_TDQ;

    for (Index = 0; Index < HcStruc->AsyncListSize; Index += Ed->Interval) {
        PrevPtr = &HcStruc->FrameList[Index]; 
        Current = (OHCI_ED*)(UINTN)(*PrevPtr);

        while (Current != NULL) {

            Status = AmiUsbValidateMemoryBuffer((VOID*)Current, sizeof(OHCI_ED));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
                return USB_ERROR;
            }

            if (Current == Ed) {
                break;
            }

            PrevPtr = &Current->EDLinkPointer; 
            Current = (OHCI_ED*)(UINTN)Current->EDLinkPointer;
        }

        if (Current == NULL) {
            continue;
        }

         Status = AmiUsbValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
         if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) {
            return USB_ERROR;
         }

        *PrevPtr = Ed->EDLinkPointer;
    }

    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, START_OF_FRAME);
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, START_OF_FRAME_ENABLE);

    for (Index = 0; Index < 100; Index++) {
        if (HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & START_OF_FRAME) {
            break;
        }
        FixedDelay(10);   // 10 us delay
    }
    ASSERT(Index < 100);
    ASSERT(HcReadHcMem(HcStruc, OHCI_INTERRUPT_STATUS) & START_OF_FRAME);
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, START_OF_FRAME_DISABLE);

    return USB_SUCCESS;
}

/**
    This function starts the standard TD schedules for the
    USB host controller

    @param HcStruc    Pointer to the host controller structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

    @note  This routine creates 1, 2, 8, 32 and 1024ms schedules

**/

UINT8
Ohci_StartEDSchedule(
    HC_STRUC    *HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs;
    UINT8           *Ptr;

    //
    // Allocate descriptor structure and fill it in HCStruc
    //
    DescPtrs = (OHCI_DESC_PTRS*)USB_MemAlloc (GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
    ASSERT(DescPtrs);
    if (!DescPtrs) return USB_ERROR;

    //
    // Save the value in the HC struc
    //
    HcStruc->DescPtrs.OhciDescPtrs = DescPtrs;

    //
    // Allocate 4 EDs + 1 TDs and put them in Descriptor list
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    DescPtrs->PeriodicEd = (OHCI_ED*)Ptr;
    DescPtrs->PeriodicEd->Control = ED_SKIP_TDQ;
    DescPtrs->PeriodicEd->EDLinkPointer = 0;
    DescPtrs->PeriodicEd->Interval = 1;

    // Initialize each entry of Interrupt Table as statically disable ED
    OhciAddPeriodicEd(HcStruc, DescPtrs->PeriodicEd);

    //
    // Allocate ED/TD for EDControl, TDControlSetup, TDControlData,
    // TDControlStatus, EDBulk, TDBulkData, EDInterrupt and TDInterruptData
    //
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
    ASSERT(Ptr);
    if (!Ptr) return USB_ERROR;

    //
    // Save the 8 ED/TD in their proper position. Note: HCStruc->DescPtrs.OhciDescPtrs
    // is initialized earlier in Ohci_StartEDSchedule.
    //
    DescPtrs->EDControl = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->TDControlSetup = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->TDControlData = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->TDControlStatus = (OHCI_TD*)Ptr;
    Ptr += sizeof (OHCI_TD);

    DescPtrs->EDBulk = (OHCI_ED*)Ptr;
    Ptr += sizeof (OHCI_ED);

    DescPtrs->TDBulkData = (OHCI_TD*)Ptr;

    if (HcStruc->HcFlag & HC_STATE_EXTERNAL) {
      return USB_SUCCESS;
    }

    // Allocate a ED/TD for EDRepeat/TDRepeat
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    ASSERT(Ptr);
    DescPtrs->EDRepeat  = (OHCI_ED*)Ptr;
 
    Ptr = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    ASSERT(Ptr);
    DescPtrs->TDRepeat  = (OHCI_TD*)Ptr;

    DescPtrs->EDRepeat->Control = ((UINT32)(gUsbData->MaxDevCount+1) |
            ED_IN_PACKET | ED_SKIP_TDQ | (DEFAULT_PACKET_LENGTH << 16));
    DescPtrs->EDRepeat->HeadPointer = (UINT32)(UINTN)DescPtrs->TDRepeat;
    DescPtrs->EDRepeat->EDLinkPointer = OHCI_TERMINATE;
    DescPtrs->EDRepeat->TailPointer = OHCI_TERMINATE;
//    DescPtrs->EDRepeat->Interval = REPEAT_INTERVAL;
    if (gUsbData->RepeatIntervalMode){
        DescPtrs->EDRepeat->Interval = REPEAT_INTERVAL_16MS;
    } else {
        DescPtrs->EDRepeat->Interval = REPEAT_INTERVAL_8MS;
    }


    DescPtrs->TDRepeat->ControlStatus = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED_32));
    DescPtrs->TDRepeat->CSReloadValue = (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_IntD |
        GTD_TWO_ERRORS | (GTD_NOT_ACCESSED_32));

    DescPtrs->TDRepeat->CurrentBufferPointer =
                (UINT32)(UINTN)DescPtrs->TDRepeat->SetupData;
    DescPtrs->TDRepeat->BufferEnd =
                (UINT32)(UINTN)DescPtrs->TDRepeat->SetupData;
    DescPtrs->TDRepeat->LinkPointer = OHCI_TERMINATE;
    DescPtrs->TDRepeat->CallBackIndex = USB_InstallCallBackFunction(Ohci_RepeatTDCallBack);
    DescPtrs->TDRepeat->ActiveFlag = FALSE;

    OhciAddPeriodicEd(HcStruc, DescPtrs->EDRepeat);
  
    USBKeyRepeat(HcStruc, 0);

    return USB_SUCCESS;
}


/**
    This function resets the OHCI controller

    @param HcStruc         Pointer to the host controller structure
    
    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure
**/

UINT8 Ohci_ResetHC(
    HC_STRUC* HcStruc
)
{
    UINT8  Index;
    //
    // Issue a software reset and HC go to UsbSuspend state
    //
    HcWriteHcMem(HcStruc, OHCI_COMMAND_STATUS, HC_RESET);

    // The reset operation must be completed within 10 us
    for (Index = 0; Index < 100; Index++) {
      FixedDelay(1);   // 1 us delay
      if (!(HcReadHcMem(HcStruc, OHCI_COMMAND_STATUS) & HC_RESET)) {
        return USB_SUCCESS;
      }
    }

    return USB_ERROR;
}


/**
    This function is called when TD1024ms completes
    a transaction. This TD runs a dummy interrupt transaction
    to a non-existant device address for the purpose of
    generating a periodic timeout interrupt.  This periodic
    interrupt may be used to check for new devices on the
    root hub etc.

    @param HcStruc    Pointer to the host controller structure
    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure
**/

UINT32 Ohci_ProcessRootHubStatusChange(
    HC_STRUC*   HcStruc
)
{
    UINT8   HcNumber;
    UINT8   Port;

    //
    // Check EnumFlag before enumerating devices behind root hub
    //
    if (gUsbData->EnumFlag == TRUE) {
        return USB_ERROR;
    }

    // The interval with a minimum duration of 100 ms when 
    // the USB System Software is notified of a connection detection.
    FixedDelay(USB_PORT_CONNECT_STABLE_DELAY_MS * 1000);
    
    gUsbData->EnumFlag = TRUE;    // Set enumeration flag and avoid hub port enumeration
    //
    // Mask the Host Controller interrupt so the ISR does not get re-entered due
    // to an IOC interrupt from any TDs that complete in frames while we are
    // configuring a new device that has just been plugged in.
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_DISABLE, 0x80000000);
    //
    // Check all the ports on the root hub for any change in connect status.
    // If the connect status has been changed on either or both of these ports,
    // then call the  routine UsbHubPortChange for each changed port.
    //
    HcNumber = HcStruc->HcNumber | BIT7;

    for (Port = 1; Port <= HcStruc->NumPorts; Port++) {

        //PortStatus = Ohci_GetRootHubStatus (HCStruc, bPort+1);
        //HcClearHcMem(HcStruc, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);
        //if (PortStatus & USB_PORT_STAT_DEV_CONNECT_CHANGED) {
        USBCheckPortChange(HcStruc, HcNumber, Port);
        //}
        //HcClearHcMem(HcStrucs, OHCI_RH_PORT1_STATUS+bPort*4, 0xFFFF);

    }
    //
    // Clear the RH_STATUS_CHANGE bit of the interrupt status register
    // in the host controller: write 1 to bit to clear it
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_STATUS, RH_STATUS_CHANGE);

    //
    // Renable interrupts from the host controller
    //
    HcWriteHcMem(HcStruc, OHCI_INTERRUPT_ENABLE, MASTER_INTERRUPT_ENABLE);

    gUsbData->EnumFlag    = FALSE;
    return USB_SUCCESS;
}



/**
    This function executes a device request command transaction

    @param HcStruc    Pointer to the host controller structure
    @param LastTd     Pointer to the Ed
    @param LastTd     Pointer to the Td which has to be completed
    @param DevInfo    Pointer to the device information structure
    
    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
OhciWaitForTransferComplete(
    HC_STRUC  *HcStruc, 
    OHCI_ED    *XferEd,
    OHCI_TD    *LastTd,
    DEV_INFO*  DevInfo
)
{
    UINT32 Count ;
    UINT32 Timeout = gUsbData->UsbReqTimeOutValue << 4; // *16, makes it number of 60mcs units

    //
    // Check status change loop iteration
    //
    for (Count = 0; !Timeout || Count < Timeout; Count++) {
        Ohci_ProcessInterrupt(HcStruc);
        if (!LastTd->ActiveFlag ) {
           return USB_SUCCESS;
        } else if (!VALID_DEVINFO(DevInfo)){
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "OHCI Abort: devinfo: %x\n", DevInfo);
            return USB_ERROR;
        }
        FixedDelay(60);  // 60 microseconds
    }

    XferEd->Control |= ED_SKIP_TDQ;
    Ohci_ProcessInterrupt(HcStruc);

    if (!LastTd->ActiveFlag) {
      return USB_SUCCESS;
    }

    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "OHCI Time-Out\n");

    return USB_ERROR;
}


/**
    This routine is called, from host controllers that supports
    OS handover functionality (currently from OHCI driver only), when OS
    wants the BIOS to hand-over the host controllers to the OS.  This routine
    will stop HC that does not support this functionality.
    
    @param HcStruc          Pointer to the HCStruc structure
    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure
**/

UINT8
Ohci_StopUnsupportedHC(
    HC_STRUC*  HcStruc
)
{
    UINT8  Index;

    if (!gUsbDataList->UsbSetupData->UsbEhciHandoff) {
        return USB_SUCCESS;
    }

    //
    // Currently this host controller stops only the EHCI host controllers
    // Find the EHCI host controller HCStruc
    //
    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++ ) {
        if (gHcTable[Index] == NULL) {
            continue;
        }
        if (!(gHcTable[Index]->HcFlag & HC_STATE_USED)) {
          continue;
        }
        if (!(gHcTable[Index]->HcFlag & HC_STATE_RUNNING) ||
         (gHcTable[Index]->HcType != USB_HC_EHCI) ||
            ((gHcTable[Index]->BusDevFuncNum & ~0x7) != 
            (HcStruc->BusDevFuncNum & ~0x7))) {
            continue;
        }

        gUsbData->HandOverInProgress = TRUE;
        AmiUsbControllerStop(gHcTable[Index]);
    }

    return USB_SUCCESS;
}

/**
    This function is called when bulk data or interrupt data TD
    is completed. This routine just deactivates the TD.

    @param HcStruc     Pointer to the HCStruc structure
    @param DevInfo     NULL (pDevInfo is not valid)
    @param Td          Pointer to the TD that completed
    @param Buffer      Not used
    @param DataLength  Data length
    
    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure
**/

UINT8
EFIAPI
Ohci_GeneralTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
 )
{
    ((OHCI_TD*)Td)->ActiveFlag = FALSE;
    return USB_SUCCESS;
}


/**
    This function is called when the control transfer scheduled
    is completed.
    @param HcStruc     Pointer to the HCStruc structure
    @param DevInfo     NULL (pDevInfo is not valid)
    @param Td          Pointer to the TD that completed
    @param Buffer      Not used
    @param DataLength  Data length

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Ohci_ControlTDCallback(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8*      Td,
    UINT8*      Buffer,
    UINT16      DataLength
)
{
    OHCI_DESC_PTRS *DescPtrs;
    UINT8           *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));
    //
    // Check to see if the TD that just completed has any error bits set.  If
    // any of the control TDs (Setup, Data, or Status) complete with an error, set
    // ActiveFlag of the control status TD and copy the error information from the
    // TD that just completed into the control status TD.
    //
    if ((UINT8)(((OHCI_TD*)Td)->ControlStatus >> 28)) {
        DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;
        if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
            (((UINTN)DescPtrs + sizeof(OHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
            return USB_ERROR;
        }
        if (((UINTN)DescPtrs->TDControlStatus < (UINTN)gUsbDataList->MemBlockStart) ||
            (((UINTN)DescPtrs->TDControlStatus + sizeof(OHCI_TD)) > (UINTN)MemBlockEnd)) {
            return USB_ERROR;
        }
        if (DescPtrs->TDControlStatus != (OHCI_TD*)Td) {
            DescPtrs->TDControlStatus->ControlStatus = ((OHCI_TD*)Td)->ControlStatus;
            DescPtrs->TDControlStatus->ActiveFlag = FALSE;
        }
    }
    //
    // Make the TD that just completed inactive.  It may be the control setup TD,
    // one of the control data TDs, or the control status TD.
    //
    ((OHCI_TD*)Td)->ActiveFlag = FALSE;

    return USB_SUCCESS;
}

/**
    This function will check whether the TD is completed
    if so, it will call the call back routine associated with
    this TD.
    
     @param HcStruc    Pointer to the host controller structure
     @param Td          Pointer to the TD that completed
     
     @retval None
     
     @note  For any TD whose ActiveFlag is TRUE and its ControlStatus
      bit 23 is clear (completed), process the TD by calling
      its call back routine, if one is present.
**/

VOID Ohci_ProcessTD(
    HC_STRUC    *HcStruc,
    OHCI_TD     *Td
)
{
    if (!Td) {
        return;  // Check for NULL
    }
    if (Td->ActiveFlag != TRUE) {
        return;  // TD is not active
    }
    if ((Td->CallBackIndex) && (Td->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        if (gAmiUsbCallBackFunTbl[Td->CallBackIndex - 1 + CALLBACK_FUNCTION_START]) {
            (*gAmiUsbCallBackFunTbl[Td->CallBackIndex - 1 + CALLBACK_FUNCTION_START])(
                HcStruc,
                0,
                (UINT8*)Td,
                0,
                0);
        }
    }
}


/**
    This function is used to free the all the allocated TDs,
    QH and DescriptorPtr structure. This function only frees
    the entries in the DescriptorPtr and the descriptor pointer
    only.

    @param  HcStruc    Pointer to the host controller structure
    @retval None
**/

VOID Ohci_FreeAllStruc(
    HC_STRUC* HcStruc
)
{
    OHCI_DESC_PTRS  *DescPtrs;

    DescPtrs = HcStruc->DescPtrs.OhciDescPtrs;

// Free the EDs & TDs
    USB_MemFree(DescPtrs->PeriodicEd, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    if (DescPtrs->EDRepeat) {
      USB_MemFree(DescPtrs->EDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_ED));
    }
    if (DescPtrs->TDRepeat) {
      USB_MemFree(DescPtrs->TDRepeat, GET_MEM_BLK_COUNT_STRUC(OHCI_TD));
    }

    USB_MemFree(DescPtrs->EDControl, 
        GET_MEM_BLK_COUNT(2 * sizeof(OHCI_ED) + 4 * sizeof(OHCI_TD)));
  
// Free descriptor structure (in BX)
    USB_MemFree(DescPtrs, GET_MEM_BLK_COUNT_STRUC(OHCI_DESC_PTRS));
}


/**
    This function check whether HC is halted.
    @param  HcStruc    Pointer to the host controller structure
    @retval TRUE       Ohci controller is halted
    @retval FALSE      Ohci controller is NOT halted
**/
BOOLEAN
OhciIsHalted (
    HC_STRUC  *HcStruc
)
{
    return (HcReadHcMem(HcStruc, OHCI_CONTROL_REG) & HC_FUNCTION_STATE) != USBOPERATIONAL;
}

/**
    This function calculates the polling rate.
    
    @param  Interval          Interval Value
    @retval PollingRate       polling rate
**/
UINT8
OhciTranslateInterval(
    UINT8   Interval
)
{
    UINT8  BitCount = 0;

    // The Interval value should be from 1 to 255
    ASSERT(Interval >= 1 && Interval <= 255);
    if(Interval != 0){
        for (BitCount = 0; Interval != 0; BitCount++) {
            Interval >>= 1;
        }
        return (UINT8)(1 << (BitCount - 1));
    }
    else{
        return 1;
    }
}



//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
