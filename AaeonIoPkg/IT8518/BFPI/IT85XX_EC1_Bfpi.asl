//**********************************************************************
//<AAEON_FHDR_START>
// Name:  <IT85XX_EC1_FBfpi.asl>
// Description: Define AAEON BFPI for Super IO.
//<AAEON_FHDR_END>
//**********************************************************************

//---------------------------------------------------------------------------
// EC_IT85XX BFPI >>
//---------------------------------------------------------------------------
// Definition
//---------------------------------------------------------------------------
#ifndef ASL_BFPI_SUCCESS
    #define ASL_BFPI_SUCCESS 0
#endif
#ifndef ASL_BFPI_NOT_SUPPORTED
    #define ASL_BFPI_NOT_SUPPORTED 0xFFFFFFFF
#endif
#ifndef ASL_BFPI_INVALID_PARAMETER
    #define ASL_BFPI_INVALID_PARAMETER 0xFFFFFFFE
#endif

//---------------------------------------------------------------------------
// Definition variable for IT85XX BFPI function
//---------------------------------------------------------------------------
Name (ApiR,0x10)	// EC API read cmd
Name (ApiW,0x30)	// EC API write cmd
Name (tLim, 0x7F)	// EC temperautre Highest limit
//---------------------------------------------------------------------------
// Temporary variable for IT85XX BFPI function
//---------------------------------------------------------------------------
Name (eDev,0x00)    // Temporary of EC API device.
Name (eFun,0x00)	// Temporary of EC API function.
Name (tHtp, 0x00)   // Temporary of highest temperature point
Name (tHpp, 0x00)   // Temporary of highest presentage of PWM
Name (tLtp, 0x00)  	// Temporary of lowest temperature point
Name (tLpp, 0x00)  	// Temporary of lowest presentage of PWM
Name (tSlp, 0x00)  	// Temporary of slope
//---------------------------------------------------------------------------
//  Set of Field names to be used to access EC BRAM configuration space.
//---------------------------------------------------------------------------
OperationRegion(E1BM,   // Name of Operation Region for SuperIO device
    SystemIO,           // Type of address space
    B1RM,               // Offset to start of region
    2)                  // Size of region in bytes
                        // End of Operation Region
