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


//<AMI_PHDR_START>
//------------------------------------------------------------------------
//
// Procedure:    PSP
// Description:  describe PSP resource
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>

//---------
    Name(_HID, EISAID("PNP0C02"))   // System board resources device node ID
    Name(PSPA, 0x80000000) //PSP bar a fake value for 32bit declaration, it will be updated in POST
    Name(LENA, 0x80000000) 
    Name(PSPB, 0x80000000) //PSP bar a fake value for 32bit declaration, it will be updated in POST
    Name(LENB, 0x80000000) 
    Name(_STA,0x0F)
//---------

    Name(CRS, ResourceTemplate(){
        // Report summit PSP bar
        Memory32Fixed(ReadWrite, 0, 0, FIXA)
        Memory32Fixed(ReadWrite, 0, 0, FIXB)

    })

    Method (_CRS, 0)
    {
        // Reserved PSP bar
        CreateDwordField(CRS, ^FIXA._BAS, ABAS)
        CreateDwordField(CRS, ^FIXA._LEN, ALEN)
        
        CreateDwordField(CRS, ^FIXB._BAS, BBAS)
        CreateDwordField(CRS, ^FIXB._LEN, BLEN)        

        Store(PSPA, ABAS)       // Base address 
        Store(LENA, ALEN)       // Region length
        
        Store(PSPB, BBAS)       // Base address 
        Store(LENB, BLEN)       // Region length

        Return(CRS)
    }

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
