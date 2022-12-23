/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 */
#ifndef _AMD_NBIO_PCIE_SERVICES_PPI_H_
#define _AMD_NBIO_PCIE_SERVICES_PPI_H_

#include <GnbDxio.h>
#include <Guid/GnbPcieInfoHob.h>

// Current PPI revision
#define AMD_NBIO_PCIE_SERVICES_REVISION   0x00

typedef struct _PEI_AMD_NBIO_PCIE_SERVICES_PPI PEI_AMD_NBIO_PCIE_SERVICES_PPI;

//
// PPI prototype
//
/**
  Returns the NBIO debug options configuration structure

  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  DebugOptions
    A pointer to a pointer to store the address of the PCIe topology structure

**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_GET_TOPOLOGY_STRUCT) (
  IN  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *This,
  OUT GNB_PCIE_INFORMATION_DATA_HOB   **DebugOptions
);

//
// PPI prototype
//
/**
  Sets the operating speed for a single PCIe port

  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  PciAddress
    PCI Address of the target port
  TargetSpeed
    Desired speed of the target port (Gen1, Gen2, Gen3)

**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_SET_TARGET_SPEED_STRUCT) (
  IN  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *This,
  IN  CONST EFI_PEI_SERVICES          **PeiServices,
  IN  UINT8                           PciDevice,
  IN  UINT8                           PciFunction,
  IN  UINT8                           TargetSpeed
);

///
/// The Ppi of Pcie sevices
///
typedef struct _PEI_AMD_NBIO_PCIE_SERVICES_PPI {
  UINT32 Revision;                                       ///< revision
  AMD_NBIO_PCIE_GET_TOPOLOGY_STRUCT     PcieGetTopology; ///<
  AMD_NBIO_PCIE_SET_TARGET_SPEED_STRUCT PcieSetSpeed;    ///<
} PEI_AMD_NBIO_PCIE_SERVICES_PPI;

extern EFI_GUID gAmdNbioPcieServicesPpiGuid ;

#endif //

