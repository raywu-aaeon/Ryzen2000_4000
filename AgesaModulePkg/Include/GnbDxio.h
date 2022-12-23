/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe component definitions.
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

#ifndef _GNBDXIO_H_
#define _GNBDXIO_H_

#pragma pack (push, 1)

#include <AGESA.h>
#include <Gnb.h>

#define MAX_NUMBER_OF_COMPLEXES                8

#define DESCRIPTOR_TERMINATE_GNB               0x40000000ull
#define DESCRIPTOR_TERMINATE_TOPOLOGY          0x20000000ull
#define DESCRIPTOR_ALLOCATED                   0x10000000ull
#define DESCRIPTOR_PLATFORM                    0x08000000ull
#define DESCRIPTOR_COMPLEX                     0x04000000ull
#define DESCRIPTOR_SILICON                     0x02000000ull
#define DESCRIPTOR_PCIE_WRAPPER                0x01000000ull
#define DESCRIPTOR_PCIE_ENGINE                 0x00800000ull
#define DESCRIPTOR_DDI_ENGINE                  0x00400000ull

#define DESCRIPTOR_ALL_WRAPPERS                (DESCRIPTOR_PCIE_WRAPPER)
#define DESCRIPTOR_ALL_ENGINES                 (DESCRIPTOR_PCIE_ENGINE)

#define DESCRIPTOR_ALL_TYPES                   (DESCRIPTOR_ALL_WRAPPERS | DESCRIPTOR_ALL_ENGINES | DESCRIPTOR_SILICON | DESCRIPTOR_PLATFORM)

#define UNUSED_LANE_ID                         255

/// PCIe Link Training State
typedef enum {
  LinkStateResetAssert,                                 ///< Assert port GPIO reset
  LinkStateResetDuration,                               ///< Timeout for reset duration
  LinkStateResetExit,                                   ///< Deassert port GPIO reset
  LinkTrainingResetTimeout,                             ///< Port GPIO reset timeout
  LinkStateReleaseTraining,                             ///< Release link training
  LinkStateDetectPresence,                              ///< Detect device presence
  LinkStateDetecting,                                   ///< Detect link training.
  LinkStateBrokenLane,                                  ///< Check and handle broken lane
  LinkStateGen2Fail,                                    ///< Check and handle device that fail training if GEN2 capability advertised
  LinkStateL0,                                          ///< Device trained to L0
  LinkStateVcoNegotiation,                              ///< Check VCO negotiation complete
  LinkStateRetrain,                                     ///< Force retrain link.
  LinkStateTrainingFail,                                ///< Link training fail
  LinkStateTrainingSuccess,                             ///< Link training success
  LinkStateGfxWorkaround,                               ///< GFX workaround
  LinkStateCompliance,                                  ///< Link in compliance mode
  LinkStateDeviceNotPresent,                            ///< Link is not connected
  LinkStateTrainingCompleted                            ///< Link training completed
} PCIE_LINK_TRAINING_STATE;

/// PCIe PSPP Power policy
typedef enum  {
  AgesaPsppDisabled,                                           ///< PSPP disabled
  AgesaPsppPerformance = 1,                                    ///< Performance
  AgesaPsppBalance,                                            ///< Balance
  AgesaPsppPowerSaving,                                        ///< Power Saving
  AgesaMaxPspp                                                 ///< Max Pspp for boundary check
} PCIE_PSPP_POLICY;


#define INIT_STATUS_PCIE_PORT_GEN2_RECOVERY          0x00000001ull
#define INIT_STATUS_PCIE_PORT_BROKEN_LANE_RECOVERY   0x00000002ull
#define INIT_STATUS_PCIE_PORT_TRAINING_FAIL          0x00000004ull
#define INIT_STATUS_PCIE_TRAINING_SUCCESS            0x00000008ull
#define INIT_STATUS_PCIE_EP_NOT_PRESENT              0x00000010ull
#define INIT_STATUS_PCIE_PORT_IN_COMPLIANCE          0x00000020ull
#define INIT_STATUS_DDI_ACTIVE                       0x00000040ull
#define INIT_STATUS_ALLOCATED                        0x00000080ull
#define INIT_STATUS_PCIE_PORT_BROKEN_LANE_X1         0x00000100ull

