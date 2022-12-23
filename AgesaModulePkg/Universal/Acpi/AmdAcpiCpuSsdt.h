/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SSDT.
 *
 * Contains implementation of the interfaces: Generate SSDT in AmdAcpiCpuSsdt.h. *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Universal
 * @e \$Revision$   @e \$Date$
 *
 */
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
 */
#ifndef _AMD_ACPI_CPU_SSDT_H_
#define _AMD_ACPI_CPU_SSDT_H_
#include "Protocol/AcpiTable.h"
#pragma pack (push, 1)

//----------------------------------------------------------------------------
//                         ACPI P-States AML TYPEDEFS, STRUCTURES, ENUMS
//
//----------------------------------------------------------------------------

//--------------------------------------------
//              AML code definition
//                   (Scope)
//---------------------------------------------
/// SCOPE
typedef struct _SCOPE {
  UINT8   ScopeOpcode;                  ///< Opcode
  UINT16  ScopeLength;                  ///< Scope Length
  UINT8   ScopeValue1;                  ///< Value1
  UINT8   ScopeValue2;                  ///< Value2
  UINT8   ScopeNamePt1a__;              ///< Name Pointer
  UINT8   ScopeNamePt1a_P;              ///< Name Pointer
  UINT8   ScopeNamePt1a_R;              ///< Name Pointer
  UINT8   ScopeNamePt1b__;              ///< Name Pointer
  UINT8   ScopeNamePt2a_C;              ///< Name Pointer
  UINT8   ScopeNamePt2a_P;              ///< Name Pointer
  UINT8   ScopeNamePt2a_U;              ///< Name Pointer
  UINT8   ScopeNamePt2a_0;              ///< Name Pointer
} SCOPE;
#define   SCOPE_STRUCT_SIZE sizeof (SCOPE) // 13 Bytes

//--------------------------------------------
//              AML code definition
//             (PCT Header and Body)
//---------------------------------------------

///Performance Control Header
typedef struct _PCT_HEADER_BODY {
  UINT8   NameOpcode;                   ///< Opcode
  UINT8   PctName_a__;                  ///< String "_"
  UINT8   PctName_a_P;                  ///< String "P"
  UINT8   PctName_a_C;                  ///< String "C"
  UINT8   PctName_a_T;                  ///< String "T"
  UINT32  Value1;                       ///< Value1
  UINT16  Value2;                       ///< Value2
  UINT8   Value3;                       ///< Value3
  UINT8   GenericRegDescription1;       ///< Generic Reg Description
  UINT16  Length1;                      ///< Length1
  UINT8   AddressSpaceId1;              ///< PCT Address Space ID
  UINT8   RegisterBitWidth1;            ///< PCT Register Bit Width
  UINT8   RegisterBitOffset1;           ///< PCT Register Bit Offset
  UINT8   Reserved1;                    ///< Reserved
  UINT32  ControlRegAddressLo;          ///< Control Register Address Low
  UINT32  ControlRegAddressHi;          ///< Control Register Address High
  UINT32  Value4;                       ///< Value4
  UINT16  Value5;                       ///< Value 5
  UINT8   GenericRegDescription2;       ///< Generic Reg Description
  UINT16  Length2;                      ///< Length2
  UINT8   AddressSpaceId2;              ///< PCT Address Space ID
  UINT8   RegisterBitWidth2;            ///< PCT Register Bit Width
  UINT8   RegisterBitOffset2;           ///< PCT Register Bit Offset
  UINT8   Reserved2;                    ///< Reserved
  UINT32  StatusRegAddressLo;           ///< Control Register Address Low
  UINT32  StatusRegAddressHi;           ///< Control Register Address High
  UINT16  Value6;                       ///< Values
} PCT_HEADER_BODY;
#define   PCT_STRUCT_SIZE sizeof (PCT_HEADER_BODY) // 50 Bytes


