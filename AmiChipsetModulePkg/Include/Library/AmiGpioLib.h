//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiGpioLib.h
  This file contains South Bridge(LPC) chipset porting library GPIO 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_GPIO_LIB_H__
#define __AMI_GPIO_LIB_H__

#include <Uefi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  TYPE_HOT_PLUG,
  TYPE_SWGPE,
  TYPE_TCOSCI,
  TYPE_RI,
  TYPE_PCI_EXP,
  TYPE_BATLOW,
  TYPE_PME,
  TYPE_ME_SCI,
  TYPE_PME_B0,
  TYPE_GP27,
  TYPE_WADT,

  // The following is AMD.
  // Reference :
  //	Preliminary Processor Programming Reference (PPR) for AMD Family 17h Model 10h, Revision A0 Processors Volume 3 of 3
  //	55570 Rev 0.39 - Sep 9, 2016
  // Section :
  //    16.2.6 SMI Registers
  //	16.2.17.1 Table 147: IOMUX Function Table
  //    AMD can map 64 event source to GPE0 SCI event.
  TYPE_GPE0_AMD_START,
  TYPE_GPE0_GEVENT0,		TYPE_GPE0_SCIMAP0_GENINT1_L = TYPE_GPE0_GEVENT0,
  TYPE_GPE0_GEVENT1,		TYPE_GPE0_SCIMAP1_GENINT2_L = TYPE_GPE0_GEVENT1,
  TYPE_GPE0_GEVENT2,		TYPE_GPE0_SCIMAP2_AGPIO3 = TYPE_GPE0_GEVENT2,
  TYPE_GPE0_GEVENT3,		TYPE_GPE0_SCIMAP3_LPC_PME_L = TYPE_GPE0_GEVENT3,
  TYPE_GPE0_GEVENT4,		TYPE_GPE0_SCIMAP4_AGPIO4 = TYPE_GPE0_GEVENT4,
  TYPE_GPE0_GEVENT5,		TYPE_GPE0_SCIMAP5_LPC_PD_L = TYPE_GPE0_GEVENT5,
  TYPE_GPE0_GEVENT6,		TYPE_GPE0_SCIMAP6_SPKR = TYPE_GPE0_GEVENT6,
  TYPE_GPE0_GEVENT7,		TYPE_GPE0_SCIMAP7_AGPIO5 = TYPE_GPE0_GEVENT7,
  TYPE_GPE0_GEVENT8,		TYPE_GPE0_SCIMAP8_WAKE_L = TYPE_GPE0_GEVENT8,
  TYPE_GPE0_GEVENT9,		TYPE_GPE0_SCIMAP9_LPC_SMI_L = TYPE_GPE0_GEVENT9,
  TYPE_GPE0_GEVENT10,		TYPE_GPE0_SCIMAP10_AGPIO6 = TYPE_GPE0_GEVENT10,
  TYPE_GPE0_GEVENT11,		TYPE_GPE0_SCIMAP11_AGPIO76 = TYPE_GPE0_GEVENT11,
  TYPE_GPE0_GEVENT12,		TYPE_GPE0_SCIMAP12_USB_OC0_L = TYPE_GPE0_GEVENT12,
  TYPE_GPE0_GEVENT13,		TYPE_GPE0_SCIMAP13_USB_OC1_L = TYPE_GPE0_GEVENT13,
  TYPE_GPE0_GEVENT14,		TYPE_GPE0_SCIMAP14_USB_OC2_L = TYPE_GPE0_GEVENT14,
  TYPE_GPE0_GEVENT15,		TYPE_GPE0_SCIMAP15_USB_OC3_L = TYPE_GPE0_GEVENT15,
  TYPE_GPE0_GEVENT16,		TYPE_GPE0_SCIMAP16_AGPIO23 = TYPE_GPE0_GEVENT16,
  TYPE_GPE0_GEVENT17,		TYPE_GPE0_SCIMAP17_ESPI_RESET_L = TYPE_GPE0_GEVENT17,
  TYPE_GPE0_GEVENT18,		TYPE_GPE0_SCIMAP18_FANIN0 = TYPE_GPE0_GEVENT18,
  TYPE_GPE0_GEVENT19,		TYPE_GPE0_SCIMAP19_SYS_RESET_L = TYPE_GPE0_GEVENT19,
  TYPE_GPE0_GEVENT20,		TYPE_GPE0_SCIMAP20_AGPIO40 = TYPE_GPE0_GEVENT20,
  TYPE_GPE0_GEVENT21,		TYPE_GPE0_SCIMAP21_PWR_BTN_L = TYPE_GPE0_GEVENT21,
  TYPE_GPE0_GEVENT22,		TYPE_GPE0_SCIMAP22_AGPIO9 = TYPE_GPE0_GEVENT22,
  TYPE_GPE0_GEVENT23,		TYPE_GPE0_SCIMAP23_AGPIO8 = TYPE_GPE0_GEVENT23,

  TYPE_GPE0_eSPI,           TYPE_GPE0_SCIMAP26_ESPI = TYPE_GPE0_eSPI,
  TYPE_GPE0_eSPI_WAKE_PME,  TYPE_GPE0_SCIMAP27_ESPI_WAKE_PME = TYPE_GPE0_eSPI_WAKE_PME,
  TYPE_GPE0_NB_GPP_PME,     TYPE_GPE0_SCIMAP29_NB_GPP_PME = TYPE_GPE0_NB_GPP_PME,
  TYPE_GPE0_NB_GPP_HOTPLUG, TYPE_GPE0_SCIMAP30_NB_GPP_HOT_PLUG = TYPE_GPE0_NB_GPP_HOTPLUG,
  TYPE_GPE0_FAKE_STS0,      TYPE_GPE0_SCIMAP33_FAKESTS0 = TYPE_GPE0_FAKE_STS0,
  TYPE_GPE0_FAKE_STS1,      TYPE_GPE0_SCIMAP34_FAKESTS1 = TYPE_GPE0_FAKE_STS1,
  TYPE_GPE0_PM_FAKE_STS2,   TYPE_GPE0_SCIMAP35_FAKESTS2 = TYPE_GPE0_PM_FAKE_STS2,
  TYPE_GPE0_SATA0_PME,      TYPE_GPE0_SCIMAP37_SATA0_PME = TYPE_GPE0_SATA0_PME,
  TYPE_GPE0_SATA1_PME,      TYPE_GPE0_SCIMAP38_SATA1_PME = TYPE_GPE0_SATA1_PME,
  TYPE_GPE0_AZALIA_PME,     TYPE_GPE0_SCIMAP39_AZALIA_PME = TYPE_GPE0_AZALIA_PME,
  TYPE_GPE0_GPIO_INT,       TYPE_GPE0_SCIMAP41_GPIO_INTERRUPT = TYPE_GPE0_GPIO_INT,
  TYPE_GPE0_ALT_HPET,       TYPE_GPE0_SCIMAP43_ALTHPET_TIMER = TYPE_GPE0_ALT_HPET,
  TYPE_GPE0_FAN_THERMAL,    TYPE_GPE0_SCIMAP44_FAN_THERMAL = TYPE_GPE0_FAN_THERMAL,
  TYPE_GPE0_ASF_MASTER_AND_SLAVE,       TYPE_GPE0_SCIMAP45_ASF_MASTER_AND_SLAVE_INTERRUPT = TYPE_GPE0_ASF_MASTER_AND_SLAVE,
  TYPE_GPE0_I2S_WAKW_EVENT, TYPE_GPE0_SCIMAP46_I2S_WAKE = TYPE_GPE0_I2S_WAKW_EVENT,
  TYPE_GPE0_SMBUS0,         TYPE_GPE0_SCIMAP47_SMBUS0_INTERRUPT = TYPE_GPE0_SMBUS0,
  TYPE_GPE0_TWARN_PIN,      TYPE_GPE0_SCIMAP48_TWARN_PIN = TYPE_GPE0_TWARN_PIN,
  TYPE_GPE0_INTERNAL_TRAFFIC_MONITOR,   TYPE_GPE0_SCIMAP49_INTERNAL_TRAFFIC_MONITOR = TYPE_GPE0_INTERNAL_TRAFFIC_MONITOR,
  TYPE_GPE0_PWRBTN,         TYPE_GPE0_SCIMAP51_POWER_BUTTON = TYPE_GPE0_PWRBTN,
  TYPE_GPE0_PROHOT_PIN,     TYPE_GPE0_SCIMAP52_PROHOT_PIN = TYPE_GPE0_PROHOT_PIN,
  TYPE_GPE0_HW_ASSERTION_MESSAGE,       TYPE_GPE0_SCIMAP53_HW_ASSERTION_MESSAGE = TYPE_GPE0_HW_ASSERTION_MESSAGE,
  TYPE_GPE0_SCI_ASSERTION_MESSAGE,      TYPE_GPE0_SCIMAP54_SCI_ASSERTION_MESSAGE = TYPE_GPE0_SCI_ASSERTION_MESSAGE,
  TYPE_GPE0_RAS_EVENT,      TYPE_GPE0_SCIMAP55_RAS_EVENT = TYPE_GPE0_RAS_EVENT,
  TYPE_GPE0_XHC_WAKE_EVENT, TYPE_GPE0_SCIMAP57_XHC_WAKE = TYPE_GPE0_XHC_WAKE_EVENT,
  TYPE_GPE0_AC_DC_TIMER_EVENT,          TYPE_GPE0_SCIMAP58_ACDC_TIMEREVENT = TYPE_GPE0_AC_DC_TIMER_EVENT,

  TYPE_GPE0_AMD_END,
  TYPE_SB_GPE0_MAX
} SB_GPE0_TYPE;

