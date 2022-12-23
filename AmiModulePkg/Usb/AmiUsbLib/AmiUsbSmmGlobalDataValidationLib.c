//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AmiUsbSmmGlobalDataValidationLib.c
  Source code for the AmiUsbSmmGlobalDataValidationLib library class.

  AmiUsbSmmGlobalDataValidationLib Function source code.
**/

#include <Uefi.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <AmiDef.h>
#include <UsbDef.h>
#include <Xhci.h>
#include <Library/AmiUsbSmmGlobalDataValidationLib.h>

USB_DATA_LIST           **gUsbDataListAddr   = NULL;
USB_GLOBAL_DATA         **gUsbGlobdaDataAddr = NULL;
UINT8                   *gUsbDataInSmmAddr   = NULL;
UINT8                   gValidateErrorCode   = 0;

/**
    This function Check Usb Smm Global Data.
    @param  None
    @retval EFI_STATUS  Status of the operation

**/
EFI_STATUS
CheckAmiUsbSmmGlobalData(
)
{
    UINTN                       Index = 0;
    HC_STRUC                    *HcStruc;
    USB3_HOST_CONTROLLER        *Usb3Hc = NULL;
    UINTN                       HcInitializedNumber = 0;
    UINTN                       Usb3HcInitializedNumber = 0;
    EFI_STATUS                  Status;
    UINT32                      FrameListSize = 0;
    UINTN                       DeviceContextSize;
    UINTN                       XfrRingsSize;
    UINT16                      NumBufs;
    UINT16                      Count;
    VOID                        *Buffer;
    USB_DATA_LIST               *UsbDataList   = (USB_DATA_LIST*)*gUsbDataListAddr;
    USB_GLOBAL_DATA             *UsbGlobdaData = (USB_GLOBAL_DATA*)*gUsbGlobdaDataAddr;
    VOID                        *IsocTdsHostAddr = NULL;

    // Validate Usb Global Data
    gValidateErrorCode = VALIDATE_USB_GLOBAL_DATA;
    if (*gUsbDataInSmmAddr == FALSE){
        Status = AmiValidateMemoryBuffer((VOID*)UsbGlobdaData, sizeof(USB_GLOBAL_DATA));
        if (EFI_ERROR(Status)) return Status;
    } else {
        Status = AmiValidateSmramBuffer((VOID*)UsbGlobdaData, sizeof(USB_GLOBAL_DATA));
        if (EFI_ERROR(Status)) return Status;
    }

    // Validate Usb data list
    gValidateErrorCode = VALIDATE_USB_DATA_LIST;
    if (*gUsbDataInSmmAddr == FALSE){
        Status = AmiValidateMemoryBuffer((VOID*)UsbDataList, sizeof(USB_DATA_LIST));
        if (EFI_ERROR(Status)) return Status;
    } else {
        Status = AmiValidateSmramBuffer((VOID*)UsbDataList, sizeof(USB_DATA_LIST));
        if (EFI_ERROR(Status)) return Status;
    }

    // Validate Usb memory block
    gValidateErrorCode = VALIDATE_USB_MEM_BLOCK;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->MemBlockStart, UsbGlobdaData->MemPages << 12);
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb memory block status
    gValidateErrorCode = VALIDATE_USB_MEM_BLOCK_STATUS;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->MemBlkSts, ((UsbGlobdaData->MemPages << 12) / sizeof(MEM_BLK)) / 8);
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb temp buffer
    gValidateErrorCode = VALIDATE_USB_TEMP_BUFFER;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbTempBuffer, MAX_TEMP_BUFFER_SIZE);
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb mass consume buffer
    gValidateErrorCode = VALIDATE_USB_MASS_MEM_BUFFER;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbMassConsumeBuffer, MAX_CONSUME_BUFFER_SIZE);
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb timing policy data
    gValidateErrorCode = VALIDATE_USB_TIMING_POLICY;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbTimingPolicy, sizeof(USB_TIMING_POLICY));
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb SETUP data
    gValidateErrorCode = VALIDATE_USB_SETUP_DATA;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbSetupData, sizeof(USB_SUPPORT_SETUP));
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb skip list
    gValidateErrorCode = VALIDATE_USB_SKIP_LIST;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbSkipListTable, 
               UsbGlobdaData->MaxSkipListCount * sizeof(USB_SKIP_LIST));
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb device table
    gValidateErrorCode = VALIDATE_DEVICE_TABLE;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->DevInfoTable, 
               UsbGlobdaData->MaxDevCount * sizeof(DEV_INFO));
    if (EFI_ERROR(Status)) return Status;

    // Validate Usb Keyboard device table
    gValidateErrorCode = VALIDATE_KB_DEVICE_TABLE;
    Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->UsbKbDeviceTable, 
               UsbGlobdaData->MaxHidCount * sizeof(DEV_INFO*));
    if (EFI_ERROR(Status)) return Status;

    if (UsbDataList->HubPortStatusBuffer != NULL) {
        gValidateErrorCode = VALIDATE_HUB_PORT_STATUS_BUFFER;
        Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->HubPortStatusBuffer, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    if (UsbDataList->InterruptStatus != NULL) {
        gValidateErrorCode = VALIDATE_INTERRUPT_STATUS;
        Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->InterruptStatus, sizeof(UINT32));
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    for (Index = 0; Index < UsbDataList->HcTableCount; Index++) {
        HcStruc = UsbDataList->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (HcStruc->HcFlag & (HC_STATE_RUNNING |HC_STATE_INITIALIZED)) {
            HcInitializedNumber++;
            if (HcStruc->Usb3HcData) {
                Usb3HcInitializedNumber++;
            }
        }
    }

    for (Index = 0; Index < UsbDataList->HcTableCount; Index++) {
        HcStruc = UsbDataList->HcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }

        gValidateErrorCode = VALIDATE_USB_HC_STRUC;
        if (*gUsbDataInSmmAddr == FALSE){
            Status = AmiValidateMemoryBuffer((VOID*)HcStruc, sizeof(HC_STRUC));
            if (EFI_ERROR(Status)) {
                return Status;
            }
        } else {
            Status = AmiValidateSmramBuffer((VOID*)HcStruc, sizeof(HC_STRUC));
            if (EFI_ERROR(Status)) return Status;
        }

        if (HcStruc->HcFlag & (HC_STATE_RUNNING |HC_STATE_INITIALIZED)) {

            // Validate Frame List
            switch (HcStruc->HcType) {
                case USB_HC_UHCI:
                     FrameListSize = USB_UHCI_FRAME_LIST_SIZE;
                     break;
                case USB_HC_OHCI:
                     FrameListSize = USB_OHCI_FRAME_LIST_SIZE;
                     break;
                case USB_HC_EHCI:
                     FrameListSize = USB_EHCI_FRAME_LIST_SIZE;
                     break;
                case USB_HC_XHCI:
                     FrameListSize = USB_XHCI_FRAME_LIST_SIZE;
                     break;
            }
            
            gValidateErrorCode = VALIDATE_USB_FRAME_LIST;
            if (FrameListSize > 0) {
                Status = AmiValidateMemoryBuffer((VOID*)HcStruc->FrameList, FrameListSize);
                if (EFI_ERROR(Status)) {
                    return Status;
                }
            }
            
            // Validate IsocTds
            if (HcStruc->IsocTds!=NULL){
                if((gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON) && (HcStruc->FrameListPhyAddr != NULL)){
                    IsocTdsHostAddr = (VOID*)((UINTN)HcStruc->IsocTds + (UINTN)HcStruc->FrameList - (UINTN)HcStruc->FrameListPhyAddr); //UnMap
                    gValidateErrorCode = VALIDATE_USB_EHCI_ISOCTDS;
                    Status = AmiValidateMemoryBuffer((VOID*)IsocTdsHostAddr, EHCI_FRAMELISTSIZE * sizeof(EHCI_ITD));
                    if (EFI_ERROR(Status)) {
                            return Status;
                    }
                } else {
                    gValidateErrorCode = VALIDATE_USB_EHCI_ISOCTDS;
                    Status = AmiValidateMemoryBuffer((VOID*)HcStruc->IsocTds, EHCI_FRAMELISTSIZE * sizeof(EHCI_ITD));
                    if (EFI_ERROR(Status)) {
                            return Status;
                    }
                }
            }

            if (HcStruc->Usb3HcData) {
                gValidateErrorCode = VALIDATE_USB_XHCI_BUS_DATA;
                Usb3Hc = HcStruc->Usb3HcData;
                if (*gUsbDataInSmmAddr == FALSE) {
                    Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc, sizeof(USB3_HOST_CONTROLLER));
                    if (EFI_ERROR(Status)) {
                        return Status;
                    }
                }else{
                    Status = AmiValidateSmramBuffer((VOID*)Usb3Hc, sizeof(USB3_HOST_CONTROLLER));
                    if (EFI_ERROR(Status)) return Status;
                }
                
                Status = AmiValidateMmioBuffer((VOID*)Usb3Hc->OpRegs, sizeof(XHCI_HC_OP_REGS));
                if (EFI_ERROR(Status)) {
                    return Status;
                }
                
               Status = AmiValidateMmioBuffer((VOID*)Usb3Hc->RtRegs, ((sizeof(UINT32)*8) + sizeof(XHCI_INTERRUPTER_REGS)));
                if (EFI_ERROR(Status)) {
                    return Status;
                }

                if (Usb3Hc->Usb3xProtocolCount>0){
                    Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc->Usb3xProtocol,
                                 (sizeof(XHCI_EXT_PROTOCOL) * Usb3Hc->Usb3xProtocolCount));
                    if (EFI_ERROR(Status)) {
                        return Status;
                    }
                }

                Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc->DcbaaPtr, TRANSFER_RING_OFFSET);
                if (EFI_ERROR(Status)) {
                    return Status;
                }

                XfrRingsSize = Usb3Hc->CapRegs.HcsParams1.MaxSlots * END_POINTS_PADDED * TRB_RING_PADDED_SIZE;
                Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc->XfrRings, XfrRingsSize);
                if (EFI_ERROR(Status)) {
                    return Status;
                }

                DeviceContextSize = (XHCI_DEVICE_CONTEXT_ENTRIES * Usb3Hc->ContextSize) * Usb3Hc->CapRegs.HcsParams1.MaxSlots;
                Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc->DeviceContext, DeviceContextSize);
                if (EFI_ERROR(Status)) {
                    return Status;
                }

                if (Usb3Hc->InputContext != ((VOID*)((UINTN)Usb3Hc->DcbaaPtr + INPUT_CONTEXT_OFFSET)))
                    return EFI_ACCESS_DENIED;

                NumBufs =  (UINT16)(((Usb3Hc->CapRegs.HcsParams2.MaxScratchPadBufsHi) << 5) + 
                                    Usb3Hc->CapRegs.HcsParams2.MaxScratchPadBufsLo);
                if ((NumBufs > 0) && (Usb3Hc->ScratchBufEntry != NULL)) {
                    Status = AmiValidateMemoryBuffer((VOID*)Usb3Hc->ScratchBufEntry, (sizeof(UINT64)*NumBufs));
                    if (EFI_ERROR(Status)) {
                        return Status;
                    }
                    for (Count = 0; Count < NumBufs; Count++) {
                        Buffer = (VOID*)((UINTN)Usb3Hc->ScratchBufEntry[Count] - (UINTN)Usb3Hc->DcbaaPtrMap + (UINTN)Usb3Hc->DcbaaPtr);
                        Status = AmiValidateMemoryBuffer (Buffer, EFI_PAGES_TO_SIZE(Usb3Hc->PageSize4K));
                        if (EFI_ERROR(Status)) {
                            return Status;
                        }
                    }
                }
            }
        }
    }

    return EFI_SUCCESS;
}

