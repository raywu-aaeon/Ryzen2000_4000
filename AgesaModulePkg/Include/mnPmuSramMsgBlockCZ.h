/* $NoKeywords:$ */
/**
 * @file
 *
 * mnPmuSramMsgBlockCZ.h
 *
 * PMU SRAM Message Block related function for CZ.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
 *
 **/
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
*
*/

#ifndef _MNPMUSRAMMSGBLOCKCZ_H_
#define _MNPMUSRAMMSGBLOCKCZ_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

//
// The size and the order of the structure and its members is very important.
// The structure maps directly from PMU SRAM Message Block table in the CZ BKDG.
//

/// DDR3 Unbuffered PMU SRAM Message Block Annex for DDR3 Unbuffered
typedef struct _PMU_SMB_DDR3U_CZ {
  IN     UINT16    M0_MR0;         ///< Location 21h:20h,
  IN     UINT16    M0_MR1;         ///< Location 23h:22h,
  IN     UINT16    M0_MR2;         ///< Location 25h:24h,
  IN     UINT8     Reserved26;     ///< Location 26h,
  IN     UINT8     Reserved27;     ///< Location 27h,
  IN     UINT8     Reserved28;     ///< Location 28h,
  IN     UINT8     Reserved29;     ///< Location 29h,
  IN     UINT8     Reserved2A;     ///< Location 2Ah,
  IN     UINT8     Reserved2B;     ///< Location 2Bh,
  IN     UINT8     Reserved2C;     ///< Location 2Ch,
  IN     UINT8     Reserved2D;     ///< Location 2Dh,
  IN     UINT8     Reserved2E;     ///< Location 2Eh,
  IN     UINT8     Reserved2F;     ///< Location 2Fh,
  IN     UINT16    M1_MR0;         ///< Location 31h:30h,
  IN     UINT16    M1_MR1;         ///< Location 33h:32h,
  IN     UINT16    M1_MR2;         ///< Location 35h:34h,
  IN     UINT8     M1CkeSetup;     ///< Location 36h, M1 Cke Setup. See M0CkeSetup
  IN     UINT8     M1CsOdtSetup;   ///< Location 37h, M1 CsOdtSetup. See M0CkeSetup
  IN     UINT8     M1AddrCmdSetup; ///< Location 38h, M1 AddrCmdSetup. See M0CkeSetup.
  OUT    UINT8     M1_CD_R_W;      ///< Location 39h, M1 State Read to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_R_R;      ///< Location 3Ah, M1 State Read to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_W_W;      ///< Location 3Bh, M1 State Write to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_W_R;      ///< Location 3Ch, M1 State Write to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_R_R_SD;   ///< Location 3Dh, M1 State Read to Read Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  OUT    UINT8     M1_CD_W_W_SD;   ///< Location 3Eh, M1 State Write to Write Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  IN     UINT8     Reserved3F;     ///< Location 3Fh,
} PMU_SMB_DDR3U_CZ;

