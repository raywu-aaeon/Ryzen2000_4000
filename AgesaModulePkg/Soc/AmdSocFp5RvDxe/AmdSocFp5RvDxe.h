/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#ifndef _AMD_SOC_FP5_RV_DXE_H_
#define _AMD_SOC_FP5_RV_DXE_H_

extern EFI_GUID gAmdErrorLogDepexProtocolGuid;
extern EFI_GUID gAmdFchSandstoneDepexProtocolGuid;
extern EFI_GUID gAmdFchSSSmbusDepexProtocolGuid;
extern EFI_GUID gAmdFchSSSmmDispacherDepexProtocolGuid;
extern EFI_GUID gAmdFchSSSmmControlDepexProtocolGuid;
extern EFI_GUID gAmdPspDxeV2RvDepexProtocolGuid;
extern EFI_GUID gAmdPspP2CmboxV2DepexProtocolGuid;
extern EFI_GUID gAmdPspSmmV2DepexProtocolGuid;
extern EFI_GUID gAmdPspHstiV2DepexProtocolGuid;
extern EFI_GUID gAmdMemAm4DxeZpDepexProtocolGuid;
extern EFI_GUID gAmdMemAmdDxeDepexProtocolGuid;
extern EFI_GUID gAmdNbioBaseRVDxeDepexProtocolGuid;
extern EFI_GUID gAmdNbioSmuV10DxeDepexProtocol;
extern EFI_GUID gAmdNbioPcieRVDxeDepexProtocolGuid;
extern EFI_GUID gAmdNbioIOMMURVDxeDepexProtocolGuid;
extern EFI_GUID gAmdNbioALIBRVDxeDepexProtocolGuid;
extern EFI_GUID gAmdCcxZenRvDepexProtocolGuid;
extern EFI_GUID gAmdCcxZenRvDepexSmmProtocolGuid;
extern EFI_GUID gAmdFabricRvDepexProtocolGuid;
extern EFI_GUID gAmdMemSmbiosV2DepexProtocolGuid;
extern EFI_GUID gAmdApcbServiceRvDepexProtocolGuid;
extern EFI_GUID gAmdRasRvDepexProtocolGuid;
extern EFI_GUID gAmdMemRestoreDepexProtocolGuid;
extern EFI_GUID gApobZpRvDxeDepexProtocolGuid;

//
// Silicon Driver installation list
//

EFI_GUID * SiliconDriverProtocolList[] = {
  &gAmdErrorLogDepexProtocolGuid,
  &gAmdFchSandstoneDepexProtocolGuid,
  &gAmdFchSSSmbusDepexProtocolGuid,
  &gAmdFchSSSmmDispacherDepexProtocolGuid,
  &gAmdFchSSSmmControlDepexProtocolGuid,
  &gAmdPspDxeV2RvDepexProtocolGuid,
  &gAmdPspP2CmboxV2DepexProtocolGuid,
  &gAmdPspSmmV2DepexProtocolGuid,
  &gAmdPspHstiV2DepexProtocolGuid,
  &gAmdMemAm4DxeZpDepexProtocolGuid,
  &gAmdMemAmdDxeDepexProtocolGuid,
  &gAmdNbioBaseRVDxeDepexProtocolGuid,
  &gAmdNbioSmuV10DxeDepexProtocol,
  &gAmdNbioPcieRVDxeDepexProtocolGuid,
  &gAmdNbioIOMMURVDxeDepexProtocolGuid,
  &gAmdNbioALIBRVDxeDepexProtocolGuid,
  &gAmdCcxZenRvDepexProtocolGuid,
  &gAmdCcxZenRvDepexSmmProtocolGuid,
  &gAmdFabricRvDepexProtocolGuid,
  &gAmdMemSmbiosV2DepexProtocolGuid,
  &gAmdApcbServiceRvDepexProtocolGuid,
  &gAmdRasRvDepexProtocolGuid,
  &gAmdMemRestoreDepexProtocolGuid,
  &gApobZpRvDxeDepexProtocolGuid
};

UINT8 SiliconDriverProtocolListNumber = (UINT8) (sizeof (SiliconDriverProtocolList) / sizeof (SiliconDriverProtocolList[0]));

//
// Functions Prototypes
//
EFI_STATUS
EFIAPI
AmdSocFp5RvDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  );


#endif // _AMD_SOC_FP5_RV_DXE_H_

