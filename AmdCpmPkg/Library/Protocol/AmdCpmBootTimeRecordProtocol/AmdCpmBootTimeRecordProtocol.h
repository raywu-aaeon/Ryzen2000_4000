/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _AMD_CPM_BOOT_TIME_RECORD_PROTOCOL_H_
#define _AMD_CPM_BOOT_TIME_RECORD_PROTOCOL_H_

#include <AmdCpmBase.h>

#define AMD_BOOT_TIME_RECORD_PROTOCOL_GUID \
{ \
  0x91599780, 0x50b0, 0x43d0, 0x9f, 0x21, 0x42, 0xd1, 0xeb, 0xc, 0x0, 0x3f \
}

#pragma pack (push, 1)
/// Boot Timing Record Data for PEI stage
typedef struct _AMD_BOOT_TIME_PEI_DATA {
  #ifdef TSC_TIMER_TICK_ENABLE
    UINT64    TscTicks;               ///<CPU TSC timing tick
  #endif
  #ifdef ACPI_TIMER_TICK_ENABLE
    UINT32    AcpiTimerTicks;         ///<ACPI Timer tick
  #endif
  UINT32    Version;                  ///< Version number
  UINT64    Description;              ///< Description of test points
}  AMD_BOOT_TIME_PEI_DATA;

/// Boot Time Record data holder
typedef struct _AMD_BOOT_TIME_PEI_RECORD {
  UINT16                   IndexToWrite;            ///< Last index wrote
  AMD_BOOT_TIME_PEI_DATA   data[MAXIMUM_RECORDS];   ///< Boot time record data holder
} AMD_BOOT_TIME_PEI_RECORD;

///Boot Timing Record Data for DXE stage
typedef struct _AMD_BOOT_TIME_DATA {
  #ifdef TSC_TIMER_TICK_ENABLE
    UINT64    TscTicks;                 ///<CPU TSC timing tick
  #endif
  #ifdef ACPI_TIMER_TICK_ENABLE
    UINT32    AcpiTimerTicks;           ///<ACPI Timer tick
  #endif
  UINT32    Version;                    ///< Version number
  UINT64    Description;                ///< Description of test points
}  AMD_BOOT_TIME_DATA;

///Linked List of Boot Time Record data
typedef struct _AMD_BOOT_TIME_RECORD_ITEM {
  AMD_BOOT_TIME_DATA                   data;         ///< Boot Time Record Data
  struct _AMD_BOOT_TIME_RECORD_ITEM    *NextRecord;  ///< Next record
} AMD_BOOT_TIME_RECORD_ITEM;

/// Boot Time Record data structure.
typedef struct _AMD_BOOT_TIME_RECORD {
  UINT16                       Index;      ///< Number of data
  AMD_BOOT_TIME_RECORD_ITEM    *ItemHead;  ///< Pointer to first data item.
} AMD_BOOT_TIME_RECORD;

#ifdef IDS_PERFORMANCE_ENABLE
  #define MAX_PERFORMANCE_UNIT_NUM MAX_IDS_PERFORMANCE_UNIT_NUM
  /// Data Structure of Parameters for TestPoint_TSC.
  typedef struct {
    UINT32 LineInFile;                    ///< Line of current time counter
    UINT64 Description;                   ///<Description ID
    UINT64 StartTsc;                      ///< The StartTimer of TestPoint_TSC
    #ifdef ACPI_TIMER_TICK_ENABLE
      UINT32 StartAcpiTimer;              ///< Start of ACPI Timer
    #endif
  } TestPoint_TSC;

  /// Data Structure of Parameters for TP_Perf_STRUCT.
  typedef struct {
    UINT32 Signature;                                  ///< "TIME"
    UINT32 Index;                                      ///< The Index of TP_Perf_STRUCT
    UINT32 TscInMhz;                                   ///< Tsc counter in 1 mhz
    #ifdef ACPI_TIMER_TICK_ENABLE
      UINT32 AcpiTimer;                                  ///<ACPI Timer tick
    #endif
    UINT32 Version;                                   ///< Version number
    TestPoint_TSC TP[MAX_PERFORMANCE_UNIT_NUM];       ///< The TP of TP_Perf_STRUCT
  } TP_Perf_STRUCT;
#endif

#pragma pack (pop)


typedef
EFI_STATUS
(EFIAPI *AMD_BOOT_TIME_RECORD_ADD) (
  IN  UINT64                      desc
  );

#ifdef IDS_PERFORMANCE_ENABLE
  typedef
  EFI_STATUS
  (EFIAPI *AMD_BOOT_TIME_RECORD_IDS) (
    IN  OUT VOID *IdsCalloutData
    );
#endif

/// Boot Time Record Protocol
typedef struct _AMD_BOOT_TIME_RECORD_PROTOCOL {
  AMD_BOOT_TIME_RECORD        *Record;                             /// < Pointer to fist items in record.
  AMD_BOOT_TIME_PEI_RECORD    *S3Record;                           /// < Pointer to fist items in record for Standby.
  #ifdef IDS_PERFORMANCE_ENABLE
    TP_Perf_STRUCT              *IdsRecord;                          ///< IDS record
    TP_Perf_STRUCT              *IdsS3Record;                        ///< IDS S3 resume wheacle
    AMD_BOOT_TIME_RECORD_IDS    CopyIdsPerformanceDataToIdsRecord;   ///< Function pointer to AGESA IDS Timing Points
  #endif
  AMD_BOOT_TIME_RECORD_ADD    AddRecord;                             ///< Function pointers to add record
} AMD_BOOT_TIME_RECORD_PROTOCOL;

extern EFI_GUID gBootTimeRecordProtocolGuid;

extern EFI_STATUS RecordTimeTicksDxe (
  IN UINT64                     desc
);

extern EFI_STATUS RecordTimeTicksSmm (
  IN EFI_BOOT_SERVICES          *mBS,
  IN UINT64                     desc
);

#ifdef IDS_PERFORMANCE_ENABLE
  extern EFI_STATUS RecordTimeTicksAGESA (
    IN  OUT VOID *IdsCalloutData
  );
#endif

#ifdef AMD_BIOS_BOOT_TIME_RECORD
  #define RECORD_TIME_SMM(x)  RecordTimeTicksSmm(gBS, x);
  #define RECORD_TIME_DXE(x)  RecordTimeTicksDxe(x);
  #ifdef IDS_PERFORMANCE_ENABLE
    #define RECORD_TIME_AGESA(x) RecordTimeTicksAGESA((VOID *)x);
  #else
    #define RECORD_TIME_AGESA(x)
  #endif
#else
  #define RECORD_TIME_SMM(x)
  #define RECORD_TIME_DXE(x)
  #define RECORD_TIME_AGESA(x)
#endif
#endif
