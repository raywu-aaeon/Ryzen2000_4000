//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiGpioLib.c
    South Bridge Chipset GPIO Library implementation

*/

#include <Library/AmiGpioLib.h>
#include "Token.h"
#include <Sb.h>
#include <Library/AmiFchIoAccessLib.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
UINT32
AmdFchGpioGetGpe0BitNum (
  IN SB_GPE0_TYPE Gpe0Type,
  IN UINT32 PinNum
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

UINT8 IoMuxSelect[] = {
	// 55570-B1 Rev 1.06 - May 18, 2018   PPR for AMD Family 17h Models 11h,18h B1
	// 15.2.16.1  IOMUX Registers
	//0  1  2  3  4  5  6  7  8  9 
	//
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,   // GPIO 0 ~ 9   (0 ~ 9)
    0, 0, 1, 1, 1, 0, 1, 1, 1, 2,   // GPIO 10 ~ 19 (0xA ~ 0x13)
    2, 2, 2, 3, 1, 0, 1, 0, 0, 1,   // GPIO 20 ~ 29 (0x14 ~ 0x1D)
    2, 2, 2, 0, 0, 0, 0, 0, 0, 0,   // GPIO 30 ~ 39 (0x1E ~ 0x27)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 40 ~ 49 (0x28 ~ 0x31)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 50 ~ 59 (0x32 ~ 0x3B)
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0,   // GPIO 60 ~ 69 (0x3C ~ 0x45)
    0, 0, 0, 0, 2, 2, 1, 0, 0, 0,   // GPIO 70 ~ 79 (0x46 ~ 0x4F)
    0, 0, 0, 0, 1, 1, 1, 2, 2, 2,   // GPIO 80 ~ 89
    2, 1, 3, 0, 0, 0, 0, 0, 0, 0,   // GPIO 90 ~ 99
    0, 0, 0, 0, 3, 3, 3, 3, 2, 2,   // GPIO 100 ~ 109
    0, 0, 0, 2, 2, 1, 1, 0, 0, 0,   // GPIO 110 ~ 119
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1,   // GPIO 120 ~ 129
    1, 3, 2, 0, 0, 2, 1, 2, 1, 1,   // GPIO 130 ~ 139
    2, 1, 2, 1, 1,                  // GPIO 140 ~ 144
                   0, 0, 0, 0, 0,   // GPIO 145 ~ 159   not used 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 150 ~ 159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 160 ~ 169
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 170 ~ 179
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 180 ~ 189
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 190 ~ 199
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 200 ~ 209
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 210 ~ 219
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 220 ~ 229
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 230 ~ 239
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // GPIO 240 ~ 249
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0    // GPIO 250 ~ 255
};

struct {
    SB_GPE0_TYPE Gpe0Type;
    UINT32 PinNum;
    struct {
        UINT32 Reg;
        UINT32 BitOffset;
    } Sci, Smi;
} CONST AmdSciMapTbl[] = {
    {TYPE_GPE0_GEVENT0,                 89,     {0x40, 0},  {0xA0, 0}},
    {TYPE_GPE0_GEVENT1,                 90,     {0x40, 8},  {0xA0, 2}},
    {TYPE_GPE0_GEVENT2,                 3,      {0x40, 16}, {0xA0, 4}},
    {TYPE_GPE0_GEVENT3,                 22,     {0x40, 24}, {0xA0, 6}},
    {TYPE_GPE0_GEVENT4,                 4,      {0x44, 0},  {0xA0, 8}},
    {TYPE_GPE0_GEVENT5,                 21,     {0x44, 8},  {0xA0, 10}},
    {TYPE_GPE0_GEVENT6,                 91,     {0x44, 16}, {0xA0, 12}},
    {TYPE_GPE0_GEVENT7,                 5,      {0x44, 24}, {0xA0, 14}},
    {TYPE_GPE0_GEVENT8,                 2,      {0x48, 0},  {0xA0, 16}},
    {TYPE_GPE0_GEVENT9,                 86,     {0x48, 8},  {0xA0, 18}},
    {TYPE_GPE0_GEVENT10,                6,      {0x48, 16}, {0xA0, 20}},
    {TYPE_GPE0_GEVENT11,                76,     {0x48, 24}, {0xA0, 22}},
    {TYPE_GPE0_GEVENT12,                16,     {0x4C, 0},  {0xA0, 24}},
    {TYPE_GPE0_GEVENT13,                17,     {0x4C, 8},  {0xA0, 26}},
    {TYPE_GPE0_GEVENT14,                18,     {0x4C, 16}, {0xA0, 28}},
    {TYPE_GPE0_GEVENT15,                24,     {0x4C, 24}, {0xA0, 30}},
    {TYPE_GPE0_GEVENT16,                23,     {0x50, 0},  {0xA4, 0}},
    {TYPE_GPE0_GEVENT17,                129,    {0x50, 8},  {0xA4, 2}},
    {TYPE_GPE0_GEVENT18,                84,     {0x50, 16}, {0xA4, 4}},
    {TYPE_GPE0_GEVENT19,                1,      {0x50, 24}, {0xA4, 6}},
    {TYPE_GPE0_GEVENT20,                40,     {0x54, 0},  {0xA4, 8}},
    {TYPE_GPE0_GEVENT21,                0,      {0x54, 8},  {0xA4, 10}},
    {TYPE_GPE0_GEVENT22,                9,      {0x54, 16}, {0xA4, 12}},
    {TYPE_GPE0_GEVENT23,                8,      {0x54, 24}, {0xA4, 14}},
    {TYPE_GPE0_eSPI,                    -1,     {0x58, 16}, {-1, -1}},
    {TYPE_GPE0_eSPI_WAKE_PME,           -1,     {0x58, 24}, {-1, -1}},
    {TYPE_GPE0_NB_GPP_PME,              -1,     {0x5c, 8},  {-1, -1}},
    {TYPE_GPE0_NB_GPP_HOTPLUG,          -1,     {0x5c, 16}, {-1, -1}},
    {TYPE_GPE0_FAKE_STS0,               -1,     {0x60, 8},  {0xA8, 2}},
    {TYPE_GPE0_FAKE_STS1,               -1,     {0x60, 16}, {0xA8, 4}},
    {TYPE_GPE0_PM_FAKE_STS2,            -1,     {0x60, 34}, {0xA8, 6}},
    {TYPE_GPE0_SATA0_PME,               -1,     {0x64, 8},  {0xA8, 10}},
    {TYPE_GPE0_SATA1_PME,               -1,     {0x64, 16}, {0xA8, 12}},
    {TYPE_GPE0_AZALIA_PME,              -1,     {0x64, 24}, {-1, -1}},
    {TYPE_GPE0_GPIO_INT,                -1,     {0x68, 8},  {0xA8, 18}},
    {TYPE_GPE0_ALT_HPET,                -1,     {0x68, 24}, {0xA8, 22}},
    {TYPE_GPE0_FAN_THERMAL,             -1,     {0x6C, 0},  {0xA8, 24}},
    {TYPE_GPE0_ASF_MASTER_AND_SLAVE,    -1,     {0x6C, 8},  {0xA8, 26}},
    {TYPE_GPE0_I2S_WAKW_EVENT,          -1,     {0x6C, 16}, {-1, -1}},
    {TYPE_GPE0_SMBUS0,                  -1,     {0x6C, 24}, {0xA8, 30}},
    {TYPE_GPE0_TWARN_PIN,               -1,     {0x70, 0},  {0xAC, 0}},
    {TYPE_GPE0_INTERNAL_TRAFFIC_MONITOR,-1,     {0x70, 8},  {0xAC, 2}},
    {TYPE_GPE0_PWRBTN,                  -1,     {0x70, 24}, {0xAC, 6}},
    {TYPE_GPE0_PROHOT_PIN,              -1,     {0x74, 0},  {0xAC, 8}},
    {TYPE_GPE0_HW_ASSERTION_MESSAGE,    -1,     {0x74, 8},  {0xAC, 10}},
    {TYPE_GPE0_SCI_ASSERTION_MESSAGE,   -1,     {0x74, 16}, {0xAC, 12}},
    {TYPE_GPE0_RAS_EVENT,               -1,     {0x74, 24}, {-1, -1}},
    {TYPE_GPE0_XHC_WAKE_EVENT,          -1,     {0x78, 8},  {0xAC, 18}},
    {TYPE_GPE0_AC_DC_TIMER_EVENT,       -1,     {0x78, 16}, {0xAC, 20}},

    {TYPE_GPE0_AMD_END, -1, {-1, -1}, {-1, -1}}
};


// GUID Definition(s)

// Protocol/Ppi Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    Get the enable bit setting in GPE0 per Gpe0Type

    @param Gpe0Type SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.

    @retval TRUE = Enabled / FALSE = Disabled

**/
BOOLEAN SbGetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
)
{
	UINT32 	Gpe0BitNum;
	BOOLEAN	IsGpe0En;

	IsGpe0En = FALSE;

	//
	// To get which GPE0 bit that the event use for.
	//
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(Gpe0Type, -1);

	if (Gpe0BitNum != -1) {
		// Check the corresponding GPE0 bit.
		if ((AmdFchMmioRead32(AMD_FCH_SMI_MMIO, FCH_SMI_REG04) >> Gpe0BitNum) & 1) {
			IsGpe0En = TRUE;
		}
	}

	return IsGpe0En;
}

