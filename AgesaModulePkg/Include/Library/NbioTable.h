/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to access PCI config space registers
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
#ifndef _NBIOTABLE_H_
#define _NBIOTABLE_H_

#include "GnbDxio.h"

#pragma pack (push, 1)

#define NBIO_TABLE_FLAGS_FORCE_S3_SAVE  0x00000001ul

typedef UINT8 GNB_TABLE;
typedef UINT8 NBIO_TABLE;

#define __DATA(x) x

#define _DATA32(Data) ((UINT32) (__DATA(Data))) & 0xFF, (((UINT32) (__DATA(Data))) >> 8) & 0xFF, (((UINT32) (__DATA(Data))) >> 16) & 0xFF, (((UINT32) (__DATA(Data))) >> 24) & 0xFF
#define _DATA64(Data) _DATA32(Data & 0xfffffffful) , _DATA32((UINT64) Data >> 32)

/// Entry type
typedef enum {
  GnbEntryWr,                     ///< Write register
  GnbEntryPropertyWr,             ///< Write register check property
  GnbEntryFullWr,                 ///< Write Rgister check revision and property
  GnbEntryRmw,                    ///< Read Modify Write register
  GnbEntryPropertyRmw,            ///< Read Modify Write register check property
  GnbEntryRevRmw,                 ///< Read Modify Write register check revision
  GnbEntryFullRmw,                ///< Read Modify Write register check revision and property
  GnbEntryPoll,                   ///< Poll register
  GnbEntryPropertyPoll,           ///< Poll register check property
  GnbEntryFullPoll,               ///< Poll register check property
  GnbEntryCopy,                   ///< Copy field from one register to another
  GnbEntryStall,                  ///< Copy field from one register to another
  GnbEntryTerminate = 0xFF        ///< Terminate table
} GNB_TABLE_ENTRY_TYPE;

#define GNB_ENTRY_WR(RegisterSpaceType, Address, Value) \
  GnbEntryWr, RegisterSpaceType, _DATA32 (Address), _DATA32 (Value)

/// Write register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  Value;                  ///< Value
} GNB_TABLE_ENTRY_WR;

#define GNB_ENTRY_PROPERTY_WR(Property, RegisterSpaceType, Address, Value) \
  GnbEntryPropertyWr, _DATA32 (Property), RegisterSpaceType, _DATA32 (Address), _DATA32 (Value)

/// Write register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT32  Property;               ///< Property
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  Value;                  ///< Value
} GNB_TABLE_ENTRY_PROPERTY_WR;


#define GNB_ENTRY_RMW(RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryRmw, RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

///Read Modify Write data Block
typedef struct {
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  AndMask;                ///< And Mask
  UINT32  OrMask;                 ///< Or Mask
} GNB_RMW_BLOCK;

/// Read Modify Write register entry
typedef struct {
  UINT8           EntryType;      ///< Entry type
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_RMW;

#define GNB_ENTRY_FULL_WR(Property, Revision, RegisterSpaceType, Address, Value) \
   GnbEntryFullWr, _DATA32 (Property), _DATA64 (Revision), RegisterSpaceType, _DATA32 (Address), _DATA32 (Value)

/// Write register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT32  Property;               ///< Property
  UINT64  Revision;               ///< Revision
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  Value;                  ///< Value
} GNB_TABLE_ENTRY_FULL_WR;


#define GNB_ENTRY_PROPERTY_RMW(Property,  RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryPropertyRmw, _DATA32 (Property), RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

/// Read Modify Write register entry
typedef struct {
  UINT8           EntryType;      ///< Entry type
  UINT32          Property;       ///< Property
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_PROPERTY_RMW;

#define GNB_ENTRY_REV_RMW(Rev,  RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryRevRmw, _DATA64 (Rev), RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

/// Read Modify Write register entry
typedef struct {
  UINT8           EntryType;      ///< Entry type
  UINT64          Revision;       ///< revision
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_REV_RMW;

#define GNB_ENTRY_FULL_RMW(Property, Revision, RegisterSpaceType, Address, AndMask, OrMask) \
  GnbEntryFullRmw, _DATA32 (Property), _DATA64 (Revision), RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (OrMask)

/// Read Modify Write register entry
typedef struct {
  UINT8           EntryType;      ///< Entry type
  UINT32          Property;       ///< Property
  UINT64          Revision;       ///< Revision
  GNB_RMW_BLOCK   Data;           ///< Data
} GNB_TABLE_ENTRY_FULL_RMW;

#define GNB_ENTRY_POLL(RegisterSpaceType, Address, AndMask, CompareValue) \
  GnbEntryPoll, RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (CompareValue)
/// Poll register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  AndMask;                ///< End mask
  UINT32  CompareValue;           ///< Compare value
} GNB_TABLE_ENTRY_POLL;

#define GNB_ENTRY_PROPERTY_POLL(Property, RegisterSpaceType, Address, AndMask, CompareValue) \
  GnbEntryPropertyPoll, _DATA32 (Property), RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (CompareValue)
/// Poll register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT32  Property;               ///< Property
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  AndMask;                ///< End mask
  UINT32  CompareValue;           ///< Compare value
} GNB_TABLE_ENTRY_PROPERTY_POLL;

#define GNB_ENTRY_FULL_POLL(Property, Revision, RegisterSpaceType, Address, AndMask, CompareValue) \
  GnbEntryFullPoll, _DATA32 (Property), _DATA64 (Revision), RegisterSpaceType, _DATA32 (Address), _DATA32 (AndMask), _DATA32 (CompareValue)
/// Poll register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT32  Property;               ///< Property
  UINT64  Revision;               ///< Revision
  UINT8   RegisterSpaceType;      ///< Register space
  UINT32  Address;                ///< Register address
  UINT32  AndMask;                ///< End mask
  UINT32  CompareValue;           ///< Compare value
} GNB_TABLE_ENTRY_FULL_POLL;

#define GNB_ENTRY_COPY(DestRegSpaceType, DestAddress, DestFieldOffset, DestFieldWidth, SrcRegisterSpaceType, SrcAddress, SrcFieldOffset, SrcFieldWidth) \
  GnbEntryCopy, DestRegSpaceType, _DATA32 (DestAddress), DestFieldOffset, DestFieldWidth, SrcRegisterSpaceType, _DATA32 (SrcAddress), SrcFieldOffset, SrcFieldWidth

/// Copy register entry
typedef struct {
  UINT8   EntryType;              ///< Entry type
  UINT8   DestRegisterSpaceType;  ///< Register space
  UINT32  DestAddress;            ///< Register address
  UINT8   DestFieldOffset;        ///< Field Offset
  UINT8   DestFieldWidth;         ///< Field Width
  UINT8   SrcRegisterSpaceType;   ///< Register space
  UINT32  SrcAddress;             ///< Register address
  UINT8   SrcFieldOffset;         ///< Field Offset
  UINT8   SrcFieldWidth;          ///< Field Width
} GNB_TABLE_ENTRY_COPY;

#define GNB_ENTRY_STALL(Microsecond) \
  GnbEntryStall, _DATA32 (Microsecond)

/// Write register entry
typedef struct {
  UINT8   EntryType;               ///< Entry type
  UINT32  Microsecond;             ///< Value
} GNB_TABLE_ENTRY_STALL;

#define GNB_ENTRY_TERMINATE GnbEntryTerminate

AGESA_STATUS
GnbProcessTable (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GNB_TABLE             *Table,
  IN      UINT32                Property,
  IN      UINT32                Flags,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  );

#pragma pack (pop)

#endif

