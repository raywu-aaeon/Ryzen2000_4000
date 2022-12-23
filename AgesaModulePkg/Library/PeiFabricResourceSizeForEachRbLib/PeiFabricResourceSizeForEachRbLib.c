/* $NoKeywords:$ */
/**
 * @file
 *
 * Get MMIO size for each Die
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision$   @e \$Date$
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
#include "PiPei.h"
#include "Filecode.h"
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include <Library/PeiServicesTablePointerLib.h>
#include <Protocol/FabricResourceManagerServicesProtocol.h>
#include <Ppi/ReadOnlyVariable2.h>

#define FILECODE LIBRARY_PEIFABRICRESOURCESIZEFOREACHRBLIB_PEIFABRICRESOURCESIZEFOREACHRBLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * FabricGetResourceSizeForEachRb
 *
 * Try to get user's request about MMIO/IO size for each RootBridge from NV variable
 *
 * @param[in, out]    ResourceSizeForEachRb     User's request about fabric resource size for each RootBridge
 *
 * @retval            EFI_SUCCESS               Get user's request from NV variable successfully
 */
EFI_STATUS
FabricGetResourceSizeForEachRb (
  IN       FABRIC_RESOURCE_FOR_EACH_RB *ResourceSizeForEachRb
  )
{
  UINTN                             VariableSize;
  EFI_STATUS                        Status;
  EFI_PEI_SERVICES                **PeiServices;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadVariable2;

  PeiServices = (EFI_PEI_SERVICES**) GetPeiServicesTablePointer();
  Status = (**PeiServices).LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadVariable2);
  ASSERT (Status == EFI_SUCCESS);

  VariableSize = sizeof (FABRIC_RESOURCE_FOR_EACH_RB);
  Status = ReadVariable2->GetVariable (
                      ReadVariable2,
                      L"ResourceSizeForEachRb",
                      &gAmdResourceSizeForEachRbGuid,
                      NULL,
                      &VariableSize,
                      (VOID *) ResourceSizeForEachRb
                      );
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetResourceSizeForEachRb
 *
 * Save user's request about MMIO/IO size for each RootBridge to NV variable
 *
 * @param[in]    CurrentUsed        Current used Mmio size for each RootBridge
 * @param[in]    UserRequest        User's request about Mmio size for each RootBridge
 *
 * @retval       EFI_UNSUPPORTED        Don't support this function during PEI
 */
EFI_STATUS
FabricSetResourceSizeForEachRb (
  IN       FABRIC_RESOURCE_FOR_EACH_RB *CurrentUsed,
  IN       FABRIC_RESOURCE_FOR_EACH_RB *UserRequest
  )
{
  return EFI_UNSUPPORTED;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricClearResourceSizeForEachRb
 *
 * Clear user's request about MMIO/IO size for each RootBridge to NV variable
 *
 *
 * @retval       EFI_UNSUPPORTED        Don't support this function during PEI
 */
EFI_STATUS
FabricClearResourceSizeForEachRb (
  )
{
  return EFI_UNSUPPORTED;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricGetResourceDistribution
 *
 * Get the information about which RootBridge's MMIO should be put above Pcie Cfg
 *
 * @param[in, out]    ResourceDistribution       If it's above Pcie Cfg
 *
 * @retval            EFI_UNSUPPORTED            Don't support this function during PEI
 */
EFI_STATUS
FabricGetResourceDistribution (
  IN       BOOLEAN   *ResourceDistribution
  )
{
  UINTN                             VariableSize;
  EFI_STATUS                        Status;
  EFI_PEI_SERVICES                **PeiServices;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadVariable2;

  PeiServices = (EFI_PEI_SERVICES**) GetPeiServicesTablePointer();
  Status = (**PeiServices).LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadVariable2);
  ASSERT (Status == EFI_SUCCESS); 

  VariableSize = sizeof (BOOLEAN) * MAX_SOCKETS_SUPPORTED * MAX_RBS_PER_SOCKET;
  Status = ReadVariable2->GetVariable (
                  ReadVariable2,
                  L"ResourceDistribution",
                  &gAmdResourceDistributionGuid,
                  NULL,
                  &VariableSize,
                  (VOID *) ResourceDistribution
                  );

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetResourceDistribution
 *
 * Set the information about which RootBridge's MMIO should be put above Pcie Cfg
 *
 * @param[in, out]    ResourceDistribution       If it's above Pcie Cfg
 *
 * @retval            EFI_UNSUPPORTED            Don't support this function during PEI
 */
EFI_STATUS
FabricSetResourceDistribution (
  IN       BOOLEAN   *ResourceDistribution
  )
{
  return EFI_UNSUPPORTED;
}


