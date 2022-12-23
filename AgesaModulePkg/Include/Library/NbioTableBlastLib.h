/* $NoKeywords:$ */
/**
 * @file
 *
 * Defines needed to define NBIO Tables
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: NBIO
 * @e \$Revision$   @e \$Date$
 *
 */
/*
*****************************************************************************
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
#ifndef _NBIOTABLEBLAST_H_
#define _NBIOTABLEBLAST_H_

#include "AMD.h"
#include <GnbDxio.h>

#pragma pack (push, 1)

#define ONE_ADDR_TYPE 0  ///< Apply table entry just once to the supplied address
#define ALL_NBIO_TYPE 1  ///< Apply table entry once per NBIO. Address supplied should be NBIO0.
#define ALL_WRAP_TYPE 2  ///< Apply table entry to all wrappers
#define ALL_PORT_TYPE 3  ///< Apply table entry to all ports


#define NBIO_TABLE_FLAGS_FORCE_S3_SAVE  0x00000001ul

#define __DATA(x) x

/// Break up UINT64 or UINT32 value into individual bytes so
/// they can be generically initialized into a byte array
#define _DATA32(Data) ((UINT32) (__DATA(Data))) & 0xFF, (((UINT32) (__DATA(Data))) >> 8) & 0xFF, (((UINT32) (__DATA(Data))) >> 16) & 0xFF, (((UINT32) (__DATA(Data))) >> 24) & 0xFF
#define _DATA64(Data) _DATA32(Data & 0xfffffffful) , _DATA32((UINT64) Data >> 32)

typedef UINT8 GNB_TABLE;

/// Entry type
typedef enum {
  GnbEntryWr,                     ///< Write register
  GnbEntryRmw,                    ///< Read Modify Write register
  GnbEntryPropertyRmw,            ///< Read Modify Write register check property
  GnbEntryStall,                  ///< Copy field from one register to another
  GnbEntryPcdWr,                  ///< Write register contingent on a PCD value
  GnbEntryPcdRmw,                 ///< Read Modify Write register contingent on a PCD value
  GnbEntryTerminate = 0xFF        ///< Terminate table
} GNB_TABLE_ENTRY_TYPE;

/// Pass these in to determine PCD Operation Type
typedef enum {
  TableBlastWriteIfValEqual,
  TableBlastWriteIfValNotEqual,
  TableBlastWriteValue,
} GNB_TABLE_PCD_OPERATION_TYPE;

///
/// Header stucture all table entries have in common
///
typedef struct {
  UINT8           EntryType;               ///< Entry type as listed in the above enum GNB_TABLE_ENTRY_TYPE
  UINT8           RegisterSpaceType;       ///< Register space type
} ENTRY_HEAD;

///
/// Info structure that all Read/Modify/Write entries have in
/// common
///
typedef struct {
  UINT32  Address;                ///< Register address
  UINT32  AndMask;                ///< And Mask
  UINT32  OrMask;                 ///< Or Mask
} GNB_RMW_BLOCK;

///
/// Write register entry : start
///
#define GNB_ENTRY_WR(RegisterSpaceType, Address, Value) \
  GnbEntryWr, RegisterSpaceType, _DATA32 (Address), _DATA32 (Value)

typedef struct {
  ENTRY_HEAD  Head;               ///< Structure descriptor
  UINT32  Address;                ///< Register address
  UINT32  Value;                  ///< Value
} GNB_TABLE_ENTRY_WR;
///
/// Write register entry : end
///

///
/// Read/Modify/Write register entry : start
///
#define GNB_ENTRY_RMW(RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryRmw, RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

typedef struct {
  ENTRY_HEAD      Head;           ///< Structure descriptor
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_RMW;
///
/// Read/Modify/Write register entry : end
///

///
/// Write register entry based off of PCD : start
///
#define GNB_ENTRY_PCD_WR(RegisterSpaceType, PcdToken, PcdOperationType, CompareDataValue, Address, Value) \
  GnbEntryPcdWr, RegisterSpaceType, _DATA32 (PcdToken), PcdOperationType, _DATA32(CompareDataValue), _DATA32 (Address), _DATA32 (Value)

#define GNB_ENTRY_PCD_VAL_WR(RegisterSpaceType, PcdToken, Address) \
  GNB_ENTRY_PCD_WR(RegisterSpaceType, PcdToken, TableBlastWriteValue, 0x00000000, Address, 0x00000000)

#define GNB_ENTRY_WR_IF_PCD_EQUAL(RegisterSpaceType, PcdToken, CompareDataValue, Address, Value) \
  GNB_ENTRY_PCD_WR(RegisterSpaceType, PcdToken, TableBlastWriteIfValEqual, CompareDataValue, Address, Value)

#define GNB_ENTRY_WR_IF_PCD_NOT_EQUAL(RegisterSpaceType, PcdToken, CompareDataValue, Address, Value) \
  GNB_ENTRY_PCD_WR(RegisterSpaceType, PcdToken, TableBlastWriteIfValNotEqual, CompareDataValue, Address, Value)

typedef struct {
  ENTRY_HEAD  Head;           ///< Structure descriptor
  UINT32      Token;          ///< Local PCD Token value
  UINT8       PcdType;        ///< Pcd Type as listed in above enum GNB_TABLE_PCD_OPERATION_TYPE
  UINT32      CompareValue;   ///< Compare data associated with the operation, if applicable
  UINT32      Address;        ///< Register address
  UINT32      Value;          ///< Value
} GNB_TABLE_ENTRY_PCD_WR;
///
/// Write register entry based off of PCD : end
///

///
/// Read/Modify/Write register entry based off of PCD : start
///
#define GNB_ENTRY_PCD_RMW(RegisterSpaceType, PcdToken, PcdOperationType, CompareDataValue, Address, AndMask, OrMask ) \
  GnbEntryPcdRmw, RegisterSpaceType, _DATA32 (PcdToken), PcdOperationType, _DATA32(CompareDataValue), _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

#define GNB_ENTRY_RMW_IF_PCD_EQUAL(RegisterSpaceType, PcdToken, CompareDataValue, Address, AndMask, OrMask ) \
  GNB_ENTRY_PCD_RMW(RegisterSpaceType, PcdToken, TableBlastWriteIfValEqual, CompareDataValue, Address, AndMask, OrMask)

#define GNB_ENTRY_RMW_IF_PCD_NOT_EQUAL(RegisterSpaceType, PcdToken, CompareDataValue, Address, AndMask, OrMask ) \
  GNB_ENTRY_PCD_RMW(RegisterSpaceType, PcdToken, TableBlastWriteIfValNotEqual, CompareDataValue, Address, AndMask, OrMask)

typedef struct {
  ENTRY_HEAD      Head;           ///< Structure descriptor
  UINT32          Token;          ///< Local PCD Token value
  UINT8           PcdType;        ///< Pcd Type as listed in above enum GNB_TABLE_PCD_OPERATION_TYPE
  UINT32          CompareValue;   ///< Compare data associated with the operation, if applicable
  GNB_RMW_BLOCK   Data;           ///< Data for RMW operation
} GNB_TABLE_ENTRY_PCD_RMW;
///
/// Read/Modify/Write register entry based off of PCD : end
///


#define GNB_ENTRY_PROPERTY_RMW(Property,  RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryPropertyRmw, RegisterSpaceType, _DATA32 (Property), _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

/// Read Modify Write register entry
typedef struct {
  ENTRY_HEAD      Head;           ///< Structure descriptor
  UINT32          Property;       ///< Property
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_PROPERTY_RMW;


#define GNB_ENTRY_STALL(Microsecond) \
  GnbEntryStall, _DATA32 (Microsecond)

/// Stall amount entry
typedef struct {
  UINT8   EntryType;               ///< Entry type
  UINT32  Microsecond;             ///< Value
} GNB_TABLE_ENTRY_STALL;

#define GNB_ENTRY_TERMINATE GnbEntryTerminate

AGESA_STATUS
GnbBlastTable (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GNB_TABLE             *Table,
  IN      UINT32                Property,
  IN      UINT32                Flags,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  );

#pragma pack (pop)

#endif /* _NBIOTABLEBLAST_H_ */

