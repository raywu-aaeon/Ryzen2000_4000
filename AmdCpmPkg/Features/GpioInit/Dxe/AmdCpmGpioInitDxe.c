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

#include <AmdCpmDxe.h>
#include <Protocol/FchInitDonePolicyProtocol.h>

VOID
EFIAPI
AmdCpmGpioInitMid (
  IN      VOID             *Context
  );

VOID
EFIAPI
AmdCpmGpioInitMidNotifyEvent (
  IN      EFI_EVENT        Event,
  IN      VOID             *Context
  );

VOID
EFIAPI
AmdCpmGpioInitLate (
  IN      EFI_EVENT        Event,
  IN      VOID             *Context
  );

VOID
AmdCpmDxePcieClockInit (
  IN      AMD_CPM_TABLE_PROTOCOL  *CpmTableProtocolPtr
  );

VOID
AmdCpmDxeGeventInit (
  IN      AMD_CPM_TABLE_PROTOCOL  *CpmTableProtocolPtr
  );

VOID
AmdCpmGeventSmiControlInit (
  IN      AMD_CPM_TABLE_PROTOCOL  *CpmTableProtocolPtr
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM GPIO Init DXE driver
 *
 * This function sets GEVENT pins and internal PCIe clock.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmGpioInitDxeEntryPoint (
  IN      EFI_HANDLE                      ImageHandle,
  IN      EFI_SYSTEM_TABLE                *SystemTable
  )
{
  EFI_STATUS                              Status;
  EFI_EVENT                               ReadyToBootEvent;
  AMD_CPM_TABLE_PROTOCOL                  *CpmTableProtocolPtr;
  EFI_EVENT                               AfterInitEnvEvent;
  VOID                                    *mAfterInitEnvEvent;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->LocateProtocol (  &gAmdCpmTableProtocolGuid,
                                  NULL,
                                  (VOID**)&CpmTableProtocolPtr
                                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpGpioInitDxeDriverBegin);

  //
  // First test gFchInitDonePolicyProtocolGuid is installed or not.
  //
  Status = gBS->LocateProtocol (
                  &gFchInitDonePolicyProtocolGuid,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    //
    // If gFchInitDonePolicyProtocolGuid still not be installed, RegisterProtocolNotify
    //
    Status = gBS->CreateEvent (
                    CPM_EVENT_NOTIFY_SIGNAL,
                    CPM_TPL_NOTIFY,
                    AmdCpmGpioInitMidNotifyEvent,
                    (VOID*)CpmTableProtocolPtr,
                    &AfterInitEnvEvent
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = gBS->RegisterProtocolNotify (
                    &gFchInitDonePolicyProtocolGuid,
                    AfterInitEnvEvent,
                    &mAfterInitEnvEvent
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    //
    // Already have gFchInitDonePolicyProtocolGuid, invoke AmdCpmGpioInitMid()
    //
    AmdCpmGpioInitMid (CpmTableProtocolPtr);
    AmdCpmGpioInitMid (CpmTableProtocolPtr);
  }

  Status = gBS->CreateEventEx (
                  CPM_EVENT_NOTIFY_SIGNAL,
                  CPM_TPL_NOTIFY,
                  AmdCpmGpioInitLate,
                  (VOID*)CpmTableProtocolPtr,
                  &gEfiEventReadyToBootGuid,
                  &ReadyToBootEvent
                  );

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpGpioInitDxeDriverEnd);

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init internal PCIe clock.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmGpioInitLate (
  IN      EFI_EVENT        Event,
  IN      VOID             *Context
  )
{
  STATIC BOOLEAN  AmdCpmGpioInitLateInvoked = FALSE;

  RECORD_TIME_DXE (BeginAmdCpmGpioInitDxeDriver);

  if (!AmdCpmGpioInitLateInvoked) {
    AmdCpmGeventSmiControlInit (Context);
    AmdCpmDxePcieClockInit (Context);
  }

  AmdCpmGpioInitLateInvoked = TRUE;
  RECORD_TIME_DXE (EndAmdCpmGpioInitDxeDriver);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init GEVENT pins
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmGpioInitMid (
  IN      VOID             *Context
  )
{
  STATIC BOOLEAN  AmdCpmGpioInitMidInvoked = FALSE;

  RECORD_TIME_DXE (BeginAmdCpmGpioInitDxeDriver);

  if (!AmdCpmGpioInitMidInvoked) {
    AmdCpmDxeGeventInit (Context);
  }

  AmdCpmGpioInitMidInvoked = TRUE;
  RECORD_TIME_DXE (EndAmdCpmGpioInitDxeDriver);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init GEVENT pins
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmGpioInitMidNotifyEvent (
  IN      EFI_EVENT        Event,
  IN      VOID             *Context
  )
{
  AmdCpmGpioInitMid (Context);
}

VOID
AmdCpmDxeAddOneItemInClkList (
  IN      AMD_CPM_EXT_CLKGEN_TABLE    *ExtClkGenTablePtr,
  IN      AMD_CPM_EXT_CLKGEN_ITEM     *ListPtr,
  IN      UINT8                       *ListNum,
  IN      UINT8                       ClkNum,
  IN      UINT8                       ClkReq
  )
{
  AMD_CPM_EXT_CLKGEN_ITEM     *CurrentItemPtr;
  UINT8   Index;
  UINT8   Index2;
  if (ClkNum == 0xFE) {
    return;
  }
  for (Index = 0; Index < AMD_EXT_CLKGEN_SIZE; Index++) {
    if (ExtClkGenTablePtr->Item[Index].Function == 0xFF) {
      break;
    }
    if (ExtClkGenTablePtr->Item[Index].Function == ClkNum + 0x80 && ClkReq == 0) {
      CurrentItemPtr = &ExtClkGenTablePtr->Item[Index];
    } else if (ExtClkGenTablePtr->Item[Index].Function == ClkReq + 0x8F && ClkReq != 0xFF && ClkReq != 0) {
      CurrentItemPtr = &ExtClkGenTablePtr->Item[Index];
    } else {
      continue;
    }
    for (Index2 = 0; Index2 < (*ListNum); Index2++) {
      if (ListPtr[Index2].Offset == CurrentItemPtr->Offset) {
        ListPtr[Index2].AndMask &= CurrentItemPtr->AndMask;
        ListPtr[Index2].OrMask |= CurrentItemPtr->OrMask;
        break;
      }
    }
    if (Index2 == (*ListNum)) {
      ListPtr[Index2].Function = 0;
      ListPtr[Index2].Offset = CurrentItemPtr->Offset;
      ListPtr[Index2].AndMask = CurrentItemPtr->AndMask;
      ListPtr[Index2].OrMask = CurrentItemPtr->OrMask;
      (*ListNum) ++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to initialize internal PCIe clock.
 *
 * @param[in]     CpmTableProtocolPtr Pointer to AMD CPM Table Protocol
 *
 */
VOID
AmdCpmDxePcieClockInit (
  IN      AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr
  )
{
  AMD_CPM_PCIE_CLOCK_TABLE            *CpmPcieClockTablePtr;
  AMD_CPM_PCIE_CLOCK_ITEM             *TablePtr;
  UINT8                               SlotStatus;
  BOOLEAN                             ClockType;
  AMD_CPM_EXT_CLKGEN_TABLE            *ExtClkGenTablePtr;
  AMD_CPM_EXT_CLKGEN_ITEM             ClkGen[AMD_PCIE_CLOCK_SIZE];
  AMD_CPM_SAVE_CONTEXT_TABLE          *SaveContextTablePtr;
  UINT8                               Index;
  UINT8                               Data;
  UINT8                               i;
  UINT32                              PcieSlotStatus;
  UINT32                              PcieSlotStatusHigh;

  ExtClkGenTablePtr = NULL;
  Index = 0;
  PcieSlotStatus = 0;
  PcieSlotStatusHigh = 0;
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpGpioInitDxePcieClockInitBegin);
  CpmPcieClockTablePtr  = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_CLOCK);
  SaveContextTablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_SAVE_CONTEXT);
  ClockType             = (BOOLEAN) CpmTableProtocolPtr->CommonFunction.GetStrap (CpmTableProtocolPtr) & BIT1;
  if (!ClockType) {
    ExtClkGenTablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_EXT_CLKGEN);
    if (!ExtClkGenTablePtr) {
      return;
    }
  }
  if (CpmPcieClockTablePtr) {
    TablePtr = &CpmPcieClockTablePtr->Item[0];
    i = 0;
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));
    while (TablePtr->ClkId != 0xFF) {
      SlotStatus = 0;
      if (TablePtr->SlotCheck & BIT1) {
        SlotStatus = CpmTableProtocolPtr->CommonFunction.DetectDevice (CpmTableProtocolPtr, TablePtr->DeviceId, NULL) ? BIT1 : 0;
      }
      if (TablePtr->SlotCheck & (BIT3 + BIT2 + BIT0)) {
        SlotStatus |= CpmTableProtocolPtr->CommonFunction.CheckPcieDevice (CpmTableProtocolPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), TablePtr->Device, TablePtr->Function);
      }
      DEBUG((DEBUG_INFO, "  Item[%X] Socket=%02X Die=%02X Bridge=%02X Miscid=%02X", i, \
            (TablePtr->SpecialFunctionId >> 24) & 0xF, (TablePtr->SpecialFunctionId >> 20) & 0xF, \
            (TablePtr->SpecialFunctionId >> 16) & 0xF, (TablePtr->SpecialFunctionId >> 28) & 0xF));
      DEBUG((DEBUG_INFO, " Device=%02X  Function=%02X  SlotCheck=%02X  SpecialFunctionId=%X  SlotStatus=%02X\n", \
            TablePtr->Device, TablePtr->Function, TablePtr->SlotCheck, (TablePtr->SpecialFunctionId & 0xFFFF), SlotStatus));
      if ((SlotStatus > 0) && (((SlotStatus & 0xFE) & TablePtr->SlotCheck) == 0)) {
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-SlotStatus > 0 & ((SlotStatus & 0xFE) & TablePtr->SlotCheck) = 0\n"));
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-Set ClkReq & ClkReqExt = 0xFF\n"));
        TablePtr->ClkReq = 0xFF;
        TablePtr->ClkReqExt = 0xFF;
      }
      if ((SlotStatus == 0) && ((TablePtr->SlotCheck & (BIT1 + BIT0)) > 0) && CpmTableProtocolPtr->MainTablePtr->UnusedGppClkOffEn) {
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-SlotStatus=0 & (SlotCheck&(BIT1+BIT0))>0 & UnusedGppClkOffEn=1\n"));
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-Set ClkReq & ClkReqExt = 0\n"));
        TablePtr->ClkReq = 0;
        TablePtr->ClkReqExt = 0;
      }
      if (i < 8) {
        PcieSlotStatus |= SlotStatus << (4 * i);
      } else {
        PcieSlotStatusHigh |= SlotStatus << (4 * (i - 8));
      }
      if (ClockType) {
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-ClockType = 1\n"));
        if (CpmTableProtocolPtr->CommonFunction.GetClkReq (CpmTableProtocolPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 28) & 0xF), TablePtr->ClkId) == 1) {
          DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-L1SS is enabled, don't do SetClkReq\n"));
        } else {
          DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-SetClkReq\n"));
          CpmTableProtocolPtr->CommonFunction.SetClkReq (CpmTableProtocolPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 28) & 0xF), TablePtr->ClkId, TablePtr->ClkReq);
        }
      } else {
        DEBUG((DEBUG_INFO, "FEA-DXE-AmdCpmDxePcieClockInit-ClockType = 0-AmdCpmDxeAddOneItemInClkList\n"));
        AmdCpmDxeAddOneItemInClkList (ExtClkGenTablePtr, &ClkGen[0], &Index, TablePtr->ClkIdExt, TablePtr->ClkReqExt);
      }
      TablePtr++;
      i++;
    }
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));

    if (SaveContextTablePtr) {
      if (CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, BootMode)) == CPM_BOOT_MODE_S0) {
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x00, (UINT8) (PcieSlotStatus));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x01, (UINT8) (PcieSlotStatus >> 8));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x02, (UINT8) (PcieSlotStatus >> 16));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x03, (UINT8) (PcieSlotStatus >> 24));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x04, (UINT8) (PcieSlotStatusHigh));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x05, (UINT8) (PcieSlotStatusHigh >> 8));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x06, (UINT8) (PcieSlotStatusHigh >> 16));
        CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x07, (UINT8) (PcieSlotStatusHigh >> 24));
      }
    }
    if (!ClockType) {
      i = 0;
      while (Index > 0) {
        if (CpmTableProtocolPtr->CommonFunction.ReadSmbusBlock) {
          CpmTableProtocolPtr->CommonFunction.ReadSmbusBlock (
                                                CpmTableProtocolPtr,
                                                ExtClkGenTablePtr->SmbusSelect,
                                                ExtClkGenTablePtr->SmbusAddress,
                                                ClkGen[i].Offset,
                                                1,
                                                &Data
                                                );
          Data = (Data & ClkGen[i].AndMask) | ClkGen[i].OrMask;
          CpmTableProtocolPtr->CommonFunction.WriteSmbusBlock (
                                                CpmTableProtocolPtr,
                                                ExtClkGenTablePtr->SmbusSelect,
                                                ExtClkGenTablePtr->SmbusAddress,
                                                ClkGen[i].Offset,
                                                1,
                                                &Data
                                                );
        }
        Index --;
        i ++;
      }
    }
  }

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpGpioInitDxePcieClockInitEnd);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to initialize GEVENT pins.
 *
 * @param[in]     CpmTableProtocolPtr Pointer to AMD CPM Table Protocol
 *
 */
