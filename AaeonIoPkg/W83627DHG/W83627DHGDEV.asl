// THIS FILE IS INCLUDED to South Bridge device scope
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
//*************************************************************************
// Revision History
// ----------------
// $Log: $
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <W83627DHGDEV.asl>
//
// Description: Define ACPI method or namespce For Super IO
//
//<AMI_FHDR_END>
//*************************************************************************
//Scope(\_SB.PCI0.SBRG) {
//-----------------------------------------------------------------------
// SET OF COMMON DATA/CONTROL METHODS USED FOR ALL LDN BASED SIO DEVICES
//-----------------------------------------------------------------------
// LIST of objects defined in this file:
// SIO specific: SIOR - Device node (_HID=0c02, UID=SPIO), SIO index/DAta IO access & SIO GPIO address space if available
// SIO specific: DCAT - Table correspondence the LDNs to Device order in Routing Table.
// SIO specific: ENFG & EXFG - Control methods to Enter and Exit configuration mode. ENFG & EXFG correspondingly
// SIO specific: LPTM - current parralel port mode
// SIO specific: UHID - PnP ID for given Serial port
// SIO specific: SIOS - SIO Chipset specific code called from _PTS
// SIO specific: SIOW - SIO Chipset specific code called from _WAK
// SIO specific: SIOH - SIO event handler, to be called from correspondent _Lxx method
// SIO specific: PowerResources & _PR0 object to control Power management for FDC, LPT, UART1,2.
//
// Generic :OpRegion & common Fields to access SIO configuration space
// Generic :CGLD - Convert Device category to LDN
// Generic :DSTA - Get device status according to ACTR register in LD IO space
// Generic :DCNT - Enable/Disable Decoding of Device resources, Route/Release resources to LPC bus
// Generic :DCRS - Returns Byte stream of device's Current resources
// Generic :DSRS - Configures new Resources to be decoded by a Device
// Device node:Motherboard resources
// SIO index/DAta IO access & SIO GPIO address space if available
//Device(SIO1) {
//    Name(_HID, EISAID("PNP0C02"))     // System board resources device node ID
//    Method(_UID, 0){                  // Unique ID. Use SIO I/O Config. port address.
//        Return(SP1O)
//    }
    Name(CRS, ResourceTemplate(){
        IO(Decode16, 0, 0, 0, 0, IOI)   // Index/Data Io address
        IO(Decode16, 0, 0, 0, 0, IO1)   // HWM IO space
        IO(Decode16, 0, 0, 0, 0, IO2)   // SPI IO space
    }) // end CRS

    Method (_CRS, 0){
        // Super I/O Configuration Port
        If(LAnd(LLess(SP1O, 0x3F0), LGreater(SP1O, 0x0F0))){
            // 0x0 to 0xF0 already reserved
            // 0x3F0 - 0x3F1 are reserved in FDC
            CreateWordField(CRS, ^IOI._MIN, GPI0)
            CreateWordField(CRS, ^IOI._MAX, GPI1)
            CreateByteField(CRS, ^IOI._LEN, GPIL)
            Store(SP1O, GPI0)    //Index/Data Base address
            Store(SP1O, GPI1)
            Store(0x02, GPIL)    //IO range
        }

        // Reserve SIO HWM IO space
        If(IO1B){
            CreateWordField(CRS, ^IO1._MIN, GP10)
            CreateWordField(CRS, ^IO1._MAX, GP11)
            CreateByteField(CRS, ^IO1._LEN, GPL1)
            Store(IO1B, GP10)    //base address
            Store(IO1B, GP11)
            Store(IO1L, GPL1)    //IO range
        }
        
        // Reserve SIO HWM IO space
        If(IO2B){
            CreateWordField(CRS, ^IO2._MIN, GP20)
            CreateWordField(CRS, ^IO2._MAX, GP21)
            CreateByteField(CRS, ^IO2._LEN, GPL2)
            Store(IO2B, GP20)    //base address
            Store(IO2B, GP21)
            Store(IO2L, GPL2)    //IO range
        }

        Return(CRS)
    }    //End _CRS


//------------------------------------------------------------------------
// Table correspondence the LDNs to Device order in Routing Table
// Device type selection is achieved by picking the value from DCAT Package by Offset = LDN
//------------------------------------------------------------------------
// Elements in the package contain LDN numbers for each category of devices.
// Default value 0xFF -> no device present.
// Make sure number of elements not less or equal to largest LDN
    Name (DCAT, Package(0x15){
    // AMI_TODO: fill the table with the present LDN
    // LDN number, 0xFF if device not present
    // We keep category 0x00~0x0F as SIO_DEV_STATUS layout in AmiGenericSio.h to Update IOST 
        0x02,    // 0x00 - Serial A (SP1)
        0x03,    //   01 - Serial B (SP2)
        0x01,    //   02 - LPT
        0x00,    //   03 - FDD
        0xFF,    //   04 - SB16 Audio
        0xFF,    //   05 - MIDI
        0xFF,    //   06 - MSS Audio
        0xFF,    //   07 - AdLib sound (FM synth)
        0xFF,    //   08 - Game port #1
        0xFF,    //   09 - Game port #2
        0x05,    //   0A - KBC 60 & 64
        0xFF,    //   0B - EC 62 & 66
        0xFF,    //   0C - Reserved 
        0xFF,    //   0D - Reserved
        0x05,    //   0E - PS/2 Mouse
        0xFF,    //   0F - Reserved
//----add your other device,if no,please cut and modify Package number----------//
        0xFF,    //   10 - CIR
        0xFF,    //   11 - Serial C (SP3) 
        0xFF,    //   12 - Serial D (SP4)
        0xFF,    //   13 - Serial E (SP5)
        0xFF,    //   14 - Serial F (SP6)
    })


//------------------------------------------------------------------------
// Enter Config Mode, Select LDN
// Arg0 : Logical Device number
//------------------------------------------------------------------------
    Mutex(MUT0, 0)    //Mutex object to sincronize the access to Logical devices

    Method(ENFG, 1) {
        Acquire(MUT0, 0xFFF)
//AMI_TODO: enter config mode and Select LDN.
        Store(ENTK, INDX)
        Store(ENTK, INDX)
        Store(Arg0, LDN)    //Select LDN
    }


//------------------------------------------------------------------------
// Exit Config Mode
//------------------------------------------------------------------------
    Method(EXFG, 0) {
//AMI_TODO: exit config mode
        Store(EXTK, INDX)
        Release(MUT0)
    }


//------------------------------------------------------------------------
// Return current LPT mode : 0-plain LPT, non Zero-ECP mode
// Arg0 : Device LDN
//------------------------------------------------------------------------
    Method(LPTM, 1){
        ENFG(CGLD(Arg0))        //Enter Config Mode, Select LDN
//AMI_TODO: if it's ECP mode .
        And(OPT0, 0x02, Local0) //ECP Mode?
        EXFG()                  //Exit Config Mode
        Return(Local0)
    }

//------------------------------------------------------------------------
// !!! BELOW ARE GENERIC SIO CONTROL METHODS. DO NOT REQUIRE MODIFICATIONS
//----------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//----------------------------------------------------------------------
//<AMI_THDR_START>
//------------------------------------------------------------------------
// Name: IOID
//
// Type: OperationRegion
//
// Description:    Operation Region to point to SuperIO configuration space
//
// Notes: OpeRegion address is defined by 'SPIO' global name. 'SPIO' is a field isnside AML_Exchange data area updated in BIOS POST.
// Referrals: BIOS, AMLDATA
//-------------------------------------------------------------------------
//<AMI_THDR_END>
    OperationRegion(IOID,    // Name of Operation Region for SuperIO device
        SystemIO,       // Type of address space
        SP1O,           // Offset to start of region
        2)              // Size of region in bytes
                        // End of Operation Region
    Field(IOID, ByteAcc, NoLock,Preserve){
        INDX, 8,    // Field named INDX is 8 bit wide
        DATA, 8     // Field DATA is 8 bit wide
    }


