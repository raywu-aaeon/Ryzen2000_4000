/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdMemoryInfoHobPeim.
 *
 * Contains code that create Memory Hob.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 320059 $   @e \$Date: 2015-06-04 00:21:59 -0500 (Thu, 04 Jun 2015) $
 *
 */
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
/*++
Module Name:

  AmdMemoryInfoHobPeim.c

Abstract:
--*/

#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/AmdMemoryInfoHob.h>
#include <Ppi/AmdMemoryInfoHobPpi.h>
#include <Ppi/AmdMemPpi.h>
#include <Addendum/Apcb/Inc/RV/APOB.h>
#include <Library/AmdPspApobLib.h>
#include <Library/IdsLib.h>
#include <Ppi/Pcd.h>
#include <PiPei.h>
#include <Library/PeiServicesLib.h>

#include "Filecode.h"
#define FILECODE UNIVERSAL_AMDMEMORYHOBINFOPEIM_AMDMEMORYHOBINFOPEIM_FILECODE

extern EFI_GUID gAmdMemoryInitCompletePpiGuid;
extern EFI_GUID gAmdNvdimmInfoHobGuid;
typedef struct _MEMORY_INFO_BLOCK_STRUCT {
  IN BOOLEAN           MemFrequencyValid;   ///< Memory Frequency Valid
  IN UINT32            MemFrequency;        ///< Memory Frequency
  IN BOOLEAN           VddioValid;          ///< This field determines if Vddio is valid
  IN UINT16            Vddio;               ///< Vddio Voltage
  IN BOOLEAN           VddpVddrValid;       ///< This field determines if VddpVddr is valid
  IN UINT8             VddpVddr;            ///< VddpVddr voltage
  IN UINT32            DdrMaxRate;          ///< UMC DdrMaxRateVddpVddr
} MEMORY_INFO_BLOCK_STRUCT;

#ifndef FOURGB
#define FOURGB      0x100000000ull
#endif

#define MAX_NUMBER_OF_EXTENDED_MEMORY_DESCRIPTOR    19
#define MAX_SIZEOF_AMD_MEMORY_INFO_HOB_BUFFER       (sizeof (AMD_MEMORY_INFO_HOB) +  \
          (MAX_NUMBER_OF_EXTENDED_MEMORY_DESCRIPTOR * sizeof (AMD_MEMORY_RANGE_DESCRIPTOR)))

/*
#define AMD_MEMORY_ATTRIBUTE_AVAILABLE      0x1
#define AMD_MEMORY_ATTRIBUTE_UMA            0x2
#define AMD_MEMORY_ATTRIBUTE_MMIO           0x3
#define AMD_MEMORY_ATTRIBUTE_RESERVED       0x4

*/

#define IDS_HDT_CONSOLE_MEM_RAGE_DESC(MemRangeIndex, MemRangeDesc) \
        { \
          IDS_HDT_CONSOLE (MAIN_FLOW, "MemRangeIndex[0x%x]:\n", MemRangeIndex);  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Base Hi: 0x%08x\n", RShiftU64 (MemRangeDesc[MemRangeIndex].Base, 32));   \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Base Lo: 0x%08x\n", ((MemRangeDesc[MemRangeIndex].Base) & 0xFFFFFFFF));  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Size Hi: 0x%08x\n", RShiftU64 (MemRangeDesc[MemRangeIndex].Size, 32));   \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Size Lo: 0x%08x\n", ((MemRangeDesc[MemRangeIndex].Size) & 0xFFFFFFFF));  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Attribute: 0x%08x (%s)\n", MemRangeDesc[MemRangeIndex].Attribute, \
                                          (MemRangeDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) ? L"Availalbe" : \
                                          (MemRangeDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_UMA) ? L"UMA" : \
                                          (MemRangeDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_MMIO) ? L"MMIO" : \
                                          (MemRangeDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_RESERVED) ? L"Reserved" : L"Unknown" \
                                          );            \
        }

#define IDS_HDT_CONSOLE_MEM_CURRENT_BASE(CurrentBase) \
        { \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    CurrentBase Hi: 0x%08x\n", RShiftU64(CurrentBase, 32)); \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    CurrentBase Lo: 0x%08x\n", (CurrentBase & 0xFFFFFFFF)); \
        }

