
/**
 * @file
 *
 * This file was automatically generated from the PPR.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: Nbio
 *
 */
#ifndef _GNBREGISTERSSSP_H_
#define _GNBREGISTERSSSP_H_

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
*
*/

//
// Goal is to slowly wean us off of the ZP version for SSP
// Todo: Modify ppr header include guards so that they have an architecture suffix. As it is right now the include guards will
// be the same for ZP and SSP (auto generated) so only one will get used not both...
//
#include "GnbRegistersSSP/IOAPIC.h"
#include "GnbRegistersSSP/IOHC.h"
#include "GnbRegistersSSP/IOAGR.h"
#include "GnbRegistersSSP/IOMMUL1.h"      //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/IOMMUL2.h"
#include "GnbRegistersSSP/IOMMUMMIO.h"
#include "GnbRegistersSSP/MCA_NBIO.h"
#include "GnbRegistersSSP/MCA_PCIE.h"
#include "GnbRegistersSSP/NBIFRCCFG.h"
#include "GnbRegistersSSP/NBIFEPF0CFG.h"
#include "GnbRegistersSSP/NBIFEPFNCFG.h"
#include "GnbRegistersSSP/NBIFMM.h"       //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/PCIECORE.h"     //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/PCIEPORT.h"     //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/PCIERCCFG.h"
#include "GnbRegistersSSP/SDPMUX.h"
#include "GnbRegistersSSP/SMU_PWR.h"      //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/SST.h"          //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/SYSHUBMM.h"     //*NBIO_TODO : Need to NDA values
#include "GnbRegistersSSP/MCA_LS.h"
#include "GnbRegistersSSP/Core_X86_Msr.h"

#ifndef NBIO_SPACE
  #define  NBIO_SPACE(HANDLE, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20))
#endif

#ifndef WRAP_SPACE
  #define  WRAP_SPACE(HANDLE, WRAPPER, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (WRAPPER->WrapId << 22))
#endif

#ifndef PORT_SPACE
  #define  PORT_SPACE(HANDLE, WRAPPER, PORTINDEX, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (WRAPPER->WrapId << 22) + (PORTINDEX << 12))
#endif

#ifndef IOHC_PORT_SPACE
  #define  IOHC_PORT_SPACE(HANDLE, WRAPPER, PORTINDEX, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (WRAPPER->WrapId * 0x100) + (PORTINDEX * 0x20))
#endif

#ifndef IOHC_BRIDGE_SPACE
  #define  IOHC_BRIDGE_SPACE(HANDLE, ENGINE, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (ENGINE->Type.Port.LogicalBridgeId << 10))
#endif

//
// Need to find new #defines in ppr generated files for these values
//
#define SLOT_CAP_ADDRESS                                       0x6C

//
// Type
#define SLOT_CAP_TYPE                                          TYPE_SMN

