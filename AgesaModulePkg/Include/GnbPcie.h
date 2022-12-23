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

#ifndef _GNBPCIE_H_
#define _GNBPCIE_H_

#pragma pack (push, 1)

#include <AGESA.h>
#include <Gnb.h>

#define MAX_NUMBER_OF_COMPLEXES                8

#define DESCRIPTOR_TERMINATE_GNB               0x40000000ull
#define DESCRIPTOR_TERMINATE_TOPOLOGY          0x20000000ull
#define DESCRIPTOR_ALLOCATED                   0x10000000ull
#define DESCRIPTOR_VIRTUAL                     0x08000000ull
#define DESCRIPTOR_PLATFORM                    0x04000000ull
#define DESCRIPTOR_COMPLEX                     0x02000000ull
#define DESCRIPTOR_SILICON                     0x01000000ull
#define DESCRIPTOR_PCIE_WRAPPER                0x00800000ull
#define DESCRIPTOR_DDI_WRAPPER                 0x00400000ull
#define DESCRIPTOR_PCIE_ENGINE                 0x00200000ull
#define DESCRIPTOR_DDI_ENGINE                  0x00100000ull

#define DESCRIPTOR_ALL_WRAPPERS                (DESCRIPTOR_DDI_WRAPPER | DESCRIPTOR_PCIE_WRAPPER)
#define DESCRIPTOR_ALL_ENGINES                 (DESCRIPTOR_DDI_ENGINE | DESCRIPTOR_PCIE_ENGINE)

#define DESCRIPTOR_ALL_TYPES                   (DESCRIPTOR_ALL_WRAPPERS | DESCRIPTOR_ALL_ENGINES | DESCRIPTOR_SILICON | DESCRIPTOR_PLATFORM)

#define UNUSED_LANE_ID                         128
//#define PCIE_LINK_RECEIVER_DETECTION_POOLING   (60 * 1000)
//#define PCIE_LINK_L0_POOLING                   (60 * 1000)
//#define PCIE_LINK_GPIO_RESET_ASSERT_TIME       (2  * 1000)
//#define PCIE_LINK_RESET_TO_TRAINING_TIME       (2  * 1000)

// Get lowest PHY lane on engine
#define PcieLibGetLoPhyLane(Engine) (Engine != NULL ? ((Engine->EngineData.StartLane > Engine->EngineData.EndLane) ? Engine->EngineData.EndLane : Engine->EngineData.StartLane) : NULL)
// Get highest PHY lane on engine
#define PcieLibGetHiPhyLane(Engine) (Engine != NULL ? ((Engine->EngineData.StartLane > Engine->EngineData.EndLane) ? Engine->EngineData.StartLane : Engine->EngineData.EndLane) : NULL)
// Get number of lanes on wrapper
#define PcieLibWrapperNumberOfLanes(Wrapper) (Wrapper != NULL ? ((UINT8)(Wrapper->EndPhyLane - Wrapper->StartPhyLane + 1)) : 0)
// Check if virtual descriptor
#define PcieLibIsVirtualDesciptor(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_VIRTUAL) != 0) : FALSE)
// Check if it is allocated descriptor
#define PcieLibIsEngineAllocated(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_ALLOCATED) != 0) : FALSE)
// Check if it is last descriptor in list
#define PcieLibIsLastDescriptor(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_TERMINATE_LIST) != 0) : TRUE)
// Check if descriptor a PCIe engine
#define PcieLibIsPcieEngine(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_PCIE_ENGINE) != 0) : FALSE)
// Check if descriptor a DDI engine
#define PcieLibIsDdiEngine(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_DDI_ENGINE) != 0) : FALSE)
// Check if descriptor a DDI wrapper
#define PcieLibIsDdiWrapper(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_DDI_WRAPPER) != 0) : FALSE)
// Check if descriptor a PCIe wrapper
#define PcieLibIsPcieWrapper(Descriptor) (Descriptor != NULL ? ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_PCIE_WRAPPER) != 0) : FALSE)
// Check if descriptor a PCIe wrapper
#define PcieLibGetNextDescriptor(Descriptor) (Descriptor != NULL ? (((Descriptor->Header.DescriptorFlags & DESCRIPTOR_TERMINATE_LIST) != 0) ? NULL : (++Descriptor)) : NULL)

