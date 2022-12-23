/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _AMD_CPM_DEFINE_H_
#define _AMD_CPM_DEFINE_H_

#define AMD_CPM_PLATFORM_ID_AUTO                  0xFFFF
#ifndef AMD_CPM_PLATFORM_ID_DEFAULT
  #define AMD_CPM_PLATFORM_ID_DEFAULT             AMD_CPM_PLATFORM_ID_AUTO
#endif

#ifndef CPM_PLATFORM_ID_OVERRIDE
#define CPM_PLATFORM_ID_OVERRIDE                  0xFFFF
#endif

#ifndef AMD_PLATFORM_ID_TABLE_SIZE
  #define AMD_PLATFORM_ID_TABLE_SIZE              0x08
#endif

#ifndef AMD_PLATFORM_ID_CONVERT_TABLE_SIZE
  #define AMD_PLATFORM_ID_CONVERT_TABLE_SIZE      0x40
#endif

#ifndef AMD_PRE_INIT_SIZE
  #define AMD_PRE_INIT_SIZE                       0x40
#endif

#ifndef AMD_CPM_CORE_TOPOLOGY_SIZE
  #define AMD_CPM_CORE_TOPOLOGY_SIZE              0x10
#endif

#ifndef UCSI_PORT_NUMBER
  #define UCSI_PORT_NUMBER                        0x2
#endif

#ifndef AMD_GPIO_ITEM_SIZE
  #define AMD_GPIO_ITEM_SIZE                      0x100
#endif

#ifndef AMD_GEVENT_ITEM_SIZE
  #define AMD_GEVENT_ITEM_SIZE                    0x20
#endif

#ifndef AMD_GPIO_MEM_VOLTAGE_SIZE
  #define AMD_GPIO_MEM_VOLTAGE_SIZE               0x05
#endif

#ifndef AMD_GPIO_VDDP_VDDR_VOLTAGE_SIZE
  #define AMD_GPIO_VDDP_VDDR_VOLTAGE_SIZE         0x03
#endif

#ifndef AMD_GPIO_DEVICE_SIZE
  #define AMD_GPIO_DEVICE_SIZE                    0x64
#endif

#ifndef AMD_GPIO_DEVICE_DETECT_SIZE
  #define AMD_GPIO_DEVICE_DETECT_SIZE             0x20
#endif

#ifndef AMD_GPIO_DEVICE_RESET_SIZE
  #define AMD_GPIO_DEVICE_RESET_SIZE              0x20
#endif

#ifndef AMD_GPIO_DEVICE_POWER_SIZE
  #define AMD_GPIO_DEVICE_POWER_SIZE              0x30
#endif

#ifndef AMD_PT_GPIO_DEVICE_INIT_SIZE
  #define AMD_PT_GPIO_DEVICE_INIT_SIZE            0x10
#endif

#ifndef AMD_PCIE_CLOCK_SIZE
  #define AMD_PCIE_CLOCK_SIZE                     0x10
#endif

#ifndef AMD_EXT_CLKGEN_SIZE
  #define AMD_EXT_CLKGEN_SIZE                     0x20
#endif

#ifndef AMD_PCIE_PORT_DESCRIPTOR_SIZE
  #define AMD_PCIE_PORT_DESCRIPTOR_SIZE           0x08
#endif

#ifndef AMD_PCIE_DDI_DESCRIPTOR_SIZE
  #define AMD_PCIE_DDI_DESCRIPTOR_SIZE            0x08
#endif

#ifndef AMD_DXIO_DDI_DESCRIPTOR_SIZE
  #define AMD_DXIO_DDI_DESCRIPTOR_SIZE            0x04
#endif

#ifndef AMD_DXIO_PORT_DESCRIPTOR_SIZE
  #define AMD_DXIO_PORT_DESCRIPTOR_SIZE           0x10
#endif

#ifndef AMD_PCIE_TOPOLOGY_OVERRIDE_SIZE
  #define AMD_PCIE_TOPOLOGY_OVERRIDE_SIZE         0x10
#endif

