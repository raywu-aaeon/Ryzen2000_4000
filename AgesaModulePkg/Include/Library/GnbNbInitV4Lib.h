/* $NoKeywords:$ */
/**
 * @file
 *
 * NB services
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
#ifndef _GNBNBINITV4LIB_H_
#define _GNBNBINITV4LIB_H_

#pragma pack (push, 1)

/// Firmware header
typedef struct {
  UINT32  Version;                  ///< Version
  UINT32  HeaderLength;             ///< Header length
  UINT32  FirmwareLength;           ///< Firmware length
  UINT32  EntryPoint;               ///< Entry point
  UINT32  MessageDigest[5];         ///< Message digest
  UINT32  Reserved_A[3];            ///< Reserved
  UINT32  CurrentSystemState;       ///< Current system state
  UINT32  DpmCacHistory;            ///< DpmCac History
  UINT32  DpmResidencyCounters;     ///< DPM recidency counters
  UINT32  Reserved_B[16];           ///< Reserved
  UINT32  Reserved_C[16];           ///< Reserved
  UINT32  Reserved_D[16];           ///< Reserved
  UINT32  HeaderEnd;                ///< Header end signature
} FIRMWARE_HEADER_V4;

/// SMU service request contect
typedef struct {
  PCI_ADDR          GnbPciAddress;   ///< PCIe address of GNB
  UINT32            RequestId;       ///< Request/Msg ID
} SMU_MSG_CONTEXT;

#pragma pack (pop)

BOOLEAN
GnbCheckPhantomFuncSupport (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

AGESA_STATUS
GnbGetTopologyInfoV4 (
  IN       PCI_ADDR                  StartPciAddress,
  IN       PCI_ADDR                  EndPciAddress,
     OUT   GNB_TOPOLOGY_INFO         *TopologyInfo,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

VOID
GnbSmuServiceRequestV4 (
  IN       PCI_ADDR                 GnbPciAddress,
  IN       UINT32                   RequestId,
  IN       UINT32                   AccessFlags,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

VOID
GnbSmuServiceRequestV4S3Script (
  IN      AMD_CONFIG_PARAMS     *StdHeader,
  IN      UINT16                ContextLength,
  IN      VOID                  *Context
  );

AGESA_STATUS
GnbSmuFirmwareLoadV4 (
  IN       PCI_ADDR                 GnbPciAddress,
  IN       FIRMWARE_HEADER_V4       *Firmware,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

PCI_ADDR
GnbGetIommuPciAddressV4 (
  IN       GNB_HANDLE               *GnbHandle,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

AGESA_STATUS
GnbEnableIommuMmioV4 (
  IN       GNB_HANDLE           *GnbHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  );

#endif

