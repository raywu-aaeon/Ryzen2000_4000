//**********************************************************************
//<AAEON_FHDR_START>
//
// Name:  <F81966Bfpi.asl>
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
#ifndef ASL_F81966_TEMPERATURE_1_STRING
    #define ASL_F81966_TEMPERATURE_1_STRING "F81966-TEMPERATURE_1"
#endif
#ifndef ASL_F81966_TEMPERATURE_2_STRING
    #define ASL_F81966_TEMPERATURE_2_STRING "F81966-TEMPERATURE_2"
#endif
#ifndef ASL_F81966_TEMPERATURE_3_STRING
    #define ASL_F81966_TEMPERATURE_3_STRING "F81966-TEMPERATURE_3"
#endif
#ifndef ASL_F81966_TEMPERATURE_4_STRING
    #define ASL_F81966_TEMPERATURE_4_STRING "F81966-TEMPERATURE_4"
#endif
#ifndef ASL_F81966_TEMPERATURE_5_STRING
    #define ASL_F81966_TEMPERATURE_5_STRING "F81966-TEMPERATURE_5"
#endif
#ifndef ASL_F81966_FAN_1_STRING
    #define ASL_F81966_FAN_1_STRING "F81966-FAN_1"
#endif
#ifndef ASL_F81966_FAN_2_STRING
    #define ASL_F81966_FAN_2_STRING "F81966-FAN_2"
#endif
#ifndef ASL_F81966_FAN_3_STRING
    #define ASL_F81966_FAN_3_STRING "F81966-FAN_3"
#endif
#ifndef ASL_F81966_3VCC_STRING
    #define ASL_F81966_3VCC_STRING "F81966-3VCC"
#endif
#ifndef ASL_F81966_VIN1_VCORE_STRING
    #define ASL_F81966_VIN1_VCORE_STRING "F81966-VIN1_VCORE"
#endif
#ifndef ASL_F81966_VIN2_STRING
    #define ASL_F81966_VIN2_STRING "F81966-VIN2"
#endif
#ifndef ASL_F81966_VIN3_STRING
    #define ASL_F81966_VIN3_STRING "F81966-VIN3"
#endif
#ifndef ASL_F81966_VIN4_STRING
    #define ASL_F81966_VIN4_STRING "F81966-VIN4"
#endif
#ifndef ASL_F81966_VSB3V_STRING
    #define ASL_F81966_VSB3V_STRING "F81966-VSB3V"
#endif
#ifndef ASL_F81966_VBAT_STRING
    #define ASL_F81966_VBAT_STRING "F81966-VBAT"
#endif
#ifndef ASL_F81966_5VSB_STRING
    #define ASL_F81966_5VSB_STRING "F81966-5VSB"
#endif
#ifndef ASL_F81966_TEMP_SENSOR_NUMBER
    #define ASL_F81966_TEMP_SENSOR_NUMBER 0
#endif
#ifndef ASL_F81966_FAN_SENSOR_NUMBER
    #define ASL_F81966_FAN_SENSOR_NUMBER 0
#endif
#ifndef ASL_F81966_VOLT_SENSOR_NUMBER
    #define ASL_F81966_VOLT_SENSOR_NUMBER 0
#endif
//---------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//---------------------------------------------------------------------
OperationRegion(IOHW,   // Name of Operation Region for SuperIO device
    SystemIO,           // Type of address space
    IO3B, // Offset to start of region
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
    Offset(0x01),
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
    HW1E, 8,
    HW1F, 8,
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
    HW2C, 8,
    HW2D, 8,
    HW2E, 8,
    HW2F, 8,
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
    HW46, 8,
    HW47, 8,
    HW48, 8,
    HW49, 8,
    HW4A, 8,
    HW4B, 8,
    HW4C, 8,
    HW4D, 8,
    HW4E, 8,
    HW4F, 8,
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
    HW5A, 8,
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
    HW67, 8,
    HW68, 8,
    HW69, 8,
    HW6A, 8,
    HW6B, 8,
    HW6C, 8,
    HW6D, 8,
    HW6E, 8,
    HW6F, 8,
    Offset(0x70),
    HW70, 8,
    HW71, 8,
    HW72, 8,
    HW73, 8,
    HW74, 8,
    HW75, 8,
    HW76, 8,
    HW77, 8,
    HW78, 8,
    HW79, 8,
    HW7A, 8,
    HW7B, 8,
    HW7C, 8,
    HW7D, 8,
    HW7E, 8,
    HW7F, 8,
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
    HW9A, 8,
    HW9B, 8,
    HW9C, 8,
    HW9D, 8,
    HW9E, 8,
    HW9F, 8,
    Offset(0xA0),
    HWA0, 8,
    HWA1, 8,
    HWA2, 8,
    HWA3, 8,
    HWA4, 8,
    HWA5, 8,
    HWA6, 8,
    HWA7, 8,
    HWA8, 8,
    HWA9, 8,
    HWAA, 8,
    HWAB, 8,
    HWAC, 8,
    HWAD, 8,
    HWAE, 8,
    HWAF, 8,
    Offset(0xB0),
    HWB0, 8,
    HWB1, 8,
    HWB2, 8,
    HWB3, 8,
    HWB4, 8,
    HWB5, 8,
    HWB6, 8,
    HWB7, 8,
    HWB8, 8,
    HWB9, 8,
    HWBA, 8,
    HWBB, 8,
    HWBC, 8,
    HWBD, 8,
    HWBE, 8,
    HWBF, 8,
    Offset(0xC0),
    HWC0, 8,
    HWC1, 8,
    HWC2, 8,
    HWC3, 8,
    HWC4, 8,
    HWC5, 8,
    HWC6, 8,
    HWC7, 8,
    HWC8, 8,
    HWC9, 8,
    HWCA, 8,
    HWCB, 8,
    HWCC, 8,
    HWCD, 8,
    HWCE, 8,
    HWCF, 8,
}