#define LANE_TYPE_PCIE_CORE_CONFIG              0x00000001ul
#define LANE_TYPE_PCIE_CORE_ALLOC               0x00000002ul
#define LANE_TYPE_PCIE_CORE_ACTIVE              0x00000004ul
#define LANE_TYPE_PCIE_SB_CORE_CONFIG           0x00000008ul
#define LANE_TYPE_PCIE_CORE_HOTPLUG             0x00000010ul
#define LANE_TYPE_PCIE_CORE_ALLOC_ACTIVE        0x00000020ul
#define LANE_TYPE_PCIE_PHY                      0x00000100ul
#define LANE_TYPE_PCIE_PHY_NATIVE               0x00000200ul
#define LANE_TYPE_PCIE_PHY_NATIVE_ACTIVE        0x00000400ul
#define LANE_TYPE_PCIE_PHY_NATIVE_HOTPLUG       0x00000800ul
#define LANE_TYPE_PCIE_PHY_NATIVE_ALLOC_ACTIVE  0x00001000ul
#define LANE_TYPE_DDI_PHY                       0x00010000ul
#define LANE_TYPE_DDI_PHY_NATIVE                0x00020000ul
#define LANE_TYPE_DDI_PHY_NATIVE_ACTIVE         0x00040000ul
#define LANE_TYPE_PHY_NATIVE_ALL                0x00100000ul
#define LANE_TYPE_PCIE_PHY_NATIVE_MASTER_PLL    0x00200000ul
#define LANE_TYPE_CORE_ALL                      LANE_TYPE_PHY_NATIVE_ALL
#define LANE_TYPE_ALL                           LANE_TYPE_PHY_NATIVE_ALL

#define LANE_TYPE_PCIE_LANES (LANE_TYPE_PCIE_CORE_ACTIVE | LANE_TYPE_PCIE_SB_CORE_CONFIG | \
                              LANE_TYPE_PCIE_CORE_HOTPLUG | LANE_TYPE_PCIE_CORE_ALLOC | \
                              LANE_TYPE_PCIE_PHY | LANE_TYPE_PCIE_PHY_NATIVE | \
                              LANE_TYPE_PCIE_PHY_NATIVE_ACTIVE | LANE_TYPE_PCIE_PHY_NATIVE_HOTPLUG | \
                              LANE_TYPE_PCIE_CORE_CONFIG | LANE_TYPE_PCIE_PHY_NATIVE_ALLOC_ACTIVE | \
                              LANE_TYPE_PCIE_CORE_ALLOC_ACTIVE)

#define LANE_TYPE_DDI_LANES (LANE_TYPE_DDI_PHY | LANE_TYPE_DDI_PHY_NATIVE | LANE_TYPE_DDI_PHY_NATIVE_ACTIVE)


#define INIT_STATUS_PCIE_PORT_GEN2_RECOVERY          0x00000001ull
#define INIT_STATUS_PCIE_PORT_BROKEN_LANE_RECOVERY   0x00000002ull
#define INIT_STATUS_PCIE_PORT_TRAINING_FAIL          0x00000004ull
#define INIT_STATUS_PCIE_TRAINING_SUCCESS            0x00000008ull
#define INIT_STATUS_PCIE_EP_NOT_PRESENT              0x00000010ull
#define INIT_STATUS_PCIE_PORT_IN_COMPLIANCE          0x00000020ull
#define INIT_STATUS_DDI_ACTIVE                       0x00000040ull
#define INIT_STATUS_ALLOCATED                        0x00000080ull
#define INIT_STATUS_PCIE_PORT_BROKEN_LANE_X1         0x00000100ull

#define PCIE_PORT_GEN_CAP_BOOT                       0x00000001ul
#define PCIE_PORT_GEN_CAP_MAX                        0x00000002ul
#define PCIE_GLOBAL_GEN_CAP_ALL_PORTS                0x00000010ul
#define PCIE_GLOBAL_GEN_CAP_TRAINED_PORTS            0x00000014ul
#define PCIE_GLOBAL_GEN_CAP_HOTPLUG_PORTS            0x00000018ul

#define PCIE_POWERGATING_SKIP_CORE                   0x00000001ul
#define PCIE_POWERGATING_SKIP_PHY                    0x00000002ul

/// PCIe Link Training State
typedef enum {
  PcieTrainingStandard,                                ///< Standard training algorithm. Training contained to AmdEarlyInit.
                                                       ///< PCIe device accessible after AmdEarlyInit complete
  PcieTrainingDistributed,                             ///< Distribute training algorithm. Training distributed across AmdEarlyInit/AmdPostInit/AmdS3LateRestore
                                                       ///< PCIe device accessible after AmdPostInit complete.
                                                       ///< Algorithm potentially save up to 60ms in S3 resume time by skipping training empty slots.
} PCIE_TRAINING_ALGORITHM;

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

/// PCIe Port Visibility
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

