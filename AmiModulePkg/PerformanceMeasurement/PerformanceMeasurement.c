//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file PerformanceMeasurement.c
 *  Show the system performance.
 */

#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/Performance.h>
#include "PerformanceMeasurement.h"
#include <Protocol/AcpiSupport.h>
#include <Guid/Performance.h>
#include "PerformanceMeasurementSmm.h"

#include <Protocol/DriverBinding.h>
#include <Protocol/DevicePathToText.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/UefiLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/PrintLib.h>
#include <Protocol/AcpiTable.h>
#include <Library/TimerLib.h>

#include <Protocol/SmmCommunication.h>
#include <Guid/SmmVariableCommon.h>



/// Globol GUID
#ifndef AMITSE_EVENT_BEFORE_BOOT_GUID
#define AMITSE_EVENT_BEFORE_BOOT_GUID  { 0x3677770f, 0xefb2, 0x43b2, {0xb8, 0xae, 0xb3, 0x2, 0xe9, 0x60, 0x48, 0x82 }}
#endif
EFI_GUID  gAcpiSupportGuid = EFI_ACPI_SUPPORT_GUID;
EFI_GUID  gBeforeBootProtocolGuid = AMITSE_EVENT_BEFORE_BOOT_GUID;
extern EFI_GUID gAmiGlobalVariableGuid;

/// Subfunction
VOID 
SavePerformanceData(
    IN MEASUREMENT_RECORD   *RecordDumpData,
    IN UINTN                TotalNumbers,
    IN UINT64               Freq
);

VOID 
SetPmAcpiTable( 
    IN FPDT_50                *TableData,
    IN EFI_PHYSICAL_ADDRESS   AcpiLowMemoryBase
);

VOID 
SortPmData( 
    IN UINT32                 AcpiLowMemoryBase
);

EFI_STATUS 
GetNameFromHandle (
  IN EFI_HANDLE     Handle,
  IN OUT CHAR16*    GaugeString,
  IN OUT EFI_GUID** LogGuid
  );

VOID 
GetShortPdbFileName (
  IN  CHAR8         *PdbFileName,
  OUT CHAR16        *UnicodeBuffer
  );

VOID 
ZeroMem(
  IN OUT VOID       *Buffer,
  IN UINTN          Size
);

EFI_STATUS 
GetFvNameHOB ( 
  IN OUT EFI_HOB_GUID_TYPE    **HobHead
);

EFI_STATUS 
GetNameFromUi (
  IN OUT UINT8                *PdbFileName,
  IN EFI_GUID                 *Guid 
);

EFI_STATUS 
GetPerformanceDataSystemScopeToolFormatStyle (
  IN MEASUREMENT_RECORD       *RecordDumpData,
  IN UINTN                    TotalNumbers,
  IN UINT64                   Freq
);

VOID 
EFIAPI 
GetPerfSmmData(
  IN UINT64                   Freq
);

EFI_STATUS ConvertStrToBuf (
  OUT UINT8                   *Buf,
  IN  UINTN                   BufferLength,
  IN  CHAR16                  *Str
);

EFI_STATUS ConvertStrToGuid (
  IN  CHAR16                 *Str,
  OUT EFI_GUID               *Guid
);
	
/// Globol variable
EFI_SYSTEM_TABLE        *gST;
EFI_BOOT_SERVICES       *gBS;
EFI_RUNTIME_SERVICES    *gRT;
UINT8                   *gPtr;
UINT32                  gDataCount = 0;
UINT64                  gStartValue;
BOOLEAN                 gCountDownTimer = FALSE;
UINT64                  gRelativePoint = 0;

/// Global Buffers used for SMM Communicate
UINT8                   *gPerformanceMeasurementCommunicateBuffer = NULL;
UINTN                   gPerformanceMeasurementCommunicateBufferSize;

/**
 * Set PM under AMITSE_EVENT_BEFORE_BOOT_GUID.
 *    
 * @param[in]   ImageHandle                The firmware allocated handle for the EFI image. 
 * @param[in]   SystemTable                A pointer to the EFI System Table.
 *
 * @retval EFI_SUCCESS                    The entry point is executed successfully.
 */

EFI_STATUS 
EFIAPI 
PmEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{        
/**
    EFI_EVENT       eLegacyBoot=NULL;
**/
    EFI_STATUS      Status;
    EFI_EVENT       FunctionEvent = NULL;
    VOID            *Registration;

    InitAmiLib(ImageHandle, SystemTable);
    gST=SystemTable;
    
    /// Buffers Allocated for SMM Communication As new core doesn't allow Buffers which are allocated after EndofDXE.
    /// Maximum Size of Buffer allocated
    
    gPerformanceMeasurementCommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof(PM_SMM_DATA_STRUCTURE);
    ///
    /// Allocate Memory for Communication buffer.   
    ///
    Status = gBS->AllocatePool( EfiRuntimeServicesData,
                                gPerformanceMeasurementCommunicateBufferSize,
                                (VOID**)&gPerformanceMeasurementCommunicateBuffer );
    
    if ( EFI_ERROR( Status )) {
        return Status;
    }

    /// Sample code for register callback function to ReadyToBoot event.
/**
    Status = CreateReadyToBootEvent( TPL_CALLBACK, PmBuild, NULL, &eLegacyBoot);
**/
    /// Register AMITSE_EVENT_BEFORE_BOOT_GUID callback
    /// Note, if your project doesn't use AMITSE_EVENT_BEFORE_BOOT_GUID callback,
    /// This function will NOT run.
    RegisterProtocolCallback(
        &gBeforeBootProtocolGuid,
        PmBuild,
        NULL, &FunctionEvent, &Registration
    );
    CreateLegacyBootEvent( TPL_CALLBACK, PmBuild, NULL, &FunctionEvent );
    return EFI_SUCCESS;
}

/**
 * Locate performance and CPU frequency.
 *    
 * @param[in]   Event                The Event that is being processed.
 * @param[in]   Context            The Event Context.
 *
 */

VOID 
EFIAPI 
PmBuild(
    IN EFI_EVENT        Event,
    IN VOID             *Context 
)
{
    EFI_STATUS                Status;               
    UINT64                    Freq;
    EFI_PHYSICAL_ADDRESS      AcpiLowMemoryBase;
    EFI_ACPI_TABLE_VERSION    Version;
    UINT16                    Index;
    EFI_ACPI_SUPPORT_PROTOCOL *AcpiSupport;
    FPDT_50                   *TableData;
    UINTN                     RsdtTblHandle;
#if !SYSTEM_SCOPE_TOOL_FORMAT
    PERF_TAB_HEADER           PerfTabHeader;
    EFI_PERF_S3_INFO          PerfS3Info;
    EFI_PERF_DATA             *S3Entry;
    EFI_PERF_INFO             PerfInfo;
    UINTN                     PageStoreSize = 0;
#endif
    BOOLEAN                   FpdtFind = FALSE;
    UINTN                     LogEntryKey = 0;
    CHAR16                    *DataName;
    CHAR8                     *TempHost;
    CHAR8                     *Dest;
    CHAR16                    *Src;
#if PERFORMANCE_LIBRARY_INCLUDE
    MEASUREMENT_RECORD        Measurement;
    CHAR8                     *TempToken;
    CHAR8                     *TempModule;
    EFI_FPDT_STRUCTURE        *FpdtVariable = NULL;
    UINTN                     DataSize;
#else
    PERFORMANCE_PROTOCOL      *Perf;
    UINT64                    Endtime;
    GAUGE_DATA_ENTRY          *OrgData;
#endif
    UINTN                     TotalNumber = 0;
    MEASUREMENT_RECORD        *TempDumpData = NULL;
    UINTN                     Count = 0;
    EFI_GUID                  *LogGuid = NULL;
    static BOOLEAN            FirstRun = TRUE;
    
    gBS = gST->BootServices;
    
     if (!FirstRun) {
         gBS->CloseEvent(Event);
         return;
     }
     
    DataName = MallocZ(EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR16));
    TempHost = MallocZ(EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR8));
        