#ifndef AMD_TABLE_LIST_ITEM_SIZE
  #define AMD_TABLE_LIST_ITEM_SIZE                0x40
#endif

#ifndef AMD_TABLE_LIST_ADDITIONAL_ITEM_SIZE
  #define AMD_TABLE_LIST_ADDITIONAL_ITEM_SIZE     0x10
#endif

#ifndef AMD_TABLE_ADDITIONAL_BUFFER_SIZE
  #define AMD_TABLE_ADDITIONAL_BUFFER_SIZE        0x400
#endif

#ifndef DEFAULT_BRIGHTNESS_LEVEL
  #define DEFAULT_BRIGHTNESS_LEVEL                60
#endif

#ifndef DEFAULT_CURRENT_DISPLAY_STATE
  #define DEFAULT_CURRENT_DISPLAY_STATE           0x0101          // (PIPE_A_CRT | (PIPE_B_CRT))
#endif

#ifndef AMD_CPM_ASL_CPU0
  #define AMD_CPM_ASL_CPU0                        0               // If 0, AMD_CPM_CPM_ASL_CPU0 = C000
#endif

#ifndef AMD_CPM_ASL_EC_NAME
  #define AMD_CPM_ASL_EC_NAME                     0               // If 0, AMD_CPM_ASL_EC_NAME = EC0_
#endif

#ifndef AMD_CPM_ASL_EC_MUTEX
  #define AMD_CPM_ASL_EC_MUTEX                    0               // If 0, AMD_CPM_ASL_EC_MUTEX = M042
#endif

#ifndef AMD_CPM_ASL_LPC_NAME
  #define AMD_CPM_ASL_LPC_NAME                    0               // If 0, AMD_CPM_ASL_LPC_NAME = LPC0
#endif

#ifndef AMD_CPM_ASL_OKEC_NAME
  #define AMD_CPM_ASL_OKEC_NAME                   0               // If 0, AMD_CPM_ASL_OKEC_NAME = OKEC
#endif

#ifndef AMD_CPM_ASL_OEM_CALLBACK
  #define AMD_CPM_ASL_OEM_CALLBACK                0               // If 0, AMD_CPM_ASL_OEM_CALLBACK = MOEM
#endif

#ifndef AMD_CPM_ASL_OEM_MLIB
  #define AMD_CPM_ASL_OEM_MLIB                    0               // If 0, AMD_CPM_ASL_OEM_MLIB = MLIB
#endif

#ifndef AMD_CPM_ASL_ACP_NAME
  #define AMD_CPM_ASL_ACP_NAME                    0               // If 0, AMD_CPM_ASL_ACP_NAME = ACP_
#endif

#ifndef AMD_CPM_ASL_AZALIA_NAME
  #define AMD_CPM_ASL_AZALIA_NAME                 0               // If 0, AMD_CPM_ASL_ACP_NAME = AZAL
#endif

#ifndef AMD_CPM_ASL_LAN_NAME
  #define AMD_CPM_ASL_LAN_NAME                    0               // If 0, AMD_CPM_ASL_LAN_NAME = BCM5
#endif

#ifndef AMD_CPM_ACPI_VERSION_SUPPORT
  #define AMD_CPM_ACPI_VERSION_SUPPORT            0x0000003Eul    // BIT0: EFI_ACPI_TABLE_VERSION_NONE
                                                                  // BIT1: EFI_ACPI_TABLE_VERSION_1_0B
                                                                  // BIT2: EFI_ACPI_TABLE_VERSION_2_0
                                                                  // BIT3: EFI_ACPI_TABLE_VERSION_3_0
                                                                  // BIT4: EFI_ACPI_TABLE_VERSION_4_0
                                                                  // BIT5: EFI_ACPI_TABLE_VERSION_5_0
#endif

#ifndef AMD_CPM_SSDT_SUPPORT
  #define AMD_CPM_SSDT_SUPPORT                    1               // If 0, SSDT table will not be loaded
#endif

#ifndef AMD_CPM_PCIE_GFX0_NAME_1
  #define AMD_CPM_PCIE_GFX0_NAME_1                '_2BP'          // PB2_
