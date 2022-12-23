//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  This file contains the test for verifying that the AMI test keys are not a part of the BIOS
  
 */

#include <AmiHsti.h>
#include <Protocol/AmiDigitalSignature.h>
#include "AmiCertificate.h"

extern EFI_GUID gEfiGlobalVariableGuid;
extern CHAR16 ImplementationId[];

static AMI_DIGITAL_SIGNATURE_PROTOCOL *mAmiSig = NULL;
static UINT8 Digest[SHA256_DIGEST_SIZE]={0};

// Ami Test Rsa2048 key
static UINT8 AmiKey1Hash[SHA256_DIGEST_SIZE] = {
   0x56, 0xd2, 0xe8, 0x18, 0xf9, 0x6e, 0x9e, 0x2f, 0x3f, 0xa4, 0x80, 0xff, 0xc7, 0xb3, 0xb4, 0x41, 
   0x62, 0x6c, 0x10, 0xf7, 0xc1, 0xc8, 0xbb, 0xb1, 0xf4, 0x44, 0xba, 0x86, 0xce, 0x7d, 0xd2, 0x70
};

// Ami Test Key2 x509 Certificate
static  UINT8 AmiKey21Hash[SHA256_DIGEST_SIZE]={
  0x42, 0x8c, 0x2a, 0x22, 0x01, 0x91, 0x0d, 0xec, 0x7d, 0x54, 0x23, 0xf5, 0xd8, 0x33, 0x23, 0x3e, 
  0x91, 0x9e, 0x49, 0xb8, 0xb7, 0x09, 0x03, 0xcb, 0x46, 0x65, 0xe0, 0xaa, 0x33, 0xe8, 0x95, 0xcf
};
// Sha256 hash of Tbs cert
 static UINT8 AmiKey22Hash[SHA256_DIGEST_SIZE]={
  0x7f, 0xc4, 0x28, 0xe4, 0x26, 0xb2, 0xa2, 0x30, 0x22, 0xad, 0x2f, 0x55, 0xd5, 0x22, 0xc6, 0x9b, 
  0x8f, 0x3d, 0x7e, 0x79, 0x11, 0x21, 0x9c, 0xd3, 0xe9, 0x72, 0xc1, 0xe1, 0x8b, 0xee, 0x21, 0x70
};

// Ami Test PK Key, n-modulus RSA2048
static UINT8 AmiPkKeyHash1[SHA256_DIGEST_SIZE] = {
      0xa9, 0x51, 0x19, 0x2f, 0x10, 0xe3, 0x90, 0x51, 0xf8, 0x0a, 0xfb, 0xc3, 0x83, 0x0e, 0x9f, 0xc9,
      0x10, 0xe7, 0xa5, 0x49, 0x20, 0xbe, 0x50, 0xf9, 0xb8, 0x04, 0xd6, 0x7e, 0x88, 0x15, 0x96, 0xd9
    };
// Ami Test PK Key, x509 Certificate
static UINT8 AmiPkKeyHash2[SHA256_DIGEST_SIZE]={
      0xcc, 0xa4, 0xe3, 0xf3, 0x17, 0x02, 0x30, 0x03, 0x0d, 0xc3, 0xe3, 0x3d, 0x1e, 0x3f, 0xa7, 0xd1,
      0x38, 0x3d, 0xe8, 0xb3, 0x36, 0x74, 0x30, 0x89, 0x2e, 0x93, 0xcb, 0xcc, 0xde, 0x03, 0x4c, 0xe0
    };

