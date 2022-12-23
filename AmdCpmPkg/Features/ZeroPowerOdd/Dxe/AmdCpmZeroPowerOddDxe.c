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

EFI_GUID ZERO_POWER_ODD_FM15_ACPI_DEVICE_GUID = {
  0xb7951665, 0x0280, 0x487a, 0x83, 0xb6, 0x36, 0x27, 0x1d, 0x4c, 0x3a, 0x90
};

EFI_GUID ZERO_POWER_ODD_FM17_ACPI_DEVICE_GUID = {
  0xBB5576D8, 0xA414, 0x4A8A, 0xA0, 0xDC, 0x07, 0x09, 0x36, 0xFE, 0x2C, 0x02
};

VOID
EFIAPI
AmdCpmZeroPowerOddInitLate (
  IN      EFI_EVENT       Event,
  IN      VOID            *Context
  );

BOOLEAN
EFIAPI
AmdCpmZeroPowerOddCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Zero Power Oddd DXE driver
 *
 * This function stores the setting of Zero Power Odd in NV Data and loads, updates
 * and installs Zero Power Odd SSDT Table.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmZeroPowerOddDxeEntryPoint (
  IN      EFI_HANDLE              ImageHandle,
  IN      EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       ReadyToBootEvent;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->CreateEventEx (
                  CPM_EVENT_NOTIFY_SIGNAL,
                  CPM_TPL_CALLBACK,
                  AmdCpmZeroPowerOddInitLate,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &ReadyToBootEvent
                  );

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * The function to load AMD CPM Zero Power Odd SSDT table.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */
VOID
EFIAPI
AmdCpmZeroPowerOddInitLate (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_ZERO_POWER_ODD_TABLE    *CpmZeroPowerOddTablePtr;
  AMD_CPM_MAIN_TABLE              *CpmMainTablePtr;
  EFI_STATUS                      Status;
  UINT32                          Buffer[14];
  UINT8                           CpuRevisionId;

  RECORD_TIME_DXE (BeginAmdCpmZeroPowerOddDxeDriver);

  if (!InitlateInvoked) {

    Status = gBS->LocateProtocol (&gAmdCpmTableProtocolGuid, NULL, (VOID**)&CpmTableProtocolPtr);
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpZeroPowerOddDxeDriverBegin);

    CpmMainTablePtr         = CpmTableProtocolPtr->MainTablePtr;
    CpmZeroPowerOddTablePtr = (AMD_CPM_ZERO_POWER_ODD_TABLE *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_ZERO_POWER_ODD);
    if (CpmZeroPowerOddTablePtr) {
      if (CpmMainTablePtr->ZeroPowerOddEn & BIT0) {
        if (!(CpmZeroPowerOddTablePtr->SataModeSupportMask & CpmTableProtocolPtr->CommonFunction.GetSataMode (CpmTableProtocolPtr))) {
          CpmMainTablePtr->ZeroPowerOddEn &= 0xF6;
        }
        if (CpmZeroPowerOddTablePtr->EventSource1 == 0) {
          Buffer[0] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, CpmZeroPowerOddTablePtr->EventPin1));
        } else {
          Buffer[0] = 0;
        }
        if ((CpmMainTablePtr->ZeroPowerOddEn & BIT1) && (CpmZeroPowerOddTablePtr->EventSource2 == 0)) {
          Buffer[1] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, CpmZeroPowerOddTablePtr->EventPin2));
        } else {
          Buffer[1] = 0;
        }
        Buffer[2] = (UINT32) CpmZeroPowerOddTablePtr->SataPortId;
        if (CpmZeroPowerOddTablePtr->EventSource1 == 0) {
          Buffer[3] = (UINT32) CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, CpmZeroPowerOddTablePtr->EventPin1);
        } else {
          Buffer[3] = (UINT32) CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, CpmZeroPowerOddTablePtr->EventPin3);
        }
        if (CpmMainTablePtr->ZeroPowerOddEn & BIT3) {
          Buffer[4] = 1;
        } else {
          Buffer[4] = 0;
        }
        if (CpmZeroPowerOddTablePtr->EventSource1 != 0) {
          Buffer[5] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmZeroPowerOddTablePtr->QEventFalling1);
          Buffer[6] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmZeroPowerOddTablePtr->QEventRising1);
        } else {
          Buffer[5] = 0;
          Buffer[6] = 0;
        }
        if ((CpmMainTablePtr->ZeroPowerOddEn & BIT1) && (CpmZeroPowerOddTablePtr->EventSource2 != 0)) {
          Buffer[7] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmZeroPowerOddTablePtr->QEventFalling2);
          Buffer[8] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmZeroPowerOddTablePtr->QEventRising2);
        } else {
          Buffer[7] = 0;
          Buffer[8] = 0;
        }
        Buffer[9] = CFG_AMD_CPM_ASL_EC_NAME;      // PcdGet32 (EcAslName)
        Buffer[10] = CFG_AMD_CPM_ASL_EC_MUTEX;    // PcdGet32 (EcMutexAslName)
        Buffer[11] = CFG_AMD_CPM_ASL_LPC_NAME;    // PcdGet32 (LpcAslName)
        Buffer[12] = CFG_AMD_CPM_ASL_OKEC_NAME;   // PcdGet32 (OkEcAslName)
        CpuRevisionId = CpmTableProtocolPtr->CommonFunction.GetCpuRevisionId (CpmTableProtocolPtr);
        if (CpuRevisionId < CPM_CPU_REVISION_ID_ZP) {
          Buffer[13] = 0;
          CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                              &ZERO_POWER_ODD_FM15_ACPI_DEVICE_GUID,
                                                              NULL,
                                                              AmdCpmZeroPowerOddCallBack,
                                                              &Buffer[0]
                                                           );
        } else {
          Buffer[13] = CFG_AMD_CPM_ASL_GP18_NAME;   // PcdGet32 (PcieGp18AslName)
          CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                              &ZERO_POWER_ODD_FM17_ACPI_DEVICE_GUID,
                                                              NULL,
                                                              AmdCpmZeroPowerOddCallBack,
                                                              &Buffer[0]
                                                           );
        }
      } else {
        CpmMainTablePtr->ZeroPowerOddEn &= 0xF6;
      }
    }
    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpZeroPowerOddDxeDriverEnd);
  }

  InitlateInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmZeroPowerOddDxeDriver);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to override Zero Power Odd SSDT Table
 *
 * This function is used to update GPE numbers and SATA port number.
 *
 * @param[in]     This           Pointer to Protocol
 * @param[in]     AmlObjPtr      The AML Object Buffer
 * @param[in]     Context        The Parameter Buffer
 *
 * @retval        TRUE           SSDT Table has been updated completely
 * @retval        FALSE          SSDT Table has not been updated completely
 */
