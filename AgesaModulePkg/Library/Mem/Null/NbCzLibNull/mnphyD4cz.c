/* $NoKeywords:$ */
/**
 * @file
 *
 * mnphyD4cz.c
 *
 * Northbridge Phy support for CZ with DDR4
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325208 $ @e \$Date: 2015-08-26 10:05:40 +0800 (Wed, 26 Aug 2015) $
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
#include "cpuRegisters.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mnreg.h"
#include "OptionMemory.h"       // need def for MEM_FEAT_BLOCK_NB
#include "mncz.h"
#include "PlatformMemoryConfiguration.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNPHYD4CZ_FILECODE
/* features */
#include "mftds.h"
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
 *     This function does Phy Predriver initialization
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPredriverInitD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the phy registers to configure CAD bus and data bus for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramCadDataBusD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function initializes FIFO configurations for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNPhyFifoConfigD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */



