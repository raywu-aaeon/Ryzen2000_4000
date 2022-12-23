/* $NoKeywords:$ */
/**
 * @file
 *
 * PT Secondly Detection Workaround
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2018-04-23 15:14:43 +0800 (Mon, 23 Apr 2018) $
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
*
*/

#define IO_DELAY_PORT                                            0xDE
#define MAX_TIMER                                        0xFFFFFFFFul
#define ELAPSED_TIME_UNIT                                          28
#define ELAPSED_TIME_DIVIDER                                      100
#define PMIO_BASE                                               0x300   // DWORD
#define PCIE0_LC_CNTL_Address                              0x11100068
#define PCIE_LC_LINK_WIDTH_CNTL_Address                    0x11140288
#define PCIE_TX_CREDITS_STATUS_Address                     0x111400d8

#define PCIE_PORT_LANE_STATUS_Address                      0x11140140

#define PORT_LANE_REVERSAL_OFFSET                                   0
#define PORT_LANE_REVERSAL_Width                                    1
#define PORT_LANE_REVERSAL_Mask                                   0x1
#define PHY_LINK_WIDTH_OFFSET                                       1
#define PHY_LINK_WIDTH_Width                                        6
#define PHY_LINK_WIDTH_Mask                                      0x7e

typedef union {
   struct {
    UINT32                                      PORT_LANE_REVERSAL:1; ///<
    UINT32                                          PHY_LINK_WIDTH:6; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PORT_LANE_STATUS_STRUCT;


// Address
#define PCIE_LC_STATE0_ADDRESS                           0x11140294
#define PCIE0_LC_STATE0_ADDRESS                          0x11140294
#define PCIE1_LC_STATE0_ADDRESS                          0x11240294

// Type
#define PCIE_LC_STATE0_TYPE                              TYPE_SMN

#define PCIE_LC_STATE0_LC_CURRENT_STATE_OFFSET           0
#define PCIE_LC_STATE0_LC_CURRENT_STATE_WIDTH            6
#define PCIE_LC_STATE0_LC_CURRENT_STATE_MASK             0x3f
#define PCIE_LC_STATE0_Reserved0_OFFSET                  6
#define PCIE_LC_STATE0_Reserved0_WIDTH                   2
#define PCIE_LC_STATE0_Reserved0_MASK                    0xc0
#define PCIE_LC_STATE0_LC_PREV_STATE1_OFFSET             8
#define PCIE_LC_STATE0_LC_PREV_STATE1_WIDTH              6
#define PCIE_LC_STATE0_LC_PREV_STATE1_MASK               0x3f00
#define PCIE_LC_STATE0_Reserved1_OFFSET                  14
#define PCIE_LC_STATE0_Reserved1_WIDTH                   2
#define PCIE_LC_STATE0_Reserved1_MASK                    0xc000
#define PCIE_LC_STATE0_LC_PREV_STATE2_OFFSET             16
#define PCIE_LC_STATE0_LC_PREV_STATE2_WIDTH              6
#define PCIE_LC_STATE0_LC_PREV_STATE2_MASK               0x3f0000
#define PCIE_LC_STATE0_Reserved2_OFFSET                  22
#define PCIE_LC_STATE0_Reserved2_WIDTH                   2
#define PCIE_LC_STATE0_Reserved2_MASK                    0xc00000
#define PCIE_LC_STATE0_LC_PREV_STATE3_OFFSET             24
#define PCIE_LC_STATE0_LC_PREV_STATE3_WIDTH              6
#define PCIE_LC_STATE0_LC_PREV_STATE3_MASK               0x3f000000
#define PCIE_LC_STATE0_Reserved3_OFFSET                  30
#define PCIE_LC_STATE0_Reserved3_WIDTH                   2
#define PCIE_LC_STATE0_Reserved3_MASK                    0xc0000000


/// PCIE_LC_STATE0
typedef union {
  struct {
    UINT32                                        LC_CURRENT_STATE:6 ; ///<
    UINT32                                               Reserved0:2 ; ///<
    UINT32                                          LC_PREV_STATE1:6 ; ///<
    UINT32                                               Reserved1:2 ; ///<
    UINT32                                          LC_PREV_STATE2:6 ; ///<
    UINT32                                               Reserved2:2 ; ///<
    UINT32                                          LC_PREV_STATE3:6 ; ///<
    UINT32                                               Reserved3:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_STATE0_STRUCT;
// Address
#define PCIE0_SWRST_CONTROL_6_ADDRESS                          0x11180428
#define PCIE1_SWRST_CONTROL_6_ADDRESS                          0x11280428

// Type
#define PCIE1_SWRST_CONTROL_6_TYPE                             TYPE_SMN

#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_A_OFFSET                     0
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_A_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_A_MASK                       0x1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_B_OFFSET                     1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_B_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_B_MASK                       0x2
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_C_OFFSET                     2
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_C_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_C_MASK                       0x4
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_D_OFFSET                     3
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_D_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_D_MASK                       0x8
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_E_OFFSET                     4
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_E_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_E_MASK                       0x10
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_F_OFFSET                     5
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_F_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_F_MASK                       0x20
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_G_OFFSET                     6
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_G_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_G_MASK                       0x40
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_H_OFFSET                     7
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_H_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_H_MASK                       0x80
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_I_OFFSET                     8
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_I_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_I_MASK                       0x100
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_J_OFFSET                     9
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_J_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_J_MASK                       0x200
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_K_OFFSET                     10
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_K_WIDTH                      1
#define PCIE_SWRST_CNTL6_STRUCT_HOLD_TRAINING_K_MASK                       0x400

/// PCIE_SWRST_CNTL6_STRUCT
typedef union {
  struct {
    UINT32                                         HOLD_TRAINING_A:1 ; ///<
    UINT32                                         HOLD_TRAINING_B:1 ; ///<
    UINT32                                         HOLD_TRAINING_C:1 ; ///<
    UINT32                                         HOLD_TRAINING_D:1 ; ///<
    UINT32                                         HOLD_TRAINING_E:1 ; ///<
    UINT32                                         HOLD_TRAINING_F:1 ; ///<
    UINT32                                         HOLD_TRAINING_G:1 ; ///<
    UINT32                                         HOLD_TRAINING_H:1 ; ///<
    UINT32                                         HOLD_TRAINING_I:1 ; ///<
    UINT32                                         HOLD_TRAINING_J:1 ; ///<
    UINT32                                         HOLD_TRAINING_K:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_SWRST_CNTL6_STRUCT;

// Register Name PCIE_LC_CNTL5

// Address
#define PCIE0_LC_CNTL5_ADDRESS                                           0x111402dc
#define PCIE1_LC_CNTL5_ADDRESS                                           0x111412dc
#define PCIE2_LC_CNTL5_ADDRESS                                           0x111422dc
#define PCIE3_LC_CNTL5_ADDRESS                                           0x111432dc
#define PCIE4_LC_CNTL5_ADDRESS                                           0x111442dc
#define PCIE5_LC_CNTL5_ADDRESS                                           0x111452dc
#define PCIE6_LC_CNTL5_ADDRESS                                           0x111462dc
#define PCIE7_LC_CNTL5_ADDRESS                                           0x111472dc
#define PCIE8_LC_CNTL5_ADDRESS                                           0x112402dc
#define PCIE9_LC_CNTL5_ADDRESS                                           0x112412dc
#define PCIEA_LC_CNTL5_ADDRESS                                           0x112422dc
#define PCIEB_LC_CNTL5_ADDRESS                                           0x112432dc
#define PCIEC_LC_CNTL5_ADDRESS                                           0x112442dc
#define PCIED_LC_CNTL5_ADDRESS                                           0x112452dc
#define PCIEE_LC_CNTL5_ADDRESS                                           0x112462dc
#define PCIEF_LC_CNTL5_ADDRESS                                           0x112472dc

// Type
#define PCIE_LC_CNTL5_TYPE                                              TYPE_SMN

#define PCIE_LC_CNTL5_LC_EQ_FS_0_OFFSET                                 0
#define PCIE_LC_CNTL5_LC_EQ_FS_0_WIDTH                                  6
#define PCIE_LC_CNTL5_LC_EQ_FS_0_MASK                                   0x3f
#define PCIE_LC_CNTL5_LC_EQ_FS_8_OFFSET                                 6
#define PCIE_LC_CNTL5_LC_EQ_FS_8_WIDTH                                  6
#define PCIE_LC_CNTL5_LC_EQ_FS_8_MASK                                   0xfc0
#define PCIE_LC_CNTL5_LC_EQ_LF_0_OFFSET                                 12
#define PCIE_LC_CNTL5_LC_EQ_LF_0_WIDTH                                  6
#define PCIE_LC_CNTL5_LC_EQ_LF_0_MASK                                   0x3f000
#define PCIE_LC_CNTL5_LC_EQ_LF_8_OFFSET                                 18
#define PCIE_LC_CNTL5_LC_EQ_LF_8_WIDTH                                  6
#define PCIE_LC_CNTL5_LC_EQ_LF_8_MASK                                   0xfc0000
#define PCIE_LC_CNTL5_LC_DSC_EQ_FS_LF_INVALID_TO_PRESETS_OFFSET         24
#define PCIE_LC_CNTL5_LC_DSC_EQ_FS_LF_INVALID_TO_PRESETS_WIDTH          1
#define PCIE_LC_CNTL5_LC_DSC_EQ_FS_LF_INVALID_TO_PRESETS_MASK           0x1000000
#define PCIE_LC_CNTL5_LC_TX_SWING_OVERRIDE_OFFSET                       25
#define PCIE_LC_CNTL5_LC_TX_SWING_OVERRIDE_WIDTH                        1
#define PCIE_LC_CNTL5_LC_TX_SWING_OVERRIDE_MASK                         0x2000000
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_OFFSET                      26
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_WIDTH                       1
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_MASK                        0x4000000
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_TEST_OFFSET                 27
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_TEST_WIDTH                  1
#define PCIE_LC_CNTL5_LC_ACCEPT_ALL_PRESETS_TEST_MASK                   0x8000000
#define PCIE_LC_CNTL5_LC_WAIT_IN_DETECT_OFFSET                          28
#define PCIE_LC_CNTL5_LC_WAIT_IN_DETECT_WIDTH                           1
#define PCIE_LC_CNTL5_LC_WAIT_IN_DETECT_MASK                            0x10000000
#define PCIE_LC_CNTL5_LC_HOLD_TRAINING_MODE_OFFSET                      29
#define PCIE_LC_CNTL5_LC_HOLD_TRAINING_MODE_WIDTH                       3
#define PCIE_LC_CNTL5_LC_HOLD_TRAINING_MODE_MASK                        0xe0000000L

/// PCIE_LC_CNTL5_STRUCT
typedef union {
  struct {
    UINT32                                              LC_EQ_FS_0:6 ; ///<
    UINT32                                              LC_EQ_FS_8:6 ; ///<
    UINT32                                              LC_EQ_LF_0:6 ; ///<
    UINT32                                              LC_EQ_LF_8:6 ; ///<
    UINT32                      LC_DSC_EQ_FS_LF_INVALID_TO_PRESETS:1 ; ///<
    UINT32                                    LC_TX_SWING_OVERRIDE:1 ; ///<
    UINT32                                   LC_ACCEPT_ALL_PRESETS:1 ; ///<
    UINT32                              LC_ACCEPT_ALL_PRESETS_TEST:1 ; ///<
    UINT32                                       LC_WAIT_IN_DETECT:1 ; ///<
    UINT32                                   LC_HOLD_TRAINING_MODE:3 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_CNTL5_STRUCT;

VOID
PTSecondlyDetectingWorkaround (
  IN       GNB_HANDLE                *GnbHandle,
  IN       UINT32                    MaxPTLane,
  IN       BOOLEAN                   LaneReversal,
  IN       UINTN                     PtPortId
  );

BOOLEAN
CheckPTLaneReversal (
  IN       BOOLEAN                   LaneReversal,
  IN       UINT32                    PciePortLaneStatusAddressData
);

VOID
STATIC
NBIO_Delay_Xus (
  IN  CONST     EFI_PEI_SERVICES   **PeiServices,
  IN  UINT32    xus
  );

BOOLEAN
CheckAbnormalPTLaneWidth (
  IN       UINT32                    MaxPTLane,
  IN       UINT32                    PcieLcLinkWidthAddressData
  );

BOOLEAN
CheckPTLaneReversal (
  IN       BOOLEAN                   LaneReversal,
  IN       UINT32                    PciePortLaneStatusAddressData
  );

