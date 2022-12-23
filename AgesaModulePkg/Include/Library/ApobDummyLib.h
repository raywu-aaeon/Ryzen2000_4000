/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP APOB related functions Prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 312133 $   @e \$Date: 2015-02-03 02:47:45 +0800 (Tue, 03 Feb 2015) $
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
#ifndef _APOB_DUMMY_LIB_H_
#define _APOB_DUMMY_LIB_H_

#include <Addendum/Apcb/Inc/APOBCMN.h>

EFI_STATUS
ApobGetApcbInstanceDummy (
  IN OUT   UINT8  *ApcbInstance
  );


EFI_STATUS
ApobGetApcbRecoveryFlagDummy (
  IN OUT   BOOLEAN  *ApcbRecoveryFlag
  );


EFI_STATUS
ApobGetDimmCfgUpdatedFlagDummy (
  IN OUT   BOOLEAN  *DimmCfgUpdatedFlag
  );

EFI_STATUS
ApobGetPhysComplexNumberDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN OUT   UINT8 *PhysComplexNumber
  );

EFI_STATUS
ApobGetPhysCoreNumberDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN OUT   UINT8  *PhysCoreNumber
  );

EFI_STATUS
ApobGetIsThreadEnabledDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN       UINT32 ThreadIndex,
  IN OUT   BOOLEAN *IsThreadEnabled
  );

EFI_STATUS
ApobGetEccEnableDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ChannelIndex,
  IN OUT   BOOLEAN *EccEnable
  );

EFI_STATUS
ApobGetNvdimmPresentInSystemDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   BOOLEAN *NvdimmPresentInSystem
);

EFI_STATUS
ApobGetNvdimmInfoDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT32 **NvdimmInfo,
  IN OUT   UINT32 *NvdimmInfoSize
  );

EFI_STATUS
ApobGetMaxDimmsPerChannelDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxDimmsPerChannel
  );

EFI_STATUS
ApobGetMaxChannelsPerDieDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerDie
  );

EFI_STATUS
ApobGetMaxChannelsPerSocketDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerSocket
  );

EFI_STATUS
ApobGetDimmSmbusInfoDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN OUT   APOB_SPD_STRUCT **DimmSmbusInfo
  );

EFI_STATUS
ApobGetMemClkFreqDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *MemClkFreq
  );

EFI_STATUS
ApobGetDdrMaxRateDummy (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *DdrMaxRate
  );

EFI_STATUS
ApobGetMemGenInfoElementDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ElementId,
  IN OUT   UINT16 *ElementSizeInByte,
  IN OUT   UINT64 *ElementValue
  );

EFI_STATUS
ApobGetNumberOfValidThresholdsDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 *NumberOfValidThresholds
  );

EFI_STATUS
ApobGetThresholdsDummy (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN       EDC_THROTTLE_THRESHOLD **Thresholds
  );
#endif //_APOB_DUMMY_LIB_H_