VOID
AmdCpmDxeGeventInit (
  IN      AMD_CPM_TABLE_PROTOCOL  *CpmTableProtocolPtr
  )
{
  AMD_CPM_GEVENT_INIT_TABLE       *GeventTablePtr;
  AMD_CPM_GEVENT_ITEM             *TablePtr;
  AMD_CPM_EXPRESS_CARD_TABLE      *ExpressCardTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE  *OtherHotplugTablePtr;
  AMD_CPM_ZERO_POWER_ODD_TABLE    *ZeroPowerOddTablePtr;

  GeventTablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_GEVENT_INIT);
  if (GeventTablePtr) {
    TablePtr = &GeventTablePtr->GeventList[0];
    while (TablePtr->Pin != 0xFF) {
      CpmTableProtocolPtr->CommonFunction.SetGevent (CpmTableProtocolPtr, TablePtr->Pin, TablePtr->Setting.Raw);
      TablePtr++;
    }
  }

  ExpressCardTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_EXPRESS_CARD);
  if (ExpressCardTablePtr) {
    CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                ExpressCardTablePtr->EventPin,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, ExpressCardTablePtr->EventPin) ? 0 : 1
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
    }
    if ((OtherHotplugTablePtr->Number > 1) && (OtherHotplugTablePtr->EventSource1 == 0)) {
      CpmTableProtocolPtr->CommonFunction.SetGeventSciTrig (
                                                CpmTableProtocolPtr,
                                                OtherHotplugTablePtr->EventPin1,
                                                CpmTableProtocolPtr->CommonFunction.GetGevent (CpmTableProtocolPtr, OtherHotplugTablePtr->EventPin1) ? 0 : 1
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
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to initialize SMI Control for GEVENT pins.
 *
 * @param[in]     CpmTableProtocolPtr Pointer to AMD CPM Table Protocol
 *
 */
VOID
AmdCpmGeventSmiControlInit (
  IN      AMD_CPM_TABLE_PROTOCOL  *CpmTableProtocolPtr
  )
{
  AMD_CPM_GEVENT_INIT_TABLE       *GeventTablePtr;
  AMD_CPM_GEVENT_ITEM             *TablePtr;

  GeventTablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_GEVENT_INIT);
  if (GeventTablePtr) {
    TablePtr = &GeventTablePtr->GeventList[0];
    while (TablePtr->Pin != 0xFF) {
      if (TablePtr->Pin < 0x40) {
        CpmTableProtocolPtr->CommonFunction.SetSmiControl (CpmTableProtocolPtr, (UINT8) TablePtr->Pin, TablePtr->Setting.Raw);
      }
      TablePtr++;
    }
  }
}