#define IDS_HDT_CONSOLE_MEM_HOLE(MemHoleIndex, MemHoleMap) \
        { \
          IDS_HDT_CONSOLE (MAIN_FLOW, "\nMemHoleIndex[0x%x]:\n", MemHoleIndex);  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Base Hi: 0x%08x\n", RShiftU64 (MemHoleMap[MemHoleIndex].Base, 32));   \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Base Lo: 0x%08x\n", ((MemHoleMap[MemHoleIndex].Base) & 0xFFFFFFFF));  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Size Hi: 0x%08x\n", RShiftU64 (MemHoleMap[MemHoleIndex].Size, 32));   \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Size Lo: 0x%08x\n", ((MemHoleMap[MemHoleIndex].Size) & 0xFFFFFFFF));  \
          IDS_HDT_CONSOLE (MAIN_FLOW, "    Type: 0x%08x (%s)\n", MemHoleMap[MemHoleIndex].Type, \
                                          (MemHoleMap[MemHoleIndex].Type == UMA) ? L"UMA" : \
                                          (MemHoleMap[MemHoleIndex].Type == MMIO) ? L"MMIO" : \
                                          (MemHoleMap[MemHoleIndex].Type == PrivilegedDRAM) ? L"PrivilegedDRAM" : L"Unknown" \
                                          );            \
        }

//
// PPI Initialization
//
STATIC AMD_MEMORY_INFO_HOB_PPI mAmdMemoryHobInfoAvailblePpi = {
  AMD_MEMORY_INFO_HOB_PPI_REVISION
};


STATIC EFI_PEI_PPI_DESCRIPTOR mAmdMemoryHobInfoAvailblePpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdMemoryInfoHobPpiGuid,
  &mAmdMemoryHobInfoAvailblePpi
};

EFI_STATUS
BuildHobInfo (
  IN CONST  EFI_PEI_SERVICES    **PeiServices,
  IN MEMORY_INFO_BLOCK_STRUCT   *MemoInfoBlockPtr
  );

EFI_STATUS
BuildHobInfo (
  IN CONST  EFI_PEI_SERVICES    **PeiServices,
  IN MEMORY_INFO_BLOCK_STRUCT   *MemInfoBlockPtr
  )
