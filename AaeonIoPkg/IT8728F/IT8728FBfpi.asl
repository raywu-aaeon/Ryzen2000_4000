//**********************************************************************
//<AAEON_FHDR_START>
//
// Name:  <IT8728FBfpi.asl>
//
// Description: Define AAEON BFPI for Super IO.
//
//<AAEON_FHDR_END>
//**********************************************************************
#ifndef ASL_BFPI_SUCCESS
    #define ASL_BFPI_SUCCESS 0
#endif
#ifndef ASL_BFPI_NOT_SUPPORTED
    #define ASL_BFPI_NOT_SUPPORTED 0xFFFFFFFF
#endif
#ifndef ASL_BFPI_INVALID_PARAMETER
    #define ASL_BFPI_INVALID_PARAMETER 0xFFFFFFFE
#endif
#ifndef ASL_IT8728F_TMPIN1_STRING
    #define ASL_IT8728F_TMPIN1_STRING "IT8728F-TMPIN1"
#endif
#ifndef ASL_IT8728F_TMPIN2_STRING
    #define ASL_IT8728F_TMPIN2_STRING "IT8728F-TMPIN2"
#endif
#ifndef ASL_IT8728F_TMPIN3_STRING
    #define ASL_IT8728F_TMPIN3_STRING "IT8728F-TMPIN3"
#endif
#ifndef ASL_IT8728F_FAN_1_STRING
    #define ASL_IT8728F_FAN_1_STRING "IT8728F-FAN_1"
#endif
#ifndef ASL_IT8728F_FAN_2_STRING
    #define ASL_IT8728F_FAN_2_STRING "IT8728F-FAN_2"
#endif
#ifndef ASL_IT8728F_FAN_3_STRING
    #define ASL_IT8728F_FAN_3_STRING "IT8728F-FAN_3"
#endif
#ifndef ASL_IT8728F_FAN_4_STRING
    #define ASL_IT8728F_FAN_4_STRING "IT8728F-FAN_4"
#endif
#ifndef ASL_IT8728F_FAN_5_STRING
    #define ASL_IT8728F_FAN_5_STRING "IT8728F-FAN_5"
#endif
#ifndef ASL_IT8728F_VIN0_STRING
    #define ASL_IT8728F_VIN0_STRING "IT8728F-VIN0"
#endif
#ifndef ASL_IT8728F_VIN1_STRING
    #define ASL_IT8728F_VIN1_STRING "IT8728F-VIN1"
#endif
#ifndef ASL_IT8728F_VIN2_STRING
    #define ASL_IT8728F_VIN2_STRING "IT8728F-VIN2"
#endif
#ifndef ASL_IT8728F_VIN3_STRING
    #define ASL_IT8728F_VIN3_STRING "IT8728F-VIN3"
#endif
#ifndef ASL_IT8728F_VIN4_STRING
    #define ASL_IT8728F_VIN4_STRING "IT8728F-VIN4"
#endif
#ifndef ASL_IT8728F_VIN5_STRING
    #define ASL_IT8728F_VIN5_STRING "IT8728F-VIN5"
#endif
#ifndef ASL_IT8728F_VIN6_STRING
    #define ASL_IT8728F_VIN6_STRING "IT8728F-VIN6"
#endif
#ifndef ASL_IT8728F_3VSB_STRING
    #define ASL_IT8728F_3VSB_STRING "IT8728F-3VSB"
#endif
#ifndef ASL_IT8728F_VBAT_STRING
    #define ASL_IT8728F_VBAT_STRING "IT8728F-VBAT"
#endif
#ifndef ASL_IT8728F_TEMP_SENSOR_NUMBER
    #define ASL_IT8728F_TEMP_SENSOR_NUMBER 0
#endif
#ifndef ASL_IT8728F_FAN_SENSOR_NUMBER
    #define ASL_IT8728F_FAN_SENSOR_NUMBER 0
#endif
#ifndef ASL_IT8728F_VOLT_SENSOR_NUMBER
    #define ASL_IT8728F_VOLT_SENSOR_NUMBER 0
#endif

//---------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//---------------------------------------------------------------------
IndexField(INDX, DATA, ByteAcc, NoLock, Preserve){
    Offset(0x71),
    RG71, 8,        //Watch Dog Timer Control Register
    RG72, 8,        //Watch Dog Timer Configuration Register
    RG73, 16,       //Watch Dog Timer Time-out Value (MSB) + (LSB) Register
    Offset(0xB8),
    RGB8, 8,        //GPIO Pin Set 1 Pin Internal Pull-up Enable Register
    RGB9, 8,        //GPIO Pin Set 2 Pin Internal Pull-up Enable Register
    RGBA, 8,        //GPIO Pin Set 3 Pin Internal Pull-up Enable Register
    RGBB, 8,        //GPIO Pin Set 4 Pin Internal Pull-up Enable Register
    RGBC, 8,        //GPIO Pin Set 5 Pin Internal Pull-up Enable Register
    RGBD, 8,        //GPIO Pin Set 6 Pin Internal Pull-up Enable Register
    Offset(0xC8),
    RGC8, 8,        //Simple I/O Set 1 Output Enable Register
    RGC9, 8,        //Simple I/O Set 2 Output Enable Register
    RGCA, 8,        //Simple I/O Set 3 Output Enable Register
    RGCB, 8,        //Simple I/O Set 4 Output Enable Register
    RGCC, 8,        //Simple I/O Set 5 Output Enable Register
    RGCD, 8,        //Simple I/O Set 6 Output Enable Register
    RGCE, 8,        //Simple I/O Set 7 Output Enable Register
    RGCF, 8,        //Simple I/O Set 8 Output Enable Register
}        //End of indexed field

#if ASL_IT8728F_GPIO_PORT_PRESENT
 //-----------------------------------------------------------------------
 // SIO GPIO I/O registers
 //-----------------------------------------------------------------------
 OperationRegion (IDIO, SystemIO, IO1B, IO1L)
 Field (IDIO, ByteAcc, NoLock, Preserve){
     GP1X, 8,    // GPIO Group 1
     GP2X, 8,    // GPIO Group 2
     GP3X, 8,    // GPIO Group 3
     GP4X, 8,    // GPIO Group 4
     GP5X, 8,    // GPIO Group 5
     GP6X, 8,    // GPIO Group 6
     GP7X, 8,    // GPIO Group 7
     GP8X, 8,    // GPIO Group 8
 } //end of indexed field

