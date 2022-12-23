/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch xGbE controller
 *
 * Init USB features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 312516 $   @e \$Date: 2015-02-06 17:37:45 -0800 (Fri, 06 Feb 2015) $
 *
 */
/*;********************************************************************************
;
; Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
;
; AMD is granting you permission to use this software and documentation (if
; any) (collectively, the "Materials") pursuant to the terms and conditions of
; the Software License Agreement included with the Materials.  If you do not
; have a copy of the Software License Agreement, contact your AMD
; representative for a copy.
;
; You agree that you will not reverse engineer or decompile the Materials, in
; whole or in part, except as allowed by applicable law.
;
; WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
; ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
; INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
; MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
; CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
; OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
; exclusion of implied warranties, so the above exclusion may not apply to
; You.
;
; LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
; NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
; INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
; THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
; liability to You for all damages, losses, and causes of action (whether in
; contract, tort (including negligence) or otherwise) exceed the amount of
; $100 USD. You agree to defend, indemnify and hold harmless AMD and its
; licensors, and any of their directors, officers, employees, affiliates or
; agents from and against any and all loss, damage, liability and other
; expenses (including reasonable attorneys' fees), resulting from Your use of
; the Materials or violation of the terms and conditions of this Agreement.
;
; U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
; "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
; subject to the restrictions as set forth in FAR 52.227-14 and
; DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
; Government constitutes acknowledgment of AMD's proprietary rights in them.
;
; EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
; stated in the Software License Agreement.
;******************************************************************************
;*/
#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE FCH_SANDSTONE_FCHSANDSTONECORE_SANDSTONE_SSXGBE_SSXGBEENV_FILECODE


/**
 * FchInitEnvXGbe - Config xGbE controller before PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitEnvXGbe (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT8                  Port;
  UINT32                 SystemPort;
  UINT32                 XgbeNbifStrap0;
  UINT32                 XgbeNbifStrap1;
  FCH_XGBE_PORT          *FchXgbePort;
  FCH_XGBE_MAC           *FchXgbePortMac;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  FchXgbePort = &LocalCfgPtr->Xgbe.Port[0];
  FchXgbePortMac = &LocalCfgPtr->Xgbe.Mac[0];

  AGESA_TESTPOINT (TpFchInitEnvXgbe, NULL);
  //PLAT-17946
  FchSmnRead (0, FCH_SS_SMN_XGBE0_NBIF_STRAP0, &XgbeNbifStrap0, NULL);
  FchSmnRead (0, FCH_SS_SMN_XGBE0_NBIF_STRAP0 + 0x200, &XgbeNbifStrap1, NULL);
  if ((((XgbeNbifStrap0 & BIT28) == 0) && ((XgbeNbifStrap1 & BIT28) == 0))  || ((LocalCfgPtr->Xgbe.Port[0].XgbePortConfig == FALSE) && (LocalCfgPtr->Xgbe.Port[1].XgbePortConfig == FALSE))) {
  //  FchSmnRW (0, FCH_NBIFSHUBMM0x00011000_SYSHUB_DS_CTRL_SHUBCLK, ~ (UINT32) (FCH_DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE), FCH_DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE, NULL);  //Disable XGbe to pass Os install
  //  FchSmnRW (0, 0x4EC20, 0xFFFF0000, 0x0101, NULL);  //
  }

  for (Port = 0; Port < 4; Port++) {
    //
    // Check if GMAC is enabled
    //
    //PLAT-16038
    if (FchXgbePort->XgbePortConfig == FALSE) {
     FchSmnRW (0, FCH_SS_RCC_DEV1_EPF1_STRAP0 + Port * 0x200, ~ (UINT32) (BIT28), 0, NULL);  //Disable XGbe to pass Os install
    }

    FchSmnRead (0, FCH_SS_SMN_XGBE0_NBIF_STRAP0 + Port * 0x200, &XgbeNbifStrap0, NULL);

    if (XgbeNbifStrap0 & BIT28) {
      SystemPort = LocalCfgPtr->Xgbe.MaxPortNum;
      LocalCfgPtr->Xgbe.MaxPortNum++;
      if (FchXgbePort->XgbePortConfig) {
        FchSsXgbePortPlatformConfig (0, Port, SystemPort, FchXgbePort);
        FchSsXgbePortMacAddress (0, Port, FchXgbePortMac);
        FchSsXgbePortPtpInit (0, Port, FchXgbePort);
      }
    } else {
      FchSsXgbePortClockGate (0, Port);
    }
    FchXgbePort++;
    FchXgbePortMac++;
  }

  FchSsXgbePadEnable (0, &LocalCfgPtr->Xgbe);
}

