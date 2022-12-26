//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Uefi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include <Setup.h>

#define IsLeap(y)   (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

typedef struct {
  UINT8    AaeonRTCWakeupTimeHour ;
  UINT8    AaeonRTCWakeupTimeMinute ;
  UINT8    AaeonRTCWakeupTimeSecond ;
  UINT8    AaeonRTCWakeupDateDay;
} SMMData ;

SMMData gSmmData ;

//----------------------------------------------------------------------------
// Procedure:   DecToBCD
//
// Description: Converts a Decimal value to a BCD value.
//
// Input:       
//      IN UINT8 Dec - Decimal value
//
// Output:      
//      UINT8 - BCD value
//
// Notes:       
//      Only for 2 digit decimal.
//
//----------------------------------------------------------------------------
UINT8 DecToBCD(UINT8 Dec)
{
    UINT8 FirstDigit = Dec % 10;
    UINT8 SecondDigit = Dec / 10;

    return (SecondDigit << 4) + FirstDigit;
}

//----------------------------------------------------------------------------
// Procedure:   BCDToDec
//
// Description: Converts a BCD value to a Decimal value.
//
// Input:       
//      IN UINT8 BCD -- BCD value
//
// Output:      
//      UINT8 - decimal value
//
// Notes:       
//      Only for 2 digit BCD.
//
//----------------------------------------------------------------------------
UINT8 BCDToDec(UINT8 BCD)
{
    UINT8 FirstDigit = BCD & 0xf;
    UINT8 SecondDigit = BCD >> 4;;
    
    return SecondDigit * 10  + FirstDigit;
}

//----------------------------------------------------------------------------
// Procedure:   ReadRtcIndex
//
// Description: Read the RTC value at the given Index.
//
// Input:       Index       RTC Index
//
// Output:      RTC Value read from the provided Index
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                  Bit 7 is the NMI bit-it should not be changed.
//              2. Output 0x70 with the Index and NMI bit setting.
//              3. Read 0x71 for Data. Getting Dec when appropriate.
//              4. Return the Data.
//----------------------------------------------------------------------------
UINT8 ReadRtcIndex(IN UINT8 Index)
{
    UINT8 volatile Value;

    // Check if Data Time is valid
    if(Index <= 9) do {
    IoWrite8(0x70, 0x0A | 0x80);
    Value = IoRead8(0x71);        
    } while (Value & 0x80); 

    IoWrite8(0x70, Index | 0x80);
    // Read register
    Value = IoRead8(0x71);               
    if (Index <= 9) Value = BCDToDec(Value);    
    return (UINT8)Value;
}

//----------------------------------------------------------------------------
// Procedure:   WriteRtcIndex
//
// Description: Write the RTC value at the given Index.
//
// Input:       Index   RTC Index
//              Data    RTC Index
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Read port 0x70 (RTC Index Register) to get bit 7.
//                 Bit 7 is the NMI bit-it should not be changed.
//              2. Output 0x70 with the Index. Switch to BCD when needed.
//              3. Write the data to 0x71.
//----------------------------------------------------------------------------
void WriteRtcIndex(IN UINT8 Index, IN UINT8 Value)
{
    IoWrite8(0x70,Index | 0x80);
      if (Index <= 9 ) Value = DecToBCD(Value);
    // Write Register
    IoWrite8(0x71,Value);               
}


//----------------------------------------------------------------------------
// Procedure:   SetWakeupTime
//
// Description: Set the alarm time to CMOS location and enable alarm interrupt
//
// Input:       
//      IN EFI_TIME *Time
//
// Output:      
//      VOID
//
//----------------------------------------------------------------------------
void SetWakeupTime (
    IN EFI_TIME     *Time
)
{
    UINT8 Value;

    WriteRtcIndex(5,Time->Hour);
    WriteRtcIndex(3,Time->Minute);
    WriteRtcIndex(1,Time->Second);
    Value = ReadRtcIndex(0x0D) & 0xC0;
    WriteRtcIndex(0x0D,(Value|DecToBCD(Time->Day)));

    //Set Enable
    Value = ReadRtcIndex(0xB);
    Value |= 1 << 5;
    WriteRtcIndex(0xB,Value);
}

