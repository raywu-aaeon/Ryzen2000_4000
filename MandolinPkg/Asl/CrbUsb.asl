//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CrbUsb.asl
    This file contains code for CrbUsb ASL.

**/

//Sync with AMD demo BIOS
Scope(\_SB.PCI0.GP17.XHC0)
{

    Device (RHUB)
    {
                        Name (_ADR, Zero)  // _ADR: Address
                        Device(PRT1)
                        {
                            Name(_ADR, One)
                            Name(UPC1, Package(4) {0xFF, 0x09, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x09, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x11, 0x0C, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x11, 0x0C, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT2)
                        {
                            Name(_ADR, 0x02)
                            Name(UPC1, Package(4) {0xFF, 0x03, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x03, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT3)
                        {
                            Name(_ADR, 0x03)
                            Name(UPC1, Package(4) {0xFF, 0x03, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x03, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1C, 0x80, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1C, 0x80, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT4)
                        {
                            Name(_ADR, 0x04)
                            Name(UPC1, Package(4) {0xFF, 0x09, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x09, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1D, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1D, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT5)
                        {
                            Name(_ADR, 0x05)
                            Name(UPC1, Package(4) {0xFF, 0x09, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x03, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x11, 0x0C, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x11, 0x0C, 0x80, 0x02, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT6)
                        {
                            Name(_ADR, 0x06)
                            Name(UPC1, Package(4) {0xFF, 0x03, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0xFF, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x10, 0x0C, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT7)
                        {
                            Name(_ADR, 0x07)
                            Name(UPC1, Package(4) {0xFF, 0x03, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x09, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1C, 0x80, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x11, 0x0C, 0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT8)
                        {
                            Name(_ADR, 0x08)
                            Name(UPC1, Package(4) {0xFF, 0x09, Zero, Zero})
                            Name(UPC2, Package(4) {0xFF, 0x03, Zero, Zero})
                            Method(_UPC, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(UPC2)
                                }
                                Else
                                {
                                    Return(UPC1)
                                }
                            }
                            Name(PLD1, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1D, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Name(PLD2, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                            Method(_PLD, 0, Serialized)
                            {
                                If(RV2I)
                                {
                                    Return(PLD2)
                                }
                                Else
                                {
                                    Return(PLD1)
                                }
                            }
                        }
                        Device(PRT9)
                        {
                            Name(_ADR, 0x09)
                            Method(_STA, 0, NotSerialized)
                            {
                                If(RV2I)
                                {
                                    Return(0x0F)
                                }
                                Else
                                {
                                    Return(Zero)
                                }
                            }
                            Name(_UPC, Package(4) {0xFF, 0x03, Zero, Zero})
                            Name(_PLD, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1C, 0x80, 0x01, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                        }
                        Device(PRTA)
                        {
                            Name(_ADR, 0x0A)
                            Method(_STA, 0, NotSerialized)
                            {
                                If(RV2I)
                                {
                                    Return(0x0F)
                                }
                                Else
                                {
                                    Return(Zero)
                                }
                            }
                            Name(_UPC, Package(4) {0xFF, 0x09, Zero, Zero})
                            Name(_PLD, Package(1)
                            {
                                Buffer(0x14)
                                {
                                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    0x91, 0x1D, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 
                                    0xFF, 0xFF, 0xFF, 0xFF
                                }
                            })
                        }

     }// end of RHUB
} // end of XHC0
     
                        

Scope(\_SB.PCI0.GP17.XHC1)
{

    Device (RHUB)
    {
        Name (_ADR, Zero)  // _ADR: Address
        Device (PRT1)
        {
            Name(_ADR, One)
            Name(_UPC, Package(4) {0xFF, 0x03, Zero, Zero})
            Name(_PLD, Package(1)
            {
                Buffer(0x14)
                {
                    0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x11, 0x0C, 0x80, 0x02, 0x01, 0x00, 0x00, 0x00, 
                    0xFF, 0xFF, 0xFF, 0xFF
                }
            })
        }
        Device (PRT2)
        {
            Name(_ADR, 0x02)
            Name(_UPC, Package(4) {0xFF, 0xFF, Zero, Zero})
            Name(_PLD, Package(1)
            {
                Buffer(0x14)
                {
                0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x10, 0x0C, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 
                0xFF, 0xFF, 0xFF, 0xFF
                }
            })
        }
        Device (PRT3)
        {
            Name(_ADR, 0x03)
            Name(UPC1, Package(4) {0xFF, 0x03, Zero, Zero})
            Name(UPC2, Package(4) {Zero, 0x03, Zero, Zero})
            Method(_UPC, 0, Serialized)
            {
                If(ISDS)
                {
                    Return(UPC2)
                }
                Else
                {
                    Return(UPC1)
                }
            }
            Name(_PLD, Package(1)
            {
                Buffer(0x14)
                {
                0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                0x11, 0x0C, 0x80, 0x02, 0x01, 0x00, 0x00, 0x00, 
                0xFF, 0xFF, 0xFF, 0xFF
                }
            })
        }
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
