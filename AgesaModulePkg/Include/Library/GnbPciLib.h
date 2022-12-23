/* $NoKeywords:$ */
/**
 * @file
 *
 * Various PCI service routines.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
*****************************************************************************
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

#ifndef _GNBLIBPCI_H_
#define _GNBLIBPCI_H_

#include "Porting.h"

///
/// Basic PCIe configuration space defines and structures
///

/// Type 0 and 1 config space offsets
#define PCICFG_SPACE_VID_OFFSET                   0x00
#define PCICFG_SPACE_DID_OFFSET                   0x02
#define PCICFG_SPACE_COMMAND_OFFSET               0x04
#define PCICFG_SPACE_STATUS_OFFSET                0x06
#define PCICFG_SPACE_REV_ID_OFFSET                0x08
#define PCICFG_SPACE_CLASS_CODE_OFFSET            0x09
#define PCICFG_SPACE_CACHE_LINE_SIZE_OFFSET       0x0C
#define PCICFG_SPACE_MASTER_LATENY_OFFSET         0x0D
#define PCICFG_SPACE_HEADER_TYPE_OFFSET           0x0E
#define PCICFG_SPACE_BIST_OFFSET                  0x0F
#define PCICFG_SPACE_CAPABILITIES_PTR_OFFSET      0x34
#define PCICFG_SPACE_INTERRUPT_LINE_OFFSET        0x3C
#define PCICFG_SPACE_INTERRUPT_PIN_OFFSET         0x3D

/// Type 0 config space offsets
#define PCICFG_SPACE_SUBSYSTEM_VID_OFFSET         0x2C
#define PCICFG_SPACE_SUBSYSTEM_ID_OFFSET          0x2E
#define PCICFG_SPACE_EXPANSION_ROM_BAR_OFFSET     0x30

/// Type 1 config space offsets
#define PCICFG_SPACE_BAR0_OFFSET                  0x10
#define PCICFG_SPACE_BAR1_OFFSET                  0x14
#define PCICFG_SPACE_PRIMARY_BUS_OFFSET           0x18
#define PCICFG_SPACE_SECONDARY_BUS_OFFSET         0x19
#define PCICFG_SPACE_SUBORDINATE_BUS_OFFSET       0x1A
#define PCICFG_SPACE_SEC_LATENCY_TIMER_OFFSET     0x1B
#define PCICFG_SPACE_IO_BASE_OFFSET               0x1C
#define PCICFG_SPACE_IO_LIMIT_OFFSET              0x1D
#define PCICFG_SPACE_SECONDARY_STATUS_OFFSET      0x1E
#define PCICFG_SPACE_MEMORY_BASE_OFFSET           0x20
#define PCICFG_SPACE_MEMORY_LIMIT_OFFSET          0x22
#define PCICFG_SPACE_PREFETCH_HIGH_OFFSET         0x28
#define PCICFG_SPACE_PREFETCH_LOW_OFFSET          0x2C
#define PCICFG_SPACE_BRIDGE_CONTROL_OFFSET        0x3E

/// As we need them, flesh out these PCIE Configuration status structures. No longer use hardcodes
typedef union {
  struct {
    UINT8     ParityErrorResponseEnable:1;
    UINT8     SerrEnable:1;
    UINT8     Reserved0:3;
    UINT8     MasterAbortMode:1;
    UINT8     SecondaryBusReset:1;
    UINT8     FastBackToBackTransactionEn:1;
    UINT8     PrimaryDiscardTimer:1;
    UINT8     SecondaryDiscardTimer:1;
    UINT8     DiscardTimerStatus:1;
    UINT8     DiscardTimerSerrEn:1;
    UINT8     Reserved1:4;
  } Field;
  UINT16 Value;
} PCICFG_SPACE_BRIDGE_CONTROL_STRUCT;


///
/// PCIe capibilities defines and structures
///
#define PCIE_EXT_AER_CAP_ID         0x01
#define DPC_EXT_CAP_ID              0x1D
#define PCIE_EXT_CAP_ID             0x1E
#define PCIE_LTR_EXT_CAP_ID         0x18
#define PCIE_CAP_ID                 0x10
#define IOMMU_CAP_ID                0x0F
#define ARI_CAP_ID                  0x0E

/// PCIe device type
typedef enum {
  PcieDeviceEndPoint,                       ///< Endpoint
  PcieDeviceLegacyEndPoint,                 ///< Legacy endpoint
  PcieDeviceRootComplex = 4,                ///< Root complex
  PcieDeviceUpstreamPort,                   ///< Upstream port
  PcieDeviceDownstreamPort,                 ///< Downstream Port
  PcieDevicePcieToPcix,                     ///< PCIe to PCI/PCIx bridge
  PcieDevicePcixToPcie,                     ///< PCI/PCIx to PCIe bridge
  PcieNotPcieDevice = 0xff                  ///< unknown device
} PCIE_DEVICE_TYPE;

typedef  UINT32 SCAN_STATUS;

#define SCAN_SKIP_FUNCTIONS         0x1
#define SCAN_SKIP_DEVICES           0x2
#define SCAN_SKIP_BUSES             0x4
#define SCAN_SUCCESS                0x0

//  Forward declaration needed for multi-structure mutual references
AGESA_FORWARD_DECLARATION (GNB_PCI_SCAN_DATA);

typedef SCAN_STATUS (*GNB_SCAN_CALLBACK) (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  );

///Scan supporting data
struct _GNB_PCI_SCAN_DATA {
  GNB_SCAN_CALLBACK     GnbScanCallback;  ///< Callback for each found device
  AMD_CONFIG_PARAMS     *StdHeader;       ///< Standard configuration header
};

#define   PCIE_CAP_ID                0x10
#define   PCIE_LINK_CAP_REGISTER     0x0C
#define   PCIE_LINK_CTRL_REGISTER    0x10
#define   PCIE_DEVICE_CAP_REGISTER   0x04
#define   PCIE_DEVICE_CTRL_REGISTER  0x08
#define   PCIE_LINK_STATUS_REGISTER  0x12
#define   PCIE_DEVICE_CAP2_REGISTER  0x24
#define   PCIE_DEVICE_CNTL2_REGISTER 0x28
#define   PCIE_ASPM_L1_SUPPORT_CAP   BIT11
#define   PCIE_SLOT_CAP_REGISTER     0x14

/// As we need them, flesh out these PCIE capabilities structures. No longer use hardcodes
typedef union {
  struct {
    UINT8     CorrectableErrorReportingEn:1;
    UINT8     NonFatalErrorReportingEn:1;
    UINT8     FatalErrorReportingEn:1;
    UINT8     UnsupportedReqReportingEn:1;
    UINT8     UnsupportedReqSeverity:1;
    UINT8     MaxPayloadSize:3;
    UINT8     ExtendedTagFieldEn:1;
    UINT8     PhantomFunctionsEn:1;
    UINT8     AuxPowerPmEnable:1;
    UINT8     DevCtrlStop:1;
    UINT8     MaxReadReqSize:3;
    UINT8     Reserved0:1;
  } Field;
  UINT16 Value;
} PCIE_DEVICE_CTRL_REGISTER_STRUCT;

typedef union {
  struct {
  UINT8       LinkSpeed:4;
  UINT8       LinkWidth:6;
  UINT8       LinkTrainingError:1;
  UINT8       LinkTraining:1;
  UINT8       SlotClockConfig:1;
  UINT8       Reserved0:3;
  } Field;
  UINT16 Value;
} PCIE_LINK_STATUS_REGISTER_STRUCT;

#define MAX_PAYLOAD_128             0x0     ///< Max allowed payload size 128 bytes
#define MAX_PAYLOAD_256             0x1     ///< Max allowed payload size 256 bytes
#define MAX_PAYLOAD_512             0x2     ///< Max allowed payload size 512 bytes
#define MAX_PAYLOAD_1024            0x3     ///< Max allowed payload size 1024 bytes
#define MAX_PAYLOAD_2048            0x4     ///< Max allowed payload size 2048 bytes
#define MAX_PAYLOAD_4096            0x5     ///< Max allowed payload size 4096 bytes
#define MAX_PAYLOAD                 0x5     ///< Max allowed payload size according to spec is 101b (4096 bytes)

#define MAX_READREQUESTSIZE_128     0x0     ///< Max allowed read request size 128 bytes
#define MAX_READREQUESTSIZE_256     0x1     ///< Max allowed read request size 256 bytes
#define MAX_READREQUESTSIZE_512     0x2     ///< Max allowed read request size 512 bytes
#define MAX_READREQUESTSIZE_1024    0x3     ///< Max allowed read request size 1024 bytes
#define MAX_READREQUESTSIZE_2048    0x4     ///< Max allowed read request size 2048 bytes
#define MAX_READREQUESTSIZE_4096    0x5     ///< Max allowed read request size 4096 bytes




BOOLEAN
GnbLibPciIsDevicePresent (
  IN      UINT32              Address,
  IN      AMD_CONFIG_PARAMS   *StdHeader
 );

BOOLEAN
GnbLibPciIsBridgeDevice (
  IN      UINT32              Address,
  IN      AMD_CONFIG_PARAMS   *StdHeader
 );

BOOLEAN
GnbLibPciIsMultiFunctionDevice (
  IN      UINT32              Address,
  IN      AMD_CONFIG_PARAMS   *StdHeader
 );

BOOLEAN
GnbLibPciIsPcieDevice (
  IN      UINT32              Address,
  IN      AMD_CONFIG_PARAMS   *StdHeader
 );

UINT8
GnbLibFindPciCapability (
  IN      UINT32              Address,
  IN      UINT8               CapabilityId,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

UINT16
GnbLibFindPcieExtendedCapability (
  IN      UINT32              Address,
  IN      UINT16              ExtendedCapabilityId,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
GnbLibPciScan (
  IN      PCI_ADDR            Start,
  IN      PCI_ADDR            End,
  IN      GNB_PCI_SCAN_DATA   *ScanData
 );

VOID
GnbLibPciScanSecondaryBus (
  IN       PCI_ADDR             Bridge,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  );

PCIE_DEVICE_TYPE
GnbLibGetPcieDeviceType (
  IN      PCI_ADDR            Device,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
GnbLibS3SaveConfigSpace (
  IN      UINT32              Address,
  IN      UINT16              StartRegisterAddress,
  IN      UINT16              EndRegisterAddress,
  IN      ACCESS_WIDTH        Width,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

#endif

