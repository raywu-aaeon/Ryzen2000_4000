/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Topology Base Lib implementation for SSP
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
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
#include <Library/BaseLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/AmdBaseLib.h>
#include <FabricRegistersDf3.h>
#include <FabricInfoSsp.h>
#include <CcxRegistersVh.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE  LIBRARY_BASEFABRICTOPOLOGYSSPLIB_BASEFABRICTOPOLOGYSSPLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FindDeviceTypeEntryInMap (
  IN       UINTN               Socket,
  IN       UINTN               Die,
  IN       FABRIC_DEVICE_TYPE  Type
  );

CONST
COMPONENT_LOCATION *
FindComponentLocationMap (
  IN       UINTN *Count,
  IN       UINTN *PhysIoms0FabricId
  );

//
// SSP IOD
//
CONST UINTN ROMDATA SspPhysIoms0FabricId = 0x18;

CONST COMPONENT_LOCATION ROMDATA SspComponentLocation [] = {
  {0, 0, 0x1B, PrimaryFch}, // Physical location, Socket 0, Die 0, Ioms3
  {1, 0, 0x1B, SlaveFch},   // Physical location, Socket 1, Die 0, Ioms3
  {0, 0, 0x1B, PrimarySmu}, // Physical location, Socket 0, Die 0, Ioms3
  {1, 0, 0x1B, SlaveSmu},   // Physical location, Socket 1, Die 0, Ioms3
};

CONST DEVICE_IDS ROMDATA  SspCsMap [] = {
  {0x00000000, 0x00000000},
  {0x00000001, 0x00000001},
  {0x00000002, 0x00000002},
  {0x00000003, 0x00000003},
  {0x00000004, 0x00000004},
  {0x00000005, 0x00000005},
  {0x00000006, 0x00000006},
  {0x00000007, 0x00000007},
  {0x00000008, 0x00000008},
  {0x00000009, 0x00000009},
  {0x0000000A, 0x0000000A},
  {0x0000000B, 0x0000000B}
};

CONST DEVICE_IDS ROMDATA  SspCsUmcMap [] = {
  {0x00000000, 0x00000000},
  {0x00000001, 0x00000001},
  {0x00000002, 0x00000002},
  {0x00000003, 0x00000003},
  {0x00000004, 0x00000004},
  {0x00000005, 0x00000005},
  {0x00000006, 0x00000006},
  {0x00000007, 0x00000007}
};

CONST DEVICE_IDS ROMDATA  SspCsCcixMap [] = {
  {0x00000008, 0x00000008},
  {0x00000009, 0x00000009},
  {0x0000000A, 0x0000000A},
  {0x0000000B, 0x0000000B}
};

CONST DEVICE_IDS ROMDATA  SspCcmMap [] = {
  {0x00000010, 0x00000010},
  {0x00000011, 0x00000011},
  {0x00000012, 0x00000012},
  {0x00000013, 0x00000013},
  {0x00000014, 0x00000014},
  {0x00000015, 0x00000015},
  {0x00000016, 0x00000016},
  {0x00000017, 0x00000017}
};

CONST DEVICE_IDS ROMDATA  SspIomsMap [] = {
  {0x00000018, 0x00000018},
  {0x00000019, 0x00000019},
  {0x0000001A, 0x0000001A},
  {0x0000001B, 0x0000001B}
};

CONST DEVICE_IDS ROMDATA  CpIomsMap [] = {
  {0x00000018, 0x00000018}, //@todo remove this line when Eddie's code is ready
  {0x00000019, 0x00000019},
  {0x0000001A, 0x0000001A},
  {0x0000001B, 0x0000001B}
};

CONST DEVICE_IDS ROMDATA  SspPieMap [] = {
  {0x0000001E, 0x0000001E}
};

CONST DEVICE_IDS ROMDATA  SspCakeMap [] = {
  {0xFFFFFFFF, 0x0000001F},
  {0xFFFFFFFF, 0x00000020},
  {0xFFFFFFFF, 0x00000021},
  {0xFFFFFFFF, 0x00000022},
  {0xFFFFFFFF, 0x00000023},
  {0xFFFFFFFF, 0x00000024}
};

