/** @file F75113PeiInit.c
  Porting for PEI phase.Just for necessary devices porting.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <token.h>
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include <Setup.h>
#include <AmiCspLib.h>  
#include "F75113PeiIoTable.h"

extern SIO_DEVICE_INIT_DATA F75113PeiInitTable[];
extern UINT8 F75113PeiInitTableCount;
//----------------------------------------------------------------------
// internal function declare; these functions are only used by this file.
//----------------------------------------------------------------------
VOID SET_F75113_GPIO(
	IN UINT8 Type,
	IN UINT8 Level,
	IN UINT8 GpioNum
)
{
	UINT8    Value;
	UINT8    GpioSetNum;
	UINT8    GpioBitNum;
	UINT8    InOutRegArray[5] = {0x10, 0x20, 0x30, 0x40, 0x70};
	UINT8    OutDataRegArray[5] = {0x11, 0x21, 0x31, 0x41, 0x71};
	
	GpioSetNum = GpioNum/10;
	GpioBitNum = GpioNum%10;


	// Set In/Output Register
	IoWrite8(F75113_CONFIG_INDEX, InOutRegArray[GpioSetNum]);
	Value = IoRead8(F75113_CONFIG_DATA);
	Value &= ~(1 << GpioBitNum);
	Value |= (Type << GpioBitNum);
	IoWrite8(F75113_CONFIG_DATA, Value);

	// Set Level Register
	IoWrite8(F75113_CONFIG_INDEX, OutDataRegArray[GpioSetNum]);
	Value = IoRead8(F75113_CONFIG_DATA);
	Value &= ~(1 << GpioBitNum);
	Value |= (Level << GpioBitNum);
	IoWrite8(F75113_CONFIG_DATA, Value);
}

VOID INIT_F75113_GPIO_CONFIG(SETUP_DATA SetupData)
{
	UINT8		i, Value;

    IoWrite8(F75113_CONFIG_INDEX, F75113_LDN_SEL_REGISTER);
    IoWrite8(F75113_CONFIG_DATA, F75113_LDN_GPIO);

    //Disable SMART_PD_MD
    IoWrite8(F75113_CONFIG_INDEX, 0x01);
    Value = IoRead8(F75113_CONFIG_DATA);
    Value &= ~BIT1;
    IoWrite8(F75113_CONFIG_DATA, Value);

    IoWrite8(F75113_CONFIG_INDEX, 0x60);
    IoWrite8(F75113_CONFIG_DATA, F75113_GPIO_BASE_ADDRESS >> 8);

    IoWrite8(F75113_CONFIG_INDEX, 0x61);
    IoWrite8(F75113_CONFIG_DATA, F75113_GPIO_BASE_ADDRESS & 0xFF);    

	for (i=0 ; i<8 ; i++) {
		// Init GP0x Group
		SET_F75113_GPIO( 
					SetupData.F75113_GP0x_Type[i],
					SetupData.F75113_GP0x_Data[i],
					i );
		// Init GP1x Group
		SET_F75113_GPIO( 
					SetupData.F75113_GP1x_Type[i],
					SetupData.F75113_GP1x_Data[i],
					i+10 );
		// Init GP2x Group
		SET_F75113_GPIO( 
					SetupData.F75113_GP2x_Type[i],
					SetupData.F75113_GP2x_Data[i],
					i+20 );
		// Init GP3x Group
		SET_F75113_GPIO( 
					SetupData.F75113_GP3x_Type[i],
					SetupData.F75113_GP3x_Data[i],
					i+30 );		
	}

	for (i=0 ; i<6 ; i++) {
		// Init GP4x Group
		SET_F75113_GPIO( 
					SetupData.F75113_GP4x_Type[i],
					SetupData.F75113_GP4x_Data[i],
					i+40 );
	}
}

//----------------------------------------------------------------------
// global function declare ; these functions are used for other files.
//----------------------------------------------------------------------
//**********************************************************************
// below are functions defined
//**********************************************************************
/**
  This function provide PEI phase SIO initialization

  @param  FileHandle     Handle of the file being invoked.
  @param  PeiServices   Describes the list of possible PEI Services.

  @retval  EFI_SUCESS       The entry point of F75113PeiInit executes successfully.
  @retval  Others           Some error occurs during the execution of this function. 
**/
EFI_STATUS F75113PeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    // Pei ReadOnlyVariable2 PPI locate
    EFI_STATUS				Status;
    SETUP_DATA				SetupData;
    UINTN           		VariableSize = sizeof( SETUP_DATA );
    EFI_GUID				gSetupGuid = SETUP_GUID;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;

	PEI_TRACE((-1, PeiServices, "F75113PeiInitEntryPoint Start\n"));

    Status = (*PeiServices)->LocatePpi(PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable);    
    
    if (!EFI_ERROR(Status)) {   	
    	Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData);
    }  

    ProgramRtRegisterTable(0, F75113PeiInitTable, F75113PeiInitTableCount);

    // Enter Configuration Mode
    IoWrite8(F75113_CONFIG_INDEX, F75113_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F75113_CONFIG_INDEX, F75113_CONFIG_MODE_ENTER_VALUE);

    #if (F75113_GPIO_PORT_PRESENT)
	// Init F75113 GPIO Configuration
    INIT_F75113_GPIO_CONFIG(SetupData);
    #endif //F75113_GPIO_PORT_PRESENT

    // Exit Configuration Mode
    IoWrite8(F75113_CONFIG_INDEX, F75113_CONFIG_MODE_EXIT_VALUE);    

    return EFI_SUCCESS;
}


