/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU Execution Cache Allocation functions.
 *
 * Contains code for doing Execution Cache Allocation for ROM space
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU
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

#ifndef _CPU_CACHE_INIT_H_
#define _CPU_CACHE_INIT_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define BSP_STACK_SIZE_64K        65536
#define BSP_STACK_SIZE_32K        32768

#define CORE0_STACK_SIZE          16384
#define CORE1_STACK_SIZE          4096

#define AMD_MTRR_FIX4K_BASE     0x268
#define AMD_MTRR_VARIABLE_BASE6 0x20C
#define AMD_MTRR_VARIABLE_BASE7 0x20E

#define WP_IO 0x0505050505050505ull

#define AGESA_CACHE_SIZE_REDUCED              1
#define AGESA_CACHE_REGIONS_ACROSS_1MB        2
#define AGESA_CACHE_REGIONS_ACROSS_4GB        3
#define AGESA_REGION_NOT_ALIGNED_ON_BOUNDARY  4
#define AGESA_CACHE_START_ADDRESS_LESS_D0000  5
#define AGESA_THREE_CACHE_REGIONS_ABOVE_1MB   6
#define AGESA_DEALLOCATE_CACHE_REGIONS        7

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */
/// Cache-As-Ram Executable region allocation modes
typedef enum {
  LimitedByL2Size,                            ///< Execution space must be allocated from L2
  InfiniteExe,                                ///< Family can support unlimited Execution space
  MaxCarExeMode                               ///< Used as limit or bounds check
} CAR_EXE_MODE;

/// Cache Information
typedef struct {
  IN       UINT32  BspStackSize;              ///< Stack size of BSP
  IN       UINT32  Core0StackSize;            ///< Stack size of primary cores
  IN       UINT32  Core1StackSize;            ///< Stack size of all non primary cores
  IN       UINT32  MemTrainingBufferSize;     ///< Memory training buffer size
  IN       UINT32  SharedMemSize;             ///< Shared memory size
  IN       UINT64  VariableMtrrMask;          ///< Mask to apply before variable MTRR writes
  IN       UINT64  VariableMtrrHeapMask;      ///< Mask to apply before variable MTRR writes for use in heap init.
  IN       UINT64  HeapBaseMask;              ///< Mask used for the heap MTRR settings
  IN CAR_EXE_MODE  CarExeType;                ///< Indicates which algorithm to use when allocating EXE space
} CACHE_INFO;

/// Merged memory region overlap type
typedef enum {
  EmptySet,                                   ///< One of the regions is zero length
  Disjoint,                                   ///< The two regions do not touch
  Adjacent,                                   ///< one region is next to the other, no gap
  CommonEnd,                                  ///< regions overlap with a common end point
  Extending,                                  ///< the 2nd region is extending the size of the 1st
  Contained,                                  ///< the 2nd region is wholely contained inside the 1st
  CommonStartContained,                       ///< the 2nd region is contained in the 1st with a common start
  Identity,                                   ///< the two regions are the same
  CommonStartExtending,                       ///< the 2nd region has same start as 1st, but is larger size
  NotCombinable                               ///< the combined regions do not follow the cache block rules
} OVERLAP_TYPE;

/// Result of merging two memory regions for cache coverage
typedef struct {
  IN OUT  UINT32        MergedStartAddr;      ///< Start address of the merged regions
  IN OUT  UINT32        MergedSize;           ///< Size of the merged regions
     OUT  UINT32        OverlapAmount;        ///< the size of the overlapping section
     OUT  OVERLAP_TYPE  OverlapType;          ///< indicates how the two regions overlap
} MERGED_CACHE_REGION;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */
AGESA_STATUS
AllocateExecutionCache (
  IN AMD_CONFIG_PARAMS *StdHeader,
  IN EXECUTION_CACHE_REGION *AmdExeAddrMapPtr
  );

#endif  // _CPU_CACHE_INIT_H_


