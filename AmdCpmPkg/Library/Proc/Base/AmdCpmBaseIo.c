/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#include <AmdCpmBaseIo.h>
#include CPM_PPI_DEFINITION (AmdCpmTablePpi)

/*---------------------------------------------------------------------------------------*/
/**
 * Read an 8-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 *
 * @retval    Register value
 *
 */
UINT8
EFIAPI
CpmMmioRead8 (
  IN       UINTN   Address
  )
{
  UINT8   Value;

  Value = *(volatile UINT8*)Address;
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a   Address = 0x%08X Value = 0x%02X\n", __FUNCTION__, Address, Value));
  return Value;
}


/*---------------------------------------------------------------------------------------*/
/**
 * Write an 8-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 * @param[in] Value         The value to write to the MMIO register
 *
 */
UINT8
EFIAPI
CpmMmioWrite8 (
  IN       UINTN   Address,
  IN       UINT8   Value
  )
{
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a  Address = 0x%08X Value = 0x%02X\n", __FUNCTION__, Address, Value));
  return *(volatile UINT8*)Address = Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 16-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 *
 * @retval    Register value
 *
 */
UINT16
EFIAPI
CpmMmioRead16 (
  IN       UINTN   Address
  )
{
  UINT16  Value;

  Value = *(volatile UINT16*)Address;
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a  Address = 0x%08X Value = 0x%04X\n", __FUNCTION__, Address, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 16-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register to read
 * @param[in] Value         The value to write to the MMIO register
 *
 */
UINT16
EFIAPI
CpmMmioWrite16 (
  IN       UINTN   Address,
  IN       UINT16  Value
  )
{
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a Address = 0x%08X Value = 0x%04X\n", __FUNCTION__, Address, Value));
  return *(volatile UINT16*)Address = Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 32-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 *
 * @retval    Register value
 *
 */
UINT32
EFIAPI
CpmMmioRead32 (
  IN       UINTN   Address
  )
{
  UINT32  Value;

  Value = *(volatile UINT32*)Address;
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a  Address = 0x%08X Value = 0x%08X\n", __FUNCTION__, Address, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 32-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 * @param[in] Value         The value to write to the MMIO register
 *
 */
UINT32
EFIAPI
CpmMmioWrite32 (
  IN       UINTN   Address,
  IN       UINT32  Value
  )
{
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a Address = 0x%08X Value = 0x%08X\n", __FUNCTION__, Address, Value));
  return *(volatile UINT32*)Address = Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 64-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 *
 * @retval    Register value
 *
 */
UINT64
EFIAPI
CpmMmioRead64 (
  IN       UINTN   Address
  )
{
  UINT64  Value;

  Value = *(volatile UINT64*)Address;
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a  Address = 0x%016X Value = 0x%016X\n", __FUNCTION__, Address, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 64-bit MMIO register
 *
 *
 * @param[in] Address       The MMIO register address
 * @param[in] Value         The value to write to the MMIO register
 *
 */
UINT64
EFIAPI
CpmMmioWrite64 (
  IN       UINTN   Address,
  IN       UINT64  Value
  )
{
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a Address = 0x%016X Value = 0x%016X\n", __FUNCTION__, Address, Value));
  return *(volatile UINT64*)Address = Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit MMIO register, performs a bitwise inclusive OR, and writes the
 * result back to the 8-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT8
EFIAPI
CpmMmioOr8 (
  IN       UINTN   Address,
  IN       UINT8   OrData
  )
{
  return CpmMmioWrite8 (Address, CpmMmioRead8 (Address) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit MMIO register, performs a bitwise AND, and writes the result back
 * to the 16-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 *
 */
UINT8
EFIAPI
CpmMmioAnd8 (
  IN       UINTN   Address,
  IN       UINT8   AndData
  )
{
  return CpmMmioWrite8 (Address, CpmMmioRead8 (Address) & AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit MMIO register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 16-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT8
EFIAPI
CpmMmioAndThenOr8 (
  IN       UINTN   Address,
  IN       UINT8   AndData,
  IN       UINT8   OrData
  )
{
    return CpmMmioWrite8 (Address, (CpmMmioRead8 (Address) & AndData) | OrData);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit MMIO register, performs a bitwise inclusive OR, and writes the
 * result back to the 16-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT16
EFIAPI
CpmMmioOr16 (
  IN       UINTN       Address,
  IN       UINT16      OrData
  )
{
  return CpmMmioWrite16 (Address, CpmMmioRead16 (Address) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit MMIO register, performs a bitwise AND, and writes the result back
 * to the 16-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 *
 */
UINT16
EFIAPI
CpmMmioAnd16 (
  IN       UINTN   Address,
  IN       UINT16  AndData
  )
{
  return CpmMmioWrite16 (Address, CpmMmioRead16 (Address) & AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit MMIO register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 16-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT16
EFIAPI
CpmMmioAndThenOr16 (
  IN       UINTN   Address,
  IN       UINT16  AndData,
  IN       UINT16  OrData
  )
{
  return CpmMmioWrite16 (Address, (CpmMmioRead16 (Address) & AndData) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit MMIO register, performs a bitwise inclusive OR, and writes the
 * result back to the 32-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT32
EFIAPI
CpmMmioOr32 (
  IN       UINTN   Address,
  IN       UINT32  OrData
  )
{
  return CpmMmioWrite32 (Address, CpmMmioRead32 (Address) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit MMIO register, performs a bitwise AND, and writes the result back
 * to the 32-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 *
 */
UINT32
EFIAPI
CpmMmioAnd32 (
  IN       UINTN   Address,
  IN       UINT32  AndData
  )
{
  return CpmMmioWrite32 (Address, CpmMmioRead32 (Address) & AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit MMIO register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 32-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT32
EFIAPI
CpmMmioAndThenOr32 (
  IN       UINTN   Address,
  IN       UINT32  AndData,
  IN       UINT32  OrData
  )
{
  return CpmMmioWrite32 (Address, (CpmMmioRead32 (Address) & AndData) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 64-bit MMIO register, performs a bitwise inclusive OR, and writes the
 * result back to the 64-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT64
EFIAPI
CpmMmioOr64 (
  IN       UINTN   Address,
  IN       UINT64  OrData
  )
{
  return CpmMmioWrite64 (Address, CpmMmioRead64 (Address) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 64-bit MMIO register, performs a bitwise AND, and writes the result back
 * to the 64-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData        The value to AND with the read value from the MMIO register.
 *
 */
UINT64
EFIAPI
CpmMmioAnd64 (
  IN       UINTN   Address,
  IN       UINT64  AndData
  )
{
  return CpmMmioWrite64 (Address, CpmMmioRead64 (Address) & AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 64-bit MMIO register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 64-bit MMIO register.
 *
 * @param[in] Address       The MMIO register address
 * @param[in] AndData       The value to AND with the read value from the MMIO register.
 * @param[in] OrData        The value to OR with the read value from the MMIO register.
 *
 */
UINT64
EFIAPI
CpmMmioAndThenOr64 (
  IN       UINTN   Address,
  IN       UINT64  AndData,
  IN       UINT64   OrData
  )
{
  return CpmMmioWrite64 (Address, (CpmMmioRead64 (Address) & AndData) | OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Output a post code
 *
 * @param[in] Postcode  The post code to write
 *
 */
VOID
EFIAPI
CpmPostCode (
  IN       UINT32  Postcode
  )
{
  if (PcdGetBool (PcdAgesaTestPointEnable)) {
    if (PcdGet8 (PcdAgesaTestPointWidth) == 3) {
      CpmIoWrite32 (PcdGet16 (PcdIdsDebugPort), (UINT32)(Postcode + CpmTpBaseValue));   // AccessWidth32
    } else if (PcdGet8 (PcdAgesaTestPointWidth) == 2) {
      CpmIoWrite16 (PcdGet16 (PcdIdsDebugPort), (UINT16)(Postcode + CpmTpBaseValue));   // AccessWidth16
    } else {
      CpmIoWrite8 (PcdGet16 (PcdIdsDebugPort), (UINT8)(Postcode + CpmTpBaseValue));     // AccessWidth8
    }
  }
};

/*---------------------------------------------------------------------------------------*/
/**
 * Read an 8-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 *
 * @retval    PCI register value
 *
 */
UINT8
EFIAPI
CpmPciRead8 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  return AmdCpmTablePpi->CommonFunction.MmioRead8 (Address);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 16-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 *
 * @retval    PCI register value
 *
 */
UINT16
EFIAPI
CpmPciRead16 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  return AmdCpmTablePpi->CommonFunction.MmioRead16 (Address);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 32-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 *
 * @retval    PCI register value
 *
 */
UINT32
EFIAPI
CpmPciRead32 (
  IN      VOID    *This,
  IN      UINT8   Bus,
  IN      UINT8   Device,
  IN      UINT8   Function,
  IN      UINT16  Offset
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  return AmdCpmTablePpi->CommonFunction.MmioRead32 (Address);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write an 8-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmPciWrite8 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT8   Data
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioWrite8 (Address, Data);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 16-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmPciWrite16 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT16  Data
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioWrite16 (Address, Data);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 32-bit PCI register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmPciWrite32 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT32  Data
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioWrite32 (Address, Data);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit PCI register, performs a bitwise AND and writes the result back
 * to the 8-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAnd8 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT8   AndData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAnd8 (Address, AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit PCI register, performs a bitwise AND and writes the result back
 * to the 16-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAnd16 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT16  AndData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAnd16 (Address, AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit PCI register, performs a bitwise AND and writes the result back
 * to the 32-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAnd32 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT32  AndData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAnd32 (Address, AndData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit PCI register, performs a bitwise OR and writes the result back
 * to the 8-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciOr8 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT8   OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioOr8 (Address, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit PCI register, performs a bitwise OR and writes the result back
 * to the 16-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciOr16 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT16  OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioOr16 (Address, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit PCI register, performs a bitwise OR and writes the result back
 * to the 32-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciOr32 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT32  OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioOr32 (Address, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit PCI register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 8-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAndThenOr8 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT8   AndData,
  IN       UINT8   OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAndThenOr8 (Address, AndData, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 16-bit PCI register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 16-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAndThenOr16 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT16  AndData,
  IN       UINT16  OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAndThenOr16 (Address, AndData, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads a 32-bit PCI register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 32-bit PCI register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Bus       The bus number of PCI device
 * @param[in] Device    The device number of PCI device
 * @param[in] Function  The function number of PCI device
 * @param[in] Offset    The offset of PCI register
 * @param[in] AndData   The value to AND with the read value from the PCI register.
 * @param[in] OrData    The value to OR with the read value from the PCI register.
 *
 */
VOID
EFIAPI
CpmPciAndThenOr32 (
  IN       VOID    *This,
  IN       UINT8   Bus,
  IN       UINT8   Device,
  IN       UINT8   Function,
  IN       UINT16  Offset,
  IN       UINT32  AndData,
  IN       UINT32  OrData
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi;
  UINT32              Address;
  AmdCpmTablePpi = This;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + Offset;
  AmdCpmTablePpi->CommonFunction.MmioAndThenOr32 (Address, AndData, OrData);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Multi-Die Bus Number from AMD_CPM_CORE_TOPOLOGY_TABLE
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Socket: Socket Number
 * @param[in] Die:    Die Number
 * @param[in] Bridge: Bridge Number
 *
 * @retval            Bus Number
 *
 */
UINT8
CpmGetMultiDieBusNumber (
  IN       VOID                       *This,
  IN       UINT16                     Socket,
  IN       UINT16                     Die,
  IN       UINT16                     Bridge
  )
{
  AMD_CPM_COMMON_FUNCTION             *CommonFunctionPtr;
  AMD_CPM_CORE_TOPOLOGY_TABLE         *AmdCpmCoreTopologyPtr;
  AMD_CPM_CORE_TOPOLOGY_LIST          *TablePtr;
  UINT8                               Bus;

  Bus = 0xFF;
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  AmdCpmCoreTopologyPtr = CommonFunctionPtr->GetTablePtr (This, CPM_SIGNATURE_CORE_TOPOLOGY);

  if (AmdCpmCoreTopologyPtr) {
    TablePtr = &AmdCpmCoreTopologyPtr->CoreList[0];
    while (TablePtr->Socket != 0xFF ) {
      if ((TablePtr->Socket == Socket) && (TablePtr->Die == Die) && (TablePtr->Bridge == Bridge)) {
        DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-OK-Bus = 0x%02X\n", __FUNCTION__, TablePtr->Bus));
        return TablePtr->Bus;
      }
      TablePtr++;
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-FAIL-Bus = 0x%02X\n", __FUNCTION__, Bus));
  return Bus;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 8-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 *
 * @retval              SMN register value
 *
 */
UINT8
EFIAPI
CpmSmnRead8 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset
  )
{
  UINT8            Bus;
  UINT8            Data;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    Data = 0xFF;
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%02X\n", SmnAddr, Offset, Data));
    return Data;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  Data = CpmPciRead8 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)));
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%02X\n", SmnAddr, Offset, Data));
  return Data;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 16-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 *
 * @retval              SMN register value
 *
 */
UINT16
EFIAPI
CpmSmnRead16 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset
  )
{
  UINT8            Bus;
  UINT16           Data;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    Data = 0xFFFF;
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%04X\n", SmnAddr, Offset, Data));
    return Data;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  Data = CpmPciRead16 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)));
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%04X\n", SmnAddr, Offset, Data));
  return Data;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read a 32-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 *
 * @retval              SMN register value
 *
 */
UINT32
EFIAPI
CpmSmnRead32 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset
  )
{
  UINT8            Bus;
  UINT32           Data;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    Data = 0xFFFFFFFF;
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%08X\n", SmnAddr, Offset, Data));
    return Data;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, (SmnAddr + Offset));
  Data = CpmPciRead32 (This, Bus, 0, 0, 0xBC);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%08X\n", SmnAddr, Offset, Data));
  return Data;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 8-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmSmnWrite8 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT8   Data
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%02X\n", SmnAddr, Offset, Data));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciWrite8 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), Data);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%02X\n", SmnAddr, Offset, Data));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 16-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmSmnWrite16 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT16  Data
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%04X\n", SmnAddr, Offset, Data));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciWrite16 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), Data);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%04X\n", SmnAddr, Offset, Data));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write a 32-bit SMN register
 *
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] Data      The value to write
 *
 */
VOID
EFIAPI
CpmSmnWrite32 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT32  Data
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%08X\n", SmnAddr, Offset, Data));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, (SmnAddr + Offset));
  CpmPciWrite32 (This, Bus, 0, 0, 0xBC, Data);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X Data = 0x%08X\n", SmnAddr, Offset, Data));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit SMN register, performs a bitwise AND and writes the result back
 * to the 8-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAnd8 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT8   AndData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%02X\n", SmnAddr, Offset, AndData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciAnd8 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), AndData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%02X\n", SmnAddr, Offset, AndData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 16-bit SMN register, performs a bitwise AND and writes the result back
 * to the 16-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAnd16 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT16  AndData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%04X\n", SmnAddr, Offset, AndData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciAnd16 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), AndData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%04X\n", SmnAddr, Offset, AndData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 32-bit SMN register, performs a bitwise AND and writes the result back
 * to the 32-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAnd32 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT32  AndData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%08X\n", SmnAddr, Offset, AndData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, (SmnAddr + Offset));
  CpmPciAnd32 (This, Bus, 0, 0, 0xBC, AndData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%08X\n", SmnAddr, Offset, AndData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit SMN register, performs a bitwise OR and writes the result back
 * to the 8-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] OrData   The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnOr8 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT8   OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%02X\n", SmnAddr, Offset, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciOr8 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%02X\n", SmnAddr, Offset, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 16-bit SMN register, performs a bitwise OR and writes the result back
 * to the 16-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] OrData   The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnOr16 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT16  OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%04X\n", SmnAddr, Offset, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciOr16 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%04X\n", SmnAddr, Offset, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 32-bit SMN register, performs a bitwise OR and writes the result back
 * to the 32-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] OrData   The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnOr32 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT32  OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%08X\n", SmnAddr, Offset, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, (SmnAddr + Offset));
  CpmPciOr32 (This, Bus, 0, 0, 0xBC, OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X OrData = 0x%08X\n", SmnAddr, Offset, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 8-bit SMN register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 8-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 * @param[in] OrData    The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAndThenOr8 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT8   AndData,
  IN       UINT8   OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%02X OrData = 0x%02X\n", SmnAddr, Offset, AndData, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciAndThenOr8 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), AndData, OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%02X OrData = 0x%02X\n", SmnAddr, Offset, AndData, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 16-bit SMN register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 16-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 * @param[in] OrData    The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAndThenOr16 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT16  AndData,
  IN       UINT16  OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%04X OrData = 0x%04X\n", SmnAddr, Offset, AndData, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, ((SmnAddr + Offset) & 0xFFFFFFFC));
  CpmPciAndThenOr16 (This, Bus, 0, 0, (0xBC + (UINT8) ((SmnAddr + Offset) & 0x3)), AndData, OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%04X OrData = 0x%04X\n", SmnAddr, Offset, AndData, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads an 32-bit SMN register, performs a bitwise AND followed by a bitwise
 * inclusive OR, and writes the result back to the 32-bit SMN register.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of SMN register
 * @param[in] Die       The Die number of SMN register
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] SmnAddr   The SmnAddr number of SMN register
 * @param[in] Offset    The Offset of SMN register
 * @param[in] AndData   The value to AND with the read value from the SMN register.
 * @param[in] OrData    The value to OR with the read value from the SMN register.
 *
 */
VOID
EFIAPI
CpmSmnAndThenOr32 (
  IN       VOID    *This,
  IN       UINT16  Socket,
  IN       UINT16  Die,
  IN       UINT16  Bridge,
  IN       UINT32  SmnAddr,
  IN       UINT32  Offset,
  IN       UINT32  AndData,
  IN       UINT32  OrData
  )
{
  UINT8            Bus;

  Bus = CpmGetMultiDieBusNumber (This, Socket, Die, Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-FAIL-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%08X OrData = 0x%08X\n", SmnAddr, Offset, AndData, OrData));
    return;
  }

  CpmPciWrite32 (This, Bus, 0, 0, 0xB8, (SmnAddr + Offset));
  CpmPciAndThenOr32 (This, Bus, 0, 0, 0xBC, AndData, OrData);
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-OK-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " SmnAddr = 0x%08X Offset = 0x%08X AndData = 0x%08X OrData = 0x%08X\n", SmnAddr, Offset, AndData, OrData));
  return;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read CPUID Family/Model/Stepping and Package Type
 *
 * @param[out] This                     The pointer of CPM Table Ppi or Protocol
 * @param[out] CpuidFamilyModelStepping CPUID Family/Model/Stepping
 * @param[out] PkgType                  The package type
 *
 */
VOID
EFIAPI
CpmCpuidRead (
  IN       VOID     *This,
     OUT   UINT32   *CpuidFamilyModelStepping,
     OUT   UINT32   *PkgType
  )
{
  CPUID_DATA        CpmCpuid;
  UINT32            CpuIdEax;

  CpmCpuidRawRead (0x80000001, &CpmCpuid);
  CpuIdEax = CpmCpuid.EAX_Reg;

  if (CpuidFamilyModelStepping) {
    *CpuidFamilyModelStepping = CpuIdEax;
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-CpuidFamilyModelStepping = 0x%08X\n", __FUNCTION__, *CpuidFamilyModelStepping));
  }
  if (PkgType) {
    *PkgType = (UINT32) (CpmCpuid.EBX_Reg >> 28) & 0xF;         // Bit[31:28]
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-PkgType = 0x%08X\n", __FUNCTION__, *PkgType));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get PCIE End Point Device ID under the bridge
 *
 * @param[in] This        The pointer of CPM Table Ppi or Protocol
 * @param[in] Device      The device number of PCIe bridge
 * @param[in] Function    The function number of PCIe bridge
 *
 * @retval                PCIE End Point Device ID
 * @retval    0xFFFFFFFF  There is no PCIE End Point Device under the bridge
 *
 */
UINT32
EFIAPI
CpmGetPcieEndPointDeviceID (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi = This;
  UINT32              Address;
  UINT32              BridgeAddress;
  UINT32              Value;
  UINT8               Bus;
  UINT8               BusSec;
  UINT8               BusTemp;

  BridgeAddress = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Device << 15) + (Function << 12) + 0x19;

  Bus = AmdCpmTablePpi->CommonFunction.MmioRead8 (BridgeAddress);             // Offset 0x19
  BusSec = AmdCpmTablePpi->CommonFunction.MmioRead8 (BridgeAddress + 1);      // Offset 0x1A

  if (Bus == 0xFF) {
    Value = 0xFFFFFFFF;
  } else {
    BusTemp = 0x1F;
    AmdCpmTablePpi->CommonFunction.MmioWrite8 (BridgeAddress, BusTemp);       // Offset 0x19
    AmdCpmTablePpi->CommonFunction.MmioWrite8 (BridgeAddress + 1, BusTemp);   // Offset 0x1A
    Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (BusTemp << 20);
    Value = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address);
    AmdCpmTablePpi->CommonFunction.MmioWrite8 (BridgeAddress, Bus);           // Offset 0x19
    AmdCpmTablePpi->CommonFunction.MmioWrite8 (BridgeAddress + 1, BusSec);    // Offset 0x1A
  }

  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-Device = 0x%02X Function = 0x%02X DeviceID = 0x%08X\n", __FUNCTION__, Device, Function, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check Whether there is a PCIE device under a bridge
 *
 * Note: It's only available after PCI enumerate.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of PCIe bridge
 * @param[in] Die       The Die number of PCIe bridge
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] Device    The device number of PCIe bridge
 * @param[in] Function  The function number of PCIe bridge
 *
 * @retval    Bit0 = 1  There is a PCI device under the bridge
 * @retval    Bit2 = 1  This device can support Clock Power Management and Clock Power Management is enabled
 * @retval    Bit3 = 1  This device can support L1SS and L1SS is enabled
 * @retval    0         There is no PCI device under the bridge
 *
 */
UINT8
EFIAPI
CpmCheckPcieDevice (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi = This;
  UINT32              Address;
  UINT32              Value32;
  UINT8               Bus;
  UINT8               Status;
  UINT32              Offset;
  UINT8               Value8;

  Bus = CpmGetMultiDieBusNumber (This, (UINT16)Socket, (UINT16)Die, (UINT16)Bridge);
  Status = 0;
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = 0x%02X\n", Device, Function, Status));
    return Status;
  }
  Offset = 0;
  Value8 = 0;
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12);
  Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + 0x08);                 // Check ClassCode
  if (((Value32 >> 16) & 0xFFFF) != 0x0604) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = 0x%02X\n", Device, Function, Status));
    return Status;
  }
  Bus = AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + 0x19);                      // Check the bus number
  if ((Bus == 0x00) || (Bus == 0xFF)) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = 0x%02X\n", Device, Function, Status));
    return Status;
  }
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20);
  Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + 0x08);                 // Check ClassCode
  if ((Value32 != 0) && (Value32 != 0xFFFFFFFF)) {
    // Device exists, set Bit0 = 1
    Status = 1;
    Offset = (UINT32) AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + 0x34);              // Capabilities Pointer
    while ((Offset != 0) && (Offset != 0xFF)) {
      Value8 = AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + Offset);                   // Cap ID
      if (Value8 != 0x10) {
        Offset = (UINT32) AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + Offset + 0x01); // Next Capability Pointer
      } else {
        Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + Offset + 0x0C);        // Capabilities Register
        if (Value32 & BIT18) {
          Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + Offset + 0x10);      // Control Register
          if (Value32 & BIT8) {
            // Device support Clock Power Management and Clock Power Management is enabled, set Bit2 = 1
            Status |= 4;
          }
        }
        break;
      }
    }
    Offset = 0x100;                                                                     // Extended Capabilities Pointer
    while ((Offset >= 0x100) && (Offset <= 0xFF8)) {
      Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + Offset);           // Extended Cap ID
      if ((Value32 & 0xFFFF) != 0x1E) {
        Offset = (Value32 >> 20) & 0xFFF;                                               // Next Capability Pointer
      } else {
        Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + Offset + 0x04);  // Capabilities Register
        if (Value32 & BIT4) {
          Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + Offset + 0x08);// Control Register
          if (Value32 & 0xF) {
            // Device support L1SS and L1SS is enabled, set Bit3 = 1
            Status |= 8;
          }
        }
        break;
      }
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-4-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = 0x%02X\n", Device, Function, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check Whether there is a PCIE VGA under a bridge.
 *
 * Note: It's only available after PCI enumerate.
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] Socket    The Socket number of PCIE bridge
 * @param[in] Die       The Die number of PCIE bridge
 * @param[in] Bridge    The Bridge number of SMN register
 * @param[in] Device    The device number of PCIE bridge
 * @param[in] Function  The function number of PCIE bridge
 *
 * @retval    TRUE      There is a PCIE VGA device under the bridge
 * @retval    FALSE     There is no PCIE VGA device under the bridge
 *
 */
BOOLEAN
EFIAPI
CpmCheckPcieVga (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  )
{
  AMD_CPM_TABLE_PPI   *AmdCpmTablePpi = This;
  UINT32              Address;
  UINT32              Value32;
  UINT8               Bus;
  UINT8               EndBus;

  Bus = CpmGetMultiDieBusNumber (This, (UINT16)Socket, (UINT16)Die, (UINT16)Bridge);
  if (Bus == 0xFF) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = FALSE\n", Device, Function));
    return FALSE;
  }
  Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12);
  Bus = AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + 0x19);                      // Check the bus number
  EndBus = AmdCpmTablePpi->CommonFunction.MmioRead8 (Address + 0x1A);                   // Check the end of bus number
  if ((Bus == 0x00) || (Bus == 0xFF) || (EndBus < Bus)) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = FALSE\n", Device, Function));
    return FALSE;
  }
  for ( ; Bus <= EndBus; Bus++) {
    Address = AmdCpmTablePpi->MainTablePtr->PcieMemIoBaseAddr + (Bus << 20);
    Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (Address + 0x08);               // Check ClassCode
    if ((Value32 != 0) && (Value32 != 0xFFFFFFFF) && ((Value32 >> 24) == 0x03)) {
      // VGA Device exists, return TRUE
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
      DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = TRUE\n", Device, Function));
      return TRUE;
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-4-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " Device = 0x%02X Function = 0x%02X Status = FALSE\n", Device, Function));
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Detect the device
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] DeviceId  The device Id
 * @param[out] Status   The status of detection bits
 *
 * @retval    TRUE      Device is found
 * @retval    FALSE     Device is not found
 *
 */
BOOLEAN
EFIAPI
CpmDetectDevice (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId,
     OUT   UINT8                       *Status
  )
{
  AMD_CPM_GPIO_DEVICE_DETECTION_TABLE *DetectionTablePtr;
  AMD_CPM_TABLE_PPI       *CpmTablePpiPtr;
  UINT8                   Index;
  UINT8                   Detected;
  UINT8                   GpioDeviceId;
  UINT8                   GpioStatus;
  BOOLEAN                 Pin1Detected;
  BOOLEAN                 Pin2Detected;
  BOOLEAN                 Pin3Detected;

  CpmTablePpiPtr = This;
  Detected = 0;
  GpioStatus = 0;

  DetectionTablePtr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_DETECTION);

  if (DetectionTablePtr) {
    for (Index = 0; Index < AMD_GPIO_DEVICE_DETECT_SIZE; Index ++) {
      GpioDeviceId = DetectionTablePtr->DeviceDetectionList[Index].DeviceId;
      if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
        break;
      }
      if (GpioDeviceId == DeviceId ) {
        if (DetectionTablePtr->DeviceDetectionList[Index].Type == CPM_TYPE_GPIO_1) {
          Pin1Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum1) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value1);
          Detected = Pin1Detected;
          GpioStatus = Pin1Detected ? 1 : 0;
          break;
        } else if (DetectionTablePtr->DeviceDetectionList[Index].Type == CPM_TYPE_GPIO_2) {
          Pin1Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum1) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value1);
          Pin2Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum2) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value2);
          Detected = Pin1Detected && Pin2Detected;
          GpioStatus = (Pin1Detected ? 1 : 0) | (Pin2Detected ? 2 : 0);
          break;
        } else if (DetectionTablePtr->DeviceDetectionList[Index].Type == CPM_TYPE_GPIO_3) {
          Pin1Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum1) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value1);
          Pin2Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum2) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value2);
          Pin3Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum3) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value3);
          Detected = Pin1Detected && Pin2Detected && Pin3Detected;
          GpioStatus = (Pin1Detected ? 1 : 0) | (Pin2Detected ? 2 : 0) | (Pin3Detected ? 4 : 0);
          break;
        } else if (DetectionTablePtr->DeviceDetectionList[Index].Type == CPM_TYPE_GPIO_2_OR) {
          Pin1Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum1) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value1);
          Pin2Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum2) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value2);
          Detected = Pin1Detected || Pin2Detected;
          GpioStatus = (Pin1Detected ? 1 : 0) | (Pin2Detected ? 2 : 0);
          break;
        } else if (DetectionTablePtr->DeviceDetectionList[Index].Type == CPM_TYPE_GPIO_3_OR) {
          Pin1Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum1) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value1);
          Pin2Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum2) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value2);
          Pin3Detected = (CpmTablePpiPtr->CommonFunction.GetGpio (CpmTablePpiPtr, DetectionTablePtr->DeviceDetectionList[Index].PinNum3) ==
                          DetectionTablePtr->DeviceDetectionList[Index].Value3);
          Detected = Pin1Detected || Pin2Detected || Pin3Detected;
          GpioStatus = (Pin1Detected ? 1 : 0) | (Pin2Detected ? 2 : 0) | (Pin3Detected ? 4 : 0);
          break;
        }
      }
    }
  }
  if (Status) {
    *Status = GpioStatus;
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-DeviceId = 0x%02X Detected = 0x%02X GpioStatus = 0x%02X\n", __FUNCTION__, DeviceId, Detected, GpioStatus));
  return Detected;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Power On/Off the device
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] DeviceId  The device Id
 * @param[in] State     0: Power Off. 1: Power On
 *
 */
