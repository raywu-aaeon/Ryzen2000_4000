/* $NoKeywords:$ */
/**
 * @file
 *
 * FchPcieWakeWA Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspSmm Driver
 * @e \$Revision: 330494 $   @e \$Date: 2015-11-09 17:22:37 +0800 (Mon, 09 Nov 2015) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 *******************************************************************************
 */
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/S3BootScriptLib.h>
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "AmdSmmCommunication.h"
#include "AmdS3SaveLibData.h"
#include "Filecode.h"


#define FILECODE PSP_AMDPSPSMMV1_AMDPSPSMMV1_FILECODE
EFI_HANDLE                      mAmdSmmCommunicationHandle;

VOID
AmdS3SaveScriptSmmDispatch (
  IN OUT   VOID    *PrivateDataAddress
  )
{
  AMD_S3_LIB_PRIVATE_DATA *AmdS3LibPrivateData;
  AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *AmdS3LibTblHdr;
  UINT8 *OpData;
  UINT16 OpCode;

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveScriptSmmDispatch Enter\n");

  //Locate the global data structure via PCD
  AmdS3LibPrivateData = NULL;
  AmdS3LibPrivateData = PrivateDataAddress;
  ASSERT (AmdS3LibPrivateData != NULL);

  //Validate the save table
  AmdS3LibTblHdr = (AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER *) AmdS3LibPrivateData->TableBase;
  ASSERT (AmdS3LibTblHdr->Sinature == AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG);
  if (AmdS3LibTblHdr->Sinature != AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3LibTbl Signature Check Fail\n");
    return;
  }
  ASSERT (*((UINT32 *) (AmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) == AMD_S3LIB_TABLE_WATCHER);
  if (*((UINT32 *) (AmdS3LibPrivateData->TableBase + AmdS3LibTblHdr->TableLength)) != AMD_S3LIB_TABLE_WATCHER) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Potencial memory overflow observed in AmdS3LibTbl\n");
    return;
  }
  //Loop the table, and invoke S3 Script Lib to save the script data
  OpData = &AmdS3LibTblHdr->Data;
  OpCode = ((AMD_S3LIB_BOOT_SCRIPT_COMMON *) OpData)->OpCode;
  while (OpCode != AMD_S3LIB_TABLE_END) {
    switch (OpCode) {
    case AMD_S3LIB_BOOT_SCRIPT_IO_WRITE_OP:
      S3BootScriptSaveIoWrite (((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpData)->Width,
                               ((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpData)->Address,
                               1,
                               &((AMD_S3LIB_BOOT_SCRIPT_IO_WRITE *) OpData)->Value);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_WRITE);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_IO_RMW_OP:
      S3BootScriptSaveIoReadWrite (((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpData)->Width,
                                   ((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpData)->Address,
                                   &((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpData)->Data,
                                   &((AMD_S3LIB_BOOT_SCRIPT_IO_RMW *) OpData)->DataMask);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_RMW);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_IO_POLL_OP:
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_IO_POLL);
      S3BootScriptSaveIoPoll (((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpData)->Width,
                              ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpData)->Address,
                              &((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpData)->Data,
                              &((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpData)->DataMask,
                              ((AMD_S3LIB_BOOT_SCRIPT_IO_POLL *) OpData)->Delay);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE_OP:
      S3BootScriptSaveMemWrite (((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpData)->Width,
                                ((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpData)->Address,
                                1,
                                &((AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE *) OpData)->Value);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_MEM_RMW_OP:
      S3BootScriptSaveMemReadWrite (((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpData)->Width,
                                    ((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpData)->Address,
                                    &((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpData)->Data,
                                    &((AMD_S3LIB_BOOT_SCRIPT_MEM_RMW *) OpData)->DataMask);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_RMW);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_MEM_POLL_OP:
      S3BootScriptSaveMemPoll (((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpData)->Width,
                               ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpData)->Address,
                               &((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpData)->DataMask,
                               &((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpData)->Data,
                               1,
                               ((AMD_S3LIB_BOOT_SCRIPT_MEM_POLL *) OpData)->LoopTimes);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_MEM_POLL);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE_OP:
      S3BootScriptSavePciCfg2Write (((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpData)->Width,
                                    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpData)->Segment,
                                    ((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpData)->Address,
                                    1,
                                    &((AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE *) OpData)->Value);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_PCI_RMW_OP:
      S3BootScriptSavePciCfg2ReadWrite (((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpData)->Width,
                                        ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpData)->Segment,
                                        ((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpData)->Address,
                                        &((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpData)->Data,
                                        &((AMD_S3LIB_BOOT_SCRIPT_PCI_RMW *) OpData)->DataMask);
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_RMW);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_PCI_POLL_OP:
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_PCI_POLL);
      S3BootScriptSavePci2Poll (((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->Width,
                                ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->Segment,
                                ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->Address,
                                &((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->Data,
                                &((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->DataMask,
                                ((AMD_S3LIB_BOOT_SCRIPT_PCI_POLL *) OpData)->Delay);
      break;
    case AMD_S3LIB_BOOT_SCRIPT_DISPATCH_OP:
      OpData += sizeof (AMD_S3LIB_BOOT_SCRIPT_DISPATCH);
      S3BootScriptSaveDispatch2 (((AMD_S3LIB_BOOT_SCRIPT_DISPATCH *) OpData)->EntryPoint,
                                 ((AMD_S3LIB_BOOT_SCRIPT_DISPATCH *) OpData)->Context);
      break;
    default:
      ASSERT (FALSE);
      break;
    }
    OpCode = ((AMD_S3LIB_BOOT_SCRIPT_COMMON *) OpData)->OpCode;
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveScriptSmmDispatch Exit\n");
}

EFI_STATUS
AmdS3SaveSmmCommunicateHandler (
  IN       EFI_HANDLE  DispatchHandle,
  IN       CONST VOID  *Context,
  IN OUT   VOID    *CommBuffer,
  IN OUT   UINTN   *CommBufferSize
  )
{
  AMD_SMM_COMMUNICATION_CMN *CmnBuffer;
  AMD_SMM_COMMUNICATION_S3SCRIPT *S3ScriptBuffer;
  EFI_STATUS  Status;

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveSmmCommunicateHandler Enter\n");

  S3ScriptBuffer = NULL;
  CmnBuffer = (AMD_SMM_COMMUNICATION_CMN *)CommBuffer;
  if (CmnBuffer->id == AMD_SMM_COMMUNICATION_ID_S3SCRIPT) {
    S3ScriptBuffer = (AMD_SMM_COMMUNICATION_S3SCRIPT *) CmnBuffer;
    AmdS3SaveScriptSmmDispatch (S3ScriptBuffer->PrivateDataAddress);
  }
  //Unregister the hanlder to make sure execute only once
  Status = gSmst->SmiHandlerUnRegister (mAmdSmmCommunicationHandle);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AmdS3SaveSmmCommunicateHandler Unregister Fail\n");
  }
  return EFI_SUCCESS;
}


EFI_STATUS
AmdSmmCommunicationEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  //
  // We're now in SMM!
  //

  //Register SMM Handler for handle the communication from outside of SMM
  mAmdSmmCommunicationHandle = NULL;
  Status = gSmst->SmiHandlerRegister (AmdS3SaveSmmCommunicateHandler, &gAmdSmmCommunicationHandleGuid, &mAmdSmmCommunicationHandle);
  ASSERT (Status == EFI_SUCCESS);

  return EFI_SUCCESS;
}