//----------------------------------------------------------------------
//  Set of Field names to be used to access SIO configuration space.
//----------------------------------------------------------------------
    IndexField(INDX, DATA, ByteAcc, NoLock, Preserve){
        Offset(0x07),
        LDN, 8,         //Logical Device Number
        Offset(0x22),
        SCF2, 8,        //Set SCF2 
        SCF3, 8,        //Set SCF3 
        SCF4, 8,        //Set SCF4 
        SCF5, 8,        //Set SCF5 
        SCF6, 8,        //Set SCF6 
        SCF7, 8,        //Set SCF7 
        SCF8, 8,        //Set SCF8 
        SCF9, 8,        //Set SCF9
        SCFA, 8,        //Set SCFA
        Offset(0x2c),
        SCFC, 8,        //Set SCFC
        Offset(0x30),
        ACTR, 8,        //Activate register
        Offset(0x60),
        IOAH, 8,        //Base I/O High addr
        IOAL, 8,        //Base I/O Low addr
        IOH2, 8,        //Base2 I/O High addr
        IOL2, 8,        //Base2 I/O Low addr
        Offset(0x70),
        INTR, 4,        //IRQ
        INTT, 4,        //IRQ type
        Offset(0x74),
        DMCH, 8,        //DMA channel
        Offset(0xE0),
        RGE0, 8,        //Option Register E0
        RGE1, 8,        //Option Register E1
        RGE2, 8,        //Option Register E2
        RGE3, 8,        //Option Register E3
        RGE4, 8,        //Option Register E4
        RGE5, 8,        //Option Register E5
        RGE6, 8,        //Option Register E6
        RGE7, 8,        //Option Register E7
        RGE8, 8,        //Option Register E8
        RGE9, 8,        //Option Register E9
        Offset(0xF0),
        OPT0, 8,        //Option register 0xF0
        OPT1, 8,        //Option register 0xF1
        OPT2, 8,        //Option register 0xF2
        OPT3, 8,        //Option register 0xF3
        OPT4, 8,        //Option register 0xF4
        OPT5, 8,        //Option register 0xF5
        OPT6, 8,        //Option register 0xF6
        OPT7, 8,        //Option register 0xF7
        OPT8, 8,        //Option register 0xF8
        OPT9, 8,        //Option register 0xF9
        Offset(0xFE),
        OPTE, 8,        //Option register 0xFE
    }        //End of indexed field

    Method(ENBK, 1) {
        //Acquire(MUT0, 0xFFF)
        //AMI_TODO: enter config mode and Select LDN.
        Store(HW4E, local0)
        Or(And(local0, 0xF8, local1), Arg0, local2)
        Store(local2, HW4E)
    }

    //---------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //---------------------------------------------------------------------
    OperationRegion(IOHW,   // Name of Operation Region for SuperIO device
        SystemIO,           // Type of address space
        IO1B, // Offset to start of region
        8)                  // Size of region in bytes
                            // End of Operation Region
    Field(IOHW, ByteAcc, NoLock,Preserve){
        Offset(5),
        HWMI, 8,            // Hardware Monitor Base Address + 5
        HWMD, 8             // Hardware Monitor Base Address + 6
    }

    //---------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //---------------------------------------------------------------------
    IndexField(HWMI, HWMD, ByteAcc, NoLock, Preserve){
        HW00, 8,
        HW01, 8,
        HW02, 8,
        HW03, 8,
        HW04, 8,
        HW05, 8,
        HW06, 8,
        HW07, 8,
        Offset(0x09),
        HW09, 8,
        HW0A, 8,
        Offset(0x11),
        HW11, 8,
        HW12, 8,
        HW13, 8,
        Offset(0x16),
        HW16, 8,
        Offset(0x20),
        HW20, 8,
        HW21, 8,
        HW22, 8,
        HW23, 8,
        HW24, 8,
        HW25, 8,
        HW26, 8,
        HW27, 8,
        HW28, 8,
        HW29, 8,
        HW2A, 8,
        Offset(0x3F),
        HW3F, 8,
        Offset(0x47),
        HW47, 8,
        HW48, 8,
        HW49, 8,
        HW4A, 8,
        HW4B, 8,
        HW4C, 8,
        Offset(0x4E),
        HW4E, 8,         //bit0~2: Bank Number
        Offset(0x50),
        HW50, 8,
        HW51, 8,
        HW52, 8,
        HW53, 8,
        Offset(0x59),
        HW59, 8,
        Offset(0x5D),
        HW5D, 8,
        Offset(0x61),
        HW61, 8,
        HW62, 8,
        HW63, 8,
        HW64, 8,
        Offset(0x67),
        HW67, 8,
        HW68, 8,
        HW69, 8,
        HW6A, 8,
     }

// Make sure referred IO devices included in SIO ASL file list ($SIO_ASLS)
// PS2 port swap feature is not covered in this code

// Keyboard 2nd Level wake up control method
//    Method(PS2K._PSW, 1){
//        Store(Arg0, KBFG)
//    }
// Mouse 2nd Level wake up control method
//    Method(PS2M._PSW, 1){
//        Store(Arg0, MSFG)
//    }
// UART1 RI 2nd Level wake up control method
//    Method(UAR1._PSW, 1){
//        Store(Arg0, UR1F)
//    }
// UART2 RI 2nd Level wake up control method
//    Method(UAR2._PSW, 1){
//        Store(Arg0, UR2F)
//    }


//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    CGLD
// Description:    Convert Device Category to Device's LDN
// Input: Arg0 : Device category #
// Output: LDN
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(CGLD, 1) {
        Return(DeRefOf(Index(DCAT, Arg0)))    // Return LDN
    }


//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSTA
// Description:    GET SIO DEVICE STATUS according to ACTR/IOST return values
// Input: Arg0 : Device category #
// Output: Device Status
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSTA, 1) {

        // IO Device presence status is determined during first _STA invocation. 
        // If "Activate" bit is set during first _STA invocation, IO device 
        // present status is stored into IOST global variable.
        // IOST global variable contains the bit mask of all enabled Io devices.
        ENFG(CGLD(Arg0))        //Enter Config Mode, Select LDN
        Store(ACTR, Local0)
        EXFG()        // Exit Config Mode

        // LDN's not decoded, Device not present.
        If(LEqual(Local0, 0xFF)) {Return(0x0)}    

        //Assume register(ACTR) bit0 is "Active" bit.
        //AMI_TODO: If register(ACTR) non-bit0 is "Active" bit, change below code.
        And(Local0, 1, Local0)  //Leave only "Activate" bit

        // IOST only have 16 bits,IOST is for category 0x00~0x0F device
        If(LLess(Arg0,0x10)) {Or(IOST, ShiftLeft(Local0, Arg0), IOST)}

        // Update IO device status in IOST according to the category#
        // Note. Once device is detected its status bit cannot be removed
        If(Local0){ 
            Return(0x0F)            // Device present & Active
        }    
        Else{
            If(LLess(Arg0,0x10)){//by IOST check
                // Check if IO device detected in Local0(IOST) bit mask
                If(And(ShiftLeft(1, Arg0), IOST)){ Return(0x0D)}  // Device Detected & Not Active 
                // IO bit not set in Local0: device is disabled during first 
                // _STA(GSTA) invocationor disabled in BIOS Setup.
                Else{ Return(0x00)}  // Device not present
            }
            Else{//by Base1 & Base2 check
                Or(ShiftLeft(IOAH, 8),IOAL,Local0)
                If(Local0) { Return(0x0D)}  // Device Detected & Not Active
//                Or(ShiftLeft(IOH2, 8),IOL2,Local0)    
//                If(Local0) { Return(0x0D)}  // Device Detected & Not Active
                Return(0x00) // Device not present
            }
        }
	} // End Of DSTA


//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCNT
// Description:    Enable/Disable Decoding of Device resources, Route/Release
// I/O & DMA Resources From, To EIO/LPC Bus
// Input: Arg0 : Device catagory #
//    Arg1 : 0/1 Disable/Enable resource decoding
// Output: Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCNT, 2) {
        ENFG(CGLD(Arg0))    //Enter Config Mode, Select LDN

        // Route/Release DMA channel from/to being ISA/PCI mode
        // Note. DMA channel 0 is currently not decoded, although it can be used on some of SIO chipsets.
        If(LAnd(LLess(DMCH,4), LNotEqual(And(DMCH, 3, Local1),0)))
        {
            rDMA(Arg0, Arg1, Increment(Local1))
        }

        Store(Arg1, ACTR)        // Update Activate Register

        // Get IO Base address
        ShiftLeft(IOAH, 8, local1)
        Or(IOAL, Local1, Local1)

    // Route/Release I/O resources from/to EIO/LPC Bus
        // Arg0      Device Category
        // Arg1      0/1 Disable/Enable resource decoding
        // Arg2      Port to Route/Release
        // Arg3      Port SIZE to Route 
        RRIO(Arg0, Arg1, Local1, 0x08)

        EXFG()        // Exit Config Mode
    } // End DCNT


//<AMI_THDR_START>
//------------------------------------------------------------------------
// Name: CRS1,CRS2
//
// Type: ResourceTemplate
//
// Description:    Current Resources Buffer for Generic SIO devices
//
// Notes: Note. DMA channel 0 is currently decoded as reserved,
// although, it can be used on some of SIO chipsets.
// Add DMA0 to _PRS if it is used
// Generic Resourse template for FDC, COMx, LPT and ECP Current Resource Settings
// (to be initialized and returned by _CRS)
//-------------------------------------------------------------------------
//<AMI_THDR_END>
    Name(CRS1, ResourceTemplate(){
        IO(Decode16, 0, 0, 1, 0, IO01)
        IRQNoFlags(IRQ1) {}
        DMA(Compatibility, NotBusMaster, Transfer8, DMA1) {}
    })
    CreateWordField(CRS1, IRQ1._INT, IRQM)    //IRQ mask 0x1
    CreateByteField(CRS1, DMA1._DMA, DMAM)    //DMA 0x4
    CreateWordField(CRS1, IO01._MIN, IO11)    //Range 1 Min Base Word 0x8
    CreateWordField(CRS1, IO01._MAX, IO12)    //Range 1 Max Base Word 0xa
    CreateByteField(CRS1, IO01._LEN, LEN1)    //Length 1 0xd

