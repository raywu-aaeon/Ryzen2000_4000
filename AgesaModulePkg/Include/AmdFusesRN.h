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

#ifndef _AMD_FUSES_SSP_H_
#define _AMD_FUSES_SSP_H_

typedef struct {
  UINT16     EnumIndex;              ///< Number of the associated enum value
  UINT16     Size;                   ///< Size of fuse (in bits)
  UINT8      StartBit;               ///< Start bit of fuse within UINT32 word aligned read
  UINT32     SmnStartAddress;        ///< Unaligned address of fuse within SMN
} AMD_FUSE;

///
/// Enum containing fuse indices for the fuse table. Uncomment
/// to use any of these values and have them also present in the
/// table.
///
enum AmdFusesEnum {
//AUDIO_AZ_AUDIO_AZ_GROUP0_DATA                           = 0,
//CCX_BYPASSFUSE                                          = 1,
//CCX_BisiEn                                              = 2,
//CCX_BistEn                                              = 3,
//CCX_BistExecCfg                                         = 4,
//CCX_BypassL3Fuse                                        = 5,
//CCX_CCX0CoreID0                                         = 6,
//CCX_CCX0CoreID1                                         = 7,
//CCX_CCX0CoreID10                                        = 8,
//CCX_CCX0CoreID11                                        = 9,
//CCX_CCX0CoreID2                                         = 10,
//CCX_CCX0CoreID3                                         = 11,
//CCX_CCX0CoreID4                                         = 12,
//CCX_CCX0CoreID5                                         = 13,
//CCX_CCX0CoreID6                                         = 14,
//CCX_CCX0CoreID7                                         = 15,
//CCX_CCX0CoreID8                                         = 16,
//CCX_CCX0CoreID9                                         = 17,
//CCX_CCX0L1Repair0                                       = 18,
//CCX_CCX0L1Repair1                                       = 19,
//CCX_CCX0L1Repair10                                      = 20,
//CCX_CCX0L1Repair11                                      = 21,
//CCX_CCX0L1Repair2                                       = 22,
//CCX_CCX0L1Repair3                                       = 23,
//CCX_CCX0L1Repair4                                       = 24,
//CCX_CCX0L1Repair5                                       = 25,
//CCX_CCX0L1Repair6                                       = 26,
//CCX_CCX0L1Repair7                                       = 27,
//CCX_CCX0L1Repair8                                       = 28,
//CCX_CCX0L1Repair9                                       = 29,
//CCX_CCX0L2Repair0                                       = 30,
//CCX_CCX0L2Repair1                                       = 31,
//CCX_CCX0L2Repair10                                      = 32,
//CCX_CCX0L2Repair11                                      = 33,
//CCX_CCX0L2Repair2                                       = 34,
//CCX_CCX0L2Repair3                                       = 35,
//CCX_CCX0L2Repair4                                       = 36,
//CCX_CCX0L2Repair5                                       = 37,
//CCX_CCX0L2Repair6                                       = 38,
//CCX_CCX0L2Repair7                                       = 39,
//CCX_CCX0L2Repair8                                       = 40,
//CCX_CCX0L2Repair9                                       = 41,
//CCX_CCX0L3M0EvenBankDis                                 = 42,
//CCX_CCX0L3M0OddBankDis                                  = 43,
//CCX_CCX0L3M1EvenBankDis                                 = 44,
//CCX_CCX0L3M1OddBankDis                                  = 45,
//CCX_CCX0L3M2EvenBankDis                                 = 46,
//CCX_CCX0L3M2OddBankDis                                  = 47,
//CCX_CCX0L3M3EvenBankDis                                 = 48,
//CCX_CCX0L3M3OddBankDis                                  = 49,
//CCX_CCX0L3MReserved                                     = 50,
//CCX_CCX0L3PllFllCtl2RladrCode                           = 51,
//CCX_CCX0L3PllFllCtl4BCoarse                             = 52,
//CCX_CCX0L3PllFllCtl4BOffsetA                            = 53,
//CCX_CCX0L3PllFllCtl4BOffsetB                            = 54,
//CCX_CCX0L3PllFllCtl4BStep                               = 55,
//CCX_CCX0L3PllFllCtl4DisVroCap                           = 56,
//CCX_CCX0L3PllFllCtl4Rsvd31_25                           = 57,
//CCX_CCX0L3PllFllCtl4V2CcGain                            = 58,
//CCX_CCX0L3Repair0Fuses0                                 = 59,
//CCX_CCX0L3Repair0Fuses1                                 = 60,
//CCX_CCX0L3Repair0Fuses10                                = 61,
//CCX_CCX0L3Repair0Fuses11                                = 62,
//CCX_CCX0L3Repair0Fuses12                                = 63,
//CCX_CCX0L3Repair0Fuses13                                = 64,
//CCX_CCX0L3Repair0Fuses14                                = 65,
//CCX_CCX0L3Repair0Fuses15                                = 66,
//CCX_CCX0L3Repair0Fuses16                                = 67,
//CCX_CCX0L3Repair0Fuses17                                = 68,
//CCX_CCX0L3Repair0Fuses18                                = 69,
//CCX_CCX0L3Repair0Fuses19                                = 70,
//CCX_CCX0L3Repair0Fuses2                                 = 71,
//CCX_CCX0L3Repair0Fuses20                                = 72,
//CCX_CCX0L3Repair0Fuses21                                = 73,
//CCX_CCX0L3Repair0Fuses22                                = 74,
//CCX_CCX0L3Repair0Fuses23                                = 75,
//CCX_CCX0L3Repair0Fuses24                                = 76,
//CCX_CCX0L3Repair0Fuses25                                = 77,
//CCX_CCX0L3Repair0Fuses26                                = 78,
//CCX_CCX0L3Repair0Fuses27                                = 79,
//CCX_CCX0L3Repair0Fuses28                                = 80,
//CCX_CCX0L3Repair0Fuses29                                = 81,
//CCX_CCX0L3Repair0Fuses3                                 = 82,
//CCX_CCX0L3Repair0Fuses30                                = 83,
//CCX_CCX0L3Repair0Fuses31                                = 84,
//CCX_CCX0L3Repair0Fuses4                                 = 85,
//CCX_CCX0L3Repair0Fuses5                                 = 86,
//CCX_CCX0L3Repair0Fuses6                                 = 87,
//CCX_CCX0L3Repair0Fuses7                                 = 88,
//CCX_CCX0L3Repair0Fuses8                                 = 89,
//CCX_CCX0L3Repair0Fuses9                                 = 90,
//CCX_CCX0L3Repair1Fuses0                                 = 91,
//CCX_CCX0L3Repair1Fuses1                                 = 92,
//CCX_CCX0L3Repair1Fuses10                                = 93,
//CCX_CCX0L3Repair1Fuses11                                = 94,
//CCX_CCX0L3Repair1Fuses12                                = 95,
//CCX_CCX0L3Repair1Fuses13                                = 96,
//CCX_CCX0L3Repair1Fuses14                                = 97,
//CCX_CCX0L3Repair1Fuses15                                = 98,
//CCX_CCX0L3Repair1Fuses16                                = 99,
//CCX_CCX0L3Repair1Fuses17                                = 100,
//CCX_CCX0L3Repair1Fuses18                                = 101,
//CCX_CCX0L3Repair1Fuses19                                = 102,
//CCX_CCX0L3Repair1Fuses2                                 = 103,
//CCX_CCX0L3Repair1Fuses20                                = 104,
//CCX_CCX0L3Repair1Fuses21                                = 105,
//CCX_CCX0L3Repair1Fuses22                                = 106,
//CCX_CCX0L3Repair1Fuses23                                = 107,
//CCX_CCX0L3Repair1Fuses24                                = 108,
//CCX_CCX0L3Repair1Fuses25                                = 109,
//CCX_CCX0L3Repair1Fuses26                                = 110,
//CCX_CCX0L3Repair1Fuses27                                = 111,
//CCX_CCX0L3Repair1Fuses28                                = 112,
//CCX_CCX0L3Repair1Fuses29                                = 113,
//CCX_CCX0L3Repair1Fuses3                                 = 114,
//CCX_CCX0L3Repair1Fuses30                                = 115,
//CCX_CCX0L3Repair1Fuses31                                = 116,
//CCX_CCX0L3Repair1Fuses4                                 = 117,
//CCX_CCX0L3Repair1Fuses5                                 = 118,
//CCX_CCX0L3Repair1Fuses6                                 = 119,
//CCX_CCX0L3Repair1Fuses7                                 = 120,
//CCX_CCX0L3Repair1Fuses8                                 = 121,
//CCX_CCX0L3Repair1Fuses9                                 = 122,
//CCX_CCX0MaFddDD0OffsetHi                                = 123,
//CCX_CCX0MaFddDD0OffsetLo                                = 124,
//CCX_CCX0MaFddDD1OffsetHi                                = 125,
//CCX_CCX0MaFddDD1OffsetLo                                = 126,
//CCX_CCX0MaFddDD2OffsetHi                                = 127,
//CCX_CCX0MaFddDD2OffsetLo                                = 128,
//CCX_CCX0MaFddDD3OffsetHi                                = 129,
//CCX_CCX0MaFddDD3OffsetLo                                = 130,
//CCX_CCX0MaFddDDL3OffsetHi                               = 131,
//CCX_CCX0MaFddDDL3OffsetLo                               = 132,
//CCX_CCX0MaFddDldo0OffsetHi                              = 133,
//CCX_CCX0MaFddDldo0OffsetLo                              = 134,
//CCX_CCX0MaFddDldo1OffsetHi                              = 135,
//CCX_CCX0MaFddDldo1OffsetLo                              = 136,
//CCX_CCX0MaFddDldo2OffsetHi                              = 137,
//CCX_CCX0MaFddDldo2OffsetLo                              = 138,
//CCX_CCX0MaFddDldo3OffsetHi                              = 139,
//CCX_CCX0MaFddDldo3OffsetLo                              = 140,
//CCX_CCX0Repair0                                         = 141,
//CCX_CCX0Repair10Hi                                      = 142,
//CCX_CCX0Repair10Lo                                      = 143,
//CCX_CCX0Repair11                                        = 144,
//CCX_CCX0Repair1Hi                                       = 145,
//CCX_CCX0Repair1Lo                                       = 146,
//CCX_CCX0Repair2                                         = 147,
//CCX_CCX0Repair3                                         = 148,
//CCX_CCX0Repair4Hi                                       = 149,
//CCX_CCX0Repair4Lo                                       = 150,
//CCX_CCX0Repair5                                         = 151,
//CCX_CCX0Repair6                                         = 152,
//CCX_CCX0Repair7Hi                                       = 153,
//CCX_CCX0Repair7Lo                                       = 154,
//CCX_CCX0Repair8                                         = 155,
//CCX_CCX0Repair9                                         = 156,
//CCX_CCX0Reserved0                                       = 157,
//CCX_CCX0Reserved3                                       = 158,
//CCX_CCX0Reserved6                                       = 159,
//CCX_CCX0Reserved9                                       = 160,
//CCX_CCX1CoreID0                                         = 161,
//CCX_CCX1CoreID1                                         = 162,
//CCX_CCX1CoreID10                                        = 163,
//CCX_CCX1CoreID11                                        = 164,
//CCX_CCX1CoreID2                                         = 165,
//CCX_CCX1CoreID3                                         = 166,
//CCX_CCX1CoreID4                                         = 167,
//CCX_CCX1CoreID5                                         = 168,
//CCX_CCX1CoreID6                                         = 169,
//CCX_CCX1CoreID7                                         = 170,
//CCX_CCX1CoreID8                                         = 171,
//CCX_CCX1CoreID9                                         = 172,
//CCX_CCX1L1Repair0                                       = 173,
//CCX_CCX1L1Repair1                                       = 174,
//CCX_CCX1L1Repair10                                      = 175,
//CCX_CCX1L1Repair11                                      = 176,
//CCX_CCX1L1Repair2                                       = 177,
//CCX_CCX1L1Repair3                                       = 178,
//CCX_CCX1L1Repair4                                       = 179,
//CCX_CCX1L1Repair5                                       = 180,
//CCX_CCX1L1Repair6                                       = 181,
//CCX_CCX1L1Repair7                                       = 182,
//CCX_CCX1L1Repair8                                       = 183,
//CCX_CCX1L1Repair9                                       = 184,
//CCX_CCX1L2Repair0                                       = 185,
//CCX_CCX1L2Repair1                                       = 186,
//CCX_CCX1L2Repair10                                      = 187,
//CCX_CCX1L2Repair11                                      = 188,
//CCX_CCX1L2Repair2                                       = 189,
//CCX_CCX1L2Repair3                                       = 190,
//CCX_CCX1L2Repair4                                       = 191,
//CCX_CCX1L2Repair5                                       = 192,
//CCX_CCX1L2Repair6                                       = 193,
//CCX_CCX1L2Repair7                                       = 194,
//CCX_CCX1L2Repair8                                       = 195,
//CCX_CCX1L2Repair9                                       = 196,
//CCX_CCX1L3M0EvenBankDis                                 = 197,
//CCX_CCX1L3M0OddBankDis                                  = 198,
//CCX_CCX1L3M1EvenBankDis                                 = 199,
//CCX_CCX1L3M1OddBankDis                                  = 200,
//CCX_CCX1L3M2EvenBankDis                                 = 201,
//CCX_CCX1L3M2OddBankDis                                  = 202,
//CCX_CCX1L3M3EvenBankDis                                 = 203,
//CCX_CCX1L3M3OddBankDis                                  = 204,
//CCX_CCX1L3MReserved                                     = 205,
//CCX_CCX1L3PllFllCtl2RladrCode                           = 206,
//CCX_CCX1L3PllFllCtl4BCoarse                             = 207,
//CCX_CCX1L3PllFllCtl4BOffsetA                            = 208,
//CCX_CCX1L3PllFllCtl4BOffsetB                            = 209,
//CCX_CCX1L3PllFllCtl4BStep                               = 210,
//CCX_CCX1L3PllFllCtl4DisVroCap                           = 211,
//CCX_CCX1L3PllFllCtl4Rsvd31_25                           = 212,
//CCX_CCX1L3PllFllCtl4V2CcGain                            = 213,
//CCX_CCX1L3Repair0Fuses0                                 = 214,
//CCX_CCX1L3Repair0Fuses1                                 = 215,
//CCX_CCX1L3Repair0Fuses10                                = 216,
//CCX_CCX1L3Repair0Fuses11                                = 217,
//CCX_CCX1L3Repair0Fuses12                                = 218,
//CCX_CCX1L3Repair0Fuses13                                = 219,
//CCX_CCX1L3Repair0Fuses14                                = 220,
//CCX_CCX1L3Repair0Fuses15                                = 221,
//CCX_CCX1L3Repair0Fuses16                                = 222,
//CCX_CCX1L3Repair0Fuses17                                = 223,
//CCX_CCX1L3Repair0Fuses18                                = 224,
//CCX_CCX1L3Repair0Fuses19                                = 225,
//CCX_CCX1L3Repair0Fuses2                                 = 226,
//CCX_CCX1L3Repair0Fuses20                                = 227,
//CCX_CCX1L3Repair0Fuses21                                = 228,
//CCX_CCX1L3Repair0Fuses22                                = 229,
//CCX_CCX1L3Repair0Fuses23                                = 230,
//CCX_CCX1L3Repair0Fuses24                                = 231,
//CCX_CCX1L3Repair0Fuses25                                = 232,
//CCX_CCX1L3Repair0Fuses26                                = 233,
//CCX_CCX1L3Repair0Fuses27                                = 234,
//CCX_CCX1L3Repair0Fuses28                                = 235,
//CCX_CCX1L3Repair0Fuses29                                = 236,
//CCX_CCX1L3Repair0Fuses3                                 = 237,
//CCX_CCX1L3Repair0Fuses30                                = 238,
//CCX_CCX1L3Repair0Fuses31                                = 239,
//CCX_CCX1L3Repair0Fuses4                                 = 240,
//CCX_CCX1L3Repair0Fuses5                                 = 241,
//CCX_CCX1L3Repair0Fuses6                                 = 242,
//CCX_CCX1L3Repair0Fuses7                                 = 243,
//CCX_CCX1L3Repair0Fuses8                                 = 244,
//CCX_CCX1L3Repair0Fuses9                                 = 245,
//CCX_CCX1L3Repair1Fuses0                                 = 246,
//CCX_CCX1L3Repair1Fuses1                                 = 247,
//CCX_CCX1L3Repair1Fuses10                                = 248,
//CCX_CCX1L3Repair1Fuses11                                = 249,
//CCX_CCX1L3Repair1Fuses12                                = 250,
//CCX_CCX1L3Repair1Fuses13                                = 251,
//CCX_CCX1L3Repair1Fuses14                                = 252,
//CCX_CCX1L3Repair1Fuses15                                = 253,
//CCX_CCX1L3Repair1Fuses16                                = 254,
//CCX_CCX1L3Repair1Fuses17                                = 255,
//CCX_CCX1L3Repair1Fuses18                                = 256,
//CCX_CCX1L3Repair1Fuses19                                = 257,
//CCX_CCX1L3Repair1Fuses2                                 = 258,
//CCX_CCX1L3Repair1Fuses20                                = 259,
//CCX_CCX1L3Repair1Fuses21                                = 260,
//CCX_CCX1L3Repair1Fuses22                                = 261,
//CCX_CCX1L3Repair1Fuses23                                = 262,
//CCX_CCX1L3Repair1Fuses24                                = 263,
//CCX_CCX1L3Repair1Fuses25                                = 264,
//CCX_CCX1L3Repair1Fuses26                                = 265,
//CCX_CCX1L3Repair1Fuses27                                = 266,
//CCX_CCX1L3Repair1Fuses28                                = 267,
//CCX_CCX1L3Repair1Fuses29                                = 268,
//CCX_CCX1L3Repair1Fuses3                                 = 269,
//CCX_CCX1L3Repair1Fuses30                                = 270,
//CCX_CCX1L3Repair1Fuses31                                = 271,
//CCX_CCX1L3Repair1Fuses4                                 = 272,
//CCX_CCX1L3Repair1Fuses5                                 = 273,
//CCX_CCX1L3Repair1Fuses6                                 = 274,
//CCX_CCX1L3Repair1Fuses7                                 = 275,
//CCX_CCX1L3Repair1Fuses8                                 = 276,
//CCX_CCX1L3Repair1Fuses9                                 = 277,
//CCX_CCX1MaFddDD0OffsetHi                                = 278,
//CCX_CCX1MaFddDD0OffsetLo                                = 279,
//CCX_CCX1MaFddDD1OffsetHi                                = 280,
//CCX_CCX1MaFddDD1OffsetLo                                = 281,
//CCX_CCX1MaFddDD2OffsetHi                                = 282,
//CCX_CCX1MaFddDD2OffsetLo                                = 283,
//CCX_CCX1MaFddDD3OffsetHi                                = 284,
//CCX_CCX1MaFddDD3OffsetLo                                = 285,
//CCX_CCX1MaFddDDL3OffsetHi                               = 286,
//CCX_CCX1MaFddDDL3OffsetLo                               = 287,
//CCX_CCX1MaFddDDPad                                      = 288,
//CCX_CCX1MaFddDldo0OffsetHi                              = 289,
//CCX_CCX1MaFddDldo0OffsetLo                              = 290,
//CCX_CCX1MaFddDldo1OffsetHi                              = 291,
//CCX_CCX1MaFddDldo1OffsetLo                              = 292,
//CCX_CCX1MaFddDldo2OffsetHi                              = 293,
//CCX_CCX1MaFddDldo2OffsetLo                              = 294,
//CCX_CCX1MaFddDldo3OffsetHi                              = 295,
//CCX_CCX1MaFddDldo3OffsetLo                              = 296,
//CCX_CCX1Repair0                                         = 297,
//CCX_CCX1Repair10Hi                                      = 298,
//CCX_CCX1Repair10Lo                                      = 299,
//CCX_CCX1Repair11                                        = 300,
//CCX_CCX1Repair1Hi                                       = 301,
//CCX_CCX1Repair1Lo                                       = 302,
//CCX_CCX1Repair2                                         = 303,
//CCX_CCX1Repair3                                         = 304,
//CCX_CCX1Repair4Hi                                       = 305,
//CCX_CCX1Repair4Lo                                       = 306,
//CCX_CCX1Repair5                                         = 307,
//CCX_CCX1Repair6                                         = 308,
//CCX_CCX1Repair7Hi                                       = 309,
//CCX_CCX1Repair7Lo                                       = 310,
//CCX_CCX1Repair8                                         = 311,
//CCX_CCX1Repair9                                         = 312,
//CCX_CCX1Reserved0                                       = 313,
//CCX_CCX1Reserved3                                       = 314,
//CCX_CCX1Reserved6                                       = 315,
//CCX_CCX1Reserved9                                       = 316,
//CCX_COLDRESETMBISIEN                                    = 317,
//CCX_COLDRESETMBISTEN                                    = 318,
//CCX_CPLB_Reserved0                                      = 319,
//CCX_CPLB_Reserved1                                      = 320,
//CCX_CacheDiagDis                                        = 321,
//CCX_CcxSpare0                                           = 322,
//CCX_CcxSpare1                                           = 323,
//CCX_ChL3InitPkg1Reserved_31_29                          = 324,
//CCX_ChL3InitPkg1Reserved_3_3                            = 325,
//CCX_ChL3InitPkg2Reserved_31_28                          = 326,
//CCX_ChL3PllBwCtlCoarseReserved_11_11                    = 327,
//CCX_ChL3PllBwCtlCoarseReserved_6_6                      = 328,
//CCX_ComplexId_Reserved                                  = 329,
//CCX_ConservativeLock                                    = 330,
//CCX_CoreDis_Reserved                                    = 331,
//CCX_CoreFunctionalSpareFuses                            = 332,
//CCX_CoreResetDidMargin                                  = 333,
//CCX_DCRAM0_FusBstStrenth                                = 334,
//CCX_DCRAM0_FusKprEn                                     = 335,
//CCX_DCRAM0_FusSblKprEn                                  = 336,
//CCX_DCRAM0_FusTimAdjBoost                               = 337,
//CCX_DCRAM0_FusTimAdjPDly                                = 338,
//CCX_DCRAM1_FusBstStrenth                                = 339,
//CCX_DCRAM1_FusKprEn                                     = 340,
//CCX_DCRAM1_FusSblKprEn                                  = 341,
//CCX_DCRAM1_FusTimAdjBoost                               = 342,
//CCX_DCRAM1_FusTimAdjPDly                                = 343,
//CCX_DC_Reserved                                         = 344,
//CCX_DDCA_FCTL                                           = 345,
//CCX_DDCA_RCTL                                           = 346,
//CCX_DEFUSE_AesDisable                                   = 347,
//CCX_DEFUSE_UcodePatchEncrypt                            = 348,
//CCX_DERAM0_FusBstStrenth                                = 349,
//CCX_DERAM0_FusKprEn                                     = 350,
//CCX_DERAM0_FusSblKprEn                                  = 351,
//CCX_DERAM0_FusTimAdjBoost                               = 352,
//CCX_DERAM0_FusTimAdjPDly                                = 353,
//CCX_DERAM1_FusBstStrenth                                = 354,
//CCX_DERAM1_FusKprEn                                     = 355,
//CCX_DERAM1_FusSblKprEn                                  = 356,
//CCX_DERAM1_FusTimAdjBoost                               = 357,
//CCX_DERAM1_FusTimAdjPDly                                = 358,
//CCX_DEROM_FusKprEn                                      = 359,
//CCX_DEROM_FusSblKprEn                                   = 360,
//CCX_DEROM_FusTimAdjPDly                                 = 361,
//CCX_DE_Reserved                                         = 362,
//CCX_DfsStretchAmount                                    = 363,
//CCX_DfsStretchEnable                                    = 364,
//CCX_DroopSyncSelect                                     = 365,
//CCX_DutyAdj2phase                                       = 366,
//CCX_DutyAdj8phase                                       = 367,
//CCX_EX_Reserved                                         = 368,
//CCX_EnableDD                                            = 369,
//CCX_FP_Reserved                                         = 370,
//CCX_FreqMode                                            = 371,
//CCX_FsmCodeMargin                                       = 372,
//CCX_FsmWaitCycles                                       = 373,
//CCX_FuseProgDone                                        = 374,
//CCX_GRSBREAKPOINTCFG                                    = 375,
//CCX_GlbRstPause                                         = 376,
//CCX_HARDREPAIREN_1                                      = 377,
//CCX_HDL3DatSuperVminmaxProg                             = 378,
//CCX_HDbootSuperVmaxEn                                   = 379,
//CCX_HDbootSuperVminEn                                   = 380,
//CCX_HardRepairEn_0                                      = 381,
//CCX_ICRAM0_FusBstStrenth                                = 382,
//CCX_ICRAM0_FusKprEn                                     = 383,
//CCX_ICRAM0_FusSblKprEn                                  = 384,
//CCX_ICRAM0_FusTimAdjBoost                               = 385,
//CCX_ICRAM0_FusTimAdjPDly                                = 386,
//CCX_ICRAM1_FusBstStrenth                                = 387,
//CCX_ICRAM1_FusKprEn                                     = 388,
//CCX_ICRAM1_FusSblKprEn                                  = 389,
//CCX_ICRAM1_FusTimAdjBoost                               = 390,
//CCX_ICRAM1_FusTimAdjPDly                                = 391,
//CCX_ICRAM_Reserved                                      = 392,
//CCX_L23SuperVmaxThreshold                               = 393,
//CCX_L23SuperVminThreshold                               = 394,
//CCX_L2RAM_DWQSTPC                                       = 395,
//CCX_L2RAM_DataSTPC                                      = 396,
//CCX_L2RAM_Reserved0                                     = 397,
//CCX_L2RAM_Reserved1                                     = 398,
//CCX_L2RAM_SuperVminmaxProg                              = 399,
//CCX_L2RAM_TWQSTPC                                       = 400,
//CCX_L2RAM_TagSTPC                                       = 401,
//CCX_L3BootSuperVmaxEn                                   = 402,
//CCX_L3BootSuperVminEn                                   = 403,
//CCX_L3FBase0_Reserved                                   = 404,
//CCX_L3FBase1_Reserved_15_12                             = 405,
//CCX_L3FasterThanDF                                      = 406,
//CCX_L3HDSuperVmaxThreshold                              = 407,
//CCX_L3HDSuperVminThreshold                              = 408,
//CCX_L3MCfg                                              = 409,
//CCX_L3MDataCfg0                                         = 410,
//CCX_L3MDataCfg1                                         = 411,
//CCX_L3PllClk0Pdly                                       = 412,
//CCX_L3PllClk1Pdly                                       = 413,
//CCX_L3PllClk2Pdly                                       = 414,
//CCX_L3PllClk3Pdly                                       = 415,
//CCX_L3PllClk4Pdly                                       = 416,
//CCX_L3PllClkDutyAdj                                     = 417,
//CCX_L3PllDpllCfg3                                       = 418,
//CCX_L3PllFllCtl0Enable                                  = 419,
//CCX_L3PllFllCtl1ClkStretchEn                            = 420,
//CCX_L3PllFllCtl1DecMode1                                = 421,
//CCX_L3PllFllCtl1DecMode2                                = 422,
//CCX_L3PllFllCtl1DecWr                                   = 423,
//CCX_L3PllFllCtl1DroopDetEn                              = 424,
//CCX_L3PllFllCtl1FllDftDataSel                           = 425,
//CCX_L3PllFllCtl1FllNegErrSlope                          = 426,
//CCX_L3PllFllCtl1FllPerfCntrEn                           = 427,
//CCX_L3PllFllCtl1FllPosErrSlope                          = 428,
//CCX_L3PllFllCtl1FllPwrUpSeqDis                          = 429,
//CCX_L3PllFllCtl1FreqOffsetExp                           = 430,
//CCX_L3PllFllCtl1FreqOffsetMant                          = 431,
//CCX_L3PllFllCtl1NctlFreezeCmpSel                        = 432,
//CCX_L3PllFllCtl1NctlFreezeEn                            = 433,
//CCX_L3PllFllCtl1StaticStretchBoost                      = 434,
//CCX_L3PllFllCtl1StaticStretchEn                         = 435,
//CCX_L3PllFllCtl1StaticStretchPct                        = 436,
//CCX_L3PllFllCtl2DecAddr                                 = 437,
//CCX_L3PllFllCtl2DecData                                 = 438,
//CCX_L3PllFllCtl2EnHighBw                                = 439,
//CCX_L3PllFllCtl2PllBwBoostEn                            = 440,
//CCX_L3PllFllCtl2Rsvd26_16                               = 441,
//CCX_L3PllFllCtl2SelBump                                 = 442,
//CCX_L3PllFllCtl2SelRladderX                             = 443,
//CCX_L3PllFllCtl2ShortRcFileX                            = 444,
//CCX_L3PllFllCtl2VrefPwrOn                               = 445,
//CCX_L3PllFllCtl3AnaobsSel                               = 446,
//CCX_L3PllFllCtl3DdOutEn                                 = 447,
//CCX_L3PllFllCtl3DdSel1                                  = 448,
//CCX_L3PllFllCtl3DdSel2                                  = 449,
//CCX_L3PllFllCtl3Rsvd                                    = 450,
//CCX_L3PllFllCtl3SfEn                                    = 451,
//CCX_L3PllFllCtl3V1CsDfxEn                               = 452,
//CCX_L3PllFllCtl3V1CsDfxSel                              = 453,
//CCX_L3PllFllCtl3V1CsEn                                  = 454,
//CCX_L3PllFllCtl3V1CsIbiasSel                            = 455,
//CCX_L3PllFllCtl3V1CsIoutMode                            = 456,
//CCX_L3PllFllCtl3V1CsIoutSel                             = 457,
//CCX_L3PllFllCtl3V1CsIpmosSel                            = 458,
//CCX_L3PllGiCoarseExp                                    = 459,
//CCX_L3PllGiCoarseMant                                   = 460,
//CCX_L3PllGpCoarseExp                                    = 461,
//CCX_L3PllGpCoarseMant                                   = 462,
//CCX_L3PllLockTimer                                      = 463,
//CCX_L3PllRsvd                                           = 464,
//CCX_L3PllTdcResolution                                  = 465,
//CCX_L3ResetDidMargin                                    = 466,
//CCX_L3SuperVminmaxProg                                  = 467,
//CCX_LSRAM0_FusBstStrenth                                = 468,
//CCX_LSRAM0_FusKprEn                                     = 469,
//CCX_LSRAM0_FusSblKprEn                                  = 470,
//CCX_LSRAM0_FusTimAdjBoost                               = 471,
//CCX_LSRAM0_FusTimAdjPDly                                = 472,
//CCX_LS_Reserved                                         = 473,
//CCX_LowBWConfig                                         = 474,
//CCX_LowBWConfigUp                                       = 475,
//CCX_LowBWSkewEn                                         = 476,
//CCX_LruCfg                                              = 477,
//CCX_MaFddBaseHi                                         = 478,
//CCX_MaFddBaseLo                                         = 479,
//CCX_MeshGatingDis                                       = 480,
//CCX_NoExtraCoarseStep                                   = 481,
//CCX_PBRAM0_FusBstStrenth                                = 482,
//CCX_PBRAM0_FusKprEn                                     = 483,
//CCX_PBRAM0_FusSblKprEn                                  = 484,
//CCX_PBRAM0_FusTimAdjBoost                               = 485,
//CCX_PBRAM0_FusTimAdjPDly                                = 486,
//CCX_PBRAM1_FusBstStrenth                                = 487,
//CCX_PBRAM1_FusKprEn                                     = 488,
//CCX_PBRAM1_FusSblKprEn                                  = 489,
//CCX_PBRAM1_FusTimAdjBoost                               = 490,
//CCX_PBRAM1_FusTimAdjPDly                                = 491,
//CCX_PBRAM2_FusBstStrenth                                = 492,
//CCX_PBRAM2_FusKprEn                                     = 493,
//CCX_PBRAM2_FusTimAdjBoost                               = 494,
//CCX_PBRAM2_FusTimAdjPDly                                = 495,
//CCX_PGMPGPROPDLY                                        = 496,
//CCX_PGMPGRUNDLY                                         = 497,
//CCX_PLLRelockForceCoreStrDis                            = 498,
//CCX_PWROKTOPWRONTIME                                    = 499,
//CCX_PWRONTOPWROKTIME                                    = 500,
//CCX_PWRRDYTOPWROKTIME                                   = 501,
//CCX_PdSyncSel                                           = 502,
//CCX_SCANCLKDIV_1                                        = 503,
//CCX_SC_Reserved                                         = 504,
//CCX_SOFTREPAIREN_1                                      = 505,
//CCX_STARTUPDFSID                                        = 506,
//CCX_STARTUPIVREN                                        = 507,
//CCX_STARTUPPSMID                                        = 508,
//CCX_STARTUPPSMID_EXT                                    = 509,
//CCX_STARTUPSTRETCHALLDIV2                               = 510,
//CCX_STARTUPSTRETCHCLKDIV2                               = 511,
//CCX_STARTUPSTRETCHEN                                    = 512,
//CCX_STARTUPSUPERVMAXEN                                  = 513,
//CCX_STARTUPSUPERVMINEN                                  = 514,
//CCX_STARTUPWLBOOST                                      = 515,
//CCX_SampleSize                                          = 516,
//CCX_ScanClkDiv_0                                        = 517,
//CCX_ScndScanToggleDis                                   = 518,
//CCX_SlowClkRamp                                         = 519,
//CCX_SoftRepairEn_0                                      = 520,
//CCX_StartupDid                                          = 521,
//CCX_StartupFid                                          = 522,
//CCX_StretchEn                                           = 523,
//CCX_StretchThresh                                       = 524,
//CCX_TagCfg                                              = 525,
//CCX_UnstretchThresh                                     = 526,
//CCX_VCOPeriodDelay                                      = 527,
//CCX_WAKEPGASSIGNMENT                                    = 528,
//CCX_WARMRESETMBISIEN                                    = 529,
//CCX_WARMRESETMBISTEN                                    = 530,
//CCX_ZEN_RESERVED_0                                      = 531,
//CCX_ZEN_RESERVED_3                                      = 532,
//CCX_ZEN_RESERVED_4                                      = 533,
//CCX_ZEN_RESERVED_5                                      = 534,
//CCX_staticEnable                                        = 535,
//CLK_BootRomCLK0_Did_clk0                                = 536,
//CLK_BootRomCLK0_Did_clk1                                = 537,
//CLK_BootRomCLK0_Did_clk2                                = 538,
//CLK_BootRomCLK0_Did_clk3                                = 539,
//CLK_BootRomCLK0_Did_clk4                                = 540,
//CLK_BootRomCLK0_Did_clk5                                = 541,
//CLK_BootRomCLK0_Did_clk6                                = 542,
//CLK_BootRomCLK10_Did_clk1                               = 543,
//CLK_BootRomCLK11_Did_clk1                               = 544,
//CLK_BootRomCLK1_Did_clk0                                = 545,
//CLK_BootRomCLK1_Did_clk1                                = 546,
//CLK_BootRomCLK2_Did_clk0                                = 547,
//CLK_BootRomCLK2_Did_clk1                                = 548,
//CLK_BootRomCLK3_Did_clk0                                = 549,
//CLK_BootRomCLK3_Did_clk1                                = 550,
//CLK_BootRomCLK4_Did_clk1                                = 551,
//CLK_BootRomCLK5_Did_clk1                                = 552,
//CLK_BootRomCLK6_Did_clk1                                = 553,
//CLK_BootRomCLK7_Did_clk1                                = 554,
//CLK_BootRomCLK8_Did_clk1                                = 555,
//CLK_BootRomCLK9_Did_clk1                                = 556,
//CLK_Bypass_ADFS_DS_clk0                                 = 557,
//CLK_Bypass_ADFS_DS_clk1                                 = 558,
//CLK_Bypass_ADFS_DS_clk2                                 = 559,
//CLK_Bypass_ADFS_DS_clk3                                 = 560,
//CLK_Bypass_ADFS_DS_clk4                                 = 561,
//CLK_Bypass_ADFS_DS_clk5                                 = 562,
//CLK_Bypass_ADFS_DS_clk6                                 = 563,
//CLK_ClkSpare_0                                          = 564,
//CLK_ClkSpare_1                                          = 565,
//CLK_ClkSpare_10                                         = 566,
//CLK_ClkSpare_11                                         = 567,
//CLK_ClkSpare_12                                         = 568,
//CLK_ClkSpare_13                                         = 569,
//CLK_ClkSpare_14                                         = 570,
//CLK_ClkSpare_15                                         = 571,
//CLK_ClkSpare_16                                         = 572,
//CLK_ClkSpare_17                                         = 573,
//CLK_ClkSpare_18                                         = 574,
//CLK_ClkSpare_2                                          = 575,
//CLK_ClkSpare_3                                          = 576,
//CLK_ClkSpare_4                                          = 577,
//CLK_ClkSpare_5                                          = 578,
//CLK_ClkSpare_6                                          = 579,
//CLK_ClkSpare_7                                          = 580,
//CLK_ClkSpare_8                                          = 581,
//CLK_ClkSpare_9                                          = 582,
//CLK_FUSES_ARE_VALID_clk0                                = 583,
//CLK_FUSES_ARE_VALID_clk1                                = 584,
//CLK_FUSES_ARE_VALID_clk2                                = 585,
//CLK_FUSES_ARE_VALID_clk3                                = 586,
//CLK_FUSES_ARE_VALID_clk4                                = 587,
//CLK_FUSES_ARE_VALID_clk5                                = 588,
//CLK_FUSES_ARE_VALID_clk6                                = 589,
//CLK_MainPllDidStartup_clk0                              = 590,
//CLK_MainPllDidStartup_clk1                              = 591,
//CLK_MainPllDidStartup_clk2                              = 592,
//CLK_MainPllDidStartup_clk3                              = 593,
//CLK_MainPllDidStartup_clk4                              = 594,
//CLK_MainPllDidStartup_clk5                              = 595,
//CLK_MainPllDidStartup_clk6                              = 596,
//CLK_MainPllMiscFuseCtrl_clk0                            = 597,
//CLK_MainPllMiscFuseCtrl_clk1                            = 598,
//CLK_MainPllMiscFuseCtrl_clk2                            = 599,
//CLK_MainPllMiscFuseCtrl_clk3                            = 600,
//CLK_MainPllMiscFuseCtrl_clk4                            = 601,
//CLK_MainPllMiscFuseCtrl_clk5                            = 602,
//CLK_MainPllMiscFuseCtrl_clk6                            = 603,
//CLK_MainPllOpFreqIdStartup_clk0                         = 604,
//CLK_MainPllOpFreqIdStartup_clk1                         = 605,
//CLK_MainPllOpFreqIdStartup_clk2                         = 606,
//CLK_MainPllOpFreqIdStartup_clk3                         = 607,
//CLK_MainPllOpFreqIdStartup_clk4                         = 608,
//CLK_MainPllOpFreqIdStartup_clk5                         = 609,
//CLK_MainPllOpFreqIdStartup_clk6                         = 610,
//CLK_MainPllRladTapSel_clk0                              = 611,
//CLK_MainPllRladTapSel_clk1                              = 612,
//CLK_MainPllRladTapSel_clk2                              = 613,
//CLK_MainPllRladTapSel_clk3                              = 614,
//CLK_MainPllRladTapSel_clk4                              = 615,
//CLK_MainPllRladTapSel_clk5                              = 616,
//CLK_MainPllRladTapSel_clk6                              = 617,
//CLK_SPLL_GI_COARSE_EXP_bin1                             = 618,
//CLK_SPLL_GI_COARSE_EXP_bin2                             = 619,
//CLK_SPLL_GI_COARSE_EXP_bin3                             = 620,
//CLK_SPLL_GI_COARSE_EXP_bin4                             = 621,
//CLK_SPLL_GI_COARSE_MANT_bin1                            = 622,
//CLK_SPLL_GI_COARSE_MANT_bin2                            = 623,
//CLK_SPLL_GI_COARSE_MANT_bin3                            = 624,
//CLK_SPLL_GI_COARSE_MANT_bin4                            = 625,
//CLK_SPLL_GP_COARSE_EXP_bin1                             = 626,
//CLK_SPLL_GP_COARSE_EXP_bin2                             = 627,
//CLK_SPLL_GP_COARSE_EXP_bin3                             = 628,
//CLK_SPLL_GP_COARSE_EXP_bin4                             = 629,
//CLK_SPLL_GP_COARSE_MANT_bin1                            = 630,
//CLK_SPLL_GP_COARSE_MANT_bin2                            = 631,
//CLK_SPLL_GP_COARSE_MANT_bin3                            = 632,
//CLK_SPLL_GP_COARSE_MANT_bin4                            = 633,
//CLK_SPLL_TDC_RESOLUTION_bin1                            = 634,
//CLK_SPLL_TDC_RESOLUTION_bin2                            = 635,
//CLK_SPLL_TDC_RESOLUTION_bin3                            = 636,
//CLK_SPLL_TDC_RESOLUTION_bin4                            = 637,
//CLK_StartupCLK0_Did_clk0                                = 638,
//CLK_StartupCLK0_Did_clk1                                = 639,
//CLK_StartupCLK0_Did_clk2                                = 640,
//CLK_StartupCLK0_Did_clk3                                = 641,
//CLK_StartupCLK0_Did_clk4                                = 642,
//CLK_StartupCLK0_Did_clk5                                = 643,
//CLK_StartupCLK0_Did_clk6                                = 644,
//CLK_StartupCLK10_Did_clk1                               = 645,
//CLK_StartupCLK11_Did_clk1                               = 646,
//CLK_StartupCLK1_Did_clk0                                = 647,
//CLK_StartupCLK1_Did_clk1                                = 648,
//CLK_StartupCLK2_Did_clk0                                = 649,
//CLK_StartupCLK2_Did_clk1                                = 650,
//CLK_StartupCLK3_Did_clk0                                = 651,
//CLK_StartupCLK3_Did_clk1                                = 652,
//CLK_StartupCLK4_Did_clk1                                = 653,
//CLK_StartupCLK5_Did_clk1                                = 654,
//CLK_StartupCLK6_Did_clk1                                = 655,
//CLK_StartupCLK7_Did_clk1                                = 656,
//CLK_StartupCLK8_Did_clk1                                = 657,
//CLK_StartupCLK9_Did_clk1                                = 658,
//DFX_DFX_PUB_SPARE_FUSES                                 = 659,
//DFX_DFX_WRITE_DISABLE                                   = 660,
//DFX_FUSE_CCD_Down                                       = 661,
//DFX_FUSE_CCD_Present                                    = 662,
//DFX_FUSE_IDCodeFused                                    = 663,
//DFX_FUSE_IDCodePartNumber                               = 664,
//DFX_FUSE_IDCodeVersion                                  = 665,
//DF_DF_GROUP0_DATA                                       = 666,
//DF_DF_GROUP1_DATA                                       = 667,
//DF_DF_GROUP2_DATA                                       = 668,
//DF_DF_GROUP3_DATA                                       = 669,
//DF_DF_GROUP4_DATA                                       = 670,
//DF_DF_GROUP5_DATA                                       = 671,
//DF_DF_WRITE_DISABLE                                     = 672,
//DF_Spare                                                = 673,
//DF_SpfDis                                               = 674,
//FCH_FCH_GROUP0_DATA                                     = 675,
//FCH_FCH_WRITE_DISABLE                                   = 676,
//FCH_fch_fuse                                            = 677,
//FUSE_Attestation_SEED_LOCK                              = 678,
//FUSE_CCD_FUSE_CCD_GROUP0_DATA                           = 679,
//FUSE_CCD_PEO_RSV                                        = 680,
//FUSE_CCD_SpareFuse3                                     = 681,
//FUSE_CCD_replace_start                                  = 682,
//FUSE_CUSTOMER_KEY_LOCK                                  = 683,
//FUSE_FUSE_GROUP0_DATA                                   = 684,
//FUSE_PEO_RSV                                            = 685,
//FUSE_REPAIR_Spare_Repair                                = 686,
//FUSE_SpareFuse1                                         = 687,
//FUSE_SpareFuse2                                         = 688,
//FUSE_SpareFuse3                                         = 689,
//FUSE_attestation_seed_replace_start                     = 690,
//FUSE_customer_key_replace_start                         = 691,
//FUSE_replace_start                                      = 692,
//GMI2_PCS_CCD_GMI2_PCS_CCD_PUB_SPARE_FUSES               = 693,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1                 = 694,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_DisableFunction = 695,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_ReadySerialBypass = 696,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_WriteDisable    = 697,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HINIT                  = 698,
//GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HWinitComplete         = 699,
//GMI2_PCS_CCD_twix_ccd_SPARE0                            = 700,
//GMI2_PCS_CCD_twix_ccd_SPARE1                            = 701,
//GMI2_PCS_CCD_twix_ccd_SPARE2                            = 702,
//GMI2_PCS_CCD_twix_ccd_SPARE3                            = 703,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1                = 704,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_DisableFunction = 705,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_ReadySerialBypass = 706,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_WriteDisable   = 707,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HINIT                 = 708,
//GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HWinitComplete        = 709,
//GMI2_PCS_IOD_GMI2_PCS_IOD_PUB_SPARE_FUSES               = 710,
//GMI2_PCS_IOD_twix_iod_SPARE0                            = 711,
//GMI2_PCS_IOD_twix_iod_SPARE1                            = 712,
//GMI2_PCS_IOD_twix_iod_SPARE2                            = 713,
//GMI_PCS_GMI_PCS_PUB_SPARE_FUSES                         = 714,
//GMI_PCS_SPARE_EFUSE_1                                   = 715,
//GMI_PCS_SPARE_EFUSE_10                                  = 716,
//GMI_PCS_SPARE_EFUSE_11                                  = 717,
//GMI_PCS_SPARE_EFUSE_12                                  = 718,
//GMI_PCS_SPARE_EFUSE_13                                  = 719,
//GMI_PCS_SPARE_EFUSE_14                                  = 720,
//GMI_PCS_SPARE_EFUSE_15                                  = 721,
//GMI_PCS_SPARE_EFUSE_16                                  = 722,
//GMI_PCS_SPARE_EFUSE_17                                  = 723,
//GMI_PCS_SPARE_EFUSE_18                                  = 724,
//GMI_PCS_SPARE_EFUSE_19                                  = 725,
//GMI_PCS_SPARE_EFUSE_2                                   = 726,
//GMI_PCS_SPARE_EFUSE_20                                  = 727,
//GMI_PCS_SPARE_EFUSE_21                                  = 728,
//GMI_PCS_SPARE_EFUSE_22                                  = 729,
//GMI_PCS_SPARE_EFUSE_23                                  = 730,
//GMI_PCS_SPARE_EFUSE_24                                  = 731,
//GMI_PCS_SPARE_EFUSE_25                                  = 732,
//GMI_PCS_SPARE_EFUSE_26                                  = 733,
//GMI_PCS_SPARE_EFUSE_27                                  = 734,
//GMI_PCS_SPARE_EFUSE_28                                  = 735,
//GMI_PCS_SPARE_EFUSE_29                                  = 736,
//GMI_PCS_SPARE_EFUSE_3                                   = 737,
//GMI_PCS_SPARE_EFUSE_30                                  = 738,
//GMI_PCS_SPARE_EFUSE_31                                  = 739,
//GMI_PCS_SPARE_EFUSE_32                                  = 740,
//GMI_PCS_SPARE_EFUSE_33                                  = 741,
//GMI_PCS_SPARE_EFUSE_34                                  = 742,
//GMI_PCS_SPARE_EFUSE_35                                  = 743,
//GMI_PCS_SPARE_EFUSE_36                                  = 744,
//GMI_PCS_SPARE_EFUSE_37                                  = 745,
//GMI_PCS_SPARE_EFUSE_38                                  = 746,
//GMI_PCS_SPARE_EFUSE_39                                  = 747,
//GMI_PCS_SPARE_EFUSE_4                                   = 748,
//GMI_PCS_SPARE_EFUSE_40                                  = 749,
//GMI_PCS_SPARE_EFUSE_41                                  = 750,
//GMI_PCS_SPARE_EFUSE_42                                  = 751,
//GMI_PCS_SPARE_EFUSE_43                                  = 752,
//GMI_PCS_SPARE_EFUSE_44                                  = 753,
//GMI_PCS_SPARE_EFUSE_45                                  = 754,
//GMI_PCS_SPARE_EFUSE_46                                  = 755,
//GMI_PCS_SPARE_EFUSE_47                                  = 756,
//GMI_PCS_SPARE_EFUSE_48                                  = 757,
//GMI_PCS_SPARE_EFUSE_49                                  = 758,
//GMI_PCS_SPARE_EFUSE_5                                   = 759,
//GMI_PCS_SPARE_EFUSE_50                                  = 760,
//GMI_PCS_SPARE_EFUSE_51                                  = 761,
//GMI_PCS_SPARE_EFUSE_52                                  = 762,
//GMI_PCS_SPARE_EFUSE_53                                  = 763,
//GMI_PCS_SPARE_EFUSE_54                                  = 764,
//GMI_PCS_SPARE_EFUSE_55                                  = 765,
//GMI_PCS_SPARE_EFUSE_56                                  = 766,
//GMI_PCS_SPARE_EFUSE_6                                   = 767,
//GMI_PCS_SPARE_EFUSE_7                                   = 768,
//GMI_PCS_SPARE_EFUSE_8                                   = 769,
//GMI_PCS_SPARE_EFUSE_9                                   = 770,
//IOHC0_ECC_Disable                                       = 771,
//IOHC0_IOHC_PCIE_Bridge_Disable                          = 772,
//IOHC0_IOHC_PUB_SPARE_FUSES                              = 773,
//IOHC0_IOHC_WRITE_DISABLE                                = 774,
//IOHC1_ECC_Disable                                       = 775,
//IOHC1_IOHC_PCIE_Bridge_Disable                          = 776,
//IOHC1_IOHC_PUB_SPARE_FUSES                              = 777,
//IOHC1_IOHC_WRITE_DISABLE                                = 778,
//IOHC2_ECC_Disable                                       = 779,
//IOHC2_IOHC_PCIE_Bridge_Disable                          = 780,
//IOHC2_IOHC_PUB_SPARE_FUSES                              = 781,
//IOHC2_IOHC_WRITE_DISABLE                                = 782,
//IOHC3_ECC_Disable                                       = 783,
//IOHC3_IOHC_PCIE_Bridge_Disable                          = 784,
//IOHC3_IOHC_PUB_SPARE_FUSES                              = 785,
//IOHC3_IOHC_WRITE_DISABLE                                = 786,
//MP0_ATTESTATION_SEED                                    = 787,
//MP0_ATTESTATION_SEED_CHECKSUM                           = 788,
//MP0_ATTESTATION_SEED_CHECKSUM_1                         = 789,
//MP0_ATTESTATION_SEED_CHECKSUM_2                         = 790,
//MP0_ATTESTATION_SEED_CHECKSUM_VALID                     = 791,
//MP0_ATTESTATION_SEED_CHECKSUM_VALID_1                   = 792,
//MP0_ATTESTATION_SEED_CHECKSUM_VALID_2                   = 793,
//MP0_ATTESTATION_SEED_ECC_EN                             = 794,
//MP0_ATTESTATION_SEED_ECC_EN_1                           = 795,
//MP0_ATTESTATION_SEED_ECC_EN_2                           = 796,
//MP0_AUDIO_AZ_HARVEST                                    = 797,
//MP0_BIOS_KEY_ID                                         = 798,
//MP0_BIOS_KEY_ID_1                                       = 799,
//MP0_BIOS_KEY_ID_2                                       = 800,
//MP0_CLDO_GMI2_BYPASS_DIS                                = 801,
//MP0_CLDO_GMI2_SEL_SRC_VDDIO_MEM                         = 802,
//MP0_CORE_DISABLE                                        = 803,
//MP0_CPU_PWROK_REFCLK_GAP_CYCLES                         = 804,
//MP0_CUSTOMER_SPARE                                      = 805,
//MP0_DDRPHY01_HARVEST                                    = 806,
//MP0_DDRPHY23_HARVEST                                    = 807,
//MP0_DDRPHY45_HARVEST                                    = 808,
//MP0_DDRPHY67_HARVEST                                    = 809,
//MP0_DF_CAKE0_HARVEST                                    = 810,
//MP0_DF_CAKE1_HARVEST                                    = 811,
//MP0_DF_CAKE2_HARVEST                                    = 812,
//MP0_DF_CAKE3_HARVEST                                    = 813,
//MP0_DF_CAKE4_HARVEST                                    = 814,
//MP0_DF_CAKE5_HARVEST                                    = 815,
//MP0_DF_CCM0_HARVEST                                     = 816,
//MP0_DF_CCM1_HARVEST                                     = 817,
//MP0_DF_CCM2_HARVEST                                     = 818,
//MP0_DF_CCM3_HARVEST                                     = 819,
//MP0_DF_CCM4_HARVEST                                     = 820,
//MP0_DF_CCM5_HARVEST                                     = 821,
//MP0_DF_CCM6_HARVEST                                     = 822,
//MP0_DF_CCM7_HARVEST                                     = 823,
//MP0_DF_CS0_CCIX_HARVEST                                 = 824,
//MP0_DF_CS0_UMC_HARVEST                                  = 825,
//MP0_DF_CS1_CCIX_HARVEST                                 = 826,
//MP0_DF_CS1_UMC_HARVEST                                  = 827,
//MP0_DF_CS2_CCIX_HARVEST                                 = 828,
//MP0_DF_CS2_UMC_HARVEST                                  = 829,
//MP0_DF_CS3_CCIX_HARVEST                                 = 830,
//MP0_DF_CS3_UMC_HARVEST                                  = 831,
//MP0_DF_CS4_UMC_HARVEST                                  = 832,
//MP0_DF_CS5_UMC_HARVEST                                  = 833,
//MP0_DF_CS6_UMC_HARVEST                                  = 834,
//MP0_DF_CS7_UMC_HARVEST                                  = 835,
//MP0_DF_IOM0_HARVEST                                     = 836,
//MP0_DF_IOM1_HARVEST                                     = 837,
//MP0_DF_IOM2_HARVEST                                     = 838,
//MP0_DF_IOM3_HARVEST                                     = 839,
//MP0_DF_SPF0_CCIX_HARVEST                                = 840,
//MP0_DF_SPF0_UMC_HARVEST                                 = 841,
//MP0_DF_SPF1_CCIX_HARVEST                                = 842,
//MP0_DF_SPF1_UMC_HARVEST                                 = 843,
//MP0_DF_SPF2_CCIX_HARVEST                                = 844,
//MP0_DF_SPF2_UMC_HARVEST                                 = 845,
//MP0_DF_SPF3_CCIX_HARVEST                                = 846,
//MP0_DF_SPF3_UMC_HARVEST                                 = 847,
//MP0_DF_SPF4_UMC_HARVEST                                 = 848,
//MP0_DF_SPF5_UMC_HARVEST                                 = 849,
//MP0_DF_SPF6_UMC_HARVEST                                 = 850,
//MP0_DF_SPF7_UMC_HARVEST                                 = 851,
//MP0_DISABLE_MP0_BIHR                                    = 852,
//MP0_DISABLE_MP0_MBIST                                   = 853,
//MP0_DISTRIBUTE_LDO_FUSES                                = 854,
//MP0_DISTRIBUTE_WAFL_FUSES                               = 855,
//MP0_ENABLE_32MB_SPI_ACCESS                              = 856,
//MP0_ENABLE_DBGU_NBIO_POST_CODES                         = 857,
//MP0_ENABLE_ODPR_TMP_COMP                                = 858,
//MP0_ENABLE_RSMU_WDT                                     = 859,
//MP0_ENABLE_SBI_POST_CODES                               = 860,
//MP0_FW_ROLLBACK_CNT                                     = 861,
//MP0_FW_ROLLBACK_CNT_1                                   = 862,
//MP0_FW_ROLLBACK_CNT_2                                   = 863,
//MP0_GMI2_PCS0_HARVEST                                   = 864,
//MP0_GMI2_PCS1_HARVEST                                   = 865,
//MP0_GMI2_PCS2_HARVEST                                   = 866,
//MP0_GMI2_PCS3_HARVEST                                   = 867,
//MP0_GMI2_PCS4_HARVEST                                   = 868,
//MP0_GMI2_PCS5_HARVEST                                   = 869,
//MP0_GMI2_PCS6_HARVEST                                   = 870,
//MP0_GMI2_PCS7_HARVEST                                   = 871,
//MP0_GMI2_PHY0_HARVEST                                   = 872,
//MP0_GMI2_PHY1_HARVEST                                   = 873,
//MP0_GMI2_PHY2_HARVEST                                   = 874,
//MP0_GMI2_PHY3_HARVEST                                   = 875,
//MP0_GMI2_PHY4_HARVEST                                   = 876,
//MP0_GMI2_PHY5_HARVEST                                   = 877,
//MP0_GMI2_PHY6_HARVEST                                   = 878,
//MP0_GMI2_PHY7_HARVEST                                   = 879,
//MP0_HARVESTING_FUSES                                    = 880,
//MP0_HARVESTING_FUSES_1                                  = 881,
//MP0_LOAD_DIAG_BOOT_LOADER                               = 882,
//MP0_MP0_GROUP0_DATA                                     = 883,
//MP0_MP0_WRITE_DISABLE                                   = 884,
//MP0_NBIO_IOHC0_HARVEST                                  = 885,
//MP0_NBIO_IOHC1_HARVEST                                  = 886,
//MP0_NBIO_IOHC2_HARVEST                                  = 887,
//MP0_NBIO_IOHC3_HARVEST                                  = 888,
//MP0_NBIO_IOMMU0_HARVEST                                 = 889,
//MP0_NBIO_IOMMU1_HARVEST                                 = 890,
//MP0_NBIO_IOMMU2_HARVEST                                 = 891,
//MP0_NBIO_IOMMU3_HARVEST                                 = 892,
//MP0_NBIO_L1NBIF0_0_HARVEST                              = 893,
//MP0_NBIO_L1NBIF0_1_HARVEST                              = 894,
//MP0_NBIO_L1NBIF0_2_HARVEST                              = 895,
//MP0_NBIO_L1NBIF0_3_HARVEST                              = 896,
//MP0_NBIO_NB2_0_HARVEST                                  = 897,
//MP0_NBIO_NB2_1_HARVEST                                  = 898,
//MP0_NBIO_NB2_2_HARVEST                                  = 899,
//MP0_NBIO_NB2_3_HARVEST                                  = 900,
//MP0_NBIO_NBIF0_0_HARVEST                                = 901,
//MP0_NBIO_NBIF0_1_HARVEST                                = 902,
//MP0_NBIO_NBIF0_2_HARVEST                                = 903,
//MP0_NBIO_NBIF0_3_HARVEST                                = 904,
//MP0_NBIO_NBIF1_0_HARVEST                                = 905,
//MP0_NBIO_NBIF1_1_HARVEST                                = 906,
//MP0_NBIO_NBIF1_2_HARVEST                                = 907,
//MP0_NBIO_NBIF1_3_HARVEST                                = 908,
//MP0_NBIO_NB_0_HARVEST                                   = 909,
//MP0_NBIO_NB_1_HARVEST                                   = 910,
//MP0_NBIO_NB_2_HARVEST                                   = 911,
//MP0_NBIO_NB_3_HARVEST                                   = 912,
//MP0_NBIO_NTB_0_HARVEST                                  = 913,
//MP0_NBIO_NTB_1_HARVEST                                  = 914,
//MP0_NBIO_NTB_2_HARVEST                                  = 915,
//MP0_NBIO_NTB_3_HARVEST                                  = 916,
//MP0_NBIO_PCIE0_0_HARVEST                                = 917,
//MP0_NBIO_PCIE0_1_HARVEST                                = 918,
//MP0_NBIO_PCIE0_2_HARVEST                                = 919,
//MP0_NBIO_PCIE0_3_HARVEST                                = 920,
//MP0_NBIO_PCIE1_0_HARVEST                                = 921,
//MP0_NBIO_PCIE1_1_HARVEST                                = 922,
//MP0_NBIO_PCIE1_2_HARVEST                                = 923,
//MP0_NBIO_PCIE1_3_HARVEST                                = 924,
//MP0_NBIO_PCIEX2_HARVEST                                 = 925,
//MP0_NBIO_PCIEX2_PCS_HARVEST                             = 926,
//MP0_NBIO_PCIE_PCS_G0_HARVEST                            = 927,
//MP0_NBIO_PCIE_PCS_G1_HARVEST                            = 928,
//MP0_NBIO_PCIE_PCS_G2_HARVEST                            = 929,
//MP0_NBIO_PCIE_PCS_G3_HARVEST                            = 930,
//MP0_NBIO_PCIE_PCS_P0_HARVEST                            = 931,
//MP0_NBIO_PCIE_PCS_P1_HARVEST                            = 932,
//MP0_NBIO_PCIE_PCS_P2_HARVEST                            = 933,
//MP0_NBIO_PCIE_PCS_P3_HARVEST                            = 934,
//MP0_NBIO_PTDMA0_HARVEST                                 = 935,
//MP0_NBIO_PTDMA1_HARVEST                                 = 936,
//MP0_NBIO_PTDMA2_HARVEST                                 = 937,
//MP0_NBIO_PTDMA3_HARVEST                                 = 938,
//MP0_NONSECURE_FUSES                                     = 939,
//MP0_PGVI_POWER_UP                                       = 940,
//MP0_PGVI_POWER_UP_MM                                    = 941,
//MP0_PSPBL_LOAD_DIAG_OS                                  = 942,
//MP0_RELEASE_CPU_RESET                                   = 943,
//MP0_ROOT_KEY                                            = 944,
//MP0_ROOT_KEY_CHECKSUM                                   = 945,
//MP0_ROOT_KEY_CHECKSUM_1                                 = 946,
//MP0_ROOT_KEY_CHECKSUM_2                                 = 947,
//MP0_ROOT_KEY_CHECKSUM_VALID                             = 948,
//MP0_ROOT_KEY_CHECKSUM_VALID_1                           = 949,
//MP0_ROOT_KEY_CHECKSUM_VALID_2                           = 950,
//MP0_ROOT_KEY_ECC_EN                                     = 951,
//MP0_ROOT_KEY_ECC_EN_1                                   = 952,
//MP0_ROOT_KEY_ECC_EN_2                                   = 953,
//MP0_ROOT_KEY_SELECT                                     = 954,
//MP0_ROOT_KEY_SELECT_1                                   = 955,
//MP0_ROOT_KEY_SELECT_2                                   = 956,
//MP0_RSMU_FUSE_VALID                                     = 957,
//MP0_RUN_BIHR                                            = 958,
//MP0_RUN_MBIST                                           = 959,
//MP0_SATA0_HARVEST                                       = 960,
//MP0_SATA1_HARVEST                                       = 961,
//MP0_SATA2_HARVEST                                       = 962,
//MP0_SATA3_HARVEST                                       = 963,
//MP0_SEC_FEATURE_SEL                                     = 964,
//MP0_SEC_FEATURE_SEL_1                                   = 965,
//MP0_SEC_FEATURE_SEL_2                                   = 966,
//MP0_SERDES_G0_HARVEST                                   = 967,
//MP0_SERDES_G1_HARVEST                                   = 968,
//MP0_SERDES_G2_HARVEST                                   = 969,
//MP0_SERDES_G3_HARVEST                                   = 970,
//MP0_SERDES_P0_HARVEST                                   = 971,
//MP0_SERDES_P1_HARVEST                                   = 972,
//MP0_SERDES_P2_HARVEST                                   = 973,
//MP0_SERDES_P3_HARVEST                                   = 974,
//MP0_SET_BOOTROM_STARTUP_CLOCKS                          = 975,
//MP0_SKIP_EXIT_BYPASS                                    = 976,
//MP0_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE          = 977,
//MP0_SMT_ENABLE                                          = 978,
//MP0_SMU_CLKC0_HARVEST                                   = 979,
//MP0_SMU_CLKC1_HARVEST                                   = 980,
//MP0_SMU_CLKC2_HARVEST                                   = 981,
//MP0_SMU_CLKC3_HARVEST                                   = 982,
//MP0_SMU_CLKC_HARVEST                                    = 983,
//MP0_SMU_TWIX0_HARVEST                                   = 984,
//MP0_SMU_TWIX1_HARVEST                                   = 985,
//MP0_SMU_TWIX2_HARVEST                                   = 986,
//MP0_SMU_TWIX3_HARVEST                                   = 987,
//MP0_SMU_TWIX4_HARVEST                                   = 988,
//MP0_SMU_TWIX5_HARVEST                                   = 989,
//MP0_SMU_TWIX6_HARVEST                                   = 990,
//MP0_SMU_TWIX7_HARVEST                                   = 991,
//MP0_SMU_WAFL_HARVEST                                    = 992,
//MP0_SRAM_HD_BC1                                         = 993,
//MP0_SRAM_HD_BC2                                         = 994,
//MP0_SRAM_PDP_BC1                                        = 995,
//MP0_SRAM_PDP_BC2                                        = 996,
//MP0_SRAM_RF_BC1                                         = 997,
//MP0_SRAM_RF_BC2                                         = 998,
//MP0_SRAM_RM                                             = 999,
//MP0_SRAM_SPARE_0                                        = 1000,
//MP0_TWIX_PCS0_HARVEST                                   = 1001,
//MP0_TWIX_PCS1_HARVEST                                   = 1002,
//MP0_TWIX_PCS2_HARVEST                                   = 1003,
//MP0_TWIX_PCS3_HARVEST                                   = 1004,
//MP0_TWIX_PCS4_HARVEST                                   = 1005,
//MP0_TWIX_PCS5_HARVEST                                   = 1006,
//MP0_TWIX_PCS6_HARVEST                                   = 1007,
//MP0_TWIX_PCS7_HARVEST                                   = 1008,
//MP0_UMC_UMC0_HARVEST                                    = 1009,
//MP0_UMC_UMC1_HARVEST                                    = 1010,
//MP0_UMC_UMC2_HARVEST                                    = 1011,
//MP0_UMC_UMC3_HARVEST                                    = 1012,
//MP0_UMC_UMC4_HARVEST                                    = 1013,
//MP0_UMC_UMC5_HARVEST                                    = 1014,
//MP0_UMC_UMC6_HARVEST                                    = 1015,
//MP0_UMC_UMC7_HARVEST                                    = 1016,
//MP0_WAFL_CPHY_HARVEST                                   = 1017,
//MP0_WAFL_DBG_INTERLOCK_1                                = 1018,
//MP0_WAFL_DBG_INTERLOCK_2                                = 1019,
//MP0_WAFL_DESKEW_TIME                                    = 1020,
//MP0_WAFL_DETECT_REPEAT                                  = 1021,
//MP0_WAFL_DETECT_TIME                                    = 1022,
//MP0_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE            = 1023,
//MP0_WAFL_PATCH                                          = 1024,
//MP0_WAFL_PCS_HARVEST                                    = 1025,
//MP0_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE               = 1026,
//MP0_WAFL_SKIP_FIRST_CAL                                 = 1027,
//MP0_WAFL_SLAVE_INFINITE_TIMEOUT                         = 1028,
//MP0_WaflInvertLinkAddr0                                 = 1029,
//MP0_WaflInvertLinkAddr1                                 = 1030,
//MP0_WaflInvertSmnAddr0                                  = 1031,
//MP0_WaflInvertSmnAddr1                                  = 1032,
//MP0_WaflLinkEnable0                                     = 1033,
//MP0_WaflLinkEnable1                                     = 1034,
//MP0_XGMI_PCS_G0_HARVEST                                 = 1035,
//MP0_XGMI_PCS_G1_HARVEST                                 = 1036,
//MP0_XGMI_PCS_G2_HARVEST                                 = 1037,
//MP0_XGMI_PCS_G3_HARVEST                                 = 1038,
//MP0_XGMI_PCS_P2_HARVEST                                 = 1039,
//MP0_XGMI_PCS_P3_HARVEST                                 = 1040,
//MP1_BC_Determinism_Scalar_CURRENT                       = 1041,
//MP1_BC_Determinism_Scalar_POWER                         = 1042,
//MP1_BC_Determinism_Scalar_VOLTAGE                       = 1043,
//MP1_CCLK_FtoV_A_WC_CURRENT                              = 1044,
//MP1_CCLK_FtoV_A_WC_POWER                                = 1045,
//MP1_CCLK_FtoV_A_WC_VOLTAGE                              = 1046,
//MP1_CCLK_FtoV_B_WC_CURRENT                              = 1047,
//MP1_CCLK_FtoV_B_WC_POWER                                = 1048,
//MP1_CCLK_FtoV_B_WC_VOLTAGE                              = 1049,
//MP1_CCLK_FtoV_C_WC_CURRENT                              = 1050,
//MP1_CCLK_FtoV_C_WC_POWER                                = 1051,
//MP1_CCLK_FtoV_C_WC_VOLTAGE                              = 1052,
//MP1_Core_Cac_b_WC_CURRENT                               = 1053,
//MP1_Core_Cac_b_WC_POWER                                 = 1054,
//MP1_Core_Cac_m_WC_CURRENT                               = 1055,
//MP1_Core_Cac_m_WC_POWER                                 = 1056,
//MP1_Core_Sidd_Tb_WC_CURRENT                             = 1057,
//MP1_Core_Sidd_Tb_WC_POWER                               = 1058,
//MP1_Core_Sidd_Tm_WC_CURRENT                             = 1059,
//MP1_Core_Sidd_Tm_WC_POWER                               = 1060,
//MP1_Core_Sidd_b_WC_CURRENT                              = 1061,
//MP1_Core_Sidd_b_WC_POWER                                = 1062,
//MP1_Core_Sidd_m_WC_CURRENT                              = 1063,
//MP1_Core_Sidd_m_WC_POWER                                = 1064,
//MP1_CpuDid0                                             = 1065,
//MP1_CpuDid1                                             = 1066,
//MP1_CpuDid2                                             = 1067,
//MP1_CpuDid3                                             = 1068,
//MP1_CpuDid4                                             = 1069,
//MP1_CpuDid5                                             = 1070,
//MP1_CpuDid6                                             = 1071,
//MP1_CpuDid7                                             = 1072,
//MP1_CpuFid0                                             = 1073,
//MP1_CpuFid1                                             = 1074,
//MP1_CpuFid2                                             = 1075,
//MP1_CpuFid3                                             = 1076,
//MP1_CpuFid4                                             = 1077,
//MP1_CpuFid5                                             = 1078,
//MP1_CpuFid6                                             = 1079,
//MP1_CpuFid7                                             = 1080,
//MP1_CpuVid0                                             = 1081,
//MP1_CpuVid1                                             = 1082,
//MP1_CpuVid2                                             = 1083,
//MP1_CpuVid3                                             = 1084,
//MP1_CpuVid4                                             = 1085,
//MP1_CpuVid5                                             = 1086,
//MP1_CpuVid6                                             = 1087,
//MP1_CpuVid7                                             = 1088,
//MP1_CstateBoostActiveCoreThreshold                      = 1089,
//MP1_DisableAllFrequencyChanges                          = 1090,
//MP1_EDC                                                 = 1091,
//MP1_FIT_Limit                                           = 1092,
//MP1_Fclk1067ShadowVid                                   = 1093,
//MP1_Fclk1067Vid                                         = 1094,
//MP1_Fclk1200ShadowVid                                   = 1095,
//MP1_Fclk1200Vid                                         = 1096,
//MP1_Fclk1333ShadowVid                                   = 1097,
//MP1_Fclk1333Vid                                         = 1098,
//MP1_Fclk1467ShadowVid                                   = 1099,
//MP1_Fclk1467Vid                                         = 1100,
//MP1_Fclk1600ShadowVid                                   = 1101,
//MP1_Fclk1600Vid                                         = 1102,
//MP1_Fclk800ShadowVid                                    = 1103,
//MP1_Fclk800Vid                                          = 1104,
//MP1_Fclk933ShadowVid                                    = 1105,
//MP1_Fclk933Vid                                          = 1106,
//MP1_Fmax                                                = 1107,
//MP1_Fmin                                                = 1108,
//MP1_ForceDeterminism                                    = 1109,
//MP1_LclkDid0                                            = 1110,
//MP1_LclkDid1                                            = 1111,
//MP1_LclkDid2                                            = 1112,
//MP1_LclkDid3                                            = 1113,
//MP1_LclkDid4                                            = 1114,
//MP1_LclkDid5                                            = 1115,
//MP1_LclkShadowVid0                                      = 1116,
//MP1_LclkShadowVid1                                      = 1117,
//MP1_LclkShadowVid2                                      = 1118,
//MP1_LclkShadowVid3                                      = 1119,
//MP1_LclkShadowVid4                                      = 1120,
//MP1_LclkShadowVid5                                      = 1121,
//MP1_LclkVid0                                            = 1122,
//MP1_LclkVid1                                            = 1123,
//MP1_LclkVid2                                            = 1124,
//MP1_LclkVid3                                            = 1125,
//MP1_LclkVid4                                            = 1126,
//MP1_LclkVid5                                            = 1127,
//MP1_MP1_GROUP0_DATA                                     = 1128,
//MP1_MP1_PUB_SPARE_FUSES                                 = 1129,
//MP1_MP1_SPARE                                           = 1130,
//MP1_MaxCpuCof                                           = 1131,
//MP1_MaxTDC                                              = 1132,
//MP1_MaxTDP                                              = 1133,
//MP1_MinOverClockCpuVid                                  = 1134,
//MP1_MinTDC                                              = 1135,
//MP1_MinTDP                                              = 1136,
//MP1_Mp0clkDid                                           = 1137,
//MP1_Mp1clkDid                                           = 1138,
//MP1_OdprFuseSlope                                       = 1139,
//MP1_PPTLimitScalar                                      = 1140,
//MP1_PPTLimitScalarReportingEn                           = 1141,
//MP1_PstateEn0                                           = 1142,
//MP1_PstateEn1                                           = 1143,
//MP1_PstateEn2                                           = 1144,
//MP1_PstateEn3                                           = 1145,
//MP1_PstateEn4                                           = 1146,
//MP1_PstateEn5                                           = 1147,
//MP1_PstateEn6                                           = 1148,
//MP1_PstateEn7                                           = 1149,
//MP1_ShubclkDid                                          = 1150,
//MP1_Sidd_RefTemp                                        = 1151,
//MP1_Sidd_RefTemp_Det                                    = 1152,
//MP1_SmnclkDid                                           = 1153,
//MP1_Soc_Sidd_Tb                                         = 1154,
//MP1_Soc_Sidd_Tb_WC                                      = 1155,
//MP1_Soc_Sidd_Tm                                         = 1156,
//MP1_Soc_Sidd_Tm_WC                                      = 1157,
//MP1_Soc_Sidd_b                                          = 1158,
//MP1_Soc_Sidd_b_WC                                       = 1159,
//MP1_Soc_Sidd_m                                          = 1160,
//MP1_Soc_Sidd_m_WC                                       = 1161,
//MP1_SocclkDid                                           = 1162,
//MP1_SuperVmaxThreshold                                  = 1163,
//MP1_SuperVminThreshold                                  = 1164,
//MP1_TDC                                                 = 1165,
//MP1_TDP                                                 = 1166,
//MP1_Tambient_WC                                         = 1167,
//MP1_Theta_ja                                            = 1168,
//MP1_TjMax                                               = 1169,
//MP1_VddcrSocVminShadowVid                               = 1170,
//MP1_VddcrSocVminVid                                     = 1171,
//MP1_Vddm_Sidd_Tb_WC                                     = 1172,
//MP1_Vddm_Sidd_Tm_WC                                     = 1173,
//MP1_Vddm_Sidd_b_WC                                      = 1174,
//MP1_Vddm_Sidd_m_WC                                      = 1175,
//MP1_VminFrequency                                       = 1176,
//MP1_WLBThreshold                                        = 1177,
//MP1_WLBThresholdBypass                                  = 1178,
//MP1_WaflclkDid                                          = 1179,
//MP5_CLDO_GMI2_BYPASS_DIS                                = 1180,
//MP5_CLDO_GMI2_SEL_SRC_VDDIO_MEM                         = 1181,
//MP5_CORE_DISABLE                                        = 1182,
//MP5_CPU_PWROK_REFCLK_GAP_CYCLES                         = 1183,
//MP5_DISABLE_MP5_BIHR                                    = 1184,
//MP5_DISABLE_MP5_MBIST                                   = 1185,
//MP5_DISABLE_PCS_PHY_WORKAROUND                          = 1186,
//MP5_DISTRIBUTE_LDO_FUSES                                = 1187,
//MP5_ENABLE_DBGU_CCD_POST_CODES                          = 1188,
//MP5_ENABLE_RSMU_WDT                                     = 1189,
//MP5_ENABLE_SBI_POST_CODES                               = 1190,
//MP5_HARVESTING_FUSES                                    = 1191,
//MP5_L3_RESET_MILESTONE                                  = 1192,
//MP5_LOAD_DIAG_BOOT_LOADER                               = 1193,
//MP5_MP5_GROUP0_DATA                                     = 1194,
//MP5_MP5_NONSECURE_FUSES                                 = 1195,
//MP5_MP5_WRITE_DISABLE                                   = 1196,
//MP5_PMFW_Core_Cac_b                                     = 1197,
//MP5_PMFW_Core_Cac_m                                     = 1198,
//MP5_PMFW_Core_Cold_temp                                 = 1199,
//MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE0                    = 1200,
//MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE1                    = 1201,
//MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE2                    = 1202,
//MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE3                    = 1203,
//MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE0                    = 1204,
//MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE1                    = 1205,
//MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE2                    = 1206,
//MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE3                    = 1207,
//MP5_PMFW_Core_FtoP_A_GuardBand                          = 1208,
//MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE0                     = 1209,
//MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE1                     = 1210,
//MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE2                     = 1211,
//MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE3                     = 1212,
//MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE0                     = 1213,
//MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE1                     = 1214,
//MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE2                     = 1215,
//MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE3                     = 1216,
//MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE0                     = 1217,
//MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE1                     = 1218,
//MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE2                     = 1219,
//MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE3                     = 1220,
//MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE0                     = 1221,
//MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE1                     = 1222,
//MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE2                     = 1223,
//MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE3                     = 1224,
//MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE0                    = 1225,
//MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE1                    = 1226,
//MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE2                    = 1227,
//MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE3                    = 1228,
//MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE0                    = 1229,
//MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE1                    = 1230,
//MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE2                    = 1231,
//MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE3                    = 1232,
//MP5_PMFW_Core_FtoP_B_GuardBand                          = 1233,
//MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE0                     = 1234,
//MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE1                     = 1235,
//MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE2                     = 1236,
//MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE3                     = 1237,
//MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE0                     = 1238,
//MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE1                     = 1239,
//MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE2                     = 1240,
//MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE3                     = 1241,
//MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE0                     = 1242,
//MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE1                     = 1243,
//MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE2                     = 1244,
//MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE3                     = 1245,
//MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE0                     = 1246,
//MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE1                     = 1247,
//MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE2                     = 1248,
//MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE3                     = 1249,
//MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE0                    = 1250,
//MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE1                    = 1251,
//MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE2                    = 1252,
//MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE3                    = 1253,
//MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE0                    = 1254,
//MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE1                    = 1255,
//MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE2                    = 1256,
//MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE3                    = 1257,
//MP5_PMFW_Core_FtoP_C_GuardBand                          = 1258,
//MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE0                     = 1259,
//MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE1                     = 1260,
//MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE2                     = 1261,
//MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE3                     = 1262,
//MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE0                     = 1263,
//MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE1                     = 1264,
//MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE2                     = 1265,
//MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE3                     = 1266,
//MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE0                     = 1267,
//MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE1                     = 1268,
//MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE2                     = 1269,
//MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE3                     = 1270,
//MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE0                     = 1271,
//MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE1                     = 1272,
//MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE2                     = 1273,
//MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE3                     = 1274,
//MP5_PMFW_Core_Hot_temp                                  = 1275,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE0        = 1276,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE1        = 1277,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE2        = 1278,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE3        = 1279,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE0        = 1280,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE1        = 1281,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE2        = 1282,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE3        = 1283,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE0        = 1284,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE1        = 1285,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE2        = 1286,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE3        = 1287,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE0        = 1288,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE1        = 1289,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE2        = 1290,
//MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE3        = 1291,
//MP5_PMFW_Core_LDO_FDD_Value_HI                          = 1292,
//MP5_PMFW_Core_LDO_FDD_Value_LO                          = 1293,
//MP5_PMFW_Core_LDO_FDD_Voltage_HI                        = 1294,
//MP5_PMFW_Core_LDO_FDD_Voltage_LO                        = 1295,
//MP5_PMFW_Core_Med_temp                                  = 1296,
//MP5_PMFW_Core_PtoV_A_COLD_CCX0                          = 1297,
//MP5_PMFW_Core_PtoV_A_COLD_CCX1                          = 1298,
//MP5_PMFW_Core_PtoV_A_HOT_CCX0                           = 1299,
//MP5_PMFW_Core_PtoV_A_HOT_CCX1                           = 1300,
//MP5_PMFW_Core_PtoV_A_MED_CCX0                           = 1301,
//MP5_PMFW_Core_PtoV_A_MED_CCX1                           = 1302,
//MP5_PMFW_Core_PtoV_B_COLD_CCX0                          = 1303,
//MP5_PMFW_Core_PtoV_B_COLD_CCX1                          = 1304,
//MP5_PMFW_Core_PtoV_B_HOT_CCX0                           = 1305,
//MP5_PMFW_Core_PtoV_B_HOT_CCX1                           = 1306,
//MP5_PMFW_Core_PtoV_B_MED_CCX0                           = 1307,
//MP5_PMFW_Core_PtoV_B_MED_CCX1                           = 1308,
//MP5_PMFW_Core_PtoV_C_COLD_CCX0                          = 1309,
//MP5_PMFW_Core_PtoV_C_COLD_CCX1                          = 1310,
//MP5_PMFW_Core_PtoV_C_HOT_CCX0                           = 1311,
//MP5_PMFW_Core_PtoV_C_HOT_CCX1                           = 1312,
//MP5_PMFW_Core_PtoV_C_MED_CCX0                           = 1313,
//MP5_PMFW_Core_PtoV_C_MED_CCX1                           = 1314,
//MP5_PMFW_Core_Sidd_Tb                                   = 1315,
//MP5_PMFW_Core_Sidd_Tm                                   = 1316,
//MP5_PMFW_Core_Sidd_b                                    = 1317,
//MP5_PMFW_Core_Sidd_m                                    = 1318,
//MP5_PMFW_L3_FtoV_A_COLD                                 = 1319,
//MP5_PMFW_L3_FtoV_A_HOT                                  = 1320,
//MP5_PMFW_L3_FtoV_A_MED                                  = 1321,
//MP5_PMFW_L3_FtoV_B_COLD                                 = 1322,
//MP5_PMFW_L3_FtoV_B_HOT                                  = 1323,
//MP5_PMFW_L3_FtoV_B_MED                                  = 1324,
//MP5_PMFW_L3_FtoV_C_COLD                                 = 1325,
//MP5_PMFW_L3_FtoV_C_HOT                                  = 1326,
//MP5_PMFW_L3_FtoV_C_MED                                  = 1327,
//MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX0                = 1328,
//MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX1                = 1329,
//MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX0                = 1330,
//MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX1                = 1331,
//MP5_PMFW_MP5_PMFW_PUB_SPARE_FUSES                       = 1332,
//MP5_PMFW_MP5_SPARE                                      = 1333,
//MP5_PMFW_OdprFuseSlope                                  = 1334,
//MP5_PMFW_Sidd_RefTemp                                   = 1335,
//MP5_PMFW_Vddm_Sidd_Tb                                   = 1336,
//MP5_PMFW_Vddm_Sidd_Tm                                   = 1337,
//MP5_PMFW_Vddm_Sidd_b                                    = 1338,
//MP5_PMFW_Vddm_Sidd_m                                    = 1339,
//MP5_RELEASE_CPU_RESET                                   = 1340,
//MP5_RSMU_FUSE_VALID                                     = 1341,
//MP5_RUN_BIHR                                            = 1342,
//MP5_RUN_MBIST                                           = 1343,
//MP5_SET_BOOTROM_STARTUP_CLOCKS                          = 1344,
//MP5_SKIP_EXIT_BYPASS                                    = 1345,
//MP5_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE          = 1346,
//MP5_SMT_ENABLE                                          = 1347,
//MP5_SRAM_CUSTOM_RM                                      = 1348,
//MP5_SRAM_HD_BC1                                         = 1349,
//MP5_SRAM_HD_BC2                                         = 1350,
//MP5_SRAM_PDP_BC1                                        = 1351,
//MP5_SRAM_PDP_BC2                                        = 1352,
//MP5_SRAM_RM                                             = 1353,
//MP5_SRAM_SPARE_0                                        = 1354,
//MP5_WAFL_DBG_INTERLOCK_1                                = 1355,
//MP5_WAFL_DBG_INTERLOCK_2                                = 1356,
//MP5_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE            = 1357,
//MP5_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE               = 1358,
//MP5_WaflInvertLinkAddr0                                 = 1359,
//MP5_WaflInvertLinkAddr1                                 = 1360,
//MP5_WaflInvertSmnAddr0                                  = 1361,
//MP5_WaflInvertSmnAddr1                                  = 1362,
//NBIF0_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES                = 1363,
//NBIF0_NBIF_SSP_GENERIC_A_WRITE_DISABLE                  = 1364,
//NBIF0_STRAP_BIF_FUSESTRAP_VALID                         = 1365,
//NBIF0_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1366,
//NBIF0_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1367,
//NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1368,
//NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1369,
//NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1370,
//NBIF0_STRAP_BIF_STRAP_HWREV_LSB2                        = 1371,
//NBIF0_STRAP_BIF_STRAP_SWREV_LSB2                        = 1372,
//NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1373,
//NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1374,
//NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1375,
//NBIF10_NBIF10_GROUP0_DATA                               = 1376,
//NBIF10_NBIF_SSP_NTB_PUB_SPARE_FUSES                     = 1377,
//NBIF10_NBIF_SSP_NTB_WRITE_DISABLE                       = 1378,
//NBIF10_STRAP_BIF_FUSESTRAP_VALID                        = 1379,
//NBIF10_STRAP_BIF_RESERVED_BIF_STRAP2                    = 1380,
//NBIF10_STRAP_BIF_RESERVED_BIF_STRAP3                    = 1381,
//NBIF10_STRAP_BIF_STRAP_DN_DEVNUM_DEV0                   = 1382,
//NBIF10_STRAP_BIF_STRAP_DN_FUNCID_DEV0                   = 1383,
//NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                  = 1384,
//NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                  = 1385,
//NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                  = 1386,
//NBIF10_STRAP_BIF_STRAP_HWREV_LSB2                       = 1387,
//NBIF10_STRAP_BIF_STRAP_SWREV_LSB2                       = 1388,
//NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0            = 1389,
//NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1            = 1390,
//NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2            = 1391,
//NBIF11_NBIF11_GROUP0_DATA                               = 1392,
//NBIF11_NBIF_SSP_NTB_PUB_SPARE_FUSES                     = 1393,
//NBIF11_NBIF_SSP_NTB_WRITE_DISABLE                       = 1394,
//NBIF11_STRAP_BIF_FUSESTRAP_VALID                        = 1395,
//NBIF11_STRAP_BIF_RESERVED_BIF_STRAP2                    = 1396,
//NBIF11_STRAP_BIF_RESERVED_BIF_STRAP3                    = 1397,
//NBIF11_STRAP_BIF_STRAP_DN_DEVNUM_DEV0                   = 1398,
//NBIF11_STRAP_BIF_STRAP_DN_FUNCID_DEV0                   = 1399,
//NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                  = 1400,
//NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                  = 1401,
//NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                  = 1402,
//NBIF11_STRAP_BIF_STRAP_HWREV_LSB2                       = 1403,
//NBIF11_STRAP_BIF_STRAP_SWREV_LSB2                       = 1404,
//NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0            = 1405,
//NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1            = 1406,
//NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2            = 1407,
//NBIF1_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES                = 1408,
//NBIF1_NBIF_SSP_GENERIC_A_WRITE_DISABLE                  = 1409,
//NBIF1_STRAP_BIF_FUSESTRAP_VALID                         = 1410,
//NBIF1_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1411,
//NBIF1_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1412,
//NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1413,
//NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1414,
//NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1415,
//NBIF1_STRAP_BIF_STRAP_HWREV_LSB2                        = 1416,
//NBIF1_STRAP_BIF_STRAP_SWREV_LSB2                        = 1417,
//NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1418,
//NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1419,
//NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1420,
//NBIF2_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES                = 1421,
//NBIF2_NBIF_SSP_GENERIC_A_WRITE_DISABLE                  = 1422,
//NBIF2_STRAP_BIF_FUSESTRAP_VALID                         = 1423,
//NBIF2_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1424,
//NBIF2_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1425,
//NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1426,
//NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1427,
//NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1428,
//NBIF2_STRAP_BIF_STRAP_HWREV_LSB2                        = 1429,
//NBIF2_STRAP_BIF_STRAP_SWREV_LSB2                        = 1430,
//NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1431,
//NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1432,
//NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1433,
//NBIF3_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES                = 1434,
//NBIF3_NBIF_SSP_GENERIC_A_WRITE_DISABLE                  = 1435,
//NBIF3_STRAP_BIF_FUSESTRAP_VALID                         = 1436,
//NBIF3_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1437,
//NBIF3_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1438,
//NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1439,
//NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1440,
//NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1441,
//NBIF3_STRAP_BIF_STRAP_HWREV_LSB2                        = 1442,
//NBIF3_STRAP_BIF_STRAP_SWREV_LSB2                        = 1443,
//NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1444,
//NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1445,
//NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1446,
//NBIF4_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES                = 1447,
//NBIF4_NBIF_SSP_GENERIC_B_WRITE_DISABLE                  = 1448,
//NBIF4_STRAP_BIF_FUSESTRAP_VALID                         = 1449,
//NBIF4_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1450,
//NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3            = 1451,
//NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4            = 1452,
//NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3                 = 1453,
//NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0                 = 1454,
//NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0                 = 1455,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1456,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1457,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1458,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3                   = 1459,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4                   = 1460,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0                   = 1461,
//NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0                   = 1462,
//NBIF4_STRAP_BIF_STRAP_HWREV_LSB2                        = 1463,
//NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0        = 1464,
//NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0        = 1465,
//NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0        = 1466,
//NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0        = 1467,
//NBIF4_STRAP_BIF_STRAP_SWREV_LSB2                        = 1468,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1469,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1470,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1471,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3             = 1472,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4             = 1473,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0             = 1474,
//NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0             = 1475,
//NBIF5_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES                = 1476,
//NBIF5_NBIF_SSP_GENERIC_B_WRITE_DISABLE                  = 1477,
//NBIF5_STRAP_BIF_FUSESTRAP_VALID                         = 1478,
//NBIF5_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1479,
//NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3            = 1480,
//NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4            = 1481,
//NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3                 = 1482,
//NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0                 = 1483,
//NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0                 = 1484,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1485,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1486,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1487,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3                   = 1488,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4                   = 1489,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0                   = 1490,
//NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0                   = 1491,
//NBIF5_STRAP_BIF_STRAP_HWREV_LSB2                        = 1492,
//NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0        = 1493,
//NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0        = 1494,
//NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0        = 1495,
//NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0        = 1496,
//NBIF5_STRAP_BIF_STRAP_SWREV_LSB2                        = 1497,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1498,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1499,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1500,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3             = 1501,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4             = 1502,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0             = 1503,
//NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0             = 1504,
//NBIF6_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES                = 1505,
//NBIF6_NBIF_SSP_GENERIC_B_WRITE_DISABLE                  = 1506,
//NBIF6_STRAP_BIF_FUSESTRAP_VALID                         = 1507,
//NBIF6_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1508,
//NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3            = 1509,
//NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4            = 1510,
//NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3                 = 1511,
//NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0                 = 1512,
//NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0                 = 1513,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1514,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1515,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1516,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3                   = 1517,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4                   = 1518,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0                   = 1519,
//NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0                   = 1520,
//NBIF6_STRAP_BIF_STRAP_HWREV_LSB2                        = 1521,
//NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0        = 1522,
//NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0        = 1523,
//NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0        = 1524,
//NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0        = 1525,
//NBIF6_STRAP_BIF_STRAP_SWREV_LSB2                        = 1526,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1527,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1528,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1529,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3             = 1530,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4             = 1531,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0             = 1532,
//NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0             = 1533,
//NBIF7_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES                = 1534,
//NBIF7_NBIF_SSP_GENERIC_B_WRITE_DISABLE                  = 1535,
//NBIF7_STRAP_BIF_FUSESTRAP_VALID                         = 1536,
//NBIF7_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1537,
//NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3            = 1538,
//NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4            = 1539,
//NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3                 = 1540,
//NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0                 = 1541,
//NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0                 = 1542,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1543,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1544,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1545,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3                   = 1546,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4                   = 1547,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0                   = 1548,
//NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0                   = 1549,
//NBIF7_STRAP_BIF_STRAP_HWREV_LSB2                        = 1550,
//NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0        = 1551,
//NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0        = 1552,
//NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0        = 1553,
//NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0        = 1554,
//NBIF7_STRAP_BIF_STRAP_SWREV_LSB2                        = 1555,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1556,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1557,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1558,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3             = 1559,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4             = 1560,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0             = 1561,
//NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0             = 1562,
//NBIF8_NBIF8_GROUP0_DATA                                 = 1563,
//NBIF8_NBIF_SSP_NTB_PUB_SPARE_FUSES                      = 1564,
//NBIF8_NBIF_SSP_NTB_WRITE_DISABLE                        = 1565,
//NBIF8_STRAP_BIF_FUSESTRAP_VALID                         = 1566,
//NBIF8_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1567,
//NBIF8_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1568,
//NBIF8_STRAP_BIF_STRAP_DN_DEVNUM_DEV0                    = 1569,
//NBIF8_STRAP_BIF_STRAP_DN_FUNCID_DEV0                    = 1570,
//NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1571,
//NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1572,
//NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1573,
//NBIF8_STRAP_BIF_STRAP_HWREV_LSB2                        = 1574,
//NBIF8_STRAP_BIF_STRAP_SWREV_LSB2                        = 1575,
//NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1576,
//NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1577,
//NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1578,
//NBIF9_NBIF9_GROUP0_DATA                                 = 1579,
//NBIF9_NBIF_SSP_NTB_PUB_SPARE_FUSES                      = 1580,
//NBIF9_NBIF_SSP_NTB_WRITE_DISABLE                        = 1581,
//NBIF9_STRAP_BIF_FUSESTRAP_VALID                         = 1582,
//NBIF9_STRAP_BIF_RESERVED_BIF_STRAP2                     = 1583,
//NBIF9_STRAP_BIF_RESERVED_BIF_STRAP3                     = 1584,
//NBIF9_STRAP_BIF_STRAP_DN_DEVNUM_DEV0                    = 1585,
//NBIF9_STRAP_BIF_STRAP_DN_FUNCID_DEV0                    = 1586,
//NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0                   = 1587,
//NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1                   = 1588,
//NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2                   = 1589,
//NBIF9_STRAP_BIF_STRAP_HWREV_LSB2                        = 1590,
//NBIF9_STRAP_BIF_STRAP_SWREV_LSB2                        = 1591,
//NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0             = 1592,
//NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1             = 1593,
//NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2             = 1594,
//NTB_NTB_PUB_SPARE_FUSES                                 = 1595,
//NTB_NVME_STRAP_CAP_AMS                                  = 1596,
//NTB_NVME_STRAP_CAP_CQR                                  = 1597,
//NTB_NVME_STRAP_CAP_CSS                                  = 1598,
//NTB_NVME_STRAP_CAP_DSTRD                                = 1599,
//NTB_NVME_STRAP_CAP_MPSMAX                               = 1600,
//NTB_NVME_STRAP_CAP_MPSMIN                               = 1601,
//NTB_NVME_STRAP_CAP_MQES                                 = 1602,
//NTB_NVME_STRAP_CAP_NSSRS                                = 1603,
//NTB_NVME_STRAP_CAP_TO                                   = 1604,
//OPN_ConfigId                                            = 1605,
//OPN_CpuID_ExtModel                                      = 1606,
//OPN_CpuID_Model                                         = 1607,
//OPN_CpuID_Stepping                                      = 1608,
//OPN_IntRev                                              = 1609,
//OPN_MSID                                                = 1610,
//OPN_NameString_0                                        = 1611,
//OPN_NameString_1                                        = 1612,
//OPN_NameString_10                                       = 1613,
//OPN_NameString_11                                       = 1614,
//OPN_NameString_12                                       = 1615,
//OPN_NameString_13                                       = 1616,
//OPN_NameString_14                                       = 1617,
//OPN_NameString_15                                       = 1618,
//OPN_NameString_16                                       = 1619,
//OPN_NameString_17                                       = 1620,
//OPN_NameString_18                                       = 1621,
//OPN_NameString_19                                       = 1622,
//OPN_NameString_2                                        = 1623,
//OPN_NameString_20                                       = 1624,
//OPN_NameString_21                                       = 1625,
//OPN_NameString_22                                       = 1626,
//OPN_NameString_23                                       = 1627,
//OPN_NameString_24                                       = 1628,
//OPN_NameString_25                                       = 1629,
//OPN_NameString_26                                       = 1630,
//OPN_NameString_27                                       = 1631,
//OPN_NameString_28                                       = 1632,
//OPN_NameString_29                                       = 1633,
//OPN_NameString_3                                        = 1634,
//OPN_NameString_30                                       = 1635,
//OPN_NameString_31                                       = 1636,
//OPN_NameString_32                                       = 1637,
//OPN_NameString_33                                       = 1638,
//OPN_NameString_34                                       = 1639,
//OPN_NameString_35                                       = 1640,
//OPN_NameString_36                                       = 1641,
//OPN_NameString_37                                       = 1642,
//OPN_NameString_38                                       = 1643,
//OPN_NameString_39                                       = 1644,
//OPN_NameString_4                                        = 1645,
//OPN_NameString_40                                       = 1646,
//OPN_NameString_41                                       = 1647,
//OPN_NameString_42                                       = 1648,
//OPN_NameString_43                                       = 1649,
//OPN_NameString_44                                       = 1650,
//OPN_NameString_45                                       = 1651,
//OPN_NameString_46                                       = 1652,
//OPN_NameString_5                                        = 1653,
//OPN_NameString_6                                        = 1654,
//OPN_NameString_7                                        = 1655,
//OPN_NameString_8                                        = 1656,
//OPN_NameString_9                                        = 1657,
//OPN_OPN_SPARE                                           = 1658,
//OPN_PkgID                                               = 1659,
//OPN_Utility                                             = 1660,
//PCIE0_PCIE0_PUB_SPARE_FUSES                             = 1661,
//PCIE0_PCIE0_WRITE_DISABLE                               = 1662,
//PCIE0_PCIE_EFUSE2_RESERVED_1                            = 1663,
//PCIE0_PCIE_EFUSE2_RESERVED_2                            = 1664,
//PCIE0_PCIE_EFUSE3_RESERVED_1                            = 1665,
//PCIE0_PCIE_EFUSE3_RESERVED_2                            = 1666,
//PCIE0_PCIE_EFUSE4_RESERVED                              = 1667,
//PCIE0_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1668,
//PCIE0_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1669,
//PCIE0_STRAP_BIF_DEVICE_ID_w                             = 1670,
//PCIE0_STRAP_BIF_GEN2_EN_w_A                             = 1671,
//PCIE0_STRAP_BIF_GEN2_EN_w_B                             = 1672,
//PCIE0_STRAP_BIF_GEN2_EN_w_C                             = 1673,
//PCIE0_STRAP_BIF_GEN2_EN_w_D                             = 1674,
//PCIE0_STRAP_BIF_GEN2_EN_w_E                             = 1675,
//PCIE0_STRAP_BIF_GEN2_EN_w_F                             = 1676,
//PCIE0_STRAP_BIF_GEN2_EN_w_G                             = 1677,
//PCIE0_STRAP_BIF_GEN2_EN_w_H                             = 1678,
//PCIE0_STRAP_BIF_GEN3_EN_w_A                             = 1679,
//PCIE0_STRAP_BIF_GEN3_EN_w_B                             = 1680,
//PCIE0_STRAP_BIF_GEN3_EN_w_C                             = 1681,
//PCIE0_STRAP_BIF_GEN3_EN_w_D                             = 1682,
//PCIE0_STRAP_BIF_GEN3_EN_w_E                             = 1683,
//PCIE0_STRAP_BIF_GEN3_EN_w_F                             = 1684,
//PCIE0_STRAP_BIF_GEN3_EN_w_G                             = 1685,
//PCIE0_STRAP_BIF_GEN3_EN_w_H                             = 1686,
//PCIE0_STRAP_BIF_GEN4_EN_w_A                             = 1687,
//PCIE0_STRAP_BIF_GEN4_EN_w_B                             = 1688,
//PCIE0_STRAP_BIF_GEN4_EN_w_C                             = 1689,
//PCIE0_STRAP_BIF_GEN4_EN_w_D                             = 1690,
//PCIE0_STRAP_BIF_GEN4_EN_w_E                             = 1691,
//PCIE0_STRAP_BIF_GEN4_EN_w_F                             = 1692,
//PCIE0_STRAP_BIF_GEN4_EN_w_G                             = 1693,
//PCIE0_STRAP_BIF_GEN4_EN_w_H                             = 1694,
//PCIE0_STRAP_BIF_LANE_NEGOTIATION                        = 1695,
//PCIE0_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1696,
//PCIE0_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1697,
//PCIE0_STRAP_BIF_LONG_yTSx_COUNT                         = 1698,
//PCIE0_STRAP_BIF_MED_yTSx_COUNT                          = 1699,
//PCIE0_STRAP_BIF_PHYSTATUS_SELECT                        = 1700,
//PCIE0_STRAP_BIF_SHORT_yTSx_COUNT                        = 1701,
//PCIE0_STRAP_BIF_SKIP_INTERVAL                           = 1702,
//PCIE0_STRAP_CHIP_BIF_MODE                               = 1703,
//PCIE1_PCIE0_PUB_SPARE_FUSES                             = 1704,
//PCIE1_PCIE0_WRITE_DISABLE                               = 1705,
//PCIE1_PCIE_EFUSE2_RESERVED_1                            = 1706,
//PCIE1_PCIE_EFUSE2_RESERVED_2                            = 1707,
//PCIE1_PCIE_EFUSE3_RESERVED_1                            = 1708,
//PCIE1_PCIE_EFUSE3_RESERVED_2                            = 1709,
//PCIE1_PCIE_EFUSE4_RESERVED                              = 1710,
//PCIE1_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1711,
//PCIE1_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1712,
//PCIE1_STRAP_BIF_DEVICE_ID_w                             = 1713,
//PCIE1_STRAP_BIF_GEN2_EN_w_A                             = 1714,
//PCIE1_STRAP_BIF_GEN2_EN_w_B                             = 1715,
//PCIE1_STRAP_BIF_GEN2_EN_w_C                             = 1716,
//PCIE1_STRAP_BIF_GEN2_EN_w_D                             = 1717,
//PCIE1_STRAP_BIF_GEN2_EN_w_E                             = 1718,
//PCIE1_STRAP_BIF_GEN2_EN_w_F                             = 1719,
//PCIE1_STRAP_BIF_GEN2_EN_w_G                             = 1720,
//PCIE1_STRAP_BIF_GEN2_EN_w_H                             = 1721,
//PCIE1_STRAP_BIF_GEN3_EN_w_A                             = 1722,
//PCIE1_STRAP_BIF_GEN3_EN_w_B                             = 1723,
//PCIE1_STRAP_BIF_GEN3_EN_w_C                             = 1724,
//PCIE1_STRAP_BIF_GEN3_EN_w_D                             = 1725,
//PCIE1_STRAP_BIF_GEN3_EN_w_E                             = 1726,
//PCIE1_STRAP_BIF_GEN3_EN_w_F                             = 1727,
//PCIE1_STRAP_BIF_GEN3_EN_w_G                             = 1728,
//PCIE1_STRAP_BIF_GEN3_EN_w_H                             = 1729,
//PCIE1_STRAP_BIF_GEN4_EN_w_A                             = 1730,
//PCIE1_STRAP_BIF_GEN4_EN_w_B                             = 1731,
//PCIE1_STRAP_BIF_GEN4_EN_w_C                             = 1732,
//PCIE1_STRAP_BIF_GEN4_EN_w_D                             = 1733,
//PCIE1_STRAP_BIF_GEN4_EN_w_E                             = 1734,
//PCIE1_STRAP_BIF_GEN4_EN_w_F                             = 1735,
//PCIE1_STRAP_BIF_GEN4_EN_w_G                             = 1736,
//PCIE1_STRAP_BIF_GEN4_EN_w_H                             = 1737,
//PCIE1_STRAP_BIF_LANE_NEGOTIATION                        = 1738,
//PCIE1_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1739,
//PCIE1_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1740,
//PCIE1_STRAP_BIF_LONG_yTSx_COUNT                         = 1741,
//PCIE1_STRAP_BIF_MED_yTSx_COUNT                          = 1742,
//PCIE1_STRAP_BIF_PHYSTATUS_SELECT                        = 1743,
//PCIE1_STRAP_BIF_SHORT_yTSx_COUNT                        = 1744,
//PCIE1_STRAP_BIF_SKIP_INTERVAL                           = 1745,
//PCIE1_STRAP_CHIP_BIF_MODE                               = 1746,
//PCIE2_PCIE0_PUB_SPARE_FUSES                             = 1747,
//PCIE2_PCIE0_WRITE_DISABLE                               = 1748,
//PCIE2_PCIE_EFUSE2_RESERVED_1                            = 1749,
//PCIE2_PCIE_EFUSE2_RESERVED_2                            = 1750,
//PCIE2_PCIE_EFUSE3_RESERVED_1                            = 1751,
//PCIE2_PCIE_EFUSE3_RESERVED_2                            = 1752,
//PCIE2_PCIE_EFUSE4_RESERVED                              = 1753,
//PCIE2_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1754,
//PCIE2_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1755,
//PCIE2_STRAP_BIF_DEVICE_ID_w                             = 1756,
//PCIE2_STRAP_BIF_GEN2_EN_w_A                             = 1757,
//PCIE2_STRAP_BIF_GEN2_EN_w_B                             = 1758,
//PCIE2_STRAP_BIF_GEN2_EN_w_C                             = 1759,
//PCIE2_STRAP_BIF_GEN2_EN_w_D                             = 1760,
//PCIE2_STRAP_BIF_GEN2_EN_w_E                             = 1761,
//PCIE2_STRAP_BIF_GEN2_EN_w_F                             = 1762,
//PCIE2_STRAP_BIF_GEN2_EN_w_G                             = 1763,
//PCIE2_STRAP_BIF_GEN2_EN_w_H                             = 1764,
//PCIE2_STRAP_BIF_GEN3_EN_w_A                             = 1765,
//PCIE2_STRAP_BIF_GEN3_EN_w_B                             = 1766,
//PCIE2_STRAP_BIF_GEN3_EN_w_C                             = 1767,
//PCIE2_STRAP_BIF_GEN3_EN_w_D                             = 1768,
//PCIE2_STRAP_BIF_GEN3_EN_w_E                             = 1769,
//PCIE2_STRAP_BIF_GEN3_EN_w_F                             = 1770,
//PCIE2_STRAP_BIF_GEN3_EN_w_G                             = 1771,
//PCIE2_STRAP_BIF_GEN3_EN_w_H                             = 1772,
//PCIE2_STRAP_BIF_GEN4_EN_w_A                             = 1773,
//PCIE2_STRAP_BIF_GEN4_EN_w_B                             = 1774,
//PCIE2_STRAP_BIF_GEN4_EN_w_C                             = 1775,
//PCIE2_STRAP_BIF_GEN4_EN_w_D                             = 1776,
//PCIE2_STRAP_BIF_GEN4_EN_w_E                             = 1777,
//PCIE2_STRAP_BIF_GEN4_EN_w_F                             = 1778,
//PCIE2_STRAP_BIF_GEN4_EN_w_G                             = 1779,
//PCIE2_STRAP_BIF_GEN4_EN_w_H                             = 1780,
//PCIE2_STRAP_BIF_LANE_NEGOTIATION                        = 1781,
//PCIE2_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1782,
//PCIE2_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1783,
//PCIE2_STRAP_BIF_LONG_yTSx_COUNT                         = 1784,
//PCIE2_STRAP_BIF_MED_yTSx_COUNT                          = 1785,
//PCIE2_STRAP_BIF_PHYSTATUS_SELECT                        = 1786,
//PCIE2_STRAP_BIF_SHORT_yTSx_COUNT                        = 1787,
//PCIE2_STRAP_BIF_SKIP_INTERVAL                           = 1788,
//PCIE2_STRAP_CHIP_BIF_MODE                               = 1789,
//PCIE3_PCIE0_PUB_SPARE_FUSES                             = 1790,
//PCIE3_PCIE0_WRITE_DISABLE                               = 1791,
//PCIE3_PCIE_EFUSE2_RESERVED_1                            = 1792,
//PCIE3_PCIE_EFUSE2_RESERVED_2                            = 1793,
//PCIE3_PCIE_EFUSE3_RESERVED_1                            = 1794,
//PCIE3_PCIE_EFUSE3_RESERVED_2                            = 1795,
//PCIE3_PCIE_EFUSE4_RESERVED                              = 1796,
//PCIE3_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1797,
//PCIE3_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1798,
//PCIE3_STRAP_BIF_DEVICE_ID_w                             = 1799,
//PCIE3_STRAP_BIF_GEN2_EN_w_A                             = 1800,
//PCIE3_STRAP_BIF_GEN2_EN_w_B                             = 1801,
//PCIE3_STRAP_BIF_GEN2_EN_w_C                             = 1802,
//PCIE3_STRAP_BIF_GEN2_EN_w_D                             = 1803,
//PCIE3_STRAP_BIF_GEN2_EN_w_E                             = 1804,
//PCIE3_STRAP_BIF_GEN2_EN_w_F                             = 1805,
//PCIE3_STRAP_BIF_GEN2_EN_w_G                             = 1806,
//PCIE3_STRAP_BIF_GEN2_EN_w_H                             = 1807,
//PCIE3_STRAP_BIF_GEN3_EN_w_A                             = 1808,
//PCIE3_STRAP_BIF_GEN3_EN_w_B                             = 1809,
//PCIE3_STRAP_BIF_GEN3_EN_w_C                             = 1810,
//PCIE3_STRAP_BIF_GEN3_EN_w_D                             = 1811,
//PCIE3_STRAP_BIF_GEN3_EN_w_E                             = 1812,
//PCIE3_STRAP_BIF_GEN3_EN_w_F                             = 1813,
//PCIE3_STRAP_BIF_GEN3_EN_w_G                             = 1814,
//PCIE3_STRAP_BIF_GEN3_EN_w_H                             = 1815,
//PCIE3_STRAP_BIF_GEN4_EN_w_A                             = 1816,
//PCIE3_STRAP_BIF_GEN4_EN_w_B                             = 1817,
//PCIE3_STRAP_BIF_GEN4_EN_w_C                             = 1818,
//PCIE3_STRAP_BIF_GEN4_EN_w_D                             = 1819,
//PCIE3_STRAP_BIF_GEN4_EN_w_E                             = 1820,
//PCIE3_STRAP_BIF_GEN4_EN_w_F                             = 1821,
//PCIE3_STRAP_BIF_GEN4_EN_w_G                             = 1822,
//PCIE3_STRAP_BIF_GEN4_EN_w_H                             = 1823,
//PCIE3_STRAP_BIF_LANE_NEGOTIATION                        = 1824,
//PCIE3_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1825,
//PCIE3_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1826,
//PCIE3_STRAP_BIF_LONG_yTSx_COUNT                         = 1827,
//PCIE3_STRAP_BIF_MED_yTSx_COUNT                          = 1828,
//PCIE3_STRAP_BIF_PHYSTATUS_SELECT                        = 1829,
//PCIE3_STRAP_BIF_SHORT_yTSx_COUNT                        = 1830,
//PCIE3_STRAP_BIF_SKIP_INTERVAL                           = 1831,
//PCIE3_STRAP_CHIP_BIF_MODE                               = 1832,
//PCIE4_PCIE0_PUB_SPARE_FUSES                             = 1833,
//PCIE4_PCIE0_WRITE_DISABLE                               = 1834,
//PCIE4_PCIE_EFUSE2_RESERVED_1                            = 1835,
//PCIE4_PCIE_EFUSE2_RESERVED_2                            = 1836,
//PCIE4_PCIE_EFUSE3_RESERVED_1                            = 1837,
//PCIE4_PCIE_EFUSE3_RESERVED_2                            = 1838,
//PCIE4_PCIE_EFUSE4_RESERVED                              = 1839,
//PCIE4_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1840,
//PCIE4_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1841,
//PCIE4_STRAP_BIF_DEVICE_ID_w                             = 1842,
//PCIE4_STRAP_BIF_GEN2_EN_w_A                             = 1843,
//PCIE4_STRAP_BIF_GEN2_EN_w_B                             = 1844,
//PCIE4_STRAP_BIF_GEN2_EN_w_C                             = 1845,
//PCIE4_STRAP_BIF_GEN2_EN_w_D                             = 1846,
//PCIE4_STRAP_BIF_GEN2_EN_w_E                             = 1847,
//PCIE4_STRAP_BIF_GEN2_EN_w_F                             = 1848,
//PCIE4_STRAP_BIF_GEN2_EN_w_G                             = 1849,
//PCIE4_STRAP_BIF_GEN2_EN_w_H                             = 1850,
//PCIE4_STRAP_BIF_GEN3_EN_w_A                             = 1851,
//PCIE4_STRAP_BIF_GEN3_EN_w_B                             = 1852,
//PCIE4_STRAP_BIF_GEN3_EN_w_C                             = 1853,
//PCIE4_STRAP_BIF_GEN3_EN_w_D                             = 1854,
//PCIE4_STRAP_BIF_GEN3_EN_w_E                             = 1855,
//PCIE4_STRAP_BIF_GEN3_EN_w_F                             = 1856,
//PCIE4_STRAP_BIF_GEN3_EN_w_G                             = 1857,
//PCIE4_STRAP_BIF_GEN3_EN_w_H                             = 1858,
//PCIE4_STRAP_BIF_GEN4_EN_w_A                             = 1859,
//PCIE4_STRAP_BIF_GEN4_EN_w_B                             = 1860,
//PCIE4_STRAP_BIF_GEN4_EN_w_C                             = 1861,
//PCIE4_STRAP_BIF_GEN4_EN_w_D                             = 1862,
//PCIE4_STRAP_BIF_GEN4_EN_w_E                             = 1863,
//PCIE4_STRAP_BIF_GEN4_EN_w_F                             = 1864,
//PCIE4_STRAP_BIF_GEN4_EN_w_G                             = 1865,
//PCIE4_STRAP_BIF_GEN4_EN_w_H                             = 1866,
//PCIE4_STRAP_BIF_LANE_NEGOTIATION                        = 1867,
//PCIE4_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1868,
//PCIE4_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1869,
//PCIE4_STRAP_BIF_LONG_yTSx_COUNT                         = 1870,
//PCIE4_STRAP_BIF_MED_yTSx_COUNT                          = 1871,
//PCIE4_STRAP_BIF_PHYSTATUS_SELECT                        = 1872,
//PCIE4_STRAP_BIF_SHORT_yTSx_COUNT                        = 1873,
//PCIE4_STRAP_BIF_SKIP_INTERVAL                           = 1874,
//PCIE4_STRAP_CHIP_BIF_MODE                               = 1875,
//PCIE5_PCIE0_PUB_SPARE_FUSES                             = 1876,
//PCIE5_PCIE0_WRITE_DISABLE                               = 1877,
//PCIE5_PCIE_EFUSE2_RESERVED_1                            = 1878,
//PCIE5_PCIE_EFUSE2_RESERVED_2                            = 1879,
//PCIE5_PCIE_EFUSE3_RESERVED_1                            = 1880,
//PCIE5_PCIE_EFUSE3_RESERVED_2                            = 1881,
//PCIE5_PCIE_EFUSE4_RESERVED                              = 1882,
//PCIE5_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1883,
//PCIE5_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1884,
//PCIE5_STRAP_BIF_DEVICE_ID_w                             = 1885,
//PCIE5_STRAP_BIF_GEN2_EN_w_A                             = 1886,
//PCIE5_STRAP_BIF_GEN2_EN_w_B                             = 1887,
//PCIE5_STRAP_BIF_GEN2_EN_w_C                             = 1888,
//PCIE5_STRAP_BIF_GEN2_EN_w_D                             = 1889,
//PCIE5_STRAP_BIF_GEN2_EN_w_E                             = 1890,
//PCIE5_STRAP_BIF_GEN2_EN_w_F                             = 1891,
//PCIE5_STRAP_BIF_GEN2_EN_w_G                             = 1892,
//PCIE5_STRAP_BIF_GEN2_EN_w_H                             = 1893,
//PCIE5_STRAP_BIF_GEN3_EN_w_A                             = 1894,
//PCIE5_STRAP_BIF_GEN3_EN_w_B                             = 1895,
//PCIE5_STRAP_BIF_GEN3_EN_w_C                             = 1896,
//PCIE5_STRAP_BIF_GEN3_EN_w_D                             = 1897,
//PCIE5_STRAP_BIF_GEN3_EN_w_E                             = 1898,
//PCIE5_STRAP_BIF_GEN3_EN_w_F                             = 1899,
//PCIE5_STRAP_BIF_GEN3_EN_w_G                             = 1900,
//PCIE5_STRAP_BIF_GEN3_EN_w_H                             = 1901,
//PCIE5_STRAP_BIF_GEN4_EN_w_A                             = 1902,
//PCIE5_STRAP_BIF_GEN4_EN_w_B                             = 1903,
//PCIE5_STRAP_BIF_GEN4_EN_w_C                             = 1904,
//PCIE5_STRAP_BIF_GEN4_EN_w_D                             = 1905,
//PCIE5_STRAP_BIF_GEN4_EN_w_E                             = 1906,
//PCIE5_STRAP_BIF_GEN4_EN_w_F                             = 1907,
//PCIE5_STRAP_BIF_GEN4_EN_w_G                             = 1908,
//PCIE5_STRAP_BIF_GEN4_EN_w_H                             = 1909,
//PCIE5_STRAP_BIF_LANE_NEGOTIATION                        = 1910,
//PCIE5_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1911,
//PCIE5_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1912,
//PCIE5_STRAP_BIF_LONG_yTSx_COUNT                         = 1913,
//PCIE5_STRAP_BIF_MED_yTSx_COUNT                          = 1914,
//PCIE5_STRAP_BIF_PHYSTATUS_SELECT                        = 1915,
//PCIE5_STRAP_BIF_SHORT_yTSx_COUNT                        = 1916,
//PCIE5_STRAP_BIF_SKIP_INTERVAL                           = 1917,
//PCIE5_STRAP_CHIP_BIF_MODE                               = 1918,
//PCIE6_PCIE0_PUB_SPARE_FUSES                             = 1919,
//PCIE6_PCIE0_WRITE_DISABLE                               = 1920,
//PCIE6_PCIE_EFUSE2_RESERVED_1                            = 1921,
//PCIE6_PCIE_EFUSE2_RESERVED_2                            = 1922,
//PCIE6_PCIE_EFUSE3_RESERVED_1                            = 1923,
//PCIE6_PCIE_EFUSE3_RESERVED_2                            = 1924,
//PCIE6_PCIE_EFUSE4_RESERVED                              = 1925,
//PCIE6_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1926,
//PCIE6_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1927,
//PCIE6_STRAP_BIF_DEVICE_ID_w                             = 1928,
//PCIE6_STRAP_BIF_GEN2_EN_w_A                             = 1929,
//PCIE6_STRAP_BIF_GEN2_EN_w_B                             = 1930,
//PCIE6_STRAP_BIF_GEN2_EN_w_C                             = 1931,
//PCIE6_STRAP_BIF_GEN2_EN_w_D                             = 1932,
//PCIE6_STRAP_BIF_GEN2_EN_w_E                             = 1933,
//PCIE6_STRAP_BIF_GEN2_EN_w_F                             = 1934,
//PCIE6_STRAP_BIF_GEN2_EN_w_G                             = 1935,
//PCIE6_STRAP_BIF_GEN2_EN_w_H                             = 1936,
//PCIE6_STRAP_BIF_GEN3_EN_w_A                             = 1937,
//PCIE6_STRAP_BIF_GEN3_EN_w_B                             = 1938,
//PCIE6_STRAP_BIF_GEN3_EN_w_C                             = 1939,
//PCIE6_STRAP_BIF_GEN3_EN_w_D                             = 1940,
//PCIE6_STRAP_BIF_GEN3_EN_w_E                             = 1941,
//PCIE6_STRAP_BIF_GEN3_EN_w_F                             = 1942,
//PCIE6_STRAP_BIF_GEN3_EN_w_G                             = 1943,
//PCIE6_STRAP_BIF_GEN3_EN_w_H                             = 1944,
//PCIE6_STRAP_BIF_GEN4_EN_w_A                             = 1945,
//PCIE6_STRAP_BIF_GEN4_EN_w_B                             = 1946,
//PCIE6_STRAP_BIF_GEN4_EN_w_C                             = 1947,
//PCIE6_STRAP_BIF_GEN4_EN_w_D                             = 1948,
//PCIE6_STRAP_BIF_GEN4_EN_w_E                             = 1949,
//PCIE6_STRAP_BIF_GEN4_EN_w_F                             = 1950,
//PCIE6_STRAP_BIF_GEN4_EN_w_G                             = 1951,
//PCIE6_STRAP_BIF_GEN4_EN_w_H                             = 1952,
//PCIE6_STRAP_BIF_LANE_NEGOTIATION                        = 1953,
//PCIE6_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1954,
//PCIE6_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1955,
//PCIE6_STRAP_BIF_LONG_yTSx_COUNT                         = 1956,
//PCIE6_STRAP_BIF_MED_yTSx_COUNT                          = 1957,
//PCIE6_STRAP_BIF_PHYSTATUS_SELECT                        = 1958,
//PCIE6_STRAP_BIF_SHORT_yTSx_COUNT                        = 1959,
//PCIE6_STRAP_BIF_SKIP_INTERVAL                           = 1960,
//PCIE6_STRAP_CHIP_BIF_MODE                               = 1961,
//PCIE7_PCIE0_PUB_SPARE_FUSES                             = 1962,
//PCIE7_PCIE0_WRITE_DISABLE                               = 1963,
//PCIE7_PCIE_EFUSE2_RESERVED_1                            = 1964,
//PCIE7_PCIE_EFUSE2_RESERVED_2                            = 1965,
//PCIE7_PCIE_EFUSE3_RESERVED_1                            = 1966,
//PCIE7_PCIE_EFUSE3_RESERVED_2                            = 1967,
//PCIE7_PCIE_EFUSE4_RESERVED                              = 1968,
//PCIE7_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 1969,
//PCIE7_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 1970,
//PCIE7_STRAP_BIF_DEVICE_ID_w                             = 1971,
//PCIE7_STRAP_BIF_GEN2_EN_w_A                             = 1972,
//PCIE7_STRAP_BIF_GEN2_EN_w_B                             = 1973,
//PCIE7_STRAP_BIF_GEN2_EN_w_C                             = 1974,
//PCIE7_STRAP_BIF_GEN2_EN_w_D                             = 1975,
//PCIE7_STRAP_BIF_GEN2_EN_w_E                             = 1976,
//PCIE7_STRAP_BIF_GEN2_EN_w_F                             = 1977,
//PCIE7_STRAP_BIF_GEN2_EN_w_G                             = 1978,
//PCIE7_STRAP_BIF_GEN2_EN_w_H                             = 1979,
//PCIE7_STRAP_BIF_GEN3_EN_w_A                             = 1980,
//PCIE7_STRAP_BIF_GEN3_EN_w_B                             = 1981,
//PCIE7_STRAP_BIF_GEN3_EN_w_C                             = 1982,
//PCIE7_STRAP_BIF_GEN3_EN_w_D                             = 1983,
//PCIE7_STRAP_BIF_GEN3_EN_w_E                             = 1984,
//PCIE7_STRAP_BIF_GEN3_EN_w_F                             = 1985,
//PCIE7_STRAP_BIF_GEN3_EN_w_G                             = 1986,
//PCIE7_STRAP_BIF_GEN3_EN_w_H                             = 1987,
//PCIE7_STRAP_BIF_GEN4_EN_w_A                             = 1988,
//PCIE7_STRAP_BIF_GEN4_EN_w_B                             = 1989,
//PCIE7_STRAP_BIF_GEN4_EN_w_C                             = 1990,
//PCIE7_STRAP_BIF_GEN4_EN_w_D                             = 1991,
//PCIE7_STRAP_BIF_GEN4_EN_w_E                             = 1992,
//PCIE7_STRAP_BIF_GEN4_EN_w_F                             = 1993,
//PCIE7_STRAP_BIF_GEN4_EN_w_G                             = 1994,
//PCIE7_STRAP_BIF_GEN4_EN_w_H                             = 1995,
//PCIE7_STRAP_BIF_LANE_NEGOTIATION                        = 1996,
//PCIE7_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 1997,
//PCIE7_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 1998,
//PCIE7_STRAP_BIF_LONG_yTSx_COUNT                         = 1999,
//PCIE7_STRAP_BIF_MED_yTSx_COUNT                          = 2000,
//PCIE7_STRAP_BIF_PHYSTATUS_SELECT                        = 2001,
//PCIE7_STRAP_BIF_SHORT_yTSx_COUNT                        = 2002,
//PCIE7_STRAP_BIF_SKIP_INTERVAL                           = 2003,
//PCIE7_STRAP_CHIP_BIF_MODE                               = 2004,
//PCIE8_PCIE8_GROUP0_DATA                                 = 2005,
//PCIE8_PCIE8_PUB_SPARE_FUSES                             = 2006,
//PCIE8_PCIE8_WRITE_DISABLE                               = 2007,
//PCIE8_PCIE_EFUSE2_RESERVED_1                            = 2008,
//PCIE8_PCIE_EFUSE2_RESERVED_2                            = 2009,
//PCIE8_PCIE_EFUSE3_RESERVED_1                            = 2010,
//PCIE8_PCIE_EFUSE3_RESERVED_2                            = 2011,
//PCIE8_PCIE_EFUSE4_RESERVED                              = 2012,
//PCIE8_STRAP_BIF_ALWAYS_USE_FAST_TXCLK                   = 2013,
//PCIE8_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w            = 2014,
//PCIE8_STRAP_BIF_DEVICE_ID_w                             = 2015,
//PCIE8_STRAP_BIF_GEN2_EN_w_A                             = 2016,
//PCIE8_STRAP_BIF_GEN2_EN_w_B                             = 2017,
//PCIE8_STRAP_BIF_GEN3_EN_w_A                             = 2018,
//PCIE8_STRAP_BIF_GEN3_EN_w_B                             = 2019,
//PCIE8_STRAP_BIF_GEN4_EN_w_A                             = 2020,
//PCIE8_STRAP_BIF_GEN4_EN_w_B                             = 2021,
//PCIE8_STRAP_BIF_LANE_NEGOTIATION                        = 2022,
//PCIE8_STRAP_BIF_LC_PMI_TO_L1_DIS                        = 2023,
//PCIE8_STRAP_BIF_LC_TX_SWING_OVERRIDE                    = 2024,
//PCIE8_STRAP_BIF_LONG_yTSx_COUNT                         = 2025,
//PCIE8_STRAP_BIF_MED_yTSx_COUNT                          = 2026,
//PCIE8_STRAP_BIF_PHYSTATUS_SELECT                        = 2027,
//PCIE8_STRAP_BIF_SHORT_yTSx_COUNT                        = 2028,
//PCIE8_STRAP_BIF_SKIP_INTERVAL                           = 2029,
//PCIE8_STRAP_CHIP_BIF_MODE                               = 2030,
//PCS0_CCD_PCS0_CCD_GROUP0_DATA                           = 2031,
//PCS0_PCS0_GROUP0_DATA                                   = 2032,
//PCS10_PCS10_GROUP0_DATA                                 = 2033,
//PCS11_PCS11_GROUP0_DATA                                 = 2034,
//PCS12_PCS12_GROUP0_DATA                                 = 2035,
//PCS13_PCS13_GROUP0_DATA                                 = 2036,
//PCS14_PCS14_GROUP0_DATA                                 = 2037,
//PCS15_PCS15_GROUP0_DATA                                 = 2038,
//PCS1_CCD_PCS1_CCD_GROUP0_DATA                           = 2039,
//PCS1_PCS1_GROUP0_DATA                                   = 2040,
//PCS20_PCS20_GROUP0_DATA                                 = 2041,
//PCS21_PCS21_GROUP0_DATA                                 = 2042,
//PCS22_PCS22_GROUP0_DATA                                 = 2043,
//PCS23_PCS23_GROUP0_DATA                                 = 2044,
//PCS24_PCS24_GROUP0_DATA                                 = 2045,
//PCS25_PCS25_GROUP0_DATA                                 = 2046,
//PCS26_PCS26_GROUP0_DATA                                 = 2047,
//PCS27_PCS27_GROUP0_DATA                                 = 2048,
//PCS28_PCS28_GROUP0_DATA                                 = 2049,
//PCS29_PCS29_GROUP0_DATA                                 = 2050,
//PCS2_PCS2_GROUP0_DATA                                   = 2051,
//PCS30_PCS30_GROUP0_DATA                                 = 2052,
//PCS31_PCS31_GROUP0_DATA                                 = 2053,
//PCS32_PCS32_GROUP0_DATA                                 = 2054,
//PCS33_PCS33_GROUP0_DATA                                 = 2055,
//PCS34_PCS34_GROUP0_DATA                                 = 2056,
//PCS35_PCS35_GROUP0_DATA                                 = 2057,
//PCS3_PCS3_GROUP0_DATA                                   = 2058,
//PCS4_PCS4_GROUP0_DATA                                   = 2059,
//PCS5_PCS5_GROUP0_DATA                                   = 2060,
//PCS6_PCS6_GROUP0_DATA                                   = 2061,
//PCS7_PCS7_GROUP0_DATA                                   = 2062,
//PCS8_PCS8_GROUP0_DATA                                   = 2063,
//PCS9_PCS9_GROUP0_DATA                                   = 2064,
//PCS_PCS_FUSES                                           = 2065,
//PCS_PCS_PUB_SPARE_FUSES                                 = 2066,
//PTDMA0_PTDMA0_GROUP0_DATA                               = 2067,
//PTDMA1_PTDMA1_GROUP0_DATA                               = 2068,
//PTDMA2_PTDMA2_GROUP0_DATA                               = 2069,
//PTDMA3_PTDMA3_GROUP0_DATA                               = 2070,
//PWR_CCD_LDO_CGR_DacOffset                               = 2071,
//PWR_CCD_LDO_CGR_DacRef                                  = 2072,
//PWR_CCD_LDO_CGT_DacOffset                               = 2073,
//PWR_CCD_LDO_CGT_DacRef                                  = 2074,
//PWR_CCD_LDO_CX0_0_DacOffset                             = 2075,
//PWR_CCD_LDO_CX0_0_DacRef                                = 2076,
//PWR_CCD_LDO_CX0_1_DacOffset                             = 2077,
//PWR_CCD_LDO_CX0_1_DacRef                                = 2078,
//PWR_CCD_LDO_CX0_2_DacOffset                             = 2079,
//PWR_CCD_LDO_CX0_2_DacRef                                = 2080,
//PWR_CCD_LDO_CX0_3_DacOffset                             = 2081,
//PWR_CCD_LDO_CX0_3_DacRef                                = 2082,
//PWR_CCD_LDO_CX1_0_DacOffset                             = 2083,
//PWR_CCD_LDO_CX1_0_DacRef                                = 2084,
//PWR_CCD_LDO_CX1_1_DacOffset                             = 2085,
//PWR_CCD_LDO_CX1_1_DacRef                                = 2086,
//PWR_CCD_LDO_CX1_2_DacOffset                             = 2087,
//PWR_CCD_LDO_CX1_2_DacRef                                = 2088,
//PWR_CCD_LDO_CX1_3_DacOffset                             = 2089,
//PWR_CCD_LDO_CX1_3_DacRef                                = 2090,
//PWR_CCD_LDO_PCS_DacOffset                               = 2091,
//PWR_CCD_LDO_PCS_DacRef                                  = 2092,
//PWR_CCD_LDO_SMU_DacOffset                               = 2093,
//PWR_CCD_LDO_SMU_DacRef                                  = 2094,
//PWR_CCD_LDO_Spare                                       = 2095,
//PWR_CCD_LDO_TIMING                                      = 2096,
//PWR_CCD_bg_slope_trim                                   = 2097,
//PWR_ODPR_0_CSR_Spare                                    = 2098,
//PWR_ODPR_0_res_ctl                                      = 2099,
//PWR_ODPR_1_CSR_Spare                                    = 2100,
//PWR_ODPR_1_res_ctl                                      = 2101,
//PWR_ODPR_Spare_0                                        = 2102,
//RESERVED_C_reserved_0                                   = 2103,
//RESERVED_N_reserved_0                                   = 2104,
//RESERVED_N_reserved_1                                   = 2105,
//RESERVED_N_reserved_2                                   = 2106,
//RESERVED_N_reserved_3                                   = 2107,
//SATA0_SATA0_GROUP0_DATA                                 = 2108,
//SATA0_SATA_WRITE_DISABLE                                = 2109,
//SATA0_sata_fuse                                         = 2110,
//SATA1_SATA1_GROUP0_DATA                                 = 2111,
//SATA1_SATA_WRITE_DISABLE                                = 2112,
//SATA1_sata_fuse                                         = 2113,
//SATA2_SATA2_GROUP0_DATA                                 = 2114,
//SATA2_SATA_WRITE_DISABLE                                = 2115,
//SATA2_sata_fuse                                         = 2116,
//SATA3_SATA3_GROUP0_DATA                                 = 2117,
//SATA3_SATA_WRITE_DISABLE                                = 2118,
//SATA3_sata_fuse                                         = 2119,
//SMS_UMC0_GROUP1_DATA                                    = 2120,
//SMS_UMC1_GROUP1_DATA                                    = 2121,
//SMS_UMC2_GROUP1_DATA                                    = 2122,
//SMS_UMC3_GROUP1_DATA                                    = 2123,
//SMS_UMC4_GROUP1_DATA                                    = 2124,
//SMS_UMC5_GROUP1_DATA                                    = 2125,
//SMS_UMC6_GROUP1_DATA                                    = 2126,
//SMS_UMC7_GROUP1_DATA                                    = 2127,
//SMUIO_COF_VID_PROG                                      = 2128,
//SMUIO_I2C_ENABLE                                        = 2129,
//SMUIO_IOD_LDO_TIMING                                    = 2130,
//SMUIO_IOD_LDO_spare                                     = 2131,
//SMUIO_IOD_bg_slope_trim                                 = 2132,
//SMUIO_LDO_DDR0_0_DacOffset                              = 2133,
//SMUIO_LDO_DDR0_0_DacRef                                 = 2134,
//SMUIO_LDO_DDR0_1_DacOffset                              = 2135,
//SMUIO_LDO_DDR0_1_DacRef                                 = 2136,
//SMUIO_LDO_DDR1_0_DacOffset                              = 2137,
//SMUIO_LDO_DDR1_0_DacRef                                 = 2138,
//SMUIO_LDO_DDR1_1_DacOffset                              = 2139,
//SMUIO_LDO_DDR1_1_DacRef                                 = 2140,
//SMUIO_LDO_GMI0_0_DacOffset                              = 2141,
//SMUIO_LDO_GMI0_0_DacRef                                 = 2142,
//SMUIO_LDO_GMI0_1_DacOffset                              = 2143,
//SMUIO_LDO_GMI0_1_DacRef                                 = 2144,
//SMUIO_LDO_GMI0_2_DacOffset                              = 2145,
//SMUIO_LDO_GMI0_2_DacRef                                 = 2146,
//SMUIO_LDO_GMI0_3_DacOffset                              = 2147,
//SMUIO_LDO_GMI0_3_DacRef                                 = 2148,
//SMUIO_LDO_GMI1_0_DacOffset                              = 2149,
//SMUIO_LDO_GMI1_0_DacRef                                 = 2150,
//SMUIO_LDO_GMI1_1_DacOffset                              = 2151,
//SMUIO_LDO_GMI1_1_DacRef                                 = 2152,
//SMUIO_LDO_GMI1_2_DacOffset                              = 2153,
//SMUIO_LDO_GMI1_2_DacRef                                 = 2154,
//SMUIO_LDO_GMI1_3_DacOffset                              = 2155,
//SMUIO_LDO_GMI1_3_DacRef                                 = 2156,
//SMUIO_LDO_GMI2_0_DacOffset                              = 2157,
//SMUIO_LDO_GMI2_0_DacRef                                 = 2158,
//SMUIO_LDO_GMI2_1_DacOffset                              = 2159,
//SMUIO_LDO_GMI2_1_DacRef                                 = 2160,
//SMUIO_LDO_GMI2_2_DacOffset                              = 2161,
//SMUIO_LDO_GMI2_2_DacRef                                 = 2162,
//SMUIO_LDO_GMI2_3_DacOffset                              = 2163,
//SMUIO_LDO_GMI2_3_DacRef                                 = 2164,
//SMUIO_LDO_GMI3_0_DacOffset                              = 2165,
//SMUIO_LDO_GMI3_0_DacRef                                 = 2166,
//SMUIO_LDO_GMI3_1_DacOffset                              = 2167,
//SMUIO_LDO_GMI3_1_DacRef                                 = 2168,
//SMUIO_LDO_GMI3_2_DacOffset                              = 2169,
//SMUIO_LDO_GMI3_2_DacRef                                 = 2170,
//SMUIO_LDO_GMI3_3_DacOffset                              = 2171,
//SMUIO_LDO_GMI3_3_DacRef                                 = 2172,
//SMUIO_LDO_USB0_DacOffset                                = 2173,
//SMUIO_LDO_USB0_DacRef                                   = 2174,
//SMUIO_LDO_USB1_DacOffset                                = 2175,
//SMUIO_LDO_USB1_DacRef                                   = 2176,
//SMUIO_MAX_VID                                           = 2177,
//SMUIO_MIN_VID                                           = 2178,
//SMUIO_ODPR_0_CSR_Spare                                  = 2179,
//SMUIO_ODPR_0_res_ctl                                    = 2180,
//SMUIO_ODPR_10_CSR_Spare                                 = 2181,
//SMUIO_ODPR_10_res_ctl                                   = 2182,
//SMUIO_ODPR_11_CSR_Spare                                 = 2183,
//SMUIO_ODPR_11_res_ctl                                   = 2184,
//SMUIO_ODPR_12_CSR_Spare                                 = 2185,
//SMUIO_ODPR_12_res_ctl                                   = 2186,
//SMUIO_ODPR_13_CSR_Spare                                 = 2187,
//SMUIO_ODPR_13_res_ctl                                   = 2188,
//SMUIO_ODPR_14_CSR_Spare                                 = 2189,
//SMUIO_ODPR_14_res_ctl                                   = 2190,
//SMUIO_ODPR_15_CSR_Spare                                 = 2191,
//SMUIO_ODPR_15_res_ctl                                   = 2192,
//SMUIO_ODPR_16_CSR_Spare                                 = 2193,
//SMUIO_ODPR_16_res_ctl                                   = 2194,
//SMUIO_ODPR_17_CSR_Spare                                 = 2195,
//SMUIO_ODPR_17_res_ctl                                   = 2196,
//SMUIO_ODPR_18_CSR_Spare                                 = 2197,
//SMUIO_ODPR_18_res_ctl                                   = 2198,
//SMUIO_ODPR_19_CSR_Spare                                 = 2199,
//SMUIO_ODPR_19_res_ctl                                   = 2200,
//SMUIO_ODPR_1_CSR_Spare                                  = 2201,
//SMUIO_ODPR_1_res_ctl                                    = 2202,
//SMUIO_ODPR_20_CSR_Spare                                 = 2203,
//SMUIO_ODPR_20_res_ctl                                   = 2204,
//SMUIO_ODPR_21_CSR_Spare                                 = 2205,
//SMUIO_ODPR_21_res_ctl                                   = 2206,
//SMUIO_ODPR_22_CSR_Spare                                 = 2207,
//SMUIO_ODPR_22_res_ctl                                   = 2208,
//SMUIO_ODPR_23_CSR_Spare                                 = 2209,
//SMUIO_ODPR_23_res_ctl                                   = 2210,
//SMUIO_ODPR_24_CSR_Spare                                 = 2211,
//SMUIO_ODPR_24_res_ctl                                   = 2212,
//SMUIO_ODPR_25_CSR_Spare                                 = 2213,
//SMUIO_ODPR_25_res_ctl                                   = 2214,
//SMUIO_ODPR_26_CSR_Spare                                 = 2215,
//SMUIO_ODPR_26_res_ctl                                   = 2216,
//SMUIO_ODPR_27_CSR_Spare                                 = 2217,
//SMUIO_ODPR_27_res_ctl                                   = 2218,
//SMUIO_ODPR_28_CSR_Spare                                 = 2219,
//SMUIO_ODPR_28_res_ctl                                   = 2220,
//SMUIO_ODPR_29_CSR_Spare                                 = 2221,
//SMUIO_ODPR_29_res_ctl                                   = 2222,
//SMUIO_ODPR_2_CSR_Spare                                  = 2223,
//SMUIO_ODPR_2_res_ctl                                    = 2224,
//SMUIO_ODPR_30_CSR_Spare                                 = 2225,
//SMUIO_ODPR_30_res_ctl                                   = 2226,
//SMUIO_ODPR_31_CSR_Spare                                 = 2227,
//SMUIO_ODPR_31_res_ctl                                   = 2228,
//SMUIO_ODPR_3_CSR_Spare                                  = 2229,
//SMUIO_ODPR_3_res_ctl                                    = 2230,
//SMUIO_ODPR_4_CSR_Spare                                  = 2231,
//SMUIO_ODPR_4_res_ctl                                    = 2232,
//SMUIO_ODPR_5_CSR_Spare                                  = 2233,
//SMUIO_ODPR_5_res_ctl                                    = 2234,
//SMUIO_ODPR_6_CSR_Spare                                  = 2235,
//SMUIO_ODPR_6_res_ctl                                    = 2236,
//SMUIO_ODPR_7_CSR_Spare                                  = 2237,
//SMUIO_ODPR_7_res_ctl                                    = 2238,
//SMUIO_ODPR_8_CSR_Spare                                  = 2239,
//SMUIO_ODPR_8_res_ctl                                    = 2240,
//SMUIO_ODPR_9_CSR_Spare                                  = 2241,
//SMUIO_ODPR_9_res_ctl                                    = 2242,
//SMUIO_QUICK_SLAM_ZERO_VID_EN                            = 2243,
//SMUIO_SMUIO_PUB_SPARE_FUSES                             = 2244,
//SMUIO_SMUIO_WRITE_DISABLE                               = 2245,
//SMUIO_STARTUP_VID_SVI0_EN                               = 2246,
//SMUIO_STARTUP_VID_SVI1_EN                               = 2247,
//SMUIO_SVI0_PLANE0_STARTUP_VID                           = 2248,
//SMUIO_SVI0_PLANE1_STARTUP_VID                           = 2249,
//SMUIO_SVI1_PLANE0_STARTUP_VID                           = 2250,
//SMUIO_SVI1_PLANE1_STARTUP_VID                           = 2251,
//SMUIO_SVT_DIS                                           = 2252,
//SMUIO_THERM_VID                                         = 2253,
//SYSTEMHUB0_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2254,
//SYSTEMHUB0_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2255,
//SYSTEMHUB0_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES      = 2256,
//SYSTEMHUB1_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2257,
//SYSTEMHUB1_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2258,
//SYSTEMHUB1_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES      = 2259,
//SYSTEMHUB2_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2260,
//SYSTEMHUB2_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2261,
//SYSTEMHUB2_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES      = 2262,
//SYSTEMHUB3_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2263,
//SYSTEMHUB3_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2264,
//SYSTEMHUB3_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES      = 2265,
//SYSTEMHUB4_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2266,
//SYSTEMHUB4_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2267,
//SYSTEMHUB4_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES      = 2268,
//SYSTEMHUB5_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2269,
//SYSTEMHUB5_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2270,
//SYSTEMHUB5_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES      = 2271,
//SYSTEMHUB6_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2272,
//SYSTEMHUB6_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2273,
//SYSTEMHUB6_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES      = 2274,
//SYSTEMHUB7_STRAP_SYSHUB_STRAP_HWREV_LSB2                = 2275,
//SYSTEMHUB7_STRAP_SYSHUB_STRAP_SWREV_LSB2                = 2276,
//SYSTEMHUB7_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES      = 2277,
//THM_CCD_FUSE_SB_FIXED_ERRATA                            = 2278,
//THM_CCD_FUSE_SB_IAI_DIS                                 = 2279,
//THM_CCD_FUSE_SB_RMI_DIS                                 = 2280,
//THM_CCD_FUSE_SB_TSI_DIS                                 = 2281,
//THM_CCD_FUSE_SMBUS_ARP_DIS                              = 2282,
//THM_CCD_FUSE_SMBUS_DIS                                  = 2283,
//THM_CCD_FUSE_SMBUS_FILTER_DIS                           = 2284,
//THM_CCD_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS                  = 2285,
//THM_CCD_FUSE_SMBUS_NOTIFY_ARP_MST_DIS                   = 2286,
//THM_CCD_FUSE_SMBUS_THM_OVERRIDE_DIS                     = 2287,
//THM_CCD_FUSE_SMBUS_THM_REG_ONLY                         = 2288,
//THM_CCD_FUSE_SMBUS_UDID_DEVICE_ID                       = 2289,
//THM_CCD_FUSE_SMBUS_UDID_MINOR_REV_ID                    = 2290,
//THM_CCD_FUSE_SMBUS_UDID_RAN_NUM_DIS                     = 2291,
//THM_CCD_FUSE_SMBUS_UDID_SUBSYS_ID                       = 2292,
//THM_CCD_FUSE_SMBUS_UDID_SUBSYS_VEN_ID                   = 2293,
//THM_CCD_FUSE_SMBUS_UDID_VENDOR_ID                       = 2294,
//THM_CCD_FUSE_TconAtValue                                = 2295,
//THM_CCD_FUSE_TconBtValue                                = 2296,
//THM_CCD_FUSE_TconCtOffsetValue0                         = 2297,
//THM_CCD_FUSE_TconCtValue                                = 2298,
//THM_CCD_FUSE_TconDtValue0                               = 2299,
//THM_CCD_FUSE_TconDtValue0l0                             = 2300,
//THM_CCD_FUSE_TconDtValue0l1                             = 2301,
//THM_CCD_FUSE_TconDtValue0l10                            = 2302,
//THM_CCD_FUSE_TconDtValue0l11                            = 2303,
//THM_CCD_FUSE_TconDtValue0l12                            = 2304,
//THM_CCD_FUSE_TconDtValue0l13                            = 2305,
//THM_CCD_FUSE_TconDtValue0l14                            = 2306,
//THM_CCD_FUSE_TconDtValue0l15                            = 2307,
//THM_CCD_FUSE_TconDtValue0l2                             = 2308,
//THM_CCD_FUSE_TconDtValue0l3                             = 2309,
//THM_CCD_FUSE_TconDtValue0l4                             = 2310,
//THM_CCD_FUSE_TconDtValue0l5                             = 2311,
//THM_CCD_FUSE_TconDtValue0l6                             = 2312,
//THM_CCD_FUSE_TconDtValue0l7                             = 2313,
//THM_CCD_FUSE_TconDtValue0l8                             = 2314,
//THM_CCD_FUSE_TconDtValue0l9                             = 2315,
//THM_CCD_FUSE_TconDtValue0r0                             = 2316,
//THM_CCD_FUSE_TconDtValue0r1                             = 2317,
//THM_CCD_FUSE_TconDtValue0r10                            = 2318,
//THM_CCD_FUSE_TconDtValue0r11                            = 2319,
//THM_CCD_FUSE_TconDtValue0r12                            = 2320,
//THM_CCD_FUSE_TconDtValue0r13                            = 2321,
//THM_CCD_FUSE_TconDtValue0r14                            = 2322,
//THM_CCD_FUSE_TconDtValue0r15                            = 2323,
//THM_CCD_FUSE_TconDtValue0r2                             = 2324,
//THM_CCD_FUSE_TconDtValue0r3                             = 2325,
//THM_CCD_FUSE_TconDtValue0r4                             = 2326,
//THM_CCD_FUSE_TconDtValue0r5                             = 2327,
//THM_CCD_FUSE_TconDtValue0r6                             = 2328,
//THM_CCD_FUSE_TconDtValue0r7                             = 2329,
//THM_CCD_FUSE_TconDtValue0r8                             = 2330,
//THM_CCD_FUSE_TconDtValue0r9                             = 2331,
//THM_CCD_FUSE_TconKValue                                 = 2332,
//THM_CCD_FUSE_TconTmpAdjLoRes                            = 2333,
//THM_CCD_FUSE_TconUseSecondary                           = 2334,
//THM_CCD_FUSE_TconZtValue                                = 2335,
//THM_CCD_FUSE_ThermTripEn                                = 2336,
//THM_CCD_FUSE_ThermTripLimit                             = 2337,
//THM_CCD_FUSE_TmonBGAdj0                                 = 2338,
//THM_CCD_FUSE_TmonClkDiv                                 = 2339,
//THM_CCD_FUSE_TmonForceMaxAcq                            = 2340,
//THM_CCD_FUSE_TmonNumAcq                                 = 2341,
//THM_CCD_FUSE_TmonReCalibEn                              = 2342,
//THM_CCD_RDIL0_PRESENT                                   = 2343,
//THM_CCD_RDIR0_PRESENT                                   = 2344,
//THM_CCD_THM_CCD_PUB_SPARE_FUSES                         = 2345,
//THM_CCD_THM_CCD_WRITE_DISABLE                           = 2346,
//THM_CCD_TMON_BGADJ_FUSE_SEL                             = 2347,
//THM_CCD_TMON_COEFF_SOURCE                               = 2348,
//THM_CCD_TMON_CONFIG_SOURCE                              = 2349,
//THM_FUSE_HtcDis                                         = 2350,
//THM_FUSE_HtcHystLmt                                     = 2351,
//THM_FUSE_HtcMsrLock                                     = 2352,
//THM_FUSE_HtcTmpLmt                                      = 2353,
//THM_FUSE_SB_FIXED_ERRATA                                = 2354,
//THM_FUSE_SB_IAI_DIS                                     = 2355,
//THM_FUSE_SB_RMI_DIS                                     = 2356,
//THM_FUSE_SB_TSI_DIS                                     = 2357,
//THM_FUSE_SMBUS_ARP_DIS                                  = 2358,
//THM_FUSE_SMBUS_DIS                                      = 2359,
//THM_FUSE_SMBUS_FILTER_DIS                               = 2360,
//THM_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS                      = 2361,
//THM_FUSE_SMBUS_NOTIFY_ARP_MST_DIS                       = 2362,
//THM_FUSE_SMBUS_THM_OVERRIDE_DIS                         = 2363,
//THM_FUSE_SMBUS_THM_REG_ONLY                             = 2364,
//THM_FUSE_SMBUS_UDID_DEVICE_ID                           = 2365,
//THM_FUSE_SMBUS_UDID_MINOR_REV_ID                        = 2366,
//THM_FUSE_SMBUS_UDID_RAN_NUM_DIS                         = 2367,
//THM_FUSE_SMBUS_UDID_SUBSYS_ID                           = 2368,
//THM_FUSE_SMBUS_UDID_SUBSYS_VEN_ID                       = 2369,
//THM_FUSE_SMBUS_UDID_VENDOR_ID                           = 2370,
//THM_FUSE_TconAtValue                                    = 2371,
//THM_FUSE_TconBtValue                                    = 2372,
//THM_FUSE_TconCtOffsetValue0                             = 2373,
//THM_FUSE_TconCtOffsetValue1                             = 2374,
//THM_FUSE_TconCtValue                                    = 2375,
//THM_FUSE_TconDtValue0                                   = 2376,
//THM_FUSE_TconDtValue0l0                                 = 2377,
//THM_FUSE_TconDtValue0l1                                 = 2378,
//THM_FUSE_TconDtValue0l10                                = 2379,
//THM_FUSE_TconDtValue0l11                                = 2380,
//THM_FUSE_TconDtValue0l12                                = 2381,
//THM_FUSE_TconDtValue0l13                                = 2382,
//THM_FUSE_TconDtValue0l14                                = 2383,
//THM_FUSE_TconDtValue0l15                                = 2384,
//THM_FUSE_TconDtValue0l2                                 = 2385,
//THM_FUSE_TconDtValue0l3                                 = 2386,
//THM_FUSE_TconDtValue0l4                                 = 2387,
//THM_FUSE_TconDtValue0l5                                 = 2388,
//THM_FUSE_TconDtValue0l6                                 = 2389,
//THM_FUSE_TconDtValue0l7                                 = 2390,
//THM_FUSE_TconDtValue0l8                                 = 2391,
//THM_FUSE_TconDtValue0l9                                 = 2392,
//THM_FUSE_TconDtValue0r0                                 = 2393,
//THM_FUSE_TconDtValue0r1                                 = 2394,
//THM_FUSE_TconDtValue0r10                                = 2395,
//THM_FUSE_TconDtValue0r11                                = 2396,
//THM_FUSE_TconDtValue0r12                                = 2397,
//THM_FUSE_TconDtValue0r13                                = 2398,
//THM_FUSE_TconDtValue0r14                                = 2399,
//THM_FUSE_TconDtValue0r15                                = 2400,
//THM_FUSE_TconDtValue0r2                                 = 2401,
//THM_FUSE_TconDtValue0r3                                 = 2402,
//THM_FUSE_TconDtValue0r4                                 = 2403,
//THM_FUSE_TconDtValue0r5                                 = 2404,
//THM_FUSE_TconDtValue0r6                                 = 2405,
//THM_FUSE_TconDtValue0r7                                 = 2406,
//THM_FUSE_TconDtValue0r8                                 = 2407,
//THM_FUSE_TconDtValue0r9                                 = 2408,
//THM_FUSE_TconDtValue1                                   = 2409,
//THM_FUSE_TconDtValue1l0                                 = 2410,
//THM_FUSE_TconDtValue1l1                                 = 2411,
//THM_FUSE_TconDtValue1l10                                = 2412,
//THM_FUSE_TconDtValue1l11                                = 2413,
//THM_FUSE_TconDtValue1l12                                = 2414,
//THM_FUSE_TconDtValue1l13                                = 2415,
//THM_FUSE_TconDtValue1l14                                = 2416,
//THM_FUSE_TconDtValue1l15                                = 2417,
//THM_FUSE_TconDtValue1l2                                 = 2418,
//THM_FUSE_TconDtValue1l3                                 = 2419,
//THM_FUSE_TconDtValue1l4                                 = 2420,
//THM_FUSE_TconDtValue1l5                                 = 2421,
//THM_FUSE_TconDtValue1l6                                 = 2422,
//THM_FUSE_TconDtValue1l7                                 = 2423,
//THM_FUSE_TconDtValue1l8                                 = 2424,
//THM_FUSE_TconDtValue1l9                                 = 2425,
//THM_FUSE_TconDtValue1r0                                 = 2426,
//THM_FUSE_TconDtValue1r1                                 = 2427,
//THM_FUSE_TconDtValue1r10                                = 2428,
//THM_FUSE_TconDtValue1r11                                = 2429,
//THM_FUSE_TconDtValue1r12                                = 2430,
//THM_FUSE_TconDtValue1r13                                = 2431,
//THM_FUSE_TconDtValue1r14                                = 2432,
//THM_FUSE_TconDtValue1r15                                = 2433,
//THM_FUSE_TconDtValue1r2                                 = 2434,
//THM_FUSE_TconDtValue1r3                                 = 2435,
//THM_FUSE_TconDtValue1r4                                 = 2436,
//THM_FUSE_TconDtValue1r5                                 = 2437,
//THM_FUSE_TconDtValue1r6                                 = 2438,
//THM_FUSE_TconDtValue1r7                                 = 2439,
//THM_FUSE_TconDtValue1r8                                 = 2440,
//THM_FUSE_TconDtValue1r9                                 = 2441,
//THM_FUSE_TconKValue                                     = 2442,
//THM_FUSE_TconTmpAdjLoRes                                = 2443,
//THM_FUSE_TconUseSecondary                               = 2444,
//THM_FUSE_TconZtValue                                    = 2445,
//THM_FUSE_ThermTripEn                                    = 2446,
//THM_FUSE_ThermTripLimit                                 = 2447,
//THM_FUSE_TmonBGAdj0                                     = 2448,
//THM_FUSE_TmonBGAdj1                                     = 2449,
//THM_FUSE_TmonClkDiv                                     = 2450,
//THM_FUSE_TmonForceMaxAcq                                = 2451,
//THM_FUSE_TmonNumAcq                                     = 2452,
//THM_FUSE_TmonReCalibEn                                  = 2453,
//THM_RDIL0_PRESENT                                       = 2454,
//THM_RDIL1_PRESENT                                       = 2455,
//THM_RDIR0_PRESENT                                       = 2456,
//THM_RDIR1_PRESENT                                       = 2457,
//THM_THM_PUB_SPARE_FUSES                                 = 2458,
//THM_THM_WRITE_DISABLE                                   = 2459,
//THM_TMON_BGADJ_FUSE_SEL                                 = 2460,
//THM_TMON_COEFF_SOURCE                                   = 2461,
//THM_TMON_CONFIG_SOURCE                                  = 2462,
//UMC0_FUSE_DdrMaxRate                                    = 2463,
//UMC0_FUSE_DdrMaxRateEnf                                 = 2464,
//UMC0_FUSE_DramTypeDis                                   = 2465,
//UMC0_FUSE_EccDis                                        = 2466,
//UMC0_FUSE_EncryptionDis                                 = 2467,
//UMC0_FUSE_MemChanDis                                    = 2468,
//UMC0_FUSE_RegDimmDis                                    = 2469,
//UMC0_FUSE_Spare_UMC                                     = 2470,
//UMC0_UMC_PUB_SPARE_FUSES                                = 2471,
//UMC1_FUSE_DdrMaxRate                                    = 2472,
//UMC1_FUSE_DdrMaxRateEnf                                 = 2473,
//UMC1_FUSE_DramTypeDis                                   = 2474,
//UMC1_FUSE_EccDis                                        = 2475,
//UMC1_FUSE_EncryptionDis                                 = 2476,
//UMC1_FUSE_MemChanDis                                    = 2477,
//UMC1_FUSE_RegDimmDis                                    = 2478,
//UMC1_FUSE_Spare_UMC                                     = 2479,
//UMC1_UMC_PUB_SPARE_FUSES                                = 2480,
//UMC2_FUSE_DdrMaxRate                                    = 2481,
//UMC2_FUSE_DdrMaxRateEnf                                 = 2482,
//UMC2_FUSE_DramTypeDis                                   = 2483,
//UMC2_FUSE_EccDis                                        = 2484,
//UMC2_FUSE_EncryptionDis                                 = 2485,
//UMC2_FUSE_MemChanDis                                    = 2486,
//UMC2_FUSE_RegDimmDis                                    = 2487,
//UMC2_FUSE_Spare_UMC                                     = 2488,
//UMC2_UMC_PUB_SPARE_FUSES                                = 2489,
//UMC3_FUSE_DdrMaxRate                                    = 2490,
//UMC3_FUSE_DdrMaxRateEnf                                 = 2491,
//UMC3_FUSE_DramTypeDis                                   = 2492,
//UMC3_FUSE_EccDis                                        = 2493,
//UMC3_FUSE_EncryptionDis                                 = 2494,
//UMC3_FUSE_MemChanDis                                    = 2495,
//UMC3_FUSE_RegDimmDis                                    = 2496,
//UMC3_FUSE_Spare_UMC                                     = 2497,
//UMC3_UMC_PUB_SPARE_FUSES                                = 2498,
//UMC4_FUSE_DdrMaxRate                                    = 2499,
//UMC4_FUSE_DdrMaxRateEnf                                 = 2500,
//UMC4_FUSE_DramTypeDis                                   = 2501,
//UMC4_FUSE_EccDis                                        = 2502,
//UMC4_FUSE_EncryptionDis                                 = 2503,
//UMC4_FUSE_MemChanDis                                    = 2504,
//UMC4_FUSE_RegDimmDis                                    = 2505,
//UMC4_FUSE_Spare_UMC                                     = 2506,
//UMC4_UMC_PUB_SPARE_FUSES                                = 2507,
//UMC5_FUSE_DdrMaxRate                                    = 2508,
//UMC5_FUSE_DdrMaxRateEnf                                 = 2509,
//UMC5_FUSE_DramTypeDis                                   = 2510,
//UMC5_FUSE_EccDis                                        = 2511,
//UMC5_FUSE_EncryptionDis                                 = 2512,
//UMC5_FUSE_MemChanDis                                    = 2513,
//UMC5_FUSE_RegDimmDis                                    = 2514,
//UMC5_FUSE_Spare_UMC                                     = 2515,
//UMC5_UMC_PUB_SPARE_FUSES                                = 2516,
//UMC6_FUSE_DdrMaxRate                                    = 2517,
//UMC6_FUSE_DdrMaxRateEnf                                 = 2518,
//UMC6_FUSE_DramTypeDis                                   = 2519,
//UMC6_FUSE_EccDis                                        = 2520,
//UMC6_FUSE_EncryptionDis                                 = 2521,
//UMC6_FUSE_MemChanDis                                    = 2522,
//UMC6_FUSE_RegDimmDis                                    = 2523,
//UMC6_FUSE_Spare_UMC                                     = 2524,
//UMC6_UMC_PUB_SPARE_FUSES                                = 2525,
//UMC7_FUSE_DdrMaxRate                                    = 2526,
//UMC7_FUSE_DdrMaxRateEnf                                 = 2527,
//UMC7_FUSE_DramTypeDis                                   = 2528,
//UMC7_FUSE_EccDis                                        = 2529,
//UMC7_FUSE_EncryptionDis                                 = 2530,
//UMC7_FUSE_MemChanDis                                    = 2531,
//UMC7_FUSE_RegDimmDis                                    = 2532,
//UMC7_FUSE_Spare_UMC                                     = 2533,
//UMC7_UMC_PUB_SPARE_FUSES                                = 2534,
//USB0_USB0_GROUP0_DATA                                   = 2535,
//USB0_USB_0_WRITE_DISABLE                                = 2536,
//USB0_usb_fuse                                           = 2537,
//USB1_USB1_GROUP0_DATA                                   = 2538,
//USB1_USB_0_WRITE_DISABLE                                = 2539,
//USB1_usb_fuse                                           = 2540,
//VHC_FUSE_REPAIR_Spare_Repair                            = 2541,
//VHC_RESERVED_N_reserved_0                               = 2542,
//VHC_RESERVED_N_reserved_1                               = 2543,
//VHC_RESERVED_N_reserved_2                               = 2544,
//WAFL_PCS_EFUSE1_HWINIT_DisableFunc                      = 2545,
//WAFL_PCS_EFUSE1_HWINIT_ReadySerBypass                   = 2546,
//WAFL_PCS_EFUSE1_HWINIT_WriteDis                         = 2547,
//WAFL_PCS_FUSE_ANALOG_0                                  = 2548,
//WAFL_PCS_FUSE_ANALOG_1                                  = 2549,
//WAFL_PCS_FUSE_ANALOG_10                                 = 2550,
//WAFL_PCS_FUSE_ANALOG_11                                 = 2551,
//WAFL_PCS_FUSE_ANALOG_12                                 = 2552,
//WAFL_PCS_FUSE_ANALOG_13                                 = 2553,
//WAFL_PCS_FUSE_ANALOG_14                                 = 2554,
//WAFL_PCS_FUSE_ANALOG_15                                 = 2555,
//WAFL_PCS_FUSE_ANALOG_16                                 = 2556,
//WAFL_PCS_FUSE_ANALOG_17                                 = 2557,
//WAFL_PCS_FUSE_ANALOG_18                                 = 2558,
//WAFL_PCS_FUSE_ANALOG_19                                 = 2559,
//WAFL_PCS_FUSE_ANALOG_2                                  = 2560,
//WAFL_PCS_FUSE_ANALOG_20                                 = 2561,
//WAFL_PCS_FUSE_ANALOG_21                                 = 2562,
//WAFL_PCS_FUSE_ANALOG_22                                 = 2563,
//WAFL_PCS_FUSE_ANALOG_23                                 = 2564,
//WAFL_PCS_FUSE_ANALOG_24                                 = 2565,
//WAFL_PCS_FUSE_ANALOG_25                                 = 2566,
//WAFL_PCS_FUSE_ANALOG_26                                 = 2567,
//WAFL_PCS_FUSE_ANALOG_27                                 = 2568,
//WAFL_PCS_FUSE_ANALOG_28                                 = 2569,
//WAFL_PCS_FUSE_ANALOG_29                                 = 2570,
//WAFL_PCS_FUSE_ANALOG_3                                  = 2571,
//WAFL_PCS_FUSE_ANALOG_30                                 = 2572,
//WAFL_PCS_FUSE_ANALOG_31                                 = 2573,
//WAFL_PCS_FUSE_ANALOG_4                                  = 2574,
//WAFL_PCS_FUSE_ANALOG_5                                  = 2575,
//WAFL_PCS_FUSE_ANALOG_6                                  = 2576,
//WAFL_PCS_FUSE_ANALOG_7                                  = 2577,
//WAFL_PCS_FUSE_ANALOG_8                                  = 2578,
//WAFL_PCS_FUSE_ANALOG_9                                  = 2579,
//WAFL_PCS_FUSE_PHY0_seq_fuse0                            = 2580,
//WAFL_PCS_FUSE_PHY0_seq_fuse10                           = 2581,
//WAFL_PCS_FUSE_PHY0_seq_fuse2                            = 2582,
//WAFL_PCS_FUSE_PHY0_seq_fuse4                            = 2583,
//WAFL_PCS_FUSE_PHY0_seq_fuse6                            = 2584,
//WAFL_PCS_FUSE_PHY0_seq_fuse8                            = 2585,
//WAFL_PCS_FUSE_PHYN_seq_fuse0                            = 2586,
//WAFL_PCS_FUSE_PHYN_seq_fuse10                           = 2587,
//WAFL_PCS_FUSE_PHYN_seq_fuse2                            = 2588,
//WAFL_PCS_FUSE_PHYN_seq_fuse4                            = 2589,
//WAFL_PCS_FUSE_PHYN_seq_fuse6                            = 2590,
//WAFL_PCS_FUSE_PHYN_seq_fuse8                            = 2591,
//WAFL_PCS_GOPX1_PCS_EFUSE1                               = 2592,
//WAFL_PCS_GOPX1_PCS_HINIT_HWinitComplete                 = 2593,
//WAFL_PCS_PCS_HINIT                                      = 2594,
  END_OF_ENUM_TABLE                                       = 0xFFFFF,
};

///
/// Fuse table containing information to read each fuse
///
static AMD_FUSE AllFuses [] = {
#ifdef AUDIO_AZ_AUDIO_AZ_GROUP0_DATA
#define
  {
    ///< AUDIO_AZ_AUDIO_AZ_GROUP0_DATA0
    0,
    64,
    0,
    0x5D704,
  },
#endif

#ifdef CCX_BYPASSFUSE
#define
  {
    ///< CCX_BYPASSFUSE1
    1,
    1,
    22,
    0x1882,
  },
#endif

#ifdef CCX_BisiEn
#define
  {
    ///< CCX_BisiEn2
    2,
    1,
    5,
    0x1854,
  },
#endif

#ifdef CCX_BistEn
#define
  {
    ///< CCX_BistEn3
    3,
    1,
    4,
    0x1854,
  },
#endif

#ifdef CCX_BistExecCfg
#define
  {
    ///< CCX_BistExecCfg4
    4,
    2,
    23,
    0x185A,
  },
#endif

#ifdef CCX_BypassL3Fuse
#define
  {
    ///< CCX_BypassL3Fuse5
    5,
    1,
    21,
    0x185A,
  },
#endif

#ifdef CCX_CCX0CoreID0
#define
  {
    ///< CCX_CCX0CoreID06
    6,
    2,
    29,
    0x18D7,
  },
#endif

#ifdef CCX_CCX0CoreID1
#define
  {
    ///< CCX_CCX0CoreID17
    7,
    2,
    8,
    0x18D5,
  },
#endif

#ifdef CCX_CCX0CoreID10
#define
  {
    ///< CCX_CCX0CoreID108
    8,
    2,
    8,
    0x18ED,
  },
#endif

#ifdef CCX_CCX0CoreID11
#define
  {
    ///< CCX_CCX0CoreID119
    9,
    2,
    19,
    0x18EA,
  },
#endif

#ifdef CCX_CCX0CoreID2
#define
  {
    ///< CCX_CCX0CoreID210
    10,
    2,
    19,
    0x18D2,
  },
#endif

#ifdef CCX_CCX0CoreID3
#define
  {
    ///< CCX_CCX0CoreID311
    11,
    2,
    29,
    0x18DF,
  },
#endif

#ifdef CCX_CCX0CoreID4
#define
  {
    ///< CCX_CCX0CoreID412
    12,
    2,
    8,
    0x18DD,
  },
#endif

#ifdef CCX_CCX0CoreID5
#define
  {
    ///< CCX_CCX0CoreID513
    13,
    2,
    19,
    0x18DA,
  },
#endif

#ifdef CCX_CCX0CoreID6
#define
  {
    ///< CCX_CCX0CoreID614
    14,
    2,
    29,
    0x18E7,
  },
#endif

#ifdef CCX_CCX0CoreID7
#define
  {
    ///< CCX_CCX0CoreID715
    15,
    2,
    8,
    0x18E5,
  },
#endif

#ifdef CCX_CCX0CoreID8
#define
  {
    ///< CCX_CCX0CoreID816
    16,
    2,
    19,
    0x18E2,
  },
#endif

#ifdef CCX_CCX0CoreID9
#define
  {
    ///< CCX_CCX0CoreID917
    17,
    2,
    29,
    0x18EF,
  },
#endif

#ifdef CCX_CCX0L1Repair0
#define
  {
    ///< CCX_CCX0L1Repair018
    18,
    1,
    28,
    0x18D7,
  },
#endif

#ifdef CCX_CCX0L1Repair1
#define
  {
    ///< CCX_CCX0L1Repair119
    19,
    1,
    7,
    0x18D4,
  },
#endif

#ifdef CCX_CCX0L1Repair10
#define
  {
    ///< CCX_CCX0L1Repair1020
    20,
    1,
    7,
    0x18EC,
  },
#endif

#ifdef CCX_CCX0L1Repair11
#define
  {
    ///< CCX_CCX0L1Repair1121
    21,
    1,
    18,
    0x18EA,
  },
#endif

#ifdef CCX_CCX0L1Repair2
#define
  {
    ///< CCX_CCX0L1Repair222
    22,
    1,
    18,
    0x18D2,
  },
#endif

#ifdef CCX_CCX0L1Repair3
#define
  {
    ///< CCX_CCX0L1Repair323
    23,
    1,
    28,
    0x18DF,
  },
#endif

#ifdef CCX_CCX0L1Repair4
#define
  {
    ///< CCX_CCX0L1Repair424
    24,
    1,
    7,
    0x18DC,
  },
#endif

#ifdef CCX_CCX0L1Repair5
#define
  {
    ///< CCX_CCX0L1Repair525
    25,
    1,
    18,
    0x18DA,
  },
#endif

#ifdef CCX_CCX0L1Repair6
#define
  {
    ///< CCX_CCX0L1Repair626
    26,
    1,
    28,
    0x18E7,
  },
#endif

#ifdef CCX_CCX0L1Repair7
#define
  {
    ///< CCX_CCX0L1Repair727
    27,
    1,
    7,
    0x18E4,
  },
#endif

#ifdef CCX_CCX0L1Repair8
#define
  {
    ///< CCX_CCX0L1Repair828
    28,
    1,
    18,
    0x18E2,
  },
#endif

#ifdef CCX_CCX0L1Repair9
#define
  {
    ///< CCX_CCX0L1Repair929
    29,
    1,
    28,
    0x18EF,
  },
#endif

#ifdef CCX_CCX0L2Repair0
#define
  {
    ///< CCX_CCX0L2Repair030
    30,
    1,
    27,
    0x18D7,
  },
#endif

#ifdef CCX_CCX0L2Repair1
#define
  {
    ///< CCX_CCX0L2Repair131
    31,
    1,
    6,
    0x18D4,
  },
#endif

#ifdef CCX_CCX0L2Repair10
#define
  {
    ///< CCX_CCX0L2Repair1032
    32,
    1,
    6,
    0x18EC,
  },
#endif

#ifdef CCX_CCX0L2Repair11
#define
  {
    ///< CCX_CCX0L2Repair1133
    33,
    1,
    17,
    0x18EA,
  },
#endif

#ifdef CCX_CCX0L2Repair2
#define
  {
    ///< CCX_CCX0L2Repair234
    34,
    1,
    17,
    0x18D2,
  },
#endif

#ifdef CCX_CCX0L2Repair3
#define
  {
    ///< CCX_CCX0L2Repair335
    35,
    1,
    27,
    0x18DF,
  },
#endif

#ifdef CCX_CCX0L2Repair4
#define
  {
    ///< CCX_CCX0L2Repair436
    36,
    1,
    6,
    0x18DC,
  },
#endif

#ifdef CCX_CCX0L2Repair5
#define
  {
    ///< CCX_CCX0L2Repair537
    37,
    1,
    17,
    0x18DA,
  },
#endif

#ifdef CCX_CCX0L2Repair6
#define
  {
    ///< CCX_CCX0L2Repair638
    38,
    1,
    27,
    0x18E7,
  },
#endif

#ifdef CCX_CCX0L2Repair7
#define
  {
    ///< CCX_CCX0L2Repair739
    39,
    1,
    6,
    0x18E4,
  },
#endif

#ifdef CCX_CCX0L2Repair8
#define
  {
    ///< CCX_CCX0L2Repair840
    40,
    1,
    17,
    0x18E2,
  },
#endif

#ifdef CCX_CCX0L2Repair9
#define
  {
    ///< CCX_CCX0L2Repair941
    41,
    1,
    27,
    0x18EF,
  },
#endif

#ifdef CCX_CCX0L3M0EvenBankDis
#define
  {
    ///< CCX_CCX0L3M0EvenBankDis42
    42,
    3,
    12,
    0x1919,
  },
#endif

#ifdef CCX_CCX0L3M0OddBankDis
#define
  {
    ///< CCX_CCX0L3M0OddBankDis43
    43,
    3,
    0,
    0x1918,
  },
#endif

#ifdef CCX_CCX0L3M1EvenBankDis
#define
  {
    ///< CCX_CCX0L3M1EvenBankDis44
    44,
    3,
    15,
    0x1919,
  },
#endif

#ifdef CCX_CCX0L3M1OddBankDis
#define
  {
    ///< CCX_CCX0L3M1OddBankDis45
    45,
    3,
    3,
    0x1918,
  },
#endif

#ifdef CCX_CCX0L3M2EvenBankDis
#define
  {
    ///< CCX_CCX0L3M2EvenBankDis46
    46,
    3,
    18,
    0x191A,
  },
#endif

#ifdef CCX_CCX0L3M2OddBankDis
#define
  {
    ///< CCX_CCX0L3M2OddBankDis47
    47,
    3,
    6,
    0x1918,
  },
#endif

#ifdef CCX_CCX0L3M3EvenBankDis
#define
  {
    ///< CCX_CCX0L3M3EvenBankDis48
    48,
    3,
    21,
    0x191A,
  },
#endif

#ifdef CCX_CCX0L3M3OddBankDis
#define
  {
    ///< CCX_CCX0L3M3OddBankDis49
    49,
    3,
    9,
    0x1919,
  },
#endif

#ifdef CCX_CCX0L3MReserved
#define
  {
    ///< CCX_CCX0L3MReserved50
    50,
    8,
    24,
    0x191B,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl2RladrCode
#define
  {
    ///< CCX_CCX0L3PllFllCtl2RladrCode51
    51,
    9,
    7,
    0x1840,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4BCoarse
#define
  {
    ///< CCX_CCX0L3PllFllCtl4BCoarse52
    52,
    1,
    19,
    0x1842,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4BOffsetA
#define
  {
    ///< CCX_CCX0L3PllFllCtl4BOffsetA53
    53,
    4,
    28,
    0x1843,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4BOffsetB
#define
  {
    ///< CCX_CCX0L3PllFllCtl4BOffsetB54
    54,
    4,
    24,
    0x1843,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4BStep
#define
  {
    ///< CCX_CCX0L3PllFllCtl4BStep55
    55,
    4,
    20,
    0x1842,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4DisVroCap
#define
  {
    ///< CCX_CCX0L3PllFllCtl4DisVroCap56
    56,
    1,
    18,
    0x1842,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4Rsvd31_25
#define
  {
    ///< CCX_CCX0L3PllFllCtl4Rsvd31_2557
    57,
    7,
    0,
    0x1840,
  },
#endif

#ifdef CCX_CCX0L3PllFllCtl4V2CcGain
#define
  {
    ///< CCX_CCX0L3PllFllCtl4V2CcGain58
    58,
    2,
    16,
    0x1842,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses0
#define
  {
    ///< CCX_CCX0L3Repair0Fuses059
    59,
    16,
    0,
    0x191C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses1
#define
  {
    ///< CCX_CCX0L3Repair0Fuses160
    60,
    16,
    0,
    0x1920,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses10
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1061
    61,
    16,
    0,
    0x1944,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses11
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1162
    62,
    16,
    0,
    0x1948,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses12
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1263
    63,
    16,
    0,
    0x194C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses13
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1364
    64,
    16,
    0,
    0x1950,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses14
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1465
    65,
    16,
    0,
    0x1954,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses15
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1566
    66,
    16,
    0,
    0x1958,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses16
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1667
    67,
    16,
    0,
    0x195C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses17
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1768
    68,
    16,
    0,
    0x1960,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses18
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1869
    69,
    16,
    0,
    0x1964,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses19
#define
  {
    ///< CCX_CCX0L3Repair0Fuses1970
    70,
    16,
    0,
    0x1968,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses2
#define
  {
    ///< CCX_CCX0L3Repair0Fuses271
    71,
    16,
    0,
    0x1924,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses20
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2072
    72,
    16,
    0,
    0x196C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses21
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2173
    73,
    16,
    0,
    0x1970,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses22
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2274
    74,
    16,
    0,
    0x1974,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses23
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2375
    75,
    16,
    0,
    0x1978,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses24
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2476
    76,
    16,
    0,
    0x197C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses25
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2577
    77,
    16,
    0,
    0x1980,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses26
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2678
    78,
    16,
    0,
    0x1984,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses27
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2779
    79,
    16,
    0,
    0x1988,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses28
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2880
    80,
    16,
    0,
    0x198C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses29
#define
  {
    ///< CCX_CCX0L3Repair0Fuses2981
    81,
    16,
    0,
    0x1990,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses3
#define
  {
    ///< CCX_CCX0L3Repair0Fuses382
    82,
    16,
    0,
    0x1928,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses30
#define
  {
    ///< CCX_CCX0L3Repair0Fuses3083
    83,
    16,
    0,
    0x1994,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses31
#define
  {
    ///< CCX_CCX0L3Repair0Fuses3184
    84,
    16,
    0,
    0x1998,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses4
#define
  {
    ///< CCX_CCX0L3Repair0Fuses485
    85,
    16,
    0,
    0x192C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses5
#define
  {
    ///< CCX_CCX0L3Repair0Fuses586
    86,
    16,
    0,
    0x1930,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses6
#define
  {
    ///< CCX_CCX0L3Repair0Fuses687
    87,
    16,
    0,
    0x1934,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses7
#define
  {
    ///< CCX_CCX0L3Repair0Fuses788
    88,
    16,
    0,
    0x1938,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses8
#define
  {
    ///< CCX_CCX0L3Repair0Fuses889
    89,
    16,
    0,
    0x193C,
  },
#endif

#ifdef CCX_CCX0L3Repair0Fuses9
#define
  {
    ///< CCX_CCX0L3Repair0Fuses990
    90,
    16,
    0,
    0x1940,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses0
#define
  {
    ///< CCX_CCX0L3Repair1Fuses091
    91,
    16,
    16,
    0x191E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses1
#define
  {
    ///< CCX_CCX0L3Repair1Fuses192
    92,
    16,
    16,
    0x1922,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses10
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1093
    93,
    16,
    16,
    0x1946,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses11
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1194
    94,
    16,
    16,
    0x194A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses12
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1295
    95,
    16,
    16,
    0x194E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses13
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1396
    96,
    16,
    16,
    0x1952,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses14
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1497
    97,
    16,
    16,
    0x1956,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses15
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1598
    98,
    16,
    16,
    0x195A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses16
#define
  {
    ///< CCX_CCX0L3Repair1Fuses1699
    99,
    16,
    16,
    0x195E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses17
#define
  {
    ///< CCX_CCX0L3Repair1Fuses17100
    100,
    16,
    16,
    0x1962,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses18
#define
  {
    ///< CCX_CCX0L3Repair1Fuses18101
    101,
    16,
    16,
    0x1966,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses19
#define
  {
    ///< CCX_CCX0L3Repair1Fuses19102
    102,
    16,
    16,
    0x196A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses2
#define
  {
    ///< CCX_CCX0L3Repair1Fuses2103
    103,
    16,
    16,
    0x1926,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses20
#define
  {
    ///< CCX_CCX0L3Repair1Fuses20104
    104,
    16,
    16,
    0x196E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses21
#define
  {
    ///< CCX_CCX0L3Repair1Fuses21105
    105,
    16,
    16,
    0x1972,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses22
#define
  {
    ///< CCX_CCX0L3Repair1Fuses22106
    106,
    16,
    16,
    0x1976,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses23
#define
  {
    ///< CCX_CCX0L3Repair1Fuses23107
    107,
    16,
    16,
    0x197A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses24
#define
  {
    ///< CCX_CCX0L3Repair1Fuses24108
    108,
    16,
    16,
    0x197E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses25
#define
  {
    ///< CCX_CCX0L3Repair1Fuses25109
    109,
    16,
    16,
    0x1982,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses26
#define
  {
    ///< CCX_CCX0L3Repair1Fuses26110
    110,
    16,
    16,
    0x1986,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses27
#define
  {
    ///< CCX_CCX0L3Repair1Fuses27111
    111,
    16,
    16,
    0x198A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses28
#define
  {
    ///< CCX_CCX0L3Repair1Fuses28112
    112,
    16,
    16,
    0x198E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses29
#define
  {
    ///< CCX_CCX0L3Repair1Fuses29113
    113,
    16,
    16,
    0x1992,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses3
#define
  {
    ///< CCX_CCX0L3Repair1Fuses3114
    114,
    16,
    16,
    0x192A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses30
#define
  {
    ///< CCX_CCX0L3Repair1Fuses30115
    115,
    16,
    16,
    0x1996,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses31
#define
  {
    ///< CCX_CCX0L3Repair1Fuses31116
    116,
    16,
    16,
    0x199A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses4
#define
  {
    ///< CCX_CCX0L3Repair1Fuses4117
    117,
    16,
    16,
    0x192E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses5
#define
  {
    ///< CCX_CCX0L3Repair1Fuses5118
    118,
    16,
    16,
    0x1932,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses6
#define
  {
    ///< CCX_CCX0L3Repair1Fuses6119
    119,
    16,
    16,
    0x1936,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses7
#define
  {
    ///< CCX_CCX0L3Repair1Fuses7120
    120,
    16,
    16,
    0x193A,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses8
#define
  {
    ///< CCX_CCX0L3Repair1Fuses8121
    121,
    16,
    16,
    0x193E,
  },
#endif

#ifdef CCX_CCX0L3Repair1Fuses9
#define
  {
    ///< CCX_CCX0L3Repair1Fuses9122
    122,
    16,
    16,
    0x1942,
  },
#endif

#ifdef CCX_CCX0MaFddDD0OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDD0OffsetHi123
    123,
    7,
    10,
    0x1861,
  },
#endif

#ifdef CCX_CCX0MaFddDD0OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDD0OffsetLo124
    124,
    7,
    3,
    0x1860,
  },
#endif

#ifdef CCX_CCX0MaFddDD1OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDD1OffsetHi125
    125,
    7,
    6,
    0x1864,
  },
#endif

#ifdef CCX_CCX0MaFddDD1OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDD1OffsetLo126
    126,
    7,
    31,
    0x1863,
  },
#endif

#ifdef CCX_CCX0MaFddDD2OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDD2OffsetHi127
    127,
    7,
    2,
    0x1868,
  },
#endif

#ifdef CCX_CCX0MaFddDD2OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDD2OffsetLo128
    128,
    7,
    27,
    0x1867,
  },
#endif

#ifdef CCX_CCX0MaFddDD3OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDD3OffsetHi129
    129,
    7,
    30,
    0x186B,
  },
#endif

#ifdef CCX_CCX0MaFddDD3OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDD3OffsetLo130
    130,
    7,
    23,
    0x186A,
  },
#endif

#ifdef CCX_CCX0MaFddDDL3OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDDL3OffsetHi131
    131,
    7,
    12,
    0x186D,
  },
#endif

#ifdef CCX_CCX0MaFddDDL3OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDDL3OffsetLo132
    132,
    7,
    5,
    0x186C,
  },
#endif

#ifdef CCX_CCX0MaFddDldo0OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDldo0OffsetHi133
    133,
    7,
    28,
    0x185F,
  },
#endif

#ifdef CCX_CCX0MaFddDldo0OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDldo0OffsetLo134
    134,
    7,
    21,
    0x185E,
  },
#endif

#ifdef CCX_CCX0MaFddDldo1OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDldo1OffsetHi135
    135,
    7,
    24,
    0x1863,
  },
#endif

#ifdef CCX_CCX0MaFddDldo1OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDldo1OffsetLo136
    136,
    7,
    17,
    0x1862,
  },
#endif

#ifdef CCX_CCX0MaFddDldo2OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDldo2OffsetHi137
    137,
    7,
    20,
    0x1866,
  },
#endif

#ifdef CCX_CCX0MaFddDldo2OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDldo2OffsetLo138
    138,
    7,
    13,
    0x1865,
  },
#endif

#ifdef CCX_CCX0MaFddDldo3OffsetHi
#define
  {
    ///< CCX_CCX0MaFddDldo3OffsetHi139
    139,
    7,
    16,
    0x186A,
  },
#endif

#ifdef CCX_CCX0MaFddDldo3OffsetLo
#define
  {
    ///< CCX_CCX0MaFddDldo3OffsetLo140
    140,
    7,
    9,
    0x1869,
  },
#endif

#ifdef CCX_CCX0Repair0
#define
  {
    ///< CCX_CCX0Repair0141
    141,
    17,
    10,
    0x18D5,
  },
#endif

#ifdef CCX_CCX0Repair10Hi
#define
  {
    ///< CCX_CCX0Repair10Hi142
    142,
    6,
    0,
    0x18EC,
  },
#endif

#ifdef CCX_CCX0Repair10Lo
#define
  {
    ///< CCX_CCX0Repair10Lo143
    143,
    11,
    21,
    0x18EA,
  },
#endif

#ifdef CCX_CCX0Repair11
#define
  {
    ///< CCX_CCX0Repair11144
    144,
    17,
    0,
    0x18E8,
  },
#endif

#ifdef CCX_CCX0Repair1Hi
#define
  {
    ///< CCX_CCX0Repair1Hi145
    145,
    6,
    0,
    0x18D4,
  },
#endif

#ifdef CCX_CCX0Repair1Lo
#define
  {
    ///< CCX_CCX0Repair1Lo146
    146,
    11,
    21,
    0x18D2,
  },
#endif

#ifdef CCX_CCX0Repair2
#define
  {
    ///< CCX_CCX0Repair2147
    147,
    17,
    0,
    0x18D0,
  },
#endif

#ifdef CCX_CCX0Repair3
#define
  {
    ///< CCX_CCX0Repair3148
    148,
    17,
    10,
    0x18DD,
  },
#endif

#ifdef CCX_CCX0Repair4Hi
#define
  {
    ///< CCX_CCX0Repair4Hi149
    149,
    6,
    0,
    0x18DC,
  },
#endif

#ifdef CCX_CCX0Repair4Lo
#define
  {
    ///< CCX_CCX0Repair4Lo150
    150,
    11,
    21,
    0x18DA,
  },
#endif

#ifdef CCX_CCX0Repair5
#define
  {
    ///< CCX_CCX0Repair5151
    151,
    17,
    0,
    0x18D8,
  },
#endif

#ifdef CCX_CCX0Repair6
#define
  {
    ///< CCX_CCX0Repair6152
    152,
    17,
    10,
    0x18E5,
  },
#endif

#ifdef CCX_CCX0Repair7Hi
#define
  {
    ///< CCX_CCX0Repair7Hi153
    153,
    6,
    0,
    0x18E4,
  },
#endif

#ifdef CCX_CCX0Repair7Lo
#define
  {
    ///< CCX_CCX0Repair7Lo154
    154,
    11,
    21,
    0x18E2,
  },
#endif

#ifdef CCX_CCX0Repair8
#define
  {
    ///< CCX_CCX0Repair8155
    155,
    17,
    0,
    0x18E0,
  },
#endif

#ifdef CCX_CCX0Repair9
#define
  {
    ///< CCX_CCX0Repair9156
    156,
    17,
    10,
    0x18ED,
  },
#endif

#ifdef CCX_CCX0Reserved0
#define
  {
    ///< CCX_CCX0Reserved0157
    157,
    1,
    31,
    0x18D7,
  },
#endif

#ifdef CCX_CCX0Reserved3
#define
  {
    ///< CCX_CCX0Reserved3158
    158,
    1,
    31,
    0x18DF,
  },
#endif

#ifdef CCX_CCX0Reserved6
#define
  {
    ///< CCX_CCX0Reserved6159
    159,
    1,
    31,
    0x18E7,
  },
#endif

#ifdef CCX_CCX0Reserved9
#define
  {
    ///< CCX_CCX0Reserved9160
    160,
    1,
    31,
    0x18EF,
  },
#endif

#ifdef CCX_CCX1CoreID0
#define
  {
    ///< CCX_CCX1CoreID0161
    161,
    2,
    29,
    0x18F7,
  },
#endif

#ifdef CCX_CCX1CoreID1
#define
  {
    ///< CCX_CCX1CoreID1162
    162,
    2,
    8,
    0x18F5,
  },
#endif

#ifdef CCX_CCX1CoreID10
#define
  {
    ///< CCX_CCX1CoreID10163
    163,
    2,
    8,
    0x190D,
  },
#endif

#ifdef CCX_CCX1CoreID11
#define
  {
    ///< CCX_CCX1CoreID11164
    164,
    2,
    19,
    0x190A,
  },
#endif

#ifdef CCX_CCX1CoreID2
#define
  {
    ///< CCX_CCX1CoreID2165
    165,
    2,
    19,
    0x18F2,
  },
#endif

#ifdef CCX_CCX1CoreID3
#define
  {
    ///< CCX_CCX1CoreID3166
    166,
    2,
    29,
    0x18FF,
  },
#endif

#ifdef CCX_CCX1CoreID4
#define
  {
    ///< CCX_CCX1CoreID4167
    167,
    2,
    8,
    0x18FD,
  },
#endif

#ifdef CCX_CCX1CoreID5
#define
  {
    ///< CCX_CCX1CoreID5168
    168,
    2,
    19,
    0x18FA,
  },
#endif

#ifdef CCX_CCX1CoreID6
#define
  {
    ///< CCX_CCX1CoreID6169
    169,
    2,
    29,
    0x1907,
  },
#endif

#ifdef CCX_CCX1CoreID7
#define
  {
    ///< CCX_CCX1CoreID7170
    170,
    2,
    8,
    0x1905,
  },
#endif

#ifdef CCX_CCX1CoreID8
#define
  {
    ///< CCX_CCX1CoreID8171
    171,
    2,
    19,
    0x1902,
  },
#endif

#ifdef CCX_CCX1CoreID9
#define
  {
    ///< CCX_CCX1CoreID9172
    172,
    2,
    29,
    0x190F,
  },
#endif

#ifdef CCX_CCX1L1Repair0
#define
  {
    ///< CCX_CCX1L1Repair0173
    173,
    1,
    28,
    0x18F7,
  },
#endif

#ifdef CCX_CCX1L1Repair1
#define
  {
    ///< CCX_CCX1L1Repair1174
    174,
    1,
    7,
    0x18F4,
  },
#endif

#ifdef CCX_CCX1L1Repair10
#define
  {
    ///< CCX_CCX1L1Repair10175
    175,
    1,
    7,
    0x190C,
  },
#endif

#ifdef CCX_CCX1L1Repair11
#define
  {
    ///< CCX_CCX1L1Repair11176
    176,
    1,
    18,
    0x190A,
  },
#endif

#ifdef CCX_CCX1L1Repair2
#define
  {
    ///< CCX_CCX1L1Repair2177
    177,
    1,
    18,
    0x18F2,
  },
#endif

#ifdef CCX_CCX1L1Repair3
#define
  {
    ///< CCX_CCX1L1Repair3178
    178,
    1,
    28,
    0x18FF,
  },
#endif

#ifdef CCX_CCX1L1Repair4
#define
  {
    ///< CCX_CCX1L1Repair4179
    179,
    1,
    7,
    0x18FC,
  },
#endif

#ifdef CCX_CCX1L1Repair5
#define
  {
    ///< CCX_CCX1L1Repair5180
    180,
    1,
    18,
    0x18FA,
  },
#endif

#ifdef CCX_CCX1L1Repair6
#define
  {
    ///< CCX_CCX1L1Repair6181
    181,
    1,
    28,
    0x1907,
  },
#endif

#ifdef CCX_CCX1L1Repair7
#define
  {
    ///< CCX_CCX1L1Repair7182
    182,
    1,
    7,
    0x1904,
  },
#endif

#ifdef CCX_CCX1L1Repair8
#define
  {
    ///< CCX_CCX1L1Repair8183
    183,
    1,
    18,
    0x1902,
  },
#endif

#ifdef CCX_CCX1L1Repair9
#define
  {
    ///< CCX_CCX1L1Repair9184
    184,
    1,
    28,
    0x190F,
  },
#endif

#ifdef CCX_CCX1L2Repair0
#define
  {
    ///< CCX_CCX1L2Repair0185
    185,
    1,
    27,
    0x18F7,
  },
#endif

#ifdef CCX_CCX1L2Repair1
#define
  {
    ///< CCX_CCX1L2Repair1186
    186,
    1,
    6,
    0x18F4,
  },
#endif

#ifdef CCX_CCX1L2Repair10
#define
  {
    ///< CCX_CCX1L2Repair10187
    187,
    1,
    6,
    0x190C,
  },
#endif

#ifdef CCX_CCX1L2Repair11
#define
  {
    ///< CCX_CCX1L2Repair11188
    188,
    1,
    17,
    0x190A,
  },
#endif

#ifdef CCX_CCX1L2Repair2
#define
  {
    ///< CCX_CCX1L2Repair2189
    189,
    1,
    17,
    0x18F2,
  },
#endif

#ifdef CCX_CCX1L2Repair3
#define
  {
    ///< CCX_CCX1L2Repair3190
    190,
    1,
    27,
    0x18FF,
  },
#endif

#ifdef CCX_CCX1L2Repair4
#define
  {
    ///< CCX_CCX1L2Repair4191
    191,
    1,
    6,
    0x18FC,
  },
#endif

#ifdef CCX_CCX1L2Repair5
#define
  {
    ///< CCX_CCX1L2Repair5192
    192,
    1,
    17,
    0x18FA,
  },
#endif

#ifdef CCX_CCX1L2Repair6
#define
  {
    ///< CCX_CCX1L2Repair6193
    193,
    1,
    27,
    0x1907,
  },
#endif

#ifdef CCX_CCX1L2Repair7
#define
  {
    ///< CCX_CCX1L2Repair7194
    194,
    1,
    6,
    0x1904,
  },
#endif

#ifdef CCX_CCX1L2Repair8
#define
  {
    ///< CCX_CCX1L2Repair8195
    195,
    1,
    17,
    0x1902,
  },
#endif

#ifdef CCX_CCX1L2Repair9
#define
  {
    ///< CCX_CCX1L2Repair9196
    196,
    1,
    27,
    0x190F,
  },
#endif

#ifdef CCX_CCX1L3M0EvenBankDis
#define
  {
    ///< CCX_CCX1L3M0EvenBankDis197
    197,
    3,
    12,
    0x199D,
  },
#endif

#ifdef CCX_CCX1L3M0OddBankDis
#define
  {
    ///< CCX_CCX1L3M0OddBankDis198
    198,
    3,
    0,
    0x199C,
  },
#endif

#ifdef CCX_CCX1L3M1EvenBankDis
#define
  {
    ///< CCX_CCX1L3M1EvenBankDis199
    199,
    3,
    15,
    0x199D,
  },
#endif

#ifdef CCX_CCX1L3M1OddBankDis
#define
  {
    ///< CCX_CCX1L3M1OddBankDis200
    200,
    3,
    3,
    0x199C,
  },
#endif

#ifdef CCX_CCX1L3M2EvenBankDis
#define
  {
    ///< CCX_CCX1L3M2EvenBankDis201
    201,
    3,
    18,
    0x199E,
  },
#endif

#ifdef CCX_CCX1L3M2OddBankDis
#define
  {
    ///< CCX_CCX1L3M2OddBankDis202
    202,
    3,
    6,
    0x199C,
  },
#endif

#ifdef CCX_CCX1L3M3EvenBankDis
#define
  {
    ///< CCX_CCX1L3M3EvenBankDis203
    203,
    3,
    21,
    0x199E,
  },
#endif

#ifdef CCX_CCX1L3M3OddBankDis
#define
  {
    ///< CCX_CCX1L3M3OddBankDis204
    204,
    3,
    9,
    0x199D,
  },
#endif

#ifdef CCX_CCX1L3MReserved
#define
  {
    ///< CCX_CCX1L3MReserved205
    205,
    8,
    24,
    0x199F,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl2RladrCode
#define
  {
    ///< CCX_CCX1L3PllFllCtl2RladrCode206
    206,
    9,
    7,
    0x1844,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4BCoarse
#define
  {
    ///< CCX_CCX1L3PllFllCtl4BCoarse207
    207,
    1,
    19,
    0x1846,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4BOffsetA
#define
  {
    ///< CCX_CCX1L3PllFllCtl4BOffsetA208
    208,
    4,
    28,
    0x1847,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4BOffsetB
#define
  {
    ///< CCX_CCX1L3PllFllCtl4BOffsetB209
    209,
    4,
    24,
    0x1847,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4BStep
#define
  {
    ///< CCX_CCX1L3PllFllCtl4BStep210
    210,
    4,
    20,
    0x1846,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4DisVroCap
#define
  {
    ///< CCX_CCX1L3PllFllCtl4DisVroCap211
    211,
    1,
    18,
    0x1846,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4Rsvd31_25
#define
  {
    ///< CCX_CCX1L3PllFllCtl4Rsvd31_25212
    212,
    7,
    0,
    0x1844,
  },
#endif

#ifdef CCX_CCX1L3PllFllCtl4V2CcGain
#define
  {
    ///< CCX_CCX1L3PllFllCtl4V2CcGain213
    213,
    2,
    16,
    0x1846,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses0
#define
  {
    ///< CCX_CCX1L3Repair0Fuses0214
    214,
    16,
    0,
    0x19A0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses1
#define
  {
    ///< CCX_CCX1L3Repair0Fuses1215
    215,
    16,
    0,
    0x19A4,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses10
#define
  {
    ///< CCX_CCX1L3Repair0Fuses10216
    216,
    16,
    0,
    0x19C8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses11
#define
  {
    ///< CCX_CCX1L3Repair0Fuses11217
    217,
    16,
    0,
    0x19CC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses12
#define
  {
    ///< CCX_CCX1L3Repair0Fuses12218
    218,
    16,
    0,
    0x19D0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses13
#define
  {
    ///< CCX_CCX1L3Repair0Fuses13219
    219,
    16,
    0,
    0x19D4,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses14
#define
  {
    ///< CCX_CCX1L3Repair0Fuses14220
    220,
    16,
    0,
    0x19D8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses15
#define
  {
    ///< CCX_CCX1L3Repair0Fuses15221
    221,
    16,
    0,
    0x19DC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses16
#define
  {
    ///< CCX_CCX1L3Repair0Fuses16222
    222,
    16,
    0,
    0x19E0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses17
#define
  {
    ///< CCX_CCX1L3Repair0Fuses17223
    223,
    16,
    0,
    0x19E4,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses18
#define
  {
    ///< CCX_CCX1L3Repair0Fuses18224
    224,
    16,
    0,
    0x19E8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses19
#define
  {
    ///< CCX_CCX1L3Repair0Fuses19225
    225,
    16,
    0,
    0x19EC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses2
#define
  {
    ///< CCX_CCX1L3Repair0Fuses2226
    226,
    16,
    0,
    0x19A8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses20
#define
  {
    ///< CCX_CCX1L3Repair0Fuses20227
    227,
    16,
    0,
    0x19F0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses21
#define
  {
    ///< CCX_CCX1L3Repair0Fuses21228
    228,
    16,
    0,
    0x19F4,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses22
#define
  {
    ///< CCX_CCX1L3Repair0Fuses22229
    229,
    16,
    0,
    0x19F8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses23
#define
  {
    ///< CCX_CCX1L3Repair0Fuses23230
    230,
    16,
    0,
    0x19FC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses24
#define
  {
    ///< CCX_CCX1L3Repair0Fuses24231
    231,
    16,
    0,
    0x1A00,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses25
#define
  {
    ///< CCX_CCX1L3Repair0Fuses25232
    232,
    16,
    0,
    0x1A04,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses26
#define
  {
    ///< CCX_CCX1L3Repair0Fuses26233
    233,
    16,
    0,
    0x1A08,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses27
#define
  {
    ///< CCX_CCX1L3Repair0Fuses27234
    234,
    16,
    0,
    0x1A0C,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses28
#define
  {
    ///< CCX_CCX1L3Repair0Fuses28235
    235,
    16,
    0,
    0x1A10,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses29
#define
  {
    ///< CCX_CCX1L3Repair0Fuses29236
    236,
    16,
    0,
    0x1A14,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses3
#define
  {
    ///< CCX_CCX1L3Repair0Fuses3237
    237,
    16,
    0,
    0x19AC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses30
#define
  {
    ///< CCX_CCX1L3Repair0Fuses30238
    238,
    16,
    0,
    0x1A18,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses31
#define
  {
    ///< CCX_CCX1L3Repair0Fuses31239
    239,
    16,
    0,
    0x1A1C,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses4
#define
  {
    ///< CCX_CCX1L3Repair0Fuses4240
    240,
    16,
    0,
    0x19B0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses5
#define
  {
    ///< CCX_CCX1L3Repair0Fuses5241
    241,
    16,
    0,
    0x19B4,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses6
#define
  {
    ///< CCX_CCX1L3Repair0Fuses6242
    242,
    16,
    0,
    0x19B8,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses7
#define
  {
    ///< CCX_CCX1L3Repair0Fuses7243
    243,
    16,
    0,
    0x19BC,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses8
#define
  {
    ///< CCX_CCX1L3Repair0Fuses8244
    244,
    16,
    0,
    0x19C0,
  },
#endif

#ifdef CCX_CCX1L3Repair0Fuses9
#define
  {
    ///< CCX_CCX1L3Repair0Fuses9245
    245,
    16,
    0,
    0x19C4,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses0
#define
  {
    ///< CCX_CCX1L3Repair1Fuses0246
    246,
    16,
    16,
    0x19A2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses1
#define
  {
    ///< CCX_CCX1L3Repair1Fuses1247
    247,
    16,
    16,
    0x19A6,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses10
#define
  {
    ///< CCX_CCX1L3Repair1Fuses10248
    248,
    16,
    16,
    0x19CA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses11
#define
  {
    ///< CCX_CCX1L3Repair1Fuses11249
    249,
    16,
    16,
    0x19CE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses12
#define
  {
    ///< CCX_CCX1L3Repair1Fuses12250
    250,
    16,
    16,
    0x19D2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses13
#define
  {
    ///< CCX_CCX1L3Repair1Fuses13251
    251,
    16,
    16,
    0x19D6,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses14
#define
  {
    ///< CCX_CCX1L3Repair1Fuses14252
    252,
    16,
    16,
    0x19DA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses15
#define
  {
    ///< CCX_CCX1L3Repair1Fuses15253
    253,
    16,
    16,
    0x19DE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses16
#define
  {
    ///< CCX_CCX1L3Repair1Fuses16254
    254,
    16,
    16,
    0x19E2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses17
#define
  {
    ///< CCX_CCX1L3Repair1Fuses17255
    255,
    16,
    16,
    0x19E6,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses18
#define
  {
    ///< CCX_CCX1L3Repair1Fuses18256
    256,
    16,
    16,
    0x19EA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses19
#define
  {
    ///< CCX_CCX1L3Repair1Fuses19257
    257,
    16,
    16,
    0x19EE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses2
#define
  {
    ///< CCX_CCX1L3Repair1Fuses2258
    258,
    16,
    16,
    0x19AA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses20
#define
  {
    ///< CCX_CCX1L3Repair1Fuses20259
    259,
    16,
    16,
    0x19F2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses21
#define
  {
    ///< CCX_CCX1L3Repair1Fuses21260
    260,
    16,
    16,
    0x19F6,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses22
#define
  {
    ///< CCX_CCX1L3Repair1Fuses22261
    261,
    16,
    16,
    0x19FA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses23
#define
  {
    ///< CCX_CCX1L3Repair1Fuses23262
    262,
    16,
    16,
    0x19FE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses24
#define
  {
    ///< CCX_CCX1L3Repair1Fuses24263
    263,
    16,
    16,
    0x1A02,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses25
#define
  {
    ///< CCX_CCX1L3Repair1Fuses25264
    264,
    16,
    16,
    0x1A06,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses26
#define
  {
    ///< CCX_CCX1L3Repair1Fuses26265
    265,
    16,
    16,
    0x1A0A,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses27
#define
  {
    ///< CCX_CCX1L3Repair1Fuses27266
    266,
    16,
    16,
    0x1A0E,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses28
#define
  {
    ///< CCX_CCX1L3Repair1Fuses28267
    267,
    16,
    16,
    0x1A12,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses29
#define
  {
    ///< CCX_CCX1L3Repair1Fuses29268
    268,
    16,
    16,
    0x1A16,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses3
#define
  {
    ///< CCX_CCX1L3Repair1Fuses3269
    269,
    16,
    16,
    0x19AE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses30
#define
  {
    ///< CCX_CCX1L3Repair1Fuses30270
    270,
    16,
    16,
    0x1A1A,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses31
#define
  {
    ///< CCX_CCX1L3Repair1Fuses31271
    271,
    16,
    16,
    0x1A1E,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses4
#define
  {
    ///< CCX_CCX1L3Repair1Fuses4272
    272,
    16,
    16,
    0x19B2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses5
#define
  {
    ///< CCX_CCX1L3Repair1Fuses5273
    273,
    16,
    16,
    0x19B6,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses6
#define
  {
    ///< CCX_CCX1L3Repair1Fuses6274
    274,
    16,
    16,
    0x19BA,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses7
#define
  {
    ///< CCX_CCX1L3Repair1Fuses7275
    275,
    16,
    16,
    0x19BE,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses8
#define
  {
    ///< CCX_CCX1L3Repair1Fuses8276
    276,
    16,
    16,
    0x19C2,
  },
#endif

#ifdef CCX_CCX1L3Repair1Fuses9
#define
  {
    ///< CCX_CCX1L3Repair1Fuses9277
    277,
    16,
    16,
    0x19C6,
  },
#endif

#ifdef CCX_CCX1MaFddDD0OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDD0OffsetHi278
    278,
    7,
    8,
    0x1871,
  },
#endif

#ifdef CCX_CCX1MaFddDD0OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDD0OffsetLo279
    279,
    7,
    1,
    0x1870,
  },
#endif

#ifdef CCX_CCX1MaFddDD1OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDD1OffsetHi280
    280,
    7,
    4,
    0x1874,
  },
#endif

#ifdef CCX_CCX1MaFddDD1OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDD1OffsetLo281
    281,
    7,
    29,
    0x1873,
  },
#endif

#ifdef CCX_CCX1MaFddDD2OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDD2OffsetHi282
    282,
    7,
    0,
    0x1878,
  },
#endif

#ifdef CCX_CCX1MaFddDD2OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDD2OffsetLo283
    283,
    7,
    25,
    0x1877,
  },
#endif

#ifdef CCX_CCX1MaFddDD3OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDD3OffsetHi284
    284,
    7,
    28,
    0x187B,
  },
#endif

#ifdef CCX_CCX1MaFddDD3OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDD3OffsetLo285
    285,
    7,
    21,
    0x187A,
  },
#endif

#ifdef CCX_CCX1MaFddDDL3OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDDL3OffsetHi286
    286,
    7,
    10,
    0x187D,
  },
#endif

#ifdef CCX_CCX1MaFddDDL3OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDDL3OffsetLo287
    287,
    7,
    3,
    0x187C,
  },
#endif

#ifdef CCX_CCX1MaFddDDPad
#define
  {
    ///< CCX_CCX1MaFddDDPad288
    288,
    15,
    17,
    0x187E,
  },
#endif

#ifdef CCX_CCX1MaFddDldo0OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDldo0OffsetHi289
    289,
    7,
    26,
    0x186F,
  },
#endif

#ifdef CCX_CCX1MaFddDldo0OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDldo0OffsetLo290
    290,
    7,
    19,
    0x186E,
  },
#endif

#ifdef CCX_CCX1MaFddDldo1OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDldo1OffsetHi291
    291,
    7,
    22,
    0x1872,
  },
#endif

#ifdef CCX_CCX1MaFddDldo1OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDldo1OffsetLo292
    292,
    7,
    15,
    0x1871,
  },
#endif

#ifdef CCX_CCX1MaFddDldo2OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDldo2OffsetHi293
    293,
    7,
    18,
    0x1876,
  },
#endif

#ifdef CCX_CCX1MaFddDldo2OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDldo2OffsetLo294
    294,
    7,
    11,
    0x1875,
  },
#endif

#ifdef CCX_CCX1MaFddDldo3OffsetHi
#define
  {
    ///< CCX_CCX1MaFddDldo3OffsetHi295
    295,
    7,
    14,
    0x1879,
  },
#endif

#ifdef CCX_CCX1MaFddDldo3OffsetLo
#define
  {
    ///< CCX_CCX1MaFddDldo3OffsetLo296
    296,
    7,
    7,
    0x1878,
  },
#endif

#ifdef CCX_CCX1Repair0
#define
  {
    ///< CCX_CCX1Repair0297
    297,
    17,
    10,
    0x18F5,
  },
#endif

#ifdef CCX_CCX1Repair10Hi
#define
  {
    ///< CCX_CCX1Repair10Hi298
    298,
    6,
    0,
    0x190C,
  },
#endif

#ifdef CCX_CCX1Repair10Lo
#define
  {
    ///< CCX_CCX1Repair10Lo299
    299,
    11,
    21,
    0x190A,
  },
#endif

#ifdef CCX_CCX1Repair11
#define
  {
    ///< CCX_CCX1Repair11300
    300,
    17,
    0,
    0x1908,
  },
#endif

#ifdef CCX_CCX1Repair1Hi
#define
  {
    ///< CCX_CCX1Repair1Hi301
    301,
    6,
    0,
    0x18F4,
  },
#endif

#ifdef CCX_CCX1Repair1Lo
#define
  {
    ///< CCX_CCX1Repair1Lo302
    302,
    11,
    21,
    0x18F2,
  },
#endif

#ifdef CCX_CCX1Repair2
#define
  {
    ///< CCX_CCX1Repair2303
    303,
    17,
    0,
    0x18F0,
  },
#endif

#ifdef CCX_CCX1Repair3
#define
  {
    ///< CCX_CCX1Repair3304
    304,
    17,
    10,
    0x18FD,
  },
#endif

#ifdef CCX_CCX1Repair4Hi
#define
  {
    ///< CCX_CCX1Repair4Hi305
    305,
    6,
    0,
    0x18FC,
  },
#endif

#ifdef CCX_CCX1Repair4Lo
#define
  {
    ///< CCX_CCX1Repair4Lo306
    306,
    11,
    21,
    0x18FA,
  },
#endif

#ifdef CCX_CCX1Repair5
#define
  {
    ///< CCX_CCX1Repair5307
    307,
    17,
    0,
    0x18F8,
  },
#endif

#ifdef CCX_CCX1Repair6
#define
  {
    ///< CCX_CCX1Repair6308
    308,
    17,
    10,
    0x1905,
  },
#endif

#ifdef CCX_CCX1Repair7Hi
#define
  {
    ///< CCX_CCX1Repair7Hi309
    309,
    6,
    0,
    0x1904,
  },
#endif

#ifdef CCX_CCX1Repair7Lo
#define
  {
    ///< CCX_CCX1Repair7Lo310
    310,
    11,
    21,
    0x1902,
  },
#endif

#ifdef CCX_CCX1Repair8
#define
  {
    ///< CCX_CCX1Repair8311
    311,
    17,
    0,
    0x1900,
  },
#endif

#ifdef CCX_CCX1Repair9
#define
  {
    ///< CCX_CCX1Repair9312
    312,
    17,
    10,
    0x190D,
  },
#endif

#ifdef CCX_CCX1Reserved0
#define
  {
    ///< CCX_CCX1Reserved0313
    313,
    1,
    31,
    0x18F7,
  },
#endif

#ifdef CCX_CCX1Reserved3
#define
  {
    ///< CCX_CCX1Reserved3314
    314,
    1,
    31,
    0x18FF,
  },
#endif

#ifdef CCX_CCX1Reserved6
#define
  {
    ///< CCX_CCX1Reserved6315
    315,
    1,
    31,
    0x1907,
  },
#endif

#ifdef CCX_CCX1Reserved9
#define
  {
    ///< CCX_CCX1Reserved9316
    316,
    1,
    31,
    0x190F,
  },
#endif

#ifdef CCX_COLDRESETMBISIEN
#define
  {
    ///< CCX_COLDRESETMBISIEN317
    317,
    1,
    27,
    0x1883,
  },
#endif

#ifdef CCX_COLDRESETMBISTEN
#define
  {
    ///< CCX_COLDRESETMBISTEN318
    318,
    1,
    25,
    0x1883,
  },
#endif

#ifdef CCX_CPLB_Reserved0
#define
  {
    ///< CCX_CPLB_Reserved0319
    319,
    11,
    0,
    0x18B8,
  },
#endif

#ifdef CCX_CPLB_Reserved1
#define
  {
    ///< CCX_CPLB_Reserved1320
    320,
    20,
    12,
    0x18B9,
  },
#endif

#ifdef CCX_CacheDiagDis
#define
  {
    ///< CCX_CacheDiagDis321
    321,
    1,
    12,
    0x1915,
  },
#endif

#ifdef CCX_CcxSpare0
#define
  {
    ///< CCX_CcxSpare0322
    322,
    12,
    20,
    0x184A,
  },
#endif

#ifdef CCX_CcxSpare1
#define
  {
    ///< CCX_CcxSpare1323
    323,
    9,
    23,
    0x1852,
  },
#endif

#ifdef CCX_ChL3InitPkg1Reserved_31_29
#define
  {
    ///< CCX_ChL3InitPkg1Reserved_31_29324
    324,
    3,
    29,
    0x1857,
  },
#endif

#ifdef CCX_ChL3InitPkg1Reserved_3_3
#define
  {
    ///< CCX_ChL3InitPkg1Reserved_3_3325
    325,
    1,
    3,
    0x1854,
  },
#endif

#ifdef CCX_ChL3InitPkg2Reserved_31_28
#define
  {
    ///< CCX_ChL3InitPkg2Reserved_31_28326
    326,
    4,
    28,
    0x185B,
  },
#endif

#ifdef CCX_ChL3PllBwCtlCoarseReserved_11_11
#define
  {
    ///< CCX_ChL3PllBwCtlCoarseReserved_11_11327
    327,
    1,
    11,
    0x182D,
  },
#endif

#ifdef CCX_ChL3PllBwCtlCoarseReserved_6_6
#define
  {
    ///< CCX_ChL3PllBwCtlCoarseReserved_6_6328
    328,
    1,
    6,
    0x182C,
  },
#endif

#ifdef CCX_ComplexId_Reserved
#define
  {
    ///< CCX_ComplexId_Reserved329
    329,
    3,
    12,
    0x1859,
  },
#endif

#ifdef CCX_ConservativeLock
#define
  {
    ///< CCX_ConservativeLock330
    330,
    2,
    20,
    0x184E,
  },
#endif

#ifdef CCX_CoreDis_Reserved
#define
  {
    ///< CCX_CoreDis_Reserved331
    331,
    4,
    8,
    0x1859,
  },
#endif

#ifdef CCX_CoreFunctionalSpareFuses
#define
  {
    ///< CCX_CoreFunctionalSpareFuses332
    332,
    160,
    0,
    0x18BC,
  },
#endif

#ifdef CCX_CoreResetDidMargin
#define
  {
    ///< CCX_CoreResetDidMargin333
    333,
    2,
    19,
    0x185A,
  },
#endif

#ifdef CCX_DCRAM0_FusBstStrenth
#define
  {
    ///< CCX_DCRAM0_FusBstStrenth334
    334,
    2,
    8,
    0x18A9,
  },
#endif

#ifdef CCX_DCRAM0_FusKprEn
#define
  {
    ///< CCX_DCRAM0_FusKprEn335
    335,
    3,
    0,
    0x18A8,
  },
#endif

#ifdef CCX_DCRAM0_FusSblKprEn
#define
  {
    ///< CCX_DCRAM0_FusSblKprEn336
    336,
    1,
    10,
    0x18A9,
  },
#endif

#ifdef CCX_DCRAM0_FusTimAdjBoost
#define
  {
    ///< CCX_DCRAM0_FusTimAdjBoost337
    337,
    3,
    5,
    0x18A8,
  },
#endif

#ifdef CCX_DCRAM0_FusTimAdjPDly
#define
  {
    ///< CCX_DCRAM0_FusTimAdjPDly338
    338,
    2,
    3,
    0x18A8,
  },
#endif

#ifdef CCX_DCRAM1_FusBstStrenth
#define
  {
    ///< CCX_DCRAM1_FusBstStrenth339
    339,
    2,
    19,
    0x18AA,
  },
#endif

#ifdef CCX_DCRAM1_FusKprEn
#define
  {
    ///< CCX_DCRAM1_FusKprEn340
    340,
    3,
    11,
    0x18A9,
  },
#endif

#ifdef CCX_DCRAM1_FusSblKprEn
#define
  {
    ///< CCX_DCRAM1_FusSblKprEn341
    341,
    1,
    21,
    0x18AA,
  },
#endif

#ifdef CCX_DCRAM1_FusTimAdjBoost
#define
  {
    ///< CCX_DCRAM1_FusTimAdjBoost342
    342,
    3,
    16,
    0x18AA,
  },
#endif

#ifdef CCX_DCRAM1_FusTimAdjPDly
#define
  {
    ///< CCX_DCRAM1_FusTimAdjPDly343
    343,
    2,
    14,
    0x18A9,
  },
#endif

#ifdef CCX_DC_Reserved
#define
  {
    ///< CCX_DC_Reserved344
    344,
    10,
    22,
    0x18AA,
  },
#endif

#ifdef CCX_DDCA_FCTL
#define
  {
    ///< CCX_DDCA_FCTL345
    345,
    3,
    0,
    0x1888,
  },
#endif

#ifdef CCX_DDCA_RCTL
#define
  {
    ///< CCX_DDCA_RCTL346
    346,
    3,
    3,
    0x1888,
  },
#endif

#ifdef CCX_DEFUSE_AesDisable
#define
  {
    ///< CCX_DEFUSE_AesDisable347
    347,
    1,
    29,
    0x189B,
  },
#endif

#ifdef CCX_DEFUSE_UcodePatchEncrypt
#define
  {
    ///< CCX_DEFUSE_UcodePatchEncrypt348
    348,
    1,
    28,
    0x189B,
  },
#endif

#ifdef CCX_DERAM0_FusBstStrenth
#define
  {
    ///< CCX_DERAM0_FusBstStrenth349
    349,
    2,
    8,
    0x1899,
  },
#endif

#ifdef CCX_DERAM0_FusKprEn
#define
  {
    ///< CCX_DERAM0_FusKprEn350
    350,
    3,
    0,
    0x1898,
  },
#endif

#ifdef CCX_DERAM0_FusSblKprEn
#define
  {
    ///< CCX_DERAM0_FusSblKprEn351
    351,
    1,
    10,
    0x1899,
  },
#endif

#ifdef CCX_DERAM0_FusTimAdjBoost
#define
  {
    ///< CCX_DERAM0_FusTimAdjBoost352
    352,
    3,
    5,
    0x1898,
  },
#endif

#ifdef CCX_DERAM0_FusTimAdjPDly
#define
  {
    ///< CCX_DERAM0_FusTimAdjPDly353
    353,
    2,
    3,
    0x1898,
  },
#endif

#ifdef CCX_DERAM1_FusBstStrenth
#define
  {
    ///< CCX_DERAM1_FusBstStrenth354
    354,
    2,
    19,
    0x189A,
  },
#endif

#ifdef CCX_DERAM1_FusKprEn
#define
  {
    ///< CCX_DERAM1_FusKprEn355
    355,
    3,
    11,
    0x1899,
  },
#endif

#ifdef CCX_DERAM1_FusSblKprEn
#define
  {
    ///< CCX_DERAM1_FusSblKprEn356
    356,
    1,
    21,
    0x189A,
  },
#endif

#ifdef CCX_DERAM1_FusTimAdjBoost
#define
  {
    ///< CCX_DERAM1_FusTimAdjBoost357
    357,
    3,
    16,
    0x189A,
  },
#endif

#ifdef CCX_DERAM1_FusTimAdjPDly
#define
  {
    ///< CCX_DERAM1_FusTimAdjPDly358
    358,
    2,
    14,
    0x1899,
  },
#endif

#ifdef CCX_DEROM_FusKprEn
#define
  {
    ///< CCX_DEROM_FusKprEn359
    359,
    3,
    22,
    0x189A,
  },
#endif

#ifdef CCX_DEROM_FusSblKprEn
#define
  {
    ///< CCX_DEROM_FusSblKprEn360
    360,
    1,
    27,
    0x189B,
  },
#endif

#ifdef CCX_DEROM_FusTimAdjPDly
#define
  {
    ///< CCX_DEROM_FusTimAdjPDly361
    361,
    2,
    25,
    0x189B,
  },
#endif

#ifdef CCX_DE_Reserved
#define
  {
    ///< CCX_DE_Reserved362
    362,
    2,
    30,
    0x189B,
  },
#endif

#ifdef CCX_DfsStretchAmount
#define
  {
    ///< CCX_DfsStretchAmount363
    363,
    4,
    0,
    0x1848,
  },
#endif

#ifdef CCX_DfsStretchEnable
#define
  {
    ///< CCX_DfsStretchEnable364
    364,
    1,
    4,
    0x1848,
  },
#endif

#ifdef CCX_DroopSyncSelect
#define
  {
    ///< CCX_DroopSyncSelect365
    365,
    2,
    25,
    0x185B,
  },
#endif

#ifdef CCX_DutyAdj2phase
#define
  {
    ///< CCX_DutyAdj2phase366
    366,
    4,
    18,
    0x1856,
  },
#endif

#ifdef CCX_DutyAdj8phase
#define
  {
    ///< CCX_DutyAdj8phase367
    367,
    4,
    22,
    0x1856,
  },
#endif

#ifdef CCX_EX_Reserved
#define
  {
    ///< CCX_EX_Reserved368
    368,
    32,
    0,
    0x18A4,
  },
#endif

#ifdef CCX_EnableDD
#define
  {
    ///< CCX_EnableDD369
    369,
    1,
    19,
    0x184E,
  },
#endif

#ifdef CCX_FP_Reserved
#define
  {
    ///< CCX_FP_Reserved370
    370,
    32,
    0,
    0x189C,
  },
#endif

#ifdef CCX_FreqMode
#define
  {
    ///< CCX_FreqMode371
    371,
    2,
    2,
    0x184C,
  },
#endif

#ifdef CCX_FsmCodeMargin
#define
  {
    ///< CCX_FsmCodeMargin372
    372,
    2,
    9,
    0x184D,
  },
#endif

#ifdef CCX_FsmWaitCycles
#define
  {
    ///< CCX_FsmWaitCycles373
    373,
    4,
    11,
    0x184D,
  },
#endif

#ifdef CCX_FuseProgDone
#define
  {
    ///< CCX_FuseProgDone374
    374,
    1,
    0,
    0x185C,
  },
#endif

#ifdef CCX_GRSBREAKPOINTCFG
#define
  {
    ///< CCX_GRSBREAKPOINTCFG375
    375,
    3,
    29,
    0x1883,
  },
#endif

#ifdef CCX_GlbRstPause
#define
  {
    ///< CCX_GlbRstPause376
    376,
    3,
    0,
    0x1854,
  },
#endif

#ifdef CCX_HARDREPAIREN_1
#define
  {
    ///< CCX_HARDREPAIREN_1377
    377,
    1,
    23,
    0x1882,
  },
#endif

#ifdef CCX_HDL3DatSuperVminmaxProg
#define
  {
    ///< CCX_HDL3DatSuperVminmaxProg378
    378,
    4,
    28,
    0x1913,
  },
#endif

#ifdef CCX_HDbootSuperVmaxEn
#define
  {
    ///< CCX_HDbootSuperVmaxEn379
    379,
    1,
    30,
    0x1917,
  },
#endif

#ifdef CCX_HDbootSuperVminEn
#define
  {
    ///< CCX_HDbootSuperVminEn380
    380,
    1,
    31,
    0x1917,
  },
#endif

#ifdef CCX_HardRepairEn_0
#define
  {
    ///< CCX_HardRepairEn_0381
    381,
    1,
    6,
    0x1854,
  },
#endif

#ifdef CCX_ICRAM0_FusBstStrenth
#define
  {
    ///< CCX_ICRAM0_FusBstStrenth382
    382,
    2,
    8,
    0x1891,
  },
#endif

#ifdef CCX_ICRAM0_FusKprEn
#define
  {
    ///< CCX_ICRAM0_FusKprEn383
    383,
    3,
    0,
    0x1890,
  },
#endif

#ifdef CCX_ICRAM0_FusSblKprEn
#define
  {
    ///< CCX_ICRAM0_FusSblKprEn384
    384,
    1,
    10,
    0x1891,
  },
#endif

#ifdef CCX_ICRAM0_FusTimAdjBoost
#define
  {
    ///< CCX_ICRAM0_FusTimAdjBoost385
    385,
    3,
    5,
    0x1890,
  },
#endif

#ifdef CCX_ICRAM0_FusTimAdjPDly
#define
  {
    ///< CCX_ICRAM0_FusTimAdjPDly386
    386,
    2,
    3,
    0x1890,
  },
#endif

#ifdef CCX_ICRAM1_FusBstStrenth
#define
  {
    ///< CCX_ICRAM1_FusBstStrenth387
    387,
    2,
    19,
    0x1892,
  },
#endif

#ifdef CCX_ICRAM1_FusKprEn
#define
  {
    ///< CCX_ICRAM1_FusKprEn388
    388,
    3,
    11,
    0x1891,
  },
#endif

#ifdef CCX_ICRAM1_FusSblKprEn
#define
  {
    ///< CCX_ICRAM1_FusSblKprEn389
    389,
    1,
    21,
    0x1892,
  },
#endif

#ifdef CCX_ICRAM1_FusTimAdjBoost
#define
  {
    ///< CCX_ICRAM1_FusTimAdjBoost390
    390,
    3,
    16,
    0x1892,
  },
#endif

#ifdef CCX_ICRAM1_FusTimAdjPDly
#define
  {
    ///< CCX_ICRAM1_FusTimAdjPDly391
    391,
    2,
    14,
    0x1891,
  },
#endif

#ifdef CCX_ICRAM_Reserved
#define
  {
    ///< CCX_ICRAM_Reserved392
    392,
    10,
    22,
    0x1892,
  },
#endif

#ifdef CCX_L23SuperVmaxThreshold
#define
  {
    ///< CCX_L23SuperVmaxThreshold393
    393,
    4,
    11,
    0x1851,
  },
#endif

#ifdef CCX_L23SuperVminThreshold
#define
  {
    ///< CCX_L23SuperVminThreshold394
    394,
    4,
    7,
    0x1850,
  },
#endif

#ifdef CCX_L2RAM_DWQSTPC
#define
  {
    ///< CCX_L2RAM_DWQSTPC395
    395,
    4,
    12,
    0x18B5,
  },
#endif

#ifdef CCX_L2RAM_DataSTPC
#define
  {
    ///< CCX_L2RAM_DataSTPC396
    396,
    8,
    0,
    0x18B0,
  },
#endif

#ifdef CCX_L2RAM_Reserved0
#define
  {
    ///< CCX_L2RAM_Reserved0397
    397,
    8,
    24,
    0x18B3,
  },
#endif

#ifdef CCX_L2RAM_Reserved1
#define
  {
    ///< CCX_L2RAM_Reserved1398
    398,
    16,
    16,
    0x18B6,
  },
#endif

#ifdef CCX_L2RAM_SuperVminmaxProg
#define
  {
    ///< CCX_L2RAM_SuperVminmaxProg399
    399,
    8,
    16,
    0x18B2,
  },
#endif

#ifdef CCX_L2RAM_TWQSTPC
#define
  {
    ///< CCX_L2RAM_TWQSTPC400
    400,
    12,
    0,
    0x18B4,
  },
#endif

#ifdef CCX_L2RAM_TagSTPC
#define
  {
    ///< CCX_L2RAM_TagSTPC401
    401,
    8,
    8,
    0x18B1,
  },
#endif

#ifdef CCX_L3BootSuperVmaxEn
#define
  {
    ///< CCX_L3BootSuperVmaxEn402
    402,
    1,
    28,
    0x1917,
  },
#endif

#ifdef CCX_L3BootSuperVminEn
#define
  {
    ///< CCX_L3BootSuperVminEn403
    403,
    1,
    29,
    0x1917,
  },
#endif

#ifdef CCX_L3FBase0_Reserved
#define
  {
    ///< CCX_L3FBase0_Reserved404
    404,
    2,
    26,
    0x1913,
  },
#endif

#ifdef CCX_L3FBase1_Reserved_15_12
#define
  {
    ///< CCX_L3FBase1_Reserved_15_12405
    405,
    4,
    13,
    0x1915,
  },
#endif

#ifdef CCX_L3FasterThanDF
#define
  {
    ///< CCX_L3FasterThanDF406
    406,
    1,
    27,
    0x185B,
  },
#endif

#ifdef CCX_L3HDSuperVmaxThreshold
#define
  {
    ///< CCX_L3HDSuperVmaxThreshold407
    407,
    4,
    19,
    0x1852,
  },
#endif

#ifdef CCX_L3HDSuperVminThreshold
#define
  {
    ///< CCX_L3HDSuperVminThreshold408
    408,
    4,
    15,
    0x1851,
  },
#endif

#ifdef CCX_L3MCfg
#define
  {
    ///< CCX_L3MCfg409
    409,
    4,
    8,
    0x1915,
  },
#endif

#ifdef CCX_L3MDataCfg0
#define
  {
    ///< CCX_L3MDataCfg0410
    410,
    12,
    0,
    0x1910,
  },
#endif

#ifdef CCX_L3MDataCfg1
#define
  {
    ///< CCX_L3MDataCfg1411
    411,
    10,
    16,
    0x1912,
  },
#endif

#ifdef CCX_L3PllClk0Pdly
#define
  {
    ///< CCX_L3PllClk0Pdly412
    412,
    4,
    8,
    0x1831,
  },
#endif

#ifdef CCX_L3PllClk1Pdly
#define
  {
    ///< CCX_L3PllClk1Pdly413
    413,
    4,
    12,
    0x1831,
  },
#endif

#ifdef CCX_L3PllClk2Pdly
#define
  {
    ///< CCX_L3PllClk2Pdly414
    414,
    4,
    16,
    0x1832,
  },
#endif

#ifdef CCX_L3PllClk3Pdly
#define
  {
    ///< CCX_L3PllClk3Pdly415
    415,
    4,
    20,
    0x1832,
  },
#endif

#ifdef CCX_L3PllClk4Pdly
#define
  {
    ///< CCX_L3PllClk4Pdly416
    416,
    4,
    24,
    0x1833,
  },
#endif

#ifdef CCX_L3PllClkDutyAdj
#define
  {
    ///< CCX_L3PllClkDutyAdj417
    417,
    4,
    28,
    0x1833,
  },
#endif

#ifdef CCX_L3PllDpllCfg3
#define
  {
    ///< CCX_L3PllDpllCfg3418
    418,
    10,
    10,
    0x1849,
  },
#endif

#ifdef CCX_L3PllFllCtl0Enable
#define
  {
    ///< CCX_L3PllFllCtl0Enable419
    419,
    1,
    17,
    0x183A,
  },
#endif

#ifdef CCX_L3PllFllCtl1ClkStretchEn
#define
  {
    ///< CCX_L3PllFllCtl1ClkStretchEn420
    420,
    1,
    1,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1DecMode1
#define
  {
    ///< CCX_L3PllFllCtl1DecMode1421
    421,
    1,
    9,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1DecMode2
#define
  {
    ///< CCX_L3PllFllCtl1DecMode2422
    422,
    1,
    8,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1DecWr
#define
  {
    ///< CCX_L3PllFllCtl1DecWr423
    423,
    1,
    7,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1DroopDetEn
#define
  {
    ///< CCX_L3PllFllCtl1DroopDetEn424
    424,
    1,
    0,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1FllDftDataSel
#define
  {
    ///< CCX_L3PllFllCtl1FllDftDataSel425
    425,
    1,
    4,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1FllNegErrSlope
#define
  {
    ///< CCX_L3PllFllCtl1FllNegErrSlope426
    426,
    2,
    11,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1FllPerfCntrEn
#define
  {
    ///< CCX_L3PllFllCtl1FllPerfCntrEn427
    427,
    1,
    5,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1FllPosErrSlope
#define
  {
    ///< CCX_L3PllFllCtl1FllPosErrSlope428
    428,
    1,
    10,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1FllPwrUpSeqDis
#define
  {
    ///< CCX_L3PllFllCtl1FllPwrUpSeqDis429
    429,
    1,
    6,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1FreqOffsetExp
#define
  {
    ///< CCX_L3PllFllCtl1FreqOffsetExp430
    430,
    4,
    20,
    0x1836,
  },
#endif

#ifdef CCX_L3PllFllCtl1FreqOffsetMant
#define
  {
    ///< CCX_L3PllFllCtl1FreqOffsetMant431
    431,
    5,
    15,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1NctlFreezeCmpSel
#define
  {
    ///< CCX_L3PllFllCtl1NctlFreezeCmpSel432
    432,
    1,
    3,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1NctlFreezeEn
#define
  {
    ///< CCX_L3PllFllCtl1NctlFreezeEn433
    433,
    1,
    2,
    0x1834,
  },
#endif

#ifdef CCX_L3PllFllCtl1StaticStretchBoost
#define
  {
    ///< CCX_L3PllFllCtl1StaticStretchBoost434
    434,
    2,
    13,
    0x1835,
  },
#endif

#ifdef CCX_L3PllFllCtl1StaticStretchEn
#define
  {
    ///< CCX_L3PllFllCtl1StaticStretchEn435
    435,
    5,
    27,
    0x1837,
  },
#endif

#ifdef CCX_L3PllFllCtl1StaticStretchPct
#define
  {
    ///< CCX_L3PllFllCtl1StaticStretchPct436
    436,
    3,
    24,
    0x1837,
  },
#endif

#ifdef CCX_L3PllFllCtl2DecAddr
#define
  {
    ///< CCX_L3PllFllCtl2DecAddr437
    437,
    6,
    18,
    0x183A,
  },
#endif

#ifdef CCX_L3PllFllCtl2DecData
#define
  {
    ///< CCX_L3PllFllCtl2DecData438
    438,
    8,
    24,
    0x183B,
  },
#endif

#ifdef CCX_L3PllFllCtl2EnHighBw
#define
  {
    ///< CCX_L3PllFllCtl2EnHighBw439
    439,
    1,
    4,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl2PllBwBoostEn
#define
  {
    ///< CCX_L3PllFllCtl2PllBwBoostEn440
    440,
    1,
    16,
    0x183A,
  },
#endif

#ifdef CCX_L3PllFllCtl2Rsvd26_16
#define
  {
    ///< CCX_L3PllFllCtl2Rsvd26_16441
    441,
    11,
    5,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl2SelBump
#define
  {
    ///< CCX_L3PllFllCtl2SelBump442
    442,
    1,
    1,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl2SelRladderX
#define
  {
    ///< CCX_L3PllFllCtl2SelRladderX443
    443,
    1,
    2,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl2ShortRcFileX
#define
  {
    ///< CCX_L3PllFllCtl2ShortRcFileX444
    444,
    1,
    0,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl2VrefPwrOn
#define
  {
    ///< CCX_L3PllFllCtl2VrefPwrOn445
    445,
    1,
    3,
    0x1838,
  },
#endif

#ifdef CCX_L3PllFllCtl3AnaobsSel
#define
  {
    ///< CCX_L3PllFllCtl3AnaobsSel446
    446,
    3,
    20,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3DdOutEn
#define
  {
    ///< CCX_L3PllFllCtl3DdOutEn447
    447,
    1,
    23,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3DdSel1
#define
  {
    ///< CCX_L3PllFllCtl3DdSel1448
    448,
    4,
    28,
    0x183F,
  },
#endif

#ifdef CCX_L3PllFllCtl3DdSel2
#define
  {
    ///< CCX_L3PllFllCtl3DdSel2449
    449,
    4,
    24,
    0x183F,
  },
#endif

#ifdef CCX_L3PllFllCtl3Rsvd
#define
  {
    ///< CCX_L3PllFllCtl3Rsvd450
    450,
    1,
    4,
    0x183C,
  },
#endif

#ifdef CCX_L3PllFllCtl3SfEn
#define
  {
    ///< CCX_L3PllFllCtl3SfEn451
    451,
    1,
    19,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsDfxEn
#define
  {
    ///< CCX_L3PllFllCtl3V1CsDfxEn452
    452,
    1,
    16,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsDfxSel
#define
  {
    ///< CCX_L3PllFllCtl3V1CsDfxSel453
    453,
    2,
    8,
    0x183D,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsEn
#define
  {
    ///< CCX_L3PllFllCtl3V1CsEn454
    454,
    1,
    18,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsIbiasSel
#define
  {
    ///< CCX_L3PllFllCtl3V1CsIbiasSel455
    455,
    4,
    0,
    0x183C,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsIoutMode
#define
  {
    ///< CCX_L3PllFllCtl3V1CsIoutMode456
    456,
    1,
    17,
    0x183E,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsIoutSel
#define
  {
    ///< CCX_L3PllFllCtl3V1CsIoutSel457
    457,
    6,
    10,
    0x183D,
  },
#endif

#ifdef CCX_L3PllFllCtl3V1CsIpmosSel
#define
  {
    ///< CCX_L3PllFllCtl3V1CsIpmosSel458
    458,
    3,
    5,
    0x183C,
  },
#endif

#ifdef CCX_L3PllGiCoarseExp
#define
  {
    ///< CCX_L3PllGiCoarseExp459
    459,
    4,
    2,
    0x182C,
  },
#endif

#ifdef CCX_L3PllGiCoarseMant
#define
  {
    ///< CCX_L3PllGiCoarseMant460
    460,
    2,
    0,
    0x182C,
  },
#endif

#ifdef CCX_L3PllGpCoarseExp
#define
  {
    ///< CCX_L3PllGpCoarseExp461
    461,
    4,
    12,
    0x182D,
  },
#endif

#ifdef CCX_L3PllGpCoarseMant
#define
  {
    ///< CCX_L3PllGpCoarseMant462
    462,
    4,
    7,
    0x182C,
  },
#endif

#ifdef CCX_L3PllLockTimer
#define
  {
    ///< CCX_L3PllLockTimer463
    463,
    14,
    18,
    0x182E,
  },
#endif

#ifdef CCX_L3PllRsvd
#define
  {
    ///< CCX_L3PllRsvd464
    464,
    2,
    16,
    0x182E,
  },
#endif

#ifdef CCX_L3PllTdcResolution
#define
  {
    ///< CCX_L3PllTdcResolution465
    465,
    8,
    0,
    0x1830,
  },
#endif

#ifdef CCX_L3ResetDidMargin
#define
  {
    ///< CCX_L3ResetDidMargin466
    466,
    2,
    17,
    0x185A,
  },
#endif

#ifdef CCX_L3SuperVminmaxProg
#define
  {
    ///< CCX_L3SuperVminmaxProg467
    467,
    4,
    12,
    0x1911,
  },
#endif

#ifdef CCX_LSRAM0_FusBstStrenth
#define
  {
    ///< CCX_LSRAM0_FusBstStrenth468
    468,
    2,
    8,
    0x18AD,
  },
#endif

#ifdef CCX_LSRAM0_FusKprEn
#define
  {
    ///< CCX_LSRAM0_FusKprEn469
    469,
    3,
    0,
    0x18AC,
  },
#endif

#ifdef CCX_LSRAM0_FusSblKprEn
#define
  {
    ///< CCX_LSRAM0_FusSblKprEn470
    470,
    1,
    10,
    0x18AD,
  },
#endif

#ifdef CCX_LSRAM0_FusTimAdjBoost
#define
  {
    ///< CCX_LSRAM0_FusTimAdjBoost471
    471,
    3,
    5,
    0x18AC,
  },
#endif

#ifdef CCX_LSRAM0_FusTimAdjPDly
#define
  {
    ///< CCX_LSRAM0_FusTimAdjPDly472
    472,
    2,
    3,
    0x18AC,
  },
#endif

#ifdef CCX_LS_Reserved
#define
  {
    ///< CCX_LS_Reserved473
    473,
    21,
    11,
    0x18AD,
  },
#endif

#ifdef CCX_LowBWConfig
#define
  {
    ///< CCX_LowBWConfig474
    474,
    7,
    0,
    0x1850,
  },
#endif

#ifdef CCX_LowBWConfigUp
#define
  {
    ///< CCX_LowBWConfigUp475
    475,
    7,
    25,
    0x184F,
  },
#endif

#ifdef CCX_LowBWSkewEn
#define
  {
    ///< CCX_LowBWSkewEn476
    476,
    3,
    22,
    0x184E,
  },
#endif

#ifdef CCX_LruCfg
#define
  {
    ///< CCX_LruCfg477
    477,
    11,
    17,
    0x1916,
  },
#endif

#ifdef CCX_MaFddBaseHi
#define
  {
    ///< CCX_MaFddBaseHi478
    478,
    10,
    11,
    0x185D,
  },
#endif

#ifdef CCX_MaFddBaseLo
#define
  {
    ///< CCX_MaFddBaseLo479
    479,
    10,
    1,
    0x185C,
  },
#endif

#ifdef CCX_MeshGatingDis
#define
  {
    ///< CCX_MeshGatingDis480
    480,
    1,
    15,
    0x1859,
  },
#endif

#ifdef CCX_NoExtraCoarseStep
#define
  {
    ///< CCX_NoExtraCoarseStep481
    481,
    1,
    4,
    0x184C,
  },
#endif

#ifdef CCX_PBRAM0_FusBstStrenth
#define
  {
    ///< CCX_PBRAM0_FusBstStrenth482
    482,
    2,
    8,
    0x1895,
  },
#endif

#ifdef CCX_PBRAM0_FusKprEn
#define
  {
    ///< CCX_PBRAM0_FusKprEn483
    483,
    3,
    0,
    0x1894,
  },
#endif

#ifdef CCX_PBRAM0_FusSblKprEn
#define
  {
    ///< CCX_PBRAM0_FusSblKprEn484
    484,
    1,
    10,
    0x1895,
  },
#endif

#ifdef CCX_PBRAM0_FusTimAdjBoost
#define
  {
    ///< CCX_PBRAM0_FusTimAdjBoost485
    485,
    3,
    5,
    0x1894,
  },
#endif

#ifdef CCX_PBRAM0_FusTimAdjPDly
#define
  {
    ///< CCX_PBRAM0_FusTimAdjPDly486
    486,
    2,
    3,
    0x1894,
  },
#endif

#ifdef CCX_PBRAM1_FusBstStrenth
#define
  {
    ///< CCX_PBRAM1_FusBstStrenth487
    487,
    2,
    19,
    0x1896,
  },
#endif

#ifdef CCX_PBRAM1_FusKprEn
#define
  {
    ///< CCX_PBRAM1_FusKprEn488
    488,
    3,
    11,
    0x1895,
  },
#endif

#ifdef CCX_PBRAM1_FusSblKprEn
#define
  {
    ///< CCX_PBRAM1_FusSblKprEn489
    489,
    1,
    21,
    0x1896,
  },
#endif

#ifdef CCX_PBRAM1_FusTimAdjBoost
#define
  {
    ///< CCX_PBRAM1_FusTimAdjBoost490
    490,
    3,
    16,
    0x1896,
  },
#endif

#ifdef CCX_PBRAM1_FusTimAdjPDly
#define
  {
    ///< CCX_PBRAM1_FusTimAdjPDly491
    491,
    2,
    14,
    0x1895,
  },
#endif

#ifdef CCX_PBRAM2_FusBstStrenth
#define
  {
    ///< CCX_PBRAM2_FusBstStrenth492
    492,
    2,
    30,
    0x1897,
  },
#endif

#ifdef CCX_PBRAM2_FusKprEn
#define
  {
    ///< CCX_PBRAM2_FusKprEn493
    493,
    3,
    22,
    0x1896,
  },
#endif

#ifdef CCX_PBRAM2_FusTimAdjBoost
#define
  {
    ///< CCX_PBRAM2_FusTimAdjBoost494
    494,
    3,
    27,
    0x1897,
  },
#endif

#ifdef CCX_PBRAM2_FusTimAdjPDly
#define
  {
    ///< CCX_PBRAM2_FusTimAdjPDly495
    495,
    2,
    25,
    0x1897,
  },
#endif

#ifdef CCX_PGMPGPROPDLY
#define
  {
    ///< CCX_PGMPGPROPDLY496
    496,
    4,
    12,
    0x1885,
  },
#endif

#ifdef CCX_PGMPGRUNDLY
#define
  {
    ///< CCX_PGMPGRUNDLY497
    497,
    8,
    16,
    0x1886,
  },
#endif

#ifdef CCX_PLLRelockForceCoreStrDis
#define
  {
    ///< CCX_PLLRelockForceCoreStrDis498
    498,
    1,
    22,
    0x185A,
  },
#endif

#ifdef CCX_PWROKTOPWRONTIME
#define
  {
    ///< CCX_PWROKTOPWRONTIME499
    499,
    4,
    4,
    0x1884,
  },
#endif

#ifdef CCX_PWRONTOPWROKTIME
#define
  {
    ///< CCX_PWRONTOPWROKTIME500
    500,
    4,
    8,
    0x1885,
  },
#endif

#ifdef CCX_PWRRDYTOPWROKTIME
#define
  {
    ///< CCX_PWRRDYTOPWROKTIME501
    501,
    4,
    0,
    0x1884,
  },
#endif

#ifdef CCX_PdSyncSel
#define
  {
    ///< CCX_PdSyncSel502
    502,
    2,
    0,
    0x184C,
  },
#endif

#ifdef CCX_SCANCLKDIV_1
#define
  {
    ///< CCX_SCANCLKDIV_1503
    503,
    5,
    9,
    0x1889,
  },
#endif

#ifdef CCX_SC_Reserved
#define
  {
    ///< CCX_SC_Reserved504
    504,
    32,
    0,
    0x18A0,
  },
#endif

#ifdef CCX_SOFTREPAIREN_1
#define
  {
    ///< CCX_SOFTREPAIREN_1505
    505,
    1,
    24,
    0x1883,
  },
#endif

#ifdef CCX_STARTUPDFSID
#define
  {
    ///< CCX_STARTUPDFSID506
    506,
    6,
    0,
    0x1880,
  },
#endif

#ifdef CCX_STARTUPIVREN
#define
  {
    ///< CCX_STARTUPIVREN507
    507,
    1,
    20,
    0x1882,
  },
#endif

#ifdef CCX_STARTUPPSMID
#define
  {
    ///< CCX_STARTUPPSMID508
    508,
    14,
    6,
    0x1880,
  },
#endif

#ifdef CCX_STARTUPPSMID_EXT
#define
  {
    ///< CCX_STARTUPPSMID_EXT509
    509,
    18,
    0,
    0x188C,
  },
#endif

#ifdef CCX_STARTUPSTRETCHALLDIV2
#define
  {
    ///< CCX_STARTUPSTRETCHALLDIV2510
    510,
    1,
    8,
    0x1889,
  },
#endif

#ifdef CCX_STARTUPSTRETCHCLKDIV2
#define
  {
    ///< CCX_STARTUPSTRETCHCLKDIV2511
    511,
    1,
    7,
    0x1888,
  },
#endif

#ifdef CCX_STARTUPSTRETCHEN
#define
  {
    ///< CCX_STARTUPSTRETCHEN512
    512,
    1,
    6,
    0x1888,
  },
#endif

#ifdef CCX_STARTUPSUPERVMAXEN
#define
  {
    ///< CCX_STARTUPSUPERVMAXEN513
    513,
    1,
    27,
    0x188B,
  },
#endif

#ifdef CCX_STARTUPSUPERVMINEN
#define
  {
    ///< CCX_STARTUPSUPERVMINEN514
    514,
    1,
    28,
    0x188B,
  },
#endif

#ifdef CCX_STARTUPWLBOOST
#define
  {
    ///< CCX_STARTUPWLBOOST515
    515,
    1,
    14,
    0x1889,
  },
#endif

#ifdef CCX_SampleSize
#define
  {
    ///< CCX_SampleSize516
    516,
    4,
    5,
    0x184C,
  },
#endif

#ifdef CCX_ScanClkDiv_0
#define
  {
    ///< CCX_ScanClkDiv_0517
    517,
    3,
    8,
    0x1855,
  },
#endif

#ifdef CCX_ScndScanToggleDis
#define
  {
    ///< CCX_ScndScanToggleDis518
    518,
    1,
    11,
    0x18B9,
  },
#endif

#ifdef CCX_SlowClkRamp
#define
  {
    ///< CCX_SlowClkRamp519
    519,
    1,
    16,
    0x185A,
  },
#endif

#ifdef CCX_SoftRepairEn_0
#define
  {
    ///< CCX_SoftRepairEn_0520
    520,
    1,
    7,
    0x1854,
  },
#endif

#ifdef CCX_StartupDid
#define
  {
    ///< CCX_StartupDid521
    521,
    6,
    11,
    0x1855,
  },
#endif

#ifdef CCX_StartupFid
#define
  {
    ///< CCX_StartupFid522
    522,
    8,
    0,
    0x1858,
  },
#endif

#ifdef CCX_StretchEn
#define
  {
    ///< CCX_StretchEn523
    523,
    1,
    17,
    0x1856,
  },
#endif

#ifdef CCX_StretchThresh
#define
  {
    ///< CCX_StretchThresh524
    524,
    3,
    15,
    0x184D,
  },
#endif

#ifdef CCX_TagCfg
#define
  {
    ///< CCX_TagCfg525
    525,
    8,
    0,
    0x1914,
  },
#endif

#ifdef CCX_UnstretchThresh
#define
  {
    ///< CCX_UnstretchThresh526
    526,
    5,
    5,
    0x1848,
  },
#endif

#ifdef CCX_VCOPeriodDelay
#define
  {
    ///< CCX_VCOPeriodDelay527
    527,
    3,
    26,
    0x1857,
  },
#endif

#ifdef CCX_WAKEPGASSIGNMENT
#define
  {
    ///< CCX_WAKEPGASSIGNMENT528
    528,
    12,
    15,
    0x1889,
  },
#endif

#ifdef CCX_WARMRESETMBISIEN
#define
  {
    ///< CCX_WARMRESETMBISIEN529
    529,
    1,
    28,
    0x1883,
  },
#endif

#ifdef CCX_WARMRESETMBISTEN
#define
  {
    ///< CCX_WARMRESETMBISTEN530
    530,
    1,
    26,
    0x1883,
  },
#endif

#ifdef CCX_ZEN_RESERVED_0
#define
  {
    ///< CCX_ZEN_RESERVED_0531
    531,
    1,
    21,
    0x1882,
  },
#endif

#ifdef CCX_ZEN_RESERVED_3
#define
  {
    ///< CCX_ZEN_RESERVED_3532
    532,
    8,
    24,
    0x1887,
  },
#endif

#ifdef CCX_ZEN_RESERVED_4
#define
  {
    ///< CCX_ZEN_RESERVED_4533
    533,
    3,
    29,
    0x188B,
  },
#endif

#ifdef CCX_ZEN_RESERVED_5
#define
  {
    ///< CCX_ZEN_RESERVED_5534
    534,
    14,
    18,
    0x188E,
  },
#endif

#ifdef CCX_staticEnable
#define
  {
    ///< CCX_staticEnable535
    535,
    1,
    18,
    0x184E,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk0
#define
  {
    ///< CLK_BootRomCLK0_Did_clk0536
    536,
    7,
    14,
    0x5D20D,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk1
#define
  {
    ///< CLK_BootRomCLK0_Did_clk1537
    537,
    7,
    14,
    0x5D211,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk2
#define
  {
    ///< CLK_BootRomCLK0_Did_clk2538
    538,
    7,
    14,
    0x5D21D,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk3
#define
  {
    ///< CLK_BootRomCLK0_Did_clk3539
    539,
    7,
    21,
    0x5D21E,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk4
#define
  {
    ///< CLK_BootRomCLK0_Did_clk4540
    540,
    7,
    0,
    0x5D220,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk5
#define
  {
    ///< CLK_BootRomCLK0_Did_clk5541
    541,
    7,
    7,
    0x5D220,
  },
#endif

#ifdef CLK_BootRomCLK0_Did_clk6
#define
  {
    ///< CLK_BootRomCLK0_Did_clk6542
    542,
    7,
    14,
    0x5D221,
  },
#endif

#ifdef CLK_BootRomCLK10_Did_clk1
#define
  {
    ///< CLK_BootRomCLK10_Did_clk1543
    543,
    7,
    0,
    0x5D21C,
  },
#endif

#ifdef CLK_BootRomCLK11_Did_clk1
#define
  {
    ///< CLK_BootRomCLK11_Did_clk1544
    544,
    7,
    7,
    0x5D21C,
  },
#endif

#ifdef CLK_BootRomCLK1_Did_clk0
#define
  {
    ///< CLK_BootRomCLK1_Did_clk0545
    545,
    7,
    21,
    0x5D20E,
  },
#endif

#ifdef CLK_BootRomCLK1_Did_clk1
#define
  {
    ///< CLK_BootRomCLK1_Did_clk1546
    546,
    7,
    21,
    0x5D212,
  },
#endif

#ifdef CLK_BootRomCLK2_Did_clk0
#define
  {
    ///< CLK_BootRomCLK2_Did_clk0547
    547,
    7,
    0,
    0x5D210,
  },
#endif

#ifdef CLK_BootRomCLK2_Did_clk1
#define
  {
    ///< CLK_BootRomCLK2_Did_clk1548
    548,
    7,
    0,
    0x5D214,
  },
#endif

#ifdef CLK_BootRomCLK3_Did_clk0
#define
  {
    ///< CLK_BootRomCLK3_Did_clk0549
    549,
    7,
    7,
    0x5D210,
  },
#endif

#ifdef CLK_BootRomCLK3_Did_clk1
#define
  {
    ///< CLK_BootRomCLK3_Did_clk1550
    550,
    7,
    7,
    0x5D214,
  },
#endif

#ifdef CLK_BootRomCLK4_Did_clk1
#define
  {
    ///< CLK_BootRomCLK4_Did_clk1551
    551,
    7,
    14,
    0x5D215,
  },
#endif

#ifdef CLK_BootRomCLK5_Did_clk1
#define
  {
    ///< CLK_BootRomCLK5_Did_clk1552
    552,
    7,
    21,
    0x5D216,
  },
#endif

#ifdef CLK_BootRomCLK6_Did_clk1
#define
  {
    ///< CLK_BootRomCLK6_Did_clk1553
    553,
    7,
    0,
    0x5D218,
  },
#endif

#ifdef CLK_BootRomCLK7_Did_clk1
#define
  {
    ///< CLK_BootRomCLK7_Did_clk1554
    554,
    7,
    7,
    0x5D218,
  },
#endif

#ifdef CLK_BootRomCLK8_Did_clk1
#define
  {
    ///< CLK_BootRomCLK8_Did_clk1555
    555,
    7,
    14,
    0x5D219,
  },
#endif

#ifdef CLK_BootRomCLK9_Did_clk1
#define
  {
    ///< CLK_BootRomCLK9_Did_clk1556
    556,
    7,
    21,
    0x5D21A,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk0
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk0557
    557,
    1,
    30,
    0x5D1DB,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk1
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk1558
    558,
    1,
    30,
    0x5D1DF,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk2
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk2559
    559,
    1,
    30,
    0x5D1E3,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk3
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk3560
    560,
    1,
    30,
    0x5D1E7,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk4
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk4561
    561,
    1,
    30,
    0x5D1EB,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk5
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk5562
    562,
    1,
    30,
    0x5D1EF,
  },
#endif

#ifdef CLK_Bypass_ADFS_DS_clk6
#define
  {
    ///< CLK_Bypass_ADFS_DS_clk6563
    563,
    1,
    30,
    0x5D1F3,
  },
#endif

#ifdef CLK_ClkSpare_0
#define
  {
    ///< CLK_ClkSpare_0564
    564,
    1,
    31,
    0x5D1DB,
  },
#endif

#ifdef CLK_ClkSpare_1
#define
  {
    ///< CLK_ClkSpare_1565
    565,
    1,
    31,
    0x5D1DF,
  },
#endif

#ifdef CLK_ClkSpare_10
#define
  {
    ///< CLK_ClkSpare_10566
    566,
    4,
    28,
    0x5D203,
  },
#endif

#ifdef CLK_ClkSpare_11
#define
  {
    ///< CLK_ClkSpare_11567
    567,
    4,
    28,
    0x5D207,
  },
#endif

#ifdef CLK_ClkSpare_12
#define
  {
    ///< CLK_ClkSpare_12568
    568,
    4,
    28,
    0x5D20B,
  },
#endif

#ifdef CLK_ClkSpare_13
#define
  {
    ///< CLK_ClkSpare_13569
    569,
    4,
    28,
    0x5D20F,
  },
#endif

#ifdef CLK_ClkSpare_14
#define
  {
    ///< CLK_ClkSpare_14570
    570,
    4,
    28,
    0x5D213,
  },
#endif

#ifdef CLK_ClkSpare_15
#define
  {
    ///< CLK_ClkSpare_15571
    571,
    4,
    28,
    0x5D217,
  },
#endif

#ifdef CLK_ClkSpare_16
#define
  {
    ///< CLK_ClkSpare_16572
    572,
    4,
    28,
    0x5D21B,
  },
#endif

#ifdef CLK_ClkSpare_17
#define
  {
    ///< CLK_ClkSpare_17573
    573,
    4,
    28,
    0x5D21F,
  },
#endif

#ifdef CLK_ClkSpare_18
#define
  {
    ///< CLK_ClkSpare_18574
    574,
    11,
    21,
    0x5D222,
  },
#endif

#ifdef CLK_ClkSpare_2
#define
  {
    ///< CLK_ClkSpare_2575
    575,
    1,
    31,
    0x5D1E3,
  },
#endif

#ifdef CLK_ClkSpare_3
#define
  {
    ///< CLK_ClkSpare_3576
    576,
    1,
    31,
    0x5D1E7,
  },
#endif

#ifdef CLK_ClkSpare_4
#define
  {
    ///< CLK_ClkSpare_4577
    577,
    1,
    31,
    0x5D1EB,
  },
#endif

#ifdef CLK_ClkSpare_5
#define
  {
    ///< CLK_ClkSpare_5578
    578,
    1,
    31,
    0x5D1EF,
  },
#endif

#ifdef CLK_ClkSpare_6
#define
  {
    ///< CLK_ClkSpare_6579
    579,
    1,
    31,
    0x5D1F3,
  },
#endif

#ifdef CLK_ClkSpare_7
#define
  {
    ///< CLK_ClkSpare_7580
    580,
    2,
    30,
    0x5D1F7,
  },
#endif

#ifdef CLK_ClkSpare_8
#define
  {
    ///< CLK_ClkSpare_8581
    581,
    4,
    28,
    0x5D1FB,
  },
#endif

#ifdef CLK_ClkSpare_9
#define
  {
    ///< CLK_ClkSpare_9582
    582,
    2,
    30,
    0x5D1FF,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk0
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk0583
    583,
    1,
    22,
    0x5D1DA,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk1
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk1584
    584,
    1,
    22,
    0x5D1DE,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk2
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk2585
    585,
    1,
    22,
    0x5D1E2,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk3
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk3586
    586,
    1,
    22,
    0x5D1E6,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk4
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk4587
    587,
    1,
    22,
    0x5D1EA,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk5
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk5588
    588,
    1,
    22,
    0x5D1EE,
  },
#endif

#ifdef CLK_FUSES_ARE_VALID_clk6
#define
  {
    ///< CLK_FUSES_ARE_VALID_clk6589
    589,
    1,
    22,
    0x5D1F2,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk0
#define
  {
    ///< CLK_MainPllDidStartup_clk0590
    590,
    4,
    9,
    0x5D1D9,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk1
#define
  {
    ///< CLK_MainPllDidStartup_clk1591
    591,
    4,
    9,
    0x5D1DD,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk2
#define
  {
    ///< CLK_MainPllDidStartup_clk2592
    592,
    4,
    9,
    0x5D1E1,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk3
#define
  {
    ///< CLK_MainPllDidStartup_clk3593
    593,
    4,
    9,
    0x5D1E5,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk4
#define
  {
    ///< CLK_MainPllDidStartup_clk4594
    594,
    4,
    9,
    0x5D1E9,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk5
#define
  {
    ///< CLK_MainPllDidStartup_clk5595
    595,
    4,
    9,
    0x5D1ED,
  },
#endif

#ifdef CLK_MainPllDidStartup_clk6
#define
  {
    ///< CLK_MainPllDidStartup_clk6596
    596,
    4,
    9,
    0x5D1F1,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk0
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk0597
    597,
    4,
    18,
    0x5D1DA,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk1
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk1598
    598,
    4,
    18,
    0x5D1DE,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk2
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk2599
    599,
    4,
    18,
    0x5D1E2,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk3
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk3600
    600,
    4,
    18,
    0x5D1E6,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk4
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk4601
    601,
    4,
    18,
    0x5D1EA,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk5
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk5602
    602,
    4,
    18,
    0x5D1EE,
  },
#endif

#ifdef CLK_MainPllMiscFuseCtrl_clk6
#define
  {
    ///< CLK_MainPllMiscFuseCtrl_clk6603
    603,
    4,
    18,
    0x5D1F2,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk0
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk0604
    604,
    9,
    0,
    0x5D1D8,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk1
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk1605
    605,
    9,
    0,
    0x5D1DC,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk2
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk2606
    606,
    9,
    0,
    0x5D1E0,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk3
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk3607
    607,
    9,
    0,
    0x5D1E4,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk4
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk4608
    608,
    9,
    0,
    0x5D1E8,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk5
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk5609
    609,
    9,
    0,
    0x5D1EC,
  },
#endif

#ifdef CLK_MainPllOpFreqIdStartup_clk6
#define
  {
    ///< CLK_MainPllOpFreqIdStartup_clk6610
    610,
    9,
    0,
    0x5D1F0,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk0
#define
  {
    ///< CLK_MainPllRladTapSel_clk0611
    611,
    5,
    13,
    0x5D1D9,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk1
#define
  {
    ///< CLK_MainPllRladTapSel_clk1612
    612,
    5,
    13,
    0x5D1DD,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk2
#define
  {
    ///< CLK_MainPllRladTapSel_clk2613
    613,
    5,
    13,
    0x5D1E1,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk3
#define
  {
    ///< CLK_MainPllRladTapSel_clk3614
    614,
    5,
    13,
    0x5D1E5,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk4
#define
  {
    ///< CLK_MainPllRladTapSel_clk4615
    615,
    5,
    13,
    0x5D1E9,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk5
#define
  {
    ///< CLK_MainPllRladTapSel_clk5616
    616,
    5,
    13,
    0x5D1ED,
  },
#endif

#ifdef CLK_MainPllRladTapSel_clk6
#define
  {
    ///< CLK_MainPllRladTapSel_clk6617
    617,
    5,
    13,
    0x5D1F1,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_EXP_bin1
#define
  {
    ///< CLK_SPLL_GI_COARSE_EXP_bin1618
    618,
    4,
    8,
    0x5D1F5,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_EXP_bin2
#define
  {
    ///< CLK_SPLL_GI_COARSE_EXP_bin2619
    619,
    4,
    0,
    0x5D1F8,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_EXP_bin3
#define
  {
    ///< CLK_SPLL_GI_COARSE_EXP_bin3620
    620,
    4,
    22,
    0x5D1FA,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_EXP_bin4
#define
  {
    ///< CLK_SPLL_GI_COARSE_EXP_bin4621
    621,
    4,
    16,
    0x5D1FE,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_MANT_bin1
#define
  {
    ///< CLK_SPLL_GI_COARSE_MANT_bin1622
    622,
    2,
    12,
    0x5D1F5,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_MANT_bin2
#define
  {
    ///< CLK_SPLL_GI_COARSE_MANT_bin2623
    623,
    2,
    4,
    0x5D1F8,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_MANT_bin3
#define
  {
    ///< CLK_SPLL_GI_COARSE_MANT_bin3624
    624,
    2,
    26,
    0x5D1FB,
  },
#endif

#ifdef CLK_SPLL_GI_COARSE_MANT_bin4
#define
  {
    ///< CLK_SPLL_GI_COARSE_MANT_bin4625
    625,
    2,
    20,
    0x5D1FE,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_EXP_bin1
#define
  {
    ///< CLK_SPLL_GP_COARSE_EXP_bin1626
    626,
    4,
    0,
    0x5D1F4,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_EXP_bin2
#define
  {
    ///< CLK_SPLL_GP_COARSE_EXP_bin2627
    627,
    4,
    22,
    0x5D1F6,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_EXP_bin3
#define
  {
    ///< CLK_SPLL_GP_COARSE_EXP_bin3628
    628,
    4,
    14,
    0x5D1F9,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_EXP_bin4
#define
  {
    ///< CLK_SPLL_GP_COARSE_EXP_bin4629
    629,
    4,
    8,
    0x5D1FD,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_MANT_bin1
#define
  {
    ///< CLK_SPLL_GP_COARSE_MANT_bin1630
    630,
    4,
    4,
    0x5D1F4,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_MANT_bin2
#define
  {
    ///< CLK_SPLL_GP_COARSE_MANT_bin2631
    631,
    4,
    26,
    0x5D1F7,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_MANT_bin3
#define
  {
    ///< CLK_SPLL_GP_COARSE_MANT_bin3632
    632,
    4,
    18,
    0x5D1FA,
  },
#endif

#ifdef CLK_SPLL_GP_COARSE_MANT_bin4
#define
  {
    ///< CLK_SPLL_GP_COARSE_MANT_bin4633
    633,
    4,
    12,
    0x5D1FD,
  },
#endif

#ifdef CLK_SPLL_TDC_RESOLUTION_bin1
#define
  {
    ///< CLK_SPLL_TDC_RESOLUTION_bin1634
    634,
    8,
    14,
    0x5D1F5,
  },
#endif

#ifdef CLK_SPLL_TDC_RESOLUTION_bin2
#define
  {
    ///< CLK_SPLL_TDC_RESOLUTION_bin2635
    635,
    8,
    6,
    0x5D1F8,
  },
#endif

#ifdef CLK_SPLL_TDC_RESOLUTION_bin3
#define
  {
    ///< CLK_SPLL_TDC_RESOLUTION_bin3636
    636,
    8,
    0,
    0x5D1FC,
  },
#endif

#ifdef CLK_SPLL_TDC_RESOLUTION_bin4
#define
  {
    ///< CLK_SPLL_TDC_RESOLUTION_bin4637
    637,
    8,
    22,
    0x5D1FE,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk0
#define
  {
    ///< CLK_StartupCLK0_Did_clk0638
    638,
    7,
    23,
    0x5D1DA,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk1
#define
  {
    ///< CLK_StartupCLK0_Did_clk1639
    639,
    7,
    23,
    0x5D1DE,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk2
#define
  {
    ///< CLK_StartupCLK0_Did_clk2640
    640,
    7,
    23,
    0x5D1E2,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk3
#define
  {
    ///< CLK_StartupCLK0_Did_clk3641
    641,
    7,
    23,
    0x5D1E6,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk4
#define
  {
    ///< CLK_StartupCLK0_Did_clk4642
    642,
    7,
    23,
    0x5D1EA,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk5
#define
  {
    ///< CLK_StartupCLK0_Did_clk5643
    643,
    7,
    23,
    0x5D1EE,
  },
#endif

#ifdef CLK_StartupCLK0_Did_clk6
#define
  {
    ///< CLK_StartupCLK0_Did_clk6644
    644,
    7,
    23,
    0x5D1F2,
  },
#endif

#ifdef CLK_StartupCLK10_Did_clk1
#define
  {
    ///< CLK_StartupCLK10_Did_clk1645
    645,
    7,
    0,
    0x5D20C,
  },
#endif

#ifdef CLK_StartupCLK11_Did_clk1
#define
  {
    ///< CLK_StartupCLK11_Did_clk1646
    646,
    7,
    7,
    0x5D20C,
  },
#endif

#ifdef CLK_StartupCLK1_Did_clk0
#define
  {
    ///< CLK_StartupCLK1_Did_clk0647
    647,
    7,
    0,
    0x5D200,
  },
#endif

#ifdef CLK_StartupCLK1_Did_clk1
#define
  {
    ///< CLK_StartupCLK1_Did_clk1648
    648,
    7,
    21,
    0x5D202,
  },
#endif

#ifdef CLK_StartupCLK2_Did_clk0
#define
  {
    ///< CLK_StartupCLK2_Did_clk0649
    649,
    7,
    7,
    0x5D200,
  },
#endif

#ifdef CLK_StartupCLK2_Did_clk1
#define
  {
    ///< CLK_StartupCLK2_Did_clk1650
    650,
    7,
    0,
    0x5D204,
  },
#endif

#ifdef CLK_StartupCLK3_Did_clk0
#define
  {
    ///< CLK_StartupCLK3_Did_clk0651
    651,
    7,
    14,
    0x5D201,
  },
#endif

#ifdef CLK_StartupCLK3_Did_clk1
#define
  {
    ///< CLK_StartupCLK3_Did_clk1652
    652,
    7,
    7,
    0x5D204,
  },
#endif

#ifdef CLK_StartupCLK4_Did_clk1
#define
  {
    ///< CLK_StartupCLK4_Did_clk1653
    653,
    7,
    14,
    0x5D205,
  },
#endif

#ifdef CLK_StartupCLK5_Did_clk1
#define
  {
    ///< CLK_StartupCLK5_Did_clk1654
    654,
    7,
    21,
    0x5D206,
  },
#endif

#ifdef CLK_StartupCLK6_Did_clk1
#define
  {
    ///< CLK_StartupCLK6_Did_clk1655
    655,
    7,
    0,
    0x5D208,
  },
#endif

#ifdef CLK_StartupCLK7_Did_clk1
#define
  {
    ///< CLK_StartupCLK7_Did_clk1656
    656,
    7,
    7,
    0x5D208,
  },
#endif

#ifdef CLK_StartupCLK8_Did_clk1
#define
  {
    ///< CLK_StartupCLK8_Did_clk1657
    657,
    7,
    14,
    0x5D209,
  },
#endif

#ifdef CLK_StartupCLK9_Did_clk1
#define
  {
    ///< CLK_StartupCLK9_Did_clk1658
    658,
    7,
    21,
    0x5D20A,
  },
#endif

#ifdef DFX_DFX_PUB_SPARE_FUSES
#define
  {
    ///< DFX_DFX_PUB_SPARE_FUSES659
    659,
    26,
    6,
    0x5D22C,
  },
#endif

#ifdef DFX_DFX_WRITE_DISABLE
#define
  {
    ///< DFX_DFX_WRITE_DISABLE660
    660,
    1,
    0,
    0x5D228,
  },
#endif

#ifdef DFX_FUSE_CCD_Down
#define
  {
    ///< DFX_FUSE_CCD_Down661
    661,
    8,
    30,
    0x5D22B,
  },
#endif

#ifdef DFX_FUSE_CCD_Present
#define
  {
    ///< DFX_FUSE_CCD_Present662
    662,
    8,
    22,
    0x5D22A,
  },
#endif

#ifdef DFX_FUSE_IDCodeFused
#define
  {
    ///< DFX_FUSE_IDCodeFused663
    663,
    1,
    1,
    0x5D228,
  },
#endif

#ifdef DFX_FUSE_IDCodePartNumber
#define
  {
    ///< DFX_FUSE_IDCodePartNumber664
    664,
    16,
    6,
    0x5D228,
  },
#endif

#ifdef DFX_FUSE_IDCodeVersion
#define
  {
    ///< DFX_FUSE_IDCodeVersion665
    665,
    4,
    2,
    0x5D228,
  },
#endif

#ifdef DF_DF_GROUP0_DATA
#define
  {
    ///< DF_DF_GROUP0_DATA666
    666,
    288,
    0,
    0x5D714,
  },
#endif

#ifdef DF_DF_GROUP1_DATA
#define
  {
    ///< DF_DF_GROUP1_DATA667
    667,
    288,
    0,
    0x5D738,
  },
#endif

#ifdef DF_DF_GROUP2_DATA
#define
  {
    ///< DF_DF_GROUP2_DATA668
    668,
    288,
    0,
    0x5D75C,
  },
#endif

#ifdef DF_DF_GROUP3_DATA
#define
  {
    ///< DF_DF_GROUP3_DATA669
    669,
    288,
    0,
    0x5D780,
  },
#endif

#ifdef DF_DF_GROUP4_DATA
#define
  {
    ///< DF_DF_GROUP4_DATA670
    670,
    160,
    0,
    0x5D7A4,
  },
#endif

#ifdef DF_DF_GROUP5_DATA
#define
  {
    ///< DF_DF_GROUP5_DATA671
    671,
    160,
    0,
    0x5D7B8,
  },
#endif

#ifdef DF_DF_WRITE_DISABLE
#define
  {
    ///< DF_DF_WRITE_DISABLE672
    672,
    1,
    30,
    0x5D227,
  },
#endif

#ifdef DF_Spare
#define
  {
    ///< DF_Spare673
    673,
    30,
    0,
    0x5D224,
  },
#endif

#ifdef DF_SpfDis
#define
  {
    ///< DF_SpfDis674
    674,
    1,
    31,
    0x5D227,
  },
#endif

#ifdef FCH_FCH_GROUP0_DATA
#define
  {
    ///< FCH_FCH_GROUP0_DATA675
    675,
    64,
    0,
    0x5D70C,
  },
#endif

#ifdef FCH_FCH_WRITE_DISABLE
#define
  {
    ///< FCH_FCH_WRITE_DISABLE676
    676,
    1,
    31,
    0x5D233,
  },
#endif

#ifdef FCH_fch_fuse
#define
  {
    ///< FCH_fch_fuse677
    677,
    31,
    0,
    0x5D230,
  },
#endif

#ifdef FUSE_Attestation_SEED_LOCK
#define
  {
    ///< FUSE_Attestation_SEED_LOCK678
    678,
    3,
    0,
    0x5D070,
  },
#endif

#ifdef FUSE_CCD_FUSE_CCD_GROUP0_DATA
#define
  {
    ///< FUSE_CCD_FUSE_CCD_GROUP0_DATA679
    679,
    32,
    0,
    0x1BA0,
  },
#endif

#ifdef FUSE_CCD_PEO_RSV
#define
  {
    ///< FUSE_CCD_PEO_RSV680
    680,
    32,
    0,
    0x1A24,
  },
#endif

#ifdef FUSE_CCD_SpareFuse3
#define
  {
    ///< FUSE_CCD_SpareFuse3681
    681,
    12,
    20,
    0x1A22,
  },
#endif

#ifdef FUSE_CCD_replace_start
#define
  {
    ///< FUSE_CCD_replace_start682
    682,
    20,
    0,
    0x1A20,
  },
#endif

#ifdef FUSE_CUSTOMER_KEY_LOCK
#define
  {
    ///< FUSE_CUSTOMER_KEY_LOCK683
    683,
    3,
    0,
    0x5D06C,
  },
#endif

#ifdef FUSE_FUSE_GROUP0_DATA
#define
  {
    ///< FUSE_FUSE_GROUP0_DATA684
    684,
    32,
    0,
    0x5D7CC,
  },
#endif

#ifdef FUSE_PEO_RSV
#define
  {
    ///< FUSE_PEO_RSV685
    685,
    32,
    0,
    0x5D134,
  },
#endif

#ifdef FUSE_REPAIR_Spare_Repair
#define
  {
    ///< FUSE_REPAIR_Spare_Repair686
    686,
    13216,
    0,
    0x5D98C,
  },
#endif

#ifdef FUSE_SpareFuse1
#define
  {
    ///< FUSE_SpareFuse1687
    687,
    9,
    23,
    0x5D06E,
  },
#endif

#ifdef FUSE_SpareFuse2
#define
  {
    ///< FUSE_SpareFuse2688
    688,
    9,
    23,
    0x5D072,
  },
#endif

#ifdef FUSE_SpareFuse3
#define
  {
    ///< FUSE_SpareFuse3689
    689,
    12,
    20,
    0x5D132,
  },
#endif

#ifdef FUSE_attestation_seed_replace_start
#define
  {
    ///< FUSE_attestation_seed_replace_start690
    690,
    20,
    3,
    0x5D070,
  },
#endif

#ifdef FUSE_customer_key_replace_start
#define
  {
    ///< FUSE_customer_key_replace_start691
    691,
    20,
    3,
    0x5D06C,
  },
#endif

#ifdef FUSE_replace_start
#define
  {
    ///< FUSE_replace_start692
    692,
    20,
    0,
    0x5D130,
  },
#endif

#ifdef GMI2_PCS_CCD_GMI2_PCS_CCD_PUB_SPARE_FUSES
#define
  {
    ///< GMI2_PCS_CCD_GMI2_PCS_CCD_PUB_SPARE_FUSES693
    693,
    2,
    30,
    0x1A33,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1694
    694,
    29,
    3,
    0x1A2C,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_DisableFunction
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_DisableFunction695
    695,
    1,
    1,
    0x1A2C,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_ReadySerialBypass
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_ReadySerialBypass696
    696,
    1,
    2,
    0x1A2C,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_WriteDisable
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_EFUSE1_WriteDisable697
    697,
    1,
    0,
    0x1A2C,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HINIT
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HINIT698
    698,
    31,
    1,
    0x1A28,
  },
#endif

#ifdef GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HWinitComplete
#define
  {
    ///< GMI2_PCS_CCD_MINI_GMI2_SLAVE_PCS_HWinitComplete699
    699,
    1,
    0,
    0x1A28,
  },
#endif

#ifdef GMI2_PCS_CCD_twix_ccd_SPARE0
#define
  {
    ///< GMI2_PCS_CCD_twix_ccd_SPARE0700
    700,
    1,
    0,
    0x1A30,
  },
#endif

#ifdef GMI2_PCS_CCD_twix_ccd_SPARE1
#define
  {
    ///< GMI2_PCS_CCD_twix_ccd_SPARE1701
    701,
    1,
    1,
    0x1A30,
  },
#endif

#ifdef GMI2_PCS_CCD_twix_ccd_SPARE2
#define
  {
    ///< GMI2_PCS_CCD_twix_ccd_SPARE2702
    702,
    13,
    2,
    0x1A30,
  },
#endif

#ifdef GMI2_PCS_CCD_twix_ccd_SPARE3
#define
  {
    ///< GMI2_PCS_CCD_twix_ccd_SPARE3703
    703,
    15,
    15,
    0x1A31,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1704
    704,
    29,
    3,
    0x5D238,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_DisableFunction
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_DisableFunction705
    705,
    1,
    1,
    0x5D238,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_ReadySerialBypass
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_ReadySerialBypass706
    706,
    1,
    2,
    0x5D238,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_WriteDisable
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_EFUSE1_WriteDisable707
    707,
    1,
    0,
    0x5D238,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HINIT
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HINIT708
    708,
    31,
    1,
    0x5D234,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HWinitComplete
#define
  {
    ///< GMI2_PCS_IOD_GMI2_MINI_MASTER_PCS_HWinitComplete709
    709,
    1,
    0,
    0x5D234,
  },
#endif

#ifdef GMI2_PCS_IOD_GMI2_PCS_IOD_PUB_SPARE_FUSES
#define
  {
    ///< GMI2_PCS_IOD_GMI2_PCS_IOD_PUB_SPARE_FUSES710
    710,
    2,
    30,
    0x5D23F,
  },
#endif

#ifdef GMI2_PCS_IOD_twix_iod_SPARE0
#define
  {
    ///< GMI2_PCS_IOD_twix_iod_SPARE0711
    711,
    15,
    0,
    0x5D23C,
  },
#endif

#ifdef GMI2_PCS_IOD_twix_iod_SPARE1
#define
  {
    ///< GMI2_PCS_IOD_twix_iod_SPARE1712
    712,
    1,
    15,
    0x5D23D,
  },
#endif

#ifdef GMI2_PCS_IOD_twix_iod_SPARE2
#define
  {
    ///< GMI2_PCS_IOD_twix_iod_SPARE2713
    713,
    14,
    16,
    0x5D23E,
  },
#endif

#ifdef GMI_PCS_GMI_PCS_PUB_SPARE_FUSES
#define
  {
    ///< GMI_PCS_GMI_PCS_PUB_SPARE_FUSES714
    714,
    3,
    29,
    0x5D283,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_1
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_1715
    715,
    1,
    0,
    0x5D240,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_10
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_10716
    716,
    32,
    0,
    0x5D258,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_11
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_11717
    717,
    1,
    0,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_12
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_12718
    718,
    1,
    1,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_13
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_13719
    719,
    1,
    2,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_14
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_14720
    720,
    1,
    3,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_15
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_15721
    721,
    1,
    4,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_16
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_16722
    722,
    3,
    5,
    0x5D25C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_17
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_17723
    723,
    2,
    8,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_18
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_18724
    724,
    1,
    10,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_19
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_19725
    725,
    2,
    11,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_2
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_2726
    726,
    1,
    1,
    0x5D240,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_20
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_20727
    727,
    1,
    13,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_21
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_21728
    728,
    1,
    14,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_22
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_22729
    729,
    6,
    15,
    0x5D25D,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_23
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_23730
    730,
    1,
    21,
    0x5D25E,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_24
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_24731
    731,
    5,
    22,
    0x5D25E,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_25
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_25732
    732,
    1,
    27,
    0x5D25F,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_26
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_26733
    733,
    3,
    28,
    0x5D25F,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_27
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_27734
    734,
    1,
    31,
    0x5D25F,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_28
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_28735
    735,
    10,
    0,
    0x5D260,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_29
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_29736
    736,
    1,
    10,
    0x5D261,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_3
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_3737
    737,
    31,
    2,
    0x5D240,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_30
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_30738
    738,
    10,
    11,
    0x5D261,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_31
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_31739
    739,
    1,
    21,
    0x5D262,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_32
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_32740
    740,
    5,
    22,
    0x5D262,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_33
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_33741
    741,
    3,
    27,
    0x5D263,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_34
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_34742
    742,
    2,
    30,
    0x5D263,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_35
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_35743
    743,
    11,
    0,
    0x5D264,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_36
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_36744
    744,
    1,
    11,
    0x5D265,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_37
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_37745
    745,
    3,
    12,
    0x5D265,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_38
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_38746
    746,
    1,
    15,
    0x5D265,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_39
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_39747
    747,
    3,
    16,
    0x5D266,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_4
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_4748
    748,
    1,
    1,
    0x5D244,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_40
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_40749
    749,
    5,
    19,
    0x5D266,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_41
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_41750
    750,
    1,
    24,
    0x5D267,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_42
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_42751
    751,
    1,
    25,
    0x5D267,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_43
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_43752
    752,
    3,
    26,
    0x5D267,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_44
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_44753
    753,
    3,
    29,
    0x5D267,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_45
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_45754
    754,
    4,
    0,
    0x5D268,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_46
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_46755
    755,
    1,
    4,
    0x5D268,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_47
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_47756
    756,
    8,
    5,
    0x5D268,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_48
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_48757
    757,
    1,
    13,
    0x5D269,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_49
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_49758
    758,
    1,
    14,
    0x5D269,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_5
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_5759
    759,
    31,
    2,
    0x5D244,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_50
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_50760
    760,
    14,
    15,
    0x5D269,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_51
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_51761
    761,
    32,
    29,
    0x5D26B,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_52
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_52762
    762,
    32,
    29,
    0x5D26F,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_53
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_53763
    763,
    32,
    29,
    0x5D273,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_54
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_54764
    764,
    32,
    29,
    0x5D277,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_55
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_55765
    765,
    32,
    29,
    0x5D27B,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_56
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_56766
    766,
    32,
    29,
    0x5D27F,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_6
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_6767
    767,
    31,
    1,
    0x5D248,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_7
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_7768
    768,
    32,
    0,
    0x5D24C,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_8
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_8769
    769,
    32,
    0,
    0x5D250,
  },
#endif

#ifdef GMI_PCS_SPARE_EFUSE_9
#define
  {
    ///< GMI_PCS_SPARE_EFUSE_9770
    770,
    32,
    0,
    0x5D254,
  },
#endif

#ifdef IOHC0_ECC_Disable
#define
  {
    ///< IOHC0_ECC_Disable771
    771,
    1,
    24,
    0x5D287,
  },
#endif

#ifdef IOHC0_IOHC_PCIE_Bridge_Disable
#define
  {
    ///< IOHC0_IOHC_PCIE_Bridge_Disable772
    772,
    24,
    0,
    0x5D284,
  },
#endif

#ifdef IOHC0_IOHC_PUB_SPARE_FUSES
#define
  {
    ///< IOHC0_IOHC_PUB_SPARE_FUSES773
    773,
    6,
    26,
    0x5D287,
  },
#endif

#ifdef IOHC0_IOHC_WRITE_DISABLE
#define
  {
    ///< IOHC0_IOHC_WRITE_DISABLE774
    774,
    1,
    25,
    0x5D287,
  },
#endif

#ifdef IOHC1_ECC_Disable
#define
  {
    ///< IOHC1_ECC_Disable775
    775,
    1,
    24,
    0x5D28B,
  },
#endif

#ifdef IOHC1_IOHC_PCIE_Bridge_Disable
#define
  {
    ///< IOHC1_IOHC_PCIE_Bridge_Disable776
    776,
    24,
    0,
    0x5D288,
  },
#endif

#ifdef IOHC1_IOHC_PUB_SPARE_FUSES
#define
  {
    ///< IOHC1_IOHC_PUB_SPARE_FUSES777
    777,
    6,
    26,
    0x5D28B,
  },
#endif

#ifdef IOHC1_IOHC_WRITE_DISABLE
#define
  {
    ///< IOHC1_IOHC_WRITE_DISABLE778
    778,
    1,
    25,
    0x5D28B,
  },
#endif

#ifdef IOHC2_ECC_Disable
#define
  {
    ///< IOHC2_ECC_Disable779
    779,
    1,
    24,
    0x5D28F,
  },
#endif

#ifdef IOHC2_IOHC_PCIE_Bridge_Disable
#define
  {
    ///< IOHC2_IOHC_PCIE_Bridge_Disable780
    780,
    24,
    0,
    0x5D28C,
  },
#endif

#ifdef IOHC2_IOHC_PUB_SPARE_FUSES
#define
  {
    ///< IOHC2_IOHC_PUB_SPARE_FUSES781
    781,
    6,
    26,
    0x5D28F,
  },
#endif

#ifdef IOHC2_IOHC_WRITE_DISABLE
#define
  {
    ///< IOHC2_IOHC_WRITE_DISABLE782
    782,
    1,
    25,
    0x5D28F,
  },
#endif

#ifdef IOHC3_ECC_Disable
#define
  {
    ///< IOHC3_ECC_Disable783
    783,
    1,
    24,
    0x5D293,
  },
#endif

#ifdef IOHC3_IOHC_PCIE_Bridge_Disable
#define
  {
    ///< IOHC3_IOHC_PCIE_Bridge_Disable784
    784,
    24,
    0,
    0x5D290,
  },
#endif

#ifdef IOHC3_IOHC_PUB_SPARE_FUSES
#define
  {
    ///< IOHC3_IOHC_PUB_SPARE_FUSES785
    785,
    6,
    26,
    0x5D293,
  },
#endif

#ifdef IOHC3_IOHC_WRITE_DISABLE
#define
  {
    ///< IOHC3_IOHC_WRITE_DISABLE786
    786,
    1,
    25,
    0x5D293,
  },
#endif

#ifdef MP0_ATTESTATION_SEED
#define
  {
    ///< MP0_ATTESTATION_SEED787
    787,
    416,
    0,
    0x5D0C4,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM788
    788,
    32,
    0,
    0x5D120,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM_1
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM_1789
    789,
    32,
    0,
    0x5D124,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM_2
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM_2790
    790,
    32,
    0,
    0x5D128,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM_VALID
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM_VALID791
    791,
    1,
    21,
    0x5D0FA,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM_VALID_1
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM_VALID_1792
    792,
    1,
    22,
    0x5D0FA,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_CHECKSUM_VALID_2
#define
  {
    ///< MP0_ATTESTATION_SEED_CHECKSUM_VALID_2793
    793,
    1,
    23,
    0x5D0FA,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_ECC_EN
#define
  {
    ///< MP0_ATTESTATION_SEED_ECC_EN794
    794,
    1,
    18,
    0x5D0FA,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_ECC_EN_1
#define
  {
    ///< MP0_ATTESTATION_SEED_ECC_EN_1795
    795,
    1,
    19,
    0x5D0FA,
  },
#endif

#ifdef MP0_ATTESTATION_SEED_ECC_EN_2
#define
  {
    ///< MP0_ATTESTATION_SEED_ECC_EN_2796
    796,
    1,
    20,
    0x5D0FA,
  },
#endif

#ifdef MP0_AUDIO_AZ_HARVEST
#define
  {
    ///< MP0_AUDIO_AZ_HARVEST797
    797,
    1,
    0,
    0x5D140,
  },
#endif

#ifdef MP0_BIOS_KEY_ID
#define
  {
    ///< MP0_BIOS_KEY_ID798
    798,
    16,
    0,
    0x5D108,
  },
#endif

#ifdef MP0_BIOS_KEY_ID_1
#define
  {
    ///< MP0_BIOS_KEY_ID_1799
    799,
    16,
    16,
    0x5D10A,
  },
#endif

#ifdef MP0_BIOS_KEY_ID_2
#define
  {
    ///< MP0_BIOS_KEY_ID_2800
    800,
    16,
    0,
    0x5D10C,
  },
#endif

#ifdef MP0_CLDO_GMI2_BYPASS_DIS
#define
  {
    ///< MP0_CLDO_GMI2_BYPASS_DIS801
    801,
    1,
    23,
    0x5D152,
  },
#endif

#ifdef MP0_CLDO_GMI2_SEL_SRC_VDDIO_MEM
#define
  {
    ///< MP0_CLDO_GMI2_SEL_SRC_VDDIO_MEM802
    802,
    1,
    24,
    0x5D153,
  },
#endif

#ifdef MP0_CORE_DISABLE
#define
  {
    ///< MP0_CORE_DISABLE803
    803,
    8,
    0,
    0x5D13C,
  },
#endif

#ifdef MP0_CPU_PWROK_REFCLK_GAP_CYCLES
#define
  {
    ///< MP0_CPU_PWROK_REFCLK_GAP_CYCLES804
    804,
    1,
    26,
    0x5D13B,
  },
#endif

#ifdef MP0_CUSTOMER_SPARE
#define
  {
    ///< MP0_CUSTOMER_SPARE805
    805,
    8,
    24,
    0x5D0FB,
  },
#endif

#ifdef MP0_DDRPHY01_HARVEST
#define
  {
    ///< MP0_DDRPHY01_HARVEST806
    806,
    1,
    1,
    0x5D140,
  },
#endif

#ifdef MP0_DDRPHY23_HARVEST
#define
  {
    ///< MP0_DDRPHY23_HARVEST807
    807,
    1,
    2,
    0x5D140,
  },
#endif

#ifdef MP0_DDRPHY45_HARVEST
#define
  {
    ///< MP0_DDRPHY45_HARVEST808
    808,
    1,
    3,
    0x5D140,
  },
#endif

#ifdef MP0_DDRPHY67_HARVEST
#define
  {
    ///< MP0_DDRPHY67_HARVEST809
    809,
    1,
    4,
    0x5D140,
  },
#endif

#ifdef MP0_DF_CAKE0_HARVEST
#define
  {
    ///< MP0_DF_CAKE0_HARVEST810
    810,
    1,
    5,
    0x5D140,
  },
#endif

#ifdef MP0_DF_CAKE1_HARVEST
#define
  {
    ///< MP0_DF_CAKE1_HARVEST811
    811,
    1,
    6,
    0x5D140,
  },
#endif

#ifdef MP0_DF_CAKE2_HARVEST
#define
  {
    ///< MP0_DF_CAKE2_HARVEST812
    812,
    1,
    7,
    0x5D140,
  },
#endif

#ifdef MP0_DF_CAKE3_HARVEST
#define
  {
    ///< MP0_DF_CAKE3_HARVEST813
    813,
    1,
    8,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CAKE4_HARVEST
#define
  {
    ///< MP0_DF_CAKE4_HARVEST814
    814,
    1,
    9,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CAKE5_HARVEST
#define
  {
    ///< MP0_DF_CAKE5_HARVEST815
    815,
    1,
    10,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM0_HARVEST
#define
  {
    ///< MP0_DF_CCM0_HARVEST816
    816,
    1,
    11,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM1_HARVEST
#define
  {
    ///< MP0_DF_CCM1_HARVEST817
    817,
    1,
    12,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM2_HARVEST
#define
  {
    ///< MP0_DF_CCM2_HARVEST818
    818,
    1,
    13,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM3_HARVEST
#define
  {
    ///< MP0_DF_CCM3_HARVEST819
    819,
    1,
    14,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM4_HARVEST
#define
  {
    ///< MP0_DF_CCM4_HARVEST820
    820,
    1,
    15,
    0x5D141,
  },
#endif

#ifdef MP0_DF_CCM5_HARVEST
#define
  {
    ///< MP0_DF_CCM5_HARVEST821
    821,
    1,
    16,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CCM6_HARVEST
#define
  {
    ///< MP0_DF_CCM6_HARVEST822
    822,
    1,
    17,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CCM7_HARVEST
#define
  {
    ///< MP0_DF_CCM7_HARVEST823
    823,
    1,
    18,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS0_CCIX_HARVEST
#define
  {
    ///< MP0_DF_CS0_CCIX_HARVEST824
    824,
    1,
    19,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS0_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS0_UMC_HARVEST825
    825,
    1,
    23,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS1_CCIX_HARVEST
#define
  {
    ///< MP0_DF_CS1_CCIX_HARVEST826
    826,
    1,
    20,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS1_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS1_UMC_HARVEST827
    827,
    1,
    24,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS2_CCIX_HARVEST
#define
  {
    ///< MP0_DF_CS2_CCIX_HARVEST828
    828,
    1,
    21,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS2_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS2_UMC_HARVEST829
    829,
    1,
    25,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS3_CCIX_HARVEST
#define
  {
    ///< MP0_DF_CS3_CCIX_HARVEST830
    830,
    1,
    22,
    0x5D142,
  },
#endif

#ifdef MP0_DF_CS3_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS3_UMC_HARVEST831
    831,
    1,
    26,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS4_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS4_UMC_HARVEST832
    832,
    1,
    27,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS5_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS5_UMC_HARVEST833
    833,
    1,
    28,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS6_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS6_UMC_HARVEST834
    834,
    1,
    29,
    0x5D143,
  },
#endif

#ifdef MP0_DF_CS7_UMC_HARVEST
#define
  {
    ///< MP0_DF_CS7_UMC_HARVEST835
    835,
    1,
    30,
    0x5D143,
  },
#endif

#ifdef MP0_DF_IOM0_HARVEST
#define
  {
    ///< MP0_DF_IOM0_HARVEST836
    836,
    1,
    11,
    0x5D145,
  },
#endif

#ifdef MP0_DF_IOM1_HARVEST
#define
  {
    ///< MP0_DF_IOM1_HARVEST837
    837,
    1,
    12,
    0x5D145,
  },
#endif

#ifdef MP0_DF_IOM2_HARVEST
#define
  {
    ///< MP0_DF_IOM2_HARVEST838
    838,
    1,
    13,
    0x5D145,
  },
#endif

#ifdef MP0_DF_IOM3_HARVEST
#define
  {
    ///< MP0_DF_IOM3_HARVEST839
    839,
    1,
    14,
    0x5D145,
  },
#endif

#ifdef MP0_DF_SPF0_CCIX_HARVEST
#define
  {
    ///< MP0_DF_SPF0_CCIX_HARVEST840
    840,
    1,
    31,
    0x5D143,
  },
#endif

#ifdef MP0_DF_SPF0_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF0_UMC_HARVEST841
    841,
    1,
    3,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF1_CCIX_HARVEST
#define
  {
    ///< MP0_DF_SPF1_CCIX_HARVEST842
    842,
    1,
    0,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF1_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF1_UMC_HARVEST843
    843,
    1,
    4,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF2_CCIX_HARVEST
#define
  {
    ///< MP0_DF_SPF2_CCIX_HARVEST844
    844,
    1,
    1,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF2_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF2_UMC_HARVEST845
    845,
    1,
    5,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF3_CCIX_HARVEST
#define
  {
    ///< MP0_DF_SPF3_CCIX_HARVEST846
    846,
    1,
    2,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF3_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF3_UMC_HARVEST847
    847,
    1,
    6,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF4_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF4_UMC_HARVEST848
    848,
    1,
    7,
    0x5D144,
  },
#endif

#ifdef MP0_DF_SPF5_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF5_UMC_HARVEST849
    849,
    1,
    8,
    0x5D145,
  },
#endif

#ifdef MP0_DF_SPF6_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF6_UMC_HARVEST850
    850,
    1,
    9,
    0x5D145,
  },
#endif

#ifdef MP0_DF_SPF7_UMC_HARVEST
#define
  {
    ///< MP0_DF_SPF7_UMC_HARVEST851
    851,
    1,
    10,
    0x5D145,
  },
#endif

#ifdef MP0_DISABLE_MP0_BIHR
#define
  {
    ///< MP0_DISABLE_MP0_BIHR852
    852,
    1,
    7,
    0x5D138,
  },
#endif

#ifdef MP0_DISABLE_MP0_MBIST
#define
  {
    ///< MP0_DISABLE_MP0_MBIST853
    853,
    1,
    8,
    0x5D139,
  },
#endif

#ifdef MP0_DISTRIBUTE_LDO_FUSES
#define
  {
    ///< MP0_DISTRIBUTE_LDO_FUSES854
    854,
    1,
    10,
    0x5D139,
  },
#endif

#ifdef MP0_DISTRIBUTE_WAFL_FUSES
#define
  {
    ///< MP0_DISTRIBUTE_WAFL_FUSES855
    855,
    1,
    29,
    0x5D153,
  },
#endif

#ifdef MP0_ENABLE_32MB_SPI_ACCESS
#define
  {
    ///< MP0_ENABLE_32MB_SPI_ACCESS856
    856,
    1,
    14,
    0x5D139,
  },
#endif

#ifdef MP0_ENABLE_DBGU_NBIO_POST_CODES
#define
  {
    ///< MP0_ENABLE_DBGU_NBIO_POST_CODES857
    857,
    1,
    24,
    0x5D13B,
  },
#endif

#ifdef MP0_ENABLE_ODPR_TMP_COMP
#define
  {
    ///< MP0_ENABLE_ODPR_TMP_COMP858
    858,
    1,
    27,
    0x5D13B,
  },
#endif

#ifdef MP0_ENABLE_RSMU_WDT
#define
  {
    ///< MP0_ENABLE_RSMU_WDT859
    859,
    1,
    9,
    0x5D139,
  },
#endif

#ifdef MP0_ENABLE_SBI_POST_CODES
#define
  {
    ///< MP0_ENABLE_SBI_POST_CODES860
    860,
    1,
    11,
    0x5D139,
  },
#endif

#ifdef MP0_FW_ROLLBACK_CNT
#define
  {
    ///< MP0_FW_ROLLBACK_CNT861
    861,
    32,
    0,
    0x5D0FC,
  },
#endif

#ifdef MP0_FW_ROLLBACK_CNT_1
#define
  {
    ///< MP0_FW_ROLLBACK_CNT_1862
    862,
    32,
    0,
    0x5D100,
  },
#endif

#ifdef MP0_FW_ROLLBACK_CNT_2
#define
  {
    ///< MP0_FW_ROLLBACK_CNT_2863
    863,
    32,
    0,
    0x5D104,
  },
#endif

#ifdef MP0_GMI2_PCS0_HARVEST
#define
  {
    ///< MP0_GMI2_PCS0_HARVEST864
    864,
    1,
    15,
    0x5D145,
  },
#endif

#ifdef MP0_GMI2_PCS1_HARVEST
#define
  {
    ///< MP0_GMI2_PCS1_HARVEST865
    865,
    1,
    16,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS2_HARVEST
#define
  {
    ///< MP0_GMI2_PCS2_HARVEST866
    866,
    1,
    17,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS3_HARVEST
#define
  {
    ///< MP0_GMI2_PCS3_HARVEST867
    867,
    1,
    18,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS4_HARVEST
#define
  {
    ///< MP0_GMI2_PCS4_HARVEST868
    868,
    1,
    19,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS5_HARVEST
#define
  {
    ///< MP0_GMI2_PCS5_HARVEST869
    869,
    1,
    20,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS6_HARVEST
#define
  {
    ///< MP0_GMI2_PCS6_HARVEST870
    870,
    1,
    21,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PCS7_HARVEST
#define
  {
    ///< MP0_GMI2_PCS7_HARVEST871
    871,
    1,
    22,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PHY0_HARVEST
#define
  {
    ///< MP0_GMI2_PHY0_HARVEST872
    872,
    1,
    23,
    0x5D146,
  },
#endif

#ifdef MP0_GMI2_PHY1_HARVEST
#define
  {
    ///< MP0_GMI2_PHY1_HARVEST873
    873,
    1,
    24,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY2_HARVEST
#define
  {
    ///< MP0_GMI2_PHY2_HARVEST874
    874,
    1,
    25,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY3_HARVEST
#define
  {
    ///< MP0_GMI2_PHY3_HARVEST875
    875,
    1,
    26,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY4_HARVEST
#define
  {
    ///< MP0_GMI2_PHY4_HARVEST876
    876,
    1,
    27,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY5_HARVEST
#define
  {
    ///< MP0_GMI2_PHY5_HARVEST877
    877,
    1,
    28,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY6_HARVEST
#define
  {
    ///< MP0_GMI2_PHY6_HARVEST878
    878,
    1,
    29,
    0x5D147,
  },
#endif

#ifdef MP0_GMI2_PHY7_HARVEST
#define
  {
    ///< MP0_GMI2_PHY7_HARVEST879
    879,
    1,
    30,
    0x5D147,
  },
#endif

#ifdef MP0_HARVESTING_FUSES
#define
  {
    ///< MP0_HARVESTING_FUSES880
    880,
    1,
    31,
    0x5D13F,
  },
#endif

#ifdef MP0_HARVESTING_FUSES_1
#define
  {
    ///< MP0_HARVESTING_FUSES_1881
    881,
    2,
    30,
    0x5D153,
  },
#endif

#ifdef MP0_LOAD_DIAG_BOOT_LOADER
#define
  {
    ///< MP0_LOAD_DIAG_BOOT_LOADER882
    882,
    1,
    16,
    0x5D13A,
  },
#endif

#ifdef MP0_MP0_GROUP0_DATA
#define
  {
    ///< MP0_MP0_GROUP0_DATA883
    883,
    96,
    0,
    0x5D7F0,
  },
#endif

#ifdef MP0_MP0_WRITE_DISABLE
#define
  {
    ///< MP0_MP0_WRITE_DISABLE884
    884,
    1,
    0,
    0x5D138,
  },
#endif

#ifdef MP0_NBIO_IOHC0_HARVEST
#define
  {
    ///< MP0_NBIO_IOHC0_HARVEST885
    885,
    1,
    31,
    0x5D147,
  },
#endif

#ifdef MP0_NBIO_IOHC1_HARVEST
#define
  {
    ///< MP0_NBIO_IOHC1_HARVEST886
    886,
    1,
    0,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOHC2_HARVEST
#define
  {
    ///< MP0_NBIO_IOHC2_HARVEST887
    887,
    1,
    1,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOHC3_HARVEST
#define
  {
    ///< MP0_NBIO_IOHC3_HARVEST888
    888,
    1,
    2,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOMMU0_HARVEST
#define
  {
    ///< MP0_NBIO_IOMMU0_HARVEST889
    889,
    1,
    3,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOMMU1_HARVEST
#define
  {
    ///< MP0_NBIO_IOMMU1_HARVEST890
    890,
    1,
    4,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOMMU2_HARVEST
#define
  {
    ///< MP0_NBIO_IOMMU2_HARVEST891
    891,
    1,
    5,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_IOMMU3_HARVEST
#define
  {
    ///< MP0_NBIO_IOMMU3_HARVEST892
    892,
    1,
    6,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_L1NBIF0_0_HARVEST
#define
  {
    ///< MP0_NBIO_L1NBIF0_0_HARVEST893
    893,
    1,
    7,
    0x5D148,
  },
#endif

#ifdef MP0_NBIO_L1NBIF0_1_HARVEST
#define
  {
    ///< MP0_NBIO_L1NBIF0_1_HARVEST894
    894,
    1,
    8,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_L1NBIF0_2_HARVEST
#define
  {
    ///< MP0_NBIO_L1NBIF0_2_HARVEST895
    895,
    1,
    9,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_L1NBIF0_3_HARVEST
#define
  {
    ///< MP0_NBIO_L1NBIF0_3_HARVEST896
    896,
    1,
    10,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NB2_0_HARVEST
#define
  {
    ///< MP0_NBIO_NB2_0_HARVEST897
    897,
    1,
    15,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NB2_1_HARVEST
#define
  {
    ///< MP0_NBIO_NB2_1_HARVEST898
    898,
    1,
    16,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NB2_2_HARVEST
#define
  {
    ///< MP0_NBIO_NB2_2_HARVEST899
    899,
    1,
    17,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NB2_3_HARVEST
#define
  {
    ///< MP0_NBIO_NB2_3_HARVEST900
    900,
    1,
    18,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF0_0_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF0_0_HARVEST901
    901,
    1,
    19,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF0_1_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF0_1_HARVEST902
    902,
    1,
    20,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF0_2_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF0_2_HARVEST903
    903,
    1,
    21,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF0_3_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF0_3_HARVEST904
    904,
    1,
    22,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF1_0_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF1_0_HARVEST905
    905,
    1,
    23,
    0x5D14A,
  },
#endif

#ifdef MP0_NBIO_NBIF1_1_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF1_1_HARVEST906
    906,
    1,
    24,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NBIF1_2_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF1_2_HARVEST907
    907,
    1,
    25,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NBIF1_3_HARVEST
#define
  {
    ///< MP0_NBIO_NBIF1_3_HARVEST908
    908,
    1,
    26,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NB_0_HARVEST
#define
  {
    ///< MP0_NBIO_NB_0_HARVEST909
    909,
    1,
    11,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NB_1_HARVEST
#define
  {
    ///< MP0_NBIO_NB_1_HARVEST910
    910,
    1,
    12,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NB_2_HARVEST
#define
  {
    ///< MP0_NBIO_NB_2_HARVEST911
    911,
    1,
    13,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NB_3_HARVEST
#define
  {
    ///< MP0_NBIO_NB_3_HARVEST912
    912,
    1,
    14,
    0x5D149,
  },
#endif

#ifdef MP0_NBIO_NTB_0_HARVEST
#define
  {
    ///< MP0_NBIO_NTB_0_HARVEST913
    913,
    1,
    27,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NTB_1_HARVEST
#define
  {
    ///< MP0_NBIO_NTB_1_HARVEST914
    914,
    1,
    28,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NTB_2_HARVEST
#define
  {
    ///< MP0_NBIO_NTB_2_HARVEST915
    915,
    1,
    29,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_NTB_3_HARVEST
#define
  {
    ///< MP0_NBIO_NTB_3_HARVEST916
    916,
    1,
    30,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_PCIE0_0_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE0_0_HARVEST917
    917,
    1,
    7,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE0_1_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE0_1_HARVEST918
    918,
    1,
    8,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE0_2_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE0_2_HARVEST919
    919,
    1,
    9,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE0_3_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE0_3_HARVEST920
    920,
    1,
    10,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE1_0_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE1_0_HARVEST921
    921,
    1,
    11,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE1_1_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE1_1_HARVEST922
    922,
    1,
    12,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE1_2_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE1_2_HARVEST923
    923,
    1,
    13,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIE1_3_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE1_3_HARVEST924
    924,
    1,
    14,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIEX2_HARVEST
#define
  {
    ///< MP0_NBIO_PCIEX2_HARVEST925
    925,
    1,
    15,
    0x5D14D,
  },
#endif

#ifdef MP0_NBIO_PCIEX2_PCS_HARVEST
#define
  {
    ///< MP0_NBIO_PCIEX2_PCS_HARVEST926
    926,
    1,
    16,
    0x5D14E,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_G0_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_G0_HARVEST927
    927,
    1,
    31,
    0x5D14B,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_G1_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_G1_HARVEST928
    928,
    1,
    0,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_G2_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_G2_HARVEST929
    929,
    1,
    1,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_G3_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_G3_HARVEST930
    930,
    1,
    2,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_P0_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_P0_HARVEST931
    931,
    1,
    3,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_P1_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_P1_HARVEST932
    932,
    1,
    4,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_P2_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_P2_HARVEST933
    933,
    1,
    5,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PCIE_PCS_P3_HARVEST
#define
  {
    ///< MP0_NBIO_PCIE_PCS_P3_HARVEST934
    934,
    1,
    6,
    0x5D14C,
  },
#endif

#ifdef MP0_NBIO_PTDMA0_HARVEST
#define
  {
    ///< MP0_NBIO_PTDMA0_HARVEST935
    935,
    1,
    11,
    0x5D13D,
  },
#endif

#ifdef MP0_NBIO_PTDMA1_HARVEST
#define
  {
    ///< MP0_NBIO_PTDMA1_HARVEST936
    936,
    1,
    12,
    0x5D13D,
  },
#endif

#ifdef MP0_NBIO_PTDMA2_HARVEST
#define
  {
    ///< MP0_NBIO_PTDMA2_HARVEST937
    937,
    1,
    13,
    0x5D13D,
  },
#endif

#ifdef MP0_NBIO_PTDMA3_HARVEST
#define
  {
    ///< MP0_NBIO_PTDMA3_HARVEST938
    938,
    1,
    14,
    0x5D13D,
  },
#endif

#ifdef MP0_NONSECURE_FUSES
#define
  {
    ///< MP0_NONSECURE_FUSES939
    939,
    1,
    15,
    0x5D139,
  },
#endif

#ifdef MP0_PGVI_POWER_UP
#define
  {
    ///< MP0_PGVI_POWER_UP940
    940,
    1,
    28,
    0x5D13B,
  },
#endif

#ifdef MP0_PGVI_POWER_UP_MM
#define
  {
    ///< MP0_PGVI_POWER_UP_MM941
    941,
    1,
    29,
    0x5D13B,
  },
#endif

#ifdef MP0_PSPBL_LOAD_DIAG_OS
#define
  {
    ///< MP0_PSPBL_LOAD_DIAG_OS942
    942,
    1,
    31,
    0x5D13B,
  },
#endif

#ifdef MP0_RELEASE_CPU_RESET
#define
  {
    ///< MP0_RELEASE_CPU_RESET943
    943,
    1,
    22,
    0x5D13A,
  },
#endif

#ifdef MP0_ROOT_KEY
#define
  {
    ///< MP0_ROOT_KEY944
    944,
    640,
    0,
    0x5D074,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM945
    945,
    32,
    0,
    0x5D114,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM_1
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM_1946
    946,
    32,
    0,
    0x5D118,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM_2
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM_2947
    947,
    32,
    0,
    0x5D11C,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM_VALID
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM_VALID948
    948,
    1,
    15,
    0x5D0F9,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM_VALID_1
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM_VALID_1949
    949,
    1,
    16,
    0x5D0FA,
  },
#endif

#ifdef MP0_ROOT_KEY_CHECKSUM_VALID_2
#define
  {
    ///< MP0_ROOT_KEY_CHECKSUM_VALID_2950
    950,
    1,
    17,
    0x5D0FA,
  },
#endif

#ifdef MP0_ROOT_KEY_ECC_EN
#define
  {
    ///< MP0_ROOT_KEY_ECC_EN951
    951,
    1,
    12,
    0x5D0F9,
  },
#endif

#ifdef MP0_ROOT_KEY_ECC_EN_1
#define
  {
    ///< MP0_ROOT_KEY_ECC_EN_1952
    952,
    1,
    13,
    0x5D0F9,
  },
#endif

#ifdef MP0_ROOT_KEY_ECC_EN_2
#define
  {
    ///< MP0_ROOT_KEY_ECC_EN_2953
    953,
    1,
    14,
    0x5D0F9,
  },
#endif

#ifdef MP0_ROOT_KEY_SELECT
#define
  {
    ///< MP0_ROOT_KEY_SELECT954
    954,
    4,
    0,
    0x5D0F8,
  },
#endif

#ifdef MP0_ROOT_KEY_SELECT_1
#define
  {
    ///< MP0_ROOT_KEY_SELECT_1955
    955,
    4,
    4,
    0x5D0F8,
  },
#endif

#ifdef MP0_ROOT_KEY_SELECT_2
#define
  {
    ///< MP0_ROOT_KEY_SELECT_2956
    956,
    4,
    8,
    0x5D0F9,
  },
#endif

#ifdef MP0_RSMU_FUSE_VALID
#define
  {
    ///< MP0_RSMU_FUSE_VALID957
    957,
    1,
    30,
    0x5D13B,
  },
#endif

#ifdef MP0_RUN_BIHR
#define
  {
    ///< MP0_RUN_BIHR958
    958,
    1,
    5,
    0x5D138,
  },
#endif

#ifdef MP0_RUN_MBIST
#define
  {
    ///< MP0_RUN_MBIST959
    959,
    1,
    6,
    0x5D138,
  },
#endif

#ifdef MP0_SATA0_HARVEST
#define
  {
    ///< MP0_SATA0_HARVEST960
    960,
    1,
    15,
    0x5D13D,
  },
#endif

#ifdef MP0_SATA1_HARVEST
#define
  {
    ///< MP0_SATA1_HARVEST961
    961,
    1,
    16,
    0x5D13E,
  },
#endif

#ifdef MP0_SATA2_HARVEST
#define
  {
    ///< MP0_SATA2_HARVEST962
    962,
    1,
    17,
    0x5D13E,
  },
#endif

#ifdef MP0_SATA3_HARVEST
#define
  {
    ///< MP0_SATA3_HARVEST963
    963,
    1,
    18,
    0x5D13E,
  },
#endif

#ifdef MP0_SEC_FEATURE_SEL
#define
  {
    ///< MP0_SEC_FEATURE_SEL964
    964,
    16,
    16,
    0x5D10E,
  },
#endif

#ifdef MP0_SEC_FEATURE_SEL_1
#define
  {
    ///< MP0_SEC_FEATURE_SEL_1965
    965,
    16,
    0,
    0x5D110,
  },
#endif

#ifdef MP0_SEC_FEATURE_SEL_2
#define
  {
    ///< MP0_SEC_FEATURE_SEL_2966
    966,
    16,
    16,
    0x5D112,
  },
#endif

#ifdef MP0_SERDES_G0_HARVEST
#define
  {
    ///< MP0_SERDES_G0_HARVEST967
    967,
    1,
    17,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_G1_HARVEST
#define
  {
    ///< MP0_SERDES_G1_HARVEST968
    968,
    1,
    18,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_G2_HARVEST
#define
  {
    ///< MP0_SERDES_G2_HARVEST969
    969,
    1,
    19,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_G3_HARVEST
#define
  {
    ///< MP0_SERDES_G3_HARVEST970
    970,
    1,
    20,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_P0_HARVEST
#define
  {
    ///< MP0_SERDES_P0_HARVEST971
    971,
    1,
    21,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_P1_HARVEST
#define
  {
    ///< MP0_SERDES_P1_HARVEST972
    972,
    1,
    22,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_P2_HARVEST
#define
  {
    ///< MP0_SERDES_P2_HARVEST973
    973,
    1,
    23,
    0x5D14E,
  },
#endif

#ifdef MP0_SERDES_P3_HARVEST
#define
  {
    ///< MP0_SERDES_P3_HARVEST974
    974,
    1,
    24,
    0x5D14F,
  },
#endif

#ifdef MP0_SET_BOOTROM_STARTUP_CLOCKS
#define
  {
    ///< MP0_SET_BOOTROM_STARTUP_CLOCKS975
    975,
    1,
    25,
    0x5D13B,
  },
#endif

#ifdef MP0_SKIP_EXIT_BYPASS
#define
  {
    ///< MP0_SKIP_EXIT_BYPASS976
    976,
    1,
    23,
    0x5D13A,
  },
#endif

#ifdef MP0_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE
#define
  {
    ///< MP0_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE977
    977,
    1,
    17,
    0x5D13A,
  },
#endif

#ifdef MP0_SMT_ENABLE
#define
  {
    ///< MP0_SMT_ENABLE978
    978,
    1,
    8,
    0x5D13D,
  },
#endif

#ifdef MP0_SMU_CLKC0_HARVEST
#define
  {
    ///< MP0_SMU_CLKC0_HARVEST979
    979,
    1,
    26,
    0x5D14F,
  },
#endif

#ifdef MP0_SMU_CLKC1_HARVEST
#define
  {
    ///< MP0_SMU_CLKC1_HARVEST980
    980,
    1,
    27,
    0x5D14F,
  },
#endif

#ifdef MP0_SMU_CLKC2_HARVEST
#define
  {
    ///< MP0_SMU_CLKC2_HARVEST981
    981,
    1,
    28,
    0x5D14F,
  },
#endif

#ifdef MP0_SMU_CLKC3_HARVEST
#define
  {
    ///< MP0_SMU_CLKC3_HARVEST982
    982,
    1,
    29,
    0x5D14F,
  },
#endif

#ifdef MP0_SMU_CLKC_HARVEST
#define
  {
    ///< MP0_SMU_CLKC_HARVEST983
    983,
    1,
    25,
    0x5D14F,
  },
#endif

#ifdef MP0_SMU_TWIX0_HARVEST
#define
  {
    ///< MP0_SMU_TWIX0_HARVEST984
    984,
    1,
    19,
    0x5D13E,
  },
#endif

#ifdef MP0_SMU_TWIX1_HARVEST
#define
  {
    ///< MP0_SMU_TWIX1_HARVEST985
    985,
    1,
    20,
    0x5D13E,
  },
#endif

#ifdef MP0_SMU_TWIX2_HARVEST
#define
  {
    ///< MP0_SMU_TWIX2_HARVEST986
    986,
    1,
    21,
    0x5D13E,
  },
#endif

#ifdef MP0_SMU_TWIX3_HARVEST
#define
  {
    ///< MP0_SMU_TWIX3_HARVEST987
    987,
    1,
    22,
    0x5D13E,
  },
#endif

#ifdef MP0_SMU_TWIX4_HARVEST
#define
  {
    ///< MP0_SMU_TWIX4_HARVEST988
    988,
    1,
    23,
    0x5D13E,
  },
#endif

#ifdef MP0_SMU_TWIX5_HARVEST
#define
  {
    ///< MP0_SMU_TWIX5_HARVEST989
    989,
    1,
    24,
    0x5D13F,
  },
#endif

#ifdef MP0_SMU_TWIX6_HARVEST
#define
  {
    ///< MP0_SMU_TWIX6_HARVEST990
    990,
    1,
    25,
    0x5D13F,
  },
#endif

#ifdef MP0_SMU_TWIX7_HARVEST
#define
  {
    ///< MP0_SMU_TWIX7_HARVEST991
    991,
    1,
    26,
    0x5D13F,
  },
#endif

#ifdef MP0_SMU_WAFL_HARVEST
#define
  {
    ///< MP0_SMU_WAFL_HARVEST992
    992,
    1,
    30,
    0x5D14F,
  },
#endif

#ifdef MP0_SRAM_HD_BC1
#define
  {
    ///< MP0_SRAM_HD_BC1993
    993,
    1,
    30,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_HD_BC2
#define
  {
    ///< MP0_SRAM_HD_BC2994
    994,
    1,
    31,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_PDP_BC1
#define
  {
    ///< MP0_SRAM_PDP_BC1995
    995,
    1,
    28,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_PDP_BC2
#define
  {
    ///< MP0_SRAM_PDP_BC2996
    996,
    1,
    29,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_RF_BC1
#define
  {
    ///< MP0_SRAM_RF_BC1997
    997,
    1,
    26,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_RF_BC2
#define
  {
    ///< MP0_SRAM_RF_BC2998
    998,
    1,
    27,
    0x5D157,
  },
#endif

#ifdef MP0_SRAM_RM
#define
  {
    ///< MP0_SRAM_RM999
    999,
    9,
    0,
    0x5D154,
  },
#endif

#ifdef MP0_SRAM_SPARE_0
#define
  {
    ///< MP0_SRAM_SPARE_01000
    1000,
    17,
    9,
    0x5D155,
  },
#endif

#ifdef MP0_TWIX_PCS0_HARVEST
#define
  {
    ///< MP0_TWIX_PCS0_HARVEST1001
    1001,
    1,
    31,
    0x5D14F,
  },
#endif

#ifdef MP0_TWIX_PCS1_HARVEST
#define
  {
    ///< MP0_TWIX_PCS1_HARVEST1002
    1002,
    1,
    0,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS2_HARVEST
#define
  {
    ///< MP0_TWIX_PCS2_HARVEST1003
    1003,
    1,
    1,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS3_HARVEST
#define
  {
    ///< MP0_TWIX_PCS3_HARVEST1004
    1004,
    1,
    2,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS4_HARVEST
#define
  {
    ///< MP0_TWIX_PCS4_HARVEST1005
    1005,
    1,
    3,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS5_HARVEST
#define
  {
    ///< MP0_TWIX_PCS5_HARVEST1006
    1006,
    1,
    4,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS6_HARVEST
#define
  {
    ///< MP0_TWIX_PCS6_HARVEST1007
    1007,
    1,
    5,
    0x5D150,
  },
#endif

#ifdef MP0_TWIX_PCS7_HARVEST
#define
  {
    ///< MP0_TWIX_PCS7_HARVEST1008
    1008,
    1,
    6,
    0x5D150,
  },
#endif

#ifdef MP0_UMC_UMC0_HARVEST
#define
  {
    ///< MP0_UMC_UMC0_HARVEST1009
    1009,
    1,
    7,
    0x5D150,
  },
#endif

#ifdef MP0_UMC_UMC1_HARVEST
#define
  {
    ///< MP0_UMC_UMC1_HARVEST1010
    1010,
    1,
    8,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC2_HARVEST
#define
  {
    ///< MP0_UMC_UMC2_HARVEST1011
    1011,
    1,
    9,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC3_HARVEST
#define
  {
    ///< MP0_UMC_UMC3_HARVEST1012
    1012,
    1,
    10,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC4_HARVEST
#define
  {
    ///< MP0_UMC_UMC4_HARVEST1013
    1013,
    1,
    11,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC5_HARVEST
#define
  {
    ///< MP0_UMC_UMC5_HARVEST1014
    1014,
    1,
    12,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC6_HARVEST
#define
  {
    ///< MP0_UMC_UMC6_HARVEST1015
    1015,
    1,
    13,
    0x5D151,
  },
#endif

#ifdef MP0_UMC_UMC7_HARVEST
#define
  {
    ///< MP0_UMC_UMC7_HARVEST1016
    1016,
    1,
    14,
    0x5D151,
  },
#endif

#ifdef MP0_WAFL_CPHY_HARVEST
#define
  {
    ///< MP0_WAFL_CPHY_HARVEST1017
    1017,
    1,
    15,
    0x5D151,
  },
#endif

#ifdef MP0_WAFL_DBG_INTERLOCK_1
#define
  {
    ///< MP0_WAFL_DBG_INTERLOCK_11018
    1018,
    2,
    12,
    0x5D139,
  },
#endif

#ifdef MP0_WAFL_DBG_INTERLOCK_2
#define
  {
    ///< MP0_WAFL_DBG_INTERLOCK_21019
    1019,
    2,
    18,
    0x5D13A,
  },
#endif

#ifdef MP0_WAFL_DESKEW_TIME
#define
  {
    ///< MP0_WAFL_DESKEW_TIME1020
    1020,
    3,
    28,
    0x5D13F,
  },
#endif

#ifdef MP0_WAFL_DETECT_REPEAT
#define
  {
    ///< MP0_WAFL_DETECT_REPEAT1021
    1021,
    1,
    27,
    0x5D153,
  },
#endif

#ifdef MP0_WAFL_DETECT_TIME
#define
  {
    ///< MP0_WAFL_DETECT_TIME1022
    1022,
    2,
    25,
    0x5D153,
  },
#endif

#ifdef MP0_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE
#define
  {
    ///< MP0_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE1023
    1023,
    1,
    20,
    0x5D13A,
  },
#endif

#ifdef MP0_WAFL_PATCH
#define
  {
    ///< MP0_WAFL_PATCH1024
    1024,
    1024,
    0,
    0x5D158,
  },
#endif

#ifdef MP0_WAFL_PCS_HARVEST
#define
  {
    ///< MP0_WAFL_PCS_HARVEST1025
    1025,
    1,
    16,
    0x5D152,
  },
#endif

#ifdef MP0_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE
#define
  {
    ///< MP0_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE1026
    1026,
    1,
    21,
    0x5D13A,
  },
#endif

#ifdef MP0_WAFL_SKIP_FIRST_CAL
#define
  {
    ///< MP0_WAFL_SKIP_FIRST_CAL1027
    1027,
    1,
    27,
    0x5D13F,
  },
#endif

#ifdef MP0_WAFL_SLAVE_INFINITE_TIMEOUT
#define
  {
    ///< MP0_WAFL_SLAVE_INFINITE_TIMEOUT1028
    1028,
    1,
    28,
    0x5D153,
  },
#endif

#ifdef MP0_WaflInvertLinkAddr0
#define
  {
    ///< MP0_WaflInvertLinkAddr01029
    1029,
    1,
    3,
    0x5D138,
  },
#endif

#ifdef MP0_WaflInvertLinkAddr1
#define
  {
    ///< MP0_WaflInvertLinkAddr11030
    1030,
    1,
    4,
    0x5D138,
  },
#endif

#ifdef MP0_WaflInvertSmnAddr0
#define
  {
    ///< MP0_WaflInvertSmnAddr01031
    1031,
    1,
    1,
    0x5D138,
  },
#endif

#ifdef MP0_WaflInvertSmnAddr1
#define
  {
    ///< MP0_WaflInvertSmnAddr11032
    1032,
    1,
    2,
    0x5D138,
  },
#endif

#ifdef MP0_WaflLinkEnable0
#define
  {
    ///< MP0_WaflLinkEnable01033
    1033,
    1,
    9,
    0x5D13D,
  },
#endif

#ifdef MP0_WaflLinkEnable1
#define
  {
    ///< MP0_WaflLinkEnable11034
    1034,
    1,
    10,
    0x5D13D,
  },
#endif

#ifdef MP0_XGMI_PCS_G0_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_G0_HARVEST1035
    1035,
    1,
    17,
    0x5D152,
  },
#endif

#ifdef MP0_XGMI_PCS_G1_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_G1_HARVEST1036
    1036,
    1,
    18,
    0x5D152,
  },
#endif

#ifdef MP0_XGMI_PCS_G2_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_G2_HARVEST1037
    1037,
    1,
    19,
    0x5D152,
  },
#endif

#ifdef MP0_XGMI_PCS_G3_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_G3_HARVEST1038
    1038,
    1,
    20,
    0x5D152,
  },
#endif

#ifdef MP0_XGMI_PCS_P2_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_P2_HARVEST1039
    1039,
    1,
    21,
    0x5D152,
  },
#endif

#ifdef MP0_XGMI_PCS_P3_HARVEST
#define
  {
    ///< MP0_XGMI_PCS_P3_HARVEST1040
    1040,
    1,
    22,
    0x5D152,
  },
#endif

#ifdef MP1_BC_Determinism_Scalar_CURRENT
#define
  {
    ///< MP1_BC_Determinism_Scalar_CURRENT1041
    1041,
    7,
    26,
    0x5D31B,
  },
#endif

#ifdef MP1_BC_Determinism_Scalar_POWER
#define
  {
    ///< MP1_BC_Determinism_Scalar_POWER1042
    1042,
    7,
    19,
    0x5D31A,
  },
#endif

#ifdef MP1_BC_Determinism_Scalar_VOLTAGE
#define
  {
    ///< MP1_BC_Determinism_Scalar_VOLTAGE1043
    1043,
    7,
    1,
    0x5D31C,
  },
#endif

#ifdef MP1_CCLK_FtoV_A_WC_CURRENT
#define
  {
    ///< MP1_CCLK_FtoV_A_WC_CURRENT1044
    1044,
    12,
    12,
    0x5D2DD,
  },
#endif

#ifdef MP1_CCLK_FtoV_A_WC_POWER
#define
  {
    ///< MP1_CCLK_FtoV_A_WC_POWER1045
    1045,
    12,
    8,
    0x5D2D9,
  },
#endif

#ifdef MP1_CCLK_FtoV_A_WC_VOLTAGE
#define
  {
    ///< MP1_CCLK_FtoV_A_WC_VOLTAGE1046
    1046,
    12,
    16,
    0x5D2E2,
  },
#endif

#ifdef MP1_CCLK_FtoV_B_WC_CURRENT
#define
  {
    ///< MP1_CCLK_FtoV_B_WC_CURRENT1047
    1047,
    12,
    24,
    0x5D2DF,
  },
#endif

#ifdef MP1_CCLK_FtoV_B_WC_POWER
#define
  {
    ///< MP1_CCLK_FtoV_B_WC_POWER1048
    1048,
    12,
    20,
    0x5D2DA,
  },
#endif

#ifdef MP1_CCLK_FtoV_B_WC_VOLTAGE
#define
  {
    ///< MP1_CCLK_FtoV_B_WC_VOLTAGE1049
    1049,
    12,
    28,
    0x5D2E3,
  },
#endif

#ifdef MP1_CCLK_FtoV_C_WC_CURRENT
#define
  {
    ///< MP1_CCLK_FtoV_C_WC_CURRENT1050
    1050,
    12,
    4,
    0x5D2E0,
  },
#endif

#ifdef MP1_CCLK_FtoV_C_WC_POWER
#define
  {
    ///< MP1_CCLK_FtoV_C_WC_POWER1051
    1051,
    12,
    0,
    0x5D2DC,
  },
#endif

#ifdef MP1_CCLK_FtoV_C_WC_VOLTAGE
#define
  {
    ///< MP1_CCLK_FtoV_C_WC_VOLTAGE1052
    1052,
    12,
    8,
    0x5D2E5,
  },
#endif

#ifdef MP1_Core_Cac_b_WC_CURRENT
#define
  {
    ///< MP1_Core_Cac_b_WC_CURRENT1053
    1053,
    12,
    24,
    0x5D2EB,
  },
#endif

#ifdef MP1_Core_Cac_b_WC_POWER
#define
  {
    ///< MP1_Core_Cac_b_WC_POWER1054
    1054,
    12,
    0,
    0x5D2E8,
  },
#endif

#ifdef MP1_Core_Cac_m_WC_CURRENT
#define
  {
    ///< MP1_Core_Cac_m_WC_CURRENT1055
    1055,
    12,
    12,
    0x5D2E9,
  },
#endif

#ifdef MP1_Core_Cac_m_WC_POWER
#define
  {
    ///< MP1_Core_Cac_m_WC_POWER1056
    1056,
    12,
    20,
    0x5D2E6,
  },
#endif

#ifdef MP1_Core_Sidd_Tb_WC_CURRENT
#define
  {
    ///< MP1_Core_Sidd_Tb_WC_CURRENT1057
    1057,
    12,
    24,
    0x5D2F7,
  },
#endif

#ifdef MP1_Core_Sidd_Tb_WC_POWER
#define
  {
    ///< MP1_Core_Sidd_Tb_WC_POWER1058
    1058,
    12,
    8,
    0x5D2F1,
  },
#endif

#ifdef MP1_Core_Sidd_Tm_WC_CURRENT
#define
  {
    ///< MP1_Core_Sidd_Tm_WC_CURRENT1059
    1059,
    12,
    12,
    0x5D2F5,
  },
#endif

#ifdef MP1_Core_Sidd_Tm_WC_POWER
#define
  {
    ///< MP1_Core_Sidd_Tm_WC_POWER1060
    1060,
    12,
    28,
    0x5D2EF,
  },
#endif

#ifdef MP1_Core_Sidd_b_WC_CURRENT
#define
  {
    ///< MP1_Core_Sidd_b_WC_CURRENT1061
    1061,
    12,
    0,
    0x5D2F4,
  },
#endif

#ifdef MP1_Core_Sidd_b_WC_POWER
#define
  {
    ///< MP1_Core_Sidd_b_WC_POWER1062
    1062,
    12,
    16,
    0x5D2EE,
  },
#endif

#ifdef MP1_Core_Sidd_m_WC_CURRENT
#define
  {
    ///< MP1_Core_Sidd_m_WC_CURRENT1063
    1063,
    12,
    20,
    0x5D2F2,
  },
#endif

#ifdef MP1_Core_Sidd_m_WC_POWER
#define
  {
    ///< MP1_Core_Sidd_m_WC_POWER1064
    1064,
    12,
    4,
    0x5D2EC,
  },
#endif

#ifdef MP1_CpuDid0
#define
  {
    ///< MP1_CpuDid01065
    1065,
    6,
    14,
    0x5D29D,
  },
#endif

#ifdef MP1_CpuDid1
#define
  {
    ///< MP1_CpuDid11066
    1066,
    6,
    20,
    0x5D29E,
  },
#endif

#ifdef MP1_CpuDid2
#define
  {
    ///< MP1_CpuDid21067
    1067,
    6,
    26,
    0x5D29F,
  },
#endif

#ifdef MP1_CpuDid3
#define
  {
    ///< MP1_CpuDid31068
    1068,
    6,
    0,
    0x5D2A0,
  },
#endif

#ifdef MP1_CpuDid4
#define
  {
    ///< MP1_CpuDid41069
    1069,
    6,
    6,
    0x5D2A0,
  },
#endif

#ifdef MP1_CpuDid5
#define
  {
    ///< MP1_CpuDid51070
    1070,
    6,
    12,
    0x5D2A1,
  },
#endif

#ifdef MP1_CpuDid6
#define
  {
    ///< MP1_CpuDid61071
    1071,
    6,
    18,
    0x5D2A2,
  },
#endif

#ifdef MP1_CpuDid7
#define
  {
    ///< MP1_CpuDid71072
    1072,
    6,
    24,
    0x5D2A3,
  },
#endif

#ifdef MP1_CpuFid0
#define
  {
    ///< MP1_CpuFid01073
    1073,
    8,
    14,
    0x5D295,
  },
#endif

#ifdef MP1_CpuFid1
#define
  {
    ///< MP1_CpuFid11074
    1074,
    8,
    22,
    0x5D296,
  },
#endif

#ifdef MP1_CpuFid2
#define
  {
    ///< MP1_CpuFid21075
    1075,
    8,
    30,
    0x5D297,
  },
#endif

#ifdef MP1_CpuFid3
#define
  {
    ///< MP1_CpuFid31076
    1076,
    8,
    6,
    0x5D298,
  },
#endif

#ifdef MP1_CpuFid4
#define
  {
    ///< MP1_CpuFid41077
    1077,
    8,
    14,
    0x5D299,
  },
#endif

#ifdef MP1_CpuFid5
#define
  {
    ///< MP1_CpuFid51078
    1078,
    8,
    22,
    0x5D29A,
  },
#endif

#ifdef MP1_CpuFid6
#define
  {
    ///< MP1_CpuFid61079
    1079,
    8,
    30,
    0x5D29B,
  },
#endif

#ifdef MP1_CpuFid7
#define
  {
    ///< MP1_CpuFid71080
    1080,
    8,
    6,
    0x5D29C,
  },
#endif

#ifdef MP1_CpuVid0
#define
  {
    ///< MP1_CpuVid01081
    1081,
    8,
    30,
    0x5D2A3,
  },
#endif

#ifdef MP1_CpuVid1
#define
  {
    ///< MP1_CpuVid11082
    1082,
    8,
    6,
    0x5D2A4,
  },
#endif

#ifdef MP1_CpuVid2
#define
  {
    ///< MP1_CpuVid21083
    1083,
    8,
    14,
    0x5D2A5,
  },
#endif

#ifdef MP1_CpuVid3
#define
  {
    ///< MP1_CpuVid31084
    1084,
    8,
    22,
    0x5D2A6,
  },
#endif

#ifdef MP1_CpuVid4
#define
  {
    ///< MP1_CpuVid41085
    1085,
    8,
    30,
    0x5D2A7,
  },
#endif

#ifdef MP1_CpuVid5
#define
  {
    ///< MP1_CpuVid51086
    1086,
    8,
    6,
    0x5D2A8,
  },
#endif

#ifdef MP1_CpuVid6
#define
  {
    ///< MP1_CpuVid61087
    1087,
    8,
    14,
    0x5D2A9,
  },
#endif

#ifdef MP1_CpuVid7
#define
  {
    ///< MP1_CpuVid71088
    1088,
    8,
    22,
    0x5D2AA,
  },
#endif

#ifdef MP1_CstateBoostActiveCoreThreshold
#define
  {
    ///< MP1_CstateBoostActiveCoreThreshold1089
    1089,
    4,
    8,
    0x5D31D,
  },
#endif

#ifdef MP1_DisableAllFrequencyChanges
#define
  {
    ///< MP1_DisableAllFrequencyChanges1090
    1090,
    1,
    17,
    0x5D31A,
  },
#endif

#ifdef MP1_EDC
#define
  {
    ///< MP1_EDC1091
    1091,
    8,
    28,
    0x5D313,
  },
#endif

#ifdef MP1_FIT_Limit
#define
  {
    ///< MP1_FIT_Limit1092
    1092,
    12,
    28,
    0x5D317,
  },
#endif

#ifdef MP1_Fclk1067ShadowVid
#define
  {
    ///< MP1_Fclk1067ShadowVid1093
    1093,
    8,
    0,
    0x5D2D4,
  },
#endif

#ifdef MP1_Fclk1067Vid
#define
  {
    ///< MP1_Fclk1067Vid1094
    1094,
    8,
    8,
    0x5D2CD,
  },
#endif

#ifdef MP1_Fclk1200ShadowVid
#define
  {
    ///< MP1_Fclk1200ShadowVid1095
    1095,
    8,
    8,
    0x5D2D5,
  },
#endif

#ifdef MP1_Fclk1200Vid
#define
  {
    ///< MP1_Fclk1200Vid1096
    1096,
    8,
    16,
    0x5D2CE,
  },
#endif

#ifdef MP1_Fclk1333ShadowVid
#define
  {
    ///< MP1_Fclk1333ShadowVid1097
    1097,
    8,
    16,
    0x5D2D6,
  },
#endif

#ifdef MP1_Fclk1333Vid
#define
  {
    ///< MP1_Fclk1333Vid1098
    1098,
    8,
    24,
    0x5D2CF,
  },
#endif

#ifdef MP1_Fclk1467ShadowVid
#define
  {
    ///< MP1_Fclk1467ShadowVid1099
    1099,
    8,
    24,
    0x5D2D7,
  },
#endif

#ifdef MP1_Fclk1467Vid
#define
  {
    ///< MP1_Fclk1467Vid1100
    1100,
    8,
    0,
    0x5D2D0,
  },
#endif

#ifdef MP1_Fclk1600ShadowVid
#define
  {
    ///< MP1_Fclk1600ShadowVid1101
    1101,
    8,
    0,
    0x5D2D8,
  },
#endif

#ifdef MP1_Fclk1600Vid
#define
  {
    ///< MP1_Fclk1600Vid1102
    1102,
    8,
    8,
    0x5D2D1,
  },
#endif

#ifdef MP1_Fclk800ShadowVid
#define
  {
    ///< MP1_Fclk800ShadowVid1103
    1103,
    8,
    16,
    0x5D2D2,
  },
#endif

#ifdef MP1_Fclk800Vid
#define
  {
    ///< MP1_Fclk800Vid1104
    1104,
    8,
    24,
    0x5D2CB,
  },
#endif

#ifdef MP1_Fclk933ShadowVid
#define
  {
    ///< MP1_Fclk933ShadowVid1105
    1105,
    8,
    24,
    0x5D2D3,
  },
#endif

#ifdef MP1_Fclk933Vid
#define
  {
    ///< MP1_Fclk933Vid1106
    1106,
    8,
    0,
    0x5D2CC,
  },
#endif

#ifdef MP1_Fmax
#define
  {
    ///< MP1_Fmax1107
    1107,
    8,
    12,
    0x5D31D,
  },
#endif

#ifdef MP1_Fmin
#define
  {
    ///< MP1_Fmin1108
    1108,
    8,
    20,
    0x5D31E,
  },
#endif

#ifdef MP1_ForceDeterminism
#define
  {
    ///< MP1_ForceDeterminism1109
    1109,
    1,
    18,
    0x5D31A,
  },
#endif

#ifdef MP1_LclkDid0
#define
  {
    ///< MP1_LclkDid01110
    1110,
    7,
    20,
    0x5D2B2,
  },
#endif

#ifdef MP1_LclkDid1
#define
  {
    ///< MP1_LclkDid11111
    1111,
    7,
    27,
    0x5D2B3,
  },
#endif

#ifdef MP1_LclkDid2
#define
  {
    ///< MP1_LclkDid21112
    1112,
    7,
    2,
    0x5D2B4,
  },
#endif

#ifdef MP1_LclkDid3
#define
  {
    ///< MP1_LclkDid31113
    1113,
    7,
    9,
    0x5D2B5,
  },
#endif

#ifdef MP1_LclkDid4
#define
  {
    ///< MP1_LclkDid41114
    1114,
    7,
    16,
    0x5D2B6,
  },
#endif

#ifdef MP1_LclkDid5
#define
  {
    ///< MP1_LclkDid51115
    1115,
    7,
    23,
    0x5D2B6,
  },
#endif

#ifdef MP1_LclkShadowVid0
#define
  {
    ///< MP1_LclkShadowVid01116
    1116,
    8,
    14,
    0x5D2BD,
  },
#endif

#ifdef MP1_LclkShadowVid1
#define
  {
    ///< MP1_LclkShadowVid11117
    1117,
    8,
    22,
    0x5D2BE,
  },
#endif

#ifdef MP1_LclkShadowVid2
#define
  {
    ///< MP1_LclkShadowVid21118
    1118,
    8,
    30,
    0x5D2BF,
  },
#endif

#ifdef MP1_LclkShadowVid3
#define
  {
    ///< MP1_LclkShadowVid31119
    1119,
    8,
    6,
    0x5D2C0,
  },
#endif

#ifdef MP1_LclkShadowVid4
#define
  {
    ///< MP1_LclkShadowVid41120
    1120,
    8,
    14,
    0x5D2C1,
  },
#endif

#ifdef MP1_LclkShadowVid5
#define
  {
    ///< MP1_LclkShadowVid51121
    1121,
    8,
    22,
    0x5D2C2,
  },
#endif

#ifdef MP1_LclkVid0
#define
  {
    ///< MP1_LclkVid01122
    1122,
    8,
    30,
    0x5D2B7,
  },
#endif

#ifdef MP1_LclkVid1
#define
  {
    ///< MP1_LclkVid11123
    1123,
    8,
    6,
    0x5D2B8,
  },
#endif

#ifdef MP1_LclkVid2
#define
  {
    ///< MP1_LclkVid21124
    1124,
    8,
    14,
    0x5D2B9,
  },
#endif

#ifdef MP1_LclkVid3
#define
  {
    ///< MP1_LclkVid31125
    1125,
    8,
    22,
    0x5D2BA,
  },
#endif

#ifdef MP1_LclkVid4
#define
  {
    ///< MP1_LclkVid41126
    1126,
    8,
    30,
    0x5D2BB,
  },
#endif

#ifdef MP1_LclkVid5
#define
  {
    ///< MP1_LclkVid51127
    1127,
    8,
    6,
    0x5D2BC,
  },
#endif

#ifdef MP1_MP1_GROUP0_DATA
#define
  {
    ///< MP1_MP1_GROUP0_DATA1128
    1128,
    96,
    0,
    0x5D7FC,
  },
#endif

#ifdef MP1_MP1_PUB_SPARE_FUSES
#define
  {
    ///< MP1_MP1_PUB_SPARE_FUSES1129
    1129,
    18,
    14,
    0x5D3C9,
  },
#endif

#ifdef MP1_MP1_SPARE
#define
  {
    ///< MP1_MP1_SPARE1130
    1130,
    1354,
    4,
    0x5D320,
  },
#endif

#ifdef MP1_MaxCpuCof
#define
  {
    ///< MP1_MaxCpuCof1131
    1131,
    6,
    6,
    0x5D2AC,
  },
#endif

#ifdef MP1_MaxTDC
#define
  {
    ///< MP1_MaxTDC1132
    1132,
    8,
    12,
    0x5D315,
  },
#endif

#ifdef MP1_MaxTDP
#define
  {
    ///< MP1_MaxTDP1133
    1133,
    8,
    12,
    0x5D311,
  },
#endif

#ifdef MP1_MinOverClockCpuVid
#define
  {
    ///< MP1_MinOverClockCpuVid1134
    1134,
    8,
    12,
    0x5D2AD,
  },
#endif

#ifdef MP1_MinTDC
#define
  {
    ///< MP1_MinTDC1135
    1135,
    8,
    20,
    0x5D316,
  },
#endif

#ifdef MP1_MinTDP
#define
  {
    ///< MP1_MinTDP1136
    1136,
    8,
    20,
    0x5D312,
  },
#endif

#ifdef MP1_Mp0clkDid
#define
  {
    ///< MP1_Mp0clkDid1137
    1137,
    7,
    10,
    0x5D2C9,
  },
#endif

#ifdef MP1_Mp1clkDid
#define
  {
    ///< MP1_Mp1clkDid1138
    1138,
    7,
    17,
    0x5D2CA,
  },
#endif

#ifdef MP1_OdprFuseSlope
#define
  {
    ///< MP1_OdprFuseSlope1139
    1139,
    14,
    0,
    0x5D294,
  },
#endif

#ifdef MP1_PPTLimitScalar
#define
  {
    ///< MP1_PPTLimitScalar1140
    1140,
    8,
    8,
    0x5D319,
  },
#endif

#ifdef MP1_PPTLimitScalarReportingEn
#define
  {
    ///< MP1_PPTLimitScalarReportingEn1141
    1141,
    1,
    16,
    0x5D31A,
  },
#endif

#ifdef MP1_PstateEn0
#define
  {
    ///< MP1_PstateEn01142
    1142,
    1,
    30,
    0x5D2AB,
  },
#endif

#ifdef MP1_PstateEn1
#define
  {
    ///< MP1_PstateEn11143
    1143,
    1,
    31,
    0x5D2AB,
  },
#endif

#ifdef MP1_PstateEn2
#define
  {
    ///< MP1_PstateEn21144
    1144,
    1,
    0,
    0x5D2AC,
  },
#endif

#ifdef MP1_PstateEn3
#define
  {
    ///< MP1_PstateEn31145
    1145,
    1,
    1,
    0x5D2AC,
  },
#endif

#ifdef MP1_PstateEn4
#define
  {
    ///< MP1_PstateEn41146
    1146,
    1,
    2,
    0x5D2AC,
  },
#endif

#ifdef MP1_PstateEn5
#define
  {
    ///< MP1_PstateEn51147
    1147,
    1,
    3,
    0x5D2AC,
  },
#endif

#ifdef MP1_PstateEn6
#define
  {
    ///< MP1_PstateEn61148
    1148,
    1,
    4,
    0x5D2AC,
  },
#endif

#ifdef MP1_PstateEn7
#define
  {
    ///< MP1_PstateEn71149
    1149,
    1,
    5,
    0x5D2AC,
  },
#endif

#ifdef MP1_ShubclkDid
#define
  {
    ///< MP1_ShubclkDid1150
    1150,
    7,
    21,
    0x5D2C6,
  },
#endif

#ifdef MP1_Sidd_RefTemp
#define
  {
    ///< MP1_Sidd_RefTemp1151
    1151,
    10,
    20,
    0x5D30A,
  },
#endif

#ifdef MP1_Sidd_RefTemp_Det
#define
  {
    ///< MP1_Sidd_RefTemp_Det1152
    1152,
    10,
    30,
    0x5D30B,
  },
#endif

#ifdef MP1_SmnclkDid
#define
  {
    ///< MP1_SmnclkDid1153
    1153,
    7,
    28,
    0x5D2C7,
  },
#endif

#ifdef MP1_Soc_Sidd_Tb
#define
  {
    ///< MP1_Soc_Sidd_Tb1154
    1154,
    12,
    8,
    0x5D2FD,
  },
#endif

#ifdef MP1_Soc_Sidd_Tb_WC
#define
  {
    ///< MP1_Soc_Sidd_Tb_WC1155
    1155,
    12,
    24,
    0x5D303,
  },
#endif

#ifdef MP1_Soc_Sidd_Tm
#define
  {
    ///< MP1_Soc_Sidd_Tm1156
    1156,
    12,
    28,
    0x5D2FB,
  },
#endif

#ifdef MP1_Soc_Sidd_Tm_WC
#define
  {
    ///< MP1_Soc_Sidd_Tm_WC1157
    1157,
    12,
    12,
    0x5D301,
  },
#endif

#ifdef MP1_Soc_Sidd_b
#define
  {
    ///< MP1_Soc_Sidd_b1158
    1158,
    12,
    16,
    0x5D2FA,
  },
#endif

#ifdef MP1_Soc_Sidd_b_WC
#define
  {
    ///< MP1_Soc_Sidd_b_WC1159
    1159,
    12,
    0,
    0x5D300,
  },
#endif

#ifdef MP1_Soc_Sidd_m
#define
  {
    ///< MP1_Soc_Sidd_m1160
    1160,
    12,
    4,
    0x5D2F8,
  },
#endif

#ifdef MP1_Soc_Sidd_m_WC
#define
  {
    ///< MP1_Soc_Sidd_m_WC1161
    1161,
    12,
    20,
    0x5D2FE,
  },
#endif

#ifdef MP1_SocclkDid
#define
  {
    ///< MP1_SocclkDid1162
    1162,
    7,
    14,
    0x5D2C5,
  },
#endif

#ifdef MP1_SuperVmaxThreshold
#define
  {
    ///< MP1_SuperVmaxThreshold1163
    1163,
    8,
    12,
    0x5D2B1,
  },
#endif

#ifdef MP1_SuperVminThreshold
#define
  {
    ///< MP1_SuperVminThreshold1164
    1164,
    8,
    4,
    0x5D2B0,
  },
#endif

#ifdef MP1_TDC
#define
  {
    ///< MP1_TDC1165
    1165,
    8,
    4,
    0x5D314,
  },
#endif

#ifdef MP1_TDP
#define
  {
    ///< MP1_TDP1166
    1166,
    8,
    4,
    0x5D310,
  },
#endif

#ifdef MP1_Tambient_WC
#define
  {
    ///< MP1_Tambient_WC1167
    1167,
    8,
    8,
    0x5D30D,
  },
#endif

#ifdef MP1_Theta_ja
#define
  {
    ///< MP1_Theta_ja1168
    1168,
    12,
    16,
    0x5D30E,
  },
#endif

#ifdef MP1_TjMax
#define
  {
    ///< MP1_TjMax1169
    1169,
    8,
    28,
    0x5D30F,
  },
#endif

#ifdef MP1_VddcrSocVminShadowVid
#define
  {
    ///< MP1_VddcrSocVminShadowVid1170
    1170,
    8,
    6,
    0x5D2C4,
  },
#endif

#ifdef MP1_VddcrSocVminVid
#define
  {
    ///< MP1_VddcrSocVminVid1171
    1171,
    8,
    30,
    0x5D2C3,
  },
#endif

#ifdef MP1_Vddm_Sidd_Tb_WC
#define
  {
    ///< MP1_Vddm_Sidd_Tb_WC1172
    1172,
    12,
    8,
    0x5D309,
  },
#endif

#ifdef MP1_Vddm_Sidd_Tm_WC
#define
  {
    ///< MP1_Vddm_Sidd_Tm_WC1173
    1173,
    12,
    28,
    0x5D307,
  },
#endif

#ifdef MP1_Vddm_Sidd_b_WC
#define
  {
    ///< MP1_Vddm_Sidd_b_WC1174
    1174,
    12,
    16,
    0x5D306,
  },
#endif

#ifdef MP1_Vddm_Sidd_m_WC
#define
  {
    ///< MP1_Vddm_Sidd_m_WC1175
    1175,
    12,
    4,
    0x5D304,
  },
#endif

#ifdef MP1_VminFrequency
#define
  {
    ///< MP1_VminFrequency1176
    1176,
    8,
    28,
    0x5D31F,
  },
#endif

#ifdef MP1_WLBThreshold
#define
  {
    ///< MP1_WLBThreshold1177
    1177,
    8,
    20,
    0x5D2AE,
  },
#endif

#ifdef MP1_WLBThresholdBypass
#define
  {
    ///< MP1_WLBThresholdBypass1178
    1178,
    8,
    28,
    0x5D2AF,
  },
#endif

#ifdef MP1_WaflclkDid
#define
  {
    ///< MP1_WaflclkDid1179
    1179,
    7,
    3,
    0x5D2C8,
  },
#endif

#ifdef MP5_CLDO_GMI2_BYPASS_DIS
#define
  {
    ///< MP5_CLDO_GMI2_BYPASS_DIS1180
    1180,
    1,
    29,
    0x1A37,
  },
#endif

#ifdef MP5_CLDO_GMI2_SEL_SRC_VDDIO_MEM
#define
  {
    ///< MP5_CLDO_GMI2_SEL_SRC_VDDIO_MEM1181
    1181,
    1,
    30,
    0x1A37,
  },
#endif

#ifdef MP5_CORE_DISABLE
#define
  {
    ///< MP5_CORE_DISABLE1182
    1182,
    8,
    0,
    0x1A38,
  },
#endif

#ifdef MP5_CPU_PWROK_REFCLK_GAP_CYCLES
#define
  {
    ///< MP5_CPU_PWROK_REFCLK_GAP_CYCLES1183
    1183,
    1,
    26,
    0x1A37,
  },
#endif

#ifdef MP5_DISABLE_MP5_BIHR
#define
  {
    ///< MP5_DISABLE_MP5_BIHR1184
    1184,
    1,
    7,
    0x1A34,
  },
#endif

#ifdef MP5_DISABLE_MP5_MBIST
#define
  {
    ///< MP5_DISABLE_MP5_MBIST1185
    1185,
    1,
    8,
    0x1A35,
  },
#endif

#ifdef MP5_DISABLE_PCS_PHY_WORKAROUND
#define
  {
    ///< MP5_DISABLE_PCS_PHY_WORKAROUND1186
    1186,
    1,
    27,
    0x1A37,
  },
#endif

#ifdef MP5_DISTRIBUTE_LDO_FUSES
#define
  {
    ///< MP5_DISTRIBUTE_LDO_FUSES1187
    1187,
    1,
    10,
    0x1A35,
  },
#endif

#ifdef MP5_ENABLE_DBGU_CCD_POST_CODES
#define
  {
    ///< MP5_ENABLE_DBGU_CCD_POST_CODES1188
    1188,
    1,
    24,
    0x1A37,
  },
#endif

#ifdef MP5_ENABLE_RSMU_WDT
#define
  {
    ///< MP5_ENABLE_RSMU_WDT1189
    1189,
    1,
    9,
    0x1A35,
  },
#endif

#ifdef MP5_ENABLE_SBI_POST_CODES
#define
  {
    ///< MP5_ENABLE_SBI_POST_CODES1190
    1190,
    1,
    11,
    0x1A35,
  },
#endif

#ifdef MP5_HARVESTING_FUSES
#define
  {
    ///< MP5_HARVESTING_FUSES1191
    1191,
    23,
    9,
    0x1A39,
  },
#endif

#ifdef MP5_L3_RESET_MILESTONE
#define
  {
    ///< MP5_L3_RESET_MILESTONE1192
    1192,
    2,
    14,
    0x1A35,
  },
#endif

#ifdef MP5_LOAD_DIAG_BOOT_LOADER
#define
  {
    ///< MP5_LOAD_DIAG_BOOT_LOADER1193
    1193,
    1,
    16,
    0x1A36,
  },
#endif

#ifdef MP5_MP5_GROUP0_DATA
#define
  {
    ///< MP5_MP5_GROUP0_DATA1194
    1194,
    64,
    0,
    0x1BA4,
  },
#endif

#ifdef MP5_MP5_NONSECURE_FUSES
#define
  {
    ///< MP5_MP5_NONSECURE_FUSES1195
    1195,
    1,
    31,
    0x1A37,
  },
#endif

#ifdef MP5_MP5_WRITE_DISABLE
#define
  {
    ///< MP5_MP5_WRITE_DISABLE1196
    1196,
    1,
    0,
    0x1A34,
  },
#endif

#ifdef MP5_PMFW_Core_Cac_b
#define
  {
    ///< MP5_PMFW_Core_Cac_b1197
    1197,
    12,
    26,
    0x1ADF,
  },
#endif

#ifdef MP5_PMFW_Core_Cac_m
#define
  {
    ///< MP5_PMFW_Core_Cac_m1198
    1198,
    12,
    14,
    0x1ADD,
  },
#endif

#ifdef MP5_PMFW_Core_Cold_temp
#define
  {
    ///< MP5_PMFW_Core_Cold_temp1199
    1199,
    8,
    22,
    0x1ADA,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE01200
    1200,
    12,
    14,
    0x1A41,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE11201
    1201,
    12,
    26,
    0x1A43,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE21202
    1202,
    12,
    6,
    0x1A44,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX0_CORE31203
    1203,
    12,
    18,
    0x1A46,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE01204
    1204,
    12,
    30,
    0x1A47,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE11205
    1205,
    12,
    10,
    0x1A49,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE21206
    1206,
    12,
    22,
    0x1A4A,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_COLD_CCX1_CORE31207
    1207,
    12,
    2,
    0x1A4C,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_GuardBand
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_GuardBand1208
    1208,
    12,
    14,
    0x1AAD,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE01209
    1209,
    12,
    14,
    0x1A59,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE11210
    1210,
    12,
    26,
    0x1A5B,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE21211
    1211,
    12,
    6,
    0x1A5C,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX0_CORE31212
    1212,
    12,
    18,
    0x1A5E,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE01213
    1213,
    12,
    30,
    0x1A5F,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE11214
    1214,
    12,
    10,
    0x1A61,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE21215
    1215,
    12,
    22,
    0x1A62,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_HOT_CCX1_CORE31216
    1216,
    12,
    2,
    0x1A64,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE01217
    1217,
    12,
    14,
    0x1A4D,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE11218
    1218,
    12,
    26,
    0x1A4F,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE21219
    1219,
    12,
    6,
    0x1A50,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX0_CORE31220
    1220,
    12,
    18,
    0x1A52,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE01221
    1221,
    12,
    30,
    0x1A53,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE11222
    1222,
    12,
    10,
    0x1A55,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE21223
    1223,
    12,
    22,
    0x1A56,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_A_MED_CCX1_CORE31224
    1224,
    12,
    2,
    0x1A58,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE01225
    1225,
    12,
    14,
    0x1A65,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE11226
    1226,
    12,
    26,
    0x1A67,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE21227
    1227,
    12,
    6,
    0x1A68,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX0_CORE31228
    1228,
    12,
    18,
    0x1A6A,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE01229
    1229,
    12,
    30,
    0x1A6B,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE11230
    1230,
    12,
    10,
    0x1A6D,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE21231
    1231,
    12,
    22,
    0x1A6E,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_COLD_CCX1_CORE31232
    1232,
    12,
    2,
    0x1A70,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_GuardBand
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_GuardBand1233
    1233,
    12,
    26,
    0x1AAF,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE01234
    1234,
    12,
    14,
    0x1A7D,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE11235
    1235,
    12,
    26,
    0x1A7F,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE21236
    1236,
    12,
    6,
    0x1A80,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX0_CORE31237
    1237,
    12,
    18,
    0x1A82,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE01238
    1238,
    12,
    30,
    0x1A83,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE11239
    1239,
    12,
    10,
    0x1A85,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE21240
    1240,
    12,
    22,
    0x1A86,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_HOT_CCX1_CORE31241
    1241,
    12,
    2,
    0x1A88,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE01242
    1242,
    12,
    14,
    0x1A71,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE11243
    1243,
    12,
    26,
    0x1A73,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE21244
    1244,
    12,
    6,
    0x1A74,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX0_CORE31245
    1245,
    12,
    18,
    0x1A76,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE01246
    1246,
    12,
    30,
    0x1A77,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE11247
    1247,
    12,
    10,
    0x1A79,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE21248
    1248,
    12,
    22,
    0x1A7A,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_B_MED_CCX1_CORE31249
    1249,
    12,
    2,
    0x1A7C,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE01250
    1250,
    12,
    14,
    0x1A89,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE11251
    1251,
    12,
    26,
    0x1A8B,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE21252
    1252,
    12,
    6,
    0x1A8C,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX0_CORE31253
    1253,
    12,
    18,
    0x1A8E,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE01254
    1254,
    12,
    30,
    0x1A8F,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE11255
    1255,
    12,
    10,
    0x1A91,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE21256
    1256,
    12,
    22,
    0x1A92,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_COLD_CCX1_CORE31257
    1257,
    12,
    2,
    0x1A94,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_GuardBand
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_GuardBand1258
    1258,
    12,
    6,
    0x1AB0,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE01259
    1259,
    12,
    14,
    0x1AA1,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE11260
    1260,
    12,
    26,
    0x1AA3,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE21261
    1261,
    12,
    6,
    0x1AA4,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX0_CORE31262
    1262,
    12,
    18,
    0x1AA6,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE01263
    1263,
    12,
    30,
    0x1AA7,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE11264
    1264,
    12,
    10,
    0x1AA9,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE21265
    1265,
    12,
    22,
    0x1AAA,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_HOT_CCX1_CORE31266
    1266,
    12,
    2,
    0x1AAC,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE01267
    1267,
    12,
    14,
    0x1A95,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE11268
    1268,
    12,
    26,
    0x1A97,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE21269
    1269,
    12,
    6,
    0x1A98,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX0_CORE31270
    1270,
    12,
    18,
    0x1A9A,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE01271
    1271,
    12,
    30,
    0x1A9B,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE11272
    1272,
    12,
    10,
    0x1A9D,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE21273
    1273,
    12,
    22,
    0x1A9E,
  },
#endif

#ifdef MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_FtoP_C_MED_CCX1_CORE31274
    1274,
    12,
    2,
    0x1AA0,
  },
#endif

#ifdef MP5_PMFW_Core_Hot_temp
#define
  {
    ///< MP5_PMFW_Core_Hot_temp1275
    1275,
    8,
    6,
    0x1ADC,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE01276
    1276,
    7,
    27,
    0x1AF3,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE11277
    1277,
    7,
    9,
    0x1AF5,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE21278
    1278,
    7,
    23,
    0x1AF6,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX0_CORE31279
    1279,
    7,
    5,
    0x1AF8,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE01280
    1280,
    7,
    1,
    0x1AFC,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE11281
    1281,
    7,
    15,
    0x1AFD,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE21282
    1282,
    7,
    29,
    0x1AFF,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_HI_CCX1_CORE31283
    1283,
    7,
    11,
    0x1B01,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE0
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE01284
    1284,
    7,
    20,
    0x1AF2,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE1
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE11285
    1285,
    7,
    2,
    0x1AF4,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE2
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE21286
    1286,
    7,
    16,
    0x1AF6,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE3
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX0_CORE31287
    1287,
    7,
    30,
    0x1AF7,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE0
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE01288
    1288,
    7,
    26,
    0x1AFB,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE1
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE11289
    1289,
    7,
    8,
    0x1AFD,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE2
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE21290
    1290,
    7,
    22,
    0x1AFE,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE3
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Offset_Value_LO_CCX1_CORE31291
    1291,
    7,
    4,
    0x1B00,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Value_HI
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Value_HI1292
    1292,
    10,
    10,
    0x1AF1,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Value_LO
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Value_LO1293
    1293,
    10,
    0,
    0x1AF0,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Voltage_HI
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Voltage_HI1294
    1294,
    8,
    24,
    0x1AEF,
  },
#endif

#ifdef MP5_PMFW_Core_LDO_FDD_Voltage_LO
#define
  {
    ///< MP5_PMFW_Core_LDO_FDD_Voltage_LO1295
    1295,
    8,
    16,
    0x1AEE,
  },
#endif

#ifdef MP5_PMFW_Core_Med_temp
#define
  {
    ///< MP5_PMFW_Core_Med_temp1296
    1296,
    8,
    30,
    0x1ADB,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_COLD_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_COLD_CCX01297
    1297,
    12,
    18,
    0x1AB2,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_COLD_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_COLD_CCX11298
    1298,
    12,
    30,
    0x1AB3,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_HOT_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_HOT_CCX01299
    1299,
    12,
    2,
    0x1AB8,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_HOT_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_HOT_CCX11300
    1300,
    12,
    14,
    0x1AB9,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_MED_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_MED_CCX01301
    1301,
    12,
    10,
    0x1AB5,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_A_MED_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_A_MED_CCX11302
    1302,
    12,
    22,
    0x1AB6,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_COLD_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_COLD_CCX01303
    1303,
    12,
    26,
    0x1ABB,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_COLD_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_COLD_CCX11304
    1304,
    12,
    6,
    0x1ABC,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_HOT_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_HOT_CCX01305
    1305,
    12,
    10,
    0x1AC1,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_HOT_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_HOT_CCX11306
    1306,
    12,
    22,
    0x1AC2,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_MED_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_MED_CCX01307
    1307,
    12,
    18,
    0x1ABE,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_B_MED_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_B_MED_CCX11308
    1308,
    12,
    30,
    0x1ABF,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_COLD_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_COLD_CCX01309
    1309,
    12,
    2,
    0x1AC4,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_COLD_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_COLD_CCX11310
    1310,
    12,
    14,
    0x1AC5,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_HOT_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_HOT_CCX01311
    1311,
    12,
    18,
    0x1ACA,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_HOT_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_HOT_CCX11312
    1312,
    12,
    30,
    0x1ACB,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_MED_CCX0
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_MED_CCX01313
    1313,
    12,
    26,
    0x1AC7,
  },
#endif

#ifdef MP5_PMFW_Core_PtoV_C_MED_CCX1
#define
  {
    ///< MP5_PMFW_Core_PtoV_C_MED_CCX11314
    1314,
    12,
    6,
    0x1AC8,
  },
#endif

#ifdef MP5_PMFW_Core_Sidd_Tb
#define
  {
    ///< MP5_PMFW_Core_Sidd_Tb1315
    1315,
    12,
    10,
    0x1AE5,
  },
#endif

#ifdef MP5_PMFW_Core_Sidd_Tm
#define
  {
    ///< MP5_PMFW_Core_Sidd_Tm1316
    1316,
    12,
    30,
    0x1AE3,
  },
#endif

#ifdef MP5_PMFW_Core_Sidd_b
#define
  {
    ///< MP5_PMFW_Core_Sidd_b1317
    1317,
    12,
    18,
    0x1AE2,
  },
#endif

#ifdef MP5_PMFW_Core_Sidd_m
#define
  {
    ///< MP5_PMFW_Core_Sidd_m1318
    1318,
    12,
    6,
    0x1AE0,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_A_COLD
#define
  {
    ///< MP5_PMFW_L3_FtoV_A_COLD1319
    1319,
    12,
    10,
    0x1ACD,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_A_HOT
#define
  {
    ///< MP5_PMFW_L3_FtoV_A_HOT1320
    1320,
    12,
    2,
    0x1AD0,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_A_MED
#define
  {
    ///< MP5_PMFW_L3_FtoV_A_MED1321
    1321,
    12,
    22,
    0x1ACE,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_B_COLD
#define
  {
    ///< MP5_PMFW_L3_FtoV_B_COLD1322
    1322,
    12,
    14,
    0x1AD1,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_B_HOT
#define
  {
    ///< MP5_PMFW_L3_FtoV_B_HOT1323
    1323,
    12,
    6,
    0x1AD4,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_B_MED
#define
  {
    ///< MP5_PMFW_L3_FtoV_B_MED1324
    1324,
    12,
    26,
    0x1AD3,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_C_COLD
#define
  {
    ///< MP5_PMFW_L3_FtoV_C_COLD1325
    1325,
    12,
    18,
    0x1AD6,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_C_HOT
#define
  {
    ///< MP5_PMFW_L3_FtoV_C_HOT1326
    1326,
    12,
    10,
    0x1AD9,
  },
#endif

#ifdef MP5_PMFW_L3_FtoV_C_MED
#define
  {
    ///< MP5_PMFW_L3_FtoV_C_MED1327
    1327,
    12,
    30,
    0x1AD7,
  },
#endif

#ifdef MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX0
#define
  {
    ///< MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX01328
    1328,
    7,
    19,
    0x1AFA,
  },
#endif

#ifdef MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX1
#define
  {
    ///< MP5_PMFW_L3_LDO_FDD_Offset_Value_HI_CCX11329
    1329,
    7,
    25,
    0x1B03,
  },
#endif

#ifdef MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX0
#define
  {
    ///< MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX01330
    1330,
    7,
    12,
    0x1AF9,
  },
#endif

#ifdef MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX1
#define
  {
    ///< MP5_PMFW_L3_LDO_FDD_Offset_Value_LO_CCX11331
    1331,
    7,
    18,
    0x1B02,
  },
#endif

#ifdef MP5_PMFW_MP5_PMFW_PUB_SPARE_FUSES
#define
  {
    ///< MP5_PMFW_MP5_PMFW_PUB_SPARE_FUSES1332
    1332,
    16,
    16,
    0x1B3A,
  },
#endif

#ifdef MP5_PMFW_MP5_SPARE
#define
  {
    ///< MP5_PMFW_MP5_SPARE1333
    1333,
    432,
    0,
    0x1B04,
  },
#endif

#ifdef MP5_PMFW_OdprFuseSlope
#define
  {
    ///< MP5_PMFW_OdprFuseSlope1334
    1334,
    14,
    0,
    0x1A40,
  },
#endif

#ifdef MP5_PMFW_Sidd_RefTemp
#define
  {
    ///< MP5_PMFW_Sidd_RefTemp1335
    1335,
    10,
    6,
    0x1AEC,
  },
#endif

#ifdef MP5_PMFW_Vddm_Sidd_Tb
#define
  {
    ///< MP5_PMFW_Vddm_Sidd_Tb1336
    1336,
    12,
    26,
    0x1AEB,
  },
#endif

#ifdef MP5_PMFW_Vddm_Sidd_Tm
#define
  {
    ///< MP5_PMFW_Vddm_Sidd_Tm1337
    1337,
    12,
    14,
    0x1AE9,
  },
#endif

#ifdef MP5_PMFW_Vddm_Sidd_b
#define
  {
    ///< MP5_PMFW_Vddm_Sidd_b1338
    1338,
    12,
    2,
    0x1AE8,
  },
#endif

#ifdef MP5_PMFW_Vddm_Sidd_m
#define
  {
    ///< MP5_PMFW_Vddm_Sidd_m1339
    1339,
    12,
    22,
    0x1AE6,
  },
#endif

#ifdef MP5_RELEASE_CPU_RESET
#define
  {
    ///< MP5_RELEASE_CPU_RESET1340
    1340,
    1,
    22,
    0x1A36,
  },
#endif

#ifdef MP5_RSMU_FUSE_VALID
#define
  {
    ///< MP5_RSMU_FUSE_VALID1341
    1341,
    1,
    28,
    0x1A37,
  },
#endif

#ifdef MP5_RUN_BIHR
#define
  {
    ///< MP5_RUN_BIHR1342
    1342,
    1,
    5,
    0x1A34,
  },
#endif

#ifdef MP5_RUN_MBIST
#define
  {
    ///< MP5_RUN_MBIST1343
    1343,
    1,
    6,
    0x1A34,
  },
#endif

#ifdef MP5_SET_BOOTROM_STARTUP_CLOCKS
#define
  {
    ///< MP5_SET_BOOTROM_STARTUP_CLOCKS1344
    1344,
    1,
    25,
    0x1A37,
  },
#endif

#ifdef MP5_SKIP_EXIT_BYPASS
#define
  {
    ///< MP5_SKIP_EXIT_BYPASS1345
    1345,
    1,
    23,
    0x1A36,
  },
#endif

#ifdef MP5_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE
#define
  {
    ///< MP5_SKIP_WAITING_FOR_PCIE_PHY_CALIBRATION_DONE1346
    1346,
    1,
    17,
    0x1A36,
  },
#endif

#ifdef MP5_SMT_ENABLE
#define
  {
    ///< MP5_SMT_ENABLE1347
    1347,
    1,
    8,
    0x1A39,
  },
#endif

#ifdef MP5_SRAM_CUSTOM_RM
#define
  {
    ///< MP5_SRAM_CUSTOM_RM1348
    1348,
    14,
    12,
    0x1A3D,
  },
#endif

#ifdef MP5_SRAM_HD_BC1
#define
  {
    ///< MP5_SRAM_HD_BC11349
    1349,
    1,
    28,
    0x1A3F,
  },
#endif

#ifdef MP5_SRAM_HD_BC2
#define
  {
    ///< MP5_SRAM_HD_BC21350
    1350,
    1,
    29,
    0x1A3F,
  },
#endif

#ifdef MP5_SRAM_PDP_BC1
#define
  {
    ///< MP5_SRAM_PDP_BC11351
    1351,
    1,
    26,
    0x1A3F,
  },
#endif

#ifdef MP5_SRAM_PDP_BC2
#define
  {
    ///< MP5_SRAM_PDP_BC21352
    1352,
    1,
    27,
    0x1A3F,
  },
#endif

#ifdef MP5_SRAM_RM
#define
  {
    ///< MP5_SRAM_RM1353
    1353,
    12,
    0,
    0x1A3C,
  },
#endif

#ifdef MP5_SRAM_SPARE_0
#define
  {
    ///< MP5_SRAM_SPARE_01354
    1354,
    2,
    30,
    0x1A3F,
  },
#endif

#ifdef MP5_WAFL_DBG_INTERLOCK_1
#define
  {
    ///< MP5_WAFL_DBG_INTERLOCK_11355
    1355,
    2,
    12,
    0x1A35,
  },
#endif

#ifdef MP5_WAFL_DBG_INTERLOCK_2
#define
  {
    ///< MP5_WAFL_DBG_INTERLOCK_21356
    1356,
    2,
    18,
    0x1A36,
  },
#endif

#ifdef MP5_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE
#define
  {
    ///< MP5_WAFL_PARTNER_DETECT_DESKEW_TIMER_DISABLE1357
    1357,
    1,
    20,
    0x1A36,
  },
#endif

#ifdef MP5_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE
#define
  {
    ///< MP5_WAFL_READYSERIAL_DESKEW_TIMER_DISABLE1358
    1358,
    1,
    21,
    0x1A36,
  },
#endif

#ifdef MP5_WaflInvertLinkAddr0
#define
  {
    ///< MP5_WaflInvertLinkAddr01359
    1359,
    1,
    3,
    0x1A34,
  },
#endif

#ifdef MP5_WaflInvertLinkAddr1
#define
  {
    ///< MP5_WaflInvertLinkAddr11360
    1360,
    1,
    4,
    0x1A34,
  },
#endif

#ifdef MP5_WaflInvertSmnAddr0
#define
  {
    ///< MP5_WaflInvertSmnAddr01361
    1361,
    1,
    1,
    0x1A34,
  },
#endif

#ifdef MP5_WaflInvertSmnAddr1
#define
  {
    ///< MP5_WaflInvertSmnAddr11362
    1362,
    1,
    2,
    0x1A34,
  },
#endif

#ifdef NBIF0_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< NBIF0_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES1363
    1363,
    18,
    14,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_NBIF_SSP_GENERIC_A_WRITE_DISABLE
#define
  {
    ///< NBIF0_NBIF_SSP_GENERIC_A_WRITE_DISABLE1364
    1364,
    1,
    1,
    0x5D3CC,
  },
#endif

#ifdef NBIF0_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF0_STRAP_BIF_FUSESTRAP_VALID1365
    1365,
    1,
    0,
    0x5D3CC,
  },
#endif

#ifdef NBIF0_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF0_STRAP_BIF_RESERVED_BIF_STRAP21366
    1366,
    2,
    6,
    0x5D3CC,
  },
#endif

#ifdef NBIF0_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF0_STRAP_BIF_RESERVED_BIF_STRAP31367
    1367,
    32,
    8,
    0x5D3CD,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01368
    1368,
    1,
    8,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11369
    1369,
    1,
    9,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21370
    1370,
    1,
    10,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_HWREV_LSB21371
    1371,
    2,
    2,
    0x5D3CC,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_SWREV_LSB21372
    1372,
    2,
    4,
    0x5D3CC,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01373
    1373,
    1,
    11,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11374
    1374,
    1,
    12,
    0x5D3D1,
  },
#endif

#ifdef NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF0_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21375
    1375,
    1,
    13,
    0x5D3D1,
  },
#endif

#ifdef NBIF10_NBIF10_GROUP0_DATA
#define
  {
    ///< NBIF10_NBIF10_GROUP0_DATA1376
    1376,
    128,
    0,
    0x5D828,
  },
#endif

#ifdef NBIF10_NBIF_SSP_NTB_PUB_SPARE_FUSES
#define
  {
    ///< NBIF10_NBIF_SSP_NTB_PUB_SPARE_FUSES1377
    1377,
    10,
    22,
    0x5D442,
  },
#endif

#ifdef NBIF10_NBIF_SSP_NTB_WRITE_DISABLE
#define
  {
    ///< NBIF10_NBIF_SSP_NTB_WRITE_DISABLE1378
    1378,
    1,
    1,
    0x5D43C,
  },
#endif

#ifdef NBIF10_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF10_STRAP_BIF_FUSESTRAP_VALID1379
    1379,
    1,
    0,
    0x5D43C,
  },
#endif

#ifdef NBIF10_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF10_STRAP_BIF_RESERVED_BIF_STRAP21380
    1380,
    2,
    6,
    0x5D43C,
  },
#endif

#ifdef NBIF10_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF10_STRAP_BIF_RESERVED_BIF_STRAP31381
    1381,
    32,
    8,
    0x5D43D,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_DN_DEVNUM_DEV0
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_DN_DEVNUM_DEV01382
    1382,
    5,
    8,
    0x5D441,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_DN_FUNCID_DEV0
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_DN_FUNCID_DEV01383
    1383,
    3,
    13,
    0x5D441,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01384
    1384,
    1,
    16,
    0x5D442,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11385
    1385,
    1,
    17,
    0x5D442,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21386
    1386,
    1,
    18,
    0x5D442,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_HWREV_LSB21387
    1387,
    2,
    2,
    0x5D43C,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_SWREV_LSB21388
    1388,
    2,
    4,
    0x5D43C,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01389
    1389,
    1,
    19,
    0x5D442,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11390
    1390,
    1,
    20,
    0x5D442,
  },
#endif

#ifdef NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF10_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21391
    1391,
    1,
    21,
    0x5D442,
  },
#endif

#ifdef NBIF11_NBIF11_GROUP0_DATA
#define
  {
    ///< NBIF11_NBIF11_GROUP0_DATA1392
    1392,
    128,
    0,
    0x5D838,
  },
#endif

#ifdef NBIF11_NBIF_SSP_NTB_PUB_SPARE_FUSES
#define
  {
    ///< NBIF11_NBIF_SSP_NTB_PUB_SPARE_FUSES1393
    1393,
    10,
    22,
    0x5D44A,
  },
#endif

#ifdef NBIF11_NBIF_SSP_NTB_WRITE_DISABLE
#define
  {
    ///< NBIF11_NBIF_SSP_NTB_WRITE_DISABLE1394
    1394,
    1,
    1,
    0x5D444,
  },
#endif

#ifdef NBIF11_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF11_STRAP_BIF_FUSESTRAP_VALID1395
    1395,
    1,
    0,
    0x5D444,
  },
#endif

#ifdef NBIF11_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF11_STRAP_BIF_RESERVED_BIF_STRAP21396
    1396,
    2,
    6,
    0x5D444,
  },
#endif

#ifdef NBIF11_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF11_STRAP_BIF_RESERVED_BIF_STRAP31397
    1397,
    32,
    8,
    0x5D445,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_DN_DEVNUM_DEV0
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_DN_DEVNUM_DEV01398
    1398,
    5,
    8,
    0x5D449,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_DN_FUNCID_DEV0
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_DN_FUNCID_DEV01399
    1399,
    3,
    13,
    0x5D449,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01400
    1400,
    1,
    16,
    0x5D44A,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11401
    1401,
    1,
    17,
    0x5D44A,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21402
    1402,
    1,
    18,
    0x5D44A,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_HWREV_LSB21403
    1403,
    2,
    2,
    0x5D444,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_SWREV_LSB21404
    1404,
    2,
    4,
    0x5D444,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01405
    1405,
    1,
    19,
    0x5D44A,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11406
    1406,
    1,
    20,
    0x5D44A,
  },
#endif

#ifdef NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF11_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21407
    1407,
    1,
    21,
    0x5D44A,
  },
#endif

#ifdef NBIF1_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< NBIF1_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES1408
    1408,
    18,
    14,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_NBIF_SSP_GENERIC_A_WRITE_DISABLE
#define
  {
    ///< NBIF1_NBIF_SSP_GENERIC_A_WRITE_DISABLE1409
    1409,
    1,
    1,
    0x5D3D4,
  },
#endif

#ifdef NBIF1_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF1_STRAP_BIF_FUSESTRAP_VALID1410
    1410,
    1,
    0,
    0x5D3D4,
  },
#endif

#ifdef NBIF1_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF1_STRAP_BIF_RESERVED_BIF_STRAP21411
    1411,
    2,
    6,
    0x5D3D4,
  },
#endif

#ifdef NBIF1_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF1_STRAP_BIF_RESERVED_BIF_STRAP31412
    1412,
    32,
    8,
    0x5D3D5,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01413
    1413,
    1,
    8,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11414
    1414,
    1,
    9,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21415
    1415,
    1,
    10,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_HWREV_LSB21416
    1416,
    2,
    2,
    0x5D3D4,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_SWREV_LSB21417
    1417,
    2,
    4,
    0x5D3D4,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01418
    1418,
    1,
    11,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11419
    1419,
    1,
    12,
    0x5D3D9,
  },
#endif

#ifdef NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF1_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21420
    1420,
    1,
    13,
    0x5D3D9,
  },
#endif

#ifdef NBIF2_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< NBIF2_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES1421
    1421,
    18,
    14,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_NBIF_SSP_GENERIC_A_WRITE_DISABLE
#define
  {
    ///< NBIF2_NBIF_SSP_GENERIC_A_WRITE_DISABLE1422
    1422,
    1,
    1,
    0x5D3DC,
  },
#endif

#ifdef NBIF2_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF2_STRAP_BIF_FUSESTRAP_VALID1423
    1423,
    1,
    0,
    0x5D3DC,
  },
#endif

#ifdef NBIF2_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF2_STRAP_BIF_RESERVED_BIF_STRAP21424
    1424,
    2,
    6,
    0x5D3DC,
  },
#endif

#ifdef NBIF2_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF2_STRAP_BIF_RESERVED_BIF_STRAP31425
    1425,
    32,
    8,
    0x5D3DD,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01426
    1426,
    1,
    8,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11427
    1427,
    1,
    9,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21428
    1428,
    1,
    10,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_HWREV_LSB21429
    1429,
    2,
    2,
    0x5D3DC,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_SWREV_LSB21430
    1430,
    2,
    4,
    0x5D3DC,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01431
    1431,
    1,
    11,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11432
    1432,
    1,
    12,
    0x5D3E1,
  },
#endif

#ifdef NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF2_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21433
    1433,
    1,
    13,
    0x5D3E1,
  },
#endif

#ifdef NBIF3_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< NBIF3_NBIF_SSP_GENERIC_A_PUB_SPARE_FUSES1434
    1434,
    18,
    14,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_NBIF_SSP_GENERIC_A_WRITE_DISABLE
#define
  {
    ///< NBIF3_NBIF_SSP_GENERIC_A_WRITE_DISABLE1435
    1435,
    1,
    1,
    0x5D3E4,
  },
#endif

#ifdef NBIF3_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF3_STRAP_BIF_FUSESTRAP_VALID1436
    1436,
    1,
    0,
    0x5D3E4,
  },
#endif

#ifdef NBIF3_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF3_STRAP_BIF_RESERVED_BIF_STRAP21437
    1437,
    2,
    6,
    0x5D3E4,
  },
#endif

#ifdef NBIF3_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF3_STRAP_BIF_RESERVED_BIF_STRAP31438
    1438,
    32,
    8,
    0x5D3E5,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01439
    1439,
    1,
    8,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11440
    1440,
    1,
    9,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21441
    1441,
    1,
    10,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_HWREV_LSB21442
    1442,
    2,
    2,
    0x5D3E4,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_SWREV_LSB21443
    1443,
    2,
    4,
    0x5D3E4,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01444
    1444,
    1,
    11,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11445
    1445,
    1,
    12,
    0x5D3E9,
  },
#endif

#ifdef NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF3_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21446
    1446,
    1,
    13,
    0x5D3E9,
  },
#endif

#ifdef NBIF4_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< NBIF4_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES1447
    1447,
    22,
    10,
    0x5D3F9,
  },
#endif

#ifdef NBIF4_NBIF_SSP_GENERIC_B_WRITE_DISABLE
#define
  {
    ///< NBIF4_NBIF_SSP_GENERIC_B_WRITE_DISABLE1448
    1448,
    1,
    1,
    0x5D3EC,
  },
#endif

#ifdef NBIF4_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF4_STRAP_BIF_FUSESTRAP_VALID1449
    1449,
    1,
    0,
    0x5D3EC,
  },
#endif

#ifdef NBIF4_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF4_STRAP_BIF_RESERVED_BIF_STRAP31450
    1450,
    32,
    6,
    0x5D3EC,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F31451
    1451,
    1,
    4,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F41452
    1452,
    1,
    5,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F31453
    1453,
    16,
    6,
    0x5D3F0,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F01454
    1454,
    16,
    22,
    0x5D3F2,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F01455
    1455,
    16,
    6,
    0x5D3F4,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01456
    1456,
    1,
    22,
    0x5D3F6,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11457
    1457,
    1,
    23,
    0x5D3F6,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21458
    1458,
    1,
    24,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F31459
    1459,
    1,
    25,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV0_F41460
    1460,
    1,
    26,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV1_F01461
    1461,
    1,
    27,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_FUNC_EN_DEV2_F01462
    1462,
    1,
    28,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_HWREV_LSB21463
    1463,
    2,
    2,
    0x5D3EC,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F01464
    1464,
    1,
    6,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F01465
    1465,
    1,
    7,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F01466
    1466,
    1,
    8,
    0x5D3F9,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F01467
    1467,
    1,
    9,
    0x5D3F9,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_SWREV_LSB21468
    1468,
    2,
    4,
    0x5D3EC,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01469
    1469,
    1,
    29,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11470
    1470,
    1,
    30,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21471
    1471,
    1,
    31,
    0x5D3F7,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F31472
    1472,
    1,
    0,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F41473
    1473,
    1,
    1,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F01474
    1474,
    1,
    2,
    0x5D3F8,
  },
#endif

#ifdef NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0
#define
  {
    ///< NBIF4_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F01475
    1475,
    1,
    3,
    0x5D3F8,
  },
#endif

#ifdef NBIF5_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< NBIF5_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES1476
    1476,
    22,
    10,
    0x5D409,
  },
#endif

#ifdef NBIF5_NBIF_SSP_GENERIC_B_WRITE_DISABLE
#define
  {
    ///< NBIF5_NBIF_SSP_GENERIC_B_WRITE_DISABLE1477
    1477,
    1,
    1,
    0x5D3FC,
  },
#endif

#ifdef NBIF5_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF5_STRAP_BIF_FUSESTRAP_VALID1478
    1478,
    1,
    0,
    0x5D3FC,
  },
#endif

#ifdef NBIF5_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF5_STRAP_BIF_RESERVED_BIF_STRAP31479
    1479,
    32,
    6,
    0x5D3FC,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F31480
    1480,
    1,
    4,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F41481
    1481,
    1,
    5,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F31482
    1482,
    16,
    6,
    0x5D400,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F01483
    1483,
    16,
    22,
    0x5D402,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F01484
    1484,
    16,
    6,
    0x5D404,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01485
    1485,
    1,
    22,
    0x5D406,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11486
    1486,
    1,
    23,
    0x5D406,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21487
    1487,
    1,
    24,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F31488
    1488,
    1,
    25,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV0_F41489
    1489,
    1,
    26,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV1_F01490
    1490,
    1,
    27,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_FUNC_EN_DEV2_F01491
    1491,
    1,
    28,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_HWREV_LSB21492
    1492,
    2,
    2,
    0x5D3FC,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F01493
    1493,
    1,
    6,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F01494
    1494,
    1,
    7,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F01495
    1495,
    1,
    8,
    0x5D409,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F01496
    1496,
    1,
    9,
    0x5D409,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_SWREV_LSB21497
    1497,
    2,
    4,
    0x5D3FC,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01498
    1498,
    1,
    29,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11499
    1499,
    1,
    30,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21500
    1500,
    1,
    31,
    0x5D407,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F31501
    1501,
    1,
    0,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F41502
    1502,
    1,
    1,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F01503
    1503,
    1,
    2,
    0x5D408,
  },
#endif

#ifdef NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0
#define
  {
    ///< NBIF5_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F01504
    1504,
    1,
    3,
    0x5D408,
  },
#endif

#ifdef NBIF6_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< NBIF6_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES1505
    1505,
    22,
    10,
    0x5D419,
  },
#endif

#ifdef NBIF6_NBIF_SSP_GENERIC_B_WRITE_DISABLE
#define
  {
    ///< NBIF6_NBIF_SSP_GENERIC_B_WRITE_DISABLE1506
    1506,
    1,
    1,
    0x5D40C,
  },
#endif

#ifdef NBIF6_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF6_STRAP_BIF_FUSESTRAP_VALID1507
    1507,
    1,
    0,
    0x5D40C,
  },
#endif

#ifdef NBIF6_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF6_STRAP_BIF_RESERVED_BIF_STRAP31508
    1508,
    32,
    6,
    0x5D40C,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F31509
    1509,
    1,
    4,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F41510
    1510,
    1,
    5,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F31511
    1511,
    16,
    6,
    0x5D410,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F01512
    1512,
    16,
    22,
    0x5D412,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F01513
    1513,
    16,
    6,
    0x5D414,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01514
    1514,
    1,
    22,
    0x5D416,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11515
    1515,
    1,
    23,
    0x5D416,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21516
    1516,
    1,
    24,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F31517
    1517,
    1,
    25,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV0_F41518
    1518,
    1,
    26,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV1_F01519
    1519,
    1,
    27,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_FUNC_EN_DEV2_F01520
    1520,
    1,
    28,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_HWREV_LSB21521
    1521,
    2,
    2,
    0x5D40C,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F01522
    1522,
    1,
    6,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F01523
    1523,
    1,
    7,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F01524
    1524,
    1,
    8,
    0x5D419,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F01525
    1525,
    1,
    9,
    0x5D419,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_SWREV_LSB21526
    1526,
    2,
    4,
    0x5D40C,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01527
    1527,
    1,
    29,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11528
    1528,
    1,
    30,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21529
    1529,
    1,
    31,
    0x5D417,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F31530
    1530,
    1,
    0,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F41531
    1531,
    1,
    1,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F01532
    1532,
    1,
    2,
    0x5D418,
  },
#endif

#ifdef NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0
#define
  {
    ///< NBIF6_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F01533
    1533,
    1,
    3,
    0x5D418,
  },
#endif

#ifdef NBIF7_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< NBIF7_NBIF_SSP_GENERIC_B_PUB_SPARE_FUSES1534
    1534,
    22,
    10,
    0x5D429,
  },
#endif

#ifdef NBIF7_NBIF_SSP_GENERIC_B_WRITE_DISABLE
#define
  {
    ///< NBIF7_NBIF_SSP_GENERIC_B_WRITE_DISABLE1535
    1535,
    1,
    1,
    0x5D41C,
  },
#endif

#ifdef NBIF7_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF7_STRAP_BIF_FUSESTRAP_VALID1536
    1536,
    1,
    0,
    0x5D41C,
  },
#endif

#ifdef NBIF7_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF7_STRAP_BIF_RESERVED_BIF_STRAP31537
    1537,
    32,
    6,
    0x5D41C,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F3
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F31538
    1538,
    1,
    4,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F4
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_AUXPWR_SUPPORT_DEV0_F41539
    1539,
    1,
    5,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F3
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV0_F31540
    1540,
    16,
    6,
    0x5D420,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV1_F01541
    1541,
    16,
    22,
    0x5D422,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_DEVICE_ID_DEV2_F01542
    1542,
    16,
    6,
    0x5D424,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01543
    1543,
    1,
    22,
    0x5D426,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11544
    1544,
    1,
    23,
    0x5D426,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21545
    1545,
    1,
    24,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F3
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F31546
    1546,
    1,
    25,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F4
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV0_F41547
    1547,
    1,
    26,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV1_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV1_F01548
    1548,
    1,
    27,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV2_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_FUNC_EN_DEV2_F01549
    1549,
    1,
    28,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_HWREV_LSB21550
    1550,
    2,
    2,
    0x5D41C,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV1_F01551
    1551,
    1,
    6,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_0_DEV2_F01552
    1552,
    1,
    7,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV1_F01553
    1553,
    1,
    8,
    0x5D429,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_SATA_DID_RAID_EN_1_DEV2_F01554
    1554,
    1,
    9,
    0x5D429,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_SWREV_LSB21555
    1555,
    2,
    4,
    0x5D41C,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01556
    1556,
    1,
    29,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11557
    1557,
    1,
    30,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21558
    1558,
    1,
    31,
    0x5D427,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F3
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F31559
    1559,
    1,
    0,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F4
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F41560
    1560,
    1,
    1,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV1_F01561
    1561,
    1,
    2,
    0x5D428,
  },
#endif

#ifdef NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F0
#define
  {
    ///< NBIF7_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV2_F01562
    1562,
    1,
    3,
    0x5D428,
  },
#endif

#ifdef NBIF8_NBIF8_GROUP0_DATA
#define
  {
    ///< NBIF8_NBIF8_GROUP0_DATA1563
    1563,
    128,
    0,
    0x5D808,
  },
#endif

#ifdef NBIF8_NBIF_SSP_NTB_PUB_SPARE_FUSES
#define
  {
    ///< NBIF8_NBIF_SSP_NTB_PUB_SPARE_FUSES1564
    1564,
    10,
    22,
    0x5D432,
  },
#endif

#ifdef NBIF8_NBIF_SSP_NTB_WRITE_DISABLE
#define
  {
    ///< NBIF8_NBIF_SSP_NTB_WRITE_DISABLE1565
    1565,
    1,
    1,
    0x5D42C,
  },
#endif

#ifdef NBIF8_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF8_STRAP_BIF_FUSESTRAP_VALID1566
    1566,
    1,
    0,
    0x5D42C,
  },
#endif

#ifdef NBIF8_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF8_STRAP_BIF_RESERVED_BIF_STRAP21567
    1567,
    2,
    6,
    0x5D42C,
  },
#endif

#ifdef NBIF8_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF8_STRAP_BIF_RESERVED_BIF_STRAP31568
    1568,
    32,
    8,
    0x5D42D,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_DN_DEVNUM_DEV0
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_DN_DEVNUM_DEV01569
    1569,
    5,
    8,
    0x5D431,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_DN_FUNCID_DEV0
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_DN_FUNCID_DEV01570
    1570,
    3,
    13,
    0x5D431,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01571
    1571,
    1,
    16,
    0x5D432,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11572
    1572,
    1,
    17,
    0x5D432,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21573
    1573,
    1,
    18,
    0x5D432,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_HWREV_LSB21574
    1574,
    2,
    2,
    0x5D42C,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_SWREV_LSB21575
    1575,
    2,
    4,
    0x5D42C,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01576
    1576,
    1,
    19,
    0x5D432,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11577
    1577,
    1,
    20,
    0x5D432,
  },
#endif

#ifdef NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF8_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21578
    1578,
    1,
    21,
    0x5D432,
  },
#endif

#ifdef NBIF9_NBIF9_GROUP0_DATA
#define
  {
    ///< NBIF9_NBIF9_GROUP0_DATA1579
    1579,
    128,
    0,
    0x5D818,
  },
#endif

#ifdef NBIF9_NBIF_SSP_NTB_PUB_SPARE_FUSES
#define
  {
    ///< NBIF9_NBIF_SSP_NTB_PUB_SPARE_FUSES1580
    1580,
    10,
    22,
    0x5D43A,
  },
#endif

#ifdef NBIF9_NBIF_SSP_NTB_WRITE_DISABLE
#define
  {
    ///< NBIF9_NBIF_SSP_NTB_WRITE_DISABLE1581
    1581,
    1,
    1,
    0x5D434,
  },
#endif

#ifdef NBIF9_STRAP_BIF_FUSESTRAP_VALID
#define
  {
    ///< NBIF9_STRAP_BIF_FUSESTRAP_VALID1582
    1582,
    1,
    0,
    0x5D434,
  },
#endif

#ifdef NBIF9_STRAP_BIF_RESERVED_BIF_STRAP2
#define
  {
    ///< NBIF9_STRAP_BIF_RESERVED_BIF_STRAP21583
    1583,
    2,
    6,
    0x5D434,
  },
#endif

#ifdef NBIF9_STRAP_BIF_RESERVED_BIF_STRAP3
#define
  {
    ///< NBIF9_STRAP_BIF_RESERVED_BIF_STRAP31584
    1584,
    32,
    8,
    0x5D435,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_DN_DEVNUM_DEV0
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_DN_DEVNUM_DEV01585
    1585,
    5,
    8,
    0x5D439,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_DN_FUNCID_DEV0
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_DN_FUNCID_DEV01586
    1586,
    3,
    13,
    0x5D439,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F0
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F01587
    1587,
    1,
    16,
    0x5D43A,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F1
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F11588
    1588,
    1,
    17,
    0x5D43A,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F2
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_FUNC_EN_DEV0_F21589
    1589,
    1,
    18,
    0x5D43A,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_HWREV_LSB2
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_HWREV_LSB21590
    1590,
    2,
    2,
    0x5D434,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_SWREV_LSB2
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_SWREV_LSB21591
    1591,
    2,
    4,
    0x5D434,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F0
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F01592
    1592,
    1,
    19,
    0x5D43A,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F1
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F11593
    1593,
    1,
    20,
    0x5D43A,
  },
#endif

#ifdef NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F2
#define
  {
    ///< NBIF9_STRAP_BIF_STRAP_VENDOR_ID_BIT_DEV0_F21594
    1594,
    1,
    21,
    0x5D43A,
  },
#endif

#ifdef NTB_NTB_PUB_SPARE_FUSES
#define
  {
    ///< NTB_NTB_PUB_SPARE_FUSES1595
    1595,
    16,
    16,
    0x5D452,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_AMS
#define
  {
    ///< NTB_NVME_STRAP_CAP_AMS1596
    1596,
    2,
    29,
    0x5D44F,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_CQR
#define
  {
    ///< NTB_NVME_STRAP_CAP_CQR1597
    1597,
    1,
    31,
    0x5D44F,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_CSS
#define
  {
    ///< NTB_NVME_STRAP_CAP_CSS1598
    1598,
    8,
    8,
    0x5D44D,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_DSTRD
#define
  {
    ///< NTB_NVME_STRAP_CAP_DSTRD1599
    1599,
    4,
    17,
    0x5D44E,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_MPSMAX
#define
  {
    ///< NTB_NVME_STRAP_CAP_MPSMAX1600
    1600,
    4,
    0,
    0x5D44C,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_MPSMIN
#define
  {
    ///< NTB_NVME_STRAP_CAP_MPSMIN1601
    1601,
    4,
    4,
    0x5D44C,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_MQES
#define
  {
    ///< NTB_NVME_STRAP_CAP_MQES1602
    1602,
    16,
    0,
    0x5D450,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_NSSRS
#define
  {
    ///< NTB_NVME_STRAP_CAP_NSSRS1603
    1603,
    1,
    16,
    0x5D44E,
  },
#endif

#ifdef NTB_NVME_STRAP_CAP_TO
#define
  {
    ///< NTB_NVME_STRAP_CAP_TO1604
    1604,
    8,
    21,
    0x5D44E,
  },
#endif

#ifdef OPN_ConfigId
#define
  {
    ///< OPN_ConfigId1605
    1605,
    16,
    26,
    0x5D47F,
  },
#endif

#ifdef OPN_CpuID_ExtModel
#define
  {
    ///< OPN_CpuID_ExtModel1606
    1606,
    4,
    13,
    0x5D47D,
  },
#endif

#ifdef OPN_CpuID_Model
#define
  {
    ///< OPN_CpuID_Model1607
    1607,
    4,
    9,
    0x5D47D,
  },
#endif

#ifdef OPN_CpuID_Stepping
#define
  {
    ///< OPN_CpuID_Stepping1608
    1608,
    4,
    17,
    0x5D47E,
  },
#endif

#ifdef OPN_IntRev
#define
  {
    ///< OPN_IntRev1609
    1609,
    6,
    10,
    0x5D481,
  },
#endif

#ifdef OPN_MSID
#define
  {
    ///< OPN_MSID1610
    1610,
    24,
    0,
    0x5D484,
  },
#endif

#ifdef OPN_NameString_0
#define
  {
    ///< OPN_NameString_01611
    1611,
    7,
    0,
    0x5D454,
  },
#endif

#ifdef OPN_NameString_1
#define
  {
    ///< OPN_NameString_11612
    1612,
    7,
    7,
    0x5D454,
  },
#endif

#ifdef OPN_NameString_10
#define
  {
    ///< OPN_NameString_101613
    1613,
    7,
    6,
    0x5D45C,
  },
#endif

#ifdef OPN_NameString_11
#define
  {
    ///< OPN_NameString_111614
    1614,
    7,
    13,
    0x5D45D,
  },
#endif

#ifdef OPN_NameString_12
#define
  {
    ///< OPN_NameString_121615
    1615,
    7,
    20,
    0x5D45E,
  },
#endif

#ifdef OPN_NameString_13
#define
  {
    ///< OPN_NameString_131616
    1616,
    7,
    27,
    0x5D45F,
  },
#endif

#ifdef OPN_NameString_14
#define
  {
    ///< OPN_NameString_141617
    1617,
    7,
    2,
    0x5D460,
  },
#endif

#ifdef OPN_NameString_15
#define
  {
    ///< OPN_NameString_151618
    1618,
    7,
    9,
    0x5D461,
  },
#endif

#ifdef OPN_NameString_16
#define
  {
    ///< OPN_NameString_161619
    1619,
    7,
    16,
    0x5D462,
  },
#endif

#ifdef OPN_NameString_17
#define
  {
    ///< OPN_NameString_171620
    1620,
    7,
    23,
    0x5D462,
  },
#endif

#ifdef OPN_NameString_18
#define
  {
    ///< OPN_NameString_181621
    1621,
    7,
    30,
    0x5D463,
  },
#endif

#ifdef OPN_NameString_19
#define
  {
    ///< OPN_NameString_191622
    1622,
    7,
    5,
    0x5D464,
  },
#endif

#ifdef OPN_NameString_2
#define
  {
    ///< OPN_NameString_21623
    1623,
    7,
    14,
    0x5D455,
  },
#endif

#ifdef OPN_NameString_20
#define
  {
    ///< OPN_NameString_201624
    1624,
    7,
    12,
    0x5D465,
  },
#endif

#ifdef OPN_NameString_21
#define
  {
    ///< OPN_NameString_211625
    1625,
    7,
    19,
    0x5D466,
  },
#endif

#ifdef OPN_NameString_22
#define
  {
    ///< OPN_NameString_221626
    1626,
    7,
    26,
    0x5D467,
  },
#endif

#ifdef OPN_NameString_23
#define
  {
    ///< OPN_NameString_231627
    1627,
    7,
    1,
    0x5D468,
  },
#endif

#ifdef OPN_NameString_24
#define
  {
    ///< OPN_NameString_241628
    1628,
    7,
    8,
    0x5D469,
  },
#endif

#ifdef OPN_NameString_25
#define
  {
    ///< OPN_NameString_251629
    1629,
    7,
    15,
    0x5D469,
  },
#endif

#ifdef OPN_NameString_26
#define
  {
    ///< OPN_NameString_261630
    1630,
    7,
    22,
    0x5D46A,
  },
#endif

#ifdef OPN_NameString_27
#define
  {
    ///< OPN_NameString_271631
    1631,
    7,
    29,
    0x5D46B,
  },
#endif

#ifdef OPN_NameString_28
#define
  {
    ///< OPN_NameString_281632
    1632,
    7,
    4,
    0x5D46C,
  },
#endif

#ifdef OPN_NameString_29
#define
  {
    ///< OPN_NameString_291633
    1633,
    7,
    11,
    0x5D46D,
  },
#endif

#ifdef OPN_NameString_3
#define
  {
    ///< OPN_NameString_31634
    1634,
    7,
    21,
    0x5D456,
  },
#endif

#ifdef OPN_NameString_30
#define
  {
    ///< OPN_NameString_301635
    1635,
    7,
    18,
    0x5D46E,
  },
#endif

#ifdef OPN_NameString_31
#define
  {
    ///< OPN_NameString_311636
    1636,
    7,
    25,
    0x5D46F,
  },
#endif

#ifdef OPN_NameString_32
#define
  {
    ///< OPN_NameString_321637
    1637,
    7,
    0,
    0x5D470,
  },
#endif

#ifdef OPN_NameString_33
#define
  {
    ///< OPN_NameString_331638
    1638,
    7,
    7,
    0x5D470,
  },
#endif

#ifdef OPN_NameString_34
#define
  {
    ///< OPN_NameString_341639
    1639,
    7,
    14,
    0x5D471,
  },
#endif

#ifdef OPN_NameString_35
#define
  {
    ///< OPN_NameString_351640
    1640,
    7,
    21,
    0x5D472,
  },
#endif

#ifdef OPN_NameString_36
#define
  {
    ///< OPN_NameString_361641
    1641,
    7,
    28,
    0x5D473,
  },
#endif

#ifdef OPN_NameString_37
#define
  {
    ///< OPN_NameString_371642
    1642,
    7,
    3,
    0x5D474,
  },
#endif

#ifdef OPN_NameString_38
#define
  {
    ///< OPN_NameString_381643
    1643,
    7,
    10,
    0x5D475,
  },
#endif

#ifdef OPN_NameString_39
#define
  {
    ///< OPN_NameString_391644
    1644,
    7,
    17,
    0x5D476,
  },
#endif

#ifdef OPN_NameString_4
#define
  {
    ///< OPN_NameString_41645
    1645,
    7,
    28,
    0x5D457,
  },
#endif

#ifdef OPN_NameString_40
#define
  {
    ///< OPN_NameString_401646
    1646,
    7,
    24,
    0x5D477,
  },
#endif

#ifdef OPN_NameString_41
#define
  {
    ///< OPN_NameString_411647
    1647,
    7,
    31,
    0x5D477,
  },
#endif

#ifdef OPN_NameString_42
#define
  {
    ///< OPN_NameString_421648
    1648,
    7,
    6,
    0x5D478,
  },
#endif

#ifdef OPN_NameString_43
#define
  {
    ///< OPN_NameString_431649
    1649,
    7,
    13,
    0x5D479,
  },
#endif

#ifdef OPN_NameString_44
#define
  {
    ///< OPN_NameString_441650
    1650,
    7,
    20,
    0x5D47A,
  },
#endif

#ifdef OPN_NameString_45
#define
  {
    ///< OPN_NameString_451651
    1651,
    7,
    27,
    0x5D47B,
  },
#endif

#ifdef OPN_NameString_46
#define
  {
    ///< OPN_NameString_461652
    1652,
    7,
    2,
    0x5D47C,
  },
#endif

#ifdef OPN_NameString_5
#define
  {
    ///< OPN_NameString_51653
    1653,
    7,
    3,
    0x5D458,
  },
#endif

#ifdef OPN_NameString_6
#define
  {
    ///< OPN_NameString_61654
    1654,
    7,
    10,
    0x5D459,
  },
#endif

#ifdef OPN_NameString_7
#define
  {
    ///< OPN_NameString_71655
    1655,
    7,
    17,
    0x5D45A,
  },
#endif

#ifdef OPN_NameString_8
#define
  {
    ///< OPN_NameString_81656
    1656,
    7,
    24,
    0x5D45B,
  },
#endif

#ifdef OPN_NameString_9
#define
  {
    ///< OPN_NameString_91657
    1657,
    7,
    31,
    0x5D45B,
  },
#endif

#ifdef OPN_OPN_SPARE
#define
  {
    ///< OPN_OPN_SPARE1658
    1658,
    8,
    24,
    0x5D487,
  },
#endif

#ifdef OPN_PkgID
#define
  {
    ///< OPN_PkgID1659
    1659,
    5,
    21,
    0x5D47E,
  },
#endif

#ifdef OPN_Utility
#define
  {
    ///< OPN_Utility1660
    1660,
    16,
    16,
    0x5D482,
  },
#endif

#ifdef PCIE0_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE0_PCIE0_PUB_SPARE_FUSES1661
    1661,
    1,
    31,
    0x5D497,
  },
#endif

#ifdef PCIE0_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE0_PCIE0_WRITE_DISABLE1662
    1662,
    1,
    0,
    0x5D488,
  },
#endif

#ifdef PCIE0_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE0_PCIE_EFUSE2_RESERVED_11663
    1663,
    1,
    31,
    0x5D48B,
  },
#endif

#ifdef PCIE0_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE0_PCIE_EFUSE2_RESERVED_21664
    1664,
    4,
    11,
    0x5D48D,
  },
#endif

#ifdef PCIE0_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE0_PCIE_EFUSE3_RESERVED_11665
    1665,
    18,
    31,
    0x5D48F,
  },
#endif

#ifdef PCIE0_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE0_PCIE_EFUSE3_RESERVED_21666
    1666,
    13,
    18,
    0x5D492,
  },
#endif

#ifdef PCIE0_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE0_PCIE_EFUSE4_RESERVED1667
    1667,
    32,
    31,
    0x5D493,
  },
#endif

#ifdef PCIE0_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE0_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1668
    1668,
    1,
    1,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE0_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1669
    1669,
    1,
    17,
    0x5D492,
  },
#endif

#ifdef PCIE0_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE0_STRAP_BIF_DEVICE_ID_w1670
    1670,
    16,
    15,
    0x5D48D,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_A1671
    1671,
    1,
    15,
    0x5D489,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_B1672
    1672,
    1,
    17,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_C1673
    1673,
    1,
    19,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_D1674
    1674,
    1,
    21,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_E1675
    1675,
    1,
    23,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_F1676
    1676,
    1,
    25,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_G1677
    1677,
    1,
    27,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE0_STRAP_BIF_GEN2_EN_w_H1678
    1678,
    1,
    29,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_A1679
    1679,
    1,
    16,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_B1680
    1680,
    1,
    18,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_C1681
    1681,
    1,
    20,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_D1682
    1682,
    1,
    22,
    0x5D48A,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_E1683
    1683,
    1,
    24,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_F1684
    1684,
    1,
    26,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_G1685
    1685,
    1,
    28,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE0_STRAP_BIF_GEN3_EN_w_H1686
    1686,
    1,
    30,
    0x5D48B,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_A1687
    1687,
    1,
    3,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_B1688
    1688,
    1,
    4,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_C1689
    1689,
    1,
    5,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_D1690
    1690,
    1,
    6,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_E1691
    1691,
    1,
    7,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_F1692
    1692,
    1,
    8,
    0x5D48D,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_G1693
    1693,
    1,
    9,
    0x5D48D,
  },
#endif

#ifdef PCIE0_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE0_STRAP_BIF_GEN4_EN_w_H1694
    1694,
    1,
    10,
    0x5D48D,
  },
#endif

#ifdef PCIE0_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE0_STRAP_BIF_LANE_NEGOTIATION1695
    1695,
    3,
    9,
    0x5D489,
  },
#endif

#ifdef PCIE0_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE0_STRAP_BIF_LC_PMI_TO_L1_DIS1696
    1696,
    1,
    0,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE0_STRAP_BIF_LC_TX_SWING_OVERRIDE1697
    1697,
    1,
    1,
    0x5D488,
  },
#endif

#ifdef PCIE0_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE0_STRAP_BIF_LONG_yTSx_COUNT1698
    1698,
    2,
    3,
    0x5D488,
  },
#endif

#ifdef PCIE0_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE0_STRAP_BIF_MED_yTSx_COUNT1699
    1699,
    2,
    5,
    0x5D488,
  },
#endif

#ifdef PCIE0_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE0_STRAP_BIF_PHYSTATUS_SELECT1700
    1700,
    1,
    2,
    0x5D48C,
  },
#endif

#ifdef PCIE0_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE0_STRAP_BIF_SHORT_yTSx_COUNT1701
    1701,
    2,
    7,
    0x5D488,
  },
#endif

#ifdef PCIE0_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE0_STRAP_BIF_SKIP_INTERVAL1702
    1702,
    3,
    12,
    0x5D489,
  },
#endif

#ifdef PCIE0_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE0_STRAP_CHIP_BIF_MODE1703
    1703,
    1,
    2,
    0x5D488,
  },
#endif

#ifdef PCIE1_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE1_PCIE0_PUB_SPARE_FUSES1704
    1704,
    1,
    31,
    0x5D4A7,
  },
#endif

#ifdef PCIE1_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE1_PCIE0_WRITE_DISABLE1705
    1705,
    1,
    0,
    0x5D498,
  },
#endif

#ifdef PCIE1_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE1_PCIE_EFUSE2_RESERVED_11706
    1706,
    1,
    31,
    0x5D49B,
  },
#endif

#ifdef PCIE1_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE1_PCIE_EFUSE2_RESERVED_21707
    1707,
    4,
    11,
    0x5D49D,
  },
#endif

#ifdef PCIE1_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE1_PCIE_EFUSE3_RESERVED_11708
    1708,
    18,
    31,
    0x5D49F,
  },
#endif

#ifdef PCIE1_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE1_PCIE_EFUSE3_RESERVED_21709
    1709,
    13,
    18,
    0x5D4A2,
  },
#endif

#ifdef PCIE1_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE1_PCIE_EFUSE4_RESERVED1710
    1710,
    32,
    31,
    0x5D4A3,
  },
#endif

#ifdef PCIE1_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE1_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1711
    1711,
    1,
    1,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE1_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1712
    1712,
    1,
    17,
    0x5D4A2,
  },
#endif

#ifdef PCIE1_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE1_STRAP_BIF_DEVICE_ID_w1713
    1713,
    16,
    15,
    0x5D49D,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_A1714
    1714,
    1,
    15,
    0x5D499,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_B1715
    1715,
    1,
    17,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_C1716
    1716,
    1,
    19,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_D1717
    1717,
    1,
    21,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_E1718
    1718,
    1,
    23,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_F1719
    1719,
    1,
    25,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_G1720
    1720,
    1,
    27,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE1_STRAP_BIF_GEN2_EN_w_H1721
    1721,
    1,
    29,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_A1722
    1722,
    1,
    16,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_B1723
    1723,
    1,
    18,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_C1724
    1724,
    1,
    20,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_D1725
    1725,
    1,
    22,
    0x5D49A,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_E1726
    1726,
    1,
    24,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_F1727
    1727,
    1,
    26,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_G1728
    1728,
    1,
    28,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE1_STRAP_BIF_GEN3_EN_w_H1729
    1729,
    1,
    30,
    0x5D49B,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_A1730
    1730,
    1,
    3,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_B1731
    1731,
    1,
    4,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_C1732
    1732,
    1,
    5,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_D1733
    1733,
    1,
    6,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_E1734
    1734,
    1,
    7,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_F1735
    1735,
    1,
    8,
    0x5D49D,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_G1736
    1736,
    1,
    9,
    0x5D49D,
  },
#endif

#ifdef PCIE1_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE1_STRAP_BIF_GEN4_EN_w_H1737
    1737,
    1,
    10,
    0x5D49D,
  },
#endif

#ifdef PCIE1_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE1_STRAP_BIF_LANE_NEGOTIATION1738
    1738,
    3,
    9,
    0x5D499,
  },
#endif

#ifdef PCIE1_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE1_STRAP_BIF_LC_PMI_TO_L1_DIS1739
    1739,
    1,
    0,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE1_STRAP_BIF_LC_TX_SWING_OVERRIDE1740
    1740,
    1,
    1,
    0x5D498,
  },
#endif

#ifdef PCIE1_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE1_STRAP_BIF_LONG_yTSx_COUNT1741
    1741,
    2,
    3,
    0x5D498,
  },
#endif

#ifdef PCIE1_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE1_STRAP_BIF_MED_yTSx_COUNT1742
    1742,
    2,
    5,
    0x5D498,
  },
#endif

#ifdef PCIE1_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE1_STRAP_BIF_PHYSTATUS_SELECT1743
    1743,
    1,
    2,
    0x5D49C,
  },
#endif

#ifdef PCIE1_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE1_STRAP_BIF_SHORT_yTSx_COUNT1744
    1744,
    2,
    7,
    0x5D498,
  },
#endif

#ifdef PCIE1_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE1_STRAP_BIF_SKIP_INTERVAL1745
    1745,
    3,
    12,
    0x5D499,
  },
#endif

#ifdef PCIE1_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE1_STRAP_CHIP_BIF_MODE1746
    1746,
    1,
    2,
    0x5D498,
  },
#endif

#ifdef PCIE2_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE2_PCIE0_PUB_SPARE_FUSES1747
    1747,
    1,
    31,
    0x5D4B7,
  },
#endif

#ifdef PCIE2_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE2_PCIE0_WRITE_DISABLE1748
    1748,
    1,
    0,
    0x5D4A8,
  },
#endif

#ifdef PCIE2_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE2_PCIE_EFUSE2_RESERVED_11749
    1749,
    1,
    31,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE2_PCIE_EFUSE2_RESERVED_21750
    1750,
    4,
    11,
    0x5D4AD,
  },
#endif

#ifdef PCIE2_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE2_PCIE_EFUSE3_RESERVED_11751
    1751,
    18,
    31,
    0x5D4AF,
  },
#endif

#ifdef PCIE2_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE2_PCIE_EFUSE3_RESERVED_21752
    1752,
    13,
    18,
    0x5D4B2,
  },
#endif

#ifdef PCIE2_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE2_PCIE_EFUSE4_RESERVED1753
    1753,
    32,
    31,
    0x5D4B3,
  },
#endif

#ifdef PCIE2_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE2_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1754
    1754,
    1,
    1,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE2_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1755
    1755,
    1,
    17,
    0x5D4B2,
  },
#endif

#ifdef PCIE2_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE2_STRAP_BIF_DEVICE_ID_w1756
    1756,
    16,
    15,
    0x5D4AD,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_A1757
    1757,
    1,
    15,
    0x5D4A9,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_B1758
    1758,
    1,
    17,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_C1759
    1759,
    1,
    19,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_D1760
    1760,
    1,
    21,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_E1761
    1761,
    1,
    23,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_F1762
    1762,
    1,
    25,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_G1763
    1763,
    1,
    27,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE2_STRAP_BIF_GEN2_EN_w_H1764
    1764,
    1,
    29,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_A1765
    1765,
    1,
    16,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_B1766
    1766,
    1,
    18,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_C1767
    1767,
    1,
    20,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_D1768
    1768,
    1,
    22,
    0x5D4AA,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_E1769
    1769,
    1,
    24,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_F1770
    1770,
    1,
    26,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_G1771
    1771,
    1,
    28,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE2_STRAP_BIF_GEN3_EN_w_H1772
    1772,
    1,
    30,
    0x5D4AB,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_A1773
    1773,
    1,
    3,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_B1774
    1774,
    1,
    4,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_C1775
    1775,
    1,
    5,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_D1776
    1776,
    1,
    6,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_E1777
    1777,
    1,
    7,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_F1778
    1778,
    1,
    8,
    0x5D4AD,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_G1779
    1779,
    1,
    9,
    0x5D4AD,
  },
#endif

#ifdef PCIE2_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE2_STRAP_BIF_GEN4_EN_w_H1780
    1780,
    1,
    10,
    0x5D4AD,
  },
#endif

#ifdef PCIE2_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE2_STRAP_BIF_LANE_NEGOTIATION1781
    1781,
    3,
    9,
    0x5D4A9,
  },
#endif

#ifdef PCIE2_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE2_STRAP_BIF_LC_PMI_TO_L1_DIS1782
    1782,
    1,
    0,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE2_STRAP_BIF_LC_TX_SWING_OVERRIDE1783
    1783,
    1,
    1,
    0x5D4A8,
  },
#endif

#ifdef PCIE2_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE2_STRAP_BIF_LONG_yTSx_COUNT1784
    1784,
    2,
    3,
    0x5D4A8,
  },
#endif

#ifdef PCIE2_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE2_STRAP_BIF_MED_yTSx_COUNT1785
    1785,
    2,
    5,
    0x5D4A8,
  },
#endif

#ifdef PCIE2_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE2_STRAP_BIF_PHYSTATUS_SELECT1786
    1786,
    1,
    2,
    0x5D4AC,
  },
#endif

#ifdef PCIE2_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE2_STRAP_BIF_SHORT_yTSx_COUNT1787
    1787,
    2,
    7,
    0x5D4A8,
  },
#endif

#ifdef PCIE2_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE2_STRAP_BIF_SKIP_INTERVAL1788
    1788,
    3,
    12,
    0x5D4A9,
  },
#endif

#ifdef PCIE2_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE2_STRAP_CHIP_BIF_MODE1789
    1789,
    1,
    2,
    0x5D4A8,
  },
#endif

#ifdef PCIE3_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE3_PCIE0_PUB_SPARE_FUSES1790
    1790,
    1,
    31,
    0x5D4C7,
  },
#endif

#ifdef PCIE3_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE3_PCIE0_WRITE_DISABLE1791
    1791,
    1,
    0,
    0x5D4B8,
  },
#endif

#ifdef PCIE3_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE3_PCIE_EFUSE2_RESERVED_11792
    1792,
    1,
    31,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE3_PCIE_EFUSE2_RESERVED_21793
    1793,
    4,
    11,
    0x5D4BD,
  },
#endif

#ifdef PCIE3_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE3_PCIE_EFUSE3_RESERVED_11794
    1794,
    18,
    31,
    0x5D4BF,
  },
#endif

#ifdef PCIE3_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE3_PCIE_EFUSE3_RESERVED_21795
    1795,
    13,
    18,
    0x5D4C2,
  },
#endif

#ifdef PCIE3_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE3_PCIE_EFUSE4_RESERVED1796
    1796,
    32,
    31,
    0x5D4C3,
  },
#endif

#ifdef PCIE3_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE3_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1797
    1797,
    1,
    1,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE3_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1798
    1798,
    1,
    17,
    0x5D4C2,
  },
#endif

#ifdef PCIE3_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE3_STRAP_BIF_DEVICE_ID_w1799
    1799,
    16,
    15,
    0x5D4BD,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_A1800
    1800,
    1,
    15,
    0x5D4B9,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_B1801
    1801,
    1,
    17,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_C1802
    1802,
    1,
    19,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_D1803
    1803,
    1,
    21,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_E1804
    1804,
    1,
    23,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_F1805
    1805,
    1,
    25,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_G1806
    1806,
    1,
    27,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE3_STRAP_BIF_GEN2_EN_w_H1807
    1807,
    1,
    29,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_A1808
    1808,
    1,
    16,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_B1809
    1809,
    1,
    18,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_C1810
    1810,
    1,
    20,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_D1811
    1811,
    1,
    22,
    0x5D4BA,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_E1812
    1812,
    1,
    24,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_F1813
    1813,
    1,
    26,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_G1814
    1814,
    1,
    28,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE3_STRAP_BIF_GEN3_EN_w_H1815
    1815,
    1,
    30,
    0x5D4BB,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_A1816
    1816,
    1,
    3,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_B1817
    1817,
    1,
    4,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_C1818
    1818,
    1,
    5,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_D1819
    1819,
    1,
    6,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_E1820
    1820,
    1,
    7,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_F1821
    1821,
    1,
    8,
    0x5D4BD,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_G1822
    1822,
    1,
    9,
    0x5D4BD,
  },
#endif

#ifdef PCIE3_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE3_STRAP_BIF_GEN4_EN_w_H1823
    1823,
    1,
    10,
    0x5D4BD,
  },
#endif

#ifdef PCIE3_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE3_STRAP_BIF_LANE_NEGOTIATION1824
    1824,
    3,
    9,
    0x5D4B9,
  },
#endif

#ifdef PCIE3_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE3_STRAP_BIF_LC_PMI_TO_L1_DIS1825
    1825,
    1,
    0,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE3_STRAP_BIF_LC_TX_SWING_OVERRIDE1826
    1826,
    1,
    1,
    0x5D4B8,
  },
#endif

#ifdef PCIE3_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE3_STRAP_BIF_LONG_yTSx_COUNT1827
    1827,
    2,
    3,
    0x5D4B8,
  },
#endif

#ifdef PCIE3_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE3_STRAP_BIF_MED_yTSx_COUNT1828
    1828,
    2,
    5,
    0x5D4B8,
  },
#endif

#ifdef PCIE3_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE3_STRAP_BIF_PHYSTATUS_SELECT1829
    1829,
    1,
    2,
    0x5D4BC,
  },
#endif

#ifdef PCIE3_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE3_STRAP_BIF_SHORT_yTSx_COUNT1830
    1830,
    2,
    7,
    0x5D4B8,
  },
#endif

#ifdef PCIE3_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE3_STRAP_BIF_SKIP_INTERVAL1831
    1831,
    3,
    12,
    0x5D4B9,
  },
#endif

#ifdef PCIE3_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE3_STRAP_CHIP_BIF_MODE1832
    1832,
    1,
    2,
    0x5D4B8,
  },
#endif

#ifdef PCIE4_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE4_PCIE0_PUB_SPARE_FUSES1833
    1833,
    1,
    31,
    0x5D4D7,
  },
#endif

#ifdef PCIE4_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE4_PCIE0_WRITE_DISABLE1834
    1834,
    1,
    0,
    0x5D4C8,
  },
#endif

#ifdef PCIE4_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE4_PCIE_EFUSE2_RESERVED_11835
    1835,
    1,
    31,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE4_PCIE_EFUSE2_RESERVED_21836
    1836,
    4,
    11,
    0x5D4CD,
  },
#endif

#ifdef PCIE4_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE4_PCIE_EFUSE3_RESERVED_11837
    1837,
    18,
    31,
    0x5D4CF,
  },
#endif

#ifdef PCIE4_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE4_PCIE_EFUSE3_RESERVED_21838
    1838,
    13,
    18,
    0x5D4D2,
  },
#endif

#ifdef PCIE4_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE4_PCIE_EFUSE4_RESERVED1839
    1839,
    32,
    31,
    0x5D4D3,
  },
#endif

#ifdef PCIE4_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE4_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1840
    1840,
    1,
    1,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE4_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1841
    1841,
    1,
    17,
    0x5D4D2,
  },
#endif

#ifdef PCIE4_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE4_STRAP_BIF_DEVICE_ID_w1842
    1842,
    16,
    15,
    0x5D4CD,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_A1843
    1843,
    1,
    15,
    0x5D4C9,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_B1844
    1844,
    1,
    17,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_C1845
    1845,
    1,
    19,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_D1846
    1846,
    1,
    21,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_E1847
    1847,
    1,
    23,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_F1848
    1848,
    1,
    25,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_G1849
    1849,
    1,
    27,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE4_STRAP_BIF_GEN2_EN_w_H1850
    1850,
    1,
    29,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_A1851
    1851,
    1,
    16,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_B1852
    1852,
    1,
    18,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_C1853
    1853,
    1,
    20,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_D1854
    1854,
    1,
    22,
    0x5D4CA,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_E1855
    1855,
    1,
    24,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_F1856
    1856,
    1,
    26,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_G1857
    1857,
    1,
    28,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE4_STRAP_BIF_GEN3_EN_w_H1858
    1858,
    1,
    30,
    0x5D4CB,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_A1859
    1859,
    1,
    3,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_B1860
    1860,
    1,
    4,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_C1861
    1861,
    1,
    5,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_D1862
    1862,
    1,
    6,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_E1863
    1863,
    1,
    7,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_F1864
    1864,
    1,
    8,
    0x5D4CD,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_G1865
    1865,
    1,
    9,
    0x5D4CD,
  },
#endif

#ifdef PCIE4_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE4_STRAP_BIF_GEN4_EN_w_H1866
    1866,
    1,
    10,
    0x5D4CD,
  },
#endif

#ifdef PCIE4_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE4_STRAP_BIF_LANE_NEGOTIATION1867
    1867,
    3,
    9,
    0x5D4C9,
  },
#endif

#ifdef PCIE4_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE4_STRAP_BIF_LC_PMI_TO_L1_DIS1868
    1868,
    1,
    0,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE4_STRAP_BIF_LC_TX_SWING_OVERRIDE1869
    1869,
    1,
    1,
    0x5D4C8,
  },
#endif

#ifdef PCIE4_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE4_STRAP_BIF_LONG_yTSx_COUNT1870
    1870,
    2,
    3,
    0x5D4C8,
  },
#endif

#ifdef PCIE4_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE4_STRAP_BIF_MED_yTSx_COUNT1871
    1871,
    2,
    5,
    0x5D4C8,
  },
#endif

#ifdef PCIE4_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE4_STRAP_BIF_PHYSTATUS_SELECT1872
    1872,
    1,
    2,
    0x5D4CC,
  },
#endif

#ifdef PCIE4_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE4_STRAP_BIF_SHORT_yTSx_COUNT1873
    1873,
    2,
    7,
    0x5D4C8,
  },
#endif

#ifdef PCIE4_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE4_STRAP_BIF_SKIP_INTERVAL1874
    1874,
    3,
    12,
    0x5D4C9,
  },
#endif

#ifdef PCIE4_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE4_STRAP_CHIP_BIF_MODE1875
    1875,
    1,
    2,
    0x5D4C8,
  },
#endif

#ifdef PCIE5_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE5_PCIE0_PUB_SPARE_FUSES1876
    1876,
    1,
    31,
    0x5D4E7,
  },
#endif

#ifdef PCIE5_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE5_PCIE0_WRITE_DISABLE1877
    1877,
    1,
    0,
    0x5D4D8,
  },
#endif

#ifdef PCIE5_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE5_PCIE_EFUSE2_RESERVED_11878
    1878,
    1,
    31,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE5_PCIE_EFUSE2_RESERVED_21879
    1879,
    4,
    11,
    0x5D4DD,
  },
#endif

#ifdef PCIE5_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE5_PCIE_EFUSE3_RESERVED_11880
    1880,
    18,
    31,
    0x5D4DF,
  },
#endif

#ifdef PCIE5_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE5_PCIE_EFUSE3_RESERVED_21881
    1881,
    13,
    18,
    0x5D4E2,
  },
#endif

#ifdef PCIE5_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE5_PCIE_EFUSE4_RESERVED1882
    1882,
    32,
    31,
    0x5D4E3,
  },
#endif

#ifdef PCIE5_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE5_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1883
    1883,
    1,
    1,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE5_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1884
    1884,
    1,
    17,
    0x5D4E2,
  },
#endif

#ifdef PCIE5_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE5_STRAP_BIF_DEVICE_ID_w1885
    1885,
    16,
    15,
    0x5D4DD,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_A1886
    1886,
    1,
    15,
    0x5D4D9,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_B1887
    1887,
    1,
    17,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_C1888
    1888,
    1,
    19,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_D1889
    1889,
    1,
    21,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_E1890
    1890,
    1,
    23,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_F1891
    1891,
    1,
    25,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_G1892
    1892,
    1,
    27,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE5_STRAP_BIF_GEN2_EN_w_H1893
    1893,
    1,
    29,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_A1894
    1894,
    1,
    16,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_B1895
    1895,
    1,
    18,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_C1896
    1896,
    1,
    20,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_D1897
    1897,
    1,
    22,
    0x5D4DA,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_E1898
    1898,
    1,
    24,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_F1899
    1899,
    1,
    26,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_G1900
    1900,
    1,
    28,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE5_STRAP_BIF_GEN3_EN_w_H1901
    1901,
    1,
    30,
    0x5D4DB,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_A1902
    1902,
    1,
    3,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_B1903
    1903,
    1,
    4,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_C1904
    1904,
    1,
    5,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_D1905
    1905,
    1,
    6,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_E1906
    1906,
    1,
    7,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_F1907
    1907,
    1,
    8,
    0x5D4DD,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_G1908
    1908,
    1,
    9,
    0x5D4DD,
  },
#endif

#ifdef PCIE5_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE5_STRAP_BIF_GEN4_EN_w_H1909
    1909,
    1,
    10,
    0x5D4DD,
  },
#endif

#ifdef PCIE5_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE5_STRAP_BIF_LANE_NEGOTIATION1910
    1910,
    3,
    9,
    0x5D4D9,
  },
#endif

#ifdef PCIE5_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE5_STRAP_BIF_LC_PMI_TO_L1_DIS1911
    1911,
    1,
    0,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE5_STRAP_BIF_LC_TX_SWING_OVERRIDE1912
    1912,
    1,
    1,
    0x5D4D8,
  },
#endif

#ifdef PCIE5_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE5_STRAP_BIF_LONG_yTSx_COUNT1913
    1913,
    2,
    3,
    0x5D4D8,
  },
#endif

#ifdef PCIE5_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE5_STRAP_BIF_MED_yTSx_COUNT1914
    1914,
    2,
    5,
    0x5D4D8,
  },
#endif

#ifdef PCIE5_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE5_STRAP_BIF_PHYSTATUS_SELECT1915
    1915,
    1,
    2,
    0x5D4DC,
  },
#endif

#ifdef PCIE5_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE5_STRAP_BIF_SHORT_yTSx_COUNT1916
    1916,
    2,
    7,
    0x5D4D8,
  },
#endif

#ifdef PCIE5_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE5_STRAP_BIF_SKIP_INTERVAL1917
    1917,
    3,
    12,
    0x5D4D9,
  },
#endif

#ifdef PCIE5_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE5_STRAP_CHIP_BIF_MODE1918
    1918,
    1,
    2,
    0x5D4D8,
  },
#endif

#ifdef PCIE6_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE6_PCIE0_PUB_SPARE_FUSES1919
    1919,
    1,
    31,
    0x5D4F7,
  },
#endif

#ifdef PCIE6_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE6_PCIE0_WRITE_DISABLE1920
    1920,
    1,
    0,
    0x5D4E8,
  },
#endif

#ifdef PCIE6_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE6_PCIE_EFUSE2_RESERVED_11921
    1921,
    1,
    31,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE6_PCIE_EFUSE2_RESERVED_21922
    1922,
    4,
    11,
    0x5D4ED,
  },
#endif

#ifdef PCIE6_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE6_PCIE_EFUSE3_RESERVED_11923
    1923,
    18,
    31,
    0x5D4EF,
  },
#endif

#ifdef PCIE6_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE6_PCIE_EFUSE3_RESERVED_21924
    1924,
    13,
    18,
    0x5D4F2,
  },
#endif

#ifdef PCIE6_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE6_PCIE_EFUSE4_RESERVED1925
    1925,
    32,
    31,
    0x5D4F3,
  },
#endif

#ifdef PCIE6_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE6_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1926
    1926,
    1,
    1,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE6_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1927
    1927,
    1,
    17,
    0x5D4F2,
  },
#endif

#ifdef PCIE6_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE6_STRAP_BIF_DEVICE_ID_w1928
    1928,
    16,
    15,
    0x5D4ED,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_A1929
    1929,
    1,
    15,
    0x5D4E9,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_B1930
    1930,
    1,
    17,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_C1931
    1931,
    1,
    19,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_D1932
    1932,
    1,
    21,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_E1933
    1933,
    1,
    23,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_F1934
    1934,
    1,
    25,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_G1935
    1935,
    1,
    27,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE6_STRAP_BIF_GEN2_EN_w_H1936
    1936,
    1,
    29,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_A1937
    1937,
    1,
    16,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_B1938
    1938,
    1,
    18,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_C1939
    1939,
    1,
    20,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_D1940
    1940,
    1,
    22,
    0x5D4EA,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_E1941
    1941,
    1,
    24,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_F1942
    1942,
    1,
    26,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_G1943
    1943,
    1,
    28,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE6_STRAP_BIF_GEN3_EN_w_H1944
    1944,
    1,
    30,
    0x5D4EB,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_A1945
    1945,
    1,
    3,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_B1946
    1946,
    1,
    4,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_C1947
    1947,
    1,
    5,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_D1948
    1948,
    1,
    6,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_E1949
    1949,
    1,
    7,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_F1950
    1950,
    1,
    8,
    0x5D4ED,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_G1951
    1951,
    1,
    9,
    0x5D4ED,
  },
#endif

#ifdef PCIE6_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE6_STRAP_BIF_GEN4_EN_w_H1952
    1952,
    1,
    10,
    0x5D4ED,
  },
#endif

#ifdef PCIE6_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE6_STRAP_BIF_LANE_NEGOTIATION1953
    1953,
    3,
    9,
    0x5D4E9,
  },
#endif

#ifdef PCIE6_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE6_STRAP_BIF_LC_PMI_TO_L1_DIS1954
    1954,
    1,
    0,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE6_STRAP_BIF_LC_TX_SWING_OVERRIDE1955
    1955,
    1,
    1,
    0x5D4E8,
  },
#endif

#ifdef PCIE6_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE6_STRAP_BIF_LONG_yTSx_COUNT1956
    1956,
    2,
    3,
    0x5D4E8,
  },
#endif

#ifdef PCIE6_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE6_STRAP_BIF_MED_yTSx_COUNT1957
    1957,
    2,
    5,
    0x5D4E8,
  },
#endif

#ifdef PCIE6_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE6_STRAP_BIF_PHYSTATUS_SELECT1958
    1958,
    1,
    2,
    0x5D4EC,
  },
#endif

#ifdef PCIE6_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE6_STRAP_BIF_SHORT_yTSx_COUNT1959
    1959,
    2,
    7,
    0x5D4E8,
  },
#endif

#ifdef PCIE6_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE6_STRAP_BIF_SKIP_INTERVAL1960
    1960,
    3,
    12,
    0x5D4E9,
  },
#endif

#ifdef PCIE6_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE6_STRAP_CHIP_BIF_MODE1961
    1961,
    1,
    2,
    0x5D4E8,
  },
#endif

#ifdef PCIE7_PCIE0_PUB_SPARE_FUSES
#define
  {
    ///< PCIE7_PCIE0_PUB_SPARE_FUSES1962
    1962,
    1,
    31,
    0x5D507,
  },
#endif

#ifdef PCIE7_PCIE0_WRITE_DISABLE
#define
  {
    ///< PCIE7_PCIE0_WRITE_DISABLE1963
    1963,
    1,
    0,
    0x5D4F8,
  },
#endif

#ifdef PCIE7_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE7_PCIE_EFUSE2_RESERVED_11964
    1964,
    1,
    31,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE7_PCIE_EFUSE2_RESERVED_21965
    1965,
    4,
    11,
    0x5D4FD,
  },
#endif

#ifdef PCIE7_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE7_PCIE_EFUSE3_RESERVED_11966
    1966,
    18,
    31,
    0x5D4FF,
  },
#endif

#ifdef PCIE7_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE7_PCIE_EFUSE3_RESERVED_21967
    1967,
    13,
    18,
    0x5D502,
  },
#endif

#ifdef PCIE7_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE7_PCIE_EFUSE4_RESERVED1968
    1968,
    32,
    31,
    0x5D503,
  },
#endif

#ifdef PCIE7_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE7_STRAP_BIF_ALWAYS_USE_FAST_TXCLK1969
    1969,
    1,
    1,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE7_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w1970
    1970,
    1,
    17,
    0x5D502,
  },
#endif

#ifdef PCIE7_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE7_STRAP_BIF_DEVICE_ID_w1971
    1971,
    16,
    15,
    0x5D4FD,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_A1972
    1972,
    1,
    15,
    0x5D4F9,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_B1973
    1973,
    1,
    17,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_C
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_C1974
    1974,
    1,
    19,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_D
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_D1975
    1975,
    1,
    21,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_E
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_E1976
    1976,
    1,
    23,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_F
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_F1977
    1977,
    1,
    25,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_G
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_G1978
    1978,
    1,
    27,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN2_EN_w_H
#define
  {
    ///< PCIE7_STRAP_BIF_GEN2_EN_w_H1979
    1979,
    1,
    29,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_A1980
    1980,
    1,
    16,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_B1981
    1981,
    1,
    18,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_C
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_C1982
    1982,
    1,
    20,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_D
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_D1983
    1983,
    1,
    22,
    0x5D4FA,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_E
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_E1984
    1984,
    1,
    24,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_F
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_F1985
    1985,
    1,
    26,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_G
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_G1986
    1986,
    1,
    28,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN3_EN_w_H
#define
  {
    ///< PCIE7_STRAP_BIF_GEN3_EN_w_H1987
    1987,
    1,
    30,
    0x5D4FB,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_A1988
    1988,
    1,
    3,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_B1989
    1989,
    1,
    4,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_C
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_C1990
    1990,
    1,
    5,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_D
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_D1991
    1991,
    1,
    6,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_E
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_E1992
    1992,
    1,
    7,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_F
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_F1993
    1993,
    1,
    8,
    0x5D4FD,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_G
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_G1994
    1994,
    1,
    9,
    0x5D4FD,
  },
#endif

#ifdef PCIE7_STRAP_BIF_GEN4_EN_w_H
#define
  {
    ///< PCIE7_STRAP_BIF_GEN4_EN_w_H1995
    1995,
    1,
    10,
    0x5D4FD,
  },
#endif

#ifdef PCIE7_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE7_STRAP_BIF_LANE_NEGOTIATION1996
    1996,
    3,
    9,
    0x5D4F9,
  },
#endif

#ifdef PCIE7_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE7_STRAP_BIF_LC_PMI_TO_L1_DIS1997
    1997,
    1,
    0,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE7_STRAP_BIF_LC_TX_SWING_OVERRIDE1998
    1998,
    1,
    1,
    0x5D4F8,
  },
#endif

#ifdef PCIE7_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE7_STRAP_BIF_LONG_yTSx_COUNT1999
    1999,
    2,
    3,
    0x5D4F8,
  },
#endif

#ifdef PCIE7_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE7_STRAP_BIF_MED_yTSx_COUNT2000
    2000,
    2,
    5,
    0x5D4F8,
  },
#endif

#ifdef PCIE7_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE7_STRAP_BIF_PHYSTATUS_SELECT2001
    2001,
    1,
    2,
    0x5D4FC,
  },
#endif

#ifdef PCIE7_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE7_STRAP_BIF_SHORT_yTSx_COUNT2002
    2002,
    2,
    7,
    0x5D4F8,
  },
#endif

#ifdef PCIE7_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE7_STRAP_BIF_SKIP_INTERVAL2003
    2003,
    3,
    12,
    0x5D4F9,
  },
#endif

#ifdef PCIE7_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE7_STRAP_CHIP_BIF_MODE2004
    2004,
    1,
    2,
    0x5D4F8,
  },
#endif

#ifdef PCIE8_PCIE8_GROUP0_DATA
#define
  {
    ///< PCIE8_PCIE8_GROUP0_DATA2005
    2005,
    32,
    0,
    0x5D988,
  },
#endif

#ifdef PCIE8_PCIE8_PUB_SPARE_FUSES
#define
  {
    ///< PCIE8_PCIE8_PUB_SPARE_FUSES2006
    2006,
    19,
    13,
    0x5D515,
  },
#endif

#ifdef PCIE8_PCIE8_WRITE_DISABLE
#define
  {
    ///< PCIE8_PCIE8_WRITE_DISABLE2007
    2007,
    1,
    0,
    0x5D508,
  },
#endif

#ifdef PCIE8_PCIE_EFUSE2_RESERVED_1
#define
  {
    ///< PCIE8_PCIE_EFUSE2_RESERVED_12008
    2008,
    1,
    19,
    0x5D50A,
  },
#endif

#ifdef PCIE8_PCIE_EFUSE2_RESERVED_2
#define
  {
    ///< PCIE8_PCIE_EFUSE2_RESERVED_22009
    2009,
    4,
    25,
    0x5D50B,
  },
#endif

#ifdef PCIE8_PCIE_EFUSE3_RESERVED_1
#define
  {
    ///< PCIE8_PCIE_EFUSE3_RESERVED_12010
    2010,
    18,
    13,
    0x5D50D,
  },
#endif

#ifdef PCIE8_PCIE_EFUSE3_RESERVED_2
#define
  {
    ///< PCIE8_PCIE_EFUSE3_RESERVED_22011
    2011,
    13,
    0,
    0x5D510,
  },
#endif

#ifdef PCIE8_PCIE_EFUSE4_RESERVED
#define
  {
    ///< PCIE8_PCIE_EFUSE4_RESERVED2012
    2012,
    32,
    13,
    0x5D511,
  },
#endif

#ifdef PCIE8_STRAP_BIF_ALWAYS_USE_FAST_TXCLK
#define
  {
    ///< PCIE8_STRAP_BIF_ALWAYS_USE_FAST_TXCLK2013
    2013,
    1,
    21,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w
#define
  {
    ///< PCIE8_STRAP_BIF_AUTO_RELEASE_HOLD_TRAINING_w2014
    2014,
    1,
    31,
    0x5D50F,
  },
#endif

#ifdef PCIE8_STRAP_BIF_DEVICE_ID_w
#define
  {
    ///< PCIE8_STRAP_BIF_DEVICE_ID_w2015
    2015,
    16,
    29,
    0x5D50B,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN2_EN_w_A
#define
  {
    ///< PCIE8_STRAP_BIF_GEN2_EN_w_A2016
    2016,
    1,
    15,
    0x5D509,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN2_EN_w_B
#define
  {
    ///< PCIE8_STRAP_BIF_GEN2_EN_w_B2017
    2017,
    1,
    17,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN3_EN_w_A
#define
  {
    ///< PCIE8_STRAP_BIF_GEN3_EN_w_A2018
    2018,
    1,
    16,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN3_EN_w_B
#define
  {
    ///< PCIE8_STRAP_BIF_GEN3_EN_w_B2019
    2019,
    1,
    18,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN4_EN_w_A
#define
  {
    ///< PCIE8_STRAP_BIF_GEN4_EN_w_A2020
    2020,
    1,
    23,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_GEN4_EN_w_B
#define
  {
    ///< PCIE8_STRAP_BIF_GEN4_EN_w_B2021
    2021,
    1,
    24,
    0x5D50B,
  },
#endif

#ifdef PCIE8_STRAP_BIF_LANE_NEGOTIATION
#define
  {
    ///< PCIE8_STRAP_BIF_LANE_NEGOTIATION2022
    2022,
    3,
    9,
    0x5D509,
  },
#endif

#ifdef PCIE8_STRAP_BIF_LC_PMI_TO_L1_DIS
#define
  {
    ///< PCIE8_STRAP_BIF_LC_PMI_TO_L1_DIS2023
    2023,
    1,
    20,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_LC_TX_SWING_OVERRIDE
#define
  {
    ///< PCIE8_STRAP_BIF_LC_TX_SWING_OVERRIDE2024
    2024,
    1,
    1,
    0x5D508,
  },
#endif

#ifdef PCIE8_STRAP_BIF_LONG_yTSx_COUNT
#define
  {
    ///< PCIE8_STRAP_BIF_LONG_yTSx_COUNT2025
    2025,
    2,
    3,
    0x5D508,
  },
#endif

#ifdef PCIE8_STRAP_BIF_MED_yTSx_COUNT
#define
  {
    ///< PCIE8_STRAP_BIF_MED_yTSx_COUNT2026
    2026,
    2,
    5,
    0x5D508,
  },
#endif

#ifdef PCIE8_STRAP_BIF_PHYSTATUS_SELECT
#define
  {
    ///< PCIE8_STRAP_BIF_PHYSTATUS_SELECT2027
    2027,
    1,
    22,
    0x5D50A,
  },
#endif

#ifdef PCIE8_STRAP_BIF_SHORT_yTSx_COUNT
#define
  {
    ///< PCIE8_STRAP_BIF_SHORT_yTSx_COUNT2028
    2028,
    2,
    7,
    0x5D508,
  },
#endif

#ifdef PCIE8_STRAP_BIF_SKIP_INTERVAL
#define
  {
    ///< PCIE8_STRAP_BIF_SKIP_INTERVAL2029
    2029,
    3,
    12,
    0x5D509,
  },
#endif

#ifdef PCIE8_STRAP_CHIP_BIF_MODE
#define
  {
    ///< PCIE8_STRAP_CHIP_BIF_MODE2030
    2030,
    1,
    2,
    0x5D508,
  },
#endif

#ifdef PCS0_CCD_PCS0_CCD_GROUP0_DATA
#define
  {
    ///< PCS0_CCD_PCS0_CCD_GROUP0_DATA2031
    2031,
    32,
    0,
    0x1BAC,
  },
#endif

#ifdef PCS0_PCS0_GROUP0_DATA
#define
  {
    ///< PCS0_PCS0_GROUP0_DATA2032
    2032,
    32,
    0,
    0x5D7D0,
  },
#endif

#ifdef PCS10_PCS10_GROUP0_DATA
#define
  {
    ///< PCS10_PCS10_GROUP0_DATA2033
    2033,
    64,
    0,
    0x5D958,
  },
#endif

#ifdef PCS11_PCS11_GROUP0_DATA
#define
  {
    ///< PCS11_PCS11_GROUP0_DATA2034
    2034,
    64,
    0,
    0x5D960,
  },
#endif

#ifdef PCS12_PCS12_GROUP0_DATA
#define
  {
    ///< PCS12_PCS12_GROUP0_DATA2035
    2035,
    64,
    0,
    0x5D968,
  },
#endif

#ifdef PCS13_PCS13_GROUP0_DATA
#define
  {
    ///< PCS13_PCS13_GROUP0_DATA2036
    2036,
    64,
    0,
    0x5D970,
  },
#endif

#ifdef PCS14_PCS14_GROUP0_DATA
#define
  {
    ///< PCS14_PCS14_GROUP0_DATA2037
    2037,
    64,
    0,
    0x5D978,
  },
#endif

#ifdef PCS15_PCS15_GROUP0_DATA
#define
  {
    ///< PCS15_PCS15_GROUP0_DATA2038
    2038,
    64,
    0,
    0x5D980,
  },
#endif

#ifdef PCS1_CCD_PCS1_CCD_GROUP0_DATA
#define
  {
    ///< PCS1_CCD_PCS1_CCD_GROUP0_DATA2039
    2039,
    32,
    0,
    0x1BB0,
  },
#endif

#ifdef PCS1_PCS1_GROUP0_DATA
#define
  {
    ///< PCS1_PCS1_GROUP0_DATA2040
    2040,
    32,
    0,
    0x5D7D4,
  },
#endif

#ifdef PCS20_PCS20_GROUP0_DATA
#define
  {
    ///< PCS20_PCS20_GROUP0_DATA2041
    2041,
    32,
    0,
    0x5D930,
  },
#endif

#ifdef PCS21_PCS21_GROUP0_DATA
#define
  {
    ///< PCS21_PCS21_GROUP0_DATA2042
    2042,
    32,
    0,
    0x5D934,
  },
#endif

#ifdef PCS22_PCS22_GROUP0_DATA
#define
  {
    ///< PCS22_PCS22_GROUP0_DATA2043
    2043,
    32,
    0,
    0x5D938,
  },
#endif

#ifdef PCS23_PCS23_GROUP0_DATA
#define
  {
    ///< PCS23_PCS23_GROUP0_DATA2044
    2044,
    32,
    0,
    0x5D93C,
  },
#endif

#ifdef PCS24_PCS24_GROUP0_DATA
#define
  {
    ///< PCS24_PCS24_GROUP0_DATA2045
    2045,
    32,
    0,
    0x5D940,
  },
#endif

#ifdef PCS25_PCS25_GROUP0_DATA
#define
  {
    ///< PCS25_PCS25_GROUP0_DATA2046
    2046,
    32,
    0,
    0x5D944,
  },
#endif

#ifdef PCS26_PCS26_GROUP0_DATA
#define
  {
    ///< PCS26_PCS26_GROUP0_DATA2047
    2047,
    64,
    0,
    0x5D900,
  },
#endif

#ifdef PCS27_PCS27_GROUP0_DATA
#define
  {
    ///< PCS27_PCS27_GROUP0_DATA2048
    2048,
    64,
    0,
    0x5D908,
  },
#endif

#ifdef PCS28_PCS28_GROUP0_DATA
#define
  {
    ///< PCS28_PCS28_GROUP0_DATA2049
    2049,
    32,
    0,
    0x5D910,
  },
#endif

#ifdef PCS29_PCS29_GROUP0_DATA
#define
  {
    ///< PCS29_PCS29_GROUP0_DATA2050
    2050,
    32,
    0,
    0x5D914,
  },
#endif

#ifdef PCS2_PCS2_GROUP0_DATA
#define
  {
    ///< PCS2_PCS2_GROUP0_DATA2051
    2051,
    32,
    0,
    0x5D7D8,
  },
#endif

#ifdef PCS30_PCS30_GROUP0_DATA
#define
  {
    ///< PCS30_PCS30_GROUP0_DATA2052
    2052,
    32,
    0,
    0x5D918,
  },
#endif

#ifdef PCS31_PCS31_GROUP0_DATA
#define
  {
    ///< PCS31_PCS31_GROUP0_DATA2053
    2053,
    32,
    0,
    0x5D91C,
  },
#endif

#ifdef PCS32_PCS32_GROUP0_DATA
#define
  {
    ///< PCS32_PCS32_GROUP0_DATA2054
    2054,
    32,
    0,
    0x5D920,
  },
#endif

#ifdef PCS33_PCS33_GROUP0_DATA
#define
  {
    ///< PCS33_PCS33_GROUP0_DATA2055
    2055,
    32,
    0,
    0x5D924,
  },
#endif

#ifdef PCS34_PCS34_GROUP0_DATA
#define
  {
    ///< PCS34_PCS34_GROUP0_DATA2056
    2056,
    32,
    0,
    0x5D928,
  },
#endif

#ifdef PCS35_PCS35_GROUP0_DATA
#define
  {
    ///< PCS35_PCS35_GROUP0_DATA2057
    2057,
    32,
    0,
    0x5D92C,
  },
#endif

#ifdef PCS3_PCS3_GROUP0_DATA
#define
  {
    ///< PCS3_PCS3_GROUP0_DATA2058
    2058,
    32,
    0,
    0x5D7DC,
  },
#endif

#ifdef PCS4_PCS4_GROUP0_DATA
#define
  {
    ///< PCS4_PCS4_GROUP0_DATA2059
    2059,
    32,
    0,
    0x5D7E0,
  },
#endif

#ifdef PCS5_PCS5_GROUP0_DATA
#define
  {
    ///< PCS5_PCS5_GROUP0_DATA2060
    2060,
    32,
    0,
    0x5D7E4,
  },
#endif

#ifdef PCS6_PCS6_GROUP0_DATA
#define
  {
    ///< PCS6_PCS6_GROUP0_DATA2061
    2061,
    32,
    0,
    0x5D7E8,
  },
#endif

#ifdef PCS7_PCS7_GROUP0_DATA
#define
  {
    ///< PCS7_PCS7_GROUP0_DATA2062
    2062,
    32,
    0,
    0x5D7EC,
  },
#endif

#ifdef PCS8_PCS8_GROUP0_DATA
#define
  {
    ///< PCS8_PCS8_GROUP0_DATA2063
    2063,
    64,
    0,
    0x5D948,
  },
#endif

#ifdef PCS9_PCS9_GROUP0_DATA
#define
  {
    ///< PCS9_PCS9_GROUP0_DATA2064
    2064,
    64,
    0,
    0x5D950,
  },
#endif

#ifdef PCS_PCS_FUSES
#define
  {
    ///< PCS_PCS_FUSES2065
    2065,
    350,
    0,
    0x5D518,
  },
#endif

#ifdef PCS_PCS_PUB_SPARE_FUSES
#define
  {
    ///< PCS_PCS_PUB_SPARE_FUSES2066
    2066,
    2,
    30,
    0x5D543,
  },
#endif

#ifdef PTDMA0_PTDMA0_GROUP0_DATA
#define
  {
    ///< PTDMA0_PTDMA0_GROUP0_DATA2067
    2067,
    64,
    0,
    0x5D848,
  },
#endif

#ifdef PTDMA1_PTDMA1_GROUP0_DATA
#define
  {
    ///< PTDMA1_PTDMA1_GROUP0_DATA2068
    2068,
    64,
    0,
    0x5D850,
  },
#endif

#ifdef PTDMA2_PTDMA2_GROUP0_DATA
#define
  {
    ///< PTDMA2_PTDMA2_GROUP0_DATA2069
    2069,
    64,
    0,
    0x5D858,
  },
#endif

#ifdef PTDMA3_PTDMA3_GROUP0_DATA
#define
  {
    ///< PTDMA3_PTDMA3_GROUP0_DATA2070
    2070,
    64,
    0,
    0x5D860,
  },
#endif

#ifdef PWR_CCD_LDO_CGR_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CGR_DacOffset2071
    2071,
    8,
    24,
    0x1B53,
  },
#endif

#ifdef PWR_CCD_LDO_CGR_DacRef
#define
  {
    ///< PWR_CCD_LDO_CGR_DacRef2072
    2072,
    8,
    16,
    0x1B52,
  },
#endif

#ifdef PWR_CCD_LDO_CGT_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CGT_DacOffset2073
    2073,
    8,
    8,
    0x1B51,
  },
#endif

#ifdef PWR_CCD_LDO_CGT_DacRef
#define
  {
    ///< PWR_CCD_LDO_CGT_DacRef2074
    2074,
    8,
    0,
    0x1B50,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_0_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX0_0_DacOffset2075
    2075,
    8,
    8,
    0x1B41,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_0_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX0_0_DacRef2076
    2076,
    8,
    0,
    0x1B40,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_1_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX0_1_DacOffset2077
    2077,
    8,
    24,
    0x1B43,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_1_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX0_1_DacRef2078
    2078,
    8,
    16,
    0x1B42,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_2_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX0_2_DacOffset2079
    2079,
    8,
    8,
    0x1B45,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_2_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX0_2_DacRef2080
    2080,
    8,
    0,
    0x1B44,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_3_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX0_3_DacOffset2081
    2081,
    8,
    24,
    0x1B47,
  },
#endif

#ifdef PWR_CCD_LDO_CX0_3_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX0_3_DacRef2082
    2082,
    8,
    16,
    0x1B46,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_0_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX1_0_DacOffset2083
    2083,
    8,
    8,
    0x1B49,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_0_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX1_0_DacRef2084
    2084,
    8,
    0,
    0x1B48,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_1_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX1_1_DacOffset2085
    2085,
    8,
    24,
    0x1B4B,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_1_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX1_1_DacRef2086
    2086,
    8,
    16,
    0x1B4A,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_2_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX1_2_DacOffset2087
    2087,
    8,
    8,
    0x1B4D,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_2_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX1_2_DacRef2088
    2088,
    8,
    0,
    0x1B4C,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_3_DacOffset
#define
  {
    ///< PWR_CCD_LDO_CX1_3_DacOffset2089
    2089,
    8,
    24,
    0x1B4F,
  },
#endif

#ifdef PWR_CCD_LDO_CX1_3_DacRef
#define
  {
    ///< PWR_CCD_LDO_CX1_3_DacRef2090
    2090,
    8,
    16,
    0x1B4E,
  },
#endif

#ifdef PWR_CCD_LDO_PCS_DacOffset
#define
  {
    ///< PWR_CCD_LDO_PCS_DacOffset2091
    2091,
    8,
    24,
    0x1B3F,
  },
#endif

#ifdef PWR_CCD_LDO_PCS_DacRef
#define
  {
    ///< PWR_CCD_LDO_PCS_DacRef2092
    2092,
    8,
    16,
    0x1B3E,
  },
#endif

#ifdef PWR_CCD_LDO_SMU_DacOffset
#define
  {
    ///< PWR_CCD_LDO_SMU_DacOffset2093
    2093,
    8,
    8,
    0x1B3D,
  },
#endif

#ifdef PWR_CCD_LDO_SMU_DacRef
#define
  {
    ///< PWR_CCD_LDO_SMU_DacRef2094
    2094,
    8,
    0,
    0x1B3C,
  },
#endif

#ifdef PWR_CCD_LDO_Spare
#define
  {
    ///< PWR_CCD_LDO_Spare2095
    2095,
    3,
    29,
    0x1B57,
  },
#endif

#ifdef PWR_CCD_LDO_TIMING
#define
  {
    ///< PWR_CCD_LDO_TIMING2096
    2096,
    26,
    3,
    0x1B54,
  },
#endif

#ifdef PWR_CCD_bg_slope_trim
#define
  {
    ///< PWR_CCD_bg_slope_trim2097
    2097,
    3,
    0,
    0x1B54,
  },
#endif

#ifdef PWR_ODPR_0_CSR_Spare
#define
  {
    ///< PWR_ODPR_0_CSR_Spare2098
    2098,
    3,
    20,
    0x1B5A,
  },
#endif

#ifdef PWR_ODPR_0_res_ctl
#define
  {
    ///< PWR_ODPR_0_res_ctl2099
    2099,
    10,
    0,
    0x1B58,
  },
#endif

#ifdef PWR_ODPR_1_CSR_Spare
#define
  {
    ///< PWR_ODPR_1_CSR_Spare2100
    2100,
    3,
    23,
    0x1B5A,
  },
#endif

#ifdef PWR_ODPR_1_res_ctl
#define
  {
    ///< PWR_ODPR_1_res_ctl2101
    2101,
    10,
    10,
    0x1B59,
  },
#endif

#ifdef PWR_ODPR_Spare_0
#define
  {
    ///< PWR_ODPR_Spare_02102
    2102,
    6,
    26,
    0x1B5B,
  },
#endif

#ifdef RESERVED_C_reserved_0
#define
  {
    ///< RESERVED_C_reserved_02103
    2103,
    32,
    0,
    0x5D12C,
  },
#endif

#ifdef RESERVED_N_reserved_0
#define
  {
    ///< RESERVED_N_reserved_02104
    2104,
    32,
    0,
    0x5D6F4,
  },
#endif

#ifdef RESERVED_N_reserved_1
#define
  {
    ///< RESERVED_N_reserved_12105
    2105,
    32,
    0,
    0x5D6F8,
  },
#endif

#ifdef RESERVED_N_reserved_2
#define
  {
    ///< RESERVED_N_reserved_22106
    2106,
    32,
    0,
    0x5D6FC,
  },
#endif

#ifdef RESERVED_N_reserved_3
#define
  {
    ///< RESERVED_N_reserved_32107
    2107,
    32,
    0,
    0x5D700,
  },
#endif

#ifdef SATA0_SATA0_GROUP0_DATA
#define
  {
    ///< SATA0_SATA0_GROUP0_DATA2108
    2108,
    64,
    0,
    0x5D868,
  },
#endif

#ifdef SATA0_SATA_WRITE_DISABLE
#define
  {
    ///< SATA0_SATA_WRITE_DISABLE2109
    2109,
    1,
    31,
    0x5D547,
  },
#endif

#ifdef SATA0_sata_fuse
#define
  {
    ///< SATA0_sata_fuse2110
    2110,
    31,
    0,
    0x5D544,
  },
#endif

#ifdef SATA1_SATA1_GROUP0_DATA
#define
  {
    ///< SATA1_SATA1_GROUP0_DATA2111
    2111,
    64,
    0,
    0x5D870,
  },
#endif

#ifdef SATA1_SATA_WRITE_DISABLE
#define
  {
    ///< SATA1_SATA_WRITE_DISABLE2112
    2112,
    1,
    31,
    0x5D54B,
  },
#endif

#ifdef SATA1_sata_fuse
#define
  {
    ///< SATA1_sata_fuse2113
    2113,
    31,
    0,
    0x5D548,
  },
#endif

#ifdef SATA2_SATA2_GROUP0_DATA
#define
  {
    ///< SATA2_SATA2_GROUP0_DATA2114
    2114,
    64,
    0,
    0x5D878,
  },
#endif

#ifdef SATA2_SATA_WRITE_DISABLE
#define
  {
    ///< SATA2_SATA_WRITE_DISABLE2115
    2115,
    1,
    31,
    0x5D54F,
  },
#endif

#ifdef SATA2_sata_fuse
#define
  {
    ///< SATA2_sata_fuse2116
    2116,
    31,
    0,
    0x5D54C,
  },
#endif

#ifdef SATA3_SATA3_GROUP0_DATA
#define
  {
    ///< SATA3_SATA3_GROUP0_DATA2117
    2117,
    64,
    0,
    0x5D880,
  },
#endif

#ifdef SATA3_SATA_WRITE_DISABLE
#define
  {
    ///< SATA3_SATA_WRITE_DISABLE2118
    2118,
    1,
    31,
    0x5D553,
  },
#endif

#ifdef SATA3_sata_fuse
#define
  {
    ///< SATA3_sata_fuse2119
    2119,
    31,
    0,
    0x5D550,
  },
#endif

#ifdef SMS_UMC0_GROUP1_DATA
#define
  {
    ///< SMS_UMC0_GROUP1_DATA2120
    2120,
    96,
    0,
    0x5D8A0,
  },
#endif

#ifdef SMS_UMC1_GROUP1_DATA
#define
  {
    ///< SMS_UMC1_GROUP1_DATA2121
    2121,
    96,
    0,
    0x5D8AC,
  },
#endif

#ifdef SMS_UMC2_GROUP1_DATA
#define
  {
    ///< SMS_UMC2_GROUP1_DATA2122
    2122,
    96,
    0,
    0x5D8B8,
  },
#endif

#ifdef SMS_UMC3_GROUP1_DATA
#define
  {
    ///< SMS_UMC3_GROUP1_DATA2123
    2123,
    96,
    0,
    0x5D8C4,
  },
#endif

#ifdef SMS_UMC4_GROUP1_DATA
#define
  {
    ///< SMS_UMC4_GROUP1_DATA2124
    2124,
    96,
    0,
    0x5D8D0,
  },
#endif

#ifdef SMS_UMC5_GROUP1_DATA
#define
  {
    ///< SMS_UMC5_GROUP1_DATA2125
    2125,
    96,
    0,
    0x5D8DC,
  },
#endif

#ifdef SMS_UMC6_GROUP1_DATA
#define
  {
    ///< SMS_UMC6_GROUP1_DATA2126
    2126,
    96,
    0,
    0x5D8E8,
  },
#endif

#ifdef SMS_UMC7_GROUP1_DATA
#define
  {
    ///< SMS_UMC7_GROUP1_DATA2127
    2127,
    96,
    0,
    0x5D8F4,
  },
#endif

#ifdef SMUIO_COF_VID_PROG
#define
  {
    ///< SMUIO_COF_VID_PROG2128
    2128,
    1,
    0,
    0x5D554,
  },
#endif

#ifdef SMUIO_I2C_ENABLE
#define
  {
    ///< SMUIO_I2C_ENABLE2129
    2129,
    1,
    3,
    0x5D554,
  },
#endif

#ifdef SMUIO_IOD_LDO_TIMING
#define
  {
    ///< SMUIO_IOD_LDO_TIMING2130
    2130,
    26,
    3,
    0x5D588,
  },
#endif

#ifdef SMUIO_IOD_LDO_spare
#define
  {
    ///< SMUIO_IOD_LDO_spare2131
    2131,
    3,
    29,
    0x5D58B,
  },
#endif

#ifdef SMUIO_IOD_bg_slope_trim
#define
  {
    ///< SMUIO_IOD_bg_slope_trim2132
    2132,
    3,
    0,
    0x5D588,
  },
#endif

#ifdef SMUIO_LDO_DDR0_0_DacOffset
#define
  {
    ///< SMUIO_LDO_DDR0_0_DacOffset2133
    2133,
    8,
    8,
    0x5D561,
  },
#endif

#ifdef SMUIO_LDO_DDR0_0_DacRef
#define
  {
    ///< SMUIO_LDO_DDR0_0_DacRef2134
    2134,
    8,
    0,
    0x5D560,
  },
#endif

#ifdef SMUIO_LDO_DDR0_1_DacOffset
#define
  {
    ///< SMUIO_LDO_DDR0_1_DacOffset2135
    2135,
    8,
    24,
    0x5D563,
  },
#endif

#ifdef SMUIO_LDO_DDR0_1_DacRef
#define
  {
    ///< SMUIO_LDO_DDR0_1_DacRef2136
    2136,
    8,
    16,
    0x5D562,
  },
#endif

#ifdef SMUIO_LDO_DDR1_0_DacOffset
#define
  {
    ///< SMUIO_LDO_DDR1_0_DacOffset2137
    2137,
    8,
    8,
    0x5D565,
  },
#endif

#ifdef SMUIO_LDO_DDR1_0_DacRef
#define
  {
    ///< SMUIO_LDO_DDR1_0_DacRef2138
    2138,
    8,
    0,
    0x5D564,
  },
#endif

#ifdef SMUIO_LDO_DDR1_1_DacOffset
#define
  {
    ///< SMUIO_LDO_DDR1_1_DacOffset2139
    2139,
    8,
    24,
    0x5D567,
  },
#endif

#ifdef SMUIO_LDO_DDR1_1_DacRef
#define
  {
    ///< SMUIO_LDO_DDR1_1_DacRef2140
    2140,
    8,
    16,
    0x5D566,
  },
#endif

#ifdef SMUIO_LDO_GMI0_0_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI0_0_DacOffset2141
    2141,
    8,
    8,
    0x5D569,
  },
#endif

#ifdef SMUIO_LDO_GMI0_0_DacRef
#define
  {
    ///< SMUIO_LDO_GMI0_0_DacRef2142
    2142,
    8,
    0,
    0x5D568,
  },
#endif

#ifdef SMUIO_LDO_GMI0_1_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI0_1_DacOffset2143
    2143,
    8,
    24,
    0x5D56B,
  },
#endif

#ifdef SMUIO_LDO_GMI0_1_DacRef
#define
  {
    ///< SMUIO_LDO_GMI0_1_DacRef2144
    2144,
    8,
    16,
    0x5D56A,
  },
#endif

#ifdef SMUIO_LDO_GMI0_2_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI0_2_DacOffset2145
    2145,
    8,
    8,
    0x5D56D,
  },
#endif

#ifdef SMUIO_LDO_GMI0_2_DacRef
#define
  {
    ///< SMUIO_LDO_GMI0_2_DacRef2146
    2146,
    8,
    0,
    0x5D56C,
  },
#endif

#ifdef SMUIO_LDO_GMI0_3_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI0_3_DacOffset2147
    2147,
    8,
    24,
    0x5D56F,
  },
#endif

#ifdef SMUIO_LDO_GMI0_3_DacRef
#define
  {
    ///< SMUIO_LDO_GMI0_3_DacRef2148
    2148,
    8,
    16,
    0x5D56E,
  },
#endif

#ifdef SMUIO_LDO_GMI1_0_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI1_0_DacOffset2149
    2149,
    8,
    8,
    0x5D571,
  },
#endif

#ifdef SMUIO_LDO_GMI1_0_DacRef
#define
  {
    ///< SMUIO_LDO_GMI1_0_DacRef2150
    2150,
    8,
    0,
    0x5D570,
  },
#endif

#ifdef SMUIO_LDO_GMI1_1_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI1_1_DacOffset2151
    2151,
    8,
    24,
    0x5D573,
  },
#endif

#ifdef SMUIO_LDO_GMI1_1_DacRef
#define
  {
    ///< SMUIO_LDO_GMI1_1_DacRef2152
    2152,
    8,
    16,
    0x5D572,
  },
#endif

#ifdef SMUIO_LDO_GMI1_2_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI1_2_DacOffset2153
    2153,
    8,
    8,
    0x5D575,
  },
#endif

#ifdef SMUIO_LDO_GMI1_2_DacRef
#define
  {
    ///< SMUIO_LDO_GMI1_2_DacRef2154
    2154,
    8,
    0,
    0x5D574,
  },
#endif

#ifdef SMUIO_LDO_GMI1_3_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI1_3_DacOffset2155
    2155,
    8,
    24,
    0x5D577,
  },
#endif

#ifdef SMUIO_LDO_GMI1_3_DacRef
#define
  {
    ///< SMUIO_LDO_GMI1_3_DacRef2156
    2156,
    8,
    16,
    0x5D576,
  },
#endif

#ifdef SMUIO_LDO_GMI2_0_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI2_0_DacOffset2157
    2157,
    8,
    8,
    0x5D579,
  },
#endif

#ifdef SMUIO_LDO_GMI2_0_DacRef
#define
  {
    ///< SMUIO_LDO_GMI2_0_DacRef2158
    2158,
    8,
    0,
    0x5D578,
  },
#endif

#ifdef SMUIO_LDO_GMI2_1_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI2_1_DacOffset2159
    2159,
    8,
    24,
    0x5D57B,
  },
#endif

#ifdef SMUIO_LDO_GMI2_1_DacRef
#define
  {
    ///< SMUIO_LDO_GMI2_1_DacRef2160
    2160,
    8,
    16,
    0x5D57A,
  },
#endif

#ifdef SMUIO_LDO_GMI2_2_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI2_2_DacOffset2161
    2161,
    8,
    8,
    0x5D57D,
  },
#endif

#ifdef SMUIO_LDO_GMI2_2_DacRef
#define
  {
    ///< SMUIO_LDO_GMI2_2_DacRef2162
    2162,
    8,
    0,
    0x5D57C,
  },
#endif

#ifdef SMUIO_LDO_GMI2_3_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI2_3_DacOffset2163
    2163,
    8,
    24,
    0x5D57F,
  },
#endif

#ifdef SMUIO_LDO_GMI2_3_DacRef
#define
  {
    ///< SMUIO_LDO_GMI2_3_DacRef2164
    2164,
    8,
    16,
    0x5D57E,
  },
#endif

#ifdef SMUIO_LDO_GMI3_0_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI3_0_DacOffset2165
    2165,
    8,
    8,
    0x5D581,
  },
#endif

#ifdef SMUIO_LDO_GMI3_0_DacRef
#define
  {
    ///< SMUIO_LDO_GMI3_0_DacRef2166
    2166,
    8,
    0,
    0x5D580,
  },
#endif

#ifdef SMUIO_LDO_GMI3_1_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI3_1_DacOffset2167
    2167,
    8,
    24,
    0x5D583,
  },
#endif

#ifdef SMUIO_LDO_GMI3_1_DacRef
#define
  {
    ///< SMUIO_LDO_GMI3_1_DacRef2168
    2168,
    8,
    16,
    0x5D582,
  },
#endif

#ifdef SMUIO_LDO_GMI3_2_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI3_2_DacOffset2169
    2169,
    8,
    8,
    0x5D585,
  },
#endif

#ifdef SMUIO_LDO_GMI3_2_DacRef
#define
  {
    ///< SMUIO_LDO_GMI3_2_DacRef2170
    2170,
    8,
    0,
    0x5D584,
  },
#endif

#ifdef SMUIO_LDO_GMI3_3_DacOffset
#define
  {
    ///< SMUIO_LDO_GMI3_3_DacOffset2171
    2171,
    8,
    24,
    0x5D587,
  },
#endif

#ifdef SMUIO_LDO_GMI3_3_DacRef
#define
  {
    ///< SMUIO_LDO_GMI3_3_DacRef2172
    2172,
    8,
    16,
    0x5D586,
  },
#endif

#ifdef SMUIO_LDO_USB0_DacOffset
#define
  {
    ///< SMUIO_LDO_USB0_DacOffset2173
    2173,
    8,
    8,
    0x5D55D,
  },
#endif

#ifdef SMUIO_LDO_USB0_DacRef
#define
  {
    ///< SMUIO_LDO_USB0_DacRef2174
    2174,
    8,
    0,
    0x5D55C,
  },
#endif

#ifdef SMUIO_LDO_USB1_DacOffset
#define
  {
    ///< SMUIO_LDO_USB1_DacOffset2175
    2175,
    8,
    24,
    0x5D55F,
  },
#endif

#ifdef SMUIO_LDO_USB1_DacRef
#define
  {
    ///< SMUIO_LDO_USB1_DacRef2176
    2176,
    8,
    16,
    0x5D55E,
  },
#endif

#ifdef SMUIO_MAX_VID
#define
  {
    ///< SMUIO_MAX_VID2177
    2177,
    8,
    20,
    0x5D556,
  },
#endif

#ifdef SMUIO_MIN_VID
#define
  {
    ///< SMUIO_MIN_VID2178
    2178,
    8,
    12,
    0x5D555,
  },
#endif

#ifdef SMUIO_ODPR_0_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_0_CSR_Spare2179
    2179,
    3,
    0,
    0x5D5B4,
  },
#endif

#ifdef SMUIO_ODPR_0_res_ctl
#define
  {
    ///< SMUIO_ODPR_0_res_ctl2180
    2180,
    10,
    0,
    0x5D58C,
  },
#endif

#ifdef SMUIO_ODPR_10_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_10_CSR_Spare2181
    2181,
    3,
    30,
    0x5D5B7,
  },
#endif

#ifdef SMUIO_ODPR_10_res_ctl
#define
  {
    ///< SMUIO_ODPR_10_res_ctl2182
    2182,
    10,
    4,
    0x5D598,
  },
#endif

#ifdef SMUIO_ODPR_11_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_11_CSR_Spare2183
    2183,
    3,
    1,
    0x5D5B8,
  },
#endif

#ifdef SMUIO_ODPR_11_res_ctl
#define
  {
    ///< SMUIO_ODPR_11_res_ctl2184
    2184,
    10,
    14,
    0x5D599,
  },
#endif

#ifdef SMUIO_ODPR_12_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_12_CSR_Spare2185
    2185,
    3,
    4,
    0x5D5B8,
  },
#endif

#ifdef SMUIO_ODPR_12_res_ctl
#define
  {
    ///< SMUIO_ODPR_12_res_ctl2186
    2186,
    10,
    24,
    0x5D59B,
  },
#endif

#ifdef SMUIO_ODPR_13_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_13_CSR_Spare2187
    2187,
    3,
    7,
    0x5D5B8,
  },
#endif

#ifdef SMUIO_ODPR_13_res_ctl
#define
  {
    ///< SMUIO_ODPR_13_res_ctl2188
    2188,
    10,
    2,
    0x5D59C,
  },
#endif

#ifdef SMUIO_ODPR_14_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_14_CSR_Spare2189
    2189,
    3,
    10,
    0x5D5B9,
  },
#endif

#ifdef SMUIO_ODPR_14_res_ctl
#define
  {
    ///< SMUIO_ODPR_14_res_ctl2190
    2190,
    10,
    12,
    0x5D59D,
  },
#endif

#ifdef SMUIO_ODPR_15_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_15_CSR_Spare2191
    2191,
    3,
    13,
    0x5D5B9,
  },
#endif

#ifdef SMUIO_ODPR_15_res_ctl
#define
  {
    ///< SMUIO_ODPR_15_res_ctl2192
    2192,
    10,
    22,
    0x5D59E,
  },
#endif

#ifdef SMUIO_ODPR_16_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_16_CSR_Spare2193
    2193,
    3,
    16,
    0x5D5BA,
  },
#endif

#ifdef SMUIO_ODPR_16_res_ctl
#define
  {
    ///< SMUIO_ODPR_16_res_ctl2194
    2194,
    10,
    0,
    0x5D5A0,
  },
#endif

#ifdef SMUIO_ODPR_17_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_17_CSR_Spare2195
    2195,
    3,
    19,
    0x5D5BA,
  },
#endif

#ifdef SMUIO_ODPR_17_res_ctl
#define
  {
    ///< SMUIO_ODPR_17_res_ctl2196
    2196,
    10,
    10,
    0x5D5A1,
  },
#endif

#ifdef SMUIO_ODPR_18_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_18_CSR_Spare2197
    2197,
    3,
    22,
    0x5D5BA,
  },
#endif

#ifdef SMUIO_ODPR_18_res_ctl
#define
  {
    ///< SMUIO_ODPR_18_res_ctl2198
    2198,
    10,
    20,
    0x5D5A2,
  },
#endif

#ifdef SMUIO_ODPR_19_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_19_CSR_Spare2199
    2199,
    3,
    25,
    0x5D5BB,
  },
#endif

#ifdef SMUIO_ODPR_19_res_ctl
#define
  {
    ///< SMUIO_ODPR_19_res_ctl2200
    2200,
    10,
    30,
    0x5D5A3,
  },
#endif

#ifdef SMUIO_ODPR_1_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_1_CSR_Spare2201
    2201,
    3,
    3,
    0x5D5B4,
  },
#endif

#ifdef SMUIO_ODPR_1_res_ctl
#define
  {
    ///< SMUIO_ODPR_1_res_ctl2202
    2202,
    10,
    10,
    0x5D58D,
  },
#endif

#ifdef SMUIO_ODPR_20_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_20_CSR_Spare2203
    2203,
    3,
    28,
    0x5D5BB,
  },
#endif

#ifdef SMUIO_ODPR_20_res_ctl
#define
  {
    ///< SMUIO_ODPR_20_res_ctl2204
    2204,
    10,
    8,
    0x5D5A5,
  },
#endif

#ifdef SMUIO_ODPR_21_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_21_CSR_Spare2205
    2205,
    3,
    31,
    0x5D5BB,
  },
#endif

#ifdef SMUIO_ODPR_21_res_ctl
#define
  {
    ///< SMUIO_ODPR_21_res_ctl2206
    2206,
    10,
    18,
    0x5D5A6,
  },
#endif

#ifdef SMUIO_ODPR_22_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_22_CSR_Spare2207
    2207,
    3,
    2,
    0x5D5BC,
  },
#endif

#ifdef SMUIO_ODPR_22_res_ctl
#define
  {
    ///< SMUIO_ODPR_22_res_ctl2208
    2208,
    10,
    28,
    0x5D5A7,
  },
#endif

#ifdef SMUIO_ODPR_23_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_23_CSR_Spare2209
    2209,
    3,
    5,
    0x5D5BC,
  },
#endif

#ifdef SMUIO_ODPR_23_res_ctl
#define
  {
    ///< SMUIO_ODPR_23_res_ctl2210
    2210,
    10,
    6,
    0x5D5A8,
  },
#endif

#ifdef SMUIO_ODPR_24_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_24_CSR_Spare2211
    2211,
    3,
    8,
    0x5D5BD,
  },
#endif

#ifdef SMUIO_ODPR_24_res_ctl
#define
  {
    ///< SMUIO_ODPR_24_res_ctl2212
    2212,
    10,
    16,
    0x5D5AA,
  },
#endif

#ifdef SMUIO_ODPR_25_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_25_CSR_Spare2213
    2213,
    3,
    11,
    0x5D5BD,
  },
#endif

#ifdef SMUIO_ODPR_25_res_ctl
#define
  {
    ///< SMUIO_ODPR_25_res_ctl2214
    2214,
    10,
    26,
    0x5D5AB,
  },
#endif

#ifdef SMUIO_ODPR_26_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_26_CSR_Spare2215
    2215,
    3,
    14,
    0x5D5BD,
  },
#endif

#ifdef SMUIO_ODPR_26_res_ctl
#define
  {
    ///< SMUIO_ODPR_26_res_ctl2216
    2216,
    10,
    4,
    0x5D5AC,
  },
#endif

#ifdef SMUIO_ODPR_27_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_27_CSR_Spare2217
    2217,
    3,
    17,
    0x5D5BE,
  },
#endif

#ifdef SMUIO_ODPR_27_res_ctl
#define
  {
    ///< SMUIO_ODPR_27_res_ctl2218
    2218,
    10,
    14,
    0x5D5AD,
  },
#endif

#ifdef SMUIO_ODPR_28_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_28_CSR_Spare2219
    2219,
    3,
    20,
    0x5D5BE,
  },
#endif

#ifdef SMUIO_ODPR_28_res_ctl
#define
  {
    ///< SMUIO_ODPR_28_res_ctl2220
    2220,
    10,
    24,
    0x5D5AF,
  },
#endif

#ifdef SMUIO_ODPR_29_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_29_CSR_Spare2221
    2221,
    3,
    23,
    0x5D5BE,
  },
#endif

#ifdef SMUIO_ODPR_29_res_ctl
#define
  {
    ///< SMUIO_ODPR_29_res_ctl2222
    2222,
    10,
    2,
    0x5D5B0,
  },
#endif

#ifdef SMUIO_ODPR_2_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_2_CSR_Spare2223
    2223,
    3,
    6,
    0x5D5B4,
  },
#endif

#ifdef SMUIO_ODPR_2_res_ctl
#define
  {
    ///< SMUIO_ODPR_2_res_ctl2224
    2224,
    10,
    20,
    0x5D58E,
  },
#endif

#ifdef SMUIO_ODPR_30_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_30_CSR_Spare2225
    2225,
    3,
    26,
    0x5D5BF,
  },
#endif

#ifdef SMUIO_ODPR_30_res_ctl
#define
  {
    ///< SMUIO_ODPR_30_res_ctl2226
    2226,
    10,
    12,
    0x5D5B1,
  },
#endif

#ifdef SMUIO_ODPR_31_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_31_CSR_Spare2227
    2227,
    3,
    29,
    0x5D5BF,
  },
#endif

#ifdef SMUIO_ODPR_31_res_ctl
#define
  {
    ///< SMUIO_ODPR_31_res_ctl2228
    2228,
    10,
    22,
    0x5D5B2,
  },
#endif

#ifdef SMUIO_ODPR_3_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_3_CSR_Spare2229
    2229,
    3,
    9,
    0x5D5B5,
  },
#endif

#ifdef SMUIO_ODPR_3_res_ctl
#define
  {
    ///< SMUIO_ODPR_3_res_ctl2230
    2230,
    10,
    30,
    0x5D58F,
  },
#endif

#ifdef SMUIO_ODPR_4_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_4_CSR_Spare2231
    2231,
    3,
    12,
    0x5D5B5,
  },
#endif

#ifdef SMUIO_ODPR_4_res_ctl
#define
  {
    ///< SMUIO_ODPR_4_res_ctl2232
    2232,
    10,
    8,
    0x5D591,
  },
#endif

#ifdef SMUIO_ODPR_5_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_5_CSR_Spare2233
    2233,
    3,
    15,
    0x5D5B5,
  },
#endif

#ifdef SMUIO_ODPR_5_res_ctl
#define
  {
    ///< SMUIO_ODPR_5_res_ctl2234
    2234,
    10,
    18,
    0x5D592,
  },
#endif

#ifdef SMUIO_ODPR_6_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_6_CSR_Spare2235
    2235,
    3,
    18,
    0x5D5B6,
  },
#endif

#ifdef SMUIO_ODPR_6_res_ctl
#define
  {
    ///< SMUIO_ODPR_6_res_ctl2236
    2236,
    10,
    28,
    0x5D593,
  },
#endif

#ifdef SMUIO_ODPR_7_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_7_CSR_Spare2237
    2237,
    3,
    21,
    0x5D5B6,
  },
#endif

#ifdef SMUIO_ODPR_7_res_ctl
#define
  {
    ///< SMUIO_ODPR_7_res_ctl2238
    2238,
    10,
    6,
    0x5D594,
  },
#endif

#ifdef SMUIO_ODPR_8_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_8_CSR_Spare2239
    2239,
    3,
    24,
    0x5D5B7,
  },
#endif

#ifdef SMUIO_ODPR_8_res_ctl
#define
  {
    ///< SMUIO_ODPR_8_res_ctl2240
    2240,
    10,
    16,
    0x5D596,
  },
#endif

#ifdef SMUIO_ODPR_9_CSR_Spare
#define
  {
    ///< SMUIO_ODPR_9_CSR_Spare2241
    2241,
    3,
    27,
    0x5D5B7,
  },
#endif

#ifdef SMUIO_ODPR_9_res_ctl
#define
  {
    ///< SMUIO_ODPR_9_res_ctl2242
    2242,
    10,
    26,
    0x5D597,
  },
#endif

#ifdef SMUIO_QUICK_SLAM_ZERO_VID_EN
#define
  {
    ///< SMUIO_QUICK_SLAM_ZERO_VID_EN2243
    2243,
    1,
    2,
    0x5D554,
  },
#endif

#ifdef SMUIO_SMUIO_PUB_SPARE_FUSES
#define
  {
    ///< SMUIO_SMUIO_PUB_SPARE_FUSES2244
    2244,
    1,
    31,
    0x5D55B,
  },
#endif

#ifdef SMUIO_SMUIO_WRITE_DISABLE
#define
  {
    ///< SMUIO_SMUIO_WRITE_DISABLE2245
    2245,
    1,
    30,
    0x5D55B,
  },
#endif

#ifdef SMUIO_STARTUP_VID_SVI0_EN
#define
  {
    ///< SMUIO_STARTUP_VID_SVI0_EN2246
    2246,
    1,
    28,
    0x5D557,
  },
#endif

#ifdef SMUIO_STARTUP_VID_SVI1_EN
#define
  {
    ///< SMUIO_STARTUP_VID_SVI1_EN2247
    2247,
    1,
    29,
    0x5D557,
  },
#endif

#ifdef SMUIO_SVI0_PLANE0_STARTUP_VID
#define
  {
    ///< SMUIO_SVI0_PLANE0_STARTUP_VID2248
    2248,
    8,
    30,
    0x5D557,
  },
#endif

#ifdef SMUIO_SVI0_PLANE1_STARTUP_VID
#define
  {
    ///< SMUIO_SVI0_PLANE1_STARTUP_VID2249
    2249,
    8,
    6,
    0x5D558,
  },
#endif

#ifdef SMUIO_SVI1_PLANE0_STARTUP_VID
#define
  {
    ///< SMUIO_SVI1_PLANE0_STARTUP_VID2250
    2250,
    8,
    14,
    0x5D559,
  },
#endif

#ifdef SMUIO_SVI1_PLANE1_STARTUP_VID
#define
  {
    ///< SMUIO_SVI1_PLANE1_STARTUP_VID2251
    2251,
    8,
    22,
    0x5D55A,
  },
#endif

#ifdef SMUIO_SVT_DIS
#define
  {
    ///< SMUIO_SVT_DIS2252
    2252,
    1,
    1,
    0x5D554,
  },
#endif

#ifdef SMUIO_THERM_VID
#define
  {
    ///< SMUIO_THERM_VID2253
    2253,
    8,
    4,
    0x5D554,
  },
#endif

#ifdef SYSTEMHUB0_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB0_STRAP_SYSHUB_STRAP_HWREV_LSB22254
    2254,
    2,
    0,
    0x5D5C0,
  },
#endif

#ifdef SYSTEMHUB0_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB0_STRAP_SYSHUB_STRAP_SWREV_LSB22255
    2255,
    2,
    2,
    0x5D5C0,
  },
#endif

#ifdef SYSTEMHUB0_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB0_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES2256
    2256,
    28,
    4,
    0x5D5C0,
  },
#endif

#ifdef SYSTEMHUB1_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB1_STRAP_SYSHUB_STRAP_HWREV_LSB22257
    2257,
    2,
    0,
    0x5D5C4,
  },
#endif

#ifdef SYSTEMHUB1_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB1_STRAP_SYSHUB_STRAP_SWREV_LSB22258
    2258,
    2,
    2,
    0x5D5C4,
  },
#endif

#ifdef SYSTEMHUB1_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB1_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES2259
    2259,
    28,
    4,
    0x5D5C4,
  },
#endif

#ifdef SYSTEMHUB2_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB2_STRAP_SYSHUB_STRAP_HWREV_LSB22260
    2260,
    2,
    0,
    0x5D5C8,
  },
#endif

#ifdef SYSTEMHUB2_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB2_STRAP_SYSHUB_STRAP_SWREV_LSB22261
    2261,
    2,
    2,
    0x5D5C8,
  },
#endif

#ifdef SYSTEMHUB2_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB2_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES2262
    2262,
    28,
    4,
    0x5D5C8,
  },
#endif

#ifdef SYSTEMHUB3_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB3_STRAP_SYSHUB_STRAP_HWREV_LSB22263
    2263,
    2,
    0,
    0x5D5CC,
  },
#endif

#ifdef SYSTEMHUB3_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB3_STRAP_SYSHUB_STRAP_SWREV_LSB22264
    2264,
    2,
    2,
    0x5D5CC,
  },
#endif

#ifdef SYSTEMHUB3_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB3_SYSTEMHUB_SSP_GENERIC_A_PUB_SPARE_FUSES2265
    2265,
    28,
    4,
    0x5D5CC,
  },
#endif

#ifdef SYSTEMHUB4_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB4_STRAP_SYSHUB_STRAP_HWREV_LSB22266
    2266,
    2,
    0,
    0x5D5D0,
  },
#endif

#ifdef SYSTEMHUB4_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB4_STRAP_SYSHUB_STRAP_SWREV_LSB22267
    2267,
    2,
    2,
    0x5D5D0,
  },
#endif

#ifdef SYSTEMHUB4_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB4_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES2268
    2268,
    28,
    4,
    0x5D5D0,
  },
#endif

#ifdef SYSTEMHUB5_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB5_STRAP_SYSHUB_STRAP_HWREV_LSB22269
    2269,
    2,
    0,
    0x5D5D4,
  },
#endif

#ifdef SYSTEMHUB5_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB5_STRAP_SYSHUB_STRAP_SWREV_LSB22270
    2270,
    2,
    2,
    0x5D5D4,
  },
#endif

#ifdef SYSTEMHUB5_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB5_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES2271
    2271,
    28,
    4,
    0x5D5D4,
  },
#endif

#ifdef SYSTEMHUB6_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB6_STRAP_SYSHUB_STRAP_HWREV_LSB22272
    2272,
    2,
    0,
    0x5D5D8,
  },
#endif

#ifdef SYSTEMHUB6_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB6_STRAP_SYSHUB_STRAP_SWREV_LSB22273
    2273,
    2,
    2,
    0x5D5D8,
  },
#endif

#ifdef SYSTEMHUB6_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB6_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES2274
    2274,
    28,
    4,
    0x5D5D8,
  },
#endif

#ifdef SYSTEMHUB7_STRAP_SYSHUB_STRAP_HWREV_LSB2
#define
  {
    ///< SYSTEMHUB7_STRAP_SYSHUB_STRAP_HWREV_LSB22275
    2275,
    2,
    0,
    0x5D5DC,
  },
#endif

#ifdef SYSTEMHUB7_STRAP_SYSHUB_STRAP_SWREV_LSB2
#define
  {
    ///< SYSTEMHUB7_STRAP_SYSHUB_STRAP_SWREV_LSB22276
    2276,
    2,
    2,
    0x5D5DC,
  },
#endif

#ifdef SYSTEMHUB7_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES
#define
  {
    ///< SYSTEMHUB7_SYSTEMHUB_SSP_GENERIC_B_PUB_SPARE_FUSES2277
    2277,
    28,
    4,
    0x5D5DC,
  },
#endif

#ifdef THM_CCD_FUSE_SB_FIXED_ERRATA
#define
  {
    ///< THM_CCD_FUSE_SB_FIXED_ERRATA2278
    2278,
    8,
    30,
    0x1B87,
  },
#endif

#ifdef THM_CCD_FUSE_SB_IAI_DIS
#define
  {
    ///< THM_CCD_FUSE_SB_IAI_DIS2279
    2279,
    1,
    29,
    0x1B87,
  },
#endif

#ifdef THM_CCD_FUSE_SB_RMI_DIS
#define
  {
    ///< THM_CCD_FUSE_SB_RMI_DIS2280
    2280,
    1,
    28,
    0x1B87,
  },
#endif

#ifdef THM_CCD_FUSE_SB_TSI_DIS
#define
  {
    ///< THM_CCD_FUSE_SB_TSI_DIS2281
    2281,
    1,
    27,
    0x1B87,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_ARP_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_ARP_DIS2282
    2282,
    1,
    7,
    0x1B88,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_DIS2283
    2283,
    1,
    6,
    0x1B88,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_FILTER_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_FILTER_DIS2284
    2284,
    1,
    12,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS2285
    2285,
    1,
    10,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_NOTIFY_ARP_MST_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_NOTIFY_ARP_MST_DIS2286
    2286,
    1,
    11,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_THM_OVERRIDE_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_THM_OVERRIDE_DIS2287
    2287,
    1,
    8,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_THM_REG_ONLY
#define
  {
    ///< THM_CCD_FUSE_SMBUS_THM_REG_ONLY2288
    2288,
    1,
    9,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_DEVICE_ID
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_DEVICE_ID2289
    2289,
    16,
    14,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_MINOR_REV_ID
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_MINOR_REV_ID2290
    2290,
    4,
    30,
    0x1B8B,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_RAN_NUM_DIS
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_RAN_NUM_DIS2291
    2291,
    1,
    13,
    0x1B89,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_SUBSYS_ID
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_SUBSYS_ID2292
    2292,
    16,
    2,
    0x1B8C,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_SUBSYS_VEN_ID
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_SUBSYS_VEN_ID2293
    2293,
    16,
    18,
    0x1B8E,
  },
#endif

#ifdef THM_CCD_FUSE_SMBUS_UDID_VENDOR_ID
#define
  {
    ///< THM_CCD_FUSE_SMBUS_UDID_VENDOR_ID2294
    2294,
    1,
    2,
    0x1B90,
  },
#endif

#ifdef THM_CCD_FUSE_TconAtValue
#define
  {
    ///< THM_CCD_FUSE_TconAtValue2295
    2295,
    12,
    0,
    0x1B64,
  },
#endif

#ifdef THM_CCD_FUSE_TconBtValue
#define
  {
    ///< THM_CCD_FUSE_TconBtValue2296
    2296,
    6,
    13,
    0x1B65,
  },
#endif

#ifdef THM_CCD_FUSE_TconCtOffsetValue0
#define
  {
    ///< THM_CCD_FUSE_TconCtOffsetValue02297
    2297,
    11,
    9,
    0x1B69,
  },
#endif

#ifdef THM_CCD_FUSE_TconCtValue
#define
  {
    ///< THM_CCD_FUSE_TconCtValue2298
    2298,
    11,
    19,
    0x1B66,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0
#define
  {
    ///< THM_CCD_FUSE_TconDtValue02299
    2299,
    7,
    20,
    0x1B86,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l0
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l02300
    2300,
    7,
    20,
    0x1B6A,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l1
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l12301
    2301,
    7,
    27,
    0x1B6B,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l10
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l102302
    2302,
    7,
    26,
    0x1B73,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l11
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l112303
    2303,
    7,
    1,
    0x1B74,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l12
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l122304
    2304,
    7,
    8,
    0x1B75,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l13
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l132305
    2305,
    7,
    15,
    0x1B75,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l14
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l142306
    2306,
    7,
    22,
    0x1B76,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l15
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l152307
    2307,
    7,
    29,
    0x1B77,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l2
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l22308
    2308,
    7,
    2,
    0x1B6C,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l3
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l32309
    2309,
    7,
    9,
    0x1B6D,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l4
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l42310
    2310,
    7,
    16,
    0x1B6E,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l5
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l52311
    2311,
    7,
    23,
    0x1B6E,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l6
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l62312
    2312,
    7,
    30,
    0x1B6F,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l7
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l72313
    2313,
    7,
    5,
    0x1B70,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l8
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l82314
    2314,
    7,
    12,
    0x1B71,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0l9
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0l92315
    2315,
    7,
    19,
    0x1B72,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r0
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r02316
    2316,
    7,
    4,
    0x1B78,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r1
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r12317
    2317,
    7,
    11,
    0x1B79,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r10
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r102318
    2318,
    7,
    10,
    0x1B81,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r11
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r112319
    2319,
    7,
    17,
    0x1B82,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r12
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r122320
    2320,
    7,
    24,
    0x1B83,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r13
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r132321
    2321,
    7,
    31,
    0x1B83,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r14
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r142322
    2322,
    7,
    6,
    0x1B84,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r15
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r152323
    2323,
    7,
    13,
    0x1B85,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r2
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r22324
    2324,
    7,
    18,
    0x1B7A,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r3
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r32325
    2325,
    7,
    25,
    0x1B7B,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r4
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r42326
    2326,
    7,
    0,
    0x1B7C,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r5
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r52327
    2327,
    7,
    7,
    0x1B7C,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r6
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r62328
    2328,
    7,
    14,
    0x1B7D,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r7
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r72329
    2329,
    7,
    21,
    0x1B7E,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r8
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r82330
    2330,
    7,
    28,
    0x1B7F,
  },
#endif

#ifdef THM_CCD_FUSE_TconDtValue0r9
#define
  {
    ///< THM_CCD_FUSE_TconDtValue0r92331
    2331,
    7,
    3,
    0x1B80,
  },
#endif

#ifdef THM_CCD_FUSE_TconKValue
#define
  {
    ///< THM_CCD_FUSE_TconKValue2332
    2332,
    1,
    12,
    0x1B65,
  },
#endif

#ifdef THM_CCD_FUSE_TconTmpAdjLoRes
#define
  {
    ///< THM_CCD_FUSE_TconTmpAdjLoRes2333
    2333,
    1,
    10,
    0x1B5D,
  },
#endif

#ifdef THM_CCD_FUSE_TconUseSecondary
#define
  {
    ///< THM_CCD_FUSE_TconUseSecondary2334
    2334,
    2,
    11,
    0x1B5D,
  },
#endif

#ifdef THM_CCD_FUSE_TconZtValue
#define
  {
    ///< THM_CCD_FUSE_TconZtValue2335
    2335,
    11,
    30,
    0x1B67,
  },
#endif

#ifdef THM_CCD_FUSE_ThermTripEn
#define
  {
    ///< THM_CCD_FUSE_ThermTripEn2336
    2336,
    1,
    1,
    0x1B5C,
  },
#endif

#ifdef THM_CCD_FUSE_ThermTripLimit
#define
  {
    ///< THM_CCD_FUSE_ThermTripLimit2337
    2337,
    8,
    2,
    0x1B5C,
  },
#endif

#ifdef THM_CCD_FUSE_TmonBGAdj0
#define
  {
    ///< THM_CCD_FUSE_TmonBGAdj02338
    2338,
    8,
    23,
    0x1B62,
  },
#endif

#ifdef THM_CCD_FUSE_TmonClkDiv
#define
  {
    ///< THM_CCD_FUSE_TmonClkDiv2339
    2339,
    3,
    13,
    0x1B5D,
  },
#endif

#ifdef THM_CCD_FUSE_TmonForceMaxAcq
#define
  {
    ///< THM_CCD_FUSE_TmonForceMaxAcq2340
    2340,
    1,
    18,
    0x1B62,
  },
#endif

#ifdef THM_CCD_FUSE_TmonNumAcq
#define
  {
    ///< THM_CCD_FUSE_TmonNumAcq2341
    2341,
    3,
    19,
    0x1B62,
  },
#endif

#ifdef THM_CCD_FUSE_TmonReCalibEn
#define
  {
    ///< THM_CCD_FUSE_TmonReCalibEn2342
    2342,
    1,
    17,
    0x1B62,
  },
#endif

#ifdef THM_CCD_RDIL0_PRESENT
#define
  {
    ///< THM_CCD_RDIL0_PRESENT2343
    2343,
    16,
    16,
    0x1B5E,
  },
#endif

#ifdef THM_CCD_RDIR0_PRESENT
#define
  {
    ///< THM_CCD_RDIR0_PRESENT2344
    2344,
    16,
    0,
    0x1B60,
  },
#endif

#ifdef THM_CCD_THM_CCD_PUB_SPARE_FUSES
#define
  {
    ///< THM_CCD_THM_CCD_PUB_SPARE_FUSES2345
    2345,
    29,
    3,
    0x1B90,
  },
#endif

#ifdef THM_CCD_THM_CCD_WRITE_DISABLE
#define
  {
    ///< THM_CCD_THM_CCD_WRITE_DISABLE2346
    2346,
    1,
    0,
    0x1B5C,
  },
#endif

#ifdef THM_CCD_TMON_BGADJ_FUSE_SEL
#define
  {
    ///< THM_CCD_TMON_BGADJ_FUSE_SEL2347
    2347,
    1,
    22,
    0x1B62,
  },
#endif

#ifdef THM_CCD_TMON_COEFF_SOURCE
#define
  {
    ///< THM_CCD_TMON_COEFF_SOURCE2348
    2348,
    1,
    31,
    0x1B63,
  },
#endif

#ifdef THM_CCD_TMON_CONFIG_SOURCE
#define
  {
    ///< THM_CCD_TMON_CONFIG_SOURCE2349
    2349,
    1,
    16,
    0x1B62,
  },
#endif

#ifdef THM_FUSE_HtcDis
#define
  {
    ///< THM_FUSE_HtcDis2350
    2350,
    1,
    1,
    0x5D5E0,
  },
#endif

#ifdef THM_FUSE_HtcHystLmt
#define
  {
    ///< THM_FUSE_HtcHystLmt2351
    2351,
    4,
    2,
    0x5D5E0,
  },
#endif

#ifdef THM_FUSE_HtcMsrLock
#define
  {
    ///< THM_FUSE_HtcMsrLock2352
    2352,
    1,
    6,
    0x5D5E0,
  },
#endif

#ifdef THM_FUSE_HtcTmpLmt
#define
  {
    ///< THM_FUSE_HtcTmpLmt2353
    2353,
    7,
    7,
    0x5D5E0,
  },
#endif

#ifdef THM_FUSE_SB_FIXED_ERRATA
#define
  {
    ///< THM_FUSE_SB_FIXED_ERRATA2354
    2354,
    8,
    5,
    0x5D630,
  },
#endif

#ifdef THM_FUSE_SB_IAI_DIS
#define
  {
    ///< THM_FUSE_SB_IAI_DIS2355
    2355,
    1,
    4,
    0x5D630,
  },
#endif

#ifdef THM_FUSE_SB_RMI_DIS
#define
  {
    ///< THM_FUSE_SB_RMI_DIS2356
    2356,
    1,
    3,
    0x5D630,
  },
#endif

#ifdef THM_FUSE_SB_TSI_DIS
#define
  {
    ///< THM_FUSE_SB_TSI_DIS2357
    2357,
    1,
    2,
    0x5D630,
  },
#endif

#ifdef THM_FUSE_SMBUS_ARP_DIS
#define
  {
    ///< THM_FUSE_SMBUS_ARP_DIS2358
    2358,
    1,
    14,
    0x5D631,
  },
#endif

#ifdef THM_FUSE_SMBUS_DIS
#define
  {
    ///< THM_FUSE_SMBUS_DIS2359
    2359,
    1,
    13,
    0x5D631,
  },
#endif

#ifdef THM_FUSE_SMBUS_FILTER_DIS
#define
  {
    ///< THM_FUSE_SMBUS_FILTER_DIS2360
    2360,
    1,
    19,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS
#define
  {
    ///< THM_FUSE_SMBUS_HOLD_SMBCLK_LOW_DIS2361
    2361,
    1,
    17,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_NOTIFY_ARP_MST_DIS
#define
  {
    ///< THM_FUSE_SMBUS_NOTIFY_ARP_MST_DIS2362
    2362,
    1,
    18,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_THM_OVERRIDE_DIS
#define
  {
    ///< THM_FUSE_SMBUS_THM_OVERRIDE_DIS2363
    2363,
    1,
    15,
    0x5D631,
  },
#endif

#ifdef THM_FUSE_SMBUS_THM_REG_ONLY
#define
  {
    ///< THM_FUSE_SMBUS_THM_REG_ONLY2364
    2364,
    1,
    16,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_DEVICE_ID
#define
  {
    ///< THM_FUSE_SMBUS_UDID_DEVICE_ID2365
    2365,
    16,
    21,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_MINOR_REV_ID
#define
  {
    ///< THM_FUSE_SMBUS_UDID_MINOR_REV_ID2366
    2366,
    4,
    5,
    0x5D634,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_RAN_NUM_DIS
#define
  {
    ///< THM_FUSE_SMBUS_UDID_RAN_NUM_DIS2367
    2367,
    1,
    20,
    0x5D632,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_SUBSYS_ID
#define
  {
    ///< THM_FUSE_SMBUS_UDID_SUBSYS_ID2368
    2368,
    16,
    9,
    0x5D635,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_SUBSYS_VEN_ID
#define
  {
    ///< THM_FUSE_SMBUS_UDID_SUBSYS_VEN_ID2369
    2369,
    16,
    25,
    0x5D637,
  },
#endif

#ifdef THM_FUSE_SMBUS_UDID_VENDOR_ID
#define
  {
    ///< THM_FUSE_SMBUS_UDID_VENDOR_ID2370
    2370,
    1,
    9,
    0x5D639,
  },
#endif

#ifdef THM_FUSE_TconAtValue
#define
  {
    ///< THM_FUSE_TconAtValue2371
    2371,
    12,
    21,
    0x5D5EE,
  },
#endif

#ifdef THM_FUSE_TconBtValue
#define
  {
    ///< THM_FUSE_TconBtValue2372
    2372,
    6,
    2,
    0x5D5F0,
  },
#endif

#ifdef THM_FUSE_TconCtOffsetValue0
#define
  {
    ///< THM_FUSE_TconCtOffsetValue02373
    2373,
    11,
    30,
    0x5D5F3,
  },
#endif

#ifdef THM_FUSE_TconCtOffsetValue1
#define
  {
    ///< THM_FUSE_TconCtOffsetValue12374
    2374,
    11,
    9,
    0x5D5F5,
  },
#endif

#ifdef THM_FUSE_TconCtValue
#define
  {
    ///< THM_FUSE_TconCtValue2375
    2375,
    11,
    8,
    0x5D5F1,
  },
#endif

#ifdef THM_FUSE_TconDtValue0
#define
  {
    ///< THM_FUSE_TconDtValue02376
    2376,
    7,
    20,
    0x5D612,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l0
#define
  {
    ///< THM_FUSE_TconDtValue0l02377
    2377,
    7,
    20,
    0x5D5F6,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l1
#define
  {
    ///< THM_FUSE_TconDtValue0l12378
    2378,
    7,
    27,
    0x5D5F7,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l10
#define
  {
    ///< THM_FUSE_TconDtValue0l102379
    2379,
    7,
    26,
    0x5D5FF,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l11
#define
  {
    ///< THM_FUSE_TconDtValue0l112380
    2380,
    7,
    1,
    0x5D600,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l12
#define
  {
    ///< THM_FUSE_TconDtValue0l122381
    2381,
    7,
    8,
    0x5D601,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l13
#define
  {
    ///< THM_FUSE_TconDtValue0l132382
    2382,
    7,
    15,
    0x5D601,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l14
#define
  {
    ///< THM_FUSE_TconDtValue0l142383
    2383,
    7,
    22,
    0x5D602,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l15
#define
  {
    ///< THM_FUSE_TconDtValue0l152384
    2384,
    7,
    29,
    0x5D603,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l2
#define
  {
    ///< THM_FUSE_TconDtValue0l22385
    2385,
    7,
    2,
    0x5D5F8,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l3
#define
  {
    ///< THM_FUSE_TconDtValue0l32386
    2386,
    7,
    9,
    0x5D5F9,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l4
#define
  {
    ///< THM_FUSE_TconDtValue0l42387
    2387,
    7,
    16,
    0x5D5FA,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l5
#define
  {
    ///< THM_FUSE_TconDtValue0l52388
    2388,
    7,
    23,
    0x5D5FA,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l6
#define
  {
    ///< THM_FUSE_TconDtValue0l62389
    2389,
    7,
    30,
    0x5D5FB,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l7
#define
  {
    ///< THM_FUSE_TconDtValue0l72390
    2390,
    7,
    5,
    0x5D5FC,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l8
#define
  {
    ///< THM_FUSE_TconDtValue0l82391
    2391,
    7,
    12,
    0x5D5FD,
  },
#endif

#ifdef THM_FUSE_TconDtValue0l9
#define
  {
    ///< THM_FUSE_TconDtValue0l92392
    2392,
    7,
    19,
    0x5D5FE,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r0
#define
  {
    ///< THM_FUSE_TconDtValue0r02393
    2393,
    7,
    4,
    0x5D604,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r1
#define
  {
    ///< THM_FUSE_TconDtValue0r12394
    2394,
    7,
    11,
    0x5D605,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r10
#define
  {
    ///< THM_FUSE_TconDtValue0r102395
    2395,
    7,
    10,
    0x5D60D,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r11
#define
  {
    ///< THM_FUSE_TconDtValue0r112396
    2396,
    7,
    17,
    0x5D60E,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r12
#define
  {
    ///< THM_FUSE_TconDtValue0r122397
    2397,
    7,
    24,
    0x5D60F,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r13
#define
  {
    ///< THM_FUSE_TconDtValue0r132398
    2398,
    7,
    31,
    0x5D60F,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r14
#define
  {
    ///< THM_FUSE_TconDtValue0r142399
    2399,
    7,
    6,
    0x5D610,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r15
#define
  {
    ///< THM_FUSE_TconDtValue0r152400
    2400,
    7,
    13,
    0x5D611,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r2
#define
  {
    ///< THM_FUSE_TconDtValue0r22401
    2401,
    7,
    18,
    0x5D606,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r3
#define
  {
    ///< THM_FUSE_TconDtValue0r32402
    2402,
    7,
    25,
    0x5D607,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r4
#define
  {
    ///< THM_FUSE_TconDtValue0r42403
    2403,
    7,
    0,
    0x5D608,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r5
#define
  {
    ///< THM_FUSE_TconDtValue0r52404
    2404,
    7,
    7,
    0x5D608,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r6
#define
  {
    ///< THM_FUSE_TconDtValue0r62405
    2405,
    7,
    14,
    0x5D609,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r7
#define
  {
    ///< THM_FUSE_TconDtValue0r72406
    2406,
    7,
    21,
    0x5D60A,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r8
#define
  {
    ///< THM_FUSE_TconDtValue0r82407
    2407,
    7,
    28,
    0x5D60B,
  },
#endif

#ifdef THM_FUSE_TconDtValue0r9
#define
  {
    ///< THM_FUSE_TconDtValue0r92408
    2408,
    7,
    3,
    0x5D60C,
  },
#endif

#ifdef THM_FUSE_TconDtValue1
#define
  {
    ///< THM_FUSE_TconDtValue12409
    2409,
    7,
    27,
    0x5D62F,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l0
#define
  {
    ///< THM_FUSE_TconDtValue1l02410
    2410,
    7,
    27,
    0x5D613,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l1
#define
  {
    ///< THM_FUSE_TconDtValue1l12411
    2411,
    7,
    2,
    0x5D614,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l10
#define
  {
    ///< THM_FUSE_TconDtValue1l102412
    2412,
    7,
    1,
    0x5D61C,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l11
#define
  {
    ///< THM_FUSE_TconDtValue1l112413
    2413,
    7,
    8,
    0x5D61D,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l12
#define
  {
    ///< THM_FUSE_TconDtValue1l122414
    2414,
    7,
    15,
    0x5D61D,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l13
#define
  {
    ///< THM_FUSE_TconDtValue1l132415
    2415,
    7,
    22,
    0x5D61E,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l14
#define
  {
    ///< THM_FUSE_TconDtValue1l142416
    2416,
    7,
    29,
    0x5D61F,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l15
#define
  {
    ///< THM_FUSE_TconDtValue1l152417
    2417,
    7,
    4,
    0x5D620,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l2
#define
  {
    ///< THM_FUSE_TconDtValue1l22418
    2418,
    7,
    9,
    0x5D615,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l3
#define
  {
    ///< THM_FUSE_TconDtValue1l32419
    2419,
    7,
    16,
    0x5D616,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l4
#define
  {
    ///< THM_FUSE_TconDtValue1l42420
    2420,
    7,
    23,
    0x5D616,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l5
#define
  {
    ///< THM_FUSE_TconDtValue1l52421
    2421,
    7,
    30,
    0x5D617,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l6
#define
  {
    ///< THM_FUSE_TconDtValue1l62422
    2422,
    7,
    5,
    0x5D618,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l7
#define
  {
    ///< THM_FUSE_TconDtValue1l72423
    2423,
    7,
    12,
    0x5D619,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l8
#define
  {
    ///< THM_FUSE_TconDtValue1l82424
    2424,
    7,
    19,
    0x5D61A,
  },
#endif

#ifdef THM_FUSE_TconDtValue1l9
#define
  {
    ///< THM_FUSE_TconDtValue1l92425
    2425,
    7,
    26,
    0x5D61B,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r0
#define
  {
    ///< THM_FUSE_TconDtValue1r02426
    2426,
    7,
    11,
    0x5D621,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r1
#define
  {
    ///< THM_FUSE_TconDtValue1r12427
    2427,
    7,
    18,
    0x5D622,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r10
#define
  {
    ///< THM_FUSE_TconDtValue1r102428
    2428,
    7,
    17,
    0x5D62A,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r11
#define
  {
    ///< THM_FUSE_TconDtValue1r112429
    2429,
    7,
    24,
    0x5D62B,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r12
#define
  {
    ///< THM_FUSE_TconDtValue1r122430
    2430,
    7,
    31,
    0x5D62B,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r13
#define
  {
    ///< THM_FUSE_TconDtValue1r132431
    2431,
    7,
    6,
    0x5D62C,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r14
#define
  {
    ///< THM_FUSE_TconDtValue1r142432
    2432,
    7,
    13,
    0x5D62D,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r15
#define
  {
    ///< THM_FUSE_TconDtValue1r152433
    2433,
    7,
    20,
    0x5D62E,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r2
#define
  {
    ///< THM_FUSE_TconDtValue1r22434
    2434,
    7,
    25,
    0x5D623,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r3
#define
  {
    ///< THM_FUSE_TconDtValue1r32435
    2435,
    7,
    0,
    0x5D624,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r4
#define
  {
    ///< THM_FUSE_TconDtValue1r42436
    2436,
    7,
    7,
    0x5D624,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r5
#define
  {
    ///< THM_FUSE_TconDtValue1r52437
    2437,
    7,
    14,
    0x5D625,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r6
#define
  {
    ///< THM_FUSE_TconDtValue1r62438
    2438,
    7,
    21,
    0x5D626,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r7
#define
  {
    ///< THM_FUSE_TconDtValue1r72439
    2439,
    7,
    28,
    0x5D627,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r8
#define
  {
    ///< THM_FUSE_TconDtValue1r82440
    2440,
    7,
    3,
    0x5D628,
  },
#endif

#ifdef THM_FUSE_TconDtValue1r9
#define
  {
    ///< THM_FUSE_TconDtValue1r92441
    2441,
    7,
    10,
    0x5D629,
  },
#endif

#ifdef THM_FUSE_TconKValue
#define
  {
    ///< THM_FUSE_TconKValue2442
    2442,
    1,
    1,
    0x5D5F0,
  },
#endif

#ifdef THM_FUSE_TconTmpAdjLoRes
#define
  {
    ///< THM_FUSE_TconTmpAdjLoRes2443
    2443,
    1,
    23,
    0x5D5E2,
  },
#endif

#ifdef THM_FUSE_TconUseSecondary
#define
  {
    ///< THM_FUSE_TconUseSecondary2444
    2444,
    2,
    24,
    0x5D5E3,
  },
#endif

#ifdef THM_FUSE_TconZtValue
#define
  {
    ///< THM_FUSE_TconZtValue2445
    2445,
    11,
    19,
    0x5D5F2,
  },
#endif

#ifdef THM_FUSE_ThermTripEn
#define
  {
    ///< THM_FUSE_ThermTripEn2446
    2446,
    1,
    14,
    0x5D5E1,
  },
#endif

#ifdef THM_FUSE_ThermTripLimit
#define
  {
    ///< THM_FUSE_ThermTripLimit2447
    2447,
    8,
    15,
    0x5D5E1,
  },
#endif

#ifdef THM_FUSE_TmonBGAdj0
#define
  {
    ///< THM_FUSE_TmonBGAdj02448
    2448,
    8,
    4,
    0x5D5EC,
  },
#endif

#ifdef THM_FUSE_TmonBGAdj1
#define
  {
    ///< THM_FUSE_TmonBGAdj12449
    2449,
    8,
    12,
    0x5D5ED,
  },
#endif

#ifdef THM_FUSE_TmonClkDiv
#define
  {
    ///< THM_FUSE_TmonClkDiv2450
    2450,
    3,
    26,
    0x5D5E3,
  },
#endif

#ifdef THM_FUSE_TmonForceMaxAcq
#define
  {
    ///< THM_FUSE_TmonForceMaxAcq2451
    2451,
    1,
    31,
    0x5D5EB,
  },
#endif

#ifdef THM_FUSE_TmonNumAcq
#define
  {
    ///< THM_FUSE_TmonNumAcq2452
    2452,
    3,
    0,
    0x5D5EC,
  },
#endif

#ifdef THM_FUSE_TmonReCalibEn
#define
  {
    ///< THM_FUSE_TmonReCalibEn2453
    2453,
    1,
    30,
    0x5D5EB,
  },
#endif

#ifdef THM_RDIL0_PRESENT
#define
  {
    ///< THM_RDIL0_PRESENT2454
    2454,
    16,
    29,
    0x5D5E3,
  },
#endif

#ifdef THM_RDIL1_PRESENT
#define
  {
    ///< THM_RDIL1_PRESENT2455
    2455,
    16,
    29,
    0x5D5E7,
  },
#endif

#ifdef THM_RDIR0_PRESENT
#define
  {
    ///< THM_RDIR0_PRESENT2456
    2456,
    16,
    13,
    0x5D5E5,
  },
#endif

#ifdef THM_RDIR1_PRESENT
#define
  {
    ///< THM_RDIR1_PRESENT2457
    2457,
    16,
    13,
    0x5D5E9,
  },
#endif

#ifdef THM_THM_PUB_SPARE_FUSES
#define
  {
    ///< THM_THM_PUB_SPARE_FUSES2458
    2458,
    22,
    10,
    0x5D639,
  },
#endif

#ifdef THM_THM_WRITE_DISABLE
#define
  {
    ///< THM_THM_WRITE_DISABLE2459
    2459,
    1,
    0,
    0x5D5E0,
  },
#endif

#ifdef THM_TMON_BGADJ_FUSE_SEL
#define
  {
    ///< THM_TMON_BGADJ_FUSE_SEL2460
    2460,
    1,
    3,
    0x5D5EC,
  },
#endif

#ifdef THM_TMON_COEFF_SOURCE
#define
  {
    ///< THM_TMON_COEFF_SOURCE2461
    2461,
    1,
    20,
    0x5D5EE,
  },
#endif

#ifdef THM_TMON_CONFIG_SOURCE
#define
  {
    ///< THM_TMON_CONFIG_SOURCE2462
    2462,
    1,
    29,
    0x5D5EB,
  },
#endif

#ifdef UMC0_FUSE_DdrMaxRate
#define
  {
    ///< UMC0_FUSE_DdrMaxRate2463
    2463,
    8,
    1,
    0x5D63C,
  },
#endif

#ifdef UMC0_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC0_FUSE_DdrMaxRateEnf2464
    2464,
    8,
    9,
    0x5D63D,
  },
#endif

#ifdef UMC0_FUSE_DramTypeDis
#define
  {
    ///< UMC0_FUSE_DramTypeDis2465
    2465,
    8,
    19,
    0x5D63E,
  },
#endif

#ifdef UMC0_FUSE_EccDis
#define
  {
    ///< UMC0_FUSE_EccDis2466
    2466,
    1,
    17,
    0x5D63E,
  },
#endif

#ifdef UMC0_FUSE_EncryptionDis
#define
  {
    ///< UMC0_FUSE_EncryptionDis2467
    2467,
    1,
    27,
    0x5D63F,
  },
#endif

#ifdef UMC0_FUSE_MemChanDis
#define
  {
    ///< UMC0_FUSE_MemChanDis2468
    2468,
    1,
    18,
    0x5D63E,
  },
#endif

#ifdef UMC0_FUSE_RegDimmDis
#define
  {
    ///< UMC0_FUSE_RegDimmDis2469
    2469,
    1,
    0,
    0x5D63C,
  },
#endif

#ifdef UMC0_FUSE_Spare_UMC
#define
  {
    ///< UMC0_FUSE_Spare_UMC2470
    2470,
    3,
    28,
    0x5D63F,
  },
#endif

#ifdef UMC0_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC0_UMC_PUB_SPARE_FUSES2471
    2471,
    1,
    31,
    0x5D63F,
  },
#endif

#ifdef UMC1_FUSE_DdrMaxRate
#define
  {
    ///< UMC1_FUSE_DdrMaxRate2472
    2472,
    8,
    1,
    0x5D640,
  },
#endif

#ifdef UMC1_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC1_FUSE_DdrMaxRateEnf2473
    2473,
    8,
    9,
    0x5D641,
  },
#endif

#ifdef UMC1_FUSE_DramTypeDis
#define
  {
    ///< UMC1_FUSE_DramTypeDis2474
    2474,
    8,
    19,
    0x5D642,
  },
#endif

#ifdef UMC1_FUSE_EccDis
#define
  {
    ///< UMC1_FUSE_EccDis2475
    2475,
    1,
    17,
    0x5D642,
  },
#endif

#ifdef UMC1_FUSE_EncryptionDis
#define
  {
    ///< UMC1_FUSE_EncryptionDis2476
    2476,
    1,
    27,
    0x5D643,
  },
#endif

#ifdef UMC1_FUSE_MemChanDis
#define
  {
    ///< UMC1_FUSE_MemChanDis2477
    2477,
    1,
    18,
    0x5D642,
  },
#endif

#ifdef UMC1_FUSE_RegDimmDis
#define
  {
    ///< UMC1_FUSE_RegDimmDis2478
    2478,
    1,
    0,
    0x5D640,
  },
#endif

#ifdef UMC1_FUSE_Spare_UMC
#define
  {
    ///< UMC1_FUSE_Spare_UMC2479
    2479,
    3,
    28,
    0x5D643,
  },
#endif

#ifdef UMC1_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC1_UMC_PUB_SPARE_FUSES2480
    2480,
    1,
    31,
    0x5D643,
  },
#endif

#ifdef UMC2_FUSE_DdrMaxRate
#define
  {
    ///< UMC2_FUSE_DdrMaxRate2481
    2481,
    8,
    1,
    0x5D644,
  },
#endif

#ifdef UMC2_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC2_FUSE_DdrMaxRateEnf2482
    2482,
    8,
    9,
    0x5D645,
  },
#endif

#ifdef UMC2_FUSE_DramTypeDis
#define
  {
    ///< UMC2_FUSE_DramTypeDis2483
    2483,
    8,
    19,
    0x5D646,
  },
#endif

#ifdef UMC2_FUSE_EccDis
#define
  {
    ///< UMC2_FUSE_EccDis2484
    2484,
    1,
    17,
    0x5D646,
  },
#endif

#ifdef UMC2_FUSE_EncryptionDis
#define
  {
    ///< UMC2_FUSE_EncryptionDis2485
    2485,
    1,
    27,
    0x5D647,
  },
#endif

#ifdef UMC2_FUSE_MemChanDis
#define
  {
    ///< UMC2_FUSE_MemChanDis2486
    2486,
    1,
    18,
    0x5D646,
  },
#endif

#ifdef UMC2_FUSE_RegDimmDis
#define
  {
    ///< UMC2_FUSE_RegDimmDis2487
    2487,
    1,
    0,
    0x5D644,
  },
#endif

#ifdef UMC2_FUSE_Spare_UMC
#define
  {
    ///< UMC2_FUSE_Spare_UMC2488
    2488,
    3,
    28,
    0x5D647,
  },
#endif

#ifdef UMC2_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC2_UMC_PUB_SPARE_FUSES2489
    2489,
    1,
    31,
    0x5D647,
  },
#endif

#ifdef UMC3_FUSE_DdrMaxRate
#define
  {
    ///< UMC3_FUSE_DdrMaxRate2490
    2490,
    8,
    1,
    0x5D648,
  },
#endif

#ifdef UMC3_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC3_FUSE_DdrMaxRateEnf2491
    2491,
    8,
    9,
    0x5D649,
  },
#endif

#ifdef UMC3_FUSE_DramTypeDis
#define
  {
    ///< UMC3_FUSE_DramTypeDis2492
    2492,
    8,
    19,
    0x5D64A,
  },
#endif

#ifdef UMC3_FUSE_EccDis
#define
  {
    ///< UMC3_FUSE_EccDis2493
    2493,
    1,
    17,
    0x5D64A,
  },
#endif

#ifdef UMC3_FUSE_EncryptionDis
#define
  {
    ///< UMC3_FUSE_EncryptionDis2494
    2494,
    1,
    27,
    0x5D64B,
  },
#endif

#ifdef UMC3_FUSE_MemChanDis
#define
  {
    ///< UMC3_FUSE_MemChanDis2495
    2495,
    1,
    18,
    0x5D64A,
  },
#endif

#ifdef UMC3_FUSE_RegDimmDis
#define
  {
    ///< UMC3_FUSE_RegDimmDis2496
    2496,
    1,
    0,
    0x5D648,
  },
#endif

#ifdef UMC3_FUSE_Spare_UMC
#define
  {
    ///< UMC3_FUSE_Spare_UMC2497
    2497,
    3,
    28,
    0x5D64B,
  },
#endif

#ifdef UMC3_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC3_UMC_PUB_SPARE_FUSES2498
    2498,
    1,
    31,
    0x5D64B,
  },
#endif

#ifdef UMC4_FUSE_DdrMaxRate
#define
  {
    ///< UMC4_FUSE_DdrMaxRate2499
    2499,
    8,
    1,
    0x5D64C,
  },
#endif

#ifdef UMC4_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC4_FUSE_DdrMaxRateEnf2500
    2500,
    8,
    9,
    0x5D64D,
  },
#endif

#ifdef UMC4_FUSE_DramTypeDis
#define
  {
    ///< UMC4_FUSE_DramTypeDis2501
    2501,
    8,
    19,
    0x5D64E,
  },
#endif

#ifdef UMC4_FUSE_EccDis
#define
  {
    ///< UMC4_FUSE_EccDis2502
    2502,
    1,
    17,
    0x5D64E,
  },
#endif

#ifdef UMC4_FUSE_EncryptionDis
#define
  {
    ///< UMC4_FUSE_EncryptionDis2503
    2503,
    1,
    27,
    0x5D64F,
  },
#endif

#ifdef UMC4_FUSE_MemChanDis
#define
  {
    ///< UMC4_FUSE_MemChanDis2504
    2504,
    1,
    18,
    0x5D64E,
  },
#endif

#ifdef UMC4_FUSE_RegDimmDis
#define
  {
    ///< UMC4_FUSE_RegDimmDis2505
    2505,
    1,
    0,
    0x5D64C,
  },
#endif

#ifdef UMC4_FUSE_Spare_UMC
#define
  {
    ///< UMC4_FUSE_Spare_UMC2506
    2506,
    3,
    28,
    0x5D64F,
  },
#endif

#ifdef UMC4_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC4_UMC_PUB_SPARE_FUSES2507
    2507,
    1,
    31,
    0x5D64F,
  },
#endif

#ifdef UMC5_FUSE_DdrMaxRate
#define
  {
    ///< UMC5_FUSE_DdrMaxRate2508
    2508,
    8,
    1,
    0x5D650,
  },
#endif

#ifdef UMC5_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC5_FUSE_DdrMaxRateEnf2509
    2509,
    8,
    9,
    0x5D651,
  },
#endif

#ifdef UMC5_FUSE_DramTypeDis
#define
  {
    ///< UMC5_FUSE_DramTypeDis2510
    2510,
    8,
    19,
    0x5D652,
  },
#endif

#ifdef UMC5_FUSE_EccDis
#define
  {
    ///< UMC5_FUSE_EccDis2511
    2511,
    1,
    17,
    0x5D652,
  },
#endif

#ifdef UMC5_FUSE_EncryptionDis
#define
  {
    ///< UMC5_FUSE_EncryptionDis2512
    2512,
    1,
    27,
    0x5D653,
  },
#endif

#ifdef UMC5_FUSE_MemChanDis
#define
  {
    ///< UMC5_FUSE_MemChanDis2513
    2513,
    1,
    18,
    0x5D652,
  },
#endif

#ifdef UMC5_FUSE_RegDimmDis
#define
  {
    ///< UMC5_FUSE_RegDimmDis2514
    2514,
    1,
    0,
    0x5D650,
  },
#endif

#ifdef UMC5_FUSE_Spare_UMC
#define
  {
    ///< UMC5_FUSE_Spare_UMC2515
    2515,
    3,
    28,
    0x5D653,
  },
#endif

#ifdef UMC5_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC5_UMC_PUB_SPARE_FUSES2516
    2516,
    1,
    31,
    0x5D653,
  },
#endif

#ifdef UMC6_FUSE_DdrMaxRate
#define
  {
    ///< UMC6_FUSE_DdrMaxRate2517
    2517,
    8,
    1,
    0x5D654,
  },
#endif

#ifdef UMC6_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC6_FUSE_DdrMaxRateEnf2518
    2518,
    8,
    9,
    0x5D655,
  },
#endif

#ifdef UMC6_FUSE_DramTypeDis
#define
  {
    ///< UMC6_FUSE_DramTypeDis2519
    2519,
    8,
    19,
    0x5D656,
  },
#endif

#ifdef UMC6_FUSE_EccDis
#define
  {
    ///< UMC6_FUSE_EccDis2520
    2520,
    1,
    17,
    0x5D656,
  },
#endif

#ifdef UMC6_FUSE_EncryptionDis
#define
  {
    ///< UMC6_FUSE_EncryptionDis2521
    2521,
    1,
    27,
    0x5D657,
  },
#endif

#ifdef UMC6_FUSE_MemChanDis
#define
  {
    ///< UMC6_FUSE_MemChanDis2522
    2522,
    1,
    18,
    0x5D656,
  },
#endif

#ifdef UMC6_FUSE_RegDimmDis
#define
  {
    ///< UMC6_FUSE_RegDimmDis2523
    2523,
    1,
    0,
    0x5D654,
  },
#endif

#ifdef UMC6_FUSE_Spare_UMC
#define
  {
    ///< UMC6_FUSE_Spare_UMC2524
    2524,
    3,
    28,
    0x5D657,
  },
#endif

#ifdef UMC6_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC6_UMC_PUB_SPARE_FUSES2525
    2525,
    1,
    31,
    0x5D657,
  },
#endif

#ifdef UMC7_FUSE_DdrMaxRate
#define
  {
    ///< UMC7_FUSE_DdrMaxRate2526
    2526,
    8,
    1,
    0x5D658,
  },
#endif

#ifdef UMC7_FUSE_DdrMaxRateEnf
#define
  {
    ///< UMC7_FUSE_DdrMaxRateEnf2527
    2527,
    8,
    9,
    0x5D659,
  },
#endif

#ifdef UMC7_FUSE_DramTypeDis
#define
  {
    ///< UMC7_FUSE_DramTypeDis2528
    2528,
    8,
    19,
    0x5D65A,
  },
#endif

#ifdef UMC7_FUSE_EccDis
#define
  {
    ///< UMC7_FUSE_EccDis2529
    2529,
    1,
    17,
    0x5D65A,
  },
#endif

#ifdef UMC7_FUSE_EncryptionDis
#define
  {
    ///< UMC7_FUSE_EncryptionDis2530
    2530,
    1,
    27,
    0x5D65B,
  },
#endif

#ifdef UMC7_FUSE_MemChanDis
#define
  {
    ///< UMC7_FUSE_MemChanDis2531
    2531,
    1,
    18,
    0x5D65A,
  },
#endif

#ifdef UMC7_FUSE_RegDimmDis
#define
  {
    ///< UMC7_FUSE_RegDimmDis2532
    2532,
    1,
    0,
    0x5D658,
  },
#endif

#ifdef UMC7_FUSE_Spare_UMC
#define
  {
    ///< UMC7_FUSE_Spare_UMC2533
    2533,
    3,
    28,
    0x5D65B,
  },
#endif

#ifdef UMC7_UMC_PUB_SPARE_FUSES
#define
  {
    ///< UMC7_UMC_PUB_SPARE_FUSES2534
    2534,
    1,
    31,
    0x5D65B,
  },
#endif

#ifdef USB0_USB0_GROUP0_DATA
#define
  {
    ///< USB0_USB0_GROUP0_DATA2535
    2535,
    96,
    0,
    0x5D888,
  },
#endif

#ifdef USB0_USB_0_WRITE_DISABLE
#define
  {
    ///< USB0_USB_0_WRITE_DISABLE2536
    2536,
    1,
    31,
    0x5D66B,
  },
#endif

#ifdef USB0_usb_fuse
#define
  {
    ///< USB0_usb_fuse2537
    2537,
    127,
    0,
    0x5D65C,
  },
#endif

#ifdef USB1_USB1_GROUP0_DATA
#define
  {
    ///< USB1_USB1_GROUP0_DATA2538
    2538,
    96,
    0,
    0x5D894,
  },
#endif

#ifdef USB1_USB_0_WRITE_DISABLE
#define
  {
    ///< USB1_USB_0_WRITE_DISABLE2539
    2539,
    1,
    31,
    0x5D67B,
  },
#endif

#ifdef USB1_usb_fuse
#define
  {
    ///< USB1_usb_fuse2540
    2540,
    127,
    0,
    0x5D66C,
  },
#endif

#ifdef VHC_FUSE_REPAIR_Spare_Repair
#define
  {
    ///< VHC_FUSE_REPAIR_Spare_Repair2541
    2541,
    608,
    0,
    0x1BB4,
  },
#endif

#ifdef VHC_RESERVED_N_reserved_0
#define
  {
    ///< VHC_RESERVED_N_reserved_02542
    2542,
    32,
    0,
    0x1B94,
  },
#endif

#ifdef VHC_RESERVED_N_reserved_1
#define
  {
    ///< VHC_RESERVED_N_reserved_12543
    2543,
    32,
    0,
    0x1B98,
  },
#endif

#ifdef VHC_RESERVED_N_reserved_2
#define
  {
    ///< VHC_RESERVED_N_reserved_22544
    2544,
    32,
    0,
    0x1B9C,
  },
#endif

#ifdef WAFL_PCS_EFUSE1_HWINIT_DisableFunc
#define
  {
    ///< WAFL_PCS_EFUSE1_HWINIT_DisableFunc2545
    2545,
    1,
    1,
    0x5D680,
  },
#endif

#ifdef WAFL_PCS_EFUSE1_HWINIT_ReadySerBypass
#define
  {
    ///< WAFL_PCS_EFUSE1_HWINIT_ReadySerBypass2546
    2546,
    1,
    2,
    0x5D680,
  },
#endif

#ifdef WAFL_PCS_EFUSE1_HWINIT_WriteDis
#define
  {
    ///< WAFL_PCS_EFUSE1_HWINIT_WriteDis2547
    2547,
    1,
    0,
    0x5D680,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_0
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_02548
    2548,
    22,
    0,
    0x5D69C,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_1
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_12549
    2549,
    22,
    22,
    0x5D69E,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_10
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_102550
    2550,
    22,
    28,
    0x5D6B7,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_11
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_112551
    2551,
    22,
    18,
    0x5D6BA,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_12
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_122552
    2552,
    22,
    8,
    0x5D6BD,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_13
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_132553
    2553,
    22,
    30,
    0x5D6BF,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_14
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_142554
    2554,
    22,
    20,
    0x5D6C2,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_15
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_152555
    2555,
    22,
    10,
    0x5D6C5,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_16
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_162556
    2556,
    22,
    0,
    0x5D6C8,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_17
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_172557
    2557,
    22,
    22,
    0x5D6CA,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_18
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_182558
    2558,
    22,
    12,
    0x5D6CD,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_19
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_192559
    2559,
    22,
    2,
    0x5D6D0,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_2
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_22560
    2560,
    22,
    12,
    0x5D6A1,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_20
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_202561
    2561,
    22,
    24,
    0x5D6D3,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_21
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_212562
    2562,
    22,
    14,
    0x5D6D5,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_22
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_222563
    2563,
    22,
    4,
    0x5D6D8,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_23
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_232564
    2564,
    22,
    26,
    0x5D6DB,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_24
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_242565
    2565,
    22,
    16,
    0x5D6DE,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_25
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_252566
    2566,
    22,
    6,
    0x5D6E0,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_26
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_262567
    2567,
    22,
    28,
    0x5D6E3,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_27
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_272568
    2568,
    22,
    18,
    0x5D6E6,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_28
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_282569
    2569,
    22,
    8,
    0x5D6E9,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_29
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_292570
    2570,
    22,
    30,
    0x5D6EB,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_3
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_32571
    2571,
    22,
    2,
    0x5D6A4,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_30
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_302572
    2572,
    22,
    20,
    0x5D6EE,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_31
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_312573
    2573,
    22,
    10,
    0x5D6F1,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_4
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_42574
    2574,
    22,
    24,
    0x5D6A7,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_5
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_52575
    2575,
    22,
    14,
    0x5D6A9,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_6
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_62576
    2576,
    22,
    4,
    0x5D6AC,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_7
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_72577
    2577,
    22,
    26,
    0x5D6AF,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_8
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_82578
    2578,
    22,
    16,
    0x5D6B2,
  },
#endif

#ifdef WAFL_PCS_FUSE_ANALOG_9
#define
  {
    ///< WAFL_PCS_FUSE_ANALOG_92579
    2579,
    22,
    6,
    0x5D6B4,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse0
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse02580
    2580,
    16,
    0,
    0x5D684,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse10
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse102581
    2581,
    16,
    16,
    0x5D68E,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse2
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse22582
    2582,
    16,
    16,
    0x5D686,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse4
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse42583
    2583,
    16,
    0,
    0x5D688,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse6
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse62584
    2584,
    16,
    16,
    0x5D68A,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHY0_seq_fuse8
#define
  {
    ///< WAFL_PCS_FUSE_PHY0_seq_fuse82585
    2585,
    16,
    0,
    0x5D68C,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse0
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse02586
    2586,
    16,
    0,
    0x5D690,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse10
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse102587
    2587,
    16,
    16,
    0x5D69A,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse2
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse22588
    2588,
    16,
    16,
    0x5D692,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse4
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse42589
    2589,
    16,
    0,
    0x5D694,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse6
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse62590
    2590,
    16,
    16,
    0x5D696,
  },
#endif

#ifdef WAFL_PCS_FUSE_PHYN_seq_fuse8
#define
  {
    ///< WAFL_PCS_FUSE_PHYN_seq_fuse82591
    2591,
    16,
    0,
    0x5D698,
  },
#endif

#ifdef WAFL_PCS_GOPX1_PCS_EFUSE1
#define
  {
    ///< WAFL_PCS_GOPX1_PCS_EFUSE12592
    2592,
    29,
    3,
    0x5D680,
  },
#endif

#ifdef WAFL_PCS_GOPX1_PCS_HINIT_HWinitComplete
#define
  {
    ///< WAFL_PCS_GOPX1_PCS_HINIT_HWinitComplete2593
    2593,
    1,
    0,
    0x5D67C,
  },
#endif

#ifdef WAFL_PCS_PCS_HINIT
#define
  {
    ///< WAFL_PCS_PCS_HINIT2594
    2594,
    31,
    1,
    0x5D67C,
  },
#endif
  {
    ///< END OF LIST
    0xFFFF,
    0,
    0,
    0x00000,
  }
};

#endif /* _AMD_FUSES_SSP_H_ */
