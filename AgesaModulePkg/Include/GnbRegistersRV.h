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
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#define  TYPE_IOMMUL1IOAGR          TYPE_SMN
#define  TYPE_IOMMUL1PCIE0          TYPE_SMN
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

//
//  Common Definition
//
#define Soundwire               0x8


// Address
#define SMN_0x13f00080                                       0x13F00080
#define SMN_0x15704330                                       0x15704330
#define SMN_0x0240001C                                       0x0240001C
#define SMN_0x1570401C                                       0x1570401C

// NBIF Device Control Register
// Address
#define NBIF0_DCE_AZ_STRAP0_ADDRESS                          0x10134200
#define NBIF0_PSPCCP_STRAP0_ADDRESS                          0x10134400
#define NBIF0_USB31_1_STRAP0_ADDRESS                         0x10134600
#define NBIF0_USB31_2_STRAP0_ADDRESS                         0x10134800
#define NBIF0_ACP_STRAP0_ADDRESS                             0x10134A00
#define NBIF0_HDAUDIO_STRAP0_ADDRESS                         0x10134c00
#define NBIF0_MP2_STRAP0_ADDRESS                             0x10134E00

#define NBIF1_SATA_STRAP0_ADDRESS                            0x10135000 // This is Fun0 may not work.
#define NBIF1_XGBE0_STRAP0_ADDRESS                           0x10135200
#define NBIF1_XGBE1_STRAP0_ADDRESS                           0x10135400
#define NBIF1_SATA_STRAP2_ADDRESS                            (NBIF1_SATA_STRAP0_ADDRESS + 8)


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
#ifndef D0F0xB8_ADDRESS
  // **** D0F0xB8 Register Definition ****
  // Address
  #define D0F0xB8_ADDRESS                                      0xb8
#endif
// Type
#define D0F0xB8_TYPE                                           TYPE_D0F0
// Field Data
#define D0F0xB8_NbSmuIndAddr_OFFSET                            0
#define D0F0xB8_NbSmuIndAddr_WIDTH                             32
#define D0F0xB8_NbSmuIndAddr_MASK                              0xffffffff