// Extended CRS buffer with 2 IO ranges
    Name(CRS2, ResourceTemplate(){
        IO(Decode16, 0, 0, 1, 0, IO02)
        IO(Decode16, 0, 0, 1, 0, IO03)
        IRQNoFlags(IRQ2) {}
        DMA(Compatibility, NotBusMaster, Transfer8, DMA2) {2}
    })
    CreateWordField(CRS2, IRQ2._INT, IRQE)    //IRQ mask 0x1
    CreateByteField(CRS2, DMA2._DMA, DMAE)    //DMA 0x4
    CreateWordField(CRS2, IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
    CreateWordField(CRS2, IO02._MAX, IO22)    //Range 1 Max Base Word 0xa
    CreateByteField(CRS2, IO02._LEN, LEN2)    //Length 1 0xd
    CreateWordField(CRS2, IO03._MIN, IO31)    //Range 2 Min Base Word 0x10
    CreateWordField(CRS2, IO03._MAX, IO32)    //Range 2 Max Base Word 0x12
    CreateByteField(CRS2, IO03._LEN, LEN3)    //Length 2 0x15
    
//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCRS
// Description:    Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
// Returns Byte stream of Current resources. May contain Resources such:
//    1 IRQ resource
//    1 DMA resource
//    1 IO Port
// Input: Arg0 : Device catagory #
// Output: _CRS Resource Buffer 
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCRS, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN

        // Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO11)    //Get IO Base MSB
        Or(IOAL, IO11, IO11)        //Get IO Base LSB
        Store(IO11, IO12)           //Set Max Base Word

        Store(0x08, LEN1)           //set length

        // Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQM)
        } 
        Else{
            Store(0, IRQM)          // No IRQ used
        }

        // Write Current Settings into DMA descriptor
        // Note. DMA channel 0 is currently decoded as reserved,
        // although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAM)          // No DMA
        } 
        Else{
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAM)
        }
        EXFG()                      //Exit Config Mode
        Return(CRS1)                //Return Current Resources
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DCR2
// Description:    Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
// Returns Byte stream of Current resources. May contain Resources such:
//    1 IRQ resource
//    1 DMA resource
//    2 IO Port
// Input: Arg0 : Device catagory #
// Output: _CRS Resource Buffer 
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DCR2, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN

        // Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO21)    //Get IO Base MSB
        Or(IOAL, IO21, IO21)        //Get IO Base LSB
        Store(IO21, IO22)           //Set Max Base Word
        Store(0x08, LEN2)

        // Write Current Settings into Buffer for 2nd IO Descriptor
        ShiftLeft(IOH2, 8, IO31)    //Get IO Base MSB
        Or(IOL2, IO31, IO31)        //Get IO Base LSB
        Store(IO31, IO32)           //Set Max Base Word
        Store(0x08, LEN3)

        // Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQE)
        } 
        Else{
            Store(0, IRQE)          // No IRQ used
        }

        // Write Current Settings into DMA descriptor
        // Note. DMA channel 0 is currently decoded as reserved,
        // although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAE)          // No DMA
        } Else {
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAE)
        }

        EXFG()                      //Exit Config Mode
        Return(CRS2)                //Return Current Resources
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSRS
// Description:    Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
// Control method can be used for configuring devices with following resource order:
//    1 IRQ resource
//    1 DMA resource
//    1 IO Port
// Input: Arg0 : PnP Resource String to set, Arg1: Category
// Arg1 : Device catagory #
// Output: Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSRS, 2) {
        If(And(LEqual(Arg1, 0x02),LPTM(Arg1) ) ) {        //LPT logical device? Extended LPT mode ?
                DSR2(Arg0, Arg1)
        } Else {
            //Set resource for other devices from CRS1, or just for Parallel Port LPT Mode
            CreateWordField(Arg0, ^IRQ1._INT, IRQM)    //IRQ mask 0x1
            CreateByteField(Arg0, ^DMA1._DMA, DMAM)    //DMA 0x4
            CreateWordField(Arg0, ^IO01._MIN, IO11)    //Range 1 Min Base Word 0x8
    
            ENFG(CGLD(Arg1))            //Enter Config Mode, Select LDN
    
            // Set Base IO Address
            And(IO11, 0xFF, IOAL)       //Set IO Base LSB
            ShiftRight(IO11, 0x8, IOAH) //Set IO Base MSB
    
            // Set IRQ
            If(IRQM){
                FindSetRightBit(IRQM, Local0)
                Subtract(Local0, 1, INTR)
            }Else{
                Store(0, INTR)          //No IRQ used
            }
    
            // Set DMA
            If(DMAM){
                FindSetRightBit(DMAM, Local0)
                Subtract(Local0, 1, DMCH)
            }Else{
                Store(4, DMCH)          //No DMA
            }
    
            EXFG()                      //Exit Config Mode
    
            // Enable ACTR
            DCNT(Arg1, 1)               //Enable Device (Routing)
    
            Store(Arg1, Local2)
            If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
        }//Else end
    }

//<AMI_PHDR_START>
//------------------------------------------------------------------------
// Procedure:    DSR2
// Description:    Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
// Control method can be used for configuring devices with following resource order:
//    1 IRQ resource
//    1 DMA resource
//    2 IO Port
// Input: Arg0 : PnP Resource String to set
// Arg1 : Device catagory #
// Output: Nothing
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
    Method(DSR2, 2) {
        CreateWordField(Arg0, ^IRQ2._INT, IRQE)    //IRQ mask 0x1
        CreateByteField(Arg0, ^DMA2._DMA, DMAE)    //DMA 0x4
        CreateWordField(Arg0, ^IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IO03._MIN, IO31)    //Range 1 Min Base Word 0x8

        ENFG(CGLD(Arg1))                //Enter Config Mode, Select LDN

        // Set Base IO Address
        And(IO21, 0xFF, IOAL)           //Set IO1 Base LSB
        ShiftRight(IO21, 0x8, IOAH)     //Set IO1 Base MSB

        And(IO31, 0xFF, IOL2)           //Set IO2 Base LSB
        ShiftRight(IO31, 0x8, IOH2)     //Set IO2 Base MSB

        // Set IRQ
        If(IRQE){
            FindSetRightBit(IRQE, Local0)
            Subtract(Local0, 1, INTR)
        }Else{
            Store(0, INTR)              //No IRQ used
        }

        // Set DMA
        If(DMAE){
            FindSetRightBit(DMAE, Local0)
            Subtract(Local0, 1, DMCH)
        }Else{
            Store(4, DMCH)              //No DMA
        }

        EXFG()                          //Exit Config Mode

        // Enable ACTR
        DCNT(Arg1, 1)                   //Enable Device (Routing)

        Store(Arg1, Local2)
        If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
    }

#ifndef ASL_BFPI_SUCCESS
    #define ASL_BFPI_SUCCESS 0
#endif
#ifndef ASL_BFPI_NOT_SUPPORTED
    #define ASL_BFPI_NOT_SUPPORTED 0xFFFFFFFF
#endif
#ifndef ASL_BFPI_INVALID_PARAMETER
    #define ASL_BFPI_INVALID_PARAMETER 0xFFFFFFFE
#endif
#ifndef ASL_W83627DHG_SYSTIN_STRING
    #define ASL_W83627DHG_SYSTIN_STRING "W83627DHG-SYSTIN"
#endif
#ifndef ASL_W83627DHG_CPUTIN_STRING
    #define ASL_W83627DHG_CPUTIN_STRING "W83627DHG-CPUTIN"
#endif
#ifndef ASL_W83627DHG_AUXTIN_STRING
    #define ASL_W83627DHG_AUXTIN_STRING "W83627DHG-AUXTIN"
#endif
#ifndef ASL_W83627DHG_SYSFANIN_STRING
    #define ASL_W83627DHG_SYSFANIN_STRING "W83627DHG-SYSFANIN"
#endif
#ifndef ASL_W83627DHG_CPUFANIN0_STRING
    #define ASL_W83627DHG_CPUFANIN0_STRING "W83627DHG-CPUFANIN0"
#endif
#ifndef ASL_W83627DHG_AUXFANIN0_STRING
    #define ASL_W83627DHG_AUXFANIN0_STRING "W83627DHG-AUXFANIN0"
#endif
#ifndef ASL_W83627DHG_CPUFANIN1_STRING
    #define ASL_W83627DHG_CPUFANIN1_STRING "W83627DHG-CPUFANIN1"
#endif
#ifndef ASL_W83627DHG_AUXFANIN0_STRING
    #define ASL_W83627DHG_AUXFANIN0_STRING "W83627DHG-AUXFANIN1"
#endif
#ifndef ASL_W83627DHG_VCORE_STRING
    #define ASL_W83627DHG_VCORE_STRING "W83627DHG-VCORE"
#endif
#ifndef ASL_W83627DHG_VIN0_STRING
    #define ASL_W83627DHG_VIN0_STRING "W83627DHG-VIN0"
#endif
#ifndef ASL_W83627DHG_VIN1_STRING
    #define ASL_W83627DHG_VIN1_STRING "W83627DHG-VIN1"
