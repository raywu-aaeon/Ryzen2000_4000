//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file AmiChipsetIoLib.c
    This file contains implementation of Ami Chipset Io Library

*/

//======================================================================
// Module specific Includes
#include <AmiChipsetIoLib.h>
#include <Uefi/UefiMultiPhase.h>
#include <Pi/PiMultiPhase.h>
#include <AmiDxeLib.h>
#include <IndustryStandard/Pci22.h>

//======================================================================
// Produced Protocols

//======================================================================
// Variable Declaration

//======================================================================
// GUID Definitions

//======================================================================
// Function Declarations

//======================================================================
// Function Definitions

//----------------------------------------------------------------------

/**
    This function searches the PCI address space for the PCI
    device specified for a particular capability ID and
    returns the Capability ID Offset if one found

    @param PciAddress - The PCI-E MMIO address of the register.
    @param CapId - CAPID to search for,
                   CAPID list:
                     0x01 = PCI Power Management Interface
                     0x10 = PCI Express Capability

    @retval Capability ID Offset if one found.
            Otherwise returns 0
**/
UINT8
EFIAPI
FindCapPtr (
    IN UINTN        PciAddress,
    IN UINT8        CapId
  )
{
  UINT8     StatusReg;
  UINT8     HeaderTypeReg;
  UINT8     NextCapReg;
  UINT8     GetCapId;

  //
  // Return 0 if the device does not exist or does not have
  // the capabilities list
  //
  StatusReg = MmioRead8 (PciAddress + PCI_PRIMARY_STATUS_OFFSET);

  if ((StatusReg == 0xFF) || ((StatusReg & BIT4) == 0)) {
    return 0;
  }

  //
  // Assign Capabilities List Pointer
  // For CardBus bridge, it should be 0x14. Otherwise, it should be 0x34
  //
  HeaderTypeReg = MmioRead8 (PciAddress + PCI_HEADER_TYPE_OFFSET) & HEADER_LAYOUT_CODE;

  if (HeaderTypeReg == HEADER_TYPE_CARDBUS_BRIDGE) {
    NextCapReg = 0x14;
  } else {
    NextCapReg = 0x34;
  }

  //
  // Search for the matched Cap ID
  //
  for(;;)
  {
    NextCapReg = MmioRead8 (PciAddress + NextCapReg);

    if (NextCapReg == 0) {
      return 0;
    }

    GetCapId = MmioRead8 (PciAddress + NextCapReg);
    if (GetCapId == CapId) {
      return NextCapReg;
    }

    NextCapReg ++;
  }
}

/**
    This function Search and return the offset of desired
    PCI Express Capability ID

    @param PciAddress - The PCI-E MMIO address of the register.
    @param CapId - CAPID to search for,
                   CAPID list:
                   0x0001 = Advanced Error Reporting Capability
                   0x0002 = Virtual Channel Capability
                   0x0003 = Device Serial Number Capability
                   0x0004 = Power Budgeting Capability

    @retval Extended Capability ID Offset if one found,
            Otherwise returns 0
**/
UINT16
EFIAPI
FindExtendedCapPtr (
    IN UINTN        PciAddress,
    IN UINT16       CapId
  )
{
  UINT16    NextCapReg;
  UINT16    GetCapId;

  NextCapReg = 0x100;

  //
  // Return 0 if the device does not exist
  //
  if (MmioRead8 (PciAddress) == 0xFF) {
    return 0;
  }

  for(;;)
  {
    GetCapId = MmioRead16 (PciAddress + NextCapReg);

    if (GetCapId == CapId) {
      return NextCapReg;
    }

    NextCapReg = MmioRead16 (PciAddress + NextCapReg + 2);

    NextCapReg >>= 4;

    if (NextCapReg == 0) {
      return 0;
    }
  }
}

/**
    This function writes an 8bit value to a specific I/O port
    and writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save ProtocOl
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param Value8         - An 8 Bit Value to write.

    @retval VOID
**/
VOID 
EFIAPI
WriteIo8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            Value8 )
{
    IoWrite8 ( IoBaseReg16, Value8 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                   EfiBootScriptWidthUint8, \
                                   IoBaseReg16, \
                                   1, \
                                   &Value8 );
}

/**
    This function writes a 16bit value to a specific I/O port
    and writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param Value16        - A 16 Bit Value to write.

    @retval VOID
**/
VOID 
EFIAPI
WriteIo16S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           Value16 )
{
    IoWrite16 ( IoBaseReg16, Value16 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                   EfiBootScriptWidthUint16,\
                                   IoBaseReg16, \
                                   1, \
                                   &Value16 );
}

