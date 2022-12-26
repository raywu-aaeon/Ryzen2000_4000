//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file NCT5538DPeiInit.c
  Porting for PEI phase.Just for necessary devices porting.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <token.h>
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include <Setup.h>
#include <Ppi/ReadOnlyVariable2.h>
  
extern IO_DECODE_DATA NCT5538DPeiDecodeTable[];
extern UINT8 NCT5538DPeiDecodeTableCount;
extern SIO_DEVICE_INIT_DATA NCT5538DPeiInitTable[];
extern UINT8 NCT5538DPeiInitTableCount;
//----------------------------------------------------------------------
// internal function declare; these functions are only used by this file.
//----------------------------------------------------------------------
VOID NCT5538DEnterConfigMode()
{
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);
}
VOID NCT5538DExitConfigMode()
{
	// Exit config mode
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_EXIT_VALUE);
}
VOID NCT5538DLDNSelect(UINT8 Ldn)
{
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_LDN_SEL_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA, Ldn);
}
VOID NCT5538DConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(NCT5538D_CONFIG_INDEX, Index);
	IoWrite8(NCT5538D_CONFIG_DATA, Data);
}
UINT8 NCT5538DConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(NCT5538D_CONFIG_INDEX, Index);
	Data8 = IoRead8(NCT5538D_CONFIG_DATA);
	return Data8;
}
// >> 2016/07/20 AAEON_OVERRIDE
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
    IoWrite8(NCT5538D_HWM_INDEX_PORT, Register);       //HWM_INDEX
    IoWrite8(NCT5538D_HWM_DATA_PORT,  Value);          //HWM_DATA
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
    IoWrite8(NCT5538D_HWM_INDEX_PORT, Register);       //HWM_INDEX
    return IoRead8(NCT5538D_HWM_DATA_PORT);            //HWM_DATA
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
    IoWrite8(NCT5538D_HWM_INDEX_PORT, 0x4E);
    IoWrite8(NCT5538D_HWM_DATA_PORT,\
	(IoRead8(NCT5538D_HWM_DATA_PORT) & 0xF0) + Bank_Num);
}
// << 2016/07/20 AAEON_OVERRIDE

VOID SET_NCT5538D_GPIO(
	IN UINT8 Type,
	IN UINT8 Level,
	IN UINT8 Invert,
	IN UINT8 GpioNum
)
{
	UINT8    Value;
	UINT8    GpioSetNum;
	UINT8    GpioBitNum;
	UINT16	BaseAddress;

	BaseAddress = NCT5538D_GPIO_BASE_ADDRESS;
	
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
//----------------------------------------------------------------------
// global function declare ; these functions are used for other files.
//----------------------------------------------------------------------
VOID NCT5538D_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
	// Seclect device LDN
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_LDN_SEL_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA, Ldn);
	// Deactivate Device
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_ACTIVATE_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA,  NCT5538D_DEACTIVATE_VALUE);
	// Clear Base Address
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_BASE1_HI_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA,  0);
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_BASE1_LO_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA,  0);
	// Clear Interrupt
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_IRQ1_REGISTER);
	IoWrite8(NCT5538D_CONFIG_DATA,  0);
	return;
}

