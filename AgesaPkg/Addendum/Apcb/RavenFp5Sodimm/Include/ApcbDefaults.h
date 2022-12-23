/* $NoKeywords:$ */
/**
 * @file
 *
 * ApcbCustomizedDefinitions.h
 *
 * AGESA PSP Customization Block Data Intializer
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: ApcbGenerator
 * @e \$Revision: 192403 $ @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
 *
 **/
/*****************************************************************************
*
* Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
*
*/
//
// OEM CUSTOMIZABLE DEFINITIONS. Any changes must be done here...
//

#ifndef _APCB_DEFAULTS_H_
#define _APCB_DEFAULTS_H_

#ifndef BLDCFG_FAMILY_ALL
  #define BLDCFG_FAMILY_ALL                         AMD_FAMILY_17_ALL
#endif
#ifndef BLDCFG_FAMILY_APCB
  #define BLDCFG_FAMILY_APCB                        AMD_F17_ALL_APCB
#endif

#ifndef BLDCFG_EXTERNAL_PARAMS_DEF_ENABLED
  #define BLDCFG_EXTERNAL_PARAMS_DEF_ENABLED        TRUE
#endif
#ifndef BLDCFG_EXTERNAL_PARAMS_ENABLED
  #define BLDCFG_EXTERNAL_PARAMS_ENABLED            FALSE
#endif
#ifndef BLDCFG_INTERNAL_PARAMS_DEF_ENABLED
  #define BLDCFG_INTERNAL_PARAMS_DEF_ENABLED        TRUE
#endif
#ifndef BLDCFG_INTERNAL_PARAMS_ENABLED
  #define BLDCFG_INTERNAL_PARAMS_ENABLED            FALSE
#endif


#ifndef BLDCFG_BOTTOM_IO
  #define BLDCFG_BOTTOM_IO                          0xE0
#endif
#ifndef BLDCFG_MEM_HOLE_REMAPPING
  #define BLDCFG_MEM_HOLE_REMAPPING                 TRUE
#endif
#ifndef BLDCFG_MEM_LIMIT_1TB
  #define BLDCFG_MEM_LIMIT_1TB                      TRUE
#endif
#ifndef BLDCFG_TIMING_MODE_SELECT
  #define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#endif
#ifndef BLDCFG_MEMORY_CLOCK_SELECT
  #define BLDCFG_MEMORY_CLOCK_SELECT                DDR3200_FREQUENCY
#endif
#ifndef BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING
  #define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#endif
#ifndef BLDCFG_MEMORY_CHANNEL_INTERLEAVING
  #define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        FALSE
#endif
#ifndef BLDCFG_ENABLE_ECC_FEATURE
  #define BLDCFG_ENABLE_ECC_FEATURE                 FALSE
#endif
#ifndef BLDCFG_MEMORY_POWER_DOWN
  #define BLDCFG_MEMORY_POWER_DOWN                  TRUE
#endif
#ifndef BLDCFG_PARITY_CONTROL
  #define BLDCFG_PARITY_CONTROL                     TRUE
#endif
#ifndef BLDCFG_BANK_SWIZZLE
  #define BLDCFG_BANK_SWIZZLE                       TRUE
#endif
#ifndef BLDCFG_ENABLE_MEM_CLR
  #define BLDCFG_ENABLE_MEM_CLR                     FALSE
#endif
#ifndef BLDCFG_ENABLE_MEMPSTATE
  #define BLDCFG_ENABLE_MEMPSTATE                   TRUE
#endif
#ifndef BLDCFG_SOLDERDOWN_DRAM
  #define BLDCFG_SOLDERDOWN_DRAM                    FALSE
#endif
#ifndef BLDCFG_UMA_MODE
  #define BLDCFG_UMA_MODE                           UMA_AUTO
#endif
#ifndef BLDCFG_UMA_SIZE
  #define BLDCFG_UMA_SIZE                           0
#endif
#ifndef BLDCFG_GFX_UMA_FRAME_BUFFER_SIZE
  #define BLDCFG_GFX_UMA_FRAME_BUFFER_SIZE          (BLDCFG_UMA_SIZE >> 20)
