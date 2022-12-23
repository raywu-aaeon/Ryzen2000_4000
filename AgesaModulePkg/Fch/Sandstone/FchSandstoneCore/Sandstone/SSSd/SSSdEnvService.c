/* $NoKeywords:$ */
/**
 * @file
 *
 * Config SANDSTONE SD
 *
 * Init SD Controller.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
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
*/
#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE PROC_FCH_SANDSTONE_SSSD_SSSDENVSERVICE_FILECODE
/**
 * FchInitEnvSdProgram - Config SD controller before PCI
 * emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitEnvSdProgram (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // SD Configuration
  //
  if (LocalCfgPtr->Sd.SdConfig == SdDisable) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGD3, AccessWidth8, 0xBF, 0x00);
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGE8, AccessWidth8, 0xFE, 0x00);
    ACPIMMIO8 (FCH_AOACx72_SD1_D3_CONTROL) &= ~ AOAC_PWR_ON_DEV;
  } else if (LocalCfgPtr->Sd.SdConfig != SdDump) {
    //ACPIMMIO8 (FCH_PMxE8_SDFlashCntrl) |= FCH_PMxE8_SDFlashCntrl_SdCd2Acpi; //Enable SD_CD0
    //ACPIMMIO8 (FCH_IOMUXx66_SD0_PWR_CTRL_AGPIO102) = 0; //ENH448923
    //ACPIMMIO32(FCH_MISCx68_MEMORY_POWER_SAVING_CONTROL) &= ~ BIT18; //SdBypassMemDsd

    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGD3, AccessWidth8, 0xBF, 0x40);
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGE8, AccessWidth8, 0xFE, BIT0);

    if (LocalCfgPtr->Sd.SdSsid != NULL ) {
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REG2C, AccessWidth32, 0, LocalCfgPtr->Sd.SdSsid, StdHeader);
    }

    RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA4, AccessWidth32, 0x3FFFFFFF, ((UINT32) (LocalCfgPtr->Sd.SdSlotType) << 30), StdHeader);

    if ( LocalCfgPtr->Sd.SdConfig == SdVer2) {
// SD 2.0
//The following programming sequence sets up SD controller to operate in SD 2.0 mode. (UBTS538428).
//A. Program D14F7xA4[BaseFreq]= 32h.
//B. Program D14F7xA8=[Ddr50Sup]=0.
//C. Program D14F7xA8=[Sdr100Sup]=0.
//D. Program D14F7xA8=[Sdr50Sup]=0.
//E. Program D14F7xB0=[HostVersionSel]=1h.
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA4, AccessWidth32, ~ (UINT32) (0xFF << 8), (UINT32) (0x32 << 8), StdHeader);
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA8, AccessWidth32, ~ (UINT32) (0x01 << 2), (UINT32) (0x00 << 2), StdHeader);
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA8, AccessWidth32, ~ (UINT32) (0x01 << 1), (UINT32) (0x00 << 1), StdHeader);
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA8, AccessWidth32, ~ (UINT32) (0x01 << 0), (UINT32) (0x00 << 0), StdHeader);
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGB0, AccessWidth32, ~ (UINT32) (0xFF << 24), (UINT32) (0x01 << 24), StdHeader);
    } else {
      //  no SD3.0 POR on TS
    }
    if ( LocalCfgPtr->Sd.SdForce18 ) {
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGD0, AccessWidth32, ~ ((UINT32) (0x01 << 17)), ((UINT32) (0x01) << 17), StdHeader);
    }

    if (LocalCfgPtr->Sd.SdDbgConfig == 1) {
      //DMA clear BIT19,BIT20
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA4, AccessWidth32, ~ (UINT32) (BIT19 + BIT20), 0, StdHeader);
    }

    if (LocalCfgPtr->Sd.SdDbgConfig == 2) {
      //PIO clear BIT19,BIT20,BIT22
      RwPci ((SANDSTONE_SD_BUS_DEV_FUN << 16) + SD_PCI_REGA4, AccessWidth32, ~ (UINT32) (BIT19 + BIT20 + BIT22), 0, StdHeader);
    }
  }
}