/*++

Routine Description:

  This function build HOB info from post interface parameters

Arguments:

  PeiServices     -     PeiServices
  MemInfoBlockPtr -     MemInfoBlock pointer

Returns:
  EFI_STATUS - Status code
--*/
{
  EFI_STATUS                          Status;
  UINT32                              Index;
  UINT64                              TopOfMemAddress;
  UINT64                              CurrentBase;
  UINT64                              AvailalbSizeToMemHole;
  UINT32                              NumOfHoles;
  UINT8                               MemInfoHobBuffer[MAX_SIZEOF_AMD_MEMORY_INFO_HOB_BUFFER];
  AMD_MEMORY_INFO_HOB                 *MemInfoHob;
  AMD_MEMORY_RANGE_DESCRIPTOR         *MemRangeDesc;
  UINTN                               SizeOfMemInfoHob;
  UINT32                              MemRangeIndex;
  AMD_MEMORY_INIT_COMPLETE_PPI        *mMemoryInitCompletePpiPtr;
  MEMORY_HOLE_DESCRIPTOR              *HoleMapPtr;
  BOOLEAN                             LastMemRangeAdjusted;
  BOOLEAN                             IsRecoveryMode;
  UINT32                              IndexLeft;
  MEMORY_HOLE_DESCRIPTOR              *HoleMapPtrLeft;
  UINT32                              UmaSizeForRecovery;
  BOOLEAN                             FoundCarveOutRange;
  EFI_BOOT_MODE                       BootMode;
  BOOLEAN                             UmaAbove4GB;


  IDS_HDT_CONSOLE (MAIN_FLOW, "    BuildHobInfo - creating AMD_MEMORY_INFO_HOB\n");

  HoleMapPtr = NULL;
  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryInitCompletePpiGuid,
                                      0,
                                      NULL,
                                      &mMemoryInitCompletePpiPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  Status = mMemoryInitCompletePpiPtr->GetSystemMemoryMap (
    PeiServices,
    &NumOfHoles,
    &TopOfMemAddress,
    &HoleMapPtr
    );
  if (EFI_SUCCESS != Status) {
    return Status;
  }
  if (HoleMapPtr == NULL) {
    return EFI_NOT_FOUND;
  }

  MemInfoHob = (AMD_MEMORY_INFO_HOB *) &MemInfoHobBuffer[0];
  MemRangeDesc = &MemInfoHob->Ranges[0];
  MemInfoHob->Version = AMD_MEMORY_INFO_HOB_VERISION;
  MemRangeIndex = 0;
  CurrentBase = 0;
  Status = EFI_SUCCESS;
  LastMemRangeAdjusted = FALSE;

  Status = PeiServicesGetBootMode (&BootMode);
  IDS_HDT_CONSOLE (MAIN_FLOW, "    BootMode: 0x%02X (%s)\n", BootMode,
                    (BootMode == BOOT_WITH_FULL_CONFIGURATION) ? L"BOOT_WITH_FULL_CONFIGURATION" :
                    (BootMode == BOOT_WITH_MINIMAL_CONFIGURATION) ? L"BOOT_WITH_MINIMAL_CONFIGURATION" :
                    (BootMode == BOOT_ASSUMING_NO_CONFIGURATION_CHANGES) ? L"BOOT_ASSUMING_NO_CONFIGURATION_CHANGES" :
                    (BootMode == BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS) ? L"BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS" :
                    (BootMode == BOOT_WITH_DEFAULT_SETTINGS) ? L"BOOT_WITH_DEFAULT_SETTINGS" :
                    (BootMode == BOOT_WITH_FULL_CONFIGURATION) ? L"BOOT_WITH_FULL_CONFIGURATION" :
                    (BootMode == BOOT_ON_S4_RESUME) ? L"BOOT_ON_S4_RESUME" :
                    (BootMode == BOOT_ON_S5_RESUME) ? L"BOOT_ON_S5_RESUME" :
                    (BootMode == BOOT_ON_S2_RESUME) ? L"BOOT_ON_S2_RESUME" :
                    (BootMode == BOOT_ON_S3_RESUME) ? L"BOOT_ON_S3_RESUME" :
                    (BootMode == BOOT_ON_FLASH_UPDATE) ? L"BOOT_ON_FLASH_UPDATE" :
                    (BootMode == BOOT_IN_RECOVERY_MODE) ? L"BOOT_IN_RECOVERY_MODE" :
                    L"Other boot mode");

  // Override boot mode for testing
  // BootMode = BOOT_WITH_FULL_CONFIGURATION;
  IsRecoveryMode = FALSE || (BootMode == BOOT_IN_RECOVERY_MODE); // Get recovery mode from PPI or PCD ...etc.
  UmaSizeForRecovery = (256 * 1024 * 1024); // 32MB or 256MB
  FoundCarveOutRange = FALSE;

  IDS_HDT_CONSOLE (MAIN_FLOW, "    NumOfHoles: %d\n", NumOfHoles);
  IDS_HDT_CONSOLE (MAIN_FLOW, "    HoleMapPtr: %x\n", HoleMapPtr);
  UmaAbove4GB = FALSE;
  for (Index = 0; Index < NumOfHoles; Index++) {
    IDS_HDT_CONSOLE_MEM_HOLE (Index, HoleMapPtr);
    if ((HoleMapPtr[Index].Type == UMA) && (HoleMapPtr[Index].Base >= FOURGB)) {
      UmaAbove4GB = TRUE;
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "\nMemory Map Info:\n");
  for (Index = 0; Index < NumOfHoles; Index++) {
    AvailalbSizeToMemHole = HoleMapPtr->Base - CurrentBase;
    if (0 != AvailalbSizeToMemHole) {
      if (!LastMemRangeAdjusted) {
        MemRangeDesc[MemRangeIndex].Size =  AvailalbSizeToMemHole;
        MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_AVAILABLE;
        MemRangeDesc[MemRangeIndex].Base = CurrentBase;
        CurrentBase += MemRangeDesc[MemRangeIndex].Size;
      } else {
        // Merge with earlier UMA converted available range again.
        MemRangeIndex--;
        MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_AVAILABLE;
        MemRangeDesc[MemRangeIndex].Size +=  AvailalbSizeToMemHole;
        CurrentBase += AvailalbSizeToMemHole;
        IDS_HDT_CONSOLE (MAIN_FLOW, "    Adjuste Memory Range Index: %d\n", MemRangeIndex);
      }
      IDS_HDT_CONSOLE_MEM_RAGE_DESC (MemRangeIndex, MemRangeDesc);
      IDS_HDT_CONSOLE_MEM_CURRENT_BASE (CurrentBase);
      IDS_HDT_CONSOLE (MAIN_FLOW, "\n");
      MemRangeIndex++;
    }
    LastMemRangeAdjusted = FALSE; // Clear flag after merge available ranges

    // Carve out areas from existing available regions
    if (IsRecoveryMode && !FoundCarveOutRange && (UmaAbove4GB == TRUE)) {
      HoleMapPtrLeft = HoleMapPtr + 1;
      for (IndexLeft = Index + 1; IndexLeft < NumOfHoles; IndexLeft++) {
        if (FOURGB >= CurrentBase + HoleMapPtrLeft->Base + HoleMapPtrLeft->Size + UmaSizeForRecovery) {
          FoundCarveOutRange = FALSE;
        } else {
          FoundCarveOutRange = TRUE;
        }
      }

      if (FoundCarveOutRange) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "    -----------------------------\n");
        IDS_HDT_CONSOLE (MAIN_FLOW, "    Adjust UMA Range Index to: %d\n", MemRangeIndex);
        MemRangeDesc[MemRangeIndex - 1].Size -= UmaSizeForRecovery;
        IDS_HDT_CONSOLE_MEM_RAGE_DESC (MemRangeIndex - 1, MemRangeDesc);
        MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_UMA;
        MemRangeDesc[MemRangeIndex].Base = CurrentBase - UmaSizeForRecovery;
        MemRangeDesc[MemRangeIndex].Size = UmaSizeForRecovery;
        IDS_HDT_CONSOLE_MEM_RAGE_DESC (MemRangeIndex, MemRangeDesc);
        IDS_HDT_CONSOLE (MAIN_FLOW, "    Finished UMA Range\n");
        IDS_HDT_CONSOLE (MAIN_FLOW, "    -----------------------------\n");
        MemRangeIndex++;
      }
    }

    switch (HoleMapPtr->Type) {
    case MMIO:
      MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_MMIO;
      break;

    case PrivilegedDRAM:
      MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_RESERVED;
      break;

    case UMA:
      if ((!FoundCarveOutRange) && (PcdGet8 (PcdCfgIgpuContorl) != 0)) {
        MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_UMA;
      } else {
        // Merge the memory space with previous available region
        ASSERT ((MemRangeDesc[MemRangeIndex - 1].Attribute) == AMD_MEMORY_ATTRIBUTE_AVAILABLE);
        MemRangeIndex--;
        MemRangeDesc[MemRangeIndex].Size +=  HoleMapPtr->Size;
        CurrentBase += HoleMapPtr->Size;
        LastMemRangeAdjusted = TRUE;
      }
      break;

    default:
      // For unknown region, report as reserved
      MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_RESERVED;
      break;
    }

    if (!LastMemRangeAdjusted) {
      MemRangeDesc[MemRangeIndex].Size =  HoleMapPtr->Size;
      ASSERT (0 != MemRangeDesc[MemRangeIndex].Size);
      MemRangeDesc[MemRangeIndex].Base = HoleMapPtr->Base;
      CurrentBase += HoleMapPtr->Size;
    }
    IDS_HDT_CONSOLE_MEM_RAGE_DESC (MemRangeIndex, MemRangeDesc);
    IDS_HDT_CONSOLE_MEM_CURRENT_BASE (CurrentBase);
    IDS_HDT_CONSOLE (MAIN_FLOW, "\n");

    MemRangeIndex++;
    HoleMapPtr++;
  }

  if (CurrentBase < TopOfMemAddress) {
    //
    // MemRangeIndex will be incremented in the previous loop hence dont need to increment here
    //
    MemRangeDesc[MemRangeIndex].Attribute = AMD_MEMORY_ATTRIBUTE_AVAILABLE;
    MemRangeDesc[MemRangeIndex].Base = CurrentBase;
    MemRangeDesc[MemRangeIndex].Size =  TopOfMemAddress - CurrentBase;

    IDS_HDT_CONSOLE_MEM_RAGE_DESC (MemRangeIndex, MemRangeDesc);
    IDS_HDT_CONSOLE (MAIN_FLOW, "\n");
  } else {
    // Since no additional descriptor required to be updated, decrease the
    // incremented number by 1 to ensure we report correct number of descriptor
    MemRangeIndex--;
  }

  MemInfoHob->NumberOfDescriptor = MemRangeIndex + 1;
  SizeOfMemInfoHob = sizeof (AMD_MEMORY_INFO_HOB) + (MemInfoHob->NumberOfDescriptor - 1) * sizeof (AMD_MEMORY_RANGE_DESCRIPTOR);
  IDS_HDT_CONSOLE (MAIN_FLOW, "    NumberOfDescriptor: 0x%x\n", MemInfoHob->NumberOfDescriptor);
  IDS_HDT_CONSOLE (MAIN_FLOW, "    SizeOfMemInfoHob: 0x%x\n", SizeOfMemInfoHob);

  //
  // Update Voltage Information.
  //
  MemInfoHob->AmdMemoryVddioValid = MemInfoBlockPtr->VddioValid;
  MemInfoHob->AmdMemoryVddio = MemInfoBlockPtr->Vddio;
  MemInfoHob->AmdMemoryVddpVddrValid = MemInfoBlockPtr->VddpVddrValid;
  MemInfoHob->AmdMemoryVddpVddr = MemInfoBlockPtr->VddpVddr;
  MemInfoHob->AmdMemoryFrequencyValid = MemInfoBlockPtr->MemFrequencyValid;
  MemInfoHob->AmdMemoryFrequency = MemInfoBlockPtr->MemFrequency;
  MemInfoHob->AmdMemoryDdrMaxRate = MemInfoBlockPtr->DdrMaxRate;

  Status =  EFI_SUCCESS;
  if (BuildGuidDataHob (&gAmdMemoryInfoHobGuid, &MemInfoHobBuffer, SizeOfMemInfoHob) == NULL) {
    Status = EFI_NOT_FOUND;
  }

  return Status;
}

