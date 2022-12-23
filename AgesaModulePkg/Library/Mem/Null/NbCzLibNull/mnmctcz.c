/* $NoKeywords:$ */
/**
 * @file
 *
 * mnmctcz.c
 *
 * Northbridge CZ MCT supporting functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 312808 $ @e \$Date: 2015-02-11 19:22:11 +0800 (Wed, 11 Feb 2015) $
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
#include "Library/AmdHeapLib.h"
#include "mport.h"
#include "Gnb.h"
#include "mm.h"
#include "mn.h"
#include "mnreg.h"
#include "OptionMemory.h"
#include "mncz.h"
#include "merrhdl.h"
//#include "cpuFeatures.h"
#include "Filecode.h"
#include "mftds.h"
#include "mu.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNMCTCZ_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define DCT_ADDR_VAL      0
#define LGCY_MMIO_HOLE_EN 1
#define DCT_SEL           4
#define ACP_ENGINE_SIZE_4MB_RJ16  0x0040

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
 *     This function switches memory pstate for CZ
 *
 *     @param[in,out]   *NBPtr    - Pointer to the MEM_NB_BLOCK
 *     @param[in]       MemPstate - Mem Pstate
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNSwitchMemPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function create the HT memory map
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNHtMemMapCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function does synchronous channel initialization
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncChannelInitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function obtains the memory frequency in the current context
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
UINT16
MemNGetMemClkFreqInCurrentContextCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function calculates and programs NB P-state dependent registers for CZ
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramNbPstateDependentRegistersCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function releases the NB P-state force for CZ
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   OptParam - Optional parameter
 *
 *     @return    TRUE
 */
BOOLEAN
MemNReleaseNbPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Report the Uma size that is going to be allocated.
 *     Total system memory   UMASize
 *     >= 6G                   1G
 *     >= 4G                 512M
 *     >= 2G                 256M
 *     < 2G                  256M
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          Uma size [31:0] = Addr [47:16]
 */
UINT32
MemNGetUmaSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function allocates memory storage for C6 and ACP Engine when
 *     it is requested to be enabled
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNAllocateC6AndAcpEngineStorageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function fixes up UMA info
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   OptParam - Optional parameter
 *
 *     @return    TRUE
 */
BOOLEAN
MemNFixupUmaInfoCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets final values for specific registers.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemNFinalizeMctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function force the ECC symbol size
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *Size    - ECC symbol size
 *                               FALSE = x4
 *                               TRUE  = x8
 *
 *     @return    TRUE
 */

BOOLEAN
MemNForceEccSymbolSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *Size
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   Set DRAM Controller select channel interleave address bit.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNInitChannelIntlvAddressBitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function disables scrubber temporarily for write access to
 *     DCT additional address space
 *
 *     @param[in,out]   *NBPtr            - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDisableScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function restores scrubber settings
 *
 *     @param[in,out]   *NBPtr            - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNRestoreScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function disable memory hole mappings
 *
 *     @param[in,out]   *NBPtr             - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *OptParam          - Optional parameter
 *
 *     @return    TRUE
 */

BOOLEAN
MemNDisableMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function restore memory hole mappings
 *
 *     @param[in,out]   *NBPtr             - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *OptParam          - Optional parameter
 *
 *     @return    TRUE
 */

BOOLEAN
MemNRestoreMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

