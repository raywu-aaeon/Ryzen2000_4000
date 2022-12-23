/**
 * @file
 *
 * SMU V10 Service definitions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision:
 *
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
 */
#ifndef _AMD_NBIO_SMU_V10_PEI_H_
#define _AMD_NBIO_SMU_V10_PEI_H_

#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>

EFI_STATUS
EFIAPI
SmuReadFuseByName (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN       UINT32                         InstanceId,
  IN       UINTN                          FuseName,
  IN OUT   UINTN                          *BufferSize,
     OUT   UINT8                          *FuseValue
  );

EFI_STATUS
EFIAPI
SmuReadFuseByLocation (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              FuseChain,
  IN  UINT32                              FuseStartBit,
  IN  UINT32                              FuseSize,
  OUT UINT32                              *FuseValue
  );

EFI_STATUS
EFIAPI
SmuServiceRequest (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              ServiceRequest,
  IN  UINT32                              *InputParameters,
  OUT UINT32                              *ReturnValues
  );

EFI_STATUS
EFIAPI
SmuRegisterRead (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              RegisterIndex,
  OUT UINT32                              *RegisterValue
  );

EFI_STATUS
EFIAPI
SmuRegisterWrite (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              RegisterIndex,
  IN  UINT32                              *RegisterValue
  );

EFI_STATUS
EFIAPI
SmuRegisterRMW (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              RegisterIndex,
  IN  UINT32                              RegisterANDValue,
  IN  UINT32                              RegisterORValue
  );


EFI_STATUS
EFIAPI
SmuHtcControl (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  OUT BOOLEAN                             *HtcStatus
  );

EFI_STATUS
EFIAPI
SmuReadCacWeights (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              MaxNumWeights,
  OUT UINT64                              *ApmWeights,
  OUT UINT32                              *NumWeightsRead,
  OUT UINT32                              *EnergyCountNormalize
  );

EFI_STATUS
EFIAPI
SmuPsiControl (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              TargetVid,
  IN  UINT32                              TargetNbVid
  );

EFI_STATUS
EFIAPI
SmuGetTdpValue (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  OUT UINT32                              *TdpValue
  );

EFI_STATUS
EFIAPI
SmuReadBrandString (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI       *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              BrandStringLength,
  OUT UINT8                               *BrandString
  );

EFI_STATUS
EFIAPI
SmuReadCorePllLockTimer (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI        *This,
  IN  UINT32                               InstanceId,
  OUT UINT32                               *LockTimerValue
  );

EFI_STATUS
AmdNbioSmuEarlyInit (
  IN       PCIe_PLATFORM_CONFIG            *Pcie
  );

#endif

