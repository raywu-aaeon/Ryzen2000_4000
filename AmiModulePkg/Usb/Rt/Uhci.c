//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Uhci.c
    AMI USB UHCI driver

**/

#include "AmiUsb.h"
#include "UsbKbd.h"
#include <Library/AmiUsbHcdLib.h>

extern  VOID*       USB_MemAlloc (UINT16);
extern  UINT8       USB_MemFree  (VOID _FAR_ *,  UINT16);
extern  UINT8       USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
extern  UINT8       EFIAPI USB_InstallCallBackFunction (CALLBACK_FUNC);

extern  VOID        EFIAPI WordWritePCIConfig(UINT16, UINT8, UINT16);

UINT32  EFIAPI HcReadPciReg(HC_STRUC*, UINT32);
VOID    EFIAPI HcWritePciReg(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcWordWritePciReg(HC_STRUC*, UINT32, UINT16);
UINT32  EFIAPI HcReadHcMem(HC_STRUC*, UINT32);
VOID    EFIAPI HcWriteHcMem(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcClearHcMem(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcSetHcMem(HC_STRUC*, UINT32, UINT32);
UINT32  EFIAPI HcReadOpReg(HC_STRUC*, UINT32);
VOID    EFIAPI HcWriteOpReg(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcClearOpReg(HC_STRUC*, UINT32, UINT32);
VOID    EFIAPI HcSetOpReg(HC_STRUC*, UINT32, UINT32);
UINT8   EFIAPI HcByteReadHcIo(HC_STRUC*, UINT32);
VOID    EFIAPI HcByteWriteHcIo(HC_STRUC*, UINT32, UINT8);
UINT16  EFIAPI HcWordReadHcIo(HC_STRUC*, UINT32);
VOID    EFIAPI HcWordWriteHcIo(HC_STRUC*, UINT32, UINT16);
UINT32  EFIAPI HcDwordReadHcIo(HC_STRUC*, UINT32);
VOID    EFIAPI HcDwordWriteHcIo(HC_STRUC*, UINT32, UINT32);
UINT8   EFIAPI HcDmaMap(HC_STRUC*, UINT8, UINT8*, UINT32, UINT8**, VOID**);
UINT8   EFIAPI HcDmaUnmap(HC_STRUC*, VOID*);

extern  VOID        EFIAPI FixedDelay(UINTN);
extern  DEV_INFO*   EFIAPI USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
extern  UINT8       USBLogError(UINT16);
extern  VOID        USB_InitFrameList (HC_STRUC*, UINT32);

extern  VOID        EFIAPI USBKBDPeriodicInterruptHandler(HC_STRUC*);
extern  VOID        EFIAPI USBKeyRepeat(HC_STRUC*, UINT8);


UINT8   USB_DisconnectDevice (HC_STRUC*, UINT8, UINT8);
UINT8   UsbGetDataToggle(DEV_INFO*,UINT8);
VOID    UsbUpdateDataToggle(DEV_INFO*, UINT8, UINT8);

//---------------------------------------------------------------------------

// Public function declaration
UINT8   EFIAPI Uhci_Start (HC_STRUC*);
UINT8   EFIAPI Uhci_Stop (HC_STRUC*);
UINT8   EFIAPI Uhci_EnumeratePorts (HC_STRUC*);
UINT8   EFIAPI Uhci_DisableInterrupts (HC_STRUC*);
UINT8   EFIAPI Uhci_EnableInterrupts (HC_STRUC*);
UINT8   EFIAPI Uhci_ProcessInterrupt(HC_STRUC*);
UINT32  EFIAPI Uhci_GetRootHubStatus (HC_STRUC*, UINT8, BOOLEAN);
UINT8   EFIAPI Uhci_DisableRootHub (HC_STRUC*,UINT8);
UINT8   EFIAPI Uhci_EnableRootHub (HC_STRUC*,UINT8);
UINT8   EFIAPI Uhci_ResetRootHub (HC_STRUC*,UINT8);
UINT16  EFIAPI Uhci_ControlTransfer (HC_STRUC*,DEV_INFO*,UINT16,UINT16,UINT16,UINT8*,UINT16);
UINT32  EFIAPI Uhci_BulkTransfer (HC_STRUC*,DEV_INFO*,UINT8,UINT8*,UINT32);
UINT16  EFIAPI Uhci_InterruptTransfer (HC_STRUC*, DEV_INFO*, UINT8, UINT16, UINT8*, UINT16);
UINT8   EFIAPI Uhci_DeactivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EFIAPI Uhci_ActivatePolling (HC_STRUC*,DEV_INFO*);
UINT8   EFIAPI Uhci_DisableKeyRepeat (HC_STRUC*);
UINT8   EFIAPI Uhci_EnableKeyRepeat (HC_STRUC*);
UINT8   EFIAPI Uhci_GlobalSuspend (HC_STRUC*);  
UINT8   EFIAPI UhciSmiControl(HC_STRUC*, BOOLEAN);

UINT8   UhciProcessQh (HC_STRUC*, UHCI_QH*);
UINT8   UhciProcessTd (HC_STRUC*, UHCI_TD*);
UINT8   UhciProcessFrameList (HC_STRUC*);

UINT8   Uhci_DisableHCPorts (HC_STRUC*);
UINT8   Uhci_StartTDSchedule (HC_STRUC*);
UINT8   Uhci_StopTDSchedule (HC_STRUC*);
UINT8   Uhci_InterruptTDCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*);
UINT8   UhciAddQhToFrameList (HC_STRUC*, UHCI_QH*);
UINT8   UhciRemoveQhFromFrameList (HC_STRUC*, UHCI_QH*);
VOID    UhciInitQh (UHCI_QH*);
BOOLEAN UhciIsHalted(HC_STRUC*);
UINT8   UhciTranslateInterval(UINT8);

extern  USB_DATA_LIST   *gUsbDataList;
extern HC_STRUC        **gHcTable;

UHCI_TD*
UhciAllocGeneralTds (
    IN UINT8        DeviceAddr,
    IN BOOLEAN      LowSpeed,
    IN UINT8        PacketId,
    IN UINT8        EndpointAddr,
    IN UINT16       MaxPacket,
    IN BOOLEAN      ShortPacket,
    IN OUT UINTN    *BufferAddr,
    IN OUT UINT32   *Length,
    IN OUT UINT8    *DataToggle
);

VOID
UhciFreeTds (
    IN UHCI_TD  *FirstTd
);

VOID
UhciActivateTds (
    IN UHCI_TD  *FirstTd,
    IN UINT8     DataToggle
);

extern  USB_GLOBAL_DATA *gUsbData;
extern  BOOLEAN gCheckUsbApiParameter;

UINT8   EFIAPI UhciRootHubQhCallBack(HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   EFIAPI UhciRepeatQhCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   EFIAPI UhciPollingQhCallback (HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);

/**
    This function fills the host controller driver routine pointers

    @param HcdHeader        Pointer to the host controller header structure

    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure

**/

UINT8
Uhci_FillHCDEntries(
    HCD_HEADER *HcdHeader
)
{
    //
    // Fill the routines here
    //
    HcdHeader->FnHcdStart                = Uhci_Start;
    HcdHeader->FnHcdStop                 = Uhci_Stop;
    HcdHeader->FnHcdEnumeratePorts       = Uhci_EnumeratePorts;
    HcdHeader->FnHcdDisableInterrupts    = Uhci_DisableInterrupts;
    HcdHeader->FnHcdEnableInterrupts     = Uhci_EnableInterrupts;
    HcdHeader->FnHcdProcessInterrupt     = Uhci_ProcessInterrupt;
    HcdHeader->FnHcdGetRootHubStatus     = Uhci_GetRootHubStatus;
    HcdHeader->FnHcdDisableRootHub       = Uhci_DisableRootHub;
    HcdHeader->FnHcdEnableRootHub        = Uhci_EnableRootHub;
    HcdHeader->FnHcdControlTransfer      = Uhci_ControlTransfer;
    HcdHeader->FnHcdBulkTransfer         = Uhci_BulkTransfer;
    HcdHeader->FnHcdIsocTransfer         = UsbHcdIsocTransferDummy;
    HcdHeader->FnHcdInterruptTransfer    = Uhci_InterruptTransfer;
    HcdHeader->FnHcdDeactivatePolling    = Uhci_DeactivatePolling;
    HcdHeader->FnHcdActivatePolling      = Uhci_ActivatePolling;
    HcdHeader->FnHcdDisableKeyRepeat     = Uhci_DisableKeyRepeat;
    HcdHeader->FnHcdEnableKeyRepeat      = Uhci_EnableKeyRepeat;
    HcdHeader->FnHcdEnableEndpoints      = UsbHcdEnableEndpointsDummy;
    HcdHeader->FnHcdInitDeviceData       = UsbHcdInitDeviceDataDummy;
    HcdHeader->FnHcdDeinitDeviceData     = UsbHcdDeinitDeviceDataDummy;
    HcdHeader->FnHcdResetRootHub         = Uhci_ResetRootHub;
    HcdHeader->FnHcdClearEndpointState   = UsbHcdClearEndpointStateDummy;
    HcdHeader->FnHcdGlobalSuspend        = Uhci_GlobalSuspend;
    HcdHeader->FnHcdSmiControl           = UhciSmiControl;

    USB_InstallCallBackFunction(UhciPollingQhCallback);
    USB_InstallCallBackFunction(UhciRepeatQhCallback);
    USB_InstallCallBackFunction(UhciRootHubQhCallBack);

    return  USB_SUCCESS;
}

/**
    This API function is called to start a UHCI host controller. The input to the
    routine is the pointer to the HC structure that defines this host controller

    @param  HcStruc          Pointer to the host controller structure

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_Start(
    HC_STRUC*   HcStruc
)
{
    UINT16  IoAddr;
    UINT16  LegSupReg;
    UINT16  Index;
    EFI_STATUS  Status;
    UINT32  UsbHcClassCode;  

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    // The address offset of class code register is in 09-0Bh, we get the value
    // from offset 08h for alignment and shift right 8 bits.
    UsbHcClassCode = HcReadPciReg(HcStruc, USB_REG_REVISION_ID);   
    UsbHcClassCode = UsbHcClassCode >> 8;

    if (UsbHcClassCode != UHCI_CLASS_CODE) {
        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "UHCI HC Class Code is wrong: %x\n", UsbHcClassCode);
        return USB_ERROR;
    }
    

    Status = AmiUsbValidateMemoryBuffer((VOID*)HcStruc->FrameList, 0x1000);
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) {
        return USB_ERROR;
    }

    //
    // Set number of root hub ports present
    //
    HcStruc->NumPorts = 2;

    //
    // Get the I/O base address for the host controller
    //
    IoAddr = (UINT16)HcReadPciReg(HcStruc, USB_IO_BASE_ADDRESS);

    //
    // Mask the low order two bits and store the value in HCStruc
    //
    IoAddr = (UINT16)(IoAddr & (~(BIT0+BIT1)));
    USB_DEBUG(DEBUG_HC, "HC I/O Address : %X\n", IoAddr);
    HcStruc->BaseAddress = IoAddr;

    HcStruc->AsyncListSize = UHCI_FRAME_LIST_SIZE;

    //
    // Disable hardware interrupt generation by programming legacy registers
    //
    LegSupReg = (UINT16)HcReadPciReg(HcStruc, USB_UHCI_REG_LEGSUP);

    //
    // Disable generation of SMI/IRQ and clear status bits
    //
    LegSupReg = (UINT16)(LegSupReg & (~BIT4));
    HcWordWritePciReg(HcStruc, USB_UHCI_REG_LEGSUP, LegSupReg);

    //
    // Disable the interrupts (to aVOID spurious interrupts)
    //
    Uhci_DisableInterrupts(HcStruc);

    //
    // Disable the host controller root hub ports
    //
    Uhci_DisableHCPorts(HcStruc);

    //
    // Check whether HC is already stopped
    //
    if (!UhciIsHalted(HcStruc)) {
        //
        // HC is still running. Stop it by programming HC run bit
        //
        HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG,
            HcByteReadHcIo(HcStruc, UHCI_COMMAND_REG) & ~UHC_HOST_CONTROLLER_RUN);

        //
        // Check whether the host controller is halted (check for 50 ms)
        //
        for (Index = 0; Index < 500; Index++) {
            if ((HcByteReadHcIo(HcStruc, UHCI_STATUS_REG)) & UHC_HC_HALTED) {
                break;
            }
            FixedDelay(100);      // 100 us delay
        }
    }
    ASSERT((HcByteReadHcIo(HcStruc, UHCI_STATUS_REG)) & UHC_HC_HALTED);
    if (!((HcByteReadHcIo(HcStruc, UHCI_STATUS_REG)) & UHC_HC_HALTED)) {
        return USB_ERROR;
    }

    //
    // Reset the host controller
    //
    HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG, UHC_GLOBAL_RESET);
  
    FixedDelay(10 * 1000);    // Recommended 10msec delay, UHCI Spec, p.12, GRESET description
  
    HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG, 0);

    //
    // Memory has been allocated in AMIUHCD
    //
    if (!HcStruc->FrameList) {
        return USB_ERROR;
    }

    USB_InitFrameList(HcStruc, UHCI_TERMINATE);

    //
    // Program frame list pointer to the HC
    //
    USB_DEBUG(DEBUG_HC, "Frame list pointer : %x\n", HcStruc->FrameList);
    HcDwordWriteHcIo(HcStruc, UHCI_FRAME_LIST_BASE, (UINT32)(UINTN)HcStruc->FrameList);

    USB_DEBUG(DEBUG_HC, "Uhci_StartTDSchedule\n");

    //
    // Start the TD schedule
    //
    if (Uhci_StartTDSchedule(HcStruc) != USB_SUCCESS) {
        return USB_ERROR;
    }


    //
    // Enable hardware interrupt generation by programming legacy registers
    //
    UhciEnableLegacyReg(HcStruc);

    //
    // Start the host controller by setting the run and configure bit
    //
    HcWordWriteHcIo(HcStruc, UHCI_COMMAND_REG,
        UHC_HOST_CONTROLLER_RUN |
        UHC_CONFIGURE_FLAG |
        UHC_MAX_PACKET_64_BYTE);

    //
    // Enable interrupt generation
    //
//  WordWriteIO((UINT16)(wIOAddr + UHCI_INTERRUPT_ENABLE), (UHC_IOC_ENABLE | UHC_TIMEOUT_CRC_ENABLE));
    HcWordWriteHcIo(HcStruc, UHCI_INTERRUPT_ENABLE, UHC_IOC_ENABLE);

    HcStruc->HcFlag |= HC_STATE_RUNNING;

    // Set USB_FLAG_DRIVER_STARTED flag when HC is running.
    if (!(gUsbData->UsbStateFlag & USB_FLAG_DRIVER_STARTED)) {
        gUsbData->UsbStateFlag |= USB_FLAG_DRIVER_STARTED;
    }

    return USB_SUCCESS;
}


/**
    This API function is called to stop the UHCI controller. The input to the
    routine is the pointer to the HC structure that defines this host controller.

    @param HcStruc         Pointer to the host controller structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Uhci_Stop(
    HC_STRUC* HcStruc
)
{
    UINT16      LegSupReg;
    UINT16      Index;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    //
    // Disable hardware interrupt generation by programming legacy registers
    //
    if (!(HcStruc->HcFlag & HC_STATE_EXTERNAL)) {
        LegSupReg = (UINT16)HcReadPciReg(HcStruc, USB_UHCI_REG_LEGSUP);

        //
        // Disable generation of SMI/IRQ and clear status bits
        //
        LegSupReg = (UINT16)(LegSupReg & ~(BIT4));
        HcWordWritePciReg(HcStruc, USB_UHCI_REG_LEGSUP, LegSupReg);
    }

    //
    // Disable the host controller interrupt generation
    //
    Uhci_DisableInterrupts(HcStruc);

    // Disconnect all devices  
    USB_DisconnectDevice(HcStruc, HcStruc->HcNumber | BIT7, 1);
    USB_DisconnectDevice(HcStruc, HcStruc->HcNumber | BIT7, 2);

    //
    // Stop the host controller
    //
    if (!UhciIsHalted(HcStruc)) {
        //
        // Clear HC run bit
        //
        HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG,
            HcByteReadHcIo(HcStruc, UHCI_COMMAND_REG) & ~(UHC_HOST_CONTROLLER_RUN));

        //
        // Check whether the host controller is halted (check for 50 ms)
        //
        for (Index = 0; Index < 500; Index++) {
            if ((HcByteReadHcIo(HcStruc, UHCI_STATUS_REG)) & UHC_HC_HALTED) {
                break;
            }
            FixedDelay(100);      // 100 us delay
        }
    }
    ASSERT((HcByteReadHcIo(HcStruc, UHCI_STATUS_REG)) & UHC_HC_HALTED);

    // Reset the host controller
    HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG, UHC_GLOBAL_RESET);
    // Recommended 10msec delay, UHCI Spec, p.12, GRESET description
    FixedDelay(10 * 1000);
    HcByteWriteHcIo(HcStruc, UHCI_COMMAND_REG, 0);

    //
    // Clear the frame list pointers
    //
    USB_InitFrameList(HcStruc, UHCI_TERMINATE);

    //
    // Disable and free the TD schedule data structures
    //
    Uhci_StopTDSchedule(HcStruc);

    //
    // Set the HC state to stopped
    //
    HcStruc->HcFlag &= ~(HC_STATE_RUNNING);

    CheckBiosOwnedHc();

    return USB_SUCCESS;
}


/**
    This API function is called to enumerate the root hub ports in the UHCI
    controller. The input to the routine is the pointer to the HC structure
    that defines this host controller

    @param HcStruc   Pointer to the HC_STRUC structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Uhci_EnumeratePorts(
    HC_STRUC* HcStruc
)
{
    UINT8       HcNumber;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }


    //
    // Check whether USB host controllers are accessible to aVOID system 
    // hang in ports enumeration.
    //
    if (HcByteReadHcIo(HcStruc, 0) == 0xFF) {
        return USB_ERROR;
    }

    //
    // Check whether enumeration is already began
    //
    if (gUsbData->EnumFlag == TRUE) {
        return USB_SUCCESS;
    }

    gUsbData->EnumFlag = TRUE;
    HcNumber = (UINT8)(HcStruc->HcNumber | BIT7);

    //
    // Process Port#1 and clear Port#1 status bit
    //
    if ((HcWordReadHcIo(HcStruc, UHCI_PORT1_CONTROL) & (UHC_CONNECT_STATUS_CHANGE | 
      UHC_CONNECT_STATUS)) == UHC_CONNECT_STATUS_CHANGE) {
      HcWordWriteHcIo(HcStruc, UHCI_PORT1_CONTROL, UHC_CONNECT_STATUS_CHANGE);
    }
    
    USBCheckPortChange(HcStruc, HcNumber, 1);
    
    HcWordWriteHcIo(HcStruc, UHCI_PORT1_CONTROL, 
        HcWordReadHcIo(HcStruc, UHCI_PORT1_CONTROL));

    //
    // Process Port#2 and clear Port#2 status bit
    //
    if ((HcWordReadHcIo(HcStruc, UHCI_PORT2_CONTROL) & (UHC_CONNECT_STATUS_CHANGE | 
      UHC_CONNECT_STATUS)) == UHC_CONNECT_STATUS_CHANGE) {
      HcWordWriteHcIo(HcStruc, UHCI_PORT2_CONTROL, UHC_CONNECT_STATUS_CHANGE);
    }
    
    USBCheckPortChange(HcStruc, HcNumber, 2);
    
    HcWordWriteHcIo(HcStruc, UHCI_PORT2_CONTROL, 
        HcWordReadHcIo(HcStruc, UHCI_PORT2_CONTROL));

    gUsbData->EnumFlag = FALSE;

    return USB_SUCCESS;
}


/**
    This API function is called to disable the interrupts generated by the UHCI
    host controller. The input to the routine is the pointer to the HC structure
    that defines this host controller.

     @param HcStruc         Pointer to the HCStruc structure

     @retval USB_SUCCESS    Success
     @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Uhci_DisableInterrupts(
    HC_STRUC* HcStruc
)
{
    UINT8   IntEnReg;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    IntEnReg = HcByteReadHcIo(HcStruc, UHCI_INTERRUPT_ENABLE);
    IntEnReg &= ~(UHC_IOC_ENABLE);
    HcByteWriteHcIo(HcStruc, UHCI_INTERRUPT_ENABLE, IntEnReg);

    return USB_SUCCESS;
}


/**
    This function enables the HC interrupts

    @param HcStruc         Pointer to the HCStruc structure

    @retval USB_SUCCESS    Success
    @retval USB_ERROR      Failure

**/

UINT8
EFIAPI
Uhci_EnableInterrupts(
    HC_STRUC* HcStruc
)
{
    return USB_SUCCESS;
}


/**
    This function is called when the USB interrupt bit is set. This function
    will parse through the TDs and QHs to find out completed TDs and call
    their respective callback functions.

    @param  HcStruc      Pointer to the HCStruc structure

    @retval USB_ERROR    Interrupt not processed
    @retval USB_SUCCESS  Interrupt processed
**/

UINT8
EFIAPI
Uhci_ProcessInterrupt(
    HC_STRUC    *HcStruc
)
{
//    UINT16  LegSupReg = 0;
    UINT16  UsbSts = 0;
    EFI_STATUS  Status;
    UINT8   LegacyEnable;

    Status = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(Status)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
      return USB_ERROR;
    }


    if (!(HcStruc->HcFlag & HC_STATE_EXTERNAL)) {
//     LegSupReg = (UINT16)HcReadPciReg(HcStruc, USB_UHCI_REG_LEGSUP);
//     if (!(LegSupReg & BIT4)) {
//       return USB_ERROR;
//     }
            LegacyEnable = UhciCheckLegacyReg(HcStruc);
            if (LegacyEnable == FALSE) return USB_ERROR;
    }


    //
    // Check whether the controller is still under BIOS control
    // Read the frame list base address and compare with stored value
    //
    if (((UINTN)HcDwordReadHcIo(HcStruc, UHCI_FRAME_LIST_BASE) & 0xFFFFF000) != 
        (UINTN)HcStruc->FrameList) {

        if (!(HcStruc->HcFlag & HC_STATE_EXTERNAL)) {
            // Disable the SMI on IRQ enable bit
            //HcWordWritePciReg(HcStruc, USB_UHCI_REG_LEGSUP, LegSupReg & ~BIT4);
            UhciDisableLegacyReg(HcStruc);
        }

        return USB_ERROR; // Control is not with us anymore
    }

    UsbSts = HcWordReadHcIo(HcStruc, UHCI_STATUS_REG);

    if (UsbSts & UHC_HC_HALTED) {
      return USB_ERROR;
    }

    if (UsbSts & UHC_USB_INTERRUPT) {
      HcWordWriteHcIo(HcStruc, UHCI_STATUS_REG, UsbSts);
      UhciProcessFrameList(HcStruc);
    }
    if ( (HcStruc->HcFlag & HC_STATE_EXTERNAL)||(gUsbDataList->UhciRootHubHcStruc != HcStruc)) {
        UhciRootHubQhCallBack(HcStruc, NULL, NULL, NULL, 0);
    }

    return  USB_SUCCESS;
}


/**
    This function returns the port connect status for the root hub port

    @param HcStruc          Pointer to the HCStruc structure
    @param PortNum          Port in the HC whose status is requested
    @param ClearChangeBits  TRUE: Clear change status bits

    @retval PortStatus      return Port status

**/

UINT32
EFIAPI
Uhci_GetRootHubStatus(
    HC_STRUC*   HcStruc,
    UINT8       PortNum,
    BOOLEAN     ClearChangeBits
)
{
    UINT32  PortStatus;
    UINT16  PortTemp;
    UINT16  PortStatusOffset = (PortNum << 1) + UHCI_PORT1_CONTROL - 2;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    PortStatus = USB_PORT_STAT_DEV_OWNER;

    //
    // Read the port status
    //
    PortTemp = HcWordReadHcIo(HcStruc, PortStatusOffset);
    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "UHCI port[%d] status: %04x\n", PortNum, PortTemp);

    //
    // Check for port connect status
    //
    if (PortTemp & UHC_CONNECT_STATUS) {
        PortStatus |= USB_PORT_STAT_DEV_CONNECTED;

        //
        // Identify the speed of the device (full or low speed)
        //
        if (PortTemp & UHC_LOW_SPEED_ATTACHED) {
            PortStatus |= USB_PORT_STAT_DEV_LOWSPEED;
        }
        else {
            PortStatus |= USB_PORT_STAT_DEV_FULLSPEED;
        }

       if (PortTemp & UHC_PORT_ENABLE) {
         PortStatus |= USB_PORT_STAT_DEV_ENABLED;
       }
    }

    //
    // Check for connect status change
    //
    if (PortTemp & UHC_CONNECT_STATUS_CHANGE) {
        PortStatus |= USB_PORT_STAT_DEV_CONNECT_CHANGED;
        if (ClearChangeBits == TRUE) {
            HcWordWriteHcIo(HcStruc, PortStatusOffset, UHC_CONNECT_STATUS_CHANGE);     //(EIP61385+)
        }
    }
    if (PortTemp & UHC_PORT_RESET) {
        PortStatus |= USB_PORT_STAT_DEV_RESET;
    }
    if (PortTemp & UHC_PORT_SUSPEND) {
        PortStatus |= USB_PORT_STAT_DEV_SUSPEND;
    }
    if (PortTemp & UHC_PORT_ENABLE_CHANGE) {
        PortStatus |= USB_PORT_STAT_DEV_ENABLE_CHANGED;
    }

    return PortStatus;
}


/**
    This function disables the root hub of the UHCI controller.

    @param HcStruc        Pointer to the host controller structure
    @param PortNum        Port in the HC to disable

    @retval USB_SUCCESS   Success to disable the root hub port.
    @retval Others        Fail to disable the root hub port.

**/

UINT8
EFIAPI
Uhci_DisableRootHub(
    HC_STRUC*   HcStruc,
    UINT8       PortNum
)
{
    UINT16  PortStatusOffset = (PortNum << 1) + UHCI_PORT1_CONTROL - 2;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    //
    // Reset the enable bit
    //
    HcWordWriteHcIo(HcStruc, PortStatusOffset,
        (UINT16)(HcWordReadHcIo(HcStruc, PortStatusOffset) & (~UHC_PORT_ENABLE)));

    return USB_SUCCESS;
}


/**
    This function enables the root hub port specified

    @param HcStruc        Pointer to the host controller structure
    @param PortNum        Port in the HC to enable

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_EnableRootHub (
    HC_STRUC    *HcStruc,
    UINT8       PortNum)
{
    UINT16  PortStatus;
    UINT16  PortStatusOffset = (PortNum << 1) + UHCI_PORT1_CONTROL - 2;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }
    
    PortStatus = HcWordReadHcIo(HcStruc, PortStatusOffset);

    //
    // Set the enable & reset bit, preserve Connect Status Change bit
    //
    PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    HcWordWriteHcIo(HcStruc, PortStatusOffset, PortStatus | UHC_PORT_RESET);

    //
    // Wait for 10ms
    //
    FixedDelay(10 * 1000);  // 10msec delay

    //
    // Clear the reset bit and set the enable, preserve Connect Status Change bit
    //
    PortStatus = HcWordReadHcIo(HcStruc, PortStatusOffset);
    PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    HcWordWriteHcIo(HcStruc, PortStatusOffset, PortStatus & (~UHC_PORT_RESET));

    // Wait 1 ms for stabilize the port status
    FixedDelay(1 * 1000);        // 1 ms delay

    // Clear Connect Status Change bit and Port Enable Change bit
    HcWordWriteHcIo(HcStruc, PortStatusOffset, HcWordReadHcIo(HcStruc, PortStatusOffset));

    //
    // Set the enable bit
    //
    PortStatus = HcWordReadHcIo(HcStruc, PortStatusOffset);
    PortStatus &= ~(UHC_CONNECT_STATUS_CHANGE | UHC_PORT_ENABLE_CHANGE);
    HcWordWriteHcIo(HcStruc, PortStatusOffset, PortStatus | UHC_PORT_ENABLE);

    //
    // Wait for 100ms
    //
    //FixedDelay(gUsbDataList->UsbTimingPolicy->UhciPortEnable * 1000);        // 100msec delay

    return USB_SUCCESS;
}

/**
    This function resets the UHCI HC root hub port

    @param HcStruc        Pointer to the host controller structure
    @param PortNum        Port in the HC to reset

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_ResetRootHub (
    HC_STRUC*  HcStruc,
    UINT8    PortNum)
{
    return USB_SUCCESS;
}


/**
    This function suspend the UHCI HC.
    
    @param HcStruc        Pointer to the host controller structure


    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure
**/

UINT8
EFIAPI
Uhci_GlobalSuspend(
    HC_STRUC*  HcStruc
)
{

    UINT16      UhciCommand;
    UINT16      UhciStatus;
    UINT32      Count;
    EFI_STATUS  EfiStatus;

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    UhciCommand = HcWordReadHcIo(HcStruc, UHCI_COMMAND_REG);
    UhciCommand &= ~UHC_HOST_CONTROLLER_RUN;
    HcWordWriteHcIo(HcStruc, UHCI_COMMAND_REG, UhciCommand);
    for (Count = 0; Count < 1024; Count++) {
        UhciStatus = HcWordReadHcIo(HcStruc, UHCI_STATUS_REG);
        if (UhciStatus & UHC_HC_HALTED) {
            break;
        }
        FixedDelay(1 * 1000);
    }
    
    HcWordWriteHcIo(HcStruc, UHCI_INTERRUPT_ENABLE, UHC_RESUME_ENABLE);
    
    UhciStatus = HcWordReadHcIo(HcStruc, UHCI_STATUS_REG);
    UhciStatus |= 0x1F;
    HcWordWriteHcIo(HcStruc, UHCI_STATUS_REG, UhciStatus);
  
    UhciCommand = HcWordReadHcIo(HcStruc, UHCI_COMMAND_REG);
    UhciCommand |= UHC_ENTER_SUSPEND;
    HcWordWriteHcIo(HcStruc, UHCI_COMMAND_REG, UhciCommand);
    FixedDelay(50 * 1000);
    
    HcStruc->HcFlag &= ~(HC_STATE_RUNNING);
    HcStruc->HcFlag |= HC_STATE_SUSPEND;
    
    return  USB_SUCCESS;
}


/**
    Set Uhci SMI Control

    @param HcStruc          Pointer to the HcStruc structure
    @param Enable           TRUE : Enable
    
    @retval USB_SUCCESS     Success
    @retval USB_ERROR       Failure
**/
UINT8
EFIAPI
UhciSmiControl(
    HC_STRUC* HcStruc,
    BOOLEAN Enable
)
{
    UINT16      LegSupReg;
    EFI_STATUS  EfiStatus;

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

    LegSupReg = (UINT16)HcReadPciReg(HcStruc, USB_UHCI_REG_LEGSUP);

    if (Enable == TRUE) {
        //
        // Eisable generation of SMI/IRQ and clear status bits
        //
        LegSupReg = (UINT16)(LegSupReg | BIT4) & ~BIT13;
        HcWordWritePciReg(HcStruc, USB_UHCI_REG_LEGSUP, LegSupReg);
    } else {
        //
        // Disable generation of SMI/IRQ and clear status bits
        //
        LegSupReg = (UINT16)(LegSupReg & ~(BIT4));
        HcWordWritePciReg(HcStruc, USB_UHCI_REG_LEGSUP, LegSupReg);
    }

    return USB_SUCCESS;
}
                                        
/**
    This function executes a transfer and waits for the completion of 
    the transfer, and returns the transfer results.

    @param HcStruc              Pointer to the HcStruc structure
    @param TransferQh           Pointers to the first data TD and last data TD in the TD list

    @retval BytesTransferred    Return value is the size of transferred data, Bytes

**/
UINT32
UhciExecuteTransfer (
    HC_STRUC    *HcStruc,
    UHCI_QH     *TransferQh
)
{
    UINT32    Timeout = gUsbData->UsbReqTimeOutValue * 100; // *100, makes it number of 10 usec units
    BOOLEAN   InfiniteLoop = (Timeout == 0);

    TransferQh->ActiveFlag = TRUE;
    UhciAddQhToFrameList(HcStruc, TransferQh);

    while (InfiniteLoop || Timeout--) {
        UhciProcessQh(HcStruc, TransferQh);
        if (TransferQh->ActiveFlag == FALSE) {
            break;
        }

        FixedDelay(10);  // 10 microseconds
    }

    UhciRemoveQhFromFrameList(HcStruc, TransferQh);
    UhciProcessQh(HcStruc, TransferQh);
    
    if (TransferQh->ActiveFlag) {
        USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "UHCI Time-Out\n");
    }

    return TransferQh->BytesTransferred;
}
 
/**
    This function executes a device request command transaction on the USB. One
    setup packet is generated containing the device request parameters supplied
    by the caller.  The setup packet may be followed by data in or data out packets
    containing data sent from the host to the device or vice-versa. This function
    will not return until the request either completes successfully or completes in
    error (due to time out, etc.)

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


    @retval BytesTransferred      Number of bytes transferred


    @note  
  Do not use USB_SUCCESS or USB_ERROR as returned values

**/

UINT16
EFIAPI
Uhci_ControlTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
)
{
    UINT16      Packet;
    UINT32      Temp;
    UINT32      Data;

    DEV_REQ     *DevReq;
    UHCI_TD     *SetupTd = NULL;
    UHCI_TD     *DataTds = NULL;
    UHCI_TD     *StatusTd = NULL;
    UHCI_TD     *LastTd = NULL;
    UHCI_TD     *CurrentTd = NULL;
    UHCI_QH     *CtrlQh;
    UINT16      NumDataTds = 0;
    UINT16      BytesRemaining;
    UINT16      BytesTransferred;
    UINT8       DataToggle;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
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
                USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Uhci ControlTransfer Invalid Pointer, Buffer is in SMRAM.\n");
                return 0;
            }
        }
        gCheckUsbApiParameter = FALSE;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }

    if (UhciIsHalted(HcStruc)) {
      return 0;
    }
    
    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

    gUsbData->UsbLastCommandStatus &= ~( USB_CONTROL_STALLED );
    DevInfo->UsbLastCommandStatusExtended = 0;

    //
    // Allocate TDs for control setup and control status packets
    //
    SetupTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (SetupTd == NULL) {
        return 0;
    }

    //
    // Build the device request in the data area of the control setup TD
    //
    DevReq = (DEV_REQ*)SetupTd->DataArea;
    DevReq->RequestType  = Request;
    DevReq->Value        = Value;
    DevReq->Index        = Index;
    DevReq->DataLength   = Length;

    //
    // Temp will contain the device address and endpoint shifted and ready to go
    // into the TDs' token field.
    // 10:0] = Dev. Addr & Endpoint
    // [18:8] = Dev. Addr & Endpoint
    //
    Temp = ((UINT32)(DevInfo->DeviceAddress)) << 8;

    //
    // Fill in various fields in the control setup TD.
    // The LinkPointer field will point to the control data TD if data will
    // be sent/received or to the control status TD if no data is expected.
    // The ControlStatus field will be set to active and interrupt on complete.
    // The Token field will contain the packet size (size of DeviceRequest
    // struc), the device address, endpoint, and a setup PID.
    // The BufferPointer field will point to the TD's DataArea buffer which
    // was just initialized to contain a DeviceRequest struc.
    // The CSReloadValue field will contain 0 because this is a "one shot" packet.
    // The pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // The ActiveFlag field will be set to TRUE.
    //

    //
    // 11/01/10 for HI/LO/FULL
    //
    Data = (((UINT32)DevInfo->EndpointSpeed) & 1) << 26;

    Data |= (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);


    SetupTd->ControlStatus = Data;

    Data = Temp |
        ((UINT32)UHCI_TD_SETUP_PACKET |
        ((UINT32)(sizeof(DEV_REQ) - 1) << 21));

    //
    // Set PID=Setup, and MaxLen
    //
    SetupTd->Token         = Data;
    SetupTd->BufferPtr     = (UINT32)(UINTN)SetupTd->DataArea;
    SetupTd->CSReload      = 0;
    SetupTd->ActiveFlag   = 1;

    LastTd = SetupTd;
    //
    // Fill in various fields in the control data TD.
    // Enough control data TDs must be initialized to handle the amount of
    // data expected.  The length of the data transfer is currently in wLength.
    // LinkPointer field will be set to the next data TD or the status TD.
    // ControlStatus field will be se to active and interrupt on complete.
    // Token field will contain the data transfer size (still in wLength), device
    // address (in DevInfo), endpoint (in dTemp), and an in or out PID
    // (in wReqType).
    // BufferPointer field will point to the data buffer passed in by the
    // caller (currently in FpBuffer).
    // CSReloadValue field will contain 0 because this is a "one shot" packet.
    // pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // ActiveFlag field will be set to TRUE.
    //
    if (Length) {
        NumDataTds = Length / DevInfo->Endp0MaxPacket;
        if (Length % DevInfo->Endp0MaxPacket) {
            NumDataTds++;
        }

        DataTds = USB_MemAlloc(GET_MEM_BLK_COUNT(NumDataTds * sizeof(UHCI_TD)));
        if (DataTds == NULL) {
            USB_MemFree(SetupTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
            return 0;
        }

        CurrentTd = DataTds;

        DataToggle  = 1;
        BytesRemaining = Length;
 
        //
        // Allocate one more TD to be used either for more data or for TD Status
        //
        HcDmaMap(HcStruc, (UINT8)(Request & BIT7), Buffer, Length, 
                      &BufPhyAddr, &BufferMapping);
        do {
            //
            // 11/01/10 for HI/LO/FULL
            //
            Data = (((UINT32)(DevInfo->EndpointSpeed) & 1) << 26);
            Data = Data |
                (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
            if(Request & BIT7) {
                Data |= UHCI_TD_SHORT_PACKET_DETECT;
            }
            CurrentTd->ControlStatus = Data;
            CurrentTd->BufferPtr = (UINT32)(UINTN)BufPhyAddr;
            Packet = (UINT16)((BytesRemaining > (DevInfo->Endp0MaxPacket)) ?
                                DevInfo->Endp0MaxPacket : BytesRemaining);
            //
            // Packet size is valid
            //
            BytesRemaining = (UINT16)(BytesRemaining - Packet);
            BufPhyAddr = BufPhyAddr + Packet;
            --Packet;

            //
            // [18:8]=Dev. addr & endp
            //
            Data = Temp | (((UINT32)Packet) << 21);
            Data = (Data & 0xFFFFFF00) | UHCI_TD_OUT_PACKET;

            if (Request & BIT7) {
                Data = (Data & 0xFFFFFF00) | UHCI_TD_IN_PACKET;
            }
            if (DataToggle & 1) {
                Data = Data | UHCI_TD_DATA_TOGGLE;  // Make packet into a data 1
            }
            CurrentTd->Token = Data;
            CurrentTd->CSReload = 0;
            CurrentTd->ActiveFlag = 1;

            LastTd->LinkPtr = (UINT32)((UINTN)CurrentTd | UHCI_VERTICAL_FLAG);
            LastTd = CurrentTd;
            CurrentTd++;
            
            DataToggle  ^=  1;
        } while (BytesRemaining);  // End the data TD list
    }
    //
    // Fill in various fields in the TD control status.
    // LinkPointer field will point to TERMINATE.
    // ControlStatus field will be set to active and interrupt on complete.
    // Token field will contain the packet size (0), the device address,
    // endpoint, and a setup PID with opposite data direction as that defined
    // in the request type (wReqType).
    // BufferPointer field will point to the TD's DataArea buffer even though
    // we are not expecting any data transfer.
    // CSReloadValue field will contain 0 because this is a "one shot" packet.
    // pCallback will be set to point to the UHCI_ControlTDCallback routine.
    // ActiveFlag field will be set to TRUE.
    //
    StatusTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (StatusTd == NULL) {
        return 0;
    }

    LastTd->LinkPtr = (UINT32)((UINTN)StatusTd | UHCI_VERTICAL_FLAG);
    //LastTd = StatusTd;
    StatusTd->LinkPtr  = UHCI_TERMINATE;
    Data = (((UINT32)(DevInfo->EndpointSpeed) & 1) << 26);

    Data = Data | (UINT32)(UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);

    StatusTd->ControlStatus = Data;
    Data = Temp;
    Data = (Data & 0xFFFFFF00) | (UINT32)UHCI_TD_OUT_PACKET;
    if ((Request & BIT7) == 0) {
        Data = (Data & 0xFFFFFF00) | (UINT32)UHCI_TD_IN_PACKET;
    }
    Data |= (UHCI_TD_DATA_TOGGLE | ((UINT32)UHCI_TD_ACTUAL_LENGTH << 21));
    StatusTd->Token = Data;
    Data = (UINT32)(UINTN)StatusTd->DataArea;
    StatusTd->BufferPtr = Data;
    StatusTd->CSReload = 0;
    StatusTd->ActiveFlag = 1;
    //
    // Now put the control setup, data and status into the HC's schedule by
    // pointing QhControl's link pointer to control setup TD.
    // This will cause the HC to execute the transaction in the next active frame.

    CtrlQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (CtrlQh == NULL) {
        return 0;
    }

    UhciInitQh(CtrlQh);
    CtrlQh->ElementPtr = (UINT32)(UINTN)SetupTd;
    CtrlQh->CurrentTd = SetupTd;
    CtrlQh->Type = Control;
    CtrlQh->FirstTd = SetupTd;

    // Wait till transfer complete
    BytesTransferred = (UINT16)UhciExecuteTransfer(HcStruc, CtrlQh);

    // Calculate the transferred length
    BytesTransferred -= (((SetupTd->ControlStatus & UHCI_TD_ACTUAL_LENGTH) + 1) & 0x7FF);
 
    // Save error information in global variable
    DevInfo->UsbLastCommandStatusExtended = 
        (CtrlQh->CurrentTd->ControlStatus & UHCI_TD_STATUS_FIELD) >> 17;

    if (CtrlQh->CurrentTd->ControlStatus & UHCI_TD_STALLED ){
        gUsbData->UsbLastCommandStatus |= USB_CONTROL_STALLED;
        BytesTransferred = 0;
    }

    if (Length) {
        HcDmaUnmap(HcStruc, BufferMapping);
    }

    USB_MemFree(SetupTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (DataTds) {
        USB_MemFree(DataTds, GET_MEM_BLK_COUNT(NumDataTds * sizeof(UHCI_TD)));
    }
    USB_MemFree(StatusTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    USB_MemFree(CtrlQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return BytesTransferred;
}   // Uhci_ControlTransfer


/**
    This function creates a chain of two TDs for bulk data transfer. It fills
    in the following fields in TD:
    pLinkPtr - NextTd address
    dToken   - All bits except length and data toggle

    @param  BulkDataTd0     1st TD in the chain
    @param  TokenData       Data for dToken
    @param  NumBulkTds      # of bulk TDs
    
    @retval None

**/

VOID
Uhci_InitBulkTdCommon (
    UHCI_TD *BulkDataTd0,
    UINT32  TokenData,
    UINT16  NumBulkTds
)
{
    UINT16  Index;
    UHCI_TD *Td0 = BulkDataTd0;
    UHCI_TD *Td1 = Td0;
    UINT16  NumTd = NumBulkTds*2;

    for (Index = 0; Index < NumTd; Index++)
    {
        Td0 = Td1;
        Td0->Token = TokenData;
        Td1 = (UHCI_TD*)((UINTN)Td0 + sizeof(UHCI_TD));
        Td0->LinkPtr = (UINT32)(UINTN)Td1 | UHCI_VERTICAL_FLAG;
    }
    // Terminated later in Uhci_InitBulkDataTds
}


/**
    This function initializes the fields in bulk data TD list that remain after
  Uhci_InitBulkTdCommon:
                  - Data buffer pointer
                  - Data length
                  - Data toggle (DAT0/DAT1)

    @param  BulkDataTd      Bulk data TD 
    @param  MaxPkt          Max packet
    @param  EndpointSpeed   Endpoint speed
    @param  Address         Address
    @param  DatToggle       DatToggle
    @param  DatToggle       DatToggle
    @param  BytesRemaining  Bytes Remaining
    @param  NumBulkTds      Number of bulk TDs
    
    @retval Td              Bulk data TD 

**/

UHCI_TD*
Uhci_InitBulkDataTds(
    IN UHCI_TD      *BulkDataTd,
    IN UINT16       MaxPkt,
    IN UINT32       EndpointSpeed,
    IN OUT UINT32   *Address,
    IN OUT UINT8    *DatToggle,
    IN OUT UINT32   *BytesRemaining,
    IN UINT16       NumBulkTds
)
{
    UINT16  Count;
    UINT32  Length;
    UHCI_TD *Td = BulkDataTd;
    UINT32  Addr = *Address;
    UINT8   Toggle = *DatToggle;
    BOOLEAN TheLastTd = FALSE;

    for (Count = 0; Count < NumBulkTds; Count++)
    {
        Length = *BytesRemaining;

        if (Length > (UINT32)MaxPkt)
        {
            Length = (UINT32)MaxPkt;
        }
        else
        {
            TheLastTd = TRUE;
        }
        Td->Token &= 0x1FFFFF;
        Td->Token |= (Length - 1) << 21;
    
        Td->Token &= ~UHCI_TD_DATA_TOGGLE;      // Make packet go into DAT0
        if (Toggle == 1)
        {
            Td->Token |= UHCI_TD_DATA_TOGGLE;   // Make packet go into DAT1
        }
    
        Td->ControlStatus = EndpointSpeed |
                    (UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE);
        if ((Td->Token & UHCI_TD_PACKET_ID) == UHCI_TD_IN_PACKET) {
            Td->ControlStatus |= UHCI_TD_SHORT_PACKET_DETECT;
        }

        Td->BufferPtr = Addr;
        Addr += MaxPkt;
        Toggle ^= 1;
        Td = (UHCI_TD*)((UINTN)Td + sizeof(UHCI_TD));
        *BytesRemaining -= Length;

        if (TheLastTd) break;
    }

    Td = (UHCI_TD*)((UINTN)Td - sizeof(UHCI_TD));
    Td->LinkPtr = UHCI_TERMINATE;

    *Address = Addr;
    *DatToggle = Toggle;

    return Td;
}


/**
    This function executes a bulk transaction on the USB. The transfer may be
    either DATA_IN or DATA_OUT packets containing data sent from the host to
    the device or vice-versa. This function wil not return until the request
    either completes successfully or completes with error (due to time out, etc.)

    @param HcStruc     Pointer to HCStruc of the host controller
    @param DevInfo     DeviceInfo structure (if available else 0)
    @param XferDir     Transfer direction
                       Bit 7: Data direction
                              0 Host sending data to device
                              1 Device sending data to host
                       Bit 6-0 : Reserved
    @param Buffer      Buffer containing data to be sent to the device or buffer to be
                       used to receive data value in Segment:Offset format
    @param Length      Length request parameter, number of bytes of data to be transferred
                       in or out of the host controller

    @retval BytesTransferred    Amount of data transferred

**/

UINT32
EFIAPI
Uhci_BulkTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length
)
{
    UINT16      MaxPkt;
    UINT8       Endp;
    UINT32      Data;
    UINT8       DatToggle;
    UINT32      TransferError;
    UHCI_QH     *BulkQh;
    UHCI_TD     *BulkDataTd;
    UHCI_TD     *NextBulkDataTd;
    UHCI_TD     *BulkDataTd0;
    UHCI_TD     *BulkDataTd1;
    UINT16      NumAllocTDs;
    UINT16      NumBulkTDs;
    UINT32      BytesRemaining;
    UINT32      BytesTransferred;
    UINT32      BytesTransferredNow;
    UINT32      Address;
    UINT32      Eps;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
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
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Uhci BulkTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }

    if (UhciIsHalted(HcStruc)) {
      return 0;
    }
    
    if (!VALID_DEVINFO( DevInfo)) {
        return 0;
    }

    if (Length == 0) {
        return 0;
    }

    // Clear HW source of error
    gUsbData->UsbLastCommandStatus &= ~(USB_BULK_STALLED | USB_BULK_TIMEDOUT );
    DevInfo->UsbLastCommandStatusExtended = 0;
    //
    // Get Bulk IN/OUT enpoint number, data sync value & max packet size
    // Store the appropriate max packet size and endpoint number
    // in the local variables
    //
    MaxPkt = (XferDir & BIT7)? DevInfo->BulkInMaxPkt : DevInfo->BulkOutMaxPkt;

    if (MaxPkt == 0) {
        return 0;
    }

    Endp = (XferDir & BIT7)? DevInfo->BulkInEndpoint : DevInfo->BulkOutEndpoint;

    //
    // For multiple LUN devices toggle is maintained by LUN0
    //
    DatToggle = UsbGetDataToggle(DevInfo, Endp | XferDir);

    //
    // Form TD token data, less the transfer length and toggle information
    //
    Data = (UINT32)Endp << 7;
    Data = (Data | DevInfo->DeviceAddress) << 8;
    Data = (XferDir & BIT7)? Data | UHCI_TD_IN_PACKET : Data | UHCI_TD_OUT_PACKET;

    BulkQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (BulkQh == NULL) {
        return 0;
    }

    BulkQh->Type = Bulk;

    // Allocate data TDs.
    NumBulkTDs = gUsbData->FullSpeedMaxBulkDataSizePerFrame/MaxPkt;
    ASSERT(NumBulkTDs != 0);

    NumAllocTDs = NumBulkTDs*2;

    BulkDataTd0 = (UHCI_TD*)USB_MemAlloc(GET_MEM_BLK_COUNT(NumAllocTDs * sizeof(UHCI_TD)));
    ASSERT(BulkDataTd0 != NULL);

    Uhci_InitBulkTdCommon (BulkDataTd0, Data, NumBulkTDs);

    HcDmaMap(HcStruc, XferDir, Buffer, Length, &BufPhyAddr, &BufferMapping);

    BulkDataTd1 = (UHCI_TD*)((UINTN)BulkDataTd0 + (NumBulkTDs * sizeof(UHCI_TD)));

    BulkDataTd = BulkDataTd0;
    NextBulkDataTd = BulkDataTd1;
    BytesRemaining = Length;
    BytesTransferred = 0;
    BytesTransferredNow = 0;
    Address = (UINT32)(UINTN)BufPhyAddr;
    TransferError = 0;
    Eps = ((UINT32)(DevInfo->EndpointSpeed) & 1) << 26;

    Uhci_InitBulkDataTds(
        BulkDataTd, MaxPkt, Eps, &Address, &DatToggle, &BytesRemaining, NumBulkTDs);

    do {
        // Start the transfer by adding TD in the bulk queue head
        UhciInitQh(BulkQh);
        BulkQh->ElementPtr = (UINT32)(UINTN)BulkDataTd;
        BulkQh->CurrentTd = BulkDataTd;
        BulkQh->FirstTd = BulkDataTd;

        // Initialize the next TD block and wait for the current one to complete.
        // In case MaxPkt is 64 Bytes, we have approx. NumBulkTDs*50mcs for this.
        if (BytesRemaining != 0) {
            Uhci_InitBulkDataTds(
                NextBulkDataTd, MaxPkt, Eps, &Address, &DatToggle, &BytesRemaining, NumBulkTDs);
        }

        // Wait till BulkDataTd is complete, check for errors
        BytesTransferredNow = UhciExecuteTransfer(HcStruc, BulkQh);

        DatToggle = BulkQh->DataToggle;
        TransferError = (BulkQh->CurrentTd->ControlStatus & UHCI_TD_STATUS_FIELD) >> 17;
        if (TransferError) {
            break;
        }
        BytesTransferred += BytesTransferredNow;

        NextBulkDataTd = BulkDataTd;

        BulkDataTd = (BulkDataTd == BulkDataTd0)? BulkDataTd1 : BulkDataTd0;

    } while ((BytesTransferred < Length) && !BulkQh->ShortPacketDetected);

    UsbUpdateDataToggle(DevInfo, Endp | XferDir, DatToggle);
    DevInfo->UsbLastCommandStatusExtended = TransferError;
    if (BulkQh->CurrentTd->ControlStatus & UHCI_TD_STALLED){
        gUsbData->UsbLastCommandStatus |= USB_BULK_STALLED;
    }
    if (BulkQh->CurrentTd->ControlStatus & UHCI_TD_ACTIVE) {
        gUsbData->UsbLastCommandStatus |= USB_BULK_TIMEDOUT;
    }
    //
    // Deallocate memory and return the transferred data size
    //
    HcDmaUnmap(HcStruc, BufferMapping);
    USB_MemFree(BulkDataTd0, GET_MEM_BLK_COUNT(NumAllocTDs * sizeof(UHCI_TD)));
    USB_MemFree(BulkQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return BytesTransferred;
}



/**
    This function executes an interrupt transaction on the USB. The data transfer
    direction is always DATA_IN. This function wil not return until the request
    either completes successfully or completes in error (due to time out, etc.)


    @param HcStruc              Pointer to HCStruc of the host controller
    @param DevInfo              DeviceInfo structure (if available else 0)
    @param EndpointAddress      The destination USB device endpoint to which the device request 
                                is being sent.
    @param MaxPktSize           Indicates the maximum packet size the target endpoint is capable 
                                of sending or receiving.
    @param Buffer               Buffer containing data to be sent to the device or buffer to be
                                used to receive data
    @param Length               wLength request parameter, number of bytes of data to be transferred

    @retval BytesTransferred    Number of bytes transferred


    @note  
  DO NOT TOUCH THE LINK POINTER OF THE TDInterruptData. It is statically allocated
  and linked with other items in the 1ms schedule

**/

UINT16
EFIAPI
Uhci_InterruptTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *Buffer,
    UINT16      Length
)
{
    UINT8       Endp;
    UINT8       DataToggle;
    UINT32      Temp;
    UINT32      Value;
    UHCI_QH     *IntQh;
    UHCI_TD     *IntTd;
    UINT32      BytesTransferred;
    UINT8       *BufPhyAddr = NULL;
    VOID        *BufferMapping = NULL;
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
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Uhci InterruptTransfer Invalid Pointer, Buffer is in SMRAM.\n");
            return 0;
        }
        gCheckUsbApiParameter = FALSE;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return 0;
    }

    if (UhciIsHalted(HcStruc)) {
      return 0;
    }
    
    if (!VALID_DEVINFO(DevInfo)) {
        return 0;
    }

    DevInfo->UsbLastCommandStatusExtended = 0;

    //
    // Check for 0 length transfer (if so, exit)
    //
    if (Length == 0) {
        return 0;
    }

    //
    // Store the descriptor pointer in a local variable
    //
    IntTd = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    if (IntTd == NULL) {
      return 0;
    }

    IntTd->LinkPtr  = UHCI_TERMINATE;

    //
    // It is an interrupt IN transaction get appropriate size
    //
    Endp = EndpointAddress & 0xF;
    DataToggle = UsbGetDataToggle(DevInfo, EndpointAddress);

    //
    // Form device address and endpoint in proper order and bit position
    //
    Temp = (UINT32)Endp << 7;
    Temp = (Temp | (DevInfo->DeviceAddress)) << 8; //[10:0] = Dev. Addr & Endpoint
                                                        //[18:8] = Dev. Addr & Endpoint
    //
    // Fill in various fields in the interrupt data TD
    //
    IntTd->ControlStatus = (((UINT32)(DevInfo->EndpointSpeed) & 1) << 26) | 
                  UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE;
    //
    // Set the buffer pointer. Note that currently UHCI Interrupt Transfer
    // implementation assumes IN packet; the direction is not passed here as
    // parameter. Should this change in future, make a branch to use 
    // UHCI_TD_OUT_PACKET while constructing dToken.
    //
    HcDmaMap(HcStruc, EndpointAddress & BIT7, Buffer, Length, 
    &BufPhyAddr, &BufferMapping);
    IntTd->BufferPtr = (UINT32)(UINTN)BufPhyAddr;
    Value = (UINT32)(Length - 1);
    Value = ((Value << 21) | Temp) & 0xffffff00;
    Value |= (EndpointAddress & BIT7) ? UHCI_TD_IN_PACKET : UHCI_TD_OUT_PACKET;

    if (DataToggle & 1) {
        Value |= UHCI_TD_DATA_TOGGLE;  // Make packet into a data 1
    }

    IntTd->Token = Value;
    IntTd->CSReload = 0;
    IntTd->ActiveFlag = 1;

    IntQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (IntQh == NULL) {
        return 0;
    }

    UhciInitQh(IntQh);
    IntQh->ElementPtr = (UINT32)(UINTN)IntTd;
    IntQh->CurrentTd = IntTd;
    IntQh->Type = Interrupt;
    IntQh->FirstTd = IntTd;
    IntQh->Interval = UhciTranslateInterval(DevInfo->PollInterval);

    BytesTransferred = (UINT16)UhciExecuteTransfer(HcStruc, IntQh);

    DevInfo->UsbLastCommandStatusExtended =
        (IntQh->CurrentTd->ControlStatus & UHCI_TD_STATUS_FIELD) >> 17;

    UsbUpdateDataToggle(DevInfo, EndpointAddress, IntQh->DataToggle);

    HcDmaUnmap(HcStruc, BufferMapping);

    USB_MemFree(IntTd, GET_MEM_BLK_COUNT_STRUC(UHCI_TD));
    USB_MemFree(IntQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));

    return (UINT16)BytesTransferred;
}