BOOLEAN
EFIAPI
AmdCpmZeroPowerOddCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;
  BufferPtr = (UINT32*)Context;

  switch (*((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('X', 'L', '0', '6')):
    if (*BufferPtr) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)BufferPtr;
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'L', '1', '0')):
    if (*(BufferPtr + 1)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('Z', 'P', 'R', 'W')):
    if (*(BufferPtr + 3)) {
      if (*((UINT32*)AmlObjPtr + 1) == 0x0A020612) {
        *((UINT8*)AmlObjPtr + 8) = *(UINT8*)(BufferPtr + 3);
      }
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'P', 'R', 'W')):
    if (*(BufferPtr + 4)) {
      *(UINT8*)AmlObjPtr = '_';
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'E', 'J', '0')):
    if (*(BufferPtr + 1)) {
      *(UINT8*)AmlObjPtr = '_';
    } else if (*(BufferPtr + 8)) {
      *(UINT8*)AmlObjPtr = '_';
    }
    break;
  case (CPM_SIGNATURE_32 ('P', 'R', 'T', '1')):
    *((UINT8 *)AmlObjPtr + 3) = '0' + *(UINT8*)(BufferPtr + 2);
    break;
  case (CPM_SIGNATURE_32 ('X', 'Q', '4', '2')):
    if (*(BufferPtr + 5)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 5);
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'Q', '4', '3')):
    if (*(BufferPtr + 6)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 6);
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'Q', '4', '0')):
    if (*(BufferPtr + 7)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 7);
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'Q', '4', '1')):
    if (*(BufferPtr + 8)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 8);
    }
    break;
  case (CPM_SIGNATURE_32 ('E', 'C', '0', '_')):
    if (*(BufferPtr + 9)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 9);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '0', '4', '2')):     // CpmKbcMutex: M042
    if (*(BufferPtr + 10)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 10);
    }
    break;
  case (CPM_SIGNATURE_32 ('L', 'P', 'C', '0')):
    if (*(BufferPtr + 11)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 11);
    }
    break;
  case (CPM_SIGNATURE_32 ('O', 'K', 'E', 'C')):
    if (*(BufferPtr + 12)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 12);
    }
    break;
  case (CPM_SIGNATURE_32 ('G', 'P', '1', '8')):
    if (*(BufferPtr + 13)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 13);
    }
    break;
  }

  return FALSE;
}

