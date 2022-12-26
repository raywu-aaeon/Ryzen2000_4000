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
// Name:  <F81216SECPeiInit.c>
//
// Description: Porting for PEI phase.Just for necessary devices porting.
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include <F81216SECPeiIoTable.h>
#include <Setup.h>
#include <AmiCspLib.h>

#define     RS485_ENABLE_REGISTER           0xF0
#define     RS485_URA                       BIT4
//-------------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------

//*************************************************************************
// belows are functions defined
//*************************************************************************
VOID F81216SECConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
    IoWrite8(F81216SEC_CONFIG_INDEX, Index);
    IoWrite8(F81216SEC_CONFIG_DATA, Data);
}
UINT8 F81216SECConfigRegisterRead(UINT8 Index)
{
    UINT8 Data8;
    IoWrite8(F81216SEC_CONFIG_INDEX, Index);
    Data8 = IoRead8(F81216SEC_CONFIG_DATA);
    return Data8;
}
VOID F81216SECLDNSelect(UINT8 Ldn)
{
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_LDN_SEL_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, Ldn);
}
VOID F81216SECEnterConfigMode()
{
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);
}
VOID F81216SECExitConfigMode()
{
    // Exit config mode
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_EXIT_VALUE);
}

VOID F81216SECMiscSetupFunction(IN CONST EFI_PEI_SERVICES  **PeiServices)
{
    EFI_STATUS                          Status;
    SETUP_DATA                          SetupData;
    UINTN                               VariableSize = sizeof( SETUP_DATA );
    EFI_GUID                            gSetupGuid = SETUP_GUID;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable = NULL;
        
    Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

    F81216SECEnterConfigMode();    

    // UART RS485 auto flow control Enabled/Disabled _Begin >>
    {
        UINT8   Data8, i;
        UINT8   F81216SECAllUartLdn[4] = { F81216SEC_LDN_UART1, F81216SEC_LDN_UART2, F81216SEC_LDN_UART3, F81216SEC_LDN_UART4};

        for(i = 0; i < 4; i++)
        {
            F81216SECLDNSelect(F81216SECAllUartLdn[i]);       // All UART LDN
            Data8 = F81216SECConfigRegisterRead(RS485_ENABLE_REGISTER);
            Data8 &= ~(RS485_URA);
            if(SetupData.F81216SECUartAutoFlowControlEnable[i] == 1)
                Data8 |= RS485_URA;
            F81216SECConfigRegisterWrite(RS485_ENABLE_REGISTER, Data8);
        }
    }
    // UART RS485 auto flow control Enabled/Disabled _End <<

    F81216SECExitConfigMode();
}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81216SEC_PeiClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  SIO_DEV2* dev
// Output:
//  NONE
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID F81216SEC_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_LDN_SEL_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_ACTIVATE_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA,  F81216SEC_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_BASE1_HI_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA,  0);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_BASE1_LO_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_IRQ1_REGISTER);
    IoWrite8(F81216SEC_CONFIG_DATA,  0);
    return;
}

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: F81216SECPeiInitEntryPoint
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
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS F81216SECPeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
//RayWu, REMOVE 2015/03/06 >>
//    UINT8 index;
//
//    for(index=0; index<sizeof(F81216SECPeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, F81216SECPeiDecodeTable[index].BaseAdd, F81216SECPeiDecodeTable[index].UID, F81216SECPeiDecodeTable[index].Type);
//RayWu, REMOVE 2015/03/06 <<
    ProgramRtRegisterTable(0, F81216SECPeiInitTable, sizeof(F81216SECPeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));
    // Enter Configuration Mode.
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_ENTER_VALUE);
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
    #if !F81216SEC_SERIAL_PORT1_PRESENT
    F81216SEC_PeiClearDevResource(F81216SEC_LDN_UART1);
    #endif
    #if !F81216SEC_SERIAL_PORT2_PRESENT
    F81216SEC_PeiClearDevResource(F81216SEC_LDN_UART2);
    #endif
    #if !F81216SEC_SERIAL_PORT3_PRESENT
    F81216SEC_PeiClearDevResource(F81216SEC_LDN_UART3);
    #endif
    #if !F81216SEC_SERIAL_PORT4_PRESENT
    F81216SEC_PeiClearDevResource(F81216SEC_LDN_UART4);
    #endif
    // Exit Configuration Mode
    IoWrite8(F81216SEC_CONFIG_INDEX, F81216SEC_CONFIG_MODE_EXIT_VALUE);

    F81216SECMiscSetupFunction(PeiServices);

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


