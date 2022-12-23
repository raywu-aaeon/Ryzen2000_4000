/*****************************************************************************
 *
 * Copyright 2008 - 2011 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software (the Materials)
 * pursuant to the terms and conditions of your Software License Agreement
 * with AMD.  This header does *NOT* give you permission to use the Materials
 * or any rights under AMD's intellectual property.  Your use of any portion
 * of these Materials shall constitute your acceptance of those terms and
 * conditions.  If you do not agree to the terms and conditions of the Software
 * License Agreement, please do not use any portion of these Materials.
 *
 * CONFIDENTIALITY:  The Materials and all other information, identified as
 * confidential and provided to you by AMD shall be kept confidential in
 * accordance with the terms and conditions of the Software License Agreement.
 *
 * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 *
 * AMD does not assume any responsibility for any errors which may appear in
 * the Materials or any other related information provided to you by AMD, or
 * result from use of the Materials or any related information.
 *
 * You agree that you will not reverse engineer or decompile the Materials.
 *
 * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 * further information, software, technical information, know-how, or show-how
 * available to you.  Additionally, AMD retains the right to modify the
 * Materials at any time, without notice, and is not obligated to provide such
 * modified Materials to you.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgement of AMD's proprietary rights in them.
 *
 * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 * direct product thereof will be exported directly or indirectly, into any
 * country prohibited by the United States Export Administration Act and the
 * regulations thereunder, without the required authorization from the U.S.
 * government nor will be used for any purpose prohibited by the same.
 * ***************************************************************************
 */
//AMD Special CMOS Port72/73
//Offset 0 to 0dh, used by ATI SB Module
//
OperationRegion(\DEB2, SystemIO, 0x80, 0x2)
Field(\DEB2, WordAcc, NoLock, Preserve)
{
     P80H, 16
}

Name(OSTY, Ones)                //BIOS kernel asl code should save the OS type in this variable for the
                                //SB CIM module to do settings based on the current OS
                                //      0 - Legacy or Unknown OS
                                //      1 - Win 98/Se
                                //      2 - Win Me
                                //      3 -
                                //      4 - Win 2000
                                //      5 - Window XP
                                //      6 - Windows Vista
                                //      7 and above - reserved for future OS
                                //      Some of the known issues which require this variable setup properly
                                //      are S3 resume failure(blue screen) and S3 resume time issues with Vista,
                                //      Win2K with sata harddrives.

	OperationRegion(ACMS, SystemIO, 0x72, 0x02)
	Field(ACMS, ByteAcc, NoLock, Preserve)
	{
		ACMX, 8,
		ACMA, 8,
	}
	IndexField(ACMX, ACMA, ByteAcc, NoLock, Preserve)
	{
		Offset(0xB9),	//Offset(185),
		IMEN, 8,
	}
	OperationRegion(PSMI, SystemIO, SMIO, 0x02)
	Field(PSMI, ByteAcc, NoLock, Preserve)
	{
		APMC, 8,
		APMD, 8,
	}
	OperationRegion(PMRG, SystemIO, 0x0CD6, 0x02)
	Field(PMRG, ByteAcc, NoLock, Preserve)
	{
		PMRI, 8,
		PMRD, 8,
	}
	IndexField(PMRI, PMRD, ByteAcc, NoLock, Preserve)
	{
		, 6,
		HPEN, 1,
		Offset(0x60),	//Offset(96),
		P1EB, 16,
		Offset(0xF0),	//Offset(240),
		, 3,
		RSTU, 1,
	}
// Picasso ++	
	OperationRegion(GSMG, SystemMemory, 0xFED81500, 0x03FF)
	Field(GSMG, AnyAcc, NoLock, Preserve)
	{
		Offset(0x5C),   //Offset(92),
		Offset(0x5E),   //Offset(94),
		GS23, 1,
		, 5,
		GV23, 1,
		GE23, 1,
		Offset(0xA0),   //Offset(160),
		Offset(0xA2),   //Offset(162),
		GS40, 1,
		, 5,
		GV40, 1,
		GE40, 1,
	}
// Picasso ++   	
	OperationRegion(GSMM, SystemMemory, 0xFED80000, 0x1000)
	Field(GSMM, AnyAcc, NoLock, Preserve)
	{
		Offset(0x288),	//Offset(648),
		, 1,
		CLPS, 1,
//EIP218890+
    offset(0x296),
    ,7,
    TMSE,1,                             //Timer SMI En
//EIP218890+
		Offset(0x2B0),	//Offset(688),
		, 2,
		SLPS, 2,
		Offset(0x3BB),	//Offset(955),
		, 6,
		PWDE, 1,
	}

	OperationRegion(P1E0, SystemIO, P1EB, 0x04)
	Field(P1E0, ByteAcc, NoLock, Preserve)
	{
		Offset(0x1),	//Offset(1),
		, 6,
		PEWS, 1,
		WSTA, 1,
		Offset(0x3),	//Offset(3),
		, 6,
		PEWD, 1,
	}

	OperationRegion(IOCC, SystemIO, PMBS, 0x80)
	Field(IOCC, ByteAcc, NoLock, Preserve)
	{
		, 8,
		, 2,
		RTCS, 1,
	}