#define SLOT_CAP_ATTN_BUTTON_PRESENT_OFFSET                   0
#define SLOT_CAP_ATTN_BUTTON_PRESENT_WIDTH                    1
#define SLOT_CAP_ATTN_BUTTON_PRESENT_MASK                     0x1
#define SLOT_CAP_PWR_CONTROLLER_PRESENT_OFFSET                1
#define SLOT_CAP_PWR_CONTROLLER_PRESENT_WIDTH                 1
#define SLOT_CAP_PWR_CONTROLLER_PRESENT_MASK                  0x2
#define SLOT_CAP_MRL_SENSOR_PRESENT_OFFSET                    2
#define SLOT_CAP_MRL_SENSOR_PRESENT_WIDTH                     1
#define SLOT_CAP_MRL_SENSOR_PRESENT_MASK                      0x4
#define SLOT_CAP_ATTN_INDICATOR_PRESENT_OFFSET                3
#define SLOT_CAP_ATTN_INDICATOR_PRESENT_WIDTH                 1
#define SLOT_CAP_ATTN_INDICATOR_PRESENT_MASK                  0x8
#define SLOT_CAP_PWR_INDICATOR_PRESENT_OFFSET                 4
#define SLOT_CAP_PWR_INDICATOR_PRESENT_WIDTH                  1
#define SLOT_CAP_PWR_INDICATOR_PRESENT_MASK                   0x10
#define SLOT_CAP_HOTPLUG_SURPRISE_OFFSET                      5
#define SLOT_CAP_HOTPLUG_SURPRISE_WIDTH                       1
#define SLOT_CAP_HOTPLUG_SURPRISE_MASK                        0x20
#define SLOT_CAP_HOTPLUG_CAPABLE_OFFSET                       6
#define SLOT_CAP_HOTPLUG_CAPABLE_WIDTH                        1
#define SLOT_CAP_HOTPLUG_CAPABLE_MASK                         0x40
#define SLOT_CAP_SLOT_PWR_LIMIT_VALUE_OFFSET                  7
#define SLOT_CAP_SLOT_PWR_LIMIT_VALUE_WIDTH                   8
#define SLOT_CAP_SLOT_PWR_LIMIT_VALUE_MASK                    0x7f80
#define SLOT_CAP_SLOT_PWR_LIMIT_SCALE_OFFSET                  15
#define SLOT_CAP_SLOT_PWR_LIMIT_SCALE_WIDTH                   2
#define SLOT_CAP_SLOT_PWR_LIMIT_SCALE_MASK                    0x18000
#define SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_OFFSET         17
#define SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_WIDTH          1
#define SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_MASK           0x20000
#define SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_OFFSET        18
#define SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_WIDTH         1
#define SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_MASK          0x40000
#define SLOT_CAP_PHYSICAL_SLOT_NUM_OFFSET                     19
#define SLOT_CAP_PHYSICAL_SLOT_NUM_WIDTH                      13
#define SLOT_CAP_PHYSICAL_SLOT_NUM_MASK                       0xfff80000L
//

// NBIO_TODO: Need to use the pcilib offsets?
// DEVICE_CNTL2
#define DEVICE_CNTL2_ADDRESS                                   0x80
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_OFFSET                  0
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_WIDTH                   4

//// Type
//#define SLOT_CNTL_TYPE                                         TYPE_SMN