/*
/// DDR3 RDIMM PMU SRAM Message Block Annex for DDR3 RDIMM
typedef struct _PMU_SMB_DDR3R_CZ {
  IN     UINT16    M0_MR0;          ///< Location 21h:20h,
  IN     UINT16    M0_MR1;          ///< Location 23h:22h,
  IN     UINT16    M0_MR2;          ///< Location 25h:24h,
  IN     UINT8     Reserved26;      ///< Location 26h,
  IN     UINT8     Reserved27;      ///< Location 27h,
  IN     UINT8     SR_Rtt;          ///< Location 28h, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     DR_Rtt_R0;       ///< Location 29h, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     DR_Rtt_R1;       ///< Location 2Ah, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     QR_Rtt_R0;       ///< Location 2Bh, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     QR_Rtt_R1;       ///< Location 2Ch, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     QR_Rtt_R2;       ///< Location 2Dh, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     QR_Rtt_R3;       ///< Location 2Eh, {00b, RTT_WR[1:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     Reserved2F;      ///< Location 2Fh,
  IN     UINT8     Dimm0_RC1_RC0;   ///< Location 30h, RDIMM0 RCWs
  IN     UINT8     Dimm0_RC3_RC2;   ///< Location 31h,
  IN     UINT8     Dimm0_RC5_RC4;   ///< Location 32h,
  IN     UINT8     Dimm0_RC7_RC6;   ///< Location 33h,
  IN     UINT8     Dimm0_RC9_RC8;   ///< Location 34h,
  IN     UINT8     Dimm0_RC11_RC10; ///< Location 35h,
  IN     UINT8     Dimm0_RC13_RC12; ///< Location 36h,
  IN     UINT8     Dimm0_RC15_RC14; ///< Location 37h,
  IN     UINT8     Dimm1_RC1_RC0;   ///< Location 38h, RDIMM1 RCWs
  IN     UINT8     Dimm1_RC3_RC2;   ///< Location 39h,
  IN     UINT8     Dimm1_RC5_RC4;   ///< Location 3Ah,
  IN     UINT8     Dimm1_RC7_RC6;   ///< Location 3Bh,
  IN     UINT8     Dimm1_RC9_RC8;   ///< Location 3Ch,
  IN     UINT8     Dimm1_RC11_RC10; ///< Location 3Dh,
  IN     UINT8     Dimm1_RC13_RC12; ///< Location 3Eh,
  IN     UINT8     Dimm1_RC15_RC14; ///< Location 3Fh,
  IN     UINT8     Dimm2_RC1_RC0;   ///< Location 40h, RDIMM2 RCWs
  IN     UINT8     Dimm2_RC3_RC2;   ///< Location 41h,
  IN     UINT8     Dimm2_RC5_RC4;   ///< Location 42h,
  IN     UINT8     Dimm2_RC7_RC6;   ///< Location 43h,
  IN     UINT8     Dimm2_RC9_RC8;   ///< Location 44h,
  IN     UINT8     Dimm2_RC11_RC10; ///< Location 45h,
  IN     UINT8     Dimm2_RC13_RC12; ///< Location 46h,
  IN     UINT8     Dimm2_RC15_RC14; ///< Location 47h,
} PMU_SMB_DDR3R_CZ;

/// DDR3 LRDIMM PMU SRAM Message Block Annex for DDR3 LRDIMM
typedef struct _PMU_SMB_DDR3L_CZ {
  IN     UINT16    M0_MR0;             ///< Location 21h:20h,
  IN     UINT16    M0_MR1;             ///< Location 23h:22h,
  IN     UINT16    M0_MR2;             ///< Location 25h:24h,
  IN     UINT8     Reserved26;         ///< Location 26h,
  IN     UINT8     Reserved27;         ///< Location 27h,
  IN     UINT8     SR_RTT;             ///< Location 28h, {0b, RTT_WR[2:0], 0b, RTT_NOM[2:0]}
  IN     UINT8     Reserved29;         ///< Location 29h,
  IN     UINT8     Reserved2A;         ///< Location 2Ah,
  IN     UINT8     Reserved2B;         ///< Location 2Bh,
  IN     UINT8     Reserved2C;         ///< Location 2Ch,
  IN     UINT8     Reserved2D;         ///< Location 2Dh,
  IN     UINT8     Reserved2E;         ///< Location 2Eh,
  IN     UINT8     Reserved2F;         ///< Location 2Fh,
  IN     UINT8     Dimm0_F0RC1_RC0;    ///< Location 30h, Buffer RCWs
  IN     UINT8     Dimm0_F0RC3_RC2;    ///< Location 31h,
  IN     UINT8     Dimm0_F0RC5_RC4;    ///< Location 32h,
  IN     UINT8     Dimm0_F0RC7_RC6;    ///< Location 33h,
  IN     UINT8     Dimm0_F0RC9_RC8;    ///< Location 34h,
  IN     UINT8     Dimm0_F0RC11_RC10;  ///< Location 35h,
  IN     UINT8     Dimm0_F0RC13_RC12;  ///< Location 36h,
  IN     UINT8     Dimm0_F0RC15_RC14;  ///< Location 37h,
  IN     UINT8     Dimm0_F1RC1_RC0;    ///< Location 38h,
  IN     UINT8     Dimm0_F1RC3_RC2;    ///< Location 39h,
  IN     UINT8     Dimm0_F1RC9_RC8;    ///< Location 3Ah,
  IN     UINT8     Dimm0_F1RC11_RC10;  ///< Location 3Bh,
  IN     UINT8     Dimm0_F1RC13_RC12;  ///< Location 3Ch,
  IN     UINT8     Dimm0_F1RC15_RC14;  ///< Location 3Dh,
  IN     UINT8     Dimm0_F2RC1_RC0;    ///< Location 3Eh,
  IN     UINT8     Dimm0_F2RC3_RC2;    ///< Location 3Fh,
  IN     UINT8     Dimm0_F3RC1_RC0;    ///< Location 40h,
  IN     UINT8     Dimm0_F3RC3_RC2;    ///< Location 41h,
  IN     UINT8     Dimm0_F3RC7_RC6;    ///< Location 42h,
  IN     UINT8     Dimm0_F3RC9_RC8;    ///< Location 43h,
  IN     UINT8     Dimm0_F3RC11_RC10;  ///< Location 44h,
  IN     UINT8     Dimm0_F4RC11_RC10;  ///< Location 45h,
  IN     UINT8     Dimm0_F5RC11_RC10;  ///< Location 46h,
  IN     UINT8     Dimm0_F6RC11_RC10;  ///< Location 47h,
  IN     UINT8     Dimm0_F7RC11_RC10;  ///< Location 48h,
  IN     UINT8     Dimm0_F8RC11_RC10;  ///< Location 49h,
  IN     UINT8     Dimm0_F9RC11_RC10;  ///< Location 4Ah,
  IN     UINT8     Dimm0_F10RC11_RC10; ///< Location 4Bh,
  IN     UINT8     Dimm0_F14RC1_RC0;   ///< Location 4Ch,
  IN     UINT8     Dimm0_F14RC3_RC2;   ///< Location 4Dh,
  IN     UINT8     Dimm0_F14RC5_RC4;   ///< Location 4Eh,
  IN     UINT8     Dimm0_F14RC7_RC6;   ///< Location 4Fh,
  IN     UINT8     Dimm0_F14RC9_RC8;   ///< Location 50h,
  IN     UINT8     Dimm0_F14RC11_RC10; ///< Location 51h,
  IN     UINT8     Dimm0_F14RC13_RC12; ///< Location 52h,
  IN     UINT8     Dimm0_F14RC15_RC14; ///< Location 53h,
  IN     UINT8     Dimm0_F15RC1_RC0;   ///< Location 54h,
  IN     UINT8     Dimm0_F15RC3_RC2;   ///< Location 55h,
  IN     UINT8     Dimm0_F15RC5_RC4;   ///< Location 56h,
  IN     UINT8     Dimm0_F15RC7_RC6;   ///< Location 57h,
  IN     UINT8     Dimm0_F15RC9_RC8;   ///< Location 58h,
  IN     UINT8     Dimm0_F15RC11_RC10; ///< Location 59h,
  IN     UINT8     Dimm0_F15RC13_RC12; ///< Location 5Ah,
  IN     UINT8     Dimm0_F15RC15_RC14; ///< Location 5Bh,
  IN     UINT8     Dimm0_ExtRC_xAC;    ///< Location 5Ch,
  IN     UINT8     Dimm0_ExtRC_xB8;    ///< Location 5Dh,
  IN     UINT8     Dimm0_ExtRC_xB9;    ///< Location 5Eh,
  IN     UINT8     Dimm0_ExtRC_xBA;    ///< Location 5Fh,
  IN     UINT8     Dimm0_ExtRC_xBB;    ///< Location 60h,
  IN     UINT8     Dimm0_ExtRC_xBC;    ///< Location 61h,
  IN     UINT8     Dimm0_ExtRC_xBD;    ///< Location 62h,
  IN     UINT8     Dimm0_ExtRC_xBE;    ///< Location 63h,
  IN     UINT8     Dimm0_ExtRC_xBF;    ///< Location 64h,
  IN     UINT8     Dimm0_ExtRC_xC8;    ///< Location 65h,
  IN     UINT8     Dimm0_ExtRC_xC9;    ///< Location 66h,
  IN     UINT8     Dimm0_ExtRC_xCA;    ///< Location 67h,
  IN     UINT8     Dimm0_ExtRC_xCB;    ///< Location 68h,
  IN     UINT8     Dimm0_ExtRC_xCC;    ///< Location 69h,
  IN     UINT8     Dimm0_ExtRC_xCD;    ///< Location 6Ah,
  IN     UINT8     Dimm0_ExtRC_xCE;    ///< Location 6Bh,
  IN     UINT8     Dimm0_ExtRC_xCF;    ///< Location 6Ch,
  IN     UINT8     Reserved6D;         ///< Location 6Dh,
  IN     UINT8     Reserved6E;         ///< Location 6Eh,
  IN     UINT8     Dimm0Cfg;           ///< Location 6Fh, TBD
  IN     UINT8[8]  DIMM1 RCWs;         ///< Location 77h:70h, See DIMM0
  IN     UINT8[8]  DIMM2 RCWs;         ///< Location 7Fh:78h, See DIMM0
} PMU_SMB_DDR3L_CZ;

/// DDR4 RDIMM PMU SRAM Message Block Annex for DDR4 RDIMM
typedef struct _PMU_SMB_DDR4R_CZ {
  IN     UINT16    M0_MR0;          ///< Location 21h:20h,
  IN     UINT16    M0_MR1;          ///< Location 23h:22h,
  IN     UINT16    M0_MR2;          ///< Location 25h:24h,
  IN     UINT16    M0_MR3;          ///< Location 27h:26h,
  IN     UINT16    M0_MR4;          ///< Location 29h:28h,
  IN     UINT16    M0_MR5;          ///< Location 2Bh:2Ah,
  IN OUT UINT16    M0_MR6;          ///< Location 2Dh:2Ch,
  IN     UINT16    Reserved2E;      ///< Location 2Fh:2Eh,
  IN     UINT8     SR_Rtt;          ///< Location 30h, TBD
  IN     UINT8     DR_Rtt_R0;       ///< Location 31h, TBD
  IN     UINT8     DR_Rtt_R1;       ///< Location 32h, TBD
  IN     UINT8     QR_Rtt_R0;       ///< Location 33h, TBD
  IN     UINT8     QR_Rtt_R1;       ///< Location 34h, TBD
  IN     UINT8     QR_Rtt_R2;       ///< Location 35h, TBD
  IN     UINT8     QR_Rtt_R3;       ///< Location 36h, TBD
  IN     UINT8     Reserved37;      ///< Location 37h,
  IN     UINT8     Dimm0_RC1_RC0;   ///< Location 38h, RDIMM 4-bit RCWs
  IN     UINT8     Dimm0_RC3_RC2;   ///< Location 39h,
  IN     UINT8     Dimm0_RC5_RC4;   ///< Location 3Ah,
  IN     UINT8     Dimm0_RC7_RC6;   ///< Location 3Bh,
  IN     UINT8     Dimm0_RC9_RC8;   ///< Location 3Ch,
  IN     UINT8     Dimm0_RC11_RC10; ///< Location 3Dh,
  IN     UINT8     Dimm0_RC13_RC12; ///< Location 3Eh,
  IN     UINT8     Dimm0_RC15_RC14; ///< Location 3Fh,
  IN     UINT8     Dimm1_RC1_RC0;   ///< Location 40h, See DIMM0
         UINT8     Dimm1_RC3_RC2;   ///< Location 41h,
         UINT8     Dimm1_RC5_RC4;   ///< Location 42h,
         UINT8     Dimm1_RC7_RC6;   ///< Location 43h,
         UINT8     Dimm1_RC9_RC8;   ///< Location 44h,
         UINT8     Dimm1_RC11_RC10; ///< Location 45h,
         UINT8     Dimm1_RC13_RC12; ///< Location 46h,
         UINT8     Dimm1_RC15_RC14; ///< Location 47h,
  IN     UINT8     Dimm2_RC1_RC0;   ///< Location 48h, See DIMM0
         UINT8     Dimm2_RC3_RC2;   ///< Location 49h,
         UINT8     Dimm2_RC5_RC4;   ///< Location 4Ah,
         UINT8     Dimm2_RC7_RC6;   ///< Location 4Bh,
         UINT8     Dimm2_RC9_RC8;   ///< Location 4Ch,
         UINT8     Dimm2_RC11_RC10; ///< Location 4Dh,
         UINT8     Dimm2_RC13_RC12; ///< Location 4Eh,
         UINT8     Dimm2_RC15_RC14; ///< Location 4Fh,
} PMU_SMB_DDR4R_CZ;
*/