typedef enum {
  GPE0_EN_OP_SAVE,
  GPE0_EN_OP_RESTORE,
  GPE0_EN_OP_CLEAR_ALL
} GPE0_EN_OP;

typedef enum {
  PCONF0,
  PCONF1,
  PADVAL,
  // The following is AMD only.
  //    Porting required for AMD : Don't touch above. Just append list below.
  AMD_GPIO,
  AMD_IOMUX
} GPIO_REG_TYPE;

typedef enum {
  GPIO_NC,
  GPIO_SC,
  GPIO_SUS,
  GPIO_Normal,
  // The following is AMD only.
  //    Porting required for AMD : Don't touch above. Just append list below.
  GPIO_AMD_GEVENT
} AMI_GPIO_GROUP_TYPE;

typedef struct _AMI_OEM_GPIO {
  AMI_GPIO_GROUP_TYPE   Group;
  UINT8                 PinNum;
} AMI_OEM_GPIO;


BOOLEAN SbGetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
);

VOID SbSetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
);

VOID SbResetGpe0En (
    IN SB_GPE0_TYPE Gpe0Type
);

VOID SbGpe0Operation (
    IN GPE0_EN_OP   Operation
);

BOOLEAN SbGetGpe0Sts (
    IN SB_GPE0_TYPE Gpe0Type
);