#endif
#ifndef BLDCFG_UMA_VERSION
  #define BLDCFG_UMA_VERSION                        UMA_NON_LEGACY
#endif
#ifndef BLDCFG_DISPLAY_RESOLUTION
  #define BLDCFG_DISPLAY_RESOLUTION                 DISPLAY_1920x1080_And_Below
#endif
#ifndef BLDCFG_MEMORY_RESTORE_CONTROL
  #define BLDCFG_MEMORY_RESTORE_CONTROL             TRUE
#endif
#ifndef BLDCFG_SAVE_MEMORY_CONTEXT_CONTROL
  #define BLDCFG_SAVE_MEMORY_CONTEXT_CONTROL        TRUE
#endif
#ifndef BLDCFG_IS_CAPSULE_MODE
  #define BLDCFG_IS_CAPSULE_MODE                    TRUE
#endif
#ifndef BLDCFG_FORCE_TRAIN_MODE
  #define BLDCFG_FORCE_TRAIN_MODE                   FORCE_TRAIN_AUTO
#endif
#ifndef BLDCFG_DIMM_TYPE_TECHNOLGY
  #define BLDCFG_DIMM_TYPE_TECHNOLGY                DDR4_TECHNOLOGY
#endif
#ifndef BLDCFG_AMP_MODE_ENABLE
  #define BLDCFG_AMP_MODE_ENABLE                    TRUE
#endif
#ifndef BLDCFG_DRAM_DOUBLE_REFRESH_RATE
  #define BLDCFG_DRAM_DOUBLE_REFRESH_RATE           FALSE
#endif
#ifndef BLDCFG_PMU_TRAINING_MODE
  #define BLDCFG_PMU_TRAINING_MODE                  PMU_TRAIN_1D
#endif
#ifndef BLDCFG_ECC_REDIRECTION
  #define BLDCFG_ECC_REDIRECTION                    FALSE
#endif
#ifndef BLDCFG_SCRUB_DRAM_RATE
  #define BLDCFG_SCRUB_DRAM_RATE                    0
#endif
#ifndef BLDCFG_SCRUB_L2_RATE
  #define BLDCFG_SCRUB_L2_RATE                      0
#endif
#ifndef BLDCFG_SCRUB_L3_RATE
  #define BLDCFG_SCRUB_L3_RATE                      0
#endif
#ifndef BLDCFG_SCRUB_IC_RATE
  #define BLDCFG_SCRUB_IC_RATE                      0
#endif
#ifndef BLDCFG_SCRUB_DC_RATE
  #define BLDCFG_SCRUB_DC_RATE                      0
#endif
#ifndef BLDCFG_ECC_SYNC_FLOOD
  #define BLDCFG_ECC_SYNC_FLOOD                     0
#endif
#ifndef BLDCFG_ECC_SYMBOL_SIZE
  #define BLDCFG_ECC_SYMBOL_SIZE                    0
#endif
#ifndef BLDCFG_DQS_TRAINING_CONTROL
  #define BLDCFG_DQS_TRAINING_CONTROL               TRUE
#endif
#ifndef BLDCFG_UMA_ABOVE_4GB
  #define BLDCFG_UMA_ABOVE_4GB                      TRUE
#endif
#ifndef BLDCFG_UMA_BUFFER_ALIGNMENT
  #define BLDCFG_UMA_BUFFER_ALIGNMENT               UMA_4MB_ALIGNED
#endif
#ifndef BLDCFG_MEMORY_ALL_CLOCKS_ON
  #define BLDCFG_MEMORY_ALL_CLOCKS_ON               FALSE
#endif
#ifndef BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT
  #define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR3200_FREQUENCY
#endif
#ifndef BLDCFG_POWER_DOWN_MODE
  #define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHANNEL
#endif
#ifndef BLDCFG_IGNORE_SPD_CHECKSUM
  #define BLDCFG_IGNORE_SPD_CHECKSUM                TRUE
#endif
#ifndef BLDCFG_MEMORY_MODE_UNGANGED
  #define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#endif