/**
    This function de-activates the polling TD for the requested device. The
    device may be a USB keyboard or USB hub

    @param HCStruc   Pointer to the HC structure
    @param DevInfo   Pointer to the device information structure

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_DeactivatePolling (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo
)
{
    UHCI_QH     *PollQh;
    UINT8       DataToggle;
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

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    if (DevInfo->PollTdPtr == NULL) {
        return USB_ERROR;
    }

    PollQh = (UHCI_QH*)DevInfo->PollTdPtr;

    UhciRemoveQhFromFrameList(HcStruc, PollQh);

    DataToggle = (PollQh->FirstTd->Token & UHCI_TD_DATA_TOGGLE)? 1 : 0;
    if (!(PollQh->FirstTd->ControlStatus & UHCI_TD_STATUS_FIELD)) {
        UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, DataToggle ^ 1);
    }

    UhciFreeTds(PollQh->FirstTd);
    USB_MemFree(PollQh, GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    DevInfo->PollTdPtr = NULL;

    if (DevInfo->PollDataBuffer) {
        USB_MemFree(DevInfo->PollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength)); 
        DevInfo->PollDataBuffer = NULL;
    }

    return USB_SUCCESS;
}


/**
    This function activates the polling TD for the requested device. The device
    may be a USB keyboard or USB hub

    @param HCStruc   Pointer to the HC structure
    @param DevInfo   Pointer to the device information structure

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

    @note  
  For the keyboard device this routine allocates TDRepeat also, if it is not
  already allocated. This routine allocate a polling TD and schedule it to 8ms
  schedule for keyboards and to 1024ms schedule for hubs.

**/

