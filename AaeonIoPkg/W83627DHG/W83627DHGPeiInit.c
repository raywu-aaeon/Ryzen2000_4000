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
// Name:  <W83627DHGPeiInit.c>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <W83627DHGPeiIoTable.h>
#include <Setup.h>
#include <AmiCspLib.h>
//-------------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//-------------------------------------------------------------------------
VOID RayDebug80(UINT8 Time, UINT8 Code){
	UINTN i;
	
	i = 0x0FFFF | (Time << 16);
	while(i != 0){
		IoWrite8(0x80, Code);
		i--;
	}
}

//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------
VOID W83627DHGIsaWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(W83627DHG_CONFIG_INDEX, Index);
	IoWrite8(W83627DHG_CONFIG_DATA, Data);
}
UINT8 W83627DHGIsaRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(W83627DHG_CONFIG_INDEX, Index);
	Data8 = IoRead8(W83627DHG_CONFIG_DATA);
	return Data8;
}
VOID W83627DHGLDNSelect(UINT8 Ldn)
{
	IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_LDN_SEL_REGISTER);
	IoWrite8(W83627DHG_CONFIG_DATA, Ldn);
}
VOID W83627DHGEnterConfigMode()
{
	IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE);
}
VOID W83627DHGExitConfigMode()
{
	// Exit config mode
	IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_EXIT_VALUE);
}

VOID W83627DHG_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
	W83627DHGLDNSelect(Ldn);
	W83627DHGIsaWrite(W83627DHG_ACTIVATE_REGISTER, W83627DHG_DEACTIVATE_VALUE);
	W83627DHGIsaWrite(W83627DHG_BASE1_HI_REGISTER, 0);
	W83627DHGIsaWrite(W83627DHG_BASE1_LO_REGISTER, 0);
	W83627DHGIsaWrite(W83627DHG_IRQ1_REGISTER, 0);
}

VOID W83627DHGMiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
	EFI_STATUS	Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
       	
	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );


}
//*************************************************************************
// belows are functions defined
//*************************************************************************

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: SioPeiInitEntryPoint
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
EFI_STATUS W83627DHGPeiInitEntryPoint(
        IN       EFI_PEI_FILE_HANDLE  FileHandle,
        IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
//RayWu, REMOVE 2015/08/07 >>
//    UINT8 index;
//
//    for(index=0; index<sizeof(W83627DHGPeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, W83627DHGPeiDecodeTable[index].BaseAdd, W83627DHGPeiDecodeTable[index].UID, W83627DHGPeiDecodeTable[index].Type);
//RayWu, REMOVE 2015/08/07 <<
	ProgramRtRegisterTable(0, W83627DHGPeiInitTable, sizeof(W83627DHGPeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

	// Enter Configuration Mode.
	W83627DHGEnterConfigMode();

	#if !(W83627DHG_PARALLEL_PORT_PRESENT)
		W83627DHG_PeiClearDevResource(W83627DHG_LDN_LPT);
	#endif
	#if !(W83627DHG_FLOPPY_PORT_PRESENT)
		W83627DHG_PeiClearDevResource(W83627DHG_LDN_FDC);
	#endif
	#if !(W83627DHG_SERIAL_PORT1_PRESENT)
		W83627DHG_PeiClearDevResource(W83627DHG_LDN_UART1);
	#endif
	#if !(W83627DHG_SERIAL_PORT2_PRESENT)
		W83627DHG_PeiClearDevResource(W83627DHG_LDN_UART2);
	#endif

	W83627DHGMiscSetupFunction(PeiServices);

	// Exit Configuration Mode
	W83627DHGExitConfigMode();
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
