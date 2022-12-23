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

/** @file PerformanceMeasurementPei.c
 *  Get S3 performance data and save to Table.
 */

#include <AmiPeiLib.h>
#include <Pei.h>
#include <AmiHobs.h>
#include <Protocol/Performance.h>
#include <Token.h>
#include "PerformanceMeasurement.h"
#include <Ffs.h>
#include <Guid/Performance.h>

/// Globol GUID
EFI_GUID gEfiPeiEndOfPeiPhasePpiGuid = EFI_PEI_END_OF_PEI_PHASE_PPI_GUID;
EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID gEfiPeiPerformanceHobGuid = EFI_PEI_PERFORMANCE_HOB_GUID;
EFI_GUID gEfiPeiFvNameHobGuid = AMI_FV_NAME_HOB_GUID;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gAmiGlobalVariableGuid;

EFI_STATUS 
EFIAPI 
PmPeiGetName (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
);

static EFI_PEI_NOTIFY_DESCRIPTOR PmEndOfPeiNotify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPeiEndOfPeiPhasePpiGuid,
        PmPeiGetName
    }
};

/**
 * Get performance record hub, found record Fv name by GUID
 *    and save to hub.
 *    
 * @param[in]   PeiServices                The pointer to the PEI Services Table.
 * @param[in]   NotifyDescriptor    The pointer to the notification service.
 * @param[in]   NullPpi                    Dummy point.
 *
 * @retval EFI_SUCCESS                Data get success.
 * @retval EFI_NOT_FOUND            Can't find data.    
 */

