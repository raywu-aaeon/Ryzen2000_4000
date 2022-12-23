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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include "AmdRasSspSmm.h"
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Protocol/AmdRasSmm2Protocol.h>
#include <Protocol/AmdMemPprProtocol.h>
#include <Library/BaseFabricTopologyLib.h>
#include <Library/SmnAccessLib.h>
#include "AGESA.h"
#include "Library/IdsLib.h"


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE RAS_AMDRASSSPSMM_AMDRASSSPSMM_FILECODE


/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
ADDR_DATA                *gAddrData;
AMD_RAS_POLICY           *mAmdRasPolicy;


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
EFIAPI
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
EFIAPI
AmdSetSmiTrigIoCycle (
   IN       UINT64 SmiTrigIoCycleData
  );

EFI_STATUS
EFIAPI
AmdGetAllLocalSmiStatus (
  IN       LOCAL_SMI_STATUS *pLocalSmiStatusList
  );

EFI_STATUS
EFIAPI
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO_V2* RasMcaErrorInfo
  );

EFI_STATUS
EFIAPI
AmdRasSmmExitType (
  IN       UINTN ProcessorNumber,
  IN       UINTN SmiExitType
  );

EFI_STATUS
EFIAPI
AmdGetSmmSaveStateBase (
  IN       UINTN   ProcessorNumber,
  OUT      UINT64* SmmSaveStateBase
  );

EFI_STATUS
EFIAPI
AmdSetMcaCloakCfg (
   IN       UINTN  ProcessorNumber,
   IN       UINT64 CloakValue,
   IN       UINT64 UnCloakValue
   );

EFI_STATUS
EFIAPI
AmdClrMcaStatus (
  IN       UINTN    ProcessorNumber,
  IN       UINTN    McaBankNumber,
  IN       BOOLEAN  IsWrMsr
  );

EFI_STATUS
EFIAPI
AmdMapSymbolToDramDevice (
  IN       AMD_RAS_SMM2_PROTOCOL *This,
  IN       RAS_MCA_ERROR_INFO_V2    *RasMcaErrorInfo,
  IN       NORMALIZED_ADDRESS   *NormalizedAddress,
  IN       UINT8                BankIndex,
  OUT      UINT32               *DeviceStart,
  OUT      UINT32               *DeviceEnd,
  OUT      UINT8                *DeviceType
  );

EFI_STATUS
EFIAPI
AmdSetMcaThreshold (
  IN       UINTN                 *ProcessorNumber,
  IN       UINTN                 *McaBankNumber,
  IN       RAS_THRESHOLD_CONFIG  *RasThresholdConfig,
  IN       BOOLEAN               OvrflwChk
);

STATIC
VOID
retrieve_regs (
  UINTN   pkgno,
  UINTN   mpuno,
  UINTN   umcno,
  UINTN   umcchno,
  UINTN   BusNumberBase
  );

EFI_STATUS
GetPostpackageRepairInfo (
  IN       AMD_DIMM_INFO    *AmdDimmInfo,
  OUT      AMD_PPR_INFO     *PprInfo
  );


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
STATIC AMD_RAS_SMM2_PROTOCOL    AmdRasSmm2Protocol = {
  AmdMcaErrorAddrTranslate,
  AmdTranslateSysAddrToCS,
  AmdSetSmiTrigIoCycle,
  AmdGetAllLocalSmiStatus,
  AmdSearchMcaError,
  AmdRasSmmExitType,
  AmdGetSmmSaveStateBase,
  AmdSetMcaCloakCfg,
  AmdClrMcaStatus,
  AmdMapSymbolToDramDevice,
  AmdSetMcaThreshold
};

typedef struct {
  UINTN                 *ProcessorNumber;
  UINTN                 *McaBankNumber;
  RAS_THRESHOLD_CONFIG  *RasThresholdConfig;
  BOOLEAN               OvrflwChk;
} SET_MP_MCA_THRESHOLD_FNC_ARG;