//WakeFuntion- set RTC wake parameter
VOID EnableAaeonRTCWake(){
	UINT32 i = 0;
	EFI_TIME Time;
    
	Time.Hour = gSmmData.AaeonRTCWakeupTimeHour;
	Time.Minute = gSmmData.AaeonRTCWakeupTimeMinute;
	Time.Second = gSmmData.AaeonRTCWakeupTimeSecond;
	Time.Day = gSmmData.AaeonRTCWakeupDateDay;

	SetWakeupTime(&Time);            
	//Clear RTC PM1 status
	IoWrite16(PM_BASE_ADDRESS , ( IoRead16(PM_BASE_ADDRESS) | (1 << 10) ));
	//set RTC_EN bit to wake up from the alarm
	IoWrite32(PM_BASE_ADDRESS, ( IoRead32(PM_BASE_ADDRESS) | (1 << 26) ));
}
//----------------------------------------------------------------------------
// Procedure:   SetAaeonRTCWake
//
// Description: Get week dat from date
//
// Input:       
//      IN UINTN Day, IN UINTN Month, IN UINTN Year
//
// Output:      
//      WeekDay
//		(0 to 7 = Sunday to Saturday)
//----------------------------------------------------------------------------	
VOID SetAaeonRTCWake(SETUP_DATA *SetupData){
	gSmmData.AaeonRTCWakeupTimeHour = SetupData->AaeonRTCWakeupTimeHour ;
	gSmmData.AaeonRTCWakeupTimeMinute = SetupData->AaeonRTCWakeupTimeMinute ;
	gSmmData.AaeonRTCWakeupTimeSecond = SetupData->AaeonRTCWakeupTimeSecond ;
	gSmmData.AaeonRTCWakeupDateDay = SetupData->AaeonRTCWakeupTimeDay;
}
//----------------------------------------------------------------------------
// Procedure:   DateGetWeekDay
//
// Description: Get week dat from date
//
// Input:       
//      IN UINT8 Day, IN UINT8 Month, IN UINT16 Year
//
// Output:      
//      WeekDay
//		(0 to 7 = Sunday to Saturday)
//----------------------------------------------------------------------------	
UINT8 DateGetWeekDay(IN UINT8 Day, IN UINT8 Month, IN UINT16 Year)
{
	UINT8 w, d, m, c;
	UINT16 y;	

	d = Day;
	m = Month - 2;
	y = Year;

	if ( m <= 0 )
	{
		m += 12;
		y--;
	}

	c = y / 100;
	y %= 100;

	w = d + y + (5 * c) + ((13 * m - 1) / 5) + (y / 4) + (c / 4);

	return w % 7;
}
//----------------------------------------------------------------------------
// Procedure:   GetDayAfterDayShift
//
// Description: Get target day after DayShift
//
// Input:       
//      IN UINT8 Day, IN UINT8 Month, IN UINT16 Year, IN UINT8 DayShift
//
// Output:      
//      TargetDay
//		(0 to 31)
//----------------------------------------------------------------------------	
UINT8 GetDayAfterDayShift(IN UINT8 Day, IN UINT8 Month, IN UINT16 Year, IN UINT8 DayShift)
{
	UINT8 DaysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	UINT8 TargetDay;

    if (IsLeap(Year)) {
        DaysInMonth[2] = 29;
    } else {
        DaysInMonth[2] = 28;
    }

    TargetDay = Day + DayShift;
    if (TargetDay > DaysInMonth[Month]) {
        TargetDay = TargetDay - DaysInMonth[Month];
    }

	return TargetDay;
}
//----------------------------------------------------------------------------
// Procedure:   CheckRtcWakeToday
//
// Description: Check RTC wake time has passed or not
//
// Input:       
//      IN EFI_TIME CurrentTime, IN SETUP_DATA *SetupData
//
// Output:      
//      BOOLEAN
//		(TRUE: RTC should wake Today / FALSE: RTC wake time has passed)
//----------------------------------------------------------------------------	
BOOLEAN CheckRtcWakeToday(IN EFI_TIME CurrentTime, IN SETUP_DATA *SetupData)
{
	if(CurrentTime.Hour < SetupData->AaeonRTCWakeupTimeHour) {
		return TRUE;
	} else if (CurrentTime.Hour == SetupData->AaeonRTCWakeupTimeHour) {
		if(CurrentTime.Minute < SetupData->AaeonRTCWakeupTimeMinute) {
			return TRUE;
		} else if (CurrentTime.Minute == SetupData->AaeonRTCWakeupTimeMinute) {
			if(CurrentTime.Second < SetupData->AaeonRTCWakeupTimeSecond)
				return TRUE;							
		}
	}

	return FALSE;
}
EFI_STATUS
EFIAPI
AaeonRtcWake_Init (SETUP_DATA *SetupData)
{
	EFI_STATUS 				Status = EFI_SUCCESS;
	UINT8					Value, CurrentWeekday, WakeWeekday, i, NextWakeWeekdayShift, DayShift;
	EFI_TIME				CurrentTime;

  	if(SetupData->AaeonWakeOnRtc == 4){
    	// Bypass: BIOS will not control RTC wake function during system shutdow
  		return Status;
  	}

	//Disable RTC alarm and clear RTC PM1 status
	Value = ReadRtcIndex(0xB);
	Value &= ~((UINT8)1 << 5);
	WriteRtcIndex(0xB,Value);
	//Clear Alarm Flag (AF) by reading RTC Reg C
	Value = ReadRtcIndex(0xC);
	IoWrite16(PM_BASE_ADDRESS , ( IoRead16(PM_BASE_ADDRESS) | (1 << 10) ));

	switch(SetupData->AaeonWakeOnRtc){
		case 0: // RTC wake disabled
			return Status;
		case 1: // RTC wake by dynamic time
			gSmmData.AaeonRTCWakeupTimeHour = ReadRtcIndex(4);
			gSmmData.AaeonRTCWakeupTimeMinute = ReadRtcIndex(2);
			gSmmData.AaeonRTCWakeupTimeSecond = ReadRtcIndex(0);
			gSmmData.AaeonRTCWakeupTimeMinute += SetupData->AaeonRTCWakeupTimeMinuteIncrease;
			if  (gSmmData.AaeonRTCWakeupTimeMinute >= 60)
			{
				gSmmData.AaeonRTCWakeupTimeMinute = 0;
				++gSmmData.AaeonRTCWakeupTimeHour;
				if (gSmmData.AaeonRTCWakeupTimeHour == 24)
					gSmmData.AaeonRTCWakeupTimeHour = 0;
			}	
			break;
		case 2: // RTC wake by Date
			SetAaeonRTCWake(SetupData);
			break;
		case 3: // RTC wake by Weekday
			Status = pRS->GetTime (&CurrentTime, NULL);
			if (EFI_ERROR(Status)) {
			    return Status;
			}
			// Get current weekday
			CurrentWeekday = DateGetWeekDay(CurrentTime.Day, CurrentTime.Month, CurrentTime.Year);
			// Find the next weekday whose RTC wake was enabled
			NextWakeWeekdayShift = 8;
			for (i = 0; i < 7; i++) {	
				if(SetupData->AaeonRTCWakeupTimeWeekday[i]) {
					WakeWeekday = i;
					if(WakeWeekday == CurrentWeekday) {
						if(CheckRtcWakeToday(CurrentTime, SetupData)) { 
							NextWakeWeekdayShift = 0; // Today is WakeWeekday
							break;
						} else {
							WakeWeekday += 7;  // Wake time has passed, shift to next week
						}
					}
					if(WakeWeekday < CurrentWeekday) WakeWeekday += 7; // WakeWeekday has passed, shift to next week
					DayShift = WakeWeekday - CurrentWeekday;
					if(NextWakeWeekdayShift > DayShift) { // Find closest WakeWeekday
						NextWakeWeekdayShift = DayShift;
					}						
				}			
			}
			
			if(NextWakeWeekdayShift == 0) { // Today is WakeWeekday
				SetupData->AaeonRTCWakeupTimeDay = CurrentTime.Day;
				SetAaeonRTCWake(SetupData);
			} 
			if(NextWakeWeekdayShift > 0) { // Today before NextWakeWeekday
				SetupData->AaeonRTCWakeupTimeDay = GetDayAfterDayShift(CurrentTime.Day, CurrentTime.Month, CurrentTime.Year, NextWakeWeekdayShift);
				SetAaeonRTCWake(SetupData);
			}
			if(NextWakeWeekdayShift == 8) return Status; //All AaeonRTCWakeupTimeWeekday was disabled
			break;
	}

	EnableAaeonRTCWake();

	return Status;
}
