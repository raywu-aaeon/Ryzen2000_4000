/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 * 
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 * 
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 * 
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 * 
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
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
