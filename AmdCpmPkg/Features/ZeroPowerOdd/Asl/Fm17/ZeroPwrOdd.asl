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
    "ZeroPwrOdd.aml",                                   // Output file
    "SSDT",                                             // Signature
    0x01,                                               // SSDT Revision
    "AMD",                                              // OEM ID
    "CPMZPODD",                                         // OEM Table ID
    0x1                                                 // OEM Revision
    )
{
    #define CPM_ZERO_POWER_ODD

    #include "CmnDef.asi"
    #include "CmnExt.asi"
    #include "PostCode.asi"

    External(\_SB.PCI0.GP18.SATA, DeviceObj)
    External(\_SB.PCI0.GP18.SATA._ADR, MethodObj)
    External(\_SB.PCI0.LPC0.EC0, DeviceObj)

    External(STDV, MethodObj)
    External(STFN, MethodObj)
    External(\_SB.PCI0.LPC0.EC0.OKEC, MethodObj)

    // ODD Zero Power support at SATA Port 1 scope on AHCI mode
    Scope(\_SB.PCI0.GP18.SATA) {
        //
        // _DSM Device Specific Method
        //
        // Arg0:   UUID      Unique function identifier
        // Arg1:   Integer   Revision Level
        // Arg2:   Integer   Function Index (0 = Return Supported Functions)
        // Arg3:   Package   Parameters
        //
        Method(_DSM, 4, Serialized) {
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
            //
            // If(LEqual(Arg0,ToUUID("3DDDFAA6-361B-4eb4-A424-8D10089D1653")))
            //
            // Note: ToUUID function is available only to ACPI 3.0 compliant ASL compilers.
            //  The ToUUID function is equivalent to an ASCII string to hex conversion in the
            //  following specified order:
            //
            //    For a given ASCII UUID string formatted as:
            //      "AABBCCDD-EEFF-GGHH-IIJJ-KKLLMMNNOOPP",
            //    where AA-PP represent ASCII strings of hexidecimal numbers.  ToUUID() of
            //    this string returns a buffer containing the integer conversion of aa-pp:
            //      Buffer(0x10){DD,CC,BB,AA,FF,EE,HH,GG,II,JJ,KK,LL,MM,NN,OO,PP}
            //
            //  Therefore, ToUUID("E4DB149B-FCFE-425b-A6D8-92357D78FC7F") equals
            //  Buffer(){0x9B,0x14,0xDB,0xE4,0xFE,0xFC,0x5B,0x42,0xD8,0xA6,0x7F,0xFC,0x78,0x7D,0x35,0x92}
            //
            If (LEqual(XCMP(Arg0, Buffer(){0x9B, 0x14, 0xDB, 0xE4, 0xFE, 0xFC, 0x5B, 0x42, 0xA6, 0xD8, 0x92, 0x35, 0x7D, 0x78, 0xFC, 0x7F}), 1)) {
                // Function 0: return supported functions
                //
                // Returns:
                //   Functions 1-2 are supported
                //
                If (LEqual(Arg2, 0)) {
                    Return(Buffer(){0x03})

                //
                // Function 1: Query Link Power Interface
                //
                // Returns:
                //   A package of Integers, where each package element is the address
                //   (_ADR value) of child devices (ports) where link power controls may
                //   inhibit device enumeration.
                //
                } ElseIf (LEqual(Arg2, 1)) {
                    Name(ADDR, Package(){0x0001FFFF})
                    Store(Add(Multiply(Local4, 0x10000), 0x0000FFFF), Index(ADDR, 0))
                    Return(Package(){ADDR})

                //
                // Function 2: Control Link Power
                //   Arg3:  Device address, Requested link power state (Package with two entries)
                //      Entry 1 - Device address (as described in the ACPI specification _ADR Object Encoding table). Note that "Ones" (ASL constant) applies setting to all possible devices.
                //      Entry 2 - Link power control value:
                //              0x00: allow link power to be removed
                //              0x01: apply power to link and child device(s)
                //
                // Returns:
                //   0: Success
                //   1: Invalid device address
                //
                } ElseIf (LEqual(Arg2, 2)) {
                    Store(DeRefOf(Index(Arg3, 0)), Local0)
                    If (LOr(LEqual(Local0, Add(Multiply(Local4, 0x10000), 0x0000FFFF)), LEqual(Local0, Ones))) {
                        Store(DeRefOf(Index(Arg3, 1)), Local1)
                        If (LEqual(Local1, 0)) {
                            \_SB.PCI0.GP18.SATA.STPT(0)              // Disable PHY Port 1
                            Return(0)
                        } ElseIf (LEqual(Local1, 1)) {
                            If (CpmIsWin8()) {
                                \_SB.PCI0.GP18.SATA.ODD8._PS0()      // _PS0 implicitly enables PHY Port 1
                            } Else {
                                \_SB.PCI0.GP18.SATA.ODDZ._PS0()      // _PS0 implicitly enables PHY Port 1
                            }
                            Return(0)
                        }
                    }
                }
            }
            Return(1)
        } // End of Method(_DSM,4, Serialized)

        // XCMP - Since ACPI 1.0 compliant OS does not understand LEqual() of two buffers,
        //        this function does a UUID buffer compare of UUID1 to UUID2.
        //
        // Arg0:    Buffer   UUID1
        // Arg1:    Buffer   UUID2
        //
        // Output:  1 = Compare success
        //          0 = Compare Failure
        //
        Method(XCMP, 2) {
            // Each buffer must be 16 bytes long or it's not a UUID
            If (LNotEqual(0x10, SizeOf(Arg0))) {
                Return(0)
            }
            If (LNotEqual(0x10, SizeOf(Arg1))) {
                Return(0)
            }

            // Start loop at beginning of buffer
            Store(0, Local0)

            // Check each byte in each buffer for a match
            While (LLess(Local0, 16)) {
                If (LNotEqual(DerefOf(Index(Arg0, Local0)), DerefOf(Index(Arg1, Local0)))) {
                    Return(0)
                }
                Increment(Local0)
            }

            Return(1)
        } // End of Method(XCMP, 2)

        Method(STDV, 0, Serialized) {
            Store(_ADR, Local0)
            Return(ShiftRight(Local0, 16))
        }

        Method(STFN, 0, Serialized) {
            Store(_ADR, Local0)
            Return(And(Local0, 0xFFFF))
        }

        Method(PBAA, 0, Serialized) {
//          Store(CpmReadPci32(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x24), Local0)
            Store (CpmReadSmnRegister (0, 0, 0, 0x10148024), Local0)
            If (LEqual(Local0, 0xFFFFFFFF)) {
                Store(0, Local0)
            }
            Return(Local0)
        }

        // Enable/Disable Sata Port
        // Arg0 - 0: Disable. 1: Enable
        Method(STPT, 1, Serialized) {
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
            // Enable PHY Port n
//          CpmWritePci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x42, Local4, 1, Xor(Arg0, 1))
            If (LEqual (Arg0, 0))
            {
              Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C)), Local0)
              Add (And (Local0, 0xFFFFFFF0), 4, Local0)
              CpmWriteSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C), Local0)

              Store (1, Local1)
              Store (20, Local2)
              while (LAnd (Local1, Local2)) {
                Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x03101128)), Local0)
                And (Local0, 0xF, Local0)
                if (LEqual (Local0, 0x4)) {
                    Store (0, Local1)
                } else {
                    Stall (100)
                    Decrement (Local2)
                }
              } // end of while (LAnd (Local1, Local2))
            }

            Store (CpmReadSmnRegister (0, 0, 0, 0x03101800), Local0)
            And (Local0, Xor (0xFFFFFFFF, ShiftLeft (1, Add (Local4, 16))), Local0)
            ShiftLeft (Xor (Arg0, 1), Add (Local4, 16), Local1)
            Or (Local0, Local1, Local0)
            CpmWriteSmnRegister (0, 0, 0, 0x03101800, Local0)

            If (LEqual (Arg0, 1))
            {
              Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C)), Local0)
              And (Local0, 0xFFFFFFF0, Local0)
              CpmWriteSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C), Local0)

              Store (1, Local1)
              Store (20, Local2)
              while (LAnd (Local1, Local2)) {
                Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x03101128)), Local0)
                And (Local0, 0xF, Local0)
                if (LEqual (Local0, 0)) {
                    Store (0, Local1)
                } else {
                    Stall (100)
                    Decrement (Local2)
                }
              } // end of while (LAnd (Local1, Local2))
            }
        }

        // Enable/Disable Sata Port Phy
        // Arg0 - 0: Disable. 1: Enable
        Method(STPP, 1, Serialized) {
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
            // Enable PHY Port n
//          CpmWritePci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x42, Local4, 1, Xor(Arg0, 1))
            \_SB.PCI0.GP18.SATA.STPT(Arg0)                // Disable PHY Port 1

//          If (LEqual(CpmReadPci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x0A, 0, 16), 0x106)) {
            If (LEqual (ShiftRight (CpmReadSmnRegister (0, 0, 0, 0x10148008), 16), 0x106)) {
                If (LNotEqual(PBAA(), 0)) {
                    // Write Enable
//                  CpmWritePci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x40, 0, 1, 1)
                    Store (CpmReadSmnRegister (0, 0, 0, 0x03101800), Local0)
                    Or (Local0, 1, Local0)
                    CpmWriteSmnRegister (0, 0, 0, 0x03101800, Local0)
                    // Port n implemented
//                  CpmWriteMem32(PBAA(), 0x0C, Local4, 1, Arg0)
                    Store (CpmReadSmnRegister (0, 0, 0, 0x0310100C), Local0)
                    And (Local0, Xor (0xFFFFFFFF, ShiftLeft(1, Local4)), Local0)
                    ShiftLeft (Arg0, Local4, Local1)
                    Or (Local0, Local1, Local0)
                    If (LEqual (Local0, 0)) {
                        Or (Local0, 1, Local0)
                    }
                    CpmWriteSmnRegister (0, 0, 0, 0x0310100C, Local0)
//                  // Port Status
//                  Store(CpmReadPci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x42, 0, 6), Local0)
//                  // at lease reserve one port enabled
//                  If (LEqual(Local0, 0x3F)) {
//                      // Enable Port 0
//                      CpmWriteMem32(PBAA(), 0x0C, 0, 1, 1)
//                  } ElseIf (LAnd(CpmReadPci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x42, 0, 1), Xor(And(Local0, 0x3E), 0x3E))) {
//                      // Disable Port 0
//                      CpmWriteMem32(PBAA(), 0x0C, 0, 1, 0)
//                  }
                    // Port Implement
//                  Store(CpmReadMem32(PBAA(), 0x0C, 0, 6), Local1)
                    Store (Local0, Local1)
                    Store(0, Local2)
                    While (Local1) {
                        If (And(Local1, 0x01)) {
                            Increment(Local2)
                        }
                        ShiftRight(Local1, 1, Local1)
                    }
                    // Update Port Number
//                  CpmWriteMem32(PBAA(), 0, 0, 5, Decrement(Local2))
                    Store (CpmReadSmnRegister (0, 0, 0, 0x03101000), Local0)
                    And (Local0, 0xFFFFFFE0, Local0)
                    Or (Local0, Decrement(Local2), Local0)
                    CpmWriteSmnRegister (0, 0, 0, 0x03101000, Local0)
                    // Write Disable
//                  CpmWritePci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x40, 0, 1, 0)
                    Store (CpmReadSmnRegister (0, 0, 0, 0x03101800), Local0)
                    And (Local0, 0xFFFFFFFE, Local0)
                    CpmWriteSmnRegister (0, 0, 0, 0x03101800, Local0)
                }
            }
        } // End of Method(STPP, 1, Serialized)

        // Get Port Interface power management
        Method(STPM, 0, Serialized) {
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
            Store(0, Local1)
            If (LNotEqual(PBAA(), 0)) {
//              // 0x118 + ZPPT * 0x80:[0] Port Start
//              Store(Add(0x118, Multiply(0x80, Local4)), Local0)
//              // Interface power management
//              Store(CpmReadMem32(PBAA(), Local0, 0, 1), Local0)
                Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x03101118)), Local0)
                And (Local0, 1, Local0)
            }
            Return(Local1)
        }

        // Port reset in AHCI mode
        Method(STPR, 0, Serialized) {
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
//          If (LEqual(CpmReadPci(CpmGetInternalBusNumber(1), STDV(), STFN(), 0x0A,0, 16), 0x106)) {
            If (LEqual (ShiftRight (CpmReadSmnRegister (0, 0, 0, 0x10148008), 16), 0x106)) {
                If (LNotEqual(PBAA(), 0)) {
//                  // 0x118 + ZPPT * 0x80:[0] Port Start
//                  Store(Add(0x118, Multiply(0x80, Local4)), Local0)
//                  // Clear Px.CMS.ST bit
//                  CpmWriteMem32(PBAA(), Local0, 0, 1, 0)
                    Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x03101118)), Local0)
                    And (Local0, 0xFFFFFFFE, Local0)
                    CpmWriteSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x03101118), Local0)
                    // wait for 1ms
                    Sleep(1)
