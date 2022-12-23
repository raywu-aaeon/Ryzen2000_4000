/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */
 
 DefinitionBlock (
  "AdaptiveS4.aml",                                               // Output file
  "SSDT",                                                         // Signature
  0x01,                                                           // SSDT Revision
  "AMD",                                                          // OEM ID
  "CPMADPS4",                                                     // OEM Table ID
  0x1                                                             // OEM Revision
  )
{
  #define CPM_ADAPTIVE_S4_ASL

  #include "CmnDef.asi"
  #include "CmnExt.asi"

  Device(AS34)
  {
//    Name(_HID, "ASD0001")
    Method(_HID, 0)
    {
        If (LGreaterEqual (CpmSbChipId, CPM_FCH_REVISION_ID_ZP))
        {
            Return("AMDI0050")
        }
        Else
        {
            Return("ASD0001")
        }
    }

    Method(_STA, 0)
    {
        If (CpmIsWin8())
        {
            Return(0xF)
        }
        Else
        {
            Return(0x0)
        }
    }

    Name (CpmAdaptiveS4InitFlag, 1)
    Name (CpmAdaptiveTimers, Buffer(8){0,0,0,0,0,0,0,0})

    // Currrent time, in binary
    Name(CpmS4TimerCurrentMinute, 0)
    Name(CpmS4TimerCurrentHour, 0)
    Name(CpmS4TimerCurrentDay, 0)
    Name(CpmS4TimerCurrentMonth, 0)
    Name(CpmS4TimerCurrentYear, 0)

    // Target _S4 time, in binary
    Name(CpmS4TimerTargetMinute, 0)
    Name(CpmS4TimerTargetHour, 0)
    Name(CpmS4TimerTargetDay, 0)
    Name(CpmS4TimerTargetMonth, 0)
    Name(CpmS4TimerTargetYear, 0)

    // Parameter buffer for Method(CpmGetAbsoluteTime, 1)
    Name(CpmS4TimerBufferMinute, 0)
    Name(CpmS4TimerBufferHour, 0)
    Name(CpmS4TimerBufferDay, 0)
    Name(CpmS4TimerBufferMonth, 0)
    Name(CpmS4TimerBufferYear, 0)

    //  Arg0: Year
    //  Arg1: Month
    Method(CpmGetDayofMonth, 2)
    {
      Store(31, Local0)
      If (LEqual (Match(Package () {4, 6, 9, 11}, MEQ, Arg1, MTR, 0, 0), Ones)) {
        Store(30, Local0)
      }
      If (LEqual (Match(Package () {2}, MEQ, Arg1, MTR, 0, 0), Ones)) {
        If (Mod(Arg0, 4)) {
          Store(28, Local0)
        } Else {
          Store(29, Local0)
        }
      }
      Return (Local0)
    }

    Method(CpmGetAbsoluteTime, 1)
    {
      // Caculate relative Input to Abs Minute
      Add(Arg0, CpmS4TimerCurrentMinute, Local0)
      Divide(Local0, 60, CpmS4TimerBufferMinute, Local0)

      // Caculate relative Input to Abs Hour
      Add(Local0, CpmS4TimerCurrentHour, Local0)
      Divide(Local0, 24, CpmS4TimerBufferHour, Local0)

      // Caculate relative Input to Abs Day
      Add(Local0, CpmS4TimerCurrentDay, Local0)
      Store(Zero, Local1)
      While (LGreater(Local0, CpmGetDayofMonth(CpmS4TimerCurrentYear, CpmS4TimerCurrentMonth))) {
        Subtract(Local0, CpmGetDayofMonth(CpmS4TimerCurrentYear, CpmS4TimerCurrentMonth), Local0)
        Increment(Local1)
      }
      Store(Local0, CpmS4TimerBufferDay)
      Store(Local1, Local0)

      // Caculate relative Input to Abs CpmS4TimerTargetMonth
      Add(Local0, CpmS4TimerCurrentMonth, Local0)
      Store(Zero, Local1)
      While (LGreater(Local0, 12)) {
        Subtract(Local0, 12, Local0)
        Increment(Local1)
      }
      Store(Local0, CpmS4TimerBufferMonth)

      // Caculate relative Input to Abs Year
      Add(Local1, CpmS4TimerCurrentYear, CpmS4TimerBufferYear)
    }

    Method(CpmGetRelativeTime, 5)
    {
      Store(Zero, Local7)
      Store(Zero, Local2)

      // Check Abs Input of CpmS4TimerTargetMonth
      If (Lor(LGreater(Arg3, 12), LLessEqual(Arg3, 0))) {
        Store(0x10000, Local7)  // Error
      }
      // Check Abs Input of Day
      If (LOr(LGreater(Arg2, CpmGetDayofMonth(Arg4, Arg3)), LLessEqual(Arg2, 0))) {
        Store(0x10000, Local7)  // Error
      }
      // Check Abs Input of Hour
      If (LGreaterEqual(Arg1, 24)) {
        Store(0x10000, Local7)  // Error
      }
      // Check Abs Input of Minute
      If (LGreaterEqual(Arg0, 60)) {
        Store(0x10000, Local7)  // Error
      }

      // Get RTC
      // Delta the abs Minute field with current Minute, and accumulate
      Store(CpmS4TimerCurrentMinute, Local0)
      Store(Arg0, Local1)
      If (LLess(Local1, Local0)) {
        Add(Local1, 60, Local1)
        Increment(Local2)
      }
      Add(Subtract(Local1, Local0), Local7, Local7)

      // Delta the abs Hour field with current Hour, and accumulate
      Store(CpmS4TimerCurrentHour, Local0)
      Store(Arg1, Local1)
      If (Local2) {
        Store(Zero, Local2)
        If (LEqual(Local1, 0)) {
          Add(Local1, 24, Local1)
          Increment(Local2)
        }
        Decrement(Local1)
      }
      If (LLess(Local1, Local0)) {
        Add(Local1, 24, Local1)
        Increment(Local2)
      }
      Add(Multiply(Subtract(Local1, Local0), 60), Local7, Local7)

      // Delta the abs Day field with current Day, and accumulate
      Store(CpmS4TimerCurrentDay, Local0)
      Store(Arg2, Local1)
      If (Local2) {
        Store(Zero, Local2)
        If (LLessEqual(Local1, 1)) {
          Add(Local1, CpmGetDayofMonth(CpmS4TimerCurrentYear, CpmS4TimerCurrentMonth), Local1)
          Increment(Local2)
        }
        Decrement(Local1)
      }
      If (LLess(Local1, Local0)) {
        Add(Local1, CpmGetDayofMonth(CpmS4TimerCurrentYear, CpmS4TimerCurrentMonth), Local1)
        Increment(Local2)
      }
      Add(Multiply(Subtract(Local1, Local0), 1440), Local7, Local7)     // 1*60*24 = 1440

      // Delta the abs CpmS4TimerTargetMonthh field with current CpmS4TimerTargetMonthh, and accumulate
      Store(CpmS4TimerCurrentMonth, Local0)
      Store(Arg3, Local1)
      If (Local2) {
        Store(Zero, Local2)
        If (LLessEqual(Local1, 1)) {
          Add(Local1, 12, Local1)
          Increment(Local2)
        }
        Increment(Local0)
      }
      If (LLess(Local1, Local0)) {
        Add(Local1, 12, Local1)
        Increment(Local2)
      }
      While (LGreater(Local1, Local0)) {
        Add(Local7, Multiply(CpmGetDayofMonth(CpmS4TimerCurrentYear, Local0), 1440), Local7)    // 60*24 = 1440
        Increment(Local0)
      }

      // Delta the abs CpmS4TimerTargetMonthh field with current CpmS4TimerTargetMonthh, and accumulate
      Store(CpmS4TimerCurrentYear, Local0)
      Store(Arg4, Local1)
      If (Local2) {
        Store(0, Local2)
        If (LLessEqual(Local1, 0)) {
          Store(1, Local2)
        }
        Decrement(Local1)
      }
      If (Lor(LNotEqual(Local1, Local0), Local2)) {
        Store(0x10000, Local7)
      }
      Return (Local7)
    }

    Method(ASCM, 2)
    {
      Store(CpmReadTable(CpmAdaptiveS4Table, CpmAdaptiveS4EcRamOffset), Local6)
      If (LEqual (CpmReadTable(CpmMainTable, CpmAdaptiveS4En), 1)) {
        If (CpmAdaptiveS4InitFlag) {
          Store(Zero, CpmAdaptiveS4InitFlag)
          CpmKbcWrite8 (Add (Local6, 0x04), 0x00)
        }
      }

      CreateField(CpmAdaptiveTimers, 32, 6, MIN4)   // S4Timer[Minute]
      CreateField(CpmAdaptiveTimers, 38, 5, HOR4)   // S4Timer[Hour]
      CreateField(CpmAdaptiveTimers, 43, 5, DAY4)   // S4Timer[Day of CpmS4TimerTargetMonthh]
      CreateField(CpmAdaptiveTimers, 48, 4, MON4)   // S4Timer[CpmS4TimerTargetMonthh]
      CreateField(CpmAdaptiveTimers, 52, 7, YER4)   // S4Timer[Year]
      CreateField(CpmAdaptiveTimers, 32,20, RMI4)   // S4TimerRelative[Minute] if [REL4]
      CreateBitField(CpmAdaptiveTimers, 59, REL4)   // S4TimerIsRelative
      CreateBitField(CpmAdaptiveTimers, 61, ERR4)   // WakeFromS4TimerFormatError
      CreateBitField(CpmAdaptiveTimers, 62, EXP4)   // WakeFromS4TimerExpired
      CreateBitField(CpmAdaptiveTimers, 63, ENA4)   // WakeFromS4TimerEnable

      Store(0, Local7)

      If (LEqual(Arg0, 0)) {
        Store(FromBCD(CpmReadRtc(0x09)), CpmS4TimerCurrentYear)
        Store(FromBCD(CpmReadRtc(0x08)), CpmS4TimerCurrentMonth)
        Store(FromBCD(CpmReadRtc(0x07)), CpmS4TimerCurrentDay)
        Store(FromBCD(CpmReadRtc(0x04)), CpmS4TimerCurrentHour)
        Store(FromBCD(CpmReadRtc(0x02)), CpmS4TimerCurrentMinute)
        Store(Arg1, CpmAdaptiveTimers)

        If(ENA4) {
          If(REL4) {
            Store(ToInteger(RMI4), Local7)  // timer value
            CpmGetAbsoluteTime(Local7)
            Store(CpmS4TimerBufferMinute, CpmS4TimerTargetMinute)
            Store(CpmS4TimerBufferHour, CpmS4TimerTargetHour)
            Store(CpmS4TimerBufferDay, CpmS4TimerTargetDay)
            Store(CpmS4TimerBufferMonth, CpmS4TimerTargetMonth)
            Store(CpmS4TimerBufferYear, CpmS4TimerTargetYear)
          } Else {
            Store(ToInteger(MIN4), CpmS4TimerTargetMinute)
            Store(ToInteger(HOR4), CpmS4TimerTargetHour)
            Store(ToInteger(DAY4), CpmS4TimerTargetDay)
            Store(ToInteger(MON4), CpmS4TimerTargetMonth)
            Store(ToInteger(YER4), CpmS4TimerTargetYear)
            Store(CpmGetRelativeTime(CpmS4TimerTargetMinute, CpmS4TimerTargetHour, CpmS4TimerTargetDay, CpmS4TimerTargetMonth, CpmS4TimerTargetYear), Local7)
          }
        }

        If (LEqual (CpmReadTable(CpmMainTable, CpmAdaptiveS4En), 1)) {
          If (LAnd(ENA4, LAnd(LGreaterEqual(0xFFFF, Local7), LGreaterEqual(Local7, 1)))) {
            CpmKbcWrite8 (Add (Local6, 0x00), And (Local7, 0xFF))
            CpmKbcWrite8 (Add (Local6, 0x01), And (ShiftRight(Local7, 8), 0xFF))
            Store(Zero, ERR4)
          } Else {
            CpmKbcWrite8 (Add (Local6, 0x00), 0x00)
            CpmKbcWrite8 (Add (Local6, 0x01), 0x00)
            Store(One, ERR4)
          }
        }

        If (LEqual (CpmReadTable(CpmMainTable, CpmAdaptiveS4En), 2)) {
          Add (Multiply (CpmReadTable(CpmAdaptiveS4Table, CpmAdaptiveS4BufferType), 0x100), CpmReadTable(CpmAdaptiveS4Table, CpmAdaptiveS4BufferOffset), Local0)

          If (LAnd(ENA4, LAnd(LGreaterEqual(0xFFFF, Local7), LGreaterEqual(Local7, 1)))) {
            Store(One, Local1)
            Store(ToBCD(CpmS4TimerTargetMinute), Local2)
            Store(ToBCD(CpmS4TimerTargetHour), Local3)
            Store(ToBCD(CpmS4TimerTargetDay), Local4)
            Store(Zero, ERR4)
          } Else {
            Store(Zero, Local1)
            Store(Zero, Local2)
            Store(Zero, Local3)
            Store(Zero, Local4)
            Store(One, ERR4) 
          }
          Store(CpmReadAcpiMmio (Add (Local0, 0x08)), Local5)
          Or (And (Local5, 0xFE), Local1, Local1)
          CpmWriteAcpiMmio (Add (Local0, 0x08), Local1)
          CpmWriteAcpiMmio (Add (Local0, 0x09), Local2)
          CpmWriteAcpiMmio (Add (Local0, 0x0A), Local3)
          CpmWriteAcpiMmio (Add (Local0, 0x0B), Local4)

          If (And (CpmReadAcpiMmio (Add (Local0, 0x08)), 0x01)) {
            CpmWriteAcpiMmio (Add (Local0, 0x00), 0x34)   // '4'
            CpmWriteAcpiMmio (Add (Local0, 0x01), 0x33)   // '3'
            CpmWriteAcpiMmio (Add (Local0, 0x02), 0x53)   // 'S'
            CpmWriteAcpiMmio (Add (Local0, 0x03), 0x41)   // 'A'
          } Else {
            CpmWriteAcpiMmio (Add (Local0, 0x00), 0x00)
            CpmWriteAcpiMmio (Add (Local0, 0x01), 0x00)
            CpmWriteAcpiMmio (Add (Local0, 0x02), 0x00)
            CpmWriteAcpiMmio (Add (Local0, 0x03), 0x00)
          }
        }
      }
      If (LEqual(Arg0, 1)) {
        If (LEqual (CpmReadTable(CpmMainTable, CpmAdaptiveS4En), 2)) {
          Add (Multiply (CpmReadTable(CpmAdaptiveS4Table, CpmAdaptiveS4BufferType), 0x100), CpmReadTable(CpmAdaptiveS4Table, CpmAdaptiveS4BufferOffset), Local0)
          If (LAnd(LEqual(CpmReadAcpiMmio(Add(Local0, 0x03)), 0x41), LAnd(LEqual(CpmReadAcpiMmio(Add(Local0, 0x02)), 0x53), LEqual(CpmReadAcpiMmio(Add(Local0, 0x01)), 0x33)))) {
            And (CpmReadAcpiMmio (Add (Local0, 0x08)), 0x02, Local0)
            ShiftRight (Local0, 1, EXP4)
          } Else {
            Store(Zero, EXP4)
          }
        }
        If (LEqual (CpmReadTable(CpmMainTable, CpmAdaptiveS4En), 1)) {
          Store(CpmKbcRead8 (Add (Local6, 0x04)), Local0)
          And (Local0, 0x01, EXP4)
        }
      }
      Return (CpmAdaptiveTimers)
    }
  }
}
