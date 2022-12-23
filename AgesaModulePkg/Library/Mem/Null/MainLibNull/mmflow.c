/* $NoKeywords:$ */
/**
 * @file
 *
 * mmflow.c
 *
 * Main Memory Flow Entrypoint file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
 * @e \$Revision: 318592 $ @e \$Date: 2015-05-12 13:18:53 -0500 (Tue, 12 May 2015) $
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "PlatformMemoryConfiguration.h"
#include "mu.h"
#include "Library/AmdHeapLib.h"
#include "OptionMemory.h"
#include "Filecode.h"

#define FILECODE LIBRARY_MEM_NULL_MAINLIBNULL_MMFLOW_FILECODE

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
STATIC
MemSPDDataProcess (
  IN OUT   MEM_DATA_STRUCT *MemPtr
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
 *      This function is the main memory configuration function for DR DDR3
 *
 *      Requirements:
 *
 *      Run-Time Requirements:
 *      1. Complete Hypertransport Bus Configuration
 *      2. AmdMemInitDataStructDef must be run to set default values
 *      3. MSR bit to allow access to high PCI regs set on all nodes
 *      4. BSP in Big Real Mode
 *      5. Stack available
 *      6. MCG_CTL=-1, MC4_EN=0 for all CPUs
 *      7. MCi_STS from shutdown/warm reset recorded (if desired) prior to entry
 *      8. All var MTRRs reset to zero
 *      9. State of NB_CFG.DisDatMsk set properly on all CPUs
 *
 *     @param[in,out]   *MemPtr   - Pointer to the MEM_DATA_STRUCT
 *
 *     @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
AmdMemAuto (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  return AGESA_SUCCESS;
  // Report error
  //  Status = (*PeiServices)->LocatePpi (PeiServices,
  //                                    &gAmdCommonErrorLogPpiGuid,
  //                                    0,
  //                                    NULL,
  //                                    (VOID **)&AmdCommonErrorLogPpiPtr);
  //  if (EFI_SUCCESS != Status) {
  //      AmdCommonErrorLogPpiPtr->MemPutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_SPD, 0, 0, 0, 0, &MemPtr->StdHeader);
  //    }
  // Consume a CCx Service
  // Consume a PSP Service (APOB)
  // Consume a Fabric Service
  // Consume a GNB Service
  // Consume a FCH Service
  // Publish PPIs from memory
  // Consume a SOC service (package and soc ID)
  // Regsiter a notify callback
  // Add depex to driver on SOC ID
  // Wait function
  // IDS/CBS option
  // Save S3 data
  // How to deal with return data and output
  //return Status;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *  This function fills a default SPD buffer with SPD values for all DIMMs installed in the system
 *
 *    The SPD Buffer is populated with a Socket-Channel-Dimm centric view of the Dimms.  At this
 *  point, the Memory controller type is not known, and the platform BIOS does not know the anything
 *  about which DIMM is on which DCT.  So the DCT relationship is abstracted from the arrangement
 *  of SPD information here.  We use the utility functions GetSpdSocketIndex(), GetMaxChannelsPerSocket(),
 *  and GetMaxDimmsPerChannel() to Map the SPD data according to which Socket-relative channel the DIMMs
 *  are connected to.  The functions rely on either the maximum values in the
 *  PlatformSpecificOverridingTable or if unspecified, the absolute maximums in AGESA.H.
 *
 *  This mapping is translated in the Northbridge object Constructor and the Technology block constructor.
 *
 *     @param[in,out]   *MemPtr   - Pointer to the MEM_DATA_STRUCT
 *
 */

VOID
STATIC
MemSPDDataProcess (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{

}

