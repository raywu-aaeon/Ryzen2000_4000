/*****************************************************************************
 *
 * Copyright (C) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 ******************************************************************************
 */

DefinitionBlock (
    "Ec.aml",               // Output file
    "SSDT",                 // Signature
    0x01,                   // SSDT Revision
    "AMD",                  // OEM ID
    "CPMEC",                // OEM Table ID
    0x1                     // OEM Revision
    )
{
    #define CPM_EC_ASL

    #include "CmnDef.asi"
    #include "CmnExt.asi"

    External(\_SB.PCI0.LPC0.EC0, DeviceObj)

    //
    // Read Kbc Gpio
    //  Arg0 - offset
    //
    Method (CpmKbcRead8, 1, Serialized)
    {
        return (\_SB.PCI0.LPC0.EC0.CpmKbcRead8 (Arg0))
    }

    //
    // Write Kbc Gpio
    //  Arg0 - offset
    //  Arg1 - value
    //
    Method (CpmKbcWrite8, 2, Serialized)
    {
        \_SB.PCI0.LPC0.EC0.CpmKbcWrite8 (Arg0, Arg1)
    }

    //
    // Read Kbc Io
    //  Arg0 - IO port
    //
    Method (CpmKbcReadIo, 1, Serialized)
    {
        return (\_SB.PCI0.LPC0.EC0.CpmKbcReadIo (Arg0))
    }
    //
    // Write Kbc Io
    //  Arg0 - IO port
    //  Arg1 - value
    //
    Method (CpmKbcWriteIo, 2, Serialized)
    {
        \_SB.PCI0.LPC0.EC0.CpmKbcWriteIo (Arg0, Arg1)
    }
    //
    // Send data to KBC by checking IBE
    //  Arg0 - IO base port
    //  Arg1 - 1: Arg2 is a command; 0: Arg2 is a data
    //  Arg2 - data to write
    //  Arg3 - timeout (ms); 0 - don't check IBE, 0xFFFF - wait until IBE
    Method (CpmKbcCmd, 4, Serialized)
    {
        \_SB.PCI0.LPC0.EC0.CpmKbcCmd (Arg0, Arg1, Arg2, Arg3)
    }

    //
    // Get GPIO in Kbc
    //  Arg0 - offset
    //
    Method (CpmKbcReadGpio, 1, Serialized)
    {
        And (Arg0, 0x07, Local1)
        ShiftRight (Arg0, 0x03, Local2)
        Add (Local2, CpmEcRamGpioBaseOffset, Local2)
        Store (CpmKbcRead8 (Local2), Local0)
        ShiftRight (Local0, Local1, Local0)
        And (Local0, 0x01, Local0)
        Return (Local0)
    }

    //
    // Set GPIO pin in Kbc
    //  Arg0 - offset
    //  Arg1 - value
    //
    Method (CpmKbcWriteGpio, 2, Serialized)
    {
        And (Arg0, 0x07, Local1)
        ShiftRight (Arg0, 0x03, Local2)
        Add (Local2, CpmEcRamGpioBaseOffset, Local2)
        Store (CpmKbcRead8 (Local2), Local0)
        ShiftLeft (And (Arg1, 0x01), Local1, Local3)
        Xor (0xFF, ShiftLeft(0x01, Local1), Local4)
        And (Local0, Local4, Local0)
        CpmKbcWrite8 (Local2, Or (Local0, Local3))
        Store (CpmKbcRead8 (0xCF), Local0)
        CpmKbcWrite8 (0xCF, Or (Local0, 0x01))
    }

    Scope (\_SB.PCI0.LPC0.EC0)
    {

        //
        // Read Kbc Gpio
        //  Arg0 - offset
        //
        Method (CpmKbcRead8, 1, Serialized)
        {
            Store (0, Local1)
            If (CondRefOf(CpmKbcMutex))
            {
                Acquire (CpmKbcMutex, 0xFFFF)
                Store (Arg0, Local0)
                OperationRegion (varM, EmbeddedControl, Local0, 0x1)
                    Field(varM, ByteAcc, NoLock, Preserve) {
                        varR, 8,
                    }
                Store (varR, Local1)
                Release (CpmKbcMutex)
            }
            return (Local1)
        }

        //
        // Write Kbc Gpio
        //  Arg0 - offset
        //  Arg1 - value
        //
        Method (CpmKbcWrite8, 2, Serialized)
        {
            If (CondRefOf(CpmKbcMutex))
            {
                Acquire (CpmKbcMutex, 0xFFFF)
                Store (Arg0, Local0)
                OperationRegion (varM, EmbeddedControl, Local0, 0x1)
                    Field(varM, ByteAcc, NoLock, Preserve) {
                        varR, 8,
                    }
                Store (Arg1, Local1)
                Store (Local1, varR)
                Release (CpmKbcMutex)
            }
        }

        //
        // Read Kbc Io
        //  Arg0 - IO port
        //
        Method (CpmKbcReadIo, 1, Serialized)
        {
            Store (Arg0, Local0)
            OperationRegion (varI, SystemIO, Local0, 0x1)
                Field(varI, ByteAcc, NoLock, Preserve) {
                    varO, 8,
                }
            Store (varO, Local1)
            return (Local1)
        }
        //
        // Write Kbc Io
        //  Arg0 - IO port
        //  Arg1 - value
        //
        Method (CpmKbcWriteIo, 2, Serialized)
        {
                Store (Arg0, Local0)
                OperationRegion (varI, SystemIO, Local0, 0x1)
                    Field(varI, ByteAcc, NoLock, Preserve) {
                        varO, 8,
                    }
                Store (Arg1, Local1)
                Store (Local1, varO)
        }
        //
        // Send cmd/data to KBC by checking IBE
        //  Arg0 - IO base port
        //  Arg1 - 0 - Arg2 is a data byte
        //         1 - Arg2 is a command byte
        //  Arg2 - data to write
        //  Arg3 - 0      - don't check IBE
        //         0xFFFF - wait until IBE
        //         Other value from 1 to 0xFFFE - timeout (MS)
        Method (CpmKbcCmd, 4, Serialized)
        {
            If (CondRefOf(CpmKbcMutex)) {
                Acquire (CpmKbcMutex, 0xFFFF)
                                         // Arg0   - base/data port
                Add   (Arg0, 4, Local1)  // Local1 - cmd/state port
                // Wait Input-Buffer-Empty
                If (LNotEqual(Arg3, 0)) {
                  Store (Arg3, Local2)     // Local2 - timeout
                  Store (CpmKbcReadIo(Local1), Local0)
                  While (LAnd (Local2, And(Local0, 0x02))) {
                      Sleep(1)
                      Store (CpmKbcReadIo(Local1), Local0)
                      if (LNotEqual (Local2, 0xFFFF)) {
                          Decrement(Local2)
                      }
                  }
                }
                // Write the data
                If (LNotEqual(Arg1, 0)) { // Arg2 is command
                    CpmKbcWriteIo(Local1, Arg2)
                } Else {
                    CpmKbcWriteIo(Arg0,   Arg2)
                }
                Release (CpmKbcMutex)
            }
        }
    }
}
