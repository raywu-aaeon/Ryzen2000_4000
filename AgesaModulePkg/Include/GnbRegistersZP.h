/* $NoKeywords:$ */
/**
 * @file
 *
 * AGESA gnb file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  GNB
 * @e \$Revision: 315399 $   @e \$Date: 2015-03-25 20:03:45 -0500 (Wed, 25 Mar 2015) $
 *
 */
/*
 ******************************************************************************
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
#ifndef _GNBREGISTERSCZ_H_
#define _GNBREGISTERSCZ_H_
#define  TYPE_D0F0                  0x1
#define  TYPE_D0F0x64               0x2
#define  TYPE_D0F0x98               0x3
#define  TYPE_D0F0xBC               0x4
#define  TYPE_SMN                   TYPE_D0F0xBC
#define  TYPE_NBIOAPICCFG           TYPE_SMN
#define  TYPE_IOHC                  TYPE_SMN
#define  TYPE_NBMISC                TYPE_SMN
#define  TYPE_PWR                   TYPE_SMN
#define  TYPE_IOAGR                 TYPE_SMN
#define  TYPE_IOAGRCFG              TYPE_SMN
#define  TYPE_SDPMUXCFG             TYPE_SMN
#define  TYPE_IOMMUL1IOAGR          TYPE_SMN
#define  TYPE_IOMMUL1NBIF           TYPE_SMN
#define  TYPE_IOMMUL1PCIE0          TYPE_SMN
#define  TYPE_IOMMUL1PCIE1          TYPE_SMN
#define  TYPE_IOMMUL2A              TYPE_SMN
#define  TYPE_NBRASCFG              TYPE_SMN
//
#define BAPM_MASK               0x00000001
#define POWER_ESTIMATOR_MASK    0x00000002
#define THERMAL_CONTROLLER_MASK 0x00000004
#define TDC_LIMITING_MASK       0x00000008
#define PKG_PWR_LIMITING_MASK   0x00000010
#define LCLK_DPM_MASK           0x00000020
#define VOLTAGE_CONTROLLER_MASK 0x00000040
#define GEAPM_MASK              0x00000080
#define BBB_MASK                0x00000100
#define IBS_MASK                0x00000200
#define PSTATE_ARBITER_MASK     0x00000400
#define NB_DPM_MASK             0x00000800
#define LCLK_DEEP_SLEEP_MASK    0x00001000
#define ULV_MASK                0x00002000
#define GFX_CU_PG_MASK          0x00004000
#define AVFS_MASK               0x00008000
#define UVD_DPM_MASK            0x00010000
#define VQ_CONTROLLER_MASK      0x00020000
#define ACP_DPM_MASK            0x00040000
#define SCLK_DPM_MASK           0x00080000
#define PRE_FETCH_DATA_MASK     0x00100000
#define DFS_BYPASS_MASK         0x00200000
#define HTC_MASK                0x00400000
#define VDDGFX_MASK             0x00800000
#define LEAPM_MASK              0x01000000
#define CONN_STDBY_MASK         0x02000000
#define PORT80_MONITOR_MASK     0x04000000
#define PSPCLK_DPM_MASK         0x08000000
#define STAPM_MASK              0x10000000
#define DETERMINISM_MASK        0x20000000
#define CPU_STRETCHER_MASK      0x40000000
#define SCLK_STRETCHER_MASK     0x80000000


// **** D0F0x04 Register Definition ****
// Address
#define D0F0x04_ADDRESS                                         0x4

// Type
#define D0F0x04_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x04_IoAccessEn_OFFSET                               0
#define D0F0x04_IoAccessEn_WIDTH                                1
#define D0F0x04_IoAccessEn_MASK                                 0x1
#define D0F0x04_MemAccessEn_OFFSET                              1
#define D0F0x04_MemAccessEn_WIDTH                               1
#define D0F0x04_MemAccessEn_MASK                                0x2
#define D0F0x04_BusMasterEn_OFFSET                              2
#define D0F0x04_BusMasterEn_WIDTH                               1
#define D0F0x04_BusMasterEn_MASK                                0x4
#define D0F0x04_Reserved_19_3_OFFSET                            3
#define D0F0x04_Reserved_19_3_WIDTH                             17
#define D0F0x04_Reserved_19_3_MASK                              0xffff8
#define D0F0x04_CapList_OFFSET                                  20
#define D0F0x04_CapList_WIDTH                                   1
#define D0F0x04_CapList_MASK                                    0x100000
#define D0F0x04_Reserved_31_21_OFFSET                           21
#define D0F0x04_Reserved_31_21_WIDTH                            11
#define D0F0x04_Reserved_31_21_MASK                             0xffe00000

/// D0F0x04
typedef union {
  struct {                                                              ///<
    UINT32                                               IoAccessEn:1 ; ///<
    UINT32                                              MemAccessEn:1 ; ///<
    UINT32                                              BusMasterEn:1 ; ///<
    UINT32                                            Reserved_19_3:17; ///<
    UINT32                                                  CapList:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x04_STRUCT;

// Address
#define NB_TOP_OF_DRAM_SLOT1_ADDRESS                           0x90

// Type
#define NB_TOP_OF_DRAM_SLOT1_TYPE                              TYPE_D0F0

#define D0F0_090_TOP_OF_DRAM_BIT_32_OFFSET                     0
#define D0F0_090_TOP_OF_DRAM_BIT_32_WIDTH                      1
#define D0F0_090_TOP_OF_DRAM_BIT_32_MASK                       0x1
//Reserved 22:1
#define D0F0_090_TOP_OF_DRAM_OFFSET                            23
#define D0F0_090_TOP_OF_DRAM_WIDTH                             9
#define D0F0_090_TOP_OF_DRAM_MASK                              0xff800000L

/// D0F0_090
typedef union {
  struct {
    UINT32                                      TOP_OF_DRAM_BIT_32:1 ; ///<
    UINT32                                           Reserved_22_1:22; ///<
    UINT32                                             TOP_OF_DRAM:9 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} D0F0_090_STRUCT;

// **** D0F0xB8 Register Definition ****
// Address
#define D0F0xB8_ADDRESS                                         0xb8

// Type
#define D0F0xB8_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xB8_NbSmuIndAddr_OFFSET                             0
#define D0F0xB8_NbSmuIndAddr_WIDTH                              32
#define D0F0xB8_NbSmuIndAddr_MASK                               0xffffffff

/// D0F0xB8
typedef union {
  struct {                                                              ///<
    UINT32                                             NbSmuIndAddr:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xB8_STRUCT;

/// ZP PPR
// DBGU GROUP BASE
#define DBGU_NBIO_PORTA                                           0x700
#define DBGU_IO_PORTA                                             0x680
#define DBGU1_PORTA                                               0x780
// DBGU PORTA ACCESS REGISTERS
#define DBGU_PORTA_INDEX_ADDRESS                                  0x00
#define DBGU_PORTA_DATALO_ADDRESS                                 0x04
#define DBGU_PORTA_DATAHI_ADDRESS                                 0x08

#define DBGU_INDEX_Index_OFFSET                                   0
#define DBGU_INDEX_Index_WIDTH                                    7
#define DBGU_INDEX_Index_MASK                                     0x7f
#define DBGU_INDEX_Reserved1_OFFSET                               7
#define DBGU_INDEX_Reserved1_WIDTH                                5
#define DBGU_INDEX_Reserved1_MASK                                 0xf80
#define DBGU_INDEX_UnitId_OFFSET                                  12
#define DBGU_INDEX_UnitId_WIDTH                                   4
#define DBGU_INDEX_UnitId_MASK                                    0xF000
#define DBGU_INDEX_Reserved2_OFFSET                               16
#define DBGU_INDEX_Reserved2_WIDTH                                15
#define DBGU_INDEX_Reserved2_MASK                                 0x7fff0000
#define DBGU_INDEX_WriteEnable_OFFSET                             31
#define DBGU_INDEX_WriteEnable_WIDTH                              1
#define DBGU_INDEX_WriteEnable_MASK                               0x80000000

/// DBGU_INDEX
typedef union {
  struct {
    UINT32                                                   Index:7 ; ///<
    UINT32                                               Reserved1:5 ; ///<
    UINT32                                                  UnitId:4 ; ///<
    UINT32                                               Reserved2:15; ///<
    UINT32                                             WriteEnable:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} DBGU_INDEX_STRUCT;

// DBGU UNIT ID
#define DBGU_TOP_UID                                              0x0
#define DBGU_DSM_UID                                              0x1
#define DBGU_TRIGGER_MERGE_UID                                    0x2
#define DBGU_DRB_UID                                              0x3
#define DBGU_MUX_UID                                              0x6
#define DBGU_PKTR_UID                                             0x7
#define DBGU_DBUS_PROG_UID                                        0x8

// DBGU TOP INDEX
#define DBGU_CONTROL                                              0x0
#define DBGU_STATUS                                               0x1
#define DBGU_ID                                                   0x2

// DBGU DSM INDEX
#define DSM_CONTROL_STATUS                                        0x0
#define DSM_CLK_CNT                                               0x1
#define DSM_CLK_MATCH                                             0x2
#define DSM_GEN_CNT_0                                             0x3
#define DSM_GEN_CNT_1                                             0x4
#define DSM_GEN_CNT_2                                             0x5
#define DSM_GEN_CNT_3                                             0x6
#define DSM_GEN_CNT_4                                             0x7
#define DSM_GEN_CNT_5                                             0x8
#define DSM_RND_LFSR                                              0x9
#define DSM_RND_POLY                                              0xA
#define DSM_RND_MASK0                                             0xB
#define DSM_RND_MATCH0                                            0xC
#define DSM_TRIG_DATA_0                                           0xD
#define DSM_TRIG_DATA_1                                           0xE
#define DSM_TRIG_SEL                                              0xF
#define DSM_SM_VEC_0_0                                            0x10
#define DSM_SM_VEC_0_1                                            0x11
#define DSM_SM_VEC_0_2                                            0x12
#define DSM_SM_VEC_0_3                                            0x13
#define DSM_SM_VEC_0_4                                            0x14
#define DSM_SM_VEC_1_0                                            0x15
#define DSM_SM_VEC_1_1                                            0x16
#define DSM_SM_VEC_1_2                                            0x17
#define DSM_SM_VEC_1_3                                            0x18
#define DSM_SM_VEC_1_4                                            0x19
#define DSM_SM_VEC_2_0                                            0x1A
#define DSM_SM_VEC_2_1                                            0x1B
#define DSM_SM_VEC_2_2                                            0x1C
#define DSM_SM_VEC_2_3                                            0x1D
#define DSM_SM_VEC_2_4                                            0x1E
#define DSM_SM_VEC_3_0                                            0x1F
#define DSM_SM_VEC_3_1                                            0x20
#define DSM_SM_VEC_3_2                                            0x21
#define DSM_SM_VEC_3_3                                            0x22
#define DSM_SM_VEC_3_4                                            0x23
#define DSM_TRIG_PRE_SEL1                                         0x24
#define DSM_TRIG_PRE_SEL2                                         0x25
#define DSM_ACT_PRE_SEL01                                         0x26
#define DSM_ACT_PRE_SEL23                                         0x27
#define DSM_CONTROL_STATUS_2                                      0x28
#define DSM_RND_MASK1                                             0x29
#define DSM_RND_MATCH1                                            0x2A
#define DSM_DBG_DELAY                                             0x2B
#define DSM_TRIG_PRE_SEL3                                         0x2C
#define DIRECT_ACTION_CONFIG                                      0x2D
#define DSM2MCODEC0                                               0x2E
#define MCODE2DSMC0                                               0x2F
#define DSM2MCODEC1                                               0x30
#define MCODE2DSMC1                                               0x31
#define DSM_DBG_MASK                                              0x32
#define DSM_DBG_BUS_MISR                                          0x33
#define DSM_PERM_TRIG_MATCH_MASK_0                                0x34
#define DSM_PERM_TRIG_MATCH_MASK_1                                0x35
#define DSM_PERM_TRIG_MATCH_MASK_2                                0x36
#define DSM_PERM_TRIG_MATCH_MASK_3                                0x37
#define DSM_PERM_TRIG_PERMS                                       0x38
#define DSM_F2F_MATCH_MASK                                        0x39
#define DSM_TRACE_ACC                                             0x3A

// DBGU TRIGGER MERGE INDEX
#define CROSS_TRIGGER_CONTROL_0                                   0x0
#define CROSS_TRIGGER_CONTROL_1                                   0x1

// DBGU DRB INDEX
#define DRB_CONTROL                                               0x0
#define DRB_BUFFER_ACCESS_INDEX                                   0x1
#define DRB_BUFFER_ACCESS_METADATA                                0x2
#define DRB_BUFFER_ACCESS_DATA                                    0x3
#define DRB_WATER_MARK_CONTROL                                    0x4

// DBGU DRB INDEX
#define DBUS_MUX_FINAL_BYTES_CONTROL_0                            0x0
#define DBUS_MUX_CDC_CONTROL                                      0x1
#define DBUS_MUX_PASSTHRU_CONTROL                                 0x2

// DBGU PKTR INDEX
#define PKTR_STATUS                                               0x0
#define PKTR_ADDRESS_BASE                                         0x1
#define PKTR_ADDRESS_LIMIT                                        0x2
#define PKTR_ADDRESS_POINTER                                      0x3

// DBGU PROGRAMMER
#define DBUS_PROG_STATUS                                          0x0
#define DBUS_PROG_INITIALIZE                                      0x1
#define DBUS_PROG_PROGRAM_0                                       0x2
#define DBUS_PROG_PROGRAM_1                                       0x3
#define DBUS_PROG_PROGRAM_2                                       0x4
#define DBUS_PROG_PROGRAM_3                                       0x5
#define DBUS_PROG_PROGRAM_4                                       0x6
#define DBUS_PROG_PROGRAM_5                                       0x7
#define DBUS_PROG_PROGRAM_6                                       0x8
#define DBUS_PROG_PROGRAM_7                                       0x9
#define DBUS_PROG_FINALIZE                                        0xA



/// DBGU_CONTROL
typedef union {
  struct {
    UINT64                                               Control_0:1 ; ///<
    UINT64                                               DsmEnable:1 ; ///<
    UINT64                                                ClkEnDsm:1 ; ///<
    UINT64                                                ClkEnDrb:1 ; ///<
    UINT64                                                ClkEnOvr:1 ; ///<
    UINT64                                            Control_63_4:59; ///<
  } Field;                                                             ///<
  UINT64 Value;                                                        ///<
} DBGU_CONTROL_STRUCT;

/// DRB_CONTROL
typedef union {
  struct {
    UINT64                                                 DataSel:2 ; ///<
    UINT64                                                PackMode:2 ; ///<
    UINT64                                              ClearIndex:1 ; ///<
    UINT64                                              BufferFull:1 ; ///<
    UINT64                                            WaterMarkHit:1 ; ///<
    UINT64                                              Reserved_7:1 ; ///<
    UINT64                                                  FifoEn:1 ; ///<
    UINT64                                           Reserved_31_9:23; ///<
    UINT64                                             FifoRdIndex:10; ///<
    UINT64                                          Reserved_47_39:6 ; ///<
    UINT64                                              DbgWrIndex:10; ///<
    UINT64                                          Reserved_63_55:6 ; ///<
  } Field;                                                             ///<
  UINT64 Value;                                                        ///<
} DRB_CONTROL_STRUCT;

/// DBUS_PROG_STATUS
typedef union {
  struct {
    UINT64                                          ProgrammerBusy:1 ; ///<
    UINT64                                       InitializePending:1 ; ///<
    UINT64                                         Program0Pending:1 ; ///<
    UINT64                                         Program1Pending:1 ; ///<
    UINT64                                         Program2Pending:1 ; ///<
    UINT64                                         Program3Pending:1 ; ///<
    UINT64                                         Program4Pending:1 ; ///<
    UINT64                                         Program5Pending:1 ; ///<
    UINT64                                         Program6Pending:1 ; ///<
    UINT64                                         Program7Pending:1 ; ///<
    UINT64                                         FinalizePending:1 ; ///<
    UINT64                                          Reserved_63_11:53; ///<
  } Field;                                                             ///<
  UINT64 Value;                                                        ///<
} DBUS_PROG_STATUS_STRUCT;

/// DBUS_MUX_CDC_CONTROL
typedef union {
  struct {
    UINT64                                         ValidGateEnable:1 ; ///<
    UINT64                                         Byte0ByteSelect:1 ; ///<
    UINT64                                         Byte0DataSelect:2 ; ///<
    UINT64                                           Byte0PackMode:2 ; ///<
    UINT64                                         Byte0GangEnable:1 ; ///<
    UINT64                                             Byte0GangId:1 ; ///<
    UINT64                                         Byte1ByteSelect:1 ; ///<
    UINT64                                         Byte1DataSelect:2 ; ///<
    UINT64                                           Byte1PackMode:2 ; ///<
    UINT64                                         Byte1GangEnable:1 ; ///<
    UINT64                                             Byte1GangId:1 ; ///<
    UINT64                                         Byte2ByteSelect:1 ; ///<
    UINT64                                         Byte2DataSelect:2 ; ///<
    UINT64                                           Byte2PackMode:2 ; ///<
    UINT64                                         Byte2GangEnable:1 ; ///<
    UINT64                                             Byte2GangId:1 ; ///<
    UINT64                                         Byte3ByteSelect:1 ; ///<
    UINT64                                         Byte3DataSelect:2 ; ///<
    UINT64                                           Byte3PackMode:2 ; ///<
    UINT64                                         Byte3GangEnable:1 ; ///<
    UINT64                                             Byte3GangId:1 ; ///<
    UINT64                                         Byte4ByteSelect:1 ; ///<
    UINT64                                         Byte4DataSelect:2 ; ///<
    UINT64                                           Byte4PackMode:2 ; ///<
    UINT64                                         Byte4GangEnable:1 ; ///<
    UINT64                                             Byte4GangId:1 ; ///<
    UINT64                                         Byte5ByteSelect:1 ; ///<
    UINT64                                         Byte5DataSelect:2 ; ///<
    UINT64                                           Byte5PackMode:2 ; ///<
    UINT64                                         Byte5GangEnable:1 ; ///<
    UINT64                                             Byte5GangId:1 ; ///<
    UINT64                                         Byte6ByteSelect:1 ; ///<
    UINT64                                         Byte6DataSelect:2 ; ///<
    UINT64                                           Byte6PackMode:2 ; ///<
    UINT64                                         Byte6GangEnable:1 ; ///<
    UINT64                                             Byte6GangId:1 ; ///<
    UINT64                                         Byte7ByteSelect:1 ; ///<
    UINT64                                         Byte7DataSelect:2 ; ///<
    UINT64                                           Byte7PackMode:2 ; ///<
    UINT64                                         Byte7GangEnable:1 ; ///<
    UINT64                                             Byte7GangId:1 ; ///<
    UINT64                                               CdcResetN:1 ; ///<
    UINT64                                          Reserved_63_58:6 ; ///<
  } Field;                                                             ///<
  UINT64 Value;                                                        ///<
} DBUS_MUX_CDC_CONTROL_STRUCT;


// PCIE STRAP ACCESS REGISTERS
#define PCIE0_STRAP_INDEX_ADDRESS                                  0x4A348
#define PCIE0_STRAP_DATA_ADDRESS                                   0x4A34C
#define PCIE1_STRAP_INDEX_ADDRESS                                  0x4A3C8
#define PCIE1_STRAP_DATA_ADDRESS                                   0x4A3CC

// Address
#define THREAD_ENABLE_ADDRESS                                  0x5a818

// Type
#define THREAD_ENABLE_TYPE                                     TYPE_PWR

#define PWR_018_ThreadEn_OFFSET                                0
#define PWR_018_ThreadEn_WIDTH                                 16
#define PWR_018_ThreadEn_MASK                                  0xffff

/// PWR_018
typedef union {
  struct {
    UINT32                                                ThreadEn:16; ///<
    UINT32                                               Reserved1:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PWR_018_STRUCT;


// Address
#define CORE_LDO_FDD_VERSION_ADDRESS                           0x5A274

// Type
#define CORE_LDO_FDD_VERSION_TYPE                              TYPE_SMN
// Field Data
#define CORE_LDO_FDD_VERSION_OFFSET                            4
#define CORE_LDO_FDD_VERSION_WIDTH                             2
#define CORE_LDO_FDD_VERSION_MASK                              0x3


// Address
#define THREAD_CONFIGURATION_ADDRESS                           0x5a81c

// Type
#define THREAD_CONFIGURATION_TYPE                              TYPE_PWR

#define PWR_01C_CoreCount_OFFSET                               0
#define PWR_01C_CoreCount_WIDTH                                4
#define PWR_01C_CoreCount_MASK                                 0xf
#define PWR_01C_ComplexCount_OFFSET                            4
#define PWR_01C_ComplexCount_WIDTH                             4
#define PWR_01C_ComplexCount_MASK                              0xf0
#define PWR_01C_SMTMode_OFFSET                                 8
#define PWR_01C_SMTMode_WIDTH                                  1
#define PWR_01C_SMTMode_MASK                                   0x100
#define PWR_01C_SMTDisable_OFFSET                              9
#define PWR_01C_SMTDisable_WIDTH                               1
#define PWR_01C_SMTDisable_MASK                                0x200

/// PWR_01C
typedef union {
  struct {
    UINT32                                               CoreCount:4 ; ///<
    UINT32                                            ComplexCount:4 ; ///<
    UINT32                                                 SMTMode:1 ; ///<
    UINT32                                              SMTDisable:1 ; ///<
    UINT32                                               Reserved1:22; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PWR_01C_STRUCT;

// Address
#define PWR_060_ADDRESS                                        0x5a860

// Register Name RSMU_PWRMGT_INTR_STATUS_PWR

// Address
#define RSMU_PWRMGT_INTR_STATUS_PWR_ADDRESS                          0x100A170

// Type
#define RSMU_PWRMGT_INTR_STATUS_PWR_TYPE                             TYPE_SMN

#define RSMU_PWRMGT_INTR_STATUS_PWR_RSMU_PWRMGT_INTR_STATUS_OFFSET   0
#define RSMU_PWRMGT_INTR_STATUS_PWR_RSMU_PWRMGT_INTR_STATUS_WIDTH    16
#define RSMU_PWRMGT_INTR_STATUS_PWR_RSMU_PWRMGT_INTR_STATUS_MASK     0xffff
#define RSMU_PWRMGT_INTR_STATUS_PWR_Reserved_31_16_OFFSET            16
#define RSMU_PWRMGT_INTR_STATUS_PWR_Reserved_31_16_WIDTH             16
#define RSMU_PWRMGT_INTR_STATUS_PWR_Reserved_31_16_MASK              0xffff0000L

/// RSMUPWRMMIO_00000170
typedef union {
  struct {
    UINT32                                 RSMU_PWRMGT_INTR_STATUS:16; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RSMU_PWRMGT_INTR_STATUS_PWR_STRUCT;

// Address
#define NTBPCIE_LOCATION_ADDRESS                               0x440000c

// Type
#define NTBPCIE_LOCATION_TYPE                                  TYPE_SDPMUX

#define NTBPCIE_LOCATION_Port_OFFSET                           0
#define NTBPCIE_LOCATION_Port_WIDTH                            16
#define NTBPCIE_LOCATION_Port_MASK                             0xffff
#define NTBPCIE_LOCATION_Core_OFFSET                           16
#define NTBPCIE_LOCATION_Core_WIDTH                            16
#define NTBPCIE_LOCATION_Core_MASK                             0xffff0000L

/// SDPMUX_0000000C
typedef union {
  struct {
    UINT32                                                    Port:16; ///<
    UINT32                                                    Core:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NTBPCIE_LOCATION_STRUCT;

// Address
#define NTBPCIE_UNITID_ADDRESS                                 0x4400010

// Type
#define NTBPCIE_UNITID_TYPE                                    TYPE_SDPMUX

#define NTBPCIE_UnitID_OFFSET                                  0
#define NTBPCIE_UnitID_WIDTH                                   7
#define NTBPCIE_UnitID_MASK                                    0x7f

/// SDPMUX_00000010
typedef union {
  struct {
    UINT32                                                  UnitID:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NTBPCIE_UNITID_STRUCT;



// Register Name RCC_BIF_STRAP0

// Address
#define RCC_NBIF0_STRAP0_ADDRESS                                   0x10131400
#define RCC_NBIF1_STRAP0_ADDRESS                                   0x10231400
#define RCC_NBIF2_STRAP0_ADDRESS                                   0x10331400

// Type
#define RCC_BIF_STRAP0_TYPE                                        TYPE_SMN

#define RCC_BIF_STRAP0_GEN3_EN_PIN_OFFSET                          0
#define RCC_BIF_STRAP0_GEN3_EN_PIN_WIDTH                           1
#define RCC_BIF_STRAP0_GEN3_EN_PIN_MASK                            0x1
#define RCC_BIF_STRAP0_CLK_PM_EN_PIN_OFFSET                        1
#define RCC_BIF_STRAP0_CLK_PM_EN_PIN_WIDTH                         1
#define RCC_BIF_STRAP0_CLK_PM_EN_PIN_MASK                          0x2
#define RCC_BIF_STRAP0_VGA_DIS_PIN_OFFSET                          2
#define RCC_BIF_STRAP0_VGA_DIS_PIN_WIDTH                           1
#define RCC_BIF_STRAP0_VGA_DIS_PIN_MASK                            0x4
#define RCC_BIF_STRAP0_MEM_AP_SIZE_PIN_OFFSET                      3
#define RCC_BIF_STRAP0_MEM_AP_SIZE_PIN_WIDTH                       3
#define RCC_BIF_STRAP0_MEM_AP_SIZE_PIN_MASK                        0x38
#define RCC_BIF_STRAP0_BIOS_ROM_EN_PIN_OFFSET                      6
#define RCC_BIF_STRAP0_BIOS_ROM_EN_PIN_WIDTH                       1
#define RCC_BIF_STRAP0_BIOS_ROM_EN_PIN_MASK                        0x40
#define RCC_BIF_STRAP0_PX_CAPABLE_OFFSET                           7
#define RCC_BIF_STRAP0_PX_CAPABLE_WIDTH                            1
#define RCC_BIF_STRAP0_PX_CAPABLE_MASK                             0x80
#define RCC_BIF_STRAP0_BIF_KILL_GEN3_OFFSET                        8
#define RCC_BIF_STRAP0_BIF_KILL_GEN3_WIDTH                         1
#define RCC_BIF_STRAP0_BIF_KILL_GEN3_MASK                          0x100
#define RCC_BIF_STRAP0_MSI_FIRST_BE_FULL_PAYLOAD_EN_OFFSET         9
#define RCC_BIF_STRAP0_MSI_FIRST_BE_FULL_PAYLOAD_EN_WIDTH          1
#define RCC_BIF_STRAP0_MSI_FIRST_BE_FULL_PAYLOAD_EN_MASK           0x200
#define RCC_BIF_STRAP0_NBIF_IGNORE_ERR_INFLR_OFFSET                10
#define RCC_BIF_STRAP0_NBIF_IGNORE_ERR_INFLR_WIDTH                 1
#define RCC_BIF_STRAP0_NBIF_IGNORE_ERR_INFLR_MASK                  0x400
#define RCC_BIF_STRAP0_PME_SUPPORT_COMPLIANCE_EN_OFFSET            11
#define RCC_BIF_STRAP0_PME_SUPPORT_COMPLIANCE_EN_WIDTH             1
#define RCC_BIF_STRAP0_PME_SUPPORT_COMPLIANCE_EN_MASK              0x800
#define RCC_BIF_STRAP0_RX_IGNORE_EP_ERR_OFFSET                     12
#define RCC_BIF_STRAP0_RX_IGNORE_EP_ERR_WIDTH                      1
#define RCC_BIF_STRAP0_RX_IGNORE_EP_ERR_MASK                       0x1000
#define RCC_BIF_STRAP0_RX_IGNORE_MSG_ERR_OFFSET                    13
#define RCC_BIF_STRAP0_RX_IGNORE_MSG_ERR_WIDTH                     1
#define RCC_BIF_STRAP0_RX_IGNORE_MSG_ERR_MASK                      0x2000
#define RCC_BIF_STRAP0_RX_IGNORE_MAX_PAYLOAD_ERR_OFFSET            14
#define RCC_BIF_STRAP0_RX_IGNORE_MAX_PAYLOAD_ERR_WIDTH             1
#define RCC_BIF_STRAP0_RX_IGNORE_MAX_PAYLOAD_ERR_MASK              0x4000
#define RCC_BIF_STRAP0_RX_IGNORE_SHORTPREFIX_ERR_DN_OFFSET         15
#define RCC_BIF_STRAP0_RX_IGNORE_SHORTPREFIX_ERR_DN_WIDTH          1
#define RCC_BIF_STRAP0_RX_IGNORE_SHORTPREFIX_ERR_DN_MASK           0x8000
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_OFFSET                     16
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_WIDTH                      1
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_MASK                       0x10000
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_DN_OFFSET                  17
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_DN_WIDTH                   1
#define RCC_BIF_STRAP0_RX_IGNORE_TC_ERR_DN_MASK                    0x20000
#define RCC_BIF_STRAP0_DN_DEVNUM_OFFSET                            18
#define RCC_BIF_STRAP0_DN_DEVNUM_WIDTH                             5
#define RCC_BIF_STRAP0_DN_DEVNUM_MASK                              0x7c0000
#define RCC_BIF_STRAP0_DN_FUNCID_OFFSET                            23
#define RCC_BIF_STRAP0_DN_FUNCID_WIDTH                             3
#define RCC_BIF_STRAP0_DN_FUNCID_MASK                              0x3800000
#define RCC_BIF_STRAP0_QUICKSIM_START_OFFSET                       26
#define RCC_BIF_STRAP0_QUICKSIM_START_WIDTH                        1
#define RCC_BIF_STRAP0_QUICKSIM_START_MASK                         0x4000000
#define RCC_BIF_STRAP0_NO_RO_ENABLED_P2P_PASSING_OFFSET            27
#define RCC_BIF_STRAP0_NO_RO_ENABLED_P2P_PASSING_WIDTH             1
#define RCC_BIF_STRAP0_NO_RO_ENABLED_P2P_PASSING_MASK              0x8000000
#define RCC_BIF_STRAP0_GPUIOV_SEC_LVL_OVRD_EN_OFFSET               28
#define RCC_BIF_STRAP0_GPUIOV_SEC_LVL_OVRD_EN_WIDTH                1
#define RCC_BIF_STRAP0_GPUIOV_SEC_LVL_OVRD_EN_MASK                 0x10000000
#define RCC_BIF_STRAP0_CFG0_RD_VF_BUSNUM_CHK_EN_OFFSET             29
#define RCC_BIF_STRAP0_CFG0_RD_VF_BUSNUM_CHK_EN_WIDTH              1
#define RCC_BIF_STRAP0_CFG0_RD_VF_BUSNUM_CHK_EN_MASK               0x20000000
#define RCC_BIF_STRAP0_BIGAPU_MODE_OFFSET                          30
#define RCC_BIF_STRAP0_BIGAPU_MODE_WIDTH                           1
#define RCC_BIF_STRAP0_BIGAPU_MODE_MASK                            0x40000000
#define RCC_BIF_STRAP0_LINK_DOWN_RESET_EN_OFFSET                   31
#define RCC_BIF_STRAP0_LINK_DOWN_RESET_EN_WIDTH                    1
#define RCC_BIF_STRAP0_LINK_DOWN_RESET_EN_MASK                     0x80000000L

/// RCC_BIF_STRAP0
typedef union {
  struct {
    UINT32                                       STRAP_GEN3_EN_PIN:1 ; ///<
    UINT32                                     STRAP_CLK_PM_EN_PIN:1 ; ///<
    UINT32                                       STRAP_VGA_DIS_PIN:1 ; ///<
    UINT32                                   STRAP_MEM_AP_SIZE_PIN:3 ; ///<
    UINT32                                   STRAP_BIOS_ROM_EN_PIN:1 ; ///<
    UINT32                                        STRAP_PX_CAPABLE:1 ; ///<
    UINT32                                     STRAP_BIF_KILL_GEN3:1 ; ///<
    UINT32                      STRAP_MSI_FIRST_BE_FULL_PAYLOAD_EN:1 ; ///<
    UINT32                             STRAP_NBIF_IGNORE_ERR_INFLR:1 ; ///<
    UINT32                         STRAP_PME_SUPPORT_COMPLIANCE_EN:1 ; ///<
    UINT32                                  STRAP_RX_IGNORE_EP_ERR:1 ; ///<
    UINT32                                 STRAP_RX_IGNORE_MSG_ERR:1 ; ///<
    UINT32                         STRAP_RX_IGNORE_MAX_PAYLOAD_ERR:1 ; ///<
    UINT32                      STRAP_RX_IGNORE_SHORTPREFIX_ERR_DN:1 ; ///<
    UINT32                                  STRAP_RX_IGNORE_TC_ERR:1 ; ///<
    UINT32                               STRAP_RX_IGNORE_TC_ERR_DN:1 ; ///<
    UINT32                                         STRAP_DN_DEVNUM:5 ; ///<
    UINT32                                         STRAP_DN_FUNCID:3 ; ///<
    UINT32                                    STRAP_QUICKSIM_START:1 ; ///<
    UINT32                         STRAP_NO_RO_ENABLED_P2P_PASSING:1 ; ///<
    UINT32                            STRAP_GPUIOV_SEC_LVL_OVRD_EN:1 ; ///<
    UINT32                          STRAP_CFG0_RD_VF_BUSNUM_CHK_EN:1 ; ///<
    UINT32                                       STRAP_BIGAPU_MODE:1 ; ///<
    UINT32                                STRAP_LINK_DOWN_RESET_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_BIF_STRAP0_STRUCT;


// Register Name RCC_BIF_STRAP1

// Address
#define RCC_BIF_STRAP1_ADDRESS                                   0x10131404
#define RCC_NBIF0_STRAP1_ADDRESS                                   0x10131404
#define RCC_NBIF1_STRAP1_ADDRESS                                   0x10231404
#define RCC_NBIF2_STRAP1_ADDRESS                                   0x10331404

// Type
#define RCC_BIF_STRAP1_TYPE                                        TYPE_SMN

#define RCC_BIF_STRAP1_FUSESTRAP_VALID_OFFSET                            0
#define RCC_BIF_STRAP1_FUSESTRAP_VALID_WIDTH                             1
#define RCC_BIF_STRAP1_FUSESTRAP_VALID_MASK                            0x1
#define RCC_BIF_STRAP1_ROMSTRAP_VALID_OFFSET                             1
#define RCC_BIF_STRAP1_ROMSTRAP_VALID_WIDTH                              1
#define RCC_BIF_STRAP1_ROMSTRAP_VALID_MASK                             0x2
#define RCC_BIF_STRAP1_WRITE_DISABLE_OFFSET                              2
#define RCC_BIF_STRAP1_WRITE_DISABLE_WIDTH                               1
#define RCC_BIF_STRAP1_WRITE_DISABLE_MASK                              0x4
#define RCC_BIF_STRAP1_STRAP_ECRC_INTERMEDIATE_CHK_EN_OFFSET             3
#define RCC_BIF_STRAP1_STRAP_ECRC_INTERMEDIATE_CHK_EN_WIDTH              1
#define RCC_BIF_STRAP1_STRAP_ECRC_INTERMEDIATE_CHK_EN_MASK             0x8
#define RCC_BIF_STRAP1_STRAP_TRUE_PM_STATUS_EN_OFFSET                    4
#define RCC_BIF_STRAP1_STRAP_TRUE_PM_STATUS_EN_WIDTH                     1
#define RCC_BIF_STRAP1_STRAP_TRUE_PM_STATUS_EN_MASK                   0x10
#define RCC_BIF_STRAP1_STRAP_IGNORE_E2E_PREFIX_UR_SWUS_OFFSET            5
#define RCC_BIF_STRAP1_STRAP_IGNORE_E2E_PREFIX_UR_SWUS_WIDTH             3
#define RCC_BIF_STRAP1_STRAP_IGNORE_E2E_PREFIX_UR_SWUS_MASK           0xE0
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_EN_OFFSET                         8
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_EN_WIDTH                          1
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_EN_MASK                       0x100
#define RCC_BIF_STRAP1_STRAP_SWUS_64BAR_EN_OFFSET                        9
#define RCC_BIF_STRAP1_STRAP_SWUS_64BAR_EN_WIDTH                         1
#define RCC_BIF_STRAP1_STRAP_SWUS_64BAR_EN_MASK                      0x200
#define RCC_BIF_STRAP1_STRAP_SWUS_AP_SIZE_OFFSET                        10
#define RCC_BIF_STRAP1_STRAP_SWUS_AP_SIZE_WIDTH                          2
#define RCC_BIF_STRAP1_STRAP_SWUS_AP_SIZE_MASK                       0xC00
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_PREFETCHABLE_OFFSET              12
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_PREFETCHABLE_WIDTH                1
#define RCC_BIF_STRAP1_STRAP_SWUS_APER_PREFETCHABLE_MASK            0x1000
#define RCC_BIF_STRAP1_STRAP_HWREV_LSB2_OFFSET                          13
#define RCC_BIF_STRAP1_STRAP_HWREV_LSB2_WIDTH                            2
#define RCC_BIF_STRAP1_STRAP_HWREV_LSB2_MASK                        0x6000
#define RCC_BIF_STRAP1_STRAP_SWREV_LSB2_OFFSET                          15
#define RCC_BIF_STRAP1_STRAP_SWREV_LSB2_WIDTH                            2
#define RCC_BIF_STRAP1_STRAP_SWREV_LSB2_MASK                       0x18000
#define RCC_BIF_STRAP1_STRAP_LINK_RST_CFG_ONLY_OFFSET                   17
#define RCC_BIF_STRAP1_STRAP_LINK_RST_CFG_ONLY_WIDTH                     1
#define RCC_BIF_STRAP1_STRAP_LINK_RST_CFG_ONLY_MASK                0x20000
#define RCC_BIF_STRAP1_STRAP_BIF_IOV_LKRST_DIS_OFFSET                   18
#define RCC_BIF_STRAP1_STRAP_BIF_IOV_LKRST_DIS_WIDTH                     1
#define RCC_BIF_STRAP1_STRAP_BIF_IOV_LKRST_DIS_MASK                0x40000
#define RCC_BIF_STRAP1_STRAP_GPUIOV_SEC_LVL_OVRD_VAL_OFFSET             19
#define RCC_BIF_STRAP1_STRAP_GPUIOV_SEC_LVL_OVRD_VAL_WIDTH               3
#define RCC_BIF_STRAP1_STRAP_GPUIOV_SEC_LVL_OVRD_VAL_MASK         0x380000
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_OFFSET                   22
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_WIDTH                     1
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_MASK               0x400000
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_OFFSET          23
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_WIDTH            1
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_MASK      0x800000
#define RCC_BIF_STRAP1_STRAP_RP_BUSNUM_OFFSET                           24
#define RCC_BIF_STRAP1_STRAP_RP_BUSNUM_WIDTH                             8
#define RCC_BIF_STRAP1_STRAP_RP_BUSNUM_MASK                     0xFF000000

/// RCC_BIF_STRAP1
typedef union {
  struct {
    UINT32                                              FUSESTRAP_VALID:1 ; ///<
    UINT32                                               ROMSTRAP_VALID:1 ; ///<
    UINT32                                                WRITE_DISABLE:1 ; ///<
    UINT32                               STRAP_ECRC_INTERMEDIATE_CHK_EN:1 ; ///<
    UINT32                                      STRAP_TRUE_PM_STATUS_EN:1 ; ///<
    UINT32                              STRAP_IGNORE_E2E_PREFIX_UR_SWUS:3 ; ///<
    UINT32                                           STRAP_SWUS_APER_EN:1 ; ///<
    UINT32                                          STRAP_SWUS_64BAR_EN:1 ; ///<
    UINT32                                           STRAP_SWUS_AP_SIZE:2 ; ///<
    UINT32                                 STRAP_SWUS_APER_PREFETCHABLE:1 ; ///<
    UINT32                                             STRAP_HWREV_LSB2:2 ; ///<
    UINT32                                             STRAP_SWREV_LSB2:2 ; ///<
    UINT32                                      STRAP_LINK_RST_CFG_ONLY:1 ; ///<
    UINT32                                      STRAP_BIF_IOV_LKRST_DIS:1 ; ///<
    UINT32                                STRAP_GPUIOV_SEC_LVL_OVRD_VAL:3 ; ///<
    UINT32                                      STRAP_BIF_PSN_UR_RPT_EN:1 ; ///<
    UINT32                             STRAP_BIF_XSTCLK_SWITCH_OVERRIDE:1 ; ///<
    UINT32                                              STRAP_RP_BUSNUM:8 ; ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_BIF_STRAP1_STRUCT;


// Register Name BIFC_MISC_CTRL0_

// Address
#define NBIF0_BIFC_MISC_CTRL0_TYPE                                        0x1013A010
#define NBIF1_BIFC_MISC_CTRL0_TYPE                                        0x1023A010
#define NBIF2_BIFC_MISC_CTRL0_TYPE                                        0x1033A010

// Type
#define BIFC_MISC_CTRL0_TYPE                                              TYPE_SMN

#define BIFC_MISC_CTRL0_VWIRE_TARG_UNITID_CHECK_EN_OFFSET                 0
#define BIFC_MISC_CTRL0_VWIRE_TARG_UNITID_CHECK_EN_WIDTH                  1
#define BIFC_MISC_CTRL0_VWIRE_TARG_UNITID_CHECK_EN_MASK                   0x1
#define BIFC_MISC_CTRL0_VWIRE_SRC_UNITID_CHECK_EN_OFFSET                  1
#define BIFC_MISC_CTRL0_VWIRE_SRC_UNITID_CHECK_EN_WIDTH                   2
#define BIFC_MISC_CTRL0_VWIRE_SRC_UNITID_CHECK_EN_MASK                    0x6
#define BIFC_MISC_CTRL0_Reserved_7_3_OFFSET                               3
#define BIFC_MISC_CTRL0_Reserved_7_3_WIDTH                                5
#define BIFC_MISC_CTRL0_Reserved_7_3_MASK                                 0xf8
#define BIFC_MISC_CTRL0_DMA_CHAIN_BREAK_IN_RCMODE_OFFSET                  8
#define BIFC_MISC_CTRL0_DMA_CHAIN_BREAK_IN_RCMODE_WIDTH                   1
#define BIFC_MISC_CTRL0_DMA_CHAIN_BREAK_IN_RCMODE_MASK                    0x100
#define BIFC_MISC_CTRL0_HST_ARB_CHAIN_LOCK_OFFSET                         9
#define BIFC_MISC_CTRL0_HST_ARB_CHAIN_LOCK_WIDTH                          1
#define BIFC_MISC_CTRL0_HST_ARB_CHAIN_LOCK_MASK                           0x200
#define BIFC_MISC_CTRL0_GSI_SST_ARB_CHAIN_LOCK_OFFSET                     10
#define BIFC_MISC_CTRL0_GSI_SST_ARB_CHAIN_LOCK_WIDTH                      1
#define BIFC_MISC_CTRL0_GSI_SST_ARB_CHAIN_LOCK_MASK                       0x400
#define BIFC_MISC_CTRL0_Reserved_15_11_OFFSET                             11
#define BIFC_MISC_CTRL0_Reserved_15_11_WIDTH                              5
#define BIFC_MISC_CTRL0_Reserved_15_11_MASK                               0xf800
#define BIFC_MISC_CTRL0_DMA_ATOMIC_LENGTH_CHK_DIS_OFFSET                  16
#define BIFC_MISC_CTRL0_DMA_ATOMIC_LENGTH_CHK_DIS_WIDTH                   1
#define BIFC_MISC_CTRL0_DMA_ATOMIC_LENGTH_CHK_DIS_MASK                    0x10000
#define BIFC_MISC_CTRL0_DMA_ATOMIC_FAILED_STS_SEL_OFFSET                  17
#define BIFC_MISC_CTRL0_DMA_ATOMIC_FAILED_STS_SEL_WIDTH                   1
#define BIFC_MISC_CTRL0_DMA_ATOMIC_FAILED_STS_SEL_MASK                    0x20000
#define BIFC_MISC_CTRL0_Reserved_23_18_OFFSET                             18
#define BIFC_MISC_CTRL0_Reserved_23_18_WIDTH                              6
#define BIFC_MISC_CTRL0_Reserved_23_18_MASK                               0xfc0000
#define BIFC_MISC_CTRL0_PCIE_CAPABILITY_PROT_DIS_OFFSET                   24
#define BIFC_MISC_CTRL0_PCIE_CAPABILITY_PROT_DIS_WIDTH                    1
#define BIFC_MISC_CTRL0_PCIE_CAPABILITY_PROT_DIS_MASK                     0x1000000
#define BIFC_MISC_CTRL0_VC7_DMA_IOCFG_DIS_OFFSET                          25
#define BIFC_MISC_CTRL0_VC7_DMA_IOCFG_DIS_WIDTH                           1
#define BIFC_MISC_CTRL0_VC7_DMA_IOCFG_DIS_MASK                            0x2000000
#define BIFC_MISC_CTRL0_DMA_2ND_REQ_DIS_OFFSET                            26
#define BIFC_MISC_CTRL0_DMA_2ND_REQ_DIS_WIDTH                             1
#define BIFC_MISC_CTRL0_DMA_2ND_REQ_DIS_MASK                              0x4000000
#define BIFC_MISC_CTRL0_PORT_DSTATE_BYPASS_MODE_OFFSET                    27
#define BIFC_MISC_CTRL0_PORT_DSTATE_BYPASS_MODE_WIDTH                     1
#define BIFC_MISC_CTRL0_PORT_DSTATE_BYPASS_MODE_MASK                      0x8000000
#define BIFC_MISC_CTRL0_Reserved_30_28_OFFSET                             28
#define BIFC_MISC_CTRL0_Reserved_30_28_WIDTH                              3
#define BIFC_MISC_CTRL0_Reserved_30_28_MASK                               0x70000000
#define BIFC_MISC_CTRL0_PCIESWUS_SELECTION_OFFSET                         31
#define BIFC_MISC_CTRL0_PCIESWUS_SELECTION_WIDTH                          1
#define BIFC_MISC_CTRL0_PCIESWUS_SELECTION_MASK                           0x80000000L

/// NBIFMISC0_00000010
typedef union {
  struct {
    UINT32                              VWIRE_TARG_UNITID_CHECK_EN:1 ; ///<
    UINT32                               VWIRE_SRC_UNITID_CHECK_EN:2 ; ///<
    UINT32                                            Reserved_7_3:5 ; ///<
    UINT32                               DMA_CHAIN_BREAK_IN_RCMODE:1 ; ///<
    UINT32                                      HST_ARB_CHAIN_LOCK:1 ; ///<
    UINT32                                  GSI_SST_ARB_CHAIN_LOCK:1 ; ///<
    UINT32                                          Reserved_15_11:5 ; ///<
    UINT32                               DMA_ATOMIC_LENGTH_CHK_DIS:1 ; ///<
    UINT32                               DMA_ATOMIC_FAILED_STS_SEL:1 ; ///<
    UINT32                                          Reserved_23_18:6 ; ///<
    UINT32                                PCIE_CAPABILITY_PROT_DIS:1 ; ///<
    UINT32                                       VC7_DMA_IOCFG_DIS:1 ; ///<
    UINT32                                         DMA_2ND_REQ_DIS:1 ; ///<
    UINT32                                 PORT_DSTATE_BYPASS_MODE:1 ; ///<
    UINT32                                          Reserved_30_28:3 ; ///<
    UINT32                                      PCIESWUS_SELECTION:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} BIFC_MISC_CTRL0_STRUCT;


// Address
#define NBIF0_LINK_CNTL2_ADDRESS                               0x10140094
#define NBIF1_LINK_CNTL2_ADDRESS                               0x10240094
#define NBIF2_LINK_CNTL2_ADDRESS                               0x10340094

// Type
#define NBIF_LINK_CNTL2_TYPE                                   TYPE_SMN

#define NBIF_LINK_CNTL2_TARGET_LINK_SPEED_OFFSET               0
#define NBIF_LINK_CNTL2_TARGET_LINK_SPEED_WIDTH                4
#define NBIF_LINK_CNTL2_TARGET_LINK_SPEED_MASK                 0xf
#define NBIF_LINK_CNTL2_ENTER_COMPLIANCE_OFFSET                4
#define NBIF_LINK_CNTL2_ENTER_COMPLIANCE_WIDTH                 1
#define NBIF_LINK_CNTL2_ENTER_COMPLIANCE_MASK                  0x10
#define NBIF_LINK_CNTL2_HW_AUTONOMOUS_SPEED_DISABLE_OFFSET     5
#define NBIF_LINK_CNTL2_HW_AUTONOMOUS_SPEED_DISABLE_WIDTH      1
#define NBIF_LINK_CNTL2_HW_AUTONOMOUS_SPEED_DISABLE_MASK       0x20
#define NBIF_LINK_CNTL2_SELECTABLE_DEEMPHASIS_OFFSET           6
#define NBIF_LINK_CNTL2_SELECTABLE_DEEMPHASIS_WIDTH            1
#define NBIF_LINK_CNTL2_SELECTABLE_DEEMPHASIS_MASK             0x40
#define NBIF_LINK_CNTL2_XMIT_MARGIN_OFFSET                     7
#define NBIF_LINK_CNTL2_XMIT_MARGIN_WIDTH                      3
#define NBIF_LINK_CNTL2_XMIT_MARGIN_MASK                       0x380
#define NBIF_LINK_CNTL2_ENTER_MOD_COMPLIANCE_OFFSET            10
#define NBIF_LINK_CNTL2_ENTER_MOD_COMPLIANCE_WIDTH             1
#define NBIF_LINK_CNTL2_ENTER_MOD_COMPLIANCE_MASK              0x400
#define NBIF_LINK_CNTL2_COMPLIANCE_SOS_OFFSET                  11
#define NBIF_LINK_CNTL2_COMPLIANCE_SOS_WIDTH                   1
#define NBIF_LINK_CNTL2_COMPLIANCE_SOS_MASK                    0x800
#define NBIF_LINK_CNTL2_COMPLIANCE_DEEMPHASIS_OFFSET           12
#define NBIF_LINK_CNTL2_COMPLIANCE_DEEMPHASIS_WIDTH            4
#define NBIF_LINK_CNTL2_COMPLIANCE_DEEMPHASIS_MASK             0xf000

/// NBIF_LINK_CNTL2
typedef union {
  struct {
    UINT32                                       TARGET_LINK_SPEED:4 ; ///<
    UINT32                                        ENTER_COMPLIANCE:1 ; ///<
    UINT32                             HW_AUTONOMOUS_SPEED_DISABLE:1 ; ///<
    UINT32                                   SELECTABLE_DEEMPHASIS:1 ; ///<
    UINT32                                             XMIT_MARGIN:3 ; ///<
    UINT32                                    ENTER_MOD_COMPLIANCE:1 ; ///<
    UINT32                                          COMPLIANCE_SOS:1 ; ///<
    UINT32                                   COMPLIANCE_DEEMPHASIS:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIF_LINK_CNTL2_STRUCT;


#define PCIE0_SLOT_APERTURE                                    0x11100000
#define PCIE1_SLOT_APERTURE                                    0x11200000


#define GPP0_LINK_CTL_STS_ADDRESS                              0x11100068
#define GPP1_LINK_CTL_STS_ADDRESS                              0x11200068

#define LINK_CTL_STS_DL_ACTIVE_OFFSET                          29

// Address
#define SLOT_CAP_ADDRESS                                       0x6C
#define GPP0_SLOT_CAP_ADDRESS                                  0x1110006C
#define GPP1_SLOT_CAP_ADDRESS                                  0x1110106C
#define GPP2_SLOT_CAP_ADDRESS                                  0x1110206C
#define GPP3_SLOT_CAP_ADDRESS                                  0x1110306C
#define GPP4_SLOT_CAP_ADDRESS                                  0x1110406C
#define GPP5_SLOT_CAP_ADDRESS                                  0x1110506C
#define GPP6_SLOT_CAP_ADDRESS                                  0x1110606C
#define GPP7_SLOT_CAP_ADDRESS                                  0x1110706C
#define GFX0_SLOT_CAP_ADDRESS                                  0x1120006C
#define GFX1_SLOT_CAP_ADDRESS                                  0x1120106C
#define GFX2_SLOT_CAP_ADDRESS                                  0x1120206C
#define GFX3_SLOT_CAP_ADDRESS                                  0x1120306C
#define GFX4_SLOT_CAP_ADDRESS                                  0x1120406C
#define GFX5_SLOT_CAP_ADDRESS                                  0x1120506C
#define GFX6_SLOT_CAP_ADDRESS                                  0x1120606C
#define GFX7_SLOT_CAP_ADDRESS                                  0x1120706C

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

/// SLOT_CAP
typedef union {
  struct {
    UINT32                                     ATTN_BUTTON_PRESENT:1 ; ///<
    UINT32                                  PWR_CONTROLLER_PRESENT:1 ; ///<
    UINT32                                      MRL_SENSOR_PRESENT:1 ; ///<
    UINT32                                  ATTN_INDICATOR_PRESENT:1 ; ///<
    UINT32                                   PWR_INDICATOR_PRESENT:1 ; ///<
    UINT32                                        HOTPLUG_SURPRISE:1 ; ///<
    UINT32                                         HOTPLUG_CAPABLE:1 ; ///<
    UINT32                                    SLOT_PWR_LIMIT_VALUE:8 ; ///<
    UINT32                                    SLOT_PWR_LIMIT_SCALE:2 ; ///<
    UINT32                           ELECTROMECH_INTERLOCK_PRESENT:1 ; ///<
    UINT32                          NO_COMMAND_COMPLETED_SUPPORTED:1 ; ///<
    UINT32                                       PHYSICAL_SLOT_NUM:13; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SLOT_CAP_STRUCT;

// SLOT_CNTL and SLOT_STATUS
// Address
#define SLOT_CNTL_ADDRESS                                      0x70
#define GPP0_SLOT_CNTL_ADDRESS                                 0x11100070
#define GPP1_SLOT_CNTL_ADDRESS                                 0x11101070
#define GPP2_SLOT_CNTL_ADDRESS                                 0x11102070
#define GPP3_SLOT_CNTL_ADDRESS                                 0x11103070
#define GPP4_SLOT_CNTL_ADDRESS                                 0x11104070
#define GPP5_SLOT_CNTL_ADDRESS                                 0x11105070
#define GPP6_SLOT_CNTL_ADDRESS                                 0x11106070
#define GPP7_SLOT_CNTL_ADDRESS                                 0x11107070
#define GFX0_SLOT_CNTL_ADDRESS                                 0x11200070
#define GFX1_SLOT_CNTL_ADDRESS                                 0x11201070
#define GFX2_SLOT_CNTL_ADDRESS                                 0x11202070
#define GFX3_SLOT_CNTL_ADDRESS                                 0x11203070
#define GFX4_SLOT_CNTL_ADDRESS                                 0x11204070
#define GFX5_SLOT_CNTL_ADDRESS                                 0x11205070
#define GFX6_SLOT_CNTL_ADDRESS                                 0x11206070
#define GFX7_SLOT_CNTL_ADDRESS                                 0x11207070

// DEVICE_CNTL2
#define DEVICE_CNTL2_ADDRESS                                   0x80
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_OFFSET                  0
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_WIDTH                   4
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_MASK                    0xF

// Type
#define SLOT_CNTL_TYPE                                         TYPE_SMN

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
//Reserved 7

/// SLOT_CNTL_STAT
typedef union {
  struct {
    UINT32                                  ATTN_BUTTON_PRESSED_EN:1 ; ///<
    UINT32                                   PWR_FAULT_DETECTED_EN:1 ; ///<
    UINT32                                   MRL_SENSOR_CHANGED_EN:1 ; ///<
    UINT32                              PRESENCE_DETECT_CHANGED_EN:1 ; ///<
    UINT32                               COMMAND_COMPLETED_INTR_EN:1 ; ///<
    UINT32                                         HOTPLUG_INTR_EN:1 ; ///<
    UINT32                                     ATTN_INDICATOR_CNTL:2 ; ///<
    UINT32                                      PWR_INDICATOR_CNTL:2 ; ///<
    UINT32                                     PWR_CONTROLLER_CNTL:1 ; ///<
    UINT32                              ELECTROMECH_INTERLOCK_CNTL:1 ; ///<
    UINT32                                     DL_STATE_CHANGED_EN:1 ; ///<
    UINT32                                               Reserved3:3 ; ///<
    UINT32                                     ATTN_BUTTON_PRESSED:1 ; ///<
    UINT32                                      PWR_FAULT_DETECTED:1 ; ///<
    UINT32                                      MRL_SENSOR_CHANGED:1 ; ///<
    UINT32                                 PRESENCE_DETECT_CHANGED:1 ; ///<
    UINT32                                       COMMAND_COMPLETED:1 ; ///<
    UINT32                                        MRL_SENSOR_STATE:1 ; ///<
    UINT32                                   PRESENCE_DETECT_STATE:1 ; ///<
    UINT32                            ELECTROMECH_INTERLOCK_STATUS:1 ; ///<
    UINT32                                        DL_STATE_CHANGED:1 ; ///<
    UINT32                                               Reserved7:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SLOT_CNTL_STRUCT;

// Register Name PCIE_STRAP_F0

// Address
#define PCIE0_STRAP_F0_ADDRESS                                          0x111802c0
#define PCIE1_STRAP_F0_ADDRESS                                          0x112802c0

// Type
#define PCIE_STRAP_F0_TYPE                                              TYPE_SMN

#define PCIE_STRAP_F0_STRAP_F0_EN_OFFSET                                0
#define PCIE_STRAP_F0_STRAP_F0_EN_WIDTH                                 1
#define PCIE_STRAP_F0_STRAP_F0_EN_MASK                                  0x1
#define PCIE_STRAP_F0_STRAP_F0_LEGACY_DEVICE_TYPE_EN_OFFSET             1
#define PCIE_STRAP_F0_STRAP_F0_LEGACY_DEVICE_TYPE_EN_WIDTH              1
#define PCIE_STRAP_F0_STRAP_F0_LEGACY_DEVICE_TYPE_EN_MASK               0x2
#define PCIE_STRAP_F0_STRAP_F0_MSI_EN_OFFSET                            2
#define PCIE_STRAP_F0_STRAP_F0_MSI_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_MSI_EN_MASK                              0x4
#define PCIE_STRAP_F0_STRAP_F0_VC_EN_OFFSET                             3
#define PCIE_STRAP_F0_STRAP_F0_VC_EN_WIDTH                              1
#define PCIE_STRAP_F0_STRAP_F0_VC_EN_MASK                               0x8
#define PCIE_STRAP_F0_STRAP_F0_DSN_EN_OFFSET                            4
#define PCIE_STRAP_F0_STRAP_F0_DSN_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_DSN_EN_MASK                              0x10
#define PCIE_STRAP_F0_STRAP_F0_AER_EN_OFFSET                            5
#define PCIE_STRAP_F0_STRAP_F0_AER_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_AER_EN_MASK                              0x20
#define PCIE_STRAP_F0_STRAP_F0_ACS_EN_OFFSET                            6
#define PCIE_STRAP_F0_STRAP_F0_ACS_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_ACS_EN_MASK                              0x40
#define PCIE_STRAP_F0_STRAP_F0_BAR_EN_OFFSET                            7
#define PCIE_STRAP_F0_STRAP_F0_BAR_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_BAR_EN_MASK                              0x80
#define PCIE_STRAP_F0_STRAP_F0_PWR_EN_OFFSET                            8
#define PCIE_STRAP_F0_STRAP_F0_PWR_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_PWR_EN_MASK                              0x100
#define PCIE_STRAP_F0_STRAP_F0_DPA_EN_OFFSET                            9
#define PCIE_STRAP_F0_STRAP_F0_DPA_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_DPA_EN_MASK                              0x200
#define PCIE_STRAP_F0_STRAP_F0_ATS_EN_OFFSET                            10
#define PCIE_STRAP_F0_STRAP_F0_ATS_EN_WIDTH                             1
#define PCIE_STRAP_F0_STRAP_F0_ATS_EN_MASK                              0x400
#define PCIE_STRAP_F0_STRAP_F0_PAGE_REQ_EN_OFFSET                       11
#define PCIE_STRAP_F0_STRAP_F0_PAGE_REQ_EN_WIDTH                        1
#define PCIE_STRAP_F0_STRAP_F0_PAGE_REQ_EN_MASK                         0x800
#define PCIE_STRAP_F0_STRAP_F0_PASID_EN_OFFSET                          12
#define PCIE_STRAP_F0_STRAP_F0_PASID_EN_WIDTH                           1
#define PCIE_STRAP_F0_STRAP_F0_PASID_EN_MASK                            0x1000
#define PCIE_STRAP_F0_STRAP_F0_ECRC_CHECK_EN_OFFSET                     13
#define PCIE_STRAP_F0_STRAP_F0_ECRC_CHECK_EN_WIDTH                      1
#define PCIE_STRAP_F0_STRAP_F0_ECRC_CHECK_EN_MASK                       0x2000
#define PCIE_STRAP_F0_STRAP_F0_ECRC_GEN_EN_OFFSET                       14
#define PCIE_STRAP_F0_STRAP_F0_ECRC_GEN_EN_WIDTH                        1
#define PCIE_STRAP_F0_STRAP_F0_ECRC_GEN_EN_MASK                         0x4000
#define PCIE_STRAP_F0_STRAP_F0_CPL_ABORT_ERR_EN_OFFSET                  15
#define PCIE_STRAP_F0_STRAP_F0_CPL_ABORT_ERR_EN_WIDTH                   1
#define PCIE_STRAP_F0_STRAP_F0_CPL_ABORT_ERR_EN_MASK                    0x8000
#define PCIE_STRAP_F0_STRAP_F0_POISONED_ADVISORY_NONFATAL_OFFSET        16
#define PCIE_STRAP_F0_STRAP_F0_POISONED_ADVISORY_NONFATAL_WIDTH         1
#define PCIE_STRAP_F0_STRAP_F0_POISONED_ADVISORY_NONFATAL_MASK          0x10000
#define PCIE_STRAP_F0_STRAP_F0_MC_EN_OFFSET                             17
#define PCIE_STRAP_F0_STRAP_F0_MC_EN_WIDTH                              1
#define PCIE_STRAP_F0_STRAP_F0_MC_EN_MASK                               0x20000
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_EN_OFFSET                         18
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_EN_WIDTH                          1
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_EN_MASK                           0x40000
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_64BIT_EN_OFFSET                   19
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_64BIT_EN_WIDTH                    1
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_64BIT_EN_MASK                     0x80000
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_ROUTING_EN_OFFSET                 20
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_ROUTING_EN_WIDTH                  1
#define PCIE_STRAP_F0_STRAP_F0_ATOMIC_ROUTING_EN_MASK                   0x100000
#define PCIE_STRAP_F0_STRAP_F0_MSI_MULTI_CAP_OFFSET                     21
#define PCIE_STRAP_F0_STRAP_F0_MSI_MULTI_CAP_WIDTH                      3
#define PCIE_STRAP_F0_STRAP_F0_MSI_MULTI_CAP_MASK                       0xe00000
#define PCIE_STRAP_F0_STRAP_F0_VFn_MSI_MULTI_CAP_OFFSET                 24
#define PCIE_STRAP_F0_STRAP_F0_VFn_MSI_MULTI_CAP_WIDTH                  3
#define PCIE_STRAP_F0_STRAP_F0_VFn_MSI_MULTI_CAP_MASK                   0x7000000
#define PCIE_STRAP_F0_STRAP_F0_MSI_PERVECTOR_MASK_CAP_OFFSET            27
#define PCIE_STRAP_F0_STRAP_F0_MSI_PERVECTOR_MASK_CAP_WIDTH             1
#define PCIE_STRAP_F0_STRAP_F0_MSI_PERVECTOR_MASK_CAP_MASK              0x8000000
#define PCIE_STRAP_F0_STRAP_F0_NO_RO_ENABLED_P2P_PASSING_OFFSET         28
#define PCIE_STRAP_F0_STRAP_F0_NO_RO_ENABLED_P2P_PASSING_WIDTH          1
#define PCIE_STRAP_F0_STRAP_F0_NO_RO_ENABLED_P2P_PASSING_MASK           0x10000000
#define PCIE_STRAP_F0_STRAP_SWUS_ARI_EN_OFFSET                          29
#define PCIE_STRAP_F0_STRAP_SWUS_ARI_EN_WIDTH                           1
#define PCIE_STRAP_F0_STRAP_SWUS_ARI_EN_MASK                            0x20000000
#define PCIE_STRAP_F0_STRAP_F0_SRIOV_EN_OFFSET                          30
#define PCIE_STRAP_F0_STRAP_F0_SRIOV_EN_WIDTH                           1
#define PCIE_STRAP_F0_STRAP_F0_SRIOV_EN_MASK                            0x40000000
#define PCIE_STRAP_F0_STRAP_F0_MSI_MAP_EN_OFFSET                        31
#define PCIE_STRAP_F0_STRAP_F0_MSI_MAP_EN_WIDTH                         1
#define PCIE_STRAP_F0_STRAP_F0_MSI_MAP_EN_MASK                          0x80000000L

/// PCIE_STRAP_F0
typedef union {
  struct {
    UINT32                                             STRAP_F0_EN:1 ; ///<
    UINT32                          STRAP_F0_LEGACY_DEVICE_TYPE_EN:1 ; ///<
    UINT32                                         STRAP_F0_MSI_EN:1 ; ///<
    UINT32                                          STRAP_F0_VC_EN:1 ; ///<
    UINT32                                         STRAP_F0_DSN_EN:1 ; ///<
    UINT32                                         STRAP_F0_AER_EN:1 ; ///<
    UINT32                                         STRAP_F0_ACS_EN:1 ; ///<
    UINT32                                         STRAP_F0_BAR_EN:1 ; ///<
    UINT32                                         STRAP_F0_PWR_EN:1 ; ///<
    UINT32                                         STRAP_F0_DPA_EN:1 ; ///<
    UINT32                                         STRAP_F0_ATS_EN:1 ; ///<
    UINT32                                    STRAP_F0_PAGE_REQ_EN:1 ; ///<
    UINT32                                       STRAP_F0_PASID_EN:1 ; ///<
    UINT32                                  STRAP_F0_ECRC_CHECK_EN:1 ; ///<
    UINT32                                    STRAP_F0_ECRC_GEN_EN:1 ; ///<
    UINT32                               STRAP_F0_CPL_ABORT_ERR_EN:1 ; ///<
    UINT32                     STRAP_F0_POISONED_ADVISORY_NONFATAL:1 ; ///<
    UINT32                                          STRAP_F0_MC_EN:1 ; ///<
    UINT32                                      STRAP_F0_ATOMIC_EN:1 ; ///<
    UINT32                                STRAP_F0_ATOMIC_64BIT_EN:1 ; ///<
    UINT32                              STRAP_F0_ATOMIC_ROUTING_EN:1 ; ///<
    UINT32                                  STRAP_F0_MSI_MULTI_CAP:3 ; ///<
    UINT32                              STRAP_F0_VFn_MSI_MULTI_CAP:3 ; ///<
    UINT32                         STRAP_F0_MSI_PERVECTOR_MASK_CAP:1 ; ///<
    UINT32                      STRAP_F0_NO_RO_ENABLED_P2P_PASSING:1 ; ///<
    UINT32                                       STRAP_SWUS_ARI_EN:1 ; ///<
    UINT32                                       STRAP_F0_SRIOV_EN:1 ; ///<
    UINT32                                     STRAP_F0_MSI_MAP_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_STRAP_F0_STRUCT;

// Register Name PCIE_L1_PM_SUB_CNTL

// Address
#define SMN_0x11100378_ADDRESS                                 0x11100378
#define SMN_0x11100378                                         0x11100378

// Type
#define SMN_0x11100378_TYPE                                    TYPE_SMN

#define SMN_0x11100378_PCI_PM_L1_2_EN_OFFSET                   0
#define SMN_0x11100378_PCI_PM_L1_2_EN_WIDTH                    1
#define SMN_0x11100378_PCI_PM_L1_2_EN_MASK                     0x1
#define SMN_0x11100378_PCI_PM_L1_1_EN_OFFSET                   1
#define SMN_0x11100378_PCI_PM_L1_1_EN_WIDTH                    1
#define SMN_0x11100378_PCI_PM_L1_1_EN_MASK                     0x2
#define SMN_0x11100378_ASPM_L1_2_EN_OFFSET                     2
#define SMN_0x11100378_ASPM_L1_2_EN_WIDTH                      1
#define SMN_0x11100378_ASPM_L1_2_EN_MASK                       0x4
#define SMN_0x11100378_ASPM_L1_1_EN_OFFSET                     3
#define SMN_0x11100378_ASPM_L1_1_EN_WIDTH                      1
#define SMN_0x11100378_ASPM_L1_1_EN_MASK                       0x8
#define SMN_0x11100378_COMMON_MODE_RESTORE_TIME_OFFSET         8
#define SMN_0x11100378_COMMON_MODE_RESTORE_TIME_WIDTH          8
#define SMN_0x11100378_COMMON_MODE_RESTORE_TIME_MASK           0xff00
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_VALUE_OFFSET         16
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_VALUE_WIDTH          10
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_VALUE_MASK           0x3ff0000
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_SCALE_OFFSET         29
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_SCALE_WIDTH          3
#define SMN_0x11100378_LTR_L1_2_THRESHOLD_SCALE_MASK           0xe0000000L

/// PCIERCCFG0F0_00000378
typedef union {
  struct {
    UINT32                                          PCI_PM_L1_2_EN:1 ; ///<
    UINT32                                          PCI_PM_L1_1_EN:1 ; ///<
    UINT32                                            ASPM_L1_2_EN:1 ; ///<
    UINT32                                            ASPM_L1_1_EN:1 ; ///<
    UINT32                                COMMON_MODE_RESTORE_TIME:8 ; ///<
    UINT32                                LTR_L1_2_THRESHOLD_VALUE:10; ///<
    UINT32                                LTR_L1_2_THRESHOLD_SCALE:3 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x11100378_STRUCT;

//    svd_group: PCS_DXIO_aliasSMN_serdes_b_container0_pcs9_pcsAperture_pcs_core0_dir_PCS_PCIEX16_GLOBAL_CONTROL0
//Group Base = 0x1230B000

// Register Name PCS_PCIEX16_GLOBAL_CONTROL0

// Address
#define SMN_0x1230b010_ADDRESS                                 0x1230b010
#define SMN_0x1230b010                                         0x1230b010

// Type
#define SMN_0x1230b010_TYPE                                    TYPE_SMN

#define SMN_0x1230b010_InitHardware_OFFSET                     0
#define SMN_0x1230b010_InitHardware_WIDTH                      1
#define SMN_0x1230b010_InitHardware_MASK                       0x1
#define SMN_0x1230b010_InitComplete_OFFSET                     1
#define SMN_0x1230b010_InitComplete_WIDTH                      1
#define SMN_0x1230b010_InitComplete_MASK                       0x2
#define SMN_0x1230b010_EIDetectorCycle_OFFSET                  2
#define SMN_0x1230b010_EIDetectorCycle_WIDTH                   1
#define SMN_0x1230b010_EIDetectorCycle_MASK                    0x4
#define SMN_0x1230b010_EIDetectorOnTime_OFFSET                 4
#define SMN_0x1230b010_EIDetectorOnTime_WIDTH                  10
#define SMN_0x1230b010_EIDetectorOnTime_MASK                   0x3ff0
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOnTime_OFFSET 14
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOnTime_WIDTH  1
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOnTime_MASK   0x4000
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOffTime_OFFSET 15
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOffTime_WIDTH  1
#define SMN_0x1230b010_VoltageDimmingEnDuringEIDetectorOffTime_MASK   0x8000
#define SMN_0x1230b010_VoltageDimmingTransitionTime_OFFSET     16
#define SMN_0x1230b010_VoltageDimmingTransitionTime_WIDTH      4
#define SMN_0x1230b010_VoltageDimmingTransitionTime_MASK       0xf0000
#define SMN_0x1230b010_EIDetectorOffTime_OFFSET                20
#define SMN_0x1230b010_EIDetectorOffTime_WIDTH                 10
#define SMN_0x1230b010_EIDetectorOffTime_MASK                  0x3ff00000

/// PCIEPCS1CORE_00000010
typedef union {
  struct {
    UINT32                                            InitHardware:1 ; ///<
    UINT32                                            InitComplete:1 ; ///<
    UINT32                                         EIDetectorCycle:1 ; ///<
    UINT32                                        EIDetectorOnTime:10; ///<
    UINT32                  VoltageDimmingEnDuringEIDetectorOnTime:1 ; ///<
    UINT32                 VoltageDimmingEnDuringEIDetectorOffTime:1 ; ///<
    UINT32                            VoltageDimmingTransitionTime:4 ; ///<
    UINT32                                       EIDetectorOffTime:10; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x1230b010_STRUCT;


//    svd_group: PCS_DXIO_aliasSMN_serdes_b_container0_pcs9_pcsAperture_pcs_core0_dir_PCS_PCIEX16_GLOBAL_CONTROL1
//Group Base = 0x1230B000

// Register Name PCS_PCIEX16_GLOBAL_CONTROL1

// Address
#define SMN_0x1230b014_ADDRESS                                 0x1230b014
#define SMN_0x1230b014                                         0x1230b014

// Type
#define SMN_0x1230b014_TYPE                                    TYPE_SMN

#define SMN_0x1230b014_DefaultPCLKFrequency_OFFSET             0
#define SMN_0x1230b014_DefaultPCLKFrequency_WIDTH              2
#define SMN_0x1230b014_DefaultPCLKFrequency_MASK               0x3
#define SMN_0x1230b014_DefaultMaximumLinkRate_OFFSET           2
#define SMN_0x1230b014_DefaultMaximumLinkRate_WIDTH            2
#define SMN_0x1230b014_DefaultMaximumLinkRate_MASK             0xc
#define SMN_0x1230b014_MasterPLL_OFFSET                        4
#define SMN_0x1230b014_MasterPLL_WIDTH                         4
#define SMN_0x1230b014_MasterPLL_MASK                          0xf0
#define SMN_0x1230b014_MasterPLLAuto_OFFSET                    8
#define SMN_0x1230b014_MasterPLLAuto_WIDTH                     1
#define SMN_0x1230b014_MasterPLLAuto_MASK                      0x100
#define SMN_0x1230b014_AllowTxActivePowerGating_OFFSET         9
#define SMN_0x1230b014_AllowTxActivePowerGating_WIDTH          1
#define SMN_0x1230b014_AllowTxActivePowerGating_MASK           0x200
#define SMN_0x1230b014_AllowRxActivePowerGating_OFFSET         10
#define SMN_0x1230b014_AllowRxActivePowerGating_WIDTH          1
#define SMN_0x1230b014_AllowRxActivePowerGating_MASK           0x400
#define SMN_0x1230b014_AllowTxInactivePowerGating_OFFSET       11
#define SMN_0x1230b014_AllowTxInactivePowerGating_WIDTH        1
#define SMN_0x1230b014_AllowTxInactivePowerGating_MASK         0x800
#define SMN_0x1230b014_AllowRxInactivePowerGating_OFFSET       12
#define SMN_0x1230b014_AllowRxInactivePowerGating_WIDTH        1
#define SMN_0x1230b014_AllowRxInactivePowerGating_MASK         0x1000
#define SMN_0x1230b014_EnableTxSSClkGating_OFFSET              13
#define SMN_0x1230b014_EnableTxSSClkGating_WIDTH               1
#define SMN_0x1230b014_EnableTxSSClkGating_MASK                0x2000
#define SMN_0x1230b014_EnableMaxPClkGating_OFFSET              14
#define SMN_0x1230b014_EnableMaxPClkGating_WIDTH               1
#define SMN_0x1230b014_EnableMaxPClkGating_MASK                0x4000
#define SMN_0x1230b014_AllowRxPS2_OFFSET                       16
#define SMN_0x1230b014_AllowRxPS2_WIDTH                        1
#define SMN_0x1230b014_AllowRxPS2_MASK                         0x10000
#define SMN_0x1230b014_AllowRxPS3_OFFSET                       17
#define SMN_0x1230b014_AllowRxPS3_WIDTH                        1
#define SMN_0x1230b014_AllowRxPS3_MASK                         0x20000
#define SMN_0x1230b014_AllowTxPS2_OFFSET                       18
#define SMN_0x1230b014_AllowTxPS2_WIDTH                        1
#define SMN_0x1230b014_AllowTxPS2_MASK                         0x40000
#define SMN_0x1230b014_AllowTxPS3_OFFSET                       19
#define SMN_0x1230b014_AllowTxPS3_WIDTH                        1
#define SMN_0x1230b014_AllowTxPS3_MASK                         0x80000
#define SMN_0x1230b014_AllowPLLShutdownRxPS2_OFFSET            21
#define SMN_0x1230b014_AllowPLLShutdownRxPS2_WIDTH             1
#define SMN_0x1230b014_AllowPLLShutdownRxPS2_MASK              0x200000
#define SMN_0x1230b014_PLLActiveAbovePS4_OFFSET                24
#define SMN_0x1230b014_PLLActiveAbovePS4_WIDTH                 1
#define SMN_0x1230b014_PLLActiveAbovePS4_MASK                  0x1000000
#define SMN_0x1230b014_PLLActiveInPS4_OFFSET                   25
#define SMN_0x1230b014_PLLActiveInPS4_WIDTH                    1
#define SMN_0x1230b014_PLLActiveInPS4_MASK                     0x2000000
#define SMN_0x1230b014_DisableRxPS4_OFFSET                     26
#define SMN_0x1230b014_DisableRxPS4_WIDTH                      1
#define SMN_0x1230b014_DisableRxPS4_MASK                       0x4000000
#define SMN_0x1230b014_DisableTxPS4_OFFSET                     27
#define SMN_0x1230b014_DisableTxPS4_WIDTH                      1
#define SMN_0x1230b014_DisableTxPS4_MASK                       0x8000000
#define SMN_0x1230b014_DisableTxPS4inRxPS3_OFFSET              28
#define SMN_0x1230b014_DisableTxPS4inRxPS3_WIDTH               1
#define SMN_0x1230b014_DisableTxPS4inRxPS3_MASK                0x10000000
#define SMN_0x1230b014_RemapSATAP6TOP5_OFFSET                  29
#define SMN_0x1230b014_RemapSATAP6TOP5_WIDTH                   1
#define SMN_0x1230b014_RemapSATAP6TOP5_MASK                    0x20000000
#define SMN_0x1230b014_FarEndAnalogLoopbackEnable_OFFSET       31
#define SMN_0x1230b014_FarEndAnalogLoopbackEnable_WIDTH        1
#define SMN_0x1230b014_FarEndAnalogLoopbackEnable_MASK         0x80000000L

/// PCIEPCS1CORE_00000014
typedef union {
  struct {
    UINT32                                    DefaultPCLKFrequency:2 ; ///<
    UINT32                                  DefaultMaximumLinkRate:2 ; ///<
    UINT32                                               MasterPLL:4 ; ///<
    UINT32                                           MasterPLLAuto:1 ; ///<
    UINT32                                AllowTxActivePowerGating:1 ; ///<
    UINT32                                AllowRxActivePowerGating:1 ; ///<
    UINT32                              AllowTxInactivePowerGating:1 ; ///<
    UINT32                              AllowRxInactivePowerGating:1 ; ///<
    UINT32                                     EnableTxSSClkGating:1 ; ///<
    UINT32                                     EnableMaxPClkGating:1 ; ///<
    UINT32                                              AllowRxPS2:1 ; ///<
    UINT32                                              AllowRxPS3:1 ; ///<
    UINT32                                              AllowTxPS2:1 ; ///<
    UINT32                                              AllowTxPS3:1 ; ///<
    UINT32                                   AllowPLLShutdownRxPS2:1 ; ///<
    UINT32                                       PLLActiveAbovePS4:1 ; ///<
    UINT32                                          PLLActiveInPS4:1 ; ///<
    UINT32                                            DisableRxPS4:1 ; ///<
    UINT32                                            DisableTxPS4:1 ; ///<
    UINT32                                     DisableTxPS4inRxPS3:1 ; ///<
    UINT32                                         RemapSATAP6TOP5:1 ; ///<
    UINT32                              FarEndAnalogLoopbackEnable:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x1230b014_STRUCT;

// Register Name PCIEP_HW_DEBUG
// Address
#define PCIE0_PCIEP_HW_DEBUG_ADDRESS                                     0x11140008
#define PCIE1_PCIEP_HW_DEBUG_ADDRESS                                     0x11240008

// Type
#define PCIEP_HW_DEBUG_TYPE                                              TYPE_SMN

#define PCIEP_HW_DEBUG_HW_00_DEBUG_OFFSET                                0
#define PCIEP_HW_DEBUG_HW_00_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_00_DEBUG_MASK                                  0x1
#define PCIEP_HW_DEBUG_HW_01_DEBUG_OFFSET                                1
#define PCIEP_HW_DEBUG_HW_01_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_01_DEBUG_MASK                                  0x2
#define PCIEP_HW_DEBUG_HW_02_DEBUG_OFFSET                                2
#define PCIEP_HW_DEBUG_HW_02_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_02_DEBUG_MASK                                  0x4
#define PCIEP_HW_DEBUG_HW_03_DEBUG_OFFSET                                3
#define PCIEP_HW_DEBUG_HW_03_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_03_DEBUG_MASK                                  0x8
#define PCIEP_HW_DEBUG_HW_04_DEBUG_OFFSET                                4
#define PCIEP_HW_DEBUG_HW_04_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_04_DEBUG_MASK                                  0x10
#define PCIEP_HW_DEBUG_HW_05_DEBUG_OFFSET                                5
#define PCIEP_HW_DEBUG_HW_05_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_05_DEBUG_MASK                                  0x20
#define PCIEP_HW_DEBUG_HW_06_DEBUG_OFFSET                                6
#define PCIEP_HW_DEBUG_HW_06_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_06_DEBUG_MASK                                  0x40
#define PCIEP_HW_DEBUG_HW_07_DEBUG_OFFSET                                7
#define PCIEP_HW_DEBUG_HW_07_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_07_DEBUG_MASK                                  0x80
#define PCIEP_HW_DEBUG_HW_08_DEBUG_OFFSET                                8
#define PCIEP_HW_DEBUG_HW_08_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_08_DEBUG_MASK                                  0x100
#define PCIEP_HW_DEBUG_HW_09_DEBUG_OFFSET                                9
#define PCIEP_HW_DEBUG_HW_09_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_09_DEBUG_MASK                                  0x200
#define PCIEP_HW_DEBUG_HW_10_DEBUG_OFFSET                                10
#define PCIEP_HW_DEBUG_HW_10_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_10_DEBUG_MASK                                  0x400
#define PCIEP_HW_DEBUG_HW_11_DEBUG_OFFSET                                11
#define PCIEP_HW_DEBUG_HW_11_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_11_DEBUG_MASK                                  0x800
#define PCIEP_HW_DEBUG_HW_12_DEBUG_OFFSET                                12
#define PCIEP_HW_DEBUG_HW_12_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_12_DEBUG_MASK                                  0x1000
#define PCIEP_HW_DEBUG_HW_13_DEBUG_OFFSET                                13
#define PCIEP_HW_DEBUG_HW_13_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_13_DEBUG_MASK                                  0x2000
#define PCIEP_HW_DEBUG_HW_14_DEBUG_OFFSET                                14
#define PCIEP_HW_DEBUG_HW_14_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_14_DEBUG_MASK                                  0x4000
#define PCIEP_HW_DEBUG_HW_15_DEBUG_OFFSET                                15
#define PCIEP_HW_DEBUG_HW_15_DEBUG_WIDTH                                 1
#define PCIEP_HW_DEBUG_HW_15_DEBUG_MASK                                  0x8000
#define PCIEP_HW_DEBUG_Reserved_31_16_OFFSET                             16
#define PCIEP_HW_DEBUG_Reserved_31_16_WIDTH                              16
#define PCIEP_HW_DEBUG_Reserved_31_16_MASK                               0xffff0000L

/// PCIEPORT0F0_00000008
typedef union {
  struct {
    UINT32                                             HW_00_DEBUG:1 ; ///<
    UINT32                                             HW_01_DEBUG:1 ; ///<
    UINT32                                             HW_02_DEBUG:1 ; ///<
    UINT32                                             HW_03_DEBUG:1 ; ///<
    UINT32                                             HW_04_DEBUG:1 ; ///<
    UINT32                                             HW_05_DEBUG:1 ; ///<
    UINT32                                             HW_06_DEBUG:1 ; ///<
    UINT32                                             HW_07_DEBUG:1 ; ///<
    UINT32                                             HW_08_DEBUG:1 ; ///<
    UINT32                                             HW_09_DEBUG:1 ; ///<
    UINT32                                             HW_10_DEBUG:1 ; ///<
    UINT32                                             HW_11_DEBUG:1 ; ///<
    UINT32                                             HW_12_DEBUG:1 ; ///<
    UINT32                                             HW_13_DEBUG:1 ; ///<
    UINT32                                             HW_14_DEBUG:1 ; ///<
    UINT32                                             HW_15_DEBUG:1 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEP_HW_DEBUG_STRUCT;

// Register Name PCIEP_PORT_CNTL

// Address
#define PCIEP_PORT_CNTL_ADDRESS                                0x11140040
#define GPP0_PORT_CNTL_ADDRESS                                 0x11140040
#define GPP1_PORT_CNTL_ADDRESS                                 0x11141040
#define GPP2_PORT_CNTL_ADDRESS                                 0x11142040
#define GPP3_PORT_CNTL_ADDRESS                                 0x11143040
#define GPP4_PORT_CNTL_ADDRESS                                 0x11144040
#define GPP5_PORT_CNTL_ADDRESS                                 0x11145040
#define GPP6_PORT_CNTL_ADDRESS                                 0x11146040
#define GPP7_PORT_CNTL_ADDRESS                                 0x11147040
#define GFX0_PORT_CNTL_ADDRESS                                 0x11240040
#define GFX1_PORT_CNTL_ADDRESS                                 0x11241040
#define GFX2_PORT_CNTL_ADDRESS                                 0x11242040
#define GFX3_PORT_CNTL_ADDRESS                                 0x11243040
#define GFX4_PORT_CNTL_ADDRESS                                 0x11244040
#define GFX5_PORT_CNTL_ADDRESS                                 0x11245040
#define GFX6_PORT_CNTL_ADDRESS                                 0x11246040
#define GFX7_PORT_CNTL_ADDRESS                                 0x11247040

// Type
#define PCIEP_PORT_CNTL_TYPE                                   TYPE_SMN

#define PCIEP_PORT_CNTL_SLV_PORT_REQ_EN_OFFSET            0
#define PCIEP_PORT_CNTL_SLV_PORT_REQ_EN_WIDTH             1
#define PCIEP_PORT_CNTL_SLV_PORT_REQ_EN_MASK              0x1
#define PCIEP_PORT_CNTL_CI_SNOOP_OVERRIDE_OFFSET          1
#define PCIEP_PORT_CNTL_CI_SNOOP_OVERRIDE_WIDTH           1
#define PCIEP_PORT_CNTL_CI_SNOOP_OVERRIDE_MASK            0x2
#define PCIEP_PORT_CNTL_HOTPLUG_MSG_EN_OFFSET             2
#define PCIEP_PORT_CNTL_HOTPLUG_MSG_EN_WIDTH              1
#define PCIEP_PORT_CNTL_HOTPLUG_MSG_EN_MASK               0x4
#define PCIEP_PORT_CNTL_NATIVE_PME_EN_OFFSET              3
#define PCIEP_PORT_CNTL_NATIVE_PME_EN_WIDTH               1
#define PCIEP_PORT_CNTL_NATIVE_PME_EN_MASK                0x8
#define PCIEP_PORT_CNTL_PWR_FAULT_EN_OFFSET               4
#define PCIEP_PORT_CNTL_PWR_FAULT_EN_WIDTH                1
#define PCIEP_PORT_CNTL_PWR_FAULT_EN_MASK                 0x10
#define PCIEP_PORT_CNTL_PMI_BM_DIS_OFFSET                 5
#define PCIEP_PORT_CNTL_PMI_BM_DIS_WIDTH                  1
#define PCIEP_PORT_CNTL_PMI_BM_DIS_MASK                   0x20
#define PCIEP_PORT_CNTL_SEQNUM_DEBUG_MODE_OFFSET          6
#define PCIEP_PORT_CNTL_SEQNUM_DEBUG_MODE_WIDTH           1
#define PCIEP_PORT_CNTL_SEQNUM_DEBUG_MODE_MASK            0x40
#define PCIEP_PORT_CNTL_CI_SLV_CPL_STATIC_ALLOC_LIMIT_S_OFFSET 8
#define PCIEP_PORT_CNTL_CI_SLV_CPL_STATIC_ALLOC_LIMIT_S_WIDTH  7
#define PCIEP_PORT_CNTL_CI_SLV_CPL_STATIC_ALLOC_LIMIT_S_MASK   0x7f00
#define PCIEP_PORT_CNTL_CI_MAX_CPL_PAYLOAD_SIZE_MODE_OFFSET 16
#define PCIEP_PORT_CNTL_CI_MAX_CPL_PAYLOAD_SIZE_MODE_WIDTH  2
#define PCIEP_PORT_CNTL_CI_MAX_CPL_PAYLOAD_SIZE_MODE_MASK   0x30000
#define PCIEP_PORT_CNTL_CI_PRIV_MAX_CPL_PAYLOAD_SIZE_OFFSET 18
#define PCIEP_PORT_CNTL_CI_PRIV_MAX_CPL_PAYLOAD_SIZE_WIDTH  3
#define PCIEP_PORT_CNTL_CI_PRIV_MAX_CPL_PAYLOAD_SIZE_MASK   0x1c0000
#define PCIEP_PORT_CNTL_CI_SLV_RSP_POISONED_UR_MODE_OFFSET 24
#define PCIEP_PORT_CNTL_CI_SLV_RSP_POISONED_UR_MODE_WIDTH  2
#define PCIEP_PORT_CNTL_CI_SLV_RSP_POISONED_UR_MODE_MASK   0x3000000

/// PCIEP_PORT_CNTL
typedef union {
  struct {
    UINT32                                         SLV_PORT_REQ_EN:1 ; ///<
    UINT32                                       CI_SNOOP_OVERRIDE:1 ; ///<
    UINT32                                          HOTPLUG_MSG_EN:1 ; ///<
    UINT32                                           NATIVE_PME_EN:1 ; ///<
    UINT32                                            PWR_FAULT_EN:1 ; ///<
    UINT32                                              PMI_BM_DIS:1 ; ///<
    UINT32                                       SEQNUM_DEBUG_MODE:1 ; ///<
    UINT32                         CI_SLV_CPL_STATIC_ALLOC_LIMIT_S:7 ; ///<
    UINT32                            CI_MAX_CPL_PAYLOAD_SIZE_MODE:2 ; ///<
    UINT32                            CI_PRIV_MAX_CPL_PAYLOAD_SIZE:3 ; ///<
    UINT32                             CI_SLV_RSP_POISONED_UR_MODE:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEP_PORT_CNTL_STRUCT;


// Register Name PCIE_TX_CNTL

// Address
#define PCIE_TX_CNTL_ADDRESS                                           0x00000080
#define GPP0_TX_CNTL_ADDRESS                                           0x11140080
#define GPP1_TX_CNTL_ADDRESS                                           0x11141080
#define GPP2_TX_CNTL_ADDRESS                                           0x11142080
#define GPP3_TX_CNTL_ADDRESS                                           0x11143080
#define GPP4_TX_CNTL_ADDRESS                                           0x11144080
#define GPP5_TX_CNTL_ADDRESS                                           0x11145080
#define GPP6_TX_CNTL_ADDRESS                                           0x11146080
#define GPP7_TX_CNTL_ADDRESS                                           0x11147080
#define GFX0_TX_CNTL_ADDRESS                                           0x11240080
#define GFX1_TX_CNTL_ADDRESS                                           0x11241080
#define GFX2_TX_CNTL_ADDRESS                                           0x11242080
#define GFX3_TX_CNTL_ADDRESS                                           0x11243080
#define GFX4_TX_CNTL_ADDRESS                                           0x11244080
#define GFX5_TX_CNTL_ADDRESS                                           0x11245080
#define GFX6_TX_CNTL_ADDRESS                                           0x11246080
#define GFX7_TX_CNTL_ADDRESS                                           0x11247080

// Type
#define PCIE_TX_CNTL_TYPE                                              TYPE_SMN

#define PCIE_TX_CNTL_Reserved_9_0_OFFSET                               0
#define PCIE_TX_CNTL_Reserved_9_0_WIDTH                                10
#define PCIE_TX_CNTL_Reserved_9_0_MASK                                 0x3ff
#define PCIE_TX_CNTL_TX_SNR_OVERRIDE_OFFSET                            10
#define PCIE_TX_CNTL_TX_SNR_OVERRIDE_WIDTH                             2
#define PCIE_TX_CNTL_TX_SNR_OVERRIDE_MASK                              0xc00
#define PCIE_TX_CNTL_TX_RO_OVERRIDE_OFFSET                             12
#define PCIE_TX_CNTL_TX_RO_OVERRIDE_WIDTH                              2
#define PCIE_TX_CNTL_TX_RO_OVERRIDE_MASK                               0x3000
#define PCIE_TX_CNTL_TX_PACK_PACKET_DIS_OFFSET                         14
#define PCIE_TX_CNTL_TX_PACK_PACKET_DIS_WIDTH                          1
#define PCIE_TX_CNTL_TX_PACK_PACKET_DIS_MASK                           0x4000
#define PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_OFFSET                           15
#define PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_WIDTH                            1
#define PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_MASK                             0x8000
#define PCIE_TX_CNTL_Reserved_19_16_OFFSET                             16
#define PCIE_TX_CNTL_Reserved_19_16_WIDTH                              4
#define PCIE_TX_CNTL_Reserved_19_16_MASK                               0xf0000
#define PCIE_TX_CNTL_TX_CPL_PASS_P_OFFSET                              20
#define PCIE_TX_CNTL_TX_CPL_PASS_P_WIDTH                               1
#define PCIE_TX_CNTL_TX_CPL_PASS_P_MASK                                0x100000
#define PCIE_TX_CNTL_TX_NP_PASS_P_OFFSET                               21
#define PCIE_TX_CNTL_TX_NP_PASS_P_WIDTH                                1
#define PCIE_TX_CNTL_TX_NP_PASS_P_MASK                                 0x200000
#define PCIE_TX_CNTL_TX_CLEAR_EXTRA_PM_REQS_OFFSET                     22
#define PCIE_TX_CNTL_TX_CLEAR_EXTRA_PM_REQS_WIDTH                      1
#define PCIE_TX_CNTL_TX_CLEAR_EXTRA_PM_REQS_MASK                       0x400000
#define PCIE_TX_CNTL_TX_FC_UPDATE_TIMEOUT_DIS_OFFSET                   23
#define PCIE_TX_CNTL_TX_FC_UPDATE_TIMEOUT_DIS_WIDTH                    1
#define PCIE_TX_CNTL_TX_FC_UPDATE_TIMEOUT_DIS_MASK                     0x800000
#define PCIE_TX_CNTL_Reserved_31_24_OFFSET                             24
#define PCIE_TX_CNTL_Reserved_31_24_WIDTH                              8
#define PCIE_TX_CNTL_Reserved_31_24_MASK                               0xff000000L

/// PCIE_TX_CNTL
typedef union {
  struct {
    UINT32                                            Reserved_9_0:10; ///<
    UINT32                                         TX_SNR_OVERRIDE:2 ; ///<
    UINT32                                          TX_RO_OVERRIDE:2 ; ///<
    UINT32                                      TX_PACK_PACKET_DIS:1 ; ///<
    UINT32                                        TX_FLUSH_TLP_DIS:1 ; ///<
    UINT32                                          Reserved_19_16:4 ; ///<
    UINT32                                           TX_CPL_PASS_P:1 ; ///<
    UINT32                                            TX_NP_PASS_P:1 ; ///<
    UINT32                                  TX_CLEAR_EXTRA_PM_REQS:1 ; ///<
    UINT32                                TX_FC_UPDATE_TIMEOUT_DIS:1 ; ///<
    UINT32                                          Reserved_31_24:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_TX_CNTL_STRUCT;


// Register Name PCIE_RX_CNTL

// Address
#define PCIE_RX_CNTL_ADDRESS                                           0x000001C0
#define GPP0_RX_CNTL_ADDRESS                                           0x111401C0
#define GPP1_RX_CNTL_ADDRESS                                           0x111411C0
#define GPP2_RX_CNTL_ADDRESS                                           0x111421C0
#define GPP3_RX_CNTL_ADDRESS                                           0x111431C0
#define GPP4_RX_CNTL_ADDRESS                                           0x111441C0
#define GPP5_RX_CNTL_ADDRESS                                           0x111451C0
#define GPP6_RX_CNTL_ADDRESS                                           0x111461C0
#define GPP7_RX_CNTL_ADDRESS                                           0x111471C0
#define GFX0_RX_CNTL_ADDRESS                                           0x112401C0
#define GFX1_RX_CNTL_ADDRESS                                           0x112411C0
#define GFX2_RX_CNTL_ADDRESS                                           0x112421C0
#define GFX3_RX_CNTL_ADDRESS                                           0x112431C0
#define GFX4_RX_CNTL_ADDRESS                                           0x112441C0
#define GFX5_RX_CNTL_ADDRESS                                           0x112451C0
#define GFX6_RX_CNTL_ADDRESS                                           0x112461C0
#define GFX7_RX_CNTL_ADDRESS                                           0x112471C0

// Type
#define PCIE_RX_CNTL_TYPE                                              TYPE_SMN

#define PCIE_RX_CNTL_RX_IGNORE_IO_ERR_OFFSET                           0
#define PCIE_RX_CNTL_RX_IGNORE_IO_ERR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_IO_ERR_MASK                             0x1
#define PCIE_RX_CNTL_RX_IGNORE_BE_ERR_OFFSET                           1
#define PCIE_RX_CNTL_RX_IGNORE_BE_ERR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_BE_ERR_MASK                             0x2
#define PCIE_RX_CNTL_RX_IGNORE_MSG_ERR_OFFSET                          2
#define PCIE_RX_CNTL_RX_IGNORE_MSG_ERR_WIDTH                           1
#define PCIE_RX_CNTL_RX_IGNORE_MSG_ERR_MASK                            0x4
#define PCIE_RX_CNTL_RX_IGNORE_CRC_ERR_OFFSET                          3
#define PCIE_RX_CNTL_RX_IGNORE_CRC_ERR_WIDTH                           1
#define PCIE_RX_CNTL_RX_IGNORE_CRC_ERR_MASK                            0x8
#define PCIE_RX_CNTL_RX_IGNORE_CFG_ERR_OFFSET                          4
#define PCIE_RX_CNTL_RX_IGNORE_CFG_ERR_WIDTH                           1
#define PCIE_RX_CNTL_RX_IGNORE_CFG_ERR_MASK                            0x10
#define PCIE_RX_CNTL_RX_IGNORE_CPL_ERR_OFFSET                          5
#define PCIE_RX_CNTL_RX_IGNORE_CPL_ERR_WIDTH                           1
#define PCIE_RX_CNTL_RX_IGNORE_CPL_ERR_MASK                            0x20
#define PCIE_RX_CNTL_RX_IGNORE_EP_ERR_OFFSET                           6
#define PCIE_RX_CNTL_RX_IGNORE_EP_ERR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_EP_ERR_MASK                             0x40
#define PCIE_RX_CNTL_RX_IGNORE_LEN_MISMATCH_ERR_OFFSET                 7
#define PCIE_RX_CNTL_RX_IGNORE_LEN_MISMATCH_ERR_WIDTH                  1
#define PCIE_RX_CNTL_RX_IGNORE_LEN_MISMATCH_ERR_MASK                   0x80
#define PCIE_RX_CNTL_RX_IGNORE_MAX_PAYLOAD_ERR_OFFSET                  8
#define PCIE_RX_CNTL_RX_IGNORE_MAX_PAYLOAD_ERR_WIDTH                   1
#define PCIE_RX_CNTL_RX_IGNORE_MAX_PAYLOAD_ERR_MASK                    0x100
#define PCIE_RX_CNTL_RX_IGNORE_TC_ERR_OFFSET                           9
#define PCIE_RX_CNTL_RX_IGNORE_TC_ERR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_TC_ERR_MASK                             0x200
#define PCIE_RX_CNTL_RX_IGNORE_CFG_UR_OFFSET                           10
#define PCIE_RX_CNTL_RX_IGNORE_CFG_UR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_CFG_UR_MASK                             0x400
#define PCIE_RX_CNTL_RX_IGNORE_IO_UR_OFFSET                            11
#define PCIE_RX_CNTL_RX_IGNORE_IO_UR_WIDTH                             1
#define PCIE_RX_CNTL_RX_IGNORE_IO_UR_MASK                              0x800
#define PCIE_RX_CNTL_RX_IGNORE_AT_ERR_OFFSET                           12
#define PCIE_RX_CNTL_RX_IGNORE_AT_ERR_WIDTH                            1
#define PCIE_RX_CNTL_RX_IGNORE_AT_ERR_MASK                             0x1000
#define PCIE_RX_CNTL_RX_NAK_IF_FIFO_FULL_OFFSET                        13
#define PCIE_RX_CNTL_RX_NAK_IF_FIFO_FULL_WIDTH                         1
#define PCIE_RX_CNTL_RX_NAK_IF_FIFO_FULL_MASK                          0x2000
#define PCIE_RX_CNTL_RX_GEN_ONE_NAK_OFFSET                             14
#define PCIE_RX_CNTL_RX_GEN_ONE_NAK_WIDTH                              1
#define PCIE_RX_CNTL_RX_GEN_ONE_NAK_MASK                               0x4000
#define PCIE_RX_CNTL_RX_FC_INIT_FROM_REG_OFFSET                        15
#define PCIE_RX_CNTL_RX_FC_INIT_FROM_REG_WIDTH                         1
#define PCIE_RX_CNTL_RX_FC_INIT_FROM_REG_MASK                          0x8000
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_OFFSET                         16
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_WIDTH                          3
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_MASK                           0x70000
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_MODE_OFFSET                    19
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_MODE_WIDTH                     1
#define PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_MODE_MASK                      0x80000
#define PCIE_RX_CNTL_RX_PCIE_CPL_TIMEOUT_DIS_OFFSET                    20
#define PCIE_RX_CNTL_RX_PCIE_CPL_TIMEOUT_DIS_WIDTH                     1
#define PCIE_RX_CNTL_RX_PCIE_CPL_TIMEOUT_DIS_MASK                      0x100000
#define PCIE_RX_CNTL_RX_IGNORE_SHORTPREFIX_ERR_OFFSET                  21
#define PCIE_RX_CNTL_RX_IGNORE_SHORTPREFIX_ERR_WIDTH                   1
#define PCIE_RX_CNTL_RX_IGNORE_SHORTPREFIX_ERR_MASK                    0x200000
#define PCIE_RX_CNTL_RX_IGNORE_MAXPREFIX_ERR_OFFSET                    22
#define PCIE_RX_CNTL_RX_IGNORE_MAXPREFIX_ERR_WIDTH                     1
#define PCIE_RX_CNTL_RX_IGNORE_MAXPREFIX_ERR_MASK                      0x400000
#define PCIE_RX_CNTL_RX_IGNORE_CPLPREFIX_ERR_OFFSET                    23
#define PCIE_RX_CNTL_RX_IGNORE_CPLPREFIX_ERR_WIDTH                     1
#define PCIE_RX_CNTL_RX_IGNORE_CPLPREFIX_ERR_MASK                      0x800000
#define PCIE_RX_CNTL_RX_IGNORE_INVALIDPASID_ERR_OFFSET                 24
#define PCIE_RX_CNTL_RX_IGNORE_INVALIDPASID_ERR_WIDTH                  1
#define PCIE_RX_CNTL_RX_IGNORE_INVALIDPASID_ERR_MASK                   0x1000000
#define PCIE_RX_CNTL_RX_IGNORE_NOT_PASID_UR_OFFSET                     25
#define PCIE_RX_CNTL_RX_IGNORE_NOT_PASID_UR_WIDTH                      1
#define PCIE_RX_CNTL_RX_IGNORE_NOT_PASID_UR_MASK                       0x2000000
#define PCIE_RX_CNTL_RX_TPH_DIS_OFFSET                                 26
#define PCIE_RX_CNTL_RX_TPH_DIS_WIDTH                                  1
#define PCIE_RX_CNTL_RX_TPH_DIS_MASK                                   0x4000000
#define PCIE_RX_CNTL_RX_RCB_FLR_TIMEOUT_DIS_OFFSET                     27
#define PCIE_RX_CNTL_RX_RCB_FLR_TIMEOUT_DIS_WIDTH                      1
#define PCIE_RX_CNTL_RX_RCB_FLR_TIMEOUT_DIS_MASK                       0x8000000
#define PCIE_RX_CNTL_Reserved_31_28_OFFSET                             28
#define PCIE_RX_CNTL_Reserved_31_28_WIDTH                              4
#define PCIE_RX_CNTL_Reserved_31_28_MASK                               0xf0000000L

/// PCIE_RX_CNTL
typedef union {
  struct {
    UINT32                                        RX_IGNORE_IO_ERR:1 ; ///<
    UINT32                                        RX_IGNORE_BE_ERR:1 ; ///<
    UINT32                                       RX_IGNORE_MSG_ERR:1 ; ///<
    UINT32                                       RX_IGNORE_CRC_ERR:1 ; ///<
    UINT32                                       RX_IGNORE_CFG_ERR:1 ; ///<
    UINT32                                       RX_IGNORE_CPL_ERR:1 ; ///<
    UINT32                                        RX_IGNORE_EP_ERR:1 ; ///<
    UINT32                              RX_IGNORE_LEN_MISMATCH_ERR:1 ; ///<
    UINT32                               RX_IGNORE_MAX_PAYLOAD_ERR:1 ; ///<
    UINT32                                        RX_IGNORE_TC_ERR:1 ; ///<
    UINT32                                        RX_IGNORE_CFG_UR:1 ; ///<
    UINT32                                         RX_IGNORE_IO_UR:1 ; ///<
    UINT32                                        RX_IGNORE_AT_ERR:1 ; ///<
    UINT32                                     RX_NAK_IF_FIFO_FULL:1 ; ///<
    UINT32                                          RX_GEN_ONE_NAK:1 ; ///<
    UINT32                                     RX_FC_INIT_FROM_REG:1 ; ///<
    UINT32                                      RX_RCB_CPL_TIMEOUT:3 ; ///<
    UINT32                                 RX_RCB_CPL_TIMEOUT_MODE:1 ; ///<
    UINT32                                 RX_PCIE_CPL_TIMEOUT_DIS:1 ; ///<
    UINT32                               RX_IGNORE_SHORTPREFIX_ERR:1 ; ///<
    UINT32                                 RX_IGNORE_MAXPREFIX_ERR:1 ; ///<
    UINT32                                 RX_IGNORE_CPLPREFIX_ERR:1 ; ///<
    UINT32                              RX_IGNORE_INVALIDPASID_ERR:1 ; ///<
    UINT32                                  RX_IGNORE_NOT_PASID_UR:1 ; ///<
    UINT32                                              RX_TPH_DIS:1 ; ///<
    UINT32                                  RX_RCB_FLR_TIMEOUT_DIS:1 ; ///<
    UINT32                                          Reserved_31_28:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_RX_CNTL_STRUCT;

// Register Name SMN_0x11140284

// Address
#define SMN_0x11140284_ADDRESS                                          0x11140284
#define SMN_0x11240284_ADDRESS                                          0x11240284

// Type
#define SMN_0x11X40284_TYPE                                             TYPE_SMN

#define SMN_0x11X40284_BIT13_OFFSET                                     13
#define SMN_0x11X40284_BIT13_WIDTH                                      1
#define SMN_0x11X40284_BIT13_MASK                                       0x2000

// Register Name PCIE_LC_CNTL2

// Address
#define PCIE0_PCIE_LC_CNTL2_ADDRESS                                      0x111402c4
#define PCIE1_PCIE_LC_CNTL2_ADDRESS                                      0x112402c4

// Type
#define PCIE_LC_CNTL2_TYPE                                              TYPE_SMN

#define PCIE_LC_CNTL2_LC_TIMED_OUT_STATE_OFFSET                         0
#define PCIE_LC_CNTL2_LC_TIMED_OUT_STATE_WIDTH                          6
#define PCIE_LC_CNTL2_LC_TIMED_OUT_STATE_MASK                           0x3f
#define PCIE_LC_CNTL2_LC_STATE_TIMED_OUT_OFFSET                         6
#define PCIE_LC_CNTL2_LC_STATE_TIMED_OUT_WIDTH                          1
#define PCIE_LC_CNTL2_LC_STATE_TIMED_OUT_MASK                           0x40
#define PCIE_LC_CNTL2_LC_LOOK_FOR_BW_REDUCTION_OFFSET                   7
#define PCIE_LC_CNTL2_LC_LOOK_FOR_BW_REDUCTION_WIDTH                    1
#define PCIE_LC_CNTL2_LC_LOOK_FOR_BW_REDUCTION_MASK                     0x80
#define PCIE_LC_CNTL2_LC_MORE_TS2_EN_OFFSET                             8
#define PCIE_LC_CNTL2_LC_MORE_TS2_EN_WIDTH                              1
#define PCIE_LC_CNTL2_LC_MORE_TS2_EN_MASK                               0x100
#define PCIE_LC_CNTL2_LC_X12_NEGOTIATION_DIS_OFFSET                     9
#define PCIE_LC_CNTL2_LC_X12_NEGOTIATION_DIS_WIDTH                      1
#define PCIE_LC_CNTL2_LC_X12_NEGOTIATION_DIS_MASK                       0x200
#define PCIE_LC_CNTL2_LC_LINK_UP_REVERSAL_EN_OFFSET                     10
#define PCIE_LC_CNTL2_LC_LINK_UP_REVERSAL_EN_WIDTH                      1
#define PCIE_LC_CNTL2_LC_LINK_UP_REVERSAL_EN_MASK                       0x400
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_OFFSET                           11
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_WIDTH                            1
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_MASK                             0x800
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_RESTART_EN_OFFSET                12
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_RESTART_EN_WIDTH                 1
#define PCIE_LC_CNTL2_LC_ILLEGAL_STATE_RESTART_EN_MASK                  0x1000
#define PCIE_LC_CNTL2_LC_WAIT_FOR_OTHER_LANES_MODE_OFFSET               13
#define PCIE_LC_CNTL2_LC_WAIT_FOR_OTHER_LANES_MODE_WIDTH                1
#define PCIE_LC_CNTL2_LC_WAIT_FOR_OTHER_LANES_MODE_MASK                 0x2000
#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_OFFSET                          14
#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_WIDTH                           2
#define PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_MASK                            0xc000
#define PCIE_LC_CNTL2_LC_DISABLE_INFERRED_ELEC_IDLE_DET_OFFSET          16
#define PCIE_LC_CNTL2_LC_DISABLE_INFERRED_ELEC_IDLE_DET_WIDTH           1
#define PCIE_LC_CNTL2_LC_DISABLE_INFERRED_ELEC_IDLE_DET_MASK            0x10000
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L1_OFFSET                        17
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L1_WIDTH                         1
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L1_MASK                          0x20000
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L23_OFFSET                       18
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L23_WIDTH                        1
#define PCIE_LC_CNTL2_LC_ALLOW_PDWN_IN_L23_MASK                         0x40000
#define PCIE_LC_CNTL2_LC_DEASSERT_RX_EN_IN_L0S_OFFSET                   19
#define PCIE_LC_CNTL2_LC_DEASSERT_RX_EN_IN_L0S_WIDTH                    1
#define PCIE_LC_CNTL2_LC_DEASSERT_RX_EN_IN_L0S_MASK                     0x80000
#define PCIE_LC_CNTL2_LC_BLOCK_EL_IDLE_IN_L0_OFFSET                     20
#define PCIE_LC_CNTL2_LC_BLOCK_EL_IDLE_IN_L0_WIDTH                      1
#define PCIE_LC_CNTL2_LC_BLOCK_EL_IDLE_IN_L0_MASK                       0x100000
#define PCIE_LC_CNTL2_LC_RCV_L0_TO_RCV_L0S_DIS_OFFSET                   21
#define PCIE_LC_CNTL2_LC_RCV_L0_TO_RCV_L0S_DIS_WIDTH                    1
#define PCIE_LC_CNTL2_LC_RCV_L0_TO_RCV_L0S_DIS_MASK                     0x200000
#define PCIE_LC_CNTL2_LC_ASSERT_INACTIVE_DURING_HOLD_OFFSET             22
#define PCIE_LC_CNTL2_LC_ASSERT_INACTIVE_DURING_HOLD_WIDTH              1
#define PCIE_LC_CNTL2_LC_ASSERT_INACTIVE_DURING_HOLD_MASK               0x400000
#define PCIE_LC_CNTL2_LC_WAIT_FOR_LANES_IN_LW_NEG_OFFSET                23
#define PCIE_LC_CNTL2_LC_WAIT_FOR_LANES_IN_LW_NEG_WIDTH                 2
#define PCIE_LC_CNTL2_LC_WAIT_FOR_LANES_IN_LW_NEG_MASK                  0x1800000
#define PCIE_LC_CNTL2_LC_PWR_DOWN_NEG_OFF_LANES_OFFSET                  25
#define PCIE_LC_CNTL2_LC_PWR_DOWN_NEG_OFF_LANES_WIDTH                   1
#define PCIE_LC_CNTL2_LC_PWR_DOWN_NEG_OFF_LANES_MASK                    0x2000000
#define PCIE_LC_CNTL2_LC_DISABLE_LOST_SYM_LOCK_ARCS_OFFSET              26
#define PCIE_LC_CNTL2_LC_DISABLE_LOST_SYM_LOCK_ARCS_WIDTH               1
#define PCIE_LC_CNTL2_LC_DISABLE_LOST_SYM_LOCK_ARCS_MASK                0x4000000
#define PCIE_LC_CNTL2_LC_LINK_BW_NOTIFICATION_DIS_OFFSET                27
#define PCIE_LC_CNTL2_LC_LINK_BW_NOTIFICATION_DIS_WIDTH                 1
#define PCIE_LC_CNTL2_LC_LINK_BW_NOTIFICATION_DIS_MASK                  0x8000000
#define PCIE_LC_CNTL2_LC_PMI_L1_WAIT_FOR_SLV_IDLE_OFFSET                28
#define PCIE_LC_CNTL2_LC_PMI_L1_WAIT_FOR_SLV_IDLE_WIDTH                 1
#define PCIE_LC_CNTL2_LC_PMI_L1_WAIT_FOR_SLV_IDLE_MASK                  0x10000000
#define PCIE_LC_CNTL2_LC_TEST_TIMER_SEL_OFFSET                          29
#define PCIE_LC_CNTL2_LC_TEST_TIMER_SEL_WIDTH                           2
#define PCIE_LC_CNTL2_LC_TEST_TIMER_SEL_MASK                            0x60000000
#define PCIE_LC_CNTL2_LC_ENABLE_INFERRED_ELEC_IDLE_FOR_PI_OFFSET        31
#define PCIE_LC_CNTL2_LC_ENABLE_INFERRED_ELEC_IDLE_FOR_PI_WIDTH         1
#define PCIE_LC_CNTL2_LC_ENABLE_INFERRED_ELEC_IDLE_FOR_PI_MASK          0x80000000L

/// PCIEPORT0F0_000002C4
typedef union {
  struct {
    UINT32                                      LC_TIMED_OUT_STATE:6 ; ///<
    UINT32                                      LC_STATE_TIMED_OUT:1 ; ///<
    UINT32                                LC_LOOK_FOR_BW_REDUCTION:1 ; ///<
    UINT32                                          LC_MORE_TS2_EN:1 ; ///<
    UINT32                                  LC_X12_NEGOTIATION_DIS:1 ; ///<
    UINT32                                  LC_LINK_UP_REVERSAL_EN:1 ; ///<
    UINT32                                        LC_ILLEGAL_STATE:1 ; ///<
    UINT32                             LC_ILLEGAL_STATE_RESTART_EN:1 ; ///<
    UINT32                            LC_WAIT_FOR_OTHER_LANES_MODE:1 ; ///<
    UINT32                                       LC_ELEC_IDLE_MODE:2 ; ///<
    UINT32                       LC_DISABLE_INFERRED_ELEC_IDLE_DET:1 ; ///<
    UINT32                                     LC_ALLOW_PDWN_IN_L1:1 ; ///<
    UINT32                                    LC_ALLOW_PDWN_IN_L23:1 ; ///<
    UINT32                                LC_DEASSERT_RX_EN_IN_L0S:1 ; ///<
    UINT32                                  LC_BLOCK_EL_IDLE_IN_L0:1 ; ///<
    UINT32                                LC_RCV_L0_TO_RCV_L0S_DIS:1 ; ///<
    UINT32                          LC_ASSERT_INACTIVE_DURING_HOLD:1 ; ///<
    UINT32                             LC_WAIT_FOR_LANES_IN_LW_NEG:2 ; ///<
    UINT32                               LC_PWR_DOWN_NEG_OFF_LANES:1 ; ///<
    UINT32                           LC_DISABLE_LOST_SYM_LOCK_ARCS:1 ; ///<
    UINT32                             LC_LINK_BW_NOTIFICATION_DIS:1 ; ///<
    UINT32                             LC_PMI_L1_WAIT_FOR_SLV_IDLE:1 ; ///<
    UINT32                                       LC_TEST_TIMER_SEL:2 ; ///<
    UINT32                     LC_ENABLE_INFERRED_ELEC_IDLE_FOR_PI:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_CNTL2_STRUCT;

// Register Name PCIE_LC_CNTL3

// Address
#define PCIE_LC_CNTL3_ADDRESS                                           0x000002d4
#define GPP0_LC_CNTL3_ADDRESS                                           0x111402d4
#define GPP1_LC_CNTL3_ADDRESS                                           0x111412d4
#define GPP2_LC_CNTL3_ADDRESS                                           0x111422d4
#define GPP3_LC_CNTL3_ADDRESS                                           0x111432d4
#define GPP4_LC_CNTL3_ADDRESS                                           0x111442d4
#define GPP5_LC_CNTL3_ADDRESS                                           0x111452d4
#define GPP6_LC_CNTL3_ADDRESS                                           0x111462d4
#define GPP7_LC_CNTL3_ADDRESS                                           0x111472d4
#define GFX0_LC_CNTL3_ADDRESS                                           0x112402d4
#define GFX1_LC_CNTL3_ADDRESS                                           0x112412d4
#define GFX2_LC_CNTL3_ADDRESS                                           0x112422d4
#define GFX3_LC_CNTL3_ADDRESS                                           0x112432d4
#define GFX4_LC_CNTL3_ADDRESS                                           0x112442d4
#define GFX5_LC_CNTL3_ADDRESS                                           0x112452d4
#define GFX6_LC_CNTL3_ADDRESS                                           0x112462d4
#define GFX7_LC_CNTL3_ADDRESS                                           0x112472d4

// Type
#define PCIE_LC_CNTL3_TYPE                                              TYPE_SMN

#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_OFFSET                       0
#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_WIDTH                        1
#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_MASK                         0x1
#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_CNTL_OFFSET                  1
#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_CNTL_WIDTH                   2
#define PCIE_LC_CNTL3_LC_SELECT_DEEMPHASIS_CNTL_MASK                    0x6
#define PCIE_LC_CNTL3_LC_RCVD_DEEMPHASIS_OFFSET                         3
#define PCIE_LC_CNTL3_LC_RCVD_DEEMPHASIS_WIDTH                          1
#define PCIE_LC_CNTL3_LC_RCVD_DEEMPHASIS_MASK                           0x8
#define PCIE_LC_CNTL3_LC_COMP_TO_DETECT_OFFSET                          4
#define PCIE_LC_CNTL3_LC_COMP_TO_DETECT_WIDTH                           1
#define PCIE_LC_CNTL3_LC_COMP_TO_DETECT_MASK                            0x10
#define PCIE_LC_CNTL3_LC_RESET_TSX_CNT_IN_RLOCK_EN_OFFSET               5
#define PCIE_LC_CNTL3_LC_RESET_TSX_CNT_IN_RLOCK_EN_WIDTH                1
#define PCIE_LC_CNTL3_LC_RESET_TSX_CNT_IN_RLOCK_EN_MASK                 0x20
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPTS_ALLOWED_OFFSET      6
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPTS_ALLOWED_WIDTH       2
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK        0xc0
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPT_FAILED_OFFSET        8
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPT_FAILED_WIDTH         1
#define PCIE_LC_CNTL3_LC_AUTO_SPEED_CHANGE_ATTEMPT_FAILED_MASK          0x100
#define PCIE_LC_CNTL3_LC_CLR_FAILED_AUTO_SPD_CHANGE_CNT_OFFSET          9
#define PCIE_LC_CNTL3_LC_CLR_FAILED_AUTO_SPD_CHANGE_CNT_WIDTH           1
#define PCIE_LC_CNTL3_LC_CLR_FAILED_AUTO_SPD_CHANGE_CNT_MASK            0x200
#define PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_OFFSET                    10
#define PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_WIDTH                     1
#define PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_MASK                      0x400
#define PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_OFFSET                    11
#define PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_WIDTH                     1
#define PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_MASK                      0x800
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_OFFSET                          12
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_WIDTH                           2
#define PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_MASK                            0x3000
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_OFFSET                          14
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_WIDTH                           2
#define PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_MASK                            0xc000
#define PCIE_LC_CNTL3_LC_CHIP_BIF_USB_IDLE_EN_OFFSET                    16
#define PCIE_LC_CNTL3_LC_CHIP_BIF_USB_IDLE_EN_WIDTH                     1
#define PCIE_LC_CNTL3_LC_CHIP_BIF_USB_IDLE_EN_MASK                      0x10000
#define PCIE_LC_CNTL3_LC_L1_BLOCK_RECONFIG_EN_OFFSET                    17
#define PCIE_LC_CNTL3_LC_L1_BLOCK_RECONFIG_EN_WIDTH                     1
#define PCIE_LC_CNTL3_LC_L1_BLOCK_RECONFIG_EN_MASK                      0x20000
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_EN_OFFSET           18
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_EN_WIDTH            1
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_EN_MASK             0x40000
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_MAX_FAIL_SEL_OFFSET 19
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_MAX_FAIL_SEL_WIDTH  2
#define PCIE_LC_CNTL3_LC_AUTO_DISABLE_SPEED_SUPPORT_MAX_FAIL_SEL_MASK   0x180000
#define PCIE_LC_CNTL3_LC_FAST_L1_ENTRY_EXIT_EN_OFFSET                   21
#define PCIE_LC_CNTL3_LC_FAST_L1_ENTRY_EXIT_EN_WIDTH                    1
#define PCIE_LC_CNTL3_LC_FAST_L1_ENTRY_EXIT_EN_MASK                     0x200000
#define PCIE_LC_CNTL3_LC_RXPHYCMD_INACTIVE_EN_MODE_OFFSET               22
#define PCIE_LC_CNTL3_LC_RXPHYCMD_INACTIVE_EN_MODE_WIDTH                1
#define PCIE_LC_CNTL3_LC_RXPHYCMD_INACTIVE_EN_MODE_MASK                 0x400000
#define PCIE_LC_CNTL3_LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK_OFFSET        23
#define PCIE_LC_CNTL3_LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK_WIDTH         1
#define PCIE_LC_CNTL3_LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK_MASK          0x800000
#define PCIE_LC_CNTL3_LC_HW_VOLTAGE_IF_CONTROL_OFFSET                   24
#define PCIE_LC_CNTL3_LC_HW_VOLTAGE_IF_CONTROL_WIDTH                    2
#define PCIE_LC_CNTL3_LC_HW_VOLTAGE_IF_CONTROL_MASK                     0x3000000
#define PCIE_LC_CNTL3_LC_VOLTAGE_TIMER_SEL_OFFSET                       26
#define PCIE_LC_CNTL3_LC_VOLTAGE_TIMER_SEL_WIDTH                        4
#define PCIE_LC_CNTL3_LC_VOLTAGE_TIMER_SEL_MASK                         0x3c000000
#define PCIE_LC_CNTL3_LC_GO_TO_RECOVERY_OFFSET                          30
#define PCIE_LC_CNTL3_LC_GO_TO_RECOVERY_WIDTH                           1
#define PCIE_LC_CNTL3_LC_GO_TO_RECOVERY_MASK                            0x40000000
#define PCIE_LC_CNTL3_LC_N_EIE_SEL_OFFSET                               31
#define PCIE_LC_CNTL3_LC_N_EIE_SEL_WIDTH                                1
#define PCIE_LC_CNTL3_LC_N_EIE_SEL_MASK                                 0x80000000L

/// PCIE_LC_CNTL3
typedef union {
  struct {
    UINT32                                    LC_SELECT_DEEMPHASIS:1 ; ///<
    UINT32                               LC_SELECT_DEEMPHASIS_CNTL:2 ; ///<
    UINT32                                      LC_RCVD_DEEMPHASIS:1 ; ///<
    UINT32                                       LC_COMP_TO_DETECT:1 ; ///<
    UINT32                            LC_RESET_TSX_CNT_IN_RLOCK_EN:1 ; ///<
    UINT32                   LC_AUTO_SPEED_CHANGE_ATTEMPTS_ALLOWED:2 ; ///<
    UINT32                     LC_AUTO_SPEED_CHANGE_ATTEMPT_FAILED:1 ; ///<
    UINT32                       LC_CLR_FAILED_AUTO_SPD_CHANGE_CNT:1 ; ///<
    UINT32                                 LC_ENHANCED_HOT_PLUG_EN:1 ; ///<
    UINT32                                 LC_RCVR_DET_EN_OVERRIDE:1 ; ///<
    UINT32                                       LC_EHP_RX_PHY_CMD:2 ; ///<
    UINT32                                       LC_EHP_TX_PHY_CMD:2 ; ///<
    UINT32                                 LC_CHIP_BIF_USB_IDLE_EN:1 ; ///<
    UINT32                                 LC_L1_BLOCK_RECONFIG_EN:1 ; ///<
    UINT32                        LC_AUTO_DISABLE_SPEED_SUPPORT_EN:1 ; ///<
    UINT32              LC_AUTO_DISABLE_SPEED_SUPPORT_MAX_FAIL_SEL:2 ; ///<
    UINT32                                LC_FAST_L1_ENTRY_EXIT_EN:1 ; ///<
    UINT32                            LC_RXPHYCMD_INACTIVE_EN_MODE:1 ; ///<
    UINT32                     LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK:1 ; ///<
    UINT32                                LC_HW_VOLTAGE_IF_CONTROL:2 ; ///<
    UINT32                                    LC_VOLTAGE_TIMER_SEL:4 ; ///<
    UINT32                                       LC_GO_TO_RECOVERY:1 ; ///<
    UINT32                                            LC_N_EIE_SEL:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_CNTL3_STRUCT;



// Register Name PCIE_LC_FORCE_COEFF

// Address
#define SMN_0x111402e0_ADDRESS                                 0x111402e0
#define SMN_0x111402e0                                         0x111402e0

// Type
#define SMN_0x111402e0_TYPE                                    TYPE_SMN

#define SMN_0x111402e0_LC_FORCE_COEFF_OFFSET                   0
#define SMN_0x111402e0_LC_FORCE_COEFF_WIDTH                    1
#define SMN_0x111402e0_LC_FORCE_COEFF_MASK                     0x1
#define SMN_0x111402e0_LC_FORCE_PRE_CURSOR_OFFSET              1
#define SMN_0x111402e0_LC_FORCE_PRE_CURSOR_WIDTH               6
#define SMN_0x111402e0_LC_FORCE_PRE_CURSOR_MASK                0x7e
#define SMN_0x111402e0_LC_FORCE_CURSOR_OFFSET                  7
#define SMN_0x111402e0_LC_FORCE_CURSOR_WIDTH                   6
#define SMN_0x111402e0_LC_FORCE_CURSOR_MASK                    0x1f80
#define SMN_0x111402e0_LC_FORCE_POST_CURSOR_OFFSET             13
#define SMN_0x111402e0_LC_FORCE_POST_CURSOR_WIDTH              6
#define SMN_0x111402e0_LC_FORCE_POST_CURSOR_MASK               0x7e000
#define SMN_0x111402e0_LC_3X3_COEFF_SEARCH_EN_OFFSET           19
#define SMN_0x111402e0_LC_3X3_COEFF_SEARCH_EN_WIDTH            1
#define SMN_0x111402e0_LC_3X3_COEFF_SEARCH_EN_MASK             0x80000
#define SMN_0x111402e0_LC_PRESET_10_EN_OFFSET                  20
#define SMN_0x111402e0_LC_PRESET_10_EN_WIDTH                   1
#define SMN_0x111402e0_LC_PRESET_10_EN_MASK                    0x100000
#define SMN_0x111402e0_Reserved_31_21_OFFSET                   21
#define SMN_0x111402e0_Reserved_31_21_WIDTH                    11
#define SMN_0x111402e0_Reserved_31_21_MASK                     0xffe00000L

/// PCIEPORT0F0_000002E0
typedef union {
  struct {
    UINT32                                          LC_FORCE_COEFF:1 ; ///<
    UINT32                                     LC_FORCE_PRE_CURSOR:6 ; ///<
    UINT32                                         LC_FORCE_CURSOR:6 ; ///<
    UINT32                                    LC_FORCE_POST_CURSOR:6 ; ///<
    UINT32                                  LC_3X3_COEFF_SEARCH_EN:1 ; ///<
    UINT32                                         LC_PRESET_10_EN:1 ; ///<
    UINT32                                          Reserved_31_21:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x111402e0_STRUCT;

// Register Name PCIE_LC_CNTL4

// Address
#define SMN_0x111402d8_ADDRESS                                 0x111402d8
#define SMN_0x111402d8                                         0x111402d8

// Type
#define SMN_0x111402d8_TYPE                                    TYPE_SMN

#define SMN_0x111402d8_LC_TX_ENABLE_BEHAVIOUR_OFFSET           0
#define SMN_0x111402d8_LC_TX_ENABLE_BEHAVIOUR_WIDTH            2
#define SMN_0x111402d8_LC_TX_ENABLE_BEHAVIOUR_MASK             0x3
#define SMN_0x111402d8_LC_DIS_CONTIG_END_SET_CHECK_OFFSET      2
#define SMN_0x111402d8_LC_DIS_CONTIG_END_SET_CHECK_WIDTH       1
#define SMN_0x111402d8_LC_DIS_CONTIG_END_SET_CHECK_MASK        0x4
#define SMN_0x111402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_OFFSET   3
#define SMN_0x111402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_WIDTH    1
#define SMN_0x111402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_MASK     0x8
#define SMN_0x111402d8_LC_BYPASS_EQ_OFFSET                     4
#define SMN_0x111402d8_LC_BYPASS_EQ_WIDTH                      1
#define SMN_0x111402d8_LC_BYPASS_EQ_MASK                       0x10
#define SMN_0x111402d8_LC_REDO_EQ_OFFSET                       5
#define SMN_0x111402d8_LC_REDO_EQ_WIDTH                        1
#define SMN_0x111402d8_LC_REDO_EQ_MASK                         0x20
#define SMN_0x111402d8_LC_EXTEND_EIEOS_OFFSET                  6
#define SMN_0x111402d8_LC_EXTEND_EIEOS_WIDTH                   1
#define SMN_0x111402d8_LC_EXTEND_EIEOS_MASK                    0x40
#define SMN_0x111402d8_LC_IGNORE_PARITY_OFFSET                 7
#define SMN_0x111402d8_LC_IGNORE_PARITY_WIDTH                  1
#define SMN_0x111402d8_LC_IGNORE_PARITY_MASK                   0x80
#define SMN_0x111402d8_LC_EQ_SEARCH_MODE_OFFSET                8
#define SMN_0x111402d8_LC_EQ_SEARCH_MODE_WIDTH                 2
#define SMN_0x111402d8_LC_EQ_SEARCH_MODE_MASK                  0x300
#define SMN_0x111402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_OFFSET     10
#define SMN_0x111402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_WIDTH      1
#define SMN_0x111402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_MASK       0x400
#define SMN_0x111402d8_LC_USC_EQ_NOT_REQD_OFFSET               11
#define SMN_0x111402d8_LC_USC_EQ_NOT_REQD_WIDTH                1
#define SMN_0x111402d8_LC_USC_EQ_NOT_REQD_MASK                 0x800
#define SMN_0x111402d8_LC_USC_GO_TO_EQ_OFFSET                  12
#define SMN_0x111402d8_LC_USC_GO_TO_EQ_WIDTH                   1
#define SMN_0x111402d8_LC_USC_GO_TO_EQ_MASK                    0x1000
#define SMN_0x111402d8_LC_SET_QUIESCE_OFFSET                   13
#define SMN_0x111402d8_LC_SET_QUIESCE_WIDTH                    1
#define SMN_0x111402d8_LC_SET_QUIESCE_MASK                     0x2000
#define SMN_0x111402d8_LC_QUIESCE_RCVD_OFFSET                  14
#define SMN_0x111402d8_LC_QUIESCE_RCVD_WIDTH                   1
#define SMN_0x111402d8_LC_QUIESCE_RCVD_MASK                    0x4000
#define SMN_0x111402d8_LC_UNEXPECTED_COEFFS_RCVD_OFFSET        15
#define SMN_0x111402d8_LC_UNEXPECTED_COEFFS_RCVD_WIDTH         1
#define SMN_0x111402d8_LC_UNEXPECTED_COEFFS_RCVD_MASK          0x8000
#define SMN_0x111402d8_LC_BYPASS_EQ_REQ_PHASE_OFFSET           16
#define SMN_0x111402d8_LC_BYPASS_EQ_REQ_PHASE_WIDTH            1
#define SMN_0x111402d8_LC_BYPASS_EQ_REQ_PHASE_MASK             0x10000
#define SMN_0x111402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_OFFSET  17
#define SMN_0x111402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_WIDTH   1
#define SMN_0x111402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_MASK    0x20000
#define SMN_0x111402d8_LC_FORCE_PRESET_VALUE_OFFSET            18
#define SMN_0x111402d8_LC_FORCE_PRESET_VALUE_WIDTH             4
#define SMN_0x111402d8_LC_FORCE_PRESET_VALUE_MASK              0x3c0000
#define SMN_0x111402d8_LC_USC_DELAY_DLLPS_OFFSET               22
#define SMN_0x111402d8_LC_USC_DELAY_DLLPS_WIDTH                1
#define SMN_0x111402d8_LC_USC_DELAY_DLLPS_MASK                 0x400000
#define SMN_0x111402d8_LC_TX_SWING_OFFSET                      23
#define SMN_0x111402d8_LC_TX_SWING_WIDTH                       1
#define SMN_0x111402d8_LC_TX_SWING_MASK                        0x800000
#define SMN_0x111402d8_LC_EQ_WAIT_FOR_EVAL_DONE_OFFSET         24
#define SMN_0x111402d8_LC_EQ_WAIT_FOR_EVAL_DONE_WIDTH          1
#define SMN_0x111402d8_LC_EQ_WAIT_FOR_EVAL_DONE_MASK           0x1000000
#define SMN_0x111402d8_LC_8GT_SKIP_ORDER_EN_OFFSET             25
#define SMN_0x111402d8_LC_8GT_SKIP_ORDER_EN_WIDTH              1
#define SMN_0x111402d8_LC_8GT_SKIP_ORDER_EN_MASK               0x2000000
#define SMN_0x111402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_OFFSET     26
#define SMN_0x111402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_WIDTH      6
#define SMN_0x111402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_MASK       0xfc000000L

/// PCIEPORT0F0_000002D8
typedef union {
  struct {
    UINT32                                  LC_TX_ENABLE_BEHAVIOUR:2 ; ///<
    UINT32                             LC_DIS_CONTIG_END_SET_CHECK:1 ; ///<
    UINT32                          LC_DIS_ASPM_L1_IN_SPEED_CHANGE:1 ; ///<
    UINT32                                            LC_BYPASS_EQ:1 ; ///<
    UINT32                                              LC_REDO_EQ:1 ; ///<
    UINT32                                         LC_EXTEND_EIEOS:1 ; ///<
    UINT32                                        LC_IGNORE_PARITY:1 ; ///<
    UINT32                                       LC_EQ_SEARCH_MODE:2 ; ///<
    UINT32                            LC_DSC_CHECK_COEFFS_IN_RLOCK:1 ; ///<
    UINT32                                      LC_USC_EQ_NOT_REQD:1 ; ///<
    UINT32                                         LC_USC_GO_TO_EQ:1 ; ///<
    UINT32                                          LC_SET_QUIESCE:1 ; ///<
    UINT32                                         LC_QUIESCE_RCVD:1 ; ///<
    UINT32                               LC_UNEXPECTED_COEFFS_RCVD:1 ; ///<
    UINT32                                  LC_BYPASS_EQ_REQ_PHASE:1 ; ///<
    UINT32                         LC_FORCE_PRESET_IN_EQ_REQ_PHASE:1 ; ///<
    UINT32                                   LC_FORCE_PRESET_VALUE:4 ; ///<
    UINT32                                      LC_USC_DELAY_DLLPS:1 ; ///<
    UINT32                                             LC_TX_SWING:1 ; ///<
    UINT32                                LC_EQ_WAIT_FOR_EVAL_DONE:1 ; ///<
    UINT32                                    LC_8GT_SKIP_ORDER_EN:1 ; ///<
    UINT32                            LC_WAIT_FOR_MORE_TS_IN_RLOCK:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x111402d8_STRUCT;

// Register Name PCIE_LC_CNTL4

// Address
#define SMN_0x112402d8_ADDRESS                                 0x112402d8
#define SMN_0x112402d8                                         0x112402d8

// Type
#define SMN_0x112402d8_TYPE                                    TYPE_SMN

#define SMN_0x112402d8_LC_TX_ENABLE_BEHAVIOUR_OFFSET           0
#define SMN_0x112402d8_LC_TX_ENABLE_BEHAVIOUR_WIDTH            2
#define SMN_0x112402d8_LC_TX_ENABLE_BEHAVIOUR_MASK             0x3
#define SMN_0x112402d8_LC_DIS_CONTIG_END_SET_CHECK_OFFSET      2
#define SMN_0x112402d8_LC_DIS_CONTIG_END_SET_CHECK_WIDTH       1
#define SMN_0x112402d8_LC_DIS_CONTIG_END_SET_CHECK_MASK        0x4
#define SMN_0x112402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_OFFSET   3
#define SMN_0x112402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_WIDTH    1
#define SMN_0x112402d8_LC_DIS_ASPM_L1_IN_SPEED_CHANGE_MASK     0x8
#define SMN_0x112402d8_LC_BYPASS_EQ_OFFSET                     4
#define SMN_0x112402d8_LC_BYPASS_EQ_WIDTH                      1
#define SMN_0x112402d8_LC_BYPASS_EQ_MASK                       0x10
#define SMN_0x112402d8_LC_REDO_EQ_OFFSET                       5
#define SMN_0x112402d8_LC_REDO_EQ_WIDTH                        1
#define SMN_0x112402d8_LC_REDO_EQ_MASK                         0x20
#define SMN_0x112402d8_LC_EXTEND_EIEOS_OFFSET                  6
#define SMN_0x112402d8_LC_EXTEND_EIEOS_WIDTH                   1
#define SMN_0x112402d8_LC_EXTEND_EIEOS_MASK                    0x40
#define SMN_0x112402d8_LC_IGNORE_PARITY_OFFSET                 7
#define SMN_0x112402d8_LC_IGNORE_PARITY_WIDTH                  1
#define SMN_0x112402d8_LC_IGNORE_PARITY_MASK                   0x80
#define SMN_0x112402d8_LC_EQ_SEARCH_MODE_OFFSET                8
#define SMN_0x112402d8_LC_EQ_SEARCH_MODE_WIDTH                 2
#define SMN_0x112402d8_LC_EQ_SEARCH_MODE_MASK                  0x300
#define SMN_0x112402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_OFFSET     10
#define SMN_0x112402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_WIDTH      1
#define SMN_0x112402d8_LC_DSC_CHECK_COEFFS_IN_RLOCK_MASK       0x400
#define SMN_0x112402d8_LC_USC_EQ_NOT_REQD_OFFSET               11
#define SMN_0x112402d8_LC_USC_EQ_NOT_REQD_WIDTH                1
#define SMN_0x112402d8_LC_USC_EQ_NOT_REQD_MASK                 0x800
#define SMN_0x112402d8_LC_USC_GO_TO_EQ_OFFSET                  12
#define SMN_0x112402d8_LC_USC_GO_TO_EQ_WIDTH                   1
#define SMN_0x112402d8_LC_USC_GO_TO_EQ_MASK                    0x1000
#define SMN_0x112402d8_LC_SET_QUIESCE_OFFSET                   13
#define SMN_0x112402d8_LC_SET_QUIESCE_WIDTH                    1
#define SMN_0x112402d8_LC_SET_QUIESCE_MASK                     0x2000
#define SMN_0x112402d8_LC_QUIESCE_RCVD_OFFSET                  14
#define SMN_0x112402d8_LC_QUIESCE_RCVD_WIDTH                   1
#define SMN_0x112402d8_LC_QUIESCE_RCVD_MASK                    0x4000
#define SMN_0x112402d8_LC_UNEXPECTED_COEFFS_RCVD_OFFSET        15
#define SMN_0x112402d8_LC_UNEXPECTED_COEFFS_RCVD_WIDTH         1
#define SMN_0x112402d8_LC_UNEXPECTED_COEFFS_RCVD_MASK          0x8000
#define SMN_0x112402d8_LC_BYPASS_EQ_REQ_PHASE_OFFSET           16
#define SMN_0x112402d8_LC_BYPASS_EQ_REQ_PHASE_WIDTH            1
#define SMN_0x112402d8_LC_BYPASS_EQ_REQ_PHASE_MASK             0x10000
#define SMN_0x112402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_OFFSET  17
#define SMN_0x112402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_WIDTH   1
#define SMN_0x112402d8_LC_FORCE_PRESET_IN_EQ_REQ_PHASE_MASK    0x20000
#define SMN_0x112402d8_LC_FORCE_PRESET_VALUE_OFFSET            18
#define SMN_0x112402d8_LC_FORCE_PRESET_VALUE_WIDTH             4
#define SMN_0x112402d8_LC_FORCE_PRESET_VALUE_MASK              0x3c0000
#define SMN_0x112402d8_LC_USC_DELAY_DLLPS_OFFSET               22
#define SMN_0x112402d8_LC_USC_DELAY_DLLPS_WIDTH                1
#define SMN_0x112402d8_LC_USC_DELAY_DLLPS_MASK                 0x400000
#define SMN_0x112402d8_LC_TX_SWING_OFFSET                      23
#define SMN_0x112402d8_LC_TX_SWING_WIDTH                       1
#define SMN_0x112402d8_LC_TX_SWING_MASK                        0x800000
#define SMN_0x112402d8_LC_EQ_WAIT_FOR_EVAL_DONE_OFFSET         24
#define SMN_0x112402d8_LC_EQ_WAIT_FOR_EVAL_DONE_WIDTH          1
#define SMN_0x112402d8_LC_EQ_WAIT_FOR_EVAL_DONE_MASK           0x1000000
#define SMN_0x112402d8_LC_8GT_SKIP_ORDER_EN_OFFSET             25
#define SMN_0x112402d8_LC_8GT_SKIP_ORDER_EN_WIDTH              1
#define SMN_0x112402d8_LC_8GT_SKIP_ORDER_EN_MASK               0x2000000
#define SMN_0x112402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_OFFSET     26
#define SMN_0x112402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_WIDTH      6
#define SMN_0x112402d8_LC_WAIT_FOR_MORE_TS_IN_RLOCK_MASK       0xfc000000L

/// PCIEPORT1F0_000002D8
typedef union {
  struct {
    UINT32                                  LC_TX_ENABLE_BEHAVIOUR:2 ; ///<
    UINT32                             LC_DIS_CONTIG_END_SET_CHECK:1 ; ///<
    UINT32                          LC_DIS_ASPM_L1_IN_SPEED_CHANGE:1 ; ///<
    UINT32                                            LC_BYPASS_EQ:1 ; ///<
    UINT32                                              LC_REDO_EQ:1 ; ///<
    UINT32                                         LC_EXTEND_EIEOS:1 ; ///<
    UINT32                                        LC_IGNORE_PARITY:1 ; ///<
    UINT32                                       LC_EQ_SEARCH_MODE:2 ; ///<
    UINT32                            LC_DSC_CHECK_COEFFS_IN_RLOCK:1 ; ///<
    UINT32                                      LC_USC_EQ_NOT_REQD:1 ; ///<
    UINT32                                         LC_USC_GO_TO_EQ:1 ; ///<
    UINT32                                          LC_SET_QUIESCE:1 ; ///<
    UINT32                                         LC_QUIESCE_RCVD:1 ; ///<
    UINT32                               LC_UNEXPECTED_COEFFS_RCVD:1 ; ///<
    UINT32                                  LC_BYPASS_EQ_REQ_PHASE:1 ; ///<
    UINT32                         LC_FORCE_PRESET_IN_EQ_REQ_PHASE:1 ; ///<
    UINT32                                   LC_FORCE_PRESET_VALUE:4 ; ///<
    UINT32                                      LC_USC_DELAY_DLLPS:1 ; ///<
    UINT32                                             LC_TX_SWING:1 ; ///<
    UINT32                                LC_EQ_WAIT_FOR_EVAL_DONE:1 ; ///<
    UINT32                                    LC_8GT_SKIP_ORDER_EN:1 ; ///<
    UINT32                            LC_WAIT_FOR_MORE_TS_IN_RLOCK:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x112402d8_STRUCT;


// Register Name PCIE_LC_CNTL6

// Address
#define SMN_0x111402ec_ADDRESS                                 0x111402ec
#define SMN_0x111402ec                                         0x111402ec

// Type
#define SMN_0x111402ec_TYPE                                    TYPE_SMN

#define SMN_0x111402ec_LC_SPC_MODE_2P5GT_OFFSET                0
#define SMN_0x111402ec_LC_SPC_MODE_2P5GT_WIDTH                 1
#define SMN_0x111402ec_LC_SPC_MODE_2P5GT_MASK                  0x1
#define SMN_0x111402ec_LC_SPC_MODE_5GT_OFFSET                  2
#define SMN_0x111402ec_LC_SPC_MODE_5GT_WIDTH                   1
#define SMN_0x111402ec_LC_SPC_MODE_5GT_MASK                    0x4
#define SMN_0x111402ec_LC_SPC_MODE_8GT_OFFSET                  4
#define SMN_0x111402ec_LC_SPC_MODE_8GT_WIDTH                   1
#define SMN_0x111402ec_LC_SPC_MODE_8GT_MASK                    0x10
#define SMN_0x111402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_OFFSET       5
#define SMN_0x111402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_WIDTH        1
#define SMN_0x111402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_MASK         0x20
#define SMN_0x111402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_OFFSET    6
#define SMN_0x111402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_WIDTH     2
#define SMN_0x111402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_MASK      0xc0
#define SMN_0x111402ec_LC_SRIS_EN_OFFSET                       8
#define SMN_0x111402ec_LC_SRIS_EN_WIDTH                        1
#define SMN_0x111402ec_LC_SRIS_EN_MASK                         0x100
#define SMN_0x111402ec_LC_SRNS_SKIP_IN_SRIS_OFFSET             9
#define SMN_0x111402ec_LC_SRNS_SKIP_IN_SRIS_WIDTH              4
#define SMN_0x111402ec_LC_SRNS_SKIP_IN_SRIS_MASK               0x1e00
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_EN_OFFSET            13
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_EN_WIDTH             1
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_EN_MASK              0x2000
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_FACTOR_OFFSET        14
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_FACTOR_WIDTH         2
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_FACTOR_MASK          0xc000
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_MODE_OFFSET          16
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_MODE_WIDTH           2
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_MODE_MASK            0x30000
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_OFFSET  18
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_WIDTH   1
#define SMN_0x111402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_MASK    0x40000
#define SMN_0x111402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_OFFSET       19
#define SMN_0x111402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_WIDTH        1
#define SMN_0x111402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_MASK         0x80000
#define SMN_0x111402ec_LC_SEND_EIEOS_IN_RCFG_OFFSET            20
#define SMN_0x111402ec_LC_SEND_EIEOS_IN_RCFG_WIDTH             1
#define SMN_0x111402ec_LC_SEND_EIEOS_IN_RCFG_MASK              0x100000
#define SMN_0x111402ec_LC_L1_POWERDOWN_OFFSET                  21
#define SMN_0x111402ec_LC_L1_POWERDOWN_WIDTH                   1
#define SMN_0x111402ec_LC_L1_POWERDOWN_MASK                    0x200000
#define SMN_0x111402ec_LC_P2_ENTRY_OFFSET                      22
#define SMN_0x111402ec_LC_P2_ENTRY_WIDTH                       1
#define SMN_0x111402ec_LC_P2_ENTRY_MASK                        0x400000
#define SMN_0x111402ec_LC_RXRECOVER_EN_OFFSET                  23
#define SMN_0x111402ec_LC_RXRECOVER_EN_WIDTH                   1
#define SMN_0x111402ec_LC_RXRECOVER_EN_MASK                    0x800000
#define SMN_0x111402ec_LC_RXRECOVER_TIMEOUT_OFFSET             24
#define SMN_0x111402ec_LC_RXRECOVER_TIMEOUT_WIDTH              7
#define SMN_0x111402ec_LC_RXRECOVER_TIMEOUT_MASK               0x7f000000
#define SMN_0x111402ec_LC_RX_L0S_STANDBY_EN_OFFSET             31
#define SMN_0x111402ec_LC_RX_L0S_STANDBY_EN_WIDTH              1
#define SMN_0x111402ec_LC_RX_L0S_STANDBY_EN_MASK               0x80000000L

/// PCIEPORT0F0_000002EC
typedef union {
  struct {
    UINT32                                       LC_SPC_MODE_2P5GT:1 ; ///<
    UINT32                                         LC_SPC_MODE_5GT:1 ; ///<
    UINT32                                         LC_SPC_MODE_8GT:1 ; ///<
    UINT32                              LC_WAIT_FOR_EIEOS_IN_RLOCK:1 ; ///<
    UINT32                           LC_DYNAMIC_INACTIVE_TS_SELECT:2 ; ///<
    UINT32                                              LC_SRIS_EN:1 ; ///<
    UINT32                                    LC_SRNS_SKIP_IN_SRIS:4 ; ///<
    UINT32                                   LC_SRIS_AUTODETECT_EN:1 ; ///<
    UINT32                               LC_SRIS_AUTODETECT_FACTOR:2 ; ///<
    UINT32                                 LC_SRIS_AUTODETECT_MODE:2 ; ///<
    UINT32                         LC_SRIS_AUTODETECT_OUT_OF_RANGE:1 ; ///<
    UINT32                              LC_DEFER_SKIP_FOR_EIEOS_EN:1 ; ///<
    UINT32                                   LC_SEND_EIEOS_IN_RCFG:1 ; ///<
    UINT32                                         LC_L1_POWERDOWN:1 ; ///<
    UINT32                                             LC_P2_ENTRY:1 ; ///<
    UINT32                                         LC_RXRECOVER_EN:1 ; ///<
    UINT32                                    LC_RXRECOVER_TIMEOUT:7 ; ///<
    UINT32                                    LC_RX_L0S_STANDBY_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x111402ec_STRUCT;

// Register Name PCIE_LC_CNTL6

// Address
#define SMN_0x112402ec_ADDRESS                                 0x112402ec
#define SMN_0x112402ec                                         0x112402ec

// Type
#define SMN_0x112402ec_TYPE                                    TYPE_SMN

#define SMN_0x112402ec_LC_SPC_MODE_2P5GT_OFFSET                0
#define SMN_0x112402ec_LC_SPC_MODE_2P5GT_WIDTH                 1
#define SMN_0x112402ec_LC_SPC_MODE_2P5GT_MASK                  0x1
#define SMN_0x112402ec_LC_SPC_MODE_5GT_OFFSET                  2
#define SMN_0x112402ec_LC_SPC_MODE_5GT_WIDTH                   1
#define SMN_0x112402ec_LC_SPC_MODE_5GT_MASK                    0x4
#define SMN_0x112402ec_LC_SPC_MODE_8GT_OFFSET                  4
#define SMN_0x112402ec_LC_SPC_MODE_8GT_WIDTH                   1
#define SMN_0x112402ec_LC_SPC_MODE_8GT_MASK                    0x10
#define SMN_0x112402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_OFFSET       5
#define SMN_0x112402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_WIDTH        1
#define SMN_0x112402ec_LC_WAIT_FOR_EIEOS_IN_RLOCK_MASK         0x20
#define SMN_0x112402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_OFFSET    6
#define SMN_0x112402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_WIDTH     2
#define SMN_0x112402ec_LC_DYNAMIC_INACTIVE_TS_SELECT_MASK      0xc0
#define SMN_0x112402ec_LC_SRIS_EN_OFFSET                       8
#define SMN_0x112402ec_LC_SRIS_EN_WIDTH                        1
#define SMN_0x112402ec_LC_SRIS_EN_MASK                         0x100
#define SMN_0x112402ec_LC_SRNS_SKIP_IN_SRIS_OFFSET             9
#define SMN_0x112402ec_LC_SRNS_SKIP_IN_SRIS_WIDTH              4
#define SMN_0x112402ec_LC_SRNS_SKIP_IN_SRIS_MASK               0x1e00
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_EN_OFFSET            13
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_EN_WIDTH             1
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_EN_MASK              0x2000
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_FACTOR_OFFSET        14
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_FACTOR_WIDTH         2
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_FACTOR_MASK          0xc000
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_MODE_OFFSET          16
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_MODE_WIDTH           2
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_MODE_MASK            0x30000
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_OFFSET  18
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_WIDTH   1
#define SMN_0x112402ec_LC_SRIS_AUTODETECT_OUT_OF_RANGE_MASK    0x40000
#define SMN_0x112402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_OFFSET       19
#define SMN_0x112402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_WIDTH        1
#define SMN_0x112402ec_LC_DEFER_SKIP_FOR_EIEOS_EN_MASK         0x80000
#define SMN_0x112402ec_LC_SEND_EIEOS_IN_RCFG_OFFSET            20
#define SMN_0x112402ec_LC_SEND_EIEOS_IN_RCFG_WIDTH             1
#define SMN_0x112402ec_LC_SEND_EIEOS_IN_RCFG_MASK              0x100000
#define SMN_0x112402ec_LC_L1_POWERDOWN_OFFSET                  21
#define SMN_0x112402ec_LC_L1_POWERDOWN_WIDTH                   1
#define SMN_0x112402ec_LC_L1_POWERDOWN_MASK                    0x200000
#define SMN_0x112402ec_LC_P2_ENTRY_OFFSET                      22
#define SMN_0x112402ec_LC_P2_ENTRY_WIDTH                       1
#define SMN_0x112402ec_LC_P2_ENTRY_MASK                        0x400000
#define SMN_0x112402ec_LC_RXRECOVER_EN_OFFSET                  23
#define SMN_0x112402ec_LC_RXRECOVER_EN_WIDTH                   1
#define SMN_0x112402ec_LC_RXRECOVER_EN_MASK                    0x800000
#define SMN_0x112402ec_LC_RXRECOVER_TIMEOUT_OFFSET             24
#define SMN_0x112402ec_LC_RXRECOVER_TIMEOUT_WIDTH              7
#define SMN_0x112402ec_LC_RXRECOVER_TIMEOUT_MASK               0x7f000000
#define SMN_0x112402ec_LC_RX_L0S_STANDBY_EN_OFFSET             31
#define SMN_0x112402ec_LC_RX_L0S_STANDBY_EN_WIDTH              1
#define SMN_0x112402ec_LC_RX_L0S_STANDBY_EN_MASK               0x80000000L

/// PCIEPORT1F0_000002EC
typedef union {
  struct {
    UINT32                                       LC_SPC_MODE_2P5GT:1 ; ///<
    UINT32                                         LC_SPC_MODE_5GT:1 ; ///<
    UINT32                                         LC_SPC_MODE_8GT:1 ; ///<
    UINT32                              LC_WAIT_FOR_EIEOS_IN_RLOCK:1 ; ///<
    UINT32                           LC_DYNAMIC_INACTIVE_TS_SELECT:2 ; ///<
    UINT32                                              LC_SRIS_EN:1 ; ///<
    UINT32                                    LC_SRNS_SKIP_IN_SRIS:4 ; ///<
    UINT32                                   LC_SRIS_AUTODETECT_EN:1 ; ///<
    UINT32                               LC_SRIS_AUTODETECT_FACTOR:2 ; ///<
    UINT32                                 LC_SRIS_AUTODETECT_MODE:2 ; ///<
    UINT32                         LC_SRIS_AUTODETECT_OUT_OF_RANGE:1 ; ///<
    UINT32                              LC_DEFER_SKIP_FOR_EIEOS_EN:1 ; ///<
    UINT32                                   LC_SEND_EIEOS_IN_RCFG:1 ; ///<
    UINT32                                         LC_L1_POWERDOWN:1 ; ///<
    UINT32                                             LC_P2_ENTRY:1 ; ///<
    UINT32                                         LC_RXRECOVER_EN:1 ; ///<
    UINT32                                    LC_RXRECOVER_TIMEOUT:7 ; ///<
    UINT32                                    LC_RX_L0S_STANDBY_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x112402ec_STRUCT;

// Register Name LINK_CAP2

// Address
#define SMN_0x11102084_ADDRESS                                 0x11102084
#define SMN_0x11102084                                         0x11102084

// Type
#define SMN_0x11102084_TYPE                                    TYPE_SMN

#define SMN_0x11102084_SUPPORTED_LINK_SPEED_OFFSET             1
#define SMN_0x11102084_SUPPORTED_LINK_SPEED_WIDTH              7
#define SMN_0x11102084_SUPPORTED_LINK_SPEED_MASK               0xfe
#define SMN_0x11102084_CROSSLINK_SUPPORTED_OFFSET              8
#define SMN_0x11102084_CROSSLINK_SUPPORTED_WIDTH               1
#define SMN_0x11102084_CROSSLINK_SUPPORTED_MASK                0x100
#define SMN_0x11102084_LOWER_SKP_OS_GEN_SUPPORT_OFFSET         9
#define SMN_0x11102084_LOWER_SKP_OS_GEN_SUPPORT_WIDTH          3
#define SMN_0x11102084_LOWER_SKP_OS_GEN_SUPPORT_MASK           0xe00
#define SMN_0x11102084_LOWER_SKP_OS_RCV_SUPPORT_OFFSET         16
#define SMN_0x11102084_LOWER_SKP_OS_RCV_SUPPORT_WIDTH          3
#define SMN_0x11102084_LOWER_SKP_OS_RCV_SUPPORT_MASK           0x70000
#define SMN_0x11102084_RESERVED_OFFSET                         19
#define SMN_0x11102084_RESERVED_WIDTH                          13
#define SMN_0x11102084_RESERVED_MASK                           0xfff80000L

/// PCIERCCFG0F2_00000084
typedef union {
  struct {
    UINT32                                    SUPPORTED_LINK_SPEED:7 ; ///<
    UINT32                                     CROSSLINK_SUPPORTED:1 ; ///<
    UINT32                                LOWER_SKP_OS_GEN_SUPPORT:3 ; ///<
    UINT32                                LOWER_SKP_OS_RCV_SUPPORT:3 ; ///<
    UINT32                                                RESERVED:13; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x11102084_STRUCT;

// Register Name LINK_CAP2

// Address
#define SMN_0x11201084_ADDRESS                                 0x11201084
#define SMN_0x11201084                                         0x11201084

// Type
#define SMN_0x11201084_TYPE                                    TYPE_SMN

#define SMN_0x11201084_SUPPORTED_LINK_SPEED_OFFSET             1
#define SMN_0x11201084_SUPPORTED_LINK_SPEED_WIDTH              7
#define SMN_0x11201084_SUPPORTED_LINK_SPEED_MASK               0xfe
#define SMN_0x11201084_CROSSLINK_SUPPORTED_OFFSET              8
#define SMN_0x11201084_CROSSLINK_SUPPORTED_WIDTH               1
#define SMN_0x11201084_CROSSLINK_SUPPORTED_MASK                0x100
#define SMN_0x11201084_LOWER_SKP_OS_GEN_SUPPORT_OFFSET         9
#define SMN_0x11201084_LOWER_SKP_OS_GEN_SUPPORT_WIDTH          3
#define SMN_0x11201084_LOWER_SKP_OS_GEN_SUPPORT_MASK           0xe00
#define SMN_0x11201084_LOWER_SKP_OS_RCV_SUPPORT_OFFSET         16
#define SMN_0x11201084_LOWER_SKP_OS_RCV_SUPPORT_WIDTH          3
#define SMN_0x11201084_LOWER_SKP_OS_RCV_SUPPORT_MASK           0x70000
#define SMN_0x11201084_RESERVED_OFFSET                         19
#define SMN_0x11201084_RESERVED_WIDTH                          13
#define SMN_0x11201084_RESERVED_MASK                           0xfff80000L

/// PCIERCCFG1F1_00000084
typedef union {
  struct {
    UINT32                                    SUPPORTED_LINK_SPEED:7 ; ///<
    UINT32                                     CROSSLINK_SUPPORTED:1 ; ///<
    UINT32                                LOWER_SKP_OS_GEN_SUPPORT:3 ; ///<
    UINT32                                LOWER_SKP_OS_RCV_SUPPORT:3 ; ///<
    UINT32                                                RESERVED:13; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x11201084_STRUCT;


// Register Name PCIE_LC_CNTL

// Address
#define SMN_0x11140280_ADDRESS                                 0x11140280
#define SMN_0x11240280_ADDRESS                                 0x11240280

// Type
#define PCIE_LC_CNTL_TYPE                                      TYPE_SMN

#define PCIE_LC_CNTL_RESERVED_OFFSET                         0
#define PCIE_LC_CNTL_RESERVED_WIDTH                          1
#define PCIE_LC_CNTL_RESERVED_MASK                           0x1
#define PCIE_LC_CNTL_LC_DONT_ENTER_L23_IN_D0_OFFSET          1
#define PCIE_LC_CNTL_LC_DONT_ENTER_L23_IN_D0_WIDTH           1
#define PCIE_LC_CNTL_LC_DONT_ENTER_L23_IN_D0_MASK            0x2
#define PCIE_LC_CNTL_LC_RESET_L_IDLE_COUNT_EN_OFFSET         2
#define PCIE_LC_CNTL_LC_RESET_L_IDLE_COUNT_EN_WIDTH          1
#define PCIE_LC_CNTL_LC_RESET_L_IDLE_COUNT_EN_MASK           0x4
#define PCIE_LC_CNTL_LC_RESET_LINK_OFFSET                    3
#define PCIE_LC_CNTL_LC_RESET_LINK_WIDTH                     1
#define PCIE_LC_CNTL_LC_RESET_LINK_MASK                      0x8
#define PCIE_LC_CNTL_LC_16X_CLEAR_TX_PIPE_OFFSET             4
#define PCIE_LC_CNTL_LC_16X_CLEAR_TX_PIPE_WIDTH              4
#define PCIE_LC_CNTL_LC_16X_CLEAR_TX_PIPE_MASK               0xf0
#define PCIE_LC_CNTL_LC_L0S_INACTIVITY_OFFSET                8
#define PCIE_LC_CNTL_LC_L0S_INACTIVITY_WIDTH                 4
#define PCIE_LC_CNTL_LC_L0S_INACTIVITY_MASK                  0xf00
#define PCIE_LC_CNTL_LC_L1_INACTIVITY_OFFSET                 12
#define PCIE_LC_CNTL_LC_L1_INACTIVITY_WIDTH                  4
#define PCIE_LC_CNTL_LC_L1_INACTIVITY_MASK                   0xf000
#define PCIE_LC_CNTL_LC_PMI_TO_L1_DIS_OFFSET                 16
#define PCIE_LC_CNTL_LC_PMI_TO_L1_DIS_WIDTH                  1
#define PCIE_LC_CNTL_LC_PMI_TO_L1_DIS_MASK                   0x10000
#define PCIE_LC_CNTL_LC_INC_N_FTS_EN_OFFSET                  17
#define PCIE_LC_CNTL_LC_INC_N_FTS_EN_WIDTH                   1
#define PCIE_LC_CNTL_LC_INC_N_FTS_EN_MASK                    0x20000
#define PCIE_LC_CNTL_LC_LOOK_FOR_IDLE_IN_L1L23_OFFSET        18
#define PCIE_LC_CNTL_LC_LOOK_FOR_IDLE_IN_L1L23_WIDTH         2
#define PCIE_LC_CNTL_LC_LOOK_FOR_IDLE_IN_L1L23_MASK          0xc0000
#define PCIE_LC_CNTL_LC_FACTOR_IN_EXT_SYNC_OFFSET            20
#define PCIE_LC_CNTL_LC_FACTOR_IN_EXT_SYNC_WIDTH             1
#define PCIE_LC_CNTL_LC_FACTOR_IN_EXT_SYNC_MASK              0x100000
#define PCIE_LC_CNTL_LC_WAIT_FOR_PM_ACK_DIS_OFFSET           21
#define PCIE_LC_CNTL_LC_WAIT_FOR_PM_ACK_DIS_WIDTH            1
#define PCIE_LC_CNTL_LC_WAIT_FOR_PM_ACK_DIS_MASK             0x200000
#define PCIE_LC_CNTL_LC_WAKE_FROM_L23_OFFSET                 22
#define PCIE_LC_CNTL_LC_WAKE_FROM_L23_WIDTH                  1
#define PCIE_LC_CNTL_LC_WAKE_FROM_L23_MASK                   0x400000
#define PCIE_LC_CNTL_LC_L1_IMMEDIATE_ACK_OFFSET              23
#define PCIE_LC_CNTL_LC_L1_IMMEDIATE_ACK_WIDTH               1
#define PCIE_LC_CNTL_LC_L1_IMMEDIATE_ACK_MASK                0x800000
#define PCIE_LC_CNTL_LC_ASPM_TO_L1_DIS_OFFSET                24
#define PCIE_LC_CNTL_LC_ASPM_TO_L1_DIS_WIDTH                 1
#define PCIE_LC_CNTL_LC_ASPM_TO_L1_DIS_MASK                  0x1000000
#define PCIE_LC_CNTL_LC_DELAY_COUNT_OFFSET                   25
#define PCIE_LC_CNTL_LC_DELAY_COUNT_WIDTH                    2
#define PCIE_LC_CNTL_LC_DELAY_COUNT_MASK                     0x6000000
#define PCIE_LC_CNTL_LC_DELAY_L0S_EXIT_OFFSET                27
#define PCIE_LC_CNTL_LC_DELAY_L0S_EXIT_WIDTH                 1
#define PCIE_LC_CNTL_LC_DELAY_L0S_EXIT_MASK                  0x8000000
#define PCIE_LC_CNTL_LC_DELAY_L1_EXIT_OFFSET                 28
#define PCIE_LC_CNTL_LC_DELAY_L1_EXIT_WIDTH                  1
#define PCIE_LC_CNTL_LC_DELAY_L1_EXIT_MASK                   0x10000000
#define PCIE_LC_CNTL_LC_EXTEND_WAIT_FOR_EL_IDLE_OFFSET       29
#define PCIE_LC_CNTL_LC_EXTEND_WAIT_FOR_EL_IDLE_WIDTH        1
#define PCIE_LC_CNTL_LC_EXTEND_WAIT_FOR_EL_IDLE_MASK         0x20000000
#define PCIE_LC_CNTL_LC_ESCAPE_L1L23_EN_OFFSET               30
#define PCIE_LC_CNTL_LC_ESCAPE_L1L23_EN_WIDTH                1
#define PCIE_LC_CNTL_LC_ESCAPE_L1L23_EN_MASK                 0x40000000
#define PCIE_LC_CNTL_LC_GATE_RCVR_IDLE_OFFSET                31
#define PCIE_LC_CNTL_LC_GATE_RCVR_IDLE_WIDTH                 1
#define PCIE_LC_CNTL_LC_GATE_RCVR_IDLE_MASK                  0x80000000L

/// PCIEPORT0F0_00000280
typedef union {
  struct {
    UINT32                                                RESERVED:1 ; ///<
    UINT32                                 LC_DONT_ENTER_L23_IN_D0:1 ; ///<
    UINT32                                LC_RESET_L_IDLE_COUNT_EN:1 ; ///<
    UINT32                                           LC_RESET_LINK:1 ; ///<
    UINT32                                    LC_16X_CLEAR_TX_PIPE:4 ; ///<
    UINT32                                       LC_L0S_INACTIVITY:4 ; ///<
    UINT32                                        LC_L1_INACTIVITY:4 ; ///<
    UINT32                                        LC_PMI_TO_L1_DIS:1 ; ///<
    UINT32                                         LC_INC_N_FTS_EN:1 ; ///<
    UINT32                               LC_LOOK_FOR_IDLE_IN_L1L23:2 ; ///<
    UINT32                                   LC_FACTOR_IN_EXT_SYNC:1 ; ///<
    UINT32                                  LC_WAIT_FOR_PM_ACK_DIS:1 ; ///<
    UINT32                                        LC_WAKE_FROM_L23:1 ; ///<
    UINT32                                     LC_L1_IMMEDIATE_ACK:1 ; ///<
    UINT32                                       LC_ASPM_TO_L1_DIS:1 ; ///<
    UINT32                                          LC_DELAY_COUNT:2 ; ///<
    UINT32                                       LC_DELAY_L0S_EXIT:1 ; ///<
    UINT32                                        LC_DELAY_L1_EXIT:1 ; ///<
    UINT32                              LC_EXTEND_WAIT_FOR_EL_IDLE:1 ; ///<
    UINT32                                      LC_ESCAPE_L1L23_EN:1 ; ///<
    UINT32                                       LC_GATE_RCVR_IDLE:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_CNTL_STRUCT;

// Address
#define PCIE0_LC_LINK_WIDTH_CNTL_ADDRESS                        0x11140288
#define PCIE1_LC_LINK_WIDTH_CNTL_ADDRESS                        0x11240288

// Type
#define PCIE_LC_LINK_WIDTH_CNTL_TYPE                           TYPE_SMN

#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_OFFSET                      0
#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_WIDTH                       3
#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_MASK                        0x7
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_3_3_OFFSET                       3
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_3_3_WIDTH                        1
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_3_3_MASK                         0x8
#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_RD_OFFSET                   4
#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_RD_WIDTH                    3
#define PCIE_LC_LINK_WIDTH_CNTL_LC_LINK_WIDTH_RD_MASK                     0x70
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_ARC_MISSING_ESCAPE_OFFSET     7
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_ARC_MISSING_ESCAPE_WIDTH      1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_ARC_MISSING_ESCAPE_MASK       0x80
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_NOW_OFFSET                    8
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_NOW_WIDTH                     1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RECONFIG_NOW_MASK                      0x100
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATION_SUPPORT_OFFSET           9
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATION_SUPPORT_WIDTH            1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATION_SUPPORT_MASK             0x200
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATE_EN_OFFSET                  10
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATE_EN_WIDTH                   1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RENEGOTIATE_EN_MASK                    0x400
#define PCIE_LC_LINK_WIDTH_CNTL_LC_SHORT_RECONFIG_EN_OFFSET               11
#define PCIE_LC_LINK_WIDTH_CNTL_LC_SHORT_RECONFIG_EN_WIDTH                1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_SHORT_RECONFIG_EN_MASK                 0x800
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_SUPPORT_OFFSET             12
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_SUPPORT_WIDTH              1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_SUPPORT_MASK               0x1000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_DIS_OFFSET                 13
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_DIS_WIDTH                  1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_DIS_MASK                   0x2000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_WAIT_FOR_RCVR_DIS_OFFSET         14
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_WAIT_FOR_RCVR_DIS_WIDTH          1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_WAIT_FOR_RCVR_DIS_MASK           0x4000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_TIMER_SEL_OFFSET                 15
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_TIMER_SEL_WIDTH                  1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCFG_TIMER_SEL_MASK                   0x8000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DEASSERT_TX_PDNB_OFFSET                16
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DEASSERT_TX_PDNB_WIDTH                 1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DEASSERT_TX_PDNB_MASK                  0x10000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_L1_RECONFIG_EN_OFFSET                  17
#define PCIE_LC_LINK_WIDTH_CNTL_LC_L1_RECONFIG_EN_WIDTH                   1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_L1_RECONFIG_EN_MASK                    0x20000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYNLINK_MST_EN_OFFSET                  18
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYNLINK_MST_EN_WIDTH                   1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYNLINK_MST_EN_MASK                    0x40000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DUAL_END_RECONFIG_EN_OFFSET            19
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DUAL_END_RECONFIG_EN_WIDTH             1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DUAL_END_RECONFIG_EN_MASK              0x80000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_CAPABLE_OFFSET             20
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_CAPABLE_WIDTH              1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_UPCONFIGURE_CAPABLE_MASK               0x100000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYN_LANES_PWR_STATE_OFFSET             21
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYN_LANES_PWR_STATE_WIDTH              2
#define PCIE_LC_LINK_WIDTH_CNTL_LC_DYN_LANES_PWR_STATE_MASK               0x600000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_EQ_REVERSAL_LOGIC_EN_OFFSET            23
#define PCIE_LC_LINK_WIDTH_CNTL_LC_EQ_REVERSAL_LOGIC_EN_WIDTH             1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_EQ_REVERSAL_LOGIC_EN_MASK              0x800000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_MULT_REVERSE_ATTEMP_EN_OFFSET          24
#define PCIE_LC_LINK_WIDTH_CNTL_LC_MULT_REVERSE_ATTEMP_EN_WIDTH           1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_MULT_REVERSE_ATTEMP_EN_MASK            0x1000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RESET_TSX_CNT_IN_RCONFIG_EN_OFFSET     25
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RESET_TSX_CNT_IN_RCONFIG_EN_WIDTH      1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_RESET_TSX_CNT_IN_RCONFIG_EN_MASK       0x2000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_L_IDLE_IN_R_IDLE_OFFSET       26
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_L_IDLE_IN_R_IDLE_WIDTH        1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_L_IDLE_IN_R_IDLE_MASK         0x4000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_NON_EI_ON_RXL0S_EXIT_OFFSET   27
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_NON_EI_ON_RXL0S_EXIT_WIDTH    1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_WAIT_FOR_NON_EI_ON_RXL0S_EXIT_MASK     0x8000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_HOLD_EI_FOR_RSPEED_CMD_CHANGE_OFFSET   28
#define PCIE_LC_LINK_WIDTH_CNTL_LC_HOLD_EI_FOR_RSPEED_CMD_CHANGE_WIDTH    1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_HOLD_EI_FOR_RSPEED_CMD_CHANGE_MASK     0x10000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_BYPASS_RXL0S_ON_SHORT_EI_OFFSET        29
#define PCIE_LC_LINK_WIDTH_CNTL_LC_BYPASS_RXL0S_ON_SHORT_EI_WIDTH         1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_BYPASS_RXL0S_ON_SHORT_EI_MASK          0x20000000
#define PCIE_LC_LINK_WIDTH_CNTL_LC_TURN_OFF_UNUSED_LANES_OFFSET           30
#define PCIE_LC_LINK_WIDTH_CNTL_LC_TURN_OFF_UNUSED_LANES_WIDTH            1
#define PCIE_LC_LINK_WIDTH_CNTL_LC_TURN_OFF_UNUSED_LANES_MASK             0x40000000
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_31_31_OFFSET                     31
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_31_31_WIDTH                      1
#define PCIE_LC_LINK_WIDTH_CNTL_Reserved_31_31_MASK                       0x80000000L

/// PCIE_LC_LINK_WIDTH_CNTL
typedef union {
  struct {
    UINT32                                           LC_LINK_WIDTH:3 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                        LC_LINK_WIDTH_RD:3 ; ///<
    UINT32                          LC_RECONFIG_ARC_MISSING_ESCAPE:1 ; ///<
    UINT32                                         LC_RECONFIG_NOW:1 ; ///<
    UINT32                                LC_RENEGOTIATION_SUPPORT:1 ; ///<
    UINT32                                       LC_RENEGOTIATE_EN:1 ; ///<
    UINT32                                    LC_SHORT_RECONFIG_EN:1 ; ///<
    UINT32                                  LC_UPCONFIGURE_SUPPORT:1 ; ///<
    UINT32                                      LC_UPCONFIGURE_DIS:1 ; ///<
    UINT32                              LC_UPCFG_WAIT_FOR_RCVR_DIS:1 ; ///<
    UINT32                                      LC_UPCFG_TIMER_SEL:1 ; ///<
    UINT32                                     LC_DEASSERT_TX_PDNB:1 ; ///<
    UINT32                                       LC_L1_RECONFIG_EN:1 ; ///<
    UINT32                                       LC_DYNLINK_MST_EN:1 ; ///<
    UINT32                                 LC_DUAL_END_RECONFIG_EN:1 ; ///<
    UINT32                                  LC_UPCONFIGURE_CAPABLE:1 ; ///<
    UINT32                                  LC_DYN_LANES_PWR_STATE:2 ; ///<
    UINT32                                 LC_EQ_REVERSAL_LOGIC_EN:1 ; ///<
    UINT32                               LC_MULT_REVERSE_ATTEMP_EN:1 ; ///<
    UINT32                          LC_RESET_TSX_CNT_IN_RCONFIG_EN:1 ; ///<
    UINT32                            LC_WAIT_FOR_L_IDLE_IN_R_IDLE:1 ; ///<
    UINT32                        LC_WAIT_FOR_NON_EI_ON_RXL0S_EXIT:1 ; ///<
    UINT32                        LC_HOLD_EI_FOR_RSPEED_CMD_CHANGE:1 ; ///<
    UINT32                             LC_BYPASS_RXL0S_ON_SHORT_EI:1 ; ///<
    UINT32                                LC_TURN_OFF_UNUSED_LANES:1 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_LINK_WIDTH_CNTL_STRUCT;

// Address
#define PCIE0_LC_CNTL6_ADDRESS                                  0x111402ec
#define PCIE1_LC_CNTL6_ADDRESS                                  0x112402ec

// Type
#define PCIE_LC_CNTL6_TYPE                                     TYPE_SMN

#define PCIE_LC_CNTL6_LC_SPC_MODE_2P5GT_OFFSET                  0
#define PCIE_LC_CNTL6_LC_SPC_MODE_2P5GT_WIDTH                   1
#define PCIE_LC_CNTL6_LC_SPC_MODE_2P5GT_MASK                    0x1
#define PCIE_LC_CNTL6_Reserved_1_1_OFFSET                       1
#define PCIE_LC_CNTL6_Reserved_1_1_WIDTH                        1
#define PCIE_LC_CNTL6_Reserved_1_1_MASK                         0x2
#define PCIE_LC_CNTL6_LC_SPC_MODE_5GT_OFFSET                    2
#define PCIE_LC_CNTL6_LC_SPC_MODE_5GT_WIDTH                     1
#define PCIE_LC_CNTL6_LC_SPC_MODE_5GT_MASK                      0x4
#define PCIE_LC_CNTL6_Reserved_3_3_OFFSET                       3
#define PCIE_LC_CNTL6_Reserved_3_3_WIDTH                        1
#define PCIE_LC_CNTL6_Reserved_3_3_MASK                         0x8
#define PCIE_LC_CNTL6_LC_SPC_MODE_8GT_OFFSET                    4
#define PCIE_LC_CNTL6_LC_SPC_MODE_8GT_WIDTH                     1
#define PCIE_LC_CNTL6_LC_SPC_MODE_8GT_MASK                      0x10
#define PCIE_LC_CNTL6_LC_WAIT_FOR_EIEOS_IN_RLOCK_OFFSET         5
#define PCIE_LC_CNTL6_LC_WAIT_FOR_EIEOS_IN_RLOCK_WIDTH          1
#define PCIE_LC_CNTL6_LC_WAIT_FOR_EIEOS_IN_RLOCK_MASK           0x20
#define PCIE_LC_CNTL6_LC_DYNAMIC_INACTIVE_TS_SELECT_OFFSET      6
#define PCIE_LC_CNTL6_LC_DYNAMIC_INACTIVE_TS_SELECT_WIDTH       2
#define PCIE_LC_CNTL6_LC_DYNAMIC_INACTIVE_TS_SELECT_MASK        0xc0
#define PCIE_LC_CNTL6_LC_SRIS_EN_OFFSET                         8
#define PCIE_LC_CNTL6_LC_SRIS_EN_WIDTH                          1
#define PCIE_LC_CNTL6_LC_SRIS_EN_MASK                           0x100
#define PCIE_LC_CNTL6_LC_SRNS_SKIP_IN_SRIS_OFFSET               9
#define PCIE_LC_CNTL6_LC_SRNS_SKIP_IN_SRIS_WIDTH                4
#define PCIE_LC_CNTL6_LC_SRNS_SKIP_IN_SRIS_MASK                 0x1e00
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_EN_OFFSET              13
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_EN_WIDTH               1
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_EN_MASK                0x2000
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_FACTOR_OFFSET          14
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_FACTOR_WIDTH           2
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_FACTOR_MASK            0xc000
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_MODE_OFFSET            16
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_MODE_WIDTH             2
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_MODE_MASK              0x30000
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_OUT_OF_RANGE_OFFSET    18
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_OUT_OF_RANGE_WIDTH     1
#define PCIE_LC_CNTL6_LC_SRIS_AUTODETECT_OUT_OF_RANGE_MASK      0x40000
#define PCIE_LC_CNTL6_LC_DEFER_SKIP_FOR_EIEOS_EN_OFFSET         19
#define PCIE_LC_CNTL6_LC_DEFER_SKIP_FOR_EIEOS_EN_WIDTH          1
#define PCIE_LC_CNTL6_LC_DEFER_SKIP_FOR_EIEOS_EN_MASK           0x80000
#define PCIE_LC_CNTL6_LC_SEND_EIEOS_IN_RCFG_OFFSET              20
#define PCIE_LC_CNTL6_LC_SEND_EIEOS_IN_RCFG_WIDTH               1
#define PCIE_LC_CNTL6_LC_SEND_EIEOS_IN_RCFG_MASK                0x100000
#define PCIE_LC_CNTL6_LC_L1_POWERDOWN_OFFSET                    21
#define PCIE_LC_CNTL6_LC_L1_POWERDOWN_WIDTH                     1
#define PCIE_LC_CNTL6_LC_L1_POWERDOWN_MASK                      0x200000
#define PCIE_LC_CNTL6_LC_P2_ENTRY_OFFSET                        22
#define PCIE_LC_CNTL6_LC_P2_ENTRY_WIDTH                         1
#define PCIE_LC_CNTL6_LC_P2_ENTRY_MASK                          0x400000
#define PCIE_LC_CNTL6_LC_RXRECOVER_EN_OFFSET                    23
#define PCIE_LC_CNTL6_LC_RXRECOVER_EN_WIDTH                     1
#define PCIE_LC_CNTL6_LC_RXRECOVER_EN_MASK                      0x800000
#define PCIE_LC_CNTL6_LC_RXRECOVER_TIMEOUT_OFFSET               24
#define PCIE_LC_CNTL6_LC_RXRECOVER_TIMEOUT_WIDTH                7
#define PCIE_LC_CNTL6_LC_RXRECOVER_TIMEOUT_MASK                 0x7f000000
#define PCIE_LC_CNTL6_LC_RX_L0S_STANDBY_EN_OFFSET               31
#define PCIE_LC_CNTL6_LC_RX_L0S_STANDBY_EN_WIDTH                1
#define PCIE_LC_CNTL6_LC_RX_L0S_STANDBY_EN_MASK                 0x80000000L

/// PCIE_LC_CNTL6
typedef union {
  struct {
    UINT32                                       LC_SPC_MODE_2P5GT:1 ; ///<
    UINT32                                            Reserved_1_1:1 ; ///<
    UINT32                                         LC_SPC_MODE_5GT:1 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                         LC_SPC_MODE_8GT:1 ; ///<
    UINT32                              LC_WAIT_FOR_EIEOS_IN_RLOCK:1 ; ///<
    UINT32                           LC_DYNAMIC_INACTIVE_TS_SELECT:2 ; ///<
    UINT32                                              LC_SRIS_EN:1 ; ///<
    UINT32                                    LC_SRNS_SKIP_IN_SRIS:4 ; ///<
    UINT32                                   LC_SRIS_AUTODETECT_EN:1 ; ///<
    UINT32                               LC_SRIS_AUTODETECT_FACTOR:2 ; ///<
    UINT32                                 LC_SRIS_AUTODETECT_MODE:2 ; ///<
    UINT32                         LC_SRIS_AUTODETECT_OUT_OF_RANGE:1 ; ///<
    UINT32                              LC_DEFER_SKIP_FOR_EIEOS_EN:1 ; ///<
    UINT32                                   LC_SEND_EIEOS_IN_RCFG:1 ; ///<
    UINT32                                         LC_L1_POWERDOWN:1 ; ///<
    UINT32                                             LC_P2_ENTRY:1 ; ///<
    UINT32                                         LC_RXRECOVER_EN:1 ; ///<
    UINT32                                    LC_RXRECOVER_TIMEOUT:7 ; ///<
    UINT32                                    LC_RX_L0S_STANDBY_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_CNTL6_STRUCT;


// Register Name PCIE_LC_FORCE_COEFF

// Address
#define SMN_0x112402e0_ADDRESS                                 0x112402e0
#define SMN_0x112402e0                                         0x112402e0

// Type
#define SMN_0x112402e0_TYPE                                    TYPE_SMN

#define SMN_0x112402e0_LC_FORCE_COEFF_OFFSET                   0
#define SMN_0x112402e0_LC_FORCE_COEFF_WIDTH                    1
#define SMN_0x112402e0_LC_FORCE_COEFF_MASK                     0x1
#define SMN_0x112402e0_LC_FORCE_PRE_CURSOR_OFFSET              1
#define SMN_0x112402e0_LC_FORCE_PRE_CURSOR_WIDTH               6
#define SMN_0x112402e0_LC_FORCE_PRE_CURSOR_MASK                0x7e
#define SMN_0x112402e0_LC_FORCE_CURSOR_OFFSET                  7
#define SMN_0x112402e0_LC_FORCE_CURSOR_WIDTH                   6
#define SMN_0x112402e0_LC_FORCE_CURSOR_MASK                    0x1f80
#define SMN_0x112402e0_LC_FORCE_POST_CURSOR_OFFSET             13
#define SMN_0x112402e0_LC_FORCE_POST_CURSOR_WIDTH              6
#define SMN_0x112402e0_LC_FORCE_POST_CURSOR_MASK               0x7e000
#define SMN_0x112402e0_LC_3X3_COEFF_SEARCH_EN_OFFSET           19
#define SMN_0x112402e0_LC_3X3_COEFF_SEARCH_EN_WIDTH            1
#define SMN_0x112402e0_LC_3X3_COEFF_SEARCH_EN_MASK             0x80000
#define SMN_0x112402e0_LC_PRESET_10_EN_OFFSET                  20
#define SMN_0x112402e0_LC_PRESET_10_EN_WIDTH                   1
#define SMN_0x112402e0_LC_PRESET_10_EN_MASK                    0x100000

/// PCIEPORT1F0_000002E0
typedef union {
  struct {
    UINT32                                          LC_FORCE_COEFF:1 ; ///<
    UINT32                                     LC_FORCE_PRE_CURSOR:6 ; ///<
    UINT32                                         LC_FORCE_CURSOR:6 ; ///<
    UINT32                                    LC_FORCE_POST_CURSOR:6 ; ///<
    UINT32                                  LC_3X3_COEFF_SEARCH_EN:1 ; ///<
    UINT32                                         LC_PRESET_10_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x112402e0_STRUCT;
// Register Name PCIE_LC_CNTL


// Register Name PCIE_LC_CNTL7

// Address
#define SMN_0x111402f0_ADDRESS                                 0x111402f0
#define SMN_0x111402f0                                         0x111402f0

// Type
#define SMN_0x111402f0_TYPE                                    TYPE_SMN

#define SMN_0x111402f0_LC_EXPECTED_TS2_CFG_COMPLETE_OFFSET     0
#define SMN_0x111402f0_LC_EXPECTED_TS2_CFG_COMPLETE_WIDTH      1
#define SMN_0x111402f0_LC_EXPECTED_TS2_CFG_COMPLETE_MASK       0x1
#define SMN_0x111402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_OFFSET 1
#define SMN_0x111402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_WIDTH  1
#define SMN_0x111402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_MASK   0x2
#define SMN_0x111402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_OFFSET    2
#define SMN_0x111402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_WIDTH     1
#define SMN_0x111402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_MASK      0x4
#define SMN_0x111402f0_LC_RESET_TS_COUNT_ON_EI_OFFSET          3
#define SMN_0x111402f0_LC_RESET_TS_COUNT_ON_EI_WIDTH           1
#define SMN_0x111402f0_LC_RESET_TS_COUNT_ON_EI_MASK            0x8
#define SMN_0x111402f0_LC_NBIF_ASPM_INPUT_EN_OFFSET            4
#define SMN_0x111402f0_LC_NBIF_ASPM_INPUT_EN_WIDTH             1
#define SMN_0x111402f0_LC_NBIF_ASPM_INPUT_EN_MASK              0x10
#define SMN_0x111402f0_LC_EVER_IDLE_TO_RLOCK_OFFSET            8
#define SMN_0x111402f0_LC_EVER_IDLE_TO_RLOCK_WIDTH             1
#define SMN_0x111402f0_LC_EVER_IDLE_TO_RLOCK_MASK              0x100
#define SMN_0x111402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_OFFSET     9
#define SMN_0x111402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_WIDTH      1
#define SMN_0x111402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_MASK       0x200
#define SMN_0x111402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_OFFSET 12
#define SMN_0x111402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_WIDTH  1
#define SMN_0x111402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_MASK   0x1000
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_OFFSET   13
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_WIDTH    8
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_MASK     0x1fe000
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_MODE_OFFSET       21
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_MODE_WIDTH        1
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_MODE_MASK         0x200000
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_OFFSET 22
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_WIDTH  1
#define SMN_0x111402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_MASK   0x400000
#define SMN_0x111402f0_LC_LINK_MANAGEMENT_EN_OFFSET            23
#define SMN_0x111402f0_LC_LINK_MANAGEMENT_EN_WIDTH             1
#define SMN_0x111402f0_LC_LINK_MANAGEMENT_EN_MASK              0x800000
#define SMN_0x111402f0_LC_FOM_TIME_OFFSET                      24
#define SMN_0x111402f0_LC_FOM_TIME_WIDTH                       2
#define SMN_0x111402f0_LC_FOM_TIME_MASK                        0x3000000
#define SMN_0x111402f0_LC_SAFE_EQ_SEARCH_OFFSET                26
#define SMN_0x111402f0_LC_SAFE_EQ_SEARCH_WIDTH                 1
#define SMN_0x111402f0_LC_SAFE_EQ_SEARCH_MASK                  0x4000000
#define SMN_0x111402f0_LC_ESM_PLL_INIT_STATE_OFFSET            27
#define SMN_0x111402f0_LC_ESM_PLL_INIT_STATE_WIDTH             1
#define SMN_0x111402f0_LC_ESM_PLL_INIT_STATE_MASK              0x8000000
#define SMN_0x111402f0_LC_ESM_PLL_INIT_DONE_OFFSET             28
#define SMN_0x111402f0_LC_ESM_PLL_INIT_DONE_WIDTH              1
#define SMN_0x111402f0_LC_ESM_PLL_INIT_DONE_MASK               0x10000000
#define SMN_0x111402f0_LC_ESM_REDO_INIT_OFFSET                 29
#define SMN_0x111402f0_LC_ESM_REDO_INIT_WIDTH                  1
#define SMN_0x111402f0_LC_ESM_REDO_INIT_MASK                   0x20000000
#define SMN_0x111402f0_LC_MULTIPORT_ESM_OFFSET                 30
#define SMN_0x111402f0_LC_MULTIPORT_ESM_WIDTH                  1
#define SMN_0x111402f0_LC_MULTIPORT_ESM_MASK                   0x40000000
#define SMN_0x111402f0_LC_CONSECUTIVE_EIOS_RESET_EN_OFFSET     31
#define SMN_0x111402f0_LC_CONSECUTIVE_EIOS_RESET_EN_WIDTH      1
#define SMN_0x111402f0_LC_CONSECUTIVE_EIOS_RESET_EN_MASK       0x80000000L

/// PCIEPORT0F0_000002F0
typedef union {
  struct {
    UINT32                            LC_EXPECTED_TS2_CFG_COMPLETE:1 ; ///<
    UINT32                       LC_IGNORE_NON_CONTIG_SETS_IN_RCFG:1 ; ///<
    UINT32                           LC_ROBUST_TRAINING_BIT_CHK_EN:1 ; ///<
    UINT32                                 LC_RESET_TS_COUNT_ON_EI:1 ; ///<
    UINT32                                   LC_NBIF_ASPM_INPUT_EN:1 ; ///<
    UINT32                                   LC_EVER_IDLE_TO_RLOCK:1 ; ///<
    UINT32                            LC_RXEQEVAL_AFTER_TIMEOUT_EN:1 ; ///<
    UINT32                        LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1:1 ; ///<
    UINT32                          LC_SCHEDULED_RXEQEVAL_INTERVAL:8 ; ///<
    UINT32                              LC_SCHEDULED_RXEQEVAL_MODE:1 ; ///<
    UINT32                       LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN:1 ; ///<
    UINT32                                   LC_LINK_MANAGEMENT_EN:1 ; ///<
    UINT32                                             LC_FOM_TIME:2 ; ///<
    UINT32                                       LC_SAFE_EQ_SEARCH:1 ; ///<
    UINT32                                   LC_ESM_PLL_INIT_STATE:1 ; ///<
    UINT32                                    LC_ESM_PLL_INIT_DONE:1 ; ///<
    UINT32                                        LC_ESM_REDO_INIT:1 ; ///<
    UINT32                                        LC_MULTIPORT_ESM:1 ; ///<
    UINT32                            LC_CONSECUTIVE_EIOS_RESET_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x111402f0_STRUCT;

// Address
#define SMN_0x112402f0_ADDRESS                                 0x112402f0
#define SMN_0x112402f0                                         0x112402f0

// Type
#define SMN_0x112402f0_TYPE                                    TYPE_SMN

#define SMN_0x112402f0_LC_EXPECTED_TS2_CFG_COMPLETE_OFFSET     0
#define SMN_0x112402f0_LC_EXPECTED_TS2_CFG_COMPLETE_WIDTH      1
#define SMN_0x112402f0_LC_EXPECTED_TS2_CFG_COMPLETE_MASK       0x1
#define SMN_0x112402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_OFFSET 1
#define SMN_0x112402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_WIDTH  1
#define SMN_0x112402f0_LC_IGNORE_NON_CONTIG_SETS_IN_RCFG_MASK   0x2
#define SMN_0x112402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_OFFSET    2
#define SMN_0x112402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_WIDTH     1
#define SMN_0x112402f0_LC_ROBUST_TRAINING_BIT_CHK_EN_MASK      0x4
#define SMN_0x112402f0_LC_RESET_TS_COUNT_ON_EI_OFFSET          3
#define SMN_0x112402f0_LC_RESET_TS_COUNT_ON_EI_WIDTH           1
#define SMN_0x112402f0_LC_RESET_TS_COUNT_ON_EI_MASK            0x8
#define SMN_0x112402f0_LC_NBIF_ASPM_INPUT_EN_OFFSET            4
#define SMN_0x112402f0_LC_NBIF_ASPM_INPUT_EN_WIDTH             1
#define SMN_0x112402f0_LC_NBIF_ASPM_INPUT_EN_MASK              0x10
#define SMN_0x112402f0_LC_EVER_IDLE_TO_RLOCK_OFFSET            8
#define SMN_0x112402f0_LC_EVER_IDLE_TO_RLOCK_WIDTH             1
#define SMN_0x112402f0_LC_EVER_IDLE_TO_RLOCK_MASK              0x100
#define SMN_0x112402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_OFFSET     9
#define SMN_0x112402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_WIDTH      1
#define SMN_0x112402f0_LC_RXEQEVAL_AFTER_TIMEOUT_EN_MASK       0x200
#define SMN_0x112402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_OFFSET 12
#define SMN_0x112402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_WIDTH  1
#define SMN_0x112402f0_LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1_MASK   0x1000
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_OFFSET   13
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_WIDTH    8
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_INTERVAL_MASK     0x1fe000
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_MODE_OFFSET       21
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_MODE_WIDTH        1
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_MODE_MASK         0x200000
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_OFFSET 22
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_WIDTH  1
#define SMN_0x112402f0_LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN_MASK   0x400000
#define SMN_0x112402f0_LC_LINK_MANAGEMENT_EN_OFFSET            23
#define SMN_0x112402f0_LC_LINK_MANAGEMENT_EN_WIDTH             1
#define SMN_0x112402f0_LC_LINK_MANAGEMENT_EN_MASK              0x800000
#define SMN_0x112402f0_LC_FOM_TIME_OFFSET                      24
#define SMN_0x112402f0_LC_FOM_TIME_WIDTH                       2
#define SMN_0x112402f0_LC_FOM_TIME_MASK                        0x3000000
#define SMN_0x112402f0_LC_SAFE_EQ_SEARCH_OFFSET                26
#define SMN_0x112402f0_LC_SAFE_EQ_SEARCH_WIDTH                 1
#define SMN_0x112402f0_LC_SAFE_EQ_SEARCH_MASK                  0x4000000
#define SMN_0x112402f0_LC_ESM_PLL_INIT_STATE_OFFSET            27
#define SMN_0x112402f0_LC_ESM_PLL_INIT_STATE_WIDTH             1
#define SMN_0x112402f0_LC_ESM_PLL_INIT_STATE_MASK              0x8000000
#define SMN_0x112402f0_LC_ESM_PLL_INIT_DONE_OFFSET             28
#define SMN_0x112402f0_LC_ESM_PLL_INIT_DONE_WIDTH              1
#define SMN_0x112402f0_LC_ESM_PLL_INIT_DONE_MASK               0x10000000
#define SMN_0x112402f0_LC_ESM_REDO_INIT_OFFSET                 29
#define SMN_0x112402f0_LC_ESM_REDO_INIT_WIDTH                  1
#define SMN_0x112402f0_LC_ESM_REDO_INIT_MASK                   0x20000000
#define SMN_0x112402f0_LC_MULTIPORT_ESM_OFFSET                 30
#define SMN_0x112402f0_LC_MULTIPORT_ESM_WIDTH                  1
#define SMN_0x112402f0_LC_MULTIPORT_ESM_MASK                   0x40000000
#define SMN_0x112402f0_LC_CONSECUTIVE_EIOS_RESET_EN_OFFSET     31
#define SMN_0x112402f0_LC_CONSECUTIVE_EIOS_RESET_EN_WIDTH      1
#define SMN_0x112402f0_LC_CONSECUTIVE_EIOS_RESET_EN_MASK       0x80000000L

/// PCIEPORT1F0_000002F0
typedef union {
  struct {
    UINT32                            LC_EXPECTED_TS2_CFG_COMPLETE:1 ; ///<
    UINT32                       LC_IGNORE_NON_CONTIG_SETS_IN_RCFG:1 ; ///<
    UINT32                           LC_ROBUST_TRAINING_BIT_CHK_EN:1 ; ///<
    UINT32                                 LC_RESET_TS_COUNT_ON_EI:1 ; ///<
    UINT32                                   LC_NBIF_ASPM_INPUT_EN:1 ; ///<
    UINT32                                   LC_EVER_IDLE_TO_RLOCK:1 ; ///<
    UINT32                            LC_RXEQEVAL_AFTER_TIMEOUT_EN:1 ; ///<
    UINT32                        LC_ESM_WAIT_FOR_PLL_INIT_DONE_L1:1 ; ///<
    UINT32                          LC_SCHEDULED_RXEQEVAL_INTERVAL:8 ; ///<
    UINT32                              LC_SCHEDULED_RXEQEVAL_MODE:1 ; ///<
    UINT32                       LC_SCHEDULED_RXEQEVAL_UPCONFIG_EN:1 ; ///<
    UINT32                                   LC_LINK_MANAGEMENT_EN:1 ; ///<
    UINT32                                             LC_FOM_TIME:2 ; ///<
    UINT32                                       LC_SAFE_EQ_SEARCH:1 ; ///<
    UINT32                                   LC_ESM_PLL_INIT_STATE:1 ; ///<
    UINT32                                    LC_ESM_PLL_INIT_DONE:1 ; ///<
    UINT32                                        LC_ESM_REDO_INIT:1 ; ///<
    UINT32                                        LC_MULTIPORT_ESM:1 ; ///<
    UINT32                            LC_CONSECUTIVE_EIOS_RESET_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x112402f0_STRUCT;

// Address
#define SMN_0x11141280_ADDRESS                                 0x11141280
#define SMN_0x11141280                                         0x11141280

// Type
#define SMN_0x11141280_TYPE                                    TYPE_SMN

#define SMN_0x11141280_LC_DONT_ENTER_L23_IN_D0_OFFSET          1
#define SMN_0x11141280_LC_DONT_ENTER_L23_IN_D0_WIDTH           1
#define SMN_0x11141280_LC_DONT_ENTER_L23_IN_D0_MASK            0x2
#define SMN_0x11141280_LC_RESET_L_IDLE_COUNT_EN_OFFSET         2
#define SMN_0x11141280_LC_RESET_L_IDLE_COUNT_EN_WIDTH          1
#define SMN_0x11141280_LC_RESET_L_IDLE_COUNT_EN_MASK           0x4
#define SMN_0x11141280_LC_RESET_LINK_OFFSET                    3
#define SMN_0x11141280_LC_RESET_LINK_WIDTH                     1
#define SMN_0x11141280_LC_RESET_LINK_MASK                      0x8
#define SMN_0x11141280_LC_16X_CLEAR_TX_PIPE_OFFSET             4
#define SMN_0x11141280_LC_16X_CLEAR_TX_PIPE_WIDTH              4
#define SMN_0x11141280_LC_16X_CLEAR_TX_PIPE_MASK               0xf0
#define SMN_0x11141280_LC_L0S_INACTIVITY_OFFSET                8
#define SMN_0x11141280_LC_L0S_INACTIVITY_WIDTH                 4
#define SMN_0x11141280_LC_L0S_INACTIVITY_MASK                  0xf00
#define SMN_0x11141280_LC_L1_INACTIVITY_OFFSET                 12
#define SMN_0x11141280_LC_L1_INACTIVITY_WIDTH                  4
#define SMN_0x11141280_LC_L1_INACTIVITY_MASK                   0xf000
#define SMN_0x11141280_LC_PMI_TO_L1_DIS_OFFSET                 16
#define SMN_0x11141280_LC_PMI_TO_L1_DIS_WIDTH                  1
#define SMN_0x11141280_LC_PMI_TO_L1_DIS_MASK                   0x10000
#define SMN_0x11141280_LC_INC_N_FTS_EN_OFFSET                  17
#define SMN_0x11141280_LC_INC_N_FTS_EN_WIDTH                   1
#define SMN_0x11141280_LC_INC_N_FTS_EN_MASK                    0x20000
#define SMN_0x11141280_LC_LOOK_FOR_IDLE_IN_L1L23_OFFSET        18
#define SMN_0x11141280_LC_LOOK_FOR_IDLE_IN_L1L23_WIDTH         2
#define SMN_0x11141280_LC_LOOK_FOR_IDLE_IN_L1L23_MASK          0xc0000
#define SMN_0x11141280_LC_FACTOR_IN_EXT_SYNC_OFFSET            20
#define SMN_0x11141280_LC_FACTOR_IN_EXT_SYNC_WIDTH             1
#define SMN_0x11141280_LC_FACTOR_IN_EXT_SYNC_MASK              0x100000
#define SMN_0x11141280_LC_WAIT_FOR_PM_ACK_DIS_OFFSET           21
#define SMN_0x11141280_LC_WAIT_FOR_PM_ACK_DIS_WIDTH            1
#define SMN_0x11141280_LC_WAIT_FOR_PM_ACK_DIS_MASK             0x200000
#define SMN_0x11141280_LC_WAKE_FROM_L23_OFFSET                 22
#define SMN_0x11141280_LC_WAKE_FROM_L23_WIDTH                  1
#define SMN_0x11141280_LC_WAKE_FROM_L23_MASK                   0x400000
#define SMN_0x11141280_LC_L1_IMMEDIATE_ACK_OFFSET              23
#define SMN_0x11141280_LC_L1_IMMEDIATE_ACK_WIDTH               1
#define SMN_0x11141280_LC_L1_IMMEDIATE_ACK_MASK                0x800000
#define SMN_0x11141280_LC_ASPM_TO_L1_DIS_OFFSET                24
#define SMN_0x11141280_LC_ASPM_TO_L1_DIS_WIDTH                 1
#define SMN_0x11141280_LC_ASPM_TO_L1_DIS_MASK                  0x1000000
#define SMN_0x11141280_LC_DELAY_COUNT_OFFSET                   25
#define SMN_0x11141280_LC_DELAY_COUNT_WIDTH                    2
#define SMN_0x11141280_LC_DELAY_COUNT_MASK                     0x6000000
#define SMN_0x11141280_LC_DELAY_L0S_EXIT_OFFSET                27
#define SMN_0x11141280_LC_DELAY_L0S_EXIT_WIDTH                 1
#define SMN_0x11141280_LC_DELAY_L0S_EXIT_MASK                  0x8000000
#define SMN_0x11141280_LC_DELAY_L1_EXIT_OFFSET                 28
#define SMN_0x11141280_LC_DELAY_L1_EXIT_WIDTH                  1
#define SMN_0x11141280_LC_DELAY_L1_EXIT_MASK                   0x10000000
#define SMN_0x11141280_LC_EXTEND_WAIT_FOR_EL_IDLE_OFFSET       29
#define SMN_0x11141280_LC_EXTEND_WAIT_FOR_EL_IDLE_WIDTH        1
#define SMN_0x11141280_LC_EXTEND_WAIT_FOR_EL_IDLE_MASK         0x20000000
#define SMN_0x11141280_LC_ESCAPE_L1L23_EN_OFFSET               30
#define SMN_0x11141280_LC_ESCAPE_L1L23_EN_WIDTH                1
#define SMN_0x11141280_LC_ESCAPE_L1L23_EN_MASK                 0x40000000
#define SMN_0x11141280_LC_GATE_RCVR_IDLE_OFFSET                31
#define SMN_0x11141280_LC_GATE_RCVR_IDLE_WIDTH                 1
#define SMN_0x11141280_LC_GATE_RCVR_IDLE_MASK                  0x80000000L

/// PCIEPORT0F1_00000280
typedef union {
  struct {
    UINT32                                 LC_DONT_ENTER_L23_IN_D0:1 ; ///<
    UINT32                                LC_RESET_L_IDLE_COUNT_EN:1 ; ///<
    UINT32                                           LC_RESET_LINK:1 ; ///<
    UINT32                                    LC_16X_CLEAR_TX_PIPE:4 ; ///<
    UINT32                                       LC_L0S_INACTIVITY:4 ; ///<
    UINT32                                        LC_L1_INACTIVITY:4 ; ///<
    UINT32                                        LC_PMI_TO_L1_DIS:1 ; ///<
    UINT32                                         LC_INC_N_FTS_EN:1 ; ///<
    UINT32                               LC_LOOK_FOR_IDLE_IN_L1L23:2 ; ///<
    UINT32                                   LC_FACTOR_IN_EXT_SYNC:1 ; ///<
    UINT32                                  LC_WAIT_FOR_PM_ACK_DIS:1 ; ///<
    UINT32                                        LC_WAKE_FROM_L23:1 ; ///<
    UINT32                                     LC_L1_IMMEDIATE_ACK:1 ; ///<
    UINT32                                       LC_ASPM_TO_L1_DIS:1 ; ///<
    UINT32                                          LC_DELAY_COUNT:2 ; ///<
    UINT32                                       LC_DELAY_L0S_EXIT:1 ; ///<
    UINT32                                        LC_DELAY_L1_EXIT:1 ; ///<
    UINT32                              LC_EXTEND_WAIT_FOR_EL_IDLE:1 ; ///<
    UINT32                                      LC_ESCAPE_L1L23_EN:1 ; ///<
    UINT32                                       LC_GATE_RCVR_IDLE:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x11141280_STRUCT;
// svd_group: NBIO_IOHC_aliasSMN
// Address
#define NB_IOC_DEBUG_ADDRESS                                   0x13B10004

// Type
#define NB_IOC_DEBUG_TYPE                                      TYPE_NBMISC

#define NBMISC_0004_NB_IOC_DEBUG_RW_OFFSET                     0
#define NBMISC_0004_NB_IOC_DEBUG_RW_WIDTH                      16
#define NBMISC_0004_NB_IOC_DEBUG_RW_MASK                       0xffff
#define NBMISC_0004_IOC_MultiReqVldErr_OFFSET                  16
#define NBMISC_0004_IOC_MultiReqVldErr_WIDTH                   1
#define NBMISC_0004_IOC_MultiReqVldErr_MASK                    0x10000
#define NBMISC_0004_IOC_MemMapCfgErr_OFFSET                    17
#define NBMISC_0004_IOC_MemMapCfgErr_WIDTH                     1
#define NBMISC_0004_IOC_MemMapCfgErr_MASK                      0x20000
#define NBMISC_0004_NB_IOC_DEBUG_RO_OFFSET                     18
#define NBMISC_0004_NB_IOC_DEBUG_RO_WIDTH                      14
#define NBMISC_0004_NB_IOC_DEBUG_RO_MASK                       0xfffc0000L

/// NBMISC_0004
typedef union {
  struct {
    UINT32                                         NB_IOC_DEBUG_RW:16; ///<
    UINT32                                      IOC_MultiReqVldErr:1 ; ///<
    UINT32                                        IOC_MemMapCfgErr:1 ; ///<
    UINT32                                         NB_IOC_DEBUG_RO:14; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0004_STRUCT;

// Address
#define SMN_0x13B10030_ADDRESS                                 0x13B10030
#define SMN_0x13B10030                                         0x13B10030

// Type
#define SMN_0x13B10030_TYPE                                    TYPE_SMN

#define SMN_0x13B10030_DlDownResetEn_OFFSET                    11
#define SMN_0x13B10030_DlDownResetEn_WIDTH                     1
#define SMN_0x13B10030_DlDownResetEn_MASK                      0x800

/// IOHCMISC_00000030
typedef union {
  struct {
    UINT32                                          Reserved_10_0:11 ; ///<
    UINT32                                           DlDownResetEn:1 ; ///<
    UINT32                                         Reserved_31_12:20 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B10030_STRUCT;


// Register Name NB_PCI_CTRL

// Address
#define NB_PCI_CTRL_ADDRESS                                           0x13b0004C

// Type
#define NB_PCI_CTRL_TYPE                                              TYPE_SMN

#define NB_PCI_CTRL_Reserved_3_0_OFFSET                               0
#define NB_PCI_CTRL_Reserved_3_0_WIDTH                                4
#define NB_PCI_CTRL_Reserved_3_0_MASK                                 0xf
#define NB_PCI_CTRL_PMEDis_OFFSET                                     4
#define NB_PCI_CTRL_PMEDis_WIDTH                                      1
#define NB_PCI_CTRL_PMEDis_MASK                                       0x10
#define NB_PCI_CTRL_SErrDis_OFFSET                                    5
#define NB_PCI_CTRL_SErrDis_WIDTH                                     1
#define NB_PCI_CTRL_SErrDis_MASK                                      0x20
#define NB_PCI_CTRL_Reserved_22_6_OFFSET                              6
#define NB_PCI_CTRL_Reserved_22_6_WIDTH                               17
#define NB_PCI_CTRL_Reserved_22_6_MASK                                0x7fffc0
#define NB_PCI_CTRL_MMIOEnable_OFFSET                                 23
#define NB_PCI_CTRL_MMIOEnable_WIDTH                                  1
#define NB_PCI_CTRL_MMIOEnable_MASK                                   0x800000
#define NB_PCI_CTRL_Reserved_25_24_OFFSET                             24
#define NB_PCI_CTRL_Reserved_25_24_WIDTH                              2
#define NB_PCI_CTRL_Reserved_25_24_MASK                               0x3000000
#define NB_PCI_CTRL_HPDis_OFFSET                                      26
#define NB_PCI_CTRL_HPDis_WIDTH                                       1
#define NB_PCI_CTRL_HPDis_MASK                                        0x4000000
#define NB_PCI_CTRL_Reserved_31_27_OFFSET                             27
#define NB_PCI_CTRL_Reserved_31_27_WIDTH                              5
#define NB_PCI_CTRL_Reserved_31_27_MASK                               0xf8000000L

/// NB_PCI_CTRL
typedef union {
  struct {
    UINT32                                            Reserved_3_0:4 ; ///<
    UINT32                                                  PMEDis:1 ; ///<
    UINT32                                                 SErrDis:1 ; ///<
    UINT32                                           Reserved_22_6:17; ///<
    UINT32                                              MMIOEnable:1 ; ///<
    UINT32                                          Reserved_25_24:2 ; ///<
    UINT32                                                   HPDis:1 ; ///<
    UINT32                                          Reserved_31_27:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NB_PCI_CTRL_STRUCT;

// Address
#define SMN_0x13B100C0_ADDRESS                                 0x13B100C0
#define SMN_0x13B100C0                                         0x13B100C0

// Type
#define SMN_0x13B100C0_TYPE                                    TYPE_SMN

#define SMN_0x13B100C0_DevFnMap_OFFSET                         0
#define SMN_0x13B100C0_DevFnMap_WIDTH                          8
#define SMN_0x13B100C0_DevFnMap_MASK                           0xff

/// IOHCMISC_000000C0
typedef union {
  struct {
    UINT32                                                DevFnMap:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B100C0_STRUCT;


// Register Name PCIE_VDM_NODE_CTRL4

// Address
#define PCIE_VDM_NODE0_CTRL4_ADDRESS                          0x13b10190
#define PCIE_VDM_NODE1_CTRL4_ADDRESS                          0x13b101A4
#define PCIE_VDM_NODE2_CTRL4_ADDRESS                          0x13b101B8
#define PCIE_VDM_NODE3_CTRL4_ADDRESS                          0x13b101CC
#define PCIE_VDM_NODE4_CTRL4_ADDRESS                          0x13b101E0
#define PCIE_VDM_NODE5_CTRL4_ADDRESS                          0x13b101F4
#define PCIE_VDM_NODE6_CTRL4_ADDRESS                          0x13b10208
#define PCIE_VDM_NODE7_CTRL4_ADDRESS                          0x13b1021C

// Type
#define PCIE_VDM_NODE_CTRL4_TYPE                              TYPE_SMN

#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_BASE_OFFSET             0
#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_BASE_WIDTH              8
#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_BASE_MASK               0xff
#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_LIMIT_OFFSET            8
#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_LIMIT_WIDTH             8
#define PCIE_VDM_NODE_CTRL4_BUS_RANGE_LIMIT_MASK              0xff00
#define PCIE_VDM_NODE_CTRL4_Reserved_30_16_OFFSET             16
#define PCIE_VDM_NODE_CTRL4_Reserved_30_16_WIDTH              15
#define PCIE_VDM_NODE_CTRL4_Reserved_30_16_MASK               0x7fff0000
#define PCIE_VDM_NODE_CTRL4_NODE_PRESENT_OFFSET               31
#define PCIE_VDM_NODE_CTRL4_NODE_PRESENT_WIDTH                1
#define PCIE_VDM_NODE_CTRL4_NODE_PRESENT_MASK                 0x80000000L

/// PCIE_VDM_NODE_CTRL4
typedef union {
  struct {
    UINT32                                          BUS_RANGE_BASE:8 ; ///<
    UINT32                                         BUS_RANGE_LIMIT:8 ; ///<
    UINT32                                          Reserved_30_16:15; ///<
    UINT32                                            NODE_PRESENT:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_VDM_NODE_CTRL4_STRUCT;


// Register Name PCIE_CNTL

// Address
#define PCIE0_CNTL_ADDRESS                                           0x11180040
#define PCIE1_CNTL_ADDRESS                                           0x11280040

// Type
#define PCIE_CNTL_TYPE                                              TYPE_SMN

#define PCIE_CNTL_HWINIT_WR_LOCK_OFFSET                             0
#define PCIE_CNTL_HWINIT_WR_LOCK_WIDTH                              1
#define PCIE_CNTL_HWINIT_WR_LOCK_MASK                               0x1
#define PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_OFFSET                      1
#define PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_WIDTH                       3
#define PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_MASK                        0xe
#define PCIE_CNTL_Reserved_6_4_OFFSET                               4
#define PCIE_CNTL_Reserved_6_4_WIDTH                                3
#define PCIE_CNTL_Reserved_6_4_MASK                                 0x70
#define PCIE_CNTL_UR_ERR_REPORT_DIS_OFFSET                          7
#define PCIE_CNTL_UR_ERR_REPORT_DIS_WIDTH                           1
#define PCIE_CNTL_UR_ERR_REPORT_DIS_MASK                            0x80
#define PCIE_CNTL_PCIE_MALFORM_ATOMIC_OPS_OFFSET                    8
#define PCIE_CNTL_PCIE_MALFORM_ATOMIC_OPS_WIDTH                     1
#define PCIE_CNTL_PCIE_MALFORM_ATOMIC_OPS_MASK                      0x100
#define PCIE_CNTL_PCIE_HT_NP_MEM_WRITE_OFFSET                       9
#define PCIE_CNTL_PCIE_HT_NP_MEM_WRITE_WIDTH                        1
#define PCIE_CNTL_PCIE_HT_NP_MEM_WRITE_MASK                         0x200
#define PCIE_CNTL_RX_SB_ADJ_PAYLOAD_SIZE_OFFSET                     10
#define PCIE_CNTL_RX_SB_ADJ_PAYLOAD_SIZE_WIDTH                      3
#define PCIE_CNTL_RX_SB_ADJ_PAYLOAD_SIZE_MASK                       0x1c00
#define PCIE_CNTL_Reserved_14_13_OFFSET                             13
#define PCIE_CNTL_Reserved_14_13_WIDTH                              2
#define PCIE_CNTL_Reserved_14_13_MASK                               0x6000
#define PCIE_CNTL_RX_RCB_ATS_UC_DIS_OFFSET                          15
#define PCIE_CNTL_RX_RCB_ATS_UC_DIS_WIDTH                           1
#define PCIE_CNTL_RX_RCB_ATS_UC_DIS_MASK                            0x8000
#define PCIE_CNTL_RX_RCB_REORDER_EN_OFFSET                          16
#define PCIE_CNTL_RX_RCB_REORDER_EN_WIDTH                           1
#define PCIE_CNTL_RX_RCB_REORDER_EN_MASK                            0x10000
#define PCIE_CNTL_RX_RCB_INVALID_SIZE_DIS_OFFSET                    17
#define PCIE_CNTL_RX_RCB_INVALID_SIZE_DIS_WIDTH                     1
#define PCIE_CNTL_RX_RCB_INVALID_SIZE_DIS_MASK                      0x20000
#define PCIE_CNTL_RX_RCB_UNEXP_CPL_DIS_OFFSET                       18
#define PCIE_CNTL_RX_RCB_UNEXP_CPL_DIS_WIDTH                        1
#define PCIE_CNTL_RX_RCB_UNEXP_CPL_DIS_MASK                         0x40000
#define PCIE_CNTL_RX_RCB_CPL_TIMEOUT_TEST_MODE_OFFSET               19
#define PCIE_CNTL_RX_RCB_CPL_TIMEOUT_TEST_MODE_WIDTH                1
#define PCIE_CNTL_RX_RCB_CPL_TIMEOUT_TEST_MODE_MASK                 0x80000
#define PCIE_CNTL_RX_RCB_WRONG_PREFIX_DIS_OFFSET                    20
#define PCIE_CNTL_RX_RCB_WRONG_PREFIX_DIS_WIDTH                     1
#define PCIE_CNTL_RX_RCB_WRONG_PREFIX_DIS_MASK                      0x100000
#define PCIE_CNTL_RX_RCB_WRONG_ATTR_DIS_OFFSET                      21
#define PCIE_CNTL_RX_RCB_WRONG_ATTR_DIS_WIDTH                       1
#define PCIE_CNTL_RX_RCB_WRONG_ATTR_DIS_MASK                        0x200000
#define PCIE_CNTL_RX_RCB_WRONG_FUNCNUM_DIS_OFFSET                   22
#define PCIE_CNTL_RX_RCB_WRONG_FUNCNUM_DIS_WIDTH                    1
#define PCIE_CNTL_RX_RCB_WRONG_FUNCNUM_DIS_MASK                     0x400000
#define PCIE_CNTL_RX_ATS_TRAN_CPL_SPLIT_DIS_OFFSET                  23
#define PCIE_CNTL_RX_ATS_TRAN_CPL_SPLIT_DIS_WIDTH                   1
#define PCIE_CNTL_RX_ATS_TRAN_CPL_SPLIT_DIS_MASK                    0x800000
#define PCIE_CNTL_TX_CPL_DEBUG_OFFSET                               24
#define PCIE_CNTL_TX_CPL_DEBUG_WIDTH                                6
#define PCIE_CNTL_TX_CPL_DEBUG_MASK                                 0x3f000000
#define PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_OFFSET                       30
#define PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_WIDTH                        1
#define PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_MASK                         0x40000000
#define PCIE_CNTL_RX_CPL_POSTED_REQ_ORD_EN_OFFSET                   31
#define PCIE_CNTL_RX_CPL_POSTED_REQ_ORD_EN_WIDTH                    1
#define PCIE_CNTL_RX_CPL_POSTED_REQ_ORD_EN_MASK                     0x80000000L

/// PCIE_CNTL
typedef union {
  struct {
    UINT32                                          HWINIT_WR_LOCK:1 ; ///<
    UINT32                                   LC_HOT_PLUG_DELAY_SEL:3 ; ///<
    UINT32                                            Reserved_6_4:3 ; ///<
    UINT32                                       UR_ERR_REPORT_DIS:1 ; ///<
    UINT32                                 PCIE_MALFORM_ATOMIC_OPS:1 ; ///<
    UINT32                                    PCIE_HT_NP_MEM_WRITE:1 ; ///<
    UINT32                                  RX_SB_ADJ_PAYLOAD_SIZE:3 ; ///<
    UINT32                                          Reserved_14_13:2 ; ///<
    UINT32                                       RX_RCB_ATS_UC_DIS:1 ; ///<
    UINT32                                       RX_RCB_REORDER_EN:1 ; ///<
    UINT32                                 RX_RCB_INVALID_SIZE_DIS:1 ; ///<
    UINT32                                    RX_RCB_UNEXP_CPL_DIS:1 ; ///<
    UINT32                            RX_RCB_CPL_TIMEOUT_TEST_MODE:1 ; ///<
    UINT32                                 RX_RCB_WRONG_PREFIX_DIS:1 ; ///<
    UINT32                                   RX_RCB_WRONG_ATTR_DIS:1 ; ///<
    UINT32                                RX_RCB_WRONG_FUNCNUM_DIS:1 ; ///<
    UINT32                               RX_ATS_TRAN_CPL_SPLIT_DIS:1 ; ///<
    UINT32                                            TX_CPL_DEBUG:6 ; ///<
    UINT32                                    RX_IGNORE_LTR_MSG_UR:1 ; ///<
    UINT32                                RX_CPL_POSTED_REQ_ORD_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_CNTL_STRUCT;

// Register Name PCIE_CNTL2

// Address
#define PCIE0_CNTL2_ADDRESS                                          0x11180070
#define PCIE1_CNTL2_ADDRESS                                          0x11280070

// Type
#define PCIE_CNTL2_TYPE                                              TYPE_SMN

#define PCIE_CNTL2_TX_ARB_ROUND_ROBIN_EN_OFFSET                      0
#define PCIE_CNTL2_TX_ARB_ROUND_ROBIN_EN_WIDTH                       1
#define PCIE_CNTL2_TX_ARB_ROUND_ROBIN_EN_MASK                        0x1
#define PCIE_CNTL2_TX_ARB_SLV_LIMIT_OFFSET                           1
#define PCIE_CNTL2_TX_ARB_SLV_LIMIT_WIDTH                            5
#define PCIE_CNTL2_TX_ARB_SLV_LIMIT_MASK                             0x3e
#define PCIE_CNTL2_TX_ARB_MST_LIMIT_OFFSET                           6
#define PCIE_CNTL2_TX_ARB_MST_LIMIT_WIDTH                            5
#define PCIE_CNTL2_TX_ARB_MST_LIMIT_MASK                             0x7c0
#define PCIE_CNTL2_TX_BLOCK_TLP_ON_PM_DIS_OFFSET                     11
#define PCIE_CNTL2_TX_BLOCK_TLP_ON_PM_DIS_WIDTH                      1
#define PCIE_CNTL2_TX_BLOCK_TLP_ON_PM_DIS_MASK                       0x800
#define PCIE_CNTL2_TX_NP_MEM_WRITE_SWP_ENCODING_OFFSET               12
#define PCIE_CNTL2_TX_NP_MEM_WRITE_SWP_ENCODING_WIDTH                1
#define PCIE_CNTL2_TX_NP_MEM_WRITE_SWP_ENCODING_MASK                 0x1000
#define PCIE_CNTL2_TX_ATOMIC_OPS_DISABLE_OFFSET                      13
#define PCIE_CNTL2_TX_ATOMIC_OPS_DISABLE_WIDTH                       1
#define PCIE_CNTL2_TX_ATOMIC_OPS_DISABLE_MASK                        0x2000
#define PCIE_CNTL2_TX_ATOMIC_ORDERING_DIS_OFFSET                     14
#define PCIE_CNTL2_TX_ATOMIC_ORDERING_DIS_WIDTH                      1
#define PCIE_CNTL2_TX_ATOMIC_ORDERING_DIS_MASK                       0x4000
#define PCIE_CNTL2_Reserved_15_15_OFFSET                             15
#define PCIE_CNTL2_Reserved_15_15_WIDTH                              1
#define PCIE_CNTL2_Reserved_15_15_MASK                               0x8000
#define PCIE_CNTL2_SLV_MEM_LS_EN_OFFSET                              16
#define PCIE_CNTL2_SLV_MEM_LS_EN_WIDTH                               1
#define PCIE_CNTL2_SLV_MEM_LS_EN_MASK                                0x10000
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_LS_EN_OFFSET                   17
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_LS_EN_WIDTH                    1
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_LS_EN_MASK                     0x20000
#define PCIE_CNTL2_MST_MEM_LS_EN_OFFSET                              18
#define PCIE_CNTL2_MST_MEM_LS_EN_WIDTH                               1
#define PCIE_CNTL2_MST_MEM_LS_EN_MASK                                0x40000
#define PCIE_CNTL2_REPLAY_MEM_LS_EN_OFFSET                           19
#define PCIE_CNTL2_REPLAY_MEM_LS_EN_WIDTH                            1
#define PCIE_CNTL2_REPLAY_MEM_LS_EN_MASK                             0x80000
#define PCIE_CNTL2_SLV_MEM_SD_EN_OFFSET                              20
#define PCIE_CNTL2_SLV_MEM_SD_EN_WIDTH                               1
#define PCIE_CNTL2_SLV_MEM_SD_EN_MASK                                0x100000
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_SD_EN_OFFSET                   21
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_SD_EN_WIDTH                    1
#define PCIE_CNTL2_SLV_MEM_AGGRESSIVE_SD_EN_MASK                     0x200000
#define PCIE_CNTL2_MST_MEM_SD_EN_OFFSET                              22
#define PCIE_CNTL2_MST_MEM_SD_EN_WIDTH                               1
#define PCIE_CNTL2_MST_MEM_SD_EN_MASK                                0x400000
#define PCIE_CNTL2_REPLAY_MEM_SD_EN_OFFSET                           23
#define PCIE_CNTL2_REPLAY_MEM_SD_EN_WIDTH                            1
#define PCIE_CNTL2_REPLAY_MEM_SD_EN_MASK                             0x800000
#define PCIE_CNTL2_RX_NP_MEM_WRITE_ENCODING_OFFSET                   24
#define PCIE_CNTL2_RX_NP_MEM_WRITE_ENCODING_WIDTH                    5
#define PCIE_CNTL2_RX_NP_MEM_WRITE_ENCODING_MASK                     0x1f000000
#define PCIE_CNTL2_SLV_MEM_DS_EN_OFFSET                              29
#define PCIE_CNTL2_SLV_MEM_DS_EN_WIDTH                               1
#define PCIE_CNTL2_SLV_MEM_DS_EN_MASK                                0x20000000
#define PCIE_CNTL2_MST_MEM_DS_EN_OFFSET                              30
#define PCIE_CNTL2_MST_MEM_DS_EN_WIDTH                               1
#define PCIE_CNTL2_MST_MEM_DS_EN_MASK                                0x40000000
#define PCIE_CNTL2_REPLAY_MEM_DS_EN_OFFSET                           31
#define PCIE_CNTL2_REPLAY_MEM_DS_EN_WIDTH                            1
#define PCIE_CNTL2_REPLAY_MEM_DS_EN_MASK                             0x80000000L

/// PCIECORE0_00000070
typedef union {
  struct {
    UINT32                                   TX_ARB_ROUND_ROBIN_EN:1 ; ///<
    UINT32                                        TX_ARB_SLV_LIMIT:5 ; ///<
    UINT32                                        TX_ARB_MST_LIMIT:5 ; ///<
    UINT32                                  TX_BLOCK_TLP_ON_PM_DIS:1 ; ///<
    UINT32                            TX_NP_MEM_WRITE_SWP_ENCODING:1 ; ///<
    UINT32                                   TX_ATOMIC_OPS_DISABLE:1 ; ///<
    UINT32                                  TX_ATOMIC_ORDERING_DIS:1 ; ///<
    UINT32                                          Reserved_15_15:1 ; ///<
    UINT32                                           SLV_MEM_LS_EN:1 ; ///<
    UINT32                                SLV_MEM_AGGRESSIVE_LS_EN:1 ; ///<
    UINT32                                           MST_MEM_LS_EN:1 ; ///<
    UINT32                                        REPLAY_MEM_LS_EN:1 ; ///<
    UINT32                                           SLV_MEM_SD_EN:1 ; ///<
    UINT32                                SLV_MEM_AGGRESSIVE_SD_EN:1 ; ///<
    UINT32                                           MST_MEM_SD_EN:1 ; ///<
    UINT32                                        REPLAY_MEM_SD_EN:1 ; ///<
    UINT32                                RX_NP_MEM_WRITE_ENCODING:5 ; ///<
    UINT32                                           SLV_MEM_DS_EN:1 ; ///<
    UINT32                                           MST_MEM_DS_EN:1 ; ///<
    UINT32                                        REPLAY_MEM_DS_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_CNTL2_STRUCT;

// Register Name PCIE_P_CNTL

// Address
#define PCIE0_P_CNTL_ADDRESS                                          0x11180100
#define PCIE1_P_CNTL_ADDRESS                                          0x11280100

// Type
#define PCIE_P_CNTL_TYPE                                              TYPE_SMN

#define PCIE_P_CNTL_P_PWRDN_EN_OFFSET                                 0
#define PCIE_P_CNTL_P_PWRDN_EN_WIDTH                                  1
#define PCIE_P_CNTL_P_PWRDN_EN_MASK                                   0x1
#define PCIE_P_CNTL_P_SYMALIGN_MODE_OFFSET                            1
#define PCIE_P_CNTL_P_SYMALIGN_MODE_WIDTH                             1
#define PCIE_P_CNTL_P_SYMALIGN_MODE_MASK                              0x2
#define PCIE_P_CNTL_P_SYMALIGN_HW_DEBUG_OFFSET                        2
#define PCIE_P_CNTL_P_SYMALIGN_HW_DEBUG_WIDTH                         1
#define PCIE_P_CNTL_P_SYMALIGN_HW_DEBUG_MASK                          0x4
#define PCIE_P_CNTL_P_ELASTDESKEW_HW_DEBUG_OFFSET                     3
#define PCIE_P_CNTL_P_ELASTDESKEW_HW_DEBUG_WIDTH                      1
#define PCIE_P_CNTL_P_ELASTDESKEW_HW_DEBUG_MASK                       0x8
#define PCIE_P_CNTL_P_IGNORE_CRC_ERR_OFFSET                           4
#define PCIE_P_CNTL_P_IGNORE_CRC_ERR_WIDTH                            1
#define PCIE_P_CNTL_P_IGNORE_CRC_ERR_MASK                             0x10
#define PCIE_P_CNTL_P_IGNORE_LEN_ERR_OFFSET                           5
#define PCIE_P_CNTL_P_IGNORE_LEN_ERR_WIDTH                            1
#define PCIE_P_CNTL_P_IGNORE_LEN_ERR_MASK                             0x20
#define PCIE_P_CNTL_P_IGNORE_EDB_ERR_OFFSET                           6
#define PCIE_P_CNTL_P_IGNORE_EDB_ERR_WIDTH                            1
#define PCIE_P_CNTL_P_IGNORE_EDB_ERR_MASK                             0x40
#define PCIE_P_CNTL_P_IGNORE_IDL_ERR_OFFSET                           7
#define PCIE_P_CNTL_P_IGNORE_IDL_ERR_WIDTH                            1
#define PCIE_P_CNTL_P_IGNORE_IDL_ERR_MASK                             0x80
#define PCIE_P_CNTL_P_IGNORE_TOK_ERR_OFFSET                           8
#define PCIE_P_CNTL_P_IGNORE_TOK_ERR_WIDTH                            1
#define PCIE_P_CNTL_P_IGNORE_TOK_ERR_MASK                             0x100
#define PCIE_P_CNTL_Reserved_11_9_OFFSET                              9
#define PCIE_P_CNTL_Reserved_11_9_WIDTH                               3
#define PCIE_P_CNTL_Reserved_11_9_MASK                                0xe00
#define PCIE_P_CNTL_P_BLK_LOCK_MODE_OFFSET                            12
#define PCIE_P_CNTL_P_BLK_LOCK_MODE_WIDTH                             1
#define PCIE_P_CNTL_P_BLK_LOCK_MODE_MASK                              0x1000
#define PCIE_P_CNTL_P_ALWAYS_USE_FAST_TXCLK_OFFSET                    13
#define PCIE_P_CNTL_P_ALWAYS_USE_FAST_TXCLK_WIDTH                     1
#define PCIE_P_CNTL_P_ALWAYS_USE_FAST_TXCLK_MASK                      0x2000
#define PCIE_P_CNTL_P_ELEC_IDLE_MODE_OFFSET                           14
#define PCIE_P_CNTL_P_ELEC_IDLE_MODE_WIDTH                            2
#define PCIE_P_CNTL_P_ELEC_IDLE_MODE_MASK                             0xc000
#define PCIE_P_CNTL_DLP_IGNORE_IN_L1_EN_OFFSET                        16
#define PCIE_P_CNTL_DLP_IGNORE_IN_L1_EN_WIDTH                         1
#define PCIE_P_CNTL_DLP_IGNORE_IN_L1_EN_MASK                          0x10000
#define PCIE_P_CNTL_ASSERT_DVALID_ON_EI_TRANS_OFFSET                  17
#define PCIE_P_CNTL_ASSERT_DVALID_ON_EI_TRANS_WIDTH                   1
#define PCIE_P_CNTL_ASSERT_DVALID_ON_EI_TRANS_MASK                    0x20000
#define PCIE_P_CNTL_Reserved_31_18_OFFSET                             18
#define PCIE_P_CNTL_Reserved_31_18_WIDTH                              14
#define PCIE_P_CNTL_Reserved_31_18_MASK                               0xfffc0000L

/// PCIECORE0_00000100
typedef union {
  struct {
    UINT32                                              P_PWRDN_EN:1 ; ///<
    UINT32                                         P_SYMALIGN_MODE:1 ; ///<
    UINT32                                     P_SYMALIGN_HW_DEBUG:1 ; ///<
    UINT32                                  P_ELASTDESKEW_HW_DEBUG:1 ; ///<
    UINT32                                        P_IGNORE_CRC_ERR:1 ; ///<
    UINT32                                        P_IGNORE_LEN_ERR:1 ; ///<
    UINT32                                        P_IGNORE_EDB_ERR:1 ; ///<
    UINT32                                        P_IGNORE_IDL_ERR:1 ; ///<
    UINT32                                        P_IGNORE_TOK_ERR:1 ; ///<
    UINT32                                           Reserved_11_9:3 ; ///<
    UINT32                                         P_BLK_LOCK_MODE:1 ; ///<
    UINT32                                 P_ALWAYS_USE_FAST_TXCLK:1 ; ///<
    UINT32                                        P_ELEC_IDLE_MODE:2 ; ///<
    UINT32                                     DLP_IGNORE_IN_L1_EN:1 ; ///<
    UINT32                               ASSERT_DVALID_ON_EI_TRANS:1 ; ///<
    UINT32                                          Reserved_31_18:14; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_P_CNTL_STRUCT;

// Address
#define PCIE0_SWRST_CONTROL_6_ADDRESS                          0x11180428

// Type
#define PCIE0_SWRST_CONTROL_6_TYPE                             TYPE_SMN

#define PCIE11180428_HOLD_TRAINING_A_OFFSET                     0
#define PCIE11180428_HOLD_TRAINING_A_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_A_MASK                       0x1
#define PCIE11180428_HOLD_TRAINING_B_OFFSET                     1
#define PCIE11180428_HOLD_TRAINING_B_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_B_MASK                       0x2
#define PCIE11180428_HOLD_TRAINING_C_OFFSET                     2
#define PCIE11180428_HOLD_TRAINING_C_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_C_MASK                       0x4
#define PCIE11180428_HOLD_TRAINING_D_OFFSET                     3
#define PCIE11180428_HOLD_TRAINING_D_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_D_MASK                       0x8
#define PCIE11180428_HOLD_TRAINING_E_OFFSET                     4
#define PCIE11180428_HOLD_TRAINING_E_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_E_MASK                       0x10
#define PCIE11180428_HOLD_TRAINING_F_OFFSET                     5
#define PCIE11180428_HOLD_TRAINING_F_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_F_MASK                       0x20
#define PCIE11180428_HOLD_TRAINING_G_OFFSET                     6
#define PCIE11180428_HOLD_TRAINING_G_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_G_MASK                       0x40
#define PCIE11180428_HOLD_TRAINING_H_OFFSET                     7
#define PCIE11180428_HOLD_TRAINING_H_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_H_MASK                       0x80
#define PCIE11180428_HOLD_TRAINING_I_OFFSET                     8
#define PCIE11180428_HOLD_TRAINING_I_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_I_MASK                       0x100
#define PCIE11180428_HOLD_TRAINING_J_OFFSET                     9
#define PCIE11180428_HOLD_TRAINING_J_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_J_MASK                       0x200
#define PCIE11180428_HOLD_TRAINING_K_OFFSET                     10
#define PCIE11180428_HOLD_TRAINING_K_WIDTH                      1
#define PCIE11180428_HOLD_TRAINING_K_MASK                       0x400

/// PCIE11180428
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
} PCIE11180428_STRUCT;

// Address
#define PCIE1_SWRST_CONTROL_6_ADDRESS                          0x11280428

// Type
#define PCIE1_SWRST_CONTROL_6_TYPE                             TYPE_SMN

#define PCIE11280428_HOLD_TRAINING_A_OFFSET                     0
#define PCIE11280428_HOLD_TRAINING_A_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_A_MASK                       0x1
#define PCIE11280428_HOLD_TRAINING_B_OFFSET                     1
#define PCIE11280428_HOLD_TRAINING_B_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_B_MASK                       0x2
#define PCIE11280428_HOLD_TRAINING_C_OFFSET                     2
#define PCIE11280428_HOLD_TRAINING_C_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_C_MASK                       0x4
#define PCIE11280428_HOLD_TRAINING_D_OFFSET                     3
#define PCIE11280428_HOLD_TRAINING_D_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_D_MASK                       0x8
#define PCIE11280428_HOLD_TRAINING_E_OFFSET                     4
#define PCIE11280428_HOLD_TRAINING_E_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_E_MASK                       0x10
#define PCIE11280428_HOLD_TRAINING_F_OFFSET                     5
#define PCIE11280428_HOLD_TRAINING_F_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_F_MASK                       0x20
#define PCIE11280428_HOLD_TRAINING_G_OFFSET                     6
#define PCIE11280428_HOLD_TRAINING_G_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_G_MASK                       0x40
#define PCIE11280428_HOLD_TRAINING_H_OFFSET                     7
#define PCIE11280428_HOLD_TRAINING_H_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_H_MASK                       0x80
#define PCIE11280428_HOLD_TRAINING_I_OFFSET                     8
#define PCIE11280428_HOLD_TRAINING_I_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_I_MASK                       0x100
#define PCIE11280428_HOLD_TRAINING_J_OFFSET                     9
#define PCIE11280428_HOLD_TRAINING_J_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_J_MASK                       0x200
#define PCIE11280428_HOLD_TRAINING_K_OFFSET                     10
#define PCIE11280428_HOLD_TRAINING_K_WIDTH                      1
#define PCIE11280428_HOLD_TRAINING_K_MASK                       0x400

/// PCIE11280428
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
} PCIE11280428_STRUCT;


// Register Name CPM_CONTROL

// Address
#define PCIE0_CPM_CONTROL_ADDRESS                                           0x11180460
#define PCIE1_CPM_CONTROL_ADDRESS                                           0x11280460

// Type
#define CPM_CONTROL_TYPE                                              TYPE_SMN

#define CPM_CONTROL_LCLK_DYN_GATE_ENABLE_OFFSET                       0
#define CPM_CONTROL_LCLK_DYN_GATE_ENABLE_WIDTH                        1
#define CPM_CONTROL_LCLK_DYN_GATE_ENABLE_MASK                         0x1
#define CPM_CONTROL_TXCLK_DYN_GATE_ENABLE_OFFSET                      1
#define CPM_CONTROL_TXCLK_DYN_GATE_ENABLE_WIDTH                       1
#define CPM_CONTROL_TXCLK_DYN_GATE_ENABLE_MASK                        0x2
#define CPM_CONTROL_TXCLK_PERM_GATE_ENABLE_OFFSET                     2
#define CPM_CONTROL_TXCLK_PERM_GATE_ENABLE_WIDTH                      1
#define CPM_CONTROL_TXCLK_PERM_GATE_ENABLE_MASK                       0x4
#define CPM_CONTROL_Reserved_4_3_OFFSET                               3
#define CPM_CONTROL_Reserved_4_3_WIDTH                                2
#define CPM_CONTROL_Reserved_4_3_MASK                                 0x18
#define CPM_CONTROL_TXCLK_LCNT_GATE_ENABLE_OFFSET                     5
#define CPM_CONTROL_TXCLK_LCNT_GATE_ENABLE_WIDTH                      1
#define CPM_CONTROL_TXCLK_LCNT_GATE_ENABLE_MASK                       0x20
#define CPM_CONTROL_TXCLK_REGS_GATE_ENABLE_OFFSET                     6
#define CPM_CONTROL_TXCLK_REGS_GATE_ENABLE_WIDTH                      1
#define CPM_CONTROL_TXCLK_REGS_GATE_ENABLE_MASK                       0x40
#define CPM_CONTROL_TXCLK_PRBS_GATE_ENABLE_OFFSET                     7
#define CPM_CONTROL_TXCLK_PRBS_GATE_ENABLE_WIDTH                      1
#define CPM_CONTROL_TXCLK_PRBS_GATE_ENABLE_MASK                       0x80
#define CPM_CONTROL_REFCLK_REGS_GATE_ENABLE_OFFSET                    8
#define CPM_CONTROL_REFCLK_REGS_GATE_ENABLE_WIDTH                     1
#define CPM_CONTROL_REFCLK_REGS_GATE_ENABLE_MASK                      0x100
#define CPM_CONTROL_LCLK_DYN_GATE_LATENCY_OFFSET                      9
#define CPM_CONTROL_LCLK_DYN_GATE_LATENCY_WIDTH                       1
#define CPM_CONTROL_LCLK_DYN_GATE_LATENCY_MASK                        0x200
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_OFFSET                     10
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_WIDTH                      1
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_MASK                       0x400
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_OFFSET                    11
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_WIDTH                     1
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_MASK                      0x800
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_OFFSET                    12
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_WIDTH                     1
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_MASK                      0x1000
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_OFFSET                   13
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_WIDTH                    1
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_MASK                     0x2000
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_OFFSET                       14
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_WIDTH                        1
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_MASK                         0x4000
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_OFFSET                        15
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_WIDTH                         1
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_MASK                          0x8000
#define CPM_CONTROL_Reserved_16_16_OFFSET                             16
#define CPM_CONTROL_Reserved_16_16_WIDTH                              1
#define CPM_CONTROL_Reserved_16_16_MASK                               0x10000
#define CPM_CONTROL_FAST_TXCLK_LATENCY_OFFSET                         17
#define CPM_CONTROL_FAST_TXCLK_LATENCY_WIDTH                          3
#define CPM_CONTROL_FAST_TXCLK_LATENCY_MASK                           0xe0000
#define CPM_CONTROL_Reserved_21_20_OFFSET                             20
#define CPM_CONTROL_Reserved_21_20_WIDTH                              2
#define CPM_CONTROL_Reserved_21_20_MASK                               0x300000
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_OFFSET                       22
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_WIDTH                        1
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_MASK                         0x400000
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_OFFSET                      23
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_WIDTH                       1
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_MASK                        0x800000
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_OFFSET                24
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_WIDTH                 1
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_MASK                  0x1000000
#define CPM_CONTROL_SPARE_REGS_OFFSET                                 25
#define CPM_CONTROL_SPARE_REGS_WIDTH                                  7
#define CPM_CONTROL_SPARE_REGS_MASK                                   0xfe000000L

/// CPM_CONTROL
typedef union {
  struct {
    UINT32                                    LCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_PERM_GATE_ENABLE:1 ; ///<
    UINT32                                            Reserved_4_3:2 ; ///<
    UINT32                                  TXCLK_LCNT_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_PRBS_GATE_ENABLE:1 ; ///<
    UINT32                                 REFCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                   LCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                  TXCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_PERM_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                REFCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                    LCLK_GATE_TXCLK_FREE:1 ; ///<
    UINT32                                     RCVR_DET_CLK_ENABLE:1 ; ///<
    UINT32                                          Reserved_16_16:1 ; ///<
    UINT32                                      FAST_TXCLK_LATENCY:3 ; ///<
    UINT32                                          Reserved_21_20:2 ; ///<
    UINT32                                    REFCLK_XSTCLK_ENABLE:1 ; ///<
    UINT32                                   REFCLK_XSTCLK_LATENCY:1 ; ///<
    UINT32                             CLKREQb_UNGATE_TXCLK_ENABLE:1 ; ///<
    UINT32                                              SPARE_REGS:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} CPM_CONTROL_STRUCT;


// Address
#define SMN_0x101235CC_ADDRESS                                 0x101235CC

// Type
#define SMN_0x101235CC_TYPE                                    TYPE_SMN

#define SMN_0x101235CC_STRAP_MULTI_FUNC_EN_OFFSET              10
#define SMN_0x101235CC_STRAP_MULTI_FUNC_EN_WIDTH               1
#define SMN_0x101235CC_STRAP_MULTI_FUNC_EN_MASK                0x400

/// NBIFRCC0_000035CC
typedef union {
  struct {
    UINT32                                     STRAP_MULTI_FUNC_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x101235CC_STRUCT;

// Address
#define SMN_0x102235CC_ADDRESS                                 0x102235CC

// Type
#define SMN_0x102235CC_TYPE                                    TYPE_SMN

#define SMN_0x102235CC_STRAP_MULTI_FUNC_EN_OFFSET              10
#define SMN_0x102235CC_STRAP_MULTI_FUNC_EN_WIDTH               1
#define SMN_0x102235CC_STRAP_MULTI_FUNC_EN_MASK                0x400

/// NBIFRCC1_000035CC
typedef union {
  struct {
    UINT32                                     STRAP_MULTI_FUNC_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x102235CC_STRUCT;

// Address
#define SMN_0x103235CC_ADDRESS                                 0x103235CC

// Type
#define SMN_0x103235CC_TYPE                                    TYPE_SMN

#define SMN_0x103235CC_STRAP_MULTI_FUNC_EN_OFFSET              10
#define SMN_0x103235CC_STRAP_MULTI_FUNC_EN_WIDTH               1
#define SMN_0x103235CC_STRAP_MULTI_FUNC_EN_MASK                0x400

/// NBIFRCC1_000035CC
typedef union {
  struct {
    UINT32                                     STRAP_MULTI_FUNC_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x103235CC_STRUCT;

// Address
#define NBIF0RCC_DEV0_PORT_STRAP6_ADDRESS                           0x10131018
#define NBIF1RCC_DEV0_PORT_STRAP6_ADDRESS                           0x10231018
#define NBIF2RCC_DEV0_PORT_STRAP6_ADDRESS                           0x10331018

// Type
#define RCC_DEV0_PORT_STRAP6_TYPE                              TYPE_SMN

#define STRAP_CFG_CRS_EN_DEV0_OFFSET                                0
#define STRAP_CFG_CRS_EN_DEV0_WIDTH                                 1
#define STRAP_CFG_CRS_EN_DEV0_MASK                                  0x1
#define STRAP_SMN_ERR_STATUS_MASK_EN_DNS_DEV0_OFFSET                1
#define STRAP_SMN_ERR_STATUS_MASK_EN_DNS_DEV0_WIDTH                 1
#define STRAP_SMN_ERR_STATUS_MASK_EN_DNS_DEV0_MASK                  0x2

/// RCC_DEV0_PORT_STRAP6
typedef union {
  struct {
    UINT32                                   STRAP_CFG_CRS_EN_DEV0:1 ; ///<
    UINT32                   STRAP_SMN_ERR_STATUS_MASK_EN_DNS_DEV0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_PORT_STRAP6_STRUCT;


// Address
#define NBIFMISC0_00000024                                     0x1013A024
#define NBIFMISC1_00000024                                     0x1023A024
#define NBIFMISC2_00000024                                     0x1033A024

// Type
#define NBIFMISC0_00000024_TYPE                                TYPE_SMN

#define NBIFMISC0_00000024_TX_RO_OVERIDE_P_F2_OFFSET           6
#define NBIFMISC0_00000024_TX_RO_OVERIDE_P_F2_WIDTH            2
#define NBIFMISC0_00000024_TX_RO_OVERIDE_P_F2_MASK             0xc0

/// NBIFMISC0_00000024
typedef union {
  struct {
    UINT32                                            Reserved_5_0:6 ; ///<
    UINT32                                      TX_RO_OVERIDE_P_F2:2 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC0_00000024_STRUCT;


// Address
#define NBIFMISC0_INTR_LINE_POLARITY_ADDRESS                   0x1013A004

// Type
#define NBIFMISC0_INTR_LINE_POLARITY_TYPE                      TYPE_SMN

#define NBIFMISC0_00000004_INTR_LINE_POLARITY_OFFSET           0
#define NBIFMISC0_00000004_INTR_LINE_POLARITY_WIDTH            8
#define NBIFMISC0_00000004_INTR_LINE_POLARITY_MASK             0xff

/// NBIFMISC0_00000004
typedef union {
  struct {
    UINT32                                      INTR_LINE_POLARITY:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC0_00000004_STRUCT;

// Address
#define NBIFMISC0_INTR_LINE_ENABLE_ADDRESS                     0x1013A008

// Type
#define NBIFMISC0_INTR_LINE_ENABLE_TYPE                        TYPE_SMN

#define NBIFMISC0_00000008_INTR_LINE_ENABLE_OFFSET             0
#define NBIFMISC0_00000008_INTR_LINE_ENABLE_WIDTH              8
#define NBIFMISC0_00000008_INTR_LINE_ENABLE_MASK               0xff

/// NBIFMISC0_00000008
typedef union {
  struct {
    UINT32                                        INTR_LINE_ENABLE:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC0_00000008_STRUCT;


// Address
#define NBIFMISC1_INTR_LINE_POLARITY_ADDRESS                   0x1023A004

// Type
#define NBIFMISC1_INTR_LINE_POLARITY_TYPE                      TYPE_SMN

#define NBIFMISC1_00000004_INTR_LINE_POLARITY_OFFSET           0
#define NBIFMISC1_00000004_INTR_LINE_POLARITY_WIDTH            8
#define NBIFMISC1_00000004_INTR_LINE_POLARITY_MASK             0xff

/// NBIFMISC1_00000004
typedef union {
  struct {
    UINT32                                      INTR_LINE_POLARITY:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC1_00000004_STRUCT;


// Address
#define NBIFMISC1_INTR_LINE_ENABLE_ADDRESS                     0x1023A008

// Type
#define NBIFMISC1_INTR_LINE_ENABLE_TYPE                        TYPE_SMN

#define NBIFMISC1_00000008_INTR_LINE_ENABLE_OFFSET             0
#define NBIFMISC1_00000008_INTR_LINE_ENABLE_WIDTH              8
#define NBIFMISC1_00000008_INTR_LINE_ENABLE_MASK               0xff

/// NBIFMISC1_00000008
typedef union {
  struct {
    UINT32                                        INTR_LINE_ENABLE:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC1_00000008_STRUCT;


// Address
#define  NBIFMISC2_INTR_LINE_POLARITY_ADDRESS                  0x1033A004

// Type
#define  NBIFMISC2_INTR_LINE_POLARITY_TYPE                     TYPE_SMN

#define NBIFMISC2_00000004_INTR_LINE_POLARITY_OFFSET           0
#define NBIFMISC2_00000004_INTR_LINE_POLARITY_WIDTH            8
#define NBIFMISC2_00000004_INTR_LINE_POLARITY_MASK             0xff

/// NBIFMISC2_00000004
typedef union {
  struct {
    UINT32                                      INTR_LINE_POLARITY:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC2_00000004_STRUCT;


// Address
#define  NBIFMISC2_INTR_LINE_ENABLE_ADDRESS                    0x1033A008

// Type
#define  NBIFMISC2_INTR_LINE_ENABLE_TYPE                       TYPE_SMN

#define NBIFMISC2_00000008_INTR_LINE_ENABLE_OFFSET             0
#define NBIFMISC2_00000008_INTR_LINE_ENABLE_WIDTH              8
#define NBIFMISC2_00000008_INTR_LINE_ENABLE_MASK               0xff

/// NBIFMISC2_00000008
typedef union {
  struct {
    UINT32                                        INTR_LINE_ENABLE:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFMISC2_00000008_STRUCT;

// Address
#define SB_LOCATION_ADDRESS                                    0x13B1007C

// Type
#define SB_LOCATION_TYPE                                       TYPE_NBMISC

#define NBMISC_007C_SBlocated_Port_OFFSET                      0
#define NBMISC_007C_SBlocated_Port_WIDTH                       16
#define NBMISC_007C_SBlocated_Port_MASK                        0xffff
#define NBMISC_007C_SBlocated_Core_OFFSET                      16
#define NBMISC_007C_SBlocated_Core_WIDTH                       16
#define NBMISC_007C_SBlocated_Core_MASK                        0xffff0000L

/// NBMISC_007C
typedef union {
  struct {
    UINT32                                          SBlocated_Port:16; ///<
    UINT32                                          SBlocated_Core:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_007C_STRUCT;

// svd_group: NBIO_IOHC_aliasSMN

// Address
#define CFG_IOHC_PCI_ADDRESS                                   0x13b10034

// Type
#define CFG_IOHC_PCI_TYPE                                      TYPE_SMN

#define SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_OFFSET          0
#define SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_WIDTH           1
#define SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_MASK            0x1
#define SMN_00000034_IOMMU_DIS_OFFSET                          31
#define SMN_00000034_IOMMU_DIS_WIDTH                           1
#define SMN_00000034_IOMMU_DIS_MASK                            0x80000000L

/// SMN_00000034
typedef union {
  struct {
    UINT32                               CFG_IOHC_PCI_Dev0Fn2RegEn:1 ; ///<
    UINT32                                               IOMMU_DIS:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000034_STRUCT;

// Address
#define NB_MMIOBASE_ADDRESS                                    0x13B1005C

// Type
#define NB_MMIOBASE_TYPE                                       TYPE_NBMISC

#define NB_MMIOBASE_OFFSET                                     0
#define NB_MMIOBASE_WIDTH                                      32
#define NB_MMIOBASE_MASK                                       0xFFFFFFFF

/// NBMISC_0064
typedef union {
  struct {
    UINT32                                                MMIOBASE:32 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NB_MMIOBASE_STRUCT;


// Address
#define NB_MMIOLIMIT_ADDRESS                                   0x13B10060

// Type
#define NB_MMIOLIMIT_TYPE                                      TYPE_NBMISC

#define NB_MMIOLIMIT_OFFSET                                    0
#define NB_MMIOLIMIT_WIDTH                                     32
#define NB_MMIOLIMIT_MASK                                      0xFFFFFFFF

/// NBMISC_0064
typedef union {
  struct {
    UINT32                                               MMIOLIMIT:32 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NB_MMIOLIMIT_STRUCT;

// Address
#define NB_LOWER_TOP_OF_DRAM2_ADDRESS                          0x13B10064

// Type
#define NB_LOWER_TOP_OF_DRAM2_TYPE                             TYPE_NBMISC

#define NBMISC_0064_ENABLE_OFFSET                              0
#define NBMISC_0064_ENABLE_WIDTH                               1
#define NBMISC_0064_ENABLE_MASK                                0x1
//Reserved_22_1:22
#define NBMISC_0064_LOWER_TOM2_OFFSET                          23
#define NBMISC_0064_LOWER_TOM2_WIDTH                           9
#define NBMISC_0064_LOWER_TOM2_MASK                            0xff800000L

/// NBMISC_0064
typedef union {
  struct {
    UINT32                                                  ENABLE:1 ; ///<
    UINT32                                           Reserved_22_1:22; ///<
    UINT32                                              LOWER_TOM2:9 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0064_STRUCT;


// Address
#define NB_UPPER_TOP_OF_DRAM2_ADDRESS                          0x13B10068

// Type
#define NB_UPPER_TOP_OF_DRAM2_TYPE                             TYPE_NBMISC

#define NBMISC_0068_UPPER_TOM2_OFFSET                          0
#define NBMISC_0068_UPPER_TOM2_WIDTH                           9
#define NBMISC_0068_UPPER_TOM2_MASK                            0x1ff

/// NBMISC_0068
typedef union {
  struct {
    UINT32                                              UPPER_TOM2:9 ; ///<
    UINT32                                           Reserved_32_8:23; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0068_STRUCT;


// Address
#define NB_LOWER_DRAM2_BASE_ADDRESS                            0x13B1006c

// Type
#define NB_LOWER_DRAM2_BASE_TYPE                               TYPE_NBMISC

#define NBMISC_006C_LOWER_DRAM2_BASE_OFFSET                    23
#define NBMISC_006C_LOWER_DRAM2_BASE_WIDTH                     9
#define NBMISC_006C_LOWER_DRAM2_BASE_MASK                      0xff800000L

/// NBMISC_006C
typedef union {
  struct {
    UINT32                                        LOWER_DRAM2_BASE:9 ; ///<
    UINT32                                           Reserved_32_9:23; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_006C_STRUCT;


// Address
#define NB_UPPER_DRAM2_BASE_ADDRESS                            0x13B10070

// Type
#define NB_UPPER_DRAM2_BASE_TYPE                               TYPE_NBMISC

#define NBMISC_0070_UPPER_DRAM2_BASE_OFFSET                    0
#define NBMISC_0070_UPPER_DRAM2_BASE_WIDTH                     8
#define NBMISC_0070_UPPER_DRAM2_BASE_MASK                      0xff

/// NBMISC_0070
typedef union {
  struct {
    UINT32                                        UPPER_DRAM2_BASE:8 ; ///<
    UINT32                                           Reserved_32_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0070_STRUCT;

// Address
#define IOHC_GLUE_CG_LCLK_CTRL_0_ADDRESS                       0x13B10088

// Type
#define IOHC_GLUE_CG_LCLK_CTRL_0_TYPE                          TYPE_NBMISC

#define NBMISC_0088_CG_OFF_HYSTERESIS_OFFSET                   4
#define NBMISC_0088_CG_OFF_HYSTERESIS_WIDTH                    8
#define NBMISC_0088_CG_OFF_HYSTERESIS_MASK                     0xff0
#define NBMISC_0088_SOFT_OVERRIDE_CLK9_OFFSET                  22
#define NBMISC_0088_SOFT_OVERRIDE_CLK9_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK9_MASK                    0x400000
#define NBMISC_0088_SOFT_OVERRIDE_CLK8_OFFSET                  23
#define NBMISC_0088_SOFT_OVERRIDE_CLK8_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK8_MASK                    0x800000
#define NBMISC_0088_SOFT_OVERRIDE_CLK7_OFFSET                  24
#define NBMISC_0088_SOFT_OVERRIDE_CLK7_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK7_MASK                    0x1000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK6_OFFSET                  25
#define NBMISC_0088_SOFT_OVERRIDE_CLK6_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK6_MASK                    0x2000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK5_OFFSET                  26
#define NBMISC_0088_SOFT_OVERRIDE_CLK5_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK5_MASK                    0x4000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK4_OFFSET                  27
#define NBMISC_0088_SOFT_OVERRIDE_CLK4_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK4_MASK                    0x8000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK3_OFFSET                  28
#define NBMISC_0088_SOFT_OVERRIDE_CLK3_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK3_MASK                    0x10000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK2_OFFSET                  29
#define NBMISC_0088_SOFT_OVERRIDE_CLK2_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK2_MASK                    0x20000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK1_OFFSET                  30
#define NBMISC_0088_SOFT_OVERRIDE_CLK1_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK1_MASK                    0x40000000
#define NBMISC_0088_SOFT_OVERRIDE_CLK0_OFFSET                  31
#define NBMISC_0088_SOFT_OVERRIDE_CLK0_WIDTH                   1
#define NBMISC_0088_SOFT_OVERRIDE_CLK0_MASK                    0x80000000L

/// NBMISC_0088
typedef union {
  struct {
    UINT32                                       CG_OFF_HYSTERESIS:8 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK9:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK8:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK7:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK6:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK5:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK4:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK3:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK2:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK1:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0088_STRUCT;


// Address
#define IOHC_GLUE_CG_LCLK_CTRL_1_ADDRESS                       0x13B1008c

// Type
#define IOHC_GLUE_CG_LCLK_CTRL_1_TYPE                          TYPE_NBMISC

#define NBMISC_008C_SOFT_OVERRIDE_CLK9_OFFSET                  22
#define NBMISC_008C_SOFT_OVERRIDE_CLK9_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK9_MASK                    0x400000
#define NBMISC_008C_SOFT_OVERRIDE_CLK8_OFFSET                  23
#define NBMISC_008C_SOFT_OVERRIDE_CLK8_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK8_MASK                    0x800000
#define NBMISC_008C_SOFT_OVERRIDE_CLK7_OFFSET                  24
#define NBMISC_008C_SOFT_OVERRIDE_CLK7_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK7_MASK                    0x1000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK6_OFFSET                  25
#define NBMISC_008C_SOFT_OVERRIDE_CLK6_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK6_MASK                    0x2000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK5_OFFSET                  26
#define NBMISC_008C_SOFT_OVERRIDE_CLK5_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK5_MASK                    0x4000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK4_OFFSET                  27
#define NBMISC_008C_SOFT_OVERRIDE_CLK4_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK4_MASK                    0x8000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK3_OFFSET                  28
#define NBMISC_008C_SOFT_OVERRIDE_CLK3_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK3_MASK                    0x10000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK2_OFFSET                  29
#define NBMISC_008C_SOFT_OVERRIDE_CLK2_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK2_MASK                    0x20000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK1_OFFSET                  30
#define NBMISC_008C_SOFT_OVERRIDE_CLK1_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK1_MASK                    0x40000000
#define NBMISC_008C_SOFT_OVERRIDE_CLK0_OFFSET                  31
#define NBMISC_008C_SOFT_OVERRIDE_CLK0_WIDTH                   1
#define NBMISC_008C_SOFT_OVERRIDE_CLK0_MASK                    0x80000000L

/// NBMISC_008C
typedef union {
  struct {
    UINT32                                      SOFT_OVERRIDE_CLK9:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK8:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK7:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK6:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK5:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK4:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK3:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK2:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK1:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_008C_STRUCT;

// Address
#define IOHC_GLUE_CG_LCLK_CTRL_2_ADDRESS                       0x13B10090

// Type
#define IOHC_GLUE_CG_LCLK_CTRL_2_TYPE                          TYPE_NBMISC

#define NBMISC_0090_SOFT_OVERRIDE_CLK9_OFFSET                  22
#define NBMISC_0090_SOFT_OVERRIDE_CLK9_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK9_MASK                    0x400000
#define NBMISC_0090_SOFT_OVERRIDE_CLK8_OFFSET                  23
#define NBMISC_0090_SOFT_OVERRIDE_CLK8_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK8_MASK                    0x800000
#define NBMISC_0090_SOFT_OVERRIDE_CLK7_OFFSET                  24
#define NBMISC_0090_SOFT_OVERRIDE_CLK7_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK7_MASK                    0x1000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK6_OFFSET                  25
#define NBMISC_0090_SOFT_OVERRIDE_CLK6_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK6_MASK                    0x2000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK5_OFFSET                  26
#define NBMISC_0090_SOFT_OVERRIDE_CLK5_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK5_MASK                    0x4000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK4_OFFSET                  27
#define NBMISC_0090_SOFT_OVERRIDE_CLK4_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK4_MASK                    0x8000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK3_OFFSET                  28
#define NBMISC_0090_SOFT_OVERRIDE_CLK3_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK3_MASK                    0x10000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK2_OFFSET                  29
#define NBMISC_0090_SOFT_OVERRIDE_CLK2_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK2_MASK                    0x20000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK1_OFFSET                  30
#define NBMISC_0090_SOFT_OVERRIDE_CLK1_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK1_MASK                    0x40000000
#define NBMISC_0090_SOFT_OVERRIDE_CLK0_OFFSET                  31
#define NBMISC_0090_SOFT_OVERRIDE_CLK0_WIDTH                   1
#define NBMISC_0090_SOFT_OVERRIDE_CLK0_MASK                    0x80000000L

/// NBMISC_0090
typedef union {
  struct {
    UINT32                                      SOFT_OVERRIDE_CLK9:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK8:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK7:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK6:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK5:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK4:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK3:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK2:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK1:1 ; ///<
    UINT32                                      SOFT_OVERRIDE_CLK0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0090_STRUCT;

#define IOC_FEATURE_CNTL_ADDRESS                               0x13B10118

// Type
#define IOC_FEATURE_CNTL_TYPE                                  TYPE_NBMISC

#define NBMISC_0118_HpPmpme_DevID_En_OFFSET                    0
#define NBMISC_0118_HpPmpme_DevID_En_WIDTH                     1
#define NBMISC_0118_HpPmpme_DevID_En_MASK                      0x1
#define NBMISC_0118_P2P_mode_OFFSET                            1
#define NBMISC_0118_P2P_mode_WIDTH                             2
#define NBMISC_0118_P2P_mode_MASK                              0x6
//Reserved_4_3
#define NBMISC_0118_JTAG_ENABLE_OFFSET                         5
#define NBMISC_0118_JTAG_ENABLE_WIDTH                          1
#define NBMISC_0118_JTAG_ENABLE_MASK                           0x20
#define NBMISC_0118_MCU_ENABLE_OFFSET                          6
#define NBMISC_0118_MCU_ENABLE_WIDTH                           1
#define NBMISC_0118_MCU_ENABLE_MASK                            0x40
//Reserved_10_7
#define NBMISC_0118_DS_ALWAYS_BUSY_OFFSET                      11
#define NBMISC_0118_DS_ALWAYS_BUSY_WIDTH                       1
#define NBMISC_0118_DS_ALWAYS_BUSY_MASK                        0x800
#define NBMISC_0118_INTx_LevelOnlyMode_OFFSET                  12
#define NBMISC_0118_INTx_LevelOnlyMode_WIDTH                   1
#define NBMISC_0118_INTx_LevelOnlyMode_MASK                    0x1000
//Reserved_14_13
#define NBMISC_0118_HostClkReqIdle_OFFSET                      15
#define NBMISC_0118_HostClkReqIdle_WIDTH                       1
#define NBMISC_0118_HostClkReqIdle_MASK                        0x8000
//Reserved_21:16
#define NBMISC_0118_IOC_ARI_SUPPORTED_OFFSET                   22
#define NBMISC_0118_IOC_ARI_SUPPORTED_WIDTH                    1
#define NBMISC_0118_IOC_ARI_SUPPORTED_MASK                     0x400000
//Reserved_27:23
#define NBMISC_0118_MISC_FEATURE_CNTL_OFFSET                   28
#define NBMISC_0118_MISC_FEATURE_CNTL_WIDTH                    4
#define NBMISC_0118_MISC_FEATURE_CNTL_MASK                     0xf0000000L

/// NBMISC_0118
typedef union {
  struct {
    UINT32                                        HpPmpme_DevID_En:1 ; ///<
    UINT32                                                P2P_mode:2 ; ///<
    UINT32                                            Reserved_4_3:2 ; ///<
    UINT32                                             JTAG_ENABLE:1 ; ///<
    UINT32                                              MCU_ENABLE:1 ; ///<
    UINT32                                           Reserved_10_7:4 ; ///<
    UINT32                                          DS_ALWAYS_BUSY:1 ; ///<
    UINT32                                      INTx_LevelOnlyMode:1 ; ///<
    UINT32                                          Reserved_14_13:2 ; ///<
    UINT32                                          HostClkReqIdle:1 ; ///<
    UINT32                                          Reserved_21_16:6 ; ///<
    UINT32                                       IOC_ARI_SUPPORTED:1 ; ///<
    UINT32                                          Reserved_27_23:5 ; ///<
    UINT32                                       MISC_FEATURE_CNTL:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0118_STRUCT;

// Address
#define NB_TOP_OF_DRAM3_ADDRESS                                0x13B10138

// Type
#define NB_TOP_OF_DRAM3_TYPE                                   TYPE_NBMISC

#define NBMISC_0138_TOM3_LIMIT_OFFSET                          0
#define NBMISC_0138_TOM3_LIMIT_WIDTH                           30
#define NBMISC_0138_TOM3_LIMIT_MASK                            0x3fffffff
//Reserved_30_30
#define NBMISC_0138_TOM3_ENABLE_OFFSET                         31
#define NBMISC_0138_TOM3_ENABLE_WIDTH                          1
#define NBMISC_0138_TOM3_ENABLE_MASK                           0x80000000L

/// NBMISC_0138
typedef union {
  struct {
    UINT32                                              TOM3_LIMIT:30; ///<
    UINT32                                          Reserved_30_30:1 ; ///<
    UINT32                                             TOM3_ENABLE:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0138_STRUCT;

// Address
#define PCIE_VDM_CNTL2_ADDRESS                                 0x13B10230

// Type
#define PCIE_VDM_CNTL2_TYPE                                    TYPE_NBMISC

#define NBMISC_0230_VdmP2pMode_OFFSET                          0
#define NBMISC_0230_VdmP2pMode_WIDTH                           2
#define NBMISC_0230_VdmP2pMode_MASK                            0x3
//Reserved 3:2
#define NBMISC_0230_MCTPT2SMUEn_OFFSET                         4
#define NBMISC_0230_MCTPT2SMUEn_WIDTH                          1
#define NBMISC_0230_MCTPT2SMUEn_MASK                           0x10
#define NBMISC_0230_AMDVDM2SMUEn_OFFSET                        5
#define NBMISC_0230_AMDVDM2SMUEn_WIDTH                         1
#define NBMISC_0230_AMDVDM2SMUEn_MASK                          0x20
#define NBMISC_0230_OtherVDM2SMUEn_OFFSET                      6
#define NBMISC_0230_OtherVDM2SMUEn_WIDTH                       1
#define NBMISC_0230_OtherVDM2SMUEn_MASK                        0x40
//Reserved 14:7
#define NBMISC_0230_MCTPMasterValid_OFFSET                     15
#define NBMISC_0230_MCTPMasterValid_WIDTH                      1
#define NBMISC_0230_MCTPMasterValid_MASK                       0x8000
#define NBMISC_0230_MCTPMasterID_OFFSET                        16
#define NBMISC_0230_MCTPMasterID_WIDTH                         16
#define NBMISC_0230_MCTPMasterID_MASK                          0xffff0000L

/// NBMISC_0230
typedef union {
  struct {
    UINT32                                              VdmP2pMode:2 ; ///<
    UINT32                                            Reserved_3_2:2 ; ///<
    UINT32                                             MCTPT2SMUEn:1 ; ///<
    UINT32                                            AMDVDM2SMUEn:1 ; ///<
    UINT32                                          OtherVDM2SMUEn:1 ; ///<
    UINT32                                           Reserved_14_7:8 ; ///<
    UINT32                                         MCTPMasterValid:1 ; ///<
    UINT32                                            MCTPMasterID:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBMISC_0230_STRUCT;

// Address
#define IOHC_SION_S0_Client0_Req_BurstTarget_Lower_ADDRESS                0x13B14400

// Type
#define IOHC_SION_S0_Client0_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4400_IOHC_SION_S0_Client0_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4400_IOHC_SION_S0_Client0_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4400_IOHC_SION_S0_Client0_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4400
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4400_STRUCT;

// Address
#define IOHC_SION_S0_Client0_Req_BurstTarget_Upper_ADDRESS                0x13B14404

// Type
#define IOHC_SION_S0_Client0_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4404_IOHC_SION_S0_Client0_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4404_IOHC_SION_S0_Client0_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4404_IOHC_SION_S0_Client0_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4404
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4404_STRUCT;

// Address
#define IOHC_SION_S0_Client0_Req_TimeSlot_Lower_ADDRESS                0x13B14408

// Type
#define IOHC_SION_S0_Client0_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4408_IOHC_SION_S0_Client0_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_4408_IOHC_SION_S0_Client0_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_4408_IOHC_SION_S0_Client0_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4408
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4408_STRUCT;

// Address
#define IOHC_SION_S0_Client0_Req_TimeSlot_Upper_ADDRESS                0x13B1440C

// Type
#define IOHC_SION_S0_Client0_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_440C_IOHC_SION_S0_Client0_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_440C_IOHC_SION_S0_Client0_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_440C_IOHC_SION_S0_Client0_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_440C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_440C_STRUCT;

// Address
#define IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14410

// Type
#define IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4410_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4410_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4410_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4410
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4410_STRUCT;

// Address
#define IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14414

// Type
#define IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4414_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4414_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4414_IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4414
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client0_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4414_STRUCT;

// Address
#define IOHC_SION_S0_Client1_Req_BurstTarget_Lower_ADDRESS                0x13B14804

// Type
#define IOHC_SION_S0_Client1_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4804_IOHC_SION_S0_Client1_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4804_IOHC_SION_S0_Client1_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4804_IOHC_SION_S0_Client1_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4804
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4804_STRUCT;

// Address
#define IOHC_SION_S0_Client1_Req_BurstTarget_Upper_ADDRESS                0x13B14808

// Type
#define IOHC_SION_S0_Client1_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4808_IOHC_SION_S0_Client1_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4808_IOHC_SION_S0_Client1_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4808_IOHC_SION_S0_Client1_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4808
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4808_STRUCT;

// Address
#define IOHC_SION_S0_Client1_Req_TimeSlot_Lower_ADDRESS                0x13B1480C

// Type
#define IOHC_SION_S0_Client1_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_480C_IOHC_SION_S0_Client1_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_480C_IOHC_SION_S0_Client1_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_480C_IOHC_SION_S0_Client1_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_480C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_480C_STRUCT;

// Address
#define IOHC_SION_S0_Client1_Req_TimeSlot_Upper_ADDRESS                0x13B14810

// Type
#define IOHC_SION_S0_Client1_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4810_IOHC_SION_S0_Client1_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_4810_IOHC_SION_S0_Client1_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_4810_IOHC_SION_S0_Client1_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4810
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4810_STRUCT;


// Address
#define IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14814

// Type
#define IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4814_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4814_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4814_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4814
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4814_STRUCT;

// Address
#define IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14818

// Type
#define IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4818_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4818_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4818_IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4818
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client1_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4818_STRUCT;

// Address
#define IOHC_SION_S0_Client2_Req_BurstTarget_Lower_ADDRESS                0x13B14C08

// Type
#define IOHC_SION_S0_Client2_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C08_IOHC_SION_S0_Client2_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4C08_IOHC_SION_S0_Client2_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4C08_IOHC_SION_S0_Client2_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C08
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C08_STRUCT;

// Address
#define IOHC_SION_S0_Client2_Req_BurstTarget_Upper_ADDRESS                0x13B14C0C

// Type
#define IOHC_SION_S0_Client2_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C0C_IOHC_SION_S0_Client2_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4C0C_IOHC_SION_S0_Client2_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4C0C_IOHC_SION_S0_Client2_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C0C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C0C_STRUCT;

// Address
#define IOHC_SION_S0_Client2_Req_TimeSlot_Lower_ADDRESS                0x13B14C10

// Type
#define IOHC_SION_S0_Client2_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C10_IOHC_SION_S0_Client2_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_4C10_IOHC_SION_S0_Client2_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_4C10_IOHC_SION_S0_Client2_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C10
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C10_STRUCT;

// Address
#define IOHC_SION_S0_Client2_Req_TimeSlot_Upper_ADDRESS                0x13B14C14

// Type
#define IOHC_SION_S0_Client2_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C14_IOHC_SION_S0_Client2_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_4C14_IOHC_SION_S0_Client2_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_4C14_IOHC_SION_S0_Client2_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C14
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C14_STRUCT;

// Address
#define IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14C18

// Type
#define IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C18_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4C18_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4C18_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C18
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C18_STRUCT;

// Address
#define IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14C1C

// Type
#define IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C1C_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4C1C_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4C1C_IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C1C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client2_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C1C_STRUCT;

// Address
#define IOHC_SION_S0_Client3_Req_BurstTarget_Lower_ADDRESS                0x13B1500C

// Type
#define IOHC_SION_S0_Client3_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_500C_IOHC_SION_S0_Client3_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_500C_IOHC_SION_S0_Client3_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_500C_IOHC_SION_S0_Client3_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_500C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_500C_STRUCT;

// Address
#define IOHC_SION_S0_Client3_Req_BurstTarget_Upper_ADDRESS                0x13B15010

// Type
#define IOHC_SION_S0_Client3_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5010_IOHC_SION_S0_Client3_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5010_IOHC_SION_S0_Client3_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5010_IOHC_SION_S0_Client3_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5010
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5010_STRUCT;

// Address
#define IOHC_SION_S0_Client3_Req_TimeSlot_Lower_ADDRESS                0x13B15014

// Type
#define IOHC_SION_S0_Client3_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5014_IOHC_SION_S0_Client3_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_5014_IOHC_SION_S0_Client3_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_5014_IOHC_SION_S0_Client3_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5014
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5014_STRUCT;

// Address
#define IOHC_SION_S0_Client3_Req_TimeSlot_Upper_ADDRESS                0x13B15018

// Type
#define IOHC_SION_S0_Client3_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5018_IOHC_SION_S0_Client3_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_5018_IOHC_SION_S0_Client3_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_5018_IOHC_SION_S0_Client3_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5018
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5018_STRUCT;

// Address
#define IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_ADDRESS                0x13B1501C

// Type
#define IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_501C_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_501C_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_501C_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_501C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_501C_STRUCT;

// Address
#define IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15020

// Type
#define IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5020_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5020_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5020_IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5020
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client3_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5020_STRUCT;

// Address
#define IOHC_SION_S0_Client4_Req_BurstTarget_Lower_ADDRESS                0x13B15410

// Type
#define IOHC_SION_S0_Client4_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5410_IOHC_SION_S0_Client4_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5410_IOHC_SION_S0_Client4_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5410_IOHC_SION_S0_Client4_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5410
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5410_STRUCT;

// Address
#define IOHC_SION_S0_Client4_Req_BurstTarget_Upper_ADDRESS                0x13B15414

// Type
#define IOHC_SION_S0_Client4_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5414_IOHC_SION_S0_Client4_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5414_IOHC_SION_S0_Client4_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5414_IOHC_SION_S0_Client4_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5414
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5414_STRUCT;

// Address
#define IOHC_SION_S0_Client4_Req_TimeSlot_Lower_ADDRESS                0x13B15418

// Type
#define IOHC_SION_S0_Client4_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5418_IOHC_SION_S0_Client4_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_5418_IOHC_SION_S0_Client4_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_5418_IOHC_SION_S0_Client4_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5418
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5418_STRUCT;

// Address
#define IOHC_SION_S0_Client4_Req_TimeSlot_Upper_ADDRESS                0x13B1541C

// Type
#define IOHC_SION_S0_Client4_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_541C_IOHC_SION_S0_Client4_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_541C_IOHC_SION_S0_Client4_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_541C_IOHC_SION_S0_Client4_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_541C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_541C_STRUCT;

// Address
#define IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15420

// Type
#define IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5420_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5420_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5420_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5420
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5420_STRUCT;

// Address
#define IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15424

// Type
#define IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5424_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5424_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5424_IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5424
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client4_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5424_STRUCT;

// Address
#define IOHC_SION_S0_Client5_Req_BurstTarget_Lower_ADDRESS                0x13B15814

// Type
#define IOHC_SION_S0_Client5_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5814_IOHC_SION_S0_Client5_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5814_IOHC_SION_S0_Client5_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5814_IOHC_SION_S0_Client5_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5814
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5814_STRUCT;

// Address
#define IOHC_SION_S0_Client5_Req_BurstTarget_Upper_ADDRESS                0x13B15818

// Type
#define IOHC_SION_S0_Client5_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5818_IOHC_SION_S0_Client5_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5818_IOHC_SION_S0_Client5_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5818_IOHC_SION_S0_Client5_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5818
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5818_STRUCT;

// Address
#define IOHC_SION_S0_Client6_Req_BurstTarget_Lower_ADDRESS                0x13B15C18

// Type
#define IOHC_SION_S0_Client6_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C18_IOHC_SION_S0_Client6_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5C18_IOHC_SION_S0_Client6_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5C18_IOHC_SION_S0_Client6_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C18
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client6_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C18_STRUCT;

// Address
#define IOHC_SION_S0_Client6_Req_BurstTarget_Upper_ADDRESS                0x13B15C1C

// Type
#define IOHC_SION_S0_Client6_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C1C_IOHC_SION_S0_Client6_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5C1C_IOHC_SION_S0_Client6_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5C1C_IOHC_SION_S0_Client6_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C1C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client6_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C1C_STRUCT;

// Address
#define IOHC_SION_S0_Client5_Req_TimeSlot_Lower_ADDRESS                0x13B1581C

// Type
#define IOHC_SION_S0_Client5_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_581C_IOHC_SION_S0_Client5_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_581C_IOHC_SION_S0_Client5_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_581C_IOHC_SION_S0_Client5_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_581C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_581C_STRUCT;

// Address
#define IOHC_SION_S0_Client5_Req_TimeSlot_Upper_ADDRESS                0x13B15820

// Type
#define IOHC_SION_S0_Client5_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5820_IOHC_SION_S0_Client5_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_5820_IOHC_SION_S0_Client5_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_5820_IOHC_SION_S0_Client5_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5820
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5820_STRUCT;

// Address
#define IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15824

// Type
#define IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5824_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5824_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5824_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5824
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5824_STRUCT;

// Address
#define IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15828

// Type
#define IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5828_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5828_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5828_IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5828
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client5_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5828_STRUCT;

// Address
#define IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15C28

// Type
#define IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C28_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5C28_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5C28_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C28
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client6_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C28_STRUCT;

// Address
#define IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15C2C

// Type
#define IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C2C_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5C2C_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5C2C_IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C2C
typedef union {
  struct {
    UINT32              IOHC_SION_S0_Client6_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C2C_STRUCT;

// Address
#define IOHC_SION_S1_Client0_Req_BurstTarget_Lower_ADDRESS                0x13B14430

// Type
#define IOHC_SION_S1_Client0_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4430_IOHC_SION_S1_Client0_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4430_IOHC_SION_S1_Client0_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4430_IOHC_SION_S1_Client0_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4430
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4430_STRUCT;

// Address
#define IOHC_SION_S1_Client0_Req_BurstTarget_Upper_ADDRESS                0x13B14434

// Type
#define IOHC_SION_S1_Client0_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4434_IOHC_SION_S1_Client0_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4434_IOHC_SION_S1_Client0_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4434_IOHC_SION_S1_Client0_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4434
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4434_STRUCT;

// Address
#define IOHC_SION_S1_Client0_Req_TimeSlot_Lower_ADDRESS                0x13B14438

// Type
#define IOHC_SION_S1_Client0_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4438_IOHC_SION_S1_Client0_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_4438_IOHC_SION_S1_Client0_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_4438_IOHC_SION_S1_Client0_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4438
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4438_STRUCT;

// Address
#define IOHC_SION_S1_Client0_Req_TimeSlot_Upper_ADDRESS                0x13B1443C

// Type
#define IOHC_SION_S1_Client0_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_443C_IOHC_SION_S1_Client0_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_443C_IOHC_SION_S1_Client0_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_443C_IOHC_SION_S1_Client0_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_443C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_443C_STRUCT;

// Address
#define IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14440

// Type
#define IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4440_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4440_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4440_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4440
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4440_STRUCT;

// Address
#define IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14444

// Type
#define IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4444_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4444_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4444_IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4444
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client0_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4444_STRUCT;

// Address
#define IOHC_SION_S1_Client1_Req_BurstTarget_Lower_ADDRESS                0x13B14834

// Type
#define IOHC_SION_S1_Client1_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4834_IOHC_SION_S1_Client1_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4834_IOHC_SION_S1_Client1_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4834_IOHC_SION_S1_Client1_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4834
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4834_STRUCT;

// Address
#define IOHC_SION_S1_Client1_Req_BurstTarget_Upper_ADDRESS                0x13B14838

// Type
#define IOHC_SION_S1_Client1_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4838_IOHC_SION_S1_Client1_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4838_IOHC_SION_S1_Client1_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4838_IOHC_SION_S1_Client1_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4838
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4838_STRUCT;

// Address
#define IOHC_SION_S1_Client1_Req_TimeSlot_Lower_ADDRESS                0x13B1483C

// Type
#define IOHC_SION_S1_Client1_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_483C_IOHC_SION_S1_Client1_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_483C_IOHC_SION_S1_Client1_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_483C_IOHC_SION_S1_Client1_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_483C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_483C_STRUCT;

// Address
#define IOHC_SION_S1_Client1_Req_TimeSlot_Upper_ADDRESS                0x13B14840

// Type
#define IOHC_SION_S1_Client1_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4840_IOHC_SION_S1_Client1_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_4840_IOHC_SION_S1_Client1_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_4840_IOHC_SION_S1_Client1_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4840
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4840_STRUCT;

// Address
#define IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14844

// Type
#define IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4844_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4844_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4844_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4844
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4844_STRUCT;

// Address
#define IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14848

// Type
#define IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4848_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4848_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4848_IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4848
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client1_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4848_STRUCT;

// Address
#define IOHC_SION_S1_Client2_Req_BurstTarget_Lower_ADDRESS                0x13B14C38

// Type
#define IOHC_SION_S1_Client2_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C38_IOHC_SION_S1_Client2_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4C38_IOHC_SION_S1_Client2_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4C38_IOHC_SION_S1_Client2_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C38
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C38_STRUCT;

// Address
#define IOHC_SION_S1_Client2_Req_BurstTarget_Upper_ADDRESS                0x13B14C3C

// Type
#define IOHC_SION_S1_Client2_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C3C_IOHC_SION_S1_Client2_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4C3C_IOHC_SION_S1_Client2_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4C3C_IOHC_SION_S1_Client2_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C3C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C3C_STRUCT;

// Address
#define IOHC_SION_S1_Client2_Req_TimeSlot_Lower_ADDRESS                0x13B14C40

// Type
#define IOHC_SION_S1_Client2_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C40_IOHC_SION_S1_Client2_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_4C40_IOHC_SION_S1_Client2_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_4C40_IOHC_SION_S1_Client2_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C40
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C40_STRUCT;

// Address
#define IOHC_SION_S1_Client2_Req_TimeSlot_Upper_ADDRESS                0x13B14C44

// Type
#define IOHC_SION_S1_Client2_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C44_IOHC_SION_S1_Client2_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_4C44_IOHC_SION_S1_Client2_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_4C44_IOHC_SION_S1_Client2_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C44
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C44_STRUCT;

// Address
#define IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_ADDRESS                0x13B14C48

// Type
#define IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C48_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_4C48_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_4C48_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C48
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C48_STRUCT;

// Address
#define IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_ADDRESS                0x13B14C4C

// Type
#define IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_4C4C_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_4C4C_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_4C4C_IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_4C4C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client2_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_4C4C_STRUCT;

// Address
#define IOHC_SION_S1_Client3_Req_BurstTarget_Lower_ADDRESS                0x13B1503C

// Type
#define IOHC_SION_S1_Client3_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_503C_IOHC_SION_S1_Client3_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_503C_IOHC_SION_S1_Client3_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_503C_IOHC_SION_S1_Client3_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_503C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_503C_STRUCT;

// Address
#define IOHC_SION_S1_Client3_Req_BurstTarget_Upper_ADDRESS                0x13B15040

// Type
#define IOHC_SION_S1_Client3_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5040_IOHC_SION_S1_Client3_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5040_IOHC_SION_S1_Client3_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5040_IOHC_SION_S1_Client3_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5040
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5040_STRUCT;

// Address
#define IOHC_SION_S1_Client3_Req_TimeSlot_Lower_ADDRESS                0x13B15044

// Type
#define IOHC_SION_S1_Client3_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5044_IOHC_SION_S1_Client3_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_5044_IOHC_SION_S1_Client3_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_5044_IOHC_SION_S1_Client3_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5044
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5044_STRUCT;

// Address
#define IOHC_SION_S1_Client3_Req_TimeSlot_Upper_ADDRESS                0x13B15048

// Type
#define IOHC_SION_S1_Client3_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5048_IOHC_SION_S1_Client3_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_5048_IOHC_SION_S1_Client3_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_5048_IOHC_SION_S1_Client3_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5048
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5048_STRUCT;

// Address
#define IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_ADDRESS                0x13B1504C

// Type
#define IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_504C_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_504C_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_504C_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_504C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_504C_STRUCT;

// Address
#define IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15050

// Type
#define IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5050_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5050_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5050_IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5050
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client3_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5050_STRUCT;

// Address
#define IOHC_SION_S1_Client4_Req_BurstTarget_Lower_ADDRESS                0x13B15440

// Type
#define IOHC_SION_S1_Client4_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5440_IOHC_SION_S1_Client4_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5440_IOHC_SION_S1_Client4_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5440_IOHC_SION_S1_Client4_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5440
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5440_STRUCT;

// Address
#define IOHC_SION_S1_Client4_Req_BurstTarget_Upper_ADDRESS                0x13B15444

// Type
#define IOHC_SION_S1_Client4_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5444_IOHC_SION_S1_Client4_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5444_IOHC_SION_S1_Client4_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5444_IOHC_SION_S1_Client4_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5444
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5444_STRUCT;

// Address
#define IOHC_SION_S1_Client4_Req_TimeSlot_Lower_ADDRESS                0x13B15448

// Type
#define IOHC_SION_S1_Client4_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5448_IOHC_SION_S1_Client4_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_5448_IOHC_SION_S1_Client4_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_5448_IOHC_SION_S1_Client4_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5448
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5448_STRUCT;

// Address
#define IOHC_SION_S1_Client4_Req_TimeSlot_Upper_ADDRESS                0x13B1544C

// Type
#define IOHC_SION_S1_Client4_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_544C_IOHC_SION_S1_Client4_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_544C_IOHC_SION_S1_Client4_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_544C_IOHC_SION_S1_Client4_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_544C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_544C_STRUCT;

// Address
#define IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15450

// Type
#define IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5450_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5450_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5450_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5450
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5450_STRUCT;

// Address
#define IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15454

// Type
#define IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5454_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5454_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5454_IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5454
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client4_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5454_STRUCT;

// Address
#define IOHC_SION_S1_Client5_Req_BurstTarget_Lower_ADDRESS                0x13B15844

// Type
#define IOHC_SION_S1_Client5_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5844_IOHC_SION_S1_Client5_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5844_IOHC_SION_S1_Client5_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5844_IOHC_SION_S1_Client5_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5844
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5844_STRUCT;

// Address
#define IOHC_SION_S1_Client5_Req_BurstTarget_Upper_ADDRESS                0x13B15848

// Type
#define IOHC_SION_S1_Client5_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5848_IOHC_SION_S1_Client5_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5848_IOHC_SION_S1_Client5_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5848_IOHC_SION_S1_Client5_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5848
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5848_STRUCT;

// Address
#define IOHC_SION_S1_Client6_Req_BurstTarget_Lower_ADDRESS                0x13B15C48

// Type
#define IOHC_SION_S1_Client6_Req_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C48_IOHC_SION_S1_Client6_Req_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5C48_IOHC_SION_S1_Client6_Req_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5C48_IOHC_SION_S1_Client6_Req_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C48
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client6_Req_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C48_STRUCT;

// Address
#define IOHC_SION_S1_Client6_Req_BurstTarget_Upper_ADDRESS                0x13B15C4C

// Type
#define IOHC_SION_S1_Client6_Req_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C4C_IOHC_SION_S1_Client6_Req_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5C4C_IOHC_SION_S1_Client6_Req_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5C4C_IOHC_SION_S1_Client6_Req_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C4C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client6_Req_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C4C_STRUCT;

// Address
#define IOHC_SION_S1_Client5_Req_TimeSlot_Lower_ADDRESS                0x13B1584C

// Type
#define IOHC_SION_S1_Client5_Req_TimeSlot_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_584C_IOHC_SION_S1_Client5_Req_TimeSlot_Lower_OFFSET 0
#define NBIOIOHC_584C_IOHC_SION_S1_Client5_Req_TimeSlot_Lower_WIDTH  32
#define NBIOIOHC_584C_IOHC_SION_S1_Client5_Req_TimeSlot_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_584C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_Req_TimeSlot_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_584C_STRUCT;

// Address
#define IOHC_SION_S1_Client5_Req_TimeSlot_Upper_ADDRESS                0x13B15850

// Type
#define IOHC_SION_S1_Client5_Req_TimeSlot_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5850_IOHC_SION_S1_Client5_Req_TimeSlot_Upper_OFFSET 0
#define NBIOIOHC_5850_IOHC_SION_S1_Client5_Req_TimeSlot_Upper_WIDTH  32
#define NBIOIOHC_5850_IOHC_SION_S1_Client5_Req_TimeSlot_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5850
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_Req_TimeSlot_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5850_STRUCT;

// Address
#define IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15854

// Type
#define IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5854_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5854_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5854_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5854
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5854_STRUCT;

// Address
#define IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15858

// Type
#define IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5858_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5858_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5858_IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5858
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client5_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5858_STRUCT;

// Address
#define IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower_ADDRESS                0x13B15C58

// Type
#define IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C58_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower_OFFSET 0
#define NBIOIOHC_5C58_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower_WIDTH  32
#define NBIOIOHC_5C58_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C58
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client6_RdRsp_BurstTarget_Lower:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C58_STRUCT;

// Address
#define IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper_ADDRESS                0x13B15C5C

// Type
#define IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper_TYPE                   TYPE_IOHC

#define NBIOIOHC_5C5C_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper_OFFSET 0
#define NBIOIOHC_5C5C_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper_WIDTH  32
#define NBIOIOHC_5C5C_IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper_MASK   0xFFFFFFFFF

/// NBIOIOHC_5C5C
typedef union {
  struct {
    UINT32              IOHC_SION_S1_Client6_RdRsp_BurstTarget_Upper:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOIOHC_5C5C_STRUCT;

// Address
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n0_ADDRESS               0x15B00400
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n1_ADDRESS               0x15B00800
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n2_ADDRESS               0x15B00C00
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n3_ADDRESS               0x15B01000

// Type
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n0_ADDRESS               0x15B00404
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n1_ADDRESS               0x15B00804
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n2_ADDRESS               0x15B00C04
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n3_ADDRESS               0x15B01004

// Type
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n0_ADDRESS               0x15B00408
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n1_ADDRESS               0x15B00808
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n2_ADDRESS               0x15B00C08
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n3_ADDRESS               0x15B01008

// Type
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n0_ADDRESS               0x15B0040C
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n1_ADDRESS               0x15B0080C
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n2_ADDRESS               0x15B00C0C
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n3_ADDRESS               0x15B0100C

// Type
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n0_ADDRESS               0x15B00430
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n1_ADDRESS               0x15B00830
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n2_ADDRESS               0x15B00C30
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n3_ADDRESS               0x15B01030

// Type
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n0_ADDRESS               0x15B00434
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n1_ADDRESS               0x15B00834
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n2_ADDRESS               0x15B00C34
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n3_ADDRESS               0x15B01034

// Type
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS               0x15B00410
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS               0x15B00810
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS               0x15B00C10
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS               0x15B01010

// Type
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS               0x15B00414
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS               0x15B00814
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS               0x15B00C14
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS               0x15B01014

// Type
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS               0x15B00440
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS               0x15B00840
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS               0x15B00C40
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS               0x15B01040

// Type
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC

// Address
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS               0x15B00444
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS               0x15B00844
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS               0x15B00C44
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS               0x15B01044

// Type
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n0_ADDRESS               0x04400400
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n1_ADDRESS               0x04400800
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n2_ADDRESS               0x04400C00
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n3_ADDRESS               0x04401000
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n4_ADDRESS               0x04401400

// Type
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Lower_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n0_ADDRESS               0x04400404
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n1_ADDRESS               0x04400804
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n2_ADDRESS               0x04400C04
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n3_ADDRESS               0x04401004
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n4_ADDRESS               0x04401404

// Type
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_BurstTarget_Upper_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n0_ADDRESS               0x04400408
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n1_ADDRESS               0x04400808
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n2_ADDRESS               0x04400C08
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n3_ADDRESS               0x04401008
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n4_ADDRESS               0x04401408

// Type
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Lower_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n0_ADDRESS               0x0440040C
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n1_ADDRESS               0x0440080C
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n2_ADDRESS               0x04400C0C
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n3_ADDRESS               0x0440100C
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n4_ADDRESS               0x0440140C

// Type
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_Req_TimeSlot_Upper_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n0_ADDRESS               0x04400430
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n1_ADDRESS               0x04400830
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n2_ADDRESS               0x04400C30
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n3_ADDRESS               0x04401030
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n4_ADDRESS               0x04401430

// Type
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Lower_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n0_ADDRESS               0x04400434
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n1_ADDRESS               0x04400834
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n2_ADDRESS               0x04400C34
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n3_ADDRESS               0x04401034
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n4_ADDRESS               0x04401434

// Type
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_Req_BurstTarget_Upper_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS               0x04400410
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS               0x04400810
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS               0x04400C10
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS               0x04401010
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n4_ADDRESS               0x04401410

// Type
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Lower_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS               0x04400414
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS               0x04400814
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS               0x04400C14
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS               0x04401014
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n4_ADDRESS               0x04401414

// Type
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S0_Client_RdRsp_BurstTarget_Upper_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS               0x04400440
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS               0x04400840
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS               0x04400C40
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS               0x04401040
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n4_ADDRESS               0x04401440

// Type
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Lower_n4_TYPE                  TYPE_IOHC

// Address
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS               0x04400444
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS               0x04400844
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS               0x04400C44
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS               0x04401044
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n4_ADDRESS               0x04401444

// Type
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_TYPE                  TYPE_IOHC
#define SDPMUX_SION_S1_Client_RdRsp_BurstTarget_Upper_n4_TYPE                  TYPE_IOHC

// Address
#define PARITY_CONTROL_0_ADDRESS                               0x13b20000

// Type
#define PARITY_CONTROL_0_TYPE                                  TYPE_NBRASCFG

#define NBRASCFG_0000_ParityCorrThreshold_OFFSET               0
#define NBRASCFG_0000_ParityCorrThreshold_WIDTH                16
#define NBRASCFG_0000_ParityCorrThreshold_MASK                 0xffff
#define NBRASCFG_0000_ParityUCPThreshold_OFFSET                16
#define NBRASCFG_0000_ParityUCPThreshold_WIDTH                 16
#define NBRASCFG_0000_ParityUCPThreshold_MASK                  0xffff0000L

/// NBRASCFG_0000
typedef union {
  struct {
    UINT32                                     ParityCorrThreshold:16; ///<
    UINT32                                      ParityUCPThreshold:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0000_STRUCT;

// Address
#define PARITY_CONTROL_1_ADDRESS                               0x13b20004

// Type
#define PARITY_CONTROL_1_TYPE                                  TYPE_NBRASCFG

#define NBRASCFG_0004_ParityErrGenGroupSel_OFFSET              0
#define NBRASCFG_0004_ParityErrGenGroupSel_WIDTH               8
#define NBRASCFG_0004_ParityErrGenGroupSel_MASK                0xff
#define NBRASCFG_0004_ParityErrGenGroupTypeSel_OFFSET          8
#define NBRASCFG_0004_ParityErrGenGroupTypeSel_WIDTH           1
#define NBRASCFG_0004_ParityErrGenGroupTypeSel_MASK            0x100
#define NBRASCFG_0004_Reserved_10_9_OFFSET                     9
#define NBRASCFG_0004_Reserved_10_9_WIDTH                      2
#define NBRASCFG_0004_Reserved_10_9_MASK                       0x600
#define NBRASCFG_0004_ParityErrGenIdSel_OFFSET                 11
#define NBRASCFG_0004_ParityErrGenIdSel_WIDTH                  5
#define NBRASCFG_0004_ParityErrGenIdSel_MASK                   0xf800
#define NBRASCFG_0004_ParityErrGenCmd_OFFSET                   16
#define NBRASCFG_0004_ParityErrGenCmd_WIDTH                    4
#define NBRASCFG_0004_ParityErrGenCmd_MASK                     0xf0000
#define NBRASCFG_0004_Reserved_29_20_OFFSET                    20
#define NBRASCFG_0004_Reserved_29_20_WIDTH                     10
#define NBRASCFG_0004_Reserved_29_20_MASK                      0x3ff00000
#define NBRASCFG_0004_ParityErrGenTrigger_OFFSET               30
#define NBRASCFG_0004_ParityErrGenTrigger_WIDTH                1
#define NBRASCFG_0004_ParityErrGenTrigger_MASK                 0x40000000
#define NBRASCFG_0004_ParityErrGenInjectAllow_OFFSET           31
#define NBRASCFG_0004_ParityErrGenInjectAllow_WIDTH            1
#define NBRASCFG_0004_ParityErrGenInjectAllow_MASK             0x80000000L

/// NBRASCFG_0004
typedef union {
  struct {
    UINT32                                    ParityErrGenGroupSel:8 ; ///<
    UINT32                                ParityErrGenGroupTypeSel:1 ; ///<
    UINT32                                           Reserved_10_9:2 ; ///<
    UINT32                                       ParityErrGenIdSel:5 ; ///<
    UINT32                                         ParityErrGenCmd:4 ; ///<
    UINT32                                          Reserved_29_20:10; ///<
    UINT32                                     ParityErrGenTrigger:1 ; ///<
    UINT32                                 ParityErrGenInjectAllow:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0004_STRUCT;

// Address
#define PARITY_SEVERITY_CONTROL_UNCORR_0_ADDRESS               0x13b20008

// Type
#define PARITY_SEVERITY_CONTROL_UNCORR_0_TYPE                  TYPE_NBRASCFG

#define NBRASCFG_0008_ParityErrSevUnCorrGrp0_OFFSET            0
#define NBRASCFG_0008_ParityErrSevUnCorrGrp0_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp0_MASK              0x3
#define NBRASCFG_0008_ParityErrSevUnCorrGrp1_OFFSET            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp1_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp1_MASK              0xc
#define NBRASCFG_0008_ParityErrSevUnCorrGrp2_OFFSET            4
#define NBRASCFG_0008_ParityErrSevUnCorrGrp2_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp2_MASK              0x30
#define NBRASCFG_0008_ParityErrSevUnCorrGrp3_OFFSET            6
#define NBRASCFG_0008_ParityErrSevUnCorrGrp3_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp3_MASK              0xc0
#define NBRASCFG_0008_ParityErrSevUnCorrGrp4_OFFSET            8
#define NBRASCFG_0008_ParityErrSevUnCorrGrp4_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp4_MASK              0x300
#define NBRASCFG_0008_ParityErrSevUnCorrGrp5_OFFSET            10
#define NBRASCFG_0008_ParityErrSevUnCorrGrp5_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp5_MASK              0xc00
#define NBRASCFG_0008_ParityErrSevUnCorrGrp6_OFFSET            12
#define NBRASCFG_0008_ParityErrSevUnCorrGrp6_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp6_MASK              0x3000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp7_OFFSET            14
#define NBRASCFG_0008_ParityErrSevUnCorrGrp7_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp7_MASK              0xc000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp8_OFFSET            16
#define NBRASCFG_0008_ParityErrSevUnCorrGrp8_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp8_MASK              0x30000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp9_OFFSET            18
#define NBRASCFG_0008_ParityErrSevUnCorrGrp9_WIDTH             2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp9_MASK              0xc0000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp10_OFFSET           20
#define NBRASCFG_0008_ParityErrSevUnCorrGrp10_WIDTH            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp10_MASK             0x300000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp11_OFFSET           22
#define NBRASCFG_0008_ParityErrSevUnCorrGrp11_WIDTH            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp11_MASK             0xc00000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp12_OFFSET           24
#define NBRASCFG_0008_ParityErrSevUnCorrGrp12_WIDTH            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp12_MASK             0x3000000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp13_OFFSET           26
#define NBRASCFG_0008_ParityErrSevUnCorrGrp13_WIDTH            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp13_MASK             0xc000000
#define NBRASCFG_0008_ParityErrSevUnCorrGrp14_OFFSET           28
#define NBRASCFG_0008_ParityErrSevUnCorrGrp14_WIDTH            2
#define NBRASCFG_0008_ParityErrSevUnCorrGrp14_MASK             0x30000000

/// NBRASCFG_0008
typedef union {
  struct {
    UINT32                                  ParityErrSevUnCorrGrp0:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp1:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp2:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp3:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp4:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp5:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp6:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp7:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp8:2 ; ///<
    UINT32                                  ParityErrSevUnCorrGrp9:2 ; ///<
    UINT32                                 ParityErrSevUnCorrGrp10:2 ; ///<
    UINT32                                 ParityErrSevUnCorrGrp11:2 ; ///<
    UINT32                                 ParityErrSevUnCorrGrp12:2 ; ///<
    UINT32                                 ParityErrSevUnCorrGrp13:2 ; ///<
    UINT32                                 ParityErrSevUnCorrGrp14:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0008_STRUCT;


// Address
#define PARITY_SEVERITY_CONTROL_CORR_0_ADDRESS                 0x13b20010

// Type
#define PARITY_SEVERITY_CONTROL_CORR_0_TYPE                    TYPE_NBRASCFG

#define NBRASCFG_0010_ParityErrSevCorrGrp0_OFFSET              0
#define NBRASCFG_0010_ParityErrSevCorrGrp0_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp0_MASK                0x3
#define NBRASCFG_0010_ParityErrSevCorrGrp1_OFFSET              2
#define NBRASCFG_0010_ParityErrSevCorrGrp1_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp1_MASK                0xc
#define NBRASCFG_0010_ParityErrSevCorrGrp2_OFFSET              4
#define NBRASCFG_0010_ParityErrSevCorrGrp2_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp2_MASK                0x30
#define NBRASCFG_0010_ParityErrSevCorrGrp3_OFFSET              6
#define NBRASCFG_0010_ParityErrSevCorrGrp3_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp3_MASK                0xc0
#define NBRASCFG_0010_ParityErrSevCorrGrp4_OFFSET              8
#define NBRASCFG_0010_ParityErrSevCorrGrp4_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp4_MASK                0x300
#define NBRASCFG_0010_ParityErrSevCorrGrp5_OFFSET              10
#define NBRASCFG_0010_ParityErrSevCorrGrp5_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp5_MASK                0xc00
#define NBRASCFG_0010_ParityErrSevCorrGrp6_OFFSET              12
#define NBRASCFG_0010_ParityErrSevCorrGrp6_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp6_MASK                0x3000
#define NBRASCFG_0010_ParityErrSevCorrGrp7_OFFSET              14
#define NBRASCFG_0010_ParityErrSevCorrGrp7_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp7_MASK                0xc000
#define NBRASCFG_0010_ParityErrSevCorrGrp8_OFFSET              16
#define NBRASCFG_0010_ParityErrSevCorrGrp8_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp8_MASK                0x30000
#define NBRASCFG_0010_ParityErrSevCorrGrp9_OFFSET              18
#define NBRASCFG_0010_ParityErrSevCorrGrp9_WIDTH               2
#define NBRASCFG_0010_ParityErrSevCorrGrp9_MASK                0xc0000
#define NBRASCFG_0010_ParityErrSevCorrGrp10_OFFSET             20
#define NBRASCFG_0010_ParityErrSevCorrGrp10_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp10_MASK               0x300000
#define NBRASCFG_0010_ParityErrSevCorrGrp11_OFFSET             22
#define NBRASCFG_0010_ParityErrSevCorrGrp11_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp11_MASK               0xc00000
#define NBRASCFG_0010_ParityErrSevCorrGrp12_OFFSET             24
#define NBRASCFG_0010_ParityErrSevCorrGrp12_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp12_MASK               0x3000000
#define NBRASCFG_0010_ParityErrSevCorrGrp13_OFFSET             26
#define NBRASCFG_0010_ParityErrSevCorrGrp13_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp13_MASK               0xc000000
#define NBRASCFG_0010_ParityErrSevCorrGrp14_OFFSET             28
#define NBRASCFG_0010_ParityErrSevCorrGrp14_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp14_MASK               0x30000000
#define NBRASCFG_0010_ParityErrSevCorrGrp15_OFFSET             30
#define NBRASCFG_0010_ParityErrSevCorrGrp15_WIDTH              2
#define NBRASCFG_0010_ParityErrSevCorrGrp15_MASK               0xc0000000L

/// NBRASCFG_0010
typedef union {
  struct {
    UINT32                                    ParityErrSevCorrGrp0:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp1:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp2:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp3:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp4:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp5:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp6:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp7:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp8:2 ; ///<
    UINT32                                    ParityErrSevCorrGrp9:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp10:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp11:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp12:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp13:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp14:2 ; ///<
    UINT32                                   ParityErrSevCorrGrp15:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0010_STRUCT;


// Address
#define PARITY_SEVERITY_CONTROL_CORR_1_ADDRESS                 0x13b20014

// Type
#define PARITY_SEVERITY_CONTROL_CORR_1_TYPE                    TYPE_NBRASCFG

#define NBRASCFG_0014_ParityErrSevCorrGrp16_OFFSET             0
#define NBRASCFG_0014_ParityErrSevCorrGrp16_WIDTH              2
#define NBRASCFG_0014_ParityErrSevCorrGrp16_MASK               0x3

/// NBRASCFG_0014
typedef union {
  struct {
    UINT32                                   ParityErrSevCorrGrp16:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0014_STRUCT;

// Address
#define PARITY_SEVERITY_CONTROL_UCP_0_ADDRESS                  0x13b20018

// Type
#define PARITY_SEVERITY_CONTROL_UCP_0_TYPE                     TYPE_NBRASCFG

#define NBRASCFG_0018_ParityErrSevUCPGrp0_OFFSET               0
#define NBRASCFG_0018_ParityErrSevUCPGrp0_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp0_MASK                 0x3
#define NBRASCFG_0018_ParityErrSevUCPGrp1_OFFSET               2
#define NBRASCFG_0018_ParityErrSevUCPGrp1_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp1_MASK                 0xc
#define NBRASCFG_0018_ParityErrSevUCPGrp2_OFFSET               4
#define NBRASCFG_0018_ParityErrSevUCPGrp2_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp2_MASK                 0x30
#define NBRASCFG_0018_ParityErrSevUCPGrp3_OFFSET               6
#define NBRASCFG_0018_ParityErrSevUCPGrp3_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp3_MASK                 0xc0
#define NBRASCFG_0018_ParityErrSevUCPGrp4_OFFSET               8
#define NBRASCFG_0018_ParityErrSevUCPGrp4_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp4_MASK                 0x300
#define NBRASCFG_0018_ParityErrSevUCPGrp5_OFFSET               10
#define NBRASCFG_0018_ParityErrSevUCPGrp5_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp5_MASK                 0xc00
#define NBRASCFG_0018_ParityErrSevUCPGrp6_OFFSET               12
#define NBRASCFG_0018_ParityErrSevUCPGrp6_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp6_MASK                 0x3000
#define NBRASCFG_0018_ParityErrSevUCPGrp7_OFFSET               14
#define NBRASCFG_0018_ParityErrSevUCPGrp7_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp7_MASK                 0xc000
#define NBRASCFG_0018_ParityErrSevUCPGrp8_OFFSET               16
#define NBRASCFG_0018_ParityErrSevUCPGrp8_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp8_MASK                 0x30000
#define NBRASCFG_0018_ParityErrSevUCPGrp9_OFFSET               18
#define NBRASCFG_0018_ParityErrSevUCPGrp9_WIDTH                2
#define NBRASCFG_0018_ParityErrSevUCPGrp9_MASK                 0xc0000
#define NBRASCFG_0018_ParityErrSevUCPGrp10_OFFSET              20
#define NBRASCFG_0018_ParityErrSevUCPGrp10_WIDTH               2
#define NBRASCFG_0018_ParityErrSevUCPGrp10_MASK                0x300000

/// NBRASCFG_0018
typedef union {
  struct {
    UINT32                                     ParityErrSevUCPGrp0:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp1:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp2:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp3:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp4:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp5:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp6:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp7:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp8:2 ; ///<
    UINT32                                     ParityErrSevUCPGrp9:2 ; ///<
    UINT32                                    ParityErrSevUCPGrp10:2 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0018_STRUCT;

// Address
#define ErrEvent_ACTION_CONTROL_ADDRESS                        0x13b20168

// Type
#define ErrEvent_ACTION_CONTROL_TYPE                           TYPE_SMN

#define ErrEvent_ACTION_CONTROL_APML_ERR_En_OFFSET             0
#define ErrEvent_ACTION_CONTROL_APML_ERR_En_WIDTH              1
#define ErrEvent_ACTION_CONTROL_APML_ERR_En_MASK               0x1
#define ErrEvent_ACTION_CONTROL_IntrGenSel_OFFSET              1
#define ErrEvent_ACTION_CONTROL_IntrGenSel_WIDTH               2
#define ErrEvent_ACTION_CONTROL_IntrGenSel_MASK                0x6
#define ErrEvent_ACTION_CONTROL_LinkDis_En_OFFSET              3
#define ErrEvent_ACTION_CONTROL_LinkDis_En_WIDTH               1
#define ErrEvent_ACTION_CONTROL_LinkDis_En_MASK                0x8
#define ErrEvent_ACTION_CONTROL_SyncFlood_En_OFFSET            4
#define ErrEvent_ACTION_CONTROL_SyncFlood_En_WIDTH             1
#define ErrEvent_ACTION_CONTROL_SyncFlood_En_MASK              0x10
#define ErrEvent_ACTION_CONTROL_Reserved_31_5_OFFSET           5
#define ErrEvent_ACTION_CONTROL_Reserved_31_5_WIDTH            27
#define ErrEvent_ACTION_CONTROL_Reserved_31_5_MASK             0xffffffe0L

/// IOHCRAS_00000168
typedef union {
  struct {
    UINT32                                             APML_ERR_En:1 ; ///<
    UINT32                                              IntrGenSel:2 ; ///<
    UINT32                                              LinkDis_En:1 ; ///<
    UINT32                                            SyncFlood_En:1 ; ///<
    UINT32                                           Reserved_31_5:27; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} ErrEvent_ACTION_CONTROL_STRUCT;

#define MISC_SEVERITY_CONTROL_ADDRESS                          0x13b20158
#define ParitySerr_ACTION_CONTROL_ADDRESS                      0x13b2016c
#define ParityFatal_ACTION_CONTROL_ADDRESS                     0x13b20170
#define ParityNonFatal_ACTION_CONTROL_ADDRESS                  0x13b20174
#define ParityCorr_ACTION_CONTROL_ADDRESS                      0x13b20178
#define EGRESS_POISON_SEVERITY_LO_ADDRESS                      0x13b20430
#define EGRESS_POISON_SEVERITY_HI_ADDRESS                      0x13b20434

// Address
#define POISON_ACTION_CONTROL_ADDRESS                          0x13b20400

// Type
#define POISON_ACTION_CONTROL_TYPE                             TYPE_NBRASCFG

#define NBRASCFG_0400_IntPoisonAPMLErrEn_OFFSET                0
#define NBRASCFG_0400_IntPoisonAPMLErrEn_WIDTH                 1
#define NBRASCFG_0400_IntPoisonAPMLErrEn_MASK                  0x1
#define NBRASCFG_0400_IntPoisonIntrGenSel_OFFSET               1
#define NBRASCFG_0400_IntPoisonIntrGenSel_WIDTH                2
#define NBRASCFG_0400_IntPoisonIntrGenSel_MASK                 0x6
#define NBRASCFG_0400_IntPoisonLinkDisEn_OFFSET                3
#define NBRASCFG_0400_IntPoisonLinkDisEn_WIDTH                 1
#define NBRASCFG_0400_IntPoisonLinkDisEn_MASK                  0x8
#define NBRASCFG_0400_IntPoisonSyncFloodEn_OFFSET              4
#define NBRASCFG_0400_IntPoisonSyncFloodEn_WIDTH               1
#define NBRASCFG_0400_IntPoisonSyncFloodEn_MASK                0x10
#define NBRASCFG_0400_Reserved_7_5_OFFSET                      5
#define NBRASCFG_0400_Reserved_7_5_WIDTH                       3
#define NBRASCFG_0400_Reserved_7_5_MASK                        0xE0
#define NBRASCFG_0400_EgressPoisonLSAPMLErrEn_OFFSET           8
#define NBRASCFG_0400_EgressPoisonLSAPMLErrEn_WIDTH            1
#define NBRASCFG_0400_EgressPoisonLSAPMLErrEn_MASK             0x100
#define NBRASCFG_0400_EgressPoisonLSIntrGenSel_OFFSET          9
#define NBRASCFG_0400_EgressPoisonLSIntrGenSel_WIDTH           2
#define NBRASCFG_0400_EgressPoisonLSIntrGenSel_MASK            0x600
#define NBRASCFG_0400_EgressPoisonLSLinkDisEn_OFFSET           11
#define NBRASCFG_0400_EgressPoisonLSLinkDisEn_WIDTH            1
#define NBRASCFG_0400_EgressPoisonLSLinkDisEn_MASK             0x800
#define NBRASCFG_0400_EgressPoisonLSSyncFloodEn_OFFSET         12
#define NBRASCFG_0400_EgressPoisonLSSyncFloodEn_WIDTH          1
#define NBRASCFG_0400_EgressPoisonLSSyncFloodEn_MASK           0x1000
#define NBRASCFG_0400_Reserved_15_13_OFFSET                    13
#define NBRASCFG_0400_Reserved_15_13_WIDTH                     3
#define NBRASCFG_0400_Reserved_15_13_MASK                      0xE000
#define NBRASCFG_0400_EgressPoisonHSAPMLErrEn_OFFSET           16
#define NBRASCFG_0400_EgressPoisonHSAPMLErrEn_WIDTH            1
#define NBRASCFG_0400_EgressPoisonHSAPMLErrEn_MASK             0x10000
#define NBRASCFG_0400_EgressPoisonHSIntrGenSel_OFFSET          17
#define NBRASCFG_0400_EgressPoisonHSIntrGenSel_WIDTH           2
#define NBRASCFG_0400_EgressPoisonHSIntrGenSel_MASK            0x60000
#define NBRASCFG_0400_EgressPoisonHSLinkDisEn_OFFSET           19
#define NBRASCFG_0400_EgressPoisonHSLinkDisEn_WIDTH            1
#define NBRASCFG_0400_EgressPoisonHSLinkDisEn_MASK             0x80000
#define NBRASCFG_0400_EgressPoisonHSSyncFloodEn_OFFSET         20
#define NBRASCFG_0400_EgressPoisonHSSyncFloodEn_WIDTH          1
#define NBRASCFG_0400_EgressPoisonHSSyncFloodEn_MASK           0x100000
#define NBRASCFG_0400_Reserved_31_21_OFFSET                    21
#define NBRASCFG_0400_Reserved_31_21_WIDTH                     11
#define NBRASCFG_0400_Reserved_31_21_MASK                      0xFFE00000

/// NBRASCFG_0400
typedef union {
  struct {
    UINT32                                      IntPoisonAPMLErrEn:1 ; ///<
    UINT32                                     IntPoisonIntrGenSel:2 ; ///<
    UINT32                                      IntPoisonLinkDisEn:1 ; ///<
    UINT32                                    IntPoisonSyncFloodEn:1 ; ///<
    UINT32                                            Reserved_7_5:3 ; ///<
    UINT32                                 EgressPoisonLSAPMLErrEn:1 ; ///<
    UINT32                                EgressPoisonLSIntrGenSel:2 ; ///<
    UINT32                                 EgressPoisonLSLinkDisEn:1 ; ///<
    UINT32                               EgressPoisonLSSyncFloodEn:1 ; ///<
    UINT32                                          Reserved_15_13:3 ; ///<
    UINT32                                 EgressPoisonHSAPMLErrEn:1 ; ///<
    UINT32                                EgressPoisonHSIntrGenSel:2 ; ///<
    UINT32                                 EgressPoisonHSLinkDisEn:1 ; ///<
    UINT32                               EgressPoisonHSSyncFloodEn:1 ; ///<
    UINT32                                          Reserved_31_21:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBRASCFG_0400_STRUCT;

//    IOHUB::IOMMUL2::IOMMU_CAP_BASE_LO_aliasSMN;
// Address
#define IOMMU_CAP_BASE_LO_ADDRESS                              0x13f00044

// Type
#define IOMMU_CAP_BASE_LO_TYPE                                 TYPE_SMN

#define SMN_00000044_IOMMU_ENABLE_OFFSET                       0
#define SMN_00000044_IOMMU_ENABLE_WIDTH                        1
#define SMN_00000044_IOMMU_ENABLE_MASK                         0x1
#define SMN_00000044_Reserved_13_1_OFFSET                      1
#define SMN_00000044_Reserved_13_1_WIDTH                       13
#define SMN_00000044_Reserved_13_1_MASK                        0x3ffe
#define SMN_00000044_IOMMU_BASE_ADDR_LO_OFFSET                 19
#define SMN_00000044_IOMMU_BASE_ADDR_LO_WIDTH                  13
#define SMN_00000044_IOMMU_BASE_ADDR_LO_MASK                   0xfff80000L

/// SMN_00000044
typedef union {
  struct {
    UINT32                                            IOMMU_ENABLE:1 ; ///<
    UINT32                                           Reserved_13_1:13; ///<
    UINT32                                      IOMMU_BASE_ADDR_LO:13; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000044_STRUCT;


// Register Name IOMMU_CONTROL_W

// Address
#define IOMMU_CONTROL_W_ADDRESS                                           0x13f0007c

// Type
#define IOMMU_CONTROL_W_TYPE                                              TYPE_SMN

#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_OFFSET                            0
#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_WIDTH                             3
#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_MASK                              0x7
#define IOMMU_CONTROL_W_Reserved_3_3_OFFSET                               3
#define IOMMU_CONTROL_W_Reserved_3_3_WIDTH                                1
#define IOMMU_CONTROL_W_Reserved_3_3_MASK                                 0x8
#define IOMMU_CONTROL_W_MINOR_REV_ID_W_OFFSET                             4
#define IOMMU_CONTROL_W_MINOR_REV_ID_W_WIDTH                              4
#define IOMMU_CONTROL_W_MINOR_REV_ID_W_MASK                               0xf0
#define IOMMU_CONTROL_W_IO_TLBSUP_W_OFFSET                                8
#define IOMMU_CONTROL_W_IO_TLBSUP_W_WIDTH                                 1
#define IOMMU_CONTROL_W_IO_TLBSUP_W_MASK                                  0x100
#define IOMMU_CONTROL_W_EFR_SUP_W_OFFSET                                  9
#define IOMMU_CONTROL_W_EFR_SUP_W_WIDTH                                   1
#define IOMMU_CONTROL_W_EFR_SUP_W_MASK                                    0x200
#define IOMMU_CONTROL_W_MSI_MULT_MESS_CAP_W_OFFSET                        10
#define IOMMU_CONTROL_W_MSI_MULT_MESS_CAP_W_WIDTH                         3
#define IOMMU_CONTROL_W_MSI_MULT_MESS_CAP_W_MASK                          0x1c00
#define IOMMU_CONTROL_W_IOMMU_CAP_EXT_W_OFFSET                            13
#define IOMMU_CONTROL_W_IOMMU_CAP_EXT_W_WIDTH                             1
#define IOMMU_CONTROL_W_IOMMU_CAP_EXT_W_MASK                              0x2000
#define IOMMU_CONTROL_W_Reserved_31_14_OFFSET                             14
#define IOMMU_CONTROL_W_Reserved_31_14_WIDTH                              18
#define IOMMU_CONTROL_W_Reserved_31_14_MASK                               0xffffc000L

/// IOMMU_CONTROL_W
typedef union {
  struct {
    UINT32                                         INTERRUPT_PIN_W:3 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                          MINOR_REV_ID_W:4 ; ///<
    UINT32                                             IO_TLBSUP_W:1 ; ///<
    UINT32                                               EFR_SUP_W:1 ; ///<
    UINT32                                     MSI_MULT_MESS_CAP_W:3 ; ///<
    UINT32                                         IOMMU_CAP_EXT_W:1 ; ///<
    UINT32                                          Reserved_31_14:18; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMU_CONTROL_W_STRUCT;

//    svd_group: IOHC_instINTSBDEVINDCFG0_aliasSMN
//Group Base = 0x13B30000

// Register Name IOHC_Bridge_CNTL

// Address
#define SMN_0x13B3C004_ADDRESS                                 0x13B3C004

// Type
#define SMN_0x13B3C004_TYPE                                    TYPE_SMN

#define SMN_0x13B3C004_BridgeDis_OFFSET                        0
#define SMN_0x13B3C004_BridgeDis_WIDTH                         1
#define SMN_0x13B3C004_BridgeDis_MASK                          0x1
#define SMN_0x13B3C004_BusMasterDis_OFFSET                     1
#define SMN_0x13B3C004_BusMasterDis_WIDTH                      1
#define SMN_0x13B3C004_BusMasterDis_MASK                       0x2
#define SMN_0x13B3C004_CfgDis_OFFSET                           2
#define SMN_0x13B3C004_CfgDis_WIDTH                            1
#define SMN_0x13B3C004_CfgDis_MASK                             0x4
#define SMN_0x13B3C004_P2pDis_OFFSET                           3
#define SMN_0x13B3C004_P2pDis_WIDTH                            1
#define SMN_0x13B3C004_P2pDis_MASK                             0x8
#define SMN_0x13B3C004_VDMDis_OFFSET                           5
#define SMN_0x13B3C004_VDMDis_WIDTH                            1
#define SMN_0x13B3C004_VDMDis_MASK                             0x20
#define SMN_0x13B3C004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B3C004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B3C004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B3C004_PassPWDis_OFFSET                        7
#define SMN_0x13B3C004_PassPWDis_WIDTH                         1
#define SMN_0x13B3C004_PassPWDis_MASK                          0x80
#define SMN_0x13B3C004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B3C004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B3C004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B3C004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B3C004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B3C004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B3C004_IDOMode_OFFSET                          10
#define SMN_0x13B3C004_IDOMode_WIDTH                           2
#define SMN_0x13B3C004_IDOMode_MASK                            0xc00
#define SMN_0x13B3C004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B3C004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B3C004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B3C004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B3C004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B3C004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B3C004_CrsEnable_OFFSET                        18
#define SMN_0x13B3C004_CrsEnable_WIDTH                         1
#define SMN_0x13B3C004_CrsEnable_MASK                          0x40000
#define SMN_0x13B3C004_APIC_Enable_OFFSET                      23
#define SMN_0x13B3C004_APIC_Enable_WIDTH                       1
#define SMN_0x13B3C004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B3C004_APIC_Range_OFFSET                       24
#define SMN_0x13B3C004_APIC_Range_WIDTH                        8
#define SMN_0x13B3C004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_0000C004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B3C004_STRUCT;

// Register Name IOHC_Bridge_CNTL

// Address
#define SMN_0x13B38004_ADDRESS                                 0x13B38004

// Type
#define SMN_0x13B38004_TYPE                                    TYPE_SMN

#define SMN_0x13B38004_BridgeDis_OFFSET                        0
#define SMN_0x13B38004_BridgeDis_WIDTH                         1
#define SMN_0x13B38004_BridgeDis_MASK                          0x1
#define SMN_0x13B38004_BusMasterDis_OFFSET                     1
#define SMN_0x13B38004_BusMasterDis_WIDTH                      1
#define SMN_0x13B38004_BusMasterDis_MASK                       0x2
#define SMN_0x13B38004_CfgDis_OFFSET                           2
#define SMN_0x13B38004_CfgDis_WIDTH                            1
#define SMN_0x13B38004_CfgDis_MASK                             0x4
#define SMN_0x13B38004_P2pDis_OFFSET                           3
#define SMN_0x13B38004_P2pDis_WIDTH                            1
#define SMN_0x13B38004_P2pDis_MASK                             0x8
#define SMN_0x13B38004_VDMDis_OFFSET                           5
#define SMN_0x13B38004_VDMDis_WIDTH                            1
#define SMN_0x13B38004_VDMDis_MASK                             0x20
#define SMN_0x13B38004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B38004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B38004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B38004_PassPWDis_OFFSET                        7
#define SMN_0x13B38004_PassPWDis_WIDTH                         1
#define SMN_0x13B38004_PassPWDis_MASK                          0x80
#define SMN_0x13B38004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B38004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B38004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B38004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B38004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B38004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B38004_IDOMode_OFFSET                          10
#define SMN_0x13B38004_IDOMode_WIDTH                           2
#define SMN_0x13B38004_IDOMode_MASK                            0xc00
#define SMN_0x13B38004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B38004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B38004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B38004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B38004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B38004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B38004_CrsEnable_OFFSET                        18
#define SMN_0x13B38004_CrsEnable_WIDTH                         1
#define SMN_0x13B38004_CrsEnable_MASK                          0x40000
#define SMN_0x13B38004_APIC_Enable_OFFSET                      23
#define SMN_0x13B38004_APIC_Enable_WIDTH                       1
#define SMN_0x13B38004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B38004_APIC_Range_OFFSET                       24
#define SMN_0x13B38004_APIC_Range_WIDTH                        8
#define SMN_0x13B38004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00008004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B38004_STRUCT;

//    svd_group: IOHC_instNBIF1DEVINDCFG0_aliasSMN
//Group Base = 0x13B30000

// Register Name IOHC_Bridge_CNTL

// Address
#define SMN_0x13B39004_ADDRESS                                 0x13B39004

// Type
#define SMN_0x13B39004_TYPE                                    TYPE_SMN

#define SMN_0x13B39004_BridgeDis_OFFSET                        0
#define SMN_0x13B39004_BridgeDis_WIDTH                         1
#define SMN_0x13B39004_BridgeDis_MASK                          0x1
#define SMN_0x13B39004_BusMasterDis_OFFSET                     1
#define SMN_0x13B39004_BusMasterDis_WIDTH                      1
#define SMN_0x13B39004_BusMasterDis_MASK                       0x2
#define SMN_0x13B39004_CfgDis_OFFSET                           2
#define SMN_0x13B39004_CfgDis_WIDTH                            1
#define SMN_0x13B39004_CfgDis_MASK                             0x4
#define SMN_0x13B39004_P2pDis_OFFSET                           3
#define SMN_0x13B39004_P2pDis_WIDTH                            1
#define SMN_0x13B39004_P2pDis_MASK                             0x8
#define SMN_0x13B39004_VDMDis_OFFSET                           5
#define SMN_0x13B39004_VDMDis_WIDTH                            1
#define SMN_0x13B39004_VDMDis_MASK                             0x20
#define SMN_0x13B39004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B39004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B39004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B39004_PassPWDis_OFFSET                        7
#define SMN_0x13B39004_PassPWDis_WIDTH                         1
#define SMN_0x13B39004_PassPWDis_MASK                          0x80
#define SMN_0x13B39004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B39004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B39004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B39004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B39004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B39004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B39004_IDOMode_OFFSET                          10
#define SMN_0x13B39004_IDOMode_WIDTH                           2
#define SMN_0x13B39004_IDOMode_MASK                            0xc00
#define SMN_0x13B39004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B39004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B39004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B39004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B39004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B39004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B39004_CrsEnable_OFFSET                        18
#define SMN_0x13B39004_CrsEnable_WIDTH                         1
#define SMN_0x13B39004_CrsEnable_MASK                          0x40000
#define SMN_0x13B39004_APIC_Enable_OFFSET                      23
#define SMN_0x13B39004_APIC_Enable_WIDTH                       1
#define SMN_0x13B39004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B39004_APIC_Range_OFFSET                       24
#define SMN_0x13B39004_APIC_Range_WIDTH                        8
#define SMN_0x13B39004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00009004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B39004_STRUCT;

//    svd_group: IOHC_instPCIE0DEVINDCFG0_aliasSMN
//Group Base = 0x13B30000

// Register Name IOHC_Bridge_CNTL

// Address
#define SMN_0x13B31004_ADDRESS                                 0x13B31004

// Type
#define SMN_0x13B31004_TYPE                                    TYPE_SMN

#define SMN_0x13B31004_BridgeDis_OFFSET                        0
#define SMN_0x13B31004_BridgeDis_WIDTH                         1
#define SMN_0x13B31004_BridgeDis_MASK                          0x1
#define SMN_0x13B31004_BusMasterDis_OFFSET                     1
#define SMN_0x13B31004_BusMasterDis_WIDTH                      1
#define SMN_0x13B31004_BusMasterDis_MASK                       0x2
#define SMN_0x13B31004_CfgDis_OFFSET                           2
#define SMN_0x13B31004_CfgDis_WIDTH                            1
#define SMN_0x13B31004_CfgDis_MASK                             0x4
#define SMN_0x13B31004_P2pDis_OFFSET                           3
#define SMN_0x13B31004_P2pDis_WIDTH                            1
#define SMN_0x13B31004_P2pDis_MASK                             0x8
#define SMN_0x13B31004_VDMDis_OFFSET                           5
#define SMN_0x13B31004_VDMDis_WIDTH                            1
#define SMN_0x13B31004_VDMDis_MASK                             0x20
#define SMN_0x13B31004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B31004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B31004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B31004_PassPWDis_OFFSET                        7
#define SMN_0x13B31004_PassPWDis_WIDTH                         1
#define SMN_0x13B31004_PassPWDis_MASK                          0x80
#define SMN_0x13B31004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B31004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B31004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B31004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B31004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B31004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B31004_IDOMode_OFFSET                          10
#define SMN_0x13B31004_IDOMode_WIDTH                           2
#define SMN_0x13B31004_IDOMode_MASK                            0xc00
#define SMN_0x13B31004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B31004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B31004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B31004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B31004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B31004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B31004_CrsEnable_OFFSET                        18
#define SMN_0x13B31004_CrsEnable_WIDTH                         1
#define SMN_0x13B31004_CrsEnable_MASK                          0x40000
#define SMN_0x13B31004_APIC_Enable_OFFSET                      23
#define SMN_0x13B31004_APIC_Enable_WIDTH                       1
#define SMN_0x13B31004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B31004_APIC_Range_OFFSET                       24
#define SMN_0x13B31004_APIC_Range_WIDTH                        8
#define SMN_0x13B31004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00001004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B31004_STRUCT;

// Address
#define SMN_0x13B31404_ADDRESS                                 0x13B31404

// Type
#define SMN_0x13B31404_TYPE                                    TYPE_SMN

#define SMN_0x13B31404_BridgeDis_OFFSET                        0
#define SMN_0x13B31404_BridgeDis_WIDTH                         1
#define SMN_0x13B31404_BridgeDis_MASK                          0x1
#define SMN_0x13B31404_BusMasterDis_OFFSET                     1
#define SMN_0x13B31404_BusMasterDis_WIDTH                      1
#define SMN_0x13B31404_BusMasterDis_MASK                       0x2
#define SMN_0x13B31404_CfgDis_OFFSET                           2
#define SMN_0x13B31404_CfgDis_WIDTH                            1
#define SMN_0x13B31404_CfgDis_MASK                             0x4
#define SMN_0x13B31404_P2pDis_OFFSET                           3
#define SMN_0x13B31404_P2pDis_WIDTH                            1
#define SMN_0x13B31404_P2pDis_MASK                             0x8
#define SMN_0x13B31404_VDMDis_OFFSET                           5
#define SMN_0x13B31404_VDMDis_WIDTH                            1
#define SMN_0x13B31404_VDMDis_MASK                             0x20
#define SMN_0x13B31404_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B31404_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B31404_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B31404_PassPWDis_OFFSET                        7
#define SMN_0x13B31404_PassPWDis_WIDTH                         1
#define SMN_0x13B31404_PassPWDis_MASK                          0x80
#define SMN_0x13B31404_NoSnoopDis_OFFSET                       8
#define SMN_0x13B31404_NoSnoopDis_WIDTH                        1
#define SMN_0x13B31404_NoSnoopDis_MASK                         0x100
#define SMN_0x13B31404_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B31404_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B31404_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B31404_IDOMode_OFFSET                          10
#define SMN_0x13B31404_IDOMode_WIDTH                           2
#define SMN_0x13B31404_IDOMode_MASK                            0xc00
#define SMN_0x13B31404_ExtDevPlug_OFFSET                       16
#define SMN_0x13B31404_ExtDevPlug_WIDTH                        1
#define SMN_0x13B31404_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B31404_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B31404_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B31404_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B31404_CrsEnable_OFFSET                        18
#define SMN_0x13B31404_CrsEnable_WIDTH                         1
#define SMN_0x13B31404_CrsEnable_MASK                          0x40000
#define SMN_0x13B31404_APIC_Enable_OFFSET                      23
#define SMN_0x13B31404_APIC_Enable_WIDTH                       1
#define SMN_0x13B31404_APIC_Enable_MASK                        0x800000
#define SMN_0x13B31404_APIC_Range_OFFSET                       24
#define SMN_0x13B31404_APIC_Range_WIDTH                        8
#define SMN_0x13B31404_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00001404
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B31404_STRUCT;

// Address
#define SMN_0x13B31804_ADDRESS                                 0x13B31804

// Type
#define SMN_0x13B31804_TYPE                                    TYPE_SMN

#define SMN_0x13B31804_BridgeDis_OFFSET                        0
#define SMN_0x13B31804_BridgeDis_WIDTH                         1
#define SMN_0x13B31804_BridgeDis_MASK                          0x1
#define SMN_0x13B31804_BusMasterDis_OFFSET                     1
#define SMN_0x13B31804_BusMasterDis_WIDTH                      1
#define SMN_0x13B31804_BusMasterDis_MASK                       0x2
#define SMN_0x13B31804_CfgDis_OFFSET                           2
#define SMN_0x13B31804_CfgDis_WIDTH                            1
#define SMN_0x13B31804_CfgDis_MASK                             0x4
#define SMN_0x13B31804_P2pDis_OFFSET                           3
#define SMN_0x13B31804_P2pDis_WIDTH                            1
#define SMN_0x13B31804_P2pDis_MASK                             0x8
#define SMN_0x13B31804_VDMDis_OFFSET                           5
#define SMN_0x13B31804_VDMDis_WIDTH                            1
#define SMN_0x13B31804_VDMDis_MASK                             0x20
#define SMN_0x13B31804_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B31804_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B31804_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B31804_PassPWDis_OFFSET                        7
#define SMN_0x13B31804_PassPWDis_WIDTH                         1
#define SMN_0x13B31804_PassPWDis_MASK                          0x80
#define SMN_0x13B31804_NoSnoopDis_OFFSET                       8
#define SMN_0x13B31804_NoSnoopDis_WIDTH                        1
#define SMN_0x13B31804_NoSnoopDis_MASK                         0x100
#define SMN_0x13B31804_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B31804_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B31804_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B31804_IDOMode_OFFSET                          10
#define SMN_0x13B31804_IDOMode_WIDTH                           2
#define SMN_0x13B31804_IDOMode_MASK                            0xc00
#define SMN_0x13B31804_ExtDevPlug_OFFSET                       16
#define SMN_0x13B31804_ExtDevPlug_WIDTH                        1
#define SMN_0x13B31804_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B31804_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B31804_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B31804_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B31804_CrsEnable_OFFSET                        18
#define SMN_0x13B31804_CrsEnable_WIDTH                         1
#define SMN_0x13B31804_CrsEnable_MASK                          0x40000
#define SMN_0x13B31804_APIC_Enable_OFFSET                      23
#define SMN_0x13B31804_APIC_Enable_WIDTH                       1
#define SMN_0x13B31804_APIC_Enable_MASK                        0x800000
#define SMN_0x13B31804_APIC_Range_OFFSET                       24
#define SMN_0x13B31804_APIC_Range_WIDTH                        8
#define SMN_0x13B31804_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00001804
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B31804_STRUCT;

// Address
#define SMN_0x13B31C04_ADDRESS                                 0x13B31C04

// Type
#define SMN_0x13B31C04_TYPE                                    TYPE_SMN

#define SMN_0x13B31C04_BridgeDis_OFFSET                        0
#define SMN_0x13B31C04_BridgeDis_WIDTH                         1
#define SMN_0x13B31C04_BridgeDis_MASK                          0x1
#define SMN_0x13B31C04_BusMasterDis_OFFSET                     1
#define SMN_0x13B31C04_BusMasterDis_WIDTH                      1
#define SMN_0x13B31C04_BusMasterDis_MASK                       0x2
#define SMN_0x13B31C04_CfgDis_OFFSET                           2
#define SMN_0x13B31C04_CfgDis_WIDTH                            1
#define SMN_0x13B31C04_CfgDis_MASK                             0x4
#define SMN_0x13B31C04_P2pDis_OFFSET                           3
#define SMN_0x13B31C04_P2pDis_WIDTH                            1
#define SMN_0x13B31C04_P2pDis_MASK                             0x8
#define SMN_0x13B31C04_VDMDis_OFFSET                           5
#define SMN_0x13B31C04_VDMDis_WIDTH                            1
#define SMN_0x13B31C04_VDMDis_MASK                             0x20
#define SMN_0x13B31C04_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B31C04_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B31C04_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B31C04_PassPWDis_OFFSET                        7
#define SMN_0x13B31C04_PassPWDis_WIDTH                         1
#define SMN_0x13B31C04_PassPWDis_MASK                          0x80
#define SMN_0x13B31C04_NoSnoopDis_OFFSET                       8
#define SMN_0x13B31C04_NoSnoopDis_WIDTH                        1
#define SMN_0x13B31C04_NoSnoopDis_MASK                         0x100
#define SMN_0x13B31C04_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B31C04_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B31C04_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B31C04_IDOMode_OFFSET                          10
#define SMN_0x13B31C04_IDOMode_WIDTH                           2
#define SMN_0x13B31C04_IDOMode_MASK                            0xc00
#define SMN_0x13B31C04_ExtDevPlug_OFFSET                       16
#define SMN_0x13B31C04_ExtDevPlug_WIDTH                        1
#define SMN_0x13B31C04_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B31C04_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B31C04_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B31C04_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B31C04_CrsEnable_OFFSET                        18
#define SMN_0x13B31C04_CrsEnable_WIDTH                         1
#define SMN_0x13B31C04_CrsEnable_MASK                          0x40000
#define SMN_0x13B31C04_APIC_Enable_OFFSET                      23
#define SMN_0x13B31C04_APIC_Enable_WIDTH                       1
#define SMN_0x13B31C04_APIC_Enable_MASK                        0x800000
#define SMN_0x13B31C04_APIC_Range_OFFSET                       24
#define SMN_0x13B31C04_APIC_Range_WIDTH                        8
#define SMN_0x13B31C04_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00001C04
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B31C04_STRUCT;

// Address
#define SMN_0x13B32004_ADDRESS                                 0x13B32004

// Type
#define SMN_0x13B32004_TYPE                                    TYPE_SMN

#define SMN_0x13B32004_BridgeDis_OFFSET                        0
#define SMN_0x13B32004_BridgeDis_WIDTH                         1
#define SMN_0x13B32004_BridgeDis_MASK                          0x1
#define SMN_0x13B32004_BusMasterDis_OFFSET                     1
#define SMN_0x13B32004_BusMasterDis_WIDTH                      1
#define SMN_0x13B32004_BusMasterDis_MASK                       0x2
#define SMN_0x13B32004_CfgDis_OFFSET                           2
#define SMN_0x13B32004_CfgDis_WIDTH                            1
#define SMN_0x13B32004_CfgDis_MASK                             0x4
#define SMN_0x13B32004_P2pDis_OFFSET                           3
#define SMN_0x13B32004_P2pDis_WIDTH                            1
#define SMN_0x13B32004_P2pDis_MASK                             0x8
#define SMN_0x13B32004_VDMDis_OFFSET                           5
#define SMN_0x13B32004_VDMDis_WIDTH                            1
#define SMN_0x13B32004_VDMDis_MASK                             0x20
#define SMN_0x13B32004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B32004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B32004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B32004_PassPWDis_OFFSET                        7
#define SMN_0x13B32004_PassPWDis_WIDTH                         1
#define SMN_0x13B32004_PassPWDis_MASK                          0x80
#define SMN_0x13B32004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B32004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B32004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B32004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B32004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B32004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B32004_IDOMode_OFFSET                          10
#define SMN_0x13B32004_IDOMode_WIDTH                           2
#define SMN_0x13B32004_IDOMode_MASK                            0xc00
#define SMN_0x13B32004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B32004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B32004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B32004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B32004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B32004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B32004_CrsEnable_OFFSET                        18
#define SMN_0x13B32004_CrsEnable_WIDTH                         1
#define SMN_0x13B32004_CrsEnable_MASK                          0x40000
#define SMN_0x13B32004_APIC_Enable_OFFSET                      23
#define SMN_0x13B32004_APIC_Enable_WIDTH                       1
#define SMN_0x13B32004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B32004_APIC_Range_OFFSET                       24
#define SMN_0x13B32004_APIC_Range_WIDTH                        8
#define SMN_0x13B32004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00002004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B32004_STRUCT;

// Address
#define SMN_0x13B32404_ADDRESS                                 0x13B32404

// Type
#define SMN_0x13B32404_TYPE                                    TYPE_SMN

#define SMN_0x13B32404_BridgeDis_OFFSET                        0
#define SMN_0x13B32404_BridgeDis_WIDTH                         1
#define SMN_0x13B32404_BridgeDis_MASK                          0x1
#define SMN_0x13B32404_BusMasterDis_OFFSET                     1
#define SMN_0x13B32404_BusMasterDis_WIDTH                      1
#define SMN_0x13B32404_BusMasterDis_MASK                       0x2
#define SMN_0x13B32404_CfgDis_OFFSET                           2
#define SMN_0x13B32404_CfgDis_WIDTH                            1
#define SMN_0x13B32404_CfgDis_MASK                             0x4
#define SMN_0x13B32404_P2pDis_OFFSET                           3
#define SMN_0x13B32404_P2pDis_WIDTH                            1
#define SMN_0x13B32404_P2pDis_MASK                             0x8
#define SMN_0x13B32404_VDMDis_OFFSET                           5
#define SMN_0x13B32404_VDMDis_WIDTH                            1
#define SMN_0x13B32404_VDMDis_MASK                             0x20
#define SMN_0x13B32404_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B32404_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B32404_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B32404_PassPWDis_OFFSET                        7
#define SMN_0x13B32404_PassPWDis_WIDTH                         1
#define SMN_0x13B32404_PassPWDis_MASK                          0x80
#define SMN_0x13B32404_NoSnoopDis_OFFSET                       8
#define SMN_0x13B32404_NoSnoopDis_WIDTH                        1
#define SMN_0x13B32404_NoSnoopDis_MASK                         0x100
#define SMN_0x13B32404_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B32404_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B32404_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B32404_IDOMode_OFFSET                          10
#define SMN_0x13B32404_IDOMode_WIDTH                           2
#define SMN_0x13B32404_IDOMode_MASK                            0xc00
#define SMN_0x13B32404_ExtDevPlug_OFFSET                       16
#define SMN_0x13B32404_ExtDevPlug_WIDTH                        1
#define SMN_0x13B32404_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B32404_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B32404_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B32404_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B32404_CrsEnable_OFFSET                        18
#define SMN_0x13B32404_CrsEnable_WIDTH                         1
#define SMN_0x13B32404_CrsEnable_MASK                          0x40000
#define SMN_0x13B32404_APIC_Enable_OFFSET                      23
#define SMN_0x13B32404_APIC_Enable_WIDTH                       1
#define SMN_0x13B32404_APIC_Enable_MASK                        0x800000
#define SMN_0x13B32404_APIC_Range_OFFSET                       24
#define SMN_0x13B32404_APIC_Range_WIDTH                        8
#define SMN_0x13B32404_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00002404
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B32404_STRUCT;

#define SMN_0x13B32804_ADDRESS                                 0x13B32804

// Type
#define SMN_0x13B32804_TYPE                                    TYPE_SMN

#define SMN_0x13B32804_BridgeDis_OFFSET                        0
#define SMN_0x13B32804_BridgeDis_WIDTH                         1
#define SMN_0x13B32804_BridgeDis_MASK                          0x1
#define SMN_0x13B32804_BusMasterDis_OFFSET                     1
#define SMN_0x13B32804_BusMasterDis_WIDTH                      1
#define SMN_0x13B32804_BusMasterDis_MASK                       0x2
#define SMN_0x13B32804_CfgDis_OFFSET                           2
#define SMN_0x13B32804_CfgDis_WIDTH                            1
#define SMN_0x13B32804_CfgDis_MASK                             0x4
#define SMN_0x13B32804_P2pDis_OFFSET                           3
#define SMN_0x13B32804_P2pDis_WIDTH                            1
#define SMN_0x13B32804_P2pDis_MASK                             0x8
#define SMN_0x13B32804_VDMDis_OFFSET                           5
#define SMN_0x13B32804_VDMDis_WIDTH                            1
#define SMN_0x13B32804_VDMDis_MASK                             0x20
#define SMN_0x13B32804_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B32804_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B32804_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B32804_PassPWDis_OFFSET                        7
#define SMN_0x13B32804_PassPWDis_WIDTH                         1
#define SMN_0x13B32804_PassPWDis_MASK                          0x80
#define SMN_0x13B32804_NoSnoopDis_OFFSET                       8
#define SMN_0x13B32804_NoSnoopDis_WIDTH                        1
#define SMN_0x13B32804_NoSnoopDis_MASK                         0x100
#define SMN_0x13B32804_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B32804_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B32804_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B32804_IDOMode_OFFSET                          10
#define SMN_0x13B32804_IDOMode_WIDTH                           2
#define SMN_0x13B32804_IDOMode_MASK                            0xc00
#define SMN_0x13B32804_ExtDevPlug_OFFSET                       16
#define SMN_0x13B32804_ExtDevPlug_WIDTH                        1
#define SMN_0x13B32804_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B32804_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B32804_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B32804_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B32804_CrsEnable_OFFSET                        18
#define SMN_0x13B32804_CrsEnable_WIDTH                         1
#define SMN_0x13B32804_CrsEnable_MASK                          0x40000
#define SMN_0x13B32804_APIC_Enable_OFFSET                      23
#define SMN_0x13B32804_APIC_Enable_WIDTH                       1
#define SMN_0x13B32804_APIC_Enable_MASK                        0x800000
#define SMN_0x13B32804_APIC_Range_OFFSET                       24
#define SMN_0x13B32804_APIC_Range_WIDTH                        8
#define SMN_0x13B32804_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00002804
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B32804_STRUCT;

// Address
#define SMN_0x13B32C04_ADDRESS                                 0x13B32C04

// Type
#define SMN_0x13B32C04_TYPE                                    TYPE_SMN

#define SMN_0x13B32C04_BridgeDis_OFFSET                        0
#define SMN_0x13B32C04_BridgeDis_WIDTH                         1
#define SMN_0x13B32C04_BridgeDis_MASK                          0x1
#define SMN_0x13B32C04_BusMasterDis_OFFSET                     1
#define SMN_0x13B32C04_BusMasterDis_WIDTH                      1
#define SMN_0x13B32C04_BusMasterDis_MASK                       0x2
#define SMN_0x13B32C04_CfgDis_OFFSET                           2
#define SMN_0x13B32C04_CfgDis_WIDTH                            1
#define SMN_0x13B32C04_CfgDis_MASK                             0x4
#define SMN_0x13B32C04_P2pDis_OFFSET                           3
#define SMN_0x13B32C04_P2pDis_WIDTH                            1
#define SMN_0x13B32C04_P2pDis_MASK                             0x8
#define SMN_0x13B32C04_VDMDis_OFFSET                           5
#define SMN_0x13B32C04_VDMDis_WIDTH                            1
#define SMN_0x13B32C04_VDMDis_MASK                             0x20
#define SMN_0x13B32C04_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B32C04_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B32C04_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B32C04_PassPWDis_OFFSET                        7
#define SMN_0x13B32C04_PassPWDis_WIDTH                         1
#define SMN_0x13B32C04_PassPWDis_MASK                          0x80
#define SMN_0x13B32C04_NoSnoopDis_OFFSET                       8
#define SMN_0x13B32C04_NoSnoopDis_WIDTH                        1
#define SMN_0x13B32C04_NoSnoopDis_MASK                         0x100
#define SMN_0x13B32C04_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B32C04_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B32C04_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B32C04_IDOMode_OFFSET                          10
#define SMN_0x13B32C04_IDOMode_WIDTH                           2
#define SMN_0x13B32C04_IDOMode_MASK                            0xc00
#define SMN_0x13B32C04_ExtDevPlug_OFFSET                       16
#define SMN_0x13B32C04_ExtDevPlug_WIDTH                        1
#define SMN_0x13B32C04_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B32C04_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B32C04_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B32C04_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B32C04_CrsEnable_OFFSET                        18
#define SMN_0x13B32C04_CrsEnable_WIDTH                         1
#define SMN_0x13B32C04_CrsEnable_MASK                          0x40000
#define SMN_0x13B32C04_APIC_Enable_OFFSET                      23
#define SMN_0x13B32C04_APIC_Enable_WIDTH                       1
#define SMN_0x13B32C04_APIC_Enable_MASK                        0x800000
#define SMN_0x13B32C04_APIC_Range_OFFSET                       24
#define SMN_0x13B32C04_APIC_Range_WIDTH                        8
#define SMN_0x13B32C04_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00002C04
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B32C04_STRUCT;

// Address
#define SMN_0x13B33004_ADDRESS                                 0x13B33004

// Type
#define SMN_0x13B33004_TYPE                                    TYPE_SMN

#define SMN_0x13B33004_BridgeDis_OFFSET                        0
#define SMN_0x13B33004_BridgeDis_WIDTH                         1
#define SMN_0x13B33004_BridgeDis_MASK                          0x1
#define SMN_0x13B33004_BusMasterDis_OFFSET                     1
#define SMN_0x13B33004_BusMasterDis_WIDTH                      1
#define SMN_0x13B33004_BusMasterDis_MASK                       0x2
#define SMN_0x13B33004_CfgDis_OFFSET                           2
#define SMN_0x13B33004_CfgDis_WIDTH                            1
#define SMN_0x13B33004_CfgDis_MASK                             0x4
#define SMN_0x13B33004_P2pDis_OFFSET                           3
#define SMN_0x13B33004_P2pDis_WIDTH                            1
#define SMN_0x13B33004_P2pDis_MASK                             0x8
#define SMN_0x13B33004_VDMDis_OFFSET                           5
#define SMN_0x13B33004_VDMDis_WIDTH                            1
#define SMN_0x13B33004_VDMDis_MASK                             0x20
#define SMN_0x13B33004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B33004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B33004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B33004_PassPWDis_OFFSET                        7
#define SMN_0x13B33004_PassPWDis_WIDTH                         1
#define SMN_0x13B33004_PassPWDis_MASK                          0x80
#define SMN_0x13B33004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B33004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B33004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B33004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B33004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B33004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B33004_IDOMode_OFFSET                          10
#define SMN_0x13B33004_IDOMode_WIDTH                           2
#define SMN_0x13B33004_IDOMode_MASK                            0xc00
#define SMN_0x13B33004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B33004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B33004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B33004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B33004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B33004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B33004_CrsEnable_OFFSET                        18
#define SMN_0x13B33004_CrsEnable_WIDTH                         1
#define SMN_0x13B33004_CrsEnable_MASK                          0x40000
#define SMN_0x13B33004_APIC_Enable_OFFSET                      23
#define SMN_0x13B33004_APIC_Enable_WIDTH                       1
#define SMN_0x13B33004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B33004_APIC_Range_OFFSET                       24
#define SMN_0x13B33004_APIC_Range_WIDTH                        8
#define SMN_0x13B33004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00003004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B33004_STRUCT;


#define SMN_0x13B33404_ADDRESS                                 0x13B33404

// Type
#define SMN_0x13B33404_TYPE                                    TYPE_SMN

#define SMN_0x13B33404_BridgeDis_OFFSET                        0
#define SMN_0x13B33404_BridgeDis_WIDTH                         1
#define SMN_0x13B33404_BridgeDis_MASK                          0x1
#define SMN_0x13B33404_BusMasterDis_OFFSET                     1
#define SMN_0x13B33404_BusMasterDis_WIDTH                      1
#define SMN_0x13B33404_BusMasterDis_MASK                       0x2
#define SMN_0x13B33404_CfgDis_OFFSET                           2
#define SMN_0x13B33404_CfgDis_WIDTH                            1
#define SMN_0x13B33404_CfgDis_MASK                             0x4
#define SMN_0x13B33404_P2pDis_OFFSET                           3
#define SMN_0x13B33404_P2pDis_WIDTH                            1
#define SMN_0x13B33404_P2pDis_MASK                             0x8
#define SMN_0x13B33404_VDMDis_OFFSET                           5
#define SMN_0x13B33404_VDMDis_WIDTH                            1
#define SMN_0x13B33404_VDMDis_MASK                             0x20
#define SMN_0x13B33404_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B33404_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B33404_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B33404_PassPWDis_OFFSET                        7
#define SMN_0x13B33404_PassPWDis_WIDTH                         1
#define SMN_0x13B33404_PassPWDis_MASK                          0x80
#define SMN_0x13B33404_NoSnoopDis_OFFSET                       8
#define SMN_0x13B33404_NoSnoopDis_WIDTH                        1
#define SMN_0x13B33404_NoSnoopDis_MASK                         0x100
#define SMN_0x13B33404_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B33404_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B33404_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B33404_IDOMode_OFFSET                          10
#define SMN_0x13B33404_IDOMode_WIDTH                           2
#define SMN_0x13B33404_IDOMode_MASK                            0xc00
#define SMN_0x13B33404_ExtDevPlug_OFFSET                       16
#define SMN_0x13B33404_ExtDevPlug_WIDTH                        1
#define SMN_0x13B33404_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B33404_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B33404_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B33404_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B33404_CrsEnable_OFFSET                        18
#define SMN_0x13B33404_CrsEnable_WIDTH                         1
#define SMN_0x13B33404_CrsEnable_MASK                          0x40000
#define SMN_0x13B33404_APIC_Enable_OFFSET                      23
#define SMN_0x13B33404_APIC_Enable_WIDTH                       1
#define SMN_0x13B33404_APIC_Enable_MASK                        0x800000
#define SMN_0x13B33404_APIC_Range_OFFSET                       24
#define SMN_0x13B33404_APIC_Range_WIDTH                        8
#define SMN_0x13B33404_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00003404
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B33404_STRUCT;


// Address
#define SMN_0x13B33804_ADDRESS                                 0x13B33804

// Type
#define SMN_0x13B33804_TYPE                                    TYPE_SMN

#define SMN_0x13B33804_BridgeDis_OFFSET                        0
#define SMN_0x13B33804_BridgeDis_WIDTH                         1
#define SMN_0x13B33804_BridgeDis_MASK                          0x1
#define SMN_0x13B33804_BusMasterDis_OFFSET                     1
#define SMN_0x13B33804_BusMasterDis_WIDTH                      1
#define SMN_0x13B33804_BusMasterDis_MASK                       0x2
#define SMN_0x13B33804_CfgDis_OFFSET                           2
#define SMN_0x13B33804_CfgDis_WIDTH                            1
#define SMN_0x13B33804_CfgDis_MASK                             0x4
#define SMN_0x13B33804_P2pDis_OFFSET                           3
#define SMN_0x13B33804_P2pDis_WIDTH                            1
#define SMN_0x13B33804_P2pDis_MASK                             0x8
#define SMN_0x13B33804_VDMDis_OFFSET                           5
#define SMN_0x13B33804_VDMDis_WIDTH                            1
#define SMN_0x13B33804_VDMDis_MASK                             0x20
#define SMN_0x13B33804_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B33804_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B33804_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B33804_PassPWDis_OFFSET                        7
#define SMN_0x13B33804_PassPWDis_WIDTH                         1
#define SMN_0x13B33804_PassPWDis_MASK                          0x80
#define SMN_0x13B33804_NoSnoopDis_OFFSET                       8
#define SMN_0x13B33804_NoSnoopDis_WIDTH                        1
#define SMN_0x13B33804_NoSnoopDis_MASK                         0x100
#define SMN_0x13B33804_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B33804_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B33804_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B33804_IDOMode_OFFSET                          10
#define SMN_0x13B33804_IDOMode_WIDTH                           2
#define SMN_0x13B33804_IDOMode_MASK                            0xc00
#define SMN_0x13B33804_ExtDevPlug_OFFSET                       16
#define SMN_0x13B33804_ExtDevPlug_WIDTH                        1
#define SMN_0x13B33804_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B33804_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B33804_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B33804_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B33804_CrsEnable_OFFSET                        18
#define SMN_0x13B33804_CrsEnable_WIDTH                         1
#define SMN_0x13B33804_CrsEnable_MASK                          0x40000
#define SMN_0x13B33804_APIC_Enable_OFFSET                      23
#define SMN_0x13B33804_APIC_Enable_WIDTH                       1
#define SMN_0x13B33804_APIC_Enable_MASK                        0x800000
#define SMN_0x13B33804_APIC_Range_OFFSET                       24
#define SMN_0x13B33804_APIC_Range_WIDTH                        8
#define SMN_0x13B33804_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00003804
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B33804_STRUCT;


// Address
#define SMN_0x13B33C04_ADDRESS                                 0x13B33C04

// Type
#define SMN_0x13B33C04_TYPE                                    TYPE_SMN

#define SMN_0x13B33C04_BridgeDis_OFFSET                        0
#define SMN_0x13B33C04_BridgeDis_WIDTH                         1
#define SMN_0x13B33C04_BridgeDis_MASK                          0x1
#define SMN_0x13B33C04_BusMasterDis_OFFSET                     1
#define SMN_0x13B33C04_BusMasterDis_WIDTH                      1
#define SMN_0x13B33C04_BusMasterDis_MASK                       0x2
#define SMN_0x13B33C04_CfgDis_OFFSET                           2
#define SMN_0x13B33C04_CfgDis_WIDTH                            1
#define SMN_0x13B33C04_CfgDis_MASK                             0x4
#define SMN_0x13B33C04_P2pDis_OFFSET                           3
#define SMN_0x13B33C04_P2pDis_WIDTH                            1
#define SMN_0x13B33C04_P2pDis_MASK                             0x8
#define SMN_0x13B33C04_VDMDis_OFFSET                           5
#define SMN_0x13B33C04_VDMDis_WIDTH                            1
#define SMN_0x13B33C04_VDMDis_MASK                             0x20
#define SMN_0x13B33C04_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B33C04_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B33C04_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B33C04_PassPWDis_OFFSET                        7
#define SMN_0x13B33C04_PassPWDis_WIDTH                         1
#define SMN_0x13B33C04_PassPWDis_MASK                          0x80
#define SMN_0x13B33C04_NoSnoopDis_OFFSET                       8
#define SMN_0x13B33C04_NoSnoopDis_WIDTH                        1
#define SMN_0x13B33C04_NoSnoopDis_MASK                         0x100
#define SMN_0x13B33C04_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B33C04_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B33C04_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B33C04_IDOMode_OFFSET                          10
#define SMN_0x13B33C04_IDOMode_WIDTH                           2
#define SMN_0x13B33C04_IDOMode_MASK                            0xc00
#define SMN_0x13B33C04_ExtDevPlug_OFFSET                       16
#define SMN_0x13B33C04_ExtDevPlug_WIDTH                        1
#define SMN_0x13B33C04_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B33C04_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B33C04_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B33C04_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B33C04_CrsEnable_OFFSET                        18
#define SMN_0x13B33C04_CrsEnable_WIDTH                         1
#define SMN_0x13B33C04_CrsEnable_MASK                          0x40000
#define SMN_0x13B33C04_APIC_Enable_OFFSET                      23
#define SMN_0x13B33C04_APIC_Enable_WIDTH                       1
#define SMN_0x13B33C04_APIC_Enable_MASK                        0x800000
#define SMN_0x13B33C04_APIC_Range_OFFSET                       24
#define SMN_0x13B33C04_APIC_Range_WIDTH                        8
#define SMN_0x13B33C04_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00003C04
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B33C04_STRUCT;

// Address
#define SMN_0x13B34004_ADDRESS                                 0x13B34004

// Type
#define SMN_0x13B34004_TYPE                                    TYPE_SMN

#define SMN_0x13B34004_BridgeDis_OFFSET                        0
#define SMN_0x13B34004_BridgeDis_WIDTH                         1
#define SMN_0x13B34004_BridgeDis_MASK                          0x1
#define SMN_0x13B34004_BusMasterDis_OFFSET                     1
#define SMN_0x13B34004_BusMasterDis_WIDTH                      1
#define SMN_0x13B34004_BusMasterDis_MASK                       0x2
#define SMN_0x13B34004_CfgDis_OFFSET                           2
#define SMN_0x13B34004_CfgDis_WIDTH                            1
#define SMN_0x13B34004_CfgDis_MASK                             0x4
#define SMN_0x13B34004_P2pDis_OFFSET                           3
#define SMN_0x13B34004_P2pDis_WIDTH                            1
#define SMN_0x13B34004_P2pDis_MASK                             0x8
#define SMN_0x13B34004_VDMDis_OFFSET                           5
#define SMN_0x13B34004_VDMDis_WIDTH                            1
#define SMN_0x13B34004_VDMDis_MASK                             0x20
#define SMN_0x13B34004_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B34004_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B34004_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B34004_PassPWDis_OFFSET                        7
#define SMN_0x13B34004_PassPWDis_WIDTH                         1
#define SMN_0x13B34004_PassPWDis_MASK                          0x80
#define SMN_0x13B34004_NoSnoopDis_OFFSET                       8
#define SMN_0x13B34004_NoSnoopDis_WIDTH                        1
#define SMN_0x13B34004_NoSnoopDis_MASK                         0x100
#define SMN_0x13B34004_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B34004_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B34004_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B34004_IDOMode_OFFSET                          10
#define SMN_0x13B34004_IDOMode_WIDTH                           2
#define SMN_0x13B34004_IDOMode_MASK                            0xc00
#define SMN_0x13B34004_ExtDevPlug_OFFSET                       16
#define SMN_0x13B34004_ExtDevPlug_WIDTH                        1
#define SMN_0x13B34004_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B34004_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B34004_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B34004_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B34004_CrsEnable_OFFSET                        18
#define SMN_0x13B34004_CrsEnable_WIDTH                         1
#define SMN_0x13B34004_CrsEnable_MASK                          0x40000
#define SMN_0x13B34004_APIC_Enable_OFFSET                      23
#define SMN_0x13B34004_APIC_Enable_WIDTH                       1
#define SMN_0x13B34004_APIC_Enable_MASK                        0x800000
#define SMN_0x13B34004_APIC_Range_OFFSET                       24
#define SMN_0x13B34004_APIC_Range_WIDTH                        8
#define SMN_0x13B34004_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00004004
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B34004_STRUCT;

// Address
#define SMN_0x13B34404_ADDRESS                                 0x13B34404

// Type
#define SMN_0x13B34404_TYPE                                    TYPE_SMN

#define SMN_0x13B34404_BridgeDis_OFFSET                        0
#define SMN_0x13B34404_BridgeDis_WIDTH                         1
#define SMN_0x13B34404_BridgeDis_MASK                          0x1
#define SMN_0x13B34404_BusMasterDis_OFFSET                     1
#define SMN_0x13B34404_BusMasterDis_WIDTH                      1
#define SMN_0x13B34404_BusMasterDis_MASK                       0x2
#define SMN_0x13B34404_CfgDis_OFFSET                           2
#define SMN_0x13B34404_CfgDis_WIDTH                            1
#define SMN_0x13B34404_CfgDis_MASK                             0x4
#define SMN_0x13B34404_P2pDis_OFFSET                           3
#define SMN_0x13B34404_P2pDis_WIDTH                            1
#define SMN_0x13B34404_P2pDis_MASK                             0x8
#define SMN_0x13B34404_VDMDis_OFFSET                           5
#define SMN_0x13B34404_VDMDis_WIDTH                            1
#define SMN_0x13B34404_VDMDis_MASK                             0x20
#define SMN_0x13B34404_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B34404_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B34404_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B34404_PassPWDis_OFFSET                        7
#define SMN_0x13B34404_PassPWDis_WIDTH                         1
#define SMN_0x13B34404_PassPWDis_MASK                          0x80
#define SMN_0x13B34404_NoSnoopDis_OFFSET                       8
#define SMN_0x13B34404_NoSnoopDis_WIDTH                        1
#define SMN_0x13B34404_NoSnoopDis_MASK                         0x100
#define SMN_0x13B34404_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B34404_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B34404_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B34404_IDOMode_OFFSET                          10
#define SMN_0x13B34404_IDOMode_WIDTH                           2
#define SMN_0x13B34404_IDOMode_MASK                            0xc00
#define SMN_0x13B34404_ExtDevPlug_OFFSET                       16
#define SMN_0x13B34404_ExtDevPlug_WIDTH                        1
#define SMN_0x13B34404_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B34404_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B34404_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B34404_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B34404_CrsEnable_OFFSET                        18
#define SMN_0x13B34404_CrsEnable_WIDTH                         1
#define SMN_0x13B34404_CrsEnable_MASK                          0x40000
#define SMN_0x13B34404_APIC_Enable_OFFSET                      23
#define SMN_0x13B34404_APIC_Enable_WIDTH                       1
#define SMN_0x13B34404_APIC_Enable_MASK                        0x800000
#define SMN_0x13B34404_APIC_Range_OFFSET                       24
#define SMN_0x13B34404_APIC_Range_WIDTH                        8
#define SMN_0x13B34404_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00004404
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B34404_STRUCT;

// Address
#define SMN_0x13B34804_ADDRESS                                 0x13B34804

// Type
#define SMN_0x13B34804_TYPE                                    TYPE_SMN

#define SMN_0x13B34804_BridgeDis_OFFSET                        0
#define SMN_0x13B34804_BridgeDis_WIDTH                         1
#define SMN_0x13B34804_BridgeDis_MASK                          0x1
#define SMN_0x13B34804_BusMasterDis_OFFSET                     1
#define SMN_0x13B34804_BusMasterDis_WIDTH                      1
#define SMN_0x13B34804_BusMasterDis_MASK                       0x2
#define SMN_0x13B34804_CfgDis_OFFSET                           2
#define SMN_0x13B34804_CfgDis_WIDTH                            1
#define SMN_0x13B34804_CfgDis_MASK                             0x4
#define SMN_0x13B34804_P2pDis_OFFSET                           3
#define SMN_0x13B34804_P2pDis_WIDTH                            1
#define SMN_0x13B34804_P2pDis_MASK                             0x8
#define SMN_0x13B34804_VDMDis_OFFSET                           5
#define SMN_0x13B34804_VDMDis_WIDTH                            1
#define SMN_0x13B34804_VDMDis_MASK                             0x20
#define SMN_0x13B34804_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B34804_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B34804_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B34804_PassPWDis_OFFSET                        7
#define SMN_0x13B34804_PassPWDis_WIDTH                         1
#define SMN_0x13B34804_PassPWDis_MASK                          0x80
#define SMN_0x13B34804_NoSnoopDis_OFFSET                       8
#define SMN_0x13B34804_NoSnoopDis_WIDTH                        1
#define SMN_0x13B34804_NoSnoopDis_MASK                         0x100
#define SMN_0x13B34804_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B34804_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B34804_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B34804_IDOMode_OFFSET                          10
#define SMN_0x13B34804_IDOMode_WIDTH                           2
#define SMN_0x13B34804_IDOMode_MASK                            0xc00
#define SMN_0x13B34804_ExtDevPlug_OFFSET                       16
#define SMN_0x13B34804_ExtDevPlug_WIDTH                        1
#define SMN_0x13B34804_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B34804_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B34804_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B34804_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B34804_CrsEnable_OFFSET                        18
#define SMN_0x13B34804_CrsEnable_WIDTH                         1
#define SMN_0x13B34804_CrsEnable_MASK                          0x40000
#define SMN_0x13B34804_APIC_Enable_OFFSET                      23
#define SMN_0x13B34804_APIC_Enable_WIDTH                       1
#define SMN_0x13B34804_APIC_Enable_MASK                        0x800000
#define SMN_0x13B34804_APIC_Range_OFFSET                       24
#define SMN_0x13B34804_APIC_Range_WIDTH                        8
#define SMN_0x13B34804_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00004804
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B34804_STRUCT;

// Address
#define SMN_0x13B34C04_ADDRESS                                 0x13B34C04

// Type
#define SMN_0x13B34C04_TYPE                                    TYPE_SMN

#define SMN_0x13B34C04_BridgeDis_OFFSET                        0
#define SMN_0x13B34C04_BridgeDis_WIDTH                         1
#define SMN_0x13B34C04_BridgeDis_MASK                          0x1
#define SMN_0x13B34C04_BusMasterDis_OFFSET                     1
#define SMN_0x13B34C04_BusMasterDis_WIDTH                      1
#define SMN_0x13B34C04_BusMasterDis_MASK                       0x2
#define SMN_0x13B34C04_CfgDis_OFFSET                           2
#define SMN_0x13B34C04_CfgDis_WIDTH                            1
#define SMN_0x13B34C04_CfgDis_MASK                             0x4
#define SMN_0x13B34C04_P2pDis_OFFSET                           3
#define SMN_0x13B34C04_P2pDis_WIDTH                            1
#define SMN_0x13B34C04_P2pDis_MASK                             0x8
#define SMN_0x13B34C04_VDMDis_OFFSET                           5
#define SMN_0x13B34C04_VDMDis_WIDTH                            1
#define SMN_0x13B34C04_VDMDis_MASK                             0x20
#define SMN_0x13B34C04_MaskUR_Enable_OFFSET                    6
#define SMN_0x13B34C04_MaskUR_Enable_WIDTH                     1
#define SMN_0x13B34C04_MaskUR_Enable_MASK                      0x40
#define SMN_0x13B34C04_PassPWDis_OFFSET                        7
#define SMN_0x13B34C04_PassPWDis_WIDTH                         1
#define SMN_0x13B34C04_PassPWDis_MASK                          0x80
#define SMN_0x13B34C04_NoSnoopDis_OFFSET                       8
#define SMN_0x13B34C04_NoSnoopDis_WIDTH                        1
#define SMN_0x13B34C04_NoSnoopDis_MASK                         0x100
#define SMN_0x13B34C04_ForceRspPassPw_OFFSET                   9
#define SMN_0x13B34C04_ForceRspPassPw_WIDTH                    1
#define SMN_0x13B34C04_ForceRspPassPw_MASK                     0x200
#define SMN_0x13B34C04_IDOMode_OFFSET                          10
#define SMN_0x13B34C04_IDOMode_WIDTH                           2
#define SMN_0x13B34C04_IDOMode_MASK                            0xc00
#define SMN_0x13B34C04_ExtDevPlug_OFFSET                       16
#define SMN_0x13B34C04_ExtDevPlug_WIDTH                        1
#define SMN_0x13B34C04_ExtDevPlug_MASK                         0x10000
#define SMN_0x13B34C04_ExtDevCrsEn_OFFSET                      17
#define SMN_0x13B34C04_ExtDevCrsEn_WIDTH                       1
#define SMN_0x13B34C04_ExtDevCrsEn_MASK                        0x20000
#define SMN_0x13B34C04_CrsEnable_OFFSET                        18
#define SMN_0x13B34C04_CrsEnable_WIDTH                         1
#define SMN_0x13B34C04_CrsEnable_MASK                          0x40000
#define SMN_0x13B34C04_APIC_Enable_OFFSET                      23
#define SMN_0x13B34C04_APIC_Enable_WIDTH                       1
#define SMN_0x13B34C04_APIC_Enable_MASK                        0x800000
#define SMN_0x13B34C04_APIC_Range_OFFSET                       24
#define SMN_0x13B34C04_APIC_Range_WIDTH                        8
#define SMN_0x13B34C04_APIC_Range_MASK                         0xff000000L

/// IOHCDEVIND_00004C04
typedef union {
  struct {
    UINT32                                               BridgeDis:1 ; ///<
    UINT32                                            BusMasterDis:1 ; ///<
    UINT32                                                  CfgDis:1 ; ///<
    UINT32                                                  P2pDis:1 ; ///<
    UINT32                                                  VDMDis:1 ; ///<
    UINT32                                           MaskUR_Enable:1 ; ///<
    UINT32                                               PassPWDis:1 ; ///<
    UINT32                                              NoSnoopDis:1 ; ///<
    UINT32                                          ForceRspPassPw:1 ; ///<
    UINT32                                                 IDOMode:2 ; ///<
    UINT32                                              ExtDevPlug:1 ; ///<
    UINT32                                             ExtDevCrsEn:1 ; ///<
    UINT32                                               CrsEnable:1 ; ///<
    UINT32                                             APIC_Enable:1 ; ///<
    UINT32                                              APIC_Range:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B34C04_STRUCT;




















//    IOHUB::IOMMUL2::IOMMU_CAP_MISC_aliasSMN
// Address
#define IOMMU_CAP_MISC_ADDRESS                                 0x13f00050

// Type
#define IOMMU_CAP_MISC_TYPE                                    TYPE_SMN

#define SMN_00000050_IOMMU_MSI_NUM_OFFSET                      0
#define SMN_00000050_IOMMU_MSI_NUM_WIDTH                       5
#define SMN_00000050_IOMMU_MSI_NUM_MASK                        0x1f
#define SMN_00000050_IOMMU_GVA_SIZE_OFFSET                     5
#define SMN_00000050_IOMMU_GVA_SIZE_WIDTH                      3
#define SMN_00000050_IOMMU_GVA_SIZE_MASK                       0xe0
#define SMN_00000050_IOMMU_PA_SIZE_OFFSET                      8
#define SMN_00000050_IOMMU_PA_SIZE_WIDTH                       7
#define SMN_00000050_IOMMU_PA_SIZE_MASK                        0x7f00
#define SMN_00000050_IOMMU_VA_SIZE_OFFSET                      15
#define SMN_00000050_IOMMU_VA_SIZE_WIDTH                       7
#define SMN_00000050_IOMMU_VA_SIZE_MASK                        0x3f8000
#define SMN_00000050_IOMMU_HT_ATS_RESV_OFFSET                  22
#define SMN_00000050_IOMMU_HT_ATS_RESV_WIDTH                   1
#define SMN_00000050_IOMMU_HT_ATS_RESV_MASK                    0x400000
#define SMN_00000050_Reserved1_OFFSET                          23
#define SMN_00000050_Reserved1_WIDTH                           4
#define SMN_00000050_Reserved1_MASK                            0x7800000
#define SMN_00000050_IOMMU_MSI_NUM_PPR_OFFSET                  27
#define SMN_00000050_IOMMU_MSI_NUM_PPR_WIDTH                   5
#define SMN_00000050_IOMMU_MSI_NUM_PPR_MASK                    0xf8000000L

/// SMN_00000050
typedef union {
  struct {
    UINT32                                           IOMMU_MSI_NUM:5 ; ///<
    UINT32                                          IOMMU_GVA_SIZE:3 ; ///<
    UINT32                                           IOMMU_PA_SIZE:7 ; ///<
    UINT32                                           IOMMU_VA_SIZE:7 ; ///<
    UINT32                                       IOMMU_HT_ATS_RESV:1 ; ///<
    UINT32                                               Reserved1:4 ; ///<
    UINT32                                       IOMMU_MSI_NUM_PPR:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000050_STRUCT;

//  IOHUB::IOMMUL2INDX::L2_DEBUG_3_aliasSMN;
// Address
#define L2_DEBUG_3_ADDRESS                                     0x13f0111c

// Type
#define L2_DEBUG_3_TYPE                                        TYPE_SMN

#define SMN_0000011C_REG_ats_iw_OFFSET                         0
#define SMN_0000011C_REG_ats_iw_WIDTH                          1
#define SMN_0000011C_REG_ats_iw_MASK                           0x1
#define SMN_0000011C_REG_mask_l2_nw_OFFSET                     1
#define SMN_0000011C_REG_mask_l2_nw_WIDTH                      1
#define SMN_0000011C_REG_mask_l2_nw_MASK                       0x2
#define SMN_0000011C_REG_atomic_filter_en_OFFSET               2
#define SMN_0000011C_REG_atomic_filter_en_WIDTH                1
#define SMN_0000011C_REG_atomic_filter_en_MASK                 0x4
#define SMN_0000011C_REG_l1wq_id_el_en_OFFSET                  3
#define SMN_0000011C_REG_l1wq_id_el_en_WIDTH                   1
#define SMN_0000011C_REG_l1wq_id_el_en_MASK                    0x8
#define SMN_0000011C_REG_pagemode0_fix_dis_OFFSET              6
#define SMN_0000011C_REG_pagemode0_fix_dis_WIDTH               1
#define SMN_0000011C_REG_pagemode0_fix_dis_MASK                0x40
#define SMN_0000011C_REG_LogATS_iriw_zero_OFFSET               7
#define SMN_0000011C_REG_LogATS_iriw_zero_WIDTH                1
#define SMN_0000011C_REG_LogATS_iriw_zero_MASK                 0x80
#define SMN_0000011C_REG_PTC_Update_AddrTransReq_OFFSET        8
#define SMN_0000011C_REG_PTC_Update_AddrTransReq_WIDTH         1
#define SMN_0000011C_REG_PTC_Update_AddrTransReq_MASK          0x100
#define SMN_0000011C_REG_RstPtrs_on_BaseHiAcc_Dis_OFFSET       9
#define SMN_0000011C_REG_RstPtrs_on_BaseHiAcc_Dis_WIDTH        1
#define SMN_0000011C_REG_RstPtrs_on_BaseHiAcc_Dis_MASK         0x200
#define SMN_0000011C_REG_RstPtrs_on_BaseLoAcc_Dis_OFFSET       10
#define SMN_0000011C_REG_RstPtrs_on_BaseLoAcc_Dis_WIDTH        1
#define SMN_0000011C_REG_RstPtrs_on_BaseLoAcc_Dis_MASK         0x400
#define SMN_0000011C_REG_RstPtrs_on_LenAccs_En_OFFSET          11
#define SMN_0000011C_REG_RstPtrs_on_LenAccs_En_WIDTH           1
#define SMN_0000011C_REG_RstPtrs_on_LenAccs_En_MASK            0x800
#define SMN_0000011C_REG_DTEResvBitChkDis_OFFSET               12
#define SMN_0000011C_REG_DTEResvBitChkDis_WIDTH                1
#define SMN_0000011C_REG_DTEResvBitChkDis_MASK                 0x1000
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseHiAcc_Dis_OFFSET    13
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseHiAcc_Dis_WIDTH     1
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseHiAcc_Dis_MASK      0x2000
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseLoAcc_Dis_OFFSET    14
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseLoAcc_Dis_WIDTH     1
#define SMN_0000011C_REG_RstGVAPtrs_on_BaseLoAcc_Dis_MASK      0x4000
#define SMN_0000011C_REG_RstGVAPtrs_on_LenAccs_En_OFFSET       15
#define SMN_0000011C_REG_RstGVAPtrs_on_LenAccs_En_WIDTH        1
#define SMN_0000011C_REG_RstGVAPtrs_on_LenAccs_En_MASK         0x8000
#define SMN_0000011C_RESERVED_OFFSET                           16
#define SMN_0000011C_RESERVED_WIDTH                            15
#define SMN_0000011C_RESERVED_MASK                             0x7fff0000
#define SMN_0000011C_REG_gmc_iommu_dis_OFFSET                  31
#define SMN_0000011C_REG_gmc_iommu_dis_WIDTH                   1
#define SMN_0000011C_REG_gmc_iommu_dis_MASK                    0x80000000L

/// SMN_0000011C
typedef union {
  struct {
    UINT32                                              REG_ats_iw:1 ; ///<
    UINT32                                          REG_mask_l2_nw:1 ; ///<
    UINT32                                    REG_atomic_filter_en:1 ; ///<
    UINT32                                       REG_l1wq_id_el_en:1 ; ///<
    UINT32                                   REG_pagemode0_fix_dis:1 ; ///<
    UINT32                                    REG_LogATS_iriw_zero:1 ; ///<
    UINT32                             REG_PTC_Update_AddrTransReq:1 ; ///<
    UINT32                            REG_RstPtrs_on_BaseHiAcc_Dis:1 ; ///<
    UINT32                            REG_RstPtrs_on_BaseLoAcc_Dis:1 ; ///<
    UINT32                               REG_RstPtrs_on_LenAccs_En:1 ; ///<
    UINT32                                    REG_DTEResvBitChkDis:1 ; ///<
    UINT32                         REG_RstGVAPtrs_on_BaseHiAcc_Dis:1 ; ///<
    UINT32                         REG_RstGVAPtrs_on_BaseLoAcc_Dis:1 ; ///<
    UINT32                            REG_RstGVAPtrs_on_LenAccs_En:1 ; ///<
    UINT32                                                RESERVED:15; ///<
    UINT32                                       REG_gmc_iommu_dis:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0000011C_STRUCT;

// Address
#define L2_SB_LOCATION_ADDRESS                                 0x13f0112c

// Type
#define L2_SB_LOCATION_TYPE                                    TYPE_SMN

#define IOMMUL2INDX_12C_SBlocated_Port_OFFSET                  0
#define IOMMUL2INDX_12C_SBlocated_Port_WIDTH                   16
#define IOMMUL2INDX_12C_SBlocated_Port_MASK                    0xffff
#define IOMMUL2INDX_12C_SBlocated_Core_OFFSET                  16
#define IOMMUL2INDX_12C_SBlocated_Core_WIDTH                   16
#define IOMMUL2INDX_12C_SBlocated_Core_MASK                    0xffff0000L

/// IOMMUL2INDX_12C
typedef union {
  struct {
    UINT32                                          SBlocated_Port:16; ///<
    UINT32                                          SBlocated_Core:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL2INDX_12C_STRUCT;

//   IOHUB::IOMMUL2INDX::L2_CONTROL_5_aliasSMN
// Address
#define L2_CONTROL_5_ADDRESS                                   0x13f01130

// Type
#define L2_CONTROL_5_TYPE                                      TYPE_SMN

#define SMN_00000130_QueueArbFBPri_OFFSET                      0
#define SMN_00000130_QueueArbFBPri_WIDTH                       1
#define SMN_00000130_QueueArbFBPri_MASK                        0x1
#define SMN_00000130_FC1Dis_OFFSET                             2
#define SMN_00000130_FC1Dis_WIDTH                              1
#define SMN_00000130_FC1Dis_MASK                               0x4
#define SMN_00000130_DTCUpdateVOneIVZero_OFFSET                3
#define SMN_00000130_DTCUpdateVOneIVZero_WIDTH                 1
#define SMN_00000130_DTCUpdateVOneIVZero_MASK                  0x8
#define SMN_00000130_DTCUpdateVZeroIVOne_OFFSET                4
#define SMN_00000130_DTCUpdateVZeroIVOne_WIDTH                 1
#define SMN_00000130_DTCUpdateVZeroIVOne_MASK                  0x10
#define SMN_00000130_FC3Dis_OFFSET                             6
#define SMN_00000130_FC3Dis_WIDTH                              1
#define SMN_00000130_FC3Dis_MASK                               0x40
#define SMN_00000130_RESERVED_OFFSET                           10
#define SMN_00000130_RESERVED_WIDTH                            2
#define SMN_00000130_RESERVED_MASK                             0xc00
#define SMN_00000130_GST_partial_ptc_cntrl_OFFSET              12
#define SMN_00000130_GST_partial_ptc_cntrl_WIDTH               7
#define SMN_00000130_GST_partial_ptc_cntrl_MASK                0x7f000
#define SMN_00000130_PCTRL_hysteresis_OFFSET                   19
#define SMN_00000130_PCTRL_hysteresis_WIDTH                    6
#define SMN_00000130_PCTRL_hysteresis_MASK                     0x1f80000
#define SMN_00000130_DTCUpdatePri_OFFSET                       25
#define SMN_00000130_DTCUpdatePri_WIDTH                        1
#define SMN_00000130_DTCUpdatePri_MASK                         0x2000000

/// SMN_00000130
typedef union {
  struct {
    UINT32                                           QueueArbFBPri:1 ; ///<
    UINT32                                                  FC1Dis:1 ; ///<
    UINT32                                     DTCUpdateVOneIVZero:1 ; ///<
    UINT32                                     DTCUpdateVZeroIVOne:1 ; ///<
    UINT32                                                  FC3Dis:1 ; ///<
    UINT32                                                RESERVED:2 ; ///<
    UINT32                                   GST_partial_ptc_cntrl:7 ; ///<
    UINT32                                        PCTRL_hysteresis:6 ; ///<
    UINT32                                            DTCUpdatePri:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000130_STRUCT;

//  IOHUB::IOMMUL2INDX::L2B_UPDATE_FILTER_CNTL_aliasSMN;
// Address
#define L2B_UPDATE_FILTER_CNTL_ADDRESS                         0x13f0114c

// Type
#define L2B_UPDATE_FILTER_CNTL_TYPE                            TYPE_SMN

#define SMN_0000014C_L2b_Update_Filter_Bypass_OFFSET           0
#define SMN_0000014C_L2b_Update_Filter_Bypass_WIDTH            1
#define SMN_0000014C_L2b_Update_Filter_Bypass_MASK             0x1
#define SMN_0000014C_L2b_Update_Filter_RdLatency_OFFSET        1
#define SMN_0000014C_L2b_Update_Filter_RdLatency_WIDTH         4
#define SMN_0000014C_L2b_Update_Filter_RdLatency_MASK          0x1e

/// SMN_0000014C
typedef union {
  struct {
    UINT32                                L2b_Update_Filter_Bypass:1 ; ///<
    UINT32                             L2b_Update_Filter_RdLatency:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0000014C_STRUCT;

//  IOHUB::IOMMUL2INDX::L2_TW_CONTROL_aliasSMN
// Address
#define L2_TW_CONTROL_ADDRESS                                  0x13f01150

// Type
#define L2_TW_CONTROL_TYPE                                     TYPE_SMN

#define SMN_00000150_RESERVED_OFFSET                           0
#define SMN_00000150_RESERVED_WIDTH                            6
#define SMN_00000150_RESERVED_MASK                             0x3f
#define SMN_00000150_TWForceCoherent_OFFSET                    6
#define SMN_00000150_TWForceCoherent_WIDTH                     1
#define SMN_00000150_TWForceCoherent_MASK                      0x40
#define SMN_00000150_TWPrefetchEn_OFFSET                       8
#define SMN_00000150_TWPrefetchEn_WIDTH                        1
#define SMN_00000150_TWPrefetchEn_MASK                         0x100
#define SMN_00000150_TWPrefetchOnly4KDis_OFFSET                9
#define SMN_00000150_TWPrefetchOnly4KDis_WIDTH                 1
#define SMN_00000150_TWPrefetchOnly4KDis_MASK                  0x200
#define SMN_00000150_TWPTEOnUntransExcl_OFFSET                 10
#define SMN_00000150_TWPTEOnUntransExcl_WIDTH                  1
#define SMN_00000150_TWPTEOnUntransExcl_MASK                   0x400
#define SMN_00000150_TWPTEOnAddrTransExcl_OFFSET               11
#define SMN_00000150_TWPTEOnAddrTransExcl_WIDTH                1
#define SMN_00000150_TWPTEOnAddrTransExcl_MASK                 0x800
#define SMN_00000150_TWPrefetchRange_OFFSET                    12
#define SMN_00000150_TWPrefetchRange_WIDTH                     3
#define SMN_00000150_TWPrefetchRange_MASK                      0x7000
#define SMN_00000150_TWFilter_Dis_OFFSET                       16
#define SMN_00000150_TWFilter_Dis_WIDTH                        1
#define SMN_00000150_TWFilter_Dis_MASK                         0x10000
#define SMN_00000150_TWFilter_64B_Dis_OFFSET                   17
#define SMN_00000150_TWFilter_64B_Dis_WIDTH                    1
#define SMN_00000150_TWFilter_64B_Dis_MASK                     0x20000
#define SMN_00000150_TWContWalkOnPErrDis_OFFSET                18
#define SMN_00000150_TWContWalkOnPErrDis_WIDTH                 1
#define SMN_00000150_TWContWalkOnPErrDis_MASK                  0x40000
#define SMN_00000150_TWSetAccessBit_Dis_OFFSET                 19
#define SMN_00000150_TWSetAccessBit_Dis_WIDTH                  1
#define SMN_00000150_TWSetAccessBit_Dis_MASK                   0x80000
#define SMN_00000150_TWClearAPBit_Dis_OFFSET                   20
#define SMN_00000150_TWClearAPBit_Dis_WIDTH                    1
#define SMN_00000150_TWClearAPBit_Dis_MASK                     0x100000

/// SMN_00000150
typedef union {
  struct {
    UINT32                                                RESERVED:6 ; ///<
    UINT32                                         TWForceCoherent:1 ; ///<
    UINT32                                            TWPrefetchEn:1 ; ///<
    UINT32                                     TWPrefetchOnly4KDis:1 ; ///<
    UINT32                                      TWPTEOnUntransExcl:1 ; ///<
    UINT32                                    TWPTEOnAddrTransExcl:1 ; ///<
    UINT32                                         TWPrefetchRange:3 ; ///<
    UINT32                                            TWFilter_Dis:1 ; ///<
    UINT32                                        TWFilter_64B_Dis:1 ; ///<
    UINT32                                     TWContWalkOnPErrDis:1 ; ///<
    UINT32                                      TWSetAccessBit_Dis:1 ; ///<
    UINT32                                        TWClearAPBit_Dis:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000150_STRUCT;

//  IOHUB::IOMMUL2INDX::L2_CP_CONTROL_aliasSMN
// Address
#define L2_CP_CONTROL_ADDRESS                                  0x13f01158

// Type
#define L2_CP_CONTROL_TYPE                                     TYPE_SMN

#define SMN_00000158_CPPrefetchDis_OFFSET                      0
#define SMN_00000158_CPPrefetchDis_WIDTH                       1
#define SMN_00000158_CPPrefetchDis_MASK                        0x1
#define SMN_00000158_CPFlushOnWait_OFFSET                      1
#define SMN_00000158_CPFlushOnWait_WIDTH                       1
#define SMN_00000158_CPFlushOnWait_MASK                        0x2
#define SMN_00000158_CPFlushOnInv_OFFSET                       2
#define SMN_00000158_CPFlushOnInv_WIDTH                        1
#define SMN_00000158_CPFlushOnInv_MASK                         0x4
#define SMN_00000158_CPRdDelay_OFFSET                          16
#define SMN_00000158_CPRdDelay_WIDTH                           16
#define SMN_00000158_CPRdDelay_MASK                            0xffff0000L

/// SMN_00000158
typedef union {
  struct {
    UINT32                                           CPPrefetchDis:1 ; ///<
    UINT32                                           CPFlushOnWait:1 ; ///<
    UINT32                                            CPFlushOnInv:1 ; ///<
    UINT32                                               CPRdDelay:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000158_STRUCT;

//    IOHUB::IOMMUL2INDX::L2_ERR_RULE_CONTROL_0_aliasSMN
// Address
#define L2_ERR_RULE_CONTROL_0_ADDRESS                          0x13f01200

// Type
#define L2_ERR_RULE_CONTROL_0_TYPE                             TYPE_SMN

#define SMN_00000200_ERRRuleLock0_OFFSET                       0
#define SMN_00000200_ERRRuleLock0_WIDTH                        1
#define SMN_00000200_ERRRuleLock0_MASK                         0x1
#define SMN_00000200_ERRRuleDisable0_OFFSET                    4
#define SMN_00000200_ERRRuleDisable0_WIDTH                     28
#define SMN_00000200_ERRRuleDisable0_MASK                      0xfffffff0L

/// SMN_00000200
typedef union {
  struct {
    UINT32                                            ERRRuleLock0:1 ; ///<
    UINT32                                         ERRRuleDisable0:28; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000200_STRUCT;


//  IOHUB::IOMMUL2INDX::L2_L2B_CK_GATE_CONTROL_aliasSMN
// Address
#define L2_L2B_CK_GATE_CONTROL_ADDRESS                         0x13f01240

// Type
#define L2_L2B_CK_GATE_CONTROL_TYPE                            TYPE_SMN

#define SMN_00000240_CKGateL2BRegsDisable_OFFSET               0
#define SMN_00000240_CKGateL2BRegsDisable_WIDTH                1
#define SMN_00000240_CKGateL2BRegsDisable_MASK                 0x1
#define SMN_00000240_CKGateL2BDynamicDisable_OFFSET            1
#define SMN_00000240_CKGateL2BDynamicDisable_WIDTH             1
#define SMN_00000240_CKGateL2BDynamicDisable_MASK              0x2
#define SMN_00000240_CKGateL2BMiscDisable_OFFSET               2
#define SMN_00000240_CKGateL2BMiscDisable_WIDTH                1
#define SMN_00000240_CKGateL2BMiscDisable_MASK                 0x4
#define SMN_00000240_CKGateL2BCacheDisable_OFFSET              3
#define SMN_00000240_CKGateL2BCacheDisable_WIDTH               1
#define SMN_00000240_CKGateL2BCacheDisable_MASK                0x8
#define SMN_00000240_CKGateL2BLength_OFFSET                    4
#define SMN_00000240_CKGateL2BLength_WIDTH                     2
#define SMN_00000240_CKGateL2BLength_MASK                      0x30
#define SMN_00000240_CKGateL2BStop_OFFSET                      6
#define SMN_00000240_CKGateL2BStop_WIDTH                       2
#define SMN_00000240_CKGateL2BStop_MASK                        0xc0
#define SMN_00000240_Reserved_31_8_OFFSET                      8
#define SMN_00000240_Reserved_31_8_WIDTH                       24
#define SMN_00000240_Reserved_31_8_MASK                        0xffffff00L

/// SMN_00000240
typedef union {
  struct {
    UINT32                                    CKGateL2BRegsDisable:1 ; ///<
    UINT32                                 CKGateL2BDynamicDisable:1 ; ///<
    UINT32                                    CKGateL2BMiscDisable:1 ; ///<
    UINT32                                   CKGateL2BCacheDisable:1 ; ///<
    UINT32                                         CKGateL2BLength:2 ; ///<
    UINT32                                           CKGateL2BStop:2 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000240_STRUCT;

//   IOHUB::IOMMUL2INDX::L2_L2B_PGSIZE_CONTROL_aliasSMN
// Address
#define L2_L2B_PGSIZE_CONTROL_ADDRESS                          0x13f01250

// Type
#define L2_L2B_PGSIZE_CONTROL_TYPE                             TYPE_SMN

#define SMN_00000250_L2BREG_GST_PGSIZE_OFFSET                  0
#define SMN_00000250_L2BREG_GST_PGSIZE_WIDTH                   7
#define SMN_00000250_L2BREG_GST_PGSIZE_MASK                    0x7f
#define SMN_00000250_L2BREG_HOST_PGSIZE_OFFSET                 8
#define SMN_00000250_L2BREG_HOST_PGSIZE_WIDTH                  7
#define SMN_00000250_L2BREG_HOST_PGSIZE_MASK                   0x7f00

/// SMN_00000250
typedef union {
  struct {
    UINT32                                       L2BREG_GST_PGSIZE:7 ; ///<
    UINT32                                      L2BREG_HOST_PGSIZE:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_00000250_STRUCT;

//    svd_group: NBIO_IOHUB_IOAPIC_aliasSMN
// Address
#define FEATURES_ENABLE_ADDRESS                                0x14300000

// Type
#define FEATURES_ENABLE_TYPE                                   TYPE_NBIOAPICCFG

#define NBIOAPICCFG_000_Ioapic_id_ext_en_OFFSET                2
#define NBIOAPICCFG_000_Ioapic_id_ext_en_WIDTH                 1
#define NBIOAPICCFG_000_Ioapic_id_ext_en_MASK                  0x4
#define NBIOAPICCFG_000_Ioapic_sb_feature_en_OFFSET            4
#define NBIOAPICCFG_000_Ioapic_sb_feature_en_WIDTH             1
#define NBIOAPICCFG_000_Ioapic_sb_feature_en_MASK              0x10
#define NBIOAPICCFG_000_Ioapic_secondary_en_OFFSET             5
#define NBIOAPICCFG_000_Ioapic_secondary_en_WIDTH              1
#define NBIOAPICCFG_000_Ioapic_secondary_en_MASK               0x20
#define NBIOAPICCFG_000_Ioapic_processor_mode_OFFSET           8
#define NBIOAPICCFG_000_Ioapic_processor_mode_WIDTH            1
#define NBIOAPICCFG_000_Ioapic_processor_mode_MASK             0x100
#define NBIOAPICCFG_000_INTx_LevelOnlyMode_OFFSET              9
#define NBIOAPICCFG_000_INTx_LevelOnlyMode_WIDTH               1
#define NBIOAPICCFG_000_INTx_LevelOnlyMode_MASK                0x200

/// NBIOAPICCFG_000
typedef union {
  struct {
    UINT32                                        Ioapic_id_ext_en:1 ; ///<
    UINT32                                    Ioapic_sb_feature_en:1 ; ///<
    UINT32                                     Ioapic_secondary_en:1 ; ///<
    UINT32                                   Ioapic_processor_mode:1 ; ///<
    UINT32                                      INTx_LevelOnlyMode:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_000_STRUCT;


// Address
#define IOAPIC_BR0_INTERRUPT_ROUTING_ADDRESS                   0x14300040

// Type
#define IOAPIC_BR0_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_040_Br0_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_040_Br0_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_040_Br0_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_040_Br0_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_040_Br0_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_040_Br0_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_040_Br0_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_040_Br0_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_040_Br0_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_040
typedef union {
  struct {
    UINT32                                        Br0_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br0_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br0_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_040_STRUCT;


// Address
#define IOAPIC_BR1_INTERRUPT_ROUTING_ADDRESS                   0x14300044

// Type
#define IOAPIC_BR1_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_044_Br1_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_044_Br1_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_044_Br1_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_044_Br1_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_044_Br1_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_044_Br1_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_044_Br1_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_044_Br1_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_044_Br1_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_044
typedef union {
  struct {
    UINT32                                        Br1_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br1_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br1_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_044_STRUCT;


// Address
#define IOAPIC_BR2_INTERRUPT_ROUTING_ADDRESS                   0x14300048

// Type
#define IOAPIC_BR2_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_048_Br2_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_048_Br2_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_048_Br2_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_048_Br2_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_048_Br2_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_048_Br2_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_048_Br2_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_048_Br2_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_048_Br2_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_048
typedef union {
  struct {
    UINT32                                        Br2_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br2_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br2_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_048_STRUCT;


// Address
#define IOAPIC_BR3_INTERRUPT_ROUTING_ADDRESS                   0x1430004c

// Type
#define IOAPIC_BR3_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_04C_Br3_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_04C_Br3_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_04C_Br3_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_04C_Br3_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_04C_Br3_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_04C_Br3_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_04C_Br3_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_04C_Br3_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_04C_Br3_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_04C
typedef union {
  struct {
    UINT32                                        Br3_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br3_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br3_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_04C_STRUCT;


// Address
#define IOAPIC_BR4_INTERRUPT_ROUTING_ADDRESS                   0x14300050

// Type
#define IOAPIC_BR4_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_050_Br4_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_050_Br4_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_050_Br4_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_050_Br4_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_050_Br4_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_050_Br4_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_050_Br4_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_050_Br4_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_050_Br4_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_050
typedef union {
  struct {
    UINT32                                        Br4_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br4_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br4_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_050_STRUCT;


// Address
#define IOAPIC_BR5_INTERRUPT_ROUTING_ADDRESS                   0x14300054

// Type
#define IOAPIC_BR5_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_054_Br5_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_054_Br5_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_054_Br5_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_054_Br5_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_054_Br5_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_054_Br5_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_054_Br5_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_054_Br5_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_054_Br5_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_054
typedef union {
  struct {
    UINT32                                        Br5_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br5_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br5_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_054_STRUCT;


// Address
#define IOAPIC_BR6_INTERRUPT_ROUTING_ADDRESS                   0x14300058

// Type
#define IOAPIC_BR6_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_058_Br6_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_058_Br6_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_058_Br6_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_058_Br6_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_058_Br6_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_058_Br6_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_058_Br6_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_058_Br6_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_058_Br6_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_058
typedef union {
  struct {
    UINT32                                        Br6_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br6_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br6_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_058_STRUCT;


// Address
#define IOAPIC_BR7_INTERRUPT_ROUTING_ADDRESS                   0x1430005c

// Type
#define IOAPIC_BR7_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_05C_Br7_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_05C_Br7_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_05C_Br7_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_05C_Br7_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_05C_Br7_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_05C_Br7_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_05C_Br7_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_05C_Br7_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_05C_Br7_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_05C
typedef union {
  struct {
    UINT32                                        Br7_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br7_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br7_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_05C_STRUCT;


// Address
#define IOAPIC_BR8_INTERRUPT_ROUTING_ADDRESS                   0x14300060

// Type
#define IOAPIC_BR8_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

#define NBIOAPICCFG_060_Br8_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_060_Br8_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_060_Br8_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_060_Br8_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_060_Br8_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_060_Br8_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_060_Br8_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_060_Br8_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_060_Br8_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_060
typedef union {
  struct {
    UINT32                                        Br8_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br8_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br8_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_060_STRUCT;


// Address
#define IOAPIC_BR9_INTERRUPT_ROUTING_ADDRESS                   0x14300064

// Type
#define IOAPIC_BR9_INTERRUPT_ROUTING_TYPE                      TYPE_SMN

#define NBIOAPICCFG_064_Br9_ext_Intr_grp_OFFSET                0
#define NBIOAPICCFG_064_Br9_ext_Intr_grp_WIDTH                 3
#define NBIOAPICCFG_064_Br9_ext_Intr_grp_MASK                  0x7
#define NBIOAPICCFG_064_Br9_ext_Intr_swz_OFFSET                4
#define NBIOAPICCFG_064_Br9_ext_Intr_swz_WIDTH                 2
#define NBIOAPICCFG_064_Br9_ext_Intr_swz_MASK                  0x30
#define NBIOAPICCFG_064_Br9_int_Intr_map_OFFSET                16
#define NBIOAPICCFG_064_Br9_int_Intr_map_WIDTH                 5
#define NBIOAPICCFG_064_Br9_int_Intr_map_MASK                  0x1f0000

/// NBIOAPICCFG_064
typedef union {
  struct {
    UINT32                                        Br9_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                        Br9_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                        Br9_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_064_STRUCT;


// Address
#define IOAPIC_BR10_INTERRUPT_ROUTING_ADDRESS                  0x14300068

// Type
#define IOAPIC_BR10_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

#define NBIOAPICCFG_068_Br10_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_068_Br10_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_068_Br10_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_068_Br10_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_068_Br10_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_068_Br10_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_068_Br10_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_068_Br10_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_068_Br10_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_068
typedef union {
  struct {
    UINT32                                       Br10_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br10_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br10_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_068_STRUCT;


// Address
#define IOAPIC_BR11_INTERRUPT_ROUTING_ADDRESS                  0x1430006c

// Type
#define IOAPIC_BR11_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_06C_Br11_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_06C_Br11_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_06C_Br11_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_06C_Br11_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_06C_Br11_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_06C_Br11_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_06C_Br11_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_06C_Br11_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_06C_Br11_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_06C
typedef union {
  struct {
    UINT32                                       Br11_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br11_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br11_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_06C_STRUCT;


// Address
#define IOAPIC_BR12_INTERRUPT_ROUTING_ADDRESS                  0x14300070

// Type
#define IOAPIC_BR12_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_070_Br12_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_070_Br12_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_070_Br12_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_070_Br12_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_070_Br12_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_070_Br12_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_070_Br12_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_070_Br12_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_070_Br12_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_070
typedef union {
  struct {
    UINT32                                       Br12_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br12_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br12_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_070_STRUCT;


// Address
#define IOAPIC_BR13_INTERRUPT_ROUTING_ADDRESS                  0x14300074

// Type
#define IOAPIC_BR13_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_074_Br13_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_074_Br13_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_074_Br13_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_074_Br13_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_074_Br13_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_074_Br13_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_074_Br13_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_074_Br13_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_074_Br13_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_074
typedef union {
  struct {
    UINT32                                       Br13_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br13_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br13_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_074_STRUCT;


// Address
#define IOAPIC_BR14_INTERRUPT_ROUTING_ADDRESS                  0x14300078

// Type
#define IOAPIC_BR14_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_078_Br14_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_078_Br14_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_078_Br14_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_078_Br14_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_078_Br14_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_078_Br14_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_078_Br14_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_078_Br14_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_078_Br14_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_078
typedef union {
  struct {
    UINT32                                       Br14_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br14_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br14_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_078_STRUCT;


// Address
#define IOAPIC_BR15_INTERRUPT_ROUTING_ADDRESS                  0x1430007c

// Type
#define IOAPIC_BR15_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_07C_Br15_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_07C_Br15_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_07C_Br15_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_07C_Br15_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_07C_Br15_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_07C_Br15_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_07C_Br15_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_07C_Br15_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_07C_Br15_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_07C
typedef union {
  struct {
    UINT32                                       Br15_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br15_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br15_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_07C_STRUCT;


// Address
#define IOAPIC_BR16_INTERRUPT_ROUTING_ADDRESS                  0x14300080

// Type
#define IOAPIC_BR16_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_080_Br16_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_080_Br16_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_080_Br16_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_080_Br16_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_080_Br16_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_080_Br16_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_080_Br16_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_080_Br16_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_080_Br16_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_080
typedef union {
  struct {
    UINT32                                       Br16_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br16_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br16_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_080_STRUCT;


// Address
#define IOAPIC_BR17_INTERRUPT_ROUTING_ADDRESS                  0x14300084

// Type
#define IOAPIC_BR17_INTERRUPT_ROUTING_TYPE                     TYPE_SMN

#define NBIOAPICCFG_084_Br17_ext_Intr_grp_OFFSET               0
#define NBIOAPICCFG_084_Br17_ext_Intr_grp_WIDTH                3
#define NBIOAPICCFG_084_Br17_ext_Intr_grp_MASK                 0x7
#define NBIOAPICCFG_084_Br17_ext_Intr_swz_OFFSET               4
#define NBIOAPICCFG_084_Br17_ext_Intr_swz_WIDTH                2
#define NBIOAPICCFG_084_Br17_ext_Intr_swz_MASK                 0x30
#define NBIOAPICCFG_084_Br17_int_Intr_map_OFFSET               16
#define NBIOAPICCFG_084_Br17_int_Intr_map_WIDTH                5
#define NBIOAPICCFG_084_Br17_int_Intr_map_MASK                 0x1f0000

/// NBIOAPICCFG_084
typedef union {
  struct {
    UINT32                                       Br17_ext_Intr_grp:3 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                       Br17_ext_Intr_swz:2 ; ///<
    UINT32                                               Reserved1:10; ///<
    UINT32                                       Br17_int_Intr_map:5 ; ///<
    UINT32                                               Reserved2:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_084_STRUCT;

// Register Name L1_MISC_CNTRL_1
// Address
// Address
#define L1_MISC_CNTRL_1_PCIE0_ADDRESS                          0x1470001c
#define L1_MISC_CNTRL_1_PCIE1_ADDRESS                          0x1480001c
#define L1_MISC_CNTRL_1_NBIF0_ADDRESS                          0x1490001c
#define L1_MISC_CNTRL_1_IOAGR_ADDRESS                          0x14a0001c
#define L1_DEBUG_1_PCIE0_ADDRESS                               0x1470001c
#define L1_DEBUG_1_PCIE1_ADDRESS                               0x1480001c
#define L1_DEBUG_1_NBIF0_ADDRESS                               0x1490001c
#define L1_DEBUG_1_IOAGR_ADDRESS                               0x14a0001c

// Type
#define L1_MISC_CNTRL_1_TYPE                                              TYPE_SMN

#define L1_MISC_CNTRL_1_REG_force_OrderStreamID_func_OFFSET               0
#define L1_MISC_CNTRL_1_REG_force_OrderStreamID_func_WIDTH                1
#define L1_MISC_CNTRL_1_REG_force_OrderStreamID_func_MASK                 0x1
#define L1_MISC_CNTRL_1_REG_ForceBypass_OFFSET                            1
#define L1_MISC_CNTRL_1_REG_ForceBypass_WIDTH                             1
#define L1_MISC_CNTRL_1_REG_ForceBypass_MASK                              0x2
#define L1_MISC_CNTRL_1_REG_cmdwait_wait_emptwq_OFFSET                    2
#define L1_MISC_CNTRL_1_REG_cmdwait_wait_emptwq_WIDTH                     1
#define L1_MISC_CNTRL_1_REG_cmdwait_wait_emptwq_MASK                      0x4
#define L1_MISC_CNTRL_1_Reserved_3_3_OFFSET                               3
#define L1_MISC_CNTRL_1_Reserved_3_3_WIDTH                                1
#define L1_MISC_CNTRL_1_Reserved_3_3_MASK                                 0x8
#define L1_MISC_CNTRL_1_REG_inv_wait_emptwq_OFFSET                        4
#define L1_MISC_CNTRL_1_REG_inv_wait_emptwq_WIDTH                         1
#define L1_MISC_CNTRL_1_REG_inv_wait_emptwq_MASK                          0x10
#define L1_MISC_CNTRL_1_Reserved_5_5_OFFSET                               5
#define L1_MISC_CNTRL_1_Reserved_5_5_WIDTH                                1
#define L1_MISC_CNTRL_1_Reserved_5_5_MASK                                 0x20
#define L1_MISC_CNTRL_1_REG_force_invalid_filter_OFFSET                   6
#define L1_MISC_CNTRL_1_REG_force_invalid_filter_WIDTH                    1
#define L1_MISC_CNTRL_1_REG_force_invalid_filter_MASK                     0x40
#define L1_MISC_CNTRL_1_REG_L2toL1_rsp_ir_iw_set_OFFSET                   7
#define L1_MISC_CNTRL_1_REG_L2toL1_rsp_ir_iw_set_WIDTH                    1
#define L1_MISC_CNTRL_1_REG_L2toL1_rsp_ir_iw_set_MASK                     0x80
#define L1_MISC_CNTRL_1_Reserved_8_8_OFFSET                               8
#define L1_MISC_CNTRL_1_Reserved_8_8_WIDTH                                1
#define L1_MISC_CNTRL_1_Reserved_8_8_MASK                                 0x100
#define L1_MISC_CNTRL_1_REG_L2toL1_credit_ctrl_OFFSET                     9
#define L1_MISC_CNTRL_1_REG_L2toL1_credit_ctrl_WIDTH                      1
#define L1_MISC_CNTRL_1_REG_L2toL1_credit_ctrl_MASK                       0x200
#define L1_MISC_CNTRL_1_REG_allow_update_dis_OFFSET                       10
#define L1_MISC_CNTRL_1_REG_allow_update_dis_WIDTH                        1
#define L1_MISC_CNTRL_1_REG_allow_update_dis_MASK                         0x400
#define L1_MISC_CNTRL_1_Reserved_11_11_OFFSET                             11
#define L1_MISC_CNTRL_1_Reserved_11_11_WIDTH                              1
#define L1_MISC_CNTRL_1_Reserved_11_11_MASK                               0x800
#define L1_MISC_CNTRL_1_REG_Truncate_ATS_Rsp_Over4K_En_OFFSET             12
#define L1_MISC_CNTRL_1_REG_Truncate_ATS_Rsp_Over4K_En_WIDTH              1
#define L1_MISC_CNTRL_1_REG_Truncate_ATS_Rsp_Over4K_En_MASK               0x1000
#define L1_MISC_CNTRL_1_REG_Block_On_4K_wait_dis_OFFSET                   13
#define L1_MISC_CNTRL_1_REG_Block_On_4K_wait_dis_WIDTH                    1
#define L1_MISC_CNTRL_1_REG_Block_On_4K_wait_dis_MASK                     0x2000
#define L1_MISC_CNTRL_1_REG_ATS_no_phys_overlap_En_OFFSET                 14
#define L1_MISC_CNTRL_1_REG_ATS_no_phys_overlap_En_WIDTH                  1
#define L1_MISC_CNTRL_1_REG_ATS_no_phys_overlap_En_MASK                   0x4000
#define L1_MISC_CNTRL_1_REG_guest_addr_mask_en_OFFSET                     15
#define L1_MISC_CNTRL_1_REG_guest_addr_mask_en_WIDTH                      1
#define L1_MISC_CNTRL_1_REG_guest_addr_mask_en_MASK                       0x8000
#define L1_MISC_CNTRL_1_REG_aerlog_on_abrt_OFFSET                         16
#define L1_MISC_CNTRL_1_REG_aerlog_on_abrt_WIDTH                          1
#define L1_MISC_CNTRL_1_REG_aerlog_on_abrt_MASK                           0x10000
#define L1_MISC_CNTRL_1_REG_enable_nw_OFFSET                              17
#define L1_MISC_CNTRL_1_REG_enable_nw_WIDTH                               1
#define L1_MISC_CNTRL_1_REG_enable_nw_MASK                                0x20000
#define L1_MISC_CNTRL_1_REG_force_pasid_vld_OFFSET                        18
#define L1_MISC_CNTRL_1_REG_force_pasid_vld_WIDTH                         1
#define L1_MISC_CNTRL_1_REG_force_pasid_vld_MASK                          0x40000
#define L1_MISC_CNTRL_1_Reserved_19_19_OFFSET                             19
#define L1_MISC_CNTRL_1_Reserved_19_19_WIDTH                              1
#define L1_MISC_CNTRL_1_Reserved_19_19_MASK                               0x80000
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_EX_OFFSET                     20
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_EX_WIDTH                      1
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_EX_MASK                       0x100000
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_PMR_OFFSET                    21
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_PMR_WIDTH                     1
#define L1_MISC_CNTRL_1_REG_force_tlpprefix_PMR_MASK                      0x200000
#define L1_MISC_CNTRL_1_REG_ignore_iwir_for_s_bit_OFFSET                  22
#define L1_MISC_CNTRL_1_REG_ignore_iwir_for_s_bit_WIDTH                   1
#define L1_MISC_CNTRL_1_REG_ignore_iwir_for_s_bit_MASK                    0x400000
#define L1_MISC_CNTRL_1_REG_force_ats_len_OFFSET                          23
#define L1_MISC_CNTRL_1_REG_force_ats_len_WIDTH                           4
#define L1_MISC_CNTRL_1_REG_force_ats_len_MASK                            0x7800000
#define L1_MISC_CNTRL_1_RESERVED_OFFSET                                   27
#define L1_MISC_CNTRL_1_RESERVED_WIDTH                                    5
#define L1_MISC_CNTRL_1_RESERVED_MASK                                     0xf8000000L

/// L1_MISC_CNTRL_1
typedef union {
  struct {
    UINT32                            REG_force_OrderStreamID_func:1 ; ///<
    UINT32                                         REG_ForceBypass:1 ; ///<
    UINT32                                 REG_cmdwait_wait_emptwq:1 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                     REG_inv_wait_emptwq:1 ; ///<
    UINT32                                            Reserved_5_5:1 ; ///<
    UINT32                                REG_force_invalid_filter:1 ; ///<
    UINT32                                REG_L2toL1_rsp_ir_iw_set:1 ; ///<
    UINT32                                            Reserved_8_8:1 ; ///<
    UINT32                                  REG_L2toL1_credit_ctrl:1 ; ///<
    UINT32                                    REG_allow_update_dis:1 ; ///<
    UINT32                                          Reserved_11_11:1 ; ///<
    UINT32                          REG_Truncate_ATS_Rsp_Over4K_En:1 ; ///<
    UINT32                                REG_Block_On_4K_wait_dis:1 ; ///<
    UINT32                              REG_ATS_no_phys_overlap_En:1 ; ///<
    UINT32                                  REG_guest_addr_mask_en:1 ; ///<
    UINT32                                      REG_aerlog_on_abrt:1 ; ///<
    UINT32                                           REG_enable_nw:1 ; ///<
    UINT32                                     REG_force_pasid_vld:1 ; ///<
    UINT32                                          Reserved_19_19:1 ; ///<
    UINT32                                  REG_force_tlpprefix_EX:1 ; ///<
    UINT32                                 REG_force_tlpprefix_PMR:1 ; ///<
    UINT32                               REG_ignore_iwir_for_s_bit:1 ; ///<
    UINT32                                       REG_force_ats_len:4 ; ///<
    UINT32                                                RESERVED:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_MISC_CNTRL_1_STRUCT;


// Address
#define L1_CNTRL_0_PCIE0_ADDRESS                               0x14700030
#define L1_CNTRL_0_PCIE1_ADDRESS                               0x14800030
#define L1_CNTRL_0_NBIF0_ADDRESS                               0x14900030
#define L1_CNTRL_0_IOAGR_ADDRESS                               0x14a00030

// Type
#define L1_CNTRL_0_TYPE                                              TYPE_SMN

#define L1_CNTRL_0_Unfilter_dis_OFFSET                               0
#define L1_CNTRL_0_Unfilter_dis_WIDTH                                1
#define L1_CNTRL_0_Unfilter_dis_MASK                                 0x1
#define L1_CNTRL_0_Fragment_dis_OFFSET                               1
#define L1_CNTRL_0_Fragment_dis_WIDTH                                1
#define L1_CNTRL_0_Fragment_dis_MASK                                 0x2
#define L1_CNTRL_0_CacheIR_only_OFFSET                               2
#define L1_CNTRL_0_CacheIR_only_WIDTH                                1
#define L1_CNTRL_0_CacheIR_only_MASK                                 0x4
#define L1_CNTRL_0_CacheIW_only_OFFSET                               3
#define L1_CNTRL_0_CacheIW_only_WIDTH                                1
#define L1_CNTRL_0_CacheIW_only_MASK                                 0x8
#define L1_CNTRL_0_Reserved0_OFFSET                                  4
#define L1_CNTRL_0_Reserved0_WIDTH                                   1
#define L1_CNTRL_0_Reserved0_MASK                                    0x10
#define L1_CNTRL_0_RESERVED_OFFSET                                   5
#define L1_CNTRL_0_RESERVED_WIDTH                                    1
#define L1_CNTRL_0_RESERVED_MASK                                     0x20
#define L1_CNTRL_0_Reserved_7_6_OFFSET                               6
#define L1_CNTRL_0_Reserved_7_6_WIDTH                                2
#define L1_CNTRL_0_Reserved_7_6_MASK                                 0xc0
#define L1_CNTRL_0_L2Credits_OFFSET                                  8
#define L1_CNTRL_0_L2Credits_WIDTH                                   6
#define L1_CNTRL_0_L2Credits_MASK                                    0x3f00
#define L1_CNTRL_0_Reserved1_OFFSET                                  14
#define L1_CNTRL_0_Reserved1_WIDTH                                   6
#define L1_CNTRL_0_Reserved1_MASK                                    0xfc000
#define L1_CNTRL_0_L1Banks_OFFSET                                    20
#define L1_CNTRL_0_L1Banks_WIDTH                                     2
#define L1_CNTRL_0_L1Banks_MASK                                      0x300000
#define L1_CNTRL_0_Reserved_23_22_OFFSET                             22
#define L1_CNTRL_0_Reserved_23_22_WIDTH                              2
#define L1_CNTRL_0_Reserved_23_22_MASK                               0xc00000
#define L1_CNTRL_0_L1Entries_OFFSET                                  24
#define L1_CNTRL_0_L1Entries_WIDTH                                   4
#define L1_CNTRL_0_L1Entries_MASK                                    0xf000000
#define L1_CNTRL_0_L1ErrEventDetectDis_OFFSET                        28
#define L1_CNTRL_0_L1ErrEventDetectDis_WIDTH                         1
#define L1_CNTRL_0_L1ErrEventDetectDis_MASK                          0x10000000
#define L1_CNTRL_0_L1ForceHostRspPassPWHigh_OFFSET                   29
#define L1_CNTRL_0_L1ForceHostRspPassPWHigh_WIDTH                    2
#define L1_CNTRL_0_L1ForceHostRspPassPWHigh_MASK                     0x60000000
#define L1_CNTRL_0_L1InterruptHalfDwDis_OFFSET                       31
#define L1_CNTRL_0_L1InterruptHalfDwDis_WIDTH                        1
#define L1_CNTRL_0_L1InterruptHalfDwDis_MASK                         0x80000000L

/// L1_CNTRL_0
typedef union {
  struct {
    UINT32                                            Unfilter_dis:1 ; ///<
    UINT32                                            Fragment_dis:1 ; ///<
    UINT32                                            CacheIR_only:1 ; ///<
    UINT32                                            CacheIW_only:1 ; ///<
    UINT32                                               Reserved0:1 ; ///<
    UINT32                                                RESERVED:1 ; ///<
    UINT32                                            Reserved_7_6:2 ; ///<
    UINT32                                               L2Credits:6 ; ///<
    UINT32                                               Reserved1:6 ; ///<
    UINT32                                                 L1Banks:2 ; ///<
    UINT32                                          Reserved_23_22:2 ; ///<
    UINT32                                               L1Entries:4 ; ///<
    UINT32                                     L1ErrEventDetectDis:1 ; ///<
    UINT32                                L1ForceHostRspPassPWHigh:2 ; ///<
    UINT32                                    L1InterruptHalfDwDis:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_CNTRL_0_STRUCT;


#define L1_CNTRL_1_PCIE0_ADDRESS                               0x14700034
#define L1_CNTRL_1_PCIE1_ADDRESS                               0x14800034
#define L1_CNTRL_1_NBIF0_ADDRESS                               0x14900034
#define L1_CNTRL_1_IOAGR_ADDRESS                               0x14a00034


// Address
#define L1_CNTRL_2_PCIE0_ADDRESS                               0x14700038
#define L1_CNTRL_2_PCIE1_ADDRESS                               0x14800038
#define L1_CNTRL_2_NBIF0_ADDRESS                               0x14900038
#define L1_CNTRL_2_IOAGR_ADDRESS                               0x14a00038

// Type
#define L1_CNTRL_2_TYPE                                  TYPE_SMN

#define L1_CNTRL_2_L1Disable_OFFSET                      0
#define L1_CNTRL_2_L1Disable_WIDTH                       1
#define L1_CNTRL_2_L1Disable_MASK                        0x1
#define L1_CNTRL_2_MSI_to_HT_remap_dis_OFFSET            1
#define L1_CNTRL_2_MSI_to_HT_remap_dis_WIDTH             1
#define L1_CNTRL_2_MSI_to_HT_remap_dis_MASK              0x2
#define L1_CNTRL_2_L1_abrt_ats_dis_OFFSET                2
#define L1_CNTRL_2_L1_abrt_ats_dis_WIDTH                 1
#define L1_CNTRL_2_L1_abrt_ats_dis_MASK                  0x4
#define L1_CNTRL_2_Reserved_3_3_OFFSET                   3
#define L1_CNTRL_2_Reserved_3_3_WIDTH                    1
#define L1_CNTRL_2_Reserved_3_3_MASK                     0x8
#define L1_CNTRL_2_RESERVED_OFFSET                       4
#define L1_CNTRL_2_RESERVED_WIDTH                        20
#define L1_CNTRL_2_RESERVED_MASK                         0xfffff0
#define L1_CNTRL_2_CPD_RESP_MODE_OFFSET                  24
#define L1_CNTRL_2_CPD_RESP_MODE_WIDTH                   3
#define L1_CNTRL_2_CPD_RESP_MODE_MASK                    0x7000000
#define L1_CNTRL_2_L1NonConsumedDataErrorSignalEn_OFFSET 27
#define L1_CNTRL_2_L1NonConsumedDataErrorSignalEn_WIDTH  1
#define L1_CNTRL_2_L1NonConsumedDataErrorSignalEn_MASK   0x8000000
#define L1_CNTRL_2_L1ConsumedDataErrorSignalEn_OFFSET    28
#define L1_CNTRL_2_L1ConsumedDataErrorSignalEn_WIDTH     1
#define L1_CNTRL_2_L1ConsumedDataErrorSignalEn_MASK      0x10000000
#define L1_CNTRL_2_L1SDPParityEn_OFFSET                  29
#define L1_CNTRL_2_L1SDPParityEn_WIDTH                   1
#define L1_CNTRL_2_L1SDPParityEn_MASK                    0x20000000
#define L1_CNTRL_2_FlushVC_HRT1_Inv_OFFSET               30
#define L1_CNTRL_2_FlushVC_HRT1_Inv_WIDTH                1
#define L1_CNTRL_2_FlushVC_HRT1_Inv_MASK                 0x40000000
#define L1_CNTRL_2_FlushVC_HRT1_IntInv_OFFSET            31
#define L1_CNTRL_2_FlushVC_HRT1_IntInv_WIDTH             1
#define L1_CNTRL_2_FlushVC_HRT1_IntInv_MASK              0x80000000L

/// L1_CNTRL_2
typedef union {
  struct {
    UINT32                                               L1Disable:1 ; ///<
    UINT32                                     MSI_to_HT_remap_dis:1 ; ///<
    UINT32                                         L1_abrt_ats_dis:1 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                                RESERVED:20; ///<
    UINT32                                           CPD_RESP_MODE:3 ; ///<
    UINT32                          L1NonConsumedDataErrorSignalEn:1 ; ///<
    UINT32                             L1ConsumedDataErrorSignalEn:1 ; ///<
    UINT32                                           L1SDPParityEn:1 ; ///<
    UINT32                                        FlushVC_HRT1_Inv:1 ; ///<
    UINT32                                     FlushVC_HRT1_IntInv:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_CNTRL_2_STRUCT;

// Address
#define L1_CNTRL_4_PCIE0_ADDRESS                               0x147000c8
#define L1_CNTRL_4_PCIE1_ADDRESS                               0x148000c8
#define L1_CNTRL_4_NBIF0_ADDRESS                               0x149000c8
#define L1_CNTRL_4_IOAGR_ADDRESS                               0x14a000c8

// Type
#define L1_CNTRL_4_TYPE                                    TYPE_SMN

#define L1_CNTRL_4_ATS_multiple_resp_en_OFFSET           0
#define L1_CNTRL_4_ATS_multiple_resp_en_WIDTH            1
#define L1_CNTRL_4_ATS_multiple_resp_en_MASK             0x1
#define L1_CNTRL_4_ATS_multiple_L1toL2_en_OFFSET         1
#define L1_CNTRL_4_ATS_multiple_L1toL2_en_WIDTH          1
#define L1_CNTRL_4_ATS_multiple_L1toL2_en_MASK           0x2
#define L1_CNTRL_4_Timeout_pulse_ext_En_OFFSET           2
#define L1_CNTRL_4_Timeout_pulse_ext_En_WIDTH            1
#define L1_CNTRL_4_Timeout_pulse_ext_En_MASK             0x4
#define L1_CNTRL_4_TlpPrefixErr_En_OFFSET                3
#define L1_CNTRL_4_TlpPrefixErr_En_WIDTH                 1
#define L1_CNTRL_4_TlpPrefixErr_En_MASK                  0x8
#define L1_CNTRL_4_RESERVED_OFFSET                       4
#define L1_CNTRL_4_RESERVED_WIDTH                        19
#define L1_CNTRL_4_RESERVED_MASK                         0x7ffff0
#define L1_CNTRL_4_AtsRsp_send_mem_type_en_OFFSET        23
#define L1_CNTRL_4_AtsRsp_send_mem_type_en_WIDTH         1
#define L1_CNTRL_4_AtsRsp_send_mem_type_en_MASK          0x800000
#define L1_CNTRL_4_IntGfx_UnitID_Val_OFFSET              24
#define L1_CNTRL_4_IntGfx_UnitID_Val_WIDTH               7
#define L1_CNTRL_4_IntGfx_UnitID_Val_MASK                0x7f000000

/// IOMMUL1IOAGR_0C8
typedef union {
  struct {
    UINT32                                    ATS_multiple_resp_en:1 ; ///<
    UINT32                                  ATS_multiple_L1toL2_en:1 ; ///<
    UINT32                                    Timeout_pulse_ext_En:1 ; ///<
    UINT32                                         TlpPrefixErr_En:1 ; ///<
    UINT32                                                RESERVED:19; ///<
    UINT32                                 AtsRsp_send_mem_type_en:1 ; ///<
    UINT32                                       IntGfx_UnitID_Val:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_CNTRL_4_STRUCT;



// Register Name L1_FEATURE_CNTRL

// Address
#define L1_FEATURE_CNTRL_PCIE0_ADDRESS                         0x1470009C
#define L1_FEATURE_CNTRL_PCIE1_ADDRESS                         0x1480009C
#define L1_FEATURE_CNTRL_NBIF0_ADDRESS                         0x1490009C
#define L1_FEATURE_CNTRL_IOAGR_ADDRESS                         0x14a0009C

// Type
#define L1_FEATURE_CNTRL_TYPE                                  TYPE_SMN

#define L1_FEATURE_CNTRL_Rsv_sticky_bits0_OFFSET               0
#define L1_FEATURE_CNTRL_Rsv_sticky_bits0_WIDTH                1
#define L1_FEATURE_CNTRL_Rsv_sticky_bits0_MASK                 0x1
#define L1_FEATURE_CNTRL_PMR_lock_bit_OFFSET                   1
#define L1_FEATURE_CNTRL_PMR_lock_bit_WIDTH                    1
#define L1_FEATURE_CNTRL_PMR_lock_bit_MASK                     0x2
#define L1_FEATURE_CNTRL_EXE_lock_bit_OFFSET                   2
#define L1_FEATURE_CNTRL_EXE_lock_bit_WIDTH                    1
#define L1_FEATURE_CNTRL_EXE_lock_bit_MASK                     0x4
#define L1_FEATURE_CNTRL_Rsv_sticky_bits7to3_OFFSET            3
#define L1_FEATURE_CNTRL_Rsv_sticky_bits7to3_WIDTH             5
#define L1_FEATURE_CNTRL_Rsv_sticky_bits7to3_MASK              0xf8
#define L1_FEATURE_CNTRL_Reserved_31_8_OFFSET                  8
#define L1_FEATURE_CNTRL_Reserved_31_8_WIDTH                   24
#define L1_FEATURE_CNTRL_Reserved_31_8_MASK                    0xffffff00L

/// L1_FEATURE_CNTRL
typedef union {
  struct {
    UINT32                                        Rsv_sticky_bits0:1 ; ///<
    UINT32                                            PMR_lock_bit:1 ; ///<
    UINT32                                            EXE_lock_bit:1 ; ///<
    UINT32                                     Rsv_sticky_bits7to3:5 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_FEATURE_CNTRL_STRUCT;

// Address
#define L1_CLKCNTRL_0_PCIE0_ADDRESS                              0x147000cc
#define L1_CLKCNTRL_0_PCIE1_ADDRESS                              0x148000cc
#define L1_CLKCNTRL_0_NBIF0_ADDRESS                              0x149000cc
#define L1_CLKCNTRL_0_IOAGR_ADDRESS                              0x14a000cc

// Type
#define L1_CLKCNTRL_0_TYPE                                    TYPE_SMN

#define L1_CLKCNTRL_0_L1_DMA_CLKGATE_EN_OFFSET              4
#define L1_CLKCNTRL_0_L1_DMA_CLKGATE_EN_WIDTH               1
#define L1_CLKCNTRL_0_L1_DMA_CLKGATE_EN_MASK                0x10
#define L1_CLKCNTRL_0_L1_CACHE_CLKGATE_EN_OFFSET            5
#define L1_CLKCNTRL_0_L1_CACHE_CLKGATE_EN_WIDTH             1
#define L1_CLKCNTRL_0_L1_CACHE_CLKGATE_EN_MASK              0x20
#define L1_CLKCNTRL_0_L1_CPSLV_CLKGATE_EN_OFFSET            6
#define L1_CLKCNTRL_0_L1_CPSLV_CLKGATE_EN_WIDTH             1
#define L1_CLKCNTRL_0_L1_CPSLV_CLKGATE_EN_MASK              0x40
#define L1_CLKCNTRL_0_L1_PERF_CLKGATE_EN_OFFSET             8
#define L1_CLKCNTRL_0_L1_PERF_CLKGATE_EN_WIDTH              1
#define L1_CLKCNTRL_0_L1_PERF_CLKGATE_EN_MASK               0x100
#define L1_CLKCNTRL_0_L1_MEMORY_CLKGATE_EN_OFFSET           9
#define L1_CLKCNTRL_0_L1_MEMORY_CLKGATE_EN_WIDTH            1
#define L1_CLKCNTRL_0_L1_MEMORY_CLKGATE_EN_MASK             0x200
#define L1_CLKCNTRL_0_L1_REG_CLKGATE_EN_OFFSET              10
#define L1_CLKCNTRL_0_L1_REG_CLKGATE_EN_WIDTH               1
#define L1_CLKCNTRL_0_L1_REG_CLKGATE_EN_MASK                0x400
#define L1_CLKCNTRL_0_L1_HOSTREQ_CLKGATE_EN_OFFSET          11
#define L1_CLKCNTRL_0_L1_HOSTREQ_CLKGATE_EN_WIDTH           1
#define L1_CLKCNTRL_0_L1_HOSTREQ_CLKGATE_EN_MASK            0x800
#define L1_CLKCNTRL_0_L1_DMARSP_CLKGATE_EN_OFFSET           12
#define L1_CLKCNTRL_0_L1_DMARSP_CLKGATE_EN_WIDTH            1
#define L1_CLKCNTRL_0_L1_DMARSP_CLKGATE_EN_MASK             0x1000
#define L1_CLKCNTRL_0_L1_HOSTRSP_CLKGATE_EN_OFFSET          13
#define L1_CLKCNTRL_0_L1_HOSTRSP_CLKGATE_EN_WIDTH           1
#define L1_CLKCNTRL_0_L1_HOSTRSP_CLKGATE_EN_MASK            0x2000
#define L1_CLKCNTRL_0_L1_CLKGATE_HYSTERESIS_OFFSET          14
#define L1_CLKCNTRL_0_L1_CLKGATE_HYSTERESIS_WIDTH           8
#define L1_CLKCNTRL_0_L1_CLKGATE_HYSTERESIS_MASK            0x3fc000
#define L1_CLKCNTRL_0_reserved_OFFSET                       22
#define L1_CLKCNTRL_0_reserved_WIDTH                        9
#define L1_CLKCNTRL_0_reserved_MASK                         0x7fc00000
#define L1_CLKCNTRL_0_L1_L2_CLKGATE_EN_OFFSET               31
#define L1_CLKCNTRL_0_L1_L2_CLKGATE_EN_WIDTH                1
#define L1_CLKCNTRL_0_L1_L2_CLKGATE_EN_MASK                 0x80000000L

/// L1_CLK_CNTROL0
typedef union {
  struct {
    UINT32                                       L1_DMA_CLKGATE_EN:1 ; ///<
    UINT32                                     L1_CACHE_CLKGATE_EN:1 ; ///<
    UINT32                                     L1_CPSLV_CLKGATE_EN:1 ; ///<
    UINT32                                      L1_PERF_CLKGATE_EN:1 ; ///<
    UINT32                                    L1_MEMORY_CLKGATE_EN:1 ; ///<
    UINT32                                       L1_REG_CLKGATE_EN:1 ; ///<
    UINT32                                   L1_HOSTREQ_CLKGATE_EN:1 ; ///<
    UINT32                                    L1_DMARSP_CLKGATE_EN:1 ; ///<
    UINT32                                   L1_HOSTRSP_CLKGATE_EN:1 ; ///<
    UINT32                                   L1_CLKGATE_HYSTERESIS:8 ; ///<
    UINT32                                                reserved:9 ; ///<
    UINT32                                        L1_L2_CLKGATE_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_CLKCNTRL_0_STRUCT;

//IOHUB::IOMMUL1::L1_CNTRL_4_instIOMMUL1INT0_aliasSMN  NBIF
// Address
#define L1_SB_LOCATION_PCIE0_ADDRESS                                 0x14700024
#define L1_SB_LOCATION_PCIE1_ADDRESS                                 0x14800024
#define L1_SB_LOCATION_NBIF0_ADDRESS                                 0x14900024
#define L1_SB_LOCATION_IOAGR_ADDRESS                                 0x14a00024

// Type
#define L1_SB_LOCATION_TYPE                                    TYPE_SMN

#define L1_SB_LOCATION_SBlocated_Port_OFFSET                 0
#define L1_SB_LOCATION_SBlocated_Port_WIDTH                  16
#define L1_SB_LOCATION_SBlocated_Port_MASK                   0xffff
#define L1_SB_LOCATION_SBlocated_Core_OFFSET                 16
#define L1_SB_LOCATION_SBlocated_Core_WIDTH                  16
#define L1_SB_LOCATION_SBlocated_Core_MASK                   0xffff0000L

/// L1_SB_LOCATION
typedef union {
  struct {
    UINT32                                          SBlocated_Port:16; ///<
    UINT32                                          SBlocated_Core:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} L1_SB_LOCATION_STRUCT;

//  IOHUB::IOMMUL2A::L2A_UPDATE_FILTER_CNTL_aliasSMN;
// Address
#define L2A_UPDATE_FILTER_CNTL_ADDRESS                         0x15700088

// Type
#define L2A_UPDATE_FILTER_CNTL_TYPE                            TYPE_SMN

#define SMN_15700088_L2a_Update_Filter_Bypass_OFFSET           0
#define SMN_15700088_L2a_Update_Filter_Bypass_WIDTH            1
#define SMN_15700088_L2a_Update_Filter_Bypass_MASK             0x1
#define SMN_15700088_L2a_Update_Filter_RdLatency_OFFSET        1
#define SMN_15700088_L2a_Update_Filter_RdLatency_WIDTH         4
#define SMN_15700088_L2a_Update_Filter_RdLatency_MASK          0x1e

/// SMN_15700088
typedef union {
  struct {
    UINT32                                L2a_Update_Filter_Bypass:1 ; ///<
    UINT32                             L2a_Update_Filter_RdLatency:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_15700088_STRUCT;

//   IOHUB::IOMMUL2A::L2_ERR_RULE_CONTROL_3_aliasSMN
// Address
#define L2_ERR_RULE_CONTROL_3_ADDRESS                          0x157000c0

// Type
#define L2_ERR_RULE_CONTROL_3_TYPE                             TYPE_SMN

#define SMN_157000C0_ERRRuleLock1_OFFSET                       0
#define SMN_157000C0_ERRRuleLock1_WIDTH                        1
#define SMN_157000C0_ERRRuleLock1_MASK                         0x1
#define SMN_157000C0_ERRRuleDisable3_OFFSET                    4
#define SMN_157000C0_ERRRuleDisable3_WIDTH                     28
#define SMN_157000C0_ERRRuleDisable3_MASK                      0xfffffff0L

/// SMN_157000C0
typedef union {
  struct {
    UINT32                                            ERRRuleLock1:1 ; ///<
    UINT32                                         ERRRuleDisable3:28; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_157000C0_STRUCT;

//   IOHUB::IOMMUL2A::L2_L2A_CK_GATE_CONTROL_aliasSMN
// Address
#define L2_L2A_CK_GATE_CONTROL_ADDRESS                         0x157000cc

// Type
#define L2_L2A_CK_GATE_CONTROL_TYPE                            TYPE_IOMMUL2A

#define IOMMUL2A_0CC_CKGateL2ARegsDisable_OFFSET               0
#define IOMMUL2A_0CC_CKGateL2ARegsDisable_WIDTH                1
#define IOMMUL2A_0CC_CKGateL2ARegsDisable_MASK                 0x1
#define IOMMUL2A_0CC_CKGateL2ADynamicDisable_OFFSET            1
#define IOMMUL2A_0CC_CKGateL2ADynamicDisable_WIDTH             1
#define IOMMUL2A_0CC_CKGateL2ADynamicDisable_MASK              0x2
#define IOMMUL2A_0CC_CKGateL2ACacheDisable_OFFSET              2
#define IOMMUL2A_0CC_CKGateL2ACacheDisable_WIDTH               1
#define IOMMUL2A_0CC_CKGateL2ACacheDisable_MASK                0x4
#define IOMMUL2A_0CC_CKGateL2ASpare_OFFSET                     3
#define IOMMUL2A_0CC_CKGateL2ASpare_WIDTH                      1
#define IOMMUL2A_0CC_CKGateL2ASpare_MASK                       0x8
#define IOMMUL2A_0CC_CKGateL2ALength_OFFSET                    4
#define IOMMUL2A_0CC_CKGateL2ALength_WIDTH                     2
#define IOMMUL2A_0CC_CKGateL2ALength_MASK                      0x30
#define IOMMUL2A_0CC_CKGateL2AStop_OFFSET                      6
#define IOMMUL2A_0CC_CKGateL2AStop_WIDTH                       2
#define IOMMUL2A_0CC_CKGateL2AStop_MASK                        0xc0
#define IOMMUL2A_0CC_Reserved_31_8_OFFSET                      8
#define IOMMUL2A_0CC_Reserved_31_8_WIDTH                       24
#define IOMMUL2A_0CC_Reserved_31_8_MASK                        0xffffff00L

/// IOMMUL2A_0CC
typedef union {
  struct {
    UINT32                                    CKGateL2ARegsDisable:1 ; ///<
    UINT32                                 CKGateL2ADynamicDisable:1 ; ///<
    UINT32                                   CKGateL2ACacheDisable:1 ; ///<
    UINT32                                          CKGateL2ASpare:1 ; ///<
    UINT32                                         CKGateL2ALength:2 ; ///<
    UINT32                                           CKGateL2AStop:2 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL2A_0CC_STRUCT;

//   IOHUB::IOMMUL2A::L2_L2A_PGSIZE_CONTROL_aliasSMN;
// Address
#define L2_L2A_PGSIZE_CONTROL_ADDRESS                          0x157000d0

// Type
#define L2_L2A_PGSIZE_CONTROL_TYPE                             TYPE_SMN

#define SMN_157000D0_L2AREG_GST_PGSIZE_OFFSET                  0
#define SMN_157000D0_L2AREG_GST_PGSIZE_WIDTH                   7
#define SMN_157000D0_L2AREG_GST_PGSIZE_MASK                    0x7f
#define SMN_157000D0_L2AREG_HOST_PGSIZE_OFFSET                 8
#define SMN_157000D0_L2AREG_HOST_PGSIZE_WIDTH                  7
#define SMN_157000D0_L2AREG_HOST_PGSIZE_MASK                   0x7f00

/// SMN_157000D0
typedef union {
  struct {
    UINT32                                       L2AREG_GST_PGSIZE:7 ; ///<
    UINT32                                      L2AREG_HOST_PGSIZE:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_157000D0_STRUCT;

// **** IOHC_x2E0 Register Definition ****
// Address
#define IOHC_x2E0_ADDRESS                                      IOHC_SPACE(0x2E0)

// Type
#define IOHC_x2E0_TYPE                                         TYPE_SMN

// **** IOHC_x2E4 Register Definition ****
// Address
#define IOHC_x2E4_ADDRESS                                      IOHC_SPACE(0x2E4)

// Type
#define IOHC_x2E4_TYPE                                         TYPE_SMN

// Address
#define SST_CLOCK_CTRL_SST0_ADDRESS                            0x17400004
#define SST_CLOCK_CTRL_SST1_ADDRESS                            0x17500004

// Type
#define TYPE_SST0                                              TYPE_SMN
#define TYPE_SST1                                              TYPE_SMN

#define SST_CLOCK_CTRL_TXCLKGATEEn_OFFSET                      0
#define SST_CLOCK_CTRL_TXCLKGATEEn_WIDTH                       1
#define SST_CLOCK_CTRL_TXCLKGATEEn_MASK                        0x1
#define SST_CLOCK_CTRL_Reserved1_OFFSET                        1
#define SST_CLOCK_CTRL_Reserved1_WIDTH                         7
#define SST_CLOCK_CTRL_Reserved1_MASK                          0xfe
#define SST_CLOCK_CTRL_PCTRL_IDLE_TIME_OFFSET                  8
#define SST_CLOCK_CTRL_PCTRL_IDLE_TIME_WIDTH                   8
#define SST_CLOCK_CTRL_PCTRL_IDLE_TIME_MASK                    0xff00
#define SST_CLOCK_CTRL_RXCLKGATEEn_OFFSET                      16
#define SST_CLOCK_CTRL_RXCLKGATEEn_WIDTH                       1
#define SST_CLOCK_CTRL_RXCLKGATEEn_MASK                        0x10000
#define SST_CLOCK_CTRL_Reserved0_OFFSET                        17
#define SST_CLOCK_CTRL_Reserved0_WIDTH                         15
#define SST_CLOCK_CTRL_Reserved0_MASK                          0xfffe0000L

/// SST_CLOCK_CTRL_STRUCT
typedef union {
  struct {
    UINT32                                             TXCLKGATEEn:1 ; ///<
    UINT32                                               Reserved1:7 ; ///<
    UINT32                                         PCTRL_IDLE_TIME:8 ; ///<
    UINT32                                             RXCLKGATEEn:1 ; ///<
    UINT32                                               Reserved0:15; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SST_CLOCK_CTRL_STRUCT;

// Register Name SION_WRAPPER_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK
// Address
#define SION_WRAPPER_404_SST0_ADDRESS                                      0x17400404
#define SION_WRAPPER_404_SST1_ADDRESS                                      0x17500404

// Type
#define SION_WRAPPER_404_SST0_TYPE                                         TYPE_SMN
#define SION_WRAPPER_404_SST1_TYPE                                         TYPE_SMN

#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK0_OFFSET 0
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK0_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK0_MASK   0x1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK1_OFFSET 1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK1_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK1_MASK   0x2
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK2_OFFSET 2
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK2_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK2_MASK   0x4
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK3_OFFSET 3
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK3_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK3_MASK   0x8
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_OFFSET 4
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4_MASK   0x10
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK5_OFFSET 5
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK5_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK5_MASK   0x20
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK6_OFFSET 6
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK6_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK6_MASK   0x40
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK7_OFFSET 7
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK7_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK7_MASK   0x80
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK8_OFFSET 8
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK8_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK8_MASK   0x100
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK9_OFFSET 9
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK9_WIDTH  1
#define SION_WRAPPER_404_CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK9_MASK   0x200
#define SION_WRAPPER_404_Reserved1_OFFSET                                  10
#define SION_WRAPPER_404_Reserved1_WIDTH                                   6
#define SION_WRAPPER_404_Reserved1_MASK                                    0xfc00
#define SION_WRAPPER_404_Reserved_25_16_OFFSET                             16
#define SION_WRAPPER_404_Reserved_25_16_WIDTH                              10
#define SION_WRAPPER_404_Reserved_25_16_MASK                               0x3ff0000
#define SION_WRAPPER_404_Reserved0_OFFSET                                  26
#define SION_WRAPPER_404_Reserved0_WIDTH                                   6
#define SION_WRAPPER_404_Reserved0_MASK                                    0xfc000000L

/// SST0_00000404
typedef union {
  struct {
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK0:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK1:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK2:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK3:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK4:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK5:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK6:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK7:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK8:1 ; ///<
    UINT32      CFG_SSTSION_GLUE_CG_LCLK_CTRL_SOFT_OVERRIDE_CLK9:1 ; ///<
    UINT32                                               Reserved1:6 ; ///<
    UINT32                                          Reserved_25_16:10; ///<
    UINT32                                               Reserved0:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SION_WRAPPER_404_STRUCT;

// NBIF Device Control Register
// Address
#define NBIF0_NTB_STRAP0_ADDRESS                              0x10134200
#define NBIF0_PSPCCP_STRAP0_ADDRESS                           0x10134400
#define NBIF0_USB_STRAP0_ADDRESS                              0x10134600

#define NBIF1_NTBCCP_STRAP0_ADDRESS                           0x10234200
#define NBIF1_SATA_STRAP0_ADDRESS                             0x10234400
#define NBIF1_HDAUDIO_STRAP0_ADDRESS                          0x10234600
#define NBIF1_XGBE0_STRAP0_ADDRESS                            0x10234800
#define NBIF1_XGBE1_STRAP0_ADDRESS                            0x10234A00
#define NBIF1_XGBE2_STRAP0_ADDRESS                            0x10234C00
#define NBIF1_XGBE3_STRAP0_ADDRESS                            0x10234E00

#define NBIF2_NTB_STRAP0_ADDRESS                              0x10334200

// Type
#define NBIF_STRAP0_TYPE                                      TYPE_SMN

#define NBIFSTRAP0_DEVICE_ID_DEV0_F0_OFFSET                   0
#define NBIFSTRAP0_DEVICE_ID_DEV0_F0_WIDTH                    16
#define NBIFSTRAP0_DEVICE_ID_DEV0_F0_MASK                     0xffff
#define NBIFSTRAP0_MAJOR_REV_ID_DEV0_F0_OFFSET                16
#define NBIFSTRAP0_MAJOR_REV_ID_DEV0_F0_WIDTH                 4
#define NBIFSTRAP0_MAJOR_REV_ID_DEV0_F0_MASK                  0xf0000
#define NBIFSTRAP0_MINOR_REV_ID_DEV0_F0_OFFSET                20
#define NBIFSTRAP0_MINOR_REV_ID_DEV0_F0_WIDTH                 4
#define NBIFSTRAP0_MINOR_REV_ID_DEV0_F0_MASK                  0xf00000
#define NBIFSTRAP0_ATI_REV_ID_DEV0_F0_OFFSET                  24
#define NBIFSTRAP0_ATI_REV_ID_DEV0_F0_WIDTH                   4
#define NBIFSTRAP0_ATI_REV_ID_DEV0_F0_MASK                    0xf000000
#define NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET                     28
#define NBIFSTRAP0_FUNC_EN_DEV0_F0_WIDTH                      1
#define NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK                       0x10000000
#define NBIFSTRAP0_LEGACY_DEVICE_TYPE_EN_DEV0_F0_OFFSET       29
#define NBIFSTRAP0_LEGACY_DEVICE_TYPE_EN_DEV0_F0_WIDTH        1
#define NBIFSTRAP0_LEGACY_DEVICE_TYPE_EN_DEV0_F0_MASK         0x20000000
#define NBIFSTRAP0_D1_SUPPORT_DEV0_F0_OFFSET                  30
#define NBIFSTRAP0_D1_SUPPORT_DEV0_F0_WIDTH                   1
#define NBIFSTRAP0_D1_SUPPORT_DEV0_F0_MASK                    0x40000000
#define NBIFSTRAP0_D2_SUPPORT_DEV0_F0_OFFSET                  31
#define NBIFSTRAP0_D2_SUPPORT_DEV0_F0_WIDTH                   1
#define NBIFSTRAP0_D2_SUPPORT_DEV0_F0_MASK                    0x80000000

/// NBIFSTRAP0
typedef union {
  struct {
    UINT32                                 STRAP_DEVICE_ID_DEV0_F0:16; ///<
    UINT32                              STRAP_MAJOR_REV_ID_DEV0_F0:4 ; ///<
    UINT32                              STRAP_MINOR_REV_ID_DEV0_F0:4 ; ///<
    UINT32                                STRAP_ATI_REV_ID_DEV0_F0:4 ; ///<
    UINT32                                   STRAP_FUNC_EN_DEV0_F0:1 ; ///<
    UINT32                     STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F0:1 ; ///<
    UINT32                                STRAP_D1_SUPPORT_DEV0_F0:1 ; ///<
    UINT32                                STRAP_D2_SUPPORT_DEV0_F0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIFSTRAP0_STRUCT;

// Address
#define PCIE_CONFIG_CNTL_PCIECORE0_ADDRESS                     0x11180044
#define PCIE_CONFIG_CNTL_PCIECORE1_ADDRESS                     0x11280044

// Type
#define PCIE_CONFIG_CNTL_TYPE                                  TYPE_SMN

#define PCIEDIR_044_DYN_CLK_LATENCY_OFFSET                     0
#define PCIEDIR_044_DYN_CLK_LATENCY_WIDTH                      4
#define PCIEDIR_044_DYN_CLK_LATENCY_MASK                       0xf
#define PCIEDIR_044_Reserved_7_4_OFFSET                        4
#define PCIEDIR_044_Reserved_7_4_WIDTH                         4
#define PCIEDIR_044_Reserved_7_4_MASK                          0xf0
#define PCIEDIR_044_CI_SWUS_MAX_PAYLOAD_SIZE_MODE_OFFSET       8
#define PCIEDIR_044_CI_SWUS_MAX_PAYLOAD_SIZE_MODE_WIDTH        1
#define PCIEDIR_044_CI_SWUS_MAX_PAYLOAD_SIZE_MODE_MASK         0x100
#define PCIEDIR_044_CI_SWUS_PRIV_MAX_PAYLOAD_SIZE_OFFSET       9
#define PCIEDIR_044_CI_SWUS_PRIV_MAX_PAYLOAD_SIZE_WIDTH        2
#define PCIEDIR_044_CI_SWUS_PRIV_MAX_PAYLOAD_SIZE_MASK         0x600
#define PCIEDIR_044_Reserved_15_11_OFFSET                      11
#define PCIEDIR_044_Reserved_15_11_WIDTH                       5
#define PCIEDIR_044_Reserved_15_11_MASK                        0xf800
#define PCIEDIR_044_CI_MAX_PAYLOAD_SIZE_MODE_OFFSET            16
#define PCIEDIR_044_CI_MAX_PAYLOAD_SIZE_MODE_WIDTH             1
#define PCIEDIR_044_CI_MAX_PAYLOAD_SIZE_MODE_MASK              0x10000
#define PCIEDIR_044_CI_PRIV_MAX_PAYLOAD_SIZE_OFFSET            17
#define PCIEDIR_044_CI_PRIV_MAX_PAYLOAD_SIZE_WIDTH             3
#define PCIEDIR_044_CI_PRIV_MAX_PAYLOAD_SIZE_MASK              0xe0000
#define PCIEDIR_044_CI_MAX_READ_REQUEST_SIZE_MODE_OFFSET       20
#define PCIEDIR_044_CI_MAX_READ_REQUEST_SIZE_MODE_WIDTH        1
#define PCIEDIR_044_CI_MAX_READ_REQUEST_SIZE_MODE_MASK         0x100000
#define PCIEDIR_044_CI_PRIV_MAX_READ_REQUEST_SIZE_OFFSET       21
#define PCIEDIR_044_CI_PRIV_MAX_READ_REQUEST_SIZE_WIDTH        3
#define PCIEDIR_044_CI_PRIV_MAX_READ_REQUEST_SIZE_MASK         0xe00000
#define PCIEDIR_044_CI_MAX_READ_SAFE_MODE_OFFSET               24
#define PCIEDIR_044_CI_MAX_READ_SAFE_MODE_WIDTH                1
#define PCIEDIR_044_CI_MAX_READ_SAFE_MODE_MASK                 0x1000000
#define PCIEDIR_044_CI_EXTENDED_TAG_EN_OVERRIDE_OFFSET         25
#define PCIEDIR_044_CI_EXTENDED_TAG_EN_OVERRIDE_WIDTH          2
#define PCIEDIR_044_CI_EXTENDED_TAG_EN_OVERRIDE_MASK           0x6000000
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_MODE_OFFSET  27
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_MODE_WIDTH   1
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_MODE_MASK    0x8000000
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV_OFFSET  28
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV_WIDTH   2
#define PCIEDIR_044_CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV_MASK    0x30000000
#define PCIEDIR_044_CI_SWUS_EXTENDED_TAG_EN_OVERRIDE_OFFSET    31
#define PCIEDIR_044_CI_SWUS_EXTENDED_TAG_EN_OVERRIDE_WIDTH     2
#define PCIEDIR_044_CI_SWUS_EXTENDED_TAG_EN_OVERRIDE_MASK      0xc0000000

/// PCIEDIR_044
typedef union {
  struct {
    UINT32                                         DYN_CLK_LATENCY:4 ; ///<
    UINT32                                            Reserved_7_4:4 ; ///<
    UINT32                           CI_SWUS_MAX_PAYLOAD_SIZE_MODE:1 ; ///< 8
    UINT32                           CI_SWUS_PRIV_MAX_PAYLOAD_SIZE:2 ; ///< 9-10
    UINT32                                          Reserved_15_11:5 ; ///< 15-11
    UINT32                                CI_MAX_PAYLOAD_SIZE_MODE:1 ; ///< 16
    UINT32                                CI_PRIV_MAX_PAYLOAD_SIZE:3 ; ///< 17-19
    UINT32                           CI_MAX_READ_REQUEST_SIZE_MODE:1 ; ///< 20
    UINT32                           CI_PRIV_MAX_READ_REQUEST_SIZE:3 ; ///< 21-23
    UINT32                                   CI_MAX_READ_SAFE_MODE:1 ; ///< 24
    UINT32                             CI_EXTENDED_TAG_EN_OVERRIDE:2 ; ///< 25-26
    UINT32                      CI_SWUS_MAX_READ_REQUEST_SIZE_MODE:1 ; ///< 27
    UINT32                      CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV:2 ; ///< 28-29
    UINT32                        CI_SWUS_EXTENDED_TAG_EN_OVERRIDE:2 ; ///< 30-31
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEDIR_044_STRUCT;

// Address
#define CPM_CONTROL_PCIECORE0_ADDRESS                          0x11180460
#define CPM_CONTROL_PCIECORE1_ADDRESS                          0x11280460

// Type
#define CPM_CONTROL_TYPE                                       TYPE_SMN

#define PCIEDIR_460_LCLK_DYN_GATE_ENABLE_OFFSET                0
#define PCIEDIR_460_LCLK_DYN_GATE_ENABLE_WIDTH                 1
#define PCIEDIR_460_LCLK_DYN_GATE_ENABLE_MASK                  0x1
#define PCIEDIR_460_TXCLK_DYN_GATE_ENABLE_OFFSET               1
#define PCIEDIR_460_TXCLK_DYN_GATE_ENABLE_WIDTH                1
#define PCIEDIR_460_TXCLK_DYN_GATE_ENABLE_MASK                 0x2
#define PCIEDIR_460_TXCLK_PERM_GATE_ENABLE_OFFSET              2
#define PCIEDIR_460_TXCLK_PERM_GATE_ENABLE_WIDTH               1
#define PCIEDIR_460_TXCLK_PERM_GATE_ENABLE_MASK                0x4
#define PCIEDIR_460_Reserved_4_3_OFFSET                        3
#define PCIEDIR_460_Reserved_4_3_WIDTH                         2
#define PCIEDIR_460_Reserved_4_3_MASK                          0x18
#define PCIEDIR_460_TXCLK_LCNT_GATE_ENABLE_OFFSET              5
#define PCIEDIR_460_TXCLK_LCNT_GATE_ENABLE_WIDTH               1
#define PCIEDIR_460_TXCLK_LCNT_GATE_ENABLE_MASK                0x20
#define PCIEDIR_460_TXCLK_REGS_GATE_ENABLE_OFFSET              6
#define PCIEDIR_460_TXCLK_REGS_GATE_ENABLE_WIDTH               1
#define PCIEDIR_460_TXCLK_REGS_GATE_ENABLE_MASK                0x40
#define PCIEDIR_460_TXCLK_PRBS_GATE_ENABLE_OFFSET              7
#define PCIEDIR_460_TXCLK_PRBS_GATE_ENABLE_WIDTH               1
#define PCIEDIR_460_TXCLK_PRBS_GATE_ENABLE_MASK                0x80
#define PCIEDIR_460_REFCLK_REGS_GATE_ENABLE_OFFSET             8
#define PCIEDIR_460_REFCLK_REGS_GATE_ENABLE_WIDTH              1
#define PCIEDIR_460_REFCLK_REGS_GATE_ENABLE_MASK               0x100
#define PCIEDIR_460_LCLK_DYN_GATE_LATENCY_OFFSET               9
#define PCIEDIR_460_LCLK_DYN_GATE_LATENCY_WIDTH                1
#define PCIEDIR_460_LCLK_DYN_GATE_LATENCY_MASK                 0x200
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_OFFSET              10
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_WIDTH               1
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_MASK                0x400
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_OFFSET             11
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_WIDTH              1
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_MASK               0x800
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_OFFSET             12
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_WIDTH              1
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_MASK               0x1000
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_OFFSET            13
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_WIDTH             1
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_MASK              0x2000
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_OFFSET                14
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_WIDTH                 1
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_MASK                  0x4000
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_OFFSET                 15
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_WIDTH                  1
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_MASK                   0x8000
#define PCIEDIR_460_Reserved_16_OFFSET                         16
#define PCIEDIR_460_Reserved_16_WIDTH                          1
#define PCIEDIR_460_Reserved_16_MASK                           0x10000
#define PCIEDIR_460_FAST_TXCLK_LATENCY_OFFSET                  17
#define PCIEDIR_460_FAST_TXCLK_LATENCY_WIDTH                   3
#define PCIEDIR_460_FAST_TXCLK_LATENCY_MASK                    0xe0000
#define PCIEDIR_460_Reserved_21_20_OFFSET                      20
#define PCIEDIR_460_Reserved_21_20_WIDTH                       2
#define PCIEDIR_460_Reserved_21_20_MASK                        0x300000
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_OFFSET                22
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_WIDTH                 1
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_MASK                  0x400000
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_OFFSET               23
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_WIDTH                1
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_MASK                 0x800000
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_OFFSET         24
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_WIDTH          1
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_MASK           0x1000000
#define PCIEDIR_460_SPARE_REGS_OFFSET                          25
#define PCIEDIR_460_SPARE_REGS_WIDTH                           7
#define PCIEDIR_460_SPARE_REGS_MASK                            0xfe000000L

/// PCIEDIR_460
typedef union {
  struct {
    UINT32                                    LCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_PERM_GATE_ENABLE:1 ; ///<
    UINT32                                            Reserved_4_3:2 ; ///<
    UINT32                                  TXCLK_LCNT_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                  TXCLK_PRBS_GATE_ENABLE:1 ; ///<
    UINT32                                 REFCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                   LCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                  TXCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_PERM_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                REFCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                    LCLK_GATE_TXCLK_FREE:1 ; ///<
    UINT32                                     RCVR_DET_CLK_ENABLE:1 ; ///<
    UINT32                                             Reserved_16:1 ; ///<
    UINT32                                      FAST_TXCLK_LATENCY:3 ; ///<
    UINT32                                          Reserved_21_20:2 ; ///<
    UINT32                                    REFCLK_XSTCLK_ENABLE:1 ; ///<
    UINT32                                   REFCLK_XSTCLK_LATENCY:1 ; ///<
    UINT32                             CLKREQb_UNGATE_TXCLK_ENABLE:1 ; ///<
    UINT32                                              SPARE_REGS:7 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEDIR_460_STRUCT;

// Address
#define PCIE_SDP_CTRL_PCIECORE0_ADDRESS                       0x1118018C
#define PCIE_SDP_CTRL_PCIECORE1_ADDRESS                       0x1128018C

// Type
#define PCIE_SDP_CTRL_TYPE                                    TYPE_SMN

#define PCIECORE_18C_SDP_UNIT_ID_OFFSET                       0
#define PCIECORE_18C_SDP_UNIT_ID_WIDTH                        4
#define PCIECORE_18C_SDP_UNIT_ID_MASK                         0xf
#define PCIECORE_18C_CI_SLV_REQR_FULL_DISCONNECT_EN_OFFSET    4
#define PCIECORE_18C_CI_SLV_REQR_FULL_DISCONNECT_EN_WIDTH     1
#define PCIECORE_18C_CI_SLV_REQR_FULL_DISCONNECT_EN_MASK      0x10
#define PCIECORE_18C_CI_SLV_REQR_PART_DISCONNECT_EN_OFFSET    5
#define PCIECORE_18C_CI_SLV_REQR_PART_DISCONNECT_EN_WIDTH     1
#define PCIECORE_18C_CI_SLV_REQR_PART_DISCONNECT_EN_MASK      0x20
#define PCIECORE_18C_CI_MSTSDP_CLKGATE_ONESIDED_ENABLE_OFFSET 6
#define PCIECORE_18C_CI_MSTSDP_CLKGATE_ONESIDED_ENABLE_WIDTH  1
#define PCIECORE_18C_CI_MSTSDP_CLKGATE_ONESIDED_ENABLE_MASK   0x40
#define PCIECORE_18C_TX_RC_TPH_PRIV_DIS_OFFSET                7
#define PCIECORE_18C_TX_RC_TPH_PRIV_DIS_WIDTH                 1
#define PCIECORE_18C_TX_RC_TPH_PRIV_DIS_MASK                  0x80
#define PCIECORE_18C_TX_SWUS_TPH_PRIV_DIS_OFFSET              8
#define PCIECORE_18C_TX_SWUS_TPH_PRIV_DIS_WIDTH               1
#define PCIECORE_18C_TX_SWUS_TPH_PRIV_DIS_MASK                0x100
#define PCIECORE_18C_CI_SLAVE_TAG_STEALING_DIS_OFFSET         9
#define PCIECORE_18C_CI_SLAVE_TAG_STEALING_DIS_WIDTH          1
#define PCIECORE_18C_CI_SLAVE_TAG_STEALING_DIS_MASK           0x200
#define PCIECORE_18C_SLAVE_PREFIX_PRELOAD_DIS_OFFSET          10
#define PCIECORE_18C_SLAVE_PREFIX_PRELOAD_DIS_WIDTH           1
#define PCIECORE_18C_SLAVE_PREFIX_PRELOAD_DIS_MASK            0x400
#define PCIECORE_18C_CI_DISABLE_LTR_DROPPING_OFFSET           11
#define PCIECORE_18C_CI_DISABLE_LTR_DROPPING_WIDTH            1
#define PCIECORE_18C_CI_DISABLE_LTR_DROPPING_MASK             0x800
#define PCIECORE_18C_RX_SWUS_SIDEBAND_CPLHDR_DIS_OFFSET       12
#define PCIECORE_18C_RX_SWUS_SIDEBAND_CPLHDR_DIS_WIDTH        1
#define PCIECORE_18C_RX_SWUS_SIDEBAND_CPLHDR_DIS_MASK         0x1000
#define PCIECORE_18C_CI_MST_MEMR_RD_NONCONT_BE_EN_OFFSET      13
#define PCIECORE_18C_CI_MST_MEMR_RD_NONCONT_BE_EN_WIDTH       1
#define PCIECORE_18C_CI_MST_MEMR_RD_NONCONT_BE_EN_MASK        0x2000
#define PCIECORE_18C_Reserved_31_14_OFFSET                    14
#define PCIECORE_18C_Reserved_31_14_WIDTH                     18
#define PCIECORE_18C_Reserved_31_14_MASK                      0xffffc000

/// PCIECORE_18C
typedef union {
  struct {
    UINT32                                             SDP_UNIT_ID:4 ; ///<
    UINT32                          CI_SLV_REQR_FULL_DISCONNECT_EN:1 ; ///<
    UINT32                          CI_SLV_REQR_PART_DISCONNECT_EN:1 ; ///<
    UINT32                       CI_MSTSDP_CLKGATE_ONESIDED_ENABLE:1 ; ///<
    UINT32                                      TX_RC_TPH_PRIV_DIS:1 ; ///<
    UINT32                                    TX_SWUS_TPH_PRIV_DIS:1 ; ///<
    UINT32                               CI_SLAVE_TAG_STEALING_DIS:1 ; ///<
    UINT32                                SLAVE_PREFIX_PRELOAD_DIS:1 ; ///<
    UINT32                                 CI_DISABLE_LTR_DROPPING:1 ; ///<
    UINT32                             RX_SWUS_SIDEBAND_CPLHDR_DIS:1 ; ///<
    UINT32                            CI_MST_MEMR_RD_NONCONT_BE_EN:1 ; ///<
    UINT32                                          Reserved_31_14:18; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIECORE_18C_STRUCT;

// Address
#define PCIE_FC_P_ADDRESS                                           0x11140180

// Type
#define PCIE_FC_P_TYPE                                              TYPE_SMN

#define PCIE_FC_P_PD_CREDITS_OFFSET                                 0
#define PCIE_FC_P_PD_CREDITS_WIDTH                                  8
#define PCIE_FC_P_PD_CREDITS_MASK                                   0xff
#define PCIE_FC_P_PH_CREDITS_OFFSET                                 8
#define PCIE_FC_P_PH_CREDITS_WIDTH                                  8
#define PCIE_FC_P_PH_CREDITS_MASK                                   0xff00
#define PCIE_FC_P_Reserved_31_16_OFFSET                             16
#define PCIE_FC_P_Reserved_31_16_WIDTH                              16
#define PCIE_FC_P_Reserved_31_16_MASK                               0xffff0000L

/// PCIEPORT0F0_00000180
typedef union {
  struct {
    UINT32                                              PD_CREDITS:8 ; ///<
    UINT32                                              PH_CREDITS:8 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_FC_P_STRUCT;

// Address
#define PCIE_FC_NP_ADDRESS                                           0x11140184

// Type
#define PCIE_FC_NP_TYPE                                              TYPE_SMN

#define PCIE_FC_NP_NPD_CREDITS_OFFSET                                0
#define PCIE_FC_NP_NPD_CREDITS_WIDTH                                 8
#define PCIE_FC_NP_NPD_CREDITS_MASK                                  0xff
#define PCIE_FC_NP_NPH_CREDITS_OFFSET                                8
#define PCIE_FC_NP_NPH_CREDITS_WIDTH                                 8
#define PCIE_FC_NP_NPH_CREDITS_MASK                                  0xff00
#define PCIE_FC_NP_Reserved_31_16_OFFSET                             16
#define PCIE_FC_NP_Reserved_31_16_WIDTH                              16
#define PCIE_FC_NP_Reserved_31_16_MASK                               0xffff0000L

/// PCIEPORT0F0_00000184
typedef union {
  struct {
    UINT32                                             NPD_CREDITS:8 ; ///<
    UINT32                                             NPH_CREDITS:8 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_FC_NP_STRUCT;

// Address
#define PCIE_FC_CPL_ADDRESS                                           0x11140188

// Type
#define PCIE_FC_CPL_TYPE                                              TYPE_SMN

#define PCIE_FC_CPL_CPLD_CREDITS_OFFSET                               0
#define PCIE_FC_CPL_CPLD_CREDITS_WIDTH                                8
#define PCIE_FC_CPL_CPLD_CREDITS_MASK                                 0xff
#define PCIE_FC_CPL_CPLH_CREDITS_OFFSET                               8
#define PCIE_FC_CPL_CPLH_CREDITS_WIDTH                                8
#define PCIE_FC_CPL_CPLH_CREDITS_MASK                                 0xff00
#define PCIE_FC_CPL_Reserved_31_16_OFFSET                             16
#define PCIE_FC_CPL_Reserved_31_16_WIDTH                              16
#define PCIE_FC_CPL_Reserved_31_16_MASK                               0xffff0000L

/// PCIEPORT0F0_00000188
typedef union {
  struct {
    UINT32                                            CPLD_CREDITS:8 ; ///<
    UINT32                                            CPLH_CREDITS:8 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_FC_CPL_STRUCT;

// Address
#define SMN_0x1110027C_ADDRESS                                            0x1110027C
#define SMN_0x1120027C_ADDRESS                                            0x1120027C

// Type
#define PCIE_LANE_EQUALIZATION_CNTL_TYPE                                  TYPE_SMN

#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_OFFSET      0
#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_WIDTH       4
#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_MASK        0xf
#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_OFFSET 4
#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_WIDTH  3
#define PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_MASK   0x70
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_7_7_OFFSET                   7
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_7_7_WIDTH                    1
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_7_7_MASK                     0x80
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_OFFSET        8
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_WIDTH         4
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_MASK          0xf00
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_OFFSET   12
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_WIDTH    3
#define PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_MASK     0x7000
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_15_15_OFFSET                 15
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_15_15_WIDTH                  1
#define PCIE_LANE_EQUALIZATION_CNTL_Reserved_15_15_MASK                   0x8000

/// PCIE_LANE_EQUALIZATION_CNTL
typedef union {
  struct {
    UINT16                               DOWNSTREAM_PORT_TX_PRESET:4 ; ///<
    UINT16                          DOWNSTREAM_PORT_RX_PRESET_HINT:3 ; ///<
    UINT16                                            Reserved_7_7:1 ; ///<
    UINT16                                 UPSTREAM_PORT_TX_PRESET:4 ; ///<
    UINT16                            UPSTREAM_PORT_RX_PRESET_HINT:3 ; ///<
    UINT16                                          Reserved_15_15:1 ; ///<
  } Field;                                                             ///<
  UINT16 Value;                                                        ///<
} PCIE_LANE_EQUALIZATION_CNTL_STRUCT;

// Address
#define SMN_0x11180190                                         0x11180190
#define SMN_0x11280190                                         0x11280190

// Type
#define NBIO_CLKREQb_MAP_CNTL_TYPE                             TYPE_SMN

#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_0_MAP_OFFSET        0
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_0_MAP_WIDTH         4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_0_MAP_MASK          0xf
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_1_MAP_OFFSET        4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_1_MAP_WIDTH         4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_1_MAP_MASK          0xf0
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_2_MAP_OFFSET        8
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_2_MAP_WIDTH         4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_2_MAP_MASK          0xf00
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_3_MAP_OFFSET        12
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_3_MAP_WIDTH         4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_3_MAP_MASK          0xf000
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_4_MAP_OFFSET        16
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_4_MAP_WIDTH         4
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_4_MAP_MASK          0xf0000
#define NBIO_CLKREQb_MAP_CNTL_Reserved_27_20_OFFSET            20
#define NBIO_CLKREQb_MAP_CNTL_Reserved_27_20_WIDTH             8
#define NBIO_CLKREQb_MAP_CNTL_Reserved_27_20_MASK              0xff00000
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_CNTL_MASK_OFFSET    28
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_CNTL_MASK_WIDTH     1
#define NBIO_CLKREQb_MAP_CNTL_PCIE_CLKREQB_CNTL_MASK_MASK      0x10000000
#define NBIO_CLKREQb_MAP_CNTL_Reserved_31_29_OFFSET            29
#define NBIO_CLKREQb_MAP_CNTL_Reserved_31_29_WIDTH             3
#define NBIO_CLKREQb_MAP_CNTL_Reserved_31_29_MASK              0xe0000000L

/// PCIECORE0_00000190
typedef union {
  struct {
    UINT32                                      PCIE_CLKREQB_0_MAP:4 ; ///<
    UINT32                                      PCIE_CLKREQB_1_MAP:4 ; ///<
    UINT32                                      PCIE_CLKREQB_2_MAP:4 ; ///<
    UINT32                                      PCIE_CLKREQB_3_MAP:4 ; ///<
    UINT32                                      PCIE_CLKREQB_4_MAP:4 ; ///<
    UINT32                                          Reserved_27_20:8 ; ///<
    UINT32                                  PCIE_CLKREQB_CNTL_MASK:1 ; ///<
    UINT32                                          Reserved_31_29:3 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIO_CLKREQb_MAP_CNTL_STRUCT;

// Address
#define NBIF0_DN_PCIE_CNTL_SMN_ADDRESS                         0x1012358c
#define NBIF1_DN_PCIE_CNTL_SMN_ADDRESS                         0x1022358c
#define NBIF2_DN_PCIE_CNTL_SMN_ADDRESS                         0x1032358c

// Type
#define DN_PCIE_CNTL_TYPE                                      TYPE_SMN

#define DN_PCIE_CNTL_HWINIT_WR_LOCK_OFFSET                     0
#define DN_PCIE_CNTL_HWINIT_WR_LOCK_WIDTH                      1
#define DN_PCIE_CNTL_HWINIT_WR_LOCK_MASK                       0x1
#define DN_PCIE_CNTL_Reserved_6_1_OFFSET                       1
#define DN_PCIE_CNTL_Reserved_6_1_WIDTH                        6
#define DN_PCIE_CNTL_Reserved_6_1_MASK                         0x7e
#define DN_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_OFFSET               7
#define DN_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_WIDTH                1
#define DN_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_MASK                 0x80
#define DN_PCIE_CNTL_Reserved_29_8_OFFSET                      8
#define DN_PCIE_CNTL_Reserved_29_8_WIDTH                       22
#define DN_PCIE_CNTL_Reserved_29_8_MASK                        0x3fffff00
#define DN_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_OFFSET               30
#define DN_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_WIDTH                1
#define DN_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_MASK                 0x40000000
#define DN_PCIE_CNTL_Reserved_31_31_OFFSET                     31
#define DN_PCIE_CNTL_Reserved_31_31_WIDTH                      1
#define DN_PCIE_CNTL_Reserved_31_31_MASK                       0x80000000L

/// NBIFRCC0_0000358C
typedef union {
  struct {
    UINT32                                          HWINIT_WR_LOCK:1 ; ///<
    UINT32                                            Reserved_6_1:6 ; ///<
    UINT32                                    UR_ERR_REPORT_DIS_DN:1 ; ///<
    UINT32                                           Reserved_29_8:22; ///<
    UINT32                                    RX_IGNORE_LTR_MSG_UR:1 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} DN_PCIE_CNTL_STRUCT;

// Address
#define SMN_0x13f00080                                         0x13F00080
#define SMN_0x15704330                                         0x15704330
#define SMN_0x0240001C                                         0x0240001C
#define SMN_0x1570401C                                         0x1570401C

// Address
#define NBIF0_MGCG_CTRL_ADDRESS                                0x1013A030
#define NBIF1_MGCG_CTRL_ADDRESS                                0x1023A030
#define NBIF2_MGCG_CTRL_ADDRESS                                0x1033A030

// Address
#define SYSHUBMM0_NGDC_MGCG_CTRL_ADDRESS                       0x01403b80
#define SYSHUBMM1_NGDC_MGCG_CTRL_ADDRESS                       0x01503b80

// Type
#define MGCG_CTRL_TYPE                                         TYPE_SMN

#define MGCG_EN_OFFSET                                         0
#define MGCG_EN_WIDTH                                          1
#define MGCG_EN_MASK                                           0x1
#define MGCG_MODE_OFFSET                                       1
#define MGCG_MODE_WIDTH                                        1
#define MGCG_MODE_MASK                                         0x2
#define MGCG_HYSTERESIS_OFFSET                                 2
#define MGCG_HYSTERESIS_WIDTH                                  8
#define MGCG_HYSTERESIS_MASK                                   0x3fc
#define MGCG_Reserved_31_10_OFFSET                             10
#define MGCG_Reserved_31_10_WIDTH                              22
#define MGCG_Reserved_31_10_MASK                               0xfffffc00L

typedef union {
  struct {
    UINT32                                                 MGCG_EN:1 ; ///<
    UINT32                                               MGCG_MODE:1 ; ///<
    UINT32                                         MGCG_HYSTERESIS:8 ; ///<
    UINT32                                          Reserved_31_10:22; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MGCG_CTRL_STRUCT;




// Register Name RCC_DEV0_EPF3_STRAP3

// Address
#define RCC_DEV0_EPF3_STRAP3_ADDRESS                                           0x1013460C

// Type
#define RCC_DEV0_EPF3_STRAP3_TYPE                                              TYPE_SMN

#define RCC_DEV0_EPF3_STRAP3_STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F3_OFFSET   0
#define RCC_DEV0_EPF3_STRAP3_STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F3_WIDTH    1
#define RCC_DEV0_EPF3_STRAP3_STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F3_MASK     0x1
#define RCC_DEV0_EPF3_STRAP3_STRAP_PWR_EN_DEV0_F3_OFFSET                       1
#define RCC_DEV0_EPF3_STRAP3_STRAP_PWR_EN_DEV0_F3_WIDTH                        1
#define RCC_DEV0_EPF3_STRAP3_STRAP_PWR_EN_DEV0_F3_MASK                         0x2
#define RCC_DEV0_EPF3_STRAP3_STRAP_SUBSYS_ID_DEV0_F3_OFFSET                    2
#define RCC_DEV0_EPF3_STRAP3_STRAP_SUBSYS_ID_DEV0_F3_WIDTH                     16
#define RCC_DEV0_EPF3_STRAP3_STRAP_SUBSYS_ID_DEV0_F3_MASK                      0x3fffc
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_EN_DEV0_F3_OFFSET                       18
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_EN_DEV0_F3_WIDTH                        1
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_EN_DEV0_F3_MASK                         0x40000
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_CLR_PENDING_EN_DEV0_F3_OFFSET           19
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_CLR_PENDING_EN_DEV0_F3_WIDTH            1
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSI_CLR_PENDING_EN_DEV0_F3_MASK             0x80000
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSIX_EN_DEV0_F3_OFFSET                      20
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSIX_EN_DEV0_F3_WIDTH                       1
#define RCC_DEV0_EPF3_STRAP3_STRAP_MSIX_EN_DEV0_F3_MASK                        0x100000
#define RCC_DEV0_EPF3_STRAP3_Reserved_23_21_OFFSET                             21
#define RCC_DEV0_EPF3_STRAP3_Reserved_23_21_WIDTH                              3
#define RCC_DEV0_EPF3_STRAP3_Reserved_23_21_MASK                               0xe00000
#define RCC_DEV0_EPF3_STRAP3_STRAP_PMC_DSI_DEV0_F3_OFFSET                      24
#define RCC_DEV0_EPF3_STRAP3_STRAP_PMC_DSI_DEV0_F3_WIDTH                       1
#define RCC_DEV0_EPF3_STRAP3_STRAP_PMC_DSI_DEV0_F3_MASK                        0x1000000
#define RCC_DEV0_EPF3_STRAP3_STRAP_VENDOR_ID_BIT_DEV0_F3_OFFSET                25
#define RCC_DEV0_EPF3_STRAP3_STRAP_VENDOR_ID_BIT_DEV0_F3_WIDTH                 1
#define RCC_DEV0_EPF3_STRAP3_STRAP_VENDOR_ID_BIT_DEV0_F3_MASK                  0x2000000
#define RCC_DEV0_EPF3_STRAP3_STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F3_OFFSET     26
#define RCC_DEV0_EPF3_STRAP3_STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F3_WIDTH      1
#define RCC_DEV0_EPF3_STRAP3_STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F3_MASK       0x4000000
#define RCC_DEV0_EPF3_STRAP3_STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F3_OFFSET    27
#define RCC_DEV0_EPF3_STRAP3_STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F3_WIDTH     1
#define RCC_DEV0_EPF3_STRAP3_STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F3_MASK      0x8000000
#define RCC_DEV0_EPF3_STRAP3_Reserved_31_28_OFFSET                             28
#define RCC_DEV0_EPF3_STRAP3_Reserved_31_28_WIDTH                              4
#define RCC_DEV0_EPF3_STRAP3_Reserved_31_28_MASK                               0xf0000000L

/// RCC_DEV0_EPF3_STRAP3
typedef union {
  struct {
    UINT32                STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F3:1 ; ///<
    UINT32                                    STRAP_PWR_EN_DEV0_F3:1 ; ///<
    UINT32                                 STRAP_SUBSYS_ID_DEV0_F3:16; ///<
    UINT32                                    STRAP_MSI_EN_DEV0_F3:1 ; ///<
    UINT32                        STRAP_MSI_CLR_PENDING_EN_DEV0_F3:1 ; ///<
    UINT32                                   STRAP_MSIX_EN_DEV0_F3:1 ; ///<
    UINT32                                          Reserved_23_21:3 ; ///<
    UINT32                                   STRAP_PMC_DSI_DEV0_F3:1 ; ///<
    UINT32                             STRAP_VENDOR_ID_BIT_DEV0_F3:1 ; ///<
    UINT32                  STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F3:1 ; ///<
    UINT32                 STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F3:1 ; ///<
    UINT32                                          Reserved_31_28:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_EPF3_STRAP3_STRUCT;



// **** DxF0x58 Register Definition ****
// Address
#define DxF0x58_ADDRESS                                         0x58

// Type
#define DxF0x58_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x58_CapID_OFFSET                                    0
#define DxF0x58_CapID_WIDTH                                     8
#define DxF0x58_CapID_MASK                                      0xff
#define DxF0x58_NextPtr_OFFSET                                  8
#define DxF0x58_NextPtr_WIDTH                                   8
#define DxF0x58_NextPtr_MASK                                    0xff00
#define DxF0x58_Version_OFFSET                                  16
#define DxF0x58_Version_WIDTH                                   4
#define DxF0x58_Version_MASK                                    0xf0000
#define DxF0x58_DeviceType_OFFSET                               20
#define DxF0x58_DeviceType_WIDTH                                4
#define DxF0x58_DeviceType_MASK                                 0xf00000
#define DxF0x58_SlotImplemented_OFFSET                          24
#define DxF0x58_SlotImplemented_WIDTH                           1
#define DxF0x58_SlotImplemented_MASK                            0x1000000
#define DxF0x58_IntMessageNum_OFFSET                            25
#define DxF0x58_IntMessageNum_WIDTH                             5
#define DxF0x58_IntMessageNum_MASK                              0x3e000000
#define DxF0x58_Reserved_31_30_OFFSET                           30
#define DxF0x58_Reserved_31_30_WIDTH                            2
#define DxF0x58_Reserved_31_30_MASK                             0xc0000000

/// DxF0x58
typedef union {
  struct {                                                              ///<
    UINT32                                                    CapID:8 ; ///<
    UINT32                                                  NextPtr:8 ; ///<
    UINT32                                                  Version:4 ; ///<
    UINT32                                               DeviceType:4 ; ///<
    UINT32                                          SlotImplemented:1 ; ///<
    UINT32                                            IntMessageNum:5 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x58_STRUCT;

// Address
#define NTB_CTRL_ADDRESS                                           0x4000200

// Type
#define NTB_CTRL_TYPE                                              TYPE_SMN

#define NTB_CTRL_CLKOffHyst_OFFSET                                 0
#define NTB_CTRL_CLKOffHyst_WIDTH                                  16
#define NTB_CTRL_CLKOffHyst_MASK                                   0xffff
#define NTB_CTRL_CLK_GATE_EN_OFFSET                                16
#define NTB_CTRL_CLK_GATE_EN_WIDTH                                 1
#define NTB_CTRL_CLK_GATE_EN_MASK                                  0x10000
#define NTB_CTRL_PMMReg_AccessPath_OFFSET                          17
#define NTB_CTRL_PMMReg_AccessPath_WIDTH                           1
#define NTB_CTRL_PMMReg_AccessPath_MASK                            0x20000
#define NTB_CTRL_SMMReg_AccessPath_OFFSET                          18
#define NTB_CTRL_SMMReg_AccessPath_WIDTH                           1
#define NTB_CTRL_SMMReg_AccessPath_MASK                            0x40000
#define NTB_CTRL_SMN_ERR_TYPE_OFFSET                               19
#define NTB_CTRL_SMN_ERR_TYPE_WIDTH                                1
#define NTB_CTRL_SMN_ERR_TYPE_MASK                                 0x80000
#define NTB_CTRL_SMM_Reg_Ctrl_OFFSET                               20
#define NTB_CTRL_SMM_Reg_Ctrl_WIDTH                                1
#define NTB_CTRL_SMM_Reg_Ctrl_MASK                                 0x100000
#define NTB_CTRL_PMM_Reg_Ctrl_OFFSET                               21
#define NTB_CTRL_PMM_Reg_Ctrl_WIDTH                                1
#define NTB_CTRL_PMM_Reg_Ctrl_MASK                                 0x200000
#define NTB_CTRL_RESERVED_OFFSET                                   22
#define NTB_CTRL_RESERVED_WIDTH                                    10
#define NTB_CTRL_RESERVED_MASK                                     0xffc00000L

/// NTB_00000200
typedef union {
  struct {
    UINT32                                              CLKOffHyst:16; ///<
    UINT32                                             CLK_GATE_EN:1 ; ///<
    UINT32                                       PMMReg_AccessPath:1 ; ///<
    UINT32                                       SMMReg_AccessPath:1 ; ///<
    UINT32                                            SMN_ERR_TYPE:1 ; ///<
    UINT32                                            SMM_Reg_Ctrl:1 ; ///<
    UINT32                                            PMM_Reg_Ctrl:1 ; ///<
    UINT32                                                RESERVED:10; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NTB_CTRL_STRUCT;

// Address
#define SMN_0x10123990                                         0x10123990
#define SMN_0x10223990                                         0x10223990
#define SMN_0x10323990                                         0x10323990

// Type
#define SMN_0x10123990_TYPE                                    TYPE_SMN

#define SMN_GMI_REQ_REALTIME_WEIGHT_OFFSET                     0
#define SMN_GMI_REQ_REALTIME_WEIGHT_WIDTH                      8
#define SMN_GMI_REQ_REALTIME_WEIGHT_MASK                       0xff
#define SMN_GMI_REQ_NORM_P_WEIGHT_OFFSET                       8
#define SMN_GMI_REQ_NORM_P_WEIGHT_WIDTH                        8
#define SMN_GMI_REQ_NORM_P_WEIGHT_MASK                         0xff00
#define SMN_GMI_REQ_NORM_NP_WEIGHT_OFFSET                      16
#define SMN_GMI_REQ_NORM_NP_WEIGHT_WIDTH                       8
#define SMN_GMI_REQ_NORM_NP_WEIGHT_MASK                        0xff0000
#define SMN_Reserved_31_24_OFFSET                              24
#define SMN_Reserved_31_24_WIDTH                               8
#define SMN_Reserved_31_24_MASK                                0xff000000L

/// NBIFRCC0_00003990
typedef union {
  struct {
    UINT32                                 GMI_REQ_REALTIME_WEIGHT:8 ; ///<
    UINT32                                   GMI_REQ_NORM_P_WEIGHT:8 ; ///<
    UINT32                                  GMI_REQ_NORM_NP_WEIGHT:8 ; ///<
    UINT32                                          Reserved_31_24:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x10123990_STRUCT;

// Register Name PCIEP_STRAP_MISC
// Address
#define PCIEP_STRAP_MISC_instPCIE0_link_ADDRESS                0x11140304
#define PCIEP_STRAP_MISC_instPCIE1_link_ADDRESS                0x11240304

// Type
#define PCIEP_STRAP_MISC_TYPE                                  TYPE_SMN

#define PCIEP_STRAP_MISC_STRAP_REVERSE_LANES_OFFSET            0
#define PCIEP_STRAP_MISC_STRAP_REVERSE_LANES_WIDTH             1
#define PCIEP_STRAP_MISC_STRAP_REVERSE_LANES_MASK              0x1
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_OFFSET            1
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_WIDTH             1
#define PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_MASK              0x2
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_OFFSET   2
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_WIDTH    1
#define PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_MASK     0x4
#define PCIEP_STRAP_MISC_STRAP_OBFF_SUPPORTED_OFFSET           3
#define PCIEP_STRAP_MISC_STRAP_OBFF_SUPPORTED_WIDTH            2
#define PCIEP_STRAP_MISC_STRAP_OBFF_SUPPORTED_MASK             0x18
#define PCIEP_STRAP_MISC_STRAP_LTR_SUPPORTED_OFFSET            5
#define PCIEP_STRAP_MISC_STRAP_LTR_SUPPORTED_WIDTH             1
#define PCIEP_STRAP_MISC_STRAP_LTR_SUPPORTED_MASK              0x20
#define PCIEP_STRAP_MISC_Reserved_31_6_OFFSET                  6
#define PCIEP_STRAP_MISC_Reserved_31_6_WIDTH                   26
#define PCIEP_STRAP_MISC_Reserved_31_6_MASK                    0xffffffc0L

/// PCIEPORT0F0_00000304
typedef union {
  struct {
    UINT32                                     STRAP_REVERSE_LANES:1 ; ///<
    UINT32                                     STRAP_E2E_PREFIX_EN:1 ; ///<
    UINT32                            STRAP_EXTENDED_FMT_SUPPORTED:1 ; ///<
    UINT32                                    STRAP_OBFF_SUPPORTED:2 ; ///<
    UINT32                                     STRAP_LTR_SUPPORTED:1 ; ///<
    UINT32                                           Reserved_31_6:26; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEP_STRAP_MISC_STRUCT;

// Register Name RAS_LEAF_CTRL

#define NBIF0_BIF_RAS_LEAF0_CTRL_ADDRESS                                    0x10139000
#define NBIF0_BIF_RAS_LEAF1_CTRL_ADDRESS                                    0x10139004
#define NBIF0_BIF_RAS_LEAF2_CTRL_ADDRESS                                    0x10139008
#define NBIF1_BIF_RAS_LEAF0_CTRL_ADDRESS                                    0x10239000
#define NBIF1_BIF_RAS_LEAF1_CTRL_ADDRESS                                    0x10239004
#define NBIF1_BIF_RAS_LEAF2_CTRL_ADDRESS                                    0x10239008
#define NBIF2_BIF_RAS_LEAF0_CTRL_ADDRESS                                    0x10339000
#define NBIF2_BIF_RAS_LEAF1_CTRL_ADDRESS                                    0x10339004
#define NBIF2_BIF_RAS_LEAF2_CTRL_ADDRESS                                    0x10339008

// Address
#define NBIF0_GDC_RAS_LEAF0_CTRL_ADDRESS                                    0x0141F800
#define NBIF0_GDC_RAS_LEAF1_CTRL_ADDRESS                                    0x0141F804
#define NBIF0_GDC_RAS_LEAF2_CTRL_ADDRESS                                    0x0141F808
#define NBIF0_GDC_RAS_LEAF3_CTRL_ADDRESS                                    0x0141F80C
#define NBIF0_GDC_RAS_LEAF4_CTRL_ADDRESS                                    0x0141F810
#define NBIF0_GDC_RAS_LEAF5_CTRL_ADDRESS                                    0x0141F814

#define NBIF1_GDC_RAS_LEAF0_CTRL_ADDRESS                                    0x0151F800
#define NBIF1_GDC_RAS_LEAF1_CTRL_ADDRESS                                    0x0151F804
#define NBIF1_GDC_RAS_LEAF2_CTRL_ADDRESS                                    0x0151F808
#define NBIF1_GDC_RAS_LEAF3_CTRL_ADDRESS                                    0x0151F80C
#define NBIF1_GDC_RAS_LEAF4_CTRL_ADDRESS                                    0x0151F810
#define NBIF1_GDC_RAS_LEAF5_CTRL_ADDRESS                                    0x0151F814

// Type
#define RAS_LEAF_CTRL_TYPE                                              TYPE_SMN

#define RAS_LEAF_CTRL_POISON_DET_EN_OFFSET                              0
#define RAS_LEAF_CTRL_POISON_DET_EN_WIDTH                               1
#define RAS_LEAF_CTRL_POISON_DET_EN_MASK                                0x1
#define RAS_LEAF_CTRL_POISON_ERREVENT_EN_OFFSET                         1
#define RAS_LEAF_CTRL_POISON_ERREVENT_EN_WIDTH                          1
#define RAS_LEAF_CTRL_POISON_ERREVENT_EN_MASK                           0x2
#define RAS_LEAF_CTRL_POISON_STALL_EN_OFFSET                            2
#define RAS_LEAF_CTRL_POISON_STALL_EN_WIDTH                             1
#define RAS_LEAF_CTRL_POISON_STALL_EN_MASK                              0x4
#define RAS_LEAF_CTRL_Reserved_3_3_OFFSET                               3
#define RAS_LEAF_CTRL_Reserved_3_3_WIDTH                                1
#define RAS_LEAF_CTRL_Reserved_3_3_MASK                                 0x8
#define RAS_LEAF_CTRL_PARITY_DET_EN_OFFSET                              4
#define RAS_LEAF_CTRL_PARITY_DET_EN_WIDTH                               1
#define RAS_LEAF_CTRL_PARITY_DET_EN_MASK                                0x10
#define RAS_LEAF_CTRL_PARITY_ERREVENT_EN_OFFSET                         5
#define RAS_LEAF_CTRL_PARITY_ERREVENT_EN_WIDTH                          1
#define RAS_LEAF_CTRL_PARITY_ERREVENT_EN_MASK                           0x20
#define RAS_LEAF_CTRL_PARITY_STALL_EN_OFFSET                            6
#define RAS_LEAF_CTRL_PARITY_STALL_EN_WIDTH                             1
#define RAS_LEAF_CTRL_PARITY_STALL_EN_MASK                              0x40
#define RAS_LEAF_CTRL_Reserved_15_7_OFFSET                              7
#define RAS_LEAF_CTRL_Reserved_15_7_WIDTH                               9
#define RAS_LEAF_CTRL_Reserved_15_7_MASK                                0xff80
#define RAS_LEAF_CTRL_ERR_EVENT_RECV_OFFSET                             16
#define RAS_LEAF_CTRL_ERR_EVENT_RECV_WIDTH                              1
#define RAS_LEAF_CTRL_ERR_EVENT_RECV_MASK                               0x10000
#define RAS_LEAF_CTRL_LINK_DIS_RECV_OFFSET                              17
#define RAS_LEAF_CTRL_LINK_DIS_RECV_WIDTH                               1
#define RAS_LEAF_CTRL_LINK_DIS_RECV_MASK                                0x20000
#define RAS_LEAF_CTRL_POISON_ERR_DET_OFFSET                             18
#define RAS_LEAF_CTRL_POISON_ERR_DET_WIDTH                              1
#define RAS_LEAF_CTRL_POISON_ERR_DET_MASK                               0x40000
#define RAS_LEAF_CTRL_PARITY_ERR_DET_OFFSET                             19
#define RAS_LEAF_CTRL_PARITY_ERR_DET_WIDTH                              1
#define RAS_LEAF_CTRL_PARITY_ERR_DET_MASK                               0x80000
#define RAS_LEAF_CTRL_ERR_EVENT_SENT_OFFSET                             20
#define RAS_LEAF_CTRL_ERR_EVENT_SENT_WIDTH                              1
#define RAS_LEAF_CTRL_ERR_EVENT_SENT_MASK                               0x100000
#define RAS_LEAF_CTRL_EGRESS_STALLED_OFFSET                             21
#define RAS_LEAF_CTRL_EGRESS_STALLED_WIDTH                              1
#define RAS_LEAF_CTRL_EGRESS_STALLED_MASK                               0x200000
#define RAS_LEAF_CTRL_Reserved_31_22_OFFSET                             22
#define RAS_LEAF_CTRL_Reserved_31_22_WIDTH                              10
#define RAS_LEAF_CTRL_Reserved_31_22_MASK                               0xffc00000L

/// NBIFGDCRAS0_00000014
typedef union {
  struct {
    UINT32                                           POISON_DET_EN:1 ; ///<
    UINT32                                      POISON_ERREVENT_EN:1 ; ///<
    UINT32                                         POISON_STALL_EN:1 ; ///<
    UINT32                                            Reserved_3_3:1 ; ///<
    UINT32                                           PARITY_DET_EN:1 ; ///<
    UINT32                                      PARITY_ERREVENT_EN:1 ; ///<
    UINT32                                         PARITY_STALL_EN:1 ; ///<
    UINT32                                           Reserved_15_7:9 ; ///<
    UINT32                                          ERR_EVENT_RECV:1 ; ///<
    UINT32                                           LINK_DIS_RECV:1 ; ///<
    UINT32                                          POISON_ERR_DET:1 ; ///<
    UINT32                                          PARITY_ERR_DET:1 ; ///<
    UINT32                                          ERR_EVENT_SENT:1 ; ///<
    UINT32                                          EGRESS_STALLED:1 ; ///<
    UINT32                                          Reserved_31_22:10; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RAS_LEAF_CTRL_STRUCT;

// Register Name RCC_DEV0_EPF#_STRAP2
// Address
#define NBIF0_RCC_DEV0_EPF0_STRAP2_ADDRESS                                     0x10134008
#define NBIF0_RCC_DEV0_EPF1_STRAP2_ADDRESS                                     0x10134208
#define NBIF0_RCC_DEV0_EPF2_STRAP2_ADDRESS                                     0x10134408
#define NBIF0_RCC_DEV0_EPF3_STRAP2_ADDRESS                                     0x10134608
#define NBIF0_RCC_DEV0_EPF4_STRAP2_ADDRESS                                     0x10134808
#define NBIF0_RCC_DEV0_EPF5_STRAP2_ADDRESS                                     0x10134A08
#define NBIF0_RCC_DEV0_EPF6_STRAP2_ADDRESS                                     0x10134C08
#define NBIF0_RCC_DEV0_EPF7_STRAP2_ADDRESS                                     0x10134E08

#define NBIF1_RCC_DEV0_EPF0_STRAP2_ADDRESS                                     0x10234008
#define NBIF1_RCC_DEV0_EPF1_STRAP2_ADDRESS                                     0x10234208
#define NBIF1_RCC_DEV0_EPF2_STRAP2_ADDRESS                                     0x10234408
#define NBIF1_RCC_DEV0_EPF3_STRAP2_ADDRESS                                     0x10234608
#define NBIF1_RCC_DEV0_EPF4_STRAP2_ADDRESS                                     0x10234808
#define NBIF1_RCC_DEV0_EPF5_STRAP2_ADDRESS                                     0x10234A08
#define NBIF1_RCC_DEV0_EPF6_STRAP2_ADDRESS                                     0x10234C08
#define NBIF1_RCC_DEV0_EPF7_STRAP2_ADDRESS                                     0x10234E08

#define NBIF2_RCC_DEV0_EPF0_STRAP2_ADDRESS                                     0x10334008
#define NBIF2_RCC_DEV0_EPF1_STRAP2_ADDRESS                                     0x10334208
#define NBIF2_RCC_DEV0_EPF2_STRAP2_ADDRESS                                     0x10334408
#define NBIF2_RCC_DEV0_EPF3_STRAP2_ADDRESS                                     0x10334608
#define NBIF2_RCC_DEV0_EPF4_STRAP2_ADDRESS                                     0x10334808
#define NBIF2_RCC_DEV0_EPF5_STRAP2_ADDRESS                                     0x10334A08
#define NBIF2_RCC_DEV0_EPF6_STRAP2_ADDRESS                                     0x10334C08
#define NBIF2_RCC_DEV0_EPF7_STRAP2_ADDRESS                                     0x10334E08

#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_EN_DEV0_F0_OFFSET                          0
#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_EN_DEV0_F0_WIDTH                           1
#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_EN_DEV0_F0_MASK                            0x1
#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_TOTAL_VFS_DEV0_F0_OFFSET                   1
#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_TOTAL_VFS_DEV0_F0_WIDTH                    5
#define RCC_DEV0_EPFx_STRAP2_STRAP_SRIOV_TOTAL_VFS_DEV0_F0_MASK                     0x3e
#define RCC_DEV0_EPFx_STRAP2_STRAP_64BAR_DIS_DEV0_F0_OFFSET                         6
#define RCC_DEV0_EPFx_STRAP2_STRAP_64BAR_DIS_DEV0_F0_WIDTH                          1
#define RCC_DEV0_EPFx_STRAP2_STRAP_64BAR_DIS_DEV0_F0_MASK                           0x40
#define RCC_DEV0_EPFx_STRAP2_STRAP_NO_SOFT_RESET_DEV0_F0_OFFSET                     7
#define RCC_DEV0_EPFx_STRAP2_STRAP_NO_SOFT_RESET_DEV0_F0_WIDTH                      1
#define RCC_DEV0_EPFx_STRAP2_STRAP_NO_SOFT_RESET_DEV0_F0_MASK                       0x80
#define RCC_DEV0_EPFx_STRAP2_STRAP_RESIZE_BAR_EN_DEV0_F0_OFFSET                     8
#define RCC_DEV0_EPFx_STRAP2_STRAP_RESIZE_BAR_EN_DEV0_F0_WIDTH                      1
#define RCC_DEV0_EPFx_STRAP2_STRAP_RESIZE_BAR_EN_DEV0_F0_MASK                       0x100
#define RCC_DEV0_EPFx_STRAP2_STRAP_MAX_PASID_WIDTH_DEV0_F0_OFFSET                   9
#define RCC_DEV0_EPFx_STRAP2_STRAP_MAX_PASID_WIDTH_DEV0_F0_WIDTH                    5
#define RCC_DEV0_EPFx_STRAP2_STRAP_MAX_PASID_WIDTH_DEV0_F0_MASK                     0x3e00
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_PERVECTOR_MASK_CAP_DEV0_F0_OFFSET            14
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_PERVECTOR_MASK_CAP_DEV0_F0_WIDTH             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_PERVECTOR_MASK_CAP_DEV0_F0_MASK              0x4000
#define RCC_DEV0_EPFx_STRAP2_STRAP_ARI_EN_DEV0_F0_OFFSET                            15
#define RCC_DEV0_EPFx_STRAP2_STRAP_ARI_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_ARI_EN_DEV0_F0_MASK                              0x8000
#define RCC_DEV0_EPFx_STRAP2_STRAP_AER_EN_DEV0_F0_OFFSET                            16
#define RCC_DEV0_EPFx_STRAP2_STRAP_AER_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_AER_EN_DEV0_F0_MASK                              0x10000
#define RCC_DEV0_EPFx_STRAP2_STRAP_ACS_EN_DEV0_F0_OFFSET                            17
#define RCC_DEV0_EPFx_STRAP2_STRAP_ACS_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_ACS_EN_DEV0_F0_MASK                              0x20000
#define RCC_DEV0_EPFx_STRAP2_STRAP_ATS_EN_DEV0_F0_OFFSET                            18
#define RCC_DEV0_EPFx_STRAP2_STRAP_ATS_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_ATS_EN_DEV0_F0_MASK                              0x40000
#define RCC_DEV0_EPFx_STRAP2_Reserved_19_19_OFFSET                                  19
#define RCC_DEV0_EPFx_STRAP2_Reserved_19_19_WIDTH                                   1
#define RCC_DEV0_EPFx_STRAP2_Reserved_19_19_MASK                                    0x80000
#define RCC_DEV0_EPFx_STRAP2_STRAP_CPL_ABORT_ERR_EN_DEV0_F0_OFFSET                  20
#define RCC_DEV0_EPFx_STRAP2_STRAP_CPL_ABORT_ERR_EN_DEV0_F0_WIDTH                   1
#define RCC_DEV0_EPFx_STRAP2_STRAP_CPL_ABORT_ERR_EN_DEV0_F0_MASK                    0x100000
#define RCC_DEV0_EPFx_STRAP2_STRAP_DPA_EN_DEV0_F0_OFFSET                            21
#define RCC_DEV0_EPFx_STRAP2_STRAP_DPA_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_DPA_EN_DEV0_F0_MASK                              0x200000
#define RCC_DEV0_EPFx_STRAP2_STRAP_DSN_EN_DEV0_F0_OFFSET                            22
#define RCC_DEV0_EPFx_STRAP2_STRAP_DSN_EN_DEV0_F0_WIDTH                             1
#define RCC_DEV0_EPFx_STRAP2_STRAP_DSN_EN_DEV0_F0_MASK                              0x400000
#define RCC_DEV0_EPFx_STRAP2_STRAP_VC_EN_DEV0_F0_OFFSET                             23
#define RCC_DEV0_EPFx_STRAP2_STRAP_VC_EN_DEV0_F0_WIDTH                              1
#define RCC_DEV0_EPFx_STRAP2_STRAP_VC_EN_DEV0_F0_MASK                               0x800000
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_MULTI_CAP_DEV0_F0_OFFSET                     24
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_MULTI_CAP_DEV0_F0_WIDTH                      3
#define RCC_DEV0_EPFx_STRAP2_STRAP_MSI_MULTI_CAP_DEV0_F0_MASK                       0x7000000
#define RCC_DEV0_EPFx_STRAP2_STRAP_PAGE_REQ_EN_DEV0_F0_OFFSET                       27
#define RCC_DEV0_EPFx_STRAP2_STRAP_PAGE_REQ_EN_DEV0_F0_WIDTH                        1
#define RCC_DEV0_EPFx_STRAP2_STRAP_PAGE_REQ_EN_DEV0_F0_MASK                         0x8000000
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EN_DEV0_F0_OFFSET                          28
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EN_DEV0_F0_WIDTH                           1
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EN_DEV0_F0_MASK                            0x10000000
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_OFFSET    29
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_WIDTH     1
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_MASK      0x20000000
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_OFFSET 30
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_WIDTH  1
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_MASK   0x40000000
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_OFFSET         31
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_WIDTH          1
#define RCC_DEV0_EPFx_STRAP2_STRAP_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_MASK           0x80000000L

/// NBIFSTRAP0_00000008
typedef union {
  struct {
    UINT32                                  STRAP_SRIOV_EN_DEV0_F0:1 ; ///<
    UINT32                           STRAP_SRIOV_TOTAL_VFS_DEV0_F0:5 ; ///<
    UINT32                                 STRAP_64BAR_DIS_DEV0_F0:1 ; ///<
    UINT32                             STRAP_NO_SOFT_RESET_DEV0_F0:1 ; ///<
    UINT32                             STRAP_RESIZE_BAR_EN_DEV0_F0:1 ; ///<
    UINT32                           STRAP_MAX_PASID_WIDTH_DEV0_F0:5 ; ///<
    UINT32                    STRAP_MSI_PERVECTOR_MASK_CAP_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_ARI_EN_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_AER_EN_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_ACS_EN_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_ATS_EN_DEV0_F0:1 ; ///<
    UINT32                                          Reserved_19_19:1 ; ///<
    UINT32                          STRAP_CPL_ABORT_ERR_EN_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_DPA_EN_DEV0_F0:1 ; ///<
    UINT32                                    STRAP_DSN_EN_DEV0_F0:1 ; ///<
    UINT32                                     STRAP_VC_EN_DEV0_F0:1 ; ///<
    UINT32                             STRAP_MSI_MULTI_CAP_DEV0_F0:3 ; ///<
    UINT32                               STRAP_PAGE_REQ_EN_DEV0_F0:1 ; ///<
    UINT32                                  STRAP_PASID_EN_DEV0_F0:1 ; ///<
    UINT32            STRAP_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0:1 ; ///<
    UINT32         STRAP_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0:1 ; ///<
    UINT32                 STRAP_PASID_PRIV_MODE_SUPPORTED_DEV0_F0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_EPFx_STRAP2_STRUCT;

// Register Name RCC_DEV0_PORT_STRAP0
// Address
#define NBIF0_RCC_DEV0_PORT_STRAP0_ADDRESS                                     0x10131000
#define NBIF1_RCC_DEV0_PORT_STRAP0_ADDRESS                                     0x10231000
#define NBIF2_RCC_DEV0_PORT_STRAP0_ADDRESS                                     0x10331000

// Type
#define RCC_DEV0_PORT_STRAP0_TYPE                                              TYPE_NBIFRCCSTRAP0

#define RCC_DEV0_PORT_STRAP0_Reserved_0_0_OFFSET                               0
#define RCC_DEV0_PORT_STRAP0_Reserved_0_0_WIDTH                                1
#define RCC_DEV0_PORT_STRAP0_Reserved_0_0_MASK                                 0x1
#define RCC_DEV0_PORT_STRAP0_STRAP_ARI_EN_DN_DEV0_OFFSET                       1
#define RCC_DEV0_PORT_STRAP0_STRAP_ARI_EN_DN_DEV0_WIDTH                        1
#define RCC_DEV0_PORT_STRAP0_STRAP_ARI_EN_DN_DEV0_MASK                         0x2
#define RCC_DEV0_PORT_STRAP0_STRAP_ACS_EN_DN_DEV0_OFFSET                       2
#define RCC_DEV0_PORT_STRAP0_STRAP_ACS_EN_DN_DEV0_WIDTH                        1
#define RCC_DEV0_PORT_STRAP0_STRAP_ACS_EN_DN_DEV0_MASK                         0x4
#define RCC_DEV0_PORT_STRAP0_STRAP_AER_EN_DN_DEV0_OFFSET                       3
#define RCC_DEV0_PORT_STRAP0_STRAP_AER_EN_DN_DEV0_WIDTH                        1
#define RCC_DEV0_PORT_STRAP0_STRAP_AER_EN_DN_DEV0_MASK                         0x8
#define RCC_DEV0_PORT_STRAP0_STRAP_CPL_ABORT_ERR_EN_DN_DEV0_OFFSET             4
#define RCC_DEV0_PORT_STRAP0_STRAP_CPL_ABORT_ERR_EN_DN_DEV0_WIDTH              1
#define RCC_DEV0_PORT_STRAP0_STRAP_CPL_ABORT_ERR_EN_DN_DEV0_MASK               0x10
#define RCC_DEV0_PORT_STRAP0_STRAP_DEVICE_ID_DN_DEV0_OFFSET                    5
#define RCC_DEV0_PORT_STRAP0_STRAP_DEVICE_ID_DN_DEV0_WIDTH                     16
#define RCC_DEV0_PORT_STRAP0_STRAP_DEVICE_ID_DN_DEV0_MASK                      0x1fffe0
#define RCC_DEV0_PORT_STRAP0_STRAP_INTERRUPT_PIN_DN_DEV0_OFFSET                21
#define RCC_DEV0_PORT_STRAP0_STRAP_INTERRUPT_PIN_DN_DEV0_WIDTH                 3
#define RCC_DEV0_PORT_STRAP0_STRAP_INTERRUPT_PIN_DN_DEV0_MASK                  0xe00000
#define RCC_DEV0_PORT_STRAP0_STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_OFFSET         24
#define RCC_DEV0_PORT_STRAP0_STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_WIDTH          1
#define RCC_DEV0_PORT_STRAP0_STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_MASK           0x1000000
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_OFFSET          25
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_WIDTH           3
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_MASK            0xe000000
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_OFFSET          28
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_WIDTH           3
#define RCC_DEV0_PORT_STRAP0_STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_MASK            0x70000000
#define RCC_DEV0_PORT_STRAP0_Reserved_31_31_OFFSET                             31
#define RCC_DEV0_PORT_STRAP0_Reserved_31_31_WIDTH                              1
#define RCC_DEV0_PORT_STRAP0_Reserved_31_31_MASK                               0x80000000L

/// NBIFRCCSTRAP0_00000000
typedef union {
  struct {
    UINT32                                            Reserved_0_0:1 ; ///<
    UINT32                                    STRAP_ARI_EN_DN_DEV0:1 ; ///<
    UINT32                                    STRAP_ACS_EN_DN_DEV0:1 ; ///<
    UINT32                                    STRAP_AER_EN_DN_DEV0:1 ; ///<
    UINT32                          STRAP_CPL_ABORT_ERR_EN_DN_DEV0:1 ; ///<
    UINT32                                 STRAP_DEVICE_ID_DN_DEV0:16; ///<
    UINT32                             STRAP_INTERRUPT_PIN_DN_DEV0:3 ; ///<
    UINT32                      STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0:1 ; ///<
    UINT32                       STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0:3 ; ///<
    UINT32                       STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0:3 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_PORT_STRAP0_STRUCT;


// Address
#define PCICFG_IOMMU_SSID_ADDRESS                                     0x13F00078

#define PCICFG_NBIF0RC_SSID_ADDRESS                                   0x10131004
#define PCICFG_NBIF0_SSID_ADDRESS                                     0x1014004C
#define PCICFG_NBIF0_NTB_SSID_ADDRESS                                 0x1014104C
#define PCICFG_NBIF0_PSPCCP_SSID_ADDRESS                              0x1014204C

#define PCICFG_NBIF1RC_SSID_ADDRESS                                   0x10231004
#define PCICFG_NBIF1_SSID_ADDRESS                                     0x1024004C
#define PCICFG_NBIF1_NTBCCP_SSID_ADDRESS                              0x1024104C
#define PCICFG_NBIF1_XGBE0_SSID_ADDRESS                               0x1024404C
#define PCICFG_NBIF1_XGBE1_SSID_ADDRESS                               0x1024504C
#define PCICFG_NBIF1_XGBE2_SSID_ADDRESS                               0x1024604C
#define PCICFG_NBIF1_XGBE3_SSID_ADDRESS                               0x1024704C

#define PCICFG_NBIF2RC_SSID_ADDRESS                                   0x10331004
#define PCICFG_NBIF2_SSID_ADDRESS                                     0x1034004C
#define PCICFG_NBIF2_NTB_SSID_ADDRESS                                 0x1034104C

#define PCICFG_NBADAPTER_SSID_ADDRESS                                 0x13B00050


#define PCICFG_SUBSYSTEM_VENDOR_ID_OFFSET                     0
#define PCICFG_SUBSYSTEM_VENDOR_ID_WIDTH                      16
#define PCICFG_SUBSYSTEM_VENDOR_ID_MASK                       0xffff
#define PCICFG_SUBSYSTEM_ID_OFFSET                            16
#define PCICFG_SUBSYSTEM_ID_WIDTH                             16
#define PCICFG_SUBSYSTEM_ID_MASK                              0xffff0000L

/// PCICFG SUBSYSTEM DEFINITION
typedef union {
  struct {
    UINT32                                     SUBSYSTEM_VENDOR_ID:16; ///<
    UINT32                                            SUBSYSTEM_ID:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCICFG_STRUCT;

// Address
#define NBIF0_RCC_DEV0_PORT_STRAP2_ADDRESS                           0x10131008
#define NBIF1_RCC_DEV0_PORT_STRAP2_ADDRESS                           0x10231008
#define NBIF2_RCC_DEV0_PORT_STRAP2_ADDRESS                           0x10331008

// Type
#define RCC_DEV0_PORT_STRAP2_TYPE                                   TYPE_SMN

#define STRAP_ECRC_CHECK_EN_DEV0_OFFSET                             4
#define STRAP_ECRC_CHECK_EN_DEV0_WIDTH                              1
#define STRAP_ECRC_CHECK_EN_DEV0_MASK                               0x10
#define STRAP_ECRC_GEN_EN_DEV0_OFFSET                               5
#define STRAP_ECRC_GEN_EN_DEV0_WIDTH                                1
#define STRAP_ECRC_GEN_EN_DEV0_MASK                                 0x20

// PCIE_DPC_STATUS
// Address
#define PCIE0_DPC_STATUS_ADDRESS                                0x11100388
#define PCIE1_DPC_STATUS_ADDRESS                                0x11200388

// Type
#define L2_TW_CONTROL_TYPE                                     TYPE_SMN

#define PCIE_DPC_STATUS_DPC_TRIGGER_STATUS_OFFSET              0
#define PCIE_DPC_STATUS_DPC_TRIGGER_STATUS_WIDTH               1
#define PCIE_DPC_STATUS_DPC_TRIGGER_STATUS_MASK                0x1
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_OFFSET              1
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_WIDTH               2
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_MASK                0x6
#define PCIE_DPC_STATUS_DPC_INTERRUPT_STATUS_OFFSET            3
#define PCIE_DPC_STATUS_DPC_INTERRUPT_STATUS_WIDTH             1
#define PCIE_DPC_STATUS_DPC_INTERRUPT_STATUS_MASK              0x8
#define PCIE_DPC_STATUS_DPC_RP_BUSY_OFFSET                     4
#define PCIE_DPC_STATUS_DPC_RP_BUSY_WIDTH                      1
#define PCIE_DPC_STATUS_DPC_RP_BUSY_MASK                       0x10
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_EXTENSION_OFFSET    5
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_EXTENSION_WIDTH     2
#define PCIE_DPC_STATUS_DPC_TRIGGER_REASON_EXTENSION_MASK      0x60
#define PCIE_DPC_STATUS_Reserved_7_7_OFFSET                    7
#define PCIE_DPC_STATUS_Reserved_7_7_WIDTH                     1
#define PCIE_DPC_STATUS_Reserved_7_7_MASK                      0x80
#define PCIE_DPC_STATUS_RP_PIO_FIRST_ERROR_POINTER_OFFSET      8
#define PCIE_DPC_STATUS_RP_PIO_FIRST_ERROR_POINTER_WIDTH       5
#define PCIE_DPC_STATUS_RP_PIO_FIRST_ERROR_POINTER_MASK        0x1F00
#define PCIE_DPC_STATUS_Reserved_13_31_OFFSET                  13
#define PCIE_DPC_STATUS_Reserved_13_31_WIDTH                   19
#define PCIE_DPC_STATUS_Reserved_13_31_MASK                    0xFFFFE000

/// PCIE_DPC_STATUS
typedef union {
  struct {
    UINT32                                      DPC_TRIGGER_STATUS:1 ; ///<
    UINT32                                      DPC_TRIGGER_REASON:2 ; ///<
    UINT32                                    DPC_INTERRUPT_STATUS:1 ; ///<
    UINT32                                             DPC_RP_BUSY:1 ; ///<
    UINT32                            DPC_TRIGGER_REASON_EXTENSION:2 ; ///<
    UINT32                                            Reserved_7_7:1 ; ///<
    UINT32                              RP_PIO_FIRST_ERROR_POINTER:5 ; ///<
    UINT32                                          Reserved_13_31:19; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_DPC_STATUS_STRUCT;

// Register Name IOHC_PCIE_CRS_Count
// Address
#define SMN_0x13B10028_ADDRESS                                   0x13b10028

// Type
#define SMN_0x13B10028_TYPE                                      TYPE_SMN

#define SMN_0x13B10028_CrsDelayCount_OFFSET                      0
#define SMN_0x13B10028_CrsDelayCount_WIDTH                       16
#define SMN_0x13B10028_CrsDelayCount_MASK                        0xffff
#define SMN_0x13B10028_CrsLimitCount_OFFSET                      16
#define SMN_0x13B10028_CrsLimitCount_WIDTH                       12
#define SMN_0x13B10028_CrsLimitCount_MASK                        0xfff0000
#define SMN_0x13B10028_Reserved_31_28_OFFSET                     28
#define SMN_0x13B10028_Reserved_31_28_WIDTH                      4
#define SMN_0x13B10028_Reserved_31_28_MASK                       0xf0000000L

/// IOHCMISC_00000028
typedef union {
  struct {
    UINT32                                           CrsDelayCount:16; ///<
    UINT32                                           CrsLimitCount:12; ///<
    UINT32                                          Reserved_31_28:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B10028_STRUCT;

// Register Name APML_CONTROL
// Address
#define SMN_0x13B20DC4_ADDRESS                                 0x13b20dc4
// Type
#define SMN_0x13B20DC4_TYPE                                    TYPE_SMN

#define SMN_0x13B20DC4_APML_NMI_En_OFFSET                      0
#define SMN_0x13B20DC4_APML_NMI_En_WIDTH                       1
#define SMN_0x13B20DC4_APML_NMI_En_MASK                        0x1
#define SMN_0x13B20DC4_APML_SyncFlood_En_OFFSET                1
#define SMN_0x13B20DC4_APML_SyncFlood_En_WIDTH                 1
#define SMN_0x13B20DC4_APML_SyncFlood_En_MASK                  0x2
#define SMN_0x13B20DC4_Reserved_7_2_OFFSET                     2
#define SMN_0x13B20DC4_Reserved_7_2_WIDTH                      6
#define SMN_0x13B20DC4_Reserved_7_2_MASK                       0xfc
#define SMN_0x13B20DC4_APML_OutputDis_OFFSET                   8
#define SMN_0x13B20DC4_APML_OutputDis_WIDTH                    1
#define SMN_0x13B20DC4_APML_OutputDis_MASK                     0x100
#define SMN_0x13B20DC4_Reserved_31_9_OFFSET                    9
#define SMN_0x13B20DC4_Reserved_31_9_WIDTH                     23
#define SMN_0x13B20DC4_Reserved_31_9_MASK                      0xfffffe00L

/// IOHCRAS_00000DC4
typedef union {
  struct {
    UINT32                                             APML_NMI_En:1 ; ///<
    UINT32                                       APML_SyncFlood_En:1 ; ///<
    UINT32                                            Reserved_7_2:6 ; ///<
    UINT32                                          APML_OutputDis:1 ; ///<
    UINT32                                           Reserved_31_9:23; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x13B20DC4_STRUCT;

#endif

