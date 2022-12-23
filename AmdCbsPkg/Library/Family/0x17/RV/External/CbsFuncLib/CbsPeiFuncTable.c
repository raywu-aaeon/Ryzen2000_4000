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

#include "CbsIDSCommonPei.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(IdsPeiFunTable,_Common)[];

#ifdef AMD_CBS_ZEN_RV
#include "CBSZenFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(ZenPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_DF_RV
#include "CBSDfFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(DfPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_UMC_RV
#include "CBSUmcFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(UmcPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_NBIO_RV
#include "CBSNbioFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(NbioPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_FCH_RV
#include "CBSFchFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(FchPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_PROMONTORY_RV
#include "CBSPromontoryFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(PromontoryPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_SMU_RV
#include "CBSSmuFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(SmuPeiFunTable,_RV)[];
#endif
#ifdef AMD_CBS_SOC_RV
#include "CBSSocFunPei_RV.h"
extern PEI_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(SocPeiFunTable,_RV)[];
#endif

PEI_CBS_COMPONENT_STRUCT CbsCommonFuncTable[] =
{
  {0xFFFFFFFF,    AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(IdsPeiFunTable,_Common) },

#ifdef AMD_CBS_ZEN_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(ZenPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(ZenPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(ZenPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_DF_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(DfPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(DfPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(DfPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_UMC_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(UmcPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(UmcPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(UmcPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_NBIO_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(NbioPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(NbioPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(NbioPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_FCH_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(FchPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(FchPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(FchPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_PROMONTORY_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(PromontoryPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(PromontoryPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(PromontoryPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_SMU_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SmuPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SmuPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SmuPeiFunTable,_RV) },
#endif
#ifdef AMD_CBS_SOC_RV
  {F17_RV_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SocPeiFunTable,_RV) },
  {F17_RV2_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SocPeiFunTable,_RV) },
  {F17_PIC_RAW_ID, AMD_RESERVE_ALL, (PEI_CBS_FUNCTION_STRUCT*) CBS_FUNCTABLE_DECLARE(SocPeiFunTable,_RV) },
#endif

  //
  // end of table.
  //
  {0, 0, NULL}
};

