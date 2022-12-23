/* $NoKeywords:$ */
/**
 * @file
 *
 *
 * AMD Register Table Related Functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include <Filecode.h>
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdRegisterLib.h>
#include <Library/GnbLib.h>
#include <Library/AmdTableLib.h>
#include <Library/CcxRolesLib.h>
#include <Library/BaseCoreLogicalIdLib.h>
#include <Library/PciLib.h>

#define FILECODE LIBRARY_AMDTABLELIB_AMDTABLELIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
F_DO_TABLE_ENTRY *DoTableEntry[TableEntryTypeMax] = {
  SetPciEntry,
  SetPciProfileFixupEntry,
  SetPciCpuRevEntry,
  SetMsrEntry,
  SetMsrCpuRevEntry,
  SetMsrCoreRevEntry,
  SetMsrPlatformFeatEntry,
  SetMsrCpuRevPlatformFeatEntry,
  SetSmnEntry,
  SetSmnMultiEntry,
  SetSmuIndexEntry,
  SetSmuIndexProfileFixupEntry,
  CopyBitFieldEntry
};

PLATFORM_FEATS mPlatformFeats;
BOOLEAN mPlatformFeatsInited = FALSE;
SOC_LOGICAL_ID  mLogicalCpuid;
BOOLEAN mLogicalCpuidInited = FALSE;
CORE_LOGICAL_ID  mLogicalCoreid;
BOOLEAN mLogicalCoreidInited = FALSE;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * An iterator for all the Family and Model Register Tables.
 *
 * RegisterTableHandle should be set to NULL to begin iteration, the first time the method is
 * invoked.  Register tables can be processed, until this method returns NULL.  RegisterTableHandle
 * should simply be passed back to the method without modification or use by the caller.
 * The table selector allows the relevant tables for different cores to be iterated, if the family separates
 * tables.  For example, MSRs can be in a table processed by all cores and PCI registers in a table processed by
 * primary cores.
 *
 * @param[in]     Selector                Select whether to iterate over tables for either all cores, primary cores, bsp, ....
 * @param[in]     RegisterTableList       Register table list
 * @param[in,out] RegisterTableHandle     IN: The handle of the current register table, or NULL if Begin.
 *                                        OUT: The handle of the next register table, if not End.
 * @param[in]     StdHeader               Handle of Header for calling lib functions and services.
 *
 * @return        The pointer to the next Register Table, or NULL if End.
 */
