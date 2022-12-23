/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO User Configuration Parser
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include <PiPei.h>
#include <AmdPcieComplex.h>
#include <GnbDxio.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Library/BaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/GnbLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/DxioLibV2.h>
#include "DxioLibLocal.h"

#define FILECODE LIBRARY_DXIOLIBV2_DXIOPARSER_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define   SSP_PLATFORM_TYPE  0
#define   MAX_INSTANCE_ID    2

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

///Port information needed for lane translation callback
typedef struct {
  UINT8           SocketNumber;       ///< SocketNumber
  UINT8           StartLane;          ///< Start Lane from User Config
  UINT8           EndLane;            ///< End Lane from User Config
  UINT8           DxioStartLane;      ///< Translated Start Lane
  UINT8           DxioEndLane;        ///< Translated End Lane
  BOOLEAN         LinkReversal;       ///< Link Reversal should be set
  BOOLEAN         LanesFound;         ///< Flag for lanes found
} PORT_INFO_CALLBACK;


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to fixup Pcie Platform Configuration for package specific values
 *
 *
 *
 * @param[in]     Pcie    PCIe configuration info
 */
AGESA_STATUS
STATIC
DxioTranslateLanesCallback (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      VOID                  *Buffer,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GNB_HANDLE            *GnbHandle;
  PORT_INFO_CALLBACK    *PortInfo;

  PortInfo = (PORT_INFO_CALLBACK *) Buffer;
  GnbHandle = (GNB_HANDLE *) PcieConfigGetParentSilicon (Wrapper);
  IDS_HDT_CONSOLE (PCIE_MISC, "Translating PHY Lanes %d to %d\n", PortInfo->StartLane, PortInfo->EndLane);
  if (GnbHandle->SocketId == PortInfo->SocketNumber) {
    if ((PortInfo->StartLane >= Wrapper->StartPhyLane) && (PortInfo->StartLane <= Wrapper->EndPhyLane)) {
      if (Wrapper->Features.CoreReversed == 0) {
        if (PortInfo->StartLane <= PortInfo->EndLane) {
          IDS_HDT_CONSOLE (PCIE_MISC, "  Core is NOT reversed, Link is NOT reversed\n");
          PortInfo->DxioStartLane = Wrapper->StartDxioLane + (PortInfo->StartLane - Wrapper->StartPhyLane);
          PortInfo->DxioEndLane = Wrapper->StartDxioLane + (PortInfo->EndLane - Wrapper->StartPhyLane);
          PortInfo->LinkReversal = FALSE;
        } else {
          IDS_HDT_CONSOLE (PCIE_MISC, "  Core is NOT reversed, Link IS reversed\n");
          PortInfo->DxioEndLane = Wrapper->StartDxioLane + (PortInfo->StartLane - Wrapper->StartPhyLane);
          PortInfo->DxioStartLane = Wrapper->StartDxioLane + (PortInfo->EndLane - Wrapper->StartPhyLane);
          PortInfo->LinkReversal = TRUE;
        }
      } else {
        if (PortInfo->StartLane <= PortInfo->EndLane) {
          IDS_HDT_CONSOLE (PCIE_MISC, "  Core IS reversed, Link is NOT reversed\n");
          PortInfo->DxioEndLane = Wrapper->EndDxioLane - (PortInfo->StartLane - Wrapper->StartPhyLane);
          PortInfo->DxioStartLane = Wrapper->EndDxioLane - (PortInfo->EndLane - Wrapper->StartPhyLane);
          PortInfo->LinkReversal = TRUE;
        } else {
          IDS_HDT_CONSOLE (PCIE_MISC, "  Core IS reversed, Link IS reversed\n");
          PortInfo->DxioStartLane = Wrapper->EndDxioLane - (PortInfo->StartLane - Wrapper->StartPhyLane);
          PortInfo->DxioEndLane = Wrapper->EndDxioLane - (PortInfo->EndLane - Wrapper->StartPhyLane);
          PortInfo->LinkReversal = FALSE;
        }
      }
      PortInfo->LanesFound = TRUE;
    }
  }
  return AGESA_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * DXIO User Config Parser
 *
 *
 *
 * @param[in]  Pcie           PCIe configuration info
 * @param[in]  StartLane      StartLane for this port from User Config
 * @param[in]  EndLane        EndLane for this port from User Config
 * @retval     BOOLEAN
 */

BOOLEAN
DxioTranslateLanes (
  IN       PCIe_PLATFORM_CONFIG      *Pcie,
  IN       UINT8                     SocketNumber,
  IN       UINT8                     StartLane,
  IN       UINT8                     EndLane,
  IN OUT   UINT8                     *StartDxioLane,
  IN OUT   UINT8                     *EndDxioLane,
  IN OUT   BOOLEAN                   *Reverse
  )
{
  PORT_INFO_CALLBACK    PortInfo;
  AGESA_STATUS          AgesaStatus;

  PortInfo.SocketNumber = SocketNumber;
  PortInfo.StartLane = StartLane;
  PortInfo.EndLane = EndLane;
  PortInfo.LanesFound = FALSE;
  AgesaStatus = PcieConfigRunProcForAllWrappers (DESCRIPTOR_ALL_WRAPPERS, DxioTranslateLanesCallback, &PortInfo, Pcie);
  if (PortInfo.LanesFound) {
    *StartDxioLane = PortInfo.DxioStartLane;
    *EndDxioLane = PortInfo.DxioEndLane;
    *Reverse = PortInfo.LinkReversal;
  } else {
    *StartDxioLane = 0;
    *EndDxioLane = 0;
  }
  ASSERT (PortInfo.LanesFound);
  return PortInfo.LanesFound;
}

/*----------------------------------------------------------------------------------------*/
/**
 * DXIO User Config Parser
 *
 *
 *
 * @param[in]  PeiServices    Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 * @param[in]  UserConfig     Pointer to the platform BIOS supplied platform configuration
 * @param[out] ThisNode       Pointer to a location to store the address of the platform descriptor for this node
 * @param[out] NodeSize       Pointer to a location to store the size (in dwords) of the platforrm desciptor for this node
 * @param[out] AncData        Pointer to a location to store the address of the ancillary port data
 * @param[out] AncDataSize    Pointer to a location to store the size (in dwords) of the ancillary port data
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
DxioParseUserConfig (
  IN       CONST EFI_PEI_SERVICES    **PeiServices,
  IN       GNB_HANDLE                *GnbHandle,
  IN       DXIO_COMPLEX_DESCRIPTOR   *UserConfig,
  IN       PCIe_PLATFORM_CONFIG      *Pcie,
  OUT      DXIO_PLATFORM_DESCRIPTOR  **ThisNode,
  OUT      UINT32                    *NodeSize,
  OUT      UINT8                     **AncData,
  OUT      UINT32                    *AncDataSize
  )
{
  AGESA_STATUS               AgesaStatus;
  UINT8                      SocketNumber;
  UINT8                      InstanceId;
  UINT8                      PortStartLane;
  UINT8                      PortEndLane;
  UINT16                     NodeMinLane;
  UINT16                     NodeMaxLane;
  BOOLEAN                    Reverse;
  // DXIO Firmware Structures
  DXIO_PLATFORM_DESCRIPTOR   *NodePlatformDesc;
  DXIO_ENGINE_DESCRIPTOR     *EnginePointer;
  UINT32                     ThisNodeCount;
  UINT32                     ThisNodeSize;
  // Ancillary Data Structures
  UINT32                     DataSize;
  UINT8                      *AncillaryData;
  UINT32                     AncillaryDataSize;
  UINT32                     AncillaryDataOffset;
  DXIO_ANCILLARYDATA         *DxioAncData;
  DXIO_ANCILLARYDATA_SUBHEAP *DxioSubHeapData;

  //User Config Pointers
  DXIO_PORT_DESCRIPTOR       *PortList;              // Pointer to start of User Config for this socket
  DXIO_PORT_DESCRIPTOR       *PortPointer;           // Updatable pointer for PortList processing

  // Get Socket Number
  SocketNumber = GnbHandle->SocketId;
  InstanceId = GnbHandle->InstanceId;
  // Get Min/Max lane number for this node
  NodeMinLane = GnbHandle->StartLane;
  NodeMaxLane = GnbHandle->EndLane;

  AgesaStatus = AGESA_SUCCESS;
  PortList = NULL;

  AgesaStatus = DxioGetUserCfgForSocket (SocketNumber, UserConfig, &PortList);

  if (AGESA_SUCCESS == AgesaStatus) {
    // Parse structure and count entries for this node
    PortPointer = PortList;
    ThisNodeSize = sizeof (DXIO_PLATFORM_DESCRIPTOR) + 8;  // Include 2 reserved UINT32 at the end
    ThisNodeCount = 0;
    AncillaryDataSize = 0;
    AncillaryDataOffset = NULL;
    EnginePointer = NULL;

    // Calculate size of Platform Structure and Ancillary Data for this node
    while (PortPointer != NULL) {
      if (PortPointer->EngineData.EngineType != DxioUnusedEngine) {
        if (DxioTranslateLanes(Pcie,
                               SocketNumber,
                               PortPointer->EngineData.StartLane,
                               PortPointer->EngineData.EndLane,
                               &PortStartLane,
                               &PortEndLane,
                               &Reverse
                               )) {
          ThisNodeSize += sizeof (DXIO_ENGINE_DESCRIPTOR);
          ThisNodeCount++;
          AncillaryDataSize += DxioAncDataCalcSize (PortPointer);
        } else {
          // Could not translate lanes.  This entry will be ignored. Note that it would ASSERT earlier;
          PortPointer->EngineData.EngineType = DxioUnusedEngine;
        }
      }
      PortPointer = PcieConfigGetNextDataDescriptor(PortPointer);
    }
    if (Pcie->PsppPolicy != PsppDisabled) {
      AncillaryDataSize += sizeof (DXIO_ANCILLARYPORTDATA_PSPP) + sizeof (DXIO_ANCILLARYDATA_SUBHEAP);
    }
    if (AncillaryDataSize != 0) {
      AncillaryDataSize += sizeof (DXIO_HEAPDATA_CONTAINER) + sizeof (DXIO_ANCILLARYDATA);
    }

    // Build data structures for this node if there is any configuration required
    if (ThisNodeCount != 0) {
      // Allocate memory for this node platform structure
      AgesaStatus = (*PeiServices)->AllocatePool (
                                      PeiServices,
                                      ThisNodeSize,
                                      (VOID **)&NodePlatformDesc
                                      );
      //ASSERT_EFI_ERROR (AgesaStatus);
      *ThisNode = NodePlatformDesc;             // Save pointer to allocated memory
      *NodeSize = (ThisNodeSize + 3) >> 2;      // Platfom Descriptor size in dwords


      // Allocate memory for this node ancillary data
      AncillaryData = NULL;
      if (AncillaryDataSize != 0) {
        AgesaStatus = (*PeiServices)->AllocatePool (
                                        PeiServices,
                                        AncillaryDataSize,
                                        (VOID **)&AncillaryData
                                        );
        if (AgesaStatus == AGESA_SUCCESS) {
          *AncData = AncillaryData;                          // Save pointer to allocated memory
          *AncDataSize = AncillaryDataSize >> 2;             // Ancillary Data size in dwords

          LibAmdMemFill (AncillaryData, 0, AncillaryDataSize, (AMD_CONFIG_PARAMS *) NULL);

          DxioAncData = (DXIO_ANCILLARYDATA *) AncillaryData;
          DxioAncData->descriptorType = 0;   ///@todo
          DxioAncData->version = DXIO_ANCILLARYDATA_VERSION;
          DxioAncData->numDWords = (AncillaryDataSize >> 2) -1;
          AncillaryData += sizeof (DXIO_ANCILLARYDATA);

          AncillaryDataOffset = sizeof (DXIO_ANCILLARYDATA);

          if (Pcie->PsppPolicy != PsppDisabled) {
            DxioSubHeapData = (DXIO_ANCILLARYDATA_SUBHEAP *) AncillaryData;
            DxioSubHeapData->descriptorType = DXIO_ANCDATA_SUBHEAPTYPE_PSPP;
            DxioSubHeapData->version = DXIO_ANCILLARYDATA_SUBHEAP_VERSION;
            DxioSubHeapData->numDWORDs = (sizeof (DXIO_ANCILLARYPORTDATA_PSPP) + sizeof (DXIO_ANCILLARYDATA_SUBHEAP)) >> 2;
            AncillaryData += sizeof (DXIO_ANCILLARYDATA_SUBHEAP);
            LibAmdMemCopy ((VOID *) AncillaryData,
                           (VOID *) &Pcie->PsppTuningParams,
                           sizeof (DXIO_ANCILLARYPORTDATA_PSPP),
                           (AMD_CONFIG_PARAMS *)NULL
                           );
            AncillaryData += sizeof (DXIO_ANCILLARYPORTDATA_PSPP);
            AncillaryDataOffset += sizeof (DXIO_ANCILLARYPORTDATA_PSPP) + sizeof (DXIO_ANCILLARYDATA_SUBHEAP);
          }
        } else {
          *AncData = (UINT8 *) NULL;
          *AncDataSize = 0;
        }
      } else {
        *AncData = (UINT8 *) NULL;
        *AncDataSize = 0;
      }

      // Initialize platform level entries for this structure
      LibAmdMemFill (NodePlatformDesc, 0, ThisNodeSize, (AMD_CONFIG_PARAMS *) NULL);
      NodePlatformDesc->PlatformType = SSP_PLATFORM_TYPE;
      NodePlatformDesc->NumEngineDesc = ThisNodeCount;
      // Parse structure and copy entries for this node to this node platform structure
      PortPointer = PortList;
      NodePlatformDesc ++;                                              // Point to first engine descriptor
      EnginePointer = (DXIO_ENGINE_DESCRIPTOR *)NodePlatformDesc;       // Initialize engine pointer to first engine
      NodePlatformDesc --;                                              // Restore NodePlatformDesc address
      AncillaryDataSize = 0;
      while (PortPointer != NULL) {
        if (PortPointer->EngineData.EngineType != DxioUnusedEngine) {
          if (DxioTranslateLanes(Pcie,
                                 SocketNumber,
                                 PortPointer->EngineData.StartLane,
                                 PortPointer->EngineData.EndLane,
                                 &PortStartLane,
                                 &PortEndLane,
                                 &Reverse
                                 )) {
            EnginePointer->StartLane = PortStartLane;
            EnginePointer->EndLane = PortEndLane;
            PortPointer->EngineData.DxioStartLane = PortStartLane;
            PortPointer->EngineData.DxioEndLane = PortEndLane;
            EnginePointer->GpioGroupID = 1;
            EnginePointer->EngineType = PortPointer->EngineData.EngineType;
            switch (PortPointer->EngineData.EngineType) {
            case DxioPcieEngine:
              EnginePointer->LinkDesc.Pcie.Capabilities.earlyTrainLink = PortPointer->Port.MiscControls.SbLink;
              IDS_HDT_CONSOLE (PCIE_MISC, "PsppPolicy is %d and looking for %d\n", Pcie->PsppPolicy, AgesaPsppBalance);
              if ((EnginePointer->LinkDesc.Pcie.Capabilities.earlyTrainLink == 1) || (Pcie->PsppPolicy == AgesaPsppBalance)) {
                EnginePointer->LinkDesc.Pcie.Capabilities.maxLinkSpeedCap = DxioGen1;
                IDS_HDT_CONSOLE (PCIE_MISC, "  Forcing Gen1\n");
              } else {
                EnginePointer->LinkDesc.Pcie.Capabilities.maxLinkSpeedCap = PortPointer->Port.LinkSpeedCapability;
              }
              if (PortPointer->Port.EqPreset != 0) {
                EnginePointer->LinkDesc.Pcie.Capabilities.eqSearchModeOride = 1;
                EnginePointer->LinkDesc.Pcie.Capabilities.eqSearchMode = PortPointer->Port.EqPreset;
                IDS_HDT_CONSOLE (GNB_TRACE, "EqSearchMode: %d\n",
                    EnginePointer->LinkDesc.Pcie.Capabilities.eqSearchMode);
              }
              EnginePointer->LinkDesc.Pcie.DevFunNumber = (PortPointer->Port.DeviceNumber << 3) | PortPointer->Port.FunctionNumber;
              EnginePointer->LinkDesc.Pcie.Capabilities.enableTurnOffSettings = 1;
              EnginePointer->LinkDesc.Pcie.Capabilities.turnOffUnusedLanes = PortPointer->Port.MiscControls.TurnOffUnusedLanes;
              EnginePointer->LinkDesc.Pcie.Capabilities.portPresent = PortPointer->Port.PortPresent;
              EnginePointer->LinkDesc.Pcie.Capabilities.linkHotplug = PortPointer->Port.LinkHotplug;
              EnginePointer->LinkDesc.Pcie.Capabilities.linkReversal = Reverse;
              DataSize = DxioAncDataPopulate (EnginePointer, PortPointer, AncillaryData);
              if (0 != DataSize) {
                EnginePointer->LinkDesc.Pcie.AncillaryDataOffset = AncillaryDataOffset >> 2;
                AncillaryData += DataSize;
                AncillaryDataOffset += DataSize;
              }
              break;
            case DxioSATAEngine:
              EnginePointer->LinkDesc.Sata.ChannelType = PortPointer->Port.MiscControls.ChannelType;
              NbioEnableNbifDevice (GnbHandle, DxioSATAEngine, PortPointer->EngineData.StartLane);
              DataSize = DxioAncDataPopulate (EnginePointer, PortPointer, AncillaryData);
              if (0 != DataSize) {
                EnginePointer->LinkDesc.Sata.AncillaryDataOffset = AncillaryDataOffset >> 2;
                AncillaryData += DataSize;
                AncillaryDataOffset += DataSize;
              }
              break;
            default:
              break;
            }
          }
          EnginePointer++;
        }
        PortPointer = PcieConfigGetNextDataDescriptor(PortPointer);
      }
    } else {
      // Nothing found for this node, skip DXIO call
      *ThisNode = NULL;             // Save pointer to allocated memory
      *NodeSize = 0;      // Platfom Descriptor size in dwords
    }
  }
  // Return pointer to this node platform structure
  return (AgesaStatus);
}


