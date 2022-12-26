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
// Name:  <IT8728FPeiIoTable.h>
//
// Description:
//  SIO init table in PEI phase. Any customers have to review below tables
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA IT8728FPeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8728F_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (IT8728F_SERIAL_PORT1_PRESENT)
    {IT8728F_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif //#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (IT8728F_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
#if (IT8728F_FLOPPY_PORT_PRESENT)
    {0x3F0, 0, dsFDC},                                  // FDC decode
#endif
#endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    //Below decode is for SIO generic IO decode
#if defined(IT8728F_TOTAL_BASE_ADDRESS) && (IT8728F_TOTAL_BASE_ADDRESS != 0)
    {IT8728F_TOTAL_BASE_ADDRESS, IT8728F_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    // Add more OEM IO decode below.
#if (IT8728F_CIR_PORT_PRESENT)
    {0x3E0, 0x10, 0xFF}, // For CIR
#endif
};

SIO_DEVICE_INIT_DATA IT8728FPeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {IT8728F_CONFIG_INDEX, 0x00, 0x87},
    {IT8728F_CONFIG_INDEX, 0x00, 0x01},
    {IT8728F_CONFIG_INDEX, 0x00, 0x55},
#if (IT8728F_CONFIG_INDEX == 0x2E)
    {IT8728F_CONFIG_INDEX, 0x00, 0x55},
#else
    {IT8728F_CONFIG_INDEX, 0x00, 0xAA},
#endif
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    //--------------------------------------------------------------------------
    // >>ITE AP Workaround Start:Early I/O initialization before POST
    //--------------------------------------------------------------------------
    //-----------IO Config Registers---------------------------------------------------
    //>>AP V1.0,IT8728F_IT8772E_BIOSAp10022v1 0.pdf
    //CR23[7,6,5]=000
    {IT8728F_CONFIG_INDEX, 0x00, 0x23},
    {IT8728F_CONFIG_DATA,  0x1F, 0x00},
    //Index 24 don't write any value.(If SPI function Enable)
    //Select LDN07h
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_GPIO},
    //CR28[6]=0
    {IT8728F_CONFIG_INDEX, 0x00, 0x28},
    {IT8728F_CONFIG_DATA,  0xBF, 0x00},
    {IT8728F_CONFIG_INDEX, 0x00, 0x2B},
    {IT8728F_CONFIG_DATA,  0xF8, 0x00},// PANSW# Mask timer Register (Index=2Bh, Default=00h)
    {IT8728F_CONFIG_INDEX, 0x00, 0x2C},
    {IT8728F_CONFIG_DATA,  0x62, ( (~VIN0_7_SUPPORT >> 3) & BIT0 )},// Extended 2 Multi-Function Pin Selection Register (Index=2Ch, Default=03h)
    //>>AP V1.5, Index 2B/ bit[7..3] is Reserved, don't write any value
    //>>AP V1.3,IT8728F_23_7x_BIOSAp10022v1 3.pdf---Modify:bit3 use default value
    //CR2B[7-3]=00-> CR2B[7-4]=00,bit3 use default
    //{IT8728F_CONFIG_INDEX, 0x00, 0x2B},
    //{IT8728F_CONFIG_DATA,  0x07, 0x00},
    //CR72[4]=0,disable wdt
    {IT8728F_CONFIG_INDEX, 0x00, 0x72},
    {IT8728F_CONFIG_DATA,  0xEF, 0x00},
#if (IT8728F_JP4==1)
    //When disable AMD Power Sequence function(JP4=1),
    //CR2C[6]=1
    {IT8728F_CONFIG_INDEX, 0x00, 0x2C},
    {IT8728F_CONFIG_DATA,  0xBF, 0x40},
#endif
    //Select LDN EC 04h
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_ENV},
    //CRF0=0x00
    {IT8728F_CONFIG_INDEX, 0x00, 0xF0},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    //clear status, Bit6 don't clear
    {IT8728F_CONFIG_INDEX, 0x00, 0xF1},
    {IT8728F_CONFIG_DATA,  0x00, 0xBF},
    //CRF2=0x00
    {IT8728F_CONFIG_INDEX, 0x00, 0xF2},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    //CRF3=0x00
    {IT8728F_CONFIG_INDEX, 0x00, 0xF3},
