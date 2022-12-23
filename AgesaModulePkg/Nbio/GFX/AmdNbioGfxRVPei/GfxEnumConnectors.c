/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to initialize Integrated Info Table
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
*****************************************************************************
*
* Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting You permission to use this software and documentation (if
* any) (collectively, the "Software") pursuant to the terms and conditions of
* the Software License Agreement included with the Software. If You do not have
* a copy of the Software License Agreement, contact Your AMD representative for
* a copy.
*
* You agree that You will not reverse engineer or decompile the Software, in
* whole or in part, except as allowed by applicable law.
*
* WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
* ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
* INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
* ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
* ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
* warranties, so the above exclusion may not apply to You, but only to the
* extent required by law.
*
* LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
* APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
* LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
* CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
* OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
* ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
* INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
* LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
* FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
* INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
* PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
* You for all damages, losses, and causes of action (whether in contract, tort
* (including negligence) or otherwise) exceed the amount of $50 USD. You agree
* to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
* and their respective licensors, directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your
* possession or use of the Software or violation of the terms and conditions of
* this Agreement.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
* Software and related documentation are "commercial items", as that term is
* defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
* software" and "commercial computer software documentation", as such terms are
* used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
* respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
* 227.7202-1 through 227.7202-4, as applicable, the commercial computer
* software and commercial computer software documentation are being licensed to
* U.S. Government end users: (a) only as commercial items, and (b) with only
* those rights as are granted to all other end users pursuant to the terms and
* conditions set forth in this Agreement. Unpublished rights are reserved under
* the copyright laws of the United States.
*
* EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
* laws and regulations, as well as the import/export control laws and
* regulations of other countries as applicable. You further agree You will not
* export, re-export, or transfer, directly or indirectly, any product,
* technical data, software or source code received from AMD under this license,
* or the direct product of such technical data or software to any country for
* which the United States or any other applicable government requires an export
* license or other governmental approval without first obtaining such licenses
* or approvals, or in violation of any applicable laws or regulations of the
* United States or the country where the technical data or software was
* obtained. You acknowledges the technical data and software received will not,
* in the absence of authorization from U.S. or local law and regulations as
* applicable, be used by or exported, re-exported or transferred to: (i) any
* sanctioned or embargoed country, or to nationals or residents of such
* countries; (ii) any restricted end-user as identified on any applicable
* government end-user list; or (iii) any party where the end-use involves
* nuclear, chemical/biological weapons, rocket systems, or unmanned air
* vehicles.  For the most current Country Group listings, or for additional
* information about the EAR or Your obligations under those regulations, please
* refer to the website of the U.S. Bureau of Industry and Security at
* http://www.bis.doc.gov/.
*******************************************************************************
*
*/


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <GnbDxio.h>
#include <NbioGfx.h>
#include <Library/AmdBaseLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/GnbHeapLib.h>
#include <Library/NbioHandleLib.h>
#include "GfxEnumConnectors.h"
#include <Include/AmdPcieComplex.h>
#include <Ppi/NbioPcieComplexPpi.h>
#include <Ppi/SocLogicalIdPpi.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/SmnAccessLib.h>
#include <GnbRegistersRV.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define ATOM_ENCODER_CAP_RECORD_HBR2_DISABLE               0x0001
#define ATOM_ENCODER_CAP_RECORD_DP_FIXED_VS_EN             0x0002
#define ATOM_ENCODER_CAP_RECORD_EXT_CHIP_MASK              0x007C
#define ATOM_ENCODER_CAP_RECORD_HDMI20_PI3EQX1204          (0x01 << 2 )     //PI redriver chip
#define ATOM_ENCODER_CAP_RECORD_HDMI20_TISN65DP159RSBT     (0x02 << 2 )     //TI retimer chip
#define ATOM_ENCODER_CAP_RECORD_HDMI20_PARADE_PS175        (0x03 << 2 )     //Parade DP->HDMI recoverter chip
#define ATOM_ENCODER_CAP_RECORD_HBR3_DISABLE               0x0080
#define ATOM_ENCODER_CAP_RECORD_USB_C_TYPE                 0x100            // the DP connector is a USB-C type.
#define ATOM_ENCODER_CAP_RECORD_HDMI20_DISABLE             0x200
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

