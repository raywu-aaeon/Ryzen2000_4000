//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CrbEc.c
    This file contains code for CrbEc ASL.

**/
  
Scope(\_SB.PCI0.SBRG) {


        Method(ECOK, 0, NotSerialized)
        {
          If(LEqual(^EC0.OKEC, One))
          {
            Return(One)
          }
          Else
          {
            Return(Zero)
          }
        }
        Device(EC0)
        {
          Name(_HID, EISAID("PNP0C09"))
#if defined( ASL_CRB_MODERN_STANDBY_SUPPORT ) && (ASL_CRB_MODERN_STANDBY_SUPPORT == 1)          
          Name(XGPE, 0x03)
#else
          Name(_GPE, 0x03)
#endif          
          Method(_STA, 0, NotSerialized)
          {
            Return(0x0F)
          }
          Name(OKEC, Zero)
          Method(_CRS, 0, NotSerialized)
          {
            Name(BUF0, ResourceTemplate()
            {
              IO(Decode16, 0x0662, 0x0662, 0x01, 0x01)
              IO(Decode16, 0x0666, 0x0666, 0x01, 0x01)
            })
            Name(BUF1, ResourceTemplate()
            {
              IO(Decode16, 0x0662, 0x0662, 0x01, 0x01)
              IO(Decode16, 0x0666, 0x0666, 0x01, 0x01)
              GpioInt(Edge, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
              {
                  0x0016
              }
            })
            Name(BUF2, ResourceTemplate()
            {
              IO(Decode16, 0x0662, 0x0662, 0x01, 0x01)
              IO(Decode16, 0x0666, 0x0666, 0x01, 0x01)
              GpioInt(Edge, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
              {
                  0x0056
              }
            })
            
            If(LEqual(RDHW, Zero))
            {
              Return(BUF0)
            }
            Else
            {            
              If(EMME)
              {
                Return(BUF2)
              }
              Return(BUF1)
            }
          }
          Method(_REG, 2, NotSerialized)
          {
            If(LEqual(Arg0, 0x03))
            {
              If(LNot(Acquire(Z009, 0x012C)))
              {            
                Store(STAS, Local0)
                Or(Local0, 0x04, Local1)
                Store(Local1, STAS)
                Release(Z009)
              }
              Store(Arg1, OKEC)
              Notify(ACAD, 0x80)
              Notify(BATT, 0x80)
              Notify(BATT, 0x81)
              Notify(LID, 0x80)
              If(OKEC) {}
            }
          }
          Mutex(Z009, 0)
          Mutex(QEVT, 0)
          OperationRegion(ERAM, EmbeddedControl, Zero, 0xFF)
          Field(ERAM, ByteAcc, NoLock, Preserve)
          {
            Offset(0x60), //Offset(96),
            VERS, 16,
            Offset(0x64), //Offset(100),
            CCI, 32,
            CTRL, 64,
            MSGI, 128,
            MSGO, 128,
            PMC0, 8,
            PMC1, 8,
            PMC2, 8,
            BDNE, 64,
            CHTY, 64,
            MANU, 64,
            , 8,
            GPO2, 8,
            GPO3, 8,
            GPO4, 8,
            GPO5, 8,
            GPO6, 8,
            GPO7, 8,
            GPO8, 8,
            GPO9, 8,
            Offset(0xB6), //Offset(182),
            SW01, 8,
            SW02, 8,
            , 8,
            VERL, 40,
            Offset(0xC2), //Offset(194),
            ECRV, 40,
            DCTM, 8,
            ACTM, 8,
            BTPL, 8,
            BTPH, 8,
            MERL, 8,
            MERH, 8,
            CCTL, 8,
            CCTH, 8,
            STAS, 8,
            Offset(0xE0),  //Offset(224),
            WKTR, 16,
            S5TR, 16,
            AS4F, 8,
            , 8,
            MDEC, 8,
            MINT, 8,
            Offset(0xEA),  //Offset(234),
            LUXR, 16,
            BRTL, 8,
            BATS, 8,
            CAPL, 8,
            CAPH, 8,
            BTVL, 8,
            BTVH, 8,
            BTCL, 8,
            BTCH, 8,
            DECL, 8,
            DECH, 8,
            DEVL, 8,
            DEVH, 8,
            LFCL, 8,
            LFCH, 8,
            CHSH, 8,
          }
          Method(_Q26, 0, NotSerialized)
          {
            Store(0xEC26, P80H)
            Notify(LID, 0x80)
          }
          
          Method(_Q27, 0, NotSerialized)
          {
            Store(0xEC27, P80H)
            Notify(LID, 0x80)
          }
          
          Method(_Q35, 0, NotSerialized)
          {
            Store(0xEC35, P80H)
            If(LNot(Acquire(QEVT, 0x012C)))
            {
              Notify(ACAD, 0x80)
              Notify(BATT, 0x80)
              Release(QEVT)
            }
          }
          
          Method(_Q39, 0, NotSerialized)
          {
            Store(0xEC39, P80H)
            If(LNot(Acquire(QEVT, 0x012C)))
            {
              Notify(ACAD, 0x80)
              Notify(BATT, 0x80)
              Notify(BATT, 0x81)
              Release(QEVT)
            }
          }

          Method(_Q3E, 0, NotSerialized)
          {
             Store(0xEC3E, P80H)
             If(LNot(Acquire(Z009, 0x012C)))
              {
                 Store(BATS, Local0)
                 Or(Local0, 0x80, Local0)
                 Store(Local0, BATS)
                 Release(Z009)
              }
              If(LNot(Acquire(QEVT, 0x012C)))
              {
                 Notify(BATT, 0x80)
                 Release(QEVT)
              }
          }
          Method(_Q45, 0, NotSerialized)
          {
            Store(0xEC45, P80H)
            Notify (BATT, 0x80) // Status Change
            
          }
          Name(DPTI, Buffer(0x07){})
          Method(_Q49, 0, NotSerialized)
          {
            Store(0xEC49, P80H)
            // As default value of CPM setup item "AmdDptcControl"
            // disable following code first.
            If(LEqual(DPTC, One))
            {
              CreateWordField(DPTI, Zero, SSZE)
              CreateByteField(DPTI,0x02,MSID)
              CreateByteField(DPTI,0x03,DECI)
              CreateByteField(DPTI,0x04,INTE)
              CreateByteField(DPTI,0x05,EP00)
              CreateByteField(DPTI,0x06,EP01)
              Store(0x07, SSZE)
              Store(0x0A, MSID)
              Store(Zero, EP00)
              Store(Zero, EP01)
              If(LNot(Acquire(Z009, 0x012C)))
              {
                 Store(MDEC, DECI)
                 Store(MINT, INTE)
                 ALIB(0x0C, DPTI)
                 Release(Z009)
              }
            }
          }
        }

} //### END ### Scope(\_SB.PCI0.SBRG) {
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
