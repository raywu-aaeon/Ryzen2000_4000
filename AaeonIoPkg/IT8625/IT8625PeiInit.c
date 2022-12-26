//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file IT8625PeiInit.c
  Porting for PEI phase.Just for necessary devices porting.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
// >> 2020/05/19 AAEON_OVERRIDE
#include <Setup.h>
#include <AmiCspLib.h>
// << 2020/05/19 AAEON_OVERRIDE
#include <IT8625SmartFansSetup.h>

extern IO_DECODE_DATA IT8625PeiDecodeTable[];
extern UINT8 IT8625PeiDecodeTableCount;
extern SIO_DEVICE_INIT_DATA IT8625PeiInitTable[];
extern UINT8 IT8625PeiInitTableCount;
//----------------------------------------------------------------------
// internal function declare; these functions are only used by this file.
//----------------------------------------------------------------------
// >> 2020/05/19 AAEON_OVERRIDE
#define     PCR1    0xF2    // APC/PME Control Register 1 (PCR 1)
#define     ECSCR   0xF3    // Environment Controller Special Configuration Register
#define     PCR2    0xF4    // APC/PME Control Register 2 (PCR 2)
// << 2020/05/19 AAEON_OVERRIDE
// >> 2020/05/21 AAEON_OVERRIDE
#define     High    1
#define     Low     0

#define     WDT_CTRL_REG    0x71
#define     WDT_CFG_REG     0x72
#define     WDT_VAL_LSB_REG 0x73

#define     GPIO1X_IPU_REG  0xB8
#define     GPIO3X_IPU_REG  0xBA
#define     GPIO4X_IPU_REG  0xBB
#define     GPIO5X_IPU_REG  0xBC
#define     GPIO6X_IPU_REG  0xBD
#define     GPIO9X_IPU_REG  0xD4
#define     GPIOAX_IPU_REG  0xD9

#define     GPIO1X_SE_REG   0xC0
#define     GPIO2X_SE_REG   0xC1
#define     GPIO3X_SE_REG   0xC2
#define     GPIO4X_SE_REG   0xC3
#define     GPIO5X_SE_REG   0xC4
#define     GPIO9X_SE_REG   0xD3
#define     GPIOAX_SE_REG   0xD8

#define     GPIO1X_OE_REG   0xC8
#define     GPIO2X_OE_REG   0xC9
#define     GPIO3X_OE_REG   0xCA
#define     GPIO4X_OE_REG   0xCB
#define     GPIO5X_OE_REG   0xCC
#define     GPIO6X_OE_REG   0xCD
#define     GPIO7X_OE_REG   0xCE
#define     GPIO8X_OE_REG   0xCF
#define     GPIO9X_OE_REG   0xD2
#define     GPIOAX_OE_REG   0xD7

#define     GPIO1X_VAL_OFFSET   0
#define     GPIO2X_VAL_OFFSET   1
#define     GPIO3X_VAL_OFFSET   2
#define     GPIO4X_VAL_OFFSET   3
#define     GPIO5X_VAL_OFFSET   4
#define     GPIO6X_VAL_OFFSET   5
#define     GPIO7X_VAL_OFFSET   6
#define     GPIO8X_VAL_OFFSET   7
#define     GPIO9X_VAL_OFFSET   8
#define     GPIOAX_VAL_OFFSET   9
// << 2020/05/21 AAEON_OVERRIDE
#define     UART_SP_CFG_REG     0xF0
#define     B_IRQ_TYPE          BIT0
#define     B_RTS_INVERT_EN     BIT6
#define     B_RS485_EN          BIT7
#define     GP_LED_BLINK_1_PIN_MAP_REG  0xF8
#define     GP_LED_BLINK_1_CTRL_REG     0xF9
#define     GP_LED_BLINK_2_PIN_MAP_REG  0xFA
#define     GP_LED_BLINK_2_CTRL_REG     0xFB
// >> 2020/05/18 AAEON_OVERRIDE
//-------------------------------------------------------------------------
//
// Procedure: IT8625_PeiClearDevResource
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
VOID IT8625_PeiClearDevResource(
    IN  UINT8    Ldn
)
{
    // Seclect device LDN
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_LDN_SEL_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, Ldn);
    // Deactivate Device
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_ACTIVATE_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA,  IT8625_DEACTIVATE_VALUE);
    // Clear Base Address
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_BASE1_HI_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA,  0);
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_BASE1_LO_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA,  0);
    // Clear Interrupt
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_IRQ1_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA,  0);
    return;
}
// << 2020/05/18 AAEON_OVERRIDE
// >> 2020/05/19 AAEON_OVERRIDE
void IT8625EnterConfigMode()
{
        UINT8 IT8625ConfigModeEnterValue[4] = IT8625_MB_PNP_MODE_KEY;
        UINT8 i;

        // Enter config mode
        for(i = 0 ; i <= 0x03 ; i++) {
                IoWrite8(IT8625_CONFIG_INDEX, IT8625ConfigModeEnterValue[i]);
                IoWrite8(0xEB, 0xFF); // IO delay
        }
}
void IT8625LDNSelect(UINT8 Ldn)
{
        IoWrite8(IT8625_CONFIG_INDEX, IT8625_LDN_SEL_REGISTER);
        IoWrite8(IT8625_CONFIG_DATA, Ldn);
}
void IT8625ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
        IoWrite8(IT8625_CONFIG_INDEX, Index);
        IoWrite8(IT8625_CONFIG_DATA, Data);
}
UINT8 IT8625ConfigRegisterRead(UINT8 Index)
{
        UINT8 Data8;
        IoWrite8(IT8625_CONFIG_INDEX, Index);
        Data8 = IoRead8(IT8625_CONFIG_DATA);
        return Data8;
}
void IT8625ExitConfigMode()
{
        UINT8 IT8625ConfigModeExitRegister = 0x02;

        // Exit config mode
        IoWrite8(IT8625_CONFIG_INDEX, IT8625ConfigModeExitRegister);
        IoWrite8(0xEB, 0xFF); // IO delay
        IoWrite8(IT8625_CONFIG_DATA, BIT1);
}
// << 2020/05/19 AAEON_OVERRIDE
UINT8 PinNumToLocValue(UINT8 PinNumHex)
{
    UINT8 LocValue = 0;

    LocValue = ((PinNumHex / 10) << 3) + (PinNumHex % 10);

    return LocValue;
}
void
IT8625HwmRegRead (
    IN UINT8 BankNo,
    IN UINT8 Register,
    OUT UINT8 *Value
)
{
    UINT8       Temp;

    // Enter Bank NO!
    IoWrite8(IT8625_HWM_INDEX_PORT, 0x06);
    Temp = IoRead8(IT8625_HWM_DATA_PORT);
    Temp &= 0x9F ;// Bit6-5
    IoWrite8(IT8625_HWM_DATA_PORT, (Temp | (BankNo << 5)));

    //Read the data from register
    IoWrite8(IT8625_HWM_INDEX_PORT, Register);
    *Value = IoRead8(IT8625_HWM_DATA_PORT);

    return;
}
void IT8625HwmRegWrite(
    IN UINT8 BankNo,
    IN UINT8 Register,
    IN UINT8 Value
)
{
    UINT8       Temp;
    UINT8       BankSel = 0x06;
    
    IoWrite8(IT8625_HWM_INDEX_PORT, BankSel);
    Temp = IoRead8(IT8625_HWM_DATA_PORT);
    Temp &= 0x9F ;// Bit6-5
    Temp |= (BankNo << 5);
    IoWrite8(IT8625_HWM_DATA_PORT, Temp);

    //Write the value to register
    IoWrite8(IT8625_HWM_INDEX_PORT, Register);
    IoWrite8(IT8625_HWM_DATA_PORT, Value);

    return;
}