EFI_STATUS
GetMemInfoBlockData (
  IN       CONST EFI_PEI_SERVICES         **PeiServices,
  IN OUT         MEMORY_INFO_BLOCK_STRUCT *MemInfoBlockPtr
  )
/*++ -----------------------------------------------------------------------------
  Routine Description:
    This function will get the APOB Data from APOB HOB

  Arguments:
    MemInfoBlockPtr   - Pointer to the AGESA_PSP_OUTPUT_BLOCK_STRUCT

  Returns:
    EFI_STATUS  - Status code
                  EFI_SUCCESS
 */
{
  EFI_STATUS                     Status;
  AMD_MEMORY_INIT_COMPLETE_PPI   *mMemoryInitCompletePpiPtr;

  Status = (*PeiServices)->LocatePpi (PeiServices,
                                      &gAmdMemoryInitCompletePpiGuid,
                                      0,
                                      NULL,
                                      &mMemoryInitCompletePpiPtr);
  if (EFI_SUCCESS != Status) {
    return Status;
  }


  MemInfoBlockPtr->MemFrequencyValid = TRUE;
  MemInfoBlockPtr->MemFrequency = mMemoryInitCompletePpiPtr->AmdMemoryFrequency;

  MemInfoBlockPtr->VddioValid = TRUE;
  MemInfoBlockPtr->Vddio = (UINT16) mMemoryInitCompletePpiPtr->AmdMemoryVddIo;

  MemInfoBlockPtr->VddpVddrValid = mMemoryInitCompletePpiPtr->AmdMemoryVddpVddr.IsValid;
  MemInfoBlockPtr->VddpVddr = mMemoryInitCompletePpiPtr->AmdMemoryVddpVddr.Voltage;
  MemInfoBlockPtr->DdrMaxRate = mMemoryInitCompletePpiPtr->DdrMaxRate;

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
InitializeAmdMemoryInfoHobPeim (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
/*++

Routine Description:

  Initialization Entry Point for AmdMemoryHobInfo PEIM

Arguments:
  FileHandle -  FileHandle
  PeiServices - PeiServices

Returns:
  EFI_STATUS  - Status code
                EFI_SUCCESS

--*/
{
  EFI_STATUS                 Status;
  MEMORY_INFO_BLOCK_STRUCT   MemInfoBlock;
  //UINT32  NumofEntry;
  //APOB_TYPE_HEADER *ApobEntries;

  //NumofEntry = 0;

  // Retrieve DIMM Smbus info log
  //Status = AmdPspGetApobEntryFromHob(APOB_MEM, APOB_MEM_DIMM_SMBUS_INFO_TYPE, &NumofEntry, &ApobEntries);
  //if (Status == EFI_SUCCESS) {
  //  BuildGuidDataHob (&gAmdMemoryDimmSmbusInfoHobGuid, ((UINT8 *) ApobEntries + sizeof (APOB_TYPE_HEADER)), (ApobEntries->TypeSize - sizeof (APOB_TYPE_HEADER)));
  //}

  //
  // Get Memory Info Block Data
  //
  Status = GetMemInfoBlockData (PeiServices, &MemInfoBlock);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  //
  // Build Memory Info Hob
  //
  Status = BuildHobInfo (PeiServices, &MemInfoBlock);

  if (Status == EFI_SUCCESS) {
    Status = (**PeiServices).InstallPpi (PeiServices, &mAmdMemoryHobInfoAvailblePpiList);
  }
  return Status;
}

