/* $NoKeywords:$ */
/**
 * @file},
 *
 * mpScz4.c},
 *
 * Platform specific settings for CZ DDR4 SO-DIMM system
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA},
 * @e sub-project: (Mem/Ps/CZ)
 * @e \$Revision: 325367 $ @e \$Date: 2015-08-27 09:46:56 +0800 (Thu, 27 Aug 2015) $
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

#define FILECODE LIBRARY_MEM_NULL_PSCZLIBNULL_MPSCZ4_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
// For A1 or Greater tables
#define AMD_REV_F15_CZ_GTE_A1    (~AMD_REV_F15_CZ_A0 & AMD_REV_F15_ALL)

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

STATIC CONST PSCFG_MAXFREQ_ENTRY ROMDATA MaxFreqCZSODIMMD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZMaxFreqTblEntSOD4 = {
   {PSCFG_MAXFREQ, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0 | AMD_REV_F15_CZ_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_ROUTING_ANY},
   sizeof (MaxFreqCZSODIMMD4) / sizeof (PSCFG_MAXFREQ_ENTRY),
   (VOID *)&MaxFreqCZSODIMMD4
};

// DDR4 Max Freq. for normal SODIMM configuration
// Format :
// DimmPerCh,   Dimms,   SR,   DR,   QR,   Speed1_2V,   Speed_TBD1,   Speed_TBD2
//
STATIC CONST PSCFG_MAXFREQ_ENTRY ROMDATA MaxFreqBRSODIMMD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY BRMaxFreqTblEntSOD4 = {
   {PSCFG_MAXFREQ, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_BR_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_ROUTING_ANY},
   sizeof (MaxFreqBRSODIMMD4) / sizeof (PSCFG_MAXFREQ_ENTRY),
   (VOID *)&MaxFreqBRSODIMMD4
};

// CAD Bus configuration for SO-DIMM (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZSODIMMTree4[] = {
  {0},
};

CONST PSC_TBL_ENTRY CZCadBusTblEnSOTree4 = {
   {PSCFG_CADBUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (CadBusCZSODIMMTree4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZSODIMMTree4
};


// Data Bus configuration for SO-DIMM (DQS routed in tree) (CZ A0 Only)
// Format :
// DimmPerCh, DDRrate,                      VDDIO, Dimm0,   Dimm1,                       RttNom,     RttWr,     Rtt_Park,   DQ,   DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZSODIMMTree4_A0[] = {
  {0},

};

CONST PSC_TBL_ENTRY CZDataBusTblEnSOTree4_A0 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZSODIMMTree4_A0) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZSODIMMTree4_A0
};

// Data Bus configuration for SO-DIMM  (DQS routed in tree) (CZ A1 or Later)
// Format :
// DimmPerCh, DDRrate,                      VDDIO, Dimm0,   Dimm1,                       RttNom,     RttWr,     Rtt_Park,   DQ,   DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZSODIMMTree4[] = {
  {0},
};

CONST PSC_TBL_ENTRY CZDataBusTblEnSOTree4 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_GTE_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZSODIMMTree4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZSODIMMTree4
};

// CAD Bus configuration for SO-DIMM (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZSODIMMDC4[] = {
  {0},
};

CONST PSC_TBL_ENTRY CZCadBusTblEnSODC4 = {
   {PSCFG_CADBUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (CadBusCZSODIMMDC4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZSODIMMDC4
};


// Data Bus configuration for SO-DIMM (DQS routed in daisy chain) (CZ A0 Only)
// Format :
// DimmPerCh, DDRrate,                      VDDIO, Dimm0,   Dimm1,                       RttNom,     RttWr,     Rtt_Park,   DQ,   DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZSODIMMDC4_A0[] = {
  {0},

};

CONST PSC_TBL_ENTRY CZDataBusTblEnSODC4_A0 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZSODIMMDC4_A0) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZSODIMMDC4_A0
};

// Data Bus configuration for SO-DIMM  (DQS routed in daisy chain) (CZ A1 or Later)
// Format :
// DimmPerCh, DDRrate,                      VDDIO, Dimm0,   Dimm1,                       RttNom,     RttWr,     Rtt_Park,   DQ,   DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZSODIMMDC4[] = {
  {0},
};

CONST PSC_TBL_ENTRY CZDataBusTblEnSODC4 = {
   {PSCFG_DATABUS, SODIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_GTE_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZSODIMMDC4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZSODIMMDC4
};

