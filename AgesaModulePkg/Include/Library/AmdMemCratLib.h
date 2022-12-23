/* $NoKeywords:$ */
/**
 * @file
 *
 * mfCrat.h
 *
 * Feature CRAT table support
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


#ifndef _MFCRAT_H_
#define _MFCRAT_H_

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

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/// DCT Select Interleaving Address Mapping
typedef struct {
  UINT8                 DctSelIntLvAddr;        ///< F2x110 DctSelIntLvAddr
  UINT8                 DctSelFunctionBit;      ///< Lowest function bit to select DCT for interleaving
} DCTSELBIT_ENTRY;

/// CRAT Memory Affinity Info Header
typedef struct {
  UINT8                 NumOfMemAffinityInfoEntries;  ///< Integer that represents the proximity domain to
  UINT32                MemoryWidth;                  ///< Specifies the number of parallel bits of the memory interface
} CRAT_MEMORY_AFFINITY_INFO_HEADER;

/// CRAT Memory Affinity Info Entry
typedef struct {
  UINT8                 Domain;                 ///< Integer that represents the proximity domain to
                                                ///< which the memory belongs
  UINT32                BaseAddressLow;         ///< Low 32Bits of the Base Address of the memory range
  UINT32                BaseAddressHigh;        ///< High 32Bits of the Base Address of the memory range
  UINT32                LengthLow;              ///< Low 32Bits of the length of the memory range
  UINT32                LengthHigh;             ///< High 32Bits of the length of the memory range
} CRAT_MEMORY_AFFINITY_INFO_ENTRY;

CRAT_MEMORY_AFFINITY_INFO_ENTRY *
MakeMemAffinityInfoEntry (
  IN UINT8                            Domain,
  IN UINT64                           Base,
  IN UINT64                           Size,
  IN CRAT_MEMORY_AFFINITY_INFO_ENTRY  *BufferLocPtr
);

UINT32
MemFCratApproximateSize (
  IN OUT   MEM_NB_BLOCK        *NBPtr
  );

UINT64
GetDctInterleavedMemSize (
  IN OUT   MEM_NB_BLOCK        *NBPtr
  );

UINT64
GetBankInterleavedAddress (
  IN OUT   MEM_NB_BLOCK        *NBPtr,
  IN       UINT64              DctBaseAddress,
  IN       UINT8               InterleavingPosition
  );

UINT64
GetChannelInterleavedAddress (
  IN OUT   MEM_NB_BLOCK        *NBPtr,
  IN       UINT64              NodeBaseAddress,
  IN       UINT8               InterleavingPosition
  );

UINT64
GetBaseAddrOfNonInterleavedRegion (
  IN OUT   MEM_NB_BLOCK        *NBPtr,
  IN       UINT8               DctLimit
  );

BOOLEAN
MemFCratSupport (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );
/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

#endif  /* _MFCRAT_H_ */

