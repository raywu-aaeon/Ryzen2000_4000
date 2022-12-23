/*****************************************************************************
 *
 * Copyright 2014 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#include <AmdCpmBase.h>

UINT8
CpmIoRead8 (
  IN      UINT16 Address
  )
{
  UINT64  X86IoRemapBase;
  UINT8   Data;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    Data = 0;
  } else {
    Data = *(volatile UINT8 *) (UINT64) (X86IoRemapBase + Address);
  }
  return Data;
}

UINT16
CpmIoRead16 (
  IN      UINT16 Address
  )
{
  UINT64  X86IoRemapBase;
  UINT16  Data;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    Data = 0;
  } else {
    Data = *(volatile UINT16 *) (UINT64) (X86IoRemapBase + Address);
  }
  return Data;
}

UINT32
CpmIoRead32 (
  IN      UINT16 Address
  )
{
  UINT64  X86IoRemapBase;
  UINT32  Data;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    Data = 0;
  } else {
    Data = *(volatile UINT32 *) (UINT64) (X86IoRemapBase + Address);
  }
  return Data;
}

VOID
CpmIoWrite8 (
  IN      UINT16 Address,
  IN      UINT8 Data
  )
{
  UINT64  X86IoRemapBase;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    // Do nothing
  } else {
    *(volatile UINT8 *)(UINT64) (X86IoRemapBase + Address) = Data;
  }
}

VOID
CpmIoWrite16 (
  IN      UINT16 Address,
  IN      UINT16 Data
  )
{
  UINT64  X86IoRemapBase;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    // Do nothing
  } else {
    *(volatile UINT16 *)(UINT64) (X86IoRemapBase + Address) = Data;
  }
}

VOID
CpmIoWrite32 (
  IN      UINT16 Address,
  IN      UINT32 Data
  )
{
  UINT64  X86IoRemapBase;

  X86IoRemapBase = CFG_CPM_X86_IO_REMAP_BASE;
  // No configuration space access supported
  //ASSERT (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF));
  if (!(Address == 0xCF9) && (Address >= 0xCF8) && (Address <= 0xCFF)) {
    // Do nothing
  } else {
    *(volatile UINT32 *)(UINT64) (X86IoRemapBase + Address) = Data;
  }
}

UINT64
CpmReadTsc (
  )
{
  UINT32 Tsc_Low;
  UINT32 Tsc_High;
  UINT64 PciMmioBase;
  UINT64 Data;
  PciMmioBase = CFG_CPM_PCI_MMIO_BASE;
  Tsc_Low     = *(volatile UINT32 *) (UINT64) (PciMmioBase + 0x000C3130);
  Tsc_High    = *(volatile UINT32 *) (UINT64) (PciMmioBase + 0x000C3134);
  Data = (((UINT64)Tsc_High) << 32) + (UINT64)Tsc_Low;
  return Data;
}

VOID
CpmCpuidRawRead (
  IN       UINT32 CpuidFcnAddress,
     OUT   CPUID_DATA *Value
  )
{
  UINT64 Address;
  if (Value) {
    Value->EAX_Reg = 0;
    Value->EBX_Reg = 0;
    Value->ECX_Reg = 0;
    Value->EDX_Reg = 0;
    switch (CpuidFcnAddress) {
    case 0x80000001:
      Address = (UINT32)CFG_CPM_PCI_MMIO_BASE;
      Value->EAX_Reg = *(volatile UINT32 *) (UINT64) (Address + 0x000C30FC);
      Value->EBX_Reg = (*(volatile UINT32 *) (UINT64) (Address + 0x000C30EC) & 0x00000700) << 20;
      break;
    }
  }
}

UINT64
CpmMsrRead (
  IN      UINT32 MsrAddress
  )
{
  UINT64 Value;
  Value = 0x0BAD0BAD0BAD0BADull;
  switch (MsrAddress) {
  case 0x0000001B:
    // Simulate MSR_IA32_APIC_BASE[8]
    Value = 0x0000000000000100ull;
    break;
  case 0xC0001015:
    // Simulate MSR_HWCR[24]: TscFreqSel
    Value = 0x0000000001000000ull;
    break;
  case 0xC0010058:
    // Simulate MMIO Configuration Base Address
    Value = CFG_CPM_PCI_MMIO_BASE;
    break;
  }
  return Value;
}

UINT64
CpmMsrWrite (
  IN       UINT32 MsrAddress,
  IN       UINT64 Value
  )
{
  return 0x0BAD0BAD0BAD0BADull;
}
