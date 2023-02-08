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
// Name:  <F81866DEV.asl>
//
// Description: Define ACPI method or namespce for Super IO.
//
//<AMI_FHDR_END>
//**********************************************************************
//Scope(\_SB.PCI0.SBRG) {
//----------------------------------------------------------------------
// SET OF COMMON DATA/CONTROL METHODS USED FOR ALL LDN BASED SIO DEVICES
//----------------------------------------------------------------------
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
//======================================================================
//Following commented line will be included in PciTree.asl 
//Device(SIO1) {
//    Name(_HID, EISAID("PNP0C02")) // System board resources device node ID
//    Name(_UID,0x111)              // Unique ID. First IO use 0x111, Second IO use 0x222 ...
//======================================================================
    Name(CRS, ResourceTemplate(){
        IO(Decode16, 0, 0, 0, 0, IOI) //Index/Data Io address
        IO(Decode16, 0, 0, 0, 0, IO1) //GP IO space
        IO(Decode16, 0, 0, 0, 0, IO2) //PME IO space
        IO(Decode16, 0, 0, 0, 0, IO3) //HWM IO space
    })

    Method (_CRS, 0){
        //Reserve Super I/O Configuration Port
        //0x0 to 0xF0 already reserved
        //0x3F0 - 0x3F1 are reserved in FDC
        If(LAnd(LLess(SP1O, 0x3F0), LGreater(SP1O, 0x0F0))){
            CreateWordField(CRS, ^IOI._MIN, GPI0)
            CreateWordField(CRS, ^IOI._MAX, GPI1)
            CreateByteField(CRS, ^IOI._LEN, GPIL)
            Store(SP1O, GPI0) //Index/Data Base address
            Store(SP1O, GPI1)
            Store(0x02, GPIL) //IO range
        }
        //Reserve SIO GP IO space
        If(IO1B){
            CreateWordField(CRS, ^IO1._MIN, GP10)
            CreateWordField(CRS, ^IO1._MAX, GP11)
            CreateByteField(CRS, ^IO1._LEN, GPL1)
            Store(IO1B, GP10) //GP IO base address
            Store(IO1B, GP11)
            Store(IO1L, GPL1) //IO range
        }
        //Reserve SIO PME IO space
        If(IO2B){
            CreateWordField(CRS, ^IO2._MIN, GP20)
            CreateWordField(CRS, ^IO2._MAX, GP21)
            CreateByteField(CRS, ^IO2._LEN, GPL2)
            Store(IO2B, GP20) //PME IO base address
            Store(IO2B, GP21)
            Store(IO2L, GPL2) //IO range
        }
        //Reserve SIO HWM IO space
        If(IO3B){
            CreateWordField(CRS, ^IO3._MIN, GP30)
            CreateWordField(CRS, ^IO3._MAX, GP31)
            CreateByteField(CRS, ^IO3._LEN, GPL3)
            Store(IO3B, GP30) //HWM IO base address
            Store(IO3B, GP31)
            Store(IO3L, GPL3) //IO range
        }
        Return(CRS)
    } //End _CRS

    //------------------------------------------------------------------
    // Table correspondence the LDNs to Device order in Routing Table
    // Device type selection is achieved by picking the value from DCAT Package by Offset = LDN
    //------------------------------------------------------------------
    // Elements in the package contain LDN numbers for each category of devices.
    // Default value 0xFF -> no device present.
    // Make sure number of elements not less or equal to largest LDN
    Name (DCAT, Package(0x15){
    // AMI_TODO: fill the table with the present LDN
    // LDN number, 0xFF if device not present
    // We keep category 0x00~0x0F as SIO_DEV_STATUS layout in AmiGenericSio.h to Update IOST 
        0x10,    //0x00 - Serial A (SP1)
        0x11,    //  01 - Serial B (SP2)
        0x03,    //  02 - LPT
        0x00,    //  03 - FDD
        0xFF,    //  04 - SB16 Audio
        0xFF,    //  05 - MIDI
        0xFF,    //  06 - MSS Audio
        0xFF,    //  07 - AdLib sound (FM synth)
        0xFF,    //  08 - Game port #1
        0xFF,    //  09 - Game port #2
        0x05,    //  0A - KBC 60 & 64
        0xFF,    //  0B - EC 62 & 66
        0xFF,    //  0C - Reserved 
        0xFF,    //  0D - Reserved
        0x05,    //  0E - PS/2 Mouse
        0xFF,    //  0F - Reserved
        //add your other device,if no,please cut and modify Package number
        0xFF,    //  10 - CIR
        0x12,    //  11 - Serial C (SP3) 
        0x13,    //  12 - Serial D (SP4)
        0x14,    //  13 - Serial E (SP5)
        0x15,    //  14 - Serial F (SP6)
    })

    //------------------------------------------------------------------
    // Mutex object to sincronize the access to Logical devices
    //------------------------------------------------------------------
    Mutex(MUT0, 0)

    //------------------------------------------------------------------
    // Enter Config Mode, Select LDN
    // Arg0 : Logical Device number
    //------------------------------------------------------------------
    Method(ENFG, 1) {
        Acquire(MUT0, 0xFFF)
        //AMI_TODO: enter config mode and Select LDN.
        Store(ENTK, INDX)
        Store(ENTK, INDX)
        Store(Arg0, LDN)    //Select LDN
    }

    //------------------------------------------------------------------
    // Exit Config Mode
    //------------------------------------------------------------------
    Method(EXFG, 0) {
        //AMI_TODO: exit config mode
        Store(EXTK, INDX)
        Release(MUT0)
    }

    //------------------------------------------------------------------
    // Return current LPT mode : 0-plain LPT, non Zero-ECP mode
    // Arg0 : Device LDN
    //------------------------------------------------------------------
    Method(LPTM, 1){
        ENFG(CGLD(Arg0))        //Enter Config Mode, Select LDN
        //AMI_TODO: if it's ECP mode .
        And(OPT0, 0x02, Local0) //ECP Mode?
        EXFG()                  //Exit Config Mode
        Return(Local0)
    }

    //------------------------------------------------------------------
    // Return current UART mode PnP ID : 0-plain Serial port, non Zero-IrDa mode
    // Arg0 : Device Category #
    //------------------------------------------------------------------
    Method(UHID, 1){
        //AMI_TODO: Return the correct HID base on UART mode (UART/IR)
        ENFG(CGLD(Arg0))                //Enter Config Mode, Select LDN
        And(OPT0, 0x70, Local0)         //Ir mode is active
        EXFG()                          //Exit Config Mode
        If (Local0) {                   //Get Uart mode : 0-Serial port, non-zero - IrDa
            Return(EISAID("PNP0510"))   //PnP Device ID IrDa
        }
        Else {
            Return(EISAID("PNP0501"))   //PnP Device ID 16550 Type
        }
    }

    //------------------------------------------------------------------
    // !!! BELOW ARE GENERIC SIO CONTROL METHODS. DO NOT REQUIRE MODIFICATIONS
    //------------------------------------------------------------------
    //<AMI_THDR_START>
    //------------------------------------------------------------------
    // Name: IOID
    //
    // Type: OperationRegion
    //
    // Description:    Operation Region to point to SuperIO configuration space
    //
    // Notes: OpeRegion address is defined by 'SP1O' global name. 
    //  'SPIO' is a field isnside AML_Exchange data area defined in SDL file.
    //
    // Referrals: BIOS, AMLDATA
    //
    //------------------------------------------------------------------
    //<AMI_THDR_END>
    //------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //------------------------------------------------------------------
    OperationRegion(IOID,   //Name of Operation Region for SuperIO device
        SystemIO,           //Type of address space
        SP1O,               //Offset to start of region
        2)                  //Size of region in bytes
                            //End of Operation Region
    Field(IOID, ByteAcc, NoLock,Preserve){
        INDX, 8,            //Field named INDX is 8 bit wide
        DATA, 8             //Field DATA is 8 bit wide
    }

    //------------------------------------------------------------------
    //  Set of Field names to be used to access SIO configuration space.
    //------------------------------------------------------------------
    IndexField(INDX, DATA, ByteAcc, NoLock, Preserve){
        Offset(0x07),
        LDN, 8,         //Logical Device Number
        Offset(0x21),
        SCF1, 8,        //Set SCF1 
        Offset(0x22),
        SCF2, 8,        //Set SCF2 
        Offset(0x23),
        SCF3, 8,        //Set SCF3 
        Offset(0x24),
        SCF4, 8,        //Set SCF4 
        Offset(0x25),
        SCF5, 8,        //Set SCF5 
        Offset(0x26),
        SCF6, 8,        //Set SCF6 
        Offset(0x29),
        CKCF, 8,        //Multi Function Select 1 Register
        Offset(0x2D),
        CR2D, 8,        //kbc/mouse wakeup register
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
    }

    //------------------------------------------------------------------
    // SIO PME block IO registers
    //------------------------------------------------------------------
    OperationRegion (RNTR, SystemIO, IO2B, IO2L)
    Field (RNTR, ByteAcc, NoLock, Preserve){
        PMES, 8,    //+0 Global PME Status
        Offset(0x04),
        PMEE, 1,    //+4 Global PME Enable
        ,7,
        Offset(0x08),
        PMS3, 8,    //GP2X Wake Status
        PMS2, 8,    //GP1X Wake Status
        PMS1, 8,    //PME  Wake Status
        ,8,
        PME3, 8,    //GP2X Wake Enable
        PME2, 8,    //GP1X Wake Enable
        PME1, 8,    //PME  Wake Enable
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
    //------------------------------------------------------------------
    // Procedure:    CGLD
    // Description:  Convert Device Category to Device's LDN
    // Input: Arg0 : Device category #
    // Output: LDN
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(CGLD, 1) {
        Return(DeRefOf(Index(DCAT, Arg0)))    //Return LDN
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DSTA
    // Description:  GET SIO DEVICE STATUS according to ACTR/IOST(category0x00~0x0F) return values
    //               GET SIO DEVICE STATUS according to ACTR/IOAH+IOAL/IOH2+IOL2(category>0x0F)
    // Input: Arg0 : Device category #
    // Output: Device Status
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSTA, 1) {
        //IO Device presence status is determined during first _STA invocation. 
        //If "Activate" bit is set during first _STA invocation, IO device 
        //present status is stored into IOST global variable.
        //IOST global variable contains the bit mask of all enabled Io devices.
        ENFG(CGLD(Arg0))                    //Enter Config Mode, Select LDN
        Store(ACTR, Local0)                 //Local0=ACTR
        Or(ShiftLeft(IOAH, 8),IOAL,Local1)  //Local1=Base 1
        EXFG()                              //Exit Config Mode
        //LDN's not decoded, Device not present.
        If(LEqual(Local0, 0xFF)) {Return(0x0)}
        //Assume register(ACTR) bit0 is "Active" bit.
        //AMI_TODO: If register(ACTR) non-bit0 is "Active" bit, change below code.
        And(Local0, 1, Local0)  //Leave only "Activate" bit
        //IOST only have 16 bits,IOST is for category 0x00~0x0F device
        If(LLess(Arg0,0x10)) {Or(IOST, ShiftLeft(Local0, Arg0), IOST)}
        //Update IO device status in IOST according to the category#
        //Note. Once device is detected its status bit cannot be removed
        If(Local0){ 
            Return(0x0F)                    // Device present & Active
        }    
        Else{
            If(LLess(Arg0,0x10)){//by IOST check
                //Check if IO device detected in Local0(IOST) bit mask
                If(And(ShiftLeft(1, Arg0), IOST)){ Return(0x0D)}  // Device Detected & Not Active 
                //IO bit not set in Local0: device is disabled during first 
                //_STA(GSTA) invocationor disabled in BIOS Setup.
                Else{ Return(0x00)}         //Device not present
            }
            Else{//by Base1 & Base2 check
                If(Local1) { Return(0x0D)}  //Device Detected & Not Active
                Return(0x00)                //Device not present
            }
        } // End if Else
    } //End of DSTA

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DCNT
    // Description:  Enable/Disable Decoding of Device resources, Route/Release
    //               I/O & DMA Resources From, To EIO/LPC Bus
    // Input: Arg0 : Device catagory #
    //        Arg1 : 0/1 Disable/Enable resource decoding
    // Output:Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DCNT, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN
        //Route/Release DMA channel from/to being ISA/PCI mode
        //Note. DMA channel 0 is currently not decoded, although it can be 
        //used on some of SIO chipsets.
        If(LAnd(LLess(DMCH,4), LNotEqual(And(DMCH, 3, Local1),0))){
//            rDMA(Arg0, Arg1, Increment(Local1))
        }
        Store(Arg1, ACTR)           //Update Activate Register
        ShiftLeft(IOAH, 8, local1)  //Get IO Base address
        Or(IOAL, Local1, Local1)
        //Route/Release I/O resources from/to EIO/LPC Bus
        //Arg0      Device Category
        //Arg1      0/1 Disable/Enable resource decoding
        //Arg2      Port to Route/Release
        //Arg3      Port SIZE to Route 
//        RRIO(Arg0, Arg1, Local1, 0x08)
        EXFG()                      //Exit Config Mode
    }

    //<AMI_THDR_START>
    //------------------------------------------------------------------
    // Name: CRS1,CRS2,CRS3
    //
    // Type: ResourceTemplate
    //
    // Description: Current Resources Buffer for Generic SIO devices
    //
    // Notes: Note. DMA channel 0 is currently decoded as reserved,
    //        although, it can be used on some of SIO chipsets.
    //        Add DMA0 to _PRS if it is used
    //        Generic Resourse template for FDC, COMx, LPT and ECP Current Resource Settings
    //        (to be initialized and returned by _CRS)
    //------------------------------------------------------------------
    //<AMI_THDR_END>
    //CRS buffer with all kinds of resources
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
    //Extended CRS buffer with 2 IO ranges
    Name(CRS2, ResourceTemplate(){
        IO(Decode16, 0, 0, 1, 0, IO02)
        IO(Decode16, 0, 0, 1, 0, IO03)
        IRQNoFlags(IRQ2) {}
            DMA(Compatibility, NotBusMaster, Transfer8, DMA2) {}
    })
    CreateWordField(CRS2, IRQ2._INT, IRQE)    //IRQ mask 0x1
    CreateByteField(CRS2, DMA2._DMA, DMAE)    //DMA 0x4
    CreateWordField(CRS2, IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
    CreateWordField(CRS2, IO02._MAX, IO22)    //Range 1 Max Base Word 0xa
    CreateByteField(CRS2, IO02._LEN, LEN2)    //Length 1 0xd
    CreateWordField(CRS2, IO03._MIN, IO31)    //Range 2 Min Base Word 0x10
    CreateWordField(CRS2, IO03._MAX, IO32)    //Range 2 Max Base Word 0x12
    CreateByteField(CRS2, IO03._LEN, LEN3)    //Length 2 0x15
    //CRS buffer without DMA resource
    Name(CRS3, ResourceTemplate(){
        IO(Decode16, 0, 0, 1, 0, IO04)
        IRQ(Level,ActiveLow,Shared,IRQ3){}    
        //DMA(Compatibility, NotBusMaster, Transfer8, DMA3) {} //RayWu, REMOVE 2014/09/03
    })
    CreateWordField(CRS3, IRQ3._INT, IRQT)    //IRQ mask 0x9
    CreateByteField(CRS3, 0x0B,IRQS)          //IRQ Shared/Active-Low/Edge-Triggered/=0x19 0xB
    //CreateByteField(CRS3, DMA3._DMA, DMAT)    //DMA 0x4  //RayWu, REMOVE 2014/09/03
    CreateWordField(CRS3, IO04._MIN, IO41)    //Range 1 Min Base Word 0x2
    CreateWordField(CRS3, IO04._MAX, IO42)    //Range 1 Max Base Word 0x4
    CreateByteField(CRS3, IO04._LEN, LEN4)    //Length 1 0x7

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DCRS
    // Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
    //               Returns Byte stream of Current resources. May contain Resources such:
    //               1 IRQ resource
    //               1 DMA resource
    //               1 IO Port
    // Input: Arg0 : Device catagory #
    //        Arg1 : Use/No-Use DMA
    // Output:       _CRS Resource Buffer 
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DCRS, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN
        //Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO11)    //Get IO Base MSB
        Or(IOAL, IO11, IO11)        //Get IO Base LSB
        Store(IO11, IO12)           //Set Max Base Word
        //Store(0x08, LEN1)
        //adjust base/aligment size if base ports are 0x3bc/0x7bc
        //If(LEqual(And(IO1L,0xff), 0xbc))
        //If(And(IO11, 0x04)){
        //   Store(0x04, LEN1)
        //}
        Store(0x08, LEN1)
        //Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQM)
        } 
        Else{
            Store(0, IRQM)          //No IRQ used
        }
        //Write Current Settings into DMA descriptor
        //Note. DMA channel 0 is currently decoded as reserved,
        //although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAM)          //No DMA
        } 
        Else{
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAM)
        }
        EXFG()                      //Exit Config Mode
        Return(CRS1)                //Return Current Resources
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DCR2
    // Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
    //               Returns Byte stream of Current resources. May contain Resources such:
    //               1 IRQ resource
    //               1 DMA resource
    //               2 IO Port
    // Input: Arg0 : Device catagory #
    //        Arg1 : Use/No-Use DMA
    // Output:      _CRS Resource Buffer 
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DCR2, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN
        //Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO21)    //Get IO Base MSB
        Or(IOAL, IO21, IO21)        //Get IO Base LSB
        Store(IO21, IO22)           //Set Max Base Word
        Store(0x08, LEN2)
        //Write Current Settings into Buffer for 2nd IO Descriptor
        ShiftLeft(IOH2, 8, IO31)    //Get IO Base MSB
        Or(IOL2, IO31, IO31)        //Get IO Base LSB
        Store(IO31, IO32)           //Set Max Base Word
        Store(0x08, LEN3)
        //Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQE)
        } 
        Else{
            Store(0, IRQE)          //No IRQ used
        }
        //Write Current Settings into DMA descriptor
        //Note. DMA channel 0 is currently decoded as reserved,
        //although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAE)          //No DMA
        } Else {
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAE)
        }
        EXFG()                      //Exit Config Mode
        Return(CRS2)                //Return Current Resources
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DCR3
    // Description:  Get FDC, LPT, ECP, UART, IRDA resources (_CRS)
    //               Returns Byte stream of Current resources. May contain Resources such:
    //               1 IRQ resource
    //               1 IO Port
    // Input: Arg0 : Device catagory #
    // Output:      _CRS Resource Buffer 
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DCR3, 2) {
        ENFG(CGLD(Arg0))            //Enter Config Mode, Select LDN
        //Write Current Settings into Buffer for 1st IO Descriptor
        ShiftLeft(IOAH, 8, IO41)    //Get IO Base MSB
        Or(IOAL, IO41, IO41)        //Get IO Base LSB
        Store(IO41, IO42)           //Get Max Base Word
        Store(0x08, LEN4)
        //Write Current Settings into IRQ descriptor
        If(INTR){
            ShiftLeft(1, INTR, IRQT)
        //Set IRQ Type:porting according INTT
        //AMI_TODO:
        //If(And(INTT,0x01)){
        //   Store(0x19, IRQS)     //IRQ Type: Active-Low-Edge-Triggered,Shared.
        //} Else {
        //   Store(1, IRQS)        //IRQ Type: Active-High-Edge-Triggered,No-Shared(default)
        //}
		 //AAEON_OVERRIDE >>
		 If(And(OPT0,0x01)){
		 	//Report IRQ Receiver mode to ACPI OS by IRQS.
		 	//IRQ Receiver - ACPI IRQS: bit4:_SHR,bit3:_LL,bit0:_HE
		 	//IRQ Sender - Fintek IRQ_MODE1(OTP6[3]) and IRQ_MODE0(OPT0[1]):
		 	//    00 : Sharing IRQ active low Level mode.
		 	//    01 : Sharing IRQ active high edge mode.
		 	//    10 : Sharing IRQ active high Level mode.
		 	//    11 : Reserved
			If(And(OPT0,0x02)){
				If(And(OPT6,0x08)){
					// Sender : 11 : Reserved
					// Code shoud not come here because IRQ type for "Reserved" is undefined.
					// F81966 Patch, reture 0x19 assuming as is.
					// Receiver: Low-Edge-Triggered : 0x19
					Store(0x19, IRQS)	}
				Else{
					// Sender : 01 : Sharing IRQ active high edge mode.
					// Receiver: High-Edge-Triggered : 0x11
					// F81966 patch, Force receiver to operat in Low-Edge-Triggered : 0x19
					//Store(0x11, IRQS)	}
					Store(0x19, IRQS)	}
			}Else{
				If(And(OPT6,0x08)){
					// Sender : 10 : Sharing IRQ active high Level mode.
					// Receiver: high-Level-Triggered : 0x10
					Store(0x10, IRQS)	}	// IRQ Type: Active-High-Level-Triggered,Shared.
				Else{
					// Sender : 00 : Sharing IRQ active low Level mode.
					// Receiver: Low-Level-Triggered : 0x18
					Store(0x18, IRQS)	}	// IRQ Type: Active-Low-Level-Triggered,Shared.
			}
		 }
		 //AAEON_OVERRIDE <<
        }Else{
            Store(0, IRQT)          //No IRQ used
        }
        //RayWu, REMOVE 2014/09/03 >>
        ////Write Current Settings into DMA descriptor
        ////Note. DMA channel 0 is currently decoded as reserved,
        ////although, it can be used on some of SIO chipsets.
        ////If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        //If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
        //    Store(0, DMAT)          //No DMA
        //} Else {
        //    And(DMCH, 3, Local1)
        //    ShiftLeft(1, Local1, DMAT)
        //}
        //RayWu, REMOVE 2014/09/03 <<
        EXFG()                      //Exit Config Mode
        Return(CRS3)                //Return Current Resources
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DSRS
    // Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
    //               Control method can be used for configuring devices with following resource order:
    //               1 IRQ resource
    //               1 DMA resource
    //               1 IO Port
    // Input: Arg0 : PnP Resource String to set
    //        Arg1 : Device catagory #
    // Output:       Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSRS, 2) {
        If(And(LEqual(Arg1, 0x02),LPTM(Arg1) ) ) {      //LPT logical device? Extended LPT mode ?
                DSR2(Arg0, Arg1)
        } Else {
            //Set resource for other devices from CRS1, or just for Parallel Port LPT Mode
            CreateWordField(Arg0, ^IRQ1._INT, IRQM)     //IRQ mask 0x1
            CreateByteField(Arg0, ^DMA1._DMA, DMAM)     //DMA 0x4
            CreateWordField(Arg0, ^IO01._MIN, IO11)     //Range 1 Min Base Word 0x8
            //Enter Config Mode
            ENFG(CGLD(Arg1))                            //Enter Config Mode, Select LDN
            //Set Base IO Address
            And(IO11, 0xFF, IOAL)                       //Set IO Base LSB
            ShiftRight(IO11, 0x8, IOAH)                 //Set IO Base MSB
            //Set IRQ
            If(IRQM){
                FindSetRightBit(IRQM, Local0)
                Subtract(Local0, 1, INTR)
            }Else{
                Store(0, INTR)                          //No IRQ used
            }
            //Set DMA
            If(DMAM){
                FindSetRightBit(DMAM, Local0)
                Subtract(Local0, 1, DMCH)
            }Else{
                Store(4, DMCH)                          //No DMA
            }
            //Exit Config Mode
            EXFG()                                      //Exit Config Mode
            //Enable ACTR
            DCNT(Arg1, 1)                               //Enable Device (Routing)
            Store(Arg1, Local2)
            If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
        }//Else end
    }//Method DSRS end

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DSR2
    // Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
    //               Control method can be used for configuring devices with following resource order:
    //               1 IRQ resource
    //               1 DMA resource
    //               2 IO Port
    // Input: Arg0 : PnP Resource String to set
    //        Arg1 : Device catagory #
    // Output:       Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSR2, 2) {
        CreateWordField(Arg0, ^IRQ2._INT, IRQE)    //IRQ mask 0x1
        CreateByteField(Arg0, ^DMA2._DMA, DMAE)    //DMA 0x4
        CreateWordField(Arg0, ^IO02._MIN, IO21)    //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IO03._MIN, IO31)    //Range 1 Min Base Word 0x8
        //Enter Config Mode
        ENFG(CGLD(Arg1))                            //Enter Config Mode, Select LDN
        //Set Base IO Address
        And(IO21, 0xFF, IOAL)                       //Set IO1 Base LSB
        ShiftRight(IO21, 0x8, IOAH)                 //Set IO1 Base MSB
        And(IO31, 0xFF, IOL2)                       //Set IO2 Base LSB
        ShiftRight(IO31, 0x8, IOH2)                 //Set IO2 Base MSB
        //Set IRQ
        If(IRQE){
            FindSetRightBit(IRQE, Local0)
            Subtract(Local0, 1, INTR)
        }Else{
            Store(0, INTR)                          //No IRQ used
        }
        //Set DMA
        If(DMAE){
            FindSetRightBit(DMAE, Local0)
            Subtract(Local0, 1, DMCH)
        }Else{
            Store(4, DMCH)                          //No DMA
        }
        //Exit Config Mode
        EXFG()                                      //Exit Config Mode
        //Enable ACTR
        DCNT(Arg1, 1)                               //Enable Device (Routing)
        Store(Arg1, Local2)
        If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DSR3
    // Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
    //               Control method can be used for configuring devices with following resource order:
    //               1 IRQ resource
    //               1 IO Port
    // Input: Arg0 : PnP Resource String to set
    //        Arg1 : Device catagory #
    // Output:       Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSR3, 2) {
        CreateWordField(Arg0, ^IO04._MIN, IO41)     //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IRQ3._INT, IRQT)     //IRQ mask 0x1
        CreateByteField(Arg0, 0x0B, IRQS)           //IRQ Flag
        //CreateByteField(Arg0, ^DMA3._DMA, DMAT)     //DMA //RayWu, REMOVE 2014/09/03
        //Enter Config Mode
        ENFG(CGLD(Arg1))
        //Set Base IO Address
        And(IO41,0xff, IOAL)                        //Set IO Base LSB
        ShiftRight(IO41, 0x8, IOAH)                 //Set IO Base MSB
        //Set IRQ
        If(IRQT){
            FindSetRightBit(IRQT, Local0)
            Subtract(Local0, 1, INTR)
            Or(OPT0, 0x01, OPT0) //B403_042_RayWu, ADD 2014/10/01
	    //AAEON_OVERRIDE >>
            //Set IRQ sender(F81866) mode according to Arg0 (expecting it is resource description ACPI OS get from UART3~6.asl)
            //IRQ Receiver - ACPI IRQS: bit4:_SHR,bit3:_LL,bit0:_HE
            //IRQ Sender - Fintek IRQ_MODE1(OTP6[3]) and IRQ_MODE0(OPT0[1]):
            //    00 : Sharing IRQ active low Level mode.
            //    01 : Sharing IRQ active high edge mode.
            //    10 : Sharing IRQ active high Level mode.
            //    11 : Reserved
            If(And(IRQS,0x10)){			// IRQ Shared? 1 - Shared
                If(And(IRQS,0x01)){		// IRQ Mode? 1 - Edge, 0 -Level
                    // Edge-Triggered
                    If(And(IRQS,0x08)){	// IRQ Polarity? 1 - Low, 0 - High
                        // Receiver: Low-Edge-Triggered : 0x19
                        // F81966 Patch, Set sender to 01 : Sharing IRQ active high edge mode.
                        And(OPT6, 0xF7, OPT6)
                        Or(OPT0, 0x02, OPT0)
                    } Else{
                        // Receiver: High-Edge-Triggered : 0x11
                        // Sender: 01 : Sharing IRQ active high edge mode.
                        And(OPT6, 0xF7, OPT6)
                        Or(OPT0, 0x02, OPT0)
                    }							
                }Else{
                    // Level-Triggered
                    If(And(IRQS,0x08)){	// IRQ Polarity? 1 - Low, 0 - High
                        // Receiver: Low-Level-Triggered : 0x18
                        // Sender: 00 : Sharing IRQ active low Level mode.
                        And(OPT6, 0xF7, OPT6)
                        And(OPT0, 0xFD, OPT0)
                    }Else{
                        // Receiver: high-Level-Triggered : 0x10
                        // Sender: 10 : Sharing IRQ active high Level mode.
                        Or(OPT6, 0x08, OPT6)
                        And(OPT0, 0xFD, OPT0)
                    }	
                }		
            }	
	    //AAEON_OVERRIDE <<
        }Else{
            Store(0, INTR)                          //No IRQ used
        }
        //RayWu, REMOVE 2014/09/03 >>
        ////Set DMA
        //If(DMAT){
        //   FindSetRightBit(DMAT, Local0)
        //   Subtract(Local0, 1, DMCH)
        //}Else{
        //   Store(4, DMCH)                           //No DMA
        //}
        //RayWu, REMOVE 2014/09/03 <<
        //Exit Config Mode
        EXFG()
        //Enable ACTR
        DCNT(Arg1, 1)                               //Enable Device (Routing)
        Store(Arg1, Local2)
        If (LGreater(Local2, 0)){Subtract(Local2, 1, Local2)}
    }

//======================================================================
//Following commented line will be included in PciTree.asl 
//} //End of SIO1
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