/**
    This function writes a 32bit value to a specific I/O port
    and writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param Value32        - a 32 Bit Value to write.

    @retval VOID
**/
VOID 
EFIAPI
WriteIo32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           Value32 )
{
    IoWrite32 ( IoBaseReg16, Value32 );

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                   EfiBootScriptWidthUint32,\
                                   IoBaseReg16, \
                                   1, \
                                   &Value32 );
}

/**
    This function reads an 8bit value from a specific I/O port, 
    then applies Set/Reset masks, and writes it back, then
    writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param SetBit8        - Mask of 8bits to set (1 = Set)
    @param ResetBit8      - Mask of 8bits to reset (1 = Reset)

    @retval VOID
**/
VOID 
EFIAPI
RwIo8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{   

    RW_IO8 ( IoBaseReg16, SetBit8, ResetBit8 );

    ResetBit8 = ~ResetBit8;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                        EfiBootScriptWidthUint8, \
                                        IoBaseReg16, \
                                        &SetBit8, \
                                        &ResetBit8 );
}

/**
    This function reads a 16bit value from a specific I/O port, 
    then applies Set/Reset masks, and writes it back, then
    writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param SetBit16       - Mask of 16bits to set (1 = Set)
    @param ResetBit16     - Mask of 16bits to reset (1 = Reset)

    @retval VOID
**/
VOID 
EFIAPI
RwIo16S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{   
    RW_IO16 ( IoBaseReg16, SetBit16, ResetBit16 );

    ResetBit16 = ~ResetBit16;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                        EfiBootScriptWidthUint16, \
                                        IoBaseReg16, \
                                        &SetBit16, \
                                        &ResetBit16 );
}

/**
    This function reads a 32bit value from a specific I/O port, 
    then applies Set/Reset masks, and writes it back, then
    writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBaseReg16    - A 16 Bit I/O Port Address
    @param SetBit32       - Mask of 32bits to set (1 = Set)
    @param ResetBit32     - Mask of 32bits to reset (1 = Reset)

    @retval VOID
**/
VOID 
EFIAPI
RwIo32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBaseReg16,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{   
    RW_IO32 ( IoBaseReg16, SetBit32, ResetBit32 );

    ResetBit32 = ~ResetBit32;

    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                        EfiBootScriptWidthUint32, \
                                        IoBaseReg16, \
                                        &SetBit32, \
                                        &ResetBit32 );
}

/**
    This function writes an 8bit value to a specific I/O
    Index/Data ports and writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBase16       - A 16 Bit I/O Address for Index I/O Port 
    @param RegIdx8        - An 8 Bit Register Index
    @param Value8         - An 8 Bit Value to write.

    @retval VOID

    @note  The default Data I/O Port is the Index I/O Port plus 1, if your 
           Data I/O Port is not that, please modify below "IoBase16 + 1".
           
**/
VOID 
EFIAPI
WriteIo8IdxDataS3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            Value8 )
{
    WriteIo8S3 (BootScriptSave, IoBase16, IoReg8);
    WriteIo8S3 (BootScriptSave, IoBase16 + 1, Value8);
}

/**
    This function reads an 8bit value from a specific I/O
    Index/Data port.

    @param IoBase16 - A 16 Bit I/O Address for Index I/O Port
    @param RegIdx8  - An 8 Bit Register offset

    @retval An 8Bit data read from the specific Index/Data I/O port.

    @note  The default Data I/O Port is the Index I/O Port plus 1, if your 
           Data I/O Port is not that, please modify below "++IoBase16".
           
**/
UINT8 
EFIAPI
ReadIo8IdxData (
    IN UINT16           IoBase16,
    IN UINT8            RegIdx8 )
{
    IoWrite8 ( IoBase16, RegIdx8 );
    return IoRead8 ( ++IoBase16 );
}

/**
    This function writes an 8bit value to a specific I/O
    Index/Data port.

    @param IoBase16 - A 16 Bit I/O Address for Index I/O Port
    @param RegIdx8  - An 8 Bit Register Index
    @param Value8   - An 8 Bit Value to write.

    @retval VOID

    @note  The default Data I/O Port is the Index I/O Port plus 1, if your 
           Data I/O Port is not that, please modify below "++IoBase16".
           
**/
VOID 
EFIAPI
WriteIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        Value8 )
{
    IoWrite8 ( IoBase16, RegIdx8 );
    IoWrite8 ( ++IoBase16, Value8 );
}