// >> 2015/08/25 Eric
//    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    {IT8728F_CONFIG_DATA,  0x00, 0x00 | (SMB_SLAVE_0_EN << 1) | (SMB_SLAVE_1_EN << 2)},
// << 2015/08/25 Eric
    //CRF4=0x00
    {IT8728F_CONFIG_INDEX, 0x00, 0xF4},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    //CRF5[7:6]=00
    {IT8728F_CONFIG_INDEX, 0x00, 0xF5},
    {IT8728F_CONFIG_DATA,  0x3F, 0x00},
    //>>AP V1.3,IT8728F_23_7x_BIOSAp10022v1 3.pdf---Modify
    //CRFA[3:2]=00->CRFA=0x00
    {IT8728F_CONFIG_INDEX, 0x00, 0xFA},
    //-{IT8728F_CONFIG_DATA,  0xF3, 0x00},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    //CRFA[3:2]=00,write 1 to clear status
    {IT8728F_CONFIG_INDEX, 0x00, 0xFB},
    {IT8728F_CONFIG_DATA,  0xF3, 0x0C},
    //Select LDN 03h
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x03},
    //CRF0[3]=1
    {IT8728F_CONFIG_INDEX, 0x00, 0xF0},
    {IT8728F_CONFIG_DATA,  0xF7, 0x08},
    //-----------Runtime Registers---------------------------------------------------
    //>>AP V1.0,IT8728F_IT8772E_BIOSAp10022v1 0.pdf
//    #if IT8728F_HWM_SUPPORT //RayWu, REMOVE 2014/07/28
#if IT8728F_HWM_PRESENT //RayWu, ADD 2014/07/28
    //select EC
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_ENV},
    // Program Base Addr
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_HWM_BASE_ADDRESS & 0xFF)},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_HWM_BASE_ADDRESS >> 8)},
    // Program PME base address
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE2_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)((UINT16)IT8728F_PME_BASE_ADDRESS >> 8)},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE2_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)((UINT16)IT8728F_PME_BASE_ADDRESS & 0x00FF)},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_ACTIVATE_VALUE},
//RayWu, REMOVE 2014/07/28 >>
//    //enable voltage channel
//    {IT8728F_HWM_BASE_ADDRESS+0x05, 0x00, 0x50},
//    {IT8728F_HWM_BASE_ADDRESS+0x06, 0x00, 0xFF},
//    //enable temperature channel
//    {IT8728F_HWM_BASE_ADDRESS+0x05, 0x00, 0x51},
//    {IT8728F_HWM_BASE_ADDRESS+0x06, 0x00, 0x38},
//    //index00h[0]=1,start monitor
//    {IT8728F_HWM_BASE_ADDRESS+0x05, 0x00, 0x00},
//    {IT8728F_HWM_BASE_ADDRESS+0x06, 0x00, 0x01},
//    //Index 4A don't write any value
//#if (THERMAL_SENSOR_INTERFACE==2)//select PECI interface
//    //index0Ah=64h
//    {IT8728F_HWM_BASE_ADDRESS + 5,  0x00, 0x0A},
//    {IT8728F_HWM_BASE_ADDRESS + 6,  0x00, 0x64},
//    //index8Eh[7,6]=11
//    //When Intel PECI support, set 0x8E register bit6,7 = 1,1
//    {IT8728F_HWM_BASE_ADDRESS+0x05, 0x00, 0x8E},
//    {IT8728F_HWM_BASE_ADDRESS+0x06, 0x3F, 0xC0},
//#endif
//    //index00h[6]=1, Update VBAT Voltage Reading again
//    {IT8728F_HWM_BASE_ADDRESS+0x05, 0x00, 0x00},
//    {IT8728F_HWM_BASE_ADDRESS+0x06, 0x00, 0x40},
//RayWu, REMOVE 2014/07/28 <<
#endif
    //<<AP V1.0,IT8728F_IT8772E_BIOSAp10022v1 0.pdf
    //--------------------------------------------------------------------------
    // <<ITE AP Workaround End
    //--------------------------------------------------------------------------
    // Program clock setting in global registers
    // Bit0: 0/1 for CLKIN is 48Mhz/24MHz .
    {IT8728F_CONFIG_INDEX, 0x00, 0x23},
    {IT8728F_CONFIG_DATA,  0xEE, 0x00 | (IT8728F_WDT_CLK_SRC << 4) | IT8728F_CLOCK},
    //---------------------------------------------------------------------
    // Before init all logical devices, program GPIO Multi-Pin if needed.
    //---------------------------------------------------------------------
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_GPIO},

    {IT8728F_CONFIG_INDEX, 0x00, 0x62},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_GPIO_BASE_ADDRESS>>8)},
    {IT8728F_CONFIG_INDEX, 0x00, 0x63},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)IT8728F_GPIO_BASE_ADDRESS},