/*********************************************************************************
 * Name: AmdRasSspSmmInit
 *
 * Description
 *   Entry point of the AMD RAS SSP SMM driver
 *   Register Ras Smm callbacks
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdRasSspSmmInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )

{
  EFI_STATUS        Status;
  EFI_HANDLE        Handle = NULL;
  RAS_THRESHOLD_CONFIG RasThresholdConfig;

  DEBUG((EFI_D_INFO, "[RAS] SSP AGESA RAS SMM driver entry\n"));

  // Get AMD Ras Policy
  Status = gBS->LocateProtocol (&gAmdRasInitDataProtocolGuid, NULL, &mAmdRasPolicy);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;    // Error detected while trying to locate pool
  }

  //Init memory address data pointer
  gAddrData = mAmdRasPolicy->AddrData;

  //PFEH enabled, firmware should setup the Error Thresholding and set interrupt type to SMI.
  //PFEH Disabled, OS will enable error threshold.
  if (mAmdRasPolicy->PFEHEnable) {
    DEBUG((EFI_D_INFO, "[RAS] Platform-First Error Handle Enabled!!!\n"));
    //Set ECC error threshold through all banks.
    RasThresholdConfig.ThresholdControl = mAmdRasPolicy->McaErrThreshEn;
    RasThresholdConfig.ThresholdCount = mAmdRasPolicy->McaErrThreshCount;
    RasThresholdConfig.ThresholdIntType = 2;          // SMI

    if (mAmdRasPolicy->McaErrThreshEn) {
        DEBUG((EFI_D_INFO, "MCE Error Threshold Enable : Counter = 0x%04x\n", mAmdRasPolicy->McaErrThreshCount));
    }

    AmdSetMcaThreshold(NULL, NULL, &RasThresholdConfig, FALSE);
  }

  Status = gSmst->SmmInstallProtocolInterface(
               &Handle,
               &gAmdRasSmm2ProtocolGuid,
               EFI_NATIVE_INTERFACE,
               &AmdRasSmm2Protocol
           );


  return Status;
}


/*---------------------------------------------------------------------------------------*/
/**
 * MCA_ADDR Address Translate
 *
 * Translate UMC local address into specific memory DIMM information and system address
 *
 *
 * @param[in]   NormalizedAddress      UMC memory address Information
 * @param[out]  SystemMemoryAddress    System Address
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
EFIAPI
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{

  DEBUG((EFI_D_INFO, "[RAS]NormalizedAddr: 0x%08x", NormalizedAddress->normalizedAddr >> 32));
  DEBUG((EFI_D_INFO, "%08x\n", NormalizedAddress->normalizedAddr & 0xFFFFFFFF));
  DEBUG((EFI_D_INFO, "[RAS]NormalizedSocId: 0x%x, DieId: 0x%x, ChannelId: 0x%x\n", NormalizedAddress->normalizedSocketId, NormalizedAddress->normalizedDieId, NormalizedAddress->normalizedChannelId));

  translate_norm_to_dram_addr (NormalizedAddress->normalizedAddr,
                               NormalizedAddress->normalizedSocketId,
                               NormalizedAddress->normalizedDieId,
                               NormalizedAddress->normalizedChannelId,
                               0,
                               &DimmInfo->ChipSelect,
                               &DimmInfo->Bank,
                               &DimmInfo->Row,
                               &DimmInfo->Column,
                               &DimmInfo->rankmul
                               );

  *SystemMemoryAddress = calcSysAddr(NormalizedAddress->normalizedAddr,
                                     NormalizedAddress->normalizedSocketId,
                                     NormalizedAddress->normalizedDieId,
                                     NormalizedAddress->normalizedChannelId
                                     );

  if (0xffffffffffffffff == *SystemMemoryAddress) {   // Return with EFI_INVALID_PARAMETER on invalid system address
    return EFI_INVALID_PARAMETER;
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * System Address Translate
 *
 * Translate system address into specific memory DIMM information and normalized address
 * information
 *
 * @param[in]   SystemMemoryAddress    System Address
 * @param[out]  NormalizedAddress      UMC memory address Information
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
EFIAPI
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{

  *NormalizedAddress = calcNormAddr(*SystemMemoryAddress);

  translate_norm_to_dram_addr (NormalizedAddress->normalizedAddr,
                               NormalizedAddress->normalizedSocketId,
                               NormalizedAddress->normalizedDieId,
                               NormalizedAddress->normalizedChannelId,
                               0,
                               &DimmInfo->ChipSelect,
                               &DimmInfo->Bank,
                               &DimmInfo->Row,
                               &DimmInfo->Column,
                               &DimmInfo->rankmul
                               );

  return EFI_SUCCESS;
}



/*---------------------------------------------------------------------------------------*/
/**
 * UMC Address Translate
 *
 * Translate physical address into specific memory channel information
 *
 *
 * @param[in/out]  RasDimmInfo      UMC memory address Information
 *
 */

EFI_STATUS
EFIAPI
AmdSetSmiTrigIoCycle (
   IN       UINT64 SmiTrigIoCycleData
)
{

  RAS_BSP_AP_MSR_SYNC ApMsrSync[3];
  UINT16              i;

  //RedirSmiEn = 1
  AsmMsrOr64 (MSR_MCEXCEPREDIR, BIT9);
  //Set SmiTrigIoCycle
  AsmMsrAndThenOr64 (MSR_SMITRIGIOCYCLE, 0xFFFFFFF800000000, SmiTrigIoCycleData);

  ZeroMem (ApMsrSync, sizeof (ApMsrSync));

  i = 0;

  ApMsrSync[i].RegisterAddress = MSR_MCEXCEPREDIR;
  ApMsrSync[i++].RegisterMask  = BIT9;

  ApMsrSync[i].RegisterAddress = MSR_SMITRIGIOCYCLE;
  ApMsrSync[i++].RegisterMask  = 0x0000000FFFFFFFFF;

  LibRasSmmSyncMsr(ApMsrSync);

  return EFI_SUCCESS;
}

VOID
GetApLocalSmiStatus (
  LOCAL_SMI_STATUS* LocalSmiStatus
  )
{

  SMM_SAVE_STATE* ApSmmSaveState;

  ApSmmSaveState = (SMM_SAVE_STATE*)(AsmReadMsr64 (MSR_SMM_BASE)+ SMM_SAVE_STATE_OFFSET);
  LocalSmiStatus->Value = (UINT64)ApSmmSaveState->LocalSmiStatus;

}