REGISTER_TABLE
**GetNextRegisterTable (
  IN       UINT32                  Selector,
  IN       REGISTER_TABLE        **RegisterTableList,
  IN OUT   REGISTER_TABLE       ***RegisterTableHandle,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  REGISTER_TABLE **NextTable;

  ASSERT (StdHeader != NULL);
  ASSERT (Selector < TableCoreSelectorMax);

  NextTable = *RegisterTableHandle;
  if (NextTable == NULL) {
    // Begin
    NextTable = RegisterTableList;
    ///@todo    IDS_OPTION_HOOK (IDS_TRAP_TABLE, &NextTable, StdHeader);
  } else {
    NextTable++;
  }
  // skip if not selected
  while ((*NextTable != NULL) && (((*NextTable)->Selector != Selector))) {
    NextTable++;
  }
  if (*NextTable == NULL) {
    // End
    *RegisterTableHandle = NULL;
  } else {
    // Iterate next table
    *RegisterTableHandle = NextTable;
  }
  return NextTable;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the PCI Register Entry.
 *
 * @TableEntryTypeMethod{::PciRegister}.
 *
 * Make the current core's PCI address with the function and register for the entry.
 * Read - Modify - Write the PCI register, clearing masked bits, and setting the data bits.
 *
 * @param[in]     Entry             The PCI register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetPciEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32               PciRegData;
  PCI_TYPE_ENTRY_DATA *PciEntry;

  PciEntry = (PCI_TYPE_ENTRY_DATA *) (*Entry);
  // "Mask nothing" is a bug, even if just by policy.
  ASSERT (PciEntry->Mask != 0);

  ///@todo  IDS_OPTION_HOOK (IDS_SET_PCI_REGISTER_ENTRY, PciEntry, StdHeader);

  PciRegData = PciRead32 (PciEntry->Address.AddressValue);
  PciRegData = PciRegData & (~(PciEntry->Mask));
  PciRegData = PciRegData | PciEntry->Data;
  PciWrite32 (PciEntry->Address.AddressValue, PciRegData);
  // Entry MUST point to next register entry
  (*((PCI_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Performance Profile PCI Register Entry.
 *
 * @TableEntryTypeMethod{::PciProfileFixup}.
 *
 * Check the entry's performance profile features to the platform's and do the
 * PCI register entry if they match.
 *
 * @param[in]     Entry             The Performance Profile register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetPciProfileFixupEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  PROFILE_FEATS      PlatformProfile;
  PCI_PROFILE_FIXUP_TYPE_ENTRY_DATA *ProfileFixupEntry;
  PCI_TYPE_ENTRY_DATA           *PciEntry;

  ProfileFixupEntry = (PCI_PROFILE_FIXUP_TYPE_ENTRY_DATA *) (*Entry);
  // Errors:  Possible values in unused entry space, extra type features, value range checks.
  // Check that the entry type is correct and the actual supplied entry data is appropriate for that entry.
  ASSERT ((ProfileFixupEntry->TypeFeats.ProfileValue & ~((PERFORMANCE_PROFILE_ALL) | (PERFORMANCE_AND))) == 0);

  GetPerformanceFeatures (&PlatformProfile, StdHeader);

  if (DoesEntryTypeSpecificInfoMatch (PlatformProfile.ProfileValue,
                                      ProfileFixupEntry->TypeFeats.ProfileValue)) {
    PciEntry = &ProfileFixupEntry->PciEntry;
    SetPciEntry ((UINT8 **) &PciEntry, StdHeader);
  }
  // Entry MUST point to next register entry
  (*((PCI_PROFILE_FIXUP_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Processor Revision Dependent PCI Register Entry.
 *
 * @TableEntryTypeMethod{::PciCpuRev}.
 *
 * Read - Modify - Write the PCI register, clearing masked bits, and setting the data bits,
 * if the current core's revision matches the revision specified in the entry.
 *
 * @param[in]     Entry             The PCI register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetPciCpuRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32          PciRegData;
  SOC_LOGICAL_ID  LogicalCpuid;
  PCI_CPU_REV_TYPE_ENTRY_DATA *CpuRevPciEntry;

  CpuRevPciEntry = (PCI_CPU_REV_TYPE_ENTRY_DATA *) (*Entry);
  ASSERT (CpuRevPciEntry->Mask != 0);

  if (!mLogicalCpuidInited) {
    BaseGetLogicalIdOnExecutingCore (&LogicalCpuid);
    mLogicalCpuidInited = TRUE;
    mLogicalCpuid = LogicalCpuid;
  } else {
    LogicalCpuid = mLogicalCpuid;
  }

  if (((LogicalCpuid.Family & CpuRevPciEntry->CpuRevision.Family) != 0) &&
      ((LogicalCpuid.Revision & CpuRevPciEntry->CpuRevision.Revision) != 0)) {
    PciRegData = PciRead32 (CpuRevPciEntry->Address.AddressValue);
    PciRegData = PciRegData & (~(CpuRevPciEntry->Mask));
    PciRegData = PciRegData | CpuRevPciEntry->Data;
    PciWrite32 (CpuRevPciEntry->Address.AddressValue, PciRegData);
  }
  // Entry MUST point to next register entry
  (*((PCI_CPU_REV_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the MSR Register Entry.
 *
 * @TableEntryTypeMethod{::MsrRegister}.
 *
 * Read - Modify - Write the MSR, clearing masked bits, and setting the data bits.
 *
 * @param[in]     Entry             The MSR register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetMsrEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  MSR_TYPE_ENTRY_DATA *MsrEntry;

  MsrEntry = (MSR_TYPE_ENTRY_DATA *) (*Entry);
  // Even for only single bit fields, use those in the mask.  "Mask nothing" is a bug, even if just by policy.
  ASSERT (MsrEntry->Mask != 0);

  AsmMsrAndThenOr64 (MsrEntry->Address, ~(MsrEntry->Mask), MsrEntry->Data);
  // Entry MUST point to next register entry
  (*((MSR_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Processor Revision Dependent MSR Entry.
 *
 * @TableEntryTypeMethod{::MsrCpuRev}.
 *
 * Read - Modify - Write the MSR, clearing masked bits, and setting the data bits,
 * if the current core's revision matches the revision specified in the entry.
 *
 * @param[in]     Entry             The MSR entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetMsrCpuRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  MSR_CPU_REV_TYPE_ENTRY_DATA *CpuRevMsrEntry;
  MSR_TYPE_ENTRY_DATA         *MsrEntry;
  SOC_LOGICAL_ID               LogicalCpuid;

  CpuRevMsrEntry = (MSR_CPU_REV_TYPE_ENTRY_DATA *) (*Entry);
  MsrEntry = &CpuRevMsrEntry->MsrEntry;
  ASSERT (MsrEntry->Mask != 0);

  if (!mLogicalCpuidInited) {
    BaseGetLogicalIdOnExecutingCore (&LogicalCpuid);
    mLogicalCpuidInited = TRUE;
    mLogicalCpuid = LogicalCpuid;
  } else {
    LogicalCpuid = mLogicalCpuid;
  }

  if (((LogicalCpuid.Family & CpuRevMsrEntry->CpuRevision.Family) != 0) &&
      ((LogicalCpuid.Revision & CpuRevMsrEntry->CpuRevision.Revision) != 0)) {
    SetMsrEntry ((UINT8 **) &MsrEntry, StdHeader);
  }
  // Entry MUST point to next register entry
  (*((MSR_CPU_REV_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the CPU silicon Revision Dependent MSR Entry.
 *
 * @TableEntryTypeMethod{::MsrCoreRev}.
 *
 * Read - Modify - Write the MSR, clearing masked bits, and setting the data bits,
 * if the current core's revision matches the revision specified in the entry.
 *
 * @param[in]     Entry             The MSR entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetMsrCoreRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  MSR_CORE_REV_TYPE_ENTRY_DATA *CoreRevMsrEntry;
  MSR_TYPE_ENTRY_DATA          *MsrEntry;
  CORE_LOGICAL_ID               CoreLogicalid;

  CoreRevMsrEntry = (MSR_CORE_REV_TYPE_ENTRY_DATA *) (*Entry);
  MsrEntry = &CoreRevMsrEntry->MsrEntry;
  ASSERT (MsrEntry->Mask != 0);

  if (!mLogicalCoreidInited) {
    BaseGetCoreLogicalIdOnExecutingCore (&CoreLogicalid);
    mLogicalCoreidInited = TRUE;
    mLogicalCoreid = CoreLogicalid;
  } else {
    CoreLogicalid = mLogicalCoreid;
  }

  if (((CoreLogicalid.CoreFamily & CoreRevMsrEntry->CoreRevision.CoreFamily) != 0) &&
      ((CoreLogicalid.CoreRevision & CoreRevMsrEntry->CoreRevision.CoreRevision) != 0)) {
    SetMsrEntry ((UINT8 **) &MsrEntry, StdHeader);
  }
  // Entry MUST point to next register entry
  (*((MSR_CORE_REV_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Platform Feature Dependent MSR Entry.
 *
 * @TableEntryTypeMethod{::MsrPlatformFeat}.
 *
 * Read - Modify - Write the MSR, clearing masked bits, and setting the data bits,
 * if the current core's platform features matches the features specified in the entry.
 *
 * @param[in]     Entry             The MSR entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetMsrPlatformFeatEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  PLATFORM_FEATS                PlatformFeatures;
  MSR_PLATFORM_FEAT_ENTRY_DATA *PlatformFeatEntry;
  MSR_TYPE_ENTRY_DATA          *MsrEntry;

  PlatformFeatEntry = (MSR_PLATFORM_FEAT_ENTRY_DATA *) (*Entry);

  ASSERT ((PlatformFeatEntry->TypeFeats.PlatformValue & ~((AMD_PF_ALL) | (AMD_PF_AND))) == 0);

  GetPlatformFeatures (&PlatformFeatures, StdHeader);

  if (DoesEntryTypeSpecificInfoMatch (PlatformFeatures.PlatformValue,
                                      PlatformFeatEntry->TypeFeats.PlatformValue)) {
    MsrEntry = &PlatformFeatEntry->MsrEntry;
    SetMsrEntry ((UINT8 **) &MsrEntry, StdHeader);
  }
  // Entry MUST point to next register entry
  (*((MSR_PLATFORM_FEAT_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Cpu Rev & Platform Feature Dependent MSR Entry.
 *
 * @TableEntryTypeMethod{::MsrCpuRevPlatformFeat}.
 *
 * Read - Modify - Write the MSR, clearing masked bits, and setting the data bits,
 * if the current core's revision matches the revision specified & current core's
 * platform features matches the features specified in the entry.
 *
 * @param[in]     Entry             The MSR entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetMsrCpuRevPlatformFeatEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  PLATFORM_FEATS                PlatformFeatures;
  MSR_CPU_REV_PLATFORM_FEAT_ENTRY_DATA *CpuRevPlatformFeatEntry;
  MSR_TYPE_ENTRY_DATA          *MsrEntry;
  SOC_LOGICAL_ID                LogicalCpuid;

  CpuRevPlatformFeatEntry = (MSR_CPU_REV_PLATFORM_FEAT_ENTRY_DATA *) (*Entry);

  ASSERT ((CpuRevPlatformFeatEntry->TypeFeats.PlatformValue & ~((AMD_PF_ALL) | (AMD_PF_AND))) == 0);

  if (!mLogicalCpuidInited) {
    BaseGetLogicalIdOnExecutingCore (&LogicalCpuid);
    mLogicalCpuidInited = TRUE;
    mLogicalCpuid = LogicalCpuid;
  } else {
    LogicalCpuid = mLogicalCpuid;
  }

  // Check CPU Rev match
  if (((LogicalCpuid.Family & CpuRevPlatformFeatEntry->CpuRevision.Family) != 0) &&
      ((LogicalCpuid.Revision & CpuRevPlatformFeatEntry->CpuRevision.Revision) != 0)) {
    // Get platform features
    GetPlatformFeatures (&PlatformFeatures, StdHeader);
    // Check platform features match
    if (DoesEntryTypeSpecificInfoMatch (PlatformFeatures.PlatformValue,
                                        CpuRevPlatformFeatEntry->TypeFeats.PlatformValue)) {
      MsrEntry = &CpuRevPlatformFeatEntry->MsrEntry;
      SetMsrEntry ((UINT8 **) &MsrEntry, StdHeader);
    }
  }

  // Entry MUST point to next register entry
  (*((MSR_CPU_REV_PLATFORM_FEAT_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the SMN Register Entry.
 *
 * @TableEntryTypeMethod{::SmnRegisters}.
 *
 * Read - Modify - Write the SMN register, clearing masked bits, and setting the data bits.
 *
 * See if you can use the other entries or make an entry that covers the fix.
 * After all, the purpose of having a table entry is to @b NOT have code which
 * isn't generic feature code, but is family/model code specific to one case.
 *
 * @param[in]     Entry             The SMN Data entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetSmnEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  SMN_TYPE_ENTRY_DATA *SmnEntry;

  if (CcxIsBsp (NULL)) {
    SmnEntry = (SMN_TYPE_ENTRY_DATA *) (*Entry);
    // Even for only single bit fields, use those in the mask.  "Mask nothing" is a bug, even if just by policy.
    ASSERT (SmnEntry->Mask != 0);

    SetSmnEntryLib (SmnEntry->InstanceId, SmnEntry->RegisterIndex, ~(SmnEntry->Mask), SmnEntry->Data);
  }

  // Entry MUST point to next register entry
  (*((SMN_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the SMN Multi Registers Entry.
 *
 * @TableEntryTypeMethod{::SmnMultiRegisters}.
 *
 * Read - Modify - Write the SMN register, clearing masked bits, and setting the data bits.
 *
 * See if you can use the other entries or make an entry that covers the fix.
 * After all, the purpose of having a table entry is to @b NOT have code which
 * isn't generic feature code, but is family/model code specific to one case.
 *
 * @param[in]     Entry             The SMN Data entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetSmnMultiEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32                     InstanceId;
  UINT32                     RegisterIndex;
  UINT32                     AndValue;
  UINT32                     OrValue;
  SMN_MULTI_TYPE_ENTRY_DATA *SmnMultiEntry;

  if (CcxIsBsp (NULL)) {
    SmnMultiEntry = (SMN_MULTI_TYPE_ENTRY_DATA *) (*Entry);
    // Even for only single bit fields, use those in the mask.  "Mask nothing" is a bug, even if just by policy.
    ASSERT (SmnMultiEntry->Mask != 0);

    InstanceId = SmnMultiEntry->InstanceId;
    AndValue = ~(SmnMultiEntry->Mask);
    OrValue = SmnMultiEntry->Data;
    for (RegisterIndex = SmnMultiEntry->RegisterIndexStart; RegisterIndex <= SmnMultiEntry->RegisterIndexEnd; RegisterIndex += SmnMultiEntry->Steps) {
      SetSmnEntryLib (InstanceId, RegisterIndex, AndValue, OrValue);
    }
  }

  // Entry MUST point to next register entry
  (*((SMN_MULTI_TYPE_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the SMU Index/Data Register Entry.
 *
 * @TableEntryTypeMethod{::SmuIndexRegister}.
 *
 * Read - Modify - Write the SMU Index/Data register, clearing masked bits, and setting the data bits.
 *
 * See if you can use the other entries or make an entry that covers the fix.
 * After all, the purpose of having a table entry is to @b NOT have code which
 * isn't generic feature code, but is family/model code specific to one case.
 *
 * @param[in]     Entry             The SMU Index Data entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetSmuIndexEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32               SmuIndexRegister;
  SMU_INDEX_ENTRY_DATA *SmuIndexEntry;

  SmuIndexEntry = (SMU_INDEX_ENTRY_DATA *) (*Entry);
  // "Mask nothing" is a bug, even if just by policy.
  ASSERT (SmuIndexEntry->Mask != 0);

  // Software must wait for 0xD8230000[31][SVIBUSY] to clear to 0 before writing any of the following fields
  if ((SmuIndexEntry->Index == 0xD8230000) || (SmuIndexEntry->Index == 0xD8230004) || (SmuIndexEntry->Index == 0xD823000C)) {
    do {
      GnbLibPciIndirectRead (SMU_INDEX_ADDRESS, 0xD8230000, AccessWidth32, &SmuIndexRegister, StdHeader);
    } while ((SmuIndexRegister & BIT31) != 0);
  }

  GnbLibPciIndirectRead (SMU_INDEX_ADDRESS, SmuIndexEntry->Index, AccessWidth32, &SmuIndexRegister, StdHeader);
  SmuIndexRegister = SmuIndexRegister & (~(SmuIndexEntry->Mask));
  SmuIndexRegister = SmuIndexRegister | SmuIndexEntry->Data;
  GnbLibPciIndirectWrite (SMU_INDEX_ADDRESS, SmuIndexEntry->Index, AccessWidth32, &SmuIndexRegister, StdHeader);
  // Entry MUST point to next register entry
  (*((SMU_INDEX_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Performance Profile SMU Index/Data Register Entry.
 *
 * @TableEntryTypeMethod{::SmuIndexProfileFixup}.
 *
 * Check the entry's performance profile features to the platform's and do the
 * SMU Index/Data register entry if they match.
 *
 * @param[in]     Entry             The Performance Profile register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
SetSmuIndexProfileFixupEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  PROFILE_FEATS          PlatformProfile;
  SMU_INDEX_ENTRY_DATA               *SmuIndexEntry;
  SMU_INDEX_PROFILE_FIXUP_ENTRY_DATA *ProfileFixupSmuIndexEntry;

  ProfileFixupSmuIndexEntry = (SMU_INDEX_PROFILE_FIXUP_ENTRY_DATA *) (*Entry);
  // Errors:  Possible values in unused entry space, extra type features, value range checks.
  // Check that the entry type is correct and the actual supplied entry data is appropriate for that entry.
  ASSERT ((ProfileFixupSmuIndexEntry->TypeFeats.ProfileValue & ~((PERFORMANCE_PROFILE_ALL) | (PERFORMANCE_AND))) == 0);

  GetPerformanceFeatures (&PlatformProfile, StdHeader);
  if (DoesEntryTypeSpecificInfoMatch (PlatformProfile.ProfileValue,
                                      ProfileFixupSmuIndexEntry->TypeFeats.ProfileValue)) {
    SmuIndexEntry = &(ProfileFixupSmuIndexEntry->SmuIndexEntry);
    SetSmuIndexEntry ((UINT8 **) &SmuIndexEntry, StdHeader);
  }
  // Entry MUST point to next register entry
  (*((SMU_INDEX_PROFILE_FIXUP_ENTRY_DATA **)Entry))++;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Perform the Copy Bitfield Entry.
 *
 * @TableEntryTypeMethod{::CopyBitField}.
 *
 * Copy bitfield from register A to register B
 *
 * @param[in]     Entry             The Performance Profile register entry to perform
 * @param[in]     StdHeader         Config handle for library and services.
 *
 */
VOID
CopyBitFieldEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT8                    *DestEntry;
  UINT64                    SourceData;
  UINT64                    SourceMask;
  UINT64                    DestData;
  UINT64                    DestMask;
  UINTN                     PciAddress;
  TABLE_ENTRY_DATA          DestEntryStruct;
  COPY_BIT_FIELD_DESCRIPTION *Source;
  COPY_BIT_FIELD_DESCRIPTION *Destination;

  Source = &(((COPY_BIT_FIELD_ENTRY_DATA *) (*Entry))->Source);
  Destination = &(((COPY_BIT_FIELD_ENTRY_DATA *) (*Entry))->Destination);
  // Get source data
  switch (Source->RegType) {
  case MsrRegister:
    SourceData = AsmReadMsr64 (Source->Address);
    break;
  case PciRegister:
    PciAddress = Source->Address;
    SourceData = PciRead32 (PciAddress);
    break;
  case SmuIndexRegister:
    GnbLibPciIndirectRead (SMU_INDEX_ADDRESS, Source->Address, AccessWidth32, &SourceData, StdHeader);
    break;
  default:
    ASSERT (FALSE);
    return;
  }

  // Check MSB, LSB, and get SourceMask, SourceData
  if (Source->MSB >= Source->LSB) {
    SourceMask = LShiftU64 (1, (Source->MSB - Source->LSB + 1)) - 1;
    SourceData  = RShiftU64 (SourceData, Source->LSB) & SourceMask;
  } else {
    // The input MSB LSB are wrong. exchange them
    ASSERT (FALSE);
    SourceMask = LShiftU64 (1, (Source->LSB - Source->MSB + 1)) - 1;
    SourceData  = RShiftU64 (SourceData, Source->MSB) & SourceMask;
  }

  // Check MSB, LSB, and get DestMask, DestData
  if (Destination->MSB >= Destination->LSB) {
    DestMask = LShiftU64 (1, (Destination->MSB - Destination->LSB + 1)) - 1;
    DestMask = LShiftU64 (DestMask, Destination->LSB);
    DestData = LShiftU64 (SourceData, Destination->LSB);
  } else {
    // The input MSB LSB are wrong. exchange them
    ASSERT (FALSE);
    DestMask = LShiftU64 (1, (Destination->LSB - Destination->MSB + 1)) - 1;
    DestMask = LShiftU64 (DestMask, Destination->MSB);
    DestData = LShiftU64 (SourceData, Destination->MSB);
  }
  if (SourceMask > DestMask) {
    ASSERT (FALSE);
    return;
  }

  // Set destination data
  switch (Destination->RegType) {
  case MsrRegister:
    DestEntryStruct.MsrEntry.Address = Destination->Address;
    DestEntryStruct.MsrEntry.Data = DestData;
    DestEntryStruct.MsrEntry.Mask = DestMask;
    break;
  case PciRegister:
    DestEntryStruct.PciEntry.Address.AddressValue = Destination->Address;
    DestEntryStruct.PciEntry.Data = (UINT32) DestData;
    DestEntryStruct.PciEntry.Mask = (UINT32) DestMask;
    break;
  case SmuIndexRegister:
    DestEntryStruct.SmuIndexEntry.Index = Destination->Address;
    DestEntryStruct.SmuIndexEntry.Data = (UINT32) DestData;
    DestEntryStruct.SmuIndexEntry.Mask = (UINT32) DestMask;
    break;
  default:
    ASSERT (FALSE);
    return;
  }
  DestEntry = (UINT8 *) &DestEntryStruct;

  DoTableEntry[Destination->RegType] ((UINT8 **) &DestEntry, StdHeader);
  // Entry MUST point to next register entry
  (*((COPY_BIT_FIELD_ENTRY_DATA **)Entry))++;
}

/* -----------------------------------------------------------------------------*/
/**
 * Returns the platform features list of the currently running processor core.
 *
 * @param[out]      Features          The Features supported by this platform
 * @param[in]       StdHeader         Header for library and services
 *
 */
VOID
GetPlatformFeatures (
     OUT   PLATFORM_FEATS         *Features,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32 PackageType;
  PLATFORM_FEATS PlatformFeats;

  if (!mPlatformFeatsInited) {
    PlatformFeats.PlatformValue = 0;

    // bit 0 - PlatformAm4: AM4 package
    PackageType = LibAmdGetPackageType (StdHeader);
    if (PackageType == PACKAGE_TYPE_AM4) {
      PlatformFeats.PlatformFeatures.PlatformAm4 = 1;
    }

    // bit 1 - PlatformX2Apic: x2APIC mode desired
    if (PcdGetBool (PcdAmdX2ApicMode)) {
      PlatformFeats.PlatformFeatures.PlatformX2Apic = 1;
    } else {
      PlatformFeats.PlatformFeatures.PlatformApic = 1;
    }

    mPlatformFeatsInited = TRUE;
    mPlatformFeats.PlatformValue = PlatformFeats.PlatformValue;
    Features->PlatformValue = PlatformFeats.PlatformValue;
  } else {
    Features->PlatformValue = mPlatformFeats.PlatformValue;
  }
}

/*-------------------------------------------------------------------------------------*/
/**
 * Returns the performance profile features list of the currently running processor core.
 *
 * @param[out]      Features          The performance profile features supported by this platform
 * @param[in]       StdHeader         Header for library and services
 *
 */
VOID
GetPerformanceFeatures (
     OUT   PROFILE_FEATS      *Features,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  ///@todo
  // Start with none.
  Features->ProfileValue = 0;

}

/*---------------------------------------------------------------------------------------*/
/**
 * Checks register table entry type specific criteria to the platform.
 *
 * Entry Data Type implementer methods can use this generically to check their own
 * specific criteria.  The method collects the actual platform characteristics and
 * provides them along with the table entry's criteria to this service.
 *
 * There are a couple considerations for any implementer method using this service.
 * The criteria value has to be representable as a UINT32.  The MSB, Bit 31, has to
 * be used as a AND test request if set in the entry.  (The platform value should never
 * have that bit set.)
 *
 * @param[in]     PlatformTypeSpecificFeatures        The platform features
 * @param[in]     EntryTypeFeatures                   The entry's desired platform features
 *
 * @retval        TRUE                                This entry should be applied
 * @retval        FALSE                               This entry does not apply
 *
 */
BOOLEAN
DoesEntryTypeSpecificInfoMatch (
  IN       UINT32   PlatformTypeSpecificFeatures,
  IN       UINT32   EntryTypeFeatures
  )
{
  BOOLEAN Result;

  Result = FALSE;

  if ((EntryTypeFeatures & BIT31) == 0) {
    // Match if ANY entry feats match a platform feat (an OR test)
    if ((EntryTypeFeatures & PlatformTypeSpecificFeatures) != 0) {
      Result = TRUE;
    }
  } else {
    // Match if ALL entry feats match a platform feat (an AND test)
    if ((EntryTypeFeatures & ~(BIT31)) == (EntryTypeFeatures & PlatformTypeSpecificFeatures)) {
      Result = TRUE;
    }
  }
  return Result;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Determine this core's Selector matches.
 *
 * @param[in]  Selector    The selector type for the table.
 * @param[in]  StdHeader   Config handle for library and services.
 *
 * @retval  TRUE           The current core matches the selector type
 * @retval  FALSE          The current core does not match the selector type
 */
BOOLEAN
IsCoreSelector (
  IN       UINT32                    Selector,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  BOOLEAN Result;

  Result = TRUE;
  ASSERT (Selector < TableCoreSelectorMax);

  if ((Selector == PrimaryCores) && !CcxIsSocketPrimary (StdHeader)) {
    Result = FALSE;
  }
  if ((Selector == DiePrimary) && !CcxIsDiePrimary (StdHeader)) {
    Result = FALSE;
  }
  if ((Selector == ComplexPrimary) && !CcxIsComplexPrimary (StdHeader)) {
    Result = FALSE;
  }
  if ((Selector == ComputeUnitPrimary) && !CcxIsComputeUnitPrimary (StdHeader)) {
    Result = FALSE;
  }
  if ((Selector == BscCore) && (!CcxIsBsp (StdHeader))) {
    Result = FALSE;
  }
  return Result;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set the registers for this core based on entries in a list of Register Tables.
 *
 * Determine the platform features and this core's logical id.  Get the specific table
 * entry type implementations for the logical model, which may be either generic (the ones
 * in this file) or specific.
 *
 * Scan the tables starting the with ones for all cores and progressively narrowing the selection
 * based on this core's role (ex. primary core).  For a selected table, check for each entry
 * matching the current core and platform, and call the implementer method to perform the
 * register set operation if it matches.
 *
 * @param[in]  RegisterEntry               RegisterEntry
 * @param[in]  StdHeader                   Config handle for library and services.
 *
 */
VOID
SetRegistersFromTable (
  IN       UINT8                  *RegisterEntry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  TABLE_ENTRY_FIELDS    *Entries;
  TABLE_ENTRY_DATA      *EntryData;
  UINT16                 EntryType;

  // Entries Format:
  //
  // 0: UINT16          EntryType
  //    VariableLength  EntryData
  // 1: UINT16          EntryType
  //    VariableLength  EntryData
  // ...
  // ...
  Entries = (TABLE_ENTRY_FIELDS *) RegisterEntry;                    // Get the first entry
  EntryType = Entries->EntryType;                                    // Get EntryType
  EntryData = &(Entries->EntryData);                                 // Get EntryData block
  while (EntryType != TableTerminator) {
    if (EntryType < TableEntryTypeMax) {
      // EntryData will be added with correct size by DoTableEntry ()
      // After that, it points to the next entry
      DoTableEntry[EntryType] ((UINT8 **) &EntryData, StdHeader);
      Entries = (TABLE_ENTRY_FIELDS *) EntryData;                    // Get the next entry
      EntryType = Entries->EntryType;                                // Get EntryType
      EntryData = &(Entries->EntryData);                             // Get EntryData
    } else {
      ASSERT (FALSE);
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set the registers for this core based on entries in a list of Register Tables.
 *
 * Determine the platform features and this core's logical id.  Get the specific table
 * entry type implementations for the logical model, which may be either generic (the ones
 * in this file) or specific.
 *
 * Scan the tables starting the with ones for all cores and progressively narrowing the selection
 * based on this core's role (ex. primary core).  For a selected table, check for each entry
 * matching the current core and platform, and call the implementer method to perform the
 * register set operation if it matches.
 *
 * @param[in]  RegisterTableList RegisterTableList
 * @param[in]  StdHeader         Config handle for library and services.
 *
 */
VOID
SetRegistersFromTableList (
  IN       REGISTER_TABLE         **RegisterTableList,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  TABLE_CORE_SELECTOR    Selector;
  REGISTER_TABLE       **TableHandle;
  REGISTER_TABLE       **RegisterTable;

  for (Selector = AllCores; Selector < TableCoreSelectorMax; Selector++) {
    if (IsCoreSelector (Selector, StdHeader)) {
      // If the current core is the selected type of core, work the table list for tables for that type of core.
      TableHandle = NULL;
      RegisterTable = GetNextRegisterTable (Selector, RegisterTableList, &TableHandle, StdHeader);
      while (*RegisterTable != NULL) {
        SetRegistersFromTable ((UINT8 *) ((*RegisterTable)->Table), StdHeader);
        RegisterTable = GetNextRegisterTable (Selector, RegisterTableList, &TableHandle, StdHeader);
      }
    } else {
      // Once a selector does not match the current core, quit looking.
      break;
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set the registers for this core based on entries in a list of Register Tables.
 *
 * This function acts as a wrapper for calling the SetRegistersFromTable.
 *
 *  @param[in]   RegTableListAtGivenTP Points to the register table list at the given time point.
 *  @param[in]   StdHeader             Config handle for library and services.
 *  @param[in]   TimePoint             Point in time of execution.
 *
 *  @retval      AGESA_SUCCESS         Register table successfully loaded
 *  @retval      AGESA_UNSUPPORTED     Register table is not supported
 */
AGESA_STATUS
SetRegistersFromTablesAtGivenTimePoint (
  IN       REGISTER_TABLE_AT_GIVEN_TP *RegTableListAtGivenTP,
  IN       REGISTER_TABLE_TIME_POINT  TimePoint,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  REGISTER_TABLE            **RegisterTableList;
  AGESA_STATUS                Status;

  if (TimePoint >= MaxAmdRegisterTableTps) {
    ASSERT (FALSE);
    return AGESA_BOUNDS_CHK;
  }

  RegisterTableList = NULL;
  while (RegTableListAtGivenTP->TimePoint != MaxAmdRegisterTableTps) {
    if (RegTableListAtGivenTP->TimePoint == TimePoint) {
      RegisterTableList = (REGISTER_TABLE **) RegTableListAtGivenTP->TableList;
      break;
    }
    RegTableListAtGivenTP++;
  }
  if (RegisterTableList != NULL) {
    SetRegistersFromTableList (RegisterTableList, StdHeader);
    Status = AGESA_SUCCESS;
  } else {
    Status = AGESA_UNSUPPORTED;
  }
  return Status;
}


