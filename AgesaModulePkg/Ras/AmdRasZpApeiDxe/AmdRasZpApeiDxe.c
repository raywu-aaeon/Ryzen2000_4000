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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "PiDxe.h"
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/RasZpBaseLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/MpService.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AmdRasApeiProtocol.h>
#include "AmdRasZpApeiDxe.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE RAS_AMDRASZPAPEIDXE_AMDRASZPAPEIDXE_FILECODE


/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
EFI_MP_SERVICES_PROTOCOL *MpServices = NULL;
AMD_RAS_POLICY           *mAmdRasPolicy;
ADDR_DATA               *gAddrData;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
AddBertErrorRecord (
  IN UINT8       *ErrorRecord,
  IN UINT32      RecordLen,
  IN UINT8       ErrorType,
  IN UINT8       SeverityType
  );

EFI_STATUS
AddHestErrorRecord (
  IN UINT8       *ErrorRecord,
  IN UINT32      RecordLen
  );

EFI_STATUS
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
  );

EFI_STATUS
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  );

VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  );

EFI_STATUS
SearchAcpiTable ( 
  IN       EFI_ACPI_TABLE_PROTOCOL      *AcpiTableProtocol,
  IN       EFI_ACPI_SDT_PROTOCOL        *AcpiSdtProtocol,
  IN       UINT32                       TableSignature,
  OUT      EFI_ACPI_SDT_HEADER          **Table,
  OUT      UINTN                        *TableKey
  );

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
extern  EFI_BOOT_SERVICES       *gBS;

/*----------------------------------------------------------------------------------------
 *                          T A B L E    D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/*
 * Calculate an ACPI style checksum
 *
 * Computes the checksum and stores the value to the checksum
 * field of the passed in ACPI table's header.
 *
 * @param[in]  Table             ACPI table to checksum
 *
 */
VOID
ChecksumAcpiTable (
  IN OUT   EFI_ACPI_DESCRIPTION_HEADER *Table
  )
{
  UINT8  *BuffTempPtr;
  UINT8  Checksum;
  UINT32 BufferOffset;

  Table->Checksum = 0;
  Checksum = 0;
  BuffTempPtr = (UINT8 *) Table;
  for (BufferOffset = 0; BufferOffset < Table->Length; BufferOffset++) {
    Checksum = Checksum - *(BuffTempPtr + BufferOffset);
  }

  Table->Checksum = Checksum;
}

/*---------------------------------------------------------------------------------------*/
/**
 * MCA_ADDR Address Translate
 *
 * Translate UMC local address into specific memory DIMM information and system address
 * 
 *
 * @param[in]   NormalizedAddress      UMC memory address Information
 * @param[out]  SystemMemoryAddress    System Address
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
AmdMcaErrorAddrTranslate (
  IN       NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      UINT64             *SystemMemoryAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{

  translate_norm_to_dram_addr (NormalizedAddress->normalizedAddr,
                               NormalizedAddress->normalizedSocketId,
                               NormalizedAddress->normalizedDieId,
                               NormalizedAddress->normalizedChannelId,
                               0,
                               &DimmInfo->ChipSelect,
                               &DimmInfo->Bank,
                               &DimmInfo->Row,
                               &DimmInfo->Column,
                               &DimmInfo->rankmul
                               );



  *SystemMemoryAddress = calcSysAddr(NormalizedAddress->normalizedAddr,
                                     NormalizedAddress->normalizedSocketId,
                                     NormalizedAddress->normalizedDieId,
                                     NormalizedAddress->normalizedChannelId
                                     );

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * System Address Translate
 *
 * Translate system address into specific memory DIMM information and normalized address
 * information
 *
 * @param[in]   SystemMemoryAddress    System Address
 * @param[out]  NormalizedAddress      UMC memory address Information
 * @param[out]  DimmInfo               DIMM information
 *
 */

