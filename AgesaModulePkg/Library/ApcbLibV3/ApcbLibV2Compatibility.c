/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB Lib V2.0 Compatibility
 *
 * Compatibility support for APCB 2.0 Services
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
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

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Porting.h>
#include <ApcbCommon.h>
#include <Addendum/Apcb/Inc/SSP/ApcbV3Priority.h>
#include <Addendum/Apcb/Inc/SSP/ApcbV3TokenUid.h>
#include "CoreApcbInterface.h"
#include <Library/ApcbLibV3.h>
#include <Library/IdsLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_APCBLIBV3_APCBLIBV2COMPATIBILITY_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

typedef struct _MAP_TOKENS_V2_TO_V3 {
  UINT16        V2TokenId;
  UINT32        Uid;
} MAP_TOKENS_V2_TO_V3;

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          G L O B A L        V A L U E S
 *----------------------------------------------------------------------------------------
 */

CONST MAP_TOKENS_V2_TO_V3 MapTokensV2ToV3Bool[] = {
  {APCB_ID_CONFIG_DF_MEM_CLEAR, APCB_TOKEN_UID_DF_MEM_CLEAR},
  {APCB_ID_CONFIG_MEMHOLEREMAPPING, APCB_TOKEN_UID_MEMHOLEREMAPPING},
  {APCB_ID_CONFIG_LIMITMEMORYTOBELOW1TB, APCB_TOKEN_UID_LIMITMEMORYTOBELOW1TB},
  {APCB_ID_CONFIG_ENABLECHIPSELECTINTLV, APCB_TOKEN_UID_ENABLECHIPSELECTINTLV},
  {APCB_ID_CONFIG_ENABLEECCFEATURE, APCB_TOKEN_UID_ENABLEECCFEATURE},
  {APCB_ID_CONFIG_ENABLEPOWERDOWN, APCB_TOKEN_UID_ENABLEPOWERDOWN},
  {APCB_ID_CONFIG_ENABLEPARITY, APCB_TOKEN_UID_ENABLEPARITY},
  {APCB_ID_CONFIG_ENABLEBANKSWIZZLE, APCB_TOKEN_UID_ENABLEBANKSWIZZLE},
  {APCB_ID_CONFIG_ENABLEMEMCLR, APCB_TOKEN_UID_ENABLEMEMCLR},
  {APCB_ID_CONFIG_MEMRESTORECTL, APCB_TOKEN_UID_MEMRESTORECTL},
  {APCB_ID_CONFIG_ISCAPSULEMODE, APCB_TOKEN_UID_ISCAPSULEMODE},
  {APCB_ID_CONFIG_AMPENABLE, APCB_TOKEN_UID_AMPENABLE},
  {APCB_ID_CONFIG_DRAMDOUBLEREFRESHRATE, APCB_TOKEN_UID_DRAMDOUBLEREFRESHRATE},
  {APCB_ID_CONFIG_ECCREDIRECTION, APCB_TOKEN_UID_ECCREDIRECTION},
  {APCB_ID_CONFIG_ECCSYNCFLOOD, APCB_TOKEN_UID_ECCSYNCFLOOD},
  {APCB_ID_CONFIG_DQSTRAININGCONTROL, APCB_TOKEN_UID_DQSTRAININGCONTROL},
  {APCB_ID_CONFIG_UMAABOVE4G, APCB_TOKEN_UID_UMAABOVE4G},
  {APCB_ID_CONFIG_MEMORYALLCLOCKSON, APCB_TOKEN_UID_MEMORYALLCLOCKSON},
  {APCB_ID_CONFIG_IGNORESPDCHECKSUM, APCB_TOKEN_UID_IGNORESPDCHECKSUM},
  {APCB_ID_CONFIG_MEMORYMODEUNGANGED, APCB_TOKEN_UID_MEMORYMODEUNGANGED},
  {APCB_ID_CONFIG_MEMORYQUADRANKCAPABLE, APCB_TOKEN_UID_MEMORYQUADRANKCAPABLE},
  {APCB_ID_CONFIG_MEMORYRDIMMCAPABLE, APCB_TOKEN_UID_MEMORYRDIMMCAPABLE},
  {APCB_ID_CONFIG_MEMORYLRDIMMCAPABLE, APCB_TOKEN_UID_MEMORYLRDIMMCAPABLE},
  {APCB_ID_CONFIG_MEMORYUDIMMCAPABLE, APCB_TOKEN_UID_MEMORYUDIMMCAPABLE},
  {APCB_ID_CONFIG_MEMORYSODIMMCAPABLE, APCB_TOKEN_UID_MEMORYSODIMMCAPABLE},
  {APCB_ID_CONFIG_DRAMDOUBLEREFRESHRATEEN, APCB_TOKEN_UID_DRAMDOUBLEREFRESHRATEEN},
  {APCB_ID_CONFIG_DIMMTYPEDDDR4CAPABLE, APCB_TOKEN_UID_DIMMTYPEDDDR4CAPABLE},
  {APCB_ID_CONFIG_DIMMTYPEDDDR3CAPABLE, APCB_TOKEN_UID_DIMMTYPEDDDR3CAPABLE},
  {APCB_ID_CONFIG_DIMMTYPELPDDDR3CAPABLE, APCB_TOKEN_UID_DIMMTYPELPDDDR3CAPABLE},
  {APCB_ID_CONFIG_ENABLEZQRESET, APCB_TOKEN_UID_ENABLEZQRESET},
  {APCB_ID_CONFIG_ENABLEBANKGROUPSWAP, APCB_TOKEN_UID_ENABLEBANKGROUPSWAP},
  {APCB_ID_CONFIG_ODTSCMDTHROTEN, APCB_TOKEN_UID_ODTSCMDTHROTEN},
  {APCB_ID_CONFIG_SWCMDTHROTEN, APCB_TOKEN_UID_SWCMDTHROTEN},
  {APCB_ID_CONFIG_FORCEPWRDOWNTHROTEN, APCB_TOKEN_UID_FORCEPWRDOWNTHROTEN},
  {APCB_ID_CONFIG_ENABLEMEMPSTATE, APCB_TOKEN_UID_ENABLEMEMPSTATE},
  {APCB_ID_CONFIG_DDRROUTEBALANCEDTEE, APCB_TOKEN_UID_DDRROUTEBALANCEDTEE},
  {APCB_ID_CONFIG_MEM_MBIST_TEST_ENABLE, APCB_TOKEN_UID_MEM_MBIST_TEST_ENABLE},
  {APCB_ID_CONFIG_MEM_MBIST_HALT_ON_ERROR, APCB_TOKEN_UID_MEM_MBIST_HALT_ON_ERROR},
  {APCB_ID_CONFIG_MEM_TSME_ENABLE, APCB_TOKEN_UID_MEM_TSME_ENABLE},
  {APCB_ID_CONFIG_MEM_DATA_POISON, APCB_TOKEN_UID_MEM_DATA_POISON},
  {APCB_ID_CONFIG_MEM_DATA_SCRAMBLE, APCB_TOKEN_UID_MEM_DATA_SCRAMBLE},
};

