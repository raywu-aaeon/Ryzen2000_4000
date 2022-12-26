#ifndef __AAEON_COMMON_LIB__H__
#define __AAEON_COMMON_LIB__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <token.h>
#include <Library/IoLib.h>
#include <Setup.h>
#ifndef PEI_BUILD
  #include <AaeonSetup.h>
#endif //PEI_BUILD

//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/


//****************************************************************************/
//		MACROS DECLARATIONS
//****************************************************************************/
#define  Gpio0x  0
#define  Gpio1x  1
#define  Gpio2x  2
#define  Gpio3x  3
#define  Gpio4x  4
#define  Gpio5x  5
#define  Gpio6x  6
#define  Gpio7x  7
#define  Gpio8x  8
#define  Gpio9x  9
#define  GpioAx  10

#define Output 1
#define Input 0

#define High 1
#define Low 0

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/
#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
#ifndef PEI_BUILD
VOID IT8728FSetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 IT8728FGetGpio(IN UINT8 GpioNum);

VOID IT8728FEnableWdt(UINT8 TimeUnit,UINT8 Time);

VOID IT8728FDisableWdt();

UINT8 IT8728FGetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //IT8728F_SUPPORT

#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
#ifndef PEI_BUILD
VOID IT8625SetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
VOID IT8625SetGpioFnType (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioFnType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 IT8625GetGpio(IN UINT8 GpioNum);

VOID IT8625EnableWdt(UINT8 TimeUnit,UINT8 Time);

VOID IT8625DisableWdt();

UINT8 IT8625GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //IT8625_SUPPORT

#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
#ifndef PEI_BUILD
VOID F81866SetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 F81866GetGpio(IN UINT8 GpioNum);

VOID F81866EnableWdt(IN UINT8 TimeUnit, IN UINT8 Timer);

VOID F81866DisableWdt();

UINT8 F81866GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //F81866_SUPPORT

#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
#ifndef PEI_BUILD
VOID F81966SetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 F81966GetGpio(IN UINT8 GpioNum);

VOID F81966EnableWdt(IN UINT8 TimeUnit, IN UINT8 Timer);

VOID F81966DisableWdt();

UINT8 F81966GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //F81966_SUPPORT

#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
#ifndef PEI_BUILD
VOID F81804SetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 F81804GetGpio(IN UINT8 GpioNum);

VOID F81804EnableWdt(IN UINT8 TimeUnit, IN UINT8 Timer);

VOID F81804DisableWdt();

UINT8 F81804GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //F81804_SUPPORT

#if defined(F75111PeiPkg_SUPPORT) && (F75111PeiPkg_SUPPORT == 1)
#ifndef PEI_BUILD
VOID F75111SetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 F75111GetGpio(IN UINT8 GpioNum);
#endif //F75111PeiPkg_SUPPORT

#if defined(F75113_SUPPORT) && (F75113_SUPPORT == 1)
#ifndef PEI_BUILD
VOID F75113SetGpio (
    IN UINT8    GpioNum,
    IN UINT8    GpioVal,
    IN UINT8    GpioType,
    IN SETUP_DATA   *SetupData
);
#endif //PEI_BUILD

UINT8 F75113GetGpio(IN UINT8 GpioNum);
#endif //F75113_SUPPORT

#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
VOID IT8518EnableWdt(IN UINT8 TimeUnit, IN UINT8 Timer);

VOID IT8518DisableWdt();

UINT8 IT8518GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset);
#endif //IT8518_SUPPORT

#ifndef PEI_BUILD
VOID AaeonSetGpio (
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN UINT8	ChipType,
	IN SETUP_DATA	*SetupData
);
#endif //PEI_BUILD

UINT8 AaeonGetGpio(IN UINT8 ChipType, IN UINT8 GpioNum);

VOID AaeonEnableWatchDog(IN UINT8 ChipType, IN UINT8 TimeUnit, IN UINT8 Timer);

VOID AaeonDisableWatchDog(IN UINT8 ChipType);

UINT8 AaeonGetIoLdnValue (IN UINT8 ChipType, IN UINT8 IOLDN, IN UINT8 RegisterOffset);
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
