/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 * 
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 * 
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 * 
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 * 
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 ******************************************************************************
 */

#include <AmdCpmSmm.h>

CPM_DEFINE_gBS;
CPM_DEFINE_gSmst;

AMD_CPM_TABLE_PROTOCOL                  *gCpmTableSmmProtocol;


EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmGpioInitS3RestoreCallback,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SW_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM GPIO Init SMM driver
 *
 * This function registers the SMI handlers to set internal PCIe clock when resume
 * from S3.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
AmdCpmGpioInitSmmEntryPoint (
  IN      EFI_HANDLE                  ImageHandle,
  IN      EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                          Status;
  CPM_SMM_SW_DISPATCH_PROTOCOL        *SwDispatch;
  CPM_SMM_SW_DISPATCH_CONTEXT         SwContext;
  EFI_HANDLE                          SwHandle;

  If_CpmInSmm (ImageHandle, SystemTable, gBS, gSmst, Status) {
    //
    // Initialize global variables
    //
    Status = gBS->LocateProtocol (
                    &gAmdCpmTableSmmProtocolGuid,
                    NULL,
                    (VOID**)&gCpmTableSmmProtocol
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpGpioInitSmmDriverBegin);
    //
    //  Locate SMM SW dispatch protocol
    //
    Status = CpmSmmLocateProtocol (
                    &gCpmSmmSwDispatchProtocolGuid,
                    NULL,
                    (VOID**)&SwDispatch
                    );
    ASSERT_EFI_ERROR (Status);

    SwContext.SwSmiInputValue = CFG_CPM_ACPI_RESTORE_SW_SMI;
    Status = SwDispatch->Register (
                    SwDispatch,
                    AmdCpmGpioInitS3RestoreCallback,
                    &SwContext,
                    &SwHandle
                    );

    gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpGpioInitSmmDriverEnd);
  }
  RECORD_TIME_DXE (EndAmdCpmGpioInitSmmDriver);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIE Clock Init
 *
 * This function sets internal PCIe clock.
 *
 * @param[in]     CpmTableProtocolPtr Pointer to AMD CPM Table Protocol
 *
 */