CONST MAP_TOKENS_V2_TO_V3 MapTokensV2ToV3Uint8[] = {
  {APCB_ID_CONFIG_DF_GMI_ENCRYPT, APCB_TOKEN_UID_DF_GMI_ENCRYPT},
  {APCB_ID_CONFIG_DF_XGMI_ENCRYPT, APCB_TOKEN_UID_DF_XGMI_ENCRYPT},
  {APCB_ID_CONFIG_DF_SAVE_RESTORE_MEM_ENCRYPT, APCB_TOKEN_UID_DF_SAVE_RESTORE_MEM_ENCRYPT},
  {APCB_ID_CONFIG_DF_SYS_STORAGE_AT_TOP_OF_MEM, APCB_TOKEN_UID_DF_SYS_STORAGE_AT_TOP_OF_MEM},
  {APCB_ID_CONFIG_DF_PROBE_FILTER_ENABLE, APCB_TOKEN_UID_DF_PROBE_FILTER}, // Was APCB_TOKEN_UID_DF_PROBE_FILTER_ENABLE
  {APCB_ID_CONFIG_DF_BOTTOMIO, APCB_TOKEN_UID_DF_BOTTOMIO},
  {APCB_ID_CONFIG_DF_MEM_INTERLEAVING, APCB_TOKEN_UID_DF_MEM_INTERLEAVING},
  {APCB_ID_CONFIG_DF_DRAM_INTERLEAVE_SIZE, APCB_TOKEN_UID_DF_MEM_INTERLEAVING_SIZE}, // Was APCB_TOKEN_UID_DF_DRAM_INTERLEAVE_SIZE
  {APCB_ID_CONFIG_DF_ENABLE_CHAN_INTLV_HASH, APCB_TOKEN_UID_DF_ENABLE_CHAN_INTLV_HASH},
  {APCB_ID_CONFIG_DF3_XGMI2_LINK_CFG, APCB_TOKEN_UID_DF3_XGMI2_LINK_CFG},
  {APCB_ID_CONFIG_UMAMODE, APCB_TOKEN_UID_UMAMODE},
  {APCB_ID_CONFIG_FORCETRAINMODE, APCB_TOKEN_UID_FORCETRAINMODE},
  {APCB_ID_CONFIG_DIMMTYPEUSEDINMIXEDCONFIG, APCB_TOKEN_UID_DIMMTYPEUSEDINMIXEDCONFIG},
  {APCB_ID_CONFIG_PMUTRAINMODE, APCB_TOKEN_UID_PMUTRAINMODE},
  {APCB_ID_CONFIG_ODTSCMDTHROTCYC, APCB_TOKEN_UID_ODTSCMDTHROTCYC},
  {APCB_ID_CONFIG_SWCMDTHROTCYC, APCB_TOKEN_UID_SWCMDTHROTCYC},
  {APCB_ID_CONFIG_DIMMSENSORRESOLUTION, APCB_TOKEN_UID_DIMMSENSORRESOLUTION},
  {APCB_ID_CONFIG_AUTOREFFINEGRANMODE, APCB_TOKEN_UID_AUTOREFFINEGRANMODE},
  {APCB_ID_CONFIG_SOLDERDOWNDRAM, APCB_TOKEN_UID_SOLDERDOWNDRAM},
  {APCB_ID_CONFIG_MEM_MBIST_SUBTEST_TYPE, APCB_TOKEN_UID_MEM_MBIST_SUBTEST_TYPE},
  {APCB_ID_CONFIG_MEM_MBIST_AGGRESOR_ON, APCB_TOKEN_UID_MEM_MBIST_AGGRESOR_ON},
  {APCB_ID_CONFIG_MEM_NVDIMM_POWER_SOURCE, APCB_TOKEN_UID_MEM_NVDIMM_POWER_SOURCE},
  {APCB_ID_CONFIG_BMC_SOCKET_NUMBER, APCB_TOKEN_UID_BMC_SOCKET_NUMBER},
  {APCB_ID_CONFIG_BMC_START_LANE, APCB_TOKEN_UID_BMC_START_LANE},
  {APCB_ID_CONFIG_BMC_END_LANE, APCB_TOKEN_UID_BMC_END_LANE},
  {APCB_ID_CONFIG_BMC_DEVICE, APCB_TOKEN_UID_BMC_DEVICE},
  {APCB_ID_CONFIG_BMC_FUNCTION, APCB_TOKEN_UID_BMC_FUNCTION},
  {APCB_ID_CONFIG_FCH_CONSOLE_OUT_ENABLE, APCB_TOKEN_UID_FCH_CONSOLE_OUT_ENABLE},
  {APCB_ID_CONFIG_FCH_CONSOLE_OUT_SERIAL_PORT, APCB_TOKEN_UID_FCH_CONSOLE_OUT_SERIAL_PORT},
};

