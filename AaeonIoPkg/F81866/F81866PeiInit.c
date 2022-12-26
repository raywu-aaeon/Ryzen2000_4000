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

#include <Setup.h>
#include <AmiCspLib.h>

VOID RayDebug80(UINT8 Time, UINT8 Code){
	UINTN i;
	
	i = 0x0FFFF | (Time << 16);
	while(i != 0){
		IoWrite8(0x80, Code);
		i--;
	}
}
//----------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//----------------------------------------------------------------------
#define		PORT_SELECT_REGISTER			0x27
	#define		GPIO_PROG_SEL			BIT2|BIT3
	#define		GPIO0_EN			0
	#define		GPIO1_EN			BIT2
	#define		GPIO2_EN			BIT3

#define		MULTI_FUNCTION_SELECT_1_REGISTER	0x28
	#define		LPT_GP_EN			BIT5

#define		UART_IRQ_SHARE_REGISTER			0xF0
	#define		RS485_EN			BIT4

#define		ACPICONTROLREGISTER1			0xF4
	#define		PWRCTRL				BIT1|BIT2
	#define		KEEP_LAST_STATE			0
	#define		ALWAYS_ON			BIT2
	#define		BYPASS_MODE			BIT1
	#define		ALWAYS_OFF			BIT1|BIT2

#define		GPIO0_OUTPUT_ENABLE_REGISTER	0xF0
#define		GPIO0_OUTPUT_DATA_REGISTER	0xF1
#define		GPIO0_DRIVE_ENABLE_REGISTER	0xF3
#define		GPIO1_OUTPUT_ENABLE_REGISTER	0xE0
#define		GPIO1_OUTPUT_DATA_REGISTER	0xE1
#define		GPIO1_DRIVE_ENABLE_REGISTER	0xE3
#define		GPIO2_OUTPUT_ENABLE_REGISTER	0xD0
#define		GPIO2_OUTPUT_DATA_REGISTER	0xD1
#define		GPIO2_DRIVE_ENABLE_REGISTER	0xD3
#define		GPIO3_OUTPUT_ENABLE_REGISTER	0xC0
#define		GPIO3_OUTPUT_DATA_REGISTER	0xC1
#define		GPIO3_DRIVE_ENABLE_REGISTER	0xC3
#define		GPIO4_OUTPUT_ENABLE_REGISTER	0xB0
#define		GPIO4_OUTPUT_DATA_REGISTER	0xB1
#define		GPIO4_DRIVE_ENABLE_REGISTER	0xB3
#define		GPIO5_OUTPUT_ENABLE_REGISTER	0xA0
#define		GPIO5_OUTPUT_DATA_REGISTER	0xA1
#define		GPIO5_DRIVE_ENABLE_REGISTER	0xA3
#define		GPIO6_OUTPUT_ENABLE_REGISTER	0x90
#define		GPIO6_OUTPUT_DATA_REGISTER	0x91
#define		GPIO6_DRIVE_ENABLE_REGISTER	0x93
#define		GPIO7_OUTPUT_ENABLE_REGISTER	0x80
#define		GPIO7_OUTPUT_DATA_REGISTER	0x81
#define		GPIO7_DRIVE_ENABLE_REGISTER	0x83
#define		GPIO8_OUTPUT_ENABLE_REGISTER	0x88
#define		GPIO8_OUTPUT_DATA_REGISTER	0x89
#define		GPIO8_DRIVE_ENABLE_REGISTER	0x8B

#define		GpioOutput		0
#define		GpioInput		1
#define		GpioLow			0
#define		GpioHigh		1
#define		GpioOpenDrain		0
#define		GpioPushPull		1

VOID F81866ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81866_CONFIG_INDEX, Index);
	IoWrite8(F81866_CONFIG_DATA, Data);
}
UINT8 F81866ConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(F81866_CONFIG_INDEX, Index);
	Data8 = IoRead8(F81866_CONFIG_DATA);
	return Data8;
}
VOID F81866LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
	IoWrite8(F81866_CONFIG_DATA, Ldn);
}
VOID F81866EnterConfigMode()
{
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
}
VOID F81866ExitConfigMode()
{
	// Exit config mode
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);
}
VOID F81866SetGpioPin(IN UINT8 GpioNum, IN UINT8 Type, IN UINT8 Level, IN UINT8 Drive)
{
	UINT8	Data8, Offset;
	
	F81866EnterConfigMode();	
	F81866LDNSelect(F81866_LDN_GPIO);		//GPIO Device Configuration Registers
	
	if( (GpioNum/10) <= 7 ){
		Offset = ( ~(GpioNum/10) );
		Offset = Offset << 4;
		Offset &= 0xF0;
	}
	else if ( (GpioNum/10) == 8 )
		Offset = 0x88;	
	Data8 = F81866ConfigRegisterRead(Offset + 3);	//Drive Enable Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Drive == 1)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset + 3, Data8);
	
	Data8 = F81866ConfigRegisterRead(Offset);	//Output Enable Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Type == 0)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset, Data8);
	
	Data8 = F81866ConfigRegisterRead(Offset + 1);	//Output Data Register
	Data8 &= ~( 1 << ( GpioNum%10 ) );
	if(Level == 1)
		Data8 |= ( 1 << ( GpioNum%10 ) );
	F81866ConfigRegisterWrite(Offset + 1, Data8);		
	F81866ExitConfigMode();
}

