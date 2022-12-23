/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD AGESA library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_AMDBASELIB_AMDBASELIB_FILECODE
#define NB_CFG      0xC001001Ful
#define MSR_MMIO_Cfg_Base           0xC0010058ul    // MMIO Configuration Base Address Register

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------*/
/**
 * Read IO port
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] IoAddress     IO port address
 * @param[in] Value         Pointer to save data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdIoRead (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT16 IoAddress,
     OUT   VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    *(UINT8 *) Value = IoRead8 (IoAddress);
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    *(UINT16 *) Value = IoRead16 (IoAddress);
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    *(UINT32 *) Value = IoRead32 (IoAddress);
    break;
  default:
    ASSERT (FALSE);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write IO port
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] IoAddress     IO port address
 * @param[in] Value         Pointer to data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdIoWrite (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT16 IoAddress,
  IN       VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    IoWrite8 (IoAddress, *(UINT8 *) Value);
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    IoWrite16 (IoAddress, *(UINT16 *) Value);
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    IoWrite32 (IoAddress, *(UINT32 *) Value);
    break;
  default:
    ASSERT (FALSE);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * IO read modify write
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] IoAddress     IO address
 * @param[in] Data          OR data
 * @param[in] DataMask      Mask to be used before data write back to register.
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdIoRMW (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT16 IoAddress,
  IN       VOID *Data,
  IN       VOID *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  UINT32  Value;
  LibAmdGetDataFromPtr (AccessWidth, Data,  DataMask, &TempData, &TempMask);
  LibAmdIoRead (AccessWidth, IoAddress, &Value, StdHeader);
  Value = (Value & (~TempMask)) | TempData;
  LibAmdIoWrite (AccessWidth, IoAddress, &Value, StdHeader);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Poll IO register
 *
 *  Poll register until (RegisterValue & DataMask) ==  Data
 *
 * @param[in] AccessWidth   Access width
 * @param[in] IoAddress     IO address
 * @param[in] Data          Data to compare
 * @param[in] DataMask      And mask
 * @param[in] Delay         Poll for time in 100ns (not supported)
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdIoPoll (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT16 IoAddress,
  IN       VOID *Data,
  IN       VOID *DataMask,
  IN       UINT64 Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  UINT32  Value;
  LibAmdGetDataFromPtr (AccessWidth, Data,  DataMask, &TempData, &TempMask);
  do {
    LibAmdIoRead (AccessWidth, IoAddress, &Value, StdHeader);
  } while (TempData != (Value & TempMask));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read memory/MMIO - 32bit access
 *
 *
 * @param[in] MemAddress    Memory address
 * @param[in] Value         Pointer to data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemRead32 (
  IN       UINT64 MemAddress,
     OUT   VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  *(UINT32 *) Value = MmioRead32 ((UINTN)MemAddress);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write memory/MMIO - 32bit access
 *
 *
 * @param[in] MemAddress    Memory address
 * @param[in] Value         Pointer to data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemWrite32 (
  IN       UINT64 MemAddress,
  IN       VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  MmioWrite32 ((UINTN) MemAddress, *((UINT32 *) Value));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read memory/MMIO
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] MemAddress    Memory address
 * @param[in] Value         Pointer to data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemRead (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT64 MemAddress,
     OUT   VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  if (sizeof (UINTN) == sizeof (UINT32)) {
    ASSERT (MemAddress <= 0xFFFFFFFF);
  }

  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    *(UINT8 *) Value = MmioRead8 ((UINTN)MemAddress);
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    *(UINT16 *) Value = MmioRead16 ((UINTN)MemAddress);
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    *(UINT32 *) Value = MmioRead32 ((UINTN)MemAddress);
    break;
  default:
    ASSERT (FALSE);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write memory/MMIO
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] MemAddress    Memory address
 * @param[in] Value         Pointer to data
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemWrite (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT64 MemAddress,
  IN       VOID *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  if (sizeof (UINTN) == sizeof (UINT32)) {
    ASSERT (MemAddress <= 0xFFFFFFFF);
  }

  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    MmioWrite8 ((UINTN) MemAddress, *((UINT8 *) Value));
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    MmioWrite16 ((UINTN) MemAddress, *((UINT16 *) Value));
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    MmioWrite32 ((UINTN) MemAddress, *((UINT32 *) Value));
    break;
  default:
    ASSERT (FALSE);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Memory/MMIO read modify write
 *
 *
 * @param[in] AccessWidth   Access width
 * @param[in] MemAddress    Memory address
 * @param[in] Data          OR data
 * @param[in] DataMask      Mask to be used before data write back to register.
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemRMW (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT64 MemAddress,
  IN       VOID *Data,
  IN       VOID *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  UINT32  Value;
  LibAmdGetDataFromPtr (AccessWidth, Data,  DataMask, &TempData, &TempMask);
  LibAmdMemRead (AccessWidth, MemAddress, &Value, StdHeader);
  Value = (Value & (~TempMask)) | TempData;
  LibAmdMemWrite (AccessWidth, MemAddress, &Value, StdHeader);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Poll Mmio
 *
 *  Poll register until (RegisterValue & DataMask) ==  Data
 *
 * @param[in] AccessWidth   Access width
 * @param[in] MemAddress    Memory address
 * @param[in] Data          Data to compare
 * @param[in] DataMask      AND mask
 * @param[in] Delay         Poll for time in 100ns (not supported)
 * @param[in] StdHeader     Standard configuration header
 *
 */