PCIe_ENGINE_CONFIG DdiComplexDataRV[] = {
  //Ddi0
  {
    {
      DESCRIPTOR_DDI_ENGINE | DESCRIPTOR_ALLOCATED,
      0,
      0,
      0
    },
    {PcieDdiEngine, 16, 19},
    0,                                              //Initialization Status
    0xFF,                                           //Scratch
    {0}                                             //PCIe_DDI_CONFIG
  },
  //Ddi1
  {
    {
      DESCRIPTOR_DDI_ENGINE | DESCRIPTOR_ALLOCATED,
      0,
      0,
      0
    },
    {PcieDdiEngine, 20, 23},
    0,                                              //Initialization Status
    0xFF,                                           //Scratch
    {0}                                             //PCIe_DDI_CONFIG
  },
  //Ddi2
  {
    {
      DESCRIPTOR_DDI_ENGINE,
      0,
      0,
      0
    },
    {PcieDdiEngine, 24, 27},
    0,                                              //Initialization Status
    0xFF,                                           //Scratch
    {0}                                             //PCIe_DDI_CONFIG
  },
  //Ddi3
  {
    {
      DESCRIPTOR_DDI_ENGINE | DESCRIPTOR_TERMINATE_LIST,
      0,
      0,
      0
    },
    {PcieDdiEngine, 28, 31},
    0,                                              //Initialization Status
    0xFF,                                           //Scratch
    {0}                                             //PCIe_DDI_CONFIG
  }
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
GfxIntegratedEnumConnectorsForDevice (
  IN       UINT8                       DisplayDeviceEnum,
     OUT   EXT_DISPLAY_PATH            *DisplayPathList,
  IN OUT   PCIe_ENGINE_CONFIG          *DdiArray
  );

VOID
GfxIntegratedDebugDumpDisplayPath (
  IN       EXT_DISPLAY_PATH                 *DisplayPath
  );

/*----------------------------------------------------------------------------------------*/

EXT_CONNECTOR_INFO ConnectorInfoTable[] = {
  {
    ConnectorTypeDP,
    DEVICE_DFP,
    CONNECTOR_DISPLAYPORT_ENUM,
    ENCODER_NOT_PRESENT,
    0,
  },
  {
    ConnectorTypeEDP,
    DEVICE_DFP,
    CONNECTOR_eDP_ENUM,
    ENCODER_NOT_PRESENT,
    1
  },
  {
    ConnectorTypeSingleLinkDVI,
    DEVICE_DFP,
    CONNECTOR_SINGLE_LINK_DVI_D_ENUM,
    ENCODER_NOT_PRESENT,
    2
  },
  {
    ConnectorTypeDualLinkDVI,
    DEVICE_DFP,
    CONNECTOR_DUAL_LINK_DVI_D_ENUM,
    ENCODER_NOT_PRESENT,
    3
  },
  {
    ConnectorTypeHDMI,
    DEVICE_DFP,
    CONNECTOR_HDMI_TYPE_A_ENUM,
    ENCODER_NOT_PRESENT,
    4
  },
  {
    ConnectorTypeDpToVga,
    DEVICE_CRT,
    CONNECTOR_VGA_ENUM,
    ENCODER_DP2VGA_ENUM_ID1,
    5
  },
  {
    ConnectorTypeDpToLvds,
    DEVICE_LCD,
    CONNECTOR_LVDS_ENUM,
    ENCODER_DP2LVDS_ENUM_ID2,
    6
  },
  {
    ConnectorTypeNutmegDpToVga,
    DEVICE_CRT,
    CONNECTOR_VGA_ENUM,
    ENCODER_ALMOND_ENUM_ID1,
    5
  },
  {
    ConnectorTypeSingleLinkDviI,
    DEVICE_DFP,
    CONNECTOR_SINGLE_LINK_DVI_I_ENUM,
    ENCODER_NOT_PRESENT,
    5
  },
  {
    ConnectorTypeCrt,
    DEVICE_CRT,
    CONNECTOR_VGA_ENUM,
    ENCODER_NOT_PRESENT,
    5
  },
  {
    ConnectorTypeLvds,
    DEVICE_LCD,
    CONNECTOR_LVDS_ENUM,
    ENCODER_NOT_PRESENT,
    6
  },
  {
    ConnectorTypeEDPToLvds,
    DEVICE_LCD,
    CONNECTOR_eDP_ENUM,
    ENCODER_NOT_PRESENT,
    1
  },
  {
    ConnectorTypeEDPToLvdsSwInit,
    DEVICE_LCD,
    CONNECTOR_eDP_ENUM,
    ENCODER_NOT_PRESENT,
    1
  },
  {
    ConnectorTypeAutoDetect,
    DEVICE_LCD,
    CONNECTOR_LVDS_eDP_ENUM,
    ENCODER_DP2LVDS_ENUM_ID2,
    7
  },
  {
    UnusedType,
    0,
    0,
    0,
    0
  },
};

UINT8 ConnectorNumerArray[] = {
//  DP    eDP   SDVI-D  DDVI-D  HDMI   VGA   LVDS   Auto (eDP, LVDS, DP-to-LVDS)
    6,    1,    6,      6,      6,     1,    1,     2
};
/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all display connectors for specific display device type.
 *
 *
 *
 * @param[in] ConnectorType   Connector type (see PCIe_DDI_DATA::ConnectorType).
 * @retval    Pointer to EXT_CONNECTOR_INFO
 * @retval    NULL if connector type unknown.
 */
EXT_CONNECTOR_INFO*
GfxIntegratedExtConnectorInfo (
  IN       UINT8                         ConnectorType
  )
{
  UINTN Index;
  for (Index = 0; Index < (sizeof (ConnectorInfoTable) / sizeof (EXT_CONNECTOR_INFO)); Index++) {
    if (ConnectorInfoTable[Index].ConnectorType == ConnectorType) {
      return &ConnectorInfoTable[Index];
    }
  }
  return NULL;
}

EXT_DISPLAY_DEVICE_INFO DisplayDeviceInfoTable[] = {
  {
    DEVICE_CRT,
    1,
    ATOM_DEVICE_CRT1_SUPPORT,
    0x100,
  },
  {
    DEVICE_LCD,
    1,
    ATOM_DEVICE_LCD1_SUPPORT,
    0x110,
  },
  {
    DEVICE_DFP,
    1,
    ATOM_DEVICE_DFP1_SUPPORT,
    0x210,
  },
  {
    DEVICE_DFP,
    2,
    ATOM_DEVICE_DFP2_SUPPORT,
    0x220,
  },
  {
    DEVICE_DFP,
    3,
    ATOM_DEVICE_DFP3_SUPPORT,
    0x230,
  },
  {
    DEVICE_DFP,
    4,
    ATOM_DEVICE_DFP4_SUPPORT,
    0x240,
  },
  {
    DEVICE_DFP,
    5,
    ATOM_DEVICE_DFP5_SUPPORT,
    0x250,
  },
  {
    DEVICE_DFP,
    6,
    ATOM_DEVICE_DFP6_SUPPORT,
    0x260,
  }
};

/*----------------------------------------------------------------------------------------*/
CONST UINT8  DdiLaneConfigArray [][4] = {
  {16, 19, 0, 0},
  {20, 23, 1, 1},
  {24, 27, 2, 2},
  {28, 31, 3, 3},
};

UINTN NumberOfDdi;
UINT8 PriorityConnectorType[4] = {0};

/*---------------------------------------------------------------------------------------*/
/**
 * Check RV OPN number
 *
 * @retval    TRUE    This is RV B4 part
 *            FALSE   This is not RV B4 part
 *
 */
BOOLEAN
CheckRvOpnB4 (
  )
{
  UINT32              RegisterData;
  UINT32              TempData32;

  SmnRegisterRead (0, SMUFUSEx000005C0_ADDRESS, &RegisterData);
  TempData32 = (RegisterData >> 30) & 0x3;
  if (TempData32 == 2) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV1 B4 \n");
    return TRUE;
  }

  // OPN = ZM2300C4T2OFB
  SmnRegisterRead (0, SMUFUSEx0000059C_ADDRESS, &RegisterData);
  if (((RegisterData >> 16) & 0xFFFF) == 0xA6DA) {
    SmnRegisterRead (0, SMUFUSEx000005A0_ADDRESS, &RegisterData);
    if (RegisterData  == 0x0D83066C) {
      SmnRegisterRead (0, SMUFUSEx000005A4_ADDRESS, &RegisterData);
      if (RegisterData  == 0xD3D95469) {
        SmnRegisterRead (0, SMUFUSEx000005A8_ADDRESS, &RegisterData);
        if ((RegisterData & 0x7FF) == 0x428) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

VOID
GfxMappingUserConfig (
  IN       DDI_DESCRIPTOR         *DdiConfig,
     OUT   PCIe_ENGINE_CONFIG     *Engine
  )
{
  BOOLEAN  LocalFlag;
  BOOLEAN  HdmiFlag;
  UINT32   Index;
  UINTN    DfpCounter;
  UINT8    DpCounter;
  UINTN    TagCounter;

  NumberOfDdi = 0;
  Index = 0;
  DfpCounter = 0;
  DpCounter = 0;
  TagCounter = 0;
  LocalFlag = FALSE;
  HdmiFlag= FALSE;

  do {
    Engine[Index].Type.Ddi.DdiData.ConnectorType = DdiConfig[Index].Ddi.ConnectorType;
    Engine[Index].Type.Ddi.DdiData.AuxIndex = DdiConfig[Index].Ddi.AuxIndex;
    Engine[Index].Type.Ddi.DdiData.HdpIndex = DdiConfig[Index].Ddi.HdpIndex;
    Engine[Index].Type.Ddi.DdiData.LanePnInversionMask = DdiConfig[Index].Ddi.LanePnInversionMask;
    Engine[Index].Type.Ddi.DdiData.Flags = DdiConfig[Index].Ddi.Flags;

    if (DdiConfig[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
      LocalFlag = TRUE;
    }
    //Init Priority Array
    if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeEDP) {
      PriorityConnectorType[Index] = 1;
    }
    if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeHDMI) {
      HdmiFlag = TRUE;
    }
    if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeDP || DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeHDMI || DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeSingleLinkDVI) {
      DfpCounter++;
    }
    NumberOfDdi++;
    Index++;
  } while (LocalFlag != TRUE);

  // Assign Tag
  while (DfpCounter != 0) {
    for (Index = 0; Index < NumberOfDdi; Index++) {
      if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeDP) {
        DpCounter++;
        DfpCounter--;
        PriorityConnectorType[Index] = DpCounter;
      }
    }
    for (Index = 0; Index < NumberOfDdi; Index++) {
      if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeHDMI) {
        DpCounter++;
        DfpCounter--;
        PriorityConnectorType[Index] = DpCounter;
      }
    }
    for (Index = 0; Index < NumberOfDdi; Index++) {
      if (DdiConfig[Index].Ddi.ConnectorType == ConnectorTypeSingleLinkDVI) {
        DpCounter++;
        DfpCounter--;
        PriorityConnectorType[Index] = DpCounter;
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Initialize display path for given engine
 *
 *
 *
 * @param[in]   Engine            Engine configuration info
 * @param[out]  DisplayPathList   Display path list
 */

AGESA_STATUS
GfxMapEngineToDisplayPath (
  IN       PCIe_ENGINE_CONFIG          *Engine,
     OUT   EXT_DISPLAY_PATH            *DisplayPathList
  )
{
  AGESA_STATUS      Status;
  UINT8             PrimaryDisplayPathId;
  UINT8             SecondaryDisplayPathId;
  UINTN             DisplayPathIndex;
  PrimaryDisplayPathId = 0xff;
  SecondaryDisplayPathId = 0xff;
  for (DisplayPathIndex = 0; DisplayPathIndex <  (sizeof (DdiLaneConfigArray) / 4); DisplayPathIndex++) {
    if (DdiLaneConfigArray[DisplayPathIndex][0] == Engine->EngineData.StartLane &&
        DdiLaneConfigArray[DisplayPathIndex][1] == Engine->EngineData.EndLane) {
      PrimaryDisplayPathId = DdiLaneConfigArray[DisplayPathIndex][2];
      SecondaryDisplayPathId = DdiLaneConfigArray[DisplayPathIndex][3];
      break;
    }
  }
  if (PrimaryDisplayPathId != 0xff) {
    IDS_HDT_CONSOLE (GFX_MISC, "  Allocate Display Connector at Primary sPath[%d]\n", PrimaryDisplayPathId);
    Engine->InitStatus |= INIT_STATUS_DDI_ACTIVE;
    GfxIntegratedCopyDisplayInfo (
      &Engine->Type.Ddi,
      &DisplayPathList[PrimaryDisplayPathId],
      (PrimaryDisplayPathId != SecondaryDisplayPathId) ? &DisplayPathList[SecondaryDisplayPathId] : NULL
      );
    Status = AGESA_SUCCESS;
  } else {
    IDS_HDT_CONSOLE (GFX_MISC, "  Error!!! Map DDI lanes %d - %d to display path failed\n",
      Engine->EngineData.StartLane,
      Engine->EngineData.EndLane
      );
    Status = AGESA_ERROR;
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all display connectors for specific display device type.
 *
 *
 *
 * @param[in] DisplayDeviceEnum   Display device enum
 * @param[in] DisplayDeviceIndex  Display device index
 * @retval    Pointer to EXT_DISPLAY_DEVICE_INFO
 * @retval    NULL if can not get display device info
 */
EXT_DISPLAY_DEVICE_INFO*
GfxIntegratedExtDisplayDeviceInfo (
  IN       UINT8                         DisplayDeviceEnum,
  IN       UINT8                         DisplayDeviceIndex
  )
{
  UINT8 Index;
  UINT8 LastIndex;
  LastIndex = 0xff;
  for (Index = 0; Index < (sizeof (DisplayDeviceInfoTable) / sizeof (EXT_DISPLAY_DEVICE_INFO)); Index++) {
    if (DisplayDeviceInfoTable[Index].DisplayDeviceEnum == DisplayDeviceEnum) {
      LastIndex = Index;
      if (DisplayDeviceInfoTable[Index].DeviceIndex == DisplayDeviceIndex) {
        return &DisplayDeviceInfoTable[Index];
      }
    }
  }
  if (DisplayDeviceEnum == DEVICE_LCD && LastIndex != 0xff) {
    return &DisplayDeviceInfoTable[LastIndex];
  }
  return NULL;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all display connectors
 *
 *
 *
 * @param[out]    DisplayPathList   Display path list
 * @param[in,out] Pcie              PCIe platform configuration info
 * @param[in]     Gfx               Gfx configuration info
 */
AGESA_STATUS
GfxIntegratedEnumerateAllConnectors (
     OUT   EXT_DISPLAY_PATH            *DisplayPathList
  )
{
  AGESA_STATUS                      AgesaStatus;
  AGESA_STATUS                      Status;
  PCIe_ENGINE_CONFIG                DdiComplexData[4];
  DXIO_COMPLEX_DESCRIPTOR           *PcieTopologyData;
  PEI_AMD_NBIO_PCIE_COMPLEX_PPI     *NbioPcieComplexPpi;
  CONST EFI_PEI_SERVICES            **PeiServices;
  EXT_CONNECTOR_INFO                *ExtConnectorInfo;
  EXT_DISPLAY_DEVICE_INFO           *ExtDisplayDeviceInfo;
  UINT32                            DdiCounter;
  EXT_DISPLAY_PATH                  *StoreDisplayPathList;
  UINT8                             DisplayDeviceIndex;
  BOOLEAN                           IsRvB4;
  BOOLEAN                           IsEdp;
  UINT32                            ResultValue;
  AMD_PEI_SOC_LOGICAL_ID_PPI      *SocLogicalIdPpi;
  SOC_LOGICAL_ID                  LogicalId;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntegratedEnumerateAllConnectors Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  IsRvB4 = FALSE;
  IsEdp = FALSE;
  ExtDisplayDeviceInfo = NULL;
  LogicalId.Revision = AMD_REVISION_UNKNOWN;
  LogicalId.Family = AMD_FAMILY_UNKNOWN;

  LibAmdMemCopy (DdiComplexData, DdiComplexDataRV, sizeof (PCIe_ENGINE_CONFIG) * 4, (AMD_CONFIG_PARAMS *)NULL);
  // locate CPM DDI table here, and initialize DdiComplexData.
  PeiServices = GetPeiServicesTablePointer ();
  Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdNbioPcieComplexPpiGuid, 0, NULL, &NbioPcieComplexPpi);
  if (!EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "gAmdNbioPcieComplexPpiGuid is installed\n");
    NbioPcieComplexPpi->PcieGetComplex (NbioPcieComplexPpi, &PcieTopologyData);
    GfxMappingUserConfig (PcieTopologyData->DdiLinkList, &DdiComplexData[0]);
  }

  StoreDisplayPathList = DisplayPathList;
  DisplayDeviceIndex = 1;


  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdSocLogicalIdPpiGuid,
                             0,
                             NULL,
                             &SocLogicalIdPpi
                             );
  if (!EFI_ERROR (Status)) {
    Status = SocLogicalIdPpi->GetLogicalIdOnCurrentCore (&LogicalId);
  }

  IsRvB4 = CheckRvOpnB4 ();

  for (DdiCounter = 0; DdiCounter < NumberOfDdi; DdiCounter++) {
    ExtConnectorInfo = GfxIntegratedExtConnectorInfo (DdiComplexData[DdiCounter].Type.Ddi.DdiData.ConnectorType);
    IDS_HDT_CONSOLE (GNB_TRACE, "ExtConnectorInfo %x\n", ExtConnectorInfo);
    IDS_HDT_CONSOLE (GNB_TRACE, "ExtConnectorInfo->ConnectorType %x\n", ExtConnectorInfo->ConnectorType);
    //
    // Remapping DDI3 to DDI4 for Rv1 B4 CPU
    //
    if(IsRvB4 == TRUE) {
      if (DisplayDeviceIndex == 3) {
        DisplayDeviceIndex = 4;
        StoreDisplayPathList++;
        ExtDisplayDeviceInfo++;
      }
    }

    StoreDisplayPathList->usDeviceConnector = ExtConnectorInfo->ConnectorEnum | (PriorityConnectorType[DdiCounter] << 8);

    IDS_HDT_CONSOLE (GNB_TRACE, "DisplayPathList->usDeviceConnector %x\n", DisplayPathList->usDeviceConnector);
    ExtDisplayDeviceInfo = GfxIntegratedExtDisplayDeviceInfo (ExtConnectorInfo->DisplayDeviceEnum, PriorityConnectorType[DdiCounter]);

    StoreDisplayPathList->usDeviceTag = ExtDisplayDeviceInfo->DeviceTag;
    StoreDisplayPathList->usDeviceACPIEnum = ExtDisplayDeviceInfo->DeviceAcpiEnum;//0x210;  // ExtDisplayDeviceInfo->DeviceAcpiEnum

    //eDP Case
    if (ExtConnectorInfo->ConnectorType == ConnectorTypeEDP) {
      StoreDisplayPathList->usDeviceConnector = ExtConnectorInfo->ConnectorEnum | (1 << 8);
      IDS_HDT_CONSOLE (GNB_TRACE, "StoreDisplayPathList->usDeviceConnecto %x\n", StoreDisplayPathList->usDeviceConnector);
      StoreDisplayPathList->usDeviceTag = 0x2;
      StoreDisplayPathList->usDeviceACPIEnum = 0x110;//0x210;  // ExtDisplayDeviceInfo->DeviceAcpiEnum
      IsEdp = TRUE;
    }

    StoreDisplayPathList->ucExtAUXDDCLutIndex = DdiComplexData[DdiCounter].Type.Ddi.DdiData.AuxIndex;
    StoreDisplayPathList->ucExtHPDPINLutIndex = DdiComplexData[DdiCounter].Type.Ddi.DdiData.HdpIndex;
    StoreDisplayPathList->ChannelMapping.ucChannelMapping = 0xE4;
    StoreDisplayPathList->ucChPNInvert = 0;
    StoreDisplayPathList->usCaps = DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags;
    //DP case
    if (ExtConnectorInfo->ConnectorType == ConnectorTypeDP) {
      switch (DdiCounter) {
        case 0:
          if (PcdGetBool (PcdDpHBR2Disable0) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR2_DISABLE);
          }
          if (PcdGetBool (PcdDpHBR3Disable0) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR3_DISABLE);
          }
        break;
        case 1:
          if (PcdGetBool (PcdDpHBR2Disable1) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR2_DISABLE);
          }
          if (PcdGetBool (PcdDpHBR3Disable1) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR3_DISABLE);
          }
        break;
        case 2:
          if (PcdGetBool (PcdDpHBR2Disable2) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR2_DISABLE);
          }
          if (PcdGetBool (PcdDpHBR3Disable2) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR3_DISABLE);
          }
        break;
        case 3:
          if (PcdGetBool (PcdDpHBR2Disable3) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR2_DISABLE);
          }
          if (PcdGetBool (PcdDpHBR3Disable3) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HBR3_DISABLE);
          }
        break;
        default:
        break;
      }
    }
    // HDMI case - follow VBIOS rule,in some case even in DP type still has chance to disable HDMI Caps.
    if (ExtConnectorInfo->ConnectorType == ConnectorTypeHDMI || ExtConnectorInfo->ConnectorType == ConnectorTypeDP) {
      switch (DdiCounter) {
        case 0:
          if (PcdGetBool (PcdHDMI2Disable0) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HDMI20_DISABLE);
          }
        break;
        case 1:
          if (PcdGetBool (PcdHDMI2Disable1) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HDMI20_DISABLE);
          }
        break;
        case 2:
          if (PcdGetBool (PcdHDMI2Disable2) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HDMI20_DISABLE);
          }
        break;
        case 3:
          if (PcdGetBool (PcdHDMI2Disable3) == TRUE) {
            StoreDisplayPathList->usCaps = (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_HDMI20_DISABLE);
          }
        break;
        default:
        break;
      }
    }
	//<Embedded_Override_Start>
    /*
    if (DdiCounter == 2 || DdiCounter == 3) {
      StoreDisplayPathList->usCaps |= (DdiComplexData[DdiCounter].Type.Ddi.DdiData.Flags | ATOM_ENCODER_CAP_RECORD_USB_C_TYPE);
    }
	//<Embedded_Override_Start>
	if (ExtConnectorInfo->ConnectorType == ConnectorTypeHDMI || ExtConnectorInfo->ConnectorType == ConnectorTypeDP || ExtConnectorInfo->ConnectorType == ConnectorTypeEDP  )
    {
     StoreDisplayPathList->usCaps &= ~ATOM_ENCODER_CAP_RECORD_USB_C_TYPE;
    }
	//<Embedded_Override_End>
	*/
	//<Embedded_Override_End>

    if (ExtConnectorInfo->ConnectorType == UnusedType) {
      StoreDisplayPathList->usDeviceTag = 0;
      StoreDisplayPathList->usDeviceACPIEnum = 0;
      StoreDisplayPathList->usDeviceConnector = 0;
      StoreDisplayPathList->ucExtAUXDDCLutIndex = 0;
      StoreDisplayPathList->ucExtHPDPINLutIndex = 0;
      StoreDisplayPathList->ChannelMapping.ucChannelMapping = 0;
      StoreDisplayPathList->ucChPNInvert = 0;
      StoreDisplayPathList->usCaps = 0;
      StoreDisplayPathList->usExtEncoderObjId = 0;
    }

    IDS_HDT_CONSOLE (GNB_TRACE, "Address of StoreDisplayPathList %x\n", StoreDisplayPathList);
    IDS_HDT_CONSOLE (GNB_TRACE, "Address of ExtConnectorInfo %x\n", ExtConnectorInfo);
    IDS_HDT_CONSOLE (GNB_TRACE, "StoreDisplayPathList usCaps: %x\n", StoreDisplayPathList->usCaps);

    StoreDisplayPathList++;
    ExtDisplayDeviceInfo++;
    DisplayDeviceIndex++;
  }

  if (IsEdp == TRUE) {
    SmnRegisterRMW (
      0,
      LVTMA_PWRSEQ_CNTL_ADDRESS,
      (UINT32)~(LVTMA_PWRSEQ_EN_Mask |
      LVTMA_PWRSEQ_TARGET_STATE_Mask |
      LVTMA_BLON_OVRD_Mask),
      (UINT32) (1 << LVTMA_PWRSEQ_EN_OFFSET |
      1 << LVTMA_PWRSEQ_TARGET_STATE_OFFSET |
      1 << LVTMA_BLON_OVRD_OFFSET),
      0
      );

    SmnRegisterRead (0,LVTMA_PWRSEQ_CNTL_ADDRESS, &ResultValue);
    IDS_HDT_CONSOLE (MAIN_FLOW, "LVTMA_PWRSEQ_CNTL_ADDRESS : %x \n", ResultValue);
  }

  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntegratedEnumerateAllConnectors Exit [0x%x]\n", Status);
  return AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all display connectors for specific display device type.
 *
 *
 *
 * @param[in]     Engine  Engine configuration info
 * @param[in,out] Buffer  Buffer pointer
 * @param[in]     Pcie    PCIe configuration info
 */