VOID TestKeyVerification( VOID )
{
    UINT64 ImplementationBitMap;
    BOOLEAN Error = FALSE;
    EFI_STATUS Status;
    UINT8   nError = 0;
    // 1 - FwKey = AMI Test
    // 2 - PK =AMI Test
    CRYPT_HANDLE     pPubKeyHndl;
    EFI_GUID         PRKeyGuid  = PR_KEY_GUID;
    UINTN             Size;
    VOID            *Var=NULL;
    INTN            err;
    UINT8           *CertStart;
    UINTN           CertLen;
    UINT8           *pDigest = Digest;
    EFI_SIGNATURE_LIST *SigList;
    EFI_SIGNATURE_DATA *SigData;
    UINT8 TestBit;
    
    TestBit = PcdGet8(AmiPcdHstiNoTestKeyImplementationBit);

    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);

    DEBUG((DEBUG_INFO, "Test Key Verification BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));

    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "Test Key Verification is not implemented\r\n"));
        return;
    }
    /*
     *  
     * locate mAmiSig
     * test FwKey from the Hob for AMI Test hash pattern.
     * same test with the PK
     */
    //
    if(mAmiSig == NULL)
    {
        Status = pBS->LocateProtocol(&gAmiDigitalSignatureProtocolGuid, NULL, (VOID **)&mAmiSig); 
        if(EFI_ERROR(Status) || !mAmiSig) {
            Error = TRUE;
        }
    }
    if(!Error)
    {
    /* 
     * Download and verify strength of Fw and PK keys 
     */
/*
 * 1. Locate FwKey
*/
// Get PRKey ptr
        pPubKeyHndl.Blob = NULL;
        pPubKeyHndl.BlobSize = 0;
        Status = mAmiSig->GetKey(mAmiSig, &pPubKeyHndl, &PRKeyGuid, pPubKeyHndl.BlobSize, 0);
//        DEBUG((-1, "Get FW Key %r (%x, %d bytes)\n",Status, pPubKeyHndl.Blob,pPubKeyHndl.BlobSize));
        if (!EFI_ERROR(Status) || Status == EFI_BUFFER_TOO_SMALL) {
                // check If dummy key - return Mode = 0
//            Byte = pPubKeyHndl.Blob[0];
//            for(Size = 1; Size < pPubKeyHndl.BlobSize && (Byte == pPubKeyHndl.Blob[Size]); Size++);
//            if(Size == pPubKeyHndl.BlobSize) {
//                nError = 1;
//            }
//            if(!nError)
//            {
                // hash the Rsa or x509 key    
                // x509 hash of full Cert file         
                if(!guidcmp(&pPubKeyHndl.AlgGuid, &gEfiCertSha256Guid))
                    pDigest = pPubKeyHndl.Blob;
                else 
                    Status = mAmiSig->Hash(mAmiSig, 
                            &gEfiHashAlgorithmSha256Guid, 
                            1, 
                            (const UINT8**)&pPubKeyHndl.Blob,
                            (const UINTN*)&pPubKeyHndl.BlobSize, 
                            Digest);
                err = MemCmp(AmiKey1Hash, pDigest, SHA256_DIGEST_SIZE);
                if(err) {
                    DEBUG((DEBUG_INFO,  "Compare AMI Key1 != FW Key\n"));
                    err = MemCmp(AmiKey21Hash, pDigest, SHA256_DIGEST_SIZE);
                    if(err) {
                        DEBUG((DEBUG_INFO,  "Compare AMI Key21 != FW Key\n"));
                        err = MemCmp(AmiKey22Hash, pDigest, SHA256_DIGEST_SIZE);
                        DEBUG((DEBUG_INFO,  "Compare AMI Key22 %s= FW Key\n", ((!err)?"=":"!")));
                    }
                }
                if(!err) 
                    nError = 1; // Test Key
//            }
        } 
/*
 *  2. Locate PK
 */
        Status = GetEfiVariable(EFI_PLATFORM_KEY_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &Var);
        if(!EFI_ERROR(Status)) {
            // Verify the PK SignatureType GUID
            // Ami Test Rsa2048 key
            // Verify the PK SignatureType GUID
            SigList = (EFI_SIGNATURE_LIST *)Var;
            if (!guidcmp ((EFI_GUID*) &(SigList->SignatureType), &gEfiCertRsa2048Guid) ||
                !guidcmp ((EFI_GUID*) &(SigList->SignatureType), &gEfiCertX509Guid)
            ){
                SigData   = (EFI_SIGNATURE_DATA *) ((UINT8 *) SigList + sizeof (EFI_SIGNATURE_LIST) + SigList->SignatureHeaderSize);
                CertStart = (UINT8*)SigData->SignatureData;
                CertLen = (UINTN)SigList->SignatureSize-sizeof(EFI_GUID);
                Status = mAmiSig->Hash(mAmiSig, 
                        &gEfiHashAlgorithmSha256Guid, 
                        1, 
                        (const UINT8**)&CertStart,
                        (const UINTN*)&CertLen, 
                        Digest);
                err = MemCmp(AmiPkKeyHash1, Digest, SHA256_DIGEST_SIZE);
                if(err) {
                    DEBUG((DEBUG_INFO,  "Compare AMI Key1 != PK\n"));
                    err = MemCmp(AmiPkKeyHash2, Digest, SHA256_DIGEST_SIZE);
                    DEBUG((DEBUG_INFO,  "Compare AMI Key2 %s= PK\n", ((!err)?"=":"!")));
                }
                if(!err) 
                    nError +=2;   // AMI Test PK
            }
        }

        if(Var) pBS->FreePool(Var);
    }
    if (Error || nError)
    {
        if (Error)
        {
            ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_VERIFY_NO_TEST_KEY));
        }
        if((nError & 1) == 1)
        {
            Error = TRUE;
            ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_VERIFY_NO_TEST_KEY1));
        }
        if((nError & 2) == 2)
        {
            Error = TRUE;
            ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_VERIFY_NO_TEST_KEY2));
        }
    }
    else 
    {
        DEBUG((DEBUG_INFO, "Setting *No Test Keys* verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_TEST_KEYS / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_TEST_KEYS % 8));
#endif
    }
}