VOID
EFIAPI
CpmPowerOnDevice (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId,
  IN       UINT8                       State
  )
{
  AMD_CPM_GPIO_DEVICE_POWER_TABLE     *PowerTablePtr;
  UINT8                               Index;
  UINT8                               GpioDeviceId;

  PowerTablePtr       = ((AMD_CPM_TABLE_PPI*)This)->CommonFunction.GetTablePtr (This, CPM_SIGNATURE_GPIO_DEVICE_POWER);

  for (Index = 0; Index < AMD_GPIO_DEVICE_POWER_SIZE; Index ++) {
    GpioDeviceId = PowerTablePtr->DevicePowerList[Index].DeviceId;
    if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
      break;
    }
    if (PowerTablePtr->DevicePowerList[Index].DeviceId == DeviceId && PowerTablePtr->DevicePowerList[Index].Mode == State) {
      switch (PowerTablePtr->DevicePowerList[Index].Type) {
      case CPM_POWER_SET:
        ((AMD_CPM_TABLE_PPI*)This)->CommonFunction.SetGpio (
                            This,
                            PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin,
                            PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Value
                            );
        break;
      case CPM_POWER_WAIT:
        while (((AMD_CPM_TABLE_PPI*)This)->CommonFunction.GetGpio (This, PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Pin) !=
               PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Value) {
        }
        break;
      case CPM_POWER_DELAY:
      case CPM_PT_POWER_DELAY:
        ((AMD_CPM_TABLE_PPI*)This)->CommonFunction.Stall (This, PowerTablePtr->DevicePowerList[Index].Config.Stall);
        break;
      }
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-DeviceId = 0x%02X State = 0x%02X\n", __FUNCTION__, DeviceId, State));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the config setting of the device
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 * @param[in] DeviceId  The device Id
 *
 * @retval    0         Device off
 * @retval    1         Device on
 */
UINT8
EFIAPI
CpmGetDeviceConfig (
  IN       VOID                        *This,
  IN       UINT8                       DeviceId
  )
{
  AMD_CPM_GPIO_DEVICE_CONFIG_TABLE    *ConfigTablePtr;
  UINT8                               Index;
  UINT8                               GpioDeviceId;
  UINT8                               Status;

  ConfigTablePtr = ((AMD_CPM_TABLE_PPI*)This)->CommonFunction.GetTablePtr (This, CPM_SIGNATURE_GPIO_DEVICE_CONFIG);
  Status = 1;

  for (Index = 0; Index < AMD_GPIO_DEVICE_SIZE; Index ++) {
    GpioDeviceId = ConfigTablePtr->DeviceList[Index].DeviceId;
    if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
      break;
    }
    if (ConfigTablePtr->DeviceList[Index].DeviceId == DeviceId) {
      Status = ConfigTablePtr->DeviceList[Index].Config.Setting.Enable;
      break;
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-DeviceId = 0x%02X Status = 0x%02X\n", __FUNCTION__, DeviceId, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Wait KBC Input Buffer Empty
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 *
 * @retval        EFI_SUCCESS    Input buffer has been empty successfully
 * @retval        EFI_ERROR      Empty input buffer failed (see error for more details)
 *
 */
EFI_STATUS
EFIAPI
CpmKbcWaitInputBufferEmpty (
  IN       UINT16 BaseAddr
  )
{
  EFI_STATUS      Status;
  UINT32          TimeOut;
  UINT8           Data8;

  Status = EFI_DEVICE_ERROR;

  for (TimeOut = 0; TimeOut < 65536; TimeOut++) {
    Data8 = CpmIoRead8 (BaseAddr + 0x04);
    if (!(Data8 & BIT1)) {
      Status = EFI_SUCCESS;
      break;
    }
    Data8 = CpmIoRead8 (0x64);      // Flush it for AC/DC issue
    Data8 = CpmIoRead8 (0xCD6);     // Dummy read for delay
    Data8 = CpmIoRead8 (0xCD6);
    Data8 = CpmIoRead8 (0xCD6);
    Data8 = CpmIoRead8 (0xCD6);
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-BaseAddr = 0x%04X Status = %r\n", __FUNCTION__, BaseAddr, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Wait KBC Output Buffer Full
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 *
 * @retval        EFI_SUCCESS    Output Buffer has been fulled successfully
 * @retval        EFI_ERROR      Full Output Buffer failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcWaitOutputBufferFull (
  IN       UINT16 BaseAddr
  )
{
  EFI_STATUS      Status;
  UINT32          TimeOut;
  UINT8           Data8;

  Status = EFI_DEVICE_ERROR;

  for (TimeOut = 0; TimeOut < 65536; TimeOut++) {
    Data8 = CpmIoRead8 (BaseAddr + 0x04);
    if (Data8 & BIT0) {
      Status = EFI_SUCCESS;
      break;
    }
    Data8 = CpmIoRead8 (0xCD6);     // Dummy read for delay
    Data8 = CpmIoRead8 (0xCD6);
    Data8 = CpmIoRead8 (0xCD6);
    Data8 = CpmIoRead8 (0xCD6);
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-BaseAddr = 0x%04X Status = %r\n", __FUNCTION__, BaseAddr, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Wait KBC Output Buffer Empty
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 *
 * @retval        EFI_SUCCESS    Output Buffer has been Empty successfully
 * @retval        EFI_ERROR      Empty Output Buffer failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcWaitOutputBufferEmpty (
  IN       UINT16 BaseAddr
  )
{
  EFI_STATUS      Status;
  UINT32          TimeOut;
  UINT8           Data8;

  Status = EFI_DEVICE_ERROR;

  for (TimeOut = 0; TimeOut < 65536; TimeOut++) {
    Data8 = CpmIoRead8 (BaseAddr + 0x04);
    if (Data8 & BIT0) {
      Data8 = CpmIoRead8 (0x60);
      Data8 = CpmIoRead8 (0xCD6);     // Dummy read for delay
      Data8 = CpmIoRead8 (0xCD6);
      Data8 = CpmIoRead8 (0xCD6);
      Data8 = CpmIoRead8 (0xCD6);
    } else {
      Status = EFI_SUCCESS;
      break;
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-BaseAddr = 0x%04X Status = %r\n", __FUNCTION__, BaseAddr, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read KBC register
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 * @param[in] Command   Command to send to KBC controller
 * @param[in] Data      Data to send to KBC controller
 * @param[in] Value      Value to read from KBC controller
 *
 * @retval        EFI_SUCCESS    Read KBC data successfully
 * @retval        EFI_ERROR      Read KBC data failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcRead (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data,
     OUT   UINT8                       *Value
  )
{
  EFI_STATUS  Status;

  Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Value = N/A Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
    return Status;
  }

  CpmIoWrite8 (BaseAddr + 0x04, Command);

  if (Data) {
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Value = N/A Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
      return Status;
    }
    CpmIoWrite8 (BaseAddr, *Data);
  }

  if (Value) {
    Status = CpmKbcWaitOutputBufferFull (BaseAddr);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Value = N/A Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
      return Status;
    }
    *Value = CpmIoRead8 (BaseAddr);
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-4-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Value = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, *Value, Status));
  } else {
    Status = EFI_INVALID_PARAMETER;
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-5-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Value = N/A Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
  }
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read KBC register Dummy
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 * @param[in] Command   Command to send to KBC controller
 * @param[in] Data      Data to send to KBC controller
 * @param[in] Value      Value to read from KBC controller
 *
 * @retval        EFI_SUCCESS    Read KBC data successfully
 * @retval        EFI_ERROR      Read KBC data failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcReadDummy (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data,
     OUT   UINT8                       *Value
  )
{
      if (BaseAddr == 0x662 && Data && Command == 0x80) {
        if (*Data == 0xAC) {
          *Value = 0xE1;
          return EFI_SUCCESS;
        } else if (*Data == 0xAF) {
          *Value = 0x68;
          return EFI_SUCCESS;
        } else if (*Data == 0xCF) {
          *Value = 0x00;
          return EFI_SUCCESS;
        }
      }
      if (BaseAddr == 0x662 && Data && Command == 0x81) {
        if (*Data == 0xAC) {
          return EFI_SUCCESS;
        } else if (*Data == 0xAF) {
          return EFI_SUCCESS;
        } else if (*Data == 0xCF) {
          return EFI_SUCCESS;
        }
      }

  if ((BaseAddr == 0x662 || BaseAddr == 0x60) && Value) {
    *Value = 0xFF;
    return EFI_SUCCESS;
  } else {
    return CpmKbcRead(BaseAddr, Command, Data, Value);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write KBC register
 *
 * @param[in] BaseAddr  Base address of KBC or EC register
 * @param[in] Command   Command to send to KBC controller
 * @param[in] Data      Data to send to KBC controller
 *
 * @retval        EFI_SUCCESS    Write KBC controller successfully
 * @retval        EFI_ERROR      Write KBC controller failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcWrite (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data
  )
{
  EFI_STATUS  Status;

  Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
    return Status;
  }

  CpmIoWrite8 (BaseAddr + 0x04, Command);

  if (Data) {
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
      return Status;
    }
    CpmIoWrite8 (BaseAddr, *Data);
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
  }

  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-BaseAddr = 0x%04X Command = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Data, Status));
  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write KBC register Dummy
 *
 * @param[in] BaseAddr  Base address of EC register
 * @param[in] Command   Command to send to EC controller
 * @param[in] Offset    EC RAM Offset to send to EC controller
 * @param[in] Data      Data to send to EC controller
 *
 * @retval        EFI_SUCCESS    Write EC controller successfully
 * @retval        EFI_ERROR      Write EC controller failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmKbcWriteDummy (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Data
  )
{
  if (BaseAddr == 0x662 || BaseAddr == 0x60) {
    return EFI_SUCCESS;
  } else {
    return CpmKbcWrite(BaseAddr, Command, Data);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write EC RAM register
 *
 * @param[in] BaseAddr  Base address of EC register
 * @param[in] Command   Command to send to EC controller
 * @param[in] Offset    EC RAM Offset to send to EC controller
 * @param[in] Data      Data to send to EC controller
 *
 * @retval        EFI_SUCCESS    Write EC controller successfully
 * @retval        EFI_ERROR      Write EC controller failed (see error for more details)
 */
EFI_STATUS
EFIAPI
CpmEcRamWrite (
  IN       UINT16                      BaseAddr,
  IN       UINT8                       Command,
  IN       UINT8                       *Offset,
  IN       UINT8                       *Data
  )
{
  EFI_STATUS  Status;

  Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-1-BaseAddr = 0x%04X Command = 0x%02X Offset = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Offset, *Data, Status));
    return Status;
  }

  CpmIoWrite8 (BaseAddr + 0x04, Command);

  if (Data) {
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-2-BaseAddr = 0x%04X Command = 0x%02X Offset = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Offset, *Data, Status));
      return Status;
    }
    CpmIoWrite8 (BaseAddr, *Offset);
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-3-BaseAddr = 0x%04X Command = 0x%02X Offset = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Offset, *Data, Status));
      return Status;
    }
    CpmIoWrite8 (BaseAddr, *Data);
    Status = CpmKbcWaitInputBufferEmpty (BaseAddr);
  }

  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End-4-BaseAddr = 0x%04X Command = 0x%02X Offset = 0x%02X Data = 0x%02X Status = %r\n", __FUNCTION__, BaseAddr, Command, *Offset, *Data, Status));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Convert Event pin number to Asl name
 *
 * @param[in]     EventPin       EVENT Pin Number
 *
 * @retval        Event Asl name
 *
 */
