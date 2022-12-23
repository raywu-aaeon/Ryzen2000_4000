/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH IO access common routine
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*;********************************************************************************
;
; Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
;
; AMD is granting you permission to use this software and documentation (if
; any) (collectively, the "Materials") pursuant to the terms and conditions of
; the Software License Agreement included with the Materials.  If you do not
; have a copy of the Software License Agreement, contact your AMD
; representative for a copy.
;
; You agree that you will not reverse engineer or decompile the Materials, in
; whole or in part, except as allowed by applicable law.
;
; WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
; ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
; INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
; MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
; CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
; OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
; exclusion of implied warranties, so the above exclusion may not apply to
; You.
;
; LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
; NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
; INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
; THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
; liability to You for all damages, losses, and causes of action (whether in
; contract, tort (including negligence) or otherwise) exceed the amount of
; $100 USD. You agree to defend, indemnify and hold harmless AMD and its
; licensors, and any of their directors, officers, employees, affiliates or
; agents from and against any and all loss, damage, liability and other
; expenses (including reasonable attorneys' fees), resulting from Your use of
; the Materials or violation of the terms and conditions of this Agreement.
;
; U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
; "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
; subject to the restrictions as set forth in FAR 52.227-14 and
; DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
; Government constitutes acknowledgment of AMD's proprietary rights in them.
;
; EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
; stated in the Software License Agreement.
;******************************************************************************
;*/
#include "FchPlatform.h"
#define FILECODE PROC_FCH_COMMON_FCHLIB_FILECODE

/**< FchStall - Reserved  */
VOID
FchStall (
  IN       UINT32              uSec,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT16 timerAddr;
  UINT32 startTime;
  UINT32 elapsedTime;

  LibAmdMemRead (AccessWidth16, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG64), &timerAddr, StdHeader);
  if ( timerAddr == 0 ) {
    uSec = uSec / 2;
    while ( uSec != 0 ) {
      LibAmdIoRead (AccessWidth8, FCHOEM_IO_DELAY_PORT, (UINT8 *) (&startTime), StdHeader);
      uSec--;
    }
  } else {
    LibAmdIoRead (AccessWidth32, timerAddr, &startTime, StdHeader);
    for ( ;; ) {
      LibAmdIoRead (AccessWidth32, timerAddr, &elapsedTime, StdHeader);
      if ( elapsedTime < startTime ) {
        elapsedTime = elapsedTime + FCH_MAX_TIMER - startTime;
      } else {
        elapsedTime = elapsedTime - startTime;
      }
      if ( (elapsedTime * FCHOEM_ELAPSED_TIME_UNIT / FCHOEM_ELAPSED_TIME_DIVIDER) > uSec ) {
        break;
      }
    }
  }
}

/**< cimFchStall - Reserved  */
VOID
CimFchStall (
  IN       UINT32              uSec,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT16 timerAddr;
  UINT32 startTime;
  UINT32 elapsedTime;

  LibAmdMemRead (AccessWidth16, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG64), &timerAddr, StdHeader);
  if ( timerAddr == 0 ) {
    uSec = uSec / 2;
    while ( uSec != 0 ) {
      LibAmdIoRead (AccessWidth8, FCHOEM_IO_DELAY_PORT, (UINT8*)&elapsedTime, StdHeader);
      uSec--;
    }
  } else {
    LibAmdIoRead (AccessWidth32, timerAddr, &startTime, StdHeader);
    for ( ;; ) {
      LibAmdIoRead (AccessWidth32, timerAddr, &elapsedTime, StdHeader);
      if ( elapsedTime < startTime ) {
        elapsedTime = elapsedTime + FCH_MAX_TIMER - startTime;
      } else {
        elapsedTime = elapsedTime - startTime;
      }
      if ( (elapsedTime * FCHOEM_ELAPSED_TIME_UNIT / FCHOEM_ELAPSED_TIME_DIVIDER) > uSec ) {
        break;
      }
    }
  }
}

/**< FchReset - Reserved  */
VOID
FchPciReset (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8   PciRstValue;

  PciRstValue = 0x06;
  LibAmdIoWrite (AccessWidth8, FCH_PCIRST_BASE_IO, &PciRstValue, StdHeader);
}

