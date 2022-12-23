/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Topology Services -
 *
 * Contains code that provides fabric topology services
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
#include "AGESA.h"
#include <PiDxe.h>
#include <Library/SmmServicesTableLib.h>
#include "Library/IdsLib.h"
#include <Protocol/FabricTopologyServices2.h>
#include <Filecode.h>
#include "AGESA.h"
#include "FabricTopologyServices2Smm.h"

#define FILECODE LIBRARY_SMMFABRICTOPOLOGYSERVICES2LIB_FABRICTOPOLOGYSERVICES2SMM_FILECODE

STATIC AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL  mFabricTopologyServices2SmmProtocol = {
  FabricTopologyGetSystemInfo2,
  FabricTopologyGetProcessorInfo2,
  FabricTopologyGetDieInfo2,
  FabricTopologyGetRootBridgeInfo2
};

EFI_STATUS
EFIAPI
FabricTopologyService2SmmProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  Handle;

  // Install Fabric Topology Services
  Handle = NULL;
  Status = gSmst->SmmInstallProtocolInterface (
                &Handle,
                &gAmdFabricTopologyServices2SmmProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mFabricTopologyServices2SmmProtocol
                );

  return Status;
}

/**
 * This service retrieves information about the overall system with respect to data fabric.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL instance.
 * @param[out] NumberOfInstalledProcessors    Pointer to the total number of populated
 *                                            processor sockets in the system.
 * @param[out] TotalNumberOfDie               Pointer to the total number of die in the system.
 * @param[out] TotalNumberOfRootBridges       Pointer to the total number of root PCI bridges in
 *                                            the system.
 * @param[out] SystemFchRootBridgeLocation    System primary FCH location.
 * @param[out] SystemSmuRootBridgeLocation    System primary SMU location.
 *
 * @retval EFI_SUCCESS                        The system topology information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
EFIAPI
FabricTopologyGetSystemInfo2 (
  IN    AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *This,
  OUT   UINTN                                  *NumberOfInstalledProcessors,
  OUT   UINTN                                  *TotalNumberOfDie,
  OUT   UINTN                                  *TotalNumberOfRootBridges,
  OUT   ROOT_BRIDGE_LOCATION                   *SystemFchRootBridgeLocation,
  OUT   ROOT_BRIDGE_LOCATION                   *SystemSmuRootBridgeLocation
  )
{
  if ((NumberOfInstalledProcessors == NULL) && (TotalNumberOfDie == NULL) && (TotalNumberOfRootBridges == NULL) &&
      (SystemFchRootBridgeLocation == NULL) && (SystemSmuRootBridgeLocation == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (NumberOfInstalledProcessors != NULL) {
    *NumberOfInstalledProcessors = FabricTopologyGetNumberOfProcessorsPresent ();
  }

  if (TotalNumberOfDie != NULL) {
    *TotalNumberOfDie = FabricTopologyGetNumberOfSystemDies ();
  }

  if (TotalNumberOfRootBridges != NULL) {
    *TotalNumberOfRootBridges = FabricTopologyGetNumberOfSystemRootBridges ();
  }

  if (SystemFchRootBridgeLocation != NULL) {
    FabricTopologyGetSystemComponentRootBridgeLocation (PrimaryFch, SystemFchRootBridgeLocation);
  }

  if (SystemSmuRootBridgeLocation != NULL) {
    FabricTopologyGetSystemComponentRootBridgeLocation (PrimarySmu, SystemSmuRootBridgeLocation);
  }

  return EFI_SUCCESS;
}

/**
 * This service retrieves information about the processor installed in the given socket.
 *
 * If no processor is installed in Socket, then EFI_INVALID_PARAMETER is returned.
 *
 * @param[in]  This                           A pointer to the
 *                                            AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL instance.
 * @param[in]  Socket                         Zero-based socket number to check.
 * @param[out] NumberOfDie                    Pointer to the number of die present on the
 *                                            given processor.
 * @param[out] NumberOfRootBridges            Pointer to the number of root PCI bridges on
 *                                            the given processor.
 *
 * @retval EFI_SUCCESS                        The processor information was retrieved successfully.
 * @retval EFI_INVALID_PARAMETER              Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER              All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
EFIAPI
FabricTopologyGetProcessorInfo2 (
  IN       AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *This,
  IN       UINTN                                   Socket,
     OUT   UINTN                                  *NumberOfDie,
     OUT   UINTN                                  *NumberOfRootBridges
  )
{
  if ((NumberOfDie == NULL) && (NumberOfRootBridges == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Socket >= FabricTopologyGetNumberOfProcessorsPresent ()) {
    return EFI_INVALID_PARAMETER;
  }

  if (NumberOfDie != NULL) {
    *NumberOfDie = FabricTopologyGetNumberOfDiesOnSocket (Socket);
  }

  if (NumberOfRootBridges != NULL) {
    *NumberOfRootBridges = FabricTopologyGetNumberOfRootBridgesOnSocket (Socket);
  }

  return EFI_SUCCESS;
}

/**
 * This service retrieves information about the given die.
 *
 * @param[in]  This                  A pointer to the
 *                                   AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL instance.
 * @param[in]  Socket                The target die's socket identifier.
 * @param[in]  Die                   The target die's identifier within Socket.
 * @param[out] NumberOfRootBridges   Pointer to the number of root PCI bridges
 *                                   present on the given die.
 * @param[out] SystemIdOffset        Pointer to the die's offset for all of its
 *                                   devices.
 * @param[out] FabricIdMap           Pointer to an array describing the devices
 *                                   present within the given die's fabric.
 *
 * @retval EFI_SUCCESS               The die information was retrieved successfully.
 * @retval EFI_INVALID_PARAMETER     Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER     Die is non-existent.
 * @retval EFI_INVALID_PARAMETER     All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
EFIAPI
FabricTopologyGetDieInfo2 (
  IN       AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *This,
  IN       UINTN                                   Socket,
  IN       UINTN                                   Die,
     OUT   UINTN                                  *NumberOfRootBridges,
     OUT   UINTN                                  *SystemIdOffset,
     OUT   AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP    **FabricIdMap
  )
{
  if ((NumberOfRootBridges == NULL) && (SystemIdOffset == NULL) && (FabricIdMap == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Socket >= FabricTopologyGetNumberOfProcessorsPresent ()) {
    return EFI_INVALID_PARAMETER;
  }

  if (Die >= FabricTopologyGetNumberOfDiesOnSocket (Socket)) {
    return EFI_INVALID_PARAMETER;
  }

  if (NumberOfRootBridges != NULL) {
    *NumberOfRootBridges = FabricTopologyGetNumberOfRootBridgesOnDie (Socket, Die);
  }

  if (SystemIdOffset != NULL) {
    *SystemIdOffset = FabricTopologyGetDieSystemOffset (Socket, Die);
  }

  if (FabricIdMap != NULL) {
    *FabricIdMap = (AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *) FabricTopologyGetDeviceMapOnDie (Socket, Die);
  }

  return EFI_SUCCESS;
}

/**
 * This service retrieves information about the given root PCI bridge.
 *
 * @param[in]  This                  A pointer to the
 *                                   AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL instance.
 * @param[in]  Socket                The target root bridge's socket identifier.
 * @param[in]  Die                   The target root bridge's die identifier within Socket.
 * @param[in]  Index                 The target root bridge's 0-based index on die
 * @param[out] SystemFabricID        Pointer to the root bridge's fabric identifier
 *                                   within the system.
 * @param[out] BusNumberBase         Pointer to the root bridge's base PCI bus
 *                                   number in the system.
 * @param[out] BusNumberLimit        Pointer to the root bridge's maximum decoded
 *                                   PCI bus number in the system.
 * @param[in]  PhysicalRootBridgeNumber Physical RootBridge number of RootBridge specified by Socket/Die/Index.
 * @param[in]  HasFchDevice          If this RootBridge has FCH.
 * @param[in]  HasSystemMgmtUnit     If this RootBridge has SMU.
 *
 * @retval EFI_SUCCESS               The root bridge's information was retrieved successfully.
 * @retval EFI_INVALID_PARAMETER     Socket is non-existent.
 * @retval EFI_INVALID_PARAMETER     Die is non-existent.
 * @retval EFI_INVALID_PARAMETER     FabricId is non-existent.
 * @retval EFI_INVALID_PARAMETER     Socket / Die / FabricId does not have a PCI bus range.
 * @retval EFI_INVALID_PARAMETER     All output parameter pointers are NULL.
 *
 **/
