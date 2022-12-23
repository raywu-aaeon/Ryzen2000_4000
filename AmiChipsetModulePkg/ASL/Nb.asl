// The ASL file for North Bridge specific function.
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
//**                                                                     **
//*************************************************************************
//*************************************************************************


//;-------------------------------------------------------------------------
//; Here NB Chipset specific porting goes
//; During porting some reserved regions and Power state mappings may be
//; provided.
//;-------------------------------------------------------------------------
//      Method (_S3D, 0){
//              If (LOr(LEqual(OSFL,1),LEqual(OSFL,2))) {Return(2)} // Win98/Me
//              Else {Return(3)}        // Win2K/XP/Linux
//      }

	  Device(AMDN) {
      Name(_HID, EISAID("PNP0C01"))       // Hardware Device ID = >System Board Resources
      Name(_UID, 200)                      // Unique ID
//---------
	  Name(_STA,0x0F)
//---------
      Name(NPTR, ResourceTemplate(){
          Memory32Fixed(ReadWrite, 0, 0, PEX)	//Pci Express Memory Mapped Extended Configuration Space
      })//end NPTR

      // reserved memory 0E0000000h to 4G
	  Method(_CRS, 0) {

          CreateDwordField(NPTR, ^PEX._LEN, PL)
          CreateDwordField(NPTR, ^PEX._BAS, PB)
          Store(\PEBS, PB)
          Store(\PEBL, PL)

          Return (NPTR)
      }
    }

  External(\_SB.APTS, MethodObj)	
  External(\_SB.AWAK, MethodObj)

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	NPTS
; Description:	METHOD IS CALLED BY OS PRIOR TO ENTER ANY SLEEP STATE
; Input: Arg0 = Arg0 = Sleep state System about to enter
; Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Method (NPTS, 1) {
        \_SB.APTS(Arg0)
	}

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:	NWAK
; Description:	METHOD CALLED ON WAKE UP FROM ANY SLEEP STATE
; Input: Arg0 = Sleep state System is resuming from
; Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
	Method (NWAK, 1) {
        \_SB.AWAK(Arg0)
	}

//-----------------------------------------------------------------------
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

