/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Zen SMM Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   AMD CCX Zen SMM  Driver
 * @e \$Revision: 315303 $   @e \$Date: 2015-03-24 12:41:35 +0800 (Tue, 24 Mar 2015) $
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
#include "AGESA.h"
#include "PiSmm.h"
#include <Library/BaseLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/IdsLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/CcxRolesLib.h>
#include <Library/CcxSetMcaLib.h>
#include <Library/AmdHeapLib.h>
#include <Protocol/AmdPspResumeServiceProtocol.h>
#include <Protocol/FchSmmSwDispatch2.h>
#include "Filecode.h"

#define FILECODE CCX_ZEN_CCXZENRVSMM_AMDCCXZENRVSMM_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
CcxZenRvPfeh (
  );

VOID
CcxZenRvPfehAp (
  IN       VOID *Buffer
  );

VOID
CcxZenRvS3ResumeLateAp (
  IN       VOID *Buffer
  );

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */
/// for MSR S3 save/restore
typedef struct {
  IN  UINT32 MsrAddr;     ///< MSR address
  IN  UINT64 MsrData;     ///< MSR data
  IN  UINT64 MsrMask;     ///< Mask to be used before data write. Set every bit of all save/restore fields.
} S3_SAVE_MSR;


/*----------------------------------------------------------------------------------------
 *               G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
S3_SAVE_MSR     mMsrSaveRestoreTable[] =
{
  { 0xC0011093, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0011097, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010296, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  }, // Cstate_Config
  { 0xC0010064, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010065, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010066, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010067, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010068, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010069, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC001006A, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC001006B, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010015, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE  }, // HWCR, bit[0][SmmLock] should not be restored. IBV may clear this bit at very early of S3 resume path
                                                           // This register must be restored after all Pstate registers (0xC001_00[64:6B]) have been restored.
                                                           // Because bit21[LockTscToCurrentP0] must be restored after customizing Pstates
  { CPU_LIST_TERMINAL               }
};

UINT64 UcodePatch = 0;
BOOLEAN mPfehMode = FALSE;

/*----------------------------------------------------------------------------------------
 *               L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
CcxZenRvPfeh (
  )
{
  UINT16          i;

  CcxZenRvPfehAp (NULL);

  for (i = 1; i < gSmst->NumberOfCpus; i++) {
    gSmst->SmmStartupThisAp (
            CcxZenRvPfehAp,
            i,
            NULL
            );
  }
}

VOID
CcxZenRvPfehAp (
  IN       VOID *Buffer
  )
{
  // Platform First Error Handling
  if (mPfehMode) {
    AsmWriteMsr64 (0xC0010121, 0xFFFFFFFFFFFFFFFF);
    AsmWriteMsr64 (0xC0010122, 0);
    AsmMsrOr64 (0xC0010120, BIT0);
  } else {
    AsmWriteMsr64 (0xC0010121, 0);
    AsmWriteMsr64 (0xC0010122, 0);
    AsmMsrAnd64 (0xC0010120, ~(UINT64)BIT0);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Save MSRs to mMsrSaveRestoreTable
 *
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
CcxZenRvS3SaveSmi (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  UINTN  i;

  // Platform First Error Handling
  CcxZenRvPfeh ();

  for (i = 0; mMsrSaveRestoreTable[i].MsrAddr != CPU_LIST_TERMINAL; i++) {
    mMsrSaveRestoreTable[i].MsrData = AsmReadMsr64 (mMsrSaveRestoreTable[i].MsrAddr);
  }

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function for restore MSRs from mMsrSaveRestoreTable
 *
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
CcxZenRvS3RestoreSmi (
  IN  RESUME_TYPE   ResumeType,
  IN  VOID          *Context
  )
{
  UINTN  i;

  if (CcxIsBsp (NULL)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvS3RestoreSmi\n");
    // Clear MSRC001_1023[49, TwCfgCombineCr0Cd]  /// A bug that this bit was restored to 1 by ucode when resume from S3
                                                  /// but all APs are not launched which makes cache as UC. So clear this bit for BSP and re-set it after
                                                  /// all APs get lauched. So please re-set this bit in PEI (refer to AmdCcxZenRvPei.c)
    AsmMsrAnd64 (0xC0011023, ~((UINT64) BIT49));

    // Workaround PLAT-11398
    // BSP gets ucode patch address from scratch MSR
    UcodePatch = AsmReadMsr64 (0xC001100C);
  }

  // Set ApicEn
  AsmMsrOr32 (0x1B, BIT11);

  // Workaround PLAT-11398, reload ucode patch during S3 resume
  if (CcxIsComputeUnitPrimary (NULL)) {
    if (UcodePatch != 0) {
      AsmWriteMsr64 (0xC0010020, UcodePatch);
    }
  }

  for (i = 0; mMsrSaveRestoreTable[i].MsrAddr != CPU_LIST_TERMINAL; i++) {
    IDS_HDT_CONSOLE (CPU_TRACE, "Restoring MSR %X with %lX\n", mMsrSaveRestoreTable[i].MsrAddr, mMsrSaveRestoreTable[i].MsrData);
    AsmMsrAndThenOr64 (mMsrSaveRestoreTable[i].MsrAddr, ~(mMsrSaveRestoreTable[i].MsrMask), (mMsrSaveRestoreTable[i].MsrData & mMsrSaveRestoreTable[i].MsrMask));
  }

  // Mca initialization
  CcxSetMca ();

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * All threads need to perform the following at late S3 resume:
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
CcxZenRvS3ResumeLateSmi (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  UINT16          i;

  IDS_HDT_CONSOLE (CPU_TRACE, "CcxZenRvS3ResumeLateSmi Entry\n");

  CcxZenRvS3ResumeLateAp (NULL);

  for (i = 1; i < gSmst->NumberOfCpus; i++) {
    gSmst->SmmStartupThisAp (
            CcxZenRvS3ResumeLateAp,
            i,
            NULL
            );
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "CcxZenRvS3ResumeLateSmi Exit\n");
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * This routine runs after S3 boot script has been executed and does the following:
 * - Force recalculation of TSC after custom Pstates registers have been restored
 */
