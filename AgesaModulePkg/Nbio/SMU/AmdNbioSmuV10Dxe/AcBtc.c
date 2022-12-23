/* $NoKeywords:$ */
/**
 * @file
 *
 * AcBtc Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AcBtc
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <PiDxe.h>
#include <Filecode.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>
#include <Library/AmdBaseLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IdsLib.h>
#include <Library/CcxPstatesLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/GnbLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/CcxPstatesLib.h>
#include <Library/GnbRegisterAccZpLib.h>
#include <Library/PcieConfigLib.h>
#include <Protocol/MpService.h>
#include <AmdNbioSmuV10Dxe.h>
#include "AcBtc.h"
#include "smu10_bios_if.h"
#include "smu10.h"

#define FILECODE NBIO_SMU_AMDNBIOSMUV10DXE_ACBTC_FILECODE

VOLATILE STATIC UINT64   ApReadyCount;
VOLATILE STATIC UINT64   ApTaskToRun;
VOLATILE STATIC UINT64   TscP0Count2mS;
STATIC EFI_EVENT         AmdBtcEvent;
VOID                     *WorkloadBuffer;

extern
VOID
ExecuteF17RvBtc (
  IN       UINT64  CalPgmIndex,
  IN       UINT64  Scratch    ///< Pointer to work buffer
  );

extern
VOID
ExecuteHalt (
  IN       UINT64  CalPgmIndex,
  IN       UINT64  Scratch    ///< Pointer to work buffer
  );

extern
VOID
SynchronizeAllApsF17Rv (
  IN       UINT64   IncrementAddress,
  IN       UINT64   MonitorAddress
  );

/* -----------------------------------------------------------------------------*/
/**
 *
 *  MiscBtcAps
 *
 *  Description:
 *    This routine stop all APs
 *
 */