#if !PERFORMANCE_LIBRARY_INCLUDE
        Status = gBS->LocateProtocol( &gPerformanceProtocolGuid, NULL, (VOID**)&Perf);
        if (EFI_ERROR(Status)){
            gBS->CloseEvent(Event);
            return;
        }
        Freq = GetPerformanceCounterProperties(&gStartValue, &Endtime);
        gCountDownTimer = gStartValue > Endtime;
        if (Freq == 0) {
            gBS->CloseEvent(Event);
            return;
        }
        
        /// Set variable then in S3, 
        /// we can know how to calculate time.
        gRT->SetVariable (
             L"PMStartValue",
             &gAmiGlobalVariableGuid,
             EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
             sizeof (UINT64),
             &gStartValue
             );        
        
        while (1) {
            Status = Perf->GetGauge(LogEntryKey, &OrgData);
            if (EFI_ERROR(Status)) {
                break;
            }
            LogEntryKey ++;
            TotalNumber ++;
        }
        
        if (TotalNumber <= 3) {
            gBS->CloseEvent(Event);
            return;
        }
        PERF_END(0, "BDS", NULL, 0);
		
		/* note:Remove the added number since it creates an empty record.*/
        //TotalNumber ++;    /// Add number for BDS End
        
        Status = gBS->AllocatePool(EfiBootServicesData, (TotalNumber + 1) * sizeof(MEASUREMENT_RECORD), (VOID**)&TempDumpData);
        gBS->SetMem (TempDumpData, (TotalNumber + 1) * sizeof(MEASUREMENT_RECORD), 0);
        if(EFI_ERROR(Status)) {
            gBS->CloseEvent(Event);    
            return ;
        }
        
        LogEntryKey = 0;
        while (1) {
            LogGuid = NULL;
            Status = Perf->GetGauge(LogEntryKey, &OrgData);
            if (EFI_ERROR(Status)) {
                break;
            }
            Status = GetNameFromHandle((EFI_HANDLE)OrgData->Handle, DataName, &LogGuid);
            if (!EFI_ERROR(Status)) {
                Src = DataName;
                Dest = (UINT8 *) TempHost;
                while (*Src) *Dest++ = (UINT8) (*Src++);
                *Dest = 0;
                MemCpy(&TempDumpData[Count].PdbFileName, TempHost, EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR8)); 
                
            }
            
            if (OrgData->Token[0] != 0) {
                Strcpy(TempDumpData[Count].Token, OrgData->Token);
            }
            if ( OrgData->Module[0] != 0) {
                Strcpy(TempDumpData[Count].Module, OrgData->Module);
            }
            
            TempDumpData[Count].StartTimeStamp = OrgData->StartTimeStamp;
            TempDumpData[Count].EndTimeStamp = OrgData->EndTimeStamp;
            if ((EFI_HANDLE)OrgData->Handle != NULL) {
                TempDumpData[Count].Handle = (EFI_HANDLE)OrgData->Handle;
            }
            if (LogGuid != NULL) { 
                MemCpy(&TempDumpData[Count].GuidName, LogGuid, sizeof(EFI_GUID)); 
            }
            
            LogEntryKey ++;
            Count ++;
        }
#else
        do {
        LogEntryKey = GetPerformanceMeasurementEx (
                                    LogEntryKey,
                                    &Measurement.Handle,
                                    &TempToken,
                                    &TempModule,
                                    &Measurement.StartTimeStamp,
                                    &Measurement.EndTimeStamp,
                                    &Measurement.Identifier);
        TotalNumber ++;
        } while (LogEntryKey != 0);
        if (TotalNumber <= 1) {
                gBS->CloseEvent(Event);              
                return ;
        }
        PERF_END(0, "BDS", NULL, 0);
        
        TotalNumber ++;    /// Add number for BDS End
        
        Status = gBS->AllocatePool(EfiBootServicesData, (TotalNumber + 1) * sizeof(MEASUREMENT_RECORD), (VOID**)&TempDumpData);
        gBS->SetMem (TempDumpData, (TotalNumber + 1) * sizeof(MEASUREMENT_RECORD), 0);
        if (EFI_ERROR(Status)) {
            gBS->CloseEvent(Event);    
            return ;
        }

        do {
            LogGuid = NULL;
            LogEntryKey = GetPerformanceMeasurementEx (
                                    LogEntryKey,
                                    &Measurement.Handle,
                                    &TempToken,
                                    &TempModule,
                                    &Measurement.StartTimeStamp,
                                    &Measurement.EndTimeStamp,
                                    &Measurement.Identifier);
            
            Status = GetNameFromHandle(Measurement.Handle, DataName, &LogGuid);
            if (!EFI_ERROR(Status)) {
                Src = DataName;
                Dest = (UINT8 *) TempHost;
                while (*Src) *Dest++ = (UINT8) (*Src++);
                *Dest = 0;
                MemCpy(&TempDumpData[Count].PdbFileName, TempHost, EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR8)); 
            }
            
            if (TempToken[0] != 0) {
                Strcpy(TempDumpData[Count].Token, TempToken);
            }
            if ( TempModule[0] != 0) {
                Strcpy(TempDumpData[Count].Module, TempModule);
            }
            
            TempDumpData[Count].StartTimeStamp = Measurement.StartTimeStamp;
            TempDumpData[Count].EndTimeStamp = Measurement.EndTimeStamp;
            if (Measurement.Handle != NULL) {
                TempDumpData[Count].Handle = Measurement.Handle;
            }
            if (LogGuid != NULL) { 
                MemCpy(&TempDumpData[Count].GuidName, LogGuid, sizeof(EFI_GUID)); 
            }
            Count ++;
        } while (LogEntryKey != 0);

    /// Get CPU frequency from FPDT variable
    Status = gRT->GetVariable( EFI_FPDT_VARIABLE, &gAmiGlobalVariableGuid, NULL, &DataSize, &FpdtVariable);
    if (EFI_ERROR (Status)) { 
        gBS->CloseEvent(Event);
        return ;
    }
    
      Freq = FpdtVariable->NanoFreq;
#endif        /// Ened !PERFORMANCE_LIBRARY_INCLUDE if

#if !SYSTEM_SCOPE_TOOL_FORMAT 
      PageStoreSize = sizeof(EFI_PERF_S3_INFO) + 
                      EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA) + 
                      sizeof (EFI_PERF_INFO) + 
                      TotalNumber * sizeof(EFI_PERF_DATA) + 
                      sizeof(PERF_TAB_HEADER) + 
                      3 * sizeof(EFI_PHASE_PERF_DATA);
      
      Status = gBS->AllocatePages (
            AllocateAnyPages,
            EfiRuntimeServicesData,
            EFI_SIZE_TO_PAGES (PageStoreSize),
            &AcpiLowMemoryBase
         );
    if (EFI_ERROR (Status)) { 
        gBS->CloseEvent(Event);              
        return ;
    }
        /// Initialize memory
    gBS->SetMem (&PerfS3Info, sizeof (EFI_PERF_S3_INFO), 0);
    gBS->SetMem (&PerfInfo, sizeof (EFI_PERF_INFO), 0);
    S3Entry = (EFI_PERF_DATA *) ((UINT32) AcpiLowMemoryBase + 
              sizeof(PERF_TAB_HEADER) + 
              sizeof(EFI_PERF_S3_INFO));
    gBS->SetMem (S3Entry, EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA), 0);
    
        /// Save CpuFreq
    PerfInfo.CpuFreq = Freq; /// Millisecond

    PerfInfo.Signiture = PERF_SIG;
    PerfS3Info.S3EntryReservedSpaceNumber = EFI_PERF_PEI_ENTRY_MAX_NUM;
        gPtr = (UINT8 *) ((UINT32) AcpiLowMemoryBase + 
               sizeof(EFI_PERF_S3_INFO) + 
               EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA) + 
               sizeof (EFI_PERF_INFO) + 
               sizeof(PERF_TAB_HEADER));
#endif /// End !SYSTEM_SCOPE_TOOL_FORMAT if
#if SYSTEM_SCOPE_TOOL_FORMAT        
    Status = GetPerformanceDataSystemScopeToolFormatStyle(TempDumpData, TotalNumber, Freq);
        if (EFI_ERROR (Status)) { 
            gBS->CloseEvent(Event);              
            return ;
        }
#else
        SavePerformanceData(TempDumpData, TotalNumber, Freq);
#if PM_SMM_DATA
        /// Get Smm data.
        GetPerfSmmData(Freq);