#ifndef BLDCFG_MEMORY_QUAD_RANK_CAPABLE
  #define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           TRUE
#endif
#ifndef BLDCFG_MEMORY_RDIMM_CAPABLE
  #define BLDCFG_MEMORY_RDIMM_CAPABLE               TRUE
#endif
#ifndef BLDCFG_MEMORY_LRDIMM_CAPABLE
  #define BLDCFG_MEMORY_LRDIMM_CAPABLE              TRUE
#endif
#ifndef BLDCFG_MEMORY_UDIMM_CAPABLE
  #define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#endif
#ifndef BLDCFG_MEMORY_SODIMM_CAPABLE
  #define BLDCFG_MEMORY_SODIMM_CAPABLE              TRUE
#endif
#ifndef BLDCFG_DRAM_DOUBLE_REFRESH_RATE_ENABLE
  #define BLDCFG_DRAM_DOUBLE_REFRESH_RATE_ENABLE    FALSE
#endif
#ifndef BLDCFG_MEMORY_DDR4_CAPABLE
  #define BLDCFG_MEMORY_DDR4_CAPABLE                TRUE
#endif
#ifndef BLDCFG_MEMORY_DDR3_CAPABLE
  #define BLDCFG_MEMORY_DDR3_CAPABLE                FALSE
#endif
#ifndef BLDCFG_MEMORY_LPDDR3_CAPABLE
  #define BLDCFG_MEMORY_LPDDR3_CAPABLE              FALSE
#endif
#ifndef BLDCFG_ZQ_RESET_CONTROL_ENABLE
  #define BLDCFG_ZQ_RESET_CONTROL_ENABLE            TRUE
#endif
#ifndef BLDCFG_BANK_GROUP_SWAP_MODE
  #define BLDCFG_BANK_GROUP_SWAP_MODE               BANK_GROUP_SWAP_APU
#endif
#ifndef BLDCFG_ODT_CMD_THROT_ENABLE
  #define BLDCFG_ODT_CMD_THROT_ENABLE               FALSE
#endif
#ifndef BLDCFG_SW_CMD_THROT_ENABLE
  #define BLDCFG_SW_CMD_THROT_ENABLE                0
#endif
#ifndef BLDCFG_FORCE_POWER_DOWN_THROT_ENABLE
  #define BLDCFG_FORCE_POWER_DOWN_THROT_ENABLE      0
#endif
#ifndef BLDCFG_ODT_CMD_THROT_CYCLE
  #define BLDCFG_ODT_CMD_THROT_CYCLE                0
#endif
#ifndef BLDCFG_SW_CMD_THROT_CYCLE
  #define BLDCFG_SW_CMD_THROT_CYCLE                 0
#endif
#ifndef BLDCFG_DIMM_SENSOR_CONFIGURATION
  #define BLDCFG_DIMM_SENSOR_CONFIGURATION          0
#endif
#ifndef BLDCFG_DIMM_SENSOR_UPPER
  #define BLDCFG_DIMM_SENSOR_UPPER                  0
#endif
#ifndef BLDCFG_DIMM_SENSOR_LOWER
  #define BLDCFG_DIMM_SENSOR_LOWER                  0
#endif
#ifndef BLDCFG_DIMM_SENSOR_CRITICAL
  #define BLDCFG_DIMM_SENSOR_CRITICAL               0
#endif
#ifndef BLDCFG_DIMM_SENSOR_RESOLUTION
  #define BLDCFG_DIMM_SENSOR_RESOLUTION             0
#endif
#ifndef BLDCFG_AUTO_REF_FINE_GRAN_MODE
  #define BLDCFG_AUTO_REF_FINE_GRAN_MODE            0
#endif
#ifndef BLDCFG_ENABLE_DDRROUTEBALANCEDTEE
  #define BLDCFG_ENABLE_DDRROUTEBALANCEDTEE            FALSE
#endif
#ifndef BLDCFG_TEMP_CONTROLLED_REFRESH_EN
  #define BLDCFG_TEMP_CONTROLLED_REFRESH_EN            TRUE