/**
    Set the enable bit in GPE0 per Gpe0Type

    @param Gpe0Type SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.

    @retval VOID

**/
VOID SbSetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   We assume customer has assigned the GPE0 number for each type.
	UINT32 	Gpe0BitNum;

	//
	// To get which GPE0 bit that the event use for.
	//
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(Gpe0Type, -1);

	// Set the corresponding GPE0 bit.
	if (Gpe0BitNum != -1) AmdFchMmioOr32(AMD_FCH_SMI_MMIO, FCH_SMI_REG04, 1 << Gpe0BitNum);
}

/**
    Reset the enable bit in GPE0 per Gpe0Type

    @param Gpe0Type SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.

    @retval VOID

**/
VOID SbResetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   We assume customer has assigned the GPE0 number for each type.
	UINT32 	Gpe0BitNum;

	//
	// To get which GPE0 bit that the event use for.
	//
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(Gpe0Type, -1);

	// Clear the corresponding GPE0 bit.
	if (Gpe0BitNum != -1) AmdFchMmioAnd32(AMD_FCH_SMI_MMIO, FCH_SMI_REG04, ~(UINT32)(1 << Gpe0BitNum));
}

/**
    Save/Restore/ClearAll GPE0 register per Operation

    @param Operation  GPE0_EN_OP. GPE0_EN_OP_SAVE, GPE0_EN_OP_RESTORE,
                      GPE0_EN_OP_CLEAR_ALL.

    @retval VOID

**/
VOID SbGpe0Operation (
    IN GPE0_EN_OP   Operation
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   We assume customer has assigned the GPE0 number for each type.
	UINT32 static Gpe0Save = 0;

	switch (Operation) {
	case GPE0_EN_OP_SAVE:
		//###Gpe0Save = READ_IO32_PM (ACPI_IOREG_GPE0_EN);
		Gpe0Save = AmdFchMmioRead32 (AMD_FCH_ACPI_PM_MMIO, ACPI_IOREG_GPE0_EN);
		break;
	case GPE0_EN_OP_RESTORE:
		//###WRITE_IO32_PM (ACPI_IOREG_GPE0_EN, Gpe0Save);
		AmdFchMmioWrite32 (AMD_FCH_ACPI_PM_MMIO, ACPI_IOREG_GPE0_EN, Gpe0Save);
		break;
	case GPE0_EN_OP_CLEAR_ALL:
		//###WRITE_IO32_PM (ACPI_IOREG_GPE0_EN, 0);
		AmdFchMmioWrite32 (AMD_FCH_ACPI_PM_MMIO, ACPI_IOREG_GPE0_EN, 0);
		break;
	}
}