#endif
        PerfInfo.Count = gDataCount;

        gBS->CopyMem (
                     (UINTN *) (UINTN) (AcpiLowMemoryBase + 
                             sizeof(PERF_TAB_HEADER) + 
                             sizeof(EFI_PERF_S3_INFO) + 
                             EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA)
                             ),
                     &PerfInfo,
                     sizeof (EFI_PERF_INFO)
                     );
        gBS->CopyMem (
                     (UINTN *) (UINTN) (AcpiLowMemoryBase + 
                     sizeof(PERF_TAB_HEADER)),
                     &PerfS3Info,
                     sizeof (EFI_PERF_S3_INFO)
                     );
        gBS->SetMem (&PerfTabHeader, sizeof (PERF_TAB_HEADER), 0);
        PerfTabHeader.Signature = PMPT_SIG; /// PMPT
        PerfTabHeader.Length =  (UINT32)TotalNumber * sizeof (EFI_PERF_DATA) +
                                sizeof(EFI_PERF_S3_INFO) + 
                                EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA) + 
                                sizeof (EFI_PERF_INFO) + 
                                3 * sizeof (EFI_PHASE_PERF_DATA) +
                                sizeof (PERF_TAB_HEADER);

        gBS->CopyMem (
             (UINTN *) (UINTN) (AcpiLowMemoryBase),
             &PerfTabHeader,
             sizeof (PERF_TAB_HEADER)
             );

        /// Set variable then in S3, 
        /// S3 performance can get address to put data
        gRT->SetVariable (
             L"PMPerfDataMemAddr",
             &gAmiGlobalVariableGuid,
             EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
             sizeof (UINT32),
             (VOID *) &AcpiLowMemoryBase
             );
        /// Sort performance data by start time
        SortPmData((UINT32) AcpiLowMemoryBase);
#endif
        /// Get protocol
        Status = gBS->LocateProtocol(&gAcpiSupportGuid, NULL, (VOID**)&AcpiSupport);

        for (Index = 0; Index < ACPI_RSDT_TABLE_NUM; Index++) {
            Status = AcpiSupport->GetAcpiTable (AcpiSupport,
                                                Index, 
                                                &TableData,
                                                &Version, 
                                                &RsdtTblHandle);

            if ((TableData->Header.Signature) == FPDT_SIG) {
                FpdtFind = TRUE;
                break;
            }
        }

    if (FpdtFind) {
#if SYSTEM_SCOPE_TOOL_FORMAT        
        AcpiLowMemoryBase = (EFI_PHYSICAL_ADDRESS)(UINTN)gPtr;
#endif
        SetPmAcpiTable(TableData, AcpiLowMemoryBase);
        /// Remove old table
        Status = AcpiSupport->SetAcpiTable (AcpiSupport, 
                                    NULL, 
                                    FALSE, 
                                    EFI_ACPI_TABLE_VERSION_4_0, 
                                    &RsdtTblHandle);
        if (EFI_ERROR (Status)) { 
            gBS->CloseEvent(Event);              
            return ;
        }
    }
    
    FirstRun = FALSE;
        ///    End
        ///    Close ReadyToBootEvent.
    gBS->CloseEvent(Event);

    return ;
}

/**
 * Save performance data and operation time about handle used.
 *    
 * @param[in]   RecordDumpData                Performance record data. 
 * @param[in]   TotalNumbers                    Total data numbers.
 * @param[in]   Freq                                    CPU frequence.
 *
 */

VOID 
SavePerformanceData(
        IN MEASUREMENT_RECORD              *RecordDumpData,
        IN UINTN    TotalNumbers,
    IN UINT64                       Freq 
)
{
    EFI_STATUS                Status = 0;
    UINTN                     TempCount;
    EFI_PERF_DATA             PerfData;
    UINT64                    StartTime = 0;
    UINT64                    EndTime = 0;
    EFI_LOADED_IMAGE_PROTOCOL *pImage;
    EFI_PHASE_PERF_DATA PhaseData[3] = {
    "SEC", 0, 0, 0,
    "PEI", 0, 0, 0,
    "DXE", 0, 0, 0
    };
    UINT8                     *TempPtr = gPtr;
    BOOLEAN                   HobFound = FALSE;
    EFI_HOB_GUID_TYPE         *HobHead;
    FV_NAME_HOB               *FvNameHob;
    UINT16                    Count = 0;
    UINT32                    DataNumber;
    UINT64                    RelativePoint = 0;
    CHAR16                    LogGuidStr[STR_SIZE_FOR_GUID] = {0};
    /// Get hob that save pei module name.
    Status = GetFvNameHOB(&HobHead);
    if (!EFI_ERROR(Status)) {
        HobFound = TRUE;
        FvNameHob = (FV_NAME_HOB *)(HobHead+1);
    }

    DataNumber = (UINT32) (Div64 ( (HobHead)->Header.HobLength, (EFI_PERF_PDBFILENAME_LENGTH + sizeof(EFI_GUID)), NULL));
    
    gPtr += 3 * sizeof (EFI_PHASE_PERF_DATA);
#if RELATIVE_TIME    
    /// Get Pei phase Start time.
    for (TempCount = 0; TempCount < TotalNumbers; TempCount ++) {
        if (!Strcmp(RecordDumpData[TempCount].Token, "SEC")) {
            /// If PEI data lost, use SEC end timme.
            RelativePoint = RecordDumpData[TempCount].EndTimeStamp;
        }
        if (!Strcmp(RecordDumpData[TempCount].Token, "PEI")) {
            RelativePoint = RecordDumpData[TempCount].StartTimeStamp;
            break;
        }
    }
    gRelativePoint = RelativePoint;
#endif
    for (TempCount = 0; TempCount < TotalNumbers; TempCount ++) {
        /// Skip Support data.
        if (!Strcmp(RecordDumpData[TempCount].Token, "DB:Support:")) {
            continue;
        }
        gBS->SetMem (&PerfData, sizeof (EFI_PERF_DATA), 0);
        
        StartTime = RecordDumpData[TempCount].StartTimeStamp;
        EndTime = RecordDumpData[TempCount].EndTimeStamp;

        if (!Strcmp(RecordDumpData[TempCount].Token, "PEIM")) {
            PerfData.Guid = ((EFI_FFS_FILE_HEADER*)(RecordDumpData[TempCount].Handle))->Name;
#if !OPTIMIZE_BOOT_FV_COPY
            Status = GetNameFromUi(&(RecordDumpData[TempCount].PdbFileName[0]), &PerfData.Guid);
#else
            /// In this part, we use hob data to get Fv name.
            if (HobFound == TRUE) { /// Hub found, check GUID and find Fv name.
                for (Count = 0; Count < DataNumber; Count++) {
                    if (!guidcmp(&(PerfData.Guid),&((FvNameHob[Count]).FvGuid))) { /// GUID match
                        Strcpy (RecordDumpData[TempCount].PdbFileName, (FvNameHob[Count]).NameString);
                    }
                }
            }
#endif
        } else {
            Status = gBS->HandleProtocol (RecordDumpData[TempCount].Handle, &gEfiLoadedImageProtocolGuid, (VOID**)&pImage);
            if (!EFI_ERROR(Status)
                 && pImage->FilePath->Type ==  MEDIA_DEVICE_PATH
                 && pImage->FilePath->SubType == MEDIA_FV_FILEPATH_DP) {
                gBS->CopyMem (&(PerfData.Guid), &( ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*) pImage->FilePath)->FvFileName), sizeof (EFI_GUID)); 
                Status = GetNameFromUi(&(RecordDumpData[TempCount].PdbFileName[0]), &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*) pImage->FilePath)->FvFileName);
            } else { // Get GUID from inputted handle
                ZeroMem (LogGuidStr, sizeof (LogGuidStr));
                UnicodeSPrint (LogGuidStr, sizeof (LogGuidStr), L"%g", RecordDumpData[TempCount].Handle);
                ConvertStrToGuid (LogGuidStr, &PerfData.Guid);
            }
        }
#if !PERFORMANCE_LIBRARY_INCLUDE
        if (gCountDownTimer) {
#if RELATIVE_TIME 
            StartTime = RelativePoint - StartTime;
            EndTime = RelativePoint - EndTime;
#endif
            StartTime = Div64 ( Mul64 ((gStartValue - StartTime), 1000000) , (UINTN)Freq, NULL);
            EndTime = Div64 ( Mul64 ((gStartValue - EndTime), 1000000) , (UINTN)Freq, NULL);
        } else {
#if RELATIVE_TIME 
            if (RelativePoint > StartTime) {
                StartTime = 0;
                EndTime = 0;
            } else {
                StartTime = StartTime - RelativePoint;
                EndTime = EndTime - RelativePoint;
#endif
                StartTime = Div64 ( Mul64 ((StartTime - gStartValue), 1000000) , (UINTN)Freq, NULL);
                EndTime = Div64 ( Mul64 ((EndTime - gStartValue), 1000000) , (UINTN)Freq, NULL);
#if RELATIVE_TIME  
            }
#endif
        }
        /// Save Time
        PerfData.StartTime = StartTime;
        PerfData.EndTime = EndTime;
        PerfData.Duration = (PerfData.EndTime - PerfData.StartTime);