VOID
RunBtcOnAps (
  )
{
  ACBTC_WORKLOAD_STRUCT  *LocalWorkload;
  UINT32                 Index;

  for (Index = 0; Index < 3; Index++) {
    SynchronizeAllApsF17Rv ((UINT64) &ApReadyCount, (UINT64) &ApTaskToRun);
    LocalWorkload = WorkloadBuffer;
    ((ACBTC_WORKLOAD_STRUCT *) LocalWorkload)->tscWaitCount = TscP0Count2mS;
    while (Index != ApTaskToRun) {}
    ExecuteF17RvBtc ((UINT64)ApTaskToRun, (UINT64)LocalWorkload);
  }
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  BeforeBtc
 *
 *  Description:
 *    This routine execute before BTC
 *
 */
EFI_STATUS
EFIAPI
StartBtc (
  )
{
  EFI_STATUS                 Status;
  EFI_MP_SERVICES_PROTOCOL   *MpServices;

  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
  if (EFI_ERROR (Status)) {
    return Status;
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
             (EFI_AP_PROCEDURE)RunBtcOnAps,
             FALSE,
             AmdBtcEvent,
             0,
             NULL,
             NULL
             );

  if (EFI_ERROR (Status))  {
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *---------------------------------------------------------------------------------------
 *  CallbackAcBtc
 *
 *  Description:
 *     notification event handler after MpService Protocol ready
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
CallbackAcBtc (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  )
{
  EFI_STATUS                           Status;
  PCIe_PLATFORM_CONFIG                 *PcieFromHob;
  PCIe_PLATFORM_CONFIG                 *Pcie;
  GNB_HANDLE                           *NbioHandle;
  UINT32                               SmuArg[6];
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServiceProtocol;
  UINT32                               AcBtcIndex;
  EFI_MP_SERVICES_PROTOCOL             *MpService;
  UINT32                               SmuResult;
  UINT32                               WorkloadBufferSize;
  UINT64                               WorkloadBufferAligned;
//  UINT8                                Index;
  UINT32                               NumberOfComplexes;
  UINT32                               NumberOfThreads;
  UINT32                               TotalThreads;
  UINTN                                Frequency;
  UINTN                                VoltageInuV;
  UINTN                                PowerInmW;
  PWR_018_STRUCT                       ThreadEnable;
  PWR_01C_STRUCT                       ThreadConfiguration;
  UINT64                               ActiveThreadMap;
  UINT8                                CoreThreads;
  UINT8                                ThreadBit;

  IDS_HDT_CONSOLE (MAIN_FLOW, "Callback Ac Btc First notify\n");

  PcieFromHob = NULL;

  // Frequency      The P-State's frequency in MegaHertz
  if (TRUE == CcxGetPstateInfo (0, 0, &Frequency, &VoltageInuV, &PowerInmW, (AMD_CONFIG_PARAMS*) NULL)) {
    TscP0Count2mS = Frequency * 2000;
  }

  //
  // Add more check to locate protocol after got event, because
  // the library will signal this event immediately once it is register
  // just in case it is already installed.
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  &MpService
                  );

  if (EFI_ERROR (Status)) {
    return;
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "Callback Ac Btc Start\n");

  SmuDxeInitialize (&PcieFromHob);
  Pcie = PcieFromHob;

  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuServicesProtocolGuid,
                  NULL,
                  &NbioSmuServiceProtocol
                  );
  IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);


  NumberOfComplexes = 0;
  NumberOfThreads = 0;
  TotalThreads = 0;
  NbioHandle = NbioGetHandle (Pcie);
  GnbRegisterReadZP (NbioHandle,
                     THREAD_CONFIGURATION_TYPE,
                     THREAD_CONFIGURATION_ADDRESS,
                     &ThreadConfiguration,
                     0,
                     NULL);
  NumberOfComplexes += ThreadConfiguration.Field.ComplexCount + 1;
  NumberOfThreads = (ThreadConfiguration.Field.SMTMode == 0) ? 2 : 1;
  TotalThreads += (ThreadConfiguration.Field.ComplexCount + 1) * (ThreadConfiguration.Field.CoreCount + 1) * NumberOfThreads;
  IDS_HDT_CONSOLE (MAIN_FLOW, "TotalThreads = 0x%x\n", TotalThreads);
  IDS_HDT_CONSOLE (MAIN_FLOW, "TotalComplexes = 0x%x\n", NumberOfComplexes);

  if (PcdGet8 (PcdAcBtc)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "AcBtc \n");
    /// Need to allocate workload buffer - minimum size is 0x931 qwords or 18824 bytes
    //
    //  Step14. Allocate DRAM
    //
    WorkloadBufferSize = (sizeof (ACBTC_WORKLOAD_STRUCT) + 64) * NumberOfComplexes;
    IDS_HDT_CONSOLE (MAIN_FLOW, "WorkloadBufferSize = 0x%x\n", WorkloadBufferSize);
    Status = gBS->AllocatePool (
                    EfiRuntimeServicesData,
                    WorkloadBufferSize,
                    &WorkloadBuffer
                    );
    IDS_HDT_CONSOLE (MAIN_FLOW, "Allocate Pool Status = 0x%x\n", Status);
    WorkloadBufferAligned = (UINT64) WorkloadBuffer;
    WorkloadBufferAligned = (WorkloadBufferAligned + 63) & 0xFFFFFFFFFFFFFFC0;
    WorkloadBuffer = (VOID *) WorkloadBufferAligned;

    ApReadyCount = 0;
    ApTaskToRun = 0xFF;
    IDS_HDT_CONSOLE (MAIN_FLOW, "Before ApReadyCount = 0x%x\n", ApReadyCount);
    // Step1: Start all APs running.  The first thing they should do is a call to a MONITOR/MWWAIT function. On return from the function they will execute the workload function.
    StartBtc();

    for (AcBtcIndex = 0; AcBtcIndex < 3; AcBtcIndex++) {
    // Initialize the ApReadyCount.

      // Wait for all APs to reach MWAIT...
      while (ApReadyCount < (TotalThreads - 1)) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "ApReadyCount = 0x%x\n", ApReadyCount);
      }
      IDS_HDT_CONSOLE (MAIN_FLOW, "ApReadyCount = 0x%x\n", ApReadyCount);

      // Renitialize the ApReadyCount because APs will return to increment it after workload execution
      ApReadyCount = 0;
      IDS_HDT_CONSOLE (MAIN_FLOW, "ApReadyCount = 0x%x\n", ApReadyCount);

      // Initialize SynchLine for all buffers
      ActiveThreadMap = 0xBEEFBEEFBEEFBEEFull;
      NbioHandle = NbioGetHandle (Pcie);
      GnbRegisterReadZP (NbioHandle,
                         THREAD_ENABLE_TYPE,
                         THREAD_ENABLE_ADDRESS,
                         &ThreadEnable,
                         0,
                         NULL);

      CoreThreads = (UINT8) (ThreadEnable.Field.ThreadEn & 0xFF);
      if (CoreThreads != 0) {
        ActiveThreadMap = 0xBEEFBEEFBEEFBEEFull;
        ThreadBit = 0x80;
        while ((ThreadBit & CoreThreads) == 0) {
          ActiveThreadMap = RShiftU64 (ActiveThreadMap, 8);
          ThreadBit = ThreadBit >> 1;
        }
      }
      IDS_HDT_CONSOLE (MAIN_FLOW, "ActiveThreadMap = 0x%x\n", ActiveThreadMap);

      // Call BIOSSMC_MSG_AcBtcStartCal [ARG = i]
      NbioHandle = NbioGetHandle (Pcie);
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = AcBtcIndex;
      SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_AcBtcStartCal, SmuArg, 0);


      // Write to monitored address to start APs executing workload.
      // Assembly code on APs will exit MWAIT when this write occurs
      ApTaskToRun = AcBtcIndex;

      // Execute workload code on BSP
      ExecuteF17RvBtc ((UINT64)AcBtcIndex, (UINT64)WorkloadBuffer);

      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_AcBtcStopCal, SmuArg, 0);
    }

    NbioHandle = NbioGetHandle (Pcie);
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_AcBtcEndCal, SmuArg, 0);
    //
    // Step 5. Release all others AP.
    //  AfterBtc();  ////EGH I am not sure what this is supposed to  - probably same as CZ - transition to Pstate 0 and IdleAllAps
  }

  if (PcdGet8 (PcdDcBtc)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "DcBtc \n");

    NbioHandle = NbioGetHandle (Pcie);
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_DcBtc, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
  }

  if ((FEATURE_CORE_CSTATES_MASK & PcdGet32 (PcdSmuFeatureControlDefinesExt)) == FEATURE_CORE_CSTATES_MASK) {
    NbioHandle = NbioGetHandle (Pcie);
    //
    // Update PcdSmuFeatureControlDefines value from CBS.
    //
    SmuArg[0] = 0;
    SmuArg[1] = (FEATURE_CORE_CSTATES_MASK & PcdGet32 (PcdSmuFeatureControlDefinesExt));
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_EnableSmuFeatures, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    IDS_HDT_CONSOLE (MAIN_FLOW, "AllSmuFeatureControlDefines = 0x%x\n", SmuArg);
    IDS_HDT_CONSOLE (MAIN_FLOW, "Status = 0x%x\n", Status);
  }
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);

  IDS_HDT_CONSOLE (MAIN_FLOW, "Callback Ac Btc End\n");

}