/**
    Get the status bit setting in GPE0 per GPE0 Type

    @param Gpe0Type SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.

    @retval TRUE = Set / FALSE= Clear

**/
BOOLEAN SbGetGpe0Sts (
    IN SB_GPE0_TYPE Gpe0Type
)
{

	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   We assume customer has assigned the GPE0 number for each type.
	UINT32 	Gpe0BitNum;
	BOOLEAN	IsGpe0En;

	IsGpe0En = FALSE;

	//
	// To get which GPE0 bit that the event use for.
	//
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(Gpe0Type, -1);

	if (Gpe0BitNum != -1) {
		// Get the corresponding GPE0 status bit.
		if ((AmdFchMmioRead32(AMD_FCH_SMI_MMIO,FCH_SMI_REG00) >> Gpe0BitNum) & 1) {
			IsGpe0En = TRUE;
		}
	}

	return IsGpe0En;
}

/**
    Clear the status bit in GPE0 per GPE0 Type

    @param Gpe0Type SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.

    @retval VOID 

**/
VOID SbClearGpe0Sts (
    IN SB_GPE0_TYPE Gpe0Type
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   We assume customer has assigned the GPE0 number for each type.
	UINT32 	Gpe0BitNum;

	//
	// To get which GPE0 bit that the event use for.
	//
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(Gpe0Type, -1);

	// Clear the corresponding GPE0 status bit.
	if (Gpe0BitNum != -1) AmdFchMmioAnd32(AMD_FCH_SMI_MMIO, FCH_SMI_REG00, ~(UINT32)(1 << Gpe0BitNum));
}