/// The return status for GFX Card Workaround.
typedef enum {
  GFX_WORKAROUND_DEVICE_NOT_READY,                       ///< GFX Workaround device is not ready.
  GFX_WORKAROUND_RESET_DEVICE,                           ///< GFX Workaround device need reset.
  GFX_WORKAROUND_SUCCESS                                 ///< The service completed normally.
} GFX_WORKAROUND_STATUS;

/// GFX workaround control
typedef enum {
  GfxWorkaroundDisable,                                   ///< GFX Workaround disabled
  GfxWorkaroundEnable                                     ///< GFX Workaround enabled
} GFX_WORKAROUND_CONTROL;

/// PIF lane power state
typedef enum {
  PifPowerStateL0,                                        ///<
  PifPowerStateLS1,                                       ///<
  PifPowerStateLS2,                                       ///<
  PifPowerStateOff = 0x7,                                 ///<
} PCIE_PIF_POWER_STATE;

/// PIF lane power control
typedef enum {
  PowerDownPifs,                                          ///<
  PowerUpPifs                                             ///<
} PCIE_PIF_POWER_CONTROL;

///PLL rumup time
typedef enum {
  NormalRampup,                                           ///<
  LongRampup,                                             ///<
} PCIE_PLL_RAMPUP_TIME;

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
  UINT8                   State;                        ///< Training state
  UINT8                   PcieBridgeId:4;               ///< IOC PCIe bridge ID
  UINT16                  UnitId:12;                    ///< Port start unit ID
  UINT16                  NumberOfUnitId:4;             ///< Def number of unitIDs assigned to port
  UINT8                   GfxWrkRetryCount:4;           ///< Number of retry for GFX workaround
  UINT32                  TimeStamp;                    ///< Time stamp used to during training process
  UINT8                   LogicalBridgeId;              ///< Logical Bridge ID
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
  UINT8                   StartPcieCoreId:4;            ///< Start PCIe Core ID
  UINT8                   EndPcieCoreId:4;              ///< End PCIe Core ID
  UINT8                   NumberOfLanes;                ///< Number of lanes
  struct {
    UINT8                 PowerOffUnusedLanes:1;        ///< Power Off unused lanes
    UINT8                 PowerOffUnusedPlls:1;         ///< Power Off unused Plls
    UINT8                 ClkGating:1;                  ///< TXCLK gating
    UINT8                 LclkGating:1;                 ///< LCLK gating
    UINT8                 TxclkGatingPllPowerDown:1;    ///< TXCLK clock gating PLL power down
    UINT8                 PllOffInL1:1;                 ///< PLL off in L1
    UINT8                 AccessEncoding:1;             ///< Reg access encoding
  } Features;
  UINT8                   MasterPll;                    ///< Bitmap of master PLL
} PCIe_WRAPPER_CONFIG;