//--------------------------------------------
//              AML code definition
//                 (PSS Header)
//--------------------------------------------
///Performance Supported States Header
typedef struct  _PSS_HEADER {
  UINT8   NameOpcode;                   ///< Opcode
  UINT8   PssName_a__;                  ///< String "_"
  UINT8   PssName_a_P;                  ///< String "P"
  UINT8   PssName_a_S;                  ///< String "S"
  UINT8   PssName_b_S;                  ///< String "S"
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT16  PssLength;                    ///< PSS Length
  UINT8   NumOfItemsInPss;              ///< Number of Items in PSS
} PSS_HEADER;
#define   PSS_HEADER_STRUCT_SIZE  sizeof (PSS_HEADER) // 9 Bytes


//--------------------------------------------
//              AML code definition
//                 (PSS Body)
//--------------------------------------------
///Performance Supported States Body
typedef struct _PSS_BODY {
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT8   PkgLength;                    ///< Package Length
  UINT8   NumOfElements;                ///< Number of Elements
  UINT8   DwordPrefixOpcode1;           ///< Prefix Opcode1
  UINT32  Frequency;                    ///< Frequency
  UINT8   DwordPrefixOpcode2;           ///< Prefix Opcode2
  UINT32  Power;                        ///< Power
  UINT8   DwordPrefixOpcode3;           ///< Prefix Opcode3
  UINT32  TransitionLatency;            ///< Transition Latency
  UINT8   DwordPrefixOpcode4;           ///< Prefix Opcode4
  UINT32  BusMasterLatency;             ///< Bus Master Latency
  UINT8   DwordPrefixOpcode5;           ///< Prefix Opcode5
  UINT32  Control;                      ///< Control
  UINT8   DwordPrefixOpcode6;           ///< Prefix Opcode6
  UINT32  Status;                       ///< Status
} PSS_BODY;
#define   PSS_BODY_STRUCT_SIZE sizeof (PSS_BODY) // 33 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (XPSS Header)
 *--------------------------------------------
 */
/// Extended PSS Header
typedef struct  _XPSS_HEADER {
  UINT8   NameOpcode;                   ///< 08h
  UINT8   XpssName_a_X;                 ///< String "X"
  UINT8   XpssName_a_P;                 ///< String "P"
  UINT8   XpssName_a_S;                 ///< String "S"
  UINT8   XpssName_b_S;                 ///< String "S"
  UINT8   PkgOpcode;                    ///< 12h
  UINT16  XpssLength;                   ///< XPSS Length
  UINT8   NumOfItemsInXpss;             ///< Number of Items in XPSS
} XPSS_HEADER;
#define   XPSS_HEADER_STRUCT_SIZE sizeof (XPSS_HEADER)  // 9 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (XPSS Body)
 *--------------------------------------------
 */
/// Extended PSS Body
typedef struct  _XPSS_BODY {
  UINT8   PkgOpcode;                    ///< 12h
  UINT8   PkgLength;                    ///< Package Length
  UINT8   XpssValueTbd;                 ///< XPSS Value
  UINT8   NumOfElements;                ///< Number of Elements
  UINT8   DwordPrefixOpcode1;           ///< Prefix Opcode1
  UINT32  Frequency;                    ///< Frequency
  UINT8   DwordPrefixOpcode2;           ///< Prefix Opcode2
  UINT32  Power;                        ///< Power
  UINT8   DwordPrefixOpcode3;           ///< Prefix Opcode3
  UINT32  TransitionLatency;            ///< Transition Latency
  UINT8   DwordPrefixOpcode4;           ///< Prefix Opcode4
  UINT32  BusMasterLatency;             ///< Bus Master Latency
  UINT32  ControlBuffer;                ///< Control Buffer
  UINT32  ControlLo;                    ///< Control Low
  UINT32  ControlHi;                    ///< Control High
  UINT32  StatusBuffer;                 ///< Status Buffer
  UINT32  StatusLo;                     ///< Status Low
  UINT32  StatusHi;                     ///< Status High
  UINT32  ControlMaskBuffer;            ///< Control Mask Buffer
  UINT32  ControlMaskLo;                ///< Control Mask Low
  UINT32  ControlMaskHi;                ///< Control Mask High
  UINT32  StatusMaskBuffer;             ///< Status Mask Buffer
  UINT32  StatusMaskLo;                 ///< Status Mask Low
  UINT32  StatusMaskHi;                 ///< Status Mask High
} XPSS_BODY;
#define   XPSS_BODY_STRUCT_SIZE sizeof (XPSS_BODY) // 72 Bytes

