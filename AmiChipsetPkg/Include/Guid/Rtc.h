
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

/** @file Rtc.h
    Real Time Clock and CMOS Data bank register definitions.

*/

#ifndef __RTC__H__
#define __RTC__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include "Token.h"

//---------------------------------------------------------------------------
// Define Real Time Clock INDEX and DATA registers
//---------------------------------------------------------------------------
#define RTC_INDEX_REG       0x70
#define RTC_DATA_REG        0x71

//---------------------------------------------------------------------------
// Define Internal Registers for Real Time Clock
//---------------------------------------------------------------------------
#define RTC_SECONDS_REG         0x00    // R/W  Range 0..59
#define RTC_SECONDS_ALARM_REG   0x01    // R/W  Range 0..59
#define RTC_MINUTES_REG         0x02    // R/W  Range 0..59
#define RTC_MINUTES_ALARM_REG   0x03    // R/W  Range 0..59
#define RTC_HOURS_REG           0x04    // R/W  Range 1..12 or 0..23
                                        // Bit 7 is AM/PM
#define RTC_HOURS_ALARM_REG     0x05    // R/W  Range 1..12 or 0..23
                                        // Bit 7 is AM/PM
#define RTC_DAY_OF_WEEK_REG     0x06    // R/W  Range 1..7
#define RTC_DAY_OF_MONTH_REG    0x07    // R/W  Range 1..31
#define RTC_MONTH_REG           0x08    // R/W  Range 1..12
#define RTC_YEAR_REG            0x09    // R/W  Range 0..99
#define RTC_REG_A_INDEX         0x0a    // R/W[0..6]  R0[7]
#define RTC_REG_B_INDEX         0x0b    // R/W
#define RTC_REG_C_INDEX         0x0c    // RO
#define RTC_REG_D_INDEX         0x0d    // RO

#define RTC_NMI_MASK            0x80

extern	EFI_GUID    gEfiTimeVariableGuid;
#if defined CREATE_CMOS_BAD_HOB && CREATE_CMOS_BAD_HOB != 0
extern	EFI_GUID    gAmiCmosBadHobGuid;
#endif

#pragma pack(push,1)

typedef struct {
    INT16 TimeZone;
    UINT8 Daylight;
} TIME_VARIABLE;

//---------------------------------------------------------------------------
// Register A Bit definitions
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_A;
    struct {
        UINT8   RateSel     : 4;
        UINT8   Divisor     : 3;
        UINT8   UpdInProgr  : 1;
    };
} RTC_REG_A;

//---------------------------------------------------------------------------
// Register B Bit definitions
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_B;
    struct {
        UINT8   DaylightSav : 1;    // 0 - Daylight saving disabled
                                    // 1 - Daylight savings enabled 
        UINT8   Mode        : 1;    // 0 - 12 hour mode
                                    // 1 - 24 hour mode 
        UINT8   Format      : 1;    // 0 - BCD Format
                                    // 1 - Binary Format 
        UINT8   SquareWave  : 1;    // 0 - Disable SQWE output
                                    // 1 - Enable SQWE output 
        UINT8   UpdateInt   : 1;    // 0 - Update INT disabled
                                    // 1 - Update INT enabled 
        UINT8   AlarmInt    : 1;    // 0 - Alarm INT disabled
                                    // 1 - Alarm INT Enabled 
        UINT8   PeriodicInt : 1;    // 0 - Periodic INT disabled
                                    // 1 - Periodic INT Enabled 
        UINT8   Set         : 1;    // 0 - Normal operation
                                    // 1 - Updates inhibited 
    };
} RTC_REG_B;

//---------------------------------------------------------------------------
// Register C Bit definitions
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_C;
    struct {
        UINT8 Reserved      : 4;    // Read as zero.  Can not be written.
        UINT8 UpdEndFlag    : 1;    // Update End Interrupt Flag
        UINT8 AlarmFlag     : 1;    // Alarm Interrupt Flag
        UINT8 PeriodicFlag  : 1;    // Periodic Interrupt Flag
        UINT8 IrqFlag       : 1;    // Interrupt Request Flag =
                                    // PF & PIE | AF & AIE | UF & UIE 
    };
} RTC_REG_C;

//---------------------------------------------------------------------------
// Register D Bit definitions
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_D;
    struct {
        UINT8 DateAlarm     : 6;
        UINT8 Reserved      : 1;    // Read as zero.  Can not be written.
        UINT8 DataValid     : 1;    // Valid RAM and Time
    };
} RTC_REG_D;


//---------------------------------------------------------------------------
// Bit definitions for Day Alarm Register (Porting Required if needed)
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_DATE_ALARM;
    struct {
        UINT8 DateAlarm     : 6;
        UINT8 Reserved      : 2;
    };
} RTC_DATE_ALARM_REG;

//---------------------------------------------------------------------------
// Bit definitions for Month Alarm Register (Porting Required if needed)
//---------------------------------------------------------------------------
typedef union {
    UINT8       REG_MONTH_ALARM;
    struct {
        UINT8 MonthAlarm    : 6;
        UINT8 Reserved      : 2;
    };
} RTC_MONTH_ALARM_REG;

#if defined CREATE_CMOS_BAD_HOB && CREATE_CMOS_BAD_HOB != 0
typedef struct {
    EFI_HOB_GUID_TYPE           Header;
    BOOLEAN                     Health;
} CMOS_BAD_HOB;
#endif

#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
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