VOID
STATIC
GfxIntegratedDdiInterfaceCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   CONNECTOR_ENUM_INFO   *ConnectorEnumInfo
  )
{
  EXT_CONNECTOR_INFO      *ExtConnectorInfo;

  if (!(Engine->Header.DescriptorFlags & DESCRIPTOR_ALLOCATED) || !(Engine->Header.DescriptorFlags & DESCRIPTOR_DDI_ENGINE)) {
    return;
  }

  ExtConnectorInfo = GfxIntegratedExtConnectorInfo (Engine->Type.Ddi.DdiData.ConnectorType);
  if (ExtConnectorInfo == NULL) {
    AGESA_STATUS_UPDATE (AGESA_ERROR, ConnectorEnumInfo->Status);
    PcieConfigResetDescriptorFlags (Engine, DESCRIPTOR_ALLOCATED);
    return;
  }
  if (ExtConnectorInfo->DisplayDeviceEnum != ConnectorEnumInfo->DisplayDeviceEnum) {
    //Not device type we are looking for
    return;
  }
  if (Engine->Type.Ddi.DisplayPriorityIndex >=  ConnectorEnumInfo->RequestedPriorityIndex &&
      Engine->Type.Ddi.DisplayPriorityIndex <  ConnectorEnumInfo->CurrentPriorityIndex) {
    ConnectorEnumInfo->CurrentPriorityIndex = Engine->Type.Ddi.DisplayPriorityIndex;
    ConnectorEnumInfo->Engine = Engine;
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all display connectors for specific display device type.
 *
 *
 *
 * @param[in]     DisplayDeviceEnum Display device list
 * @param[out]    DisplayPathList   Display path list
 * @param[in,out] Pcie              PCIe configuration info
 * @param[in]     Gfx               Gfx configuration info
 */
AGESA_STATUS
GfxIntegratedEnumConnectorsForDevice (
  IN       UINT8                       DisplayDeviceEnum,
     OUT   EXT_DISPLAY_PATH            *DisplayPathList,
  IN OUT   PCIe_ENGINE_CONFIG          *DdiArray
  )
{
  UINT8                   DisplayDeviceIndex;
  CONNECTOR_ENUM_INFO     ConnectorEnumInfo;
  EXT_CONNECTOR_INFO      *ExtConnectorInfo;
  EXT_DISPLAY_DEVICE_INFO *ExtDisplayDeviceInfo;
  AGESA_STATUS            Status;
  UINT32                  Index;
  UINT8                   ConnectorIdArray[sizeof (ConnectorNumerArray)];

  ConnectorEnumInfo.Status = AGESA_SUCCESS;
  DisplayDeviceIndex = 1;
  ConnectorEnumInfo.RequestedPriorityIndex = 0;
  ConnectorEnumInfo.DisplayDeviceEnum = DisplayDeviceEnum;
  LibAmdMemFill (ConnectorIdArray, 0x00, sizeof (ConnectorIdArray), (AMD_CONFIG_PARAMS *)NULL);
  do {
    ConnectorEnumInfo.Engine = NULL;
    ConnectorEnumInfo.CurrentPriorityIndex = 0xff;

    for (Index = 0; Index < 4; Index++) {
      GfxIntegratedDdiInterfaceCallback (&DdiArray[Index], &ConnectorEnumInfo);
    }
    if (ConnectorEnumInfo.Engine == NULL) {
      break;                                  // No more connector support this
    }
    ConnectorEnumInfo.RequestedPriorityIndex = ConnectorEnumInfo.CurrentPriorityIndex + 1;
    ExtConnectorInfo = GfxIntegratedExtConnectorInfo (ConnectorEnumInfo.Engine->Type.Ddi.DdiData.ConnectorType);
//    ASSERT (ExtConnectorInfo != NULL);
//    ASSERT (ExtConnectorInfo->ConnectorIndex < sizeof (ConnectorIdArray));
    if (ConnectorIdArray[ExtConnectorInfo->ConnectorIndex] >=  ConnectorNumerArray[ExtConnectorInfo->ConnectorIndex]) {
      //Run out of supported connectors
      AGESA_STATUS_UPDATE (AGESA_ERROR, ConnectorEnumInfo.Status);
      PcieConfigResetDescriptorFlags (ConnectorEnumInfo.Engine, DESCRIPTOR_ALLOCATED);
      continue;
    }
    ConnectorEnumInfo.Engine->Type.Ddi.ConnectorId = ConnectorIdArray[ExtConnectorInfo->ConnectorIndex] + 1;
    ExtDisplayDeviceInfo = GfxIntegratedExtDisplayDeviceInfo (DisplayDeviceEnum, DisplayDeviceIndex);
    if (ExtDisplayDeviceInfo == NULL) {
      //Run out of supported display device types
      AGESA_STATUS_UPDATE (AGESA_ERROR, ConnectorEnumInfo.Status);
      Status = AGESA_ERROR;
      PcieConfigResetDescriptorFlags (ConnectorEnumInfo.Engine, DESCRIPTOR_ALLOCATED);
    }

//    if ((Gfx->Gnb3dStereoPinIndex != 0) && (ConnectorEnumInfo.Engine->Type.Ddi.DdiData.HdpIndex == (Gfx->Gnb3dStereoPinIndex - 1))) {
//      AGESA_STATUS_UPDATE (AGESA_ERROR, ConnectorEnumInfo.Status);
//      Status = AGESA_ERROR;
//      PcieConfigDisableEngine (ConnectorEnumInfo.Engine);
//    }

    ConnectorEnumInfo.Engine->Type.Ddi.DisplayDeviceId = DisplayDeviceIndex;

    Status = GfxMapEngineToDisplayPath (ConnectorEnumInfo.Engine, DisplayPathList);
    AGESA_STATUS_UPDATE (Status, ConnectorEnumInfo.Status);
    if (Status != AGESA_SUCCESS) {
      continue;
    }
    ConnectorIdArray[ExtConnectorInfo->ConnectorIndex]++;
    DisplayDeviceIndex++;
  } while (ConnectorEnumInfo.Engine != NULL);
  return ConnectorEnumInfo.Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Initialize display path for given engine
 *
 *
 *
 * @param[in]  Engine            Engine configuration info
 * @param[out] DisplayPath       Display path list
 * @param[out] SecondaryDisplayPath Secondary display path list
 */

VOID
GfxIntegratedCopyDisplayInfo (
  IN       PCIe_DDI_CONFIG             *DdiEngine,
     OUT   EXT_DISPLAY_PATH            *DisplayPath,
     OUT   EXT_DISPLAY_PATH            *SecondaryDisplayPath
  )
{
  EXT_CONNECTOR_INFO      *ExtConnectorInfo;
  EXT_DISPLAY_DEVICE_INFO *ExtDisplayDeviceInfo;

  ExtConnectorInfo = GfxIntegratedExtConnectorInfo (DdiEngine->DdiData.ConnectorType);
  ExtDisplayDeviceInfo = GfxIntegratedExtDisplayDeviceInfo (ExtConnectorInfo->DisplayDeviceEnum, DdiEngine->DisplayDeviceId);
  DisplayPath->usDeviceConnector = ExtConnectorInfo->ConnectorEnum | (DdiEngine->ConnectorId << 8);
  DisplayPath->usDeviceTag = ExtDisplayDeviceInfo->DeviceTag;
  DisplayPath->usDeviceACPIEnum = ExtDisplayDeviceInfo->DeviceAcpiEnum;
  DisplayPath->ucExtAUXDDCLutIndex = DdiEngine->DdiData.AuxIndex;
  DisplayPath->ucExtHPDPINLutIndex = DdiEngine->DdiData.HdpIndex;
  DisplayPath->ucChPNInvert = DdiEngine->DdiData.LanePnInversionMask;
  DisplayPath->usCaps = DdiEngine->DdiData.Flags;
  DisplayPath->usExtEncoderObjId = ExtConnectorInfo->EncoderEnum;
  if (DdiEngine->DdiData.Mapping[0].ChannelMappingValue == 0) {
    DisplayPath->ChannelMapping.ucChannelMapping = 0xE4; //0x1B;
  } else {
    DisplayPath->ChannelMapping.ucChannelMapping = DdiEngine->DdiData.Mapping[0].ChannelMappingValue;
  }
  GfxIntegratedDebugDumpDisplayPath (DisplayPath);
  if (DdiEngine->DdiData.ConnectorType == ConnectorTypeDualLinkDVI) {
    if (SecondaryDisplayPath != NULL) {
      SecondaryDisplayPath->usDeviceConnector = DisplayPath->usDeviceConnector;
    }
    GfxIntegratedDebugDumpDisplayPath (DisplayPath);

    if (DdiEngine->DdiData.Mapping[1].ChannelMappingValue == 0) {
      DisplayPath->ChannelMapping.ucChannelMapping = 0xE4; //0x1B;
    } else {
      DisplayPath->ChannelMapping.ucChannelMapping = DdiEngine->DdiData.Mapping[1].ChannelMappingValue;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump  display path settings
 *
 *
 *
 * @param[in] DisplayPath            Display path
 */

VOID
GfxIntegratedDebugDumpDisplayPath (
  IN       EXT_DISPLAY_PATH            *DisplayPath
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceConnector = 0x%x\n",
   DisplayPath->usDeviceConnector
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceTag = 0x%x\n",
   DisplayPath->usDeviceTag
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceACPIEnum = 0x%x\n",
   DisplayPath->usDeviceACPIEnum
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usExtEncoderObjId = 0x%x\n",
   DisplayPath->usExtEncoderObjId
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     ucChannelMapping = 0x%x\n",
   DisplayPath->ChannelMapping.ucChannelMapping
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     ucChPNInvert = 0x%x\n",
   DisplayPath->ucChPNInvert
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usCaps = 0x%x\n",
   DisplayPath->usCaps
   );
}