#endif
#ifndef AMD_CPM_PCIE_GFX1_NAME_1
  #define AMD_CPM_PCIE_GFX1_NAME_1                '_3BP'          // PB3_
#endif
#ifndef AMD_CPM_PCIE_GPP0_NAME_1
  #define AMD_CPM_PCIE_GPP0_NAME_1                '_4BP'          // PB4_
#endif
#ifndef AMD_CPM_PCIE_GPP1_NAME_1
  #define AMD_CPM_PCIE_GPP1_NAME_1                '_5BP'          // PB5_
#endif
#ifndef AMD_CPM_PCIE_GPP2_NAME_1
  #define AMD_CPM_PCIE_GPP2_NAME_1                '_6BP'          // PB6_
#endif
#ifndef AMD_CPM_PCIE_GPP3_NAME_1
  #define AMD_CPM_PCIE_GPP3_NAME_1                '_7BP'          // PB7_
#endif

#ifndef AMD_CPM_PCIE_GFX0_NAME_2
  #define AMD_CPM_PCIE_GFX0_NAME_2                '12BP'          // PB21
#endif
#ifndef AMD_CPM_PCIE_GFX1_NAME_2
  #define AMD_CPM_PCIE_GFX1_NAME_2                '22BP'          // PB22
#endif
#ifndef AMD_CPM_PCIE_GPP0_NAME_2
  #define AMD_CPM_PCIE_GPP0_NAME_2                '13BP'          // PB31
#endif
#ifndef AMD_CPM_PCIE_GPP1_NAME_2
  #define AMD_CPM_PCIE_GPP1_NAME_2                '23BP'          // PB32
#endif
#ifndef AMD_CPM_PCIE_GPP2_NAME_2
  #define AMD_CPM_PCIE_GPP2_NAME_2                '33BP'          // PB33
#endif
#ifndef AMD_CPM_PCIE_GPP3_NAME_2
  #define AMD_CPM_PCIE_GPP3_NAME_2                '43BP'          // PB34
#endif
#ifndef AMD_CPM_PCIE_GPP4_NAME_2
  #define AMD_CPM_PCIE_GPP4_NAME_2                '53BP'          // PB35
#endif

#ifndef AMD_CPM_PCIE_GPP0_NAME_3
  #define AMD_CPM_PCIE_GPP0_NAME_3                '0PPG'          // GPP0
#endif
#ifndef AMD_CPM_PCIE_GPP1_NAME_3
  #define AMD_CPM_PCIE_GPP1_NAME_3                '1PPG'          // GPP1
#endif
#ifndef AMD_CPM_PCIE_GPP2_NAME_3
  #define AMD_CPM_PCIE_GPP2_NAME_3                '2PPG'          // GPP2
#endif
#ifndef AMD_CPM_PCIE_GPP3_NAME_3
  #define AMD_CPM_PCIE_GPP3_NAME_3                '3PPG'          // GPP3
#endif
#ifndef AMD_CPM_PCIE_GFX_NAME_3
  #define AMD_CPM_PCIE_GFX_NAME_3                 '_XFG'          // GFX_
#endif

#ifndef AMD_CPM_PCIE_GPP0_NAME_4
  #define AMD_CPM_PCIE_GPP0_NAME_4                '0PPG'          // GPP0
#endif
#ifndef AMD_CPM_PCIE_GPP1_NAME_4
  #define AMD_CPM_PCIE_GPP1_NAME_4                '1PPG'          // GPP1
#endif
#ifndef AMD_CPM_PCIE_GPP2_NAME_4
  #define AMD_CPM_PCIE_GPP2_NAME_4                '2PPG'          // GPP2
#endif
#ifndef AMD_CPM_PCIE_GPP3_NAME_4
  #define AMD_CPM_PCIE_GPP3_NAME_4                '3PPG'          // GPP3
#endif
#ifndef AMD_CPM_PCIE_GPP4_NAME_4
  #define AMD_CPM_PCIE_GPP4_NAME_4                '4PPG'          // GPP4
