/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>

#include <Features/Aod/Include/AodRuntimeLib.h>

static UINT16 MemFreqTranslateTable [][2] = {
  {0x04, 333},
  {0x06, 400},
  {0x0A, 533},
  {0x14, 667},
  {0x18, 800},
  {0x19, 1050},
  {0x1A, 1066},
  {0x1C, 933},
  {0x20, 1067},
  {0x24, 1200},
  {0x28, 1333},
  {0x29, 1367},
  {0x2A, 1400},
  {0x2B, 1433},
  {0x2C, 1467},
  {0x2D, 1500},
  {0x2E, 1533},
  {0x2F, 1567},
  {0x30, 1600},
  {0x31, 1633},
  {0x32, 1667},
  {0x33, 1700},
  {0x34, 1733},
  {0x35, 1767},
  {0x36, 1800},
  {0x37, 1833},
  {0x38, 1867},
  {0x39, 1900},
  {0x3A, 1933},
  {0x3B, 1967},
  {0x3C, 2000},
  {0x3D, 2033},
  {0x3E, 2067},
  {0x3F, 2100},
  {0x40, 2133},
  {0x41, 2167},
  {0x42, 2200},
  {0xFF, 0xFF}
};

VOID
AodSmnRead (
  IN       UINT8               DieBusNum,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress;
  PciAddress = (DieBusNum << 20) + 0xB8;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = (DieBusNum << 20) + 0xBC;
  *Value = PciRead32 (PciAddress);
}

VOID
AodSmnWrite (
  IN       UINT8               DieBusNum,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  )
{
  UINT32    RegIndex;
  UINTN     PciAddress;

  RegIndex = SmnAddress;
  PciAddress = (DieBusNum << 20) + 0xB8;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = (DieBusNum << 20) + 0xBC;
  PciWrite32 (PciAddress, *Value);
}


BOOLEAN
VerifyAcpiSmiTransferBuffer (
  AodNvAreaStruct *AodNvAreaPtr
  )
{
  if (AodNvAreaPtr->AodMemBuffer.Version == AOD_MEMORY_BUFFER_VERSION) {
    AodNvAreaPtr->Reserved1 += 0x100;  // Just for test purpose to record function execution times
    return TRUE;
  } else {
    return FALSE;
  }
}


VOID
FinalizeTransferBuffer (
  AodNvAreaStruct *AodNvAreaPtr,
  EFI_STATUS  Status
  )
{
  AodNvAreaPtr->AodSmiCmd = 0;
  AodNvAreaPtr->AodSmiStatus = (UINT32) Status;
  AodNvAreaPtr->AodMemBuffer.Version = 0;     // Clear the version field to avoid multiple entries of SMI handler
  AodNvAreaPtr->AodMemBuffer.Command = 0;
  AodNvAreaPtr->Reserved1 += 1;  // Just for test purpose to record the finalize calling times
  DisableSmMasterDecode ();
}


EFI_STATUS
GetMemFreqIndexByClk (
  UINT16    MemFreqClk,
  UINT8     *FreqIndex
  )
{
  UINT8 Index = 0;
  if (FreqIndex == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (MemFreqTranslateTable[Index][0] != 0xFF) {
    if (MemFreqTranslateTable[Index][1] == MemFreqClk) {
      *FreqIndex = (UINT8) MemFreqTranslateTable[Index][0];
      return EFI_SUCCESS;
    }
    Index++;
  }

  return EFI_NOT_FOUND;
}


EFI_STATUS
GetMemFreqClkByIndex (
  UINT8       FreqIndex,
  UINT16     *MemFreqClk
  )
{
  UINT8 Index = 0;
  if (MemFreqClk == NULL) {
    return EFI_UNSUPPORTED;
  }

  while (MemFreqTranslateTable[Index][0] != 0xFF) {
    if (MemFreqTranslateTable[Index][0] == FreqIndex) {
      *MemFreqClk = MemFreqTranslateTable[Index][1];
      return EFI_SUCCESS;
    }
    Index++;
  }

  return EFI_NOT_FOUND;
}

UINT8
HammingWeight (
  IN UINT32 Value
  )
{
   UINT8 Count;
   UINT32 Temp;

   Count = 0;
   Temp = Value;

   while (Temp > 0) {
      Temp &= Temp - 1;
      Count++;
   }
   return Count;
}

