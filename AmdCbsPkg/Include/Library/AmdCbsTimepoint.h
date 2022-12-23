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

#ifndef _CBS_TIMEPOINT_H_
#define _CBS_TIMEPOINT_H_

typedef enum {
    // P E I    P H A S E
    CBS_INITRESET_BEFORE = 1,
    CBS_INITRESET_AFTER,
    CBS_INITEARLY_BEFORE,
    CBS_INITEARLY_AFTER,
    CBS_INITPOST_BEFORE,
    CBS_INITPOST_AFTER,
    CBS_S3LATERESTORE_BEFORE,
    CBS_S3LATERESTORE_AFTER,
    GNB_CALLOUT_PCIE_PLATFORM_CONFIG,
    GNB_CALLOUT_PCIE_PHY_CONFIG,
    GNB_CALLOUT_PCIE_EARLY_PORT_CONFIG,
    GNB_CALLOUT_GNB_PACKAGE_POWER_CONFIG,
    CBS_FCH_PEI_CALLOUT,
    GNB_CALLOUT_GNB_BEFORE_EARLY_INIT,
    GNB_CALLOUT_SMUBIOSTABLE_OVERRIDE,
    CBS_AGESA_GET_IDS_INIT_DATA,
    GNB_CALLOUT_BUILDOPTIONS_OVERRIDE,    
    GNB_CALLOUT_SMUFEATURES_MASK_OVERRIDE,

    // D X E    P H A S E
    CBS_INITENV_BEFORE,
    CBS_INITENV_AFTER,
    CBS_INITMID_BEFORE,
    CBS_INITMID_AFTER,
    CBS_INITLATE_BEFORE,
    CBS_INITLATE_AFTER,
    GNB_CALLOUT_PPFUSE_OVERRIDE,
    GNB_CALLOUT_INTEGRATED_TABLE,
    GNB_CALLOUT_NB_POWER_GATE,
    GNB_CALLOUT_PCIE_POWER_GATE,
    GNB_CALLOUT_GMM_REGISTER_OVERRIDE,
    GNB_CALLOUT_GNB_PCIE_AER_CONFIG,
    CBS_FCH_DXE_CALLOUT,
    CBS_SMU_PORT80_LOGGING_BUFFER,
    GNB_CALLOUT_BEFORE_TXPRESET_LOADING
} CBS_TIMEPOINT;

#endif // _CBS_TIMEPOINT_H_