/**
    Set GPI Pin Enable bit in Gpe0

    @param Gpio - Define the group and Pin# of the GPIO

    @retval VOID

**/
VOID SbSetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   customer need to know the Gpio.PinNum of (GEVENT0~GEVENT23)
	UINT8	IoMuxEn = IoMuxSelect[Gpio.PinNum];

	// IoMux select GPIO.
	AmdFchMmioAndThenOr8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum, 0xFC , IoMuxEn);

	// Clear Bit23 OutputEnable
	AmdFchMmioAndThenOr32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), ~BIT23, 0);
}

/**
    Get GPI Pin Enable bit setting in Gpe0

    @param Gpio - Define the group and Pin# of the GPIO

    @retval TRUE = Enabled / FALSE= Disabled

**/
BOOLEAN SbGetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   customer need to know the Gpio.PinNum of (GEVENT0~GEVENT23)
	BOOLEAN IsGpi = FALSE;

	// IoMux select GPIO.
	//####MmioAndThenOr8(IoMuxMmio + Pin, 0xFC , IoMuxEn);
	// Check Bit23 OutputEnable
	if ((AmdFchMmioRead32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2)) & BIT23) == 0) IsGpi = TRUE;

	return IsGpi;
}

/**
    Reset GPI Pin Enable bit in Gpe0

    @param Gpio - Define the group and Pin# of the GPIO

    @retval VOID

**/
VOID SbResetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   customer need to know the Gpio.PinNum of (GEVENT0~GEVENT23)
	//
	//   AMD doesn't Gpi enable bit. we turn on GPO instead.
	UINT8	IoMuxEn = IoMuxSelect[Gpio.PinNum];

	// IoMux select GPIO.
	AmdFchMmioAndThenOr8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum, 0xFC , IoMuxEn);
	// Clear Bit23 OutputEnable
	AmdFchMmioAndThenOr32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), ~BIT23, 1);
}

/**
    Get GPI Pin Status bit setting in Gpe0

    @param Gpio - Define the group and Pin# of the GPIO

    @retval VOID

**/
BOOLEAN SbGetGpe0GpinSts (
    IN AMI_OEM_GPIO Gpio
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   Customer need to know corresponding Gpio.PinNum for GEVENT. (GEVENT0~GEVENT23)
	//
	UINT32 	Gpe0BitNum;
	BOOLEAN	IsGpe0En;

	IsGpe0En = FALSE;

	// Find the GPE0 bit number.
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(TYPE_GPE0_AMD_END, Gpio.PinNum);

	if (Gpe0BitNum != -1) {
		// Get the corresponding GPE0 status bit.
		if ((AmdFchMmioRead32(AMD_FCH_SMI_MMIO,FCH_SMI_REG00) >> Gpe0BitNum) & 1) {
			IsGpe0En = TRUE;
		}
	}

	return IsGpe0En;
}

/**
    Clear GPI Pin Status bit in Gpe0

    @param Gpio - Define the group and Pin# of the GPIO

    @retval VOID

**/
VOID SbClearGpe0GpinSts (
    IN AMI_OEM_GPIO Gpio
)
{
	// <AAV> TBD :
	//		The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number for each type.
	//
	// The following porting :
	//   Customer need to know corresponding Gpio.PinNum for GEVENT. (GEVENT0~GEVENT23)
	//
	UINT32 	Gpe0BitNum;

	// Find the GPE0 bit number.
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(TYPE_GPE0_AMD_END, Gpio.PinNum);

	if (Gpe0BitNum != -1) {
		// Get the corresponding GPE0 status bit.
		AmdFchMmioOr32(AMD_FCH_SMI_MMIO,FCH_SMI_REG00, 1 << Gpe0BitNum);
	}
}

