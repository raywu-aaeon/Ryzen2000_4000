//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <UART5.asl>
//
// Description: Define ACPI device for UART5.
//
//<AMI_FHDR_END>
//**********************************************************************
// Category # :0x13
//======================================================================
//Following commented line will be included in PciTree.asl 
//Device(UAR5) {
//    Name(_UID, 5)            //Generic ID for COME
//    Name(_HID, EISAID("PNP0501"))                 //PnP Device ID 16550 Type
//======================================================================
    Name(_DDN, "COM5") //RayWu, ADD 2014/12/10

    Method(_STA, 0) {Return(^^SIO2.DSTA(0x13))}     //Get UART status
    Method(_DIS, 0) {^^SIO2.DCNT(0x13, 0)}          //Disable UART
    Method(_CRS, 0) {Return(^^SIO2.DCR3(0x13, 0))}  //Get UART current resources
    Method(_SRS, 1) {^^SIO2.DSR3(Arg0, 0x13)}       //Set UART resources
//----------------------------------------------------------------------
// UART4 Possible Resources
//----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//----------------------------------------------------------------------
//RayWu, ADD 2014/12/05 >>
    Name(_PRS, ResourceTemplate() {
        StartDependentFn(0, 0) {
            IO(Decode16, 0x2D0, 0x2D0, 1, 8)
            IRQ(Level,ActiveLow,Shared) {11}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x2C0, 0x2C0, 1, 8)
            IRQ(Level,ActiveLow,Shared) {11}
        }
        EndDependentFn()
    })
//RayWu, ADD 2014/12/05 <<
//RayWu, REMOVE 2014/12/05 >>
//    Name(_PRS, ResourceTemplate() {
//        StartDependentFn(0, 0) {
//            IO(Decode16, 0x2F0, 0x2F0, 1, 8)
//            IRQ(Level,ActiveLow,Shared) {7}
//            DMA(Compatibility, NotBusMaster, Transfer8) {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x3E8, 0x3E8, 1, 8)
//            IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
//            DMA(Compatibility, NotBusMaster, Transfer8) {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x2E8, 0x2E8, 1, 8)
//            IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
//            DMA(Compatibility, NotBusMaster, Transfer8) {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x2F0, 0x2F0, 1, 8)
//            IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
//            DMA(Compatibility, NotBusMaster, Transfer8) {}
//        }
//        StartDependentFnNoPri() {
//            IO(Decode16, 0x2E0, 0x2E0, 1, 8)
//            IRQ(Level,ActiveLow,Shared) {3,4,5,6,7,10,11,12}
//            DMA(Compatibility, NotBusMaster, Transfer8) {}
//        }
//        EndDependentFn()
//    })
//RayWu, REMOVE 2014/12/05 <<
//======================================================================
//Following commented line will be included in PciTree.asl 
// }// End Of UAR5
//======================================================================
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