Method(ENBK, 1) {
    //Set FAN_PROG_SEL from Fan Fault Time Register Index 9Fh Bit[7]
    ShiftLeft(And(Arg0, 0x01), 7, Local0)
    Or(And(HW9F, 0x7F, Local1), Local0, Local2)
    Store(Local2, HW9F)
}
#if ASL_F81966_HWM_PRESENT
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
//   Arg1 : T.B.D.
//
// Output:
//   FAN speed in RPM
//
//---------------------------------------------------------------------------
    Method (HCVF, 2){
        // Check input to prevent divide 0
        If (LEqual(Arg0, 0xFFFF)) { Return (0) }
        If (LEqual(Arg0, 0xFFF)) { Return (0) }
        If (LEqual(Arg0, 0)) { Return (0) }

        // Speed = 1500000/(Divisor);
        Store (Arg0, Local0)
        Divide (1500000, Local0, , Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVV
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
    Method (HCVV, 3){
        Multiply (Arg0, 8, Local0)  // reading unit is 8mV

        // Check input to prevent divide 0
        If (LEqual(Arg2, 0)) { Return (Local0) }

        // Voltage = Reading * 8mV * (R1 + R2) / R2
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
            Store (ASL_F81966_TEMP_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            Store (ASL_F81966_FAN_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            Store (ASL_F81966_VOLT_SENSOR_NUMBER, Local0)
        }
        Return (Local0)
    }
//------------------------------------------------------------------------
// Table:    THTS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
Name(THTS, Package() {
#if ASL_F81966_TEMPERATURE_1_SUPPORT
    ASL_F81966_TEMPERATURE_1_STRING,
#endif
#if ASL_F81966_TEMPERATURE_2_SUPPORT
    ASL_F81966_TEMPERATURE_2_STRING,
#endif
#if ASL_F81966_TEMPERATURE_3_SUPPORT
    ASL_F81966_TEMPERATURE_3_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    THFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
Name(THFS, Package() {
#if ASL_F81966_FAN_1_SUPPORT
    ASL_F81966_FAN_1_STRING,
#endif
#if ASL_F81966_FAN_2_SUPPORT
    ASL_F81966_FAN_2_STRING,
#endif
#if ASL_F81966_FAN_3_SUPPORT
    ASL_F81966_FAN_3_STRING,
#endif
})
//------------------------------------------------------------------------
// Table:    THVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
Name(THVS, Package() {
#if ASL_F81966_3VCC_SUPPORT
    ASL_F81966_3VCC_STRING,
#endif
#if ASL_F81966_VIN1_VCORE_SUPPORT
    ASL_F81966_VIN1_VCORE_STRING,
#endif
#if ASL_F81966_VIN2_SUPPORT
    ASL_F81966_VIN2_STRING,
#endif
#if ASL_F81966_VIN3_SUPPORT
    ASL_F81966_VIN3_STRING,
#endif
#if ASL_F81966_VIN4_SUPPORT
    ASL_F81966_VIN4_STRING,
#endif
#if ASL_F81966_VSB3V_SUPPORT
    ASL_F81966_VSB3V_STRING,
#endif
#if ASL_F81966_VBAT_SUPPORT
    ASL_F81966_VBAT_STRING,
#endif
#if ASL_F81966_5VSB_SUPPORT
    ASL_F81966_5VSB_STRING,
#endif
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
// Note: 
//
//---------------------------------------------------------------------------
    Method (H1RS, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
#if ASL_F81966_TEMPERATURE_1_SUPPORT
            If (LEqual(Arg1, ASL_F81966_TEMPERATURE_1_STRING)) {  // Temperature 1 - System Temperature
                Store (HW72, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
#else
            If (LNotEqual(Arg0, 0)) {   // Should not be TRUE always
            }
#endif
#if ASL_F81966_TEMPERATURE_2_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_TEMPERATURE_2_STRING)) {  // Temperature 2 - System Temperature 2
                Store (HW74, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
#endif
#if ASL_F81966_TEMPERATURE_3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_TEMPERATURE_3_STRING)) {  // Temperature 3 - System Temperature 3
                Store (HW7E, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
#endif
#if ASL_F81966_TEMPERATURE_4_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_TEMPERATURE_4_STRING)) {  // Temperature 4 - System Temperature 4
                Store (HW7A, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
#endif
#if ASL_F81966_TEMPERATURE_5_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_TEMPERATURE_5_STRING)) {  // Temperature 5 - System Temperature 5
                Store (HW7B, Local0)
                Store (HCVT (Local0, 0), Local0)
            }
#endif
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
#if ASL_F81966_FAN_1_SUPPORT
            If (LEqual(Arg1, ASL_F81966_FAN_1_STRING)) {                // FAN1
                ShiftLeft(HWA0,8,local0) //FAN1 count reading (MSB)
                Or(local0,HWA1,local2) //FAN1 count reading (LSB)
                Store (0, Local1)                                       // Local1 : T.B.D.
                Store (HCVF (local2, local1), local0)
            }
#else
            If (LNotEqual(Arg0, 1)) {   // Should not be TRUE always
            }
#endif
#if ASL_F81966_FAN_2_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_FAN_2_STRING)) {            // FAN2
                ShiftLeft(HWB0,8,local0) //FAN2 count reading (MSB)
                Or(local0,HWB1,local2) //FAN2 count reading (LSB)
                Store (0, Local1)                                       // Local1 : T.B.D.
                Store (HCVF (local2, local1), local0)
            }
#endif
#if ASL_F81966_FAN_3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_FAN_3_STRING)) {            // FAN3
                ShiftLeft(HWC0,8,local0) //FAN3 count reading (MSB)
                Or(local0,HWC1,local2) //FAN3 count reading (LSB)
                Store (0, Local1)                                       // Local1 : T.B.D.
                Store (HCVF (local2, local1), local0)
            }
#endif
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
#if ASL_F81966_3VCC_SUPPORT
            If (LEqual(Arg1, ASL_F81966_3VCC_STRING)) {                 // 3VCC
                Store (HW20, Local0)
                Store( HCVV (Local0, 150, 150), Local0)
            }
#endif
#if ASL_F81966_VIN1_VCORE_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VIN1_VCORE_STRING)) {       // VIN1
                Store (HW21, Local0)
                Store( HCVV (Local0, ASL_VIN1_RA, ASL_VIN1_RB), Local0)
            }
#endif
#if ASL_F81966_VIN2_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VIN2_STRING)) {             // VIN2
                Store (HW22, Local0)
                Store( HCVV (Local0, ASL_VIN2_RA, ASL_VIN2_RB), Local0)
            }
#endif
#if ASL_F81966_VIN3_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VIN3_STRING)) {             // VIN3
                Store (HW23, Local0)
                Store( HCVV (Local0, ASL_VIN3_RA, ASL_VIN3_RB), Local0)
            }
#endif
#if ASL_F81966_VIN4_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VIN4_STRING)) {             // VIN4
                Store (HW24, Local0)
                Store( HCVV (Local0, ASL_VIN4_RA, ASL_VIN4_RB), Local0)
            }
#endif
#if ASL_F81966_VSB3V_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VSB3V_STRING)) {            // VSB3V
                Store (HW25, Local0)
                Store( HCVV (Local0, 150, 150), Local0)
            }
#endif
#if ASL_F81966_VBAT_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_VBAT_STRING)) {             // VBAT
                Store (HW26, Local0)
                Store( HCVV (Local0, 150, 150), Local0)
            }
#endif
#if ASL_F81966_5VSB_SUPPORT
            ElseIf (LEqual(Arg1, ASL_F81966_5VSB_STRING)) {             // 5VSB
                Store (HW27, Local0)
                Store( HCVV (Local0, 2, 1), Local0)                     // The 5VSB voltage to be monitored is internally divided by 3
            }
#endif
        }
        Return (Local0)
    }
#endif // ASL_F81966_HWM_PRESENT

//------------------------------------------------------------------------
// Table:    TLDN
// Description:  LDN look up table for GPIO group number
//-------------------------------------------------------------------------
    Name (TLDN, Package(0xA){
        6,  // GP0x
        6,  // GP1x
        6,  // GP2x
        6,  // GP3x
        6,  // GP4x
        6,  // GP5x
        6,  // GP6x
        6,  // GP7x
        6,  // GP8x
        6   // GP9x
    })

//------------------------------------------------------------------------
// Procedure:    CGTL
// Description:  Convert Super I/O GPIO group number to LDN
// Input: Arg0 : Super I/O Group number
// Output: LDN
//-------------------------------------------------------------------------
    Method(CGTL, 1) {
        If (LGreater(Arg0, 0x0A))
        { Return (ASL_BFPI_INVALID_PARAMETER) }
        Return(DerefOf(Index(TLDN, Arg0)))    // Return LDN
    }

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
        Store (CGTL(Local1), Local4)
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        // Local4 : GPIO LDN
        If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(Local4)                                            // Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,0))
        {
            ShiftRight(And(OPT2, Local3), Local2, Local5)       // GPIO0x Pin Status Register Index F2h
        } ElseIf (LEqual(Local1,1))
        {
            ShiftRight(And(RGE2, Local3), Local2, Local5)       // GPIO1x Pin Status Register Index E2h
        } ElseIf (LEqual(Local1,2))
        {
            ShiftRight(And(RGD2, Local3), Local2, Local5)       // GPIO2x Pin Status Register Index D2h
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(RGC2, Local3), Local2, Local5)       // GPIO3x Pin Status Register Index C2h
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(RGB2, Local3), Local2, Local5)       // GPIO4x Pin Status Register Index B2h
        } ElseIf (LEqual(Local1,5))
        {
            ShiftRight(And(RGA2, Local3), Local2, Local5)       // GPIO5x Pin Status Register Index A2h
        } ElseIf (LEqual(Local1,6))
        {
            ShiftRight(And(RG92, Local3), Local2, Local5)       // GPIO6x Pin Status Register Index 92h
        } ElseIf (LEqual(Local1,7))
        {
            ShiftRight(And(RG82, Local3), Local2, Local5)       // GPIO7x Pin Status Register Index 82h
        } ElseIf (LEqual(Local1,8))
        {
            ShiftRight(And(RG8A, Local3), Local2, Local5)       // GPIO8x Pin Status Register Index 8Ah
        } ElseIf (LEqual(Local1,9))
        {
            ShiftRight(And(RG9A, Local3), Local2, Local5)       // GPIO9x Pin Status Register Index 9Ah
        }

        EXFG()        // Exit Config Mode

        If ( LAnd(LNotEqual(Local5 , 0), LNotEqual(Local5 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local5)
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
         Store (CGTL(Local1), Local4)
         // Local1 : Result : Super I/O Group number
         // Local2 : Remainder : Pin number in group 
         // Local3 : Pin bit map
         // Local4 : GPIO LDN
         If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
         { Return (ASL_BFPI_INVALID_PARAMETER) }

         ENFG(Local4)                                           // Enter Config Mode, Select GPIO LDN

         If (LEqual(Local1,0))
         {
             Or (And(OPT1,Not(Local3)), ShiftLeft(Arg1,Local2), OPT1)   // GPIO0x Pin Output Data Register Index F1h
         } ElseIf (LEqual(Local1,1))
         {
             Or (And(RGE1,Not(Local3)), ShiftLeft(Arg1,Local2), RGE1)   // GPIO1x Pin Output Data Register Index E1h
         } ElseIf (LEqual(Local1,2))
         {
             Or (And(RGD1,Not(Local3)), ShiftLeft(Arg1,Local2), RGD1)   // GPIO2x Pin Output Data Register Index D1h
         } ElseIf (LEqual(Local1,3))
         {
             Or (And(RGC1,Not(Local3)), ShiftLeft(Arg1,Local2), RGC1)   // GPIO3x Pin Output Data Register Index C1h
         } ElseIf (LEqual(Local1,4))
         {
             Or (And(RGB1,Not(Local3)), ShiftLeft(Arg1,Local2), RGB1)   // GPIO4x Pin Output Data Register Index B1h
         } ElseIf (LEqual(Local1,5))
         {
             Or (And(RGA1,Not(Local3)), ShiftLeft(Arg1,Local2), RGA1)   // GPIO5x Pin Output Data Register Index A1h
         } ElseIf (LEqual(Local1,6))
         {
             Or (And(RG91,Not(Local3)), ShiftLeft(Arg1,Local2), RG91)   // GPIO6x Pin Output Data Register Index 91h
         } ElseIf (LEqual(Local1,7))
         {
             Or (And(RG81,Not(Local3)), ShiftLeft(Arg1,Local2), RG81)   // GPIO7x Pin Output Data Register Index 81h
         } ElseIf (LEqual(Local1,8))
         {
             Or (And(RG89,Not(Local3)), ShiftLeft(Arg1,Local2), RG89)   // GPIO8x Pin Output Data Register Index 89h
         } ElseIf (LEqual(Local1,9))
         {
             Or (And(RG99,Not(Local3)), ShiftLeft(Arg1,Local2), RG99)   // GPIO9x Pin Output Data Register Index 99h
         }

         EXFG()        // Exit Config Mode

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
        Store (CGTL(Local1), Local4)
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
         // Local2 : Remainder : Pin number in group 
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        // Local4 : GPIO LDN
        If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(Local4)                                                // Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,0))
        {
            ShiftRight(And(OPT0, Local3), Local2, Local5)           // GPIO0x Pin Output Enable Register Index F0h
        } ElseIf (LEqual(Local1,1))
        {
            ShiftRight(And(RGE0, Local3), Local2, Local5)           // GPIO1x Pin Output Enable Register Index E0h
        } ElseIf (LEqual(Local1,2))
        {
            ShiftRight(And(RGD0, Local3), Local2, Local5)           // GPIO2x Pin Output Enable Register Index D0h
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(RGC0, Local3), Local2, Local5)           // GPIO3x Pin Output Enable Register Index C0h
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(RGB0, Local3), Local2, Local5)           // GPIO4x Pin Output Enable Register Index B0h
        } ElseIf (LEqual(Local1,5))
        {
            ShiftRight(And(RGA0, Local3), Local2, Local5)           // GPIO5x Pin Output Enable Register Index A0h
        } ElseIf (LEqual(Local1,6))
        {
            ShiftRight(And(RG90, Local3), Local2, Local5)           // GPIO6x Pin Output Enable Register Index 90h
        } ElseIf (LEqual(Local1,7))
        {
            ShiftRight(And(RG80, Local3), Local2, Local5)           // GPIO7x Pin Output Enable Register Index 80h
        } ElseIf (LEqual(Local1,8))
        {
            ShiftRight(And(RG88, Local3), Local2, Local5)           // GPIO8x Pin Output Enable Register Index 88h
        } ElseIf (LEqual(Local1,9))
        {
            ShiftRight(And(RG98, Local3), Local2, Local5)           // GPIO9x Pin Output Enable Register Index 98h
        }

        EXFG()                                                      // Exit Config Mode

        And(Not(Local5), 0x01, Local5)
        If ( LAnd(LNotEqual(Local5 , 0), LNotEqual(Local5 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local5)
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
        Store (CGTL(Local1), Local4)
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        // Local4 : GPIO LDN
        If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        And(Not(Arg1), 0x01, Arg1)

        ENFG(Local4)                                                //Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,0))
        {
            Or (And(OPT0,Not(Local3)), ShiftLeft(Arg1,Local2), OPT0)    // GPIO0x Pin Output Enable Register Index F0h
        } ElseIf (LEqual(Local1,1))
        {
            Or (And(RGE0,Not(Local3)), ShiftLeft(Arg1,Local2), RGE0)    // GPIO1x Pin Output Enable Register Index E0h
        } ElseIf (LEqual(Local1,2))
        {
            Or (And(RGD0,Not(Local3)), ShiftLeft(Arg1,Local2), RGD0)    // GPIO2x Pin Output Enable Register Index D0h
        } ElseIf (LEqual(Local1,3))
        {
            Or (And(RGC0,Not(Local3)), ShiftLeft(Arg1,Local2), RGC0)    // GPIO3x Pin Output Enable Register Index C0h
        } ElseIf (LEqual(Local1,4))
        {
            Or (And(RGB0,Not(Local3)), ShiftLeft(Arg1,Local2), RGB0)    // GPIO4x Pin Output Enable Register Index B0h
        } ElseIf (LEqual(Local1,5))
        {
            Or (And(RGA0,Not(Local3)), ShiftLeft(Arg1,Local2), RGA0)    // GPIO5x Pin Output Enable Register Index A0h
        } ElseIf (LEqual(Local1,6))
        {
            Or (And(RG90,Not(Local3)), ShiftLeft(Arg1,Local2), RG90)    // GPIO6x Pin Output Enable Register Index 90h
        } ElseIf (LEqual(Local1,7))
        {
            Or (And(RG80,Not(Local3)), ShiftLeft(Arg1,Local2), RG80)    // GPIO7x Pin Output Enable Register Index 80h
        } ElseIf (LEqual(Local1,8))
        {
            Or (And(RG88,Not(Local3)), ShiftLeft(Arg1,Local2), RG88)    // GPIO8x Pin Output Enable Register Index 88h
        } ElseIf (LEqual(Local1,9))
        {
            Or (And(RG98,Not(Local3)), ShiftLeft(Arg1,Local2), RG98)    // GPIO9x Pin Output Enable Register Index 98h
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
        Store (CGTL(Local1), Local4)
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        // Local4 : GPIO LDN
        If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(Local4)                                                // Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,0))
        {
            ShiftRight(And(OPT3, Local3), Local2, Local5)           // GPIO0x Pin Drive Enable Register Index F3h
        } ElseIf (LEqual(Local1,1))
        {
            ShiftRight(And(RGE3, Local3), Local2, Local5)           // GPIO1x Pin Drive Enable Register Index E3h
        } ElseIf (LEqual(Local1,2))
        {
            Return (ASL_BFPI_INVALID_PARAMETER)                     // GPIO2x Pin Not Supported Drive Enable Register
        } ElseIf (LEqual(Local1,3))
        {
            ShiftRight(And(RGC3, Local3), Local2, Local5)           // GPIO3x Pin Drive Enable Register Index C3h
        } ElseIf (LEqual(Local1,4))
        {
            ShiftRight(And(RGB3, Local3), Local2, Local5)           // GPIO4x Pin Drive Enable Register Index B3h
        } ElseIf (LEqual(Local1,5))
        {
            Return (ASL_BFPI_INVALID_PARAMETER)                     // GPIO5x Pin Not Supported Drive Enable Register
        } ElseIf (LEqual(Local1,6))
        {
            If ( LEqual(Local2,7) ) {
                Return (ASL_BFPI_INVALID_PARAMETER)                 // GPIO67 Pin Not Supported Drive Enable Register
            }
            ShiftRight(And(RG93, Local3), Local2, Local5)           // GPIO6x Pin Drive Enable Register Index 93h
        } ElseIf (LEqual(Local1,7))
        {
            ShiftRight(And(RG83, Local3), Local2, Local5)           // GPIO7x Pin Drive Enable Register Index 83h
        } ElseIf (LEqual(Local1,8))
        {
            ShiftRight(And(RG8B, Local3), Local2, Local5)           // GPIO8x Pin Drive Enable Register Index 8Bh
        } ElseIf (LEqual(Local1,9))
        {
            ShiftRight(And(RG9B, Local3), Local2, Local5)           // GPIO9x Pin Drive Enable Register Index 9Bh
        }

        EXFG()                                                      // Exit Config Mode

        If ( LAnd(LNotEqual(Local5 , 0), LNotEqual(Local5 , 1)) ) {
            Return (ASL_BFPI_INVALID_PARAMETER)
        }
        Return (Local5)
    }
//---------------------------------------------------------------------------
// Name: D1SO
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
    Method (D1SO, 2){
        Store(And(Arg0, 0xff), Local0)                              // Local1: DIO number
        Divide (Local0, 10, Local2, Local1)
        ShiftLeft(0x01, Local2, Local3)                             // pin bitmask
        Store (CGTL(Local1), Local4)
        // Local1 : Result : Super I/O Group number
        // Local2 : Remainder : Pin number in group 
        // Local3 : Pin bit map
        // Local4 : GPIO LDN
        If (LEqual(Local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }


        ENFG(Local4)                                                    //Enter Config Mode, Select GPIO LDN

        If (LEqual(Local1,0))
        {
            Or (And(OPT3,Not(Local3)), ShiftLeft(Arg1,Local2), OPT3)    // GPIO0x Pin Drive Enable Register Index F3h
        } ElseIf (LEqual(Local1,1))
        {
            Or (And(RGE3,Not(Local3)), ShiftLeft(Arg1,Local2), RGE3)    // GPIO1x Pin Drive Enable Register Index E3h
        } ElseIf (LEqual(Local1,2))
        {
            Return (ASL_BFPI_INVALID_PARAMETER)                         // GPIO2x Pin Not Supported Drive Enable Register
        } ElseIf (LEqual(Local1,3))
        {
            Or (And(RGC3,Not(Local3)), ShiftLeft(Arg1,Local2), RGC3)    // GPIO3x Pin Drive Enable Register Index C3h
        } ElseIf (LEqual(Local1,4))
        {
            Or (And(RGB3,Not(Local3)), ShiftLeft(Arg1,Local2), RGB3)    // GPIO4x Pin Drive Enable Register Index B3h
        } ElseIf (LEqual(Local1,5))
        {
            Return (ASL_BFPI_INVALID_PARAMETER)                         // GPIO5x Pin Not Supported Drive Enable Register
        } ElseIf (LEqual(Local1,6))
        {
            If ( LEqual(Local2,7) ) {
                Return (ASL_BFPI_INVALID_PARAMETER)                     // GPIO67 Pin Not Supported Drive Enable Register
            }
            Or (And(RG93,Not(Local3)), ShiftLeft(Arg1,Local2), RG93)    // GPIO6x Pin Drive Enable Register Index 93h
        } ElseIf (LEqual(Local1,7))
        {
            Or (And(RG83,Not(Local3)), ShiftLeft(Arg1,Local2), RG83)    // GPIO7x Pin Drive Enable Register Index 83h
        } ElseIf (LEqual(Local1,8))
        {
            Or (And(RG8B,Not(Local3)), ShiftLeft(Arg1,Local2), RG8B)    // GPIO8x Pin Drive Enable Register Index 8Bh
        } ElseIf (LEqual(Local1,9))
        {
            Or (And(RG9B,Not(Local3)), ShiftLeft(Arg1,Local2), RG9B)    // GPIO9x Pin Drive Enable Register Index 9Bh
        }

        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }
#if ASL_F81966_WDT_PRESENT
//------------------------------------------------------------------------
// Table:    THFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
Name(THFC, Package() {
#if ASL_F81966_SMF1_SUPPORT
    ASL_F81966_FAN_1_STRING,
#endif
#if ASL_F81966_SMF2_SUPPORT
    ASL_F81966_FAN_2_STRING,
#endif
#if ASL_F81966_SMF3_SUPPORT
    ASL_F81966_FAN_3_STRING,
#endif
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
        ENFG(ASL_F81966_LDN_WDT)        //Enter Config Mode, Select WDT LDN
        Store (OPT6, Local0)
        Store (OPT5, Local1)
        // Local0 : Current time-out counter
        // Local1 :
        //   [3] : 0 - Second Mode, 1 - Minute Mode

        EXFG()        // Exit Config Mode

        If (LEqual(And(ShiftRight(Local1,3),1), 1)) {
           Multiply (Local0, 60000, Local0)  // Multiply with 60 in Minute mode
        }

        If (LEqual(And(ShiftRight(Local1,3),1), 0)) {
            Multiply (Local0, 1000, Local0)  // Multiply with 1 in Second mode
        }

        Return (Local0)
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
        // OPT6 : Current time-out counter
        // OPT5 :
        //   [5] : WD_EN -> 0 - Dislabe, 1 - Enable
        //   [4] : WD_PULSE mode -> 0 - level, 1 - pulse
        //   [3] : WD_UNIT -> 0 - Second Mode, 1 - Minute Mode
        //   [1-0] : WD_PSWIDTH -> 0 - 1ms, 1 - 25ms, 2 - 125ms, 3 - 5sec

        ENFG(ASL_F81966_LDN_WDT)        //Enter Config Mode, Select WDT LDN
                
        If (LGreater(Arg0, 0))
        {
            Divide (Arg0, 1000, Local1, Local0)
            // Convert ms to sec
            // Local0 : time-out in second
            // Local1 : time-out remainder in ms

            If (LGreater(Local1,0))
            {
                Increment(Local0)
            }

            If (LLessEqual(Local0, 255)) //If Local0 < or = 255s
            {
                And(OPT5,0xF7,OPT5)  // WD_UNIT set to Second Mode
            } 
            Else
            {
                Divide (Local0, 60, Local1, Local0)
                If (LGreater(Local1,0))
                {
                    Increment(Local0)
                }
                Or (OPT5, 0x08, OPT5)  // WD_UNIT set to Minute Mode
            }
            Store (Local0, OPT6) // Set time-out counter 
            Or (And(OPT5,0xEC),  0x11, OPT5)  // WD_PULSE -> pulse mode, WD_PSWIDTH -> 25 ms
            Or (OPT5, 0x20, OPT5)  // Enable Watch Dog
        }
        Else
        {
            And (OPT5, 0xDF, OPT5)  // Disable Watch Dog
        }
        
        EXFG()        // Exit Config Mode
        Return (ASL_BFPI_SUCCESS)
    }
#endif  //ASL_F81966_WDT_PRESENT
#if ASL_F81966_SMF_SUPPORT
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
        Return (ASL_F81966_SMF_NUMBER)
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

        // Return a list of FAN names that supported Smart FAN from this SOP, seperated by comma.
#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81966_FAN_1_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81966_FAN_2_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81966_FAN_3_STRING, "\"", ), ), Local0)
#endif
        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    TSEL
// Description: Select the temperature source for controlling FAN
//-------------------------------------------------------------------------
    Name(TSEL, Package() {
        ASL_F81966_TEMPERATURE_3_STRING,
        ASL_F81966_TEMPERATURE_1_STRING,
        ASL_F81966_TEMPERATURE_2_STRING,
        "Reserved",
        ASL_F81966_TEMPERATURE_4_STRING,
        ASL_F81966_TEMPERATURE_5_STRING,
        "Reserved",
        "Reserved",
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
    ENBK (0)
    If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
        Store (DerefOf(Index(TSEL, And(HWAF,0x03))), Local0)
    }
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
    ElseIf (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
        Store (DerefOf(Index(TSEL, And(HWBF,0x03))), Local0)
    }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
    ElseIf (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
        Store (DerefOf(Index(TSEL, And(HWCF,0x03))), Local0)
    }
#endif    
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
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1RM, 1){
    If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
    } Else { Return(ASL_BFPI_NOT_SUPPORTED) }
    Return (0x3)
}
//---------------------------------------------------------------------------
// Name: F1PW
//
// Description:  SMF report Max. PWM value for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Max. PWM value supported.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1PW, 1){
    If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
    } Else { Return(ASL_BFPI_NOT_SUPPORTED) }
    Return (255)
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
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1LP, 1){
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
        Store ("", Local1)

#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
            Store (ASL_F81966_SMFC_FAN_1_PREFIX, Local0)
            // Index AFh Bit[7]: FAN1_TEMP_SEL_DIG
            // Index AFh Bit[1:0]: FAN1_TEMP_SEL
            // {FAN1_TEMP_SEL_DIG, FAN1_TEMP_SEL}
            Or(And(ShiftRight(HWAF, 5),0x04),And(HWAF,0x03),Local2)
            Store (DerefOf(Index(TSEL, Local2)), Local1)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ASL_F81966_SMFC_FANOUT_SUFFIX, Local0)
            Return (Local0)
        }
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
            Store (ASL_F81966_SMFC_FAN_2_PREFIX, Local0)
            // Index BFh Bit[7]: FAN2_TEMP_SEL_DIG
            // Index BFh Bit[1:0]: FAN2_TEMP_SEL
            // {FAN2_TEMP_SEL_DIG, FAN2_TEMP_SEL}
            Or(And(ShiftRight(HWBF, 5),0x04),And(HWBF,0x03),Local2)
            Store (DerefOf(Index(TSEL, Local2)), Local1)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ASL_F81966_SMFC_FANOUT_SUFFIX, Local0)
            Return (Local0)
        }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
            Store (ASL_F81966_SMFC_FAN_3_PREFIX, Local0)
            // Index CFh Bit[7]: FAN3_TEMP_SEL_DIG
            // Index CFh Bit[1:0]: FAN3_TEMP_SEL
            // {FAN3_TEMP_SEL_DIG, FAN3_TEMP_SEL}
            Or(And(ShiftRight(HWCF, 5),0x04),And(HWCF,0x03),Local2)
            Store (DerefOf(Index(TSEL, Local2)), Local1)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ASL_F81966_SMFC_FANOUT_SUFFIX, Local0)
            Return (Local0)
        }
