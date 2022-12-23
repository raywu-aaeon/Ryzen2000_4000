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

/** @file SbPspMutexSmiLib.c
    This file contains code for South bridge Psp Mutex Smi related
    function

*/

// Module specific Includes
#include "Efi.h"
#include "Token.h"
#include <AmiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SbPspMutexSmiLib.h>
#include <AgesaModulePkg/Include/Library/AmdSocBaseLib.h>
#include <AgesaModulePkg/Include/Library/AmdPspBaseLibV1.h>
#include <AgesaModulePkg/Include/Library/AmdPspBaseLibV2.h>



#define SMI_BASE        0x200   // DWORD
/**
    This function returns SMI state

    @param VOID

               
    @retval TRUE SMI enabled
    @retval FALSE SMI disabled

    @note  

**/
BOOLEAN SbPspMutexSmi_GetSmiState(VOID)
{
    BOOLEAN     IsSmiEn=FALSE;
#if SMM_SUPPORT
    UINT8   Buffer;
    volatile UINT8  *SbMmioBase = (UINT8*)(UINTN)SB_MMIO_BASE;
     
    AcquirePspSmiRegMutexV2();

    //Buffer = ReadSbSmiIo8(FCH_SMI_REG98+3);   //EIP36094+
    Buffer =  *(volatile UINT8*)(SbMmioBase+SMI_BASE+0x98+0x03);

    ReleasePspSmiRegMutexV2();
    
    if (!(Buffer&BIT07)) IsSmiEn=TRUE; // Yes, Global was enabled.
#endif // #if SMM_SUPPORT
    return IsSmiEn;
}

/**
    This function disables SMI

    @param VOID

    @retval VOID

    @note  

**/
VOID SbPspMutexSmi_SmiDisable(VOID)
{
#if SMM_SUPPORT
    UINT8   Buffer;
    volatile UINT8  *SbMmioBase = (UINT8*)(UINTN)SB_MMIO_BASE;
    
    AcquirePspSmiRegMutexV2();
    
    // Disable Global SMI
    //UEFI_RWSbSmiIo8(FCH_SMI_REG98+3, BIT07, BIT07);  //EIP36094+
    Buffer =  *(volatile UINT8*)(SbMmioBase+SMI_BASE+0x98+0x03);
    Buffer |= BIT07;
    *(volatile UINT8*) (SbMmioBase+SMI_BASE+0x98+0x03) = Buffer;
    
    ReleasePspSmiRegMutexV2();
#endif
}

/**
    This function enables SMI

    @param VOID

    @retval VOID

    @note  

**/
VOID SbPspMutexSmi_SmiEnable(VOID)
{
#if SMM_SUPPORT
    UINT8   Buffer;
    volatile UINT8  *SbMmioBase = (UINT8*)(UINTN)SB_MMIO_BASE;
    
    AcquirePspSmiRegMutexV2();
    
    // Enable Global SMI
    // UEFI_RWSbSmiIo8(FCH_SMI_REG98+3, BIT07, 0); //EIP36094+
    Buffer =  *(volatile UINT8*)(SbMmioBase+SMI_BASE+0x98+0x03);
    Buffer &= ~BIT07;
    *(volatile UINT8*) (SbMmioBase+SMI_BASE+0x98+0x03) = Buffer;
    
    ReleasePspSmiRegMutexV2();
#endif // #if SMM_SUPPORT
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