/// DDR4 Unbuffered PMU SRAM Message Block Annex for DDR4 Unbuffered
typedef struct _PMU_SMB_DDR4U_CZ {
  IN     UINT16    M0_MR0;         ///< Location 21h:20h,
  IN     UINT16    M0_MR1;         ///< Location 23h:22h,
  IN     UINT16    M0_MR2;         ///< Location 25h:24h,
  IN     UINT16    M0_MR3;         ///< Location 27h:26h,
  IN     UINT16    M0_MR4;         ///< Location 29h:28h,
  IN     UINT16    M0_MR5;         ///< Location 2Bh:2Ah,
  IN OUT UINT16    M0_MR6;         ///< Location 2Dh:2Ch,
  IN     UINT8     X16Present;     ///< Location 2Eh, X16 device map. Corresponds to CS[7:0].
                                   ///<                    1 = CS contains x16 devices.
                                   ///<                    0 = CS does not contain x16 devices.
  IN     UINT8     Reserved2F;     ///< Location 2Fh,
  IN     UINT16    M1_MR0;         ///< Location 31h:30h,
  IN     UINT16    M1_MR1;         ///< Location 33h:32h,
  IN     UINT16    M1_MR2;         ///< Location 35h:34h,
  IN     UINT16    M1_MR3;         ///< Location 37h:36h,
  IN     UINT16    M1_MR4;         ///< Location 39h:38h,
  IN     UINT16    M1_MR5;         ///< Location 3Bh:3Ah,
  IN OUT UINT16    M1_MR6;         ///< Location 3Dh:3Ch,
  IN     UINT8     Reserved3E;     ///< Location 3Eh,
  IN     UINT8     Reserved3F;     ///< Location 3Fh,
  IN     UINT8     M1CkeSetup;     ///< Location 40h, M1 Cke Setup. See M0CkeSetup
  IN     UINT8     M1CsOdtSetup;   ///< Location 41h, M1 CsOdtSetup. See M0CkeSetup
  IN     UINT8     M1AddrCmdSetup; ///< Location 42h, M1 AddrCmdSetup. See M0CkeSetup.
  OUT    UINT8     M1_CD_R_W;      ///< Location 43h, M1 State Read to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_R_R;      ///< Location 44h, M1 State Read to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_W_W;      ///< Location 45h, M1 State Write to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_W_R;      ///< Location 46h, M1 State Write to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M1_CD_R_R_SD;   ///< Location 47h, M1 State Read to Read Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  OUT    UINT8     M1_CD_W_W_SD;   ///< Location 48h, M1 State Write to Write Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  OUT    UINT8     Reserved49;     ///< Location 49h
} PMU_SMB_DDR4U_CZ;

