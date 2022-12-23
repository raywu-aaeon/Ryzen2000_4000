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

/** @file SbCspIoDecodeLib.c
    This file contains code for South Bridge LPC IO Decode
    initialization in the Library stage

*/

//-------------------------------------------------------------------------
// Include(s)
//-------------------------------------------------------------------------

#include <Token.h>
#include <AmiChipsetIoLib.h>
#include <Sb.h>
#include <Library/PcdLib.h>
#include <Protocol/AmiSio.h>
#include <Library/SbCspLib.h>



// The definition is for AMD SB LPC ISA Bridge (Device 20, Function 3)
// from IO Port Decode Enable Register 1- RW - 8 bits - [PCI_Reg: 44h]
// to IO Port Decode Enable Register 4- RW - 8 bits - [PCI_Reg: 47h]
typedef union _AMD_SB_IO_DECODE_REG1_4{
    struct {
        UINT32  ParallelPort:6; // 0..5
        UINT32  SerialPort:8; // 0..7
        UINT32  AudioPort:4; // 0..3
        UINT32  MIDIPort:4; // 0..3
        UINT32  MSSPort:4; // 0..3
        UINT32  FdcPort:2; // 0..1
        UINT32  GamePort:1; // 0
        UINT32  KbcPort:1; // 0
        UINT32  AcpiMicroControllerPort:1; // 0
        UINT32  AdLibPort:1; // 0
    };
    UINT32      CONFIG;
}AMD_SB_IO_DECODE_REG1_4;

typedef union _AMD_SB_IO_MEM_DECODE_REG5{
    struct  {
        UINT8   SuperIoPort:1;              // 0
        UINT8   AlternateSuperIoPort:1;     // 1
        UINT8   WideGenericIoPort:1;        // 2
        UINT8   RomRange1Port:1;            // 3
        UINT8   RomRange2Port:1;            // 4
        UINT8   MemoryRangePort:1;          // 5
        UINT8   RtcIoRangePort:1;           // 6
        UINT8   NullPort:1;                 // 7
    };
    UINT8       CONFIG;
}AMD_SB_IO_MEM_DECODE_REG5;

typedef union _AMD_SB_IO_MEM_DECODE_REG6{
    struct  {
        UINT8   IoPort0:1;                  // 0
        UINT8   IoPort1:1;                  // 1
        UINT8   IoPort2:1;                  // 2
        UINT8   IoPort3:1;                  // 3
        UINT8   MemPort:1;                  // 4
        UINT8   IoPort4:1;                  // 5
        UINT8   IoPort5:1;                  // 6
        UINT8   IoPort6:1;                  // 7
    };
    UINT8       CONFIG;
}AMD_SB_IO_MEM_DECODE_REG6;

typedef union _AMD_SB_IO_MEM_DECODE_REG7{
    struct  {
        UINT8   WideIo1:1;              // 0
        UINT8   WideIo2:1;              // 1
        UINT8   NullPort:6;             // 2~7
    };
    UINT8       CONFIG;
}AMD_SB_IO_MEM_DECODE_REG7;

typedef struct _AMD_SB_LPC_DECODER{
    AMD_SB_IO_DECODE_REG1_4     SbIoDecodeReg1;
    AMD_SB_IO_MEM_DECODE_REG5   SbIoMemDecodeReg5;
    AMD_SB_IO_MEM_DECODE_REG6   SbIoMemDecodeReg6;
    AMD_SB_IO_MEM_DECODE_REG7   SbIoMemDecodeReg7;
    BOOLEAN                     SbIoDecodeReg1En;
    BOOLEAN                     SbIoMemDecodeReg5En;
    BOOLEAN                     SbIoMemDecodeReg6En;
    BOOLEAN                     SbIoMemDecodeReg7En;
}AMD_SB_LPC_DECODER;