/**
    This function Validate Usb Smm Global Data.
    @param  UsbGlobdaDataAddr  Pointer of Usb Globda Data
    @param  UsbDataListAddr    Pointer of Usb Data List
    @param  UsbDataInSmmAddr   Pointer of Usb Data In Smm
    @retval EFI_STATUS         Status of the operation

**/
EFI_STATUS
EFIAPI
AmiUsbSmmGlobalDataValidation(
    USB_GLOBAL_DATA *UsbGlobdaDataAddr,
    USB_DATA_LIST   *UsbDataListAddr,
    UINT8           *UsbDataInSmmAddr
)
{
    EFI_STATUS          Status;
    UINT8               *MouseInputBufferEnd;
    UINT8               *KbcharacterBufferEnd;
    UINT8               *KbcScanCodeBufferEnd;
    UINTN               Index;
    DEV_INFO            *DevInfoTableEnd;
    HC_STRUC            *HcStruc;
    LIST_ENTRY          *Link = NULL;
    USB_DEV_CONFIG_LINK *ReadDevConfigLink = NULL;
    USB_DATA_LIST       *UsbDataList;
    USB_GLOBAL_DATA     *UsbGlobdaData;

    if(gUsbGlobdaDataAddr == NULL) gUsbGlobdaDataAddr = (USB_GLOBAL_DATA**)UsbGlobdaDataAddr;
    if(gUsbDataInSmmAddr == NULL)  gUsbDataInSmmAddr  = UsbDataInSmmAddr;
    if(gUsbDataListAddr == NULL)   gUsbDataListAddr   = (USB_DATA_LIST**)UsbDataListAddr;

    UsbGlobdaData = (USB_GLOBAL_DATA*)*gUsbGlobdaDataAddr;
    UsbDataList   = (USB_DATA_LIST*)*gUsbDataListAddr;

    // Validate Device config information
    gValidateErrorCode = VALIDATE_USB_DEV_CON_INFO;
    for (Link = UsbGlobdaData->DevConfigInfoList.ForwardLink;
        Link != (LIST_ENTRY*)(UINTN)(&UsbGlobdaData->DevConfigInfoList);
        Link = Link->ForwardLink ) {
        ReadDevConfigLink = BASE_CR(Link, USB_DEV_CONFIG_LINK, Link);
        if (ReadDevConfigLink < (&UsbGlobdaData->DevConfigLink[0])) return EFI_ACCESS_DENIED;
        if (ReadDevConfigLink > (&UsbGlobdaData->DevConfigLink[MAX_DEV_CONFIG_LINK-1])) return EFI_ACCESS_DENIED;
    }
    
    // Validate Mosue Input Buffer
    gValidateErrorCode = VALIDATE_USB_MS_INPUT_BUFFER;
    MouseInputBufferEnd = (UINT8*)((UINTN)UsbGlobdaData->UsbMsInputBuffer + sizeof(UsbGlobdaData->UsbMsInputBuffer));
    if (((UINTN)UsbDataList->MouseInputBufferHeadPtr < (UINTN)UsbGlobdaData->UsbMsInputBuffer) ||
        ((UINTN)UsbDataList->MouseInputBufferHeadPtr > (UINTN)MouseInputBufferEnd) ||
        ((UINTN)UsbDataList->MouseInputBufferTailPtr < (UINTN)UsbGlobdaData->UsbMsInputBuffer) ||
        ((UINTN)UsbDataList->MouseInputBufferTailPtr > (UINTN)MouseInputBufferEnd)) {
        return EFI_ACCESS_DENIED;
    }

    // Validate Keyboard CHAR Buffer
    gValidateErrorCode = VALIDATE_USB_KB_CHAR_BUFFER;
    KbcharacterBufferEnd = (UINT8*)((UINTN)UsbGlobdaData->KbcCharacterBufferStart + sizeof(UsbGlobdaData->KbcCharacterBufferStart));
    if (((UINTN)UsbDataList->KbcCharacterBufferHead < (UINTN)UsbGlobdaData->KbcCharacterBufferStart) ||
        ((UINTN)UsbDataList->KbcCharacterBufferHead > (UINTN)KbcharacterBufferEnd) ||
        ((UINTN)UsbDataList->KbcCharacterBufferTail < (UINTN)UsbGlobdaData->KbcCharacterBufferStart) ||
        ((UINTN)UsbDataList->KbcCharacterBufferTail > (UINTN)KbcharacterBufferEnd)) {
        return EFI_ACCESS_DENIED;
    }

    // Validate Keyboard SCAN Buffer
    gValidateErrorCode = VALIDATE_USB_KB_SCAN_BUFFER;
    KbcScanCodeBufferEnd = (UINT8*)((UINTN)UsbGlobdaData->KbcScanCodeBufferStart + sizeof(UsbGlobdaData->KbcScanCodeBufferStart));
    if (((UINTN)UsbDataList->KbcScanCodeBufferPtr < (UINTN)UsbGlobdaData->KbcScanCodeBufferStart) ||
        ((UINTN)UsbDataList->KbcScanCodeBufferPtr > (UINTN)KbcScanCodeBufferEnd)) {
        return EFI_ACCESS_DENIED;
    }

    // Validate Keyboard Repeat device info
    gValidateErrorCode = VALIDATE_USB_KB_REPEAT_DEV;
    DevInfoTableEnd = UsbDataList->DevInfoTable + UsbGlobdaData->MaxDevCount;
    if (UsbDataList->KeyRepeatDevInfo != NULL) { 
        if (((UINTN)UsbDataList->KeyRepeatDevInfo < (UINTN)UsbDataList->DevInfoTable) ||
            ((UINTN)UsbDataList->KeyRepeatDevInfo > (UINTN)DevInfoTableEnd)) {
            return EFI_ACCESS_DENIED;
        }
    }

    // Validate Keyboard device info
    gValidateErrorCode = VALIDATE_USB_KB_DEV;
    for (Index = 0; Index < UsbGlobdaData->MaxHidCount; Index++) {
        if (UsbDataList->UsbKbDeviceTable[Index] != NULL) {
            if (((UINTN)(UsbDataList->UsbKbDeviceTable[Index]) < (UINTN)UsbDataList->DevInfoTable) ||
                ((UINTN)(UsbDataList->UsbKbDeviceTable[Index]) > (UINTN)DevInfoTableEnd)) {
                return EFI_ACCESS_DENIED;
            }
        }
    }

    if (UsbDataList->HcTableCount != 0) {

        // Validate USB HC struc pointer
        gValidateErrorCode = VALIDATE_USB_HC_STRUC_POINTER;
        if (*gUsbDataInSmmAddr == FALSE){
            Status = AmiValidateMemoryBuffer((VOID*)UsbDataList->HcTable, sizeof(HC_STRUC*) * UsbDataList->HcTableCount);
            if (EFI_ERROR(Status)) {
                return EFI_ACCESS_DENIED;
            }
        } else {
            Status = AmiValidateSmramBuffer((VOID*)UsbDataList->HcTable, sizeof(HC_STRUC*) * UsbDataList->HcTableCount);
            if (EFI_ERROR(Status)) return Status;
        }
        
        for (Index = 0; Index < UsbDataList->HcTableCount; Index++) {
            HcStruc = UsbDataList->HcTable[Index];
            if (HcStruc == NULL) {
                continue;
            }
           //Check if MMIO address space of usb controller resides in SMRAM region. If yes, don't proceed.
            if (HcStruc->HcType != USB_HC_UHCI) {
                if (HcStruc->BaseAddress != 0) {
                    // Validate USB HC struc pointer
                    gValidateErrorCode = VALIDATE_USB_HC_MMIO;
                    Status = AmiValidateMmioBuffer((VOID*)HcStruc->BaseAddress, HcStruc->BaseAddressSize);
                    if (EFI_ERROR(Status)) {
                        DEBUG((DEBUG_ERROR, "Usb Mmio address is invalid, it is in SMRAM\n"));
                        return EFI_ACCESS_DENIED;
                    }
                }
            }
        }
    }

    Status = CheckAmiUsbSmmGlobalData();
    
    if (EFI_ERROR(Status)) {
        return EFI_ACCESS_DENIED;
    }

    gValidateErrorCode = VALIDATE_USB_DUMMY;
    return EFI_SUCCESS;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
