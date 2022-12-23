/* $NoKeywords:$ */
/**
 * @file
 *
 * mu.h
 *
 * Utility support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 **/
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
  *
 */

#ifndef _MU_H_
#define _MU_H_

#include "SocLogicalId.h"

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
#ifndef PSO_ENTRY
  #define PSO_ENTRY UINT8
#endif

//
// Maximum value macro
//
#ifndef MAX
  #define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#endif
//
// Minimum Value macro
//
#ifndef MIN
  #define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif
//
// Absolute Value Macro
//
#ifndef ABS
  #define ABS(X) (((X) < 0) ? (-(X)) : (X))
#endif
//
// Taking ceiling of (a / b)
//
#ifndef CEIL_DIV
  #define CEIL_DIV(a, b)  (((a) + (b) - 1) / (b))
#endif
//
// Check if value x is a power of 2 or not
//
#ifndef IS_POWER_OF_2
  #define IS_POWER_OF_2(x)  (((x) & ((x) - 1)) == 0)
#endif
//
// Find offset of a member variable in a struct
//
#ifndef OFFSET_OF
  #define OFFSET_OF(s, m) ((UINTN) ( (UINT8 *)&((s *)0)->m - (UINT8 *)0 ))
#endif

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/// Test patterns for DQS training
typedef enum {
  TestPattern0,             ///< Test pattern used in first pass of receiver enable training
  TestPattern1,             ///< Test pattern used in first pass of receiver enable training
  TestPattern2,             ///< Test pattern used in second pass of receiver enable training
  TestPatternJD1B,          ///< 72-bit test pattern used in position training (ganged mode)
  TestPatternJD1A,          ///< 72-bit test pattern used in position training
  TestPatternJD256B,        ///< 256-bit test pattern used in position training (ganged mode)
  TestPatternJD256A,        ///< 256-bit test pattern used in position training
  TestPatternML,            ///< Test pattern used in first pass of max latency training
  TestPattern3,             ///< Test pattern used in first pass of receiver enable training
  TestPattern4              ///< Test pattern used in first pass of receiver enable training
} TRAIN_PATTERN;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

VOID
MemUWriteCachelines (
  IN       UINT32 Address,
  IN       UINT8 Pattern[],
  IN       UINT16 ClCount
  );

VOID
MemUReadCachelines (
  IN       UINT8 Buffer[],
  IN       UINT32 Address,
  IN       UINT16 ClCount
  );

VOID
MemUDummyCLRead (
  IN       UINT32 Address
  );

VOID
MemUFlushPattern (
  IN       UINT32 Address,
  IN       UINT16 ClCount
  );


VOID
MemUFillTrainPattern (
  IN       TRAIN_PATTERN Pattern,
  IN       UINT8 Buffer[],
  IN       UINT16 Size
  );

UINT32
MemUSetUpperFSbase (
  IN       UINT32 Address,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

VOID
MemUSetTargetWTIO (
  IN       UINT32 Address,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

VOID
MemUResetTargetWTIO (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

VOID
MemUProcIOClFlush (
  IN       UINT32 Address,
  IN       UINT16 ClCount,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

VOID
MemUWait10ns (
  IN       UINT32 Count,
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

VOID
MemUGetWrLvNblErr (
  IN OUT   UINT16 *ErrBitmap,
  IN       UINT32 TestAddr,
  IN       UINT16 ClCount
  );

VOID
AlignPointerTo16Byte (
  IN OUT   UINT8 **BufferPtrPtr
  );

VOID *
FindPSOverrideEntry (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       PSO_ENTRY EntryType,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID,
  IN       UINT8 DimmID,
  IN       SOC_LOGICAL_ID *LogicalIdPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT8
GetMaxDimmsPerChannel (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN UINT8 SocketID,
  IN UINT8 ChannelID
  );

UINT8
GetMaxSolderedDownDimmsPerChannel (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 SocketID,
  IN       UINT8 ChannelID
  );

UINT8
GetMaxChannelsPerSocket (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN UINT8 SocketID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT8
GetMaxCSPerChannel (
  IN      PSO_TABLE *PlatformMemoryConfiguration,
  IN      UINT8 SocketID,
  IN      UINT8 ChannelID
  );

UINT8
GetSpdSocketIndex (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN UINT8 SocketID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT8
GetSpdChannelIndex (
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN UINT8 SocketID,
  IN UINT8 ChannelID,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

UINT32
GetVarMtrrHiMsk (
  IN       SOC_LOGICAL_ID *LogicalIdPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MemUMFenceInstr (
  VOID
  );

UINT32
MemUnsToMemClk (
  IN       UINT32 Speed,
  IN       UINT32 NumberOfns
  );
#endif  /* _MU_H_ */



