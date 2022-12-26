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
// Name:  <IT8728FPeiInit.c>
//
// Description: Porting for PEI phase.Just for necessary devices porting.
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiPeiLib.h>
#include <IT8728FPeiIoTable.h>

#include <Setup.h>
#include <AmiCspLib.h>

//-------------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//-------------------------------------------------------------------------
#define		PCR1			0xF2
#define		PCR2			0xF4
#define		High			1
#define		Low			0

#define		SERIAL_PORT_SCR		0xF0
	#define		IRQ_TYPE	BIT0|BIT1
	#define		NonShare	0
	#define		Share		BIT0

#define		GPIO1X_DRVEN_REG	0xB8
#define		GPIO2X_DRVEN_REG	0xB9
#define		GPIO3X_DRVEN_REG	0xBA
#define		GPIO4X_DRVEN_REG	0xBB
#define		GPIO5X_DRVEN_REG	0xBC
#define		GPIO6X_DRVEN_REG	0xBD

#define		GPIO1X_OE_REG	0xC8
#define		GPIO2X_OE_REG	0xC9
#define		GPIO3X_OE_REG	0xCA
#define		GPIO4X_OE_REG	0xCB
#define		GPIO5X_OE_REG	0xCC
#define		GPIO6X_OE_REG	0xCD
#define		GPIO7X_OE_REG	0xCE
#define		GPIO8X_OE_REG	0xCF