// Get lowest PHY lane on engine
#define PcieLibGetLoPhyLane(Engine) (Engine != NULL ? ((Engine->EngineData.StartLane > Engine->EngineData.EndLane) ? Engine->EngineData.EndLane : Engine->EngineData.StartLane) : 0)
// Get highest PHY lane on engine
#define PcieLibGetHiPhyLane(Engine) (Engine != NULL ? ((Engine->EngineData.StartLane > Engine->EngineData.EndLane) ? Engine->EngineData.StartLane : Engine->EngineData.EndLane) : 0)
// Get number of lanes on wrapper
#define PcieLibWrapperNumberOfLanes(Wrapper) (Wrapper != NULL ? ((UINT8)(Wrapper->EndPhyLane - Wrapper->StartPhyLane + 1)) : 0)
// Check if virtual descriptor
#define PcieLibIsEngineAllocated(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_ALLOCATED) != 0) : FALSE)
// Check if it is last descriptor in list
#define PcieLibIsLastDescriptor(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_TERMINATE_LIST) != 0) : TRUE)
// Check if descriptor a PCIe engine
#define PcieLibIsPcieEngine(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_PCIE_ENGINE) != 0) : FALSE)
// Check if descriptor a DDI engine
#define PcieLibIsPcieWrapper(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_PCIE_WRAPPER) != 0) : FALSE)
// Check if descriptor a PCIe wrapper
#define PcieLibGetNextDescriptor(Descriptor) (Descriptor != NULL ? (((Descriptor->Header.DescriptorFlags & DESCRIPTOR_TERMINATE_LIST) != 0) ? NULL : ((Descriptor) + 1)) : NULL)

// PCIe functions to avoid hardcoding these values where they are used
#define PCIE_FUNCTION0  0
#define PCIE_FUNCTION1  1
#define PCIE_FUNCTION2  2
#define PCIE_FUNCTION3  3
#define PCIE_FUNCTION4  4
#define PCIE_FUNCTION5  5
#define PCIE_FUNCTION6  6
#define PCIE_FUNCTION7  7

/// PCIe port State
typedef enum {
  UnhidePorts,                                          ///< Command to unhide port
  HidePorts,                                            ///< Command to hide unused ports
} PCIE_PORT_VISIBILITY;

/// Table Register Entry
typedef struct {
  UINT16          Reg;                                  ///< Address
  UINT32          Mask;                                 ///< Mask
  UINT32          Data;                                 ///< Data
} PCIE_PORT_REGISTER_ENTRY;

/// Table Register Entry
typedef struct {
  PCIE_PORT_REGISTER_ENTRY  *Table;                     ///< Table
  UINT32                    Length;                     ///< Length
} PCIE_PORT_REGISTER_TABLE_HEADER;

/// Table Register Entry
typedef struct {
  UINT32          Reg;                                  ///< Address
  UINT32          Mask;                                 ///< Mask
  UINT32          Data;                                 ///< Data
} PCIE_HOST_REGISTER_ENTRY;

/// Table Register Entry
typedef struct {
  PCIE_HOST_REGISTER_ENTRY  *Table;                     ///< Table
  UINT32                    Length;                     ///< Length
} PCIE_HOST_REGISTER_TABLE_HEADER;

///Link ASPM info
typedef struct {
  PCI_ADDR        DownstreamPort;                       ///< PCI address of downstream port
  PCIE_ASPM_TYPE  DownstreamAspm;                       ///< Downstream Device Aspm
  PCI_ADDR        UpstreamPort;                         ///< PCI address of upstream port
  PCIE_ASPM_TYPE  UpstreamAspm;                         ///< Upstream Device Capability
  PCIE_ASPM_TYPE  RequestedAspm;                        ///< Requested ASPM
  BOOLEAN         BlackList;                            ///< Blacklist device
} PCIe_LINK_ASPM;