// Generic Register Descriptor (GDR) Fields
#define     GDR_ASI_SYSTEM_MEM      0x00    // Address Space ID
#define     GDR_ASI_SYSTEM_IO       0x01    // Address Space ID
#define     GDR_ASI_FIXED_HW        0x7F    // Address Space ID
#define     GDR_ASZ_UNDEFINED       0x00    // Address Size
#define     GDR_ASZ_BYTE_ACCESS     0x01    // Address Size

// Defines for ACPI Scope Table
// ----------------------------
#define     SCOPE_LENGTH    (SCOPE_STRUCT_SIZE + \
                            PCT_STRUCT_SIZE + \
                            PSS_HEADER_STRUCT_SIZE + \
                            PSS_BODY_STRUCT_SIZE + \
                            PPC_HEADER_BODY_STRUCT_SIZE)
#define     SCOPE_VALUE1    0x5C
#define     SCOPE_VALUE2    0x2E
#define     SCOPE_NAME__    '_'
#define     SCOPE_NAME_P    'P'
#define     SCOPE_NAME_R    'R'
#define     SCOPE_NAME_S    'S'
#define     SCOPE_NAME_B    'B'
#define     SCOPE_NAME_C    'C'
#define     SCOPE_NAME_U    'U'
#define     SCOPE_NAME_0    '0'
#define     SCOPE_NAME_1    '1'
#define     SCOPE_NAME_2    '2'
#define     SCOPE_NAME_3    '3'
#define     SCOPE_NAME_A    'A'

// Defines for PCT Control and Status Table
// ----------------------------------------
#define     PCT_NAME__                  '_'
#define     PCT_NAME_P                  'P'
#define     PCT_NAME_C                  'C'
#define     PCT_NAME_T                  'T'
#define     PCT_VALUE1                  0x11022C12ul
#define     PCT_VALUE2                  0x0A14
#define     PCT_VALUE3                  0x11
#define     GENERIC_REG_DESCRIPTION     0x82
#define     PCT_LENGTH                  0x0C
#define     PCT_ADDRESS_SPACE_ID        0x7F
#define     PCT_REGISTER_BIT_WIDTH      0x40
#define     PCT_REGISTER_BIT_OFFSET     0x00
#define     PCT_RESERVED                0x00
#define     PCT_CONTROL_REG_LO          0xC0010062ul
#define     PCT_CONTROL_REG_HI          0x00
#define     PCT_VALUE4                  0x14110079ul
#define     PCT_VALUE5                  0x110A
#define     PCT_STATUS_REG_LO           0x00
#define     PCT_STATUS_REG_HI           0x00
#define     PCT_VALUE6                  0x0079


// Defines for PSS Header Table
// ----------------------------
#define     PSS_NAME__                  '_'
#define     PSS_NAME_X                  'X'
#define     PSS_NAME_P                  'P'
#define     PSS_NAME_S                  'S'
#define     PSS_LENGTH                  (sizeof pssBodyStruct + 3)


// Defines for PSS Header Table
// ----------------------------
#define     PSS_PKG_LENGTH              0x20  // PSS_BODY_STRUCT_SIZE - 1
#define     PSS_NUM_OF_ELEMENTS         0x06

// Defines for XPSS Header Table
// ----------------------------
#define     XPSS_PKG_LENGTH             0x47  // XPSS_BODY_STRUCT_SIZE - 1
#define     XPSS_NUM_OF_ELEMENTS        0x08


// Defines for PPC Header Table
// ----------------------------
#define     PPC_NAME__                  '_'
#define     PPC_NAME_P                  'P'
#define     PPC_NAME_C                  'C'
#define     PPC_NAME_V                  'V'
#define     PPC_METHOD_FLAGS            0x00;
#define     PPC_VALUE1                  0x0A;