/// Silicon configuration data
typedef struct  {
  PCIe_DESCRIPTOR_HEADER  Header;                       ///< Descriptor Header
  UINT8                   SocketId;                     ///< Socket ID
  UINT8                   DieNumber;                    ///< Module ID
  UINT8                   RBIndex;                      ///< Node to which GNB connected
  UINT8                   InstanceId;                   ///< Logical Instance Identifier
  PCI_ADDR                Address;                      ///< PCI address of GNB host bridge
  UINT64                  GmmBase;                      ///< GMM Base
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

/// PCIe Lane allocation descriptor
typedef struct {
  UINT32                  Flags;                        ///< Flags
  UINT8                   WrapId;                       ///< Wrapper ID
  UINT8                   EngineType;                   ///< Engine Type
  UINT8                   NumberOfEngines;              ///< Number of engines to configure
  UINT8                   NumberOfConfigurations;       ///< Number of possible configurations
  UINT8                   *ConfigTable;                 ///< Pointer to config table
} PCIe_LANE_ALLOC_DESCRIPTOR;

/// Lane Control
typedef enum {
  EnableLanes,              ///< Enable Lanes
  DisableLanes              ///< Disable Lanes
} LANE_CONTROL;

/// PCIE HW initiated power gating
typedef enum {
  PcieHwInitPwrGatingDisabled,                        ///< Disable Power gating
  PcieHwInitPwrGatingL1Pg,                            ///< L1-PG
  PcieHwInitPwrGatingOffPg,                           ///< Off-PG
  PcieHwInitPwrGatingEnableAll                        ///< Enable ALL
} PCIE_HW_INIT_POWER_GATING;

/// PCIe Correctable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_5_0 :6;                          ///< Unused bits
    UINT32                  BadTLP :1;                                ///< [6] BadTlpMask
    UINT32                  BadDLLPStatus :1;                         ///< [7] BadDllpMask
    UINT32                  ReplayNumberRolloverStatus :1;            ///< [8] ReplayNumRolloverMask
    UINT32                  Reserved_11_9 :3;                         ///< Unused bits
    UINT32                  ReplayTimerTimeoutStatus :1;              ///< [12] ReplayTimerTimeoutMask
    UINT32                  AdvisoryNonFatalErrorStatus :1;           ///< [13] AdvisoryNonfatalErrMask
    UINT32                  Reserved_31_14 :18;                       ///< Unused bits
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_CORRECTABLE_MASK;

/// PCIe Unorrectable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_3_0 :4;                          ///< [3:0] Unused bits
    UINT32                  DataLinkProtocolErrorstatusMask :1;       ///< [4] DlpErrMask
    UINT32                  Reserved_11_5 :7;                         ///< [11:5] Unused bits
    UINT32                  PoisonedTLPStatusMask :1;                 ///< [12] PsnErrMask
    UINT32                  Reserved_13_13 :1;                        ///< [13] Unused bit
    UINT32                  CompletionTimeoutStatusMask :1;           ///< [14] CplTimeoutMask
    UINT32                  CompleterAbortStatusMask :1;              ///< [15] CplAbortErrMask
    UINT32                  UnexpectedCompletionStatusMask :1;        ///< [16] UnexpCplMask
    UINT32                  Reserved_17_17:1 ;                        ///< [17] Unused bit
    UINT32                  MalTlpMask:1 ;                            ///< [18] MalTlpMask
    UINT32                  ECRCErrorStatusMask :1;                   ///< [19] EcrcErrMask
    UINT32                  UnsupportedRequestErrorStatusMask :1;     ///< [20] UnsuppReqErrMask
    UINT32                  AcsViolationMask:1 ;                      ///< [21] AcsViolationMask
    UINT32                  Reserved_31_22 :10;                       ///< [31:22] Unused bits
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_UNCORRECTABLE_MASK;

/// PCIe Unorrectable Error Mask
typedef union {
  struct {                                                            ///<
    UINT32                  Reserved_3_0 :4;                          ///< [3:0] Unused bits
    UINT32                  DataLinkProtocolErrorstatusSeverity :1;   ///< [4] DlpErrSeverity
    UINT32                  Reserved_11_5 :7;                         ///< [11:5] Unused bits
    UINT32                  PoisonedTLPStatusSeverity :1;             ///< [12] PsnErrSeverity
    UINT32                  Reserved_13_13 :1;                        ///< [13] Unused bit
    UINT32                  CompletionTimeoutStatusSeverity :1;       ///< [14] CplTimeoutSeverity
    UINT32                  CompleterAbortStatusSeverity :1;          ///< [15] CplAbortErrSeverity
    UINT32                  UnexpectedCompletionStatusSeverity :1;    ///< [16] UnexpCplSeverity
    UINT32                  Reserved_17_17:1 ;                        ///< [17] Unused bit
    UINT32                  MalTlpSeverity:1 ;                        ///< [18] MalTlpSeverity
    UINT32                  ECRCErrorStatusSeverity :1;               ///< [19] EcrcErrSeverity
    UINT32                  UnsupportedRequestErrorStatusSeverity :1; ///< [20] UnsuppReqErrSeverity
    UINT32                  AcsViolationSeverity:1 ;                  ///< [21] AcsViolationSeverity
    UINT32                  Reserved_31_22 :10;                       ///< [31:22] Unused bits
  } Field;                                                            ///<
  UINT32 Value;                                                       ///<
} PCIe_AER_UNCORRECTABLE_SEVERITY;

/// PCIe AER Port Configuration
typedef struct {
  BOOLEAN                         PortAerEnable;                      ///< General per-port enable
  PCIe_AER_CORRECTABLE_MASK       CorrectableMask;                    ///< Per-port mask for correctable errors
  PCIe_AER_UNCORRECTABLE_MASK     UncorrectableMask;                  ///< Per-port mask for uncorrectable errors
  PCIe_AER_UNCORRECTABLE_SEVERITY UncorrectableSeverity;              ///< Per-port severity configuration for uncorrectable errors
} PCIe_PORT_AER_CONFIG;

/// PCIe AER Configuration
typedef struct {
  UINT8                    NumberOfPorts;                           ///< The amount of ports of GNB
  PCIe_PORT_AER_CONFIG     *PortAerConfig;                          ///< Per-port AER configuration (Only 3 ports supported in code)
} PCIe_AER_CONFIG;

#pragma pack (pop)

#endif

