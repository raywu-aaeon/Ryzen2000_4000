//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <CIR.asl>
//
// Description: Define ACPI device for CIR.
//
//<AMI_FHDR_END>
//*************************************************************************
// CIR //
// Category # :0x10
//====================================================================================
//Following commented line will be included in PciTree.asl 
//Device(CIR) {
//    Name(_HID, EISAID("PNP0510"))        //PnP Device ID CIR
//    Name(_UID, 1)                //UID for CIR 
//====================================================================================
    Method(_STA, 0) {Return(^^SIO1.DSTA(0x10))}    //Get CIR status
    Method(_DIS, 0) {^^SIO1.DCNT(0x10, 0)}     //Disable CIR
    Method(_CRS, 0) {Return(^^SIO1.DCRS(0x10, 0))}    //Get CIR current resources
    Method(_SRS, 1) {^^SIO1.DSRS(Arg0, 0x10) }    //Set CIR recources
//    Method(_PRS, 0) {Return(^^SIO1.CMPR)}        //Return possible resources
//-----------------------------------------------------------------------
// CIR Possible Resources
//-----------------------------------------------------------------------
//NOTE: _PRS MUST be the NAME not a METHOD object 
//to have GENERICSIO.C working right! 
//-----------------------------------------------------------------------
    Name(_PRS, ResourceTemplate() {
        StartDependentFn(0, 0) {
            IO(Decode16, 0x3E0, 0x3E0, 1, 8)
            IRQNoFlags() {10}
        }
        StartDependentFnNoPri() {
            IO(Decode16, 0x3E0, 0x3E0, 1, 8)
            IRQNoFlags() {3,4,5,6,7,9,10,11,12}
        }
        EndDependentFn()
    })
//====================================================================================
//Following commented line will be included in PciTree.asl 
//} // End Of CIR
//====================================================================================
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
