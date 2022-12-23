//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file SbCspLib.h
  This file contains South Bridge(LPC) chipset porting library functions
  and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __SBLIB_H__
#define __SBLIB_H__

#include <Uefi.h>
#include <PiPei.h>
//###include <Pei.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
//####include <Protocol/AmiSio.h> //### EIP425141 : Separate AmiCompatiblityPkg items to SbAmiCompatibility.h.
#include <Ppi/ReadOnlyVariable2.h>
#include "AmiFchIoAccessLib.h"
//####include "AmiCmosLib.h" //### EIP425141 : Separate AmiCompatiblityPkg items to SbAmiCompatibility.h.
#include "AmiCspFlashLib.h"
#include "AmiGpioLib.h"
//####include "AmiPirqRouterLib.h" //### EIP425141 : Separate AmiCompatiblityPkg items to SbAmiCompatibility.h.
#include "AmiSbMiscLib.h"
#include "AmiSmbiosLib.h"
#include "AmiSmmLib.h"

#ifdef __cplusplus
extern "C" {
#endif

//###  EIP425141 : This is different from chipset template.
//###  We separate AmiCompatiblityPkg items to SbAmiCompatibility.h.
//###  It help us to use SbCspLib.h macro without the dependence of AmiCompatiblityPkg.
//###  For future the AmiCompatiblityPkg maybe deprecated.
//###
//###EFI_STATUS SbLibSetLpcDeviceDecoding(
//###    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
//###    IN UINT16                   Base,
//###    IN UINT8                    DevUid,
//###    IN SIO_DEV_TYPE             Type
//###);
//###
//###EFI_STATUS SbLibSetLpcGenericDecoding(
//###    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
//###    IN UINT16                   Base,
//###    IN UINT16                   Length,
//###    IN BOOLEAN                  Enable
//###);


//  Index/Data I/O Access
#define READ_IO8_IDX_DATA(mIndex, bReg)         ReadIo8IdxData(mIndex, bReg)
#define WRITE_IO8_IDX_DATA(mIndex, bReg, bVal)  WriteIo8IdxData(mIndex, bReg, (UINT8)bVal)
#define RW_IO8_IDX_DATA(mIndex, bReg, Set, Rst) RwIo8IdxData(mIndex, bReg, (UINT8)Set, (UINT8)Rst)
#define SET_IO8_IDX_DATA(bReg, Set)             RwIo8IdxData(mIndex, bReg, (UINT8)Set, 0)
#define RESET_IO8_IDX_DATA(bReg, Reset)         RwIo8IdxData(mIndex, bReg, 0, (UINT8)Reset)

//  Index/Data I/O Access + S3 Boot Script
#define WRITE_IO8_IDX_DATA_S3(mBoot,mIndex, bReg, bVal) \
                            WriteIo8IdxDataS3(mBoot,mIndex, bReg, (UINT8)bVal)
#define RW_IO8_IDX_DATA_S3(mBoot,mIndex, bReg, Set, Rst) \
                            RwIo8IdxDataS3(mBoot,mIndex, bReg, (UINT8)Set, (UINT8)Rst)
#define SET_IO8_IDX_DATA_S3(mBoot,mIndex, bReg, Set) \
                            RwIo8IdxDataS3(mBoot,mIndex, bReg, (UINT8)Set, 0)
#define RESET_IO8_IDX_DATA_S3(mBoot,mIndex, bReg, Rst) \
                            RwIo8IdxDataS3(mBoot,mIndex, bReg, 0, (UINT8)Rst)


//---------------------------------------------------------------------------
// Chipset PCI Macros, Porting Required.
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SMBus Module and ACPI Block (Device 20, Function 0)
#define READ_PCI8_SMBUS(bReg)           READ_PCI8(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg)
#define WRITE_PCI8_SMBUS(bReg, bVal)    WRITE_PCI8(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, bVal)
#define SET_PCI8_SMBUS(bReg, Set)       SET_PCI8(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI8_SMBUS(bReg, Rst)     RESET_PCI8(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI8_SMBUS(bReg, Set, Rst)   RW_PCI8(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set, Rst)
#define READ_PCI16_SMBUS(bReg)          READ_PCI16(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg)
#define WRITE_PCI16_SMBUS(bReg, wVal)   WRITE_PCI16(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, wVal)
#define SET_PCI16_SMBUS(bReg, Set)      SET_PCI16(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI16_SMBUS(bReg, Rst)    RESET_PCI16(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI16_SMBUS(bReg, Set, Rst)  RW_PCI16(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg,Set, Rst)
#define READ_PCI32_SMBUS(bReg)          READ_PCI32(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg)
#define WRITE_PCI32_SMBUS(bReg, dVal)   WRITE_PCI32(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, dVal)
#define SET_PCI32_SMBUS(bReg, Set)      SET_PCI32(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI32_SMBUS(bReg, Rst)    RESET_PCI32(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI32_SMBUS(bReg, Set, Rst)  RW_PCI32(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg,Set, Rst)

//----------------------------------------------------------------------------
//   LPC ISA Bridge (Device 20, Function 3)
#define READ_PCI8_SB(bReg)              READ_PCI8(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg)
#define WRITE_PCI8_SB(bReg, bVal)       WRITE_PCI8(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, bVal)
#define SET_PCI8_SB(bReg, Set)          SET_PCI8(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI8_SB(bReg, Reset)      RESET_PCI8(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI8_SB(bReg, Set, Reset)    RW_PCI8(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)
#define READ_PCI16_SB(bReg)             READ_PCI16(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg)
#define WRITE_PCI16_SB(bReg, wVal)      WRITE_PCI16(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, wVal)
#define SET_PCI16_SB(bReg, Set)         SET_PCI16(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI16_SB(bReg, Reset)     RESET_PCI16(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI16_SB(bReg, Set, Reset)   RW_PCI16(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)
#define READ_PCI32_SB(bReg)             READ_PCI32(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC, bReg)
#define WRITE_PCI32_SB(bReg, dVal)      WRITE_PCI32(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, dVal)
#define SET_PCI32_SB(bReg, Set)         SET_PCI32(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI32_SB(bReg, Reset)     RESET_PCI32(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI32_SB(bReg, Set, Reset)   RW_PCI32(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// IDE Controller (Device 20, Function 1)
#define READ_PCI8_IDE(bReg)             READ_PCI8(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg)
#define WRITE_PCI8_IDE(bReg, bVal)      WRITE_PCI8(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, bVal)
#define SET_PCI8_IDE(bReg, Set)         SET_PCI8(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI8_IDE(bReg, Reset)     RESET_PCI8(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI8_IDE(bReg, Set, Reset)   RW_PCI8(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)
#define READ_PCI16_IDE(bReg)            READ_PCI16(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg)
#define WRITE_PCI16_IDE(bReg, wVal)     WRITE_PCI16(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, wVal)
#define SET_PCI16_IDE(bReg, Set)        SET_PCI16(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI16_IDE(bReg, Reset)    RESET_PCI16(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI16_IDE(bReg, Set, Reset)  RW_PCI16(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)
#define READ_PCI32_IDE(bReg)            READ_PCI32(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg)
#define WRITE_PCI32_IDE(bReg, dVal)     WRITE_PCI32(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, dVal)
#define SET_PCI32_IDE(bReg, Set)        SET_PCI32(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI32_IDE(bReg, Reset)    RESET_PCI32(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI32_IDE(bReg, Set, Reset)  RW_PCI32(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// SATA Registers (Bus 0, Device 17, Function 0)
#define READ_PCI8_SATA(bReg)            READ_PCI8(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg)
#define WRITE_PCI8_SATA(bReg, bVal)     WRITE_PCI8(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, bVal)
#define SET_PCI8_SATA(bReg, Set)        SET_PCI8(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI8_SATA(bReg, Reset)    RESET_PCI8(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI8_SATA(bReg, Set, Reset)  RW_PCI8(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Reset)
#define READ_PCI16_SATA(bReg)           READ_PCI16(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg)
#define WRITE_PCI16_SATA(bReg, wVal)    WRITE_PCI16(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, wVal)
#define SET_PCI16_SATA(bReg, Set)       SET_PCI16(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI16_SATA(bReg, Reset)   RESET_PCI16(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI16_SATA(bReg, Set, Reset) RW_PCI16(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Reset)
#define READ_PCI32_SATA(bReg)           READ_PCI32(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg)
#define WRITE_PCI32_SATA(bReg, dVal)    WRITE_PCI32(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, dVal)
#define SET_PCI32_SATA(bReg, Set)       SET_PCI32(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI32_SATA(bReg, Reset)   RESET_PCI32(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI32_SATA(bReg, Set, Reset) RW_PCI32(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Reset)


//----------------------------------------------------------------------------
// Host PCI Bridge Registers (Device 20, Function 4)
#define READ_PCI8_PCIBR(bReg)            READ_PCI8(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg)
#define WRITE_PCI8_PCIBR(bReg, bVal)     WRITE_PCI8(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, bVal)
#define SET_PCI8_PCIBR(bReg, Set)        SET_PCI8(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI8_PCIBR(bReg, Rst)      RESET_PCI8(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI8_PCIBR(bReg, Set, Rst)    RW_PCI8(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set, Rst)
#define READ_PCI16_PCIBR(bReg)           READ_PCI16(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg)
#define WRITE_PCI16_PCIBR(bReg, wVal)    WRITE_PCI16(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, wVal)
#define SET_PCI16_PCIBR(bReg, Set)       SET_PCI16(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI16_PCIBR(bReg, Rst)     RESET_PCI16(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI16_PCIBR(bReg, Set, Rst)   RW_PCI16(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg,Set, Rst)
#define READ_PCI32_PCIBR(bReg)           READ_PCI32(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg)
#define WRITE_PCI32_PCIBR(bReg, dVal)    WRITE_PCI32(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, dVal)
#define SET_PCI32_PCIBR(bReg, Set)       SET_PCI32(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI32_PCIBR(bReg, Rst)     RESET_PCI32(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI32_PCIBR(bReg, Set, Rst)   RW_PCI32(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg,Set, Rst)

//----------------------------------------------------------------------------
// USB Controller #1 (EHCI)
#define READ_PCI8_EUSB(bReg)            READ_PCI8(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg)
#define WRITE_PCI8_EUSB(bReg, bVal)     WRITE_PCI8(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, bVal)
#define SET_PCI8_EUSB(bReg, Set)        SET_PCI8(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI8_EUSB(bReg, Reset)    RESET_PCI8(FCH_EHCI1_BUS,FCH_EHCI1_DEV,NC, bReg, Reset)
#define RW_PCI8_EUSB(bReg, Set, Reset)  RW_PCI8(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set, Reset)
#define READ_PCI16_EUSB(bReg)           READ_PCI16(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg)
#define WRITE_PCI16_EUSB(bReg, wVal)    WRITE_PCI16(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, wVal)
#define SET_PCI16_EUSB(bReg, Set)       SET_PCI16(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI16_EUSB(bReg, Reset)   RESET_PCI16(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Reset)
#define RW_PCI16_EUSB(bReg, Set, Reset) RW_PCI16(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set, Reset)
#define READ_PCI32_EUSB(bReg)           READ_PCI32(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg)
#define WRITE_PCI32_EUSB(bReg, dVal)    WRITE_PCI32(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, dVal)
#define SET_PCI32_EUSB(bReg, Set)       SET_PCI32(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI32_EUSB(bReg, Reset)   RESET_PCI32(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Reset)
#define RW_PCI32_EUSB(bReg, Set, Reset) RW_PCI32(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// USB Controller #2 (EHCI)
#define READ_PCI8_EUSB2(bReg)               READ_PCI8(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg)
#define WRITE_PCI8_EUSB2(bReg, bVal)        WRITE_PCI8(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, bVal)
#define SET_PCI8_EUSB2(bReg, Set)           SET_PCI8(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI8_EUSB2(bReg, Reset)       RESET_PCI8(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI8_EUSB2(bReg, Set, Reset)     RW_PCI8(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)
#define READ_PCI16_EUSB2(bReg)              READ_PCI16(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg)
#define WRITE_PCI16_EUSB2(bReg, wVal)       WRITE_PCI16(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, wVal)
#define SET_PCI16_EUSB2(bReg, Set)          SET_PCI16(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI16_EUSB2(bReg, Reset)      RESET_PCI16(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI16_EUSB2(bReg, Set, Reset)    RW_PCI16(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)
#define READ_PCI32_EUSB2(bReg)              READ_PCI32(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg)
#define WRITE_PCI32_EUSB2(bReg, dVal)       WRITE_PCI32(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, dVal)
#define SET_PCI32_EUSB2(bReg, Set)          SET_PCI32(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI32_EUSB2(bReg, Reset)      RESET_PCI32(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI32_EUSB2(bReg, Set, Reset)    RW_PCI32(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// USB Controller #3 (EHCI)
#define READ_PCI8_EUSB3(bReg)               READ_PCI8(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg)
#define WRITE_PCI8_EUSB3(bReg, bVal)        WRITE_PCI8(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, bVal)
#define SET_PCI8_EUSB3(bReg, Set)           SET_PCI8(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI8_EUSB3(bReg, Reset)       RESET_PCI8(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI8_EUSB3(bReg, Set, Reset)     RW_PCI8(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)
#define READ_PCI16_EUSB3(bReg)              READ_PCI16(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg)
#define WRITE_PCI16_EUSB3(bReg, wVal)       WRITE_PCI16(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, wVal)
#define SET_PCI16_EUSB3(bReg, Set)          SET_PCI16(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI16_EUSB3(bReg, Reset)      RESET_PCI16(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI16_EUSB3(bReg, Set, Reset)    RW_PCI16(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)
#define READ_PCI32_EUSB3(bReg)              READ_PCI32(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg)
#define WRITE_PCI32_EUSB3(bReg, dVal)       WRITE_PCI32(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, dVal)
#define SET_PCI32_EUSB3(bReg, Set)          SET_PCI32(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI32_EUSB3(bReg, Reset)      RESET_PCI32(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI32_EUSB3(bReg, Set, Reset)    RW_PCI32(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)


//----------------------------------------------------------------------------
// USB XHCI 0 Controller  (XHCI)
#define READ_PCI8_XHCI0(bReg)               READ_PCI8(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg)
#define WRITE_PCI8_XHCI0(bReg, bVal)        WRITE_PCI8(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, bVal)
#define SET_PCI8_XHCI0(bReg, Set)           SET_PCI8(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI8_XHCI0(bReg, Reset)       RESET_PCI8(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI8_XHCI0(bReg, Set, Reset)     RW_PCI8(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)
#define READ_PCI16_XHCI0(bReg)              READ_PCI16(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg)
#define WRITE_PCI16_XHCI0(bReg, wVal)       WRITE_PCI16(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, wVal)
#define SET_PCI16_XHCI0(bReg, Set)          SET_PCI16(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI16_XHCI0(bReg, Reset)      RESET_PCI16(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI16_XHCI0(bReg, Set, Reset)    RW_PCI16(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)
#define READ_PCI32_XHCI0(bReg)              READ_PCI32(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg)
#define WRITE_PCI32_XHCI0(bReg, dVal)       WRITE_PCI32(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, dVal)
#define SET_PCI32_XHCI0(bReg, Set)          SET_PCI32(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI32_XHCI0(bReg, Reset)      RESET_PCI32(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI32_XHCI0(bReg, Set, Reset)    RW_PCI32(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// USB XHCI 0 Controller  (XHCI)
#define READ_PCI8_XHCI1(bReg)               READ_PCI8(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg)
#define WRITE_PCI8_XHCI1(bReg, bVal)        WRITE_PCI8(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, bVal)
#define SET_PCI8_XHCI1(bReg, Set)           SET_PCI8(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set)
#define RESET_PCI8_XHCI1(bReg, Reset)       RESET_PCI8(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Reset)
#define RW_PCI8_XHCI1(bReg, Set, Reset)     RW_PCI8(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set, Reset)
#define READ_PCI16_XHCI1(bReg)              READ_PCI16(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg)
#define WRITE_PCI16_XHCI1(bReg, wVal)       WRITE_PCI16(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, wVal)
#define SET_PCI16_XHCI1(bReg, Set)          SET_PCI16(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set)
#define RESET_PCI16_XHCI1(bReg, Reset)      RESET_PCI16(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Reset)
#define RW_PCI16_XHCI1(bReg, Set, Reset)    RW_PCI16(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set, Reset)
#define READ_PCI32_XHCI1(bReg)              READ_PCI32(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg)
#define WRITE_PCI32_XHCI1(bReg, dVal)       WRITE_PCI32(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, dVal)
#define SET_PCI32_XHCI1(bReg, Set)          SET_PCI32(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set)
#define RESET_PCI32_XHCI1(bReg, Reset)      RESET_PCI32(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Reset)
#define RW_PCI32_XHCI1(bReg, Set, Reset)    RW_PCI32(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// SMBus Module and ACPI Block (Device 20, Function 0)
#define WRITE_PCI8_SMBUS_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, bVal)
#define SET_PCI8_SMBUS_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI8_SMBUS_S3(mBoot, bReg, Rst) \
                                RESET_PCI8_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI8_SMBUS_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI8_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set,Rst)
