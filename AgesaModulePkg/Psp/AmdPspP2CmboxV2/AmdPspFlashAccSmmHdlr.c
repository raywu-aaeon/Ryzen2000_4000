
/* $NoKeywords:$ */
/**
 * @file
 *
 * PspP2Cmbox Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspP2Cmbox Driver
 * @e \$Revision$   @e \$Date$
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
#include "AmdPspP2CmboxV2.h"
#include <AmdPspSmmCommunication.h>
#include <Library/AmdPspFlashAccLib.h>
#include <Filecode.h>

#define FILECODE PSP_AMDPSPP2CMBOXV2_AMDPSPFLASHACCSMMHDLR_FILECODE

extern UINTN                                 mBlockSize;
extern PSP_NV_DESCRIPTOR mPspNvDb[];
extern EFI_HANDLE                            mPspSmmCommHandle;

EFI_STATUS
PspFlashAccSmmCommunicateHandler (
  IN       EFI_HANDLE  DispatchHandle,
  IN       CONST VOID  *Context,
  IN OUT   VOID    *CommBuffer,
  IN OUT   UINTN   *CommBufferSize
  )
{
  PSP_SMM_COMMUNICATION_CMN *Buffer;
  PSP_SMM_COMM_RW_FLASH *RwBuffer;
  PSP_SMM_COMM_ERASEFLASH *EraseBuffer;
  PSP_SMM_COMM_RPMC_INCMC *RpmcIncMcBuffer;
  PSP_SMM_COMM_RPMC_REQMC *RpmcReqMcBuffer;
  EFI_STATUS Status;

  Status = EFI_UNSUPPORTED;
  Buffer = (PSP_SMM_COMMUNICATION_CMN *)CommBuffer;
  IDS_HDT_CONSOLE_PSP_TRACE ("PspFlashAccSmmCommunicateHandler ID %x\n", Buffer->id);

  switch (Buffer->id) {
  case PSP_SMM_COMM_ID_GET_BLOCK_SIZE:
    Status = PspGetFlashBlockSize (&((PSP_SMM_COMM_GETBLKSIZE *) CommBuffer)->BlockSize);
    break;
  case PSP_SMM_COMM_ID_READ_FLASH:
    RwBuffer = (PSP_SMM_COMM_RW_FLASH *) CommBuffer;
    Status = PspReadFlash (RwBuffer->FlashAddress, &RwBuffer->NumBytes, RwBuffer->Buffer);
    break;
  case PSP_SMM_COMM_ID_WRITE_FALSH:
    RwBuffer = (PSP_SMM_COMM_RW_FLASH *) CommBuffer;
    Status = PspWriteFlash (RwBuffer->FlashAddress, &RwBuffer->NumBytes, RwBuffer->Buffer);
    break;
  case PSP_SMM_COMM_ID_ERASE_FALSH:
    EraseBuffer = (PSP_SMM_COMM_ERASEFLASH *) CommBuffer;
    Status = PspEraseFlash (EraseBuffer->FlashAddress, &EraseBuffer->NumBytes);
    break;
  case PSP_SMM_COMM_ID_CLOSE_INTERFACE:
    if (mPspSmmCommHandle != NULL) {
      Status = gSmst->SmiHandlerUnRegister (mPspSmmCommHandle);
    } else {
      Status = EFI_INVALID_PARAMETER;
      IDS_HDT_CONSOLE_PSP_TRACE ("mPspSmmCommHandle NULL\n");
    }
    break;
  case PSP_SMM_COMM_ID_RPMC_INCMC:
    RpmcIncMcBuffer = (PSP_SMM_COMM_RPMC_INCMC *) CommBuffer;
    Status = PspRpmcIncMc (RpmcIncMcBuffer->CounterAddr, RpmcIncMcBuffer->CounterData, RpmcIncMcBuffer->Signature);
    break;
  case PSP_SMM_COMM_ID_RPMC_REQMC:
    RpmcReqMcBuffer = (PSP_SMM_COMM_RPMC_REQMC *) CommBuffer;
    Status = PspRpmcReqMc (RpmcReqMcBuffer->CounterAddr, RpmcReqMcBuffer->Tag, RpmcReqMcBuffer->Signature, RpmcReqMcBuffer->CounterData, RpmcReqMcBuffer->OutputSignature);
    break;
  default:
    ASSERT (FALSE);
  }
  return Status;
}