/**
    This function set LPC Bridge Generic Decoding

    @param *LpcPciIo - Pointer to LPC PCI IO Protocol (This is not used but kept for backwards compatible)
    @param Base      - I/O base address
    @param Length    - I/O Length
    @param Enabled   - Enable/Disable the generic decode range register
    
    @retval EFI_SUCCESS - Set successfully.
    @retval EFI_UNSUPPORTED - This function is not implemented or the Length more than the maximum supported size of generic range decoding.
    @retval EFI_INVALID_PARAMETER - the Input parameter is invalid.
    @retval EFI_OUT_OF_RESOURCES - There is not available Generic Decoding Register.
    @retval EFI_NOT_FOUND - the generic decode range will be disabled is not found.

**/
EFI_STATUS AmiSioLibSetLpcGenericDecoding (
    IN VOID           *LpcPciIo,
    IN UINT16         Base,
    IN UINT16         Length,
    IN BOOLEAN        Enable
    )
{
    // Porting Required
    UINT8                   Index;
    UINT16                  IoBase;
    AMD_SB_LPC_DECODER      dr;
    UINT8                   AltWideIoRange;
    UINT16					OrgIoBase[3] = {0, 0, 0};

    if (Length > 0x200) return EFI_UNSUPPORTED;

    if (Length == 0) return EFI_INVALID_PARAMETER;

    if (Length < 4) Length = 4;

    // IO/Mem Port Decode Enable Register 5- RW - 8 bits - [PCI_Reg: 48h]
    dr.SbIoMemDecodeReg5.CONFIG = READ_PCI8_SB(0x48);

    // Read I/O Generic Decodes Register.
    // IO/Mem Port Decode Enable Register 7- RW - 8 bits - [PCI_Reg: 4Bh]
    dr.SbIoMemDecodeReg7.CONFIG = READ_PCI8_SB(0x4B);

    if (((dr.SbIoMemDecodeReg7.CONFIG & (BIT00 + BIT01)) == (BIT00 + BIT01)) \
        && ((dr.SbIoMemDecodeReg5.CONFIG & BIT02) == BIT02)) return EFI_OUT_OF_RESOURCES;

    OrgIoBase[0] = READ_PCI16_SB(0x64);
    OrgIoBase[1] = READ_PCI16_SB(0x66);
    OrgIoBase[2] = READ_PCI16_SB(0x90);

    IoBase = Base;
    if (Enable) {
        Index = 0xff;

        // Due to Agesa "KernHwAcpiReset.c" force to use "FCH_LPC_REG64(IOBaseAddress1)" for "CfgSioPmeBaseAddress".
        // Therefore, we could not use "FCH_LPC_REG64(IOBaseAddress1)" for other usage.
        if ( ((dr.SbIoMemDecodeReg5.CONFIG & BIT02) == 0) && (SB_SIO_PME_BASE_ADDRESS == Base) ) Index = 0;
        else if ((dr.SbIoMemDecodeReg7.CONFIG & BIT00) == 0) Index = 1;
        else if ((dr.SbIoMemDecodeReg7.CONFIG & BIT01) == 0) Index = 2;
#if 0
        if ((Index != 0) && (Length > 0x10) && ((dr.SbIoMemDecodeReg5.CONFIG & BIT02) == 0))
        {
            Index = 0;
        }
#endif

		// check if the same base has been programmed in PEI
		if (dr.SbIoMemDecodeReg5.CONFIG & BIT02) {
            // Due to Agesa "KernHwAcpiReset.c" force to use "FCH_LPC_REG64(IOBaseAddress1)" for "CfgSioPmeBaseAddress".
            // Therefore, we could not use "FCH_LPC_REG64(IOBaseAddress1)" for other usage.
			if ( (OrgIoBase[0] == Base) && (SB_SIO_PME_BASE_ADDRESS == Base) ) Index = 0;
		}
		if (dr.SbIoMemDecodeReg7.CONFIG & BIT00) {
			if (OrgIoBase[1] == Base) Index = 1;
		}
		if (dr.SbIoMemDecodeReg7.CONFIG & BIT01) {
			if (OrgIoBase[2] == Base) Index = 2;
		}

        switch (Index) {
            case 0 :
                dr.SbIoMemDecodeReg5.WideGenericIoPort = 1;
                break;
            case 1 :
                dr.SbIoMemDecodeReg7.WideIo1 = 1;
                break;
            case 2 :
                dr.SbIoMemDecodeReg7.WideIo2 = 1;
                break;
            default :
                return EFI_UNSUPPORTED;
        }
    } else {
        for (Index = 0; Index < 3; Index++) {
            switch (Index) {
                case 0 :
                    // Due to Agesa "KernHwAcpiReset.c" force to use "FCH_LPC_REG64(IOBaseAddress1)" for "CfgSioPmeBaseAddress".
                    // Therefore, we could not use "FCH_LPC_REG64(IOBaseAddress1)" for other usage.
                    if (OrgIoBase[Index] == Base && \
                        SB_SIO_PME_BASE_ADDRESS == Base && \
                        (dr.SbIoMemDecodeReg5.CONFIG & BIT02)) {
                        IoBase = 0;
                        dr.SbIoMemDecodeReg5.WideGenericIoPort = 0;
                    }
                    break;
                case 1 :
                    if (OrgIoBase[Index] == Base && \
                        (dr.SbIoMemDecodeReg7.CONFIG & BIT00)) {
                        IoBase = 0;
                        dr.SbIoMemDecodeReg7.WideIo1 = 0;
                    }
                    break;
                case 2 :
                    if (OrgIoBase[Index] == Base && \
                        (dr.SbIoMemDecodeReg7.CONFIG & BIT01)) {
                        IoBase = 0;
                        dr.SbIoMemDecodeReg7.WideIo2 = 0;
                    }
                    break;
            }
        }
        //###AltWideIoRange = READ_PCI8_SB(0x74);
        //###WRITE_PCI8_SB(0x74, AltWideIoRange & ~(BIT00 + BIT02 + BIT03));
    }

    WRITE_PCI8_SB(0x48, dr.SbIoMemDecodeReg5.CONFIG);
    WRITE_PCI8_SB(0x4B, dr.SbIoMemDecodeReg7.CONFIG);

	AltWideIoRange = 0;
    switch (Index) {
        case 0 :
        	AltWideIoRange = BIT00;
            WRITE_PCI16_SB(0x64, IoBase);
            break;
        case 1 :
            AltWideIoRange = BIT02;
            WRITE_PCI16_SB(0x66, IoBase);
            break;
        case 2 :
        	AltWideIoRange = BIT03;
            WRITE_PCI16_SB(0x90, IoBase);
            break;
    }
	if (Length <= 16) {
		// 0 => Wide IO range defined by D14F3x64 is 512 bytes.
		// 1 => The range is 16 bytes. To use this feature,
		// address in D14F3x64 must be aligned to 16 bytes,
		// i.e., bits[3:0] must be 0.
		// If the address is not aligned to 16 bytes,
		// the IO range is from address[15:0] to {address[15:4], 0xF}.
		//###WRITE_PCI8_SB(0x74, READ_PCI8_SB(0x74) | AltWideIoRange);
		SET_PCI8_SB(0x74, AltWideIoRange);
	} else {
		RESET_PCI8_SB(0x74, AltWideIoRange);
	}
    // Porting End

    return EFI_SUCCESS;

}