UINT8
EFIAPI
Uhci_ActivatePolling (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo)
{
    UHCI_TD     *PollTd;
    UHCI_QH     *PollQh;
    BOOLEAN    LowSpeed;
    UINT8    PacketId;
    UINTN    BufferAddr;
    UINT32    DataLen;
    UINT8    DataToggle;
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

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }
    
    if( !VALID_DEVINFO(DevInfo) )
        return USB_ERROR;

    DevInfo->PollDataBuffer = USB_MemAlloc(GET_MEM_BLK_COUNT(DevInfo->PollingLength));
    if (DevInfo->PollDataBuffer == NULL) {
        return USB_ERROR;
    }

  LowSpeed = (DevInfo->EndpointSpeed & 1) != 0;
  PacketId = (DevInfo->IntInEndpoint & BIT7) ? UHCI_TD_IN_PACKET : UHCI_TD_OUT_PACKET;
  BufferAddr = (UINTN)DevInfo->PollDataBuffer;
  DataLen = DevInfo->PollingLength;
  DataToggle = UsbGetDataToggle(DevInfo, DevInfo->IntInEndpoint);

  PollTd = UhciAllocGeneralTds(DevInfo->DeviceAddress, LowSpeed, PacketId, 
          DevInfo->IntInEndpoint & 0xF, DevInfo->IntInMaxPkt, TRUE, 
          &BufferAddr, &DataLen, &DataToggle);
  if (PollTd == NULL) {
    USB_MemFree(DevInfo->PollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength));
    return USB_ERROR;
  }

    PollQh = USB_MemAlloc(GET_MEM_BLK_COUNT_STRUC(UHCI_QH));
    if (PollQh == NULL) {
        USB_MemFree(DevInfo->PollDataBuffer, GET_MEM_BLK_COUNT(DevInfo->PollingLength));
        UhciFreeTds(PollTd);
        return USB_ERROR;
    }

    DevInfo->PollTdPtr = (UINT8*)PollQh;

    UhciInitQh(PollQh);
    PollQh->ElementPtr = (UINT32)(UINTN)PollTd;
    PollQh->CurrentTd = PollTd;
    PollQh->Type = Interrupt;
    PollQh->FirstTd = PollTd;
    PollQh->Interval = UhciTranslateInterval(DevInfo->PollInterval);
    PollQh->CallBackIndex = USB_InstallCallBackFunction(UhciPollingQhCallback);
    PollQh->DevInfoPtr = DevInfo;
    PollQh->ActiveFlag = TRUE;

    UhciAddQhToFrameList(HcStruc, PollQh);

    return USB_SUCCESS;
}