#define		GPIO1X_VAL_OFFSET	0
#define		GPIO2X_VAL_OFFSET	1
#define		GPIO3X_VAL_OFFSET	2
#define		GPIO4X_VAL_OFFSET	3
#define		GPIO5X_VAL_OFFSET	4
#define		GPIO6X_VAL_OFFSET	5
#define		GPIO7X_VAL_OFFSET	6
#define		GPIO8X_VAL_OFFSET	7
//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------
void IT8728FHWMRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(IT8728F_HWM_INDEX_PORT, Index);
	IoWrite8(IT8728F_HWM_DATA_PORT, Data);
}
UINT8 IT8728FHWMRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(IT8728F_HWM_INDEX_PORT, Index);
	Data8 = IoRead8(IT8728F_HWM_DATA_PORT);
	return Data8;
}
void IT8728FLDNSelect(UINT8 Ldn)
{
	IoWrite8(IT8728F_CONFIG_INDEX, 0x07);
	IoWrite8(IT8728F_CONFIG_DATA, Ldn);
}
void IT8728FConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(IT8728F_CONFIG_INDEX, Index);
	IoWrite8(IT8728F_CONFIG_DATA, Data);
}
UINT8 IT8728FConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(IT8728F_CONFIG_INDEX, Index);
	Data8 = IoRead8(IT8728F_CONFIG_DATA);
	return Data8;
}
void IT8728FEnterConfigMode()
{
	UINT8 IT8728FConfigModeEnterValue[4] = {0x87,0x01,0x55,0x55};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x03;i++){
		IoWrite8(IT8728F_CONFIG_INDEX, IT8728FConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}
void IT8728FExitConfigMode()
{
	UINT8 IT8728FConfigModeExitRegister = 0x02;

	// Exit config mode
	IoWrite8(IT8728F_CONFIG_INDEX, IT8728FConfigModeExitRegister);
	IoWrite8(0xEB, 0xFF); // IO delay
	IoWrite8(IT8728F_CONFIG_DATA, BIT1);
}
void IT8728FGpioOutputControl(UINT8 GpioNum, UINT8 Level)
{
	UINT8 Data8;
	UINT16 Address;
	
	Address = IT8728F_GPIO_BASE_ADDRESS + ((GpioNum/10)-1);
	Data8 = IoRead8(Address);
	Data8 &= ~(1 << (GpioNum%10));
	if(Level == High)
		Data8 |= (1 << (GpioNum%10));
	IoWrite8(Address, Data8);
}

#if defined(IT8728_SMF1_SUPPORT) && (IT8728_SMF1_SUPPORT == 1)
void IT8728SmartFan1Support(UINT8 IT8728SMF1Control, UINT8 IT8728SMF1Mode, UINT8 IT8728SMF1PWMDuty
			, UINT8 IT8728SMF1SPinPWMDuty, UINT8 IT8728SMF1TempSrc, UINT8 IT8728SMF1OffTemp
			, UINT8 IT8728SMF1StartTemp, UINT8 IT8728SMF1FullTemp, UINT8 IT8728SMF1PWMSlope)
{
	UINT8 Data8;
	
	switch(IT8728SMF1Control){
		case 0:	//Smart FAN disable, always running under full speed
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8&(~BIT0) );
			Data8 = IT8728FHWMRegisterRead(0x14);
			IT8728FHWMRegisterWrite( 0x14, Data8|BIT0 );
			break;
		case 1:	//Smart FAN enable
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8|BIT0 );
			
			switch(IT8728SMF1Mode){
				case 0: //Manual Mode
					Data8 = IT8728FHWMRegisterRead(0x15);
					IT8728FHWMRegisterWrite( 0x15, Data8&(~BIT7) );
					IT8728FHWMRegisterWrite( 0x63, IT8728SMF1PWMDuty );
					break;
				case 1: //Automatic Mode
					Data8 = IT8728FHWMRegisterRead(0x15);
					Data8 |= BIT7;
					Data8 &= ~(BIT0+BIT1); //Temperature Input Selection
					Data8 |= IT8728SMF1TempSrc;
					Data8 &= ~BIT2; //Tachometer Closed-loop Mode: Disable
					IT8728FHWMRegisterWrite( 0x15, Data8 );
					IT8728FHWMRegisterWrite( 0x63, IT8728SMF1SPinPWMDuty );
					IT8728FHWMRegisterWrite( 0x60, IT8728SMF1OffTemp );
					IT8728FHWMRegisterWrite( 0x61, IT8728SMF1StartTemp );
					IT8728FHWMRegisterWrite( 0x62, IT8728SMF1FullTemp );
					IT8728FHWMRegisterWrite( 0x64, IT8728SMF1PWMSlope << 3 );
					break;
				default :
					break;
			}
			break;
		default :
			break;
	} //switch(IT8728SMF1Control)
}
#endif //IT8728_SMF1_SUPPORT
#if defined(IT8728_SMF2_SUPPORT) && (IT8728_SMF2_SUPPORT == 1)
void IT8728SmartFan2Support(UINT8 IT8728SMF2Control, UINT8 IT8728SMF2Mode, UINT8 IT8728SMF2PWMDuty
			, UINT8 IT8728SMF2SPinPWMDuty, UINT8 IT8728SMF2TempSrc, UINT8 IT8728SMF2OffTemp
			, UINT8 IT8728SMF2StartTemp, UINT8 IT8728SMF2FullTemp, UINT8 IT8728SMF2PWMSlope)
{
	UINT8 Data8;
	
	switch(IT8728SMF2Control){
		case 0:	//Smart FAN disable, always running under full speed
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8&(~BIT1) );
			Data8 = IT8728FHWMRegisterRead(0x14);
			IT8728FHWMRegisterWrite( 0x14, Data8|BIT1 );
			break;
		case 1:	//Smart FAN enable
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8|BIT1 );
			
			switch(IT8728SMF2Mode){
				case 0: //Manual Mode
					Data8 = IT8728FHWMRegisterRead(0x16);
					IT8728FHWMRegisterWrite( 0x16, Data8&(~BIT7) );
					IT8728FHWMRegisterWrite( 0x6B, IT8728SMF2PWMDuty );
					break;
				case 1: //Automatic Mode
					Data8 = IT8728FHWMRegisterRead(0x16);
					Data8 |= BIT7;
					Data8 &= ~(BIT0+BIT1); //Temperature Input Selection
					Data8 |= IT8728SMF2TempSrc;
					Data8 &= ~BIT2; //Tachometer Closed-loop Mode: Disable
					IT8728FHWMRegisterWrite( 0x16, Data8 );
					IT8728FHWMRegisterWrite( 0x6B, IT8728SMF2SPinPWMDuty );
					IT8728FHWMRegisterWrite( 0x68, IT8728SMF2OffTemp );
					IT8728FHWMRegisterWrite( 0x69, IT8728SMF2StartTemp );
					IT8728FHWMRegisterWrite( 0x6A, IT8728SMF2FullTemp );
					IT8728FHWMRegisterWrite( 0x6C, IT8728SMF2PWMSlope << 3 );
					break;
				default :
					break;
			}
			break;
		default :
			break;
	} //switch(IT8728SMF2Control)
}
#endif //IT8728_SMF2_SUPPORT
// >> 2015/08/25 Eric
#if defined(IT8728_SMF3_SUPPORT) && (IT8728_SMF3_SUPPORT == 1)
void IT8728SmartFan3Support(UINT8 IT8728SMF3Control, UINT8 IT8728SMF3Mode, UINT8 IT8728SMF3PWMDuty
			, UINT8 IT8728SMF3SPinPWMDuty, UINT8 IT8728SMF3TempSrc, UINT8 IT8728SMF3OffTemp
			, UINT8 IT8728SMF3StartTemp, UINT8 IT8728SMF3FullTemp, UINT8 IT8728SMF3PWMSlope)
{
	UINT8 Data8;
	
	switch(IT8728SMF3Control){
		case 0:	//Smart FAN disable, always running under full speed
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8&(~BIT2) );
			Data8 = IT8728FHWMRegisterRead(0x14);
			IT8728FHWMRegisterWrite( 0x14, Data8|BIT2 );
			break;
		case 1:	//Smart FAN enable
			Data8 = IT8728FHWMRegisterRead(0x13);
			IT8728FHWMRegisterWrite( 0x13, Data8|BIT2 );
			
			switch(IT8728SMF3Mode){
				case 0: //Manual Mode
					Data8 = IT8728FHWMRegisterRead(0x17);
					IT8728FHWMRegisterWrite( 0x17, Data8&(~BIT7) );
					IT8728FHWMRegisterWrite( 0x73, IT8728SMF3PWMDuty );
					break;
				case 1: //Automatic Mode
					Data8 = IT8728FHWMRegisterRead(0x17);
					Data8 |= BIT7;
					Data8 &= ~(BIT0+BIT1); //Temperature Input Selection
					Data8 |= IT8728SMF3TempSrc;
					Data8 &= ~BIT2; //Tachometer Closed-loop Mode: Disable
					IT8728FHWMRegisterWrite( 0x17, Data8 );
					IT8728FHWMRegisterWrite( 0x73, IT8728SMF3SPinPWMDuty );
					IT8728FHWMRegisterWrite( 0x70, IT8728SMF3OffTemp );
					IT8728FHWMRegisterWrite( 0x71, IT8728SMF3StartTemp );
					IT8728FHWMRegisterWrite( 0x72, IT8728SMF3FullTemp );
					IT8728FHWMRegisterWrite( 0x74, IT8728SMF3PWMSlope << 3 );
					break;
				default :
					break;
			}
			break;
		default :
			break;
	} //switch(IT8728SMF3Control)
}
#endif //IT8728_SMF3_SUPPORT
// << 2015/08/25 Eric
// >> 2017/03/22 Eric
#if defined(IT8728_SMF4_SUPPORT) && (IT8728_SMF4_SUPPORT == 1)
void IT8728SmartFan4Support(SETUP_DATA *SetupData) {
	UINT8 Data8;

	Data8 = IT8728FHWMRegisterRead(0x0B) & (UINT8)~(BIT1 + BIT0);
	Data8 |= SetupData->IT8728SMF4Mode;
	IT8728FHWMRegisterWrite(0x0B, Data8);
}
#endif // IT8728_SMF4_SUPPORT
#if defined(IT8728_SMF5_SUPPORT) && (IT8728_SMF5_SUPPORT == 1)
void IT8728SmartFan5Support(SETUP_DATA *SetupData) {
	UINT8 Data8;

	Data8 = IT8728FHWMRegisterRead(0x0B) & (UINT8)~(BIT3 + BIT2);
	Data8 |= SetupData->IT8728SMF5Mode << 2;
	IT8728FHWMRegisterWrite(0x0B, Data8);
}
#endif // IT8728_SMF5_SUPPORT
// << 2017/03/22 Eric
//*************************************************************************
// belows are functions defined
//*************************************************************************
VOID IT8728FMiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
	EFI_STATUS	Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
       	
	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

	IT8728FEnterConfigMode();

	// Restore AC Power Loss control _Begin >>
	{
		UINT8	Data8;

		IT8728FLDNSelect(IT8728F_LDN_ENV);		// Environment Controller Configuration Registers (LDN=04h)
		Data8 = IT8728FConfigRegisterRead(PCR1);
		Data8 &= ~(BIT5);
		switch(SetupData.IT8728FRestoreACPowerLoss)
		{
			default:
			case 0: // Last State
				Data8 |= BIT5;
				break;
			case 1: // Always On
				break;
			case 2: // Always Off
				break;
			case 3: // By Pass
				break;
		}
		IT8728FConfigRegisterWrite(PCR1, Data8);

		Data8 = IT8728FConfigRegisterRead(PCR2);
		Data8 &= ~(BIT6 + BIT5);
		switch(SetupData.IT8728FRestoreACPowerLoss)
		{
			default:
			case 0: // Last State
				break;
			case 1: // Always On
				Data8 |= BIT5;
				break;
			case 2: // Always Off
				break;
			case 3: // By Pass
				Data8 |= (BIT6 + BIT5);
				break;
		}
		IT8728FConfigRegisterWrite(PCR2, Data8);
	}
	// Restore AC Power Loss control _End <<

	// GPIO setup variable _Begin >>
	{
		UINT8	i;
		UINT8	Gpio_Oe, Gpio_Val, Gpio_DrvEn;

		IT8728FLDNSelect(IT8728F_LDN_GPIO);		//GPIO Device Configuration Registers

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO1X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio1x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio1x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio1x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO1X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO1X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO1X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO2X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio2x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio2x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio2x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO2X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO2X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO2X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO3X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio3x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio3x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio3x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO3X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO3X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO3X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO4X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio4x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio4x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio4x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO4X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO4X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO4X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO5X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio5x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio5x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio5x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO5X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO5X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO5X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO6X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio6x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio6x_Val[i]) << i ) ;
			Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio6x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO6X_VAL_OFFSET, Gpio_Val);
		IT8728FConfigRegisterWrite(GPIO6X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO6X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO7X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio7x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio7x_Val[i]) << i ) ;
			//Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio7x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO7X_VAL_OFFSET, Gpio_Val);
		//IT8728FConfigRegisterWrite(GPIO7X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO7X_OE_REG, Gpio_Oe);

		Gpio_Oe = Gpio_Val = Gpio_DrvEn = 0;
		// GPIO8X Misc configuration
		for (i = 0; i < 8; i++)
		{
			Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8728FGpio8x_Oe[i]) << i );
			Gpio_Val |= ( (BOOLEAN)(SetupData.IT8728FGpio8x_Val[i]) << i ) ;
			//Gpio_DrvEn |= ( (BOOLEAN)(SetupData.IT8728FGpio8x_DrvEn[i]) << i );
		}
		IoWrite8(IT8728F_GPIO_BASE_ADDRESS+ GPIO8X_VAL_OFFSET, Gpio_Val);
		//IT8728FConfigRegisterWrite(GPIO8X_DRVEN_REG, Gpio_DrvEn);
		IT8728FConfigRegisterWrite(GPIO8X_OE_REG, Gpio_Oe);

	}
	// GPIO setup variable _End <<

	// UART IRQ Sharing control _Begin >>
	{
		UINT8	Data8;

		IT8728FLDNSelect(IT8728F_LDN_UART1);
		Data8 = IT8728FConfigRegisterRead(SERIAL_PORT_SCR);
		Data8 &= ~(IRQ_TYPE);
		Data8 |= NonShare;
		IT8728FConfigRegisterWrite(SERIAL_PORT_SCR, Data8);

		IT8728FLDNSelect(IT8728F_LDN_UART2);
		Data8 = IT8728FConfigRegisterRead(SERIAL_PORT_SCR);
		Data8 &= ~(IRQ_TYPE);
		Data8 |= NonShare;
		IT8728FConfigRegisterWrite(SERIAL_PORT_SCR, Data8);
	}
	// UART IRQ Sharing control _End <<

	IT8728FExitConfigMode();

	// PECI Temperature Correction _Begin >>
	#if defined(PECI_TEMP_ADJUST_FOR_INTEL_CPU) && (PECI_TEMP_ADJUST_FOR_INTEL_CPU != 0)
	{
		#define     MSR_TEMPERATURE_TARGET	0x000001A2
        	UINT64      Temp;
        	UINT8       TjMax;
        	UINT8       flag;
        	UINT8	    PECI_ADJUST_REG[] = { 0x56, 0x57, 0x59 };

        	// Read Intel CPU Tjmax value
        	Temp = AsmReadMsr64(MSR_TEMPERATURE_TARGET);
        	TjMax = (UINT8)(Shr64(Temp, 16));

        	// Enable Thermal Diode Zero Degree Adjust Register Write
        	flag = IT8728FHWMRegisterRead(0x5C) | BIT7;
        	IT8728FHWMRegisterWrite(0x5C, flag);

        	// Fill Intel CPU Tjmax value into selected Thermal Diode Zero Degree Adjust register
        	IT8728FHWMRegisterWrite(PECI_ADJUST_REG[PECI_TEMP_ADJUST_FOR_INTEL_CPU - 1], TjMax);

        	// Disable Thermal Diode Zero Degree Adjust Register Write
        	IT8728FHWMRegisterWrite(0x5C, (flag & ~BIT7));
	}
	#endif // PECI_TEMP_ADJUST_FOR_INTEL_CPU
	// PECI Temperature Correction _End <<

	// Smart FAN control _Begin >>
	{
		#if defined(IT8728_SMF1_SUPPORT) && (IT8728_SMF1_SUPPORT == 1)
		IT8728SmartFan1Support(SetupData.IT8728SMF1Control, SetupData.IT8728SMF1Mode
			, SetupData.IT8728SMF1PWMDuty, SetupData.IT8728SMF1SPinPWMDuty, SetupData.IT8728SMF1TempSrc
			, SetupData.IT8728SMF1OffTemp, SetupData.IT8728SMF1StartTemp, SetupData.IT8728SMF1FullTemp
			, SetupData.IT8728SMF1PWMSlope);
		#endif
		#if defined(IT8728_SMF2_SUPPORT) && (IT8728_SMF2_SUPPORT == 1)
		IT8728SmartFan2Support(SetupData.IT8728SMF2Control, SetupData.IT8728SMF2Mode
			, SetupData.IT8728SMF2PWMDuty, SetupData.IT8728SMF2SPinPWMDuty, SetupData.IT8728SMF2TempSrc
			, SetupData.IT8728SMF2OffTemp, SetupData.IT8728SMF2StartTemp, SetupData.IT8728SMF2FullTemp
			, SetupData.IT8728SMF2PWMSlope);
		#endif	
		// >> 2015/08/25 Eric
		#if defined(IT8728_SMF3_SUPPORT) && (IT8728_SMF3_SUPPORT == 1)
		IT8728SmartFan3Support(SetupData.IT8728SMF3Control, SetupData.IT8728SMF3Mode
			, SetupData.IT8728SMF3PWMDuty, SetupData.IT8728SMF3SPinPWMDuty, SetupData.IT8728SMF3TempSrc
			, SetupData.IT8728SMF3OffTemp, SetupData.IT8728SMF3StartTemp, SetupData.IT8728SMF3FullTemp
			, SetupData.IT8728SMF3PWMSlope);
		#endif	
		// << 2015/08/25 Eric
		// >> 2017/03/22 Eric
		#if defined(IT8728_SMF4_SUPPORT) && (IT8728_SMF4_SUPPORT == 1)
		IT8728SmartFan4Support(&SetupData);
		#endif
		#if defined(IT8728_SMF5_SUPPORT) && (IT8728_SMF5_SUPPORT == 1)
		IT8728SmartFan5Support(&SetupData);
		#endif
		// << 2017/03/22 Eric
	}
	// Smart FAN control _End <<

}// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_PeiClearDevResource
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
VOID IT8728F_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_LDN_SEL_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_ACTIVATE_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA,  IT8728F_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_BASE1_HI_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA,  0);
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_BASE1_LO_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_IRQ1_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA,  0);
    return;
}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728FPeiInitEntryPoint
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
EFI_STATUS IT8728FPeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
//RayWu, REMOVE 2014/07/28 >>
//    UINT8 index;
//
//    for(index=0; index<sizeof(IT8728FPeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, IT8728FPeiDecodeTable[index].BaseAdd, IT8728FPeiDecodeTable[index].UID, IT8728FPeiDecodeTable[index].Type);
//RayWu, REMOVE 2014/07/28 <<
    ProgramRtRegisterTable(0, IT8728FPeiInitTable, sizeof(IT8728FPeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));
    // Enter Configuration Mode.
    IoWrite8(IT8728F_CONFIG_INDEX, 0x87);
    IoWrite8(IT8728F_CONFIG_INDEX, 0x01);
    IoWrite8(IT8728F_CONFIG_INDEX, 0x55);
#if (IT8728F_CONFIG_INDEX == 0x2E)
    IoWrite8(IT8728F_CONFIG_INDEX, 0x55);
#else
    IoWrite8(IT8728F_CONFIG_INDEX, 0xAA);
#endif
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
    IT8728F_PeiClearDevResource(IT8728F_LDN_CIR);
    // Exit Configuration Mode
    IoWrite8(IT8728F_CONFIG_INDEX, 0x02);
    IoWrite8(IT8728F_CONFIG_DATA,  0x02);

    IT8728FMiscSetupFunction(PeiServices);

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
