/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to initialize Integrated Info Table
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312286 $   @e \$Date: 2015-02-04 14:11:11 +0800 (Wed, 04 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbFuseTable.h"
#include  "GnbPcie.h"
#include  "GnbGfx.h"
#include  "GnbGfxFamServices.h"
#include  "GnbCommonLib.h"
#include  "GfxPwrPlayTableV5.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBGFXINTTABLEV5_GFXPWRPLAYTABLEV5_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
GfxIntDebugDumpPpTable (
  IN       ATOM_PPLIB_POWERPLAYTABLE5   *PpTable,
  IN       GFX_PLATFORM_CONFIG          *Gfx
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Create new software state
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @retval                           Pointer to state entry in SW state array
 */

SW_STATE *
GfxPwrPlayCreateSwState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINTN Index;
  for (Index = 0; Index < MAX_NUM_OF_SW_STATES; Index++) {
    if (PpWorkspace->SwStateArray[Index].Valid == FALSE) {
      PpWorkspace->SwStateArray[Index].Valid = TRUE;
      return  &(PpWorkspace->SwStateArray[Index]);
    }
  }
  return NULL;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Create new DPM state
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Sclk             SCLK in kHz
 * @param[in]       Vid              Vid index
 * @retval                           Index of state entry in DPM state array
 */

UINT8
GfxPwrPlayCreateDpmState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Sclk,
  IN       UINT8                         Vid
  )
{
  UINT8 Index;

  for (Index = 0; Index < MAX_NUM_OF_DPM_STATES; Index++) {
    if (PpWorkspace->DpmStateArray[Index].Valid == FALSE) {
      PpWorkspace->DpmStateArray[Index].Sclk = Sclk;
      PpWorkspace->DpmStateArray[Index].Vid = Vid;
      PpWorkspace->DpmStateArray[Index].Valid = TRUE;
      PpWorkspace->DpmStateArray[Index].Tdp = 0;
      return Index;
    }
  }
  return 0;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Locate existing or Create new DPM state
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Sclk             SCLK in kHz
 * @param[in]       Vid              Vid index
 * @retval                           Index of state entry in DPM state array
 */

UINT8
GfxPwrPlayAddDpmState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Sclk,
  IN       UINT8                         Vid
  )
{
  UINT8 Index;

  for (Index = 0; Index < MAX_NUM_OF_DPM_STATES; Index++) {
    if (PpWorkspace->DpmStateArray[Index].Valid &&
        Sclk == PpWorkspace->DpmStateArray[Index].Sclk &&
        Vid == PpWorkspace->DpmStateArray[Index].Vid) {

      return Index;
    }
  }

  Index = GfxPwrPlayCreateDpmState (PpWorkspace, Sclk, Vid);

  return Index;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Add reference to DPM state for SW state
 *
 *
 * @param[in, out]  SwStateArray     Pointer to SW state array
 * @param[in]       DpmStateIndex    DPM state index
 */

VOID
GfxPwrPlayAddDpmStateToSwState (
  IN OUT   SW_STATE                      *SwStateArray,
  IN       UINT8                         DpmStateIndex
  )
{
  SwStateArray->DpmStatesArray[SwStateArray->NumberOfDpmStates++] = DpmStateIndex;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Copy SW state info to PPTable
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */
VOID *
GfxPwrPlayAttachStateInfoBlock (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                 Index;
  UINT8                 SwStateIndex;
  STATE_ARRAY           *StateArray;
  ATOM_PPLIB_STATE_V2   *States;
  StateArray = (STATE_ARRAY *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  States = &StateArray->States[0];
  SwStateIndex = 0;
  for (Index = 0; Index < MAX_NUM_OF_SW_STATES; Index++) {
    if (PpWorkspace->SwStateArray[Index].Valid && PpWorkspace->SwStateArray[Index].NumberOfDpmStates != 0) {
      States->nonClockInfoIndex  = SwStateIndex;
      States->ucNumDPMLevels = PpWorkspace->SwStateArray[Index].NumberOfDpmStates;
      LibAmdMemCopy (
        &States->ClockInfoIndex[0],
        PpWorkspace->SwStateArray[Index].DpmStatesArray,
        PpWorkspace->SwStateArray[Index].NumberOfDpmStates,
        GnbLibGetHeader (PpWorkspace->Gfx)
        );
      States = (ATOM_PPLIB_STATE_V2*) ((UINT8*) States + sizeof (ATOM_PPLIB_STATE_V2) + sizeof (UINT8) * (States->ucNumDPMLevels - 1));
      SwStateIndex++;
    }
  }
  StateArray->ucNumEntries = SwStateIndex;
  PpWorkspace->PpTable->sHeader.usStructureSize = PpWorkspace->PpTable->sHeader.usStructureSize + (USHORT) ((UINT8 *) States - (UINT8 *) StateArray);
IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachStateInfoBlock usStructureSize = %08x\n",
      PpWorkspace->PpTable->sHeader.usStructureSize);
  return StateArray;
}
/*----------------------------------------------------------------------------------------*/
/**
 * Copy clock info to PPTable
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  CLOCK_INFO_ARRAY            *ClockInfoArray;
  UINT8                       Index;
  UINT8                       ClkStateIndex;
  ClkStateIndex = 0;
  ClockInfoArray = (CLOCK_INFO_ARRAY *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  for (Index = 0; Index < PpWorkspace->NumOfSclkVoltDepEntries; Index++) {
    ClockInfoArray->ClockInfo[ClkStateIndex].index = (UINT8) Index;
    ClkStateIndex++;
  }
  ClockInfoArray->ucNumEntries = ClkStateIndex;
  ClockInfoArray->ucEntrySize = sizeof (ATOM_PPLIB_CZ_CLOCK_INFO);
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (CLOCK_INFO_ARRAY) + sizeof (ATOM_PPLIB_CZ_CLOCK_INFO) * ClkStateIndex - sizeof (ATOM_PPLIB_CZ_CLOCK_INFO);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachClockInfoBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return ClockInfoArray;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Copy non clock info to PPTable
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachNonClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  NON_CLOCK_INFO_ARRAY  *NonClockInfoArray;
  UINT8                 Index;
  UINT8                 NonClkStateIndex;

  NonClockInfoArray = (NON_CLOCK_INFO_ARRAY *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  NonClkStateIndex = 0;
  for (Index = 0; Index < MAX_NUM_OF_SW_STATES; Index++) {
    if (PpWorkspace->SwStateArray[Index].Valid && PpWorkspace->SwStateArray[Index].NumberOfDpmStates != 0) {
      NonClockInfoArray->NonClockInfo[NonClkStateIndex].usClassification = PpWorkspace->SwStateArray[Index].Classification;
      NonClockInfoArray->NonClockInfo[NonClkStateIndex].ulCapsAndSettings = PpWorkspace->SwStateArray[Index].CapsAndSettings;
      NonClockInfoArray->NonClockInfo[NonClkStateIndex].usClassification2 = PpWorkspace->SwStateArray[Index].Classification2;
      NonClockInfoArray->NonClockInfo[NonClkStateIndex].ulDCLK = PpWorkspace->SwStateArray[Index].Dclk;
      NonClockInfoArray->NonClockInfo[NonClkStateIndex].ulVCLK = PpWorkspace->SwStateArray[Index].Vclk;
      NonClkStateIndex++;
    }
  }
  NonClockInfoArray->ucNumEntries = NonClkStateIndex;
  NonClockInfoArray->ucEntrySize = sizeof (ATOM_PPLIB_NONCLOCK_INFO);
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (NON_CLOCK_INFO_ARRAY) + sizeof (ATOM_PPLIB_NONCLOCK_INFO) * NonClkStateIndex - sizeof (ATOM_PPLIB_NONCLOCK_INFO);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachNonClockInfoBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return NonClockInfoArray;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Check if fused state valid
 *
 *
 * @param[out]      Index             State index
 * @param[in]       PpFuses           Pointer to fuse table
 * @param[in]       Gfx               Gfx configuration info
 * @retval          TRUE              State is valid
 */
BOOLEAN
GfxPwrPlayIsFusedStateValid (
  IN      UINT8                         Index,
  IN      PP_FUSE_ARRAY_V2              *PpFuses,
  IN      GFX_PLATFORM_CONFIG           *Gfx
  )
{
  BOOLEAN Result;
  Result = FALSE;
  if ((PpFuses->PerfFlag & (1 << Index)) || (PpFuses->PowerSavingsFlag & (1 << Index))) {
    Result = TRUE;
  }
  return Result;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get SW state classification from fuses
 *
 *
 * @param[out]      Index             State index
 * @param[in]       PpFuses           Pointer to fuse table
 * @param[in]       Gfx               Gfx configuration info
 * @retval                            State classification
 */

UINT16
GfxPwrPlayGetClassificationFromFuses (
  IN      UINT8                         Index,
  IN      PP_FUSE_ARRAY_V2              *PpFuses,
  IN      GFX_PLATFORM_CONFIG           *Gfx
  )
{
  UINT16  Classification;
  Classification = ATOM_PPLIB_CLASSIFICATION_UVDSTATE;

  if (PpFuses->PerfFlag & (1 << Index)) {
//  case POLICY_LABEL_BATTERY:
    Classification |= ATOM_PPLIB_CLASSIFICATION_UI_BATTERY;
  }

  if (PpFuses->PowerSavingsFlag & (1 << Index)) {
//  case POLICY_LABEL_PERFORMANCE:
    Classification |= ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE;
  }

  return Classification;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build SCLK state info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildSclkStateTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       ClkStateIndex;
  UINT8                       DpmFuseIndex;
  UINT32                      Sclk;
  SW_STATE                    *State;
  PP_FUSE_ARRAY_V2            *PpFuses;

  PpFuses = PpWorkspace->PpFuses;

//Remove Battery state
//  // Create Battery state
//  State = GfxPwrPlayCreateSwState (PpWorkspace);
//
//  State->Classification = ATOM_PPLIB_CLASSIFICATION_UI_BATTERY;
//  State->Classification2 = 0;
//  State->Vclk = 0;
//  State->Dclk = 0;
//  if (PpWorkspace->Gfx->AbmSupport != 0) {
//    State->CapsAndSettings |= ATOM_PPLIB_ENABLE_VARIBRIGHT;
//  }
//  if (PpWorkspace->Gfx->DynamicRefreshRate != 0) {
//    State->CapsAndSettings |= ATOM_PPLIB_ENABLE_DRR;
//  }
//
//  // Loop through fused DPM states and find those that go with Battery
//  for (DpmFuseIndex = 0; DpmFuseIndex < MAX_NUM_OF_FUSED_DPM_STATES; DpmFuseIndex++) {
//
//    if (PpFuses->PowerSavingsFlag & (1 << DpmFuseIndex)) {
//
//      Sclk = (PpFuses->SclkDid[DpmFuseIndex] != 0) ?
//             GfxFmCalculateClock (PpFuses->SclkDid[DpmFuseIndex],
//                                  GnbLibGetHeader (PpWorkspace->Gfx)) : 0;
//
//      if (Sclk != 0) {
//        ClkStateIndex = GfxPwrPlayAddDpmState (PpWorkspace, Sclk, PpFuses->VddNbVid[DpmFuseIndex]);
//        GfxPwrPlayAddDpmStateToSwState (State, ClkStateIndex);
//      }
//    }
//  }

  // Create Performance state
  State = GfxPwrPlayCreateSwState (PpWorkspace);

  State->Classification = ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE;
  State->Classification2 = 0;
  State->Vclk = 0;
  State->Dclk = 0;

  // Loop through fused DPM states and find those that go with Performance
  for (DpmFuseIndex = 0; DpmFuseIndex < MAX_NUM_OF_FUSED_DPM_STATES; DpmFuseIndex++) {

    if (PpFuses->PerfFlag & (1 << DpmFuseIndex)) {

      Sclk = (PpFuses->SclkDid[DpmFuseIndex] != 0) ?
             GfxFmCalculateClock (PpFuses->SclkDid[DpmFuseIndex],
                                  GnbLibGetHeader (PpWorkspace->Gfx)) : 0;

      if (Sclk != 0) {
        ClkStateIndex = GfxPwrPlayAddDpmState (PpWorkspace, Sclk, PpFuses->VddNbVid[DpmFuseIndex]);
        if ((ClkStateIndex == 0) || (ClkStateIndex == 7)) {
          GfxPwrPlayAddDpmStateToSwState (State, ClkStateIndex);
        }
      }
    }
  }

  // Create Boot State
  State = GfxPwrPlayCreateSwState (PpWorkspace);
  State->Classification = ATOM_PPLIB_CLASSIFICATION_BOOT;
  Sclk = GfxFmCalculateClock (PpFuses->SclkDid[0],
                              GnbLibGetHeader (PpWorkspace->Gfx));
  ClkStateIndex = GfxPwrPlayAddDpmState (PpWorkspace, Sclk, PpFuses->VddNbVid[0]);
  GfxPwrPlayAddDpmStateToSwState (State, ClkStateIndex);

}


/*----------------------------------------------------------------------------------------*/
/**
 * Add ECLK state
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Eclk             SCLK in kHz
 * @retval                           Index of state entry in ECLK clock array
 */

UINT8
GfxPwrPlayAddEclkState (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Eclk
  )
{
  UINT8   Index;
  USHORT  EclkLow;
  UCHAR   EclkHigh;
  EclkLow = (USHORT) (Eclk & 0xffff);
  EclkHigh = (UCHAR) (Eclk >> 16);
  for (Index = 0; Index < PpWorkspace->NumOfVceClockEnties; Index++) {
    if (PpWorkspace->VceClockInfoArray[Index].ucECClkHigh == EclkHigh && PpWorkspace->VceClockInfoArray[Index].usECClkLow == EclkLow) {
      return Index;
    }
  }
  PpWorkspace->VceClockInfoArray[PpWorkspace->NumOfVceClockEnties].ucECClkHigh = EclkHigh;
  PpWorkspace->VceClockInfoArray[PpWorkspace->NumOfVceClockEnties].usECClkLow = EclkLow;
  PpWorkspace->VceClockInfoArray[PpWorkspace->NumOfVceClockEnties].ucEVClkHigh = EclkHigh;
  PpWorkspace->VceClockInfoArray[PpWorkspace->NumOfVceClockEnties].usEVClkLow = EclkLow;
  return PpWorkspace->NumOfVceClockEnties++;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Add ECLK voltage record
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       EclkIndex        ECLK index
 * @param[in]      Vid              Vid index
 * @retval                           Index of state entry in Eclk Voltage record array
 */

UINT8
GfxPwrPlayAddEclkVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         EclkIndex,
  IN       UINT8                         Vid
  )
{
  UINT8   Index;
  for (Index = 0; Index < PpWorkspace->NumOfClockVoltageLimitEnties; Index++) {
    if (PpWorkspace->VceClockVoltageLimitArray[Index].ucVCEClockInfoIndex == EclkIndex) {
      return Index;
    }
  }
  PpWorkspace->VceClockVoltageLimitArray[PpWorkspace->NumOfClockVoltageLimitEnties].ucVCEClockInfoIndex = EclkIndex;
  PpWorkspace->VceClockVoltageLimitArray[PpWorkspace->NumOfClockVoltageLimitEnties].usVoltage = Vid;
  return PpWorkspace->NumOfClockVoltageLimitEnties++;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Add Uvd Clock Info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Vclk             VCLK in kHz
 * @param[in]       Dclk             DCLK in kHz
 * @retval                           Index of state entry in clock array
 */

UINT8
GfxPwrPlayAddUvdClkInfo (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT32                        Vclk,
  IN       UINT32                        Dclk
  )
{
  UINT8   Index;
  USHORT  VclkLow;
  UCHAR   VclkHigh;
  USHORT  DclkLow;
  UCHAR   DclkHigh;
  VclkLow = (USHORT) (Vclk & 0xffff);
  VclkHigh = (UCHAR) (Vclk >> 16);
  DclkLow = (USHORT) (Dclk & 0xffff);
  DclkHigh = (UCHAR) (Dclk >> 16);
  for (Index = 0; Index < PpWorkspace->NumOfUvdClockEntries; Index++) {
    if (PpWorkspace->UvdClockInfoArray[Index].ucVClkHigh == VclkHigh &&
        PpWorkspace->UvdClockInfoArray[Index].usVClkLow == VclkLow) {
      return Index;
    }
  }
  PpWorkspace->UvdClockInfoArray[PpWorkspace->NumOfUvdClockEntries].ucVClkHigh = VclkHigh;
  PpWorkspace->UvdClockInfoArray[PpWorkspace->NumOfUvdClockEntries].usVClkLow = VclkLow;
  PpWorkspace->UvdClockInfoArray[PpWorkspace->NumOfUvdClockEntries].ucDClkHigh = DclkHigh;
  PpWorkspace->UvdClockInfoArray[PpWorkspace->NumOfUvdClockEntries].usDClkLow = DclkLow;
  return PpWorkspace->NumOfUvdClockEntries++;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Add Uvd voltage record
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       ClkIndex         CLK index
 * @param[in]       Vid              Vid index
 * @retval                           Index of state entry in Eclk Voltage record array
 */

UINT8
GfxPwrPlayAddUvdVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         ClkIndex,
  IN       UINT8                         Vid
  )
{
  UINT8   Index;
  for (Index = 0; Index < PpWorkspace->NumOfUvdClkVoltLimitEntries; Index++) {
    if (PpWorkspace->UvdClkVoltLimitArray[Index].ucUVDClockInfoIndex == ClkIndex) {
      return Index;
    }
  }
  PpWorkspace->UvdClkVoltLimitArray[PpWorkspace->NumOfUvdClkVoltLimitEntries].ucUVDClockInfoIndex =
      ClkIndex;
  PpWorkspace->UvdClkVoltLimitArray[PpWorkspace->NumOfUvdClkVoltLimitEntries].usVoltage = Vid;
  return PpWorkspace->NumOfUvdClkVoltLimitEntries++;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Add Samu voltage record
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Vid              Vid
 * @param[in]       Samclk           CLK associated with the Vid
 * @retval                           Index of state entry in Voltage record array
 */

UINT8
GfxPwrPlayAddSamuVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         Vid,
  IN       UINT32                        Samclk
  )
{
  UINT8   Index;
  USHORT  SamclkLow;
  UCHAR   SamclkHigh;
  SamclkLow = (USHORT) (Samclk & 0xffff);
  SamclkHigh = (UCHAR) (Samclk >> 16);
  for (Index = 0; Index < PpWorkspace->NumOfSamClkVoltLimitEntries; Index++) {
    if ((PpWorkspace->SamClkVoltLimitArray[Index].usSAMClockHigh == SamclkHigh) &&
        (PpWorkspace->SamClkVoltLimitArray[Index].usSAMClockLow == SamclkLow) &&
        (PpWorkspace->SamClkVoltLimitArray[Index].usVoltage == Vid)
        ) {
      return Index;
    }
  }
  PpWorkspace->SamClkVoltLimitArray[PpWorkspace->NumOfSamClkVoltLimitEntries].usSAMClockHigh =
      SamclkHigh;
  PpWorkspace->SamClkVoltLimitArray[PpWorkspace->NumOfSamClkVoltLimitEntries].usSAMClockLow =
      SamclkLow;
  PpWorkspace->SamClkVoltLimitArray[PpWorkspace->NumOfSamClkVoltLimitEntries].usVoltage = Vid;
  return PpWorkspace->NumOfSamClkVoltLimitEntries++;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Add Acp voltage record
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 * @param[in]       Vid              Vid



 * @param[in]       Acpclk           CLK associated with the Vid
 * @retval                           Index of state entry in Voltage record array
 */

UINT8
GfxPwrPlayAddAcpVoltageRecord (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace,
  IN       UINT8                         Vid,
  IN       UINT32                        Acpclk
  )
{
  UINT8   Index;
  USHORT  AcpclkLow;
  UCHAR   AcpclkHigh;
  AcpclkLow = (USHORT) (Acpclk & 0xffff);
  AcpclkHigh = (UCHAR) (Acpclk >> 16);
  for (Index = 0; Index < PpWorkspace->NumOfAcpClkVoltLimitEntries; Index++) {
    if ((PpWorkspace->AcpClkVoltLimitArray[Index].ucACPClockHigh == AcpclkHigh) &&
        (PpWorkspace->AcpClkVoltLimitArray[Index].usACPClockLow == AcpclkLow) &&
        (PpWorkspace->AcpClkVoltLimitArray[Index].usVoltage == Vid)
        ) {
      return Index;
    }
  }
  PpWorkspace->AcpClkVoltLimitArray[PpWorkspace->NumOfAcpClkVoltLimitEntries].ucACPClockHigh =
      AcpclkHigh;
  PpWorkspace->AcpClkVoltLimitArray[PpWorkspace->NumOfAcpClkVoltLimitEntries].usACPClockLow =
      AcpclkLow;
  PpWorkspace->AcpClkVoltLimitArray[PpWorkspace->NumOfAcpClkVoltLimitEntries].usVoltage = Vid;
  return PpWorkspace->NumOfAcpClkVoltLimitEntries++;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach extended header
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachExtendedHeaderBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_EXTENDEDHEADER *ExtendedHeader;
  ExtendedHeader = (ATOM_PPLIB_EXTENDEDHEADER *)
      ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  ExtendedHeader->usSize = sizeof (ATOM_PPLIB_EXTENDEDHEADER);
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (ATOM_PPLIB_EXTENDEDHEADER);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachExtendedHeaderBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return ExtendedHeader;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach Vce Rev Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachVceTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_VCE_TABLE  *VceTable;
  VceTable = (ATOM_PPLIB_VCE_TABLE *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  VceTable->revid = 0;
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (ATOM_PPLIB_VCE_TABLE);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachVceTableRevBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return VceTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach VCE clock info block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachVceClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  VCECLOCKINFOARRAY   *VceClockInfoArray;
  VceClockInfoArray = (VCECLOCKINFOARRAY *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  VceClockInfoArray->ucNumEntries = PpWorkspace->NumOfVceClockEnties;
  LibAmdMemCopy (
    &VceClockInfoArray->entries[0],
    &PpWorkspace->VceClockInfoArray[0],
    VceClockInfoArray->ucNumEntries * sizeof (VCECLOCKINFO),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize = PpWorkspace->PpTable->sHeader.usStructureSize +
                                                  sizeof (VCECLOCKINFOARRAY) +
                                                  VceClockInfoArray->ucNumEntries * sizeof (VCECLOCKINFO) -
                                                  sizeof (VCECLOCKINFO);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachVceClockInfoBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return VceClockInfoArray;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Attach VCE voltage limit block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachVceVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE  *VceClockVoltageLimitTable;
  VceClockVoltageLimitTable = (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  VceClockVoltageLimitTable->numEntries = PpWorkspace->NumOfClockVoltageLimitEnties;
  LibAmdMemCopy (
    &VceClockVoltageLimitTable->entries[0],
    &PpWorkspace->VceClockVoltageLimitArray[0],
    VceClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE) +
      VceClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD) -
      sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachVceVoltageLimitBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return VceClockVoltageLimitTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach VCE state block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachVceStateTableBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_VCE_STATE_TABLE  *VceStateTable;
  VceStateTable = (ATOM_PPLIB_VCE_STATE_TABLE *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  VceStateTable->numEntries = PpWorkspace->NumOfVceStateEntries;
  LibAmdMemCopy (
    &VceStateTable->entries[0],
    &PpWorkspace->VceStateArray[0],
    VceStateTable->numEntries * sizeof (ATOM_PPLIB_VCE_STATE_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize = PpWorkspace->PpTable->sHeader.usStructureSize +
                                                  sizeof (ATOM_PPLIB_VCE_STATE_TABLE) +
                                                  VceStateTable->numEntries * sizeof (ATOM_PPLIB_VCE_STATE_RECORD) -
                                                  sizeof (ATOM_PPLIB_VCE_STATE_RECORD);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxPwrPlayAttachVceStateTableBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return VceStateTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach Uvd Rev Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachUvdTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_UVD_TABLE  *UvdTable;
  UvdTable = (ATOM_PPLIB_UVD_TABLE *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  UvdTable->revid = 0;
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (ATOM_PPLIB_UVD_TABLE);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachUvdTableRevBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return UvdTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach UVD clock info block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachUvdClockInfoBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  UVD_CLOCK_INFO_ARRAY   *UvdClockInfoArray;
  UvdClockInfoArray = (UVD_CLOCK_INFO_ARRAY *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  UvdClockInfoArray->ucNumEntries = PpWorkspace->NumOfUvdClockEntries;
  LibAmdMemCopy (
    &UvdClockInfoArray->entries[0],
    &PpWorkspace->UvdClockInfoArray[0],
    UvdClockInfoArray->ucNumEntries * sizeof (UVD_CLOCK_INFO),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize = PpWorkspace->PpTable->sHeader.usStructureSize +
                                                  sizeof (UVD_CLOCK_INFO_ARRAY) +
                                                  UvdClockInfoArray->ucNumEntries * sizeof (UVD_CLOCK_INFO) -
                                                  sizeof (UVD_CLOCK_INFO);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachUvdClockInfoBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return UvdClockInfoArray;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Attach UVD voltage limit block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachUvdVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  UVD_CLK_VOLT_LIMIT_TABLE  *UvdClockVoltageLimitTable;
  UvdClockVoltageLimitTable = (UVD_CLK_VOLT_LIMIT_TABLE *) ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  UvdClockVoltageLimitTable->numEntries = PpWorkspace->NumOfUvdClkVoltLimitEntries;
  LibAmdMemCopy (
    &UvdClockVoltageLimitTable->entries[0],
    &PpWorkspace->UvdClkVoltLimitArray[0],
    UvdClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (UVD_CLK_VOLT_LIMIT_TABLE) +
      UvdClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD) -
      sizeof (ATOM_PPLIB_UVD_CLK_VOLT_LIMIT_RECORD);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachUvdVoltageLimitBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return UvdClockVoltageLimitTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach SAMU Rev Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachSamuTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_SAMU_TABLE  *VceTable;

  if (PpWorkspace->NumOfSamClkVoltLimitEntries == 0) {
    IDS_HDT_CONSOLE ( GNB_TRACE, "No GfxPwrPlayAttachSamuTableRevBlock usStructureSize \n");
    return PpWorkspace->PpTable;
  }

  VceTable = (ATOM_PPLIB_SAMU_TABLE *) ((UINT8 *) PpWorkspace->PpTable +
      PpWorkspace->PpTable->sHeader.usStructureSize);
  VceTable->revid = 0;
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (ATOM_PPLIB_SAMU_TABLE);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachSamuTableRevBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return VceTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach ACP Rev Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachAcpTableRevBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_ACP_TABLE  *AcpTable;

  if (PpWorkspace->NumOfAcpClkVoltLimitEntries == 0) {
    IDS_HDT_CONSOLE( GNB_TRACE, "No GfxPwrPlayAttachAcpTableRevBlock usStructureSize \n");
    return PpWorkspace->PpTable;
  }
  AcpTable = (ATOM_PPLIB_ACP_TABLE *) ((UINT8 *) PpWorkspace->PpTable +
      PpWorkspace->PpTable->sHeader.usStructureSize);
  AcpTable->revid = 0;
  PpWorkspace->PpTable->sHeader.usStructureSize += sizeof (ATOM_PPLIB_ACP_TABLE);

  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachAcpTableRevBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);
  return AcpTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach SAMU voltage limit block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachSamuVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE  *SamuClockVoltageLimitTable;
  SamuClockVoltageLimitTable = (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE *)
    ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  SamuClockVoltageLimitTable->numEntries = PpWorkspace->NumOfSamClkVoltLimitEntries;
  LibAmdMemCopy (
    &SamuClockVoltageLimitTable->entries[0],
    &PpWorkspace->SamClkVoltLimitArray[0],
    SamuClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE) +
      SamuClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD) -
      sizeof (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_RECORD);
  IDS_HDT_CONSOLE( GNB_TRACE, "GfxPwrPlayAttachSamuVoltageLimitBlock usStructureSize = %08x\n",PpWorkspace->PpTable->sHeader.usStructureSize);

  return SamuClockVoltageLimitTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach ACP voltage limit block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachAcpVoltageLimitBlock (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE  *AcpClockVoltageLimitTable;
  AcpClockVoltageLimitTable = (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE *)
    ((UINT8 *) PpWorkspace->PpTable + PpWorkspace->PpTable->sHeader.usStructureSize);
  AcpClockVoltageLimitTable->numEntries = PpWorkspace->NumOfAcpClkVoltLimitEntries;
  LibAmdMemCopy (
    &AcpClockVoltageLimitTable->entries[0],
    &PpWorkspace->AcpClkVoltLimitArray[0],
    AcpClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE) +
      AcpClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD) -
      sizeof (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_RECORD);

  IDS_HDT_CONSOLE( GNB_TRACE, "Acp clk num =             %02x\n", AcpClockVoltageLimitTable->numEntries);
  IDS_HDT_CONSOLE( GNB_TRACE, "Acp clk offset =          %08x\n", AcpClockVoltageLimitTable);
  IDS_HDT_CONSOLE( GNB_TRACE, "Acp clk usStructureSize = %08x\n",
      PpWorkspace->PpTable->sHeader.usStructureSize);

  return AcpClockVoltageLimitTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach Sclk Volt Dep Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachSclkDepTable (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE  *SclkTable;

  SclkTable = (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE *)
      ((UINT8 *) PpWorkspace->PpTable +
      PpWorkspace->PpTable->sHeader.usStructureSize);
  SclkTable->numEntries = PpWorkspace->NumOfSclkVoltDepEntries;
  LibAmdMemCopy (
    &SclkTable->entries[0],
    &PpWorkspace->SclkVoltDepArray[0],
    SclkTable->numEntries * sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE) +
      SclkTable->numEntries * sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD) -
      sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD);

  IDS_HDT_CONSOLE( GNB_TRACE, "Sclk num =             %02x\n", SclkTable->numEntries);
  IDS_HDT_CONSOLE( GNB_TRACE, "Sclk offset =          %08x\n", SclkTable);
  IDS_HDT_CONSOLE( GNB_TRACE, "Sclk usStructureSize = %08x\n",
      PpWorkspace->PpTable->sHeader.usStructureSize);

  return SclkTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Attach Sclk Volt GFX Dep Block
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID *
GfxPwrPlayAttachSclkGfxDepTable (
  IN OUT   PP_WORKSPACE_V2              *PpWorkspace
  )
{
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE  *SclkTable;

  SclkTable = (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE *)
      ((UINT8 *) PpWorkspace->PpTable +
      PpWorkspace->PpTable->sHeader.usStructureSize);
  SclkTable->numEntries = PpWorkspace->NumOfSclkVoltGfxDepEntries;
  LibAmdMemCopy (
    &SclkTable->entries[0],
    &PpWorkspace->SclkVoltGfxDepArray[0],
    SclkTable->numEntries * sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD),
    GnbLibGetHeader (PpWorkspace->Gfx)
    );
  PpWorkspace->PpTable->sHeader.usStructureSize =
      PpWorkspace->PpTable->sHeader.usStructureSize +
      sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE) +
      SclkTable->numEntries * sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD) -
      sizeof (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_RECORD);

  IDS_HDT_CONSOLE( GNB_TRACE, "SclkGfx num =             %02x\n", SclkTable->numEntries);
  IDS_HDT_CONSOLE( GNB_TRACE, "SclkGfx offset =          %08x\n", SclkTable);
  IDS_HDT_CONSOLE( GNB_TRACE, "SclkGfx usStructureSize = %08x\n",
      PpWorkspace->PpTable->sHeader.usStructureSize);

  return SclkTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build VCE state info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildVceStateTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       Index;
  UINT8                       VceStateIndex;
  UINT8                       Vid;
  UINT32                      Eclk;
  UINT32                      Sclk;
  UINT8                       UsedStateBitmap;
  UsedStateBitmap = 0;

  // load record table
  for (Index = 0;
       Index < (sizeof (PpWorkspace->VceStateArray) /
                sizeof (PpWorkspace->VceStateArray[0]));
       Index++) {
    Vid = PpWorkspace->PpFuses->VddNbVid[Index];
    Eclk = GfxFmCalculateClock (PpWorkspace->PpFuses->EclkDid[Index],
                                GnbLibGetHeader (PpWorkspace->Gfx));
    PpWorkspace->VceStateArray[Index].ucVCEClockInfoIndex =
        GfxPwrPlayAddEclkState (PpWorkspace, Eclk);
    Sclk = GfxFmCalculateClock (PpWorkspace->PpFuses->SclkDid[Index],
                                GnbLibGetHeader (PpWorkspace->Gfx));
    PpWorkspace->VceStateArray[Index].ucClockInfoIndex =
        GfxPwrPlayAddDpmState (PpWorkspace, Sclk, Vid);
    GfxPwrPlayAddEclkVoltageRecord (PpWorkspace,
        PpWorkspace->VceStateArray[Index].ucVCEClockInfoIndex, Vid);
  }

  // build used state
  for (Index = 0;
       Index < (sizeof (PpWorkspace->PpFuses->VceFlags) /
                sizeof (PpWorkspace->PpFuses->VceFlags[0])) ;
       Index++) {
    UsedStateBitmap |= PpWorkspace->PpFuses->VceFlags[Index];
    IDS_HDT_CONSOLE (GFX_MISC, "  VceFlags[%x] = %x\n", Index, PpWorkspace->PpFuses->VceFlags[Index]);
    for (VceStateIndex = 0;
         VceStateIndex < (sizeof (PpWorkspace->VceStateArray) /
                          sizeof (PpWorkspace->VceStateArray[0]));
         VceStateIndex++) {
      if ((PpWorkspace->PpFuses->VceFlags[Index] & (1 << VceStateIndex)) != 0) {
        Sclk = GfxFmCalculateClock (PpWorkspace->PpFuses->SclkDid[PpWorkspace->PpFuses->VceReqSclkSel[Index]],
                                    GnbLibGetHeader (PpWorkspace->Gfx));
        Vid = PpWorkspace->PpFuses->VddNbVid[PpWorkspace->PpFuses->VceReqSclkSel[Index]];
        PpWorkspace->VceStateArray[VceStateIndex].ucClockInfoIndex =
            GfxPwrPlayAddDpmState (PpWorkspace, Sclk, Vid);
        if (PpWorkspace->PpFuses->VceMclk) {
          PpWorkspace->VceStateArray[VceStateIndex].ucClockInfoIndex |=
              (PpWorkspace->PpFuses->VceMclk << 6);
        }
        Eclk = GfxFmCalculateClock (PpWorkspace->PpFuses->EclkDid[Index],
                                    GnbLibGetHeader (PpWorkspace->Gfx));
        PpWorkspace->VceStateArray[VceStateIndex].ucVCEClockInfoIndex =
            GfxPwrPlayAddEclkState (PpWorkspace, Eclk);
        PpWorkspace->NumOfVceStateEntries++;
      }
    }
  }
  IDS_HDT_CONSOLE (GFX_MISC, "  NumOfVceStateEntries %d\n", PpWorkspace->NumOfVceStateEntries);

  //build unused states
  for (VceStateIndex = 0;
       VceStateIndex < (sizeof (PpWorkspace->VceStateArray) / sizeof (PpWorkspace->VceStateArray[0]));
       VceStateIndex++) {
    if ((UsedStateBitmap & (1 << VceStateIndex)) == 0) {
      PpWorkspace->VceStateArray[VceStateIndex].ucClockInfoIndex = 0;
      PpWorkspace->VceStateArray[VceStateIndex].ucVCEClockInfoIndex = GfxPwrPlayAddEclkState (PpWorkspace, 0);
      PpWorkspace->NumOfVceStateEntries++;
    }
  }
  IDS_HDT_CONSOLE (GFX_MISC, "  UsedStateBitmap %x\n", UsedStateBitmap);
  IDS_HDT_CONSOLE (GFX_MISC, "  NumOfVceStateEntries %d\n", PpWorkspace->NumOfVceStateEntries);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build UVD state info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildUvdClockTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       Index;
  UINT8                       Vid;
  UINT32                      Vclk;
  UINT32                      Dclk;
  UINT8                       UvdIndex;

  // build used state
  for (Index = 0; Index < MAX_NUM_OF_UVD_CLK_STATES ; Index++) {
    if (GfxPwrPlayIsFusedStateValid (Index, PpWorkspace->PpFuses, PpWorkspace->Gfx)) {
      Vid = PpWorkspace->PpFuses->VddNbVid[Index];
      Vclk = GfxFmCalculateClock (PpWorkspace->PpFuses->VclkDid[Index],
                                  GnbLibGetHeader (PpWorkspace->Gfx));
      Dclk = GfxFmCalculateClock (PpWorkspace->PpFuses->DclkDid[Index],
                                  GnbLibGetHeader (PpWorkspace->Gfx));
      UvdIndex = GfxPwrPlayAddUvdClkInfo (PpWorkspace, Vclk, Dclk);
      GfxPwrPlayAddUvdVoltageRecord (PpWorkspace,
          UvdIndex, Vid);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build SAMU info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildSamuTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       SamuIndex;
  UINT8                       Vid;
  UINT32                      Samuclk;
  // build used state
  for (SamuIndex = 0; SamuIndex < MAX_NUM_OF_SAMCLK_STATES; SamuIndex++) {
    if (GfxPwrPlayIsFusedStateValid (SamuIndex, PpWorkspace->PpFuses, PpWorkspace->Gfx)) {
      Vid = PpWorkspace->PpFuses->VddNbVid[SamuIndex];
      if (PpWorkspace->PpFuses->SamClkDid[SamuIndex] != 0) {
        Samuclk = GfxFmCalculateClock (PpWorkspace->PpFuses->SamClkDid[SamuIndex],
            GnbLibGetHeader (PpWorkspace->Gfx));
        GfxPwrPlayAddSamuVoltageRecord (PpWorkspace, Vid, Samuclk);
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build Acp info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildAcpTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       AcpIndex;
  UINT8                       Vid;
  UINT32                      Acpclk;
  // build used state
  for (AcpIndex = 0; AcpIndex < MAX_NUM_OF_ACPCLK_STATES; AcpIndex++) {
    if (GfxPwrPlayIsFusedStateValid (AcpIndex, PpWorkspace->PpFuses, PpWorkspace->Gfx)) {
      Vid = PpWorkspace->PpFuses->VddNbVid[AcpIndex];
      if (PpWorkspace->PpFuses->AcpClkDid[AcpIndex] != 0) {
        Acpclk = GfxFmCalculateClock (PpWorkspace->PpFuses->AcpClkDid[AcpIndex],
            GnbLibGetHeader (PpWorkspace->Gfx));
        GfxPwrPlayAddAcpVoltageRecord (PpWorkspace, Vid, Acpclk);
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build Sclk info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildSclkDepTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       SclkIndex;
  UINT8                       Vid;
  UINT32                      Sclk;
  USHORT  SclkLow;
  UCHAR   SclkHigh;

  // build the table
  for (SclkIndex = 0; SclkIndex < MAX_NUM_OF_FUSED_DPM_STATES; SclkIndex++) {
    if (GfxPwrPlayIsFusedStateValid (SclkIndex, PpWorkspace->PpFuses,
        PpWorkspace->Gfx)) {
      Vid = PpWorkspace->PpFuses->VddNbVid[SclkIndex];
      Sclk = GfxFmCalculateClock (PpWorkspace->PpFuses->SclkDid[SclkIndex],
          GnbLibGetHeader (PpWorkspace->Gfx));
      ASSERT (Vid != 0)
      ASSERT (Sclk != 0)
      SclkLow = (USHORT) (Sclk & 0xffff);
      SclkHigh = (UCHAR) (Sclk >> 16);
      PpWorkspace->SclkVoltDepArray[SclkIndex].usVoltage = Vid;
      PpWorkspace->SclkVoltDepArray[SclkIndex].ucClockHigh = SclkHigh;
      PpWorkspace->SclkVoltDepArray[SclkIndex].usClockLow = SclkLow;
      PpWorkspace->NumOfSclkVoltDepEntries++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build Sclk Gfx info
 *
 *
 * @param[in, out]  PpWorkspace      PP workspace
 */

VOID
GfxPwrPlayBuildSclkGfxDepTable (
  IN OUT   PP_WORKSPACE_V2               *PpWorkspace
  )
{
  UINT8                       SclkIndex;
  UINT8                       Vid;
  UINT32                      Sclk;
  USHORT  SclkLow;
  UCHAR   SclkHigh;

  // build the table
  for (SclkIndex = 0; SclkIndex < MAX_NUM_OF_FUSED_DPM_STATES; SclkIndex++) {
    if (GfxPwrPlayIsFusedStateValid (SclkIndex, PpWorkspace->PpFuses,
        PpWorkspace->Gfx)) {
      Vid = PpWorkspace->PpFuses->GfxVid[SclkIndex];
      Sclk = GfxFmCalculateClock (PpWorkspace->PpFuses->SclkDid[SclkIndex],
          GnbLibGetHeader (PpWorkspace->Gfx));
      // ASSERT (Vid != 0)
      ASSERT (Sclk != 0)
      SclkLow = (USHORT) (Sclk & 0xffff);
      SclkHigh = (UCHAR) (Sclk >> 16);
      PpWorkspace->SclkVoltGfxDepArray[SclkIndex].usVoltage = Vid;
      PpWorkspace->SclkVoltGfxDepArray[SclkIndex].ucClockHigh = SclkHigh;
      PpWorkspace->SclkVoltGfxDepArray[SclkIndex].usClockLow = SclkLow;
      PpWorkspace->NumOfSclkVoltGfxDepEntries++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build PP table
 *
 *
 * @param[out] Buffer           Buffer to create PP table
 * @param[in]  Gfx              Gfx configuration info
 * @retval     AGESA_SUCCESS
 * @retval     AGESA_ERROR
 */

AGESA_STATUS
GfxPwrPlayBuildTable (
     OUT   VOID                          *Buffer,
  IN       GFX_PLATFORM_CONFIG           *Gfx
  )
{
  PP_WORKSPACE_V2             PpWorkspace;
  VOID                        *BlockPtr;

  LibAmdMemFill (&PpWorkspace, 0x00, sizeof (PP_WORKSPACE_V2), GnbLibGetHeader (Gfx));
  PpWorkspace.PpFuses = GnbLocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, GnbLibGetHeader (Gfx));
  ASSERT (PpWorkspace.PpFuses != NULL);
  if (PpWorkspace.PpFuses == NULL) {
    return AGESA_ERROR;
  }

  PpWorkspace.PpTable = (ATOM_PPLIB_POWERPLAYTABLE5 *) Buffer;
  PpWorkspace.Gfx = Gfx;
  //Fill static info
  PpWorkspace.PpTable->sHeader.ucTableFormatRevision = 6;
  PpWorkspace.PpTable->sHeader.ucTableContentRevision = 1;
  PpWorkspace.PpTable->ucDataRevision = PpWorkspace.PpFuses->PPlayTableRev;

  PpWorkspace.PpTable->sThermalController.ucFanParameters = ATOM_PP_FANPARAMETERS_NOFAN;
  PpWorkspace.PpTable->sHeader.usStructureSize = sizeof (ATOM_PPLIB_POWERPLAYTABLE5);
  PpWorkspace.PpTable->usTableSize = sizeof (ATOM_PPLIB_POWERPLAYTABLE5);

  if ((Gfx->AmdPlatformType & AMD_PLATFORM_MOBILE) != 0) {
    PpWorkspace.PpTable->ulPlatformCaps |= ATOM_PP_PLATFORM_CAP_POWERPLAY;
  }

  // Fill Sclk SW/DPM state info

  GfxPwrPlayBuildSclkStateTable (&PpWorkspace);

  // Fill Eclk state info
  if (PpWorkspace.PpFuses->VceStateTableSupport) {
    GfxPwrPlayBuildVceStateTable (&PpWorkspace);
    GfxPwrPlayBuildUvdClockTable (&PpWorkspace);
    GfxPwrPlayBuildSamuTable (&PpWorkspace);
    GfxPwrPlayBuildSclkDepTable (&PpWorkspace);
    GfxPwrPlayBuildAcpTable (&PpWorkspace);
    GfxPwrPlayBuildSclkGfxDepTable (&PpWorkspace);
  }

  //Copy state info to actual PP table
  BlockPtr = GfxPwrPlayAttachStateInfoBlock (&PpWorkspace);
  PpWorkspace.PpTable->usStateArrayOffset = (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
  BlockPtr = GfxPwrPlayAttachClockInfoBlock (&PpWorkspace);
  PpWorkspace.PpTable->usClockInfoArrayOffset = (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
  BlockPtr = GfxPwrPlayAttachNonClockInfoBlock (&PpWorkspace);
  PpWorkspace.PpTable->usNonClockInfoArrayOffset = (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));

  if (PpWorkspace.PpFuses->VceStateTableSupport) {
    ATOM_PPLIB_EXTENDEDHEADER   *ExtendedHeader;
    ExtendedHeader =
        (ATOM_PPLIB_EXTENDEDHEADER *) GfxPwrPlayAttachExtendedHeaderBlock (&PpWorkspace);
    PpWorkspace.PpTable->usExtendendedHeaderOffset =
        (USHORT) ((UINT8 *) ExtendedHeader - (UINT8 *) (PpWorkspace.PpTable));
    BlockPtr = GfxPwrPlayAttachVceTableRevBlock (&PpWorkspace);
    ExtendedHeader->usVCETableOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
    GfxPwrPlayAttachVceClockInfoBlock (&PpWorkspace);
    GfxPwrPlayAttachVceVoltageLimitBlock (&PpWorkspace);
    GfxPwrPlayAttachVceStateTableBlock (&PpWorkspace);

    BlockPtr = GfxPwrPlayAttachUvdTableRevBlock (&PpWorkspace);
    ExtendedHeader->usUVDTableOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
    GfxPwrPlayAttachUvdClockInfoBlock (&PpWorkspace);
    GfxPwrPlayAttachUvdVoltageLimitBlock (&PpWorkspace);

    BlockPtr = GfxPwrPlayAttachSamuTableRevBlock (&PpWorkspace);
    ExtendedHeader->usSAMUTableOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
    if (ExtendedHeader->usSAMUTableOffset != 0) {
      GfxPwrPlayAttachSamuVoltageLimitBlock (&PpWorkspace);
    }

    BlockPtr = GfxPwrPlayAttachSclkDepTable (&PpWorkspace);
    PpWorkspace.PpTable->usVddcDependencyOnSCLKOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));

    BlockPtr = GfxPwrPlayAttachAcpTableRevBlock (&PpWorkspace);
    ExtendedHeader->usACPTableOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));
    if (ExtendedHeader->usACPTableOffset != 0) {
      GfxPwrPlayAttachAcpVoltageLimitBlock (&PpWorkspace);
    }

    BlockPtr = GfxPwrPlayAttachSclkGfxDepTable (&PpWorkspace);
    ExtendedHeader->usSclkVddgfxTableOffset =
        (USHORT) ((UINT8 *) BlockPtr - (UINT8 *) (PpWorkspace.PpTable));


    IDS_HDT_CONSOLE (GNB_TRACE, "ExtendedHeader \n");
    IDS_HDT_CONSOLE (GNB_TRACE, "   VceTableOffset = %04x\n", ExtendedHeader->usVCETableOffset);
    IDS_HDT_CONSOLE (GNB_TRACE, "   UvdTableOffset = %04x\n", ExtendedHeader->usUVDTableOffset);
    IDS_HDT_CONSOLE (GNB_TRACE, "   SamTableOffset = %04x\n", ExtendedHeader->usSAMUTableOffset);
    IDS_HDT_CONSOLE (GNB_TRACE, "   AcpTableOffset = %04x\n", ExtendedHeader->usACPTableOffset);
    IDS_HDT_CONSOLE (GNB_TRACE, "   sclkVddgfxTableOffset = %04x\n", ExtendedHeader->usSclkVddgfxTableOffset);
    IDS_HDT_CONSOLE (GNB_TRACE, "\n");

  }

  IDS_HDT_CONSOLE( GNB_TRACE, "total pp table size = %08x\n",
      PpWorkspace.PpTable->sHeader.usStructureSize);
  GNB_DEBUG_CODE (
    GfxIntDebugDumpPpTable (PpWorkspace.PpTable, Gfx);
  );

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump PP table
 *
 *
 *
 * @param[in] PpTable           Power Play table
 * @param[in] Gfx               Gfx configuration info
 */

VOID
GfxIntDebugDumpPpTable (
  IN       ATOM_PPLIB_POWERPLAYTABLE5   *PpTable,
  IN       GFX_PLATFORM_CONFIG          *Gfx
  )
{
  UINTN                                     Index;
  UINTN                                     DpmIndex;
  STATE_ARRAY                               *StateArray;
  ATOM_PPLIB_STATE_V2                       *StatesPtr;
  NON_CLOCK_INFO_ARRAY                      *NonClockInfoArrayPtr;
  CLOCK_INFO_ARRAY                          *ClockInfoArrayPtr;
  ATOM_PPLIB_EXTENDEDHEADER                 *ExtendedHeader;
  ATOM_PPLIB_VCE_STATE_TABLE                *VceStateTable;
  ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE  *VceClockVoltageLimitTable;
  VCECLOCKINFOARRAY                         *VceClockInfoArray;
  UVD_CLOCK_INFO_ARRAY                      *UvdClockInfoArray;
  UVD_CLK_VOLT_LIMIT_TABLE                  *UvdClockVoltLimitTable;
  ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE        *SamuClockVoltLimitTable;
  ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE        *AcpClockVoltLimitTable;
  UINT8                                     SclkIndex;
  UINT8                                     EclkIndex;
  UINT8                                     VclkIndex;
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE      *GfxClockVoltDepTable;
  ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE      *SclkClockVoltDepTable;

  IDS_HDT_CONSOLE (GFX_MISC, "  < --- Power Play Table ------ > \n");
  IDS_HDT_CONSOLE (GFX_MISC, "  Table Revision = %d\n", PpTable->ucDataRevision);
  StateArray = (STATE_ARRAY *) ((UINT8 *) PpTable + PpTable->usStateArrayOffset);
  StatesPtr = StateArray->States;
  NonClockInfoArrayPtr = (NON_CLOCK_INFO_ARRAY *) ((UINT8 *) PpTable + PpTable->usNonClockInfoArrayOffset);
  ClockInfoArrayPtr = (CLOCK_INFO_ARRAY *) ((UINT8 *) PpTable + PpTable->usClockInfoArrayOffset);
  IDS_HDT_CONSOLE (GFX_MISC, "  < --- SW State Table ---------> \n");
  for (Index = 0; Index < StateArray->ucNumEntries; Index++) {
    IDS_HDT_CONSOLE (GFX_MISC, "  State #%d\n", Index + 1
      );
    IDS_HDT_CONSOLE (GFX_MISC, "    Classification 0x%x\n",
       NonClockInfoArrayPtr->NonClockInfo[StatesPtr->nonClockInfoIndex].usClassification
      );
    IDS_HDT_CONSOLE (GFX_MISC, "    Classification2 0x%x\n",
       NonClockInfoArrayPtr->NonClockInfo[StatesPtr->nonClockInfoIndex].usClassification2
      );
    IDS_HDT_CONSOLE (GFX_MISC, "    VCLK = %dkHz\n",
       NonClockInfoArrayPtr->NonClockInfo[StatesPtr->nonClockInfoIndex].ulVCLK
      );
    IDS_HDT_CONSOLE (GFX_MISC, "    DCLK = %dkHz\n",
       NonClockInfoArrayPtr->NonClockInfo[StatesPtr->nonClockInfoIndex].ulDCLK
      );
    IDS_HDT_CONSOLE (GFX_MISC, "    DPM State Index: ");
    for (DpmIndex = 0; DpmIndex < StatesPtr->ucNumDPMLevels; DpmIndex++) {
      IDS_HDT_CONSOLE (GFX_MISC, "%d ",
        StatesPtr->ClockInfoIndex [DpmIndex]
        );
    }
    IDS_HDT_CONSOLE (GFX_MISC, "\n");
    StatesPtr = (ATOM_PPLIB_STATE_V2 *) ((UINT8 *) StatesPtr + sizeof (ATOM_PPLIB_STATE_V2) + StatesPtr->ucNumDPMLevels - 1);
  }

  SclkClockVoltDepTable = (PpTable->usVddcDependencyOnSCLKOffset == NULL) ? NULL :
  (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE *)
  ((UINT8 *) PpTable + PpTable->usVddcDependencyOnSCLKOffset);

  IDS_HDT_CONSOLE (GFX_MISC, "  < --- ATOM_PPLIB_CZ_CLOCK_INFO(SCLK DPM State Table) ---> \n");
  if (SclkClockVoltDepTable != NULL) {
    for (Index = 0; Index < ClockInfoArrayPtr->ucNumEntries; Index++) {
      UINT32  Sclk;
      Sclk = SclkClockVoltDepTable->entries[ClockInfoArrayPtr->ClockInfo[Index].index].usClockLow | (SclkClockVoltDepTable->entries[ClockInfoArrayPtr->ClockInfo[Index].index].ucClockHigh << 16);
      IDS_HDT_CONSOLE (GFX_MISC, "  DPM State #%d\n",
        Index
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    SCLK = %d\n",
        Sclk
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
        SclkClockVoltDepTable->entries[ClockInfoArrayPtr->ClockInfo[Index].index].usVoltage
        );
    }
  }
  if (PpTable->usExtendendedHeaderOffset != 0) {
    ExtendedHeader = (ATOM_PPLIB_EXTENDEDHEADER *) ((UINT8 *) PpTable +
      PpTable->usExtendendedHeaderOffset);

    IDS_HDT_CONSOLE (GNB_TRACE, "ExtendedHeader = %08x\n", ExtendedHeader);

    VceClockInfoArray = (VCECLOCKINFOARRAY *) ((UINT8 *) PpTable +
        ExtendedHeader->usVCETableOffset + sizeof (ATOM_PPLIB_VCE_TABLE));
    VceClockVoltageLimitTable =
        (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE *) ((UINT8 *) VceClockInfoArray +
        sizeof (VCECLOCKINFOARRAY) +
        VceClockInfoArray->ucNumEntries * sizeof (VCECLOCKINFO) -
        sizeof (VCECLOCKINFO));
    VceStateTable =
        (ATOM_PPLIB_VCE_STATE_TABLE *) ((UINT8 *) VceClockVoltageLimitTable +
        sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_TABLE) +
        VceClockVoltageLimitTable->numEntries * sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD) -
        sizeof (ATOM_PPLIB_VCE_CLOCK_VOLTAGE_LIMIT_RECORD));
    UvdClockInfoArray =
        (UVD_CLOCK_INFO_ARRAY *) ((UINT8 *) PpTable + ExtendedHeader->usUVDTableOffset +
         sizeof (ATOM_PPLIB_UVD_TABLE));
    UvdClockVoltLimitTable =
        (UVD_CLK_VOLT_LIMIT_TABLE *) ((UINT8 *) UvdClockInfoArray + sizeof (UVD_CLOCK_INFO_ARRAY) +
        UvdClockInfoArray->ucNumEntries * sizeof (UVD_CLOCK_INFO) -
        sizeof (UVD_CLOCK_INFO));
    SamuClockVoltLimitTable = (ExtendedHeader->usSAMUTableOffset == NULL) ? NULL :
        (ATOM_PPLIB_SAMCLK_VOLT_LIMIT_TABLE *)
        ((UINT8 *) PpTable + ExtendedHeader->usSAMUTableOffset + sizeof (ATOM_PPLIB_SAMU_TABLE));
    AcpClockVoltLimitTable = (ExtendedHeader->usACPTableOffset == NULL) ? NULL :
        (ATOM_PPLIB_ACPCLK_VOLT_LIMIT_TABLE *)
        ((UINT8 *) PpTable + ExtendedHeader->usACPTableOffset + sizeof (ATOM_PPLIB_ACP_TABLE));
//    SclkClockVoltDepTable = (PpTable->usVddcDependencyOnSCLKOffset == NULL) ? NULL :
//        (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE *)
//        ((UINT8 *) PpTable + PpTable->usVddcDependencyOnSCLKOffset);
    GfxClockVoltDepTable = (ExtendedHeader->usSclkVddgfxTableOffset == NULL) ? NULL :
        (ATOM_PPLIB_CLK_VOLT_DEPENDENCY_TABLE *)
        ((UINT8 *) PpTable + ExtendedHeader->usSclkVddgfxTableOffset);

    IDS_HDT_CONSOLE (GFX_MISC, "  < --- VCE State Table [%d]--> \n", VceStateTable->numEntries);
    for (Index = 0; Index < VceStateTable->numEntries; Index++) {
      SclkIndex = VceStateTable->entries[Index].ucClockInfoIndex & 0x3F;
      EclkIndex = VceStateTable->entries[Index].ucVCEClockInfoIndex;
      IDS_HDT_CONSOLE (GFX_MISC, "  SclkIndex = %d\n", SclkIndex);
      IDS_HDT_CONSOLE (GFX_MISC, "  EclkIndex = %d\n", EclkIndex);
      IDS_HDT_CONSOLE (GFX_MISC, "  VCE State #%d\n", Index
        );
      if ((VceClockInfoArray->entries[EclkIndex].usECClkLow | (VceClockInfoArray->entries[EclkIndex].ucECClkHigh << 16)) == 0) {
        IDS_HDT_CONSOLE (GFX_MISC, "    Disable\n");
      } else {
        IDS_HDT_CONSOLE (GFX_MISC, "    SCLK = %d\n",
//          ClockInfoArrayPtr->ClockInfo[SclkIndex].usEngineClockLow | (ClockInfoArrayPtr->ClockInfo[SclkIndex].ucEngineClockHigh << 16)
          SclkClockVoltDepTable->entries[ClockInfoArrayPtr->ClockInfo[SclkIndex].index].usClockLow | (SclkClockVoltDepTable->entries[ClockInfoArrayPtr->ClockInfo[SclkIndex].index].ucClockHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    ECCLK = %d\n",
          VceClockInfoArray->entries[EclkIndex].usECClkLow | (VceClockInfoArray->entries[EclkIndex].ucECClkHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    EVCLK = %d\n",
          VceClockInfoArray->entries[EclkIndex].usEVClkLow | (VceClockInfoArray->entries[EclkIndex].ucEVClkHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    MCLK = %d\n",
          (VceStateTable->entries[Index].ucClockInfoIndex >> 6 ) & 0x3
          );
      }
    }

    IDS_HDT_CONSOLE (GFX_MISC, "  < --- VCE Voltage Record Table ---> \n");
    for (Index = 0; Index < VceClockVoltageLimitTable->numEntries; Index++) {
      EclkIndex = VceClockVoltageLimitTable->entries[Index].ucVCEClockInfoIndex;
      IDS_HDT_CONSOLE (GFX_MISC, "  VCE Voltage Record #%d\n", Index
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    VCE Table Index (ucVCEClockInfoIndex) = %d\n",
        EclkIndex
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    ECLK = %d\n",
        VceClockInfoArray->entries[EclkIndex].usECClkLow | (VceClockInfoArray->entries[EclkIndex].ucECClkHigh << 16)
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
        VceClockVoltageLimitTable->entries[Index].usVoltage
        );
    }

    IDS_HDT_CONSOLE (GFX_MISC, "  < --- UVD Voltage Record Table ---> \n");
    for (Index = 0; Index < UvdClockVoltLimitTable->numEntries; Index++) {
      VclkIndex = UvdClockVoltLimitTable->entries[Index].ucUVDClockInfoIndex;
      IDS_HDT_CONSOLE (GFX_MISC, "  UVD Voltage Record #%d\n", Index
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    UVD Table Index (ucUVDClockInfoIndex) = %d\n",
        VclkIndex
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    VCLK = %d\n",
        UvdClockInfoArray->entries[VclkIndex].usVClkLow | (UvdClockInfoArray->entries[VclkIndex].ucVClkHigh << 16)
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    DCLK = %d\n",
        UvdClockInfoArray->entries[VclkIndex].usDClkLow | (UvdClockInfoArray->entries[VclkIndex].ucDClkHigh << 16)
        );
      IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
        UvdClockVoltLimitTable->entries[Index].usVoltage
        );
    }

    if (SamuClockVoltLimitTable != NULL) {
      IDS_HDT_CONSOLE (GFX_MISC, "  < --- SAMU Voltage Record Table ---> \n");
      for (Index = 0; Index < SamuClockVoltLimitTable->numEntries; Index++) {
        IDS_HDT_CONSOLE (GFX_MISC, "  SAMU Voltage Record #%d\n", Index
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    SAMCLK = %d\n",
            SamuClockVoltLimitTable->entries[Index].usSAMClockLow |
            (SamuClockVoltLimitTable->entries[Index].usSAMClockHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
            SamuClockVoltLimitTable->entries[Index].usVoltage
          );
      }
    }

    if (AcpClockVoltLimitTable != NULL) {
      IDS_HDT_CONSOLE (GFX_MISC, "  < --- ACP Voltage Record Table ---> \n");
      for (Index = 0; Index < AcpClockVoltLimitTable->numEntries; Index++) {
        IDS_HDT_CONSOLE (GFX_MISC, "  Acp Voltage Record #%d\n", Index
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    ACPCLK = %d\n",
            AcpClockVoltLimitTable->entries[Index].usACPClockLow |
            (AcpClockVoltLimitTable->entries[Index].ucACPClockHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
            AcpClockVoltLimitTable->entries[Index].usVoltage
          );
      }
    }

    if (SclkClockVoltDepTable != NULL) {
      IDS_HDT_CONSOLE (GFX_MISC, "  < --- Vddc SCLK Voltage Dependency Table ---> \n");
      for (Index = 0; Index < SclkClockVoltDepTable->numEntries; Index++) {
        IDS_HDT_CONSOLE (GFX_MISC, "  Vddc Sclk Voltage Dep Table #%d\n", Index
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    SCLK = %d\n",
            SclkClockVoltDepTable->entries[Index].usClockLow |
            (SclkClockVoltDepTable->entries[Index].ucClockHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
            SclkClockVoltDepTable->entries[Index].usVoltage
          );
      }
    }

    if (GfxClockVoltDepTable != NULL) {
      IDS_HDT_CONSOLE (GFX_MISC, "  <--- GFX Voltage Dependency Table ---> \n");
      for (Index = 0; Index < GfxClockVoltDepTable->numEntries; Index++) {
        IDS_HDT_CONSOLE (GFX_MISC, "  Gfx Sclk Voltage Dep Table #%d\n", Index
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    SCLK = %d\n",
            GfxClockVoltDepTable->entries[Index].usClockLow |
            (GfxClockVoltDepTable->entries[Index].ucClockHigh << 16)
          );
        IDS_HDT_CONSOLE (GFX_MISC, "    VID index = %x\n",
            GfxClockVoltDepTable->entries[Index].usVoltage
          );
      }
    }

  }

  for (Index = 0; Index < 512; Index++) {
    if ((Index % 16) == 0) {
      IDS_HDT_CONSOLE (GFX_MISC, " \n");
    }
    IDS_HDT_CONSOLE (GFX_MISC, " %02x", *(UINT8 *)((UINT8 *)PpTable + Index));
  }


  IDS_HDT_CONSOLE (GFX_MISC, " PplayDumpExit\n");

}

