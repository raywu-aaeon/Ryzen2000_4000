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
//<AMI_FHDR_START>
//
// Name:        AmiChipsetIoLibEx.h
//
// Description: This header file contains the AmiChipsetIoLibEx.h definition.
//				Which is extra definition and didn't be included in template.
//				!!!! Please don't include this file. !!!!
//				!!!! To include AmiChipsetIoLib.h instead !!!!!
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _AMICHIPSETPKG_INCLUDE_LIBRARY_AMICHIPSETIOLIBEX_H_
#define _AMICHIPSETPKG_INCLUDE_LIBRARY_AMICHIPSETIOLIBEX_H_

#include <Uefi/UefiBaseType.h>
#include <Library/PciLib.h>
#include <Token.h>

#define AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(A) ((UINTN) PcdGet64 (PcdPciExpressBaseAddress) + A)

//----------------------------------------------------------------------------
// Standard PCI Macros, No Porting Required.
//----------------------------------------------------------------------------

// The MacroAddr is the PCI_LIB_ADDRESS of MdePkg-PciLib

#define READ_PCI8EX(MacroAddr)           PciRead8 (MacroAddr)
#define READ_PCI16EX(MacroAddr)          PciRead16 (MacroAddr)
#define READ_PCI32EX(MacroAddr)          PciRead32 (MacroAddr)
#define WRITE_PCI8EX(MacroAddr, bVal)    PciWrite8 (MacroAddr, bVal)
#define WRITE_PCI16EX(MacroAddr, wVal)   PciWrite16 (MacroAddr, wVal)
#define WRITE_PCI32EX(MacroAddr, dVal)   PciWrite32 (MacroAddr, dVal)
#define RW_PCI8EX(MacroAddr, Set, Rst) \
          PciAndThenOr8 (MacroAddr, ~(Rst), Set)
#define RW_PCI16EX(MacroAddr, Set, Rst) \
          PciAndThenOr16 (MacroAddr, ~(Rst), Set)
#define RW_PCI32EX(MacroAddr, Set, Rst) \
          PciAndThenOr32 (MacroAddr, ~(Rst), Set)
#define SET_PCI8EX(MacroAddr, bSet)      PciOr8 (MacroAddr, bSet)
#define SET_PCI16EX(MacroAddr, wSet)     PciOr16 (MacroAddr, wSet)
#define SET_PCI32EX(MacroAddr, dSet)     PciOr32 (MacroAddr, dSet)
#define RESET_PCI8EX(MacroAddr, bRst)    PciAnd8 (MacroAddr, ~(bRst))
#define RESET_PCI16EX(MacroAddr, wRst)   PciAnd16 (MacroAddr, ~(wRst))
#define RESET_PCI32EX(MacroAddr, dRst)   PciAnd32 (MacroAddr, ~(dRst))

#define WRITE_PCI8_S3EX(mBtScSv, MacroAddr, bValue) \
                                WriteMem8S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), bValue)
#define SET_PCI8_S3EX(mBtScSv, MacroAddr, bSet) \
                                RwMem8S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), bSet, 0)
#define RESET_PCI8_S3EX(mBtScSv, MacroAddr, bReset) \
                                RwMem8S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), 0, bReset)
#define RW_PCI8_S3EX(mBtScSv, MacroAddr, bSet, bRst) \
                                RwMem8S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), bSet, bRst)
#define WRITE_PCI16_S3EX(mBtScSv, MacroAddr, wValue) \
                                WriteMem16S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), wValue)
#define SET_PCI16_S3EX(mBtScSv, MacroAddr, wSet) \
                                RwMem16S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), wSet, 0)
#define RESET_PCI16_S3EX(mBtScSv, MacroAddr, wReset) \
                                RwMem16S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), 0, wReset)
#define RW_PCI16_S3EX(mBtScSv, MacroAddr, wSet, wRst) \
                                RwMem16S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), wSet, wRst)
#define WRITE_PCI32_S3EX(mBtScSv, MacroAddr, dValue) \
                                WriteMem32S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), dValue)
#define SET_PCI32_S3EX(mBtScSv, MacroAddr, dSet) \
                                RwMem32S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), dSet, 0)
#define RESET_PCI32_S3EX(mBtScSv, MacroAddr, dReset) \
                                RwMem32S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), 0, dReset)
#define RW_PCI32_S3EX(mBtScSv, MacroAddr, dSet, dRst) \
                                RwMem32S3(mBtScSv, AMICHIPSETIOLIBEX_PCI_ADDRESS_EX(MacroAddr), dSet, dRst)

//----------------------------------------------------------------------------
// A macro to support boot script save after smm lock
//----------------------------------------------------------------------------
BOOLEAN
EFIAPI
CspIsSwitchBootScriptToSmm (
  );

EFI_S3_SAVE_STATE_PROTOCOL*
EFIAPI
CspGetBootScriptWrapper (
  );

#define CSP_BOOT_SCRIPT_SERVICE_EX(macroService) ((!CspIsSwitchBootScriptToSmm()) ? macroService : CspGetBootScriptWrapper())


#pragma pack(1)



#pragma pack()

#endif /* _AMICHIPSETPKG_INCLUDE_LIBRARY_AMICHIPSETIOLIBEX_H_ */

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
