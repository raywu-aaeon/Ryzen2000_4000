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

/** @file PerformanceMeasurement.h
 *  PerformanceMeasurement functions definitions.
 */

#ifndef __DP__H__
#define __DP__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Acpi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#define FPDT_SIG 0x54445046     ///<FPDT
#define PERF_SIG 0x66726550     ///<Perf
#define PMPT_SIG 0x54504D50     ///<PMPT
#define IS_HYPHEN(a)            ((a) == L'-')
#define IS_NULL(a)              ((a) == L'\0')
#define STR_SIZE_FOR_GUID       36
#define MILLION                 1000000

#define PROGRESS_ID_LOAD_IMAGE_START        1
#define PROGRESS_ID_LOAD_IMAGE_END          2
#define PROGRESS_ID_START                   3
#define PROGRESS_ID_END                     4

#define GUID_EVENT_REC_LENGTH               34
#define STRING_EVENT_REC_LENGTH             58
#define PEI_PERFORMANCE_STRING_SIZE_MAX     16
#define STATUS_CODE_PEI_NB_INIT_CHECK_POINT 0x15
#define STATUS_CODE_PEI_S3_OS_WAKE          0xE3




VOID 
EFIAPI 
PmBuild(    
 IN EFI_EVENT        Event,
 IN VOID             *Context);

/// Data structure
/// {83E3B906-4D88-4e0b-B8B0-D4B89E26E05A}
#define AMI_FV_NAME_HOB_GUID {0x83e3b906, 0x4d88, 0x4e0b, {0xb8, 0xb0, 0xd4, 0xb8, 0x9e, 0x26, 0xe0, 0x5a}}

#define EFI_PERF_PEI_ENTRY_MAX_NUM     100    

/// If this data set to 1, time calculate will follow PerformancePkg
///#define PERFORMANCE_LIBRARY_INCLUDE 1

/// Performance Record Types define
#define EFI_FIRMWARE_BASIC_BOOT_PERFORMANCE_POINTER_RECORD         0x0000
#define EFI_S3_PERFORMANCE_TABLE_POINTER_RECORD                 0x0001
#define AMI_POST_PERFORMANCE_TABLE_POINTER_RECORD                 0x3622
/// 0x0002 - 0x0FFF Reserved for ACPI specification usage.
/// 0x1000 - 0x1FFF Reserved for Platform Vendor usage. 
/// 0x2000 - 0x2FFF Reserved for Hardware Vendor usage.
/// 0x3000 - 0x3FFF Reserved for BIOS Vendor usage.
/// 0x4000 - 0xFFFF Reserved for future use

/// Runtime Performance Record Types define
#define EFI_RUNTIME_S3_RESUME_PERFORMANCE_RECORD                 0x0000
#define EFI_RUNTIME_S3_SUSPEND_PERFORMANCE_RECORD                 0x0001
#define EFI_RUNTIME_FIRMWARE_BASIC_BOOT_PERFORMANCE_DATA_RECORD 0x0002
/// 0x0003 - 0x0FFF Reserved for ACPI specification usage.
/// 0x1000 - 0x1FFF Reserved for Platform Vendor usage. 
/// 0x2000 - 0x2FFF Reserved for Hardware Vendor usage.
/// 0x3000 - 0x3FFF Reserved for BIOS Vendor usage.
/// 0x4000 - 0xFFFF Reserved for future use

/// System Scope Tool Format Performance Record Types
#define BOOT_MODULE_PERFORMANCE_TABLE_POINTER_RECORD            0x1002
#define RUNTIME_MODULE_TABLE_POINTER_RECORD                     0x1003
#define TIMESTAMP_DELTA_RECORD                                  0x1004
#define HARDWARE_BOOT_PERFORMANCE_RECORD                        0x1005
#define EVENT_RECORD_WITH_GUID                                  0x1010
#define EVENT_RECORD_WITH_STRING                                0x1011
#define BDS_ATTEMPT_EVENT_RECORD                                0x1012
/// System Scope Tool Format Runtime Performance Record Types
#define RUNTIME_MODULE_REC_TYPE                                 0x1020
#define RUNTIME_FUNCTION_REC_TYPE                               0x1021
#define EFI_FPDT_VARIABLE   L"FPDT_Volatile"

/// Data structure
#pragma    pack(push, 1)
/// AMI define
typedef struct _EFI_PHASE_PERF_DATA{
    CHAR8   Token[4];
    UINT64  StartTime;
    UINT64  EndTime;
    UINT64  Duration;
} EFI_PHASE_PERF_DATA;

typedef struct _EFI_PERF_DATA{
    CHAR8    Token[EFI_PERF_PDBFILENAME_LENGTH];
    EFI_GUID Guid;
    UINT64   StartTime;
    UINT64   EndTime;
    UINT64   Duration;
} EFI_PERF_DATA;

