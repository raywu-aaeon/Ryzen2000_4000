/* $NoKeywords:$ */
/**
 * @file
 *
 * Install of build options for a Carrizo FP4 platform solution
 *
 * This file generates the defaults tables for the "Carrizo FP4" platform solution
 * set of processors. The documented build options are imported from a user
 * controlled file for processing.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Core
 * @e \$Revision: 320438 $   @e \$Date: 2015-06-10 14:22:16 +0800 (Wed, 10 Jun 2015) $
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

/*****************************************************************************
 *   Define the RELEASE VERSION string
 *
 * The Release Version string should identify the next planned release.
 * When a branch is made in preparation for a release, the release manager
 * should change/confirm that the branch version of this file contains the
 * string matching the desired version for the release. The trunk version of
 * the file should always contain a trailing 'X'. This will make sure that a
 * development build from trunk will not be confused for a released version.
 * The release manager will need to remove the trailing 'X' and update the
 * version string as appropriate for the release. The trunk copy of this file
 * should also be updated/incremented for the next expected version, + trailing 'X'
 ****************************************************************************/
                  // This is the delivery package title, "CarrizoPI        "
                  // This string MUST be exactly 16 characters long
//Clear AGESA V5 Package string
#define AGESA_PACKAGE_STRING  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

                  // This is the release version number of the AGESA component
                  // This string MUST be exactly 12 characters long
//Clear AGESA V5 version string
#define AGESA_VERSION_STRING  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


// The Carrizo FP4 solution is defined to be family 0x15 models 0x60 - 0x6F in the FP4 sockets.
#define INSTALL_FP4_SOCKET_SUPPORT           TRUE
#define INSTALL_FAMILY_15_MODEL_6x_SUPPORT   TRUE

// The following definitions specify the default values for various parameters in which there are
// no clearly defined defaults to be used in the common file.  The values below are based on product
// and BKDG content, please consult the AGESA Memory team for consultation.
#define DFLT_SCRUB_DRAM_RATE            (0)
#define DFLT_SCRUB_L2_RATE              (0)
#define DFLT_SCRUB_L3_RATE              (0)
#define DFLT_SCRUB_IC_RATE              (0)
#define DFLT_SCRUB_DC_RATE              (0)
#define DFLT_MEMORY_QUADRANK_TYPE       QUADRANK_UNBUFFERED
#define DFLT_VRM_SLEW_RATE              (5000)


#define DFLT_SMBUS0_BASE_ADDRESS            0xB00
#define DFLT_SMBUS1_BASE_ADDRESS            0xB20
#define DFLT_SIO_PME_BASE_ADDRESS           0xE00
#define DFLT_ACPI_PM1_EVT_BLOCK_ADDRESS     0x400
#define DFLT_ACPI_PM1_CNT_BLOCK_ADDRESS     0x404
#define DFLT_ACPI_PM_TMR_BLOCK_ADDRESS      0x408
#define DFLT_ACPI_CPU_CNT_BLOCK_ADDRESS     0x410
#define DFLT_ACPI_GPE0_BLOCK_ADDRESS        0x420
#define DFLT_SPI_BASE_ADDRESS               0xFEC10000ul
#define DFLT_WATCHDOG_TIMER_BASE_ADDRESS    0xFEC000F0ul
#define DFLT_HPET_BASE_ADDRESS              0xFED00000ul
#define DFLT_SMI_CMD_PORT                   0xB0
#define DFLT_ACPI_PMA_CNT_BLK_ADDRESS       0xFE00
#define DFLT_GEC_BASE_ADDRESS               0xFED61000ul
#define DFLT_AZALIA_SSID                    0x780D1022ul
#define DFLT_SMBUS_SSID                     0x780B1022ul
#define DFLT_IDE_SSID                       0x780C1022ul
#define DFLT_SATA_AHCI_SSID                 0x78011022ul
#define DFLT_SATA_IDE_SSID                  0x78001022ul
#define DFLT_SATA_RAID5_SSID                0x78031022ul
#define DFLT_SATA_RAID_SSID                 0x78021022ul
#define DFLT_EHCI_SSID                      0x78081022ul
#define DFLT_OHCI_SSID                      0x78071022ul
#define DFLT_LPC_SSID                       0x780E1022ul
#define DFLT_SD_SSID                        0x78061022ul
#define DFLT_XHCI_SSID                      0x78121022ul
#define DFLT_FCH_PORT80_BEHIND_PCIB         FALSE
#define DFLT_FCH_ENABLE_ACPI_SLEEP_TRAP     TRUE
#define DFLT_FCH_GPP_LINK_CONFIG            PortA4
#define DFLT_FCH_GPP_PORT0_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT1_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT2_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT3_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT0_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT1_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT2_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT3_HOTPLUG          FALSE