CONST DEVICE_IDS ROMDATA  SspTcdxMap [] = {
  {0xFFFFFFFF, 0x00000025},
  {0xFFFFFFFF, 0x00000026},
  {0xFFFFFFFF, 0x00000027},
  {0xFFFFFFFF, 0x00000028},
  {0xFFFFFFFF, 0x00000029},
  {0xFFFFFFFF, 0x0000002A},
  {0xFFFFFFFF, 0x0000002B},
  {0xFFFFFFFF, 0x0000002C},
  {0xFFFFFFFF, 0x0000002D},
  {0xFFFFFFFF, 0x0000002E},
  {0xFFFFFFFF, 0x0000002F},
  {0xFFFFFFFF, 0x00000030}
};

CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP ROMDATA SspDeviceMap[] = {
  {Cs,     (UINTN) (sizeof (SspCsMap) / sizeof (SspCsMap[0])),         &SspCsMap[0]},
  {Ccm,    (UINTN) (sizeof (SspCcmMap) / sizeof (SspCcmMap[0])),       &SspCcmMap[0]},
  {Ioms,   (UINTN) (sizeof (SspIomsMap) / sizeof (SspIomsMap[0])),     &SspIomsMap[0]},
  {Pie,    (UINTN) (sizeof (SspPieMap) / sizeof (SspPieMap[0])),       &SspPieMap[0]},
  {Cake,   (UINTN) (sizeof (SspCakeMap) / sizeof (SspCakeMap[0])),     &SspCakeMap[0]},
  {Tcdx,   (UINTN) (sizeof (SspTcdxMap) / sizeof (SspTcdxMap[0])),     &SspTcdxMap[0]},
  {CsUmc,  (UINTN) (sizeof (SspCsUmcMap) / sizeof (SspCsUmcMap[0])),   &SspCsUmcMap[0]},
  {CsCcix, (UINTN) (sizeof (SspCsCcixMap) / sizeof (SspCsCcixMap[0])), &SspCsCcixMap[0]},
  {FabricDeviceTypeMax, 0, NULL}
};

CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP ROMDATA CpDeviceMap[] = {
  {Cs,     (UINTN) (sizeof (SspCsMap) / sizeof (SspCsMap[0])),         &SspCsMap[0]},
  {Ccm,    (UINTN) (sizeof (SspCcmMap) / sizeof (SspCcmMap[0])),       &SspCcmMap[0]},
  {Ioms,   (UINTN) (sizeof (CpIomsMap) / sizeof (CpIomsMap[0])),       &CpIomsMap[0]},
  {Pie,    (UINTN) (sizeof (SspPieMap) / sizeof (SspPieMap[0])),       &SspPieMap[0]},
  {Cake,   (UINTN) (sizeof (SspCakeMap) / sizeof (SspCakeMap[0])),     &SspCakeMap[0]},
  {Tcdx,   (UINTN) (sizeof (SspTcdxMap) / sizeof (SspTcdxMap[0])),     &SspTcdxMap[0]},
  {CsUmc,  (UINTN) (sizeof (SspCsUmcMap) / sizeof (SspCsUmcMap[0])),   &SspCsUmcMap[0]},
  {CsCcix, (UINTN) (sizeof (SspCsCcixMap) / sizeof (SspCsCcixMap[0])), &SspCsCcixMap[0]},
  {FabricDeviceTypeMax, 0, NULL}
};

//
// MTS IOD
//
CONST UINTN ROMDATA MtsPhysIoms0FabricId = 0x18;

CONST COMPONENT_LOCATION ROMDATA MtsComponentLocation [] = {
  {0, 0, 4, PrimaryFch}, // Physcial location, Socket 0, Die 0, Ioms0
  {0, 0, 4, PrimarySmu}, // Physcial location, Socket 0, Die 0, Ioms0
};

CONST DEVICE_IDS ROMDATA  MtsCsMap [] = {
  {0x00000000, 0x00000000},
  {0x00000001, 0x00000001}
};

CONST DEVICE_IDS ROMDATA  MtsCcmMap [] = {
  {0x00000002, 0x00000002},
  {0x00000003, 0x00000003}
};

CONST DEVICE_IDS ROMDATA  MtsIomsMap [] = {
  {0x00000004, 0x00000004}
};

