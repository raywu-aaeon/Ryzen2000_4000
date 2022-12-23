/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Heap related functions.
 *
 * Contains code that initialize, maintain, and allocate the heap space.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  LIB
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef _AMD_HEAP_LIB_H_
#define _AMD_HEAP_LIB_H_

/*---------------------------------------------------------------------------------------
 *          M I X E D   (Definitions And Macros / Typedefs, Structures, Enums)
 *---------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *---------------------------------------------------------------------------------------
 */
///Heap Manager Life cycle (Persist)
///For compatile still support previous Persist definition, but will keep the data through boot time for all persist type
///And keep runtime persist for HEAP_RUNTIME_SYSTEM_MEM type.
///Suggest use HEAP_BOOTTIME_SYSTEM_MEM for boot time required, and HEAP_RUNTIME_SYSTEM_MEM for runtime required
#define HEAP_DO_NOT_EXIST_YET        1
#define HEAP_LOCAL_CACHE             2
#define HEAP_TEMP_MEM                3
#define HEAP_SYSTEM_MEM              4
#define HEAP_DO_NOT_EXIST_ANYMORE    5
#define HEAP_S3_RESUME               6
#define HEAP_BOOTTIME_SYSTEM_MEM     7
#define HEAP_RUNTIME_SYSTEM_MEM      8

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */
#pragma pack (push, 1)
/// Allocate Heap Parameters
typedef struct _ALLOCATE_HEAP_PARAMS {
  UINT32  RequestedBufferSize;                    ///< Size of buffer.
  UINT32  BufferHandle;                           ///< An unique ID of buffer.
  UINT8   Persist;                                ///< Persist Flag, refer to the Macro HEAP_X definition above
  UINT8   *BufferPtr;                             ///< Pointer to buffer.
} ALLOCATE_HEAP_PARAMS;

/// Locate Heap Parameters
typedef struct _LOCATE_HEAP_PTR {
  UINT32  BufferHandle;                           ///< An unique ID of buffer.
  UINT32 BufferSize;                              ///< Data buffer size.
  UINT8   *BufferPtr;                             ///< Pointer to buffer.
} LOCATE_HEAP_PTR;
#pragma pack (pop)
/*---------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *---------------------------------------------------------------------------------------
 */

// AGESA_STATUS
// HeapManagerInit (
//   IN       AMD_CONFIG_PARAMS *StdHeader
//   );

