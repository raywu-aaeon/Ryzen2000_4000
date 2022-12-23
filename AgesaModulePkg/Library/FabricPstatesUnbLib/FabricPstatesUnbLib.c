/* $NoKeywords:$ */
/**
 * @file
 *
 * Base Fabric Pstates Lib implementation for UNB
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
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
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include "FabricPstatesUnbLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/FabricPstatesLib.h"
#include "Library/AmdHeapLib.h"
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include "Ppi/FabricPstateServicesPpi.h"

#define FILECODE LIBRARY_FABRICPSTATESUNBLIB_FABRICPSTATESUNBLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define NB_PS_HIGH 0
#define NB_PS_LOW  1

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
UnbTransitionToNbLow (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
UnbTransitionToNbHigh (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
WaitForNbTransitionToComplete (
  IN       UINT8              NbPsHiOrLow,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

BOOLEAN
FabricPstatesAreAllSocketsInAUnifiedDomain (
  VOID
  )
{
  return FALSE;
}

BOOLEAN
FabricPstatesAreAllDieOnSocketInAUnifiedDomain (
  IN       UINTN  Socket
  )
{
  return FALSE;
}

BOOLEAN
FabricPstatesIsSwitchingEnabledOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  BOOLEAN                Support;
  UINTN                  PciAddress;
  NB_PSTATE_STS_REGISTER NbPstateSts;

  Support = FALSE;

  if (PcdGetBool (PcdAmdFabricPstateSupport)) {
    PciAddress = NB_PSTATE_STATUS_PCI_ADDR;
    *((UINT32 *) &NbPstateSts) = PciRead32 (PciAddress);
    if (NbPstateSts.NbPstateDis != 1) {
      Support = TRUE;
    }
  }
  return Support;
}

UINTN
FabricPstatesGetNumberOfPstatesOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  UINTN                   PciAddress;
  NB_PSTATE_CTRL_REGISTER NbPstateCtrl;

  PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
  *((UINT32 *) &NbPstateCtrl) = PciRead32 (PciAddress);
  return (NbPstateCtrl.NbPstateMaxVal + 1);
}

VOID
FabricPstatesGetPstateInfo (
  IN       UINTN               Socket,
  IN       UINTN               Die,
  IN       UINTN               Pstate,
     OUT   FABRIC_PSTATE_INFO  *Info
  )
{
  UINT32             Vid;
  UINTN              PciAddress;
  NB_PSTATE_REGISTER NbPstate;

  PciAddress = NB_PSTATE_0_PCI_ADDR + Pstate * 4;
  *((UINT32 *) &NbPstate) = PciRead32 (PciAddress);

  Vid = GetF15CzNbVid (&NbPstate);

  // COF = (100 * (Fid + 4) / (2 ^ Did));
  Info->Frequency = 100 * (NbPstate.NbFid_5_0 + 4) / (1 << NbPstate.NbDid);
  // Voltage in uV (1mV = 1000uV)
  Info->Voltage = ConvertVidInuV (Vid);
  // Power in mW
  Info->Power = Info->Voltage * NbPstate.NbIddValue;
  switch (NbPstate.NbIddDiv) {
  case 0:
    Info->Power = Info->Power / 1000L;
    break;
  case 1:
    Info->Power = Info->Power / 10000L;
    break;
  case 2:
    Info->Power = Info->Power / 100000L;
    break;
  default:
    // IddDiv is set to an undefined value.  This is due to either a misfused CPU, or
    // an invalid P-state MSR write.
    Info->Power = 0;
    break;
  }
  // AssociatedMstate
  Info->AssociatedMstate = NbPstate.MemPstate;
}

BOOLEAN
FabricPstatesForcePstateOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die,
  IN       UINTN  Pstate
  )
{
  UINT32                   PciData;
  BOOLEAN                  SmuCfgLock;
  UINTN                    PciAddress;
  LOCATE_HEAP_PTR          LocateHeap;
  ALLOCATE_HEAP_PARAMS     AllocateHeap;
  SAVE_NB_PSTATE_CTRL_REG *SaveNbPstateCtrlReg;
  NB_PSTATE_CTRL_REGISTER  NbPstateCtrl;
  NB_PSTATE_STS_REGISTER   NbPstateSts;

  if (Pstate == NB_HIGH) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Force Nb High on Socket%d Die%d\n", Socket, Die);
    UnbTransitionToNbHigh (NULL);
    return TRUE;
  }
  if (Pstate == NB_LOW) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Force Nb Low on Socket%d Die%d\n", Socket, Die);
    UnbTransitionToNbLow (NULL);
    return TRUE;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  Force Pstate%d on Socket%d Die%d\n", Pstate, Socket, Die);

  // Get Heap
  LocateHeap.BufferHandle = AMD_FABRIC_PSTATE_LIB_HANDLE;
  if (HeapLocateBuffer (&LocateHeap, NULL) == AGESA_SUCCESS) {
    SaveNbPstateCtrlReg = (SAVE_NB_PSTATE_CTRL_REG *) LocateHeap.BufferPtr;
  } else {
    AllocateHeap.BufferHandle = AMD_FABRIC_PSTATE_LIB_HANDLE;
    AllocateHeap.RequestedBufferSize = sizeof (SAVE_NB_PSTATE_CTRL_REG);
    AllocateHeap.Persist = HEAP_BOOTTIME_SYSTEM_MEM;
    if (HeapAllocateBuffer (&AllocateHeap, NULL) != AGESA_SUCCESS) {
      return FALSE;
    }
    SaveNbPstateCtrlReg = (SAVE_NB_PSTATE_CTRL_REG *) AllocateHeap.BufferPtr;
    LibAmdMemFill (SaveNbPstateCtrlReg, 0, sizeof (SAVE_NB_PSTATE_CTRL_REG), NULL);
  }

  // Get NbPstateCtrl
  PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
  *((UINT32 *) &NbPstateCtrl) = PciRead32 (PciAddress);
  if (SaveNbPstateCtrlReg->Valid == FALSE) {
    // Save Nb Pstate Ctrl Reg
    SaveNbPstateCtrlReg->NbPstateCtrl = NbPstateCtrl;
    SaveNbPstateCtrlReg->Valid = TRUE;
  }

  // Check SmuCfgLock and return FALSE if appropriate
  PciAddress = MAKE_SBDFO (0, 0, 0x18, FUNC_2, 0x1B4);
  PciData = PciRead32 (PciAddress);
  SmuCfgLock = (BOOLEAN) ((PciData >> 25) & 1);

  if ((Pstate != NbPstateCtrl.NbPstateHi) && (Pstate != NbPstateCtrl.NbPstateLo) && SmuCfgLock) {
    return FALSE;
  }

  // Force
  PciAddress = NB_PSTATE_STATUS_PCI_ADDR;
  *((UINT32 *) &NbPstateSts) = PciRead32 (PciAddress);

  if ((NbPstateSts.CurNbPstate != NbPstateCtrl.NbPstateHi) && (NbPstateSts.CurNbPstate != NbPstateCtrl.NbPstateLo)) {
    // Current NbPstate is neither NbPstateHi nor NbPstateLo
    // SwitchNbPstate first
    if (NbPstateSts.CurNbPstateLo == 1) {
      UnbTransitionToNbHigh (NULL);
    } else {
      UnbTransitionToNbLow (NULL);
    }
    // Update NbPstateSts
    PciAddress = NB_PSTATE_STATUS_PCI_ADDR;
    *((UINT32 *) &NbPstateSts) = PciRead32 (PciAddress);
  }

  PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
  if (Pstate < NbPstateCtrl.NbPstateLo) {
    // Pstate > NbPstateLo
    // Modify NbPstateHi and switch to NbPstateHi
    if ((NbPstateSts.CurNbPstateLo == 0) && (NbPstateCtrl.NbPstateHi != Pstate)) {
      UnbTransitionToNbLow (NULL);
    }
    NbPstateCtrl.NbPstateHi = (UINT32)Pstate;
    PciWrite32 (PciAddress, *((UINT32 *) &NbPstateCtrl));

    UnbTransitionToNbHigh (NULL);
  } else {
    // Pstate >= NbPstateLo
    // Modify NbPstateLo and switch to NbPstateLo
    if ((NbPstateSts.CurNbPstateLo == 1) && (NbPstateCtrl.NbPstateLo != Pstate)) {
      UnbTransitionToNbHigh (NULL);
    }
    NbPstateCtrl.NbPstateLo = (UINT32)Pstate;
    PciWrite32 (PciAddress, *((UINT32 *) &NbPstateCtrl));
    UnbTransitionToNbLow (NULL);
  }
  return TRUE;
}

VOID
FabricPstatesReleaseForceOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  UINTN                    PciAddress;
  LOCATE_HEAP_PTR          LocateHeap;
  SAVE_NB_PSTATE_CTRL_REG *SaveNbPstateCtrlReg;
  NB_PSTATE_CTRL_REGISTER  NbPstateCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "  Pstates release force\n");

  LocateHeap.BufferHandle = AMD_FABRIC_PSTATE_LIB_HANDLE;
  if (HeapLocateBuffer (&LocateHeap, NULL) == AGESA_SUCCESS) {
    SaveNbPstateCtrlReg = (SAVE_NB_PSTATE_CTRL_REG *) LocateHeap.BufferPtr;
    if (SaveNbPstateCtrlReg->Valid) {
      PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
      *((UINT32 *) &NbPstateCtrl) = PciRead32 (PciAddress);
      NbPstateCtrl = SaveNbPstateCtrlReg->NbPstateCtrl;
      PciWrite32 (PciAddress, *((UINT32 *) &NbPstateCtrl));
    }
  }
  return;
}

UINTN
FabricPstatesGetCurrentPstateOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  UINTN                    PciAddress;
  NB_PSTATE_STS_REGISTER   NbPstateSts;

  PciAddress = NB_PSTATE_STATUS_PCI_ADDR;
  *((UINT32 *) &NbPstateSts) = PciRead32 (PciAddress);
  return NbPstateSts.CurNbPstate;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
UnbTransitionToNbLow (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINTN                     PciAddress;
  NB_PSTATE_CTRL_REGISTER   NbPsCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "  TransitionToNbLow\n");

  // Write 0 to D18F5x170[SwNbPstateLoDis, NbPstateDisOnP0, NbPstateThreshold].
  PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
  *((UINT32 *) &NbPsCtrl) = PciRead32 (PciAddress);
  NbPsCtrl.SwNbPstateLoDis = 0;
  NbPsCtrl.NbPstateDisOnP0 = 0;
  NbPsCtrl.NbPstateThreshold = 0;
  PciWrite32 (PciAddress, *((UINT32 *) &NbPsCtrl));

  // Wait for D18F5x174[CurNbPstateLo] = 1
  WaitForNbTransitionToComplete (NB_PS_LOW, StdHeader);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Transition to the high NB P-state.
 *
 *
 * @param[in]  StdHeader          Config handle for library and services.
 *
 */
