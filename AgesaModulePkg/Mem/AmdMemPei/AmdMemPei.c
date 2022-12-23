/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory API for CZ DDR4, and related functions.
 *
 * Contains code that initializes memory
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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
/*++
Module Name:

  AmdMemPei.c
  Init Memory interface

Abstract:
--*/

#include "PiPei.h"
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Ppi/AmdMemPpi.h>
#include <Library/AmdMemBaseLib/AmdMemBaseLib.h>
#include <Uefi.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdMemMainLib/AmdMemMainLib.h>
#include <Library/AmdMemServicesLib.h>
#include "Filecode.h"

#define FILECODE MEM_AMDMEMPEI_AMDMEMPEI_FILECODE

STATIC PEI_INITIALIZE_AGESA_MEMORY_PPI mInitializeAgesaMemoryPpi = {
  AMD_MEMORY_INITIALIZE_AGESA_MEMORY_REVISION
};

STATIC EFI_PEI_PPI_DESCRIPTOR mInitializeAgesaMemoryPiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdMemoryInitializeAgesaMemoryPpiGuid,
  &mInitializeAgesaMemoryPpi
};

STATIC PEI_MEMORY_INIT_COMPLETE_PPI mMemoryInitCompletePpi = {
  AMD_MEMORY_INIT_COMPLETE_REVISION,
  AmdGetMemoryAbove4gbService,
  AmdGetMemoryBelow4gbService,
  AmdGetMemoryBelow1TbService,
  AmdGetBottomIoService,
  AmdGetTotalMemorySizeService,
  AmdGetMemoryFrequencyService,
  AmdGetUmaInfoService
};

STATIC EFI_PEI_PPI_DESCRIPTOR mMemoryInitCompleteiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdMemoryInitCompletePpiGuid,
  &mMemoryInitCompletePpi
};

STATIC AMD_MEM_POOL_PTR_TABLE_PPI mMemPoolPtrTablePpi = {
  AMD_MEM_POOL_PTR_TABLE_REVISION
};

STATIC EFI_PEI_PPI_DESCRIPTOR mMemPolPtrTablePiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdMemoryPoolPointerTablePpiGuid,
  &mMemPoolPtrTablePpi
};
/*++

Routine Description:

  PSP Driver Entry. Initialize PSP device and report DRAM info to PSP once found

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
PeiAmdMemEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  MEM_DATA_STRUCT       *MemDataStructure;
  //PEI_AMD_SOC_ID_CHECK_PPI *AmdSocIdPpiPtr;
  AMD_MEM_POOL_PTR_TABLE_PPI *AmdPoolTablePtr;
  IN AMD_CONFIG_PARAMS  *StdHeader;

  //-----------------------------------------
  //
  //              Check SOC ID
  //
  //-----------------------------------------
  //Status = (*PeiServices)->LocatePpi (PeiServices,
  //                                    &AmdSocIdCheckPpi,
  //                                    0,
  //                                    NULL,
  //                                    &AmdSocIdPpiPtr);
  //if (EFI_SUCCESS != Status) {
  //  // return error message.
  //  return Status;
  //}
  //Status = AmdSocIdPpiPtr->CheckSocId (PeiServices, SocId);
  //if (Status != EFI_SUCCESS) {
  //  return EFI_NOT_FOUND;
  //}

  StdHeader = NULL;
  AGESA_TESTPOINT (TpProcMemAmdMemAuto, StdHeader);
  //----------------------------------------------------------------
  //
  // Initialize Pool Pointer table - keep track of pointers allocated form the pool
  //
  //----------------------------------------------------------------
  Status = (**PeiServices).InstallPpi (PeiServices, &mMemPolPtrTablePiList);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  //----------------------------------------------------------------
  //
  //            Allocate space for data structure
  //
  //----------------------------------------------------------------
  Status = (*PeiServices)->AllocatePool (
                           PeiServices,
                           sizeof (MEM_DATA_STRUCT),
                           &MemDataStructure
                           );
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  //----------------------------------------------------------------
  //
  //            Save allocate space for data structure
  //
  //----------------------------------------------------------------
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                    &gAmdMemoryPoolPointerTablePpiGuid,
                                    0,
                                    NULL,
                                    &AmdPoolTablePtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  AmdPoolTablePtr->PtrTable[AMD_MEM_DATA_STRUCT_POOL_PTR] = (UINT32*)MemDataStructure;

  //----------------------------------------------------------------
  //
  //            Initialize PCDs values in memory data structure
  //
  //----------------------------------------------------------------

  // Initialize Parameters
  // MemMainInitParameters(MemDataStructure);

  //----------------------------------------------------------------
  //
  //            Initialize Memory
  //
  //----------------------------------------------------------------
  IDS_HDT_CONSOLE (MAIN_FLOW, "Memory Driver\n");

  //----------------------------------------------------------------
  //
  //            Initiate Program specific Memory initialization
  //
  //----------------------------------------------------------------
  Status = (**PeiServices).InstallPpi (PeiServices, &mInitializeAgesaMemoryPiList);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  //----------------------------------------------------------------
  //
  //            De-allocate space for data structure
  //
  //----------------------------------------------------------------
  AmdPoolTablePtr->PtrTable[AMD_MEM_DATA_STRUCT_POOL_PTR] = (UINT32*)NULL;
  //----------------------------------------------------------------
  //
  //          Indicate that Memory initialization complete
  //
  //----------------------------------------------------------------
  Status = (**PeiServices).InstallPpi (PeiServices, &mMemoryInitCompleteiList);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  AGESA_TESTPOINT (TpProcMemEnd, StdHeader);
  return (Status);
}


