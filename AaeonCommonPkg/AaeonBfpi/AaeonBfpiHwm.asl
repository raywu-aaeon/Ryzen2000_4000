#if ASL_WMI_HWM_SUPPORT
  Scope(\_SB.BFPI) {
    //---------------------------------------------------------------------------
    // Name: HWMO
    //
    // Description:  HWM Operation
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
    Method (HWMO, 3){
      If (LEqual(Arg0, 0x0000)) {  // Report capability
        Return(HMRC(Arg1, Arg2))
      }
      If (LEqual(Arg0, 0x0001)) {  // Read sensor
        Return(HMRS(Arg1, Arg2))
      }
      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: HMRC
    //
    // Description:  HWM report capability
    //   Arg0 : IIA0, Select capability data to return
    //   Arg1 : IIA1, Basically not used.
    //
    // Output:
    //   According to sub-function.
    //
    //---------------------------------------------------------------------------
    Method (HMRC, 2){
      And (Arg0, 0xFF, Local0) // Input: Interger - Select capability data to return

      If (LEqual(Local0, 0x00)) {
        // Report general capability in JSON format
        Store (0, Local1)
        Store ("{\"Name\":\"HWM\",\"Instance Number\":", Local2)
        Store ("", local3)
        Store (One, local4)

        // Check sensor data
        If (LNotEqual(HMSN(0), 0)) {  // Temperature sensor present?
          Increment (Local1)
          If (LEqual(Local4, ZERO)) { Concatenate (Local3, ",", Local3) } Else { Decrement(Local4) }  // Start to append comma from secondary.
          Concatenate (Local3, "\"Temperature\"", Local3)
        }
        If (LNotEqual(HMSN(1), 0)) {  // FAN sensor present?
          Increment (Local1)
          If (LEqual(Local4, ZERO)) { Concatenate (Local3, ",", Local3) } Else { Decrement(Local4) }  // Start to append comma from secondary.
          Concatenate (Local3, "\"FAN\"", Local3)
        }
        If (LNotEqual(HMSN(2), 0)) {  // Voltage sensor present?
          Increment (Local1)
          If (LEqual(Local4, ZERO)) { Concatenate (Local3, ",", Local3) } Else { Decrement(Local4) }  // Start to append comma from secondary.
          Concatenate (Local3, "\"Voltage\"", Local3)
        }
        If (LEqual(Local1, 0)) { Return (ASL_BFPI_NOT_SUPPORTED) } // Should never happen.

        // Generate string and put to data buffer
        Concatenate (Local2, Local1, Local2)
        Concatenate (Local2, ",\"Instance Data\":[", Local2)
        Concatenate (Local2, Local3, Local2)
        Concatenate (Local2, "]}", Local2)
        Store (Local2, \_SB.BFPI.WDBF)

        Return (ASL_BFPI_SUCCESS)
      }
      ElseIf (LEqual(Local0, 0x02)) {
        // Supported Temperature sensor number & capability
        HMSC(0)
        Return (HMSN(0))
      }
      ElseIf (LEqual(Local0, 0x03)) {
        // Supported FAN sensor number & capability
        HMSC(1)
        Return (HMSN(1))
      }
      ElseIf (LEqual(Local0, 0x04)) {
        // Supported Voltage sensor number & capability
        HMSC(2)
        Return (HMSN(2))
      }
      ElseIf (LEqual(Local0, 0x12)) {
        // Supported standard Temperature sensor Bitmap
        Return (HMSM(0))
      }
      ElseIf (LEqual(Local0, 0x13)) {
        // Supported standard FAN sensor Bitmap
        Return (HMSM(1))
      }
      ElseIf (LEqual(Local0, 0x14)) {
        // Supported standard Voltage sensor Bitmap
        Return (HMSM(2))
      }

      Return(ASL_BFPI_INVALID_PARAMETER)
    }

    //---------------------------------------------------------------------------
    // Name: HMSN
    //
    // Description:  HWM report sensor number
    //   Arg0 : Sensor Type
    //     0 : Temperature
    //     1 : Fan
    //     2 : Voltage
    //
    // Output:
    //   Integer - Total senser number for specified sensor type
    //
    //---------------------------------------------------------------------------
    Method (HMSN, 1){
      Store (0, Local0)
      If (LGreater(Arg0, 2)) { Return (ASL_BFPI_INVALID_PARAMETER) }

      // Concatenate all supported sensor name for requested type
#if ASL_HWM_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Add (Local0, ASL_OEM_HWM_SN_METHOD, Local0)
#endif
#if ASL_HWM_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Add (Local0, \_SB.SHSN(Arg0), Local0)
#endif
#if ASL_HWM_TYPE_SIO1_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO1.H1SN(Arg0), Local0)
#endif
#if ASL_HWM_TYPE_SIO2_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO2.H2SN(Arg0), Local0)
#endif
#if ASL_HWM_TYPE_SIO3_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.SIO3.H3SN(Arg0), Local0)
#endif
#if ASL_HWM_TYPE_EC1_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.EC01.E1SN(Arg0), Local0)
#endif
#if ASL_HWM_TYPE_EC2_SUPPORT
      Add (Local0, \_SB.PCI0.LPCB.EC02.E2SN(Arg0), Local0)
#endif

      Return(Local0)
    }

    //---------------------------------------------------------------------------
    // Name: HMSS
    //
    // Description:  HWM report sensor name string
    //   Arg0 : Sensor Type
    //     0 : Temperature
    //     1 : Fan
    //     2 : Voltage
    //   Arg1 : Index of sensor to return name string
    //
    // Output:
    //   String - Name string of specified sensor
    //   "NULL" - if not found
    //
    //---------------------------------------------------------------------------
    Method (HMSS, 2){
      Store (Arg1, Local0)  // Index
      Store (0, Local1)  // Supported number
      Store ("NULL", Local2)  // String to return

#if ASL_HWM_TYPE_OEM_SUPPORT
      // OEM controlling method can be implemented externally in project level.
      Store (ASL_OEM_HWM_SN_METHOD, Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (ASL_OEM_HWM_SS_METHOD, Local2)
      } Else {
        Subtract (Local0, Local1, Local0), Local2)
      }
#endif
#if ASL_HWM_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SHSN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.SHSS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0), Local2)
      }
#endif
#if ASL_HWM_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.H1SN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO1.H1SS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_HWM_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.H2SN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO2.H2SS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_HWM_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.H3SN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.SIO3.H3SS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_HWM_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1SN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.EC01.E1SS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif
#if ASL_HWM_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2SN(Arg0), Local1)
      If (LLessEqual(Local0, Local1)) {
        Store (\_SB.PCI0.LPCB.EC02.E2SS(Arg0, Local0), Local2)
      } Else {
        Subtract (Local0, Local1, Local0)
      }
#endif

      Return (Local2)
    }

    //---------------------------------------------------------------------------
    // Name: HMSL
    //
    // Description:  HWM report sensor name list
    //   Arg0 : Sensor Type
    //     0 : Temperature
    //     1 : Fan
    //     2 : Voltage
    //
    // Output:
    //   String - List of supported sensor name for specified sensor type
    //
    //---------------------------------------------------------------------------
    Method (HMSL, 1){
      Store ("", Local1)
      Store ("", Local2)
      Store (ONE, Local3)

      // Concatenate all supported sensor name for requested type
#if ASL_HWM_TYPE_OEM_SUPPORT
      // OEM SMF controlling method can be implemented externally in project level.
      Store (ASL_OEM_HWM_SL_METHOD, Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_SOC_SUPPORT
      // SoC SMF controlling method should be implemented externally in platform level.
      Store (\_SB.SHSL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.H1SL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.H2SL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.H3SL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.H1SL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif
#if ASL_HWM_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.H2SL(Arg0), Local2)
      If (LEqual(Local3, ZERO)) { Concatenate (Local1, ",", Local1) } Else { Decrement(Local3) }  // Start to append comma from secondary.
      Concatenate (Local1, Local2, Local1)
#endif

      Return(Local1)
    }

    //------------------------------------------------------------------------
    // Table:    TTHM, TFAN, TVOL
    // Description:  Look up table for standard name of sensors
    //-------------------------------------------------------------------------
    Name(TTHM, Package() {
        ASL_STD_TEMP_STRING_LIST
    })

    Name(TFAN, Package() {
        ASL_STD_FAN_STRING_LIST
    })

    Name(TVOL, Package() {
        ASL_STD_VOLT_STRING_LIST
    })

    //---------------------------------------------------------------------------
    // Name: HMSM
    //
    // Description:  HWM report sensor Bitmap
    //   Arg0 : Sensor Type
    //     0 : Temperature
    //     1 : Fan
    //     2 : Voltage
    //
    // Output:
    //   Integer - Bitmap for supported standard sensor of specified type.
    //
    //---------------------------------------------------------------------------
    Method (HMSM, 1){
      If (LGreater(Arg0, 2)) { Return (ASL_BFPI_INVALID_PARAMETER) }

      Store (0, Local0)  // Counter
      Store (0, Local1)  // Return value

      // Prepare capability bitmap
      If (LEqual(Arg0,0)) {  // Supported standard Temperture Sensor
        While (LLess(Local0, SizeOf(TTHM))) {
          If (LNotEqual(AHRS(0, DerefOf(Index(TTHM, Local0))), ASL_BFPI_NOT_SUPPORTED)) {
            Or (Local1, ShiftLeft(0x01, Local0), Local1)
          }
          Increment (Local0)
        }
      }
      ElseIf (LEqual(Arg0,1)) {  // Supported standard FAN Sensor
        While (LLess(Local0, SizeOf(TFAN))) {
          If (LNotEqual(AHRS(1, DerefOf(Index(TFAN, Local0))), ASL_BFPI_NOT_SUPPORTED)) {
            Or (Local1, ShiftLeft(0x01, Local0), Local1)
          }
          Increment (Local0)
        }
      }
      ElseIf (LEqual(Arg0,2)) {  // Supported standard Voltage Sensor
        While (LLess(Local0, SizeOf(TVOL))) {
          If (LNotEqual(AHRS(2, DerefOf(Index(TVOL, Local0))), ASL_BFPI_NOT_SUPPORTED)) {
            Or (Local1, ShiftLeft(0x01, Local0), Local1)
          }
          Increment (Local0)
        }
      } Else { Store (ASL_BFPI_INVALID_PARAMETER, Local1) }

      Return(Local1)
    }

    //---------------------------------------------------------------------------
    // Name: HMSC
    //
    // Description:  HWM report sensor capability
    //   Arg0 : Sensor Type
    //     0 : Temperature
    //     1 : Fan
    //     2 : Voltage
    //
    // Output:
    //   Integer - Bitmap for supported standard sensor of specified type.
    //   Data buffer - Capability data in JSON format for specified type
    //   ASL_BFPI_NOT_SUPPORTED - Requested sensor type is not supported.
    //
    //---------------------------------------------------------------------------
    Method (HMSC, 1){
      If (LGreater(Arg0, 2)) { Return (ASL_BFPI_INVALID_PARAMETER) }

      // Report capability in JSON format to data buffer
      If (LEqual(Arg0,0)) { Store ("Temperature", Local2)}
      ElseIf (LEqual(Arg0,1)) { Store ("FAN", Local2)}
      ElseIf (LEqual(Arg0,2)) { Store ("Voltage", Local2)}

      Store ("{\"Name\":\"", Local3)
      Concatenate (Local3, Local2, Local3)
      Concatenate (Local3, "\",\"Sensor Number\":", Local3)
      Concatenate (Local3, HMSN(Arg0), Local3)
      Concatenate (Local3, ",\"Sensor Data\":[", Local3)
      Concatenate (Local3, HMSL(Arg0), Local3)
      Concatenate (Local3, "]}", Local3)
      Store (Local3, \_SB.BFPI.WDBF)

    }

    //---------------------------------------------------------------------------
    // Name: HMRS
    //
    // Description:  HWM read sensor
    //   Arg0 : IIA0,
    //            [7:4] - Sensor mapping format
    //            [11:8] - Sensor type to read
    //            [15:12] - Sensor index to read
    //   Arg1 : IIA1, Basically not used
    //
    // Output:
    //   Reading value from sensors
    //   ASL_BFPI_INVALID_PARAMETER
    //
    //---------------------------------------------------------------------------
    Method (HMRS, 2){
      ShiftRight (And(Arg0,0xF00), 8, Local0) // [11:8] - Sensor type to read
      If (LGreater(Local0, 2)) { Return (ASL_BFPI_INVALID_PARAMETER) }
      ShiftRight (And(Arg0,0xFFFF), 12, Local1) // [15:12] - Sensor index to read
      ShiftRight (And(Arg0,0xF0), 4, Local3) // [7:4] - Sensor mapping format

      If (LEqual(Local3, 0)){
        Store ("NULL", Local2)  // Sensor name string
        If (LEqual(Local0, 0)) {  // Temperature
          If (LLess(Local1, SizeOf(TTHM))) {
            Store (DerefOf(Index(TTHM, Local1)), Local2)
          }
        }
        ElseIf (LEqual(Local0, 1)) {  // Fan
          If (LLess(Local1, SizeOf(TFAN))) {
            Store (DerefOf(Index(TFAN, Local1)), Local2)
          }
        }
        ElseIf (LEqual(Local0, 2)) {  // Voltage
          If (LLess(Local1, SizeOf(TVOL))) {
            Store (DerefOf(Index(TVOL, Local1)), Local2)
          }
        }
      } Else {
        Store (HMSS(Local0,Local1), Local2)
      }

      If (LEqual(Local2, "NULL")) {
        Store (ToString (WDBF), Local2)
      }
      Return (AHRS(Local0, Local2))
    }

    //---------------------------------------------------------------------------
    // Name: AHRS
    //
    // Description:  AAEON HWM read sensor
    //   Arg0 : Sensor Type
    //   Arg1 : Sensor Name
    //
    // Output:
    //   Reading value from sensors
    //   ASL_BFPI_NOT_SUPPORTED
    //
    //---------------------------------------------------------------------------
    Method (AHRS, 2) {
      Store (ASL_BFPI_NOT_SUPPORTED, Local0)
      #if ASL_HWM_TYPE_OEM_SUPPORT
      // OEM HWM controlling method can be implemented externally in project level.
      Store (ASL_OEM_HWM_RS_METHOD, Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_SOC_SUPPORT
      // SoC HWM controlling method should be implemented externally in platform level.
      Store (\_SB.SHRS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_SIO1_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO1.H1RS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_SIO2_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO2.H2RS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_SIO3_SUPPORT
      Store (\_SB.PCI0.LPCB.SIO3.H3RS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_EC1_SUPPORT
      Store (\_SB.PCI0.LPCB.EC01.E1RS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      #if ASL_HWM_TYPE_EC2_SUPPORT
      Store (\_SB.PCI0.LPCB.EC02.E2RS(Arg0, Arg1), Local0)
      If (LNotEqual(Local0, ASL_BFPI_NOT_SUPPORTED)) { Return (Local0) }
      #endif
      Return (ASL_BFPI_NOT_SUPPORTED)
    }

  }  // Scope(\_SB.BFPI)
#endif