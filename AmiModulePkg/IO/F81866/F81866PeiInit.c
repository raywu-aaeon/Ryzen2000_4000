//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866PeiInit.c>
//
// Description: Porting for PEI phase.Just for necessary devices porting.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include "F81866PeiIoTable.h"

//----------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//----------------------------------------------------------------------

//**********************************************************************
// belows are functions defined
//**********************************************************************
// <AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: F81866_PeiClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  IN  UINT8    Ldn
// Output:
//  NONE
//
//----------------------------------------------------------------------
// <AMI_PHDR_END>
VOID F81866_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(F81866_CONFIG_INDEX, F81866_ACTIVATE_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  F81866_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_HI_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_LO_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(F81866_CONFIG_INDEX, F81866_IRQ1_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,  0);
    return;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: F81866PeiInitEntryPoint
//
// Description:
//  This function provide PEI phase SIO initialization
//
// Input:
//  IN  EFI_FFS_FILE_HEADER    *FfsHeader - Logical Device's information
//  IN  EFI_PEI_SERVICES       **PeiServices  - Read/Write PCI config space
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//----------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS F81866PeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    UINT8 index;

    for(index=0; index<sizeof(F81866PeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, F81866PeiDecodeTable[index].BaseAdd, F81866PeiDecodeTable[index].UID, F81866PeiDecodeTable[index].Type);

    ProgramRtRegisterTable(0, F81866PeiInitTable, sizeof(F81866PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));
    // Enter Configuration Mode.

    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
    F81866_PeiClearDevResource(F81866_LDN_UART3);
    F81866_PeiClearDevResource(F81866_LDN_UART4);
    F81866_PeiClearDevResource(F81866_LDN_UART5);
    F81866_PeiClearDevResource(F81866_LDN_UART6);
    // Exit Configuration Mode
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