//                  // 0x12C + ZPPT * 0x80:[3:0] device detection Initialization
//                  Store(Add(0x12C, Multiply(0x80, Local4)), Local0)
                    // Assert port reset
//                  CpmWriteMem32(PBAA(), Local0, 0, 4, 1)
                    Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C)), Local0)
                    And (Local0, 0xFFFFFFF0, Local0)
                    Or (Local0, 1, Local0)
                    CpmWriteSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C), Local0)
                    // wait for 2ms
                    Sleep(2)
                    // De-assert port reset
//                  CpmWriteMem32(PBAA(), Local0, 0, 4, 0)
                    Store (CpmReadSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C)), Local0)
                    And (Local0, 0xFFFFFFF0, Local0)
                    CpmWriteSmnRegister (0, 0, 0, Add (Multiply (Local4, 0x80), 0x0310112C), Local0)
                }
            }
        }

        Device(PRT1) {
            // Address for Port 1 (ODD)
            // FFFF in Lower WORD indicates
            // no Port Multiplier
            Name(_ADR, 0x00000001)

            Method(_STA, 0) {
                Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
                // ODD Zero Power Enabled
                If (And(Local0, 1)) {
                    // Disable ODD - ODDZ needto be enabled
                    Return(0x0)
                } Else {
                    // Enable ODD - ODDZ need to be disabled
                    Return(0xF)
                }
            }

            Device(ODD) {
                Method(_ADR) {
                    Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddSataPortId), Local4)
                    Return(Local4)
                }

                // Set Device Removable icon for MS hot-fix KB950186 Vista
                Method(_RMV, 0) {
                    Return(0x00)
                }
            } // End of Device(ODD)
        } // End of Device(PRT1)

        Device(ODD8) {
            #include "Odd8Device.asi"
        }

        Device(ODDZ) {
            #include "OddZDevice.asi"
        }

        Name(SAPO, 0x0)
        Name(SACB, 0x0)
        Name(SASS, 0x0)

        //
        // CPM SATA TPTS interface method
        //  Arg0 - An Integer containing the value of the sleeping state (1 for S1, 2 for S2, etc.)
        //
        Method (TPTS, 1) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            // ODD Zero Power is enabled, and ODD Hotplug is enabled.
            If (LEqual(And(Local0, 3), 3)) {
                // Source of ODD_PLUGIN# - 0: FCH GPIO/GEVENT Pin
                If (LEqual(Local6, 0)) {
                    If (CpmReadGevent(Local3)) {
                        Store(0x1, \_SB.PCI0.GP18.SATA.SAPO)
                    } Else {
                        Store(0x0, \_SB.PCI0.GP18.SATA.SAPO)
                    }
                // Source of ODD_PLUGIN# - 1: KBC GPIO/QEVENT Pin, 2: ECRAM GPIO/QEVENT Pin
                } Else {
                    If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                        If (CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8)))) {
                            Store(0x1, \_SB.PCI0.GP18.SATA.SAPO)
                        } Else {
                            Store(0x0, \_SB.PCI0.GP18.SATA.SAPO)
                        }
                    }
                }
            }
        }

        //
        // CPM SATA TWAK interface method
        //  Arg0 - An Integer containing the value of the sleeping state (1 for S1, 2 for S2, etc.)
        //
        Method (TWAK, 1) {
            Store(Arg0, \_SB.PCI0.GP18.SATA.SASS)
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            // ODD Zero Power is enabled, and ODD Hotplug is enabled.
            If (LEqual(And(Local0, 3), 3)) {
                // Source of ODD_PLUGIN# - 0: FCH GPIO/GEVENT Pin
                If (LEqual(Local6, 0)) {
                    If (CpmReadGevent(Local3)) {
                        If (LAnd(LEqual(Arg0, 4), LEqual(\_SB.PCI0.GP18.SATA.SAPO, 0x0))) {
                            If (LNot(CpmIsWin8())) {
                                Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                                Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                            }
                        }
                    }
                // Source of ODD_PLUGIN# - 1: KBC GPIO/QEVENT Pin, 2: ECRAM GPIO/QEVENT Pin
                } Else {
                    If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                        If (CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8)))) {
                            If (LAnd(LEqual(Arg0, 3), LEqual(\_SB.PCI0.GP18.SATA.SAPO, 0x0))) {
                                If (LNot(CpmIsWin8())) {
                                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                                }
                            } ElseIf (LAnd(LEqual(Arg0, 4), LEqual(\_SB.PCI0.GP18.SATA.SAPO, 0x0))) {
                                If (LNot(CpmIsWin8())) {
                                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                                }
                            }
                        }
                    }
                }
            }
        }

    } // End of Scope(\_SB.PCI0.GP18.SATA)

    //
    // General-Purpose Event
    //
    Scope(\_GPE) {
        //
        // ODD_DA#
        //
        Method(XL06, 0x0, Notserialized) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin1), Local2)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(0x0, Local7)
            // Check ODD_PLUGIN# status when Odd Hot Plug is enabled.
            If (And(Local0, 0x2)) {
                Store(CpmReadGevent(Local3), Local7)
            }
            // Handle ODD_DA# only when ODD_PLUGIN# is low (ODD is present)
            If (LEqual(Local7, 0x0)) {
                // Handle ODD_DA# only when ODD_DA# is low
                If (LEqual(CpmReadGevent(Local2), 0x0)) {
                    CpmSetPostCode(CpmTpZeroPowerOddInsertEvent_ODD_DA)
                    If (And(Local0, 0x10)) {
                        // Apply a port reset in AHCI mode
                        \_SB.PCI0.GP18.SATA.STPR()
                    }
                    // Notify for different OS mode
                    If (CpmIsWin8()) {
                        Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x02)
                    } Else {
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x80)
                    }
                }
            }
        } // End of Method(XL06, 0x0, Notserialized)

        //
        // ODD_PLUGIN#
        //
        Method(XL10) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddDeviceId), Local1)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            // Let ODD_PLUGIN# signal input debounce for 200ms
            Sleep(200)
            // ODD_PLUGIN# input level = High, hot remove
            If (CpmReadGeventTriggerType(Local3)) {
                // Did we get Rising Edge (Removal)?
                If (CpmReadGevent(Local3)) {
                    CpmSetPostCode(CpmTpZeroPowerOddRemoveEvent_ODD_PLUGIN)
                    CpmSetDevicePower(Local1, 0)
                    If (CpmIsWin8()) {
                        Store(0, \_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus)
                    } Else {
                        Store(0, \_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus)
                    }
                    Sleep(40)
                    // Disable Port
                    \_SB.PCI0.GP18.SATA.STPP(0)
                    If (CpmIsWin8()) {
                        Store(0x3, \_SB.PCI0.GP18.SATA.ODD8.ODPS)
                    } Else {
                        Store(0x3, \_SB.PCI0.GP18.SATA.ODDZ.ODPS)
                    }
                    // Switch SB detection logic to raising edge
                    CpmWriteGeventTriggerType(Local3, Xor(CpmReadGevent(Local3), 1))
                }
            } Else {
                // Let GEVENT16# signal input debounce for 20ms
                Sleep(20)
                // If GEVENT6# input value is Low then card is present
                If (LNot(CpmReadGevent(Local3))) {
                    CpmSetPostCode(CpmTpZeroPowerOddInsertEvent_ODD_PLUGIN)
                    // Enable Port
                    \_SB.PCI0.GP18.SATA.STPP(1)
                    Sleep(40)
                    // Power On ODD
                    CpmSetDevicePower(Local1, 1)
                    Sleep(40)
                    If (CpmIsWin8()) {
                        Store(1, \_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus)
                    } Else {
                        Store(1, \_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus)
                    }
                    // Apply a port reset in AHCI mode
//                  \_SB.PCI0.GP18.SATA.STPR()
                    If (CpmIsWin8()) {
                        Store(0x0, \_SB.PCI0.GP18.SATA.ODD8.ODPS)
                    } Else {
                        Store(0x0, \_SB.PCI0.GP18.SATA.ODDZ.ODPS)
                    }
                    // Switch SB detection logic to raising edge
                    CpmWriteGeventTriggerType(Local3, Xor(CpmReadGevent(Local3), 1))
                }
            }
            // Sleep 40ms
            Sleep(40)

            If (And(Local0, 1)) {
                If (CpmIsWin8()) {
                    Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x1)
                } Else {
                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                    Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                }
            } Else {
                Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x1)
                // for AMDAHCI's prior to Win8 driver, extra requirement for plug in
                If (LNot(CpmIsWin8())) {
                    Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x81)
                }
            }
        } // End of Method(XL10)
    } // End of Scope(\_GPE)

    //
    // EC QEvent
    //
    Scope(\_SB.PCI0.LPC0.EC0) {
        //
        // ODD_DA# RISING
        //
        Method(XQ43, 0x0, Serialized) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                Store(CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8))), Local7)
            } Else {
                Store(0x0, Local7)
            }
            If (LNot(And(Local0, 2))) {
                Store(0x1, Local6)
                Store(0x0, Local7)
            }
            // Source of ODD_PLUGIN# == 1 or 2 KBC/ECRAM GPIO/QEVENT Pin; and ODD_PLUGIN# is Low level.
            If (LAnd(Local6, And(Not(Local7), 1))) {
                If (And(Local0, 0x10)) {
                    // Apply a port reset in AHCI mode
                    \_SB.PCI0.GP18.SATA.STPR()
                }
                If (CpmIsWin8()) {
                    If (LEqual(\_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus, 0)) {
                        Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x02)
                        CpmSetPostCode(CpmTpZeroPowerOddRemoveQEvent_ODD_DA)
                    }
                } Else {
                    If (LEqual(\_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus, 0)) {
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x80)
                        CpmSetPostCode(CpmTpZeroPowerOddRemoveQEvent_ODD_DA)
                    }
                }
            }
        } // End of Method(XQ43, 0x0, Serialized)

        //
        // ODD_DA# FALLING
        //
        Method(XQ42, 0x0, Serialized) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                Store(CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8))), Local7)
            } Else {
                Store(0x0, Local7)
            }
            If (LNot(And(Local0, 2))) {
                Store(0x1, Local6)
                Store(0x0, Local7)
            }
            // Source of ODD_PLUGIN# == 1 or 2 KBC/ECRAM GPIO/QEVENT Pin; and ODD_PLUGIN# is Low level.
            If (LAnd(Local6, And(Not(Local7), 1))) {
                If (CpmIsWin8()) {
                    If (LEqual(\_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus, 0)) {
                        Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x02)
                        CpmSetPostCode(CpmTpZeroPowerOddInsertQEvent_ODD_DA)
                    }
                } Else {
                    If (LEqual(\_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus, 0)) {
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x80)
                        CpmSetPostCode(CpmTpZeroPowerOddInsertQEvent_ODD_DA)
                    }
                }
            }
        } // End of Method(XQ42, 0x0, Serialized)

        //
        // ODD_PLUGIN# RISING
        //
        Method(XQ41, 0x0, Serialized) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddDeviceId), Local1)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                Store(CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8))), Local7)
            } Else {
                Store(0x1, Local7)
            }
            // Source of ODD_PLUGIN# == 1 or 2 KBC/ECRAM GPIO/QEVENT Pin; and ODD_PLUGIN# is High level.
            If (LAnd(Local6, Local7)) {
                CpmSetPostCode(CpmTpZeroPowerOddRemoveQEvent_ODD_PLUGIN)
                CpmSetDevicePower(Local1, 0)
                If (CpmIsWin8()) {
                    Store(0, \_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus)
                } Else {
                    Store(0, \_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus)
                }
                Sleep(40)
                // Disable Port
                \_SB.PCI0.GP18.SATA.STPP(0)
                If (CpmIsWin8()) {
                    Store(0x3, \_SB.PCI0.GP18.SATA.ODD8.ODPS)
                } Else {
                    Store(0x3, \_SB.PCI0.GP18.SATA.ODDZ.ODPS)
                }
                Sleep(40)
                If (And(Local0, 1)) {
                    If (CpmIsWin8()) {
                        Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x1)
                    } Else {
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                    }
                } Else {
                    Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x1)
                    // for AMDAHCI's prior to Win8 driver, extra requirement for plug in
                    If (LNot(CpmIsWin8())) {
                        Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x81)
                    }
                }
            }
        } // End of Method(XQ41, 0x0, Serialized)

        //
        // ODD_PLUGIN# FALLING
        //
        Method(XQ40, 0x0, Serialized) {
            Store(CpmReadTable(CpmMainTable, CpmZeroPowerOddEn), Local0)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddDeviceId), Local1)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventPin2), Local3)
            Store(CpmReadTable(CpmZeroPowerOddTable, CpmZeroPowerOddEventSource2), Local6)
            If (LEqual(\_SB.PCI0.LPC0.EC0.OKEC, 0x01)) {
                Store(CpmReadGpio(Add(Local3, ShiftLeft(Local6, 8))), Local7)
            } Else {
                Store(0x0, Local7)
            }
            // Source of ODD_PLUGIN# == 1 or 2 KBC/ECRAM GPIO/QEVENT Pin; and ODD_PLUGIN# is Low level.
            If (LAnd(Local6, And(Not(Local7), 1))) {
                CpmSetPostCode(CpmTpZeroPowerOddInsertQEvent_ODD_PLUGIN)
                Sleep(40)
                // Enable Port
                \_SB.PCI0.GP18.SATA.STPP(1)
                Sleep(40)
                If (CpmIsWin8()) {
                    Store(0x0, \_SB.PCI0.GP18.SATA.ODD8.ODPS)
                } Else {
                    Store(0x0, \_SB.PCI0.GP18.SATA.ODDZ.ODPS)
                }
                // Power On ODD
                CpmSetDevicePower(Local1, 1)
                Sleep(40)
                If (CpmIsWin8()) {
                    Store(1, \_SB.PCI0.GP18.SATA.ODD8.CpmOddStatus)
                } Else {
                    Store(1, \_SB.PCI0.GP18.SATA.ODDZ.CpmOddStatus)
                }
//                // Apply a port reset in AHCI mode
//                \_SB.PCI0.GP18.SATA.STPR()
//                Sleep(40)
                If (And(Local0, 1)) {
                    If (CpmIsWin8()) {
                        Notify(\_SB.PCI0.GP18.SATA.ODD8, 0x1)
                    } Else {
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x1)
                        Notify(\_SB.PCI0.GP18.SATA.ODDZ, 0x81)
                    }
                } Else {
                    Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x1)
                    // for AMDAHCI's prior to Win8 driver, extra requirement for plug in
                    If (LNot(CpmIsWin8())) {
                        Notify(\_SB.PCI0.GP18.SATA.PRT1, 0x81)
                    }
                }
            }
        } // End of Method(XQ40, 0x0, Serialized)
    } // // End of Scope(\_SB.PCI0.LPC0.EC0)
} // End of DefinitionBlock()