// Defines for PSD Header Table
// ----------------------------
#define     PSD_NAME__                  '_'
#define     PSD_NAME_P                  'P'
#define     PSD_NAME_S                  'S'
#define     PSD_NAME_D                  'D'
#define     PSD_HEADER_LENGTH           (PSD_BODY_STRUCT_SIZE + 2)
#define     PSD_VALUE1                  0x01


// Defines for PSD Header Table
// ----------------------------
#define     PSD_PKG_LENGTH                   (PSD_BODY_STRUCT_SIZE - 1)
#define     NUM_OF_ENTRIES                   0x05
#define     PSD_NUM_OF_ENTRIES               0x05
#define     PSD_REVISION                     0x00
#define     PSD_DEPENDENCY_DOMAIN            0x00
#define     PSD_COORDINATION_TYPE_HW_ALL     0xFE
#define     PSD_COORDINATION_TYPE_SW_ANY     0xFD
#define     PSD_COORDINATION_TYPE_SW_ALL     0xFC

#define     CUSTOM_PSTATE_FLAG          0x55
#define     PSTATE_FLAG_1               0x55
#define     TARGET_PSTATE_FLAG          0xAA
#define     PSTATE_FLAG_2               0xAA

// Defines for ACPI C-State Objects
// ----------------------------
#define   CST_NAME__                        '_'
#define   CST_NAME_C                        'C'
#define   CST_NAME_S                        'S'
#define   CST_NAME_T                        'T'
#define   CST_HEADER_PKG_LENGTH              5
#define   CST_HEADER_PKG_LENGTH_ONE_BYTEDATA 0x40
#define   CST_LENGTH_NO_C1                   0x0247
#define   CST_LENGTH_WITH_C1                 0x0449
#define   CST_PKG_LENGTH                     (CST_BODY_SIZE - 1)
#define   CST_PKG_ELEMENTS                   0x04
#define   CST_SUBPKG_LENGTH                  0x14
#define   CST_SUBPKG_ELEMENTS                0x0A
#define   CST_GDR_LENGTH                     0x000C
#define   CST_C1_TYPE                        0x01
#define   CST_C2_TYPE                        0x02
#define   CST_C3_TYPE                        0x03

#define   CSD_NAME_D                     'D'
#define   CSD_COORD_TYPE_HW_ALL          0xFE

#define   LPI_NAME__                        '_'
#define   LPI_NAME_L                        'L'
#define   LPI_NAME_P                        'P'
#define   LPI_NAME_I                        'I'
#define   LPI_HEADER_PKG_LENGTH              0x1441
#define   LPI_HEADER_PKG_ELEMENTS            6
#define   LPI_BODY_PKG_LENGTH                0x0644
#define   LPI_BODY_PKG_ELEMENTS              10
#define   LPI_SUBPKG_LENGTH                  0x14
#define   LPI_SUBPKG_ELEMENTS                0x0A
#define   LPI_GDR_LENGTH                     0x000C


/*--------------------------------------------
 *              AML code definition
 *             (PPC Header and Body)
 *--------------------------------------------
 */
/// Performance Present Capabilities Header
typedef struct _PPC_HEADER_BODY {
  UINT8   NameOpcode;                   ///< Name Opcode
  UINT8   PpcName_a_P;                  ///< String "P"
  UINT8   PpcName_b_P;                  ///< String "P"
  UINT8   PpcName_a_C;                  ///< String "C"
  UINT8   PpcName_a_V;                  ///< String "V"
  UINT8   Value1;                       ///< Value
  UINT8   DefaultPerfPresentCap;        ///< Default Perf Present Cap
  UINT8   MethodOpcode;                 ///< Method Opcode
  UINT8   PpcLength;                    ///< Method Length
  UINT8   PpcName_a__;                  ///< String "_"
  UINT8   PpcName_c_P;                  ///< String "P"
  UINT8   PpcName_d_P;                  ///< String "P"
  UINT8   PpcName_b_C;                  ///< String "C"
  UINT8   MethodFlags;                  ///< Method Flags
  UINT8   ReturnOpcode;                 ///< Return Opcoce
  UINT8   PpcName_e_P;                  ///< String "P"
  UINT8   PpcName_f_P;                  ///< String "P"
  UINT8   PpcName_c_C;                  ///< String "C"
  UINT8   PpcName_b_V;                  ///< String "V"

} PPC_HEADER_BODY;
#define   PPC_HEADER_BODY_STRUCT_SIZE sizeof (PPC_HEADER_BODY) // 19 Bytes
#define   PPC_METHOD_LENGTH             11 // 11 Bytes