/**
    This function sets LPC Bridge Device Decoding

    @param *LpcPciIo - Pointer to LPC PCI IO Protocol (This is not used but kept for backwards compatible)
    @param Base      - I/O base address, if Base is 0 means disabled the decode of the device
    @param DevUid    - The device Unique ID
    @param Type      - Device Type, please refer to AMISIO.h
    
    @retval EFI_SUCCESS - Set successfully.
    @retval EFI_UNSUPPORTED - There is not proper Device Decoding register for the device UID.

**/
EFI_STATUS AmiSioLibSetLpcDeviceDecoding (
    IN VOID                 *LpcPciIo,
    IN UINT16               Base,
    IN UINT8                DevUid,
    IN SIO_DEV_TYPE         Type
    )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    AMD_SB_LPC_DECODER      dr;

    //
    // Read what currently have there...
    // IO Port Decode Enable Register 1- RW - 8 bits - [PCI_Reg: 44h]
    // IO Port Decode Enable Register 2- RW - 8 bits - [PCI_Reg: 45h]
    // IO Port Decode Enable Register 3- RW - 8 bits - [PCI_Reg: 46h]
    // IO Port Decode Enable Register 4- RW - 8 bits - [PCI_Reg: 47h]
    //
    //####Status = LpcPciIo->Pci.Read(LpcPciIo, \
    //####                    EfiPciIoWidthUint32, \
    //####                    0x44, \
    //####                    1, \
    //####                    &dr.SbIoDecodeReg1.CONFIG \
    //####                    );
    //####if (EFI_ERROR(Status)) return Status;
    dr.SbIoDecodeReg1.CONFIG = READ_PCI32_SB(0x44);
    dr.SbIoDecodeReg1En = TRUE;

    // IO/Mem Port Decode Enable Register 5- RW - 8 bits - [PCI_Reg: 48h]
    //####Status = LpcPciIo->Pci.Read(LpcPciIo, \
    //####                    EfiPciIoWidthUint8, \
    //####                    0x48, \
    //####                    1, \
    //####                    &dr.SbIoMemDecodeReg5.CONFIG \
    //####                    );
    //####if (EFI_ERROR(Status)) return Status;
    dr.SbIoMemDecodeReg5.CONFIG = READ_PCI8_SB(0x48);
    dr.SbIoMemDecodeReg5En = TRUE;

    //
    // Check all possible Base Addresses
    //
    switch (Type) {

        case (dsFDC) :
            switch(Base) {
                case 0 :
                    dr.SbIoDecodeReg1.FdcPort = 0;
                    break;
                // FDC Address range
                case 0x3f0 :
                    dr.SbIoDecodeReg1.FdcPort |= BIT00;
                    break;
                case 0x370 :
                    dr.SbIoDecodeReg1.FdcPort |= BIT01;
                    break;
                default :
                    dr.SbIoDecodeReg1En = FALSE;
                    dr.SbIoMemDecodeReg5En = FALSE;
                    Status = EFI_UNSUPPORTED;
            }
            break;

        case (dsLPT) :
            switch(Base) {
                case 0 :
                    dr.SbIoDecodeReg1.ParallelPort = 0;
                    break;
                // LPT Address range
                case 0x378 :
                    dr.SbIoDecodeReg1.ParallelPort |= BIT00;
                    break;
                case 0x278 :
                    dr.SbIoDecodeReg1.ParallelPort |= BIT02;
                    break;
                case 0x3bc :
                    dr.SbIoDecodeReg1.ParallelPort |= BIT04;
                    break;
                default :
                    dr.SbIoDecodeReg1En = FALSE;
                    dr.SbIoMemDecodeReg5En = FALSE;
                    Status = EFI_UNSUPPORTED;
            }
            break;

        case (dsUART) :
            switch(Base) {
                case 0 :
// (P20101118A-) -                    if (DevUid) dr.SbIoDecodeReg1.SerialPort &= ~BIT01;
// (P20101118A-)                     else dr.SbIoDecodeReg1.SerialPort &= ~BIT00;
                    //####dr.SbIoDecodeReg1.SerialPort = 0;
                    break;
                // COM Port Address range
                case 0x3f8 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT00;
                    break;
                case 0x2f8 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT01;
                    break;
                case 0x220 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT02;
                    break;
                case 0x228 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT03;
                    break;
                case 0x238 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT04;
                    break;
                case 0x2E8 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT05;
                    break;
                case 0x338 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT06;
                    break;
                case 0x3e8 :
                    dr.SbIoDecodeReg1.SerialPort |= BIT07;
                    break;
                default :
                    dr.SbIoDecodeReg1En = FALSE;
                    dr.SbIoMemDecodeReg5En = FALSE;
                    Status = EFI_UNSUPPORTED;
            }
            break;

        // KBC Address Enable
        case (dsPS2K) :
// (P20101112A-)        case (dsPS2M) :
        case (dsPS2CK) :
// (P20101112A-)        case (dsPS2CM) :
            if (Base == 0) dr.SbIoDecodeReg1.KbcPort = 0;
            else dr.SbIoDecodeReg1.KbcPort = 1;
            break;
        // (P20101112A)>
        case (dsPS2M) :
        case (dsPS2CM) :
            break;
        // <(P20101112A)

        // Game Port Address Enable
        case (dsGAME) :
            switch(Base) {
                case 0 :
                    dr.SbIoDecodeReg1.GamePort = 0;
                    break;
                // Game port, Midi, IR
                case 0x200 : case 0x201 : case 0x202 : case 0x203 :
                case 0x204 : case 0x205 : case 0x206 : case 0x207 :
                case 0x208 : case 0x209 : case 0x20A : case 0x20B :
                case 0x20C : case 0x20D : case 0x20E : case 0x20F :
                    dr.SbIoDecodeReg1.GamePort = 1;
                    break;
                default :
                    dr.SbIoDecodeReg1En = FALSE;
                    dr.SbIoMemDecodeReg5En = FALSE;
                    Status = EFI_UNSUPPORTED;
            }
            break;

        // Other Address Enable
        case (0xff) :
            switch (Base) {
                case 0x62 : case 0x66 :
                    dr.SbIoDecodeReg1.AcpiMicroControllerPort = 1;
                    break;
                case 0x388 : case 0x389 :
                    dr.SbIoDecodeReg1.AdLibPort = 1;
                    break;

                case 0x230 :
                    dr.SbIoDecodeReg1.AudioPort |= BIT00;
                    break;
                case 0x240 :
                    dr.SbIoDecodeReg1.AudioPort |= BIT01;
                    break;
                case 0x260 :
                    dr.SbIoDecodeReg1.AudioPort |= BIT02;
                    break;
                case 0x280 :
                    dr.SbIoDecodeReg1.AudioPort |= BIT03;
                    break;

                case 0x300 :
                    dr.SbIoDecodeReg1.MIDIPort |= BIT00;
                    break;
                case 0x310 :
                    dr.SbIoDecodeReg1.MIDIPort |= BIT01;
                    break;
                case 0x320 :
                    dr.SbIoDecodeReg1.MIDIPort |= BIT02;
                    break;
                case 0x330 :
                    dr.SbIoDecodeReg1.MIDIPort |= BIT03;
                    break;

                case 0x530 :
                    dr.SbIoDecodeReg1.MSSPort |= BIT00;
                    break;
                case 0x604 :
                    dr.SbIoDecodeReg1.MSSPort |= BIT01;
                    break;
                case 0xE80 :
                    dr.SbIoDecodeReg1.MSSPort |= BIT02;
                    break;
                case 0xF40 :
                    dr.SbIoDecodeReg1.MSSPort |= BIT03;
                    break;

                case 0x2e :
                    dr.SbIoMemDecodeReg5.SuperIoPort = 1;
                    break;
                case 0x4e :
                    dr.SbIoMemDecodeReg5.AlternateSuperIoPort = 1;
                    break;

                default :
                    dr.SbIoDecodeReg1En = FALSE;
                    dr.SbIoMemDecodeReg5En = FALSE;
                    Status = AmiSioLibSetLpcGenericDecoding( LpcPciIo, \
                                                            Base , \
                                                            DevUid, \
                                                            TRUE );
            }
            break;

        default :
            dr.SbIoDecodeReg1En = FALSE;
            dr.SbIoMemDecodeReg5En = FALSE;
            Status = EFI_UNSUPPORTED;
    }
    // Use Provided LPC Bridge PCI IO to write data back
    if (dr.SbIoDecodeReg1En) {
        //####Status = LpcPciIo->Pci.Write(LpcPciIo, \
        //####                    EfiPciIoWidthUint32, \
        //####                    0x44, \
        //####                    1, \
        //####                    &dr.SbIoDecodeReg1.CONFIG \
        //####                    );
        //####if (EFI_ERROR(Status)) return Status;
        WRITE_PCI32_SB(0x44, dr.SbIoDecodeReg1.CONFIG);
    }

    // Use Provided LPC Bridge PCI IO to write data back
    if (dr.SbIoMemDecodeReg5En) {
        //####Status = LpcPciIo->Pci.Write(LpcPciIo, \
        //####                    EfiPciIoWidthUint8, \
        //####                    0x48, \
        //####                    1, \
        //####                    &dr.SbIoMemDecodeReg5.CONFIG \
        //####                    );
        //####if (EFI_ERROR(Status)) return Status;
        WRITE_PCI8_SB(0x48, dr.SbIoMemDecodeReg5.CONFIG);
    }

    return Status;
}

