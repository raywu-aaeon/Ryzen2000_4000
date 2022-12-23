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

/** @file CrbEcFeature.c
    This file contains code for CrbEcFeature ASL.

**/
#define LPC0 SBRG

External(AFN4, MethodObj)
External(ALIB, MethodObj)

Scope(\_SB) {

    Device(ACAD)
    {
      Name(_HID, "ACPI0003")
      Name(_PCL, Package(1) {_SB})
      Name(XX00, Buffer(0x03){})
      Name(ACDC, 0xFF)
      Method(_PSR, 0, NotSerialized)
      {
        Store(One, Local0)
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(^^PCI0.LPC0.EC0.CHSH, Local0)
            ShiftRight(Local0, 0x07, Local0)
            CreateWordField(XX00, Zero, SSZE)
            CreateByteField(XX00,0x02,ACST)
            Store(0x03, SSZE)
            If(LNotEqual(Local0, ACDC))
            {
              If(Local0)
              {
               Store(0xECAC, P80H)
               AFN4(One)
               Store(Zero, ACST)
              }
              Else
              {
               Store(0xECDC, P80H)
               AFN4(0x02)
               Store(One, ACST)
              }
            
              ALIB(One, XX00)
              Store(Local0, ACDC)
            }     
            Release(^^PCI0.LPC0.EC0.Z009)
          }
        }
        Return(Local0)
      }
      Method(_STA, 0, NotSerialized)
      {
        Return(0x0F)
      }
    }
    Device(BATT)
    {
      Name(_HID, EISAID("PNP0C0A"))
      Name(_UID, One)
      Name(_PCL, Package(1) {_SB})
      Name(PBIF, Package(13)
      {
        One, Zero, 0x125C, One, Zero, Zero, Zero, Zero, Zero, "BA-05", "1",
        "LION", ""
      })
      Name(PBIX, Package(20)
      {
        Zero, One, Zero, 0x125C, One, Zero, Zero, Zero, Zero, 0x00100000,
        Ones, Ones, 0xEA60, 0xEA60, Zero, Zero, "BA-05", "1", "LION", ""
      })
      Name(BUF8, Buffer(0x8){})
      Method(XBTP, 1, NotSerialized)
      {
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            If(LEqual(Arg0, Zero))
            {
              Store(Zero, Local0)
              Store(Zero, Local1)
            }
            Else
            {
              And(Arg0, 0xFF, Local0)
              ShiftRight(Arg0, 0x08, Local1)
              And(Local1, 0xFF, Local1)
            }
            Store(Local0, ^^PCI0.LPC0.EC0.BTPL)
            Store(Local1, ^^PCI0.LPC0.EC0.BTPH)
            Release(^^PCI0.LPC0.EC0.Z009)
          }
        }
      }
      Name(PBST, Package(4) {One, 0x0A90, 0x1000, 0x2A30})
      Name(CALB, Buffer(0x10){})
      Name(BDBG, Buffer(0x0100){})
      Method(_STA, 0, NotSerialized)
      {
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(^^PCI0.LPC0.EC0.CHSH, Local0)
            Release(^^PCI0.LPC0.EC0.Z009)
            If(And(Local0, 0x40))
            {
              Return(0x1F)
            }
            Else
            {
              Return(0x0F)
            }
          }
        }
        Return(0x1F)
      }
      Method(_BIF, 0, NotSerialized)
      {
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(^^PCI0.LPC0.EC0.LFCL, Local2)
            Store(^^PCI0.LPC0.EC0.LFCH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIF, 0x02))
            Store(^^PCI0.LPC0.EC0.DECL, Local2)
            Store(^^PCI0.LPC0.EC0.DECH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIF, One))
            Store(^^PCI0.LPC0.EC0.DEVL, Local2)
            Store(^^PCI0.LPC0.EC0.DEVH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIF, 0x04))
            Store("", Index(PBIF, 0x09))
            Store("", Index(PBIF, 0x0B))
            // ACPI specification - "10.2.2.1 _BIF (Battery Information)"
            //     >> "Model Number", "Serial Number", "Battery Type" and "OEM Information" should be in type of "String(ASCIIZ)" 
            //     >> ASCIIZ: ASCII character string terminated with a 0x00(NULL).
            // In below code, terminated sign was removed during "Store(Source, Destination)".
            // Therefore, we create an buffer(BUF8) to making sure terminated sign existed.
            //     >> Example: BDNE should be 0x00323630363044ff, but somehow it becomes 0x323630363044ff.
            //Store(^^PCI0.LPC0.EC0.BDNE, Index(PBIF, 0x09))
            Store(^^PCI0.LPC0.EC0.BDNE, BUF8)
            Store(BUF8, Index(PBIF, 0x09))
            //Store(^^PCI0.LPC0.EC0.CHTY, Index(PBIF, 0x0B))
            Store(^^PCI0.LPC0.EC0.CHTY, BUF8)
            Store(BUF8, Index(PBIF, 0x0B))
            //Store(^^PCI0.LPC0.EC0.MANU, Index(PBIF, 0x0C))
            Store(^^PCI0.LPC0.EC0.MANU, BUF8)
            Store(BUF8, Index(PBIF, 0x0C))
            Release(^^PCI0.LPC0.EC0.Z009)
          }
        }
        Return(PBIF)
      }
      Method(XBIX, 0, NotSerialized)
      {
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(^^PCI0.LPC0.EC0.LFCL, Local2)
            Store(^^PCI0.LPC0.EC0.LFCH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIX, 0x03))
            Store(^^PCI0.LPC0.EC0.DECL, Local2)
            Store(^^PCI0.LPC0.EC0.DECH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIX, 0x02))
            Store(^^PCI0.LPC0.EC0.DEVL, Local2)
            Store(^^PCI0.LPC0.EC0.DEVH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIX, 0x05))
            Store(^^PCI0.LPC0.EC0.CCTL, Local2)
            Store(^^PCI0.LPC0.EC0.CCTH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIX, 0x08))
            Store(^^PCI0.LPC0.EC0.MERL, Local2)
            Store(^^PCI0.LPC0.EC0.MERH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBIX, 0x09))
            Store("", Index(PBIX, 0x10))
            Store("", Index(PBIX, 0x12))
            Store(^^PCI0.LPC0.EC0.BDNE, Index(PBIX, 0x10))
            Store(^^PCI0.LPC0.EC0.CHTY, Index(PBIX, 0x12))
            Store(^^PCI0.LPC0.EC0.MANU, Index(PBIX, 0x13))
            Release(^^PCI0.LPC0.EC0.Z009)
          }
        }
        Return(PBIX)
      }
      Method(_BST, 0, NotSerialized)
      {
        CreateWordField(CALB, Zero, CLSZ)
        CreateByteField(CALB,0x02,BTID)
        CreateByteField(CALB,0x03,PWRU)
        CreateDWordField(CALB, 0x04, FCAP)
        CreateDWordField(CALB, 0x08, RCAP)
        CreateDWordField(CALB, 0x0C, BTVT)
        Store(0x10, CLSZ)
        Store(Zero, BTID)
        Store(Zero, PWRU)
        If(^^PCI0.LPC0.ECOK())
        {
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(Zero, Local2)
            Store(^^PCI0.LPC0.EC0.CAPL, Local2)
            Store(^^PCI0.LPC0.EC0.CAPH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBST, 0x02))
            Store(Local0, RCAP)
            Store(^^PCI0.LPC0.EC0.LFCH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Store(^^PCI0.LPC0.EC0.LFCL, Local2)
            Add(Local1, Local2, Local0)
            Store(Local0, FCAP)
            Store(^^PCI0.LPC0.EC0.BTCL, Local2)
            Store(^^PCI0.LPC0.EC0.BTCH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(^^PCI0.LPC0.EC0.BATS, Local3)
            If(LEqual(And(Local3, One), Zero))
            {
              Store(And(Not(Local0), 0x7FFF), Local0)
              Store(DerefOf(Index(PBST, Zero)), Local1)
              Store(Or(One, And(Local1, 0xFC)), Index(PBST, Zero))
            }
            Else
            {
              Store(DerefOf(Index(PBST, Zero)), Local1)
              Store(Or(0x02, And(Local1, 0xFC)), Index(PBST, Zero))
            }
            Store(Local0, Index(PBST, One))
            Store(^^PCI0.LPC0.EC0.BTVL, Local2)
            Store(^^PCI0.LPC0.EC0.BTVH, Local0)
            Multiply(Local0, 0x0100, Local1)
            Add(Local1, Local2, Local0)
            Store(Local0, Index(PBST, 0x03))
            Store(Local0, BTVT)
            Release(^^PCI0.LPC0.EC0.Z009)
          }
        }
        Return(PBST)
      }
    }
    Device(LID)
    {
      Name(_HID, EISAID("PNP0C0D"))
      Method(_LID, 0, NotSerialized)
      {
        If(^^PCI0.LPC0.ECOK())
        {
          Store(0xFF, Local0)
          If(LNot(Acquire(^^PCI0.LPC0.EC0.Z009, 0x012C)))
          {
            Store(^^PCI0.LPC0.EC0.GPO3, Local0)
            Release(^^PCI0.LPC0.EC0.Z009)
          }
          If(And(Local0, 0x08))
          {
            Return(One)
          }
          Else
          {
            Return(Zero)
          }
        }
        Return(One)
      }
    }

} //### END ### Scope(\_SB) {
    
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
