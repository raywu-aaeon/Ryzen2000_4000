/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains implementation for the SMM Access2 Protocol
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision:  $   @e \$Date:  $
 *
 */
/*
 ******************************************************************************
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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */


#include <PiDxe.h>
#include <Filecode.h>
#include <IdsHookId.h>
#include <cpuRegisters.h>
#include <Protocol/SmmAccess2.h>
#include <Protocol/MpService.h>
#include <Library/CcxSmmAccess2Lib.h>
#include <Library/CcxRolesLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IdsLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Guid/SmramMemoryReserve.h>

#define FILECODE LIBRARY_DXECCXSMMACCESS2LIB_CCXSMMACCESS2LIB_FILECODE

extern  EFI_BOOT_SERVICES *gBS;

EFI_HANDLE                SmmAccessHandle = NULL;
EFI_SMRAM_DESCRIPTOR      *mSmramMap;
EFI_MP_SERVICES_PROTOCOL  *mMpServices = NULL;
UINTN                     NumberOfRegions = 0;
BOOLEAN                   mSkipSmmLock = TRUE;

STATIC EFI_SMM_ACCESS2_PROTOCOL mSmmAccess2 = {
  CcxSmmOpen2,
  CcxSmmClose2,
  CcxSmmLock2,
  CcxSmmGetCapabilities2,
  FALSE,
  FALSE
};

/*---------------------------------------------------------------------------------------*/
/**
 *  Helper routine to open SMRAM on cores
 *
 *  @param[in]     Unused                  Unused
 *
 */