/**< outPort80 - Reserved  */
VOID
OutPort80 (
  IN       UINT32              pcode,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  LibAmdIoWrite (AccessWidth8, FCHOEM_OUTPUT_DEBUG_PORT, &pcode, StdHeader);
  return;
}

/**< outPort1080 - Reserved  */
VOID
OutPort1080 (
  IN       UINT32              pcode,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  LibAmdIoWrite (AccessWidth32, 0x1080, &pcode, StdHeader);
  return;
}

/**< FchCopyMem - Reserved  */
VOID
FchCopyMem (
  IN      VOID*   pDest,
  IN      VOID*   pSource,
  IN      UINTN   Length
  )
{
  UINTN  i;
  UINT8  *Ptr;
  UINT8  *Source;
  Ptr = (UINT8*)pDest;
  Source = (UINT8*)pSource;
  for (i = 0; i < Length; i++) {
    *Ptr = *Source;
    Source++;
    Ptr++;
  }
}

/** GetRomSigPtr - Reserved **/
VOID*
GetRomSigPtr (
  IN      UINTN               *RomSigPtr,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32   RomPtr;
  UINT32   RomSig;
  UINT16   MswAddr;

  *RomSigPtr = 0;
  MswAddr = 0xFF00;
  do {
    RomPtr = (MswAddr << 16) + FCH_ROMSIG_BASE_IO;
    LibAmdMemRead (AccessWidth32, (UINT64) RomPtr, &RomSig, StdHeader);
    if (RomSig == FCH_ROMSIG_SIGNATURE) {
      *RomSigPtr = RomPtr;
      break;
    }
    MswAddr >>= 1;
    MswAddr |= BIT15;
  } while (MswAddr != 0xFFFC);//Change from 0xFFF8 ro 0xFFFC to cover ROM_SIG@0xFFFA0000 
  if (*RomSigPtr == 0) {
    //Error Condition Embedded Firmware Structure not found
    IDS_HDT_CONSOLE (FCH_TRACE, "GetRomSigPtr failed to find Ptr HALT\n" );
    FCH_DEADLOOP();
  }
  return RomSigPtr;
}

/** RwXhciIndReg - Reserved **/
VOID
RwXhciIndReg (
  IN       UINT32              Index,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN  PciAddress;

  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, Index);
  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x4C;
  PciAndThenOr32 (PciAddress, AndMask, OrMask);

  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, Index);
  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x4C;
  PciAndThenOr32 (PciAddress, AndMask, OrMask);
}

/** RwXhci0IndReg - Reserved **/
VOID
RwXhci0IndReg (
  IN       UINT32              Index,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN  PciAddress;

  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, Index);
  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x4C;
  PciAndThenOr32 (PciAddress, AndMask, OrMask);
}

/** RwXhci1IndReg - Reserved **/
VOID
RwXhci1IndReg (
  IN       UINT32              Index,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN  PciAddress;

  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, Index);
  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x4C;
  PciAndThenOr32 (PciAddress, AndMask, OrMask);
}

/** ReadXhci0Phy - Reserved **/
VOID
ReadXhci0Phy (
  IN       UINT32              Port,
  IN       UINT32              Address,
  IN       UINT32              *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32    RegIndex;
  UINT32    RegValue;
  UINTN     PciAddress;

  RwXhci0IndReg ( FCH_XHCI_IND60_REG00, 0xFFFFC000, (Port << 13) + BIT12 + Address, StdHeader);

  RegIndex = FCH_XHCI_IND60_REG04;
  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = (USB_XHCI_BUS_DEV_FUN << 12) + 0x4C;
  RegValue = PciRead32 (PciAddress);

  (*Value) = ( RegValue >> (Port * 8)) & 0x000000FF;
}

/** ReadXhci1Phy - Reserved **/
VOID
ReadXhci1Phy (
  IN       UINT32              Port,
  IN       UINT32              Address,
  IN       UINT32              *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32    RegIndex;
  UINT32    RegValue;
  UINTN     PciAddress;

  RwXhci1IndReg ( FCH_XHCI_IND60_REG00, 0xFFFFC000, (Port << 13) + BIT12 + Address, StdHeader);

  RegIndex = FCH_XHCI_IND60_REG04;
  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, RegIndex);
  PciAddress = (USB_XHCI1_BUS_DEV_FUN << 12) + 0x4C;
  RegValue = PciRead32 (PciAddress);

  (*Value) = ( RegValue >> (Port * 8)) & 0x000000FF;
}