#endif
#ifndef AMD_CPM_PCIE_GPP5_NAME_4
  #define AMD_CPM_PCIE_GPP5_NAME_4                '5PPG'          // GPP5
#endif
#ifndef AMD_CPM_PCIE_GPP6_NAME_4
  #define AMD_CPM_PCIE_GPP6_NAME_4                '6PPG'          // GPP6
#endif
#ifndef AMD_CPM_PCIE_GPP7_NAME_4
  #define AMD_CPM_PCIE_GPP7_NAME_4                '7PPG'          // GPP7
#endif
#ifndef AMD_CPM_PCIE_GPP8_NAME_4
  #define AMD_CPM_PCIE_GPP8_NAME_4                '8PPG'          // GPP8
#endif
#ifndef AMD_CPM_PCIE_GPP9_NAME_4
  #define AMD_CPM_PCIE_GPP9_NAME_4                '9PPG'          // GPP9
#endif
#ifndef AMD_CPM_PCIE_GPPA_NAME_4
  #define AMD_CPM_PCIE_GPPA_NAME_4                'APPG'          // GPPA
#endif
#ifndef AMD_CPM_PCIE_GPPB_NAME_4
  #define AMD_CPM_PCIE_GPPB_NAME_4                'BPPG'          // GPPB
#endif
#ifndef AMD_CPM_PCIE_GPPC_NAME_4
  #define AMD_CPM_PCIE_GPPC_NAME_4                'CPPG'          // GPPC
#endif
#ifndef AMD_CPM_PCIE_GPPD_NAME_4
  #define AMD_CPM_PCIE_GPPD_NAME_4                'DPPG'          // GPPD
#endif
#ifndef AMD_CPM_PCIE_GPPE_NAME_4
  #define AMD_CPM_PCIE_GPPE_NAME_4                'EPPG'          // GPPE
#endif
#ifndef AMD_CPM_PCIE_GPPF_NAME_4
  #define AMD_CPM_PCIE_GPPF_NAME_4                'FPPG'          // GPPF
#endif
#ifndef AMD_CPM_PCIE_GPPG_NAME_4
  #define AMD_CPM_PCIE_GPPG_NAME_4                'GPPG'          // GPPG
#endif
#ifndef AMD_CPM_PCIE_GPPH_NAME_4
  #define AMD_CPM_PCIE_GPPH_NAME_4                'HPPG'          // GPPH
#endif

#ifndef AMD_CPM_PCIE_GFX0_NAME_4
  #define AMD_CPM_PCIE_GFX0_NAME_4                '0XFG'          // GFX0
#endif
#ifndef AMD_CPM_PCIE_GFX1_NAME_4
  #define AMD_CPM_PCIE_GFX1_NAME_4                '1XFG'          // GFX1
#endif
#ifndef AMD_CPM_PCIE_GFX2_NAME_4
  #define AMD_CPM_PCIE_GFX2_NAME_4                '2XFG'          // GFX2
#endif
#ifndef AMD_CPM_PCIE_GFX3_NAME_4
  #define AMD_CPM_PCIE_GFX3_NAME_4                '3XFG'          // GFX3
#endif
#ifndef AMD_CPM_PCIE_GFX4_NAME_4
  #define AMD_CPM_PCIE_GFX4_NAME_4                '4XFG'          // GFX4
#endif

#ifndef AMD_CPM_PCIE_GP17_NAME_4
  #define AMD_CPM_PCIE_GP17_NAME_4                '71PG'          // GP17
#endif
#ifndef AMD_CPM_PCIE_GP18_NAME_4
  #define AMD_CPM_PCIE_GP18_NAME_4                '81PG'          // GP18
#endif
#ifndef AMD_CPM_PCIE_GP28_NAME_4
  #define AMD_CPM_PCIE_GP28_NAME_4                '82PG'          // GP28
#endif
#ifndef AMD_CPM_PCIE_GP38_NAME_4
  #define AMD_CPM_PCIE_GP38_NAME_4                '83PG'          // GP38
#endif

#ifndef AMD_CPM_FCH_PCIE_GPP0_NAME
  #define AMD_CPM_FCH_PCIE_GPP0_NAME              '0BPS'          // SPB0
