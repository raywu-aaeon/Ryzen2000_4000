//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  This file contains the test for Signed Firmware Update and Signed Firmware Update with test keys.

 */

#include <AmiHsti.h>
#include <Protocol/AmiDigitalSignature.h>
#include "AmiCertificate.h"

extern CHAR16 ImplementationId[];

static AMI_DIGITAL_SIGNATURE_PROTOCOL *mAmiSig = NULL;

const UINT8 *FwBadKey = (CONST UINT8 *)"$BAD";


/*
     This function tries to find the FW keys in the BIOS image
     
     
 */
BOOLEAN CheckForFwKey( VOID )
{
    EFI_STATUS Status;
    CRYPT_HANDLE     pPubKeyHndl;
    EFI_GUID         PRKeyGuid  = PR_KEY_GUID;

    /*
      locate mAmiSig
      test FwKey from the Hob for AMI Test hash pattern.
      same test with the PK
    */
    Status = pBS->LocateProtocol(&gAmiDigitalSignatureProtocolGuid, NULL, (VOID **)&mAmiSig); 
   
    // Ami Digital Signature Protocol not found.  Return an error 
    if (EFI_ERROR(Status))
        return FALSE;
    
    pPubKeyHndl.Blob = NULL;
    pPubKeyHndl.BlobSize = 0;
    Status = mAmiSig->GetKey(mAmiSig, &pPubKeyHndl, &PRKeyGuid, pPubKeyHndl.BlobSize, 0);
        DEBUG((DEBUG_VERBOSE, "Get FW Key %r (%x, %d bytes)\n",Status, pPubKeyHndl.Blob,pPubKeyHndl.BlobSize));
    
    if (!EFI_ERROR(Status) || Status == EFI_BUFFER_TOO_SMALL) 
    {
        if(*((UINT32*)(pPubKeyHndl.Blob)) != *(UINT32*)FwBadKey) {
            // key found
            DEBUG((DEBUG_INFO, "Key found!  Status = %r    \n",Status));
            return TRUE;
        }
    } 
    // get not found
    return FALSE;
}



/*
  This function checks for the Secure Flash functionality to be enabled in the BIOS.  
  
  
  
  @return VOID
 */

VOID SignedFirmwareUpdate( VOID )
{
    UINT64 ImplementationBitMap;
    UINT8  TestBit, TestBit2;
    BOOLEAN KeyPresent;
    BOOLEAN Error1 = FALSE;
    BOOLEAN Error2 = FALSE;
    

    TestBit = PcdGet8(AmiPcdHstiSignedFirmwareUpdateImplementationBit);
    TestBit2 = PcdGet8(AmiPcdHstiSecureUpdateWithDefaultKeyImplementationBit);

    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    DEBUG((DEBUG_INFO, "Signed Firmware Update TestBit = %d   BitMap = %X\r\n", TestBit, ImplementationBitMap));

    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "Signed Firmware Update is not implemented!!  TestBit = %X   BitMap = %X\r\n", TestBit, ImplementationBitMap));
        Error1 = TRUE;
    }
    if ((TestBit2 == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit2) ))
    {
        DEBUG((DEBUG_INFO, "Signed Firmware Update with Default Key is not implemented!!  TestBit = %X   BitMap = %X\r\n", TestBit, ImplementationBitMap));
        Error2 = TRUE;
    }
    
    if (Error1 && Error2)
    {
        return;
    }
    
    
    DEBUG((DEBUG_INFO, "AMI HSTI - Running Signed Firmware Update tests\r\n"));

    KeyPresent = CheckForFwKey();
    // If Secure Flash is enabled then it is supported
    // If it is not the test fails
    if (SecureMod_SUPPORT == 0 || !KeyPresent)
    {
        if (Error1)
            ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_SIGNED_FIRMWARE_UPDATE));
        if (Error2)
            ReportError(TestBit2, 1, STRING_TOKEN(AMI_HSTI_SIGNED_FIRMWARE_UPDATE_WITH_DEFAULT_KEY));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting Signed Firmware Update verification bits\n\r"));
        if (!Error1)
        {
            HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_SECURE_FIRMWARE_UPDATE / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_SECURE_FIRMWARE_UPDATE % 8));
#endif
        }
        
        if (!Error2)
        {
            HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit2 / 8, 1 << (TestBit2 % 8));
        }
    }
}
