/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Boot Time Calibration Library
 *
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
#include "PiDxe.h"
#include <Library/BaseLib.h>
#include <Library/SynchronizationLib.h>
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include "CcxRegistersXv.h"
#include "UnbRegisters.h"
#include "Library/AmdBaseLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include <Library/PciLib.h>
#include "Protocol/MpService.h"

#define FILECODE LIBRARY_CCXBTCLIB_CCXXVBTCLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                          G L O B A L     D A T A
 *----------------------------------------------------------------------------------------
 */
STATIC UINT8          OkToStartTest;
STATIC EFI_EVENT      AmdBtcEvent;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT8
CcxXvBtcGetTargetPstate (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );

AGESA_STATUS
CcxXvTransitionPstate (
 IN       UINT8              StateNumber,
 IN       BOOLEAN            WaitForTransition,
 IN       AMD_CONFIG_PARAMS *StdHeader
 );

VOID
CcxXvBtcAps (
 IN       AMD_CONFIG_PARAMS *StdHeader
 );

 /*----------------------------------------------------------------------------------------
  *                          E X P O R T E D    F U N C T I O N S
  *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Setup for boot time calibration tests.
 *
 * This procedure will perform the following steps :
 * 1..Set Bsp to P7 (Or Pmin)
 *
 * @param[in]  StdHeader            Standard configuration header
 */
AGESA_STATUS
CcxBtcBefore (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8                     TargetPstate;
  EFI_MP_SERVICES_PROTOCOL *MpServices;
  EFI_STATUS                Status;

  // Initialize the semaphore.
  OkToStartTest = 0;

  TargetPstate = CcxXvBtcGetTargetPstate (StdHeader);
  CcxXvTransitionPstate (TargetPstate, FALSE, StdHeader);

  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
  if (EFI_ERROR (Status)) {
    return AGESA_ERROR;
  }

  // Create a event so StartupAllAPs executes in non-blocking mode.
  Status = gBS->CreateEvent (
                  0x00000000,
                  0,
                  NULL,
                  NULL,
                  &AmdBtcEvent
                  );
  if (EFI_ERROR (Status)) {
    return AGESA_ERROR;
  }

  Status = MpServices->StartupAllAPs (
           MpServices,
           CcxXvBtcAps,
           FALSE,
           AmdBtcEvent,
           0,
           (VOID *) StdHeader,
           NULL
           );

  if (EFI_ERROR (Status))  {
    return AGESA_ERROR;
  }

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Restore pre workload run conditions
 *
 * @param[in]  StdHeader            Standard configuration header
 */
VOID
CcxBtcAfter (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  InterlockedIncrement ((UINT32 *) &OkToStartTest);

  CcxXvTransitionPstate (0, FALSE, StdHeader);

  while (gBS->CheckEvent (AmdBtcEvent) == EFI_SUCCESS) {
  }
}

/*---------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Return a target Pstate which is required for the CalPgmIndex
 *
 * @param[in]  StdHeader        Standard configuration header
 *
 * @return                      Target Pstate which is required for the CalPgmIndex
 */
UINT8
CcxXvBtcGetTargetPstate (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8  TargetPstate;
  UINTN  PciAddress;
  CPB_CTRL_REGISTER CpbCtrl;
  CLK_PWR_TIMING_CTRL2_REGISTER Cptc2;

  TargetPstate = 7;
  PciAddress = CPTC2_PCI_ADDR;
  *((UINT32 *) &Cptc2) = PciRead32 (PciAddress);
  if (TargetPstate > (UINT8) Cptc2.HwPstateMaxVal) {
    TargetPstate = (UINT8) Cptc2.HwPstateMaxVal;
  };

  PciAddress = CPB_CTRL_PCI_ADDR;
  *((UINT32 *) &CpbCtrl) = PciRead32 (PciAddress);
  TargetPstate = TargetPstate - (UINT8) CpbCtrl.NumBoostStates;

  return (TargetPstate);
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Transitions the executing core to the desired P-state.
 *
 *  @param[in]   StateNumber              The new P-State to make effective.
 *  @param[in]   WaitForTransition        True if the caller wants the transition completed upon return.
 *  @param[in]   StdHeader                Header for library and services
 *
 *  @retval      AGESA_SUCCESS       Always Succeeds
 */
AGESA_STATUS
CcxXvTransitionPstate (
  IN       UINT8              StateNumber,
  IN       BOOLEAN            WaitForTransition,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT64       LocalMsrRegister;

  LocalMsrRegister = AsmReadMsr64 (MSR_PSTATE_CTL);
  ((PSTATE_CTRL_MSR *) &LocalMsrRegister)->PstateCmd = (UINT64) StateNumber;
  AsmWriteMsr64 (MSR_PSTATE_CTL, LocalMsrRegister);
  if (WaitForTransition) {
    do {
      LocalMsrRegister = AsmReadMsr64 (MSR_PSTATE_STS);
    } while (((PSTATE_STS_MSR *) &LocalMsrRegister)->CurPstate != (UINT64) StateNumber);
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Work procedure for the Aps.
 *
 * This procedure will perform the following steps :
 * 1..Set APs to P7 (Or Pmin)
 * 2..Wait for semaphore to flag run tests.
 * 3..Transfer to a target Pstate
 * 4..If tests completed, wait for semaphore to signal transition Pstate and exit, else...
 *    ... wait for semaphore to signal run next workload.
 *
 *  @param[in]   StdHeader                Header for library and services
 */
VOID
CcxXvBtcAps (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8   TargetPstate;

  TargetPstate = CcxXvBtcGetTargetPstate (StdHeader);
  CcxXvTransitionPstate (TargetPstate, TRUE, StdHeader);

  while (OkToStartTest == 0) {
    CpuPause ();
  }

  CcxXvTransitionPstate (0, FALSE, StdHeader);

  return;
}