//RayWu, REMOVE 2014/07/28 >>
//    {IT8728F_CONFIG_INDEX, 0x00, 0x25},
//    {IT8728F_CONFIG_DATA,  0x08, 0x00},// GPIO Set 1 Multi-Function Pin Selection Register (Index=25h, Default=00h)
//    //config as uart2
//    {IT8728F_CONFIG_INDEX, 0x00, 0x26},
//    {IT8728F_CONFIG_DATA,  0x00, 0x00},// GPIO Set 2 Multi-Function Pin Selection Register (Index=26h, Default=FFh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x27},
//    {IT8728F_CONFIG_DATA,  0x00, 0x00},// GPIO Set 3 Multi-Function Pin Selection Register (Index=27h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x28},
//    {IT8728F_CONFIG_DATA,  0x40, 0x00},// GPIO Set 4 Multi-Function Pin Selection Register (Index=28h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x29},
//    {IT8728F_CONFIG_DATA,  0x00, 0x00},// GPIO Set 5 Multi-Function Pin Selection Register (Index=29h, Default=00h)
//RayWu, REMOVE 2014/07/28 <<
//RayWu, REMOVE 2015/05/05 >>
////RayWu, ADD 2014/07/28 >>
//    {IT8728F_CONFIG_INDEX, 0x00, 0x25},
//    {IT8728F_CONFIG_DATA,  0x08, GPIO_1X_SEL},          // GPIO Set 1 Multi-Function Pin Selection Register (Index=25h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x26},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_2X_SEL},          // GPIO Set 2 Multi-Function Pin Selection Register (Index=26h, Default=FFh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x27},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_3X_SEL},          // GPIO Set 3 Multi-Function Pin Selection Register (Index=27h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x28},
//    {IT8728F_CONFIG_DATA,  0x40, GPIO_4X_SEL},          // GPIO Set 4 Multi-Function Pin Selection Register (Index=28h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x29},
//    {IT8728F_CONFIG_DATA,  0xC0, GPIO_50_55_SEL},       // GPIO Set 5 Multi-Function Pin Selection Register (Index=29h, Default=00h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0x29},
//    {IT8728F_CONFIG_DATA,  0xBF, GPIO_5X_6X_PS2_SEL},
//    {IT8728F_CONFIG_INDEX, 0x00, 0x29},
//    {IT8728F_CONFIG_DATA,  0x7F, GPIO_65_SEL},
////RayWu, ADD 2014/07/28 <<
//RayWu, REMOVE 2015/05/05 <<

