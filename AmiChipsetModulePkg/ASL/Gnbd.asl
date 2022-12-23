//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// Revision History
// ----------------
// $Log: $
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        Gnbd.asl
//
// Description: GNB asl code
//
// Notes:
//
//<AMI_FHDR_END>
//*************************************************************************
	OperationRegion(NAPC, PCI_Config, 0xF8, 0x08)
	Field(NAPC, DWordAcc, NoLock, Preserve)
	{
		NAPX, 32,
		NAPD, 32,
	}
	Mutex(NAPM, 0)
	Method(NAPE, 0, NotSerialized)
	{
		Acquire(NAPM, 0xFFFF)
		Store(Zero, NAPX)
		Store(NAPD, Local0)
		And(Local0, 0xFFFFFFEF, Local0)
		Store(Local0, NAPD)
		Release(NAPM)
	}

	Method(GINI, 0, NotSerialized)
	{
        NAPE()
	}

 OperationRegion(NBRV, PCI_Config, 0x08, 1)
  Field(NBRV,ByteAcc,NoLock,Preserve)
  {
    	PREV, 8		// PCI revision-classcode
  }
// RS880 NB (bus0/dev0/func0) NB_BAR3_PCIEXP_MMCFG
  OperationRegion(NBBR, PCI_Config, 0x1C, 0x8)
  Field(NBBR, DwordAcc, NoLock, Preserve)
  {
	BR3L, 32,
	BR3H, 32,
  }

// RS880 NB (bus0/dev0/func0) NB_PCI_ARB
  OperationRegion(NBBI, PCI_Config, 0x84, 0x4)
  Field(NBBI, DwordAcc, NoLock, Preserve)
  {
	PARB,32,
  }
  
  
