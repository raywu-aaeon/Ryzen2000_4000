/* $NoKeywords:$ */
/**
 * @file
 *
 * Gather Pstate Data Services.
 *
 * Contains code that Pstate Gather Data
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
 * @e \$Revision$   @e \$Date$
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
#include <Library/BaseLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <AGESA.h>
#include <Filecode.h>
#include <cpuRegisters.h>
#include <CcxRegistersRv.h>
#include <GnbDxio.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>
#include <Library/CcxPstatesLib.h>
#include <Library/GnbLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/BaseCoreLogicalIdLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/AmdIdsHookLib.h>
#include <Protocol/AmdAcpiCpuSsdtServicesProtocol.h>
#include <Protocol/AmdAcpiCratServicesProtocol.h>
#include <Protocol/AmdAcpiSratServicesProtocol.h>
#include <Protocol/AmdCoreTopologyProtocol.h>
#include <Protocol/FabricNumaServicesProtocol.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/AmdNbioSmuServicesProtocol.h>

#define FILECODE CCX_ZEN_CCXZENRVDXE_CCXZENRVACPISERVICESDXE_FILECODE

/// TLB type
typedef enum {
  TLB_2M = 0,       ///< 0 - TLB 2M4M associativity
  TLB_4K,           ///< 1 - TLB 4K associativity
  TLB_1G,           ///< 2 - TLB 1G associativity
  TLB_TYPE_MAX,     ///< MaxValue
} TLB_TYPE;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
CcxZenRvPStateGatherData (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_PSTATE_SYS_INFO                   **PstateSysInfoPtr
  );

AGESA_STATUS
CcxZenRvGetPstateTransLatency (
     OUT   UINT32                                 *TransitionLatency,
  IN       AMD_CONFIG_PARAMS                      *StdHeader
  );

EFI_STATUS
EFIAPI
CcxZenRvGetCStateInfo (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_CSTATE_INFO                       **CstateInfo
  );

UINT32
EFIAPI
CcxZenRvGetPsdDomain (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       UINT8                                   LocalApicId
  );

EFI_STATUS
EFIAPI
CcxZenRvGetPStatePower (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       CCX_PSTATE                             Pstate,
     OUT   UINTN                                  *PowerInmW
  );

EFI_STATUS
EFIAPI
CcxZenRvGetCratHsaProcEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

EFI_STATUS
EFIAPI
CcxZenRvGetCratCacheEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

EFI_STATUS
EFIAPI
CcxZenRvGetCratTlbEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

EFI_STATUS
EFIAPI
CcxZenRvCreateSratLapic (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

EFI_STATUS
EFIAPI
CcxZenRvCreateSratX2Apic (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

STATIC
UINT8
CcxZenRvCalcLocalApic (
  IN       UINTN    Socket,
  IN       UINTN    Die,
  IN       UINTN    Complex,
  IN       UINTN    Core,
  IN       UINTN    Thread
  );

UINT8 *
AddOneCratEntry (
  IN       CRAT_ENTRY_TYPE    CratEntryType,
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd
  );

UINT8
GetCacheAssoc (
  IN       UINT16   RawAssoc
  );

UINT8
GetTlbSize (
  IN       TLB_TYPE   TLB_TYPE,
  IN       CRAT_TLB  *CratTlbEntry,
  IN       UINT16     RawAssocSize
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL   mZenRvSsdtServicesProtocol = {
  0,
  CcxZenRvPStateGatherData,
  CcxZenRvGetCStateInfo,
  CcxZenRvGetPsdDomain,
  CcxZenRvGetPStatePower
};

STATIC AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL   mZenRvCratServicesProtocol = {
  0,
  CcxZenRvGetCratHsaProcEntry,
  CcxZenRvGetCratCacheEntry,
  CcxZenRvGetCratTlbEntry
};

STATIC AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL   mZenRvSratServicesProtocol = {
  1,
  CcxZenRvCreateSratLapic,
  CcxZenRvCreateSratX2Apic
};

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
CcxZenRvAcpiCpuSsdtServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Install ACPI CPU SSDT services protocol
  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdAcpiCpuSsdtServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mZenRvSsdtServicesProtocol
                );
}

EFI_STATUS
EFIAPI
CcxZenRvCratServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Install ACPI CPU CRAT services protocol
  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdCcxAcpiCratServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mZenRvCratServicesProtocol
                );
}

EFI_STATUS
EFIAPI
CcxZenRvSratServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Install ACPI CPU SRAT services protocol
  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdCcxAcpiSratServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mZenRvSratServicesProtocol
                );
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL
 *----------------------------------------------------------------------------------------
 */

