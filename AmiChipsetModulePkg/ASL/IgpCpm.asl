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
//<AMI_FHDR_START>
//
// Name:        IgpCpm.asl
//
// Description: IGD asl code for compatible with Raven CPM.
//
// Notes:
//
//<AMI_FHDR_END>
//*************************************************************************

    External(AFN7, MethodObj)

    Name(AF7E, 0x80000001)

    Method(_STA, 0, NotSerialized)
    {
        Return(0x0F)
    }
    
    Name(DOSA, Zero)

    Method(_DOS, 1, NotSerialized)
    {
        Store(Arg0, DOSA)
    }

    Method(_DOD, 0, NotSerialized)
    {
        Return(Package(7) {0x00010110, 0x00010210, 0x00010220, 0x00010230, 0x00010240, 0x00031000, 0x00032000})
    }


    Device(LCD)
    {
        Name(_ADR, 0x0110)
        Name(BCLB, Package(52)
        {
            0x5A, 0x3C, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12,
            0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28,
            0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E,
            0x40, 0x42, 0x44, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x54,
            0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x64
        })
        Method(_BCL, 0, NotSerialized)
        {
            Return(BCLB)
        }
        Method(_BCM, 1, NotSerialized)
        {
            If(LEqual(AF7E, 0x80000001))
            {
                Divide(Multiply(Arg0, 0xFF), 0x64, Local1, Local0)
                AFN7(Local0)
				//Store(Arg0, BRTL)
            }
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