//---------------------------------------------------------------------------
// Name: D1GL
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
    Method (D1GL, 1) {
        Store(And(Arg0, 0xff), Local0)                          // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                         // pin bitmask
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        If (LEqual(Local1,1))
        {
            ShiftRight(And(GP1X, Local3), Local2, Local4)       // GP1x Pin Status Register (Base Address + 0)
        } ElseIf (LEqual(Local1,2))
        {
            ShiftRight(And(GP2X, Local3), Local2, Local4)       // GP2x Pin Status Register (Base Address + 1)
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(GP3X, Local3), Local2, Local4)       // GP3x Pin Status Register (Base Address + 2)
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(GP4X, Local3), Local2, Local4)       // GP4x Pin Status Register (Base Address + 3)
        } ElseIf (LEqual(Local1,5))
        {
            ShiftRight(And(GP5X, Local3), Local2, Local4)       // GP5x Pin Status Register (Base Address + 4)
        } ElseIf (LEqual(Local1,6))
        {
            ShiftRight(And(GP6X, Local3), Local2, Local4)       // GP6x Pin Status Register (Base Address + 5)
        } ElseIf (LEqual(Local1,7))
        {
            ShiftRight(And(GP7X, Local3), Local2, Local4)       // GP7x Pin Status Register (Base Address + 6)
        } ElseIf (LEqual(Local1,8))
        {
            ShiftRight(And(GP8X, Local3), Local2, Local4)       // GP8x Pin Status Register (Base Address + 7)
        }

        If ( LAnd(LNotEqual(Local4 , 0), LNotEqual(Local4 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local4)
    }

//---------------------------------------------------------------------------
// Name: D1SL
//
// Description:  DIO SIO1 Set Level
//   Arg0 : GPIO Number to set level
//   Arg1 : Level to set
//     0 - Low level
//     1 - High level
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SL, 2){
         Store(And(Arg0, 0xff), Local0)                         // Local1: DIO number
         Divide (Local0, 10, Local2, Local1)
         ShiftLeft(0x01, Local2, Local3)                        //pin bitmask
         // Local1 : Result : Super I/O Group number
         // Local2 : Remainder : Pin number in group 
         // Local3 : Pin bit map

         If (LEqual(Local1,1))
         {
             Or (And(GP1X,Not(Local3)), ShiftLeft(Arg1,Local2), GP1X)   // GP1x Pin Output Data Register (Base Address + 0)
         } ElseIf (LEqual(Local1,2))
         {
             Or (And(GP2X,Not(Local3)), ShiftLeft(Arg1,Local2), GP2X)   // GP2x Pin Output Data Register (Base Address + 1)
         } ElseIf (LEqual(Local1,3))
         {
             Or (And(GP3X,Not(Local3)), ShiftLeft(Arg1,Local2), GP3X)   // GP3x Pin Output Data Register (Base Address + 2)
         } ElseIf (LEqual(Local1,4))
         {
             Or (And(GP4X,Not(Local3)), ShiftLeft(Arg1,Local2), GP4X)   // GP4x Pin Output Data Register (Base Address + 3)
         } ElseIf (LEqual(Local1,5))
         {
             Or (And(GP5X,Not(Local3)), ShiftLeft(Arg1,Local2), GP5X)   // GP5x Pin Output Data Register (Base Address + 4)
         } ElseIf (LEqual(Local1,6))
         {
             Or (And(GP6X,Not(Local3)), ShiftLeft(Arg1,Local2), GP6X)   // GP6x Pin Output Data Register (Base Address + 5)
         } ElseIf (LEqual(Local1,7))
         {
             Or (And(GP7X,Not(Local3)), ShiftLeft(Arg1,Local2), GP7X)   // GP7x Pin Output Data Register (Base Address + 6)
         } ElseIf (LEqual(Local1,8))
         {
             Or (And(GP8X,Not(Local3)), ShiftLeft(Arg1,Local2), GP8X)   // GP8x Pin Output Data Register (Base Address + 7)
         }

         Return (ASL_BFPI_SUCCESS)
    }

//---------------------------------------------------------------------------
// Name: D1GD
//
// Description:  DIO SIO1 Get Direction
//   Arg0 : GPIO Number to get Direction
//
// Output:
//   Interger:
//   0 - Output
//   1 - Input
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (D1GD, 1) {
        Store(And(Arg0, 0xff), Local0)                             // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                            //pin bitmask
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group
        // Local3 : Pin bit map

        ENFG(ASL_IT8728F_LDN_GPIO)                                 //Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,1))
        {
            ShiftRight(And(RGC8, Local3), Local2, Local4)           // GP1x Pin Output Enable Register Index C8h
        } ElseIf (LEqual(Local1,2))
        {
            ShiftRight(And(RGC9, Local3), Local2, Local4)           // GP2x Pin Output Enable Register Index C9h
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(RGCA, Local3), Local2, Local4)           // GP3x Pin Output Enable Register Index CAh
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(RGCB, Local3), Local2, Local4)           // GP4x Pin Output Enable Register Index CBh
        } ElseIf (LEqual(Local1,5))
        {
            ShiftRight(And(RGCC, Local3), Local2, Local4)           // GP5x Pin Output Enable Register Index CCh
        } ElseIf (LEqual(Local1,6))
        {
            ShiftRight(And(RGCD, Local3), Local2, Local4)           // GP6x Pin Output Enable Register Index CDh
        } ElseIf (LEqual(Local1,7))
        {
            ShiftRight(And(RGCE, Local3), Local2, Local4)           // GP7x Pin Output Enable Register Index CEh
        } ElseIf (LEqual(Local1,8))
        {
            ShiftRight(And(RGCF, Local3), Local2, Local4)           // GP8x Pin Output Enable Register Index CFh
        }

        EXFG()                                                      // Exit Config Mode

        And(Not(Local4), 0x01, Local4)
        If ( LAnd(LNotEqual(Local4 , 0), LNotEqual(Local4 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local4)
    }

//---------------------------------------------------------------------------
// Name: D1SD
//
// Description:  DIO SIO1 Set Direction
//   Arg0 : GPIO Number to set Direction
//   Arg1 : Direction to set
//     0 - Output
//     1 - Input
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SD, 2){
        Store(And(Arg0, 0xff), Local0)                              // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                             // pin bitmask
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map

        And(Not(Arg1), 0x01, Arg1)

        ENFG(ASL_IT8728F_LDN_GPIO)                                  //Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,1))
        {
            Or (And(RGC8,Not(Local3)), ShiftLeft(Arg1,Local2), RGC8)    // GP1x Pin Output Enable Register Index C8h
        } ElseIf (LEqual(Local1,2))
        {
            Or (And(RGC9,Not(Local3)), ShiftLeft(Arg1,Local2), RGC9)    // GP2x Pin Output Enable Register Index C9h
        } ElseIf (LEqual(Local1,3))
        {
            Or (And(RGCA,Not(Local3)), ShiftLeft(Arg1,Local2), RGCA)    // GP3x Pin Output Enable Register Index CAh
        } ElseIf (LEqual(Local1,4))
        {
            Or (And(RGCB,Not(Local3)), ShiftLeft(Arg1,Local2), RGCB)    // GP4x Pin Output Enable Register Index CBh
        } ElseIf (LEqual(Local1,5))
        {
            Or (And(RGCC,Not(Local3)), ShiftLeft(Arg1,Local2), RGCC)    // GP5x Pin Output Enable Register Index CCh
        } ElseIf (LEqual(Local1,6))
        {
            Or (And(RGCD,Not(Local3)), ShiftLeft(Arg1,Local2), RGCD)    // GP6x Pin Output Enable Register Index CDh
        } ElseIf (LEqual(Local1,7))
        {
            Or (And(RGCE,Not(Local3)), ShiftLeft(Arg1,Local2), RGCE)    // GP7x Pin Output Enable Register Index CEh
        } ElseIf (LEqual(Local1,8))
        {
            Or (And(RGCF,Not(Local3)), ShiftLeft(Arg1,Local2), RGCF)    // GP8x Pin Output Enable Register Index CFh
        }

        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }

//---------------------------------------------------------------------------
// Name: D1GO
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
    Method (D1GO, 1) {
        Store(And(Arg0, 0xff), Local0)                             // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                            //pin bitmask
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        If (LGreater(Local1, 6))                                   // IT8728F only supports GPIO Pin Set 1, 2, 3, 4, 5
        { Return (ASL_BFPI_NOT_SUPPORTED) }                        // and 6 Pin Internal Pull-up Enable

        ENFG(ASL_IT8728F_LDN_GPIO)                                 // Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,1))
        {
            ShiftRight(And(RGB8, Local3), Local2, Local4)           // GPIO Pin Set 1 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,2))
        {
            ShiftRight(And(RGB9, Local3), Local2, Local4)           // GPIO Pin Set 2 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(RGBA, Local3), Local2, Local4)           // GPIO Pin Set 3 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(RGBB, Local3), Local2, Local4)           // GPIO Pin Set 4 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,5))
        {
            If (LGreaterEqual(Local2,6) ) {
                Return (ASL_BFPI_NOT_SUPPORTED)                     // GP56 and GP57 Not Supported Internal Pull-up Enable
            }
            ShiftRight(And(RGBC, Local3), Local2, Local4)           // GPIO Pin Set 5 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,6))
        {
            If (LLessEqual(Local2,1) ) {
                Return (ASL_BFPI_NOT_SUPPORTED)                     // GP60 and GP61 Not Supported Internal Pull-up Enable
            }
            ShiftRight(And(RGBD, Local3), Local2, Local4)           // GPIO Pin Set 6 Pin Internal Pull-up Enable Register
        }

        EXFG()                                                      // Exit Config Mode

        If ( LAnd(LNotEqual(Local4 , 0), LNotEqual(Local4 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local4)
    }

//---------------------------------------------------------------------------
// Name: D1SO
//
// Description:  OEM GPIO Set Driving
//   Arg0 : GPIO Number to set Driving
//   Arg1 : Driving to set
//     0: Open drain
//     1: Push pull
//     2: T.B.D.
//     3: T.B.D.
//     4: T.B.D.
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SO, 2){
        Store(And(Arg0, 0xff), Local0)                              // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                             // pin bitmask
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        If (LGreater(Local1, 6))                                    // IT8728F only supports GPIO Pin Set 1, 2, 3, 4, 5
        { Return (ASL_BFPI_NOT_SUPPORTED) }                         // and 6 Pin Internal Pull-up Enable

        ENFG(ASL_IT8728F_LDN_GPIO)                                  //Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,1))
        {
            Or (And(RGB8,Not(Local3)), ShiftLeft(Arg1,Local2), RGB8)    // GPIO Pin Set 1 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,2))
        {
            Or (And(RGB9,Not(Local3)), ShiftLeft(Arg1,Local2), RGB9)    // GPIO Pin Set 2 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,3))
        {
            Or (And(RGBA,Not(Local3)), ShiftLeft(Arg1,Local2), RGBA)    // GPIO Pin Set 3 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,4))
        {
            Or (And(RGBB,Not(Local3)), ShiftLeft(Arg1,Local2), RGBB)    // GPIO Pin Set 4 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,5))
        {
            If (LGreaterEqual(Local2,6) ) {
                Return (ASL_BFPI_NOT_SUPPORTED)                         // GP56 and GP57 Not Supported Internal Pull-up Enable
            }
            Or (And(RGBC,Not(Local3)), ShiftLeft(Arg1,Local2), RGBC)    // GPIO Pin Set 5 Pin Internal Pull-up Enable Register
        } ElseIf (LEqual(Local1,6))
        {
            If (LLessEqual(Local2,1) ) {
                Return (ASL_BFPI_NOT_SUPPORTED)                         // GP60 and GP61 Not Supported Internal Pull-up Enable
            }
            Or (And(RGBD,Not(Local3)), ShiftLeft(Arg1,Local2), RGBD)    // GPIO Pin Set 6 Pin Internal Pull-up Enable Register
        }

        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }
#endif // ASL_IT8728F_GPIO_PORT_PRESENT

#if ASL_IT8728F_WDT_BFPI_SUPPORT
//---------------------------------------------------------------------------
// Name: W1RC
//
// Description:  SIO WDT report capability - Max timeout
//
// Output:
//   Interger: Max timeout value in ms
//
//---------------------------------------------------------------------------
    Method (W1RC, 0) {
        Return (ASL_SIO_WDT_MAX_TIMEOUT)
    }

//---------------------------------------------------------------------------
// Name: W1GT
//
// Description:  SIO WDT Get timeout
//
// Output:
//   Interger: Remained timeout value in ms
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (W1GT, 0) {
        // IT8728F Watch Dog Timer Time-out Value registers
        // does not change during countdown.
        Return (ASL_BFPI_NOT_SUPPORTED)
    }

//---------------------------------------------------------------------------
// Name: W1ST
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
    Method (W1ST, 1){
        // Validate input
        If (LGreater(Arg0, ASL_SIO_WDT_MAX_TIMEOUT)) { 
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Store (0, Local0)
        Store (0, Local1)
        // Local0 : time-out to set to WDT 
        // Local1 : temporal for remainder from divide operation 
        // Default Second / Normal mode

        // Calculate counter and mode to set
        // RG71 : Current time-out counter
        //   [0] : WDT Status -> 0 - WDT value is not is equal to 0
        //                    -> 1 - WDT value is equal to 0
        //
        // RG72 : Watch Dog Timer Configuration Register
        //   [7] : WDT Time-out Value Select -> 0 - Minute
        //                                   -> 1 - Second
        //   [6] : WDT Output through KRST (pulse) Enable -> 0 - Disable
        //                                                -> 1 - Enable
        //   [5] : WDT Time-out Value Extra Select -> 0 - Determined by WDT Time-out value select 1 (bit 7 of this register)
        //                                            1 - 62.5ms x WDT Timer-out value
        //   [4] : WDT Output through PWRGD Enable -> 0 - Disable
        //                                         -> 1 - Enable
        //
        // RG73 : Watch Dog Timer Time-out Value (LSB) Register
        //   [7-0] : WDT Time-out Value 7-0
        //
        // RG74 : Watch Dog Timer Time-out Value (MSB) Register
        //   [7-0] : WDT Time-out Value 15-8

        ENFG(ASL_IT8728F_LDN_GPIO)        //Enter Config Mode, Select GPIO LDN
                
        If (LGreater(Arg0, 0))
        {
            Divide (Arg0, 1000, Local1, Local0)
            // Convert ms to sec
            // Local0 : time-out in second
            // Local1 : time-out remainder in ms

            If (LGreater(Local1, 0))
            {
                Increment(Local0)
            }

            If (LLessEqual(Local0, 65535)) //If Local0 < or = 65535s
            {
                Or(RG72, 0x80, RG72)  // WDT CFG register [7] = 1 : Second Mode
            }
            Else
            {
                // Convert Sec to Minute
                // Local0 : time-out in Minute
                // Local1 : time-out remainder in ms
                Divide (Local0, 60, Local1, Local0)
                If (LGreater(Local1, 0))
                {
                    Increment(Local0)
                }
                And(RG72, 0x7F, RG72)  // WDT Cfg Register [7] = 0 : Minute Mode
            }
            And(RG71, 0xFE, RG71) // Clear WDT Status bit
            Or(And(RG72, 0xDF), 0x50, RG72) // Countdown in Second/Minute mode and Output through KRST/PWRGD
            Store(Local0, RG73) // Set time-out counter and start countdown
        }
        Else
        {
            Store (0, RG73)         // Set time-out counter to 0 to disable Watch Dog
        }
        
        EXFG()        // Exit Config Mode
        Return (ASL_BFPI_SUCCESS)
    }
#endif  //ASL_IT8728F_WDT_BFPI_SUPPORT

#if  ASL_IT8728F_HWM_PRESENT
//---------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//---------------------------------------------------------------------
OperationRegion(IOHW,   // Name of Operation Region for SuperIO device
    SystemIO,           // Type of address space
    IO3B,               // Offset to start of region
    8)                  // Size of region in bytes
                        // End of Operation Region
Field(IOHW, ByteAcc, NoLock,Preserve){
    Offset(5),
    HWMI, 8,            // Hardware Monitor Base Address + 5
    HWMD, 8             // Hardware Monitor Base Address + 6
}

//---------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//---------------------------------------------------------------------
IndexField(HWMI, HWMD, ByteAcc, NoLock, Preserve){
    Offset(0x00),
    HW00, 8,
    HW01, 8,
    HW02, 8,
    HW03, 8,
    HW04, 8,
    HW05, 8,
    HW06, 8,
    HW07, 8,
    HW08, 8,
    HW09, 8,
    HW0A, 8,
    HW0B, 8,
    HW0C, 8,
    HW0D, 8,
    HW0E, 8,
    HW0F, 8,
    Offset(0x10),
    HW10, 8,
    HW11, 8,
    HW12, 8,
    HW13, 8,
    HW14, 8,
    HW15, 8,
    HW16, 8,
    HW17, 8,
    HW18, 8,
    HW19, 8,
    HW1A, 8,
    HW1B, 8,
    HW1C, 8,
    HW1D, 8,
    Offset(0x20),
    HW20, 8,
    HW21, 8,
    HW22, 8,
    HW23, 8,
    HW24, 8,
    HW25, 8,
    HW26, 8,
    HW27, 8,
    HW28, 8,
    HW29, 8,
    HW2A, 8,
    HW2B, 8,
    Offset(0x30),
    HW30, 8,
    HW31, 8,
    HW32, 8,
    HW33, 8,
    HW34, 8,
    HW35, 8,
    HW36, 8,
    HW37, 8,
    HW38, 8,
    HW39, 8,
    HW3A, 8,
    HW3B, 8,
    HW3C, 8,
    HW3D, 8,
    HW3E, 8,
    HW3F, 8,
    Offset(0x40),
    HW40, 8,
    HW41, 8,
    HW42, 8,
    HW43, 8,
    HW44, 8,
    HW45, 8,
    Offset(0x50),
    HW50, 8,
    HW51, 8,
    HW52, 8,
    HW53, 8,
    HW54, 8,
    HW55, 8,
    HW56, 8,
    HW57, 8,
    HW58, 8,
    HW59, 8,
    Offset(0x5B),
    HW5B, 8,
    HW5C, 8,
    HW5D, 8,
    HW5E, 8,
    HW5F, 8,
    Offset(0x60),
    HW60, 8,
    HW61, 8,
    HW62, 8,
    HW63, 8,
    HW64, 8,
    HW65, 8,
    HW66, 8,
    Offset(0x68),
    HW68, 8,
    HW69, 8,
    HW6A, 8,
    HW6B, 8,
    HW6C, 8,
    HW6D, 8,
    HW6E, 8,
    Offset(0x70),
    HW70, 8,
    HW71, 8,
    HW72, 8,
    HW73, 8,
    HW74, 8,
    HW75, 8,
    HW76, 8,
    Offset(0x80),
    HW80, 8,
    HW81, 8,
    HW82, 8,
    HW83, 8,
    HW84, 8,
    HW85, 8,
    HW86, 8,
    HW87, 8,
    HW88, 8,
    HW89, 8,
    HW8A, 8,
    HW8B, 8,
    HW8C, 8,
    HW8D, 8,
    HW8E, 8,
    HW8F, 8,
    Offset(0x90),
    HW90, 8,
    HW91, 8,
    HW92, 8,
    HW93, 8,
    HW94, 8,
    HW95, 8,
    HW96, 8,
    HW97, 8,
    HW98, 8,
    HW99, 8,
    Offset(0x9C),
    HW9C, 8,
    HW9D, 8,
    HW9E, 8,
    HW9F, 8,
}

//---------------------------------------------------------------------------
// Name: HCVT
//
// Description:  SIO HWM convert Temperature reading to mdC (mini-degree-C)
//   Arg0 : Temperature reading
//   Arg1 : Temperature reading format
//     0 - 8 bits with unit 1 dC (degree-C)
//     1 - 9 bits with unit 0.5 dC
//
// Output:
//   INT32 Temperature reading in mdC
//
//---------------------------------------------------------------------------
    Method (HCVT, 2){
        Store (Arg0, Local0)
        // Local0: Reading value
        // Local1: Signed bit
        // 0 - Positive
        // 1 - Negative
        If (LEqual(Arg1,0)){
            Store (And(ShiftRight(Local0,7),0x01), Local1)
            If (LEqual(Local1, 1)) {
                // Transfer to positive value
                Subtract (0xFF, Local0, Local0)
                Increment (Local0)
            }
            Multiply (Local0, 1000, Local0)  // dC to mdC
        }
        Else {
            Store (And(ShiftRight(Local0,8),0x01), Local1)
            If (LEqual(Local1, 1)) {
                // Transfer to positive value
                Subtract (0x1FF, Local0, Local0)
                Increment (Local0)
            }
            Multiply (Local0, 500, Local0)  // 0.5dC to mdC
        }

        // Transform to INT32
        If (LEqual(Local1, 1)) {
            // Transfer back to negative value
            Subtract (0xFFFFFFFF, Local0, Local0)
            Increment (Local0)
        }
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVF
//
// Description:  SIO HWM convert FAN reading to RPM
//   Arg0 : FAN reading
//   Arg1 : Divisor register value
//     0 - Divisor is 1
//     1 - Divisor is 2
//     2 - Divisor is 4
//     3 ...
//
// Output:
//   FAN speed in RPM
//
//---------------------------------------------------------------------------
    Method (HCVF, 2){
        // Check input to prevent divide 0
        If (LEqual(Arg0, 0xFFFF)) { Return (0) }
        If (LEqual(Arg0, 0)) { Return (0) }

        // Calculate actual divisor number
        Store (One, Local0)
        ShiftLeft (Local0, Arg1, Local0)
        
        // Speed = 1350000/(Divisor*Reading);
        Multiply (Arg0, Local0, Local0)
        Divide (1350000, Local0, , Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVV
//
// Description:  SIO HWM convert Voltage reading to mini-volt
//   Arg0 : Voltage reading
//   Arg1 : Ra value, resistor to power
//   Arg2 : Rb value, resistor to ground
//
// Output:
//   Voltage in mini-volt
//
//---------------------------------------------------------------------------
    Method (HCVV, 3){
        Multiply (Arg0, 12, Local0)  // reading unit is 12mV

        // Return directly if it doesn't use resistor divisor
        If (LEqual(Arg1, 0)) { Return (Local0) }
        // Check input to prevent divide 0
        If (LEqual(Arg2, 0)) { Return (Local0) }

        // Voltage = Reading * 12mV * (Ra + Rb) / Rb
        Multiply (Local0, Add(Arg1, Arg2), Local0)
        Divide (Local0, Arg2, , Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: H1SN
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
    Method (H1SN, 1){
        Store (0, Local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            Store (ASL_IT8728F_TEMP_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            Store (ASL_IT8728F_FAN_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            Store (ASL_IT8728F_VOLT_SENSOR_NUMBER, Local0)
        }
        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    THTS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
Name(THTS, Package() {
#if ASL_IT8728F_TMPIN1_SUPPORT
    ASL_IT8728F_TMPIN1_STRING,
#endif // IT8728F_TMPIN1_SUPPORT
#if ASL_IT8728F_TMPIN2_SUPPORT
    ASL_IT8728F_TMPIN2_STRING,
#endif // IT8728F_TMPIN2_SUPPORT
#if ASL_IT8728F_TMPIN3_SUPPORT
    ASL_IT8728F_TMPIN3_STRING,
#endif // IT8728F_TMPIN3_SUPPORT
})

//------------------------------------------------------------------------
// Table:    THFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
Name(THFS, Package() {
#if ASL_FAN_TAC_1
    ASL_IT8728F_FAN_1_STRING,
#endif // FAN_TAC_1
#if ASL_FAN_TAC_2
    ASL_IT8728F_FAN_2_STRING,
#endif // FAN_TAC_2
#if ASL_FAN_TAC_3
    ASL_IT8728F_FAN_3_STRING,
#endif // FAN_TAC_3
#if ASL_FAN_TAC4_EN
    ASL_IT8728F_FAN_4_STRING,
#endif // FAN_TAC4_EN
#if ASL_FAN_TAC5_EN
    ASL_IT8728F_FAN_5_STRING,
#endif // FAN_TAC5_EN
})

//------------------------------------------------------------------------
// Table:    THVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
Name(THVS, Package() {
#if ASL_IT8728F_VIN0_SUPPORT
    ASL_IT8728F_VIN0_STRING,
#endif // IT8728F_VIN0_SUPPORT
#if ASL_IT8728F_VIN1_SUPPORT
    ASL_IT8728F_VIN1_STRING,
#endif // IT8728F_VIN1_SUPPORT
#if ASL_IT8728F_VIN2_SUPPORT
    ASL_IT8728F_VIN2_STRING,
#endif // IT8728F_VIN2_SUPPORT
#if ASL_IT8728F_VIN3_SUPPORT
    ASL_IT8728F_VIN3_STRING,
#endif // IT8728F_VIN3_SUPPORT
#if ASL_IT8728F_VIN4_SUPPORT
    ASL_IT8728F_VIN4_STRING,
#endif // IT8728F_VIN4_SUPPORT
#if ASL_IT8728F_VIN5_SUPPORT
    ASL_IT8728F_VIN5_STRING,
#endif // IT8728F_VIN5_SUPPORT
#if ASL_IT8728F_VIN6_SUPPORT
    ASL_IT8728F_VIN6_STRING,
#endif // IT8728F_VIN6_SUPPORT
#if ASL_IT8728F_3VSB_SUPPORT
    ASL_IT8728F_3VSB_STRING,
#endif // IT8728F_3VSB_SUPPORT
#if ASL_IT8728F_VBAT_SUPPORT
    ASL_IT8728F_VBAT_STRING,
#endif // IT8728F_VBAT_SUPPORT
})

//---------------------------------------------------------------------------
// Name: H1SS
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
//   "NULL" if not found
//
//---------------------------------------------------------------------------
    Method (H1SS, 2){
        Store ("NULL", Local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            If (LLess(Arg1, SizeOf(THTS))) {
              Store (DerefOf(Index(THTS, Arg1)), Local0)
            }
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            If (LLess(Arg1, SizeOf(THFS))) {
              Store (DerefOf(Index(THFS, Arg1)), Local0)
            }
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            If (LLess(Arg1, SizeOf(THVS))) {
              Store (DerefOf(Index(THVS, Arg1)), Local0)
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
        Store ("", Local0)
        Store (ONE, Local1)
        Store (0, Local2)    // Sensor number
        Store (0, Local3)    // Counter

        Store (H1SN(Arg0), Local2)    // Sensor number

        While (LLess(Local3, Local2)) {
            If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (H1SS(Arg0, Local3), "\"", ), ), Local0)
            Increment (Local3)
        }
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: H1RS
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
//   Refer to IT8728FExternalFunList in IT8728FHwmSetup.c.
//---------------------------------------------------------------------------
    Method (H1RS, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)
        If (LEqual(Arg0, 0)) {
          // Temperature
          #if ASL_IT8728F_TMPIN1_SUPPORT
            If (LEqual(Arg1, ASL_IT8728F_TMPIN1_STRING)) {  // TEMP1 - TMPIN1 Temperature
                Store (HW29, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
          #else
            If (LNotEqual(Arg0, 0)) {   // Should not be TRUE always
            }
          #endif // ASL_IT8728F_TMPIN1_SUPPORT
          #if ASL_IT8728F_TMPIN2_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_TMPIN2_STRING)) {  // TEMP2 - TMPIN2 Temperature
                Store (HW2A, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
          #endif // ASL_IT8728F_TMPIN2_SUPPORT
          #if ASL_IT8728F_TMPIN3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_TMPIN3_STRING)) {  // TEMP3 - TMPIN3 Temperature
                Store (HW2B, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
          #endif // ASL_IT8728F_TMPIN3_SUPPORT
        } ElseIf (LEqual(Arg0, 1)) {
          // Fan
          #if ASL_FAN_TAC_1
            If (LEqual(Arg1, ASL_IT8728F_FAN_1_STRING)) {               // FAN1
                ShiftLeft(HW18, 8, Local0)                              // Get FAN1 count reading MSB
                Or(HW0D, Local0, Local0)                                // Get FAN1 count reading LSB
                Store (1, Local1)                                       // Local1 : Default Divisor = 2
                Store (HCVF (Local0, Local1), Local0)
            }
          #else
            If (LNotEqual(Arg0, 1)) {   // Should not be TRUE always
            }
          #endif // ASL_FAN_TAC_1
          #if ASL_FAN_TAC_2
            ElseIf (LEqual(Arg1, ASL_IT8728F_FAN_2_STRING)) {           // FAN2
                ShiftLeft(HW19, 8, Local0)                              // Get FAN2 count reading MSB
                Or(HW0E, Local0, Local0)                                // Get FAN2 count reading LSB
                Store (1, Local1)                                       // Local1 : Default Divisor = 2
                Store (HCVF (Local0, Local1), Local0)
            }
          #endif // ASL_FAN_TAC_2
          #if ASL_FAN_TAC_3
            ElseIf (LEqual(Arg1, ASL_IT8728F_FAN_3_STRING)) {           // FAN3
                ShiftLeft(HW1A, 8, Local0)                              // Get FAN3 count reading MSB
                Or(HW0F, Local0, Local0)                                // Get FAN3 count reading LSB
                Store (1, Local1)                                       // Local1 : Default Divisor = 2
                Store (HCVF (Local0, Local1), Local0)
            }
          #endif // ASL_FAN_TAC_3
          #if ASL_FAN_TAC4_EN
            ElseIf (LEqual(Arg1, ASL_IT8728F_FAN_4_STRING)) {           // FAN4
                ShiftLeft(HW81, 8, Local0)                              // Get FAN4 count reading MSB
                Or(HW80, Local0, Local0)                                // Get FAN4 count reading LSB
                Store (1, Local1)                                       // Local1 : Default Divisor = 2
                Store (HCVF (Local0, Local1), Local0)
            }
          #endif // ASL_FAN_TAC4_EN
          #if ASL_FAN_TAC5_EN
            ElseIf (LEqual(Arg1, ASL_IT8728F_FAN_5_STRING)) {           // FAN5
                ShiftLeft(HW83, 8, Local0)                              // Get FAN5 count reading MSB
                Or(HW82, Local0, Local0)                                // Get FAN5 count reading LSB
                Store (1, Local1)                                       // Local1 : Default Divisor = 2
                Store (HCVF (Local0, Local1), Local0)
            }
          #endif // ASL_FAN_TAC5_EN
        } ElseIf (LEqual(Arg0, 2)) {
          // Voltage
          #if ASL_IT8728F_VIN0_SUPPORT
            If (LEqual(Arg1, ASL_IT8728F_VIN0_STRING)) {           // VIN0
                Store (HW20, Local0)
                Store( HCVV (Local0, ASL_VIN0_RA, ASL_VIN0_RB), Local0)
            }
          #else
            If (LNotEqual(Arg0, 2)) {   // Should not be TRUE always
            }
          #endif // ASL_IT8728F_VIN0_SUPPORT
          #if ASL_IT8728F_VIN1_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN1_STRING)) {       // VIN1
                Store (HW21, Local0)
                Store( HCVV (Local0, ASL_VIN1_RA, ASL_VIN1_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN1_SUPPORT
          #if ASL_IT8728F_VIN2_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN2_STRING)) {       // VIN2
                Store (HW22, Local0)
                Store( HCVV (Local0, ASL_VIN2_RA, ASL_VIN2_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN2_SUPPORT
          #if ASL_IT8728F_VIN3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN3_STRING)) {       // VIN3
                Store (HW23, Local0)
                Store( HCVV (Local0, ASL_VIN3_RA, ASL_VIN3_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN3_SUPPORT
          #if ASL_IT8728F_VIN4_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN4_STRING)) {       // VIN4
                Store (HW24, Local0)
                Store( HCVV (Local0, ASL_VIN4_RA, ASL_VIN4_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN4_SUPPORT
          #if ASL_IT8728F_VIN5_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN5_STRING)) {       // VIN5
                Store (HW25, Local0)
                Store( HCVV (Local0, ASL_VIN5_RA, ASL_VIN5_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN5_SUPPORT
          #if ASL_IT8728F_VIN6_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VIN6_STRING)) {       // VIN6
                Store (HW26, Local0)
                Store( HCVV (Local0, ASL_VIN6_RA, ASL_VIN6_RB), Local0)
            }
          #endif // ASL_IT8728F_VIN6_SUPPORT
          #if ASL_IT8728F_3VSB_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_3VSB_STRING)) {       // 3VSB
                Store (HW27, Local0)
                Store( HCVV (Local0, 0, 1), Local0)
                Multiply (Local0, 2, Local0)
            }
          #endif // ASL_IT8728F_3VSB_SUPPORT
          #if ASL_IT8728F_VBAT_SUPPORT
            ElseIf (LEqual(Arg1, ASL_IT8728F_VBAT_STRING)) {       // VBAT
                Store (HW28, Local0)
                Store( HCVV (Local0, 0, 1), Local0)
                Multiply (Local0, 2, Local0)
            }
          #endif // ASL_IT8728F_VBAT_SUPPORT
        }
        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    THFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
Name(THFC, Package() {
#if ASL_IT8728_SMF1_SUPPORT
    ASL_IT8728F_FAN_1_STRING,
#endif // IT8728_SMF1_SUPPORT
#if ASL_IT8728_SMF2_SUPPORT
    ASL_IT8728F_FAN_2_STRING,
#endif // IT8728_SMF2_SUPPORT
#if ASL_IT8728_SMF3_SUPPORT
    ASL_IT8728F_FAN_3_STRING,
#endif // IT8728_SMF3_SUPPORT
})

//---------------------------------------------------------------------------
// Name: F1FS
//
// Description:  SMF report controller name string
//   Arg0 : Index of Controller to return name string
//
// Output:
//   String - Name string of specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (F1FS, 1){
    Store ("NULL", Local0)

    If (LLess(Arg0, SizeOf(THFC))) {
      Store (DerefOf(Index(THFC, Arg0)), Local0)
    }

    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: F1RN
//
// Description:  SIO SMF report FAN number
//
// Output:
//   Integer - Total smart FAN number supported by this SIO
//   
//---------------------------------------------------------------------------
    Method (F1RN, 0){
        Return (ASL_IT8728F_SMF_NUMBER)
    }

//---------------------------------------------------------------------------
// Name: F1RL
//
// Description:  SIO SMF Report name list
//
// Input: N/A
//
// Output:
//   String : A list of FAN names that supported Smart FAN from this SIO, seperated by comma.
//
//---------------------------------------------------------------------------
    Method (F1RL, 0){
        Store ("", Local0)
        Store (ONE, Local1)
        Store (F1RN, Local2)    // SMF number
        Store (0, Local3)    // Counter

        // Return a list of FAN names that supported Smart FAN from this SOP, seperated by comma.
        While (LLess(Local3, Local2)) {
            If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (F1FS(Local3), "\"", ), ), Local0)
            Increment (Local3)
        }

        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    TSEL
// Description: Select the temperature source for controlling FAN
//-------------------------------------------------------------------------
    Name(TSEL, Package() {
        ASL_IT8728F_TMPIN1_STRING,
        ASL_IT8728F_TMPIN2_STRING,
        ASL_IT8728F_TMPIN3_STRING,
    })

//---------------------------------------------------------------------------
// Name: F1TS
//
// Description:  SMF report name string for target temperature
//   Arg0 : String - FAN name to return
//
// Output:
//   String - Name string of target temperature for specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
    Method (F1TS, 1){
        Store ("NULL", Local0)

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
              Store (DerefOf(Index(TSEL, And(HW15,0x03))), Local0)
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
              Store (DerefOf(Index(TSEL, And(HW16,0x03))), Local0)
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
              Store (DerefOf(Index(TSEL, And(HW17,0x03))), Local0)
          }
        #endif // IT8728_SMF3_SUPPORT
    
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1RM
//
// Description:  SMF report FAN mode
//   Arg0 : FAN index
//
// Output:
//   Integer - Bitmap for supported FAN mode.
//               bit 0 - Manual mode
//               bit 1 - Linear mode (Points-linear mode)
//               bit 2 - Slope-linear mode Supported
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-linear mode is not supported
//
//---------------------------------------------------------------------------
    Method (F1RM, 1){
        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
            Return (0x5)
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
            Return (0x5)
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
            Return (0x5)
          }
        #endif // IT8728_SMF3_SUPPORT

        Return(ASL_BFPI_NOT_SUPPORTED)
    }

//---------------------------------------------------------------------------
// Name: F1PW
//
// Description:  SMF report Max. PWM value for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Max. PWM value supported.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-linear mode is not supported
//
//---------------------------------------------------------------------------
    Method (F1PW, 1){
        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
            Return (ASL_IT8728_SMF_MAX_DUTY)
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
            Return (ASL_IT8728_SMF_MAX_DUTY)
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
            Return (ASL_IT8728_SMF_MAX_DUTY)
          }
        #endif // IT8728_SMF3_SUPPORT

        Return(ASL_BFPI_NOT_SUPPORTED)
    }

//---------------------------------------------------------------------------
// Name: F1LP
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
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-linear mode is not supported
//
//---------------------------------------------------------------------------
    Method (F1LP, 1){
        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
            Return (0x0F16)  // Step Value as 1, Max Slope Value as 15
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
            Return (0x0F16)  // Step Value as 1, Max Slope Value as 15
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
            Return (0x0F16)  // Step Value as 1, Max Slope Value as 15
          }
        #endif // IT8728_SMF3_SUPPORT
        
        Return (ASL_BFPI_NOT_SUPPORTED)
    }

//---------------------------------------------------------------------------
// Name: F1RC
//
// Description:  SIO SMF Report capability
//
// Input:
//   Arg0 : String - FAN name string to report capability
//
// Output:
//   String : Return correspond Smart FAN functionality in JSON format. Return "NULL" if no FAN matches the name.
//
//---------------------------------------------------------------------------
    Method (F1RC, 1){
        Store ("NULL", Local0)  // String to return
        Store (F1TS(Arg0), Local1)  // Name string for target temperature

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
            Store (ASL_IT8728F_SMFC_FAN_1_PREFIX, Local0)
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
            Store (ASL_IT8728F_SMFC_FAN_2_PREFIX, Local0)
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
            Store (ASL_IT8728F_SMFC_FAN_3_PREFIX, Local0)
          }
        #endif // IT8728_SMF3_SUPPORT

        Concatenate (Local0, Local1, Local0)
        Concatenate (Local0, ASL_IT8728F_SMFC_FANOUT_SUFFIX, Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1GM
//
// Description:  SIO SMF get mode
//   Arg0 : SMF name to get
//
// Output:
//   Integer :
//     Bit[3:0]: Fan Mode
//       0 - Manual mode
//       1 - Linear mode (This SIO is not supported)
//       2 - Slope-Linear mode
//     Bit[7:4]: Reserved Bits
//     Bit[15:8]: (valid only for manual mode) Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
    Method (F1GM, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
              And(HW15, 0x80, Local1)                     // Index 15h Bit[7]: FAN_CTL1 PWM Mode
              If (LEqual(Local1, 0x80)) {                 // Bit[7] = 1b : Automatic operation
                  Store(2, Local0)
              }
              Else {                                      // Bit[7] = 0b : Software operation
                  Store (0, Local0)
                  Or (Local0, ShiftLeft(HW63, 8), Local0) // Index 63h: FAN_CTL1 duty value
              }
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
              And(HW16, 0x80, Local1)                     // Index 16h Bit[7]: FAN_CTL2 PWM Mode
              If (LEqual(Local1, 0x80)) {                 // Bit[7] = 1b : Automatic operation
                  Store (2, Local0)
              }
              Else {                                      // Bit[7] = 0b : Software operation
                  Store (0, Local0)
                  Or (Local0, ShiftLeft(HW6B, 8), Local0) // Index 6Bh: FAN_CTL2 duty value
              }
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
              And(HW17, 0x80, Local1)                     // Index 17h Bit[7]: FAN_CTL3 PWM Mode
              If (LEqual(Local1, 0x80)) {                 // Bit[7] = 1b : Automatic operation
                  Store (2, Local0)
              }
              Else {                                      // Bit[7] = 0b : Software operation
                  Store (0, Local0)
                  Or (Local0, ShiftLeft(HW73, 8), Local0) // Index 73h: FAN_CTL3 duty value
              }
          }
        #endif // IT8728_SMF3_SUPPORT

        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1SM
//
// Description:  SIO SMF set mode
//   Arg0 : SMF name to set
//   Arg1 : SMF mode to set
//       0 - Manual mode
//       1 - Linear mode (This SIO is not supported)
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
//
//---------------------------------------------------------------------------
    Method (F1SM, 3){
        If (LAnd(LEqual(Arg1, 0), LGreater(Arg2, ASL_IT8728_SMF_MAX_DUTY))) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }

        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
              And(HW15, 0x7F, Local1)     // Index 15 Bit[7]: FAN_CTL1 PWM Mode
              If (LEqual(Arg1, 0)) {      // If Manual Mode
                  Store(Arg2, HW63)       // Index 63 Bit[7:0] : FAN_CTL1 PWM value
                  Store(Local1, HW15)     // Index 15 Bit[7] = 0b : Software operation
              }
              Else {
                  Or(Local1, 0x80, HW15)  // Index 15 Bit[7] = 1b : Automatic operation
              }
              Store (ASL_BFPI_SUCCESS, Local0)
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
              And(HW16, 0x7F, Local1)     // Index 16 Bit[7]: FAN_CTL2 PWM Mode
              If (LEqual(Arg1, 0)) {      // If Manual Mode
                  Store(Arg2, HW6B)       // Index 6B Bit[7:0] : FAN_CTL2 PWM value
                  Store(Local1, HW16)     // Index 16 Bit[7] = 0b : Software operation
              }
              Else {
                  Or(Local1, 0x80, HW16)  // Index 16 Bit[7] = 1b : Automatic operation
              }
              Store (ASL_BFPI_SUCCESS, Local0)
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
              And(HW17, 0x7F, Local1)     // Index 17 Bit[7]: FAN_CTL3 PWM Mode
              If (LEqual(Arg1, 0)) {      // If Manual Mode
                  Store(Arg2, HW73)       // Index 73 Bit[7:0] : FAN_CTL3 PWM value
                  Store(Local1, HW17)     // Index 17 Bit[7] = 0b : Software operation
              }
              Else {
                  Or(Local1, 0x80, HW17)  // Index 17 Bit[7] = 1b : Automatic operation
              }
              Store (ASL_BFPI_SUCCESS, Local0)
          }
        #endif // IT8728_SMF3_SUPPORT

        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1GP
//
// Description:  SIO SMF control get control point configuration
//   Arg0 : SMF name to get
//   Arg1 : control point to get
//     0 - lowest point
//     1 - highest point (This SIO is not supported)
//     2 - Slope
//     3 - secondary low point (Not support)
//
// Output:
//   Integer :
//     For Temp. point -
//       Bit[7:0]: DutyCycle coordinate for this pont
//         0 - 0% duty
//         X - (X/Max)% duty
//         Max - 100% duty
//       Bit[16:8]: Temperature coordinate for this pont
//         0~255
//     For Slope -
//       Bit[7:0]: Digit part after point, of slope. in 1/256
//       Bit[15:8]: Integer part of slope
//     BFPI_NOT_SUPPORTED: No FAN matches name provided.
//
//---------------------------------------------------------------------------
    Method (F1GP, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
              // SmartGuardian Automatic Mode works quite differently with linear mode.
              // It has no exact temperature and duty setting. So we keep point coordination in ASL name instead.
              Switch (Arg1)
              {
                  case (0x0) { // lowest point
                    Store (HW63, Local0) // Report Start PWM as lowest duty cycle
                    Or (Local0, ShiftLeft(HW61, 8), Local0) // Report Start Control Temperature as lowest temperature
                  }
                  case (0x2) { // Slope
                    Store (ShiftLeft(And(HW64, 0x7F), 5), Local0)  // Get PWM Slope
                  }
                  Default { return (ASL_BFPI_NOT_SUPPORTED) }
              }
          }
        #endif // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
              // SmartGuardian Automatic Mode works quite differently with linear mode.
              // It has no exact temperature and duty setting. So we keep point coordination in ASL name instead.
              Switch (Arg1)
              {
                  case (0x0) { // lowest point
                    Store (HW6B, Local0) // Report Start PWM as lowest duty cycle
                    Or (Local0, ShiftLeft(HW69, 8), Local0) // Report Start Control Temperature as lowest temperature
                  }
                  case (0x2) { // Slope
                    Store (ShiftLeft(And(HW6C, 0x7F), 5), Local0)  // Get PWM Slope
                  }
                  Default { return (ASL_BFPI_NOT_SUPPORTED) }
              }
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
              // SmartGuardian Automatic Mode works quite differently with linear mode.
              // It has no exact temperature and duty setting. So we keep point coordination in ASL name instead.
              Switch (Arg1)
              {
                  case (0x0) { // lowest point
                    Store (HW73, Local0) // Report Start PWM as lowest duty cycle
                    Or (Local0, ShiftLeft(HW71, 8), Local0) // Report Start Control Temperature as lowest temperature
                  }
                  case (0x2) { // Slope
                    Store (ShiftLeft(And(HW74, 0x7F), 5), Local0)  // Get PWM Slope
                  }
              }
          }
        #endif // IT8728_SMF3_SUPPORT

        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1SP
//
// Description:  SIO SMF control set control point configuration
//   Arg0 : SMF name to set
//   Arg1 : Point number to configre.
//     0 - lowest point
//     1 - highest point  (This SIO is not supported)
//     2 - Slope
//     3 - third low point  (Not support)
//   For points
//     Arg2 : DutyCycle coordinate for this pont
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     Arg3 : Temperature coordinate for this pont
//       0~255
//   For Slope configuration -
//     Arg2 : Digit part after point, of slope to set. in 1/256
//     Arg3 : Integer part of slope to set.
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER :
//       A FAN matches name provided, but is given a wrong control point
//       or PWM dutycycle given is larger than Max. supported.
//     BFPI_SUCCESS
//
// Note:
//   If a control point is given with a value higher than higher control points,
//   the value should also be set to higher point. Vice versa for lower ones.
//---------------------------------------------------------------------------
    Method (F1SP, 4){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

        #if ASL_IT8728_SMF1_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_1_STRING)) {
              Store (ASL_BFPI_SUCCESS, Local0)
              switch (Arg1) {
                case (0x0) {  // Set lowest point
                    If (LGreater(Arg2, ASL_IT8728_SMF_MAX_DUTY)) { Return (ASL_BFPI_INVALID_PARAMETER) }
                    Store (Arg2, HW63)  // Set the Start PWM register as the lowest duty
                    Store (Arg3, HW61)  // Set the Start Temperature register as the lowest temperature
                    If (LLess(HW61, HW60)) {  // If the lowest temperature < Off Control Temperature
                        Store (HW61, HW60)  // To sync the Off Control Temperature same as the lowest temperature
                    }
                }
                case (0x2) {  // Set Slope
                    And(HW64, 0x80, Local1)
                    Or (Local1, ShiftLeft(Arg3, 3), Local1)  // Set PMW Slope (Integer)
                    Or (Local1, ShiftRight(Arg2, 5), Local1)  // Set PMW Slope (Digit)
                    Store (Local1, HW64)  // Set Slope to register
                }
                Default { return (ASL_BFPI_NOT_SUPPORTED) }
              }
              ShiftRight(And(HW64, 0x78), 3, Local1) // Get Slope (Integer)
              Subtract(ASL_IT8728_SMF_MAX_DUTY, HW63, Local2)  // Local2 : PWM Delta
              Divide (Local2, Local1, Local4, Local3)  // Local3 : The temperature delta of the lowest and maximum PWM
                                                       // Local4 : Remainder
              Divide (Multiply(Local4, 2), Local1,, Local2)
              If (LGreater(Local2, 0)) {
                  Increment (Local3)  // Rounding remainder to the temperature delta
              }
              Add(HW61, Local3, Local2)  // Local2 = The calculated Highest Temperature (PWM ≒ 255)
              If (LGreater(Local2, 0x7F)) {  // If the calculated Highest Temperature > 127°C
                  Store (0x7F, Local2)  // Replace the calculated Highest Temperature as the maximum supported temperature
              }
              If (LGreater(Local2, HW62)) { // If the calculated Highest Temperature > Full Speed Temperature
                  Store (Local2, HW62)  // Set Full Speed Temperature = Highest Temperature
              }
          }
        #endif  // IT8728_SMF1_SUPPORT
        #if ASL_IT8728_SMF2_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_2_STRING)) {
              Store (ASL_BFPI_SUCCESS, Local0)
              switch (Arg1) {
                case (0x0) {  // Set lowest point
                    If (LGreater(Arg2, ASL_IT8728_SMF_MAX_DUTY)) { Return (ASL_BFPI_INVALID_PARAMETER) }
                    Store (Arg2, HW6B)  // Set the Start PWM register as the lowest duty
                    Store (Arg3, HW69)  // Set the Start Temperature register as the lowest temperature
                    If (LLess(HW69, HW68)) {  // If the lowest temperature < Off Control Temperature
                        Store (HW69, HW68)  // To sync the Off Control Temperature same as the lowest temperature
                    }
                }
                case (0x2) {  // Set Slope
                    And(HW6C, 0x80, Local1)
                    Or (Local1, ShiftLeft(Arg3, 3), Local1)  // Set PMW Slope (Integer)
                    Or (Local1, ShiftRight(Arg2, 5), Local1)  // Set PMW Slope (Digit)
                    Store (Local1, HW6C)  // Set Slope to register
                }
                Default { return (ASL_BFPI_NOT_SUPPORTED) }
              }
              ShiftRight(And(HW6C, 0x78), 3, Local1) // Get Slope (Integer)
              Subtract(ASL_IT8728_SMF_MAX_DUTY, HW6B, Local2)  // Local2 : PWM Delta
              Divide (Local2, Local1, Local4, Local3)  // Local3 : The temperature delta of the lowest and maximum PWM
                                                       // Local4 : Remainder
              Divide (Multiply(Local4, 2), Local1,, Local2)
              If (LGreater(Local2, 0)) {
                  Increment (Local3)  // Rounding remainder to the temperature delta
              }
              Add(HW69, Local3, Local2)  // Local2 = The calculated Highest Temperature (PWM ≒ 255)
              If (LGreater(Local2, 0x7F)) {  // If the calculated Highest Temperature > 127°C
                  Store (0x7F, Local2)  // Replace the calculated Highest Temperature as the maximum supported temperature
              }
              If (LGreater(Local2, HW6A)) { // If the calculated Highest Temperature > Full Speed Temperature
                  Store (Local2, HW6A)  // Set Full Speed Temperature = Highest Temperature
              }
          }
        #endif // IT8728_SMF2_SUPPORT
        #if ASL_IT8728_SMF3_SUPPORT
          If (LEqual(Arg0, ASL_IT8728F_FAN_3_STRING)) {
              Store (ASL_BFPI_SUCCESS, Local0)
              switch (Arg1) {
                case (0x0) {  // Set lowest point
                    If (LGreater(Arg2, ASL_IT8728_SMF_MAX_DUTY)) { Return (ASL_BFPI_INVALID_PARAMETER) }
                    Store (Arg2, HW73)  // Set the Start PWM register as the lowest duty
                    Store (Arg3, HW71)  // Set the Start Temperature register as the lowest temperature
                    If (LLess(HW71, HW70)) {  // If the lowest temperature < Off Control Temperature
                        Store (HW71, HW70)  // To sync the Off Control Temperature same as the lowest temperature
                    }
                }
                case (0x2) {  // Set Slope
                    And(HW74, 0x80, Local1)
                    Or (Local1, ShiftLeft(Arg3, 3), Local1)  // Set PMW Slope (Integer)
                    Or (Local1, ShiftRight(Arg2, 5), Local1)  // Set PMW Slope (Digit)
                    Store (Local1, HW74)  // Set Slope to register
                }
                Default { return (ASL_BFPI_NOT_SUPPORTED) }
              }
              ShiftRight(And(HW74, 0x78), 3, Local1) // Get Slope (Integer)
              Subtract(ASL_IT8728_SMF_MAX_DUTY, HW73, Local2)  // Local2 : PWM Delta
              Divide (Local2, Local1, Local4, Local3)  // Local3 : The temperature delta of the lowest and maximum PWM
                                                       // Local4 : Remainder
              Divide (Multiply(Local4, 2), Local1,, Local2)
              If (LGreater(Local2, 0)) {
                  Increment (Local3)  // Rounding remainder to the temperature delta
              }
              Add(HW71, Local3, Local2)  // Local2 = The calculated Highest Temperature (PWM ≒ 255)
              If (LGreater(Local2, 0x7F)) {  // If the calculated Highest Temperature > 127°C
                  Store (0x7F, Local2)  // Replace the calculated Highest Temperature as the maximum supported temperature
              }
              If (LGreater(Local2, HW72)) { // If the calculated Highest Temperature > Full Speed Temperature
                  Store (Local2, HW72)  // Set Full Speed Temperature = Highest Temperature
              }
          }
        #endif // IT8728_SMF3_SUPPORT

        Return (Local0)
    }

#endif  //ASL_IT8728F_HWM_PRESENT
// << AAEON BFPI - End