VOID INIT_NCT5538D_GPIO_CONFIG(SETUP_DATA SetupData)
{
	UINT8 i;

	// GPIO0
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP00_Type, SetupData.NCT5538D_GP00_Data, SetupData.NCT5538D_GP00_Inv, 0);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP01_Type, SetupData.NCT5538D_GP01_Data, SetupData.NCT5538D_GP01_Inv, 1);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP04_Type, SetupData.NCT5538D_GP04_Data, SetupData.NCT5538D_GP04_Inv, 4);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP05_Type, SetupData.NCT5538D_GP05_Data, SetupData.NCT5538D_GP05_Inv, 5);

	// GPIO2
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP20_Type, SetupData.NCT5538D_GP20_Data, SetupData.NCT5538D_GP20_Inv, 0);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP21_Type, SetupData.NCT5538D_GP21_Data, SetupData.NCT5538D_GP21_Inv, 1);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP22_Type, SetupData.NCT5538D_GP22_Data, SetupData.NCT5538D_GP22_Inv, 2);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP23_Type, SetupData.NCT5538D_GP23_Data, SetupData.NCT5538D_GP23_Inv, 3);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP27_Type, SetupData.NCT5538D_GP27_Data, SetupData.NCT5538D_GP27_Inv, 7);

	// GPIO3
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP30_Type, SetupData.NCT5538D_GP30_Data, SetupData.NCT5538D_GP30_Inv, 0);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP33_Type, SetupData.NCT5538D_GP33_Data, SetupData.NCT5538D_GP33_Inv, 3);

	// GPIO4
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP47_Type, SetupData.NCT5538D_GP47_Data, SetupData.NCT5538D_GP47_Inv, 7);

	// GPIO5
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP54_Type, SetupData.NCT5538D_GP54_Data, SetupData.NCT5538D_GP54_Inv, 4);

	// GPIO7
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP75_Type, SetupData.NCT5538D_GP75_Data, SetupData.NCT5538D_GP75_Inv, 5);
	SET_NCT5538D_GPIO(SetupData.NCT5538D_GP76_Type, SetupData.NCT5538D_GP76_Data, SetupData.NCT5538D_GP76_Inv, 6);

	// GPIO8
	for(i = 0 ; i < 8 ; i++)
	{
		SET_NCT5538D_GPIO(SetupData.NCT5538D_GP8x_Type[i], SetupData.NCT5538D_GP8x_Data[i], SetupData.NCT5538D_GP8x_Inv[i], i);
	}
}

#if (NCT5538D_SERIAL_PORT1_PRESENT == 1)
VOID SET_NCT5538D_UART_RS485_MODE(SETUP_DATA SetupData)
{
	UINT8	Data8;

	NCT5538DLDNSelect(NCT5538D_LDN_UART1);

	// Set UART A RS485 auto flow control
	Data8 = NCT5538DConfigRegisterRead(0xF2) & ~(BIT7 + BIT6);
	Data8 |= (SetupData.NCT5538D_UARTA_RS485_enable << 7) \
			+ (SetupData.NCT5538D_UARTA_RS485_inv_sel << 6);
	NCT5538DConfigRegisterWrite(0xF2, Data8);
}
#endif // NCT5538D_SERIAL_PORT1_PRESENT

// >> 2016/07/19 AAEON_OVERRIDE
#if ((NCT5538D_CPUFAN_CTRL_SUPPORT) || (NCT5538D_SYSFAN_CTRL_SUPPORT) || \
    (NCT5538D_AUXFAN0_CTRL_SUPPORT) || (NCT5538D_AUXFAN1_CTRL_SUPPORT))
