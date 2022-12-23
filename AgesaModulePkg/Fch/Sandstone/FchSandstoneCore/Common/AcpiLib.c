/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH ACPI lib
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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
*/
#include "FchPlatform.h"
#define FILECODE PROC_FCH_COMMON_ACPILIB_FILECODE
//
//
// Routine Description:
//
//  Locate ACPI table
//
// Arguments:
//
//  Signature - table signature
//
//Returns:
//
//  pointer to ACPI table
//
//
VOID*
AcpiLocateTable (
  IN  UINT32     Signature
  )
{
  UINT32              Index;
  UINT32              *RsdPtr;
  UINT32              *Rsdt;
  UINTN               TableOffset;
  DESCRIPTION_HEADER  *CurrentTable;

  RsdPtr = (UINT32*) (UINTN) FCHOEM_ACPI_TABLE_RANGE_LOW;
  Rsdt = NULL;
  do {
    if ( *RsdPtr == ' DSR' && *(RsdPtr + 1) == ' RTP' ) {
      Rsdt = (UINT32*) (UINTN) ((RSDP_HEADER*)RsdPtr)->RsdtAddress;
      break;
    }
    RsdPtr += 4;
  } while ( RsdPtr <= (UINT32*) (UINTN) FCHOEM_ACPI_TABLE_RANGE_HIGH );

  if ( Rsdt != NULL && AcpiGetTableCheckSum (Rsdt) == 0 ) {
    for ( Index = 0; Index < (((DESCRIPTION_HEADER*)Rsdt)->Length - sizeof (DESCRIPTION_HEADER)) / 4; Index++ ) {
      TableOffset = *(UINTN*) ((UINT8*)Rsdt + sizeof (DESCRIPTION_HEADER) + Index * 4);
      CurrentTable = (DESCRIPTION_HEADER*)TableOffset;
      if ( CurrentTable->Signature == Signature ) {
        return CurrentTable;
      }
    }
  }
  return NULL;
}

//
//
//  Routine Description:
//
//  Update table CheckSum
//
//  Arguments:
//
//  TablePtr - table pointer
//
//  Returns:
//
//  none
//
//
VOID
AcpiSetTableCheckSum (
  IN  VOID     *TablePtr
  )
{
  UINT8   CheckSum;

  CheckSum = 0;
  ((DESCRIPTION_HEADER*)TablePtr)->CheckSum = 0;
  CheckSum = AcpiGetTableCheckSum (TablePtr);
  ((DESCRIPTION_HEADER*)TablePtr)->CheckSum = (UINT8) (FCHOEM_ACPI_BYTE_CHECHSUM - CheckSum);
}

//
//
//  Routine Description:
//
//  Get table CheckSum - Get ACPI table checksum
//
//  Arguments:
//
//  TablePtr - table pointer
//
//  Returns:
//
//  none
//
//
UINT8
AcpiGetTableCheckSum (
  IN  VOID     *TablePtr
  )
{
  return GetByteSum (TablePtr, ((DESCRIPTION_HEADER*)TablePtr)->Length);
}


//
//
//  Routine Description:
//
//  GetByteSum - Get BYTE checksum value
//
//  Arguments:
//
//  DataPtr - table pointer
//  Length  - table length
//
//  Returns:
//
//  CheckSum - CheckSum value
//
//
UINT8
GetByteSum (
  IN  VOID       *DataPtr,
  IN  UINT32     Length
  )
{
  UINT32   Index;
  UINT8    CheckSum;

  CheckSum = 0;
  for ( Index = 0; Index < Length; Index++ ) {
    CheckSum = CheckSum + (*((UINT8*)DataPtr + Index));
  }
  return CheckSum;
}

//
//
//  Routine Description:
//
//  GetFchAcpiMmioBase - Get FCH HwAcpi MMIO Base Address
//
//  Arguments:
//
//  AcpiMmioBase - HwAcpi MMIO Base Address
//  StdHeader    - Amd Stand Header
//
//  Returns:
//
//  AcpiMmioBase - HwAcpi MMIO Base Address
//
//
VOID
GetFchAcpiMmioBase (
     OUT   UINT32                *AcpiMmioBase,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT32    AcpiMmioBaseAddressDword;

  ReadPmio (FCH_PMIOA_REG24 + 2, AccessWidth16, &AcpiMmioBaseAddressDword, StdHeader);
  *AcpiMmioBase = AcpiMmioBaseAddressDword << 16;
}

//
//
//  Routine Description:
//
//  GetFchAcpiPmBase - Get FCH HwAcpi PM Base Address
//
//  Arguments:
//
//  AcpiPmBase   - HwAcpi PM Base Address
//  StdHeader    - Amd Stand Header
//
//  Returns:
//
//  AcpiPmBase   - HwAcpi PM Base Address
//
//
VOID
GetFchAcpiPmBase (
     OUT   UINT16                *AcpiPmBase,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  ReadPmio (FCH_PMIOA_REG60, AccessWidth16, AcpiPmBase, StdHeader);
}


UINT8
ReadFchSleepType (
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT16     Value16;
  ReadPmio (FCH_PMIOA_REG62, AccessWidth16, &Value16, StdHeader);
  LibAmdIoRead (AccessWidth16, Value16, &Value16, StdHeader);
  return (UINT8) ((Value16 >> 10) & 7);
}


