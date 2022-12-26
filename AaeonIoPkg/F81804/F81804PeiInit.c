//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file F81804PeiInit.c
  Porting for PEI phase.Just for necessary devices porting.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include <Setup.h>
#include <AmiCspLib.h>
extern IO_DECODE_DATA F81804PeiDecodeTable[];
extern UINT8 F81804PeiDecodeTableCount;
extern SIO_DEVICE_INIT_DATA F81804PeiInitTable[];
extern UINT8 F81804PeiInitTableCount;
//----------------------------------------------------------------------
// internal function declare; these functions are only used by this file.
//----------------------------------------------------------------------

#define		UART_RS485_EN_REGISTER			0xF0
#define		RS485_EN			BIT4

#define		ACPICONTROLREGISTER1			0xF4
#define		PWRCTRL				BIT1|BIT2
#define		KEEP_LAST_STATE		0
#define		ALWAYS_ON			2
#define		ALWAYS_ON_NOPSOUT	1
#define		ALWAYS_OFF			3

#define		GPIO0_OUTPUT_ENABLE_REGISTER	0xF0
#define		GPIO0_OUTPUT_DATA_REGISTER	0xF1
#define		GPIO0_DRIVE_ENABLE_REGISTER	0xF3
#define		GPIO1_OUTPUT_ENABLE_REGISTER	0xE0
#define		GPIO1_OUTPUT_DATA_REGISTER	0xE1
#define		GPIO1_DRIVE_ENABLE_REGISTER	0xE3
#define		GPIO2_OUTPUT_ENABLE_REGISTER	0xD0
#define		GPIO2_OUTPUT_DATA_REGISTER	0xD1
#define		GPIO5_OUTPUT_ENABLE_REGISTER	0xA0
#define		GPIO5_OUTPUT_DATA_REGISTER	0xA1
#define		GPIO6_OUTPUT_ENABLE_REGISTER	0x90
#define		GPIO6_OUTPUT_DATA_REGISTER	0x91
#define		GPIO6_DRIVE_ENABLE_REGISTER	0x93
#define		GPIO7_OUTPUT_ENABLE_REGISTER	0x80
#define		GPIO7_OUTPUT_DATA_REGISTER	0x81
#define		GPIO7_DRIVE_ENABLE_REGISTER	0x83
#define		GPIO9_OUTPUT_ENABLE_REGISTER	0x98
#define		GPIO9_OUTPUT_DATA_REGISTER	0x99
#define		GPIO9_DRIVE_ENABLE_REGISTER	0x9B

#define		GpioOutput		0
#define		GpioInput		1
#define		GpioLow			0
#define		GpioHigh		1
#define		GpioOpenDrain		0
#define		GpioPushPull		1

VOID F81804ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
IoWrite8(F81804_CONFIG_INDEX, Index);
IoWrite8(F81804_CONFIG_DATA, Data);
}
UINT8 F81804ConfigRegisterRead(UINT8 Index)
{
UINT8 Data8;
IoWrite8(F81804_CONFIG_INDEX, Index);
Data8 = IoRead8(F81804_CONFIG_DATA);
return Data8;
}
VOID F81804LDNSelect(UINT8 Ldn)
{
IoWrite8(F81804_CONFIG_INDEX,F81804_LDN_SEL_REGISTER);
IoWrite8(F81804_CONFIG_DATA, Ldn);
}
VOID F81804EnterConfigMode()
{
IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_ENTER_VALUE);
IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_ENTER_VALUE);
}
VOID F81804ExitConfigMode()
{
// Exit config mode
IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_EXIT_VALUE);
}

VOID F81804MiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
EFI_STATUS	Status;
SETUP_DATA				SetupData;
UINTN           			VariableSize = sizeof( SETUP_DATA );
EFI_GUID				gSetupGuid = SETUP_GUID;
EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
       
Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

F81804EnterConfigMode();	

// Restore AC Power Loss control _Begin >>
{
    UINT8	Data8;

   F81804LDNSelect(F81804_LDN_PME);		// PME, ACPI and ERP Device Configuration Registers (LDN CR0A)
    Data8 =F81804ConfigRegisterRead(ACPICONTROLREGISTER1);
    Data8 &= ~(PWRCTRL);
    switch(SetupData.F81804RestoreACPowerLoss)
    {
        default:
        case 0: // Last State
            Data8 |= (KEEP_LAST_STATE << 1);
            break;
        case 1: // Always On
            Data8 |= (ALWAYS_ON << 1);
            break;
        case 2: // Always Off
            Data8 |= (ALWAYS_OFF << 1);
            break;
        case 3: // Always On without PS_ON#
            Data8 |= (ALWAYS_ON_NOPSOUT << 1);
            break;
    }
   F81804ConfigRegisterWrite(ACPICONTROLREGISTER1, Data8);
}
// Restore AC Power Loss control _End <<