VOID F81866MiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
	EFI_STATUS	Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
       	
	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

	F81866EnterConfigMode();	

	// Restore AC Power Loss control _Begin >>
	{
		UINT8	Data8;

		F81866LDNSelect(F81866_LDN_PME);		// PME, ACPI and ERP Device Configuration Registers (LDN CR0A)
		Data8 = F81866ConfigRegisterRead(ACPICONTROLREGISTER1);
		Data8 &= ~(PWRCTRL);
		switch(SetupData.F81866RestoreACPowerLoss)
		{
			default:
			case 0: // Last State
				Data8 |= KEEP_LAST_STATE;
				break;
			case 1: // Always On
				Data8 |= ALWAYS_ON;
				break;
			case 2: // Always Off
				Data8 |= ALWAYS_OFF;
				break;
			case 3: // Bypass
				Data8 |= BYPASS_MODE;
				break;
		}
		F81866ConfigRegisterWrite(ACPICONTROLREGISTER1, Data8);
	}
	// Restore AC Power Loss control _End <<

	// UART RS485 auto flow control Enabled/Disabled _Begin >>
	{
		UINT8	Data8, i;
		UINT8	F81866AllUartLdn[6] = { F81866_LDN_UART1, F81866_LDN_UART2, F81866_LDN_UART3,\
						F81866_LDN_UART4, F81866_LDN_UART5, F81866_LDN_UART6 };

		for(i = 0; i < 6; i++)
		{
			F81866LDNSelect(F81866AllUartLdn[i]);		// All UART LDN
			Data8 = F81866ConfigRegisterRead(UART_IRQ_SHARE_REGISTER);
			Data8 &= ~(RS485_EN);
			if(SetupData.F81866UartAutoFlowControlEnable[i] == 1)
				Data8 |= RS485_EN;
			F81866ConfigRegisterWrite(UART_IRQ_SHARE_REGISTER, Data8);
		}
	}
	// UART RS485 auto flow control Enabled/Disabled _End <<

	// Parallel Port / Gpio multi function selection _Begin >>
	{
		UINT8	Data8;

		Data8 = F81866ConfigRegisterRead(PORT_SELECT_REGISTER);
		Data8 &= ~(GPIO_PROG_SEL);
		Data8 |= GPIO0_EN;

		Data8 = F81866ConfigRegisterRead(MULTI_FUNCTION_SELECT_1_REGISTER);
		Data8 &= ~(LPT_GP_EN);
		if(SetupData.F81866Gpio7x8x_Lpt_Switch == 0)
			Data8 |= LPT_GP_EN;
		F81866ConfigRegisterWrite(MULTI_FUNCTION_SELECT_1_REGISTER, Data8);
	}
	// Parallel Port / Gpio multi function selection _End <<

	// GPIO setup variable _Begin >>
	{
		UINT8	i;
		UINT8	Gpio_Oe, Gpio_Val, Gpio_DrvEn;

		F81866LDNSelect(F81866_LDN_GPIO);		//GPIO Device Configuration Registers

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO0X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio0x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio0x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio0x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO0_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO0_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO0_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO1X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio1x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio1x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio1x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO1_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO1_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO1_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO2X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio2x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio2x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio2x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO2_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO2_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO2_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO3X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio3x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio3x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio3x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO3_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO3_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO3_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO4X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio4x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio4x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio4x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO4_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO4_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO4_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO5X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio5x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio5x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio5x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO5_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO5_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO5_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO6X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio6x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio6x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio6x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO6_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO6_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO6_OUTPUT_ENABLE_REGISTER, Gpio_Oe);												

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO7X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio7x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio7x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio7x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO7_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO7_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO7_OUTPUT_ENABLE_REGISTER, Gpio_Oe);

		// GPIO8X Misc configuration
		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.F81866Gpio8x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.F81866Gpio8x_Val[i]) << i );
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.F81866Gpio8x_DrvEn[i]) << i );
		}
		F81866ConfigRegisterWrite(GPIO8_OUTPUT_DATA_REGISTER, Gpio_Val);
		F81866ConfigRegisterWrite(GPIO8_DRIVE_ENABLE_REGISTER, Gpio_DrvEn);
		F81866ConfigRegisterWrite(GPIO8_OUTPUT_ENABLE_REGISTER, Gpio_Oe);
	}
	// GPIO setup variable _End <<

	F81866ExitConfigMode();
}

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
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
    UINT8 index;

    for(index=0; index<sizeof(F81866PeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, F81866PeiDecodeTable[index].BaseAdd, F81866PeiDecodeTable[index].UID, F81866PeiDecodeTable[index].Type);
#endif
    
    ProgramRtRegisterTable(0, F81866PeiInitTable, sizeof(F81866PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));
    // Enter Configuration Mode.

    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
// F81866_CLEAR_UNUSED_LDN_RES >>
//    F81866_PeiClearDevResource(F81866_LDN_UART3);
//    F81866_PeiClearDevResource(F81866_LDN_UART4);
//    F81866_PeiClearDevResource(F81866_LDN_UART5);
//    F81866_PeiClearDevResource(F81866_LDN_UART6);
    #if !F81866_SERIAL_PORT1_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART1);
    #endif
    #if !F81866_SERIAL_PORT2_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART2);
    #endif
    #if !F81866_SERIAL_PORT3_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART3);
    #endif
    #if !F81866_SERIAL_PORT4_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART4);
    #endif
    #if !F81866_SERIAL_PORT5_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART5);
    #endif
    #if !F81866_SERIAL_PORT6_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_UART6);
    #endif
    #if !F81866_PARALLEL_PORT_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_LPT);
    #endif
    #if !F81866_KEYBOARD_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_PS2K);
    #endif
    #if !F81866_FLOPPY_PORT_PRESENT
        F81866_PeiClearDevResource(F81866_LDN_FDC);
    #endif
//F81866_CLEAR_UNUSED_LDN_RES <<
    // Exit Configuration Mode
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);

    F81866MiscSetupFunction(PeiServices);

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