AGESA_STATUS
HeapAllocateBuffer (
  IN OUT   ALLOCATE_HEAP_PARAMS *AllocateHeapParams,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
HeapDeallocateBuffer (
  IN       UINT32 BufferHandle,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
HeapLocateBuffer (
  IN OUT   LOCATE_HEAP_PTR *LocateHeap,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/// AGESA Buffer Handles (These are reserved)
typedef enum {
  AMD_INIT_RESET_HANDLE = 0x000A000,              ///< Assign 0x000A000 buffer handle to AmdInitReset routine.
  AMD_INIT_EARLY_HANDLE,                          ///< Assign 0x000A001 buffer handle to AmdInitEarly routine.
  AMD_INIT_POST_HANDLE,                           ///< Assign 0x000A002 buffer handle to AmdInitPost routine.
  AMD_INIT_ENV_HANDLE,                            ///< Assign 0x000A003 buffer handle to AmdInitEnv routine.
  AMD_INIT_MID_HANDLE,                            ///< Assign 0x000A004 buffer handle to AmdInitMid routine.
  AMD_INIT_LATE_HANDLE,                           ///< Assign 0x000A005 buffer handle to AmdInitLate routine.
  AMD_INIT_RESUME_HANDLE,                         ///< Assign 0x000A006 buffer handle to AmdInitResume routine.
  AMD_LATE_RUN_AP_TASK_HANDLE,                    ///< Assign 0x000A007 buffer handle to AmdLateRunApTask routine.
  AMD_INIT_RTB_HANDLE,                            ///< Assign 0x000A008 buffer handle to AmdInitRtb routine.
  AMD_S3_LATE_RESTORE_HANDLE,                     ///< Assign 0x000A009 buffer handle to AmdS3LateRestore routine.
  AMD_S3_SCRIPT_SAVE_TABLE_HANDLE,                ///< Assign 0x000A00A buffer handle to be used for S3 save table
  AMD_S3_SCRIPT_TEMP_BUFFER_HANDLE,               ///< Assign 0x000A00B buffer handle to be used for S3 save table
  AMD_CPU_AP_TASKING_HANDLE,                      ///< Assign 0x000A00C buffer handle to AP tasking input parameters.
  AMD_REC_MEM_SOCKET_HANDLE,                      ///< Assign 0x000A00D buffer handle to save socket with memory in memory recovery mode.
  AMD_MEM_AUTO_HANDLE,                            ///< Assign 0x000A00E buffer handle to AmdMemAuto routine.
  AMD_MEM_SPD_HANDLE,                             ///< Assign 0x000A00F buffer handle to AmdMemSpd routine.
  AMD_MEM_DATA_HANDLE,                            ///< Assign 0x000A010 buffer handle to MemData
  AMD_MEM_TRAIN_BUFFER_HANDLE,                    ///< Assign 0x000A011 buffer handle to allocate buffer for training
  AMD_MEM_S3_DATA_HANDLE,                         ///< Assign 0x000A012 buffer handle to special case register for S3
  AMD_MEM_S3_NB_HANDLE,                           ///< Assign 0x000A013 buffer handle to NB block for S3
  AMD_MEM_S3_MR0_DATA_HANDLE,                     ///< Assign 0x000A014 buffer handle to MR0 data block for S3
  AMD_UMA_INFO_HANDLE,                            ///< Assign 0x000A015 buffer handle to be used for Uma information
  AMD_DMI_MEM_DEV_INFO_HANDLE,                    ///< Assign 0x000A016 buffer handle to DMI Type16 17 19 20 information
  EVENT_LOG_BUFFER_HANDLE,                        ///< Assign 0x000A017 buffer handle to Event Log
  IDS_CONTROL_HANDLE,                             ///< Assign 0x000A018 buffer handle to AmdIds routine.
  IDS_HDT_OUT_BUFFER_HANDLE,                      ///< Assign 0x000A019 buffer handle to be used for HDTOUT support.
  IDS_CHECK_POINT_PERF_HANDLE,                    ///< Assign 0x000A01A buffer handle to Performance analysis
  AMD_PCIE_COMPLEX_DATA_HANDLE,                   ///< Assign 0x000A01B buffer handle to be used for PCIe support
  AMD_MEM_SYS_DATA_HANDLE,                        ///< Assign 0x000A01C buffer handle to be used for memory data structure
  AMD_GNB_SMU_CONFIG_HANDLE,                      ///< Assign 0x000A01D buffer handle to be used for GNB SMU configuration
  AMD_PP_FUSE_TABLE_HANDLE,                       ///< Assign 0x000A01E buffer handle to be used for TT fuse table
  AMD_GFX_PLATFORM_CONFIG_HANDLE,                 ///< Assign 0x000A01F buffer handle to be used for Gfx platform configuration
  AMD_GNB_TEMP_DATA_HANDLE,                       ///< Assign 0x000A020 buffer handle for GNB general purpose data block
  AMD_MEM_2D_RDQS_HANDLE,                         ///< Assign 0x000A021 buffer handle for 2D training
  AMD_MEM_2D_RD_WR_HANDLE,                        ///< Assign 0x000A022 buffer handle for 2D Read/Write training
  AMD_GNB_IOMMU_SCRATCH_MEM_HANDLE,               ///< Assign 0x000A023 buffer handle to be used for GNB IOMMU scratch memory
  AMD_MEM_S3_SAVE_HANDLE,                         ///< Assign 0x000A024 buffer handle for memory data saved right after memory init
  AMD_MEM_2D_RDQS_RIM_HANDLE,                     ///< Assign 0x000A025 buffer handle for 2D training Eye RIM Search
  AMD_MEM_2D_RD_WR_RIM_HANDLE,                    ///< Assign 0x000A026 buffer handle for 2D Read/Write training Eye RIM Search
  AMD_CPU_NB_PSTATE_FIXUP_HANDLE,                 ///< Assign 0x000A027 buffer handle for an NB P-state workaround
  AMD_MEM_CRAT_INFO_BUFFER_HANDLE,                ///< Assign 0x000A028 buffer handle for CRAT Memory affinity component structure
  AMD_SKIP_MEM_S3_SAVE,                           ///< Assign 0x000A029 buffer handle for the flag to skip memory S3 save
  AMD_IS_FEATURE_ENABLED,                         ///< Assign 0x000A02A buffer handle for keeping the result of IsFeatureEnabled
  AMD_MEM_DATAEYE_WORK_AREA_HANDLE,               ///< Assign 0x000A02B buffer handle for Composite Data Eye Compression Work Area
  AMD_GNB_SAMU_PATCH_HANDLE,                      ///< Assign 0x000A02C buffer handle for Samu patch buffer
  AMD_GNB_SAMU_BOOT_CONTROL_HANDLE,               ///< Assign 0x000A02D buffer handle for Samu boot control buffer
  AMD_GNB_ACP_ENGINE_HANDLE,                      ///< Assign 0x000A02E buffer handle for GNB ACP engine buffer
  AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE,              ///< Assign 0x000A02F buffer handle for PMU SRAM Message Block buffer
  AMD_MEM_DRAM_CAD_BUS_CONFIG_HANDLE,             ///< Assign 0x000A030 buffer handle for DRAM CAD Bus Configuration
  AMD_GNB_SMU_TABLE_HANDLE,                       ///< Assign 0x000A031 buffer handle for GNB SMU table buffer
  AMD_GNB_CRAT_HSA_TABLE_HANDLE,                  ///< Assign 0x000A032 buffer handle for GNB CRAT HSA unit table
  AMD_GNB_BUILD_OPTIONS_HANDLE,                   ///< Assign 0x000A033 buffer handle for GNB build options
  AMD_S3_FINAL_RESTORE_HANDLE,                    ///< Assign 0x000A034 buffer handle to AmdS3FinalRestore routine.
  AMD_GNB_PCIE_AER_CONFIG_HANDLE,                 ///< Assign 0x000A035 buffer handle for GNB PCIE AER configuration.
  AMD_BTC_SCRATCH_HANDLE,                         ///< Assign 0x000A036 buffer handle for boot time calibration workloads
  AMD_BTC_XMM_SAVE_HANDLE,                        ///< Assign 0x000A037 buffer handle for boot time calibration xmm register save
  AMD_PSP_DIRECTORY_BUFFER_HANDLE,                ///< Assign 0x000A037 buffer handle to PSP Dir buffer
  AMD_PSP_L2_DIRECTORY_BUFFER_HANDLE,             ///< Assign 0x000A038 buffer handle to PSP L2 Dir buffer
  AMD_S3_SAVE_HANDLE,                             ///< Assign 0x000A038 buffer handle to memory context data
  AMD_MEM_DDR_MAX_RATE_HANDLE,                    ///< Assign 0x000A039 buffer handle to memory DDR max rate
  AMD_GNB_TDP_HANDLE,                             ///< Assign 0x000A03A buffer handle to GNB TDP
  AMD_FABRIC_PSTATE_LIB_HANDLE,                   ///< Assign 0x000A03B buffer handle to Fabric Pstate lib
  AMD_ACPI_TABLE_BUFFER_HANDLE,                   ///< Assign 0x000A03C buffer handle to ACPI Tables
  AMD_MMIO_MANAGER,                               ///< Assign 0x000A03D buffer handle to DF MMIO manager
  AMD_IO_MANAGER,                                 ///< Assign 0x000A03D buffer handle to DF IO manager
  AMD_PFEH_HANDLE,                                ///< Assign 0x000A03F buffer handle to PFEH mode
  AMD_MEM_MISC_HANDLES_START = 0x1000000,         ///< Reserve 0x1000000 to 0x1FFFFFF buffer handle
  AMD_MEM_MISC_HANDLES_END = 0x1FFFFFF,           ///< miscellaneous memory init tasks' buffers.
  AMD_HEAP_IN_MAIN_MEMORY_HANDLE = 0x8000000,     ///< Assign 0x8000000 to AMD_HEAP_IN_MAIN_MEMORY_HANDLE.
  SOCKET_DIE_MAP_HANDLE = 0x534F4B54,             ///< 'sokt'
  NODE_ID_MAP_HANDLE = 0x4E4F4445,                ///< 'node'
  HOP_COUNT_TABLE_HANDLE = 0x484F5053,            ///< 'hops'
  AMD_FCH_RESET_DATA_BLOCK_HANDLE = 0x46434852,   ///< 'FCHR' Buffer handle for FCH private data block at InitReset
  AMD_FCH_DATA_BLOCK_HANDLE = 0x46434845,         ///< 'FCHE' Buffer handle for FCH private data block at InitEnv
  IDS_TRAP_TABLE_HANDLE = 0x49524547,             ///< 'IREG' Handle for IDS register table
  IDS_SAVE_IDTR_HANDLE = 0x49445452,              ///< 'IDTR'
  IDS_BSC_IDT_HANDLE = 0x42534349,                ///< 'BSCI' BSC Idt table
  IDS_NV_TO_CMOS_HANDLE = 0x534D4349,             ///< 'ICMS' Handle for IDS CMOS save
  IDS_GRA_HANDLE = 0x41524749,                    ///< 'IGRA' Handle for IDS GRA save
  IDS_EXTEND_HANDLE = 0x54584549,                 ///< 'IEXT' Handle for IDS extend module
  IDS_TEMP_DATA_HANDLE = 0x504D5459,              ///< 'ITMP' Handle for IDS temp data
  IDS_NV_TABLE_DATA_HANDLE = 0x4254564E,          ///< 'NVTB' Handle for IDS NV table data
  IDS_NV_TABLE_DATA_DXE_HANDLE = 0x5444564E,      ///< 'NVDT' Handle for DXE IDS NV table data
} AGESA_BUFFER_HANDLE;

#endif // _AMD_HEAP_LIB_H_

