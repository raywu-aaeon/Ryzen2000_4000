/*****************************************************************************
 *
 * Copyright 2017 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

EFI_GUID UCSI_ACPI_DEVICE_GUID = {
  0x7B95E3E3, 0x9E63, 0x4E85, 0x8A, 0xA8, 0x6B, 0xD4, 0x09, 0x95, 0xB0, 0x50
};

VOID
EFIAPI
AmdCpmUcsiInitLate (
  IN      EFI_EVENT       Event,
  IN      VOID            *Context
  );

BOOLEAN
EFIAPI
AmdCpmUcsiCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM UCSI DXE driver
 *
 * This function stores the setting of UCSI in NV Data and loads, updates
 * and installs UCSI SSDT Table.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmUcsiDxeEntryPoint (
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
                  AmdCpmUcsiInitLate,
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
AmdCpmUcsiInitLate (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_UCSI_TABLE              *CpmUcsiTablePtr;
  AMD_CPM_MAIN_TABLE              *CpmMainTablePtr;
  EFI_STATUS                      Status;
  UINT32                          Buffer[5];
  AMD_CPM_NV_DATA_STRUCT          *eNvStore;
  AMD_CPM_NV_DATA_PROTOCOL        *pAmdCpmNvDataProtocol;
  UINT32                          Data32;

  eNvStore    = 0;
  Data32      = 0;

  if (!InitlateInvoked) {

    Status = gBS->LocateProtocol (&gAmdCpmTableProtocolGuid, NULL, (VOID**)&CpmTableProtocolPtr);
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpUcsiDxeDriverBegin);

    CpmMainTablePtr = CpmTableProtocolPtr->MainTablePtr;
    CpmUcsiTablePtr = (AMD_CPM_UCSI_TABLE *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_UCSI);
    if (CpmUcsiTablePtr && CpmMainTablePtr->UcsiEn) {
      Status = gBS->LocateProtocol (&gAmdCpmNvDataProtocolGuid, NULL, (VOID**)&pAmdCpmNvDataProtocol);
      if (!EFI_ERROR (Status)) {
        eNvStore = pAmdCpmNvDataProtocol->NvDataPtr;
        Data32 = eNvStore->CpmUcsiTable;
        eNvStore->CpmUcsiOPMData            = Data32 + 0x1D;
        eNvStore->CpmUcsiEcUcsiLocation     = CpmUcsiTablePtr->EcUcsiLocation;
        eNvStore->CpmUcsiEcVersionLocation  = CpmUcsiTablePtr->EcUcsiLocation + CpmUcsiTablePtr->EcVersionLocation;
        eNvStore->CpmUcsiEcCciLocation      = CpmUcsiTablePtr->EcUcsiLocation + CpmUcsiTablePtr->EcCciLocation;
        eNvStore->CpmUcsiEcCtlLocation      = CpmUcsiTablePtr->EcUcsiLocation + CpmUcsiTablePtr->EcCtlLocation;
        eNvStore->CpmUcsiEcMgiLocation      = CpmUcsiTablePtr->EcUcsiLocation + CpmUcsiTablePtr->EcMgiLocation;
        eNvStore->CpmUcsiEcMgoLocation      = CpmUcsiTablePtr->EcUcsiLocation + CpmUcsiTablePtr->EcMgoLocation;
        eNvStore->CpmUcsiEcCommandIo        = CpmUcsiTablePtr->EcUcsiCommandIo;
        eNvStore->CpmUcsiEcUcsiCommand      = CpmUcsiTablePtr->EcUcsiCommand;
      }
      Buffer[0] = CFG_AMD_CPM_ASL_EC_NAME;      // PcdGet32 (EcAslName)
      Buffer[1] = CFG_AMD_CPM_ASL_EC_MUTEX;     // PcdGet32 (EcMutexAslName)
      Buffer[2] = CFG_AMD_CPM_ASL_LPC_NAME;     // PcdGet32 (LpcAslName)
      Buffer[3] = CFG_AMD_CPM_ASL_OKEC_NAME;    // PcdGet32 (OkEcAslName)
      Buffer[4] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmUcsiTablePtr->EcUcsiQEvent);
      CpmTableProtocolPtr->CommonFunction.AddSsdtTable ((VOID*)CpmTableProtocolPtr,
                                                        &UCSI_ACPI_DEVICE_GUID,
                                                        NULL,
                                                        AmdCpmUcsiCallBack,
                                                        &Buffer[0]);
    }
    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpUcsiDxeDriverEnd);
  }

  InitlateInvoked = TRUE;

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
AmdCpmUcsiCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;
  BufferPtr = (UINT32*)Context;

  switch (*((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('E', 'C', '0', '_')):
    if (*BufferPtr) {
      *(UINT32*) AmlObjPtr = *(UINT32*)BufferPtr;
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '0', '4', '2')):     // CpmKbcMutex: M042
    if (*(BufferPtr + 1)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('L', 'P', 'C', '0')):
    if (*(BufferPtr + 2)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 2);
    }
    break;
  case (CPM_SIGNATURE_32 ('O', 'K', 'E', 'C')):
    if (*(BufferPtr + 3)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 3);
    }
    break;
  case (CPM_SIGNATURE_32 ('X', 'Q', '5', '0')):
    if (*(BufferPtr + 4)) {
      *(UINT8*)AmlObjPtr = '_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 4);
    }
    break;
  }

  return FALSE;
}