/**
    This function disables the keyboard repeat rate logic

    @param HCStruc   Pointer to the HC structure


    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_DisableKeyRepeat (
    HC_STRUC    *HcStruc
)
{
    UHCI_DESC_PTRS      *UhicDescPtrs;
    UHCI_QH             *Qh;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    UhicDescPtrs = HcStruc->DescPtrs.UhciDescPtrs;

    if (UhicDescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)UhicDescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)UhicDescPtrs + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh = UhicDescPtrs->RepeatQh;

    if (Qh == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)Qh < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)Qh + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)Qh->FirstTd < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)Qh->FirstTd + sizeof(UHCI_TD)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh->FirstTd->CSReload = UHCI_TD_ONE_ERROR;
    Qh->FirstTd->ControlStatus= UHCI_TD_ONE_ERROR;
    Qh->FirstTd->ActiveFlag = 0;
    Qh->ActiveFlag = FALSE;
    Qh->ElementPtr = UHCI_TERMINATE;

    return USB_SUCCESS;
}


/**
    This function enables the keyboard repeat rate logic

    @param HCStruc   Pointer to the HC structure


    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
Uhci_EnableKeyRepeat (
    HC_STRUC    *HcStruc
)
{
    UHCI_DESC_PTRS      *UhicDescPtrs;
    UHCI_QH             *Qh;
    EFI_STATUS          EfiStatus;
    UINT8               *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));

    EfiStatus = UsbHcStrucValidation(HcStruc);
    
    if (EFI_ERROR(EfiStatus)) {
        return USB_ERROR;
    }

    if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) {
        return USB_ERROR;
    }

    if (UhciIsHalted(HcStruc)) {
      return USB_ERROR;
    }

    UhicDescPtrs = HcStruc->DescPtrs.UhciDescPtrs;

    if (UhicDescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)UhicDescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)UhicDescPtrs + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh = UhicDescPtrs->RepeatQh;

    if (((UINTN)Qh < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)Qh + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)Qh->FirstTd < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)Qh->FirstTd + sizeof(UHCI_TD)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    Qh->FirstTd->CSReload = (UHCI_TD_INTERRUPT_ON_COMPLETE |
                            UHCI_TD_ONE_ERROR | UHCI_TD_ACTIVE);
    Qh->FirstTd->ControlStatus = Qh->FirstTd->CSReload;
    Qh->FirstTd->ActiveFlag = 1;
    Qh->ElementPtr = (UINT32)(UINTN)Qh->FirstTd;
    Qh->CurrentTd = Qh->FirstTd;
    Qh->ActiveFlag = TRUE;

    return USB_SUCCESS;
}



/**
    This routine disables the UHCI HC root hub ports

    @param HCStruc   Pointer to the HC structure


    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
Uhci_DisableHCPorts(
    HC_STRUC* HcStruc
)
{

    //
    // Disable the root hub port 1
    //
    HcByteWriteHcIo(HcStruc, UHCI_PORT1_CONTROL,
                (UINT8)(HcByteReadHcIo(HcStruc, UHCI_PORT1_CONTROL) & (~UHC_PORT_ENABLE)));
    //
    // Disable the root hub port 2
    //
    HcByteWriteHcIo(HcStruc, UHCI_PORT2_CONTROL,
                (UINT8)(HcByteReadHcIo(HcStruc, UHCI_PORT2_CONTROL) & (~UHC_PORT_ENABLE)));

    return USB_SUCCESS;
}


/**
    This routine will add the particular QH into the frame list

    @param HCStruc   Pointer to the HC structure
    @param NewQh     Address of the QH to be linked

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure
**/

