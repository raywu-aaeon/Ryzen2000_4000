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
#include <Library/PcdLib.h>
#include <IdsHookId.h>
#include <IdsNvIdZP.h>
#include <IdsNvDefZP.h>

#define FILECODE LIBRARY_NBIOIDSHOOKZPLIB_NBIOIDSHOOKZPLIB_FILECODE

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
SmuZPBeforeFeatureEnable (
  HOOK_ID   HookId,
  VOID      *Handle,
  VOID      *Data
  )
{
  UINT64            IdsNvValue;
  UINT32            Value;
  EFI_STATUS        Status;

  Status = EFI_SUCCESS;

  //Disable CORE C-STATES if IBS is enabled
  IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_EN_IBS, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_CMN_CPU_EN_IBS_AUTO:
      break;
    case IDSOPT_CMN_CPU_EN_IBS_ENABLED:
      //SMU Feature Enable/Disable
      Value = PcdGet32 (PcdSmuFeatureControlDefines);
      //Core Cstates Disable
      Value &= (UINT32) (~BIT8);
      PcdSet32 (PcdSmuFeatureControlDefines, Value);
      break;
    case IDSOPT_CMN_CPU_EN_IBS_DISABLED:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }

  //cTDP Control
  IDS_NV_READ_SKIP (IDSNVID_CMNC_TDP_CTL, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_CMNC_TDP_CTL_MANUAL:
      IDS_NV_READ_SKIP (IDSNVID_CMNC_TDP_LIMIT, &IdsNvValue) {
        PcdSet32 (PcdAmdcTDP, (UINT32)IdsNvValue);
      }
      break;
    case IDSOPT_CMNC_TDP_CTL_AUTO:
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
          ASSERT (FALSE);
          break;
        }
      }

      break;
    case IDSOPT_DBG_FAN_CTL_AUTO:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }

  return Status;
}

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
    if (IdsNvValue) {
      PcdSetBool (PcdCfgIommuSupport, (BOOLEAN)IdsNvValue);
    }
  }

  //NBIO Internal Poison Consumption
  IDS_NV_READ_SKIP (IDSNVID_DBG_POISON_CONSUMPTION, &IdsNvValue) {
    if (IdsNvValue != IDSOPT_DBG_POISON_CONSUMPTION_AUTO) {
      PcdSetBool (PcdAmdNbioPoisonConsumption, (BOOLEAN)IdsNvValue);
    }
  }

  //NBIO RAS Control
  IDS_NV_READ_SKIP (IDSNVID_DBG_RAS_CONTROL, &IdsNvValue) {
    if (IdsNvValue != IDSOPT_DBG_RAS_CONTROL_AUTO) {
      PcdSetBool (PcdAmdNbioRASControl, (BOOLEAN)IdsNvValue);
    }
  }

  //HD Audio Enable
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_HD_AUDIO_EN, &IdsNvValue) {
    if (IdsNvValue != IDSOPT_CMN_GNB_HD_AUDIO_EN_AUTO) {
      PcdSetBool (PcdCfgHdAudioEnable, (BOOLEAN)IdsNvValue);
    }
  }

  //Force PCIe gen speed
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_PC_IE_GEN_SPEED, &IdsNvValue) {
    if (IdsNvValue != 0x0F) {
      PcdSet8 (PcdCfgForcePcieGenSpeed, (UINT8)IdsNvValue);
    }
  }

  //cHTC Control
  IDS_NV_READ_SKIP (IDSNVID_CMN_NBIOC_HTC_CTL, &IdsNvValue) {
    if (IdsNvValue == 1) {
      IDS_NV_READ_SKIP (IDSNVID_CMN_NBIOC_HTC, &IdsNvValue) {
        PcdSet32 (PcdMocTjMax, (UINT32)IdsNvValue);
      }
    }
  }

  //Linux mode
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_LINUX_MODE, &IdsNvValue) {
    if (IdsNvValue != 0xF) {
      if (IdsNvValue == 1) {
        PcdSet8 (PcdDldoPsmMargin, 3);
      }
    }
  }

  // XFR Enhancement
  IDS_NV_READ_SKIP (IDSNVID_CMN_NBIO_XF_R20_CTL, &IdsNvValue) {
    if (IdsNvValue != 0xF) {
      if (IdsNvValue == 0) {
        PcdSet32 (PcdAmdcTDP, 0);
        PcdSet32 (PcdCfgTDC, 0);
        PcdSet32 (PcdCfgEDC, 0);
        PcdSet32 (PcdMocPPTLimit, 0);
        PcdSet32 (PcdMocTDCLimit, 0);
        PcdSet32 (PcdMocEDCLimit, 0);
        PcdSet32 (PcdMocPBOLimitScalar, 100);
      } else if (IdsNvValue == 1) {
        PcdSet32 (PcdMocPPTLimit, PcdGet32 (PcdAmdcTDP) * 1000);
        PcdSet32 (PcdMocTDCLimit, PcdGet32 (PcdCfgTDC) * 1000);
        PcdSet32 (PcdMocEDCLimit, PcdGet32 (PcdCfgEDC) * 1000);
        PcdSet32 (PcdMocPBOLimitScalar, 700);
      }
    }
  }

  return IDS_HOOK_SUCCESS;
}

#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define NBIO_ZP_IDS_HOOKS_INT
#else
  #include <Internal/NbioIdsHookZPLibInt.h>
#endif

IDS_HOOK_ELEMENT NbioZPIdsHooks[] = {
  {
    IDS_HOOK_NBIO_SMUV9_INIT_CMN,
    &SmuZPBeforeFeatureEnable
  },
  {
    IDS_HOOK_NBIO_LOAD_BUILD_OPTION,
    &IdsHookNbioLoadBuildOption
  },
  NBIO_ZP_IDS_HOOKS_INT
  IDS_HOOKS_END
};

IDS_HOOK_TABLE NbioZPIdsHookTable = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  NbioZPIdsHooks
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &NbioZPIdsHookTable;
  return AGESA_SUCCESS;
}