/// D0F0xB8
typedef union {
  struct {                                                              ///<
    UINT32                                             NbSmuIndAddr:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xB8_STRUCT;

/// RV PPR
// DBGU GROUP BASE
#define DBGU_NBIO_PORTA                                           0x700
#define DBGU_IO_PORTA                                             0x780
#define DBGU_GFX_PORTA                                            0x9F00
#define DBGU0_PORTA                                               0x600
#define DBGU1_PORTA                                               0x680

#define DBGU_NBIO_PORTB                                           0x70C
#define DBGU_IO_PORTB                                             0x78C
#define DBGU_GFX_PORTB                                            0x9F0C
#define DBGU0_PORTB                                               0x60C
#define DBGU1_PORTB                                               0x68C

#define DBGU_NBIO_PORTC                                           0x718
#define DBGU_IO_PORTC                                             0x798
#define DBGU_GFX_PORTC                                            0x9F18
#define DBGU0_PORTC                                               0x618
#define DBGU1_PORTC                                               0x698

#define DBGU_NBIO_PORTD                                           0x724
#define DBGU_IO_PORTD                                             0x7A4
#define DBGU_GFX_PORTD                                            0x9F24
#define DBGU0_PORTD                                               0x624
#define DBGU1_PORTD                                               0x6A4

// DBGU PORTA ACCESS REGISTERS
#define DBGU_PORT_INDEX_ADDRESS                                   0x00
#define DBGU_PORT_DATALO_ADDRESS                                  0x04
#define DBGU_PORT_DATAHI_ADDRESS                                  0x08

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

// SDMA0_CLK_CTRL
#define SDMA0_CLK_CTRL_ADDRESS                                 0x49EC

#define SDMA0_CLK_CTRL_ON_DELAY_OFFSET                                   0
#define SDMA0_CLK_CTRL_ON_DELAY_WIDTH                                    4
#define SDMA0_CLK_CTRL_ON_DELAY_MASK                                     0xf
#define SDMA0_CLK_CTRL_OFF_HYSTERESIS_OFFSET                             4
#define SDMA0_CLK_CTRL_OFF_HYSTERESIS_WIDTH                              8
#define SDMA0_CLK_CTRL_OFF_HYSTERESIS_MASK                               0xff0
#define SDMA0_CLK_CTRL_Reserved_23_12_OFFSET                             12
#define SDMA0_CLK_CTRL_Reserved_23_12_WIDTH                              4
#define SDMA0_CLK_CTRL_Reserved_23_12_MASK                               0xfff000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE7_OFFSET                             24
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE7_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE7_MASK                               0x1000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE6_OFFSET                             25
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE6_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE6_MASK                               0x2000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE5_OFFSET                             26
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE5_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE5_MASK                               0x4000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE4_OFFSET                             27
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE4_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE4_MASK                               0x8000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE3_OFFSET                             28
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE3_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE3_MASK                               0x10000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE2_OFFSET                             29
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE2_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE2_MASK                               0x20000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE1_OFFSET                             30
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE1_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE1_MASK                               0x40000000
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE0_OFFSET                             31
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE0_WIDTH                              1
#define SDMA0_CLK_CTRL_SOFT_OVERRIDE0_MASK                               0x80000000L

/// SDMA0_CLK_CTRL
typedef union {
  struct {
    UINT32                                                ON_DELAY:4 ; ///<
    UINT32                                          OFF_HYSTERESIS:8 ; ///<
    UINT32                                          Reserved_23_12:12; ///<
    UINT32                                          SOFT_OVERRIDE7:1 ; ///<
    UINT32                                          SOFT_OVERRIDE6:1 ; ///<
    UINT32                                          SOFT_OVERRIDE5:1 ; ///<
    UINT32                                          SOFT_OVERRIDE4:1 ; ///<
    UINT32                                          SOFT_OVERRIDE3:1 ; ///<
    UINT32                                          SOFT_OVERRIDE2:1 ; ///<
    UINT32                                          SOFT_OVERRIDE1:1 ; ///<
    UINT32                                          SOFT_OVERRIDE0:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SDMA0_CLK_CTRL_STRUCT;




// PCIE STRAP ACCESS REGISTERS
#define PCIE0_STRAP_INDEX_ADDRESS                                0x4A34C
#define PCIE0_STRAP_DATA_ADDRESS                                 0x4A350

// Address
#define THREAD_ENABLE_ADDRESS                                    0x5a818

// Type
#define THREAD_ENABLE_TYPE                                       TYPE_PWR

#define PWR_018_ThreadEn_OFFSET                                  0
#define PWR_018_ThreadEn_WIDTH                                   16
#define PWR_018_ThreadEn_MASK                                    0xffff

/// PWR_018
typedef union {
  struct {
    UINT32                                                ThreadEn:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PWR_018_STRUCT;


// Address
#define RSMU_HCID_NBIF_RV_GPU_ADDRESS                        0x4b600

// Type
#define RSMU_HCID_NBIF_RV_GPU_TYPE                          TYPE_SMN

#define RSMU_HCID_HwRev_OFFSET                                     0
#define RSMU_HCID_HwRev_Width                                      6
#define RSMU_HCID_HwRev_Mask                                    0x3f
#define RSMU_HCID_HwMinVer_OFFSET                                  6
#define RSMU_HCID_HwMinVer_Width                                   7
#define RSMU_HCID_HwMinVer_Mask                               0x1FC0
#define RSMU_HCID_HwMajVer_OFFSET                                  13
#define RSMU_HCID_HwMajVer_OFFSET_Width                            7
#define RSMU_HCID_HwMajVer_OFFSET_Mask                       0xfe000
#define RSMU_HCID_HwID_OFFSET                                     20
#define RSMU_HCID_HwID_Width                                      12
#define RSMU_HCID_HwID_Mask                               0xfff00000

/// RSMU_HCID_NBIF_RV_GPU
typedef union {
  struct {
    UINT32                                           RSMU_HCID_HwRev:6; ///<
    UINT32                                        RSMU_HCID_HwMinVer:7; ///<
    UINT32                                        RSMU_HCID_HwMajVer:7; ///<
    UINT32                                           RSMU_HCID_HwID:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} RSMU_HCID_NBIF_RV_GPU_STRUCT;

// Address
#define THREAD_CONFIGURATION_ADDRESS                          0x5a81c

// Type
#define THREAD_CONFIGURATION_TYPE                            TYPE_PWR

#define PWR_01C_CoreCount_OFFSET                                    0
#define PWR_01C_CoreCount_WIDTH                                     4
#define PWR_01C_CoreCount_MASK                                    0xf
#define PWR_01C_ComplexCount_OFFSET                                 4
#define PWR_01C_ComplexCount_WIDTH                                  4
#define PWR_01C_ComplexCount_MASK                                0xf0
#define PWR_01C_SMTMode_OFFSET                                      8
#define PWR_01C_SMTMode_WIDTH                                       1
#define PWR_01C_SMTMode_MASK                                    0x100
#define PWR_01C_SMTDisable_OFFSET                                   9
#define PWR_01C_SMTDisable_WIDTH                                    1
#define PWR_01C_SMTDisable_MASK                                 0x200

/// PWR_01C
typedef union {
  struct {
    UINT32                                               CoreCount:4 ; ///<
    UINT32                                            ComplexCount:4 ; ///<
    UINT32                                                 SMTMode:1 ; ///<
    UINT32                                              SMTDisable:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PWR_01C_STRUCT;


// Address
#define PWR_060_ADDRESS                                       0x5a860

#define SMN_RCC_DEV1_PORT_STRAP0_ADDRESS                   0x10131200
// Register Name RCC_BIF_STRAP1_

// Address
#define DEV0_PORT_STRAP0_ADDRESS                           0x1012349c

#define STRAP_Reserved0_OFFSET                                      0
#define STRAP_Reserved0_WIDTH                                       1
#define STRAP_Reserved0_MASK                                      0x1
#define STRAP_ARI_EN_DN_DEV0_OFFSET                                 1
#define STRAP_ARI_EN_DN_DEV0_WIDTH                                  1
#define STRAP_ARI_EN_DN_DEV0_MASK                                 0x2
#define STRAP_ACS_EN_DN_DEV0_OFFSET                                 2
#define STRAP_ACS_EN_DN_DEV0_WIDTH                                  1
#define STRAP_ACS_EN_DN_DEV0_MASK                                 0x4
#define STRAP_AER_EN_DN_DEV0_OFFSET                                 3
#define STRAP_AER_EN_DN_DEV0_WIDTH                                  1
#define STRAP_AER_EN_DN_DEV0_MASK                                 0x8
#define STRAP_CPL_ABORT_ERR_EN_DN_DEV0_OFFSET                       4
#define STRAP_CPL_ABORT_ERR_EN_DN_DEV0_WIDTH                        1
#define STRAP_CPL_ABORT_ERR_EN_DN_DEV0_MASK                      0x10
#define STRAP_STRAP_DEVICE_ID_DN_DEV0_OFFSET                        5
#define STRAP_STRAP_DEVICE_ID_DN_DEV0_WIDTH                        16
#define STRAP_STRAP_DEVICE_ID_DN_DEV0_MASK                   0x1FFFE0
#define STRAP_STRAP_INTERRUPT_PIN_DN_DEV0_OFFSET                   21
#define STRAP_STRAP_INTERRUPT_PIN_DN_DEV0_WIDTH                     3
#define STRAP_STRAP_INTERRUPT_PIN_DN_DEV0_MASK               0xE00000
#define STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_OFFSET                  24
#define STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_WIDTH                    1
#define STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0_MASK             0x1000000
#define STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_OFFSET                   25
#define STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_WIDTH                     3
#define STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0_MASK              0xE000000
#define STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_OFFSET                   28
#define STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_WIDTH                     3
#define STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0_MASK             0x70000000
#define STRAP_EPF0_DUMMY_EN_DEV0_OFFSET                            31
#define STRAP_EPF0_DUMMY_EN_DEV0_WIDTH                              1
#define STRAP_EPF0_DUMMY_EN_DEV0_MASK                      0x80000000

/// DEV0_PORT_STRAP0
typedef union {
  struct {
    UINT32                                              Reserved0:1 ;            ///<
    UINT32                                   STRAP_ARI_EN_DN_DEV0:1 ;            ///<
    UINT32                                   STRAP_ACS_EN_DN_DEV0:1 ;            ///<
    UINT32                                   STRAP_AER_EN_DN_DEV0:1 ;            ///<
    UINT32                         STRAP_CPL_ABORT_ERR_EN_DN_DEV0:1 ;            ///<
    UINT32                               STRAP_DEVICE_ID_DN_DEV0:16 ;            ///<
    UINT32                            STRAP_INTERRUPT_PIN_DN_DEV0:3 ;            ///<
    UINT32                     STRAP_IGNORE_E2E_PREFIX_UR_DN_DEV0:1 ;            ///<
    UINT32                      STRAP_MAX_PAYLOAD_SUPPORT_DN_DEV0:3 ;            ///<
    UINT32                      STRAP_MAX_LINK_WIDTH_SUPPORT_DEV0:3 ;            ///<
    UINT32                               STRAP_EPF0_DUMMY_EN_DEV0:1 ;            ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} DEV0_PORT_STRAP0_STRUCT;



//RPB_SDPPORT_CNTL
// Address
#define RPB_SDPPORT_CNTL_Address                              0x3440

// Type
#define RPB_SDPPORT_CNTL_Type                               TYPE_SMN


#define NBIF_DMA_SELF_ACTIVATE_OFFSET                              0
#define NBIF_DMA_SELF_ACTIVATE_Width                               1
#define NBIF_DMA_SELF_ACTIVATE_Mask                              0x1
#define NBIF_DMA_CFG_MODE_OFFSET                                   1
#define NBIF_DMA_CFG_MODE_Width                                    2
#define NBIF_DMA_CFG_MODE_Mask                                   0x6
#define NBIF_DMA_ENABLE_REISSUE_CREDIT_OFFSET                      3
#define NBIF_DMA_ENABLE_REISSUE_CREDIT_Width                       1
#define NBIF_DMA_ENABLE_REISSUE_CREDIT_Mask                      0x8
#define NBIF_DMA_ENABLE_SATURATE_COUNTER_OFFSET                    4
#define NBIF_DMA_ENABLE_SATURATE_COUNTER_Width                     1
#define NBIF_DMA_ENABLE_SATURATE_COUNTER_Mask                   0x10
#define NBIF_DMA_ENABLE_DISRUPT_FULLDIS_OFFSET                     5
#define NBIF_DMA_ENABLE_DISRUPT_FULLDIS_Width                      1
#define NBIF_DMA_ENABLE_DISRUPT_FULLDIS_Mask                    0x20
#define NBIF_DMA_HALT_THRESHOLD_OFFSET                             6
#define NBIF_DMA_HALT_THRESHOLD_Width                              4
#define NBIF_DMA_HALT_THRESHOLD_Mask                           0x3c0
#define NBIF_HST_SELF_ACTIVATE_OFFSET                             10
#define NBIF_HST_SELF_ACTIVATE_Width                               1
#define NBIF_HST_SELF_ACTIVATE_Mask                            0x400
#define NBIF_HST_CFG_MODE_OFFSET                                  11
#define NBIF_HST_CFG_MODE_Width                                    2
#define NBIF_HST_CFG_MODE_Mask                                0x1800
#define NBIF_HST_ENABLE_REISSUE_CREDIT_OFFSET                     13
#define NBIF_HST_ENABLE_REISSUE_CREDIT_Width                       1
#define NBIF_HST_ENABLE_REISSUE_CREDIT_Mask                   0x2000
#define NBIF_HST_ENABLE_SATURATE_COUNTER_OFFSET                   14
#define NBIF_HST_ENABLE_SATURATE_COUNTER_Width                     1
#define NBIF_HST_ENABLE_SATURATE_COUNTER_Mask                 0x4000
#define NBIF_HST_ENABLE_DISRUPT_FULLDIS_OFFSET                    15
#define NBIF_HST_ENABLE_DISRUPT_FULLDIS_Width                      1
#define NBIF_HST_ENABLE_DISRUPT_FULLDIS_Mask                  0x8000
#define NBIF_HST_HALT_THRESHOLD_OFFSET                            16
#define NBIF_HST_HALT_THRESHOLD_Width                              4
#define NBIF_HST_HALT_THRESHOLD_Mask                         0xf0000
#define NBIF_HST_PASSIVE_MODE_OFFSET                              20
#define NBIF_HST_PASSIVE_MODE_Width                                1
#define NBIF_HST_PASSIVE_MODE_Mask                          0x100000
#define NBIF_HST_QUICK_COMACK_OFFSET                              21
#define NBIF_HST_QUICK_COMACK_Width                                1
#define NBIF_HST_QUICK_COMACK_Mask                          0x200000
#define DF_SDPVDCI_RDRSPCKEN_OFFSET                               22
#define DF_SDPVDCI_RDRSPCKEN_Width                                 1
#define DF_SDPVDCI_RDRSPCKEN_Mask                           0x400000
#define DF_SDPVDCI_RDRSPCKENRCV_OFFSET                            23
#define DF_SDPVDCI_RDRSPCKENRCV_Width                              1
#define DF_SDPVDCI_RDRSPCKENRCV_Mask                        0x800000
#define DF_SDPVDCI_RDRSPDATACKEN_OFFSET                           24
#define DF_SDPVDCI_RDRSPDATACKEN_Width                             1
#define DF_SDPVDCI_RDRSPDATACKEN_Mask                      0x1000000
#define DF_SDPVDCI_RDRSPDATACKENRCV_OFFSET                        25
#define DF_SDPVDCI_RDRSPDATACKENRCV_Width                          1
#define DF_SDPVDCI_RDRSPDATACKENRCV_Mask                   0x2000000
#define DF_SDPVDCI_WRRSPCKEN_OFFSET                               26
#define DF_SDPVDCI_WRRSPCKEN_Width                                 1
#define DF_SDPVDCI_WRRSPCKEN_Mask                         0x40000000
#define DF_SDPVDCI_WRRSPCKENRCV_OFFSET                            27
#define DF_SDPVDCI_WRRSPCKENRCV_Width                              1
#define DF_SDPVDCI_WRRSPCKENRCV_Mask                       0x8000000
#define RPB_SDPPORT_CNTL_Reserved_28_31_OFFSET                    28
#define RPB_SDPPORT_CNTL_Reserved_28_31_Width                      4
#define RPB_SDPPORT_CNTL_Reserved_28_31_Mask              0xF0000000

//RPB_SDPPORT_CNTL
typedef union {
   struct {
    UINT32                              NBIF_DMA_SELF_ACTIVATE:1; ///<
    UINT32                              NBIF_DMA_CFG_MODE:2; ///<
    UINT32                              NBIF_DMA_ENABLE_REISSUE_CREDIT:1; ///<
    UINT32                              NBIF_DMA_ENABLE_SATURATE_COUNTER:1; ///<
    UINT32                              NBIF_DMA_ENABLE_DISRUPT_FULLDIS:1; ///<
    UINT32                              NBIF_DMA_HALT_THRESHOLD:4; ///<
    UINT32                              NBIF_HST_SELF_ACTIVATE:1; ///<
    UINT32                              NBIF_HST_CFG_MODE:2; ///<
    UINT32                              NBIF_HST_ENABLE_REISSUE_CREDIT:1; ///<
    UINT32                              NBIF_HST_ENABLE_SATURATE_COUNTER:1; ///<
    UINT32                              NBIF_HST_ENABLE_DISRUPT_FULLDIS:1; ///<
    UINT32                              NBIF_HST_HALT_THRESHOLD:4; ///<
    UINT32                              NBIF_HST_PASSIVE_MODE:1; ///<
    UINT32                              NBIF_HST_QUICK_COMACK:1; ///<
    UINT32                              DF_SDPVDCI_RDRSPCKEN:1; ///<
    UINT32                              DF_SDPVDCI_RDRSPCKENRCV:1; ///<
    UINT32                              DF_SDPVDCI_RDRSPDATACKEN:1; ///<
    UINT32                              DF_SDPVDCI_RDRSPDATACKENRCV:1; ///<
    UINT32                              DF_SDPVDCI_WRRSPCKEN:1; ///<
    UINT32                              DF_SDPVDCI_WRRSPCKENRCV:1; ///<
    UINT32                              RPB_SDPPORT_CNTL_Reserved_28_31:4; ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} SMN_RPB_SDPPORT_CNTLSTRUCT;

// **** SMUFUSEx0000059C Register Definition ****
// Address
#define SMUFUSEx0000059C_ADDRESS                            0x0005D59C

// Type
#define SMUFUSEx0000059C_TYPE                                 TYPE_SMN

// Field Data
#define OPN_NameString_18_OFFSET                                   30
#define OPN_NameString_18_Width                                     2
#define OPN_NameString_18_Mask                             0xc0000000
#define OPN_NameString_17_OFFSET                                   23
#define OPN_NameString_17_Width                                     7
#define OPN_NameString_17_Mask                             0x3f800000
#define OPN_NameString_16_OFFSET                                   16
#define OPN_NameString_16_Width                                     7
#define OPN_NameString_16_Mask                               0x7f0000
#define OPN_NameString_15_OFFSET                                    9
#define OPN_NameString_15_Width                                     7
#define OPN_NameString_15_Mask                                 0xFE00
#define OPN_NameString_14_OFFSET                                    2
#define OPN_NameString_14_Width                                     7
#define OPN_NameString_14_Mask                                  0x1fc
#define OPN_NameString_13_OFFSET                                    0
#define OPN_NameString_13_Width                                     2
#define OPN_NameString_13_Mask                                    0x3

///SMUFUSEx0000059C
typedef union {
   struct {
    UINT32                                        OPN_NameString_18:2; ///<
    UINT32                                        OPN_NameString_17:7; ///<
    UINT32                                        OPN_NameString_16:7; ///<
    UINT32                                        OPN_NameString_15:7; ///<
    UINT32                                        OPN_NameString_14:7; ///<
    UINT32                                        OPN_NameString_13:2; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMUFUSEx0000059C_STRUCT;


// **** SMUFUSEx000005A0 Register Definition ****
// Address
#define SMUFUSEx000005A0_ADDRESS                           0x0005D5A0

// Type
#define SMUFUSEx000005A0_TYPE                                TYPE_SMN

#define SMUFUSEx05A0_OPN_NameString_22_OFFSET                      26
#define SMUFUSEx05A0_OPN_NameString_22_Width                        6
#define SMUFUSEx05A0_OPN_NameString_22_Mask                0xfc000000
#define SMUFUSEx05A0_OPN_NameString_21_OFFSET                      19
#define SMUFUSEx05A0_OPN_NameString_21_Width                        7
#define SMUFUSEx05A0_OPN_NameString_21_Mask                 0x3f80000
#define SMUFUSEx05A0_OPN_NameString_20_OFFSET                      12
#define SMUFUSEx05A0_OPN_NameString_20_Width                        7
#define SMUFUSEx05A0_OPN_NameString_20_Mask                   0x7f000
#define SMUFUSEx05A0_OPN_NameString_19_OFFSET                       5
#define SMUFUSEx05A0_OPN_NameString_19_Width                        7
#define SMUFUSEx05A0_OPN_NameString_19_Mask                     0xFE0
#define SMUFUSEx05A0_OPN_NameString_18_OFFSET                       0
#define SMUFUSEx05A0_OPN_NameString_18_Width                        5
#define SMUFUSEx05A0_OPN_NameString_18_Mask                      0x1f

//SMUFUSEx000005A0
typedef union {
   struct {
    UINT32                                        OPN_NameString_22:6; ///<
    UINT32                                        OPN_NameString_21:7; ///<
    UINT32                                        OPN_NameString_20:7; ///<
    UINT32                                        OPN_NameString_19:7; ///<
    UINT32                                        OPN_NameString_18:5; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMUFUSEx000005A0_STRUCT;


// **** SMUFUSEx000005A4 Register Definition ****
// Address
#define SMUFUSEx000005A4_ADDRESS                           0x0005D5A4

// Type
#define SMUFUSEx000005A4_TYPE                                TYPE_SMN

#define SMUFUSEx05A4_OPN_NameString_27_OFFSET                      29
#define SMUFUSEx05A4_OPN_NameString_27_Width                        3
#define SMUFUSEx05A4_OPN_NameString_27_Mask                0xe0000000
#define SMUFUSEx05A4_OPN_NameString_26_OFFSET                      22
#define SMUFUSEx05A4_OPN_NameString_26_Width                        7
#define SMUFUSEx05A4_OPN_NameString_26_Mask                0x1fc00000
#define SMUFUSEx05A4_OPN_NameString_25_OFFSET                      15
#define SMUFUSEx05A4_OPN_NameString_25_Width                        7
#define SMUFUSEx05A4_OPN_NameString_25_Mask                  0x3f8000
#define SMUFUSEx05A4_OPN_NameString_24_OFFSET                       8
#define SMUFUSEx05A4_OPN_NameString_24_Width                        7
#define SMUFUSEx05A4_OPN_NameString_24_Mask                    0x7f00
#define SMUFUSEx05A4_OPN_NameString_23_OFFSET                       1
#define SMUFUSEx05A4_OPN_NameString_23_Width                        7
#define SMUFUSEx05A4_OPN_NameString_23_Mask                      0xfe
#define SMUFUSEx05A4_OPN_NameString_22_OFFSET                       0
#define SMUFUSEx05A4_OPN_NameString_22_Width                        1
#define SMUFUSEx05A4_OPN_NameString_22_Mask                       0x1

//SMUFUSEx000005A4
typedef union {
   struct {
    UINT32                                        OPN_NameString_27:3; ///<
    UINT32                                        OPN_NameString_26:7; ///<
    UINT32                                        OPN_NameString_25:7; ///<
    UINT32                                        OPN_NameString_24:7; ///<
    UINT32                                        OPN_NameString_23:7; ///<
    UINT32                                        OPN_NameString_22:1; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMUFUSEx000005A4_STRUCT;


// **** SMUFUSEx000005A8 Register Definition ****
// Address
#define SMUFUSEx000005A8_ADDRESS                           0x0005D5A8

// Type
#define SMUFUSEx000005A8_TYPE                                TYPE_SMN

#define SMUFUSEx05A8_OPN_NameString_31_OFFSET                      25
#define SMUFUSEx05A8_OPN_NameString_31_Width                        7
#define SMUFUSEx05A8_OPN_NameString_31_Mask                0xfe000000
#define SMUFUSEx05A8_OPN_NameString_30_OFFSET                      18
#define SMUFUSEx05A8_OPN_NameString_30_Width                        7
#define SMUFUSEx05A8_OPN_NameString_30_Mask                 0x1fc0000
#define SMUFUSEx05A8_OPN_NameString_29_OFFSET                      11
#define SMUFUSEx05A8_OPN_NameString_29_Width                        7
#define SMUFUSEx05A8_OPN_NameString_29_Mask                   0x3f800
#define SMUFUSEx05A8_OPN_NameString_28_OFFSET                       4
#define SMUFUSEx05A8_OPN_NameString_28_Width                        1
#define SMUFUSEx05A8_OPN_NameString_28_Mask                     0x7f0
#define SMUFUSEx05A8_OPN_NameString_27_OFFSET                       0
#define SMUFUSEx05A8_OPN_NameString_27_Width                        4
#define SMUFUSEx05A8_OPN_NameString_27_Mask                       0xf

//SMUFUSEx000005A8
typedef union {
   struct {
    UINT32                                        OPN_NameString_31:7; ///<
    UINT32                                        OPN_NameString_30:7; ///<
    UINT32                                        OPN_NameString_29:7; ///<
    UINT32                                        OPN_NameString_28:7; ///<
    UINT32                                        OPN_NameString_27:4; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMUFUSEx000005A8_STRUCT;


// **** SMUFUSEx000005C0 Register Definition ****
// Address
#define SMUFUSEx000005C0_ADDRESS                           0x0005D5C0

// Type
#define SMUFUSEx000005C0_TYPE                                TYPE_SMN

// Field Data
#define SMUFUSEx05c0_OPN_OPN_SPARE_OFFSET                          25
#define SMUFUSEx05c0_OPN_OPN_SPARE_Width                            7
#define SMUFUSEx05c0_OPN_OPN_SPARE_Mask                    0xfe000000
#define SMUFUSEx05c0_OPN_MSID_OFFSET                                1
#define SMUFUSEx05c0_OPN_MSID_Width                                24
#define SMUFUSEx05c0_OPN_MSID_Mask                         0x01fffffe
#define SMUFUSEx05c0_OPN_Utility_OFFSET                             0
#define SMUFUSEx05c0_OPN_Utility_Width                              1
#define SMUFUSEx05c0_OPN_Utility_Mask                             0x1

//SMUFUSEx000005C0
typedef union {
   struct {
    UINT32                                            OPN_OPN_SPARE:7; ///<
    UINT32                                                OPN_MSID:24; ///<
    UINT32                                              OPN_Utility:1; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                        ///<
} SMUFUSEx000005C0_STRUCT;


// Address
#define MC_VM_NB_MMIOBASE_Address                             0x6a040
// Type
#define MC_VM_NB_MMIOBASE_TYPE                               TYPE_SMN

#define MC_VM_NB_MMIOBASE_OFFSET                                    0
#define MC_VM_NB_MMIOBASE_Width                                    32
#define MC_VM_NB_MMIOBASE_Mask                             0xFFFFFFFF

//MC_VM_NB_MMIOBASE
typedef union {
   struct {
    UINT32                                     MC_VM_NB_MMIOBASE:32; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                      ///<
} SMN_MC_VM_NB_MMIOBASE_STRUCT;


// Address
#define MC_VM_NB_MMIOLIMIT_Address                             0x6a044
// Type
#define MC_VM_NB_MMIOLIMIT_TYPE                               TYPE_SMN

#define MC_VM_NB_MMIOLIMIT_OFFSET                                    0
#define MC_VM_NB_MMIOLIMIT_Width                                    32
#define MC_VM_NB_MMIOLIMIT_Mask                             0xFFFFFFFF

//MC_VM_NB_MMIOLIMIT
typedef union {
   struct {
    UINT32                                     MC_VM_NB_MMIOLIMIT:32; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                      ///<
} SMN_MC_VM_NB_MMIOLIMIT_STRUCT;



// Address
#define MC_VM_NB_PCI_CTRL_ADDRESS                              0x6a048

// Type
#define MC_VM_NB_PCI_CTRL_TYPE                                TYPE_SMN

#define MC_VM_NB_PCI_CTRL_22_0_OFFSET                                3
#define MC_VM_NB_PCI_CTRL_22_0_WIDTH                                23
#define MC_VM_NB_PCI_CTRL_22_0_MASK                           0x7fffff
#define MMIOENABLE_OFFSET                                           23
#define MMIOENABLE_Width                                             1
#define MMIOENABLE_Mask                                       0x800000
#define MC_VM_NB_PCI_CTRL_31_24_OFFSET                               3
#define MC_VM_NB_PCI_CTRL_31_24_WIDTH                                8
#define MC_VM_NB_PCI_CTRL_31_24_MASK                        0xff000000

///MC_VM_NB_PCI_CTRL
typedef union {
   struct {
    UINT32                                  MC_VM_NB_PCI_CTRL_22_0:23; ///<
    UINT32                                               MMIOENABLE:1; ///<
    UINT32                                  MC_VM_NB_PCI_CTRL_31_24:8; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_MC_VM_NB_PCI_CTRL_STRUCT;


// Address
#define MC_VM_NB_PCI_ARB_ADDRESS                               0x6a04c

// Type
#define MC_VM_NB_PCI_ARB_TYPE                                 TYPE_SMN


#define MC_VM_NB_PCI_ARB_Reserved_2_0_OFFSET                         0
#define MC_VM_NB_PCI_ARB_Reserved_2_0_Width                          3
#define MC_VM_NB_PCI_ARB_Reserved_2_0_Mask                         0x7
#define VGA_HOLE_OFFSET                                              3
#define VGA_HOLE_Width                                               1
#define VGA_HOLE_Mask                                              0x8
#define MC_VM_NB_PCI_ARB_Reserved_31_4_OFFSET                        4
#define MC_VM_NB_PCI_ARB_Reserved_31_2_Width                        28
#define MC_VM_NB_PCI_ARB_Reserved_31_2_Mask                 0xFFFFFFF0

/// MC_VM_NB_PCI_ARB
typedef union {
   struct {
    UINT32                     MC_VM_NB_PCI_ARB_Reserved_2_0:3; ///<
    UINT32                                          VGA_HOLE:1; ///<
    UINT32                  MC_VM_NB_PCI_ARB_Reserved_31_2 :28; ///<
  } Field;                                                      ///<
  UINT32 Value;                                                 ///<
} SMN_MC_VM_NB_PCI_ARB_STRUCT;





//MC_VM_APT_CNTL
#define MC_VM_APT_CNTL_Address                               0x6a07c
// Type
#define MC_VM_APT_CNTL_TYPE                                 TYPE_SMN

#define FORCE_MTYPE_UC_OFFSET                                      0
#define FORCE_MTYPE_UC_Width                                       1
#define FORCE_MTYPE_UC_Mask                                      0x1
#define DIRECT_SYSTEM_EN_OFFSET                                    1
#define DIRECT_SYSTEM_EN_Width                                     1
#define DIRECT_SYSTEM_EN_Mask                                    0x2
#define MC_VM_APT_CNTL_Reserved_31_2_OFFSET                        2
#define MC_VM_APT_CNTL_Reserved_31_2_Width                        30
#define MC_VM_APT_CNTL_Reserved_31_2_Mask                 0xFFFFFFFC

//MC_VM_APT_CNTL
typedef union {
   struct {
    UINT32                                          FORCE_MTYPE_UC:1; ///<
    UINT32                                        DIRECT_SYSTEM_EN:1; ///<
    UINT32                           MC_VM_APT_CNTL_Reserved_31_2:30; ///<
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} SMN_MC_VM_APT_CNTL_STRUCT;


// Address
#define MC_VM_NB_TOP_OF_DRAM_SLOT1_Address                   0x6a050

// Type
#define MC_VM_NB_TOP_OF_DRAM_SLOT1_TYPE                     TYPE_SMN

#define TOP_OF_DRAM_SLOT1_Reserved_23_0_OFFSET                     0
#define TOP_OF_DRAM_SLOT1_Reserved_23_0_Width                     23
#define TOP_OF_DRAM_SLOT1_Reserved_23_0_Mask                0x7FFFFF

#define TOP_OF_DRAM_OFFSET                                        23
#define TOP_OF_DRAM_Width                                          9
#define TOP_OF_DRAM_Mask                                  0xff800000

//MC_VM_NB_TOP_OF_DRAM_SLOT1
typedef union {
   struct {
    UINT32                                         Reserved_23_0:23; ///<
    UINT32                                            TOP_OF_DRAM:9; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                      ///<
} SMN_MC_VM_NB_TOP_OF_DRAM_SLOT1_STRUCT;



// Address
#define MC_VM_NB_LOWER_Address                               0x6a054
// Type
#define MC_VM_NB_LOWER_TYPE                                 TYPE_SMN


#define MC_VM_NB_LOWER_ENABLE_OFFSET                               0
#define MC_VM_NB_LOWER_ENABLE_Width                                1
#define MC_VM_NB_LOWER_ENABLE_Mask                               0x1
#define MC_VM_NB_LOWER_TOM2_Reserved_1_22_OFFSET                   1
#define MC_VM_NB_LOWER_TOM2_Reserved_1_22_Width                   22
#define MC_VM_NB_LOWER_TOM2_Reserved_1_22_Mask              0x7FFFFE
#define MC_VM_NB_LOWER_TOM2_OFFSET                                23
#define MC_VM_NB_LOWER_TOM2_Width                                  9
#define MC_VM_NB_LOWER_TOM2_Mask                          0xff800000

//MC_VM_NB_LOWER
typedef union {
   struct {
    UINT32                                                ENABLE:1; ///<
    UINT32                    MC_VM_NB_LOWER_TOM2_Reserved_1_22:22; ///<
    UINT32                                            LOWER_TOM2:9; ///<
  } Field;                                                          ///<
  UINT32 Value;                                                     ///<
} SMN_MC_VM_NB_LOWER_STRUCT;


// Address
#define MC_VM_NB_UPPER_TOP_OF_DRAM2_Address                 0x6a058
// Type
#define MC_VM_NB_UPPER_TOP_OF_DRAM2_TYPE                   TYPE_SMN

#define MC_VM_NB_UPPER_TOM2_OFFSET                                0
#define MC_VM_NB_UPPER_TOM2_Width                                12
#define MC_VM_NB_UPPER_TOM2_Mask                              0xFFF
#define MC_VM_NB_UPPER_TOM2_Reserved_12_31_OFFSET                12
#define MC_VM_NB_UPPER_TOM2_Reserved_12_31_Width                 20
#define MC_VM_NB_UPPER_TOM2_Reserved_12_31_Mask          0xFFFFF000

//MC_VM_NB_UPPER_TOP_OF_DRAM2
typedef union {
   struct {
    UINT32                                  MC_VM_NB_UPPER_TOM2:12; ///<
    UINT32                   MC_VM_NB_UPPER_TOM2_Reserved_12_31:20; ///<
  } Field;                                                          ///<
  UINT32 Value;                                                     ///<
} SMN_MC_VM_NB_UPPER_TOP_OF_DRAM2_STRUCT;

// Address
#define AUDIO_PORT_CONNECTIVITY_ADDRESS                       0xe370

// Type
#define AUDIO_PORT_CONNECTIVITY_TYPE                        TYPE_SMN

#define REG_PORT_CONNECTIVITY_OFFSET                     0
#define REG_PORT_CONNECTIVITY_Width                      3
#define REG_PORT_CONNECTIVITY_Mask                       0x7
#define AUDIO_PORT_Reserved_3_OFFSET                     3
#define AUDIO_PORT_Reserved_3_Width                      1
#define AUDIO_PORT_Reserved_3_Mask                       0x8
#define REG_PORT_CONNECTIVITY_OVERRIDE_ENABLE_OFFSET     4
#define REG_PORT_CONNECTIVITY_OVERRIDE_ENABLE_Width      1
#define REG_PORT_CONNECTIVITY_OVERRIDE_ENABLE_Mask       0x10
#define AUDIO_PORT_Reserved_5_31_OFFSET                  5
#define AUDIO_PORT_Reserved_5_31_Width                   27
#define AUDIO_PORT_Reserved_5_31_Mask                    0xFFFFFFE7

/// AUDIO_PORT_CONNECTIVITY
typedef union {
   struct {
    UINT32                                        REG_PORT_CONNECTIVITY:3; ///<
    UINT32                                                   Reserved_3:1; ///<
    UINT32                        REG_PORT_CONNECTIVITY_OVERRIDE_ENABLE:1; ///<
    UINT32                                                Reserved_5_31:27; ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} AUDIO_PORT_CONNECTIVITY_STRUCT;


// Address
#define LVTMA_PWRSEQ_CNTL_ADDRESS                           0x1750c
// Type
#define LVTMA_PWRSEQ_CNTL_TYPE                             TYPE_SMN


#define LVTMA_PWRSEQ_EN_OFFSET                                    0
#define LVTMA_PWRSEQ_EN_Width                                     1
#define LVTMA_PWRSEQ_EN_Mask                                    0x1
#define LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN_OFFSET       1
#define LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN__Width       1
#define LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN__Mask      0x2
#define LVTMA_PWRSEQ_TARGET_STATE_OFFSET                          4
#define LVTMA_PWRSEQ_TARGET_STATE_Width                           1
#define LVTMA_PWRSEQ_TARGET_STATE_Mask                         0x10
#define LVTMA_SYNCEN_OFFSET                                       8
#define LVTMA_SYNCEN_Width                                        1
#define LVTMA_SYNCEN_Mask                                     0x100
#define LVTMA_SYNCEN_OVRD_OFFSET                                  9
#define LVTMA_SYNCEN_OVRD_Width                                   1
#define LVTMA_SYNCEN_OVRD_Mask                                0x200
#define LVTMA_SYNCEN_POL_OFFSET                                  10
#define LVTMA_SYNCEN_POL_Width                                    1
#define LVTMA_SYNCEN_POL_Mask                                 0x400
#define LVTMA_DIGON_OFFSET                                       16
#define LVTMA_DIGON_Width                                         1
#define LVTMA_DIGON_Mask                                    0x10000
#define LVTMA_DIGON_OVRD_OFFSET                                  17
#define LVTMA_DIGON_OVRD_Width                                    1
#define LVTMA_DIGON_OVRD_Mask                               0x20000
#define LVTMA_DIGON_POL_OFFSET                                   18
#define LVTMA_DIGON_POL_Width                                     1
#define LVTMA_DIGON_POL_Mask                                0x40000
#define LVTMA_BLON_OFFSET                                        24
#define LVTMA_BLON_Width                                          1
#define LVTMA_BLON_Mask                                   0x1000000
#define LVTMA_BLON_OVRD_OFFSET                                   25
#define LVTMA_BLON_OVRD_Width                                     1
#define LVTMA_BLON_OVRD_Mask                              0x2000000
#define LVTMA_BLON_POL_OFFSET                                    26
#define LVTMA_BLON_POL_Width                                      1
#define LVTMA_BLON_POL_Mask                               0x4000000


typedef union {
   struct {
    UINT32                                        LVTMA_PWRSEQ_EN:1; ///<
    UINT32           LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN:1; ///<
    UINT32                              LVTMA_PWRSEQ_TARGET_STATE:1; ///<
    UINT32                                           LVTMA_SYNCEN:1; ///<
    UINT32                                      LVTMA_SYNCEN_OVRD:1; ///<
    UINT32                                       LVTMA_SYNCEN_POL:1; ///<
    UINT32                                            LVTMA_DIGON:1; ///<
    UINT32                                       LVTMA_DIGON_OVRD:1; ///<
    UINT32                                        LVTMA_DIGON_POL:1; ///<
    UINT32                                             LVTMA_BLON:1; ///<
    UINT32                                        LVTMA_BLON_OVRD:1; ///<
    UINT32                                         LVTMA_BLON_POL:1; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                      ///<
} LVTMA_PWRSEQ_CNTL_STRUCT;


// Address
#define RCC_BIF_STRAP1_ADDRESS                                   0x10123484

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
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_OFFSET                   22
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_WIDTH                     1
#define RCC_BIF_STRAP1_STRAP_BIF_PSN_UR_RPT_EN_MASK               0x400000
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_OFFSET          23
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_WIDTH            1
#define RCC_BIF_STRAP1_STRAP_BIF_XSTCLK_SWITCH_OVERRIDE_MASK      0x800000

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
    UINT32                                                 Reserved0   :3 ; ///<
    UINT32                                      STRAP_BIF_PSN_UR_RPT_EN:1 ; ///<
    UINT32                             STRAP_BIF_XSTCLK_SWITCH_OVERRIDE:1 ; ///<
    UINT32                                                    Reserved1:8 ; ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_BIF_STRAP1_STRUCT;

// Register Name RCC_DEV0_PORT_STRAP2_

// Address
#define RCC_DEV0_PORT_STRAP2_ADDRESS                            0x101234a4

// Type
#define RCC_DEV0_PORT_STRAP2_TYPE                                 TYPE_SMN


#define STRAP_DE_EMPHASIS_SEL_DN_DEV0_OFFSET                             0
#define STRAP_DE_EMPHASIS_SEL_DN_DEV0_WIDTH                              1
#define STRAP_DE_EMPHASIS_SEL_DN_DEV0_MASK                             0x1
#define STRAP_DSN_EN_DN_DEV0_OFFSET                                      1
#define STRAP_DSN_EN_DN_DEV0_WIDTH                                       1
#define STRAP_DSN_EN_DN_DEV0_MASK                                      0x2
#define STRAP_E2E_PREFIX_EN_DEV0_OFFSET                                  2
#define STRAP_E2E_PREFIX_EN_DEV0_WIDTH                                   1
#define STRAP_E2E_PREFIX_EN_DEV0_MASK                                  0x4
#define STRAP_ECN1P1_EN_DEV0_OFFSET                                      3
#define STRAP_ECN1P1_EN_DEV0_WIDTH                                       1
#define STRAP_ECN1P1_EN_DEV0_MASK                                      0x8
#define STRAP_ECRC_CHECK_EN_DEV0_OFFSET                                  4
#define STRAP_ECRC_CHECK_EN_DEV0_WIDTH                                   1
#define STRAP_ECRC_CHECK_EN_DEV0_MASK                                 0x10
#define STRAP_ECRC_GEN_EN_DEV0_OFFSET                                    5
#define STRAP_ECRC_GEN_EN_DEV0_WIDTH                                     1
#define STRAP_ECRC_GEN_EN_DEV0_MASK                                   0x20
#define STRAP_ERR_REPORTING_DIS_DEV0_OFFSET                              6
#define STRAP_ERR_REPORTING_DIS_DEV0_WIDTH                               1
#define STRAP_ERR_REPORTING_DIS_DEV0_MASK                             0x40
#define STRAP_EXTENDED_FMT_SUPPORTED_DEV0_OFFSET                         7
#define STRAP_EXTENDED_FMT_SUPPORTED_DEV0_WIDTH                          1
#define STRAP_EXTENDED_FMT_SUPPORTED_DEV0_MASK                        0x80
#define STRAP_EXTENDED_TAG_ECN_EN_DEV0_OFFSET                            8
#define STRAP_EXTENDED_TAG_ECN_EN_DEV0_WIDTH                             1
#define STRAP_EXTENDED_TAG_ECN_EN_DEV0_MASK                          0x100
#define STRAP_EXT_VC_COUNT_DN_DEV0_OFFSET                                9
#define STRAP_EXT_VC_COUNT_DN_DEV0_WIDT                                  3
#define STRAP_EXT_VC_COUNT_DN_DEV0_MASK                              0xE00
#define STRAP_FIRST_RCVD_ERR_LOG_DN_DEV0_OFFSET                         12
#define STRAP_FIRST_RCVD_ERR_LOG_DN_DEV0_WIDTH                           1
#define STRAP_FIRST_RCVD_ERR_LOG_DN_DEV0_MASK                       0x1000
#define STRAP_POISONED_ADVISORY_NONFATAL_DN_DEV0_OFFSET                 13
#define STRAP_POISONED_ADVISORY_NONFATAL_DN_DEV0_WIDTH                   1
#define STRAP_POISONED_ADVISORY_NONFATAL_DN_DEV0_MASK               0x2000
#define STRAP_GEN2_COMPLIANCE_DEV0_OFFSET                               14
#define STRAP_GEN2_COMPLIANCE_DEV0_WIDTH                                 1
#define STRAP_GEN2_COMPLIANCE_DEV0_MASK                             0x4000
#define STRAP_GEN2_EN_DEV0_OFFSET                                       15
#define STRAP_GEN2_EN_DEV0_WIDTH                                         1
#define STRAP_GEN2_EN_DEV0_MASK                                     0x8000
#define STRAP_GEN3_COMPLIANCE_DEV0_OFFSET                               16
#define STRAP_GEN3_COMPLIANCE_DEV0_WIDTH                                 1
#define STRAP_GEN3_COMPLIANCE_DEV0_MASK                            0x10000
#define STRAP_TARGET_LINK_SPEED_DEV0_OFFSET                             17
#define STRAP_TARGET_LINK_SPEED_DEV0_WIDTH                               2
#define STRAP_TARGET_LINK_SPEED_DEV0_MASK                          0x60000
#define STRAP_INTERNAL_ERR_EN_DEV0_OFFSET                               19
#define STRAP_INTERNAL_ERR_EN_DEV0_WIDTH                                 1
#define STRAP_INTERNAL_ERR_EN_DEV0_MASK                            0x80000
#define STRAP_L0S_ACCEPTABLE_LATENCY_DEV0_OFFSET                        20
#define STRAP_L0S_ACCEPTABLE_LATENCY_DEV0_WIDTH                          3
#define STRAP_L0S_ACCEPTABLE_LATENCY_DEV0_MASK                    0x700000
#define STRAP_L0S_EXIT_LATENCY_DEV0_OFFSET                              23
#define STRAP_L0S_EXIT_LATENCY_DEV0_WIDTH                                3
#define STRAP_L0S_EXIT_LATENCY_DEV0_MASK                         0x3800000
#define STRAP_L1_ACCEPTABLE_LATENCY_DEV0_OFFSET                         26
#define STRAP_L1_ACCEPTABLE_LATENCY_DEV0_WIDTH                           3
#define STRAP_L1_ACCEPTABLE_LATENCY_DEV0_MASK                   0x1C000000
#define STRAP_L1_EXIT_LATENCY_DEV0_OFFSET                               29
#define STRAP_L1_EXIT_LATENCY_DEV0_WIDTH                                 3
#define STRAP_L1_EXIT_LATENCY_DEV0_MASK                         0xE0000000

typedef union {
  struct {
    UINT32                                     DE_EMPHASIS_SEL_DN_DEV0:1 ;           ///<
    UINT32                                              DSN_EN_DN_DEV0:1 ;           ///<
    UINT32                                          E2E_PREFIX_EN_DEV0:1 ;           ///<
    UINT32                                              ECN1P1_EN_DEV0:1 ;           ///<
    UINT32                                          ECRC_CHECK_EN_DEV0:1 ;           ///<
    UINT32                                            ECRC_GEN_EN_DEV0:1 ;           ///<
    UINT32                                      ERR_REPORTING_DIS_DEV0:1 ;           ///<
    UINT32                                 EXTENDED_FMT_SUPPORTED_DEV0:1 ;           ///<
    UINT32                                    EXTENDED_TAG_ECN_EN_DEV0:1 ;           ///<
    UINT32                                        EXT_VC_COUNT_DN_DEV0:3 ;           ///<
    UINT32                                  FIRST_RCVD_ERR_LOG_DN_DEV0:1 ;           ///<
    UINT32                          POISONED_ADVISORY_NONFATAL_DN_DEV0:1 ;           ///<
    UINT32                                        GEN2_COMPLIANCE_DEV0:1 ;           ///<
    UINT32                                                GEN2_EN_DEV0:1 ;           ///<
    UINT32                                        GEN3_COMPLIANCE_DEV0:1 ;           ///<
    UINT32                                      TARGET_LINK_SPEED_DEV0:2 ;           ///<
    UINT32                                        INTERNAL_ERR_EN_DEV0:1 ;           ///<
    UINT32                                 L0S_ACCEPTABLE_LATENCY_DEV0:3 ;           ///<
    UINT32                                       L0S_EXIT_LATENCY_DEV0:3 ;           ///<
    UINT32                                  L1_ACCEPTABLE_LATENCY_DEV0:3 ;           ///<
    UINT32                                        L1_EXIT_LATENCY_DEV0:3 ;           ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_DEV0_PORT_STRAP2_STRUCT;

// Address
#define RCC_DEV0_EPF0_STRAP0_ADDRESS                           0x101234BC

#define STRAP_DEVICE_ID_DEV0_F0_OFFSET                                  0
#define STRAP_DEVICE_ID_DEV0_F0_WIDTH                                  16
#define STRAP_DEVICE_ID_DEV0_F0_MASK                               0xFFFF
#define STRAP_MAJOR_REV_ID_DEV0_F0_OFFSET                              16
#define STRAP_MAJOR_REV_ID_DEV0_F0_WIDTH                                4
#define STRAP_MAJOR_REV_ID_DEV0_F0_MASK                           0xF0000
#define STRAP_MINOR_REV_ID_DEV0_F0_OFFSET                              20
#define STRAP_MINOR_REV_ID_DEV0_F0_WIDTH                                4
#define STRAP_MINOR_REV_ID_DEV0_F0_MASK                          0xF00000
#define STRAP_ATI_REV_ID_DEV0_F0_OFFSET                                24
#define STRAP_ATI_REV_ID_DEV0_F0_WIDTH                                  4
#define STRAP_ATI_REV_ID_DEV0_F0_MASK                           0xF000000
#define STRAP_FUNC_EN_DEV0_F0_OFFSET                                   28
#define STRAP_FUNC_EN_DEV0_F0_WIDTH                                     1
#define STRAP_FUNC_EN_DEV0_F0_MASK                             0x10000000
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F0_OFFSET                     29
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F0_WIDTH                       1
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F0_MASK               0x20000000
#define STRAP_D1_SUPPORT_DEV0_F0_OFFSET                                30
#define STRAP_D1_SUPPORT_DEV0_F0_WIDTH                                  1
#define STRAP_D1_SUPPORT_DEV0_F0_MASK                          0x40000000
#define STRAP_D2_SUPPORT_DEV0_F0_OFFSET                                31
#define STRAP_D2_SUPPORT_DEV0_F0_WIDTH                                  1
#define STRAP_D2_SUPPORT_DEV0_F0_MASK                          0x80000000

/// RCC_DEV0_EPF0_STRAP0
typedef union {
  struct {
    UINT32                                   STRAP_DEVICE_ID_DEV0_F0:16 ;            ///<
    UINT32                                 STRAP_MAJOR_REV_ID_DEV0_F0:4 ;            ///<
    UINT32                                 STRAP_MINOR_REV_ID_DEV0_F0:4 ;            ///<
    UINT32                                   STRAP_ATI_REV_ID_DEV0_F0:4 ;            ///<
    UINT32                                      STRAP_FUNC_EN_DEV0_F0:1 ;            ///<
    UINT32                        STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F0:1 ;            ///<
    UINT32                                   STRAP_D1_SUPPORT_DEV0_F0:1 ;            ///<
    UINT32                                   STRAP_D2_SUPPORT_DEV0_F0:1 ;            ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_DEV0_EPF0_STRAP0_STRUCT;


// Address
#define RCC_DEV0_EPF1_STRAP0_ADDRESS                           0x101234e0

#define STRAP_DEVICE_ID_DEV0_F1_OFFSET                                  0
#define STRAP_DEVICE_ID_DEV0_F1_WIDTH                                  16
#define STRAP_DEVICE_ID_DEV0_F1_MASK                               0xFFFF
#define STRAP_MAJOR_REV_ID_DEV0_F1_OFFSET                              16
#define STRAP_MAJOR_REV_ID_DEV0_F1_WIDTH                                4
#define STRAP_MAJOR_REV_ID_DEV0_F1_MASK                           0xF0000
#define STRAP_MINOR_REV_ID_DEV0_F1_OFFSET                              20
#define STRAP_MINOR_REV_ID_DEV0_F1_WIDTH                                4
#define STRAP_MINOR_REV_ID_DEV0_F1_MASK                          0xF00000
#define Reserved_24_27_OFFSET                                          24
#define Reserved_24_27_WIDTH                                            4
#define Reserved_24_27_MASK                                     0xF000000
#define STRAP_FUNC_EN_DEV0_F1_OFFSET                                   28
#define STRAP_FUNC_EN_DEV0_F1_WIDTH                                     1
#define STRAP_FUNC_EN_DEV0_F1_MASK                             0x10000000
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F1_OFFSET                     29
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F1_WIDTH                       1
#define STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F1_MASK               0x20000000
#define STRAP_D1_SUPPORT_DEV0_F1_OFFSET                                30
#define STRAP_D1_SUPPORT_DEV0_F1_WIDTH                                  1
#define STRAP_D1_SUPPORT_DEV0_F1_MASK                          0x40000000
#define STRAP_D2_SUPPORT_DEV0_F1_OFFSET                                31
#define STRAP_D2_SUPPORT_DEV0_F1_WIDTH                                  1
#define STRAP_D2_SUPPORT_DEV0_F1_MASK                          0x80000000


/// RCC_DEV0_EPF1_STRAP0
typedef union {
  struct {
    UINT32                                   STRAP_DEVICE_ID_DEV0_F1:16 ;            ///<
    UINT32                                 STRAP_MAJOR_REV_ID_DEV0_F1:4 ;            ///<
    UINT32                                 STRAP_MINOR_REV_ID_DEV0_F1:4 ;            ///<
    UINT32                                             Reserved_24_27:4 ;            ///<
    UINT32                                      STRAP_FUNC_EN_DEV0_F1:1 ;            ///<
    UINT32                        STRAP_LEGACY_DEVICE_TYPE_EN_DEV0_F1:1 ;            ///<
    UINT32                                   STRAP_D1_SUPPORT_DEV0_F1:1 ;            ///<
    UINT32                                   STRAP_D2_SUPPORT_DEV0_F1:1 ;            ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_DEV0_EPF1_STRAP0_STRUCT;

// Register Name RCC_BIF_STRAP2_

// Address
#define RCC_BIF_STRAP2_ADDRESS                                          0x101234c8

// Type
#define RCC_BIF_STRAP2_TYPE                                               TYPE_SMN

#define RCC_BIF_STRAP2_SRIOV_EN_DEV0_F0_OFFSET                                   0
#define RCC_BIF_STRAP2_SRIOV_EN_DEV0_F0_WIDTH                                    1
#define RCC_BIF_STRAP2_SRIOV_EN_DEV0_F0_MASK                                   0x1
#define RCC_BIF_STRAP2_SRIOV_TOTAL_VFS_DEV0_F0_OFFSET                            1
#define RCC_BIF_STRAP2_SRIOV_TOTAL_VFS_DEV0_F0_WIDTH                             5
#define RCC_BIF_STRAP2_SRIOV_TOTAL_VFS_DEV0_F0_MASK                           0x3E
#define RCC_BIF_STRAP2_64BAR_DIS_DEV0_F0_OFFSET                                  6
#define RCC_BIF_STRAP2_64BAR_DIS_DEV0_F0_WIDTH                                   1
#define RCC_BIF_STRAP2_64BAR_DIS_DEV0_F0_MASK                                 0x40
#define RCC_BIF_STRAP2_NO_SOFT_RESET_DEV0_F0_OFFSET                              7
#define RCC_BIF_STRAP2_NO_SOFT_RESET_DEV0_F0_WIDTH                               1
#define RCC_BIF_STRAP2_NO_SOFT_RESET_DEV0_F0_MASK                             0x80
#define RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_OFFSET                              8
#define RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_WIDTH                               1
#define RCC_BIF_STRAP2_RESIZE_BAR_EN_DEV0_F0_MASK                            0x100
#define RCC_BIF_STRAP2_MAX_PASID_WIDTH_DEV0_F0_OFFSET                            9
#define RCC_BIF_STRAP2_MAX_PASID_WIDTH_DEV0_F0_WIDTH                             5
#define RCC_BIF_STRAP2_MAX_PASID_WIDTH_DEV0_F0_MASK                         0x3E00
#define RCC_BIF_STRAP2_MSI_PERVECTOR_MASK_CAP_DEV0_F0_OFFSET                    14
#define RCC_BIF_STRAP2_MSI_PERVECTOR_MASK_CAP_DEV0_F0_WIDTH                      1
#define RCC_BIF_STRAP2_MSI_PERVECTOR_MASK_CAP_DEV0_F0_MASK                  0x4000
#define RCC_BIF_STRAP2_ARI_EN_DEV0_F0_OFFSET                                    15
#define RCC_BIF_STRAP2_ARI_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_ARI_EN_DEV0_F0_MASK                                  0x8000
#define RCC_BIF_STRAP2_AER_EN_DEV0_F0_OFFSET                                    16
#define RCC_BIF_STRAP2_AER_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_AER_EN_DEV0_F0_MASK                                 0x10000
#define RCC_BIF_STRAP2_ACS_EN_DEV0_F0_OFFSET                                    17
#define RCC_BIF_STRAP2_ACS_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_ACS_EN_DEV0_F0_MASK                                 0x20000
#define RCC_BIF_STRAP2_ATS_EN_DEV0_F0_OFFSET                                    18
#define RCC_BIF_STRAP2_ATS_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_ATS_EN_DEV0_F0_MASK                                 0x40000
#define RCC_BIF_STRAP2_CPL_ABORT_ERR_EN_DEV0_F0_OFFSET                          20
#define RCC_BIF_STRAP2_CPL_ABORT_ERR_EN_DEV0_F0_WIDTH                            1
#define RCC_BIF_STRAP2_CPL_ABORT_ERR_EN_DEV0_F0_MASK                      0x100000
#define RCC_BIF_STRAP2_DPA_EN_DEV0_F0_OFFSET                                    21
#define RCC_BIF_STRAP2_DPA_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_DPA_EN_DEV0_F0_MASK                                0x200000
#define RCC_BIF_STRAP2_DSN_EN_DEV0_F0_OFFSET                                    22
#define RCC_BIF_STRAP2_DSN_EN_DEV0_F0_WIDTH                                      1
#define RCC_BIF_STRAP2_DSN_EN_DEV0_F0_MASK                                0x400000
#define RCC_BIF_STRAP2_VC_EN_DEV0_F0_OFFSET                                     23
#define RCC_BIF_STRAP2_VC_EN_DEV0_F0_WIDTH                                       1
#define RCC_BIF_STRAP2_VC_EN_DEV0_F0_MASK                                 0x800000
#define RCC_BIF_STRAP2_MSI_MULTI_CAP_DEV0_F0_OFFSET                             24
#define RCC_BIF_STRAP2_MSI_MULTI_CAP_DEV0_F0_WIDTH                               3
#define RCC_BIF_STRAP2_MSI_MULTI_CAP_DEV0_F0_MASK                        0x7000000
#define RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_OFFSET                               27
#define RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_WIDTH                                 1
#define RCC_BIF_STRAP2_PAGE_REQ_EN_DEV0_F0_MASK                          0x8000000
#define RCC_BIF_STRAP2_PASID_EN_DEV0_F0_OFFSET                                  28
#define RCC_BIF_STRAP2_PASID_EN_DEV0_F0_WIDTH                                    1
#define RCC_BIF_STRAP2_PASID_EN_DEV0_F0_MASK                            0x10000000
#define RCC_BIF_STRAP2_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_OFFSET            29
#define RCC_BIF_STRAP2_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_WIDTH              1
#define RCC_BIF_STRAP2_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0_MASK      0x20000000
#define RCC_BIF_STRAP2_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_OFFSET         30
#define RCC_BIF_STRAP2_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_WIDTH           1
#define RCC_BIF_STRAP2_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0_MASK   0x40000000
#define RCC_BIF_STRAP2_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_OFFSET                 31
#define RCC_BIF_STRAP2_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_WIDTH                   1
#define RCC_BIF_STRAP2_PASID_PRIV_MODE_SUPPORTED_DEV0_F0_MASK           0x80000000

/// RCC_BIF_STRAP2
typedef union {
  struct {
    UINT32                             STRAP_SRIOV_EN_DEV0_F0:1 ;           ///<
    UINT32                             STRAP_SRIOV_TOTAL_VFS_DEV0_F0:5 ;    ///<
    UINT32                             STRAP_64BAR_DIS_DEV0_F0:1 ;          ///<
    UINT32                             STRAP_NO_SOFT_RESET_DEV0_F0:1 ;      ///<
    UINT32                             STRAP_RESIZE_BAR_EN_DEV0_F0:1 ;      ///<
    UINT32                             STRAP_MAX_PASID_WIDTH_DEV0_F0:5 ;    ///<
    UINT32                             STRAP_MSI_PERVECTOR_MASK_CAP_DEV0_F0:1 ; ///<
    UINT32                             STRAP_ARI_EN_DEV0_F0:1 ;             ///<
    UINT32                             STRAP_AER_EN_DEV0_F0:1 ;             ///<
    UINT32                             STRAP_ACS_EN_DEV0_F0:1 ;             ///<
    UINT32                             STRAP_ATS_EN_DEV0_F0:1 ;             ///<
    UINT32                             Reserved:1 ;                         ///<
    UINT32                             STRAP_CPL_ABORT_ERR_EN_DEV0_F0:1 ;   ///<
    UINT32                             STRAP_DPA_EN_DEV0_F0:1 ;             ///<
    UINT32                             STRAP_DSN_EN_DEV0_F0:1 ;             ///<
    UINT32                             STRAP_VC_EN_DEV0_F0:1 ;              ///<
    UINT32                             STRAP_MSI_MULTI_CAP_DEV0_F0:3 ;      ///<
    UINT32                             STRAP_PAGE_REQ_EN_DEV0_F0:1 ;        ///<
    UINT32                             STRAP_PASID_EN_DEV0_F0:1 ;           ///<
    UINT32                             STRAP_PASID_EXE_PERMISSION_SUPPORTED_DEV0_F0:1 ; ///<
    UINT32                             STRAP_PASID_GLOBAL_INVALIDATE_SUPPORTED_DEV0_F0:1 ; ///<
    UINT32                             STRAP_PASID_PRIV_MODE_SUPPORTED_DEV0_F0:1 ; ///<
  } Field;                                                                  ///<
  UINT32 Value;                                                             ///<
} RCC_BIF_STRAP2_STRUCT;

// Register Name RCC_BIF_STRAP3_

// Address
#define RCC_BIF_STRAP3_ADDRESS                                         0x101234a8
// Type
#define RCC_BIF_STRAP3_TYPE                                              TYPE_SMN

#define RCC_BIF_STRAP3_LINK_BW_NOTIFICATION_CAP_DN_EN_DEV0_OFFSET               0
#define RCC_BIF_STRAP3_LINK_BW_NOTIFICATION_CAP_DN_EN_DEV0_WIDTH                1
#define RCC_BIF_STRAP3_LINK_BW_NOTIFICATION_CAP_DN_EN_DEV0_MASK               0x1
#define RCC_BIF_STRAP3_LTR_EN_DEV0_OFFSET                                       1
#define RCC_BIF_STRAP3_LTR_EN_DEV0_WIDTH                                        1
#define RCC_BIF_STRAP3_LTR_EN_DEV0_MASK                                       0x2
#define RCC_BIF_STRAP3_LTR_EN_DN_DEV0_OFFSET                                    2
#define RCC_BIF_STRAP3_LTR_EN_DN_DEV0_WIDTH                                     1
#define RCC_BIF_STRAP3_LTR_EN_DN_DEV0_MASK                                    0x4
#define RCC_BIF_STRAP3_MAX_PAYLOAD_SUPPORT_DEV0_OFFSET                          3
#define RCC_BIF_STRAP3_MAX_PAYLOAD_SUPPORT_DEV0_WIDTH                           3
#define RCC_BIF_STRAP3_MAX_PAYLOAD_SUPPORT_DEV0_MASK                         0x38
#define RCC_BIF_STRAP3_MSI_EN_DN_DEV0_OFFSET                                    6
#define RCC_BIF_STRAP3_MSI_EN_DN_DEV0_WIDTH                                     1
#define RCC_BIF_STRAP3_MSI_EN_DN_DEV0_MASK                                   0x40
#define RCC_BIF_STRAP3_MSTCPL_TIMEOUT_EN_DEV0_OFFSET                            7
#define RCC_BIF_STRAP3_MSTCPL_TIMEOUT_EN_DEV0_WIDTH                             1
#define RCC_BIF_STRAP3_MSTCPL_TIMEOUT_EN_DEV0_MASK                           0x80
#define RCC_BIF_STRAP3_NO_SOFT_RESET_DN_DEV0_OFFSET                             8
#define RCC_BIF_STRAP3_NO_SOFT_RESET_DN_DEV0_WIDTH                              1
#define RCC_BIF_STRAP3_NO_SOFT_RESET_DN_DEV0_MASK                           0x100
#define RCC_BIF_STRAP3_OBFF_SUPPORTED_DEV0_OFFSET                               9
#define RCC_BIF_STRAP3_OBFF_SUPPORTED_DEV0_WIDTH                                2
#define RCC_BIF_STRAP3_OBFF_SUPPORTED_DEV0_MASK                             0x600
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_DEV0_OFFSET     11
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_DEV0_WIDTH       3
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_DEV0_MASK   0x3800
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_DEV0_OFFSET          14
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_DEV0_WIDTH            4
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_DEV0_MASK       0x3C000
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_DEV0_OFFSET       18
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_DEV0_WIDTH         3
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_DEV0_MASK   0x1C0000
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_DEV0_OFFSET            21
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_DEV0_WIDTH              4
#define RCC_BIF_STRAP3_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_DEV0_MASK       0x1E00000
#define RCC_BIF_STRAP3_PM_SUPPORT_DEV0_OFFSET                                 25
#define RCC_BIF_STRAP3_PM_SUPPORT_DEV0_WIDTH                                   2
#define RCC_BIF_STRAP3_PM_SUPPORT_DEV0_MASK                            0x6000000
#define RCC_BIF_STRAP3_PM_SUPPORT_DN_DEV0_OFFSET                              27
#define RCC_BIF_STRAP3_PM_SUPPORT_DN_DEV0_WIDTH                                2
#define RCC_BIF_STRAP3_PM_SUPPORT_DN_DEV0_MASK                        0x18000000
#define RCC_BIF_STRAP3_ATOMIC_EN_DN_DEV0_OFFSET                               29
#define RCC_BIF_STRAP3_ATOMIC_EN_DN_DEV0_WIDTH                                 1
#define RCC_BIF_STRAP3_ATOMIC_EN_DN_DEV0_MASK                         0x20000000
#define RCC_BIF_STRAP3_VENDOR_ID_BIT_DN_DEV0_OFFSET                           30
#define RCC_BIF_STRAP3_VENDOR_ID_BIT_DN_DEV0_WIDTH                             1
#define RCC_BIF_STRAP3_VENDOR_ID_BIT_DN_DEV0_MASK                     0x40000000
#define RCC_BIF_STRAP3_PMC_DSI_DN_DEV0_OFFSET                                 31
#define RCC_BIF_STRAP3_PMC_DSI_DN_DEV0_WIDTH                                   1
#define RCC_BIF_STRAP3_PMC_DSI_DN_DEV0_MASK                           0x80000000

/// RCC_BIF_STRAP3
typedef union {
  struct {
    UINT32                             STRAP_LINK_BW_NOTIFICATION_CAP_DN_EN_DEV0:1 ;  ///<
    UINT32                             STRAP_LTR_EN_DEV0:1 ;                ///<
    UINT32                             STRAP_LTR_EN_DN_DEV0:1 ;             ///<
    UINT32                             STRAP_MAX_PAYLOAD_SUPPORT_DEV0:3 ;   ///<
    UINT32                             STRAP_MSI_EN_DN_DEV0:1 ;             ///<
    UINT32                             STRAP_MSTCPL_TIMEOUT_EN_DEV0:1 ;     ///<
    UINT32                             STRAP_NO_SOFT_RESET_DN_DEV0:1 ;      ///<
    UINT32                             STRAP_OBFF_SUPPORTED_DEV0:2 ;        ///<
    UINT32                             STRAP_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_DEV0:3 ;  ///<
    UINT32                             STRAP_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_DEV0:4 ;       ///<
    UINT32                             STRAP_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_DEV0:3 ;    ///<
    UINT32                             STRAP_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_DEV0:4 ;         ///<
    UINT32                             STRAP_PM_SUPPORT_DEV0:2 ;            ///<
    UINT32                             STRAP_PM_SUPPORT_DN_DEV0:2 ;         ///<
    UINT32                             STRAP_ATOMIC_EN_DN_DEV0:1 ;          ///<
    UINT32                             STRAP_VENDOR_ID_BIT_DN_DEV0:1 ;      ///<
    UINT32                             STRAP_PMC_DSI_DN_DEV0:1 ;            ///<
  } Field;                                                   ///<
  UINT32 Value;                                                             ///<
} RCC_BIF_STRAP3_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF0

// Address
#define RCC_DEV0_EPF0_STRAP4_ADDRESS                                  0x101234d0
#define RCC_DEV0_EPF0_STRAP4_TYPE                                       TYPE_SMN


#define RCC_STRAP_MSIX_TABLE_OFFSET_DEV0_F0_OFFSET                             0
#define RCC_STRAP_MSIX_TABLE_OFFSET_DEV0_F0_WIDTH                             20
#define RCC_STRAP_MSIX_TABLE_OFFSET_DEV0_F0_MASK                         0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F0_OFFSET                              20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F0_WIDTH                                1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F0_MASK                          0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F0_OFFSET                                    21
#define RCC_STRAP_ATOMIC_EN_DEV0_F0_WIDTH                                      1
#define RCC_STRAP_ATOMIC_EN_DEV0_F0_MASK                                0x200000
#define RCC_STRAP_FLR_EN_DEV0_F0_OFFSET                                       22
#define RCC_STRAP_FLR_EN_DEV0_F0_WIDTH                                         1
#define RCC_STRAP_FLR_EN_DEV0_F0_MASK                                   0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F0_OFFSET                                  23
#define RCC_STRAP_PME_SUPPORT_DEV0_F0_WIDTH                                    5
#define RCC_STRAP_PME_SUPPORT_DEV0_F0_MASK                             0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F0_OFFSET                                28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F0_WIDTH                                  3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F0_MASK                          0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F0_OFFSET                               31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F0_WIDTH                                 1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F0_MASK                         0x80000000

/// RCC_BIF_STRAP4
typedef union {
  struct {
    UINT32                                  STRAP_MSIX_TABLE_OFFSET_DEV0_F0:20 ;  ///<
    UINT32                                     STRAP_ATOMIC_64BIT_EN_DEV0_F0:1 ;  ///<
    UINT32                                           STRAP_ATOMIC_EN_DEV0_F0:1 ;  ///<
    UINT32                                              STRAP_FLR_EN_DEV0_F0:1 ;  ///<
    UINT32                                         STRAP_PME_SUPPORT_DEV0_F0:5 ;  ///<
    UINT32                                       STRAP_INTERRUPT_PIN_DEV0_F0:3 ;  ///<
    UINT32                                      STRAP_AUXPWR_SUPPORT_DEV0_F0:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF0_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF1

// Address
#define RCC_DEV0_EPF1_STRAP4_ADDRESS                                 0x101234fc
#define RCC_DEV0_EPF1_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F1_Reserved_OFFSET                                               0
#define DEV0_F1_Reserved_WIDTH                                               20
#define DEV0_F1_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F1_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F1_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F1_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F1_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F1_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F1_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F1_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F1_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F1_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F1_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F1_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F1_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F1_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F1_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F1_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F1_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F1_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F1_MASK                        0x80000000


/// RCC_BIF_STRAP4
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F1:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F1:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F1:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F1:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F1:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F1:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF1_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF2

// Address
#define RCC_DEV0_EPF2_STRAP4_ADDRESS                                 0x10134410
#define RCC_DEV0_EPF2_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F2_Reserved_OFFSET                                               0
#define DEV0_F2_Reserved_WIDTH                                               20
#define DEV0_F2_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F2_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F2_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F2_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F2_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F2_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F2_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F2_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F2_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F2_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F2_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F2_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F2_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F2_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F2_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F2_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F2_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F2_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F2_MASK                        0x80000000

/// RCC_BIF_STRAP4
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F2:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F2:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F2:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F2:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F2:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F2:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF2_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF3

// Address
#define RCC_DEV0_EPF3_STRAP4_ADDRESS                                 0x10134610
#define RCC_DEV0_EPF3_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F3_Reserved_OFFSET                                               0
#define DEV0_F3_Reserved_WIDTH                                               20
#define DEV0_F3_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F3_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F3_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F3_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F3_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F3_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F3_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F3_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F3_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F3_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F3_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F3_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F3_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F3_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F3_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F3_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F3_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F3_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F3_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV0_EPF3
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F3:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F3:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F3:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F3:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F3:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F3:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF3_STRAP4_STRUCT;

// Register Name RCC_BIF_STRAP4_DEV0_EPF4

// Address
#define RCC_DEV0_EPF4_STRAP4_ADDRESS                                 0x10134810
#define RCC_DEV0_EPF4_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F4_Reserved_OFFSET                                               0
#define DEV0_F4_Reserved_WIDTH                                               20
#define DEV0_F4_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F4_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F4_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F4_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F4_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F4_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F4_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F4_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F4_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F4_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F4_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F4_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F4_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F4_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F4_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F4_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F4_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F4_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F4_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV0_EPF4
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F4:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F4:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F4:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F4:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F4:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F4:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF4_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF5

// Address
#define RCC_DEV0_EPF5_STRAP4_ADDRESS                                 0x10134a10
#define RCC_DEV0_EPF5_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F5_Reserved_OFFSET                                               0
#define DEV0_F5_Reserved_WIDTH                                               20
#define DEV0_F5_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F5_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F5_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F5_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F5_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F5_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F5_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F5_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F5_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F5_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F5_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F5_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F5_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F5_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F5_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F5_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F5_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F5_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F5_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV0_EPF5
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F5:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F5:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F5:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F5:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F5:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F5:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF5_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV0_EPF6

// Address
#define RCC_DEV0_EPF6_STRAP4_ADDRESS                                 0x10134c10
#define RCC_DEV0_EPF6_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F6_Reserved_OFFSET                                               0
#define DEV0_F6_Reserved_WIDTH                                               20
#define DEV0_F6_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F6_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F6_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F6_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F6_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F6_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F6_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F6_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F6_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F6_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F6_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F6_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F6_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F6_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F6_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F6_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F6_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F6_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F6_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV0_EPF6
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F6:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F6:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F6:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F6:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F6:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F6:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF6_STRAP4_STRUCT;

// Register Name RCC_BIF_STRAP4_DEV0_EPF7

// Address
#define RCC_DEV0_EPF7_STRAP4_ADDRESS                                 0x10134e10
#define RCC_DEV0_EPF7_STRAP4_TYPE                                      TYPE_SMN

#define DEV0_F7_Reserved_OFFSET                                               0
#define DEV0_F7_Reserved_WIDTH                                               20
#define DEV0_F7_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F7_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F7_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV0_F7_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV0_F7_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV0_F7_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV0_F7_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV0_F7_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV0_F7_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV0_F7_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV0_F7_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV0_F7_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV0_F7_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F7_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F7_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV0_F7_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F7_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F7_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV0_F7_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV0_EPF7
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV0_F7:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV0_F7:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV0_F7:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV0_F7:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV0_F7:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV0_F7:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV0_EPF7_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV1_EPF0

// Address
#define RCC_DEV1_EPF0_STRAP4_ADDRESS                                 0x10135010
#define RCC_DEV1_EPF0_STRAP4_TYPE                                      TYPE_SMN

#define DEV1_F0_Reserved_OFFSET                                               0
#define DEV1_F0_Reserved_WIDTH                                               20
#define DEV1_F0_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F0_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F0_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F0_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV1_F0_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV1_F0_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV1_F0_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV1_F0_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV1_F0_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV1_F0_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV1_F0_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV1_F0_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV1_F0_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F0_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F0_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F0_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F0_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F0_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F0_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV1_EPF0
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV1_F0:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV1_F0:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV1_F0:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV1_F0:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV1_F0:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV1_F0:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV1_EPF0_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV1_EPF1

// Address
#define RCC_DEV1_EPF1_STRAP4_ADDRESS                                 0x10135210
#define RCC_DEV1_EPF1_STRAP4_TYPE                                      TYPE_SMN

#define DEV1_F1_Reserved_OFFSET                                               0
#define DEV1_F1_Reserved_WIDTH                                               20
#define DEV1_F1_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F1_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F1_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F1_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV1_F1_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV1_F1_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV1_F1_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV1_F1_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV1_F1_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV1_F1_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV1_F1_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV1_F1_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV1_F1_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F1_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F1_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F1_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F1_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F1_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F1_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV1_EPF1
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV1_F1:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV1_F1:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV1_F1:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV1_F1:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV1_F1:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV1_F1:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV1_EPF1_STRAP4_STRUCT;


// Register Name RCC_BIF_STRAP4_DEV1_EPF2

// Address
#define RCC_DEV1_EPF2_STRAP4_ADDRESS                                 0x10135410
#define RCC_DEV1_EPF2_STRAP4_TYPE                                      TYPE_SMN

#define DEV1_F2_Reserved_OFFSET                                               0
#define DEV1_F2_Reserved_WIDTH                                               20
#define DEV1_F2_Reserved_MASK                                           0xFFFFF
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F2_OFFSET                             20
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F2_WIDTH                               1
#define RCC_STRAP_ATOMIC_64BIT_EN_DEV1_F2_MASK                         0x100000
#define RCC_STRAP_ATOMIC_EN_DEV1_F2_OFFSET                                   21
#define RCC_STRAP_ATOMIC_EN_DEV1_F2_WIDTH                                     1
#define RCC_STRAP_ATOMIC_EN_DEV1_F2_MASK                               0x200000
#define RCC_STRAP_FLR_EN_DEV1_F2_OFFSET                                      22
#define RCC_STRAP_FLR_EN_DEV1_F2_WIDTH                                        1
#define RCC_STRAP_FLR_EN_DEV1_F2_MASK                                  0x400000
#define RCC_STRAP_PME_SUPPORT_DEV1_F2_OFFSET                                 23
#define RCC_STRAP_PME_SUPPORT_DEV1_F2_WIDTH                                   5
#define RCC_STRAP_PME_SUPPORT_DEV1_F2_MASK                            0xF800000
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F2_OFFSET                               28
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F2_WIDTH                                 3
#define RCC_STRAP_INTERRUPT_PIN_DEV1_F2_MASK                         0x70000000
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F2_OFFSET                              31
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F2_WIDTH                                1
#define RCC_STRAP_AUXPWR_SUPPORT_DEV1_F2_MASK                        0x80000000

/// RCC_BIF_STRAP4_DEV1_EPF2
typedef union {
  struct {
    UINT32                                                        Reserved:20 ;  ///<
    UINT32                                    STRAP_ATOMIC_64BIT_EN_DEV1_F2:1 ;  ///<
    UINT32                                          STRAP_ATOMIC_EN_DEV1_F2:1 ;  ///<
    UINT32                                             STRAP_FLR_EN_DEV1_F2:1 ;  ///<
    UINT32                                        STRAP_PME_SUPPORT_DEV1_F2:5 ;  ///<
    UINT32                                      STRAP_INTERRUPT_PIN_DEV1_F2:3 ;  ///<
    UINT32                                     STRAP_AUXPWR_SUPPORT_DEV1_F2:1 ;  ///<
  } Field;                                                   ///<
  UINT32 Value;
} RCC_BIF_DEV1_EPF2_STRAP4_STRUCT;

// Register Name RCC_BIF_STRAP8_

// Address
#define RCC_BIF_STRAP8_ADDRESS                                          0x101234d8

// Type
#define RCC_BIF_STRAP8_TYPE                                               TYPE_SMN


#define RCC_BIF_STRAP8_BAR_COMPLIANCE_EN_DEV0_F0_OFFSET                          0
#define RCC_BIF_STRAP8_BAR_COMPLIANCE_EN_DEV0_F0_WIDTH                           1
#define RCC_BIF_STRAP8_BAR_COMPLIANCE_EN_DEV0_F0_MASK                          0x1
#define RCC_BIF_STRAP8_DOORBELL_APER_SIZE_DEV0_F0_OFFSET                         1
#define RCC_BIF_STRAP8_DOORBELL_APER_SIZE_DEV0_F0_WIDTH                          2
#define RCC_BIF_STRAP8_DOORBELL_APER_SIZE_DEV0_F0_MASK                         0x6
#define RCC_BIF_STRAP8_DOORBELL_BAR_DIS_DEV0_F0_OFFSET                           3
#define RCC_BIF_STRAP8_DOORBELL_BAR_DIS_DEV0_F0_WIDTH                            1
#define RCC_BIF_STRAP8_DOORBELL_BAR_DIS_DEV0_F0_MASK                           0x8
#define RCC_BIF_STRAP8_FB_ALWAYS_ON_DEV0_F0_OFFSET                               4
#define RCC_BIF_STRAP8_FB_ALWAYS_ON_DEV0_F0_WIDTH                                1
#define RCC_BIF_STRAP8_FB_ALWAYS_ON_DEV0_F0_MASK                              0x10
#define RCC_BIF_STRAP8_FB_CPL_TYPE_SEL_DEV0_F0_OFFSET                            5
#define RCC_BIF_STRAP8_FB_CPL_TYPE_SEL_DEV0_F0_WIDTH                             2
#define RCC_BIF_STRAP8_FB_CPL_TYPE_SEL_DEV0_F0_MASK                           0x60
#define RCC_BIF_STRAP8_IO_BAR_DIS_DEV0_F0_OFFSET                                 7
#define RCC_BIF_STRAP8_IO_BAR_DIS_DEV0_F0_WIDTH                                  1
#define RCC_BIF_STRAP8_IO_BAR_DIS_DEV0_F0_MASK                                0x80
#define RCC_BIF_STRAP8_LFB_ERRMSG_EN_DEV0_F0_OFFSET                              8
#define RCC_BIF_STRAP8_LFB_ERRMSG_EN_DEV0_F0_WIDTH                               1
#define RCC_BIF_STRAP8_LFB_ERRMSG_EN_DEV0_F0_MASK                            0x100
#define RCC_BIF_STRAP8_MEM_AP_SIZE_DEV0_F0_OFFSET                                9
#define RCC_BIF_STRAP8_MEM_AP_SIZE_DEV0_F0_WIDTH                                 3
#define RCC_BIF_STRAP8_MEM_AP_SIZE_DEV0_F0_MASK                              0xE00
#define RCC_BIF_STRAP8_REG_AP_SIZE_DEV0_F0_OFFSET                               12
#define RCC_BIF_STRAP8_REG_AP_SIZE_DEV0_F0_WIDTH                                 2
#define RCC_BIF_STRAP8_REG_AP_SIZE_DEV0_F0_MASK                             0x3000
#define RCC_BIF_STRAP8_ROM_AP_SIZE_DEV0_F0_OFFSET                               14
#define RCC_BIF_STRAP8_ROM_AP_SIZE_DEV0_F0_WIDTH                                 2
#define RCC_BIF_STRAP8_ROM_AP_SIZE_DEV0_F0_MASK                             0xC000
#define RCC_BIF_STRAP8_VF_DOORBELL_APER_SIZE_DEV0_F0_OFFSET                     16
#define RCC_BIF_STRAP8_VF_DOORBELL_APER_SIZE_DEV0_F0_WIDTH                       3
#define RCC_BIF_STRAP8_VF_DOORBELL_APER_SIZE_DEV0_F0_MASK                  0x70000
#define RCC_BIF_STRAP8_VF_MEM_AP_SIZE_DEV0_F0_OFFSET                            19
#define RCC_BIF_STRAP8_VF_MEM_AP_SIZE_DEV0_F0_WIDTH                              3
#define RCC_BIF_STRAP8_VF_MEM_AP_SIZE_DEV0_F0_MASK                      0x00380000
#define RCC_BIF_STRAP8_VF_REG_AP_SIZE_DEV0_F0_OFFSET                            22
#define RCC_BIF_STRAP8_VF_REG_AP_SIZE_DEV0_F0_WIDTH                              2
#define RCC_BIF_STRAP8_VF_REG_AP_SIZE_DEV0_F0_MASK                        0xC00000
#define RCC_BIF_STRAP8_VGA_DIS_DEV0_F0_OFFSET                                   24
#define RCC_BIF_STRAP8_VGA_DIS_DEV0_F0_WIDTH                                     1
#define RCC_BIF_STRAP8_VGA_DIS_DEV0_F0_MASK                              0x1000000
#define RCC_BIF_STRAP8_NBIF_ROM_BAR_DIS_CHICKEN_DEV0_F0_OFFSET                  25
#define RCC_BIF_STRAP8_NBIF_ROM_BAR_DIS_CHICKEN_DEV0_F0_WIDTH                    1
#define RCC_BIF_STRAP8_NBIF_ROM_BAR_DIS_CHICKEN_DEV0_F0_MASK             0x2000000
#define RCC_BIF_STRAP8_VF_REG_PROT_DIS_DEV0_F0_OFFSET                           26
#define RCC_BIF_STRAP8_VF_REG_PROT_DIS_DEV0_F0_WIDTH                             1
#define RCC_BIF_STRAP8_VF_REG_PROT_DIS_DEV0_F0_MASK                      0x4000000
#define RCC_BIF_STRAP8_VF_MSI_MULTI_CAP_DEV0_F0_OFFSET                          27
#define RCC_BIF_STRAP8_VF_MSI_MULTI_CAP_DEV0_F0_WIDTH                            3
#define RCC_BIF_STRAP8_VF_MSI_MULTI_CAP_DEV0_F0_MASK                    0x38000000
#define RCC_BIF_STRAP8_SRIOV_VF_MAPPING_MODE_DEV0_F0_OFFSET                     30
#define RCC_BIF_STRAP8_SRIOV_VF_MAPPING_MODE_DEV0_F0_WIDTH                       2
#define RCC_BIF_STRAP8_SRIOV_VF_MAPPING_MODE_DEV0_F0_MASK               0xC0000000

/// RCC_BIF_STRAP8
typedef union {
  struct {
    UINT32                             STRAP_BAR_COMPLIANCE_EN_DEV0_F0:1 ;  ///<
    UINT32                             STRAP_DOORBELL_APER_SIZE_DEV0_F0:2 ; ///<
    UINT32                             STRAP_DOORBELL_BAR_DIS_DEV0_F0:1 ;   ///<
    UINT32                             STRAP_FB_ALWAYS_ON_DEV0_F0:1 ;       ///<
    UINT32                             STRAP_FB_CPL_TYPE_SEL_DEV0_F0:2 ;    ///<
    UINT32                             STRAP_IO_BAR_DIS_DEV0_F0:1 ;         ///<
    UINT32                             STRAP_LFB_ERRMSG_EN_DEV0_F0:1 ;      ///<
    UINT32                             STRAP_MEM_AP_SIZE_DEV0_F0:3 ;        ///<
    UINT32                             STRAP_REG_AP_SIZE_DEV0_F0:2 ;        ///<
    UINT32                             STRAP_ROM_AP_SIZE_DEV0_F0:2 ;        ///<
    UINT32                             STRAP_VF_DOORBELL_APER_SIZE_DEV0_F0:3 ; ///<
    UINT32                             STRAP_VF_MEM_AP_SIZE_DEV0_F0:3 ;     ///<
    UINT32                             STRAP_VF_REG_AP_SIZE_DEV0_F0:2 ;     ///<
    UINT32                             STRAP_VGA_DIS_DEV0_F0:1 ;            ///<
    UINT32                             STRAP_NBIF_ROM_BAR_DIS_CHICKEN_DEV0_F0:1 ; ///<
    UINT32                             STRAP_VF_REG_PROT_DIS_DEV0_F0:1 ;    ///<
    UINT32                             STRAP_VF_MSI_MULTI_CAP_DEV0_F0:3 ;   ///<
    UINT32                             STRAP_SRIOV_VF_MAPPING_MODE_DEV0_F0:2 ;    ///<
  } Field;                                                   ///<
  UINT32 Value;                                                             ///<
} RCC_BIF_STRAP8_STRUCT;


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


// Register Name ACP_I2S_PIN_CONFIG

// Address
#define SMN_ACP_I2S_PIN_CONFIG_ADDRESS                        0x1241400
#define SMN_0x1241400                                         0x1241400

// Type
#define SMN_ACP_I2S_PIN_CONFIGTYPE                            TYPE_SMN

#define SMN_ACP_I2S_PIN_CONFIG_OFFSET                         0
#define SMN_ACP_I2S_PIN_CONFIG_WIDTH                          3
#define SMN_ACP_I2S_PIN_CONFIG_MASK                           0x7
#define SMN_Reserved_31_3_OFFSET                              3
#define SMN_Reserved_31_3_WIDTH                               29
#define SMN_Reserved_31_3_MASK                                0xfffffff8L

/// ACPMMIO_00041400
typedef union {
  struct {
    UINT32                                      ACP_I2S_PIN_CONFIG:3 ; ///<
    UINT32                                           Reserved_31_3:29; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN__STRUCT;


#define PCIE0_SLOT_APERTURE                                    0x11100000
// Address
#define EXTENDED_TAG_Cap_ADDRESS                               0x1110005C
// Address
#define EXTENDED_TAG_ADDRESS                                   0x11100060
// Address
#define Native_PME_ADDRESS                                     0x11100074


// Address
#define SLOT_CAP_ADDRESS                                       0x6C
#define GPP0_SLOT_CAP_ADDRESS                                  0x1110006C
#define GPP1_SLOT_CAP_ADDRESS                                  0x1110106C
#define GPP2_SLOT_CAP_ADDRESS                                  0x1110206C
#define GPP3_SLOT_CAP_ADDRESS                                  0x1110306C
#define GPP4_SLOT_CAP_ADDRESS                                  0x1110406C
#define GPP5_SLOT_CAP_ADDRESS                                  0x1110506C
#define GPP6_SLOT_CAP_ADDRESS                                  0x1110606C

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


//
// Register Name PCIE_L1_PM_SUB_CAP
//
#define SMN_PCIE0FUNC0_PCIE_L1_PM_SUB_CAP_ADDRESS              0x11100374UL

//
// PCIE_L1_PM_SUB_CNTL Register Bitfields:
//

/// Bitfield Description : Controls if PCI-PM L1.2 is enabled.
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_2_EN_OFFSET              0
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_2_EN_WIDTH               1
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_2_EN_MASK                0x1

/// Bitfield Description : Controls if PCI-PM L1.1 is enabled.
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_1_EN_OFFSET              1
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_1_EN_WIDTH               1
#define PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_1_EN_MASK                0x2

/// Bitfield Description : Controls if ASPM L1.2 is enabled.
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_2_EN_OFFSET                2
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_2_EN_WIDTH                 1
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_2_EN_MASK                  0x4

/// Bitfield Description : Controls if ASPM L1.1 is enabled.
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_1_EN_OFFSET                3
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_1_EN_WIDTH                 1
#define PCIE_L1_PM_SUB_CNTL_ASPM_L1_1_EN_MASK                  0x8

/// Bitfield Description :
#define PCIE_L1_PM_SUB_CNTL_Reserved_7_4_OFFSET                4
#define PCIE_L1_PM_SUB_CNTL_Reserved_7_4_WIDTH                 4
#define PCIE_L1_PM_SUB_CNTL_Reserved_7_4_MASK                  0xf0

/// Bitfield Description : (Downstream Ports only) When any of PCI-PM L1.2 Supported bit or ASPM L1.2 Supported bit is set, and if programmed when ASPM L1.2 Enable bit and PCI-PM L1.2 Enable bit are both clear, controls the value of Tcommonmode (in us) which must be used by the Downstream Port for timing the re-establishment of common mode. For Upstream Ports this field is Reserved.
#define PCIE_L1_PM_SUB_CNTL_COMMON_MODE_RESTORE_TIME_OFFSET    8
#define PCIE_L1_PM_SUB_CNTL_COMMON_MODE_RESTORE_TIME_WIDTH     8
#define PCIE_L1_PM_SUB_CNTL_COMMON_MODE_RESTORE_TIME_MASK      0xff00

/// Bitfield Description : When ASPM L1.2 Supported bit is set, and if programmed when ASPM L1.2 Enable bit is clear, in combination with the LTR L1.2 THRESHOLD Scale value, controls the LTR threshold used to determine if entry into L1 results in L1.1 (if enabled) or L1.2 (if enabled).
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_VALUE_OFFSET    16
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_VALUE_WIDTH     10
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_VALUE_MASK      0x3ff0000

/// Bitfield Description :
#define PCIE_L1_PM_SUB_CNTL_Reserved_28_26_OFFSET              26
#define PCIE_L1_PM_SUB_CNTL_Reserved_28_26_WIDTH               3
#define PCIE_L1_PM_SUB_CNTL_Reserved_28_26_MASK                0x1c000000

/// Bitfield Description : When ASPM L1.2 Supported bit is set, and if programmed when ASPM L1.2 Enable bit is clear, controls the scale used for the LTR L1.2 THRESHOLD Value.
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_SCALE_OFFSET    29
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_SCALE_WIDTH     3
#define PCIE_L1_PM_SUB_CNTL_LTR_L1_2_THRESHOLD_SCALE_MASK      0xe0000000L

typedef union {
  struct {
    UINT32                                          PCI_PM_L1_2_EN:1 ; ///<
    UINT32                                          PCI_PM_L1_1_EN:1 ; ///<
    UINT32                                            ASPM_L1_2_EN:1 ; ///<
    UINT32                                            ASPM_L1_1_EN:1 ; ///<
    UINT32                                            Reserved_7_4:4 ; ///<
    UINT32                                COMMON_MODE_RESTORE_TIME:8 ; ///<
    UINT32                                LTR_L1_2_THRESHOLD_VALUE:10; ///<
    UINT32                                          Reserved_28_26:3 ; ///<
    UINT32                                LTR_L1_2_THRESHOLD_SCALE:3 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_L1_PM_SUB_CNTL_STRUCT;


// DEVICE_CNTL2
#define DEVICE_CNTL2_ADDRESS                                   0x80
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_OFFSET                  0
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_WIDTH                   4
#define DEVICE_CNTL2_CPL_TIMEOUT_VALUE_MASK                    0xF

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

// Register Name L1_MISC_CNTRL_1
// Address
// Address
#define L1_MISC_CNTRL_1_PCIE0_ADDRESS                          0x1470001c
#define L1_MISC_CNTRL_1_PCIE1_ADDRESS                          0x1480001c //Ioagr
//#define L1_MISC_CNTRL_1_NBIF0_ADDRESS                          0x1490001c
//#define L1_MISC_CNTRL_1_IOAGR_ADDRESS                          0x14a0001c
//#define L1_DEBUG_1_PCIE0_ADDRESS                               0x1470001c
//#define L1_DEBUG_1_PCIE1_ADDRESS                               0x1480001c
//#define L1_DEBUG_1_NBIF0_ADDRESS                               0x1490001c
//#define L1_DEBUG_1_IOAGR_ADDRESS                               0x14a0001c

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

#define L1_CNTRL_1_PCIE0_ADDRESS                               0x14700034
#define L1_CNTRL_1_IOAGR_ADDRESS                               0x14800034

// Address
#define L1_CNTRL_2_PCIE0_ADDRESS                               0x14700038
#define L1_CNTRL_2_IOAGR_ADDRESS                               0x14800038

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

// Register Name PCIEP_HW_DEBUG
// Address
#define PCIE0_PCIEP_HW_DEBUG_ADDRESS                                     0x11140008

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

// Address
#define SYSHUB_DS_CTRL_SOCCLK_ADDRESS                             0x1410000

// Type
#define SYSHUB_DS_CTRL_SOCCLK_TYPE                                 TYPE_SMN

#define HST_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     0
#define HST_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x1
#define HST_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     1
#define HST_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x2
#define HST_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     2
#define HST_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x4
#define HST_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     3
#define HST_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x8
#define HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     4
#define HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x10
#define HST_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     5
#define HST_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x20
#define HST_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     6
#define HST_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x40
#define HST_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     7
#define HST_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x80
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_15_8_OFFSET                       8
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_15_8_Width                        8
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_15_8_Mask                    0xFF00
#define DMA_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    16
#define DMA_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x10000
#define DMA_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    17
#define DMA_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x20000
#define DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    18
#define DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x40000
#define DMA_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    19
#define DMA_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x80000
#define DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    20
#define DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x100000
#define DMA_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    21
#define DMA_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x200000
#define DMA_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    22
#define DMA_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x400000
#define DMA_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    23
#define DMA_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x800000
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_27_24_OFFSET                     24
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_27_24_Width                       4
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_27_24_Mask                0xF000000
#define SYSHUB_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     28
#define SYSHUB_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Width                       1
#define SYSHUB_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask               0x10000000
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_30_29_OFFSET                     29
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_30_29_Width                       2
#define SYSHUB_DS_CTRL_SOCCLK_Reserved_30_29_Mask               0x60000000
#define SYSHUB_SOCCLK_DS_EN_OFFSET                                      31
#define SYSHUB_SOCCLK_DS_EN_Width                                        1
#define SYSHUB_SOCCLK_DS_EN_Mask                                0x80000000

///SYSHUB_DS_CTRL_SOCCLK
typedef union {
   struct {
    UINT32                                        HST_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        SYSHUB_DS_CTRL_SOCCLK_Reserved_15_8:8; ///<
    UINT32                                        DMA_CL0_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL1_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL2_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL3_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL5_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL6_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL7_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                         SYSHUB_DS_CTRL_SOCCLK_Reserved_27_24:4; ///<
    UINT32                                         SYSHUB_SOCCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                         SYSHUB_DS_CTRL_SOCCLK_Reserved_30_29:2; ///<
    UINT32                                                          SYSHUB_SOCCLK_DS_EN:1; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} SYSHUB_DS_CTRL_SOCCLK_STRUCT;


// Address
#define SYSHUB_DS_CTRL_SHUBCLK_ADDRESS                             0x1411000

// Type
#define SYSHUB_DS_CTRL_SHUBCLK_TYPE                                 TYPE_SMN

#define HST_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     0
#define HST_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x1
#define HST_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     1
#define HST_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x2
#define HST_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     2
#define HST_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x4
#define HST_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     3
#define HST_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                     0x8
#define HST_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     4
#define HST_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x10
#define HST_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     5
#define HST_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x20
#define HST_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     6
#define HST_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x40
#define HST_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     7
#define HST_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define HST_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                    0x80
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_15_8_OFFSET                       8
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_15_8_Width                        8
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_15_8_Mask                    0xFF00
#define DMA_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    16
#define DMA_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x10000
#define DMA_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    17
#define DMA_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x20000
#define DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    18
#define DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x40000
#define DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    19
#define DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                 0x80000
#define DMA_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    20
#define DMA_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x100000
#define DMA_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    21
#define DMA_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x200000
#define DMA_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    22
#define DMA_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x400000
#define DMA_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                    23
#define DMA_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                      1
#define DMA_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask                0x800000
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_27_24_OFFSET                     24
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_27_24_Width                       4
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_27_24_Mask                0xF000000
#define SYSHUB_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET                     28
#define SYSHUB_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Width                       1
#define SYSHUB_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask               0x10000000
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_30_29_OFFSET                     29
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_30_29_Width                       2
#define SYSHUB_DS_CTRL_SHUBCLK_Reserved_30_29_Mask               0x60000000
#define SYSHUB_SHUBCLK_DS_EN_OFFSET                                      31
#define SYSHUB_SHUBCLK_DS_EN_Width                                        1
#define SYSHUB_SHUBCLK_DS_EN_Mask                                0x80000000

///SYSHUB_DS_CTRL_SHUBCLK
typedef union {
   struct {
    UINT32                                        HST_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        HST_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        SYSHUB_DS_CTRL_SHUBCLK_Reserved_15_8:8; ///<
    UINT32                                        DMA_CL0_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL1_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL4_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL5_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL6_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                        DMA_CL7_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                         SYSHUB_DS_CTRL_SHUBCLK_Reserved_27_24:4; ///<
    UINT32                                         SYSHUB_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE:1; ///<
    UINT32                                         SYSHUB_DS_CTRL_SHUBCLK_Reserved_30_29:2; ///<
    UINT32                                                          SYSHUB_SHUBCLK_DS_EN:1; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} SYSHUB_DS_CTRL_SHUBCLK_STRUCT;

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

// Register Name PCIE_TX_REQUESTER_ID

// Address
#define PCIE_TX_REQUESTER_ID_ADDRESS                                           0x11140084
#define GPP0_TX_REQUESTER_ID_ADDRESS                                           0x11140084
#define GPP1_TX_REQUESTER_ID_ADDRESS                                           0x11141084
#define GPP2_TX_REQUESTER_ID_ADDRESS                                           0x11142084
#define GPP3_TX_REQUESTER_ID_ADDRESS                                           0x11143084
#define GPP4_TX_REQUESTER_ID_ADDRESS                                           0x11144084
#define GPP5_TX_REQUESTER_ID_ADDRESS                                           0x11145084
#define GPP6_TX_REQUESTER_ID_ADDRESS                                           0x11146084

// Type
#define PCIE_TX_REQUESTER_ID_TYPE                                              TYPE_SMN

#define PCIE_TX_REQUESTER_ID_FUNCTION_OFFSET                                   0
#define PCIE_TX_REQUESTER_ID_FUNCTION_WIDTH                                    3
#define PCIE_TX_REQUESTER_ID_FUNCTION_MASK                                     0x7
#define PCIE_TX_REQUESTER_ID_DEVICE_OFFSET                                     3
#define PCIE_TX_REQUESTER_ID_DEVICE_WIDTH                                      5
#define PCIE_TX_REQUESTER_ID_DEVICE_MASK                                       0xf8
#define PCIE_TX_REQUESTER_ID_BUS_OFFSET                                        8
#define PCIE_TX_REQUESTER_ID_BUS_WIDTH                                         8
#define PCIE_TX_REQUESTER_ID_BUS_MASK                                          0xff00

/// PCIE_TX_REQUESTER_ID
typedef union {
  struct {
    UINT32                                   TxRequesterIdFunction:3 ; ///<
    UINT32                                     TxRequesterIdDevice:5 ; ///<
    UINT32                                        TxRequesterIdBus:8 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_TX_REQUESTER_ID_STRUCT;

// Address
#define PCIE_PORT0_1A8_ADDRESS                                         0x111401A8

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


// Register Name PCIE_LC_CNTL

// Address
#define SMN_0x11140280_ADDRESS                                 0x11140280
#define SMN_0x11140280                                         0x11140280

// Type
#define SMN_0x11140280_TYPE                                    TYPE_SMN

#define SMN_0x11140280_RESERVED_OFFSET                         0
#define SMN_0x11140280_RESERVED_WIDTH                          1
#define SMN_0x11140280_RESERVED_MASK                           0x1
#define SMN_0x11140280_LC_DONT_ENTER_L23_IN_D0_OFFSET          1
#define SMN_0x11140280_LC_DONT_ENTER_L23_IN_D0_WIDTH           1
#define SMN_0x11140280_LC_DONT_ENTER_L23_IN_D0_MASK            0x2
#define SMN_0x11140280_LC_RESET_L_IDLE_COUNT_EN_OFFSET         2
#define SMN_0x11140280_LC_RESET_L_IDLE_COUNT_EN_WIDTH          1
#define SMN_0x11140280_LC_RESET_L_IDLE_COUNT_EN_MASK           0x4
#define SMN_0x11140280_LC_RESET_LINK_OFFSET                    3
#define SMN_0x11140280_LC_RESET_LINK_WIDTH                     1
#define SMN_0x11140280_LC_RESET_LINK_MASK                      0x8
#define SMN_0x11140280_LC_16X_CLEAR_TX_PIPE_OFFSET             4
#define SMN_0x11140280_LC_16X_CLEAR_TX_PIPE_WIDTH              4
#define SMN_0x11140280_LC_16X_CLEAR_TX_PIPE_MASK               0xf0
#define SMN_0x11140280_LC_L0S_INACTIVITY_OFFSET                8
#define SMN_0x11140280_LC_L0S_INACTIVITY_WIDTH                 4
#define SMN_0x11140280_LC_L0S_INACTIVITY_MASK                  0xf00
#define SMN_0x11140280_LC_L1_INACTIVITY_OFFSET                 12
#define SMN_0x11140280_LC_L1_INACTIVITY_WIDTH                  4
#define SMN_0x11140280_LC_L1_INACTIVITY_MASK                   0xf000
#define SMN_0x11140280_LC_PMI_TO_L1_DIS_OFFSET                 16
#define SMN_0x11140280_LC_PMI_TO_L1_DIS_WIDTH                  1
#define SMN_0x11140280_LC_PMI_TO_L1_DIS_MASK                   0x10000
#define SMN_0x11140280_LC_INC_N_FTS_EN_OFFSET                  17
#define SMN_0x11140280_LC_INC_N_FTS_EN_WIDTH                   1
#define SMN_0x11140280_LC_INC_N_FTS_EN_MASK                    0x20000
#define SMN_0x11140280_LC_LOOK_FOR_IDLE_IN_L1L23_OFFSET        18
#define SMN_0x11140280_LC_LOOK_FOR_IDLE_IN_L1L23_WIDTH         2
#define SMN_0x11140280_LC_LOOK_FOR_IDLE_IN_L1L23_MASK          0xc0000
#define SMN_0x11140280_LC_FACTOR_IN_EXT_SYNC_OFFSET            20
#define SMN_0x11140280_LC_FACTOR_IN_EXT_SYNC_WIDTH             1
#define SMN_0x11140280_LC_FACTOR_IN_EXT_SYNC_MASK              0x100000
#define SMN_0x11140280_LC_WAIT_FOR_PM_ACK_DIS_OFFSET           21
#define SMN_0x11140280_LC_WAIT_FOR_PM_ACK_DIS_WIDTH            1
#define SMN_0x11140280_LC_WAIT_FOR_PM_ACK_DIS_MASK             0x200000
#define SMN_0x11140280_LC_WAKE_FROM_L23_OFFSET                 22
#define SMN_0x11140280_LC_WAKE_FROM_L23_WIDTH                  1
#define SMN_0x11140280_LC_WAKE_FROM_L23_MASK                   0x400000
#define SMN_0x11140280_LC_L1_IMMEDIATE_ACK_OFFSET              23
#define SMN_0x11140280_LC_L1_IMMEDIATE_ACK_WIDTH               1
#define SMN_0x11140280_LC_L1_IMMEDIATE_ACK_MASK                0x800000
#define SMN_0x11140280_LC_ASPM_TO_L1_DIS_OFFSET                24
#define SMN_0x11140280_LC_ASPM_TO_L1_DIS_WIDTH                 1
#define SMN_0x11140280_LC_ASPM_TO_L1_DIS_MASK                  0x1000000
#define SMN_0x11140280_LC_DELAY_COUNT_OFFSET                   25
#define SMN_0x11140280_LC_DELAY_COUNT_WIDTH                    2
#define SMN_0x11140280_LC_DELAY_COUNT_MASK                     0x6000000
#define SMN_0x11140280_LC_DELAY_L0S_EXIT_OFFSET                27
#define SMN_0x11140280_LC_DELAY_L0S_EXIT_WIDTH                 1
#define SMN_0x11140280_LC_DELAY_L0S_EXIT_MASK                  0x8000000
#define SMN_0x11140280_LC_DELAY_L1_EXIT_OFFSET                 28
#define SMN_0x11140280_LC_DELAY_L1_EXIT_WIDTH                  1
#define SMN_0x11140280_LC_DELAY_L1_EXIT_MASK                   0x10000000
#define SMN_0x11140280_LC_EXTEND_WAIT_FOR_EL_IDLE_OFFSET       29
#define SMN_0x11140280_LC_EXTEND_WAIT_FOR_EL_IDLE_WIDTH        1
#define SMN_0x11140280_LC_EXTEND_WAIT_FOR_EL_IDLE_MASK         0x20000000
#define SMN_0x11140280_LC_ESCAPE_L1L23_EN_OFFSET               30
#define SMN_0x11140280_LC_ESCAPE_L1L23_EN_WIDTH                1
#define SMN_0x11140280_LC_ESCAPE_L1L23_EN_MASK                 0x40000000
#define SMN_0x11140280_LC_GATE_RCVR_IDLE_OFFSET                31
#define SMN_0x11140280_LC_GATE_RCVR_IDLE_WIDTH                 1
#define SMN_0x11140280_LC_GATE_RCVR_IDLE_MASK                  0x80000000L

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
} SMN_0x11140280_STRUCT;

// Address
#define PCIE0_LC_LINK_WIDTH_CNTL_ADDRESS                        0x11140288

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

// Register Name PCIE_LC_SPEED_CNTL

// Address
#define PCIE_LC_SPEED_CNTL_ADDRESS                                           0x11140290

// Field Definitions
#define PCIE_LC_SPEED_CNTL_LC_GEN2_EN_STRAP_OFFSET                           0
#define PCIE_LC_SPEED_CNTL_LC_GEN2_EN_STRAP_WIDTH                            1
#define PCIE_LC_SPEED_CNTL_LC_GEN2_EN_STRAP_MASK                             0x1
#define PCIE_LC_SPEED_CNTL_LC_GEN3_EN_STRAP_OFFSET                           1
#define PCIE_LC_SPEED_CNTL_LC_GEN3_EN_STRAP_WIDTH                            1
#define PCIE_LC_SPEED_CNTL_LC_GEN3_EN_STRAP_MASK                             0x2
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_EN_OFFSET           2
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_EN_WIDTH            1
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_EN_MASK             0x4
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_OFFSET              3
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_WIDTH               2
#define PCIE_LC_SPEED_CNTL_LC_TARGET_LINK_SPEED_OVERRIDE_MASK                0x18
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_SW_SPEED_CHANGE_OFFSET                5
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_SW_SPEED_CHANGE_WIDTH                 1
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_SW_SPEED_CHANGE_MASK                  0x20
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_SW_SPEED_CHANGE_OFFSET               6
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_SW_SPEED_CHANGE_WIDTH                1
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_SW_SPEED_CHANGE_MASK                 0x40
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_HW_SPEED_CHANGE_OFFSET                7
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_HW_SPEED_CHANGE_WIDTH                 1
#define PCIE_LC_SPEED_CNTL_LC_FORCE_EN_HW_SPEED_CHANGE_MASK                  0x80
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_HW_SPEED_CHANGE_OFFSET               8
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_HW_SPEED_CHANGE_WIDTH                1
#define PCIE_LC_SPEED_CNTL_LC_FORCE_DIS_HW_SPEED_CHANGE_MASK                 0x100
#define PCIE_LC_SPEED_CNTL_LC_INITIATE_LINK_SPEED_CHANGE_OFFSET              9
#define PCIE_LC_SPEED_CNTL_LC_INITIATE_LINK_SPEED_CHANGE_WIDTH               1
#define PCIE_LC_SPEED_CNTL_LC_INITIATE_LINK_SPEED_CHANGE_MASK                0x200
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_OFFSET           10
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_WIDTH            2
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK             0xc00
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPT_FAILED_OFFSET             12
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPT_FAILED_WIDTH              1
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_ATTEMPT_FAILED_MASK               0x1000
#define PCIE_LC_SPEED_CNTL_LC_CURRENT_DATA_RATE_OFFSET                       13
#define PCIE_LC_SPEED_CNTL_LC_CURRENT_DATA_RATE_WIDTH                        2
#define PCIE_LC_SPEED_CNTL_LC_CURRENT_DATA_RATE_MASK                         0x6000
#define PCIE_LC_SPEED_CNTL_LC_DONT_CLR_TARGET_SPD_CHANGE_STATUS_OFFSET       15
#define PCIE_LC_SPEED_CNTL_LC_DONT_CLR_TARGET_SPD_CHANGE_STATUS_WIDTH        1
#define PCIE_LC_SPEED_CNTL_LC_DONT_CLR_TARGET_SPD_CHANGE_STATUS_MASK         0x8000
#define PCIE_LC_SPEED_CNTL_LC_CLR_FAILED_SPD_CHANGE_CNT_OFFSET               16
#define PCIE_LC_SPEED_CNTL_LC_CLR_FAILED_SPD_CHANGE_CNT_WIDTH                1
#define PCIE_LC_SPEED_CNTL_LC_CLR_FAILED_SPD_CHANGE_CNT_MASK                 0x10000
#define PCIE_LC_SPEED_CNTL_LC_1_OR_MORE_TS2_SPEED_ARC_EN_OFFSET              17
#define PCIE_LC_SPEED_CNTL_LC_1_OR_MORE_TS2_SPEED_ARC_EN_WIDTH               1
#define PCIE_LC_SPEED_CNTL_LC_1_OR_MORE_TS2_SPEED_ARC_EN_MASK                0x20000
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN2_OFFSET               18
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN2_WIDTH                1
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN2_MASK                 0x40000
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN2_OFFSET                19
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN2_WIDTH                 1
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN2_MASK                  0x80000
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN3_OFFSET               20
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN3_WIDTH                1
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_EVER_SENT_GEN3_MASK                 0x100000
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN3_OFFSET                21
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN3_WIDTH                 1
#define PCIE_LC_SPEED_CNTL_LC_OTHER_SIDE_SUPPORTS_GEN3_MASK                  0x200000
#define PCIE_LC_SPEED_CNTL_LC_AUTO_RECOVERY_DIS_OFFSET                       22
#define PCIE_LC_SPEED_CNTL_LC_AUTO_RECOVERY_DIS_WIDTH                        1
#define PCIE_LC_SPEED_CNTL_LC_AUTO_RECOVERY_DIS_MASK                         0x400000
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_STATUS_OFFSET                     23
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_STATUS_WIDTH                      1
#define PCIE_LC_SPEED_CNTL_LC_SPEED_CHANGE_STATUS_MASK                       0x800000
#define PCIE_LC_SPEED_CNTL_LC_DATA_RATE_ADVERTISED_OFFSET                    24
#define PCIE_LC_SPEED_CNTL_LC_DATA_RATE_ADVERTISED_WIDTH                     2
#define PCIE_LC_SPEED_CNTL_LC_DATA_RATE_ADVERTISED_MASK                      0x3000000
#define PCIE_LC_SPEED_CNTL_LC_CHECK_DATA_RATE_OFFSET                         26
#define PCIE_LC_SPEED_CNTL_LC_CHECK_DATA_RATE_WIDTH                          1
#define PCIE_LC_SPEED_CNTL_LC_CHECK_DATA_RATE_MASK                           0x4000000
#define PCIE_LC_SPEED_CNTL_LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN_OFFSET          27
#define PCIE_LC_SPEED_CNTL_LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN_WIDTH           1
#define PCIE_LC_SPEED_CNTL_LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN_MASK            0x8000000
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L0s_EN_OFFSET                28
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L0s_EN_WIDTH                 1
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L0s_EN_MASK                  0x10000000
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L1_EN_OFFSET                 29
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L1_EN_WIDTH                  1
#define PCIE_LC_SPEED_CNTL_LC_INIT_SPEED_NEG_IN_L1_EN_MASK                   0x20000000
#define PCIE_LC_SPEED_CNTL_LC_DONT_CHECK_EQTS_IN_RCFG_OFFSET                 30
#define PCIE_LC_SPEED_CNTL_LC_DONT_CHECK_EQTS_IN_RCFG_WIDTH                  1
#define PCIE_LC_SPEED_CNTL_LC_DONT_CHECK_EQTS_IN_RCFG_MASK                   0x40000000
#define PCIE_LC_SPEED_CNTL_LC_DELAY_COEFF_UPDATE_DIS_OFFSET                  31
#define PCIE_LC_SPEED_CNTL_LC_DELAY_COEFF_UPDATE_DIS_WIDTH                   1
#define PCIE_LC_SPEED_CNTL_LC_DELAY_COEFF_UPDATE_DIS_MASK                    0x80000000L

/// PCIE_LC_SPEED_CNTL
typedef union {
  struct {
    UINT32                                        LC_GEN2_EN_STRAP:1 ; ///<
    UINT32                                        LC_GEN3_EN_STRAP:1 ; ///<
    UINT32                        LC_TARGET_LINK_SPEED_OVERRIDE_EN:1 ; ///<
    UINT32                           LC_TARGET_LINK_SPEED_OVERRIDE:2 ; ///<
    UINT32                             LC_FORCE_EN_SW_SPEED_CHANGE:1 ; ///<
    UINT32                            LC_FORCE_DIS_SW_SPEED_CHANGE:1 ; ///<
    UINT32                             LC_FORCE_EN_HW_SPEED_CHANGE:1 ; ///<
    UINT32                            LC_FORCE_DIS_HW_SPEED_CHANGE:1 ; ///<
    UINT32                           LC_INITIATE_LINK_SPEED_CHANGE:1 ; ///<
    UINT32                        LC_SPEED_CHANGE_ATTEMPTS_ALLOWED:2 ; ///<
    UINT32                          LC_SPEED_CHANGE_ATTEMPT_FAILED:1 ; ///<
    UINT32                                    LC_CURRENT_DATA_RATE:2 ; ///<
    UINT32                    LC_DONT_CLR_TARGET_SPD_CHANGE_STATUS:1 ; ///<
    UINT32                            LC_CLR_FAILED_SPD_CHANGE_CNT:1 ; ///<
    UINT32                           LC_1_OR_MORE_TS2_SPEED_ARC_EN:1 ; ///<
    UINT32                            LC_OTHER_SIDE_EVER_SENT_GEN2:1 ; ///<
    UINT32                             LC_OTHER_SIDE_SUPPORTS_GEN2:1 ; ///<
    UINT32                            LC_OTHER_SIDE_EVER_SENT_GEN3:1 ; ///<
    UINT32                             LC_OTHER_SIDE_SUPPORTS_GEN3:1 ; ///<
    UINT32                                    LC_AUTO_RECOVERY_DIS:1 ; ///<
    UINT32                                  LC_SPEED_CHANGE_STATUS:1 ; ///<
    UINT32                                 LC_DATA_RATE_ADVERTISED:2 ; ///<
    UINT32                                      LC_CHECK_DATA_RATE:1 ; ///<
    UINT32                       LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN:1 ; ///<
    UINT32                             LC_INIT_SPEED_NEG_IN_L0s_EN:1 ; ///<
    UINT32                              LC_INIT_SPEED_NEG_IN_L1_EN:1 ; ///<
    UINT32                              LC_DONT_CHECK_EQTS_IN_RCFG:1 ; ///<
    UINT32                               LC_DELAY_COEFF_UPDATE_DIS:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_SPEED_CNTL_STRUCT;


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

// Register Name PCIE_LC_CNTL2

// Address
#define PCIE0_PCIE_LC_CNTL2_ADDRESS                                      0x111402c4

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

// Address
#define PCIE0_LC_CNTL6_ADDRESS                                 0x111402ec

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



#define RCC_DEV0_EPF1_STRAP3_ADDRESS                           0x1013420c
#define RCC_DEV0_EPF5_STRAP13_ADDRESS                          0x10134a34


// Address
#define RCC_DEV0_EPF0_STRAP3_ADDRESS                           0x1013400c

#define STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F0_OFFSET                0
#define STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F0_WIDTH                 1
#define STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F0_MASK                0x1
#define STRAP_PWR_EN_DEV0_F0_OFFSET                                    1
#define STRAP_PWR_EN_DEV0_F0_WIDTH                                     1
#define STRAP_PWR_EN_DEV0_F0_MASK                                    0x2
#define STRAP_SUBSYS_ID_DEV0_F0_OFFSET                                 2
#define STRAP_SUBSYS_ID_DEV0_F0_WIDTH                                 16
#define STRAP_SUBSYS_ID_DEV0_F0_MASK                             0x3FFFC
#define STRAP_MSI_EN_DEV0_F0_OFFSET                                   18
#define STRAP_MSI_EN_DEV0_F0_WIDTH                                     1
#define STRAP_MSI_EN_DEV0_F0_MASK                                0x40000
#define STRAP_MSI_CLR_PENDING_EN_DEV0_F0_OFFSET                       19
#define STRAP_MSI_CLR_PENDING_EN_DEV0_F0_WIDTH                         1
#define STRAP_MSI_CLR_PENDING_EN_DEV0_F0_MASK                    0x80000
#define STRAP_MSIX_EN_DEV0_F0_OFFSET                                  20
#define STRAP_MSIX_EN_DEV0_F0_WIDTH                                    1
#define STRAP_MSIX_EN_DEV0_F0_MASK                              0x100000
#define STRAP_MSIX_TABLE_BIR_DEV0_F0_OFFSET                           21
#define STRAP_MSIX_TABLE_BIR_DEV0_F0_WIDTH                             3
#define STRAP_MSIX_TABLE_BIR_DEV0_F0_MASK                       0xE00000
#define STRAP_PMC_DSI_DEV0_F0_OFFSET                                  24
#define STRAP_PMC_DSI_DEV0_F0_WIDTH                                    1
#define STRAP_PMC_DSI_DEV0_F0_MASK                             0x1000000
#define STRAP_VENDOR_ID_BIT_DEV0_F0_OFFSET                            25
#define STRAP_VENDOR_ID_BIT_DEV0_F0_WIDTH                              1
#define STRAP_VENDOR_ID_BIT_DEV0_F0_MASK                       0x2000000
#define STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F0_OFFSET                 26
#define STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F0_WIDTH                   1
#define STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F0_MASK            0x4000000
#define STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F0_OFFSET                27
#define STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F0_WIDTH                  1
#define STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F0_MASK           0x8000000
#define Reserved_28_31_OFFSET                                         28
#define Reserved_28_31_WIDTH                                           4
#define Reserved_28_31_MASK                                   0xF0000000

/// RCC_DEV0_EPF0_STRAP3
typedef union {
  struct {
    UINT32                   STRAP_POISONED_ADVISORY_NONFATAL_DEV0_F0:1 ; ///<
    UINT32                                       STRAP_PWR_EN_DEV0_F0:1 ; ///<
    UINT32                                   STRAP_SUBSYS_ID_DEV0_F0:16 ; ///<
    UINT32                                       STRAP_MSI_EN_DEV0_F0:1 ; ///<
    UINT32                           STRAP_MSI_CLR_PENDING_EN_DEV0_F0:1 ; ///<
    UINT32                                      STRAP_MSIX_EN_DEV0_F0:1 ; ///<
    UINT32                               STRAP_MSIX_TABLE_BIR_DEV0_F0:3 ; ///<
    UINT32                                      STRAP_PMC_DSI_DEV0_F0:1 ; ///<
    UINT32                                STRAP_VENDOR_ID_BIT_DEV0_F0:1 ; ///<
    UINT32                     STRAP_ALL_MSI_EVENT_SUPPORT_EN_DEV0_F0:1 ; ///<
    UINT32                    STRAP_SMN_ERR_STATUS_MASK_EN_EP_DEV0_F0:1 ; ///<
    UINT32                                             Reserved_28_31:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_EPF0_STRAP3_STRUCT;


// Address
#define RCC_DEV0_EPF0_STRAP13_ADDRESS                          0x101234c4

#define STRAP_CLASS_CODE_PIF_DEV0_F0_OFFSET                             0
#define STRAP_CLASS_CODE_PIF_DEV0_F0_WIDTH                              8
#define STRAP_CLASS_CODE_PIF_DEV0_F0_MASK                            0xFF
#define STRAP_CLASS_CODE_SUB_DEV0_F0_OFFSET                             8
#define STRAP_CLASS_CODE_SUB_DEV0_F0_WIDTH                              8
#define STRAP_CLASS_CODE_SUB_DEV0_F0_MASK                          0xFF00
#define STRAP_CLASS_CODE_BASE_DEV0_F0_OFFSET                           16
#define STRAP_CLASS_CODE_BASE_DEV0_F0_WIDTH                             8
#define STRAP_CLASS_CODE_BASE_DEV0_F0_MASK                       0xFF0000
#define Reserved_24_31_OFFSET                                          24
#define Reserved_24_31_WIDTH                                            8
#define Reserved_24_31_MASK                                    0xFF000000

/// RCC_DEV0_EPF0_STRAP13
typedef union {
  struct {
    UINT32                               STRAP_CLASS_CODE_PIF_DEV0_F0:8 ; ///<
    UINT32                               STRAP_CLASS_CODE_SUB_DEV0_F0:8 ; ///<
    UINT32                              STRAP_CLASS_CODE_BASE_DEV0_F0:8 ; ///<
    UINT32                                             Reserved_24_31:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} RCC_DEV0_EPF0_STRAP13_STRUCT;


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


#define SMN_BIFC_MISC_CTL_REG_ADDRESS                          0x1013a010

// Type
#define SMN_BIFC_MISC_CTL_REG_TYPE                             TYPE_SMN

#define MISC_CNTRL_REG_VWIRE_TARG_UNITID_CHECK_EN_OFFSET       0
#define MISC_CNTRL_REG_VWIRE_TARG_UNITID_CHECK_EN_WIDTH        1
#define MISC_CNTRL_REG_VWIRE_TARG_UNITID_CHECK_EN_MASK         0x1
#define MISC_CNTRL_VWIRE_SRC_UNITID_CHECK_EN_OFFSET            1
#define MISC_CNTRL_VWIRE_SRC_UNITID_CHECK_EN_WIDTH             2
#define MISC_CNTRL_VWIRE_SRC_UNITID_CHECK_EN_MASK              0x6
#define Reserved1_OFFSET                                       3
#define Reserved1_WIDTH                                        5
#define Reserved1_MASK                                         0xF8
#define MISC_CNTRL_REG_DMA_CHAIN_BREAK_IN_RCMODE_OFFSET        8
#define MISC_CNTRL_REG_DMA_CHAIN_BREAK_IN_RCMODE_WIDTH         1
#define MISC_CNTRL_REG_DMA_CHAIN_BREAK_IN_RCMODE_MASK          0x100
#define MISC_CNTRL_REG_HST_ARB_CHAIN_LOCK_OFFSET               9
#define MISC_CNTRL_REG_HST_ARB_CHAIN_LOCK_WIDTH                1
#define MISC_CNTRL_REG_HST_ARB_CHAIN_LOCK_MASK                 0x200
#define MISC_CNTRL_REG_GSI_SST_ARB_CHAIN_LOCK_OFFSET           10
#define MISC_CNTRL_REG_GSI_SST_ARB_CHAIN_LOCK_WIDTH            1
#define MISC_CNTRL_REG_GSI_SST_ARB_CHAIN_LOCK_MASK             0x400
#define Reserved2_OFFSET                                       11
#define Reserved2_WIDTH                                        5
#define Reserved2_MASK                                         0xF800
#define MISC_CNTRL_REG_DMA_ATOMIC_LENGTH_CHK_DIS_OFFSET        16
#define MISC_CNTRL_REG_DMA_ATOMIC_LENGTH_CHK_DIS_WIDTH         1
#define MISC_CNTRL_REG_DMA_ATOMIC_LENGTH_CHK_DIS_MASK          0x10000
#define MISC_CNTRL_REG_DMA_ATOMIC_FAILED_STS_SEL_OFFSET        17
#define MISC_CNTRL_REG_DMA_ATOMIC_FAILED_STS_SEL_WIDTH         1
#define MISC_CNTRL_REG_DMA_ATOMIC_FAILED_STS_SEL_MASK          0x20000
#define MISC_CNTRL_REG_DMA_FORCE_VF_AS_PF_SRIOIVEN_LOW_OFFSET  18
#define MISC_CNTRL_REG_DMA_FORCE_VF_AS_PF_SRIOIVEN_LOW_WIDTH   1
#define MISC_CNTRL_REG_DMA_FORCE_VF_AS_PF_SRIOIVEN_LOW_MASK    0x40000
#define MISC_CNTRL_REG_DMA_ADDR_KEEP_PH_OFFSET                 19
#define MISC_CNTRL_REG_DMA_ADDR_KEEP_PH_WIDTH                  1
#define MISC_CNTRL_REG_DMA_ADDR_KEEP_PH_MASK                   0x80000
#define MISC_CNTRL_REG_RCC_GMI_TD_FORCE_ZERO_OFFSET            20
#define MISC_CNTRL_REG_RCC_GMI_TD_FORCE_ZERO_WIDTH             1
#define MISC_CNTRL_REG_RCC_GMI_TD_FORCE_ZERO_MASK              0x100000
#define Reserved3_OFFSET                                       21
#define Reserved3_WIDTH                                        3
#define Reserved3_MASK                                         0xE00000
#define MISC_CNTRL_REG_PCIE_CAPABILITY_PROT_DIS_OFFSET         24
#define MISC_CNTRL_REG_PCIE_CAPABILITY_PROT_DIS_WIDTH          1
#define MISC_CNTRL_REG_PCIE_CAPABILITY_PROT_DIS_MASK           0x1000000
#define MISC_CNTRL_REG_VC7_DMA_IOCFG_DIS_OFFSET                25
#define MISC_CNTRL_REG_VC7_DMA_IOCFG_DIS_WIDTH                 1
#define MISC_CNTRL_REG_VC7_DMA_IOCFG_DIS_MASK                  0x2000000
#define MISC_CNTRL_REG_DMA_2ND_REQ_DIS_OFFSET                  26
#define MISC_CNTRL_REG_DMA_2ND_REQ_DIS_WIDTH                   1
#define MISC_CNTRL_REG_DMA_2ND_REQ_DIS_MASK                    0x4000000
#define MISC_CNTRL_REG_PORT_DSTATE_BYPASS_MODE_OFFSET          27
#define MISC_CNTRL_REG_PORT_DSTATE_BYPASS_MODE_WIDTH           1
#define MISC_CNTRL_REG_PORT_DSTATE_BYPASS_MODE_MASK            0x8000000
#define MISC_CNTRL_REG_PME_TURNOFF_MODE_OFFSET                 28
#define MISC_CNTRL_REG_PME_TURNOFF_MODE_WIDTH                  1
#define MISC_CNTRL_REG_PME_TURNOFF_MODE_MASK                   0x10000000
#define Reserved4_OFFSET                                       29
#define Reserved4_WIDTH                                        2
#define Reserved4_MASK                                         0x60000000
#define MISC_CNTRL_REG_PCIESWUS_SELECTION_OFFSET               31
#define MISC_CNTRL_REG_PCIESWUS_SELECTION_WIDTH                1
#define MISC_CNTRL_REG_PCIESWUS_SELECTION_MASK                 0x80000000

typedef union {
  struct {
    UINT32                                             Vwire_Targ_Unitid_Check_En:1 ; ///<
    UINT32                                              Vwire_Src_Unitid_Check_En:2 ; ///<
    UINT32                                                              Reserved1:5 ; ///<
    UINT32                                              Dma_Chain_Break_In_Rcmode:1 ; ///<
    UINT32                                                     Hst_Arb_Chain_Lock:1 ; ///<
    UINT32                                                 Gsi_Sst_Arb_Chain_Lock:1 ; ///<
    UINT32                                                              Reserved2:5 ; ///<
    UINT32                                              Dma_Atomic_Length_Chk_Dis:1 ; ///<
    UINT32                                              Dma_Atomic_Failed_Sts_Sel:1 ; ///<
    UINT32                                        Dma_Force_Vf_As_Pf_Srioiven_Low:1 ; ///<
    UINT32                                                       Dma_Addr_Keep_Ph:1 ; ///<
    UINT32                                                  Rcc_Gmi_Td_Force_Zero:1 ; ///<
    UINT32                                                              Reserved3:3 ; ///<
    UINT32                                               Pcie_Capability_Prot_Dis:1 ; ///<
    UINT32                                                      Vc7_Dma_Iocfg_Dis:1 ; ///<
    UINT32                                                        Dma_2nd_Req_Dis:1 ; ///<
    UINT32                                                Port_Dstate_Bypass_Mode:1 ; ///<
    UINT32                                                       Pme_Turnoff_Mode:1 ; ///<
    UINT32                                                              Reserved4:2 ; ///<
    UINT32                                                     Pcieswus_Selection:1 ; ///<
  } Field;                                                             ///<
} SMN_0x1013a010_STRUCT;

///  PGMST_CTRL_STRUCT
// Address
#define NBIF_PGMST_CTRL_ADDRESS                          0x1013a0e0
// Type
#define NBIF_PGMST_CTRL_Type                               TYPE_SMN

#define NBIF_CFG_PG_HYSTERESIS_OFFSET                             0
#define NBIF_CFG_PG_HYSTERESIS_WIDTH                              8
#define NBIF_CFG_PG_HYSTERESIS_MASK                            0xFF
#define NBIF_CFG_PG_EN_OFFSET                                     8
#define NBIF_CFG_PG_EN_WIDTH                                      1
#define NBIF_CFG_PG_EN_MASK                                   0x100
#define Reserved_9_OFFSET                                         9
#define Reserved_9_WIDTH                                          1
#define Reserved_9_MASK                                       0x200
#define NBIF_CFG_IDLENESS_COUNT_EN_OFFSET                        10
#define NBIF_CFG_IDLENESS_COUNT_EN_WIDTH                          4
#define NBIF_CFG_IDLENESS_COUNT_EN_MASK                      0x3C00
#define NBIF_CFG_FW_PG_EXIT_EN_OFFSET                            14
#define NBIF_CFG_FW_PG_EXIT_EN_WIDTH                              2
#define NBIF_CFG_FW_PG_EXIT_EN_MASK                          0xC000
#define Reserved_16_31_OFFSET                                    16
#define Reserved_16_31_WIDTH                                     16
#define Reserved_16_31_MASK                              0xFFFF0000

typedef union {
  struct {
    UINT32                               NBIF_CFG_PG_HYSTERESIS:8 ; ///<
    UINT32                                       NBIF_CFG_PG_EN:1 ; ///<
    UINT32                                           Reserved_9:1 ; ///<
    UINT32                           NBIF_CFG_IDLENESS_COUNT_EN:4 ; ///<
    UINT32                               NBIF_CFG_FW_PG_EXIT_EN:2 ; ///<
    UINT32                                      Reserved_16_31:16 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PGMST_CTRL_STRUCT;

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
#define NBMISC_0068_UPPER_TOM2_WIDTH                           8
#define NBMISC_0068_UPPER_TOM2_MASK                            0xff

/// NBMISC_0068
typedef union {
  struct {
    UINT32                                              UPPER_TOM2:8 ; ///<
    UINT32                                           Reserved_32_8:24; ///<
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
#define IOHC_GLUE_CG_LCLK_CTRL_0_ADDRESS                       0x13b10088 //0x88

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
#define IOHC_GLUE_CG_LCLK_CTRL_1_ADDRESS                       0x13B1008c //0x8c

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

///  IOHC_PGMST_CTRL_STRUCT
// Address
#define IOHC_PGMST_CTRL_ADDRESS                               0x13b10340
// Type
#define IOHC_PGMST_CTRL_Type                                    TYPE_SMN


#define IOHC_CFG_PG_HYSTERESIS_OFFSET                                  0
#define IOHC_CFG_PG_HYSTERESIS_WIDTH                                   8
#define IOHC_CFG_PG_HYSTERESIS_MASK                                 0xFF
#define IOHC_CFG_PG_EN_OFFSET                                          8
#define IOHC_CFG_PG_EN_WIDTH                                           1
#define IOHC_CFG_PG_EN_MASK                                        0x100
#define IOHC_Reserved_9_OFFSET                                         9
#define IOHC_Reserved_9_WIDTH                                          1
#define IOHC_Reserved_9_MASK                                       0x200
#define IOHC_CFG_IDLENESS_COUNT_EN_OFFSET                             10
#define IOHC_CFG_IDLENESS_COUNT_EN_WIDTH                               4
#define IOHC_CFG_IDLENESS_COUNT_EN_MASK                           0x3C00
#define IOHC_CFG_FW_PG_EXIT_EN_OFFSET                                 14
#define IOHC_CFG_FW_PG_EXIT_EN_WIDTH                                   2
#define IOHC_CFG_FW_PG_EXIT_EN_MASK                               0xC000
#define IOHC_Reserved_16_31_OFFSET                                    16
#define IOHC_Reserved_16_31_WIDTH                                     16
#define IOHC_Reserved_16_31_MASK                              0xFFFF0000

typedef union {
  struct {
    UINT32                               IOHC_CFG_PG_HYSTERESIS:8 ; ///<
    UINT32                                       IOHC_CFG_PG_EN:1 ; ///<
    UINT32                                           Reserved_9:1 ; ///<
    UINT32                           IOHC_CFG_IDLENESS_COUNT_EN:4 ; ///<
    UINT32                               IOHC_CFG_FW_PG_EXIT_EN:2 ; ///<
    UINT32                                      Reserved_16_31:16 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOHC_PGMST_CTRL_STRUCT;


///  IOHC_MISC_PGMST_CTRL_STRUCT
// Address
#define IOHC_MISC_PGMST_CTRL_ADDRESS                          0x13B10344
// Type
#define IOHC_MISC_PGMST_CTRL_Type                               TYPE_SMN

#define IOHC_MISC_PORT_DISCONNECT_HYSTERESIS_OFFSET                    0
#define IOHC_MISC_PORT_DISCONNECT_HYSTERESIS_WIDTH                     6
#define IOHC_MISC_PORT_DISCONNECT_HYSTERESIS_MASK                   0x3F
#define IOHC_MISC_SDF_PORT_DISCONNECT_REAL_TIME_HYSTERESIS_OFFSET      6
#define IOHC_MISC_SDF_PORT_DISCONNECT_REAL_TIME_HYSTERESIS_WIDTH       6
#define IOHC_MISC_SDF_PORT_DISCONNECT_REAL_TIME_HYSTERESIS_MASK    0xFC0
#define IOHC_MISC_RESERVED_12_14_OFFSET                               12
#define IOHC_MISC_RESERVED_12_14_WIDTH                                 3
#define IOHC_MISC_RESERVED_12_14_MASK                             0x7000
#define IOHC_MISC_DMA_ENABLE_EARLY_CLKREQ_OFFSET                      15
#define IOHC_MISC_DMA_ENABLE_EARLY_CLKREQ_WIDTH                        1
#define IOHC_MISC_DMA_ENABLE_EARLY_CLKREQ_MASK                    0x8000
#define IOHC_MISC_HOST_ENABLE_EARLY_CLKREQ_OFFSET                     16
#define IOHC_MISC_HOST_ENABLE_EARLY_CLKREQ_WIDTH                      16
#define IOHC_MISC_HOST_ENABLE_EARLY_CLKREQ_MASK               0xFFFF0000

typedef union {
  struct {
    UINT32                           Port_Disconnect_Hysteresis:6 ; ///<
    UINT32             SDF_Port_Disconnect_Real_Time_Hysteresis:6 ; ///<
    UINT32                                       Reserved_12_14:3 ; ///<
    UINT32                                 DMAEnableEarlyClkReq:1 ; ///<
    UINT32                               HostEnableEarlyClkReq:16 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOHC_MISC_PGMST_CTRL_STRUCT;


//
// Register Name SB_DEVICE_CNTL2
//
#define SMN_SB_DEVICE_CNTL2_ADDRESS                            0x13b14034UL


//
// Register Name IOHC_QOS_CONTROL
//
#define SMN_IOHC_QOS_CONTROL_ADDRESS                           0x13b14040UL

//
// IOHC_QOS_CONTROL Register Bitfields:
//

/// Bitfield Description : VC0QoSPriority.
#define IOHC_QOS_CONTROL_VC0QoSPriority_OFFSET                 0
#define IOHC_QOS_CONTROL_VC0QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC0QoSPriority_MASK                   0xf

/// Bitfield Description : VC1QoSPriority.
#define IOHC_QOS_CONTROL_VC1QoSPriority_OFFSET                 4
#define IOHC_QOS_CONTROL_VC1QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC1QoSPriority_MASK                   0xf0

/// Bitfield Description : VC2QoSPriority.
#define IOHC_QOS_CONTROL_VC2QoSPriority_OFFSET                 8
#define IOHC_QOS_CONTROL_VC2QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC2QoSPriority_MASK                   0xf00

/// Bitfield Description : VC3QoSPriority.
#define IOHC_QOS_CONTROL_VC3QoSPriority_OFFSET                 12
#define IOHC_QOS_CONTROL_VC3QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC3QoSPriority_MASK                   0xf000

/// Bitfield Description : VC4QoSPriority.
#define IOHC_QOS_CONTROL_VC4QoSPriority_OFFSET                 16
#define IOHC_QOS_CONTROL_VC4QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC4QoSPriority_MASK                   0xf0000

/// Bitfield Description : VC5QoSPriority.
#define IOHC_QOS_CONTROL_VC5QoSPriority_OFFSET                 20
#define IOHC_QOS_CONTROL_VC5QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC5QoSPriority_MASK                   0xf00000

/// Bitfield Description : VC6QoSPriority.
#define IOHC_QOS_CONTROL_VC6QoSPriority_OFFSET                 24
#define IOHC_QOS_CONTROL_VC6QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC6QoSPriority_MASK                   0xf000000

/// Bitfield Description : VC7QoSPriority.
#define IOHC_QOS_CONTROL_VC7QoSPriority_OFFSET                 28
#define IOHC_QOS_CONTROL_VC7QoSPriority_WIDTH                  4
#define IOHC_QOS_CONTROL_VC7QoSPriority_MASK                   0xf0000000L

typedef union {
  struct {
    UINT32                                          VC0QoSPriority:4 ; ///<
    UINT32                                          VC1QoSPriority:4 ; ///<
    UINT32                                          VC2QoSPriority:4 ; ///<
    UINT32                                          VC3QoSPriority:4 ; ///<
    UINT32                                          VC4QoSPriority:4 ; ///<
    UINT32                                          VC5QoSPriority:4 ; ///<
    UINT32                                          VC6QoSPriority:4 ; ///<
    UINT32                                          VC7QoSPriority:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOHC_QOS_CONTROL_STRUCT;

//
// Register Name USB_QoS_CNTL
//
#define SMN_USB_QoS_CNTL_ADDRESS                               0x13b14044UL

//
// USB_QoS_CNTL Register Bitfields:
//

/// Bitfield Description : UnitID to set QoSPriority
#define USB_QoS_CNTL_UnitID0_OFFSET                            0
#define USB_QoS_CNTL_UnitID0_WIDTH                             7
#define USB_QoS_CNTL_UnitID0_MASK                              0x7f

/// Bitfield Description :
#define USB_QoS_CNTL_Reserved_7_7_OFFSET                       7
#define USB_QoS_CNTL_Reserved_7_7_WIDTH                        1
#define USB_QoS_CNTL_Reserved_7_7_MASK                         0x80

/// Bitfield Description : QoSPriority to set for UnitID0
#define USB_QoS_CNTL_UnitID0QoSPriority_OFFSET                 8
#define USB_QoS_CNTL_UnitID0QoSPriority_WIDTH                  4
#define USB_QoS_CNTL_UnitID0QoSPriority_MASK                   0xf00

/// Bitfield Description : Enable UnitIDQoSPrioty setting for UnitID0
#define USB_QoS_CNTL_UnitID0Enable_OFFSET                      12
#define USB_QoS_CNTL_UnitID0Enable_WIDTH                       1
#define USB_QoS_CNTL_UnitID0Enable_MASK                        0x1000

/// Bitfield Description :
#define USB_QoS_CNTL_Reserved_15_13_OFFSET                     13
#define USB_QoS_CNTL_Reserved_15_13_WIDTH                      3
#define USB_QoS_CNTL_Reserved_15_13_MASK                       0xe000

/// Bitfield Description : UnitID to set QoSPriority
#define USB_QoS_CNTL_UnitID1_OFFSET                            16
#define USB_QoS_CNTL_UnitID1_WIDTH                             7
#define USB_QoS_CNTL_UnitID1_MASK                              0x7f0000

/// Bitfield Description :
#define USB_QoS_CNTL_Reserved_23_23_OFFSET                     23
#define USB_QoS_CNTL_Reserved_23_23_WIDTH                      1
#define USB_QoS_CNTL_Reserved_23_23_MASK                       0x800000

/// Bitfield Description : QoSPriority to set for UnitID1
#define USB_QoS_CNTL_UnitID1QoSPriority_OFFSET                 24
#define USB_QoS_CNTL_UnitID1QoSPriority_WIDTH                  4
#define USB_QoS_CNTL_UnitID1QoSPriority_MASK                   0xf000000

/// Bitfield Description : Enable UnitIDQoSPrioty setting for UnitID1
#define USB_QoS_CNTL_UnitID1Enable_OFFSET                      28
#define USB_QoS_CNTL_UnitID1Enable_WIDTH                       1
#define USB_QoS_CNTL_UnitID1Enable_MASK                        0x10000000

/// Bitfield Description :
#define USB_QoS_CNTL_Reserved_31_29_OFFSET                     29
#define USB_QoS_CNTL_Reserved_31_29_WIDTH                      3
#define USB_QoS_CNTL_Reserved_31_29_MASK                       0xe0000000L

typedef union {
  struct {
    UINT32                                                 UnitID0:7 ; ///<
    UINT32                                            Reserved_7_7:1 ; ///<
    UINT32                                      UnitID0QoSPriority:4 ; ///<
    UINT32                                           UnitID0Enable:1 ; ///<
    UINT32                                          Reserved_15_13:3 ; ///<
    UINT32                                                 UnitID1:7 ; ///<
    UINT32                                          Reserved_23_23:1 ; ///<
    UINT32                                      UnitID1QoSPriority:4 ; ///<
    UINT32                                           UnitID1Enable:1 ; ///<
    UINT32                                          Reserved_31_29:3 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} USB_QoS_CNTL_STRUCT;





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

// Register Name IOMMU_CONTROL_W

// Address
#define IOMMU_CONTROL_W_ADDRESS                                           0x13f0007c

// Type
#define IOMMU_CONTROL_W_TYPE                                              TYPE_SMN

#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_OFFSET                            0
#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_WIDTH                             3
#define IOMMU_CONTROL_W_INTERRUPT_PIN_W_MASK                              0x7


//IOMMU_L2:IOMMU_MMIO_CONTROL1_W
// Address
#define IOMMU_MMIO_CONTROL1_W_ADDRESS                         0x13f00084
// Type
#define IOMMU_MMIO_CONTROL1_W_TYPE                            TYPE_SMN

#define PAS_MAX_W_OFFSET                                               0
#define PAS_MAX_W_Width                                                4
#define PAS_MAX_W_Mask                                               0xf
#define IOMMU_MMIO_CONTROL1_Reserved1_OFFSET                           4
#define IOMMU_MMIO_CONTROL1_Reserved1_Width                            2
#define IOMMU_MMIO_CONTROL1_Reserved1_Mask                          0x30
#define DTE_seg_W_OFFSET                                               6
#define DTE_seg_W_Width                                                2
#define DTE_seg_W_Mask                                              0xc0
#define PPR_OVERFLOW_EARLY_SUP_W_OFFSET                                8
#define PPR_OVERFLOW_EARLY_SUP_W_Width                                 1
#define PPR_OVERFLOW_EARLY_SUP_W_Mask                              0x100
#define PPR_AUTORESP_SUP_W_OFFSET                                      9
#define PPR_AUTORESP_SUP_W_Width                                       1
#define PPR_AUTORESP_SUP_W_Mask                                    0x200
#define BLOCK_STOPMARK_SUP_W_OFFSET                                   10
#define BLOCK_STOPMARK_SUP_W_Width                                     1
#define BLOCK_STOPMARK_SUP_W_Mask                                  0x400
#define MARCnum_SUP_W_OFFSET                                          11
#define MARCnum_SUP_W_Width                                            2
#define MARCnum_SUP_W_Mask                                        0x1800
#define SNOOP_ATTRS_SUP_W_OFFSET                                      13
#define SNOOP_ATTRS_SUP_W_Width                                        1
#define SNOOP_ATTRS_SUP_W_Mask                                    0x2000
#define GIo_SUP_W_OFFSET                                              14
#define GIo_SUP_W_Width                                                1
#define GIo_SUP_W_Mask                                            0x4000
#define HA_SUP_W_OFFSET                                               15
#define HA_SUP_W_Width                                                 1
#define HA_SUP_W_Mask                                             0x8000
#define EPH_SUP_W_OFFSET                                              16
#define EPH_SUP_W_Width                                                1
#define EPH_SUP_W_Mask                                           0x10000
#define ATTRFW_SUP_W_OFFSET                                           17
#define ATTRFW_SUP_W_Width                                             1
#define ATTRFW_SUP_W_Mask                                        0x20000
#define V2_HD_DIS_SUP_W_OFFSET                                        18
#define V2_HD_DIS_SUP_W_Width                                          1
#define V2_HD_DIS_SUP_W_Mask                                     0x40000
#define InvIotlbTypeSup_W_OFFSET                                      19
#define InvIotlbTypeSup_W_Width                                        1
#define InvIotlbTypeSup_W_Mask                                   0x80000
#define HD_SUP_W_OFFSET                                               20
#define HD_SUP_W_Width                                                 1
#define HD_SUP_W_Mask                                           0x100000
#define IOMMU_MMIO_CONTROL1_Reserved_OFFSET                           21
#define IOMMU_MMIO_CONTROL1_Reserved_Width                            11
#define IOMMU_MMIO_CONTROL1_Reserved_Mask                     0xffe00000

typedef union {
   struct {
    UINT32                                                   PAS_MAX_W:4; ///<
    UINT32                                                   Reserved1:2; ///<
    UINT32                                                   DTE_seg_W:2; ///<
    UINT32                                    PPR_OVERFLOW_EARLY_SUP_W:1; ///<
    UINT32                                          PPR_AUTORESP_SUP_W:1; ///<
    UINT32                                        BLOCK_STOPMARK_SUP_W:1; ///<
    UINT32                                               MARCnum_SUP_W:2; ///<
    UINT32                                           SNOOP_ATTRS_SUP_W:1; ///<
    UINT32                                                   GIo_SUP_W:1; ///<
    UINT32                                                    HA_SUP_W:1; ///<
    UINT32                                                   EPH_SUP_W:1; ///<
    UINT32                                                ATTRFW_SUP_W:1; ///<
    UINT32                                             V2_HD_DIS_SUP_W:1; ///<
    UINT32                                           InvIotlbTypeSup_W:1; ///<
    UINT32                                                    HD_SUP_W:1; ///<
    UINT32                                                   Reserved:11; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMU_MMIO_CONTROL1_W_STRUCT;

// Register Name PCIE_CNTL

// Address
#define PCIE0_CNTL_ADDRESS                                           0x11180040

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

// Address
#define PCIE_CONFIG_CNTL_PCIECORE0_ADDRESS                     0x11180044

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
#define PCIE_CONFIG_CNTL2_ADDRESS                             0x11180070

// Type
#define PCIE_CONFIG_CNTL2_TYPE                                TYPE_SMN


#define PCIE_CTRL2_TX_ARB_ROUND_ROBIN_EN_OFFSET               0
#define PCIE_CTRL2_TX_ARB_ROUND_ROBIN_EN_WIDTH                1
#define PCIE_CTRL2_TX_ARB_ROUND_ROBIN_EN_MASK                 0x1
#define PCIE_CTRL2_TX_ARB_SLV_LIMIT_OFFSET                    1
#define PCIE_CTRL2_TX_ARB_SLV_LIMIT_WIDTH                     5
#define PCIE_CTRL2_TX_ARB_SLV_LIMIT_MASK                      0x3E
#define PCIE_CTRL2_TX_ARB_MST_LIMIT_OFFSET                    6
#define PCIE_CTRL2_TX_ARB_MST_LIMIT_WIDTH                     5
#define PCIE_CTRL2_TX_ARB_MST_LIMIT_MASK                      0x7C0
#define PCIE_CTRL2_TX_BLOCK_TLP_ON_PM_DIS_OFFSET              11
#define PCIE_CTRL2_TX_BLOCK_TLP_ON_PM_DIS_WIDTH               1
#define PCIE_CTRL2_TX_BLOCK_TLP_ON_PM_DIS_MASK                0x800
#define PCIE_CTRL2_TX_NP_MEM_WRITE_SWP_ENCODING_OFFSET        12
#define PCIE_CTRL2_TX_NP_MEM_WRITE_SWP_ENCODING_WIDTH         1
#define PCIE_CTRL2_TX_NP_MEM_WRITE_SWP_ENCODING_MASK          0x1000
#define PCIE_CTRL2_TX_ATOMIC_OPS_DISABLE_OFFSET               13
#define PCIE_CTRL2_TX_ATOMIC_OPS_DISABLE_WIDTH                1
#define PCIE_CTRL2_TX_ATOMIC_OPS_DISABLE_MASK                 0x2000
#define PCIE_CTRL2_TX_ATOMIC_ORDERING_DIS_OFFSET              14
#define PCIE_CTRL2_TX_ATOMIC_ORDERING_DIS_WIDTH               1
#define PCIE_CTRL2_TX_ATOMIC_ORDERING_DIS_MASK                0x4000
#define PCIE_CTRL2_Reserved_15_OFFSET                         15
#define PCIE_CTRL2_Reserved_15_WIDTH                          1
#define PCIE_CTRL2_Reserved_15_MASK                           0x8000
#define PCIE_CTRL2_SLV_MEM_LS_EN_OFFSET                       16
#define PCIE_CTRL2_SLV_MEM_LS_EN_WIDTH                        1
#define PCIE_CTRL2_SLV_MEM_LS_EN_MASK                         0x10000
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_LS_EN_OFFSET            17
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_LS_EN_WIDTH             1
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_LS_EN_MASK              0x20000
#define PCIE_CTRL2_MST_MEM_LS_EN_OFFSET                       18
#define PCIE_CTRL2_MST_MEM_LS_EN_WIDTH                        1
#define PCIE_CTRL2_MST_MEM_LS_EN_MASK                         0x40000
#define PCIE_CTRL2_REPLAY_MEM_LS_EN_OFFSET                    19
#define PCIE_CTRL2_REPLAY_MEM_LS_EN_WIDTH                     1
#define PCIE_CTRL2_REPLAY_MEM_LS_EN_MASK                      0x80000
#define PCIE_CTRL2_SLV_MEM_SD_EN_OFFSET                       20
#define PCIE_CTRL2_SLV_MEM_SD_EN_WIDTH                        1
#define PCIE_CTRL2_SLV_MEM_SD_EN_MASK                         0x100000
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_SD_EN_OFFSET            21
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_SD_EN_WIDTH             1
#define PCIE_CTRL2_SLV_MEM_AGGRESSIVE_SD_EN_MASK              0x200000
#define PCIE_CTRL2_MST_MEM_SD_EN_OFFSET                       22
#define PCIE_CTRL2_MST_MEM_SD_EN_WIDTH                        1
#define PCIE_CTRL2_MST_MEM_SD_EN_MASK                         0x400000
#define PCIE_CTRL2_REPLAY_MEM_SD_EN_OFFSET                    23
#define PCIE_CTRL2_REPLAY_MEM_SD_EN_WIDTH                     1
#define PCIE_CTRL2_REPLAY_MEM_SD_EN_MASK                      0x800000
#define PCIE_CTRL2_RX_NP_MEM_WRITE_ENCODING_OFFSET            24
#define PCIE_CTRL2_RX_NP_MEM_WRITE_ENCODING_WIDTH             5
#define PCIE_CTRL2_RX_NP_MEM_WRITE_ENCODING_MASK              0x1F000000
#define PCIE_CTRL2_SLV_MEM_DS_EN_OFFSET                       29
#define PCIE_CTRL2_SLV_MEM_DS_EN_WIDTH                        1
#define PCIE_CTRL2_SLV_MEM_DS_EN_MASK                         0x20000000
#define PCIE_CTRL2_MST_MEM_DS_EN_OFFSET                       30
#define PCIE_CTRL2_MST_MEM_DS_EN_WIDTH                        1
#define PCIE_CTRL2_MST_MEM_DS_EN_MASK                         0x40000000
#define PCIE_CTRL2_REPLAY_MEM_DS_EN_OFFSET                    31
#define PCIE_CTRL2_REPLAY_MEM_DS_EN_WIDTH                     1
#define PCIE_CTRL2_REPLAY_MEM_DS_EN_MASK                      0x80000000

/// PCIE_CTRL2
typedef union {
  struct {
    UINT32                                  TX_ARB_ROUND_ROBIN_EN:1 ; ///<
    UINT32                                       TX_ARB_SLV_LIMIT:5 ; ///<
    UINT32                                       TX_ARB_MST_LIMIT:5 ; ///<
    UINT32                                 TX_BLOCK_TLP_ON_PM_DIS:1 ; ///<
    UINT32                           TX_NP_MEM_WRITE_SWP_ENCODING:1 ; ///<
    UINT32                                  TX_ATOMIC_OPS_DISABLE:1 ; ///<
    UINT32                                 TX_ATOMIC_ORDERING_DIS:1 ; ///<
    UINT32                                            Reserved_15:1 ; ///<
    UINT32                                          SLV_MEM_LS_EN:1 ; ///<
    UINT32                               SLV_MEM_AGGRESSIVE_LS_EN:1 ; ///<
    UINT32                                          MST_MEM_LS_EN:1 ; ///<
    UINT32                                       REPLAY_MEM_LS_EN:1 ; ///<
    UINT32                                          SLV_MEM_SD_EN:1 ; ///<
    UINT32                               SLV_MEM_AGGRESSIVE_SD_EN:1 ; ///<
    UINT32                                          MST_MEM_SD_EN:1 ; ///<
    UINT32                                       REPLAY_MEM_SD_EN:1 ; ///<
    UINT32                               RX_NP_MEM_WRITE_ENCODING:5 ; ///<
    UINT32                                          SLV_MEM_DS_EN:1 ; ///<
    UINT32                                          MST_MEM_DS_EN:1 ; ///<
    UINT32                                       REPLAY_MEM_DS_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_CTRL2_STRUCT;


// Address
#define PCIE_CONFIG_CNTL2_RX_ADDRESS                             0x11180074

// Type
#define PCIE_CONFIG_CNTL2_RX_TYPE                                TYPE_SMN

#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVALIDPASID_UR_OFFSET        0
#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVALIDPASID_UR_WIDTH         1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVALIDPASID_UR_MASK        0x1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMRD_UR_OFFSET            1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMRD_UR_WIDTH             1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMRD_UR_MASK            0x2
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMWR_UR_OFFSET            2
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMWR_UR_WIDTH             1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_TRANSMWR_UR_MASK            0x4
#define PCIE_CTRL2_RX_RX_IGNORE_EP_ATSTRANSREQ_UR_OFFSET         3
#define PCIE_CTRL2_RX_RX_IGNORE_EP_ATSTRANSREQ_UR_WIDTH          1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_ATSTRANSREQ_UR_MASK         0x8
#define PCIE_CTRL2_RX_RX_IGNORE_EP_PAGEREQMSG_UR_OFFSET          4
#define PCIE_CTRL2_RX_RX_IGNORE_EP_PAGEREQMSG_UR_WIDTH           1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_PAGEREQMSG_UR_MASK         0x10
#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVCPL_UR_OFFSET              5
#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVCPL_UR_WIDTH               1
#define PCIE_CTRL2_RX_RX_IGNORE_EP_INVCPL_UR_MASK             0x20
#define PCIE_CTRL2_RX_Reserved_6_7_OFFSET                        6
#define PCIE_CTRL2_RX_Reserved_6_7_WIDTH                         2
#define PCIE_CTRL2_RX_Reserved_6_7_MASK                       0xC0
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_EN_OFFSET                   8
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_EN_WIDTH                    1
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_EN_MASK                 0x100
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_SCALE_OFFSET                9
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_SCALE_WIDTH                 3
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_SCALE_MASK              0xE00
#define PCIE_CTRL2_RX_SLVCPL_MEM_LS_EN_OFFSET                   12
#define PCIE_CTRL2_RX_SLVCPL_MEM_LS_EN_WIDTH                     1
#define PCIE_CTRL2_RX_SLVCPL_MEM_LS_EN_MASK                 0x1000
#define PCIE_CTRL2_RX_SLVCPL_MEM_SD_EN_OFFSET                   13
#define PCIE_CTRL2_RX_SLVCPL_MEM_SD_EN_WIDTH                     1
#define PCIE_CTRL2_RX_SLVCPL_MEM_SD_EN_MASK                 0x2000
#define PCIE_CTRL2_RX_SLVCPL_MEM_DS_EN_OFFSET                   14
#define PCIE_CTRL2_RX_SLVCPL_MEM_DS_EN_WIDTH                     1
#define PCIE_CTRL2_RX_SLVCPL_MEM_DS_EN_MASK                 0x4000
#define PCIE_CTRL2_RX_Reserved_15_OFFSET                        15
#define PCIE_CTRL2_RX_Reserved_15_WIDTH                          1
#define PCIE_CTRL2_RX_Reserved_15_MASK                      0x8000
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_MAX_COUNT_OFFSET           16
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_MAX_COUNT_WIDTH            10
#define PCIE_CTRL2_RX_RX_RCB_LATENCY_MAX_COUNT_MASK      0x3FF0000
#define PCIE_CTRL2_RX_Reserved_26_27_OFFSET                     26
#define PCIE_CTRL2_RX_Reserved_26_27_WIDTH                       2
#define PCIE_CTRL2_RX_Reserved_26_27_MASK                0xC000000
#define PCIE_CTRL2_RX_FLR_EXTEND_MODE_OFFSET                    28
#define PCIE_CTRL2_RX_FLR_EXTEND_MODE_WIDTH                      3
#define PCIE_CTRL2_RX_FLR_EXTEND_MODE_MASK              0x70000000
#define PCIE_CTRL2_RX_Reserved_31_OFFSET                        31
#define PCIE_CTRL2_RX_Reserved_31_WIDTH                          1
#define PCIE_CTRL2_RX_Reserved_31_MASK                  0x80000000

/// PCIE_CTRL2_RX
typedef union {
  struct {
    UINT32                          RX_IGNORE_EP_INVALIDPASID_UR:1 ; ///<
    UINT32                              RX_IGNORE_EP_TRANSMRD_UR:1 ; ///<
    UINT32                              RX_IGNORE_EP_TRANSMWR_UR:1 ; ///<
    UINT32                           RX_IGNORE_EP_ATSTRANSREQ_UR:1 ; ///<
    UINT32                            RX_IGNORE_EP_PAGEREQMSG_UR:1 ; ///<
    UINT32                                RX_IGNORE_EP_INVCPL_UR:1 ; ///<
    UINT32                                          Reserved_6_7:2 ; ///<
    UINT32                                     RX_RCB_LATENCY_EN:1 ; ///<
    UINT32                                  RX_RCB_LATENCY_SCALE:3 ; ///<
    UINT32                                      SLVCPL_MEM_LS_EN:1 ; ///<
    UINT32                                      SLVCPL_MEM_SD_EN:1 ; ///<
    UINT32                                      SLVCPL_MEM_DS_EN:1 ; ///<
    UINT32                                           Reserved_15:1 ; ///<
    UINT32                             RX_RCB_LATENCY_MAX_COUNT:10 ; ///<
    UINT32                                        Reserved_26_27:2 ; ///<
    UINT32                                       FLR_EXTEND_MODE:3 ; ///<
    UINT32                                           Reserved_31:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_CTRL2_RX_STRUCT;

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
#define PCIE_SDP_CTRL_PCIECORE0_ADDRESS                       0x1118018C

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
#define PCIECORE_18C_CI_MSTSDP_DISCONNECT_RSP_ON_PARTIAL_OFFSET   14
#define PCIECORE_18C_CI_MSTSDP_DISCONNECT_RSP_ON_PARTIAL_WIDTH     1
#define PCIECORE_18C_CI_MSTSDP_DISCONNECT_RSP_ON_PARTIAL_MASK 0x4000
#define PCIECORE_18C_CI_SWUS_RCVD_ERR_HANDLING_DIS_OFFSET         15
#define PCIECORE_18C_CI_SWUS_RCVD_ERR_HANDLING_DIS_WIDTH           1
#define PCIECORE_18C_CI_SWUS_RCVD_ERR_HANDLING_DIS_MASK       0x8000
#define PCIECORE_18C_Reserved_31_16_OFFSET                        16
#define PCIECORE_18C_Reserved_31_16_WIDTH                         16
#define PCIECORE_18C_Reserved_31_16_MASK                  0xffff0000

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
    UINT32                     CI_MSTSDP_DISCONNECT_RSP_ON_PARTIAL:1 ; ///<
    UINT32                           CI_SWUS_RCVD_ERR_HANDLING_DIS:1 ; ///<
    UINT32                                          Reserved_31_16:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIECORE_18C_STRUCT;

// Address
#define PCIE_LC_PM_CNTL_ADDRESS                             0x111800F4

// Type
#define PCIE_LC_PM_CNTL_TYPE                                TYPE_SMN

#define PCIE_LC_PM_CNTL_LC_PORT_0_CLKREQB_MAP_OFFSET        0
#define PCIE_LC_PM_CNTL_LC_PORT_0_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_0_CLKREQB_MAP_MASK          0xf
#define PCIE_LC_PM_CNTL_LC_PORT_1_CLKREQB_MAP_OFFSET        4
#define PCIE_LC_PM_CNTL_LC_PORT_1_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_1_CLKREQB_MAP_MASK          0xf0
#define PCIE_LC_PM_CNTL_LC_PORT_2_CLKREQB_MAP_OFFSET        8
#define PCIE_LC_PM_CNTL_LC_PORT_2_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_2_CLKREQB_MAP_MASK          0xf00
#define PCIE_LC_PM_CNTL_LC_PORT_3_CLKREQB_MAP_OFFSET        12
#define PCIE_LC_PM_CNTL_LC_PORT_3_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_3_CLKREQB_MAP_MASK          0xf000
#define PCIE_LC_PM_CNTL_LC_PORT_4_CLKREQB_MAP_OFFSET        16
#define PCIE_LC_PM_CNTL_LC_PORT_4_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_4_CLKREQB_MAP_MASK          0xf0000
#define PCIE_LC_PM_CNTL_LC_PORT_5_CLKREQB_MAP_OFFSET        20
#define PCIE_LC_PM_CNTL_LC_PORT_5_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_5_CLKREQB_MAP_MASK          0xf00000
#define PCIE_LC_PM_CNTL_LC_PORT_6_CLKREQB_MAP_OFFSET        24
#define PCIE_LC_PM_CNTL_LC_PORT_6_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_6_CLKREQB_MAP_MASK          0xf000000
#define PCIE_LC_PM_CNTL_LC_PORT_7_CLKREQB_MAP_OFFSET        28
#define PCIE_LC_PM_CNTL_LC_PORT_7_CLKREQB_MAP_WIDTH         4
#define PCIE_LC_PM_CNTL_LC_PORT_7_CLKREQB_MAP_MASK          0xf0000000

/// PCIECORE0x000000F4
typedef union {
  struct {
    UINT32                                      LC_PORT_0_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_1_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_2_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_3_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_4_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_5_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_6_CLKREQB_MAP:4 ; ///<
    UINT32                                      LC_PORT_7_CLKREQB_MAP:4 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_LC_PM_CNTL_STRUCT;

// Register Name PCIE_STRAP_F0

// Address
#define PCIE0_STRAP_F0_ADDRESS                                          0x111802c0

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

// Register Name CPM_CONTROL

// Address
#define PCIE0_CPM_CONTROL_ADDRESS                                     0x11180460

// Type
#define PCIE0_CPM_CONTROL_TYPE                                        TYPE_SMN

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
#define CPM_CONTROL_LCLK_DYN_GATE_LATENCY_WIDTH                       2
#define CPM_CONTROL_LCLK_DYN_GATE_LATENCY_MASK                        0x600
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_OFFSET                     11
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_WIDTH                      1
#define CPM_CONTROL_TXCLK_DYN_GATE_LATENCY_MASK                       0x800
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_OFFSET                    12
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_WIDTH                     2
#define CPM_CONTROL_TXCLK_PERM_GATE_LATENCY_MASK                      0x3000
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_OFFSET                    14
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_WIDTH                     1
#define CPM_CONTROL_TXCLK_REGS_GATE_LATENCY_MASK                      0x4000
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_OFFSET                   15
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_WIDTH                    1
#define CPM_CONTROL_REFCLK_REGS_GATE_LATENCY_MASK                     0x8000
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_OFFSET                       16
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_WIDTH                        1
#define CPM_CONTROL_LCLK_GATE_TXCLK_FREE_MASK                         0x10000
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_OFFSET                        17
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_WIDTH                         1
#define CPM_CONTROL_RCVR_DET_CLK_ENABLE_MASK                          0x20000
#define CPM_CONTROL_FAST_TXCLK_LATENCY_OFFSET                         18
#define CPM_CONTROL_FAST_TXCLK_LATENCY_WIDTH                          3
#define CPM_CONTROL_FAST_TXCLK_LATENCY_MASK                           0x1C0000
#define CPM_CONTROL_Reserved_21_OFFSET                                21
#define CPM_CONTROL_Reserved_21_WIDTH                                 1
#define CPM_CONTROL_Reserved_21_MASK                                  0x200000
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_OFFSET                       22
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_WIDTH                        1
#define CPM_CONTROL_REFCLK_XSTCLK_ENABLE_MASK                         0x400000
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_OFFSET                      23
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_WIDTH                       1
#define CPM_CONTROL_REFCLK_XSTCLK_LATENCY_MASK                        0x800000
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_OFFSET                24
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_WIDTH                 1
#define CPM_CONTROL_CLKREQb_UNGATE_TXCLK_ENABLE_MASK                  0x1000000
#define CPM_CONTROL_LCLK_GATE_ALLOW_IN_L1_OFFSET                      25
#define CPM_CONTROL_LCLK_GATE_ALLOW_IN_L1_WIDTH                       1
#define CPM_CONTROL_LCLK_GATE_ALLOW_IN_L1_MASK                        0x2000000
#define CPM_CONTROL_SPARE_REGS_OFFSET                                 26
#define CPM_CONTROL_SPARE_REGS_WIDTH                                  6
#define CPM_CONTROL_SPARE_REGS_MASK                                   0xFC000000

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
    UINT32                                   LCLK_DYN_GATE_LATENCY:2 ; ///<   ----
    UINT32                                  TXCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_PERM_GATE_LATENCY:2 ; ///<
    UINT32                                 TXCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                REFCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                    LCLK_GATE_TXCLK_FREE:1 ; ///<
    UINT32                                     RCVR_DET_CLK_ENABLE:1 ; ///<
    UINT32                                      FAST_TXCLK_LATENCY:3 ; ///<
    UINT32                                             Reserved_21:1 ; ///<
    UINT32                                    REFCLK_XSTCLK_ENABLE:1 ; ///<
    UINT32                                   REFCLK_XSTCLK_LATENCY:1 ; ///<
    UINT32                             CLKREQb_UNGATE_TXCLK_ENABLE:1 ; ///<
    UINT32                                   LCLK_GATE_ALLOW_IN_L1:1 ; ///<
    UINT32                                              SPARE_REGS:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} CPM_CONTROL_STRUCT;

// Address
#define CPM_CONTROL_PCIECORE0_ADDRESS                          0x11180460

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
#define PCIEDIR_460_LCLK_DYN_GATE_LATENCY_WIDTH                2
#define PCIEDIR_460_LCLK_DYN_GATE_LATENCY_MASK                 0x600
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_OFFSET              11
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_WIDTH               1
#define PCIEDIR_460_TXCLK_DYN_GATE_LATENCY_MASK                0x800
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_OFFSET             12
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_WIDTH              2
#define PCIEDIR_460_TXCLK_PERM_GATE_LATENCY_MASK               0x3000
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_OFFSET             14
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_WIDTH              1
#define PCIEDIR_460_TXCLK_REGS_GATE_LATENCY_MASK               0x4000
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_OFFSET            15
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_WIDTH             1
#define PCIEDIR_460_REFCLK_REGS_GATE_LATENCY_MASK              0x8000
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_OFFSET                16
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_WIDTH                 1
#define PCIEDIR_460_LCLK_GATE_TXCLK_FREE_MASK                  0x10000
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_OFFSET                 17
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_WIDTH                  1
#define PCIEDIR_460_RCVR_DET_CLK_ENABLE_MASK                   0x20000
#define PCIEDIR_460_FAST_TXCLK_LATENCY_OFFSET                  18
#define PCIEDIR_460_FAST_TXCLK_LATENCY_WIDTH                   3
#define PCIEDIR_460_FAST_TXCLK_LATENCY_MASK                    0x1C0000
#define PCIEDIR_460_Reserved_21_OFFSET                         21
#define PCIEDIR_460_Reserved_21_WIDTH                          1
#define PCIEDIR_460_Reserved_21_MASK                           0x200000
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_OFFSET                22
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_WIDTH                 1
#define PCIEDIR_460_REFCLK_XSTCLK_ENABLE_MASK                  0x400000
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_OFFSET               23
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_WIDTH                1
#define PCIEDIR_460_REFCLK_XSTCLK_LATENCY_MASK                 0x800000
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_OFFSET         24
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_WIDTH          1
#define PCIEDIR_460_CLKREQb_UNGATE_TXCLK_ENABLE_MASK           0x1000000
#define PCIEDIR_460_LCLK_GATE_ALLOW_IN_L1_OFFSET               25
#define PCIEDIR_460_LCLK_GATE_ALLOW_IN_L1_WIDTH                1
#define PCIEDIR_460_LCLK_GATE_ALLOW_IN_L1_MASK                 0x2000000
#define PCIEDIR_460_SPARE_REGS_OFFSET                          26
#define PCIEDIR_460_SPARE_REGS_WIDTH                           6
#define PCIEDIR_460_SPARE_REGS_MASK                            0xFC000000

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
    UINT32                                   LCLK_DYN_GATE_LATENCY:2 ; ///<
    UINT32                                  TXCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                 TXCLK_PERM_GATE_LATENCY:2 ; ///<
    UINT32                                 TXCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                REFCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                    LCLK_GATE_TXCLK_FREE:1 ; ///<
    UINT32                                     RCVR_DET_CLK_ENABLE:1 ; ///<
    UINT32                                      FAST_TXCLK_LATENCY:3 ; ///<
    UINT32                                             Reserved_21:1 ; ///<
    UINT32                                    REFCLK_XSTCLK_ENABLE:1 ; ///<
    UINT32                                   REFCLK_XSTCLK_LATENCY:1 ; ///<
    UINT32                             CLKREQb_UNGATE_TXCLK_ENABLE:1 ; ///<
    UINT32                                   LCLK_GATE_ALLOW_IN_L1:1 ; ///<
    UINT32                                              SPARE_REGS:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIEDIR_460_STRUCT;


#define RCC_PCIE_CNTL_ADDRESS                                 0x1012358c
#define RCC_PCIE_CNTL1_ADDRESS                                0x101313AC

#define RCC_PCIE_CNTL_TYPE                                    TYPE_SMN

#define RCC_PCIE_CNTL_HWINIT_WR_LOCK_OFFSET                   0
#define RCC_PCIE_CNTL_HWINIT_WR_LOCK_WIDTH                    1
#define RCC_PCIE_CNTL_HWINIT_WR_LOCK_MASK                     0x1
#define RCC_PCIE_CNTL_RESERVED_OFFSET                         1
#define RCC_PCIE_CNTL_RESERVED_WIDTH                          6
#define RCC_PCIE_CNTL_RESERVED_MASK                           0x7E
#define RCC_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_OFFSET             7
#define RCC_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_WIDTH              1
#define RCC_PCIE_CNTL_UR_ERR_REPORT_DIS_DN_MASK               0x80
#define RCC_PCIE_CNTL_RESERVED1_OFFSET                        8
#define RCC_PCIE_CNTL_RESERVED1_WIDTH                         22
#define RCC_PCIE_CNTL_RESERVED1_MASK                          0x3FFFFF00
#define RCC_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_OFFSET             30
#define RCC_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_WIDTH              1
#define RCC_PCIE_CNTL_RX_IGNORE_LTR_MSG_UR_MASK               0x40000000
#define RCC_PCIE_CNTL_RESERVED2_OFFSET                        31
#define RCC_PCIE_CNTL_RESERVED2_WIDTH                         1
#define RCC_PCIE_CNTL_RESERVED2_MASK                          0x80000000

typedef union {
  struct {
    UINT32                                         HWINIT_WR_LOCK:1 ; ///<
    UINT32                                               RESERVED:6 ; ///<
    UINT32                                   UR_ERR_REPORT_DIS_DN:1 ; ///<
    UINT32                                             RESERVED1:22 ; ///<
    UINT32                                   RX_IGNORE_LTR_MSG_UR:1 ; ///<
    UINT32                                              RESERVED2:1 ; ///<
   } Field;                                                             ///<
} SMN_0x1012358c_STRUCT;

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
#define NBIF0_MGCG_CTRL_ADDRESS                          0x1013a05c
#define SYSHUBMM0_NGDC_MGCG_CTRL_ADDRESS                 0x1410310
#define SYSHUB_MGCG_CTRL_SHUBCLK_ADDRESS                 0x1411040

// Type
#define MGCG_CTRL_TYPE                                    TYPE_SMN


#define NBIF_MGCG_EN_LCLK_OFFSET                                 0
#define NBIF_MGCG_EN_LCLK_WIDTH                                  1
#define NBIF_MGCG_EN_LCLK_MASK                                 0x1
#define NBIF_MGCG_MODE_LCLK_OFFSET                               1
#define NBIF_MGCG_MODE_LCLK_WIDTH                                1
#define NBIF_MGCG_MODE_LCLK_MASK                               0x2
#define NBIF_MGCG_HYSTERESIS_LCLK_OFFSET                         2
#define NBIF_MGCG_HYSTERESIS_LCLK_WIDTH                          8
#define NBIF_MGCG_HYSTERESIS_LCLK_MASK                       0x3FC
#define NBIF_MGCG_HST_DIS_LCLK_OFFSET                           10
#define NBIF_MGCG_HST_DIS_LCLK_WIDTH                             1
#define NBIF_MGCG_HST_DIS_LCLK_MASK                          0x400
#define NBIF_MGCG_DMA_DIS_LCLK_OFFSET                           11
#define NBIF_MGCG_DMA_DIS_LCLK_WIDTH                             1
#define NBIF_MGCG_DMA_DIS_LCLK_MASK                          0x800
#define NBIF_MGCG_REGS_DIS_LCLK_OFFSET                          12
#define NBIF_MGCG_REGS_DIS_LCLK_WIDTH                            1
#define NBIF_MGCG_REGS_DIS_LCLK_MASK                        0x1000
#define NBIF_MGCG_AER_DIS_LCLK_OFFSET                           13
#define NBIF_MGCG_AER_DIS_LCLK_WIDTH                             1
#define NBIF_MGCG_AER_DIS_LCLK_MASK                         0x2000
#define Reserved_31_14_OFFSET                                   14
#define Reserved_31_14_WIDTH                                    18
#define Reserved_31_14_MASK                             0xFFFFC000

typedef union {
  struct {
    UINT32                                       NBIF_MGCG_EN_LCLK:1 ; ///<
    UINT32                                     NBIF_MGCG_MODE_LCLK:1 ; ///<
    UINT32                               NBIF_MGCG_HYSTERESIS_LCLK:8 ; ///<
    UINT32                                  NBIF_MGCG_HST_DIS_LCLK:1 ; ///<
    UINT32                                  NBIF_MGCG_DMA_DIS_LCLK:1 ; ///<
    UINT32                                 NBIF_MGCG_REGS_DIS_LCLK:1 ; ///<
    UINT32                                  NBIF_MGCG_AER_DIS_LCLK:1 ; ///<
    UINT32                                         Reserved_31_14:18 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MGCG_CTRL_STRUCT;


// RCC_DEV0_PORT_STRAP3
// Address
#define SMN_0x1013100c_ADDRESS                                 0x1013100c
// Type
#define SMN_0x1013100c_TYPE                                    TYPE_SMN
#define SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_OFFSET          29
#define SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_WIDTH           1
#define SMN_0x1013100c_STRAP_ATOMIC_EN_DN_DEV0_MASK            0x20000000

// RCC_DEV0_PORT_STRAP5
// Address
#define SMN_0x10131014_ADDRESS                                 0x10131014
// Type
#define SMN_0x10131014_TYPE                                    TYPE_SMN
#define SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_OFFSET    17
#define SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_WIDTH     1
#define SMN_0x10131014_STRAP_ATOMIC_64BIT_EN_DN_DEV0_MASK      0x20000

// RCC_DEV0_PORT_STRAP7
// Address
#define SMN_RCC_DEV0_PORT_STRAP7_ADDRESS                     0x1013101c
// Type
#define SMN_RCC_DEV0_PORT_STRAP7_TYPE                          TYPE_SMN


#define STRAP_PORT_NUMBER_DEV0_OFFSET                                 0
#define STRAP_PORT_NUMBER_DEV0_Width                                  8
#define STRAP_PORT_NUMBER_DEV0_Mask                                0xFF
#define STRAP_MAJOR_REV_ID_DN_DEV0_OFFSET                             8
#define STRAP_MAJOR_REV_ID_DN_DEV0_Width                              4
#define STRAP_MAJOR_REV_ID_DN_DEV0_Mask                           0xF00
#define STRAP_MINOR_REV_ID_DN_DEV0_OFFSET                            12
#define STRAP_MINOR_REV_ID_DN_DEV0_Width                              4
#define STRAP_MINOR_REV_ID_DN_DEV0_Mask                          0xf000
#define STRAP_RP_BUSNUM_DEV0_OFFSET                                  16
#define STRAP_RP_BUSNUM_DEV0_Width                                    8
#define STRAP_RP_BUSNUM_DEV0_Mask                              0xff0000
#define STRAP_DN_DEVNUM_DEV0_OFFSET                                  24
#define STRAP_DN_DEVNUM_DEV0_Width                                    5
#define STRAP_DN_DEVNUM_DEV0_Mask                            0x1f000000
#define STRAP_DN_FUNCID_DEV0_OFFSET                                  29
#define STRAP_DN_FUNCID_DEV0_Width                                    3
#define STRAP_DN_FUNCID_DEV0_Mask                            0xe0000000

typedef union {
   struct {
    UINT32                                      STRAP_PORT_NUMBER_DEV0:8; ///<
    UINT32                                  STRAP_MAJOR_REV_ID_DN_DEV0:4; ///<
    UINT32                                  STRAP_MINOR_REV_ID_DN_DEV0:4; ///<
    UINT32                                        STRAP_RP_BUSNUM_DEV0:8; ///<
    UINT32                                        STRAP_DN_DEVNUM_DEV0:5; ///<
    UINT32                                        STRAP_DN_FUNCID_DEV0:3; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_RCC_DEV0_PORT_STRAP7_STRUCT;

// RCC_DEV1_PORT_STRAP7
// Address
#define SMN_RCC_DEV1_PORT_STRAP7_ADDRESS                     0x1013121c
// Type
#define SMN_RCC_DEV1_PORT_STRAP7_TYPE                          TYPE_SMN

#define STRAP_PORT_NUMBER_DEV1_OFFSET                                 0
#define STRAP_PORT_NUMBER_DEV1_Width                                  8
#define STRAP_PORT_NUMBER_DEV1_Mask                                0xFF
#define STRAP_MAJOR_REV_ID_DN_DEV1_OFFSET                             8
#define STRAP_MAJOR_REV_ID_DN_DEV1_Width                              4
#define STRAP_MAJOR_REV_ID_DN_DEV1_Mask                           0xF00
#define STRAP_MINOR_REV_ID_DN_DEV1_OFFSET                            12
#define STRAP_MINOR_REV_ID_DN_DEV1_Width                              4
#define STRAP_MINOR_REV_ID_DN_DEV1_Mask                          0xf000
#define STRAP_RP_BUSNUM_DEV1_OFFSET                                  16
#define STRAP_RP_BUSNUM_DEV1_Width                                    8
#define STRAP_RP_BUSNUM_DEV1_Mask                              0xff0000
#define STRAP_DN_DEVNUM_DEV1_OFFSET                                  24
#define STRAP_DN_DEVNUM_DEV1_Width                                    5
#define STRAP_DN_DEVNUM_DEV1_Mask                            0x1f000000
#define STRAP_DN_FUNCID_DEV1_OFFSET                                  29
#define STRAP_DN_FUNCID_DEV1_Width                                    3
#define STRAP_DN_FUNCID_DEV1_Mask                            0xe0000000

typedef union {
   struct {
    UINT32                                      STRAP_PORT_NUMBER_DEV1:8; ///<
    UINT32                                  STRAP_MAJOR_REV_ID_DN_DEV1:4; ///<
    UINT32                                  STRAP_MINOR_REV_ID_DN_DEV1:4; ///<
    UINT32                                        STRAP_RP_BUSNUM_DEV1:8; ///<
    UINT32                                        STRAP_DN_DEVNUM_DEV1:5; ///<
    UINT32                                        STRAP_DN_FUNCID_DEV1:3; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_RCC_DEV1_PORT_STRAP7_STRUCT;

// Address
#define SMN_0x101313e4_ADDRESS                                 0x101313e4

// Type
#define SMN_0x101313e4_TYPE                                    TYPE_SMN

#define SMN_0x101313e4_STRAP_MULTI_FUNC_EN_OFFSET              10
#define SMN_0x101313e4_STRAP_MULTI_FUNC_EN_WIDTH               1
#define SMN_0x101313e4_STRAP_MULTI_FUNC_EN_MASK                0x400

/// NBIFRCC1_000013e4
typedef union {
  struct {
    UINT32                                     STRAP_MULTI_FUNC_EN:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x101313e4_STRUCT;

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
#define ErrEvent_ACTION_CONTROL_ADDRESS                        0x13b2009C

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

// RV,PCO
#define ParitySerr_ACTION_CONTROL                              0x13b200A0
#define ParityFatal_ACTION_CONTROL                             0x13b200A4
#define ParityNonFatal_ACTION_CONTROL                          0x13b200A8

typedef union {
  struct {
    UINT32                                             APML_ERR_En:1 ; ///<
    UINT32                                              IntrGenSel:2 ; ///<
    UINT32                                              LinkDis_En:1 ; ///<
    UINT32                                            SyncFlood_En:1 ; ///<
    UINT32                                           Reserved_31_5:27; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE0PortASerr_ACTION_CONTROL_STRUCT, PCIE0PortAExtFatal_ACTION_CONTROL_STRUCT, PCIE0PortAIntFatal_ACTION_CONTROL_STRUCT;

//
// Register Name PCIE0PortASerr_ACTION_CONTROL
//
#define SMN_NBIO0_PCIE0PortASerr_ACTION_CONTROL               0x13b200B0UL

//
// Register Name PCIE0PortAIntFatal_ACTION_CONTROL
//
#define SMN_NBIO0_PCIE0PortAIntFatal_ACTION_CONTROL           0x13b200B4UL

//
// Register Name PCIE0PortAExtFatal_ACTION_CONTROL
//
#define SMN_NBIO0_PCIE0PortAExtFatal_ACTION_CONTROL           0x13b200C0UL

#ifndef IOHC_PORT_SPACE
  #define  IOHC_PORT_SPACE(HANDLE, WRAPPER, PORTINDEX, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (WRAPPER->WrapId * 0x100) + (PORTINDEX * 0x20))
#endif

/// NBRASCFG_0400
typedef union {
  struct {
    UINT32                                      IntPoisonAPMLErrEn:1 ; ///<
    UINT32                                     IntPoisonIntrGenSel:2 ; ///<
    UINT32                                      IntPoisonLinkDisEn:1 ; ///<
    UINT32                                            Reserved_7_5:3 ; ///<
    UINT32                                    IntPoisonSyncFloodEn:1 ; ///<
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
    UINT32                                        Br0_ext_Intr_swz:2 ; ///<
    UINT32                                        Br0_int_Intr_map:5 ; ///<
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
    UINT32                                        Br1_ext_Intr_swz:2 ; ///<
    UINT32                                        Br1_int_Intr_map:5 ; ///<
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
    UINT32                                        Br2_ext_Intr_swz:2 ; ///<
    UINT32                                        Br2_int_Intr_map:5 ; ///<
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
    UINT32                                        Br3_ext_Intr_swz:2 ; ///<
    UINT32                                        Br3_int_Intr_map:5 ; ///<
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
    UINT32                                        Br4_ext_Intr_swz:2 ; ///<
    UINT32                                        Br4_int_Intr_map:5 ; ///<
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
    UINT32                                        Br5_ext_Intr_swz:2 ; ///<
    UINT32                                        Br5_int_Intr_map:5 ; ///<
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
    UINT32                                        Br6_ext_Intr_swz:2 ; ///<
    UINT32                                        Br6_int_Intr_map:5 ; ///<
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
    UINT32                                        Br7_ext_Intr_swz:2 ; ///<
    UINT32                                        Br7_int_Intr_map:5 ; ///<
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
    UINT32                                        Br8_ext_Intr_swz:2 ; ///<
    UINT32                                        Br8_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_060_STRUCT;


// Address
#define IOAPIC_BR9_INTERRUPT_ROUTING_ADDRESS                   0x14300064

// Type
#define IOAPIC_BR9_INTERRUPT_ROUTING_TYPE                      TYPE_NBIOAPICCFG

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
    UINT32                                        Br9_ext_Intr_swz:2 ; ///<
    UINT32                                        Br9_int_Intr_map:5 ; ///<
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
    UINT32                                       Br10_ext_Intr_swz:2 ; ///<
    UINT32                                       Br10_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_068_STRUCT;


// Address
#define IOAPIC_BR11_INTERRUPT_ROUTING_ADDRESS                  0x1430006c

// Type
#define IOAPIC_BR11_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br11_ext_Intr_swz:2 ; ///<
    UINT32                                       Br11_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_06C_STRUCT;


// Address
#define IOAPIC_BR12_INTERRUPT_ROUTING_ADDRESS                  0x14300070

// Type
#define IOAPIC_BR12_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br12_ext_Intr_swz:2 ; ///<
    UINT32                                       Br12_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_070_STRUCT;


// Address
#define IOAPIC_BR13_INTERRUPT_ROUTING_ADDRESS                  0x14300074

// Type
#define IOAPIC_BR13_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br13_ext_Intr_swz:2 ; ///<
    UINT32                                       Br13_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_074_STRUCT;


// Address
#define IOAPIC_BR14_INTERRUPT_ROUTING_ADDRESS                  0x14300078

// Type
#define IOAPIC_BR14_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br14_ext_Intr_swz:2 ; ///<
    UINT32                                       Br14_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_078_STRUCT;


// Address
#define IOAPIC_BR15_INTERRUPT_ROUTING_ADDRESS                  0x1430007c

// Type
#define IOAPIC_BR15_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br15_ext_Intr_swz:2 ; ///<
    UINT32                                       Br15_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_07C_STRUCT;


// Address
#define IOAPIC_BR16_INTERRUPT_ROUTING_ADDRESS                  0x14300080

// Type
#define IOAPIC_BR16_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br16_ext_Intr_swz:2 ; ///<
    UINT32                                       Br16_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_080_STRUCT;


// Address
#define IOAPIC_BR17_INTERRUPT_ROUTING_ADDRESS                  0x14300084

// Type
#define IOAPIC_BR17_INTERRUPT_ROUTING_TYPE                     TYPE_NBIOAPICCFG

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
    UINT32                                       Br17_ext_Intr_swz:2 ; ///<
    UINT32                                       Br17_int_Intr_map:5 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAPICCFG_084_STRUCT;


//
// Register Name IOAPIC_GLUE_CG_LCLK_CTRL_0
//
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_ADDRESS                     0x14300100UL

//
// IOAPIC_GLUE_CG_LCLK_CTRL_0 Register Bitfields:
//

/// Bitfield Description :
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_3_0_OFFSET         0
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_3_0_WIDTH          4
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_3_0_MASK           0xf

/// Bitfield Description : Hysteresis for local clock gating to filter out small turn off changes.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_OFFSET    4
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_WIDTH     8
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_MASK      0xff0

/// Bitfield Description :
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_21_12_OFFSET       12
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_21_12_WIDTH        10
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_Reserved_21_12_MASK         0x3ff000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_OFFSET   22
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_MASK     0x400000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_OFFSET   23
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_MASK     0x800000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_OFFSET   24
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_MASK     0x1000000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_OFFSET   25
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_MASK     0x2000000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_OFFSET   26
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_MASK     0x4000000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_OFFSET   27
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_MASK     0x8000000

/// Bitfield Description : Disable dynamic clock gating for unused branch.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_OFFSET   28
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_MASK     0x10000000

/// Bitfield Description : Disable dynamic clock gating for IOAPIC_ONO.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_OFFSET   29
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_MASK     0x20000000

/// Bitfield Description : Disable dynamic clock gating for IOAPIC_Perf.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_OFFSET   30
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_MASK     0x40000000

/// Bitfield Description : Disable dynamic clock gating for IOAPIC_Cfg.
/// 0 - Enable Clock Gating
/// 1 - Disable Clock Gating.
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_OFFSET   31
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_WIDTH    1
#define IOAPIC_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_MASK     0x80000000L

typedef union {
  struct {
    UINT32                                            Reserved_3_0:4 ; ///<
    UINT32                                       CG_OFF_HYSTERESIS:8 ; ///<
    UINT32                                          Reserved_21_12:10; ///<
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
} IOAPIC_GLUE_CG_LCLK_CTRL_0_STRUCT;


//IOHUB::IOMMUL1::L1_CNTRL_4_instIOMMUL1INT0_aliasSMN  IOAGR
// Address
#define L1_CNTRL_4_AGR_ADDRESS                                 0x147000c8

// Type
#define L1_CNTRL_4_AGR_TYPE                                    TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_0C8_ATS_multiple_resp_en_OFFSET           0
#define IOMMUL1IOAGR_0C8_ATS_multiple_resp_en_WIDTH            1
#define IOMMUL1IOAGR_0C8_ATS_multiple_resp_en_MASK             0x1
#define IOMMUL1IOAGR_0C8_ATS_multiple_L1toL2_en_OFFSET         1
#define IOMMUL1IOAGR_0C8_ATS_multiple_L1toL2_en_WIDTH          1
#define IOMMUL1IOAGR_0C8_ATS_multiple_L1toL2_en_MASK           0x2
#define IOMMUL1IOAGR_0C8_Timeout_pulse_ext_En_OFFSET           2
#define IOMMUL1IOAGR_0C8_Timeout_pulse_ext_En_WIDTH            1
#define IOMMUL1IOAGR_0C8_Timeout_pulse_ext_En_MASK             0x4
#define IOMMUL1IOAGR_0C8_TlpPrefixErr_En_OFFSET                3
#define IOMMUL1IOAGR_0C8_TlpPrefixErr_En_WIDTH                 1
#define IOMMUL1IOAGR_0C8_TlpPrefixErr_En_MASK                  0x8
#define IOMMUL1IOAGR_0C8_RESERVED_OFFSET                       4
#define IOMMUL1IOAGR_0C8_RESERVED_WIDTH                        19
#define IOMMUL1IOAGR_0C8_RESERVED_MASK                         0x7ffff0
#define IOMMUL1IOAGR_0C8_AtsRsp_send_mem_type_en_OFFSET        23
#define IOMMUL1IOAGR_0C8_AtsRsp_send_mem_type_en_WIDTH         1
#define IOMMUL1IOAGR_0C8_AtsRsp_send_mem_type_en_MASK          0x800000
#define IOMMUL1IOAGR_0C8_IntGfx_UnitID_Val_OFFSET              24
#define IOMMUL1IOAGR_0C8_IntGfx_UnitID_Val_WIDTH               7
#define IOMMUL1IOAGR_0C8_IntGfx_UnitID_Val_MASK                0x7f000000

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
} IOMMUL1IOAGR_0C8_STRUCT;

// Address
#define L1_DEBUG_1_AGR_ADDRESS                                 0x1470001c

// Type
#define L1_DEBUG_1_AGR_TYPE                                    TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_01C_REG_force_OrderStreamID_func_OFFSET   0
#define IOMMUL1IOAGR_01C_REG_force_OrderStreamID_func_WIDTH    1
#define IOMMUL1IOAGR_01C_REG_force_OrderStreamID_func_MASK     0x1
#define IOMMUL1IOAGR_01C_REG_cmdwait_wait_emptwq_OFFSET        2
#define IOMMUL1IOAGR_01C_REG_cmdwait_wait_emptwq_WIDTH         1
#define IOMMUL1IOAGR_01C_REG_cmdwait_wait_emptwq_MASK          0x4
#define IOMMUL1IOAGR_01C_REG_inv_wait_emptwq_OFFSET            4
#define IOMMUL1IOAGR_01C_REG_inv_wait_emptwq_WIDTH             1
#define IOMMUL1IOAGR_01C_REG_inv_wait_emptwq_MASK              0x10
#define IOMMUL1IOAGR_01C_REG_disble_eco_invaldation_0_OFFSET   6
#define IOMMUL1IOAGR_01C_REG_disble_eco_invaldation_0_WIDTH    1
#define IOMMUL1IOAGR_01C_REG_disble_eco_invaldation_0_MASK     0x40
#define IOMMUL1IOAGR_01C_REG_L2toL2_rsp_ir_iw_set_OFFSET       7
#define IOMMUL1IOAGR_01C_REG_L2toL2_rsp_ir_iw_set_WIDTH        1
#define IOMMUL1IOAGR_01C_REG_L2toL2_rsp_ir_iw_set_MASK         0x80
#define IOMMUL1IOAGR_01C_REG_L2toL1_credit_ctrl_OFFSET         9
#define IOMMUL1IOAGR_01C_REG_L2toL1_credit_ctrl_WIDTH          1
#define IOMMUL1IOAGR_01C_REG_L2toL1_credit_ctrl_MASK           0x200
#define IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_OFFSET       10
#define IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_WIDTH        1
#define IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_MASK         0x400
#define IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_OFFSET       13
#define IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_WIDTH        1
#define IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_MASK         0x2000
#define IOMMUL1IOAGR_01C_REG_guest_addr_mask_en_OFFSET         15
#define IOMMUL1IOAGR_01C_REG_guest_addr_mask_en_WIDTH          1
#define IOMMUL1IOAGR_01C_REG_guest_addr_mask_en_MASK           0x8000
#define IOMMUL1IOAGR_01C_REG_aerlog_on_abrt_OFFSET             16
#define IOMMUL1IOAGR_01C_REG_aerlog_on_abrt_WIDTH              1
#define IOMMUL1IOAGR_01C_REG_aerlog_on_abrt_MASK               0x10000
#define IOMMUL1IOAGR_01C_REG_enable_nw_OFFSET                  17
#define IOMMUL1IOAGR_01C_REG_enable_nw_WIDTH                   1
#define IOMMUL1IOAGR_01C_REG_enable_nw_MASK                    0x20000
#define IOMMUL1IOAGR_01C_REG_force_pasid_vld_OFFSET            18
#define IOMMUL1IOAGR_01C_REG_force_pasid_vld_WIDTH             1
#define IOMMUL1IOAGR_01C_REG_force_pasid_vld_MASK              0x40000
#define IOMMUL1IOAGR_01C_REG_force_ats_len_OFFSET              19
#define IOMMUL1IOAGR_01C_REG_force_ats_len_WIDTH               1
#define IOMMUL1IOAGR_01C_REG_force_ats_len_MASK                0x80000
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_EX_OFFSET         20
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_EX_WIDTH          1
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_EX_MASK           0x100000
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_PMR_OFFSET        21
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_PMR_WIDTH         1
#define IOMMUL1IOAGR_01C_REG_force_tlpprefix_PMR_MASK          0x200000
#define IOMMUL1IOAGR_01C_REG_ignore_iwir_for_s_bit_OFFSET      22
#define IOMMUL1IOAGR_01C_REG_ignore_iwir_for_s_bit_WIDTH       1
#define IOMMUL1IOAGR_01C_REG_ignore_iwir_for_s_bit_MASK        0x400000
#define IOMMUL1IOAGR_01C_RESERVED_OFFSET                       23
#define IOMMUL1IOAGR_01C_RESERVED_WIDTH                        9
#define IOMMUL1IOAGR_01C_RESERVED_MASK                         0xff800000L

/// IOMMUL1IOAGR_01C
typedef union {
  struct {
    UINT32                            REG_force_OrderStreamID_func:1 ; ///<
    UINT32                                 REG_cmdwait_wait_emptwq:1 ; ///<
    UINT32                                     REG_inv_wait_emptwq:1 ; ///<
    UINT32                            REG_disble_eco_invaldation_0:1 ; ///<
    UINT32                                REG_L2toL2_rsp_ir_iw_set:1 ; ///<
    UINT32                                  REG_L2toL1_credit_ctrl:1 ; ///<
    UINT32                                REG_eco_allow_update_dis:1 ; ///<
    UINT32                                REG_Block_On_4K_wait_dis:1 ; ///<
    UINT32                                  REG_guest_addr_mask_en:1 ; ///<
    UINT32                                      REG_aerlog_on_abrt:1 ; ///<
    UINT32                                           REG_enable_nw:1 ; ///<
    UINT32                                     REG_force_pasid_vld:1 ; ///<
    UINT32                                       REG_force_ats_len:1 ; ///<
    UINT32                                  REG_force_tlpprefix_EX:1 ; ///<
    UINT32                                 REG_force_tlpprefix_PMR:1 ; ///<
    UINT32                               REG_ignore_iwir_for_s_bit:1 ; ///<
    UINT32                                                RESERVED:9 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL1IOAGR_01C_STRUCT;

// Address
#define L1_FEATURE_CNTRL_AGR_ADDRESS                           0x1470009c

// Type
#define L1_FEATURE_CNTRL_AGR_TYPE                              TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_09C_Debug_sticky_bits_OFFSET              0
#define IOMMUL1IOAGR_09C_Debug_sticky_bits_WIDTH               8
#define IOMMUL1IOAGR_09C_Debug_sticky_bits_MASK                0xff
#define IOMMUL1IOAGR_09C_Reserved_31_8_OFFSET                  8
#define IOMMUL1IOAGR_09C_Reserved_31_8_WIDTH                   24
#define IOMMUL1IOAGR_09C_Reserved_31_8_MASK                    0xffffff00L

/// IOMMUL1IOAGR_09C
typedef union {
  struct {
    UINT32                                       Debug_sticky_bits:8 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL1IOAGR_09C_STRUCT;

// Address
#define L1_CNTRL_2_AGR_ADDRESS                                 0x14700038

// Type
#define L1_CNTRL_2_AGR_TYPE                                    TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_038_L1Disable_OFFSET                      0
#define IOMMUL1IOAGR_038_L1Disable_WIDTH                       1
#define IOMMUL1IOAGR_038_L1Disable_MASK                        0x1
#define IOMMUL1IOAGR_038_MSI_to_HT_remap_dis_OFFSET            1
#define IOMMUL1IOAGR_038_MSI_to_HT_remap_dis_WIDTH             1
#define IOMMUL1IOAGR_038_MSI_to_HT_remap_dis_MASK              0x2
#define IOMMUL1IOAGR_038_L1_abrt_ats_dis_OFFSET                2
#define IOMMUL1IOAGR_038_L1_abrt_ats_dis_WIDTH                 1
#define IOMMUL1IOAGR_038_L1_abrt_ats_dis_MASK                  0x4
#define IOMMUL1IOAGR_038_Reserved_3_3_OFFSET                   3
#define IOMMUL1IOAGR_038_Reserved_3_3_WIDTH                    1
#define IOMMUL1IOAGR_038_Reserved_3_3_MASK                     0x8
#define IOMMUL1IOAGR_038_RESERVED_OFFSET                       4
#define IOMMUL1IOAGR_038_RESERVED_WIDTH                        20
#define IOMMUL1IOAGR_038_RESERVED_MASK                         0xfffff0
#define IOMMUL1IOAGR_038_CPD_RESP_MODE_OFFSET                  24
#define IOMMUL1IOAGR_038_CPD_RESP_MODE_WIDTH                   3
#define IOMMUL1IOAGR_038_CPD_RESP_MODE_MASK                    0x7000000
#define IOMMUL1IOAGR_038_L1NonConsumedDataErrorSignalEn_OFFSET 27
#define IOMMUL1IOAGR_038_L1NonConsumedDataErrorSignalEn_WIDTH  1
#define IOMMUL1IOAGR_038_L1NonConsumedDataErrorSignalEn_MASK   0x8000000
#define IOMMUL1IOAGR_038_L1ConsumedDataErrorSignalEn_OFFSET    28
#define IOMMUL1IOAGR_038_L1ConsumedDataErrorSignalEn_WIDTH     1
#define IOMMUL1IOAGR_038_L1ConsumedDataErrorSignalEn_MASK      0x10000000
#define IOMMUL1IOAGR_038_L1SDPParityEn_OFFSET                  29
#define IOMMUL1IOAGR_038_L1SDPParityEn_WIDTH                   1
#define IOMMUL1IOAGR_038_L1SDPParityEn_MASK                    0x20000000
#define IOMMUL1IOAGR_038_FlushVC_HRT1_Inv_OFFSET               30
#define IOMMUL1IOAGR_038_FlushVC_HRT1_Inv_WIDTH                1
#define IOMMUL1IOAGR_038_FlushVC_HRT1_Inv_MASK                 0x40000000
#define IOMMUL1IOAGR_038_FlushVC_HRT1_IntInv_OFFSET            31
#define IOMMUL1IOAGR_038_FlushVC_HRT1_IntInv_WIDTH             1
#define IOMMUL1IOAGR_038_FlushVC_HRT1_IntInv_MASK              0x80000000L

/// IOMMUL1IOAGR_038
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
} IOMMUL1IOAGR_038_STRUCT;

// Address
#define L1_CLKCNTRL_0_AGR_ADDRESS                              0x147000cc

// Type
#define L1_CLKCNTRL_0_AGR_TYPE                                 TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_0CC_L1_DMA_CLKGATE_EN_OFFSET              4
#define IOMMUL1IOAGR_0CC_L1_DMA_CLKGATE_EN_WIDTH               1
#define IOMMUL1IOAGR_0CC_L1_DMA_CLKGATE_EN_MASK                0x10
#define IOMMUL1IOAGR_0CC_L1_CACHE_CLKGATE_EN_OFFSET            5
#define IOMMUL1IOAGR_0CC_L1_CACHE_CLKGATE_EN_WIDTH             1
#define IOMMUL1IOAGR_0CC_L1_CACHE_CLKGATE_EN_MASK              0x20
#define IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_OFFSET            6
#define IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_WIDTH             1
#define IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_MASK              0x40
#define IOMMUL1IOAGR_0CC_L1_PERF_CLKGATE_EN_OFFSET             8
#define IOMMUL1IOAGR_0CC_L1_PERF_CLKGATE_EN_WIDTH              1
#define IOMMUL1IOAGR_0CC_L1_PERF_CLKGATE_EN_MASK               0x100
#define IOMMUL1IOAGR_0CC_L1_MEMORY_CLKGATE_EN_OFFSET           9
#define IOMMUL1IOAGR_0CC_L1_MEMORY_CLKGATE_EN_WIDTH            1
#define IOMMUL1IOAGR_0CC_L1_MEMORY_CLKGATE_EN_MASK             0x200
#define IOMMUL1IOAGR_0CC_L1_REG_CLKGATE_EN_OFFSET              10
#define IOMMUL1IOAGR_0CC_L1_REG_CLKGATE_EN_WIDTH               1
#define IOMMUL1IOAGR_0CC_L1_REG_CLKGATE_EN_MASK                0x400
#define IOMMUL1IOAGR_0CC_L1_HOSTREQ_CLKGATE_EN_OFFSET          11
#define IOMMUL1IOAGR_0CC_L1_HOSTREQ_CLKGATE_EN_WIDTH           1
#define IOMMUL1IOAGR_0CC_L1_HOSTREQ_CLKGATE_EN_MASK            0x800
#define IOMMUL1IOAGR_0CC_L1_DMARSP_CLKGATE_EN_OFFSET           12
#define IOMMUL1IOAGR_0CC_L1_DMARSP_CLKGATE_EN_WIDTH            1
#define IOMMUL1IOAGR_0CC_L1_DMARSP_CLKGATE_EN_MASK             0x1000
#define IOMMUL1IOAGR_0CC_L1_HOSTRSP_CLKGATE_EN_OFFSET          13
#define IOMMUL1IOAGR_0CC_L1_HOSTRSP_CLKGATE_EN_WIDTH           1
#define IOMMUL1IOAGR_0CC_L1_HOSTRSP_CLKGATE_EN_MASK            0x2000
#define IOMMUL1IOAGR_0CC_L1_CLKGATE_HYSTERESIS_OFFSET          14
#define IOMMUL1IOAGR_0CC_L1_CLKGATE_HYSTERESIS_WIDTH           8
#define IOMMUL1IOAGR_0CC_L1_CLKGATE_HYSTERESIS_MASK            0x3fc000
#define IOMMUL1IOAGR_0CC_reserved_OFFSET                       22
#define IOMMUL1IOAGR_0CC_reserved_WIDTH                        9
#define IOMMUL1IOAGR_0CC_reserved_MASK                         0x7fc00000
#define IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_OFFSET               31
#define IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_WIDTH                1
#define IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_MASK                 0x80000000L

/// IOMMUL1IOAGR_0CC
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
} IOMMUL1IOAGR_0CC_STRUCT;

//IOHUB::IOMMUL1::L1_CNTRL_4_instIOMMUL1INT0_aliasSMN  NBIF
// Address
#define L1_SB_LOCATION_ADDRESS                                 0x14800024

// Type
#define L1_SB_LOCATION_TYPE                                    TYPE_IOMMUL1IOAGR

#define IOMMUL1IOAGR_024_SBlocated_Port_OFFSET                 0
#define IOMMUL1IOAGR_024_SBlocated_Port_WIDTH                  16
#define IOMMUL1IOAGR_024_SBlocated_Port_MASK                   0xffff
#define IOMMUL1IOAGR_024_SBlocated_Core_OFFSET                 16
#define IOMMUL1IOAGR_024_SBlocated_Core_WIDTH                  16
#define IOMMUL1IOAGR_024_SBlocated_Core_MASK                   0xffff0000L

/// IOMMUL1IOAGR_024
typedef union {
  struct {
    UINT32                                          SBlocated_Port:16; ///<
    UINT32                                          SBlocated_Core:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL1IOAGR_024_STRUCT;


//IOHUB::IOMMUL1::L1_CNTRL_4_instIOMMUL1INT0_aliasSMN  PCIE0
// Address
#define L1_CNTRL_4_PCIE0_ADDRESS                               0x148000c8

// Type
#define L1_CNTRL_4_PCIE0_TYPE                                  TYPE_IOMMUL1PCIE0

#define IOMMUL1PCIE0_0C8_ATS_multiple_resp_en_OFFSET           0
#define IOMMUL1PCIE0_0C8_ATS_multiple_resp_en_WIDTH            1
#define IOMMUL1PCIE0_0C8_ATS_multiple_resp_en_MASK             0x1
#define IOMMUL1PCIE0_0C8_ATS_multiple_L1toL2_en_OFFSET         1
#define IOMMUL1PCIE0_0C8_ATS_multiple_L1toL2_en_WIDTH          1
#define IOMMUL1PCIE0_0C8_ATS_multiple_L1toL2_en_MASK           0x2
#define IOMMUL1PCIE0_0C8_Timeout_pulse_ext_En_OFFSET           2
#define IOMMUL1PCIE0_0C8_Timeout_pulse_ext_En_WIDTH            1
#define IOMMUL1PCIE0_0C8_Timeout_pulse_ext_En_MASK             0x4
#define IOMMUL1PCIE0_0C8_TlpPrefixErr_En_OFFSET                3
#define IOMMUL1PCIE0_0C8_TlpPrefixErr_En_WIDTH                 1
#define IOMMUL1PCIE0_0C8_TlpPrefixErr_En_MASK                  0x8
#define IOMMUL1PCIE0_0C8_RESERVED_OFFSET                       4
#define IOMMUL1PCIE0_0C8_RESERVED_WIDTH                        19
#define IOMMUL1PCIE0_0C8_RESERVED_MASK                         0x7ffff0
#define IOMMUL1PCIE0_0C8_AtsRsp_send_mem_type_en_OFFSET        23
#define IOMMUL1PCIE0_0C8_AtsRsp_send_mem_type_en_WIDTH         1
#define IOMMUL1PCIE0_0C8_AtsRsp_send_mem_type_en_MASK          0x800000
#define IOMMUL1PCIE0_0C8_IntGfx_UnitID_Val_OFFSET              24
#define IOMMUL1PCIE0_0C8_IntGfx_UnitID_Val_WIDTH               7
#define IOMMUL1PCIE0_0C8_IntGfx_UnitID_Val_MASK                0x7f000000

/// IOMMUL1PCIE0_0C8
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
} IOMMUL1PCIE0_0C8_STRUCT;


// Address
#define L1_DEBUG_1_PCIE0_ADDRESS                               0x1480001c

// Type
#define L1_DEBUG_1_PCIE0_TYPE                                  TYPE_IOMMUL1PCIE0

#define IOMMUL1PCIE0_01C_REG_force_OrderStreamID_func_OFFSET   0
#define IOMMUL1PCIE0_01C_REG_force_OrderStreamID_func_WIDTH    1
#define IOMMUL1PCIE0_01C_REG_force_OrderStreamID_func_MASK     0x1
#define IOMMUL1PCIE0_01C_REG_cmdwait_wait_emptwq_OFFSET        2
#define IOMMUL1PCIE0_01C_REG_cmdwait_wait_emptwq_WIDTH         1
#define IOMMUL1PCIE0_01C_REG_cmdwait_wait_emptwq_MASK          0x4
#define IOMMUL1PCIE0_01C_REG_inv_wait_emptwq_OFFSET            4
#define IOMMUL1PCIE0_01C_REG_inv_wait_emptwq_WIDTH             1
#define IOMMUL1PCIE0_01C_REG_inv_wait_emptwq_MASK              0x10
#define IOMMUL1PCIE0_01C_REG_disble_eco_invaldation_0_OFFSET   6
#define IOMMUL1PCIE0_01C_REG_disble_eco_invaldation_0_WIDTH    1
#define IOMMUL1PCIE0_01C_REG_disble_eco_invaldation_0_MASK     0x40
#define IOMMUL1PCIE0_01C_REG_L2toL2_rsp_ir_iw_set_OFFSET       7
#define IOMMUL1PCIE0_01C_REG_L2toL2_rsp_ir_iw_set_WIDTH        1
#define IOMMUL1PCIE0_01C_REG_L2toL2_rsp_ir_iw_set_MASK         0x80
#define IOMMUL1PCIE0_01C_REG_L2toL1_credit_ctrl_OFFSET         9
#define IOMMUL1PCIE0_01C_REG_L2toL1_credit_ctrl_WIDTH          1
#define IOMMUL1PCIE0_01C_REG_L2toL1_credit_ctrl_MASK           0x200
#define IOMMUL1PCIE0_01C_REG_eco_allow_update_dis_OFFSET       10
#define IOMMUL1PCIE0_01C_REG_eco_allow_update_dis_WIDTH        1
#define IOMMUL1PCIE0_01C_REG_eco_allow_update_dis_MASK         0x400
#define IOMMUL1PCIE0_01C_REG_Block_On_4K_wait_dis_OFFSET       13
#define IOMMUL1PCIE0_01C_REG_Block_On_4K_wait_dis_WIDTH        1
#define IOMMUL1PCIE0_01C_REG_Block_On_4K_wait_dis_MASK         0x2000
#define IOMMUL1PCIE0_01C_REG_guest_addr_mask_en_OFFSET         15
#define IOMMUL1PCIE0_01C_REG_guest_addr_mask_en_WIDTH          1
#define IOMMUL1PCIE0_01C_REG_guest_addr_mask_en_MASK           0x8000
#define IOMMUL1PCIE0_01C_REG_aerlog_on_abrt_OFFSET             16
#define IOMMUL1PCIE0_01C_REG_aerlog_on_abrt_WIDTH              1
#define IOMMUL1PCIE0_01C_REG_aerlog_on_abrt_MASK               0x10000
#define IOMMUL1PCIE0_01C_REG_enable_nw_OFFSET                  17
#define IOMMUL1PCIE0_01C_REG_enable_nw_WIDTH                   1
#define IOMMUL1PCIE0_01C_REG_enable_nw_MASK                    0x20000
#define IOMMUL1PCIE0_01C_REG_force_pasid_vld_OFFSET            18
#define IOMMUL1PCIE0_01C_REG_force_pasid_vld_WIDTH             1
#define IOMMUL1PCIE0_01C_REG_force_pasid_vld_MASK              0x40000
#define IOMMUL1PCIE0_01C_REG_force_ats_len_OFFSET              19
#define IOMMUL1PCIE0_01C_REG_force_ats_len_WIDTH               1
#define IOMMUL1PCIE0_01C_REG_force_ats_len_MASK                0x80000
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_EX_OFFSET         20
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_EX_WIDTH          1
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_EX_MASK           0x100000
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_PMR_OFFSET        21
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_PMR_WIDTH         1
#define IOMMUL1PCIE0_01C_REG_force_tlpprefix_PMR_MASK          0x200000
#define IOMMUL1PCIE0_01C_REG_ignore_iwir_for_s_bit_OFFSET      22
#define IOMMUL1PCIE0_01C_REG_ignore_iwir_for_s_bit_WIDTH       1
#define IOMMUL1PCIE0_01C_REG_ignore_iwir_for_s_bit_MASK        0x400000
#define IOMMUL1PCIE0_01C_RESERVED_OFFSET                       23
#define IOMMUL1PCIE0_01C_RESERVED_WIDTH                        9
#define IOMMUL1PCIE0_01C_RESERVED_MASK                         0xff800000L

/// IOMMUL1PCIE0_01C
typedef union {
  struct {
    UINT32                            REG_force_OrderStreamID_func:1 ; ///<
    UINT32                                 REG_cmdwait_wait_emptwq:1 ; ///<
    UINT32                                     REG_inv_wait_emptwq:1 ; ///<
    UINT32                            REG_disble_eco_invaldation_0:1 ; ///<
    UINT32                                REG_L2toL2_rsp_ir_iw_set:1 ; ///<
    UINT32                                  REG_L2toL1_credit_ctrl:1 ; ///<
    UINT32                                REG_eco_allow_update_dis:1 ; ///<
    UINT32                                REG_Block_On_4K_wait_dis:1 ; ///<
    UINT32                                  REG_guest_addr_mask_en:1 ; ///<
    UINT32                                      REG_aerlog_on_abrt:1 ; ///<
    UINT32                                           REG_enable_nw:1 ; ///<
    UINT32                                     REG_force_pasid_vld:1 ; ///<
    UINT32                                       REG_force_ats_len:1 ; ///<
    UINT32                                  REG_force_tlpprefix_EX:1 ; ///<
    UINT32                                 REG_force_tlpprefix_PMR:1 ; ///<
    UINT32                               REG_ignore_iwir_for_s_bit:1 ; ///<
    UINT32                                                RESERVED:9 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL1PCIE0_01C_STRUCT;

// Address
#define L1_FEATURE_CNTRL_PCIE0_ADDRESS                         0x1480009c

// Type
#define L1_FEATURE_CNTRL_PCIE0_TYPE                            TYPE_IOMMUL1PCIE0

#define IOMMUL1PCIE0_09C_Debug_sticky_bits_OFFSET              0
#define IOMMUL1PCIE0_09C_Debug_sticky_bits_WIDTH               8
#define IOMMUL1PCIE0_09C_Debug_sticky_bits_MASK                0xff
#define IOMMUL1PCIE0_09C_Reserved_31_8_OFFSET                  8
#define IOMMUL1PCIE0_09C_Reserved_31_8_WIDTH                   24
#define IOMMUL1PCIE0_09C_Reserved_31_8_MASK                    0xffffff00L

/// IOMMUL1PCIE0_09C
typedef union {
  struct {
    UINT32                                       Debug_sticky_bits:8 ; ///<
    UINT32                                           Reserved_31_8:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMUL1PCIE0_09C_STRUCT;


// Address
#define L1_CLKCNTRL_0_PCIE0_ADDRESS                            0x148000cc

// Type
#define L1_CLKCNTRL_0_PCIE0_TYPE                               TYPE_IOMMUL1PCIE0

#define IOMMUL1PCIE0_0CC_L1_DMA_CLKGATE_EN_OFFSET              4
#define IOMMUL1PCIE0_0CC_L1_DMA_CLKGATE_EN_WIDTH               1
#define IOMMUL1PCIE0_0CC_L1_DMA_CLKGATE_EN_MASK                0x10
#define IOMMUL1PCIE0_0CC_L1_CACHE_CLKGATE_EN_OFFSET            5
#define IOMMUL1PCIE0_0CC_L1_CACHE_CLKGATE_EN_WIDTH             1
#define IOMMUL1PCIE0_0CC_L1_CACHE_CLKGATE_EN_MASK              0x20
#define IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_OFFSET            6
#define IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_WIDTH             1
#define IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_MASK              0x40
#define IOMMUL1PCIE0_0CC_L1_PERF_CLKGATE_EN_OFFSET             8
#define IOMMUL1PCIE0_0CC_L1_PERF_CLKGATE_EN_WIDTH              1
#define IOMMUL1PCIE0_0CC_L1_PERF_CLKGATE_EN_MASK               0x100
#define IOMMUL1PCIE0_0CC_L1_MEMORY_CLKGATE_EN_OFFSET           9
#define IOMMUL1PCIE0_0CC_L1_MEMORY_CLKGATE_EN_WIDTH            1
#define IOMMUL1PCIE0_0CC_L1_MEMORY_CLKGATE_EN_MASK             0x200
#define IOMMUL1PCIE0_0CC_L1_REG_CLKGATE_EN_OFFSET              10
#define IOMMUL1PCIE0_0CC_L1_REG_CLKGATE_EN_WIDTH               1
#define IOMMUL1PCIE0_0CC_L1_REG_CLKGATE_EN_MASK                0x400
#define IOMMUL1PCIE0_0CC_L1_HOSTREQ_CLKGATE_EN_OFFSET          11
#define IOMMUL1PCIE0_0CC_L1_HOSTREQ_CLKGATE_EN_WIDTH           1
#define IOMMUL1PCIE0_0CC_L1_HOSTREQ_CLKGATE_EN_MASK            0x800
#define IOMMUL1PCIE0_0CC_L1_DMARSP_CLKGATE_EN_OFFSET           12
#define IOMMUL1PCIE0_0CC_L1_DMARSP_CLKGATE_EN_WIDTH            1
#define IOMMUL1PCIE0_0CC_L1_DMARSP_CLKGATE_EN_MASK             0x1000
#define IOMMUL1PCIE0_0CC_L1_HOSTRSP_CLKGATE_EN_OFFSET          13
#define IOMMUL1PCIE0_0CC_L1_HOSTRSP_CLKGATE_EN_WIDTH           1
#define IOMMUL1PCIE0_0CC_L1_HOSTRSP_CLKGATE_EN_MASK            0x2000
#define IOMMUL1PCIE0_0CC_L1_CLKGATE_HYSTERESIS_OFFSET          14
#define IOMMUL1PCIE0_0CC_L1_CLKGATE_HYSTERESIS_WIDTH           8
#define IOMMUL1PCIE0_0CC_L1_CLKGATE_HYSTERESIS_MASK            0x3fc000
#define IOMMUL1PCIE0_0CC_reserved_OFFSET                       22
#define IOMMUL1PCIE0_0CC_reserved_WIDTH                        9
#define IOMMUL1PCIE0_0CC_reserved_MASK                         0x7fc00000
#define IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_OFFSET               31
#define IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_WIDTH                1
#define IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_MASK                 0x80000000L

/// IOMMUL1PCIE0_0CC
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
} IOMMUL1PCIE0_0CC_STRUCT;

// Address
#define IOMMU_L1_SDP_CLKREQ_CNTRL_F0_INST1_ADDRESS             0x147000d4
#define IOMMU_L1_SDP_CLKREQ_CNTRL_F0_INST2_ADDRESS             0x148000d4

// Type
#define IOMMU_L1_SDP_CLKREQ_CNTRL_F0_TYPE                      TYPE_SMN

#define HW_PG_WAKEUP_EN_DMA_OFFSET                             0
#define HW_PG_WAKEUP_EN_DMA_WIDTH                              1
#define HW_PG_WAKEUP_EN_DMA_MASK                               0x1

#define HW_PG_WAKEUP_EN_HOST_OFFSET                            1
#define HW_PG_WAKEUP_EN_HOST_WIDTH                             1
#define HW_PG_WAKEUP_EN_HOST_MASK                              0x2

#define Reserved2_31_OFFSET                                    2
#define Reserved2_31_WIDTH                                     30
#define Reserved2_31_MASK                                      0xFFFFFFFC

/// IOMMU_L1_SDP_CLKREQ_CNTRL
typedef union {
  struct {
    UINT32                                     HW_PG_WAKEUP_EN_DMA:1 ; ///<
    UINT32                                    HW_PG_WAKEUP_EN_HOST:1 ; ///<
    UINT32                                           Reserved2_31:30 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMU_L1_SDP_CLKREQ_CNTRL_STRUCT;


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


// Address
#define IOMMU_L2A_MEMPWR_GATE_1_ADDRESS                         0x157000d4

// Type
#define IOMMU_L2A_MEMPWR_GATE_1_TYPE                              TYPE_SMN

#define L2AREG_LS_EN_OFFSET                                              0
#define L2AREG_LS_EN_WIDTH                                               1
#define L2AREG_LS_EN_MASK                                              0x1
#define L2AREG_DS_EN_OFFSET                                              1
#define L2AREG_DS_EN_WIDTH                                               1
#define L2AREG_DS_EN_MASK                                              0x2
#define L2AREG_SD_EN_OFFSET                                              2
#define L2AREG_SD_EN_WIDTH                                               1
#define L2AREG_SD_EN_MASK                                              0x4
#define IOMMU_L2A_Reserved_3_OFFSET                                      3
#define IOMMU_L2A_Reserved_3_WIDTH                                       1
#define IOMMU_L2A_Reserved_3_MASK                                      0x8
#define L2AREG_CACHE_PGMEM_SEL_OFFSET                                    4
#define L2AREG_CACHE_PGMEM_SEL_WIDTH                                     1
#define L2AREG_CACHE_PGMEM_SEL_MASK                                   0x10
#define Reserved_5_31_OFFSET                                             5
#define Reserved_5_31_WIDTH                                             27
#define Reserved_5_31_MASK                                      0xFFFFFFE0

///
typedef union {
  struct {
    UINT32                                            L2AREG_LS_EN:1 ; ///<
    UINT32                                            L2AREG_DS_EN:1 ; ///<
    UINT32                                            L2AREG_SD_EN:1 ; ///<
    UINT32                                              Reserved_3:1 ; ///<
    UINT32                                  L2AREG_CACHE_PGMEM_SEL:1 ; ///<
    UINT32                                          Reserved_5_31:27 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMU_L2A_MEMPWR_GATE_1_STRUCT;

//
// IOMMU_L2A
//
// Address
#define L2_PWRGATE_CNTRL_REG_0_Address                         0x157000f8

// Type
#define L2_PWRGATE_CNTRL_REG_0_TYPE                            TYPE_SMN

#define IP_PG_thres_OFFSET                                     0
#define IP_PG_thres_Width                                      32
#define IP_PG_thres_Mask                                       0xFFFFFFFF

// L2_PWRGATE_CNTRL_REG_0
typedef union {
   struct {
    UINT32                                        IP_PG_thres:32; ///<
  } Field;                                                        ///<
  UINT32 Value;                                                   ///<
} L2_PWRGATE_CNTRL_REG_0_STRUCT;

// Address
#define IOMMU_L2A_L2_PWRGATE_CNTRL_REG_3_ADDRESS                 0x15700104

// Type
#define IOMMU_L2A_L2_PWRGATE_CNTRL_REG_3_TYPE                      TYPE_SMN

#define IP_PG_EN_OFFSET                                                   0
#define IP_PG_EN_WIDTH                                                    1
#define IP_PG_EN_MASK                                                   0x1
#define IP_PG_BUSY_OFFSET                                                 1
#define IP_PG_BUSY_WIDTH                                                  1
#define IP_PG_BUSY_MASK                                                 0x2
#define L2_PG_STATUS_OFFSET                                               2
#define L2_PG_STATUS_WIDTH                                                1
#define L2_PG_STATUS_MASK                                               0x4
#define CFG_FW_PG_EXIT_EN_OFFSET                                          3
#define CFG_FW_PG_EXIT_EN_WIDTH                                           2
#define CFG_FW_PG_EXIT_EN_MASK                                         0x18
#define Reserved_5_31_OFFSET                                              5
#define Reserved_5_31_WIDTH                                              27
#define Reserved_5_31_MASK                                       0xFFFFFFE0

///
typedef union {
  struct {
    UINT32                                              IP_PG_en:1 ; ///<
    UINT32                                            IP_PG_busy:1 ; ///<
    UINT32                                          L2_PG_STATUS:1 ; ///<
    UINT32                                     CFG_FW_PG_EXIT_EN:2 ; ///<
  } Field;                                                           ///<
  UINT32 Value;                                                      ///<
} IOMMU_L2A_L2_PWRGATE_CNTRL_REG_3_STRUCT;


// Address
#define IOMMU_L2B_MEMPWR_GATE_1_ADDRESS                        0x13f01254

// Type
#define IOMMU_L2B_MEMPWR_GATE_1_TYPE                             TYPE_SMN

#define L2BREG_LS_EN_OFFSET                                             0
#define L2BREG_LS_EN_WIDTH                                              1
#define L2BREG_LS_EN_MASK                                             0x1
#define L2BREG_DS_EN_OFFSET                                             1
#define L2BREG_DS_EN_WIDTH                                              1
#define L2BREG_DS_EN_MASK                                             0x2
#define L2BREG_SD_EN_OFFSET                                             2
#define L2BREG_SD_EN_WIDTH                                              1
#define L2BREG_SD_EN_MASK                                             0x4
#define L2B_IP_PGMEM_SEL_OFFSET                                         3
#define L2B_IP_PGMEM_SEL_WIDTH                                          1
#define L2B_IP_PGMEM_SEL_MASK                                         0x8
#define L2BREG_CACHE_PGMEM_SEL_OFFSET                                   4
#define L2BREG_CACHE_PGMEM_SEL_WIDTH                                    1
#define L2BREG_CACHE_PGMEM_SEL_MASK                                  0x10
#define Reserved_5_31_OFFSET                                            5
#define Reserved_5_31_WIDTH                                            27
#define Reserved_5_31_MASK                                     0xFFFFFFE0

///
typedef union {
  struct {
    UINT32                                            L2BREG_LS_EN:1 ; ///<
    UINT32                                            L2BREG_DS_EN:1 ; ///<
    UINT32                                            L2BREG_SD_EN:1 ; ///<
    UINT32                                        L2B_IP_PGMEM_SEL:1 ; ///<
    UINT32                                  L2BREG_CACHE_PGMEM_SEL:1 ; ///<
    UINT32                                          Reserved_5_31:27 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOMMU_L2B_MEMPWR_GATE_1_STRUCT;


///  IOAGR_SDP_PORT_CTRL_STRUCT
// Address
#define IOAGR_SDP_PORT_CTRL_ADDRESS                           0x15B00040
// Type
#define IOAGR_SDP_PORT_CTRL_Type                                TYPE_SMN

#define IOAGR_SDP_PORT_DISCONNECT_HYSTERESIS_OFFSET                    0
#define IOAGR_SDP_PORT_DISCONNECT_HYSTERESIS_WIDTH                     6
#define IOAGR_SDP_PORT_DISCONNECT_HYSTERESIS_MASK                   0x3F
#define IOAGR_SDP_RESERVED_6_14_OFFSET                                 6
#define IOAGR_SDP_RESERVED_6_14_WIDTH                                  9
#define IOAGR_SDP_RESERVED_6_14_MASK                              0x7FC0
#define IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_OFFSET                      15
#define IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_WIDTH                        1
#define IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_MASK                    0x8000
#define IOAGR_SDP_HOST_ENABLE_EARLY_CLKREQ_OFFSET                     16
#define IOAGR_SDP_HOST_ENABLE_EARLY_CLKREQ_WIDTH                      16
#define IOAGR_SDP_HOST_ENABLE_EARLY_CLKREQ_MASK               0xFFFF0000

typedef union {
  struct {
    UINT32                           Port_Disconnect_Hysteresis:6 ; ///<
    UINT32                                        Reserved_6_14:9 ; ///<
    UINT32                                 DMAEnableEarlyClkReq:1 ; ///<
    UINT32                               HostEnableEarlyClkReq:16 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOAGR_SDP_PORT_CTRL_STRUCT;


// Address
#define NB_IOAGR_PGMST_ADDRESS                                 0x15B00080

// Type
#define NB_IOAGR_PGMST_TYPE                                      TYPE_SMN

#define NBIOAGR_PGMST_CFG_PG_HYSTERESIS_OFFSET                          0
#define NBIOAGR_PGMST_CFG_PG_HYSTERESIS_WIDTH                           8
#define NBIOAGR_PGMST_CFG_PG_HYSTERESIS_MASK                         0xFF
#define NBIOAGR_CFG_PG_EN_OFFSET                                        8
#define NBIOAGR_CFG_PG_EN_WIDTH                                         1
#define NBIOAGR_CFG_PG_EN_MASK                                      0x100
#define NBIOAGR_Reserved_9_OFFSET                                       9
#define NBIOAGR_Reserved_9_WIDTH                                        1
#define NBIOAGR_Reserved_9_MASK                                     0x200
#define NBIOAGR_CFG_IDLENESS_COUNT_EN_OFFSET                           10
#define NBIOAGR_CFG_IDLENESS_COUNT_EN_WIDTH                             4
#define NBIOAGR_CFG_IDLENESS_COUNT_EN_MASK                         0x3C00
#define NBIOAGR_CFG_FW_PG_EXIT_EN_OFFSET                               14
#define NBIOAGR_CFG_FW_PG_EXIT_EN_WIDTH                                 2
#define NBIOAGR_CFG_FW_PG_EXIT_EN_MASK                             0xC000
#define NBIOAGR_Reserved_16_31_OFFSET                                  16
#define NBIOAGR_Reserved_16_31_WIDTH                                   16
#define NBIOAGR_Reserved_16_31_MASK                            0xFFFF0000

/// NBIOAGR_PGMST
typedef union {
  struct {
    UINT32                                       CFG_PG_HYSTERESIS:8 ; ///<
    UINT32                                               CFG_PG_EN:1 ; ///<
    UINT32                                              Reserved_9:1 ; ///<
    UINT32                                   CFG_IDLENESS_COUNT_EN:4 ; ///<
    UINT32                                       CFG_FW_PG_EXIT_EN:2 ; ///<
    UINT32                                               Reserved:16 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} NBIOAGR_PGMST_STRUCT;


// Address
#define IOAGR_GLUE_CG_LCLK_CTRL_0_ADDRESS                      0x15b00000

// Type
#define IOAGR_GLUE_CG_LCLK_CTRL_0_TYPE                         TYPE_IOAGRCFG

#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_0_3_OFFSET          0
#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_0_3_WIDTH           4
#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_0_3_MASK            0xF
#define IOAGR_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_OFFSET     4
#define IOAGR_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_WIDTH      8
#define IOAGR_GLUE_CG_LCLK_CTRL_0_CG_OFF_HYSTERESIS_MASK       0xff0
#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_12_21_OFFSET        12
#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_12_21_WIDTH         10
#define IOAGR_GLUE_CG_LCLK_CTRL_0_Reserved_12_21_MASK          0x3FF000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_OFFSET    22
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK9_MASK      0x400000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_OFFSET    23
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK8_MASK      0x800000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_OFFSET    24
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK7_MASK      0x1000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_OFFSET    25
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK6_MASK      0x2000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_OFFSET    26
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK5_MASK      0x4000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_OFFSET    27
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK4_MASK      0x8000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_OFFSET    28
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK3_MASK      0x10000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_OFFSET    29
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK2_MASK      0x20000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_OFFSET    30
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK1_MASK      0x40000000
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_OFFSET    31
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_0_SOFT_OVERRIDE_CLK0_MASK      0x80000000L

/// IOAGR_GLUE_CG_LCLK_CTRL_0
typedef union {
  struct {
    UINT32                                            Reserved_0_3:4 ; ///<
    UINT32                                       CG_OFF_HYSTERESIS:8 ; ///<
    UINT32                                          Reserved_12_21:10; ///<
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
} IOAGR_GLUE_CG_LCLK_CTRL_0_STRUCT;

// Address
#define IOAGR_GLUE_CG_LCLK_CTRL_1_ADDRESS                      0x15b00004

// Type
#define IOAGR_GLUE_CG_LCLK_CTRL_1_TYPE                         TYPE_IOAGRCFG

#define IOAGR_GLUE_CG_LCLK_CTRL_1_Reserved_0_3_OFFSET          0
#define IOAGR_GLUE_CG_LCLK_CTRL_1_Reserved_0_3_WIDTH           22
#define IOAGR_GLUE_CG_LCLK_CTRL_1_Reserved_0_3_MASK            0x3FFFFF
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK9_OFFSET    22
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK9_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK9_MASK      0x400000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK8_OFFSET    23
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK8_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK8_MASK      0x800000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK7_OFFSET    24
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK7_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK7_MASK      0x1000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK6_OFFSET    25
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK6_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK6_MASK      0x2000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK5_OFFSET    26
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK5_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK5_MASK      0x4000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK4_OFFSET    27
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK4_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK4_MASK      0x8000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK3_OFFSET    28
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK3_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK3_MASK      0x10000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK2_OFFSET    29
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK2_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK2_MASK      0x20000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK1_OFFSET    30
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK1_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK1_MASK      0x40000000
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK0_OFFSET    31
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK0_WIDTH     1
#define IOAGR_GLUE_CG_LCLK_CTRL_1_SOFT_OVERRIDE_CLK0_MASK      0x80000000L

/// IOAGR_GLUE_CG_LCLK_CTRL_1
typedef union {
  struct {
    UINT32                                           Reserved_0_21:22; ///<
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
} IOAGR_GLUE_CG_LCLK_CTRL_1_STRUCT;


#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n0_ADDRESS   0x15b00400UL
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n0_ADDRESS   0x15b00404UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n0_ADDRESS      0x15b00408UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n0_ADDRESS      0x15b0040cUL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS 0x15b00410UL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS 0x15b00414UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Lower_n0_ADDRESS    0x15b00418UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Upper_n0_ADDRESS    0x15b0041cUL

#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n0_ADDRESS   0x15b00430UL
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n0_ADDRESS   0x15b00434UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n0_ADDRESS      0x15b00438UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n0_ADDRESS      0x15b0043cUL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n0_ADDRESS 0x15b00440UL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n0_ADDRESS 0x15b00444UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Lower_n0_ADDRESS    0x15b00448UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Upper_n0_ADDRESS    0x15b0044cUL


#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n1_ADDRESS   0x15b00800UL
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n1_ADDRESS   0x15b00804UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n1_ADDRESS      0x15b00808UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n1_ADDRESS      0x15b0080cUL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS 0x15b00810UL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS 0x15b00814UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Lower_n1_ADDRESS    0x15b00818UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Upper_n1_ADDRESS    0x15b0081cUL

#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n1_ADDRESS   0x15b00830UL
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n1_ADDRESS   0x15b00834UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n1_ADDRESS      0x15b00838UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n1_ADDRESS      0x15b0083cUL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n1_ADDRESS 0x15b00840UL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n1_ADDRESS 0x15b00844UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Lower_n1_ADDRESS    0x15b00848UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Upper_n1_ADDRESS    0x15b0084cUL

#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n2_ADDRESS   0x15b00c00UL
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n2_ADDRESS   0x15b00c04UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n2_ADDRESS      0x15b00c08UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n2_ADDRESS      0x15b00c0cUL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS 0x15b00c10UL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS 0x15b00c14UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Lower_n2_ADDRESS    0x15b00c18UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Upper_n2_ADDRESS    0x15b00c1cUL

#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n2_ADDRESS   0x15b00c30UL
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n2_ADDRESS   0x15b00c34UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n2_ADDRESS      0x15b00c38UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n2_ADDRESS      0x15b00c3cUL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n2_ADDRESS 0x15b00c40UL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n2_ADDRESS 0x15b00c44UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Lower_n2_ADDRESS    0x15b00c48UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Upper_n2_ADDRESS    0x15b00c4cUL

#define IOAGR_SION_S0_Client_Req_BurstTarget_Lower_n3_ADDRESS   0x15b01000UL
#define IOAGR_SION_S0_Client_Req_BurstTarget_Upper_n3_ADDRESS   0x15b01004UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Lower_n3_ADDRESS      0x15b01008UL
#define IOAGR_SION_S0_Client_Req_TimeSlot_Upper_n3_ADDRESS      0x15b0100cUL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS 0x15b01010UL
#define IOAGR_SION_S0_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS 0x15b01014UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Lower_n3_ADDRESS    0x15b01018UL
#define IOAGR_SION_S0_Client_RdRsp_TimeSlot_Upper_n3_ADDRESS    0x15b0101cUL

#define IOAGR_SION_S1_Client_Req_BurstTarget_Lower_n3_ADDRESS   0x15b01030UL
#define IOAGR_SION_S1_Client_Req_BurstTarget_Upper_n3_ADDRESS   0x15b01034UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Lower_n3_ADDRESS      0x15b01038UL
#define IOAGR_SION_S1_Client_Req_TimeSlot_Upper_n3_ADDRESS      0x15b0103cUL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Lower_n3_ADDRESS 0x15b01040UL
#define IOAGR_SION_S1_Client_RdRsp_BurstTarget_Upper_n3_ADDRESS 0x15b01044UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Lower_n3_ADDRESS    0x15b01048UL
#define IOAGR_SION_S1_Client_RdRsp_TimeSlot_Upper_n3_ADDRESS    0x15b0104cUL


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

// Register Name PCIEP_STRAP_MISC
// Address
#define PCIEP_STRAP_MISC_instPCIE0_link_ADDRESS                0x11140304

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
#define SION_WRAPPER_404_Reserved1_OFFSET                                        10
#define SION_WRAPPER_404_Reserved1_WIDTH                                         6
#define SION_WRAPPER_404_Reserved1_MASK                                          0xfc00
#define SION_WRAPPER_404_Reserved_25_16_OFFSET                                   16
#define SION_WRAPPER_404_Reserved_25_16_WIDTH                                    10
#define SION_WRAPPER_404_Reserved_25_16_MASK                                     0x3ff0000
#define SION_WRAPPER_404_Reserved0_OFFSET                                        26
#define SION_WRAPPER_404_Reserved0_WIDTH                                         6
#define SION_WRAPPER_404_Reserved0_MASK                                          0xfc000000L

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
    UINT32                                             Reserved1:6 ; ///<
    UINT32                                       Reserved_25_16:10; ///<
    UINT32                                             Reserved0:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SION_WRAPPER_404_STRUCT;


// Address
#define SMN_NBIF_CFG_Address                                        0x1013a0e8
// Type
#define SMN_NBIF_CFG_TYPE                                             TYPE_SMN

#define NBIF_CFG_SHUBCLK_0_IDLE_HYSTERESIS_OFFSET                            0
#define NBIF_CFG_SHUBCLK_0_IDLE_HYSTERESIS_Width                             5
#define NBIF_CFG_SHUBCLK_0_IDLE_HYSTERESIS_Mask                           0x1f
#define NBIF_CFG_SHUBCLK_1_IDLE_HYSTERESIS_OFFSET                            5
#define NBIF_CFG_SHUBCLK_1_IDLE_HYSTERESIS_Width                             5
#define NBIF_CFG_SHUBCLK_1_IDLE_HYSTERESIS_Mask                          0x3e0
#define NBIF_PG_ENDP_D3_ONLY_OFFSET                                         10
#define NBIF_PG_ENDP_D3_ONLY_Width                                           1
#define NBIF_PG_ENDP_D3_ONLY_Mask                                        0x400
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE_OFFSET                        11
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE_Width                          1
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE_Mask                       0x800
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_DS_EXIT_OFFSET                       12
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_DS_EXIT_Width                         1
#define NBIF_PG_EARLY_WAKEUP_BY_CLIENT_DS_EXIT_Mask                     0x1000
#define NBIF_PG_SHUB_CLK_PERM_OFFSET                                        13
#define NBIF_PG_SHUB_CLK_PERM_Width                                          1
#define NBIF_PG_SHUB_CLK_PERM_Mask                                      0x2000
#define NBIF_PG_DS_ALLOW_DIS_OFFSET                                         14
#define NBIF_PG_DS_ALLOW_DIS_Width                                           1
#define NBIF_PG_DS_ALLOW_DIS_Mask                                       0x4000
#define NBIF_PG_Reserved_15_OFFSET                                          15
#define NBIF_PG_Reserved_15_Width                                            1
#define NBIF_PG_Reserved_15_Mask                                        0x8000
#define NBIF_PG_RESET_SELECT_COLD_RESET_OFFSET                              16
#define NBIF_PG_RESET_SELECT_COLD_RESET_Width                                1
#define NBIF_PG_RESET_SELECT_COLD_RESET_Mask                           0x10000
#define NBIF_PG_Reserved_17_23_OFFSET                                       17
#define NBIF_PG_Reserved_17_23_Width                                         7
#define NBIF_PG_Reserved_17_23_Mask                                   0xFE0000
#define NBIF_CFG_REFCLK_CYCLE_FOR_200NS_OFFSET                              24
#define NBIF_CFG_REFCLK_CYCLE_FOR_200NS_Width                                6
#define NBIF_CFG_REFCLK_CYCLE_FOR_200NS_Mask                        0x3f000000
#define NBIF_PG_Reserved_30_OFFSET                                          30
#define NBIF_PG_Reserved_30_Width                                            1
#define NBIF_PG_Reserved_30_Mask                                    0x40000000
#define NBIF_CFG_PG_EXIT_OVERRIDE_OFFSET                                    31
#define NBIF_CFG_PG_EXIT_OVERRIDE_Width                                      1
#define NBIF_CFG_PG_EXIT_OVERRIDE_Mask                              0x80000000

/// NBIF_CFG
typedef union {
   struct {
    UINT32                                        NBIF_CFG_SHUBCLK_0_IDLE_HYSTERESIS:5; ///<
    UINT32                                        NBIF_CFG_SHUBCLK_1_IDLE_HYSTERESIS:5; ///<
    UINT32                                        NBIF_PG_ENDP_D3_ONLY:1; ///<
    UINT32                                        NBIF_PG_EARLY_WAKEUP_BY_CLIENT_ACTIVE:1; ///<
    UINT32                                        NBIF_PG_EARLY_WAKEUP_BY_CLIENT_DS_EXIT:1; ///<
    UINT32                                        NBIF_PG_SHUB_CLK_PERM:1; ///<
    UINT32                                        NBIF_PG_DS_ALLOW_DIS:1; ///<
    UINT32                                        NBIF_PG_Reserved_15:1; ///<
    UINT32                                        NBIF_PG_RESET_SELECT_COLD_RESET:1; ///<
    UINT32                                        NBIF_PG_Reserved_17_23:7; ///<
    UINT32                                        NBIF_CFG_REFCLK_CYCLE_FOR_200NS:6; ///<
    UINT32                                        NBIF_PG_Reserved_30:1; ///<
    UINT32                                        NBIF_CFG_PG_EXIT_OVERRIDE:1; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_NBIF_CFG_STRUCT;


// Address
#define SMN_0x1013A108                                         0x1013A108

// Type
#define SMN_0x1013A108_TYPE                                    TYPE_SMN

#define SMN_GMI_REQ_REALTIME_WEIGHT_OFFSET                     0
#define SMN_GMI_REQ_REALTIME_WEIGHT_WIDTH                      8
#define SMN_GMI_REQ_REALTIME_WEIGHT_MASK                       0xff
#define SMN_GMI_REQ_NORM_P_WEIGHT_OFFSET                       8
#define SMN_GMI_REQ_NORM_P_WEIGHT_WIDTH                        8
#define SMN_GMI_REQ_NORM_P_WEIGHT_MASK                         0xff00
#define SMN_GMI_REQ_NORM_NP_WEIGHT_OFFSET                      16
#define SMN_GMI_REQ_NORM_NP_WEIGHT_WIDTH                       8
#define SMN_GMI_REQ_NORM_NP_WEIGHT_MASK                        0xff0000
#define SMN_Reserved_30_24_OFFSET                              24
#define SMN_Reserved_30_24_WIDTH                               7
#define SMN_Reserved_30_24_MASK                                0x7f000000L
#define SMN_GMI_REQ_WRR_MODE_OFFSET                            31
#define SMN_GMI_REQ_WRR_MODE_WIDTH                             1
#define SMN_GMI_REQ_WRR_MODE_MASK                              0x80000000L

/// NBIFMISC0x00000108
typedef union {
  struct {
    UINT32                                 GMI_REQ_REALTIME_WEIGHT:8 ; ///<
    UINT32                                   GMI_REQ_NORM_P_WEIGHT:8 ; ///<
    UINT32                                  GMI_REQ_NORM_NP_WEIGHT:8 ; ///<
    UINT32                                          Reserved_30_24:7 ; ///<
    UINT32                                        GMI_REQ_WRR_MODE:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_0x1013A108_STRUCT;

// Address
#define PCS_PCIEX16_C10_GLOBAL_CONTROL0_ADDRESS                0x11a0b010

// Type
#define PCS_PCIEX16_C10_GLOBAL_CONTROL0_TYPE                     TYPE_SMN

#define InitHardware_OFFSET                                             0
#define InitHardware_Width                                              1
#define InitHardware_Mask                                             0x1
#define InitComplete_OFFSET                                             1
#define InitComplete_Width                                              1
#define InitComplete_Mask                                             0x2
#define EIDetectorCycle_OFFSET                                          2
#define EIDetectorCycle_Width                                           1
#define EIDetectorCycle_Mask                                          0x4
#define PCS_PCIEX16_C10_Reserved_3_OFFSET                               3
#define PCS_PCIEX16_C10_Reserved_3_Width                                1
#define PCS_PCIEX16_C10_Reserved_3_Mask                               0x8
#define EIDetectorOnTime_OFFSET                                         4
#define EIDetectorOnTime_Width                                         10
#define EIDetectorOnTime_Mask                                      0x3FF0
#define VoltageDimmingEnDuringEIDetectorOnTime_OFFSET                  14
#define VoltageDimmingEnDuringEIDetectorOnTime_Width                    1
#define VoltageDimmingEnDuringEIDetectorOnTime_Mask                0x4000
#define VoltageDimmingEnDuringEIDetectorOffTime_OFFSET                 15
#define VoltageDimmingEnDuringEIDetectorOffTime_Width                   1
#define VoltageDimmingEnDuringEIDetectorOffTime_Mask               0x8000
#define VoltageDimmingTransitionTime_OFFSET                            16
#define VoltageDimmingTransitionTime_Width                              4
#define VoltageDimmingTransitionTime_Mask                         0xf0000
#define EIDetectorOffTime_OFFSET                                       20
#define EIDetectorOffTime_Width                                        10
#define EIDetectorOffTime_Mask                                 0x3ff00000
#define Reserved31_30_OFFSET                                           30
#define Reserved31_30_Width                                             2
#define Reserved31_30_Mask                                     0xC0000000

///PCS_PCIEX16 CONTROL0
typedef union {
   struct {
    UINT32                                           InitHardware:1; ///<
    UINT32                                           InitComplete:1; ///<
    UINT32                                        EIDetectorCycle:1; ///<
    UINT32                                              Reserved3:1; ///<
    UINT32                                      EIDetectorOnTime:10; ///<
    UINT32                 VoltageDimmingEnDuringEIDetectorOnTime:1; ///<
    UINT32                VoltageDimmingEnDuringEIDetectorOffTime:1; ///<
    UINT32                           VoltageDimmingTransitionTime:4; ///<
    UINT32                                     EIDetectorOffTime:10; ///<
    UINT32                                          Reserved31_30:2; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCS_PCIEX16_CONTROL0_STRUCT;


// Address
#define PCS_PCIEX16_C10_GLOBAL_CONTROL1_ADDRESS                0x11a0b014

// Type
#define PCS_PCIEX16_C10_GLOBAL_CONTROL1_TYPE                     TYPE_SMN

#define DefaultPCLKFrequency_OFFSET                                     0
#define DefaultPCLKFrequency_Width                                      2
#define DefaultPCLKFrequency_Mask                                     0x3
#define DefaultMaximumLinkRate_OFFSET                                   2
#define DefaultMaximumLinkRate_Width                                    2
#define DefaultMaximumLinkRate_Mask                                   0xc
#define MasterPLL_OFFSET                                                4
#define MasterPLL_Width                                                 4
#define MasterPLL_Mask                                               0xf0
#define MasterPLLAuto_OFFSET                                            8
#define MasterPLLAuto_Width                                             1
#define MasterPLLAuto_Mask                                          0x100
#define AllowTxActivePowerGating_OFFSET                                 9
#define AllowTxActivePowerGating_Width                                  1
#define AllowTxActivePowerGating_Mask                               0x200
#define AllowRxActivePowerGating_OFFSET                                10
#define AllowRxActivePowerGating_Width                                  1
#define AllowRxActivePowerGating_Mask                               0x400
#define AllowTxInactivePowerGating_OFFSET                              11
#define AllowTxInactivePowerGating_Width                                1
#define AllowTxInactivePowerGating_Mask                             0x800
#define AllowRxInactivePowerGating_OFFSET                              12
#define AllowRxInactivePowerGating_Width                                1
#define AllowRxInactivePowerGating_Mask                            0x1000
#define EnableTxSSClkGating_OFFSET                                     13
#define EnableTxSSClkGating_Width                                       1
#define EnableTxSSClkGating_Mask                                   0x2000
#define EnableMaxPClkGating_OFFSET                                     14
#define EnableMaxPClkGating_Width                                       1
#define EnableMaxPClkGating_Mask                                   0x4000
#define Reserved_15_OFFSET                                             15
#define Reserved_15_Width                                               1
#define Reserved_15_Mask                                           0x8000
#define AllowRxPS2_OFFSET                                              16
#define AllowRxPS2_Width                                                1
#define AllowRxPS2_Mask                                           0x10000
#define AllowRxPS3_OFFSET                                              17
#define AllowRxPS3_Width                                                1
#define AllowRxPS3_Mask                                           0x20000
#define AllowTxPS2_OFFSET                                              18
#define AllowTxPS2_Width                                                1
#define AllowTxPS2_Mask                                           0x40000
#define AllowTxPS3_OFFSET                                              19
#define AllowTxPS3_Width                                                1
#define AllowTxPS3_Mask                                           0x80000
#define AllowPLLShutdownRxPS2_OFFSET                                   21
#define AllowPLLShutdownRxPS2_Width                                     1
#define AllowPLLShutdownRxPS2_Mask                                0x200000
#define Reserved23_22_OFFSET                                           22
#define Reserved23_22_Width                                             2
#define Reserved23_22_Mask                                       0xC00000
#define PLLActiveAbovePS4_OFFSET                                       24
#define PLLActiveAbovePS4_Width                                         1
#define PLLActiveAbovePS4_Mask                                  0x1000000
#define PLLActiveInPS4_OFFSET                                          25
#define PLLActiveInPS4_Width                                            1
#define PLLActiveInPS4_Mask                                     0x2000000
#define DisableRxPS4_OFFSET                                            26
#define DisableRxPS4_Width                                              1
#define DisableRxPS4_Mask                                       0x4000000
#define DisableTxPS4_OFFSET                                            27
#define DisableTxPS4_Width                                              1
#define DisableTxPS4_Mask                                       0x8000000
#define DisableTxPS4inRxPS3_OFFSET                                     28
#define DisableTxPS4inRxPS3_Width                                       1
#define DisableTxPS4inRxPS3_Mask                               0x10000000
#define RemapSATAP6TOP5_OFFSET                                         29
#define RemapSATAP6TOP5_Width                                           1
#define RemapSATAP6TOP5_Mask                                   0x20000000
#define Reserved_30_OFFSET                                             30
#define Reserved_30_Width                                               1
#define Reserved_30_Mask                                       0x40000000
#define FarEndAnalogLoopbackEnable_OFFSET                              31
#define FarEndAnalogLoopbackEnable_Width                                1
#define FarEndAnalogLoopbackEnable_Mask                       0x800000000

///PCS_PCIEX16 CONTROL1
typedef union {
   struct {
    UINT32                                   DefaultPCLKFrequency:2; ///<
    UINT32                                 DefaultMaximumLinkRate:2; ///<
    UINT32                                              MasterPLL:4; ///<
    UINT32                                          MasterPLLAuto:1; ///<
    UINT32                               AllowTxActivePowerGating:1; ///<
    UINT32                               AllowRxActivePowerGating:1; ///<
    UINT32                             AllowTxInactivePowerGating:1; ///<
    UINT32                             AllowRxInactivePowerGating:1; ///<
    UINT32                                    EnableTxSSClkGating:1; ///<
    UINT32                                    EnableMaxPClkGating:1; ///<
    UINT32                                            Reserved_15:1; ///<
    UINT32                                             AllowRxPS2:1; ///<
    UINT32                                             AllowRxPS3:1; ///<
    UINT32                                             AllowTxPS2:1; ///<
    UINT32                                             AllowTxPS3:1; ///<
    UINT32                                            Reserved_20:1; ///<
    UINT32                                  AllowPLLShutdownRxPS2:1; ///<
    UINT32                                          Reserved23_22:2; ///<
    UINT32                                      PLLActiveAbovePS4:1; ///<
    UINT32                                         PLLActiveInPS4:1; ///<
    UINT32                                           DisableRxPS4:1; ///<
    UINT32                                           DisableTxPS4:1; ///<
    UINT32                                    DisableTxPS4inRxPS3:1; ///<
    UINT32                                        RemapSATAP6TOP5:1; ///<
    UINT32                                            Reserved_30:1; ///<
    UINT32                             FarEndAnalogLoopbackEnable:1; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCS_PCIEX16_CONTROL1_STRUCT;


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
#define PCIE_PGMST_CNTL_Address                                 0x111804C0
#define RSMU_POWER_GATING_CONTROL_Address                       0x11180484
#define PCS_C10_POWER_GATING_REGISTER_Address                   0x11A0B7C0
#define PCICFG_IOMMU_SSID_ADDRESS                               0x13F00078

// Address
#define PCICFG_NBIF0RC_SSID_ADDRESS                             0x10131004
#define PCICFG_NBIF1RC_SSID_ADDRESS                             0x10131204
#define PCICFG_NBIF0EPF0_GFX_SSID_ADDRESS                       0x1014004C
#define PCICFG_NBIF0EPF1_GFX_Audio_SSID_ADDRESS                 0x1014104C
#define PCICFG_NBIF0EPF2_PSP_SSID_ADDRESS                       0x1014204C
#define PCICFG_NBIF0EPF6_HDAudio_SSID_ADDRESS                   0x1014604C
#define PCICFG_NBIF0EPF9_GBE0_SSID_ADDRESS                      0x1014904C
#define PCICFG_NBIF0EPF10_GBE1_SSID_ADDRESS                     0x1014A04C

#define PCICFG_SUBSYSTEM_VENDOR_ID_OFFSET                       0
#define PCICFG_SUBSYSTEM_VENDOR_ID_WIDTH                        16
#define PCICFG_SUBSYSTEM_VENDOR_ID_MASK                         0xffff
#define PCICFG_SUBSYSTEM_ID_OFFSET                              16
#define PCICFG_SUBSYSTEM_ID_WIDTH                               16
#define PCICFG_SUBSYSTEM_ID_MASK                                0xffff0000L

/// PCICFG SUBSYSTEM DEFINITION
typedef union {
  struct {
    UINT32                                     SUBSYSTEM_VENDOR_ID:16; ///<
    UINT32                                            SUBSYSTEM_ID:16; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCICFG_STRUCT;


// Address
#define IOHC_PCIE_CRS_Count_Address                             0x13b10028

// Type
#define IOHC_PCIE_CRS_Count_TYPE                                  TYPE_SMN

#define CrsDelayCount_OFFSET                                             0
#define CrsDelayCount_Width                                             16
#define CrsDelayCount_Mask                                          0xFFFF
#define CrsLimitCount_OFFSET                                            16
#define CrsLimitCount_Width                                             12
#define CrsLimitCount_Mask                                       0xfff0000

typedef union {
   struct {
    UINT32                                           CrsDelayCount:16; ///<
    UINT32                                           CrsLimitCount:12; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} IOHC_PCIE_CRS_Count_STRUCT;


// Address
#define PCIE_IOMMU_COMMAND_Address                               0x13f00004

// Type
#define PCIE_IOMMU_COMMAND_TYPE                                  TYPE_SMN


#define IO_ACCESS_EN_OFFSET                                      0
#define IO_ACCESS_EN_Width                                       1
#define IO_ACCESS_EN_Mask                                        0x1
#define MEM_ACCESS_EN_OFFSET                                     1
#define MEM_ACCESS_EN_Width                                      1
#define MEM_ACCESS_EN_Mask                                       0x2
#define BUS_MASTER_EN_OFFSET                                     2
#define BUS_MASTER_EN_Width                                      1
#define BUS_MASTER_EN_Mask                                       0x4
#define PCIE_IOMMU_COMMAND_Reserved1_OFFSET                      3
#define PCIE_IOMMU_COMMAND_Reserved1_Width                       3
#define PCIE_IOMMU_COMMAND_Reserved1_Mask                        0x38
#define PARITY_ERROR_EN_OFFSET                                   6
#define PARITY_ERROR_EN_Width                                    1
#define PARITY_ERROR_EN_Mask                                     0x40
#define Reserved0_OFFSET                                         7
#define Reserved0_Width                                          1
#define Reserved0_Mask                                           0x80
#define SERR_EN_OFFSET                                           8
#define SERR_EN_Width                                            1
#define SERR_EN_Mask                                             0x100
#define PCIE_IOMMU_COMMAND_Reserved2_OFFSET                      9
#define PCIE_IOMMU_COMMAND_Reserved2_Width                       1
#define PCIE_IOMMU_COMMAND_Reserved2_Mask                        0x200
#define INTERRUPT_DIS_OFFSET                                     10
#define INTERRUPT_DIS_Width                                      1
#define INTERRUPT_DIS_Mask                                       0x400
#define PCIE_IOMMU_COMMAND_Reserved_OFFSET                       11
#define PCIE_IOMMU_COMMAND_Reserved_Width                        5
#define PCIE_IOMMU_COMMAND_Reserved_Mask                         0xf800

/// PCIE_IOMMU_COMMAND DEFINITION
typedef union {
   struct {
    UINT32                                            IO_ACCESS_EN:1; ///<
    UINT32                                           MEM_ACCESS_EN:1; ///<
    UINT32                                           BUS_MASTER_EN:1; ///<
    UINT32                                               Reserved1:3; ///<
    UINT32                                         PARITY_ERROR_EN:1; ///<
    UINT32                                               Reserved0:1; ///<
    UINT32                                                 SERR_EN:1; ///<
    UINT32                                               Reserved2:1; ///<
    UINT32                                           INTERRUPT_DIS:1; ///<
    UINT32                                                Reserved:5; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} PCIE_IOMMU_COMMAND_STRUCT;

//
// Register Name MiscClkCntl4
// Description : Non Sticky bit.
//

// Address
#define SMN_MiscClkCntl4_ADDRESS                               0x2d01e4cUL

/// Bitfield Description : GPP_CLK6 Reserved.
#define MiscClkCntl4_GPP_CLK6_Reserved_OFFSET                  0
#define MiscClkCntl4_GPP_CLK6_Reserved_WIDTH                   4
#define MiscClkCntl4_GPP_CLK6_Reserved_MASK                    0xful

/// Bitfield Description :
#define MiscClkCntl4_Reserved_5_4_OFFSET                       4
#define MiscClkCntl4_Reserved_5_4_WIDTH                        2
#define MiscClkCntl4_Reserved_5_4_MASK                         0x30ul

/// Bitfield Description : RV TMDP_100M Refclk Driver PWDN.
#define MiscClkCntl4_TMDP_100M_Refclk_Driver_PWDN_OFFSET       6
#define MiscClkCntl4_TMDP_100M_Refclk_Driver_PWDN_WIDTH        1
#define MiscClkCntl4_TMDP_100M_Refclk_Driver_PWDN_MASK         0x40ul

/// Bitfield Description : RV TMDP_100M Refclk Selection.
#define MiscClkCntl4_TMDP_100M_Refclk_Selection_OFFSET         7
#define MiscClkCntl4_TMDP_100M_Refclk_Selection_WIDTH          2
#define MiscClkCntl4_TMDP_100M_Refclk_Selection_MASK           0x180ul

/// Bitfield Description : RV TMDP_48M Refclk Driver PWDN.
#define MiscClkCntl4_TMDP_48M_Refclk_Driver_PWDN_OFFSET        9
#define MiscClkCntl4_TMDP_48M_Refclk_Driver_PWDN_WIDTH         1
#define MiscClkCntl4_TMDP_48M_Refclk_Driver_PWDN_MASK          0x200ul

/// Bitfield Description : RV TMDP_48M Refclk Selection.
#define MiscClkCntl4_TMDP_48M_Refclk_Selection_OFFSET          10
#define MiscClkCntl4_TMDP_48M_Refclk_Selection_WIDTH           2
#define MiscClkCntl4_TMDP_48M_Refclk_Selection_MASK            0xc00ul

/// Bitfield Description :
#define MiscClkCntl4_Reserved_15_12_OFFSET                     12
#define MiscClkCntl4_Reserved_15_12_WIDTH                      4
#define MiscClkCntl4_Reserved_15_12_MASK                       0xf000ul

/// Bitfield Description : SATA Core Clock Enable/Disable. SATA Core clocks are FCH_SATA_SGPIO_CLK and FCH_SATA_100M_CLK which are generated from FCH.
#define MiscClkCntl4_SATA_Core_Clk_En_OFFSET                   16
#define MiscClkCntl4_SATA_Core_Clk_En_WIDTH                    1
#define MiscClkCntl4_SATA_Core_Clk_En_MASK                     0x10000ul

/// Bitfield Description : USB3 Host Clock Enable/Disable.
#define MiscClkCntl4_USB3_Host_Clk_En_OFFSET                   17
#define MiscClkCntl4_USB3_Host_Clk_En_WIDTH                    1
#define MiscClkCntl4_USB3_Host_Clk_En_MASK                     0x20000ul

/// Bitfield Description : USB31 Host Clock Enable/Disable.
#define MiscClkCntl4_USB31_Host_Clk_En_OFFSET                  18
#define MiscClkCntl4_USB31_Host_Clk_En_WIDTH                   1
#define MiscClkCntl4_USB31_Host_Clk_En_MASK                    0x40000u

/// Bitfield Description :
#define MiscClkCntl4_Reserved_19_19_OFFSET                     19
#define MiscClkCntl4_Reserved_19_19_WIDTH                      1
#define MiscClkCntl4_Reserved_19_19_MASK                       0x80000ul

/// Bitfield Description : GFX_DLDOCLK 600 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_GFX_DLDOCLK_600MClk_EnB_OFFSET            20
#define MiscClkCntl4_GFX_DLDOCLK_600MClk_EnB_WIDTH             1
#define MiscClkCntl4_GFX_DLDOCLK_600MClk_EnB_MASK              0x100000ul

/// Bitfield Description : GFX_DLDOCLK 300 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_GFX_DLDOCLK_300MClk_EnB_OFFSET            21
#define MiscClkCntl4_GFX_DLDOCLK_300MClk_EnB_WIDTH             1
#define MiscClkCntl4_GFX_DLDOCLK_300MClk_EnB_MASK              0x200000ul

/// Bitfield Description : CCX_DLDOCLK 600 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_CCX_DLDOCLK_600MClk_EnB_OFFSET            22
#define MiscClkCntl4_CCX_DLDOCLK_600MClk_EnB_WIDTH             1
#define MiscClkCntl4_CCX_DLDOCLK_600MClk_EnB_MASK              0x400000ul

/// Bitfield Description : CCX_DLDOCLK 300 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_CCX_DLDOCLK_300MClk_EnB_OFFSET            23
#define MiscClkCntl4_CCX_DLDOCLK_300MClk_EnB_WIDTH             1
#define MiscClkCntl4_CCX_DLDOCLK_300MClk_EnB_MASK              0x800000ul

/// Bitfield Description : PCIe_PHY_A Set On-Chip Refclk Global Dynamic DisableB.
/// PCIe_PHY_A set refclk can be enable globally by set this bit to 0.
/// Please refer to xB0[9], [24]/xB4 [9], [24]register regarding PCIe_PHY_A set configuration registers.
/// BIOS needs to program this bit to 1 when resume if PHY_A set is enabled for turn-off by ClkReqxB and SATA device status.
#define MiscClkCntl4_PCIe_PHY_A_Refclk_Global_Dynamic_EnB_OFFSET 24
#define MiscClkCntl4_PCIe_PHY_A_Refclk_Global_Dynamic_EnB_WIDTH  1
#define MiscClkCntl4_PCIe_PHY_A_Refclk_Global_Dynamic_EnB_MASK   0x1000000ul

/// Bitfield Description : Non Sticky bit.
#define MiscClkCntl4_Reserved_26_25_OFFSET                     25
#define MiscClkCntl4_Reserved_26_25_WIDTH                      2
#define MiscClkCntl4_Reserved_26_25_MASK                       0x6000000ul

/// Bitfield Description : GFX_DLDOCLK 400 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_GFX_DLDOCLK_400MClk_EnB_OFFSET            27
#define MiscClkCntl4_GFX_DLDOCLK_400MClk_EnB_WIDTH             1
#define MiscClkCntl4_GFX_DLDOCLK_400MClk_EnB_MASK              0x8000000ul

/// Bitfield Description : CCX_DLDOCLK 400 MHz Clock Output Enable/Disable.
#define MiscClkCntl4_CCX_DLDOCLK_400MClk_EnB_OFFSET            28
#define MiscClkCntl4_CCX_DLDOCLK_400MClk_EnB_WIDTH             1
#define MiscClkCntl4_CCX_DLDOCLK_400MClk_EnB_MASK              0x10000000ul

/// Bitfield Description : Low Power Display 600MHz Clock Output Enable/Disable.
#define MiscClkCntl4_Low_Power_Display_600MClk_EnB_OFFSET      29
#define MiscClkCntl4_Low_Power_Display_600MClk_EnB_WIDTH       1
#define MiscClkCntl4_Low_Power_Display_600MClk_EnB_MASK        0x20000000ul

/// Bitfield Description : Non Sticky bit.
#define MiscClkCntl4_LowPowerDisplay300MClkEnB_OFFSET          30
#define MiscClkCntl4_LowPowerDisplay300MClkEnB_WIDTH           1
#define MiscClkCntl4_LowPowerDisplay300MClkEnB_MASK            0x40000000ul

/// Bitfield Description : Non Sticky bit.
#define MiscClkCntl4_LowPowerDisplay400MClkEnB_OFFSET          31
#define MiscClkCntl4_LowPowerDisplay400MClkEnB_WIDTH           1
#define MiscClkCntl4_LowPowerDisplay400MClkEnB_MASK            0x80000000ul

/// MISC_004C
typedef union {
  struct {
    UINT32                                       GPP_CLK6_Reserved:4 ; ///<
    UINT32                                            Reserved_5_4:2 ; ///<
    UINT32                            TMDP_100M_Refclk_Driver_PWDN:1 ; ///<
    UINT32                              TMDP_100M_Refclk_Selection:2 ; ///<
    UINT32                             TMDP_48M_Refclk_Driver_PWDN:1 ; ///<
    UINT32                               TMDP_48M_Refclk_Selection:2 ; ///<
    UINT32                                          Reserved_15_12:4 ; ///<
    UINT32                                        SATA_Core_Clk_En:1 ; ///<
    UINT32                                        USB3_Host_Clk_En:1 ; ///<
    UINT32                                       USB31_Host_Clk_En:1 ; ///<
    UINT32                                          Reserved_19_19:1 ; ///<
    UINT32                                 GFX_DLDOCLK_600MClk_EnB:1 ; ///<
    UINT32                                 GFX_DLDOCLK_300MClk_EnB:1 ; ///<
    UINT32                                 CCX_DLDOCLK_600MClk_EnB:1 ; ///<
    UINT32                                 CCX_DLDOCLK_300MClk_EnB:1 ; ///<
    UINT32                    PCIe_PHY_A_Refclk_Global_Dynamic_EnB:1 ; ///<
    UINT32                                          Reserved_26_25:2 ; ///<
    UINT32                                 GFX_DLDOCLK_400MClk_EnB:1 ; ///<
    UINT32                                 CCX_DLDOCLK_400MClk_EnB:1 ; ///<
    UINT32                           Low_Power_Display_600MClk_EnB:1 ; ///<
    UINT32                               LowPowerDisplay300MClkEnB:1 ; ///<
    UINT32                               LowPowerDisplay400MClkEnB:1 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MiscClkCntl4_STRUCT;


//
// Register Name CGPLLCntrlReg5
// Description : PCIe_PHY_A1 Refclk Static Disable.
// When PHY_A1 does not use, PHY_A1 refclk can be turn-off by set this bit to 1.
//

// Address
#define SMN_CGPLLCntrlReg5_ADDRESS                             0x2d01eb0UL

/// Bitfield Description : PCIe_PHY_A0 Refclk SataMac Enable. When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according SATA Device status.
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_SataMac_En_OFFSET         0
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_SataMac_En_WIDTH          1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_SataMac_En_MASK           0x1ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port Enable Mask
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device0/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort_En_OFFSET        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort_En_WIDTH         7
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort_En_MASK          0xFEul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port0 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device0/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort0_En_OFFSET       1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort0_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort0_En_MASK         0x2ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port1 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device1/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort1_En_OFFSET       2
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort1_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort1_En_MASK         0x4ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port2 Enable
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device1/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort2_En_OFFSET       3
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort2_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort2_En_MASK         0x8ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port3 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device1/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort3_En_OFFSET       4
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort3_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort3_En_MASK         0x10ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port4 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device4/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort4_En_OFFSET       5
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort4_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort4_En_MASK         0x20ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port5 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device5/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort5_En_OFFSET       6
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort5_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort5_En_MASK         0x40ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Port6 Enable.
/// When set to 1, CLKGEN PHY_A0 Refclk can be enable/disable according external GPP device[6:0]/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)) or SATA device status.
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort6_En_OFFSET       7
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort6_En_WIDTH        1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_PCIePort6_En_MASK         0x80ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Dynamic EnableB.
/// When xB0[9:8]="00" and x4C[24]=0, PHY_A0 refclk is free running.
/// When xB0[9:8]="01" and x4C[24]=4, PHY_A0 refclk is controlled by xB0[7:0] and ClkReq[6:0]B/SATA_FCH_refclkgateoffdyn.
/// The xB0[7:0] bits are not necessarily mutually exclusive. More than one bit can be set, so the control condition should be that all "voters" need to agree that the PHY refclk branch can be shut down before it can be turned off.
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Dynamic_EnB_OFFSET 8
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Dynamic_EnB_WIDTH  1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Dynamic_EnB_MASK   0x100ul

/// Bitfield Description : PCIe_PHY_A0 Refclk Static Disable. When PHY_A0 does not use, PHY_A0 refclk can be turn-off by set this bit to 1.
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Static_Disable_OFFSET 9
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Static_Disable_WIDTH  1
#define CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Static_Disable_MASK   0x200ul

/// Bitfield Description :
#define CGPLLCntrlReg5_Reserved_15_10_OFFSET                   10
#define CGPLLCntrlReg5_Reserved_15_10_WIDTH                    6
#define CGPLLCntrlReg5_Reserved_15_10_MASK                     0xfc00ul

/// Bitfield Description : PCIe_PHY_A1 Refclk SataMac Enable. When set, CLKGEN PHY_A1 Refclk can be enable/disable according SATA Device status.
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_SataMac_En_OFFSET         16
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_SataMac_En_WIDTH          1
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_SataMac_En_MASK           0x10000ul

/// Bitfield Description : PCIe_PHY_A1 Refclk Port Enable Mask.
/// When set to 1, CLKGEN PHY_A1 Refclk can be enable/disable according external GPP device0/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_PCIePort_En_OFFSET        17
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_PCIePort_En_WIDTH         7
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_PCIePort_En_MASK          0xFE0000ul

/// Bitfield Description : PCIe_PHY_A1 Refclk Dynamic EnableB
/// When xB0[25:24]="00" and x4C[24]=0, PHY_A1 refclk is free running.
/// When xB0[25:24]="01" and x4C[24]=4, PHY_A1 refclk is controlled by xB0[23:16] and ClkReq[6:0]B/SATA_FCH_refclkgateoffdyn.
/// The xB0[23:16] bits are not necessarily mutually exclusive. More than one bit can be set, so the control condition should be that all voters need to agree that the PHY refclk branch can be shut down before it can be turned off.
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_OFFSET 24
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_WIDTH  1
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_MASK   0x1000000ul

/// Bitfield Description : PCIe_PHY_A1 Refclk Static Disable.
/// When PHY_A1 does not use, PHY_A1 refclk can be turn-off by set this bit to 1.
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Static_Disable_OFFSET 25
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Static_Disable_WIDTH  1
#define CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Static_Disable_MASK   0x2000000ul

/// Bitfield Description :
#define CGPLLCntrlReg5_Reserved_31_26_OFFSET                   26
#define CGPLLCntrlReg5_Reserved_31_26_WIDTH                    6
#define CGPLLCntrlReg5_Reserved_31_26_MASK                     0xfc000000ul

/// MISC_00B0
typedef union {
  struct {
    UINT32                                CLKGEN_PHY_A0_SataMac_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort0_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort1_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort2_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort3_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort4_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort5_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort6_En:1 ; ///<
    UINT32                        CLKGEN_PHY_A0_Refclk_Dynamic_EnB:1 ; ///<
    UINT32                     CLKGEN_PHY_A0_Refclk_Static_Disable:1 ; ///<
    UINT32                                          Reserved_15_10:6 ; ///<
    UINT32                                CLKGEN_PHY_A1_SataMac_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort0_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort1_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort2_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort3_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort4_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort5_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A1_PCIePort6_En:1 ; ///<
    UINT32                        CLKGEN_PHY_A1_Refclk_Dynamic_EnB:1 ; ///<
    UINT32                     CLKGEN_PHY_A1_Refclk_Static_Disable:1 ; ///<
    UINT32                                          Reserved_31_26:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} CGPLLCntrlReg5_STRUCT;

//
// Register Name CGPLLCntrlReg6
// Description : PCIe_PHY_A3_4 Refclk Static Disable.
// When PHY_A1 does not use, PHY_A3_4 refclk can be turn-off by set this bit to 1.
//

// Address
#define SMN_CGPLLCntrlReg6_ADDRESS                             0x2d01eb4UL

/// Bitfield Description : PCIe_PHY_A2 Refclk SataMac Enable. When set to 1, CLKGEN PHY_A2 Refclk can be enable/disable according SATA device status.
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_SataMac_En_OFFSET         0
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_SataMac_En_WIDTH          1
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_SataMac_En_MASK           0x1ul

/// Bitfield Description : PCIe_PHY_A2 Refclk Port Enable Mask
/// When set to 1, CLKGEN PHY_A2 Refclk can be enable/disable according external GPP device0/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_PCIePort_En_OFFSET        1
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_PCIePort_En_WIDTH         7
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_PCIePort_En_MASK          0xFEul

/// Bitfield Description : PCIe_PHY_A2 Refclk Dynamic EnableB.
/// When xB0[9:8]="00" and x4C[24]=0, PHY_A2 refclk is free running.
/// When xB0[9:8]="01" and x4C[24]=4, PHY_A2 refclk is controlled by xB0[7:0] and ClkReq[6:0]B/SATA_FCH_refclkgateoffdyn.
/// The xB0[7:0] bits are not necessarily mutually exclusive. More than one bit can be set, so the control condition should be that all voters need to agree that the PHY refclk branch can be shut down before it can be turned off.
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Dynamic_EnB_OFFSET 8
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Dynamic_EnB_WIDTH  1
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Dynamic_EnB_MASK   0x100ul

/// Bitfield Description : PCIe_PHY_A2 Refclk Static Disable. When PHY_A2 does not use, PHY_A0 refclk can be turn-off by set this bit to 1.
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Static_Disable_OFFSET 9
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Static_Disable_WIDTH  1
#define CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Static_Disable_MASK   0x200ul

/// Bitfield Description :
#define CGPLLCntrlReg6_Reserved_15_10_OFFSET                   10
#define CGPLLCntrlReg6_Reserved_15_10_WIDTH                    6
#define CGPLLCntrlReg6_Reserved_15_10_MASK                     0xfc00ul

/// Bitfield Description : PCIe_PHY_A3_4 Refclk SataMac Enable. When set to 1, CLKGEN PHY_A3_4 Refclk can be enable/disable according SATA Device status.
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_SataMac_En_OFFSET       16
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_SataMac_En_WIDTH        1
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_SataMac_En_MASK         0x10000ul

/// Bitfield Description : PCIe_PHY_A3_4 Refclk Port Enable Mask.
/// When set to 1, CLKGEN PHY_A3_4 Refclk can be enable/disable according external GPP device0/ClkReqB L1 status (ClkReqB = 0 (Refclk ON); 1 (Refclk OFF- L1 substate)).
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_PCIePort_En_OFFSET     17
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_PCIePort_En_WIDTH      7
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_PCIePort_En_MASK       0xFE0000ul

/// Bitfield Description : PCIe_PHY_A3_4 Refclk Dynamic EnableB.
/// When xB0[25:24]="00" and x4C[24]=0, PHY_A3_4 refclk is free running.
/// When xB0[25:24]="01" and x4C[24]=4, PHY_A3_4 refclk is controlled by xB0[23:16] and ClkReq[6:0]B/SATA_FCH_refclkgateoffdyn.
/// The xB0[23:16] bits are not necessarily mutually exclusive. More than one bit can be set, so the control condition should be that all voters need to agree that the PHY refclk branch can be shut down before it can be turned off.
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB_OFFSET 24
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB_WIDTH  1
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB_MASK   0x1000000ul

/// Bitfield Description : PCIe_PHY_A3_4 Refclk Static Disable.
/// When PHY_A1 does not use, PHY_A3_4 refclk can be turn-off by set this bit to 1.
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Static_Disable_OFFSET 25
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Static_Disable_WIDTH  1
#define CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Static_Disable_MASK   0x2000000ul

/// Bitfield Description :
#define CGPLLCntrlReg6_Reserved_31_26_OFFSET                   26
#define CGPLLCntrlReg6_Reserved_31_26_WIDTH                    6
#define CGPLLCntrlReg6_Reserved_31_26_MASK                     0xfc000000ul

/// MISC_00B4
typedef union {
  struct {
    UINT32                                CLKGEN_PHY_A2_SataMac_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort0_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort1_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A0_PCIePort2_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort3_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort4_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort5_En:1 ; ///<
    UINT32                              CLKGEN_PHY_A2_PCIePort6_En:1 ; ///<
    UINT32                        CLKGEN_PHY_A2_Refclk_Dynamic_EnB:1 ; ///<
    UINT32                     CLKGEN_PHY_A2_Refclk_Static_Disable:1 ; ///<
    UINT32                                          Reserved_15_10:6 ; ///<
    UINT32                              CLKGEN_PHY_A3_4_SataMac_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort0_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort1_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort2_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort3_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort4_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort5_En:1 ; ///<
    UINT32                            CLKGEN_PHY_A3_4_PCIePort6_En:1 ; ///<
    UINT32                      CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB:1 ; ///<
    UINT32                   CLKGEN_PHY_A3_4_Refclk_Static_Disable:1 ; ///<
    UINT32                                          Reserved_31_26:6 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} CGPLLCntrlReg6_STRUCT;

//
//  ACP_PGFSM_CONTROL
//
// Address
#define ACP_PGFSM_CTRL_ADDRESS                                     0x124141c
// Type
#define ACP_PGFSM_CTRL_TYPE                                         TYPE_SMN

#define ACP_PGFSM_CTRL_OFFSET                                              0
#define ACP_PGFSM_CTRL_Width                                               1
#define ACP_PGFSM_CTRL_Mask                                              0x1
#define Reserved31_1_OFFSET                                                1
#define Reserved31_1_Width                                                31
#define Reserved31_1_Mask                                         0xFFFFFFFE

typedef union {
   struct {
    UINT32                                                  ACP_PGFSM_CTRL:1; ///<
    UINT32                                                   Reserved31_1:31; ///<
 } Field;                                                                     ///<
  UINT32 Value;                                                               ///<
} ACP_PGFSM_CTRL_STRUCT;

//
//  ACP_PGFSM_STATUS
//
// Address
#define ACP_PGFSM_STATUS_ADDRESS                                   0x1241420
// Type
#define ACP_PGFSM_STATUS_TYPE                                       TYPE_SMN

#define ACP_PGFSM_STATUS_OFFSET                                            0
#define ACP_PGFSM_STATUS_Width                                             2
#define ACP_PGFSM_STATUS_Mask                                            0x3
#define ACP_PGFSM_Reserved31_3_OFFSET                                      2
#define ACP_PGFSM_Reserved31_3_Width                                      30
#define ACP_PGFSM_Reserved31_3_Mask                               0xFFFFFFFC

typedef union {
   struct {
    UINT32                                               ACP_PGFSM_STATUS:1; ///<
    UINT32                                                  Reserved31_3:30; ///<
  } Field;                                                                   ///<
  UINT32 Value;                                                              ///<
} ACP_PGFSM_STATUS_STRUCT;

//
// ACP_CONTROL
//
// Address
#define ACP_CONTROL_ADDRESS                                         0x1241004
// Type
#define ACP_CONTROL_TYPE                                             TYPE_SMN

#define ClkEn_OFFSET                                                        0
#define ClkEn_Width                                                         1
#define ClkEn_Mask                                                        0x1
#define ACP_CONTROL_Reserved31_1_OFFSET                                     1
#define ACP_CONTROL_Reserved31_1_Width                                     31
#define ACP_CONTROL_Reserved31_1_Mask                              0xFFFFFFFE

typedef union {
   struct {
    UINT32                                                      ACP_CONTROL:1; ///<
    UINT32                                                    Reserved31_1:31; ///<
  } Field;                                                                     ///<
  UINT32 Value;                                                                ///<
} ACP_CONTROL_STRUCT;

//
// ACP_SOFT_RESET
//
// Address
#define ACP_SOFT_RESET_ADDRESS                                      0x1241000
// Type
#define ACP_SOFT_RESET_TYPE                                          TYPE_SMN

#define SoftResetAud_OFFSET                                                 0
#define SoftResetAud_Width                                                  1
#define SoftResetAud_Mask                                                 0x1
#define SoftResetDMA_OFFSET                                                 1
#define SoftResetDMA_Width                                                  1
#define SoftResetDMA_Mask                                                 0x2
#define SoftResetDSP_OFFSET                                                 2
#define SoftResetDSP_Width                                                  1
#define SoftResetDSP_Mask                                                 0x4
#define ACP_SOFT_RESET_Reserved7_3_OFFSET                                   3
#define ACP_SOFT_RESET_Reserved7_3_Width                                    5
#define ACP_SOFT_RESET_Reserved7_3_Mask                                  0xF8
#define InternalSoftResetMode_OFFSET                                        8
#define InternalSoftResetMode_Width                                         1
#define InternalSoftResetMode_Mask                                      0x100
#define ACP_SOFT_RESET_Reserved15_9_OFFSET                                  9
#define ACP_SOFT_RESET_Reserved15_9_Width                                   7
#define ACP_SOFT_RESET_Reserved15_9_Mask                               0xFE00
#define SoftResetAudDone_OFFSET                                            16
#define SoftResetAudDone_Width                                              1
#define SoftResetAudDone_Mask                                         0x10000
#define SoftResetDMADone_OFFSET                                            17
#define SoftResetDMADone_Width                                              1
#define SoftResetDMADone_Mask                                         0x20000
#define SoftResetDSPDone_OFFSET                                            18
#define SoftResetDSPDone_Width                                              1
#define SoftResetDSPDone_Mask                                         0x40000
#define ACP_SOFT_RESET_Reserved31_19_OFFSET                                19
#define ACP_SOFT_RESET_Reserved31_19_Width                                 13
#define ACP_SOFT_RESET_Reserved31_19_Mask                          0xFFF80000

typedef union {
   struct {
    UINT32                                                     SoftResetAud:1 ; ///<
    UINT32                                                     SoftResetDMA:1 ; ///<
    UINT32                                                     SoftResetDSP:1 ; ///<
    UINT32                                       ACP_SOFT_RESET_Reserved7_3:5 ; ///<
    UINT32                                            InternalSoftResetMode:1 ; ///<
    UINT32                                      ACP_SOFT_RESET_Reserved15_9:7 ; ///<
    UINT32                                                 SoftResetAudDone:1 ; ///<
    UINT32                                                 SoftResetDMADone:1 ; ///<
    UINT32                                                 SoftResetDSPDone:1 ; ///<
    UINT32                                     ACP_SOFT_RESET_Reserved31_19:13; ///<
  } Field;                                                                      ///<
  UINT32 Value;                                                                 ///<
} ACP_SOFT_RESET_STRUCT;

//
// ACP_DYNAMIC_CG_MASTER_CONTROL
//
// Address
#define ACP_DYNAMIC_CG_MASTER_CONTROL_ADDRESS                       0x1241010
// Type
#define ACP_DYNAMIC_CG_MASTER_CONTROL_TYPE                           TYPE_SMN

#define ACP_DYNAMIC_CG_Disable_OFFSET                                       0
#define ACP_DYNAMIC_CG_Disable_Width                                       16
#define ACP_DYNAMIC_CG_Disable_Mask                                    0xFFFF
#define ACP_Course_CG_OFFSET                                               16
#define ACP_Course_CG_Width                                                16
#define ACP_Course_CG_Mask                                         0xffff0000

typedef union {
   struct {
    UINT32                                          ACP_DYNAMIC_CG_Disable:16 ; ///<
    UINT32                                                   ACP_Course_CG:16 ; ///<
  } Field;                                                                      ///<
  UINT32 Value;                                                                 ///<
} ACP_DYNAMIC_CG_MASTER_CONTROL_STRUCT;

//
// ACP_PGMEM_CTRL
//
// Address
#define ACP_PGMEM_CTRL_ADDRESS                                      0x12418c0
// Type
#define ACP_PGMEM_CTRL_TYPE                                          TYPE_SMN

#define ACP_PGMEM_DEEP_SLEEP_OFFSET                                         0
#define ACP_PGMEM_DEEP_SLEEP_Width                                         12
#define ACP_PGMEM_DEEP_SLEEP_Mask                                       0xFFF
#define ACP_PGMEM_SHUT_DOWN_OFFSET                                         16
#define ACP_PGMEM_SHUT_DOWN_Width                                          12
#define ACP_PGMEM_SHUT_DOWN_Mask                                   0x0fff0000

typedef union {
   struct {
    UINT32                                           ACP_PGMEM_DEEP_SLEEP:16 ; ///<
    UINT32                                            ACP_PGMEM_SHUT_DOWN:16 ; ///<
  } Field;                                                                     ///<
  UINT32 Value;                                                                ///<
} ACP_PGMEM_CTRL_STRUCT;

//
// ACP_MEM_PG_STS
//
// Address
#define ACP_MEM_PG_STS_ADDRESS                                      0x12418cc
// Type
#define ACP_MEM_PG_STS_TYPE                                          TYPE_SMN

#define ACP_MEM_READY_FOR_OPERATION_OFFSET                                  0
#define ACP_MEM_READY_FOR_OPERATION_Width                                  11
#define ACP_MEM_READY_FOR_OPERATION_Mask                                0xFFF

typedef union {
   struct {
    UINT32                                      ACP_MEM_READY_FOR_OPERATION:12; ///<
  } Field;                                                                      ///<
  UINT32 Value;                                                                 ///<
} ACP_MEM_PG_STS_STRUCT;

//
// RSMU_HARD_RESETB_SATA
//
// Address
#define RSMU_HARD_RESETB_SATA_ADDRESS                                0x10a8008
// Type
#define RSMU_HARD_RESETB_SATA_TYPE                                    TYPE_SMN

#define RSMU_HARD_RESETB_OFFSET                                              0
#define RSMU_HARD_RESETB_Width                                               2
#define RSMU_HARD_RESETB_Mask                                              0x3
#define RSMU_MASTER_HARD_RESET_FENCE_ENABLE_OFFSET                           2
#define RSMU_MASTER_HARD_RESET_FENCE_ENABLE_Width                            2
#define RSMU_MASTER_HARD_RESET_FENCE_ENABLE_Mask                           0xc
#define RSMU_HARD_RESETB_SATA_Reserved4_OFFSET                               4
#define RSMU_HARD_RESETB_SATA_Reserved4_Width                                1
#define RSMU_HARD_RESETB_SATA_Reserved4_Mask                              0x10
#define RSMU_SLAVE_HARD_RESET_TIMEOUT_ENABLE_OFFSET                          5
#define RSMU_SLAVE_HARD_RESET_TIMEOUT_ENABLE_Width                           2
#define RSMU_SLAVE_HARD_RESET_TIMEOUT_ENABLE_Mask                         0x60
#define RSMU_HARD_RESETB_SATA_Reserved7_31_OFFSET                            7
#define RSMU_HARD_RESETB_SATA_Reserved7_31_Width                            25
#define RSMU_HARD_RESETB_SATA_Reserved7_31_Mask                     0xFFFFFF80

typedef union {
   struct {
    UINT32                                                  RSMU_HARD_RESETB:2; ///<
    UINT32                               RSMU_MASTER_HARD_RESET_FENCE_ENABLE:2; ///<
    UINT32                                   RSMU_HARD_RESETB_SATA_Reserved4:1; ///<
    UINT32                              RSMU_SLAVE_HARD_RESET_TIMEOUT_ENABLE:2; ///<
    UINT32                               RSMU_HARD_RESETB_SATA_Reserved7_31:25; ///<
  } Field;                                                                      ///<
  UINT32 Value;                                                                 ///<
} RSMU_HARD_RESETB_SATA_STRUCT;


///
///RV2 Registers
///

//
// SHUBCLK_DPM_CTRL
//
// Address
#define SHUBCLK_DPM_CTRL_ADDRESS                                     0x1403c4c
// Type
#define SHUBCLK_DPM_CTRL_TYPE                                         TYPE_SMN

#define SHUBCLK_DPM_MODE_OFFSET                                              0
#define SHUBCLK_DPM_MODE_Width                                               1
#define SHUBCLK_DPM_MODE_Mask                                              0x1
#define SHUBCLK_DPM_ENABLE_OFFSET                                            1
#define SHUBCLK_DPM_ENABLE_Width                                             1
#define SHUBCLK_DPM_ENABLE_Mask                                            0x2
#define SHUBCLK_DPM_DMAWR_QUANT_OFFSET                                       2
#define SHUBCLK_DPM_DMAWR_QUANT_Width                                        8
#define SHUBCLK_DPM_DMAWR_QUANT_Mask                                     0x3fc
#define SHUBCLK_DPM_DMARD_QUANT_OFFSET                                      10
#define SHUBCLK_DPM_DMARD_QUANT_Width                                        8
#define SHUBCLK_DPM_DMARD_QUANT_Mask                                   0x3fc00
#define SHUBCLK_DPM_CLEAR_OFFSET                                            18
#define SHUBCLK_DPM_CLEAR_Width                                              1
#define SHUBCLK_DPM_CLEAR_Mask                                         0x40000

typedef union {
   struct {
    UINT32                                                  SHUBCLK_DPM_MODE:1; ///<
    UINT32                                                SHUBCLK_DPM_ENABLE:1; ///<
    UINT32                                           SHUBCLK_DPM_DMAWR_QUANT:8; ///<
    UINT32                                           SHUBCLK_DPM_DMARD_QUANT:8; ///<
    UINT32                                                 SHUBCLK_DPM_CLEAR:1; ///<
  } Field;                                                                      ///<
  UINT32 Value;                                                                 ///<
} SHUBCLK_DPM_CTRL_STRUCT;

//
// SHUBCLK_DPM_RD_WEIGHT
//
// Address
#define SHUBCLK_DPM_RD_WEIGHT_ADDRESS                                0x1403c54
// Type
#define SHUBCLK_DPM_RD_WEIGHT_TYPE                                    TYPE_SMN

#define SHUBCLK_DPM_RD_WEIGHT_4B_OFFSET                                      0
#define SHUBCLK_DPM_RD_WEIGHT_4B_Width                                       5
#define SHUBCLK_DPM_RD_WEIGHT_4B_Mask                                     0x1f
#define SHUBCLK_DPM_RD_WEIGHT_8B_OFFSET                                      5
#define SHUBCLK_DPM_RD_WEIGHT_8B_Width                                       5
#define SHUBCLK_DPM_RD_WEIGHT_8B_Mask                                    0x3e0
#define SHUBCLK_DPM_RD_WEIGHT_16B_OFFSET                                    10
#define SHUBCLK_DPM_RD_WEIGHT_16B_Width                                      5
#define SHUBCLK_DPM_RD_WEIGHT_16B_Mask                                  0x7c00
#define SHUBCLK_DPM_RD_WEIGHT_32B_OFFSET                                    15
#define SHUBCLK_DPM_RD_WEIGHT_32B_Width                                      5
#define SHUBCLK_DPM_RD_WEIGHT_32B_Mask                                 0xf8000
#define SHUBCLK_DPM_RD_WEIGHT_64B_OFFSET                                    20
#define SHUBCLK_DPM_RD_WEIGHT_64B_Width                                      5
#define SHUBCLK_DPM_RD_WEIGHT_64B_Mask                               0x1f00000

typedef union {
   struct {
    UINT32                                        SHUBCLK_DPM_RD_WEIGHT_4B:5; ///<
    UINT32                                        SHUBCLK_DPM_RD_WEIGHT_8B:5; ///<
    UINT32                                       SHUBCLK_DPM_RD_WEIGHT_16B:5; ///<
    UINT32                                       SHUBCLK_DPM_RD_WEIGHT_32B:5; ///<
    UINT32                                       SHUBCLK_DPM_RD_WEIGHT_64B:5; ///<
  } Field;                                                                    ///<
  UINT32 Value;                                                               ///<
} SHUBCLK_DPM_RD_WEIGHT_STRUCT;


//
// SHUBCLK_DPM_WR_WEIGHT
//
//
// Address
#define SHUBCLK_DPM_WR_WEIGHT_ADDRESS                                0x1403c50
// Type
#define SHUBCLK_DPM_WR_WEIGHT_TYPE                                    TYPE_SMN

#define SHUBCLK_DPM_WR_WEIGHT_4B_OFFSET                                      0
#define SHUBCLK_DPM_WR_WEIGHT_4B__Width                                      5
#define SHUBCLK_DPM_WR_WEIGHT_4B__Mask                                    0x1f
#define SHUBCLK_DPM_WR_WEIGHT_8B_OFFSET                                      5
#define SHUBCLK_DPM_WR_WEIGHT_8B_Width                                       5
#define SHUBCLK_DPM_WR_WEIGHT_8B_Mask                                    0x3e0
#define SHUBCLK_DPM_WR_WEIGHT_16B_OFFSET                                    10
#define SHUBCLK_DPM_WR_WEIGHT_16B_Width                                      5
#define SHUBCLK_DPM_WR_WEIGHT_16B_Mask                                  0x7c00
#define SHUBCLK_DPM_WR_WEIGHT_32B_OFFSET                                    15
#define SHUBCLK_DPM_WR_WEIGHT_32B_Width                                      5
#define SHUBCLK_DPM_WR_WEIGHT_32B_Mask                                 0xf8000
#define SHUBCLK_DPM_WR_WEIGHT_64B_OFFSET                                    20
#define SHUBCLK_DPM_WR_WEIGHT_64B_Width                                      5
#define SHUBCLK_DPM_WR_WEIGHT_64B_Mask                               0x1f00000

typedef union {
   struct {
    UINT32                                         SHUBCLK_DPM_WR_WEIGHT_4B:5; ///<
    UINT32                                         SHUBCLK_DPM_WR_WEIGHT_8B:5; ///<
    UINT32                                        SHUBCLK_DPM_WR_WEIGHT_16B:5; ///<
    UINT32                                        SHUBCLK_DPM_WR_WEIGHT_32B:5; ///<
    UINT32                                        SHUBCLK_DPM_WR_WEIGHT_64B:5; ///<
  } Field;                                                                     ///<
  UINT32 Value;                                                                ///<
} SHUBCLK_DPM_WR_WEIGHT_STRUCT;


//
// SATA_GLOBAL_OPTION
//
//
// Address
#define SATA_GLOBAL_OPTION_ADDRESS                                   0x3101800
// Type
#define SATA_GLOBAL_OPTION_TYPE                                       TYPE_SMN

#define GLOBAL_OPTION_DMA_Axim_Idle_OFFSET                                   1
#define GLOBAL_OPTION_DMA_Axim_Idle_Width                                    1
#define GLOBAL_OPTION_DMA_Axim_Idle_Mask                                   0x2
#define GLOBAL_OPTION_Flr_Rst_OFFSET                                         2
#define GLOBAL_OPTION_Flr_Rst_Width                                          1
#define GLOBAL_OPTION_Flr_Rst_Mask                                         0x4
#define PCS_PHY_global_SW_Reset_OFFSET                                       3
#define PCS_PHY_global_SW_Reset_Width                                        1
#define PCS_PHY_global_SW_Reset_Mask                                       0x8
#define GLOBAL_OPTION_Reserved2_OFFSET                                       4
#define GLOBAL_OPTION_Reserved2_Width                                        1
#define GLOBAL_OPTION_Reserved2_Mask                                      0x10
#define En_Performance_enhancement_OFFSET                                    5
#define En_Performance_enhancement_Width                                     1
#define En_Performance_enhancement_Mask                                   0x20
#define cfg_flr_oob_enable_OFFSET                                            6
#define cfg_flr_oob_enable_Width                                             1
#define cfg_flr_oob_enable_Mask                                           0x40
#define d3hot_d0_rst_OFFSET                                                  7
#define d3hot_d0_rst_Width                                                   1
#define d3hot_d0_rst_Mask                                                 0x80
#define GLOBAL_OPTION_Reserved3_OFFSET                                       8
#define GLOBAL_OPTION_Reserved3_Width                                        1
#define GLOBAL_OPTION_Reserved3_Mask                                     0x100
#define Dis_fix_databurstend_OFFSET                                          9
#define Dis_fix_databurstend_Width                                           1
#define Dis_fix_databurstend_Mask                                        0x200
#define Dis_fix_SB02003_B_OFFSET                                            10
#define Dis_fix_SB02003_B_Width                                              1
#define Dis_fix_SB02003_B_Mask                                           0x400
#define Dis_fix_SB02003_C_OFFSET                                            11
#define Dis_fix_SB02003_C_Width                                              1
#define Dis_fix_SB02003_C_Mask                                           0x800
#define SATA_PXIS_FIX_DISABLE_OFFSET                                        12
#define SATA_PXIS_FIX_DISABLE_Width                                          1
#define SATA_PXIS_FIX_DISABLE_Mask                                      0x1000
#define Dis_AHCI_Prefetch_OFFSET                                            13
#define Dis_AHCI_Prefetch_Width                                              1
#define Dis_AHCI_Prefetch_Mask                                          0x2000
#define En_Force_OFS_Zero_OFFSET                                            14
#define En_Force_OFS_Zero_Width                                              1
#define En_Force_OFS_Zero_Mask                                          0x4000
#define Sata_Global_Option_Reserved_15_OFFSET                               15
#define Sata_Global_Option_Reserved_15_Width                                 1
#define Sata_Global_Option_Reserved_15_Mask                             0x8000
#define Shut_Down_Port0_OFFSET                                              16
#define Shut_Down_Port0_Width                                                1
#define Shut_Down_Port0_Mask                                           0x10000
#define Shut_Down_Port1_OFFSET                                              17
#define Shut_Down_Port1_Width                                                1
#define Shut_Down_Port1_Mask                                           0x20000
#define Shut_Down_Reserved_23_18_OFFSET                                     18
#define Shut_Down_Reserved_23_18_Width                                       6
#define Shut_Down_Reserved_23_18_Mask                                 0xFC0000
#define Set_TFSts_to_7f_P_OFFSET                                            24
#define Set_TFSts_to_7f_P_Width                                              2
#define Set_TFSts_to_7f_P_Mask                                      0x03000000
#define Set_TFSts_to_7f_P_Reserved_31_26_OFFSET                             26
#define Set_TFSts_to_7f_P_Reserved_31_26_Width                               6
#define Set_TFSts_to_7f_P_Reserved_31_26_Mask                       0xFC000000

typedef union {
   struct {
    UINT32                                       GLOBAL_OPTION_DMA_Axim_Idle:1; ///<
    UINT32                                             GLOBAL_OPTION_Flr_Rst:1; ///<
    UINT32                                           PCS_PHY_global_SW_Reset:1; ///<
    UINT32                                           GLOBAL_OPTION_Reserved2:1; ///<
    UINT32                                        En_Performance_enhancement:1; ///<
    UINT32                                                cfg_flr_oob_enable:1; ///<
    UINT32                                                      d3hot_d0_rst:1; ///<
    UINT32                                           GLOBAL_OPTION_Reserved3:1; ///<
    UINT32                                              Dis_fix_databurstend:1; ///<
    UINT32                                                 Dis_fix_SB02003_B:1; ///<
    UINT32                                                 Dis_fix_SB02003_C:1; ///<
    UINT32                                             SATA_PXIS_FIX_DISABLE:1; ///<
    UINT32                                                 Dis_AHCI_Prefetch:1; ///<
    UINT32                                                 En_Force_OFS_Zero:1; ///<
    UINT32                                    Sata_Global_Option_Reserved_15:1; ///<
    UINT32                                                   Shut_Down_Port0:1; ///<
    UINT32                                                   Shut_Down_Port1:1; ///<
    UINT32                                          Shut_Down_Reserved_23_18:6; ///<
    UINT32                                                 Set_TFSts_to_7f_P:2; ///<
    UINT32                                  Set_TFSts_to_7f_P_Reserved_31_26:6; ///<
  } Field;                                                                     ///<
  UINT32 Value;                                                                ///<
} SATA_GLOBAL_OPTION_STRUCT;

//
//RAVEN Family OPN definition values
//
#define RV1_SINGLE_SOURCE   0
#define RV1_B4_DUAL_SOURCE  2
#define RV2_SINGLE_SOURCE   1
#define RV2_DUAL_SOURCE     3

//
//PCIe strap index offset values for Raven
//
#define FUSE_INSTANCE_MULTIPLIER    0x1000
#define FUSE_ACCESS_LOCATION        0xFFFE0000

#define STRAP_BIF_SUBSYS_VEN_ID_OFFSET_RV1                                              0x82
#define STRAP_BIF_SUBSYS_VEN_ID_OFFSET_RV2                                              0x85
#define STRAP_BIF_SUBSYS_ID_OFFSET_RV1                                                  0x83
#define STRAP_BIF_SUBSYS_ID_OFFSET_RV2                                                  0x86
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV1 0x88
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV2 0x8B
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV1   0x89
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV2   0x8C
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_OFFSET_RV1      0x8A
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_OFFSET_RV2      0x8D
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_OFFSET_RV1        0x8B
#define STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_OFFSET_RV2        0x8E
#define STRAP_BIF_PM_SUPPORT_A_INDEX_RV1                                                0xC3 
#define STRAP_BIF_PM_SUPPORT_A_INDEX_RV2                                                0xC6
#define STRAP_BIF_L1_EXIT_LATENCY_A_OFFSET_RV1                                          0xC4
#define STRAP_BIF_L1_EXIT_LATENCY_A_OFFSET_RV2                                          0xC7
#define STRAP_BIF_L0S_EXIT_LATENCY_A_OFFSET_RV1                                         0xC5
#define STRAP_BIF_L0S_EXIT_LATENCY_A_OFFSET_RV2                                         0xC8


#endif