#endif
        Return ("NULL")
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
//       1 - Linear mode
//     Bit[7:4]: Reserved Bits
//     Bit[15:8]: (valid only for manual mode) Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/255)% duty
//       255 - 100% duty
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
    Method (F1GM, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)
        ENBK (0) // FAN_PROG_SEL -> 0

#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
            And(HW96, 0x03, Local1)                     // Index 96h Bit[1:0]: FAN1_MODE
            If (LEqual(Local1, 0x01)) {                 // Bit[1:0] = 01b : Auto fan speed control by duty cycle
                Store (1, Local0)
            }
            If (LEqual(Local1, 0x03)) {                 // Bit[1:0] = 11b : Manual mode fan control
                Store (0, Local0)
                Or (Local0, ShiftLeft(HWA3, 8), Local0) // Index A3h: FAN1 duty value
            }
            
        }
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
            And(ShiftRight(HW96, 2), 0x03, Local1)      // Index 96h Bit[3:2]: FAN2_MODE
            If (LEqual(Local1, 0x01)) {                 // Bit[3:2] = 01b: Auto fan speed control by duty cycle
                Store (1, Local0)
            }
            If (LEqual(Local1, 0x03)) {                 // Bit[3:2] = 11b: Manual mode fan control
                Store (0, Local0)
                Or (Local0, ShiftLeft(HWB3, 8), Local0) // Index B3h: FAN2 duty value
            }
        }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
            And(ShiftRight(HW96, 4), 0x03, Local1)      // Index 96h Bit[5:4]: FAN3_MODE
            If (LEqual(Local1, 0x01)) {                 // Bit[5:4] = 01b: Auto fan speed control by duty cycle
                Store (1, Local0)
            }
            If (LEqual(Local1, 0x03)) {                 // Bit[5:4] = 11b: Manual mode fan control
                Store (0, Local0)
                Or (Local0, ShiftLeft(HWC3, 8), Local0) // Index C3h: FAN3 duty value
            }
        }
