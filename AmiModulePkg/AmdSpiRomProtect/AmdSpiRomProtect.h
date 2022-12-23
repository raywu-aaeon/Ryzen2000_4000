//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file AmdSpiRomProtect.h
    AmdSpiRomProtect definitions

**/
//*************************************************************************

#ifndef  _AmdSpiRomProtect_H   //To Avoid this header get compiled twice
#define  _AmdSpiRomProtect_H

#include <Token.h>

//#define AmdSpiRomProtect_PCI_CFG_ADDRESS(bus, dev, func, reg) \
//            (UINT64) ((((UINT8)(bus) << 24) + ((UINT8)(dev) << 16) + \
//            ((UINT8)(func) << 8) + ((UINT8)(reg))) & 0xffffffff)

#ifndef AMD_PSP_ROM_ARMOR2_SMM_SUPPORT
#define AMD_PSP_ROM_ARMOR2_SMM_SUPPORT 0
#endif

//**********************************************************************
// Dev 14 Fun 3 Register 
//**********************************************************************
#define SB_BUS_DEV_FUN      ((0x14 << 3) + 3)
#define SB_LPC_BUS          0
#define SB_LPC_DEV          20
#define SB_LPC_FUNC         3

#define LPCRomProtect0    0x50
#define LPCRomProtect1    0x54
#define LPCRomProtect2    0x58
#define LPCRomProtect3    0x5C


//----------------------------------------------------------------------------
// SPI Rom MMIO Rang register
//----------------------------------------------------------------------------
#define SPIRestrictedCmd2Reg    0x09            
#define SPIRestrictedCmdValue   0x06        //Flash Write command OP code.
                                             //Most flash part use 0x06 for Write command OP code,so we use 0x06 as default value.
#define SPIMMIOReg1D              0x1D                                             


//----------------------------------------------------------------------------
// SMI register
//----------------------------------------------------------------------------

#define SB_SMI_BASE         0xFED80200ul
#define SmiReg98               0x98    //
#define SmiRegB2               0xB2    //  

//----------------------------------------------------------------------------
// AOAC register
//----------------------------------------------------------------------------

#define SB_AOAC_BASE         0xFED81E00ul
#define AOACReg94               0x94    //
 
#endif  //_AmdSpiRomProtect_H