/**
    This function reads an 8bit value from a specific I/O
    Index/Data port, then applies Set/Reset masks and writes
    it back.

    @param IoBase16  - A 16 Bit I/O Address for Index I/O Port
    @param RegIdx8   - An 8 Bit Register Index
    @param SetBit8   - Mask of 8bits to set (1 = Set)
    @param ResetBit8 - Mask of 8bits to reset (1 = Reset)

    @retval VOID

    @note  The default Data I/O Port is the Index I/O Port plus 1, if your 
           Data I/O Port is not that, please modify IoRead8IdxData and 
           IoWrite8IdxData's "++IoBase16".
           
**/
VOID 
EFIAPI
RwIo8IdxData (
    IN UINT16       IoBase16,
    IN UINT8        RegIdx8,
    IN UINT8        SetBit8,
    IN UINT8        ResetBit8 )
{
    UINT8           Buffer8 ;

    Buffer8 = ReadIo8IdxData ( IoBase16, RegIdx8 ) & ~ResetBit8 | SetBit8;
    WriteIo8IdxData ( IoBase16, RegIdx8, Buffer8 );
}

/**
    This function reads an 8bit value from a specific I/O
    Index/Data ports, then applies Set/Reset masks, and writes
    it back. Also writes a copy to Boot Script Table.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param IoBase16       - A 16 Bit I/O Address for Index I/O Port 
    @param RegIdx8        - An 8 Bit Register Index
    @param SetBit8        - Mask of 8bits to set (1 = Set)
    @param ResetBit8      - Mask of 8bits to reset (1 = Reset)

    @retval An 8Bit data read from the specific Index/Data I/O port after 
            applying Set/Reset masks. 

    @note The default Data I/O Port is the Index I/O Port plus 1, if your 
          Data I/O Port is not that, please modify below "IoBase16 + 1" 
          and IoWrite8IdxData's "++IoBase16".
              
**/
VOID 
EFIAPI
RwIo8IdxDataS3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT16                           IoBase16,
    IN UINT8                            IoReg8,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    RwIo8IdxData (IoBase16, IoReg8, SetBit8, ResetBit8);

    BOOT_SCRIPT_S3_IO_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                   EfiBootScriptWidthUint8,\
                                   IoBase16, \
                                   1, \
                                   &IoReg8 );
    ResetBit8 = ~ResetBit8;
    BOOT_SCRIPT_S3_IO_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                        EfiBootScriptWidthUint8, \
                                        IoBase16 + 1, \
                                        &SetBit8, \
                                        &ResetBit8 );
}

/**
    This function writes an 8bits data to the specific PCI
    register and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param Value8         - An 8 Bits data will be written to the 
                            specific PCI register and Boot Script.

    @retval VOID
    
**/
VOID 
EFIAPI
WritePci8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT8                            Value8 )
{
	WRITE_PCI8(Bus, Dev, Fun, Reg, Value8);

  BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
    EfiBootScriptWidthUint8, \
    CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
    1, \
    &Value8
    );
}

/**
    This function writes a 16bits data to the specific PCI
    register and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param Value16        - A 16 Bits data will be written to the 
                            specific PCI register and Boot Script.

    @retval VOID
    
**/
VOID 
EFIAPI
WritePci16S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT16                           Value16 )
{

	WRITE_PCI16(Bus, Dev, Fun, Reg, Value16);

  BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
    EfiBootScriptWidthUint16, \
    CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
    1, \
    &Value16
    );
}

/**
    This function writes a 32bits data to the specific PCI
    register and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param Value32        - A 32 Bits data will be written to the
                            specific PCI register and Boot Script.

    @retval VOID
    
**/
VOID 
EFIAPI
WritePci32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT32                           Value32 )
{

	WRITE_PCI32(Bus, Dev, Fun, Reg, Value32);

  BOOT_SCRIPT_S3_MEM_WRITE_MACRO( \
    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
    EfiBootScriptWidthUint32, \
    CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
    1, \
    &Value32
    );
}

