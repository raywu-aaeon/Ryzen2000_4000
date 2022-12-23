/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP APOB related functions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309172 $   @e \$Date: 2014-12-10 21:13:24 +0800 (Wed, 10 Dec 2014) $
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
#include "Uefi.h"
#include <Pi/PiMultiPhase.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdPspApobLib.h>
#include <SSP/APOB.h>
#include <ApobCommonServicePub.h>
#include <Filecode.h>

#define FILECODE LIBRARY_APOBSSPLIB_APOBSSPLIB_FILECODE


/**
 *  Return ApobApcbRecoveryFlag
 *
 *  @param[in, out] APCB Recovery Flag
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetApcbRecoveryFlagSsp (
  IN OUT   BOOLEAN  *ApcbRecoveryFlag
  )
{
  EFI_STATUS Status;
  APOB_APCB_BOOT_INFO_STRUCT *ApobEntry;
  ApobEntry = NULL;
  *ApcbRecoveryFlag = FALSE;
  if (PcdGetBool (PcdAmdPspApcbRecoveryEnable) == FALSE) {
    // Alway return FALSE, if ApcbRecovery feature disabled
    return EFI_SUCCESS;
  }
  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_APCB_BOOT_INFO_TYPE, 0, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Fail to get ApobApcbRecoveryFlag\n");
    return EFI_NOT_FOUND;
  }
  *ApcbRecoveryFlag = ApobEntry->ApcbRecoveryFlag;
  return Status;
}

/*
/**
 *  Return ApobApcbRecoveryFlag
 *
 *  @param[in, out] APCB Active Instance
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetApcbInstanceSsp (
  IN OUT   UINT8  *ApcbInstance
  )
{
  EFI_STATUS Status;
  APOB_APCB_BOOT_INFO_STRUCT *ApobEntry;
  ApobEntry = NULL;
  *ApcbInstance = 0;
  IDS_HDT_CONSOLE_PSP_TRACE ("GetApcbInstanceSsp\n");

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_APCB_BOOT_INFO_TYPE, 0, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Fail to get ApobApcbInstance\n");
    return EFI_NOT_FOUND;
  }
  *ApcbInstance = (UINT8) ApobEntry->ApcbActiveInstance;
  return Status;
}

/**
 *  Return DimmCfgUpdatedFlag
 *
 *  @param[in, out] DimmCfgUpdatedFlag
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetDimmCfgUpdatedFlagSsp (
  IN OUT   BOOLEAN  *DimmCfgUpdatedFlag
  )
{
  EFI_STATUS Status;
  APOB_APCB_BOOT_INFO_STRUCT *ApobEntry;
  ApobEntry = NULL;
  *DimmCfgUpdatedFlag = FALSE;

  IDS_HDT_CONSOLE_PSP_TRACE ("GetApcbInstanceSsp\n");
  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_APCB_BOOT_INFO_TYPE, 0, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Fail to get DimmCfgUpdatedFlag\n");
    return EFI_NOT_FOUND;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("DimmCfgUpdatedFlag %x\n", ApobEntry->DimmConfigurationUpdated);
  *DimmCfgUpdatedFlag = ApobEntry->DimmConfigurationUpdated;
  return Status;
}
/**
 *  Get the physical CCD number by reading APOB APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] CcxIndex used access ComplexMap
 *  @param[in, out] PhysComplexNumber
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetPhysCcdNumberSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN OUT   UINT8 *PhysCcdNumber
  )
{
  EFI_STATUS Status;

  APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *PhysCcdNumber = ApobEntry->CcdMap[CcdIndex].PhysCcdNumber;
  }
  return Status;
}
/**
 *  Get the physical complex number by reading APOB APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] CcxIndex used access ComplexMap
 *  @param[in, out] PhysComplexNumber
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetPhysComplexNumberSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN OUT   UINT8 *PhysComplexNumber
  )
{
  EFI_STATUS Status;

  APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *PhysComplexNumber = ApobEntry->CcdMap[CcdIndex].ComplexMap[CcxIndex].PhysComplexNumber;
  }
  return Status;
}

/**
 *  Get the physical core number by reading APOB APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] CcxIndex used access ComplexMap
 *  @param[in] CoreIndex used access CoreInfo
 *  @param[in, out] PhysCoreNumber
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetPhysCoreNumberSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN OUT   UINT8  *PhysCoreNumber
  )
{
  EFI_STATUS Status;

  APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *PhysCoreNumber = ApobEntry->CcdMap[CcdIndex].ComplexMap[CcxIndex].CoreInfo[CoreIndex].PhysCoreNumber;
  }
  return Status;
}

/**
 *  Check if the thread is enable by reading APOB APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] CcxIndex used access ComplexMap
 *  @param[in] CoreIndex used access CoreInfo
 *  @param[in] ThreadIndex used access IsThreadEnabled
 *  @param[in, out] IsThreadEnabled
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetIsThreadEnabledSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 CcdIndex,
  IN       UINT32 CcxIndex,
  IN       UINT32 CoreIndex,
  IN       UINT32 ThreadIndex,
  IN OUT   BOOLEAN *IsThreadEnabled
  )
{
  EFI_STATUS Status;

  APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCD_LOGICAL_TO_PHYSICAL_MAP_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *IsThreadEnabled = ApobEntry->CcdMap[CcdIndex].ComplexMap[CcxIndex].CoreInfo[CoreIndex].IsThreadEnabled[ThreadIndex];
  }
  return Status;
}

/**
 *  Check EccEnable by reading APOB APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] ChannelIndex used access EccEnable arrary
 *  @param[in, out] EccEnable
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetEccEnableSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ChannelIndex,
  IN OUT   BOOLEAN *EccEnable
  )
{
  EFI_STATUS Status;
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *EccEnable = ApobEntry->EccEnable[ChannelIndex];
  }
  return Status;
}

/**
 *  Get NvdimmPresentInSystem by reading APOB APOB_MEM_NVDIMM_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] NvdimmPresentInSystem
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetNvdimmPresentInSystemSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   BOOLEAN *NvdimmPresentInSystem
  )
{
  EFI_STATUS Status;
  APOB_MEM_NVDIMM_INFO_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_NVDIMM_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *NvdimmPresentInSystem = ApobEntry->NvdimmPresentInSystem;
  }
  return Status;
}

/**
 *  Get NvdimmPresentInSystem by reading APOB APOB_MEM_NVDIMM_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] NvdimmInfo
 *  @param[in, out] NvdimmInfoSize, on Input size used for hold NvdimmInfo, on Output the real size used in APOB
 *
 *  @retval       EFI_SUCCESS             Function succeed
 *  @retval       EFI_BUFFER_TOO_SMALL    NvdimmInfoSize not enough size
 *  @retval       other NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetNvdimmInfoSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT32 **NvdimmInfo,
  IN OUT   UINT32 *NvdimmInfoSize
  )
{
  EFI_STATUS Status;
  APOB_MEM_NVDIMM_INFO_STRUCT *ApobEntry;

 *NvdimmInfoSize = sizeof (ApobEntry->NvdimmInfo);

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_NVDIMM_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
     *NvdimmInfo = &ApobEntry->NvdimmInfo[0][0];
  }
  return Status;
}

/**
 *  Get MaxDimmsPerChannel of SPD structure by reading APOB APOB_MEM_DIMM_SPD_DATA_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] MaxDimmsPerChannel
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetMaxDimmsPerChannelSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxDimmsPerChannel
  )
{
  EFI_STATUS Status;
  APOB_MEM_DIMM_SPD_DATA_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_DIMM_SPD_DATA_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *MaxDimmsPerChannel = ApobEntry->MaxDimmsPerChannel;
  }
  return Status;
}

/**
 *  Get MaxChannelsPerDie
 *
 *  @param[in] ApobInstanceId not used
 *  @param[in, out] MaxDimmsPerChannel
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetMaxChannelsPerDieSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerDie
  )
{
  *MaxChannelsPerDie = ABL_APOB_MAX_CHANNELS_PER_DIE;
  return EFI_SUCCESS;
}
/**
 *  Get MaxChannelsPerSocket of SPD structure by reading APOB APOB_MEM_DIMM_SPD_DATA_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] MaxChannelsPerSocket
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetMaxChannelsPerSocketSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT8 *MaxChannelsPerSocket
  )
{
  EFI_STATUS Status;
  APOB_MEM_DIMM_SPD_DATA_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_DIMM_SPD_DATA_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *MaxChannelsPerSocket = ApobEntry->MaxChannelsPerSocket;
  }
  return Status;
}

/**
 *  Get DimmSmbusInfo of SPD structure by reading APOB APOB_MEM_DIMM_SPD_DATA_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] Index used to access DimmSmbusInfo structure
 *  @param[in, out] DimmSmbusInfo
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetDimmSmbusInfoSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN OUT   APOB_SPD_STRUCT **DimmSmbusInfo
  )
{
  EFI_STATUS Status;
  APOB_MEM_DIMM_SPD_DATA_STRUCT *ApobEntry;

  if (Index > ABL_APOB_MAX_CHANNELS_PER_DIE * ABL_APOB_MAX_DIMMS_PER_CHANNEL) {
    return EFI_NOT_FOUND;
  }

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_DIMM_SPD_DATA_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *DimmSmbusInfo = &ApobEntry->DimmSmbusInfo[Index];
  }
  return Status;
}


/**
 *  Get MemClkFreq of SPD structure by reading APOB APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] MemClkFreq
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetMemClkFreqSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *MemClkFreq
  )
{
  EFI_STATUS Status;
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *MemClkFreq = ApobEntry->MemClkFreq;
  }
  return Status;
}

/**
 *  Get DdrMaxRate of SPD structure by reading APOB APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] DdrMaxRate
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetDdrMaxRateSsp (
  IN       UINT32 ApobInstanceId,
  IN OUT   UINT16 *DdrMaxRate
  )
{
  EFI_STATUS Status;
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *DdrMaxRate = ApobEntry->DdrMaxRate;
  }
  return Status;
}


/**
 *  Get MemGenInfoElement by reading APOB APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE
 *
 *  @param[in] ApobInstanceId
 *  @param[in] ElementId
 *  @param[in, out] ElementSizeInByte
 *  @param[in, out] ElementValue
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetMemGenInfoElementSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 ElementId,
  IN OUT   UINT16 *ElementSizeInByte,
  IN OUT   UINT64 *ElementValue
  )
{
  EFI_STATUS Status;
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE, ApobInstanceId, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    switch (ElementId) {
      case MemCtrllerProcOdtDddr4Current:
        *ElementSizeInByte=2;
        *ElementValue = ApobEntry->MemCtrllerProcOdtDddr4Current[0]; ///@todo, from SSP, the data type is changed from UINT32 to UINT8 array
                                                                     /// we only return the first member of that array, maybe interface needs updated;
        break;

      case MemCtrllerRttNomDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerRttNomDddr4Current[0];
        break;

      case MemCtrllerRttWrDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerRttWrDddr4Current[0];
        break;

      case MemCtrllerRttParkDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerRttParkDddr4Current[0];
        break;

      case MemCtrllerAddrCmdSetupDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerAddrCmdSetupDddr4Current[0];
        break;

      case MemCtrllerCsOdtSetupDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCsOdtSetupDddr4Current[0];
        break;

      case MemCtrllerCkeSetupDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCkeSetupDddr4Current[0];
        break;

      case MemCtrllerCadBusAddrCmdDrvStrenDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCadBusAddrCmdDrvStrenDddr4Current[0];
        break;

      case MemCtrllerCadBusClkDrvStrenDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCadBusClkDrvStrenDddr4Current[0];
        break;

      case MemCtrllerCsOdtCmdDrvStrenDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCsOdtCmdDrvStrenDddr4Current[0];
        break;

      case MemCtrllerCkeDrvStrenDddr4Current:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->MemCtrllerCkeDrvStrenDddr4Current[0];
        break;

      case InterLeaveCapability:
        *ElementSizeInByte=4;
        *ElementValue = ApobEntry->InterLeaveCapability.Value;
        break;

      case InterLeaveCurrentMode:
        *ElementSizeInByte=4;
        *ElementValue = ApobEntry->InterLeaveCurrentMode.Value;
        break;

      case InterLeaveSize:
        *ElementSizeInByte=1;
        *ElementValue = ApobEntry->InterLeaveSize;
        break;
      default:
        ASSERT (FALSE);
        Status = EFI_NOT_FOUND;
        break;
    }
  }
  return Status;
}

/**
 *  Get NumberOfValidThresholds by reading APOB APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT
 *
 *  @param[in] ApobInstanceId
 *  @param[in, out] NumberOfValidThresholds
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetNumberOfValidThresholdsSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 *NumberOfValidThresholds
  )
{
  EFI_STATUS Status;
  APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT *ApobEntry;

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCX_EDC_THROTTLE_THRESH_TYPE, 0, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);

  if (Status == EFI_SUCCESS) {
    *NumberOfValidThresholds = ApobEntry->NumberOfValidThresholds;
  }

  return Status;
}

/**
 *  Get Thresholds by reading APOB APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT
 *
 *  @param[in] ApobInstanceId
 *  @param[in] Index
 *  @param[in, out] Thresholds
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
ApobGetThresholdsSsp (
  IN       UINT32 ApobInstanceId,
  IN       UINT32 Index,
  IN       EDC_THROTTLE_THRESHOLD **Thresholds
  )
{
  EFI_STATUS Status;
  APOB_EDC_THROTTLE_THRESHOLD_INFO_STRUCT *ApobEntry;

  if (Index > MAX_NUMBER_OF_THROTTLERS) {
    return EFI_NOT_FOUND;
  }

  Status = AmdPspGetApobEntryInstance (APOB_CCX, APOB_CCX_EDC_THROTTLE_THRESH_TYPE, 0, FALSE, (APOB_TYPE_HEADER **) &ApobEntry);
  if (Status == EFI_SUCCESS) {
    *Thresholds = &ApobEntry->Thresholds[Index];
  }

  return Status;
}