#endif
#ifndef ASL_W83627DHG_VIN2_STRING
    #define ASL_W83627DHG_VIN2_STRING "W83627DHG-VIN2"
#endif
#ifndef ASL_W83627DHG_VIN3_STRING
    #define ASL_W83627DHG_VIN3_STRING "W83627DHG-VIN3"
#endif
#ifndef ASL_W83627DHG_VCC3_STRING
    #define ASL_W83627DHG_VCC3_STRING "W83627DHG-VCC3"
#endif
#ifndef ASL_W83627DHG_AVCC_STRING
    #define ASL_W83627DHG_AVCC_STRING "W83627DHG-AVCC"
#endif
#ifndef ASL_W83627DHG_VSB3_STRING
    #define ASL_W83627DHG_VSB3_STRING "W83627DHG-VSB3"
#endif
#ifndef ASL_W83627DHG_VBAT_STRING
    #define ASL_W83627DHG_VBAT_STRING "W83627DHG-VBAT"
#endif

//------------------------------------------------------------------------
// Table:    TLDN
// Description:  LDN look up table for GPIO group number
//-------------------------------------------------------------------------
    Name (TLDN, Package(0x9){
        ASL_BFPI_INVALID_PARAMETER,  // GP0x, not supported by W83627
        ASL_BFPI_INVALID_PARAMETER,  // GP1x, not supported by W83627
        9,  // GP2x
        9,  // GP3x
        9,  // GP4x
        9,  // GP5x
        7,  // GP6x
        ASL_BFPI_INVALID_PARAMETER,  // GP7x, not supported by W83627
        ASL_BFPI_INVALID_PARAMETER  // GP8x, not supported by W83627
    })
//------------------------------------------------------------------------
// Procedure:    CGTL
// Description:  Convert Super I/O GPIO group number to LDN
// Input: Arg0 : Super I/O Group number
// Output: LDN
//-------------------------------------------------------------------------
    Method(CGTL, 1) {
        If (LGreater(Arg0, 8))
        { Return (ASL_BFPI_INVALID_PARAMETER) }
        Return(DerefOf(Index(TLDN, Arg0)))    // Return LDN
    }

//---------------------------------------------------------------------------
// Name: D1GL
//
// Description:  DIO SIO1 Get Level
//   Arg0 : GPIO Number to get level
//
// Output:
//   Interger:
//   0 - Low level
//   1 - High level
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (D1GL, 1) {
        Store(And(Arg0, 0xff), local0) // local1: DIO number
        Divide (local0, 10, local2, local1)
        ShiftLeft(0x01, local2, local3) //pin bitmask
        Store (CGTL(local1), local4)
        // local1 : Result : Super I/O Group number
        // local2 : Remainder : Pin number in group 
        // local3 : Pin bit map
        // local4 : GPIO LDN
        If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(local4)        //Enter Config Mode, Select GPIO LDN

        If (LEqual(local1,2))
        {
            ShiftRight(And(RGE4, local3), local2, local5)
        } ElseIf (LEqual(local1,3))
        {
            ShiftRight(And(OPT1, local3), local2, local5)
        } ElseIf (LEqual(local1,4))
        {
            ShiftRight(And(OPT5, local3), local2, local5)
        } ElseIf (LEqual(local1,5))
        {
            ShiftRight(And(RGE1, local3), local2, local5)
        } ElseIf (LEqual(local1,6))
        {
            ShiftRight(And(OPT5, local3), local2, local5)
        }

        EXFG()        // Exit Config Mode

        Return (local5)
    }

//---------------------------------------------------------------------------
// Name: D1SL
//
// Description:  OEM GPIO Set Level
//   Arg0 : GPIO Number to set level
//   Arg1 : Level to set
//     0 - Low level
//     1 - High level
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SL, 2){
         Store(And(Arg0, 0xff), local0) // local1: DIO number
         Divide (local0, 10, local2, local1)
         ShiftLeft(0x01, local2, local3) //pin bitmask
         Store (CGTL(local1), local4)
         // local1 : Result : Super I/O Group number
         // local2 : Remainder : Pin number in group 
         // local3 : Pin bit map
         // local4 : GPIO LDN
         If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
         { Return (ASL_BFPI_INVALID_PARAMETER) }

         ENFG(local4)        //Enter Config Mode, Select GPIO LDN

         If (LEqual(local1,2))
         {
             Or (And(RGE4,Not(local3)), ShiftLeft(Arg1,local2), RGE4)
         } ElseIf (LEqual(local1,3))
         {
             Or (And(OPT1,Not(local3)), ShiftLeft(Arg1,local2), OPT1)
         } ElseIf (LEqual(local1,4))
         {
             Or (And(OPT5,Not(local3)), ShiftLeft(Arg1,local2), OPT5)
         } ElseIf (LEqual(local1,5))
         {
             Or (And(RGE1,Not(local3)), ShiftLeft(Arg1,local2), RGE1)
         } ElseIf (LEqual(local1,6))
         {
             Or (And(OPT5,Not(local3)), ShiftLeft(Arg1,local2), OPT5)
         }

         EXFG()        // Exit Config Mode

         Return (ASL_BFPI_SUCCESS)
    }

//---------------------------------------------------------------------------
// Name: D1GD
//
// Description:  OEM GPIO Get Direction
//   Arg0 : GPIO Number to get Direction
//
// Output:
//   Interger:
//   0 - Output
//   1 - Input
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (D1GD, 1) {
         Store(And(Arg0, 0xff), local0) // local1: DIO number
         Divide (local0, 10, local2, local1)
         ShiftLeft(0x01, local2, local3) //pin bitmask
         Store (CGTL(local1), local4)
         // local1 : Result : Super I/O Group number
         // local2 : Remainder : Pin number in group 
         // local3 : Pin bit map
         // local4 : GPIO LDN
         If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
         { Return (ASL_BFPI_INVALID_PARAMETER) }

         ENFG(local4)        //Enter Config Mode, Select GPIO LDN

         If (LEqual(local1,2))
         {
             ShiftRight(And(RGE3, local3), local2, local5)
         } ElseIf (LEqual(local1,3))
         {
             ShiftRight(And(OPT0, local3), local2, local5)
         } ElseIf (LEqual(local1,4))
         {
             ShiftRight(And(OPT4, local3), local2, local5)
         } ElseIf (LEqual(local1,5))
         {
             ShiftRight(And(RGE0, local3), local2, local5)
         } ElseIf (LEqual(local1,6))
         {
             ShiftRight(And(OPT4, local3), local2, local5)
         }

         EXFG()        // Exit Config Mode

         Return (local5)
    }

//---------------------------------------------------------------------------
// Name: D1SD
//
// Description:  OEM GPIO Set Direction
//   Arg0 : GPIO Number to set Direction
//   Arg1 : Direction to set
//     0 - Output
//     1 - Input
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SD, 2){
        Store(And(Arg0, 0xff), local0) // local1: DIO number
        Divide (local0, 10, local2, local1)
        ShiftLeft(0x01, local2, local3) //pin bitmask
        Store (CGTL(local1), local4)
        // local1 : Result : Super I/O Group number
        // local2 : Remainder : Pin number in group 
        // local3 : Pin bit map
        // local4 : GPIO LDN
        If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(local4)        //Enter Config Mode, Select GPIO LDN

        If (LEqual(local1,2))
        {
            Or (And(RGE3,Not(local3)), ShiftLeft(Arg1,local2), RGE3)
        } ElseIf (LEqual(local1,3))
        {
            Or (And(OPT0,Not(local3)), ShiftLeft(Arg1,local2), OPT0)
        } ElseIf (LEqual(local1,4))
        {
            Or (And(OPT4,Not(local3)), ShiftLeft(Arg1,local2), OPT4)
        } ElseIf (LEqual(local1,5))
        {
            Or (And(RGE1,Not(local3)), ShiftLeft(Arg1,local2), RGE0)
        } ElseIf (LEqual(local1,6))
        {
            Or (And(OPT4,Not(local3)), ShiftLeft(Arg1,local2), OPT4)
        }

        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }
//---------------------------------------------------------------------------
// Name: D1GO
//
// Description:  OEM GPIO Get Driving
//   Arg0 : GPIO Number to get Driving
//
// Output:
//   Interger:
//     0: Open drain
//     1: Push pull / Internal pull-up 20K
//     2: Internal pull-up 10K
//     3: Internal pull-up 5K
//     4: Internal pull-up 1K
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (D1GO, 1) {
        Return (ASL_BFPI_NOT_SUPPORTED)
    }

//---------------------------------------------------------------------------
// Name: D1SO
//
// Description:  OEM GPIO Set Driving
//   Arg0 : GPIO Number to set Driving
//   Arg1 : Driving to set
//     0: Open drain
//     1: Push pull / Internal pull-up 20K
//     2: Internal pull-up 10K
//     3: Internal pull-up 5K
//     4: Internal pull-up 1K
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SO, 2){
        Return (ASL_BFPI_NOT_SUPPORTED)
    }