#else
#if RELATIVE_TIME 
        StartTime = StartTime - RelativePoint;
        EndTime = EndTime - RelativePoint;
#endif
        StartTime =   Div64 (Mul64 (StartTime, (UINTN)Freq), 1000000, NULL);
        EndTime =   Div64 (Mul64 (EndTime, (UINTN)Freq), 1000000, NULL);
        /// Save Time
        PerfData.StartTime = Div64 (StartTime, 1000, NULL);
        PerfData.EndTime = Div64 (EndTime, 1000, NULL);
        PerfData.Duration = (PerfData.EndTime - PerfData.StartTime);
#endif
        if (!Strcmp(RecordDumpData[TempCount].Token, "SEC")) {
            PhaseData[0].StartTime = PerfData.StartTime;
            PhaseData[0].EndTime = PerfData.EndTime;
            PhaseData[0].Duration = PerfData.Duration;
#if RELATIVE_TIME 
            PhaseData[0].StartTime = 0;
            PhaseData[0].EndTime = 0;
            PhaseData[0].Duration = 0;
            PerfData.StartTime = 0;
            PerfData.EndTime = 0;
            PerfData.Duration = 0;
#endif
        }
        if (!Strcmp(RecordDumpData[TempCount].Token, "PEI")) {
            PhaseData[1].StartTime = PerfData.StartTime;
            PhaseData[1].EndTime = PerfData.EndTime;
            PhaseData[1].Duration = PerfData.Duration;
        }
        if (!Strcmp(RecordDumpData[TempCount].Token, "DXE")) {
            PhaseData[2].StartTime = PerfData.StartTime;
            PhaseData[2].EndTime = PerfData.EndTime;
            PhaseData[2].Duration = PerfData.Duration;
        }
        if (RecordDumpData[TempCount].PdbFileName[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].PdbFileName);
            
        } else if (RecordDumpData[TempCount].Token[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].Token);
        } else if (RecordDumpData[TempCount].Module[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].Module);
        }
        
        gDataCount ++;
        gBS->CopyMem (gPtr, &PerfData, sizeof (EFI_PERF_DATA));
        gPtr += sizeof (EFI_PERF_DATA);
    }
    
    gBS->CopyMem (TempPtr, &PhaseData, 3 * sizeof (EFI_PHASE_PERF_DATA));
}

/**
 * Set ACPI table header and add table to list.
 *    
 * @param[in]   TableData                                        PMPT table data.
 * @param[in]   AcpiLowMemoryBase                    Record data point.
 *
 */

VOID 
SetPmAcpiTable( 
    IN FPDT_50                 *TableData, 
    IN EFI_PHYSICAL_ADDRESS     AcpiLowMemoryBase
)
{
        EFI_STATUS                  Status;
        EFI_ACPI_SUPPORT_PROTOCOL   *AcpiSupport;
        UINTN                       RsdtTblHandle;
#if SYSTEM_SCOPE_TOOL_FORMAT        
        FPDT_50                     *TempTableData;
        UINT32                      TableSize = sizeof(FPDT_50);
#else
        AMI_FPDT_50                 *TempTableData;
        UINT32                      TableSize = sizeof(AMI_FPDT_50);
#endif
        EFI_ACPI_TABLE_PROTOCOL     *AcpiTableProtocol = NULL;

        /// Get protocol
        Status = gBS->LocateProtocol(&gAcpiSupportGuid, NULL, (VOID**)&AcpiSupport);
        if (EFI_ERROR (Status)) {           
            return ;
        }
        /// Set space to table
        TempTableData = MallocZ(TableSize);

        TempTableData->Header.Length = TableSize;

        TempTableData->Header.Signature = TableData->Header.Signature;
        TempTableData->Header.Revision = TableData->Header.Revision;
        TempTableData->Header.Checksum = 0;

        MemCpy(&(TempTableData->Header.OemId[0]), &(TableData->Header.OemId[0]), 6);     /// "ALASKA"
        MemCpy(&(TempTableData->Header.OemTblId[0]), &(TableData->Header.OemTblId[0]), 8); /// "AMI"

        TempTableData->Header.OemRev = TableData->Header.OemRev;   /// "0x1072009"
        TempTableData->Header.CreatorId = TableData->Header.CreatorId;///"AMI."
        TempTableData->Header.CreatorRev = TableData->Header.CreatorRev; /// 4 

        TempTableData->BasS3Rec.PerfRecType = TableData->BasS3Rec.PerfRecType;
        TempTableData->BasS3Rec.Length = TableData->BasS3Rec.Length;
        TempTableData->BasS3Rec.Revision = TableData->BasS3Rec.Revision;
        TempTableData->BasS3Rec.Pointer = TableData->BasS3Rec.Pointer;

        TempTableData->BasBootRec.PerfRecType = TableData->BasBootRec.PerfRecType;
        TempTableData->BasBootRec.Length = TableData->BasBootRec.Length;
        TempTableData->BasBootRec.Revision = TableData->BasBootRec.Revision;
#if SYSTEM_SCOPE_TOOL_FORMAT        
        TempTableData->BasBootRec.Pointer = AcpiLowMemoryBase;
#else
        TempTableData->BasBootRec.Pointer = TableData->BasBootRec.Pointer;

        TempTableData->AmiBootRec.PerfRecType = AMI_POST_PERFORMANCE_TABLE_POINTER_RECORD;
        TempTableData->AmiBootRec.Length = 16;
        TempTableData->AmiBootRec.Revision = RECORD_VERSION;
        TempTableData->AmiBootRec.Pointer = ((UINT32)AcpiLowMemoryBase);
#endif
        Status = gBS->LocateProtocol(
                 &gEfiAcpiTableProtocolGuid, 
                 NULL, 
                 (VOID**)&AcpiTableProtocol);
        if (EFI_ERROR (Status)) {           
            return ;
        }
        AcpiTableProtocol->InstallAcpiTable(AcpiTableProtocol, 
                                            TempTableData, 
                                            TableSize, 
                                            &RsdtTblHandle);
}

/**
 * Sort PM data by time.
 *    
 * @param[in]   AcpiLowMemoryBase                    Record data point.
 *
 */

VOID 
SortPmData(
    IN UINT32           AcpiLowMemoryBase
)
{
    EFI_PERF_DATA *DataPtr;
    EFI_PERF_DATA *NextDataPtr;
    UINT16 Index;
    UINT16 Pass;
    EFI_PERF_DATA TempData;
    UINT64 StartTime;
    UINT64 NextStartTime;

    gBS->SetMem (&TempData, sizeof (EFI_PERF_DATA), 0);
    /// Sorting data by time
    for (Pass = 1; Pass < gDataCount; Pass++) {
        DataPtr = (EFI_PERF_DATA *) ((UINT32) AcpiLowMemoryBase + 
                                    sizeof(EFI_PERF_S3_INFO) + 
                                    EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof(EFI_PERF_DATA) + 
                                    sizeof (EFI_PERF_INFO) + 
                                    3*sizeof (EFI_PHASE_PERF_DATA) + sizeof(PERF_TAB_HEADER));
        NextDataPtr = DataPtr ++;
        for (Index = 0; Index < gDataCount - 1; Index++) {
            StartTime = DataPtr->StartTime;
            NextStartTime = NextDataPtr->StartTime;
            if (StartTime < NextStartTime) {
                gBS->CopyMem (
                    &TempData,
                    DataPtr,
                    sizeof (EFI_PERF_DATA)
                    );
                gBS->CopyMem (
                    DataPtr,
                    NextDataPtr,
                    sizeof (EFI_PERF_DATA)
                    );
                gBS->CopyMem (
                    NextDataPtr,
                    &TempData,
                    sizeof (EFI_PERF_DATA)
                    );
            }
            DataPtr ++;
            NextDataPtr ++;
        }
    }
    return;
}

/**
 * Save performancedata to ACPI table by System Scope Tool Format style.
 *    
 * @param[in]   RecordDumpData                Performance record data. 
 * @param[in]   TotalNumbers                    Total data numbers.
 * @param[in]   Freq                                    CPU frequence.
 * 
 *@retval EFI_SUCCESS                               Data get and save success.
 */

