/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  APCB
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
#include "Porting.h"
#include "Addendum/Apcb/Inc/RV/APCB.h"
#include "ApcbCommon.h"
#include <Library/IdsLib.h>
#include <Filecode.h>

#define FILECODE PSP_APCB_TOKENSRV_CBS_EXT_TOKENS_FILECODE                  

//
// APCB CBS Token ID definitions
//
TOKEN_PAIR CbsExtTokenPair[] = {
  { APCB_ID_CBS_DF_CMN_GMI_ENCRYPTION,                APCB_TOKEN_CBS_DF_CMN_GMI_ENCRYPTION               },
  { APCB_ID_CBS_DF_CMN_X_GMI_ENCRYPTION,              APCB_TOKEN_CBS_DF_CMN_X_GMI_ENCRYPTION             },
  { APCB_ID_CBS_DF_CMN_CC6_MEM_ENCRYPTION,            APCB_TOKEN_CBS_DF_CMN_CC6_MEM_ENCRYPTION           },
  { APCB_ID_CBS_DF_CMN_CC6_ALLOCATION_SCHEME,         APCB_TOKEN_CBS_DF_CMN_CC6_ALLOCATION_SCHEME        },
  { APCB_ID_CBS_DF_CMN_SYS_PROBE_FILTER,              APCB_TOKEN_CBS_DF_CMN_SYS_PROBE_FILTER             },
  { APCB_ID_CBS_DF_CMN_MEM_INTLV,                     APCB_TOKEN_CBS_DF_CMN_MEM_INTLV                    },
  { APCB_ID_CBS_DF_CMN_MEM_INTLV_SIZE,                APCB_TOKEN_CBS_DF_CMN_MEM_INTLV_SIZE               },
  { APCB_ID_CBS_DF_CMN_CHNL_INTLV_HASH,               APCB_TOKEN_CBS_DF_CMN_CHNL_INTLV_HASH              },
  { APCB_ID_CBS_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4, APCB_TOKEN_CBS_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4},
  { APCB_ID_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4, APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4},
  { APCB_ID_CBS_CMN_MEM_CTRLLER_BANK_SWIZZLE_DDR4,    APCB_TOKEN_CBS_CMN_MEM_CTRLLER_BANK_SWIZZLE_DDR4   },
  { APCB_ID_CBS_CMN_MEM_ADDRESS_HASHING_DDR4,         APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASHING_DDR4        },
  { APCB_ID_CBS_CMN_MEM_SPEED_DDR4,                   APCB_TOKEN_CBS_CMN_MEM_SPEED_DDR4                  },
  { APCB_ID_CBS_CMN_MEM_TIMING_TCL_DDR4,              APCB_TOKEN_CBS_CMN_MEM_TIMING_TCL_DDR4             },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRCDRD_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDRD_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRCDWR_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCDWR_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRP_DDR4,              APCB_TOKEN_CBS_CMN_MEM_TIMING_TRP_DDR4             },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRAS_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TRAS_DDR4            },
  { APCB_ID_CBS_CMN_MEM_DATA_POISONING_DDR4,          APCB_TOKEN_CBS_CMN_MEM_DATA_POISONING_DDR4         },
  { APCB_ID_CBS_CMN_MEM_ADDRESS_HASH_BANK_DDR4,       APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_BANK_DDR4      },
  { APCB_ID_CBS_CMN_MEM_ADDRESS_HASH_CS_DDR4,         APCB_TOKEN_CBS_CMN_MEM_ADDRESS_HASH_CS_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TSME_DDR4,                    APCB_TOKEN_CBS_CMN_MEM_TSME_DDR4                   },
  { APCB_ID_CBS_CMN_MEM_OVERCLOCK_DDR4,               APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_DDR4              },
  { APCB_ID_CBS_CMN_GNB_GFX_UMA_MODE,                 APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_MODE                },
  { APCB_ID_CBS_CMN_GNB_GFX_UMA_VERSION,              APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_VERSION             },
  { APCB_ID_CBS_CMN_GNB_GFX_DISPLAY_RESOLUTION,       APCB_TOKEN_CBS_CMN_GNB_GFX_DISPLAY_RESOLUTION      },
  { APCB_ID_CBS_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE,    APCB_TOKEN_CBS_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE   },
  { APCB_ID_CBS_CMN_GNB_SOC_OVERCLOCK_VID,            APCB_TOKEN_CBS_CMN_GNB_SOC_OVERCLOCK_VID           },
  { APCB_ID_CBS_CMN_GNB_FCLK_OC_FLAG,                 APCB_TOKEN_CBS_CMN_GNB_FCLK_OC_FLAG                },
  { APCB_ID_CBS_CMN_CPU_SEV_ASID_SPACE_LIMIT,         APCB_TOKEN_CBS_CMN_CPU_SEV_ASID_SPACE_LIMIT        },
  { APCB_ID_CBS_CMN_MEM_SPD_READ_OPTIMIZATION_DDR4,   APCB_TOKEN_CBS_CMN_MEM_SPD_READ_OPTIMIZATION_DDR4  },
  { APCB_ID_CBS_CMN_MEM_MBIST_EN,                     APCB_TOKEN_CBS_CMN_MEM_MBIST_EN                    },
  { APCB_ID_CBS_CMN_MEM_MBIST_SUB_TEST,               APCB_TOKEN_CBS_CMN_MEM_MBIST_SUB_TEST              },
  { APCB_ID_CBS_DF_CMN_MEM_CLEAR,                     APCB_TOKEN_CBS_DF_CMN_MEM_CLEAR                    },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRC_CTRL_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_CTRL_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRC_DDR4,              APCB_TOKEN_CBS_CMN_MEM_TIMING_TRC_DDR4             },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRRD_S_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_S_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRRD_L_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TRRD_L_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TFAW_CTRL_DDR4,        APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_CTRL_DDR4       },
  { APCB_ID_CBS_CMN_MEM_TIMING_TFAW_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TFAW_DDR4            },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWTR_S_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_S_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWTR_L_DDR4,           APCB_TOKEN_CBS_CMN_MEM_TIMING_TWTR_L_DDR4          },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWR_CTRL_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_CTRL_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWR_DDR4,              APCB_TOKEN_CBS_CMN_MEM_TIMING_TWR_DDR4             },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4,     APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4    },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRCPAGE_DDR4,          APCB_TOKEN_CBS_CMN_MEM_TIMING_TRCPAGE_DDR4         },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4,  APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4 },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_L_DDR4,       APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_L_DDR4      },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4,  APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4 },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_L_DDR4,       APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_L_DDR4      },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC_CTRL_DDR4,        APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_CTRL_DDR4       },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC_DDR4            },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC2_CTRL_DDR4,       APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_CTRL_DDR4      },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC2_DDR4,            APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC2_DDR4           },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC4_CTRL_DDR4,       APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_CTRL_DDR4      },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRFC4_DDR4,            APCB_TOKEN_CBS_CMN_MEM_TIMING_TRFC4_DDR4           },
  { APCB_ID_CBS_CMN_MEM_OVERCLOCK_FAIL_CNT,           APCB_TOKEN_CBS_CMN_MEM_OVERCLOCK_FAIL_CNT          },
  { APCB_ID_CBS_CMN_MEM_CTRLLER_PROC_ODT_DDR4,        APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PROC_ODT_DDR4       },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SC_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SC_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_SD_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_SD_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDRD_DD_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDRD_DD_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SC_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SC_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_SD_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_SD_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRWR_DD_DDR4,         APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRWR_DD_DDR4        },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRDWR_DDR4,            APCB_TOKEN_CBS_CMN_MEM_TIMING_TRDWR_DDR4           },
  { APCB_ID_CBS_CMN_MEM_TIMING_TWRRD_DDR4,            APCB_TOKEN_CBS_CMN_MEM_TIMING_TWRRD_DDR4           },
  { APCB_ID_CBS_CMN_MEM_TIMING_TRTP_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TRTP_DDR4            },
  { APCB_ID_CBS_CMN_MEM_TIMING_TCWL_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TCWL_DDR4            },
  { APCB_ID_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4,     APCB_TOKEN_CBS_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4    },
  { APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_NOM_DDR4,         APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_NOM_DDR4        },
  { APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_WR_DDR4,          APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_WR_DDR4         },
  { APCB_ID_CBS_CMN_MEM_CTRLLER_RTT_PARK_DDR4,        APCB_TOKEN_CBS_CMN_MEM_CTRLLER_RTT_PARK_DDR4       },
  { APCB_ID_CBS_CMN_MEM_TIMING_TCKE_DDR4,             APCB_TOKEN_CBS_CMN_MEM_TIMING_TCKE_DDR4            },
  { APCB_ID_CBS_CMN_MEM_CTRLLER_DATA_SCRAMBLE_DDR4,   APCB_TOKEN_CBS_CMN_MEM_CTRLLER_DATA_SCRAMBLE_DDR4  },
  { APCB_ID_CBS_CMN_MEM_CTRLLER2_T_MODE_DDR4,         APCB_TOKEN_CBS_CMN_MEM_CTRLLER2_T_MODE_DDR4        },
  { APCB_ID_CBS_CMN_MEM_GEAR_DOWN_MODE_DDR4,          APCB_TOKEN_CBS_CMN_MEM_GEAR_DOWN_MODE_DDR4         },
  { APCB_ID_CBS_CMN_MEM_MBIST_AGGRESSORS,             APCB_TOKEN_CBS_CMN_MEM_MBIST_AGGRESSORS            },
  { APCB_ID_CBS_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT, APCB_TOKEN_CBS_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT},
  { APCB_ID_CBS_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4,       APCB_TOKEN_CBS_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4      },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4,      APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4     },
  { APCB_ID_CBS_CMN_MEM_ADDR_CMD_SETUP_DDR4,          APCB_TOKEN_CBS_CMN_MEM_ADDR_CMD_SETUP_DDR4         },
  { APCB_ID_CBS_CMN_MEM_CS_ODT_SETUP_DDR4,            APCB_TOKEN_CBS_CMN_MEM_CS_ODT_SETUP_DDR4           },
  { APCB_ID_CBS_CMN_MEM_CKE_SETUP_DDR4,               APCB_TOKEN_CBS_CMN_MEM_CKE_SETUP_DDR4              },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4,   APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4  },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4,   APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4 },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4, APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4 },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4, APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4 },
  { APCB_ID_CBS_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4,   APCB_TOKEN_CBS_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4  },
  { APCB_ID_CBS_CPU_RELAXED_EDC_THROTTLING,           APCB_TOKEN_CBS_CPU_RELAXED_EDC_THROTTLING          },
  { APCB_ID_CBS_CMN_CLDO_VDDP_CTL,                    APCB_TOKEN_CBS_CMN_CLDO_VDDP_CTL                   },
  { APCB_ID_CBS_CMN_CLDOVDD_PVOLTAGE,                 APCB_TOKEN_CBS_CMN_CLDOVDD_PVOLTAGE                },
};

UINT16
mTranslateCbsExtTokenId (
  IN       UINT16             CommonId
  )
{
  UINT16 i;

  for (i = 0; i < sizeof (CbsExtTokenPair) / sizeof (TOKEN_PAIR); i++) {
    if (CommonId == CbsExtTokenPair[i].ApcbCommonId) {
      return CbsExtTokenPair[i].ApcbToken;
    }
  }

  ASSERT (FALSE);

  return 0xFFFF;
}