// RS880 NB (bus0/dev0/func0) NBMISCIND index/data register pair
  OperationRegion(NBMS, PCI_Config, 0x60, 0x8)
  Field(NBMS,DwordAcc,NoLock,Preserve)
  {
	MIDX,32,
	MIDR,32
  }
 
  Mutex(NBMM, 0)
  
  // Read RS880 NBMISCIND register as dword
  // Arg0 = index(0x00-0x5E)
  Method(NBMR, 1)
  {
	Acquire(NBMM, 0xFFFF)
	And(Arg0, 0x7F, Local0)
	Store(Local0, MIDX)
	Store(MIDR, Local0)
	Store(0x7F, MIDX)
	Release(NBMM)
	Return(Local0)
  }
  
  // Write RS880 NBMISCIND register as dword
  // Arg0 = index(0x00-0x5E)
  // Arg1 = dword data
  Method(NBMW, 2)
  {
	Acquire(NBMM, 0xFFFF)
	And(Arg0, 0x7F, Local0)
	Or(Local0, 0x80, Local0)
	Store(Local0, MIDX)
	Store(Arg1, MIDR)
//	Store(0x7F, MIDX)
	Store(and(Local0, 0x7F, Local0), MIDX)
	Release(NBMM)
  }
  
  OperationRegion(NBXP, PCI_Config, 0xE0, 0x8)
  Field(NBXP, DwordAcc, NoLock, Preserve)
  {
	NBXI,32,
	NBXD,32
  }

  Mutex(NBXM, 0)
  
  Method(NBXR, 1)
  {
	Acquire(NBXM, 0xFFFF)
	Store(Arg0, NBXI)
	Store(NBXD, Local0)
	Store(0, NBXI)
	Release(NBXM)
	Return(Local0)
  }
  
  Method(NBXW, 2)
  {
	Acquire(NBXM, 0xFFFF)
	Store(Arg0, NBXI)
	Store(Arg1, NBXD)
	Store(0, NBXI)
	Release(NBXM)  
  }
  
    // Get NB PCIE GFX Core Mode
  Method(GFXM)
  {
	Store(NBMR(0x08), Local0)
	And(Local0, 0x0F, Local0)
	Return(Local0)
  }

  // Get NB PCIE GPPSB Core Mode
  Method(GPPM)
  {
	Store(NBMR(0x067), Local0)
	And(Local0, 0xF0, Local0)
	Return(Local0)  
  }
  
  // Get PCIE GPP Core Mode (for configuration modes C and D
  // and Port9 (mode C or D) and Port10 (mode D only))
  Method(GPPX)
  {

// For RS780 this corresponds to NBMisc register 0x2d
// Bits[10:7] (PCIE_NBCFG+REG15 - NBMISCIND: 0x2D)
// See RS780 RPR secion 5.6 PIE GPP COnfiguration
	Store(NBMR(0x2D), Local0)
	ShiftRight(Local0, 0x07, Local0)
	And(Local0, 0x0F, Local0)
	Return(Local0)
  }

  // Set/Clear PCIE HOLD_TRAINx bit for a PCIE Port
  // Arg0 = (2,10) device number of RS880 PCIE P2P
  // Arg1 = 0(set HOLD_TRAINx bit to disable training)
  //      = 1(clear HOLD_TRAINx bit to allow training)
  Method(XPTR,2)
  {
  	If(LAnd(LLess(Arg0,2),LGreater(Arg0,7)))
  	{
  		Return(0)	// out of range
  	}
  	Else
  	{
		Store(GPPM(), Local0)	// Get Pcie GPPSB configuration mode
		Store(GPPX(), Local1)	// Get Pcie GPP configuration mode
		Store(1,Local0)
	  	If(LLess(Arg0,4))
  		{
			Add(Arg0,2,Local1)	  		
	  	}
  		Else
	  	{
  			Add(Arg0,17,Local1)
  		}
	  	ShiftLeft(Local0,Local1,Local0)
		Store(NBMR(0x08),Local2)	// PCIE_LINK_CFG
		If(Arg1)
		{	// Allow training
			And(Local2,Not(Local0),Local2)	
		}
		Else
		{	// Hold training
			Or(Local2,Local0,Local2)
		}
		NBMW(0x08,Local2)
		Return(Ones)
	}
  }

  Name(PX3L, 0x80000000)	// 32 bits reserved name for BAR3 low
  Name(PX3H, 0x80000000)	// 32 bits reserved name for BAR3 high
  Name(PX3S, 0x10000000)	// default size of NB_PCIE_BAR3_MMCFG range (256 bus's)
  Name(PX3K, 0xF0000000)	// default mask of NB_PCIE_BAR3_MMCFG (start at Bit 28)
  Mutex(BR3X, 0)

  Method(BR3M, 0)
  {
   Store(PARB, Local0)
	ShiftRight(Local0, 16, Local0)
	And(Local0, 0x7, Local0)

	// If nbcfg(0x84[18:16]) is not 0  then we need to adjust the size
	If(Local0) {
	// PCIE Enhanced Configuration Mechanism Address mapping ...
	// A[63:28] upper bits of base address (256MB aligned)
	// A[27:20] target bus number (1 of 256 max)
	// A[19:15] target device number (1 of 32)
	// A[14:12] target function number (1 of 8)
	// A[11:2]  target dword number (1 of 1024)

	// 32 devices(5 bits) * 1024 dwords(10 bits) * 4 bytes/dword * 8 functions(3 bits)	

	// In ATI/AMD RS5xx and up design, the bits [27:20] of the PCIE MMCFG BAR3 register
	// may be used to limit the # of bus's decoded.

	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 0, bus range = A[27:20] (default, 8 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 1, bus range = A[20]    (1 bit)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 2, bus range = A[21:20] (2 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 3, bus range = A[22:20] (3 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 4, bus range = A[23:20] (4 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 5, bus range = A[24:20] (5 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 6, bus range = A[25:20] (6 bits)
	// For nbcfg(bus 0, dev0, fn0) Reg84[18:16] = 7, bus range = A[26:20] (7 bits)

	// Pre-calculated # of bytes needed per bus = 0x100000 bytes =
	// (32devices (5bits) * 1024Dwords (10bits) * 4 Bytes/Dword * 8functions (3 bits))	

		ShiftLeft(0x1, Local0, Local1)
		Subtract(0x1000, Local1, Local1)
		ShiftLeft(Local1, 20, Local1)
		Store(Local1, PX3K)			// Update the mask

		ShiftRight(0x100000, Local0, Local0)
		Store(Local0, PX3S)			// update the size
	}

	// We use a mutex to prevent any other code from
	// accessing this while we need to get to it
	Acquire(BR3X, 0xFFFF)

	// Unhide PCIE_MMCFG_BAR
	Store(NBMR(0x00), Local0)
	And(Local0,0xFFFFFFF7, Local0)
	NBMW(0x00, Local0)

	// Get the low 32 bits
	Store(BR3L, Local0)
	And(Local0, PX3K, Local0)			// mask out the lower unused bits
	Store(Local0, PX3L)

	Store(BR3H, Local0)
	And(Local0, 0xFF, Local0)			// mask for 8bits (BAR3[39:32])
	Store(Local0, PX3H)

	// Hide PCIE_MMCFG_BAR again
	Store(NBMR(0x00), Local0)
	Or(Local0, 0x08, Local0)
	NBMW(0x00, Local0)

	Release(BR3X)

	Return(PX3L)
  }
  
  
Method (GPTS, 1) {
}

Method (GWAK, 1) {
    If (PICM)
    {
            NAPE()
    }
}


	OperationRegion(NB2_, PCI_Config, 0x00, 0x100)
	Field(NB2_, AnyAcc, NoLock, Preserve) {
		Offset (0x60),
		MI_, 32,		//Misc Index
		MD_, 32,
		Offset (0x90),
        TOM_, 32,
		Offset (0x94),
		OI_, 32,		//ORB Index
		OD_, 32,
		Offset (0xE0),
		LI_, 32,		//Link index
		LD_, 32		
  		}

	Device(BROD) {

		Name(_HID, EISAID("PNP0C02"))	// System board resources device node ID
		Name(_UID, 0x14)		// Unique ID. 
		Name(UMAS, 0x18000000)  // Variable for UMASize
		Name(CRS, ResourceTemplate() {
			Memory32Fixed(ReadOnly, 0x00000000, 0x00000000, NUMA) //Non-writeable (Default Values)
		}		// End of ResourceTemplate
		)		// end of CRS

		Method (_CRS, 0)                // Reserve UMA resource
		{
			CreateDwordField(CRS, ^NUMA._BAS, BAS1) // Base Address for UMA
			CreateDwordField(CRS, ^NUMA._LEN, LEN1) // Length for UMA

            Store(UMAS, LEN1)
            Subtract(TOM_, LEN1, BAS1)    // Base Address for UMA = TOM - length
			Return(CRS)
		}
	}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************
