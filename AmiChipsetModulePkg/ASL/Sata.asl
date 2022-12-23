
				Name(B5EN, Zero)
				Name(BA_5, Zero)
				Name(SBAR, 0xF0B6F000)
					Name(OSVR, Zero)
				/*
				Name(SAD0, Zero)
				Name(SAD3, Zero)
				PowerResource(P0SA, 0, 0)
				{
					Method(_STA, 0, NotSerialized)
					{
						Return(SAD0)
					}
					Method(_ON, 0, NotSerialized)
					{
						Store(0xA1, DBG8)
						Store(One, SAD0)
					}
					Method(_OFF, 0, NotSerialized)
					{
						Store(0xA2, DBG8)
						Store(Zero, SAD0)
					}
				}
				PowerResource(P3SA, 0, 0)
				{
					Method(_STA, 0, NotSerialized)
					{
						Return(SAD3)
					}
					Method(_ON, 0, NotSerialized)
					{
						Store(0xA4, DBG8)
						Store(One, SAD3)
					}
					Method(_OFF, 0, NotSerialized)
					{
						Store(0xA5, DBG8)
						Store(Zero, SAD3)
					}
				}
				*/
					
				OperationRegion(SATX, PCI_Config, Zero, 0x44)
				Field(SATX, AnyAcc, NoLock, Preserve)
				{
					VIDI, 32,
					Offset(0xA),	//Offset(10),
					STCL, 16,
					Offset(0x24),	//Offset(36),
					BA05, 32,
					Offset(0x40),	//Offset(64),
					WTEN, 1,
					Offset(0x42),	//Offset(66),
					DIS0, 1,
					DIS1, 1,
					DIS2, 1,
					DIS3, 1,
					DIS4, 1,
					DIS5, 1,
				}
				Field(SATX, AnyAcc, NoLock, Preserve)
				{
					Offset(0x42),	//Offset(66),
					DISP, 6,
				}
				Method(GBAA, 0, Serialized)
				{
					Store(BA05, BA_5)
					If(LOr(LEqual(BA_5, Ones), LNotEqual(STCL, 0x0101)))
					{
						Store(Zero, B5EN)
						Return(SBAR)
					}
					Else
					{
						Store(One, B5EN)
						Return(BA_5)
					}
				}
				OperationRegion(BAR5, SystemMemory, GBAA, 0x1000)
				Field(BAR5, AnyAcc, NoLock, Preserve)
				{
					NOPT, 5,
					Offset(0xC),	//Offset(12),
					PTI0, 1,
					PTI1, 1,
					PTI2, 1,
					PTI3, 1,
					PTI4, 1,
					PTI5, 1,
					PTI6, 1,
					PTI7, 1,
					Offset(0x118),	//Offset(280),
					CST0, 1,
					Offset(0x120),	//Offset(288),
					, 7,
					BSY0, 1,
					Offset(0x128),	//Offset(296),
					DET0, 4,
					, 4,
					IPM0, 4,
					Offset(0x12C),	//Offset(300),
					DDI0, 4,
					Offset(0x198),	//Offset(408),
					CST1, 1,
					Offset(0x1A0),	//Offset(416),
					, 7,
					BSY1, 1,
					Offset(0x1A8),	//Offset(424),
					DET1, 4,
					, 4,
					IPM1, 4,
					Offset(0x1AC),	//Offset(428),
					DDI1, 4,
					Offset(0x218),	//Offset(536),
					CST2, 1,
					Offset(0x220),	//Offset(544),
					, 7,
					BSY2, 1,
					Offset(0x228),	//Offset(552),
					DET2, 4,
					, 4,
					IPM2, 4,
					Offset(0x22C),	//Offset(556),
					DDI2, 4,
					Offset(0x298),	//Offset(664),
					CST3, 1,
					Offset(0x2A0),	//Offset(672),
					, 7,
					BSY3, 1,
					Offset(0x2A8),	//Offset(680),
					DET3, 4,
					, 4,
					IPM3, 4,
					Offset(0x2AC),	//Offset(684),
					DDI3, 4,
					Offset(0x318),	//Offset(792),
					CST4, 1,
					Offset(0x320),	//Offset(800),
					, 7,
					BSY4, 1,
					Offset(0x328),	//Offset(808),
					DET4, 4,
					, 4,
					IPM4, 4,
					Offset(0x32C),	//Offset(812),
					DDI4, 4,
					Offset(0x398),	//Offset(920),
					CST5, 1,
					Offset(0x3A0),	//Offset(928),
					, 7,
					BSY5, 1,
					Offset(0x3A8),	//Offset(936),
					DET5, 4,
					, 4,
					IPM5, 4,
					Offset(0x3AC),	//Offset(940),
					DDI5, 4,
				}
				Field(BAR5, AnyAcc, NoLock, Preserve)
				{
					Offset(0xC),	//Offset(12),
					PTI, 6,
				}
				Method(_INI, 0, NotSerialized)
				{
					GBAA()
				}
				Device(PRID)
				{
					Name(_ADR, Zero)
					Name(SPTM, Buffer(0x14)
					{
						0x78, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 
						0x78, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 
						0x1F, 0x00, 0x00, 0x00
					})
					Method(_GTM, 0, NotSerialized)
					{
						Return(SPTM)
					}
					Method(_STM, 3, NotSerialized)
					{
						Store(Arg0, SPTM)
					}
					Method(_PS0, 0, NotSerialized)
					{
						GBAA()
						If(LAnd(LOr(LGreaterEqual(OSVR, 12), LEqual(OSVR, 0)), B5EN))
						{
							If(IPM2)
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY2, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
					}
					Method(_PS3, 0, NotSerialized)
					{
					}
					Device(P_D0)
					{
						Name(_ADR, Zero)
						Method(_STA, 0, NotSerialized)
						{
							GBAA()
							If(LEqual(B5EN, Zero))
							{
								Return(Zero)
							}
							If(LEqual(DET0, 0x03))
							{
								Return(0x0F)
							}
							Else
							{
								Return(Zero)
							}
						}
						Name(S12P, Zero)
						Method(_PS0, 0, NotSerialized)
						{
							GBAA()
							If(LAnd(LAnd(LLess(OSVR, 12), LNotEqual(OSVR, 0)), B5EN))
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY0, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
						Method(_PS3, 0, NotSerialized)
						{
						}
						Method(_GTF, 0, NotSerialized)
						{
							Store(Buffer(0x07)
							{
								0x03, 0x46, 0x00, 0x00, 0x00, 0xA0, 0xEF
							}, Local0)
							Return(Local0)
						}
					}
					Device(P_D1)
					{
						Name(_ADR, One)
						Method(_STA, 0, NotSerialized)
						{
							GBAA()
							If(LEqual(B5EN, Zero))
							{
								Return(Zero)
							}
							If(LEqual(DET2, 0x03))
							{
								Return(0x0F)
							}
							Else
							{
								Return(Zero)
							}
						}
						Name(S12P, Zero)
						Method(_PS0, 0, NotSerialized)
						{
							GBAA()
							If(LAnd(LAnd(LLess(OSVR, 12), LNotEqual(OSVR, 0)), B5EN))
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY2, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
						Method(_PS3, 0, NotSerialized)
						{
						}
						Method(_GTF, 0, NotSerialized)
						{
							Store(Buffer(0x07)
							{
								0x03, 0x46, 0x00, 0x00, 0x00, 0xA0, 0xEF
							}, Local0)
							Return(Local0)
						}
					}
				}
				Device(SECD)
				{
					Name(_ADR, 0x02)
					Name(SPTM, Buffer(0x14)
					{
						0x78, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 
						0x78, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 
						0x1F, 0x00, 0x00, 0x00
					})
					Method(_GTM, 0, NotSerialized)
					{
						Return(SPTM)
					}
					Method(_STM, 3, NotSerialized)
					{
						Store(Arg0, SPTM)
					}
					Method(_PS0, 0, NotSerialized)
					{
						GBAA()
						If(LAnd(LOr(LGreaterEqual(OSVR, 12), LEqual(OSVR, 0)), B5EN))
						{
							If(IPM1)
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY1, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
							If(IPM3)
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY3, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
					}
					Method(_PS3, 0, NotSerialized)
					{
					}
					Device(S_D0)
					{
						Name(_ADR, Zero)
						Method(_STA, 0, NotSerialized)
						{
							GBAA()
							If(LEqual(B5EN, Zero))
							{
								Return(Zero)
							}
							If(LEqual(DET1, 0x03))
							{
								Return(0x0F)
							}
							Else
							{
								Return(Zero)
							}
						}
						Method(_PS0, 0, NotSerialized)
						{
							GBAA()
							If(LAnd(LAnd(LLess(OSVR, 12), LNotEqual(OSVR, 0)), B5EN))
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY1, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
						Method(_PS3, 0, NotSerialized)
						{
						}
						Method(_GTF, 0, NotSerialized)
						{
							Store(Buffer(0x07)
							{
								0x03, 0x46, 0x00, 0x00, 0x00, 0xA0, 0xEF
							}, Local0)
							Return(Local0)
						}
					}
					Device(S_D1)
					{
						Name(_ADR, One)
						Method(_STA, 0, NotSerialized)
						{
							GBAA()
							If(LEqual(B5EN, Zero))
							{
								Return(Zero)
							}
							If(LEqual(DET3, 0x03))
							{
								Return(0x0F)
							}
							Else
							{
								Return(Zero)
							}
						}
						Method(_PS0, 0, NotSerialized)
						{
							GBAA()
							If(LAnd(LAnd(LLess(OSVR, 12), LNotEqual(OSVR, 0)), B5EN))
							{
								Store(0x32, Local0)
								While(LAnd(LEqual(BSY3, One), Local0))
								{
									Sleep(0xFA)
									Decrement(Local0)
								}
							}
						}
						Method(_PS3, 0, NotSerialized)
						{
						}
						Method(_GTF, 0, NotSerialized)
						{
							Store(Buffer(0x07)
							{
								0x03, 0x46, 0x00, 0x00, 0x00, 0xA0, 0xEF
							}, Local0)
							Return(Local0)
						}
					}
				}
				Method(ENP, 2, NotSerialized)
				{
					If(LEqual(Arg0, Zero))
					{
						Store(Not(Arg1), DIS0)
					}
					Else
					{
						If(LEqual(Arg0, One))
						{
							Store(Not(Arg1), DIS1)
						}
						Else
						{
							If(LEqual(Arg0, 0x02))
							{
								Store(Not(Arg1), DIS2)
							}
							Else
							{
								If(LEqual(Arg0, 0x03))
								{
									Store(Not(Arg1), DIS3)
								}
								Else
								{
									If(LEqual(Arg0, 0x04))
									{
										Store(Not(Arg1), DIS4)
									}
									Else
									{
										If(LEqual(Arg0, 0x05))
										{
											Store(Not(Arg1), DIS5)
										}
									}
								}
							}
						}
					}
					Store(One, WTEN)
					If(LEqual(Arg0, Zero))
					{
						Store(Arg1, PTI0)
					}
					Else
					{
						If(LEqual(Arg0, One))
						{
							Store(Arg1, PTI1)
						}
						Else
						{
							If(LEqual(Arg0, 0x02))
							{
								Store(Arg1, PTI2)
							}
							Else
							{
								If(LEqual(Arg0, 0x03))
								{
									Store(Arg1, PTI3)
								}
								Else
								{
									If(LEqual(Arg0, 0x04))
									{
										Store(Arg1, PTI4)
									}
									Else
									{
										If(LEqual(Arg0, 0x05))
										{
											Store(Arg1, PTI5)
										}
									}
								}
							}
						}
					}
					If(LEqual(DISP, 0x3F))
					{
						Store(One, PTI0)
					}
					Else
					{
						If(LAnd(DIS0, Xor(And(DISP, 0x3E), 0x3E)))
						{
							Store(Zero, PTI0)
						}
					}
					Store(PTI, Local0)
					Store(Zero, Local1)
					While(Local0)
					{
						If(And(Local0, One))
						{
							Increment(Local1)
						}
						ShiftRight(Local0, One, Local0)
					}
					Store(Decrement(Local1), NOPT)
					Store(Zero, WTEN)
				}
			