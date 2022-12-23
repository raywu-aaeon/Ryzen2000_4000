/* $NoKeywords:$ */
/**
 * @file
 *
 * Install of build option: GNB
 *
 * Contains AMD AGESA install macros and test conditions. Output is the
 * defaults tables reflecting the User's build options selection.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Options
 * @e \$Revision: 329865 $   @e \$Date: 2015-10-29 09:59:04 +0800 (Thu, 29 Oct 2015) $
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

#include "Gnb.h"
#include "OptionGnb.h"
#include "GnbPcie.h"
#include "GnbGfx.h"

//---------------------------------------------------------------------------------------------------
// Common BUILD options
// These Common Build options apply to all families
//---------------------------------------------------------------------------------------------------
  #define CFG_IGFX_AS_PCIE_EP                          TRUE
  #define CFG_GNB_PCIE_LINK_RECEIVER_DETECTION_POOLING (60 * 1000)
  #define CFG_GNB_PCIE_LINK_L0_POOLING                 (60 * 1000)
  #define CFG_GNB_PCIE_LINK_GPIO_RESET_ASSERT_TIME     (2 * 1000)
  #define CFG_GNB_PCIE_LINK_RESET_TO_TRAINING_TIME     (2 * 1000)
  #define CFG_GNB_PCIE_TRAINING_ALGORITHM              PcieTrainingStandard
  #define CFG_GNB_PCIE_POWERGATING_FLAGS               0
  #define CFG_PCIE_ASPM_BLACK_LIST_ENABLE              TRUE
  #define CFG_MAX_PAYLOAD_ENABLE                       TRUE
  #define CFG_GNB_IVRS_RELATIVE_ADDR_NAMES_SUPPORT     FALSE
  #define CFG_ACPI_SET_OEM_ID                          'A','M','D',' ',' ',' '         // OemIdString[6];      ///< @BldCfgItem{BLDCFG_ACPI_SET_OEM_ID}
  #define CFG_ACPI_SET_OEM_TABLE_ID                    'A','G','E','S','A',' ',' ',' ' // OemTableIdString[8]; ///< @BldCfgItem{BLDCFG_ACPI_SET_OEM_TABLE_ID}
  #define CFG_GNB_LOAD_REAL_FUSE                       TRUE

//  GNB_BUILD_OPTIONS ROMDATA GnbBuildOptions = {
  GNB_BUILD_OPTIONS GnbBuildOptions = {
    CFG_IGFX_AS_PCIE_EP,                          ///< IgfxModeAsPcieEp;                   ///< Itegrated Gfx mode Pcie EP or Legacy
    CFG_GNB_PCIE_LINK_RECEIVER_DETECTION_POOLING, ///< CfgGnbLinkReceiverDetectionPooling; ///< Receiver pooling detection time in us.
    CFG_GNB_PCIE_LINK_L0_POOLING,                 ///< CfgGnbLinkL0Pooling;                ///< Pooling for link to get to L0 in us
    CFG_GNB_PCIE_LINK_GPIO_RESET_ASSERT_TIME,     ///< CfgGnbLinkGpioResetAssertionTime;   ///< Gpio reset assertion time in us
    CFG_GNB_PCIE_LINK_RESET_TO_TRAINING_TIME,     ///< CfgGnbLinkResetToTrainingTime;      ///< Time duration between deassert GPIO reset and release training in us
    CFG_GNB_PCIE_TRAINING_ALGORITHM,              ///< CfgGnbTrainingAlgorithm;            ///< distribution of training across interface calls
    CFG_GNB_PCIE_POWERGATING_FLAGS,               ///< CfgPciePowerGatingFlags;            ///< Pcie Power gating flags
    CFG_PCIE_ASPM_BLACK_LIST_ENABLE,              ///< PcieAspmBlackListEnable;            ///< Control Pcie Aspm Black List
    CFG_MAX_PAYLOAD_ENABLE,                       ///< CfgMaxPayloadEnable;                ///< Enables configuration of Max_Payload_Size in PCIe device links
    CFG_GNB_IVRS_RELATIVE_ADDR_NAMES_SUPPORT,     ///< IvrsRelativeAddrNamesSupport;       ///< Support for relative address names
    CFG_ACPI_SET_OEM_ID,                          ///< OemIdString[6];                     ///< Configurable ACPI OEM Id
    CFG_ACPI_SET_OEM_TABLE_ID,                    ///< OemTableIdString[8];                ///< Configurable ACPI OEM Table Id
    CFG_GNB_LOAD_REAL_FUSE                        ///< GnbLoadRealFuseTable;               ///< Support for fuse table loading
  };

//---------------------------------------------------------------------------------------------------
// Family-specific common BUILD options
// The build options are used in all families, but may be configured differently for different families
// CFG_XXXX will override default value if CFG_XXXX is defined
// CFG_XXXX_FM will override CFG_XXXX if CFG_XXXX_FM is defined (Where _FM is family, _CZ, _ST, ...
// If neither CFG_XXXX_FM or CFG_XXXX is defined, then the family specific default will be defined
// within the family-specific definition areas below
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
// CZ-specific common BUILD options
//---------------------------------------------------------------------------------------------------
    // Common configuration defaults for CZ
    #define CFG_SMU_MESSAGE_ENABLE_CZ                 TRUE
    #define CFG_SCS_SUPPORT_CZ                        TRUE
    #define CFG_UMA_STEERING_CZ                       DefaultGarlic
    #define CFG_GMC_POWER_GATING_CZ                   GmcPowerGatingWithStutter
    #define CFG_GMC_CLOCK_GATING_CZ                   TRUE
    #define CFG_ORB_DYN_WAKE_ENABLE_CZ                TRUE
    #define CFG_ORB_CLOCK_GATING_ENABLE_CZ            TRUE
    #define CFG_IOMMU_L1_CLOCK_GATING_ENABLE_CZ       TRUE
    #define CFG_IOMMU_L2_CLOCK_GATING_ENABLE_CZ       TRUE
    #define CFG_IOC_LCLK_CLOCK_GATING_ENABLE_CZ       TRUE
    #define CFG_GNB_BAPM_SUPPORT_CZ                   TRUE  // CfgBapmEnable;                       ///< @BldCfgItem{BLDCFG_BAPM_ENABLE}
    #define CFG_CHUB_CLOCK_GATING_CZ                  TRUE
    #define CFG_ACP_CLOCK_GATING_CZ                   TRUE
    #define CFG_AXG_DISABLE_CZ                        FALSE
    #define  CFG_GNB_NUM_DISPLAY_STREAM_PIPES_CZ      3
    #define CFG_PCIE_ARI_SUPPORT_CZ                   FALSE
    #define CFG_PCIE_HW_INIT_PWR_GATING_CZ            PcieHwInitPwrGatingEnableAll
    #define CFG_SPG_CLOCK_GATING_ENABLE_CZ            TRUE
    #define CFG_ACG_AZ_CLOCK_GATING_ENABLE_CZ         TRUE
    #define CFG_IOMMU_L1_MEM_POWER_GATING_CZ          TRUE
    #define CFG_IOMMU_L2_MEM_POWER_GATING_CZ          FALSE
    #define CFG_ORB_TX_MEM_POWER_GATING_CZ            OrbMemPowerGatingLS
    #define CFG_ORB_RX_MEM_POWER_GATING_CZ            OrbMemPowerGatingLS
    #define CFG_SSTUNL_CLK_GATING_CZ                  TRUE
    #define CFG_PARITY_ERROR_CONFIGURATION_CZ         FALSE
    #define CFG_SPG_MEM_POWER_GATING_CZ               SPGACGAZMemPowerGatingLS
    #define CFG_ACG_AZ_MEM_POWER_GATING_CZ            SPGACGAZMemPowerGatingLS
    #define CFG_BIF_MEM_SD_EN_CZ                      TRUE
    #define CFG_SDMA_MEM_POWER_GATING_CZ              TRUE
    #define CFG_PCIE_TX_POWER_INOFF_CZ                3
    #define CFG_PCIE_RX_POWER_INOFF_CZ                3
    #define CFG_SMU_DETERMINISM_AMBIENT_CZ            0
    #define CFG_BTC_ENABLE_CZ                         TRUE
    #define CFG_PSI_ENABLE_CZ                         TRUE
    #define CFG_ACS_ENABLE_CZ                         FALSE
    #define CFG_SHADOW_PSTATES_CZ                     TRUE

//    GNB_BUILD_OPTIONS_CZ ROMDATA GnbBuildOptionsCZ = {
    GNB_BUILD_OPTIONS_CZ GnbBuildOptionsCZ = {
      { // GNB_BUILD_OPTIONS_COMMON
        CFG_SCS_SUPPORT_CZ,
        CFG_UMA_STEERING_CZ,
        CFG_GMC_POWER_GATING_CZ,
        CFG_GMC_CLOCK_GATING_CZ,
        CFG_ORB_DYN_WAKE_ENABLE_CZ,
        CFG_ORB_CLOCK_GATING_ENABLE_CZ,
        CFG_IOMMU_L1_CLOCK_GATING_ENABLE_CZ,
        CFG_IOMMU_L2_CLOCK_GATING_ENABLE_CZ,
        CFG_IOC_LCLK_CLOCK_GATING_ENABLE_CZ,
        CFG_GNB_BAPM_SUPPORT_CZ,
        FALSE,
        CFG_GNB_NUM_DISPLAY_STREAM_PIPES_CZ,
        CFG_SMU_MESSAGE_ENABLE_CZ
      },
      CFG_CHUB_CLOCK_GATING_CZ,
      CFG_ACP_CLOCK_GATING_CZ,
      {
        CFG_GNB_BAPM_SUPPORT_CZ,  ///<               BAPM
        1,  ///<    POWER_ESTIMATOR
        1,  ///< THERMAL_CONTROLLER
        1,  ///<       TDC_LIMITING
        1,  ///<   PKG_PWR_LIMITING
        1,  ///<           LCLK_DPM
        1,  ///< VOLTAGE_CONTROLLER
        1,  ///<              GEAPM
        1,  ///<                BBB
        1,  ///<                IBS
        1,  ///<     PSTATE_ARBITER
        1,  ///<             NB_DPM
        1,  ///<    LCLK_DEEP_SLEEP
        1,  ///<                ULV
        1,  ///<          GFX_CU_PG
        0,  ///<               AVFS
        0,//1,  ///<            UVD_DPM
        1,  ///<      VQ_CONTROLLER
        1,  ///<                ACC
        0,//1,  ///<           SCLK_DPM
        1,  ///<     PRE_FETCH_DATA
        1,  ///<         DFS_BYPASS
        1,  ///<                HTC
        0,//1,  ///<             VDDGFX
        1,  ///<              LEAPM
        0,  ///<         CONN_STDBY
        0,//1,  ///<     PORT80_MONITOR
        1,  ///<         PSPCLK_DPM
        1,  ///<              STAPM
        0,//1,  ///<    RELIABILITY_MASK
        1,  ///<      CPU_STRETCHER
        0,//1,  ///< SCLK_STRETCHER_MASK
      },
      CFG_AXG_DISABLE_CZ,
      CFG_PCIE_HW_INIT_PWR_GATING_CZ,
      CFG_PCIE_ARI_SUPPORT_CZ,
      CFG_SPG_CLOCK_GATING_ENABLE_CZ,
      CFG_ACG_AZ_CLOCK_GATING_ENABLE_CZ,
      CFG_IOMMU_L1_MEM_POWER_GATING_CZ,
      CFG_IOMMU_L2_MEM_POWER_GATING_CZ,
      CFG_ORB_TX_MEM_POWER_GATING_CZ,
      CFG_ORB_RX_MEM_POWER_GATING_CZ,
      CFG_SSTUNL_CLK_GATING_CZ,
      CFG_PARITY_ERROR_CONFIGURATION_CZ,
      CFG_SPG_MEM_POWER_GATING_CZ,
      CFG_ACG_AZ_MEM_POWER_GATING_CZ,
      CFG_BIF_MEM_SD_EN_CZ,
      CFG_SDMA_MEM_POWER_GATING_CZ,
      CFG_PCIE_TX_POWER_INOFF_CZ,
      CFG_PCIE_RX_POWER_INOFF_CZ,
      CFG_SMU_DETERMINISM_AMBIENT_CZ,
      CFG_BTC_ENABLE_CZ,
      CFG_PSI_ENABLE_CZ,
      CFG_ACS_ENABLE_CZ,
      CFG_SHADOW_PSTATES_CZ
    };

//---------------------------------------------------------------------------------------------------
// ST-specific common BUILD options
//---------------------------------------------------------------------------------------------------
    // Common configuration defaults for ST
    #define CFG_SMU_MESSAGE_ENABLE_ST                 TRUE
    #define CFG_SCS_SUPPORT_ST                        TRUE
    #define CFG_UMA_STEERING_ST                       DefaultGarlic
    #define CFG_GMC_POWER_GATING_ST                   GmcPowerGatingWithStutter
    #define CFG_GMC_CLOCK_GATING_ST                   TRUE
    #define CFG_ORB_DYN_WAKE_ENABLE_ST                TRUE
    #define CFG_ORB_CLOCK_GATING_ENABLE_ST            TRUE
    #define CFG_IOMMU_L1_CLOCK_GATING_ENABLE_ST       TRUE
    #define CFG_IOMMU_L2_CLOCK_GATING_ENABLE_ST       TRUE
    #define CFG_IOC_LCLK_CLOCK_GATING_ENABLE_ST       TRUE
    #define CFG_GNB_BAPM_SUPPORT_ST                   TRUE  // CfgBapmEnable;                       ///< @BldCfgItem{BLDCFG_BAPM_ENABLE}
    #define CFG_CHUB_CLOCK_GATING_ST                  TRUE
    #define CFG_ACP_CLOCK_GATING_ST                   TRUE
    #define CFG_AXG_DISABLE_ST                        FALSE
    #define  CFG_GNB_NUM_DISPLAY_STREAM_PIPES_ST      3
    #define CFG_PCIE_ARI_SUPPORT_ST                   FALSE
    #define CFG_PCIE_HW_INIT_PWR_GATING_ST            PcieHwInitPwrGatingEnableAll
    #define CFG_SPG_CLOCK_GATING_ENABLE_ST            TRUE
    #define CFG_ACG_AZ_CLOCK_GATING_ENABLE_ST         TRUE
    #define CFG_IOMMU_L1_MEM_POWER_GATING_ST          TRUE
    #define CFG_IOMMU_L2_MEM_POWER_GATING_ST          FALSE
    #define CFG_ORB_TX_MEM_POWER_GATING_ST            OrbMemPowerGatingLS
    #define CFG_ORB_RX_MEM_POWER_GATING_ST            OrbMemPowerGatingLS
    #define CFG_SSTUNL_CLK_GATING_ST                  TRUE
    #define CFG_PARITY_ERROR_CONFIGURATION_ST         FALSE
    #define CFG_SPG_MEM_POWER_GATING_ST               SPGACGAZMemPowerGatingLS
    #define CFG_ACG_AZ_MEM_POWER_GATING_ST            SPGACGAZMemPowerGatingLS
    #define CFG_BIF_MEM_SD_EN_ST                      TRUE
    #define CFG_SDMA_MEM_POWER_GATING_ST              TRUE
    #define CFG_PCIE_TX_POWER_INOFF_ST                3
    #define CFG_PCIE_RX_POWER_INOFF_ST                3
    #define CFG_SMU_DETERMINISM_AMBIENT_ST            0
    #define CFG_BTC_ENABLE_ST                         TRUE
    #define CFG_PSI_ENABLE_ST                         TRUE
    #define CFG_ACS_ENABLE_ST                         FALSE
    #define CFG_POSTCODE_DISABLE_ST                   TRUE

//    GNB_BUILD_OPTIONS_ST ROMDATA GnbBuildOptionsST = {
    GNB_BUILD_OPTIONS_ST GnbBuildOptionsST = {
      { // GNB_BUILD_OPTIONS_COMMON
        CFG_SCS_SUPPORT_ST,
        CFG_UMA_STEERING_ST,
        CFG_GMC_POWER_GATING_ST,
        CFG_GMC_CLOCK_GATING_ST,
        CFG_ORB_DYN_WAKE_ENABLE_ST,
        CFG_ORB_CLOCK_GATING_ENABLE_ST,
        CFG_IOMMU_L1_CLOCK_GATING_ENABLE_ST,
        CFG_IOMMU_L2_CLOCK_GATING_ENABLE_ST,
        CFG_IOC_LCLK_CLOCK_GATING_ENABLE_ST,
        CFG_GNB_BAPM_SUPPORT_ST,
        FALSE,
        CFG_GNB_NUM_DISPLAY_STREAM_PIPES_ST,
        CFG_SMU_MESSAGE_ENABLE_ST
      },
      CFG_CHUB_CLOCK_GATING_ST,
      CFG_ACP_CLOCK_GATING_ST,
      {
        CFG_GNB_BAPM_SUPPORT_ST,  ///<               BAPM
        1,  ///<    POWER_ESTIMATOR
        1,  ///< THERMAL_CONTROLLER
        1,  ///<       TDC_LIMITING
        1,  ///<   PKG_PWR_LIMITING
        1,  ///<           LCLK_DPM
        1,  ///< VOLTAGE_CONTROLLER
        1,  ///<              GEAPM
        1,  ///<                BBB
        1,  ///<                IBS
        1,  ///<     PSTATE_ARBITER
        1,  ///<             NB_DPM
        1,  ///<    LCLK_DEEP_SLEEP
        0,  ///<                ULV
        1,  ///<          GFX_CU_PG
        1,  ///<               AVFS
        0,//1,  ///<            UVD_DPM
        0,//1,  ///<               CHTC
        0,//1,  ///<            ACP_DPM
        0,//1,  ///<           SCLK_DPM
        1,  ///<     PRE_FETCH_DATA
        1,  ///<         DFS_BYPASS
        1,  ///<                HTC
        0,//1,  ///<             VDDGFX
        1,  ///<              LEAPM
        1,  ///<         CONN_STDBY
        0,//1,  ///<     PORT80_MONITOR
        1,  ///<         PSPCLK_DPM
        1,  ///<              STAPM
        0,//1,  ///<    DETERMINISM_MASK
        1,  ///<      CPU_STRETCHER
        0,//1,  ///< SCLK_STRETCHER_MASK
      },
      CFG_AXG_DISABLE_ST,
      CFG_PCIE_HW_INIT_PWR_GATING_ST,
      CFG_PCIE_ARI_SUPPORT_ST,
      CFG_SPG_CLOCK_GATING_ENABLE_ST,
      CFG_ACG_AZ_CLOCK_GATING_ENABLE_ST,
      CFG_IOMMU_L1_MEM_POWER_GATING_ST,
      CFG_IOMMU_L2_MEM_POWER_GATING_ST,
      CFG_ORB_TX_MEM_POWER_GATING_ST,
      CFG_ORB_RX_MEM_POWER_GATING_ST,
      CFG_SSTUNL_CLK_GATING_ST,
      CFG_PARITY_ERROR_CONFIGURATION_ST,
      CFG_SPG_MEM_POWER_GATING_ST,
      CFG_ACG_AZ_MEM_POWER_GATING_ST,
      CFG_BIF_MEM_SD_EN_ST,
      CFG_SDMA_MEM_POWER_GATING_ST,
      CFG_PCIE_TX_POWER_INOFF_ST,
      CFG_PCIE_RX_POWER_INOFF_ST,
      CFG_SMU_DETERMINISM_AMBIENT_ST,
      CFG_BTC_ENABLE_ST,
      CFG_PSI_ENABLE_ST,
      CFG_ACS_ENABLE_ST,
      CFG_POSTCODE_DISABLE_ST
    };

  //---------------------------------------------------------------------------------------------------
  // Module entries
  //---------------------------------------------------------------------------------------------------

// S3 need redesign
//  //--------------------------------------------------------------------------------------------------
//OptionS3ScriptInstall.h
//  #if (AGESA_ENTRY_INIT_LATE == TRUE)
//  //---------------------------------------------------------------------------------------------------
//
//
//  #if  (GNB_TYPE_CZ == TRUE || GNB_TYPE_ST == TRUE)
//    #define GNBS3RESTOREV8
//    #if (GNB_TYPE_CZ == TRUE || GNB_TYPE_ST == TRUE)
//      S3_DISPATCH_FUNCTION  GnbSmuServiceRequestV8S3Script;
//      #undef  GNBS3RESTOREV8
//      #define GNBS3RESTOREV8 {GnbSmuServiceRequestV8S3Script_ID, GnbSmuServiceRequestV8S3Script},
//    #endif
//
//    #define GNBS3WAITFORCACLOCKCZ
//    #if (GNB_TYPE_CZ == TRUE)
//      S3_DISPATCH_FUNCTION  GnbSmuWaitForCacLockCZS3Script;
//      #undef  GNBS3WAITFORCACLOCKCZ
//      #define GNBS3WAITFORCACLOCKCZ {GnbSmuWaitForCacLockS3Script_ID, GnbSmuWaitForCacLockCZS3Script},
//    #endif
//    #define GNBS3WAITFORCACLOCKST
//    #if (GNB_TYPE_ST == TRUE)
//      S3_DISPATCH_FUNCTION  GnbSmuWaitForCacLockSTS3Script;
//      #undef  GNBS3WAITFORCACLOCKST
//      #define GNBS3WAITFORCACLOCKST {GnbSmuWaitForCacLockS3Script_ID, GnbSmuWaitForCacLockSTS3Script},
//    #endif
//
//    S3_DISPATCH_FUNCTION  GnbLibStallS3Script;
//    #define PCIELATERESTORECZ
//    #if (GNB_TYPE_CZ == TRUE)
//      S3_DISPATCH_FUNCTION  PcieLateRestoreInitCZS3Script;
//      #undef  PCIELATERESTORECZ
//      #define PCIELATERESTORECZ {PcieLateRestoreCZS3Script_ID, PcieLateRestoreInitCZS3Script},
//    #endif
//    #define PCIELATERESTOREST
//    #if (GNB_TYPE_ST == TRUE)
//      S3_DISPATCH_FUNCTION  PcieLateRestoreInitSTS3Script;
//      #undef  PCIELATERESTOREST
//      #define PCIELATERESTOREST {PcieLateRestoreSTS3Script_ID, PcieLateRestoreInitSTS3Script},
//    #endif
//    #define GNB_S3_DISPATCH_FUNCTION_TABLE \
//    GNBS3RESTOREV8      \
//    PCIELATERESTORECZ \
//    PCIELATERESTOREST \
//    GNBS3WAITFORCACLOCKCZ \
//    GNBS3WAITFORCACLOCKST \
//    {GnbLibStallS3Script_ID, GnbLibStallS3Script},
//  #endif

  #define CFG_AMD_POWER_CEILING            0
  #define CFG_MEMORY_LRDIMM_CAPABLE              TRUE
  #define CFG_LIMIT_MEMORY_TO_BELOW_1TB         TRUE

//Clear AGESA V5 Package and Version information.
#define AGESA_CODE_SIGNATURE  {0, 0, 0, 0, 0, 0, 0, 0}
#define AGESA_PACKAGE_STRING  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define AGESA_VERSION_STRING  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

// Defaults for public user options
#define OPTION_UDIMMS                           FALSE
#define OPTION_RDIMMS                           FALSE
#define OPTION_SODIMMS                          FALSE
#define OPTION_LRDIMMS                          FALSE
#define OPTION_DDR2                             FALSE
#define OPTION_DDR3                             FALSE
#define OPTION_GDDR5                            FALSE
#define OPTION_DDR4                             FALSE
#define OPTION_ECC                              FALSE
#define OPTION_EMP                              FALSE
#define OPTION_BANK_INTERLEAVE                  FALSE
#define OPTION_DCT_INTERLEAVE                   FALSE
#define OPTION_NODE_INTERLEAVE                  FALSE
#define OPTION_PARALLEL_TRAINING                FALSE
#define OPTION_ONLINE_SPARE                     FALSE
#define OPTION_MEM_RESTORE                      FALSE
#define OPTION_DIMM_EXCLUDE                     FALSE
#define OPTION_AMP                              FALSE
#define OPTION_DATA_EYE                         FALSE
#define OPTION_AGGRESSOR                        FALSE
#define OPTION_S3_SUPPORT                       FALSE
#define OPTION_ONDIMMTHERMAL                    FALSE

// Default all CPU controls to off
#define OPTION_CRAT                             FALSE
#define OPTION_CDIT                             FALSE
#define OPTION_CPU_CORELEVELING                 FALSE
#define OPTION_CPU_CFOH                         FALSE
#define OPTION_C6_STATE                         FALSE
#define OPTION_IO_CSTATE                        FALSE
#define OPTION_CPB                              FALSE
#define OPTION_CPU_APM                          FALSE
#define OPTION_CPU_PSI                          FALSE
#define OPTION_CPU_HTC                          FALSE
#define OPTION_S3SCRIPT                         FALSE
#define OPTION_GFX_RECOVERY                     FALSE
#define OPTION_PREFETCH_MODE                    FALSE
#define OPTION_CONNECTED_STANDBY                FALSE
#define OPTION_CC6_EXIT_CONTROL                 FALSE
#define OPTION_BTC                              FALSE

#define OPTION_ACPI_PSTATES             TRUE
#define OPTION_WHEA                     TRUE
#define OPTION_DMI                      TRUE
#define OPTION_EARLY_SAMPLES            FALSE
#define CFG_ACPI_PSTATES_PPC            TRUE
#define CFG_ACPI_PSTATES_PCT            TRUE
#define CFG_ACPI_PSTATES_PSD            TRUE
#define CFG_ACPI_PSTATES_PSS            TRUE
#define CFG_ACPI_PSTATES_XPSS           TRUE
#define CFG_ACPI_PSTATE_PSD_INDPX       FALSE
//#define CFG_VRM_HIGH_SPEED_ENABLE       FALSE
#define CFG_VRM_NB_HIGH_SPEED_ENABLE    FALSE
#define CFG_VRM_GFX_HIGH_SPEED_ENABLE    FALSE
#define OPTION_ALIB                     TRUE
    #define OPTION_ADDR_TO_CS_TRANSLATOR        FALSE
  #define CFG_PCI_MMIO_BASE               (0)

  #define CFG_PCI_MMIO_SIZE               (0)
  #define CFG_IOMMU_EXCLUSION_RANGE_LIST      (NULL)
  #define CFG_HYBRID_BOOST_ENABLE            TRUE
//  #define CFG_GNB_IOAPIC_ADDRESS             NULL
  #define CFG_GNB_IOMMU_ADDRESS             NULL
  #define CFG_GPU_FREQUENCY_LIMIT           0
  #define CFG_MAX_NUM_AUDIO_ENDPOINTS      255
  #define CFG_BAPM_ENABLE                   TRUE
  #define CFG_GNB_AZ_I2SBUS_SELECT          GnbAcpAzalia
  #define CFG_GNB_AZ_I2SBUS_PIN_CONFIG      GnbAcp4Tx4RxBluetooth
  #define CFG_PPT_LIMIT_AC                  0
  #define CFG_PPT_LIMIT_DC                  0
  #define CFG_SYSTEM_CONFIGURATION          0
  #define CFG_STAPM_SCALAR                  0
  #define CFG_STAPM_BOOST                   StapmBoostSystemConfig
  #define CFG_STAPM_TIME_CONSTANT           0
  #define CFG_ENABLE_DATA_EYE              TRUE
  #define CFG_ACPI_SET_OEM_ID             'A','M','D',' ',' ',' '
  #define CFG_ACPI_SET_OEM_TABLE_ID       'A','G','E','S','A',' ',' ',' '
  #define CFG_BATTERY_BOOST_TUNE         0
  #define CFG_DRAM_DOUBLE_REFRESH_RATE             FALSE
  #define CFG_MEMORY_PHY_VOLTAGE          VOLT1_05
  #define CFG_THERMCTL_LIMIT         0
  #define CFG_CODEC_VERB_TABLE      NULL
  #define CFG_ACP_POWER_GATING      FALSE

//#define CFG_VRM_CURRENT_LIMIT                 0
//#define CFG_VRM_MAXIMUM_CURRENT_LIMIT         0
//#define CFG_VRM_LOW_POWER_THRESHOLD           14000  // 15W - 14000; 35W - 18000
//#define CFG_PLAT_NUM_IO_APICS                 3
#define CFG_CORE_LEVELING_MODE                0      // CORE_LEVEL_LOWEST
#define CFG_MEM_INIT_PSTATE                   0

// Specify the default values for the VRM controlling the VDDNB plane.
#define CFG_VRM_NB_CURRENT_LIMIT              0
#define CFG_VRM_NB_MAXIMUM_CURRENT_LIMIT      0
#define CFG_VRM_NB_LOW_POWER_THRESHOLD        15000  // 15W - 15000; 35W - 15000

// Specify the default values for the VRM controlling the GFX voltage rail .
#define CFG_VRM_GFX_CURRENT_LIMIT             0
#define CFG_VRM_GFX_MAXIMUM_CURRENT_LIMIT     0
#define CFG_VRM_GFX_LOW_POWER_THRESHOLD       15000  // 15W - 15000; 35W - 15000


#define OPT_REMOVE_RDIMMS_SUPPORT           TRUE
#define OPT_REMOVE_LRDIMMS_SUPPORT          TRUE
#define OPT_REMOVE_NODE_INTERLEAVE          TRUE
#define OPT_REMOVE_PARALLEL_TRAINING         TRUE
#define OPT_REMOVE_ONLINE_SPARE_SUPPORT      TRUE
#define OPT_REMOVE_MULTISOCKET_SUPPORT       TRUE
#define OPT_REMOVE_WHEA                      TRUE
#define OPT_REMOVE_EARLY_SAMPLES             FALSE
#define CFG_SKIN_CONTROL_SCALAR              0
#define CFG_VRM_CURRENT_LIMIT                0
#define CFG_VRM_MAXIMUM_CURRENT_LIMIT        0
#define CFG_VRM_SVI_OCP_LEVEL                0
#define CFG_VRM_LOW_POWER_THRESHOLD          18000
#define CFG_VRM_SLEW_RATE                    12000
#define CFG_VRM_NB_CURRENT_LIMIT             0
#define CFG_VRM_NB_MAXIMUM_CURRENT_LIMIT     0
#define CFG_VRM_NB_SVI_OCP_LEVEL             0
#define CFG_VRM_NB_LOW_POWER_THRESHOLD       15000
#define CFG_VRM_NB_SLEW_RATE                 10000
#define CFG_VRM_GFX_CURRENT_LIMIT            0
#define CFG_VRM_GFX_MAXIMUM_CURRENT_LIMIT    0
#define CFG_VRM_GFX_SVI_OCP_LEVEL            0
#define CFG_VRM_GFX_LOW_POWER_THRESHOLD      15000
#define CFG_VRM_GFX_SLEW_RATE                10000
#define CFG_PLAT_NUM_IO_APICS                3
//#define CFG_CORE_LEVELING_MODE               CORE_LEVEL_LOWEST
//#define CFG_MEM_INIT_PSTATE                  0
#define CFG_AMD_PLATFORM_TYPE                  0
#define CFG_DIMM_TYPE_USED_IN_MIXED_CONFIG     0
#define CFG_DIMM_TYPE_DDR3_CAPABLE             FALSE
#define CFG_DIMM_TYPE_DDR4_CAPABLE             TRUE
#define CFG_MEMORY_BUS_FREQUENCY_LIMIT         0
#define CFG_MEMORY_MODE_UNGANGED               TRUE
#define CFG_MEMORY_QUAD_RANK_CAPABLE           FALSE
#define CFG_MEMORY_QUADRANK_TYPE               0
#define CFG_MEMORY_RDIMM_CAPABLE               FALSE
#define CFG_MEMORY_UDIMM_CAPABLE               TRUE
#define CFG_MEMORY_SODIMM_CAPABLE              TRUE
#define CFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#define CFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE
#define CFG_MEMORY_CHANNEL_INTERLEAVING        TRUE
//#define CFG_MEMORY_POWER_DOWN                  TRUE
//#define CFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHIP_SELECT
#define CFG_ONLINE_SPARE                       FALSE
#define CFG_BANK_SWIZZLE                       TRUE
#define CFG_TIMING_MODE_SELECT                 0
#define CFG_MEMORY_CLOCK_SELECT                1066
#define CFG_DQS_TRAINING_CONTROL               FALSE
#define CFG_IGNORE_SPD_CHECKSUM                FALSE
#define CFG_USE_BURST_MODE                     FALSE
#define CFG_MEMORY_ALL_CLOCKS_ON               FALSE
//#define CFG_ENABLE_ECC_FEATURE                 FALSE
//#define CFG_ECC_REDIRECTION                    TRUE
#define CFG_SCRUB_DRAM_RATE                    0
#define CFG_SCRUB_L2_RATE                      0
#define CFG_SCRUB_L3_RATE                      0
#define CFG_SCRUB_IC_RATE                      0
#define CFG_SCRUB_DC_RATE                      0
#define CFG_ECC_SYNC_FLOOD                     TRUE
#define CFG_ECC_SYMBOL_SIZE                    4
#define CFG_HEAP_DRAM_ADDRESS                  0xB0000ul
#define CFG_1GB_ALIGN                          FALSE
#define CFG_VRM_HIGH_SPEED_ENABLE              TRUE
#define CFG_PLATFORM_CSTATE_IO_BASE_ADDRESS    0x413
#define CFG_UMA_ALIGNMENT                      0x00FFFFC0
#define CFG_UMA_ALLOCATION_MODE                UMA_AUTO
#define CFG_PLATFORM_CSTATE_MODE               CStateModeC6
#define CFG_MEMORY_POWER_POLICY_MODE             Performance
#define CFG_GNB_IOAPIC_ADDRESS               0xFEC01000
#define CFG_UMA_ABOVE4G_SUPPORT              TRUE
#define CFG_REMOTE_DISPLAY_SUPPORT           TRUE

#define CFG_GNB_AZ_SSID                      0xC9501022

  #define CFG_CPU_FREQUENCY_LIMIT         0
  #define CFG_CPU_CONNECTED_STANDBY_MODE  0
  #define CFG_CSTATE_MODE                     CStateModeC6
  #define CFG_CSTATE_OPDATA                   0
  #define CFG_CSTATE_IO_BASE_ADDRESS       0
  #define CFG_CPB_MODE                        CpbModeAuto
  #define CFG_PLATFORM_CONTROL_FLOW_MODE  (Nfcm)
  #define CFG_USE_32_BYTE_REFRESH  (FALSE)
  #define CFG_USE_VARIABLE_MCT_ISOC_PRIORITY  (FALSE)
  #define CFG_PERFORMANCE_HARDWARE_PREFETCHER  (0)
  #define CFG_PERFORMANCE_SOFTWARE_PREFETCHES  (0)
  #define CFG_PERFORMANCE_DRAM_PREFETCHER  (0)

  #define CFG_NB_PSTATES_SUPPORTED        (TRUE)
  #define CFG_HTC_TEMPERATURE_LIMIT        (0)
  #define CFG_LHTC_TEMPERATURE_LIMIT        (0)
  #define CFG_PCI_MMIO_BASE               (0)
  #define CFG_PCI_MMIO_SIZE               (0)
  #define CFG_IOMMU_EXCLUSION_RANGE_LIST      (NULL)
  #define CFG_HYBRID_BOOST_ENABLE            TRUE







  #define CFG_LVDS_BIT_DEPTH                            FALSE
  #define CFG_LVDS_PARAM_OVERWRITE_EN                   FALSE

///////////////////////////
  #define CFG_MEMORY_ENABLE_BANK_SWAP_ONLY      BANK_SWAP_ONLY_AUTO
  #define CFG_MEMORY_ENABLE_BANK_INTERLEAVING   TRUE
  #define CFG_MEMORY_ENABLE_NODE_INTERLEAVING   FALSE
  #define CFG_MEMORY_CHANNEL_INTERLEAVING       TRUE
  #define CFG_MEMORY_POWER_DOWN                 FALSE
  #define CFG_MEMORY_MAC_DEFAULT                MAC_UNTESTEDMAC
  #define CFG_MEMORY_EXTENDED_TEMPERATURE_RANGE FALSE
  #define CFG_DRAM_TEMP_CONTROLLED_REFRESH_EN     TRUE
  #define CFG_POWER_DOWN_MODE                   0
  #define CFG_ONLINE_SPARE                      FALSE
  #define CFG_MEMORY_PARITY_ENABLE              FALSE
  #define CFG_BANK_SWIZZLE                      TRUE
//  #define CFG_TIMING_MODE_SELECT                TIMING_MODE_AUTO
//  #define CFG_MEMORY_CLOCK_SELECT               DDR800_FREQUENCY
//  #define CFG_DQS_TRAINING_CONTROL              TRUE
  #define CFG_IGNORE_SPD_CHECKSUM               FALSE
  #define CFG_USE_BURST_MODE                    FALSE
  #define CFG_MEMORY_ALL_CLOCKS_ON              FALSE
  #define CFG_DDR_PHY_DLL_BYPASS_MODE           TRUE
  #define CFG_ENABLE_ECC_FEATURE                TRUE
  #define CFG_ECC_REDIRECTION                   FALSE
//  #define CFG_SCRUB_DRAM_RATE         0
//  #define CFG_SCRUB_L2_RATE           DFLT_SCRUB_L2_RATE
//  #define CFG_SCRUB_L3_RATE           DFLT_SCRUB_L3_RATE
//  #define CFG_SCRUB_IC_RATE           DFLT_SCRUB_IC_RATE
//  #define CFG_SCRUB_DC_RATE           DFLT_SCRUB_DC_RATE
//  #define CFG_ECC_SYNC_FLOOD          TRUE
//  #define CFG_ECC_SYMBOL_SIZE         0
//  #define CFG_1GB_ALIGN               FALSE
  #define CFG_UMA_VERSION             0
  #define CFG_UMA_MODE                0
  #define CFG_FORCE_TRAIN_MODE                0
  #define CFG_PMU_TRAIN_MODE                0
  #define CFG_UMA_SIZE                0
  #define CFG_UMA_ABOVE4G           FALSE
//  #define CFG_UMA_ALIGNMENT           NO_UMA_ALIGNED
//  #define CFG_DIMM_TYPE_USED_IN_MIXED_CONFIG      DDR3_TECHNOLOGY
  #define CFG_DIMM_TYPE_DDR4_CAPABLE      TRUE
//  #define CFG_DIMM_TYPE_DDR3_CAPABLE      TRUE
  #define CFG_CUSTOM_VDDIO_VOLTAGE        0
  #define CFG_PROCESSOR_SCOPE_IN_SB   FALSE
  #define CFG_S3_LATE_RESTORE         TRUE
  #define CFG_USE_32_BYTE_REFRESH  (FALSE)
  #define CFG_USE_VARIABLE_MCT_ISOC_PRIORITY  (FALSE)
  #define CFG_PROCESSOR_SCOPE_NAME0          0
  #define CFG_PROCESSOR_SCOPE_NAME1          0
  #define CFG_GNB_HD_AUDIO                   TRUE
  #define CFG_ABM_SUPPORT                    FALSE
  #define CFG_DYNAMIC_REFRESH_RATE           0
  #define CFG_LCD_BACK_LIGHT_CONTROL         200
  #define CFG_EXT_HDMI_RE_DRIVE_REG_INFO             (NULL)
  #define CFG_EXT_HDMI_RE_DRIVE_REG_NUM               0


BUILD_OPT_CFG UserOptions = {
  {                                             // AGESA version string
    AGESA_CODE_SIGNATURE,                       //    code header Signature
    AGESA_PACKAGE_STRING,                       //    16 character ID
    AGESA_VERSION_STRING,                       //    12 character version string
    0                                           //    null string terminator
  },
  //Build Option Area
  OPTION_UDIMMS,                        //UDIMMS
  OPTION_RDIMMS,                        //RDIMMS
  OPTION_LRDIMMS,                       //LRDIMMS
  OPTION_ECC,                           //ECC
  OPTION_BANK_INTERLEAVE,               //BANK_INTERLEAVE
  OPTION_DCT_INTERLEAVE,                //DCT_INTERLEAVE
  OPTION_NODE_INTERLEAVE,               //NODE_INTERLEAVE
  OPTION_PARALLEL_TRAINING,             //PARALLEL_TRAINING
  OPTION_ONLINE_SPARE,                  //ONLINE_SPARE
  OPTION_MEM_RESTORE,                   //MEM CONTEXT RESTORE
  OPTION_ACPI_PSTATES,                  //ACPI_PSTATES
  OPTION_CRAT,                          //CRAT
  OPTION_CDIT,                          //CDIT
  OPTION_WHEA,                          //WHEA
  OPTION_DMI,                           //DMI
  OPTION_EARLY_SAMPLES,                 //EARLY_SAMPLES
  OPTION_ADDR_TO_CS_TRANSLATOR,         //ADDR_TO_CS_TRANSLATOR

  //Build Configuration Area
  CFG_PCI_MMIO_BASE,
  CFG_PCI_MMIO_SIZE,
  {
    // CoreVrm
    {
      CFG_VRM_CURRENT_LIMIT,              // VrmCurrentLimit
      CFG_VRM_LOW_POWER_THRESHOLD,        // VrmLowPowerThershold
      CFG_VRM_SLEW_RATE,                  // VrmSlewRate
      CFG_VRM_HIGH_SPEED_ENABLE,          // VrmHiSpeedEnable
      CFG_VRM_MAXIMUM_CURRENT_LIMIT,      // VrmMaximumCurrentLimit
      CFG_VRM_SVI_OCP_LEVEL               // VrmSviOcpLevel
    },
    // NbVrm
    {
      CFG_VRM_NB_CURRENT_LIMIT,           // VrmNbCurrentLimit
      CFG_VRM_NB_LOW_POWER_THRESHOLD,     // VrmNbLowPowerThershold
      CFG_VRM_NB_SLEW_RATE,               // VrmNbSlewRate
      CFG_VRM_NB_HIGH_SPEED_ENABLE,       // VrmNbHiSpeedEnable
      CFG_VRM_NB_MAXIMUM_CURRENT_LIMIT,   // VrmNbMaximumCurrentLimit
      CFG_VRM_NB_SVI_OCP_LEVEL            // VrmNbSviOcpLevel
    },
    // GfxVrm
    {
      CFG_VRM_GFX_CURRENT_LIMIT,           // VrmGfxCurrentLimit
      CFG_VRM_GFX_LOW_POWER_THRESHOLD,     // VrmGfxLowPowerThershold
      CFG_VRM_GFX_SLEW_RATE,               // VrmGfxSlewRate
      CFG_VRM_GFX_HIGH_SPEED_ENABLE,       // VrmGfxHiSpeedEnable
      CFG_VRM_GFX_MAXIMUM_CURRENT_LIMIT,   // VrmGfxMaximumCurrentLimit
      CFG_VRM_GFX_SVI_OCP_LEVEL            // VrmGfxSviOcpLevel
    }
  },
  CFG_CPU_FREQUENCY_LIMIT,              //CfgCpuFrequencyLimit
  CFG_CPU_CONNECTED_STANDBY_MODE,       //CfgPlatformConnectedStandbyMode
  CFG_PLAT_NUM_IO_APICS,                //PlatformApicIoNumber
  CFG_MEM_INIT_PSTATE,                  //MemoryInitPstate
  CFG_CSTATE_MODE,                      //CStateMode
  CFG_CSTATE_OPDATA,                    //CStatePlatformData
  CFG_CSTATE_IO_BASE_ADDRESS,           //CStateIoBaseAddress
  CFG_CPB_MODE,                         //CpbMode
  CFG_CORE_LEVELING_MODE,               //CoreLevelingCofig
  {
    CFG_PLATFORM_CONTROL_FLOW_MODE,       // The platform's control flow mode.
    CFG_USE_32_BYTE_REFRESH,              // Display Refresh uses 32 byte packets.
    CFG_USE_VARIABLE_MCT_ISOC_PRIORITY,   // The Memory controller will be set to Variable Isoc Priority.
    CFG_MEMORY_POWER_POLICY_MODE,         // Memory power policy
    CFG_NB_PSTATES_SUPPORTED              // The Nb-Pstates is supported or not
  },
  CFG_AMD_PLATFORM_TYPE,                // CfgAmdPlatformType
  CFG_AMD_POWER_CEILING,                // CfgAmdPowerCeiling
  CFG_HTC_TEMPERATURE_LIMIT,            // CfgHtcTemperatureLimit
  CFG_LHTC_TEMPERATURE_LIMIT,           // CfgLhtcTemperatureLimit

  CFG_MEMORY_BUS_FREQUENCY_LIMIT,       // CfgMemoryBusFrequencyLimit
  CFG_MEMORY_MODE_UNGANGED,             // CfgMemoryModeUnganged
  CFG_MEMORY_QUAD_RANK_CAPABLE,         // CfgMemoryQuadRankCapable
  CFG_MEMORY_QUADRANK_TYPE,             // CfgMemoryQuadrankType
  CFG_MEMORY_RDIMM_CAPABLE,             // CfgMemoryRDimmCapable
  CFG_MEMORY_LRDIMM_CAPABLE,            // CfgMemoryLRDimmCapable
  CFG_MEMORY_UDIMM_CAPABLE,             // CfgMemoryUDimmCapable
  CFG_MEMORY_SODIMM_CAPABLE,            // CfgMemorySodimmCapable
  CFG_LIMIT_MEMORY_TO_BELOW_1TB,        // CfgLimitMemoryToBelow1Tb
  CFG_MEMORY_ENABLE_BANK_SWAP_ONLY,     // CfgMemoryEnableBankSwapOnly
  CFG_MEMORY_ENABLE_BANK_INTERLEAVING,  // CfgMemoryEnableBankInterleaving
  CFG_MEMORY_ENABLE_NODE_INTERLEAVING,  // CfgMemoryEnableNodeInterleaving
  CFG_MEMORY_CHANNEL_INTERLEAVING,      // CfgMemoryChannelInterleaving
  CFG_MEMORY_POWER_DOWN,                // CfgMemoryPowerDown
  CFG_MEMORY_MAC_DEFAULT,               // CfgMemoryMacDefault
  CFG_MEMORY_EXTENDED_TEMPERATURE_RANGE,// CfgMemoryExtendedTemperatureRange
  CFG_DRAM_TEMP_CONTROLLED_REFRESH_EN,  // CfgDramTempControlledRefreshEn
  CFG_POWER_DOWN_MODE,                  // CfgPowerDownMode
  CFG_ONLINE_SPARE,                     // CfgOnlineSpare
  CFG_MEMORY_PARITY_ENABLE,             // CfgMemoryParityEnable
  CFG_BANK_SWIZZLE,                     // CfgBankSwizzle
  CFG_TIMING_MODE_SELECT,               // CfgTimingModeSelect
  CFG_MEMORY_CLOCK_SELECT,              // CfgMemoryClockSelect
  CFG_DQS_TRAINING_CONTROL,             // CfgDqsTrainingControl
  CFG_IGNORE_SPD_CHECKSUM,              // CfgIgnoreSpdChecksum
  CFG_USE_BURST_MODE,                   // CfgUseBurstMode
  CFG_MEMORY_ALL_CLOCKS_ON,             // CfgMemoryAllClocksOn
  CFG_DDR_PHY_DLL_BYPASS_MODE,          // CfgDdrPhyDllBypassMode
  CFG_ENABLE_ECC_FEATURE,               // CfgEnableEccFeature
  CFG_ECC_REDIRECTION,                  // CfgEccRedirection
  CFG_SCRUB_DRAM_RATE,                  // CfgScrubDramRate
  CFG_SCRUB_L2_RATE,                    // CfgScrubL2Rate
  CFG_SCRUB_L3_RATE,                    // CfgScrubL3Rate
  CFG_SCRUB_IC_RATE,                    // CfgScrubIcRate
  CFG_SCRUB_DC_RATE,                    // CfgScrubDcRate
  CFG_ECC_SYNC_FLOOD,                   // CfgEccSyncFlood
  CFG_ECC_SYMBOL_SIZE,                  // CfgEccSymbolSize
  CFG_HEAP_DRAM_ADDRESS,                // CfgHeapDramAddress
  CFG_1GB_ALIGN,                        // CfgNodeMem1GBAlign
  CFG_S3_LATE_RESTORE,                  // CfgS3LateRestore
  CFG_ACPI_PSTATE_PSD_INDPX,            // CfgAcpiPstateIndependent
  0,          // CfgAcpiPstatesPsdPolicy
  CFG_UMA_VERSION,                      // CfgUmaVersion
  CFG_UMA_MODE,                         // CfgUmaMode
  CFG_UMA_SIZE,                         // CfgUmaSize
  CFG_UMA_ABOVE4G,                      // CfgUmaAbove4G
  CFG_UMA_ALIGNMENT,                    // CfgUmaAlignment
  CFG_PROCESSOR_SCOPE_IN_SB,            // CfgProcessorScopeInSb
  CFG_PROCESSOR_SCOPE_NAME0,            // CfgProcessorScopeName0
  CFG_PROCESSOR_SCOPE_NAME1,            // CfgProcessorScopeName1
  CFG_GNB_HD_AUDIO,                     // CfgGnbHdAudio
  CFG_ABM_SUPPORT,                      // CfgAbmSupport
  CFG_DYNAMIC_REFRESH_RATE,             // CfgDynamicRefreshRate
  CFG_LCD_BACK_LIGHT_CONTROL,           // CfgLcdBackLightControl
  0,             // CfgGnb3dStereoPinIndex
  0,      // CfgTempPcieMmioBaseAddress
  0,                    // CfgGnbIGPUSSID
  0,                 // CfgGnbHDAudioSSID
  0,                    // CfgGnbPcieSSID
  0,         // CfgLvdsSpreadSpectrum
  0,    // CfgLvdsSpreadSpectrumRate

  0,                      // FchBldCfg

  0,                    // CfgIommuSupport
  0,    // CfgLvdsPowerOnSeqDigonToDe
  0,  // CfgLvdsPowerOnSeqDeToVaryBl
  0,    // CfgLvdsPowerOnSeqDeToDigon
  0, // CfgLvdsPowerOnSeqVaryBlToDe
  0,// CfgLvdsPowerOnSeqOnToOffDelay
  0,// CfgLvdsPowerOnSeqVaryBlToBlon
  0,// CfgLvdsPowerOnSeqBlonToVaryBl
  0,        // CfgLvdsMaxPixelClockFreq
  0,      // CfgLcdBitDepthControlValue
  0,            // CfgLvds24bbpPanelMode
  {
    0,          // CfgLvdsMiscControl
    0,             // CfgLvdsMiscControl
    0,                   // CfgLvdsMiscControl
    0,          // CfgLvdsMiscControl
    0,        // CfgLvdsMiscControl
    0,  // CfgLvdsMiscControl
    0                                     // Reserved
  },
  0,      // CfgPcieRefClkSpreadSpectrum
  0,             // CfgExternalVrefCtlFeature
  0,                 // CfgForceTrainMode
  0,       // CfgGnbRemoteDisplaySupport
  0, // CfgIvrsExclusionRangeList
  0,         // CfgGnbSyncFloodPinAsNmi
  0,       // CfgIgpuEnableDisablePolicy
  0,    // CfgGnbSwTjOffset
  0,        // CfgLvdsMiscVoltAdjustment
  {
    0,                                       // Reserved
    0, // CfgDisplayMiscControl.VbiosFastBootEn
    0,                                       // Reserved
  },
  0,              // CfgDpFixedVoltSwingType
  CFG_DIMM_TYPE_USED_IN_MIXED_CONFIG,   // CfgDimmTypeUsedInMixedConfig
  CFG_DIMM_TYPE_DDR4_CAPABLE,           // CfgDimmTypeDdr4Capable
  CFG_DIMM_TYPE_DDR3_CAPABLE,           // CfgDimmTypeDdr3Capable
  CFG_HYBRID_BOOST_ENABLE,              // CfgHybridBoostEnable
  CFG_GNB_IOAPIC_ADDRESS,               // CfgGnbIoapicAddress
  CFG_ENABLE_DATA_EYE,                  // CfgDataEyeEn
  CFG_BATTERY_BOOST_TUNE,               // CfgBatteryBoostTune
  CFG_DRAM_DOUBLE_REFRESH_RATE,         // CfgDramDoubleRefreshRateEn
  0,                       // CfgGnbResolution
  0,                         // CfgGnbAcpSize
  CFG_PMU_TRAIN_MODE,                   // CfgPmuTrainMode
  CFG_MEMORY_PHY_VOLTAGE,               // CfgMemoryPhyVoltage
  CFG_GPU_FREQUENCY_LIMIT,              // CfgGpuFrequencyLimit
  CFG_MAX_NUM_AUDIO_ENDPOINTS,          // CfgMaxNumAudioEndpoints
  CFG_BAPM_ENABLE,                      // CfgBapmEnable
  CFG_GNB_AZ_I2SBUS_SELECT,             // CfgGnbAzI2sBusSelect
  CFG_GNB_AZ_I2SBUS_PIN_CONFIG,         // CfgGnbAzI2sBusPinConfig
  CFG_PPT_LIMIT_AC,                     // CfgPkgPwrLimitAC
  CFG_PPT_LIMIT_DC,                     // CfgPkgPwrLimitDC
  CFG_SYSTEM_CONFIGURATION,             // CfgSystemConfiguration
  { // STAPM paramters
    CFG_STAPM_SCALAR,                   // CfgStapmScalar
    CFG_STAPM_BOOST,                    // CfgStapmBoost
    CFG_STAPM_TIME_CONSTANT             // CfgStapmTimeConstant
  },
  0,                 // CfgEDPv1_4VSMode
  0,     // CfgExtHDMIReDrvSlvAddr
  CFG_EXT_HDMI_RE_DRIVE_REG_NUM,        // CfgExtHDMIReDrvRegNum
  (UINT64)CFG_EXT_HDMI_RE_DRIVE_REG_INFO,       // CfgExtHDMIRegSetting
  CFG_THERMCTL_LIMIT,                   // CfgThermCtlLimit
  (UINT64)CFG_CODEC_VERB_TABLE,         // CfgCodecVerbTable
  CFG_GNB_AZ_SSID,                      // CfgGnbAzSsid
  CFG_CUSTOM_VDDIO_VOLTAGE,             // CfgCustomVddioVoltage
  CFG_ACP_POWER_GATING,                 // CfgAcpPowerGating
  0,                                    //reserved...
};