#define WRITE_PCI16_SMBUS_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg,wVal)
#define SET_PCI16_SMBUS_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI16_SMBUS_S3(mBoot, bReg, Rst) \
                                RESET_PCI16_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI16_SMBUS_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI16_S3(mBoot,FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set,Rst)
#define WRITE_PCI32_SMBUS_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg,dVal)
#define SET_PCI32_SMBUS_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set)
#define RESET_PCI32_SMBUS_S3(mBoot, bReg, Rst) \
                                RESET_PCI32_S3(mBoot, FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Rst)
#define RW_PCI32_SMBUS_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI32_S3(mBoot,FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,bReg, Set,Rst)

//----------------------------------------------------------------------------
//   LPC ISA Bridge (Device 20, Function 3)
#define WRITE_PCI8_SB_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, bVal)
#define SET_PCI8_SB_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI8_SB_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI8_SB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)
#define WRITE_PCI16_SB_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, wVal)
#define SET_PCI16_SB_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI16_SB_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI16_SB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_SB_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, dVal)
#define SET_PCI32_SB_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set)
#define RESET_PCI32_SB_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Reset)
#define RW_PCI32_SB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// IDE Controller (Device 20, Function 1)
#define WRITE_PCI8_IDE_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, bVal)
#define SET_PCI8_IDE_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI8_IDE_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI8_IDE_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)
#define WRITE_PCI16_IDE_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, wVal)
#define SET_PCI16_IDE_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI16_IDE_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI16_IDE_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_IDE_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, dVal)
#define SET_PCI32_IDE_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set)
#define RESET_PCI32_IDE_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Reset)
#define RW_PCI32_IDE_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// SATA Registers (Bus 0, Device 17, Function 0)
#define WRITE_PCI8_SATA_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, bVal)
#define SET_PCI8_SATA_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI8_SATA_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI8_SATA_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI8_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Rst)
#define WRITE_PCI16_SATA_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, wVal)
#define SET_PCI16_SATA_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI16_SATA_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI16_SATA_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_SATA_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, dVal)
#define SET_PCI32_SATA_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set)
#define RESET_PCI32_SATA_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Reset)
#define RW_PCI32_SATA_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// Host PCI Bridge Registers (Device 20, Function 4)
#define WRITE_PCI8_PCIBR_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, bVal)
#define SET_PCI8_PCIBR_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI8_PCIBR_S3(mBoot, bReg, Rst) \
                                RESET_PCI8_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI8_PCIBR_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI8_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set,Rst)
