  //Bolton Embedded Controller IR deivce
  Device(ECIR)		
    {
      Name(_HID,EISAID("AMDC003"))

      // Device Wakeup Flag
      Name(IRWF, One)	//IR wakeup flag default enable

      //LPC PCI Config Space Region
      OperationRegion(LPCS, PCI_Config, 0x00, 0x100)
      Field(LPCS, AnyAcc, NoLock, Preserve) 
        {
          offset (0xA4),
          IMCP, 16,       //IMC Port
        }

      //Operation Region for IMC index/data
      OperationRegion(ECIO, SystemIO, And(IMCP, 0xFFFE), 0x2)	
      Field(ECIO, ByteAcc, NoLock, Preserve)
        {
          INDX, 8, 
          DATA, 8
        }
    
      //IMC logical device register space
      IndexField(INDX, DATA, ByteAcc, NoLock, Preserve)	
        {
          Offset(0x7), 
          LDNM, 8, 
          Offset(0x30), 
          ACT, 1,
          Offset(0x60), 
          IOBH, 8, 
          IOBL, 8, 
          Offset(0x70), 
          INT, 4, 
        }
        
         Mutex(IRCM, 0)
         OperationRegion(IRCP, SystemIO, 0x0550, 0x02)
         Field(IRCP, ByteAcc, NoLock, Preserve)
         {
             IRCX, 8,
             IRCD, 8,
         }
         IndexField(IRCX, IRCD, ByteAcc, NoLock, Preserve)
         {
             Offset(0xAB),	//Offset(171),
             RXTX, 2,
             Offset(0xCA),	//Offset(202),
             LEDB, 1,
         }
         
      Method(CFG, 1)
        {
          Store(0x5A, INDX)
          Store(0x5A, INDX)
          Store(Arg0, LDNM)
        }

      //Method to exit config mode
      Method(XCFG)
        {
          Store(0xA5, INDX)
        }

      Mutex(ECMU, 0x0)

      //Method to return status of any logical device in EC
      Method(STA, 1)
        {
          Store(0x00, Local0)
          Acquire(ECMU, 0x5000)

          CFG(Arg0)
          If(ACT)
            {
              Store(0x0F, Local0)
            }
          If (LEqual(INDX, 0xFF)) 
            {
              Store(0x00, Local0)      
            }
          XCFG()
    
          Release(ECMU)
          Return(Local0)
        }

      Method(_STA)
        {
          Store(0x00, Local0)
          If(LGreaterEqual(\OSVR, 12))  //Windows Vista and later
            {
              Store(STA(0x05), Local0)
            }
          Return(Local0)
        }

      Name(_CRS, ResourceTemplate()
        {
          IO(Decode16, 0x550, 0x550, 0x1, 0x2)
          IRQ(Level,ActiveLow,Shared) {0x5}
        }) // (_CRS)

      Method(_DIS,0)
        {
        }

      Method(_PRW, 0)
        {
          Return(GPRW(0x1C, 4))
        }	// can wakeup from S4 state

      Method(_PSW, 1)
        {
          Store(Arg0, IRWF)
        }
      Name(IRTF, Zero)

   
      //AMD specific control method to return board related IR info             
      Method(IRCF, 2)
        {
          //Bit 0 - 7
          //Version number of silicon (Supports up to 16 version numbers).
          //For example
          // 0x39 for A11
          // 0x3A for A12
          //Bit 8 v 10(Supports up to 7 transmitters.  AMD IR device supports 2 Transmitters)
          //Number of TX ports
          //For example
          // 0 - for no emitters
          // 1 - for one emitter
          //Bit 11 v 12(Supports up to 3 receivers. AMD IR device supports 2 receivers)
          //Number of receivers
          //For example
          // 0 for no receivers
          // 1 for one receiver
          //Bit 13 v 15
          //Receiver number for Learn.
          // 0 for no learning receiver.
          // Otherwise it is the mask value of learning receiver( 3 bits to support maximum 3 receivers).
          //bit16 to represent the presence of Receiver LED on the hardware

          Store(0, Local0)
          Store(Zero, Local1)
          If (LEqual(ARG0, 0x01)) 
            {
              //Query platform configuration
                If(LNot(Acquire(IRCM, 0x5000)))
                {
                    Store(RXTX, Local1)
                    Release(IRCM)
                }
                If(Local1)
                {
                    Or(Local0, 0x00013000, Local0)
                    If(LEqual(Local1, 0x03))
                    {
                        Or(Local0, 0x0200, Local0)
                    }
                    Else
                    {
                        Or(Local0, 0x0100, Local0)
                    }
                }
            }
          If (LEqual(ARG0, 0x02))
            {
              //Emitter Jack connection info
                If(LNotEqual(IRTF, Zero))
                {
                    Store(IRTF, Local0)
                }
                Else
                {
                    If(LNot(Acquire(IRCM, 0x5000)))
                    {
                        Store(RXTX, Local0)
                        Release(IRCM)
                    }
                }
            }
          If (LEqual(ARG0, 0x03)) 
            {
                If(LNot(Acquire(IRCM, 0xFFFF)))
                {
                    If(LEqual(Arg1, Zero))
                    {
                        Store(Zero, LEDB)
                    }
                    Else
                    {
                        Store(One, LEDB)
                        Sleep(0x64)
                        Store(Zero, LEDB)
                    }
                    Release(IRCM)
                }

                If(LEqual(Arg0, 0x04))
                {
                    If(LEqual(Arg1, Zero)) {}
                    Else {}
                }
                If(LOr(LEqual(Arg0, Zero), LGreater(Arg0, 0x05)))
                {
                    Store(Ones, Local0)
                }
                Return(Local0)
            }
        }
    } //Device(ECIR)