//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>

//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
// Include(s)
#include <Uefi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include <Setup.h>

#include "AaeonIoPkg\IT8518\EcApiProtocol.c"

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: 
//
// Description:
// 
// Input:
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS EFIAPI
IT85xx_AfterG3Init (SETUP_DATA *SetupData)
{
    EFI_STATUS Status = EFI_SUCCESS;

    {	    	   	
    	#if defined (IT85xx_AFTER_G3_SUPPORT)&& (IT85xx_AFTER_G3_SUPPORT == 1)
    	{
    		if (!SetupData->AaeonPowerMode)
    		{ 
    			if (SetupData->AaeonSIO_AfterG3 == 0x02)
    			{
    			EcPmcAccess(ApiRead);   
    			EcWriteByte(EcReg_Dat0,(EcReadByte(EcReg_Dat0)&0xFC));	
    			EcPmcAccess(ApiWrite);		    
    			}
    		}
    	}
    	#endif		
    }

	return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