/* User makes option selections here
 * Comment out the items wanted to be included in the build.
 * Uncomment those items you wish to REMOVE from the build.
 */
//#define BLDOPT_REMOVE_DDR3_SUPPORT             TRUE
//#define BLDOPT_REMOVE_DDR4_SUPPORT             TRUE
//#define BLDOPT_REMOVE_UDIMMS_SUPPORT           TRUE
#define BLDOPT_REMOVE_RDIMMS_SUPPORT           TRUE
#define BLDOPT_REMOVE_LRDIMMS_SUPPORT          TRUE
//#define BLDOPT_REMOVE_ECC_SUPPORT              TRUE
//#define BLDOPT_REMOVE_BANK_INTERLEAVE          TRUE
//#define BLDOPT_REMOVE_DCT_INTERLEAVE           TRUE
#define BLDOPT_REMOVE_NODE_INTERLEAVE          TRUE
#define BLDOPT_REMOVE_PARALLEL_TRAINING        TRUE
#define BLDOPT_REMOVE_ONLINE_SPARE_SUPPORT     TRUE
//#define BLDOPT_REMOVE_MEM_RESTORE_SUPPORT      TRUE
#define BLDOPT_REMOVE_MULTISOCKET_SUPPORT        TRUE
//#define BLDOPT_REMOVE_ACPI_PSTATES             TRUE
#define BLDOPT_REMOVE_WHEA                     TRUE
//#define BLDOPT_REMOVE_DMI                      TRUE
#define BLDOPT_REMOVE_EARLY_SAMPLES            FALSE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PPC               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PCT               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSD               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSS               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_XPSS              TRUE
//#define BLDCFG_NB_PSTATES_SUPPORTED                  FALSE
//#define BLDCFG_AP_COMM_METHOD AP_COMM_PCI // Besides uncomment this build option,
                                            // you have to add a parameter 'AP_COMM_PCI' to 'AMD_DISABLE_STACK_PRIVATE' macro

//This element selects whether P-States should be forced to be independent,
// as reported by the ACPI _PSD object. For single-link processors,
// setting TRUE for OS to support this feature.
//#define BLDCFG_FORCE_INDEPENDENT_PSD_OBJECT  TRUE

/* Build configuration values here.
 */
#define BLDCFG_SYSTEM_CONFIGURATION              1 //This is the new CZ FW configurations 1-6; default is 1 at 15W
#define BLDCFG_AMD_TDP_LIMIT                     0
#define BLDCFG_PPT_LIMIT_AC                      0
#define BLDCFG_PPT_LIMIT_DC                      0
#define BLDCFG_BATTERY_BOOST_TUNE                0
//#define BLDCFG_STAPM_BOOST                       1 // When not defined, this value will use the default for the System Configuration
#define BLDCFG_STAPM_TIME_CONSTANT               0
#define BLDCFG_SKIN_CONTROL_SCALAR               0
#define BLDCFG_THERMCTL_LIMIT                    0

// Specify the default values for the VRM controlling the VDD plane.
// For detail information, please refer to FP4 Infrastructure Roadmap #53555
//#define BLDCFG_VRM_CURRENT_LIMIT                 22000  // 15W - 22000; 35W - 39000
//#define BLDCFG_VRM_MAXIMUM_CURRENT_LIMIT         35000  // 15W - 35000; 35W - 55000
#define BLDCFG_VRM_CURRENT_LIMIT                 0
#define BLDCFG_VRM_MAXIMUM_CURRENT_LIMIT         0
#define BLDCFG_VRM_LOW_POWER_THRESHOLD           14000  // 15W - 14000; 35W - 18000
#define BLDCFG_PLAT_NUM_IO_APICS                 3
#define BLDCFG_CORE_LEVELING_MODE                CORE_LEVEL_LOWEST
#define BLDCFG_MEM_INIT_PSTATE                   0

// Specify the default values for the VRM controlling the VDDNB plane.
// If not specified, the values used for the core VRM will be applied
//#define BLDCFG_VRM_NB_CURRENT_LIMIT              12000  // 15W - 12000; 35W - 12000
//#define BLDCFG_VRM_NB_MAXIMUM_CURRENT_LIMIT      17000  // 15W - 17000; 35W - 17000
#define BLDCFG_VRM_NB_CURRENT_LIMIT              0
#define BLDCFG_VRM_NB_MAXIMUM_CURRENT_LIMIT      0
#define BLDCFG_VRM_NB_LOW_POWER_THRESHOLD        15000  // 15W - 15000; 35W - 15000
//#define BLDCFG_VRM_NB_HIGH_SPEED_ENABLE           0

