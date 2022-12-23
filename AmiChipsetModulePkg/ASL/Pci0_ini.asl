
#define GPIC PICM //  rename reference bios name to AMI name

	//
	// The follwoing ASL refer to RavenPI0060 - RMD0060D.FD 
	//

	Name(OSTB, Ones)
	Name(TPOS, Zero)
	Name(LINX, Zero)
	Name(OSSP, Zero)
	Method(SEQL, 2, Serialized)
	{
		Store(SizeOf(Arg0), Local0)
		Store(SizeOf(Arg1), Local1)
		If(LNotEqual(Local0, Local1))
		{
			Return(Zero)
		}
		Name(BUF0, Buffer(Local0){})
		Store(Arg0, BUF0)
		Name(BUF1, Buffer(Local0){})
		Store(Arg1, BUF1)
		Store(Zero, Local2)
		While(LLess(Local2, Local0))
		{
			Store(DerefOf(Index(BUF0, Local2)), Local3)
			Store(DerefOf(Index(BUF1, Local2)), Local4)
			If(LNotEqual(Local3, Local4))
			{
				Return(Zero)
			}
			Increment(Local2)
		}
		Return(One)
	}
	Method(OSTP, 0, NotSerialized)
	{
		If(LEqual(OSTB, Ones))
		{
			If(CondRefOf(\_OSI, Local0))
			{
				Store(Zero, OSTB)
				Store(Zero, TPOS)
				If(_OSI("Windows 2001"))
				{
					Store(0x08, OSTB)
					Store(0x08, TPOS)
				}
				If(_OSI("Windows 2001.1"))
				{
					Store(0x20, OSTB)
					Store(0x20, TPOS)
				}
				If(_OSI("Windows 2001 SP1"))
				{
					Store(0x10, OSTB)
					Store(0x10, TPOS)
				}
				If(_OSI("Windows 2001 SP2"))
				{
					Store(0x11, OSTB)
					Store(0x11, TPOS)
				}
				If(_OSI("Windows 2001 SP3"))
				{
					Store(0x12, OSTB)
					Store(0x12, TPOS)
				}
				If(_OSI("Windows 2006"))
				{
					Store(0x40, OSTB)
					Store(0x40, TPOS)
				}
				If(_OSI("Windows 2006 SP1"))
				{
					Store(0x41, OSTB)
					Store(0x41, TPOS)
					Store(One, OSSP)
				}
				If(_OSI("Windows 2009"))
				{
					Store(One, OSSP)
					Store(0x50, OSTB)
					Store(0x50, TPOS)
				}
				If(_OSI("Windows 2012"))
				{
					Store(One, OSSP)
					Store(0x60, OSTB)
					Store(0x60, TPOS)
				}
				If(_OSI("Windows 2013"))
				{
					Store(One, OSSP)
					Store(0x61, OSTB)
					Store(0x61, TPOS)
				}
				If(_OSI("Windows 2015"))
				{
					Store(One, OSSP)
					Store(0x70, OSTB)
					Store(0x70, TPOS)
				}
/*EIP554494
			   If(_OSI("Linux"))
				{
					Store(One, LINX)
					Store(0x80, OSTB)
					Store(0x80, TPOS)
				}
*/
//EIP554494
			}
			Else
			{
				If(CondRefOf(\_OS, Local0))
				{
					If(SEQL(_OS, "Microsoft Windows"))
					{
						Store(One, OSTB)
						Store(One, TPOS)
					}
					Else
					{
						If(SEQL(_OS, "Microsoft WindowsME: Millennium Edition"))
						{
							Store(0x02, OSTB)
							Store(0x02, TPOS)
						}
						Else
						{
							If(SEQL(_OS, "Microsoft Windows NT"))
							{
								Store(0x04, OSTB)
								Store(0x04, TPOS)
							}
							Else
							{
								Store(Zero, OSTB)
								Store(Zero, TPOS)
							}
						}
					}
				}
				Else
				{
					Store(Zero, OSTB)
					Store(Zero, TPOS)
				}
			}
		}
		Return(OSTB)
	}

Scope (\_SB.PCI0) {
	Method(_INI, 0, NotSerialized)
	{
		If(LNotEqual(GPIC, Zero))
		{
			DSPI()
			//## AMI Porting ##If(\NAPC)
			//## AMI Porting ##{
				NAPE()
			//## AMI Porting ##}
		}
		OSTP()
		OSFL() // AMI Porting
	}
}