#endif
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1SM
//
// Description:  SIO SMF set mode
//   Arg0 : SMF name to set
//   Arg1 : SMF mode to set
//       0 - Manual mode
//       1 - Linear mode
//   Arg2 : Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/255)% duty
//       255 - 100% duty
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_SUCCESS
//
//---------------------------------------------------------------------------
    Method (F1SM, 3){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)
        ENBK (0) // FAN_PROG_SEL -> 0

#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
            And(HW96, 0xFC, Local1)     // Index 96h Bit[1:0]: FAN1_MODE
            If (LEqual(Arg1, 0)) {
                Or(Local1, 0x03, HW96)  // Bit[1:0] = 11b : Manual mode fan control
                Store (Arg2, HWA3)      // Index A3h: FAN1 duty value
            }
            Else {
                Or(Local1, 0x01, HW96)  // Bit[1:0] = 01b : Auto fan speed control by duty cycle
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
            And(HW96, 0xF3, Local1)     // Index 96h Bit[3:2]: FAN2_MODE
            If (LEqual(Arg1, 0)) {
                Or(Local1, 0x0C, HW96)  // Bit[3:2] = 11b: Manual mode fan control
                Store (Arg2, HWB3)      // Index B3h: FAN2 duty value
            }
            Else {
                Or(Local1, 0x04, HW96)  // Bit[3:2] = 01b: Auto fan speed control by duty cycle
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
            And(HW96, 0xCF, Local1)     // Index 96h Bit[5:4]: FAN3_MODE
            If (LEqual(Arg1, 0)) {
                Or(Local1, 0x30, HW96)  // Bit[5:4] = 11b: Manual mode fan control
                Store (Arg2, HWC3)      // Index C3h: FAN3 duty value
            }
            Else {
                Or(Local1, 0x10, HW96)  // Bit[5:4] = 01b: Auto fan speed control by duty cycle
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1GP
//
// Description:  SIO SMF control get control point configuration
//   Arg0 : SMF name to get
//   Arg1 : control point to get
//     0 - lowest point
//     1 - highest point
//     2 - secondary low point
//     3 - third low point
//
// Output:
//   Integer :
//     Bit[7:0]: DutyCycle coordinate for this pont
//       0 - 0% duty
//       X - (X/255)% duty
//       255 - 100% duty
//     Bit[16:8]: Temperature coordinate for this pont
//       0~255
//     BFPI_NOT_SUPPORTED: No FAN matches name provided.
//
//---------------------------------------------------------------------------
    Method (F1GP, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
            // FAN1 SEGMENT 1 SPEED COUNT Index AAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (HWAE, Local0) // Index AE: FAN1 SEGMENT 5 SPEED COUNT
                Or (Local0, ShiftLeft(HWA9, 8), Local0) // Index A9: FAN1 Boundary 4 Temperature
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (HWAB, Local0) // Index AB: FAN1 SEGMENT 2 SPEED COUNT
                Or (Local0, ShiftLeft(HWA6, 8), Local0) // Index A6: FAN1 Boundary 1 Temperature
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (HWAD, Local0) // Index AD: FAN1 SEGMENT 4 SPEED COUNT
                Or (Local0, ShiftLeft(HWA8, 8), Local0) // Index A8: FAN1 Boundary 3 Temperature
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (HWAC, Local0) // Index AC: FAN1 SEGMENT 3 SPEED COUNT
                Or (Local0, ShiftLeft(HWA7, 8), Local0) // Index A7: FAN1 Boundary 2 Temperature
            }
        }
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
            // FAN2 SEGMENT 1 SPEED COUNT Index BAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (HWBE, Local0) // Index BE: FAN2 SEGMENT 5 SPEED COUNT
                Or (Local0, ShiftLeft(HWB9, 8), Local0) // Index B9: FAN2 Boundary 4 Temperature
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (HWBB, Local0) // Index BB: FAN2 SEGMENT 2 SPEED COUNT
                Or (Local0, ShiftLeft(HWB6, 8), Local0) // Index B6: FAN2 Boundary 1 Temperature
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (HWBD, Local0) // Index BD: FAN2 SEGMENT 4 SPEED COUNT
                Or (Local0, ShiftLeft(HWB8, 8), Local0) // Index B8: FAN2 Boundary 3 Temperature
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (HWBC, Local0) // Index BC: FAN2 SEGMENT 3 SPEED COUNT
                Or (Local0, ShiftLeft(HWB7, 8), Local0) // Index B7: FAN2 Boundary 2 Temperature
            }
        }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
            // FAN3 SEGMENT 1 SPEED COUNT Index CAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (HWCE, Local0) // Index CE: FAN3 SEGMENT 5 SPEED COUNT
                Or (Local0, ShiftLeft(HWC9, 8), Local0) // Index C9: FAN3 Boundary 4 Temperature
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (HWCB, Local0) // Index CB: FAN3 SEGMENT 2 SPEED COUNT
                Or (Local0, ShiftLeft(HWC6, 8), Local0) // Index C6: FAN3 Boundary 1 Temperature
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (HWCD, Local0) // Index CD: FAN3 SEGMENT 4 SPEED COUNT
                Or (Local0, ShiftLeft(HWC8, 8), Local0) // Index C8: FAN3 Boundary 3 Temperature
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (HWCC, Local0) // Index CC: FAN3 SEGMENT 3 SPEED COUNT
                Or (Local0, ShiftLeft(HWC7, 8), Local0) // Index C7: FAN3 Boundary 2 Temperature
            }
        }
