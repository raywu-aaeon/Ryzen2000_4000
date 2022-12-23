/* $NoKeywords:$ */
/**
 * @file
 *
 * Gnb fuse table
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 330378 $   @e \$Date: 2015-11-05 14:22:53 +0800 (Thu, 05 Nov 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbGfxFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbFuseTable.h"
#include  "GnbFuseTableCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbHandleLib.h"
#include  "OptionGnb.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GNBFUSETABLECZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_BUILD_OPTIONS GnbBuildOptions;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */



/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
GnbFuseTableDebugDumpCZ (
  IN       PP_FUSE_ARRAY_V2    *PpFuseArray,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );



PP_FUSE_ARRAY_V2  DefaultPpFuseArrayCZ = {
    0,                              // PP table revision
    {0x40, 0,  0,  0, 0, 0, 0, 0},           // VCLK DID - entended to 8
    {0x40, 0,  0,  0, 0, 0, 0, 0},  // DCLK DID - entended to 8
    8,                              // Thermal SCLK
    {0,    0,  0,  0,  0,  0},      // Vclk/Dclk selector
    {0x40, 0x40, 0x40, 0, 0, 0, 0, 0},       // Lclk DID - entended to 8
    {0,    0,  0,  0,  0, 0, 0, 0}, // Displclk DID - entended to 8
    3,                              // Pcie Gen 2 VID
    0x10,                           // Main PLL id for 3200 VCO
    0,                              // WRCK SMU clock Divisor
    0,                              // GPU boost cap
    0,                              // Boost margin
    0,                              // Throttle margin
    TRUE,                           // Support VCE in PP table
    {0x1, 0x2, 0x4, 0x0, 0x0, 0, 0, 0},      // VCE Flags - entended to 8
    0,                              // MCLK for VCE 0-3
    0,                              // MCLK for VCE 4
    0,                              // MCLK for VCE 5
    0,                              // MCLK for VCE 6
    0,                              // MCLK for VCE 7
    {0, 0, 0, 0, 0, 0, 0, 0},                // SCLK selector for VCE
    {0x40, 0x40, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0},    // Eclk DID - entended to 8
    0,                              // HTC Enabled
    0,                              // HTC Temperature Limit
    0,                              // HTC Hysteresis Limit
    0,                              // GCK_PLL_FUSES
    { 1, 1, 1, 1},                  // DRAM Configuration Low [per DCT]
    { 0, 0, 0, 0},                  // DRAM Configuration High [per DCT]
    { 0, 0, 0, 0},                  // DRAM Controller Miscellaneous 2 [per DCT]- removed on CZ
    { 0, 0, 0, 0},                  // Memory PState Control and Status [per DCT]
    { 0, 0, 0, 0},                  // NB PState Enable
    { 0, 0, 0, 0},                  // NB VID [6:0]
    { 0, 0, 0, 0},                  // NB VID [7]
    { 0, 0, 0, 0},                  // Memory P State
    { 0, 0, 0, 0},                  // NB FID
    { 1, 1, 1, 1},                  // NB DID
    { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24}, // VddNbVid - entended to 8
    { 0x17, 0x18, 0x20, 0x22, 0x24, 0x24, 0x24, 0x24}, //SclkDid - entended to 8
    { 0x17, 0x18, 0x20, 0x22, 0x24}, //SamuclkDid
    { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7},    // VddNbVidOffset - entended to 8
    0,                              // NumBoostStates
    0x1E,                           // PowerplayPerf
    0x1,                            // PowerplayPerf5
    0x1,                            // PowerplayPerf6
    0x1,                            // PowerplayPerf7
    0x3,                            // PowerplayPS
    0,                              // PowerplayPS5
    0,                              // PowerplayPS6
    0,                              // PowerplayPS7
    { 0x17, 0x18, 0x20, 0x22, 0x24, 0x24, 0x24, 0x24}, //AcpclkDid - entended to 8
    4,                                //PcieGen3Vid
    { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24}, //GfxVid - new added for cz
    { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7},    // GfxVidOffset - new added for cz
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014004_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014004_GnbVid0_OFFSET,
    D0F0xBC_xC0014004_GnbVid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[0])
  },
  {
    D0F0xBC_xC0014004_GnbVid1_OFFSET,
    D0F0xBC_xC0014004_GnbVid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014007_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014007_GnbVid2_OFFSET,
    D0F0xBC_xC0014007_GnbVid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014008_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014008_GnbVid3_OFFSET,
    D0F0xBC_xC0014008_GnbVid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[3])
  },
  {
    D0F0xBC_xC0014008_GnbVid4_OFFSET,
    D0F0xBC_xC0014008_GnbVid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014104_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014104_GfxVid0_OFFSET,
    D0F0xBC_xC0014104_GfxVid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[0])
  },
  {
    D0F0xBC_xC0014104_GfxVid1_OFFSET,
    D0F0xBC_xC0014104_GfxVid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[1])
  },
  {
    D0F0xBC_xC0014104_GfxVid2_OFFSET,
    D0F0xBC_xC0014104_GfxVid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014107_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014107_GfxVid3_OFFSET,
    D0F0xBC_xC0014107_GfxVid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0014108_TABLE_CZ [] = {
  {
    D0F0xBC_xC0014108_GfxVid4_OFFSET,
    D0F0xBC_xC0014108_GfxVid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160C4_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160C4_GnbVid5_OFFSET,
    D0F0xBC_xC00160C4_GnbVid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[5])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160C7_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160C7_GnbVid6_OFFSET,
    D0F0xBC_xC00160C7_GnbVid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160C8_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160C8_GnbVid7_OFFSET,
    D0F0xBC_xC00160C8_GnbVid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVid[7])
  },
  {
    D0F0xBC_xC00160C8_GnbVidOffset5_OFFSET,
    D0F0xBC_xC00160C8_GnbVidOffset5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[5])
  },
  {
    D0F0xBC_xC00160C8_GnbVidOffset6_OFFSET,
    D0F0xBC_xC00160C8_GnbVidOffset6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160CB_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160CB_GnbVidOffset7_OFFSET,
    D0F0xBC_xC00160CB_GnbVidOffset7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[7])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160CC_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160CC_AClkDid5_OFFSET,
    D0F0xBC_xC00160CC_AClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[5])
  },
  {
    D0F0xBC_xC00160CC_AClkDid6_OFFSET,
    D0F0xBC_xC00160CC_AClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[6])
  },
  {
    D0F0xBC_xC00160CC_AClkDid7_OFFSET,
    D0F0xBC_xC00160CC_AClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[7])
  },
  {
    D0F0xBC_xC00160CC_DClkDid5_OFFSET,
    D0F0xBC_xC00160CC_DClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[5])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160CF_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160CF_DClkDid6_OFFSET,
    D0F0xBC_xC00160CF_DClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160D0_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160D0_DClkDid7_OFFSET,
    D0F0xBC_xC00160D0_DClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[7])
  },
  {
    D0F0xBC_xC00160D0_DispClkDid5_OFFSET,
    D0F0xBC_xC00160D0_DispClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[5])
  },
  {
    D0F0xBC_xC00160D0_DispClkDid6_OFFSET,
    D0F0xBC_xC00160D0_DispClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160D3_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160D3_DispClkDid7_OFFSET,
    D0F0xBC_xC00160D3_DispClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[7])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160D4_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160D4_EClkDid5_OFFSET,
    D0F0xBC_xC00160D4_EClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[5])
  },
  {
    D0F0xBC_xC00160D4_EClkDid6_OFFSET,
    D0F0xBC_xC00160D4_EClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[6])
  },
  {
    D0F0xBC_xC00160D4_EClkDid7_OFFSET,
    D0F0xBC_xC00160D4_EClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[7])
  },
  {
    D0F0xBC_xC00160D4_LClkDpmDid5_OFFSET,
    D0F0xBC_xC00160D4_LClkDpmDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[5])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160D7_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160D7_LClkDpmDid6_OFFSET,
    D0F0xBC_xC00160D7_LClkDpmDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160D8_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160D8_LClkDpmDid7_OFFSET,
    D0F0xBC_xC00160D8_LClkDpmDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[7])
  },
  {
    D0F0xBC_xC00160D8_SClkDid5_OFFSET,
    D0F0xBC_xC00160D8_SClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[5])
  },
  {
    D0F0xBC_xC00160D8_SClkDid6_OFFSET,
    D0F0xBC_xC00160D8_SClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[6])
  },
  {
    D0F0xBC_xC00160D8_SClkDid7_OFFSET,
    D0F0xBC_xC00160D8_SClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[7])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160DC_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160DC_VClkDid5_OFFSET,
    D0F0xBC_xC00160DC_VClkDid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[5])
  },
  {
    D0F0xBC_xC00160DC_VClkDid6_OFFSET,
    D0F0xBC_xC00160DC_VClkDid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[6])
  },
  {
    D0F0xBC_xC00160DC_VClkDid7_OFFSET,
    D0F0xBC_xC00160DC_VClkDid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[7])
  },
  {
    D0F0xBC_xC00160DC_GfxVid5_OFFSET,
    D0F0xBC_xC00160DC_GfxVid5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[5])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160DF_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160DF_GfxVid6_OFFSET,
    D0F0xBC_xC00160DF_GfxVid6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160E0_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160E0_GfxVid7_OFFSET,
    D0F0xBC_xC00160E0_GfxVid7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVid[7])
  },
  {
    D0F0xBC_xC00160E0_GfxVidOffset5_OFFSET,
    D0F0xBC_xC00160E0_GfxVidOffset5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[5])
  },
  {
    D0F0xBC_xC00160E0_GfxVidOffset6_OFFSET,
    D0F0xBC_xC00160E0_GfxVidOffset6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160E3_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160E3_GfxVidOffset7_OFFSET,
    D0F0xBC_xC00160E3_GfxVidOffset7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[7])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160F4_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160F4_PowerplayPerfFlag5_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPerfFlag5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PerfFlag5)
  },
  {
    D0F0xBC_xC00160F4_PowerplayPerfFlag6_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPerfFlag6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PerfFlag6)
  },
  {
    D0F0xBC_xC00160F4_PowerplayPerfFlag7_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPerfFlag7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PerfFlag7)
  },
  {
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag5_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PowerSavingsFlag5)
  },
  {
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag6_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PowerSavingsFlag6)
  },
  {
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag7_OFFSET,
    D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PowerSavingsFlag7)
  },
  {
    D0F0xBC_xC00160F4_VCEFlag4_OFFSET,
    D0F0xBC_xC00160F4_VCEFlag4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[4])
  },
  {
    D0F0xBC_xC00160F4_VCEFlag5_OFFSET,
    D0F0xBC_xC00160F4_VCEFlag5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[5])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160F7_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160F7_VCEFlag6_OFFSET,
    D0F0xBC_xC00160F7_VCEFlag6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC00160F8_TABLE_CZ [] = {
  {
    D0F0xBC_xC00160F8_VCEFlag7_OFFSET,
    D0F0xBC_xC00160F8_VCEFlag7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[7])
  },
  {
    D0F0xBC_xC00160F8_VCEMclk4_OFFSET,
    D0F0xBC_xC00160F8_VCEMclk4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceMclk4)
  },
  {
    D0F0xBC_xC00160F8_VCEMclk5_OFFSET,
    D0F0xBC_xC00160F8_VCEMclk5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceMclk5)
  },
  {
    D0F0xBC_xC00160F8_VCEMclk6_OFFSET,
    D0F0xBC_xC00160F8_VCEMclk6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceMclk6)
  },
  {
    D0F0xBC_xC00160F8_VCEMclk7_OFFSET,
    D0F0xBC_xC00160F8_VCEMclk7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceMclk7)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001704C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001704C_NumBoostStates_OFFSET,
    D0F0xBC_xC001704C_NumBoostStates_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NumBoostStates)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001706C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001706C_PowerplayTableRev_OFFSET,
    D0F0xBC_xC001706C_PowerplayTableRev_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PPlayTableRev)
  },
  {
    D0F0xBC_xC001706C_PcieGen2Vid_OFFSET,
    D0F0xBC_xC001706C_PcieGen2Vid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PcieGen2Vid)
  },
  {
    D0F0xBC_xC001706C_PcieGen3Vid_OFFSET,
    D0F0xBC_xC001706C_PcieGen3Vid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PcieGen3Vid)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001706F_TABLE_CZ [] = {
  {
    D0F0xBC_xC001706F_SClkDid0_OFFSET,
    D0F0xBC_xC001706F_SClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017070_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017070_SClkDid1_OFFSET,
    D0F0xBC_xC0017070_SClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[1])
  },
  {
    D0F0xBC_xC0017070_SClkDid2_OFFSET,
    D0F0xBC_xC0017070_SClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[2])
  },
  {
    D0F0xBC_xC0017070_SClkDid3_OFFSET,
    D0F0xBC_xC0017070_SClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[3])
  },
  {
    D0F0xBC_xC0017070_SClkDid4_OFFSET,
    D0F0xBC_xC0017070_SClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, SclkDid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017074_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017074_DispClkDid0_OFFSET,
    D0F0xBC_xC0017074_DispClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[0])
  },
  {
    D0F0xBC_xC0017074_DispClkDid1_OFFSET,
    D0F0xBC_xC0017074_DispClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[1])
  },
  {
    D0F0xBC_xC0017074_DispClkDid2_OFFSET,
    D0F0xBC_xC0017074_DispClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[2])
  },
  {
    D0F0xBC_xC0017074_DispClkDid3_OFFSET,
    D0F0xBC_xC0017074_DispClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017077_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017077_DispClkDid4_OFFSET,
    D0F0xBC_xC0017077_DispClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DispClkDid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017078_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017078_LClkDpmDid0_OFFSET,
    D0F0xBC_xC0017078_LClkDpmDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[0])
  },
  {
    D0F0xBC_xC0017078_LClkDpmDid1_OFFSET,
    D0F0xBC_xC0017078_LClkDpmDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[1])
  },
  {
    D0F0xBC_xC0017078_LClkDpmDid2_OFFSET,
    D0F0xBC_xC0017078_LClkDpmDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[2])
  },
  {
    D0F0xBC_xC0017078_LClkDpmDid3_OFFSET,
    D0F0xBC_xC0017078_LClkDpmDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001707B_TABLE_CZ [] = {
  {
    D0F0xBC_xC001707B_LClkDpmDid4_OFFSET,
    D0F0xBC_xC001707B_LClkDpmDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, LclkDid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001707C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001707C_DClkDid0_OFFSET,
    D0F0xBC_xC001707C_DClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[0])
  },
  {
    D0F0xBC_xC001707C_DClkDid1_OFFSET,
    D0F0xBC_xC001707C_DClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[1])
  },
  {
    D0F0xBC_xC001707C_DClkDid2_OFFSET,
    D0F0xBC_xC001707C_DClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001707F_TABLE_CZ [] = {
  {
    D0F0xBC_xC001707F_DClkDid3_OFFSET,
    D0F0xBC_xC001707F_DClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017080_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017080_DClkDid4_OFFSET,
    D0F0xBC_xC0017080_DClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DclkDid[4])
  },
  {
    D0F0xBC_xC0017080_VClkDid0_OFFSET,
    D0F0xBC_xC0017080_VClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[0])
  },
  {
    D0F0xBC_xC0017080_VClkDid1_OFFSET,
    D0F0xBC_xC0017080_VClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[1])
  },
  {
    D0F0xBC_xC0017080_VClkDid2_OFFSET,
    D0F0xBC_xC0017080_VClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017083_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017083_VClkDid3_OFFSET,
    D0F0xBC_xC0017083_VClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017084_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017084_VClkDid4_OFFSET,
    D0F0xBC_xC0017084_VClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VclkDid[4])
  },
  {
    D0F0xBC_xC0017084_EClkDid0_OFFSET,
    D0F0xBC_xC0017084_EClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[0])
  },
  {
    D0F0xBC_xC0017084_EClkDid1_OFFSET,
    D0F0xBC_xC0017084_EClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017087_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017087_EClkDid2_OFFSET,
    D0F0xBC_xC0017087_EClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017088_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017088_EClkDid3_OFFSET,
    D0F0xBC_xC0017088_EClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[3])
  },
  {
    D0F0xBC_xC0017088_EClkDid4_OFFSET,
    D0F0xBC_xC0017088_EClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, EclkDid[4])
  },
  {
    D0F0xBC_xC0017088_PowerplayPerfFlag_OFFSET,
    D0F0xBC_xC0017088_PowerplayPerfFlag_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PerfFlag)
  },
  {
    D0F0xBC_xC0017088_PowerplayPowerSavingsFlag_OFFSET,
    D0F0xBC_xC0017088_PowerplayPowerSavingsFlag_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, PowerSavingsFlag)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017107_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017107_AClkDid0_OFFSET,
    D0F0xBC_xC0017107_AClkDid0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017108_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017108_AClkDid1_OFFSET,
    D0F0xBC_xC0017108_AClkDid1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[1])
  },
  {
    D0F0xBC_xC0017108_AClkDid2_OFFSET,
    D0F0xBC_xC0017108_AClkDid2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[2])
  },
  {
    D0F0xBC_xC0017108_AClkDid3_OFFSET,
    D0F0xBC_xC0017108_AClkDid3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[3])
  },
  {
    D0F0xBC_xC0017108_AClkDid4_OFFSET,
    D0F0xBC_xC0017108_AClkDid4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, AcpClkDid[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001711C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001711C_VCEFlag0_OFFSET,
    D0F0xBC_xC001711C_VCEFlag0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[0])
  },
  {
    D0F0xBC_xC001711C_VCEFlag1_OFFSET,
    D0F0xBC_xC001711C_VCEFlag1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001711F_TABLE_CZ [] = {
  {
    D0F0xBC_xC001711F_VCEFlag2_OFFSET,
    D0F0xBC_xC001711F_VCEFlag2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017120_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017120_VCEFlag3_OFFSET,
    D0F0xBC_xC0017120_VCEFlag3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceFlags[3])
  },
  {
    D0F0xBC_xC0017120_VCEMclk_OFFSET,
    D0F0xBC_xC0017120_VCEMclk_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceMclk)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001712C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001712C_GnbVidOffset0_OFFSET,
    D0F0xBC_xC001712C_GnbVidOffset0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001712F_TABLE_CZ [] = {
  {
    D0F0xBC_xC001712F_GnbVidOffset1_OFFSET,
    D0F0xBC_xC001712F_GnbVidOffset1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017130_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017130_GnbVidOffset2_OFFSET,
    D0F0xBC_xC0017130_GnbVidOffset2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[2])
  },
  {
    D0F0xBC_xC0017130_GnbVidOffset3_OFFSET,
    D0F0xBC_xC0017130_GnbVidOffset3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[3])
  },
  {
    D0F0xBC_xC0017130_GnbVidOffset4_OFFSET,
    D0F0xBC_xC0017130_GnbVidOffset4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VddNbVidOffset[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017134_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017134_GfxVidOffset0_OFFSET,
    D0F0xBC_xC0017134_GfxVidOffset0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[0])
  },
  {
    D0F0xBC_xC0017134_GfxVidOffset1_OFFSET,
    D0F0xBC_xC0017134_GfxVidOffset1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[1])
  },
  {
    D0F0xBC_xC0017134_GfxVidOffset2_OFFSET,
    D0F0xBC_xC0017134_GfxVidOffset2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017137_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017137_GfxVidOffset3_OFFSET,
    D0F0xBC_xC0017137_GfxVidOffset3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[3])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017138_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017138_GfxVidOffset4_OFFSET,
    D0F0xBC_xC0017138_GfxVidOffset4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, GfxVidOffset[4])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017164_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017164_ReqSclkSel0_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel0_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[0])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel1_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel1_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[1])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel2_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel2_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[2])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel3_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel3_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[3])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel4_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel4_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[4])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel5_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel5_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[5])
  },
  {
    D0F0xBC_xC0017164_ReqSclkSel6_OFFSET,
    D0F0xBC_xC0017164_ReqSclkSel6_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[6])
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC0017167_TABLE_CZ [] = {
  {
    D0F0xBC_xC0017167_ReqSclkSel7_OFFSET,
    D0F0xBC_xC0017167_ReqSclkSel7_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, VceReqSclkSel[7])
  }
};