/**
 *---------------------------------------------------------------------------------------
 *
 *  PStateGatherData
 *
 *  Description:
 *    This function will gather PState information from the MSRs and fill up the
 *    pStateBuf. This buffer will be used by the PState Leveling, and PState Table
 *    generation code later.
 *
 *  Parameters:
 *    @param[in]  This                                 A pointer to the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL instance.
 *    @param[out] PstateSysInfoPtr                     Contains Pstate information for whole system
 *
 *    @retval     AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
EFIAPI
CcxZenRvPStateGatherData (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_PSTATE_SYS_INFO                   **PstateSysInfoPtr
  )
{
  UINT32                  LApicIdLoop;
  UINT32                  TableSize;
  UINT32                  PstateLoop;
  UINT32                  TotalEnabledPStates;
  UINTN                   NumberOfComplexes;
  UINTN                   NumberOfCores;
  UINTN                   NumberOfThreads;
  UINTN                   ComplexeLoop;
  UINTN                   CoreLoop;
  UINTN                   ThreadLoop;
  UINTN                   LogicalCoreNum;
  UINTN                   MaxSwState;
  UINTN                   NumberOfBoostPstate;
  UINTN                   Frequency;
  UINTN                   VoltageInuV;
  UINTN                   PowerInmW;
  UINTN                   NumberOfSockets;
  UINTN                   NumberOfDies;
  UINTN                   SocketLoop;
  UINTN                   DieLoop;
  AMD_PSTATE_SOCKET_INFO *PstateSocketInfo;
  S_PSTATE_VALUES        *PstateStructure;
  ALLOCATE_HEAP_PARAMS    AllocHeapParams;
  EFI_STATUS              Status;
  AGESA_STATUS            AgesaStatus;
  AMD_CONFIG_PARAMS       StdHeader;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *CoreTopology;

  CcxGetPstateNumber (0, &NumberOfBoostPstate, &MaxSwState, &StdHeader);
  MaxSwState = MaxSwState - NumberOfBoostPstate;

  Status = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, &FabricTopology);
  ASSERT (!EFI_ERROR (Status));

  Status = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopology);
  ASSERT (!EFI_ERROR (Status));

  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) != EFI_SUCCESS) {
    return EFI_DEVICE_ERROR;
  }

  // Create Heap and store p-state data for ACPI table
  TableSize = (UINT32) (sizeof (AMD_PSTATE_SYS_INFO) + MultU64x64 ((MultU64x64 (MaxSwState, sizeof (S_PSTATE_VALUES)) + sizeof (AMD_PSTATE_SOCKET_INFO)), NumberOfSockets));

  AllocHeapParams.RequestedBufferSize = TableSize;
  AllocHeapParams.BufferHandle        = AMD_PSTATE_DATA_BUFFER_HANDLE;
  AllocHeapParams.Persist             = HEAP_SYSTEM_MEM;
  AgesaStatus = HeapAllocateBuffer (&AllocHeapParams, &StdHeader);
  ASSERT (AgesaStatus == AGESA_SUCCESS);
  if (AgesaStatus == AGESA_SUCCESS) {
    *PstateSysInfoPtr = (AMD_PSTATE_SYS_INFO *) AllocHeapParams.BufferPtr;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }

  (*PstateSysInfoPtr)->TotalSocketInSystem = (UINT8) NumberOfSockets;
  (*PstateSysInfoPtr)->SizeOfBytes    = TableSize;
  PstateSocketInfo = (*PstateSysInfoPtr)->PStateSocketStruct;

  for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
    // Calculate number of logical cores
    LogicalCoreNum = 0;
    LApicIdLoop = 0;
    if (FabricTopology->GetProcessorInfo (FabricTopology, SocketLoop, &NumberOfDies, NULL) == EFI_SUCCESS) {
      for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
        if (CoreTopology->GetCoreTopologyOnDie (CoreTopology, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads) == EFI_SUCCESS) {
          LogicalCoreNum += NumberOfComplexes * NumberOfCores * NumberOfThreads;
          for (ComplexeLoop = 0; ComplexeLoop < NumberOfComplexes; ComplexeLoop++) {
            for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
              for (ThreadLoop = 0; ThreadLoop < NumberOfThreads; ThreadLoop++) {
                PstateSocketInfo->LocalApicId[LApicIdLoop] = CcxZenRvCalcLocalApic (SocketLoop, DieLoop, ComplexeLoop, CoreLoop, ThreadLoop);
                LApicIdLoop++;
              }
            }
          }
        }
      }
    }

    PstateSocketInfo->SocketNumber        = (UINT8) SocketLoop;
    PstateSocketInfo->TotalLogicalCores   = (UINT8) LogicalCoreNum;
    PstateSocketInfo->CreateAcpiTables    = TRUE;
    PstateSocketInfo->PStateMaxValue      = (UINT8) MaxSwState;

    // Get transition latency
    CcxZenRvGetPstateTransLatency (&(PstateSocketInfo->TransitionLatency), &StdHeader);

    // Get IsPsdDependent
    // Family 17h defaults to dependent PSD
    switch (PcdGet8 (PcdAmdAgesaPstatePolicy)) {
    case 0:
      PstateSocketInfo->IsPsdDependent = FALSE;
      break;
    case 1:
      PstateSocketInfo->IsPsdDependent = TRUE;
      break;
    case 2:
      PstateSocketInfo->IsPsdDependent = FALSE;
      break;
    default:
      ASSERT (FALSE);
      break;
    }

    PstateStructure = PstateSocketInfo->PStateStruct;
    TotalEnabledPStates = 0;

    for (PstateLoop = 0; PstateLoop <= MaxSwState; PstateLoop++) {

      LibAmdMemFill (PstateStructure, 0, sizeof (S_PSTATE_VALUES), &StdHeader);

      if (CcxGetPstateInfo (0, (SwPstate0 + PstateLoop), &Frequency, &VoltageInuV, &PowerInmW, &StdHeader)) {
        PstateStructure->CoreFreq       = (UINT32) Frequency;
        PstateStructure->Power          = (UINT32) PowerInmW;
        PstateStructure->SwPstateNumber = PstateLoop;
        PstateStructure->PStateEnable   = 1;
        PstateStructure++;
        TotalEnabledPStates++;
      }
    } // for (PstateLoop = 0; PstateLoop < MaxState; PstateLoop++)

    // Don't create ACPI Tables if there is one or less than one PState is enabled
    if (TotalEnabledPStates <= 1) {
      PstateSocketInfo->CreateAcpiTables = FALSE;
    }

    PstateSocketInfo = (AMD_PSTATE_SOCKET_INFO *) ((UINT8 *) PstateSocketInfo + sizeof (AMD_PSTATE_SOCKET_INFO) + sizeof (S_PSTATE_VALUES) * MaxSwState);
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Family specific call to get Pstate Transition Latency.
 *
 *  Calculate TransitionLatency by Gaters On/Off Time value and pll value.
 *
 *  @param[out]    TransitionLatency                 The transition latency.
 *  @param[in]     StdHeader                         Header for library and services
 *
 *  @retval        AGESA_SUCCESS Always succeeds.
 */