EFI_STATUS 
GetPerformanceDataSystemScopeToolFormatStyle (
        IN MEASUREMENT_RECORD              *RecordDumpData,
        IN UINTN    TotalNumbers,
    IN UINT64                       Freq
)
{
    EFI_STATUS Status;
    EFI_GUID    ZeroGuid = {0x00000000,0x0000,0x0000,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    UINTN   PerfDataCount;
    BOOLEAN TokenExist = FALSE;
    BOOLEAN ModuleExist = FALSE;
    BOOLEAN GuidExist = FALSE;
    BOOLEAN PdbnameExist = FALSE;     
    BOOLEAN LoadImageToken = FALSE;
    GUID_EVENT_RECORD *GuidEventRecordPtr = NULL;
    STRING_EVENT_RECORD *StringEventRecordPtr = NULL;
    UINT64 StartTime = 0;
    UINT64 EndTime = 0;
    UINT8  *TempPtr;
    UINTN  VariableSize = sizeof(UINT32);
    EFI_FPDT_STRUCTURE    *FpdtVariable = NULL;
    PERF_TAB_HEADER       *BasBootPerTabHeader;
    EFI_PHYSICAL_ADDRESS  FbptAddress = 0x00000000ffffffff;
    UINTN                             PageStoreSize = 0;
    UINTN                             TempCount;
    EFI_PERF_DATA                     PerfData;
    EFI_LOADED_IMAGE_PROTOCOL         *Image;
#if OPTIMIZE_BOOT_FV_COPY
    BOOLEAN                           HobFound = FALSE;
    EFI_HOB_GUID_TYPE                 *HobHead;
    FV_NAME_HOB                       *FvNameHob;
    UINT16                            Count = 0;
    UINT32                            DataNumber;
#endif
#if !PERFORMANCE_LIBRARY_INCLUDE
    UINT64                            TempStartTime;
    UINT64                            TempEndTime;
#endif
    
    
    /// Get performance data count    
    PerfDataCount = TotalNumbers;

    /// Get FBPT address from FPDT variable
    Status = gRT->GetVariable( 
                    EFI_FPDT_VARIABLE,
                    &gAmiGlobalVariableGuid,
                    NULL,
                    &VariableSize,
                    &FpdtVariable
                    );
    if (EFI_ERROR (Status)) {  
        return Status;
    }
    BasBootPerTabHeader = (PERF_TAB_HEADER*)(FpdtVariable->BasBootPointer);

    PageStoreSize = (sizeof(PERF_TAB_HEADER) + 
                     sizeof(BASIC_BOOT_PERF_REC) + 
                     2 * (PerfDataCount + 10) * sizeof(STRING_EVENT_RECORD));
    /// Set memory to save data
    Status = gBS->AllocatePages (
                    AllocateMaxAddress,
                    EfiRuntimeServicesData,
                    EFI_SIZE_TO_PAGES (PageStoreSize),
                    &FbptAddress
                    );
    if (EFI_ERROR(Status)) {
        gBS->FreePool((VOID *)FbptAddress);
        return Status;
    }
    BasBootPerTabHeader->Length = (UINT32)PageStoreSize;
    gBS->CopyMem ((UINTN *) (UINTN) FbptAddress, BasBootPerTabHeader, sizeof(PERF_TAB_HEADER) + sizeof(BASIC_BOOT_PERF_REC));
    TempPtr = (UINT8 *) ((UINTN) FbptAddress + sizeof(PERF_TAB_HEADER) + sizeof(BASIC_BOOT_PERF_REC));
    gBS->SetMem (TempPtr, 2 * (PerfDataCount + 10) * sizeof(STRING_EVENT_RECORD), 0);

#if OPTIMIZE_BOOT_FV_COPY
    /// Get hob that save pei module name.
    Status = GetFvNameHOB(&HobHead);
    if (!EFI_ERROR(Status)) {
        HobFound = TRUE;
        FvNameHob = (FV_NAME_HOB *)(HobHead+1);
    }

    DataNumber = (UINT32) (Div64 ( (HobHead)->Header.HobLength, (EFI_PERF_PDBFILENAME_LENGTH + sizeof(EFI_GUID)), NULL));
#endif
    
    /// list the data    
    for (TempCount = 0; 
        TempCount < PerfDataCount; 
        TempCount++, 
        TokenExist = FALSE, 
        ModuleExist = FALSE, 
        GuidExist = FALSE, 
        PdbnameExist = FALSE, 
        LoadImageToken = FALSE ) {
        /// Skip Support data.
        if (!Strcmp(RecordDumpData[TempCount].Token, "DB:Support:")) {
            continue;
        }

        gBS->SetMem (&PerfData, sizeof (EFI_PERF_DATA), 0);
        
        StartTime = RecordDumpData[TempCount].StartTimeStamp;
        EndTime = RecordDumpData[TempCount].EndTimeStamp;

        if (!Strcmp(RecordDumpData[TempCount].Token, "PEIM")) {
            PerfData.Guid = ((EFI_FFS_FILE_HEADER*)(RecordDumpData[TempCount].Handle))->Name;
#if !OPTIMIZE_BOOT_FV_COPY
            Status = GetNameFromUi(&(RecordDumpData[TempCount].PdbFileName[0]), &PerfData.Guid);
#else
            // In this part, we use hob data to get Fv name.
            if (HobFound == TRUE) { /// Hub found, check GUID and find Fv name.
                for (Count = 0; Count < DataNumber; Count++) {
                    if (!guidcmp(&(PerfData.Guid),&((FvNameHob[Count]).FvGuid))) { /// GUID match
                        Strcpy (RecordDumpData[TempCount].PdbFileName, (FvNameHob[Count]).NameString);
                    }
                }
            }
#endif
        } else {
            Status = gBS->HandleProtocol (
                          RecordDumpData[TempCount].Handle,
                          &gEfiLoadedImageProtocolGuid, 
                          (VOID**)&Image
                          );
            if (!EFI_ERROR(Status)
                && Image->FilePath->Type ==  MEDIA_DEVICE_PATH
                && Image->FilePath->SubType == MEDIA_FV_FILEPATH_DP) {
                
                gBS->CopyMem (&(PerfData.Guid), &( ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*) Image->FilePath)->FvFileName), sizeof (EFI_GUID)); 
                Status = GetNameFromUi(&(RecordDumpData[TempCount].PdbFileName[0]), &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*) Image->FilePath)->FvFileName);
          }
        }

#if !PERFORMANCE_LIBRARY_INCLUDE
        /// Skip non complete record.
        if (gCountDownTimer) {
            if (StartTime < EndTime) {
                continue;
            }
        } else {
            if (StartTime > EndTime) {
                continue;
            }
        }

        ///
        /// According to ACPI 5.1 spec, All timer values are expressed in 1 nanosecond increments filled into FPDT,
        /// and the value gotten from GetGauge() function is the number of TSC counts per second, so the unit of the time 
        /// must be transferred from a second to a namosecond, and the following is divided two calculations prevented the 
        /// value overflow.
        ///
        if (gCountDownTimer) {
            TempStartTime = Div64 ( Mul64 ((gStartValue - StartTime), (1000 * 1000)) , (UINTN)Freq, NULL);
            if (TempStartTime == 0) {
                TempStartTime = Div64 ( Mul64 ((gStartValue - StartTime), (1000 * 1000 * 1000)) , (UINTN)Freq, NULL);
            } else {
                TempStartTime = Mul64 (TempStartTime, 1000);
            }
          
            TempEndTime = Div64 ( Mul64 ((gStartValue - EndTime), (1000 * 1000)) , (UINTN)Freq, NULL);
            if (TempEndTime == 0) {
                TempEndTime = Div64 ( Mul64 ((gStartValue - EndTime), (1000 * 1000 * 1000)) , (UINTN)Freq, NULL);
            } else {
                TempEndTime = Mul64 (TempEndTime, 1000);
            }
        } else {
            TempStartTime = Div64 ( Mul64 ((StartTime - gStartValue), (1000 * 1000)) , (UINTN)Freq, NULL);
            if (TempStartTime == 0) {
                TempStartTime = Div64 ( Mul64 ((StartTime - gStartValue), (1000 * 1000 * 1000)) , (UINTN)Freq, NULL);
            } else {
                TempStartTime = Mul64 (TempStartTime, 1000);
            }

            TempEndTime = Div64 ( Mul64 ((EndTime - gStartValue), (1000 * 1000)) , (UINTN)Freq, NULL);
            if (TempEndTime == 0) {
                TempEndTime = Div64 ( Mul64 ((EndTime - gStartValue), (1000 * 1000 * 1000)) , (UINTN)Freq, NULL);
            } else {
                TempEndTime = Mul64 (TempEndTime, 1000);
            }
        }
        /// Save Time
        PerfData.StartTime = TempStartTime;
        PerfData.EndTime = TempEndTime;
        PerfData.Duration = (PerfData.EndTime - PerfData.StartTime);
