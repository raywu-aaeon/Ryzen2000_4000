/* $NoKeywords:$ */
/**
 * @file
 *
 *  Register definitions
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

#ifndef _GNBREGISTERSCOMMON_H_
#define _GNBREGISTERSCOMMON_H_


#define  TYPE_D0F0                  0x1
#define  TYPE_D0F0x64               0x2
#define  TYPE_D0F0x98               0x3
#define  TYPE_D0F0xE4               0x5
#define  TYPE_DxF0                  0x6
#define  TYPE_DxF0xE4               0x7
#define  TYPE_D18F1                 0xb
#define  TYPE_D18F2                 0xc
#define  TYPE_D18F3                 0xd
#define  TYPE_MSR                   0x10
#define  TYPE_D1F0                  0x11
#define  TYPE_GMM                   0x12
#define  D18F2x9C  0xe
#define  GMM       0x11

#ifndef WRAP_SPACE1
  #define  WRAP_SPACE1(w, x)   (0x01300000 | (w << 16) | (x))
#endif
#ifndef WRAP_SPACE2
  #define  WRAP_SPACE2(w, x)   (0x01500000 | (w << 16) | (x))
#endif
#ifndef WRAP_SPACE
//0~C  45,46,50, 80,  800~805, 813, 900~905, 913, A00~A05, A13, B00~B05, B13, C00~C05, C13  8030~8036   F000~F004
#define  WRAP_SPACE(w, x)   (( (x <= 0xC) || (x == 0x45) || (x == 0x46) || (x == 0x50) || (x == 0x80) || \
                              ((x >= 0x800) && (x <= 0x805)) || (x == 0x813) || \
                              ((x >= 0x900) && (x <= 0x905)) || (x == 0x913) || \
                              ((x >= 0xA00) && (x <= 0xA05)) || (x == 0xA13) || \
                              ((x >= 0xB00) && (x <= 0xB05)) || (x == 0xB13) || \
                              ((x >= 0xC00) && (x <= 0xC05)) || (x == 0xC13) || \
                              ((x >= 0x8030) && (x <= 0x8036)) || \
                              ((x >= 0xF000) && (x <= 0xF004)) ) ? WRAP_SPACE2(w, x) : WRAP_SPACE1(w, x))
#endif

#ifndef CORE_SPACE
  #define  CORE_SPACE(c, x)   (0x00010000 | (c << 24) | (x))
#endif
#ifndef PHY_SPACE
  #define  PHY_SPACE(w, p, x) (0x00200000 | ((p + 1) << 24) | (w << 16) | (x))
#endif
#ifndef  PIF_SPACE
  #define  PIF_SPACE(w, p, x) (0x00100000 | ((p + 1) << 24) | (w << 16) | (x))
#endif
// **** D0F0x00 Register Definition ****
// Address
#define D0F0x00_ADDRESS                                         0x0

// Type
#define D0F0x00_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x00_VendorID_OFFSET                                 0
#define D0F0x00_VendorID_WIDTH                                  16
#define D0F0x00_VendorID_MASK                                   0xffff
#define D0F0x00_DeviceID_OFFSET                                 16
#define D0F0x00_DeviceID_WIDTH                                  16
#define D0F0x00_DeviceID_MASK                                   0xffff0000

/// D0F0x00
typedef union {
  struct {                                                              ///<
    UINT32                                                 VendorID:16; ///<
    UINT32                                                 DeviceID:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x00_STRUCT;

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
#define D0F0x04_SpecialCycleEn_OFFSET                           3
#define D0F0x04_SpecialCycleEn_WIDTH                            1
#define D0F0x04_SpecialCycleEn_MASK                             0x8
#define D0F0x04_MemWriteInvalidateEn_OFFSET                     4
#define D0F0x04_MemWriteInvalidateEn_WIDTH                      1
#define D0F0x04_MemWriteInvalidateEn_MASK                       0x10
#define D0F0x04_PalSnoopEn_OFFSET                               5
#define D0F0x04_PalSnoopEn_WIDTH                                1
#define D0F0x04_PalSnoopEn_MASK                                 0x20
#define D0F0x04_ParityErrorEn_OFFSET                            6
#define D0F0x04_ParityErrorEn_WIDTH                             1
#define D0F0x04_ParityErrorEn_MASK                              0x40
#define D0F0x04_Reserved_7_7_OFFSET                             7
#define D0F0x04_Reserved_7_7_WIDTH                              1
#define D0F0x04_Reserved_7_7_MASK                               0x80
#define D0F0x04_SerrEn_OFFSET                                   8
#define D0F0x04_SerrEn_WIDTH                                    1
#define D0F0x04_SerrEn_MASK                                     0x100
#define D0F0x04_FastB2BEn_OFFSET                                9
#define D0F0x04_FastB2BEn_WIDTH                                 1
#define D0F0x04_FastB2BEn_MASK                                  0x200
#define D0F0x04_Reserved_19_10_OFFSET                           10
#define D0F0x04_Reserved_19_10_WIDTH                            10
#define D0F0x04_Reserved_19_10_MASK                             0xffc00
#define D0F0x04_CapList_OFFSET                                  20
#define D0F0x04_CapList_WIDTH                                   1
#define D0F0x04_CapList_MASK                                    0x100000
#define D0F0x04_PCI66En_OFFSET                                  21
#define D0F0x04_PCI66En_WIDTH                                   1
#define D0F0x04_PCI66En_MASK                                    0x200000
#define D0F0x04_Reserved_22_22_OFFSET                           22
#define D0F0x04_Reserved_22_22_WIDTH                            1
#define D0F0x04_Reserved_22_22_MASK                             0x400000
#define D0F0x04_FastBackCapable_OFFSET                          23
#define D0F0x04_FastBackCapable_WIDTH                           1
#define D0F0x04_FastBackCapable_MASK                            0x800000
#define D0F0x04_Reserved_24_24_OFFSET                           24
#define D0F0x04_Reserved_24_24_WIDTH                            1
#define D0F0x04_Reserved_24_24_MASK                             0x1000000
#define D0F0x04_DevselTiming_OFFSET                             25
#define D0F0x04_DevselTiming_WIDTH                              2
#define D0F0x04_DevselTiming_MASK                               0x6000000
#define D0F0x04_SignalTargetAbort_OFFSET                        27
#define D0F0x04_SignalTargetAbort_WIDTH                         1
#define D0F0x04_SignalTargetAbort_MASK                          0x8000000
#define D0F0x04_ReceivedTargetAbort_OFFSET                      28
#define D0F0x04_ReceivedTargetAbort_WIDTH                       1
#define D0F0x04_ReceivedTargetAbort_MASK                        0x10000000
#define D0F0x04_ReceivedMasterAbort_OFFSET                      29
#define D0F0x04_ReceivedMasterAbort_WIDTH                       1
#define D0F0x04_ReceivedMasterAbort_MASK                        0x20000000
#define D0F0x04_SignaledSystemError_OFFSET                      30
#define D0F0x04_SignaledSystemError_WIDTH                       1
#define D0F0x04_SignaledSystemError_MASK                        0x40000000
#define D0F0x04_ParityErrorDetected_OFFSET                      31
#define D0F0x04_ParityErrorDetected_WIDTH                       1
#define D0F0x04_ParityErrorDetected_MASK                        0x80000000

/// D0F0x04
typedef union {
  struct {                                                              ///<
    UINT32                                               IoAccessEn:1 ; ///<
    UINT32                                              MemAccessEn:1 ; ///<
    UINT32                                              BusMasterEn:1 ; ///<
    UINT32                                           SpecialCycleEn:1 ; ///<
    UINT32                                     MemWriteInvalidateEn:1 ; ///<
    UINT32                                               PalSnoopEn:1 ; ///<
    UINT32                                            ParityErrorEn:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                                   SerrEn:1 ; ///<
    UINT32                                                FastB2BEn:1 ; ///<
    UINT32                                           Reserved_19_10:10; ///<
    UINT32                                                  CapList:1 ; ///<
    UINT32                                                  PCI66En:1 ; ///<
    UINT32                                           Reserved_22_22:1 ; ///<
    UINT32                                          FastBackCapable:1 ; ///<
    UINT32                                           Reserved_24_24:1 ; ///<
    UINT32                                             DevselTiming:2 ; ///<
    UINT32                                        SignalTargetAbort:1 ; ///<
    UINT32                                      ReceivedTargetAbort:1 ; ///<
    UINT32                                      ReceivedMasterAbort:1 ; ///<
    UINT32                                      SignaledSystemError:1 ; ///<
    UINT32                                      ParityErrorDetected:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x04_STRUCT;

// **** D0F0x60 Register Definition ****
// Address
#define D0F0x60_ADDRESS                                         0x60

// Type
#define D0F0x60_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x60_MiscIndAddr_OFFSET                              0
#define D0F0x60_MiscIndAddr_WIDTH                               7
#define D0F0x60_MiscIndAddr_MASK                                0x7f
#define D0F0x60_MiscIndWrEn_OFFSET                              7
#define D0F0x60_MiscIndWrEn_WIDTH                               1
#define D0F0x60_MiscIndWrEn_MASK                                0x80
#define D0F0x60_Reserved_31_8_OFFSET                            8
#define D0F0x60_Reserved_31_8_WIDTH                             24
#define D0F0x60_Reserved_31_8_MASK                              0xffffff00

/// D0F0x60
typedef union {
  struct {                                                              ///<
    UINT32                                              MiscIndAddr:7 ; ///<
    UINT32                                              MiscIndWrEn:1 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x60_STRUCT;

// **** D0F0x64 Register Definition ****
// Address
#define D0F0x64_ADDRESS                                         0x64

// Type
#define D0F0x64_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x64_MiscIndData_OFFSET                              0
#define D0F0x64_MiscIndData_WIDTH                               32
#define D0F0x64_MiscIndData_MASK                                0xffffffff

/// D0F0x64
typedef union {
  struct {                                                              ///<
    UINT32                                              MiscIndData:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_STRUCT;



// **** D0F0x90 Register Definition ****
// Address
#define D0F0x90_ADDRESS                                         0x90

// Type
#define D0F0x90_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x90_Reserved_22_0_OFFSET                            0
#define D0F0x90_Reserved_22_0_WIDTH                             23
#define D0F0x90_Reserved_22_0_MASK                              0x7fffff
#define D0F0x90_TopOfDram_OFFSET                                23
#define D0F0x90_TopOfDram_WIDTH                                 9
#define D0F0x90_TopOfDram_MASK                                  0xff800000

/// D0F0x90
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_22_0:23; ///<
    UINT32                                                TopOfDram:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x90_STRUCT;


// **** D0F0x94 Register Definition ****
// Address
#define D0F0x94_ADDRESS                                         0x94

// Type
#define D0F0x94_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x94_OrbIndAddr_OFFSET                               0
#define D0F0x94_OrbIndAddr_WIDTH                                7
#define D0F0x94_OrbIndAddr_MASK                                 0x7f
#define D0F0x94_Reserved_31_7_OFFSET                            7
#define D0F0x94_Reserved_31_7_WIDTH                             25
#define D0F0x94_Reserved_31_7_MASK                              0xffffff80

/// D0F0x94
typedef union {
  struct {                                                              ///<
    UINT32                                               OrbIndAddr:7 ; ///<
    UINT32                                            Reserved_31_7:25; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x94_STRUCT;


// **** D0F0xE0 Register Definition ****
// Address
#define D0F0xE0_ADDRESS                                         0xe0

// Type
#define D0F0xE0_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xE0_PcieIndxAddr_OFFSET                             0
#define D0F0xE0_PcieIndxAddr_WIDTH                              16
#define D0F0xE0_PcieIndxAddr_MASK                               0xffff
#define D0F0xE0_FrameType_OFFSET                                16
#define D0F0xE0_FrameType_WIDTH                                 8
#define D0F0xE0_FrameType_MASK                                  0xff0000
#define D0F0xE0_BlockSelect_OFFSET                              24
#define D0F0xE0_BlockSelect_WIDTH                               8
#define D0F0xE0_BlockSelect_MASK                                0xff000000

/// D0F0xE0
typedef union {
  struct {                                                              ///<
    UINT32                                             PcieIndxAddr:16; ///<
    UINT32                                                FrameType:8 ; ///<
    UINT32                                              BlockSelect:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE0_STRUCT;


// **** D18F3x15C Register Definition ****
// Address
#define D18F3x15C_ADDRESS                                       0x15c

// Type
#define D18F3x15C_TYPE                                          TYPE_D18F3
// Field Data
#define D18F3x15C_SclkVidLevel0_OFFSET                          0
#define D18F3x15C_SclkVidLevel0_WIDTH                           7
#define D18F3x15C_SclkVidLevel0_MASK                            0x7f
#define D18F3x15C_Reserved_7_7_OFFSET                           7
#define D18F3x15C_Reserved_7_7_WIDTH                            1
#define D18F3x15C_Reserved_7_7_MASK                             0x80
#define D18F3x15C_SclkVidLevel1_OFFSET                          8
#define D18F3x15C_SclkVidLevel1_WIDTH                           7
#define D18F3x15C_SclkVidLevel1_MASK                            0x7f00
#define D18F3x15C_Reserved_15_15_OFFSET                         15
#define D18F3x15C_Reserved_15_15_WIDTH                          1
#define D18F3x15C_Reserved_15_15_MASK                           0x8000
#define D18F3x15C_SclkVidLevel2_OFFSET                          16
#define D18F3x15C_SclkVidLevel2_WIDTH                           7
#define D18F3x15C_SclkVidLevel2_MASK                            0x7f0000
#define D18F3x15C_Reserved_23_23_OFFSET                         23
#define D18F3x15C_Reserved_23_23_WIDTH                          1
#define D18F3x15C_Reserved_23_23_MASK                           0x800000
#define D18F3x15C_SclkVidLevel3_OFFSET                          24
#define D18F3x15C_SclkVidLevel3_WIDTH                           7
#define D18F3x15C_SclkVidLevel3_MASK                            0x7f000000
#define D18F3x15C_Reserved_31_31_OFFSET                         31
#define D18F3x15C_Reserved_31_31_WIDTH                          1
#define D18F3x15C_Reserved_31_31_MASK                           0x80000000

/// D18F3x15C
typedef union {
  struct {                                                              ///<
    UINT32                                            SclkVidLevel0:7 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                            SclkVidLevel1:7 ; ///<
    UINT32                                           Reserved_15_15:1 ; ///<
    UINT32                                            SclkVidLevel2:7 ; ///<
    UINT32                                           Reserved_23_23:1 ; ///<
    UINT32                                            SclkVidLevel3:7 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F3x15C_STRUCT;

// **** D18F3x17C Register Definition ****

// **** DxF0x04 Register Definition ****
// Address
#define DxF0x04_ADDRESS                                         0x4

// Type
#define DxF0x04_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x04_IoAccessEn_OFFSET                               0
#define DxF0x04_IoAccessEn_WIDTH                                1
#define DxF0x04_IoAccessEn_MASK                                 0x1
#define DxF0x04_MemAccessEn_OFFSET                              1
#define DxF0x04_MemAccessEn_WIDTH                               1
#define DxF0x04_MemAccessEn_MASK                                0x2
#define DxF0x04_BusMasterEn_OFFSET                              2
#define DxF0x04_BusMasterEn_WIDTH                               1
#define DxF0x04_BusMasterEn_MASK                                0x4
#define DxF0x04_SpecialCycleEn_OFFSET                           3
#define DxF0x04_SpecialCycleEn_WIDTH                            1
#define DxF0x04_SpecialCycleEn_MASK                             0x8
#define DxF0x04_MemWriteInvalidateEn_OFFSET                     4
#define DxF0x04_MemWriteInvalidateEn_WIDTH                      1
#define DxF0x04_MemWriteInvalidateEn_MASK                       0x10
#define DxF0x04_PalSnoopEn_OFFSET                               5
#define DxF0x04_PalSnoopEn_WIDTH                                1
#define DxF0x04_PalSnoopEn_MASK                                 0x20
#define DxF0x04_ParityErrorEn_OFFSET                            6
#define DxF0x04_ParityErrorEn_WIDTH                             1
#define DxF0x04_ParityErrorEn_MASK                              0x40
#define DxF0x04_IdselStepping_OFFSET                            7
#define DxF0x04_IdselStepping_WIDTH                             1
#define DxF0x04_IdselStepping_MASK                              0x80
#define DxF0x04_SerrEn_OFFSET                                   8
#define DxF0x04_SerrEn_WIDTH                                    1
#define DxF0x04_SerrEn_MASK                                     0x100
#define DxF0x04_FastB2BEn_OFFSET                                9
#define DxF0x04_FastB2BEn_WIDTH                                 1
#define DxF0x04_FastB2BEn_MASK                                  0x200
#define DxF0x04_IntDis_OFFSET                                   10
#define DxF0x04_IntDis_WIDTH                                    1
#define DxF0x04_IntDis_MASK                                     0x400
#define DxF0x04_Reserved_18_11_OFFSET                           11
#define DxF0x04_Reserved_18_11_WIDTH                            8
#define DxF0x04_Reserved_18_11_MASK                             0x7f800
#define DxF0x04_IntStatus_OFFSET                                19
#define DxF0x04_IntStatus_WIDTH                                 1
#define DxF0x04_IntStatus_MASK                                  0x80000
#define DxF0x04_CapList_OFFSET                                  20
#define DxF0x04_CapList_WIDTH                                   1
#define DxF0x04_CapList_MASK                                    0x100000
#define DxF0x04_PCI66En_OFFSET                                  21
#define DxF0x04_PCI66En_WIDTH                                   1
#define DxF0x04_PCI66En_MASK                                    0x200000
#define DxF0x04_Reserved_22_22_OFFSET                           22
#define DxF0x04_Reserved_22_22_WIDTH                            1
#define DxF0x04_Reserved_22_22_MASK                             0x400000
#define DxF0x04_FastBackCapable_OFFSET                          23
#define DxF0x04_FastBackCapable_WIDTH                           1
#define DxF0x04_FastBackCapable_MASK                            0x800000
#define DxF0x04_MasterDataPerr_OFFSET                           24
#define DxF0x04_MasterDataPerr_WIDTH                            1
#define DxF0x04_MasterDataPerr_MASK                             0x1000000
#define DxF0x04_DevselTiming_OFFSET                             25
#define DxF0x04_DevselTiming_WIDTH                              2
#define DxF0x04_DevselTiming_MASK                               0x6000000
#define DxF0x04_SignaledTargetAbort_OFFSET                      27
#define DxF0x04_SignaledTargetAbort_WIDTH                       1
#define DxF0x04_SignaledTargetAbort_MASK                        0x8000000
#define DxF0x04_ReceivedTargetAbort_OFFSET                      28
#define DxF0x04_ReceivedTargetAbort_WIDTH                       1
#define DxF0x04_ReceivedTargetAbort_MASK                        0x10000000
#define DxF0x04_ReceivedMasterAbort_OFFSET                      29
#define DxF0x04_ReceivedMasterAbort_WIDTH                       1
#define DxF0x04_ReceivedMasterAbort_MASK                        0x20000000
#define DxF0x04_SignaledSystemError_OFFSET                      30
#define DxF0x04_SignaledSystemError_WIDTH                       1
#define DxF0x04_SignaledSystemError_MASK                        0x40000000
#define DxF0x04_ParityErrorDetected_OFFSET                      31
#define DxF0x04_ParityErrorDetected_WIDTH                       1
#define DxF0x04_ParityErrorDetected_MASK                        0x80000000

/// DxF0x04
typedef union {
  struct {                                                              ///<
    UINT32                                               IoAccessEn:1 ; ///<
    UINT32                                              MemAccessEn:1 ; ///<
    UINT32                                              BusMasterEn:1 ; ///<
    UINT32                                           SpecialCycleEn:1 ; ///<
    UINT32                                     MemWriteInvalidateEn:1 ; ///<
    UINT32                                               PalSnoopEn:1 ; ///<
    UINT32                                            ParityErrorEn:1 ; ///<
    UINT32                                            IdselStepping:1 ; ///<
    UINT32                                                   SerrEn:1 ; ///<
    UINT32                                                FastB2BEn:1 ; ///<
    UINT32                                                   IntDis:1 ; ///<
    UINT32                                           Reserved_18_11:8 ; ///<
    UINT32                                                IntStatus:1 ; ///<
    UINT32                                                  CapList:1 ; ///<
    UINT32                                                  PCI66En:1 ; ///<
    UINT32                                           Reserved_22_22:1 ; ///<
    UINT32                                          FastBackCapable:1 ; ///<
    UINT32                                           MasterDataPerr:1 ; ///<
    UINT32                                             DevselTiming:2 ; ///<
    UINT32                                      SignaledTargetAbort:1 ; ///<
    UINT32                                      ReceivedTargetAbort:1 ; ///<
    UINT32                                      ReceivedMasterAbort:1 ; ///<
    UINT32                                      SignaledSystemError:1 ; ///<
    UINT32                                      ParityErrorDetected:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x04_STRUCT;


// **** DxF0x18 Register Definition ****
// Address
#define DxF0x18_ADDRESS                                         0x18

// Type
#define DxF0x18_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x18_PrimaryBus_OFFSET                               0
#define DxF0x18_PrimaryBus_WIDTH                                8
#define DxF0x18_PrimaryBus_MASK                                 0xff
#define DxF0x18_SecondaryBus_OFFSET                             8
#define DxF0x18_SecondaryBus_WIDTH                              8
#define DxF0x18_SecondaryBus_MASK                               0xff00
#define DxF0x18_SubBusNumber_OFFSET                             16
#define DxF0x18_SubBusNumber_WIDTH                              8
#define DxF0x18_SubBusNumber_MASK                               0xff0000
#define DxF0x18_SecondaryLatencyTimer_OFFSET                    24
#define DxF0x18_SecondaryLatencyTimer_WIDTH                     8
#define DxF0x18_SecondaryLatencyTimer_MASK                      0xff000000

/// DxF0x18
typedef union {
  struct {                                                              ///<
    UINT32                                               PrimaryBus:8 ; ///<
    UINT32                                             SecondaryBus:8 ; ///<
    UINT32                                             SubBusNumber:8 ; ///<
    UINT32                                    SecondaryLatencyTimer:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x18_STRUCT;


// **** DxF0x20 Register Definition ****
// Address
#define DxF0x20_ADDRESS                                         0x20

// Type
#define DxF0x20_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x20_Reserved_3_0_OFFSET                             0
#define DxF0x20_Reserved_3_0_WIDTH                              4
#define DxF0x20_Reserved_3_0_MASK                               0xf
#define DxF0x20_MemBase_OFFSET                                  4
#define DxF0x20_MemBase_WIDTH                                   12
#define DxF0x20_MemBase_MASK                                    0xfff0
#define DxF0x20_Reserved_19_16_OFFSET                           16
#define DxF0x20_Reserved_19_16_WIDTH                            4
#define DxF0x20_Reserved_19_16_MASK                             0xf0000
#define DxF0x20_MemLimit_OFFSET                                 20
#define DxF0x20_MemLimit_WIDTH                                  12
#define DxF0x20_MemLimit_MASK                                   0xfff00000

/// DxF0x20
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_3_0:4 ; ///<
    UINT32                                                  MemBase:12; ///<
    UINT32                                           Reserved_19_16:4 ; ///<
    UINT32                                                 MemLimit:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x20_STRUCT;

// **** DxF0x24 Register Definition ****
// Address
#define DxF0x24_ADDRESS                                         0x24

// Type
#define DxF0x24_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x24_PrefMemBaseR_OFFSET                             0
#define DxF0x24_PrefMemBaseR_WIDTH                              4
#define DxF0x24_PrefMemBaseR_MASK                               0xf
#define DxF0x24_PrefMemBase_31_20__OFFSET                       4
#define DxF0x24_PrefMemBase_31_20__WIDTH                        12
#define DxF0x24_PrefMemBase_31_20__MASK                         0xfff0
#define DxF0x24_PrefMemLimitR_OFFSET                            16
#define DxF0x24_PrefMemLimitR_WIDTH                             4
#define DxF0x24_PrefMemLimitR_MASK                              0xf0000
#define DxF0x24_PrefMemLimit_OFFSET                             20
#define DxF0x24_PrefMemLimit_WIDTH                              12
#define DxF0x24_PrefMemLimit_MASK                               0xfff00000

/// DxF0x24
typedef union {
  struct {                                                              ///<
    UINT32                                             PrefMemBaseR:4 ; ///<
    UINT32                                       PrefMemBase_31_20_:12; ///<
    UINT32                                            PrefMemLimitR:4 ; ///<
    UINT32                                             PrefMemLimit:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x24_STRUCT;

// **** DxF0x3C Register Definition ****
// Address
#define DxF0x3C_ADDRESS                                         0x3c

// Type
#define DxF0x3C_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x3C_IntLine_OFFSET                                  0
#define DxF0x3C_IntLine_WIDTH                                   8
#define DxF0x3C_IntLine_MASK                                    0xff
#define DxF0x3C_IntPin_OFFSET                                   8
#define DxF0x3C_IntPin_WIDTH                                    3
#define DxF0x3C_IntPin_MASK                                     0x700
#define DxF0x3C_IntPinR_OFFSET                                  11
#define DxF0x3C_IntPinR_WIDTH                                   5
#define DxF0x3C_IntPinR_MASK                                    0xf800
#define DxF0x3C_ParityResponseEn_OFFSET                         16
#define DxF0x3C_ParityResponseEn_WIDTH                          1
#define DxF0x3C_ParityResponseEn_MASK                           0x10000
#define DxF0x3C_SerrEn_OFFSET                                   17
#define DxF0x3C_SerrEn_WIDTH                                    1
#define DxF0x3C_SerrEn_MASK                                     0x20000
#define DxF0x3C_IsaEn_OFFSET                                    18
#define DxF0x3C_IsaEn_WIDTH                                     1
#define DxF0x3C_IsaEn_MASK                                      0x40000
#define DxF0x3C_VgaEn_OFFSET                                    19
#define DxF0x3C_VgaEn_WIDTH                                     1
#define DxF0x3C_VgaEn_MASK                                      0x80000
#define DxF0x3C_Vga16En_OFFSET                                  20
#define DxF0x3C_Vga16En_WIDTH                                   1
#define DxF0x3C_Vga16En_MASK                                    0x100000
#define DxF0x3C_MasterAbortMode_OFFSET                          21
#define DxF0x3C_MasterAbortMode_WIDTH                           1
#define DxF0x3C_MasterAbortMode_MASK                            0x200000
#define DxF0x3C_SecondaryBusReset_OFFSET                        22
#define DxF0x3C_SecondaryBusReset_WIDTH                         1
#define DxF0x3C_SecondaryBusReset_MASK                          0x400000
#define DxF0x3C_FastB2BCap_OFFSET                               23
#define DxF0x3C_FastB2BCap_WIDTH                                1
#define DxF0x3C_FastB2BCap_MASK                                 0x800000
#define DxF0x3C_Reserved_31_24_OFFSET                           24
#define DxF0x3C_Reserved_31_24_WIDTH                            8
#define DxF0x3C_Reserved_31_24_MASK                             0xff000000

/// DxF0x3C
typedef union {
  struct {                                                              ///<
    UINT32                                                  IntLine:8 ; ///<
    UINT32                                                   IntPin:3 ; ///<
    UINT32                                                  IntPinR:5 ; ///<
    UINT32                                         ParityResponseEn:1 ; ///<
    UINT32                                                   SerrEn:1 ; ///<
    UINT32                                                    IsaEn:1 ; ///<
    UINT32                                                    VgaEn:1 ; ///<
    UINT32                                                  Vga16En:1 ; ///<
    UINT32                                          MasterAbortMode:1 ; ///<
    UINT32                                        SecondaryBusReset:1 ; ///<
    UINT32                                               FastB2BCap:1 ; ///<
    UINT32                                           Reserved_31_24:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x3C_STRUCT;


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


// **** DxF0x68 Register Definition ****
// Address
#define DxF0x68_ADDRESS                                         0x68

// Type
#define DxF0x68_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x68_PmControl_OFFSET                                0
#define DxF0x68_PmControl_WIDTH                                 2
#define DxF0x68_PmControl_MASK                                  0x3
#define DxF0x68_Reserved_2_2_OFFSET                             2
#define DxF0x68_Reserved_2_2_WIDTH                              1
#define DxF0x68_Reserved_2_2_MASK                               0x4
#define DxF0x68_ReadCplBoundary_OFFSET                          3
#define DxF0x68_ReadCplBoundary_WIDTH                           1
#define DxF0x68_ReadCplBoundary_MASK                            0x8
#define DxF0x68_LinkDis_OFFSET                                  4
#define DxF0x68_LinkDis_WIDTH                                   1
#define DxF0x68_LinkDis_MASK                                    0x10
#define DxF0x68_RetrainLink_OFFSET                              5
#define DxF0x68_RetrainLink_WIDTH                               1
#define DxF0x68_RetrainLink_MASK                                0x20
#define DxF0x68_CommonClockCfg_OFFSET                           6
#define DxF0x68_CommonClockCfg_WIDTH                            1
#define DxF0x68_CommonClockCfg_MASK                             0x40
#define DxF0x68_ExtendedSync_OFFSET                             7
#define DxF0x68_ExtendedSync_WIDTH                              1
#define DxF0x68_ExtendedSync_MASK                               0x80
#define DxF0x68_ClockPowerManagementEn_OFFSET                   8
#define DxF0x68_ClockPowerManagementEn_WIDTH                    1
#define DxF0x68_ClockPowerManagementEn_MASK                     0x100
#define DxF0x68_HWAutonomousWidthDisable_OFFSET                 9
#define DxF0x68_HWAutonomousWidthDisable_WIDTH                  1
#define DxF0x68_HWAutonomousWidthDisable_MASK                   0x200
#define DxF0x68_LinkBWManagementEn_OFFSET                       10
#define DxF0x68_LinkBWManagementEn_WIDTH                        1
#define DxF0x68_LinkBWManagementEn_MASK                         0x400
#define DxF0x68_LinkAutonomousBWIntEn_OFFSET                    11
#define DxF0x68_LinkAutonomousBWIntEn_WIDTH                     1
#define DxF0x68_LinkAutonomousBWIntEn_MASK                      0x800
#define DxF0x68_Reserved_15_12_OFFSET                           12
#define DxF0x68_Reserved_15_12_WIDTH                            4
#define DxF0x68_Reserved_15_12_MASK                             0xf000
#define DxF0x68_LinkSpeed_OFFSET                                16
#define DxF0x68_LinkSpeed_WIDTH                                 4
#define DxF0x68_LinkSpeed_MASK                                  0xf0000
#define DxF0x68_NegotiatedLinkWidth_OFFSET                      20
#define DxF0x68_NegotiatedLinkWidth_WIDTH                       6
#define DxF0x68_NegotiatedLinkWidth_MASK                        0x3f00000
#define DxF0x68_Reserved_26_26_OFFSET                           26
#define DxF0x68_Reserved_26_26_WIDTH                            1
#define DxF0x68_Reserved_26_26_MASK                             0x4000000
#define DxF0x68_LinkTraining_OFFSET                             27
#define DxF0x68_LinkTraining_WIDTH                              1
#define DxF0x68_LinkTraining_MASK                               0x8000000
#define DxF0x68_SlotClockCfg_OFFSET                             28
#define DxF0x68_SlotClockCfg_WIDTH                              1
#define DxF0x68_SlotClockCfg_MASK                               0x10000000
#define DxF0x68_DlActive_OFFSET                                 29
#define DxF0x68_DlActive_WIDTH                                  1
#define DxF0x68_DlActive_MASK                                   0x20000000
#define DxF0x68_LinkBWManagementStatus_OFFSET                   30
#define DxF0x68_LinkBWManagementStatus_WIDTH                    1
#define DxF0x68_LinkBWManagementStatus_MASK                     0x40000000
#define DxF0x68_LinkAutonomousBWStatus_OFFSET                   31
#define DxF0x68_LinkAutonomousBWStatus_WIDTH                    1
#define DxF0x68_LinkAutonomousBWStatus_MASK                     0x80000000

/// DxF0x68
typedef union {
  struct {                                                              ///<
    UINT32                                                PmControl:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                          ReadCplBoundary:1 ; ///<
    UINT32                                                  LinkDis:1 ; ///<
    UINT32                                              RetrainLink:1 ; ///<
    UINT32                                           CommonClockCfg:1 ; ///<
    UINT32                                             ExtendedSync:1 ; ///<
    UINT32                                   ClockPowerManagementEn:1 ; ///<
    UINT32                                 HWAutonomousWidthDisable:1 ; ///<
    UINT32                                       LinkBWManagementEn:1 ; ///<
    UINT32                                    LinkAutonomousBWIntEn:1 ; ///<
    UINT32                                           Reserved_15_12:4 ; ///<
    UINT32                                                LinkSpeed:4 ; ///<
    UINT32                                      NegotiatedLinkWidth:6 ; ///<
    UINT32                                           Reserved_26_26:1 ; ///<
    UINT32                                             LinkTraining:1 ; ///<
    UINT32                                             SlotClockCfg:1 ; ///<
    UINT32                                                 DlActive:1 ; ///<
    UINT32                                   LinkBWManagementStatus:1 ; ///<
    UINT32                                   LinkAutonomousBWStatus:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x68_STRUCT;

// **** DxF0x6C Register Definition ****
// Address
#define DxF0x6C_ADDRESS                                         0x6c

// Type
#define DxF0x6C_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x6C_AttnButtonPresent_OFFSET                        0
#define DxF0x6C_AttnButtonPresent_WIDTH                         1
#define DxF0x6C_AttnButtonPresent_MASK                          0x1
#define DxF0x6C_PwrControllerPresent_OFFSET                     1
#define DxF0x6C_PwrControllerPresent_WIDTH                      1
#define DxF0x6C_PwrControllerPresent_MASK                       0x2
#define DxF0x6C_MrlSensorPresent_OFFSET                         2
#define DxF0x6C_MrlSensorPresent_WIDTH                          1
#define DxF0x6C_MrlSensorPresent_MASK                           0x4
#define DxF0x6C_AttnIndicatorPresent_OFFSET                     3
#define DxF0x6C_AttnIndicatorPresent_WIDTH                      1
#define DxF0x6C_AttnIndicatorPresent_MASK                       0x8
#define DxF0x6C_PwrIndicatorPresent_OFFSET                      4
#define DxF0x6C_PwrIndicatorPresent_WIDTH                       1
#define DxF0x6C_PwrIndicatorPresent_MASK                        0x10
#define DxF0x6C_HotplugSurprise_OFFSET                          5
#define DxF0x6C_HotplugSurprise_WIDTH                           1
#define DxF0x6C_HotplugSurprise_MASK                            0x20
#define DxF0x6C_HotplugCapable_OFFSET                           6
#define DxF0x6C_HotplugCapable_WIDTH                            1
#define DxF0x6C_HotplugCapable_MASK                             0x40
#define DxF0x6C_SlotPwrLimitValue_OFFSET                        7
#define DxF0x6C_SlotPwrLimitValue_WIDTH                         8
#define DxF0x6C_SlotPwrLimitValue_MASK                          0x7f80
#define DxF0x6C_SlotPwrLimitScale_OFFSET                        15
#define DxF0x6C_SlotPwrLimitScale_WIDTH                         2
#define DxF0x6C_SlotPwrLimitScale_MASK                          0x18000
#define DxF0x6C_ElecMechIlPresent_OFFSET                        17
#define DxF0x6C_ElecMechIlPresent_WIDTH                         1
#define DxF0x6C_ElecMechIlPresent_MASK                          0x20000
#define DxF0x6C_NoCmdCplSupport_OFFSET                          18
#define DxF0x6C_NoCmdCplSupport_WIDTH                           1
#define DxF0x6C_NoCmdCplSupport_MASK                            0x40000
#define DxF0x6C_PhysicalSlotNumber_OFFSET                       19
#define DxF0x6C_PhysicalSlotNumber_WIDTH                        13
#define DxF0x6C_PhysicalSlotNumber_MASK                         0xfff80000

/// DxF0x6C
typedef union {
  struct {                                                              ///<
    UINT32                                        AttnButtonPresent:1 ; ///<
    UINT32                                     PwrControllerPresent:1 ; ///<
    UINT32                                         MrlSensorPresent:1 ; ///<
    UINT32                                     AttnIndicatorPresent:1 ; ///<
    UINT32                                      PwrIndicatorPresent:1 ; ///<
    UINT32                                          HotplugSurprise:1 ; ///<
    UINT32                                           HotplugCapable:1 ; ///<
    UINT32                                        SlotPwrLimitValue:8 ; ///<
    UINT32                                        SlotPwrLimitScale:2 ; ///<
    UINT32                                        ElecMechIlPresent:1 ; ///<
    UINT32                                          NoCmdCplSupport:1 ; ///<
    UINT32                                       PhysicalSlotNumber:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x6C_STRUCT;


// **** DxF0x80 Register Definition ****
// Address
#define DxF0x80_ADDRESS                                         0x80

// Type
#define DxF0x80_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x80_CplTimeoutValue_OFFSET                          0
#define DxF0x80_CplTimeoutValue_WIDTH                           4
#define DxF0x80_CplTimeoutValue_MASK                            0xf
#define DxF0x80_CplTimeoutDis_OFFSET                            4
#define DxF0x80_CplTimeoutDis_WIDTH                             1
#define DxF0x80_CplTimeoutDis_MASK                              0x10
#define DxF0x80_AriForwardingEn_OFFSET                          5
#define DxF0x80_AriForwardingEn_WIDTH                           1
#define DxF0x80_AriForwardingEn_MASK                            0x20
#define DxF0x80_Reserved_31_6_OFFSET                            6
#define DxF0x80_Reserved_31_6_WIDTH                             26
#define DxF0x80_Reserved_31_6_MASK                              0xffffffc0

/// DxF0x80
typedef union {
  struct {                                                              ///<
    UINT32                                          CplTimeoutValue:4 ; ///<
    UINT32                                            CplTimeoutDis:1 ; ///<
    UINT32                                          AriForwardingEn:1 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x80_STRUCT;


// **** DxF0x88 Register Definition ****
// Address
#define DxF0x88_ADDRESS                                         0x88

// Type
#define DxF0x88_TYPE                                            TYPE_D4F0
// Field Data
#define DxF0x88_TargetLinkSpeed_OFFSET                          0
#define DxF0x88_TargetLinkSpeed_WIDTH                           4
#define DxF0x88_TargetLinkSpeed_MASK                            0xf
#define DxF0x88_EnterCompliance_OFFSET                          4
#define DxF0x88_EnterCompliance_WIDTH                           1
#define DxF0x88_EnterCompliance_MASK                            0x10
#define DxF0x88_HwAutonomousSpeedDisable_OFFSET                 5
#define DxF0x88_HwAutonomousSpeedDisable_WIDTH                  1
#define DxF0x88_HwAutonomousSpeedDisable_MASK                   0x20
#define DxF0x88_SelectableDeemphasis_OFFSET                     6
#define DxF0x88_SelectableDeemphasis_WIDTH                      1
#define DxF0x88_SelectableDeemphasis_MASK                       0x40
#define DxF0x88_XmitMargin_OFFSET                               7
#define DxF0x88_XmitMargin_WIDTH                                3
#define DxF0x88_XmitMargin_MASK                                 0x380
#define DxF0x88_EnterModCompliance_OFFSET                       10
#define DxF0x88_EnterModCompliance_WIDTH                        1
#define DxF0x88_EnterModCompliance_MASK                         0x400
#define DxF0x88_ComplianceSOS_OFFSET                            11
#define DxF0x88_ComplianceSOS_WIDTH                             1
#define DxF0x88_ComplianceSOS_MASK                              0x800
#define DxF0x88_ComplianceDeemphasis_OFFSET                     12
#define DxF0x88_ComplianceDeemphasis_WIDTH                      1
#define DxF0x88_ComplianceDeemphasis_MASK                       0x1000
#define DxF0x88_Reserved_15_13_OFFSET                           13
#define DxF0x88_Reserved_15_13_WIDTH                            3
#define DxF0x88_Reserved_15_13_MASK                             0xe000
#define DxF0x88_CurDeemphasisLevel_OFFSET                       16
#define DxF0x88_CurDeemphasisLevel_WIDTH                        1
#define DxF0x88_CurDeemphasisLevel_MASK                         0x10000
#define DxF0x88_Reserved_31_17_OFFSET                           17
#define DxF0x88_Reserved_31_17_WIDTH                            15
#define DxF0x88_Reserved_31_17_MASK                             0xfffe0000

/// DxF0x88
typedef union {
  struct {                                                              ///<
    UINT32                                          TargetLinkSpeed:4 ; ///<
    UINT32                                          EnterCompliance:1 ; ///<
    UINT32                                 HwAutonomousSpeedDisable:1 ; ///<
    UINT32                                     SelectableDeemphasis:1 ; ///<
    UINT32                                               XmitMargin:3 ; ///<
    UINT32                                       EnterModCompliance:1 ; ///<
    UINT32                                            ComplianceSOS:1 ; ///<
    UINT32                                     ComplianceDeemphasis:1 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                       CurDeemphasisLevel:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x88_STRUCT;

// **** DxF0x128 Register Definition ****
// Address
#define DxF0x128_ADDRESS                                        0x128

// Type
#define DxF0x128_TYPE                                           TYPE_D4F0
// Field Data
#define DxF0x128_Reserved_15_0_OFFSET                           0
#define DxF0x128_Reserved_15_0_WIDTH                            16
#define DxF0x128_Reserved_15_0_MASK                             0xffff
#define DxF0x128_PortArbTableStatus_OFFSET                      16
#define DxF0x128_PortArbTableStatus_WIDTH                       1
#define DxF0x128_PortArbTableStatus_MASK                        0x10000
#define DxF0x128_VcNegotiationPending_OFFSET                    17
#define DxF0x128_VcNegotiationPending_WIDTH                     1
#define DxF0x128_VcNegotiationPending_MASK                      0x20000
#define DxF0x128_Reserved_31_18_OFFSET                          18
#define DxF0x128_Reserved_31_18_WIDTH                           14
#define DxF0x128_Reserved_31_18_MASK                            0xfffc0000

/// DxF0x128
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_15_0:16; ///<
    UINT32                                       PortArbTableStatus:1 ; ///<
    UINT32                                     VcNegotiationPending:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0x128_STRUCT;


// **** D0F0x64_x00 Register Definition ****
// Address
#define D0F0x64_x00_ADDRESS                                     0x0

// Type
#define D0F0x64_x00_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x00_Reserved_5_0_OFFSET                         0
#define D0F0x64_x00_Reserved_5_0_WIDTH                          6
#define D0F0x64_x00_Reserved_5_0_MASK                           0x3f
#define D0F0x64_x00_NbFchCfgEn_OFFSET                           6
#define D0F0x64_x00_NbFchCfgEn_WIDTH                            1
#define D0F0x64_x00_NbFchCfgEn_MASK                             0x40
#define D0F0x64_x00_HwInitWrLock_OFFSET                         7
#define D0F0x64_x00_HwInitWrLock_WIDTH                          1
#define D0F0x64_x00_HwInitWrLock_MASK                           0x80
#define D0F0x64_x00_Reserved_31_8_OFFSET                        8
#define D0F0x64_x00_Reserved_31_8_WIDTH                         24
#define D0F0x64_x00_Reserved_31_8_MASK                          0xffffff00

/// D0F0x64_x00
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_5_0:6 ; ///<
    UINT32                                               NbFchCfgEn:1 ; ///<
    UINT32                                             HwInitWrLock:1 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x00_STRUCT;

// **** D0F0x64_x0C Register Definition ****
// Address
#define D0F0x64_x0C_ADDRESS                                     0xc

// Type
#define D0F0x64_x0C_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x0C_Reserved_1_0_OFFSET                         0
#define D0F0x64_x0C_Reserved_1_0_WIDTH                          2
#define D0F0x64_x0C_Reserved_1_0_MASK                           0x3
#define D0F0x64_x0C_Dev2BridgeDis_OFFSET                        2
#define D0F0x64_x0C_Dev2BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev2BridgeDis_MASK                          0x4
#define D0F0x64_x0C_Dev3BridgeDis_OFFSET                        3
#define D0F0x64_x0C_Dev3BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev3BridgeDis_MASK                          0x8
#define D0F0x64_x0C_Dev4BridgeDis_OFFSET                        4
#define D0F0x64_x0C_Dev4BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev4BridgeDis_MASK                          0x10
#define D0F0x64_x0C_Dev5BridgeDis_OFFSET                        5
#define D0F0x64_x0C_Dev5BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev5BridgeDis_MASK                          0x20
#define D0F0x64_x0C_Dev6BridgeDis_OFFSET                        6
#define D0F0x64_x0C_Dev6BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev6BridgeDis_MASK                          0x40
#define D0F0x64_x0C_Dev7BridgeDis_OFFSET                        7
#define D0F0x64_x0C_Dev7BridgeDis_WIDTH                         1
#define D0F0x64_x0C_Dev7BridgeDis_MASK                          0x80
#define D0F0x64_x0C_Reserved_31_8_OFFSET                        8
#define D0F0x64_x0C_Reserved_31_8_WIDTH                         24
#define D0F0x64_x0C_Reserved_31_8_MASK                          0xffffff00

/// D0F0x64_x0C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_1_0:2 ; ///<
    UINT32                                            Dev2BridgeDis:1 ; ///<
    UINT32                                            Dev3BridgeDis:1 ; ///<
    UINT32                                            Dev4BridgeDis:1 ; ///<
    UINT32                                            Dev5BridgeDis:1 ; ///<
    UINT32                                            Dev6BridgeDis:1 ; ///<
    UINT32                                            Dev7BridgeDis:1 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x0C_STRUCT;

// **** D0F0x64_x19 Register Definition ****
// Address
#define D0F0x64_x19_ADDRESS                                     0x19

// Type
#define D0F0x64_x19_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x19_TomEn_OFFSET                                0
#define D0F0x64_x19_TomEn_WIDTH                                 1
#define D0F0x64_x19_TomEn_MASK                                  0x1
#define D0F0x64_x19_Reserved_22_1_OFFSET                        1
#define D0F0x64_x19_Reserved_22_1_WIDTH                         22
#define D0F0x64_x19_Reserved_22_1_MASK                          0x7ffffe
#define D0F0x64_x19_Tom2_31_23__OFFSET                          23
#define D0F0x64_x19_Tom2_31_23__WIDTH                           9
#define D0F0x64_x19_Tom2_31_23__MASK                            0xff800000

/// D0F0x64_x19
typedef union {
  struct {                                                              ///<
    UINT32                                                    TomEn:1 ; ///<
    UINT32                                            Reserved_22_1:22; ///<
    UINT32                                              Tom2_31_23_:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x19_STRUCT;

// **** D0F0x64_x1A Register Definition ****
// Address
#define D0F0x64_x1A_ADDRESS                                     0x1a

// Type
#define D0F0x64_x1A_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x1A_Tom2_39_32__OFFSET                          0
#define D0F0x64_x1A_Tom2_39_32__WIDTH                           8
#define D0F0x64_x1A_Tom2_39_32__MASK                            0xff
#define D0F0x64_x1A_Reserved_31_8_OFFSET                        8
#define D0F0x64_x1A_Reserved_31_8_WIDTH                         24
#define D0F0x64_x1A_Reserved_31_8_MASK                          0xffffff00

/// D0F0x64_x1A
typedef union {
  struct {                                                              ///<
    UINT32                                              Tom2_39_32_:8 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x1A_STRUCT;

// **** D0F0x64_x1D Register Definition ****
// Address
#define D0F0x64_x1D_ADDRESS                                     0x1d

// Type
#define D0F0x64_x1D_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x1D_IntGfxAsPcieEn_OFFSET                       0
#define D0F0x64_x1D_IntGfxAsPcieEn_WIDTH                        1
#define D0F0x64_x1D_IntGfxAsPcieEn_MASK                         0x1
#define D0F0x64_x1D_VgaEn_OFFSET                                1
#define D0F0x64_x1D_VgaEn_WIDTH                                 1
#define D0F0x64_x1D_VgaEn_MASK                                  0x2
#define D0F0x64_x1D_Reserved_2_2_OFFSET                         2
#define D0F0x64_x1D_Reserved_2_2_WIDTH                          1
#define D0F0x64_x1D_Reserved_2_2_MASK                           0x4
#define D0F0x64_x1D_Vga16En_OFFSET                              3
#define D0F0x64_x1D_Vga16En_WIDTH                               1
#define D0F0x64_x1D_Vga16En_MASK                                0x8
#define D0F0x64_x1D_Reserved_31_4_OFFSET                        4
#define D0F0x64_x1D_Reserved_31_4_WIDTH                         28
#define D0F0x64_x1D_Reserved_31_4_MASK                          0xfffffff0

/// D0F0x64_x1D
typedef union {
  struct {                                                              ///<
    UINT32                                           IntGfxAsPcieEn:1 ; ///<
    UINT32                                                    VgaEn:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                                  Vga16En:1 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x1D_STRUCT;


// **** D0F0x64_x6A Register Definition ****
// Address
#define D0F0x64_x6A_ADDRESS                                     0x6a

// Type
#define D0F0x64_x6A_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x6A_VoltageForceEn_OFFSET                       0
#define D0F0x64_x6A_VoltageForceEn_WIDTH                        1
#define D0F0x64_x6A_VoltageForceEn_MASK                         0x1
#define D0F0x64_x6A_VoltageChangeEn_OFFSET                      1
#define D0F0x64_x6A_VoltageChangeEn_WIDTH                       1
#define D0F0x64_x6A_VoltageChangeEn_MASK                        0x2
#define D0F0x64_x6A_VoltageChangeReq_OFFSET                     2
#define D0F0x64_x6A_VoltageChangeReq_WIDTH                      1
#define D0F0x64_x6A_VoltageChangeReq_MASK                       0x4
#define D0F0x64_x6A_VoltageLevel_OFFSET                         3
#define D0F0x64_x6A_VoltageLevel_WIDTH                          2
#define D0F0x64_x6A_VoltageLevel_MASK                           0x18
#define D0F0x64_x6A_Reserved_31_5_OFFSET                        5
#define D0F0x64_x6A_Reserved_31_5_WIDTH                         27
#define D0F0x64_x6A_Reserved_31_5_MASK                          0xffffffe0

/// D0F0x64_x6A
typedef union {
  struct {                                                              ///<
    UINT32                                           VoltageForceEn:1 ; ///<
    UINT32                                          VoltageChangeEn:1 ; ///<
    UINT32                                         VoltageChangeReq:1 ; ///<
    UINT32                                             VoltageLevel:2 ; ///<
    UINT32                                            Reserved_31_5:27; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x6A_STRUCT;

// **** D0F0x64_x6B Register Definition ****
// Address
#define D0F0x64_x6B_ADDRESS                                     0x6b

// Type
#define D0F0x64_x6B_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x6B_VoltageChangeAck_OFFSET                     0
#define D0F0x64_x6B_VoltageChangeAck_WIDTH                      1
#define D0F0x64_x6B_VoltageChangeAck_MASK                       0x1
#define D0F0x64_x6B_CurrentVoltageLevel_OFFSET                  1
#define D0F0x64_x6B_CurrentVoltageLevel_WIDTH                   2
#define D0F0x64_x6B_CurrentVoltageLevel_MASK                    0x6
#define D0F0x64_x6B_Reserved_31_3_OFFSET                        3
#define D0F0x64_x6B_Reserved_31_3_WIDTH                         29
#define D0F0x64_x6B_Reserved_31_3_MASK                          0xfffffff8

/// D0F0x64_x6B
typedef union {
  struct {                                                              ///<
    UINT32                                         VoltageChangeAck:1 ; ///<
    UINT32                                      CurrentVoltageLevel:2 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x6B_STRUCT;

// **** D0F0x98_x06 Register Definition ****
// Address
#define D0F0x98_x06_ADDRESS                                     0x6

// Type
#define D0F0x98_x06_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x06_Reserved_25_0_OFFSET                        0
#define D0F0x98_x06_Reserved_25_0_WIDTH                         26
#define D0F0x98_x06_Reserved_25_0_MASK                          0x3ffffff
#define D0F0x98_x06_UmiNpMemWrEn_OFFSET                         26
#define D0F0x98_x06_UmiNpMemWrEn_WIDTH                          1
#define D0F0x98_x06_UmiNpMemWrEn_MASK                           0x4000000
#define D0F0x98_x06_Reserved_31_27_OFFSET                       27
#define D0F0x98_x06_Reserved_31_27_WIDTH                        5
#define D0F0x98_x06_Reserved_31_27_MASK                         0xf8000000

/// D0F0x98_x06
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_25_0:26; ///<
    UINT32                                             UmiNpMemWrEn:1 ; ///<
    UINT32                                           Reserved_31_27:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x06_STRUCT;


// **** D0F0x98_x2C Register Definition ****
// Address
#define D0F0x98_x2C_ADDRESS                                     0x2c

// Type
#define D0F0x98_x2C_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x2C_Reserved_0_0_OFFSET                         0
#define D0F0x98_x2C_Reserved_0_0_WIDTH                          1
#define D0F0x98_x2C_Reserved_0_0_MASK                           0x1
#define D0F0x98_x2C_DynWakeEn_OFFSET                            1
#define D0F0x98_x2C_DynWakeEn_WIDTH                             1
#define D0F0x98_x2C_DynWakeEn_MASK                              0x2
#define D0F0x98_x2C_Reserved_15_2_OFFSET                        2
#define D0F0x98_x2C_Reserved_15_2_WIDTH                         14
#define D0F0x98_x2C_Reserved_15_2_MASK                          0xfffc
#define D0F0x98_x2C_WakeHysteresis_OFFSET                       16
#define D0F0x98_x2C_WakeHysteresis_WIDTH                        16
#define D0F0x98_x2C_WakeHysteresis_MASK                         0xffff0000

/// D0F0x98_x2C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                                DynWakeEn:1 ; ///<
    UINT32                                            Reserved_15_2:14; ///<
    UINT32                                           WakeHysteresis:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x2C_STRUCT;

// **** D0F0x98_x3A Register Definition ****
// Address
#define D0F0x98_x3A_ADDRESS                                     0x3a

// Type
#define D0F0x98_x3A_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x3A_Reserved_2_0_OFFSET                         0
#define D0F0x98_x3A_Reserved_2_0_WIDTH                          3
#define D0F0x98_x3A_Reserved_2_0_MASK                           0x7
#define D0F0x98_x3A_ClumpingEn_OFFSET                           3
#define D0F0x98_x3A_ClumpingEn_WIDTH                            1
#define D0F0x98_x3A_ClumpingEn_MASK                             0x8
#define D0F0x98_x3A_Reserved_31_4_OFFSET                        4
#define D0F0x98_x3A_Reserved_31_4_WIDTH                         28
#define D0F0x98_x3A_Reserved_31_4_MASK                          0xfffffff0

/// D0F0x98_x3A
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_2_0:3 ; ///<
    UINT32                                               ClumpingEn:1 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x3A_STRUCT;


// **** D0F0xE4_WRAP_0080 Register Definition ****
// Address
#define D0F0xE4_WRAP_0080_ADDRESS                               0x80

// Type
#define D0F0xE4_WRAP_0080_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_OFFSET             0
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_WIDTH              4
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_MASK               0xf
#define D0F0xE4_WRAP_0080_Reserved_31_4_OFFSET                  4
#define D0F0xE4_WRAP_0080_Reserved_31_4_WIDTH                   28
#define D0F0xE4_WRAP_0080_Reserved_31_4_MASK                    0xfffffff0

/// D0F0xE4_WRAP_0080
typedef union {
  struct {                                                              ///<
    UINT32                                       StrapBifLinkConfig:4 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0080_STRUCT;

// **** D0F0xE4_WRAP_0800 Register Definition ****
// Address
#define D0F0xE4_WRAP_0800_ADDRESS                               0x800

// Type
#define D0F0xE4_WRAP_0800_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0800_HoldTraining_OFFSET                   0
#define D0F0xE4_WRAP_0800_HoldTraining_WIDTH                    1
#define D0F0xE4_WRAP_0800_HoldTraining_MASK                     0x1
#define D0F0xE4_WRAP_0800_Reserved_31_1_OFFSET                  1
#define D0F0xE4_WRAP_0800_Reserved_31_1_WIDTH                   31
#define D0F0xE4_WRAP_0800_Reserved_31_1_MASK                    0xfffffffe

/// D0F0xE4_WRAP_0800
typedef union {
  struct {                                                              ///<
    UINT32                                             HoldTraining:1 ; ///<
    UINT32                                            Reserved_31_1:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0800_STRUCT;

// **** D0F0xE4_WRAP_0803 Register Definition ****
// Address
#define D0F0xE4_WRAP_0803_ADDRESS                               0x803

// Type
#define D0F0xE4_WRAP_0803_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0803_Reserved_4_0_OFFSET                   0
#define D0F0xE4_WRAP_0803_Reserved_4_0_WIDTH                    5
#define D0F0xE4_WRAP_0803_Reserved_4_0_MASK                     0x1f
#define D0F0xE4_WRAP_0803_StrapBifDeemphasisSel_OFFSET          5
#define D0F0xE4_WRAP_0803_StrapBifDeemphasisSel_WIDTH           1
#define D0F0xE4_WRAP_0803_StrapBifDeemphasisSel_MASK            0x20
#define D0F0xE4_WRAP_0803_Reserved_31_6_OFFSET                  6
#define D0F0xE4_WRAP_0803_Reserved_31_6_WIDTH                   26
#define D0F0xE4_WRAP_0803_Reserved_31_6_MASK                    0xffffffc0

/// D0F0xE4_WRAP_0803
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_4_0:5 ; ///<
    UINT32                                    StrapBifDeemphasisSel:1 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0803_STRUCT;

// **** D0F0xE4_WRAP_0903 Register Definition ****
// Address
#define D0F0xE4_WRAP_0903_ADDRESS                               0x903

// Type
#define D0F0xE4_WRAP_0903_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0903_Reserved_4_0_OFFSET                   0
#define D0F0xE4_WRAP_0903_Reserved_4_0_WIDTH                    5
#define D0F0xE4_WRAP_0903_Reserved_4_0_MASK                     0x1f
#define D0F0xE4_WRAP_0903_StrapBifDeemphasisSel_OFFSET          5
#define D0F0xE4_WRAP_0903_StrapBifDeemphasisSel_WIDTH           1
#define D0F0xE4_WRAP_0903_StrapBifDeemphasisSel_MASK            0x20
#define D0F0xE4_WRAP_0903_Reserved_31_6_OFFSET                  6
#define D0F0xE4_WRAP_0903_Reserved_31_6_WIDTH                   26
#define D0F0xE4_WRAP_0903_Reserved_31_6_MASK                    0xffffffc0

/// D0F0xE4_WRAP_0903
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_4_0:5 ; ///<
    UINT32                                    StrapBifDeemphasisSel:1 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0903_STRUCT;


// **** D0F0xE4_WRAP_8011 Register Definition ****
// Address
#define D0F0xE4_WRAP_8011_ADDRESS                               0x8011

// Type
#define D0F0xE4_WRAP_8011_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8011_TxclkDynGateLatency_OFFSET            0
#define D0F0xE4_WRAP_8011_TxclkDynGateLatency_WIDTH             6
#define D0F0xE4_WRAP_8011_TxclkDynGateLatency_MASK              0x3f
#define D0F0xE4_WRAP_8011_TxclkPermGateEven_OFFSET              6
#define D0F0xE4_WRAP_8011_TxclkPermGateEven_WIDTH               1
#define D0F0xE4_WRAP_8011_TxclkPermGateEven_MASK                0x40
#define D0F0xE4_WRAP_8011_TxclkDynGateEnable_OFFSET             7
#define D0F0xE4_WRAP_8011_TxclkDynGateEnable_WIDTH              1
#define D0F0xE4_WRAP_8011_TxclkDynGateEnable_MASK               0x80
#define D0F0xE4_WRAP_8011_TxclkPermStop_OFFSET                  8
#define D0F0xE4_WRAP_8011_TxclkPermStop_WIDTH                   1
#define D0F0xE4_WRAP_8011_TxclkPermStop_MASK                    0x100
#define D0F0xE4_WRAP_8011_TxclkRegsGateEnable_OFFSET            9
#define D0F0xE4_WRAP_8011_TxclkRegsGateEnable_WIDTH             1
#define D0F0xE4_WRAP_8011_TxclkRegsGateEnable_MASK              0x200
#define D0F0xE4_WRAP_8011_TxclkRegsGateLatency_OFFSET           10
#define D0F0xE4_WRAP_8011_TxclkRegsGateLatency_WIDTH            6
#define D0F0xE4_WRAP_8011_TxclkRegsGateLatency_MASK             0xfc00
#define D0F0xE4_WRAP_8011_RcvrDetClkEnable_OFFSET               16
#define D0F0xE4_WRAP_8011_RcvrDetClkEnable_WIDTH                1
#define D0F0xE4_WRAP_8011_RcvrDetClkEnable_MASK                 0x10000
#define D0F0xE4_WRAP_8011_TxclkPermGateLatency_OFFSET           17
#define D0F0xE4_WRAP_8011_TxclkPermGateLatency_WIDTH            6
#define D0F0xE4_WRAP_8011_TxclkPermGateLatency_MASK             0x7e0000
#define D0F0xE4_WRAP_8011_Reserved_23_23_OFFSET                 23
#define D0F0xE4_WRAP_8011_Reserved_23_23_WIDTH                  1
#define D0F0xE4_WRAP_8011_Reserved_23_23_MASK                   0x800000
#define D0F0xE4_WRAP_8011_TxclkLcntGateEnable_OFFSET            24
#define D0F0xE4_WRAP_8011_TxclkLcntGateEnable_WIDTH             1
#define D0F0xE4_WRAP_8011_TxclkLcntGateEnable_MASK              0x1000000
#define D0F0xE4_WRAP_8011_Reserved_30_25_OFFSET                 25
#define D0F0xE4_WRAP_8011_Reserved_30_25_WIDTH                  6
#define D0F0xE4_WRAP_8011_Reserved_30_25_MASK                   0x7e000000
#define D0F0xE4_WRAP_8011_StrapBifValid_OFFSET                  31
#define D0F0xE4_WRAP_8011_StrapBifValid_WIDTH                   1
#define D0F0xE4_WRAP_8011_StrapBifValid_MASK                    0x80000000

/// D0F0xE4_WRAP_8011
typedef union {
  struct {                                                              ///<
    UINT32                                      TxclkDynGateLatency:6 ; ///<
    UINT32                                        TxclkPermGateEven:1 ; ///<
    UINT32                                       TxclkDynGateEnable:1 ; ///<
    UINT32                                            TxclkPermStop:1 ; ///<
    UINT32                                      TxclkRegsGateEnable:1 ; ///<
    UINT32                                     TxclkRegsGateLatency:6 ; ///<
    UINT32                                         RcvrDetClkEnable:1 ; ///<
    UINT32                                     TxclkPermGateLatency:6 ; ///<
    UINT32                                           Reserved_23_23:1 ; ///<
    UINT32                                      TxclkLcntGateEnable:1 ; ///<
    UINT32                                           Reserved_30_25:6 ; ///<
    UINT32                                            StrapBifValid:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8011_STRUCT;

// **** D0F0xE4_WRAP_8012 Register Definition ****
// Address
#define D0F0xE4_WRAP_8012_ADDRESS                               0x8012

// Type
#define D0F0xE4_WRAP_8012_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8012_Pif1xIdleGateLatency_OFFSET           0
#define D0F0xE4_WRAP_8012_Pif1xIdleGateLatency_WIDTH            6
#define D0F0xE4_WRAP_8012_Pif1xIdleGateLatency_MASK             0x3f
#define D0F0xE4_WRAP_8012_Reserved_6_6_OFFSET                   6
#define D0F0xE4_WRAP_8012_Reserved_6_6_WIDTH                    1
#define D0F0xE4_WRAP_8012_Reserved_6_6_MASK                     0x40
#define D0F0xE4_WRAP_8012_Pif1xIdleGateEnable_OFFSET            7
#define D0F0xE4_WRAP_8012_Pif1xIdleGateEnable_WIDTH             1
#define D0F0xE4_WRAP_8012_Pif1xIdleGateEnable_MASK              0x80
#define D0F0xE4_WRAP_8012_Pif1xIdleResumeLatency_OFFSET         8
#define D0F0xE4_WRAP_8012_Pif1xIdleResumeLatency_WIDTH          6
#define D0F0xE4_WRAP_8012_Pif1xIdleResumeLatency_MASK           0x3f00
#define D0F0xE4_WRAP_8012_Reserved_15_14_OFFSET                 14
#define D0F0xE4_WRAP_8012_Reserved_15_14_WIDTH                  2
#define D0F0xE4_WRAP_8012_Reserved_15_14_MASK                   0xc000
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateLatency_OFFSET         16
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateLatency_WIDTH          6
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateLatency_MASK           0x3f0000
#define D0F0xE4_WRAP_8012_Reserved_22_22_OFFSET                 22
#define D0F0xE4_WRAP_8012_Reserved_22_22_WIDTH                  1
#define D0F0xE4_WRAP_8012_Reserved_22_22_MASK                   0x400000
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateEnable_OFFSET          23
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateEnable_WIDTH           1
#define D0F0xE4_WRAP_8012_Pif2p5xIdleGateEnable_MASK            0x800000
#define D0F0xE4_WRAP_8012_Pif2p5xIdleResumeLatency_OFFSET       24
#define D0F0xE4_WRAP_8012_Pif2p5xIdleResumeLatency_WIDTH        6
#define D0F0xE4_WRAP_8012_Pif2p5xIdleResumeLatency_MASK         0x3f000000
#define D0F0xE4_WRAP_8012_Reserved_31_30_OFFSET                 30
#define D0F0xE4_WRAP_8012_Reserved_31_30_WIDTH                  2
#define D0F0xE4_WRAP_8012_Reserved_31_30_MASK                   0xc0000000

/// D0F0xE4_WRAP_8012
typedef union {
  struct {                                                              ///<
    UINT32                                     Pif1xIdleGateLatency:6 ; ///<
    UINT32                                             Reserved_6_6:1 ; ///<
    UINT32                                      Pif1xIdleGateEnable:1 ; ///<
    UINT32                                   Pif1xIdleResumeLatency:6 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                   Pif2p5xIdleGateLatency:6 ; ///<
    UINT32                                           Reserved_22_22:1 ; ///<
    UINT32                                    Pif2p5xIdleGateEnable:1 ; ///<
    UINT32                                 Pif2p5xIdleResumeLatency:6 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8012_STRUCT;


// **** D0F0xE4_WRAP_8021 Register Definition ****
// Address
#define D0F0xE4_WRAP_8021_ADDRESS                               0x8021

// Type
#define D0F0xE4_WRAP_8021_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8021_Lanes10_OFFSET                        0
#define D0F0xE4_WRAP_8021_Lanes10_WIDTH                         4
#define D0F0xE4_WRAP_8021_Lanes10_MASK                          0xf
#define D0F0xE4_WRAP_8021_Lanes32_OFFSET                        4
#define D0F0xE4_WRAP_8021_Lanes32_WIDTH                         4
#define D0F0xE4_WRAP_8021_Lanes32_MASK                          0xf0
#define D0F0xE4_WRAP_8021_Lanes54_OFFSET                        8
#define D0F0xE4_WRAP_8021_Lanes54_WIDTH                         4
#define D0F0xE4_WRAP_8021_Lanes54_MASK                          0xf00
#define D0F0xE4_WRAP_8021_Lanes76_OFFSET                        12
#define D0F0xE4_WRAP_8021_Lanes76_WIDTH                         4
#define D0F0xE4_WRAP_8021_Lanes76_MASK                          0xf000
#define D0F0xE4_WRAP_8021_Lanes98_OFFSET                        16
#define D0F0xE4_WRAP_8021_Lanes98_WIDTH                         4
#define D0F0xE4_WRAP_8021_Lanes98_MASK                          0xf0000
#define D0F0xE4_WRAP_8021_Lanes1110_OFFSET                      20
#define D0F0xE4_WRAP_8021_Lanes1110_WIDTH                       4
#define D0F0xE4_WRAP_8021_Lanes1110_MASK                        0xf00000
#define D0F0xE4_WRAP_8021_Lanes1312_OFFSET                      24
#define D0F0xE4_WRAP_8021_Lanes1312_WIDTH                       4
#define D0F0xE4_WRAP_8021_Lanes1312_MASK                        0xf000000
#define D0F0xE4_WRAP_8021_Lanes1514_OFFSET                      28
#define D0F0xE4_WRAP_8021_Lanes1514_WIDTH                       4
#define D0F0xE4_WRAP_8021_Lanes1514_MASK                        0xf0000000

/// D0F0xE4_WRAP_8021
typedef union {
  struct {                                                              ///<
    UINT32                                                  Lanes10:4 ; ///<
    UINT32                                                  Lanes32:4 ; ///<
    UINT32                                                  Lanes54:4 ; ///<
    UINT32                                                  Lanes76:4 ; ///<
    UINT32                                                  Lanes98:4 ; ///<
    UINT32                                                Lanes1110:4 ; ///<
    UINT32                                                Lanes1312:4 ; ///<
    UINT32                                                Lanes1514:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8021_STRUCT;

// **** D0F0xCC_x01 Register Definition ****
// Address
#define D0F0xCC_x01_ADDRESS                                      0x1

// Type
#define D0F0xCC_x01_TYPE                                         TYPE_D0F0xCC
// Field Data
#define D0F0xCC_x01_BridgeDis_OFFSET                             0
#define D0F0xCC_x01_BridgeDis_WIDTH                              1
#define D0F0xCC_x01_BridgeDis_MASK                               0x1
#define D0F0xCC_x01_Reserved_1_1_OFFSET                          1
#define D0F0xCC_x01_Reserved_1_1_WIDTH                           1
#define D0F0xCC_x01_Reserved_1_1_MASK                            0x2
#define D0F0xCC_x01_CfgDis_OFFSET                                2
#define D0F0xCC_x01_CfgDis_WIDTH                                 1
#define D0F0xCC_x01_CfgDis_MASK                                  0x4
#define D0F0xCC_x01_P2pDis_OFFSET                                3
#define D0F0xCC_x01_P2pDis_WIDTH                                 1
#define D0F0xCC_x01_P2pDis_MASK                                  0x8
#define D0F0xCC_x01_Reserved_15_4_OFFSET                         4
#define D0F0xCC_x01_Reserved_15_4_WIDTH                          12
#define D0F0xCC_x01_Reserved_15_4_MASK                           0xfff0
#define D0F0xCC_x01_ExtDevPlug_OFFSET                            16
#define D0F0xCC_x01_ExtDevPlug_WIDTH                             1
#define D0F0xCC_x01_ExtDevPlug_MASK                              0x10000
#define D0F0xCC_x01_ExtDevCsrEn_OFFSET                           17
#define D0F0xCC_x01_ExtDevCsrEn_WIDTH                            1
#define D0F0xCC_x01_ExtDevCsrEn_MASK                             0x20000
#define D0F0xCC_x01_CsrEnable_OFFSET                             18
#define D0F0xCC_x01_CsrEnable_WIDTH                              1
#define D0F0xCC_x01_CsrEnable_MASK                               0x40000
#define D0F0xCC_x01_IntSelMod_OFFSET                             19
#define D0F0xCC_x01_IntSelMod_WIDTH                              1
#define D0F0xCC_x01_IntSelMod_MASK                               0x80000
#define D0F0xCC_x01_SetPowEn_OFFSET                              20
#define D0F0xCC_x01_SetPowEn_WIDTH                               1
#define D0F0xCC_x01_SetPowEn_MASK                                0x100000
#define D0F0xCC_x01_Reserved_22_21_OFFSET                        21
#define D0F0xCC_x01_Reserved_22_21_WIDTH                         2
#define D0F0xCC_x01_Reserved_22_21_MASK                          0x600000
#define D0F0xCC_x01_ApicEnable_OFFSET                            23
#define D0F0xCC_x01_ApicEnable_WIDTH                             1
#define D0F0xCC_x01_ApicEnable_MASK                              0x800000
#define D0F0xCC_x01_ApicRange_OFFSET                             24
#define D0F0xCC_x01_ApicRange_WIDTH                              8
#define D0F0xCC_x01_ApicRange_MASK                               0xff000000

/// D0F0xCC_x1
typedef union {
  struct {                                                              ///<
    UINT32                                                BridgeDis:1 ; ///<
    UINT32                                             Reserved_1_1:2 ; ///<
    UINT32                                                   CfgDis:1 ; ///<
    UINT32                                                   P2pDis:1 ; ///<
    UINT32                                            Reserved_15_4:12; ///<
    UINT32                                               ExtDevPlug:1 ; ///<
    UINT32                                              ExtDevCsrEn:1 ; ///<
    UINT32                                                CsrEnable:1 ; ///<
    UINT32                                                IntSelMod:1 ; ///<
    UINT32                                                 SetPowEn:1 ; ///<
    UINT32                                           Reserved_22_21:2 ; ///<
    UINT32                                               ApicEnable:1 ; ///<
    UINT32                                                ApicRange:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xCC_x01_STRUCT;

// **** D0F0xC8 Register Definition ****
// Address
#define D0F0xC8_ADDRESS                                         0xc8

// Type
#define D0F0xC8_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xC8_NB_DEV_IND_ADDR_OFFSET                          0
#define D0F0xC8_NB_DEV_IND_ADDR_WIDTH                           7
#define D0F0xC8_NB_DEV_IND_ADDR_MASK                            0x7F
#define D0F0xC8_Reserved_15_7_OFFSET                            7
#define D0F0xC8_Reserved_15_7_WIDTH                             9
#define D0F0xC8_Reserved_15_7_MASK                              0xFF80
#define D0F0xC8_NB_DEV_IND_SEL_OFFSET                           16
#define D0F0xC8_NB_DEV_IND_SEL_WIDTH                            8
#define D0F0xC8_NB_DEV_IND_SEL_MASK                             0xFF0000
#define D0F0xC8_Reserved_31_24_OFFSET                           24
#define D0F0xC8_Reserved_31_24_WIDTH                            8
#define D0F0xC8_Reserved_31_24_MASK                             0xFF000000

/// D0F0xC8
typedef union {
  struct {                                                              ///<
    UINT32                                         NB_DEV_IND_ADDR:7; ///<
    UINT32                                           Reserved_15_7:9; ///<
    UINT32                                          NB_DEV_IND_SEL:8; ///<
    UINT32                                          Reserved_31_24:8; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xC8_STRUCT;

// **** D0F0xE4_WRAP_8022 Register Definition ****
// Address
#define D0F0xE4_WRAP_8022_ADDRESS                               0x8022

// Type
#define D0F0xE4_WRAP_8022_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8022_Lanes10_OFFSET                        0
#define D0F0xE4_WRAP_8022_Lanes10_WIDTH                         4
#define D0F0xE4_WRAP_8022_Lanes10_MASK                          0xf
#define D0F0xE4_WRAP_8022_Lanes32_OFFSET                        4
#define D0F0xE4_WRAP_8022_Lanes32_WIDTH                         4
#define D0F0xE4_WRAP_8022_Lanes32_MASK                          0xf0
#define D0F0xE4_WRAP_8022_Lanes54_OFFSET                        8
#define D0F0xE4_WRAP_8022_Lanes54_WIDTH                         4
#define D0F0xE4_WRAP_8022_Lanes54_MASK                          0xf00
#define D0F0xE4_WRAP_8022_Lanes76_OFFSET                        12
#define D0F0xE4_WRAP_8022_Lanes76_WIDTH                         4
#define D0F0xE4_WRAP_8022_Lanes76_MASK                          0xf000
#define D0F0xE4_WRAP_8022_Lanes98_OFFSET                        16
#define D0F0xE4_WRAP_8022_Lanes98_WIDTH                         4
#define D0F0xE4_WRAP_8022_Lanes98_MASK                          0xf0000
#define D0F0xE4_WRAP_8022_Lanes1110_OFFSET                      20
#define D0F0xE4_WRAP_8022_Lanes1110_WIDTH                       4
#define D0F0xE4_WRAP_8022_Lanes1110_MASK                        0xf00000
#define D0F0xE4_WRAP_8022_Lanes1312_OFFSET                      24
#define D0F0xE4_WRAP_8022_Lanes1312_WIDTH                       4
#define D0F0xE4_WRAP_8022_Lanes1312_MASK                        0xf000000
#define D0F0xE4_WRAP_8022_Lanes1514_OFFSET                      28
#define D0F0xE4_WRAP_8022_Lanes1514_WIDTH                       4
#define D0F0xE4_WRAP_8022_Lanes1514_MASK                        0xf0000000

/// D0F0xE4_WRAP_8022
typedef union {
  struct {                                                              ///<
    UINT32                                                  Lanes10:4 ; ///<
    UINT32                                                  Lanes32:4 ; ///<
    UINT32                                                  Lanes54:4 ; ///<
    UINT32                                                  Lanes76:4 ; ///<
    UINT32                                                  Lanes98:4 ; ///<
    UINT32                                                Lanes1110:4 ; ///<
    UINT32                                                Lanes1312:4 ; ///<
    UINT32                                                Lanes1514:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8022_STRUCT;

// **** D0F0xE4_WRAP_8023 Register Definition ****
// Address
#define D0F0xE4_WRAP_8023_ADDRESS                               0x8023

// Type
#define D0F0xE4_WRAP_8023_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8023_LaneEnable_OFFSET                     0
#define D0F0xE4_WRAP_8023_LaneEnable_WIDTH                      16
#define D0F0xE4_WRAP_8023_LaneEnable_MASK                       0xffff
#define D0F0xE4_WRAP_8023_Reserved_31_16_OFFSET                 16
#define D0F0xE4_WRAP_8023_Reserved_31_16_WIDTH                  16
#define D0F0xE4_WRAP_8023_Reserved_31_16_MASK                   0xffff0000

/// D0F0xE4_WRAP_8023
typedef union {
  struct {                                                              ///<
    UINT32                                               LaneEnable:16; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8023_STRUCT;

// **** D0F0xE4_WRAP_8025 Register Definition ****
// Address
#define D0F0xE4_WRAP_8025_ADDRESS                               0x8025

// Type
#define D0F0xE4_WRAP_8025_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8025_LMTxPhyCmd0_OFFSET                    0
#define D0F0xE4_WRAP_8025_LMTxPhyCmd0_WIDTH                     3
#define D0F0xE4_WRAP_8025_LMTxPhyCmd0_MASK                      0x7
#define D0F0xE4_WRAP_8025_LMRxPhyCmd0_OFFSET                    3
#define D0F0xE4_WRAP_8025_LMRxPhyCmd0_WIDTH                     2
#define D0F0xE4_WRAP_8025_LMRxPhyCmd0_MASK                      0x18
#define D0F0xE4_WRAP_8025_LMLinkSpeed0_OFFSET                   5
#define D0F0xE4_WRAP_8025_LMLinkSpeed0_WIDTH                    1
#define D0F0xE4_WRAP_8025_LMLinkSpeed0_MASK                     0x20
#define D0F0xE4_WRAP_8025_Reserved_7_6_OFFSET                   6
#define D0F0xE4_WRAP_8025_Reserved_7_6_WIDTH                    2
#define D0F0xE4_WRAP_8025_Reserved_7_6_MASK                     0xc0
#define D0F0xE4_WRAP_8025_LMTxPhyCmd1_OFFSET                    8
#define D0F0xE4_WRAP_8025_LMTxPhyCmd1_WIDTH                     3
#define D0F0xE4_WRAP_8025_LMTxPhyCmd1_MASK                      0x700
#define D0F0xE4_WRAP_8025_LMRxPhyCmd1_OFFSET                    11
#define D0F0xE4_WRAP_8025_LMRxPhyCmd1_WIDTH                     2
#define D0F0xE4_WRAP_8025_LMRxPhyCmd1_MASK                      0x1800
#define D0F0xE4_WRAP_8025_LMLinkSpeed1_OFFSET                   13
#define D0F0xE4_WRAP_8025_LMLinkSpeed1_WIDTH                    1
#define D0F0xE4_WRAP_8025_LMLinkSpeed1_MASK                     0x2000
#define D0F0xE4_WRAP_8025_Reserved_15_14_OFFSET                 14
#define D0F0xE4_WRAP_8025_Reserved_15_14_WIDTH                  2
#define D0F0xE4_WRAP_8025_Reserved_15_14_MASK                   0xc000
#define D0F0xE4_WRAP_8025_LMTxPhyCmd2_OFFSET                    16
#define D0F0xE4_WRAP_8025_LMTxPhyCmd2_WIDTH                     3
#define D0F0xE4_WRAP_8025_LMTxPhyCmd2_MASK                      0x70000
#define D0F0xE4_WRAP_8025_LMRxPhyCmd2_OFFSET                    19
#define D0F0xE4_WRAP_8025_LMRxPhyCmd2_WIDTH                     2
#define D0F0xE4_WRAP_8025_LMRxPhyCmd2_MASK                      0x180000
#define D0F0xE4_WRAP_8025_LMLinkSpeed2_OFFSET                   21
#define D0F0xE4_WRAP_8025_LMLinkSpeed2_WIDTH                    1
#define D0F0xE4_WRAP_8025_LMLinkSpeed2_MASK                     0x200000
#define D0F0xE4_WRAP_8025_Reserved_23_22_OFFSET                 22
#define D0F0xE4_WRAP_8025_Reserved_23_22_WIDTH                  2
#define D0F0xE4_WRAP_8025_Reserved_23_22_MASK                   0xc00000
#define D0F0xE4_WRAP_8025_LMTxPhyCmd3_OFFSET                    24
#define D0F0xE4_WRAP_8025_LMTxPhyCmd3_WIDTH                     3
#define D0F0xE4_WRAP_8025_LMTxPhyCmd3_MASK                      0x7000000
#define D0F0xE4_WRAP_8025_LMRxPhyCmd3_OFFSET                    27
#define D0F0xE4_WRAP_8025_LMRxPhyCmd3_WIDTH                     2
#define D0F0xE4_WRAP_8025_LMRxPhyCmd3_MASK                      0x18000000
#define D0F0xE4_WRAP_8025_LMLinkSpeed3_OFFSET                   29
#define D0F0xE4_WRAP_8025_LMLinkSpeed3_WIDTH                    1
#define D0F0xE4_WRAP_8025_LMLinkSpeed3_MASK                     0x20000000
#define D0F0xE4_WRAP_8025_Reserved_31_30_OFFSET                 30
#define D0F0xE4_WRAP_8025_Reserved_31_30_WIDTH                  2
#define D0F0xE4_WRAP_8025_Reserved_31_30_MASK                   0xc0000000

/// D0F0xE4_WRAP_8025
typedef union {
  struct {                                                              ///<
    UINT32                                              LMTxPhyCmd0:3 ; ///<
    UINT32                                              LMRxPhyCmd0:2 ; ///<
    UINT32                                             LMLinkSpeed0:1 ; ///<
    UINT32                                             Reserved_7_6:2 ; ///<
    UINT32                                              LMTxPhyCmd1:3 ; ///<
    UINT32                                              LMRxPhyCmd1:2 ; ///<
    UINT32                                             LMLinkSpeed1:1 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                              LMTxPhyCmd2:3 ; ///<
    UINT32                                              LMRxPhyCmd2:2 ; ///<
    UINT32                                             LMLinkSpeed2:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                              LMTxPhyCmd3:3 ; ///<
    UINT32                                              LMRxPhyCmd3:2 ; ///<
    UINT32                                             LMLinkSpeed3:1 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8025_STRUCT;


// **** D0F0xE4_WRAP_8040 Register Definition ****
// Address
#define D0F0xE4_WRAP_8040_ADDRESS                               0x8040

// Type
#define D0F0xE4_WRAP_8040_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8040_OwnPhyA_OFFSET                        0
#define D0F0xE4_WRAP_8040_OwnPhyA_WIDTH                         1
#define D0F0xE4_WRAP_8040_OwnPhyA_MASK                          0x1
#define D0F0xE4_WRAP_8040_OwnPhyB_OFFSET                        1
#define D0F0xE4_WRAP_8040_OwnPhyB_WIDTH                         1
#define D0F0xE4_WRAP_8040_OwnPhyB_MASK                          0x2
#define D0F0xE4_WRAP_8040_OwnPhyC_OFFSET                        2
#define D0F0xE4_WRAP_8040_OwnPhyC_WIDTH                         1
#define D0F0xE4_WRAP_8040_OwnPhyC_MASK                          0x4
#define D0F0xE4_WRAP_8040_OwnPhyD_OFFSET                        3
#define D0F0xE4_WRAP_8040_OwnPhyD_WIDTH                         1
#define D0F0xE4_WRAP_8040_OwnPhyD_MASK                          0x8
#define D0F0xE4_WRAP_8040_Reserved_7_4_OFFSET                   4
#define D0F0xE4_WRAP_8040_Reserved_7_4_WIDTH                    4
#define D0F0xE4_WRAP_8040_Reserved_7_4_MASK                     0xf0
#define D0F0xE4_WRAP_8040_DigaPwrdnValue_OFFSET                 8
#define D0F0xE4_WRAP_8040_DigaPwrdnValue_WIDTH                  3
#define D0F0xE4_WRAP_8040_DigaPwrdnValue_MASK                   0x700
#define D0F0xE4_WRAP_8040_Reserved_11_11_OFFSET                 11
#define D0F0xE4_WRAP_8040_Reserved_11_11_WIDTH                  1
#define D0F0xE4_WRAP_8040_Reserved_11_11_MASK                   0x800
#define D0F0xE4_WRAP_8040_DigbPwrdnValue_OFFSET                 12
#define D0F0xE4_WRAP_8040_DigbPwrdnValue_WIDTH                  3
#define D0F0xE4_WRAP_8040_DigbPwrdnValue_MASK                   0x7000
#define D0F0xE4_WRAP_8040_Reserved_15_15_OFFSET                 15
#define D0F0xE4_WRAP_8040_Reserved_15_15_WIDTH                  1
#define D0F0xE4_WRAP_8040_Reserved_15_15_MASK                   0x8000
#define D0F0xE4_WRAP_8040_CntPhyA_OFFSET                        16
#define D0F0xE4_WRAP_8040_CntPhyA_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntPhyA_MASK                          0x10000
#define D0F0xE4_WRAP_8040_CntPhyB_OFFSET                        17
#define D0F0xE4_WRAP_8040_CntPhyB_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntPhyB_MASK                          0x20000
#define D0F0xE4_WRAP_8040_CntPhyC_OFFSET                        18
#define D0F0xE4_WRAP_8040_CntPhyC_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntPhyC_MASK                          0x40000
#define D0F0xE4_WRAP_8040_CntPhyD_OFFSET                        19
#define D0F0xE4_WRAP_8040_CntPhyD_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntPhyD_MASK                          0x80000
#define D0F0xE4_WRAP_8040_CntDigA_OFFSET                        20
#define D0F0xE4_WRAP_8040_CntDigA_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntDigA_MASK                          0x100000
#define D0F0xE4_WRAP_8040_CntDigB_OFFSET                        21
#define D0F0xE4_WRAP_8040_CntDigB_WIDTH                         1
#define D0F0xE4_WRAP_8040_CntDigB_MASK                          0x200000
#define D0F0xE4_WRAP_8040_ChangeLnSpd_OFFSET                    22
#define D0F0xE4_WRAP_8040_ChangeLnSpd_WIDTH                     1
#define D0F0xE4_WRAP_8040_ChangeLnSpd_MASK                      0x400000
#define D0F0xE4_WRAP_8040_Reserved_31_23_OFFSET                 23
#define D0F0xE4_WRAP_8040_Reserved_31_23_WIDTH                  9
#define D0F0xE4_WRAP_8040_Reserved_31_23_MASK                   0xff800000

/// D0F0xE4_WRAP_8040
typedef union {
  struct {                                                              ///<
    UINT32                                                  OwnPhyA:1 ; ///<
    UINT32                                                  OwnPhyB:1 ; ///<
    UINT32                                                  OwnPhyC:1 ; ///<
    UINT32                                                  OwnPhyD:1 ; ///<
    UINT32                                             Reserved_7_4:4 ; ///<
    UINT32                                           DigaPwrdnValue:3 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                           DigbPwrdnValue:3 ; ///<
    UINT32                                           Reserved_15_15:1 ; ///<
    UINT32                                                  CntPhyA:1 ; ///<
    UINT32                                                  CntPhyB:1 ; ///<
    UINT32                                                  CntPhyC:1 ; ///<
    UINT32                                                  CntPhyD:1 ; ///<
    UINT32                                                  CntDigA:1 ; ///<
    UINT32                                                  CntDigB:1 ; ///<
    UINT32                                              ChangeLnSpd:1 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8040_STRUCT;

// **** D0F0xE4_WRAP_8060 Register Definition ****
// Address
#define D0F0xE4_WRAP_8060_ADDRESS                               0x8060

// Type
#define D0F0xE4_WRAP_8060_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8060_Reconfigure_OFFSET                    0
#define D0F0xE4_WRAP_8060_Reconfigure_WIDTH                     1
#define D0F0xE4_WRAP_8060_Reconfigure_MASK                      0x1
#define D0F0xE4_WRAP_8060_Reserved_1_1_OFFSET                   1
#define D0F0xE4_WRAP_8060_Reserved_1_1_WIDTH                    1
#define D0F0xE4_WRAP_8060_Reserved_1_1_MASK                     0x2
#define D0F0xE4_WRAP_8060_ResetComplete_OFFSET                  2
#define D0F0xE4_WRAP_8060_ResetComplete_WIDTH                   1
#define D0F0xE4_WRAP_8060_ResetComplete_MASK                    0x4
#define D0F0xE4_WRAP_8060_Reserved_15_3_OFFSET                  3
#define D0F0xE4_WRAP_8060_Reserved_15_3_WIDTH                   13
#define D0F0xE4_WRAP_8060_Reserved_15_3_MASK                    0xfff8
#define D0F0xE4_WRAP_8060_BifGlobalReset_OFFSET                 16
#define D0F0xE4_WRAP_8060_BifGlobalReset_WIDTH                  1
#define D0F0xE4_WRAP_8060_BifGlobalReset_MASK                   0x10000
#define D0F0xE4_WRAP_8060_BifCalibrationReset_OFFSET            17
#define D0F0xE4_WRAP_8060_BifCalibrationReset_WIDTH             1
#define D0F0xE4_WRAP_8060_BifCalibrationReset_MASK              0x20000
#define D0F0xE4_WRAP_8060_Reserved_31_18_OFFSET                 18
#define D0F0xE4_WRAP_8060_Reserved_31_18_WIDTH                  14
#define D0F0xE4_WRAP_8060_Reserved_31_18_MASK                   0xfffc0000

/// D0F0xE4_WRAP_8060
typedef union {
  struct {                                                              ///<
    UINT32                                              Reconfigure:1 ; ///<
    UINT32                                             Reserved_1_1:1 ; ///<
    UINT32                                            ResetComplete:1 ; ///<
    UINT32                                            Reserved_15_3:13; ///<
    UINT32                                           BifGlobalReset:1 ; ///<
    UINT32                                      BifCalibrationReset:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8060_STRUCT;

// **** D0F0xE4_WRAP_8062 Register Definition ****
// Address
#define D0F0xE4_WRAP_8062_ADDRESS                               0x8062

// Type
#define D0F0xE4_WRAP_8062_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8062_ReconfigureEn_OFFSET                  0
#define D0F0xE4_WRAP_8062_ReconfigureEn_WIDTH                   1
#define D0F0xE4_WRAP_8062_ReconfigureEn_MASK                    0x1
#define D0F0xE4_WRAP_8062_Reserved_1_1_OFFSET                   1
#define D0F0xE4_WRAP_8062_Reserved_1_1_WIDTH                    1
#define D0F0xE4_WRAP_8062_Reserved_1_1_MASK                     0x2
#define D0F0xE4_WRAP_8062_ResetPeriod_OFFSET                    2
#define D0F0xE4_WRAP_8062_ResetPeriod_WIDTH                     3
#define D0F0xE4_WRAP_8062_ResetPeriod_MASK                      0x1c
#define D0F0xE4_WRAP_8062_Reserved_9_5_OFFSET                   5
#define D0F0xE4_WRAP_8062_Reserved_9_5_WIDTH                    5
#define D0F0xE4_WRAP_8062_Reserved_9_5_MASK                     0x3e0
#define D0F0xE4_WRAP_8062_BlockOnIdle_OFFSET                    10
#define D0F0xE4_WRAP_8062_BlockOnIdle_WIDTH                     1
#define D0F0xE4_WRAP_8062_BlockOnIdle_MASK                      0x400
#define D0F0xE4_WRAP_8062_ConfigXferMode_OFFSET                 11
#define D0F0xE4_WRAP_8062_ConfigXferMode_WIDTH                  1
#define D0F0xE4_WRAP_8062_ConfigXferMode_MASK                   0x800
#define D0F0xE4_WRAP_8062_Reserved_31_12_OFFSET                 12
#define D0F0xE4_WRAP_8062_Reserved_31_12_WIDTH                  20
#define D0F0xE4_WRAP_8062_Reserved_31_12_MASK                   0xfffff000

/// D0F0xE4_WRAP_8062
typedef union {
  struct {                                                              ///<
    UINT32                                            ReconfigureEn:1 ; ///<
    UINT32                                             Reserved_1_1:1 ; ///<
    UINT32                                              ResetPeriod:3 ; ///<
    UINT32                                             Reserved_9_5:5 ; ///<
    UINT32                                              BlockOnIdle:1 ; ///<
    UINT32                                           ConfigXferMode:1 ; ///<
    UINT32                                           Reserved_31_12:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8062_STRUCT;


// **** D0F0xE4_PIF_0010 Register Definition ****
// Address
#define D0F0xE4_PIF_0010_ADDRESS                                0x10

// Type
#define D0F0xE4_PIF_0010_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0010_Reserved_3_0_OFFSET                    0
#define D0F0xE4_PIF_0010_Reserved_3_0_WIDTH                     4
#define D0F0xE4_PIF_0010_Reserved_3_0_MASK                      0xf
#define D0F0xE4_PIF_0010_EiDetCycleMode_OFFSET                  4
#define D0F0xE4_PIF_0010_EiDetCycleMode_WIDTH                   1
#define D0F0xE4_PIF_0010_EiDetCycleMode_MASK                    0x10
#define D0F0xE4_PIF_0010_Reserved_5_5_OFFSET                    5
#define D0F0xE4_PIF_0010_Reserved_5_5_WIDTH                     1
#define D0F0xE4_PIF_0010_Reserved_5_5_MASK                      0x20
#define D0F0xE4_PIF_0010_RxDetectFifoResetMode_OFFSET           6
#define D0F0xE4_PIF_0010_RxDetectFifoResetMode_WIDTH            1
#define D0F0xE4_PIF_0010_RxDetectFifoResetMode_MASK             0x40
#define D0F0xE4_PIF_0010_RxDetectTxPwrMode_OFFSET               7
#define D0F0xE4_PIF_0010_RxDetectTxPwrMode_WIDTH                1
#define D0F0xE4_PIF_0010_RxDetectTxPwrMode_MASK                 0x80
#define D0F0xE4_PIF_0010_Reserved_16_8_OFFSET                   8
#define D0F0xE4_PIF_0010_Reserved_16_8_WIDTH                    9
#define D0F0xE4_PIF_0010_Reserved_16_8_MASK                     0x1ff00
#define D0F0xE4_PIF_0010_Ls2ExitTime_OFFSET                     17
#define D0F0xE4_PIF_0010_Ls2ExitTime_WIDTH                      3
#define D0F0xE4_PIF_0010_Ls2ExitTime_MASK                       0xe0000
#define D0F0xE4_PIF_0010_EiCycleOffTime_OFFSET                  20
#define D0F0xE4_PIF_0010_EiCycleOffTime_WIDTH                   3
#define D0F0xE4_PIF_0010_EiCycleOffTime_MASK                    0x700000
#define D0F0xE4_PIF_0010_Reserved_31_23_OFFSET                  23
#define D0F0xE4_PIF_0010_Reserved_31_23_WIDTH                   9
#define D0F0xE4_PIF_0010_Reserved_31_23_MASK                    0xff800000

/// D0F0xE4_PIF_0010
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_3_0:4 ; ///<
    UINT32                                           EiDetCycleMode:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                    RxDetectFifoResetMode:1 ; ///<
    UINT32                                        RxDetectTxPwrMode:1 ; ///<
    UINT32                                            Reserved_16_8:9 ; ///<
    UINT32                                              Ls2ExitTime:3 ; ///<
    UINT32                                           EiCycleOffTime:3 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0010_STRUCT;

// **** D0F0xE4_PIF_0011 Register Definition ****
// Address
#define D0F0xE4_PIF_0011_ADDRESS                                0x11

// Type
#define D0F0xE4_PIF_0011_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0011_X2Lane10_OFFSET                        0
#define D0F0xE4_PIF_0011_X2Lane10_WIDTH                         1
#define D0F0xE4_PIF_0011_X2Lane10_MASK                          0x1
#define D0F0xE4_PIF_0011_X2Lane32_OFFSET                        1
#define D0F0xE4_PIF_0011_X2Lane32_WIDTH                         1
#define D0F0xE4_PIF_0011_X2Lane32_MASK                          0x2
#define D0F0xE4_PIF_0011_X2Lane54_OFFSET                        2
#define D0F0xE4_PIF_0011_X2Lane54_WIDTH                         1
#define D0F0xE4_PIF_0011_X2Lane54_MASK                          0x4
#define D0F0xE4_PIF_0011_X2Lane76_OFFSET                        3
#define D0F0xE4_PIF_0011_X2Lane76_WIDTH                         1
#define D0F0xE4_PIF_0011_X2Lane76_MASK                          0x8
#define D0F0xE4_PIF_0011_Reserved_7_4_OFFSET                    4
#define D0F0xE4_PIF_0011_Reserved_7_4_WIDTH                     4
#define D0F0xE4_PIF_0011_Reserved_7_4_MASK                      0xf0
#define D0F0xE4_PIF_0011_X4Lane30_OFFSET                        8
#define D0F0xE4_PIF_0011_X4Lane30_WIDTH                         1
#define D0F0xE4_PIF_0011_X4Lane30_MASK                          0x100
#define D0F0xE4_PIF_0011_X4Lane74_OFFSET                        9
#define D0F0xE4_PIF_0011_X4Lane74_WIDTH                         1
#define D0F0xE4_PIF_0011_X4Lane74_MASK                          0x200
#define D0F0xE4_PIF_0011_Reserved_11_10_OFFSET                  10
#define D0F0xE4_PIF_0011_Reserved_11_10_WIDTH                   2
#define D0F0xE4_PIF_0011_Reserved_11_10_MASK                    0xc00
#define D0F0xE4_PIF_0011_X4Lane52_OFFSET                        12
#define D0F0xE4_PIF_0011_X4Lane52_WIDTH                         1
#define D0F0xE4_PIF_0011_X4Lane52_MASK                          0x1000
#define D0F0xE4_PIF_0011_Reserved_15_13_OFFSET                  13
#define D0F0xE4_PIF_0011_Reserved_15_13_WIDTH                   3
#define D0F0xE4_PIF_0011_Reserved_15_13_MASK                    0xe000
#define D0F0xE4_PIF_0011_X8Lane70_OFFSET                        16
#define D0F0xE4_PIF_0011_X8Lane70_WIDTH                         1
#define D0F0xE4_PIF_0011_X8Lane70_MASK                          0x10000
#define D0F0xE4_PIF_0011_Reserved_24_17_OFFSET                  17
#define D0F0xE4_PIF_0011_Reserved_24_17_WIDTH                   8
#define D0F0xE4_PIF_0011_Reserved_24_17_MASK                    0x1fe0000
#define D0F0xE4_PIF_0011_MultiPif_OFFSET                        25
#define D0F0xE4_PIF_0011_MultiPif_WIDTH                         1
#define D0F0xE4_PIF_0011_MultiPif_MASK                          0x2000000
#define D0F0xE4_PIF_0011_Reserved_31_26_OFFSET                  26
#define D0F0xE4_PIF_0011_Reserved_31_26_WIDTH                   6
#define D0F0xE4_PIF_0011_Reserved_31_26_MASK                    0xfc000000

/// D0F0xE4_PIF_0011
typedef union {
  struct {                                                              ///<
    UINT32                                                 X2Lane10:1 ; ///<
    UINT32                                                 X2Lane32:1 ; ///<
    UINT32                                                 X2Lane54:1 ; ///<
    UINT32                                                 X2Lane76:1 ; ///<
    UINT32                                             Reserved_7_4:4 ; ///<
    UINT32                                                 X4Lane30:1 ; ///<
    UINT32                                                 X4Lane74:1 ; ///<
    UINT32                                           Reserved_11_10:2 ; ///<
    UINT32                                                 X4Lane52:1 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                                 X8Lane70:1 ; ///<
    UINT32                                           Reserved_24_17:8 ; ///<
    UINT32                                                 MultiPif:1 ; ///<
    UINT32                                           Reserved_31_26:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0011_STRUCT;

// **** D0F0xE4_PIF_0012 Register Definition ****
// Address
#define D0F0xE4_PIF_0012_ADDRESS                                0x12

// Type
#define D0F0xE4_PIF_0012_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0012_TxPowerStateInTxs2_OFFSET              0
#define D0F0xE4_PIF_0012_TxPowerStateInTxs2_WIDTH               3
#define D0F0xE4_PIF_0012_TxPowerStateInTxs2_MASK                0x7
#define D0F0xE4_PIF_0012_ForceRxEnInL0s_OFFSET                  3
#define D0F0xE4_PIF_0012_ForceRxEnInL0s_WIDTH                   1
#define D0F0xE4_PIF_0012_ForceRxEnInL0s_MASK                    0x8
#define D0F0xE4_PIF_0012_RxPowerStateInRxs2_OFFSET              4
#define D0F0xE4_PIF_0012_RxPowerStateInRxs2_WIDTH               3
#define D0F0xE4_PIF_0012_RxPowerStateInRxs2_MASK                0x70
#define D0F0xE4_PIF_0012_PllPowerStateInTxs2_OFFSET             7
#define D0F0xE4_PIF_0012_PllPowerStateInTxs2_WIDTH              3
#define D0F0xE4_PIF_0012_PllPowerStateInTxs2_MASK               0x380
#define D0F0xE4_PIF_0012_PllPowerStateInOff_OFFSET              10
#define D0F0xE4_PIF_0012_PllPowerStateInOff_WIDTH               3
#define D0F0xE4_PIF_0012_PllPowerStateInOff_MASK                0x1c00
#define D0F0xE4_PIF_0012_Reserved_15_13_OFFSET                  13
#define D0F0xE4_PIF_0012_Reserved_15_13_WIDTH                   3
#define D0F0xE4_PIF_0012_Reserved_15_13_MASK                    0xe000
#define D0F0xE4_PIF_0012_Tx2p5clkClockGatingEn_OFFSET           16
#define D0F0xE4_PIF_0012_Tx2p5clkClockGatingEn_WIDTH            1
#define D0F0xE4_PIF_0012_Tx2p5clkClockGatingEn_MASK             0x10000
#define D0F0xE4_PIF_0012_Reserved_23_17_OFFSET                  17
#define D0F0xE4_PIF_0012_Reserved_23_17_WIDTH                   7
#define D0F0xE4_PIF_0012_Reserved_23_17_MASK                    0xfe0000
#define D0F0xE4_PIF_0012_PllRampUpTime_OFFSET                   24
#define D0F0xE4_PIF_0012_PllRampUpTime_WIDTH                    3
#define D0F0xE4_PIF_0012_PllRampUpTime_MASK                     0x7000000
#define D0F0xE4_PIF_0012_Reserved_27_27_OFFSET                  27
#define D0F0xE4_PIF_0012_Reserved_27_27_WIDTH                   1
#define D0F0xE4_PIF_0012_Reserved_27_27_MASK                    0x8000000
#define D0F0xE4_PIF_0012_PllPwrOverrideEn_OFFSET                28
#define D0F0xE4_PIF_0012_PllPwrOverrideEn_WIDTH                 1
#define D0F0xE4_PIF_0012_PllPwrOverrideEn_MASK                  0x10000000
#define D0F0xE4_PIF_0012_PllPwrOverrideVal_OFFSET               29
#define D0F0xE4_PIF_0012_PllPwrOverrideVal_WIDTH                3
#define D0F0xE4_PIF_0012_PllPwrOverrideVal_MASK                 0xe0000000

/// D0F0xE4_PIF_0012
typedef union {
  struct {                                                              ///<
    UINT32                                       TxPowerStateInTxs2:3 ; ///<
    UINT32                                           ForceRxEnInL0s:1 ; ///<
    UINT32                                       RxPowerStateInRxs2:3 ; ///<
    UINT32                                      PllPowerStateInTxs2:3 ; ///<
    UINT32                                       PllPowerStateInOff:3 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                    Tx2p5clkClockGatingEn:1 ; ///<
    UINT32                                           Reserved_23_17:7 ; ///<
    UINT32                                            PllRampUpTime:3 ; ///<
    UINT32                                           Reserved_27_27:1 ; ///<
    UINT32                                         PllPwrOverrideEn:1 ; ///<
    UINT32                                        PllPwrOverrideVal:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0012_STRUCT;

// **** D0F0xE4_PIF_0013 Register Definition ****
// Address
#define D0F0xE4_PIF_0013_ADDRESS                                0x13

// Type
#define D0F0xE4_PIF_0013_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0013_TxPowerStateInTxs2_OFFSET              0
#define D0F0xE4_PIF_0013_TxPowerStateInTxs2_WIDTH               3
#define D0F0xE4_PIF_0013_TxPowerStateInTxs2_MASK                0x7
#define D0F0xE4_PIF_0013_ForceRxEnInL0s_OFFSET                  3
#define D0F0xE4_PIF_0013_ForceRxEnInL0s_WIDTH                   1
#define D0F0xE4_PIF_0013_ForceRxEnInL0s_MASK                    0x8
#define D0F0xE4_PIF_0013_RxPowerStateInRxs2_OFFSET              4
#define D0F0xE4_PIF_0013_RxPowerStateInRxs2_WIDTH               3
#define D0F0xE4_PIF_0013_RxPowerStateInRxs2_MASK                0x70
#define D0F0xE4_PIF_0013_PllPowerStateInTxs2_OFFSET             7
#define D0F0xE4_PIF_0013_PllPowerStateInTxs2_WIDTH              3
#define D0F0xE4_PIF_0013_PllPowerStateInTxs2_MASK               0x380
#define D0F0xE4_PIF_0013_PllPowerStateInOff_OFFSET              10
#define D0F0xE4_PIF_0013_PllPowerStateInOff_WIDTH               3
#define D0F0xE4_PIF_0013_PllPowerStateInOff_MASK                0x1c00
#define D0F0xE4_PIF_0013_Reserved_15_13_OFFSET                  13
#define D0F0xE4_PIF_0013_Reserved_15_13_WIDTH                   3
#define D0F0xE4_PIF_0013_Reserved_15_13_MASK                    0xe000
#define D0F0xE4_PIF_0013_Tx2p5clkClockGatingEn_OFFSET           16
#define D0F0xE4_PIF_0013_Tx2p5clkClockGatingEn_WIDTH            1
#define D0F0xE4_PIF_0013_Tx2p5clkClockGatingEn_MASK             0x10000
#define D0F0xE4_PIF_0013_Reserved_23_17_OFFSET                  17
#define D0F0xE4_PIF_0013_Reserved_23_17_WIDTH                   7
#define D0F0xE4_PIF_0013_Reserved_23_17_MASK                    0xfe0000
#define D0F0xE4_PIF_0013_PllRampUpTime_OFFSET                   24
#define D0F0xE4_PIF_0013_PllRampUpTime_WIDTH                    3
#define D0F0xE4_PIF_0013_PllRampUpTime_MASK                     0x7000000
#define D0F0xE4_PIF_0013_Reserved_27_27_OFFSET                  27
#define D0F0xE4_PIF_0013_Reserved_27_27_WIDTH                   1
#define D0F0xE4_PIF_0013_Reserved_27_27_MASK                    0x8000000
#define D0F0xE4_PIF_0013_PllPwrOverrideEn_OFFSET                28
#define D0F0xE4_PIF_0013_PllPwrOverrideEn_WIDTH                 1
#define D0F0xE4_PIF_0013_PllPwrOverrideEn_MASK                  0x10000000
#define D0F0xE4_PIF_0013_PllPwrOverrideVal_OFFSET               29
#define D0F0xE4_PIF_0013_PllPwrOverrideVal_WIDTH                3
#define D0F0xE4_PIF_0013_PllPwrOverrideVal_MASK                 0xe0000000

/// D0F0xE4_PIF_0013
typedef union {
  struct {                                                              ///<
    UINT32                                       TxPowerStateInTxs2:3 ; ///<
    UINT32                                           ForceRxEnInL0s:1 ; ///<
    UINT32                                       RxPowerStateInRxs2:3 ; ///<
    UINT32                                      PllPowerStateInTxs2:3 ; ///<
    UINT32                                       PllPowerStateInOff:3 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                    Tx2p5clkClockGatingEn:1 ; ///<
    UINT32                                           Reserved_23_17:7 ; ///<
    UINT32                                            PllRampUpTime:3 ; ///<
    UINT32                                           Reserved_27_27:1 ; ///<
    UINT32                                         PllPwrOverrideEn:1 ; ///<
    UINT32                                        PllPwrOverrideVal:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0013_STRUCT;

// **** D0F0xE4_PIF_0015 Register Definition ****
// Address
#define D0F0xE4_PIF_0015_ADDRESS                                0x15

// Type
#define D0F0xE4_PIF_0015_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0015_TxPhyStatus00_OFFSET                   0
#define D0F0xE4_PIF_0015_TxPhyStatus00_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus00_MASK                     0x1
#define D0F0xE4_PIF_0015_TxPhyStatus01_OFFSET                   1
#define D0F0xE4_PIF_0015_TxPhyStatus01_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus01_MASK                     0x2
#define D0F0xE4_PIF_0015_TxPhyStatus02_OFFSET                   2
#define D0F0xE4_PIF_0015_TxPhyStatus02_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus02_MASK                     0x4
#define D0F0xE4_PIF_0015_TxPhyStatus03_OFFSET                   3
#define D0F0xE4_PIF_0015_TxPhyStatus03_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus03_MASK                     0x8
#define D0F0xE4_PIF_0015_TxPhyStatus04_OFFSET                   4
#define D0F0xE4_PIF_0015_TxPhyStatus04_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus04_MASK                     0x10
#define D0F0xE4_PIF_0015_TxPhyStatus05_OFFSET                   5
#define D0F0xE4_PIF_0015_TxPhyStatus05_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus05_MASK                     0x20
#define D0F0xE4_PIF_0015_TxPhyStatus06_OFFSET                   6
#define D0F0xE4_PIF_0015_TxPhyStatus06_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus06_MASK                     0x40
#define D0F0xE4_PIF_0015_TxPhyStatus07_OFFSET                   7
#define D0F0xE4_PIF_0015_TxPhyStatus07_WIDTH                    1
#define D0F0xE4_PIF_0015_TxPhyStatus07_MASK                     0x80
#define D0F0xE4_PIF_0015_Reserved_31_8_OFFSET                   8
#define D0F0xE4_PIF_0015_Reserved_31_8_WIDTH                    24
#define D0F0xE4_PIF_0015_Reserved_31_8_MASK                     0xffffff00

/// D0F0xE4_PIF_0015
typedef union {
  struct {                                                              ///<
    UINT32                                            TxPhyStatus00:1 ; ///<
    UINT32                                            TxPhyStatus01:1 ; ///<
    UINT32                                            TxPhyStatus02:1 ; ///<
    UINT32                                            TxPhyStatus03:1 ; ///<
    UINT32                                            TxPhyStatus04:1 ; ///<
    UINT32                                            TxPhyStatus05:1 ; ///<
    UINT32                                            TxPhyStatus06:1 ; ///<
    UINT32                                            TxPhyStatus07:1 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0015_STRUCT;


// **** D0F0xE4_CORE_0011 Register Definition ****
// Address
#define D0F0xE4_CORE_0011_ADDRESS                               0x11

// Type
#define D0F0xE4_CORE_0011_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0011_DynClkLatency_OFFSET                  0
#define D0F0xE4_CORE_0011_DynClkLatency_WIDTH                   4
#define D0F0xE4_CORE_0011_DynClkLatency_MASK                    0xf
#define D0F0xE4_CORE_0011_Reserved_31_4_OFFSET                  4
#define D0F0xE4_CORE_0011_Reserved_31_4_WIDTH                   28
#define D0F0xE4_CORE_0011_Reserved_31_4_MASK                    0xfffffff0

/// D0F0xE4_CORE_0011
typedef union {
  struct {                                                              ///<
    UINT32                                            DynClkLatency:4 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0011_STRUCT;


// **** D0F0xE4_PHY_0009 Register Definition ****
// Address
#define D0F0xE4_PHY_0009_ADDRESS                                0x9

// Type
#define D0F0xE4_PHY_0009_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_0009_Reserved_23_0_OFFSET                   0
#define D0F0xE4_PHY_0009_Reserved_23_0_WIDTH                    24
#define D0F0xE4_PHY_0009_Reserved_23_0_MASK                     0xffffff
#define D0F0xE4_PHY_0009_ClkOff_OFFSET                          24
#define D0F0xE4_PHY_0009_ClkOff_WIDTH                           1
#define D0F0xE4_PHY_0009_ClkOff_MASK                            0x1000000
#define D0F0xE4_PHY_0009_DisplayStream_OFFSET                   25
#define D0F0xE4_PHY_0009_DisplayStream_WIDTH                    1
#define D0F0xE4_PHY_0009_DisplayStream_MASK                     0x2000000
#define D0F0xE4_PHY_0009_Reserved_27_26_OFFSET                  26
#define D0F0xE4_PHY_0009_Reserved_27_26_WIDTH                   2
#define D0F0xE4_PHY_0009_Reserved_27_26_MASK                    0xc000000
#define D0F0xE4_PHY_0009_CascadedPllSel_OFFSET                  28
#define D0F0xE4_PHY_0009_CascadedPllSel_WIDTH                   1
#define D0F0xE4_PHY_0009_CascadedPllSel_MASK                    0x10000000
#define D0F0xE4_PHY_0009_Reserved_30_29_OFFSET                  29
#define D0F0xE4_PHY_0009_Reserved_30_29_WIDTH                   2
#define D0F0xE4_PHY_0009_Reserved_30_29_MASK                    0x60000000
#define D0F0xE4_PHY_0009_PCIePllSel_OFFSET                      31
#define D0F0xE4_PHY_0009_PCIePllSel_WIDTH                       1
#define D0F0xE4_PHY_0009_PCIePllSel_MASK                        0x80000000

/// D0F0xE4_PHY_0009
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_23_0:24; ///<
    UINT32                                                   ClkOff:1 ; ///<
    UINT32                                            DisplayStream:1 ; ///<
    UINT32                                           Reserved_27_26:2 ; ///<
    UINT32                                           CascadedPllSel:1 ; ///<
    UINT32                                           Reserved_30_29:2 ; ///<
    UINT32                                               PCIePllSel:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_0009_STRUCT;

// **** D0F0xE4_PHY_000A Register Definition ****
// Address
#define D0F0xE4_PHY_000A_ADDRESS                                0xa

// Type
#define D0F0xE4_PHY_000A_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_000A_Reserved_23_0_OFFSET                   0
#define D0F0xE4_PHY_000A_Reserved_23_0_WIDTH                    24
#define D0F0xE4_PHY_000A_Reserved_23_0_MASK                     0xffffff
#define D0F0xE4_PHY_000A_ClkOff_OFFSET                          24
#define D0F0xE4_PHY_000A_ClkOff_WIDTH                           1
#define D0F0xE4_PHY_000A_ClkOff_MASK                            0x1000000
#define D0F0xE4_PHY_000A_DisplayStream_OFFSET                   25
#define D0F0xE4_PHY_000A_DisplayStream_WIDTH                    1
#define D0F0xE4_PHY_000A_DisplayStream_MASK                     0x2000000
#define D0F0xE4_PHY_000A_Reserved_27_26_OFFSET                  26
#define D0F0xE4_PHY_000A_Reserved_27_26_WIDTH                   2
#define D0F0xE4_PHY_000A_Reserved_27_26_MASK                    0xc000000
#define D0F0xE4_PHY_000A_CascadedPllSel_OFFSET                  28
#define D0F0xE4_PHY_000A_CascadedPllSel_WIDTH                   1
#define D0F0xE4_PHY_000A_CascadedPllSel_MASK                    0x10000000
#define D0F0xE4_PHY_000A_Reserved_30_29_OFFSET                  29
#define D0F0xE4_PHY_000A_Reserved_30_29_WIDTH                   2
#define D0F0xE4_PHY_000A_Reserved_30_29_MASK                    0x60000000
#define D0F0xE4_PHY_000A_PCIePllSel_OFFSET                      31
#define D0F0xE4_PHY_000A_PCIePllSel_WIDTH                       1
#define D0F0xE4_PHY_000A_PCIePllSel_MASK                        0x80000000

/// D0F0xE4_PHY_000A
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_23_0:24; ///<
    UINT32                                                   ClkOff:1 ; ///<
    UINT32                                            DisplayStream:1 ; ///<
    UINT32                                           Reserved_27_26:2 ; ///<
    UINT32                                           CascadedPllSel:1 ; ///<
    UINT32                                           Reserved_30_29:2 ; ///<
    UINT32                                               PCIePllSel:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_000A_STRUCT;

// **** D0F0xE4_PHY_000B Register Definition ****
// Address
#define D0F0xE4_PHY_000B_ADDRESS                                0xb

// Type
#define D0F0xE4_PHY_000B_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_000B_TxPwrSbiEn_OFFSET                      0
#define D0F0xE4_PHY_000B_TxPwrSbiEn_WIDTH                       1
#define D0F0xE4_PHY_000B_TxPwrSbiEn_MASK                        0x1
#define D0F0xE4_PHY_000B_RxPwrSbiEn_OFFSET                      1
#define D0F0xE4_PHY_000B_RxPwrSbiEn_WIDTH                       1
#define D0F0xE4_PHY_000B_RxPwrSbiEn_MASK                        0x2
#define D0F0xE4_PHY_000B_PcieModeSbiEn_OFFSET                   2
#define D0F0xE4_PHY_000B_PcieModeSbiEn_WIDTH                    1
#define D0F0xE4_PHY_000B_PcieModeSbiEn_MASK                     0x4
#define D0F0xE4_PHY_000B_FreqDivSbiEn_OFFSET                    3
#define D0F0xE4_PHY_000B_FreqDivSbiEn_WIDTH                     1
#define D0F0xE4_PHY_000B_FreqDivSbiEn_MASK                      0x8
#define D0F0xE4_PHY_000B_DllLockSbiEn_OFFSET                    4
#define D0F0xE4_PHY_000B_DllLockSbiEn_WIDTH                     1
#define D0F0xE4_PHY_000B_DllLockSbiEn_MASK                      0x10
#define D0F0xE4_PHY_000B_OffsetCancelSbiEn_OFFSET               5
#define D0F0xE4_PHY_000B_OffsetCancelSbiEn_WIDTH                1
#define D0F0xE4_PHY_000B_OffsetCancelSbiEn_MASK                 0x20
#define D0F0xE4_PHY_000B_SkipBitSbiEn_OFFSET                    6
#define D0F0xE4_PHY_000B_SkipBitSbiEn_WIDTH                     1
#define D0F0xE4_PHY_000B_SkipBitSbiEn_MASK                      0x40
#define D0F0xE4_PHY_000B_IncoherentClkSbiEn_OFFSET              7
#define D0F0xE4_PHY_000B_IncoherentClkSbiEn_WIDTH               1
#define D0F0xE4_PHY_000B_IncoherentClkSbiEn_MASK                0x80
#define D0F0xE4_PHY_000B_EiDetSbiEn_OFFSET                      8
#define D0F0xE4_PHY_000B_EiDetSbiEn_WIDTH                       1
#define D0F0xE4_PHY_000B_EiDetSbiEn_MASK                        0x100
#define D0F0xE4_PHY_000B_Reserved_13_9_OFFSET                   9
#define D0F0xE4_PHY_000B_Reserved_13_9_WIDTH                    5
#define D0F0xE4_PHY_000B_Reserved_13_9_MASK                     0x3e00
#define D0F0xE4_PHY_000B_MargPktSbiEn_OFFSET                    14
#define D0F0xE4_PHY_000B_MargPktSbiEn_WIDTH                     1
#define D0F0xE4_PHY_000B_MargPktSbiEn_MASK                      0x4000
#define D0F0xE4_PHY_000B_PllCmpPktSbiEn_OFFSET                  15
#define D0F0xE4_PHY_000B_PllCmpPktSbiEn_WIDTH                   1
#define D0F0xE4_PHY_000B_PllCmpPktSbiEn_MASK                    0x8000
#define D0F0xE4_PHY_000B_Reserved_31_16_OFFSET                  16
#define D0F0xE4_PHY_000B_Reserved_31_16_WIDTH                   16
#define D0F0xE4_PHY_000B_Reserved_31_16_MASK                    0xffff0000

/// D0F0xE4_PHY_000B
typedef union {
  struct {                                                              ///<
    UINT32                                               TxPwrSbiEn:1 ; ///<
    UINT32                                               RxPwrSbiEn:1 ; ///<
    UINT32                                            PcieModeSbiEn:1 ; ///<
    UINT32                                             FreqDivSbiEn:1 ; ///<
    UINT32                                             DllLockSbiEn:1 ; ///<
    UINT32                                        OffsetCancelSbiEn:1 ; ///<
    UINT32                                             SkipBitSbiEn:1 ; ///<
    UINT32                                       IncoherentClkSbiEn:1 ; ///<
    UINT32                                               EiDetSbiEn:1 ; ///<
    UINT32                                            Reserved_13_9:5 ; ///<
    UINT32                                             MargPktSbiEn:1 ; ///<
    UINT32                                           PllCmpPktSbiEn:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_000B_STRUCT;


// **** D0F0xE4_PHY_4001 Register Definition ****
// Address
#define D0F0xE4_PHY_4001_ADDRESS                                0x4001

// Type
#define D0F0xE4_PHY_4001_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_4001_Reserved_14_0_OFFSET                   0
#define D0F0xE4_PHY_4001_Reserved_14_0_WIDTH                    15
#define D0F0xE4_PHY_4001_Reserved_14_0_MASK                     0x7fff
#define D0F0xE4_PHY_4001_ForceDccRecalc_OFFSET                  15
#define D0F0xE4_PHY_4001_ForceDccRecalc_WIDTH                   1
#define D0F0xE4_PHY_4001_ForceDccRecalc_MASK                    0x8000
#define D0F0xE4_PHY_4001_Reserved_31_16_OFFSET                  16
#define D0F0xE4_PHY_4001_Reserved_31_16_WIDTH                   16
#define D0F0xE4_PHY_4001_Reserved_31_16_MASK                    0xffff0000

/// D0F0xE4_PHY_4001
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_14_0:15; ///<
    UINT32                                           ForceDccRecalc:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_4001_STRUCT;

// **** D0F0xE4_PHY_4002 Register Definition ****

// **** D0F0xE4_PHY_6005 Register Definition ****
// Address
#define D0F0xE4_PHY_6005_ADDRESS                                0x6005

// Type
#define D0F0xE4_PHY_6005_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_6005_Reserved_28_0_OFFSET                   0
#define D0F0xE4_PHY_6005_Reserved_28_0_WIDTH                    29
#define D0F0xE4_PHY_6005_Reserved_28_0_MASK                     0x1fffffff
#define D0F0xE4_PHY_6005_IsOwnMstr_OFFSET                       29
#define D0F0xE4_PHY_6005_IsOwnMstr_WIDTH                        1
#define D0F0xE4_PHY_6005_IsOwnMstr_MASK                         0x20000000
#define D0F0xE4_PHY_6005_Reserved_30_30_OFFSET                  30
#define D0F0xE4_PHY_6005_Reserved_30_30_WIDTH                   1
#define D0F0xE4_PHY_6005_Reserved_30_30_MASK                    0x40000000
#define D0F0xE4_PHY_6005_GangedModeEn_OFFSET                    31
#define D0F0xE4_PHY_6005_GangedModeEn_WIDTH                     1
#define D0F0xE4_PHY_6005_GangedModeEn_MASK                      0x80000000

/// D0F0xE4_PHY_6005
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_28_0:29; ///<
    UINT32                                                IsOwnMstr:1 ; ///<
    UINT32                                           Reserved_30_30:1 ; ///<
    UINT32                                             GangedModeEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_6005_STRUCT;


// **** DxF0xE4_x20 Register Definition ****
// Address
#define DxF0xE4_x20_ADDRESS                                     0x20

// Type
#define DxF0xE4_x20_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_x20_Reserved_14_0_OFFSET                        0
#define DxF0xE4_x20_Reserved_14_0_WIDTH                         15
#define DxF0xE4_x20_Reserved_14_0_MASK                          0x7fff
#define DxF0xE4_x20_TxFlushTlpDis_OFFSET                        15
#define DxF0xE4_x20_TxFlushTlpDis_WIDTH                         1
#define DxF0xE4_x20_TxFlushTlpDis_MASK                          0x8000
#define DxF0xE4_x20_Reserved_31_16_OFFSET                       16
#define DxF0xE4_x20_Reserved_31_16_WIDTH                        16
#define DxF0xE4_x20_Reserved_31_16_MASK                         0xffff0000

/// DxF0xE4_x20
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_14_0:15; ///<
    UINT32                                            TxFlushTlpDis:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_x20_STRUCT;

// **** DxF0xE4_x50 Register Definition ****
// Address
#define DxF0xE4_x50_ADDRESS                                     0x50

// Type
#define DxF0xE4_x50_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_x50_PortLaneReversal_OFFSET                     0
#define DxF0xE4_x50_PortLaneReversal_WIDTH                      1
#define DxF0xE4_x50_PortLaneReversal_MASK                       0x1
#define DxF0xE4_x50_PhyLinkWidth_OFFSET                         1
#define DxF0xE4_x50_PhyLinkWidth_WIDTH                          6
#define DxF0xE4_x50_PhyLinkWidth_MASK                           0x7e
#define DxF0xE4_x50_Reserved_31_7_OFFSET                        7
#define DxF0xE4_x50_Reserved_31_7_WIDTH                         25
#define DxF0xE4_x50_Reserved_31_7_MASK                          0xffffff80

/// DxF0xE4_x50
typedef union {
  struct {                                                              ///<
    UINT32                                         PortLaneReversal:1 ; ///<
    UINT32                                             PhyLinkWidth:6 ; ///<
    UINT32                                            Reserved_31_7:25; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_x50_STRUCT;

// **** DxF0xE4_x70 Register Definition ****
// Address
#define DxF0xE4_x70_ADDRESS                                     0x70

// Type
#define DxF0xE4_x70_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_x70_Reserved_15_0_OFFSET                        0
#define DxF0xE4_x70_Reserved_15_0_WIDTH                         16
#define DxF0xE4_x70_Reserved_15_0_MASK                          0xffff
#define DxF0xE4_x70_RxRcbCplTimeout_OFFSET                      16
#define DxF0xE4_x70_RxRcbCplTimeout_WIDTH                       3
#define DxF0xE4_x70_RxRcbCplTimeout_MASK                        0x70000
#define DxF0xE4_x70_RxRcbCplTimeoutMode_OFFSET                  19
#define DxF0xE4_x70_RxRcbCplTimeoutMode_WIDTH                   1
#define DxF0xE4_x70_RxRcbCplTimeoutMode_MASK                    0x80000
#define DxF0xE4_x70_Reserved_31_20_OFFSET                       20
#define DxF0xE4_x70_Reserved_31_20_WIDTH                        12
#define DxF0xE4_x70_Reserved_31_20_MASK                         0xfff00000

/// DxF0xE4_x70
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_15_0:16; ///<
    UINT32                                          RxRcbCplTimeout:3 ; ///<
    UINT32                                      RxRcbCplTimeoutMode:1 ; ///<
    UINT32                                           Reserved_31_20:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_x70_STRUCT;


// **** DxF0xE4_xA2 Register Definition ****
// Address
#define DxF0xE4_xA2_ADDRESS                                     0xa2

// Type
#define DxF0xE4_xA2_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_xA2_LcLinkWidth_OFFSET                          0
#define DxF0xE4_xA2_LcLinkWidth_WIDTH                           3
#define DxF0xE4_xA2_LcLinkWidth_MASK                            0x7
#define DxF0xE4_xA2_Reserved_3_3_OFFSET                         3
#define DxF0xE4_xA2_Reserved_3_3_WIDTH                          1
#define DxF0xE4_xA2_Reserved_3_3_MASK                           0x8
#define DxF0xE4_xA2_LcLinkWidthRd_OFFSET                        4
#define DxF0xE4_xA2_LcLinkWidthRd_WIDTH                         3
#define DxF0xE4_xA2_LcLinkWidthRd_MASK                          0x70
#define DxF0xE4_xA2_LcReconfigArcMissingEscape_OFFSET           7
#define DxF0xE4_xA2_LcReconfigArcMissingEscape_WIDTH            1
#define DxF0xE4_xA2_LcReconfigArcMissingEscape_MASK             0x80
#define DxF0xE4_xA2_LcReconfigNow_OFFSET                        8
#define DxF0xE4_xA2_LcReconfigNow_WIDTH                         1
#define DxF0xE4_xA2_LcReconfigNow_MASK                          0x100
#define DxF0xE4_xA2_LcRenegotiationSupport_OFFSET               9
#define DxF0xE4_xA2_LcRenegotiationSupport_WIDTH                1
#define DxF0xE4_xA2_LcRenegotiationSupport_MASK                 0x200
#define DxF0xE4_xA2_LcRenegotiateEn_OFFSET                      10
#define DxF0xE4_xA2_LcRenegotiateEn_WIDTH                       1
#define DxF0xE4_xA2_LcRenegotiateEn_MASK                        0x400
#define DxF0xE4_xA2_LcShortReconfigEn_OFFSET                    11
#define DxF0xE4_xA2_LcShortReconfigEn_WIDTH                     1
#define DxF0xE4_xA2_LcShortReconfigEn_MASK                      0x800
#define DxF0xE4_xA2_LcUpconfigureSupport_OFFSET                 12
#define DxF0xE4_xA2_LcUpconfigureSupport_WIDTH                  1
#define DxF0xE4_xA2_LcUpconfigureSupport_MASK                   0x1000
#define DxF0xE4_xA2_LcUpconfigureDis_OFFSET                     13
#define DxF0xE4_xA2_LcUpconfigureDis_WIDTH                      1
#define DxF0xE4_xA2_LcUpconfigureDis_MASK                       0x2000
#define DxF0xE4_xA2_Reserved_19_14_OFFSET                       14
#define DxF0xE4_xA2_Reserved_19_14_WIDTH                        6
#define DxF0xE4_xA2_Reserved_19_14_MASK                         0xfc000
#define DxF0xE4_xA2_LcUpconfigCapable_OFFSET                    20
#define DxF0xE4_xA2_LcUpconfigCapable_WIDTH                     1
#define DxF0xE4_xA2_LcUpconfigCapable_MASK                      0x100000
#define DxF0xE4_xA2_LcDynLanesPwrState_OFFSET                   21
#define DxF0xE4_xA2_LcDynLanesPwrState_WIDTH                    2
#define DxF0xE4_xA2_LcDynLanesPwrState_MASK                     0x600000
#define DxF0xE4_xA2_Reserved_31_23_OFFSET                       23
#define DxF0xE4_xA2_Reserved_31_23_WIDTH                        9
#define DxF0xE4_xA2_Reserved_31_23_MASK                         0xff800000

/// DxF0xE4_xA2
typedef union {
  struct {                                                              ///<
    UINT32                                              LcLinkWidth:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                            LcLinkWidthRd:3 ; ///<
    UINT32                               LcReconfigArcMissingEscape:1 ; ///<
    UINT32                                            LcReconfigNow:1 ; ///<
    UINT32                                   LcRenegotiationSupport:1 ; ///<
    UINT32                                          LcRenegotiateEn:1 ; ///<
    UINT32                                        LcShortReconfigEn:1 ; ///<
    UINT32                                     LcUpconfigureSupport:1 ; ///<
    UINT32                                         LcUpconfigureDis:1 ; ///<
    UINT32                                           Reserved_19_14:6 ; ///<
    UINT32                                        LcUpconfigCapable:1 ; ///<
    UINT32                                       LcDynLanesPwrState:2 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_xA2_STRUCT;

// **** DxF0xE4_xA4 Register Definition ****
// Address
#define DxF0xE4_xA4_ADDRESS                                     0xa4

// Type
#define DxF0xE4_xA4_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_xA4_LcGen2EnStrap_OFFSET                        0
#define DxF0xE4_xA4_LcGen2EnStrap_WIDTH                         1
#define DxF0xE4_xA4_LcGen2EnStrap_MASK                          0x1
#define DxF0xE4_xA4_LcGen3EnStrap_OFFSET                        1
#define DxF0xE4_xA4_LcGen3EnStrap_WIDTH                         1
#define DxF0xE4_xA4_LcGen3EnStrap_MASK                          0x2
#define DxF0xE4_xA4_Reserved_5_2_OFFSET                         2
#define DxF0xE4_xA4_Reserved_5_2_WIDTH                          4
#define DxF0xE4_xA4_Reserved_5_2_MASK                           0x3c
#define DxF0xE4_xA4_LcForceDisSwSpeedChange_OFFSET              6
#define DxF0xE4_xA4_LcForceDisSwSpeedChange_WIDTH               1
#define DxF0xE4_xA4_LcForceDisSwSpeedChange_MASK                0x40
#define DxF0xE4_xA4_Reserved_8_7_OFFSET                         7
#define DxF0xE4_xA4_Reserved_8_7_WIDTH                          2
#define DxF0xE4_xA4_Reserved_8_7_MASK                           0x180
#define DxF0xE4_xA4_LcInitiateLinkSpeedChange_OFFSET            9
#define DxF0xE4_xA4_LcInitiateLinkSpeedChange_WIDTH             1
#define DxF0xE4_xA4_LcInitiateLinkSpeedChange_MASK              0x200
#define DxF0xE4_xA4_Reserved_11_10_OFFSET                       10
#define DxF0xE4_xA4_Reserved_11_10_WIDTH                        2
#define DxF0xE4_xA4_Reserved_11_10_MASK                         0xc00
#define DxF0xE4_xA4_LcSpeedChangeAttemptFailed_OFFSET           12
#define DxF0xE4_xA4_LcSpeedChangeAttemptFailed_WIDTH            1
#define DxF0xE4_xA4_LcSpeedChangeAttemptFailed_MASK             0x1000
#define DxF0xE4_xA4_Reserved_18_13_OFFSET                       13
#define DxF0xE4_xA4_Reserved_18_13_WIDTH                        6
#define DxF0xE4_xA4_Reserved_18_13_MASK                         0x7e000
#define DxF0xE4_xA4_LcOtherSideSupportsGen2_OFFSET              19
#define DxF0xE4_xA4_LcOtherSideSupportsGen2_WIDTH               1
#define DxF0xE4_xA4_LcOtherSideSupportsGen2_MASK                0x80000
#define DxF0xE4_xA4_Reserved_26_20_OFFSET                       20
#define DxF0xE4_xA4_Reserved_26_20_WIDTH                        7
#define DxF0xE4_xA4_Reserved_26_20_MASK                         0x7f00000
#define DxF0xE4_xA4_LcMultUpstreamAutoSpdChngEn_OFFSET          27
#define DxF0xE4_xA4_LcMultUpstreamAutoSpdChngEn_WIDTH           1
#define DxF0xE4_xA4_LcMultUpstreamAutoSpdChngEn_MASK            0x8000000
#define DxF0xE4_xA4_Reserved_31_28_OFFSET                       28
#define DxF0xE4_xA4_Reserved_31_28_WIDTH                        4
#define DxF0xE4_xA4_Reserved_31_28_MASK                         0xf0000000

/// DxF0xE4_xA4
typedef union {
  struct {                                                              ///<
    UINT32                                            LcGen2EnStrap:1 ; ///<
    UINT32                                            LcGen3EnStrap:1 ; ///<
    UINT32                                             Reserved_5_2:4 ; ///<
    UINT32                                  LcForceDisSwSpeedChange:1 ; ///<
    UINT32                                             Reserved_8_7:2 ; ///<
    UINT32                                LcInitiateLinkSpeedChange:1 ; ///<
    UINT32                                           Reserved_11_10:2 ; ///<
    UINT32                               LcSpeedChangeAttemptFailed:1 ; ///<
    UINT32                                           Reserved_18_13:6 ; ///<
    UINT32                                  LcOtherSideSupportsGen2:1 ; ///<
    UINT32                                           Reserved_26_20:7 ; ///<
    UINT32                              LcMultUpstreamAutoSpdChngEn:1 ; ///<
    UINT32                                           Reserved_31_28:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_xA4_STRUCT;

// **** DxF0xE4_xA5 Register Definition ****
// Address
#define DxF0xE4_xA5_ADDRESS                                     0xa5

// Type
#define DxF0xE4_xA5_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_xA5_LcCurrentState_OFFSET                       0
#define DxF0xE4_xA5_LcCurrentState_WIDTH                        6
#define DxF0xE4_xA5_LcCurrentState_MASK                         0x3f
#define DxF0xE4_xA5_Reserved_7_6_OFFSET                         6
#define DxF0xE4_xA5_Reserved_7_6_WIDTH                          2
#define DxF0xE4_xA5_Reserved_7_6_MASK                           0xc0
#define DxF0xE4_xA5_LcPrevState1_OFFSET                         8
#define DxF0xE4_xA5_LcPrevState1_WIDTH                          6
#define DxF0xE4_xA5_LcPrevState1_MASK                           0x3f00
#define DxF0xE4_xA5_Reserved_15_14_OFFSET                       14
#define DxF0xE4_xA5_Reserved_15_14_WIDTH                        2
#define DxF0xE4_xA5_Reserved_15_14_MASK                         0xc000
#define DxF0xE4_xA5_LcPrevState2_OFFSET                         16
#define DxF0xE4_xA5_LcPrevState2_WIDTH                          6
#define DxF0xE4_xA5_LcPrevState2_MASK                           0x3f0000
#define DxF0xE4_xA5_Reserved_23_22_OFFSET                       22
#define DxF0xE4_xA5_Reserved_23_22_WIDTH                        2
#define DxF0xE4_xA5_Reserved_23_22_MASK                         0xc00000
#define DxF0xE4_xA5_LcPrevState3_OFFSET                         24
#define DxF0xE4_xA5_LcPrevState3_WIDTH                          6
#define DxF0xE4_xA5_LcPrevState3_MASK                           0x3f000000
#define DxF0xE4_xA5_Reserved_31_30_OFFSET                       30
#define DxF0xE4_xA5_Reserved_31_30_WIDTH                        2
#define DxF0xE4_xA5_Reserved_31_30_MASK                         0xc0000000

/// DxF0xE4_xA5
typedef union {
  struct {                                                              ///<
    UINT32                                           LcCurrentState:6 ; ///<
    UINT32                                             Reserved_7_6:2 ; ///<
    UINT32                                             LcPrevState1:6 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                             LcPrevState2:6 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                             LcPrevState3:6 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_xA5_STRUCT;


// **** DxF0xE4_xC0 Register Definition ****
// Address
#define DxF0xE4_xC0_ADDRESS                                     0xc0

// Type
#define DxF0xE4_xC0_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_xC0_Reserved_12_0_OFFSET                        0
#define DxF0xE4_xC0_Reserved_12_0_WIDTH                         13
#define DxF0xE4_xC0_Reserved_12_0_MASK                          0x1fff
#define DxF0xE4_xC0_StrapForceCompliance_OFFSET                 13
#define DxF0xE4_xC0_StrapForceCompliance_WIDTH                  1
#define DxF0xE4_xC0_StrapForceCompliance_MASK                   0x2000
#define DxF0xE4_xC0_Reserved_14_14_OFFSET                       14
#define DxF0xE4_xC0_Reserved_14_14_WIDTH                        1
#define DxF0xE4_xC0_Reserved_14_14_MASK                         0x4000
#define DxF0xE4_xC0_StrapAutoRcSpeedNegotiationDis_OFFSET       15
#define DxF0xE4_xC0_StrapAutoRcSpeedNegotiationDis_WIDTH        1
#define DxF0xE4_xC0_StrapAutoRcSpeedNegotiationDis_MASK         0x8000
#define DxF0xE4_xC0_Reserved_31_16_OFFSET                       16
#define DxF0xE4_xC0_Reserved_31_16_WIDTH                        16
#define DxF0xE4_xC0_Reserved_31_16_MASK                         0xffff0000

/// DxF0xE4_xC0
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_12_0:13; ///<
    UINT32                                     StrapForceCompliance:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                           StrapAutoRcSpeedNegotiationDis:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_xC0_STRUCT;

// **** D0F0xE4_WRAP_8013 Register Definition ****
// Address
#define D0F0xE4_WRAP_8013_ADDRESS                               0x8013

// Field Data
#define D0F0xE4_WRAP_8013_MasterPciePllA_OFFSET                 0
#define D0F0xE4_WRAP_8013_MasterPciePllA_WIDTH                  1
#define D0F0xE4_WRAP_8013_MasterPciePllA_MASK                   0x1
#define D0F0xE4_WRAP_8013_Reserved_1_1_OFFSET                   1
#define D0F0xE4_WRAP_8013_Reserved_1_1_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_1_1_MASK                     0x2
#define D0F0xE4_WRAP_8013_Reserved_2_2_OFFSET                   2
#define D0F0xE4_WRAP_8013_Reserved_2_2_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_2_2_MASK                     0x4
#define D0F0xE4_WRAP_8013_Reserved_3_3_OFFSET                   3
#define D0F0xE4_WRAP_8013_Reserved_3_3_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_3_3_MASK                     0x8
#define D0F0xE4_WRAP_8013_ClkDividerResetOverrideA_OFFSET       4
#define D0F0xE4_WRAP_8013_ClkDividerResetOverrideA_WIDTH        1
#define D0F0xE4_WRAP_8013_ClkDividerResetOverrideA_MASK         0x10
#define D0F0xE4_WRAP_8013_Reserved_5_5_OFFSET                   5
#define D0F0xE4_WRAP_8013_Reserved_5_5_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_5_5_MASK                     0x20
#define D0F0xE4_WRAP_8013_Reserved_6_6_OFFSET                   6
#define D0F0xE4_WRAP_8013_Reserved_6_6_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_6_6_MASK                     0x40
#define D0F0xE4_WRAP_8013_Reserved_7_7_OFFSET                   7
#define D0F0xE4_WRAP_8013_Reserved_7_7_WIDTH                    1
#define D0F0xE4_WRAP_8013_Reserved_7_7_MASK                     0x80
#define D0F0xE4_WRAP_8013_TxclkSelCoreOverride_OFFSET           8
#define D0F0xE4_WRAP_8013_TxclkSelCoreOverride_WIDTH            1
#define D0F0xE4_WRAP_8013_TxclkSelCoreOverride_MASK             0x100
#define D0F0xE4_WRAP_8013_TxclkSelPifAOverride_OFFSET           9
#define D0F0xE4_WRAP_8013_TxclkSelPifAOverride_WIDTH            1
#define D0F0xE4_WRAP_8013_TxclkSelPifAOverride_MASK             0x200
#define D0F0xE4_WRAP_8013_Reserved_10_10_OFFSET                 10
#define D0F0xE4_WRAP_8013_Reserved_10_10_WIDTH                  1
#define D0F0xE4_WRAP_8013_Reserved_10_10_MASK                   0x400
#define D0F0xE4_WRAP_8013_Reserved_11_11_OFFSET                 11
#define D0F0xE4_WRAP_8013_Reserved_11_11_WIDTH                  1
#define D0F0xE4_WRAP_8013_Reserved_11_11_MASK                   0x800
#define D0F0xE4_WRAP_8013_Reserved_12_12_OFFSET                 12
#define D0F0xE4_WRAP_8013_Reserved_12_12_WIDTH                  1
#define D0F0xE4_WRAP_8013_Reserved_12_12_MASK                   0x1000
#define D0F0xE4_WRAP_8013_Reserved_15_13_OFFSET                 13
#define D0F0xE4_WRAP_8013_Reserved_15_13_WIDTH                  3
#define D0F0xE4_WRAP_8013_Reserved_15_13_MASK                   0xe000
#define D0F0xE4_WRAP_8013_Reserved_16_16_OFFSET                 16
#define D0F0xE4_WRAP_8013_Reserved_16_16_WIDTH                  1
#define D0F0xE4_WRAP_8013_Reserved_16_16_MASK                   0x10000
#define D0F0xE4_WRAP_8013_Reserved_19_17_OFFSET                 17
#define D0F0xE4_WRAP_8013_Reserved_19_17_WIDTH                  3
#define D0F0xE4_WRAP_8013_Reserved_19_17_MASK                   0xe0000
#define D0F0xE4_WRAP_8013_Reserved_20_20_OFFSET                 20
#define D0F0xE4_WRAP_8013_Reserved_20_20_WIDTH                  1
#define D0F0xE4_WRAP_8013_Reserved_20_20_MASK                   0x100000
#define D0F0xE4_WRAP_8013_Reserved_31_21_OFFSET                 21
#define D0F0xE4_WRAP_8013_Reserved_31_21_WIDTH                  11
#define D0F0xE4_WRAP_8013_Reserved_31_21_MASK                   0xffe00000

/// D0F0xE4_WRAP_8013
typedef union {
  struct {                                                              ///<
    UINT32                                           MasterPciePllA:1 ; ///<
    UINT32                                           MasterPciePllB:1 ; ///<
    UINT32                                           MasterPciePllC:1 ; ///<
    UINT32                                           MasterPciePllD:1 ; ///<
    UINT32                                 ClkDividerResetOverrideA:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                             Reserved_6_6:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                     TxclkSelCoreOverride:1 ; ///<
    UINT32                                     TxclkSelPifAOverride:1 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                           Reserved_12_12:1 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                           Reserved_16_16:1 ; ///<
    UINT32                                           Reserved_19_17:3 ; ///<
    UINT32                                           Reserved_20_20:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8013_STRUCT;

// **** D0F0xE4_WRAP_8014 Register Definition ****
// Address
#define D0F0xE4_WRAP_8014_ADDRESS                               0x8014

// Field Data
#define D0F0xE4_WRAP_8014_TxclkPermGateEnable_OFFSET            0
#define D0F0xE4_WRAP_8014_TxclkPermGateEnable_WIDTH             1
#define D0F0xE4_WRAP_8014_TxclkPermGateEnable_MASK              0x1
#define D0F0xE4_WRAP_8014_TxclkPrbsGateEnable_OFFSET            1
#define D0F0xE4_WRAP_8014_TxclkPrbsGateEnable_WIDTH             1
#define D0F0xE4_WRAP_8014_TxclkPrbsGateEnable_MASK              0x2
#define D0F0xE4_WRAP_8014_Reserved_2_2_OFFSET                   2
#define D0F0xE4_WRAP_8014_Reserved_2_2_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_2_2_MASK                     0x4
#define D0F0xE4_WRAP_8014_Reserved_3_3_OFFSET                   3
#define D0F0xE4_WRAP_8014_Reserved_3_3_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_3_3_MASK                     0x8
#define D0F0xE4_WRAP_8014_Reserved_4_4_OFFSET                   4
#define D0F0xE4_WRAP_8014_Reserved_4_4_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_4_4_MASK                     0x10
#define D0F0xE4_WRAP_8014_Reserved_5_5_OFFSET                   5
#define D0F0xE4_WRAP_8014_Reserved_5_5_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_5_5_MASK                     0x20
#define D0F0xE4_WRAP_8014_Reserved_6_6_OFFSET                   6
#define D0F0xE4_WRAP_8014_Reserved_6_6_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_6_6_MASK                     0x40
#define D0F0xE4_WRAP_8014_Reserved_7_7_OFFSET                   7
#define D0F0xE4_WRAP_8014_Reserved_7_7_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_7_7_MASK                     0x80
#define D0F0xE4_WRAP_8014_Reserved_8_8_OFFSET                   8
#define D0F0xE4_WRAP_8014_Reserved_8_8_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_8_8_MASK                     0x100
#define D0F0xE4_WRAP_8014_Reserved_9_9_OFFSET                   9
#define D0F0xE4_WRAP_8014_Reserved_9_9_WIDTH                    1
#define D0F0xE4_WRAP_8014_Reserved_9_9_MASK                     0x200
#define D0F0xE4_WRAP_8014_Reserved_10_10_OFFSET                 10
#define D0F0xE4_WRAP_8014_Reserved_10_10_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_10_10_MASK                   0x400
#define D0F0xE4_WRAP_8014_Reserved_11_11_OFFSET                 11
#define D0F0xE4_WRAP_8014_Reserved_11_11_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_11_11_MASK                   0x800
#define D0F0xE4_WRAP_8014_PcieGatePifA1xEnable_OFFSET           12
#define D0F0xE4_WRAP_8014_PcieGatePifA1xEnable_WIDTH            1
#define D0F0xE4_WRAP_8014_PcieGatePifA1xEnable_MASK             0x1000
#define D0F0xE4_WRAP_8014_Reserved_13_13_OFFSET                 13
#define D0F0xE4_WRAP_8014_Reserved_13_13_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_13_13_MASK                   0x2000
#define D0F0xE4_WRAP_8014_Reserved_14_14_OFFSET                 14
#define D0F0xE4_WRAP_8014_Reserved_14_14_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_14_14_MASK                   0x4000
#define D0F0xE4_WRAP_8014_Reserved_15_15_OFFSET                 15
#define D0F0xE4_WRAP_8014_Reserved_15_15_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_15_15_MASK                   0x8000
#define D0F0xE4_WRAP_8014_PcieGatePifA2p5xEnable_OFFSET         16
#define D0F0xE4_WRAP_8014_PcieGatePifA2p5xEnable_WIDTH          1
#define D0F0xE4_WRAP_8014_PcieGatePifA2p5xEnable_MASK           0x10000
#define D0F0xE4_WRAP_8014_Reserved_17_17_OFFSET                 17
#define D0F0xE4_WRAP_8014_Reserved_17_17_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_17_17_MASK                   0x20000
#define D0F0xE4_WRAP_8014_Reserved_18_18_OFFSET                 18
#define D0F0xE4_WRAP_8014_Reserved_18_18_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_18_18_MASK                   0x40000
#define D0F0xE4_WRAP_8014_Reserved_19_19_OFFSET                 19
#define D0F0xE4_WRAP_8014_Reserved_19_19_WIDTH                  1
#define D0F0xE4_WRAP_8014_Reserved_19_19_MASK                   0x80000
#define D0F0xE4_WRAP_8014_TxclkPermGateOnlyWhenPllPwrDn_OFFSET  20
#define D0F0xE4_WRAP_8014_TxclkPermGateOnlyWhenPllPwrDn_WIDTH   1
#define D0F0xE4_WRAP_8014_TxclkPermGateOnlyWhenPllPwrDn_MASK    0x100000
#define D0F0xE4_WRAP_8014_Reserved_31_21_OFFSET                 21
#define D0F0xE4_WRAP_8014_Reserved_31_21_WIDTH                  11
#define D0F0xE4_WRAP_8014_Reserved_31_21_MASK                   0xffe00000

/// D0F0xE4_WRAP_8014
typedef union {
  struct {
    UINT32                                      TxclkPermGateEnable:1 ; ///<
    UINT32                                      TxclkPrbsGateEnable:1 ; ///<
    UINT32                                      DdiGatePifA1xEnable:1 ; ///<
    UINT32                                      DdiGatePifB1xEnable:1 ; ///<
    UINT32                                      DdiGatePifC1xEnable:1 ; ///<
    UINT32                                      DdiGatePifD1xEnable:1 ; ///<
    UINT32                                        DdiGateDigAEnable:1 ; ///<
    UINT32                                        DdiGateDigBEnable:1 ; ///<
    UINT32                                    DdiGatePifA2p5xEnable:1 ; ///<
    UINT32                                    DdiGatePifB2p5xEnable:1 ; ///<
    UINT32                                    DdiGatePifC2p5xEnable:1 ; ///<
    UINT32                                    DdiGatePifD2p5xEnable:1 ; ///<
    UINT32                                     PcieGatePifA1xEnable:1 ; ///<
    UINT32                                     PcieGatePifB1xEnable:1 ; ///<
    UINT32                                     PcieGatePifC1xEnable:1 ; ///<
    UINT32                                     PcieGatePifD1xEnable:1 ; ///<
    UINT32                                   PcieGatePifA2p5xEnable:1 ; ///<
    UINT32                                   PcieGatePifB2p5xEnable:1 ; ///<
    UINT32                                   PcieGatePifC2p5xEnable:1 ; ///<
    UINT32                                   PcieGatePifD2p5xEnable:1 ; ///<
    UINT32                            TxclkPermGateOnlyWhenPllPwrDn:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8014_STRUCT;

// **** D0F0x64_x51 Register Definition ****
// Address
#define D0F0x64_x51_ADDRESS                                     0x51

// Type
#define D0F0x64_x51_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x51_Reserved_2_0_OFFSET                         0
#define D0F0x64_x51_Reserved_2_0_WIDTH                          3
#define D0F0x64_x51_Reserved_2_0_MASK                           0x7
#define D0F0x64_x51_P2pDis_OFFSET                               3
#define D0F0x64_x51_P2pDis_WIDTH                                1
#define D0F0x64_x51_P2pDis_MASK                                 0x8
#define D0F0x64_x51_Reserved_15_4_OFFSET                        4
#define D0F0x64_x51_Reserved_15_4_WIDTH                         12
#define D0F0x64_x51_Reserved_15_4_MASK                          0xfff0
#define D0F0x64_x51_ExtDevPlug_OFFSET                           16
#define D0F0x64_x51_ExtDevPlug_WIDTH                            1
#define D0F0x64_x51_ExtDevPlug_MASK                             0x10000
#define D0F0x64_x51_ExtDevCrsEn_OFFSET                          17
#define D0F0x64_x51_ExtDevCrsEn_WIDTH                           1
#define D0F0x64_x51_ExtDevCrsEn_MASK                            0x20000
#define D0F0x64_x51_CrsEn_OFFSET                                18
#define D0F0x64_x51_CrsEn_WIDTH                                 1
#define D0F0x64_x51_CrsEn_MASK                                  0x40000
#define D0F0x64_x51_IntSelMode_OFFSET                           19
#define D0F0x64_x51_IntSelMode_WIDTH                            1
#define D0F0x64_x51_IntSelMode_MASK                             0x80000
#define D0F0x64_x51_SetPowEn_OFFSET                             20
#define D0F0x64_x51_SetPowEn_WIDTH                              1
#define D0F0x64_x51_SetPowEn_MASK                               0x100000
#define D0F0x64_x51_Reserved_31_21_OFFSET                       21
#define D0F0x64_x51_Reserved_31_21_WIDTH                        11
#define D0F0x64_x51_Reserved_31_21_MASK                         0xffe00000

/// D0F0x64_x51
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_2_0:3 ; ///<
    UINT32                                                   P2pDis:1 ; ///<
    UINT32                                            Reserved_15_4:12; ///<
    UINT32                                               ExtDevPlug:1 ; ///<
    UINT32                                              ExtDevCrsEn:1 ; ///<
    UINT32                                                    CrsEn:1 ; ///<
    UINT32                                               IntSelMode:1 ; ///<
    UINT32                                                 SetPowEn:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x51_STRUCT;


// **** D0F0xE4_CORE_0010 Register Definition ****
// Address
#define D0F0xE4_CORE_0010_ADDRESS                               0x10

// Type
#define D0F0xE4_CORE_0010_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0010_HwInitWrLock_OFFSET                   0
#define D0F0xE4_CORE_0010_HwInitWrLock_WIDTH                    1
#define D0F0xE4_CORE_0010_HwInitWrLock_MASK                     0x1
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_OFFSET                1
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_WIDTH                 3
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_MASK                  0xe
#define D0F0xE4_CORE_0010_Reserved_6_4_OFFSET                   4
#define D0F0xE4_CORE_0010_Reserved_6_4_WIDTH                    3
#define D0F0xE4_CORE_0010_Reserved_6_4_MASK                     0x70
#define D0F0xE4_CORE_0010_UrErrReportDis_OFFSET                 7
#define D0F0xE4_CORE_0010_UrErrReportDis_WIDTH                  1
#define D0F0xE4_CORE_0010_UrErrReportDis_MASK                   0x80
#define D0F0xE4_CORE_0010_Reserved_8_8_OFFSET                   8
#define D0F0xE4_CORE_0010_Reserved_8_8_WIDTH                    1
#define D0F0xE4_CORE_0010_Reserved_8_8_MASK                     0x100
#define D0F0xE4_CORE_0010_UmiNpMemWrite_OFFSET                  9
#define D0F0xE4_CORE_0010_UmiNpMemWrite_WIDTH                   1
#define D0F0xE4_CORE_0010_UmiNpMemWrite_MASK                    0x200
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_OFFSET            10
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_WIDTH             3
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_MASK              0x1c00
#define D0F0xE4_CORE_0010_Reserved_15_13_OFFSET                 13
#define D0F0xE4_CORE_0010_Reserved_15_13_WIDTH                  3
#define D0F0xE4_CORE_0010_Reserved_15_13_MASK                   0xe000
#define D0F0xE4_CORE_0010_RxRcbReorderEn_OFFSET                 16
#define D0F0xE4_CORE_0010_RxRcbReorderEn_WIDTH                  1
#define D0F0xE4_CORE_0010_RxRcbReorderEn_MASK                   0x10000
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_OFFSET            17
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_WIDTH             1
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_MASK              0x20000
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_OFFSET               18
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_WIDTH                1
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_MASK                 0x40000
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_OFFSET        19
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_WIDTH         1
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_MASK          0x80000
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_OFFSET           20
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_WIDTH            1
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_MASK             0x100000
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_OFFSET              21
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_WIDTH               1
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_MASK                0x200000
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_OFFSET           22
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_WIDTH            1
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_MASK             0x400000
#define D0F0xE4_CORE_0010_Reserved_23_23_OFFSET                 23
#define D0F0xE4_CORE_0010_Reserved_23_23_WIDTH                  1
#define D0F0xE4_CORE_0010_Reserved_23_23_MASK                   0x800000
#define D0F0xE4_CORE_0010_TxCplDebug_OFFSET                     24
#define D0F0xE4_CORE_0010_TxCplDebug_WIDTH                      6
#define D0F0xE4_CORE_0010_TxCplDebug_MASK                       0x3f000000
#define D0F0xE4_CORE_0010_Reserved_30_30_OFFSET                 30
#define D0F0xE4_CORE_0010_Reserved_30_30_WIDTH                  1
#define D0F0xE4_CORE_0010_Reserved_30_30_MASK                   0x40000000
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_OFFSET            31
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_WIDTH             1
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_MASK              0x80000000

/// D0F0xE4_CORE_0010
typedef union {
  struct {                                                              ///<
    UINT32                                             HwInitWrLock:1 ; ///<
    UINT32                                          LcHotPlugDelSel:3 ; ///<
    UINT32                                             Reserved_6_4:3 ; ///<
    UINT32                                           UrErrReportDis:1 ; ///<
    UINT32                                             Reserved_8_8:1 ; ///<
    UINT32                                            UmiNpMemWrite:1 ; ///<
    UINT32                                      RxUmiAdjPayloadSize:3 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                           RxRcbReorderEn:1 ; ///<
    UINT32                                      RxRcbInvalidSizeDis:1 ; ///<
    UINT32                                         RxRcbUnexpCplDis:1 ; ///<
    UINT32                                  RxRcbCplTimeoutTestMode:1 ; ///<
    UINT32                                     RxRcbChannelOrdering:1 ; ///<
    UINT32                                        RxRcbWrongAttrDis:1 ; ///<
    UINT32                                     RxRcbWrongFuncnumDis:1 ; ///<
    UINT32                                           Reserved_23_23:1 ; ///<
    UINT32                                               TxCplDebug:6 ; ///<
    UINT32                                           Reserved_30_30:1 ; ///<
    UINT32                                      RxCplPostedReqOrdEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0010_STRUCT;


// **** D0F0xE4_WRAP_8063 Register Definition ****
// Address
#define D0F0xE4_WRAP_8063_ADDRESS                               0x8063

// Type
#define D0F0xE4_WRAP_8063_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8063_Reserved_0_0_OFFSET                   0
#define D0F0xE4_WRAP_8063_Reserved_0_0_WIDTH                    1
#define D0F0xE4_WRAP_8063_Reserved_0_0_MASK                     0x1
#define D0F0xE4_WRAP_8063_ResetPrbsEn_OFFSET                    1
#define D0F0xE4_WRAP_8063_ResetPrbsEn_WIDTH                     1
#define D0F0xE4_WRAP_8063_ResetPrbsEn_MASK                      0x2
#define D0F0xE4_WRAP_8063_ResetLaneMuxEn_OFFSET                 2
#define D0F0xE4_WRAP_8063_ResetLaneMuxEn_WIDTH                  1
#define D0F0xE4_WRAP_8063_ResetLaneMuxEn_MASK                   0x4
#define D0F0xE4_WRAP_8063_ResetWrapRegsEn_OFFSET                3
#define D0F0xE4_WRAP_8063_ResetWrapRegsEn_WIDTH                 1
#define D0F0xE4_WRAP_8063_ResetWrapRegsEn_MASK                  0x8
#define D0F0xE4_WRAP_8063_ResetSrbm0En_OFFSET                   4
#define D0F0xE4_WRAP_8063_ResetSrbm0En_WIDTH                    1
#define D0F0xE4_WRAP_8063_ResetSrbm0En_MASK                     0x10
#define D0F0xE4_WRAP_8063_ResetSrbm1En_OFFSET                   5
#define D0F0xE4_WRAP_8063_ResetSrbm1En_WIDTH                    1
#define D0F0xE4_WRAP_8063_ResetSrbm1En_MASK                     0x20
#define D0F0xE4_WRAP_8063_ResetLcEn_OFFSET                      6
#define D0F0xE4_WRAP_8063_ResetLcEn_WIDTH                       1
#define D0F0xE4_WRAP_8063_ResetLcEn_MASK                        0x40
#define D0F0xE4_WRAP_8063_Reserved_7_7_OFFSET                   7
#define D0F0xE4_WRAP_8063_Reserved_7_7_WIDTH                    1
#define D0F0xE4_WRAP_8063_Reserved_7_7_MASK                     0x80
#define D0F0xE4_WRAP_8063_Reserved_9_8_OFFSET                   8
#define D0F0xE4_WRAP_8063_Reserved_9_8_WIDTH                    2
#define D0F0xE4_WRAP_8063_Reserved_9_8_MASK                     0x300
#define D0F0xE4_WRAP_8063_Reserved_10_10_OFFSET                 10
#define D0F0xE4_WRAP_8063_Reserved_10_10_WIDTH                  1
#define D0F0xE4_WRAP_8063_Reserved_10_10_MASK                   0x400
#define D0F0xE4_WRAP_8063_SyncIdlePif0En_OFFSET                 11
#define D0F0xE4_WRAP_8063_SyncIdlePif0En_WIDTH                  1
#define D0F0xE4_WRAP_8063_SyncIdlePif0En_MASK                   0x800
#define D0F0xE4_WRAP_8063_ResetSrbmNbEn_OFFSET                  12
#define D0F0xE4_WRAP_8063_ResetSrbmNbEn_WIDTH                   1
#define D0F0xE4_WRAP_8063_ResetSrbmNbEn_MASK                    0x1000
#define D0F0xE4_WRAP_8063_ResetSrbmGfxEn_OFFSET                 13
#define D0F0xE4_WRAP_8063_ResetSrbmGfxEn_WIDTH                  1
#define D0F0xE4_WRAP_8063_ResetSrbmGfxEn_MASK                   0x2000
#define D0F0xE4_WRAP_8063_ResetSrbmDcEn_OFFSET                  14
#define D0F0xE4_WRAP_8063_ResetSrbmDcEn_WIDTH                   1
#define D0F0xE4_WRAP_8063_ResetSrbmDcEn_MASK                    0x4000
#define D0F0xE4_WRAP_8063_ResetCpmEn_OFFSET                     15
#define D0F0xE4_WRAP_8063_ResetCpmEn_WIDTH                      1
#define D0F0xE4_WRAP_8063_ResetCpmEn_MASK                       0x8000
#define D0F0xE4_WRAP_8063_ResetPif0_OFFSET                      16
#define D0F0xE4_WRAP_8063_ResetPif0_WIDTH                       1
#define D0F0xE4_WRAP_8063_ResetPif0_MASK                        0x10000
#define D0F0xE4_WRAP_8063_Reserved_17_17_OFFSET                 17
#define D0F0xE4_WRAP_8063_Reserved_17_17_WIDTH                  1
#define D0F0xE4_WRAP_8063_Reserved_17_17_MASK                   0x20000
#define D0F0xE4_WRAP_8063_Reserved_19_18_OFFSET                 18
#define D0F0xE4_WRAP_8063_Reserved_19_18_WIDTH                  2
#define D0F0xE4_WRAP_8063_Reserved_19_18_MASK                   0xc0000
#define D0F0xE4_WRAP_8063_ResetImpArg0En_OFFSET                 20
#define D0F0xE4_WRAP_8063_ResetImpArg0En_WIDTH                  1
#define D0F0xE4_WRAP_8063_ResetImpArg0En_MASK                   0x100000
#define D0F0xE4_WRAP_8063_Reserved_21_21_OFFSET                 21
#define D0F0xE4_WRAP_8063_Reserved_21_21_WIDTH                  1
#define D0F0xE4_WRAP_8063_Reserved_21_21_MASK                   0x200000
#define D0F0xE4_WRAP_8063_Reserved_23_22_OFFSET                 22
#define D0F0xE4_WRAP_8063_Reserved_23_22_WIDTH                  2
#define D0F0xE4_WRAP_8063_Reserved_23_22_MASK                   0xc00000
#define D0F0xE4_WRAP_8063_ResetPhy0En_OFFSET                    24
#define D0F0xE4_WRAP_8063_ResetPhy0En_WIDTH                     1
#define D0F0xE4_WRAP_8063_ResetPhy0En_MASK                      0x1000000
#define D0F0xE4_WRAP_8063_Reserved_25_25_OFFSET                 25
#define D0F0xE4_WRAP_8063_Reserved_25_25_WIDTH                  1
#define D0F0xE4_WRAP_8063_Reserved_25_25_MASK                   0x2000000
#define D0F0xE4_WRAP_8063_Reserved_27_26_OFFSET                 26
#define D0F0xE4_WRAP_8063_Reserved_27_26_WIDTH                  2
#define D0F0xE4_WRAP_8063_Reserved_27_26_MASK                   0xc000000
#define D0F0xE4_WRAP_8063_Reserved_31_28_OFFSET                 28
#define D0F0xE4_WRAP_8063_Reserved_31_28_WIDTH                  4
#define D0F0xE4_WRAP_8063_Reserved_31_28_MASK                   0xf0000000

/// D0F0xE4_WRAP_8063
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                              ResetPrbsEn:1 ; ///<
    UINT32                                           ResetLaneMuxEn:1 ; ///<
    UINT32                                          ResetWrapRegsEn:1 ; ///<
    UINT32                                             ResetSrbm0En:1 ; ///<
    UINT32                                             ResetSrbm1En:1 ; ///<
    UINT32                                                ResetLcEn:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                           SyncIdlePif0En:1 ; ///<
    UINT32                                            ResetSrbmNbEn:1 ; ///<
    UINT32                                           ResetSrbmGfxEn:1 ; ///<
    UINT32                                            ResetSrbmDcEn:1 ; ///<
    UINT32                                               ResetCpmEn:1 ; ///<
    UINT32                                                ResetPif0:1 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                           Reserved_19_18:2 ; ///<
    UINT32                                           ResetImpArg0En:1 ; ///<
    UINT32                                           Reserved_21_21:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                              ResetPhy0En:1 ; ///<
    UINT32                                           Reserved_25_25:1 ; ///<
    UINT32                                           Reserved_27_26:2 ; ///<
    UINT32                                           Reserved_31_28:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8063_STRUCT;

// **** D0F0xE4_WRAP_8015 Register Definition ****
// Address
#define D0F0xE4_WRAP_8015_ADDRESS                               0x8015

// Type
#define D0F0xE4_WRAP_8015_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8015_EnableD0StateReport_OFFSET            0
#define D0F0xE4_WRAP_8015_EnableD0StateReport_WIDTH             1
#define D0F0xE4_WRAP_8015_EnableD0StateReport_MASK              0x1
#define D0F0xE4_WRAP_8015_Reserved_1_1_OFFSET                   1
#define D0F0xE4_WRAP_8015_Reserved_1_1_WIDTH                    1
#define D0F0xE4_WRAP_8015_Reserved_1_1_MASK                     0x2
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk2p5x_OFFSET     2
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk2p5x_WIDTH      1
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk2p5x_MASK       0x4
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk2p5x_OFFSET      3
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk2p5x_WIDTH       1
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk2p5x_MASK        0x8
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk2p5x_OFFSET      4
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk2p5x_WIDTH       2
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk2p5x_MASK        0x30
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk2p5x_OFFSET       6
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk2p5x_WIDTH        2
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk2p5x_MASK         0xc0
#define D0F0xE4_WRAP_8015_Reserved_8_8_OFFSET                   8
#define D0F0xE4_WRAP_8015_Reserved_8_8_WIDTH                    1
#define D0F0xE4_WRAP_8015_Reserved_8_8_MASK                     0x100
#define D0F0xE4_WRAP_8015_SlowRefclkLcntGateForce_OFFSET        9
#define D0F0xE4_WRAP_8015_SlowRefclkLcntGateForce_WIDTH         1
#define D0F0xE4_WRAP_8015_SlowRefclkLcntGateForce_MASK          0x200
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk1x_OFFSET       10
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk1x_WIDTH        1
#define D0F0xE4_WRAP_8015_SlowRefclkThroughTxclk1x_MASK         0x400
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk1x_OFFSET        11
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk1x_WIDTH         1
#define D0F0xE4_WRAP_8015_SlowRefclkEnableTxclk1x_MASK          0x800
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk1x_OFFSET        12
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk1x_WIDTH         2
#define D0F0xE4_WRAP_8015_SlowRefclkDivideTxclk1x_MASK          0x3000
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk1x_OFFSET         14
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk1x_WIDTH          2
#define D0F0xE4_WRAP_8015_SlowRefclkBurstTxclk1x_MASK           0xc000
#define D0F0xE4_WRAP_8015_RefclkRegsGateLatency_OFFSET          16
#define D0F0xE4_WRAP_8015_RefclkRegsGateLatency_WIDTH           6
#define D0F0xE4_WRAP_8015_RefclkRegsGateLatency_MASK            0x3f0000
#define D0F0xE4_WRAP_8015_Reserved_22_22_OFFSET                 22
#define D0F0xE4_WRAP_8015_Reserved_22_22_WIDTH                  1
#define D0F0xE4_WRAP_8015_Reserved_22_22_MASK                   0x400000
#define D0F0xE4_WRAP_8015_RefclkRegsGateEnable_OFFSET           23
#define D0F0xE4_WRAP_8015_RefclkRegsGateEnable_WIDTH            1
#define D0F0xE4_WRAP_8015_RefclkRegsGateEnable_MASK             0x800000
#define D0F0xE4_WRAP_8015_RefclkBphyGateLatency_OFFSET          24
#define D0F0xE4_WRAP_8015_RefclkBphyGateLatency_WIDTH           6
#define D0F0xE4_WRAP_8015_RefclkBphyGateLatency_MASK            0x3f000000
#define D0F0xE4_WRAP_8015_Reserved_30_30_OFFSET                 30
#define D0F0xE4_WRAP_8015_Reserved_30_30_WIDTH                  1
#define D0F0xE4_WRAP_8015_Reserved_30_30_MASK                   0x40000000
#define D0F0xE4_WRAP_8015_RefclkBphyGateEnable_OFFSET           31
#define D0F0xE4_WRAP_8015_RefclkBphyGateEnable_WIDTH            1
#define D0F0xE4_WRAP_8015_RefclkBphyGateEnable_MASK             0x80000000

/// D0F0xE4_WRAP_8015
typedef union {
  struct {                                                              ///<
    UINT32                                      EnableD0StateReport:1 ; ///<
    UINT32                                             Reserved_1_1:1 ; ///<
    UINT32                               SlowRefclkThroughTxclk2p5x:1 ; ///<
    UINT32                                SlowRefclkEnableTxclk2p5x:1 ; ///<
    UINT32                                SlowRefclkDivideTxclk2p5x:2 ; ///<
    UINT32                                 SlowRefclkBurstTxclk2p5x:2 ; ///<
    UINT32                                             Reserved_8_8:1 ; ///<
    UINT32                                  SlowRefclkLcntGateForce:1 ; ///<
    UINT32                                 SlowRefclkThroughTxclk1x:1 ; ///<
    UINT32                                  SlowRefclkEnableTxclk1x:1 ; ///<
    UINT32                                  SlowRefclkDivideTxclk1x:2 ; ///<
    UINT32                                   SlowRefclkBurstTxclk1x:2 ; ///<
    UINT32                                    RefclkRegsGateLatency:6 ; ///<
    UINT32                                           Reserved_22_22:1 ; ///<
    UINT32                                     RefclkRegsGateEnable:1 ; ///<
    UINT32                                    RefclkBphyGateLatency:6 ; ///<
    UINT32                                           Reserved_30_30:1 ; ///<
    UINT32                                     RefclkBphyGateEnable:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8015_STRUCT;

// **** DxF0xE4_xB5 Register Definition ****
// Address
#define DxF0xE4_xB5_ADDRESS                                     0xb5

// Type
#define DxF0xE4_xB5_TYPE                                        TYPE_D4F0xE4
// Field Data
#define DxF0xE4_xB5_LcSelectDeemphasis_OFFSET                   0
#define DxF0xE4_xB5_LcSelectDeemphasis_WIDTH                    1
#define DxF0xE4_xB5_LcSelectDeemphasis_MASK                     0x1
#define DxF0xE4_xB5_LcSelectDeemphasisCntl_OFFSET               1
#define DxF0xE4_xB5_LcSelectDeemphasisCntl_WIDTH                2
#define DxF0xE4_xB5_LcSelectDeemphasisCntl_MASK                 0x6
#define DxF0xE4_xB5_LcRcvdDeemphasis_OFFSET                     3
#define DxF0xE4_xB5_LcRcvdDeemphasis_WIDTH                      1
#define DxF0xE4_xB5_LcRcvdDeemphasis_MASK                       0x8
#define DxF0xE4_xB5_LcCompToDetect_OFFSET                       4
#define DxF0xE4_xB5_LcCompToDetect_WIDTH                        1
#define DxF0xE4_xB5_LcCompToDetect_MASK                         0x10
#define DxF0xE4_xB5_LcResetTsxCntInRlockEn_OFFSET               5
#define DxF0xE4_xB5_LcResetTsxCntInRlockEn_WIDTH                1
#define DxF0xE4_xB5_LcResetTsxCntInRlockEn_MASK                 0x20
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptsAllowed_OFFSET     6
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptsAllowed_WIDTH      2
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptsAllowed_MASK       0xc0
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptFailed_OFFSET       8
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptFailed_WIDTH        1
#define DxF0xE4_xB5_LcAutoSpeedChangeAttemptFailed_MASK         0x100
#define DxF0xE4_xB5_LcClrFailedAutoSpdChangeCnt_OFFSET          9
#define DxF0xE4_xB5_LcClrFailedAutoSpdChangeCnt_WIDTH           1
#define DxF0xE4_xB5_LcClrFailedAutoSpdChangeCnt_MASK            0x200
#define DxF0xE4_xB5_LcEnhancedHotPlugEn_OFFSET                  10
#define DxF0xE4_xB5_LcEnhancedHotPlugEn_WIDTH                   1
#define DxF0xE4_xB5_LcEnhancedHotPlugEn_MASK                    0x400
#define DxF0xE4_xB5_LcRcvrDetEnOverride_OFFSET                  11
#define DxF0xE4_xB5_LcRcvrDetEnOverride_WIDTH                   1
#define DxF0xE4_xB5_LcRcvrDetEnOverride_MASK                    0x800
#define DxF0xE4_xB5_LcEhpRxPhyCmd_OFFSET                        12
#define DxF0xE4_xB5_LcEhpRxPhyCmd_WIDTH                         2
#define DxF0xE4_xB5_LcEhpRxPhyCmd_MASK                          0x3000
#define DxF0xE4_xB5_LcEhpTxPhyCmd_OFFSET                        14
#define DxF0xE4_xB5_LcEhpTxPhyCmd_WIDTH                         2
#define DxF0xE4_xB5_LcEhpTxPhyCmd_MASK                          0xc000
#define DxF0xE4_xB5_LcChipBifUsbIdleEn_OFFSET                   16
#define DxF0xE4_xB5_LcChipBifUsbIdleEn_WIDTH                    1
#define DxF0xE4_xB5_LcChipBifUsbIdleEn_MASK                     0x10000
#define DxF0xE4_xB5_LcL1BlockReconfigEn_OFFSET                  17
#define DxF0xE4_xB5_LcL1BlockReconfigEn_WIDTH                   1
#define DxF0xE4_xB5_LcL1BlockReconfigEn_MASK                    0x20000
#define DxF0xE4_xB5_LcAutoDisableGen2En_OFFSET                  18
#define DxF0xE4_xB5_LcAutoDisableGen2En_WIDTH                   1
#define DxF0xE4_xB5_LcAutoDisableGen2En_MASK                    0x40000
#define DxF0xE4_xB5_LcAutoDisableGen2MaxFailSel_OFFSET          19
#define DxF0xE4_xB5_LcAutoDisableGen2MaxFailSel_WIDTH           2
#define DxF0xE4_xB5_LcAutoDisableGen2MaxFailSel_MASK            0x180000
#define DxF0xE4_xB5_LcFastL1EntryExitEn_OFFSET                  21
#define DxF0xE4_xB5_LcFastL1EntryExitEn_WIDTH                   1
#define DxF0xE4_xB5_LcFastL1EntryExitEn_MASK                    0x200000
#define DxF0xE4_xB5_LcRxPhyCmdInactiveEnMode_OFFSET             22
#define DxF0xE4_xB5_LcRxPhyCmdInactiveEnMode_WIDTH              1
#define DxF0xE4_xB5_LcRxPhyCmdInactiveEnMode_MASK               0x400000
#define DxF0xE4_xB5_Reserved_31_23_OFFSET                       23
#define DxF0xE4_xB5_Reserved_31_23_WIDTH                        9
#define DxF0xE4_xB5_Reserved_31_23_MASK                         0xff800000

/// DxF0xE4_xB5
typedef union {
  struct {                                                              ///<
    UINT32                                       LcSelectDeemphasis:1 ; ///<
    UINT32                                   LcSelectDeemphasisCntl:2 ; ///<
    UINT32                                         LcRcvdDeemphasis:1 ; ///<
    UINT32                                           LcCompToDetect:1 ; ///<
    UINT32                                   LcResetTsxCntInRlockEn:1 ; ///<
    UINT32                         LcAutoSpeedChangeAttemptsAllowed:2 ; ///<
    UINT32                           LcAutoSpeedChangeAttemptFailed:1 ; ///<
    UINT32                              LcClrFailedAutoSpdChangeCnt:1 ; ///<
    UINT32                                      LcEnhancedHotPlugEn:1 ; ///<
    UINT32                                      LcRcvrDetEnOverride:1 ; ///<
    UINT32                                            LcEhpRxPhyCmd:2 ; ///<
    UINT32                                            LcEhpTxPhyCmd:2 ; ///<
    UINT32                                       LcChipBifUsbIdleEn:1 ; ///<
    UINT32                                      LcL1BlockReconfigEn:1 ; ///<
    UINT32                                      LcAutoDisableGen2En:1 ; ///<
    UINT32                              LcAutoDisableGen2MaxFailSel:2 ; ///<
    UINT32                                      LcFastL1EntryExitEn:1 ; ///<
    UINT32                                 LcRxPhyCmdInactiveEnMode:1 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxF0xE4_xB5_STRUCT;


// **** D0F0xE4_PHY_6006 Register Definition ****
// Address
#define D0F0xE4_PHY_6006_ADDRESS                                0x6006

// Type
#define D0F0xE4_PHY_6006_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_6006_TxMarginNom_OFFSET                     0
#define D0F0xE4_PHY_6006_TxMarginNom_WIDTH                      8
#define D0F0xE4_PHY_6006_TxMarginNom_MASK                       0xff
#define D0F0xE4_PHY_6006_DeemphGen1Nom_OFFSET                   8
#define D0F0xE4_PHY_6006_DeemphGen1Nom_WIDTH                    8
#define D0F0xE4_PHY_6006_DeemphGen1Nom_MASK                     0xff00
#define D0F0xE4_PHY_6006_Deemph35Gen2Nom_OFFSET                 16
#define D0F0xE4_PHY_6006_Deemph35Gen2Nom_WIDTH                  8
#define D0F0xE4_PHY_6006_Deemph35Gen2Nom_MASK                   0xff0000
#define D0F0xE4_PHY_6006_Deemph60Gen2Nom_OFFSET                 24
#define D0F0xE4_PHY_6006_Deemph60Gen2Nom_WIDTH                  8
#define D0F0xE4_PHY_6006_Deemph60Gen2Nom_MASK                   0xff000000

/// D0F0xE4_PHY_6006
typedef union {
  struct {                                                              ///<
    UINT32                                              TxMarginNom:8 ; ///<
    UINT32                                            DeemphGen1Nom:8 ; ///<
    UINT32                                          Deemph35Gen2Nom:8 ; ///<
    UINT32                                          Deemph60Gen2Nom:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_6006_STRUCT;

// **** GMMx00 Register Definition ****
// Address
#define GMMx00_ADDRESS                                          0x0

// Type
#define GMMx00_TYPE                                             TYPE_GMM
// Field Data
#define GMMx00_Offset_OFFSET                                    0
#define GMMx00_Offset_WIDTH                                     31
#define GMMx00_Offset_MASK                                      0x7fffffff
#define GMMx00_Aper_OFFSET                                      31
#define GMMx00_Aper_WIDTH                                       1
#define GMMx00_Aper_MASK                                        0x80000000

/// GMMx00
typedef union {
  struct {                                                              ///<
    UINT32                                                   Offset:31; ///<
    UINT32                                                     Aper:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx00_STRUCT;

// **** GMMx04 Register Definition ****
// Address
#define GMMx04_ADDRESS                                          0x4

// Type
#define GMMx04_TYPE                                             TYPE_GMM
// Field Data
#define GMMx04_Data_OFFSET                                      0
#define GMMx04_Data_WIDTH                                       32
#define GMMx04_Data_MASK                                        0xffffffff

/// GMMx04
typedef union {
  struct {                                                              ///<
    UINT32                                                     Data:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx04_STRUCT;


// **** D0F0xE4_WRAP_8016 Register Definition ****
// Address
#define D0F0xE4_WRAP_8016_ADDRESS                               0x8016

// Type
#define D0F0xE4_WRAP_8016_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_8016_CalibAckLatency_OFFSET                0
#define D0F0xE4_WRAP_8016_CalibAckLatency_WIDTH                 6
#define D0F0xE4_WRAP_8016_CalibAckLatency_MASK                  0x3f
#define D0F0xE4_WRAP_8016_Reserved_7_6_OFFSET                   6
#define D0F0xE4_WRAP_8016_Reserved_7_6_WIDTH                    2
#define D0F0xE4_WRAP_8016_Reserved_7_6_MASK                     0xc0
#define D0F0xE4_WRAP_8016_CalibDoneSelPifA_OFFSET               8
#define D0F0xE4_WRAP_8016_CalibDoneSelPifA_WIDTH                1
#define D0F0xE4_WRAP_8016_CalibDoneSelPifA_MASK                 0x100
#define D0F0xE4_WRAP_8016_Reserved_9_9_OFFSET                   9
#define D0F0xE4_WRAP_8016_Reserved_9_9_WIDTH                    1
#define D0F0xE4_WRAP_8016_Reserved_9_9_MASK                     0x200
#define D0F0xE4_WRAP_8016_Reserved_10_10_OFFSET                 10
#define D0F0xE4_WRAP_8016_Reserved_10_10_WIDTH                  1
#define D0F0xE4_WRAP_8016_Reserved_10_10_MASK                   0x400
#define D0F0xE4_WRAP_8016_Reserved_11_11_OFFSET                 11
#define D0F0xE4_WRAP_8016_Reserved_11_11_WIDTH                  1
#define D0F0xE4_WRAP_8016_Reserved_11_11_MASK                   0x800
#define D0F0xE4_WRAP_8016_Gen1OnlyEngage_OFFSET                 12
#define D0F0xE4_WRAP_8016_Gen1OnlyEngage_WIDTH                  1
#define D0F0xE4_WRAP_8016_Gen1OnlyEngage_MASK                   0x1000
#define D0F0xE4_WRAP_8016_Gen1OnlyEngaged_OFFSET                13
#define D0F0xE4_WRAP_8016_Gen1OnlyEngaged_WIDTH                 1
#define D0F0xE4_WRAP_8016_Gen1OnlyEngaged_MASK                  0x2000
#define D0F0xE4_WRAP_8016_Reserved_15_14_OFFSET                 14
#define D0F0xE4_WRAP_8016_Reserved_15_14_WIDTH                  2
#define D0F0xE4_WRAP_8016_Reserved_15_14_MASK                   0xc000
#define D0F0xE4_WRAP_8016_LclkDynGateLatency_OFFSET             16
#define D0F0xE4_WRAP_8016_LclkDynGateLatency_WIDTH              6
#define D0F0xE4_WRAP_8016_LclkDynGateLatency_MASK               0x3f0000
#define D0F0xE4_WRAP_8016_LclkGateFree_OFFSET                   22
#define D0F0xE4_WRAP_8016_LclkGateFree_WIDTH                    1
#define D0F0xE4_WRAP_8016_LclkGateFree_MASK                     0x400000
#define D0F0xE4_WRAP_8016_LclkDynGateEnable_OFFSET              23
#define D0F0xE4_WRAP_8016_LclkDynGateEnable_WIDTH               1
#define D0F0xE4_WRAP_8016_LclkDynGateEnable_MASK                0x800000
#define D0F0xE4_WRAP_8016_Reserved_31_24_OFFSET                 24
#define D0F0xE4_WRAP_8016_Reserved_31_24_WIDTH                  8
#define D0F0xE4_WRAP_8016_Reserved_31_24_MASK                   0xff000000

/// D0F0xE4_WRAP_8016
typedef union {
  struct {                                                              ///<
    UINT32                                          CalibAckLatency:6 ; ///<
    UINT32                                             Reserved_7_6:2 ; ///<
    UINT32                                         CalibDoneSelPifA:1 ; ///<
    UINT32                                             Reserved_9_9:1 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                           Gen1OnlyEngage:1 ; ///<
    UINT32                                          Gen1OnlyEngaged:1 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                       LclkDynGateLatency:6 ; ///<
    UINT32                                             LclkGateFree:1 ; ///<
    UINT32                                        LclkDynGateEnable:1 ; ///<
    UINT32                                           Reserved_31_24:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_8016_STRUCT;

#endif

