Scope(\_SB.BFPI) {

#if ASL_WDT_TYPE_OEM_SUPPORT
//---------------------------------------------------------------------------
// Name: OWRC
//
// Description:  OEM WDT report capability - Max timeout
//
// Output:
//   Interger: Max timeout value in ms
//
//---------------------------------------------------------------------------
    Method (OWRC, 0) {
        Return (ASL_BFPI_NOT_SUPPORTED)  // TODO: Porting required.
    }

//---------------------------------------------------------------------------
// Name: OWGT
//
// Description:  OEM WDT Get timeout
//
// Output:
//   Interger: Remained timeout value in ms
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (OWGT, 0) {
        Return (ASL_BFPI_NOT_SUPPORTED)  // TODO: Porting required.
    }

//---------------------------------------------------------------------------
// Name: OWST
//
// Description:  OEM WDT set watchdog timeout value and start/stop watchdog
//   Arg0 : Timeout value in ms
//            0: stop watchdog
//            other: start watchdog with value as timeout
//
// Output:
//   BFPI_STATUS
//
// Note:
//   1. BIOS should have already configure WDT output during POST.
//      So we just set counter here.
//   2. Follow EAPI specification:
//      If the hardware implementation of
//      the watchdog timer does not allow a setting at the exact time selected, the
//      EAPI selects the next possible longer timing.
//
//---------------------------------------------------------------------------
    Method (OWST, 1){
        // Validate input
        If (LGreater(Arg0, ASL_WDT_MAX_TIMEOUT)) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }

        Return (ASL_BFPI_NOT_SUPPORTED)  // TODO: Porting required.
    }
#endif  // ASL_WDT_TYPE_OEM_SUPPORT