typedef struct _EFI_PERF_S3_INFO{
    UINT64        S3Resume;       ///< Total time
    UINT32        S3EntryNum;     ///< Module numbers
    UINT32        S3ResumeNum;    ///< S3 resume numbers
    UINT64        S3ResumeAve;    ///< Average time
    UINT16        S3EntryReservedSpaceNumber;   /// EFI_PERF_PEI_ENTRY_MAX_NUM number, AMIPerfRecordDump can easy to know how many space reseverved for S3 resume data.
} EFI_PERF_S3_INFO;
//    EFI_PERF_DATA S3Entry[EFI_PERF_PEI_ENTRY_MAX_NUM];
typedef struct _EFI_PERF_INFO{
    UINT64        CpuFreq;        ///< CPU frequency
    UINT32        Count;          ///< Total module number
    UINT32        Signiture;      ///< Signiture,
} EFI_PERF_INFO;

typedef struct _MEASUREMENT_RECORD{
  VOID                      *Handle;
  CHAR8                     Token[40];        ///< Measured token string name.
  CHAR8                     Module[40];       ///< Module string name.
  UINT64                    StartTimeStamp;   ///< Start time point.
  UINT64                    EndTimeStamp;     ///< End time point.
  UINT32                    Identifier;       ///< Identifier.
  EFI_GUID                  GuidName;
  CHAR8   PdbFileName[EFI_PERF_PDBFILENAME_LENGTH];
} MEASUREMENT_RECORD;

typedef    struct _GUID_EVENT_RECORD {    
    UINT16                  GuidEventRecType;        
    UINT8                   Length;                    
    UINT8                   Revision;                
    UINT16                  ProgressId;           
    UINT32                  ProcessorId;        
    UINT64                  Timestamp;                
    EFI_GUID                Guid;                    
} GUID_EVENT_RECORD;

typedef    struct _STRING_EVENT_RECORD {    
    UINT16                  StringEventRecType;        
    UINT8                   Length;                    
    UINT8                   Revision;                
    UINT16                  ProgressId;               
    UINT32                  ProcessorId;            
    UINT64                  Timestamp;                
    EFI_GUID                Guid;                    
    CHAR8                   NameString[24];            
} STRING_EVENT_RECORD;

typedef    struct _PERF_REC_HEADER {    
    UINT16                  PerfRecType;        
    UINT8                   RecLength;            
    UINT8                   Revision;          
} PERF_REC_HEADER,*PPERF_REC_HEADER;

typedef struct _BASIC_BOOT_PERF_REC {
    PERF_REC_HEADER         Header;               
    UINT32                  Reserved;                
    UINT64                  ResetEnd;                  
    UINT64                  OsLoaderLoadImageStart;    
    UINT64                  OsLoaderStartImageStart;    
    UINT64                  ExitBootServicesEntry;     
    UINT64                  ExitBootServicesExit;       
} BASIC_BOOT_PERF_REC,*PBASIC_BOOT_PERF_REC;

typedef struct {
    ACPI_HDR                AcpiTableData;
    UINT32                  PerfDataMemAddr;
    VOID                    *PerformanceData;
}EFI_PM_ACPITABLE;

typedef    struct _EFI_FPDT_STRUCTURE {
    EFI_PHYSICAL_ADDRESS    S3Pointer;
    EFI_PHYSICAL_ADDRESS    BasBootPointer;
    UINT64                  NanoFreq;
} EFI_FPDT_STRUCTURE;

typedef    struct _FPDT_PERF_RECORD {    
    UINT16                  PerfRecType;        
    UINT8                   Length;                
    UINT8                   Revision;            
    UINT32                  Reserved;          
    EFI_PHYSICAL_ADDRESS    Pointer;            
} FPDT_PERF_RECORD,*PFPDT_PERF_RECORD;

typedef struct _FPDT_50 {
    ACPI_HDR            Header;
    FPDT_PERF_RECORD    BasS3Rec; 
    FPDT_PERF_RECORD    BasBootRec;     
} FPDT_50,*PFPDT_50;

typedef struct _AMI_FPDT_50 {
    ACPI_HDR            Header;
    FPDT_PERF_RECORD    BasS3Rec; 
    FPDT_PERF_RECORD    BasBootRec; 
    FPDT_PERF_RECORD    AmiBootRec;        
} AMI_FPDT_50;

typedef    struct _PERF_TAB_HEADER{    
    UINT32              Signature;            
    UINT32              Length;        
} PERF_TAB_HEADER;

typedef struct _FV_NAME_HOB {
    EFI_GUID            FvGuid;
    CHAR8               NameString[EFI_PERF_PDBFILENAME_LENGTH];
} FV_NAME_HOB;
#pragma pack(pop)
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
