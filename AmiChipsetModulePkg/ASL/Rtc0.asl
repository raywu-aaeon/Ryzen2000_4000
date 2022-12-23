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

/** @file Rtc0.asl
  This file is for SB/LPC RTC controller.
   
  This file contains a declaration of ACPI device for South Bridge or
  LPC real time clock Controller. It should be included in the device of
  SB/LPC.
  
  Notes: GENERALLY NO PORTING REQUIRED.
  
*/

Device(RTC0) {
    Name(_HID, EISAID("PNP0B00"))
    Name(BUF0, ResourceTemplate()
    {
        IO(Decode16, 0x0070, 0x0070, 0x00, 0x02)
    })
    Name(BUF1, ResourceTemplate()
    {
        IO(Decode16, 0x0070, 0x0070, 0x00, 0x02)
        IRQNoFlags() {8}
    })
    Method(_CRS, 0, Serialized)
    {
        If(LEqual(HPEN, One))
        {
            Return(BUF0)
        }
            Return(BUF1)
    }
}   // End RTC

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