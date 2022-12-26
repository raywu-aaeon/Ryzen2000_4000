#if ASL_WMI_LED_SUPPORT
  Scope(\_SB.BFPI) {
    //---------------------------------------------------------------------------
    // Name: LEDO
    //
    // Description:  LED Operation
    //
    // Input:
    //   Arg0 : Sub-function number
    //   Arg1 : IIA0, Input: IntegerArgument
    //   Arg2 : IIA1, Input: IntegerArgument
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (LEDO, 3){
      If (LEqual(Arg0, 0x0000)) {  // Report capability
        Return(LDRC(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0001)) {  // LED get brightness
        Return(LDGB(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0002)) {  // LED set brightness
        Return(LDSB(Arg1, Arg2))
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //------------------------------------------------------------------------
    // Table:    TLED
    // Description:  LED name string look up table
    //
    //-------------------------------------------------------------------------
    Name (TLED, Package(ASL_LED_NUMBER) {
        ASL_LED_STRING_LIST
    })

    //---------------------------------------------------------------------------
    // Name: LDRC
    //
    // Description:  LED report capability
    //   Arg0 : IIA0, Select capability data to return
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (LDRC, 2){
      And (Arg0, 0xFF, Local0) // Input: Interger - Select capability data to return

      If (LEqual(Local0, 0x00)) {  // Report capability in JSON format
        Store (LEDC, Local0)
        For (Local1 = 0, Local1 < ASL_LED_NUMBER, Local1++)
        {
          Concatenate(Local0, "\"", Local0)
          Concatenate(Local0, DeRefOf(Index(TLED,Local1)), Local0)
          Concatenate(Local0, "\"", Local0)
          If (LLess(Add(Local1,ONE),ASL_LED_NUMBER))
          {
            Concatenate(Local0, ",", Local0)
          }
        }
        Concatenate(Local0, "]}", Local0)
        Store (Local0, WDBF)
        Return (ASL_BFPI_SUCCESS)
      }
      If (LEqual(Local0, 0x10)) {  // Return Supported LED number
        Return (ASL_LED_NUMBER)
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: LDGB
    //
    // Description:  LED get brightness
    //   Arg0 : IIA0, LED number to get.
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   Interger:
    //     0 - Off
    //     1 - On
    //   BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (LDGB, 2){
      If (LGreaterEqual(Arg0, ASL_LED_NUMBER)) {
        Return (ASL_BFPI_INVALID_PARAMETER)
      }
      // Currently support OEM type only
#if ASL_LED_TYPE_OEM_SUPPORT
      Return (ASL_OEM_LED_GB_METHOD)
#endif
    }

    //---------------------------------------------------------------------------
    // Name: LDSB
    //
    // Description:  LED set brightness
    //   Arg1 : IIA0
    //     Bit[7:0] : LED number to set
    //     Bit[16] : LED brightness to set
    //       0 - Off
    //       1 - On
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   BFPI_SUCCESS
    //   BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (LDSB, 2){
      And (Arg0, 0xFF, Local0)  // Bit[7:0] : LED number to set
      And (ShiftRight (Arg0, 16), 0x01, Local1)  //Bit[16] : LED brightness to set
      If (LGreaterEqual(Local0, ASL_LED_NUMBER)) { Return (ASL_BFPI_INVALID_PARAMETER) }
      If (LGreater(Local1, 1)) { Return (ASL_BFPI_INVALID_PARAMETER) }
      // Currently support OEM type only
#if ASL_LED_TYPE_OEM_SUPPORT
      Return (ASL_OEM_LED_SB_METHOD)
#endif
    }

  }  // Scope(\_SB.BFPI)
  #endif