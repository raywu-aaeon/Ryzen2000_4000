/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory API, and related functions.
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

  AmdMemAm4Pei.c
  Init Memory interface

Abstract:
--*/

#include "PiPei.h"
//#include <Library/IdsLib.h>
#include <Ppi/AmdMemPpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Addendum/Apcb/Inc/ZP/APOB.h>
#include <Library/AmdPspApobLib.h>
#include <Library/HobLib.h>
#include "Filecode.h"

#define FILECODE MEM_AMDMEMAM4PEI_AMDMEMAM4PEI_FILECODE
extern EFI_GUID gAmdNvdimmInfoHobGuid;

EFI_STATUS
GetSystemMemoryMapInternal (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN UINT32                     *NumberOfHoles,
  IN UINT64                     *TopOfSystemMemory,
  IN  VOID                      **MemHoleDescPtr
  )
{
  EFI_STATUS                          Status;
  UINT32                              NumOfMemHoleMap;
  APOB_TYPE_HEADER                    *ApobEntry;
  APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT  *SystemMemoryMapPtr;
  APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT  SystemMemoryMap;

  Status = AmdPspGetApobEntryInstance (APOB_FABRIC, APOB_SYS_MAP_INFO_TYPE, 0, FALSE, &ApobEntry);
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  CopyMem (&SystemMemoryMap, ApobEntry, sizeof (APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT));
  //
  // Get the number of holes so that you can allocate sufficient buffer for all entries
  //
  NumOfMemHoleMap = SystemMemoryMap.ApobSystemMap.NumberOfHoles;
  //
  // Allocate some buffer for Memory Hole Map Descriptor
  //
  if (NumOfMemHoleMap != 0) {
    Status = (*PeiServices)->AllocatePool (PeiServices,
                      (((NumOfMemHoleMap -1 ) * sizeof (MEMORY_HOLE_DESCRIPTOR)) + sizeof (APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT)),
                                         &SystemMemoryMapPtr);
    if (Status != EFI_SUCCESS) {
      return Status;
    }
    CopyMem (SystemMemoryMapPtr, ApobEntry, (((NumOfMemHoleMap -1 ) * sizeof (MEMORY_HOLE_DESCRIPTOR)) + sizeof (APOB_SYSTEM_MEMORY_MAP_TYPE_STRUCT)));
    *MemHoleDescPtr =  (VOID *)&SystemMemoryMapPtr->ApobSystemMap.HoleInfo[0];
    *TopOfSystemMemory = SystemMemoryMapPtr->ApobSystemMap.TopOfSystemMemory;
    *NumberOfHoles = NumOfMemHoleMap;
  }

  return EFI_SUCCESS;
}
/*++

Routine Description:

  PSP Driver Entry. Initialize PSP device and report DRAM info to PSP once found

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdMemAm4PeimZp (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                      Status;
  AMD_MEMORY_INIT_COMPLETE_PPI    *MemInitCompleteData;
  EFI_PEI_PPI_DESCRIPTOR          *MemInitPpiList;
  APOB_TYPE_HEADER                *ApobEntry;
  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT   ApobMemGenConfig;
  APOB_MEM_NVDIMM_INFO_STRUCT         NvdimmMemoryInfo;

  ApobEntry = NULL;
  //----------------------------------------------------------------
  //
  // Allocate space for AmdMemoryInitCompletePpi
  //
  //----------------------------------------------------------------
  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (AMD_MEMORY_INIT_COMPLETE_PPI),
                                         &MemInitCompleteData);

  if (Status != EFI_SUCCESS) {
    return Status;
  }
  ZeroMem (MemInitCompleteData, sizeof (AMD_MEMORY_INIT_COMPLETE_PPI));
  MemInitCompleteData->Revision = AMD_MEMORY_INIT_COMPLETE_REVISION;

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE, 0, FALSE, &ApobEntry);

  if ((Status != EFI_SUCCESS) || (ApobEntry == NULL)) {
    MemInitCompleteData->AmdMemoryFrequency = 0;
    MemInitCompleteData->DdrMaxRate = 0;
  } else {
    CopyMem (&ApobMemGenConfig, ApobEntry, sizeof (APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE_STRUCT));
    MemInitCompleteData->AmdMemoryFrequency = ApobMemGenConfig.MemClkFreq;
    MemInitCompleteData->DdrMaxRate = ApobMemGenConfig.DdrMaxRate;

  }

  Status = (*PeiServices)->AllocatePool (PeiServices, sizeof (EFI_PEI_PPI_DESCRIPTOR), &MemInitPpiList);
  MemInitPpiList->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  MemInitPpiList->Guid  = &gAmdMemoryInitCompletePpiGuid;
  MemInitPpiList->Ppi   = MemInitCompleteData;
  ((AMD_MEMORY_INIT_COMPLETE_PPI *)MemInitPpiList->Ppi)->GetSystemMemoryMap = GetSystemMemoryMapInternal;

  Status = (*PeiServices)->InstallPpi (PeiServices, MemInitPpiList);

  Status = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_NVDIMM_INFO_TYPE, 0, FALSE, &ApobEntry);
  if (Status == EFI_SUCCESS) {
    CopyMem(&NvdimmMemoryInfo, ApobEntry, sizeof(APOB_MEM_NVDIMM_INFO_STRUCT));
    if (BuildGuidDataHob (&gAmdNvdimmInfoHobGuid, &NvdimmMemoryInfo.NvdimmInfo[0][0], sizeof (NvdimmMemoryInfo.NvdimmInfo)) == NULL) {
      Status = EFI_NOT_FOUND;
    }
  }

  return (Status);
}