VOID
LibAmdMemPoll (
  IN       ACCESS_WIDTH AccessWidth,
  IN       UINT64 MemAddress,
  IN       VOID *Data,
  IN       VOID *DataMask,
  IN       UINT64 Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  UINT32  Value;
  LibAmdGetDataFromPtr (AccessWidth, Data,  DataMask, &TempData, &TempMask);
  do {
    LibAmdMemRead (AccessWidth, MemAddress, &Value, StdHeader);
  } while (TempData != (Value & TempMask));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get MMIO base address for PCI accesses
 *
 * @param[out] MmioAddress   PCI MMIO base address
 * @param[out] MmioSize      Size of region in bytes
 * @param[in]  StdHeader     Standard configuration header
 *
 * @retval    TRUE          MmioAddress/MmioSize are valid
 */
BOOLEAN
GetPciMmioAddress (
     OUT   UINT64            *MmioAddress,
     OUT   UINT32            *MmioSize,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  BOOLEAN MmioIsEnabled;
  UINT32  EncodedSize;
  UINT64  LocalMsrRegister;

  MmioIsEnabled = FALSE;
  LocalMsrRegister = AsmReadMsr64 (MSR_MMIO_Cfg_Base);
  if ((LocalMsrRegister & BIT0) != 0) {
    *MmioAddress = LocalMsrRegister & 0xFFFFFFFFFFF00000;
    EncodedSize = (UINT32) RShiftU64 ((LocalMsrRegister & 0x3C), 2);
    *MmioSize = ((1 << EncodedSize) * 0x100000);
    MmioIsEnabled = TRUE;
  }
  return MmioIsEnabled;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Locate next capability pointer
 *
 *  Given a SBDFO this routine will find the next PCI capabilities list entry.
 *  if the end of the list is reached, or if a problem is detected, then ILLEGAL_SBDFO is
 *  returned.
 *  To start a new search from the head of the list, specify a SBDFO with an offset of zero.
 *
 * @param[in,out] Address       Pci address
 * @param[in]     StdHeader     Standard configuration header
 */

VOID
LibAmdPciFindNextCap (
  IN OUT   PCI_ADDR *Address,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  PCI_ADDR Base;
  UINT32 Offset;
  UINT32 Temp;
  PCI_ADDR TempAddress;

  ASSERT (Address != NULL);
  ASSERT (*(UINT32 *) Address != ILLEGAL_SBDFO);

  Base.AddressValue = Address->AddressValue;
  Offset = Base.Address.Register;
  Base.Address.Register = 0;

  Address->AddressValue = (UINT32) ILLEGAL_SBDFO;

  // Verify that the SBDFO points to a valid PCI device SANITY CHECK
  Temp = PciRead32 (Base.AddressValue);
  if (Temp == 0xFFFFFFFF) {
    ASSERT (FALSE);
    return; // There is no device at this address
  }

  // Verify that the device supports a capability list
  TempAddress.AddressValue = Base.AddressValue + 0x04;
  Temp = PciBitFieldRead32 (TempAddress.AddressValue, 20, 20);
  if (Temp == 0) {
    return; // This PCI device does not support capability lists
  }

  if (Offset != 0) {
    // If we are continuing on an existing list
    TempAddress.AddressValue = Base.AddressValue + Offset;
    Temp = PciBitFieldRead32 (TempAddress.AddressValue, 8, 15);
  } else {
    // We are starting on a new list
    TempAddress.AddressValue = Base.AddressValue + 0x34;
    Temp = PciBitFieldRead32 (TempAddress.AddressValue, 0, 7);
  }

  if (Temp == 0) {
    return; // We have reached the end of the capabilities list
  }

  // Error detection and recovery- The statement below protects against
  //   PCI devices with broken PCI capabilities lists.  Detect a pointer
  //   that is not uint32 aligned, points into the first 64 reserved DWORDs
  //   or points back to itself.
  if (((Temp & 3) != 0) || (Temp == Offset) || (Temp < 0x40)) {
    ASSERT (FALSE);
    return;
  }

  Address->AddressValue = Base.AddressValue + Temp;
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Insert SMBIOS NULL terminated string at Destination address
 *
 * @param[in,out] Destination   Pointer to Destination string pointer
 * @param[in]     DestMax       Pointer to max size of buffer
 * @param[in]     Source        Pointer to Source String
 *
 * @retval        EFI_STATUS    Status of placing string
 *
 */
EFI_STATUS
EFIAPI
LibAmdInsertSmbiosString (
  IN OUT   CHAR8       **Destination,
  IN       UINTN       *DestMax,
  IN       CONST CHAR8 *Source
  )
{
  EFI_STATUS  Status;

  if (Source[0] != 0) {
    Status = AsciiStrCatS (*Destination, *DestMax, Source);
    *Destination += AsciiStrSize (Source);
    *DestMax -= AsciiStrSize (Source);
  } else {
    Status = AsciiStrCpyS (*Destination, *DestMax, "Unknown");
    *Destination += AsciiStrSize ("Unknown");
    *DestMax -= AsciiStrSize ("Unknown");
  }

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set memory with value
 *
 *
 * @param[in,out] Destination   Pointer to memory range
 * @param[in]     Value         Value to set memory with
 * @param[in]     FillLength    Size of the memory range
 * @param[in]     StdHeader     Standard configuration header (Optional)
 */
VOID
LibAmdMemFill (
  IN       VOID *Destination,
  IN       UINT8 Value,
  IN       UINTN FillLength,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  SetMem (Destination, FillLength, Value);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Copy memory
 *
 *
 * @param[in,out] Destination   Pointer to destination buffer
 * @param[in]     Source        Pointer to source buffer
 * @param[in]     CopyLength    buffer length
 * @param[in]     StdHeader     Standard configuration header (Optional)
 */
VOID
LibAmdMemCopy (
  IN       VOID *Destination,
  IN       VOID *Source,
  IN       UINTN CopyLength,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  CopyMem (Destination, Source, CopyLength);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Returns the package type mask for the processor
 *
 *
 * @param[in]     StdHeader     Standard configuration header (Optional)
 */

//  Returns the package type mask for the processor
UINT32
LibAmdGetPackageType (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32      ProcessorPackageType;
  CPUID_DATA  CpuId;

  AsmCpuid (
      0x80000001,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  ProcessorPackageType = (UINT32) (CpuId.EBX_Reg >> 28) & 0xF; // bit 31:28
  return (UINT32) (1 << ProcessorPackageType);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Returns the package type mask for the processor
 *
 *
 * @param[in]     AccessWidth     Access width
 * @param[in]     Data            data
 * @param[in]     DataMask        data
 * @param[out]    TemData         typecast data
 * @param[out]    TempDataMask    typecast data
 */


VOID
LibAmdGetDataFromPtr (
  IN       ACCESS_WIDTH AccessWidth,
  IN       VOID         *Data,
  IN       VOID         *DataMask,
     OUT   UINT32       *TemData,
     OUT   UINT32       *TempDataMask
  )
{
  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    *TemData = (UINT32)*(UINT8 *) Data;
    *TempDataMask = (UINT32)*(UINT8 *) DataMask;
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    *TemData = (UINT32)*(UINT16 *) Data;
    *TempDataMask = (UINT32)*(UINT16 *) DataMask;
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    *TemData = *(UINT32 *) Data;
    *TempDataMask = *(UINT32 *) DataMask;
    break;
  default:
    IDS_ERROR_TRAP;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Returns the package type mask for the processor
 *
 *
 * @param[in]     AccessWidth     Access width
 * @retval        Width in number of bytes
 */


UINT8
LibAmdAccessWidth (
  IN       ACCESS_WIDTH AccessWidth
  )
{
  UINT8 Width;

  switch (AccessWidth) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    Width = 1;
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    Width = 2;
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    Width = 4;
    break;
  case AccessWidth64:
  case AccessS3SaveWidth64:
    Width = 8;
    break;
  default:
    Width = 0;
    IDS_ERROR_TRAP;
  }
  return Width;
}

