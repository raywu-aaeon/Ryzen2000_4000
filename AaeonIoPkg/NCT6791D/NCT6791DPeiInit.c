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
// Name:  <NCT6791DPeiInit.c>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <NCT6791DPeiIoTable.h>
#include <Setup.h>
#include <AmiCspLib.h>
//-------------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------
VOID RayDebug80(UINT8 Time, UINT8 Code){
	UINTN i;
	
	i = 0x0FFFF | (Time << 16);
	while(i != 0){
		IoWrite8(0x80, Code);
		i--;
	}
}

//----------------------------------------------------------------------------
// Procedure:     AccessHwmWithIO
//
// Description: Write the defined value to HWM space register.
//
// Input:     UINT8   Register        -> Register who content the wanted value
//            UINTN   *Value          -> Register value
//
// Output:     NULL
//
//----------------------------------------------------------------------------
VOID WriteHwmWithIO (
    IN UINT8 Register,
    IN UINT8 Value
)
{
    IoWrite8(NCT6791D_HWM_INDEX_PORT, Register);       //HWM_INDEX
    IoWrite8(NCT6791D_HWM_DATA_PORT,  Value);          //HWM_DATA
}

//----------------------------------------------------------------------------
// Procedure:     ReadHwmWithIO
//
// Description: Read the defined value to HWM space register.
//
// Input:     UINT8   Register        -> Register who content the wanted value
//
// Output:     NULL
//
//----------------------------------------------------------------------------
UINT8 ReadHwmWithIO (
    IN UINT8 Register
)
{
    IoWrite8(NCT6791D_HWM_INDEX_PORT, Register);       //HWM_INDEX
    return IoRead8(NCT6791D_HWM_DATA_PORT);            //HWM_DATA
}

//----------------------------------------------------------------------------
// Procedure:     HwmBankSel
//
// Description: Switch Bank of HWM space register.
//
// Input:     UINT8   Bank Num -> Register who content the wanted value
//
// Output:     NULL
//
//----------------------------------------------------------------------------
VOID HwmBankSel (
    IN UINT8 Bank_Num
)
{
    IoWrite8(NCT6791D_HWM_INDEX_PORT, 0x4E);
    IoWrite8(NCT6791D_HWM_DATA_PORT,\
	(IoRead8(NCT6791D_HWM_DATA_PORT) & 0xF0) + Bank_Num);
}

//*************************************************************************
// belows are functions defined
//*************************************************************************
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: NCT6791D_PeiClearDevResource
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
VOID NCT6791D_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_LDN_SEL_REGISTER);
    IoWrite8(NCT6791D_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_ACTIVATE_REGISTER);
    IoWrite8(NCT6791D_CONFIG_DATA,  NCT6791D_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_BASE1_HI_REGISTER);
    IoWrite8(NCT6791D_CONFIG_DATA,  0);
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_BASE1_LO_REGISTER);
    IoWrite8(NCT6791D_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_IRQ1_REGISTER);
    IoWrite8(NCT6791D_CONFIG_DATA,  0);
    return;
}

VOID SET_NCT6791D_GPIO(
	IN UINT16 BaseAddress,
	IN UINT8 Type,
	IN UINT8 Level,
	IN UINT8 Invert,
	IN UINT8 GpioNum
)
{
	UINT8    Value;
	UINT8    GpioSetNum;
	UINT8    GpioBitNum;
	
	GpioSetNum = GpioNum/10;
	GpioBitNum = GpioNum%10;

	// Set GPIO Group Index
	IoWrite8(BaseAddress, GpioSetNum);

	// Set Level Register
	Value = IoRead8(BaseAddress + 2);
	Value &= ~(1 << GpioBitNum);
	Value |= (Level << GpioBitNum);
	IoWrite8(BaseAddress + 2, Value);

	// Set Inversion Register
	if(Invert != 0xFF) {
		Value = IoRead8(BaseAddress + 3);
		Value &= ~(1 << GpioBitNum);
		Value |= (Invert << GpioBitNum);
		IoWrite8(BaseAddress + 3, Value);
	}

	// Set In/Output Register
	Value = IoRead8(BaseAddress + 1);
	Value &= ~(1 << GpioBitNum);
	Value |= (Type << GpioBitNum);
	IoWrite8(BaseAddress + 1, Value);
}

