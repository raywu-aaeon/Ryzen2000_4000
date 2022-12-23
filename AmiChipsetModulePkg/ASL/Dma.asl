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

/** @file Dma.asl
  This file is for SB/LPC DMA controller.
   
  This file contains a declaration of ACPI device for South Bridge or
  LPC DMA Controller. It should be included in the device of SB/LPC.
  
  Notes: GENERALLY NO PORTING REQUIRED.
  
*/

Device(DMAD) {
    Name(_HID,EISAID("PNP0200"))
    Name(_CRS, ResourceTemplate()
    {
        DMA(Compatibility, BusMaster, Transfer8) {4}
        IO(Decode16, 0x0, 0x0, 0, 0x10)
        IO(Decode16, 0x81, 0x81, 0, 0x3)
        IO(Decode16, 0x87, 0x87, 0, 0x1)
        IO(Decode16, 0x89, 0x89, 0, 0x3)
        IO(Decode16, 0x8f, 0x8f, 0, 0x1)
        IO(Decode16, 0xc0, 0xc0, 0, 0x20)
    })
}   // End of DMA

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