//RayWu, ADD 2015/05/05 >>
    {IT8728F_CONFIG_INDEX, 0x00, 0x25},
    {IT8728F_CONFIG_DATA,  0x08, (GP17 << 7) | (GP16 << 6) | (GP15 << 5) | (GP14 << 4) | (0 << 3) | (GP12 << 2) | (GP11 << 1) | (GP10)},		// GPIO Set 1 Multi-Function Pin Selection Register (Index=25h, Default=00h)
    {IT8728F_CONFIG_INDEX, 0x00, 0x26},
    {IT8728F_CONFIG_DATA,  0x08, (GP27 << 7) | (GP26 << 6) | (GP25 << 5) | (GP24 << 4) | (GP23 << 3) | (GP22 << 2) | (GP21 << 1) | (GP20)},		// GPIO Set 2 Multi-Function Pin Selection Register (Index=26h, Default=FFh)
    {IT8728F_CONFIG_INDEX, 0x00, 0x27},
    {IT8728F_CONFIG_DATA,  0x08, (GP37 << 7) | (GP36 << 6) | (GP35 << 5) | (GP34 << 4) | (GP33 << 3) | (GP32 << 2) | (GP31 << 1) | (GP30)},		// GPIO Set 3 Multi-Function Pin Selection Register (Index=27h, Default=00h)
    {IT8728F_CONFIG_INDEX, 0x00, 0x28},
    {IT8728F_CONFIG_DATA,  0x08, (GP47 << 7) | (0 << 6) | (GP45 << 5) | (GP44 << 4) | (GP43 << 3) | (GP42 << 2) | (GP41 << 1) | (GP40)},		// GPIO Set 4 Multi-Function Pin Selection Register (Index=28h, Default=00h)
    {IT8728F_CONFIG_INDEX, 0x00, 0x29},
    {IT8728F_CONFIG_DATA,  0x01, (GP65 << 7) | (GP56_57_60_61_62 << 6) | (GP55 << 5) | (GP54 << 4) | (GP53 << 3) | (GP52 << 2) | (GP51 << 1) | 0},	// GPIO Set 5 Multi-Function Pin Selection Register (Index=29h, Default=00h)
//RayWu, ADD 2015/05/05 <<

//RayWu, ADD 2015/07/28 >>
    #if (IT8728F_BUS_SELECTION == 1)
    {IT8728F_CONFIG_INDEX, 0x00, 0xE9},
    {IT8728F_CONFIG_DATA,  0xDF, 0x20},
    #endif
//RayWu, ADD 2015/07/28 <<

    //>>EIP76867: ITE APNote,set PWRGD 1 and then set 0 will cause AMD CPU can not enter OS
#if (IT8728F_AMD_PWRGD==0)//it is intel platform,AMD platform will skipt
    {IT8728F_CONFIG_INDEX, 0x00, 0x2A},
    {IT8728F_CONFIG_DATA,  0xDF, 0x00 | (PWRGD<<5)},// Extended 1 Multi-Function Pin Selection Register (Index=2Ah, Default=00h)
#endif
    //<<EIP76867 End
#if (IT8728F_PARALLEL_PORT_PRESENT == 0)
	//For GP80~87 Simple IO Enable:
    //Parallel Port disabled: LDN 3\Index 30=00h
	//SMbue Isolation Disable: Global Index 2Ch<bit 7>=1
    //CR2C[7]=1
    {IT8728F_CONFIG_INDEX, 0x00, 0x2C},
    {IT8728F_CONFIG_DATA,  0x7F, 0x80},
#endif
//RayWu, ADD 2014/07/28 >>
    //---------------------------------------------------------------------
    // GPIO porting
    //---------------------------------------------------------------------
//RayWu, REMOVE 2015/05/05 >>
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC0},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_1X_SEL},		// Simple I/O GPIO Set 1 (Index=C0h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC1},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_2X_SEL},		// Simple I/O GPIO Set 2 (Index=C1h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC2},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_3X_SEL},		// Simple I/O GPIO Set 3 (Index=C2h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC3},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_4X_SEL},		// Simple I/O GPIO Set 4 (Index=C3h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC4},
//    {IT8728F_CONFIG_DATA,  0x00, ((GPIO_5X_6X_PS2_SEL<<1)|(GPIO_5X_6X_PS2_SEL)|GPIO_50_55_SEL)},	// Simple I/O GPIO Set 5 (Index=C4h)
//RayWu, REMOVE 2015/05/05 <<

