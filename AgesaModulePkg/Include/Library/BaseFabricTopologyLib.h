/* $NoKeywords:$ */
/**
 * @file
 *
 * Low-level Fabric Topology Services base library
 *
 * Contains interface to the family specific fabric topology base library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
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
 **/

#ifndef _BASE_FABRIC_TOPOLOGY_LIB_H_
#define _BASE_FABRIC_TOPOLOGY_LIB_H_
#pragma pack (push, 1)

/// Root Bridge location
typedef struct {
  UINTN       Socket;
  UINTN       Die;
  UINTN       Index;
} ROOT_BRIDGE_LOCATION;

/// Fabric Device Types
typedef enum {
  PrimaryFch,                  ///< Primary FCH
  SlaveFch,                    ///< Slave FCH
  FchTypeMax,                  ///< Not a valid entry type, use for limit checking.
  PrimarySmu,                  ///< Primary SMU
  SlaveSmu,                    ///< Slave SMU
  SmuTypeMax,                  ///< Not a valid entry type, use for limit checking.
  ComponentTypeMax             ///< Not a valid entry type, use for limit checking.
} COMPONENT_TYPE;

/// Component location
typedef struct {
  UINTN                Socket;
  UINTN                Die;
  UINTN                IomsFabricId;
  COMPONENT_TYPE       Type;
} COMPONENT_LOCATION;

/// Fabric Device Types
typedef enum {
  Ccm,                         ///< Processor Family Specific Workarounds which are @b not practical using the other types.
  Gcm,                         ///< Processor Config Space registers via SMN.
  Ncs,                         ///< Processor Config Space registers via SMN.
  Ncm,                         ///< Processor Config Space registers via SMN.
  Pie,                         ///< Processor Config Space registers via SMN.
  Ioms,                        ///< Processor Config Space registers via SMN.
  Cs,                          ///< Processor Config Space registers via SMN.
  Tcdx,                        ///< Processor Config Space registers via SMN.
  Cake,                        ///< Processor Config Space registers via SMN.
  CsUmc,                       ///< Processor Config Space registers via SMN.
  CsCcix,                      ///< Processor Config Space registers via SMN.
  FabricDeviceTypeMax          ///< Not a valid entry type, use for limit checking.
} FABRIC_DEVICE_TYPE;

/// Device ID structure
typedef struct {
  UINTN   FabricID;           ///< Fabric ID
  UINTN   InstanceID;         ///< Instance ID
} DEVICE_IDS;

/// Processor neighbor information
typedef struct {
  UINTN   SocketNumber;       ///< Socket Number
} AMD_FABRIC_TOPOLOGY_PROCESSOR_NEIGHBOR_INFO;

/// Fabric topology structure
typedef struct {
  FABRIC_DEVICE_TYPE   Type;          ///< Type
  UINTN                Count;         ///< Count
  CONST DEVICE_IDS     *IDs;          ///< Device IDs
} AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP;

/// Fabric topology neighbor information structure
typedef struct {
  UINTN   SocketNumber;             ///< Socket Number
  UINTN   InternalDieNumber;        ///< Internal Die Number
  UINTN   HostCake;                 ///< Host Cake
  UINTN   NeighborCake;             ///< Neighbor Cake
} AMD_FABRIC_TOPOLOGY_DIE_NEIGHBOR_INFO;

UINTN
FabricTopologyGetNumberOfProcessorsPresent (
  VOID
  );

UINTN
FabricTopologyGetNumberOfSystemDies (
  VOID
  );

UINTN
FabricTopologyGetNumberOfSystemRootBridges (
  VOID
  );

UINTN
FabricTopologyGetNumberOfDiesOnSocket (
  IN       UINTN Socket
  );

UINTN
FabricTopologyGetNumberOfRootBridgesOnSocket (
  IN       UINTN Socket
  );

UINTN
FabricTopologyGetNumberOfRootBridgesOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  );

UINTN
FabricTopologyGetDieSystemOffset (
  IN       UINTN Socket,
  IN       UINTN Die
  );

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FabricTopologyGetDeviceMapOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  );

UINTN
FabricTopologyGetHostBridgeSystemFabricID (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

UINTN
FabricTopologyGetHostBridgeBusBase (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

UINTN
FabricTopologyGetHostBridgeBusLimit (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

BOOLEAN
FabricTopologyGetSystemComponentRootBridgeLocation (
  IN       COMPONENT_TYPE Component,
  IN OUT   ROOT_BRIDGE_LOCATION *Location
  );

BOOLEAN
FabricTopologyHasFch (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

BOOLEAN
FabricTopologyHasSmu (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

UINTN
FabricTopologyGetPhysRootBridgeNumber (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  );

#pragma pack (pop)
#endif // _BASE_FABRIC_TOPOLOGY_LIB_H_