/*--------------------------------------------
 *              AML code definition
 *                (PSD Header)
 *--------------------------------------------
 */
/// P-State Dependency Header
typedef struct  _PSD_HEADER {
  UINT8   NameOpcode;                   ///< Name Opcode
  UINT8   PsdName_a__;                  ///< String "_"
  UINT8   PsdName_a_P;                  ///< String "P"
  UINT8   PsdName_a_S;                  ///< String "S"
  UINT8   PsdName_a_D;                  ///< String "D"
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT8   PsdLength;                    ///< PSD Length
  UINT8   Value1;                       ///< Value
} PSD_HEADER;
#define   PSD_HEADER_STRUCT_SIZE sizeof (PSD_HEADER) // 8 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (PSD Body)
 *--------------------------------------------
 */
/// P-State Dependency Body
typedef struct _PSD_BODY {
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT8   PkgLength;                    ///< Package Length
  UINT8   NumOfEntries;                 ///< Number of Entries
  UINT8   BytePrefixOpcode1;            ///< Prefix Opcode1 in Byte
  UINT8   PsdNumOfEntries;              ///< PSD Number of Entries
  UINT8   BytePrefixOpcode2;            ///< Prefix Opcode2 in Byte
  UINT8   PsdRevision;                  ///< PSD Revision
  UINT8   DwordPrefixOpcode1;           ///< Prefix Opcode1 in DWord
  UINT32  DependencyDomain;             ///< Dependency Domain
  UINT8   DwordPrefixOpcode2;           ///< Prefix Opcode2 in DWord
  UINT32  CoordinationType;             ///< (0xFC = SW_ALL, 0xFD = SW_ANY, 0xFE = HW_ALL)
  UINT8   DwordPrefixOpcode3;           ///< Prefix Opcode3 in DWord
  UINT32  NumOfProcessors;              ///< Number of Processors
} PSD_BODY;
#define   PSD_BODY_STRUCT_SIZE sizeof (PSD_BODY) // 22 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (CST HEADER)
 *--------------------------------------------
 */
/// CST Header
typedef struct _CST_HEADER_STRUCT {
  UINT8   NameOpcode;                   ///< Name Opcode
  UINT8   CstName_a__;                  ///< String "_"
  UINT8   CstName_a_C;                  ///< String "C"
  UINT8   CstName_a_S;                  ///< String "S"
  UINT8   CstName_a_T;                  ///< String "T"
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT16  PkgLength;                    ///< Package Length
  UINT8   PkgElements;                  ///< Number of Elements
  UINT8   BytePrefix;                   ///< Byte Prefix Opcode
  UINT8   Count;                        ///< Number of Cstate info packages
} CST_HEADER_STRUCT;
#define   CST_HEADER_SIZE sizeof (CST_HEADER_STRUCT) // 11 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (CST Body)
 *--------------------------------------------
 */
/// CST Body
typedef struct _CST_BODY_STRUCT {
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT8   PkgLength;                    ///< Package Length
  UINT8   PkgElements;                  ///< Number of Elements
  UINT8   BufferOpcode;                 ///< Buffer Opcode
  UINT8   BufferLength;                 ///< Buffer Length
  UINT8   BufferElements;               ///< Number of Elements
  UINT8   BufferOpcode2;                ///< Buffer Opcode
  UINT8   GdrOpcode;                    ///< Generic Register Descriptor Opcode
  UINT16  GdrLength;                    ///< Descriptor Length
  UINT8   AddrSpaceId;                  ///< Address Space ID
  UINT8   RegBitWidth;                  ///< Register Bit Width
  UINT8   RegBitOffset;                 ///< Register Bit Offset
  UINT8   AddressSize;                  ///< Address Size
  UINT64  RegisterAddr;                 ///< Register Address
  UINT16  EndTag;                       ///< End Tag Descriptor
  UINT8   BytePrefix;                   ///< Byte Prefix Opcode
  UINT8   Type;                         ///< Type
  UINT8   WordPrefix;                   ///< Word Prefix Opcode
  UINT16  Latency;                      ///< Latency
  UINT8   DWordPrefix;                  ///< Dword Prefix Opcode
  UINT32  Power;                        ///< Power
} CST_BODY_STRUCT;
#define   CST_BODY_SIZE sizeof (CST_BODY_STRUCT) // 34 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (LPI HEADER)
 *--------------------------------------------
 */
