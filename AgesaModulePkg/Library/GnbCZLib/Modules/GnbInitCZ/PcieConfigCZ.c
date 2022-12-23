/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific PCIe wrapper configuration services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 328567 $   @e \$Date: 2015-10-10 03:21:46 +0800 (Sat, 10 Oct 2015) $
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
#include  <Library/BaseLib.h>
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLib.h"
#include  "GnbRegistersCZ.h"
#include  "GnbRegisterAccCZ.h"
#include  "PcieComplexDataCZ.h"
#include  <AmdSoc.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_PCIECONFIGCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define DEVFUNC(d, f) ((((UINT8) d) << 3) | ((UINT8) f))

extern PCIe_LANE_ALLOC_DESCRIPTOR ROMDATA   PcieLaneAllocConfigurationCZ[];

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
PcieConfigurePcieEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIe_LANE_ALLOC_DESCRIPTOR    *PcieLaneConfig,
  IN      UINT8                         ConfigurationId
  );

AGESA_STATUS
PcieConfigureDdiEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIe_LANE_ALLOC_DESCRIPTOR    *DdiLaneConfig,
  IN      UINT8                         ConfigurationId
  );

AGESA_STATUS
PcieConfigureEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIE_ENGINE_TYPE              EngineType,
  IN      UINT8                         ConfigurationId
  );

AGESA_STATUS
PcieGetCoreConfigurationValueCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 CoreId,
  IN      UINT64                ConfigurationSignature,
  IN      UINT8                 *ConfigurationValue
  );

BOOLEAN
PcieCheckPortPciDeviceMappingCZ (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  );

CONST CHAR8*
PcieDebugGetCoreConfigurationStringCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 ConfigurationValue
  );

CONST CHAR8*
PcieDebugGetWrapperNameStringCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper
  );

CONST CHAR8*
PcieDebugGetHostRegAddressSpaceStringCZ (
  IN      PCIe_SILICON_CONFIG    *Silicon,
  IN      UINT16                 AddressFrame
  );

BOOLEAN
PcieCheckPortPcieLaneCanBeMuxedCZ (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  );

AGESA_STATUS
PcieMapPortPciAddressCZ (
  IN      PCIe_ENGINE_CONFIG     *Engine
  );

AGESA_STATUS
PcieGetSbConfigInfoCZ (
  IN       UINT8                         SocketId,
     OUT   PCIe_PORT_DESCRIPTOR          *SbPort,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );


//
// Default port dev map
//
UINT8 ROMDATA DefaultPortDevMapCZ [] = {
  DEVFUNC (2, 1),
  DEVFUNC (2, 2),
  DEVFUNC (2, 3),
  DEVFUNC (2, 4),
  DEVFUNC (2, 5),
  DEVFUNC (3, 1),
  DEVFUNC (3, 2),
  DEVFUNC (3, 3),
  DEVFUNC (3, 4),
  DEVFUNC (3, 5)
};

/*----------------------------------------------------------------------------------------*/
//
// Default apic config
//

///@todo IOAPIC has not been confirmed
APIC_DEVICE_INFO ROMDATA DefaultIoapicConfigCZ [] = {
  {0, 0, 0x17},
  {2, 0, 0x18},
  {4, 0, 0x19},
  {6, 0, 0x1A},
  {0, 1, 0x17},
  {2, 1, 0x0F},
  {4, 1, 0x10},
  {6, 1, 0x11},
  {0, 2, 0x12},
  {2, 2, 0x0F}
};


/*----------------------------------------------------------------------------------------*/
/**
 * Configure engine list to support lane allocation according to configuration ID.
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  PcieLaneConfig       Lane configuration descriptor
 * @param[in]  ConfigurationId     Configuration ID
 * @retval     AGESA_SUCCESS       Configuration successfully applied
 * @retval     AGESA_ERROR         Requested configuration not supported
 */
