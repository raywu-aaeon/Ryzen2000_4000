/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU prefetch functions.
 *
 * This funtion provides for performance tuning to optimize for specific
 * workloads. For general performance use the recommended settings.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx
 * @e \$Revision: 315062 $   @e \$Date: 2015-03-19 07:54:52 +0800 (Thu, 19 Mar 2015) $
 *
 */
/*
 ****************************************************************************
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseLib.h>
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include "cpuRegisters.h"
#include "CcxZenZpPrefetch.h"
#include "Library/AmdBaseLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/CcxRolesLib.h"
#include "Protocol/MpService.h"

#define FILECODE CCX_ZEN_CCXZENZPDXE_CCXZENZPPREFETCH_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
CcxZpPrefetchModeAps (
  IN       CCX_PREFETCH_MODE                *PrefetchMode
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZpInitializePrefetchMode
 *
 *  Description:
 *    This funtion provides for performance tuning to optimize for specific
 *    workloads. For general performance use the recommended settings.
 *
 *  Parameters:
 *    @param[in]  StdHeader                 Config handle for library and services
 *
 *    @retval     AGESA_STATUS
 *
 *
 */
AGESA_STATUS
CcxZenZpInitializePrefetchMode (
  IN       AMD_CONFIG_PARAMS                *StdHeader
  )
{
  EFI_STATUS                Status;
  CCX_PREFETCH_MODE         PrefetchMode;
  EFI_MP_SERVICES_PROTOCOL *MpServices;

  PrefetchMode.HardwarePrefetchMode = PcdGet8 (PcdAmdHardwarePrefetchMode);
  PrefetchMode.SoftwarePrefetchMode = PcdGet8 (PcdAmdSoftwarePrefetchMode);
  if ((PrefetchMode.HardwarePrefetchMode != HARDWARE_PREFETCHER_AUTO) ||
      (PrefetchMode.SoftwarePrefetchMode != SOFTWARE_PREFETCHES_AUTO)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZpInitializePrefetchMode:\n");
    IDS_HDT_CONSOLE (CPU_TRACE, "    HardwarePrefetchMode - %d\n", PrefetchMode.HardwarePrefetchMode);
    IDS_HDT_CONSOLE (CPU_TRACE, "    SoftwarePrefetchMode - %d\n", PrefetchMode.SoftwarePrefetchMode);

    Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    ASSERT (!EFI_ERROR (Status));
    if (EFI_ERROR (Status)) {
      return AGESA_ERROR;
    }
    MpServices->StartupAllAPs (
        MpServices,
        CcxZpPrefetchModeAps,
        FALSE,
        NULL,
        0,
        (VOID *) &PrefetchMode,
        NULL
    );
    CcxZpPrefetchModeAps (&PrefetchMode);
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZpPrefetchModeAps
 *
 *  Description:
 *    This funtion provides for performance tuning to optimize for specific
 *    workloads. For general performance use the recommended settings.
 *
 *  Parameters:
 *    @param[in]  PrefetchMode              Prefetch mode
 *
 *
 */
VOID
CcxZpPrefetchModeAps (
  IN       CCX_PREFETCH_MODE                *PrefetchMode
  )
{
  ASSERT (PrefetchMode->HardwarePrefetchMode < MAX_HARDWARE_PREFETCH_MODE);

  switch (PrefetchMode->HardwarePrefetchMode) {
  case DISABLE_HARDWARE_PREFETCH:
    // DC_CFG (MSR_C001_1022)
    //  [13] = 1
    //  [15] = 1
    AsmMsrOr64 (MSR_DC_CFG, (BIT13 | BIT15));
    // CU_CFG3 (MSR_C001_102B)
    //  [3]  = 1
    //  [16] = 1
    //  [17] = 1
    //  [18] = 1
    if (CcxIsComputeUnitPrimary (NULL)) {
      AsmMsrOr64 (MSR_CU_CFG3, (BIT3 | BIT16 | BIT17 | BIT18));
    }
    break;
  case DISABLE_L2_STRIDE_PREFETCHER:
    // For DISABLE_L2_STRIDE_PREFETCHER, also implement the following :
    // DISABLE_L1_PREFETCHER
    // DISABLE_HW_PREFETCHER_TRAINING_ON_SOFTWARE_PREFETCHES
    // Hence, no break to allow code to flow through.
    // CU_CFG3 (MSR_C001_102B)
    //  [1] = 0
    if (CcxIsComputeUnitPrimary (NULL)) {
      AsmMsrAnd64 (MSR_CU_CFG3, ~BIT1);
    }
  case DISABLE_L1_PREFETCHER:
    // For this setting, also implement DISABLE_HW_PREFETCHER_TRAINING_ON_SOFTWARE_PREFETCHES.
    // Hence, no break to allow code to flow through.
    // CU_CFG3 (MSR_C001_102B)
    //  [3] = 1
    if (CcxIsComputeUnitPrimary (NULL)) {
      AsmMsrOr64 (MSR_CU_CFG3, BIT3);
    }
  case DISABLE_HW_PREFETCHER_TRAINING_ON_SOFTWARE_PREFETCHES:
    // DC_CFG (MSR_C001_1022)
    //  [15] = 1
    AsmMsrOr64 (MSR_DC_CFG, BIT15);
    break;
  default:
    break;
  }
  // DISABLE_SOFTWARE_PREFETCHES
  if (PrefetchMode->SoftwarePrefetchMode == DISABLE_SOFTWARE_PREFETCHES) {
    // MSR_DE_CFG (MSR_C001_1029)
    //  [7:2] = 0x3F
    if (CcxIsComputeUnitPrimary (NULL)) {
      AsmMsrOr64 (MSR_DE_CFG, 0xFC);
    }
  }
}