/// LPI Header
typedef struct _LPI_HEADER_STRUCT {
  UINT8   NameOpcode;                   ///< Name Opcode
  UINT8   LpiName_a__;                  ///< String "_"
  UINT8   LpiName_a_L;                  ///< String "L"
  UINT8   LpiName_a_P;                  ///< String "P"
  UINT8   LpiName_a_I;                  ///< String "I"
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT16  PkgLength;                    ///< Package Length
  UINT8   PkgElements;                  ///< Number of Elements
  UINT8   WordPrefix;                   ///< Word Prefix Opcode
  UINT16  Revision;                     ///< Revision
  UINT8   QWordPrefix;                  ///< QWord Prefix Opcode
  UINT64  LevelID;                      ///< Level ID
  UINT8   WordPrefix2;                  ///< Word Prefix Opcode
  UINT16  Count;                        ///< Number of Cstate info packages
} LPI_HEADER_STRUCT;
#define   LPI_HEADER_SIZE sizeof (LPI_HEADER_STRUCT) // 11 Bytes

/*--------------------------------------------
 *              AML code definition
 *           (Resource Descriptor Body)
 *--------------------------------------------
 */
typedef struct _RESOURCE_DESCRIPTOR {
  UINT8   BufferOpcode;                 ///< Buffer Opcode
  UINT8   BufferLength;                 ///< Buffer Length
  UINT8   BufferElements;               ///< Number of Elements
  UINT8   BufferOpcode2;                ///< Buffer Opcode
  UINT8   GdrOpcode;                    ///< Generic Register Descriptor Opcode
  UINT16  GdrLength;                    ///< Descriptor Length
  UINT8   AddrSpaceId;                  ///< Address Space ID
  UINT8   RegBitWidth;                  ///< Register Bit Width
  UINT8   RegBitOffset;                 ///< Register Bit Offset
  UINT8   AddressSize;                  ///< Address Size
  UINT64  RegisterAddr;                 ///< Register Address
  UINT16  EndTag;                       ///< End Tag Descriptor
} RESOURCE_DESCRIPTOR;

/*--------------------------------------------
 *              AML code definition
 *                 (LPI Body)
 *--------------------------------------------
 */
/// LPI Body
typedef struct _LPI_BODY_STRUCT {
  UINT8   PkgOpcode;                    ///< Package Opcode
  UINT16  PkgLength;                    ///< Package Length
  UINT8   PkgElements;                  ///< Number of Elements
  UINT8   DWordPrefix;                  ///< Dword Prefix Opcode
  UINT32  MinResidency;                 ///< Minimum Residency
  UINT8   DWordPrefix2;                 ///< Dword Prefix Opcode
  UINT32  WorstCaseWakeupLatency;       ///< Worst Case Wakeup Latency
  UINT8   DWordPrefix3;                 ///< Dword Prefix Opcode
  UINT32  Flags;                        ///< Flags
  UINT8   DWordPrefix4;                 ///< Dword Prefix Opcode
  UINT32  ArchContextLostFlags;         ///< Arch.  Context Lost Flags
  UINT8   DWordPrefix5;                 ///< Dword Prefix Opcode
  UINT32  ResidencyCounterFrequency;    ///< Residency Counter Frequency
  UINT8   DWordPrefix6;                 ///< Dword Prefix Opcode
  UINT32  EnabledParentState;           ///< Enabled Parent State
  RESOURCE_DESCRIPTOR  EntryMethod;     ///< Entry Method
  RESOURCE_DESCRIPTOR  ResidencyCounterRegister;  ///< Residency Counter Register
  RESOURCE_DESCRIPTOR  UsageCounterRegister;  ///< Update Counter Register
  UINT8   StringPrefix;                 ///< String Prefix Opcode
  UINT8   StateName0;                   ///< First char ('C')
  UINT8   StateName1;                   ///< Second char ('x')
  UINT8   StateNameNull;                ///< ASCIIZ terminator (NULL)
} LPI_BODY_STRUCT;
#define   LPI_BODY_SIZE sizeof (LPI_BODY_STRUCT) // 34 Bytes