// UART RS485 auto flow control Enabled/Disabled _Begin >>
{
    UINT8	Data8, i;
    UINT8	F81804AllUartLdn[2] = {F81804_LDN_UART1,F81804_LDN_UART2 };

    for(i = 0; i < 2; i++)
    {
       F81804LDNSelect(F81804AllUartLdn[i]);		// All UART LDN
        Data8 =F81804ConfigRegisterRead(UART_RS485_EN_REGISTER);
        Data8 &= ~(RS485_EN);
        if(SetupData.F81804UartAutoFlowControlEnable[i] == 1)
            Data8 |= RS485_EN;
       F81804ConfigRegisterWrite(UART_RS485_EN_REGISTER, Data8);
    }
}
// UART RS485 auto flow control Enabled/Disabled _End <<

	// GPIO setup variable _Begin >>
	{
		UINT8	i;
		UINT8	Gpio_Oe, Gpio_Val, Gpio_DrvEn;
		BOOLEAN F81804Gpio0x_Support[8] = {1, 0, 0, 0, 1, 0, 0, 0};
		BOOLEAN F81804Gpio1x_Support[8] = {0, 0, 1, 0, 1, 1, 1, 1};
		BOOLEAN F81804Gpio2x_Support[8] = {0, 0, 1, 1, 1, 1, 1, 1};
		BOOLEAN F81804Gpio5x_Support[8] = {1, 1, 1, 1, 1, 1, 1, 1};
		BOOLEAN F81804Gpio6x_Support[8] = {0, 0, 0, 0, 0, 0, 1, 1};
		BOOLEAN F81804Gpio7x_Support[8] = {1, 0, 0, 0, 0, 0, 0, 0};
		BOOLEAN F81804Gpio9x_Support[8] = {0, 1, 1, 1, 1, 1, 0, 1};

		F81804LDNSelect(F81804_LDN_GPIO);		//GPIO Device Configuration Registers

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO0X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio0x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio0x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio0x_Val[i]) << i ) ;
				Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81804Gpio0x_DrvEn[i]) << i );
			}
		}
		F81804ConfigRegisterWrite(GPIO0_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO0_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81804ConfigRegisterWrite(GPIO0_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO1X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio1x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio1x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio1x_Val[i]) << i ) ;
				Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81804Gpio1x_DrvEn[i]) << i );
			}
		}
		F81804ConfigRegisterWrite(GPIO1_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO1_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81804ConfigRegisterWrite(GPIO1_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO2X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio2x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio2x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio2x_Val[i]) << i ) ;
			}
		}
		F81804ConfigRegisterWrite(GPIO2_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO2_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO5X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio5x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio5x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio5x_Val[i]) << i ) ;
			}
		}
		F81804ConfigRegisterWrite(GPIO5_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO5_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO6X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio6x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio6x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio6x_Val[i]) << i ) ;
				Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81804Gpio6x_DrvEn[i]) << i );
			}
		}
		F81804ConfigRegisterWrite(GPIO6_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO6_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81804ConfigRegisterWrite(GPIO6_OUTPUT_ENABLE_REGISTER, Gpio_Oe);												

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO7X Misc configuration
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio7x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio7x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio7x_Val[i]) << i ) ;
				Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81804Gpio7x_DrvEn[i]) << i );
			}
		}
		F81804ConfigRegisterWrite(GPIO7_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO7_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81804ConfigRegisterWrite(GPIO7_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		// GPIO9X Misc configuration
		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		for (i = 0; i < 8; i++)
		{
			if(F81804Gpio9x_Support[i])
			{
				Gpio_Oe |= ( (BOOLEAN)(SetupData.F81804Gpio9x_Oe[i]) << i );
				Gpio_Val |= ( (BOOLEAN)(SetupData.F81804Gpio9x_Val[i]) << i ) ;
				Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81804Gpio9x_DrvEn[i]) << i );
			}
		}
		F81804ConfigRegisterWrite(GPIO9_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81804ConfigRegisterWrite(GPIO9_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81804ConfigRegisterWrite(GPIO9_OUTPUT_ENABLE_REGISTER, Gpio_Oe);		
	}
	// GPIO setup variable _End <<

F81804ExitConfigMode();
}
//----------------------------------------------------------------------
//
// Procedure: F81804_PeiClearDevResource
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
VOID F81804_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(F81804_CONFIG_INDEX, F81804_LDN_SEL_REGISTER);
    IoWrite8(F81804_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(F81804_CONFIG_INDEX, F81804_ACTIVATE_REGISTER);
    IoWrite8(F81804_CONFIG_DATA,  F81804_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(F81804_CONFIG_INDEX, F81804_BASE1_HI_REGISTER);
    IoWrite8(F81804_CONFIG_DATA,  0);
    IoWrite8(F81804_CONFIG_INDEX, F81804_BASE1_LO_REGISTER);
    IoWrite8(F81804_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(F81804_CONFIG_INDEX, F81804_IRQ1_REGISTER);
    IoWrite8(F81804_CONFIG_DATA,  0);
    return;
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

  @retval  EFI_SUCESS       The entry point of F81804PeiInit executes successfully.
  @retval  Others           Some error occurs during the execution of this function. 
**/
EFI_STATUS F81804PeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    UINT8 index = 0;

#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
    for(index=0; index<F81804PeiDecodeTableCount; index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, F81804PeiDecodeTable[index].BaseAdd, F81804PeiDecodeTable[index].UID, F81804PeiDecodeTable[index].Type);
#endif
    ProgramRtRegisterTable(0, F81804PeiInitTable, F81804PeiInitTableCount);

    IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_ENTER_VALUE);
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
//F81804_CLEAR_UNUSED_LDN_RES >>
    #if !F81804_SERIAL_PORT1_PRESENT
       F81804_PeiClearDevResource(F81804_LDN_UART1);
    #endif
    #if !F81804_SERIAL_PORT2_PRESENT
       F81804_PeiClearDevResource(F81804_LDN_UART2);
    #endif
    #if !F81804_KEYBOARD_PRESENT
       F81804_PeiClearDevResource(F81804_LDN_PS2K);
    #endif
//F81804_CLEAR_UNUSED_LDN_RES <<
    // Exit Configuration Mode
    IoWrite8(F81804_CONFIG_INDEX,F81804_CONFIG_MODE_EXIT_VALUE);

   F81804MiscSetupFunction(PeiServices);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