#define WRITE_PCI16_PCIBR_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg,wVal)
#define SET_PCI16_PCIBR_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI16_PCIBR_S3(mBoot, bReg, Rst) \
                                RESET_PCI16_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI16_PCIBR_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI16_S3(mBoot,FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set,Rst)
#define WRITE_PCI32_PCIBR_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg,dVal)
#define SET_PCI32_PCIBR_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set)
#define RESET_PCI32_PCIBR_S3(mBoot, bReg, Rst) \
                                RESET_PCI32_S3(mBoot, FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Rst)
#define RW_PCI32_PCIBR_S3(mBoot, bReg, Set, Rst) \
                                RW_PCI32_S3(mBoot,FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,bReg, Set,Rst)

//----------------------------------------------------------------------------
/* RVA9 : there is no fixed bus XHCI. The XHCI is behind bridge and no EHCI in Sandstone. so comment below.
//----------------------------------------------------------------------------
// USB Controller #1 (EHCI)
#define WRITE_PCI8_EUSB_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, bVal)
#define SET_PCI8_EUSB_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI8_EUSB_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Reset)
#define RW_PCI8_EUSB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set, Reset)
#define WRITE_PCI16_EUSB_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, wVal)
#define SET_PCI16_EUSB_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI16_EUSB_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Reset)
#define RW_PCI16_EUSB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set, Reset)
#define WRITE_PCI32_EUSB_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, dVal)
#define SET_PCI32_EUSB_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set)
#define RESET_PCI32_EUSB_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Reset)
#define RW_PCI32_EUSB_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC, bReg, Set, Reset)

//----------------------------------------------------------------------------
// USB Controller #2 (EHCI)
#define WRITE_PCI8_EUSB2_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, bVal)
#define SET_PCI8_EUSB2_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI8_EUSB2_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI8_EUSB2_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)
#define WRITE_PCI16_EUSB2_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, wVal)
#define SET_PCI16_EUSB2_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI16_EUSB2_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI16_EUSB2_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_EUSB2_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, dVal)
#define SET_PCI32_EUSB2_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set)
#define RESET_PCI32_EUSB2_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Reset)
#define RW_PCI32_EUSB2_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,bReg, Set, Reset)

//----------------------------------------------------------------------------
// USB Controller #3 (EHCI)
#define WRITE_PCI8_EUSB3_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, bVal)
#define SET_PCI8_EUSB3_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI8_EUSB3_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI8_EUSB3_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)
#define WRITE_PCI16_EUSB3_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, wVal)
#define SET_PCI16_EUSB3_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI16_EUSB3_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI16_EUSB3_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_EUSB3_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, dVal)
#define SET_PCI32_EUSB3_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set)
#define RESET_PCI32_EUSB3_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Reset)
#define RW_PCI32_EUSB3_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,bReg, Set, Reset)
//----------------------------------------------------------------------------
// USB XHCI0 Controller #0 (XHCI)
#define WRITE_PCI8_XHCI0_S3(mBoot, bReg, bVal) \
                                WRITE_PCI8_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, bVal)
#define SET_PCI8_XHCI0_S3(mBoot, bReg, Set) \
                                SET_PCI8_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI8_XHCI0_S3(mBoot, bReg, Reset) \
                                RESET_PCI8_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI8_XHCI0_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI8_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)
#define WRITE_PCI16_XHCI0_S3(mBoot, bReg, wVal) \
                                WRITE_PCI16_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, wVal)
#define SET_PCI16_XHCI0_S3(mBoot, bReg, Set) \
                                SET_PCI16_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI16_XHCI0_S3(mBoot, bReg, Reset) \
                                RESET_PCI16_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI16_XHCI0_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI16_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)
#define WRITE_PCI32_XHCI0_S3(mBoot, bReg, dVal) \
                                WRITE_PCI32_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, dVal)
#define SET_PCI32_XHCI0_S3(mBoot, bReg, Set) \
                                SET_PCI32_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set)
#define RESET_PCI32_XHCI0_S3(mBoot, bReg, Reset) \
                                RESET_PCI32_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Reset)
#define RW_PCI32_XHCI0_S3(mBoot, bReg, Set, Reset) \
                                RW_PCI32_S3(mBoot, FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,bReg, Set, Reset)
*/
//------------------------------------------------------------------------;
// Chipset specific IO Macros, need porting for each SB controller. ;
//------------------------------------------------------------------------;

