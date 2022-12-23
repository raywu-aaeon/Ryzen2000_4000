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

/** @file Pic.asl
  This file is for SB/LPC PIC(8259) controller.
   
  This file contains a declaration of ACPI device for South Bridge or
  LPC PIC(8259) Controller. It should be included in the device of
  SB/LPC.
  
  Notes: GENERALLY NO PORTING REQUIRED.
  
*/

Device(PIC) {
    Name(_HID,EISAID("PNP0000"))    // Hardware Device ID
    Name(_CRS, ResourceTemplate()
    {
        IO(Decode16, 0x20, 0x20, 0, 0x2)
        IO(Decode16, 0xA0, 0xA0, 0, 0x2)
//      IRQ(Edge, ActiveHigh, Exclusive ){2}
        IRQNoFlags(){2}
    })
}   // End of PIC

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