#endif
#ifndef BLDCFG_MEMRESTORE_VALID_DAYS
  #define BLDCFG_MEMRESTORE_VALID_DAYS              30
#endif
#ifndef BLDCFG_DDR_ROUTE_BALANCED_TEE
  #define BLDCFG_DDR_ROUTE_BALANCED_TEE             FALSE
  #ifdef BLDCFG_ENABLE_DDRROUTEBALANCEDTEE
    #undef BLDCFG_DDR_ROUTE_BALANCED_TEE
    #define BLDCFG_DDR_ROUTE_BALANCED_TEE           BLDCFG_ENABLE_DDRROUTEBALANCEDTEE
  #endif
#endif
#ifndef BLDCFG_MEM_TSME_ENABLE
  #define BLDCFG_MEM_TSME_ENABLE                    FALSE
#endif
#ifndef BLDCFG_FCH_ASSERT_ENABLE
  #define BLDCFG_FCH_ASSERT_ENABLE                  FALSE
#endif
#ifndef BLDCFG_FCH_TURTLE_BOOT_ENABLE
  #define BLDCFG_FCH_TURTLE_BOOT_ENABLE             FALSE
#endif
#ifndef BLDCFG_FCH_ELEVATE_SMBUS_CLOCK
  #define BLDCFG_FCH_ELEVATE_SMBUS_CLOCK            FALSE
#endif
#ifndef BLDCFG_MEM_FORCE_DATA_MASK_DISABLE
  #define BLDCFG_MEM_FORCE_DATA_MASK_DISABLE        FALSE
#endif
#ifndef BLDCFG_MEM_MBIST_TEST_ENABLE
  #define BLDCFG_MEM_MBIST_TEST_ENABLE              FALSE
#endif
#ifndef BLDCFG_MEM_MBIST_SUBTEST_TYPE
  #define BLDCFG_MEM_MBIST_SUBTEST_TYPE             0
#endif
#ifndef BLDCFG_MEM_MBIST_HALT_ON_ERROR
  #define BLDCFG_MEM_MBIST_HALT_ON_ERROR            FALSE
#endif
#ifndef BLDCFG_MEM_MBIST_AGGRESOR_ON
  #define BLDCFG_MEM_MBIST_AGGRESOR_ON              FALSE
#endif
#ifndef BLDCFG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT
  #define BLDCFG_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORT 0
#endif
#ifndef BLDCFG_MEM_CPU_VREF_RANGE
  #define BLDCFG_MEM_CPU_VREF_RANGE                 0
#endif
#ifndef BLDCFG_MEM_DRAM_VREF_RANGE
  #define BLDCFG_MEM_DRAM_VREF_RANGE                0
#endif
#ifndef BLDCFG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN
  #define BLDCFG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN FALSE
#endif
#ifndef BLDCFG_FCH_ESPI_ABL_INIT_ENABLE
  #define BLDCFG_FCH_ESPI_ABL_INIT_ENABLE                            TRUE
#endif
#ifndef BLDCFG_FCH_ESPI_IO80_ENABLE
  #define BLDCFG_FCH_ESPI_IO80_ENABLE                                FALSE
#endif
#ifndef BLDCFG_FCH_ESPI_KBC6064_ENABLE
  #define BLDCFG_FCH_ESPI_KBC6064_ENABLE                             TRUE
#endif
#ifndef BLDCFG_FCH_ESPI_CLOCK
  #define BLDCFG_FCH_ESPI_CLOCK                                      0x0F
#endif
#ifndef BLDCFG_FCH_ESPI_IOMODE
  #define BLDCFG_FCH_ESPI_IOMODE                                     0x0F