CONST MAP_TOKENS_V2_TO_V3 MapTokensV2ToV3Uint16[] = {
  {APCB_ID_CONFIG_SCRUBDRAMRATE, APCB_TOKEN_UID_SCRUBDRAMRATE},
  {APCB_ID_CONFIG_SCRUBL2RATE, APCB_TOKEN_UID_SCRUBL2RATE},
  {APCB_ID_CONFIG_SCRUBL3RATE, APCB_TOKEN_UID_SCRUBL3RATE},
  {APCB_ID_CONFIG_SCRUBICRATE, APCB_TOKEN_UID_SCRUBICRATE},
  {APCB_ID_CONFIG_SCRUBDCRATE, APCB_TOKEN_UID_SCRUBDCRATE},
  {APCB_ID_CONFIG_ECCSYMBOLSIZE, APCB_TOKEN_UID_ECCSYMBOLSIZE},
  {APCB_ID_CONFIG_DIMMSENSORCONF, APCB_TOKEN_UID_DIMMSENSORCONF},
  {APCB_ID_CONFIG_DIMMSENSORUPPER, APCB_TOKEN_UID_DIMMSENSORUPPER},
  {APCB_ID_CONFIG_DIMMSENSORLOWER, APCB_TOKEN_UID_DIMMSENSORLOWER},
  {APCB_ID_CONFIG_DIMMSENSORCRITICAL, APCB_TOKEN_UID_DIMMSENSORCRITICAL},
  {APCB_ID_CONFIG_MEM_CPU_VREF_RANGE, APCB_TOKEN_UID_MEM_CPU_VREF_RANGE},
  {APCB_ID_CONFIG_MEM_DRAM_VREF_RANGE, APCB_TOKEN_UID_MEM_DRAM_VREF_RANGE},
};

