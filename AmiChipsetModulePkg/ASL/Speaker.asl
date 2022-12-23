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

/** @file Speaker.asl
  This file is for SB/LPC speaker.
   
  This file contains a declaration of ACPI device for South Bridge or
  LPC speaker device. It should be included in the device of
  SB/LPC.
  
  Notes: GENERALLY NO PORTING REQUIRED.
  
*/

Device(SPKR) {
    Name(_HID,EISAID("PNP0800"))
    Name(_CRS, ResourceTemplate()
    {
        IO(Decode16, 0x61, 0x61, 0, 0x1)
    })
}   // End of Spkr

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