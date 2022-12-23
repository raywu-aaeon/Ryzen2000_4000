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
#ifndef _AMD_NBIO_PCIE_DPCSTATUS_PPI_H_
#define _AMD_NBIO_PCIE_DPCSTATUS_PPI_H_

#define MAX_NUMBER_DPCSTATUS      128
/// PCIE_DPC_STATUS
typedef struct {
  UINT8                           SocketId;                       ///< Socket ID
  UINT8                           DieID;                          ///< Die ID
  UINT8                           RBIndex;                        ///< Node to which GNB connected
  UINT8                           BusNumber;                      ///< PCI Bus Number
  UINT8                           PCIeCoreID;                     ///< PCIe core ID
  UINT8                           PCIePortID;                     ///< PCIe port ID
  UINT16                          DpcStatus;                      ///< PCIe DPC status
} PCIe_DPC_STATUS_RECORD;

/// PCIE_DPC_STATUS
typedef struct {
  UINT8                           size;                                 ///< number of PCIe DPC status
  PCIe_DPC_STATUS_RECORD          DpcStatusArray[MAX_NUMBER_DPCSTATUS]; ///< PCIe DPC status Array
} PCIe_DPC_STATUS_DATA;

typedef struct _PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI;

//
// PPI prototype
//
/**
  Returns the DPC Status data structure

  This
    A pointer to the PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI instance.
  DpcStatus
    A pointer to a pointer to store the address of DPC Status data array

**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_GET_DPCSTATUS) (
  IN  PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI  *This,
  OUT PCIe_DPC_STATUS_DATA             **DpcStatus
);

///
/// The Ppi of DPC Status sevices
///
typedef struct _PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI {
  AMD_NBIO_PCIE_GET_DPCSTATUS     GetDpcStatus; ///<
} PEI_AMD_NBIO_PCIE_DPCSTATUS_PPI;

///{7E70BBC8-9E8D-4BCB-8A3F-AF0CDE679D92}
extern EFI_GUID gAmdNbioPcieDpcStatusPpiGuid ;

#endif //