EFI_STATUS
EFIAPI 
PmPeiGetName (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *NullPpi
)
{
    EFI_STATUS                      Status;   
    UINT32                          Counter;
    UINT8                           Index = 0;
    PEI_PERFORMANCE_LOG_HEADER      *LogHob;
    PEI_PERFORMANCE_LOG_ENTRY       *LogEntry;
    EFI_PEI_HOB_POINTERS            Hob;
    EFI_GUID                        *Guid = NULL;
    UINT8                           *TempFfsData = NULL;
    UINT8                           *TempFfsPtr = NULL;
    EFI_USER_INTERFACE_SECTION      *TempFfsName = NULL;
    UINTN                           FfsLength;                                                        
    EFI_FIRMWARE_VOLUME_HEADER      *pFv;
    EFI_FFS_FILE_HEADER             *pFile;
    UINTN                           Instance = 0;
    FV_NAME_HOB                     *FvNameHob;
    EFI_HOB_GUID_TYPE               *HobHead;
    UINTN                           FileNameLength;
    EFI_COMMON_SECTION_HEADER       *TempCeHeader;
    BOOLEAN                         UiFind = FALSE;
    UINTN                           TempFvLength = 0;
    UINTN                           TempTotalFvLength = 0;
    UINTN                           SearchCount;

    (*PeiServices)->GetHobList (PeiServices, &Hob.Raw);
    Status = FindNextHobByGuid(&gPerformanceProtocolGuid, &Hob.Raw);

    if (EFI_ERROR (Status)) return Status;

    LogHob = (PEI_PERFORMANCE_LOG_HEADER *) (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + sizeof (EFI_GUID));
    LogEntry   = (PEI_PERFORMANCE_LOG_ENTRY *) (LogHob + 1);
    
    Status = (*PeiServices)->CreateHob (PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        sizeof(EFI_HOB_GUID_TYPE) +  (LogHob->NumberOfEntries) * sizeof(FV_NAME_HOB),
                                        &HobHead);

    if (EFI_ERROR(Status)) return Status;

    HobHead->Name = gEfiPeiFvNameHobGuid;
    FvNameHob = (FV_NAME_HOB *)(HobHead + 1);

    for( Counter = 0;
        ((Counter < LogHob->NumberOfEntries));
        Counter++)
        {
        if (LogEntry[Counter].EndTimeStamp == 0) {
            continue;
           }

        if (Strcmp(LogEntry[Counter].Token, "PEIM")) {
            continue;
        }
        Guid = &((EFI_FFS_FILE_HEADER*)(LogEntry[Counter].Handle))->Name;
        if (((INT32 *)Guid)[0] != 0) { /// Save GUID And name
            Instance = 0;
            UiFind = FALSE;
            TempTotalFvLength = 0;
            
            while (TRUE) {
                Status = (*PeiServices)->FfsFindNextVolume (PeiServices, Instance, &pFv);
                if (EFI_ERROR (Status)) {
                    break;
                }
                pFile = NULL;
                ///
                /// Start new search in volume
                ///
                while (TRUE) {
                      Status = (*(PeiServices))->FfsFindNextFile (PeiServices, EFI_FV_FILETYPE_PEIM, pFv, &pFile);
                      if (Status == EFI_NOT_FOUND) {
                        break;
                      }
                      if (!MemCmp(&(pFile->Name),Guid,sizeof(EFI_GUID))) {    /// FV Found
                        FfsLength = pFile->Size[0] + (pFile->Size[1] << 8) + (pFile->Size[2] << 16);
                        pFile ++;
                        TempFfsData = (UINT8*)pFile;
                        TempTotalFvLength = sizeof(EFI_FFS_FILE_HEADER);
                        /// Parsing Fv file to find User_Interface
                        SearchCount = 0;
                        while (TRUE) {
                            TempCeHeader = (EFI_COMMON_SECTION_HEADER*)TempFfsData;
                            if (TempCeHeader->Type == EFI_SECTION_USER_INTERFACE) {
                                UiFind = TRUE;
                                break;
                            }

                            TempFvLength = TempCeHeader->Size[0] + 
                                           (TempCeHeader->Size[1] << 8) + 
                                           (TempCeHeader->Size[2] << 16);
                            
                            TempFvLength = TempFvLength + 
                                           (TempFvLength % 4);
                            
                            TempTotalFvLength += TempFvLength;
                            if (TempTotalFvLength > FfsLength || SearchCount > 0x20) {
                                /// Over file length, found fail.
                                break;
                            }
                            TempFfsData = (UINT8*)(TempFfsData + TempFvLength);
                            SearchCount ++;
                        }
                        if (UiFind) {
                            TempFfsName = (EFI_USER_INTERFACE_SECTION*)TempFfsData;
                            TempFfsPtr = (UINT8*)(TempFfsName->FileNameString);
                            FileNameLength = TempFfsName->CommonHeader.Size[0] + 
                                            (TempFfsName->CommonHeader.Size[1] << 8) + 
                                            (TempFfsName->CommonHeader.Size[2] << 16);
                            if (((FileNameLength - 4) / 2) > 40) { /// over length, skip this data.
                                UiFind = FALSE;
                            } else {
                                for (Index = 0; Index < (FileNameLength - 4) / 2; Index++) { /// Save token name
                                    if (Index == EFI_PERF_PDBFILENAME_LENGTH) {
                                        break;
                                    }
                                    FvNameHob->NameString[Index] = (CHAR8) TempFfsPtr[0];
                                    TempFfsPtr += 2;
                                }
                            }
                        }
                        break; /// FV Found End
                      }
                }
                Instance += 1;
            }
            if (UiFind) {
                (*PeiServices)->CopyMem ( &(FvNameHob->FvGuid),
                                          Guid,
                                          sizeof (EFI_GUID));
            }
            FvNameHob++;
        }
    }

    return EFI_SUCCESS;
}

/**
 * Get S3 performance data and save to Table.
 *    
 * @param[in]   PeiServices                The pointer to the PEI Services Table.
 * @param[in]   CheckPoint                Check point data.
 *
 * @retval EFI_SUCCESS                S3 Data get and save to table  success.
 * @retval EFI_NOT_FOUND            Can't find data.    
 */

