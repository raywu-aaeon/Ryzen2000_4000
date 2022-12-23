/* $NoKeywords:$ */
/**
 * @file
 *
 * mpUcz4.c
 *
 * Platform specific settings for CZ DDR4 UDIMM system
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps/CZ)
 * @e \$Revision: 334519 $ @e \$Date: 2016-01-15 15:48:51 +0800 (Fri, 15 Jan 2016) $
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

#define FILECODE LIBRARY_MEM_PSCZLIB_MPUCZ4_FILECODE
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
// DDR4 Max Freq UDIMM
// Format :
// DimmPerCh,   Dimms,   SR,   DR,   QR,   Speed1_5V,   Speed1_35V,   Speed1_25V
//
STATIC CONST PSCFG_MAXFREQ_ENTRY ROMDATA MaxFreqCZUDIMMD4[] = {
  // DimmPerCh, Dimms, SR, DR, Speed1_2V
  {0},
};
CONST PSC_TBL_ENTRY CZMaxFreqTblEntUD4 = {
   {PSCFG_MAXFREQ, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_ROUTING_ANY},
   sizeof (MaxFreqCZUDIMMD4) / sizeof (PSCFG_MAXFREQ_ENTRY),
   (VOID *)&MaxFreqCZUDIMMD4
};

// CAD Bus configuration for UDIMM (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,                Dimm0,             Dimm1,  Slow, AddrCmdTmg,  CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZUDIMMTreeD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnUTreeD4 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0 | AMD_REV_F15_CZ_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (CadBusCZUDIMMTreeD4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZUDIMMTreeD4
};

// Data Bus configuration for UDIMM (DQS routed in tree) (CZ A0 Only)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,   RttNom,    RttWr,    RttPark,   DQ,  DQS,  ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZUDIMMTreeD4_A0[] = {
  {0}
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUTreeD4_A0 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZUDIMMTreeD4_A0) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZUDIMMTreeD4_A0
};

// Data Bus configuration for UDIMM (DQS routed in tree) (CZ A1 or Later)
// Format :
// DimmPerCh, DDRrate,   VDDIO,              Dimm0,             Dimm1,  RttNom,     RttWr,   RttPark,   DQ,  DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZUDIMMTreeD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUTreeD4 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZUDIMMTreeD4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZUDIMMTreeD4
};

// CAD Bus configuration for UDIMM (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,                Dimm0,             Dimm1,  Slow, AddrCmdTmg,  CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZUDIMMDCD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnUDCD4 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0 | AMD_REV_F15_CZ_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (CadBusCZUDIMMDCD4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZUDIMMDCD4
};

// Data Bus configuration for UDIMM (DQS routed in daisy chain) (CZ A0 Only)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,   RttNom,    RttWr,    RttPark,   DQ,  DQS,  ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZUDIMMDCD4_A0[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUDCD4_A0 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A0}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZUDIMMDCD4_A0) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZUDIMMDCD4_A0
};

// Data Bus configuration for UDIMM (DQS routed in daisy chain) (CZ A1 or Later)
// Format :
// DimmPerCh, DDRrate,   VDDIO,              Dimm0,             Dimm1,  RttNom,     RttWr,   RttPark,   DQ,  DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusCZUDIMMDCD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUDCD4 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_CZ_A1}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZUDIMMDCD4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusCZUDIMMDCD4
};

// CAD Bus configuration for UDIMM (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,                Dimm0,             Dimm1,  Slow, AddrCmdTmg,  CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusBRUDIMMTreeD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY BRCadBusTblEnUTreeD4 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_BR_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (CadBusBRUDIMMTreeD4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusBRUDIMMTreeD4
};

// Data Bus configuration for UDIMM  (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,    VDDIO,             Dimm0,             Dimm1,     RttNom,      RttWr,    RttPark,   DQ,  DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusBRUDIMMTreeD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY BRDataBusTblEnUTreeD4 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_BR_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusBRUDIMMTreeD4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusBRUDIMMTreeD4
};

// CAD Bus configuration for UDIMM (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,                Dimm0,             Dimm1,  Slow, AddrCmdTmg,  CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusBRUDIMMDCD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY BRCadBusTblEnUDCD4 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_BR_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (CadBusBRUDIMMDCD4) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusBRUDIMMDCD4
};

// Data Bus configuration for UDIMM  (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,    VDDIO,             Dimm0,             Dimm1,     RttNom,      RttWr,    RttPark,   DQ,  DQS, ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D4 ROMDATA DataBusBRUDIMMDCD4[] = {
  {0},
};
CONST PSC_TBL_ENTRY BRDataBusTblEnUDCD4 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_BR_ALL}, PT_DONT_CARE, DDR4_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusBRUDIMMDCD4) / sizeof (PSCFG_DATABUS_ENTRY_D4),
   (VOID *)&DataBusBRUDIMMDCD4
};

