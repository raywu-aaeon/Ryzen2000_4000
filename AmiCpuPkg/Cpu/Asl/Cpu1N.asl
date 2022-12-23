//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:  cpu1N.asl
//
//  Description:
//   CPU asl code for 1-Node configuration
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

Scope(\_PR ){
	OperationRegion(SSDT,SystemMemory,0xFFFF0000,0xFFFF)	// Will be updated during BIOS POST.
	Name(DCOR, 2)			//Is Dual Core? This will be updated during BIOS.
	Name(TBLD, 0x4)			//Flag indicates whether SSDT loaded yet
	Name(NPSS, 5)			//Num of P-states supported. This will be updated during BIOS.
	Name(HNDL, 0x80000000)	//Handle Returned while LOADing SSDT

	//_PSS states shared by all CPUs.
	Name(APSS, Package() {
	//	Package() {  <CoreFreq[WORD]>,
	// 	             |       <Power[WORD]>,
	//  	         |       |       <TransitionLatency[WORD]>,
	//	             |       |       |      <BusMasterlatency[WORD]>,
	// 	             |       |       |       |       <Control Register value to write to achive described performance state [WORD]> 
	//  	         |       |       |       |       |       <Status Register value to read back to verify successful transition accomplished[WORD]>
	//	             |       |       |       |       |       |
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 0
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 1
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 2
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 3
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 4
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 5
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 6
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 7
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 8
		Package() {  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},  // State 9
	})
//Always Start the Scope Name from P001 for the Windows to Boot
//Number of Entries should be equal to Max number of cores in the system
//Porting Starts Here: 

	Processor(P000, 1, 0x810, 0x6) {
		include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
	}
	Processor(P001, 2, 0x810, 0x6) {
		include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
	}
	Processor(P002, 3, 0x810, 0x6) {
		include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
	}
	Processor(P003, 4, 0x810, 0x6) {
		include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
	}
    Processor(P004, 5, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P005, 6, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P006, 7, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P007, 8, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P008, 9, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P009, 0xA, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00A, 0xB, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00B, 0xC, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00C, 0xD, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00D, 0xE, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00E, 0xF, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }
    Processor(P00F, 0x10, 0x810, 0x6) {
        include ("AmiCpuPkg\\CPU\\Asl\\CpuAsl.inc")
    }


}	// End of \_PR scope

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
