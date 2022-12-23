/* $NoKeywords:$ */
/**
 * @file
 *
 * Gnb Nbio Base ZP Hob GUID definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Gnb
 * @e \$Revision: 309090 $   @e \$Date: 2015-09-09 04:30:05 +0800 (Wed, 9 Sep 2015) $
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
 **/
#ifndef _GNB_NBIO_BASE_ZP_HOB_INFO_H_
#define _GNB_NBIO_BASE_ZP_HOB_INFO_H_

#define _GNB_NBIO_BASE_ZP_HOB_INFO_GUID \
{ \
  0xce3e2c94, 0x82e2, 0x4429, 0xba, 0x69, 0xcc, 0xf6, 0xb9, 0xba, 0x1, 0x4c \
}
extern EFI_GUID gGnbNbioBaseZPHobInfoGuid;

#pragma pack (push, 1)

/// The Build time options configuration for common family-specific options
typedef struct {
  BOOLEAN               CfgScsSupport;                      ///< Scs support
  UINT8                 CfgUmaSteering;                     ///< Configurable UMA Steering
  UINT8                 GmcPowerGating;                     ///< Control GMC power gating
  BOOLEAN               CfgGmcClockGating;                  ///< Control GMC clock power gate
  BOOLEAN               CfgOrbDynWakeEnable;                ///< Enables ORB Dynamic wake up
  BOOLEAN               CfgOrbClockGatingEnable;            ///< Control ORB clock gating
  BOOLEAN               CfgIommuL1ClockGatingEnable;        ///< Control IOMMU L1 clock gating
  BOOLEAN               CfgIommuL2ClockGatingEnable;        ///< Control IOMMU L2 clock gating
  BOOLEAN               CfgIocLclkClockGatingEnable;        ///< Control IOC LCLK clock gating
  BOOLEAN               CfgBapmSupport;                     ///< BAPM support
  BOOLEAN               CfgDcTdpEnable;                     ///< Control dcTDP
  UINT8                 CfgGnbNumDisplayStreamPipes;        ///< Number of display stream pipes
  BOOLEAN               CfgSmuMessageEnable;                ///< Control SMU message service
} GNB_BUILD_OPTIONS_COMMON_HOB;

