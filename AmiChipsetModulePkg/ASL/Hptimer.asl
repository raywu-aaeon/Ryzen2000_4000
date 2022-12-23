//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file Hptimer.asl
  This file is for SB/LPC HPET Timer.

  This file contains a declaration of ACPI device and ACPI methods
  implementation for South Bridge High Performance Event Timer (HPET).
  It should be included in the root of the namespace(\).

  Notes: GENERALLY NO PORTING REQUIRED.

*/

            Device(HPET)
            {
                Name(_HID, EISAID("PNP0103"))
                Method(_STA, 0, NotSerialized)
                {
                    If(LEqual(HPEN, One))
                    {
                        If(LGreaterEqual(OSVR,12)) //### refer to AMD reference code (LGreaterEqual(OSTB, 0x40))
                        {
                            Return(0x0F)
                        }
                        Store(Zero, HPEN)
                        Return(One)
                    }
                    Return(One)
                }
                Method(_CRS, 0, NotSerialized)
                {
                    Name(BUF0, ResourceTemplate()
                    {
                        IRQNoFlags() {0}
                        IRQNoFlags() {8}
                        Memory32Fixed(ReadOnly, ASL_HPET_BASE_ADDRESS, 0x00000400) // 1kb reserved space
                    })
                    //###CreateDWordField(BUF0, 0x0A, HPEB)
                    //###Store(0xFED00000, Local0)
                    //###And(Local0, 0xFFFFFC00, HPEB)
                    Return(BUF0)
                }
            }

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