#endif
#ifndef BLDCFG_FCH_ESPI_ALERT_MODE
  #define BLDCFG_FCH_ESPI_ALERT_MODE                                  ESPI_ALERT_MODE_VAL_ALERT_PIN
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE0_SIZE
  #define BLDCFG_FCH_ESPI_IORANGE0_SIZE                               0
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE0_BASE
  #define BLDCFG_FCH_ESPI_IORANGE0_BASE                               0x4F
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE1_SIZE
  #define BLDCFG_FCH_ESPI_IORANGE1_SIZE                               0
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE1_BASE
  #define BLDCFG_FCH_ESPI_IORANGE1_BASE                               0x4E
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE2_SIZE
  #define BLDCFG_FCH_ESPI_IORANGE2_SIZE                               0xFF
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE2_BASE
  #define BLDCFG_FCH_ESPI_IORANGE2_BASE                               0x600
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE3_SIZE
  #define BLDCFG_FCH_ESPI_IORANGE3_SIZE                               0
#endif
#ifndef BLDCFG_FCH_ESPI_IORANGE3_BASE
  #define BLDCFG_FCH_ESPI_IORANGE3_BASE                               0x4C
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE0_SIZE
  #define BLDCFG_FCH_ESPI_MMIORANGE0_SIZE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE0_BASE
  #define BLDCFG_FCH_ESPI_MMIORANGE0_BASE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE1_SIZE
  #define BLDCFG_FCH_ESPI_MMIORANGE1_SIZE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE1_BASE
  #define BLDCFG_FCH_ESPI_MMIORANGE1_BASE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE2_SIZE
  #define BLDCFG_FCH_ESPI_MMIORANGE2_SIZE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE2_BASE
  #define BLDCFG_FCH_ESPI_MMIORANGE2_BASE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE3_SIZE
  #define BLDCFG_FCH_ESPI_MMIORANGE3_SIZE                             0
#endif
#ifndef BLDCFG_FCH_ESPI_MMIORANGE3_BASE
  #define BLDCFG_FCH_ESPI_MMIORANGE3_BASE                             0
#endif
#ifndef BLDCFG_PMU_TRAIN_ERROR_RECOVERY
  #define BLDCFG_PMU_TRAIN_ERROR_RECOVERY           TRUE
#endif
#ifndef BLDCFG_DF_MEM_CLEAR
  #define BLDCFG_DF_MEM_CLEAR             FALSE
#endif
#ifndef BLDCFG_MEM_CLK_MAP
  #define BLDCFG_MEM_CLK_MAP            { MEMCLK_DIS_MAP(ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)} // MemClkDisMap
#endif
#ifndef BLDCFG_CKE_TRI_MAP
  #define BLDCFG_CKE_TRI_MAP            { CKE_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x05, 0x0A, 0xFF, 0xFF) }                           // CkeTriMap
#endif
#ifndef BLDCFG_ODT_TRI_MAP
  #define BLDCFG_ODT_TRI_MAP            { ODT_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00) }                           // OdtTriMap
#endif
#ifndef BLDCFG_CS_TRI_MAP
  #define BLDCFG_CS_TRI_MAP             { CS_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00) }    // CsTriMap
#endif
#ifndef BLDCFG_NUM_DIMMS_SUPPORTED
  #define BLDCFG_NUM_DIMMS_SUPPORTED    { NUMBER_OF_DIMMS_SUPPORTED(ANY_SOCKET, ANY_CHANNEL, 2) }                                  // NumberDimmSupported
#endif
#ifndef BLDCFG_NUM_SOLDERED_DOWN_DIMM_SUPPORTED
  #define BLDCFG_NUM_SOLDERED_DOWN_DIMM_SUPPORTED      { 0, 0, 0, 0, 0, 0 }                                                        // NumberSolderedDownDimmsSupported
#endif
#ifndef BLDCFG_NUM_CS_SUPPORTED
  #define BLDCFG_NUM_CS_SUPPORTED       { 0, 0, 0, 0, 0, 0 }                                                                       // NumberChipSelectsSupported
#endif

#ifndef BLDCFG_NUM_CHNL_SUPPORTED
  #define BLDCFG_NUM_CHNL_SUPPORTED     { NUMBER_OF_CHANNELS_SUPPORTED(ANY_SOCKET, 2) }                                            // NumberChannelsSupported
#endif
#ifndef BLDCFG_BUS_SPEED_OVERRIDE
  #define BLDCFG_BUS_SPEED_OVERRIDE     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }                                                  // OverrideBusSpeed