#endif
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1SP
//
// Description:  SIO SMF control set control point configuration
//   Arg0 : SMF name to set
//   Arg1 : Point number to configre.
//     0 - lowest point
//     1 - highest point
//     2 - secondary low point
//     3 - third low point
//   Arg2 : DutyCycle coordinate for this pont
//     0 - 0% duty
//     X - (X/255)% duty
//     255 - 100% duty
//   Arg3 : Temperature coordinate for this pont
//     0~255
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER : A FAN matches name provided, but is given a wrong control point.
//     BFPI_SUCCESS
//
// Note:
//   If a control point is given with a value higher than higher control points,
//   the value should also be set to higher point. Vice versa for lower ones.
//---------------------------------------------------------------------------
    Method (F1SP, 4){
        Name (BUFF, Buffer(4) {0x0})
        Store (ASL_BFPI_NOT_SUPPORTED, Local0)

#if ASL_F81966_SMF1_SUPPORT && ASL_F81966_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_1_STRING)) {
            // FAN1 SEGMENT 1 SPEED COUNT Index AAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (Arg3, HWA9) // Index A9: FAN1 Boundary 4 Temperature
                Store (Arg2, HWAE) // Index AE: FAN1 SEGMENT 5 SPEED COUNT
                // Update secondary low point if it has value higher
                If (LGreater(Arg3, HWA8)) { Store (Arg3, HWA8) }
                If (LGreater(Arg2, HWAD)) { Store (Arg2, HWAD) }
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWA7)) { Store (Arg3, HWA7) }
                If (LGreater(Arg2, HWAC)) { Store (Arg2, HWAC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWA6)) { Store (Arg3, HWA6) }
                If (LGreater(Arg2, HWAB)) {
                    Store (Arg2, HWAB)
                    Store (Arg2, HWAA)
                }
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (Arg3, HWA6) // Index A6: FAN1 Boundary 1 Temperature
                Store (Arg2, HWAB) // Index AB: FAN1 SEGMENT 2 SPEED COUNT
                Store (Arg2, HWAA) // Index AA: FAN1 SEGMENT 1 SPEED COUNT
                // Update Third low point if it has value lower
                If (LLess(Arg3, HWA7)) { Store (Arg3, HWA7) }
                If (LLess(Arg2, HWAC)) { Store (Arg2, HWAC) }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWA8)) { Store (Arg3, HWA8) }
                If (LLess(Arg2, HWAD)) { Store (Arg2, HWAD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWA9)) { Store (Arg3, HWA9) }
                If (LLess(Arg2, HWAE)) { Store (Arg2, HWAE) }
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (Arg3, HWA8) // Index A8: FAN1 Boundary 3 Temperature
                Store (Arg2, HWAD) // Index AD: FAN1 SEGMENT 4 SPEED COUNT
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWA7)) { Store (Arg3, HWA7) }
                If (LGreater(Arg2, HWAC)) { Store (Arg2, HWAC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWA6)) { Store (Arg3, HWA6) }
                If (LGreater(Arg2, HWAB)) {
                    Store (Arg2, HWAB)
                    Store (Arg2, HWAA)
                }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWA9)) { Store (Arg3, HWA9) }
                If (LLess(Arg2, HWAE)) { Store (Arg2, HWAE) }
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (Arg3, HWA7) // Index A7: FAN1 Boundary 2 Temperature
                Store (Arg2, HWAC) // Index AC: FAN1 SEGMENT 3 SPEED COUNT
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWA6)) { Store (Arg3, HWA6) }
                If (LGreater(Arg2, HWAB)) {
                    Store (Arg2, HWAB)
                    Store (Arg2, HWAA)
                }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWA8)) { Store (Arg3, HWA8) }
                If (LLess(Arg2, HWAD)) { Store (Arg2, HWAD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWA9)) { Store (Arg3, HWA9) }
                If (LLess(Arg2, HWAE)) { Store (Arg2, HWAE) }
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
#if ASL_F81966_SMF2_SUPPORT && ASL_F81966_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_2_STRING)) {
            // FAN2 SEGMENT 1 SPEED COUNT Index BAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (Arg3, HWB9) // Index B9: FAN2 Boundary 4 Temperature
                Store (Arg2, HWBE) // Index BE: FAN2 SEGMENT 5 SPEED COUNT
                // Update secondary low point if it has value higher
                If (LGreater(Arg3, HWB8)) { Store (Arg3, HWB8) }
                If (LGreater(Arg2, HWBD)) { Store (Arg2, HWBD) }
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWB7)) { Store (Arg3, HWB7) }
                If (LGreater(Arg2, HWBC)) { Store (Arg2, HWBC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWB6)) { Store (Arg3, HWB6) }
                If (LGreater(Arg2, HWBB)) {
                    Store (Arg2, HWBB)
                    Store (Arg2, HWBA)
                }
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (Arg3, HWB6) // Index B6: FAN2 Boundary 1 Temperature
                Store (Arg2, HWBB) // Index BB: FAN2 SEGMENT 2 SPEED COUNT
                Store (Arg2, HWBA) // Index BA: FAN2 SEGMENT 1 SPEED COUN
                // Update Third low point if it has value lower
                If (LLess(Arg3, HWB7)) { Store (Arg3, HWB7) }
                If (LLess(Arg2, HWBC)) { Store (Arg2, HWBC) }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWB8)) { Store (Arg3, HWB8) }
                If (LLess(Arg2, HWBD)) { Store (Arg2, HWBD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWB9)) { Store (Arg3, HWB9) }
                If (LLess(Arg2, HWBE)) { Store (Arg2, HWBE) }
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (Arg3, HWB8) // Index B8: FAN2 Boundary 3 Temperature
                Store (Arg2, HWBD) // Index BD: FAN2 SEGMENT 4 SPEED COUNT
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWB7)) { Store (Arg3, HWB7) }
                If (LGreater(Arg2, HWBC)) { Store (Arg2, HWBC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWB6)) { Store (Arg3, HWB6) }
                If (LGreater(Arg2, HWBB)) {
                    Store (Arg2, HWBB)
                    Store (Arg2, HWBA)
                }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWB9)) { Store (Arg3, HWB9) }
                If (LLess(Arg2, HWBE)) { Store (Arg2, HWBE) }
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (Arg3, HWB7) // Index B7: FAN2 Boundary 2 Temperature
                Store (Arg2, HWBC) // Index BC: FAN2 SEGMENT 3 SPEED COUNT
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWB6)) { Store (Arg3, HWB6) }
                If (LGreater(Arg2, HWBB)) {
                    Store (Arg2, HWBB)
                    Store (Arg2, HWBA)
                }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWB8)) { Store (Arg3, HWB8) }
                If (LLess(Arg2, HWBD)) { Store (Arg2, HWBD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWB9)) { Store (Arg3, HWB9) }
                If (LLess(Arg2, HWBE)) { Store (Arg2, HWBE) }
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
#if ASL_F81966_SMF3_SUPPORT && ASL_F81966_FAN_3_SUPPORT
        If (LEqual(Arg0, ASL_F81966_FAN_3_STRING)) {
            // FAN3 SEGMENT 1 SPEED COUNT Index CAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (Arg3, HWC9) // Index C9: FAN3 Boundary 4 Temperature
                Store (Arg2, HWCE) // Index CE: FAN3 SEGMENT 5 SPEED COUNT
                // Update secondary low point if it has value higher
                If (LGreater(Arg3, HWC8)) { Store (Arg3, HWC8) }
                If (LGreater(Arg2, HWCD)) { Store (Arg2, HWCD) }
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWC7)) { Store (Arg3, HWC7) }
                If (LGreater(Arg2, HWCC)) { Store (Arg2, HWCC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWC6)) { Store (Arg3, HWC6) }
                If (LGreater(Arg2, HWCB)) {
                    Store (Arg2, HWCB)
                    Store (Arg2, HWCA)
                }
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (Arg3, HWC6) // Index C6: FAN3 Boundary 1 Temperature
                Store (Arg2, HWCB) // Index CB: FAN3 SEGMENT 2 SPEED COUNT
                Store (Arg2, HWCA) // Index CA: FAN3 SEGMENT 1 SPEED COUN
                // Update Third low point if it has value lower
                If (LLess(Arg3, HWC7)) { Store (Arg3, HWC7) }
                If (LLess(Arg2, HWCC)) { Store (Arg2, HWCC) }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWC8)) { Store (Arg3, HWC8) }
                If (LLess(Arg2, HWCD)) { Store (Arg2, HWCD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWC9)) { Store (Arg3, HWC9) }
                If (LLess(Arg2, HWCE)) { Store (Arg2, HWCE) }
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (Arg3, HWC8) // Index C8: FAN3 Boundary 3 Temperature
                Store (Arg2, HWCD) // Index CD: FAN3 SEGMENT 4 SPEED COUNT
                // Update Third low point if it has value higher
                If (LGreater(Arg3, HWC7)) { Store (Arg3, HWC7) }
                If (LGreater(Arg2, HWCC)) { Store (Arg2, HWCC) }
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWC6)) { Store (Arg3, HWC6) }
                If (LGreater(Arg2, HWCB)) {
                    Store (Arg2, HWCB)
                    Store (Arg2, HWCA)
                }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWC9)) { Store (Arg3, HWC9) }
                If (LLess(Arg2, HWCE)) { Store (Arg2, HWCE) }
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (Arg3, HWC7) // Index C7: FAN3 Boundary 2 Temperature
                Store (Arg2, HWCC) // Index CC: FAN3 SEGMENT 3 SPEED COUNT
                // Update Highest point if it has value higher
                If (LGreater(Arg3, HWC6)) { Store (Arg3, HWC6) }
                If (LGreater(Arg2, HWCB)) {
                    Store (Arg2, HWCB)
                    Store (Arg2, HWCA)
                }
                // Update Secondary low point if it has value lower
                If (LLess(Arg3, HWC8)) { Store (Arg3, HWC8) }
                If (LLess(Arg2, HWCD)) { Store (Arg2, HWCD) }
                // Update Lowest point if it has value lower
                If (LLess(Arg3, HWC9)) { Store (Arg3, HWC9) }
                If (LLess(Arg2, HWCE)) { Store (Arg2, HWCE) }
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif
        Return (Local0)
    }
#endif // F81966_SMF_SUPPORT