#endif
#ifndef AMD_CPM_FCH_PCIE_GPP1_NAME
  #define AMD_CPM_FCH_PCIE_GPP1_NAME              '1BPS'          // SPB1
#endif
#ifndef AMD_CPM_FCH_PCIE_GPP2_NAME
  #define AMD_CPM_FCH_PCIE_GPP2_NAME              '2BPS'          // SPB2
#endif
#ifndef AMD_CPM_FCH_PCIE_GPP3_NAME
  #define AMD_CPM_FCH_PCIE_GPP3_NAME              '3BPS'          // SPB3
#endif

//
// OFFSET_OF DEFINITION
//
#ifndef OFFSET_OF
  #define OFFSET_OF(type, member) ((UINT8) &(((type*)0)->member))
#endif

//
// GPIO DEFINITION
//
#define GPIO_DEFINITION(gpio, function, output, pullup, sticky) \
{gpio, (function <= 3 ? 0x800 : 0) + (function << 8) + (output < 3 ? (output < 2 ? output : 0x02) : 0x08) + \
((sticky == 1) || (pullup < 4) ? ((sticky == 1 ? 0x10 : 0) + (pullup == 0 ? 0x40 : 0) + \
(pullup == 1 ? 0x20 : 0) + (pullup == 3 ? 0x24 : 0) + 0x80) : 0)}

//
// Multi Socket/Die GPIO Definition
//
#define GPIO_DEF_V2(socket, die, gpio, function, output, pullup) \
{(socket << 15) + (die << 13) + (0 << 11) + gpio, (function <= 3 ? 0x800 : 0) + (function << 8) + \
(output < 3 ? (output < 2 ? output : 0x02) : 0x08) + ((pullup == 0 ? 0x40 : 0) + (pullup == 1 ? 0x20 : 0) + (pullup == 3 ? 0x24 : 0) + 0x80)}

#define GPIO_DEF_V3(socket, die, bridge, gpio, function, output, pullup) \
{(socket << 15) + (die << 13) + (bridge << 11) + gpio, (function <= 3 ? 0x800 : 0) + (function << 8) + \
(output < 3 ? (output < 2 ? output : 0x02) : 0x08) + ((pullup == 0 ? 0x40 : 0) + (pullup == 1 ? 0x20 : 0) + (pullup == 3 ? 0x24 : 0) + 0x80)}

#define EC_GPIO_DEFINITION(gpio, output) \
{gpio, output}

#define EC_GPIO_DEF_V2(gpio, output) \
{(0x200 + gpio), output}

//
// PROMONTORY GPIO DEFINITION
//
#define PT_GPIO_DEFINITION(gpio, OutEnB, Out, intEnb, intLevelTrigType, intType, intMask ) \
{gpio, OutEnB + (Out << 1) + (intEnb << 2) + (intLevelTrigType << 3) + (intType << 4) + (intMask << 6)}

//
// GEVENT DEFINITION
//
#define GEVENT_DEFINITION(gevent, enable, scitrig, scilevel, smisci, scis0, scimap, smitrig, smicontrol) \
{gevent, enable + (scitrig <= 1 ? scitrig << 1 : 1 << 10) + (scilevel << 2) + (smisci << 3) + (scis0 << 4) + (scimap << 5) + \
(smitrig << 11) + (smicontrol << 12)}

//
// GPIO INTERRUPT DEFINITION
//
#define GPIO_INTERRUPT_DEFINITION(gpio, enable, leveltrig, activelevel, wakecontrol, debouncecontrol, debouncetimerOutunit, debouncetimerOut) \
{gpio | 0x100, debouncetimerOut + (debouncetimerOutunit << 4) + (debouncecontrol << 5) + (leveltrig << 8) + (activelevel << 9) + (enable << 11) + \
(wakecontrol << 13)}

//
// GPIO DEVICE CONFIG DEFINITION
//
#define GPIO_DEVICE_DEFINITION(deviceid, enable, assert, deassert, hotplug) \
{deviceid, enable + (assert << 2) + (deassert << 3) + (hotplug << 4)}