AGESA_STATUS
PcieConfigurePcieEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIe_LANE_ALLOC_DESCRIPTOR    *PcieLaneConfig,
  IN      UINT8                         ConfigurationId
  )
{
  UINT8               CoreLaneIndex;
  PCIe_ENGINE_CONFIG  *EnginesList;

  if (ConfigurationId >= PcieLaneConfig->NumberOfConfigurations) {
    return AGESA_ERROR;
  }
  EnginesList = PcieConfigGetChildEngine (Wrapper);
  CoreLaneIndex = ConfigurationId * PcieLaneConfig->NumberOfEngines * 2;

  while (EnginesList != NULL) {
    if (PcieLibIsPcieEngine (EnginesList)) {
      PcieConfigResetDescriptorFlags (EnginesList, DESCRIPTOR_ALLOCATED);
      EnginesList->Type.Port.StartCoreLane = PcieLaneConfig->ConfigTable[CoreLaneIndex++];
      EnginesList->Type.Port.EndCoreLane = PcieLaneConfig->ConfigTable[CoreLaneIndex++];
    }
    EnginesList = PcieLibGetNextDescriptor (EnginesList);
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Configure engine list to support lane allocation according to configuration ID.
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  DdiLaneConfig       Lane configuration descriptor
 * @param[in]  ConfigurationId     Configuration ID
 * @retval     AGESA_SUCCESS       Configuration successfully applied
 * @retval     AGESA_ERROR         Requested configuration not supported
 */
AGESA_STATUS
PcieConfigureDdiEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIe_LANE_ALLOC_DESCRIPTOR    *DdiLaneConfig,
  IN      UINT8                         ConfigurationId
  )
{
  UINTN               LaneIndex;
  PCIe_ENGINE_CONFIG  *EnginesList;
  if (ConfigurationId >= DdiLaneConfig->NumberOfConfigurations) {
    return AGESA_ERROR;
  }
  LaneIndex = ConfigurationId * DdiLaneConfig->NumberOfEngines * 2;
  EnginesList = PcieConfigGetChildEngine (Wrapper);
  while (EnginesList != NULL) {
    if (PcieLibIsDdiEngine (EnginesList)) {
      PcieConfigResetDescriptorFlags (EnginesList, DESCRIPTOR_ALLOCATED);
      EnginesList->EngineData.StartLane = DdiLaneConfig->ConfigTable[LaneIndex++] + Wrapper->StartPhyLane;
      EnginesList->EngineData.EndLane = DdiLaneConfig->ConfigTable[LaneIndex++] + Wrapper->StartPhyLane;
    }
    EnginesList = PcieLibGetNextDescriptor (EnginesList);
  }
  return  AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Configure engine list to support lane allocation according to configuration ID.
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  EngineType          Engine Type
 * @param[in]  ConfigurationId     Configuration ID
 * @retval     AGESA_SUCCESS       Configuration successfully applied
 * @retval     AGESA_ERROR         Requested configuration not supported
 */
AGESA_STATUS
PcieConfigureEnginesLaneAllocationCZ (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIE_ENGINE_TYPE              EngineType,
  IN      UINT8                         ConfigurationId
  )
{
  AGESA_STATUS                Status;
  PCIe_LANE_ALLOC_DESCRIPTOR  *LaneConfigDescriptor;

  Status = AGESA_ERROR;
  LaneConfigDescriptor = PcieLaneAllocConfigurationCZ;
  while (LaneConfigDescriptor != NULL) {
    if (LaneConfigDescriptor->WrapId == Wrapper->WrapId && LaneConfigDescriptor->EngineType == EngineType) {
      switch (EngineType) {
      case PciePortEngine:
        Status = PcieConfigurePcieEnginesLaneAllocationCZ (Wrapper, LaneConfigDescriptor, ConfigurationId);
        break;
      case PcieDdiEngine:
        Status = PcieConfigureDdiEnginesLaneAllocationCZ (Wrapper, LaneConfigDescriptor, ConfigurationId);
        break;
      default:
        ASSERT (FALSE);
      }
      break;
    }
    LaneConfigDescriptor = PcieConfigGetNextDataDescriptor (LaneConfigDescriptor);
  }
  return Status;
}



/*----------------------------------------------------------------------------------------*/
/**
 * Get core configuration value
 *
 *
 *
 * @param[in]  Wrapper                Pointer to internal configuration data area
 * @param[in]  CoreId                 Core ID
 * @param[in]  ConfigurationSignature Configuration signature
 * @param[out] ConfigurationValue     Configuration value (for core configuration)
 * @retval     AGESA_SUCCESS          Configuration successfully applied
 * @retval     AGESA_ERROR            Core configuration value can not be determined
 */
AGESA_STATUS
PcieGetCoreConfigurationValueCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 CoreId,
  IN      UINT64                ConfigurationSignature,
  IN      UINT8                 *ConfigurationValue
  )
{

  AGESA_STATUS  Status;
  Status = AGESA_SUCCESS;
  switch (ConfigurationSignature) {
  case GFX_CORE_x8:
    *ConfigurationValue = 0x0;
    break;
  case GPP_CORE_x4x1x1x1x1:
    *ConfigurationValue = 0x4;
    break;
  case GPP_CORE_x4x2x1x1:
    *ConfigurationValue = 0x3;
    break;
  case GPP_CORE_x4x2x2:
    *ConfigurationValue = 0x2;
    break;
  case GPP_CORE_x4x4:
    *ConfigurationValue = 0x1;
    break;
  default:
    IDS_HDT_CONSOLE (PCIE_MISC, "ERROR!!![%s Wrapper] Unknown core config signature 0x%08x%08x\n",
      PcieDebugGetWrapperNameStringCZ (Wrapper),
      ((UINT32 *) &ConfigurationSignature)[1],
      ((UINT32 *) &ConfigurationSignature)[0]
    );
    ASSERT (FALSE);
    Status = AGESA_ERROR;
  }
  return  Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Check if engine can be remapped to Device/function number requested by user
 * defined engine descriptor
 *
 *   Function only called if requested device/function does not much native device/function
 *
 * @param[in]  PortDescriptor      Pointer to user defined engine descriptor
 * @param[in]  Engine              Pointer engine configuration
 * @retval     TRUE                Descriptor can be mapped to engine
 * @retval     FALSE               Descriptor can NOT be mapped to engine
 */

BOOLEAN
PcieCheckPortPciDeviceMappingCZ (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  )
{
  UINT8 DevFunc;
  UINT8 Index;
  DevFunc = DEVFUNC (PortDescriptor->Port.DeviceNumber, PortDescriptor->Port.FunctionNumber);
  if (PortDescriptor->Port.MiscControls.SbLink == 1) {
    IDS_HDT_CONSOLE (GNB_TRACE, "Found SB...\n");
    if ((PortDescriptor->Port.DeviceNumber != Engine->Type.Port.NativeDevNumber) || (PortDescriptor->Port.FunctionNumber != Engine->Type.Port.NativeFunNumber)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Not default config\n");
      return FALSE;
    }
  }
  if (DevFunc == 0) {
    return TRUE;
  }
  for (Index = 0; Index < (sizeof (DefaultPortDevMapCZ) / sizeof (DefaultPortDevMapCZ[0])); Index++) {
    if (DefaultPortDevMapCZ[Index] == DevFunc) {
      return TRUE;
    }
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get core configuration string
 *
 *   Debug function for logging configuration
 *
 * @param[in] Wrapper              Pointer to internal configuration data area
 * @param[in] ConfigurationValue   Configuration value
 * @retval                         Configuration string
 */

CONST CHAR8*
PcieDebugGetCoreConfigurationStringCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 ConfigurationValue
  )
{
  ///@todo CZ STRAP_BIF_LINK_CONFIG has not been confirmed
  switch (ConfigurationValue) {

  case 0x0:
    return "8";
  case 0x4:
    return "4:1:1:1:1";
  case 0x3:
    return "4:2:1:1";
  case 0x2:
    return "4:2:2";
  case 0x1:
    return "4:4";
  default:
    break;
  }
  return " !!! Something Wrong !!!";
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get wrapper name
 *
 *  Debug function for logging wrapper name
 *
 * @param[in] Wrapper              Pointer to internal configuration data area
 * @retval                         Wrapper Name string
 */

CONST CHAR8*
PcieDebugGetWrapperNameStringCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper
  )
{
  switch (Wrapper->WrapId) {
  case  GFX_WRAP_ID:
    return "GFX";
  case  GPP_WRAP_ID:
    return "GPP";
  case  DDI_WRAP_ID:
    return "Virtual DDI";
  default:
    break;
  }
  return " !!! Something Wrong !!!";
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get register address name
 *
 *  Debug function for logging register trace
 *
 * @param[in] Silicon              Silicon config descriptor
 * @param[in] AddressFrame         Address Frame
 * @retval                         Register address name
 */
CONST CHAR8*
PcieDebugGetHostRegAddressSpaceStringCZ (
  IN      PCIe_SILICON_CONFIG    *Silicon,
  IN      UINT16                 AddressFrame
  )
{
  switch (AddressFrame) {
  case  0x130:
    return "PSX80 WRAP PCIE";//"GPP WRAP";
  case  0x131:
    return "PSX81 WRAP PCIE";//"GFX WRAP";

  case  0x110:
    return "PSX80 PIF0";//"GPP PIF0";
  case  0x111:
    return "PSX81 PIF0";//"GFX PIF0";


  case  0x120:
    return "PSX80 PHY0";//"GPP PHY0";
  case  0x121:
    return "PSX81 PHY0";//"GFX PHY0";


  case  0x140:
    return "PSX80 BIF (CORE)";//"GPP CORE";
  case  0x141:
    return "PSX81 BIF (CORE)";//"GFX CORE";

  case  0x150:
    return "PSX80 WRAP BIF";
  case  0x151:
    return "PSX81 WRAP BIF";

  default:
    break;
  }
  return " !!! Something Wrong !!!";
}


/*----------------------------------------------------------------------------------------*/
/**
 * Check if the lane can be muxed by link width requested by user
 * defined engine descriptor
 *
 *    Check Engine StartCoreLane could be aligned by user requested link width(x1, x2, x4, x8, x16).
 *    Check Engine StartCoreLane could be aligned by user requested link width x2.
 *
 * @param[in]  PortDescriptor      Pointer to user defined engine descriptor
 * @param[in]  Engine              Pointer engine configuration
 * @retval     TRUE                Lane can be muxed
 * @retval     FALSE               Lane can NOT be muxed
 */

BOOLEAN
PcieCheckPortPcieLaneCanBeMuxedCZ (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  )
{
  UINT16                DescriptorHiLane;
  UINT16                DescriptorLoLane;
  UINT16                DescriptorNumberOfLanes;
  PCIe_WRAPPER_CONFIG   *Wrapper;
  UINT16                NormalizedLoPhyLane;
  BOOLEAN               Result;

  Result  = FALSE;
  Wrapper = PcieConfigGetParentWrapper (Engine);
  DescriptorLoLane = MIN (PortDescriptor->EngineData.StartLane, PortDescriptor->EngineData.EndLane);
  DescriptorHiLane = MAX (PortDescriptor->EngineData.StartLane, PortDescriptor->EngineData.EndLane);
  DescriptorNumberOfLanes = DescriptorHiLane - DescriptorLoLane + 1;

  NormalizedLoPhyLane = DescriptorLoLane - Wrapper->StartPhyLane;

  if (NormalizedLoPhyLane == Engine->Type.Port.StartCoreLane) {
    Result = TRUE;
  } else {
    if (NormalizedLoPhyLane == 0) {
      Result = TRUE;
    } else {
      if ((NormalizedLoPhyLane % DescriptorNumberOfLanes) == 0) {
        Result = TRUE;
      }
    }
  }
  return Result;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 *
 * @param[in]  Engine              Pointer to engine configuration
 * @retval     AGESA_ERROR         Fail to map PCI device address
 * @retval     AGESA_SUCCESS       Successfully allocate PCI address
 */

AGESA_STATUS
PcieMapPortPciAddressCZ (
  IN      PCIe_ENGINE_CONFIG     *Engine
  )
{
  AGESA_STATUS            Status;
  CZ_COMPLEX_CONFIG       *ComplexConfig;
  PCIe_COMPLEX_CONFIG     *Complex;
  PCIe_PLATFORM_CONFIG    *Pcie;
  UINT8                   DevFunc;
  UINT8                   Index;
  Status = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMapPortPciAddressCZ Enter\n");
  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  if (Engine->Type.Port.PortData.DeviceNumber == 0 && Engine->Type.Port.PortData.FunctionNumber == 0) {
    Engine->Type.Port.PortData.DeviceNumber = Engine->Type.Port.NativeDevNumber;
    Engine->Type.Port.PortData.FunctionNumber = Engine->Type.Port.NativeFunNumber;
  }
  ComplexConfig = (CZ_COMPLEX_CONFIG *) PcieConfigGetParentSilicon (Engine);
  IDS_OPTION_HOOK (IDS_GNB_PCIE_PORT_REMAP, &Engine->Type.Port, GnbLibGetHeader (Pcie));
  DevFunc = (Engine->Type.Port.PortData.DeviceNumber << 3) | Engine->Type.Port.PortData.FunctionNumber;
  IDS_HDT_CONSOLE (GNB_TRACE, "    Device %x, Function %x\n", Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber);
  for (Index = 0; Index < sizeof (ComplexConfig->FmSilicon.PortDevMap); ++Index) {
    if (ComplexConfig->FmSilicon.PortDevMap[Index] == DevFunc) {
      Status = AGESA_ERROR;
      break;
    }
  }
  if (Status == AGESA_SUCCESS) {
    ComplexConfig->FmSilicon.PortDevMap[Engine->Type.Port.PcieBridgeId] = DevFunc;
    IDS_HDT_CONSOLE (GNB_TRACE, "    PortDevMap DevFunc 0x%x, for PcieBridgeId %d\n", DevFunc, Engine->Type.Port.PcieBridgeId);
  }
  for (Index = 0; Index < (sizeof (DefaultPortDevMapCZ) / sizeof (DefaultPortDevMapCZ[0])); ++Index) {
    if (DevFunc == DefaultPortDevMapCZ[Index]) {
      Engine->Type.Port.LogicalBridgeId = Index;
      IDS_HDT_CONSOLE (GNB_TRACE, "    LogicalBridgeId = %x\n", Index);
      // Get the configuration from the table or from "auto settings"
      if (Engine->Type.Port.PortData.ApicDeviceInfo.GroupMap == 0x00) {
        // If Group is 0, use "Auto" settings
        Engine->Type.Port.PortData.ApicDeviceInfo = DefaultIoapicConfigCZ[Index];
      }
      break;
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMapPortPciAddressCZ Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 * @param[in]  Silicon             Silicon config descriptor
 */

VOID
PcieSetPortPciAddressMapCZ (
  IN      PCIe_SILICON_CONFIG     *Silicon
  )
{
  UINT8                   Index;
  UINT8                   DevFuncIndex;
  UINT8                   PortDevMap [sizeof (DefaultPortDevMapCZ)];
  PCIe_PLATFORM_CONFIG    *Pcie;
  D0F0x64_x30_STRUCT      D0F0x64_x30;

  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Silicon->Header);
  LibAmdMemCopy (&PortDevMap[0], &DefaultPortDevMapCZ[0], sizeof (DefaultPortDevMapCZ), GnbLibGetHeader (Pcie));
  for (Index = 0; Index < sizeof (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap); ++Index) {
    if (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap[Index] != 0) {
      for (DevFuncIndex = 0; DevFuncIndex < sizeof (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap); ++DevFuncIndex) {
        if (PortDevMap[DevFuncIndex] == ((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap[Index]) {
          PortDevMap[DevFuncIndex] = 0;
          break;
        }
      }
    }
  }
  for (Index = 0; Index < sizeof (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap); ++Index) {
    if (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap[Index] == 0) {
      for (DevFuncIndex = 0; DevFuncIndex < sizeof (((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap); ++DevFuncIndex) {
        if (PortDevMap[DevFuncIndex] != 0) {
          ((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap[Index] = PortDevMap[DevFuncIndex];
          PortDevMap[DevFuncIndex] = 0;
          break;
        }
      }
    }
    GnbRegisterReadCZ ((GNB_HANDLE *) Silicon, D0F0x64_x30_TYPE, D0F0x64_x30_ADDRESS + Index, &D0F0x64_x30.Value, 0, GnbLibGetHeader (Pcie));
    D0F0x64_x30.Field.PBr0_DevFnMap = ((CZ_COMPLEX_CONFIG *) Silicon)->FmSilicon.PortDevMap[Index];
    GnbRegisterWriteCZ ((GNB_HANDLE *) Silicon, D0F0x64_x30_TYPE, D0F0x64_x30_ADDRESS + Index, &D0F0x64_x30.Value, 0, GnbLibGetHeader (Pcie));
  }
}



PCIe_PORT_DESCRIPTOR DefaultSbPortCZ = {
  0,
  PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 0, 3),
  PCIE_PORT_DATA_INITIALIZER_V2 (PortEnabled, ChannelTypeExt6db, 2, 1, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmL0sL1, 0, 0)
};

/*----------------------------------------------------------------------------------------*/
/**
 * Build default SB configuration descriptor
 *
 *
 * @param[in]  SocketId         Socket Id
 * @param[out] SbPort           Pointer to SB configuration descriptor
 * @param[in]  StdHeader        Standard configuration header.
 * @retval     AGESA_SUCCESS    Configuration data build successfully
 */
AGESA_STATUS
PcieGetSbConfigInfoCZ (
  IN       UINT8                         SocketId,
     OUT   PCIe_PORT_DESCRIPTOR          *SbPort,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  )
{
  CPUID_DATA CpuId;

  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  // If FP4, return unsupported
  if ((((CpuId.EBX_Reg >> 28) & 0xF) == BR_PKG_FP4) || (((CpuId.EBX_Reg >> 28) & 0xF) == BR_PKG_AM4)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "CZ FP4/AM4 Internal FCH\n");
    return AGESA_UNSUPPORTED;
  }
  // FM2 cantain 1x4 UMI
  LibAmdMemCopy (SbPort, &DefaultSbPortCZ, sizeof (DefaultSbPortCZ), StdHeader);

  return AGESA_SUCCESS;
}



