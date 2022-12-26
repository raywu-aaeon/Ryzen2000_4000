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
//
// Name:  <F81866Setup.c>
//
// Description: Setup related Routines.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include "F81866Setup.h"
//#include "SetupStringList.h"

/*
 * Put None Standard Setup Functions Here.
*/

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:    OemInitF81866SetupStrings
//
// Description:
//  This function provide SIO Setup screen display string.
//
// Input:
//  IN  IN UINT16       Class
//  IN  EFI_HII_HANDLE  *HiiHandle
//
// Output:    VOID
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//----------------------------------------------------------------------
// <AMI_PHDR_END>
VOID OemInitF81866SetupStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class)
{
    /*    static EFI_GUID siopg=EFI_AMI_SIO_PROTOCOL_GUID;
        SIO_DEV2        *Dev;
        UINTN           i,hcnt;
        EFI_HANDLE      *hbuff;
        EFI_STATUS      Status=0;

        if(Class == ADVANCED_FORM_SET_CLASS) {
            Status=pBS->LocateHandleBuffer(ByProtocol,&siopg, NULL, &hcnt,&hbuff);
            if (EFI_ERROR(Status)) hcnt = 0;
            for (i=0; i<hcnt; i++) {
                Status = pBS->HandleProtocol ( hbuff[i],&siopg,(VOID*)&Dev);
                ASSERT_EFI_ERROR(Status);
                if(Dev->DeviceInfo->HasSetup) SetSioStrings(Dev, HiiHandle);
            }
        }
    */
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