VOID
UnbTransitionToNbHigh (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINTN                     PciAddress;
  NB_PSTATE_CTRL_REGISTER   NbPsCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "  TransitionToNbHigh\n");

  // Set D18F5x170[SwNbPstateLoDis] = 1.
  PciAddress = NB_PSTATE_CTRL_PCI_ADDR;
  *((UINT32 *) &NbPsCtrl) = PciRead32 (PciAddress);
  NbPsCtrl.SwNbPstateLoDis = 1;
  PciWrite32 (PciAddress, *((UINT32 *) &NbPsCtrl));

  // Wait for D18F5x174[CurNbPstateLo] = 0
  WaitForNbTransitionToComplete (NB_PS_HIGH, StdHeader);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Wait for CurNbPstateLo to match requirment
 *
 *
 * @param[in]  NbPsHiOrLow        Switch to Nb Pstate High or Nb Low
 * @param[in]  StdHeader          Config handle for library and services.
 *
 */
VOID
WaitForNbTransitionToComplete (
  IN       UINT8              NbPsHiOrLow,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINTN                    PciAddress;
  NB_PSTATE_STS_REGISTER   NbPsSts;

  IDS_HDT_CONSOLE (CPU_TRACE, "  WaitForNbTransitionToComplete\n");

  PciAddress = NB_PSTATE_STATUS_PCI_ADDR;
  do {
    *((UINT32 *) &NbPsSts) = PciRead32 (PciAddress);
  } while (((UINT8) NbPsSts.CurNbPstateLo != NbPsHiOrLow) || (NbPsSts.Reserved == 1));
}


