/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe utility. Various supporting functions.
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

#ifndef _PCIEUTILLIB_H_
#define _PCIEUTILLIB_H_

/// Core lanes
typedef enum {
  AllCoreLanes,           ///< All core lanes
  AllocatedCoreLanes,     ///< Allocated core lanes
  ActiveCoreLanes,        ///< Active core lanes
  HotplugCoreLanes,       ///< Hot plug core lanes
  SbCoreLanes,            ///< South bridge core lanes
} CORE_LANES;

/// DDI lanes
typedef enum {
  DdiAllLanes,            ///< All DDI Lanes
  DdiActiveLanes          ///< Active DDI Lanes
} DDI_LANES;

BOOLEAN
PcieUtilSearchArray (
  IN      UINT8                         *Buf1,
  IN      UINTN                         Buf1Length,
  IN      UINT8                         *Buf2,
  IN      UINTN                         Buf2Length
  );

VOID
PcieUtilGetLinkHwStateHistory (
  IN       PCIe_ENGINE_CONFIG            *Engine,
     OUT   UINT8                         *History,
  IN       UINT8                         Length,
  IN       PCIe_PLATFORM_CONFIG          *Pcie
  );


BOOLEAN
PcieUtilIsLinkReversed (
  IN      BOOLEAN                        HwLinkState,
  IN      PCIe_ENGINE_CONFIG             *Engine,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  );


UINT8
PcieUtilGetLinkWidth (
  IN      PCIe_ENGINE_CONFIG            *Engine,
  IN      PCIe_PLATFORM_CONFIG          *Pcie
  );


UINT32
PcieUtilGetEngineLaneBitMap (
  IN      UINT32                         IncludeLaneType,
  IN      UINT32                         ExcludeLaneType,
  IN      PCIe_ENGINE_CONFIG             *Engine
  );

UINT32
PcieUtilGetWrapperLaneBitMap (
  IN      UINT32                         IncludeLaneType,
  IN      UINT32                         ExcludeLaneType,
  IN      PCIe_WRAPPER_CONFIG            *Wrapper
  );

VOID
PciePortProgramRegisterTable (
  IN      PCIE_PORT_REGISTER_ENTRY       *Table,
  IN      UINTN                          Length,
  IN      PCIe_ENGINE_CONFIG             *Engine,
  IN      BOOLEAN                        S3Save,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  );

VOID
PcieLockRegisters (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN       PCIe_PLATFORM_CONFIG          *Pcie
  );

PCIE_LINK_SPEED_CAP
PcieUtilGlobalGenCapability (
  IN      UINT32                         Flags,
  IN      PCIe_PLATFORM_CONFIG           *Pcie
  );

#endif

