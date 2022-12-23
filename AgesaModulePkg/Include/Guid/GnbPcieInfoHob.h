/* $NoKeywords:$ */
/**
 * @file
 *
 * Gnb Pcie Data Hob GUID definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Gnb
 * @e \$Revision: 309090 $   @e \$Date: 2015-09-09 04:30:05 +0800 (Wed, 9 Sep 2015) $
 */
/*****************************************************************************
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
 **/
#ifndef _GNB_PCIE_HOB_INFO_H_
#define _GNB_PCIE_HOB_INFO_H_

#define _GNB_PCIE_HOB_INFO_GUID \
{ \
  0x3eb1d90, 0xce14, 0x40d8, 0xa6, 0xba, 0x10, 0x3a, 0x8d, 0x7b, 0xd3, 0x2d \
}
extern EFI_GUID gGnbPcieHobInfoGuid;

#include <GnbDxio.h>

#pragma pack (push, 1)
#define MAX_NUMBER_OF_COMPLEXES_SUPPORTED         8
#define MAX_NUMBER_OF_CORES_PER_COMPLEX           2
#define MAX_NUMBER_OF_PORTS_PER_COMPLEX           16

/// Complex Configuration for silicon module
typedef struct {
  PCIe_SILICON_CONFIG     Silicon;                                        ///< Silicon
  PCIe_WRAPPER_CONFIG     Wrapper[MAX_NUMBER_OF_CORES_PER_COMPLEX];       ///< PCIe Core Descriptors
  PCIe_ENGINE_CONFIG      Ports[MAX_NUMBER_OF_PORTS_PER_COMPLEX];         ///< PCIe Port Descriptors
  UINT8                   PortDevMap[MAX_NUMBER_OF_PORTS_PER_COMPLEX];    ///< PortDevMap Allocation
} COMPLEX_CONFIG_MODEL;

/// PCIe information HOB data
typedef struct _GNB_PCIE_INFORMATION_DATA_HOB {
  EFI_HOB_GUID_TYPE           EfiHobGuidType;                             ///< GUID Hob type structure
  PCIe_PLATFORM_CONFIG        PciePlatformConfigHob;                      ///< Platform Config Structure
  COMPLEX_CONFIG_MODEL        ComplexConfigs[MAX_NUMBER_OF_COMPLEXES];    ///< Allocation for Max Complex Structure suported
} GNB_PCIE_INFORMATION_DATA_HOB;

#pragma pack (pop)

#endif