CONST MAP_TOKENS_V2_TO_V3 MapTokensV2ToV3Uint32[] = {
  {APCB_ID_CONFIG_CCX_MIN_SEV_ASID, APCB_TOKEN_UID_CCX_MIN_SEV_ASID},
  {APCB_ID_CONFIG_DF_PCI_MMIO_SIZE, APCB_TOKEN_UID_DF_PCI_MMIO_SIZE},
  {APCB_ID_CONFIG_DF_CAKE_CRC_THRESH_PERF_BOUNDS, APCB_TOKEN_UID_DF_CAKE_CRC_THRESH_PERF_BOUNDS},
  {APCB_ID_CONFIG_USERTIMINGMODE, APCB_TOKEN_UID_USERTIMINGMODE},
  {APCB_ID_CONFIG_MEMCLOCKVALUE, APCB_TOKEN_UID_MEMCLOCKVALUE},
  {APCB_ID_CONFIG_UMASIZE, APCB_TOKEN_UID_UMASIZE},
  {APCB_ID_CONFIG_UMAALIGNMENT, APCB_TOKEN_UID_UMAALIGNMENT},
  {APCB_ID_CONFIG_MEMORYBUSFREQUENCYLIMIT, APCB_TOKEN_UID_MEMORYBUSFREQUENCYLIMIT},
  {APCB_ID_CONFIG_POWERDOWNMODE, APCB_TOKEN_UID_POWERDOWNMODE},
};

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the value associated with an APCB V2 Common token
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CONFIG_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval            TRUE            - The value is successfully retrieved
 *                     FALSE           - The token is not found
 *
 */