EFI_STATUS
AmdTranslateSysAddrToCS (
  IN       UINT64             *SystemMemoryAddress,
  OUT      NORMALIZED_ADDRESS *NormalizedAddress,
  OUT      DIMM_INFO          *DimmInfo
)
{

  *NormalizedAddress = calcNormAddr(*SystemMemoryAddress);

  translate_norm_to_dram_addr (NormalizedAddress->normalizedAddr,
                               NormalizedAddress->normalizedSocketId,
                               NormalizedAddress->normalizedDieId,
                               NormalizedAddress->normalizedChannelId,
                               0,
                               &DimmInfo->ChipSelect,
                               &DimmInfo->Bank,
                               &DimmInfo->Row,
                               &DimmInfo->Column,
                               &DimmInfo->rankmul
                               );

  return EFI_SUCCESS;
}

EFI_STATUS
AmdSearchMcaError (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  )
{
  UINTN Index;
  BOOLEAN CpuMapFound = FALSE;

  if (RasMcaErrorInfo->CpuInfo.ProcessorNumber > mAmdRasPolicy->TotalNumberOfProcessors) {
    return EFI_INVALID_PARAMETER;
  }

  Index = 0;
  for (Index = 0; Index < mAmdRasPolicy->TotalNumberOfProcessors; Index++) {
      if (mAmdRasPolicy->RasCpuMap[Index].ProcessorNumber == RasMcaErrorInfo->CpuInfo.ProcessorNumber) {
        RasMcaErrorInfo->CpuInfo.SocketId = mAmdRasPolicy->RasCpuMap[Index].SocketId;
        RasMcaErrorInfo->CpuInfo.CcxId = mAmdRasPolicy->RasCpuMap[Index].CcxId;
        RasMcaErrorInfo->CpuInfo.DieId = mAmdRasPolicy->RasCpuMap[Index].DieId;
        RasMcaErrorInfo->CpuInfo.CoreId = mAmdRasPolicy->RasCpuMap[Index].CoreId;
        RasMcaErrorInfo->CpuInfo.ThreadID = mAmdRasPolicy->RasCpuMap[Index].ThreadID;
        CpuMapFound = TRUE;
        break;
      }
  }
  if (!CpuMapFound) {
      return EFI_NOT_FOUND;
  }

  //Program BSP first
  if (RasMcaErrorInfo->CpuInfo.ProcessorNumber == 0) {
    CollectMcaErrorInfo(RasMcaErrorInfo);
  } else {
    MpServices->StartupThisAP (
                               MpServices,
                               CollectMcaErrorInfo,
                               RasMcaErrorInfo->CpuInfo.ProcessorNumber,
                               NULL,
                               0,
                               (VOID *) RasMcaErrorInfo ,
                               NULL
    );
  }

  return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: AmdRasZpApeiDxeInit
 *
 * Description
 *   Entry point of the AMD RAS ZP APEI DXE driver
 *   Install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdRasZpApeiDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  EFI_HANDLE            Handle = NULL;
  AMD_RAS_APEI_PROTOCOL *AmdRasApeiProtocol;
  UINTN                 NumberOfEnabledProcessors;
  UINTN                 NumberOfLogicProcessors = 0;

  // Allocate Memory for the the AMD_RAS_APEI_PROTOCOL protocol.
  Status = gBS->AllocatePool (
                              EfiBootServicesData,              // IN EFI_MEMORY_TYPE PoolType
                              sizeof (AMD_RAS_APEI_PROTOCOL),   // IN UINTN Size
                              &AmdRasApeiProtocol               // OUT VOID **Buffer
                              );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;    // Error detected while trying to locate pool
  }

  // Get EFI MP service
  if (MpServices == NULL) {
    Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return Status;    // Error detected while trying to locate pool
    }
  }

  // Get AMD Ras Policy
  Status = gBS->LocateProtocol (&gAmdRasInitDataProtocolGuid, NULL, &mAmdRasPolicy);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;    // Error detected while trying to locate pool
  }

  //Init memory address data pointer
  gAddrData = mAmdRasPolicy->AddrData;

  // Get StartThisApFrom, StartThisApTo, StartThisApSteps
  MpServices->GetNumberOfProcessors (MpServices, &NumberOfLogicProcessors, &NumberOfEnabledProcessors);

  DEBUG((EFI_D_ERROR, "[RAS] TotalNumberOfProcessor = 0x%08x\n", mAmdRasPolicy->TotalNumberOfProcessors));

  //The logical processor number shoudl match to the avaliable processors reported from AGESA.
  ASSERT (NumberOfLogicProcessors == mAmdRasPolicy->TotalNumberOfProcessors);

  // Initialize function pointers to protocol interfaces
  AmdRasApeiProtocol->McaErrorAddrTranslate = &AmdMcaErrorAddrTranslate;
  AmdRasApeiProtocol->TranslateSysAddrToCS = &AmdTranslateSysAddrToCS;
  AmdRasApeiProtocol->AddBootErrorRecordEntry = &AddBertErrorRecord;
  AmdRasApeiProtocol->AddHestErrorSourceEntry = &AddHestErrorRecord;
  AmdRasApeiProtocol->SearchMcaError = &AmdSearchMcaError;

  Status = gBS->InstallProtocolInterface (
                                          &Handle,                  // IN OUT EFI_HANDLE
                                          &gAmdRasApeiProtocolGuid, // IN EFI_GUID
                                          EFI_NATIVE_INTERFACE,     // IN EFI_INITERFACE_TYPE
                                          AmdRasApeiProtocol        // IN VOID* Interface
                                          );
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return EFI_PROTOCOL_ERROR;
  }

  return (Status);
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  AddBertErrorRecord
 *
 *  Description:
 *     Adds a new Boot Error Record Entry to the APEI Boot Error Record Table (BERT).
 *
 *  Parameters:
 *    @param[in]     *ErrorRecord
 *    @param[in]     RecordLen
 *    @param[in]     ErrorType
 *    @param[in]     SeverityType
 *
 *    @retval         EFI_SUCCESS   Error record has been added to BERT table
 *                    EFI_UNSUPPORTED ErrorType passed in is unsupported
 *                    EFI_OUT_OF_RESOURCES  Could not allocate memory
 *                    EFI_VOLUME_FULL   cannot add one more error record
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
AddBertErrorRecord (
  IN UINT8  *ErrorRecord,
  IN UINT32 RecordLen,
  IN UINT8  ErrorType,
  IN UINT8  SeverityType
  )
{
  EFI_STATUS                Status = EFI_SUCCESS;
  EFI_ACPI_TABLE_PROTOCOL   *AcpiTableProtocol;
  EFI_ACPI_SDT_PROTOCOL     *AcpiSdtProtocol;
  EFI_ACPI_SDT_HEADER       *Table;
  UINTN                     TableKey;
  EFI_ACPI_6_0_BOOT_ERROR_RECORD_TABLE_HEADER   *BertTable;             // Local helper pointer
  EFI_ACPI_6_0_BOOT_ERROR_REGION_STRUCTURE      *NewBertErrRgnTable;
  EFI_ACPI_6_0_BOOT_ERROR_REGION_STRUCTURE      *OrgBertErrRgnTable;

  Status = gBS->LocateProtocol (
                  &gEfiAcpiTableProtocolGuid,
                  NULL,
                  &AcpiTableProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (
                  &gEfiAcpiSdtProtocolGuid,
                  NULL,
                  &AcpiSdtProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Table = NULL;
  Status = SearchAcpiTable(AcpiTableProtocol, AcpiSdtProtocol, BERT_SIG, &Table, &TableKey);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  BertTable = (EFI_ACPI_6_0_BOOT_ERROR_RECORD_TABLE_HEADER*)Table;

  // Get pointer to original Boot Error Region Ptr
  OrgBertErrRgnTable = (EFI_ACPI_6_0_BOOT_ERROR_REGION_STRUCTURE*) BertTable->BootErrorRegion;
  // First check to see if Error Data Entry Count has reached the maximum allowed (error count is stored in Bit[13:4])
  if (OrgBertErrRgnTable->BlockStatus.ErrorDataEntryCount == 0x3FF) {
      return EFI_VOLUME_FULL;
  }
 
  // Reserve ACPI system memory for new BERT Error Region Table + add-on error entries (Raw or Generic)
  Status = gBS->AllocatePool (EfiACPIMemoryNVS, BertTable->BootErrorRegionLength + RecordLen, &NewBertErrRgnTable);
  if (EFI_ERROR (Status))  {
    return Status;
  }

  switch (ErrorType)
  {
  case ERROR_TYPE_RAW:    // Raw data Error
    // Copy Error Region Data from Original BERT table Error Region into New BERT table
    gBS->CopyMem (NewBertErrRgnTable, OrgBertErrRgnTable, BertTable->BootErrorRegionLength);
    // Copy new Error Record data at the end of the current BERT table
    gBS->CopyMem ((UINT8*) NewBertErrRgnTable + BertTable->BootErrorRegionLength, ErrorRecord, RecordLen);
    // Update the RAW data length parameter with the new data length
    NewBertErrRgnTable->RawDataLength = OrgBertErrRgnTable->RawDataLength + RecordLen;
    break;

  case ERROR_TYPE_GENERIC:     // Generic Error (Note: **According to WHEA, RAW data must follow any Generic error data entries**)
    // Copy Original Error Region raw data into New BERT Error Region data
    gBS->CopyMem (NewBertErrRgnTable, OrgBertErrRgnTable, OrgBertErrRgnTable->RawDataOffset);
    // Copy new Generic Error Record data at the end of the current BERT table Error Region Offset but before the Raw data
    gBS->CopyMem ((UINT8*) NewBertErrRgnTable + OrgBertErrRgnTable->RawDataOffset, ErrorRecord, RecordLen);
    // Copy Original Raw Data after the new Generic Error Record Data
    if (OrgBertErrRgnTable->RawDataLength != 0) {
      gBS->CopyMem((UINT8*) (NewBertErrRgnTable + OrgBertErrRgnTable->RawDataOffset + RecordLen),\
                   (UINT8*) (OrgBertErrRgnTable + OrgBertErrRgnTable->RawDataOffset), OrgBertErrRgnTable->RawDataLength);
    }
    // Update the Raw data offset value
    NewBertErrRgnTable->RawDataOffset = OrgBertErrRgnTable->RawDataOffset + RecordLen;
    // Update the Generic data offset value
    NewBertErrRgnTable->DataLength = OrgBertErrRgnTable->DataLength + RecordLen;
    break;
  default:
    Status = EFI_UNSUPPORTED;
      return Status;
  }

  //The Severity Type priority from high to low:
  //FATAL > RECOVERABLE > CORRECTED
  //Always keep highest severity level in Generic Error Status Block.
  switch (SeverityType)
  {
  case ERROR_RECOVERABLE:
      if (NewBertErrRgnTable->ErrorSeverity != ERROR_SEVERITY_FATAL) {
        NewBertErrRgnTable->ErrorSeverity = ERROR_RECOVERABLE;
      }
    break;
  case ERROR_SEVERITY_FATAL:
    // If error type Uncorrectable AND multiple uncorrectable errors
    if (SeverityType == ERROR_SEVERITY_FATAL && (NewBertErrRgnTable->BlockStatus.MultipleUncorrectableErrors == 0)) {
      // If block status uncorrectable error valid
      if (NewBertErrRgnTable->BlockStatus.UncorrectableErrorValid) {
        NewBertErrRgnTable->BlockStatus.MultipleUncorrectableErrors = 1;
      } else {
        NewBertErrRgnTable->BlockStatus.UncorrectableErrorValid = 1;
      }
    }
    NewBertErrRgnTable->ErrorSeverity = ERROR_SEVERITY_FATAL;
    break;
  case ERROR_SEVERITY_CORRECTED:
    // If error type Correctable AND multiple corrected errors
    if (NewBertErrRgnTable->BlockStatus.MultipleCorrectableErrors == 0) {
      if (NewBertErrRgnTable->BlockStatus.CorrectableErrorValid) {
        NewBertErrRgnTable->BlockStatus.MultipleCorrectableErrors = 1;
      } else {
        NewBertErrRgnTable->BlockStatus.CorrectableErrorValid = 1;
      }
    }
    if (NewBertErrRgnTable->ErrorSeverity > ERROR_SEVERITY_CORRECTED) {
      NewBertErrRgnTable->ErrorSeverity = ERROR_SEVERITY_CORRECTED;
    }
    break;
  }

  // Update Error Data Entry Count to 1 in upper nibble
  NewBertErrRgnTable->BlockStatus.ErrorDataEntryCount = NewBertErrRgnTable->BlockStatus.ErrorDataEntryCount + 1;

  // Set Boot Error Region Pointer to new Bert Boot Error Region memory location
  BertTable->BootErrorRegion = (UINT64)((UINTN) NewBertErrRgnTable);
  // Set Boot Error Region length to new Bert Boot Error Region length
  BertTable->BootErrorRegionLength = BertTable->BootErrorRegionLength + RecordLen;


  ChecksumAcpiTable ((EFI_ACPI_DESCRIPTION_HEADER *) BertTable);

  //
  // Remove previous table
  //
  Status = AcpiTableProtocol->UninstallAcpiTable (
                                AcpiTableProtocol,
                                TableKey
                                );
  //
  // Add new table
  //
  Status = AcpiTableProtocol->InstallAcpiTable (
                                AcpiTableProtocol,
                                BertTable,
                                (UINTN)BertTable->Header.Length,
                                &TableKey
                                );
  // Free memory allocated for original Error Region record
  gBS->FreePool (OrgBertErrRgnTable);

  gBS->FreePool (BertTable);


  return Status;
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  AddHestErrorRecord
 *
 *  Description:
 *     Adds a new Hardware Error Source Record Entry to the APEI Hardware Error Source Table (HEST).
 *
 *  Parameters:
 *    @param[in]     *ErrorRecord
 *    @param[in]     RecordLen
 *
 *    @retval         EFI_SUCCESS  Error record has been added to HEST table
 *                    EFI_UNSUPPORTED  ErrorType passed in is unsupported
 *                    EFI_OUT_OF_RESOURCES  Could not allocate memory
 *                    EFI_VOLUME_FULL  Cannot add one more error record
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
AddHestErrorRecord (
  IN UINT8  *ErrorRecord,
  IN UINT32 RecordLen
  )
{
  EFI_STATUS                Status = EFI_SUCCESS;
  EFI_ACPI_TABLE_PROTOCOL   *AcpiTableProtocol;
  EFI_ACPI_SDT_PROTOCOL     *AcpiSdtProtocol;
  EFI_ACPI_SDT_HEADER       *Table;
  UINTN                     TableKey;
  UINT8                     *HestTableEnd;
  EFI_ACPI_6_0_HARDWARE_ERROR_SOURCE_TABLE_HEADER *OldHestTable;             // Local helper pointer
  EFI_ACPI_6_0_HARDWARE_ERROR_SOURCE_TABLE_HEADER *NewHestTable;

  Status = gBS->LocateProtocol (
                  &gEfiAcpiTableProtocolGuid,
                  NULL,
                  &AcpiTableProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (
                  &gEfiAcpiSdtProtocolGuid,
                  NULL,
                  &AcpiSdtProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Table = NULL;
  Status = SearchAcpiTable(AcpiTableProtocol, AcpiSdtProtocol, EFI_ACPI_6_0_HARDWARE_ERROR_SOURCE_TABLE_SIGNATURE, &Table, &TableKey);
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "[RAS]HEST table not found !!!\n"));
    return Status;
  }

  OldHestTable = (EFI_ACPI_6_0_HARDWARE_ERROR_SOURCE_TABLE_HEADER *)Table;

  Status = gBS->AllocatePool (EfiACPIMemoryNVS, OldHestTable->Header.Length + RecordLen, &NewHestTable);

  gBS->CopyMem (NewHestTable, OldHestTable, OldHestTable->Header.Length);

  HestTableEnd = (UINT8*)((UINTN)NewHestTable + NewHestTable->Header.Length);
  gBS->CopyMem (HestTableEnd, ErrorRecord, RecordLen);

  NewHestTable->Header.Length += RecordLen;
  NewHestTable->ErrorSourceCount++;

  ChecksumAcpiTable ((EFI_ACPI_DESCRIPTION_HEADER *) NewHestTable);

  //
  // Remove previous table
  //
  Status = AcpiTableProtocol->UninstallAcpiTable (
                                AcpiTableProtocol,
                                TableKey
                                );
  //
  // Add new table
  //
  Status = AcpiTableProtocol->InstallAcpiTable (
                                AcpiTableProtocol,
                                NewHestTable,
                                (UINTN)NewHestTable->Header.Length,
                                &TableKey
                                );

  gBS->FreePool (OldHestTable);
  gBS->FreePool (NewHestTable);


 return Status;
}


VOID
CollectMcaErrorInfo (
  IN OUT   RAS_MCA_ERROR_INFO* RasMcaErrorInfo
  )
{
  UINT32 i;
  UINT8 BankNum;
  UINT64 MsrData;
  MCA_STATUS_MSR McaStatusMsr;

  MsrData = AsmReadMsr64 (MSR_MCG_CAP);            // MCG_CAP
  BankNum = (UINT8)(MsrData & 0xFF);

  for (i = 0; i < BankNum; i++) {
    if (i == MCA_EMPTY0_BANK)
	  continue;
    //Find error log
    McaStatusMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_STATUS_OFFSET));
    if (McaStatusMsr.Field.Val) {
      //Collect MSR value
      RasMcaErrorInfo->McaBankErrorInfo[i].McaBankNumber = i;
      RasMcaErrorInfo->McaBankErrorInfo[i].McaStatusMsr.Value = McaStatusMsr.Value;
      RasMcaErrorInfo->McaBankErrorInfo[i].McaAddrMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_ADDR_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaConfigMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_CONFIG_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaIpidMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_IPID_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaSyndMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_SYND_OFFSET));
      RasMcaErrorInfo->McaBankErrorInfo[i].McaMisc0Msr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC0_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaMisc1Msr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_MISC1_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaDeStatMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_DESTAT_OFFSET));
        RasMcaErrorInfo->McaBankErrorInfo[i].McaDeAddrMsr.Value = AsmReadMsr64((MCA_EXTENSION_BASE + (i * 0x10) | MCA_DEADDR_OFFSET));
      }
    }
}