#endif
#ifndef BLDCFG_DRAM_TECH_OVERRIDE
  #define BLDCFG_DRAM_TECH_OVERRIDE     { 0, 0, 0, 0, 0, 0, 0, 0, 0 }                                                              // DramTechnology
#endif
#ifndef BLDCFG_SOLDRD_DOWN_DIMM_TYPE
  #define BLDCFG_SOLDRD_DOWN_DIMM_TYPE  { 0, 0, 0, 0, 0, 0 }                                                                       // SolderedDownSoDimmType
#endif
#ifndef BLDCFG_MEM_POWER_POLICY_OVERRIDE
  #define BLDCFG_MEM_POWER_POLICY_OVERRIDE  { 0, 0, 0, 0, 0, 0 }                                                                   // MemoryPowerPolicyOverride
#endif
#ifndef BLDCFG_NUM_MOTHERBOARD_LAYERS
  #define BLDCFG_NUM_MOTHERBOARD_LAYERS { 0, 0, 0, 0, 0, 0 }                                                                        // MotherboardLayers
#endif

#ifndef BLDCFG_MEMORY_QUADRANK_TYPE
  #define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_UNBUFFERED
#endif
#ifndef BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING
  #define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE
#endif

#ifndef BLDCFG_ONLINE_SPARE
  #define BLDCFG_ONLINE_SPARE                       FALSE
#endif
#ifndef BLDCFG_USE_BURST_MODE
  #define BLDCFG_USE_BURST_MODE                     FALSE
#endif
#ifndef BLDCFG_HEAP_DRAM_ADDRESS
  #define BLDCFG_HEAP_DRAM_ADDRESS                  0xB0000ul
#endif
#ifndef BLDCFG_1GB_ALIGN
  #define BLDCFG_1GB_ALIGN                          FALSE
#endif
#ifndef BLDCFG_UMA_ALIGNMENT
  #define BLDCFG_UMA_ALIGNMENT                      UMA_4MB_ALIGNED
#endif
#ifndef BLDCFG_DIMM_TYPE_PACKAGE
  #define BLDCFG_DIMM_TYPE_PACKAGE                  UDIMM_PACKAGE
#endif

//
// Please Review the below SMBUS Address, based off your schematics and comment out lines which doesnt belongs
// to the project for which this fie is being customized
//

#ifndef BLDCFG_SPD_CH_A_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_A_DIMM0_ADDRESS      0xA0
#endif
#ifndef BLDCFG_SPD_CH_A_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_A_DIMM1_ADDRESS      0xA4
#endif

#ifndef BLDCFG_SPD_CH_B_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_B_DIMM0_ADDRESS      0xA2
#endif
#ifndef BLDCFG_SPD_CH_B_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_B_DIMM1_ADDRESS      0xA6
#endif

#ifndef BLDCFG_SPD_CH_C_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_C_DIMM0_ADDRESS      0xA8
#endif
#ifndef BLDCFG_SPD_CH_C_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_C_DIMM1_ADDRESS      0xAC
#endif

#ifndef BLDCFG_SPD_CH_D_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_D_DIMM0_ADDRESS      0xAA
#endif
#ifndef BLDCFG_SPD_CH_D_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_D_DIMM1_ADDRESS      0xAE
#endif

#ifndef BLDCFG_SPD_CH_E_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_E_DIMM0_ADDRESS      0xA0
#endif
#ifndef BLDCFG_SPD_CH_E_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_E_DIMM1_ADDRESS      0xA4
#endif

#ifndef BLDCFG_SPD_CH_F_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_F_DIMM0_ADDRESS      0xA2
#endif
#ifndef BLDCFG_SPD_CH_F_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_F_DIMM1_ADDRESS      0xA6
#endif

#ifndef BLDCFG_SPD_CH_G_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_G_DIMM0_ADDRESS      0xA8
#endif
#ifndef BLDCFG_SPD_CH_G_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_G_DIMM1_ADDRESS      0xAC
#endif

#ifndef BLDCFG_SPD_CH_H_DIMM0_ADDRESS
  #define BLDCFG_SPD_CH_H_DIMM0_ADDRESS      0xAA
