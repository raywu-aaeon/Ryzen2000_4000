/* $NoKeywords:$ */
/**
 * @file
 *
 * mnphycz.c
 *
 * Northbridge Phy support for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 317293 $ @e \$Date: 2015-04-22 08:44:09 +0800 (Wed, 22 Apr 2015) $
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


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNPHYCZ_FILECODE
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

typedef struct {
  UINT8 BankAddr :4;
  UINT8 Addr13 :1;
  UINT8 Addr14 :1;
  UINT8 Addr15 :1;
  UINT8 Reserved :1;
} BANK_ADDR_MAP;
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

VOID
MemNTriStateUnusedPadCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function programs DDR mode for each Phy
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNSetPhyDdrModeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs general Phy configuration registers
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPhyGenCfgCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the phy registers according to the desired phy VDDIO voltage level
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNPhyVoltageLevelCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs DRAM channel frequency
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNProgramChannelFreqCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{

}



/* -----------------------------------------------------------------------------*/
/**
 *
 *    DRAM Phy Power Savings, tri-state unused pads, and DLLs.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Additional DRAM Phy Power Savings
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNAddlDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Enable DDR3 PHY calibrating
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNEnablePhyCalibrationCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Waits for PHY calibrating to complete
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPendOnPhyCalibrateCompletionCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Set the rate for PHY calibrate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNRateOfPhyCalibrateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function tri-state unused pads.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNTriStateUnusedPadCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Determine slow OPN mode is true if any valid NB-Pstates not tied
 *     to M1 has NCLK=800MHZ/M0=667MHZ or NCLK=800MHZ/M0=1333MHZ
 *
 *     @param[in,out]   *NBPtr    - Pointer to the MEM_NB_BLOCK
 *
 *     @return         TRUE  - slow_OPN mode, otherwise False
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
STATIC
MemNSlowOpnModeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets or set DQS timing during training.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   TrnDly - type of delay to be set
 *     @param[in]   DrbnVar - encoding of Dimm-Rank-Byte-Nibble to be accessed
 *                  (use either DIMM_BYTE_ACCESS(dimm,byte) or CS_NBBL_ACCESS(cs,nibble) to use this encoding
 *     @param[in]   Field - Value to be programmed
 *     @param[in]   IsSet - Indicates if the function will set or get
 *
 *     @return      value read, if the function is used as a "get"
 */

UINT32
MemNcmnGetSetTrainDlyCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       TRN_DLY_TYPE TrnDly,
  IN       DRBN DrbnVar,
  IN       UINT16 Field
  )
{
  return 0;
}


