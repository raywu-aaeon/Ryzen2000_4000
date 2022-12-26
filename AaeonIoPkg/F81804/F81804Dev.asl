//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
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
// Name:  <F81804DEV.asl>
//
// Description: Define ACPI method or name space for Super IO.
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
// SIO specific: LPTM - current parallel port mode
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
        IO3B, // Offset to start of region
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
        Offset(0x70),
        HW70, 8,
        HW71, 8,
        HW72, 8,
        HW73, 8,
        HW74, 8,
        Offset(0x7E),
        HW7E, 8,
        Offset(0x96),
        HW96, 8,
        Offset(0xA0),
        HWA0, 8,
        HWA1, 8,
        HWA2, 8,
        HWA3, 8,
        HWA4, 8,
        HWA5, 8,
        HWA6, 8,
        HWA7, 8,
        HWA8, 8,
        HWA9, 8,
        HWAA, 8,
        HWAB, 8,
        HWAC, 8,
        HWAD, 8,
        HWAE, 8,
        HWAF, 8,
        Offset(0xC0),
        HWC0, 8,
        HWC1, 8,
        HWC2, 8,
        HWC3, 8,
        HWC4, 8,
        HWC5, 8,
        HWC6, 8,
        HWC7, 8,
        HWC8, 8,
        HWC9, 8,
        HWCA, 8,
        HWCB, 8,
        HWCC, 8,
        HWCD, 8,
        HWCE, 8,
        HWCF, 8,
     }
    Name(CRS, ResourceTemplate(){
        IO(Decode16, 0, 0, 0, 0, IOI) //Index/Data Io address
        IO(Decode16, 0, 0, 0, 0, IO1) //GP IO space
        IO(Decode16, 0, 0, 0, 0, IO2) //WDT IO space
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
            Store(IO1B, GP10) //IO base address
            Store(IO1B, GP11)
            Store(IO1L, GPL1) //IO range
        }
        //Reserve SIO WDT IO space
        If(IO2B){
            CreateWordField(CRS, ^IO2._MIN, GP20)
            CreateWordField(CRS, ^IO2._MAX, GP21)
            CreateByteField(CRS, ^IO2._LEN, GPL2)
            Store(IO2B, GP20) //IO base address
            Store(IO2B, GP21)
            Store(IO2L, GPL2) //IO range
        }
        //Reserve SIO HWM IO space
        If(IO3B){
            CreateWordField(CRS, ^IO3._MIN, GP30)
            CreateWordField(CRS, ^IO3._MAX, GP31)
            CreateByteField(CRS, ^IO3._LEN, GPL3)
            Store(IO3B, GP30) //IO base address
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
        0x15,    //  01 - Serial B (SP2)
        0xFF,    //  02 - LPT
        0xFF,    //  03 - FDD
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
        //Add your other device here. Their bit mask of statuses IOES:
        0xFF,    //  10 - CIR ------------ 0x00
        0xFF,    //  11 - Serial C (SP3) -   01
        0xFF,    //  12 - Serial D (SP4) -   02
        0xFF,    //  13 - Serial E (SP5) -   03
        0xFF,    //  14 - Serial B (SP6) -   04
    })

    //------------------------------------------------------------------
    // Mutex object to synchronize the access to Logical devices
    //------------------------------------------------------------------
    Mutex(MUT0, 0)

    //------------------------------------------------------------------
    // Enter Config Mode, Select LDN
    // Arg0 : Logical Device number
    //------------------------------------------------------------------
    Method(ENFG, 1) {
        Acquire(MUT0, 0xFFF)
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
    // Return current UART mode PnP ID : 0-plain Serial port, non Zero-IrDa mode
    // Arg0 : Device Category #
    //------------------------------------------------------------------
    Method(UHID, 1){
        //AMI_TODO: Return the correct HID base on UART mode (UART/IR)
        ENFG(CGLD(Arg0))                //Enter Config Mode, Select LDN
        And(OPT1, 0x10, Local0)         //IR mode is active
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
    //  'SPIO' is a field inside AML_Exchange data area defined in SDL file.
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
        offset(0x80),
        RG80, 8,        //Option Register 80 GPIO7x Output Enable Register
        RG81, 8,        //Option Register 81 GPIO7x Output Data Register
        RG82, 8,        //Option Register 82 GPIO7x Pin Status Register
        RG83, 8,        //Option Register 83 GPIO7x Drive Enable Register
        offset(0x90),
        RG90, 8,        //Option Register 90 GPIO6x Output Enable Register
        RG91, 8,        //Option Register 91 GPIO6x Output Data Register
        RG92, 8,        //Option Register 92 GPIO6x Pin Status Register
        RG93, 8,        //Option Register 93 GPIO6x Drive Enable Register
        offset(0x98),
        RG98, 8,        //Option Register 98 GPIO9x Output Enable Register
        RG99, 8,        //Option Register 99 GPIO9x Output Data Register
        RG9A, 8,        //Option Register 9A GPIO9x Pin Status Register
        RG9B, 8,        //Option Register 9B GPIO9x Drive Enable Register
        offset(0xA0),
        RGA0, 8,        //Option Register A0 GPIO5x Output Enable Register
        RGA1, 8,        //Option Register A1 GPIO5x Output Data Register
        RGA2, 8,        //Option Register A2 GPIO5x Pin Status Register
        RGA3, 8,        //Option Register A3 GPIO5x Drive Enable Register
        RGA4, 8,        //Option Register A4 GPIO5x SMI Enable Register
        RGA5, 8,        //Option Register A5 GPIO5x SMI Detect Select Register
        RGA6, 8,        //Option Register A6 GPIO5x SMI Status Register
        Offset(0xD0),
        RGD0, 8,        //Option Register D0 GPIO2x Output Enable Register
        RGD1, 8,        //Option Register D1 GPIO2x Output Data Register
        RGD2, 8,        //Option Register D2 GPIO2x Pin Status Register
        Offset(0xE0),
        RGE0, 8,        //Option Register E0 GPIO1x Output Enable Register
        RGE1, 8,        //Option Register E1 GPIO1x Output Data Register
        RGE2, 8,        //Option Register E2 GPIO1x Pin Status Register
        RGE3, 8,        //Option Register E3 GPIO1x Drive Enable Register
        RGE4, 8,        //Option Register E4 GPIO1x SMI Enable Register
        RGE5, 8,        //Option Register E5 GPIO1x SMI Detect Select Register
        RGE6, 8,        //Option Register E6 GPIO1x SMI Status Register
        RGE7, 8,        //Option Register E7
        RGE8, 8,        //Option Register E8
        RGE9, 8,        //Option Register E9
        Offset(0xF0),
        OPT0, 8,        //Option register 0xF0 GPIO0x Output Enable Register
        OPT1, 8,        //Option register 0xF1 GPIO0x Output Data Register
        OPT2, 8,        //Option register 0xF2 GPIO0x Pin Status Register
        OPT3, 8,        //Option register 0xF3 GPIO0x Drive Enable Register
        OPT4, 8,        //Option register 0xF4 GPIO0x SMI Enable Register
        OPT5, 8,        //Option register 0xF5 GPIO0x SMI Detect Select Register/WDT Control Configuration Register
        OPT6, 8,        //Option register 0xF6 GPIO0x SMI Status Register       /WDT Timer Configuration Register        
        OPT7, 8,        //Option register 0xF7 GPIO0x Pulse Width Select Register
        OPT8, 8,        //Option register 0xF8 GPIO0x Output Mode Register
        OPT9, 8,        //Option register 0xF9
    }

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
            Else{//If here, should use ESTA
                Return(0x00)
            }
        } // End if Else
    } //End of DSTA

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    ESTA
    // Description:  GET SIO DEVICE STATUS according to ACTR/IOES((category>0x0F)) return values
    // Input: Arg0 : Device category #
    // Output: Device Status
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(ESTA, 1) {
        //IO Device presence status is determined during first _STA invocation. 
        //If "Activate" bit is set during first _STA invocation, IO device 
        //present status is stored into IOES global variable.
        //IOES global variable contains the bit mask of all enabled Io devices.
        ENFG(CGLD(Arg0))                    //Enter Config Mode, Select LDN
        Store(ACTR, Local0)                 //Local0=ACTR
        EXFG()                              //Exit Config Mode
        //LDN's not decoded, Device not present.
        If(LEqual(Local0, 0xFF)) {Return(0x0)}
        //Assume register(ACTR) bit0 is "Active" bit.
        //AMI_TODO: If register(ACTR) non-bit0 is "Active" bit, change below code.
        And(Local0, 1, Local0)  //Leave only "Activate" bit
        //IOES only have 16 bits,IOES is for category>0x0F device
        If(LGreater(Arg0,0x0F)) {Or(IOES, ShiftLeft(Local0, And(Arg0, 0x0F)), IOES)}
        //Update IO device status in IOES according to the category#
        //Note. Once device is detected its status bit cannot be removed
        If(Local0){ 
            Return(0x0F)                    // Device present & Active
        }    
        Else{
            If(LGreater(Arg0,0x0F)){//by IOES check
                //Check if IO device detected in Local0(IOES) bit mask
                If(And(ShiftLeft(1, And(Arg0, 0x0F)), IOES)){ Return(0x0D)}  // Device Detected & Not Active 
                //IO bit not set in Local0: device is disabled during first 
                //_STA(GSTA) invocationor disabled in BIOS Setup.
                Else{ Return(0x00)}         //Device not present
            }
            Else{//If here, should use DSTA
                Return(0x00)
            }
        } // End if Else
    } //End of ESTA

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DCNT
    // Description:  Enable/Disable Decoding of Device resources, Route/Release
    //               I/O & DMA Resources From, To EIO/LPC Bus
    // Input: Arg0 : Device category #
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
            rDMA(Arg0, Arg1, Increment(Local1))
        }
        Store(Arg1, ACTR)           //Update Activate Register
        ShiftLeft(IOAH, 8, local1)  //Get IO Base address
        Or(IOAL, Local1, Local1)
        //Route/Release I/O resources from/to EIO/LPC Bus
        //Arg0      Device Category
        //Arg1      0/1 Disable/Enable resource decoding
        //Arg2      Port to Route/Release
        //Arg3      Port SIZE to Route 
        RRIO(Arg0, Arg1, Local1, 0x08)
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
    //        Generic Resource template for FDC, COMx, LPT and ECP Current Resource Settings
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
        DMA(Compatibility, NotBusMaster, Transfer8, DMA3) {}
    })
    CreateWordField(CRS3, IRQ3._INT, IRQT)    //IRQ mask 0x9
    CreateByteField(CRS3, 0x0B,IRQS)          //IRQ Shared/Active-Low/Edge-Triggered/=0x19 0xB
    CreateByteField(CRS3, DMA3._DMA, DMAT)    //DMA 0x4
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
    // Input: Arg0 : Device category #
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
        //adjust base/alignment size if base ports are 0x3bc/0x7bc
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
    // Input: Arg0 : Device category #
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
    // Input: Arg0 : Device category #
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
        }Else{
            Store(0, IRQT)          //No IRQ used
        }
        //Write Current Settings into DMA descriptor
        //Note. DMA channel 0 is currently decoded as reserved,
        //although, it can be used on some of SIO chipsets.
        //If(Or(LGreater(DMCH,3), LEqual(And(DMCH, 3, Local1),0))){
        If(LOr(LGreater(DMCH,3), LEqual(Arg1, 0))){
            Store(0, DMAT)          //No DMA
        } Else {
            And(DMCH, 3, Local1)
            ShiftLeft(1, Local1, DMAT)
        }
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
    //        Arg1 : Device category #
    // Output:       Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSRS, 2) {
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
    //        Arg1 : Device category #
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
    }

    //<AMI_PHDR_START>
    //------------------------------------------------------------------
    // Procedure:    DSR3
    // Description:  Set FDC, LPT, ECP, UART, IRDA resources (_SRS)
    //               Control method can be used for configuring devices with following resource order:
    //               1 IRQ resource
    //               1 IO Port
    // Input: Arg0 : PnP Resource String to set
    //        Arg1 : Device category #
    // Output:       Nothing
    //------------------------------------------------------------------
    //<AMI_PHDR_END>
    Method(DSR3, 2) {
        CreateWordField(Arg0, ^IO04._MIN, IO41)     //Range 1 Min Base Word 0x8
        CreateWordField(Arg0, ^IRQ3._INT, IRQT)     //IRQ mask 0x1
        CreateByteField(Arg0, 0x0B, IRQS)           //IRQ Flag
        CreateByteField(Arg0, ^DMA3._DMA, DMAT)     //DMA
        //Enter Config Mode
        ENFG(CGLD(Arg1))
        //Set Base IO Address
        And(IO41,0xff, IOAL)                        //Set IO Base LSB
        ShiftRight(IO41, 0x8, IOAH)                 //Set IO Base MSB
        //Set IRQ
        If(IRQT){
            FindSetRightBit(IRQT, Local0)
            Subtract(Local0, 1, INTR)
        //Set IRQ flag,AMI_TODO: bit4:_SHR,bit3:_LL,bit0:_HE
        //Store(IRQS, INTT) //some relative share,active-low/high registers
        }Else{
            Store(0, INTR)                          //No IRQ used
        }
        //Set DMA
        If(DMAT){
           FindSetRightBit(DMAT, Local0)
           Subtract(Local0, 1, DMCH)
        }Else{
           Store(4, DMCH)                           //No DMA
        }
        //Exit Config Mode
        EXFG()
        //Enable ACTR
        DCNT(Arg1, 1)                               //Enable Device (Routing)
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
#ifndef ASL_F81804_TEMPERATURE_1_STRING
    #define ASL_F81804_TEMPERATURE_1_STRING "F81804-TEMP1IN"
#endif
#ifndef ASL_F81804_TEMPERATURE_2_STRING
    #define ASL_F81804_TEMPERATURE_2_STRING "F81804-TEMP2IN"
#endif
#ifndef ASL_F81804_TEMPERATURE_3_STRING
    #define ASL_F81804_TEMPERATURE_3_STRING "F81804-TEMP3IN"
#endif
#ifndef ASL_F81804_FAN_1_STRING
    #define ASL_F81804_FAN_1_STRING "F81804-FAN1"
#endif
#ifndef ASL_F81804_FAN_2_STRING
    #define ASL_F81804_FAN_2_STRING "F81804-FAN2"
#endif
#ifndef ASL_F81804_3VCC_STRING
    #define ASL_F81804_3VCC_STRING "F81804-3VCC"
#endif
#ifndef ASL_F81804_VIN1_STRING
    #define ASL_F81804_VIN1_STRING "F81804-VIN1"
#endif
#ifndef ASL_F81804_VIN2_STRING
    #define ASL_F81804_VIN2_STRING "F81804-VIN2"
#endif
#ifndef ASL_F81804_VSB3V_STRING
    #define ASL_F81804_VSB3V_STRING "F81804-VSB3V"
#endif
#ifndef ASL_F81804_VBAT_STRING
    #define ASL_F81804_VBAT_STRING "F81804-VBAT"
#endif
#ifndef ASL_F81804_5VSB_STRING
    #define ASL_F81804_5VSB_STRING "F81804-5VSB"
#endif
//Peter debug++Need modify
#ifndef ASL_SIO_WDT_MAX_TIMEOUT
    #define ASL_SIO_WDT_MAX_TIMEOUT "15300000"
#endif
#ifndef ASL_F81804_TEMP_SENSOR_NUMBER
    #define ASL_F81804_TEMP_SENSOR_NUMBER "0x03"
#endif
#ifndef ASL_F81804_FAN_SENSOR_NUMBER
    #define ASL_F81804_FAN_SENSOR_NUMBER "0x03"
#endif
#ifndef ASL_F81804_VOLT_SENSOR_NUMBER
    #define ASL_F81804_VOLT_SENSOR_NUMBER "0x06"
#endif
#ifndef ASL_F81804_AUXFANIN1_STRING
    #define ASL_F81804_AUXFANIN1_STRING "0x02"
#endif
#ifndef ASL_F81804_VIN1_RA
    #define ASL_F81804_VIN1_RA 150
#endif
#ifndef ASL_F81804_VIN2_RA
    #define ASL_F81804_VIN2_RA 80
#endif
#ifndef ASL_F81804_VIN1_RB
    #define ASL_F81804_VIN1_RB 10
#endif
#ifndef ASL_F81804_VIN2_RB
    #define ASL_F81804_VIN2_RB 20
#endif
#ifndef ASL_F81804_SmartFan_SUPPORT
    #define ASL_F81804_SmartFan_SUPPORT 0x01
#endif
#ifndef ASL_F81804_SMF_NUMBER
    #define ASL_F81804_SMF_NUMBER "0x02"
#endif
#ifndef ASL_F81804_SMFC_FAN1OUT
    #define ASL_F81804_SMFC_FAN1OUT "Name:FAN1,Temperature Point:4,Temperature Target:FAN1,Supported Mod:[\"Manual\",\"Linear\"]}"
#endif
#ifndef ASL_F81804_SMFC_FAN2OUT
    #define ASL_F81804_SMFC_FAN2OUT "Name:FAN3,Temperature Point:4,Temperature Target:FAN2,Supported Mod:[\"Manual\",\"Linear\"]}"
#endif
//Peter debug--Need modify
//------------------------------------------------------------------------
// Table:    TLDN
// Description:  LDN look up table for GPIO group number
//-------------------------------------------------------------------------
    Name (TLDN, Package(0x0A){
        6,  // GP0x
        6,  // GP1x
        6,  // GP2x
        ASL_BFPI_INVALID_PARAMETER,  // GP3x, not supported by F81804
        ASL_BFPI_INVALID_PARAMETER,  // GP4x, not supported by F81804
        6,  // GP5x
        6,  // GP6x
        6,  // GP7x
        ASL_BFPI_INVALID_PARAMETER,  // GP8x, not supported by F81804
        6   // GP9x
    })
//------------------------------------------------------------------------
// Procedure:    CGTL
// Description:  Convert Super I/O GPIO group number to LDN
// Input: Arg0 : Super I/O Group number
// Output: LDN
//-------------------------------------------------------------------------
    Method(CGTL, 1) {
        If (LGreater(Arg0, 0x0A))
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

        If (LEqual(local1,0))
        {
            ShiftRight(And(OPT2, local3), local2, local5)
        } ElseIf (LEqual(local1,1))
        {
            ShiftRight(And(RGE2, local3), local2, local5)
        } ElseIf (LEqual(local1,2))
        {
            ShiftRight(And(RGD2, local3), local2, local5)
        } ElseIf (LEqual(local1,5))
        {
            ShiftRight(And(RGA2, local3), local2, local5)
        } ElseIf (LEqual(local1,6))
        {
            ShiftRight(And(RG92, local3), local2, local5)
        }ElseIf (LEqual(local1,7))
        {
            ShiftRight(And(RG82, local3), local2, local5)
        }ElseIf (LEqual(local1,9))
        {
            ShiftRight(And(RG9A, local3), local2, local5)
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

         If (LEqual(local1,0))
         {
             Or (And(OPT1,Not(local3)), ShiftLeft(Arg1,local2), OPT1)
         } ElseIf (LEqual(local1,1))
         {
             Or (And(RGE1,Not(local3)), ShiftLeft(Arg1,local2), RGE1)
         } ElseIf (LEqual(local1,2))
         {
             Or (And(RGD1,Not(local3)), ShiftLeft(Arg1,local2), RGD1)
         } ElseIf (LEqual(local1,5))
         {
             Or (And(RGA1,Not(local3)), ShiftLeft(Arg1,local2), RGA1)
         } ElseIf (LEqual(local1,6))
         {
             Or (And(RG91,Not(local3)), ShiftLeft(Arg1,local2), RG91)
         }ElseIf (LEqual(local1,7))
         {
             Or (And(RG81,Not(local3)), ShiftLeft(Arg1,local2), RG81)
         }ElseIf (LEqual(local1,9))
         {
             Or (And(RG99,Not(local3)), ShiftLeft(Arg1,local2), RG99)
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

         If (LEqual(local1,0))
         {
             ShiftRight(And(OPT0, local3), local2, local5)
         } ElseIf (LEqual(local1,1))
         {
             ShiftRight(And(RGE0, local3), local2, local5)
         } ElseIf (LEqual(local1,2))
         {
             ShiftRight(And(RGD0, local3), local2, local5)
         } ElseIf (LEqual(local1,5))
         {
             ShiftRight(And(RGA0, local3), local2, local5)
         } ElseIf (LEqual(local1,6))
         {
             ShiftRight(And(RG90, local3), local2, local5)
         }ElseIf (LEqual(local1,7))
         {
             ShiftRight(And(RG80, local3), local2, local5)
         } ElseIf (LEqual(local1,9))
         {
             ShiftRight(And(RG98, local3), local2, local5)
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

        If (LEqual(local1,0))
        {
            Or (And(OPT0,Not(local3)), ShiftLeft(Arg1,local2), OPT0)
        } ElseIf (LEqual(local1,1))
        {
            Or (And(RGE0,Not(local3)), ShiftLeft(Arg1,local2), RGE0)
        } ElseIf (LEqual(local1,2))
        {
            Or (And(RGD0,Not(local3)), ShiftLeft(Arg1,local2), RGD0)
        } ElseIf (LEqual(local1,5))
        {
            Or (And(RGA0,Not(local3)), ShiftLeft(Arg1,local2), RGA0)
        } ElseIf (LEqual(local1,6))
        {
            Or (And(RG90,Not(local3)), ShiftLeft(Arg1,local2), RG90)
        }ElseIf (LEqual(local1,7))
        {
            Or (And(RG80,Not(local3)), ShiftLeft(Arg1,local2), RG80)
        } ElseIf (LEqual(local1,9))
        {
            Or (And(RG98,Not(local3)), ShiftLeft(Arg1,local2), RG98)
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
//     1: Push pull 
//   ASL_BFPI_INVALID_PARAMETER
//
//---------------------------------------------------------------------------
    Method (D1GO, 1) {
         Store(And(Arg0, 0xff), local0) // local1: DIO number
         Divide (local0, 10, local2, local1)
         ShiftLeft(0x01, local2, local3) //pin bitmask
         If (LEqual(local1, 0x02)) //GP2x not support Drive Enable
        { Return (ASL_BFPI_INVALID_PARAMETER) }
         Store (CGTL(local1), local4)
        // local1 : Result : Super I/O Group number
        // local2 : Remainder : Pin number in group 
        // local3 : Pin bit map
        // local4 : GPIO LDN
        If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(local4)        //Enter Config Mode, Select GPIO LDN
        If (LEqual(local1,0))
         {
             ShiftRight(And(OPT3, local3), local2, local5)
         } ElseIf (LEqual(local1,1))
         {
             ShiftRight(And(RGE3, local3), local2, local5)
         } ElseIf (LEqual(local1,5))
         {
             ShiftRight(And(RGA3, local3), local2, local5)
         } ElseIf (LEqual(local1,6))
         {
             ShiftRight(And(RG93, local3), local2, local5)
         }ElseIf (LEqual(local1,7))
         {
             ShiftRight(And(RG83, local3), local2, local5)
         } ElseIf (LEqual(local1,9))
         {
             ShiftRight(And(RG9B, local3), local2, local5)
         }

         EXFG()        // Exit Config Mode

         Return (local5)
    }

//---------------------------------------------------------------------------
// Name: D1SO
//
// Description:  OEM GPIO Set Driving
//   Arg0 : GPIO Number to set Driving
//   Arg1 : Driving to set
//     0: Open drain
//     1: Push pull 
//
// Output:
//   BFPI_STATUS
//
//---------------------------------------------------------------------------
    Method (D1SO, 2){
         Store(And(Arg0, 0xff), local0) // local1: DIO number
         Divide (local0, 10, local2, local1)
         ShiftLeft(0x01, local2, local3) //pin bitmask
         If (LEqual(local1, 0x02)) //GP2x not support Drive Enable
        { Return (ASL_BFPI_INVALID_PARAMETER) }
         Store (CGTL(local1), local4)
        // local1 : Result : Super I/O Group number
        // local2 : Remainder : Pin number in group 
        // local3 : Pin bit map
        // local4 : GPIO LDN
        If (LEqual(local4, ASL_BFPI_INVALID_PARAMETER))
        { Return (ASL_BFPI_INVALID_PARAMETER) }

        ENFG(local4)        //Enter Config Mode, Select GPIO LDN
        If (LEqual(local1,0))
        {
            Or (And(OPT3,Not(local3)), ShiftLeft(Arg1,local2), OPT3)
        } ElseIf (LEqual(local1,1))
        {
            Or (And(RGE3,Not(local3)), ShiftLeft(Arg1,local2), RGE3)
        } ElseIf (LEqual(local1,5))
        {
            Or (And(RGA3,Not(local3)), ShiftLeft(Arg1,local2), RGA3)
        } ElseIf (LEqual(local1,6))
        {
            Or (And(RG93,Not(local3)), ShiftLeft(Arg1,local2), RG93)
        }ElseIf (LEqual(local1,7))
        {
            Or (And(RG83,Not(local3)), ShiftLeft(Arg1,local2), RG83)
        } ElseIf (LEqual(local1,9))
        {
            Or (And(RG9B,Not(local3)), ShiftLeft(Arg1,local2), RG9B)
        }

        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }

#if  ASL_F81804_WDT_PRESENT
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
        ENFG(7)        //Enter Config Mode, Select WDT LDN
        Store (OPT6, local0)
        Store (OPT5, local1)
        // local0 : Time of watchdog timer (0~255)
        // local1 : BIT3 Select time unit (0: 1sec, 1: 60 sec)
        EXFG()        // Exit Config Mode
        If (LEqual(And(ShiftRight(local1,3),1), 1)) 
        {
         Multiply (local0, 60000, local0)  // Multiply with 60000 to report value in ms
        }
        Else
        {
        Multiply (local0, 1000, local0)  // Multiply with 1000 to report value in ms
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
        ENFG(ASL_F81804_LDN_WDT)        //Enter Config Mode, Select WDT LDN
        If (LEqual(Arg0, 0))
        {
            And (OPT5, 0xDF, OPT5) // Stop WDT
            Return (ASL_BFPI_SUCCESS) 
        }
        If (LGreater(Arg0, 0))
        {
            Divide (Arg0, 1000, local1, local0)
            //Divide (Dividend, Divisor, Remainder, Result)
            // Convert ms to sec
            // local0 : time-out in second
            // local1 : time-out remainder in ms

            If (LGreater(local0, 255))
            {
                Or (local2, 0x08, local2)  // BIT3 = 1 : 60 sec mode
                Divide (local0, 60, local1, local0)
                If (LGreater(local1,0)) { 
                    Increment(local0)
                }
            }
        }

        // Set to SIO

        Or (And(OPT5,0xDF), 0x00, OPT5) // Stop WDT before changing counting mode
        Or (And(OPT5,0xF7), local2, OPT5)  // Set counting mode
        Store (local0, OPT6)  // Set counter
        Or (And(OPT5,0xDF), 0x20, OPT5)// Enabled WDT
        EXFG()        // Exit Config Mode

        Return (ASL_BFPI_SUCCESS)
    }
#endif  ASL_F81804_WDT_PRESENT

#if  ASL_F81804_HWM_PRESENT
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
            Store (ASL_F81804_TEMP_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            Store (ASL_F81804_FAN_SENSOR_NUMBER, Local0)
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            Store (ASL_F81804_VOLT_SENSOR_NUMBER, Local0)
        }
        Return (Local0)
    }
//------------------------------------------------------------------------
// Table:    THTS
// Description:  Look up table for HWM thermal sensor's name string
//-------------------------------------------------------------------------
Name(THTS, Package() {
#if ASL_F81804_TEMPERATURE_1_SUPPORT
    ASL_F81804_TEMPERATURE_1_STRING,
#endif
#if ASL_F81804_TEMPERATURE_2_SUPPORT
    ASL_F81804_TEMPERATURE_2_STRING,
#endif
#if ASL_F81804_TEMPERATURE_3_SUPPORT
    ASL_F81804_TEMPERATURE_3_STRING,
#endif
})

//------------------------------------------------------------------------
// Table:    THFS
// Description:  Look up table for HWM FAN sensor's name string
//-------------------------------------------------------------------------
Name(THFS, Package() {
#if ASL_F81804_TEMPERATURE_1_SUPPORT
    ASL_F81804_TEMPERATURE_1_STRING,
#endif
#if ASL_F81804_TEMPERATURE_2_SUPPORT
    ASL_F81804_TEMPERATURE_2_STRING,
#endif
#if ASL_F81804_TEMPERATURE_3_SUPPORT
    ASL_F81804_TEMPERATURE_3_STRING,
#endif

})

//------------------------------------------------------------------------
// Table:    THVS
// Description:  Look up table for HWM voltage sensor's name string
//-------------------------------------------------------------------------
Name(THVS, Package() {
#if ASL_F81804_VCORE_SUPPORT
    ASL_F81804_VCORE_STRING,
#endif
#if ASL_F81804_VIN0_SUPPORT
    ASL_F81804_VIN0_STRING,
#endif
#if ASL_F81804_VIN1_SUPPORT
    ASL_F81804_VIN1_STRING,
#endif
#if ASL_F81804_VIN2_SUPPORT
    ASL_F81804_VIN2_STRING,
#endif
#if ASL_F81804_VIN3_SUPPORT
    ASL_F81804_VIN3_STRING,
#endif
#if ASL_F81804_VCC3_SUPPORT
    ASL_F81804_VCC3_STRING,
#endif
#if ASL_F81804_AVCC_SUPPORT
    ASL_F81804_AVCC_STRING,
#endif
#if ASL_F81804_VSB3_SUPPORT
    ASL_F81804_VSB3_STRING,
#endif
#if ASL_F81804_VBAT_SUPPORT
    ASL_F81804_VBAT_STRING,
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

        If (LEqual(Arg0, 0)) {
            // Temperature
#if ASL_F81804_TEMPERATURE_1_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_TEMPERATURE_1_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_TEMPERATURE_2_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_TEMPERATURE_2_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_TEMPERATURE_3_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_TEMPERATURE_3_STRING, "\"", ), ), Local0)
#endif
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
#if ASL_F81804_FAN_1_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_FAN_1_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_FAN_2_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_FAN_2_STRING, "\"", ), ), Local0)
#endif
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
#if ASL_F81804_3VCC_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_3VCC_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_VIN1_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_VIN1_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_VIN2_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_VIN2_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_VSB3V_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_VSB3V_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_VBAT_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_VBAT_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_5VSB_SUPPORT
            If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
            Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_5VSB_STRING, "\"", ), ), Local0)
#endif
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
        If (LEqual(Arg0, 0xFFFF)) { Return (0) }
        If (LEqual(Arg0, 0x0FFF)) { Return (0) }
        If (LEqual(Arg0, 0)) { Return (0) }

        
        // Speed = 15000000/count;
        Divide (1500000, Arg0, , Local0)
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
//   Refer to F81804ExternalFunList in F81804HwmSetup.c.
//---------------------------------------------------------------------------
    Method (H1RS, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        If (LEqual(Arg0, 0)) {
            // Temperature
            If (LEqual(Arg1, ASL_F81804_TEMPERATURE_1_STRING)) {  // TEMP1 - Temperature 1
                Store (HW72, local0)
                Store (HCVT (local0, 0), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_TEMPERATURE_2_STRING)) {  // TEMP2 - Temperature 2
                Store (HW74, local0)
                Store (HCVT (local0, 0), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_TEMPERATURE_3_STRING)) {  // TEMP3 - Temperature 3 (CPU PECI)
                Store (HW7E, local0)
                Store (HCVT (local0, 0), local0)
            }
        } ElseIf (LEqual(Arg0, 1)) {
            // Fan
            If (LEqual(Arg1, ASL_F81804_FAN_1_STRING)) {  // FAN1
                ShiftLeft(HWA0,8,local0) //FAN1 count reading (MSB)
                store (HWA1, local1)     //FAN1 count reading (LSB)
                Or(local0,local1,local2) //FAN1 count
                Store (HCVF (local2, local1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_FAN_2_STRING)) {  // FAN2
                ShiftLeft(HWC0,8,local0) //FAN2 count reading (MSB)
                store (HWC1, local1)     //FAN2 count reading (LSB)
                Or(local0,local1,local2) //FAN2 count
                Store (HCVF (local2, local1), local0)
            }
        } ElseIf (LEqual(Arg0, 2)) {
            // Voltage
            If (LEqual(Arg1, ASL_F81804_3VCC_STRING)) {  // 3VCC
                Store (HW20, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_VIN1_STRING)) {  // VIN1
                Store (HW21, local0)
                Store( HCVV (local0, ASL_F81804_VIN1_RA, ASL_F81804_VIN1_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_VIN2_STRING)) {  // VIN2
                Store (HW22, local0)
                Store( HCVV (local0, ASL_F81804_VIN2_RA, ASL_F81804_VIN2_RB), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_VSB3V_STRING)) {  // VSB3V
                Store (HW25, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_VBAT_STRING)) {  // VBAT
                Store (HW26, local0)
                Store( HCVV (local0, 1, 1), local0)
            }
            ElseIf (LEqual(Arg1, ASL_F81804_5VSB_STRING)) {  // 5VSB
                Store (HW27, local0)
                Store( HCVV (local0, 2, 1), local0)
            }
        }
        Return (local0)
    }
#endif  //ASL_F81804_HWM_PRESENT

#if ASL_F81804_SmartFan_SUPPORT
//------------------------------------------------------------------------
// Table:    THFC
// Description:  Look up table for FAN controller's name string
//-------------------------------------------------------------------------
Name(THFC, Package() {
#if ASL_F81804_FAN_1_SUPPORT
    ASL_F81804_FAN_1_STRING,
#endif
#if ASL_F81804_FAN_2_SUPPORT
    ASL_F81804_FAN_2_STRING,
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
        Return (ASL_F81804_SMF_NUMBER)
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

        // Return a list of FAN names that supported Smart FAN from this SOP, seperated by comma.
#if ASL_F81804_FAN_1_SUPPORT
        If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_FAN_1_STRING, "\"", ), ), Local0)
#endif
#if ASL_F81804_FAN_2_SUPPORT
        If (LEqual(local1, ZERO)) { Concatenate (Local0, ",", Local0) } Else { Decrement(Local1) }  // Start to append comma from secondary.
        Concatenate (Local0, Concatenate ("\"", Concatenate (ASL_F81804_FAN_2_STRING, "\"", ), ), Local0)
#endif
        Return (local0)
    }

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
    If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) {
        Store (DerefOf(Index(TSEL, And(HWAF,0x03))), Local0)
    }
#if ASL_F81804_SMF2_SUPPORT && ASL_F81804_FAN_2_SUPPORT
    ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
        Store (DerefOf(Index(TSEL, And(HWCF,0x03))), Local0)
    }
#endif    
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
    If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
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
    If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) {
    } ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
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
    Return (ASL_BFPI_NOT_SUPPORTED)  // F81804 does not support Slop-Linear mode
}
//------------------------------------------------------------------------
// Table:    TSEL
// Description: Select the temperature source for controlling FAN
//-------------------------------------------------------------------------
    Name(TSEL, Package() {
        ASL_F81804_TEMPERATURE_3_STRING,
        ASL_F81804_TEMPERATURE_1_STRING,
        ASL_F81804_TEMPERATURE_2_STRING,
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
    })
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
        Store ("", local1)

#if ASL_F81804_SMF1_SUPPORT && ASL_F81804_FAN_1_SUPPORT
        If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) {
            Store (ASL_F81804_SMFC_FAN_1_PREFIX, Local0)
            // Index AFh Bit[7]: FAN1_TEMP_SEL_DIG
            // Index AFh Bit[1:0]: FAN1_TEMP_SEL
            // {FAN1_TEMP_SEL_DIG, FAN1_TEMP_SEL}
            Or(And(ShiftRight(HWAF, 5),0x04),And(HWAF,0x03),Local2)
            Store (DerefOf(Index(TSEL, Local2)), Local1)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ASL_F81804_SMFC_FANOUT_SUFFIX, Local0)
            Return (Local0)
        }
