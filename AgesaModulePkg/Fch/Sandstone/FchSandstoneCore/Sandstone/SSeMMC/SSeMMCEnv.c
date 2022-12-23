/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch eMMC controller
 *
 * Init USB features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 312667 $   @e \$Date: 2015-02-09 17:39:22 -0800 (Mon, 09 Feb 2015) $
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

//<Embedded_Override_Start>
#include <Library/PcdLib.h>
//<Embedded_Override_End>

#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE FCH_SANDSTONE_SSEMMC_SSEMMCENV_FILECODE

EMMC_CONFIG_BIT_MAP EmmcConfigureTable[] = {
//Emmc Configure Spec
  //version	SDR50 Sup SDR100 Su DDR50 Sup Force 1.8 Force 3.3 Re-Tuning Mode  SDR50-tun WP_TIE CD_TIE SDR50 Drver strength DDR50 Driver strength Slot Type BaseFre down speed
  {{0  ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00,0}},
  {{0x0,0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0x3f,0}},
  {{0x1,0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0xC8,3}},
  {{0x2,1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0xC8,3}},
  {{0x2,0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0xC8,3}},
  {{0x2,1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0xC8,3}},
  {{0x0,0, 0, 0, 1, 0, 0, 0, 3, 1, 1, 1, 0x3f,0}},
  {{0x2,0, 0, 0, 1, 0, 0, 0, 3, 1, 1, 1, 0xC8,3}},
  {{0x2,0, 0, 1, 1, 0, 0, 0, 3, 1, 1, 1, 0xC8,3}},
  {{0x2,1, 1, 0, 1, 0, 0, 0, 3, 1, 1, 1, 0xC8,3}},
  {{0x2,1, 1, 1, 1, 0, 0, 0, 3, 1, 1, 1, 0xC8,3}},
  {{0x2,1, 1, 1, 1, 0, 0, 0, 3, 1, 1, 1, 0x96,2}}
};

/**
 * FchInitEnvEmmc - Config eMMC controller before PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitEnvEmmc (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT32                 EspiBase;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  AGESA_TESTPOINT (TpFchInitEnvEmmc, NULL);

  if ( LocalCfgPtr->Emmc.EmmcEnable ) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGE8, AccessWidth8, ~(UINT32) BIT4, BIT4);
    if ( LocalCfgPtr->Emmc.EmmcBoot ) {
      //Configure all IoMux and clear status here
      RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, 0, 0,StdHeader);
      RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG48), AccessWidth32, 0xFF00, 0,StdHeader);
      //<Embedded_Override_Start>
      RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG7C), AccessWidth32, 0, 0, StdHeader);
     
      if (PcdGetBool (PcdEspiIo80Enable))
      {
        //Need to route 80 IO port to eSPI instead of LPC
        ReadPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGA0, AccessWidth32, &EspiBase, NULL);
        EspiBase &= 0xFFFFFFC0;
        EspiBase += 0x00010000;
        RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT2, BIT2);
      }
      //<Embedded_Override_End>
    }
    RwMem (FCH_EMMC_CFG_REGB0,  AccessWidth32, ~ (UINT32) (0xFF << 24), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Spec_Ver << 24));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 0) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50_Sup << 0));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 1) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr100_Sup << 1));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 2) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Ddr50_Sup << 2));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x01 << 17), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Force18 << 17));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x01 << 18), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Force33 << 18));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.ReTuningMode << 14));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 13), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50Tune << 13));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x03 << 26), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.WpCdTie << 26));
    RwMem (FCH_EMMC_CFG_REGFA,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50DriverStrength << 14));
    RwMem (FCH_EMMC_CFG_REGFE,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Ddr50DriverStrength << 14));
    RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x03 << 30), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.SlotType << 30));
    RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0xFF << 8) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.BaseFre << 8));
    RwMem (FCH_EMMC_CFG_REG116, AccessWidth32, ~ (UINT32) (0x03 << 4) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.DownSpeed << 4));

    LocalCfgPtr->FchRunTime.FchDeviceEnableMap |= BIT28; //Enable eMMC from OS
    if ( LocalCfgPtr->Emmc.EmmcD3Support ) {
      LocalCfgPtr->FchRunTime.FchDeviceD3ColdMap |= BIT28; //Enable eMMC from OS
    }

    if(LocalCfgPtr->Emmc.EmmcBoot){
        LocalCfgPtr->FchRunTime.FchDeviceEnableMap |= BIT20; //Enable eMMC Boot
    }

    LocalCfgPtr->FchRunTime.FchDeviceEnableMap &= ~ (BIT18 + BIT19); //
    LocalCfgPtr->FchRunTime.FchDeviceEnableMap |= (LocalCfgPtr->Emmc.EmmcDriverType & 0x03) << 18; //Load driver type

    if (LocalCfgPtr->Emmc.EmmcEnable <= 5 ) { //SD
      LocalCfgPtr->FchRunTime.FchDeviceEnableMap |= BIT18; // force Load MS driver
    }

    if (!LocalCfgPtr->Emmc.EmmcAdma2Support ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 19) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcAdmaSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 20) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcSdmaSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 22) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcA64bSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 28) , 0);
    }

  }
}