/**
    This function sets LPC Bridge Device Decoding
              
    @param LpcPciIo Pointer to LPC PCI IO Protocol
    @param Base I/O base address, if Base is 0 means disabled the
           decode of the device 
    @param DevUid The device Unique ID
    @param Type Device Type, please refer to AMISIO.h

    @retval EFI_STATUS
            EFI_SUCCESS Set successfully.
            EFI_UNSUPPORTED There is not proper Device Decoding 
                            register for the device UID.
**/
EFI_STATUS SbLibSetLpcDeviceDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT8                    DevUid,
    IN SIO_DEV_TYPE             Type )
{
    return  AmiSioLibSetLpcDeviceDecoding ( LpcPciIo, \
                                            Base , \
                                            DevUid, \
                                            Type);
}

/**
    This function set LPC Bridge Generic Decoding
              
    @param LpcPciIo Pointer to LPC PCI IO Protocol
    @param Base I/O base address
    @param Length I/O Length
    @param Enabled Enable/Disable the generic decode range register

    @retval EFI_STATUS
            EFI_SUCCESS Set successfully.
            EFI_UNSUPPORTED This function is not implemented or the
                            Length more than the maximum supported
                            size of generic range decoding.
            EFI_INVALID_PARAMETER the Input parameter is invalid.
            EFI_OUT_OF_RESOURCES There is not available Generic
                                 Decoding Register.
            EFI_NOT_FOUND the generic decode range will be disabled
                          is not found.
**/
EFI_STATUS SbLibSetLpcGenericDecoding (
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable )
{
    return  AmiSioLibSetLpcGenericDecoding( LpcPciIo, \
                                            Base , \
                                            Length, \
                                            Enable);
}

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
