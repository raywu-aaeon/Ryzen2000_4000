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
#include "PiPei.h"
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/PcdLib.h>
#include <IdsHookId.h>
#include "IdsNvIdRV.h"
#include "IdsNvDefRV.h"
#include "Filecode.h"
#include <smu10_bios_if.h>

#define FILECODE LIBRARY_NBIOIDSHOOKRVLIB_NBIOIDSHOOKRVLIB_FILECODE

/**
 *
 * IDS HOOK for SMU feature enable
 *
 *
 *
 * @param[in] HookId          IDS HOOK ID
 * @param[in] Handle          Handle
 * @param[in] Data            Data
 * @retval    AGESA_STATUS
 *
 **/
IDS_HOOK_STATUS
SmuRVBeforeFeatureEnable (
  HOOK_ID   HookId,
  VOID      *Handle,
  VOID      *Data
  )
{
  UINT32            Value;
  UINT64            IdsNvValue;
  EFI_STATUS        Status;
  PPTable_t  *PPtable;
  Status = EFI_SUCCESS;
  PPtable = (PPTable_t *) Data;
  // System Temperature Tracking
   IDS_NV_READ_SKIP (IDSNVID_CMN_SYSTEM_TEMPERATURE_TRACKING, &IdsNvValue) {
     switch (IdsNvValue) {
     case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_AUTO:
       break;
     case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_DISABLE:
       PPtable->SYSTEM_TEMPERATURE_TRACKING = IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_DISABLE;
       break;
     case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_ENABLE:
       PPtable->SYSTEM_TEMPERATURE_TRACKING = IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_ENABLE;
       break;
     default:
       ASSERT (FALSE);
       break;
    }
  }

  //Disable CORE C-STATES if IBS is enabled
  IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_EN_IBS, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_CMN_CPU_EN_IBS_AUTO:
      break;
    case IDSOPT_CMN_CPU_EN_IBS_ENABLED:
      //SMU Feature Enable/Disable
      Value = PcdGet32 (PcdSmuFeatureControlDefinesExt);
      //Core Cstates Disable
      Value &= (UINT32) (~BIT8);
      PcdSet32 (PcdSmuFeatureControlDefinesExt, Value);
      break;
    case IDSOPT_CMN_CPU_EN_IBS_DISABLED:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }

  //Fan Control
  IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_CTL, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_DBG_FAN_CTL_MANUAL:
      IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_CTL, &IdsNvValue) {
        PcdSet8 (PcdFanTableOverride, (UINT8)IdsNvValue);
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_LOW, &IdsNvValue) {
          PcdSet8 (PcdFanTableTempLow, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_MED, &IdsNvValue) {
          PcdSet8 (PcdFanTableTempMed, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_HIGH, &IdsNvValue) {
          PcdSet8 (PcdFanTableTempHigh, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_CRITICAL, &IdsNvValue) {
          PcdSet8 (PcdFanTableTempCritical, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_T_PWM_LOW, &IdsNvValue) {
          PcdSet8 (PcdFanTablePwmLow, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_MED, &IdsNvValue) {
          PcdSet8 (PcdFanTablePwmMed, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_HIGH, &IdsNvValue) {
          PcdSet8 (PcdFanTablePwmHigh, (UINT8)IdsNvValue);
        }
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_HYST, &IdsNvValue) {
          PcdSet8 (PcdFanTableHysteresis, (UINT8)IdsNvValue);
        }
        //Fan Polarity
        IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_POLARITY, &IdsNvValue) {
        PcdSet8 (PcdFanTablePolarity, (UINT8)IdsNvValue);
        }
      }
      //Pwm Frequency
      IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_FREQ, &IdsNvValue) {
        PcdSet8 (PcdFanTablePwmFreq, (UINT8)IdsNvValue);
      }

      //Force PWM Control
      IDS_NV_READ_SKIP (IDSNVID_DBG_FORCE_PWM_CTL, &IdsNvValue) {
        switch (IdsNvValue) {
        case IDSOPT_DBG_FORCE_PWM_CTL_FORCE:
          PcdSet8 (PcdForceFanPwmEn, (UINT8)IdsNvValue);
          IDS_NV_READ_SKIP (IDSNVID_DBG_FORCE_PWM, &IdsNvValue) {
            PcdSet8 (PcdForceFanPwm, (UINT8)IdsNvValue);
          }
          break;
        case IDSOPT_DBG_FORCE_PWM_CTL_UNFORCE:
          break;
        default:
//          ASSERT (FALSE);
          break;
        }
      }

      break;
    case IDSOPT_DBG_FAN_CTL_AUTO:
      break;
    default:
//      ASSERT (FALSE);
      break;
    }
  }

  return Status;
}

//#define FILECODE LIBRARY_NBIOIDSHOOKRVLIB_NBIOIDSHOOKZPLIB_FILECODE
/**
 *
 * IDS HOOK for NBIO load build options
 *
 *
 *
 * @param[in] HookId          IDS HOOK ID
 * @param[in] Handle          Handle
 * @param[in] Data            Data
 * @retval    AGESA_STATUS
 *
 **/
IDS_HOOK_STATUS
IdsHookNbioLoadBuildOption (
  HOOK_ID HookId,
  VOID *Handle,
  VOID *Data
  )
{
  UINT64     IdsNvValue;

  //IOMMU
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_NB_IOMMU, &IdsNvValue) {
    if (IdsNvValue != IDSOPT_CMN_GNB_NB_IOMMU_AUTO) {
      PcdSetBool (PcdCfgIommuSupport, (BOOLEAN)IdsNvValue);
    }
  }

  //System Configuration
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_SMU_SYSTEM_CONFIG, &IdsNvValue) {
    if (IdsNvValue != IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_AUTO) {
      PcdSet8 (PcdCfgSystemConfiguration, (UINT8)IdsNvValue);
    }
  }

  //GFX Clock Frequency
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_CLOCK_FREQUENCY, &IdsNvValue) {
    if (IdsNvValue != 0) {
      PcdSet16 (PcdMocGfxClockFrequency, (UINT16)IdsNvValue);
    }
  }
  //GFX Core voltage
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_CORE_VID, &IdsNvValue) {
    if (IdsNvValue != 0) {
      PcdSet8 (PcdMocGfxCoreVid, (UINT8)IdsNvValue);
    }
  }

  //Integrated Graphics Controller
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFXI_GPU_CONTROL, &IdsNvValue) {
    if (IdsNvValue == 0) {
      PcdSet8 (PcdCfgIgpuContorl, (UINT8)IdsNvValue);
    }
  }

  return IDS_HOOK_SUCCESS;
}

#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define NBIO_RV_IDS_HOOKS_INT
#else
  #include <Internal/NbioIdsHookRVLibInt.h>
#endif

IDS_HOOK_ELEMENT NbioRVIdsHooks[] = {
  {
    IDS_HOOK_NBIO_SMUV10_INIT_CMN,
    &SmuRVBeforeFeatureEnable
  },
  {
    IDS_HOOK_NBIO_LOAD_BUILD_OPTION,
    &IdsHookNbioLoadBuildOption
  },
  NBIO_RV_IDS_HOOKS_INT
  IDS_HOOKS_END
};

IDS_HOOK_TABLE NbioRVIdsHookTable = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  NbioRVIdsHooks
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &NbioRVIdsHookTable;
  return AGESA_SUCCESS;
}