UINT32
EFIAPI
CpmEventAslNameConverter (
  IN       UINT8                       EventPin
  )
{
  UINT32                          AslName;
  if ((EventPin & 0xF) < 0xA) {
    AslName = 0x3000 + ((EventPin & 0xF) << 8);
  } else {
    AslName = 0x4000 + (((EventPin & 0xF) - 0x9) << 8);
  }
  if (((EventPin >> 4) & 0xF) < 0xA) {
    AslName |= 0x30 + ((EventPin >> 4) & 0xF);
  } else {
    AslName |= 0x40 + (((EventPin >> 4) & 0xF) - 0x9);
  }
  return AslName;
}
/*---------------------------------------------------------------------------------------*/
/**
 * Register CPM base functions
 *
 * @param[in] This      The pointer of CPM Table Ppi or Protocol
 *
 */
VOID
EFIAPI
CpmRegisterBaseIo (
  IN       VOID                        *This
  )
{
  AMD_CPM_COMMON_FUNCTION             *CommonFunctionPtr;

  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-Start\n", __FUNCTION__));
  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;

  CommonFunctionPtr->IoRead8          = CpmIoRead8;
  CommonFunctionPtr->IoRead16         = CpmIoRead16;
  CommonFunctionPtr->IoRead32         = CpmIoRead32;
  CommonFunctionPtr->IoWrite8         = CpmIoWrite8;
  CommonFunctionPtr->IoWrite16        = CpmIoWrite16;
  CommonFunctionPtr->IoWrite32        = CpmIoWrite32;
  CommonFunctionPtr->MmioRead8        = CpmMmioRead8;
  CommonFunctionPtr->MmioRead16       = CpmMmioRead16;
  CommonFunctionPtr->MmioRead32       = CpmMmioRead32;
  CommonFunctionPtr->MmioRead64       = CpmMmioRead64;
  CommonFunctionPtr->MmioWrite8       = CpmMmioWrite8;
  CommonFunctionPtr->MmioWrite16      = CpmMmioWrite16;
  CommonFunctionPtr->MmioWrite32      = CpmMmioWrite32;
  CommonFunctionPtr->MmioWrite64      = CpmMmioWrite64;
  CommonFunctionPtr->MmioAnd8         = CpmMmioAnd8;
  CommonFunctionPtr->MmioAnd16        = CpmMmioAnd16;
  CommonFunctionPtr->MmioAnd32        = CpmMmioAnd32;
  CommonFunctionPtr->MmioAnd64        = CpmMmioAnd64;
  CommonFunctionPtr->MmioOr8          = CpmMmioOr8;
  CommonFunctionPtr->MmioOr16         = CpmMmioOr16;
  CommonFunctionPtr->MmioOr32         = CpmMmioOr32;
  CommonFunctionPtr->MmioOr64         = CpmMmioOr64;
  CommonFunctionPtr->MmioAndThenOr8   = CpmMmioAndThenOr8;
  CommonFunctionPtr->MmioAndThenOr16  = CpmMmioAndThenOr16;
  CommonFunctionPtr->MmioAndThenOr32  = CpmMmioAndThenOr32;
  CommonFunctionPtr->MmioAndThenOr64  = CpmMmioAndThenOr64;
  CommonFunctionPtr->MsrRead          = CpmMsrRead;
  CommonFunctionPtr->MsrWrite         = CpmMsrWrite;
  CommonFunctionPtr->PciRead8         = CpmPciRead8;
  CommonFunctionPtr->PciRead16        = CpmPciRead16;
  CommonFunctionPtr->PciRead32        = CpmPciRead32;
  CommonFunctionPtr->PciWrite8        = CpmPciWrite8;
  CommonFunctionPtr->PciWrite16       = CpmPciWrite16;
  CommonFunctionPtr->PciWrite32       = CpmPciWrite32;
  CommonFunctionPtr->PciAnd8          = CpmPciAnd8;
  CommonFunctionPtr->PciAnd16         = CpmPciAnd16;
  CommonFunctionPtr->PciAnd32         = CpmPciAnd32;
  CommonFunctionPtr->PciOr8           = CpmPciOr8;
  CommonFunctionPtr->PciOr16          = CpmPciOr16;
  CommonFunctionPtr->PciOr32          = CpmPciOr32;
  CommonFunctionPtr->PciAndThenOr8    = CpmPciAndThenOr8;
  CommonFunctionPtr->PciAndThenOr16   = CpmPciAndThenOr16;
  CommonFunctionPtr->PciAndThenOr32   = CpmPciAndThenOr32;
  CommonFunctionPtr->SmnRead8         = CpmSmnRead8;
  CommonFunctionPtr->SmnRead16        = CpmSmnRead16;
  CommonFunctionPtr->SmnRead32        = CpmSmnRead32;
  CommonFunctionPtr->SmnWrite8        = CpmSmnWrite8;
  CommonFunctionPtr->SmnWrite16       = CpmSmnWrite16;
  CommonFunctionPtr->SmnWrite32       = CpmSmnWrite32;
  CommonFunctionPtr->SmnAnd8          = CpmSmnAnd8;
  CommonFunctionPtr->SmnAnd16         = CpmSmnAnd16;
  CommonFunctionPtr->SmnAnd32         = CpmSmnAnd32;
  CommonFunctionPtr->SmnOr8           = CpmSmnOr8;
  CommonFunctionPtr->SmnOr16          = CpmSmnOr16;
  CommonFunctionPtr->SmnOr32          = CpmSmnOr32;
  CommonFunctionPtr->SmnAndThenOr8    = CpmSmnAndThenOr8;
  CommonFunctionPtr->SmnAndThenOr16   = CpmSmnAndThenOr16;
  CommonFunctionPtr->SmnAndThenOr32   = CpmSmnAndThenOr32;
  CommonFunctionPtr->ReadTsc          = CpmReadTsc;
  CommonFunctionPtr->BitScanForward   = CpmBitScanForward;
  CommonFunctionPtr->BitScanReverse   = CpmBitScanReverse;
  CommonFunctionPtr->CpuidRawRead     = CpmCpuidRawRead;
  CommonFunctionPtr->CpuidRead        = CpmCpuidRead;
  CommonFunctionPtr->PostCode         = CpmPostCode;
  CommonFunctionPtr->CheckPcieDevice  = CpmCheckPcieDevice;
  CommonFunctionPtr->CheckPcieVga     = CpmCheckPcieVga;
  CommonFunctionPtr->DetectDevice     = CpmDetectDevice;
  CommonFunctionPtr->PowerOnDevice    = CpmPowerOnDevice;
  CommonFunctionPtr->GetDeviceConfig  = CpmGetDeviceConfig;
  CommonFunctionPtr->KbcRead          = CpmKbcRead;
  CommonFunctionPtr->KbcWrite         = CpmKbcWrite;
  CommonFunctionPtr->EcRamWrite       = CpmEcRamWrite;
  CommonFunctionPtr->GetPcieEndPointDeviceID  = CpmGetPcieEndPointDeviceID;
  CommonFunctionPtr->GetMultiDieBusNumber     = CpmGetMultiDieBusNumber;
  CommonFunctionPtr->EventAslNameConverter    = CpmEventAslNameConverter;
  DEBUG((DEBUG_INFO, "  LIB-BAS-%a-End\n", __FUNCTION__));
  return;
}