Field(E1BM, ByteAcc, NoLock,Preserve){
    BIDX, 8,            // Field named INDX is 8 bit wide
    BDAT, 8             // Field DATA is 8 bit wide
}
IndexField(BIDX, BDAT, ByteAcc, NoLock, Preserve){
    Offset(0x10),
    ADEV, 8,    // API Device Number
    AFUN, 8,    // API Function Number
    ACNF, 8,    // API Configuration
    A_D0, 8,    // API Data 0
    A_D1, 8,    // API Data 1
    A_D2, 8,    // API Data 2
    A_D3, 8,    // API Data 3
    A_D4, 8,    // API Data 4
    A_D5, 8,    // API Data 5
    A_D6, 8,    // API Data 6
    A_D7, 8,    // API Data 7
    A_D8, 8,    // API Data 8
    A_D9, 8,    // API Data 9
    A_DA, 8,    // API Data A
    A_DB, 8,    // API Data B
    A_DC, 8,    // API Data C
}        //End of indexed field
//---------------------------------------------------------------------------
// IT85xx BFPI common function.
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Name: E_RW
//
// Description: Read/Write EC API function.
// Input:
//   eDev: Device number of EC API
//   eFun: Function number of EC API
//   Arg0: 0x10:Read
//         0x30:Write
//
// Output:
//   0x0: Success
//   0x1: Not support / Time output
//   A_D0~A_DC: EC API data registers
//---------------------------------------------------------------------------
Method (E_RW, 1){
    Store (eDev, ADEV)
    Store (eFun, AFUN)
    Store (Arg0, ACNF)

    Store (200, Local0)          // Set time out counter
    While(Local0)
    {
        Decrement(Local0)        // Decrement Count.
        If(And(ACNF, 0x03))      // bit0: Success, bit1: Fail
        {
            If(And(ACNF,1))  { Store (0x00, Local0) }
            Else { Return (0x01) }
        }
        Stall(100)               // Delay = 100us.
    }
    Return (0x00)
}
//===========================================================================
// EC_IT85XX BFPI-WDT >>
//===========================================================================
#if  ASL_IT851X_WDT_SUPPORT
//---------------------------------------------------------------------------
// Name: W1RC
//
// Description:  SIO WDT report capability - Max timeout
//
// Output:
//   Interger: Max timeout value in ms
//
//---------------------------------------------------------------------------
Method (E1RC, 0) {
    Return (ASL_EC1_WDT_MAX_TIMEOUT)
}
//---------------------------------------------------------------------------
// Name: E1GT
//
// Description:  SIO WDT Get timeout
//
// Output:
//   Interger: Remained timeout value in ms
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
Method (E1GT, 0) {
    Store (0xA8, eDev)
    Store (0x00, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}
                                       // A_D0   : WDT tiemr register 0-255 (0: Stop WDT)
                                       // A_D1-b0: WDT mode 0: second, 1: minute.
    Multiply (A_D0, 1000, Local0)      //Multiply with 1000 in normal mode

    If (And(A_D1,0x01)) {
        Multiply (Local0, 60, Local0)  // Multiply with 60 in Minute mode
    }
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1ST
//
// Description:  SIO WDT set watchdog timeout value and start/stop watchdog
//   Arg0 : Timeout value in ms
//            0: stop watchdog
//            other: start watchdog with value as timeout
//
// Output:
//   BFPI_STATUS
//
// Note: BIOS should have already configure WDT output during POST.
//       So we just set mode and counter here.
//
//---------------------------------------------------------------------------
Method (E1ST, 1){
    // Validate input
    If (LGreater(Arg0, ASL_EC1_WDT_MAX_TIMEOUT)) {
        Return (ASL_BFPI_INVALID_PARAMETER)
    }

    Store (0xA8, eDev)
    Store (0x00, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    If (LGreater(Arg0, 0))
    {
        If (LGreater(Arg0, 1000))
        {
            Divide (Arg0, 1000, Local1, Local0)     // Convert ms to sec, Local0 : time-out in second, Local1 : time-out remainder in ms

            If (LGreater(Local0, 255))
            {
                Divide (Local0, 60, Local2, Local0) // If WDT timer between 256 ~ 300 sec, set WDT timer as 5 min.
                If (LEqual(Local0,4))
                {
                    If (LGreater(Local1, 0)) { Add(Local0,1,Local0) }
                }
                                                    // A_D0   : WDT tiemr register 0-255 (0: Stop WDT)
                                                    // A_D1-B0: WDT mode 0: second, 1: minute.
                Or(A_D1, 0x01 , A_D1)               // Minute mode
            }
            Else
            { And (A_D1, 0xFE, A_D1) }              // Second mode
            Store (Local0, A_D0)
        }
        Else                                        // If WDT timer less then 1 sec, set WDT timer as 1 sec.
        { Store (0x01, A_D0) }
    }
    Else
    {
        Store (0x00, A_D0)
    }
    Store (0x30, ACNF)
    Return (ASL_BFPI_SUCCESS)
}
#endif  //ASL_IT851X_WDT_SUPPORT
//===========================================================================
// EC1_IT85XX BFPI-WDT <<
//===========================================================================
//===========================================================================
// EC_IT85XX BFPI-DIO >>
//===========================================================================

//---------------------------------------------------------------------------
// Name: E1GL
//
// Description:  DIO SIO1 Get Level
//   Arg0 : GPIO Number to get level
//
// Output:
//   Interger:
//   0 - Low level
//   1 - High level
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
Method (E1GL, 1) {
    Store (0xA2, eDev)
    Store (0x01, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    Divide (And(Arg0,0xff),8,Local2,Local1)
    ShiftLeft(0x01, Local2, Local3)
    // Local1 : Result :    GPIO group number
    // Local2 : Remainder : Pin number in group
    // Local3 : bitmask
    If (LEqual(Local1,0))
    {
        ShiftRight(And(A_D1, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,1))
    {
        ShiftRight(And(A_D2, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,2))
    {
        ShiftRight(And(A_D3, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,3))
    {
        ShiftRight(And(A_D4, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,4))
    {
        ShiftRight(And(A_D5, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,5))
    {
        ShiftRight(And(A_D6, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,6))
    {
        ShiftRight(And(A_D7, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,7))
    {
        ShiftRight(And(A_D8, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,8))
    {
        ShiftRight(And(A_D9, Local3), Local2, Local0)
    }
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1SL
//
// Description:  OEM GPIO Set Level
//   Arg0 : GPIO Number to set level
//   Arg1 : Level to set
//     0 - Low level
//     1 - High level
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
Method (E1SL, 2) {
    Store (0xA2, eDev)
    Store (0x01, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    Divide (And(Arg0, 0xff), 8, Local2, Local1)
    ShiftLeft(0x01, Local2, Local3)
    // Local1 : Result :    GPIO group number
    // Local2 : Remainder : Pin number in group
    // Local3 : bitmask
    If (LEqual(Local1,0))
    {
        Or (And(A_D1,Not(Local3)), ShiftLeft(Arg1,Local2), A_D1)
    } ElseIf (LEqual(Local1,1))
    {
        Or (And(A_D2,Not(Local3)), ShiftLeft(Arg1,Local2), A_D2)
    } ElseIf (LEqual(Local1,2))
    {
        Or (And(A_D3,Not(Local3)), ShiftLeft(Arg1,Local2), A_D3)
    } ElseIf (LEqual(Local1,3))
    {
        Or (And(A_D4,Not(Local3)), ShiftLeft(Arg1,Local2), A_D4)
    } ElseIf (LEqual(Local1,4))
    {
        Or (And(A_D5,Not(Local3)), ShiftLeft(Arg1,Local2), A_D5)
    } ElseIf (LEqual(Local1,5))
    {
        Or (And(A_D6,Not(Local3)), ShiftLeft(Arg1,Local2), A_D6)
    } ElseIf (LEqual(Local1,6))
    {
        Or (And(A_D7,Not(Local3)), ShiftLeft(Arg1,Local2), A_D7)
    } ElseIf (LEqual(Local1,7))
    {
        Or (And(A_D8,Not(Local3)), ShiftLeft(Arg1,Local2), A_D8)
    } ElseIf (LEqual(Local1,8))
    {
        Or (And(A_D9,Not(Local3)), ShiftLeft(Arg1,Local2), A_D9)
    }

    If (LGreater(E_RW(ApiW), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}
    Return (ASL_BFPI_SUCCESS)
}
//---------------------------------------------------------------------------
// Name: E1GD
//
// Description:  OEM GPIO Get Direction
//   Arg0 : GPIO Number to get Direction
//
// Output:
//   Interger:
//   0 - Output
//   1 - Input
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
Method (E1GD, 1) {
    Store (0xA2, eDev)
    Store (0x00, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    Divide (And(Arg0, 0xff), 8, Local2, Local1)
    ShiftLeft(0x01, Local2, Local3)
    // Local1 : Result :    GPIO group number
    // Local2 : Remainder : Pin number in group
    // Local3 : bitmask
    If (LEqual(Local1,0))
    {
        ShiftRight(And(A_D1, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,1))
    {
        ShiftRight(And(A_D2, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,2))
    {
        ShiftRight(And(A_D3, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,3))
    {
        ShiftRight(And(A_D4, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,4))
    {
        ShiftRight(And(A_D5, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,5))
    {
        ShiftRight(And(A_D6, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,6))
    {
        ShiftRight(And(A_D7, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,7))
    {
        ShiftRight(And(A_D8, Local3), Local2, Local0)
    } ElseIf (LEqual(Local1,8))
    {
        ShiftRight(And(A_D9, Local3), Local2, Local0)
    }
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1SD
//
// Description:  OEM GPIO Set Direction
//   Arg0 : GPIO Number to set Direction
//   Arg1 : Direction to set
//     0 - Output
//     1 - Input
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
Method (E1SD, 2) {
    Store (0xA2, eDev)
    Store (0x00, eFun)
    If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    Divide (And(Arg0, 0xff), 8, Local2, Local1)
    ShiftLeft(0x01, Local2, Local3)
    // Local1 : Result :    GPIO Group number
    // Local2 : Remainder : Pin number in group
    // Local3 : bitmask
    If (LEqual(Local1,0))
    {
        Or (And(A_D1,Not(Local3)), ShiftLeft(Arg1,Local2), A_D1)
    } ElseIf (LEqual(Local1,1))
    {
        Or (And(A_D2,Not(Local3)), ShiftLeft(Arg1,Local2), A_D2)
    } ElseIf (LEqual(Local1,2))
    {
        Or (And(A_D3,Not(Local3)), ShiftLeft(Arg1,Local2), A_D3)
    } ElseIf (LEqual(Local1,3))
    {
        Or (And(A_D4,Not(Local3)), ShiftLeft(Arg1,Local2), A_D4)
    } ElseIf (LEqual(Local1,4))
    {
        Or (And(A_D5,Not(Local3)), ShiftLeft(Arg1,Local2), A_D5)
    } ElseIf (LEqual(Local1,5))
    {
        Or (And(A_D6,Not(Local3)), ShiftLeft(Arg1,Local2), A_D6)
    } ElseIf (LEqual(Local1,6))
    {
        Or (And(A_D7,Not(Local3)), ShiftLeft(Arg1,Local2), A_D7)
    } ElseIf (LEqual(Local1,7))
    {
        Or (And(A_D8,Not(Local3)), ShiftLeft(Arg1,Local2), A_D8)
    } ElseIf (LEqual(Local1,8))
    {
        Or (And(A_D9,Not(Local3)), ShiftLeft(Arg1,Local2), A_D9)
    }

    If (LGreater(E_RW(ApiW), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

    Return (ASL_BFPI_SUCCESS)
}

//---------------------------------------------------------------------------
// Name: E1GO
//
// Description:  DIO SIO1 Get Driving
//   Arg0 : GPIO Number to get Driving
//
// Output:
//   Interger:
//     0: Open drain
//     1: Push pull
//     2: T.B.D.
//     3: T.B.D.
//     4: T.B.D.
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
Method (E1GO, 1) {
    // This feature isn't supported, currently.
    Return (ASL_BFPI_INVALID_PARAMETER)
}
//---------------------------------------------------------------------------
// Name: E1SO
//
// Description:  OEM GPIO Set Driving
//   Arg0 : GPIO Number to set Driving
//   Arg1 : Driving to set
//     0: Open drain
//     1: Push pull / Internal pull-up 20K
//     2: Internal pull-up 10K
//     3: Internal pull-up 5K
//     4: Internal pull-up 1K
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
Method (E1SO, 2) {
    // This feature isn't supported, currently.
    Return (ASL_BFPI_INVALID_PARAMETER)
}
//===========================================================================
// EC_IT85XX BFPI-DIO <<
//===========================================================================
//===========================================================================
// EC_IT85XX BFPI-HWM >>
//===========================================================================
// ===== THERMAL =====
#ifndef ASL_EC1_IT85XX_THRM_SEN0_STRING
    #define ASL_EC1_IT85XX_THRM_SEN0_STRING "EC_IT85XX THERMAL SENSOR 0"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN1_STRING
    #define ASL_EC1_IT85XX_THRM_SEN1_STRING "EC_IT85XX THERMAL SENSOR 1"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN2_STRING
    #define ASL_EC1_IT85XX_THRM_SEN2_STRING "EC_IT85XX THERMAL SENSOR 2"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN3_STRING
    #define ASL_EC1_IT85XX_THRM_SEN3_STRING "EC_IT85XX THERMAL SENSOR 3"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN4_STRING
    #define ASL_EC1_IT85XX_THRM_SEN4_STRING "EC_IT85XX THERMAL SENSOR 4"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN5_STRING
    #define ASL_EC1_IT85XX_THRM_SEN5_STRING "EC_IT85XX THERMAL SENSOR 5"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN6_STRING
    #define ASL_EC1_IT85XX_THRM_SEN6_STRING "EC_IT85XX THERMAL SENSOR 6"
#endif

#ifndef ASL_EC1_IT85XX_THRM_SEN7_STRING
    #define ASL_EC1_IT85XX_THRM_SEN7_STRING "EC_IT85XX THERMAL SENSOR 7"
#endif
// ===== FAN =====
#ifndef ASL_EC1_IT85XX_FAN0_STRING
    #define ASL_EC1_IT85XX_FAN0_STRING "EC_IT85XX FAN0"
#endif
#ifndef ASL_EC1_IT85XX_FAN1_STRING
    #define ASL_EC1_IT85XX_FAN1_STRING "EC_IT85XX FAN1"
#endif
#ifndef ASL_EC1_IT85XX_FAN2_STRING
    #define ASL_EC1_IT85XX_FAN2_STRING "EC_IT85XX FAN2"
#endif
// ===== VIN =====
#ifndef ASL_EC1_IT85XX_VIN0_NAME
    #define ASL_EC1_IT85XX_VIN0_STRING "EC1_IT85XX-VIN0"
#endif
#ifndef ASL_EC1_IT85XX_VIN1_NAME
    #define ASL_EC1_IT85XX_VIN1_STRING "EC1_IT85XX-VIN1"
#endif
#ifndef ASL_EC1_IT85XX_VIN2_STRING
    #define ASL_EC1_IT85XX_VIN2_STRING "EC1_IT85XX-VIN2"
#endif
#ifndef ASL_EC1_IT85XX_VIN3_STRING
    #define ASL_EC1_IT85XX_VIN3_STRING "EC1_IT85XX-VIN3"
#endif
#ifndef ASL_EC1_IT85XX_VIN4_STRING
    #define ASL_EC1_IT85XX_VIN4_STRING "EC1_IT85XX-VIN4"
#endif
#ifndef ASL_EC1_IT85XX_VIN5_STRING
    #define ASL_EC1_IT85XX_VIN5_STRING "EC1_IT85XX-VIN5"
#endif
#ifndef ASL_EC1_IT85XX_VIN6_STRING
    #define ASL_EC1_IT85XX_VIN6_STRING "EC1_IT85XX-VIN6"
#endif
#ifndef ASL_EC1_IT85XX_VIN7_STRING
    #define ASL_EC1_IT85XX_VIN7_STRING "EC1_IT85XX-VIN7"
#endif
//---------------------------------------------------------------------------
// Name: E1SN
//
// Description:  SIO HWM report sensor number
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   Integer - Total senser number for specified sensor type
//
//---------------------------------------------------------------------------
Method (E1SN, 1){
    Store (0, Local0)
    //If (LEqual(Arg0, 0)) {// Temperature
    //    Store (0xA5, eDev)
    //    Store (0x00, eFun)
    //} ElseIf (LEqual(Arg0, 1)) {// Fan
    //    Store (0xA6, eDev)
    //    Store (0x00, eFun)
    //} ElseIf (LEqual(Arg0, 2)) {// Voltage
    //    Store (0xA5, eDev)
    //    Store (0x01, eFun)
    //}
    //If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }
    //Store (A_D0, Local0)   // Amount function are supported by EC chip.
    //Return (Local0)
    If (LEqual(Arg0, 0)) {
        // Temperature
        Store (ASL_EC1_IT85XX_TEMP_SENSOR_NUMBER, Local0)
    } ElseIf (LEqual(Arg0, 1)) {
        // Fan
        Store (ASL_EC1_IT85XX_FAN_SENSOR_NUMBER, Local0)
    } ElseIf (LEqual(Arg0, 2)) {
        // Voltage
        Store (ASL_EC1_IT85XX_VOLT_SENSOR_NUMBER, Local0)
    }
    Return (Local0)
}

//------------------------------------------------------------------------
// Table:    TETS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
Name(TETS, Package() {
#if ASL_IT851X_PECI_ENABLE
    ASL_EC1_IT85XX_THRM_SEN0_STRING,
#endif
#if ASL_IT851X_TEMP1_ENABLE
    ASL_EC1_IT85XX_THRM_SEN1_STRING,
#endif
#if ASL_IT851X_TEMP2_ENABLE
    ASL_EC1_IT85XX_THRM_SEN2_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    TEFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
Name(TEFS, Package() {
#if ASL_IT851X_TACH1_ENABLE
    ASL_EC1_IT85XX_FAN0_STRING,
#endif
#if ASL_IT851X_TACH2_ENABLE
    ASL_EC1_IT85XX_FAN1_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    TEVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
Name(TEVS, Package() {
#if ASL_IT851X_VIN0_ENABLE
    ASL_EC1_IT85XX_VIN0_STRING,
#endif
#if ASL_IT851X_VIN1_ENABLE
    ASL_EC1_IT85XX_VIN1_STRING,
#endif
#if ASL_IT851X_VIN2_ENABLE
    ASL_EC1_IT85XX_VIN2_STRING,
#endif
#if ASL_IT851X_VIN3_ENABLE
    ASL_EC1_IT85XX_VIN3_STRING,
#endif
#if ASL_IT851X_VIN4_ENABLE
    ASL_EC1_IT85XX_VIN4_STRING,
#endif
#if ASL_IT851X_VIN5_ENABLE
    ASL_EC1_IT85XX_VIN5_STRING,
#endif
#if ASL_IT851X_VIN6_ENABLE
    ASL_EC1_IT85XX_VIN6_STRING,
#endif
#if ASL_IT851X_VIN7_ENABLE
    ASL_EC1_IT85XX_VIN7_STRING,
#endif
})

//---------------------------------------------------------------------------
// Name: E1SS
//
// Description:  EC HWM report sensor name string
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
Method (E1SS, 2){
    Store ("NULL", Local0)
    If (LEqual(Arg0, 0)) {
        // Temperature
        If (LLess(Arg1, SizeOf(TETS))) {
          Store (DerefOf(Index(TETS, Arg1)), Local0)
        }
    } ElseIf (LEqual(Arg0, 1)) {
        // Fan
        If (LLess(Arg1, SizeOf(TEFS))) {
          Store (DerefOf(Index(TEFS, Arg1)), Local0)
        }
    } ElseIf (LEqual(Arg0, 2)) {
        // Voltage
        If (LLess(Arg1, SizeOf(TEVS))) {
          Store (DerefOf(Index(TEVS, Arg1)), Local0)
        }
    }
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: H1SL
//
// Description:  SIO HWM report sensor name list
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   String - List of supported sensor name for specified sensor type
//
//---------------------------------------------------------------------------
Method (H1SL, 1){
    Store ("", Local0)    // String to return
    Store (ONE, Local1)    // Flag to append comma to string
    Store (0, Local2)    // Sensor number
    Store (0, Local3)    // Counter

    Store (E1SN(Arg0), Local2)    // Sensor number

    While (LLess(Local3, Local2)) {
        If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (E1SS(Arg0, Local3), "\"", ), ), Local0)
        Increment (Local3)
    }

    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: HVCV
//
// Description:  SIO HWM convert Voltage reading to mini-volt
//   Arg0 : Voltage reading
//   Arg1 : R1 value, resistor to power
//   Arg2 : R2 value, resistor to ground
//
// Output:
//   Voltage in mini-volt
//
//---------------------------------------------------------------------------
    Method (HVCV, 3){
        Divide(Multiply(Arg0,1000),341,,Local0)                // Reverse convert ADC with 3FFh into 3.0V
        Divide(Multiply(Local0,Add(Arg1,Arg2)),Arg2,,Local0)   // Reverse convert with voltage dividing
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: E1RS
//
// Description:  SIO HWM read sensor
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
// Note: Order for sensors follows same order in BIOS setup.
//   Refer to W83627DHGExternalFunList in W83627DHGHwmSetup.c.
//---------------------------------------------------------------------------
    Method (E1RS, 2){

            Store (ASL_BFPI_NOT_SUPPORTED, Local0)

         If (LEqual(Arg0, 0)) {  // Temperature
            Store (0xA5, eDev)
            Store (0x00, eFun)
            If (LGreater(E_RW(ApiR), 0)) {Return (ASL_BFPI_NOT_SUPPORTED)}

            If (LEqual(0,1)) {} // False, return BFPI_NOT_SUPPORTED if no match
            #if ASL_IT851X_PECI_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN0_STRING)) {
                Store (Multiply(A_D1,1000), Local0)
            }
            #endif
            #if ASL_IT851X_TEMP1_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN1_STRING)) {
                Store (Multiply(A_D2,1000), Local0)
            }
            #endif
            #if ASL_IT851X_TEMP2_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN2_STRING)) {
                Store (Multiply(A_D3,1000), Local0)
            }
            #endif
            #if ASL_EC1_IT85XX_THRM_SEN3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN3_STRING)) {
                Store (Multiply(A_D4,1000), Local0)
            }
            #endif
            #if ASL_EC1_IT85XX_THRM_SEN4_SUPPORT
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN4_STRING)) {
                Store (Multiply(A_D5,1000), Local0)
            }
            #endif
            #if ASL_EC1_IT85XX_THRM_SEN5_SUPPORT
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN5_STRING)) {
                Store (Multiply(A_D6,1000), Local0)
            }
            #endif
            #if ASL_EC1_IT85XX_THRM_SEN6_SUPPORT
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN6_STRING)) {
                Store (Multiply(A_D7,1000), Local0)
            }
            #endif
            #if ASL_EC1_IT85XX_THRM_SEN7_SUPPORT
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_THRM_SEN7_STRING)) {
                Store (Multiply(A_D8,1000), Local0)
            }
            #endif
            Else { Return (ASL_BFPI_NOT_SUPPORTED) }

        } ElseIf (LEqual(Arg0, 1)) {
	        Store (0xA6, eDev)
            If (LEqual(0,1)) {} // False, return BFPI_NOT_SUPPORTED if no match
    	    #if ASL_IT851X_TACH1_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_FAN0_STRING)) {
                Store (0x00, eFun)
            }
            #endif
            #if ASL_IT851X_TACH2_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_FAN1_STRING)) {
                Store (0x01, eFun)
            }
            #endif
            Else { Return (ASL_BFPI_NOT_SUPPORTED) }

            If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }

            Or(A_D2,ShiftLeft(A_D1,8),Local0)

        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            Store (0xA5, eDev)
            If (LEqual(0,1)) {} // False, return BFPI_NOT_SUPPORTED if no match
            #if ASL_IT851X_VIN0_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN0_STRING)) {
                Store (0x01, eFun)
            }
            #endif
            #if ASL_IT851X_VIN1_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN1_STRING)) {
                Store (0x01, eFun)
            }
            #endif
            #if ASL_IT851X_VIN2_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN2_STRING)) {
                Store (0x01, eFun)
            }
            #endif
            #if ASL_IT851X_VIN3_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN3_STRING)) {
                Store (0x01, eFun)
            }
            #endif
            #if ASL_IT851X_VIN4_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN4_STRING)) {
                Store (0x02, eFun)
            }
            #endif
            #if ASL_IT851X_VIN5_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN5_STRING)) {
                Store (0x02, eFun)
            }
            #endif
            #if ASL_IT851X_VIN6_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN6_STRING)) {
                Store (0x02, eFun)
            }
            #endif
            #if ASL_IT851X_VIN7_ENABLE
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN7_STRING)) {
                Store (0x02, eFun)
            }
            #endif
            Else { Return (ASL_BFPI_NOT_SUPPORTED) }

            If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }

                If (LEqual(Arg1, ASL_EC1_IT85XX_VIN0_STRING)) {  // VIN0
                Add(ShiftLeft(A_D1,8),A_D2,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN0_R1R2,8), And(ASL_IT851X_VIN0_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN1_STRING)) {  // VIN1
                Add(ShiftLeft(A_D3,8),A_D4,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN1_R1R2,8), And(ASL_IT851X_VIN1_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN2_STRING)) {  // VIN2
                Add(ShiftLeft(A_D5,8),A_D6,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN2_R1R2,8), And(ASL_IT851X_VIN2_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN3_STRING)) {  // VIN3
                Add(ShiftLeft(A_D7,8),A_D8,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN3_R1R2,8), And(ASL_IT851X_VIN3_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN4_STRING)) {  // VIN4
                Add(ShiftLeft(A_D1,8),A_D2,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN4_R1R2,8), And(ASL_IT851X_VIN4_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN5_STRING)) {  // VIN5
                Add(ShiftLeft(A_D3,8),A_D4,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN5_R1R2,8), And(ASL_IT851X_VIN5_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN6_STRING)) {  // VIN6
                Add(ShiftLeft(A_D5,8),A_D6,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN6_R1R2,8), And(ASL_IT851X_VIN6_R1R2,0xff)), Local0)
            }
            ElseIf (LEqual(Arg1, ASL_EC1_IT85XX_VIN7_STRING)) {  // VIN7
                Add(ShiftLeft(A_D7,8),A_D8,Local0)
                Store( HVCV (Local0, ShiftRight(ASL_IT851X_VIN7_R1R2,8), And(ASL_IT851X_VIN7_R1R2,0xff)), Local0)
            } Else { Return (ASL_BFPI_NOT_SUPPORTED) }
        } Else { Return (ASL_BFPI_NOT_SUPPORTED) }
        Return (Local0)

    }
//===========================================================================
// EC_IT85XX BFPI-HWM <<
//===========================================================================
//===========================================================================
// EC_IT85XX BFPI-SMF >>
//===========================================================================
//------------------------------------------------------------------------
// Table:    TEFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
Name(TEFC, Package() {
#if ASL_IT851X_FAN1_ENABLE
    ASL_EC1_IT85XX_FAN0_STRING,
#endif
#if ASL_IT851X_FAN2_ENABLE
    ASL_EC1_IT85XX_FAN1_STRING,
#endif
})
//------------------------------------------------------------------------
// Table:    TEFT
// Description:  Look up table for FAN controller's target temperature string
// Note: Order must be same as register definition in EC API
//-------------------------------------------------------------------------
Name(TEFT, Package() {
#if ASL_IT851X_PECI_ENABLE
    ASL_EC1_IT85XX_THRM_SEN0_STRING,
#else
    "N/A",
#endif
#if ASL_IT851X_TEMP1_ENABLE
    ASL_EC1_IT85XX_THRM_SEN1_STRING,
#else
    "N/A",
#endif
#if ASL_IT851X_TEMP2_ENABLE
    ASL_EC1_IT85XX_THRM_SEN2_STRING,
#else
    "N/A",
#endif
})
//---------------------------------------------------------------------------
// Name: E1FS
//
// Description:  EC SMF report sensor name string
//   Arg0 : Index of Controller to return name string
//
// Output:
//   String - Name string of specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (E1FS, 1){
    Store ("NULL", Local0)

    If (LLess(Arg0, SizeOf(TEFC))) {
      Store (DerefOf(Index(TEFC, Arg0)), Local0)
    }

    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1TS
//
// Description:  EC SMF report name string for target temperature
//   Arg0 : String - FAN name to return
//
// Output:
//   String - Name string of target temperature for specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (E1TS, 1){
    Store ("NULL", Local0)

    Store (0xA6,eDev)
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (0x00, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (0x01, eFun)
    } Else { return (ASL_BFPI_NOT_SUPPORTED) }
    If (LGreater(E_RW(ApiR), 0)) { Return (Local0) }

    Store (DerefOf(Index(TEFT, And(A_D3,0x0F))), Local0)  // A_D3 Bit[3:0] : Temperature target

    Return (Local0)
}
//===========================================================================
// Name: E1RL
//
// Description:  SIO SMF Report name list
//
// Input: N/A
//
// Output:
//   String : A list of FAN names that supported Smart FAN from this OEM controller, seperated by comma.
//
//---------------------------------------------------------------------------
Method (E1RL, 0){
    Store ("", Local0)
    Store (ONE, Local1)
    // Return a list of FAN names that supported Smart FAN from this SOP, seperated by comma.
    #if ASL_IT851X_FAN1_ENABLE
    If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
    Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_EC1_IT85XX_FAN0_STRING, "\"", ), ), Local0)
    #endif
    #if ASL_IT851X_FAN2_ENABLE
    If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
    Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_EC1_IT85XX_FAN1_STRING, "\"", ), ), Local0)
    #endif
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1RN
//
// Description:  SMF report FAN number
//
// Output:
//   Integer - Total smart FAN number supported
//
//---------------------------------------------------------------------------
Method (E1RN, 0){
    //Store (0xA6, eDev)
    //Store (0x00, eFun)
    //If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }
    //
    //Store (A_D0, Local0)    //Amount of SMART fan function supported
    //Return (Local0)
    Return (ASL_EC1_IT85XX_SMF_NUMBER)
}

