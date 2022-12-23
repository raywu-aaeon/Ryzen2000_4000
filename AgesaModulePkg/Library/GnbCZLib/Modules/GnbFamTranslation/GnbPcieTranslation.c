/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific function translation
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
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBFAMTRANSLATION_GNBPCIETRANSLATION_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
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
 * @retval     AGESA_UNSUPPORTED   No more configuration available for given engine type
 * @retval     AGESA_ERROR         Requested configuration not supported
 */
AGESA_STATUS
PcieFmConfigureEnginesLaneAllocation (
  IN      PCIe_WRAPPER_CONFIG           *Wrapper,
  IN      PCIE_ENGINE_TYPE              EngineType,
  IN      UINT8                         ConfigurationId
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Wrapper->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Wrapper->Header);
  Status = GnbLibLocateService (GnbPcieFamConfigService, Complex->SocketId, &PcieConfigService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmConfigureEnginesLaneAllocation (Wrapper, EngineType, ConfigurationId);
  }
  return  AGESA_ERROR;
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
PcieFmGetCoreConfigurationValue (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 CoreId,
  IN      UINT64                ConfigurationSignature,
  IN      UINT8                 *ConfigurationValue
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_INIT_SERVICES    *PcieInitService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Wrapper->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Wrapper->Header);
  Status = GnbLibLocateService (GnbPcieFamInitService, Complex->SocketId, &PcieInitService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieInitService->PcieFmGetCoreConfigurationValue (Wrapper, CoreId, ConfigurationSignature,  ConfigurationValue);
  }
  return  AGESA_ERROR;
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
PcieFmCheckPortPciDeviceMapping (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamConfigService, Complex->SocketId, &PcieConfigService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmCheckPortPciDeviceMapping (PortDescriptor, Engine);
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
PcieFmDebugGetCoreConfigurationString (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      UINT8                 ConfigurationValue
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_DEBUG_SERVICES   *PcieDebugService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Wrapper->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamDebugService, Complex->SocketId, &PcieDebugService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieDebugService->PcieFmDebugGetCoreConfigurationString (Wrapper, ConfigurationValue);
  }
  return " !!! Unsupported Core Configuration !!!";
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
PcieFmDebugGetWrapperNameString (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_DEBUG_SERVICES   *PcieDebugService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Wrapper->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamDebugService, Complex->SocketId, &PcieDebugService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieDebugService->PcieFmDebugGetWrapperNameString (Wrapper);
  }
  return " !!! Unsupported Wrapper Type !!!";
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
PcieFmDebugGetHostRegAddressSpaceString (
  IN      PCIe_SILICON_CONFIG    *Silicon,
  IN      UINT16                 AddressFrame
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_DEBUG_SERVICES   *PcieDebugService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Silicon->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamDebugService, Complex->SocketId, &PcieDebugService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieDebugService->PcieFmDebugGetHostRegAddressSpaceString (Silicon, AddressFrame);
  }
  return " !!! Unsupported Host Register Address Space !!!";
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
PcieFmCheckPortPcieLaneCanBeMuxed (
  IN      PCIe_PORT_DESCRIPTOR  *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG    *Engine
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamConfigService, Complex->SocketId, &PcieConfigService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmCheckPortPcieLaneCanBeMuxed (PortDescriptor, Engine);
  }
  return FALSE;
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
PcieFmMapPortPciAddress (
  IN      PCIe_ENGINE_CONFIG     *Engine
  )
{
  AGESA_STATUS              Status;
  PCIe_COMPLEX_CONFIG       *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamConfigService, Complex->SocketId, &PcieConfigService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmMapPortPciAddress (Engine);
  }
  return  AGESA_ERROR;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get total number of silicons/wrappers/engines for this complex
 *
 *
 *
 * @param[in]  SocketId              Socket ID.
 * @param[out] Length                Length of configuration info block
 * @param[out] StdHeader             Standard Configuration Header
 * @retval     AGESA_SUCCESS         Configuration data length is correct
 */
AGESA_STATUS
PcieFmGetComplexDataLength (
  IN       UINT8                         SocketId,
     OUT   UINTN                         *Length,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  )
{
  AGESA_STATUS              Status;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;
  Status = GnbLibLocateService (GnbPcieFamConfigService, SocketId, &PcieConfigService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmGetComplexDataLength (SocketId, Length, StdHeader);
  }
  return Status;
}




/*----------------------------------------------------------------------------------------*/
/**
 * Build configuration
 *
 *
 * @param[in]  SocketId         Socket ID.
 * @param[out] Buffer           Pointer to buffer to build internal complex data structure
 * @param[out] StdHeader        Standard configuration header.
 * @retval     AGESA_SUCCESS    Configuration data build successfully
 */
AGESA_STATUS
PcieFmBuildComplexConfiguration (
  IN       UINT8                         SocketId,
     OUT   VOID                          *Buffer,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  )
{
  AGESA_STATUS              Status;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;
  Status = GnbLibLocateService (GnbPcieFamConfigService, SocketId, &PcieConfigService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmBuildComplexConfiguration (SocketId, Buffer, StdHeader);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get max link speed capability supported by this port
 *
 *
 *
 * @param[in]  Flags              See Flags PCIE_PORT_GEN_CAP_BOOT / PCIE_PORT_GEN_CAP_MAX
 * @param[in]  Engine             Pointer to engine config descriptor
 * @retval     PcieGen1/PcieGen2  Max supported link gen capability
 */
PCIE_LINK_SPEED_CAP
PcieFmGetLinkSpeedCap (
  IN       UINT32                Flags,
  IN       PCIe_ENGINE_CONFIG    *Engine
  )
{
  AGESA_STATUS            Status;
  PCIe_COMPLEX_CONFIG     *Complex;
  PCIe_PLATFORM_CONFIG      *Pcie;
  PCIe_FAM_INIT_SERVICES  *PcieInitService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamInitService, Complex->SocketId, &PcieInitService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieInitService->PcieFmGetLinkSpeedCap (Flags, Engine);
  }
  return PcieGen1;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  Get native PHY lane bitmap
 *
 *
 * @param[in]  PhyLaneBitmap  Package PHY lane bitmap
 * @param[in]  Engine         Standard configuration header.
 * @retval     Native PHY lane bitmap
 */
UINT32
PcieFmGetNativePhyLaneBitmap (
  IN       UINT32                        PhyLaneBitmap,
  IN       PCIe_ENGINE_CONFIG            *Engine
  )
{
  AGESA_STATUS            Status;
  PCIe_COMPLEX_CONFIG     *Complex;
  PCIe_PLATFORM_CONFIG    *Pcie;
  PCIe_FAM_INIT_SERVICES  *PcieInitService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &Complex->Header);
  Status = GnbLibLocateService (GnbPcieFamInitService, Complex->SocketId, &PcieInitService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieInitService->PcieFmGetNativePhyLaneBitmap (PhyLaneBitmap, Engine);
  }
  return 0x0;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set current link speed
 *
 *
 * @param[in]  LinkSpeedCapability  Link Speed Capability
 * @param[in]  Engine               Pointer to engine configuration descriptor
 * @param[in]  Pcie                 Pointer to global PCIe configuration
 *
 */
VOID
PcieFmSetLinkSpeedCap (
  IN      PCIE_LINK_SPEED_CAP            LinkSpeedCapability,
  IN      PCIe_ENGINE_CONFIG             *Engine,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  )
{
  AGESA_STATUS            Status;
  PCIe_COMPLEX_CONFIG     *Complex;
  PCIe_FAM_INIT_SERVICES  *PcieInitService;

  Complex = (PCIe_COMPLEX_CONFIG *) PcieConfigGetParent (DESCRIPTOR_COMPLEX, &Engine->Header);
  Status = GnbLibLocateService (GnbPcieFamInitService, Complex->SocketId, &PcieInitService, GnbLibGetHeader (Pcie));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    PcieInitService->PcieFmSetLinkSpeedCap (LinkSpeedCapability, Engine, Pcie);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get SB port info
 *
 *
 * @param[out] SocketId         Socket ID
 * @param[out] SbPort           Pointer to SB configuration descriptor
 * @param[in]  StdHeader        Standard configuration header.
 * @retval     AGESA_SUCCESS    SB configuration determined successfully
 */
AGESA_STATUS
PcieFmGetSbConfigInfo (
  IN       UINT8                        SocketId,
     OUT   PCIe_PORT_DESCRIPTOR         *SbPort,
  IN       AMD_CONFIG_PARAMS            *StdHeader
  )
{
  AGESA_STATUS              Status;
  PCIe_FAM_CONFIG_SERVICES  *PcieConfigService;
  Status = GnbLibLocateService (GnbPcieFamConfigService, SocketId, &PcieConfigService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return PcieConfigService->PcieFmGetSbConfigInfo (SocketId, SbPort, StdHeader);
  }
  return Status;
}


