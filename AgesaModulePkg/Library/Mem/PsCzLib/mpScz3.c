/* $NoKeywords:$ */
/**
 * @file
 *
 * mpScz3.c
 *
 * Platform specific settings for CZ DDR3 SO-DIMM system
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps/CZ)
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

#include "AGESA.h"
#include "mport.h"
#include "ma.h"
#include "mm.h"
#include "mn.h"
#include "mp.h"
#include "PlatformMemoryConfiguration.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_PSCZLIB_MPSCZ3_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*
 *-----------------------------------------------------------------------------
 *                                EXPORTED FUNCTIONS
 *
 *-----------------------------------------------------------------------------
 */

// DDR3 Max Freq. for normal SODIMM configuration
// Format :
// DimmPerCh,   Dimms,   SR,   DR,   QR,   Speed1_5V,   Speed1_35V,   Speed1_25V
//
STATIC CONST PSCFG_MAXFREQ_ENTRY ROMDATA MaxFreqCZSODIMMD3[] = {
  {_1DIMM, 1, 1, 0, 0, DDR2133_FREQUENCY, DDR1866_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_1DIMM, 1, 0, 1, 0, DDR1866_FREQUENCY, DDR1866_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_2DIMM, 1, 1, 0, 0, DDR1600_FREQUENCY, DDR1600_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_2DIMM, 1, 0, 1, 0, DDR1600_FREQUENCY, DDR1600_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_2DIMM, 2, 2, 0, 0, DDR1600_FREQUENCY, DDR1600_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_2DIMM, 2, 1, 1, 0, DDR1600_FREQUENCY, DDR1333_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
  {_2DIMM, 2, 0, 2, 0, DDR1600_FREQUENCY, DDR1333_FREQUENCY, UNSUPPORTED_DDR_FREQUENCY},
};
CONST PSC_TBL_ENTRY CZMaxFreqTblEntSOD3 = {
   {PSCFG_MAXFREQ, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_ROUTING_ANY},
   sizeof (MaxFreqCZSODIMMD3) / sizeof (PSCFG_MAXFREQ_ENTRY),
   (VOID *)&MaxFreqCZSODIMMD3
};

// CAD Bus configuration for SO-DIMM (Routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZTree3[] = {
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00380000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00360000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR2133, V1_5                , DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR2133, V1_5                , DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x00380000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00380000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x00360000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00360000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_SR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_DR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_SR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_DR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_SR, 0, 0x003C3C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_DR, 1, 0x00003C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , 0, 0x003C3C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , 1, 0x00003C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_SR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_DR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_SR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_DR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR2133, V1_5                , NP     , DIMM_SR, 0, 0x003B3B3B, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR2133, V1_5                , NP     , DIMM_DR, 1, 0x00003B3B, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR2133, V1_5                , DIMM_SR, NP     , 0, 0x003B3B3B, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR2133, V1_5                , DIMM_DR, NP     , 1, 0x00003B3B, 0x1F, 0x1F, 0x1F, 0x1F},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnSOTree3 = {
   {PSCFG_CADBUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (CadBusCZTree3) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZTree3
};

// Data Bus configuration for SO-DIMM (Routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,   RttNom,  RttWr,   DQ,   DQS,  ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D3 ROMDATA DataBusCZSODIMMTree3[] = {
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR2133, V1_5                , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR2133, V1_5                , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR2133, V1_5                , NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR2133, V1_5                , NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR2133, V1_5                , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR2133, V1_5                , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnSOTree3 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZSODIMMTree3) / sizeof (PSCFG_DATABUS_ENTRY_D3),
   (VOID *)&DataBusCZSODIMMTree3
};

// CAD Bus configuration for SO-DIMM (Routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZDC3[] = {
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00380000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 0, 0x00360000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR2133, V1_5                , DIMM_SR, NP     , 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {1, DDR2133, V1_5                , DIMM_DR, NP     , 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x003B0000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00390039, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x00380000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 0, 0x00350037, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 0, 0x00360000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, 1, 0x00000035, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, 0, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, 1, 0x00000000, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_SR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_DR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_SR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_DR, 1, 0x0000002B, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_SR, 0, 0x003C3C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_DR, 1, 0x00003C3C, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_SR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_DR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_SR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_DR, 1, 0x00000031, 0x1F, 0x1F, 0x3F, 0x1F},
  {2, DDR2133, V1_5                , NP     , DIMM_SR, 0, 0x003B3B3B, 0x1F, 0x1F, 0x1F, 0x1F},
  {2, DDR2133, V1_5                , NP     , DIMM_DR, 1, 0x00003B3B, 0x1F, 0x1F, 0x1F, 0x1F},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnSODC3 = {
   {PSCFG_CADBUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (CadBusCZDC3) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZDC3
};

// Data Bus configuration for SO-DIMM (Routed in daisy chain)
// Format :
//
STATIC CONST PSCFG_DATABUS_ENTRY_D3 ROMDATA DataBusCZSODIMMDC3[] = {
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {1, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {1, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_SR, NP     , ODT_60 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1600, V1_25 + V1_35 + V1_5, DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1866, V1_35 + V1_5        , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR1866, V1_35 + V1_5        , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR2133, V1_5                , DIMM_SR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {1, DDR2133, V1_5                , DIMM_DR, NP     , ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR667 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x04},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x01},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR800 , V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x05},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_120, ODT_OFF, 0x70, 0x70, 0x04},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1066, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_40 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_60 , ODT_OFF, 0x70, 0x70, 0x05},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_SR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_DR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_DR, DIMM_SR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1333, V1_25 + V1_35 + V1_5, DIMM_SR, DIMM_DR, ODT_30 , ODT_120, 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_25 + V1_35 + V1_5, NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_DR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1600, V1_35 + V1_5        , DIMM_SR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_35 + V1_5        , NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_DR, DIMM_SR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR1866, V1_5                , DIMM_SR, DIMM_DR, ODT_20 , ODT_60 , 0x75, 0x75, 0x0C},
  {2, DDR2133, V1_5                , NP     , DIMM_SR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
  {2, DDR2133, V1_5                , NP     , DIMM_DR, ODT_40 , ODT_OFF, 0x70, 0x70, 0x0C},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnSODC3 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZSODIMMDC3) / sizeof (PSCFG_DATABUS_ENTRY_D3),
   (VOID *)&DataBusCZSODIMMDC3
};