EFI_STATUS 
EFIAPI 
GetS3Performance (
            IN EFI_PEI_SERVICES **PeiServices, 
    IN UINT8                    CheckPoint
)
{
    EFI_STATUS                      Status;
    UINT64                          Time;
    UINTN                           VarSize;    
    //EFI_PERF_HEADER                 *PerfHeader;
    EFI_PERF_S3_INFO                *PerfS3Info;
    EFI_PERF_DATA                   *S3Data;
    EFI_PERF_INFO                   *PerfInfo;
    UINT8                           Index = 0;
    PEI_PERFORMANCE_LOG_ENTRY       *LogEntry;
    EFI_PEI_HOB_POINTERS            Hob;
    EFI_PHYSICAL_ADDRESS            AcpiLowMemoryBase;
    UINT8                           Index2 = 0;
    UINT64                          StartTime;
    UINT64                          EndTime;
    UINT64                          StartValue;
    BOOLEAN                         CountDownTimer = FALSE;
    EFI_FPDT_STRUCTURE              *FpdtVar;

    if (CheckPoint == STATUS_CODE_PEI_S3_OS_WAKE) { /// Before exit S3, 80 port will be 0xe3
        Time = GetCpuTimer ();
        VarSize = sizeof (EFI_PHYSICAL_ADDRESS);

        Status = PeiGetVariable (
            PeiServices,
            L"PMPerfDataMemAddr", &gAmiGlobalVariableGuid,    
            NULL, &VarSize, &AcpiLowMemoryBase
        );
        if (EFI_ERROR (Status)) return Status;
        
        VarSize = sizeof (UINT64);
        Status = PeiGetVariable (
            PeiServices,
            L"PMStartValue", &gAmiGlobalVariableGuid,    
            NULL, &VarSize, &StartValue
        );
        if (EFI_ERROR (Status)) return Status;
        
        CountDownTimer = StartValue > 0;
        /*
        PerfHeader = (EFI_PERF_HEADER *) (((UINT32) AcpiLowMemoryBase) + 
                                            sizeof(PERF_TAB_HEADER));
        */
        PerfS3Info = (EFI_PERF_S3_INFO *) (((UINT32) AcpiLowMemoryBase) + sizeof(PERF_TAB_HEADER));
        S3Data = (EFI_PERF_DATA *) (((UINT32) AcpiLowMemoryBase) + 
                                   sizeof(PERF_TAB_HEADER) + 
                                   sizeof(EFI_PERF_S3_INFO));
        PerfInfo = (EFI_PERF_INFO *) (((UINT32) AcpiLowMemoryBase) + 
                                     sizeof(PERF_TAB_HEADER) + 
                                     sizeof(EFI_PERF_S3_INFO) + 
                                     EFI_PERF_PEI_ENTRY_MAX_NUM * sizeof (EFI_PERF_DATA));
        /// Get S3 detailed performance data
        PerfS3Info->S3EntryNum = 0;
        (*PeiServices)->GetHobList (PeiServices, &Hob.Raw);
        Status = FindNextHobByGuid (&gPerformanceProtocolGuid, &Hob.Raw);
        if (EFI_ERROR (Status)) return Status;
{
        UINT32        Counter;
        PEI_PERFORMANCE_LOG_HEADER  *LogHob;
        EFI_GUID                           *Guid = NULL;
        FV_NAME_HOB                  *FvNameHob;
                
        LogHob = (PEI_PERFORMANCE_LOG_HEADER *) (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + sizeof (EFI_GUID));
        LogEntry   = (PEI_PERFORMANCE_LOG_ENTRY *) (LogHob + 1);
        
        (*PeiServices)->GetHobList (PeiServices, &Hob.Raw);
                        
        Status = FindNextHobByGuid (&gEfiPeiFvNameHobGuid, &Hob.Raw);
        if (EFI_ERROR (Status)) return Status;
        FvNameHob = (FV_NAME_HOB *) (Hob.Raw + sizeof (EFI_HOB_GENERIC_HEADER) + sizeof (EFI_GUID));
        
        for(Counter = 0;
            ((Counter < LogHob->NumberOfEntries) && (PerfS3Info->S3EntryNum < EFI_PERF_PEI_ENTRY_MAX_NUM));
            Counter++)
        {
            if (LogEntry[Counter].EndTimeStamp == 0) {
                continue;
            }
            if (Strcmp(LogEntry[Counter].Token, "PEIM")) {
                Guid = NULL;
            } else {
                Guid = &(((EFI_FFS_FILE_HEADER*)(LogEntry[Counter].Handle))->Name);
            }
        if (Guid != NULL) { /// Save GUID And name
            for (Index = 0; Index < (LogHob->NumberOfEntries); Index++) {
                if (!guidcmp(Guid, &(FvNameHob[Index].FvGuid))) { /// GUID match
                    for (Index2 = 0; Index2 < EFI_PERF_PDBFILENAME_LENGTH; Index2++) { /// Save token name
                        if (Index2 == EFI_PERF_PDBFILENAME_LENGTH || (FvNameHob[Index]).NameString[Index2] == 0) {
                            break;
                        }
                        S3Data[PerfS3Info->S3EntryNum].Token[Index2] = (FvNameHob[Index]).NameString[Index2];
                    }
                    break;
                }
            }
              (*PeiServices)->CopyMem ( &(S3Data[PerfS3Info->S3EntryNum].Guid), 
                                        Guid, 
                                        sizeof (EFI_GUID));
        }
        else {
            for (Index = 0; Index < PEI_PERFORMANCE_STRING_SIZE_MAX; Index++) { /// Save token name if no GUID
                S3Data[PerfS3Info->S3EntryNum].Token[Index] = (CHAR8) (LogEntry[Counter].Token[Index]);
                if (LogEntry[Counter].Token[Index] == 0) {
                    break;
                }
            }
        }

        StartTime = LogEntry[Counter].StartTimeStamp;
        EndTime = LogEntry[Counter].EndTimeStamp;

#if !PERFORMANCE_LIBRARY_INCLUDE
        if (CountDownTimer) {
            StartTime = DivU64x64Remainder ( MultU64x32 ((StartValue - StartTime), 1000000) , (UINTN)PerfInfo->CpuFreq, NULL);
            EndTime = DivU64x64Remainder ( MultU64x32 ((StartValue - EndTime), 1000000) , (UINTN)PerfInfo->CpuFreq, NULL);
        } else {
            StartTime = DivU64x64Remainder ( MultU64x32 ((StartTime - StartValue), 1000000) , (UINTN)PerfInfo->CpuFreq, NULL);
            EndTime = DivU64x64Remainder ( MultU64x32 ((EndTime - StartValue), 1000000) , (UINTN)PerfInfo->CpuFreq, NULL);
        }
        /// Save Time
        S3Data[PerfS3Info->S3EntryNum].StartTime = StartTime;
        S3Data[PerfS3Info->S3EntryNum].EndTime = EndTime;
#else
        StartTime =  Div64 (Mul64 (StartTime, (UINTN)PerfInfo->CpuFreq), 1000000, NULL);
        EndTime =  Div64 (Mul64 (EndTime, (UINTN)PerfInfo->CpuFreq), 1000000, NULL);
        
        S3Data[PerfS3Info->S3EntryNum].StartTime = Div64 (StartTime, 1000, NULL);
        S3Data[PerfS3Info->S3EntryNum].EndTime = Div64 (EndTime, 1000, NULL);
#endif
        S3Data[PerfS3Info->S3EntryNum].Duration = S3Data[PerfS3Info->S3EntryNum].EndTime - S3Data[PerfS3Info->S3EntryNum].StartTime;
        
        PerfS3Info->S3EntryNum++;
        }
}
        /// Use core cpu freq to calculate time.
        VarSize = sizeof(UINT32);
        Status = PeiGetVariable(
                PeiServices,
                L"FPDT_Variable_NV", &gAmiGlobalVariableGuid,
                NULL, &VarSize, &FpdtVar);
        /// Time = GetCpuTimer (); /// used to varify s3 time if need.
        if (!EFI_ERROR (Status)) {
            Time = Div64 (Mul64 (Time, (UINTN)FpdtVar->NanoFreq), 1000000, NULL);
        } else {
            Time = Div64 (Mul64 (Time, (UINTN)PerfInfo->CpuFreq), 1000000, NULL);
        }

#if !PERFORMANCE_LIBRARY_INCLUDE
        if (S3Data[PerfS3Info->S3EntryNum - 1].EndTime != 0) {
            Time = S3Data[PerfS3Info->S3EntryNum - 1].EndTime;
        } else {
            Time = Div64 (Time, 1000000, NULL);
        }
#else        
        Time = Div64 (Time, 1000000, NULL);
#endif
        PerfS3Info->S3Resume += Time;
        
        PerfS3Info->S3ResumeNum += 1;
        PerfS3Info->S3ResumeAve = Div64 ((PerfS3Info->S3Resume),
                                         (PerfS3Info->S3ResumeNum),
                                         NULL
                                         );
    }

    return EFI_SUCCESS;
}

/**
 *Create End Of Pei notify function.
 *    
 * @param[in]   PeiServices                The pointer to the PEI Services Table.
 * @param[in]   CheckPoint                Check point data.
 *
 * @retval EFI_SUCCESS                Notify function create success.
 */

EFI_STATUS 
EFIAPI 
PeiInitGetName (
        IN EFI_PEI_SERVICES **PeiServices, 
        IN UINT8 CheckPoint
)
{
    EFI_STATUS  Status;
    
    if (CheckPoint == STATUS_CODE_PEI_NB_INIT_CHECK_POINT) {                
        Status = (*PeiServices)->NotifyPpi ( PeiServices, PmEndOfPeiNotify );
        return Status;
    }
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
