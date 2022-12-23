/* $NoKeywords:$ */
/**
 * @file
 *
 * APOB common service Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#ifndef _AMD_PSP_COMMONSERVICE_PROTOCOL_H_
#define _AMD_PSP_COMMONSERVICE_PROTOCOL_H_

#include "ApobCommonServicePub.h"
#include <Addendum/Apcb/Inc/APOBCMN.h>


typedef
EFI_STATUS
(*FP_GET_APCB_RECOVERY_FLAG)(
  IN OUT   BOOLEAN  *ApcbRecoveryFlag
  );

typedef
EFI_STATUS
(*FP_GET_DIMMCFG_UPDATED_FLAG) (
  IN OUT   BOOLEAN  *DimmCfgUpdatedFlag
  );

typedef
EFI_STATUS
(*FP_GET_APCB_INSTANCE) (
  IN OUT   UINT8  *ApcbInstance
  );

typedef
EFI_STATUS
(*FP_GET_PHYS_CCD_NUMBER) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN OUT   UINT8 *PhysCcdNumber
);

typedef
EFI_STATUS
(*FP_GET_PHYS_COMPLEX_NUMBER) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN OUT   UINT8 *PhysComplexNumber
);

typedef
EFI_STATUS
(*FP_GET_PHYSCORE_NUMBER) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN OUT   UINT8  *PhysCoreNumber
);

typedef
EFI_STATUS
(*FP_GET_IS_THREAD_ENABLED) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN       UINT32 ThreadIndex,
  IN OUT   BOOLEAN *IsThreadEnabled
);

typedef
EFI_STATUS
(*FP_GET_ECC_ENABLE) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ChannelIndex,
  IN OUT   BOOLEAN *EccEnable
);

typedef
EFI_STATUS
(*FP_GET_NVDIMM_PRESENT_IN_SYSTEM) (
  IN       UINT32 ApobInstanceId,
  IN OUT   BOOLEAN *NvdimmPresentInSystem
);

typedef
EFI_STATUS
(*FP_GET_NVDIMM_INFO) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT32 **NvdimmInfo,
  IN OUT   UINT32 *NvdimmInfoSize
);

typedef
EFI_STATUS
(*FP_GET_MAX_DIMMS_PER_CHANNEL) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxDimmsPerChannel
);

typedef
EFI_STATUS
(*FP_GET_MAX_CHANNELS_PER_SOCKET) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerSocket
);
typedef
EFI_STATUS
(*FP_GET_MAX_CHANNELS_PER_DIE) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerDie
);
typedef
EFI_STATUS
(*FP_GET_DIMM_SMBUS_INFO) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN OUT   APOB_SPD_STRUCT **DimmSmbusInfo
);

typedef
EFI_STATUS
(*FP_GET_MEMORY_FREQUENCY) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *AmdMemoryFrequency
);

typedef
EFI_STATUS
(*FP_GET_DDR_MAX_RATE) (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *DdrMaxRate
);

typedef
EFI_STATUS
(*FP_GET_MEM_GEN_INFO_ELEMENT) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ElementId,
  IN OUT   UINT16 *ElementSizeInByte,
  IN OUT   UINT64 *ElementValue
  );

typedef
EFI_STATUS
(*FP_GET_NUMBER_OF_VALID_THRESHOLDS) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 *NumberOfValidThresholds
  );

typedef
EFI_STATUS
(*FP_GET_THRESHOLDS) (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN       EDC_THROTTLE_THRESHOLD **Thresholds
  );

///
/// PPI prototype
///
/// Defines APOB_COMMON_SERVICE_PROTOCOL, which public the common APOB service across all programs
///
typedef struct _APOB_COMMON_SERVICE_PROTOCOL {
  FP_GET_APCB_INSTANCE                    ApobGetApcbInstance;
  FP_GET_APCB_RECOVERY_FLAG               ApobGetApcbRecoveryFlag;
  FP_GET_DIMMCFG_UPDATED_FLAG             ApobGetDimmCfgUpdatedFlag;
  FP_GET_PHYS_CCD_NUMBER                  ApobGetPhysCcdNumber;
  FP_GET_PHYS_COMPLEX_NUMBER              ApobGetPhysComplexNumber;
  FP_GET_PHYSCORE_NUMBER                  ApobGetPhysCoreNumber;
  FP_GET_IS_THREAD_ENABLED                ApobGetIsThreadEnabled;
  FP_GET_ECC_ENABLE                       ApobGetEccEnable;
  FP_GET_NVDIMM_PRESENT_IN_SYSTEM         ApobGetNvdimmPresentInSystem;
  FP_GET_NVDIMM_INFO                      ApobGetNvdimmInfo;
  FP_GET_MAX_DIMMS_PER_CHANNEL            ApobGetMaxDimmsPerChannel;
  FP_GET_MAX_CHANNELS_PER_DIE             ApobGetMaxChannelsPerDie;
  FP_GET_MAX_CHANNELS_PER_SOCKET          ApobGetMaxChannelsPerSocket;
  FP_GET_DIMM_SMBUS_INFO                  ApobGetDimmSmbusInfo;
  FP_GET_MEMORY_FREQUENCY                 ApobGetMemoryFrequency;
  FP_GET_DDR_MAX_RATE                     ApobGetDdrMaxRate;
  FP_GET_MEM_GEN_INFO_ELEMENT             ApobGetMemGenInfoElement;
  FP_GET_NUMBER_OF_VALID_THRESHOLDS       ApobGetNumberOfValidThresholds;
  FP_GET_THRESHOLDS                       ApobGetThresholds;
} APOB_COMMON_SERVICE_PROTOCOL;

extern EFI_GUID gApobCommonServiceProtocolGuid;

#endif //_AMD_PSP_COMMONSERVICE_PROTOCOL_H_