//RayWu, ADD 2015/05/05 >>
    {IT8728F_CONFIG_INDEX, 0x00, 0xC0},
    {IT8728F_CONFIG_DATA,  0x08, (GP17 << 7) | (GP16 << 6) | (GP15 << 5) | (GP14 << 4) | (0 << 3) | (GP12 << 2) | (GP11 << 1) | (GP10)},
    {IT8728F_CONFIG_INDEX, 0x00, 0xC1},
    {IT8728F_CONFIG_DATA,  0x00, (GP27 << 7) | (GP26 << 6) | (GP25 << 5) | (GP24 << 4) | (GP23 << 3) | (GP22 << 2) | (GP21 << 1) | (GP20)},
    {IT8728F_CONFIG_INDEX, 0x00, 0xC2},
    {IT8728F_CONFIG_DATA,  0x00, (GP37 << 7) | (GP36 << 6) | (GP35 << 5) | (GP34 << 4) | (GP33 << 3) | (GP32 << 2) | (GP31 << 1) | (GP30)},
    {IT8728F_CONFIG_INDEX, 0x00, 0xC3},
    {IT8728F_CONFIG_DATA,  0x00, (GP47 << 7) | (0 << 6) | (GP45 << 5) | (GP44 << 4) | (GP43 << 3) | (GP42 << 2) | (GP41 << 1) | (GP40)},
    {IT8728F_CONFIG_INDEX, 0x00, 0xC4},
    {IT8728F_CONFIG_DATA,  0x01, (GP56_57_60_61_62 << 7) | (GP56_57_60_61_62 << 6) | (GP55 << 5) | (GP54 << 4) | (GP53 << 3) | (GP52 << 2) | (GP51 << 1) | 0},
//RayWu, ADD 2015/05/05 <<

//RayWu, REMOVE 2015/05/05 >>
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC8},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_1X_IN_OUT},	// GPIO Set 1 Input Output (Index=C8h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xC9},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_2X_IN_OUT},	// GPIO Set 2 Input Output (Index=C9h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCA},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_3X_IN_OUT},	// GPIO Set 3 Input Output (Index=CAh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCB},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_4X_IN_OUT},	// GPIO Set 4 Input Output (Index=CBh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCC},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_5X_IN_OUT},	// GPIO Set 5 Input Output (Index=CCh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCD},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_6X_IN_OUT},	// GPIO Set 6 Input Output (Index=CDh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCE},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_7X_IN_OUT},	// GPIO Set 7 Input Output (Index=CEh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xCF},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_8X_IN_OUT},	// GPIO Set 8 Input Output (Index=CFh)
//
//    {IT8728F_CONFIG_INDEX, 0x00, 0xB8},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_1X_PULL_UP},	// GPIO Set 1 Internal Pull-Up (Index=B8h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xB9},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_2X_PULL_UP},	// GPIO Set 2 Internal Pull-Up (Index=B9h)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xBA},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_3X_PULL_UP},	// GPIO Set 3 Internal Pull-Up (Index=BAh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xBB},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_4X_PULL_UP},	// GPIO Set 4 Internal Pull-Up (Index=BBh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xBC},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_5X_PULL_UP},	// GPIO Set 5 Internal Pull-Up (Index=BCh)
//    {IT8728F_CONFIG_INDEX, 0x00, 0xBD},
//    {IT8728F_CONFIG_DATA,  0x00, GPIO_6X_PULL_UP},	// GPIO Set 6 Internal Pull-Up (Index=BDh)
//
//    {IT8728F_CONFIG_INDEX, 0x00, 0x62},
//    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_GPIO_BASE_ADDRESS>>8)},
//    {IT8728F_CONFIG_INDEX, 0x00, 0x63},
//    {IT8728F_CONFIG_DATA,  0x00, (UINT8)IT8728F_GPIO_BASE_ADDRESS},
//RayWu, REMOVE 2015/05/05 <<

//RayWu, REMOVE, 2014/09/05 >>
//    {IT8728F_GPIO_BASE_ADDRESS + 0, 0x00, GPIO_1X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 1, 0x00, GPIO_2X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 2, 0x00, GPIO_3X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 3, 0x00, GPIO_4X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 4, 0x00, GPIO_5X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 5, 0x00, GPIO_6X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 6, 0x00, GPIO_7X_OUTPUT_DEFAULT},
//    {IT8728F_GPIO_BASE_ADDRESS + 7, 0x00, GPIO_8X_OUTPUT_DEFAULT},
//RayWu, REMOVE, 2014/09/05 <<

//RayWu, ADD 2014/07/28 <<
    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (IT8728F_SERIAL_PORT1_PRESENT)
    // Select device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_UART1},
    // Program Base Addr
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_ACTIVATE_VALUE},
#endif
#endif
    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