//----------------------------------------------------------------------
// global function declare ; these functions are used for other files.
//----------------------------------------------------------------------
//**********************************************************************
// below are functions defined
//**********************************************************************
// >> 2020/05/19 AAEON_OVERRIDE
VOID IT8625MiscSetupFunction(IN CONST EFI_PEI_SERVICES **PeiServices)
{
        EFI_STATUS                              Status;
        SETUP_DATA                              SetupData;
        UINTN                                   VariableSize = sizeof( SETUP_DATA );
        EFI_GUID                                gSetupGuid = SETUP_GUID;
        EFI_PEI_READ_ONLY_VARIABLE2_PPI         *ReadOnlyVariable = NULL;
        
        Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return;
        }

        IT8625EnterConfigMode();

        // Restore AC Power Loss control _Begin >>
        {
                UINT8   Data8;

                IT8625LDNSelect(IT8625_LDN_ENV);              // Environment Controller Configuration Registers (LDN=04h)
                Data8 = IT8625ConfigRegisterRead(PCR1);
                Data8 &= ~(BIT5);
                switch(SetupData.IT8625RestoreACPowerLoss)
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
                IT8625ConfigRegisterWrite(PCR1, Data8);

                Data8 = IT8625ConfigRegisterRead(PCR2);
                Data8 &= ~(BIT6 + BIT5);
                switch(SetupData.IT8625RestoreACPowerLoss)
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
                IT8625ConfigRegisterWrite(PCR2, Data8);
        }
        // Restore AC Power Loss control _End <<

        // SMBUS Slave 0 and 1 Control _Begin >>
        {
                UINT8   Data8;

                IT8625LDNSelect(IT8625_LDN_ENV);              // Environment Controller Configuration Registers (LDN=04h)
                Data8 = IT8625ConfigRegisterRead(ECSCR);
                Data8 &= ~(BIT2 + BIT1);
                Data8 |= (UINT8)((SetupData.IT8625SmbSlave1En << 2) + (SetupData.IT8625SmbSlave0En << 1));
                IT8625ConfigRegisterWrite(ECSCR, Data8);
        }
        // SMBUS Slave 0 and 1 Control _End <<

        // UART RS485 auto flow control Enabled/Disabled _Begin >>
        #if ((IT8625_SERIAL_PORT1_PRESENT == 1) || (IT8625_SERIAL_PORT2_PRESENT == 1))
        {
            UINT8   Data8, i;
            UINT8   IT8625AllUartLdn[2] = { IT8625_LDN_UART1, IT8625_LDN_UART2 };
    
            for(i = 0; i < 2; i++)
            {
                IT8625LDNSelect(IT8625AllUartLdn[i]);       // All UART LDN
                Data8 = IT8625ConfigRegisterRead(UART_SP_CFG_REG);
                Data8 &= ~(B_RS485_EN + B_RTS_INVERT_EN + B_IRQ_TYPE);
                if(SetupData.IT8625UartIrqType[i] == 1)
                    Data8 |= B_IRQ_TYPE;
                if(SetupData.IT8625UartAutoFlowCtrl[i] == 1)
                    Data8 |= B_RS485_EN;
                if(SetupData.IT8625UartRtsInvert[i] == 1)
                    Data8 |= B_RTS_INVERT_EN;
                IT8625ConfigRegisterWrite(UART_SP_CFG_REG, Data8);
            }
        }
        #endif // IT8625_SERIAL_PORT1_PRESENT || IT8625_SERIAL_PORT2_PRESENT
        // UART RS485 auto flow control Enabled/Disabled _End <<

        // Watch Dog & GPIO setup variable _Begin >>
        {
            UINT8   i;
            UINT8   WdtRegValue;
            UINT8   Gpio_Se, Gpio_Oe, Gpio_Val, Gpio_Ipu;
    
            IT8625LDNSelect(IT8625_LDN_GPIO);     //GPIO Device Configuration Registers

            // Watch Dog Configuration
            IT8625ConfigRegisterWrite(WDT_VAL_LSB_REG, 0);  // Clear default Watch Dog Timer Time-out Value 
            WdtRegValue = IT8625ConfigRegisterRead(WDT_CTRL_REG) & ~(BIT4);
            IT8625ConfigRegisterWrite(
                WDT_CTRL_REG,
                WdtRegValue | ( (BOOLEAN)SetupData.IT8625WdtRstconout << 4 )
            );

            WdtRegValue = IT8625ConfigRegisterRead(WDT_CFG_REG) & ~(BIT7 + BIT6 + BIT5 + BIT4);
            IT8625ConfigRegisterWrite(
                WDT_CFG_REG,
                WdtRegValue | ( (BOOLEAN)SetupData.IT8625WdtTimeOutValSel << 7 )
                            | ( (BOOLEAN)SetupData.IT8625WdtKrstEn << 6 )
                            | ( (BOOLEAN)SetupData.IT8625WdtValExSel << 5 )
                            | ( (BOOLEAN)SetupData.IT8625WdtPwrgdEn << 4 )
            );
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO1X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio1x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio1x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio1x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio1x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO1X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO1X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO1X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO1X_OE_REG, Gpio_Oe);
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO2X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio2x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio2x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio2x_Val[i]) << i );
                //Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio2x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO2X_VAL_OFFSET, Gpio_Val);
            //IT8625ConfigRegisterWrite(GPIO2X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO2X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO2X_OE_REG, Gpio_Oe);
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO3X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio3x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio3x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio3x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio3x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO3X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO3X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO3X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO3X_OE_REG, Gpio_Oe);
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO4X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio4x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio4x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio4x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio4x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO4X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO4X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO4X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO4X_OE_REG, Gpio_Oe);
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO5X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio5x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio5x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio5x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio5x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO5X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO5X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO5X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO5X_OE_REG, Gpio_Oe);
    
            Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO6X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio6x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio6x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio6x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO6X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO6X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO6X_OE_REG, Gpio_Oe);
    
            Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO7X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio7x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio7x_Val[i]) << i );
                //Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio7x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO7X_VAL_OFFSET, Gpio_Val);
            //IT8625ConfigRegisterWrite(GPIO7X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO7X_OE_REG, Gpio_Oe);
    
            Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO8X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio8x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio8x_Val[i]) << i );
                //Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio8x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO8X_VAL_OFFSET, Gpio_Val);
            //IT8625ConfigRegisterWrite(GPIO8X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO8X_OE_REG, Gpio_Oe);
    
            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIO9X Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625Gpio9x_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625Gpio9x_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625Gpio9x_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625Gpio9x_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIO9X_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIO9X_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIO9X_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIO9X_OE_REG, Gpio_Oe);

            Gpio_Se = Gpio_Oe = Gpio_Val = Gpio_Ipu = 0;
            // GPIOAX Misc configuration
            for (i = 0; i < 8; i++)
            {
                Gpio_Se |= ( (BOOLEAN)(SetupData.IT8625GpioAx_Se[i]) << i );
                Gpio_Oe |= ( (BOOLEAN)(SetupData.IT8625GpioAx_Oe[i]) << i );
                Gpio_Val |= ( (BOOLEAN)(SetupData.IT8625GpioAx_Val[i]) << i );
                Gpio_Ipu |= ( (BOOLEAN)(SetupData.IT8625GpioAx_Ipu[i]) << i );
            }
            IoWrite8(IT8625_GPIO_BASE_ADDRESS + GPIOAX_VAL_OFFSET, Gpio_Val);
            IT8625ConfigRegisterWrite(GPIOAX_IPU_REG, Gpio_Ipu);
            IT8625ConfigRegisterWrite(GPIOAX_SE_REG, Gpio_Se);
            IT8625ConfigRegisterWrite(GPIOAX_OE_REG, Gpio_Oe);
        }
        // Watch Dog & GPIO setup variable _End <<

        // GP LED Blinking Pin Mapping _Begin >>
        {
            UINT8   RegTemp8;

            // Set GP LED Blinking 1 Location
            if (SetupData.GpLed1Location) {
                RegTemp8 = IT8625ConfigRegisterRead(GP_LED_BLINK_1_PIN_MAP_REG) & (BIT7 + BIT6);
                RegTemp8 |= PinNumToLocValue(SetupData.GpLed1Location);
                IT8625ConfigRegisterWrite(
                    GP_LED_BLINK_1_PIN_MAP_REG,
                    RegTemp8
                );
    
                RegTemp8 = IT8625ConfigRegisterRead(GP_LED_BLINK_1_CTRL_REG) & (BIT5 + BIT4);
                // Set GP LED Blinking 1 Output Low Enable
                RegTemp8 |= SetupData.IT8625GpLed1OutLow;
                // Set GP LED 1 Blink Frequency
                RegTemp8 |= ((SetupData.IT8625GpLed1Freq & 0x07) << 1) | ((SetupData.IT8625GpLed1Freq & 0x18) << 3);

                IT8625ConfigRegisterWrite(
                    GP_LED_BLINK_1_CTRL_REG,
                    RegTemp8
                );
            }

            // Set GP LED Blinking 2 Location
            if (SetupData.GpLed2Location) {
                RegTemp8 = IT8625ConfigRegisterRead(GP_LED_BLINK_2_PIN_MAP_REG) & (BIT7 + BIT6);
                RegTemp8 |= PinNumToLocValue(SetupData.GpLed2Location);
                IT8625ConfigRegisterWrite(
                    GP_LED_BLINK_2_PIN_MAP_REG,
                    RegTemp8
                );
    
                RegTemp8 = IT8625ConfigRegisterRead(GP_LED_BLINK_2_CTRL_REG) & (BIT5 + BIT4);
                // Set GP LED Blinking 2 Output Low Enable
                RegTemp8 |= SetupData.IT8625GpLed2OutLow;
                // Set GP LED 2 Blink Frequency
                RegTemp8 |= ((SetupData.IT8625GpLed2Freq & 0x07) << 1) | ((SetupData.IT8625GpLed2Freq & 0x18) << 3);

                IT8625ConfigRegisterWrite(
                    GP_LED_BLINK_2_CTRL_REG,
                    RegTemp8
                );
            }
        }
        // GP LED Blinking Pin Mapping _End <<

        IT8625ExitConfigMode();

        // PECI Temperature Correction _Begin >>
        #if defined(PECI_TEMP_ADJUST_FOR_INTEL_CPU) && (PECI_TEMP_ADJUST_FOR_INTEL_CPU != 0)
        {
            #define     MSR_TEMPERATURE_TARGET  0x000001A2
            UINT64      Temp;
            UINT8       TjMax;
            UINT8       flag;
            UINT8       PECI_ADJUST_REG[] = { 0x56, 0x57, 0x59, 0x5A, 0x90, 0x91 };
    
            // Read Intel CPU Tjmax value
            Temp = AsmReadMsr64(MSR_TEMPERATURE_TARGET);
            TjMax = (UINT8)(Shr64(Temp, 16));
    
            // Enable Thermal Diode Zero Degree Adjust Register Write
            IT8625HwmRegRead(0, 0x5C, &flag);
            IT8625HwmRegWrite(0, 0x5C, (flag | BIT7));
    
            // Fill Intel CPU Tjmax value into selected Thermal Diode Zero Degree Adjust register
            IT8625HwmRegWrite(0, PECI_ADJUST_REG[PECI_TEMP_ADJUST_FOR_INTEL_CPU - 1], TjMax);
    
            // Disable Thermal Diode Zero Degree Adjust Register Write
            IT8625HwmRegWrite(0, 0x5C, (flag & ~BIT7));
        }
        #endif // PECI_TEMP_ADJUST_FOR_INTEL_CPU
        // PECI Temperature Correction _End <<

        // PEI Init Smart Fan _Begin >>
        /**
            Program smart fan with setup setting.
        **/
        {
            IT8625_SMF_CONTROL          SMFControl;
            UINTN                       Size = sizeof(IT8625_SMF_CONTROL);
            EFI_GUID                    It8625HwmConfigGuid = IT8625_SMF_GUID;
            EFI_STATUS                  Status;
            UINT8                       TempData;
            
            //Get Setup variable
            Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"IT8625_SMF", &It8625HwmConfigGuid, NULL, &Size, &SMFControl );
            if(EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                return;
            }

            //Fan Polarity
            IT8625HwmRegRead(0, 0x14, &TempData);
            TempData &= 0x7F;
            IT8625HwmRegWrite(0, 0x14, TempData | (SMFControl.FanPolarity << 7)); //Bank 0 Index 0x14[7]
            
            //Fan 1 setting
            #if defined(IT8625_SMF1_SUPPORT) && (IT8625_SMF1_SUPPORT == 1)
            switch (SMFControl.Fan1SmartMode) {
            case 0://Software Mode
                //Index 15h[7] = 0
                IT8625HwmRegRead(0, 0x15, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x15, TempData); //Bank 0 Index 0x15
                IT8625HwmRegWrite(0, 0x63, SMFControl.Fan1PwmControl); //Bank 0 Index 0x63 PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 15h[7] = 1
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x15, &TempData);
                TempData &= 0x43; //Clear 0x15[7][5-2]
                IT8625HwmRegWrite(0, 0x15, TempData | BIT7 | (SMFControl.Fan1Tempin << 3) | (SMFControl.Fan1Type << 2)); //Bank 0 Index 0x15[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0x60, SMFControl.Fan1TempOffLimit); //Bank 0 Index 0x60 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0x61, SMFControl.Fan1TempStartLimit); //Bank 0 Index 0x61 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0x62, SMFControl.Fan1TempFullSpeedLimit); //Bank 0 Index 0x62 Temperature Limit of full speed
                if(SMFControl.Fan1Type == 1) {
                    SMFControl.Fan1StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0x63, (UINT8)SMFControl.Fan1StartRpm); //Bank 0 Index 0x63 Minumum(RPM)
                    SMFControl.Fan1RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0x64, (UINT8)SMFControl.Fan1RpmSlope | 0x80); //Bank 0 Index 0x64 Slope(RPM)
                    SMFControl.Fan1TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0x66, SMFControl.Fan1TargetZone); //Bank 0 Index 0x66 Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0x63, (UINT8)SMFControl.Fan1StartPwm); //Bank 0 Index 0x63 Minumum(PWM)
                    IT8625HwmRegWrite(0, 0x64, (UINT8)(SMFControl.Fan1PwmSlope << 3) | 0x80); //Bank 0 Index 0x64 Slope
                }        
                IT8625HwmRegRead(0, 0x65, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0x65, TempData | SMFControl.Fan1TempInterval); //Bank 0 Index 0x65[4-0]
                IT8625HwmRegRead(2, 0x5D, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x5D, TempData | SMFControl.Fan1Smooth); //Bank 2 Index 0x5D[5-0]
                //Curves count(Min: 1, Max: 4)
                SMFControl.Fan1CurveCount --;
                if(SMFControl.Fan1CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x10, SMFControl.Fan1ExtraAStartLimit); //Bank 2 Index 0x10
                //Temperature Input
                IT8625HwmRegRead(2, 0x12, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x12, TempData | (SMFControl.Fan1ExtraATempIn << 5)); //Bank 2 Index 0x12[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan1ExtraASlopeType)
                    SMFControl.Fan1ExtraASlopeType = 0x80;
                SMFControl.Fan1ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x13, SMFControl.Fan1ExtraASlopeType | SMFControl.Fan1ExtraARange); //Bank 2 Index 0x13
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan1Type == 1) {
                    SMFControl.Fan1ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x11, (UINT8)SMFControl.Fan1ExtraASlope | 0x80); //Bank 2 Index 0x11(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x11, (UINT8)SMFControl.Fan1ExtraASlope | 0x80); //Bank 2 Index 0x11(PWM)
                SMFControl.Fan1CurveCount --;
                if(SMFControl.Fan1CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x14, SMFControl.Fan1ExtraBStartLimit); //Bank 2 Index 0x14
                //Temperature Input
                IT8625HwmRegRead(2, 0x16, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x16, TempData | SMFControl.Fan1ExtraBTempIn); //Bank 2 Index 0x16[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan1ExtraBSlopeType &= 0x80;
                SMFControl.Fan1ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x17, SMFControl.Fan1ExtraBSlopeType | SMFControl.Fan1ExtraBRange); //Bank 2 Index 0x17
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x15, SMFControl.Fan1ExtraBSlope | 0x80); //Bank 2 Index 0x15
                SMFControl.Fan1CurveCount --;
                if(SMFControl.Fan1CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x18, SMFControl.Fan1ExtraCStartLimit); //Bank 2 Index 0x18
                //Temperature Input
                IT8625HwmRegRead(2, 0x1A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x1A, TempData | SMFControl.Fan1ExtraCTempIn); //Bank 2 Index 0x1A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan1ExtraBSlopeType &= 0x80;
                SMFControl.Fan1ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x1B, SMFControl.Fan1ExtraCSlopeType | SMFControl.Fan1ExtraCRange); //Bank 2 Index 0x1B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x19, SMFControl.Fan1ExtraCSlope | 0x80); //Bank 2 Index 0x19
                break;
            }
            #endif  // IT8625_SMF1_SUPPORT
        
            //Fan 2 setting
            #if defined(IT8625_SMF2_SUPPORT) && (IT8625_SMF2_SUPPORT == 1)
            switch (SMFControl.Fan2SmartMode) {
            case 0://Software Mode
                //Index 16h[7] = 0
                IT8625HwmRegRead(0, 0x16, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x16, TempData); //Bank 0 Index 0x16[7]
                IT8625HwmRegWrite(0, 0x6B, SMFControl.Fan2PwmControl); //Bank 0 Index 0x6B PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 16h[7] = 1
                //Curves count(Min: 1, Max: 4)
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x16, &TempData);
                TempData &= 0x43; //Clear 0x16[7][5-2]
                IT8625HwmRegWrite(0, 0x16, TempData | BIT7 | (SMFControl.Fan2Tempin << 3) | (SMFControl.Fan2Type << 2)); //Bank 0 Index 0x16[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0x68, SMFControl.Fan2TempOffLimit); //Bank 0 Index 0x68 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0x69, SMFControl.Fan2TempStartLimit); //Bank 0 Index 0x69 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0x6A, SMFControl.Fan2TempFullSpeedLimit); //Bank 0 Index 0x6A Temperature Limit of full speed
                if(SMFControl.Fan2Type == 1) {
                    SMFControl.Fan2StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0x6B, (UINT8)SMFControl.Fan2StartRpm); //Bank 0 Index 0x6B Minumum(RPM)
                    SMFControl.Fan2RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0x6C, (UINT8)SMFControl.Fan2RpmSlope | 0x80); //Bank 0 Index 0x6C Slope(RPM)
                    SMFControl.Fan2TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0x6E, SMFControl.Fan2TargetZone); //Bank 0 Index 0x6E Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0x6B, (UINT8)SMFControl.Fan2StartPwm); //Bank 0 Index 0x6B Minumum(PWM)
                    IT8625HwmRegWrite(0, 0x6C, (UINT8)(SMFControl.Fan2PwmSlope << 3) | 0x80); //Bank 0 Index 0x6C Slope
                }        
                IT8625HwmRegRead(0, 0x6D, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0x6D, TempData | SMFControl.Fan2TempInterval); //Bank 0 Index 0x6D[4-0]
                IT8625HwmRegRead(2, 0x5E, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x5E, TempData | SMFControl.Fan2Smooth); //Bank 2 Index 0x5E[5-0]
                SMFControl.Fan2CurveCount --;
                if(SMFControl.Fan2CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x20, SMFControl.Fan2ExtraAStartLimit); //Bank 2 Index 0x20
                //Temperature Input
                IT8625HwmRegRead(2, 0x22, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x22, TempData | (SMFControl.Fan2ExtraATempIn << 5)); //Bank 2 Index 0x22[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan2ExtraASlopeType)
                    SMFControl.Fan2ExtraASlopeType = 0x80;
                SMFControl.Fan2ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x23, SMFControl.Fan2ExtraASlopeType | SMFControl.Fan2ExtraARange); //Bank 2 Index 0x23
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan2Type == 1) {
                    SMFControl.Fan2ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x21, (UINT8)SMFControl.Fan2ExtraASlope | 0x80); //Bank 2 Index 0x21(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x21, (UINT8)SMFControl.Fan2ExtraASlope | 0x80); //Bank 2 Index 0x21(PWM)
                SMFControl.Fan2CurveCount --;
                if(SMFControl.Fan2CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x24, SMFControl.Fan2ExtraBStartLimit); //Bank 2 Index 0x24
                //Temperature Input
                IT8625HwmRegRead(2, 0x26, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x26, TempData | SMFControl.Fan2ExtraBTempIn); //Bank 2 Index 0x26[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan2ExtraBSlopeType &= 0x80;
                SMFControl.Fan2ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x27, SMFControl.Fan2ExtraBSlopeType | SMFControl.Fan2ExtraBRange); //Bank 2 Index 0x27
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x25, SMFControl.Fan2ExtraBSlope | 0x80); //Bank 2 Index 0x25
                SMFControl.Fan2CurveCount --;
                if(SMFControl.Fan2CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x28, SMFControl.Fan2ExtraCStartLimit); //Bank 2 Index 0x28
                //Temperature Input
                IT8625HwmRegRead(2, 0x2A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x2A, TempData | SMFControl.Fan2ExtraCTempIn); //Bank 2 Index 0x2A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan2ExtraBSlopeType &= 0x80;
                SMFControl.Fan2ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x2B, SMFControl.Fan2ExtraCSlopeType | SMFControl.Fan2ExtraCRange); //Bank 2 Index 0x2B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x29, SMFControl.Fan2ExtraCSlope | 0x80); //Bank 2 Index 0x29
                break;
            }
            #endif  // IT8625_SMF2_SUPPORT
        
            //Fan 3 setting
            #if defined(IT8625_SMF3_SUPPORT) && (IT8625_SMF3_SUPPORT == 1)
            switch (SMFControl.Fan3SmartMode) {
            case 0://Software Mode
                //Index 17h[7] = 0
                IT8625HwmRegRead(0, 0x17, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x17, TempData); //Bank 0 Index 0x17[7]
                IT8625HwmRegWrite(0, 0x73, SMFControl.Fan3PwmControl); //Bank 0 Index 0x73 PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 17h[7] = 1
                //Curves count(Min: 1, Max: 4)
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x17, &TempData);
                TempData &= 0x43; //Clear 0x17[7][5-2]
                IT8625HwmRegWrite(0, 0x17, TempData | BIT7 | (SMFControl.Fan3Tempin << 3) | (SMFControl.Fan3Type << 2)); //Bank 0 Index 0x17[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0x70, SMFControl.Fan3TempOffLimit); //Bank 0 Index 0x70 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0x69, SMFControl.Fan3TempStartLimit); //Bank 0 Index 0x69 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0x72, SMFControl.Fan3TempFullSpeedLimit); //Bank 0 Index 0x72 Temperature Limit of full speed
                if(SMFControl.Fan3Type == 1) {
                    SMFControl.Fan3StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0x73, (UINT8)SMFControl.Fan3StartRpm); //Bank 0 Index 0x73 Minumum(RPM)
                    SMFControl.Fan3RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0x74, (UINT8)SMFControl.Fan3RpmSlope | 0x80); //Bank 0 Index 0x74 Slope(RPM)
                    SMFControl.Fan3TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0x76, SMFControl.Fan3TargetZone); //Bank 0 Index 0x76 Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0x73, (UINT8)SMFControl.Fan3StartPwm); //Bank 0 Index 0x73 Minumum(PWM)
                    IT8625HwmRegWrite(0, 0x74, (UINT8)(SMFControl.Fan3PwmSlope << 3) | 0x80); //Bank 0 Index 0x74 Slope
                }        
                IT8625HwmRegRead(0, 0x75, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0x75, TempData | SMFControl.Fan3TempInterval); //Bank 0 Index 0x75[4-0]
                IT8625HwmRegRead(2, 0x5F, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x5F, TempData | SMFControl.Fan3Smooth); //Bank 2 Index 0x5F[5-0]
                SMFControl.Fan3CurveCount --;
                if(SMFControl.Fan3CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x30, SMFControl.Fan3ExtraAStartLimit); //Bank 2 Index 0x30
                //Temperature Input
                IT8625HwmRegRead(2, 0x32, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x32, TempData | (SMFControl.Fan3ExtraATempIn << 5)); //Bank 2 Index 0x32[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan3ExtraASlopeType)
                    SMFControl.Fan3ExtraASlopeType = 0x80;
                SMFControl.Fan3ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x33, SMFControl.Fan3ExtraASlopeType | SMFControl.Fan3ExtraARange); //Bank 2 Index 0x33
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan3Type == 1) {
                    SMFControl.Fan3ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x31, (UINT8)SMFControl.Fan3ExtraASlope | 0x80); //Bank 2 Index 0x31(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x31, (UINT8)SMFControl.Fan3ExtraASlope | 0x80); //Bank 2 Index 0x31(PWM)
                SMFControl.Fan3CurveCount --;
                if(SMFControl.Fan3CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x34, SMFControl.Fan3ExtraBStartLimit); //Bank 2 Index 0x34
                //Temperature Input
                IT8625HwmRegRead(2, 0x36, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x36, TempData | SMFControl.Fan3ExtraBTempIn); //Bank 2 Index 0x36[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan3ExtraBSlopeType &= 0x80;
                SMFControl.Fan3ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x37, SMFControl.Fan3ExtraBSlopeType | SMFControl.Fan3ExtraBRange); //Bank 2 Index 0x37
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x35, SMFControl.Fan3ExtraBSlope | 0x80); //Bank 2 Index 0x35
                SMFControl.Fan3CurveCount --;
                if(SMFControl.Fan3CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x38, SMFControl.Fan3ExtraCStartLimit); //Bank 2 Index 0x38
                //Temperature Input
                IT8625HwmRegRead(2, 0x3A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x3A, TempData | SMFControl.Fan3ExtraCTempIn); //Bank 2 Index 0x3A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan3ExtraBSlopeType &= 0x80;
                SMFControl.Fan3ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x3B, SMFControl.Fan3ExtraCSlopeType | SMFControl.Fan3ExtraCRange); //Bank 2 Index 0x3B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x39, SMFControl.Fan3ExtraCSlope | 0x80); //Bank 2 Index 0x39
                break;
            }
            #endif  // IT8625_SMF3_SUPPORT
        
            //Fan 4 setting
            #if defined(IT8625_SMF4_SUPPORT) && (IT8625_SMF4_SUPPORT == 1)
            switch (SMFControl.Fan4SmartMode) {
            case 0://Software Mode
                //Index 1Eh[7] = 0
                IT8625HwmRegRead(0, 0x1E, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x1E, TempData); //Bank 0 Index 0x1E
                IT8625HwmRegWrite(0, 0x7B, SMFControl.Fan4PwmControl); //Bank 0 Index 0x7B PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 1Eh[7] = 1
                //Curves count(Min: 1, Max: 4)
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x1E, &TempData);
                TempData &= 0x43; //Clear 0x1E[7][5-2]
                IT8625HwmRegWrite(0, 0x1E, TempData | BIT7 | (SMFControl.Fan4Tempin << 3) | (SMFControl.Fan4Type << 2)); //Bank 0 Index 0x1E[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0x78, SMFControl.Fan4TempOffLimit); //Bank 0 Index 0x78 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0x79, SMFControl.Fan4TempStartLimit); //Bank 0 Index 0x79 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0x7A, SMFControl.Fan4TempFullSpeedLimit); //Bank 0 Index 0x7A Temperature Limit of full speed
                if(SMFControl.Fan4Type == 1) {
                    SMFControl.Fan4StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0x7B, (UINT8)SMFControl.Fan4StartRpm); //Bank 0 Index 0x7B Minumum(RPM)
                    SMFControl.Fan4RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0x7C, (UINT8)SMFControl.Fan4RpmSlope | 0x80); //Bank 0 Index 0x7C Slope(RPM)
                    SMFControl.Fan4TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0x7E, SMFControl.Fan4TargetZone); //Bank 0 Index 0x7E Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0x7B, (UINT8)SMFControl.Fan4StartPwm); //Bank 0 Index 0x7B Minumum(PWM)
                    IT8625HwmRegWrite(0, 0x7C, (UINT8)(SMFControl.Fan4PwmSlope << 3) | 0x80); //Bank 0 Index 0x7C Slope
                }        
                IT8625HwmRegRead(0, 0x7D, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0x7D, TempData | SMFControl.Fan4TempInterval); //Bank 0 Index 0x7D[4-0]
                IT8625HwmRegRead(2, 0x6D, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x6D, TempData | SMFControl.Fan4Smooth); //Bank 2 Index 0x6D[5-0]
                SMFControl.Fan4CurveCount --;
                if(SMFControl.Fan4CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x40, SMFControl.Fan4ExtraAStartLimit); //Bank 2 Index 0x40
                //Temperature Input
                IT8625HwmRegRead(2, 0x42, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x42, TempData | (SMFControl.Fan4ExtraATempIn << 5)); //Bank 2 Index 0x42[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan4ExtraASlopeType)
                    SMFControl.Fan4ExtraASlopeType = 0x80;
                SMFControl.Fan4ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x43, SMFControl.Fan4ExtraASlopeType | SMFControl.Fan4ExtraARange); //Bank 2 Index 0x43
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan4Type == 1) {
                    SMFControl.Fan4ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x41, (UINT8)SMFControl.Fan4ExtraASlope | 0x80); //Bank 2 Index 0x41(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x41, (UINT8)SMFControl.Fan4ExtraASlope | 0x80); //Bank 2 Index 0x41(PWM)
                SMFControl.Fan4CurveCount --;
                if(SMFControl.Fan4CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x44, SMFControl.Fan4ExtraBStartLimit); //Bank 2 Index 0x44
                //Temperature Input
                IT8625HwmRegRead(2, 0x46, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x46, TempData | SMFControl.Fan4ExtraBTempIn); //Bank 2 Index 0x46[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan4ExtraBSlopeType &= 0x80;
                SMFControl.Fan4ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x47, SMFControl.Fan4ExtraBSlopeType | SMFControl.Fan4ExtraBRange); //Bank 2 Index 0x47
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x45, SMFControl.Fan4ExtraBSlope | 0x80); //Bank 2 Index 0x45
                SMFControl.Fan4CurveCount --;
                if(SMFControl.Fan4CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x48, SMFControl.Fan4ExtraCStartLimit); //Bank 2 Index 0x48
                //Temperature Input
                IT8625HwmRegRead(2, 0x4A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x4A, TempData | SMFControl.Fan4ExtraCTempIn); //Bank 2 Index 0x4A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan4ExtraBSlopeType &= 0x80;
                SMFControl.Fan4ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x4B, SMFControl.Fan4ExtraCSlopeType | SMFControl.Fan4ExtraCRange); //Bank 2 Index 0x4B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x49, SMFControl.Fan4ExtraCSlope | 0x80); //Bank 2 Index 0x49
                break;
            }
            #endif  // IT8625_SMF4_SUPPORT
        
            //Fan 5 setting
            #if defined(IT8625_SMF5_SUPPORT) && (IT8625_SMF5_SUPPORT == 1)
            switch (SMFControl.Fan5SmartMode) {
            case 0://Software Mode
                //Index 1Fh[7] = 0
                IT8625HwmRegRead(0, 0x1F, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x1F, TempData); //Bank 0 Index 0x1F
                IT8625HwmRegWrite(0, 0xA3, SMFControl.Fan5PwmControl); //Bank 0 Index 0xA3 PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 1Fh[7] = 1
                //Curves count(Min: 1, Max: 4)
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x1F, &TempData);
                TempData &= 0x43; //Clear 0x1F[7][5-2]
                IT8625HwmRegWrite(0, 0x1F, TempData | BIT7 | (SMFControl.Fan5Tempin << 3) | (SMFControl.Fan5Type << 2)); //Bank 0 Index 0x1F[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0xA0, SMFControl.Fan5TempOffLimit); //Bank 0 Index 0xA0 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0xA1, SMFControl.Fan5TempStartLimit); //Bank 0 Index 0xA1 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0xA2, SMFControl.Fan5TempFullSpeedLimit); //Bank 0 Index 0xA2 Temperature Limit of full speed
                if(SMFControl.Fan5Type == 1) {
                    SMFControl.Fan5StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0xA3, (UINT8)SMFControl.Fan5StartRpm); //Bank 0 Index 0xA3 Minumum(RPM)
                    SMFControl.Fan5RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0xA4, (UINT8)SMFControl.Fan5RpmSlope | 0x80); //Bank 0 Index 0xA4 Slope(RPM)
                    SMFControl.Fan5TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0xA6, SMFControl.Fan5TargetZone); //Bank 0 Index 0xA6 Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0xA3, (UINT8)SMFControl.Fan5StartPwm); //Bank 0 Index 0xA3 Minumum(PWM)
                    IT8625HwmRegWrite(0, 0xA4, (UINT8)(SMFControl.Fan5PwmSlope << 3) | 0x80); //Bank 0 Index 0xA4 Slope
                }        
                IT8625HwmRegRead(0, 0xA5, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0xA5, TempData | SMFControl.Fan5TempInterval); //Bank 0 Index 0xA5[4-0]
                IT8625HwmRegRead(2, 0x6E, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x6E, TempData | SMFControl.Fan5Smooth); //Bank 2 Index 0x6E[5-0]
                SMFControl.Fan5CurveCount --;
                if(SMFControl.Fan5CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x50, SMFControl.Fan5ExtraAStartLimit); //Bank 2 Index 0x50
                //Temperature Input
                IT8625HwmRegRead(2, 0x52, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x52, TempData | (SMFControl.Fan5ExtraATempIn << 5)); //Bank 2 Index 0x52[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan5ExtraASlopeType)
                    SMFControl.Fan5ExtraASlopeType = 0x80;
                SMFControl.Fan5ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x53, SMFControl.Fan5ExtraASlopeType | SMFControl.Fan5ExtraARange); //Bank 2 Index 0x53
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan5Type == 1) {
                    SMFControl.Fan5ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x51, (UINT8)SMFControl.Fan5ExtraASlope | 0x80); //Bank 2 Index 0x51(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x51, (UINT8)SMFControl.Fan5ExtraASlope | 0x80); //Bank 2 Index 0x51(PWM)
                SMFControl.Fan5CurveCount --;
                if(SMFControl.Fan5CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x54, SMFControl.Fan5ExtraBStartLimit); //Bank 2 Index 0x54
                //Temperature Input
                IT8625HwmRegRead(2, 0x56, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x56, TempData | SMFControl.Fan5ExtraBTempIn); //Bank 2 Index 0x56[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan5ExtraBSlopeType &= 0x80;
                SMFControl.Fan5ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x57, SMFControl.Fan5ExtraBSlopeType | SMFControl.Fan5ExtraBRange); //Bank 2 Index 0x57
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x55, SMFControl.Fan5ExtraBSlope | 0x80); //Bank 2 Index 0x55
                SMFControl.Fan5CurveCount --;
                if(SMFControl.Fan5CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x58, SMFControl.Fan5ExtraCStartLimit); //Bank 2 Index 0x58
                //Temperature Input
                IT8625HwmRegRead(2, 0x5A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x5A, TempData | SMFControl.Fan5ExtraCTempIn); //Bank 2 Index 0x5A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan5ExtraBSlopeType &= 0x80;
                SMFControl.Fan5ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x5B, SMFControl.Fan5ExtraCSlopeType | SMFControl.Fan5ExtraCRange); //Bank 2 Index 0x5B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x59, SMFControl.Fan5ExtraCSlope | 0x80); //Bank 2 Index 0x59
                break;
            }
            #endif  // IT8625_SMF5_SUPPORT
        
            //Fan 6 setting
            #if defined(IT8625_SMF6_SUPPORT) && (IT8625_SMF6_SUPPORT == 1)
            switch (SMFControl.Fan6SmartMode) {
            case 0://Software Mode
                //Index 92h[7] = 0
                IT8625HwmRegRead(0, 0x92, &TempData);
                TempData &= 0x7F;
                IT8625HwmRegWrite(0, 0x92, TempData); //Bank 0 Index 0x92
                IT8625HwmRegWrite(0, 0xAB, SMFControl.Fan6PwmControl); //Bank 0 Index 0xAB PWM Control value.
                break;
            case 1://Automatic Mode
                //Index 92h[7] = 1
                //Curves count(Min: 1, Max: 4)
                //Fan type & mode & Temperature input
                IT8625HwmRegRead(0, 0x92, &TempData);
                TempData &= 0x43; //Clear 0x92[7][5-2]
                IT8625HwmRegWrite(0, 0x92, TempData | BIT7 | (SMFControl.Fan6Tempin << 3) | (SMFControl.Fan6Type << 2)); //Bank 0 Index 0x92[7]&[5-3]&[2]
                IT8625HwmRegWrite(0, 0xA8, SMFControl.Fan6TempOffLimit); //Bank 0 Index 0xA8 Temperature Limit of fan off
                IT8625HwmRegWrite(0, 0xA9, SMFControl.Fan6TempStartLimit); //Bank 0 Index 0xA9 Temperature Limit of fan start(PWM)
                IT8625HwmRegWrite(0, 0xAA, SMFControl.Fan6TempFullSpeedLimit); //Bank 0 Index 0xAA Temperature Limit of full speed
                if(SMFControl.Fan6Type == 1) {
                    //Temperature inpute
                    SMFControl.Fan6StartRpm /= 32;
                    IT8625HwmRegWrite(0, 0xAB, (UINT8)SMFControl.Fan6StartRpm); //Bank 0 Index 0xAB Minumum(RPM)
                    SMFControl.Fan6RpmSlope /= 8;
                    IT8625HwmRegWrite(0, 0xAC, (UINT8)SMFControl.Fan6RpmSlope | 0x80); //Bank 0 Index 0xAC Slope(RPM)
                    SMFControl.Fan6TargetZone /= 8;
                    IT8625HwmRegWrite(0, 0xAE, SMFControl.Fan6TargetZone); //Bank 0 Index 0xAE Target Zone(RPM)
                }
                else {
                    IT8625HwmRegWrite(0, 0xAB, (UINT8)SMFControl.Fan6StartPwm); //Bank 0 Index 0xAB Minumum(PWM)
                    IT8625HwmRegWrite(0, 0xAC, (UINT8)(SMFControl.Fan6PwmSlope << 3) | 0x80); //Bank 0 Index 0xAC Slope
                }        
                IT8625HwmRegRead(0, 0xAD, &TempData);
                TempData &= 0xE0;
                IT8625HwmRegWrite(0, 0xAD, TempData | SMFControl.Fan6TempInterval); //Bank 0 Index 0xAD[4-0]
                IT8625HwmRegRead(2, 0x6F, &TempData);
                TempData &= 0xC0;
                IT8625HwmRegWrite(2, 0x6F, TempData | SMFControl.Fan6Smooth); //Bank 2 Index 0x6F[5-0]
                SMFControl.Fan6CurveCount --;
                if(SMFControl.Fan6CurveCount == 0)
                    break;
                //Extra vector A
                //START Limit
                IT8625HwmRegWrite(2, 0x60, SMFControl.Fan6ExtraAStartLimit); //Bank 2 Index 0x60
                //Temperature Input
                IT8625HwmRegRead(2, 0x62, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x62, TempData | (SMFControl.Fan6ExtraATempIn << 5)); //Bank 2 Index 0x62[7-5]
                //Positive/Negative Slope & Range value
                if(SMFControl.Fan6ExtraASlopeType)
                    SMFControl.Fan6ExtraASlopeType = 0x80;
                SMFControl.Fan6ExtraARange &= 0x7F;
                IT8625HwmRegWrite(2, 0x63, SMFControl.Fan6ExtraASlopeType | SMFControl.Fan6ExtraARange); //Bank 2 Index 0x63
                //Slope value & Enable Extra Vector.
                if(SMFControl.Fan6Type == 1) {
                    SMFControl.Fan6ExtraASlope /= 8;
                    IT8625HwmRegWrite(2, 0x61, (UINT8)SMFControl.Fan6ExtraASlope | 0x80); //Bank 2 Index 0x61(RPM)
                }
                else
                    IT8625HwmRegWrite(2, 0x61, (UINT8)SMFControl.Fan6ExtraASlope | 0x80); //Bank 2 Index 0x61(PWM)
                SMFControl.Fan6CurveCount --;
                if(SMFControl.Fan6CurveCount == 0)
                    break;
                //Extra vector B        
                //START Limit
                IT8625HwmRegWrite(2, 0x64, SMFControl.Fan6ExtraBStartLimit); //Bank 2 Index 0x64
                //Temperature Input
                IT8625HwmRegRead(2, 0x66, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x66, TempData | SMFControl.Fan6ExtraBTempIn); //Bank 2 Index 0x66[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan6ExtraBSlopeType &= 0x80;
                SMFControl.Fan6ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x67, SMFControl.Fan6ExtraBSlopeType | SMFControl.Fan6ExtraBRange); //Bank 2 Index 0x67
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x65, SMFControl.Fan6ExtraBSlope | 0x80); //Bank 2 Index 0x65
                SMFControl.Fan6CurveCount --;
                if(SMFControl.Fan6CurveCount == 0)
                    break;
                //Extra vector C        
                //START Limit
                IT8625HwmRegWrite(2, 0x68, SMFControl.Fan6ExtraCStartLimit); //Bank 2 Index 0x68
                //Temperature Input
                IT8625HwmRegRead(2, 0x6A, &TempData);
                TempData &= 0x1F;
                IT8625HwmRegWrite(2, 0x6A, TempData | SMFControl.Fan6ExtraCTempIn); //Bank 2 Index 0x6A[7-5]
                //Positive/Negative Slope & Range value
                SMFControl.Fan6ExtraBSlopeType &= 0x80;
                SMFControl.Fan6ExtraBRange &= 0x7F;
                IT8625HwmRegWrite(2, 0x6B, SMFControl.Fan6ExtraCSlopeType | SMFControl.Fan6ExtraCRange); //Bank 2 Index 0x6B
                //Slope value & Enable Extra Vector.
                IT8625HwmRegWrite(2, 0x69, SMFControl.Fan6ExtraCSlope | 0x80); //Bank 2 Index 0x69
                break;
            }
            #endif  // IT8625_SMF6_SUPPORT
        }
        // PEI Init Smart Fan _End >>

}
// << 2020/05/19 AAEON_OVERRIDE
/**
  This function provide PEI phase SIO initialization

  @param  FileHandle     Handle of the file being invoked.
  @param  PeiServices   Describes the list of possible PEI Services.

  @retval  EFI_SUCESS       The entry point of IT8625PeiInit executes successfully.
  @retval  Others           Some error occurs during the execution of this function. 
**/
EFI_STATUS IT8625PeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
// >> 2020/05/18 AAEON_OVERRIDE
//    UINT8 index;
//
//    for(index=0; index<IT8625PeiDecodeTableCount; index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, IT8625PeiDecodeTable[index].BaseAdd, IT8625PeiDecodeTable[index].UID, IT8625PeiDecodeTable[index].Type);
// << 2020/05/18 AAEON_OVERRIDE

    ProgramRtRegisterTable(0, IT8625PeiInitTable, IT8625PeiInitTableCount);
// >> 2020/05/18 AAEON_OVERRIDE
    // Enter Configuration Mode
    IT8625EnterConfigMode();

    // Disable Non-Used Device in Pei Phase, if its default value is actived
    #if !(IT8625_SERIAL_PORT1_PRESENT)
      IT8625_PeiClearDevResource(IT8625_LDN_UART1);
    #endif // IT8625_SERIAL_PORT1_PRESENT
    #if !(IT8625_SERIAL_PORT2_PRESENT)
      IT8625_PeiClearDevResource(IT8625_LDN_UART2);
    #endif // IT8625_SERIAL_PORT2_PRESENT
    #if !(IT8625_PARALLEL_PORT_PRESENT)
      IT8625_PeiClearDevResource(IT8625_LDN_LPT);
    #endif // IT8625_PARALLEL_PORT_PRESENT
    #if !(IT8625_CIR_PORT_PRESENT)
        IT8625_PeiClearDevResource(IT8625_LDN_CIR);
    #endif // IT8625_CIR_PORT_PRESENT

    // Exit Configuration Mode
    IT8625ExitConfigMode();

    // Init IT8625 Misc Functions
    IT8625MiscSetupFunction(PeiServices);
// << 2020/05/18 AAEON_OVERRIDE

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