/** RwSsicIndReg - Reserved **/
VOID
RwSsicIndReg (
  IN       UINT32              Index,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN  PciAddress;

  PciAddress = (USB_SSIC_BUS_DEV_FUN << 12) + 0x48;
  PciWrite32 (PciAddress, Index);
  PciAddress = (USB_SSIC_BUS_DEV_FUN << 12) + 0x4C;
  PciAndThenOr32 (PciAddress, AndMask, OrMask);
}

/** AcLossControl - Reserved **/
VOID
AcLossControl (
  IN       UINT8 AcLossControlValue
  )
{
  AcLossControlValue &= 0x03;
  AcLossControlValue |= BIT2;
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG5B, AccessWidth8, 0xF0, AcLossControlValue);
}

/** RecordFchConfigPtr - Reserved **/
VOID
RecordFchConfigPtr (
  IN       UINT32 FchConfigPtr
  )
{
  RwMem (ACPI_MMIO_BASE + CMOS_RAM_BASE + 0x08, AccessWidth8, 0, (UINT8) ((FchConfigPtr >> 0) & 0xFF) );
  RwMem (ACPI_MMIO_BASE + CMOS_RAM_BASE + 0x09, AccessWidth8, 0, (UINT8) ((FchConfigPtr >> 8) & 0xFF) );
  RwMem (ACPI_MMIO_BASE + CMOS_RAM_BASE + 0x0A, AccessWidth8, 0, (UINT8) ((FchConfigPtr >> 16) & 0xFF) );
  RwMem (ACPI_MMIO_BASE + CMOS_RAM_BASE + 0x0B, AccessWidth8, 0, (UINT8) ((FchConfigPtr >> 24) & 0xFF) );
}

/** ReadAlink - Reserved **/
UINT32
ReadAlink (
  IN       UINT32              Index,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 Data;
  LibAmdIoWrite (AccessWidth32, ALINK_ACCESS_INDEX, &Index, StdHeader);
  LibAmdIoRead (AccessWidth32, ALINK_ACCESS_DATA, &Data, StdHeader);
  //Clear Index
  Index = 0;
  LibAmdIoWrite (AccessWidth32, ALINK_ACCESS_INDEX, &Index, StdHeader);
  return Data;
}

/** WriteAlink - Reserved **/
VOID
WriteAlink (
  IN       UINT32              Index,
  IN       UINT32              Data,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  LibAmdIoWrite (AccessWidth32, ALINK_ACCESS_INDEX, &Index, StdHeader);
  LibAmdIoWrite (AccessWidth32, ALINK_ACCESS_DATA, &Data, StdHeader);
  //Clear Index
  Index = 0;
  LibAmdIoWrite (AccessWidth32, ALINK_ACCESS_INDEX, &Index, StdHeader);
}

/** RwAlink - Reserved **/
VOID
RwAlink (
  IN       UINT32              Index,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 AccessType;

  AccessType = Index & 0xE0000000;
  if (AccessType == (AXINDC << 29)) {
    WriteAlink ((FCH_AX_INDXC_REG30 | AccessType), Index & 0x1FFFFFFF, StdHeader);
    Index = FCH_AX_DATAC_REG34 | AccessType;
  } else if (AccessType == (AXINDP << 29)) {
    WriteAlink ((FCH_AX_INDXP_REG38 | AccessType), Index & 0x1FFFFFFF, StdHeader);
    Index = FCH_AX_DATAP_REG3C | AccessType;
  }
  WriteAlink (Index, (ReadAlink (Index, StdHeader) & AndMask) | OrMask, StdHeader);
}