/// SMU Features Bit Map
typedef union {
  struct {                                                              ///<
    UINT32                                                     BAPM:1 ; ///<
    UINT32                                          POWER_ESTIMATOR:1 ; ///<
    UINT32                                       THERMAL_CONTROLLER:1 ; ///<
    UINT32                                             TDC_LIMITING:1 ; ///<
    UINT32                                         PKG_PWR_LIMITING:1 ; ///<
    UINT32                                                 LCLK_DPM:1 ; ///<
    UINT32                                       VOLTAGE_CONTROLLER:1 ; ///<
    UINT32                                                    GEAPM:1 ; ///<
    UINT32                                                      BBB:1 ; ///<
    UINT32                                                      IBS:1 ; ///<
    UINT32                                           PSTATE_ARBITER:1 ; ///<
    UINT32                                                   NB_DPM:1 ; ///<
    UINT32                                          LCLK_DEEP_SLEEP:1 ; ///<
    UINT32                                                      ULV:1 ; ///<
    UINT32                                                GFX_CU_PG:1 ; ///<
    UINT32                                                     AVFS:1 ; ///<
    UINT32                                                  UVD_DPM:1 ; ///<
    UINT32                                                     CHTC:1 ; ///<
    UINT32                                                  ACP_DPM:1 ; ///<
    UINT32                                                 SCLK_DPM:1 ; ///<
    UINT32                                           PRE_FETCH_DATA:1 ; ///<
    UINT32                                               DFS_BYPASS:1 ; ///<
    UINT32                                                  VCE_DPM:1 ; ///<
    UINT32                                                   VDDGFX:1 ; ///<
    UINT32                                                    LEAPM:1 ; ///<
    UINT32                                               CONN_STDBY:1 ; ///<
    UINT32                                           PORT80_MONITOR:1 ; ///<
    UINT32                                               PSPCLK_DPM:1 ; ///<
    UINT32                                                    STAPM:1 ; ///<
    UINT32                                              DETERMINISM:1 ; ///<
    UINT32                                            CPU_STRETCHER:1 ; ///<
    UINT32                                           SCLK_STRETCHER:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} SMU_SERVICE_ENABLEMENT_BITMAP_ZP_HOB;

/// The Build time options configuration for ZP-specific options
typedef struct _GNB_BUILD_OPTIONS_ZP_DATA_HOB {
  EFI_HOB_GUID_TYPE                            EfiHobGuidType;                     ///< GUID Hob type structure
  SMU_SERVICE_ENABLEMENT_BITMAP_ZP_HOB         CfgSMUServiceEnablementBitMap;      ///< Bit map for SMU service enablement (1 means the service is enabled)
  BOOLEAN                                      CfgChubClockGating;                 ///< CHUB Clock Gating
  BOOLEAN                                      CfgAcpClockGating;                  ///< ACP Clock Gating
  BOOLEAN                                      CfgAxgDisable;                      ///< Config the AXG enable/disable(include SPG and ACGAZ)
  UINT8                                        CfgPcieHwInitPwerGating;            ///< PCIE HW initiated power gating
  BOOLEAN                                      CfgAriSupport;                      ///< PCIe ARI support enable
  BOOLEAN                                      CfgSpgClockGatingEnable;            ///< Control SPG clock gating
  BOOLEAN                                      CfgAcgAzClockGatingEnable;          ///< Control ACG AZ clock gating
  BOOLEAN                                      CfgIommuL1MemPowerGating;           ///< Control IOMMU L1 memory power gating
  BOOLEAN                                      CfgIommuL2MemPowerGating;           ///< Control IOMMU L2A L2B memory power gating
  UINT8                                        CfgOrbTxMemPowerGating;             ///< Control ORB TX memory power gating
  UINT8                                        CfgOrbRxMemPowerGating;             ///< Control ORB RX memory power gating
  BOOLEAN                                      CfgSstunlClkGating;                 ///< Control IOMMU L1 SSTUNL clock gating
  BOOLEAN                                      CfgParityErrorConfiguration;        ///< Internal Parity Error Configuration
  UINT8                                        CfgSpgMemPowerGatingEnable;         ///< Control SPG memory power gating
  UINT8                                        CfgAcgAzMemPowerGatingEnable;       ///< Control ACG memory power gating
  UINT8                                        CfgBifMemPowerGatingEnable;         ///< Control BIF memory power gating
  BOOLEAN                                      CfgSDMAMemPowerGatingEnable;        ///< SDMA Memory Power Gating
  UINT8                                        CfgPcieTxpwrInOff;                  ///< TxPwr mapping for TxPhyCmd
  UINT8                                        CfgPcieRxpwrInOff;                  ///< RxPwr mapping for RxPhyCmd
  UINT32                                       CfgSmuDeterminismAmbient;           ///< SMU Determisnism Ambient Param
  BOOLEAN                                      CfgBTCEnable;                       ///< Boot Time Calibration Eanble
  BOOLEAN                                      CfgPSIEnable;                       ///< PSI Eanble
  BOOLEAN                                      CfgACSEnable;                       ///< ACS Eanble
  BOOLEAN                                      CfgIOHCClkGatinSgupport;            ///< IOHC Clk Gating Support
  BOOLEAN                                      CfgIommuSupport;                    ///< IOMMU Support
  BOOLEAN                                      CfgNbioPoisonConsumption;           ///< NBIO Poison Consumption
  BOOLEAN                                      CfgNbioRASEnable;                   ///< NBIO RAS Eanble
  BOOLEAN                                      CfgNTBEnable;                       ///< NTB Eanble
  UINT8                                        CfgNTBLocation;                     ///< NTB location
  UINT8                                        CfgNTBPcieCoreSel;                  ///< NTB PCIe Core
  UINT8                                        CfgNTBMode;                         ///< NTB Mode
  UINT8                                        CfgNTBLinkSpeed;                    ///< NTB link speed
  GNB_BUILD_OPTIONS_COMMON_HOB                 GnbCommonOptions;                   ///< GNB Options for multi-family libraries
} GNB_BUILD_OPTIONS_ZP_DATA_HOB;

#pragma pack (pop)

#endif