//----------------------------------------------------------------------------
// ACPI Access
#define READ_IO8_PM(IoReg)                READ_IO8(PM_BASE_ADDRESS+IoReg)
#define WRITE_IO8_PM(IoReg, mVal)         WRITE_IO8(PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO8_PM(IoReg, mSet)           RW_IO8(PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO8_PM(IoReg, mReset)       RW_IO8(PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO8_PM(IoReg, mSet, mReset)    RW_IO8(PM_BASE_ADDRESS+IoReg, mSet, mReset)
#define READ_IO16_PM(IoReg)               READ_IO16(PM_BASE_ADDRESS+IoReg)
#define WRITE_IO16_PM(IoReg, mVal)        WRITE_IO16(PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO16_PM(IoReg, mSet)          RW_IO16(PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO16_PM(IoReg, mReset)      RW_IO16(PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO16_PM(IoReg, mSet, mReset)   RW_IO16(PM_BASE_ADDRESS+IoReg, mSet, mReset)
#define READ_IO32_PM(IoReg)               READ_IO32(PM_BASE_ADDRESS+IoReg)
#define WRITE_IO32_PM(IoReg, mVal)        WRITE_IO32(PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO32_PM(IoReg, mSet)          RW_IO32(PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO32_PM(IoReg, mReset)      RW_IO32(PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO32_PM(IoReg, mSet, mReset)   RW_IO32(PM_BASE_ADDRESS+IoReg, mSet, mReset)

