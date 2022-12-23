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
* Copyright 2016 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting You permission to use this software and documentation (if
* any) (collectively, the "Software") pursuant to the terms and conditions of
* the Software License Agreement included with the Software. If You do not have
* a copy of the Software License Agreement, contact Your AMD representative for
* a copy.
*
* You agree that You will not reverse engineer or decompile the Software, in
* whole or in part, except as allowed by applicable law.
*
* WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
* ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
* INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
* ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
* ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
* warranties, so the above exclusion may not apply to You, but only to the
* extent required by law.
*
* LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
* APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
* LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
* CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
* OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
* ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
* INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
* LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
* FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
* INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
* PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
* You for all damages, losses, and causes of action (whether in contract, tort
* (including negligence) or otherwise) exceed the amount of $50 USD. You agree
* to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
* and their respective licensors, directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your
* possession or use of the Software or violation of the terms and conditions of
* this Agreement.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
* Software and related documentation are "commercial items", as that term is
* defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
* software" and "commercial computer software documentation", as such terms are
* used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
* respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
* 227.7202-1 through 227.7202-4, as applicable, the commercial computer
* software and commercial computer software documentation are being licensed to
* U.S. Government end users: (a) only as commercial items, and (b) with only
* those rights as are granted to all other end users pursuant to the terms and
* conditions set forth in this Agreement. Unpublished rights are reserved under
* the copyright laws of the United States.
*
* EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
* laws and regulations, as well as the import/export control laws and
* regulations of other countries as applicable. You further agree You will not
* export, re-export, or transfer, directly or indirectly, any product,
* technical data, software or source code received from AMD under this license,
* or the direct product of such technical data or software to any country for
* which the United States or any other applicable government requires an export
* license or other governmental approval without first obtaining such licenses
* or approvals, or in violation of any applicable laws or regulations of the
* United States or the country where the technical data or software was
* obtained. You acknowledges the technical data and software received will not,
* in the absence of authorization from U.S. or local law and regulations as
* applicable, be used by or exported, re-exported or transferred to: (i) any
* sanctioned or embargoed country, or to nationals or residents of such
* countries; (ii) any restricted end-user as identified on any applicable
* government end-user list; or (iii) any party where the end-use involves
* nuclear, chemical/biological weapons, rocket systems, or unmanned air
* vehicles.  For the most current Country Group listings, or for additional
* information about the EAR or Your obligations under those regulations, please
* refer to the website of the U.S. Bureau of Industry and Security at
* http://www.bis.doc.gov/.
*******************************************************************************
*
*/
//
// OEM CUSTOMIZABLE DEFINITIONS. Any changes must be done here...
//

#ifndef _APCB_CUSTOMIZED_DEFINITIONS_H_
#define _APCB_CUSTOMIZED_DEFINITIONS_H_
//AMI porting>
#include "token.h"

#define BLDCFG_FAMILY_ALL                         AMD_FAMILY_17_ALL
#define BLDCFG_FAMILY_APCB                        AMD_F17_ALL_APCB

#define BLDCFG_EXTERNAL_PARAMS_DEF_ENABLED        TRUE
#define BLDCFG_EXTERNAL_PARAMS_ENABLED            FALSE
#define BLDCFG_INTERNAL_PARAMS_DEF_ENABLED        TRUE
#define BLDCFG_INTERNAL_PARAMS_ENABLED            FALSE