CONST DEVICE_IDS ROMDATA  MtsPieMap [] = {
  {0x00000005, 0x00000005}
};

CONST DEVICE_IDS ROMDATA  MtsTcdxMap [] = {
  {0xFFFFFFFF, 0x00000006},
  {0xFFFFFFFF, 0x00000007}
};

CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP ROMDATA MtsDeviceMap[] = {
  {Cs,     (UINTN) (sizeof (MtsCsMap) / sizeof (MtsCsMap[0])),         &MtsCsMap[0]},
  {Ccm,    (UINTN) (sizeof (MtsCcmMap) / sizeof (MtsCcmMap[0])),       &MtsCcmMap[0]},
  {Ioms,   (UINTN) (sizeof (MtsIomsMap) / sizeof (MtsIomsMap[0])),     &MtsIomsMap[0]},
  {Pie,    (UINTN) (sizeof (MtsPieMap) / sizeof (MtsPieMap[0])),       &MtsPieMap[0]},
  {Tcdx,   (UINTN) (sizeof (MtsTcdxMap) / sizeof (MtsTcdxMap[0])),     &MtsTcdxMap[0]},
  {FabricDeviceTypeMax, 0, NULL}
};


UINTN
FabricTopologyGetNumberOfProcessorsPresent (
  VOID
  )
{
  SYS_CFG_REGISTER  SysCfg;

  SysCfg.Value = FabricRegisterAccRead (0, 0, SYSCFG_FUNC, SYSCFG_REG, FABRIC_REG_ACC_BC);

  return (UINTN) (SysCfg.Field.OtherSocketPresent + 1);
}

UINTN
FabricTopologyGetNumberOfSystemDies (
  VOID
  )
{
  SYS_COMP_COUNT_REGISTER  SystemCompCount;

  SystemCompCount.Value = FabricRegisterAccRead (0, 0, SYSCOMPCOUNT_FUNC, SYSCOMPCOUNT_REG, FABRIC_REG_ACC_BC);

  return (UINTN) SystemCompCount.Field.PIECount;
}

UINTN
FabricTopologyGetNumberOfSystemRootBridges (
  VOID
  )
{
  SYS_COMP_COUNT_REGISTER  SystemCompCount;

  SystemCompCount.Value = FabricRegisterAccRead (0, 0, SYSCOMPCOUNT_FUNC, SYSCOMPCOUNT_REG, FABRIC_REG_ACC_BC);

  return (UINTN) SystemCompCount.Field.IOMCount;
}

UINTN
FabricTopologyGetNumberOfDiesOnSocket (
  IN       UINTN Socket
  )
{
  return 1;
}

UINTN
FabricTopologyGetNumberOfRootBridgesOnSocket (
  IN       UINTN Socket
  )
{
  UINTN                    RbCount;
  SYS_COMP_COUNT_REGISTER  SystemCompCount;

  SystemCompCount.Value = FabricRegisterAccRead (Socket, 0, SYSCOMPCOUNT_FUNC, SYSCOMPCOUNT_REG, FABRIC_REG_ACC_BC);
  RbCount = (UINTN) DivU64x32 (SystemCompCount.Field.IOMCount, (UINT32) FabricTopologyGetNumberOfProcessorsPresent ());
  return (UINTN) RbCount;
}

UINTN
FabricTopologyGetNumberOfRootBridgesOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  UINTN                    RbCount;
  SYS_COMP_COUNT_REGISTER  SystemCompCount;

  SystemCompCount.Value = FabricRegisterAccRead (Socket, 0, SYSCOMPCOUNT_FUNC, SYSCOMPCOUNT_REG, FABRIC_REG_ACC_BC);
  RbCount = (UINTN) DivU64x32 (SystemCompCount.Field.IOMCount, (UINT32) FabricTopologyGetNumberOfProcessorsPresent ());
  RbCount = (UINTN) DivU64x32 (RbCount, (UINT32) FabricTopologyGetNumberOfDiesOnSocket (Socket));

  return (UINTN) RbCount;
}