AGESA_STATUS
CcxZenRvGetPstateTransLatency (
     OUT   UINT32                                 *TransitionLatency,
  IN       AMD_CONFIG_PARAMS                      *StdHeader
  )
{
  *TransitionLatency = 0;

  return (AGESA_SUCCESS);
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  CcxZenRvGetCStateInfo
 *
 *  Description:
 *    This function will gather CState information
 *
 *  Parameters:
 *    @param[in]  This                                 A pointer to the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL instance.
 *    @param[out] CstateInfo                           Contains Cstate information
 *
 *    @retval     AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
EFIAPI
CcxZenRvGetCStateInfo (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_CSTATE_INFO                       **CstateInfo
  )
{
  CPUID_DATA                          CpuId;
  AGESA_STATUS                        AgesaStatus;
  ALLOCATE_HEAP_PARAMS                AllocHeapParams;
  SOC_LOGICAL_ID                      LogicalId;
  EFI_STATUS                          Status;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *NbioSmuServices;
  UINT32                              SmuArg[6];
  UINT32                              SmuReturn[6];
  BOOLEAN                             SmuFwOsC3Enable;
  UINT16                              C1Latency;
  UINT16                              C2Latency;
  UINT16                              C3Latency;

  AllocHeapParams.RequestedBufferSize = sizeof (AMD_CSTATE_INFO);
  AllocHeapParams.BufferHandle        = AMD_CSTATE_DATA_BUFFER_HANDLE;
  AllocHeapParams.Persist             = HEAP_SYSTEM_MEM;
  AgesaStatus = HeapAllocateBuffer (&AllocHeapParams, NULL);
  ASSERT (AgesaStatus == AGESA_SUCCESS);
  if (AgesaStatus == AGESA_SUCCESS) {
    *CstateInfo = (AMD_CSTATE_INFO *) AllocHeapParams.BufferPtr;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }

  // Is Cstate enabled
  if ((PcdGet8 (PcdAmdCStateMode) != 1) ||
      (PcdGet16 (PcdAmdCStateIoBaseAddress) == 0)) {
    (*CstateInfo)->IsCstateEnabled = FALSE;
  } else {
    (*CstateInfo)->IsCstateEnabled = TRUE;
  }

  // Io Cstate address
  (*CstateInfo)->IoCstateAddr = (UINT32) PcdGet16 (PcdAmdCStateIoBaseAddress);

  // Is _CSD generated
  AsmCpuidEx (
      0x8000001D,
      0,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  (*CstateInfo)->IsCsdGenerated = (((CpuId.EAX_Reg >> 14) & 0xFFF) == 0) ? FALSE : TRUE;

  (*CstateInfo)->IsMonitorMwaitSupported = TRUE;

  (*CstateInfo)->C1Latency = 1;

  (*CstateInfo)->C2Latency = 400;

  (*CstateInfo)->C3Latency = 0;

  BaseGetLogicalIdOnExecutingCore (&LogicalId);
  // Only supported for PIC
  if ((LogicalId.Family == AMD_FAMILY_17_PIC) && ((LogicalId.Revision & AMD_REV_F17_PIC_ALL) != 0)) {
    // AGESA should only create C3 state if SMU FW supports it. We need to send the EnableSmuFeature message
    // to SMU FW first, to get the return argument which indicates whether the feature is supported.
    Status = gBS->LocateProtocol (&gAmdNbioSmuServicesProtocolGuid, NULL, &NbioSmuServices);
    ASSERT (!EFI_ERROR (Status));

    LibAmdMemFill (SmuArg, 0x00, 24, NULL);
    LibAmdMemFill (SmuReturn, 0x00, 24, NULL);

    if (PcdGetBool (PcdAmdAcpiCstC3)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  PcdAmdAcpiCstC3 enabled\n");
      SmuArg[1] = 0x00004000;
    }

    NbioSmuServices->AmdSmuServiceRequest (NbioSmuServices, 0, SMC_MSG_EnableSmuFeatures, SmuArg, SmuReturn);
    SmuFwOsC3Enable = (((SmuReturn[1] >> 14) & 0x1) == 1) ? TRUE : FALSE;

    IDS_HDT_CONSOLE (CPU_TRACE, "  SmuFwOsC3Enable %X\n", SmuFwOsC3Enable);
    if (PcdGetBool (PcdAmdAcpiCstC3) && SmuFwOsC3Enable) {
      C1Latency = PcdGet16 (PcdAmdAcpiCpuCstC1Latency);
      IDS_HOOK (IDS_HOOK_C1_LATENCY, NULL, (VOID *) &C1Latency);
      (*CstateInfo)->C1Latency = C1Latency;

      C2Latency = PcdGet16 (PcdAmdAcpiCpuCstC2Latency);
      IDS_HOOK (IDS_HOOK_C2_LATENCY, NULL, (VOID *) &C2Latency);
      (*CstateInfo)->C2Latency = C2Latency;

      C3Latency = PcdGet16 (PcdAmdAcpiCpuCstC3Latency);
      IDS_HOOK (IDS_HOOK_C3_LATENCY, NULL, (VOID *) &C3Latency);
      (*CstateInfo)->C3Latency = C3Latency;

      IDS_HDT_CONSOLE (CPU_TRACE, "  Created C3 object with latency %X\n", C3Latency);
    }
  }

  return EFI_SUCCESS;
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  CcxZenRvGetPsdDomain
 *
 *  Description:
 *    This function will return PSD domain for independency
 *
 *  Parameters:
 *    @param[in]  This                                 A pointer to the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL instance.
 *    @param[in]  LocalApicId                          Local APIC ID
 *
 *    @retval     AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
UINT32
EFIAPI
CcxZenRvGetPsdDomain (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       UINT8                                   LocalApicId
  )
{
  UINT8  ThreadsPerCore;

  ThreadsPerCore = CcxGetThreadsPerCore ();
  ASSERT (ThreadsPerCore != 0);

  return ((UINT32) (LocalApicId / ThreadsPerCore));
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  CcxZenRvGetPStatePower
 *
 *  Description:
 *    This function will return the Power in mW for specified PState
 *
 *  Parameters:
 *    @param[in]  This                    Pointer to the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL instance.
 *    @param[in]  Pstate                  PState to read
 *    @param[out] PowerInmW               Power in mW of the specified PState
 *
 *    @retval     EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
EFIAPI
CcxZenRvGetPStatePower (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       CCX_PSTATE                             Pstate,
     OUT   UINTN                                  *PowerInmW
  )
{
  UINT32    CpuVid;
  UINT32    IddValue;
  UINT32    IddDiv;
  UINT32    PstateNumber;
  UINTN     VoltageInuV;
  PSTATE_MSR  PstateMsr;

  PstateNumber = Pstate < HwPstate0 ? (UINT32) Pstate : (UINT32) Pstate - HwPstate0;
  PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + PstateNumber);

  if (PstateMsr.Field.PstateEn == 0) {
    return FALSE;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvGetPStatePower - P%d\n", PstateNumber);

  CpuVid   = (UINT32) PstateMsr.Field.CpuVid;
  IddValue = (UINT32) PstateMsr.Field.IddValue;
  IddDiv   = (UINT32) PstateMsr.Field.IddDiv;

  // Voltage
  if ((CpuVid >= 0xF8) && (CpuVid <= 0xFF)) {
    VoltageInuV = 0;
  } else {
    VoltageInuV = 1550000L - (6250 * CpuVid);
  }

  // PowerInmW
  *PowerInmW = (VoltageInuV) / 10 * IddValue;

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


/*----------------------------------------------------------------------------------------
 *                          AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL
 *----------------------------------------------------------------------------------------
 */

/**
 * This service retrieves CRAT information about the HSA.
 *
 * @param[in]      This                             A pointer to the
 *                                                  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL instance.
 * @param[in]      CratHeaderStructPtr              CRAT table structure pointer
 * @param[in, out] TableEnd                         Point to the end of this table
 *
 * @retval EFI_SUCCESS                              The HSA processor information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CratHsaProcInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
CcxZenRvGetCratHsaProcEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  )
{
  UINTN                SocketLoop;
  UINTN                DieLoop;
  UINTN                NumberOfSockets;
  UINTN                NumberOfDies;
  UINTN                NumberOfComplexes;
  UINTN                NumberOfCores;
  UINTN                NumberOfThreads;
  UINT32               Domain;
  UINT32               PreDomain;
  EFI_STATUS           CalledStatus;
  CRAT_HSA_PROCESSING_UNIT *CratHsaEntry;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL    *CoreTopologyServices;
  FABRIC_NUMA_SERVICES_PROTOCOL          *FabricNuma;

  // Locate Fabric CRAT Services Protocol
  if (gBS->LocateProtocol (&gAmdFabricNumaServicesProtocolGuid, NULL, (VOID **) &FabricNuma) != EFI_SUCCESS) {
    return EFI_ABORTED;
  }

  // Locate FabricTopologyServices2Protocol
  CalledStatus = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  ASSERT (!EFI_ERROR (CalledStatus));

  CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);
  ASSERT (!EFI_ERROR (CalledStatus));

  PreDomain = 0;
  CratHsaEntry = NULL;
  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) == EFI_SUCCESS) {
    for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
      if (FabricTopology->GetProcessorInfo (FabricTopology, SocketLoop, &NumberOfDies, NULL) == EFI_SUCCESS) {
        for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
          if (FabricNuma->DomainXlat (FabricNuma, SocketLoop, DieLoop, &Domain) ==  EFI_SUCCESS) {
            if ((Domain != PreDomain) || (Domain == 0)) {
              CratHsaEntry = (CRAT_HSA_PROCESSING_UNIT *) AddOneCratEntry (CRAT_HSA_PROC_UNIT_TYPE, CratHeaderStructPtr, TableEnd);
              CratHsaEntry->Flags.Enabled    = 1;
              CratHsaEntry->Flags.CpuPresent = 1;
              CratHsaEntry->ProximityNode    = Domain;
              CratHsaEntry->ProcessorIdLow   = (SocketLoop, DieLoop, 0, 0, 0);
              CratHsaEntry->NumCPUCores      = 0;
              CratHsaEntry->WaveFrontSize    = 4;
              PreDomain = Domain;
            }
            CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
            CratHsaEntry->NumCPUCores += (UINT16) (NumberOfComplexes * NumberOfCores * NumberOfThreads);
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}

/**
 * This service retrieves information about the cache.
 *
 * @param[in]      This                             A pointer to the
 *                                                  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL instance.
 * @param[in]      CratHeaderStructPtr              CRAT table structure pointer
 * @param[in, out] TableEnd                         Point to the end of this table
 *
 * @retval EFI_SUCCESS                              The cache information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CratCacheInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
CcxZenRvGetCratCacheEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  )
{
  UINT8                i;
  UINT8                ApicId;
  UINT8                SiblingMapMask;
  UINT32               NumOfThreadsSharing;
  UINT32               TotalThreads;
  UINTN                SocketLoop;
  UINTN                DieLoop;
  UINTN                ComplexLoop;
  UINTN                CoreLoop;
  UINTN                ThreadsLoop;
  UINTN                NumberOfSockets;
  UINTN                NumberOfDies;
  UINTN                NumberOfComplexes;
  UINTN                NumberOfCores;
  UINTN                NumberOfThreads;
  CPUID_DATA           CpuId;
  EFI_STATUS           CalledStatus;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *CoreTopologyServices;
  CRAT_CACHE          *CratCacheEntry;

  // Locate FabricTopologyServices2Protocol
  CalledStatus = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  ASSERT (!EFI_ERROR (CalledStatus));

  CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);
  ASSERT (!EFI_ERROR (CalledStatus));

  TotalThreads = 0;
  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) == EFI_SUCCESS) {
    for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
      if (FabricTopology->GetProcessorInfo (FabricTopology, SocketLoop, &NumberOfDies, NULL) == EFI_SUCCESS) {
        for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
          if (CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads) == EFI_SUCCESS) {
            for (ComplexLoop = 0; ComplexLoop < NumberOfComplexes; ComplexLoop++) {
              for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
                for (ThreadsLoop = 0; ThreadsLoop < NumberOfThreads; ThreadsLoop++) {
                  ApicId = CcxZenRvCalcLocalApic (SocketLoop, DieLoop, ComplexLoop, CoreLoop, ThreadsLoop);

                  // L1 Data cache
                  AsmCpuidEx (0x8000001D, 0, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratCacheEntry = (CRAT_CACHE *) AddOneCratEntry (CRAT_CACHE_TYPE, CratHeaderStructPtr, TableEnd);
                    CratCacheEntry->Flags.Enabled   = 1;
                    CratCacheEntry->Flags.CpuCache  = 1;
                    CratCacheEntry->Flags.DataCache = 1;
                    CratCacheEntry->ProcessorIdLow  = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratCacheEntry->SiblingMap[i]   = SiblingMapMask << (TotalThreads % 8);
                    CratCacheEntry->CacheProperties = (((CpuId.EDX_Reg >> 1) & 1) == 0) ? 0 : 2;
                    AsmCpuid (AMD_CPUID_TLB_L1Cache, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratCacheEntry->CacheSize       = CpuId.ECX_Reg >> 24;
                    CratCacheEntry->CacheLevel      = L1_CACHE;
                    CratCacheEntry->LinesPerTag     = (CpuId.ECX_Reg >> 8) & 0xFF;
                    CratCacheEntry->CacheLineSize   = CpuId.ECX_Reg & 0xFF;
                    CratCacheEntry->Associativity   = (CpuId.ECX_Reg >> 16) & 0xFF;
                    CratCacheEntry->CacheLatency    = 1;
                  }

                  // L1 Instruction cache
                  AsmCpuidEx (0x8000001D, 1, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratCacheEntry = (CRAT_CACHE *) AddOneCratEntry (CRAT_CACHE_TYPE, CratHeaderStructPtr, TableEnd);
                    CratCacheEntry->Flags.Enabled   = 1;
                    CratCacheEntry->Flags.CpuCache  = 1;
                    CratCacheEntry->Flags.InstructionCache = 1;
                    CratCacheEntry->ProcessorIdLow  = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratCacheEntry->SiblingMap[i]   = SiblingMapMask << (TotalThreads % 8);
                    CratCacheEntry->CacheProperties = (((CpuId.EDX_Reg >> 1) & 1) == 0) ? 0 : 2;
                    AsmCpuid (AMD_CPUID_TLB_L1Cache, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratCacheEntry->CacheSize       = CpuId.EDX_Reg >> 24;
                    CratCacheEntry->CacheLevel      = L1_CACHE;
                    CratCacheEntry->LinesPerTag     = (CpuId.EDX_Reg >> 8) & 0xFF;
                    CratCacheEntry->CacheLineSize   = CpuId.EDX_Reg & 0xFF;
                    CratCacheEntry->Associativity   = (CpuId.EDX_Reg >> 16) & 0xFF;
                    CratCacheEntry->CacheLatency    = 1;
                  }

                  // L2 cache
                  AsmCpuidEx (0x8000001D, 2, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratCacheEntry = (CRAT_CACHE *) AddOneCratEntry (CRAT_CACHE_TYPE, CratHeaderStructPtr, TableEnd);
                    CratCacheEntry->Flags.Enabled   = 1;
                    CratCacheEntry->Flags.CpuCache  = 1;
                    CratCacheEntry->Flags.DataCache = 1;
                    CratCacheEntry->Flags.InstructionCache = 1;
                    CratCacheEntry->ProcessorIdLow  = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratCacheEntry->SiblingMap[i]   = SiblingMapMask << (TotalThreads % 8);
                    CratCacheEntry->CacheProperties = (((CpuId.EDX_Reg >> 1) & 1) == 0) ? 0 : 2;
                    AsmCpuid (AMD_CPUID_L2L3Cache_L2TLB, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratCacheEntry->CacheSize       = CpuId.ECX_Reg >> 16;
                    CratCacheEntry->CacheLevel      = L2_CACHE;
                    CratCacheEntry->LinesPerTag     = (CpuId.ECX_Reg >> 8) & 0xF;
                    CratCacheEntry->CacheLineSize   = CpuId.ECX_Reg & 0xFF;
                    CratCacheEntry->Associativity   = GetCacheAssoc ((CpuId.ECX_Reg >> 12) & 0xF);
                    CratCacheEntry->CacheLatency    = 1;
                  }

                  // L3 cache
                  AsmCpuidEx (0x8000001D, 3, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratCacheEntry = (CRAT_CACHE *) AddOneCratEntry (CRAT_CACHE_TYPE, CratHeaderStructPtr, TableEnd);
                    CratCacheEntry->Flags.Enabled   = 1;
                    CratCacheEntry->Flags.CpuCache  = 1;
                    CratCacheEntry->Flags.DataCache = 1;
                    CratCacheEntry->Flags.InstructionCache = 1;
                    CratCacheEntry->ProcessorIdLow  = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratCacheEntry->SiblingMap[i]   = SiblingMapMask << (TotalThreads % 8);
                    CratCacheEntry->CacheProperties = (((CpuId.EDX_Reg >> 1) & 1) == 0) ? 0 : 2;
                    AsmCpuid (AMD_CPUID_L2L3Cache_L2TLB, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratCacheEntry->CacheSize       = (CpuId.EDX_Reg >> 18) * 512;
                    CratCacheEntry->CacheLevel      = L3_CACHE;
                    CratCacheEntry->LinesPerTag     = (CpuId.EDX_Reg >> 8) & 0xF;
                    CratCacheEntry->CacheLineSize   = CpuId.EDX_Reg & 0xFF;
                    CratCacheEntry->Associativity   = GetCacheAssoc ((CpuId.EDX_Reg >> 12) & 0xF);
                    CratCacheEntry->CacheLatency    = 1;
                  }

                  TotalThreads++;
                }
              }
            }
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}

/**
 * This service retrieves information about the TLB.
 *
 * @param[in]      This                             A pointer to the
 *                                                  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL instance.
 * @param[in]      CratHeaderStructPtr              CRAT table structure pointer
 * @param[in, out] TableEnd                         Point to the end of this table
 *
 * @retval EFI_SUCCESS                              The TLB information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CratTlbInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
CcxZenRvGetCratTlbEntry (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  )
{
  UINT8                i;
  UINT8                ApicId;
  UINT8                SiblingMapMask;
  UINT32               NumOfThreadsSharing;
  UINT32               TotalThreads;
  UINTN                SocketLoop;
  UINTN                DieLoop;
  UINTN                ComplexLoop;
  UINTN                CoreLoop;
  UINTN                ThreadsLoop;
  UINTN                NumberOfSockets;
  UINTN                NumberOfDies;
  UINTN                NumberOfComplexes;
  UINTN                NumberOfCores;
  UINTN                NumberOfThreads;
  CPUID_DATA           CpuId;
  EFI_STATUS           CalledStatus;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *CoreTopologyServices;
  CRAT_TLB            *CratTlbEntry;

  // Locate FabricTopologyServices2Protocol
  CalledStatus = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  ASSERT (!EFI_ERROR (CalledStatus));

  CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);
  ASSERT (!EFI_ERROR (CalledStatus));

  TotalThreads = 0;
  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) == EFI_SUCCESS) {
    for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
      if (FabricTopology->GetProcessorInfo (FabricTopology, SocketLoop, &NumberOfDies, NULL) == EFI_SUCCESS) {
        for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
          if (CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads) == EFI_SUCCESS) {
            for (ComplexLoop = 0; ComplexLoop < NumberOfComplexes; ComplexLoop++) {
              for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
                for (ThreadsLoop = 0; ThreadsLoop < NumberOfThreads; ThreadsLoop++) {
                  ApicId = CcxZenRvCalcLocalApic (SocketLoop, DieLoop, ComplexLoop, CoreLoop, ThreadsLoop);

                  // L1 Data TLB
                  AsmCpuidEx (0x8000001D, 0, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratTlbEntry = (CRAT_TLB *) AddOneCratEntry (CRAT_TLB_TYPE, CratHeaderStructPtr, TableEnd);
                    CratTlbEntry->Flags.Enabled     = 1;
                    CratTlbEntry->Flags.DataTLB     = 1;
                    CratTlbEntry->Flags.CpuTLB      = 1;
                    CratTlbEntry->ProcessorIdLow    = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratTlbEntry->SiblingMap[i]     = SiblingMapMask << (TotalThreads % 8);
                    CratTlbEntry->TlbLevel          = L1_CACHE;
                    AsmCpuid (AMD_CPUID_TLB_L1Cache, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->DataTlbAssociativity2MB = CpuId.EAX_Reg >> 24;
                    CratTlbEntry->DataTlbSize2MB    = GetTlbSize (TLB_2M, CratTlbEntry, ((CpuId.EAX_Reg >> 16) & 0xFF));
                    CratTlbEntry->DTLB4KAssoc       = CpuId.EBX_Reg >> 24;
                    CratTlbEntry->DTLB4KSize        = GetTlbSize (TLB_4K, CratTlbEntry, ((CpuId.EBX_Reg >> 16) & 0xFF));
                    AsmCpuid (AMD_CPUID_L1L2Tlb1GIdentifiers, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->DTLB1GAssoc       = CpuId.EAX_Reg >> 28;
                    CratTlbEntry->DTLB1GSize        = GetTlbSize (TLB_1G, CratTlbEntry, ((CpuId.EAX_Reg >> 16) & 0xFFF));
                  }

                  // L1 Instruction TLB
                  AsmCpuidEx (0x8000001D, 1, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratTlbEntry = (CRAT_TLB *) AddOneCratEntry (CRAT_TLB_TYPE, CratHeaderStructPtr, TableEnd);
                    CratTlbEntry->Flags.Enabled     = 1;
                    CratTlbEntry->Flags.InstructionTLB = 1;
                    CratTlbEntry->Flags.CpuTLB      = 1;
                    CratTlbEntry->ProcessorIdLow    = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratTlbEntry->SiblingMap[i]     = SiblingMapMask << (TotalThreads % 8);
                    CratTlbEntry->TlbLevel          = L1_CACHE;
                    AsmCpuid (AMD_CPUID_TLB_L1Cache, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->InstructionTlbAssociativity2MB = (CpuId.EAX_Reg >> 8) & 0xFF;
                    CratTlbEntry->InstructionTlbSize2MB = GetTlbSize (TLB_2M, CratTlbEntry, (CpuId.EAX_Reg & 0xFF));
                    CratTlbEntry->ITLB4KAssoc       = (CpuId.EBX_Reg >> 8) & 0xFF;
                    CratTlbEntry->ITLB4KSize        = GetTlbSize (TLB_4K, CratTlbEntry, (CpuId.EBX_Reg & 0xFF));
                    AsmCpuid (AMD_CPUID_L1L2Tlb1GIdentifiers, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->ITLB1GAssoc       = (CpuId.EAX_Reg >> 12) & 0xF;
                    CratTlbEntry->ITLB1GSize        = GetTlbSize (TLB_1G, CratTlbEntry, (CpuId.EAX_Reg & 0xFFF));
                  }

                  // L2 Data TLB
                  AsmCpuidEx (0x8000001D, 2, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratTlbEntry = (CRAT_TLB *) AddOneCratEntry (CRAT_TLB_TYPE, CratHeaderStructPtr, TableEnd);
                    CratTlbEntry->Flags.Enabled     = 1;
                    CratTlbEntry->Flags.DataTLB     = 1;
                    CratTlbEntry->Flags.CpuTLB      = 1;
                    CratTlbEntry->ProcessorIdLow    = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratTlbEntry->SiblingMap[i]     = SiblingMapMask << (TotalThreads % 8);
                    CratTlbEntry->TlbLevel          = L2_CACHE;
                    AsmCpuid (AMD_CPUID_L2L3Cache_L2TLB, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->DataTlbAssociativity2MB = CpuId.EAX_Reg >> 28;
                    CratTlbEntry->DataTlbSize2MB    = GetTlbSize (TLB_2M, CratTlbEntry, ((CpuId.EAX_Reg >> 16) & 0xFFF));
                    CratTlbEntry->DTLB4KAssoc       = GetCacheAssoc (CpuId.EBX_Reg >> 28);
                    CratTlbEntry->DTLB4KSize        = GetTlbSize (TLB_4K, CratTlbEntry, ((CpuId.EBX_Reg >> 16) & 0xFFF));
                    AsmCpuid (AMD_CPUID_L1L2Tlb1GIdentifiers, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->DTLB1GAssoc       = GetCacheAssoc (CpuId.EBX_Reg >> 28);
                    CratTlbEntry->DTLB1GSize        = GetTlbSize (TLB_1G, CratTlbEntry, ((CpuId.EAX_Reg >> 16) & 0xFFF));
                  }

                  // L2 Instruction TLB
                  AsmCpuidEx (0x8000001D, 2, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                  NumOfThreadsSharing = (((CpuId.EAX_Reg >> 14) & 0xFFF) + 1);
                  if ((TotalThreads % NumOfThreadsSharing) == 0) {
                    CratTlbEntry = (CRAT_TLB *) AddOneCratEntry (CRAT_TLB_TYPE, CratHeaderStructPtr, TableEnd);
                    CratTlbEntry->Flags.Enabled     = 1;
                    CratTlbEntry->Flags.InstructionTLB = 1;
                    CratTlbEntry->Flags.CpuTLB      = 1;
                    CratTlbEntry->ProcessorIdLow    = ApicId;
                    SiblingMapMask = 1;
                    for (i = 1; i < NumOfThreadsSharing; i++) {
                      SiblingMapMask = (SiblingMapMask << 1) + 1;
                    }
                    i = (UINT8) (TotalThreads / 8);
                    CratTlbEntry->SiblingMap[i]     = SiblingMapMask << (TotalThreads % 8);
                    CratTlbEntry->TlbLevel          = L2_CACHE;
                    AsmCpuid (AMD_CPUID_L2L3Cache_L2TLB, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->InstructionTlbAssociativity2MB = GetCacheAssoc ((CpuId.EAX_Reg >> 12) & 0xF);
                    CratTlbEntry->InstructionTlbSize2MB = GetTlbSize (TLB_2M, CratTlbEntry, (CpuId.EAX_Reg & 0xFFF));
                    CratTlbEntry->ITLB4KAssoc       = GetCacheAssoc ((CpuId.EBX_Reg >> 12) & 0xF);
                    CratTlbEntry->ITLB4KSize        = GetTlbSize (TLB_4K, CratTlbEntry, (CpuId.EBX_Reg & 0xFFF));
                    AsmCpuid (AMD_CPUID_L1L2Tlb1GIdentifiers, &(CpuId.EAX_Reg), &(CpuId.EBX_Reg), &(CpuId.ECX_Reg), &(CpuId.EDX_Reg));
                    CratTlbEntry->ITLB1GAssoc       = GetCacheAssoc ((CpuId.EBX_Reg >> 12) & 0xF);
                    CratTlbEntry->ITLB1GSize        = GetTlbSize (TLB_1G, CratTlbEntry, (CpuId.EBX_Reg & 0xFFF));
                  }

                  // No L3 TLB

                  TotalThreads++;
                }
              }
            }
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------
 *                          AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL
 *----------------------------------------------------------------------------------------
 */

/**
 * This service create SRAT Local APIC structure
 *
 * @param[in]      This                             A pointer to the
 *                                                  AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL instance.
 * @param[in]      SratHeaderStructPtr              SRAT table structure pointer
 * @param[in, out] TableEnd                         Point to the end of this table
 *
 * @retval EFI_SUCCESS                              The LAPIC was successfully created.
 *
 **/
EFI_STATUS
EFIAPI
CcxZenRvCreateSratLapic (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  )
{
  UINT8                ApicId;
  UINTN                SocketLoop;
  UINTN                DieLoop;
  UINTN                ComplexLoop;
  UINTN                CoreLoop;
  UINTN                ThreadsLoop;
  UINTN                NumberOfSockets;
  UINTN                NumberOfDies;
  UINTN                NumberOfComplexes;
  UINTN                NumberOfCores;
  UINTN                NumberOfThreads;
  UINT32               Domain;
  SRAT_APIC           *ApicEntry;
  EFI_STATUS           CalledStatus;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL    *CoreTopologyServices;
  FABRIC_NUMA_SERVICES_PROTOCOL          *FabricNuma;

  // Locate Fabric SRAT Services Protocol
  if (gBS->LocateProtocol (&gAmdFabricNumaServicesProtocolGuid, NULL, (VOID **) &FabricNuma) != EFI_SUCCESS) {
    return EFI_ABORTED;
  }

  // Locate FabricTopologyServices2Protocol
  CalledStatus = gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  ASSERT (!EFI_ERROR (CalledStatus));

  CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);
  ASSERT (!EFI_ERROR (CalledStatus));

  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) == EFI_SUCCESS) {
    for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
      if (FabricTopology->GetProcessorInfo (FabricTopology, SocketLoop, &NumberOfDies, NULL) == EFI_SUCCESS) {
        for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
          if (FabricNuma->DomainXlat (FabricNuma, SocketLoop, DieLoop, &Domain) ==  EFI_SUCCESS) {
            if (CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads) == EFI_SUCCESS) {
              for (ComplexLoop = 0; ComplexLoop < NumberOfComplexes; ComplexLoop++) {
                for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
                  for (ThreadsLoop = 0; ThreadsLoop < NumberOfThreads; ThreadsLoop++) {
                    ApicEntry = (SRAT_APIC *) *TableEnd;
                    *TableEnd += sizeof (SRAT_APIC);

                    ApicId = CcxZenRvCalcLocalApic (SocketLoop, DieLoop, ComplexLoop, CoreLoop, ThreadsLoop);

                    ApicEntry->Type = SRAT_LOCAL_APIC_TYPE;
                    ApicEntry->Length = sizeof (SRAT_APIC);
                    ApicEntry->ProximityDomain_7_0 = (UINT8) Domain & 0xFF;
                    ApicEntry->ProximityDomain_31_8[0] = (UINT8) ((Domain >> 8) & 0xFF);
                    ApicEntry->ProximityDomain_31_8[1] = (UINT8) ((Domain >> 16) & 0xFF);
                    ApicEntry->ProximityDomain_31_8[2] = (UINT8) ((Domain >> 24) & 0xFF);
                    ApicEntry->ApicId = ApicId;
                    ApicEntry->Flags.Enabled = 1;
                    ApicEntry->LocalSapicEid = 0;
                    ApicEntry->ClockDomain = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
CcxZenRvCreateSratX2Apic (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  )
{
  return EFI_SUCCESS;
}

STATIC
UINT8
CcxZenRvCalcLocalApic (
  IN       UINTN    Socket,
  IN       UINTN    Die,
  IN       UINTN    Complex,
  IN       UINTN    Core,
  IN       UINTN    Thread
  )
{
  UINT8  ThreadsPerCore;

  ThreadsPerCore = CcxGetThreadsPerCore ();
  ASSERT (Socket < 2);
  ASSERT (Die < 4);
  ASSERT (Complex < 2);
  ASSERT (Core < 4);
  ASSERT (ThreadsPerCore != 0);
  ASSERT (ThreadsPerCore <= 2);
  ASSERT (Thread < ThreadsPerCore);

  return (UINT8) ((Socket << 6) | (Die << 4) | (Complex << 3) | (Core * ThreadsPerCore) | Thread);
}

/*---------------------------------------------------------------------------------------*/
/**
* This function will add one CRAT entry.
*
*    @param[in]      CratEntryType        CRAT entry type
*    @param[in]      CratHeaderStructPtr  CRAT header pointer
*    @param[in, out] TableEnd             The end of CRAT
*
*/
UINT8 *
AddOneCratEntry (
  IN       CRAT_ENTRY_TYPE    CratEntryType,
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd
  )
{
  UINT8 *CurrentEntry;

  ASSERT (CratEntryType < CRAT_MAX_TYPE);

  CurrentEntry = *TableEnd;
  CratHeaderStructPtr->TotalEntries++;
  switch (CratEntryType) {
  case CRAT_HSA_PROC_UNIT_TYPE:
    *TableEnd += sizeof (CRAT_HSA_PROCESSING_UNIT);
    ((CRAT_HSA_PROCESSING_UNIT *) CurrentEntry)->Type = (UINT8) CratEntryType;
    ((CRAT_HSA_PROCESSING_UNIT *) CurrentEntry)->Length = sizeof (CRAT_HSA_PROCESSING_UNIT);
    CratHeaderStructPtr->NumNodes++;
    break;
  case CRAT_CACHE_TYPE:
    *TableEnd += sizeof (CRAT_CACHE);
    ((CRAT_CACHE *) CurrentEntry)->Type = (UINT8) CratEntryType;
    ((CRAT_CACHE *) CurrentEntry)->Length = sizeof (CRAT_CACHE);
    break;
  case CRAT_TLB_TYPE:
    *TableEnd += sizeof (CRAT_TLB);
    ((CRAT_TLB *) CurrentEntry)->Type = (UINT8) CratEntryType;
    ((CRAT_TLB *) CurrentEntry)->Length = sizeof (CRAT_TLB);
    break;
  case CRAT_FPU_TYPE:
    *TableEnd += sizeof (CRAT_FPU);
    ((CRAT_FPU *) CurrentEntry)->Type = (UINT8) CratEntryType;
    ((CRAT_FPU *) CurrentEntry)->Length = sizeof (CRAT_FPU);
    break;
  default:
    ASSERT (FALSE);
    break;
  }
  return CurrentEntry;
}

/*---------------------------------------------------------------------------------------*/
/**
* Return associativity
*
*    @param[in]      RawAssoc          Data which is got from CPUID
*
*/
UINT8
GetCacheAssoc (
  IN       UINT16   RawAssoc
  )
{
  UINT8 Associativity;

  Associativity = 0;

  switch (RawAssoc) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
    Associativity = (UINT8) RawAssoc;
    break;
  case 5:
    Associativity = 6;
    break;
  case 6:
    Associativity = 8;
    break;
  case 8:
    Associativity = 16;
    break;
  case 0xA:
    Associativity = 32;
    break;
  case 0xB:
    Associativity = 48;
    break;
  case 0xC:
    Associativity = 64;
    break;
  case 0xD:
    Associativity = 96;
    break;
  case 0xE:
    Associativity = 128;
    break;
  case 0xF:
    Associativity = 0xFF;
    break;
  default:
    ASSERT (FALSE);
    break;
  }

  return Associativity;
}

/*---------------------------------------------------------------------------------------*/
/**
* Return associativity
*
*    @param[in]      TLB_TYPE          2M4M, 4K or 1G
*    @param[in]      CratTlbEntry      Crat TLB entry
*    @param[in]      RawAssocSize      Value which is got from CPUID
*
*/
UINT8
GetTlbSize (
  IN       TLB_TYPE   TLB_TYPE,
  IN       CRAT_TLB  *CratTlbEntry,
  IN       UINT16     RawAssocSize
  )
{
  UINT8 TlbSize;

  if (RawAssocSize >= 256) {
    TlbSize = (UINT8) (RawAssocSize / 256);
    if (TLB_TYPE == TLB_2M) {
      CratTlbEntry->Flags.TLB2MBase256 = 1;
    }

    if (TLB_TYPE == TLB_4K) {
      CratTlbEntry->Flags.TLB4KBase256 = 1;
    }

    if (TLB_TYPE == TLB_1G) {
      CratTlbEntry->Flags.TLB1GBase256 = 1;
    }
  } else {
    TlbSize = (UINT8) (RawAssocSize);
  }

  return TlbSize;
}

