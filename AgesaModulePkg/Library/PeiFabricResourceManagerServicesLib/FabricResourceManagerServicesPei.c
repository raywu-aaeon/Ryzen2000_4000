/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Resource Manager Service functions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
 *
 */
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
 */
#include <PiPei.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/FabricResourceSizeForEachRbLib.h>
#include <Ppi/FabricResourceManagerServicesPpi.h>
#include <Filecode.h>
#include "AGESA.h"


#define FILECODE LIBRARY_PEIFABRICRESOURCEMANAGERSERVICESLIB_FABRICRESOURCEMANAGERSERVICESPEI_FILECODE

EFI_STATUS
EFIAPI
PeiFabricAllocateMmio (
  IN OUT   UINT64                     *BaseAddress,
  IN OUT   UINT64                     *Length,
  IN       UINT64                      Alignment,
  IN       FABRIC_TARGET               Target,
  IN OUT   FABRIC_MMIO_ATTRIBUTE      *Attributes
  );

EFI_STATUS
EFIAPI
PeiFabricAllocateIo (
  IN OUT   UINT32                     *BaseAddress,
  IN OUT   UINT32                     *Length,
  IN       FABRIC_TARGET               Target
  );

EFI_STATUS
EFIAPI
PeiFabricGetAvailableResource (
  IN       FABRIC_RESOURCE_FOR_EACH_RB        *ResourceForEachRb
  );


STATIC FABRIC_RESOURCE_MANAGER_PPI  mFabricResourceManagerServicesPpi = {
  AMD_FABRIC_RESOURCE_PPI_REV,
  PeiFabricAllocateMmio,
  PeiFabricAllocateIo,
  PeiFabricGetAvailableResource
};

STATIC EFI_PEI_PPI_DESCRIPTOR mFabricResourceManagerPpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdFabricResourceManagerServicesPpiGuid,
  &mFabricResourceManagerServicesPpi
};


EFI_STATUS
EFIAPI
FabricResourceManagerServicePpiInstall (
  IN       CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  // Install Fabric Resource Manager Services
  Status = (**PeiServices).InstallPpi (PeiServices, &mFabricResourceManagerPpiList);

  return Status;

}

/*---------------------------------------------------------------------------------------*/
/**
 * BSC entry point for allocate MMIO
 *
 * program MMIO base/limit/control registers
 *
 * @param[in, out]    BaseAddress        Starting address of the requested MMIO range.
 * @param[in, out]    Length             Length of the requested MMIO range.
 * @param[in]         Alignment          Alignment bit map.
 * @param[in]         Target             PCI bus number/RootBridge number of the requestor.
 * @param[in, out]    Attributes         Attributes of the requested MMIO range indicating whether
 *                                       it is readable/writable/non-posted
 *
 * @retval            EFI_STATUS         EFI_OUT_OF_RESOURCES - The requested range could not be added because there are not
 *                                                              enough mapping resources.
 *                                       EFI_ABORTED          - One or more input parameters are invalid. For example, the
 *                                                              PciBusNumber does not correspond to any device in the system.
 *                                       EFI_SUCCESS          - MMIO region allocated successfully
 */
EFI_STATUS
EFIAPI
PeiFabricAllocateMmio (
  IN OUT   UINT64                     *BaseAddress,
  IN OUT   UINT64                     *Length,
  IN       UINT64                      Alignment,
  IN       FABRIC_TARGET               Target,
  IN OUT   FABRIC_MMIO_ATTRIBUTE      *Attributes
  )
{
  EFI_STATUS         Status;

  Status = FabricAllocateMmio (BaseAddress, Length, Alignment, Target, Attributes);

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * BSC entry point for for allocate IO
 *
 * program IO base/limit registers
 *
 * @param[in, out]    BaseAddress        Starting address of the requested MMIO range.
 * @param[in, out]    Length             Length of the requested MMIO range.
 * @param[in]         Target             PCI bus number/RootBridge number of the requestor.
 *
 * @retval            EFI_STATUS         EFI_OUT_OF_RESOURCES - The requested range could not be added because there are not
 *                                                              enough mapping resources.
 *                                       EFI_ABORTED          - One or more input parameters are invalid. For example, the
 *                                                              PciBusNumber does not correspond to any device in the system.
 *                                       EFI_SUCCESS          - IO region allocated successfully
 */
EFI_STATUS
EFIAPI
PeiFabricAllocateIo (
  IN OUT   UINT32                     *BaseAddress,
  IN OUT   UINT32                     *Length,
  IN       FABRIC_TARGET               Target
  )
{
  EFI_STATUS         Status;

  Status = FabricAllocateIo (BaseAddress, Length, Target);

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * PeiFabricGetAvailableResource
 *
 * Get available DF resource (MMIO/IO) for each RootBridge
 *
 * @param[in, out]    ResourceForEachRb     Avaiable DF resource (MMIO/IO) for each RootBridge
 *
 * @retval            EFI_SUCCESS           Available resources successfully obtained
 *                    EFI_ABORTED           Unable to obtain resource information
 */
EFI_STATUS
EFIAPI
PeiFabricGetAvailableResource (
  IN       FABRIC_RESOURCE_FOR_EACH_RB      *ResourceForEachRb
  )
{
  EFI_STATUS         Status;

  Status = FabricGetAvailableResource (ResourceForEachRb);

  return Status;
}


