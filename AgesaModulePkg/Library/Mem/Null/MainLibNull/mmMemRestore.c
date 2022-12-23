/* $NoKeywords:$ */
/**
 * @file
 *
 * mmMemRestore.c
 *
 * Main Memory Feature implementation file for Node Interleaving
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
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
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Library/AmdHeapLib.h"
//#include "cpuFeatures.h"
//#include "cpuRegisters.h"
//#include "cpuPostInit.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_MAINLIBNULL_MMMEMRESTORE_FILECODE

#define ST_PRE_ESR  0
#define ST_POST_ESR 1
#define ST_DONE     2

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

VOID
STATIC
MemMCreateS3NbBlock (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
     OUT   S3_MEM_NB_BLOCK **S3NBPtr
  );

VOID
MemMContextSave (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

BOOLEAN
MemMContextRestore (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

BOOLEAN
STATIC
MemMDramInit (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

UINT32
GetReducedMemBlockSize (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

VOID
MemMReducedMemBlockSave (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
  IN       VOID                *Storage,
     OUT   UINT32              *ActualBufferSize
  );

VOID
MemMReducedMemBlockRestore (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
  IN       VOID                *Storage
  );

/*-----------------------------------------------------------------------------
*                                EXPORTED FUNCTIONS
*
*-----------------------------------------------------------------------------
*/
extern MEM_FEAT_BLOCK_MAIN MemFeatMain;

BOOLEAN
MemMS3Save (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *  Determines the maximum amount of space required to store all reduced NB block
 *  and DCT block.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
UINT32
GetReducedMemBlockSize (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Save all the required reduced NB blocks and DCT blocks.
 *
 *     @param[in,out]   *MemMainPtr       - Pointer to the MEM_MAIN_DATA_BLOCK
 *     @param[in]       Storage           - Beginning of the context buffer.
 *     @param[out]      ActualBufferSize  - Actual size used in saving the device list.
 *
 */
VOID
MemMReducedMemBlockSave (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
  IN       VOID                *Storage,
     OUT   UINT32              *ActualBufferSize
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Restore all the required reduced NB blocks and DCT blocks.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *     @param[in]       Storage       - Beginning of the context buffer.
 *
 */
VOID
MemMReducedMemBlockRestore (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
  IN       VOID                *Storage
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check and save memory context if possible.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
VOID
MemMContextSave (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check and restore memory context if possible.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  DQS timing restore succeeds.
 *     @return          FALSE - DQS timing restore fails.
 */
BOOLEAN
MemMContextRestore (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Save all memory related data for S3.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMS3Save (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * This function does dram init based on register value
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 *
 */
BOOLEAN
STATIC
MemMDramInit (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  Create S3 NB Block.
 *
 *     @param[in,out]   MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *     @param[out]      S3NBPtr   - Pointer to the S3 NB Block pointer
 *
 */
VOID
STATIC
MemMCreateS3NbBlock (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr,
     OUT   S3_MEM_NB_BLOCK **S3NBPtr
  )
{

}