EFI_STATUS
SearchAcpiTable ( 
  IN       EFI_ACPI_TABLE_PROTOCOL      *AcpiTableProtocol,
  IN       EFI_ACPI_SDT_PROTOCOL        *AcpiSdtProtocol,
  IN       UINT32                       TableSignature,
  OUT      EFI_ACPI_SDT_HEADER          **Table,
  OUT      UINTN                        *TableKey
)
{
  EFI_STATUS                                Status;
  INTN                                      Index;
  EFI_ACPI_TABLE_VERSION                    Version;
  UINTN                                     TempTableKey;
  EFI_ACPI_SDT_HEADER                       *TempTable;

  //
  // Search table
  //
  Index  = 0;
  do {
    TempTable = NULL;
    Status = AcpiSdtProtocol->GetAcpiTable (
                                Index,
                                &TempTable,
                                &Version,
                                &TempTableKey
                                );
    if (EFI_ERROR (Status)) {
      //no more table
      break;
    }
    //
    // Check Signture
    //
    if (TempTable->Signature == TableSignature) {
        *Table = TempTable;
        *TableKey = TempTableKey;
        return Status;
    }
    //GetAcpiTable will allocate a buffer to store a copy of the table and return the pointer to the caller.
    //Free the buffer in every search.
    gBS->FreePool (TempTable);
    Index++;
  } while (TRUE);

  return Status;
}