#else
        StartTime =   Div64 (Mul64 (StartTime, (UINTN)Freq), 1000000, NULL);
        EndTime =   Div64 (Mul64 (EndTime, (UINTN)Freq), 1000000, NULL);
        /// Save Time
        PerfData.StartTime = StartTime;
        PerfData.EndTime = EndTime;
        PerfData.Duration = (PerfData.EndTime - PerfData.StartTime);
#endif
        if (RecordDumpData[TempCount].PdbFileName[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].PdbFileName);
            PdbnameExist = TRUE;  
        } else if (RecordDumpData[TempCount].Token[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].Token);
            TokenExist = TRUE;
        } else if (RecordDumpData[TempCount].Module[0] != 0) {
            Strcpy(PerfData.Token, RecordDumpData[TempCount].Module);
            ModuleExist = TRUE;
        }

        if (guidcmp(&PerfData.Guid, &ZeroGuid)) {
            GuidExist = TRUE;
        }
        
        if (TokenExist && !Strcmp(RecordDumpData[TempCount].Token, "LoadImage:")) {
            LoadImageToken = TRUE;
        }

        /// Save Token
        if (GuidExist) {
            /// Start record     
            GuidEventRecordPtr = (GUID_EVENT_RECORD*)TempPtr;   
            GuidEventRecordPtr->GuidEventRecType = EVENT_RECORD_WITH_GUID;
            GuidEventRecordPtr->Length = 34;
            GuidEventRecordPtr->Revision = 1;

            if (LoadImageToken) {
                GuidEventRecordPtr->ProgressId = PROGRESS_ID_START; /// Start
            } else {
                GuidEventRecordPtr->ProgressId = PROGRESS_ID_LOAD_IMAGE_START; /// LoadImage Start
            }

            GuidEventRecordPtr->ProcessorId = 0;
            GuidEventRecordPtr->Timestamp = PerfData.StartTime;
            gBS->CopyMem (&(GuidEventRecordPtr->Guid), &PerfData.Guid, sizeof (EFI_GUID)); 
            TempPtr += sizeof (GUID_EVENT_RECORD);
          /// End record
            GuidEventRecordPtr = (GUID_EVENT_RECORD*)TempPtr;   
            GuidEventRecordPtr->GuidEventRecType = EVENT_RECORD_WITH_GUID;
            GuidEventRecordPtr->Length = GUID_EVENT_REC_LENGTH;
            GuidEventRecordPtr->Revision = 1;

            if (LoadImageToken) {
                GuidEventRecordPtr->ProgressId = PROGRESS_ID_END; /// End
            } else {
                GuidEventRecordPtr->ProgressId = PROGRESS_ID_LOAD_IMAGE_END; /// LoadImage End
            }

            GuidEventRecordPtr->ProcessorId = 0;
            GuidEventRecordPtr->Timestamp = PerfData.EndTime;
            gBS->CopyMem (&(GuidEventRecordPtr->Guid), &PerfData.Guid, sizeof (EFI_GUID)); 
            TempPtr += sizeof (GUID_EVENT_RECORD);
        } else if (TokenExist || ModuleExist || PdbnameExist) {
            /// Start record     
            StringEventRecordPtr = (STRING_EVENT_RECORD*)TempPtr;   
            StringEventRecordPtr->StringEventRecType = EVENT_RECORD_WITH_STRING;
            StringEventRecordPtr->Length = STRING_EVENT_REC_LENGTH;
            StringEventRecordPtr->Revision = 1;

            if (LoadImageToken) {
                StringEventRecordPtr->ProgressId = PROGRESS_ID_START; /// Start
            } else {
              StringEventRecordPtr->ProgressId = PROGRESS_ID_LOAD_IMAGE_START; /// LoadImage Start
            }

            StringEventRecordPtr->ProcessorId = 0;
            StringEventRecordPtr->Timestamp = PerfData.StartTime;

            if (PdbnameExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].PdbFileName);
            } else if (TokenExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].Token);
            } else if (ModuleExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].Module);
            }

            TempPtr += sizeof (STRING_EVENT_RECORD);
            /// End record
            StringEventRecordPtr = (STRING_EVENT_RECORD*)TempPtr;   
            StringEventRecordPtr->StringEventRecType = EVENT_RECORD_WITH_STRING;
            StringEventRecordPtr->Length = STRING_EVENT_REC_LENGTH;
            StringEventRecordPtr->Revision = 1;

            if (LoadImageToken) {
                StringEventRecordPtr->ProgressId = PROGRESS_ID_END; /// End
            } else {
                StringEventRecordPtr->ProgressId = PROGRESS_ID_LOAD_IMAGE_END; /// LoadImage End
            }

            StringEventRecordPtr->ProcessorId = 0;
            StringEventRecordPtr->Timestamp = PerfData.EndTime;

            if (PdbnameExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].PdbFileName);
            } else if (TokenExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].Token);
            } else if (ModuleExist) {
                Strcpy (StringEventRecordPtr->NameString, RecordDumpData[TempCount].Module);
            }
          
            TempPtr += sizeof (STRING_EVENT_RECORD);
        }
    } /// End for loop

    gBS->FreePool(RecordDumpData);

    /// Change data address
    FpdtVariable->BasBootPointer = FbptAddress;
    gPtr = (UINT8 *) ((UINTN) FbptAddress);

    return EFI_SUCCESS;

}

/**
 * Use GUID to get firmware volume and serch user interface section to get name.
 *    
 * @param[in]        PdbFileName                Record's name data. 
 * @param[in]        Guid                       Record's GUID.
 * 
 *@retval EFI_SUCCESS                           Get record name success.
 */

EFI_STATUS 
GetNameFromUi (
    IN OUT UINT8  *PdbFileName,
    IN EFI_GUID *Guid
)
{
    EFI_FIRMWARE_VOLUME_PROTOCOL    *Fv;

    EFI_STATUS   Status;
    UINTN        NumHandles;
    EFI_HANDLE   *HandleBuffer;
    UINTN        Counter;
    UINT8        *Buffer;
    UINTN        BufferSize = EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR16);
    UINT32       *AuthenticationStatus;
    CHAR8        *Dest;
    CHAR16       *Src;
    CHAR8        TempToken[EFI_PERF_PDBFILENAME_LENGTH] = {0};

    
    Status = gBS->LocateHandleBuffer (ByProtocol, &guidFV, NULL, &NumHandles, &HandleBuffer);
    if (EFI_ERROR(Status)) return Status;
    Buffer = MallocZ (BufferSize);
    AuthenticationStatus = MallocZ (sizeof(UINT32));
    for (Counter = 0; Counter < NumHandles; ++Counter)
    {
        gBS->HandleProtocol (HandleBuffer[Counter], &guidFV, (VOID**)&Fv);
        Status = Fv->ReadSection (
            Fv, Guid,
            EFI_SECTION_USER_INTERFACE, 0,
            &Buffer, &BufferSize,
            AuthenticationStatus
        );
        if (!EFI_ERROR(Status)) break;
    }

    if (EFI_ERROR(Status)) {
        return Status;
    }
    /// convert CHAR16 string to CHAR8 string
    Src = (CHAR16*)Buffer;
    Dest = (UINT8 *)TempToken;
    while (*Src) *Dest++ = (UINT8) (*Src++);
    *Dest = 0;

    Strcpy (PdbFileName, TempToken);
    
    gBS->FreePool (HandleBuffer);
    return Status;

}

/**
 * Set memory buffer data to 0.
 *    
 * @param[in]         Buffer                Data buffer. 
 * @param[in]         Size                  Data size.
 * 
 */

VOID
ZeroMem(
    IN OUT VOID  *Buffer,
    IN UINTN      Size
)
{
    UINT8 *Ptr;
    Ptr = Buffer;
    while (Size--)
    {
        *(Ptr++) = 0;
    }

}

/**
 * Get hob data.
 *    
 * @param[in]   HobHead     Hob header
 *
 */