//RayWu, ADD 2015/08/11 >>
#if (IT8728F_MOUSE_PRESENT)
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_PS2M},
    // Program Interrupt
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_IRQ1_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x0C},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_ACTIVATE_VALUE},
#endif //IT8728F_MOUSE_PRESENT
//RayWu, ADD 2015/08/11 <<
//#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT) //RayWu, REMOVE 2015/08/11
#if (IT8728F_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_PS2K},
    // Program Base Addr
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x60},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE2_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE2_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_IRQ1_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_PS2K},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_DEACTIVATE_VALUE},
#endif //IT8728F_KEYBOARD_PRESENT
#if (IT8728F_FLOPPY_PORT_PRESENT)
    // Seclect device FLOPPY
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_FDC},
    // Program Base Addr
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x03},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0xF0},
    // Program Interrupt
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_IRQ1_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x06},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0xFF, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0xFF, IT8728F_ACTIVATE_VALUE},
#endif //IT8728F_FLOPPY_PORT_PRESENT
//#endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1) //RayWu, REMOVE 2015/08/11
    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
#if (IT8728F_PARALLEL_PORT_PRESENT)
    //Select LDN 03h
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x03},
    //Set parallel port mode to EPP+ECP mode
    {IT8728F_CONFIG_INDEX, 0x00, 0xF0},
    {IT8728F_CONFIG_DATA,  0xFC, 0x03},