VOID
EFIAPI
OpenSmramOnCore (
  IN       VOID *Unused
 )
{
  if (CcxIsComputeUnitPrimary (NULL)) {
    // Disable protection in ASeg and TSeg
    AsmMsrAnd64 (SMMMASK_ADDRESS, ~((UINT64) BIT1 | (UINT64) BIT0));

    // Enable FixMtrrModEn
    AsmMsrOr64 (SYS_CFG, LShiftU64(1, 19));

    // Enable Rd/Wr DRAM in ASeg
    AsmMsrOr64 (AMD_MTRR_FIX16k_A0000, 0x1818181818181818);

    // Disable FixMtrrModEn
    AsmMsrAnd64 (SYS_CFG, ~(LShiftU64 (1, 19)));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Helper routine to close SMRAM on cores
 *
 *  @param[in]     Unused                  Unused
 *
 */
VOID
EFIAPI
CloseSmramOnCore (
  IN       VOID *Unused
 )
{
  if (CcxIsComputeUnitPrimary (NULL)) {
    // Disable protection in ASeg and TSeg
    AsmMsrAnd64 (SMMMASK_ADDRESS, ~((UINT64) BIT1 | (UINT64) BIT0));

    // Enable FixMtrrModEn
    AsmMsrOr64 (SYS_CFG, LShiftU64 (1, 19));

    // Disable Rd/Wr DRAM in ASeg
    AsmMsrAnd64 (AMD_MTRR_FIX16k_A0000, 0xE7E7E7E7E7E7E7E7);

    // Disable FixMtrrModEn
    AsmMsrAnd64 (SYS_CFG, ~(LShiftU64 (1, 19)));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Helper routine to lock SMRAM on cores
 *
 *  @param[in]     Unused                  Unused
 *
 */
VOID
EFIAPI
LockSmramOnCore (
  IN       VOID *Unused
 )
{
  AsmWbinvd ();

  AsmMsrOr64 (SMMMASK_ADDRESS, (BIT1 | BIT0));

  if (!mSkipSmmLock) {
    AsmMsrOr64 (MSR_HWCR, SMMLOCK);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Opens the SMRAM area to be accessible by a boot-service driver
 *
 *  @param[in]     This                  The EFI_SMM_ACCESS2_PROTOCOL instance
 *
 *  @retval        EFI_SUCCESS           The operation was successful
 *  @retval        EFI_DEVICE_ERROR      SMRAM cannot be opened, perhaps because it is locked
 *  @retval        EFI_UNSUPPORTED       The system does not support opening and closing of SMRAM
 */
EFI_STATUS
EFIAPI
CcxSmmOpen2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  )
{

  UINTN      Index;
  EFI_STATUS Status;

  Status = EFI_SUCCESS;
  if ((mSmmAccess2.LockState) || (mMpServices == NULL)) {
    Status = EFI_DEVICE_ERROR;
    return Status; 
  }

  for (Index = 0; Index < NumberOfRegions; Index++) {
    if (mSmramMap[Index].RegionState & EFI_SMRAM_LOCKED) {
      IDS_HDT_CONSOLE (CPU_TRACE, "CcxSmmOpen2: RegionState %d is locked\n", Index);
      continue;
    }
    mSmramMap[Index].RegionState &= ~(EFI_SMRAM_CLOSED | EFI_ALLOCATED);
    mSmramMap[Index].RegionState |= EFI_SMRAM_OPEN;
  }

  OpenSmramOnCore (NULL);
  mMpServices->StartupAllAPs (
               mMpServices,
               OpenSmramOnCore,
               FALSE,
               NULL,
               0,
               NULL,
               NULL
               );

  mSmmAccess2.OpenState = TRUE;

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Inhibits access to the SMRAM.
 *
 *  @param[in]     This                  The EFI_SMM_ACCESS2_PROTOCOL instance
 *
 *  @retval        EFI_SUCCESS           The operation was successful
 *  @retval        EFI_DEVICE_ERROR      SMRAM cannot be closed
 *  @retval        EFI_UNSUPPORTED       The system does not support opening and closing of SMRAM
 */
EFI_STATUS
EFIAPI
CcxSmmClose2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  )
{

  UINTN Index;
  EFI_STATUS Status;

  Status = EFI_SUCCESS;
  if (mSmmAccess2.LockState) {
    Status = EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < NumberOfRegions; Index++) {
    if (mSmramMap[Index].RegionState & (EFI_SMRAM_LOCKED | EFI_SMRAM_CLOSED)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "CcxSmmClose2: RegionState %d is locked\n", Index);
      continue;
    }
    mSmramMap[Index].RegionState &= ~EFI_SMRAM_OPEN;
    mSmramMap[Index].RegionState |= (EFI_SMRAM_CLOSED | EFI_ALLOCATED);
  }

  CloseSmramOnCore (NULL);
  mMpServices->StartupAllAPs (
               mMpServices,
               CloseSmramOnCore,
               FALSE,
               NULL,
               0,
               NULL,
               NULL
               );

  mSmmAccess2.OpenState = FALSE;

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Inhibits access to the SMRAM
 *
 *  @param[in]     This                  The EFI_SMM_ACCESS2_PROTOCOL instance
 *
 *  @retval        EFI_SUCCESS           The device was successfully locked
 *  @retval        EFI_UNSUPPORTED       The system does not support locking of SMRAM
 */
EFI_STATUS
EFIAPI
CcxSmmLock2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  )
{
  UINTN                 Index;
  UINT32                *SMIx98;
  UINT64                FchAddress;
  EFI_STATUS            Status;


  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxSmmLock2: LOCKING SMM\n");
  Status = EFI_SUCCESS;

  if (mSmmAccess2.OpenState) {
    Status = EFI_DEVICE_ERROR;
  }

  for (Index = 0; Index < NumberOfRegions; Index++) {
    mSmramMap[Index].RegionState |= EFI_SMRAM_LOCKED;
  }

  /// @todo Use FCH library to enable/disable SMI
  // Disable SMI generation
  FchAddress = FCH_MMIO_ADDRESS + SMI_REGISTER_SPACE + SMI_TRIG0_OFFSET;
  SMIx98 = (UINT32 *) FchAddress;
  *SMIx98 |= SMIENB;

  mMpServices->StartupAllAPs (
                mMpServices,
                LockSmramOnCore,
                FALSE,
                NULL,
                0,
                NULL,
                NULL
                );

  LockSmramOnCore (NULL);

  mSmmAccess2.LockState = TRUE;

  // Re-enable SMI generation
  *SMIx98 &= ~SMIENB;

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Queries the memory controller for the regions that will support SMRAM
 *
 *  @param[in]       This                The EFI_SMM_ACCESS2_PROTOCOL instance
 *  @param[in, out]  SmramMapSize        A pointer to the size, in bytes, of the SmramMemoryMap
 *                                       buffer. On input, this value is the size of the buffer
 *                                       that is allocated by the caller. On output, it is the
 *                                       size of the buffer that was returned if the buffer was
 *                                       large enough, or, if the buffer was too small, the size
 *                                       of the buffer that is needed to contain the map
 *  @param[in, out]  SmramMap            A pointer to the buffer in which firmware places the
 *                                       current memory map. The map is an array of EFI_SMRAM_DESCRIPTORs
 *
 *  @retval        EFI_SUCCESS           The operation was successful
 *  @retval        EFI_BUFFER_TOO_SMALL  SmramMapSize buffer is too small
 */
EFI_STATUS
EFIAPI
CcxSmmGetCapabilities2 (
  IN CONST EFI_SMM_ACCESS2_PROTOCOL *This,
  IN OUT   UINTN                    *SmramMapSize,
  IN OUT   EFI_SMRAM_DESCRIPTOR     *SmramMap
  )
{
  UINTN Size;
  EFI_STATUS Status;

  Size = NumberOfRegions * sizeof (EFI_SMRAM_DESCRIPTOR);
  Status = EFI_SUCCESS;

  if ((*SmramMapSize >= Size) && (SmramMap != NULL)) {
    CopyMem (SmramMap, mSmramMap, Size);
  } else {
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxSmmGetCapabilities2: SmramMapSize is too small!\n");
    Status = EFI_BUFFER_TOO_SMALL;
  }

  *SmramMapSize = Size;

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Helper routine to program TsegBase and TsegMask
 *
 *  @param[in]     TsegConfig                  Tseg configuration data
 *
 */
VOID
EFIAPI
SetupSmmRegs (
  IN       CCX_SMM_TSEG_CONFIG  *TsegConfig
  )
{
  if (CcxIsComputeUnitPrimary (NULL)) {
    // Setup TSegBase and TSegMask
    AsmWriteMsr64 (SMMADDR_ADDRESS, TsegConfig->TsegBase);
    AsmWriteMsr64 (SMMMASK_ADDRESS, TsegConfig->TsegMask);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *  This library produces the SMM Access2 Protocol.
 *
 *
 *  @retval        EFI_SUCCESS           SMM Access2 Protocol installed successfully
 *  @retval        EFI_NOT_FOUND         SMM Access2 Protocol installation failed
 */
EFI_STATUS
EFIAPI
CcxSmmAccess2ProtocolInstall (
  )
{
  UINTN                          Index;
  UINT64                         TotalSize;
  EFI_STATUS                     Status;
  EFI_HOB_GUID_TYPE              *GuidHob;
  CCX_SMM_TSEG_CONFIG            TsegConfig;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *SmramDescriptorBlock;

  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  (VOID **) &mMpServices
                  );

  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  GuidHob = GetFirstGuidHob (&gEfiSmmPeiSmramMemoryReserveGuid);

  if (GuidHob == NULL) {
    return EFI_NOT_FOUND;
  }

  SmramDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *) GET_GUID_HOB_DATA (GuidHob);

  if (SmramDescriptorBlock == NULL) {
    return EFI_NOT_FOUND;
  }

  mSmramMap = AllocateZeroPool ((SmramDescriptorBlock->NumberOfSmmReservedRegions) * sizeof (EFI_SMRAM_DESCRIPTOR));

  NumberOfRegions = SmramDescriptorBlock->NumberOfSmmReservedRegions;

  TotalSize = 0;
  for (Index = 0; Index < NumberOfRegions; Index++) {
    mSmramMap[Index].PhysicalStart = SmramDescriptorBlock->Descriptor[Index].PhysicalStart;
    mSmramMap[Index].CpuStart      = SmramDescriptorBlock->Descriptor[Index].CpuStart;
    mSmramMap[Index].PhysicalSize  = SmramDescriptorBlock->Descriptor[Index].PhysicalSize;
    mSmramMap[Index].RegionState   = SmramDescriptorBlock->Descriptor[Index].RegionState;
    TotalSize += mSmramMap[Index].PhysicalSize;
  }

  TsegConfig.TsegBase = mSmramMap[0].PhysicalStart;
  TsegConfig.TsegMask = ~(TotalSize - 1) | 0x6600;

  SetupSmmRegs (&TsegConfig);

  mMpServices->StartupAllAPs (
               mMpServices,
               SetupSmmRegs,
               FALSE,
               NULL,
               0,
               (VOID *) &TsegConfig,
               NULL
               );

  IDS_SKIP_HOOK (IDS_HOOK_CCX_SKIP_SMM_LOCK, NULL, NULL) {
    mSkipSmmLock = FALSE;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &SmmAccessHandle,
                  &gEfiSmmAccess2ProtocolGuid,
                  &mSmmAccess2,
                  NULL
                  );

  return EFI_SUCCESS;
}