//---------------------------------------------------------------------------
// Name: E1RM
//
// Description:  SMF report FAN mode
//   Arg0 : FAN index
//
// Output:
//   Integer - Bitmap for supported FAN mode.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (E1RM, 1){
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
    } Else { Return (ASL_BFPI_NOT_SUPPORTED) }
    Return (0x5)
}

//---------------------------------------------------------------------------
// Name: E1PW
//
// Description:  SMF report Max. PWM value for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Max. PWM value supported.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (E1PW, 1){
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
    } Else { Return (ASL_BFPI_NOT_SUPPORTED) }
    Return (ASL_EC1_SMF_MAX_DUTY)
}

//---------------------------------------------------------------------------
// Name: E1LP
//
// Description:  SMF report  return Min. slope unit for specified FAN Controller
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
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
    } Else { Return (ASL_BFPI_NOT_SUPPORTED) }
    Return (0x4001)  // Max 64, 2(n) type
}

//---------------------------------------------------------------------------
// Name: F1RC
//
// Description:  SMF Report capability
//
// Input:
//   Arg0 : String - FAN name string
//
// Output:
//   String : Correspond Smart FAN functionality in JSON format.
//   "NULL" : No correspond SMF found
//
//---------------------------------------------------------------------------
Method (F1RC, 1){
    Store ("NULL", Local0)  // String to return
    Store ("", Local1)  // Temporal
    Store (0, Local2)  // Counter
    Store (ONE, Local3)    // Flag to append comma to string

    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (ASL_EC1_IT85XX_FANOUT0_PREFIX, Local0)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (ASL_EC1_IT85XX_FANOUT1_PREFIX, Local0)
    } Else { Return (Local0) }

    Store (E1TS(Arg0), Local1)
    Concatenate (Local0, Local1, Local0)
    Concatenate (Local0, ASL_EC1_IT85XX_FANOUT_SUFFIX, Local0)

    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1GM