VOID INIT_NCT6791D_GPIO_CONFIG(SETUP_DATA SetupData)
{
	UINT8		i;

	for (i=0 ; i<8 ; i++) {
		// Init GP0x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP0x_Type[i],
					SetupData.NCT6791D_GP0x_Data[i],
					SetupData.NCT6791D_GP0x_Inv[i],
					i );
		// Init GP1x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP1x_Type[i],
					SetupData.NCT6791D_GP1x_Data[i],
					SetupData.NCT6791D_GP1x_Inv[i],
					i+10 );
		// Init GP2x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP2x_Type[i],
					SetupData.NCT6791D_GP2x_Data[i],
					SetupData.NCT6791D_GP2x_Inv[i],
					i+20 );
		// Init GP4x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP4x_Type[i],
					SetupData.NCT6791D_GP4x_Data[i],
					SetupData.NCT6791D_GP4x_Inv[i],
					i+40 );
		// Init GP5x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP5x_Type[i],
					SetupData.NCT6791D_GP5x_Data[i],
					SetupData.NCT6791D_GP5x_Inv[i],
					i+50 );
		// Init GP6x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP6x_Type[i],
					SetupData.NCT6791D_GP6x_Data[i],
					SetupData.NCT6791D_GP6x_Inv[i],
					i+60 );
		// Init GP8x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP8x_Type[i],
					SetupData.NCT6791D_GP8x_Data[i],
					SetupData.NCT6791D_GP8x_Inv[i],
					i+80 );
	}

	for (i=0 ; i<7 ; i++) {
		// Init GP3x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP3x_Type[i],
					SetupData.NCT6791D_GP3x_Data[i],
					SetupData.NCT6791D_GP3x_Inv[i],
					i+30 );
		// Init GP7x Group
		SET_NCT6791D_GPIO( NCT6791D_GPIO_BASE_ADDRESS,
					SetupData.NCT6791D_GP7x_Type[i],
					SetupData.NCT6791D_GP7x_Data[i],
					SetupData.NCT6791D_GP7x_Inv[i],
					i+70 );
	}
}

#if (NCT6791D_SERIAL_PORT1_PRESENT) || (NCT6791D_SERIAL_PORT2_PRESENT)
VOID SET_NCT6791D_UART_RS485_MODE(SETUP_DATA SetupData)
{
	UINT8	Value;

	// Enter Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);

	#if NCT6791D_SERIAL_PORT1_PRESENT
	  // Select Logical Device 2
	  IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_LDN_SEL_REGISTER);
	  IoWrite8(NCT6791D_CONFIG_DATA, NCT6791D_LDN_UART1);

	  // Set UART A RS485 auto flow control
	  IoWrite8(NCT6791D_CONFIG_INDEX, 0xF2);
	  Value = IoRead8(NCT6791D_CONFIG_DATA) & ~(BIT7 + BIT6);
	  Value |= (SetupData.NCT6791D_UART_RS485_enable[0] << 7) \
	  		+ (SetupData.NCT6791D_UART_RS485_inv_sel[0] << 6);
	  IoWrite8(NCT6791D_CONFIG_DATA, Value);
	#endif // NCT6791D_SERIAL_PORT1_PRESENT

	#if NCT6791D_SERIAL_PORT2_PRESENT
	  // Select Logical Device 3
	  IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_LDN_SEL_REGISTER);
	  IoWrite8(NCT6791D_CONFIG_DATA, NCT6791D_LDN_UART2);

	  // Set UART B RS485 auto flow control
	  IoWrite8(NCT6791D_CONFIG_INDEX, 0xF2);
	  Value = IoRead8(NCT6791D_CONFIG_DATA) & ~(BIT7 + BIT6);
	  Value |= (SetupData.NCT6791D_UART_RS485_enable[1] << 7) \
	  		+ (SetupData.NCT6791D_UART_RS485_inv_sel[1] << 6);
	  IoWrite8(NCT6791D_CONFIG_DATA, Value);
	#endif // NCT6791D_SERIAL_PORT2_PRESENT

	// Exit Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_EXIT_VALUE);
}
#endif // NCT6791D_SERIAL_PORT_PRESENT