//----------------------------------------------------------------------------
//  ACPI Access + S3 Boot Script
#define WRITE_IO8_PM_S3(mBoot, IoReg, mVal) \
                WRITE_IO8_S3(mBoot, PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO8_PM_S3(mBoot, IoReg, mSet) \
                RW_IO8_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO8_PM_S3(mBoot, IoReg, mReset) \
                RW_IO8_S3(mBoot, PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO8_PM_S3(mBoot, IoReg, mSet, mReset) \
                RW_IO8_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, mReset)
#define WRITE_IO16_PM_S3(mBoot, IoReg, mVal) \
                WRITE_IO16_S3(mBoot, PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO16_PM_S3(mBoot, IoReg, mSet) \
                RW_IO16_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO16_PM_S3(mBoot, IoReg, mReset) \
                RW_IO16_S3(mBoot, PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO16_PM_S3(mBoot, IoReg, mSet, mReset) \
                RW_IO16_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, mReset)
#define WRITE_IO32_PM_S3(mBoot, IoReg, mVal) \
                WRITE_IO32_S3(mBoot, PM_BASE_ADDRESS+IoReg, mVal)
#define SET_IO32_PM_S3(mBoot, IoReg, mSet) \
                RW_IO32_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, 0)
#define RESET_IO32_PM_S3(mBoot, IoReg, mReset) \
                RW_IO32_S3(mBoot, PM_BASE_ADDRESS+IoReg, 0, mReset)
#define RW_IO32_PM_S3(mBoot, IoReg, mSet, mReset) \
                RW_IO32_S3(mBoot, PM_BASE_ADDRESS+IoReg, mSet, mReset)

//----------------------------------------------------------------------------
//  Power Management (PM) Access
#define READ_IO8_PMIO(bReg)               READ_IO8_IDX_DATA(PM_IO_INDEX, bReg)
#define WRITE_IO8_PMIO(bReg, mVal)        WRITE_IO8_IDX_DATA(PM_IO_INDEX, bReg, mVal)
#define RW_IO8_PMIO(bReg, mSet, mReset)   RW_IO8_IDX_DATA(PM_IO_INDEX, bReg, mSet, mReset)
#define SET_IO8_PMIO(bReg, mSet)          RW_IO8_IDX_DATA(PM_IO_INDEX, bReg, mSet, 0)
#define RESET_IO8_PMIO(bReg, mReset)      RW_IO8_IDX_DATA(PM_IO_INDEX, bReg, 0, mReset)

//----------------------------------------------------------------------------
//  Power Management (PM) Access + S3 Boot Script
#define WRITE_IO8_PMIO_S3(mBoot,bReg, mVal) \
                WRITE_IO8_IDX_DATA_S3(mBoot,PM_IO_INDEX, bReg, mVal)
#define RW_IO8_PMIO_S3(mBoot,bReg, mSet, mReset) \
                RW_IO8_IDX_DATA_S3(mBoot,PM_IO_INDEX, bReg, mSet, mReset)
#define SET_IO8_PMIO_S3(mBoot,bReg, mSet) \
                RW_IO8_IDX_DATA_S3(mBoot,PM_IO_INDEX, bReg, mSet, 0)
#define RESET_IO8_PMIO_S3(mBoot,bReg, mReset) \
                RW_IO8_IDX_DATA_S3(mBoot,PM_IO_INDEX, bReg, 0, mReset)

//----------------------------------------------------------------------------
//  PCI IRQ Routing (Pci_Intr_Index/Pci_Intr_Data)
#define READ_IO8_PIRQ(mIdx) \
                READ_IO8_IDX_DATA(PIRQ_IO_INDEX, mIdx)
#define WRITE_IO8_PIRQ(mIdx, mVal) \
                WRITE_IO8_IDX_DATA(PIRQ_IO_INDEX, mIdx, mVal)

//----------------------------------------------------------------------------
//  PCI IRQ Routing (Pci_Intr_Index/Pci_Intr_Data) + S3 BootScript
#define WRITE_IO8_PIRQ_S3(mBoot,mIdx, mVal) \
                WRITE_IO8_IDX_DATA_S3(mBoot,PIRQ_IO_INDEX, mIdx, mVal)

//----------------------------------------------------------------------------
// AMD (AlternatRtcAddrPort/AlternatRtcDataPort)
#define READ_IO8_AMD_RTC(mIdx)          READ_IO8_IDX_DATA(0x72, mIdx)
#define WRITE_IO8_AMD_RTC(mIdx, mVal)   WRITE_IO8_IDX_DATA(0x72, mIdx, mVal)

//------------------------------------------------------------------------;
// Chipset specific MMIO Macros, need porting for each SB controller.;
//------------------------------------------------------------------------;

//------------------------------------------------------------------------;
// GPIO MMIO
#define READ_MMIO8_GPIO(MarcoReg) AmdFchMmioRead8(AMD_FCH_GPIO_MMIO, MarcoReg)

#define WRITE_MMIO8_GPIO(MarcoReg, MarcoData) AmdFchMmioWrite8(AMD_FCH_GPIO_MMIO, MarcoReg, MarcoData)

#define RW_MMIO8_GPIO(MarcoReg, MarcoResetBits, MarcoSetBits) \
			AmdFchMmioAndThenOr8(AMD_FCH_GPIO_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

//------------------------------------------------------------------------;
// MISC MMIO
#define READ_MMIO8_MISC(MarcoReg) AmdFchMmioRead8(AMD_FCH_MISC_MMIO, MarcoReg)
#define READ_MMIO32_MISC(MarcoReg) AmdFchMmioRead32(AMD_FCH_MISC_MMIO, MarcoReg)

#define WRITE_MMIO8_MISC(MarcoReg, MarcoData) AmdFchMmioWrite8(AMD_FCH_MISC_MMIO, MarcoReg, MarcoData)

#define RW_MMIO8_MISC(MarcoReg, MarcoResetBits, MarcoSetBits) \
			AmdFchMmioAndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO8_MISC(MarcoReg, MarcoSetBits) \
			AmdFchMmioAndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, -1, MarcoSetBits)

#define RESET_MMIO8_MISC(MarcoReg, MarcoResetBits) \
			AmdFchMmioAndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), 0)