VOID SbClearGpe0Sts (
    IN SB_GPE0_TYPE Gpe0Type
);

VOID SbSetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
);

BOOLEAN SbGetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
);

VOID SbResetGpe0GpinEn (
    IN AMI_OEM_GPIO Gpio
);

BOOLEAN SbGetGpe0GpinSts (
    IN AMI_OEM_GPIO Gpio
);

VOID SbClearGpe0GpinSts (
    IN AMI_OEM_GPIO Gpio
);

BOOLEAN SbGetGpioUseSel (
    IN AMI_OEM_GPIO Gpio
);

VOID SbProgGpioUseSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      GpioMode,
    IN UINT8        MulFunc
);

BOOLEAN SbGetGpioIoSel (
    IN AMI_OEM_GPIO Gpio
);

VOID SbSetGpioIoSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      InputMode
);

BOOLEAN SbGetGpioLvlSel (
    IN AMI_OEM_GPIO Gpio
);

VOID SbSetGpioLvlSel (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      High
);

UINT32 SbReadAltGpiSmiSts (
    IN AMI_OEM_GPIO Gpio
);

VOID SbClearAltGpiSmiSts (
    IN AMI_OEM_GPIO Gpio
);

VOID SbProgramAltGpiSmi (
    IN AMI_OEM_GPIO Gpio,
    IN BOOLEAN      Set
);

VOID SbProgramGpioRout (
    IN AMI_OEM_GPIO Gpio,
    IN UINT8        Mode
);

VOID SbProgramGpioRegister (
    IN AMI_OEM_GPIO   Gpio,
    IN GPIO_REG_TYPE  RegType,
    IN UINT32         AndData,
    IN UINT32         OrData
);

UINT32 SbReadGpioRegister (
    IN AMI_OEM_GPIO   Gpio,
    IN GPIO_REG_TYPE  RegType
);

#ifdef __cplusplus
}
#endif
#endif


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
