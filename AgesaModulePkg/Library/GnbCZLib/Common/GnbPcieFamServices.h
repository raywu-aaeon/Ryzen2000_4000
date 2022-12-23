/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe family specific services.
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
#ifndef _GNBPCIEFAMSERVICES_H_
#define _GNBPCIEFAMSERVICES_H_

#include  "Gnb.h"
#include  "GnbPcie.h"

AGESA_STATUS
PcieFmGetComplexDataLength (
  IN       UINT8                         SocketId,
     OUT   UINTN                         *Length,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

typedef AGESA_STATUS F_PCIEFMGETCOMPLEXDATALENGTH (
  IN       UINT8                         SocketId,
     OUT   UINTN                         *Length,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

AGESA_STATUS
PcieFmBuildComplexConfiguration (
  IN       UINT8                         SocketId,
     OUT   VOID                          *Buffer,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

typedef AGESA_STATUS F_PCIEFMBUILDCOMPLEXCONFIGURATION (
  IN       UINT8                         SocketId,
     OUT   VOID                          *Buffer,
  IN       AMD_CONFIG_PARAMS             *StdHeader
  );

AGESA_STATUS
PcieFmConfigureEnginesLaneAllocation (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       PCIE_ENGINE_TYPE              EngineType,
  IN       UINT8                         ConfigurationId
  );

typedef AGESA_STATUS F_PCIEFMCONFIGUREENGINESLANEALLOCATION (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       PCIE_ENGINE_TYPE              EngineType,
  IN       UINT8                         ConfigurationId
  );

AGESA_STATUS
PcieFmGetCoreConfigurationValue (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       UINT8                         CoreId,
  IN       UINT64                        ConfigurationSignature,
  IN       UINT8                         *ConfigurationValue
  );

typedef AGESA_STATUS F_PCIEFMGETCORECONFIGURATIONVALUE (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       UINT8                         CoreId,
  IN       UINT64                        ConfigurationSignature,
  IN       UINT8                         *ConfigurationValue
  );

BOOLEAN
PcieFmCheckPortPciDeviceMapping (
  IN      PCIe_PORT_DESCRIPTOR           *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

typedef BOOLEAN F_PCIEFMCHECKPORTPCIDEVICEMAPPING (
  IN      PCIe_PORT_DESCRIPTOR           *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

AGESA_STATUS
PcieFmMapPortPciAddress (
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

typedef AGESA_STATUS F_PCIEFMMAPPORTPCIADDRESS (
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

BOOLEAN
PcieFmCheckPortPcieLaneCanBeMuxed (
  IN      PCIe_PORT_DESCRIPTOR           *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

typedef BOOLEAN F_PCIEFMCHECKPORTPCIELANECANBEMUXED (
  IN      PCIe_PORT_DESCRIPTOR           *PortDescriptor,
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

CONST CHAR8*
PcieFmDebugGetCoreConfigurationString (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       UINT8                         ConfigurationValue
 );

typedef CONST CHAR8* F_PCIEFMDEBUGGETCORECONFIGURATIONSTRING (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       UINT8                         ConfigurationValue
 );

CONST CHAR8*
PcieFmDebugGetWrapperNameString (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper
 );

typedef CONST CHAR8* F_PCIEFMDEBUGGETWRAPPERNAMESTRING (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper
 );

CONST CHAR8*
PcieFmDebugGetHostRegAddressSpaceString (
  IN      PCIe_SILICON_CONFIG            *Silicon,
  IN      UINT16                         AddressFrame
  );

typedef CONST CHAR8* F_PCIEFMDEBUGGETHOSTREGADDRESSSPACESTRING (
  IN      PCIe_SILICON_CONFIG            *Silicon,
  IN      UINT16                         AddressFrame
  );

PCIE_LINK_SPEED_CAP
PcieFmGetLinkSpeedCap (
  IN       UINT32                        Flags,
  IN       PCIe_ENGINE_CONFIG            *Engine
  );

typedef PCIE_LINK_SPEED_CAP F_PCIEFMGETLINKSPEEDCAP (
  IN       UINT32                        Flags,
  IN       PCIe_ENGINE_CONFIG            *Engine
  );

VOID
PcieFmSetLinkSpeedCap (
  IN      PCIE_LINK_SPEED_CAP            LinkSpeedCapability,
  IN      PCIe_ENGINE_CONFIG             *Engine,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  );

typedef VOID F_PCIEFMSETLINKSPEEDCAP (
  IN      PCIE_LINK_SPEED_CAP            LinkSpeedCapability,
  IN      PCIe_ENGINE_CONFIG             *Engine,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  );

UINT32
PcieFmGetNativePhyLaneBitmap (
  IN       UINT32                        PhyLaneBitmap,
  IN       PCIe_ENGINE_CONFIG            *Engine
  );

typedef UINT32 F_PCIEFMGETNATIVEPHYLANEBITMAP (
  IN       UINT32                        PhyLaneBitmap,
  IN       PCIe_ENGINE_CONFIG            *Engine
  );

AGESA_STATUS
PcieFmGetSbConfigInfo (
  IN       UINT8                        SocketId,
     OUT   PCIe_PORT_DESCRIPTOR         *SbPort,
  IN       AMD_CONFIG_PARAMS            *StdHeader
  );

typedef AGESA_STATUS F_PCIEFMGETSBCONFIGINFO (
  IN       UINT8                        SocketId,
     OUT   PCIe_PORT_DESCRIPTOR         *SbPort,
  IN       AMD_CONFIG_PARAMS            *StdHeader
  );


/// PCIe config services
typedef struct {
  F_PCIEFMGETCOMPLEXDATALENGTH              *PcieFmGetComplexDataLength;              ///< PcieFmGetComplexDataLength
  F_PCIEFMBUILDCOMPLEXCONFIGURATION         *PcieFmBuildComplexConfiguration;         ///< PcieFmBuildComplexConfiguration
  F_PCIEFMCONFIGUREENGINESLANEALLOCATION    *PcieFmConfigureEnginesLaneAllocation;    ///< PcieFmConfigureEnginesLaneAllocation
  F_PCIEFMCHECKPORTPCIDEVICEMAPPING         *PcieFmCheckPortPciDeviceMapping;         ///< PcieFmCheckPortPciDeviceMapping
  F_PCIEFMMAPPORTPCIADDRESS                 *PcieFmMapPortPciAddress;                 ///< PcieFmMapPortPciAddress
  F_PCIEFMCHECKPORTPCIELANECANBEMUXED       *PcieFmCheckPortPcieLaneCanBeMuxed;       ///< PcieFmCheckPortPcieLaneCanBeMuxed
  F_PCIEFMGETSBCONFIGINFO                   *PcieFmGetSbConfigInfo;                   ///< PcieFmGetSbConfigInfo
} PCIe_FAM_CONFIG_SERVICES;

/// PCIe init services
typedef struct {
  F_PCIEFMGETCORECONFIGURATIONVALUE         *PcieFmGetCoreConfigurationValue;         ///< PcieFmGetCoreConfigurationValue
  F_PCIEFMGETLINKSPEEDCAP                   *PcieFmGetLinkSpeedCap;                   ///< PcieFmGetLinkSpeedCap
  F_PCIEFMGETNATIVEPHYLANEBITMAP            *PcieFmGetNativePhyLaneBitmap;            ///< PcieFmGetNativePhyLaneBitmap
  F_PCIEFMSETLINKSPEEDCAP                   *PcieFmSetLinkSpeedCap;                   ///< PcieFmSetLinkSpeedCap
} PCIe_FAM_INIT_SERVICES;

///PCIe debug services
typedef struct {
  F_PCIEFMDEBUGGETHOSTREGADDRESSSPACESTRING *PcieFmDebugGetHostRegAddressSpaceString; ///< PcieFmGetCoreConfigurationValue
  F_PCIEFMDEBUGGETWRAPPERNAMESTRING         *PcieFmDebugGetWrapperNameString;         ///< PcieFmDebugGetWrapperNameString
  F_PCIEFMDEBUGGETCORECONFIGURATIONSTRING   *PcieFmDebugGetCoreConfigurationString;   ///< PcieFmDebugGetCoreConfigurationString
} PCIe_FAM_DEBUG_SERVICES;

#endif