/*----------------------------------------------------------------------------------------*/
VOID
CcxZenRvS3ResumeLateAp (
  IN       VOID *Buffer
  )
{
  UINT64 LocalMsrRegister;

  // Force recalc of TSC
  LocalMsrRegister = AsmReadMsr64 (0xC0010064);
  AsmWriteMsr64 (0xC0010064, LocalMsrRegister);

  // Clear and set again CpbDis
  LocalMsrRegister = AsmReadMsr64 (0xC0010015);
  if ((LocalMsrRegister & BIT25) == BIT25) {
     AsmMsrAnd64 (0xC0010015, ~((UINT64) BIT25));
     AsmMsrOr64 (0xC0010015, BIT25);
  }

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * AMD ZEN driver main entry point
 *
 *
 * @param[in]       ImageHandle           Image Handle
 * @param[in]       SystemTable           Pointer to system globals
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
AmdCcxZenRvSmmDriverEntryPoint (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  PSP_RESUME_SERVICE_PROTOCOL    *PspResume;
  FCH_SMM_SW_DISPATCH2_PROTOCOL  *SwDispatch;
  FCH_SMM_SW_REGISTER_CONTEXT     SwContext;
  EFI_HANDLE                      SwHandle;
  LOCATE_HEAP_PTR                 LocateHeapParams;

  AGESA_TESTPOINT (TpCcxSmmEntry, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvSmm Entry\n");

  LocateHeapParams.BufferHandle = AMD_PFEH_HANDLE;
  if (HeapLocateBuffer (&LocateHeapParams, NULL) == AGESA_SUCCESS) {
    mPfehMode = *((BOOLEAN *) LocateHeapParams.BufferPtr);
  }

  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmSwDispatch2ProtocolGuid,
                  NULL,
                  &SwDispatch
                  );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Locate gFchSmmSwDispatch2ProtocolGuid failed\n");
    return Status;
  }

  // Install Save MSRs SMI handler
  SwContext.AmdSwValue  = PcdGet8 (PcdAmdCcxS3SaveSmi);
  SwContext.Order       = 0x80;
  Status = SwDispatch->Register (
                          SwDispatch,
                          CcxZenRvS3SaveSmi,
                          &SwContext,
                          &SwHandle
                          );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvS3SaveSmi is not registered\n");
    return Status;
  }

  // Install S3 resume late handler
  SwContext.AmdSwValue  = PcdGet8 (PcdFchOemBeforePciRestoreSwSmi);
  SwContext.Order       = 0x80;
  Status = SwDispatch->Register (
                          SwDispatch,
                          CcxZenRvS3ResumeLateSmi,
                          &SwContext,
                          &SwHandle
                          );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvS3ResumeLateSmi is not registered\n");
    return Status;
  }

  // Install Restore MSRs callback
  Status = gSmst->SmmLocateProtocol (
                  &gAmdPspResumeServiceProtocolGuid,
                  NULL,
                  &PspResume
                  );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Locate gAmdPspResumeServiceProtocolGuid failed\n");
    return Status;
  }
  PspResume->Register (PspResume, CcxZenRvS3RestoreSmi, mMsrSaveRestoreTable, PSP_RESUME_CALLBACK_HIGHEST_LEVEL, PspResumeCallBackFlagAllCores, NULL);

  // IDS Hook
  IDS_HOOK (IDS_HOOK_CCX_SMM, NULL, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvSmm End\n");

  AGESA_TESTPOINT (TpCcxSmmExit, NULL);

  return Status;
}