// Specify the default values for the VRM controlling the GFX voltage rail .
//#define BLDCFG_VRM_GFX_CURRENT_LIMIT             22000  // 15W - 22000; 35W - 30000
//#define BLDCFG_VRM_GFX_MAXIMUM_CURRENT_LIMIT     35000  // 15W - 35000; 35W - 45000
#define BLDCFG_VRM_GFX_CURRENT_LIMIT             0
#define BLDCFG_VRM_GFX_MAXIMUM_CURRENT_LIMIT     0
#define BLDCFG_VRM_GFX_LOW_POWER_THRESHOLD       15000  // 15W - 15000; 35W - 15000

// Override the default strings used for AGESA ACPI table OEM fields.
// These strings must conform to applicable ACPI rules for OEM fields.
// Default strings are 'AMD   ' and 'AGESA   '
//#define  BLDCFG_ACPI_SET_OEM_ID                   ' ',' ',' ',' ',' ',' '             // This string must be 6 characters long.
//#define  BLDCFG_ACPI_SET_OEM_TABLE_ID             ' ',' ',' ',' ',' ',' ',' ',' '     // This string must be 8 characters long.

#define BLDCFG_AMD_PLATFORM_TYPE                  AMD_PLATFORM_MOBILE

#define BLDCFG_DIMM_TYPE_USED_IN_MIXED_CONFIG     DDR3_TECHNOLOGY
#define BLDCFG_DIMM_TYPE_DDR3_CAPABLE             TRUE
#define BLDCFG_DIMM_TYPE_DDR4_CAPABLE             TRUE
#define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR2400_FREQUENCY
#define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           FALSE
#define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_UNBUFFERED
#define BLDCFG_MEMORY_RDIMM_CAPABLE               FALSE
#define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE              TRUE
#define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        TRUE
#define BLDCFG_MEMORY_POWER_DOWN                  TRUE
#define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHIP_SELECT
#define BLDCFG_ONLINE_SPARE                       FALSE
#define BLDCFG_BANK_SWIZZLE                       TRUE
#define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#define BLDCFG_MEMORY_CLOCK_SELECT                DDR2133_FREQUENCY
#define BLDCFG_DQS_TRAINING_CONTROL               FALSE
#define BLDCFG_IGNORE_SPD_CHECKSUM                FALSE
#define BLDCFG_USE_BURST_MODE                     FALSE
#define BLDCFG_MEMORY_ALL_CLOCKS_ON               FALSE
#define BLDCFG_ENABLE_ECC_FEATURE                 TRUE
#define BLDCFG_ECC_REDIRECTION                    FALSE
#define BLDCFG_SCRUB_DRAM_RATE                    0
#define BLDCFG_SCRUB_L2_RATE                      0
#define BLDCFG_SCRUB_L3_RATE                      0
#define BLDCFG_SCRUB_IC_RATE                      0
#define BLDCFG_SCRUB_DC_RATE                      0
#define BLDCFG_ECC_SYNC_FLOOD                     TRUE
#define BLDCFG_ECC_SYMBOL_SIZE                    4
#define BLDCFG_HEAP_DRAM_ADDRESS                  0xB0000ul
#define BLDCFG_1GB_ALIGN                          FALSE
#define BLDCFG_VRM_HIGH_SPEED_ENABLE              TRUE
#define BLDCFG_PLATFORM_CSTATE_IO_BASE_ADDRESS    0x1770
#define BLDCFG_UMA_ALIGNMENT                      UMA_4MB_ALIGNED
#define BLDCFG_GNB_AZ_I2SBUS_SELECT               GnbAcpAzalia
#define BLDCFG_GNB_AZ_I2SBUS_PIN_CONFIG           GnbAcp4Tx4RxBluetooth
#define BLDCFG_UMA_ABOVE4G_SUPPORT                TRUE
#define BLDCFG_CUSTOM_VDDIO_VOLTAGE               VOLT_INITIAL
//#define BLDCFG_PLATFORM_CPB_MODE                  CpbModeDisabled
//#define BLDCFG_PROCESSOR_SCOPE_NAME0              'C'
//#define BLDCFG_PROCESSOR_SCOPE_NAME1              '0'
//#define BLDCFG_PLATFORM_CSTATE_MODE               CStateModeDisabled
//#define BLDCFG_PLATFORM_CSTATE_OPDATA             0
#define BLDCFG_MEMORY_POWER_POLICY_MODE             Performance
/*  Process the options...
 * This file include MUST occur AFTER the user option selection settings
 */