EFI_STATUS 
GetFvNameHOB (
  IN OUT EFI_HOB_GUID_TYPE **HobHead    
)
{
    EFI_STATUS  Status;
    VOID        *pHobList = NULL;
    EFI_GUID    guidHob = HOB_LIST_GUID;    
    EFI_GUID    FvNameHobGuid = AMI_FV_NAME_HOB_GUID;
    
    pHobList = GetEfiConfigurationTable(gST, &guidHob);
    if (!pHobList) return EFI_NOT_READY;

    *HobHead = (EFI_HOB_GUID_TYPE*)pHobList;

    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, HobHead)))
    {
        if (guidcmp(&(*HobHead)->Name, &FvNameHobGuid) == 0)
            break;
    }

    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;
    
    return  EFI_SUCCESS;
}

/**
 *  Get the PDB file name.
 *    
 * @param[in]                PdbFileName                The long PDB file name.
 * @param[out]               UnicodeBuffer              The output string to be logged by performance logger.
 * 
 */

VOID
GetShortPdbFileName (
  IN  CHAR8     *PdbFileName,
  OUT CHAR16    *UnicodeBuffer
  )
{
  UINTN IndexA;     /// Current work location within an ASCII string.
  UINTN IndexU;     /// Current work location within a Unicode string.
  UINTN StartIndex;
  UINTN EndIndex;

  ZeroMem (UnicodeBuffer, DXE_PERFORMANCE_STRING_LENGTH * sizeof (CHAR16));

  if (PdbFileName == NULL) {
    StrCpy (UnicodeBuffer, L" ");
  } else {
    StartIndex = 0;
    for (EndIndex = 0; PdbFileName[EndIndex] != 0; EndIndex++);
    
    for (IndexA = 0; PdbFileName[IndexA] != 0; IndexA++) {
      if (PdbFileName[IndexA] == '\\') {
        StartIndex = IndexA + 1;
      }

      if (PdbFileName[IndexA] == '.') {
        EndIndex = IndexA;
      }
    }

    IndexU = 0;
    for (IndexA = StartIndex; IndexA < EndIndex; IndexA++) {
      UnicodeBuffer[IndexU] = (CHAR16) PdbFileName[IndexA];
      IndexU++;
      if (IndexU >= DXE_PERFORMANCE_STRING_LENGTH) {
        UnicodeBuffer[DXE_PERFORMANCE_STRING_LENGTH] = 0;
        break;
      }
    }
  }
}

/**
 * Use handle to get record name.
 *
 * @param[in]               Handle             Record's handle.
 * @param[in]               GaugeString        Record's name data. 
 * @param[in]               LogGuid            Record's GUID.
 *
 *@retval EFI_SUCCESS                         Get record name success.
 */

EFI_STATUS
GetNameFromHandle (
  IN EFI_HANDLE     Handle,
  IN OUT CHAR16*    GaugeString,
  IN OUT EFI_GUID** LogGuid
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding;
  EFI_STRING                  StringPtr;
  EFI_DEVICE_PATH_PROTOCOL    *LoadedImageDevicePath;
  EFI_GUID                    *NameGuid;
  CHAR16                      *NameString;
  UINTN                       StringSize;
  CHAR8                       *PlatformLanguage;
  CHAR8                       *PdbFileName;
  EFI_COMPONENT_NAME2_PROTOCOL      *ComponentName2;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL  *DevicePathToText;

  ///
  /// Method 1: Get the name string from image PDB
  ///
  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **) &Image
                  );

  if (EFI_ERROR (Status)) {
    Status =gBS->OpenProtocol (
                    Handle,
                    &gEfiDriverBindingProtocolGuid,
                    (VOID **) &DriverBinding,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );

    if (!EFI_ERROR (Status)) {
      Status = gBS->HandleProtocol (
                      DriverBinding->ImageHandle,
                      &gEfiLoadedImageProtocolGuid,
                      (VOID **) &Image
                      );
    }
  }

  if (!EFI_ERROR (Status)) {
{
    PdbFileName = PeCoffLoaderGetPdbPointer (Image->ImageBase);
    if (PdbFileName != NULL) {
      GetShortPdbFileName (PdbFileName, GaugeString);
      return EFI_SUCCESS;
    }
}
  }

  ///
  /// Method 2: Get the name string from ComponentName2 protocol
  ///
  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID **) &ComponentName2
                  );

  if (!EFI_ERROR (Status)) {
    ///
    /// Get the current platform language setting
    ///
    GetEfiGlobalVariable2 (L"PlatformLang", (VOID**)&PlatformLanguage, NULL);
    Status = ComponentName2->GetDriverName (
                               ComponentName2,
                               PlatformLanguage != NULL ? PlatformLanguage : "en-US",
                               &StringPtr
                               );
    if (!EFI_ERROR (Status)) {
      StrnCpy (GaugeString, StringPtr, EFI_PERF_PDBFILENAME_LENGTH);
      GaugeString[EFI_PERF_PDBFILENAME_LENGTH] = 0;
      return EFI_SUCCESS;
    }
  }

  Status =gBS->HandleProtocol (
                  Handle,
                  &gEfiLoadedImageDevicePathProtocolGuid,
                  (VOID **) &LoadedImageDevicePath
                  );
  if (!EFI_ERROR (Status) && (LoadedImageDevicePath != NULL)) {
{
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    DevicePath = LoadedImageDevicePath;

    ///
    /// Try to get image GUID from LoadedImageDevicePath protocol
    ///
    NameGuid = NULL;
    while (!IsDevicePathEndType (DevicePath)) {
      NameGuid = EfiGetNameGuidFromFwVolDevicePathNode ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *) DevicePath);
      if (NameGuid != NULL) {
        break;
      }
      DevicePath = NextDevicePathNode (DevicePath);
    }
}
    if (NameGuid != NULL) {
      ///
      /// Try to get the image's FFS UI section by image GUID
      ///

      NameString = NULL;
      StringSize = 0;
      Status = GetSectionFromAnyFv (
                NameGuid,
                EFI_SECTION_USER_INTERFACE,
                0,
                (VOID **) &NameString,
                &StringSize
                );
      *LogGuid = NameGuid;
      
      if (!EFI_ERROR (Status)) {
        ///
        /// Method 3. Get the name string from FFS UI section
        ///
        StrnCpy (GaugeString, NameString, EFI_PERF_PDBFILENAME_LENGTH);
        GaugeString[EFI_PERF_PDBFILENAME_LENGTH] = 0;
        gBS->FreePool (NameString);
      } else {
        ///
        /// Method 4: Get the name string from image GUID
        ///
        UnicodeSPrint (GaugeString, EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR16), L"%g", NameGuid);
      }
      return EFI_SUCCESS;
    } else {
      ///
      /// Method 5: Get the name string from image DevicePath
      ///
      Status = gBS->LocateProtocol (
                      &gEfiDevicePathToTextProtocolGuid,
                      NULL,
                      (VOID **) &DevicePathToText
                      );
      if (!EFI_ERROR (Status)) {
        NameString = DevicePathToText->ConvertDevicePathToText (LoadedImageDevicePath, TRUE, FALSE);
        if (NameString != NULL) {
          StrnCpy (GaugeString, NameString, EFI_PERF_PDBFILENAME_LENGTH);
          GaugeString[EFI_PERF_PDBFILENAME_LENGTH] = 0;
          gBS->FreePool (NameString);
          return EFI_SUCCESS;
        }
      }
    }
  }

  return EFI_NOT_FOUND;
}

/**
 * Get and save Smm performance record.
 *
 * @param[in]               Freq                CPU frequence.
 *
 */