#define BLDCFG_BOTTOM_IO                          0xD0
#define BLDCFG_MEM_HOLE_REMAPPING                 TRUE
#define BLDCFG_MEM_LIMIT_1TB                      TRUE
#define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#define BLDCFG_MEMORY_CLOCK_SELECT                DDR2400_FREQUENCY
#define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        FALSE
#define BLDCFG_ENABLE_ECC_FEATURE                 TRUE
#define BLDCFG_MEMORY_POWER_DOWN                  TRUE
#define BLDCFG_PARITY_CONTROL                     FALSE
#define BLDCFG_BANK_SWIZZLE                       TRUE
#define BLDCFG_ENABLE_MEM_CLR                     FALSE
#define BLDCFG_UMA_MODE                           UMA_AUTO
#define BLDCFG_UMA_SIZE                           0x10000000
#define BLDCFG_UMA_VERSION                        UMA_NON_LEGACY
#define BLDCFG_DISPLAY_RESOLUTION                 DISPLAY_1920x1080_And_Below
#define BLDCFG_MEMORY_RESTORE_CONTROL             TRUE
#define BLDCFG_SAVE_MEMORY_CONTEXT_CONTROL        TRUE
#define BLDCFG_IS_CAPSULE_MODE                    TRUE
#define BLDCFG_FORCE_TRAIN_MODE                   FORCE_TRAIN_AUTO
#define BLDCFG_DIMM_TYPE_TECHNOLGY                DDR4_TECHNOLOGY
#define BLDCFG_AMP_MODE_ENABLE                    TRUE
#define BLDCFG_DRAM_DOUBLE_REFRESH_RATE           FALSE
#define BLDCFG_PMU_TRAINING_MODE                  PMU_TRAIN_1D_2D
#define BLDCFG_ECC_REDIRECTION                    FALSE
#define BLDCFG_SCRUB_DRAM_RATE                    0
#define BLDCFG_SCRUB_L2_RATE                      0
#define BLDCFG_SCRUB_L3_RATE                      0
#define BLDCFG_SCRUB_IC_RATE                      0
#define BLDCFG_SCRUB_DC_RATE                      0
#define BLDCFG_ECC_SYNC_FLOOD                     1
#define BLDCFG_ECC_SYMBOL_SIZE                    1
#define BLDCFG_DQS_TRAINING_CONTROL               TRUE
#define BLDCFG_UMA_ABOVE_4GB                      TRUE
#define BLDCFG_UMA_BUFFER_ALIGNMENT               UMA_4MB_ALIGNED
#define BLDCFG_MEMORY_ALL_CLOCKS_ON               FALSE
#define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR3200_FREQUENCY
#define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHANNEL
#define BLDCFG_IGNORE_SPD_CHECKSUM                TRUE
#define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           TRUE
#define BLDCFG_MEMORY_RDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_LRDIMM_CAPABLE              TRUE
#define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE              TRUE
#define BLDCFG_DRAM_DOUBLE_REFRESH_RATE_ENABLE    FALSE
#define BLDCFG_MEMORY_DDR4_CAPABLE                TRUE
#define BLDCFG_MEMORY_DDR3_CAPABLE                FALSE
#define BLDCFG_MEMORY_LPDDR3_CAPABLE              FALSE
#define BLDCFG_ZQ_RESET_CONTROL_ENABLE            TRUE
#define BLDCFG_BANK_GROUP_SWAP_MODE               BANK_GROUP_SWAP_APU
#define BLDCFG_ODT_CMD_THROT_ENABLE               FALSE
#define BLDCFG_SW_CMD_THROT_ENABLE                0
#define BLDCFG_FORCE_POWER_DOWN_THROT_ENABLE      0
#define BLDCFG_ODT_CMD_THROT_CYCLE                0
#define BLDCFG_SW_CMD_THROT_CYCLE                 0
#define BLDCFG_DIMM_SENSOR_CONFIGURATION          0
#define BLDCFG_DIMM_SENSOR_UPPER                  0
#define BLDCFG_DIMM_SENSOR_LOWER                  0
#define BLDCFG_DIMM_SENSOR_CRITICAL               0
#define BLDCFG_DIMM_SENSOR_RESOLUTION             0
#define BLDCFG_AUTO_REF_FINE_GRAN_MODE            0
#define BLDCFG_ENABLE_MEMPSTATE                   TRUE
#define BLDCFG_ENABLE_DDRROUTEBALANCEDTEE         FALSE

#define BLDCFG_MEM_PS_ERROR_HANDLING              0

#define BLDCFG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN TRUE

#define BLDCFG_MEM_CLK_MAP            { MEMCLK_DIS_MAP(ANY_SOCKET, ANY_CHANNEL, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00)} // MemClkDisMap
#define BLDCFG_CKE_TRI_MAP            { CKE_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x00, 0x01, 0x02, 0x03) }                           // CkeTriMap
#define BLDCFG_ODT_TRI_MAP            { ODT_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x00, 0x01, 0x02, 0x03) }                           // OdtTriMap
#define BLDCFG_CS_TRI_MAP             { CS_TRI_MAP(ANY_SOCKET, ANY_CHANNEL, 0x00, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00) }    // CsTriMap
#define BLDCFG_NUM_DIMMS_SUPPORTED    { NUMBER_OF_DIMMS_SUPPORTED(ANY_SOCKET, ANY_CHANNEL, 1) }                                  // NumberDimmSupported
#define BLDCFG_NUM_SOLDERED_DOWN_DIMM_SUPPORTED      { 0, 0, 0, 0, 0, 0 }                                                        // NumberSolderedDownDimmsSupported
#define BLDCFG_NUM_CS_SUPPORTED       { 0, 0, 0, 0, 0, 0 }                                                                       // NumberChipSelectsSupported

#define BLDCFG_NUM_CHNL_SUPPORTED     { NUMBER_OF_CHANNELS_SUPPORTED(ANY_SOCKET, 2) }                                            // NumberChannelsSupported
#define BLDCFG_BUS_SPEED_OVERRIDE     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }                                                  // OverrideBusSpeed
#define BLDCFG_DRAM_TECH_OVERRIDE     { 0, 0, 0, 0, 0, 0, 0, 0, 0 }                                                              // DramTechnology
#define BLDCFG_SOLDRD_DOWN_DIMM_TYPE  { 0, 0, 0, 0, 0, 0 }                                                                       // SolderedDownSoDimmType
#define BLDCFG_MEM_POWER_POLICY_OVERRIDE  { 0, 0, 0, 0, 0, 0 }                                                                   // MemoryPowerPolicyOverride
#define BLDCFG_NUM_MOTHERBOARD_LAYERS { 0, 0, 0, 0, 0, 0 }                                                                        // MotherboardLayers



