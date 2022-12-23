/**
 * @file
 *
 * AMD Integrated Debug Print Routines
 *
 * Contains all functions related to IDS Debug Print
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
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
 */

 /*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Uefi.h>
#include <Pi/PiMultiPhase.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/AmdBaseLib.h>
#include <AmdIdsDebugPrintLocal.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDIDSDEBUGPRINTLIB_AMDIDSDEBUGPRINTLIB_FILECODE

extern AMD_IDS_DEBUG_PRINT_INSTANCE AmdIdsDebugPrintRedirectIoInstance;
extern AMD_IDS_DEBUG_PRINT_INSTANCE AmdIdsDebugPrintHdtoutInstance;
extern AMD_IDS_DEBUG_PRINT_INSTANCE AmdIdsDebugPrintSerialInstance;

#define MAX_LOCAL_BUFFER_SIZE   512

CONST AMD_IDS_DEBUG_PRINT_INSTANCE* mAmdIdsDebugPrintInstances[] =
{
  &AmdIdsDebugPrintRedirectIoInstance,
  &AmdIdsDebugPrintHdtoutInstance,
  &AmdIdsDebugPrintSerialInstance,
  NULL,
};
/**
 *
 *  @param[in,out] Value  - Hex value to convert to a string in Buffer.
 *
 *
 */
VOID
GetAmdIdsDebugPrintInstances (
  IN OUT   CONST AMD_IDS_DEBUG_PRINT_INSTANCE   ***pIdsAmdIdsDebugPrintInstancesPtr
  )
{
  *pIdsAmdIdsDebugPrintInstancesPtr = &mAmdIdsDebugPrintInstances[0];
}


/**
 *  Check If any print service is enabled.
 *
 *  @param[in] AmdIdsDebugPrintInstances    The Pointer to print service list
 *
 *  @retval       TRUE    At least on print service is enabled
 *  @retval       FALSE   All print service is disabled
 *
 **/
BOOLEAN
AmdIdsDebugPrintCheckSupportAny (
  IN      CONST AMD_IDS_DEBUG_PRINT_INSTANCE **AmdIdsDebugPrintInstances
  )
{
  BOOLEAN IsSupported;
  UINTN i;
  IsSupported = FALSE;
  for (i = 0; AmdIdsDebugPrintInstances[i] != NULL; i++) {
    if (AmdIdsDebugPrintInstances[i]->support ()) {
      IsSupported = TRUE;
    }
  }
  return IsSupported;
}

RETURN_STATUS
EFIAPI
AmdIdsDebugPrintLibConstructor (
  VOID
  )
{
  UINT8 i;
  if (AmdIdsDebugPrintCheckSupportAny (mAmdIdsDebugPrintInstances)) {
    //init input
    for (i = 0; mAmdIdsDebugPrintInstances[i] != NULL; i++) {
      if (mAmdIdsDebugPrintInstances[i]->support ()) {
        mAmdIdsDebugPrintInstances[i]->constructor ();
      }
    }
  }
  return RETURN_SUCCESS;
}


/**
 *  Process debug string and print to the final Physical Layer
 *
 *  @param[in] FilterFlag    - Filter Flag
 *  @param[in] *Format - format string
 *  @param[in] Marker  - Variable parameter
 *
**/
VOID
AmdIdsDebugPrintf (
  IN      UINT64      FilterFlag,
  IN      CONST CHAR8 *Format,
  IN      VA_LIST     Marker
  )
{
  CHAR8 LocalBuffer[MAX_LOCAL_BUFFER_SIZE];
  UINTN OutPutStringLen;
  UINT64 Filter;
  AMD_IDS_DEBUG_PRINT_INSTANCE **AmdIdsDebugPrintInstances;
  UINT8 i;

  if (PcdGetBool (PcdAmdIdsDebugPrintEnable) == FALSE) {
    return;
  }

  OutPutStringLen = AsciiVSPrint (LocalBuffer, sizeof (LocalBuffer), Format, Marker);

  GetAmdIdsDebugPrintInstances (
      (const AMD_IDS_DEBUG_PRINT_INSTANCE ***)&AmdIdsDebugPrintInstances);
  if (AmdIdsDebugPrintCheckSupportAny (
        (const AMD_IDS_DEBUG_PRINT_INSTANCE **)AmdIdsDebugPrintInstances)) {
    //init input
    for (i = 0; AmdIdsDebugPrintInstances[i] != NULL; i++) {
      if (AmdIdsDebugPrintInstances[i]->support ()) {
        Filter = PcdGet64 (PcdAmdIdsDebugPrintFilter);
        //Get Customize filter if implemented(Option)
        AmdIdsDebugPrintInstances[i]->customfilter (&Filter);
        if (FilterFlag & Filter) {
          //Print Physical Layer
          AmdIdsDebugPrintInstances[i]->print (&LocalBuffer[0], OutPutStringLen);
        }
      }
    }
  }
}