#if ((NCT6791D_CPUFAN_CTRL_SUPPORT) || (NCT6791D_SYSFAN_CTRL_SUPPORT) || \
    (NCT6791D_AUXFAN0_CTRL_SUPPORT) || (NCT6791D_AUXFAN1_CTRL_SUPPORT) || (NCT6791D_AUXFAN2_CTRL_SUPPORT))
//-------------------------------------------------------------------------
//
// Procedure: NCT6791D_SMF_INIT
//
// Description:
//  This function Initialize NCT6791D SuperI/O Smart Fan function.
//
//------------------------------------------------------------------------- 
VOID
NCT6791D_SMF_INIT(SETUP_DATA SetupData)
{
        UINT8           rv;

        #if NCT6791D_CPUFAN_CTRL_SUPPORT
		// Switch to HWM Bank 2
		HwmBankSel(2);

		if(SetupData.OnOff_CpuFan_Ctrl) {
			switch(SetupData.CpuFan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.CpuFanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.CpuFanTempSrc | (SetupData.CpuFanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.CpuFanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.CpuTolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.CpuFanStartUp);

				WriteHwmWithIO(0x05, SetupData.CpuFanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.CpuFanStopTime);

				WriteHwmWithIO(0x03, SetupData.CpuFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.CpuFanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.CpuFanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.CpuFanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.CpuFanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.CpuFanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.CpuFanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.CpuFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.CpuFanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
			  	WriteHwmWithIO(0x00, SetupData.CpuFanTempSrc);

				WriteHwmWithIO(0x21, SetupData.CpuFanT[0]);
				WriteHwmWithIO(0x22, SetupData.CpuFanT[1]);
				WriteHwmWithIO(0x23, SetupData.CpuFanT[2]);
				WriteHwmWithIO(0x24, SetupData.CpuFanT[3]);

				WriteHwmWithIO(0x27, SetupData.CpuFanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.CpuFanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.CpuFanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.CpuFanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.CpuFanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.CpuFanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.CpuFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.CpuFanStepDownTime);

				rv = SetupData.CpuFanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.CpuFanCountUp & 0x0F) << 4));

				// Switch to HWM Bank 6
				HwmBankSel(6);
				rv = ReadHwmWithIO(0x00) & ~BIT1;
				WriteHwmWithIO(0x00, rv | (SetupData.En_CPU_RPM << 1));

				// Switch to HWM Bank 2
				HwmBankSel(2);
				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.CpuTolOfTemp & 0x07));
				break;
			}
			// CPUFANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.CpuFan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_CPUFAN_CTRL_SUPPORT

        #if NCT6791D_SYSFAN_CTRL_SUPPORT
		// >> 2015/12/07 Eric +
		// Switch to HWM Bank 0
		HwmBankSel(0);
		
		rv = ReadHwmWithIO(0x04) & ~BIT0;
		WriteHwmWithIO(0x04, rv | (SetupData.SysFanOutputMode & BIT0));
		// << 2015/12/07 Eric +
		// Switch to HWM Bank 1
		HwmBankSel(1);

		if(SetupData.OnOff_SysFan_Ctrl) {
			switch(SetupData.SysFan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.SysFanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.SysFanTempSrc | (SetupData.SysFanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.SysFanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.SysTolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.SysFanStartUp);

				WriteHwmWithIO(0x05, SetupData.SysFanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.SysFanStopTime);

				WriteHwmWithIO(0x03, SetupData.SysFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.SysFanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.SysFanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.SysFanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.SysFanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.SysFanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.SysFanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.SysFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.SysFanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
				WriteHwmWithIO(0x21, SetupData.SysFanT[0]);
				WriteHwmWithIO(0x22, SetupData.SysFanT[1]);
				WriteHwmWithIO(0x23, SetupData.SysFanT[2]);
				WriteHwmWithIO(0x24, SetupData.SysFanT[3]);

				WriteHwmWithIO(0x27, SetupData.SysFanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.SysFanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.SysFanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.SysFanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.SysFanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.SysFanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.SysFanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.SysFanStepDownTime);

				rv = SetupData.SysFanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.SysFanCountUp & 0x0F) << 4));

				// Switch to HWM Bank 6
				HwmBankSel(6);
				rv = ReadHwmWithIO(0x00) & ~BIT0;
				WriteHwmWithIO(0x00, rv | SetupData.En_SYS_RPM);

				// Switch to HWM Bank 1
				HwmBankSel(1);
				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.SysTolOfTemp & 0x07));
				break;
			}
			// SYSFANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.SysFan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_SYSFAN_CTRL_SUPPORT

        #if NCT6791D_AUXFAN0_CTRL_SUPPORT
		// Switch to HWM Bank 3
		HwmBankSel(3);

		if(SetupData.OnOff_Aux0Fan_Ctrl) {
			switch(SetupData.Aux0Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux0FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux0FanTempSrc | (SetupData.Aux0FanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.Aux0FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux0TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux0FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux0FanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.Aux0FanStopTime);

				WriteHwmWithIO(0x03, SetupData.Aux0FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux0FanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.Aux0FanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.Aux0FanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.Aux0FanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.Aux0FanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux0FanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux0FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux0FanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
				WriteHwmWithIO(0x21, SetupData.Aux0FanT[0]);
				WriteHwmWithIO(0x22, SetupData.Aux0FanT[1]);
				WriteHwmWithIO(0x23, SetupData.Aux0FanT[2]);
				WriteHwmWithIO(0x24, SetupData.Aux0FanT[3]);

				WriteHwmWithIO(0x27, SetupData.Aux0FanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.Aux0FanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.Aux0FanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.Aux0FanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.Aux0FanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.Aux0FanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux0FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux0FanStepDownTime);

				rv = SetupData.Aux0FanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.Aux0FanCountUp & 0x0F) << 4));

				// Switch to HWM Bank 6
				HwmBankSel(6);
				rv = ReadHwmWithIO(0x00) & ~BIT2;
				WriteHwmWithIO(0x00, rv | (SetupData.En_AUX0_RPM << 2));

				// Switch to HWM Bank 3
				HwmBankSel(3);
				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux0TolOfTemp & 0x07));
				break;
			}
			// AUX0FANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.Aux0Fan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_AUXFAN0_CTRL_SUPPORT

        #if NCT6791D_AUXFAN1_CTRL_SUPPORT
		// Switch to HWM Bank 8
		HwmBankSel(8);

		if(SetupData.OnOff_Aux1Fan_Ctrl) {
			switch(SetupData.Aux1Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux1FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux1FanTempSrc | (SetupData.Aux1FanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.Aux1FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux1TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux1FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux1FanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.Aux1FanStopTime);

				WriteHwmWithIO(0x03, SetupData.Aux1FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux1FanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.Aux1FanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.Aux1FanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.Aux1FanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.Aux1FanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux1FanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux1FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux1FanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
				WriteHwmWithIO(0x21, SetupData.Aux1FanT[0]);
				WriteHwmWithIO(0x22, SetupData.Aux1FanT[1]);
				WriteHwmWithIO(0x23, SetupData.Aux1FanT[2]);
				WriteHwmWithIO(0x24, SetupData.Aux1FanT[3]);

				WriteHwmWithIO(0x27, SetupData.Aux1FanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.Aux1FanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.Aux1FanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.Aux1FanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.Aux1FanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.Aux1FanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux1FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux1FanStepDownTime);

				rv = SetupData.Aux1FanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.Aux1FanCountUp & 0x0F) << 4));

				// Switch to HWM Bank 6
				HwmBankSel(6);
				rv = ReadHwmWithIO(0x00) & ~BIT3;
				WriteHwmWithIO(0x00, rv | (SetupData.En_AUX1_RPM << 3));

				// Switch to HWM Bank 3
				HwmBankSel(8);
				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux1TolOfTemp & 0x07));
				break;
			}
			// AUX1FANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.Aux1Fan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_AUXFAN1_CTRL_SUPPORT

        #if NCT6791D_AUXFAN2_CTRL_SUPPORT
		// Switch to HWM Bank 9
		HwmBankSel(9);

		if(SetupData.OnOff_Aux2Fan_Ctrl) {
			switch(SetupData.Aux2Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux2FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux2FanTempSrc | (SetupData.Aux2FanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.Aux2FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux2TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux2FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux2FanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.Aux2FanStopTime);

				WriteHwmWithIO(0x03, SetupData.Aux2FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux2FanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.Aux2FanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.Aux2FanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.Aux2FanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.Aux2FanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux2FanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux2FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux2FanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
				WriteHwmWithIO(0x21, SetupData.Aux2FanT[0]);
				WriteHwmWithIO(0x22, SetupData.Aux2FanT[1]);
				WriteHwmWithIO(0x23, SetupData.Aux2FanT[2]);
				WriteHwmWithIO(0x24, SetupData.Aux2FanT[3]);

				WriteHwmWithIO(0x27, SetupData.Aux2FanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.Aux2FanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.Aux2FanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.Aux2FanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.Aux2FanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.Aux2FanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux2FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux2FanStepDownTime);

				rv = SetupData.Aux2FanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.Aux2FanCountUp & 0x0F) << 4));

				// Switch to HWM Bank 6
				HwmBankSel(6);
				rv = ReadHwmWithIO(0x00) & ~BIT4;
				WriteHwmWithIO(0x00, rv | (SetupData.En_AUX2_RPM << 4));

				// Switch to HWM Bank 3
				HwmBankSel(9);
				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux2TolOfTemp & 0x07));
				break;
			}
			// AUX2FANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.Aux2Fan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_AUXFAN2_CTRL_SUPPORT

        #if NCT6791D_AUXFAN3_CTRL_SUPPORT
		// Switch to HWM Bank A
		HwmBankSel(0x0A);

		if(SetupData.OnOff_Aux3Fan_Ctrl) {
			switch(SetupData.Aux3Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux3FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux3FanTempSrc | (SetupData.Aux3FanStopduty << 7));	// 2015/11/03 Eric +
				WriteHwmWithIO(0x01, SetupData.Aux3FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux3TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux3FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux3FanStopValue);
			// 2015/11/03 Eric - 	rv = ReadHwmWithIO(0x00) & 0x7F;
			// 2015/11/03 Eric - 	WriteHwmWithIO(0x00, rv | BIT7);

				WriteHwmWithIO(0x07, SetupData.Aux3FanStopTime);

				WriteHwmWithIO(0x03, SetupData.Aux3FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux3FanStepDownTime);

				WriteHwmWithIO(0x35, SetupData.Aux3FanCriticalTemp);
				break;

			  case 2: // Speed Cruise Mode
				WriteHwmWithIO(0x01, (UINT8)(SetupData.Aux3FanTargetSpeed & 0xFF));

				rv = ReadHwmWithIO(0x0C) & 0x80;
				WriteHwmWithIO(0x0C, rv | (UINT8)((SetupData.Aux3FanTargetSpeed >> 8) & 0x0F)\
					| ((SetupData.Aux3FanSpeedTol & 0x38) << 1));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux3FanSpeedTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux3FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux3FanStepDownTime);
				break;

			  case 4: // Smart Fan IV Mode
				WriteHwmWithIO(0x21, SetupData.Aux3FanT[0]);
				WriteHwmWithIO(0x22, SetupData.Aux3FanT[1]);
				WriteHwmWithIO(0x23, SetupData.Aux3FanT[2]);
				WriteHwmWithIO(0x24, SetupData.Aux3FanT[3]);

				WriteHwmWithIO(0x27, SetupData.Aux3FanPwm[0]);
				WriteHwmWithIO(0x28, SetupData.Aux3FanPwm[1]);
				WriteHwmWithIO(0x29, SetupData.Aux3FanPwm[2]);
				WriteHwmWithIO(0x2A, SetupData.Aux3FanPwm[3]);

				WriteHwmWithIO(0x35, SetupData.Aux3FanCriticalTemp);

				rv = ReadHwmWithIO(0x38) & 0xF8;
				WriteHwmWithIO(0x38, rv | (SetupData.Aux3FanCriticalTempTol & 0x07));

				WriteHwmWithIO(0x03, SetupData.Aux3FanStepUpTime);

				WriteHwmWithIO(0x04, SetupData.Aux3FanStepDownTime);

				rv = SetupData.Aux3FanCountDown & 0x0F;
				WriteHwmWithIO(0x66, rv | ((SetupData.Aux3FanCountUp & 0x0F) << 4));

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (SetupData.Aux3TolOfTemp & 0x07));
				break;
			}
			// AUX3FANOUT Mode Select
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv | (SetupData.Aux3Fan_Ctrl_Mode << 4));

		} else {
			// Set Manual Mode and full speed PWM
			rv = ReadHwmWithIO(0x02) & 0x0F;
			WriteHwmWithIO(0x02, rv);
			WriteHwmWithIO(0x09, 0xFF);
		}
	#endif	// NCT6791D_AUXFAN3_CTRL_SUPPORT

}
#endif // (NCT6791D_FAN_CTRL_SUPPORT)