#if  ASL_W83627DHG_WDT_PRESENT
//---------------------------------------------------------------------------
// Name: W1RC
//
// Description:  SIO WDT report capability - Max timeout
//
// Output:
//   Interger: Max timeout value in ms
//
//---------------------------------------------------------------------------
    Method (W1RC, 0) {
        Return (ASL_SIO_WDT_MAX_TIMEOUT)
    }

//---------------------------------------------------------------------------
// Name: W1GT
//
// Description:  SIO WDT Get timeout
//
// Output:
//   Interger: Remained timeout value in ms
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (W1GT, 0) {
        ENFG(8)        //Enter Config Mode, Select WDT LDN
        Store (OPT6, local0)
        Store (OPT5, local1)
        // local0 : Current time-out counter
        // local1 :
        //   [3] : 0 - Second Mode, 1 - Minute Mode
        //   [4] : 0 - Disable, 1 - Enable 1000x faster
        EXFG()        // Exit Config Mode

        If (LEqual(And(ShiftRight(local1,3),1), 1)) {
           Multiply (local0, 60, local0)  // Multiply with 60 in Minute mode
        }

        If (LEqual(And(ShiftRight(local1,4),1), 0)) {
            Multiply (local0, 1000, local0)  // Multiply with 1000 in normal mode
        }

        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: W1ST
//
// Description:  SIO WDT set watchdog timeout value and start/stop watchdog
//   Arg0 : Timeout value in ms
//            0: stop watchdog
//            other: start watchdog with value as timeout
//
// Output:
//   BFPI_STATUS
//
// Note: BIOS should have already configure WDT output during POST.
//       So we just set mode and counter here.
//
//---------------------------------------------------------------------------
    Method (W1ST, 1){
        // Validate input
        If (LGreater(Arg0, ASL_SIO_WDT_MAX_TIMEOUT)) { 
            Return (ASL_BFPI_INVALID_PARAMETER)
        }

        Store (0, local0)
        Store (0, local1)
        Store (0, local2)
        // local0 : time-out to set to WDT
        // local1 : temporal for remainder from divide operation
        // local2 : WDT mode to set
        // Default Second / Normal mode

        // Calculate counter and mode to set
        // OPT6 : Current time-out counter
        // OPT5 :
        //   [3] : 0 - Disable, 1 - Enable 1000x faster
        //   [4] : 0 - Second Mode, 1 - Minute Mode
        If (LGreater(Arg0, 0))
        {
            Divide (Arg0, 1000, local1, local0)
            // Convert ms to sec
            // local0 : time-out in second
            // local1 : time-out remainder in ms

            If (LGreater(local1,0)) {
                If (LLessEqual(Arg0, 15300))
                {
                    Or (Local2, 0x10, local2)  // BIT4 = 1 : 1000x mode
                    Store (Arg0, local0)
                    // local0 : time-out in ms
                } else {
                    Increment(local0)
                }
            }

            If (LGreater(local0, 255))
            {
                Or (local2, 0x08, local2)  // BIT3 = 1 : Minute mode
                Divide (local0, 60, local1, local0)
                If (LGreater(local1,0)) { 
                    Increment(local0)
                }
            }
        }

        // Set to SIO
        ENFG(8)        //Enter Config Mode, Select WDT LDN
        Store (0, OPT6)  // Stop WDT before changing counting mode
        Or (And(OPT5,0xE7), local2, OPT5)  // Set counting mode
        Store (local0, OPT6)  // Set counter
        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }
#endif  ASL_W83627DHG_WDT_PRESENT

#if  ASL_W83627DHG_HWM_PRESENT
//---------------------------------------------------------------------------
// Name: H1SN
//
// Description:  SIO HWM report sensor number
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   Integer - Total senser number for specified sensor type
//   
//---------------------------------------------------------------------------
    Method (H1SN, 1){
        Store (0, Local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            Store (ASL_W83627DHG_TEMP_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            Store (ASL_W83627DHG_FAN_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            Store (ASL_W83627DHG_VOLT_SENSOR_NUMBER, Local0)
        }
        Return (Local0)
    }

//------------------------------------------------------------------------
// Table:    THTS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
Name(THTS, Package() {
#if ASL_W83627DHG_SYSTIN_SUPPORT
    ASL_W83627DHG_SYSTIN_STRING,
#endif
#if ASL_W83627DHG_CPUTIN_SUPPORT
    ASL_W83627DHG_CPUTIN_STRING,
#endif
#if ASL_W83627DHG_AUXTIN_SUPPORT
    ASL_W83627DHG_AUXTIN_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    THFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
Name(THFS, Package() {
#if ASL_W83627DHG_SYSFANIN_SUPPORT
    ASL_W83627DHG_SYSFANIN_STRING,
#endif
#if ASL_W83627DHG_CPUFANIN0_SUPPORT
    ASL_W83627DHG_CPUFANIN0_STRING,
#endif
#if ASL_W83627DHG_AUXFANIN0_SUPPORT
    ASL_W83627DHG_AUXFANIN0_STRING,
#endif
#if ASL_W83627DHG_CPUFANIN1_SUPPORT
    ASL_W83627DHG_CPUFANIN1_STRING,
#endif
#if ASL_W83627DHG_AUXFANIN1_SUPPORT
    ASL_W83627DHG_AUXFANIN1_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    THVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
Name(THVS, Package() {
#if ASL_W83627DHG_VCORE_SUPPORT
    ASL_W83627DHG_VCORE_STRING,
#endif
#if ASL_W83627DHG_VIN0_SUPPORT
    ASL_W83627DHG_VIN0_STRING,
#endif
#if ASL_W83627DHG_VIN1_SUPPORT
    ASL_W83627DHG_VIN1_STRING,
#endif
#if ASL_W83627DHG_VIN2_SUPPORT
    ASL_W83627DHG_VIN2_STRING,
#endif
#if ASL_W83627DHG_VIN3_SUPPORT
    ASL_W83627DHG_VIN3_STRING,
#endif
#if ASL_W83627DHG_VCC3_SUPPORT
    ASL_W83627DHG_VCC3_STRING,
#endif
#if ASL_W83627DHG_AVCC_SUPPORT
    ASL_W83627DHG_AVCC_STRING,
#endif
#if ASL_W83627DHG_VSB3_SUPPORT
    ASL_W83627DHG_VSB3_STRING,
#endif
#if ASL_W83627DHG_VBAT_SUPPORT
    ASL_W83627DHG_VBAT_STRING,
#endif
})

//---------------------------------------------------------------------------
// Name: H1SS
//
// Description:  HWM report sensor name string
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//   Arg1 : Index of sensor to return name string
//
// Output:
//   String - Name string of specified sensor
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (H1SS, 2){
    Store ("NULL", Local0)
    If (LEqual(Arg0, 0)) {
        // Temperature
        If (LLess(Arg1, SizeOf(THTS))) {
          Store (DerefOf(Index(THTS, Arg1)), Local0)
        }
    } ElseIf (LEqual(Arg0, 1)) {
        // Fan
        If (LLess(Arg1, SizeOf(THFS))) {
          Store (DerefOf(Index(THFS, Arg1)), Local0)
        }
    } ElseIf (LEqual(Arg0, 2)) {
        // Voltage
        If (LLess(Arg1, SizeOf(THVS))) {
          Store (DerefOf(Index(THVS, Arg1)), Local0)
        }
    }
    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: H1SL
//
// Description:  SIO HWM report sensor name list
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//
// Output:
//   String - List of supported sensor name for specified sensor type
//   
//---------------------------------------------------------------------------
    Method (H1SL, 1){
        Store ("", Local0)
        Store (ONE, Local1)
        Store (0, Local2)    // Sensor number
        Store (0, Local3)    // Counter

        Store (H1SN(Arg0), Local2)    // Sensor number

        While (LLess(Local3, Local2)) {
            If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (H1SS(Arg0, Local3), "\"", ), ), Local0)
            Increment (Local3)
        }
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVT
//
// Description:  SIO HWM convert Temperature reading to mdC (mini-degree-C)
//   Arg0 : Temperature reading
//   Arg1 : Temperature reading format
//     0 - 8 bits with unit 1 dC (degree-C)
//     1 - 9 bits with unit 0.5 dC
//
// Output:
//   INT32 Temperature reading in mdC
//
//---------------------------------------------------------------------------
    Method (HCVT, 2){
        Store (Arg0, Local0)
        // Local0: Reading value
        // Local1: Signed bit
        // 0 - Positive
        // 1 - Negative
        If (LEqual(Arg1,0)){
            Store (And(ShiftRight(Local0,7),0x01), Local1)
            If (LEqual(Local1, 1)) {
                // Transfer to positive value
                Subtract (0xFF, Local0, Local0)
                Increment (Local0)
            }
            Multiply (Local0, 1000, Local0)  // dC to mdC
        }
        Else {
            Store (And(ShiftRight(Local0,8),0x01), Local1)
            If (LEqual(Local1, 1)) {
                // Transfer to positive value
                Subtract (0x1FF, Local0, Local0)
                Increment (Local0)
            }
            Multiply (Local0, 500, Local0)  // 0.5dC to mdC
        }

        // Transform to INT32
        If (LEqual(Local1, 1)) {
            // Transfer back to negative value
            Subtract (0xFFFFFFFF, Local0, Local0)
            Increment (Local0)
        }
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVF
//
// Description:  SIO HWM convert FAN reading to RPM
//   Arg0 : FAN reading
//   Arg1 : Divisor register value
//     0 - Divisor is 1
//     1 - Divisor is 2
//     2 - Divisor is 4
//     3 ...
//
// Output:
//   FAN speed in RPM
//
//---------------------------------------------------------------------------
    Method (HCVF, 2){
        // Check input to prevent divide 0
        If (LEqual(Arg0, 0xFF)) { Return (0) }
        If (LEqual(Arg0, 0)) { Return (0) }

        // Calculate actual divisor number
        Store (One, Local0)
        ShiftLeft (Local0, Arg1, Local0)
        
        // Speed = 1350000/(Divisor*Reading);
        Multiply (Arg0, Local0, Local0)
        Divide (1350000, Local0, , Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: HCVV
//
// Description:  SIO HWM convert Voltage reading to mini-volt
//   Arg0 : Voltage reading
//   Arg1 : R1 value, resistor to power
//   Arg2 : R2 value, resistor to ground
//
// Output:
//   Voltage in mini-volt
//
//---------------------------------------------------------------------------
    Method (HCVV, 3){
        Multiply (Arg0, 8, Local0)  // reading unit is 8mV

        // Check input to prevent divide 0
        If (LEqual(Arg1, 0)) { Return (Local0) }
        If (LEqual(Arg2, 0)) { Return (Local0) }

        // Voltage = Reading * 8mV * (R1 + R2) / R2
        Multiply (Local0, Add(Arg1, Arg2), Local0)
        Divide (Local0, Arg2, , Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: H1RS
//
// Description:  SIO HWM read sensor
//   Arg0 : Sensor Type
//     0 : Temperature
//     1 : Fan
//     2 : Voltage
//   Arg1 : Sensor Name
//
// Output:
//   Sensor reading accoring to Arg0
//     Temperature in mini-degree-C
//     Fan in RPM
//     Voltage in mini-volt
//
// Note: Order for sensors follows same order in BIOS setup.
//   Refer to W83627DHGExternalFunList in W83627DHGHwmSetup.c.
//---------------------------------------------------------------------------
    Method (H1RS, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            If (LEqual(Arg1, ASL_W83627DHG_SYSTIN_STRING)) {  // TEMP1 - SYSTIN - System Temperature 1
                ENBK (0)
                Store (HW27, local0)
                Store (HCVT (local0, 0), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_CPUTIN_STRING)) {  // TEMP2 - CPUTIN/PECI - CPU Temperature
                ENBK (1)
                Store (Or(ShiftLeft(HW50,1), ShiftRight(HW51,7)), local0)
                Store (HCVT (local0, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_AUXTIN_STRING)) {  // TEMP3 - AUXTIN - System Temperature 2
                ENBK (2)
                Store (Or(ShiftLeft(HW50,1), ShiftRight(HW51,7)), local0)
                Store (HCVT (local0, 1), local0)
            }
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            ENBK (0)
            If (LEqual(Arg1, ASL_W83627DHG_SYSFANIN_STRING)) {  // FAN1 - SYSFANIN
                Store (And(ShiftRight(HW47, 4), 0x03), local1)  // BIT[1:0] - Divisor [1:0]
                Store (And(ShiftRight(HW5D, 5), 0x01), local0)  // BIT0 - Divisor [2]
                Or (local1, ShiftLeft(local0, 2), local1)  // local1 - Divisor read
                Store (HW28, local0)
                Store (HCVF (local0, local1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_CPUFANIN0_STRING)) {  // FAN2 - CPUFANIN0
                Store (And(ShiftRight(HW47, 6), 0x03), local1)  // BIT[1:0] - Divisor [1:0]
                Store (And(ShiftRight(HW5D, 6), 0x01), local0)  // BIT0 - Divisor [2]
                Or (local1, ShiftLeft(local0, 2), local1)  // local1 - Divisor read
                Store (HW29, local0)
                Store (HCVF (local0, local1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_AUXFANIN0_STRING)) {  // FAN3 - AUXFANIN0
                Store (And(ShiftRight(HW4B, 6), 0x03), local1)  // BIT[1:0] - Divisor [1:0]
                Store (And(ShiftRight(HW5D, 7), 0x01), local0)  // BIT0 - Divisor [2]
                Or (local1, ShiftLeft(local0, 2), local1)  // local1 - Divisor read
                Store (HW2A, local0)
                Store (HCVF (local0, local1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_CPUFANIN1_STRING)) {  // FAN4 - CPUFANIN1
                Store (And(HW59, 0x03), local1)  // BIT[1:0] - Divisor [1:0]
                Store (And(ShiftRight(HW4C, 7), 0x01), local0)  // BIT0 - Divisor [2]
                Or (local1, ShiftLeft(local0, 2), local1)  // local1 - Divisor read
                Store (HW3F, local0)
                Store (HCVF (local0, local1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_AUXFANIN1_STRING)) {  // FAN5 - AUXFANIN1
                Store (And(ShiftRight(HW59, 2), 0x03), local1)  // BIT[1:0] - Divisor [1:0]
                Store (And(ShiftRight(HW59, 7), 0x01), local0)  // BIT0 - Divisor [2]
                Or (local1, ShiftLeft(local0, 2), local1)  // local1 - Divisor read
                ENBK (5)
                Store (HW53, local0)
                Store (HCVF (local0, local1), local0)
            }
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            ENBK (0)
            If (LEqual(Arg1, ASL_W83627DHG_VCORE_STRING)) {  // VCORE
                Store (HW20, local0)
                Store( HCVV (local0, 0, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VIN0_STRING)) {  // VIN0
                Store (HW21, local0)
                Store( HCVV (local0, ASL_W83627DHG_VIN0_RA, ASL_W83627DHG_VIN0_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VIN1_STRING)) {  // VIN1
                Store (HW24, local0)
                Store( HCVV (local0, ASL_W83627DHG_VIN1_RA, ASL_W83627DHG_VIN1_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VIN2_STRING)) {  // VIN2
                Store (HW25, local0)
                Store( HCVV (local0, ASL_W83627DHG_VIN2_RA, ASL_W83627DHG_VIN2_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VIN3_STRING)) {  // VIN3
                Store (HW26, local0)
                Store( HCVV (local0, ASL_W83627DHG_VIN3_RA, ASL_W83627DHG_VIN3_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VCC3_STRING)) {  // VCC3
                Store (HW23, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_AVCC_STRING)) {  // AVCC
                Store (HW22, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VSB3_STRING)) {  // 3VSB
                ENBK (5)
                Store (HW50, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_W83627DHG_VBAT_STRING)) {  // VBAT
                ENBK (5)
                Store (HW51, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
        }
        Return (local0)
    }
#endif  //ASL_W83627DHG_HWM_PRESENT

#if ASL_W83627DHG_SmartFan_SUPPORT
//------------------------------------------------------------------------
// Table:    THFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
Name(THFC, Package() {
#if ASL_W83627DHG_SYSFANOUT_SUPPORT
    ASL_W83627DHG_SYSFANIN_STRING,
#endif
#if ASL_W83627DHG_CPUFANOUT0_SUPPORT
    ASL_W83627DHG_CPUFANIN0_STRING,
#endif
#if ASL_W83627DHG_AUXFANOUT_SUPPORT
    ASL_W83627DHG_AUXFANIN0_STRING,
#endif
#if ASL_W83627DHG_CPUFANOUT1_SUPPORT
    ASL_W83627DHG_CPUFANIN1_STRING,
#endif
})

//---------------------------------------------------------------------------
// Name: F1FS
//
// Description:  SMF report controller name string
//   Arg0 : Index of Controller to return name string
//
// Output:
//   String - Name string of specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (F1FS, 1){
    Store ("NULL", Local0)

    If (LLess(Arg0, SizeOf(THFC))) {
      Store (DerefOf(Index(THFC, Arg0)), Local0)
    }

    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: F1RN
//
// Description:  SIO SMF report FAN number
//
// Output:
//   Integer - Total smart FAN number supported by this SIO
//   
//---------------------------------------------------------------------------
    Method (F1RN, 0){
        Return (ASL_W83627DHG_SMF_NUMBER)
    }

//---------------------------------------------------------------------------
// Name: F1RL
//
// Description:  SIO SMF Report name list
//
// Input: N/A
//
// Output:
//   String : A list of FAN names that supported Smart FAN from this SIO, seperated by comma.
//
//---------------------------------------------------------------------------
    Method (F1RL, 0){
        Store ("", local0)
        Store (ONE, local1)
        Store (F1RN, Local2)    // SMF number
        Store (0, Local3)    // Counter

        // Return a list of FAN names that supported Smart FAN from this SOP, seperated by comma.
        While (LLess(Local3, Local2)) {
            If (LEqual(Local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (F1FS(Local3), "\"", ), ), Local0)
            Increment (Local3)
        }

        Return (local0)
    }

//------------------------------------------------------------------------
// Table:    TFT2
// Description:  Look up table for target temperature of FANCTRL2.
//   Order is same as CPUFANOUT0 TEMP_SEL (Bank0, Idx49[2:0])
//-------------------------------------------------------------------------
    Name(TFT2, Package() {
        ASL_W83627DHG_CPUTIN_STRING,
        "Reserved",
        "CPU Temperature",  // PECI Agent 1
        "CPU Temperature",  // PECI Agent 2
        "CPU Temperature",  // PECI Agent 3
        "CPU Temperature",  // PECI Agent 4
        "Reserved",
        "Reserved",
    })

//------------------------------------------------------------------------
// Table:    TFT3
// Description:  Look up table for target temperature of FANCTRL3
//   Order is same as AUXFANOUT TEMP_SEL (Bank0, Idx49[6:4])
//-------------------------------------------------------------------------
    Name(TFT3, Package() {
        ASL_W83627DHG_AUXTIN_STRING,
        "Reserved",
        "CPU Temperature",  // PECI Agent 1
        "CPU Temperature",  // PECI Agent 2
        "CPU Temperature",  // PECI Agent 3
        "CPU Temperature",  // PECI Agent 4
        "Reserved",
        "Reserved",
    })

//------------------------------------------------------------------------
// Table:    TFT4
// Description:  Look up table for target temperature of FANCTRL3
//   Order is same as CPUFANOUT1 TEMP_SEL (Bank0, Idx4A[7:5])
//-------------------------------------------------------------------------
    Name(TFT4, Package() {
        ASL_W83627DHG_SYSTIN_STRING,
        ASL_W83627DHG_CPUTIN_STRING,
        ASL_W83627DHG_AUXTIN_STRING,
        "Reserved",
        "CPU Temperature",  // PECI Agent 1
        "CPU Temperature",  // PECI Agent 2
        "CPU Temperature",  // PECI Agent 3
        "CPU Temperature",  // PECI Agent 4
    })

//---------------------------------------------------------------------------
// Name: F1TS
//
// Description:  SMF report name string for target temperature
//   Arg0 : String - FAN name to return
//
// Output:
//   String - Name string of target temperature for specified Controller
//   "NULL" if not found
//
//---------------------------------------------------------------------------
Method (F1TS, 1){
    Store ("NULL", Local0)

    ENBK (0)
    If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
        Return (ASL_W83627DHG_SYSTIN_STRING)
    }
    ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
        Store (DerefOf(Index(TFT2, And(HW49,0x07))), Local0)
    }
    ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
        Store (DerefOf(Index(TFT3, And(ShiftRight(HW49,4),0x07))), Local0)
    }
    ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
        Store (DerefOf(Index(TFT4, And(ShiftRight(HW4A,5),0x07))), Local0)
    }

    Return (Local0)
}

//---------------------------------------------------------------------------
// Name: F1RM
//
// Description:  SMF report FAN mode
//   Arg0 : FAN index
//
// Output:
//   Integer - Bitmap for supported FAN mode.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1RM, 1){
    If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
    } Else { Return(ASL_BFPI_NOT_SUPPORTED) }
    Return (0x3)
}

//---------------------------------------------------------------------------
// Name: F1PW
//
// Description:  SMF report Max. PWM value for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Max. PWM value supported.
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1PW, 1){
    If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
    } Else { Return(ASL_BFPI_NOT_SUPPORTED) }
    Return (255)
}

//---------------------------------------------------------------------------
// Name: F1LP
//
// Description:  SMF report  return Min. slope unit for specified FAN Controller
//   Arg0 : FAN String
//
// Output:
//   Integer - Slope supported by FAN specified by Arg1.
//     Bit0 : Slop type
//       0 : Use Bit[7:4] and Bit[3:1] as step value
//       1 : 2(n), Bit[7:4] and Bit[3:1] are ignored.
//            ex: 1, 2, 4, 8, 16... 2(n)
//     Bit[3:1] : Digit part of step value
//       0 : No digit part
//       1~3: In form of 2-n. Ex: n=1: unit=0.5; n=2: unit=0.25...
//       Others: reserved
//     Bit[7:4] : Integer part of step value.
//     Bit[15:8]: Max. slope value
//     ASL_BFPI_NOT_SUPPORTED: No matched FAN found or slope-liear mode is not supported
//
//---------------------------------------------------------------------------
Method (F1LP, 1){
    Return (ASL_BFPI_NOT_SUPPORTED)  // W83627DHG does not support Slop-Linear mode
}

//---------------------------------------------------------------------------
// Name: F1RC
//
// Description:  SIO SMF Report capability
//
// Input:
//   Arg0 : String - FAN name string to report capability
//
// Output:
//   String : Return correspond Smart FAN functionality in JSON format. Return "NULL" if no FAN matches the name.
//
//---------------------------------------------------------------------------
    Method (F1RC, 1){
        Store ("NULL", Local0)  // String to return
        Store (F1TS(Arg0), Local1)  // Name string for target temperature

        If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
            Return (ASL_W83627DHG_SMFC_SYSFANOUT)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
            Store (ASL_W83627DHG_SMFC_CPUFANOUT0_PREFIX, Local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
            Store (ASL_W83627DHG_SMFC_AUXFANOUT_PREFIX, Local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
            Store (ASL_W83627DHG_SMFC_CPUFANOUT1_PREFIX, Local0)
        } Else { Return (Local0) }

        Concatenate (Local0, Local1, Local0)
        Concatenate (Local0, ASL_W83627DHG_SMFC_FANOUT_SUFFIX, Local0)
        Return (Local0)
    }

//---------------------------------------------------------------------------
// Name: F1GM
//
// Description:  SIO SMF get mode
//   Arg0 : SMF name to get
//
// Output:
//   Integer :
//     Bit[3:0]: Fan Mode
//       0 - Manual mode
//       1 - Linear mode
//     Bit[7:4]: Reserved Bits
//     Bit[15:8]: (valid only for manual mode) Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
    Method (F1GM, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        ENBK (0)

        If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
            And(ShiftRight(HW04, 2), 0x03, local0)
            Or (local0, ShiftLeft(HW01, 8), local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
            And(ShiftRight(HW04, 4), 0x03, local0)
            Or (local0, ShiftLeft(HW03, 8), local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
            And(ShiftRight(HW12, 1), 0x03, local0)
            Or (local0, ShiftLeft(HW11, 8), local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
            And(ShiftRight(HW62, 4), 0x03, local0)
            Or (local0, ShiftLeft(HW61, 8), local0)
        }

        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: F1SM
//
// Description:  SIO SMF set mode
//   Arg0 : SMF name to set
//   Arg1 : SMF mode to set
//       0 - Manual mode
//       1 - Linear mode
//   Arg2 : Duty cycle for manual mode
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER : PWM dutycycle given is larger than Max. supported.
//     BFPI_SUCCESS
//
//---------------------------------------------------------------------------
    Method (F1SM, 3){
        If (LAnd(LEqual(Arg1, 0), LGreater(Arg2, 255))) { Return (ASL_BFPI_INVALID_PARAMETER) }

        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        ENBK (0)

        If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
            If (LEqual(Arg1, 0)) {
                Store (Arg2, HW01)
                And(HW04, 0xF3, HW04)   // Bit[3:2] = 0 : Maunal mode
            }
            Else {
                Or (And(HW04, 0xF3), 0x04, HW04)   // Bit[3:2] = 01b : Thermal Crusie mode
            }
            Store (ASL_BFPI_SUCCESS, local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
            If (LEqual(Arg1, 0)) {
                Store (Arg2, HW03)
                And(HW04, 0xCF, HW04)   // Bit[5:4] = 0 : Maunal mode
            }
            Else {
                Or (And(HW04, 0xCF), 0x30, HW04)   // Bit[3:2] = 11b : Smart Fan III mode
            }
            Store (ASL_BFPI_SUCCESS, local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
            If (LEqual(Arg1, 0)) {
                Store (Arg2, HW11)
                And(HW12, 0xF9, HW12)   // Bit[2:1] = 0 : Maunal mode
            }
            Else {
                Or (And(HW12, 0xF9), 0x02, HW12)   // Bit[2:1] = 01b : Thermal Crusie mode
            }
            Store (ASL_BFPI_SUCCESS, local0)
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
            If (LEqual(Arg1, 0)) {
                Store (Arg2, HW61)
                And(HW62, 0xCF, HW62)   // Bit[5:4] = 0 : Maunal mode
            }
            Else {
                Or (And(HW62, 0xCF), 0x30, HW62)   // Bit[3:2] = 11b : Smart Fan III mode
            }
            Store (ASL_BFPI_SUCCESS, local0)
        }

        Return (local0)
    }

// Control points for CPUFANOUT0
    // Lowest
    Name (F1T1, 0)    // Temperature
    // Highest
    Name (F1T2, 100)
    // Control points for CPUFANOUT1
    // Lowest
    Name (F2T1, 0)    // Temperature
    // Highest
    Name (F2T2, 100)

//---------------------------------------------------------------------------
// Name: F1GP
//
// Description:  SIO SMF control get control point configuration
//   Arg0 : SMF name to get
//   Arg1 : control point to get
//     0 - lowest point
//     1 - highest point
//     2 - secondary low point
//     3 - third low point
//
// Output:
//   Integer :
//     Bit[7:0]: DutyCycle coordinate for this pont
//       0 - 0% duty
//       X - (X/Max)% duty
//       Max - 100% duty
//     Bit[16:8]: Temperature coordinate for this pont
//       0~255
//     BFPI_NOT_SUPPORTED: No FAN matches name provided.
//
//---------------------------------------------------------------------------
    Method (F1GP, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        ENBK (0)

        If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
            If (LLess(Arg1, 1)) {   // SYSFANOUT supports only one control point
                // Thermal cruise mode works differently with linear mode.
                // So we basically take "Start-up" value as PWM duty, "Target Temperature" as Temperature.
                Store (HW0A, local0)    // Start-up value
                Or (local0, ShiftLeft(HW05, 8), local0)
            }
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
            // Smart FAN III mode works quite differently with linear mode.
            // It has no exact temperature setting. So we keeps temperature coodination in ASL name instead.
            If (LEqual(Arg1, 0)) {   // lowest?
                Store (HW09, local0)
                Or (local0, ShiftLeft(F1T1, 8), local0)
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest?
                Store (HW67, local0)
                Or (local0, ShiftLeft(F1T2, 8), local0)
            }
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
            If (LLess(Arg1, 1)) {   // AUXFANOUT supports only one control point
                // Thermal cruise mode works differently with linear mode.
                // So we basically take "Start-up" value as PWM duty, "Target Temperature" as Temperature.
                Store (HW16, local0)    // Start-up value
                Or (local0, ShiftLeft(HW13, 8), local0)
            }
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
            // Smart FAN III mode works quite differently with linear mode.
            // It has no exact temperature setting. So we keeps temperature coodination in ASL name instead.
            If (LEqual(Arg1, 0)) {   // lowest?
                Store (HW64, local0)
                Or (local0, ShiftLeft(F2T1, 8), local0)
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest?
                Store (HW69, local0)
                Or (local0, ShiftLeft(F2T2, 8), local0)
            }
        }

        Return (local0)
    }

//---------------------------------------------------------------------------
// Name: FCVS
//
// Description:  Convert two control point to a slope value suitable for Smart FAN III "Output Step" and "Tolerance"
//   Arg0 : Point 1 PWM duty
//   Arg1 : Point 1 Temperature
//   Arg2 : Point 2 PWM duty
//   Arg3 : Point 2 Temperature
//
// Output:
//   Buffer(4) { "Output Step", "Tolerance", "Initial Value", "Target Temperature" }
//
//---------------------------------------------------------------------------
    Method (FCVS, 4){
        Name (RBUF, Buffer(4) {0x01, 0x01, 0x7F, 0x40})
        Subtract (Arg2, Arg0, local0)   // local0 : PWM delta
        Subtract (Arg3, Arg1, local1)   // local1 : Temperature delta
        Divide (Add(Arg0,Arg2), 2, , local2)   // local2 : Initial Value
        Store (local2, Index(RBUF,2))
        Divide (Add(Arg1,Arg3), 2, , local2)   // local2 : Target Temperature
        Store (local2, Index(RBUF,3))

        If (LEqual(local1, 0)) {    // No Temperature delta
            Store (Local0, Index (RBUF, 0)) // "Output Step" = PWM delta
            Return (RBUF)
        }
        If (LEqual(local0, 0)) {    // No PWM delta
            Store (0x0F, Index (RBUF, 1)) // "Output Step" = PWM delta
            Return (RBUF)
        }
        Divide (local1, local0, local3, local2)
        // local2 : Result, slope to set
        // local3 : Remainder
        Divide (Multiply(local3, 2), local0,, local3)
        If (LEqual(local3,1)) {
            Increment (local2)  // Rounding remainder to local2
        }
        Store (local2, Index(RBUF,0))
        Return (RBUF)
    }

//---------------------------------------------------------------------------
// Name: F1SP
//
// Description:  SIO SMF control set control point configuration
//   Arg0 : SMF name to set
//   Arg1 : Point number to configre.
//     0 - lowest point
//     1 - highest point
//     2 - secondary low point
//     3 - third low point
//   Arg2 : DutyCycle coordinate for this pont
//     0 - 0% duty
//     X - (X/Max)% duty
//     Max - 100% duty
//   Arg3 : Temperature coordinate for this pont
//     0~255
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER :
//       A FAN matches name provided, but is given a wrong control point
//       or PWM dutycycle given is larger than Max. supported.
//     BFPI_SUCCESS
//
// Note:
//   If a control point is given with a value higher than higher control points,
//   the value should also be set to higher point. Vice versa for lower ones.
//---------------------------------------------------------------------------
    Method (F1SP, 4){
        If (LGreater(Arg2, 255)) { Return (ASL_BFPI_INVALID_PARAMETER) }

        Name (BUFF, Buffer(4) {0x0})
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        ENBK (0)

        If (LEqual(Arg0, ASL_W83627DHG_SYSFANIN_STRING)) {
            Store (ASL_BFPI_SUCCESS, local0)
            If (LEqual(Arg1, 0)) {   // SYSFANOUT supports only one control point
                // Thermal cruise mode works differently with linear mode.
                // So we basically take "Start-up" value as PWM duty, "Target Temperature" as Temperature.
                Store (Arg2, HW0A)
                Store (Arg3, HW05)
            }
            Else {
                Store (ASL_BFPI_INVALID_PARAMETER, local0)
            }
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN0_STRING)) {
            Store (ASL_BFPI_SUCCESS, local0)
            If (LEqual(Arg1, 0)) {  // Lower control point
                Store (Arg2, HW09)
                If (LGreater(Arg2, HW67)) {
                    Store (Arg2, HW67)  // Also update point 2 if value is larger.
                }
                Store (Arg3, F1T1)
                If (LGreater(Arg3, F1T2)) {
                    Store (Arg3, F1T2)  // Also update point 2 if value is larger.
                }
            }
            ElseIf (LEqual(Arg1, 1)) {  // Highest control point
                Store (Arg2, HW67)
                If (LLess(Arg2, HW09)) {
                    Store (Arg2, HW09)  // Also update point 1 if value is lower.
                }
                Store (Arg3, F1T2)
                If (LLess(Arg3, F1T1)) {
                    Store (Arg3, F1T1)  // Also update point 1 if value is lower.
                }
            }
            Else {
                Store (ASL_BFPI_INVALID_PARAMETER, local0)
            }
            Store (FCVS(HW09,F1T1,HW67,F1T2), BUFF)
            Store (DerefOf(Index(BUFF,0)), HW68)    // Output Step
            Store (DerefOf(Index(BUFF,1)), local1)
            Or (And(HW07, 0x0F), ShiftLeft(local1, 4), HW07)    // Tolerance
            Store (DerefOf(Index(BUFF,2)), HW03)    // Initial Value
            Store (DerefOf(Index(BUFF,3)), HW06)    // Target Temperature
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_AUXFANIN0_STRING)) {
            Store (ASL_BFPI_SUCCESS, local0)
            If (LEqual(Arg1, 0)) {   // SYSFANOUT supports only one control point
                // Thermal cruise mode works differently with linear mode.
                // So we basically take "Start-up" value as PWM duty, "Target Temperature" as Temperature.
                Store (Arg2, HW16)
                Store (Arg3, HW13)
            }
            Else {
                Store (ASL_BFPI_INVALID_PARAMETER, local0)
            }
        }
        ElseIf (LEqual(Arg0, ASL_W83627DHG_CPUFANIN1_STRING)) {
            Store (ASL_BFPI_SUCCESS, local0)
            If (LEqual(Arg1, 0)) {  // Lower control point
                Store (Arg2, HW64)
                If (LGreater(Arg2, HW69)) {
                    Store (Arg2, HW69)  // Also update point 2 if value is larger.
                }
                Store (Arg3, F2T1)
                If (LGreater(Arg3, F2T2)) {
                    Store (Arg3, F2T2)  // Also update point 2 if value is larger.
                }
            }
            ElseIf (LEqual(Arg1, 1)) {  // Highest control point
                Store (Arg2, HW69)
                If (LLess(Arg2, HW64)) {
                    Store (Arg2, HW64)  // Also update point 1 if value is lower.
                }
                Store (Arg3, F2T2)
                If (LLess(Arg3, F2T1)) {
                    Store (Arg3, F2T1)  // Also update point 1 if value is lower.
                }
            }
            Else {
                Store (ASL_BFPI_INVALID_PARAMETER, local0)
            }
            Store (FCVS(HW64,F2T1,HW69,F2T2), BUFF)
            Store (DerefOf(Index(BUFF,0)), HW6A)    // Output Step
            Store (DerefOf(Index(BUFF,1)), local1)
            Or (And(HW62, 0x0F), local1, HW62)    // Tolerance
            Store (DerefOf(Index(BUFF,2)), HW61)    // Initial Value
            Store (DerefOf(Index(BUFF,3)), HW63)    // Target Temperature
        }

        Return (local0)
    }
#endif // W83627DHG_SmartFan_SUPPORT

//} // End of SIO1

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