///PCIe ASPM Latency Information
typedef struct {
  UINT8  MaxL0sExitLatency;                             ///< Max L0s exit latency in us
  UINT8  MaxL1ExitLatency;                              ///< Max L1 exit latency in us
} PCIe_ASPM_LATENCY_INFO;

/// PCI address association
typedef struct {
  UINT8 NewDeviceAddress;                                ///< New PCI address (Device,Fucntion)
  UINT8 NativeDeviceAddress;                             ///< Native PCI address (Device,Fucntion)
} PCI_ADDR_LIST;

typedef UINT16 PCIe_ENGINE_INIT_STATUS;

/// PCIe port configuration info
typedef struct {
  PCIe_PORT_DATA          PortData;                     ///< Port data
  UINT8                   StartCoreLane;                ///< Start Core Lane
  UINT8                   EndCoreLane;                  ///< End Core lane
  UINT8                   NativeDevNumber :5;           ///< Native PCI device number of the port
  UINT8                   NativeFunNumber :3;           ///< Native PCI function number of the port
  UINT8                   CoreId :4;                    ///< PCIe core ID
  UINT8                   PortId :4;                    ///< Port ID on wrapper
  PCI_ADDR                Address;                      ///< PCI address of the port
//  UINT8                   State;                        ///< Training state
  UINT8                   PcieBridgeId:4;               ///< IOC PCIe bridge ID
//  UINT16                  UnitId:12;                    ///< Port start unit ID
//  UINT16                  NumberOfUnitId:4;             ///< Def number of unitIDs assigned to port
  UINT8                   GfxWrkRetryCount:4;           ///< Number of retry for GFX workaround
  UINT8                   LogicalBridgeId;              ///< Logical Bridge ID
  UINT8                   PowerOffUnusedLanesPLL:1;     ///< Power Off unused lanes and PLL
  UINT8                   PowerOffPhyLanesPllL1:1;      ///< Power Off Phy Lanes and Pll in L1
  UINT8                   DynamicLanesPowerState:6;     ///< Dynamic Lanes Power State for Linkwidth Switch
  UINT8                   SlotPowerLimit;               ///< Slot Power Limit
  UINT8                   MaxPayloadSize;               ///< Max_Payload_Size
  UINT8                   L1ImmediateACK:1;             ///< L1 Immediate ACK
  UINT8                   TXDeEmphasis:4;               ///< TX De-emphasis
  UINT8                   TXMargin:3;                   ///< TX Margin
  UINT8                   ScramblerCntl:1;              ///< Scrambler control
  UINT8                   EqSearchMode:2;               ///< Equalization Search Mode
  UINT8                   DisGen3EQPhase:1;             ///< Disable Gen3 EQ Phase2/3
  UINT8                   LinkAspmL1_1:1;               ///< Enable PM L1 SS L1.1
  UINT8                   LinkAspmL1_2:1;               ///< Enable PM L1 SS L1.2
  UINT8                   SlotPowerLimitScale:2;        ///< Slot Power Limit Scale
  UINT8                   ClkReq:4;                     ///< ClkReq:[0:3]
  UINT8                   EqPreset:4;                   ///< EqPreset:[4:7]
  struct {
    UINT8                 NonPostedHeader;              ///< Non-Posted Header
    UINT8                 NonPostedData;                ///< Non-Posted Data
    UINT8                 PostedHeader;                 ///< Posted Header
    UINT8                 PostedData;                   ///< Posted Data
    UINT8                 CompletionHeader;             ///< Completion Header
    UINT8                 CompletionData;               ///< Completion Data
  } FlowCntlCredits;
  struct {
    UINT8                 SpcGen1:1;                    ///< SPC Mode 2P5GT
    UINT8                 SpcGen2:1;                    ///< SPC Mode 5GT
    UINT8                 SpcGen3:1;                    ///< SPC Mode 8GT
  } SpcMode;
  struct {
    UINT16                DsTxPreset:4;                 ///< Gen3 Downstream Tx Preset
    UINT16                DsRxPresetHint:3;             ///< Gen3 Downstream Rx Preset Hint
    UINT16                UsTxPreset:4;                 ///< Gen3 Upstream Tx Preset
    UINT16                UsRxPresetHint:3;             ///< Gen3 Upstream Rx Preset Hint
  } LaneEqualizationCntl;
  UINT8                   LcFomTime;                    ///< Figure of Merit time
  UINT8                   PortReversal:1;               ///< PortReversal
  UINT8                   BypassGen3EQ:1;               ///< BypassGen3EQ
  UINT8                   Enable3x3Search:1;            ///< Enable3x3Search
  UINT8                   EnableSafeSearch:1;           ///< EnableSafeSearch
  UINT8                   SRIS_SRNS:1;                  ///< SRIS SRNS
  UINT8                   SRIS_En:1;                    ///< SRIS Enable
  UINT8                   SRIS_AutoDetectEn:1;          ///< SRIS Auto Detect Enable
  UINT8                   SRIS_LowerSKPSupport:1;       ///< SRIS Lower SKP Support
  struct {
    UINT8                DsTxPreset:4;                  ///< Gen4 Downstream Tx Preset
    UINT8                UsTxPreset:4;                  ///< Gen4 Upstream Tx Preset
  } Gen4LaneEqualizationCntl;
  UINT8                   DisGen4EQPhase:1;             ///< Gen4 Bypass phase2/3 EQ
  UINT8                   BypassGen4EQ:1;               ///< Gen4 Bypass phase3 EQ
  UINT8                   EqSearchModeGen4:2;           ///< Equalization Search Mode for Gen4
  UINT8                   ReservedEndOfPortConfig:4;
} PCIe_PORT_CONFIG;