//
// Description:  SIO SMF get mode
//   Arg0 : SMF name to get
//
// Output:
//   Integer :
//     Bit[3:0]: Fan Mode
//       0 - Manual mode
//       2 - Slope-Linear mode
//     Bit[7:4]: Reserved Bits
//     Bit[15:8]: (valid only for manual mode) Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
Method (E1GM, 1){
    Store (0xA6,eDev)

    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (0x00, eFun)
    }
    ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (0x01, eFun)
    }
    ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN2_STRING)) {
        Store (0x02, eFun)
    }
    Else { return (ASL_BFPI_NOT_SUPPORTED) }
    If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }

    And (A_D3,0x80,Local1)                       // Bit7: SMART FAN function switch. 1:On, 0:Off
    If (LEqual(Local1, 0x0)) {                   // Manual mode
        Store (A_D8, Local3)                     // Manual PWM value
        Or (ShiftRight(Local1,0x7), ShiftLeft(Local3, 0x8), Local0)
    } Else { Return (0x02) }

    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1SM
// Description:  SIO SMF set mode
//   Arg0 : SMF name to set
//   Arg1 : SMF mode to set
//       0 - Manual mode
//       1 - Linear mode (for backward compatible)
//       2 - Slope-Linear mode
//   Arg2 : Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER : PWM dutycycle given is larger than Max. supported.
//     BFPI_SUCCESS
//---------------------------------------------------------------------------
Method (E1SM, 3){
    If (LAnd(LEqual(Arg1, 0), LGreater(Arg2, ASL_EC1_SMF_MAX_DUTY))) { Return (ASL_BFPI_INVALID_PARAMETER) }

    Store (0xA6,eDev)
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (0x00, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (0x01, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN2_STRING)) {
        Store (0x02, eFun)
    } Else { return (ASL_BFPI_NOT_SUPPORTED) }
    If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED)}

    If (LEqual(Arg1, 0)) {                            // 0:Maunal mode
        Store (Arg2, A_D8)                          // Set PWM value.
        And(A_D3,0x7F,A_D3)                           // SMART FAN function Off
    }
    Else {
        Or(A_D3,0x80,A_D3)                            // SMART FAN function On
    }
    If (LGreater(E_RW(ApiW), 0)) {
        Return (ASL_BFPI_NOT_SUPPORTED)
    }
    Return (ASL_BFPI_SUCCESS)
}
//---------------------------------------------------------------------------
// Name: U_TP
//
// Description:  Calculate the current heat point, percent of PWM.
//
// Input:     A_D4, A_D6, A_D7
//
// Output:
//     tSlp : Option Register 07h: Slope of FAN
//     tLtp : Option Register 04h: Temperature of FAN to start
//     tLpp : Option Register 06h: PWM of FAN start
//     tHtp : Calculated temperature for highest point
//     tHpp : Calculated PWM for highest point
//
//---------------------------------------------------------------------------
Method (U_TP, 0){
    // Save current setting slope, Start of temperature , Start of PWM.
    Store (A_D7,tSlp)
    Store (A_D4,tLtp)
    Store (A_D6,tLpp)

    If (LGreater(tSlp,0)){
        //Calculate the highest hit point with 100% PWM.
        Divide (Subtract(100,tLpp),ShiftLeft(0x1,Subtract(tSlp,1)),Local1,Local0)
        // If the calculated highest heat point greater then chip supports highest thermal limit,
        // re-calculated highest heat point as chip supports highest thermal limit,
        If (LGreater(Add(tLtp,Local0),tLim)){
            Add(tLpp,Multiply(Subtract(tLim,tLtp),ShiftLeft(0x1,Subtract(tSlp,1))),tHpp)
            Store(tLim,tHtp)
        } Else {
            Add(tLtp,Local0,tHtp)
            Add(tLpp,Multiply(Local0,ShiftLeft(0x1,Subtract(tSlp,1))),tHpp)
        }
    } Else {
        Store (tLtp, tHtp)
        Store (tLpp, tHpp)
    }
}
//---------------------------------------------------------------------------
// Name: E1GP
//
// Description:  SIO SMF control get control point configuration
//   Arg0 : SMF name to get
//   Arg1 : control point to get
//     0 - lowest point
//     1 - highest point  (For backward compatibility)
//     2 - Slope
//     3 - secondary low point     (Not support)
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
Method (E1GP, 2){
    Store (0xA6,eDev)
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (0x00, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (0x01, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN2_STRING)) {
        Store (0x02, eFun)
    } Else { return (ASL_BFPI_NOT_SUPPORTED) }
    If (LGreater(E_RW(ApiR), 0)) {
        Return (ASL_BFPI_NOT_SUPPORTED)
    }
    U_TP()
    Switch (Arg1)
    {
        Case (0x0) {  // lowest point
            Or (tLpp, ShiftLeft(tLtp, 8), Local0)
        }
        Case (0x1) {  // highest point
            Or (tHpp, ShiftLeft(tHtp, 8), Local0)
        }
        Case (0x2) {  // Slope
            Store (ShiftLeft(A_D7, 8), Local0)
        }
        Default { return (ASL_BFPI_NOT_SUPPORTED) }
    }
    Return (Local0)
}
//---------------------------------------------------------------------------
// Name: E1SP
//
// Description:  EC SMF control set control point configuration. Supports Slope-Linear mode only.
//   Arg0 : SMF name to set
//   Arg1 : Point number to configure.
//     0 - lowest point
//     1 - highest point  (For backward compatibility, will update slope at same time)
//     2 - Slope
//     3 - third low point     (Not support)
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
//   If a control point is given with a value higher than higher control points,
//   the value should also be set to higher point. Vice versa for lower ones.
//---------------------------------------------------------------------------
Method (E1SP, 4){
    If (LAnd(LNotEqual(Arg1, 2), LGreater(Arg2, ASL_EC1_SMF_MAX_DUTY))) { Return (ASL_BFPI_INVALID_PARAMETER) }

    Store (0xA6, eDev)           // Fan Controller
    If (LEqual(Arg0, ASL_EC1_IT85XX_FAN0_STRING)) {
        Store (0x00, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN1_STRING)) {
        Store (0x01, eFun)
    } ElseIf (LEqual(Arg0, ASL_EC1_IT85XX_FAN2_STRING)) {
        Store (0x02, eFun)
    } Else { return (ASL_BFPI_NOT_SUPPORTED) }
    If (LGreater(E_RW(ApiR), 0)) { Return (ASL_BFPI_NOT_SUPPORTED) }
    U_TP()          //Calculate the current heat point, percent of PWM.
    Switch (Arg1)   //Update the new tHtp,tHpp,tLtp,tLPP,
    {
        Case (0x0) {							//Set new lowest point
            Store(Arg2, tLpp)
            Store(Arg3, tLtp)
            If (LGreater(tLtp,tHtp)){ Store(tLtp, tHtp)}
            If (LGreater(tLpp,tHpp)){ store(tLpp, tHpp)}
        }
        Case (0x1) {							//Set new highest point
            Store(Arg2, tHpp)
            Store(Arg3, tHtp)
            If (LLess(tHtp,tLtp)){ Store(tHtp,tLtp) }
            If (LLess(tHpp,tLpp)){ Store(tHpp,tLpp) }
            If (LGreater(tHtp,tLtp)){
                Subtract(tHpp,tLpp, Local3)
                Subtract(tHtp,tLtp, Local4)
                Divide (Local3, Local4, Local1, Local2)
                If (LGreater(Local1,0x0)){
                    Add(Local2,0x1,Local2)
                }
                //Local3: delta-PWM
                //Local4: delta-T
                //Local2: Increasing PWM per degree.
                If (LGreater(Local2,0x0)){
                    For (Local0=0,Local0<7,Local0++) // 0-6 step
                    {
                        If(LGreaterEqual(ShiftLeft(0x1,Local0),Local2)){
                        //If Slope value greater 'Increasing PWM per degree'
                        Store(Add(Local0,0x1),tSlp)
                        Store(0x8,Local0)
                        }
                    }
                } Else { Store(0x0,tSlp) }
            } Else { Store(0x0,tSlp) }
        }
        Case (0x02) {							//Set slope
                    Store(Arg3, tSlp)           //EC supports only integer slope
        }
        Default { return (ASL_BFPI_NOT_SUPPORTED) }
    }
    Store(tLtp,A_D4)                                // Start of temperature
    Store(tLpp,A_D6)                                // Start of PWM
    Store(tSlp,A_D7)                                // Slope
    If (LGreater(A_D5,tLtp)){ Store (tLtp,A_D5) }   // If off of temperature greater start of temperature, set off of temperature as start of temperature.
    If (LGreater(E_RW(ApiW), 0)) {
        Return (ASL_BFPI_NOT_SUPPORTED)
    }
    Return (0x0)
}
//===========================================================================
// EC_IT85XX BFPI-SMF <<
//===========================================================================
//---------------------------------------------------------------------------
// EC_IT85XX BFPI End
//---------------------------------------------------------------------------







