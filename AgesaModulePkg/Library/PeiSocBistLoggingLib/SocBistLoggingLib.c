/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD SOC BIST Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
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
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */

#include "Uefi.h"
#include <Library/BaseLib.h>
#include "AMD.h"
#include "Filecode.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PeiSocBistLib.h>
#include <Ppi/FabricTopologyServices2Ppi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/AmdErrorLogPpi.h>

#define FILECODE LIBRARY_PEISOCBISTLOGGINGLIB_SOCBISTLOGGINGLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

 /*----------------------------------------------------------------------------------------
  *                          E X P O R T E D    F U N C T I O N S
  *----------------------------------------------------------------------------------------
 */

 /*---------------------------------------------------------------------------------------*/
 /**
  *
  * Logs an error if BIST failures are detected
  *
  * @param[in]      PeiServices            Pointer to PEI services
  *
  */
VOID
LogBistStatus (
  IN       CONST EFI_PEI_SERVICES **PeiServices
  )
{
  UINTN                                 i;
  UINTN                                 j;
  UINTN                                 k;
  UINTN                                 NumberOfSockets;
  UINTN                                 NumberOfDies;
  UINTN                                 NumberOfComplexes;
  UINTN                                 SystemDieCount;
  UINTN                                 Unused;
  UINT32                                BistData;
  EFI_STATUS                            CalledStatus;
  AGESA_STATUS                          BistStatus;
  PEI_AMD_ERROR_LOG_PPI                 *AmdErrorLog;
  AMD_PEI_FABRIC_TOPOLOGY_SERVICES2_PPI *FabricTopologyServices;
  AMD_CORE_TOPOLOGY_SERVICES_PPI        *CoreTopologyServices;

  CalledStatus = (*PeiServices)->LocatePpi (
                                 PeiServices,
                                 &gAmdFabricTopologyServices2PpiGuid,
                                 0,
                                 NULL,
                                 &FabricTopologyServices
                                 );

  ASSERT (CalledStatus == EFI_SUCCESS);

  CalledStatus = (*PeiServices)->LocatePpi (
                                 PeiServices,
                                 &gAmdCoreTopologyServicesPpiGuid,
                                 0,
                                 NULL,
                                 &CoreTopologyServices
                                 );

  if (CalledStatus != EFI_SUCCESS) {
    return;
  }

  CalledStatus = (*PeiServices)->LocatePpi (
                                 PeiServices,
                                 &gAmdErrorLogPpiGuid,
                                 0,
                                 NULL,
                                 &AmdErrorLog
                                 );

  ASSERT (CalledStatus == EFI_SUCCESS);

  FabricTopologyServices->GetSystemInfo (&NumberOfSockets, NULL, NULL, NULL, NULL);

  SystemDieCount = 0;

  for (i = 0; i < NumberOfSockets; i++) {
    FabricTopologyServices->GetProcessorInfo (i, &NumberOfDies, NULL);
    BistStatus = ReadNonCcxBistData ((i * NumberOfDies), &BistData, PeiServices);

    if (BistStatus != AGESA_SUCCESS) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "***************************** !!Non-CCX BIST ERROR!! Socket %d *********************\n", i);

      AmdErrorLog->AmdErrorLogPei (AmdErrorLog,
                                   AGESA_ALERT,
                                   CPU_EVENT_NON_CCX_BIST_FAILURE,
                                   i,
                                   0x00000000,
                                   0x00000000,
                                   BistData
                                   );
    }

    for (j = 0; j < NumberOfDies; j++) {
      CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, i, j, &NumberOfComplexes, &Unused, &Unused);
      for (k = 0; k < NumberOfComplexes; k++) {
        // Read Bist
        BistStatus = ReadCcxBistData (k, SystemDieCount, PeiServices);


        // If there's a BIST failure, log it in error log
        if (BistStatus != AGESA_SUCCESS) {

          IDS_HDT_CONSOLE (MAIN_FLOW, "***************************** !!CCX BIST ERROR!! Socket %d Die %d Complex %d *********************\n", i, j, k);

          AmdErrorLog->AmdErrorLogPei (AmdErrorLog,
                                       AGESA_ALERT,
                                       CPU_EVENT_CCX_BIST_FAILURE,
                                       i,
                                       j,
                                       k,
                                       0x00000000
                                      );
        }
      }
      SystemDieCount++;
    }
  }
}