/*----------------------------------------------------------------------------------------*/
/**
 * Read PMIO
 *
 *
 *
 * @param[in] Address  - PMIO Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Read Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
ReadPmio (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8    i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);
  for (i = 0; i < OpFlag; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD6, &Address, StdHeader);
    Address++;
    LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGCD7, (UINT8 *)Value + i, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Write PMIO
 *
 *
 *
 * @param[in] Address  - PMIO Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Write Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
WritePmio (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8    i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);
  for (i = 0; i < OpFlag; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD6, &Address, StdHeader);
    Address++;
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD7, (UINT8 *)Value + i, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * RwPmio - Read/Write PMIO
 *
 *
 *
 * @param[in] Address    - PMIO Offset value
 * @param[in] OpFlag     - Access sizes
 * @param[in] AndMask    - Data And Mask 32 bits
 * @param[in] OrMask     - Data OR Mask 32 bits
 * @param[in] StdHeader
 *
 */
VOID
RwPmio (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       UINT32              AndMask,
  IN       UINT32              OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 Result;

  ReadPmio (Address, OpFlag, &Result, StdHeader);
  Result = (Result & AndMask) | OrMask;
  WritePmio (Address, OpFlag, &Result, StdHeader);
}


/*----------------------------------------------------------------------------------------*/
/**
 * Read PMIO2
 *
 *
 *
 * @param[in] Address  - PMIO2 Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Read Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
ReadPmio2 (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8 i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);
  for ( i = 0; i < OpFlag; i++ ) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD0, &Address, StdHeader);
    Address++;
    LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGCD1, (UINT8 *) Value + i, StdHeader);
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Write PMIO 2
 *
 *
 *
 * @param[in] Address  - PMIO2 Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Write Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
WritePmio2 (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8 i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);

  for ( i = 0; i < OpFlag; i++ ) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD0, &Address, StdHeader);
    Address++;
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD1, (UINT8 *) Value + i, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * RwPmio2 - Read/Write PMIO2
 *
 *
 *
 * @param[in] Address    - PMIO2 Offset value
 * @param[in] OpFlag     - Access sizes
 * @param[in] AndMask    - Data And Mask 32 bits
 * @param[in] OrMask     - Data OR Mask 32 bits
 * @param[in] StdHeader
 *
 */
VOID
RwPmio2 (
  IN       UINT8 Address,
  IN       UINT8  OpFlag,
  IN       UINT32 AndMask,
  IN       UINT32 OrMask,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 Result;

  ReadPmio2 (Address, OpFlag, &Result, StdHeader);
  Result = (Result & AndMask) | OrMask;
  WritePmio2 (Address, OpFlag, &Result, StdHeader);
}


/*----------------------------------------------------------------------------------------*/
/**
 * Read BIOSRAM
 *
 *
 *
 * @param[in] Address  - BIOSRAM Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Read Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
ReadBiosram (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8    i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);
  for (i = 0; i < OpFlag; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD4, &Address, StdHeader);
    Address++;
    LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGCD5, (UINT8 *)Value + i, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Write BIOSRAM
 *
 *
 *
 * @param[in] Address  - BIOSRAM Offset value
 * @param[in] OpFlag   - Access sizes
 * @param[in] Value    - Write Data Buffer
 * @param[in] StdHeader
 *
 */
VOID
WriteBiosram (
  IN       UINT8               Address,
  IN       UINT8               OpFlag,
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8    i;

  OpFlag = OpFlag & 0x7f;
  OpFlag = 1 << (OpFlag - 1);
  for (i = 0; i < OpFlag; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD4, &Address, StdHeader);
    Address++;
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGCD5, (UINT8 *)Value + i, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Record SMI Status
 *
 *
 * @param[in] StdHeader
 *
 */
VOID
RecordSmiStatus (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN   Index;
  UINT8   SwSmiValue;

  ACPIMMIO8 (0xfed80304) |= 0x01;
  for ( Index = 0; Index < 20; Index++ ) {
    ACPIMMIO8 (0xfed10020 + Index) = ACPIMMIO8 (0xfed80280 + Index);
  }
  LibAmdIoRead (AccessWidth8, 0xB0, &SwSmiValue, StdHeader);
  ACPIMMIO8 (0xfed10040) = SwSmiValue;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Clear All SMI Status
 *
 *
 * @param[in] StdHeader
 *
 */
VOID
ClearAllSmiStatus (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINTN   Index;

  for ( Index = 0; Index < 20; Index++ ) {
    ACPIMMIO8 (0xfed80280 + Index) |= 0;
  }
}