FUSE_TABLE_ENTRY_CZ  FuseRegisterTableCZ [] = {
  {
    D0F0xBC_xC0014004_TYPE,
    D0F0xBC_xC0014004_ADDRESS,
    sizeof (D0F0xBC_xC0014004_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014004_TABLE_CZ
  },
  {
    D0F0xBC_xC0014007_TYPE,
    D0F0xBC_xC0014007_ADDRESS,
    sizeof (D0F0xBC_xC0014007_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014007_TABLE_CZ
  },
  {
    D0F0xBC_xC0014008_TYPE,
    D0F0xBC_xC0014008_ADDRESS,
    sizeof (D0F0xBC_xC0014008_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014008_TABLE_CZ
  },
  {
    D0F0xBC_xC0014104_TYPE,
    D0F0xBC_xC0014104_ADDRESS,
    sizeof (D0F0xBC_xC0014104_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014104_TABLE_CZ
  },
  {
    D0F0xBC_xC0014107_TYPE,
    D0F0xBC_xC0014107_ADDRESS,
    sizeof (D0F0xBC_xC0014107_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014107_TABLE_CZ
  },
  {
    D0F0xBC_xC0014108_TYPE,
    D0F0xBC_xC0014108_ADDRESS,
    sizeof (D0F0xBC_xC0014108_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0014108_TABLE_CZ
  },
  {
    D0F0xBC_xC00160C4_TYPE,
    D0F0xBC_xC00160C4_ADDRESS,
    sizeof (D0F0xBC_xC00160C4_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160C4_TABLE_CZ
  },
  {
    D0F0xBC_xC00160C7_TYPE,
    D0F0xBC_xC00160C7_ADDRESS,
    sizeof (D0F0xBC_xC00160C7_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160C7_TABLE_CZ
  },
  {
    D0F0xBC_xC00160C8_TYPE,
    D0F0xBC_xC00160C8_ADDRESS,
    sizeof (D0F0xBC_xC00160C8_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160C8_TABLE_CZ
  },
  {
    D0F0xBC_xC00160CB_TYPE,
    D0F0xBC_xC00160CB_ADDRESS,
    sizeof (D0F0xBC_xC00160CB_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160CB_TABLE_CZ
  },
  {
    D0F0xBC_xC00160CC_TYPE,
    D0F0xBC_xC00160CC_ADDRESS,
    sizeof (D0F0xBC_xC00160CC_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160CC_TABLE_CZ
  },
  {
    D0F0xBC_xC00160CF_TYPE,
    D0F0xBC_xC00160CF_ADDRESS,
    sizeof (D0F0xBC_xC00160CF_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160CF_TABLE_CZ
  },
  {
    D0F0xBC_xC00160D0_TYPE,
    D0F0xBC_xC00160D0_ADDRESS,
    sizeof (D0F0xBC_xC00160D0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160D0_TABLE_CZ
  },
  {
    D0F0xBC_xC00160D3_TYPE,
    D0F0xBC_xC00160D3_ADDRESS,
    sizeof (D0F0xBC_xC00160D3_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160D3_TABLE_CZ
  },
  {
    D0F0xBC_xC00160D4_TYPE,
    D0F0xBC_xC00160D4_ADDRESS,
    sizeof (D0F0xBC_xC00160D4_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160D4_TABLE_CZ
  },
  {
    D0F0xBC_xC00160D7_TYPE,
    D0F0xBC_xC00160D7_ADDRESS,
    sizeof (D0F0xBC_xC00160D7_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160D7_TABLE_CZ
  },
  {
    D0F0xBC_xC00160D8_TYPE,
    D0F0xBC_xC00160D8_ADDRESS,
    sizeof (D0F0xBC_xC00160D8_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160D8_TABLE_CZ
  },
  {
    D0F0xBC_xC00160DC_TYPE,
    D0F0xBC_xC00160DC_ADDRESS,
    sizeof (D0F0xBC_xC00160DC_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160DC_TABLE_CZ
  },
  {
    D0F0xBC_xC00160DF_TYPE,
    D0F0xBC_xC00160DF_ADDRESS,
    sizeof (D0F0xBC_xC00160DF_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160DF_TABLE_CZ
  },
  {
    D0F0xBC_xC00160E0_TYPE,
    D0F0xBC_xC00160E0_ADDRESS,
    sizeof (D0F0xBC_xC00160E0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160E0_TABLE_CZ
  },
  {
    D0F0xBC_xC00160E3_TYPE,
    D0F0xBC_xC00160E3_ADDRESS,
    sizeof (D0F0xBC_xC00160E3_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160E3_TABLE_CZ
  },
  {
    D0F0xBC_xC00160F4_TYPE,
    D0F0xBC_xC00160F4_ADDRESS,
    sizeof (D0F0xBC_xC00160F4_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160F4_TABLE_CZ
  },
  {
    D0F0xBC_xC00160F7_TYPE,
    D0F0xBC_xC00160F7_ADDRESS,
    sizeof (D0F0xBC_xC00160F7_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160F7_TABLE_CZ
  },
  {
    D0F0xBC_xC00160F8_TYPE,
    D0F0xBC_xC00160F8_ADDRESS,
    sizeof (D0F0xBC_xC00160F8_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC00160F8_TABLE_CZ
  },
  {
    D0F0xBC_xC001704C_TYPE,
    D0F0xBC_xC001704C_ADDRESS,
    sizeof (D0F0xBC_xC001704C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001704C_TABLE_CZ
  },
  {
    D0F0xBC_xC001706C_TYPE,
    D0F0xBC_xC001706C_ADDRESS,
    sizeof (D0F0xBC_xC001706C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001706C_TABLE_CZ
  },
  {
    D0F0xBC_xC001706F_TYPE,
    D0F0xBC_xC001706F_ADDRESS,
    sizeof (D0F0xBC_xC001706F_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001706F_TABLE_CZ
  },
  {
    D0F0xBC_xC0017070_TYPE,
    D0F0xBC_xC0017070_ADDRESS,
    sizeof (D0F0xBC_xC0017070_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017070_TABLE_CZ
  },
  {
    D0F0xBC_xC0017074_TYPE,
    D0F0xBC_xC0017074_ADDRESS,
    sizeof (D0F0xBC_xC0017074_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017074_TABLE_CZ
  },
  {
    D0F0xBC_xC0017077_TYPE,
    D0F0xBC_xC0017077_ADDRESS,
    sizeof (D0F0xBC_xC0017077_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017077_TABLE_CZ
  },
  {
    D0F0xBC_xC0017078_TYPE,
    D0F0xBC_xC0017078_ADDRESS,
    sizeof (D0F0xBC_xC0017078_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017078_TABLE_CZ
  },
  {
    D0F0xBC_xC001707B_TYPE,
    D0F0xBC_xC001707B_ADDRESS,
    sizeof (D0F0xBC_xC001707B_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001707B_TABLE_CZ
  },
  {
    D0F0xBC_xC001707C_TYPE,
    D0F0xBC_xC001707C_ADDRESS,
    sizeof (D0F0xBC_xC001707C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001707C_TABLE_CZ
  },
  {
    D0F0xBC_xC001707F_TYPE,
    D0F0xBC_xC001707F_ADDRESS,
    sizeof (D0F0xBC_xC001707F_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001707F_TABLE_CZ
  },
  {
    D0F0xBC_xC0017080_TYPE,
    D0F0xBC_xC0017080_ADDRESS,
    sizeof (D0F0xBC_xC0017080_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017080_TABLE_CZ
  },
  {
    D0F0xBC_xC0017083_TYPE,
    D0F0xBC_xC0017083_ADDRESS,
    sizeof (D0F0xBC_xC0017083_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017083_TABLE_CZ
  },
  {
    D0F0xBC_xC0017084_TYPE,
    D0F0xBC_xC0017084_ADDRESS,
    sizeof (D0F0xBC_xC0017084_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017084_TABLE_CZ
  },
  {
    D0F0xBC_xC0017087_TYPE,
    D0F0xBC_xC0017087_ADDRESS,
    sizeof (D0F0xBC_xC0017087_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017087_TABLE_CZ
  },
  {
    D0F0xBC_xC0017088_TYPE,
    D0F0xBC_xC0017088_ADDRESS,
    sizeof (D0F0xBC_xC0017088_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017088_TABLE_CZ
  },
  {
    D0F0xBC_xC0017107_TYPE,
    D0F0xBC_xC0017107_ADDRESS,
    sizeof (D0F0xBC_xC0017107_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017107_TABLE_CZ
  },
  {
    D0F0xBC_xC0017108_TYPE,
    D0F0xBC_xC0017108_ADDRESS,
    sizeof (D0F0xBC_xC0017108_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017108_TABLE_CZ
  },
  {
    D0F0xBC_xC001711C_TYPE,
    D0F0xBC_xC001711C_ADDRESS,
    sizeof (D0F0xBC_xC001711C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001711C_TABLE_CZ
  },
  {
    D0F0xBC_xC001711F_TYPE,
    D0F0xBC_xC001711F_ADDRESS,
    sizeof (D0F0xBC_xC001711F_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001711F_TABLE_CZ
  },
  {
    D0F0xBC_xC0017120_TYPE,
    D0F0xBC_xC0017120_ADDRESS,
    sizeof (D0F0xBC_xC0017120_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017120_TABLE_CZ
  },
  {
    D0F0xBC_xC001712C_TYPE,
    D0F0xBC_xC001712C_ADDRESS,
    sizeof (D0F0xBC_xC001712C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001712C_TABLE_CZ
  },
  {
    D0F0xBC_xC001712F_TYPE,
    D0F0xBC_xC001712F_ADDRESS,
    sizeof (D0F0xBC_xC001712F_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001712F_TABLE_CZ
  },
  {
    D0F0xBC_xC0017130_TYPE,
    D0F0xBC_xC0017130_ADDRESS,
    sizeof (D0F0xBC_xC0017130_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017130_TABLE_CZ
  },
  {
    D0F0xBC_xC0017134_TYPE,
    D0F0xBC_xC0017134_ADDRESS,
    sizeof (D0F0xBC_xC0017134_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017134_TABLE_CZ
  },
  {
    D0F0xBC_xC0017137_TYPE,
    D0F0xBC_xC0017137_ADDRESS,
    sizeof (D0F0xBC_xC0017137_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017137_TABLE_CZ
  },
  {
    D0F0xBC_xC0017138_TYPE,
    D0F0xBC_xC0017138_ADDRESS,
    sizeof (D0F0xBC_xC0017138_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017138_TABLE_CZ
  },
  {
    D0F0xBC_xC0017164_TYPE,
    D0F0xBC_xC0017164_ADDRESS,
    sizeof (D0F0xBC_xC0017164_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017164_TABLE_CZ
  },
  {
    D0F0xBC_xC0017167_TYPE,
    D0F0xBC_xC0017167_ADDRESS,
    sizeof (D0F0xBC_xC0017167_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC0017167_TABLE_CZ
  }
};

FUSE_REGISTER_ENTRY_CZ D18F3x64_TABLE_CZ [] = {
  {
    D18F3x64_HTC_EN_OFFSET,
    D18F3x64_HTC_EN_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, HtcEn)
  },
  {
    D18F3x64_HTC_TMP_LMT_OFFSET,
    D18F3x64_HTC_TMP_LMT_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, HtcTmpLmt)
  },
  {
    D18F3x64_HTC_HYST_LMT_OFFSET,
    D18F3x64_HTC_HYST_LMT_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, HtcHystLmt)
  }
};

FUSE_REGISTER_ENTRY_CZ D0F0xBC_xC001400C_TABLE_CZ [] = {
  {
    D0F0xBC_xC001400C_MainPllOpFreqIdStartup_OFFSET,
    D0F0xBC_xC001400C_MainPllOpFreqIdStartup_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MainPllOpFreqIdStartup)
  }
};

FUSE_REGISTER_ENTRY_CZ D18F2x90_dct0_TABLE_CZ [] = {
  {
    D18F2x90_dct0_DisDllShutdownSR_OFFSET,
    D18F2x90_dct0_DisDllShutdownSR_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DisDllShutdownSR[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F2x90_dct1_TABLE_CZ [] = {
  {
    D18F2x90_dct0_DisDllShutdownSR_OFFSET,
    D18F2x90_dct0_DisDllShutdownSR_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, DisDllShutdownSR[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F2x94_dct0_TABLE_CZ [] = {
  {
    D18F2x94_dct0_MemClkFreq_OFFSET,
    D18F2x94_dct0_MemClkFreq_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemClkFreq[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F2x94_dct1_TABLE_CZ [] = {
  {
    D18F2x94_dct0_MemClkFreq_OFFSET,
    D18F2x94_dct0_MemClkFreq_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemClkFreq[1])
  }
};
//
//FUSE_REGISTER_ENTRY_CZ D18F2xA8_dct0_TABLE_CZ [] = {
//  {
//    D18F2xA8_dct0_MemPhyPllPdMode_OFFSET,
//    D18F2xA8_dct0_MemPhyPllPdMode_WIDTH,
//    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPhyPllPdMode[0])
//  }
//};
//
//FUSE_REGISTER_ENTRY_CZ D18F2xA8_dct1_TABLE_CZ [] = {
//  {
//    D18F2xA8_dct0_MemPhyPllPdMode_OFFSET,
//    D18F2xA8_dct0_MemPhyPllPdMode_WIDTH,
//    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPhyPllPdMode[1])
//  }
//};

FUSE_REGISTER_ENTRY_CZ D18F2x2E0_dct0_TABLE_CZ [] = {
  {
    D18F2x2E0_dct0_M1MemClkFreq_OFFSET,
    D18F2x2E0_dct0_M1MemClkFreq_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, M1MemClkFreq[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F2x2E0_dct1_TABLE_CZ [] = {
  {
    D18F2x2E0_dct0_M1MemClkFreq_OFFSET,
    D18F2x2E0_dct0_M1MemClkFreq_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, M1MemClkFreq[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F5x160_TABLE_CZ [] = {
  {
    D18F5x160_NbPstateEn_OFFSET,
    D18F5x160_NbPstateEn_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbPstateEn[0])
  },
  {
    D18F5x160_MemPstate_OFFSET,
    D18F5x160_MemPstate_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPstate[0])
  },
  {
    D18F5x160_NbFid_5_0__OFFSET,
    D18F5x160_NbFid_5_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbFid[0])
  },
  {
    D18F5x160_NbDid_OFFSET,
    D18F5x160_NbDid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbDid[0])
  },
  {
    D18F5x160_NbVid_6_0__OFFSET,
    D18F5x160_NbVid_6_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_6_0[0])
  },
  {
    D18F5x160_NbVid_7__OFFSET,
    D18F5x160_NbVid_7__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_7[0])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F5x164_TABLE_CZ [] = {
  {
    D18F5x164_NbPstateEn_OFFSET,
    D18F5x164_NbPstateEn_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbPstateEn[1])
  },
  {
    D18F5x164_MemPstate_OFFSET,
    D18F5x164_MemPstate_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPstate[1])
  },
  {
    D18F5x164_NbFid_5_0__OFFSET,
    D18F5x164_NbFid_5_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbFid[1])
  },
  {
    D18F5x164_NbDid_OFFSET,
    D18F5x164_NbDid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbDid[1])
  },
  {
    D18F5x164_NbVid_6_0__OFFSET,
    D18F5x164_NbVid_6_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_6_0[1])
  },
  {
    D18F5x164_NbVid_7__OFFSET,
    D18F5x164_NbVid_7__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_7[1])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F5x168_TABLE_CZ [] = {
  {
    D18F5x168_NbPstateEn_OFFSET,
    D18F5x168_NbPstateEn_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbPstateEn[2])
  },
  {
    D18F5x168_MemPstate_OFFSET,
    D18F5x168_MemPstate_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPstate[2])
  },
  {
    D18F5x168_NbFid_5_0__OFFSET,
    D18F5x168_NbFid_5_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbFid[2])
  },
  {
    D18F5x168_NbDid_OFFSET,
    D18F5x168_NbDid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbDid[2])
  },
  {
    D18F5x168_NbVid_6_0__OFFSET,
    D18F5x168_NbVid_6_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_6_0[2])
  },
  {
    D18F5x168_NbVid_7__OFFSET,
    D18F5x168_NbVid_7__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_7[2])
  }
};

FUSE_REGISTER_ENTRY_CZ D18F5x16C_TABLE_CZ [] = {
  {
    D18F5x16C_NbPstateEn_OFFSET,
    D18F5x16C_NbPstateEn_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbPstateEn[3])
  },
  {
    D18F5x16C_MemPstate_OFFSET,
    D18F5x16C_MemPstate_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, MemPstate[3])
  },
  {
    D18F5x16C_NbFid_5_0__OFFSET,
    D18F5x16C_NbFid_5_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbFid[3])
  },
  {
    D18F5x16C_NbDid_OFFSET,
    D18F5x16C_NbDid_WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbDid[3])
  },
  {
    D18F5x16C_NbVid_6_0__OFFSET,
    D18F5x16C_NbVid_6_0__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_6_0[3])
  },
  {
    D18F5x16C_NbVid_7__OFFSET,
    D18F5x16C_NbVid_7__WIDTH,
    (UINT16) offsetof (PP_FUSE_ARRAY_V2, NbVid_7[3])
  }
};

FUSE_TABLE_ENTRY_CZ  PPRegisterTableCZ [] = {
  {
    D18F3x64_TYPE,
    D18F3x64_ADDRESS,
    sizeof (D18F3x64_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F3x64_TABLE_CZ
  },
  {
    D0F0xBC_xC001400C_TYPE,
    D0F0xBC_xC001400C_ADDRESS,
    sizeof (D0F0xBC_xC001400C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D0F0xBC_xC001400C_TABLE_CZ
  },
  {
    D18F2x90_dct0_TYPE,
    D18F2x90_dct0_ADDRESS,
    sizeof (D18F2x90_dct0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x90_dct0_TABLE_CZ
  },
  {
    D18F2x90_dct1_TYPE,
    D18F2x90_dct1_ADDRESS,
    sizeof (D18F2x90_dct1_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x90_dct1_TABLE_CZ
  },
  {
    D18F2x94_dct0_TYPE,
    D18F2x94_dct0_ADDRESS,
    sizeof (D18F2x94_dct0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x94_dct0_TABLE_CZ
  },
  {
    D18F2x94_dct1_TYPE,
    D18F2x94_dct1_ADDRESS,
    sizeof (D18F2x94_dct1_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x94_dct1_TABLE_CZ
  },
//  {
//    D18F2xA8_dct0_TYPE,
//    D18F2xA8_dct0_ADDRESS,
//    sizeof (D18F2xA8_dct0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
//    D18F2xA8_dct0_TABLE_CZ
//  },
//  {
//    D18F2xA8_dct1_TYPE,
//    D18F2xA8_dct1_ADDRESS,
//    sizeof (D18F2xA8_dct1_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
//    D18F2xA8_dct1_TABLE_CZ
//  },
  {
    D18F2x2E0_dct0_TYPE,
    D18F2x2E0_dct0_ADDRESS,
    sizeof (D18F2x2E0_dct0_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x2E0_dct0_TABLE_CZ
  },
  {
    D18F2x2E0_dct1_TYPE,
    D18F2x2E0_dct1_ADDRESS,
    sizeof (D18F2x2E0_dct1_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F2x2E0_dct1_TABLE_CZ
  },
  {
    D18F5x160_TYPE,
    D18F5x160_ADDRESS,
    sizeof (D18F5x160_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F5x160_TABLE_CZ
  },
  {
    D18F5x164_TYPE,
    D18F5x164_ADDRESS,
    sizeof (D18F5x164_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F5x164_TABLE_CZ
  },
  {
    D18F5x168_TYPE,
    D18F5x168_ADDRESS,
    sizeof (D18F5x168_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F5x168_TABLE_CZ
  },
  {
    D18F5x16C_TYPE,
    D18F5x16C_ADDRESS,
    sizeof (D18F5x16C_TABLE_CZ) / sizeof (FUSE_REGISTER_ENTRY_CZ),
    D18F5x16C_TABLE_CZ
  }
};



FUSE_TABLE_CZ  FuseTableCZ = {
  sizeof (FuseRegisterTableCZ) / sizeof (FUSE_TABLE_ENTRY_CZ),
  FuseRegisterTableCZ
};


FUSE_TABLE_CZ  PPTableCZ = {
  sizeof (PPRegisterTableCZ) / sizeof (FUSE_TABLE_ENTRY_CZ),
  PPRegisterTableCZ
};

/*----------------------------------------------------------------------------------------*/
/**
 * Load Fuse Table CZ
 *
 *
 * @param[in]  FuseTable        Pointer to fuse table entries to load
 * @param[out] PpFuseArray      Pointer to save fuse table
 * @param[in]  StdHeader        Pointer to Standard configuration
 * @retval     AGESA_STATUS
 */

VOID
STATIC
NbFuseLoadFuseTableCZ (
  IN       FUSE_TABLE_CZ       *FuseTable,
     OUT   PP_FUSE_ARRAY_V2       *PpFuseArray,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN                     RegisterIndex;
  for (RegisterIndex = 0; RegisterIndex < FuseTable->FuseTableLength; RegisterIndex++ ) {
    UINTN   FieldIndex;
    UINTN   FuseRegisterTableLength;
    UINT32  FuseValue;
    FuseRegisterTableLength = FuseTable->FuseTable[RegisterIndex].FuseRegisterTableLength;

    GnbRegisterReadCZ (
      GnbGetHandle (StdHeader),
      FuseTable->FuseTable[RegisterIndex].RegisterSpaceType,
      FuseTable->FuseTable[RegisterIndex].Register,
      &FuseValue,
      0,
      StdHeader
    );
    for (FieldIndex = 0; FieldIndex < FuseRegisterTableLength;  FieldIndex++) {
      FUSE_REGISTER_ENTRY_CZ   RegisterEntry;
      RegisterEntry = FuseTable->FuseTable[RegisterIndex].FuseRegisterTable[FieldIndex];
      *((UINT8 *) PpFuseArray + RegisterEntry.FuseOffset) = (UINT8) ((FuseValue >> RegisterEntry.FieldOffset) &
                                                            ((1 << RegisterEntry.FieldWidth) - 1));
    }
  }

  // Combine bit definition into VceMclk, PerfFlag, PowerSavingsFlag
  PpFuseArray->VceMclk |= ((UINT8) (PpFuseArray->VceMclk4 << 4)) |
                          ((UINT8) (PpFuseArray->VceMclk5 << 5)) |
                          ((UINT8) (PpFuseArray->VceMclk6 << 6)) |
                          ((UINT8) (PpFuseArray->VceMclk7 << 7));

  PpFuseArray->PerfFlag |= ((UINT8) (PpFuseArray->PerfFlag5 << 5)) |
                           ((UINT8) (PpFuseArray->PerfFlag6 << 6)) |
                           ((UINT8) (PpFuseArray->PerfFlag7 << 7));

  PpFuseArray->PowerSavingsFlag |= ((UINT8) (PpFuseArray->PowerSavingsFlag5 << 5)) |
                                   ((UINT8) (PpFuseArray->PowerSavingsFlag6 << 6)) |
                                   ((UINT8) (PpFuseArray->PowerSavingsFlag7 << 7));

}

/*----------------------------------------------------------------------------------------*/
/**
 * Check OPN for PP Fuse workaround
 *
 *
 * @param[in]  StdHeader          Pointer to Standard configuration
 * @param[in]  OpnPtr             Pointer to OPNs
 * @retval     TRUE               The workaround should be applied
 * @retval     FALSE              The workaround should not be applied
 */

BOOLEAN
CheckOpnCZ (
  IN      AMD_CONFIG_PARAMS       *StdHeader,
  IN      OPN_CHAR_STRUCT         *OpnPtr
  )
{
  UINT32          Value24;
  UINT32          Value28;
  UINT32          Value2C;
  UINT32          Value30;
  OPN_CHAR_STRUCT ReadOpn;
  INT8            OpnCharIndex;
  UINT8           OpnNumIndex;

  // Read OPN from D0F0xBC_xC0016130[9] - D0F0xBC_xC0016124[15]
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), TYPE_D0F0xBC, 0xC0016124, &Value24, 0, StdHeader);
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), TYPE_D0F0xBC, 0xC0016128, &Value28, 0, StdHeader);
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), TYPE_D0F0xBC, 0xC001612C, &Value2C, 0, StdHeader);
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), TYPE_D0F0xBC, 0xC0016130, &Value30, 0, StdHeader);

  ReadOpn.OpnChar [0] = (Value24 >> 15) & 0x7F;
  ReadOpn.OpnChar [1] = (Value24 >> 22) & 0x7F;
  ReadOpn.OpnChar [2] = (Value24 >> 29) | (((Value28) & 0xF) << 3);
  ReadOpn.OpnChar [3] = (Value28 >> 4) & 0x7F;
  ReadOpn.OpnChar [4] = (Value28 >> 11) & 0x7F;
  ReadOpn.OpnChar [5] = (Value28 >> 18) & 0x7F;
  ReadOpn.OpnChar [6] = (Value28 >> 25) & 0x7F;
  ReadOpn.OpnChar [7] = Value2C & 0x7F;
  ReadOpn.OpnChar [8] = (Value2C >> 7) & 0x7F;
  ReadOpn.OpnChar [9] = (Value2C >> 14) & 0x7F;
  ReadOpn.OpnChar [10] = (Value2C >> 21) & 0x7F;
  ReadOpn.OpnChar [11] = (Value2C >> 28) | ((Value30 & 0x7) << 4);
  ReadOpn.OpnChar [12] = (Value30 >> 3) & 0x7F;

  IDS_HDT_CONSOLE (GNB_TRACE, "  OPN: ");
  for (OpnCharIndex = 0; OpnCharIndex <= OPN_CHAR_LENGTH - 1; OpnCharIndex++) {
    IDS_HDT_CONSOLE (GNB_TRACE, "%c", ReadOpn.OpnChar [OpnCharIndex]);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "\n");

  OpnNumIndex = 0;
  while (OpnPtr [OpnNumIndex].OpnChar [0] != 0x0) {
    for (OpnCharIndex = 0; OpnCharIndex <= OPN_CHAR_LENGTH - 1; OpnCharIndex++) {
      if (OpnPtr [OpnNumIndex].OpnChar [OpnCharIndex] != ReadOpn.OpnChar [OpnCharIndex]) {
        break;
      }
    }
    if (OpnCharIndex == OPN_CHAR_LENGTH) {
      return TRUE;
    }
    OpnNumIndex++;
  }

  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Override Fuse Workaround for BRAM4 PlatSi
 *
 *
 * @param[out] PpFuseArray      Pointer to save fuse table
 * @param[in]  StdHeader        Pointer to Standard configuration
 */
VOID
NbFusePlatSiWorkaround_BRAM4_CZ (
  IN       PP_FUSE_ARRAY_V2       *PpFuseArray,
  IN      AMD_CONFIG_PARAMS       *StdHeader
  )
{
#if 0
  CPU_LOGICAL_ID          LogicalId;
  CPUID_DATA              CpuId;
  OPN_CHAR_STRUCT         OpnRequiredWA [] = {
    {'1', 'D', '3', '4', '0', '1', 'A', 'G', 'M', '4', '4', 'A', 'B'},
    {'1', 'D', '3', '4', 'E', '1', 'A', 'G', 'M', '4', '4', 'A', 'B'},
    {0x0}
  };

  IDS_HDT_CONSOLE (GNB_TRACE, "NbFusePlatSiWorkaround_BRAM4_CZ Enter\n");
  GetLogicalIdOfCurrentCore (&LogicalId, StdHeader);
  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  if (((LogicalId.Revision & AMD_F15_BR_A1) != 0) && (((CpuId.EBX_Reg >> 28) & 0xF) == CZ_SOCKET_AM4) && (CheckOpnCZ (StdHeader, (OPN_CHAR_STRUCT *) &OpnRequiredWA[0]) == TRUE)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "  Applying PlatSi PP Fuse workaround\n");
    PpFuseArray->PerfFlag = 0x1F;
    PpFuseArray->PerfFlag5 = 1;
    PpFuseArray->PerfFlag6 = 1;
    PpFuseArray->PerfFlag7 = 1;
    PpFuseArray->PowerSavingsFlag = 0x1F;
    PpFuseArray->PowerSavingsFlag5 = 0x1;
    PpFuseArray->PowerSavingsFlag6 = 0x1;
    PpFuseArray->PowerSavingsFlag7 = 0x1;

    PpFuseArray->PerfFlag |= ((UINT8) (PpFuseArray->PerfFlag5 << 5)) |
                           ((UINT8) (PpFuseArray->PerfFlag6 << 6)) |
                           ((UINT8) (PpFuseArray->PerfFlag7 << 7));

    PpFuseArray->PowerSavingsFlag |= ((UINT8) (PpFuseArray->PowerSavingsFlag5 << 5)) |
                                   ((UINT8) (PpFuseArray->PowerSavingsFlag6 << 6)) |
                                   ((UINT8) (PpFuseArray->PowerSavingsFlag7 << 7));

  }
  IDS_HDT_CONSOLE (GNB_TRACE, "NbFusePlatSiWorkaround_BRAM4_CZ Exit\n");
#endif
}

/*----------------------------------------------------------------------------------------*/
/**
 * Gnb load fuse table
 *
 *
 *
 * @param[in] StdHeader        Pointer to Standard configuration
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
GnbLoadFuseTableCZ (
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  PP_FUSE_ARRAY_V2          *PpFuseArray;
  AGESA_STATUS           Status;
  D0F0xBC_xD8230F00_STRUCT        D0F0xBC_xD8230F00;

  Status = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbLoadFuseTableCZ Enter\n");

  PpFuseArray = (PP_FUSE_ARRAY_V2 *) GnbAllocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, sizeof (PP_FUSE_ARRAY_V2), StdHeader);
  ASSERT (PpFuseArray != NULL);
  if (PpFuseArray != NULL) {
    //Support for real fuse table
    GnbRegisterReadCZ (GnbGetHandle (StdHeader), D0F0xBC_xD8230F00_TYPE, D0F0xBC_xD8230F00_ADDRESS, &D0F0xBC_xD8230F00.Value, 0, StdHeader);
    if ((D0F0xBC_xD8230F00.Field.COF_VID_PROG) && (GnbBuildOptions.GnbLoadRealFuseTable)) {
      NbFuseLoadFuseTableCZ (&FuseTableCZ, PpFuseArray, StdHeader);
      PpFuseArray->VceStateTableSupport = TRUE;
      IDS_HDT_CONSOLE (NB_MISC, "  Processor Fused\n");
    } else {
      LibAmdMemCopy (PpFuseArray, &DefaultPpFuseArrayCZ, sizeof (PP_FUSE_ARRAY_V2), StdHeader);
      IDS_HDT_CONSOLE (NB_MISC, "  Processor Unfuse\n");
    }
    NbFuseLoadFuseTableCZ (&PPTableCZ, PpFuseArray, StdHeader);
// todo:_workaround    NbFusePlatSiWorkaround_BRAM4_CZ (PpFuseArray, StdHeader);
    IDS_OPTION_CALLOUT (IDS_CALLOUT_GNB_PPFUSE_OVERRIDE, PpFuseArray, StdHeader);
    GnbFuseTableDebugDumpCZ (PpFuseArray, StdHeader);
  } else {
    Status = AGESA_ERROR;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbLoadFuseTableCZ Exit [0x%x]\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Override fuses based on AGESA params
 *
 *
 * @param[in]   StdHeader     Standard configuration header
 * @retval      AGESA_STATUS
 */
AGESA_STATUS
GnbOverrideGpuFreqeuencyCZ (
  IN      AMD_CONFIG_PARAMS       *StdHeader
  )
{
  AGESA_STATUS          AgesaStatus;
  PP_FUSE_ARRAY_V2      *PpFuseArray;
  AMD_ENV_PARAMS        *EnvParamsPtr;
  UINT32                Sclk;
  UINT32                SclkMax;
  UINT32                SclkCap;
  UINT8                 DpmIndex;
  UINT8                 Index;
  UINT8                 PerfFlagOverride;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbOverrideGpuFreqeuencyCZ Enter\n");

  AgesaStatus = AGESA_SUCCESS;
  PpFuseArray = GnbLocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, StdHeader);

  EnvParamsPtr = (AMD_ENV_PARAMS *) StdHeader;

  ASSERT (PpFuseArray != NULL);

  if (PpFuseArray == NULL) {
    IDS_HDT_CONSOLE (GNB_TRACE, "  ERROR! Cannot locate fuse table\n");
    AgesaStatus = AGESA_ERROR;
    return AgesaStatus;
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "  PerfFlag => %02x\n", PpFuseArray->PerfFlag);
  PerfFlagOverride = 0;
  IDS_HDT_CONSOLE (GNB_TRACE, "  PsFlag => %02x\n", PpFuseArray->PowerSavingsFlag);

  // Convert SclkCap to 10KHz units
  SclkCap = EnvParamsPtr->GnbEnvConfiguration.GpuFrequencyLimit * 100;

  // Loop through fused DPM states and find the highest supported Performance Sclk
  SclkMax = 0;
  for (DpmIndex = 0;
       DpmIndex < (sizeof (PpFuseArray->SclkDid) / sizeof (PpFuseArray->SclkDid[0]));
       DpmIndex++) {

    if (PpFuseArray->PerfFlag & (1 << DpmIndex)) {

      Sclk = (PpFuseArray->SclkDid[DpmIndex] != 0) ?
             GfxFmCalculateClock (PpFuseArray->SclkDid[DpmIndex], StdHeader) : 0;

      IDS_HDT_CONSOLE (GNB_TRACE, "  Sclk = %d\n", Sclk);

      if (Sclk > SclkMax) {
        SclkMax = Sclk;
      }
      if (Sclk <= SclkCap) {
        PerfFlagOverride |= (1 << DpmIndex);
        IDS_HDT_CONSOLE (GNB_TRACE, "  PerfFlagOverride => %02x\n", PerfFlagOverride);
      } else {
        // Should not happen, but if DpmIndex is 0 then an invalid low limit was
        // probably used
        if (DpmIndex > 0) {
          DpmIndex--;
        }
        break;
      }
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "  DpmIndex = %d\n", DpmIndex);
  for (Index = 0;
       Index < (sizeof (PpFuseArray->VceReqSclkSel) / sizeof (PpFuseArray->VceReqSclkSel[0]));
       Index++) {
    if (PpFuseArray->VceReqSclkSel[Index] > DpmIndex) {
      PpFuseArray->VceReqSclkSel[Index] = DpmIndex;
      IDS_HDT_CONSOLE (GNB_TRACE, "  VceReqSclkSel[%02x] => %d\n", Index, DpmIndex);
    }
  }

  for (Index = 0;
       Index < (sizeof (PpFuseArray->SclkDid) / sizeof (PpFuseArray->SclkDid[0]));
       Index++) {
    if (Index > DpmIndex) {
      PpFuseArray->SclkDid[Index] = PpFuseArray->SclkDid[DpmIndex];
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "  Max Sclk = %d\n", SclkMax);
  IDS_HDT_CONSOLE (GNB_TRACE, "  PerfFlagOverride => %02x\n", PerfFlagOverride);

  if (PerfFlagOverride == 0) {
    // Invalid low limit was used
    PerfFlagOverride = 1;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Force PerfFlagOverride => %02x\n", PerfFlagOverride);
  }

  PpFuseArray->PerfFlag = PerfFlagOverride;

  if (PerfFlagOverride == 1) {
    PpFuseArray->PowerSavingsFlag = PerfFlagOverride;
    IDS_HDT_CONSOLE (GNB_TRACE, "  PsFlagOverride   => %02x\n", PerfFlagOverride);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbOverrideGpuFreqeuencyCZ Enter\n");
  return AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Debug dump fuse table
 *
 *
 * @param[out] PpFuseArray      Pointer to save fuse table
 * @param[in]  StdHeader        Pointer to Standard configuration
 */

VOID
GnbFuseTableDebugDumpCZ (
  IN       PP_FUSE_ARRAY_V2       *PpFuseArray,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN   Index;

  IDS_HDT_CONSOLE (NB_MISC, "<------------ GNB FUSE TABLE------------>\n");
  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  VCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->VclkDid[Index],
      (PpFuseArray->VclkDid[Index] != 0) ? (GfxFmCalculateClock (PpFuseArray->VclkDid[Index], StdHeader) / 100) : 0
      );
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  DCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->DclkDid[Index],
      (PpFuseArray->DclkDid[Index] != 0) ? (GfxFmCalculateClock (PpFuseArray->DclkDid[Index], StdHeader) / 100) : 0
    );
  }
  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  DISPCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->DispClkDid[Index],
      (PpFuseArray->DispClkDid[Index] != 0) ? (GfxFmCalculateClock (PpFuseArray->DispClkDid[Index], StdHeader) / 100) : 0
      );
  }
  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  ECLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->EclkDid[Index],
      (PpFuseArray->EclkDid[Index] != 0) ? (GfxFmCalculateClock (PpFuseArray->EclkDid[Index], StdHeader) / 100) : 0
      );
  }
  for (Index = 0; Index < 5; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  SamuCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->SamClkDid[Index],
      (PpFuseArray->SamClkDid[Index] != 0) ?
          (GfxFmCalculateClock (PpFuseArray->SamClkDid[Index], StdHeader) / 100) : 0
      );
  }
  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  VceReqSclkSel[%d] - 0x%02x \n",
      Index,
      PpFuseArray->VceReqSclkSel[Index]
      );
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  VCE SCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->SclkDid[PpFuseArray->VceReqSclkSel[Index]],
      (PpFuseArray->SclkDid[PpFuseArray->VceReqSclkSel[Index]] != 0) ? (GfxFmCalculateClock (PpFuseArray->SclkDid[PpFuseArray->VceReqSclkSel[Index]], StdHeader) / 100) : 0
      );
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  VCE Flags[ % d] - 0x % 02x\n",
      Index,
      PpFuseArray->VceFlags[Index]
      );
  }
  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "\n  SCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->SclkDid[Index],
      (PpFuseArray->SclkDid[Index] != 0) ?
          (GfxFmCalculateClock (PpFuseArray->SclkDid[Index], StdHeader) / 100) : 0
    );
    IDS_HDT_CONSOLE (NB_MISC, "  SCLK/GNB VID[%d] - 0x%02x\n", Index, PpFuseArray->VddNbVid[Index]);
    IDS_HDT_CONSOLE (NB_MISC, "  VddNbVidOffset[%d] - 0x%02x\n", Index, PpFuseArray->VddNbVidOffset[Index]);
    IDS_HDT_CONSOLE (NB_MISC, "  GFX VID[%d] - 0x%02x\n", Index, PpFuseArray->GfxVid[Index]);
    IDS_HDT_CONSOLE (NB_MISC, "  GfxVidOffset[%d] - 0x%02x\n", Index, PpFuseArray->GfxVidOffset[Index]);
  }

  for (Index = 0; Index < 8; Index++) {
    IDS_HDT_CONSOLE (
      NB_MISC,
      "  AcpCLK DID[%d] - 0x%02x (%dMHz)\n",
      Index,
      PpFuseArray->AcpClkDid[Index],
      (PpFuseArray->AcpClkDid[Index] != 0) ?
          (GfxFmCalculateClock (PpFuseArray->AcpClkDid[Index], StdHeader) / 100) : 0
      );
  }
  for (Index = 0; Index < 6; Index++) {
    IDS_HDT_CONSOLE (NB_MISC, "  State #%d\n", Index);
    IDS_HDT_CONSOLE (NB_MISC, "    Vclk/Dclk Index - 0x%x\n", PpFuseArray->VclkDclkSel[Index]);
  }
  IDS_HDT_CONSOLE (NB_MISC, "  GEN2 VID - 0x%x\n", PpFuseArray->PcieGen2Vid);
  IDS_HDT_CONSOLE (NB_MISC, "  GEN3 VID - 0x%x\n", PpFuseArray->PcieGen3Vid);
  IDS_HDT_CONSOLE (NB_MISC, "  Main PLL Id - 0x%x\n", PpFuseArray->MainPllId);
  IDS_HDT_CONSOLE (NB_MISC, "  GpuBoostCap  - %x\n", PpFuseArray->GpuBoostCap);
  IDS_HDT_CONSOLE (NB_MISC, "  SclkDpmBoostMargin    - %x\n", PpFuseArray->SclkDpmBoostMargin);
  IDS_HDT_CONSOLE (NB_MISC, "  SclkDpmThrottleMargin - %x\n", PpFuseArray->SclkDpmThrottleMargin);
  IDS_HDT_CONSOLE (
    NB_MISC, "  SclkThermDid          - %x(%dMHz)\n",
    PpFuseArray->SclkThermDid,
    (PpFuseArray->SclkThermDid != 0) ? (GfxFmCalculateClock (PpFuseArray->SclkThermDid, StdHeader) / 100) : 0
    );
  if (PpFuseArray->HtcEn == 0) {
    IDS_HDT_CONSOLE (NB_MISC, "  HtcEn                 - Disabled\n");
  } else {
    IDS_HDT_CONSOLE (NB_MISC, "  HtcEn                 - Enabled\n    HtcTmpLmt = %d - HtcHystLmt = %d", PpFuseArray->HtcTmpLmt, PpFuseArray->HtcHystLmt);
  }
  for (Index = 0; Index < 4; Index++) {
    if (PpFuseArray->NbPstateEn[Index] == 0) {
      IDS_HDT_CONSOLE (NB_MISC, "  NbPstate[%d]          - Disabled\n", Index);
    } else {
      IDS_HDT_CONSOLE (NB_MISC, "  NbPstate[%d]          - Enabled\n", Index);
      IDS_HDT_CONSOLE (NB_MISC, "    NbDid = %d\n", PpFuseArray->NbDid[Index]);
      IDS_HDT_CONSOLE (NB_MISC, "    NbFid = %d\n", PpFuseArray->NbFid[Index]);
      IDS_HDT_CONSOLE (NB_MISC, "    MemPstate = %d\n", PpFuseArray->MemPstate[Index]);
      IDS_HDT_CONSOLE (NB_MISC, "    NbVid = %d\n", PpFuseArray->NbVid_6_0[Index] + (PpFuseArray->NbVid_7[Index] << 7));
    }
  }
  IDS_HDT_CONSOLE (NB_MISC, "  MainPllOpFreqIdStartup - %d\n", PpFuseArray->MainPllOpFreqIdStartup);
  for (Index = 0; Index < 4; Index++) {
    IDS_HDT_CONSOLE (NB_MISC, "  DisDllShutdownSR[%d]  - %d \n", Index, PpFuseArray->DisDllShutdownSR[Index]);
  }
  for (Index = 0; Index < 4; Index++) {
    IDS_HDT_CONSOLE (NB_MISC, "  MemPhyPllPdMode[%d]   - %d \n", Index, PpFuseArray->MemPhyPllPdMode[Index]);
  }
  for (Index = 0; Index < 4; Index++) {
    IDS_HDT_CONSOLE (NB_MISC, "  MemClkFreq[%d]        - %d \n", Index, PpFuseArray->MemClkFreq[Index]);
    IDS_HDT_CONSOLE (NB_MISC, "  M1MemClkFreq[%d]      - %d \n", Index, PpFuseArray->M1MemClkFreq[Index]);
  }
  IDS_HDT_CONSOLE (NB_MISC, "  VceMclk         - %02x \n", PpFuseArray->VceMclk);
  IDS_HDT_CONSOLE (NB_MISC, "  PerfFlag        - %02x \n", PpFuseArray->PerfFlag);
  IDS_HDT_CONSOLE (NB_MISC, "  PSFlag          - %02x \n", PpFuseArray->PowerSavingsFlag);
  IDS_HDT_CONSOLE (NB_MISC, "<------------ GNB FUSE END-------------->\n");
}