#endif
#ifndef BLDCFG_SPD_CH_H_DIMM1_ADDRESS
  #define BLDCFG_SPD_CH_H_DIMM1_ADDRESS      0xAE
#endif

#ifndef BLDCFG_MEM_LAYOOUT_TYPE
  #define BLDCFG_MEM_LAYOOUT_TYPE           MEMORY_LAYOUT_TYPE_DIMM
#endif


#ifndef BLDCFG_I2C_MUX_ADRRESS
  #define BLDCFG_I2C_MUX_ADRRESS            0x94
#endif
#ifndef BLDCFG_I2C_CHANNEL_1
  #define BLDCFG_I2C_CHANNEL_1               1
#endif
#ifndef BLDCFG_I2C_CHANNEL_2
  #define BLDCFG_I2C_CHANNEL_2               2
#endif
#ifndef BLDCFG_I2C_CHANNEL_3
  #define BLDCFG_I2C_CHANNEL_3               3
#endif
#ifndef BLDCFG_I2C_CHANNEL_4
  #define BLDCFG_I2C_CHANNEL_4               4
#endif

#ifndef BLDCFG_CCX_MIN_SEV_ASID
  #define BLDCFG_CCX_MIN_SEV_ASID              0x0000
#endif

#ifndef BLDCFG_DF_GMI_ENCRYPT
  #define BLDCFG_DF_GMI_ENCRYPT               3
#endif
#ifndef BLDCFG_DF_XGMI_ENCRYPT
  #define BLDCFG_DF_XGMI_ENCRYPT              3
#endif
#ifndef BLDCFG_DF_SAVE_RESTORE_MEM_ENCRYPT
  #define BLDCFG_DF_SAVE_RESTORE_MEM_ENCRYPT  3
#endif
#ifndef BLDCFG_DF_SYS_STORAGE_AT_TOM
  #define BLDCFG_DF_SYS_STORAGE_AT_TOM        3
#endif
#ifndef BLDCFG_DF_PROBE_FILTER_ENABLE
  #define BLDCFG_DF_PROBE_FILTER_ENABLE       3
#endif
#ifndef BLDCFG_DF_BOTTOM_IO
  #define BLDCFG_DF_BOTTOM_IO                 0xE0
#endif
#ifndef BLDCFG_DF_MEM_INTERLEAVING
  #define BLDCFG_DF_MEM_INTERLEAVING          7
#endif
#ifndef BLDCFG_DF_DRAM_INTLV_SIZE
  #define BLDCFG_DF_DRAM_INTLV_SIZE           7
#endif
#ifndef BLDCFG_DF_CHAN_INTLV_HASH_EN
  #define BLDCFG_DF_CHAN_INTLV_HASH_EN        3
#endif
#ifndef BLDCFG_DF_PCI_MMIO_SIZE
  #define BLDCFG_DF_PCI_MMIO_SIZE             0x10000000
#endif
#ifndef BLDCFG_DF_CAKE_CRC_THRESH_PERF_BOUNDS
  #define BLDCFG_DF_CAKE_CRC_THRESH_PERF_BOUNDS  100  // 0.001%
#endif

//
// UART Enable Disable through SOC UART/ LPC-SUPER IO
// 0 - LPC UART, 1 - SOC UART0
//
#ifndef BLDCFG_FCH_CONSOLE_OUT_ENABLE
  #define BLDCFG_FCH_CONSOLE_OUT_ENABLE         0
#endif

#ifndef BLDCFG_FCH_CONSOLE_OUT_SERIAL_PORT
  #define BLDCFG_FCH_CONSOLE_OUT_SERIAL_PORT    0
#endif

#ifndef BLDCFG_FCH_UART_BAUD_RATE
  #define BLDCFG_FCH_UART_BAUD_RATE             115200
#endif

//#define BLDCFG_CONOUTCTRL_BREAKPOINT          FALSE
//#define BLDCFG_CONOUTCTRL_BREAKPOINT_ALLDIE   FALSE

#endif   //ifndef  _APCB_DEFAULTS_H_