EFI_STATUS
EFIAPI
FabricTopologyGetRootBridgeInfo2 (
  IN       AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *This,
  IN       UINTN                                   Socket,
  IN       UINTN                                   Die,
  IN       UINTN                                   Index,
     OUT   UINTN                                  *SystemFabricID,
     OUT   UINTN                                  *BusNumberBase,
     OUT   UINTN                                  *BusNumberLimit,
     OUT   UINTN                                  *PhysicalRootBridgeNumber,
     OUT   BOOLEAN                                *HasFchDevice,
     OUT   BOOLEAN                                *HasSystemMgmtUnit
  )
{
  if ((SystemFabricID == NULL) && (BusNumberBase == NULL) && (BusNumberLimit == NULL) &&
      (PhysicalRootBridgeNumber == NULL) && (HasFchDevice == NULL) && (HasSystemMgmtUnit == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Socket >= FabricTopologyGetNumberOfProcessorsPresent ()) {
    return EFI_INVALID_PARAMETER;
  }

  if (Die >= FabricTopologyGetNumberOfDiesOnSocket (Socket)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Index >= FabricTopologyGetNumberOfRootBridgesOnDie (Socket, Die)) {
    return EFI_INVALID_PARAMETER;
  }

  if (SystemFabricID != NULL) {
    *SystemFabricID = FabricTopologyGetHostBridgeSystemFabricID (Socket, Die, Index);
  }

  if (BusNumberBase != NULL) {
    *BusNumberBase = FabricTopologyGetHostBridgeBusBase (Socket, Die, Index);
  }

  if (BusNumberLimit != NULL) {
    *BusNumberLimit = FabricTopologyGetHostBridgeBusLimit (Socket, Die, Index);
  }

  if (PhysicalRootBridgeNumber != NULL) {
    *PhysicalRootBridgeNumber = FabricTopologyGetPhysRootBridgeNumber (Socket, Die, Index);
  }

  if (HasFchDevice != NULL) {
    *HasFchDevice = FabricTopologyHasFch (Socket, Die, Index);
  }

  if (HasSystemMgmtUnit != NULL) {
    *HasSystemMgmtUnit = FabricTopologyHasSmu (Socket, Die, Index);
  }

  return EFI_SUCCESS;
}