#define SLOT_CNTL_ATTN_BUTTON_PRESSED_EN_OFFSET                0
#define SLOT_CNTL_ATTN_BUTTON_PRESSED_EN_WIDTH                 1
#define SLOT_CNTL_ATTN_BUTTON_PRESSED_EN_MASK                  0x1
#define SLOT_CNTL_PWR_FAULT_DETECTED_EN_OFFSET                 1
#define SLOT_CNTL_PWR_FAULT_DETECTED_EN_WIDTH                  1
#define SLOT_CNTL_PWR_FAULT_DETECTED_EN_MASK                   0x2
#define SLOT_CNTL_MRL_SENSOR_CHANGED_EN_OFFSET                 2
#define SLOT_CNTL_MRL_SENSOR_CHANGED_EN_WIDTH                  1
#define SLOT_CNTL_MRL_SENSOR_CHANGED_EN_MASK                   0x4
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_EN_OFFSET            3
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_EN_WIDTH             1
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_EN_MASK              0x8
#define SLOT_CNTL_COMMAND_COMPLETED_INTR_EN_OFFSET             4
#define SLOT_CNTL_COMMAND_COMPLETED_INTR_EN_WIDTH              1
#define SLOT_CNTL_COMMAND_COMPLETED_INTR_EN_MASK               0x10
#define SLOT_CNTL_HOTPLUG_INTR_EN_OFFSET                       5
#define SLOT_CNTL_HOTPLUG_INTR_EN_WIDTH                        1
#define SLOT_CNTL_HOTPLUG_INTR_EN_MASK                         0x20
#define SLOT_CNTL_ATTN_INDICATOR_CNTL_OFFSET                   6
#define SLOT_CNTL_ATTN_INDICATOR_CNTL_WIDTH                    2
#define SLOT_CNTL_ATTN_INDICATOR_CNTL_MASK                     0xc0
#define SLOT_CNTL_PWR_INDICATOR_CNTL_OFFSET                    8
#define SLOT_CNTL_PWR_INDICATOR_CNTL_WIDTH                     2
#define SLOT_CNTL_PWR_INDICATOR_CNTL_MASK                      0x300
#define SLOT_CNTL_PWR_CONTROLLER_CNTL_OFFSET                   10
#define SLOT_CNTL_PWR_CONTROLLER_CNTL_WIDTH                    1
#define SLOT_CNTL_PWR_CONTROLLER_CNTL_MASK                     0x400
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_CNTL_OFFSET            11
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_CNTL_WIDTH             1
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_CNTL_MASK              0x800
#define SLOT_CNTL_DL_STATE_CHANGED_EN_OFFSET                   12
#define SLOT_CNTL_DL_STATE_CHANGED_EN_WIDTH                    1
#define SLOT_CNTL_DL_STATE_CHANGED_EN_MASK                     0x1000
//Reserved 3
#define SLOT_CNTL_ATTN_BUTTON_PRESSED_OFFSET                   16
#define SLOT_CNTL_ATTN_BUTTON_PRESSED_WIDTH                    1
#define SLOT_CNTL_ATTN_BUTTON_PRESSED_MASK                     0x10000
#define SLOT_CNTL_PWR_FAULT_DETECTED_OFFSET                    17
#define SLOT_CNTL_PWR_FAULT_DETECTED_WIDTH                     1
#define SLOT_CNTL_PWR_FAULT_DETECTED_MASK                      0x20000
#define SLOT_CNTL_MRL_SENSOR_CHANGED_OFFSET                    18
#define SLOT_CNTL_MRL_SENSOR_CHANGED_WIDTH                     1
#define SLOT_CNTL_MRL_SENSOR_CHANGED_MASK                      0x40000
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_OFFSET               19
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_WIDTH                1
#define SLOT_CNTL_PRESENCE_DETECT_CHANGED_MASK                 0x80000
#define SLOT_CNTL_COMMAND_COMPLETED_OFFSET                     20
#define SLOT_CNTL_COMMAND_COMPLETED_WIDTH                      1
#define SLOT_CNTL_COMMAND_COMPLETED_MASK                       0x100000
#define SLOT_CNTL_MRL_SENSOR_STATE_OFFSET                      21
#define SLOT_CNTL_MRL_SENSOR_STATE_WIDTH                       1
#define SLOT_CNTL_MRL_SENSOR_STATE_MASK                        0x200000
#define SLOT_CNTL_PRESENCE_DETECT_STATE_OFFSET                 22
#define SLOT_CNTL_PRESENCE_DETECT_STATE_WIDTH                  1
#define SLOT_CNTL_PRESENCE_DETECT_STATE_MASK                   0x400000
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_STATUS_OFFSET          23
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_STATUS_WIDTH           1
#define SLOT_CNTL_ELECTROMECH_INTERLOCK_STATUS_MASK            0x800000
#define SLOT_CNTL_DL_STATE_CHANGED_OFFSET                      24
#define SLOT_CNTL_DL_STATE_CHANGED_WIDTH                       1
#define SLOT_CNTL_DL_STATE_CHANGED_MASK                        0x1000000

#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_OFFSET                          14
#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_WIDTH                           2
#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_MASK                            0xc000

#define SMN_0x13B31004_BridgeDis_OFFSET                        0
#define SMN_0x13B31004_BridgeDis_WIDTH                         1
#define SMN_0x13B31004_BridgeDis_MASK                          0x1

#define LINK_CTL_STS_DL_ACTIVE_OFFSET                          29

// NBIO_TODO: These seem to conflict with the PPR
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_OFFSET            1
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_WIDTH             1
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_MASK              0x2
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_OFFSET   2
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_WIDTH    1
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_MASK     0x4
#define PCIEP_STRAP_MISC_STRAP_CCIX_EN_OFFSET                  6
#define PCIEP_STRAP_MISC_STRAP_CCIX_EN_WIDTH                   1
#define PCIEP_STRAP_MISC_STRAP_CCIX_EN_MASK                    0x40
#define PCIEP_STRAP_MISC_STRAP_CCIX_OPT_TLP_FMT_SUPPORT_OFFSET 7
#define PCIEP_STRAP_MISC_STRAP_CCIX_OPT_TLP_FMT_SUPPORT_WIDTH  1
#define PCIEP_STRAP_MISC_STRAP_CCIX_OPT_TLP_FMT_SUPPORT_MASK   0x80

// NBIO_TODO: Verify working on SSP
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_OFFSET                          12
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_WIDTH                           2
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_MASK                            0x3000
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_OFFSET                          14
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_WIDTH                           2
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_MASK                            0xc000


#endif /*_GNBREGISTERSSSP_H_*/

