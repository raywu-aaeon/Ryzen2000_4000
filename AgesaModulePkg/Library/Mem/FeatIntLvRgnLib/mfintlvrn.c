/* $NoKeywords:$ */
/**
 * @file
 *
 * mfrintlv.c
 *
 * Feature Region interleaving support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/Intlvrgn)
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


#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "Library/AmdMemFeatIntLvRgnLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATINTLVRGNLIB_MFINTLVRN_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define _4GB_RJ27 ((UINT32)4 << (30 - 27))
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
 *   MemFInterleaveRegion:
 *
 *  Applies region interleaving if both DCTs have different size of memory, and
 *  the channel interleaving region doesn't have UMA covered.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemFInterleaveRegion (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 TOM;
  UINT32 TOM2;
  UINT32 TOMused;
  UINT32 UmaBase;
  UINT32 DctSelBase;
  S_UINT64 SMsr;
  LOCATE_HEAP_PTR LocHeap;
  UMA_INFO *UmaInfoPtr;

  MEM_DATA_STRUCT *MemPtr;
  MEM_PARAMETER_STRUCT *RefPtr;

  MemPtr = NBPtr->MemPtr;
  RefPtr = NBPtr->RefPtr;

  UmaBase = (UINT32) RefPtr->UmaBase >> (27 - 16);

  //TOM scaled from [47:0] to [47:27]
  SMsr.Value64 = AsmReadMsr64 (TOP_MEM);
  SMsr.Values32.lo += (16 << 20);  // Add 16MB to gain back C6 region if C6 is enabled
  TOM = (SMsr.Values32.lo >> 27) | (SMsr.Values32.hi << (32 - 27));

  //TOM2 scaled from [47:0] to [47:27]
  SMsr.Value64 = AsmReadMsr64 (TOP_MEM2);
  TOM2 = (SMsr.Values32.lo >> 27) | (SMsr.Values32.hi << (32 - 27));

  TOMused = (UmaBase >= _4GB_RJ27) ? TOM2 : TOM;

  if (UmaBase != 0) {
    //Check if channel interleaving is enabled ? if so, go to next step.
    if (NBPtr->GetBitField (NBPtr, BFDctSelIntLvEn) == 1) {
      DctSelBase = NBPtr->GetBitField (NBPtr, BFDctSelBaseAddr);
      //Skip if DctSelBase is equal to 0, because DCT0 has as the same memory size as DCT1.
      if (DctSelBase != 0) {
        //We need not enable swapped interleaved region when channel interleaving region has covered all of the UMA.
        if (DctSelBase < TOMused) {
          NBPtr->EnableSwapIntlvRgn (NBPtr, UmaBase, TOMused);

          // Set UMA attribute to interleaved after interleaved region has been swapped
          LocHeap.BufferHandle = AMD_UMA_INFO_HANDLE;
          if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) == AGESA_SUCCESS) {
            UmaInfoPtr = (UMA_INFO *) LocHeap.BufferPtr;
            UmaInfoPtr->UmaAttributes = UMA_ATTRIBUTE_INTERLEAVE | UMA_ATTRIBUTE_ON_DCT0 | UMA_ATTRIBUTE_ON_DCT1;
          } else {
            ASSERT (FALSE);
          }
        }
      }
    }
  }
}