BOOLEAN
ApcbV2GetConfigToken (
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  UINT8         i;
  UINT8         CurrentPriorityLevel;
  UINT8         StartingPriorityLevel;
  UINT8         EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  ASSERT (NULL != SizeInByte);
  ASSERT (NULL != Value);

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);

    for (i = 0; i < sizeof (MapTokensV2ToV3Bool) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
      if (MapTokensV2ToV3Bool[i].V2TokenId == TokenId) {
        *SizeInByte = 1;
        if (ApcbGetBool (MapTokensV2ToV3Bool[i].Uid, (BOOLEAN *)Value)) {
          return TRUE;
        } else {
          break;
        }
      }
    }

    for (i = 0; i < sizeof (MapTokensV2ToV3Uint8) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
      if (MapTokensV2ToV3Uint8[i].V2TokenId == TokenId) {
        *SizeInByte = 1;
        if (ApcbGet8 (MapTokensV2ToV3Uint8[i].Uid, (UINT8 *)Value)) {
          return TRUE;
        } else {
          break;
        }
      }
    }

    for (i = 0; i < sizeof (MapTokensV2ToV3Uint16) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
      if (MapTokensV2ToV3Uint16[i].V2TokenId == TokenId) {
        *SizeInByte = 2;
        if (ApcbGet16 (MapTokensV2ToV3Uint16[i].Uid, (UINT16 *)Value)) {
          return TRUE;
        } else {
          break;
        }
      }
    }

    for (i = 0; i < sizeof (MapTokensV2ToV3Uint32) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
      if (MapTokensV2ToV3Uint32[i].V2TokenId == TokenId) {
        *SizeInByte = 4;
        if (ApcbGet32 (MapTokensV2ToV3Uint32[i].Uid, (UINT32 *)Value)) {
          return TRUE;
        } else {
          break;
        }
      }
    }
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB V2 Compatibility] Token 0x%04x not found", TokenId);
  return FALSE;
}


/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets the value associated with an APCB V2 Common token
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CONFIG_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   The size of the value to be set
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval            TRUE            - The value is successfully set
 *                     FALSE           - The token is not found
 *
 */
BOOLEAN
ApcbV2SetConfigToken (
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  UINT8         i;

  ASSERT (NULL != SizeInByte);
  ASSERT (NULL != Value);

  ApcbSetPurpose (APCB_TYPE_PURPOSE_NORMAL);

  for (i = 0; i < sizeof (MapTokensV2ToV3Bool) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
    if (MapTokensV2ToV3Bool[i].V2TokenId == TokenId) {
      if (ApcbSetBool (MapTokensV2ToV3Bool[i].Uid, (BOOLEAN)*Value)) {
        return TRUE;
      } else {
        break;
      }
    }
  }

  for (i = 0; i < sizeof (MapTokensV2ToV3Uint8) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
    if (MapTokensV2ToV3Uint8[i].V2TokenId == TokenId) {
      if (ApcbSet8 (MapTokensV2ToV3Uint8[i].Uid, (UINT8)*Value)) {
        return TRUE;
      } else {
        break;
      }
    }
  }

  for (i = 0; i < sizeof (MapTokensV2ToV3Uint16) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
    if (MapTokensV2ToV3Uint16[i].V2TokenId == TokenId) {
      if (ApcbSet16 (MapTokensV2ToV3Uint16[i].Uid, (UINT16)*Value)) {
        return TRUE;
      } else {
        break;
      }
    }
  }

  for (i = 0; i < sizeof (MapTokensV2ToV3Uint32) / sizeof (MAP_TOKENS_V2_TO_V3); i ++) {
    if (MapTokensV2ToV3Uint32[i].V2TokenId == TokenId) {
      if (ApcbSet32 (MapTokensV2ToV3Uint32[i].Uid, (UINT32)*Value)) {
        return TRUE;
      } else {
        break;
      }
    }
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("[APCB V2 Compatibility] Token 0x%04x not found", TokenId);
  return FALSE;
}