UINT8
UhciAddQhToFrameList (
    HC_STRUC    *HcStruc,
    UHCI_QH     *NewQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    UHCI_QH     *Qh = NULL;
    BOOLEAN     ByInterval = FALSE;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (NewQh == NULL) {
        return USB_ERROR;
    }

    switch (NewQh->Type) {
        case Control:
        case Bulk:
            ByInterval = FALSE;
            break;
        case Interrupt:
            ByInterval = TRUE;
            break;
        case Isochronous:
            ASSERT(FALSE);
        default:
            return USB_ERROR;
    }

    if (ByInterval && NewQh->Interval == 0) {
        return USB_ERROR;
    }

    for (Index = 0; Index < HcStruc->AsyncListSize; 
        ByInterval ? Index += NewQh->Interval : Index++) {
        PrevPtr = &HcStruc->FrameList[Index];
        LinkPtr = *PrevPtr;

        while (!(LinkPtr & UHCI_TERMINATE)) {
            Qh = (UHCI_QH*)(UINTN)(LinkPtr & UHCI_POINTER_MASK);

            Status = AmiUsbValidateMemoryBuffer((VOID*)Qh, sizeof(UHCI_QH));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
               return USB_ERROR;
            }

            if (Qh->Type <= NewQh->Type) {
                if (ByInterval == FALSE ||
                    Qh->Interval <= NewQh->Interval) {
                    break;
                }
            }
            PrevPtr = &Qh->LinkPtr;
            LinkPtr = *PrevPtr; 
        }
        if (Qh == NewQh) {
            continue;
        }

        Status = AmiUsbValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
            return USB_ERROR;
        }

        NewQh->LinkPtr = *PrevPtr;
        *PrevPtr = (UINT32)((UINTN)NewQh | UHCI_QUEUE_HEAD);
    }

    return USB_SUCCESS;
}

