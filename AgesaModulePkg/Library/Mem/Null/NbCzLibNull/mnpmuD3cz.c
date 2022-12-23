/* $NoKeywords:$ */
/**
 * @file
 *
 * mnpmuD3cz.c
 *
 * Support functions for memory training using PMU for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 317056 $ @e \$Date: 2015-04-20 22:06:48 +0800 (Mon, 20 Apr 2015) $
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
#include "mport.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "cpuRegisters.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "mtsdi3.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mnPmuFirmwareCZ.h"
#include "mnPmuFirmwareD3cz.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "OptionMemory.h"
#include "mncz.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNPMUD3CZ_FILECODE



/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define PMU_TRAINS_ECC_LANES       0x80    ///< PMU trains ECC lanes
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


ROMDATA PMU_FIRMWARE PmuFirmwareD3ImageTableCZ[] = {
//
//  PMU Signature  Instance   Package String      NULL Reserved   Size                                           Image Data
//
  {{PMU_SIGNATURE,    '0',    PMU_PACKAGE_STRING,  0,     {0}  }, PMU_SRAM_DMEM_SIZE_CZ + PMU_SRAM_IMEM_SIZE_CZ, PMU_DDR3_CZ_9221   },
  {{PMU_SIGNATURE,    '1',    PMU_PACKAGE_STRING,  0,     {0}  }, PMU_IMAGE_NOT_USEABLE },
};
ROMDATA UINT8 PmuFirmwareD3ImageTableSizeCZ = GET_SIZE_OF (PmuFirmwareD3ImageTableCZ);

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function sets the PMU sequence control for DRAM training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
// This is a placholder for D3 Specific Sequence Control
//
// VOID
// MemNSetPmuSequenceControlD3CZ (
//   IN OUT   MEM_NB_BLOCK *NBPtr
//   )
// {
//   LOCATE_HEAP_PTR LocHeap;
//   PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
//
//   LocHeap.BufferHandle = AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE;
//
//   if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) != AGESA_SUCCESS) {
//     ASSERT(FALSE); // Could not locate heap for PMU SRAM Message Block buffer.
//   }
//
//   PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) LocHeap.BufferPtr;
//   //
//   // Call Common Sequence Control
//   //
//   MemNSetPmuSequenceControlCZ(NBPtr);
// }
//

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function passes to PMU DRAM configuration over PMU SRAM for DDR3
 *     DRAM init and training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramConfigD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function passes to PMU DRAM timings over PMU SRAM for DDR3 DRAM init and training.
 *     Timings are MemPstate dependent.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramTimingsD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function set the PMU sequence control for DRAM training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSetPmuSequenceControlD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}