EFI_STATUS
EFIAPI
AmdGetAllLocalSmiStatus (
  IN       LOCAL_SMI_STATUS* pLocalSmiStatusList
  )
{

  UINTN ProcessorNumber;
  SMM_SAVE_STATE* BspSmmSaveState;

  BspSmmSaveState = (SMM_SAVE_STATE*)(AsmReadMsr64 (MSR_SMM_BASE) + SMM_SAVE_STATE_OFFSET);

  pLocalSmiStatusList[0].Value = (UINT64)BspSmmSaveState->LocalSmiStatus;
  if (pLocalSmiStatusList[0].Value != 0) {
    DEBUG((EFI_D_INFO, "CPU0 Local SMI Status = 0x%08x\n", pLocalSmiStatusList[0].Value));
  }

  for (ProcessorNumber = 1; ProcessorNumber < gSmst->NumberOfCpus; ProcessorNumber++) {
    gSmst->SmmStartupThisAp (
            GetApLocalSmiStatus,
            ProcessorNumber,
            &pLocalSmiStatusList[ProcessorNumber]
            );
    if (pLocalSmiStatusList[ProcessorNumber].Value != 0) {
      DEBUG((EFI_D_INFO, "CPU%d", ProcessorNumber));
      DEBUG((EFI_D_INFO, " Local SMI Status = 0x%08x\n", pLocalSmiStatusList[ProcessorNumber].Value));
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO_V2* RasMcaErrorInfo
  )
{

  UINTN Index;
  BOOLEAN CpuMapFound = FALSE;

  if (RasMcaErrorInfo->CpuInfo.ProcessorNumber > mAmdRasPolicy->TotalNumberOfProcessors) {
    return EFI_INVALID_PARAMETER;
  }

  Index = 0;
  for (Index = 0; Index < mAmdRasPolicy->TotalNumberOfProcessors; Index++) {
      if (mAmdRasPolicy->RasCpuMap[Index].ProcessorNumber == RasMcaErrorInfo->CpuInfo.ProcessorNumber) {
        RasMcaErrorInfo->CpuInfo.SocketId = mAmdRasPolicy->RasCpuMap[Index].SocketId;
        RasMcaErrorInfo->CpuInfo.CcxId = mAmdRasPolicy->RasCpuMap[Index].CcxId;
        RasMcaErrorInfo->CpuInfo.DieId = mAmdRasPolicy->RasCpuMap[Index].DieId;
        RasMcaErrorInfo->CpuInfo.CoreId = mAmdRasPolicy->RasCpuMap[Index].CoreId;
        RasMcaErrorInfo->CpuInfo.ThreadID = mAmdRasPolicy->RasCpuMap[Index].ThreadID;
        CpuMapFound = TRUE;
        break;
      }
  }
  if (!CpuMapFound) {
      return EFI_NOT_FOUND;
  }

  CollectMpMcaErrorInfo(RasMcaErrorInfo);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
AmdRasSmmExitType (
  IN       UINTN ProcessorNumber,
  IN       UINTN SmiExitType
  )
{

  RAS_MSR_ACCESS RasMsrAccess;

  //Set SMI exit type
  RasMsrAccess.RegisterAddress = MSR_PFEH_CFG;
  RasMsrAccess.RegisterValue   = SmiExitType;
  RasMsrAccess.RegisterMask    = SMI_EXITTYPE_MASK;

  LibRasSmmMsrWrite (&RasMsrAccess, ProcessorNumber);

  return EFI_SUCCESS;
}

VOID
GetApSmmSaveStateBase (
  UINT64* ApSaveStateBase
  )
{
  *ApSaveStateBase = AsmReadMsr64 (MSR_SMM_BASE)+ SMM_SAVE_STATE_OFFSET;
}


EFI_STATUS
EFIAPI
AmdGetSmmSaveStateBase (
   IN       UINTN ProcessorNumber,
   OUT      UINT64* SmmSaveStateBase
   )
{
  if (ProcessorNumber == 0) {
    *SmmSaveStateBase = (AsmReadMsr64(MSR_SMM_BASE) + SMM_SAVE_STATE_OFFSET);
    return EFI_SUCCESS;
  }

  gSmst->SmmStartupThisAp (
          GetApSmmSaveStateBase,
          ProcessorNumber,
          SmmSaveStateBase
          );
  return EFI_SUCCESS;
}


VOID
McaCloakControl (
  IN       RAS_MSR_ACCESS *RasMsrAccess
  )
{
  // MSR_PFEH_CLOAK_CFG data = (((MSR_PFEH_CLOAK_CFG data) & ~(UnCloakValue)) | CloakValue)
  AsmMsrAndThenOr64 (RasMsrAccess->RegisterAddress, ~(RasMsrAccess->RegisterMask), RasMsrAccess->RegisterValue);
  return;
}

EFI_STATUS
EFIAPI
AmdSetMcaCloakCfg (
   IN       UINTN ProcessorNumber,
   IN       UINT64 CloakValue,
   IN       UINT64 UnCloakValue
   )
{
  RAS_MSR_ACCESS RasMsrAccess;

  //Cloak MC register (CloakValue)    : If BITx (i.e. Bank x) is set (= 1) then Bank x will be Cloaked
  //Uncloak MC register (UnCloakValue): If BITx (i.e. Bank x) is set (= 1) then Bank x will be UnCloaked
  //Note:
  //01. CloakValue has a higher priority than UnCloakValue.
  //02. Unspecified BITs (BITx = 0) in CloakValue and UnCloakValue paremeters will maintain its original value.
  RasMsrAccess.RegisterAddress = MSR_PFEH_CLOAK_CFG; //0xC0010121
  RasMsrAccess.RegisterValue = CloakValue;
  RasMsrAccess.RegisterMask  = UnCloakValue;

  LibRasSmmRunFunc (McaCloakControl, &RasMsrAccess, ProcessorNumber);
  return EFI_SUCCESS;

}

VOID
McaStatusClr (
   IN VOID  *Buffer
 )
{

  UINT8  *McaBankNumber;
  UINT32 McaBankAddrBase;

  McaBankNumber = (UINT8*)Buffer;
  McaBankAddrBase = MCA_EXTENSION_BASE + (*McaBankNumber * SMCA_REG_PER_BANK);

  // MSR_C001_0015[18][McStatusWrEn] = 1
  AsmMsrAndThenOr64(MSR_HWCR, ~BIT18, BIT18);

  //Clear MCA_STATUS, MCA_ADDR, MCA_SYND, MCA_DEADDR, MCA_DESTAT
  AsmWriteMsr64 (McaBankAddrBase | MCA_ADDR_OFFSET, 0);
  AsmWriteMsr64 (McaBankAddrBase | MCA_SYND_OFFSET, 0);
  AsmWriteMsr64 (McaBankAddrBase | MCA_DEADDR_OFFSET, 0);
  AsmWriteMsr64 (McaBankAddrBase | MCA_DESTAT_OFFSET, 0);
  AsmWriteMsr64 (McaBankAddrBase | MCA_STATUS_OFFSET, 0);

  // MSR_C001_0015[18][McStatusWrEn] = 0
  AsmMsrAndThenOr64(MSR_HWCR, ~BIT18, 0);
}

EFI_STATUS
EFIAPI
AmdClrMcaStatus (
  IN       UINTN            ProcessorNumber,
  IN       UINTN    McaBankNumber,
  IN       BOOLEAN          IsWrMsr
   )
{
  RAS_MSR_ACCESS RasMsrAccess;
  UINT32 ECX_Data;
  UINT32 EAX_Data;
  UINT32 EDX_Data;
  UINT64 Msr_Data;
  UINT64 Hwcr_Data;
  UINT64 SmmSaveStateBase;
  SMM_SAVE_STATE* SmmSaveState;
  BOOLEAN IsMsrStatus;

  if (IsWrMsr) {
    //Check which register OS want to update ECX for Bank and Register, EAX:EDX for the Value
    AmdGetSmmSaveStateBase(ProcessorNumber, &SmmSaveStateBase);
    SmmSaveState = (SMM_SAVE_STATE*)SmmSaveStateBase;

    ECX_Data = (UINT32)(SmmSaveState->RCX & 0xFFFFFFFF);
    EAX_Data = (UINT32)(SmmSaveState->RAX & 0xFFFFFFFF);
    EDX_Data = (UINT32)(SmmSaveState->RDX & 0xFFFFFFFF);

    Msr_Data = (UINT64)EDX_Data;
    Msr_Data = (Msr_Data << 32) | EAX_Data;

    //Prepare MSR update table
    RasMsrAccess.RegisterAddress = MSR_HWCR;
    LibRasSmmMsrRead(&RasMsrAccess, ProcessorNumber);
    Hwcr_Data = RasMsrAccess.RegisterValue;

    IsMsrStatus = FALSE;
    //Check MCA_STATUS write
    if ((MCA_LEGACY_BASE <= ECX_Data) && (ECX_Data < MCA_LEGACY_TOP_ADDR)) {
      //Legacy MCA address
      if ((ECX_Data & MCA_REG_OFFSET_MASK) == MCA_STATUS_OFFSET) {
        IsMsrStatus = TRUE;
      }
    } else if (ECX_Data == LMCA_STATUS_REG){
        IsMsrStatus = TRUE;
    } else {
      //Extension MCA Address
      if ((ECX_Data & SMCA_REG_OFFSET_MASK) == MCA_STATUS_OFFSET) {
        IsMsrStatus = TRUE;
      }
    }

    // BIOS should abort and leave MCA register uncloak if OS does not set
    // MSR_C001_0015[18][McStatusWrEn] = 1
    if (IsMsrStatus) {
      //HWCR[18] need set when write non 0 value to MCA_STATUS
      if ((Msr_Data != 0) && ((Hwcr_Data & BIT18) == 0)) {
          return EFI_ABORTED;
        }
    }
    RasMsrAccess.RegisterAddress = ECX_Data;
    RasMsrAccess.RegisterValue = Msr_Data;
    RasMsrAccess.RegisterMask  = 0xFFFFFFFFFFFFFFFF;

    LibRasSmmMsrWrite (&RasMsrAccess,ProcessorNumber);
  } else {
    LibRasSmmRunFunc(McaStatusClr, &McaBankNumber, ProcessorNumber);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
GetPostpackageRepairInfo (
  IN       AMD_DIMM_INFO    *AmdDimmInfo,
  OUT      AMD_PPR_INFO     *PprInfo
)
{
  EFI_STATUS Status;
  AMD_POST_PACKAGE_REPAIR_INFO_PROTOCOL *PPRInterface;

  Status = gSmst->SmmLocateProtocol (&gAmdPostPackageRepairInfoProtocolGuid, NULL, &PPRInterface);
  if (EFI_ERROR (Status)) {
    return Status;    // Error detected
  }
  Status = PPRInterface->AmdGetPprInfo(PPRInterface, AmdDimmInfo, PprInfo);
  return Status;
}


/*********************************************************************************
 * Name: AmdMapSymbolToDramDevice
 *
 * Description
 *   Maps ECC Symbol to DRAM device based on DIMM device width, EccSymbolSize and
 *   EccBitInterleaving
 *
 * Arguments:
 *   RasMcaErrorInfo  : Structure containing error information
 *   NormalizedAddress : Structure containing DIMM location information
 *   BankIndex : Offset of data in McaBankErrorInfo struct
 *   DeviceStart : First device to repair
 *   DeviceEnd : Last device to repair
 *   DeviceWidth : DIMM Device Width from SPD
 *
 * Returns:
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdMapSymbolToDramDevice (
  IN AMD_RAS_SMM2_PROTOCOL *This,
  IN RAS_MCA_ERROR_INFO_V2 *RasMcaErrorInfo,
  IN NORMALIZED_ADDRESS   *NormalizedAddress,
  IN UINT8                BankIndex,
  OUT UINT32               *DeviceStart,
  OUT UINT32               *DeviceEnd,
  OUT UINT8                *DeviceWidth
)
{
  EFI_STATUS Status;
  UINT64 Symbol, Address;
  UMC_ECCCTRL_REG RasEccCtrlReg;
  AMD_DIMM_INFO AmdDimmInfo;
  DIMM_INFO DimmInfo;
  AMD_PPR_INFO PprInfo;
  UINT32 RasEccCtrlRegAddress;
  UINT32 BusNumber;
  UINT32 EccSymbolSize;

  //Get device width from AmdPostPackageRepairInfoProtocol
  AmdMcaErrorAddrTranslate(NormalizedAddress, &Address, &DimmInfo);
  AmdDimmInfo.SocketId = NormalizedAddress->normalizedSocketId;
  AmdDimmInfo.DieId = NormalizedAddress->normalizedDieId;
  AmdDimmInfo.ChannelId = NormalizedAddress->normalizedChannelId;
  AmdDimmInfo.Chipselect = DimmInfo.ChipSelect;
  Status = GetPostpackageRepairInfo(&AmdDimmInfo, &PprInfo);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Error calling GetPostpackageRepairInfo.\n"));
    return Status;    // Error detected
  }
  *DeviceWidth = (1<<(PprInfo.DeviceWidth & 0x7))*4;
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: Device Width: 0x%x\n", *DeviceWidth));

  //Check for multi-bit error, return all valid devices for a given DeviceType x4=0-17, x8=0-8
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: McaStatusMsr.Field.Deferred: 0x%x\n",
    RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaStatusMsr.Field.Deferred));
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: McaConfigMsr.Field.LogDeferredInMcaStat: 0x%x\n",
    RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaConfigMsr.Field.LogDeferredInMcaStat));
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: McaDeStatMsr.Field.Val: 0x%x\n",
    RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaDeStatMsr.Field.Val));
  if ((RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaStatusMsr.Field.Deferred) ||
    ((RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaConfigMsr.Field.LogDeferredInMcaStat == 0) &&
    (RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaDeStatMsr.Field.Val)))
    {
      *DeviceStart = 0;
      switch (*DeviceWidth) {
        case DEVICE_WIDTH_x4:
          *DeviceEnd = 17;
          break;
        case DEVICE_WIDTH_x8:
          *DeviceEnd = 8;
          break;
        default:
          *DeviceEnd = 0;
          DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Device Width for multi-bit error.\n"));
          return EFI_INVALID_PARAMETER;
    }
    DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: Returning DeviceStart: 0x%x, "
      "DeviceEnd: 0x%x, DeviceWidth: 0x%x\n", *DeviceStart, *DeviceEnd, *DeviceWidth));
    return EFI_SUCCESS;
  }

  // Error is not a Deferred Error, need to check
  // MCA_SYND[ErrorPriority] != Corrected
  if (RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaSyndMsr.Field.ErrorPriority != MCA_SYND_ERROR_PRIORITY_CORRECTED) {
    DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Syndrome\n"));
    return EFI_UNSUPPORTED;
  }


  //Read RAS ECC Control register to get EccSymbolSize and EccBitInterleaving values
  RasEccCtrlRegAddress = (UMC0_CH_REG_BASE + (UMC_SMN_ADDR_OFFSET * NormalizedAddress->normalizedChannelId)) | UMC_ECC_CTRL;

  BusNumber = (UINT32) FabricTopologyGetHostBridgeBusBase (
                         NormalizedAddress->normalizedSocketId,
                         NormalizedAddress->normalizedDieId, 0);
  SmnRegisterRead (BusNumber, RasEccCtrlRegAddress, &RasEccCtrlReg.Value);

  //For SSP a new register field EccSymbolSize16 exists to indicate x16 Symbol
  //size.  If this bit is set ignore EccSymbolSize.
  if (RasEccCtrlReg.Field.EccSymbolSize16 == 1) {
    EccSymbolSize = ECC_SYMBOL_SIZE_x16;
  } else {
  //Otherwise, use EccSymbolSize as the size
    EccSymbolSize = RasEccCtrlReg.Field.EccSymbolSize;
  }

  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: EccSymbolSize: 0x%x\n",
    EccSymbolSize));
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: EccBitInterleaving: 0x%x\n",
    RasEccCtrlReg.Field.EccBitInterleaving));

  //Get Symbol from ErrorInformation passed in.
  //For DramEccErr, Symbol = ErrorInformation[13:8]
  Symbol = RasMcaErrorInfo->McaBankErrorInfo[BankIndex].McaSyndMsr.Field.ErrorInformation;
  Symbol = ((Symbol >> 8) & 0x3F);
  //Check for valid symbol from HW then adjust at the end.
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: Raw Symbol: 0x%x\n", Symbol));
  if (Symbol == 0) {
    DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Symbol: 0x%x\n", Symbol));
    return EFI_INVALID_PARAMETER;
  }
  //Adjust symbol after checking for valid case.
  Symbol--;

  if (*DeviceWidth == DEVICE_WIDTH_x4) {
    if (EccSymbolSize == ECC_SYMBOL_SIZE_x4) {
      if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
        *DeviceStart = (UINT32) Symbol / 2;
        *DeviceEnd = *DeviceStart;
      } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
        if (Symbol < 0x20) {
          *DeviceStart = (UINT32) Symbol % 0x10;
          *DeviceEnd = *DeviceStart;
        } else {
          *DeviceStart = (UINT32) (Symbol % 2) + 0x10;
          *DeviceEnd = *DeviceStart;
        }
      } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
        }
    } else if (EccSymbolSize == ECC_SYMBOL_SIZE_x8) {
      if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
        *DeviceStart = (UINT32) Symbol;
        *DeviceEnd = *DeviceStart;
      } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
        if (Symbol < 0x10) {
          *DeviceStart = (UINT32) (Symbol*2) % 0x10;
          *DeviceEnd = (UINT32) ((Symbol*2) + 1) % 0x10;
        } else {
          *DeviceStart = (UINT32) 0x10;
          *DeviceEnd = (UINT32) 0x11;
        }
      } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size = 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
        }
    } else if (EccSymbolSize == ECC_SYMBOL_SIZE_x16) {
      if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
        *DeviceStart = (UINT32) Symbol;
        *DeviceEnd = *DeviceStart;
      } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
        if (Symbol < 0x10) {
          *DeviceStart = (UINT32) (Symbol*4) % 0x10;
          *DeviceEnd = (UINT32) ((Symbol*4) + 3) % 0x10;
        } else {
          *DeviceStart = (UINT32) 0x10;
          *DeviceEnd = (UINT32) 0x11;
        }
      } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size = 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
        }
    } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
    }

  } else if (*DeviceWidth == DEVICE_WIDTH_x8) {
  if (EccSymbolSize == ECC_SYMBOL_SIZE_x4) {
    if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
      *DeviceStart = (UINT32) Symbol / 4;
      *DeviceEnd = *DeviceStart;
    } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
      if (Symbol < 0x20) {
        *DeviceStart = (UINT32) (Symbol / 2) % 0x8;
        *DeviceEnd = *DeviceStart;
      } else {
        *DeviceStart = 0x8;
        *DeviceEnd = *DeviceStart;
      }
    } else {
      DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
        "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
        *DeviceWidth, EccSymbolSize,
        RasEccCtrlReg.Field.EccBitInterleaving));
      return EFI_INVALID_PARAMETER;
      }
    } else if (EccSymbolSize == ECC_SYMBOL_SIZE_x8) {
      if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
        *DeviceStart = (UINT32) Symbol / 2;
        *DeviceEnd = *DeviceStart;
      } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
        if (Symbol < 0x10) {
          *DeviceStart = (UINT32) Symbol % 8;
          *DeviceEnd = *DeviceStart;
        } else {
          *DeviceStart = 0x8;
          *DeviceEnd = *DeviceStart;
        }
      } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
        }
    } else if (EccSymbolSize == ECC_SYMBOL_SIZE_x16) {
      if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_ENABLED) {
        *DeviceStart = (UINT32) Symbol / 2;
        *DeviceEnd = *DeviceStart;
      } else if (RasEccCtrlReg.Field.EccBitInterleaving == ECC_BIT_INTERLEAVING_DISABLED) {
        if (Symbol < 0x10) {
          *DeviceStart = (UINT32) 2 * (Symbol % 4);
          *DeviceEnd = *DeviceStart + 1;
        } else {
          *DeviceStart = 0x10;
          *DeviceEnd = 0x11;
        }
      } else {
        DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
            "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
            *DeviceWidth, EccSymbolSize,
            RasEccCtrlReg.Field.EccBitInterleaving));
        return EFI_INVALID_PARAMETER;
        }
    } else {
      DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
        "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
        *DeviceWidth, EccSymbolSize,
        RasEccCtrlReg.Field.EccBitInterleaving));
      return EFI_INVALID_PARAMETER;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid Parameter Width: 0x%x, "
        "ECC Symbol Size: 0x%x, Bit Interleave: 0x%x\n",
        *DeviceWidth, EccSymbolSize,
        RasEccCtrlReg.Field.EccBitInterleaving));
    return EFI_INVALID_PARAMETER;
  }
  //Check data returned to ensure that it is valid
  if ((*DeviceWidth == DEVICE_WIDTH_x4) && (*DeviceEnd > 0x11) ||
    (*DeviceWidth == DEVICE_WIDTH_x8) && (*DeviceEnd > 0x8))
  {
    DEBUG ((DEBUG_ERROR, "AmdMapSymbolToDramDevice: Invalid End Device generated: 0x%x",
      *DeviceEnd));
    return EFI_INVALID_PARAMETER;
  }
  DEBUG ((DEBUG_VERBOSE, "AmdMapSymbolToDramDevice: Returning DeviceStart: 0x%x, "
    "DeviceEnd: 0x%x, DeviceWidth: 0x%x\n", *DeviceStart, *DeviceEnd, *DeviceWidth));
  return EFI_SUCCESS;
}

EFI_STATUS
SetCoreMcaThreshold (
  IN       SET_MP_MCA_THRESHOLD_FNC_ARG *pProcArg
  )
{
  UINT8                BankNum;
//  UINT64               McMisc0;
  UINT64               MsrData;
  UINT32               i;
  UINT32        Misc0Addr;
  UINT32        Misc1Addr;
  UINT64               SaveHwcr;
  MCA_IPID_MSR         McIpid;
  MCA_MISC0_MSR Misc0;
  MCA_MISC1_MSR Misc1;
  BOOLEAN       OvrFlwChk;

  MsrData = AsmReadMsr64 (MSR_MCG_CAP);            // MCG_CAP
  BankNum = (UINT8)(MsrData & 0xFF);

  if ((pProcArg->McaBankNumber != NULL) && (*(pProcArg->McaBankNumber) > BankNum)) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((EFI_D_INFO, "[In Core] ThresholdControl: 0x%02x, ThresholdCount: 0x%02x, ThresholdIntType: 0x%02x \n",
        pProcArg->RasThresholdConfig->ThresholdControl,
        pProcArg->RasThresholdConfig->ThresholdCount,
        pProcArg->RasThresholdConfig->ThresholdIntType));

//  McMisc0 = pProcArg->RasThresholdConfig->ThresholdIntType;
//  McMisc0 = (UINT64)(((McMisc0 << 17 | (pProcArg->RasThresholdConfig->ThresholdCount & 0x0FFF)) << 32) | BIT51);

  if (pProcArg->RasThresholdConfig->ThresholdControl) {
    // MSR_C001_0015[18][McStatusWrEn] = 1
    SaveHwcr = AsmReadMsr64 (MSR_HWCR);
    MsrData = SaveHwcr | BIT18;
    AsmWriteMsr64 (MSR_HWCR, MsrData);
#if 0
    for (i = 0; i < BankNum; i++) {
      if ((pProcArg->McaBankNumber != NULL) && (i != *(pProcArg->McaBankNumber))) {
        continue;
      }
      DEBUG ((EFI_D_INFO, "[In Core] McaBankNumber: %02d\n", i));
      AsmMsrAndThenOr64 ((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC0_OFFSET), 0xFFF1F000FFFFFFFF, McMisc0);

      //Check if it is UMC bank
      McIpid.Value = AsmReadMsr64 ((MCA_EXTENSION_BASE + (i * 0x10) | MCA_IPID_OFFSET));            // MCA_IPID
      if (McIpid.Field.HardwareID == MCA_UMC_ID) {
        AsmMsrAndThenOr64 ((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC1_OFFSET), 0xFFF1F000FFFFFFFF, McMisc0);
      }
    }
#endif

    for (i = 0; i < BankNum; i++) {
      if ((pProcArg->McaBankNumber != NULL) && (i != *(pProcArg->McaBankNumber))) {
        continue;
      }
      DEBUG ((EFI_D_INFO, "[In Core] McaBankNumber: %02d\n", i));
      Misc0Addr = (MCA_EXTENSION_BASE + (i * SMCA_REG_PER_BANK)) | MCA_MISC0_OFFSET;
      Misc1Addr = (MCA_EXTENSION_BASE + (i * SMCA_REG_PER_BANK)) | MCA_MISC1_OFFSET;
      Misc0.Value = AsmReadMsr64 (Misc0Addr);

      //Check if it is UMC bank
      McIpid.Value = AsmReadMsr64 ((MCA_EXTENSION_BASE + (i * SMCA_REG_PER_BANK) | MCA_IPID_OFFSET));            // MCA_IPID
      Misc1.Value = 0;
      DEBUG((EFI_D_INFO, "[In Core] MCA IPID: 0x%04x\n", McIpid.Field.HardwareID));
      if (McIpid.Field.HardwareID == MCA_UMC_ID) {
        Misc1.Value = AsmReadMsr64 (Misc1Addr);
      }
      //Check if ErrCnt was enabled.

      OvrFlwChk = (((Misc0.Field.Ovrflw == 1) ? TRUE:FALSE) & ((Misc0.Field.CntEn == 1) ? TRUE:FALSE)) | !pProcArg->OvrflwChk;

      if (OvrFlwChk) {
        Misc0.Field.CntEn = 0;

        Misc0.Field.ErrCnt = pProcArg->RasThresholdConfig->ThresholdCount;
        Misc0.Field.ThresholdIntType = pProcArg->RasThresholdConfig->ThresholdIntType;
        //Clear Ovrflw bit.
        Misc0.Field.Ovrflw = 0;

        AsmWriteMsr64 (Misc0Addr, Misc0.Value);
        Misc0.Field.CntEn = 1;
        AsmWriteMsr64 (Misc0Addr, Misc0.Value);
      }

      OvrFlwChk = (((Misc1.Field.Ovrflw == 1) ? TRUE:FALSE) & ((Misc1.Field.CntEn == 1) ? TRUE:FALSE)) | !pProcArg->OvrflwChk;
      if (Misc1.Field.Valid && OvrFlwChk) {
        Misc1.Field.CntEn = 0;
        Misc1.Field.ErrCnt = pProcArg->RasThresholdConfig->ThresholdCount;
        Misc1.Field.ThresholdIntType = pProcArg->RasThresholdConfig->ThresholdIntType;
        //Clear Ovrflw bit.
        Misc1.Field.Ovrflw = 0;

        AsmWriteMsr64 (Misc1Addr, Misc1.Value);
        Misc1.Field.CntEn = 1;
        AsmWriteMsr64 (Misc1Addr, Misc1.Value);
      }
    }
    // Restore MSR_C001_0015[18][McStatusWrEn]
    AsmWriteMsr64 (MSR_HWCR, SaveHwcr);
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set Mca Threshold
 *
 * Set MCA Threshold to specific MCA bank(s) and Processor(s)
 *
 *
 * @param[in]   *ProcessorNumber       Pointer to Processor Number info variable (NULL: all processor)
 * @param[in]   *McaBankNumber         Pointer to MCA bank Number info variable  (NULL: all MCA BANK)
 * @param[in]   *RasThresholdConfig    Pointer to RAS_THRESHOLD_CONFIG variable  (Cannot be NULL)
 * @param[in]   OvrflwChk              Ovrflw bit check variable                 (TRUE = Check Ovrflw bit, FALSE = Always reset ErrCnt)
 *
 */
EFI_STATUS
EFIAPI
AmdSetMcaThreshold (
  IN       UINTN                 *ProcessorNumber,
  IN       UINTN                 *McaBankNumber,
  IN       RAS_THRESHOLD_CONFIG  *RasThresholdConfig,
  IN       BOOLEAN               OvrflwChk
)
{
  EFI_STATUS                   Status;
  SET_MP_MCA_THRESHOLD_FNC_ARG ProcArg;
  UINT16                       i;

  Status = EFI_SUCCESS;

  ProcArg.ProcessorNumber = NULL;
  if ((ProcessorNumber != NULL) && (*ProcessorNumber > gSmst->NumberOfCpus)) {
    return EFI_INVALID_PARAMETER;
  } else {
    ProcArg.ProcessorNumber = ProcessorNumber;
  }

  if (RasThresholdConfig == NULL) {
    return EFI_INVALID_PARAMETER;
  } else {
    ProcArg.RasThresholdConfig = RasThresholdConfig;
  }

  ProcArg.McaBankNumber = NULL;
  if (McaBankNumber != NULL) {
    ProcArg.McaBankNumber = McaBankNumber;
  }

  ProcArg.OvrflwChk = OvrflwChk;

  //Program BSP
  if ((ProcessorNumber == NULL) ||
      ((ProcessorNumber != NULL) && (*ProcessorNumber) == 0)) {
    DEBUG ((EFI_D_INFO, "ProcessorNumber: 0\n"));
    Status = SetCoreMcaThreshold(&ProcArg);

    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //Program AP
  for (i = 1; i < gSmst->NumberOfCpus; i++) {
    if ((ProcessorNumber != NULL) && (i != *ProcessorNumber)) {
      continue;
    }
    DEBUG ((EFI_D_INFO, "ProcessorNumber: %02d\n", i));
    Status = gSmst->SmmStartupThisAp (
                      SetCoreMcaThreshold,
                      i,
                      (VOID *) &ProcArg
                      );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return Status;
}
