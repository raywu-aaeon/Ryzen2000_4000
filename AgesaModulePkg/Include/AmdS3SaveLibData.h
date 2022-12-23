/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD S3 save library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 312770 $   @e \$Date: 2015-02-11 13:24:42 +0800 (Wed, 11 Feb 2015) $
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
 **/
#ifndef _AMD_S3SAVE_LIB_DATA_H_
#define _AMD_S3SAVE_LIB_DATA_H_

/// Define the Private Data structure used by AmdS3SaveDxeLib
typedef struct _AMD_S3LIB_PRIVATE_DATA {
  BOOLEAN   S3ScriptLock;     ///< S3Script Lock or Not for Non SMM driver
  BOOLEAN   CloseTable;       ///< TRUE AmdS3SaveLib is collecting the S3 script data, FALSE stop collect the data
  UINT8     *TableBase;       ///< Table used to collect the S3 Script DATA after SmmLock
} AMD_S3_LIB_PRIVATE_DATA;

#define AMD_S3LIB_BOOT_SCRIPT_TABLE_SIG SIGNATURE_32 ('A', 'S', '3', 'T')
#define AMD_S3LIB_BOOT_SCRIPT_TABLE_VER_1 0x1ul
#define AMD_S3LIB_BUFFER_INIT_SIZE  (1024 * 16)
#define AMD_S3LIB_BUFFER_INC_SIZE  (1024 * 1)
#define AMD_S3LIB_TABLE_END        (0xFFFF)
#define AMD_S3LIB_TABLE_END_SIZE   sizeof (UINT16)
#define AMD_S3LIB_TABLE_WATCHER    (0x01558844ul)
#define AMD_S3LIB_TABLE_WATCHER_SIZE   sizeof (UINT32)

/// S3 Boot Script table Header
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_TABLE_HEADER {
  UINT32  Sinature;         ///< Sinature
  UINT32  Version;          ///< Version
  UINT8   Reserved [24];    ///< Reserved
  UINTN   TableLength;      ///< Allocated memory length
  UINTN   NextDataOffset;   ///< Offset to next data
  UINT8   Data;             ///< Data start
} AMD_S3_LIB_BOOT_SCRIPT_TABLE_HEADER;

/// S3 Lib script operator enumeration
typedef enum {
  AMD_S3LIB_BOOT_SCRIPT_IO_WRITE_OP = 0x0,    ///< IO write operator
  AMD_S3LIB_BOOT_SCRIPT_IO_RMW_OP,            ///< IO Read Write operator
  AMD_S3LIB_BOOT_SCRIPT_IO_POLL_OP,           ///< IO poll operator
  AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE_OP,         ///< Mem write operator
  AMD_S3LIB_BOOT_SCRIPT_MEM_RMW_OP,           ///< Mem Read Write operator
  AMD_S3LIB_BOOT_SCRIPT_MEM_POLL_OP,          ///< Mem poll operator
  AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE_OP,         ///< PCI write operator
  AMD_S3LIB_BOOT_SCRIPT_PCI_RMW_OP,           ///< PCI Read Write operator
  AMD_S3LIB_BOOT_SCRIPT_PCI_POLL_OP,          ///< PCI poll operator
  AMD_S3LIB_BOOT_SCRIPT_DISPATCH_OP,          ///< Dispatch operator
}  AMD_S3LIB_BOOT_SCRIPT_OP;

/// Amd S3 Lib Boot script common structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_COMMON{
  UINT16                    OpCode;           ///< operator
} AMD_S3LIB_BOOT_SCRIPT_COMMON;

/// Amd S3 Lib Boot script IO write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_IO_WRITE {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Value;            ///< Value
} AMD_S3LIB_BOOT_SCRIPT_IO_WRITE;

/// Amd S3 Lib Boot script IO read write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_IO_RMW {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
} AMD_S3LIB_BOOT_SCRIPT_IO_RMW;

/// Amd S3 Lib Boot script IO poll structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_IO_POLL {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
  UINT64                    Delay;            ///< Delay
} AMD_S3LIB_BOOT_SCRIPT_IO_POLL;

/// Amd S3 Lib Boot script Memory write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Value;            ///< Value
} AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE;

/// Amd S3 Lib Boot script Memory read write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_MEM_RMW {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
} AMD_S3LIB_BOOT_SCRIPT_MEM_RMW;

/// Amd S3 Lib Boot script Memory poll structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_MEM_POLL {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
  UINTN                     LoopTimes;        ///< LoopTimes
} AMD_S3LIB_BOOT_SCRIPT_MEM_POLL;

/// Amd S3 Lib Boot script PCI write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT16                    Segment;          ///< PCI segment
  UINT64                    Address;          ///< Address
  UINT64                    Value;            ///< Value
} AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE;

/// Amd S3 Lib Boot script PCI read write structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_PCI_RMW {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT16                    Segment;          ///< PCI segment
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
} AMD_S3LIB_BOOT_SCRIPT_PCI_RMW;

/// Amd S3 Lib Boot script PCI POLL structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_PCI_POLL {
  UINT16                    OpCode;           ///< operator
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;            ///< Width
  UINT16                    Segment;          ///< PCI segment
  UINT64                    Address;          ///< Address
  UINT64                    Data;             ///< Data
  UINT64                    DataMask;         ///< DataMask
  UINT64                    Delay;            ///< Delay
} AMD_S3LIB_BOOT_SCRIPT_PCI_POLL;

/// Amd S3 Lib Boot script Dispatch structure
typedef struct  _AMD_S3LIB_BOOT_SCRIPT_DISPATCH {
  UINT16                    OpCode;           ///< operator
  VOID                      *EntryPoint;      ///< EntryPoint
  VOID                      *Context;         ///< Context
} AMD_S3LIB_BOOT_SCRIPT_DISPATCH;

/// Union structure of Amd S3 Lib script data
typedef union _AMD_S3LIB_BOOT_SCRIPT_DATA {
  AMD_S3LIB_BOOT_SCRIPT_COMMON Common;        ///< Common
  AMD_S3LIB_BOOT_SCRIPT_IO_WRITE IoWrite;     ///< IoWrite
  AMD_S3LIB_BOOT_SCRIPT_IO_RMW IoRMW;         ///< IoRMW
  AMD_S3LIB_BOOT_SCRIPT_IO_POLL IoPoll;       ///< IoPoll
  AMD_S3LIB_BOOT_SCRIPT_MEM_WRITE MemWrite;   ///< MemWrite
  AMD_S3LIB_BOOT_SCRIPT_MEM_RMW MemRMW;       ///< MemRMW
  AMD_S3LIB_BOOT_SCRIPT_MEM_POLL MemPoll;     ///< MemPoll
  AMD_S3LIB_BOOT_SCRIPT_PCI_WRITE PciWrite;   ///< PciWrite
  AMD_S3LIB_BOOT_SCRIPT_PCI_RMW PciRMW;       ///< PciRMW
  AMD_S3LIB_BOOT_SCRIPT_PCI_POLL PciPoll;     ///< PciPoll
  AMD_S3LIB_BOOT_SCRIPT_DISPATCH Dispatch;    ///< Dispatch
} AMD_S3LIB_BOOT_SCRIPT_DATA;

#endif //_AMD_S3SAVE_LIB_DATA_H_
