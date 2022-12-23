/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Ccx Pstates Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
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
#include <Library/BaseLib.h>
#include <AGESA.h>
#include <cpuRegisters.h>
#include <CcxRegistersVh.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxPstatesLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_CCXPSTATESVHLIB_CCXPSTATESVHLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxGetPstateInfo
 *
 *    Get Pstate information
 *
 *    @param[in]      Socket         Zero-based socket number to check
 *    @param[in]      Pstate         Which P-state to analyze
 *    @param[in]      Frequency      The P-State's frequency in MegaHertz
 *    @param[in]      VoltageInuV    The P-State's voltage in uV
 *    @param[in]      PowerInmW      The Power in milliWatts of that P-State
 *    @param[in]      StdHeader      Standard Head Pointer
 *
 *    @retval         TRUE           Get Pstate information successful.
 *    @retval         FALSE          Pstate is disabled
 *
 */
BOOLEAN
CcxGetPstateInfo (
  IN       UINTN               Socket,
  IN       CCX_PSTATE          Pstate,
     OUT   UINTN              *Frequency,
     OUT   UINTN              *VoltageInuV,
     OUT   UINTN              *PowerInmW,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT32    CpuFid;
  UINT32    CpuDfsId;
  UINT32    CpuVid;
  UINT32    IddValue;
  UINT32    IddDiv;
  UINT32    PstateNumber;
  PSTATE_MSR  PstateMsr;

  PstateNumber = Pstate < HwPstate0 ? (UINT32) Pstate : (UINT32) Pstate - HwPstate0;
  PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + PstateNumber);

  if (PstateMsr.Field.PstateEn == 0) {
    return FALSE;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  F17VhGetPstateFrequency - P%d\n", PstateNumber);

  CpuFid   = (UINT32) PstateMsr.Field.CpuFid_7_0;
  CpuDfsId = (UINT32) PstateMsr.Field.CpuDfsId;
  CpuVid   = (UINT32) PstateMsr.Field.CpuVid;
  IddValue = (UINT32) PstateMsr.Field.IddValue;
  IddDiv   = (UINT32) PstateMsr.Field.IddDiv;

  ASSERT ((CpuDfsId <= 0x1A) || ((CpuDfsId & BIT0) == 0));

  if (CpuDfsId == 0) {
    *Frequency = 0;
  } else if ((CpuDfsId >= 8) && (CpuDfsId <= 0x3C)) {
    *Frequency = (UINTN) ((200 * CpuFid) / CpuDfsId);
  } else {
    IDS_HDT_CONSOLE (CPU_TRACE, "    Undefined CpuDfsId %d used. Force it to div 1.\n", CpuDfsId);
    ASSERT (FALSE);
    *Frequency = (UINTN) (25 * CpuFid);
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "    FrequencyInMHz=%d, CpuFid=%d, CpuDfsId=%d\n", *Frequency, CpuFid, CpuDfsId);

  // Voltage
  if ((CpuVid >= 0xF8) && (CpuVid <= 0xFF)) {
    *VoltageInuV = 0;
  } else {
    *VoltageInuV = 1550000L - (6250 * CpuVid);
  }

  // PowerInmW
  *PowerInmW = (*VoltageInuV) / 10 * IddValue;

  switch (IddDiv) {
  case 0:
    *PowerInmW = *PowerInmW / 100L;
    break;
  case 1:
    *PowerInmW = *PowerInmW / 1000L;
    break;
  case 2:
    *PowerInmW = *PowerInmW / 10000L;
    break;
  default:
    // IddDiv is set to an undefined value.  This is due to either a misfused CPU, or
    // an invalid P-state MSR write.
    ASSERT (FALSE);
    *PowerInmW = 0;
    break;
  }
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxGetPstateNumber
 *
 *    Get number of Pstate
 *
 *    @param[in]      Socket               Zero-based socket number to check
 *    @param[in]      NumberOfBoostPstate  Number of boost Pstate
 *    @param[in]      NumberOfHwPstate     Number of hardware Pstate
 *    @param[in]      StdHeader            Standard Head Pointer
 *
 */
VOID
CcxGetPstateNumber (
  IN       UINTN               Socket,
     OUT   UINTN              *NumberOfBoostPstate,
     OUT   UINTN              *NumberOfHwPstate,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  PSTATE_CURLIM_MSR  CurLim;

  *NumberOfBoostPstate = 0;

  CurLim.Value = AsmReadMsr64 (MSR_PSTATE_CURRENT_LIMIT);
  *NumberOfHwPstate = (UINTN) CurLim.Field.PstateMaxVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxSwitchPstate
 *
 *    Switch to a certain Pstate
 *
 *    @param[in]      SwitchPstate            Target Pstate & wait for completion
 *
 */
VOID
CcxSwitchPstate (
  IN       CCX_SWITCH_PSTATE *SwitchPstate
  )
{
  PSTATE_MSR           PstateMsr;
  HW_PSTATE_STATUS_MSR HwPstateSts;

  PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + (UINT32) (SwitchPstate->Pstate));
  if (PstateMsr.Field.PstateEn == 0) {
    ASSERT (FALSE);
    return;
  }

  AsmWriteMsr64 (MSR_PSTATE_CTL, SwitchPstate->Pstate);

  if (SwitchPstate->WaitForCompletion) {
    if (SwitchPstate->Pstate != 0) {
      // Switch to non-P0, check FID & DID
      do {
        HwPstateSts.Value = AsmReadMsr64 (MSR_HW_PSTATE_STATUS);
      } while ((HwPstateSts.Field.CurCpuFid != PstateMsr.Field.CpuFid_7_0) ||
               (HwPstateSts.Field.CurCpuDfsId != PstateMsr.Field.CpuDfsId));
    } else {
      // Switch to P0, check current frequency >= P0
      do {
        HwPstateSts.Value = AsmReadMsr64 (MSR_HW_PSTATE_STATUS);
      } while ((DivU64x32 (MultU64x64 (200, (UINT32) HwPstateSts.Field.CurCpuFid), (UINT32) HwPstateSts.Field.CurCpuDfsId)) <
               (DivU64x32 (MultU64x64 (200, (UINT32) PstateMsr.Field.CpuFid_7_0), (UINT32) PstateMsr.Field.CpuDfsId)));
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxGetCurrentPstate
 *
 *    Get current Pstate
 *
 *    @retval  UINT8    current Pstate
 *
 */
UINT8
CcxGetCurrentPstate (
  )
{
  PSTATE_STS_MSR PstateSts;

  PstateSts.Value = AsmReadMsr64 (MSR_PSTATE_STS);
  return (UINT8) PstateSts.Field.CurPstate;
}

/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */


