/* $NoKeywords:$ */
/**
 * @file
 *
 * mnreg.c
 *
 * Common Northbridge register access functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include "mm.h"
#include "mn.h"
#include "merrhdl.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_NBLIBNULL_MNREG_FILECODE


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
VOID
MemNErrorRecoveryStatus (
  IN OUT   BOOLEAN Status
  );

VOID
MemNIgnoreErrorStatus (
  IN OUT   BOOLEAN Status
  );
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets the current DCT to work on.
 *   Should be called before accessing a certain DCT
 *   All data structures will be updated to point to the current DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Dct - ID of the target DCT
 *
 */

VOID
MemNSwitchDCTNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function is used by families that use a separate DctCfgSel bit to
 *     select the current DCT which will be accessed by function 2.
 *     NOTE:  This function must be called BEFORE the NBPtr->Dct variable is
 *     updated.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Dct     - Pointer to ID of the target DCT
 *
 */

BOOLEAN
MemNDctCfgSelectUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  )
{

  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets the current channel to work on.
 *   Should be called before accessing a certain channel
 *   All data structures will be updated to point to the current channel
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Channel - ID of the target channel
 *
 */

VOID
MemNSwitchChannelNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Channel
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets a bit field from PCI register
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Field name
 *
 *     @return      Bit field value
 */

UINT32
MemNGetBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets a bit field from PCI register
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Field name
 *     @param[in]   Field - Value to be stored in PCT register
 *
 */

VOID
MemNSetBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check if bitfields of all enabled DCTs on a die have the expected value. Ignore
 *  DCTs that are disabled.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be checked
 *
 *     @return          TRUE -  All enabled DCTs have the expected value on the bitfield.
 *     @return          FALSE - Not all enabled DCTs have the expected value on the bitfield.
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNBrdcstCheckNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Set bitfields of all enabled DCTs on a die to a value. Ignore
 *  DCTs that are disabled.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNBrdcstSetNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Set bitfields of all DCTs regardless of if they are being enabled or not on a
 *  die to a value.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNBrdcstSetUnConditionalNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{

}

/*-----------------------------------------------------------------------------*/
/**
 *      This function calculates the memory channel index relative to the
 *      socket, taking the Die number, the Dct, and the channel.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in] Dct
 *     @param[in] Channel
 *
 */
UINT8
MemNGetSocketRelativeChannelNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct,
  IN       UINT8 Channel
  )
{
  return 0;
}
/*-----------------------------------------------------------------------------*/
/**
 *      This function records the error recovery status
 *
 *     @param[in,out]   Status   - Error recovery status
 */
VOID
MemNErrorRecoveryStatus (
  IN OUT   BOOLEAN Status
  )
{
}
/*-----------------------------------------------------------------------------*/
/**
 *      This function ignores the error recovery status
 *
 *     @param[in,out]   Status   - Error recovery status
 */
VOID
MemNIgnoreErrorStatus (
  IN OUT   BOOLEAN Status
  )
{
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *  Poll a bitfield. If the bitfield does not get set to the target value within
 *  specified microseconds, it times out.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *     @param[in]   MicroSecond - Number of microsecond to wait
 *     @param[in]   IfBroadCast - Need to broadcast to both DCT or not
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNPollBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field,
  IN       UINT32 MicroSecond,
  IN       BOOLEAN IfBroadCast
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function changes memory Pstate context
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in]      MemPstate  - Target Memory Pstate
 *
 *     @return    TRUE
 * ----------------------------------------------------------------------------
 */
VOID
MemNChangeMemPStateContextNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSTATE MemPstate
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function allocates buffer for NB register table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Handle   - Handle for heap allocation for NBRegTable
 *
 *     @return      TRUE  - Successfully allocates buffer the first time
 *     @return      FALSE - Buffer already allocated or fails to allocate
 */

BOOLEAN
MemNAllocateNBRegTableNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       NB_REG_TAB_HANDLE  Handle
  )
{

  return TRUE;
}

/*-----------------------------------------------------------------------------
 *
 *
 *     This function is an empty function used to intialize FamilySpecificHook array
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  OptParam   - Optional parameter
 *
 *     @return  TRUE - always
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNDefaultFamilyHookNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

