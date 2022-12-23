	// I2C MITT/WITT ASL code
	Scope(_SB.I2CA)
	{
		Device(WTP1)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK0001")
			Name(_CID, "SPBTestKMDF")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x007F, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MTP1)
		{
			Name(_HID, "STK0001")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB_.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WTP2)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK0002")
			Name(_CID, "SPBTestKMDF")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MTP2)
		{
			Name(_HID, "STK0002")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB_.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WTP3)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK0003")
			Name(_CID, "SPBTestKMDF")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MTP3)
		{
			Name(_HID, "STK0003")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB_.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WTP4)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK0004")
			Name(_CID, "SPBTestKMDF")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MTP4)
		{
			Name(_HID, "STK0004")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0014, ControllerInitiated, 0x000222E0, AddressingMode7Bit, "\\_SB_.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MTP5)
		{
			Name(_HID, "STK0005")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0015, ControllerInitiated, 0x00053020, AddressingMode7Bit, "\\_SB_.I2CA", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CB)
	{
		Device(WT21)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00012")
			Name(_CID, "SPBTestKMDF2")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x007F, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT21)
		{
			Name(_HID, "STK00012")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB_.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT22)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00022")
			Name(_CID, "SPBTestKMDF2")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT22)
		{
			Name(_HID, "STK00022")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB_.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT23)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00032")
			Name(_CID, "SPBTestKMDF2")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT23)
		{
			Name(_HID, "STK00032")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB_.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT24)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00042")
			Name(_CID, "SPBTestKMDF2")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT24)
		{
			Name(_HID, "STK00042")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0014, ControllerInitiated, 0x000222E0, AddressingMode7Bit, "\\_SB_.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT25)
		{
			Name(_HID, "STK00052")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0015, ControllerInitiated, 0x00053020, AddressingMode7Bit, "\\_SB_.I2CB", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CC)
	{
		Device(WT31)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00013")
			Name(_CID, "SPBTestKMDF3")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x007F, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT31)
		{
			Name(_HID, "STK00013")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB_.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT32)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00023")
			Name(_CID, "SPBTestKMDF3")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT32)
		{
			Name(_HID, "STK00023")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB_.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT33)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00033")
			Name(_CID, "SPBTestKMDF3")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT33)
		{
			Name(_HID, "STK00033")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB_.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT34)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00043")
			Name(_CID, "SPBTestKMDF3")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT34)
		{
			Name(_HID, "STK00043")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0014, ControllerInitiated, 0x000222E0, AddressingMode7Bit, "\\_SB_.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT35)
		{
			Name(_HID, "STK00053")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0015, ControllerInitiated, 0x00053020, AddressingMode7Bit, "\\_SB_.I2CC", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CD)
	{
		Device(WT41)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00014")
			Name(_CID, "SPBTestKMDF4")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x007F, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT41)
		{
			Name(_HID, "STK00014")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB_.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT42)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00024")
			Name(_CID, "SPBTestKMDF4")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0011, ControllerInitiated, 0x000186A0, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT42)
		{
			Name(_HID, "STK00024")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB_.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT43)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00034")
			Name(_CID, "SPBTestKMDF4")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0012, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT43)
		{
			Name(_HID, "STK00034")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB_.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(WT44)
		{
			Name(_ADR, Zero)
			Name(_HID, "STK00044")
			Name(_CID, "SPBTestKMDF4")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0013, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, One))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT44)
		{
			Name(_HID, "STK00044")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0014, ControllerInitiated, 0x000222E0, AddressingMode7Bit, "\\_SB_.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
		Device(MT45)
		{
			Name(_HID, "STK00054")
			Name(_CID, "WITTTest")
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0015, ControllerInitiated, 0x00053020, AddressingMode7Bit, "\\_SB_.I2CD", 0x00, ResourceConsumer,,)
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(LEqual(MWTT, Zero))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}

    // I2C NFC ASL code
    Scope(_SB.I2CA)
	{
		Device(NFC1)
		{
			Name(_HID, EISAID("NXP8013"))
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0029, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveHigh, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0045
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0089
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x008A
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(NFCS, One)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CB)
	{
		Device(NFC1)
		{
			Name(_HID, EISAID("NXP8013"))
			Name(_UID, 0x02)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0029, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveHigh, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0045
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0089
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x008A
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(NFCS, 0x02)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CC)
	{
		Device(NFC1)
		{
			Name(_HID, EISAID("NXP8013"))
			Name(_UID, 0x03)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0029, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveHigh, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0045
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0089
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x008A
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(NFCS, 0x03)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
	Scope(_SB.I2CD)
	{
		Device(NFC1)
		{
			Name(_HID, EISAID("NXP8013"))
			Name(_UID, 0x04)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0029, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveHigh, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0045
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0089
					}
					GpioIo(Exclusive, PullNone, 0x0000, 0x0000, IoRestrictionOutputOnly, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x008A
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(NFCS, 0x04)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
		}
	}
    
	
	// I2C touch panel ASL code
	Scope(_SB.I2CA)
	{
		Device(TPNL)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x004A, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Shared, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, One)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(Zero)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
		Device(ELAN)
		{
			Name(_HID, "04F31234")
			Name(_CID, "PNP0C50")
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Exclusive, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x05)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(One)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	Scope(_SB.I2CB)
	{
		Device(TPNL)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x02)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x004A, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Shared, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x02)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(Zero)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
		Device(ELAN)
		{
			Name(_HID, "04F31234")
			Name(_CID, "PNP0C50")
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Exclusive, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x06)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(One)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	Scope(_SB.I2CC)
	{
		Device(TPNL)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x03)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x004A, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Shared, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x03)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(Zero)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
		Device(ELAN)
		{
			Name(_HID, "04F31234")
			Name(_CID, "PNP0C50")
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Exclusive, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x07)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(One)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	
	Scope(_SB.I2CD)
	{
		Device(TPNL)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x04)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x004A, ControllerInitiated, 0x000F4240, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Shared, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x04)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(Zero)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
		Device(ELAN)
		{
			Name(_HID, "04F31234")
			Name(_CID, "PNP0C50")
			Name(_UID, One)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, Exclusive, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x000C
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPN, 0x08)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(One)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	
	// I2C touch pad ASL code
	Scope(_SB.I2CA)
	{
		Device(TPDD)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x05)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0020, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0009
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPD, One)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(0x20)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	Scope(_SB.I2CB)
	{
		Device(TPDD)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x06)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0020, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0009
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPD, 0x02)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(0x20)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	Scope(_SB.I2CC)
	{
		Device(TPDD)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x07)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0020, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0009
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPD, 0x03)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(0x20)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	Scope(_SB.I2CD)
	{
		Device(TPDD)
		{
			Name(_HID, EISAID("PNP0C50"))
			Name(_CID, "PNP0C50")
			Name(_UID, 0x08)
			Method(_CRS, 0, NotSerialized)
			{
				Name(RBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0020, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0009
					}
				})
				Return(RBUF)
			}
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(THPD, 0x04)))
				{
					Return(0x0F)
				}
				Else
				{
					Return(Zero)
				}
			}
			Method(_DSW, 3, NotSerialized)
			{
				If(Arg0) {}
				Else {}
			}
			Method(_PS0, 0, NotSerialized)
			{
			}
			Method(_PS3, 0, NotSerialized)
			{
			}
			Method(_DSM, 4, Serialized)
			{
				Name(_T_1, Zero)
				Name(_T_0, Zero)
				//If(LEqual(Arg0, ToUUID("3CDFF6F7-42674555-AD05B30A3D8938DE")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xF7, 0xF6, 0xDF, 0x3C, 0x67, 0x42, 0x55, 0x45,
            		/* 0008 */   0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE
        		}))
				{
					While(One)
					{
						Store(ToInteger(Arg2), _T_0)
						If(LEqual(_T_0, Zero))
						{
							While(One)
							{
								Store(ToInteger(Arg1), _T_1)
								If(LEqual(_T_1, One))
								{
									Return(Buffer(One)
									{
										0x03
									})
								}
								Else
								{
									Return(Buffer(One)
									{
										0x00
									})
								}
								Break
							}
						}
						Else
						{
							If(LEqual(_T_0, One))
							{
								Return(0x20)
							}
							Else
							{
								Return(Zero)
							}
						}
						Break
					}
				}
				Else
				{
					Return(Buffer(One)
					{
						0x00
					})
				}
			}
		}
	}
	
	// I2C ALST ASL code
		Scope(_SB.I2CA)
	{
		Device(CMSR)
		{
			Name(_ADR, Zero)
			Name(_HID, "CPLM3218")
			Name(_CID, "CPLM3218")
			Name(_UID, One)
			Name(_DEP, Package(1) {I2CA})
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(ALST, One)))
				{
					Return(0x0F)
				}
				Return(Zero)
			}
			Method(_CRS, 0, NotSerialized)
			{
				Name(SBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CA", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0018
					}
				})
				Return(SBUF)
			}
			Name(CPM0, Package(7) {0x7DB5, One, 0x0F, 0x0840, 0x013B, 0x011D, Zero})
			Name(CPM1, Package(3) {0x0898, 0x000186A0, 0x000186A0})
			Name(CPM2, Package(6) {0x61A8, 0x000186A0, 0x000186A0, 0x000186A0, 0x00030D40, 0x00186A00})
			Name(CPM3, Package(4)
			{
				Package(2) {0x3C, 0x0A}, 
				Package(2) {0x64, 0x0B}, 
				Package(2) {0x64, 0x1F40}, 
				Package(2) {0x01F4, 0x1F41}
			})
			Name(CPM5, Package(7) {Zero, 0x000249F0, 0x0190, 0x03E8, 0x02, 0x32, 0x05})
			Method(_DSM, 4, NotSerialized)
			{
				//If(LEqual(Arg0, ToUUID("0703C6B6-1CCA4144-9FE74654F53A0BD9")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xB6, 0xC6, 0x03, 0x07, 0xCA, 0x1C, 0x44, 0x41,
            		/* 0008 */   0x9F, 0xE7, 0x46, 0x54, 0xF5, 0x3A, 0x0B, 0xD9
        		}))
				{
					If(LEqual(Arg2, Zero))
					{
						Return(Buffer(One)
						{
							0x03
						})
					}
					If(LEqual(Arg2, One))
					{
						If(LEqual(ToInteger(Arg3), Zero))
						{
							Return(CPM0)
						}
						If(LEqual(ToInteger(Arg3), One))
						{
							Return(CPM1)
						}
						If(LEqual(ToInteger(Arg3), 0x02))
						{
							Return(CPM2)
						}
						If(LEqual(ToInteger(Arg3), 0x03))
						{
							Return(CPM3)
						}
						If(LEqual(ToInteger(Arg3), 0x05))
						{
							Return(CPM5)
						}
					}
				}
				Return(Buffer(One)
				{
					0x00
				})
			}
		}
	}
	Scope(_SB.I2CB)
	{
		Device(CMSR)
		{
			Name(_ADR, Zero)
			Name(_HID, "CPLM3218")
			Name(_CID, "CPLM3218")
			Name(_UID, One)
			Name(_DEP, Package(1) {I2CB})
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(ALST, 0x02)))
				{
					Return(0x0F)
				}
				Return(Zero)
			}
			Method(_CRS, 0, NotSerialized)
			{
				Name(SBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CB", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0018
					}
				})
				Return(SBUF)
			}
			Name(CPM0, Package(7) {0x7DB5, One, 0x0F, 0x0840, 0x013B, 0x011D, Zero})
			Name(CPM1, Package(3) {0x0898, 0x000186A0, 0x000186A0})
			Name(CPM2, Package(6) {0x61A8, 0x000186A0, 0x000186A0, 0x000186A0, 0x00030D40, 0x00186A00})
			Name(CPM3, Package(4)
			{
				Package(2) {0x3C, 0x0A}, 
				Package(2) {0x64, 0x0B}, 
				Package(2) {0x64, 0x1F40}, 
				Package(2) {0x01F4, 0x1F41}
			})
			Name(CPM5, Package(7) {Zero, 0x000249F0, 0x0190, 0x03E8, 0x02, 0x32, 0x05})
			Method(_DSM, 4, NotSerialized)
			{
				//If(LEqual(Arg0, ToUUID("0703C6B6-1CCA4144-9FE74654F53A0BD9")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xB6, 0xC6, 0x03, 0x07, 0xCA, 0x1C, 0x44, 0x41,
            		/* 0008 */   0x9F, 0xE7, 0x46, 0x54, 0xF5, 0x3A, 0x0B, 0xD9
        		}))
				{
					If(LEqual(Arg2, Zero))
					{
						Return(Buffer(One)
						{
							0x03
						})
					}
					If(LEqual(Arg2, One))
					{
						If(LEqual(ToInteger(Arg3), Zero))
						{
							Return(CPM0)
						}
						If(LEqual(ToInteger(Arg3), One))
						{
							Return(CPM1)
						}
						If(LEqual(ToInteger(Arg3), 0x02))
						{
							Return(CPM2)
						}
						If(LEqual(ToInteger(Arg3), 0x03))
						{
							Return(CPM3)
						}
						If(LEqual(ToInteger(Arg3), 0x05))
						{
							Return(CPM5)
						}
					}
				}
				Return(Buffer(One)
				{
					0x00
				})
			}
		}
	}
	Scope(_SB.I2CC)
	{
		Device(CMSR)
		{
			Name(_ADR, Zero)
			Name(_HID, "CPLM3218")
			Name(_CID, "CPLM3218")
			Name(_UID, One)
			Name(_DEP, Package(1) {I2CC})
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(ALST, 0x03)))
				{
					Return(0x0F)
				}
				Return(Zero)
			}
			Method(_CRS, 0, NotSerialized)
			{
				Name(SBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CC", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0018
					}
				})
				Return(SBUF)
			}
			Name(CPM0, Package(7) {0x7DB5, One, 0x0F, 0x0840, 0x013B, 0x011D, Zero})
			Name(CPM1, Package(3) {0x0898, 0x000186A0, 0x000186A0})
			Name(CPM2, Package(6) {0x61A8, 0x000186A0, 0x000186A0, 0x000186A0, 0x00030D40, 0x00186A00})
			Name(CPM3, Package(4)
			{
				Package(2) {0x3C, 0x0A}, 
				Package(2) {0x64, 0x0B}, 
				Package(2) {0x64, 0x1F40}, 
				Package(2) {0x01F4, 0x1F41}
			})
			Name(CPM5, Package(7) {Zero, 0x000249F0, 0x0190, 0x03E8, 0x02, 0x32, 0x05})
			Method(_DSM, 4, NotSerialized)
			{
				//If(LEqual(Arg0, ToUUID("0703C6B6-1CCA4144-9FE74654F53A0BD9")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xB6, 0xC6, 0x03, 0x07, 0xCA, 0x1C, 0x44, 0x41,
            		/* 0008 */   0x9F, 0xE7, 0x46, 0x54, 0xF5, 0x3A, 0x0B, 0xD9
        		}))
				{
					If(LEqual(Arg2, Zero))
					{
						Return(Buffer(One)
						{
							0x03
						})
					}
					If(LEqual(Arg2, One))
					{
						If(LEqual(ToInteger(Arg3), Zero))
						{
							Return(CPM0)
						}
						If(LEqual(ToInteger(Arg3), One))
						{
							Return(CPM1)
						}
						If(LEqual(ToInteger(Arg3), 0x02))
						{
							Return(CPM2)
						}
						If(LEqual(ToInteger(Arg3), 0x03))
						{
							Return(CPM3)
						}
						If(LEqual(ToInteger(Arg3), 0x05))
						{
							Return(CPM5)
						}
					}
				}
				Return(Buffer(One)
				{
					0x00
				})
			}
		}
	}
	Scope(_SB.I2CD)
	{
		Device(CMSR)
		{
			Name(_ADR, Zero)
			Name(_HID, "CPLM3218")
			Name(_CID, "CPLM3218")
			Name(_UID, One)
			Name(_DEP, Package(1) {I2CD})
			Method(_STA, 0, NotSerialized)
			{
				If(And(LGreaterEqual(TPOS, 0x60), LEqual(ALST, 0x04)))
				{
					Return(0x0F)
				}
				Return(Zero)
			}
			Method(_CRS, 0, NotSerialized)
			{
				Name(SBUF, ResourceTemplate()
				{
					I2CSerialBus(0x0010, ControllerInitiated, 0x00061A80, AddressingMode7Bit, "\\_SB.I2CD", 0x00, ResourceConsumer,,)
					GpioInt(Level, ActiveLow, ExclusiveAndWake, PullUp, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
					{
						0x0018
					}
				})
				Return(SBUF)
			}
			Name(CPM0, Package(7) {0x7DB5, One, 0x0F, 0x0840, 0x013B, 0x011D, Zero})
			Name(CPM1, Package(3) {0x0898, 0x000186A0, 0x000186A0})
			Name(CPM2, Package(6) {0x61A8, 0x000186A0, 0x000186A0, 0x000186A0, 0x00030D40, 0x00186A00})
			Name(CPM3, Package(4)
			{
				Package(2) {0x3C, 0x0A}, 
				Package(2) {0x64, 0x0B}, 
				Package(2) {0x64, 0x1F40}, 
				Package(2) {0x01F4, 0x1F41}
			})
			Name(CPM5, Package(7) {Zero, 0x000249F0, 0x0190, 0x03E8, 0x02, 0x32, 0x05})
			Method(_DSM, 4, NotSerialized)
			{
				//If(LEqual(Arg0, ToUUID("0703C6B6-1CCA4144-9FE74654F53A0BD9")}))
				If(LEqual(Arg0, Buffer (0x10)
        		{
            		/* 0000 */   0xB6, 0xC6, 0x03, 0x07, 0xCA, 0x1C, 0x44, 0x41,
            		/* 0008 */   0x9F, 0xE7, 0x46, 0x54, 0xF5, 0x3A, 0x0B, 0xD9
        		}))
				{
					If(LEqual(Arg2, Zero))
					{
						Return(Buffer(One)
						{
							0x03
						})
					}
					If(LEqual(Arg2, One))
					{
						If(LEqual(ToInteger(Arg3), Zero))
						{
							Return(CPM0)
						}
						If(LEqual(ToInteger(Arg3), One))
						{
							Return(CPM1)
						}
						If(LEqual(ToInteger(Arg3), 0x02))
						{
							Return(CPM2)
						}
						If(LEqual(ToInteger(Arg3), 0x03))
						{
							Return(CPM3)
						}
						If(LEqual(ToInteger(Arg3), 0x05))
						{
							Return(CPM5)
						}
					}
				}
				Return(Buffer(One)
				{
					0x00
				})
			}
		}
	}
	