#endif
#if ASL_F81804_SMF2_SUPPORT && ASL_F81804_FAN_2_SUPPORT
        If (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
            Store (ASL_F81804_SMFC_FAN_2_PREFIX, Local0)
            // Index BFh Bit[7]: FAN2_TEMP_SEL_DIG
            // Index BFh Bit[1:0]: FAN2_TEMP_SEL
            // {FAN2_TEMP_SEL_DIG, FAN2_TEMP_SEL}
            Or(And(ShiftRight(HWCF, 5),0x04),And(HWCF,0x03),Local2)
            Store (DerefOf(Index(TSEL, Local2)), Local1)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ASL_F81804_SMFC_FANOUT_SUFFIX, Local0)
            Return (Local0)
        }
#endif
        
        Return ("NULL")
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
//       X - (X/255)% duty
//       255 - 100% duty
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//
//---------------------------------------------------------------------------
    Method (F1GM, 1){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
         If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) { //FAN1 MODE
            And(HW96, 0x03, local0)
            If (LEqual(local0,0x03)) //Check Bit[1:0]
            {
              Store (0,local0) //Manual mode
              Or (local0, ShiftLeft(HWA3, 8), local0)
            }
            Else{
              Store (1,local0) //Linear mode
              }
        }
        ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) { //FAN2 MODE
            And(HW96, 0x30, local0)
            If (LEqual(local0,0x30)) //Check Bit[5:4]
            {
              Store (0,local0) //Manual mode
              Or (local0, ShiftLeft(HWC3, 8), local0)
            }           
            Else{
              Store (1,local0) //Linear mode
              }
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
//       X - (X/255)% duty
//       255 - 100% duty
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_SUCCESS
//
//---------------------------------------------------------------------------
    Method (F1SM, 3){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
#if ASL_F81804_SMF1_SUPPORT && ASL_F81804_FAN_1_SUPPORT         
        If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) { //FAN1 MODE
            And(HW96, 0xFC, Local1)     // Index 96h Bit[1:0]: FAN1_MODE
            If (LEqual(Arg1, 0)) {
                Or(Local1, 0x03, HW96)  // Bit[1:0] = 11b : Manual mode fan control
                Store (Arg2, HWA3)      // Index A3h: FAN1 duty value
            }
            Else {
                Or(Local1, 0x01, HW96)  // Bit[1:0] = 01b : Auto fan speed control by duty cycle
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
#endif        
#if ASL_F81804_SMF2_SUPPORT && ASL_F81804_FAN_2_SUPPORT        
        ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) { //FAN2 MODE
         If (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
              And(HW96, 0xCF, Local1)     // Index 96h Bit[5:4]: FAN2_MODE
              If (LEqual(Arg1, 0)) {
                  Or(Local1, 0x30, HW96)  // Bit[5:4] = 11b: Manual mode fan control
                  Store (Arg2, HWC3)      // Index C3h: FAN2 duty value
              }
              Else {
                 Or(Local1, 0x10, HW96)  // Bit[5:4] = 01b: Auto fan speed control by duty cycle
              }
              Store (ASL_BFPI_SUCCESS, Local0)
          }
        }
#endif        
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
//       X - (X/255)% duty
//       255 - 100% duty
//     Bit[16:8]: Temperature coordinate for this pont
//       0~255
//     BFPI_NOT_SUPPORTED: No FAN matches name provided.
//
//---------------------------------------------------------------------------
    Method (F1GP, 2){
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) {//FAN1 MODE
            // FAN1 SEGMENT 1 SPEED COUNT Index AAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (HWAE, Local0) // Index AE: FAN1 SEGMENT 5 SPEED COUNT
                Or (Local0, ShiftLeft(HWA9, 8), Local0) // Index A9: FAN1 Boundary 4 Temperature
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (HWAB, Local0) // Index AB: FAN1 SEGMENT 2 SPEED COUNT
                Or (Local0, ShiftLeft(HWA6, 8), Local0) // Index A6: FAN1 Boundary 1 Temperature
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (HWAD, Local0) // Index AD: FAN1 SEGMENT 4 SPEED COUNT
                Or (Local0, ShiftLeft(HWA8, 8), Local0) // Index A8: FAN1 Boundary 3 Temperature
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (HWAC, Local0) // Index AC: FAN1 SEGMENT 3 SPEED COUNT
                Or (Local0, ShiftLeft(HWA7, 8), Local0) // Index A7: FAN1 Boundary 2 Temperature
            }
        }
        ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {//FAN2 MODE
            // FAN2 SEGMENT 1 SPEED COUNT Index CAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (HWCE, Local0) // Index CE: FAN2 SEGMENT 5 SPEED COUNT
                Or (Local0, ShiftLeft(HWC9, 8), Local0) // Index C9: FAN2 Boundary 4 Temperature
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (HWCB, Local0) // Index CB: FAN2 SEGMENT 2 SPEED COUNT
                Or (Local0, ShiftLeft(HWC6, 8), Local0) // Index C6: FAN2 Boundary 1 Temperature
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (HWCD, Local0) // Index CD: FAN2 SEGMENT 4 SPEED COUNT
                Or (Local0, ShiftLeft(HWC8, 8), Local0) // Index C8: FAN2 Boundary 3 Temperature
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (HWCC, Local0) // Index CC: FAN2 SEGMENT 3 SPEED COUNT
                Or (Local0, ShiftLeft(HWC7, 8), Local0) // Index C7: FAN2 Boundary 2 Temperature
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
//     X - (X/255)% duty
//     255 - 100% duty
//   Arg3 : Temperature coordinate for this pont
//     0~255
//
// Output:
//   BFPI_STATUS
//     BFPI_NOT_SUPPORTED : No FAN matches name provided
//     BFPI_INVALID_PARAMETER : A FAN matches name provided, but is given a wrong control point.
//     BFPI_SUCCESS
//
// Note:
//   If a control point is given with a value higher than higher control points,
//   the value should also be set to higher point. Vice versa for lower ones.
//---------------------------------------------------------------------------
    Method (F1SP, 4){
        Name (BUFF, Buffer(4) {0x0})
        Store (ASL_BFPI_NOT_SUPPORTED, local0)
        If (LEqual(Arg0, ASL_F81804_FAN_1_STRING)) { //FAN1 MODE
            // FAN1 SEGMENT 1 SPEED COUNT Index AAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (Arg3, HWA9) // Index A9: FAN1 Boundary 4 Temperature
                Store (Arg2, HWAE) // Index AE: FAN1 SEGMENT 5 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (Arg3, HWA6) // Index A6: FAN1 Boundary 1 Temperature
                Store (Arg2, HWAB) // Index AB: FAN1 SEGMENT 2 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (Arg3, HWA8) // Index A8: FAN1 Boundary 3 Temperature
                Store (Arg2, HWAD) // Index AD: FAN1 SEGMENT 4 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (Arg3, HWA7) // Index A7: FAN1 Boundary 2 Temperature
                Store (Arg2, HWAC) // Index AC: FAN1 SEGMENT 3 SPEED COUNT
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
        ElseIf (LEqual(Arg0, ASL_F81804_FAN_2_STRING)) {
            // FAN3 SEGMENT 1 SPEED COUNT Index CAh = FFh -> 100% Full speed
            If (LEqual(Arg1, 0)) {   // Lowest point
                Store (Arg3, HWC9) // Index C9: FAN2 Boundary 4 Temperature
                Store (Arg2, HWCE) // Index CE: FAN2 SEGMENT 5 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 1)) {   // Highest point
                Store (Arg3, HWC6) // Index C6: FAN2 Boundary 1 Temperature
                Store (Arg2, HWCB) // Index CB: FAN2 SEGMENT 2 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 2)) {   // Secondary low point
                Store (Arg3, HWC8) // Index C8: FAN2 Boundary 3 Temperature
                Store (Arg2, HWCD) // Index CD: FAN2 SEGMENT 4 SPEED COUNT
            }
            ElseIf (LEqual(Arg1, 3)) {   // Third low point
                Store (Arg3, HWC7) // Index C7: FAN2 Boundary 2 Temperature
                Store (Arg2, HWCC) // Index CC: FAN2 SEGMENT 3 SPEED COUNT
            }
            Store (ASL_BFPI_SUCCESS, Local0)
        }
        
        Return (local0)
    }
#endif // F81804_SmartFan_SUPPORT

//======================================================================
//Following commented line will be included in PciTree.asl 
//} //End of SIO1
//======================================================================
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