/**
    This routine will remove a QH from the the frame list

    @param HCStruc           Pointer to the HC structure
    @param RetiredQh         Address of the QH to be removed

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
UhciRemoveQhFromFrameList (
    HC_STRUC    *HcStruc,
    UHCI_QH     *RetiredQh
)
{
    UINT16      Index;
    UINT32      *PrevPtr;
    UINT32      LinkPtr;
    UHCI_QH     *Qh;
    BOOLEAN     ByInterval = FALSE;
    EFI_STATUS  Status = EFI_SUCCESS;

    if (RetiredQh == NULL) {
        return USB_ERROR;
    }

    switch (RetiredQh->Type) {
        case Control:
        case Bulk:
            ByInterval = FALSE;
            break;
        case Interrupt:
            ByInterval = TRUE;
            break;
        case Isochronous:
            ASSERT(FALSE);
        default:
            return USB_ERROR;
    }

    if (ByInterval && RetiredQh->Interval == 0) {
        return USB_ERROR;
    }

    RetiredQh->ElementPtr = UHCI_TERMINATE;

    for (Index = 0; Index < HcStruc->AsyncListSize;
        ByInterval ? Index += RetiredQh->Interval : Index++) {
        PrevPtr = &HcStruc->FrameList[Index];
        LinkPtr = *PrevPtr; 
 
        while (!(LinkPtr & UHCI_TERMINATE)) {
            Qh = (UHCI_QH*)(UINTN)(LinkPtr & UHCI_POINTER_MASK);

            Status = AmiUsbValidateMemoryBuffer((VOID*)Qh, sizeof(UHCI_QH));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
                return USB_ERROR;
            }
            if(Qh == RetiredQh) {
                break;
            }
            PrevPtr = &Qh->LinkPtr;
            LinkPtr = *PrevPtr;
        }

        if (LinkPtr & UHCI_TERMINATE) {
            continue;
        }

        Status = AmiUsbValidateMemoryBuffer((VOID*)PrevPtr, sizeof(UINT32));
        if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
            return USB_ERROR;
        }

        *PrevPtr = RetiredQh->LinkPtr;
    }

    RetiredQh->LinkPtr = UHCI_TERMINATE;
    return USB_SUCCESS;
}

/**
    This routine will start the TD schedule for the UHCI controller. After this
    routine TD's can be scheduled for execution.


    @param HCStruc           Pointer to the HC structure


    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure


**/

UINT8
Uhci_StartTDSchedule (
    HC_STRUC  *HcStruc
)
{
    UHCI_DESC_PTRS  *DescPtr;
    UHCI_TD         *Td;

    //
    // Allocate the UHCI descriptor pointer structure
    //
    DescPtr = (UHCI_DESC_PTRS*) USB_MemAlloc (GET_MEM_BLK_COUNT_STRUC(UHCI_DESC_PTRS));
    if (DescPtr == NULL) {
        USB_DEBUG(DEBUG_HC|DEBUG_MEM, "UHCI Descriptor struc alloc failed.\n");
        return USB_ERROR;
    }

    //
    // Save the value in the HC struc
    //
    HcStruc->DescPtrs.UhciDescPtrs = DescPtr;

    DescPtr->StaticQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH)));
    if (DescPtr->StaticQh == NULL) {
        return USB_ERROR;
    }

    UhciInitQh(DescPtr->StaticQh);
    DescPtr->StaticQh->Type = Interrupt;
    DescPtr->StaticQh->Interval = 1;
    UhciAddQhToFrameList(HcStruc, DescPtr->StaticQh);

    if (HcStruc->HcFlag & HC_STATE_EXTERNAL) {
      return USB_SUCCESS;
    }

    DescPtr->RepeatQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH) + 
                                         1 * sizeof(UHCI_TD)));
    if(DescPtr->RepeatQh == NULL) {
        return USB_ERROR;
    }

    Td = (UHCI_TD*)((UINTN)DescPtr->RepeatQh + sizeof (UHCI_QH));

    //
    // Initialize the body of TdRepeat. It will run a interrupt transaction
    // to a non-existant dummy device.  This will have the effect of generating
    // a periodic interrupt used to generate keyboard repeat.  This TD is normally
    // inactive, and is only activated when a key is pressed.  TdRepeat will be
    // set to timeout after two attempts.  Since the TD is in the schedule
    // at 16ms intervals, this will generate an interrupt at intervals of 32ms
    // (when the TD is active).  This 32ms periodic interrupt may then
    // approximate the fastest keyboard repeat rate of 30 characters per second.
    //
    Td->LinkPtr = UHCI_TERMINATE;
    Td->ControlStatus = UHCI_TD_ONE_ERROR;
    Td->Token = (UHCI_TD_IN_PACKET |
                ((UINT32)(gUsbData->MaxDevCount+1) << 8) |
                ((UINT32)(DEFAULT_PACKET_LENGTH - 1) << 21));
    Td->BufferPtr = (UINT32)(UINTN)Td->DataArea;
    Td->CSReload = UHCI_TD_ONE_ERROR;
    Td->ActiveFlag = 0;

    UhciInitQh(DescPtr->RepeatQh);
    DescPtr->RepeatQh->Type = Interrupt;
    DescPtr->RepeatQh->FirstTd = Td;
//    DescPtr->RepeatQh->Interval = REPEAT_INTERVAL;
    if (gUsbData->RepeatIntervalMode){
        DescPtr->RepeatQh->Interval = REPEAT_INTERVAL_16MS;
    } else {
        DescPtr->RepeatQh->Interval = REPEAT_INTERVAL_8MS;
    }

    DescPtr->RepeatQh->CallBackIndex = USB_InstallCallBackFunction(UhciRepeatQhCallback);
    DescPtr->RepeatQh->ActiveFlag = FALSE;

    //
    // Schedule the TDRepeat to 8ms schedule
    //
    UhciAddQhToFrameList(HcStruc, DescPtr->RepeatQh);

    //
    // Inform the common code that key repeat is implemented
    //
    USBKeyRepeat(HcStruc, 0);

    //
    // Initialize the body of root hub TD.  It will run a interrupt
    // transaction to a nonexistent dummy device.  This will have the effect
    // of generating a periodic interrupt for the purpose of checking for
    // attach/detach on the root hub's ports
    // This initialization is done only once for the first HC
    //
    DescPtr->RootHubQh = USB_MemAlloc(GET_MEM_BLK_COUNT(1 * sizeof(UHCI_QH) + 
                                         1 * sizeof(UHCI_TD)));
    ASSERT(DescPtr->RootHubQh != NULL);
    if (DescPtr->RootHubQh == NULL) {
        return USB_ERROR;
    }

    Td = (UHCI_TD*)((UINTN)DescPtr->RootHubQh + sizeof (UHCI_QH));

    Td->LinkPtr = UHCI_TERMINATE;
    Td->ControlStatus  = 0;
    Td->Token =
        (UHCI_TD_IN_PACKET | ((UINT32)(gUsbData->MaxDevCount+1) << 8) |
        ((UINT32)(DEFAULT_PACKET_LENGTH - 1) << 21));
    Td->BufferPtr = (UINT32)(UINTN)Td->DataArea;
    Td->CSReload = 0;
    Td->ActiveFlag = 0;

    UhciInitQh(DescPtr->RootHubQh);
    DescPtr->RootHubQh->Type = Interrupt;
    DescPtr->RootHubQh->FirstTd = Td;
    DescPtr->RootHubQh->Interval = 128;
    DescPtr->RootHubQh->CallBackIndex = USB_InstallCallBackFunction(UhciRootHubQhCallBack);
    DescPtr->RootHubQh->ActiveFlag = FALSE;

    //
    // Schedule the root hub TD to 256ms schedule
    //
    UhciAddQhToFrameList(HcStruc, DescPtr->RootHubQh);

    if (gUsbDataList->UhciRootHubHcStruc == NULL) {
      Td->CSReload =
              UHCI_TD_INTERRUPT_ON_COMPLETE |
              UHCI_TD_ONE_ERROR |
              UHCI_TD_ACTIVE;
        Td->ActiveFlag = 1;
        Td->ControlStatus = Td->CSReload;
        DescPtr->RootHubQh->ElementPtr = (UINT32)(UINTN)Td;
        DescPtr->RootHubQh->CurrentTd = Td;
        DescPtr->RootHubQh->ActiveFlag = TRUE;;
        gUsbDataList->UhciRootHubHcStruc = HcStruc;
    }

    USB_DEBUG(DEBUG_HC, "TD's are scheduled\n");

    return USB_SUCCESS;
}