#if PECI_EN
VOID NCT6791D_PECI_INIT()
{
    #define EFI_MSR_IA32_TEMPERATURE_TARGET     0x1A2
    UINT8   Tjmax_Value;

    Tjmax_Value = (UINT8)(AsmReadMsr64(EFI_MSR_IA32_TEMPERATURE_TARGET) >> 16);
    // Switch to HWM Bank 7
    IoWrite8(NCT6791D_HWM_INDEX_PORT, 0x4E);
    IoWrite8(NCT6791D_HWM_DATA_PORT,\
        (IoRead8(NCT6791D_HWM_DATA_PORT) & 0xF0) + 7);

    // Fill CPU Tjmax to SIO PECI Command Tbase0 Register
    IoWrite8(NCT6791D_HWM_INDEX_PORT, 0x09);
    IoWrite8(NCT6791D_HWM_DATA_PORT, Tjmax_Value);
}
#endif // PECI_EN

VOID NCT6791DDeepS5Config(SETUP_DATA SetupData)
{
	UINT8	Value;

	// Enter Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);

	// Select Logical Device 16
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_LDN_SEL_REGISTER);
	IoWrite8(NCT6791D_CONFIG_DATA, NCT6791D_LDN_DSLP);

	// Set Deep S5
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_ACTIVATE_REGISTER);
	Value = IoRead8(NCT6791D_CONFIG_DATA) & 0xFE;
	Value |= SetupData.NCT6791DDeepS5 & 1;
	IoWrite8(NCT6791D_CONFIG_DATA, Value);

	// Exit Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_EXIT_VALUE);
}