///Descriptor header
typedef struct {
  UINT32                  DescriptorFlags;              ///< Descriptor flags
  UINT16                  Parent;                       ///< Offset of parent descriptor
  UINT16                  Peer;                         ///< Offset of the peer descriptor
  UINT16                  Child;                        ///< Offset of the list of child descriptors
} PCIe_DESCRIPTOR_HEADER;

/// DDI (Digital Display Interface) configuration info
typedef struct {
  PCIe_DDI_DATA           DdiData;                      ///< DDI Data
  UINT8                   DisplayPriorityIndex;         ///< Display priority index
  UINT8                   ConnectorId;                  ///< Connector id determined by enumeration
  UINT8                   DisplayDeviceId;              ///< Display device id determined by enumeration
} PCIe_DDI_CONFIG;


/// Engine configuration data
typedef struct {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor header
  PCIe_ENGINE_DATA        EngineData;                   ///< Engine Data
  PCIe_ENGINE_INIT_STATUS InitStatus;                   ///< Initialization Status
  UINT8                   Scratch;                      ///< Scratch pad
  union {
    PCIe_PORT_CONFIG      Port;                         ///< PCIe port configuration data
    PCIe_DDI_CONFIG       Ddi;                          ///< DDI configuration data
  } Type;
} PCIe_ENGINE_CONFIG;