UINTN
FabricTopologyGetDieSystemOffset (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  return (Socket << 5);
}

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FabricTopologyGetDeviceMapOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  UINT32  PackageId;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *DeviceMap;

  PackageId = LibAmdGetPackageType (NULL);

  if (PackageId == (1 << SSP_SOCKET_AM4)) {
    DeviceMap = &MtsDeviceMap[0];
  } else if (PackageId == (1 << SSP_SOCKET_SP3r2)) {
    DeviceMap = &CpDeviceMap[0];
  } else {
    DeviceMap = &SspDeviceMap[0];
  }
  return DeviceMap;
}

UINTN
FabricTopologyGetHostBridgeSystemFabricID (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;

  IomsEntry = FindDeviceTypeEntryInMap (Socket, Die, Ioms);
  ASSERT (IomsEntry != NULL);

  ASSERT (Index < IomsEntry->Count);
  return (FabricTopologyGetDieSystemOffset (Socket, Die) + IomsEntry->IDs[Index].FabricID);
}

UINTN
FabricTopologyGetHostBridgeBusBase (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  CFG_ADDRESS_CTRL_REGISTER                  CfgAddrCtrl;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;

  IomsEntry = FindDeviceTypeEntryInMap (Socket, Die, Ioms);
  ASSERT (IomsEntry != NULL);

  ASSERT (Index < IomsEntry->Count);
  CfgAddrCtrl.Value = FabricRegisterAccRead (Socket, Die, CFGADDRESSCTRL_FUNC, CFGADDRESSCTRL_REG, IomsEntry->IDs[Index].InstanceID);
  return (UINTN) (CfgAddrCtrl.Field.SecBusNum);
}

UINTN
FabricTopologyGetHostBridgeBusLimit (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  UINTN                                      BusLimit;
  UINTN                                      CfgAddrMapIndex;
  UINTN                                      TargetFabricId;
  CFG_ADDRESS_MAP_REGISTER                   BusMap;

  TargetFabricId = FabricTopologyGetHostBridgeSystemFabricID (Socket, Die, Index);

  BusLimit = 0xFF;
  for (CfgAddrMapIndex = 0; CfgAddrMapIndex < SSP_NUMBER_OF_BUS_REGIONS; CfgAddrMapIndex++) {
    BusMap.Value = FabricRegisterAccRead (0, 0, CFGADDRESSMAP_FUNC, (CFGADDRESSMAP0_REG + (CfgAddrMapIndex * SSP_BUS_REGION_REGISTER_OFFSET)), FABRIC_REG_ACC_BC);
    if ((BusMap.Field.RE == 1) && (BusMap.Field.WE == 1) && (BusMap.Field.DstFabricID == (UINT32) TargetFabricId)) {
      BusLimit = (UINTN) BusMap.Field.BusNumLimit;
      break;
    }
  }

  return BusLimit;
}

BOOLEAN
FabricTopologyGetSystemComponentRootBridgeLocation (
  IN       COMPONENT_TYPE Component,
  IN OUT   ROOT_BRIDGE_LOCATION *Location
  )
{
  UINTN   i;
  UINTN   j;
  UINTN   Count;
  BOOLEAN Found;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;
  CONST COMPONENT_LOCATION                  *ComponentLocation;

  ASSERT ((Component == PrimaryFch) || (Component == PrimarySmu));

  ComponentLocation = FindComponentLocationMap (&Count, NULL);

  Found = FALSE;
  for (i = 0; i < Count; i++) {
    if (ComponentLocation[i].Type == Component) {
      Location->Socket = ComponentLocation[i].Socket;
      Location->Die = ComponentLocation[i].Die;

      IomsEntry = FindDeviceTypeEntryInMap (Location->Socket, Location->Die, Ioms);
      for (j = 0; j < (IomsEntry->Count); j++) {
        if (IomsEntry->IDs[j].FabricID == ComponentLocation[i].IomsFabricId) {
          Location->Index = j;
          break;
        }
      }
      ASSERT (j < IomsEntry->Count);
      Found = TRUE;
      break;
    }
  }
  return Found;
}