#define WRITE_MMIO32_MISC(MarcoReg, MarcoData) AmdFchMmioWrite32(AMD_FCH_MISC_MMIO, MarcoReg, MarcoData)

#define RW_MMIO32_MISC(MarcoReg, MarcoResetBits, MarcoSetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO32_MISC(MarcoReg, MarcoSetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, -1, MarcoSetBits)

#define RESET_MMIO32_MISC(MarcoReg, MarcoResetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), 0)

//------------------------------------------------------------------------;
// MISC MMIO + S3 boot script
#define WRITE_MMIO8_MISC_S3(MarcoReg, MarcoData) \
			AmdFchMmioS3Write8(AMD_FCH_MISC_MMIO, MarcoReg, MarcoData)

#define RW_MMIO8_MISC_S3(MarcoReg, MarcoResetBits, MarcoSetBits) \
            AmdFchMmioS3AndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO8_MISC_S3(MarcoReg, MarcoSetBits) \
            AmdFchMmioS3AndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, -1, MarcoSetBits)

#define RESET_MMIO8_MISC_S3(MarcoReg, MarcoResetBits) \
            AmdFchMmioS3AndThenOr8(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), 0)

#define WRITE_MMIO32_MISC_S3(MarcoReg, MarcoData) AmdFchMmioS3Write32(AMD_FCH_MISC_MMIO, MarcoReg, MarcoData)