//-------------------------------------------------------------------------
//
// Procedure: NCT5538D_SMF_INIT
//
// Description:
//  This function Initialize NCT5538D SuperI/O Smart Fan function.
//
//------------------------------------------------------------------------- 
VOID
NCT5538D_SMF_INIT(SETUP_DATA SetupData)
{
        UINT8           rv;

        #if NCT5538D_CPUFAN_CTRL_SUPPORT
		// Switch to HWM Bank 2
		HwmBankSel(2);

		if(SetupData.OnOff_CpuFan_Ctrl) {
			switch(SetupData.CpuFan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.CpuFanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.CpuFanTempSrc | (SetupData.CpuFanStopduty << 7));
				WriteHwmWithIO(0x01, SetupData.CpuFanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.CpuTolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.CpuFanStartUp);

				WriteHwmWithIO(0x05, SetupData.CpuFanStopValue);

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
	#endif	// NCT5538D_CPUFAN_CTRL_SUPPORT

        #if NCT5538D_SYSFAN_CTRL_SUPPORT
		// Switch to HWM Bank 0
		HwmBankSel(0);
		
		rv = ReadHwmWithIO(0x04) & ~BIT0;
		WriteHwmWithIO(0x04, rv | (SetupData.SysFanOutputMode & BIT0));
		// Switch to HWM Bank 1
		HwmBankSel(1);

		if(SetupData.OnOff_SysFan_Ctrl) {
			switch(SetupData.SysFan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.SysFanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.SysFanTempSrc | (SetupData.SysFanStopduty << 7));
				WriteHwmWithIO(0x01, SetupData.SysFanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.SysTolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.SysFanStartUp);

				WriteHwmWithIO(0x05, SetupData.SysFanStopValue);

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
	#endif	// NCT5538D_SYSFAN_CTRL_SUPPORT

        #if NCT5538D_AUXFAN0_CTRL_SUPPORT
		// Switch to HWM Bank 3
		HwmBankSel(3);

		if(SetupData.OnOff_Aux0Fan_Ctrl) {
			switch(SetupData.Aux0Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux0FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux0FanTempSrc | (SetupData.Aux0FanStopduty << 7));
				WriteHwmWithIO(0x01, SetupData.Aux0FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux0TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux0FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux0FanStopValue);

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
	#endif	// NCT5538D_AUXFAN0_CTRL_SUPPORT

        #if NCT5538D_AUXFAN1_CTRL_SUPPORT
		// Switch to HWM Bank 8
		HwmBankSel(8);

		if(SetupData.OnOff_Aux1Fan_Ctrl) {
			switch(SetupData.Aux1Fan_Ctrl_Mode) {
			  default:
			  case 0: // Manual Mode
				WriteHwmWithIO(0x09, SetupData.Aux1FanOutValue);
				break;

			  case 1: // Thermal Cruise Mode
			  	WriteHwmWithIO(0x00, SetupData.Aux1FanTempSrc | (SetupData.Aux1FanStopduty << 7));
				WriteHwmWithIO(0x01, SetupData.Aux1FanTargetTemp);

				rv = ReadHwmWithIO(0x02) & 0xF8;
				WriteHwmWithIO(0x02, rv | (UINT8)(SetupData.Aux1TolOfTemp & 0x07));

				WriteHwmWithIO(0x06, SetupData.Aux1FanStartUp);

				WriteHwmWithIO(0x05, SetupData.Aux1FanStopValue);

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
	#endif	// NCT5538D_AUXFAN1_CTRL_SUPPORT

}
#endif // (NCT5538D_FAN_CTRL_SUPPORT)

#if PECI_EN
VOID NCT5538D_PECI_INIT()
{
        #define EFI_MSR_IA32_TEMPERATURE_TARGET     0x1A2
        UINT8   Tjmax_Value;
        
        Tjmax_Value = (UINT8)(AsmReadMsr64(EFI_MSR_IA32_TEMPERATURE_TARGET) >> 16);
        // Switch to HWM Bank 7
        IoWrite8(NCT5538D_HWM_INDEX_PORT, 0x4E);
        IoWrite8(NCT5538D_HWM_DATA_PORT,\
            (IoRead8(NCT5538D_HWM_DATA_PORT) & 0xF0) + 7);
        
        // Fill CPU Tjmax to SIO PECI Command Tbase0 Register
        IoWrite8(NCT5538D_HWM_INDEX_PORT, 0x09);
        IoWrite8(NCT5538D_HWM_DATA_PORT, Tjmax_Value);
}
#endif // PECI_EN
// << 2016/07/19 AAEON_OVERRIDE

VOID NCT5538DAcPWRLossConfig(SETUP_DATA SetupData)
{
	UINT8	Data8, Index8;

	// Select Logical Device A
	NCT5538DLDNSelect(NCT5538D_LDN_PME);

	// Clear the previous settings
	Index8 = 0xE3;
	Data8 = NCT5538DConfigRegisterRead(Index8) & ~BIT5;
	NCT5538DConfigRegisterWrite(Index8, Data8);

	Index8 = 0xE4;
	Data8 = NCT5538DConfigRegisterRead(Index8) & ~(BIT6 + BIT5);
	NCT5538DConfigRegisterWrite(Index8, Data8);

	Index8 = 0xE6;
	Data8 = NCT5538DConfigRegisterRead(Index8) | BIT4;
	NCT5538DConfigRegisterWrite(Index8, Data8);

	// Set NCT5538D Restore On AC Power Loss
	if (SetupData.NCT5538D_AC_PWR_LOSS < 4) {
		Index8 = 0xE4;
		IoWrite8(NCT5538D_CONFIG_INDEX, 0xE4);
		Data8 = NCT5538DConfigRegisterRead(Index8) | SetupData.NCT5538D_AC_PWR_LOSS << 5;
		NCT5538DConfigRegisterWrite(Index8, Data8);
	} else {
		Index8 = 0xE3;
		Data8 = NCT5538DConfigRegisterRead(Index8) | BIT5;
		NCT5538DConfigRegisterWrite(Index8, Data8);
	}
}

VOID NCT5538DMiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
	EFI_STATUS	Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
       	
	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

	// Init NCT5538D GPIO Configuration
	INIT_NCT5538D_GPIO_CONFIG(SetupData);


	NCT5538DEnterConfigMode();

	// Init NCT5538D UARTA RS485 Configuration
	#if (NCT5538D_SERIAL_PORT1_PRESENT == 1)
		SET_NCT5538D_UART_RS485_MODE(SetupData);
	#endif // NCT5538D_SERIAL_PORT_PRESENT

	// Init NCT5538D Restore On AC Power Loss Feature
	NCT5538DAcPWRLossConfig(SetupData);

	NCT5538DExitConfigMode();
}
//**********************************************************************
// below are functions defined
//**********************************************************************
/**
  This function provide PEI phase SIO initialization

  @param  FileHandle     Handle of the file being invoked.
  @param  PeiServices   Describes the list of possible PEI Services.

  @retval  EFI_SUCESS       The entry point of NCT5538DPeiInit executes successfully.
  @retval  Others           Some error occurs during the execution of this function. 
**/
EFI_STATUS NCT5538DPeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
	// >> 2016/07/20 AAEON_OVERRIDE
	// Pei ReadOnlyVariable2 PPI locate
	EFI_STATUS				Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
	
	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );
	// << 2016/07/20 AAEON_OVERRIDE
//    UINT8 index;
//
//    for(index=0; index<NCT5538DPeiDecodeTableCount; index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, NCT5538DPeiDecodeTable[index].BaseAdd, NCT5538DPeiDecodeTable[index].UID, NCT5538DPeiDecodeTable[index].Type);

	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);

	#if !(NCT5538D_SERIAL_PORT1_PRESENT)
		NCT5538D_PeiClearDevResource(NCT5538D_LDN_UART1);
	#endif
	#if !(NCT5538D_KEYBOARD_PRESENT && NCT5538D_MOUSE_PRESENT)
		NCT5538D_PeiClearDevResource(NCT5538D_LDN_PS2M);
	#endif

	IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_EXIT_VALUE);


	ProgramRtRegisterTable(0, NCT5538DPeiInitTable, NCT5538DPeiInitTableCount);

	// >> 2016/07/19 AAEON_OVERRIDE
        // Init PECI function
        #if PECI_EN
      	  NCT5538D_PECI_INIT();
        #endif // PECI_EN

	// Init Smart Fan Settings
	#if ((NCT5538D_CPUFAN_CTRL_SUPPORT) || (NCT5538D_SYSFAN_CTRL_SUPPORT) || \
	    (NCT5538D_AUXFAN0_CTRL_SUPPORT) || (NCT5538D_AUXFAN1_CTRL_SUPPORT))
	  NCT5538D_SMF_INIT(SetupData);
	#endif // NCT5538D_FAN_CTRL_SUPPORT
	// << 2016/07/19 AAEON_OVERRIDE

	NCT5538DMiscSetupFunction(PeiServices);

	return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