/**
    This function reads an 8bits data from the specific PCI
    register, applies masks, and writes it back, also writes it
    to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param SetBit8        - Mask of bits to set (1 = Set)
    @param ResetBit8      - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwPci8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    RW_PCI8(Bus, Dev, Fun, Reg, SetBit8, ResetBit8);

    ResetBit8 = ~ResetBit8;

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
      CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
      EfiBootScriptWidthUint8, \
      CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
      &SetBit8, \
      &ResetBit8
      );
}

/**
    This function reads a 16bits data from the specific PCI
    register, applies masks, and writes it back, also writes it
    to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save ProtocOl
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param SetBit16       - Mask of bits to set (1 = Set)
    @param ResetBit16     - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwPci16S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{
    RW_PCI16(Bus, Dev, Fun, Reg, SetBit16, ResetBit16);

    ResetBit16 = ~ResetBit16;

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
      CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
      EfiBootScriptWidthUint16, \
      CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
      &SetBit16, \
      &ResetBit16
      );
}

/**
    This function reads a 32bits data from the specific PCI
    register, applies masks, and writes it back, also writes it
    to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Bus            - PCI Bus number.
    @param Dev            - PCI Device number.
    @param Fun            - PCI Function number.
    @param Reg            - PCI Register number.
    @param SetBit32       - Mask of bits to set (1 = Set)
    @param ResetBit32     - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwPci32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINT8                            Bus,
    IN UINT8                            Dev,
    IN UINT8                            Fun,
    IN UINT16                           Reg,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{
    RW_PCI32(Bus, Dev, Fun, Reg, SetBit32, ResetBit32);

    ResetBit32 = ~ResetBit32;

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( \
      CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
      EfiBootScriptWidthUint32, \
      CSP_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg), \
      &SetBit32, \
      &ResetBit32
      );
}

/**
    This function writes an 8bits data to a specific memory
    (or MMIO) address and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param Value8         - An 8Bits data writes to the address.

    @retval VOID
    
**/
VOID 
EFIAPI
WriteMem8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT8                            Value8 )
{
    MmioWrite8 (Address, Value8);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                    EfiBootScriptWidthUint8, \
                                    Address, \
                                    1, \
                                    &Value8 );
}

/**
    This function writes a 16bits data to a specific memory
    (or MMIO) address and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param Value16        - A 16Bits data writes to the address.

    @retval VOID
    
**/
VOID 
EFIAPI
WriteMem16S3(
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT16                           Value16 )
{
    MmioWrite16 (Address, Value16);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                    EfiBootScriptWidthUint16, \
                                    Address, \
                                    1, \
                                    &Value16 );
}

/**
    This function writes a 32bits data to a specific memory
    (or MMIO) address and Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param Value32        - A 32Bits data writes to the address.

    @retval VOID
    
**/
VOID 
EFIAPI
WriteMem32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT32                           Value32 )
{
    MmioWrite32 (Address, Value32);

    BOOT_SCRIPT_S3_MEM_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                    EfiBootScriptWidthUint32, \
                                    Address, \
                                    1, \
                                    &Value32 );
}

/**
    This function reads an 8bits data from a specific memory
    (or MMIO) address, applies masks, and writes it back, also
    writes it to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param SetBit8        - Mask of bits to set (1 = Set)
    @param ResetBit8      - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwMem8S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT8                            SetBit8,
    IN UINT8                            ResetBit8 )
{
    ResetBit8 = ~ResetBit8;
    MmioAndThenOr8 (Address, ResetBit8, SetBit8);

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                         EfiBootScriptWidthUint8, \
                                         Address, \
                                         &SetBit8, \
                                         &ResetBit8 );
}

/**
    This function reads a 16bits data from a specific memory
    (or MMIO) address, applies masks, and writes it back, also
    writes it to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param SetBit16       - Mask of bits to set (1 = Set)
    @param ResetBit16     - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwMem16S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT16                           SetBit16,
    IN UINT16                           ResetBit16 )
{
    ResetBit16 = ~ResetBit16;
    MmioAndThenOr16 (Address, ResetBit16, SetBit16);

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                         EfiBootScriptWidthUint16, \
                                         Address, \
                                         &SetBit16, \
                                         &ResetBit16 );
}

/**
    This function reads a 32bits data from a specific memory
    (or MMIO) address, applies masks, and writes it back, also
    writes it to Boot Script.

    @param BootScriptSave - Pointer to Boot Script Save Protocol
    @param Address        - A 64Bits Memory (or MMIO) address
    @param SetBit32       - Mask of bits to set (1 = Set)
    @param ResetBit32     - Mask of bits to clear  (1 = clear)

    @retval VOID
    
**/
VOID 
EFIAPI
RwMem32S3 (
    IN EFI_S3_SAVE_STATE_PROTOCOL       *BootScriptSave,
    IN UINTN                            Address,
    IN UINT32                           SetBit32,
    IN UINT32                           ResetBit32 )
{
    ResetBit32 = ~ResetBit32;
    MmioAndThenOr32 (Address, ResetBit32, SetBit32);

    BOOT_SCRIPT_S3_MEM_READ_WRITE_MACRO( CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave), \
                                         EfiBootScriptWidthUint32, \
                                         Address, \
                                         &SetBit32, \
                                         &ResetBit32 );
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