VOID
AmdCpmSmmPcieClockInit (
  IN      AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr
  )
{
  AMD_CPM_PCIE_CLOCK_TABLE            *CpmPcieClockTablePtr;
  AMD_CPM_PCIE_CLOCK_ITEM             *TablePtr;
  UINT8                               SlotStatus;
  BOOLEAN                             ClockType;
  AMD_CPM_EXPRESS_CARD_TABLE          *ExpressCardTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE    *OtherHotplugTablePtr;
  AMD_CPM_ZERO_POWER_ODD_TABLE        *ZeroPowerOddTablePtr;
  AMD_CPM_SAVE_CONTEXT_TABLE          *SaveContextTablePtr;
  UINT8                               i;
  UINT32                              PcieSlotStatus;
  UINT32                              PcieSlotStatusHigh;

  i = 0;
  PcieSlotStatus = 0;
  PcieSlotStatusHigh = 0;

  CpmPcieClockTablePtr                = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_CLOCK);
  SaveContextTablePtr                 = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_SAVE_CONTEXT);
  ClockType                           = (BOOLEAN) CpmTableProtocolPtr->CommonFunction.GetStrap (CpmTableProtocolPtr) & BIT1;

  if (SaveContextTablePtr && ClockType && CpmPcieClockTablePtr) {
    PcieSlotStatusHigh = (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x07);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x06);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x05);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x04);
    PcieSlotStatus = (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x03);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x02);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x01);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x00);
    TablePtr = &CpmPcieClockTablePtr->Item[0];
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));
    while (TablePtr->ClkId != 0xFF) {
      SlotStatus = 0;
      if (TablePtr->SlotCheck & BIT1) {
        SlotStatus = CpmTableProtocolPtr->CommonFunction.DetectDevice (CpmTableProtocolPtr, TablePtr->DeviceId, NULL) ? BIT1 : 0;
      }
      if (TablePtr->SlotCheck & (BIT3 + BIT2 + BIT0)) {
        if (i < 8) {
          SlotStatus |=  (UINT8) ((PcieSlotStatus >> (4 * i)) & 0xF);
        } else {
          SlotStatus |=  (UINT8) ((PcieSlotStatusHigh >> (4 * (i - 8))) & 0xF);
        }
      }
      DEBUG((DEBUG_INFO, "  Item[%X] Socket=%02X Die=%02X Bridge=%02X Miscid=%02X", i, \
            (TablePtr->SpecialFunctionId >> 24) & 0xF, (TablePtr->SpecialFunctionId >> 20) & 0xF, \
            (TablePtr->SpecialFunctionId >> 16) & 0xF, (TablePtr->SpecialFunctionId >> 28) & 0xF));
      DEBUG((DEBUG_INFO, " Device=%02X  Function=%02X  SlotCheck=%02X  SpecialFunctionId=%X  SlotStatus=%02X\n", \
            TablePtr->Device, TablePtr->Function, TablePtr->SlotCheck, (TablePtr->SpecialFunctionId & 0xFFFF), SlotStatus));
      if ((SlotStatus > 0) && (((SlotStatus & 0xFE) & TablePtr->SlotCheck) == 0)) {
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-SlotStatus > 0 & ((SlotStatus & 0xFE) & TablePtr->SlotCheck) = 0\n"));
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-Set ClkReq & ClkReqExt = 0xFF\n"));
        TablePtr->ClkReq = 0xFF;
        TablePtr->ClkReqExt = 0xFF;
      }
      if ((SlotStatus == 0) && ((TablePtr->SlotCheck & (BIT1 + BIT0)) > 0) && CpmTableProtocolPtr->MainTablePtr->UnusedGppClkOffEn) {
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-SlotStatus=0 & (SlotCheck&(BIT1+BIT0))>0 & UnusedGppClkOffEn=1\n"));
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-Set ClkReq & ClkReqExt = 0\n"));
        TablePtr->ClkReq = 0;
        TablePtr->ClkReqExt = 0;
      }
      if (CpmTableProtocolPtr->CommonFunction.GetClkReq (CpmTableProtocolPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 28) & 0xF), TablePtr->ClkId) == 1) {
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-L1SS is enabled, don't do SetClkReq\n"));
      } else {
        DEBUG((DEBUG_INFO, "FEA-SMM-AmdCpmSmmPcieClockInit-SetClkReq\n"));
        CpmTableProtocolPtr->CommonFunction.SetClkReq (CpmTableProtocolPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 28) & 0xF), TablePtr->ClkId, TablePtr->ClkReq);
      }
      TablePtr++;
      i++;
    }
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));
  }
  ExpressCardTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_EXPRESS_CARD);
  if (ExpressCardTablePtr) {
    CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                ExpressCardTablePtr->EventPin,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, ExpressCardTablePtr->EventPin) ? 0 : 1
                                                );
    CpmTableProtocolPtr->CommonFunction.SetGeventSci (
                                                CpmTableProtocolPtr,
                                                ExpressCardTablePtr->EventPin
                                                );
  }
  OtherHotplugTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
  if (OtherHotplugTablePtr) {
    if ((OtherHotplugTablePtr->Number > 0) && (OtherHotplugTablePtr->EventSource0 == 0)) {
      CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                OtherHotplugTablePtr->EventPin0,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, OtherHotplugTablePtr->EventPin0) ? 0 : 1
                                                );
      CpmTableProtocolPtr->CommonFunction.SetGeventSci (
                                                CpmTableProtocolPtr,
                                                OtherHotplugTablePtr->EventPin0
                                                );
    }
    if ((OtherHotplugTablePtr->Number > 1) && (OtherHotplugTablePtr->EventSource1 == 0)) {
      CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                OtherHotplugTablePtr->EventPin1,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, OtherHotplugTablePtr->EventPin1) ? 0 : 1
                                                );
      CpmTableProtocolPtr->CommonFunction.SetGeventSci (
                                                CpmTableProtocolPtr,
                                                OtherHotplugTablePtr->EventPin1
                                                );
    }
  }
  if (CpmTableProtocolPtr->MainTablePtr->ZeroPowerOddEn & (BIT0 | BIT1)) {
    ZeroPowerOddTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_ZERO_POWER_ODD);
    if (ZeroPowerOddTablePtr) {
      if ((CpmTableProtocolPtr->MainTablePtr->ZeroPowerOddEn & BIT0) && (ZeroPowerOddTablePtr->EventSource1 == 0)) {
        CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                ZeroPowerOddTablePtr->EventPin1,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, ZeroPowerOddTablePtr->EventPin1) ? 0 : 1
                                                );
      }
      if ((CpmTableProtocolPtr->MainTablePtr->ZeroPowerOddEn & BIT1) && (ZeroPowerOddTablePtr->EventSource2 == 0)) {
        CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                ZeroPowerOddTablePtr->EventPin2,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, ZeroPowerOddTablePtr->EventPin2) ? 0 : 1
                                                );
      }
    }
  }
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to init GEVENT pins
 *
 * @param[in]     CpmTableProtocolPtr Pointer to AMD CPM Table Protocol
 *
 */

VOID
AmdCpmSmmGeventInit (
  IN      AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr
  )
{
  AMD_CPM_GEVENT_INIT_TABLE       *GeventTablePtr;
  AMD_CPM_GEVENT_ITEM             *TablePtr;

  if (CpmTableProtocolPtr) {
    GeventTablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_GEVENT_INIT);

    if (GeventTablePtr) {
      TablePtr = &GeventTablePtr->GeventList[0];
      while (TablePtr->Pin != 0xFF) {
        CpmTableProtocolPtr->CommonFunction.SetGevent (CpmTableProtocolPtr, TablePtr->Pin, TablePtr->Setting.Raw);
        TablePtr++;
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *
 * SMI Handler to set internal PCIe clock
 *
 * This function restores internal PCIe clock when resume from S3.
 *
 */

EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmGpioInitS3RestoreCallback,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SW_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  )
{
  AmdCpmSmmPcieClockInit (gCpmTableSmmProtocol);
  AmdCpmSmmGeventInit (gCpmTableSmmProtocol);
  return EFI_SUCCESS;
}
