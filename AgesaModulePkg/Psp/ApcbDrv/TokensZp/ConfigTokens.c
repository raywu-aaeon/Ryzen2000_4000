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
#include "Addendum/Apcb/Inc/ZP/APCB.h"
#include "ApcbCommon.h"
#include <Library/IdsLib.h>
#include <Filecode.h>

#define FILECODE PSP_APCB_TOKENSZP_CONFIG_TOKENS_FILECODE

//
// APCB Config Token ID definitions
//
TOKEN_PAIR ConfigTokenPair[] = {
  { APCB_ID_CONFIG_CCX_MIN_SEV_ASID,                APCB_TOKEN_CONFIG_CCX_MIN_SEV_ASID                   },
  { APCB_ID_CONFIG_DF_GMI_ENCRYPT,                  APCB_TOKEN_CONFIG_DF_GMI_ENCRYPT                     },
  { APCB_ID_CONFIG_DF_XGMI_ENCRYPT,                 APCB_TOKEN_CONFIG_DF_XGMI_ENCRYPT                    },
  { APCB_ID_CONFIG_DF_SAVE_RESTORE_MEM_ENCRYPT,     APCB_TOKEN_CONFIG_DF_SAVE_RESTORE_MEM_ENCRYPT        },
  { APCB_ID_CONFIG_DF_SYS_STORAGE_AT_TOP_OF_MEM,    APCB_TOKEN_CONFIG_DF_SYS_STORAGE_AT_TOP_OF_MEM       },
  { APCB_ID_CONFIG_DF_PROBE_FILTER_ENABLE,          APCB_TOKEN_CONFIG_DF_PROBE_FILTER_ENABLE             },
  { APCB_ID_CONFIG_DF_BOTTOMIO,                     APCB_TOKEN_CONFIG_DF_BOTTOMIO                        },
  { APCB_ID_CONFIG_DF_MEM_INTERLEAVING,             APCB_TOKEN_CONFIG_DF_MEM_INTERLEAVING                },
  { APCB_ID_CONFIG_DF_DRAM_INTERLEAVE_SIZE,         APCB_TOKEN_CONFIG_DF_DRAM_INTERLEAVE_SIZE            },
  { APCB_ID_CONFIG_DF_ENABLE_CHAN_INTLV_HASH,       APCB_TOKEN_CONFIG_DF_ENABLE_CHAN_INTLV_HASH          },
  { APCB_ID_CONFIG_DF_PCI_MMIO_SIZE,                APCB_TOKEN_CONFIG_DF_PCI_MMIO_SIZE                   },
  { APCB_ID_CONFIG_DF_CAKE_CRC_THRESH_PERF_BOUNDS,  APCB_TOKEN_CONFIG_DF_CAKE_CRC_THRESH_PERF_BOUNDS     },
  { APCB_ID_CONFIG_DF_MEM_CLEAR,                    APCB_TOKEN_CONFIG_DF_MEM_CLEAR                       },
  { APCB_ID_CONFIG_MEMHOLEREMAPPING,                APCB_TOKEN_CONFIG_MEMHOLEREMAPPING                   },
  { APCB_ID_CONFIG_LIMITMEMORYTOBELOW1TB,           APCB_TOKEN_CONFIG_LIMITMEMORYTOBELOW1TB              },
  { APCB_ID_CONFIG_USERTIMINGMODE,                  APCB_TOKEN_CONFIG_USERTIMINGMODE                     },
  { APCB_ID_CONFIG_MEMCLOCKVALUE,                   APCB_TOKEN_CONFIG_MEMCLOCKVALUE                      },
  { APCB_ID_CONFIG_ENABLECHIPSELECTINTLV,           APCB_TOKEN_CONFIG_ENABLECHIPSELECTINTLV              },
  { APCB_ID_CONFIG_ENABLEECCFEATURE,                APCB_TOKEN_CONFIG_ENABLEECCFEATURE                   },
  { APCB_ID_CONFIG_ENABLEPOWERDOWN,                 APCB_TOKEN_CONFIG_ENABLEPOWERDOWN                    },
  { APCB_ID_CONFIG_ENABLEPARITY,                    APCB_TOKEN_CONFIG_ENABLEPARITY                       },
  { APCB_ID_CONFIG_ENABLEBANKSWIZZLE,               APCB_TOKEN_CONFIG_ENABLEBANKSWIZZLE                  },
  { APCB_ID_CONFIG_ENABLEMEMCLR,                    APCB_TOKEN_CONFIG_ENABLEMEMCLR                       },
  { APCB_ID_CONFIG_UMAMODE,                         APCB_TOKEN_CONFIG_UMAMODE                            },
  { APCB_ID_CONFIG_UMASIZE,                         APCB_TOKEN_CONFIG_UMASIZE                            },
  { APCB_ID_CONFIG_MEMRESTORECTL,                   APCB_TOKEN_CONFIG_MEMRESTORECTL                      },
  { APCB_ID_CONFIG_ISCAPSULEMODE,                   APCB_TOKEN_CONFIG_ISCAPSULEMODE                      },
  { APCB_ID_CONFIG_FORCETRAINMODE,                  APCB_TOKEN_CONFIG_FORCETRAINMODE                     },
  { APCB_ID_CONFIG_DIMMTYPEUSEDINMIXEDCONFIG,       APCB_TOKEN_CONFIG_DIMMTYPEUSEDINMIXEDCONFIG          },
  { APCB_ID_CONFIG_AMPENABLE,                       APCB_TOKEN_CONFIG_AMPENABLE                          },
  { APCB_ID_CONFIG_DRAMDOUBLEREFRESHRATE,           APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATE              },
  { APCB_ID_CONFIG_PMUTRAINMODE,                    APCB_TOKEN_CONFIG_PMUTRAINMODE                       },
  { APCB_ID_CONFIG_ECCREDIRECTION,                  APCB_TOKEN_CONFIG_ECCREDIRECTION                     },
  { APCB_ID_CONFIG_SCRUBDRAMRATE,                   APCB_TOKEN_CONFIG_SCRUBDRAMRATE                      },
  { APCB_ID_CONFIG_SCRUBL2RATE,                     APCB_TOKEN_CONFIG_SCRUBL2RATE                        },
  { APCB_ID_CONFIG_SCRUBL3RATE,                     APCB_TOKEN_CONFIG_SCRUBL3RATE                        },
  { APCB_ID_CONFIG_SCRUBICRATE,                     APCB_TOKEN_CONFIG_SCRUBICRATE                        },
  { APCB_ID_CONFIG_SCRUBDCRATE,                     APCB_TOKEN_CONFIG_SCRUBDCRATE                        },
  { APCB_ID_CONFIG_ECCSYNCFLOOD,                    APCB_TOKEN_CONFIG_ECCSYNCFLOOD                       },
  { APCB_ID_CONFIG_ECCSYMBOLSIZE,                   APCB_TOKEN_CONFIG_ECCSYMBOLSIZE                      },
  { APCB_ID_CONFIG_DQSTRAININGCONTROL,              APCB_TOKEN_CONFIG_DQSTRAININGCONTROL                 },
  { APCB_ID_CONFIG_UMAABOVE4G,                      APCB_TOKEN_CONFIG_UMAABOVE4G                         },
  { APCB_ID_CONFIG_UMAALIGNMENT,                    APCB_TOKEN_CONFIG_UMAALIGNMENT                       },
  { APCB_ID_CONFIG_MEMORYALLCLOCKSON,               APCB_TOKEN_CONFIG_MEMORYALLCLOCKSON                  },
  { APCB_ID_CONFIG_MEMORYBUSFREQUENCYLIMIT,         APCB_TOKEN_CONFIG_MEMORYBUSFREQUENCYLIMIT            },
  { APCB_ID_CONFIG_POWERDOWNMODE,                   APCB_TOKEN_CONFIG_POWERDOWNMODE                      },
  { APCB_ID_CONFIG_IGNORESPDCHECKSUM,               APCB_TOKEN_CONFIG_IGNORESPDCHECKSUM                  },
  { APCB_ID_CONFIG_MEMORYMODEUNGANGED,              APCB_TOKEN_CONFIG_MEMORYMODEUNGANGED                 },
  { APCB_ID_CONFIG_MEMORYQUADRANKCAPABLE,           APCB_TOKEN_CONFIG_MEMORYQUADRANKCAPABLE              },
  { APCB_ID_CONFIG_MEMORYRDIMMCAPABLE,              APCB_TOKEN_CONFIG_MEMORYRDIMMCAPABLE                 },
  { APCB_ID_CONFIG_MEMORYLRDIMMCAPABLE,             APCB_TOKEN_CONFIG_MEMORYLRDIMMCAPABLE                },
  { APCB_ID_CONFIG_MEMORYUDIMMCAPABLE,              APCB_TOKEN_CONFIG_MEMORYUDIMMCAPABLE                 },
  { APCB_ID_CONFIG_MEMORYSODIMMCAPABLE,             APCB_TOKEN_CONFIG_MEMORYSODIMMCAPABLE                },
  { APCB_ID_CONFIG_DRAMDOUBLEREFRESHRATEEN,         APCB_TOKEN_CONFIG_DRAMDOUBLEREFRESHRATEEN            },
  { APCB_ID_CONFIG_DIMMTYPEDDDR4CAPABLE,            APCB_TOKEN_CONFIG_DIMMTYPEDDDR4CAPABLE               },
  { APCB_ID_CONFIG_DIMMTYPEDDDR3CAPABLE,            APCB_TOKEN_CONFIG_DIMMTYPEDDDR3CAPABLE               },
  { APCB_ID_CONFIG_DIMMTYPELPDDDR3CAPABLE,          APCB_TOKEN_CONFIG_DIMMTYPELPDDDR3CAPABLE             },
  { APCB_ID_CONFIG_ENABLEZQRESET,                   APCB_TOKEN_CONFIG_ENABLEZQRESET                      },
  { APCB_ID_CONFIG_ENABLEBANKGROUPSWAP,             APCB_TOKEN_CONFIG_ENABLEBANKGROUPSWAP                },
  { APCB_ID_CONFIG_ODTSCMDTHROTEN,                  APCB_TOKEN_CONFIG_ODTSCMDTHROTEN                     },
  { APCB_ID_CONFIG_SWCMDTHROTEN,                    APCB_TOKEN_CONFIG_SWCMDTHROTEN                       },
  { APCB_ID_CONFIG_FORCEPWRDOWNTHROTEN,             APCB_TOKEN_CONFIG_FORCEPWRDOWNTHROTEN                },
  { APCB_ID_CONFIG_ODTSCMDTHROTCYC,                 APCB_TOKEN_CONFIG_ODTSCMDTHROTCYC                    },
  { APCB_ID_CONFIG_SWCMDTHROTCYC,                   APCB_TOKEN_CONFIG_SWCMDTHROTCYC                      },
  { APCB_ID_CONFIG_DIMMSENSORCONF,                  APCB_TOKEN_CONFIG_DIMMSENSORCONF                     },
  { APCB_ID_CONFIG_DIMMSENSORUPPER,                 APCB_TOKEN_CONFIG_DIMMSENSORUPPER                    },
  { APCB_ID_CONFIG_DIMMSENSORLOWER,                 APCB_TOKEN_CONFIG_DIMMSENSORLOWER                    },
  { APCB_ID_CONFIG_DIMMSENSORCRITICAL,              APCB_TOKEN_CONFIG_DIMMSENSORCRITICAL                 },
  { APCB_ID_CONFIG_DIMMSENSORRESOLUTION,            APCB_TOKEN_CONFIG_DIMMSENSORRESOLUTION               },
  { APCB_ID_CONFIG_AUTOREFFINEGRANMODE,             APCB_TOKEN_CONFIG_AUTOREFFINEGRANMODE                },
  { APCB_ID_CONFIG_ENABLEMEMPSTATE,                 APCB_TOKEN_CONFIG_ENABLEMEMPSTATE                    },
  { APCB_ID_CONFIG_SOLDERDOWNDRAM,                  APCB_TOKEN_CONFIG_SOLDERDOWNDRAM                     },
  { APCB_ID_CONFIG_DDRROUTEBALANCEDTEE,             APCB_TOKEN_CONFIG_DDRROUTEBALANCEDTEE                },
  { APCB_ID_CONFIG_MEM_MBIST_TEST_ENABLE,           APCB_TOKEN_CONFIG_MEM_MBIST_TEST_ENABLE              },
  { APCB_ID_CONFIG_MEM_MBIST_SUBTEST_TYPE,          APCB_TOKEN_CONFIG_MEM_MBIST_SUBTEST_TYPE             },
  { APCB_ID_CONFIG_MEM_MBIST_AGGRESOR_ON,           APCB_TOKEN_CONFIG_MEM_MBIST_AGGRESOR_ON              },
  { APCB_ID_CONFIG_MEM_MBIST_HALT_ON_ERROR,         APCB_TOKEN_CONFIG_MEM_MBIST_HALT_ON_ERROR            },
  { APCB_ID_CONFIG_MEM_CPU_VREF_RANGE,              APCB_TOKEN_CONFIG_MEM_CPU_VREF_RANGE                 },
  { APCB_ID_CONFIG_MEM_DRAM_VREF_RANGE,             APCB_TOKEN_CONFIG_MEM_DRAM_VREF_RANGE                },
  { APCB_ID_CONFIG_MEM_TSME_ENABLE,                 APCB_TOKEN_CONFIG_MEM_TSME_ENABLE                    },
  { APCB_ID_CONFIG_MEM_NVDIMM_POWER_SOURCE,         APCB_TOKEN_CONFIG_MEM_NVDIMM_POWER_SOURCE            },
  { APCB_ID_CONFIG_MEM_DATA_POISON,                 APCB_TOKEN_CONFIG_MEM_DATA_POISON                    },
  { APCB_ID_CONFIG_MEM_DATA_SCRAMBLE,               APCB_TOKEN_CONFIG_MEM_DATA_SCRAMBLE                  },
  { APCB_ID_CONFIG_BMC_SOCKET_NUMBER,               APCB_TOKEN_CONFIG_BMC_SOCKET_NUMBER                  },
  { APCB_ID_CONFIG_BMC_START_LANE,                  APCB_TOKEN_CONFIG_BMC_START_LANE                     },
  { APCB_ID_CONFIG_BMC_END_LANE,                    APCB_TOKEN_CONFIG_BMC_END_LANE                       },
  { APCB_ID_CONFIG_BMC_DEVICE,                      APCB_TOKEN_CONFIG_BMC_DEVICE                         },
  { APCB_ID_CONFIG_BMC_FUNCTION,                    APCB_TOKEN_CONFIG_BMC_FUNCTION                       },
  { APCB_ID_CONFIG_FCH_CONSOLE_OUT_ENABLE,          APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_ENABLE             },
  { APCB_ID_CONFIG_FCH_CONSOLE_OUT_SERIAL_PORT,     APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_SERIAL_PORT        },
};

UINT16
mTranslateConfigTokenId (
  IN       UINT16             CommonId
  )
{
  UINT16 i;

  for (i = 0; i < sizeof (ConfigTokenPair) / sizeof (TOKEN_PAIR); i++) {
    if (CommonId == ConfigTokenPair[i].ApcbCommonId) {
      return ConfigTokenPair[i].ApcbToken;
    }
  }

  ASSERT (FALSE);

  return 0xFFFF;
}