/**
    Get GPIO Use Setting

    @param Gpio - Define the group and Pin# of the GPIO

    @retval TRUE = GPIO MODE / FALSE= NATIVE MODE

**/
BOOLEAN SbGetGpioUseSel (
    IN AMI_OEM_GPIO Gpio
)
{
	BOOLEAN IsGpio = FALSE;
	UINT8	IoMux;

	IoMux = AmdFchMmioRead8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum) & 3; // Bit[0:1]

	if (IoMux == IoMuxSelect[Gpio.PinNum]) {
		IsGpio = TRUE;
	}

	return IsGpio;
}

/**
    Program GPIO Use Setting

    @param Gpio - Define the group and Pin# of the GPIO
    @param GpioMode - TRUE = GPIO MODE / FALSE= NATIVE MODE
    @param MulFunc - While this pin is a multi-function pin and GpioMode
                     is Native Mode, BIOS will refer to MulFunc to
                     determine which native function this pin will be
                     used.

    @retval VOID

**/
VOID SbProgGpioUseSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      GpioMode,
    IN UINT8        MulFunc
)
{
	if (GpioMode) {
		AmdFchMmioWrite8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum, IoMuxSelect[Gpio.PinNum]);
	} else {
		AmdFchMmioWrite8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum, MulFunc);
	}
}

/**
    Get GPIO I/O Setting

    @param Gpio - Define the group and Pin# of the GPIO

    @retval TRUE : Input Mode / FALSE : Output Mode

**/
BOOLEAN SbGetGpioIoSel (
    IN AMI_OEM_GPIO Gpio
)
{
	BOOLEAN IsInputMode = FALSE;

	// Bit23 OutputEnable
	if (!(AmdFchMmioRead32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2)) & BIT23)) {
		IsInputMode = TRUE;
	}

	return IsInputMode;
}

/**
    Set GPIO I/O Setting

    @param Gpio - Define the group and Pin# of the GPIO
    @param InputMode - TRUE : Input Mode / FALSE : Output Mode

    @retval VOID

**/
VOID SbSetGpioIoSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      InputMode
)
{
	if (InputMode) {
		AmdFchMmioAnd32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), ~BIT23);
	} else {
		AmdFchMmioOr32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), BIT23);
	}
}

/**
    Get GPIO Level Setting

    @param Gpio - Define the group and Pin# of the GPIO

    @retval TRUE: High level / FALSE: Low level

**/
BOOLEAN SbGetGpioLvlSel (
    IN AMI_OEM_GPIO Gpio
)
{
	BOOLEAN IsLevelHigh = FALSE;
	UINT32	GpioContext = AmdFchMmioRead32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2));
	UINT8	Level;

	if (GpioContext & BIT23) {
		// if GPO return ActiveLevel.

		// Bits Definition   	Bits Definition
		// 00b Active high 		10b Active on both of edges if LevelTrig=0
		// 01b Active Low 		11b Reserved
		Level = (GpioContext >> 9) & 3;

		if (Level == 0) {
			IsLevelHigh = TRUE;
		} else if (Level == 1) {
			IsLevelHigh = FALSE;
		}
	} else {
		// if GPI return PinSts.
		Level = (GpioContext >> 16) & 1;
		
		if (Level == 0) {
			IsLevelHigh = FALSE;
		} else if (Level == 1) {
			IsLevelHigh = TRUE;
		}
	}

	return IsLevelHigh;
}

/**
    Set GPIO Level

    @param Gpio - Define the group and Pin# of the GPIO
    @param High - TRUE: Set to High level / FALSE: Set to Low level

    @retval VOID

**/
VOID SbSetGpioLvlSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      High
)
{
	UINT8	Level;

	// Bits Definition   	Bits Definition
	// 00b Active high 		10b Active on both of edges if LevelTrig=0
	// 01b Active Low 		11b Reserved
	if (High) {
		Level = 0;
	} else {
		Level = 1;
	}

	AmdFchMmioAndThenOr32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), ~(BIT9 + BIT10), Level << 9);
}

