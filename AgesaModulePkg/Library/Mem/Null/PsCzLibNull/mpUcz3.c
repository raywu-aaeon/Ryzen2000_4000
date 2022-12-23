/* $NoKeywords:$ */
/**
 * @file
 *
 * mpUcz3.c
 *
 * Platform specific settings for CZ DDR3 UDIMM system
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

#define FILECODE LIBRARY_MEM_NULL_PSCZLIBNULL_MPUCZ3_FILECODE
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

//
STATIC CONST PSCFG_MAXFREQ_ENTRY ROMDATA MaxFreqCZUDIMMD3[] = {
  {0}
};
CONST PSC_TBL_ENTRY CZMaxFreqTblEntUD3 = {
   {PSCFG_MAXFREQ, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_ROUTING_ANY},
   sizeof (MaxFreqCZUDIMMD3) / sizeof (PSCFG_MAXFREQ_ENTRY),
   (VOID *)&MaxFreqCZUDIMMD3
};

// CAD Bus configuration for UDIMM (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZUDIMMTree3[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnUTree3 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (CadBusCZUDIMMTree3) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZUDIMMTree3
};

// Data Bus configuration for UDIMM (DQS routed in tree)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,   RttNom,  RttWr,   DQ,   DQS,  ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D3 ROMDATA DataBusCZUDIMMTree3[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUTree3 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_TREE},
   sizeof (DataBusCZUDIMMTree3) / sizeof (PSCFG_DATABUS_ENTRY_D3),
   (VOID *)&DataBusCZUDIMMTree3
};

// CAD Bus configuration for UDIMM (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,  Slow, AddrCmdTmg, CKE, CS/ODT, AddrCmd, CLK driver strength
//
STATIC CONST PSCFG_CADBUS_ENTRY ROMDATA CadBusCZUDIMMDC3[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZCadBusTblEnUDC3 = {
   {PSCFG_CADBUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (CadBusCZUDIMMDC3) / sizeof (PSCFG_CADBUS_ENTRY),
   (VOID *)&CadBusCZUDIMMDC3
};

// Data Bus configuration for SO-DIMM (DQS routed in daisy chain)
// Format :
// DimmPerCh, DDRrate,   VDDIO,      Dimm0,   Dimm1,   RttNom,  RttWr,   DQ,   DQS,  ODT strength
//
STATIC CONST PSCFG_DATABUS_ENTRY_D3 ROMDATA DataBusCZUDIMMDC3[] = {
  {0},
};
CONST PSC_TBL_ENTRY CZDataBusTblEnUDC3 = {
   {PSCFG_DATABUS, UDIMM_TYPE, NOD_DONT_CARE, {AMD_FAMILY_15_CZ, AMD_REV_F15_ALL}, PT_DONT_CARE, DDR3_TECHNOLOGY, MBL_DONT_CARE, MBP_DONT_CARE, DQS_DAISY_CHAIN},
   sizeof (DataBusCZUDIMMDC3) / sizeof (PSCFG_DATABUS_ENTRY_D3),
   (VOID *)&DataBusCZUDIMMDC3
};