/*--------------------------------------------
 *              AML code definition
 *                    (LPI)
 *--------------------------------------------
 */
/// LPI complete structure
typedef struct _LPI_STRUCT {
  LPI_HEADER_STRUCT  Header;            ///< Header
  LPI_BODY_STRUCT    C1;                ///< C1 State
  LPI_BODY_STRUCT    C2;                ///< C2 State
  LPI_BODY_STRUCT    C3;                ///< C3 State
} LPI_STRUCT;
#define   LPI_SIZE sizeof (LPI_STRUCT)

/*--------------------------------------------
 *              AML code definition
 *                 (CSD HEADER)
 *--------------------------------------------
 */
/// CSD Header
typedef struct _CSD_HEADER_STRUCT {
  UINT8   NameOpcode;                  ///< Name Opcode
  UINT8   CsdName_a__;                 ///< String "_"
  UINT8   CsdName_a_C;                 ///< String "C"
  UINT8   CsdName_a_S;                 ///< String "S"
  UINT8   CsdName_a_D;                 ///< String "D"
} CSD_HEADER_STRUCT;
#define   CSD_HEADER_SIZE sizeof (CSD_HEADER_STRUCT) // 5 Bytes

/*--------------------------------------------
 *              AML code definition
 *                 (CSD Body)
 *--------------------------------------------
 */
/// CSD Body
typedef struct _CSD_BODY_STRUCT {
  UINT8   PkgOpcode;                   ///< Package Opcode
  UINT8   PkgLength;                   ///< Package Length
  UINT8   PkgElements;                 ///< Number of Elements
  UINT8   PkgOpcode2;                  ///< Package Opcode
  UINT8   PkgLength2;                  ///< Package Length
  UINT8   PkgElements2;                ///< Number of Elements
  UINT8   BytePrefix;                  ///< Byte Prefix Opcode
  UINT8   NumEntries;                  ///< Number of Entries
  UINT8   BytePrefix2;                 ///< Byte Prefix Opcode
  UINT8   Revision;                    ///< Revision
  UINT8   DWordPrefix;                 ///< DWord Prefix Opcode
  UINT32  Domain;                      ///< Dependency Domain Number
  UINT8   DWordPrefix2;                ///< DWord Prefix Opcode
  UINT32  CoordType;                   ///< Coordination Type
  UINT8   DWordPrefix3;                ///< Dword Prefix Opcode
  UINT32  NumProcessors;               ///< Number of Processors in the Domain
  UINT8   DWordPrefix4;                ///< Dword Prefix Opcode
  UINT32  Index;                       ///< Index of C-State entry for which dependency applies
} CSD_BODY_STRUCT;
#define   CSD_BODY_SIZE sizeof (CSD_BODY_STRUCT) // 30 Bytes

AGESA_STATUS
AmdAcpiCpuSSdt (
  IN       EFI_ACPI_TABLE_PROTOCOL  *AcpiTableProtocol,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );


/*
  PCD defintions
*/
/// PcdAmdAcpiC3Ctrl
#define PCD_AMD_ACPI_C3_CTRL_VAL_DISABLED   0
#define PCD_AMD_ACPI_C3_CTRL_VAL_CST        1
#define PCD_AMD_ACPI_C3_CTRL_VAL_LPI        2

#pragma pack (pop)
#endif // _AMD_ACPI_CPU_SSDT_H_

