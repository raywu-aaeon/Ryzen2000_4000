/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimmAcpi.h
 * 
 * 
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
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

/** @file JedecNvdimmAcpi.h
    Header file for JedecNvdimmAcpi Driver

**/

#ifndef _JEDEC_NVDIMM_ACPI_H_
#define _JEDEC_NVDIMM_ACPI_H_

#pragma pack (push, 1)

///< NFIT header
typedef struct {
  UINT8   Sign[4];                    ///< NFIT, Signature for the NVDIMM Firmware Interface Table
  UINT32  Length;                     ///< Length, in bytes, of the entire table
  UINT8   Revision;                   ///< 1
  UINT8   Checksum;                   ///< Entire table must sum to zero.
  UINT8   OemId[6];                   ///< OEM ID
  UINT8   OemTableId[8];              ///< OEM Tabled ID
  UINT32  OemRev;                     ///< OEM Revision
  UINT8   CreatorId[4];               ///< Creator ID
  UINT32  CreatorRev;                 ///< Creator Revision
  UINT32  Reserved;                   ///< Reserved
} NFIT_HEADER;

///< System Physical Address (SPA) Range Structure
///< Type 0
//#define EFI_MEMORY_UC               0x00000001
//#define EFI_MEMORY_WC               0x00000002
//#define EFI_MEMORY_WT               0x00000004
//#define EFI_MEMORY_WB               0x00000008
//#define EFI_MEMORY_UCE              0x00000010
//#define EFI_MEMORY_WP               0x00001000
//#define EFI_MEMORY_RP               0x00002000
//#define EFI_MEMORY_XP               0x00004000
//#define EFI_MEMORY_NV               0x00008000
//#define EFI_MEMORY_MORE_RELIABLE    0x00010000

typedef struct {
  UINT16  Type;                       ///< 0 - System Physical Address Range Structure
  UINT16  Length;                     ///< Length in bytes for entire structure
  UINT16  SpaRangeStructIndex;        ///< Used by NVDIMM Region Mapping Structure to uniquely refer to this structure.
  UINT16  Flags;                      ///< Flags
  UINT32  Reserved;                   ///< Reserved
  UINT32  ProximityDomain;            ///< This number must match with corresponding entry in the SRAT table
  EFI_GUID AddrRangeTypeGUID;         ///< GUID that defines the type of the Address Range Type
  UINT64  SpaRangeBase;               ///< Start Address of the System Physical Address Range
  UINT64  SpaRangeLength;             ///< Range Length of the region in bytes
  UINT64  AddrRangeMemMappingAttr;    ///< Memory mapping attributes for this address range
} SPA_RANGE_STRUCT;

///< NVDIMM Region Mapping Structure
///< Type 1
typedef struct {
  UINT16  Type;                       ///< 1 - NVDIMM Region Mapping Structure
  UINT16  Length;                     ///< Length in bytes for entire structure
  UINT32  NfitDeviceHandle;           ///< The _ADR of the NVDIMM device containing the NVDIMM region
  UINT16  NvdimmPhysicalId;           ///< Handle for the SMBIOS Type 17 structure describing the NVDIMM containing the NVDIMM region
  UINT16  NvdimmRegionId;             ///< Unique identifier for the NVDIMM region
  UINT16  SpaRangeStructIndex;        ///< The SPA range, if any, associated with the NVDIMM region
  UINT16  NvdimmCtrlRegionStructIndex;///< The index of the NVDIMM Control Region Structure for the NVDIMM region
  UINT64  NvdimmRegionSize;           ///< In bytes. The size of the NVDIMM region.
  UINT64  RegionOffset;               ///< In bytes. The Starting Offset for the NVDIMM region in the Interleave Set
  UINT64  NvdimmPhysicalAddrRegionBase;///< In bytes. The base physical address within the NVDIMM of the NVDIMM region
  UINT16  InterleaveStructIndex;      ///< The Interleave Structure, if any, for the NVDIMM region
  UINT16  InterleaveWay;              ///< Number of NVDIMMs in the interleave set
  UINT16  NvdimmStateFlags;           ///< NVDIMM state flags
  UINT16  Reserved;                   ///< Reserved
} REGION_MAPPING_STRUCT;

///< NVDIMM Control Region Structure
///< Type 4
typedef struct {
  UINT16  Type;                       ///< 4 - NVDIMM Control Region Structure
  UINT16  Length;                     ///< Length in bytes for entire structure
  UINT16  ControlRegionStructIndex;   ///< Index Number uniquely identifies the NVDIMM Control Region Structure
  UINT16  VendorId;                   ///< Byte 0 set to SPD byte 320 and byte 1 set to SPD byte 321
  UINT16  DeviceId;                   ///< Byte 0 set to SPD byte 192 and byte 1 set to SPD byte 193
  UINT16  RevisionId;                 ///< Byte 0 set to SPD byte 349 and byte 1 is reserved, set to 0
  UINT16  SubSysVendorId;             ///< Byte 0 set to SPD byte 194 and byte 1 set to SPD byte 195
  UINT16  SubSysDeviceId;             ///< Byte 0 set to SPD byte 196 and byte 1 set to SPD byte 197
  UINT16  SubSysRevisionId;           ///< Byte 0 set to SPD byte 198 and byte 1 is resreved, set to 0
  UINT8   ValidField;                 ///< 
  UINT8   ManufacturingLocation;      ///< Set to SPD byte 322
  UINT16  ManufacturingDate;          ///< Byte 0 set to SPD byte 323 and byte 1 set to SPD byte 324
  UINT16  Reserved;                   ///< Reserved
  UINT8   SerialNumber[4];            ///< Byte 0 - 3 set to SPD byte 325 - 328
  UINT16  RegionFormatInterfaceCode;  ///<
  UINT16  NumOfBlockCtrlWindow;       ///<
  UINT64  SizeOfBlockCtrlWindow;      ///<
  UINT64  CmdRegOffsetInBlockCtrlWindow;  ///<
  UINT64  SizeOfCmdRegInBlockCtrlWindow;  ///<
  UINT64  StatusRegOffsetInBlockCtrlWindow; ///<
  UINT64  SizeOfStatusRegInBlockCtrlWindow; ///<
  UINT16  CtrlRegionFlag;             ///<
  UINT8   Reserved1[6];
} CONTROL_REGION_STRUCT;

///< SMBIOS Management Information Structure
///< Type 3
typedef struct {
  UINT16 Type;
  UINT16 Length;
  UINT32 Reserved;
//  UINT8  Data[];
} SMBIOS_MGMT_INFO_STRUCT;

#pragma pack (pop)

#endif // _JEDEC_NVDIMM_ACPI_H_

