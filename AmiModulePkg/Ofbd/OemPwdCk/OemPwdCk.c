//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file 
OemPwdCk.c

Password Check protocol is for BIOS to indicate AFU that BIOS password exists and 
needs to initiate password checking before flashing BIOS. AFU will set OEM_PC_CK 
in dbGetCkSts field and send OFBD data to BIOS to report password checking is 
required or not.
 
If password check function is requested then BIOS should fill out password length 
in dwPwdLen field. Afterward AFU asks user to input password with specified password
length given from BIOS in field dwPwdLen and fill user input password in memory 
buffer after signature of OFBD_EXT_TBL_END for BIOS to do the comparison. 
*/

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "OemPwdCk.h"
#include "../Ofbd.h"

static int ErrorNum = 0;

/**
   	Ofbd (Oem Password Get handle)
	
	This function is used to tell the Afu, the BIOS supports password checking and provide the password length.
	
	@param pOFBDHdr - Ofbd header.

  	@return EFI_STATUS
  	@retval EFI_SUCCESS Function executed successfully
*/ 

EFI_STATUS
OFBDPwdGetHandle( 
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_PWDCK_SAMPLE_TEST
    
    UINT8 *pOFBDTblEnd;
	OFBD_TC_52_PC_STRUCT *PwdCkStructPtr; 

    pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + gOFBD_Size);
	PwdCkStructPtr = (OFBD_TC_52_PC_STRUCT *)((UINT8 *)pOFBDHdr + sizeof(OFBD_HDR) + sizeof(OFBD_EXT_HDR)); 
	
	//
	// For OEM engineers to reference >>>
	//
	
	// 
    // How to let Afu knows that Bios supports password checking function.
    //
	
	//
	// Step 01. Fill in the OEM_RS_PC_REQ in PwdCkStructPtr->dbRetSts
	//
	// Step 02. Fill in the password length in PwdCkStructPtr->dwPwdLen 
	//
	
	
	//
	// (Optional) : How to request that Afu to display the special message string
	//
	
	//
	// Step 01. Fill in the OFBD_RS_DIS_OEMSTR in pOFBDHdr->OFBD_RS
	//
	// Step 02. Copy the message string data into pOFBDTblEnd
	//

    //
    // For OEM engineers to reference <<<
    //
#endif

    return(Status);
}

/**
   	Ofbd (Oem Password Check handle)
	
	This function is used to check the user input password, which get from Afu.
	
	@param pOFBDHdr - Ofbd header.

  	@return EFI_STATUS
  	@retval EFI_SUCCESS Function executed successfully
*/ 

EFI_STATUS
OFBDPwdCheckHandle(
    IN OUT OFBD_HDR *pOFBDHdr)
{
    EFI_STATUS Status = EFI_SUCCESS;

#if OEM_PWDCK_SAMPLE_TEST
	UINT8 *pOFBDTblEnd;
	OFBD_TC_52_PC_STRUCT *PwdCkStructPtr;  
   
	PwdCkStructPtr = (OFBD_TC_52_PC_STRUCT *)((UINT8 *)pOFBDHdr + sizeof(OFBD_HDR) + sizeof(OFBD_EXT_HDR)); 
	pOFBDTblEnd = (UINT8 *)((UINT8 *)pOFBDHdr + gOFBD_Size);
	
	//
    // For OEM engineers to reference >>>
    //
    
	// 
	// How to get user input password from Afu tools for comparison
	//
	
    //
    // Step 01. Get the password data from pOFBDTblEnd
    //
    // Step 02. Get the password data length from PwdCkStructPtr->dwPwdLen (which based on user input data length)
    // 
    // Step 03-1. If the comparison is passed, please fill in OEM_RS_PC_CK_OK in PwdCkStructPtr->dbRetSts, 
	//
	//            otherwise do not fill out.
	//
	// Step 03-2. If the comparison still fails and exceeds the number of retries, please fill in
	//
	//            OEM_RS_PC_TIMES_EXCEEDED in PwdCkStructPtr->dbRetSts, let Afu to stop the flash process.
    //
    
	//
    // (Optional) : How to request that Afu to display the special message string
    //
    
    //
    // Step 01. Fill in the OFBD_RS_DIS_OEMSTR in pOFBDHdr->OFBD_RS
    //
    // Step 02. Copy the message string data into pOFBDTblEnd
    //

    //
    // For OEM engineers to reference <<<
    //
	
#endif

    return(Status);
}

/**
   	This function is Ofbd Oem Password Check function entry point

	@param Buffer - Ofbd header.
  	@param pOFBDDataHandled - handle value returns
  	
	@retval	0xFF means Function executed successfully
	@retval	0xFE means Function error occured
*/ 

VOID OEMPWDCKEntry (
    IN VOID             *Buffer,
    IN OUT UINT8        *pOFBDDataHandled )
{
    OFBD_HDR *pOFBDHdr;
    OFBD_EXT_HDR *pOFBDExtHdr; 
    VOID *pOFBDTblEnd;
    OFBD_TC_52_PC_STRUCT *PwdCkStructPtr;    

    if(*pOFBDDataHandled == 0)
    {
        pOFBDHdr = (OFBD_HDR *)Buffer;
        pOFBDExtHdr = (OFBD_EXT_HDR *)((UINT8 *)Buffer + sizeof(OFBD_HDR));
        PwdCkStructPtr = (OFBD_TC_52_PC_STRUCT *)((UINT8 *)pOFBDExtHdr + sizeof(OFBD_EXT_HDR)); 
        pOFBDTblEnd = (VOID *)((UINT8 *)Buffer + gOFBD_Size);    

        //TRACE((-1,"pOFBDHdr address is:%x ------\n",pOFBDHdr));
        //TRACE((-1,"pOFBDTblEnd address is:%x ------\n",*(UINT64 *)((UINT8 *)pOFBDTblEnd -sizeof(OFBD_END))));
        
        if(pOFBDHdr->OFBD_FS & OFBD_FS_PWD)
        {   
            //Check Type Code ID
            if(pOFBDExtHdr->TypeCodeID == OFBD_EXT_TC_PWD)
            {  
                //IoWrite32(0x300, *(UINT32 *)((UINT8 *)pOFBDTblEnd -4)); //debug
				if(PwdCkStructPtr->dbGetCkSts == OFBD_TC_OPC_GET)
				{
					if(OFBDPwdGetHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM ROM ID Data Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
				else if(PwdCkStructPtr->dbGetCkSts == OFBD_TC_OPC_CHECK)
				{
					if(OFBDPwdCheckHandle(pOFBDHdr) == EFI_SUCCESS)
					{
						//OEM ROM ID Data Handled.
                    	*pOFBDDataHandled = 0xFF;      
                    	return;
                	}
				}
                /*//Not OEM ROM ID Data.
                *pOFBDDataHandled = 0;          
                return;*/
            } 
            //else
            //{
                 //Error occured
                *pOFBDDataHandled = 0xFE;          
                return;
            //}
        }  
    }

    return;
}


