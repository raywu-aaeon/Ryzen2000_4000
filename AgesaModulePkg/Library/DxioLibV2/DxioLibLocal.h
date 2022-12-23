/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO Ancillary Data handlers
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

#ifndef _DXIOANCDATAV2_H_
#define _DXIOANCDATAV2_H_

// Configuration Points from APU specific driver
VOID
DxioCfgBeforeReconfig (
  IN       GNB_HANDLE       *GnbHandle
  );

VOID
DxioCfgAfterReconfig (
  IN       GNB_HANDLE       *GnbHandle
  );

// DXIO Debug Output Functions
VOID
DxioDebugDump (
  IN       DXIO_PLATFORM_DESCRIPTOR  *PlatformDescriptor,
  IN       UINT32                    PlatformDescSize,
  IN       UINT8                     *AncillaryData,
  IN       UINT32                    AncillaryDataSize
  );

// DXIO Library Functions
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
  );

AGESA_STATUS
DxioProcessResults (
  IN       GNB_HANDLE                      *GnbHandle,
  IN       DXIO_COMPLEX_DESCRIPTOR         *UserConfig,
  IN       DXIO_PLATFORM_DESCRIPTOR        *ThisNode,
  IN       UINT32                          ThisNodeSize,
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi
  );

VOID
DxioPortMapping (
  IN      GNB_HANDLE                *GnbHandle,
  IN      DXIO_COMPLEX_DESCRIPTOR   *UserConfig,
  IN      DXIO_PLATFORM_DESCRIPTOR  *ThisNode,
  IN OUT  DXIO_ENGINE_DESCRIPTOR    **EarlyTrain,
  IN OUT  UINT32                    *EarlyTrainAddress,
  IN OUT  PCIe_ENGINE_CONFIG        **EarlyTrainEngine
  );

VOID
DxioUpdatePortTrainingStatus (
  IN       GNB_HANDLE                *GnbHandle,
  IN       DXIO_COMPLEX_DESCRIPTOR   *UserConfig,
  OUT      DXIO_PLATFORM_DESCRIPTOR  *ThisNode
  );

AGESA_STATUS
PcieMapPortPciAddress (
  IN      PCIe_ENGINE_CONFIG     *Engine,
  IN      UINT8*                 PortDevMap
  );

VOID
PcieSetPortPciAddressMap (
  IN      GNB_HANDLE    *GnbHandle,
  IN      UINT8         *PortDevMap
  );

VOID
NbioEnableNbifDevice (
  IN        GNB_HANDLE         *GnbHandle,
  IN        UINT8              DeviceType,
  IN        UINT8              StartLane
  );

VOID
NbioDisableNbifDevice (
  IN        GNB_HANDLE         *GnbHandle,
  IN        UINT8              DeviceType,
  IN        UINT8              StartLane
  );

UINT32
DxioAncDataCalcSize (
  IN       DXIO_PORT_DESCRIPTOR    *PortPointer
  );

UINT32
DxioAncDataPopulate (
  IN       DXIO_ENGINE_DESCRIPTOR  *EnginePointer,
  IN       DXIO_PORT_DESCRIPTOR    *PortPointer,
  IN       UINT8                   *AncData
  );

UINT8
DxioLibServiceRequest (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI   *SmuServicesPpi,
  IN       UINT32                          InstanceId,
  IN       UINT32                          ServiceRequest,
  IN       UINT32                          DxioArg1,
  IN       UINT32                          DxioArg2,
  IN       UINT32                          DxioArg3,
  IN       UINT32                          DxioArg4,
  IN       UINT32                          DxioArg5
  );

AGESA_STATUS
DxioGetUserCfgForSocket (
  IN      UINT8                     SocketNumber,
  IN      DXIO_COMPLEX_DESCRIPTOR   *UserComplex,
  IN OUT  DXIO_PORT_DESCRIPTOR      **PortList
  );

VOID
DxioWorkaroundSetSimNowStatus (
  IN      BOOLEAN   IsSimNow
  );

VOID
DxioWorkaroundForNoDxioInitialize (
  );

VOID
DxioWorkaroundForNoDxioGetStatus (
  IN OUT  UINT32            *SmuArg
  );

#endif