#endif// IT8728F_PARALLEL_PORT_PRESENT

    // Seclect device KEYBOARD
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_PS2K},
    // config
    {IT8728F_CONFIG_INDEX, 0x00, 0xF0},
    {IT8728F_CONFIG_DATA,  0xF7, 0x00 | (IT8728F_KBC_CLOCK << 3)},
    // Seclect device EC
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_ENV},
    // config
    {IT8728F_CONFIG_INDEX, 0x00, 0xF4}, //Auto-swap of KCLK/KDAT and MCLK/MDAT
    {IT8728F_CONFIG_DATA,  0x7F, IT8728F_PS2_SWAP << 7},
    // Clear Interrupt
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_IRQ1_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, 0x00},

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {IT8728F_CONFIG_INDEX, 0x00, 0x02},
    {IT8728F_CONFIG_DATA,  0x00, 0x02},

    //---------------------------------------------------------------------
    // PEI Init Hardware Monitor.
    //---------------------------------------------------------------------
    #if IT8728F_HWM_PRESENT
        // Program Global Configuration Registers.
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x50},
        {IT8728F_HWM_DATA_PORT, 0x00, VIN0_7_SUPPORT},
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x51},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (IT8728F_TEMP_SST_PECI_HTRR << 6)
            | (IT8728F_TEMP_RESISTOR_MODE_3_ENABLE << 5)//TMP 1-3 Set to Thermal Resistor
            | (IT8728F_TEMP_RESISTOR_MODE_2_ENABLE << 4)//Thermal Diode
            | (IT8728F_TEMP_RESISTOR_MODE_1_ENABLE << 3)
            | (IT8728F_TEMP_DIODE_MODE_3_ENABLE << 2)
            | (IT8728F_TEMP_DIODE_MODE_2_ENABLE << 1)
            | IT8728F_TEMP_DIODE_MODE_1_ENABLE},
    #if (IT8728F_ETSHS_MODE > 1)    //PECI or SST Host must set Clock to 24MHz (AN1.3)
        //External Thermal Sensor Host Selection
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x0A},
        {IT8728F_HWM_DATA_PORT, 0x83,  0x44 | (IT8728F_ETSHS_MODE << 4)},
        //PECI idle high
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x8E},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x02},
    #else
        //External Thermal Sensor Host Selection
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x0A},
        {IT8728F_HWM_DATA_PORT, 0x8F, 0x40 | (IT8728F_ETSHS_MODE << 4)},
    #endif // IT8728F_ETSHS_MODE
        //Fan PWM Smoothing Step Frequency Selection Register
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x0B},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (FAN_PWM_SMOOTH_FREQ_SEL << 6)
            | (FAN_CTL5_SEL << 2)
            | FAN_CTL4_SEL},
        //Fan Tachometer Control Register
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x0C},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (TMPIN3_ENHANCED_INT_MODE_EN << 7)
            | (TMPIN2_ENHANCED_INT_MODE_EN << 6)
            | (FAN_TAC5_EN << 5)
            | (FAN_TAC4_EN << 4)
            | (TMPIN1_ENHANCED_INT_MODE_EN << 3)},
        //Fan Controller Main Control Register
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x13},
        {IT8728F_HWM_DATA_PORT,  0x8F, 0x00 | (FAN_TAC_3 << 6)
            | (FAN_TAC_2 << 5) 
            | (FAN_TAC_1 << 4)},
        //FAN_CTL Control Register
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x14},
        {IT8728F_HWM_DATA_PORT, 0x7F,  0x00 | (FAN_CTL_POLARITY << 7)},
        //Thermal Diode Zero Degree Adjust register write enable
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x5C},
        {IT8728F_HWM_DATA_PORT, 0x7F, 0x80},
    #if TEMP_ADJUST_1
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x56},
        {IT8728F_HWM_DATA_PORT, 0x00, TEMP_ADJUST_1},
    #endif  // TEMP_ADJUST_1
    #if TEMP_ADJUST_2
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x57},
        {IT8728F_HWM_DATA_PORT, 0x00, TEMP_ADJUST_2},
    #endif  // TEMP_ADJUST_2
    #if TEMP_ADJUST_3
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x59},
        {IT8728F_HWM_DATA_PORT, 0x00, TEMP_ADJUST_3},
    #endif // TEMP_ADJUST_3
        //Thermal Diode Zero Degree Adjust register write disable
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x5C},
        {IT8728F_HWM_DATA_PORT, 0x7F, 0x00},
        //FAN_CTL3-1 SmartGuardian Automatic Mode Register
        //Bit 7   : This bit selects the PWM linear changing decreasing mode
        //          0:Slow decreasing mode
        //          1:Direct decreasing mode
        //Bit 6   : FAN Full Limit Control as Thermal out Reached 
        //          When the relevant enable bit is set and the FAN output mode is selected as Automatic 
        //          mode by bit7 of EC index 15h, 16h, 17h, the corresponding FAN output will be forced to 
        //          full PWM if any thermal output limit is reached. 
        //          0: Disable 
        //          1: Enable
        //Bit 4-0 : Temperature internal
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x65},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (FAN1_DIRECT_DOWN_CTRL << 7)
            | (FAN1_FULL_ON_AS_THERMAL_REACHED << 6)
            | FAN_CTL1_TEMP_INTERVAL},
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x6D},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (FAN2_DIRECT_DOWN_CTRL << 7)
            | (FAN2_FULL_ON_AS_THERMAL_REACHED << 6)
            | FAN_CTL2_TEMP_INTERVAL},
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x75},
        {IT8728F_HWM_DATA_PORT, 0x00, 0x00 | (FAN3_DIRECT_DOWN_CTRL << 7)
            | (FAN3_FULL_ON_AS_THERMAL_REACHED << 6)
            | FAN_CTL3_TEMP_INTERVAL},
    #if (IT8728F_ETSHS_MODE == 6)
        //Host Target Address
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x89},
        {IT8728F_HWM_DATA_PORT, 0x00, Host_Target_Address},
        //Host Write Length
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x8A},
        {IT8728F_HWM_DATA_PORT, 0x00, Host_Write_Length},
        //Host Read Length
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x8B},
        {IT8728F_HWM_DATA_PORT, 0x00, Host_Read_Length},
        //Command
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x8C},
        {IT8728F_HWM_DATA_PORT, 0x00, Host_Command},
        //Auto-Start
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x8E},
        {IT8728F_HWM_DATA_PORT, 0x00, 0xF0},
    #endif
        //Index 00 bit 6 set to 1(Update VBAT Voltage Reading again)
        {IT8728F_HWM_INDEX_PORT, 0x00, 0x00},
        {IT8728F_HWM_DATA_PORT, 0xBE, 0x41},
    #endif  // IT8728F_HWM_PRESENT
};

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
