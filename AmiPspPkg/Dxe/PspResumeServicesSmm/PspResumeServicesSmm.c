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
#include "PiSmm.h"
#include <Library/SynchronizationLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include "Library/SmmServicesTableLib.h"
#include <Library/UefiLib.h>
#include <Protocol/AmdPspResumeServiceProtocol.h>


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */

// Below structure is copied from PiSmmCpuDxeSmm.h >>>
///
/// The type of SMM CPU Information
///
typedef struct {
  SPIN_LOCK                         *Busy;
  volatile EFI_AP_PROCEDURE         Procedure;
  volatile VOID                     *Parameter;
  volatile UINT32                   *Run;
  volatile BOOLEAN                  *Present;
} SMM_CPU_DATA_BLOCK;

typedef enum {
  SmmCpuSyncModeTradition,
  SmmCpuSyncModeRelaxedAp,
  SmmCpuSyncModeMax
} SMM_CPU_SYNC_MODE;

typedef struct {
  //
  // Pointer to an array. The array should be located immediately after this structure
  // so that UC cache-ability can be set together.
  //
  SMM_CPU_DATA_BLOCK            *CpuData;
  volatile UINT32               *Counter;
  volatile UINT32               BspIndex;
  volatile BOOLEAN              *InsideSmm;
  volatile BOOLEAN              *AllCpusInSync;
  volatile SMM_CPU_SYNC_MODE    EffectiveSyncMode;
  volatile BOOLEAN              SwitchBsp;
  volatile BOOLEAN              *CandidateBsp;
} SMM_DISPATCHER_MP_SYNC_DATA;
//<<<

/*----------------------------------------------------------------------------------------
 *               G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

extern	EFI_GUID	gAmiMpSyncDataProtocolGuid;

/*----------------------------------------------------------------------------------------
 *               L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
    Initialize the mSmmMpSyncData from UefiCpuPkg/MpService.c when system resumes from S3

  @param ResumeType  The type from resume. S3 or S0i3
  @param VOID        The Context

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
EFIAPI
PspResumeCallback (
  IN  RESUME_TYPE   ResumeType,
  IN  VOID          *Context
  )
{
    UINT8	                        i = 0;
    EFI_STATUS                      Status;
    SMM_DISPATCHER_MP_SYNC_DATA     *mSmmMpSyncData = NULL;

    Status = gSmst->SmmLocateProtocol(
                    &gAmiMpSyncDataProtocolGuid,
                    NULL,
                    (VOID**)&mSmmMpSyncData);

    if (Status != EFI_SUCCESS)
        return  Status;

    DEBUG((DEBUG_INFO, "mSmmMpSyncData = %x \n", mSmmMpSyncData));

    // Initialize the flags for SMM
    if (FeaturePcdGet (PcdCpuSmmEnableBspElection)) {
        mSmmMpSyncData->BspIndex = (UINT32)-1;
    }

    *mSmmMpSyncData->Counter = 0;
    *mSmmMpSyncData->AllCpusInSync = FALSE;
    *mSmmMpSyncData->InsideSmm = FALSE;

    for (i = 0; i < gSmst->NumberOfCpus; i++)
    {
        *mSmmMpSyncData->CpuData[i].Busy = 0;
        *mSmmMpSyncData->CpuData[i].Run = 0;
        *mSmmMpSyncData->CpuData[i].Present = FALSE;
    }
    return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * AMI Psp resume services main entry point
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
EFIAPI
AmiPspResumeServicesDriverEntryPoint (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS                     Status;
    PSP_RESUME_SERVICE_PROTOCOL	   *PspResume;

    // Register Psp resume servcies callback
    Status = gSmst->SmmLocateProtocol (
                  &gAmdPspResumeServiceProtocolGuid,
                  NULL,
                  &PspResume
                  );
    if (EFI_ERROR (Status)) {
        return EFI_SUCCESS;
    }
    Status = PspResume->Register (PspResume, PspResumeCallback, NULL, PSP_RESUME_CALLBACK_HIGHEST_LEVEL, PspResumeCallBackFlagBspOnly, NULL);

    return Status;
}