/// Composite Annex structure for various memory types
typedef union _PMU_SRAM_MSG_BLOCK_ANNEX_CZ {
  IN OUT PMU_SMB_DDR3U_CZ  D3u;   ///< Annex for DDR3 Unbuffered
  IN OUT PMU_SMB_DDR4U_CZ  D4u;   ///< Annex for DDR4 Unbuffered
} PMU_SRAM_MSG_BLOCK_ANNEX_CZ;

/// Base PMU SRAM Message Block Base
typedef struct _PMU_SRAM_MSG_BLOCK_CZ {
  IN     UINT8     TableRevision;  ///< Location 0h, MsgBlock Revision
  IN     UINT8     MsgMisc;        ///< Location 1h, 01h = Pulse MTEST during training
  IN     UINT16    PmuRevision;    ///< Location 3h:2h, PMU firmware revision ID
  IN     UINT32    CpuId;          ///< Location 7h:4h, 32-bit CPUID
  IN     UINT8     DramType;       ///< Location 8h, Module Type From SPD Dram Device Type:
                                   ///<                   0x0B = DDR3
                                   ///<                   0x0C = DDR4
  IN     UINT8     ModuleType;     ///< Location 9h, ModuleType[6:0]: Per JEDEC SPD Definition.
                                   ///<              ModuleType[7]: PmuTrainEcc.
                                   ///<                   1 = PMU trains ECC for all DIMMs.
                                   ///<                   0 = PMU does not train ECC.
  IN     UINT8     CsPresent;      ///< Location Ah, Global chip select map. Corresponds to CS[7:0].
                                   ///<                   1 = CS Present.
                                   ///<                   0 = CS Not Present.
  IN     UINT8     AddrMirror;     ///< Location Bh, Corresponds to CS[7:0]
                                   ///<                   1 = Address Mirror.
                                   ///<                   0 = No Address Mirror.
  IN OUT UINT8     CsTestFail;     ///< Location Ch, Corresponds to CS[7:0]
                                   ///<                   1 = Failed Training or Initilization
                                   ///<                   0 = No Failure.
  IN     UINT8     DctCfg;         ///< Location Dh, [0] PerRankTiming:
                                   ///<                   1 = The channel is configured to use four timing groups for CS[3:0].
                                   ///<                   0 = The channel is configured to use four timing groups for four sets of chipselect-pairs.
                                   ///<              [1] SlowAccessMode:
                                   ///<                   1 = 2T Address Timing.
                                   ///<                   0 = 1T Address Timing.
                                   ///<              [2] CsMux45:
                                   ///<                   1 = CS[5:4] have an address function.
                                   ///<                   0 = CS[5:4] have a CS function.
                                   ///<              [3] CsMux67:
                                   ///<                   1 = CS[7:6] have an address function.
                                   ///<                   0 = CS[7:6] have a CS function.
                                   ///<              [4] CsTimingMux67:
                                   ///<                   1 = Address Timing.
                                   ///<                   0 = CS Timing
  IN     UINT16    CurrentTemp;    ///< Location Fh:Eh, Unsigned 11-bit temperature in 0.125 degree C increments, -49C offset.  See D18F5xA8_x383[GblMaxTemp].
  IN     UINT16    SequenceCtrl;   ///< Location 11h:10h, PMU Sequence Control Word
  IN     UINT8     HdtCtrl;        ///< Location 12h, Reserved for Debug Use
  IN     UINT8     M0CkeSetup;     ///< Location 13h, Setup time on CAD bus signals.
                                   ///<               [4:0] Fine delay, in 1/32 UI increments, relative to prelaunch.
                                   ///<               [5] Prelaunch, in 1UI increments, relative to positive latching memclock edge.
                                   ///<                    1 = 1 memclock.
                                   ///<                    0 = 1/2 memclock.
  IN     UINT8     M0CsOdtSetup;   ///< Location 14h, Setup time on CAD bus signals.
                                   ///<               [4:0] Fine delay, in 1/32 UI increments, relative to prelaunch.
                                   ///<               [5] Prelaunch, in 1UI increments, relative to positive latching memclock edge.
                                   ///<                     1 = 1 memclock
                                   ///<                     0 = 1/2 memclock.
  IN     UINT8     M0AddrCmdSetup; ///< Location 15h, Setup time on CAD bus signals.
                                   ///<               [4:0] Fine delay, in 1/32 UI increments, relative to prelaunch.
                                   ///<               [5] Prelaunch, in 1UI increments, relative to positive latching memclock edge.
                                   ///<                    1 = 1 memclock.
                                   ///<                    0 = 1/2 memclock.
                                   ///<                    If the signal is in 2T timing mode then signal asserts exactly 1 memclock earlier
                                   ///<                    than specified and is 2 memclocks in duration.
  OUT    UINT8     M0_CD_R_W;      ///< Location 16h, M0 State Read to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M0_CD_R_R;      ///< Location 17h, M0 State Read to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M0_CD_W_W;      ///< Location 18h, M0 State Write to Write Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M0_CD_W_R;      ///< Location 19h, M0 State Write to Read Command delay in MCLKs, any chip select to any other chipselect
  OUT    UINT8     M0_CD_R_R_SD;   ///< Location 1Ah, M0 State Read to Read Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  OUT    UINT8     M0_CD_W_W_SD;   ///< Location 1Bh, M0 State Write to Write Command delay in MCLKs, any chip select to any other chipselect on the same DIMM.
  IN     UINT8     Reserved1C;     ///< Location 1Ch,
  IN     UINT8     Reserved1D;     ///< Location 1Dh,
  IN     UINT8     Reserved1E;     ///< Location 1Eh,
  IN     UINT8     Reserved1F;     ///< Location 1Fh,
  IN OUT PMU_SRAM_MSG_BLOCK_ANNEX_CZ Annex; ///< See Annexes
} PMU_SRAM_MSG_BLOCK_CZ;


/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define SMB_PER_RANK_TMG    0x01
#define SMB_2T_TMG          0x02
#define SMB_CSMUX_45_ADDR   0x04
#define SMB_CSMUX_67_ADDR   0x08
#define SMB_TMG_MUX_67_ADDR 0x10

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

BOOLEAN
MemNWritePmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNReadPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNInitPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

BOOLEAN
MemNPostPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );
#endif //_MNPMUSRAMMSGBLOCKCZ_H_