BOOLEAN
FabricTopologyHasFch (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  UINTN   i;
  UINTN   Count;
  UINTN   IomsFabricId;
  UINTN   Ioms0FabricId;
  BOOLEAN Found;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;
  CONST COMPONENT_LOCATION                  *ComponentLocation;

  IomsEntry = FindDeviceTypeEntryInMap (Socket, Die, Ioms);
  IomsFabricId = IomsEntry->IDs[Index].FabricID;

  ComponentLocation = FindComponentLocationMap (&Count, &Ioms0FabricId);

  Found = FALSE;
  for (i = 0; i < Count; i++) {
    if ((ComponentLocation[i].Type < FchTypeMax) &&
        (Socket == ComponentLocation[i].Socket) &&
        (Die == ComponentLocation[i].Die) &&
        (IomsFabricId == ComponentLocation[i].IomsFabricId)) {
      Found = TRUE;
      break;
    }
  }
  return Found;
}

BOOLEAN
FabricTopologyHasSmu (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  UINTN   i;
  UINTN   Count;
  UINTN   IomsFabricId;
  UINTN   Ioms0FabricId;
  BOOLEAN Found;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;
  CONST COMPONENT_LOCATION                  *ComponentLocation;

  IomsEntry = FindDeviceTypeEntryInMap (Socket, Die, Ioms);
  IomsFabricId = IomsEntry->IDs[Index].FabricID;

  ComponentLocation = FindComponentLocationMap (&Count, &Ioms0FabricId);

  Found = FALSE;

  for (i = 0; i < Count; i++) {
    if ((ComponentLocation[i].Type < SmuTypeMax) &&
        (ComponentLocation[i].Type > FchTypeMax) &&
        (Socket == ComponentLocation[i].Socket) &&
        (Die == ComponentLocation[i].Die) &&
        (IomsFabricId == ComponentLocation[i].IomsFabricId)) {
      Found = TRUE;
      break;
    }
  }

  return Found;
}

UINTN
FabricTopologyGetPhysRootBridgeNumber (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  UINTN  FabricId;
  UINTN  PhysNumber;
  UINT32 PackageId;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;

  PackageId = LibAmdGetPackageType (NULL);

  if (PackageId == (1 << SSP_SOCKET_AM4)) {
    PhysNumber = 0;
  } else {
    IomsEntry = FindDeviceTypeEntryInMap (Socket, Die, Ioms);
    FabricId = IomsEntry->IDs[Index].FabricID;

    ASSERT (FabricId >= SspPhysIoms0FabricId);
    PhysNumber = FabricId - SspPhysIoms0FabricId;
  }

  return PhysNumber;
}

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FindDeviceTypeEntryInMap (
  IN       UINTN               Socket,
  IN       UINTN               Die,
  IN       FABRIC_DEVICE_TYPE  Type
  )
{
  UINTN                                      i;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *DeviceMap;

  DeviceMap = FabricTopologyGetDeviceMapOnDie (Socket, Die);
  for (i = 0; DeviceMap[i].Type < FabricDeviceTypeMax; i++) {
    if (DeviceMap[i].Type == Type) {
      break;
    }
  }

  if (DeviceMap[i].Type == Type) {
    return &DeviceMap[i];
  } else {
    return NULL;
  }
}


CONST
COMPONENT_LOCATION *
FindComponentLocationMap (
  IN       UINTN *Count,
  IN       UINTN *PhysIoms0FabricId
  )
{
  UINT32  PackageId;
  CONST COMPONENT_LOCATION *ComponentLocationMap;

  PackageId = LibAmdGetPackageType (NULL);

  if (PackageId == (1 << SSP_SOCKET_AM4)) {
    ComponentLocationMap = &MtsComponentLocation[0];
    if (Count != NULL) {
      *Count = sizeof (MtsComponentLocation) / sizeof (MtsComponentLocation[0]);
    }
    if (PhysIoms0FabricId != NULL) {
      *PhysIoms0FabricId = MtsPhysIoms0FabricId;
    }
  } else {
    ComponentLocationMap = &SspComponentLocation[0];
    if (Count != NULL) {
      *Count = sizeof (SspComponentLocation) / sizeof (SspComponentLocation[0]);
    }
    if (PhysIoms0FabricId != NULL) {
      *PhysIoms0FabricId = SspPhysIoms0FabricId;
    }
  }
  return ComponentLocationMap;
}