/**
    Read Alternate GPI SMI Status Register

    @param Gpio - Define the group and Pin# of the GPIO

    @return The value read from Alternate GPI SMI Status Register

**/
UINT32 SbReadAltGpiSmiSts (
    IN AMI_OEM_GPIO Gpio
)
{
	return AmdFchMmioRead32(AMD_FCH_SMI_MMIO, FCH_SMI_REG10);
}

/**
    Clear Alternate GPI SMI Status

    @param Gpio - Define the group and Pin# of the GPIO

    @retval VOID

**/
VOID SbClearAltGpiSmiSts (
    IN AMI_OEM_GPIO Gpio
)
{
	// The following porting :
	//   Currently, We only support AMD-GEVENT as Alt Gpi Smi.
	//   Customer need to know corresponding Gpio.PinNum for GEVENT. (GEVENT0~GEVENT23)
	UINT32 	Gpe0BitNum;

	// Find the GPE0 bit number.
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(TYPE_GPE0_AMD_END, Gpio.PinNum);

	if (Gpe0BitNum != -1) {
		AmdFchMmioOr32(AMD_FCH_SMI_MMIO,FCH_SMI_REG10, 1 << Gpe0BitNum);
	}
}

/**
    Program Alternate GPI SMI Register

    @param Gpio - Define the group and Pin# of the GPIO
    @param Set - TRUE: Set / FALSE: Clear corresponding Alternate GPI SMI
                 Enable bit.

    @retval VOID

**/
VOID SbProgramAltGpiSmi (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      Set
)
{
	// The following porting :
	//   Currently, We only support AMD-GEVENT as Alt Gpi Smi.
	//   Customer need to know corresponding Gpio.PinNum for GEVENT. (GEVENT0~GEVENT23)
	UINT32 Gpe0BitNum;

	// Find the GPE0 bit number.
	Gpe0BitNum = AmdFchGpioGetGpe0BitNum(TYPE_GPE0_AMD_END, Gpio.PinNum);

	if (Gpe0BitNum != -1) {
		if (Set) AmdFchMmioOr32(AMD_FCH_SMI_MMIO,FCH_SMI_REG14, 1 << Gpe0BitNum);
		else AmdFchMmioOr32(AMD_FCH_SMI_MMIO,FCH_SMI_REG14, ~(1 << Gpe0BitNum));
	}
}

/**
    Program GPIO Rout

    @param Gpio - Define the group and Pin# of the GPIO
    @param Mode - NO_EFFECT/SMI_MODE/SCI_MODE/NMI_MODE

    @retval VOID

**/
VOID SbProgramGpioRout (
    IN AMI_OEM_GPIO Gpio,
    IN UINT8        Mode
)
{
	// The following porting :
	//   Currently, We only support AMD-GEVENT as Alt Gpi Smi.
	//   Customer need to know corresponding Gpio.PinNum for GEVENT. (GEVENT0~GEVENT23)
	UINT32 SmiCtrlMode;
	UINT32 i;

	switch (Mode) {
	case 0:
		SmiCtrlMode = 0;
		break;
	case 1:
		SmiCtrlMode = 1;
		break;
	case 2:
		// <AAV>
		//	 No SCI_MODE support. The Gpe0Type of AMD GPE0 field is dynamic. Customer should assign the GPE0 number in SciMap for each Pin.
		SmiCtrlMode = 0; // disable : means the SCI depend on SciMap register.
		//##return;
		break;
	case 3:
		SmiCtrlMode = 2;
		break;
	}

	i = 0;
	do {
	    if (AmdSciMapTbl[i].PinNum == Gpio.PinNum) {
	        AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, AmdSciMapTbl[i].Smi.Reg, ~(3 << AmdSciMapTbl[i].Smi.BitOffset),  SmiCtrlMode);
	        break;
	    }
	    i++;
	} while(AmdSciMapTbl[i].Gpe0Type != TYPE_GPE0_AMD_END);
}

