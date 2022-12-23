/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate ACPI Processor SSDT.
 *
 * Contains code that generate ACPI Processor SSDT
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Universal
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
#include "AGESA.h"
#include "Filecode.h"
#include "AmdAcpiDxe.h"
#include "AmdAcpiCpuSsdt.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/BaseLib.h"
#include "Library/CcxPstatesLib.h"
#include "Library/IdsLib.h"
#include "Library/AmdIdsHookLib.h"
#include "Protocol/AmdAcpiCpuSsdtServicesProtocol.h"
#include "Protocol/AmdCoreTopologyProtocol.h"
#include "Protocol/AmdCoreTopologyV2Protocol.h"
#include "IdsHookId.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_ACPI_AMDACPICPUSSDT_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
STATIC ACPI_TABLE_HEADER  ROMDATA CpuSsdtHdrStruct =
{
  {'S','S','D','T'},
  0,
  1,
  0,
  {0},
  {0},
  1,
  {'A','M','D',' '},
  1
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

UINT32
AmdAcpiCalSsdtSize (
  IN       AMD_PSTATE_SYS_INFO     *AmdPstateSysInfo,
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  );

UINT32
AmdAcpiCalCstObj (
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  );

UINT32
AmdAcpiCalPstObj (
  IN       AMD_PSTATE_SOCKET_INFO  *AmdPstateSocketInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  );

UINT32
AmdCreateCStateAcpiTables (
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN OUT   VOID                   **SsdtPtr,
  IN       UINT8                    LocalApicId,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  );

UINT32
AmdCreatePStateAcpiTables (
  IN       AMD_PSTATE_SOCKET_INFO  *AmdPstateSocketInfo,
  IN OUT   VOID                   **SsdtPtr,
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL *CpuSsdtServices,
  IN       UINT8                    LocalApicId,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  );


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/**
 *---------------------------------------------------------------------------------------
 *
 *  GenerateSsdt
 *
 *  Description:
 *    This function will populate the SSDT with ACPI P-States and C-States Objects, whenever
 *    necessary
 *    This function should be called only from BSP
 *
 *  Parameters:
 *    @param[in]       AcpiTableProtocol          Pointer to gEfiAcpiTableProtocolGuid protocol
 *    @param[in]       StdHeader                  Header for library and services
 *
 *    @retval          AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
AGESA_STATUS
AmdAcpiCpuSSdt (
  IN       EFI_ACPI_TABLE_PROTOCOL  *AcpiTableProtocol,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8                  LocalApicId;
  UINT8                  SocketLoop;
  UINT8                  TotalSockets;
  UINT8                  CoreNumberHi;
  UINT8                  CoreNumberLo;
  UINT32                 CoreLoop;
  UINT32                 LogicalCoreNumberInThisSocket;
  UINT32                 CurrSize;
  UINT32                 SizeTemp;
  UINT32                 ScopeSize;
  UINT32                 CoreCount;
  UINTN                  TableSize;
  UINTN                  TableKey;
  ALLOCATE_HEAP_PARAMS   AllocateHeapParams;
  AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL *AmdAcpiCpuSsdtServices;
  AMD_PSTATE_SYS_INFO    *AmdPstateSysInfo;
  AMD_PSTATE_SOCKET_INFO *AmdPstateSocketInfo;
  AMD_CSTATE_INFO        *AmdCstateInfo;
  ACPI_TABLE_HEADER      *SsdtHeaderPtr;
  LPI_STRUCT             *Lpi;
  SCOPE                  *AmdCpuSsdtScopeStruct;
  UINT8                  *AmdCpuSsdtBodyStruct;
  EFI_STATUS             CalledStatus;
  UINT8                  AcpiCstateSelection;


  IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create Processor SSDT\n");

  // Initialize data variables
  ScopeSize   = 0;
  CoreCount   = 0;
  LocalApicId = 0;

  // Get all the CPUs P-States information
  CalledStatus = gBS->LocateProtocol (&gAmdAcpiCpuSsdtServicesProtocolGuid, NULL, (VOID **)&AmdAcpiCpuSsdtServices);
  if (EFI_ERROR (CalledStatus)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "  gAmdAcpiCpuSsdtServicesProtocolGuid not found\n");
    return EFI_PROTOCOL_ERROR;
  }

  AcpiCstateSelection = PcdGet8(PcdAmdAcpiC3Ctrl);
  IDS_HDT_CONSOLE (MAIN_FLOW, "  PcdAmdAcpiC3Ctrl=0x%x\n", AcpiCstateSelection);
  switch (AcpiCstateSelection) {
    case PCD_AMD_ACPI_C3_CTRL_VAL_DISABLED: // Disable
      IDS_HDT_CONSOLE (MAIN_FLOW, "  Set PcdAmdAcpiCstC3 to FALSE\n");
      PcdSetBool (PcdAmdAcpiCstC3, FALSE);
      break;
    case PCD_AMD_ACPI_C3_CTRL_VAL_CST: // CST
    case PCD_AMD_ACPI_C3_CTRL_VAL_LPI: // LPI (with CST)
      if (PcdGet16 (PcdAmdAcpiCpuCstC3Latency) != 0) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "  Set PcdAmdAcpiCstC3 to TRUE\n");
        PcdSetBool (PcdAmdAcpiCstC3, TRUE);
      }
      break;
    default:
      ASSERT (FALSE);
      break;
  }

  AmdAcpiCpuSsdtServices->GetPstateInfo (AmdAcpiCpuSsdtServices, &AmdPstateSysInfo);
  AmdAcpiCpuSsdtServices->GetCstateInfo (AmdAcpiCpuSsdtServices, &AmdCstateInfo);

  // Allocate rough buffer for AcpiTable
  // Do not know the actual size.. pre-calculate it.
  AllocateHeapParams.RequestedBufferSize = AmdAcpiCalSsdtSize (AmdPstateSysInfo, AmdCstateInfo, StdHeader);
  AllocateHeapParams.BufferHandle        = AMD_PSTATE_ACPI_BUFFER_HANDLE;
  AllocateHeapParams.Persist             = HEAP_SYSTEM_MEM;
  if (HeapAllocateBuffer (&AllocateHeapParams, StdHeader) != AGESA_SUCCESS) {
    return AGESA_ERROR;
  }
  SsdtHeaderPtr = (ACPI_TABLE_HEADER *) AllocateHeapParams.BufferPtr;

  // Copy SSDT header into allocated buffer
  LibAmdMemCopy (SsdtHeaderPtr, (VOID *) &CpuSsdtHdrStruct, (UINTN) (sizeof (ACPI_TABLE_HEADER)), StdHeader);

  // Update table OEM fields.
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 100) <= 6);
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCpuSsdtTableHeaderOemTableId), 100) <= 8);

  LibAmdMemCopy ((VOID *) SsdtHeaderPtr->OemId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
                 StdHeader);
  LibAmdMemCopy ((VOID *) SsdtHeaderPtr->OemTableId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiCpuSsdtTableHeaderOemTableId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCpuSsdtTableHeaderOemTableId), 8),
                 StdHeader);

  // Initialize ScopeStruct pointer
  AmdCpuSsdtScopeStruct = (SCOPE *) (SsdtHeaderPtr + 1);

  // Generate name scope and ACPI objects for every core in the system
  AmdPstateSocketInfo   = AmdPstateSysInfo->PStateSocketStruct;
  TotalSockets          = AmdPstateSysInfo->TotalSocketInSystem;
  for (SocketLoop = 0; SocketLoop < TotalSockets; SocketLoop++) {
    LogicalCoreNumberInThisSocket = AmdPstateSocketInfo->TotalLogicalCores;
    for (CoreLoop = 0; CoreLoop < LogicalCoreNumberInThisSocket; CoreLoop++) {
      CurrSize = 0;
      CoreCount++;
      // Set Name Scope for CPU0, 1, 2, ..... n
      // CPU0 to CPUn will name  as  C000 to Cnnn
      // -----------------------------------------
      AmdCpuSsdtScopeStruct->ScopeOpcode        = SCOPE_OPCODE;
      AmdCpuSsdtScopeStruct->ScopeValue1        = SCOPE_VALUE1;
      AmdCpuSsdtScopeStruct->ScopeValue2        = SCOPE_VALUE2;
      AmdCpuSsdtScopeStruct->ScopeNamePt1a__    = SCOPE_NAME__;
      if (PcdGetBool (PcdAmdAcpiCpuSsdtProcessorScopeInSb)) {
        AmdCpuSsdtScopeStruct->ScopeNamePt1a_P  = SCOPE_NAME_S;
        AmdCpuSsdtScopeStruct->ScopeNamePt1a_R  = SCOPE_NAME_B;
      } else {
        AmdCpuSsdtScopeStruct->ScopeNamePt1a_P  = SCOPE_NAME_P;
        AmdCpuSsdtScopeStruct->ScopeNamePt1a_R  = SCOPE_NAME_R;
      }
      AmdCpuSsdtScopeStruct->ScopeNamePt1b__    = SCOPE_NAME__;

      AmdCpuSsdtScopeStruct->ScopeNamePt2a_C    = PcdGet8 (PcdAmdAcpiCpuSsdtProcessorScopeName0);
      AmdCpuSsdtScopeStruct->ScopeNamePt2a_P    = PcdGet8 (PcdAmdAcpiCpuSsdtProcessorScopeName1);

      CoreNumberHi = ((CoreCount - 1) >> 4) & 0x0F;
      AmdCpuSsdtScopeStruct->ScopeNamePt2a_U    = (UINT8) (SCOPE_NAME_0 + CoreNumberHi);

      CoreNumberLo = (CoreCount - 1) & 0x0F;
      if (CoreNumberLo < 0xA) {
        AmdCpuSsdtScopeStruct->ScopeNamePt2a_0  = (UINT8) (SCOPE_NAME_0 + CoreNumberLo);
      } else {
        AmdCpuSsdtScopeStruct->ScopeNamePt2a_0  = (UINT8) (SCOPE_NAME_A + CoreNumberLo - 0xA);
      }

      // Increment and typecast the pointer
      AmdCpuSsdtBodyStruct = (UINT8 *) (AmdCpuSsdtScopeStruct + 1);

      // Get the Local Apic Id for each core
      LocalApicId = AmdPstateSocketInfo->LocalApicId[CoreLoop];

      // Create P-State ACPI Objects
      if (PcdGetBool (PcdAmdAcpiPstateObjEnable)) {
        if (AmdPstateSocketInfo->CreateAcpiTables) {
          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create Pstate tables\n");
          CurrSize += (AmdCreatePStateAcpiTables (AmdPstateSocketInfo, (VOID *) &AmdCpuSsdtBodyStruct, AmdAcpiCpuSsdtServices, (UINT8) (CoreCount - 1), StdHeader));
        }
      }

      // Create C-State ACPI Objects
      if (AmdCstateInfo->IsCstateEnabled) {

        CurrSize += (AmdCreateCStateAcpiTables (AmdCstateInfo, (VOID *) &AmdCpuSsdtBodyStruct, (UINT8) (CoreCount - 1), StdHeader));

        if (AcpiCstateSelection == PCD_AMD_ACPI_C3_CTRL_VAL_LPI) { // Enable LPI
          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create LPI\n");
          // Add LPI
          Lpi = (LPI_STRUCT *) AmdCpuSsdtBodyStruct;
          Lpi->Header.NameOpcode = NAME_OPCODE;
          Lpi->Header.LpiName_a__ = LPI_NAME__;
          Lpi->Header.LpiName_a_L = LPI_NAME_L;
          Lpi->Header.LpiName_a_P = LPI_NAME_P;
          Lpi->Header.LpiName_a_I = LPI_NAME_I;
          Lpi->Header.PkgOpcode = PACKAGE_OPCODE;
          Lpi->Header.PkgLength = LPI_HEADER_PKG_LENGTH;
          Lpi->Header.PkgElements = LPI_HEADER_PKG_ELEMENTS;
          Lpi->Header.WordPrefix = WORD_PREFIX_OPCODE;
          Lpi->Header.Revision = 0;
          Lpi->Header.QWordPrefix = QWORD_PREFIX_OPCODE;
          Lpi->Header.LevelID = 0;
          Lpi->Header.WordPrefix2 = WORD_PREFIX_OPCODE;
          Lpi->Header.Count = 3;

          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create LPI.C1\n");
          Lpi->C1.PkgOpcode = PACKAGE_OPCODE;
          Lpi->C1.PkgLength = LPI_BODY_PKG_LENGTH;
          Lpi->C1.PkgElements = LPI_BODY_PKG_ELEMENTS;
          Lpi->C1.DWordPrefix = DWORD_PREFIX_OPCODE;
          Lpi->C1.MinResidency = PcdGet32 (PcdAmdAcpiCpuLpiC1MinRes);
          Lpi->C1.DWordPrefix2 = DWORD_PREFIX_OPCODE;
          Lpi->C1.WorstCaseWakeupLatency = PcdGet32 (PcdAmdAcpiCpuLpiC1WorstCaseWakeupLatency);
          Lpi->C1.DWordPrefix3 = DWORD_PREFIX_OPCODE;
          Lpi->C1.Flags = 1;
          Lpi->C1.DWordPrefix4 = DWORD_PREFIX_OPCODE;
          Lpi->C1.ArchContextLostFlags = 0;
          Lpi->C1.DWordPrefix5 = DWORD_PREFIX_OPCODE;
          Lpi->C1.ResidencyCounterFrequency = 0;
          Lpi->C1.DWordPrefix6 = DWORD_PREFIX_OPCODE;
          Lpi->C1.EnabledParentState = 0;

          Lpi->C1.EntryMethod.BufferOpcode = BUFFER_OPCODE;
          Lpi->C1.EntryMethod.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C1.EntryMethod.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C1.EntryMethod.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C1.EntryMethod.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C1.EntryMethod.GdrLength = LPI_GDR_LENGTH;
          Lpi->C1.EntryMethod.AddrSpaceId = GDR_ASI_FIXED_HW;
          Lpi->C1.EntryMethod.RegBitWidth = 0x02;
          Lpi->C1.EntryMethod.RegBitOffset = 0x02;
          Lpi->C1.EntryMethod.AddressSize = GDR_ASZ_UNDEFINED;
          Lpi->C1.EntryMethod.RegisterAddr = 0;
          Lpi->C1.EntryMethod.EndTag = 0x0079;

          Lpi->C1.ResidencyCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C1.ResidencyCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C1.ResidencyCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C1.ResidencyCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C1.ResidencyCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C1.ResidencyCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C1.ResidencyCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C1.ResidencyCounterRegister.RegBitWidth = 0x00;
          Lpi->C1.ResidencyCounterRegister.RegBitOffset = 0x00;
          Lpi->C1.ResidencyCounterRegister.AddressSize = 0x00;
          Lpi->C1.ResidencyCounterRegister.RegisterAddr = 0;
          Lpi->C1.ResidencyCounterRegister.EndTag = 0x0079;

          Lpi->C1.UsageCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C1.UsageCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C1.UsageCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C1.UsageCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C1.UsageCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C1.UsageCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C1.UsageCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C1.UsageCounterRegister.RegBitWidth = 0x00;
          Lpi->C1.UsageCounterRegister.RegBitOffset = 0x00;
          Lpi->C1.UsageCounterRegister.AddressSize = 0x00;
          Lpi->C1.UsageCounterRegister.RegisterAddr = 0;
          Lpi->C1.UsageCounterRegister.EndTag = 0x0079;

          Lpi->C1.StringPrefix = STRING_PREFIX_OPCODE;
          Lpi->C1.StateName0 = 'C';
          Lpi->C1.StateName1 = '1';
          Lpi->C1.StateNameNull = 0;

          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create LPI.C2\n");
          Lpi->C2.PkgOpcode = PACKAGE_OPCODE;
          Lpi->C2.PkgLength = LPI_BODY_PKG_LENGTH;
          Lpi->C2.PkgElements = LPI_BODY_PKG_ELEMENTS;
          Lpi->C2.DWordPrefix = DWORD_PREFIX_OPCODE;
          Lpi->C2.MinResidency = PcdGet32 (PcdAmdAcpiCpuLpiC2MinRes);
          Lpi->C2.DWordPrefix2 = DWORD_PREFIX_OPCODE;
          if (AmdCstateInfo->C3Latency != 0) {
            Lpi->C2.WorstCaseWakeupLatency = PcdGet32 (PcdAmdAcpiCpuLpiC2WorstCaseWakeupLatency);
          } else {
            IDS_HDT_CONSOLE (MAIN_FLOW, "  C3 disable, take C3 worst case latency\n");
            // C3 is disabled, take C3 setting
            Lpi->C2.WorstCaseWakeupLatency = PcdGet32 (PcdAmdAcpiCpuLpiC3WorstCaseWakeupLatency);
          }
          Lpi->C2.DWordPrefix3 = DWORD_PREFIX_OPCODE;
          Lpi->C2.Flags = 1;
          Lpi->C2.DWordPrefix4 = DWORD_PREFIX_OPCODE;
          Lpi->C2.ArchContextLostFlags = 0;
          Lpi->C2.DWordPrefix5 = DWORD_PREFIX_OPCODE;
          Lpi->C2.ResidencyCounterFrequency = 0;
          Lpi->C2.DWordPrefix6 = DWORD_PREFIX_OPCODE;
          Lpi->C2.EnabledParentState = 0;

          Lpi->C2.EntryMethod.BufferOpcode = BUFFER_OPCODE;
          Lpi->C2.EntryMethod.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C2.EntryMethod.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C2.EntryMethod.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C2.EntryMethod.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C2.EntryMethod.GdrLength = LPI_GDR_LENGTH;
          Lpi->C2.EntryMethod.AddrSpaceId = GDR_ASI_SYSTEM_IO;
          Lpi->C2.EntryMethod.RegBitWidth = 0x08;
          Lpi->C2.EntryMethod.RegBitOffset = 0x00;
          Lpi->C2.EntryMethod.AddressSize = GDR_ASZ_BYTE_ACCESS;
          Lpi->C2.EntryMethod.RegisterAddr = AmdCstateInfo->IoCstateAddr + 1;
          Lpi->C2.EntryMethod.EndTag = 0x0079;

          Lpi->C2.ResidencyCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C2.ResidencyCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C2.ResidencyCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C2.ResidencyCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C2.ResidencyCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C2.ResidencyCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C2.ResidencyCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C2.ResidencyCounterRegister.RegBitWidth = 0x00;
          Lpi->C2.ResidencyCounterRegister.RegBitOffset = 0x00;
          Lpi->C2.ResidencyCounterRegister.AddressSize = 0x00;
          Lpi->C2.ResidencyCounterRegister.RegisterAddr = 0;
          Lpi->C2.ResidencyCounterRegister.EndTag = 0x0079;

          Lpi->C2.UsageCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C2.UsageCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C2.UsageCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C2.UsageCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C2.UsageCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C2.UsageCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C2.UsageCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C2.UsageCounterRegister.RegBitWidth = 0x00;
          Lpi->C2.UsageCounterRegister.RegBitOffset = 0x00;
          Lpi->C2.UsageCounterRegister.AddressSize = 0x00;
          Lpi->C2.UsageCounterRegister.RegisterAddr = 0;
          Lpi->C2.UsageCounterRegister.EndTag = 0x0079;

          Lpi->C2.StringPrefix = STRING_PREFIX_OPCODE;
          Lpi->C2.StateName0 = 'C';
          Lpi->C2.StateName1 = '2';
          Lpi->C2.StateNameNull = 0;

          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to create LPI.C3\n");
          Lpi->C3.PkgOpcode = PACKAGE_OPCODE;
          Lpi->C3.PkgLength = LPI_BODY_PKG_LENGTH;
          Lpi->C3.PkgElements = LPI_BODY_PKG_ELEMENTS;
          Lpi->C3.DWordPrefix = DWORD_PREFIX_OPCODE;
          Lpi->C3.MinResidency = PcdGet32 (PcdAmdAcpiCpuLpiC3MinRes);
          Lpi->C3.DWordPrefix2 = DWORD_PREFIX_OPCODE;
          Lpi->C3.WorstCaseWakeupLatency = PcdGet32 (PcdAmdAcpiCpuLpiC3WorstCaseWakeupLatency);
          Lpi->C3.DWordPrefix3 = DWORD_PREFIX_OPCODE;
          if (AmdCstateInfo->C3Latency != 0) {
            Lpi->C3.Flags = 1; //(AmdCstateInfo->C3Latency != 0) ? 1 : 0;
          } else {
            // Disable C3
            IDS_HDT_CONSOLE (MAIN_FLOW, "  Disable LPI.C3\n");
            Lpi->C3.Flags = 0; //(AmdCstateInfo->C3Latency != 0) ? 1 : 0;
          }
          Lpi->C3.DWordPrefix4 = DWORD_PREFIX_OPCODE;
          Lpi->C3.ArchContextLostFlags = 0;
          Lpi->C3.DWordPrefix5 = DWORD_PREFIX_OPCODE;
          Lpi->C3.ResidencyCounterFrequency = 0;
          Lpi->C3.DWordPrefix6 = DWORD_PREFIX_OPCODE;
          Lpi->C3.EnabledParentState = 0;

          Lpi->C3.EntryMethod.BufferOpcode = BUFFER_OPCODE;
          Lpi->C3.EntryMethod.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C3.EntryMethod.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C3.EntryMethod.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C3.EntryMethod.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C3.EntryMethod.GdrLength = LPI_GDR_LENGTH;
          Lpi->C3.EntryMethod.AddrSpaceId = GDR_ASI_SYSTEM_IO;
          Lpi->C3.EntryMethod.RegBitWidth = 0x08;
          Lpi->C3.EntryMethod.RegBitOffset = 0x00;
          Lpi->C3.EntryMethod.AddressSize = GDR_ASZ_BYTE_ACCESS;
          Lpi->C3.EntryMethod.RegisterAddr = AmdCstateInfo->IoCstateAddr + 2;
          Lpi->C3.EntryMethod.EndTag = 0x0079;

          Lpi->C3.ResidencyCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C3.ResidencyCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C3.ResidencyCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C3.ResidencyCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C3.ResidencyCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C3.ResidencyCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C3.ResidencyCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C3.ResidencyCounterRegister.RegBitWidth = 0x00;
          Lpi->C3.ResidencyCounterRegister.RegBitOffset = 0x00;
          Lpi->C3.ResidencyCounterRegister.AddressSize = 0x00;
          Lpi->C3.ResidencyCounterRegister.RegisterAddr = 0;
          Lpi->C3.ResidencyCounterRegister.EndTag = 0x0079;

          Lpi->C3.UsageCounterRegister.BufferOpcode = BUFFER_OPCODE;
          Lpi->C3.UsageCounterRegister.BufferLength = LPI_SUBPKG_LENGTH;
          Lpi->C3.UsageCounterRegister.BufferElements = LPI_SUBPKG_ELEMENTS;
          Lpi->C3.UsageCounterRegister.BufferOpcode2 = BUFFER_OPCODE;
          Lpi->C3.UsageCounterRegister.GdrOpcode = GENERIC_REG_DESCRIPTION;
          Lpi->C3.UsageCounterRegister.GdrLength = LPI_GDR_LENGTH;
          Lpi->C3.UsageCounterRegister.AddrSpaceId = GDR_ASI_SYSTEM_MEM;
          Lpi->C3.UsageCounterRegister.RegBitWidth = 0x00;
          Lpi->C3.UsageCounterRegister.RegBitOffset = 0x00;
          Lpi->C3.UsageCounterRegister.AddressSize = 0x00;
          Lpi->C3.UsageCounterRegister.RegisterAddr = 0;
          Lpi->C3.UsageCounterRegister.EndTag = 0x0079;

          Lpi->C3.StringPrefix = STRING_PREFIX_OPCODE;
          Lpi->C3.StateName0 = 'C';
          Lpi->C3.StateName1 = '3';
          Lpi->C3.StateNameNull = 0;

          IDS_HDT_CONSOLE (MAIN_FLOW, "  Start to adjust CurSize with LPI_SIZE\n");
          CurrSize += LPI_SIZE; // Already added in AmdAcpiCalCstObj
          AmdCpuSsdtBodyStruct = (UINT8 *) (Lpi + 1);
        }
      }


      // Now update the SCOPE Length field
      CurrSize += (SCOPE_STRUCT_SIZE - 1);
      ScopeSize += CurrSize;

      ASSERT (CurrSize < 0x1000);

      SizeTemp = ((CurrSize << 4) & 0x0000FF00);
      SizeTemp |= ((CurrSize & 0x0000000F) | 0x00000040);
      AmdCpuSsdtScopeStruct->ScopeLength = (UINT16) SizeTemp;

      AmdCpuSsdtScopeStruct = (SCOPE *) AmdCpuSsdtBodyStruct;
    }
    AmdPstateSocketInfo = (AMD_PSTATE_SOCKET_INFO *) ((UINT8 *) AmdPstateSocketInfo + sizeof (AMD_PSTATE_SOCKET_INFO) + sizeof (S_PSTATE_VALUES) * AmdPstateSocketInfo->PStateMaxValue);
  }

  // Update SSDT header Checksum
  SsdtHeaderPtr->TableLength = (ScopeSize + CoreCount + sizeof (ACPI_TABLE_HEADER));
  ChecksumAcpiTable (SsdtHeaderPtr, StdHeader);

  // Publish SSDT
  TableSize = SsdtHeaderPtr->TableLength;
  TableKey = 0;
  AcpiTableProtocol->InstallAcpiTable (
                  AcpiTableProtocol,
                  SsdtHeaderPtr,
                  TableSize,
                  &TableKey
                  );

  // Deallocate heap
  HeapDeallocateBuffer (AMD_PSTATE_ACPI_BUFFER_HANDLE, StdHeader);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  Processor SSDT is created\n");

  return AGESA_SUCCESS;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

 /**
 *---------------------------------------------------------------------------------------
 *
 *  AmdAcpiCalSsdtSize
 *
 *  Description:
 *    This function will calculate the size of processor SSDT tables
 *
 *  Parameters:
 *    @param[in]     *AmdPstateSysInfo        Pstate system information
 *    @param[in]     *AmdCstateInfo           Cstate information
 *    @param[in]     *StdHeader               Stand header
 *
 *    @retval        UINT32
 *
 *---------------------------------------------------------------------------------------
 */
UINT32
AmdAcpiCalSsdtSize (
  IN       AMD_PSTATE_SYS_INFO     *AmdPstateSysInfo,
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT8                     SocketLoop;
  UINT32                    CoreLoop;
  UINT32                    ScopeSize;
  UINT32                    CstateAcpiObjSize;
  UINT32                    PstateAcpiObjSize;
  AMD_PSTATE_SOCKET_INFO   *AmdPstateSocketInfo;

  ScopeSize           = sizeof (ACPI_TABLE_HEADER);
  if (AmdCstateInfo->IsCstateEnabled) {
    CstateAcpiObjSize = AmdAcpiCalCstObj (AmdCstateInfo, StdHeader); // Size of Cstate Acpi objects are the same for every core
  } else {
    CstateAcpiObjSize = 0;
  }
  AmdPstateSocketInfo = AmdPstateSysInfo->PStateSocketStruct;

  for (SocketLoop = 0; SocketLoop < AmdPstateSysInfo->TotalSocketInSystem; SocketLoop++) {
    for (CoreLoop = 0; CoreLoop < AmdPstateSocketInfo->TotalLogicalCores; CoreLoop++) {
      ScopeSize += (SCOPE_STRUCT_SIZE - 1); // Scope size per core
      ScopeSize += CstateAcpiObjSize;       // C-State ACPI objects size per core

      // Add P-State ACPI Objects size per core
      if (AmdPstateSocketInfo->CreateAcpiTables) {
        PstateAcpiObjSize = AmdAcpiCalPstObj (AmdPstateSocketInfo, StdHeader);
        ScopeSize += PstateAcpiObjSize;
      }

      if (PcdGet8(PcdAmdAcpiC3Ctrl) == PCD_AMD_ACPI_C3_CTRL_VAL_LPI) {
        ScopeSize += LPI_SIZE;
      }
    }
    ScopeSize += AmdPstateSocketInfo->TotalLogicalCores;
    AmdPstateSocketInfo = (AMD_PSTATE_SOCKET_INFO *) ((UINT8 *) AmdPstateSocketInfo + sizeof (AMD_PSTATE_SOCKET_INFO) + sizeof (S_PSTATE_VALUES) * AmdPstateSocketInfo->PStateMaxValue);
  }

  return ScopeSize;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Returns the size of Cstate ACPI objects
 *
 *  Parameters:
 *    @param[in]     *AmdCstateInfo           Cstate information
 *    @param[in]     *StdHeader               Stand header
 *
 *    @retval        CstObjSize               Size of CST Object
 *
 */
UINT32
AmdAcpiCalCstObj (
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT32   CStateAcpiObjSize;

  CStateAcpiObjSize = CST_HEADER_SIZE + CST_BODY_SIZE;

  // If CSD Object is generated, add the size of CSD Object to the total size of
  // CState ACPI Object size
  if (AmdCstateInfo->IsCsdGenerated) {
    CStateAcpiObjSize += CSD_HEADER_SIZE + CSD_BODY_SIZE;
  }

  if (PcdGetBool (PcdAmdAcpiCstC1) && AmdCstateInfo->IsMonitorMwaitSupported) {
    CStateAcpiObjSize += CST_BODY_SIZE;
  }

  if (PcdGetBool (PcdAmdAcpiCstC3) && (AmdCstateInfo->C3Latency != 0)) {
    CStateAcpiObjSize += CST_BODY_SIZE;
  }

  return CStateAcpiObjSize;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Returns the size of Pstate ACPI objects
 *
 *  Parameters:
 *    @param[in]     *AmdPstateSocketInfo     Pstate information for this socket
 *    @param[in]     *StdHeader               Stand header
 *
 *    @retval        CstObjSize               Size of CST Object
 *
 */
UINT32
AmdAcpiCalPstObj (
  IN       AMD_PSTATE_SOCKET_INFO  *AmdPstateSocketInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT32 MaxPstateNumber;

  MaxPstateNumber = AmdPstateSocketInfo->PStateMaxValue + 1;
  return (PCT_STRUCT_SIZE +
          PSS_HEADER_STRUCT_SIZE +
          (MaxPstateNumber * PSS_BODY_STRUCT_SIZE) +
          XPSS_HEADER_STRUCT_SIZE +
          (MaxPstateNumber * XPSS_BODY_STRUCT_SIZE) +
          PSD_HEADER_STRUCT_SIZE +
          PSD_BODY_STRUCT_SIZE +
          PPC_HEADER_BODY_STRUCT_SIZE);
}

/**--------------------------------------------------------------------------------------
 *
 *  CreateCStateAcpiTables
 *
 *  Description:
 *     This is the common routine for creating ACPI C-State objects
 *
 *  Parameters:
 *    @param[in]     AmdCstateInfo        Buffer that contains C-State information
 *    @param[in,out] SsdtPtr              ACPI SSDT table pointer
 *    @param[in]     LocalApicId          Local Apic Id
 *    @param[in]     StdHeader            Handle to config for library and services
 *
 *    @retval        Size of ACPI C-States objects generated
 *
 *---------------------------------------------------------------------------------------
 **/
UINT32
AmdCreateCStateAcpiTables (
  IN       AMD_CSTATE_INFO         *AmdCstateInfo,
  IN OUT   VOID                   **SsdtPtr,
  IN       UINT8                    LocalApicId,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT8                 NumberOfCstates;
  UINT32                PkgLength;
  UINT32                ObjSize;
  BOOLEAN               DeclareC1;
  BOOLEAN               DeclareC3;
  CST_HEADER_STRUCT     *CstHeaderPtr;
  CST_BODY_STRUCT       *CstBodyPtr;
  CSD_HEADER_STRUCT     *CsdHeaderPtr;
  CSD_BODY_STRUCT       *CsdBodyPtr;

  ObjSize = 0;
  NumberOfCstates = 1;
  DeclareC1 = FALSE;
  DeclareC3 = FALSE;

  if (PcdGetBool (PcdAmdAcpiCstC1) && AmdCstateInfo->IsMonitorMwaitSupported) {
    DeclareC1 = TRUE;
    NumberOfCstates++;
  }

  if (PcdGetBool (PcdAmdAcpiCstC3) && (AmdCstateInfo->C3Latency != 0)) {
    DeclareC3 = TRUE;
    NumberOfCstates++;
  }

  PkgLength = ((CST_BODY_SIZE * NumberOfCstates) + CST_HEADER_PKG_LENGTH);
  //====================
  // Set CST Table
  //====================

  // Set CST Header
  // --------------

  // Typecast the pointer
  CstHeaderPtr = (CST_HEADER_STRUCT *) *SsdtPtr;

  CstHeaderPtr->NameOpcode    = NAME_OPCODE;
  CstHeaderPtr->CstName_a__   = CST_NAME__;
  CstHeaderPtr->CstName_a_C   = CST_NAME_C;
  CstHeaderPtr->CstName_a_S   = CST_NAME_S;
  CstHeaderPtr->CstName_a_T   = CST_NAME_T;
  CstHeaderPtr->PkgOpcode     = PACKAGE_OPCODE;
  CstHeaderPtr->PkgLength     = (((PkgLength & 0xF0) << 4) | CST_HEADER_PKG_LENGTH_ONE_BYTEDATA | (PkgLength & 0xF));
  CstHeaderPtr->PkgElements   = NumberOfCstates + 1;
  CstHeaderPtr->BytePrefix    = BYTE_PREFIX_OPCODE;
  CstHeaderPtr->Count         = NumberOfCstates;

  // Set CST Body
  // --------------

  // Typecast the pointer
  CstHeaderPtr++;
  CstBodyPtr = (CST_BODY_STRUCT *) CstHeaderPtr;

  if (DeclareC1) {

    CstBodyPtr->PkgOpcode       = PACKAGE_OPCODE;
    CstBodyPtr->PkgLength       = CST_PKG_LENGTH;
    CstBodyPtr->PkgElements     = CST_PKG_ELEMENTS;
    CstBodyPtr->BufferOpcode    = BUFFER_OPCODE;
    CstBodyPtr->BufferLength    = CST_SUBPKG_LENGTH;
    CstBodyPtr->BufferElements  = CST_SUBPKG_ELEMENTS;
    CstBodyPtr->BufferOpcode2   = BUFFER_OPCODE;
    CstBodyPtr->GdrOpcode       = GENERIC_REG_DESCRIPTION;
    CstBodyPtr->GdrLength       = CST_GDR_LENGTH;
    CstBodyPtr->AddrSpaceId     = GDR_ASI_FIXED_HW;
    CstBodyPtr->RegBitWidth     = 0x02;
    CstBodyPtr->RegBitOffset    = 0x02;
    CstBodyPtr->AddressSize     = GDR_ASZ_UNDEFINED;
    CstBodyPtr->RegisterAddr    = 0;
    CstBodyPtr->EndTag          = 0x0079;
    CstBodyPtr->BytePrefix      = BYTE_PREFIX_OPCODE;
    CstBodyPtr->Type            = CST_C1_TYPE;
    CstBodyPtr->WordPrefix      = WORD_PREFIX_OPCODE;
    CstBodyPtr->Latency         = AmdCstateInfo->C1Latency;
    CstBodyPtr->DWordPrefix     = DWORD_PREFIX_OPCODE;
    CstBodyPtr->Power           = 0;

    CstBodyPtr++;
  }

  CstBodyPtr->PkgOpcode       = PACKAGE_OPCODE;
  CstBodyPtr->PkgLength       = CST_PKG_LENGTH;
  CstBodyPtr->PkgElements     = CST_PKG_ELEMENTS;
  CstBodyPtr->BufferOpcode    = BUFFER_OPCODE;
  CstBodyPtr->BufferLength    = CST_SUBPKG_LENGTH;
  CstBodyPtr->BufferElements  = CST_SUBPKG_ELEMENTS;
  CstBodyPtr->BufferOpcode2   = BUFFER_OPCODE;
  CstBodyPtr->GdrOpcode       = GENERIC_REG_DESCRIPTION;
  CstBodyPtr->GdrLength       = CST_GDR_LENGTH;
  CstBodyPtr->AddrSpaceId     = GDR_ASI_SYSTEM_IO;
  CstBodyPtr->RegBitWidth     = 0x08;
  CstBodyPtr->RegBitOffset    = 0x00;
  CstBodyPtr->AddressSize     = GDR_ASZ_BYTE_ACCESS;
  CstBodyPtr->RegisterAddr    = AmdCstateInfo->IoCstateAddr + 1;
  CstBodyPtr->EndTag          = 0x0079;
  CstBodyPtr->BytePrefix      = BYTE_PREFIX_OPCODE;
  CstBodyPtr->Type            = CST_C2_TYPE;
  CstBodyPtr->WordPrefix      = WORD_PREFIX_OPCODE;
  CstBodyPtr->Latency         = AmdCstateInfo->C2Latency;
  CstBodyPtr->DWordPrefix     = DWORD_PREFIX_OPCODE;
  CstBodyPtr->Power           = 0;

  CstBodyPtr++;

  if (DeclareC3) {

    CstBodyPtr->PkgOpcode       = PACKAGE_OPCODE;
    CstBodyPtr->PkgLength       = CST_PKG_LENGTH;
    CstBodyPtr->PkgElements     = CST_PKG_ELEMENTS;
    CstBodyPtr->BufferOpcode    = BUFFER_OPCODE;
    CstBodyPtr->BufferLength    = CST_SUBPKG_LENGTH;
    CstBodyPtr->BufferElements  = CST_SUBPKG_ELEMENTS;
    CstBodyPtr->BufferOpcode2   = BUFFER_OPCODE;
    CstBodyPtr->GdrOpcode       = GENERIC_REG_DESCRIPTION;
    CstBodyPtr->GdrLength       = CST_GDR_LENGTH;
    CstBodyPtr->AddrSpaceId     = GDR_ASI_SYSTEM_IO;
    CstBodyPtr->RegBitWidth     = 0x08;
    CstBodyPtr->RegBitOffset    = 0x00;
    CstBodyPtr->AddressSize     = GDR_ASZ_BYTE_ACCESS;
    CstBodyPtr->RegisterAddr    = AmdCstateInfo->IoCstateAddr + 2;
    CstBodyPtr->EndTag          = 0x0079;
    CstBodyPtr->BytePrefix      = BYTE_PREFIX_OPCODE;
    CstBodyPtr->Type            = CST_C3_TYPE;
    CstBodyPtr->WordPrefix      = WORD_PREFIX_OPCODE;
    CstBodyPtr->Latency         = AmdCstateInfo->C3Latency;
    CstBodyPtr->DWordPrefix     = DWORD_PREFIX_OPCODE;
    CstBodyPtr->Power           = 0;

    CstBodyPtr++;
  }

  // Update the pointer
  *SsdtPtr = CstBodyPtr;

  //====================
  // Set CSD Table
  //====================

  if (AmdCstateInfo->IsCsdGenerated) {

    // Set CSD Header
    // --------------

    // Typecast the pointer
    CsdHeaderPtr = (CSD_HEADER_STRUCT *) *SsdtPtr;

    CsdHeaderPtr->NameOpcode  = NAME_OPCODE;
    CsdHeaderPtr->CsdName_a__ = CST_NAME__;
    CsdHeaderPtr->CsdName_a_C = CST_NAME_C;
    CsdHeaderPtr->CsdName_a_S = CST_NAME_S;
    CsdHeaderPtr->CsdName_a_D = CSD_NAME_D;

    // Set CSD Body
    // --------------

    // Typecast the pointer
    CsdHeaderPtr++;
    CsdBodyPtr = (CSD_BODY_STRUCT *) CsdHeaderPtr;

    CsdBodyPtr->PkgOpcode     = PACKAGE_OPCODE;
    CsdBodyPtr->PkgLength     = CSD_BODY_SIZE - 1;
    CsdBodyPtr->PkgElements   = 1;
    CsdBodyPtr->PkgOpcode2    = PACKAGE_OPCODE;
    CsdBodyPtr->PkgLength2    = CSD_BODY_SIZE - 4; // CSD_BODY_SIZE - Package() - Package Opcode
    CsdBodyPtr->PkgElements2  = 6;
    CsdBodyPtr->BytePrefix    = BYTE_PREFIX_OPCODE;
    CsdBodyPtr->NumEntries    = 6;
    CsdBodyPtr->BytePrefix2   = BYTE_PREFIX_OPCODE;
    CsdBodyPtr->Revision      = 0;
    CsdBodyPtr->DWordPrefix   = DWORD_PREFIX_OPCODE;
    CsdBodyPtr->Domain        = (LocalApicId & 0xFE) >> 1;
    CsdBodyPtr->DWordPrefix2  = DWORD_PREFIX_OPCODE;
    CsdBodyPtr->CoordType     = CSD_COORD_TYPE_HW_ALL;
    CsdBodyPtr->DWordPrefix3  = DWORD_PREFIX_OPCODE;
    CsdBodyPtr->NumProcessors = 0x2;
    CsdBodyPtr->DWordPrefix4  = DWORD_PREFIX_OPCODE;
    CsdBodyPtr->Index         = 0x0;

    CsdBodyPtr++;

    // Update the pointer
    *SsdtPtr = CsdBodyPtr;
  }

  ObjSize = AmdAcpiCalCstObj (AmdCstateInfo, StdHeader);
  return ObjSize;
}

/**--------------------------------------------------------------------------------------
 *
 *  CreatePStateAcpiTables
 *
 *  Description:
 *     This is the common routine for creating ACPI P-State objects
 *
 *  Parameters:
 *    @param[in]     AmdPstateSocketInfo  Buffer that contains P-State information
 *    @param[in,out] SsdtPtr              ACPI SSDT table pointer
 *    @param[in]     CpuSsdtServices      A pointer to AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL
 *    @param[in]     LocalApicId          Local Apic Id
 *    @param[in]     StdHeader            Handle to config for library and services
 *
 *    @retval          Size of generated ACPI P-States objects
 *
 *---------------------------------------------------------------------------------------
 **/
UINT32
AmdCreatePStateAcpiTables (
  IN       AMD_PSTATE_SOCKET_INFO  *AmdPstateSocketInfo,
  IN OUT   VOID                   **SsdtPtr,
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL *CpuSsdtServices,
  IN       UINT8                    LocalApicId,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT8                      PstateCapLevelSupport;
  UINT8                      OemPerfPresentCap;
  UINT8                      PstateNum;
  UINT32                     SizeTemp;
  UINT32                     PstateCapInputMilliWatts;
  UINT32                     CurrSize;
  UINT32                     PstateCount;
  UINTN                      NumberOfCcds;
  UINTN                      NumberOfComplexes;
  UINTN                      NumberOfCores;
  UINTN                      NumberOfThreads;
  UINTN                      PowerInmW;
  BOOLEAN                    PstateCapEnable;
  BOOLEAN                    PstateCapLevelSupportDetermined;
  PCT_HEADER_BODY            *pPctAcpiTables;
  PSS_HEADER                 *pPssHeaderAcpiTables;
  PSS_BODY                   *pPssBodyAcpiTables;
  XPSS_HEADER                *pXpssHeaderAcpiTables;
  XPSS_BODY                  *pXpssBodyAcpiTables;
  PSD_HEADER                 *pPsdHeaderAcpiTables;
  PSD_BODY                   *pPsdBodyAcpiTables;
  PPC_HEADER_BODY            *pPpcAcpiTables;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL    *CoreTopology;
  AMD_CORE_TOPOLOGY_SERVICES_V2_PROTOCOL *CoreTopology2;
  EFI_STATUS                 CalledStatus;

  CurrSize = 0;
  PstateCount = 0;
  PstateCapEnable = FALSE;
  PstateCapLevelSupport = 0;
  PstateCapLevelSupportDetermined = TRUE;
  PstateCapInputMilliWatts = PcdGet32 (PcdAmdPowerCeiling);

  //Check Pstate Capability
  if (PstateCapInputMilliWatts != 0) {
    PstateCapEnable = TRUE;
    PstateCapLevelSupportDetermined = FALSE;
  }

  //====================
  // Set _PCT Table
  //====================

  // Typecast the pointer
  pPctAcpiTables = (PCT_HEADER_BODY *) *SsdtPtr;

  // Set _PCT Body
  //---------------
  if (PcdGetBool (PcdAmdAcpiCpuSsdtPct)) {
    pPctAcpiTables->NameOpcode                  = NAME_OPCODE;
    pPctAcpiTables->PctName_a__                 = PCT_NAME__;
    pPctAcpiTables->PctName_a_P                 = PCT_NAME_P;
    pPctAcpiTables->PctName_a_C                 = PCT_NAME_C;
    pPctAcpiTables->PctName_a_T                 = PCT_NAME_T;
    pPctAcpiTables->Value1                      = PCT_VALUE1;
    pPctAcpiTables->Value2                      = PCT_VALUE2;
    pPctAcpiTables->Value3                      = PCT_VALUE3;
    pPctAcpiTables->GenericRegDescription1      = GENERIC_REG_DESCRIPTION;
    pPctAcpiTables->Length1                     = PCT_LENGTH;
    pPctAcpiTables->AddressSpaceId1             = PCT_ADDRESS_SPACE_ID;
    pPctAcpiTables->RegisterBitWidth1           = PCT_REGISTER_BIT_WIDTH;
    pPctAcpiTables->RegisterBitOffset1          = PCT_REGISTER_BIT_OFFSET;
    pPctAcpiTables->Reserved1                   = PCT_RESERVED;
    pPctAcpiTables->ControlRegAddressLo         = PCT_CONTROL_REG_LO;
    pPctAcpiTables->ControlRegAddressHi         = PCT_CONTROL_REG_HI;
    pPctAcpiTables->Value4                      = PCT_VALUE4;
    pPctAcpiTables->Value5                      = PCT_VALUE5;
    pPctAcpiTables->GenericRegDescription2      = GENERIC_REG_DESCRIPTION;
    pPctAcpiTables->Length2                     = PCT_LENGTH;
    pPctAcpiTables->AddressSpaceId2             = PCT_ADDRESS_SPACE_ID;
    pPctAcpiTables->RegisterBitWidth2           = PCT_REGISTER_BIT_WIDTH;
    pPctAcpiTables->RegisterBitOffset2          = PCT_REGISTER_BIT_OFFSET;
    pPctAcpiTables->Reserved2                   = PCT_RESERVED;
    pPctAcpiTables->StatusRegAddressLo          = PCT_STATUS_REG_LO;
    pPctAcpiTables->StatusRegAddressHi          = PCT_STATUS_REG_HI;
    pPctAcpiTables->Value6                      = PCT_VALUE6;

    // Increment and then typecast the pointer
    pPctAcpiTables++;
    CurrSize += PCT_STRUCT_SIZE;

    *SsdtPtr = pPctAcpiTables;
  } // End of _PCT Table

  //====================
  // Set _PSS Table
  //====================

  // Typecast the pointer
  pPssHeaderAcpiTables = (PSS_HEADER *) pPctAcpiTables;
  pPssBodyAcpiTables   = (PSS_BODY *)   pPctAcpiTables;

  if (PcdGetBool (PcdAmdAcpiCpuSsdtPss)) {
    // Set _PSS Header
    //---------------

    // Note: Set pssLength and numOfItemsInPss later
    pPssHeaderAcpiTables->NameOpcode            = NAME_OPCODE;
    pPssHeaderAcpiTables->PssName_a__           = PSS_NAME__;
    pPssHeaderAcpiTables->PssName_a_P           = PSS_NAME_P;
    pPssHeaderAcpiTables->PssName_a_S           = PSS_NAME_S;
    pPssHeaderAcpiTables->PssName_b_S           = PSS_NAME_S;
    pPssHeaderAcpiTables->PkgOpcode             = PACKAGE_OPCODE;


    // Set _PSS Body
    //---------------

    // Typecast the pointer
    pPssBodyAcpiTables = (PSS_BODY *) (pPssHeaderAcpiTables + 1);

    PstateCount = 0;
    for (PstateNum = 0; PstateNum <= AmdPstateSocketInfo->PStateMaxValue; PstateNum++) {
      if (AmdPstateSocketInfo->PStateStruct[PstateNum].PStateEnable != 0) {
        pPssBodyAcpiTables->PkgOpcode           = PACKAGE_OPCODE;
        pPssBodyAcpiTables->PkgLength           = PSS_PKG_LENGTH;
        pPssBodyAcpiTables->NumOfElements       = PSS_NUM_OF_ELEMENTS;
        pPssBodyAcpiTables->DwordPrefixOpcode1  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->Frequency           = AmdPstateSocketInfo->PStateStruct[PstateNum].CoreFreq;
        pPssBodyAcpiTables->DwordPrefixOpcode2  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->Power               = AmdPstateSocketInfo->PStateStruct[PstateNum].Power;

        if (PstateCapEnable && (!PstateCapLevelSupportDetermined) && (PstateCapInputMilliWatts >= pPssBodyAcpiTables->Power)) {
          PstateCapLevelSupport = (UINT8) AmdPstateSocketInfo->PStateStruct[PstateNum].SwPstateNumber;
          PstateCapLevelSupportDetermined = TRUE;
        }

        pPssBodyAcpiTables->DwordPrefixOpcode3  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->TransitionLatency   = AmdPstateSocketInfo->TransitionLatency;
        pPssBodyAcpiTables->DwordPrefixOpcode4  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->BusMasterLatency    = AmdPstateSocketInfo->TransitionLatency;
        pPssBodyAcpiTables->DwordPrefixOpcode5  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->Control             = AmdPstateSocketInfo->PStateStruct[PstateNum].SwPstateNumber;
        pPssBodyAcpiTables->DwordPrefixOpcode6  = DWORD_PREFIX_OPCODE;
        pPssBodyAcpiTables->Status              = AmdPstateSocketInfo->PStateStruct[PstateNum].SwPstateNumber;

        pPssBodyAcpiTables++;
        PstateCount++;
      }
    } // for (PstateNum = 0; PstateNum < MPPSTATE_MAXIMUM_STATES; PstateNum++)

    if (PstateCapEnable && (!PstateCapLevelSupportDetermined)) {
      PstateCapLevelSupport = AmdPstateSocketInfo->PStateMaxValue;
    }

    OemPerfPresentCap = PcdGet8 (PcdAmdAcpiCpuPerfPresentCap);
    if (OemPerfPresentCap <= AmdPstateSocketInfo->PStateMaxValue) {

      CpuSsdtServices->GetPstatePower (CpuSsdtServices, OemPerfPresentCap, &PowerInmW);

      if (PowerInmW <= PstateCapInputMilliWatts) {
        PstateCapLevelSupport = OemPerfPresentCap;
      }
    }

    // Set _PSS Header again
    // Now Set pssLength and numOfItemsInPss
    SizeTemp = (PstateCount * PSS_BODY_STRUCT_SIZE) + 3;
    pPssHeaderAcpiTables->PssLength  = (SizeTemp << 4) & 0x0000FF00;
    pPssHeaderAcpiTables->PssLength |= (SizeTemp & 0x0000000F) | 0x00000040;
    pPssHeaderAcpiTables->NumOfItemsInPss = (UINT8) PstateCount;
    CurrSize += (PSS_HEADER_STRUCT_SIZE + (PstateCount * PSS_BODY_STRUCT_SIZE));

    *SsdtPtr = pPssBodyAcpiTables;
  } // End of _PSS Table

  //====================
  // Set XPSS Table
  //====================

  // Typecast the pointer
  pXpssHeaderAcpiTables = (XPSS_HEADER *) pPssBodyAcpiTables;
  pXpssBodyAcpiTables   = (XPSS_BODY *)   pPssBodyAcpiTables;

  if (PcdGetBool (PcdAmdAcpiCpuSsdtXpss)) {
    // Set XPSS Header
    //---------------

    // Note: Set the pssLength and numOfItemsInPss later
    pXpssHeaderAcpiTables->NameOpcode           = NAME_OPCODE;
    pXpssHeaderAcpiTables->XpssName_a_X         = PSS_NAME_X;
    pXpssHeaderAcpiTables->XpssName_a_P         = PSS_NAME_P;
    pXpssHeaderAcpiTables->XpssName_a_S         = PSS_NAME_S;
    pXpssHeaderAcpiTables->XpssName_b_S         = PSS_NAME_S;
    pXpssHeaderAcpiTables->PkgOpcode            = PACKAGE_OPCODE;

    // Set XPSS Body
    //---------------

    // Typecast the pointer
    pXpssBodyAcpiTables = (XPSS_BODY *) (pXpssHeaderAcpiTables + 1);

    for (PstateNum = 0; PstateNum <= AmdPstateSocketInfo->PStateMaxValue; PstateNum++) {
      if (AmdPstateSocketInfo->PStateStruct[PstateNum].PStateEnable != 0) {
        pXpssBodyAcpiTables->PkgOpcode          = PACKAGE_OPCODE;
        pXpssBodyAcpiTables->PkgLength          = XPSS_PKG_LENGTH;
        pXpssBodyAcpiTables->NumOfElements      = XPSS_NUM_OF_ELEMENTS;
        pXpssBodyAcpiTables->XpssValueTbd       = 04;
        pXpssBodyAcpiTables->DwordPrefixOpcode1 = DWORD_PREFIX_OPCODE;
        pXpssBodyAcpiTables->Frequency          = AmdPstateSocketInfo->PStateStruct[PstateNum].CoreFreq;
        pXpssBodyAcpiTables->DwordPrefixOpcode2 = DWORD_PREFIX_OPCODE;
        pXpssBodyAcpiTables->Power              = AmdPstateSocketInfo->PStateStruct[PstateNum].Power;
        pXpssBodyAcpiTables->DwordPrefixOpcode3 = DWORD_PREFIX_OPCODE;
        pXpssBodyAcpiTables->TransitionLatency  = AmdPstateSocketInfo->TransitionLatency;
        pXpssBodyAcpiTables->DwordPrefixOpcode4 = DWORD_PREFIX_OPCODE;
        pXpssBodyAcpiTables->BusMasterLatency   = AmdPstateSocketInfo->TransitionLatency;
        pXpssBodyAcpiTables->ControlBuffer      = ACPI_BUFFER;
        pXpssBodyAcpiTables->ControlLo          = AmdPstateSocketInfo->PStateStruct[PstateNum].SwPstateNumber;
        pXpssBodyAcpiTables->ControlHi          = 0;
        pXpssBodyAcpiTables->StatusBuffer       = ACPI_BUFFER;
        pXpssBodyAcpiTables->StatusLo           = AmdPstateSocketInfo->PStateStruct[PstateNum].SwPstateNumber;
        pXpssBodyAcpiTables->StatusHi           = 0;
        pXpssBodyAcpiTables->ControlMaskBuffer  = ACPI_BUFFER;
        pXpssBodyAcpiTables->ControlMaskLo      = 0;
        pXpssBodyAcpiTables->ControlMaskHi      = 0;
        pXpssBodyAcpiTables->StatusMaskBuffer   = ACPI_BUFFER;
        pXpssBodyAcpiTables->StatusMaskLo       = 0;
        pXpssBodyAcpiTables->StatusMaskHi       = 0;

        pXpssBodyAcpiTables++;
      }
    } // for (PstateNum = 0; PstateNum < MPPSTATE_MAXIMUM_STATES; PstateNum++)

    // Set XPSS Header again
    // Now set pssLength and numOfItemsInPss
    SizeTemp = (PstateCount * XPSS_BODY_STRUCT_SIZE) + 3;
    pXpssHeaderAcpiTables->XpssLength  = (SizeTemp << 4) & 0x0000FF00;
    pXpssHeaderAcpiTables->XpssLength |= (SizeTemp & 0x0000000F) | 0x00000040;
    pXpssHeaderAcpiTables->NumOfItemsInXpss = (UINT8) PstateCount;
    CurrSize += (XPSS_HEADER_STRUCT_SIZE + (PstateCount * XPSS_BODY_STRUCT_SIZE));

    *SsdtPtr = pXpssBodyAcpiTables;
  } // End of _XPSS Table

  //====================
  // Set _PSD Table
  //====================

  // Typecast the pointer
  pPsdHeaderAcpiTables = (PSD_HEADER *) pXpssBodyAcpiTables;
  pPsdBodyAcpiTables   = (PSD_BODY *)   pXpssBodyAcpiTables;

  NumberOfThreads = 1;
  CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesV2ProtocolGuid, NULL, &CoreTopology2);
  if (CalledStatus == EFI_SUCCESS) {
    CoreTopology2->GetCoreTopologyOnDie (CoreTopology2, AmdPstateSocketInfo->SocketNumber, 0, &NumberOfCcds, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
  } else {
    CalledStatus = gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopology);
    if (CalledStatus == EFI_SUCCESS) {
      NumberOfCcds = 1;
      CoreTopology->GetCoreTopologyOnDie (CoreTopology, AmdPstateSocketInfo->SocketNumber, 0, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
    }
  }
  ASSERT (!EFI_ERROR (CalledStatus));

  if ((AmdPstateSocketInfo->TotalLogicalCores != 1) && (PcdGetBool (PcdAmdAcpiCpuSsdtPsd)) && ((AmdPstateSocketInfo->IsPsdDependent) || (NumberOfThreads > 1))) {
    // Set _PSD Header
    //----------------
    pPsdHeaderAcpiTables->NameOpcode            = NAME_OPCODE;
    pPsdHeaderAcpiTables->PkgOpcode             = PACKAGE_OPCODE;
    pPsdHeaderAcpiTables->PsdLength             = PSD_HEADER_LENGTH;
    pPsdHeaderAcpiTables->Value1                = PSD_VALUE1;
    pPsdHeaderAcpiTables->PsdName_a__           = PSD_NAME__;
    pPsdHeaderAcpiTables->PsdName_a_P           = PSD_NAME_P;
    pPsdHeaderAcpiTables->PsdName_a_S           = PSD_NAME_S;
    pPsdHeaderAcpiTables->PsdName_a_D           = PSD_NAME_D;

    CurrSize += PSD_HEADER_STRUCT_SIZE;

    // Set _PSD Body
    //--------------

    // Typecast the pointer
    pPsdBodyAcpiTables = (PSD_BODY *) (pPsdHeaderAcpiTables + 1);

    pPsdBodyAcpiTables->PkgOpcode               = PACKAGE_OPCODE;
    pPsdBodyAcpiTables->PkgLength               = PSD_PKG_LENGTH;
    pPsdBodyAcpiTables->NumOfEntries            = NUM_OF_ENTRIES;
    pPsdBodyAcpiTables->BytePrefixOpcode1       = BYTE_PREFIX_OPCODE;
    pPsdBodyAcpiTables->PsdNumOfEntries         = PSD_NUM_OF_ENTRIES;
    pPsdBodyAcpiTables->BytePrefixOpcode2       = BYTE_PREFIX_OPCODE;
    pPsdBodyAcpiTables->PsdRevision             = PSD_REVISION;
    pPsdBodyAcpiTables->DwordPrefixOpcode1      = DWORD_PREFIX_OPCODE;

    if (AmdPstateSocketInfo->IsPsdDependent) {
      pPsdBodyAcpiTables->DependencyDomain      = PSD_DEPENDENCY_DOMAIN;
      pPsdBodyAcpiTables->CoordinationType      = PSD_COORDINATION_TYPE_SW_ALL;
      pPsdBodyAcpiTables->NumOfProcessors       = AmdPstateSocketInfo->TotalLogicalCores;
    } else {
      // Get number of threads per core
      ASSERT (NumberOfThreads != 0);
      pPsdBodyAcpiTables->DependencyDomain      = (UINT32) (LocalApicId / NumberOfThreads); //CpuSsdtServices->GetPsdDomain (CpuSsdtServices, LocalApicId);
      pPsdBodyAcpiTables->CoordinationType      = PSD_COORDINATION_TYPE_HW_ALL;
      pPsdBodyAcpiTables->NumOfProcessors       = (UINT32) NumberOfThreads;
    }
    pPsdBodyAcpiTables->DwordPrefixOpcode2      = DWORD_PREFIX_OPCODE;
    pPsdBodyAcpiTables->DwordPrefixOpcode3      = DWORD_PREFIX_OPCODE;

    pPsdBodyAcpiTables++;
    *SsdtPtr = pPsdBodyAcpiTables;
    CurrSize += PSD_BODY_STRUCT_SIZE;
  } // End of _PSD Table

  //====================
  // Set _PPC Table
  //====================

  // Typecast the pointer
  pPpcAcpiTables = (PPC_HEADER_BODY *) pPsdBodyAcpiTables;

  if (PcdGetBool (PcdAmdAcpiCpuSsdtPpc)) {
    // Name (PPCV, value)
    pPpcAcpiTables->NameOpcode                  = NAME_OPCODE;
    pPpcAcpiTables->PpcName_a_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_b_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_a_C                 = PPC_NAME_C;
    pPpcAcpiTables->PpcName_a_V                 = PPC_NAME_V;
    pPpcAcpiTables->Value1                      = PPC_VALUE1;
    pPpcAcpiTables->DefaultPerfPresentCap       = PstateCapLevelSupport;

    // Method (_PPC) { return (PPCV) }
    pPpcAcpiTables->MethodOpcode                = METHOD_OPCODE;
    pPpcAcpiTables->PpcLength                   = PPC_METHOD_LENGTH;
    pPpcAcpiTables->PpcName_a__                 = PPC_NAME__;
    pPpcAcpiTables->PpcName_c_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_d_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_b_C                 = PPC_NAME_C;
    pPpcAcpiTables->MethodFlags                 = PPC_METHOD_FLAGS;
    pPpcAcpiTables->ReturnOpcode                = RETURN_OPCODE;
    pPpcAcpiTables->PpcName_e_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_f_P                 = PPC_NAME_P;
    pPpcAcpiTables->PpcName_c_C                 = PPC_NAME_C;
    pPpcAcpiTables->PpcName_b_V                 = PPC_NAME_V;

    CurrSize += PPC_HEADER_BODY_STRUCT_SIZE;
    // Increment and typecast the pointer
    pPpcAcpiTables++;
    *SsdtPtr =  pPpcAcpiTables;
  } // End of _PPC Table

  return CurrSize;
}