//
// Internal Clock Request Definition
//
#define PCIE_INCLK(socket, die, clkid, clkreq, devid, devnum, funnum, slotchk) \
{clkid, clkreq, 0, 0, devid, devnum, funnum, slotchk, (socket << 24) + (die << 20) + (0 << 16) + (0 << 28)}

#define PCIE_CLKV2(socket, die, bridge, clkid, clkreq, devid, devnum, funnum, slotchk) \
{clkid, clkreq, 0, 0, devid, devnum, funnum, slotchk, (socket << 24) + (die << 20) + (bridge << 16) + (0 << 28)}

#define PCIE_CLKV3(socket, die, bridge, miscid, clkid, clkreq, devid, devnum, funnum, slotchk) \
{clkid, clkreq, 0, 0, devid, devnum, funnum, slotchk, (socket << 24) + (die << 20) + (bridge << 16) + (miscid << 28)}

#define PcieAddress(Ptr, Bus, Device, Function, Register) \
        Ptr->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Register

#define CPM_DEVICE_OFF                          0
#define CPM_DEVICE_ON                           1
#define CPM_DEVICE_AUTO                         2

#define CPM_TYPE_GPIO_1                         0
#define CPM_TYPE_GPIO_2                         1
#define CPM_TYPE_GPIO_3                         2
#define CPM_TYPE_GPIO_2_OR                      3
#define CPM_TYPE_GPIO_3_OR                      4

#define CPM_GPIO_PIN(pin, value)    (pin + (value << 16))
#define CPM_EC_GPIO_PIN(pin, value) ((pin | 0x100) + (value << 16))
#define CPM_ECRAM_GPIO_PIN(pin, value) ((pin | 0x200) + (value << 16))

///< Device Reset mode.
#define CPM_RESET_ASSERT                        0     ///<   0: Reset Assert.
#define CPM_RESET_DEASSERT                      1     ///<   1: Reset De-assert.
#define CPM_RESET_DELAY                         2     ///<   2: Delay between Assert and Deassert.
#define CPM_PT_RESET_DELAY                      3     ///<   3: Delay between Assert and Deassert for Promontory GPIO.

#define CPM_RESET_GPIO                          0
#define CPM_RESET_NA                            0

#define CPM_POWER_OFF                           0
#define CPM_POWER_ON                            1

///< Device Power Type.
#define CPM_POWER_SET                           0     ///<   0: Set GPIO.
#define CPM_POWER_WAIT                          1     ///<   1: Wait GPIO.
#define CPM_POWER_DELAY                         2     ///<   2: Add Delay.
#define CPM_PT_POWER_DELAY                      3     ///<   3: Add Delay for Promontory GPIO.

// AML Define

#ifndef AML_OPREGION_OP
  #define AML_OPREGION_OP                       0x805B
#endif

//
// BIOS & ACPI SW SMI function number
//
#ifndef CPM_ACPI_RESTORE_SW_SMI
  #define CPM_ACPI_RESTORE_SW_SMI               0xE3
#endif
#ifndef CPM_ACPI_ENABLE_SW_SMI
  #define CPM_ACPI_ENABLE_SW_SMI                0xA0
#endif

#ifndef CPM_ECRAM_BASE_ADDR
  #define CPM_ECRAM_BASE_ADDR                   0x62
#endif

#ifndef CPM_ECRAM_GPIO_OFFSET
  #define CPM_ECRAM_GPIO_OFFSET                 0xAB
#endif

#ifndef CPM_SWSMICMD_SETAUTOUMAMODE
  #define CPM_SWSMICMD_SETAUTOUMAMODE           0xDF
#endif

#ifndef CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI
  #define CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI    0xE4
#endif

#ifndef CPM_X86_IO_REMAP_BASE
  #define CPM_X86_IO_REMAP_BASE                 0x000000FDFC000000ull
#endif

#ifndef CPM_PCI_MMIO_BASE
  #define CPM_PCI_MMIO_BASE                     0x0000000080000000ull
#endif


#endif
