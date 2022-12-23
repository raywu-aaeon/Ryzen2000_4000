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

//-----------------------------------------------------------------------
//      Generic PCI IRQ Link devices
//-----------------------------------------------------------------------
// Note. All Link devices are placed under \_SB scope
//-----------------------------------------------------------------------
Scope(\_SB) {

    OperationRegion(PIRQ, SystemIO, 0xC00, 0x2)
    Field(PIRQ, ByteAcc, NoLock, Preserve)
    {
            PIDX, 8,        // Index port
            PDAT, 8     // Data port
    }

    IndexField(PIDX, PDAT, ByteAcc, NoLock, Preserve)
    {
           PIRA, 8,     // INT A
           PIRB, 8,     // INT B
           PIRC, 8,     // INT C
           PIRD, 8,     // INT D
           PIRE, 8,     // INT E
           PIRF, 8,     // INT F
           PIRG, 8,     // INT G
           PIRH, 8,     // INT H
           Offset(0xC),	//Offset(12),
           SIRA, 8,
           SIRB, 8,
           SIRC, 8,
           SIRD, 8,
           PIRS, 8,     // SCI
           Offset(0x13),
           HDAD, 8,     // HD Audio
           Offset(0x17),	//Offset(23),
           SDCL, 8,
           Offset(0x1A),	//Offset(26),
           SDIO, 8,
           Offset(0x30),
           USB1, 8,
           Offset(0x34),	//Offset(52),
           USB3, 8,
           Offset(0x41),	//Offset(65),
           SATA, 8,
           Offset(0x62),	//Offset(98),
           GIOC, 8,
           Offset(0x70),	//Offset(112),
           I2C0, 8,
           I2C1, 8,
           I2C2, 8,
           I2C3, 8,
           URT0, 8,
           URT1, 8,
           Offset(0x80),//Offset(128),
           AIRA, 8,     // INT A - IO APIC
           AIRB, 8,     // INT B - IO APIC
           AIRC, 8,     // INT C - IO APIC
           AIRD, 8,     // INT D - IO APIC
           AIRE, 8,     // INT E - IO APIC
           AIRF, 8,     // INT F - IO APIC 
           AIRG, 8,     // INT G - IO APIC 
           AIRH, 8,     // INT H - IO APIC 
    }

    OperationRegion(KBDD, SystemIO, 0x64, 0x01)
    Field(KBDD, ByteAcc, NoLock, Preserve){
        PD64, 8     // Port 64h
    }

    Method(DSPI)
    {
             INTA(0x1f)
             INTB(0x1f)
             INTC(0x1f)
             INTD(0x1f)
         Store(PD64, Local1)    // dummy read status
             Store(0x1f, PIRE)
             Store(0x1f, PIRF)
             Store(0x1f, PIRG)
             Store(0x1f, PIRH)
             Store(PD64, Local1)    // dummy read status
             Store(0x10, AIRA)
             Store(0x11, AIRB)
             Store(0x12, AIRC)
             Store(0x13, AIRD)
             Store(0x14, AIRE)
             Store(0x15, AIRF)
             Store(0x16, AIRG)
             Store(0x17, AIRH)
    }

    Method(INTA,1)
    {
             Store(ARG0, PIRA)
             Store(ARG0, HDAD)
    }

    Method(INTB,1)
    {
             Store(ARG0, PIRB)
    }

    Method(INTC,1)
    {
             Store(ARG0, PIRC)
             Store(ARG0, USB1)
             Store(ARG0, USB3)
    }

    Method(INTD,1)
    {
             Store(ARG0, PIRD)
             Store(ARG0, SATA)
    }

    Name(BUFA,ResourceTemplate()
    {
            IRQ(Level, ActiveLow, Shared ) {15}
    })

    Name(IPRA,ResourceTemplate()
    {
            IRQ(Level, ActiveLow, Shared ) {5,10,11}
    })

    Name(IPRB,ResourceTemplate()
    {
            IRQ(Level, ActiveLow, Shared ) {5,10,11}
    })

    Name(IPRC,ResourceTemplate()
    {
            IRQ(Level, ActiveLow, Shared ) {5,10,11}
    })

    Name(IPRD,ResourceTemplate()
    {
            IRQ(Level, ActiveLow, Shared ) {5,10,11}
    })

    Device(LNKA)
    {
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 1)
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKA_STA
;
; Description:  PCI Irq Router device. Get device status method
;
;  Input: Nothing
;
;  Output: 0xb - LNKx enabled/present/not visible in UI
;       0x9 - LNKx disabled/present/not visible in UI
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
                Method(_STA,0) {
// Get the PIRQx status to Local0
            If(PIRA)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
        }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKA_PRS
;
; Description:  PCI Irq Router device. List of possible IRQs can be routed by Device LNKx
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
        Method(_PRS,0){
                   Return(PRSA)
        }
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKA_DIS
;
; Description:  PCI Irq Router device. Disable PIRQx routing
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/

        Method(_DIS)
        {
                 INTA(0x1f)
        }
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKA_CRS
;
; Description:  PCI Irq Router device. Return currently Programed IRQ number
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRA, IRQX)
                    Return(BUFA)
        }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKA_SRS