/**
    This routine will stop the TD schedules and frees the data structures

    @param HCStruc           Pointer to the HC structure

    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure


**/

UINT8
Uhci_StopTDSchedule (
    HC_STRUC    *HcStruc
)
{
    UINT8      i;
    UHCI_DESC_PTRS  *DescPtrs = HcStruc->DescPtrs.UhciDescPtrs;
    UINT8            *MemBlockEnd = (UINT8*)((UINTN)gUsbDataList->MemBlockStart + (gUsbData->MemPages << 12));
    //
    // Free all the TD/QH data structures
    //
    if (DescPtrs == NULL) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs->StaticQh < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->StaticQh + sizeof(UHCI_QH)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs->RootHubQh < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->RootHubQh + sizeof(UHCI_QH)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    if (((UINTN)DescPtrs->RepeatQh < (UINTN)gUsbDataList->MemBlockStart) ||
        (((UINTN)DescPtrs->RepeatQh + sizeof(UHCI_QH)) > (UINTN)MemBlockEnd)) {
        return USB_ERROR;
    }

    USB_MemFree (DescPtrs->StaticQh, GET_MEM_BLK_COUNT(sizeof(UHCI_QH)));
    if (DescPtrs->RootHubQh) {
      USB_MemFree (DescPtrs->RootHubQh, 
      GET_MEM_BLK_COUNT(sizeof(UHCI_QH) + sizeof(UHCI_TD)));
    }
    if (DescPtrs->RepeatQh) {
      USB_MemFree (DescPtrs->RepeatQh, 
      GET_MEM_BLK_COUNT(sizeof(UHCI_QH) + sizeof(UHCI_TD)));
    }
 
    //
    // Finally free the descriptor pointer
    //
    USB_MemFree (DescPtrs, GET_MEM_BLK_COUNT_STRUC(UHCI_DESC_PTRS));

    USBKeyRepeat(HcStruc, 3);

    if (gUsbDataList->UhciRootHubHcStruc == HcStruc) {
      gUsbDataList->UhciRootHubHcStruc  = NULL;
      for (i = 0; i < gUsbDataList->HcTableCount; i++) {
        if (gHcTable[i] == NULL) {
          continue;
        }
      if ((gHcTable[i]->HcNumber) && 
          (gHcTable[i]->HcType == USB_HC_UHCI) &&
          (gHcTable[i]->HcFlag & HC_STATE_RUNNING) &&
          (HcStruc != gHcTable[i])) {

           DescPtrs = gHcTable[i]->DescPtrs.UhciDescPtrs;
                
                if (((UINTN)DescPtrs < (UINTN)gUsbDataList->MemBlockStart) ||
                    (((UINTN)DescPtrs + sizeof(UHCI_DESC_PTRS)) > (UINTN)MemBlockEnd)) {
                    return USB_ERROR;
                }
                if (((UINTN)DescPtrs->RootHubQh < (UINTN)gUsbDataList->MemBlockStart) ||
                    (((UINTN)DescPtrs->RootHubQh + sizeof(UHCI_QH)) > (UINTN)MemBlockEnd)) {
                    return USB_ERROR;
                }

                if (((UINTN)DescPtrs->RootHubQh->FirstTd < (UINTN)gUsbDataList->MemBlockStart) ||
                    (((UINTN)DescPtrs->RootHubQh->FirstTd + sizeof(UHCI_TD)) > (UINTN)MemBlockEnd)) {
                    return USB_ERROR;
                }

                if (((UINTN)DescPtrs->RootHubQh->CurrentTd < (UINTN)gUsbDataList->MemBlockStart) ||
                    (((UINTN)DescPtrs->RootHubQh->CurrentTd + sizeof(UHCI_TD)) > (UINTN)MemBlockEnd)) {
                    return USB_ERROR;
                }

                DescPtrs->RootHubQh->FirstTd->CSReload =
                        UHCI_TD_INTERRUPT_ON_COMPLETE |
                        UHCI_TD_ONE_ERROR |
                        UHCI_TD_ACTIVE;
                DescPtrs->RootHubQh->FirstTd->ActiveFlag = 1;
                DescPtrs->RootHubQh->FirstTd->ControlStatus =
                DescPtrs->RootHubQh->FirstTd->CSReload;
                DescPtrs->RootHubQh->ElementPtr = 
                        (UINT32)(UINTN)DescPtrs->RootHubQh->FirstTd;
                DescPtrs->RootHubQh->CurrentTd = 
                        DescPtrs->RootHubQh->FirstTd;
                DescPtrs->RootHubQh->ActiveFlag = TRUE;;
                gUsbDataList->UhciRootHubHcStruc = gHcTable[i];
           }
        }
    }

    return USB_SUCCESS;
}

/**
    This function will check whether the QH is completed if so, it will call
    the call back routine associated with the TDs present in the QH

    @param HCStruc           Pointer to the HC structure
    @param Qh                Pointer to the QH
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
UhciProcessQh(
    HC_STRUC    *HcStruc,
    UHCI_QH     *Qh
)
{
    UHCI_TD     *Td;
    UINT16      Length;
    EFI_STATUS  Status;
 
    if (Qh == NULL) {
        return USB_ERROR;
    }

    if (Qh->ActiveFlag == FALSE) {
        return USB_SUCCESS;
    }

    if (Qh->FirstTd == NULL) {
        return USB_SUCCESS;
    }

    if (Qh->CurrentTd == NULL) {
        Qh->CurrentTd = Qh->FirstTd;
    }

    Td = Qh->CurrentTd;
    while (Td) {
        Qh->CurrentTd = Td;
        Qh->DataToggle = (Td->Token & UHCI_TD_DATA_TOGGLE) ? 1 : 0;

        if (Td->ControlStatus & UHCI_TD_ACTIVE) {
            return USB_ERROR;
        }

        Length = (UINT16)((Td->ControlStatus + 1) & UHCI_TD_ACTUAL_LENGTH);
        Qh->BytesTransferred += Length;

        if (Td->ControlStatus & UHCI_TD_STATUS_FIELD) {
            break;
        }

        Qh->DataToggle ^= 1;
        Qh->ShortPacketDetected = (Length < (((Td->Token >> 21) + 1) & 0x7FF));

        if (Qh->ShortPacketDetected) {
            if (Qh->Type == Control) {
                while (!(Td->LinkPtr & UHCI_TERMINATE)) {
                    Td = (UHCI_TD*)((UINTN)Td->LinkPtr & UHCI_POINTER_MASK);
                }
                Qh->ElementPtr = (UINT32)(UINTN)Td;
                continue;
            }
            break;
        }
 
        Td = (Td->LinkPtr & UHCI_TERMINATE) ? NULL : (UHCI_TD*)(UINTN)(Td->LinkPtr & UHCI_POINTER_MASK);
    }

    Qh->ActiveFlag = FALSE;
    
    if (Qh->CallBackIndex == 0) {
        return USB_SUCCESS;
    }
    
    if ((Qh->CallBackIndex) && (Qh->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        if (gAmiUsbCallBackFunTbl[Qh->CallBackIndex - 1 + CALLBACK_FUNCTION_START]) {
            if ((gAmiUsbCallBackFunTbl[Qh->CallBackIndex - 1 + CALLBACK_FUNCTION_START] != UhciRepeatQhCallback) && 
                (gAmiUsbCallBackFunTbl[Qh->CallBackIndex - 1 + CALLBACK_FUNCTION_START] != UhciRootHubQhCallBack)) {
                Status = UsbDevInfoValidation(Qh->DevInfoPtr);
                if (EFI_ERROR(Status)) {
                    return USB_ERROR;
                }
            }
            (*gAmiUsbCallBackFunTbl[Qh->CallBackIndex - 1 + CALLBACK_FUNCTION_START])(
                    HcStruc,
                    (DEV_INFO*)Qh->DevInfoPtr,
                    (UINT8*)Qh,
                    0,
                    0);
        }
    }

    return USB_SUCCESS;
}

/**
    This function will check whether the TD is completed if so, it will call
    the call back routine associated with this TD

    @param HCStruc           Pointer to the HC structure
    @param Td                Pointer to the TD
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

    @note  
  For any TD whose ActiveFlag is TRUE and its ControlStatus bit 23 is clear
  (completed), process the TD by calling its callback routine, if one is present.

**/

UINT8
UhciProcessTd(
    HC_STRUC    *HcStruc,
    UHCI_TD     *Td
)
{
    UINT8       DevAddr;
    DEV_INFO    *DevInfo;

    if (Td == NULL) {   // Check for NULL
        return USB_ERROR;
    }

    if (Td->ActiveFlag == 0) {
        return USB_SUCCESS;
    }

    if (Td->ControlStatus & UHCI_TD_ACTIVE) {
        return USB_ERROR;
    }

    Td->ActiveFlag = 0;
    if ((Td->CallBackIndex) && (Td->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
        //
        // Get the device address from the completed TD
        //
        DevAddr = (UINT8)(((Td->Token) >> 8) & 0x7F);
        DevInfo = USB_GetDeviceInfoStruc(USB_SRCH_DEV_ADDR, 0,
                        DevAddr, HcStruc);

        if (gAmiUsbCallBackFunTbl[Td->CallBackIndex - 1 + CALLBACK_FUNCTION_START] && (DevInfo != NULL)) {
            (*gAmiUsbCallBackFunTbl[Td->CallBackIndex - 1 + CALLBACK_FUNCTION_START])(
                    HcStruc,
                    DevInfo,
                    (UINT8*)Td,
                    0,
                    0);
        }
    }

    return USB_SUCCESS;
}

/**
    This function will parse through frame list to find completed QH/TD
    and invoke corresponding call back routine

    @param HCStruc           Pointer to the HC structure
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

    @note  
  For any TD whose ActiveFlag is TRUE and its ControlStatus bit 23 is clear
  (completed), process the TD by calling its call back routine, if one is present.

**/

UINT8
UhciProcessFrameList (
    HC_STRUC    *HcStruc
)
{
    UINT32  ListPtr;
    EFI_STATUS  Status;

    ListPtr = HcStruc->FrameList[0];

    while (!(ListPtr & UHCI_TERMINATE)) {
        if (ListPtr & UHCI_QUEUE_HEAD) {

            Status = AmiUsbValidateMemoryBuffer((VOID*)(UINTN)ListPtr, sizeof(UHCI_QH));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
                return USB_ERROR;
            }

            UhciProcessQh(HcStruc, (UHCI_QH*)(UINTN)(ListPtr & UHCI_POINTER_MASK));
            ListPtr = ((UHCI_QH*)(UINTN)(ListPtr & UHCI_POINTER_MASK))->LinkPtr;
        } else {

            Status = AmiUsbValidateMemoryBuffer((VOID*)(UINTN)ListPtr, sizeof(UHCI_TD));
            if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)){
               return USB_ERROR;
            }

            UhciProcessTd(HcStruc, (UHCI_TD*)(UINTN)(ListPtr & UHCI_POINTER_MASK));
            ListPtr = ((UHCI_TD*)(UINTN)(ListPtr & UHCI_POINTER_MASK))->LinkPtr;
        }
    }
    return USB_SUCCESS;
}

