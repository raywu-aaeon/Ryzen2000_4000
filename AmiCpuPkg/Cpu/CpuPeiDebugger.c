//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CpuPeiDebugger.c
    This file contains PEI stage board component code for
    Template SB

**/
#include <Efi.h>
#include <AmiLib.h>
#include <Token.h>


/**
    This eLink function is used to initialize CPU for PEI debugger support

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID
InitializeCpu(
    VOID
)
{
	UINT32	Value;

    //Enable Apic
//	*(UINT32*)  (APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER) |= 1 << 8;	
	*(UINT32*)  (APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER) = (1 << 8) + 0x0F;

    //--------------------------
    // Program Virtual Wire Mode.
    //--------------------------

    // Program LINT0 vector as ExtInt
    Value = *(UINT32*)(APIC_BASE + APIC_LVT_LINT0_REGISTER);
//    Value &= 0xFFFE00FF;
    Value &= 0xFFFF00FF;
    Value |= 0x700;
    *(UINT32*)(APIC_BASE + APIC_LVT_LINT0_REGISTER) = Value;
  
    // Program the LINT1 vector entry as NMI
    Value = *(UINT32*)(APIC_BASE + APIC_LVT_LINT1_REGISTER);
    Value &= 0xFFFE00FF;
    Value |= 0x10400;

 	*(UINT32*)(APIC_BASE + APIC_LVT_LINT1_REGISTER) = Value;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