/// Wrapper configuration data
typedef struct {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor Header
  UINT8                   WrapId;                       ///< Wrapper ID
  UINT8                   NumberOfPIFs;                 ///< Number of PIFs on wrapper
  UINT8                   StartPhyLane;                 ///< Start PHY Lane
  UINT8                   EndPhyLane;                   ///< End PHY Lane
  UINT8                   StartDxioLane;                ///< Start Dxio Lane (Translated)
  UINT8                   EndDxioLane;                  ///< End Dxio Lane (Translated)
  struct {
    UINT8                 PowerOffUnusedLanes:1;        ///< Power Off unused lanes
    UINT8                 PowerOffUnusedPlls:1;         ///< Power Off unused Plls
    UINT8                 ClkGating:1;                  ///< TXCLK gating
    UINT8                 LclkGating:1;                 ///< LCLK gating
    UINT8                 TxclkGatingPllPowerDown:1;    ///< TXCLK clock gating PLL power down
    UINT8                 PllOffInL1:1;                 ///< PLL off in L1
    UINT8                 AccessEncoding:1;             ///< Reg access encoding
    UINT8                 CoreReversed:1;               ///< Indicates lanes are reversed in package connection
  } Features;
  UINT8                   MasterPll;                    ///< Bitmap of master PLL
} PCIe_WRAPPER_CONFIG;


/// Silicon configuration data
typedef struct  {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor Header
  UINT8                   SocketId;                     ///< Socket ID
  UINT8                   DieNumber;                    ///< Module ID
  UINT8                   RBIndex;                      ///< Physical Root Bridge
  UINT8                   InstanceId;                   ///< Logical Instance Identifier
  PCI_ADDR                Address;                      ///< PCI address of GNB host bridge
  UINT16                  StartLane;                    ///< Start Lane of this node
  UINT16                  EndLane;                      ///< End Lane of this node
  UINT8                   BusNumberLimit;               ///< Last Bus Number assigned to this node
  UINT8                   SbPresent:1;                  ///< Set to 1 if FCH connected to this NBIO
  UINT8                   SmuPresent:1;                 ///< Set to 1 if SMU connected to this NBIO
  UINT8                   Reserved1:6;                  ///< Reserved
  UINT8                   LogicalRBIndex;               ///< Logical Root Bridge
  UINT8                   Reserved2;                    ///< Reserved
} PCIe_SILICON_CONFIG;

typedef PCIe_SILICON_CONFIG GNB_HANDLE;

/// Complex configuration data
typedef struct {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor Header
  UINT8                   NodeId;                       ///< Processor Node ID
  UINT8                   Reserved;                     ///< For alignment
} PCIe_COMPLEX_CONFIG;

/// PCIe platform configuration info
typedef struct {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor Header
  PVOID                   StdHeader;                    ///< Standard configuration header
  UINT32                  LinkReceiverDetectionPooling; ///< Receiver pooling detection time in us.
  UINT32                  LinkL0Pooling;                ///< Pooling for link to get to L0 in us
  UINT32                  LinkGpioResetAssertionTime;   ///< Gpio reset assertion time in us
  UINT32                  LinkResetToTrainingTime;      ///< Time duration between deassert GPIO reset and release training in us                                                      ///
  UINT32                  PsppTuningParams;             ///< Tuning parameters for PSPP
  UINT8                   GfxCardWorkaround;            ///< GFX Card Workaround
  UINT8                   PsppPolicy;                   ///< PSPP policy
  UINT8                   TrainingExitState;            ///< State at which training should exit (see PCIE_LINK_TRAINING_STATE)
  UINT8                   TrainingAlgorithm;            ///< Training algorithm (see PCIE_TRAINING_ALGORITHM)
  PCIe_COMPLEX_CONFIG     ComplexList[MAX_NUMBER_OF_COMPLEXES];  ///< Complex
} PCIe_PLATFORM_CONFIG;


/// PCIe Engine Description

typedef struct {
  UINT32                  Flags;                        /**< Descriptor flags
                                                         * @li @b Bit31 - last descriptor on wrapper
                                                         * @li @b Bit30 - Descriptor allocated for PCIe port or DDI
                                                         */
  PCIe_ENGINE_DATA        EngineData;                   ///< Engine Data
} PCIe_ENGINE_DESCRIPTOR;

#pragma pack (pop)

#endif