;
; Description:  PCI Irq Router device. Program new IRQ number to LNKx of IRQ router
;
;  Input: ARG0 = PNP Resource String to set for IRQ
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            INTA(Local0)
        }
    } // end Device LNKA

// port LNKB..LNKD similar to LNKA device
    Device(LNKB){
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 2)
                Method(_STA,0) {
            If(PIRB)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }

        Method(_PRS,0){
                   Return(PRSB)
        }

                Method(_DIS,0) {
                   INTB(0x1f)
                    }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRB, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            INTB(Local0)
        }
    }// end Device LNKB
    Device(LNKC)
    {
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 3)

                Method(_STA,0) {
            If(PIRC)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }

            Method(_PRS,0){
                   Return(PRSC)
        }

                Method(_DIS,0) {
                   INTC(0x1f)
                    }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRC, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            INTC(Local0)
        }

    }// end Device LNKC

    Device(LNKD){
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 4)
                Method(_STA,0) {
            If(PIRD)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }
        Method(_PRS,0){
                   Return(PRSD)
        }

                Method(_DIS,0) {
                   INTD(0x1f)
                }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRD, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            INTD(Local0)
        }

    }// end Device LNKD

    Device(LNKE)
    {
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 5)
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKE_STA
;
; Description:  PCI Irq Router device. Get device status method
;
;  Input: Nothing
;
;  Output: 0xb - LNKx enabled/present/not visible in UI
;       0x9 - LNKx disabled/present/not visible in UI
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
                Method(_STA,0) {
// Get the PIRQx status to Local0
            If(PIRE)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
        }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKE_PRS
;
; Description:  PCI Irq Router device. List of possible IRQs can be routed by Device LNKx
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
        Method(_PRS,0){
                   Return(PRSE)
        }
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKE_DIS
;
; Description:  PCI Irq Router device. Disable PIRQx routing
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/

        Method(_DIS)
        {
                 Store(0x1f, PIRE)
        }
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKE_CRS
;
; Description:  PCI Irq Router device. Return currently Programed IRQ number
;
;  Input: Nothing
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRE, IRQX)
                    Return(BUFA)
        }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    LNKE_SRS
;
; Description:  PCI Irq Router device. Program new IRQ number to LNKx of IRQ router
;
;  Input: ARG0 = PNP Resource String to set for IRQ
;
;  Output: Buffer
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(PIRE, Local0)
            Decrement(Local0)
            Store(Local0, PIRE)
        }
    } // end Device LNKE

// port LNKB..LNKD similar to LNKA device
    Device(LNKF){
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 6)
                Method(_STA,0) {
            If(PIRF)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }

        Method(_PRS,0){
                   Return(PRSF)
        }

                Method(_DIS,0) {
                   Store(0x1f, PIRF)
                    }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRF, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            Store(Local0, PIRF)
        }
    }// end Device LNKF
    Device(LNKG)
    {
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 7)

                Method(_STA,0) {
            If(PIRG)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }

            Method(_PRS,0){
                   Return(PRSG)
        }

                Method(_DIS,0) {
                   Store(0x1f, PIRG)
                    }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRG, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            Store(Local0, PIRG)
        }

    }// end Device LNKG

    Device(LNKH){
                Name(_HID, EISAID("PNP0C0F"))
                Name(_UID, 8)
                Method(_STA,0) {
            If(PIRH)
                {Return (0xb)} // LNKx enabled
                Else
                {Return (0x9)} // LNKx disabled/present/not visible in UI
                }
        Method(_PRS,0){
                   Return(PRSH)
        }

                Method(_DIS,0) {
                   Store(0x1f, PIRH)
                }

            Method(_CRS,0){
                    CreateWordField(BUFA, 0x1, IRQX)
                    ShiftLeft(1, PIRH, IRQX)
                    Return(BUFA)
        }

        Method(_SRS, 1)
        {
            // ARG0 = PnP Resource String
            CreateWordField(ARG0, 0x01, IRA)    // IRQ Low Mask
            FindSetRightBit(IRA, Local0)
            Decrement(Local0)
            Store(Local0, PIRH)
        }

    }// end Device LNKH

// add LNKx devices if required by Hardware design
} // end _SB scope

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