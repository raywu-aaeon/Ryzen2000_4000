/*****************************************************************************
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

#include "CBSFchFunDXE_RV.h"

#ifdef AMD_CBS_FCH_RV
DXE_CBS_FUNCTION_STRUCT CBS_FUNCTABLE_DECLARE(FchDxeFunTable,_RV)[] =
{
  {
    F17_RV_RAW_ID,
    AMD_RESERVE_ALL,
    CBS_FUNC_DECLARE(FchInitEnvParams,_RV),
    IDS_HOOK_FCH_INIT_ENV
  },

  {
    F17_RV2_RAW_ID,
    AMD_RESERVE_ALL,
    CBS_FUNC_DECLARE(FchInitEnvParams,_RV),
    IDS_HOOK_FCH_INIT_ENV
  },

  {
    F17_PIC_RAW_ID,
    AMD_RESERVE_ALL,
    CBS_FUNC_DECLARE(FchInitEnvParams,_RV),
    IDS_HOOK_FCH_INIT_ENV
  },

  {
    0,        // F17_RV_RAW_ID,
    0,        // AMD_RESERVE_ALL,
    NULL,     // CBS_FUNC_DECLARE(FchFunc_Init_DXE,_RV),
    0         // CBS_CALLOUT_ID
  }
};

VOID
CBS_FUNC_DECLARE(FchInitEnvParams,_RV) (
  IN EFI_BOOT_SERVICES        *BootServices,
  IN OUT  VOID                *DataParams,
  IN AMD_SYSTEM_CONFIGURATION *SystemConfiguration
  )
{
  UINT32                    PcdSata32;
  CBS_IDS_HOOK_PARAMS       *CbsIdsHookParams;
  FCH_DATA_BLOCK            *FchParams;

  CbsIdsHookParams = (CBS_IDS_HOOK_PARAMS *)DataParams;
  FchParams = (FCH_DATA_BLOCK *)(CbsIdsHookParams->Data);

  // I2C, Uart, ESPI
  PcdSata32 = PcdGet32 (FchRTDeviceEnableMap);

  if (SystemConfiguration->CbsCmnFchI2C0Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C0Config) {
	  PcdSata32 |= BIT5;
	} else {
	  PcdSata32 &= ~ BIT5;
	}
  }
  if (SystemConfiguration->CbsCmnFchI2C1Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C1Config) {
	  PcdSata32 |= BIT6;
	} else {
	  PcdSata32 &= ~ BIT6;
	}
  }
  if (SystemConfiguration->CbsCmnFchI2C2Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C2Config) {
	  PcdSata32 |= BIT7;
	} else {
	  PcdSata32 &= ~ BIT7;
	}
  }
  if (SystemConfiguration->CbsCmnFchI2C3Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C3Config) {
	  PcdSata32 |= BIT8;
	} else {
	  PcdSata32 &= ~ BIT8;
	}
  }
  if (SystemConfiguration->CbsCmnFchI2C4Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C4Config) {
	  PcdSata32 |= BIT9;
	} else {
	  PcdSata32 &= ~ BIT9;
	}
  }
  if (SystemConfiguration->CbsCmnFchI2C5Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchI2C5Config) {
	  PcdSata32 |= BIT10;
	} else {
	  PcdSata32 &= ~ BIT10;
	}
  }
  if (SystemConfiguration->CbsCmnFchUart0Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchUart0Config) {
	  PcdSata32 |= BIT11;
	} else {
	  PcdSata32 &= ~ BIT11;
	}
  }
  if (SystemConfiguration->CbsCmnFchUart1Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchUart1Config) {
	  PcdSata32 |= BIT12;
	} else {
	  PcdSata32 &= ~ BIT12;
	}
  }
  if (SystemConfiguration->CbsCmnFchUart2Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchUart2Config) {
	  PcdSata32 |= BIT16;
	} else {
	  PcdSata32 &= ~ BIT16;
	}
  }
  if (SystemConfiguration->CbsCmnFchUart3Config != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchUart3Config) {
	  PcdSata32 |= BIT26;
	} else {
	  PcdSata32 &= ~ BIT26;
	}
  }

  if (SystemConfiguration->CbsCmnFchEspiConfig != 0xf) { // Auto
	if (SystemConfiguration->CbsCmnFchEspiConfig) {
	  PcdSata32 |= BIT27;
	} else {
	  PcdSata32 &= ~ BIT27;
	}
  }
  PcdSet32 (FchRTDeviceEnableMap, PcdSata32);
}
#endif

