/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU prefetch functions.
 *
 * This funtion provides for performance tuning to optimize for specific
 * workloads. For general performance use the recommended settings.
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx
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
#ifndef _CCX_ZEN_ZP_PREFETCH_DXE_H_
#define _CCX_ZEN_ZP_PREFETCH_DXE_H_

#pragma pack (push, 1)

///  The possible hardware prefetch mode settings.
typedef enum  {
  HARDWARE_PREFETCHER_AUTO,                     ///< Use the recommended setting for the processor. In most cases, the recommended setting is enabled.
  DISABLE_HW_PREFETCHER_TRAINING_ON_SOFTWARE_PREFETCHES,  ///< Use the recommended setting for the hardware prefetcher, but disable training on software prefetches.
  DISABLE_L1_PREFETCHER,                        ///< Use the recommended settings for the hardware prefetcher, but disable L1 prefetching and above.
  DISABLE_L2_STRIDE_PREFETCHER,                 ///< Use the recommended settings for the hardware prefetcher, but disable the L2 stride prefetcher and above
  DISABLE_HARDWARE_PREFETCH,                    ///< Disable hardware prefetching.
  MAX_HARDWARE_PREFETCH_MODE                    ///< Not a hardware prefetch mode, use for limit checking.
} HARDWARE_PREFETCH_MODE;

///  The possible software prefetch mode settings.
typedef enum  {
  SOFTWARE_PREFETCHES_AUTO,                     ///< Use the recommended setting for the processor. In most cases, the recommended setting is enabled.
  DISABLE_SOFTWARE_PREFETCHES,                  ///< Disable software prefetches (convert software prefetch instructions to NOP).
  MAX_SOFTWARE_PREFETCH_MODE                    ///< Not a software prefetch mode, use for limit checking.
} SOFTWARE_PREFETCH_MODE;

/// Advanced performance tunings, prefetchers.
/// These settings provide for performance tuning to optimize for specific workloads.
typedef struct {
  IN HARDWARE_PREFETCH_MODE  HardwarePrefetchMode; ///< This value provides for advanced performance tuning by controlling the hardware prefetcher setting.
  IN SOFTWARE_PREFETCH_MODE  SoftwarePrefetchMode; ///< This value provides for advanced performance tuning by controlling the software prefetch instructions.
} CCX_PREFETCH_MODE;

AGESA_STATUS
CcxZenZpInitializePrefetchMode (
  IN       AMD_CONFIG_PARAMS                *StdHeader
  );

#pragma pack (pop)
#endif // _CCX_ZEN_ZP_PREFETCH_DXE_H_