Method (SPTS, 1) {
	       Store(Arg0, P80H)

		If(LEqual(Arg0, 0x03))
		{
			Store(Zero, RSTU)
		}

        Store(One, CLPS)
		Store(One, SLPS)
		Store(PEWS, PEWS)

		If(LEqual(Arg0, 0x03))
		{
			Store(One, \SLPS)
		}
		If(LEqual(Arg0, 0x04))
		{
			Store(One, \SLPS)
			Store(One, RSTU)
		}
		If(LEqual(Arg0, 0x05))
		{
			Store(One, PWDE)
			//Store(0x90, BCMD)
			//\_SB.BSMI(Zero)
			//\_SB.GSMI(0x03)
		}
	//Store(1, PCMD)
	//Store(Arg0, P80_)

	//Set Blink LED according to sleep state, for S4/S5 leave it ON always.
// 	if (LEqual(Arg0,1)){Store(0x02,\BLNK)}	// for S1, 10: 2sec on, 2sec off, repeating
// 	if (LEqual(Arg0,2)){Store(0x00,\BLNK)}	// for S2, 00: Blink LED off
// 	if (LEqual(Arg0,3)){Store(0x01,\BLNK)}	// for S3, 1sec on, 3sec off, repeating


//	Store(1, CLPS)	// Clear SLP_SMI Status
//	Store(1, SLPS)	// Enable SLP_SMI
//	Store(0, ALLS)  // Set NOT to allow any S state (For SLEEP trap)
//	Store(1, PHYD)  // A11 bug
	//CPMS()
	//CPMS()
//
// Clear GPP9 NIC PME Status for ACPI S1 cannot wake while the system goes to sleep state second time.
//
//		Store(5, Local0)
//		While(Local0)
//		{
//			Store(1, PMSA)
//			Store(1, PMSB)
//			Store(1, PMSC)
//			Decrement(Local0)
//		}
// This procedure is workaround for Hudson-2 A11 only.
// Please removed it after A12 chip come back.
	//	Store(1, PEWS)			// Clear PciExpWakeStatus
//		Store(0x66,DBG8)

//Hudson-2 comment out 	if (LLessEqual(\RVID, 0x13)) {Store(zero, \PWDE)}	// Clear PciExpWakeDisEn to workaround PCIE LAN wakeup hang issue
// 	if (LEqual(Arg0,4)){Store(zero,US5R)}
}

Method (SWAK, 1) {

		If(LEqual(Arg0, 0x03))
		{
			Store(One, RSTU)
		}
		Store(\PEWS, \PEWS)
		Store(Zero, \PEWD)

	If (PICM)
	{
		\_SB_.DSPI()
	}
//	Store(One, \PMS7)
//EIP218890+
if (TMSE){
  Store(0, TMSE)
}
//EIP218890+
// 	Store(one, HECO)	// Enable HPET ECO
// 	if (LEqual(Arg0,3)){Store(one,RSTU)}	//set RSTU to make pci_rst reset USB in S3
// 	Store(\PEWS, \PEWS)	// Clear PciExpWakeStatus
// 	Store(0x03, \BLNK)	// Turn on Blink LED for S0 stateb

	//CPMS()
	//CPMS()
//
// Clear GPP9 NIC PME Status for ACPI S1 cannot wake while the system goes to sleep state second time.
//
//		Store(5, Local0)
//		While(Local0)
//		{
//			Store(1, PMSA)
//			Store(1, PMSB)
//			Store(1, PMSC)
//			Decrement(Local0)
//		}
//
// This procedure is workaround for Hudson-2 A11 only.
// Please removed it after A12 chip come back.
//
		//Store(1, PEWS)			// Clear PciExpWakeStatus
    //if (IMCS) {
   //   IBWE()
  //  }

//		Store(0x77,DBG8)
// 	if (LEqual(Arg0,4)){Store(one,US5R)}

		If(LEqual(Arg0, 0x03))
		{
		 Notify(\_SB.PWRB, 0x02) 
		}
		If(LEqual(Arg0, 0x04))
		{
		Notify(\_SB.PWRB, 0x02)
		}
}

Scope (\_GPE)
{
//	Method(_L1F, 0) {store(0x1f,P80_)}
//	Method(_L19, 0) {store(0x19,P80_)}
//	Method(_L06, 0) {store(0x06,P80_)}
//	Method(_L00, 0) {store(0x00,P80_)}
}
	