#define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_UNBUFFERED
#define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE

#define BLDCFG_ONLINE_SPARE                       FALSE
#define BLDCFG_USE_BURST_MODE                     FALSE
#define BLDCFG_HEAP_DRAM_ADDRESS                  0xB0000ul
#define BLDCFG_1GB_ALIGN                          FALSE
#define BLDCFG_UMA_ALIGNMENT                      UMA_4MB_ALIGNED
#define BLDCFG_DIMM_TYPE_PACKAGE                  UDIMM_PACKAGE

//
// Please Review the below SMBUS Address, based off your schematics and comment out lines which doesnt belongs
// to the project for which this fie is being customized
//

#define BLDCFG_SPD_CH_A_DIMM0_ADDRESS      CHANNEL_A_DIMM_0_ADDRESS //AMI porting 0xA0
#define BLDCFG_SPD_CH_A_DIMM1_ADDRESS      CHANNEL_A_DIMM_1_ADDRESS //AMI porting 0xA4

#define BLDCFG_SPD_CH_B_DIMM0_ADDRESS      CHANNEL_B_DIMM_0_ADDRESS //AMI porting 0xA8
#define BLDCFG_SPD_CH_B_DIMM1_ADDRESS      CHANNEL_B_DIMM_1_ADDRESS //AMI porting 0xA6

#define BLDCFG_SPD_CH_C_DIMM0_ADDRESS      0xA2
#define BLDCFG_SPD_CH_C_DIMM1_ADDRESS      0xAC

#define BLDCFG_SPD_CH_D_DIMM0_ADDRESS      0xAA
#define BLDCFG_SPD_CH_D_DIMM1_ADDRESS      0xAE

#define BLDCFG_SPD_CH_E_DIMM0_ADDRESS      0xA0
#define BLDCFG_SPD_CH_E_DIMM1_ADDRESS      0xA4

#define BLDCFG_SPD_CH_F_DIMM0_ADDRESS      0xA2
#define BLDCFG_SPD_CH_F_DIMM1_ADDRESS      0xA6

#define BLDCFG_SPD_CH_G_DIMM0_ADDRESS      0xA8
#define BLDCFG_SPD_CH_G_DIMM1_ADDRESS      0xAC

#define BLDCFG_SPD_CH_H_DIMM0_ADDRESS      0xAA
#define BLDCFG_SPD_CH_H_DIMM1_ADDRESS      0xAE

#define BLDCFG_MEM_LAYOOUT_TYPE           MEMORY_LAYOUT_TYPE_DIMM

#define BLDCFG_I2C_MUX_ADRRESS            0x94
#define BLDCFG_I2C_CHANNEL_1               1
#define BLDCFG_I2C_CHANNEL_2               2
#define BLDCFG_I2C_CHANNEL_3               3
#define BLDCFG_I2C_CHANNEL_4               4

#define BLDCFG_CCX_MIN_SEV_ASID                0

#define BLDCFG_DF_GMI_ENCRYPT                  3
#define BLDCFG_DF_XGMI_ENCRYPT                 3
#define BLDCFG_DF_SAVE_RESTORE_MEM_ENCRYPT     3
#define BLDCFG_DF_SYS_STORAGE_AT_TOM           3
#define BLDCFG_DF_PROBE_FILTER_ENABLE          3
#define BLDCFG_DF_BOTTOM_IO                    0xD0
#define BLDCFG_DF_MEM_INTERLEAVING             7
#define BLDCFG_DF_DRAM_INTLV_SIZE              7
#define BLDCFG_DF_CHAN_INTLV_HASH_EN           3
#define BLDCFG_DF_PCI_MMIO_SIZE                0x8000000
#define BLDCFG_DF_CAKE_CRC_THRESH_PERF_BOUNDS  100  // 0.001%

//
// UART Enable Disable through SOC UART/ LPC-SUPER IO
// 0 - LPC UART, 1 - SOC UART0
//
#define BLDCFG_FCH_CONSOLE_OUT_ENABLE       0
#define BLDCFG_FCH_CONSOLE_OUT_SERIAL_PORT  1
#define BLDCFG_FCH_UART_BAUD_RATE           115200

//#define BLDCFG_CONOUTCTRL_BREAKPOINT          FALSE
//#define BLDCFG_CONOUTCTRL_BREAKPOINT_ALLDIE   FALSE

//
// SPD SMBUS voltage 1-1.8V. 0- 3.3V
//
#define     BLDCFG_SPD_SMBUS_VOLTAGE         0

#endif   //ifndef  _APCB_CUSTOMIZED_DEFINITIONS_H_