VOID 
EFIAPI 
GetPerfSmmData(
    IN UINT64       Freq
)
{
    EFI_STATUS  Status;
    EFI_SMM_COMMUNICATE_HEADER      *SmmCommunicateHeader;
    EFI_SMM_COMMUNICATION_PROTOCOL  *gSmmCommunication = NULL;
    PM_SMM_DATA_STRUCTURE           *SmmData;
    EFI_GUID    GetPerfSmmDataGuid = PM_GET_SMM_DATA_GUID;
    MEASUREMENT_RECORD              *SmmRecordBuffer = NULL;
    UINTN                           Counter;
    EFI_PERF_DATA                   PerfData;
    UINT64                          StartTime = 0;
    UINT64                          EndTime = 0;
    
#if PERFORMANCE_LIBRARY_INCLUDE 
    BOOLEAN                         CountDownTimer = FALSE;
    UINT64                          LocalFreq;
#endif
    
    Status = gBS->AllocatePool( EfiBootServicesData,
                                 sizeof(PM_SMM_DATA_STRUCTURE),
                                 (VOID**)&SmmData );
    if ( EFI_ERROR( Status )) {     
        return;
    } 
    gBS->SetMem(SmmData, sizeof (PM_SMM_DATA_STRUCTURE), 0);
    
    SmmData->Signature = '$PM';
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gPerformanceMeasurementCommunicateBuffer;
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &GetPerfSmmDataGuid, sizeof( EFI_GUID ) );
    
    SmmCommunicateHeader->MessageLength  = sizeof(PM_SMM_DATA_STRUCTURE);
    gBS->CopyMem( &SmmCommunicateHeader->Data, SmmData, sizeof(PM_SMM_DATA_STRUCTURE) );
    
    Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
    if (EFI_ERROR(Status)) {
        return;  
    }

    Status = gSmmCommunication->Communicate (gSmmCommunication, 
                                             gPerformanceMeasurementCommunicateBuffer, 
                                             &gPerformanceMeasurementCommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        return;  
    }
    /// Smm record.
    SmmData = (PM_SMM_DATA_STRUCTURE*)(SmmCommunicateHeader->Data);
    SmmRecordBuffer = (MEASUREMENT_RECORD*)(SmmData->BufferAddress);
     
#if PERFORMANCE_LIBRARY_INCLUDE     
    /// Update Freq and gStartValue.
    LocalFreq = GetPerformanceCounterProperties(&gStartValue, &EndTime);
    CountDownTimer = gStartValue > EndTime;

    if (LocalFreq == 0) {
        return;
    }
#endif     
    for (Counter = 0; Counter < SmmData->RecordNumbers; Counter++) {
        gBS->SetMem (&PerfData, sizeof (EFI_PERF_DATA), 0);
         
        StartTime = SmmRecordBuffer[Counter].StartTimeStamp;
        EndTime = SmmRecordBuffer[Counter].EndTimeStamp;
#if !PERFORMANCE_LIBRARY_INCLUDE
        if (gCountDownTimer) {
#if RELATIVE_TIME 
            StartTime = gRelativePoint - StartTime;
            EndTime = gRelativePoint - EndTime;
#endif
            StartTime = Div64 ( Mul64 ((gStartValue - StartTime), 1000000) , (UINTN)Freq, NULL);
            EndTime = Div64 ( Mul64 ((gStartValue - EndTime), 1000000) , (UINTN)Freq, NULL);
        } else {
#if RELATIVE_TIME 
            if (gRelativePoint > StartTime) {
                StartTime = 0;
                EndTime = 0;
            } else {
                StartTime = StartTime - gRelativePoint;
                EndTime = EndTime - gRelativePoint;
#endif
            StartTime = Div64 ( Mul64 ((StartTime - gStartValue), 1000000) , (UINTN)Freq, NULL);
            EndTime = Div64 ( Mul64 ((EndTime - gStartValue), 1000000) , (UINTN)Freq, NULL);
#if RELATIVE_TIME  
            }
#endif
        }
#else
#if RELATIVE_TIME 
        StartTime = StartTime - gRelativePoint;
        EndTime = EndTime - gRelativePoint;
#endif
        if (CountDownTimer) {
            StartTime = Div64 ( Mul64 ((gStartValue - StartTime), 1000000) , (UINTN)LocalFreq, NULL);
            EndTime = Div64 ( Mul64 ((gStartValue - EndTime), 1000000) , (UINTN)LocalFreq, NULL);
        } else {
            StartTime = Div64 ( Mul64 ((StartTime - gStartValue), 1000000) , (UINTN)LocalFreq, NULL);
            EndTime = Div64 ( Mul64 ((EndTime - gStartValue), 1000000) , (UINTN)LocalFreq, NULL);
        }
#endif         
        /// Save Time
        PerfData.StartTime = StartTime;
        PerfData.EndTime = EndTime;
        PerfData.Duration = (PerfData.EndTime - PerfData.StartTime);
        
        if (SmmRecordBuffer[Counter].PdbFileName[0] != 0) {
            Strcpy(PerfData.Token, SmmRecordBuffer[Counter].PdbFileName);
        } else if (SmmRecordBuffer[Counter].Token[0] != 0) {
            Strcpy(PerfData.Token, SmmRecordBuffer[Counter].Token);
        } else if (SmmRecordBuffer[Counter].Module[0] != 0) {
            Strcpy(PerfData.Token, SmmRecordBuffer[Counter].Module);
        }
         
        gBS->CopyMem (&(PerfData.Guid), &(SmmRecordBuffer[Counter].GuidName), sizeof (EFI_GUID));
        gBS->CopyMem (gPtr, &PerfData, sizeof (EFI_PERF_DATA));
        gPtr += sizeof (EFI_PERF_DATA);
         
        gDataCount ++;
    }
}

/**
  Converts a list of string to a specified buffer.

  @param Buf[out]             The output buffer that contains the string.
  @param BufferLength[in]     The length of the buffer
  @param Str[in]              The input string that contains the hex number

  @retval EFI_SUCCESS    The string was successfully converted to the buffer.

**/
EFI_STATUS
ConvertStrToBuf (
    OUT     UINT8       *Buf,
    IN      UINTN       BufferLength,
    IN      CHAR16      *Str
    )
{
    UINTN       Index;
    UINTN       StrLength;
    UINT8       Digit;
    UINT8       Byte;

    Digit = 0;

    //
    // Two hex char make up one byte
    //
    StrLength = BufferLength * sizeof (CHAR16);

    for(Index = 0; Index < StrLength; Index++, Str++) {

        if ((*Str >= L'a') && (*Str <= L'f')) {
            Digit = (UINT8) (*Str - L'a' + 0x0A);
        } else if ((*Str >= L'A') && (*Str <= L'F')) {
            Digit = (UINT8) (*Str - L'A' + 0x0A);
        } else if ((*Str >= L'0') && (*Str <= L'9')) {
            Digit = (UINT8) (*Str - L'0');
        } else {
            return EFI_INVALID_PARAMETER;
        }

        //
        // For odd characters, write the upper nibble for each buffer byte,
        // and for even characters, the lower nibble.
        //
        if ((Index & 1) == 0) {
            Byte = (UINT8) (Digit << 4);
        } else {
            Byte = Buf[Index / 2];
            Byte &= 0xF0;
            Byte = (UINT8) (Byte | Digit);
        }

        Buf[Index / 2] = Byte;
    }

    return EFI_SUCCESS;
}

/**
  Converts a string to GUID value.
  Guid Format is xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx

  @param Str[in]               The registry format GUID string that contains the GUID value.
  @param Guid[out]             A pointer to the converted GUID value.

  @retval EFI_SUCCESS     The GUID string was successfully converted to the GUID value.
  @retval EFI_UNSUPPORTED The input string is not in registry format.
  @return others          Some error occurred when converting part of GUID value.

**/
EFI_STATUS
ConvertStrToGuid (
    IN      CHAR16      *Str,
    OUT     EFI_GUID    *Guid
    )
{
    //
    // Get the first UINT32 data
    //
    Guid->Data1 = (UINT32) StrHexToUint64  (Str);
    while (!IS_HYPHEN (*Str) && !IS_NULL (*Str)) {
        Str ++;
    }

    if (IS_HYPHEN (*Str)) {
        Str++;
    } else {
        return EFI_UNSUPPORTED;
    }

    //
    // Get the second UINT16 data
    //
    Guid->Data2 = (UINT16) StrHexToUint64  (Str);
    while (!IS_HYPHEN (*Str) && !IS_NULL (*Str)) {
        Str ++;
    }

    if (IS_HYPHEN (*Str)) {
        Str++;
    } else {
        return EFI_UNSUPPORTED;
    }

    //
    // Get the third UINT16 data
    //
    Guid->Data3 = (UINT16) StrHexToUint64  (Str);
    while (!IS_HYPHEN (*Str) && !IS_NULL (*Str)) {
        Str ++;
    }

    if (IS_HYPHEN (*Str)) {
        Str++;
    } else {
        return EFI_UNSUPPORTED;
    }

    //
    // Get the following 8 bytes data
    //
    ConvertStrToBuf (&Guid->Data4[0], 2, Str);
    //
    // Skip 2 byte hex chars
    //
    Str += 2 * 2;

    if (IS_HYPHEN (*Str)) {
        Str++;
    } else {
        return EFI_UNSUPPORTED;
    }
    ConvertStrToBuf (&Guid->Data4[2], 6, Str);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