#define AGESA_ENTRY_INIT_RESET                    FALSE
#define AGESA_ENTRY_INIT_RECOVERY                 FALSE
#define AGESA_ENTRY_INIT_EARLY                    TRUE
#define AGESA_ENTRY_INIT_POST                     TRUE
#define AGESA_ENTRY_INIT_ENV                      TRUE
#define AGESA_ENTRY_INIT_MID                      TRUE
#define AGESA_ENTRY_INIT_LATE                     TRUE
#define AGESA_ENTRY_INIT_RTB                      TRUE
#define AGESA_ENTRY_INIT_RESUME                   TRUE
#define AGESA_ENTRY_INIT_LATE_RESTORE             FALSE
#define AGESA_ENTRY_INIT_FINAL_RESTORE            FALSE
#define AGESA_ENTRY_INIT_GENERAL_SERVICES         TRUE
/*
 * Customized OEM build configurations for FCH component
 */
// #define BLDCFG_SMBUS0_BASE_ADDRESS            0xB00
// #define BLDCFG_SMBUS1_BASE_ADDRESS            0xB20
// #define BLDCFG_SIO_PME_BASE_ADDRESS           0xE00
// #define BLDCFG_ACPI_PM1_EVT_BLOCK_ADDRESS     0x400
// #define BLDCFG_ACPI_PM1_CNT_BLOCK_ADDRESS     0x404
// #define BLDCFG_ACPI_PM_TMR_BLOCK_ADDRESS      0x408
// #define BLDCFG_ACPI_CPU_CNT_BLOCK_ADDRESS     0x410
// #define BLDCFG_ACPI_GPE0_BLOCK_ADDRESS        0x420
// #define BLDCFG_SPI_BASE_ADDRESS               0xFEC10000ul
// #define BLDCFG_WATCHDOG_TIMER_BASE            0xFEC000F0ul
// #define BLDCFG_HPET_BASE_ADDRESS              0xFED00000ul
// #define BLDCFG_SMI_CMD_PORT_ADDRESS           0xB0
// #define BLDCFG_ACPI_PMA_BLK_ADDRESS           0xFE00
// #define BLDCFG_ROM_BASE_ADDRESS               0xFED61000ul
// #define BLDCFG_AZALIA_SSID                    0x780D1022ul
// #define BLDCFG_SMBUS_SSID                     0x780B1022ul
// #define BLDCFG_IDE_SSID                       0x780C1022ul
// #define BLDCFG_SATA_AHCI_SSID                 0x78011022ul
// #define BLDCFG_SATA_IDE_SSID                  0x78001022ul
// #define BLDCFG_SATA_RAID5_SSID                0x78031022ul
// #define BLDCFG_SATA_RAID_SSID                 0x78021022ul
// #define BLDCFG_EHCI_SSID                      0x78081022ul
// #define BLDCFG_OHCI_SSID                      0x78071022ul
// #define BLDCFG_LPC_SSID                       0x780E1022ul
// #define BLDCFG_SD_SSID                        0x78061022ul
// #define BLDCFG_XHCI_SSID                      0x78121022ul
// #define BLDCFG_FCH_PORT80_BEHIND_PCIB         FALSE
// #define BLDCFG_FCH_ENABLE_ACPI_SLEEP_TRAP     TRUE
// #define BLDCFG_FCH_GPP_LINK_CONFIG            PortA4
// #define BLDCFG_FCH_GPP_PORT0_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT1_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT2_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT3_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT0_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT1_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT2_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT3_HOTPLUG          FALSE

//CONST GPIO_CONTROL ROMDATA CarrizoFchGpioControlList[] =
//{
//  //GpioPin, PinFunction ,CfgByte
//  { 0x36, 0x01, OutputEnable | PullUpEnable | DrvStrengthSel_16mA},
//  { 0xff,0xff,0xff } //last dummy pin configure
//};
//#define BLDCFG_FCH_GPIO_CONTROL_LIST &CarrizoFchGpioControlList

/*
 * Customized OEM build configurations for GNB component
 */
//#define BLDCFG_GNB_AZ_SSID        0x157A1022ul  // HD Audio Controller Subsystem Vendor ID and Subsystem ID

/*
 * Customized OEM build Codec Verb table
 * the verb table to customize the audio codec configuration
 * The data format and the usage are defined in High Definition Audio Specification
 * Codec vendor provides the data
 */

// Instantiate all solution relevant data.
//#include <PlatformInstall.h>


