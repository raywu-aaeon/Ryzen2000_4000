/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 4 7 16 17 19 20
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
#ifndef _UNIVERSAL_ACPI_AMD_ACPI_DXE_H_
#pragma pack (push, 1)

#define ACPI_TABLE_MAX_LENGTH           0x100000ul ///< Reserve 1M for ACPI table

// Defines for Common ACPI
// -----------------------------
#define     SCOPE_OPCODE                0x10
#define     NAME_OPCODE                 0x08
#define     METHOD_OPCODE               0x14
#define     PACKAGE_OPCODE              0x12
#define     BUFFER_OPCODE               0x11
#define     BYTE_PREFIX_OPCODE          0x0A
#define     WORD_PREFIX_OPCODE          0x0B
#define     DWORD_PREFIX_OPCODE         0x0C
#define     STRING_PREFIX_OPCODE        0x0D
#define     QWORD_PREFIX_OPCODE         0x0E
#define     RETURN_OPCODE               0xA4
#define     ACPI_BUFFER                 0x080A0B11ul

/// Format for Header
typedef struct {
  UINT8   Sign[4];                      ///< Signature
  UINT32  TableLength;                  ///< Table Length
  UINT8   Revision;                     ///< Revision
  UINT8   Checksum;                     ///< Checksum
  UINT8   OemId[6];                     ///< OEM ID
  UINT8   OemTableId[8];                ///< OEM Tabled ID
  UINT32  OemRev;                       ///< OEM Revision
  UINT8   CreatorId[4];                 ///< Creator ID
  UINT32  CreatorRev;                   ///< Creator Revision
} ACPI_TABLE_HEADER;

VOID
ChecksumAcpiTable (
  IN OUT   ACPI_TABLE_HEADER *Table,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

#pragma pack (pop)
#endif // _UNIVERSAL_ACPI_AMD_ACPI_DXE_H_

