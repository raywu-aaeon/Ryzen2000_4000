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
#ifndef _GFXENUMCONNECTORS_H_
#define _GFXENUMCONNECTORS_H_

/// External connector info
typedef struct {
  PCIE_CONNECTOR_TYPE ConnectorType;          ///<
  UINT8               DisplayDeviceEnum;      ///<
  UINT16              ConnectorEnum;          ///<
  UINT16              EncoderEnum;            ///<
  UINT8               ConnectorIndex;         ///<
} EXT_CONNECTOR_INFO;

/// External display device info
typedef struct {
  UINT8               DisplayDeviceEnum;      ///<
  UINT8               DeviceIndex;            ///<
  UINT16              DeviceTag;              ///<
  UINT16              DeviceAcpiEnum;         ///<
} EXT_DISPLAY_DEVICE_INFO;

/// Connector enumeration info
typedef struct {
  AGESA_STATUS        Status;                 ///<
  UINT8               DisplayDeviceEnum;      ///<
  UINT8               RequestedPriorityIndex; ///<
  UINT8               CurrentPriorityIndex;   ///<
  PCIe_ENGINE_CONFIG  *Engine;                ///<
} CONNECTOR_ENUM_INFO;

VOID
GfxIntegratedCopyDisplayInfo (
  IN       PCIe_ENGINE_CONFIG             *Engine,
     OUT   EXT_DISPLAY_PATH               *DisplayPath,
     OUT   EXT_DISPLAY_PATH               *SecondaryDisplayPath,
  IN       GFX_PLATFORM_CONFIG            *Gfx
  );

AGESA_STATUS
GfxIntegratedEnumerateAllConnectors (
     OUT   EXT_DISPLAY_PATH                 *DisplayPathList,
  IN OUT   PCIe_PLATFORM_CONFIG             *Pcie,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  );

EXT_CONNECTOR_INFO*
GfxIntegratedExtConnectorInfo (
  IN       UINT8                         ConnectorType
  );

EXT_DISPLAY_DEVICE_INFO*
GfxIntegratedExtDisplayDeviceInfo (
  IN       UINT8                         DisplayDeviceEnum,
  IN       UINT8                         DisplayDeviceIndex
  );


#endif

