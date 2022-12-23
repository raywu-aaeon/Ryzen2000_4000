/* $NoKeywords:$ */
/**
 * @file
 *
 * mndctD3cz.c
 *
 * Northbridge DCT support for CZ and DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325428 $ @e \$Date: 2015-08-27 20:08:24 +0800 (Thu, 27 Aug 2015) $
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


/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */

#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mp.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "mncz.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mftds.h"
#include "merrhdl.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNDCTD3CZ_FILECODE

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


/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function uses calculated values from DCT.Timings structure to
 *      program its registers for CZ
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramCycTimingsD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs Mem Pstate registers for DDR3
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       MemPstate - Mem Pstate
 *
 */

VOID
MemNProgramMemPstateRegD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the memory controller for training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDctForTrainingD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the memory controller for mission mode
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDctNormalD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}



/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function returns the High and Low Bit Masks to be swapped
 *      to enable CS interleaving for CZ with DDR3
 *
 *     @param[in,out]  *NBPtr      - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  BankAddrMap - Bank Address Mapping Nibble for the current CS
 *     @param[in,out]  *LowBit     - Pointer to Low bit
 *     @param[in,out]  *HiBit      - Pointer to High bit
 *
 */
VOID
MemNGetCSIntLvAddrD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 BankAddrMap,
  OUT   UINT8 *LowBit,
  OUT   UINT8 *HiBit
  )
{

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *    Mode Register initialization for DDR3
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNModeRegisterInitializationD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs DDR3 turnaround timings for each DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramTurnaroundTimingsD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}



