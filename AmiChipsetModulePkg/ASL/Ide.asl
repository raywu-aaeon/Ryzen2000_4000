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

//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        Ide.asl
//
// Description: This file contains Set of ACPI Control Methods to configure IDE 
//              Controller and IDE Drives settings
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
//**********************************************************************

//**********************************************************************;
//        Device(IDE0)
//  {
//      Name(_ADR, 0xDDDDFFFF)    // Pci Device & Function number of PCI IDE controller
//
// Above PCI device and address are defined in PCItree.asl
//**********************************************************************;
           Name(UDMT, Package() {  // UDMA Timing Table
             120, 90, 60, 45, 30, 20, 15, 0     // UDMA mode 0, 1, 2, 3, 4, 5, 6
           })

           Name(PIOT, Package() {  // PIO Timing Table
             600, 390, 270, 180, 120, 0        // PIO mode 0, 1, 2, 3, 4
           })

           Name(PITR, Package() {  // PIO Timing Regsiter Setting Table
             0x99, 0x47, 0x34, 0x22, 0x20, 0x99 // PIO mode 0, 1, 2, 3, 4
           })

           Name(MDMT, Package() {  // MWDMA Timing Table
             480, 150, 120, 0                  // MWDMA mode 0, 1, 2
           })

           Name(MDTR, Package() {  // MWDMA Timing Regsiter Setting Table
             0x77, 0x21, 0x20, 0xFF            // MWDMA mode 0, 1, 2
           })

           OperationRegion(IDE, PCI_Config, 0x40, 0x20)
           Field(IDE, AnyAcc, NoLock, Preserve) {           //R01
               PPIT, 16,       // OFFSET 40h, Primary PIO Timing
               SPIT, 16,       // OFFSET 42h, Secondary PIO Timing
               PMDT, 16,       // OFFSET 44h, Primary MWDMA Timing
               SMDT, 16,       // OFFSET 46h, Secondary MWDMA Timing
               PPIC, 8,        // OFFSET 48h, Primary PIO Control
               SPIC, 8,        // OFFSET 49h, Secondary PIO Control
               PPIM, 8,        // OFFSET 4Ah, Primary PIO Mode
               SPIM, 8,        // OFFSET 4Bh, Secondary PIO Mode
               OFFSET(0x14),
               PUDC, 2,        // OFFSET 54h, Primary UDMA Control
               SUDC, 2,        // OFFSET 54h, Secondary UDMA Control
               OFFSET(0x16),
               PUDM, 8,        // OFFSET 56h, Primary UltraDMA Mode
               SUDM, 8,        // OFFSET 57h, Secondary UltraDMA Mode
           }

           Method(GETT, 1) {
               Store(And(Arg0, 0x0F), Local0)      // Recovery Width
               Store(ShiftRight(Arg0, 4), Local1)  // Command Width

               Return(Multiply(30, Add(Add(Local0, 1), Add(Local1, 1))))
           }

           Method(GTM, 1) {
               CreateByteField(Arg0, 0, PIT1)
               CreateByteField(Arg0, 1, PIT0)
               CreateByteField(Arg0, 2, MDT1)
               CreateByteField(Arg0, 3, MDT0)
               CreateByteField(Arg0, 4, PICx)
               CreateByteField(Arg0, 5, UDCx)
               CreateByteField(Arg0, 6, UDMx)

               NAME(BUF, Buffer(20) {0xFF, 0xFF, 0xFF, 0xFF,
                     0xFF, 0xFF, 0xFF, 0xFF,
                     0xFF, 0xFF, 0xFF, 0xFF,
                     0xFF, 0xFF, 0xFF, 0xFF,
                     0x00, 0x00, 0x00, 0x00 })
               CreateDwordField(BUF, 0,  PIO0)
               CreateDwordField(BUF, 4,  DMA0)
               CreateDwordField(BUF, 8,  PIO1)
               CreateDwordField(BUF, 12, DMA1)
               CreateDwordField(BUF, 16, FLAG)

               If(And(PICx, 0x01))
                {
                   Return(BUF)     // Return if the current channel is disable
               }

               Store(GETT(PIT0), PIO0)
               Store(GETT(PIT1), PIO1)

               If(And(UDCx, 0x01))
               {   // It's under UDMA mode
                   Or(FLAG, 0x01, FLAG)
                   Store(DerefOf(Index(^UDMT, And(UDMx, 0x0F))), DMA0)
               }
               Else {
                   Store(GETT(MDT0), DMA0)
               }

               If(And(UDCx, 0x02))
               {   // It's under UDMA mode
                   Or(FLAG, 0x04, FLAG)
                   Store(DerefOf(Index(^UDMT, ShiftRight(UDMx, 4))), DMA1)
               }
               Else {
                   Store(GETT(MDT1), DMA1)
               }

               Or(FLAG, 0x1A, FLAG)
               Return(BUF)
           } // End of GTM

           Method(STM, 3) {
               CreateDwordField(Arg0, 0,  PIO0)
               CreateDwordField(Arg0, 4,  DMA0)
               CreateDwordField(Arg0, 8,  PIO1)
               CreateDwordField(Arg0, 12, DMA1)
               CreateDwordField(Arg0, 16, FLAG)

               NAME(BUF, Buffer(7) {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00})
               CreateByteField(BUF, 0, PIT1)
               CreateByteField(BUF, 1, PIT0)
               CreateByteField(BUF, 2, MDT1)
               CreateByteField(BUF, 3, MDT0)
               CreateByteField(BUF, 4, PIMx)
               CreateByteField(BUF, 5, UDCx)
               CreateByteField(BUF, 6, UDMx)

               Store(Match(^PIOT, MLE, PIO0, MTR, 0, 0), Local0)
               Divide(Local0, 5, Local0, )
               Store(Match(^PIOT, MLE, PIO1, MTR, 0, 0), Local1)
               Divide(Local1, 5, Local1, )
               Store(Or(ShiftLeft(Local1, 4), Local0), PIMx)

               Store(DerefOf(Index(^PITR, Local0)), PIT0)
               Store(DerefOf(Index(^PITR, Local1)), PIT1)

               If(And(FLAG, 0x01))
               {   // Drive 0 is under UDMA mode
                   Store(Match(^UDMT, MLE, DMA0, MTR, 0, 0), Local0)
                   Divide(Local0, 7, Local0, )
                   Or(UDMx, Local0, UDMx)
                   Or(UDCx, 0x01, UDCx)
               }
               Else {
                   If(LNotEqual(DMA0, 0xFFFFFFFF)) {
                       Store(Match(^MDMT, MLE, DMA0, MTR, 0, 0), Local0)
                       Store(DerefOf(Index(^MDTR, Local0)), MDT0)
                   }
               }

               If(And(FLAG, 0x04))
               {   // Drive 1 is under UDMA mode
                   Store(Match(^UDMT, MLE, DMA1, MTR, 0, 0), Local0)
                   Divide(Local0, 7, Local0, )
                   Or(UDMx, ShiftLeft(Local0, 4), UDMx)
                   Or(UDCx, 0x02, UDCx)
               }
               Else {
                   If(LNotEqual(DMA1, 0xFFFFFFFF)) {
                       Store(Match(^MDMT, MLE, DMA1, MTR, 0, 0), Local0)
                       Store(DerefOf(Index(^MDTR, Local0)), MDT1)
                   }
               }

               Return(BUF)
           } // END of STM

           Method(GTF, 2) {
               CreateByteField(Arg1, 0, MDT1)
               CreateByteField(Arg1, 1, MDT0)
               CreateByteField(Arg1, 2, PIMx)
               CreateByteField(Arg1, 3, UDCx)
               CreateByteField(Arg1, 4, UDMx)
               If(LEqual(Arg0, 0xA0)) {
                   Store(And(PIMx, 0x0F), Local0)
                   Store(MDT0, Local1)
                   And(UDCx, 0x01, Local2)
                   Store(And(UDMx, 0x0F), Local3)
               }
               Else {
                   Store(ShiftRight(PIMx, 4), Local0)
                   Store(MDT1, Local1)
                   And(UDCx, 0x02, Local2)
                   Store(ShiftRight(UDMx, 4), Local3)
               }

               Name(BUF, Buffer(21) {
                           0x03, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xEF,
                           0x03, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xEF,
// 1x7 = 0xF5 = Freeze Lock
               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF5
               })
               CreateByteField(BUF, 1, PMOD)  // PMOD = PIO Mode
               CreateByteField(BUF, 8, DMOD)  // DMOD = DMA Mode
               CreateByteField(BUF, 5,  CMDa) // CMDa = Target drive
               CreateByteField(BUF, 12, CMDb) // CMDb = Target drive
               CreateByteField(BUF, 19, CMDc) // CMDc = Target drive

               Store(Arg0, CMDa)
               Store(Arg0, CMDb)
               Store(Arg0, CMDc)

               Or(Local0, 0x08, PMOD)

               If(Local2)
               {
                   Or(Local3, 0x40, DMOD)
               }
               Else {
                   Store(Match(^MDMT, MLE, GETT(Local1), MTR, 0, 0), Local4)
                   If(LLess(Local4, 3)) {
                       Or(0x20, Local4, DMOD)
                   }
               }

               Return(BUF)
           } // End of GTF

        Device(PRID) {
        Name(_ADR, 0)   // IDE Primary Channel

        Method(_GTM) {
            NAME(BUF, Buffer(7) {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VPIT)
            CreateWordField(BUF, 2, VMDT)
            CreateByteField(BUF, 4, VPIC)
            CreateByteField(BUF, 5, VUDC)
            CreateByteField(BUF, 6, VUDM)

            Store(^^PPIT, VPIT)
            Store(^^PMDT, VMDT)
            Store(^^PPIC, VPIC)
            Store(^^PUDC, VUDC)
            Store(^^PUDM, VUDM)


            Return(GTM(BUF))
        }

        Method(_STM,3) {
            NAME(BUF, Buffer(7) {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VPIT)
            CreateWordField(BUF, 2, VMDT)
            CreateByteField(BUF, 4, VPIM)
            CreateByteField(BUF, 5, VUDC)
            CreateByteField(BUF, 6, VUDM)

            Store(STM(Arg0, Arg1, Arg2), BUF)

            Store(VPIT, ^^PPIT)
            Store(VMDT, ^^PMDT)
            Store(VPIM, ^^PPIM)
            Store(VUDC, ^^PUDC)
            Store(VUDM, ^^PUDM)

        }

        Device(P_D0) {
            Name(_ADR, 0)   // Drive 0 - Master

            Method(_GTF) {
                Name(BUF, Buffer(5) {0x00, 0x00, 0x00, 0x00, 0x00})
                CreateWordField(BUF, 0, VMDT)
                CreateByteField(BUF, 2, VPIM)
                CreateByteField(BUF, 3, VUDC)
                CreateByteField(BUF, 4, VUDM)
                Store(^^^PMDT, VMDT)
                Store(^^^PPIM, VPIM)
                Store(^^^PUDC, VUDC)
                Store(^^^PUDM, VUDM)
                Return(GTF(0xA0, BUF))
    // //-P080406           Return(GTF(0xA0, BUF))
    // //-P080406           Return(Concatenate(GTF(0xA0, BUF),FZTF))
    //          Return(Concatenate(RATA(GTF(0xA0, BUF)),FZTF))  //+P080406
                       }
            } // End of P_D0

        Device(P_D1) {
            Name(_ADR, 1)   // Drive 1 - Slave

            Method(_GTF) {
                Name(BUF, Buffer(5) {0x00, 0x00, 0x00, 0x00, 0x00})
                CreateWordField(BUF, 0, VMDT)
                CreateByteField(BUF, 2, VPIM)
                CreateByteField(BUF, 3, VUDC)
                CreateByteField(BUF, 4, VUDM)

                Store(^^^PMDT, VMDT)
                Store(^^^PPIM, VPIM)
                Store(^^^PUDC, VUDC)
                Store(^^^PUDM, VUDM)


                Return(GTF(0xB0, BUF))
    // //-P080406           Return(GTF(0xB0, BUF))
    // //-P080406           Return(Concatenate(GTF(0xB0, BUF),FZTF))
    //          Return(Concatenate(RATA(GTF(0xB0, BUF)),FZTF))  //+P080406
                }
               } // End of P_D1
        } // End of PRID

        Device(SECD) {
        Name(_ADR, 1)   // IDE Secondary Channel

        Method(_GTM) {
            NAME(BUF, Buffer(7) {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VPIT)
            CreateWordField(BUF, 2, VMDT)
            CreateByteField(BUF, 4, VPIC)
            CreateByteField(BUF, 5, VUDC)
            CreateByteField(BUF, 6, VUDM)


            Store(^^SPIT, VPIT)
            Store(^^SMDT, VMDT)
            Store(^^SPIC, VPIC)
            Store(^^SUDC, VUDC)
            Store(^^SUDM, VUDM)


            Return(GTM(BUF))
        }

        Method(_STM,3) {
            NAME(BUF, Buffer(7) {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VPIT)
            CreateWordField(BUF, 2, VMDT)
            CreateByteField(BUF, 4, VPIM)
            CreateByteField(BUF, 5, VUDC)
            CreateByteField(BUF, 6, VUDM)

            Store(STM(Arg0, Arg1, Arg2), BUF)

            Store(VPIT, ^^SPIT)
            Store(VMDT, ^^SMDT)
            Store(VPIM, ^^SPIM)
            Store(VUDC, ^^SUDC)
            Store(VUDM, ^^SUDM)

        }

        Device(S_D0) {
        Name(_ADR, 0)   // Drive 0 - Master

        Method(_GTF) {
            Name(BUF, Buffer(5) {0x00, 0x00, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VMDT)
            CreateByteField(BUF, 2, VPIM)
            CreateByteField(BUF, 3, VUDC)
            CreateByteField(BUF, 4, VUDM)

            Store(^^^SMDT, VMDT)
            Store(^^^SPIM, VPIM)
            Store(^^^SUDC, VUDC)
            Store(^^^SUDM, VUDM)

            Return(GTF(0xA0, BUF))
// //-P080406           Return(GTF(0xA0, BUF))
// //-P080406           Return(Concatenate(GTF(0xA0, BUF),FZTF))
//          Return(Concatenate(RATA(GTF(0xA0, BUF)),FZTF))  //+P080406
                   }
               } // End of S_D0

        Device(S_D1) {
        Name(_ADR, 1)   // Drive 1 - Slave

        Method(_GTF) {
            Name(BUF, Buffer(5) {0x00, 0x00, 0x00, 0x00, 0x00})
            CreateWordField(BUF, 0, VMDT)
            CreateByteField(BUF, 2, VPIM)
            CreateByteField(BUF, 3, VUDC)
            CreateByteField(BUF, 4, VUDM)

            Store(^^^SMDT, VMDT)
            Store(^^^SPIM, VPIM)
            Store(^^^SUDC, VUDC)
            Store(^^^SUDM, VUDM)

            Return(GTF(0xB0, BUF))
// //-P080406           Return(GTF(0xB0, BUF))
// //-P080406           Return(Concatenate(GTF(0xB0, BUF),FZTF))
//          Return(Concatenate(RATA(GTF(0xB0, BUF)),FZTF))  //+P080406
                   }
               } // End of S_D1
           } // End of SECD

// // Prepare ATA buffer to be returned by _GTF
//  Method(RATA, 1)
//  {
//  // Input - Arg0 Source buffer to modify
//    CreateByteField(Arg0, 0, CMDN)
//    Multiply(CMDN, 56, Local0)        // Return buffer size (bits)
//    CreateField(Arg0, 8, Local0, RETB)// Return ATA command Buffer
//
//  Store(RETB, Debug)
//  //Store(FZLK(RETB, _ADR), RETB) //(CORE0214.2+)
//  Return(RETB)
//  }
//} // end PCI IDE Conroller
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