#if ASL_HWM_TYPE_OEM_SUPPORT
//---------------------------------------------------------------------------
// Name: OHSN
//
// Description:  OEM HWM report sensor number
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   Integer - Total senser number for specified sensor type
//
//---------------------------------------------------------------------------
    Method (OHSN, 1){
        Store (0, Local0)
        //If (LEqual(Arg0, 0)) {
        //    // Temperature
        //    Store (ASL_OEM_TEMP_SENSOR_NUMBER, Local0)
        //} ElseIf (LEqual(Arg0, 1)) {
        //    // Fan
        //    Store (ASL_OEM_FAN_SENSOR_NUMBER, Local0)
        //} ElseIf (LEqual(Arg0, 2)) {
        //    // Voltage
        //    Store (ASL_OEM_VOLT_SENSOR_NUMBER, Local0)
        //}
        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    OHTS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
    Name(OHTS, Package() {
        //ASL_OEM_TIN0_STRING,
        //ASL_OEM_TIN1_STRING,
        //ASL_OEM_TIN2_STRING,
    })

//------------------------------------------------------------------------
// Table:    OHFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
    Name(OHFS, Package() {
        //ASL_OEM_FANIN0_STRING,
        //ASL_OEM_FANIN1_STRING,
        //ASL_OEM_FANIN2_STRING,
    })

//------------------------------------------------------------------------
// Table:    OHVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
    Name(OHVS, Package() {
        //ASL_OEM_VIN0_STRING,
        //ASL_OEM_VIN1_STRING,
        //ASL_OEM_VIN2_STRING,
    })

//---------------------------------------------------------------------------
// Name: OHSS
//
// Description:  OEM HWM report sensor name string
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//   Arg1 : Index of sensor to return name string
//
// Output:
//   String - Name string of specified sensor
//   "NULL" if not found
//
//---------------------------------------------------------------------------
    Method (OHSS, 2){
        Store ("NULL", Local0)
        //If (LEqual(Arg0, 0)) {
        //    // Temperature
        //    If (LLess(Arg1, SizeOf(OHTS))) {
        //      Store (DerefOf(Index(OHTS, Arg1)), Local0)
        //    }
        //} ElseIf (LEqual(Arg0, 1)) {
        //    // Fan
        //    If (LLess(Arg1, SizeOf(OHFS))) {
        //      Store (DerefOf(Index(OHFS, Arg1)), Local0)
        //    }
        //} ElseIf (LEqual(Arg0, 2)) {
        //    // Voltage
        //    If (LLess(Arg1, SizeOf(OHVS))) {
        //      Store (DerefOf(Index(OHVS, Arg1)), Local0)
        //    }
        //}
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: OHSL
//
// Description:  OEM HWM report sensor name list
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   String - List of supported sensor name for specified sensor type
//
//---------------------------------------------------------------------------
    Method (OHSL, 1){
        Store ("", Local0)    // String to return
        //Store (ONE, Local1)    // Flag to append comma to string
        //Store (0, Local2)    // Sensor number
        //Store (0, Local3)    // Counter

        //If (LEqual(Arg0, 0)) {
        //    // Temperature
        //    Store (ASL_OEM_TEMP_SENSOR_NUMBER, Local2)    // Sensor number
        //} ElseIf (LEqual(Arg0, 1)) {
        //    // Fan
        //    Store (ASL_OEM_FAN_SENSOR_NUMBER, Local2)    // Sensor number
        //} ElseIf (LEqual(Arg0, 2)) {
        //    // Voltage
        //    Store (ASL_OEM_VOLT_SENSOR_NUMBER, Local2)    // Sensor number
        //}
        //While (LLess(Local3, Local2)) {
        //    If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        //    Concatenate (Local0, Concatenate ("\"", Concatenate (OHSS(Arg0, Local3), "\"", ), ), Local0)
        //    Increment (Local3)
        //}
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: OHRS
//
// Description:  OEM HWM read sensor
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//   Arg1 : Sensor Name
//
// Output:
//   Sensor reading accoring to Arg0
//     Temperature in mini-degree-C
//     Fan in RPM
//     Voltage in mini-volt
//
//---------------------------------------------------------------------------
    Method (OHRS, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            //If (LEqual(Arg1, "Name for sensor 1")) {  // Name match for OEM Temperature sensor 1
            //    ...
            //}
            //ElseIf (LEqual(Arg1, "Name for sensor 2")) {  // Name match for OEM Temperature sensor 2
            //    ...
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            //If (LEqual(Arg1, "Name for sensor 1")) {  // Name match for OEM FAN sensor 1
            //    ...
            //}
            //ElseIf ...
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            //If (LEqual(Arg1, "Name for sensor 1")) {  // Name match for OEM Voltage sensor 1
            //    ...
            //}
            //ElseIf ...
        }
        Return (local0)
    }
#endif  // ASL_HWM_TYPE_OEM_SUPPORT

#if ASL_SMF_TYPE_OEM_SUPPORT
//---------------------------------------------------------------------------
// Name: OFRN
//
// Description:  OEM SMF report FAN number
//
// Output:
//   Integer - Total smart FAN number supported by this OEM controller
//
//---------------------------------------------------------------------------
    Method (OFRN, 0){
        Return (0)
    }

//------------------------------------------------------------------------
// Table:    TOFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
    Name(TOFC, Package() {
        "OEM FAN 1 name",
        "OEM FAN 2 name",
    })

//---------------------------------------------------------------------------
// Name: OFRS
//
// Description:  OEM SMF report return controller name
//   Arg0 : Index of Controller to return name string
//
// Output:
//   String - Name string for controller
//   "NULL" - Not found
//
//---------------------------------------------------------------------------
    Method (OFRS, 1){
        Store ("NULL", Local0)

        If (LLess(Arg0, SizeOf(TOFC))) {
          Store (DerefOf(Index(TOFC, Arg0)), Local0)
        }

        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: OFTS
//
// Description:  OEM SMF report name string for target temperature
//   Arg0 : Index of Controller to return name string
//
// Output:
//   String - Name string of target temperature for specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (OFTS, 1){
    Store ("NULL", Local0)

    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: OFRL
//
// Description:  OEM SMF Report name list
//
// Input: N/A
//
// Output:
//   String : A list of FAN names that supported Smart FAN from this OEM controller, seperated by comma.
//
//---------------------------------------------------------------------------
    Method (OFRL, 0){
        Store ("", local0)
        // Example 1: Add code here in ASL
        // Store ("\"Name 1\", \"Name 2\", \"Name 3\"", Local0)
        // Example 2: use token
        // Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_OEM_FAN_SENSOR1_STRING, "\"", ), ), Local0)
        // Concatenate (Local0, ",", Local0)
        // Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_OEM_FAN_SENSOR2_STRING, "\"", ), ), Local0)
        // Concatenate (Local0, ",", Local0)
        // Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_OEM_FAN_SENSOR3_STRING, "\"", ), ), Local0)
        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: OFRM
//
// Description:  SMF report FAN mode
//   Arg0 : FAN index
//
// Output:
//   Integer - Bitmap for supported FAN mode.
//
//---------------------------------------------------------------------------
Method (OFRM, 1){
        //If (LEqual(Arg0, ASL_OEM_FAN0_STRING)) {
        //} ElseIf (LEqual(Arg0, ASL_OEM__FAN1_STRING)) {
        //} Else { Return (ASL_BFPI_NOT_SUPPORTED) }
        //Return (7)
        Return (0)
}

//---------------------------------------------------------------------------
// Name: OFPW
//
// Description:  SMF report Max. PWM value for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Max. PWM value supported.
//
//---------------------------------------------------------------------------
Method (OFPW, 1){
        //If (LEqual(Arg0, ASL_OEM_FAN0_STRING)) {
        //} ElseIf (LEqual(Arg0, ASL_OEM__FAN1_STRING)) {
        //} Else { Return (ASL_BFPI_NOT_SUPPORTED) }
        //Return (255)
        Return (ASL_BFPI_NOT_SUPPORTED)
}

//---------------------------------------------------------------------------
// Name: OFLP
//
// Description:  SMF return slope capability for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Slope supported by FAN specified by Arg1.
//     Bit0 : Slop type
//       0 : Use Bit[7:4] and Bit[3:1] as step value
//       1 : 2(n), Bit[7:4] and Bit[3:1] are ignored.
//            ex: 1, 2, 4, 8, 16... 2(n)
//     Bit[3:1] : Digit part of step value
//       0 : No digit part
//       1~3: In form of 2-n. Ex: n=1: unit=0.5; n=2: unit=0.25...
//       Others: reserved
//     Bit[7:4] : Integer part of step value.
//     Bit[15:8]: Max. slope value
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (E1LP, 1){
        //If (LEqual(Arg0, ASL_OEM_FAN0_STRING)) {
        //} ElseIf (LEqual(Arg0, ASL_OEM__FAN1_STRING)) {
        //} Else { Return (ASL_BFPI_NOT_SUPPORTED) }
        //Return (0x4001)  // Max 64, 2(n) type
        Return (ASL_BFPI_NOT_SUPPORTED)
}

//------------------------------------------------------------------------
// Table:    OTFT
// Description:  Look up table for target temperature of OEM FAN.
//   Order should be same as register definition.
//   Temperature name should follow STD_XXX_TEMP tokens in AaeonIoPkg.sdl
//-------------------------------------------------------------------------
    Name(OTFT, Package() {
        // Just example
        "CPU Temperature",
        "System Temperature",
        "System Temperature 2",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
    })

//---------------------------------------------------------------------------
// Name: OFRC
//
// Description:  OEM SMF Report capability
//
// Input:
//   Arg0 : String - FAN name string
//
// Output:
//   String : Correspond Smart FAN functionality in JSON format.
//   "NULL" : No correspond SMF found
//
//---------------------------------------------------------------------------
    Method (OFRC, 1){
//        Store ("", local0)
//        Store ("", local2)
//
//        // Otherwise, Return Smart FAN functionality in JSON format.
//        If (LEqual(Arg0, "Name for FAN 1")) {
//            // Example for a FAN with fixed temperature target.
//            Return ("{\"Name\":\"Name for FAN 1",\"Temperature Point\":4,\"Temperature Target\":\"CPU Temperature\",\"Supported Mode\":[\"Manual\",\"Linear\"]}")
//        }
//        If (LEqual(Arg0, "Name for FAN 2")) {
//            // Example for reading temperature target from register.
//            Store ("{\"Name\":\"Name for FAN 2",\"Temperature Point\":4,\"Temperature Target\":\"", Local0)
//            Store (DerefOf(Index(OTFT, XXXX)), Local2)  // OTFT: OEM look-up table for FAN target; XXXX: Retrived Register Value. They should be define separately.
//            Concatenate (Local0, Local2, Local0)
//            Concatenate (Local0, "\",\"Supported Mode\":[\"Manual\",\"Linear\"]}", Local0)
//            Return (Local0)
//        }
//        // Add if more FAN supported.
//        // ...
        Return ("NULL")
    }

//---------------------------------------------------------------------------
// Name: OFGM
//
// Description:  OEM SMF get mode
//   Arg0 : SMF name to get
//
// Output:
//   Integer :
//     Bit[3:0]: Fan Mode
//       0 - Manual mode
//       1 - Linear mode (Point-Linear mode)
//       2 - Slope-Linear mode
//     Bit[7:4]: Reserved Bits
//     Bit[15:8]: (valid only for manual mode) PWM value for manual mode
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
    Method (OFGM, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        // Retrive data to local0
        //If (LEqual(Arg0, "Name for FAN 1")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    ...
        //}
        //ElseIf (LEqual(Arg0, "Name for FAN 2")) {  // Name match for OEM FAN 2, should be same as sensor name.
        //    ...
        //}
        // Add if more FAN supported.
        // ...
        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: OFSM
//
// Description:  OEM SMF set mode
//   Arg0 : SMF name to set
//   Arg1 : SMF mode to set
//       0 - Manual mode
//       1 - Linear mode (Point-Linear mode)
//       2 - Slope-Linear mode
//     Bit[15:8]: (valid only for manual mode) PWM value for manual mode
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_SUCCESS
//
//---------------------------------------------------------------------------
    Method (OFSM, 3){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        //If (LEqual(Arg0, "Name for FAN 1")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {
        //        // Manual mode
        //        ...
        //    }
        //    Else {
        //        // Linear mode
        //        ...
        //    }
        //    Store (ASL_BFPI_SUCCESS, local0)
        //}
        //ElseIf (LEqual(Arg0, "Name for FAN 2")) {  // Name match for OEM FAN 2, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {
        //        // Manual mode
        //        ...
        //    }
        //    Else {
        //        // Linear mode
        //        ...
        //    }
        //    Store (ASL_BFPI_SUCCESS, local0)
        //}
        // Add if more FAN supported.
        // ...
        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: OFGP
//
// Description:  OEM SMF control get control point configuration
//   Arg0 : SMF name to get
//   Arg1 : control point to get
//     For Linear mode (Point-Linear mode) -
//       0 - lowest point
//       1 - highest point
//       2 - secondary low point
//       3 - third low point
//     ...
//     For Slope-Linear mode -
//       0 - lowest point
//       1 - highest point
//       2 - Slope
//       3 - third low point
//       ...
//
// Output:
//   Integer :
//     For Temp. point -
//       Bit[7:0]: DutyCycle coordinate for this pont
//         0 - 0% duty
//         X - (X/Max)% duty
//         Max - 100% duty
//       Bit[15:8]: Temperature coordinate for this pont
//     For Slope -
//       Bit[7:0]: Digit part after point, of slope. in 1/256
//       Bit[15:8]: Integer part of slope
//     BFPI_NOT_SUPPORTED: No FAN matches name provided.
//
//---------------------------------------------------------------------------
    Method (OFGP, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        // Retrive data to local0
        //If (LEqual(Arg0, "Name for FAN 1")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {   // lowest?
        //        ...
        //    }
        //    ElseIf (LEqual(Arg1, 1)) {   // Highest?
        //        ...
        //    }
        //    ElseIf (LEqual(Arg1, 2)) {   // Secondary low?
        //        ...
        //    }
        //    ...
        //}
        //ElseIf (LEqual(Arg0, "Name for FAN 2")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {   // lowest?
        //        ...
        //    }
        //    ElseIf (LEqual(Arg1, 1)) {   // Highest?
        //        ...
        //    }
        //    ElseIf (LEqual(Arg1, 2)) {   // Secondary low?
        //        ...
        //    }
        //    ...
        //}
        // Add if more FAN supported.
        // ...
        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: OFSP
//
// Description:  OEM SMF control set control point configuration
//   Arg0 : SMF name to set
//   Arg1 : control point to configre
//     For Linear mode (Point-Linear mode) -
//       0 - lowest point
//       1 - highest point
//       2 - secondary low point
//       3 - third low point
//     ...
//     For Slope-Linear mode -
//       0 - lowest point
//       1 - highest point
//       2 - Slope
//       3 - third low point
//       ...
//   For points
//     Arg2 : DutyCycle coordinate for this pont
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     Arg3 : Temperature coordinate for this pont
//   For Slope configuration -
//     Arg2 : Digit part after point, of slope to set. in 1/256
//     Arg3 : Integer part of slope to set.
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER :
//       A FAN matches name provided, but is given a wrong control point.
//       or PWM dutycycle given is larger than Max. supported.
//     BFPI_SUCCESS
//
// Note:
//   If a control point is given with a value bigger than higher control points,
//   the value should also be set to higher point. Vice versa for value smaller.
//---------------------------------------------------------------------------
    Method (OFSP, 4){
        //If (LEqual(Arg0, "Name for FAN 1")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {   // lowest?
        //        ...
        //        // If Lowest > secondary low, update Secondary low point
        //        // If Lowest > Third low, update Third low point
        //        // ...
        //        // If Lowest > Highest, Highest point
        //    }
        //    ElseIf (LEqual(Arg1, 1)) {   // Highest?
        //        ...
        //        // If Highest < secondary low, update Secondary low point
        //        // If Highest < Third low, update Third low point
        //        // ...
        //        // If Highest < Lowest, Highest point
        //    }
        //    ElseIf (LEqual(Arg1, 2)) {   // Secondary low?
        //        ...
        //        // If Secondary low < Lowest, update Lowest point
        //        // ...
        //        // If Secondary low > Third low, update Third low point
        //        // ...
        //        // If Secondary low > Highest, Highest point
        //    }
        //    ...
        //    Else {
        //        Return (ASL_BFPI_INVALID_PARAMETER)
        //    }
        //}
        //ElseIf (LEqual(Arg0, "Name for FAN 2")) {  // Name match for OEM FAN 1, should be same as sensor name.
        //    If (LEqual(Arg1, 0)) {   // lowest?
        //        ...
        //        // If Lowest > secondary low, update Secondary low point
        //        // If Lowest > Third low, update Third low point
        //        // ...
        //        // If Lowest > Highest, Highest point
        //    }
        //    ElseIf (LEqual(Arg1, 1)) {   // Highest?
        //        ...
        //        // If Highest < secondary low, update Secondary low point
        //        // If Highest < Third low, update Third low point
        //        // ...
        //        // If Highest < Lowest, Highest point
        //    }
        //    ElseIf (LEqual(Arg1, 2)) {   // Secondary low?
        //        ...
        //        // If Secondary low < Lowest, update Lowest point
        //        // ...
        //        // If Secondary low > Third low, update Third low point
        //        // ...
        //        // If Secondary low > Highest, Highest point
        //    }
        //    ...
        //    Else {
        //        Return (ASL_BFPI_INVALID_PARAMETER)
        //    }
        //}
        // Add if more FAN supported.
        // ...
        //Else {
            Return (ASL_BFPI_NOT_SUPPORTED)
        //}
        //Return (ASL_BFPI_SUCCESS)
    }
#endif // ASL_SMF_TYPE_OEM_SUPPORT

#if ASL_LED_TYPE_OEM_SUPPORT
    //---------------------------------------------------------------------------
    // Name: OLGB
    //
    // Description:  OEM LED get brightness
    //   Arg0 : LED number to get
    //
    // Output:
    //   Interger:
    //   0 - Off
    //   1 - On
    //   BFPI_NOT_SUPPORTED
    //
    //---------------------------------------------------------------------------
    Method (OLGB, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        // Get LED brightness
        // ...
        Return (local0)
    }

    //---------------------------------------------------------------------------
    // Name: OLSB
    //
    // Description:  OEM LED set brightness
    //   Arg0 : LED number to set
    //   Arg1 : LED brightness to set
    //            0 - Off
    //            1 - On
    //
    // Output:
    //   BFPI_STATUS
    //
    //---------------------------------------------------------------------------
    Method (OLSB, 2){
        // Set LED brightness
        // ...
        Return (ASL_BFPI_NOT_SUPPORTED)
    }
#endif
}