/**
    Program GPIO Register

    @param Gpio - Define the group and Pin# of the GPIO
    @param RegType - The register type which is going to read
    @param AndData - The value to AND with read value from the GPIO register.
    @param OrData - The value to OR with the result of the AND operation.

    @retval VOID

**/
VOID SbProgramGpioRegister (
    IN AMI_OEM_GPIO   Gpio,
    IN GPIO_REG_TYPE  RegType,
    IN UINT32         AndData,
    IN UINT32         OrData
)
{
	UINT32	Data = 0;

	// <AAV> Check int and reserve pin later.
	//###if ((Gpio.PinNum << 2) >= 0xB8 || (Gpio.PinNum << 2) <= 0xF8) return 0xFFFFFFFF;

#if defined(AMI_CPM_LIB_WRAPPER_SUPPORT) && (AMI_CPM_LIB_WRAPPER_SUPPORT == 1)
	Data = (UINT16)AndData; // the UIN16 refer to AMD_CPM_GPIO_SETTING.
	CpmSetGpio(AmiCpmFchWrapperConstructor(), (UINT16)Gpio.PinNum, (UINT16)Data);
#else
	switch (RegType) {
	case AMD_GPIO:
		AmdFchMmioAndThenOr32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2), AndData, OrData);
		break;
	case AMD_IOMUX:
		AmdFchMmioAndThenOr8(AMD_FCH_IOMUX_MMIO, Gpio.PinNum, (UINT8)AndData, (UINT8)OrData);
		break;
	default:
		// EFI_UNSUPPORTED
		break;
	}
#endif
}

/**
    Read GPIO Register

    @param Gpio - Define the group and Pin# of the GPIO
    @param RegType - The register type which is going to read

    @retval 0xFFFFFFFF - Failed to read the register
    @retval Others - The data read from the register

**/
UINT32 SbReadGpioRegister (
    IN AMI_OEM_GPIO   Gpio,
    IN GPIO_REG_TYPE  RegType
)
{
	UINT32	Data = 0xFFFFFFFF;

	// <AAV> Check int and reserve pin later.
	//###if ((Gpio.PinNum << 2) >= 0xB8 || (Gpio.PinNum << 2) <= 0xF8) return 0xFFFFFFFF;

#if defined(AMI_CPM_LIB_WRAPPER_SUPPORT) && (AMI_CPM_LIB_WRAPPER_SUPPORT == 1)
	Data = (UINT32)CpmGetGpio(AmiCpmFchWrapperConstructor(), (UINT16)Gpio.PinNum);
#else
	switch (RegType) {
	case AMD_GPIO:
		Data = AmdFchMmioRead32 (AMD_FCH_GPIO_MMIO, (Gpio.PinNum << 2));
		break;
	case AMD_IOMUX:
		Data = AmdFchMmioRead32 (AMD_FCH_IOMUX_MMIO, Gpio.PinNum);
		break;
	default:
		// EFI_UNSUPPORTED
		break;
	}
#endif

  return Data;
}

/**
    And bite then or bite then write to mmio.

    @param Gpe0Type	SB_GPE0_TYPE, like TYPE_HOT_PLUG .. etc.
    @param PinNum - gpio pin

    @retval UINT32 GPE0 bit number

**/
UINT32
AmdFchGpioGetGpe0BitNum (
  IN SB_GPE0_TYPE Gpe0Type,
  IN UINT32 PinNum
  )
{
	UINT32 i;
	UINT32 Gpe0BitNum;

	// Find the GPE0 bit number.
	Gpe0BitNum = -1;

	i = 0;
	do {
	    if (PinNum != -1 && PinNum == AmdSciMapTbl[i].PinNum) {
	        Gpe0BitNum = (AmdFchMmioRead32(AMD_FCH_SMI_MMIO, AmdSciMapTbl[i].Sci.Reg) >> AmdSciMapTbl[i].Sci.BitOffset) & 0x1F;
	        break;
	    }
	    if (Gpe0Type != TYPE_GPE0_AMD_END && Gpe0Type == AmdSciMapTbl[i].Gpe0Type) {
	        Gpe0BitNum = (AmdFchMmioRead32(AMD_FCH_SMI_MMIO, AmdSciMapTbl[i].Sci.Reg) >> AmdSciMapTbl[i].Sci.BitOffset) & 0x1F;
	        break;
	    }
	    i++;
	} while (AmdSciMapTbl[i].Gpe0Type != TYPE_GPE0_AMD_END);
	
	return Gpe0BitNum;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