VOID NCT6791DAcPWRLossConfig(SETUP_DATA SetupData)
{
	UINT8	Value;

	// Enter Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);	

	// Select Logical Device A
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_LDN_SEL_REGISTER);
	IoWrite8(NCT6791D_CONFIG_DATA, NCT6791D_LDN_ACPI);

	// Clear the previous settings
	IoWrite8(NCT6791D_CONFIG_INDEX, 0xE3);
	Value = IoRead8(NCT6791D_CONFIG_DATA) & ~BIT5;
	IoWrite8(NCT6791D_CONFIG_DATA, Value);

	IoWrite8(NCT6791D_CONFIG_INDEX, 0xE4);
	Value = IoRead8(NCT6791D_CONFIG_DATA) & ~(BIT6 + BIT5);
	IoWrite8(NCT6791D_CONFIG_DATA, Value);

	IoWrite8(NCT6791D_CONFIG_INDEX, 0xE6);
	Value = IoRead8(NCT6791D_CONFIG_DATA) | BIT4;
	IoWrite8(NCT6791D_CONFIG_DATA, Value);

	// Set NCT6791D Restore On AC Power Loss
	if (SetupData.NCT6791D_AC_PWR_LOSS < 4) {
		IoWrite8(NCT6791D_CONFIG_INDEX, 0xE4);
		Value = IoRead8(NCT6791D_CONFIG_DATA) | SetupData.NCT6791D_AC_PWR_LOSS << 5;
		IoWrite8(NCT6791D_CONFIG_DATA, Value);
	} else {
		IoWrite8(NCT6791D_CONFIG_INDEX, 0xE3);
		Value = IoRead8(NCT6791D_CONFIG_DATA) | BIT5;
		IoWrite8(NCT6791D_CONFIG_DATA, Value);
	}

	// Exit Config Mode
	IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_EXIT_VALUE);
}

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
EFI_STATUS NCT6791DPeiInitEntryPoint(
        IN       EFI_PEI_FILE_HANDLE  FileHandle,
        IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    // Pei ReadOnlyVariable2 PPI locate
    EFI_STATUS				Status;
    SETUP_DATA				SetupData;
    UINTN           			VariableSize = sizeof( SETUP_DATA );
    EFI_GUID				gSetupGuid = SETUP_GUID;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
    
    Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );
//RayWu, REMOVE 2015/03/04 >>
//    UINT8 index;
//
//    for(index=0; index<sizeof(NCT6791DPeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, NCT6791DPeiDecodeTable[index].BaseAdd, NCT6791DPeiDecodeTable[index].UID, NCT6791DPeiDecodeTable[index].Type);
//RayWu, REMOVE 2015/03/04 <<
    ProgramRtRegisterTable(0, NCT6791DPeiInitTable, sizeof(NCT6791DPeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

    // Enter Configuration Mode
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_ENTER_VALUE);
    // Disable Non-Used Device in Pei Phase,if its default value is actived.
    #if !(NCT6791D_PARALLEL_PORT_PRESENT)
      NCT6791D_PeiClearDevResource(NCT6791D_LDN_LPT);
    #endif // NCT6791D_PARALLEL_PORT_PRESENT
    #if !(NCT6791D_SERIAL_PORT1_PRESENT)
      NCT6791D_PeiClearDevResource(NCT6791D_LDN_UART1);
    #endif // NCT6791D_SERIAL_PORT1_PRESENT
    #if !(NCT6791D_SERIAL_PORT2_PRESENT)
      NCT6791D_PeiClearDevResource(NCT6791D_LDN_UART2);
    #endif // NCT6791D_SERIAL_PORT2_PRESENT
    NCT6791D_PeiClearDevResource(NCT6791D_LDN_CIR);
    // Exit Configuration Mode
    IoWrite8(NCT6791D_CONFIG_INDEX, NCT6791D_CONFIG_MODE_EXIT_VALUE);

    // Init NCT6791D GPIO Configuration
    INIT_NCT6791D_GPIO_CONFIG(SetupData);

    // Init NCT6791D UART1/2 RS485 Configuration
    #if (NCT6791D_SERIAL_PORT1_PRESENT) || (NCT6791D_SERIAL_PORT2_PRESENT)
      SET_NCT6791D_UART_RS485_MODE(SetupData);
    #endif // NCT6791D_SERIAL_PORT_PRESENT

    // Init Smart Fan Settings
    #if ((NCT6791D_CPUFAN_CTRL_SUPPORT) || (NCT6791D_SYSFAN_CTRL_SUPPORT) || \
        (NCT6791D_AUXFAN0_CTRL_SUPPORT) || (NCT6791D_AUXFAN1_CTRL_SUPPORT) || (NCT6791D_AUXFAN2_CTRL_SUPPORT))
      NCT6791D_SMF_INIT(SetupData);
    #endif // NCT6791D_FAN_CTRL_SUPPORT

    // Init NCT6791D PECI Feature
    #if PECI_EN
      NCT6791D_PECI_INIT();
    #endif // PECI_EN

    // Init NCT6791D Deep S5 Feature
    NCT6791DDeepS5Config(SetupData);

    // Init NCT6791D Restore On AC Power Loss Feature
    NCT6791DAcPWRLossConfig(SetupData);
    
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



