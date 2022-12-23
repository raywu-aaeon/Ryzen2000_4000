//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                  *****
//*************************************************************************
//**********************************************************************

//**********************************************************************
// DO NOT INCLUDE REVISION HISTORY.  IT IS INTENTIONALLY REMOVED!
//**********************************************************************

Name(Type, 0x80000000)

Method (_PDC,1) {
	CreateDwordField(Arg0,8,DAT0)
	Store(DAT0, TYPE)			// Native GV3 support if BIT0 is set
//	Store(TYPE, DBG8)				

	//Type
	//bit 0: OSPM is capable of direct access to performance state MSRs.
	//bit 1: OSPM supports the C1 "I/O then HALT" FFH sequence.
	//bit 2: OSPM is capable of direct access to On Demand throttling MSR's.
	//bit 3: OSPM is capable of independent C1, P state and Tstate support for each 
	//  	  for multi-processor configurations.
	//bit 4: OSPM is capable of independent C2 and C3 state support each proccesor
	//		  for multi-processor configuations.

	// Check if table already loaded or no P-STATES.
	If (LAND(LEqual(TBLD,0),LNotEqual(NPSS,0))) {
		//Check if independent P-states and C-states are supported or not dual core.
		If (LOR(LEQUAL(AND(TYPE,0x1b),0x1b), LEqual(DCOR, 0))) {
			Store(1, TBLD)
			Load(SSDT, HNDL)	
		}
	}
}					// End of _PDC

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
