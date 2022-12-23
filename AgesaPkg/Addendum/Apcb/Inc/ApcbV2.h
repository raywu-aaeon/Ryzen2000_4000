/* $NoKeywords:$ */
/**
 * @file
 *
 * ApcbV2.h
 *
 * AGESA PSP Customization Block Data Definition
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: ApcbToolV2
 * @e \$Revision: $ @e \$Date: $
 *
 **/
/*****************************************************************************
*
* Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#ifndef _APCB_V2_H_
#define _APCB_V2_H_


#pragma pack(push, 1)

#define APCB_HEADER_VERSION_MAJOR   2
#define APCB_HEADER_VERSION_MINOR   0
//#define APCB_HEADER_VERSION         ((APCB_HEADER_VERSION_MAJOR << 4) | APCB_HEADER_VERSION_MINOR)
/*
//
// APCB Header Definition Version 2
//
typedef struct {
  UINT32  Signature;           // ASCII "APCB", 'A' is LSB
  UINT16  SizeOfHeader;        // Size of header
  UINT16  Version;             // Version, BCD. Version 1.2 is 0x12
  UINT32  SizeOfApcb;          // Size of APCB
  UINT32  UniqueApcbInstance;  // UniuweApcbInstance to ensure
                               // compatibitly for giveen flshed BIOS lifecycle
  UINT8   CheckSumByte;        // APCB Checksum Byte
  UINT8   Reserved1[3];        // Reserved
  UINT32  Reserved2[3];        // Reserved
} APCB_HEADER;


#define APCB_INDEX_HEADER_VERSION_MAJOR   0
#define APCB_INDEX_HEADER_VERSION_MINOR   1
#define APCB_INDEX_HEADER_VERSION         ((APCB_INDEX_HEADER_VERSION_MAJOR << 4) | APCB_INDEX_HEADER_VERSION_MINOR)
//
// APCB Index of Data Type Header Definition
//
typedef struct {
  UINT16  SizeOfHeader;     // Size of header
  UINT8   Version;          // Version, BCD. Version 1.2 is 0x12
  UINT8   Reserved;         // Reserved
  UINT32  SizeOfIndexData;  // Size of index data, absolute address in PSP
                            // NOTE: Will we support it to be relative address to starging address of APCB?
} APCB_INDEX_HEADER;

//
// APCB Index of Data Type  Definition
//
typedef struct {
  UINT16  GroupId;           // Group ID
  UINT16  TypeId;          // Type ID
  UINT32  Address;          // Data address
} APCB_TYPE_INDEX;

//
// APCB Data Type Header Definition
//
typedef struct {
  UINT16  GroupId;           // Group ID
  UINT16  TypeId;            // Type ID
  UINT16  SizeOfType;       // Size of type, in bytes
  UINT16  InstanceId;       // Instance ID
	UINT32	Reserved1;
	UINT32	Reserved2;
} APCB_TYPE_HEADER;

#define ALIGN_SIZE_OF_TYPE    4


#define APCB_GROUP_HEADER_VERSION_MAJOR   0
#define APCB_GROUP_HEADER_VERSION_MINOR   1
#define APCB_GROUP_HEADER_VERSION         ((APCB_GROUP_HEADER_VERSION_MAJOR << 4) | APCB_GROUP_HEADER_VERSION_MINOR)

#define INVALID_GROUP_ID    0xFFFF
#define UNKNOWN_GROUP_ID    0xFFFE

//
// APCB Data Group Header Definition
//
typedef struct {
  UINT32  Signature;        // ASCII Signature
  UINT16  GroupId;          // Group ID
  UINT16  SizeOfHeader;     // Size of header
  UINT16  Version;          // Version, BCD. Version 1.2 is 0x12
  UINT16  Reserved;      // Reserved
  UINT32  SizeOfGroup;      // Size of group
} APCB_GROUP_HEADER;

typedef struct {
  UINT32  Signature;        // ASCII Signature
  UINT16  GroupId;          // Group ID
} APCB_GROUP_ID_SIGN;

//
// APCB Layout Definition
//
typedef struct {
  APCB_HEADER          Header;
  APCB_INDEX_HEADER    Index;
  APCB_GROUP_HEADER    Group;
  APCB_TYPE_HEADER     Type;
  VOID                 *Data;
} APCB_LAYOUT;
*/
#pragma pack(pop)

#endif // _APCB_V2_H_

