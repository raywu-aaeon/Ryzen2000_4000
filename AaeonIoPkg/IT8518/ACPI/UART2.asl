//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date: $
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <UART2.ASL>
//
// Description: Define ACPI method or namespce For Super IO
//
//<AMI_FHDR_END>
//*************************************************************************
// UART2 //
// Category # :0x01
//Device(UAR2) {
//    Name(_HID, EISAID("PNP0501"))    //PnP Device ID 16550 Type
//	Name(_UID, 2)	//Generic ID for COMB

	Name(_DDN, "COM4")
	Method(_STA, 0) {Return(^^EC01.DSTA(0x09))}	//Get UART status
	Method(_DIS, 0) {^^EC01.DCNT(0x09, 0)}			//Disable UART
	Method(_CRS, 0) {Return(^^EC01.DCRS(0x09, 0))}	//Get UART current resources
	Method(_SRS, 1) {^^EC01.DSRS(Arg0, 0x09)}		//Set UART resources

		Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x2F8, 0x2F8, 1, 8)
			IRQNoFlags() {3}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2D8, 0x2D8, 1, 8)
			IRQNoFlags() {10}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		EndDependentFn()
		
/*		//Share IRQ
		Name(_PRS, ResourceTemplate() {
		StartDependentFn(0, 0) {
			IO(Decode16, 0x2C8, 0x2C8, 1, 8)
			IRQ(Level,ActiveLow,Shared){6}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		StartDependentFnNoPri() {
			IO(Decode16, 0x2D8, 0x2D8, 1, 8)
			IRQ(Level,ActiveLow,Shared) {6}
			DMA(Compatibility, NotBusMaster, Transfer8) {}
		}
		EndDependentFn()
*/		
				
	})
//} // End Of UAR2
//-----------------------------------------------------------------------

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
