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

/** @file Timer.asl
  This file is for SB/LPC Timer(8254) controller.
   
  This file contains a declaration of ACPI device for South Bridge or
  LPC Timer(8254) Controller. It should be included in the device of
  SB/LPC.
  
  Notes: GENERALLY NO PORTING REQUIRED.
  
*/

Device(TMR) {
    Name(_HID,EISAID("PNP0100"))
    Name(_CRS, ResourceTemplate()
    {
        IO(Decode16, 0x40, 0x40, 0, 0x4)
        IRQNoFlags(){0}
    })
}   // End of TMR

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