/**
    This function is called when TD256ms completes a transaction. This TD runs
    a dummy interrupt transaction to a non-existant device address for the
    purpose of generating a periodic timeout interrupt.  This periodic interrupt
    may be used to check for new devices on the root hub etc.

    @param HCStruc       Pointer to the HCStruc structure
    @param DevInfo       NULL (DevInfo is not valid)
    @param Qh            Pointer to the QH
    @param Buffer        No used   
    @param DataLength    No used    
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
UhciRootHubQhCallBack(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UINT8       Index;
    HC_STRUC    *Hc;
    UHCI_QH     *RootHubQh = NULL;
    UINT16      PortSc;

    //
    // First deactivate the TDRootHub so this callback function will not get
    // reentered.
    //
    if (Qh != NULL) {
        RootHubQh = (UHCI_QH*)Qh;
        RootHubQh->FirstTd->ActiveFlag = 0;
    }

    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
        Hc = gHcTable[Index];
        if (Hc == NULL) {
            continue;
        }

        if (Hc->HcType != USB_HC_UHCI) {  // Process for UHCI only
          continue;
        }

        if (!(Hc->HcFlag & HC_STATE_RUNNING)) {
          continue;
        }

       //
       // Check whether the controller is still under BIOS control
       // Read the frame list base address and compare with stored value
       //
       if ((HcDwordReadHcIo(HcStruc, UHCI_FRAME_LIST_BASE) & 0xFFFFF000) 
         != (UINT32)(UINTN)Hc->FrameList) {
         continue;
       }

      //
      // Check whether USB host controllers are accessible to aVOID system 
      // hang in ports enumeration.
      //
      if (HcByteReadHcIo(HcStruc, 0) == 0xFF) {
        continue;
      }

      //
      // Check whether enumeration is already began
      //
      if (gUsbData->EnumFlag == FALSE) {
          gUsbData->EnumFlag = TRUE;

         //
         // Mask the Host Controller interrupt so the ISR does not get re-entered due
         // to an IOC interrupt from any TDs that complete in frames while we are
         // configuring a new device that has just been plugged in.
         //
         // Disable IOC, timeout & CRC interrupt
         //
         HcWordWriteHcIo(HcStruc, UHCI_INTERRUPT_ENABLE, 0);
    
         //
         // Process Port#1 and clear Port#1 status bit
         //
         PortSc = HcWordReadHcIo(HcStruc, UHCI_PORT1_CONTROL);
         if (PortSc & UHC_CONNECT_STATUS_CHANGE) {
                // The interval with a minimum duration of 100 ms when 
                // the USB System Software is notified of a connection detection.
                if (PortSc & UHC_CONNECT_STATUS) {
                    FixedDelay(USB_PORT_CONNECT_STABLE_DELAY_MS * 1000);
                }
                
                USBCheckPortChange(Hc, Hc->HcNumber | BIT7, 1);
                HcWordWriteHcIo(HcStruc, UHCI_PORT1_CONTROL, 
                    HcWordReadHcIo(HcStruc, UHCI_PORT1_CONTROL));
          }
    
         //
         // Process Port#2 and clear Port#2 status bit
         //
         PortSc = HcWordReadHcIo(HcStruc, UHCI_PORT2_CONTROL);
         if (PortSc & UHC_CONNECT_STATUS_CHANGE) {
                // The interval with a minimum duration of 100 ms when 
                // the USB System Software is notified of a connection detection.
                if (PortSc & UHC_CONNECT_STATUS) {
                    FixedDelay(USB_PORT_CONNECT_STABLE_DELAY_MS * 1000);
                }
                USBCheckPortChange(Hc, Hc->HcNumber | BIT7, 2);
                HcWordWriteHcIo(HcStruc, UHCI_PORT2_CONTROL, 
                    HcWordReadHcIo(HcStruc, UHCI_PORT2_CONTROL));
           }

          //
          // Renable interrupts from the host controller
          // Enable IOC, timeout & CRC interrupt
          //
          HcWordWriteHcIo(HcStruc, UHCI_INTERRUPT_ENABLE, (UINT16)(UHC_IOC_ENABLE));

          gUsbData->EnumFlag = FALSE;
       }
    }
    if (Qh != NULL) {
        //
        // Reactivate the TdRootHub
        //
        RootHubQh->FirstTd->ControlStatus  = RootHubQh->FirstTd->CSReload;
        RootHubQh->FirstTd->ActiveFlag = 1;
        RootHubQh->ElementPtr = (UINT32)(UINTN)RootHubQh->FirstTd;
        RootHubQh->CurrentTd = RootHubQh->FirstTd;
        RootHubQh->ActiveFlag = TRUE;
    }

    return  USB_SUCCESS;
}


/**
    This function is called when TdRepeat completes a transaction.  This TD
    runs a dummy interrupt transaction to a non-existant device address for
    the purpose of generating a periodic timeout interrupt which in turn is
    used to generate keyboard repeat.

    @param HCStruc       Pointer to the HCStruc structure
    @param DevInfo       NULL (DevInfo is not valid)
    @param Qh            Pointer to the QH
    @param Buffer        No used   
    @param DataLength    No used    
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
UhciRepeatQhCallback(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UHCI_QH *RepeatQh = (UHCI_QH*)Qh;

    USB_DEBUG(DEBUG_HC, "Processing Repeat TD ...\n");
    //
    // First deactivate the TdRepeat so this callback function will not get
    // re-entered.
    //
    RepeatQh->FirstTd->ActiveFlag = 0;


    if ((gUsbData->UsbDevSupport & USB_KB_DEV_SUPPORT) == USB_KB_DEV_SUPPORT)
        USBKBDPeriodicInterruptHandler(HcStruc);

    //
    // Reactivate the TdRepeat
    //
    if (RepeatQh->FirstTd->CSReload & UHCI_TD_ACTIVE) {
        RepeatQh->FirstTd->ControlStatus = RepeatQh->FirstTd->CSReload;
        RepeatQh->FirstTd->ActiveFlag = 1;
        RepeatQh->ElementPtr = (UINT32)(UINTN)RepeatQh->FirstTd;
        RepeatQh->CurrentTd = RepeatQh->FirstTd;
        RepeatQh->ActiveFlag = TRUE;
  }

    return  USB_SUCCESS;
}


/**
    This function is called when a polling TD from the TD pool completes an
    interrupt transaction to its assigned device.
    This routine should process any data in the TD's data buffer, handle any
    errors, and then copy the TD's CSReloadValue field into its control status
    field to put the TD back into service.

    @param HCStruc       Pointer to the HCStruc structure
    @param DevInfo       NULL (DevInfo is not valid)
    @param Qh            Pointer to the QH
    @param Buffer        No used   
    @param DataLength    No used    
    
    @retval USB_SUCCESS      On success
    @retval USB_ERROR        Failure

**/

UINT8
EFIAPI
UhciPollingQhCallback(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       *Qh,
    UINT8       *Buffer,
    UINT16      DataLength
)
{
    UHCI_QH     *PollQh = (UHCI_QH*)Qh;   

    USB_DEBUG(DEBUG_HC, "Processing polling TD ...\n");

    UsbUpdateDataToggle(DevInfo, DevInfo->IntInEndpoint, 
      PollQh->DataToggle);

    if ((PollQh->CurrentTd->ControlStatus & UHCI_TD_STATUS_FIELD) == 0) {
        if ((DevInfo->CallBackIndex) && (DevInfo->CallBackIndex <= MAX_CALLBACK_FUNCTION)) {
            if (gAmiUsbCallBackFunTbl[DevInfo->CallBackIndex - 1 + CALLBACK_FUNCTION_START]) {
                (*gAmiUsbCallBackFunTbl[DevInfo->CallBackIndex - 1 + CALLBACK_FUNCTION_START])(
                        HcStruc,
                        DevInfo,
                        Qh,
                        DevInfo->PollDataBuffer,
                        (UINT16)PollQh->BytesTransferred);
            }
        }
    }

    UhciActivateTds(PollQh->FirstTd, PollQh->DataToggle);

    PollQh->ElementPtr = (UINT32)(UINTN)PollQh->FirstTd;
    PollQh->CurrentTd = PollQh->FirstTd;
    PollQh->BytesTransferred = 0;
    PollQh->ActiveFlag = TRUE;

    return  USB_SUCCESS;
}

/**
    Initial the Qh
    
    @param  Qh            Pointer to the QH
    @retval None
 
**/
VOID
UhciInitQh (
    UHCI_QH *Qh
)
{
    Qh->LinkPtr = UHCI_TERMINATE;
    Qh->ElementPtr = UHCI_TERMINATE;
    Qh->CurrentTd = NULL;
    Qh->DataToggle = 0;
    Qh->BytesTransferred = 0;
    Qh->ShortPacketDetected = FALSE;
    Qh->FirstTd = NULL;
    Qh->Interval = 0;
    Qh->CallBackIndex = 0;
    Qh->ActiveFlag = FALSE;
    Qh->DevInfoPtr = NULL;
}

/**
    This function check whether HC is halted.
    @param  HcStruc    Pointer to the host controller structure
    @retval TRUE       Uhci controller is halted
    @retval FALSE      Uhci controller is NOT halted

**/
BOOLEAN
UhciIsHalted (
    HC_STRUC  *HcStruc
)
{
    return (HcByteReadHcIo(HcStruc, UHCI_STATUS_REG) & UHC_HC_HALTED) == UHC_HC_HALTED;
}

/**
    This function calculates the polling rate.
    @param  Interval          Interval Value
    @retval PollingRate       Polling rate
**/
UINT8
UhciTranslateInterval(
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

/**
    This function calculates the polling rate.
    @param  DeviceAddr        Device address
    @param  LowSpeed          Low speed
    @param  PacketId          Packet ID
    @param  EndpointAddr      Endpoint Address
    @param  MaxPacket         Max packet
    @param  ShortPacket       Short packet
    @retval BufferAddr        Buffer address
    @retval Length            Length
    @retval DataToggle        Data toggle
**/
UHCI_TD*
UhciAllocGeneralTds (
    IN UINT8    DeviceAddr,
    IN BOOLEAN    LowSpeed,
    IN UINT8    PacketId,
    IN UINT8        EndpointAddr,
    IN UINT16    MaxPacket,
    IN BOOLEAN    ShortPacket,
    IN OUT UINTN    *BufferAddr,
    IN OUT UINT32   *Length,
    IN OUT UINT8    *DataToggle
)
{
    UINT16    NumTds = 0;
    UHCI_TD    *FirstTd = NULL;
    UHCI_TD    *Td = NULL;
    UINTN    Address = *BufferAddr;
    UINT32    BytesRemaining = *Length;
    UINT8    Toggle = *DataToggle;
    UINT16    MaxLen;

    if (BytesRemaining == 0) {
      return NULL;
    }

    NumTds = (UINT16)(BytesRemaining / MaxPacket);
    if (BytesRemaining % MaxPacket) {
      NumTds++;
    }

    FirstTd = USB_MemAlloc(GET_MEM_BLK_COUNT(NumTds * sizeof(UHCI_TD)));
    if (FirstTd == NULL) {
      return NULL;
    }
  
  for (Td = FirstTd;;) {
    MaxLen = BytesRemaining > MaxPacket ? MaxPacket : (UINT16)BytesRemaining;

    Td->LinkPtr = UHCI_TERMINATE;
    Td->Token = (UINT32)PacketId | ((UINT32)DeviceAddr << 8) | 
            ((UINT32)EndpointAddr << 15) | ((UINT32)(MaxLen - 1) << 21);
    if (Toggle) {
      Td->Token |= UHCI_TD_DATA_TOGGLE;
    }

    Td->BufferPtr = (UINT32)Address;
    Td->CSReload = UHCI_TD_THREE_ERRORS | UHCI_TD_ACTIVE;
    if (LowSpeed) {
      Td->CSReload |= UHCI_TD_LOW_SPEED_DEVICE;
    }
    if (ShortPacket) {
      Td->CSReload |= UHCI_TD_SHORT_PACKET_DETECT;
    }
    Td->ControlStatus = Td->CSReload;
    Td->ActiveFlag = 1;

    BytesRemaining -= MaxLen;
    Address += MaxLen;
    Toggle ^= 1;

    if (BytesRemaining == 0) {
      break;
    }

    Td->LinkPtr = (UINT32)(((UINTN)Td + sizeof(UHCI_TD)) | UHCI_VERTICAL_FLAG);
    Td = (UHCI_TD*)((UINTN)Td->LinkPtr & UHCI_POINTER_MASK);
  }

  Td->CSReload |= UHCI_TD_INTERRUPT_ON_COMPLETE;
  Td->ControlStatus = Td->CSReload;

  *Length = BytesRemaining;
  *BufferAddr = Address;
  *DataToggle = Toggle;
  
  return FirstTd;
}

/**
    Free  Tds
    @param  FirstTd          First Td
    @retval None
**/
VOID
UhciFreeTds (
    IN UHCI_TD  *FirstTd
)
{
    UHCI_TD  *Td = FirstTd;
    UINT16  NumTds = 0;

    if (FirstTd == NULL) {
    return;
    }

    while (Td) {
        NumTds++;
        Td = (Td->LinkPtr & UHCI_TERMINATE) ? NULL : (UHCI_TD*)((UINTN)Td->LinkPtr & UHCI_POINTER_MASK);
    }

    USB_MemFree(FirstTd, GET_MEM_BLK_COUNT(NumTds * sizeof(UHCI_TD)));
}

/**
    Activated Td
    @param  FirstTd          First Td
    @param  DataToggle       Data toggle
    @retval None
**/
VOID
UhciActivateTds (
    IN UHCI_TD  *FirstTd,
    IN UINT8  DataToggle
)
{
    UHCI_TD  *Td = FirstTd;
    UINT8  Toogle = DataToggle;

    if (FirstTd == NULL) {
      return;
    }

    while (Td) {
        Td->Token &= ~UHCI_TD_DATA_TOGGLE;
        if (Toogle) {
          Td->Token |= UHCI_TD_DATA_TOGGLE;
        }
        Td->ControlStatus = Td->CSReload;
        Td->ActiveFlag = 1;

        Toogle ^= 1;
        Td = (Td->LinkPtr & UHCI_TERMINATE) ? NULL : (UHCI_TD*)((UINTN)Td->LinkPtr & UHCI_POINTER_MASK);
    }
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