#define RW_MMIO32_MISC_S3(MarcoReg, MarcoResetBits, MarcoSetBits) \
            AmdFchMmioS3AndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO32_MISC_S3(MarcoReg, MarcoSetBits) \
            AmdFchMmioS3AndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, -1, MarcoSetBits)

#define RESET_MMIO32_MISC_S3(MarcoReg, MarcoResetBits) \
            AmdFchMmioS3AndThenOr32(AMD_FCH_MISC_MMIO, MarcoReg, ~(MarcoResetBits), 0)

//------------------------------------------------------------------------;
// SMI MMIO
#define READ_MMIO8_SMI(MarcoReg) AmdFchMmioRead8(AMD_FCH_SMI_MMIO, MarcoReg)
#define READ_MMIO32_SMI(MarcoReg) AmdFchMmioRead32(AMD_FCH_SMI_MMIO, MarcoReg)

#define WRITE_MMIO8_SMI(MarcoReg, MarcoData) AmdFchMmioWrite8(AMD_FCH_SMI_MMIO, MarcoReg, MarcoData)

#define RW_MMIO8_SMI(MarcoReg, MarcoResetBits, MarcoSetBits) \
			AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO8_SMI(MarcoReg, MarcoSetBits) \
            AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, MarcoReg, ~0, MarcoSetBits)

#define RESET_MMIO8_SMI(MarcoReg, MarcoResetBits) \
            AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, MarcoReg, ~(MarcoResetBits), 0)

#define WRITE_MMIO32_SMI(MarcoReg, MarcoData) AmdFchMmioWrite32(AMD_FCH_SMI_MMIO, MarcoReg, MarcoData)

#define RW_MMIO32_SMI(MarcoReg, MarcoResetBits, MarcoSetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, MarcoReg, ~(MarcoResetBits), MarcoSetBits)

#define SET_MMIO32_SMI(MarcoReg, MarcoSetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, MarcoReg, ~0, MarcoSetBits)

#define RESET_MMIO32_SMI(MarcoReg, MarcoResetBits) \
            AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, MarcoReg, ~(MarcoResetBits), 0)

#ifdef __cplusplus
}
#endif
#endif

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
