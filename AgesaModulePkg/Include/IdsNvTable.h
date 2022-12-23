/**
 * @file
 *
 * AMD Integrated Debug Hook Routines
 *
 * Contains all functions related to IDS Hook
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
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
#ifndef _AMD_IDS_NV_TABLE_H_
#define _AMD_IDS_NV_TABLE_H_

#pragma pack(push, 1)

#define IDS_NV_TABLE_SIGNATURE    0x564E4924ul      ///< $INV
#define IDS_NV_TABLE_REV_1        0x00000001ul
#define IDS_NV_TABLE_HEADER_REV1_DATA \
{\
    IDS_NV_TABLE_SIGNATURE, \
    IDS_NV_TABLE_REV_1, \
}
/// IDS NV table header
typedef struct _IDS_NV_TABLE_HEADER {
  UINT32 Signature;   ///< Signature
  UINT32 Revision;    ///< Revision
  UINT8  Reserved[24];    ///< Rsvd
} IDS_NV_TABLE_HEADER;

typedef UINT16 IDS_NV_ID;
#define IDS_NV_ATTRIB_SIZE_BYTE     0     ///< byte
#define IDS_NV_ATTRIB_SIZE_WORD     1     ///< word
#define IDS_NV_ATTRIB_SIZE_DWORD    2     ///< dword
#define IDS_NV_ATTRIB_SIZE_QWORD    3     ///< qword

/// IDS NV attribute
typedef struct _IDS_NV_ATTRIB {
  UINT8 size:2;   ///< Size of a NV record
  UINT8 reserved:6; ///< reserved
} IDS_NV_ATTRIB;

#define IDS_NV_ID_END  0xfffful
#define IDS_NV_VALUE_END 0xfffffffful
#define IDS_NV_RECORD_END \
{\
    IDS_NV_ID_END, \
    IDS_NV_VALUE_END\
}
/// IDS NV record generic
typedef struct  _IDS_NV_RECORD_CMN {
  IDS_NV_ID     Id;    ///< IDS NV ID
  IDS_NV_ATTRIB Attrib; ///< IDS NV Attribute
} IDS_NV_RECORD_CMN;

/// IDS NV record for 8 bits
typedef struct  IDS_NV_RECORD_U8 {
  IDS_NV_ID     Id;    ///< IDS NV ID
  IDS_NV_ATTRIB Attrib; ///< IDS NV Attribute
  UINT8         Value; ///< Value
} IDS_NV_RECORD_U8;

/// IDS NV record for 16 bits
typedef struct  IDS_NV_RECORD_U16 {
  IDS_NV_ID     Id;    ///< IDS NV ID
  IDS_NV_ATTRIB Attrib; ///< IDS NV Attribute
  UINT16        Value; ///< Value
} IDS_NV_RECORD_U16;

/// IDS NV record for 32 bits
typedef struct  _IDS_NV_RECORD_U32 {
  IDS_NV_ID     Id;    ///< IDS NV ID
  IDS_NV_ATTRIB Attrib; ///< IDS NV Attribute
  UINT32        Value; ///< Value
} IDS_NV_RECORD_U32;

/// IDS NV record for 64 bits
typedef struct  _IDS_NV_RECORD_U64 {
  IDS_NV_ID     Id;    ///< IDS NV ID
  IDS_NV_ATTRIB Attrib; ///< IDS NV Attribute
  UINT64        Value; ///< Value
} IDS_NV_RECORD_U64;

/// IDS NV table
typedef struct  _IDS_NV_TABLE {
  IDS_NV_TABLE_HEADER Header;   ///< Header
  UINT8         NvRecords;    ///< Data start
} IDS_NV_TABLE;

#pragma pack(pop)

#endif //#define _AMD_IDS_NV_TABLE_H_

