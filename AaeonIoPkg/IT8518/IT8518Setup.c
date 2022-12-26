//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <IT8518Setup.c>
//
// Description: Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include "IT8518Setup.h"

#include "EcApiProtocol.c"
//#include "SetupStringList.h"

/*
 * Put None Standard Setup Functions Here.
*/

VOID InitIT851XVersionStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class
);
//-------------------------------------------------------------------------
VOID InitIT851XVersionStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class)
{
        UINT8   i;
        UINT8   EC1_DATE[4];
        UINT8   EC1_VERSION[8];

        if (EcFwAccess(ApiRead))
        {
          if (EcReadByte(EcReg_Dat0)&0x01 )
          {
              for (i=0;i<8;i++)
              { EC1_VERSION[i] = EcReadByte(EcReg_Dat0+5+i);  }
              
              for (i=0;i<4;i++)
              { EC1_DATE[i] = EcReadByte(EcReg_Dat0+1+i);  } 
              
              
              InitString(HiiHandle,STRING_TOKEN(STR_EC1_VERSION_VALUE),L"    (%c%c%c%c%c%c%c%c)(%x/%x/%x%x)",EC1_VERSION[0],EC1_VERSION[1],EC1_VERSION[2],EC1_VERSION[3],EC1_VERSION[4],EC1_VERSION[5],EC1_VERSION[6],EC1_VERSION[7],EC1_DATE[2],EC1_DATE[3],EC1_DATE[0],EC1_DATE[1]);
              

              /*
                InitString(HiiHandle,STRING_TOKEN(STR_EC1_VENDOR_VALUE),L"AAEON");
                InitString(HiiHandle,STRING_TOKEN(STR_EC1_INFO_VALUE),L"CPU Board");
                
                for (i=0;i<8;i++)
                { EC1_VERSION[i] = EcReadByte(EcReg_Dat0+5+i);  }
                InitString(HiiHandle,STRING_TOKEN(STR_EC1_VERSION_VALUE),L"%c%c%c%c%c%c%c%c",EC1_VERSION[0],EC1_VERSION[1],EC1_VERSION[2],EC1_VERSION[3],EC1_VERSION[4],EC1_VERSION[5],EC1_VERSION[6],EC1_VERSION[7]);

                for (i=0;i<4;i++)
                { EC1_DATE[i] = EcReadByte(EcReg_Dat0+1+i);  } 
                InitString(HiiHandle,STRING_TOKEN(STR_EC1_BUILD_DATE_VALUE),L"%x/%x/%x%x",EC1_DATE[2],EC1_DATE[3],EC1_DATE[0],EC1_DATE[1]);    
              */
          }        
        }                                   
}
//RayWu, ADD 2014/07/17 <<
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    OemInitIT8518SetupStrings
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
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID OemInitIT8518SetupStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class)
{
    /*    static EFI_GUID siopg=EFI_AMI_SIO_PROTOCOL_GUID;
        SIO_DEV2        *dev;
        UINTN           i,hcnt;
        EFI_HANDLE      *hbuff;
        EFI_STATUS      Status=0;

        if(Class == ADVANCED_FORM_SET_CLASS) {
            Status=pBS->LocateHandleBuffer(ByProtocol,&siopg, NULL, &hcnt,&hbuff);
            if (EFI_ERROR(Status)) hcnt = 0;
            for (i=0; i<hcnt; i++) {
                Status = pBS->HandleProtocol ( hbuff[i],&siopg,(VOID*)&dev);
                ASSERT_EFI_ERROR(Status);
                if(dev->DeviceInfo->HasSetup) SetSioStrings(dev, HiiHandle);
            }
        }
    */
}
/////////////////////////////////////////////////////////////////////////////
//Below function will update HII database's SIO strings, before enter setup
/////////////////////////////////////////////////////////////////////////////

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
