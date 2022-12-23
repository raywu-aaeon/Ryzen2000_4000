//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  This file contains the test for Crypto Strength
 */

#include <AmiHsti.h>
#include <Protocol/AmiDigitalSignature.h>
#include "AmiCertificate.h"
//#include <../CryptoLib/x509v3.h>
//#include <../CryptoLib/includes.h>
//#include <../CryptoLib/common.h>

extern EFI_GUID gEfiGlobalVariableGuid;

extern CHAR16 ImplementationId[];

static AMI_DIGITAL_SIGNATURE_PROTOCOL *mAmiSig = NULL;
static UINT8 *gDstAddress = NULL;
static UINTN  gHeapSize   = CR_DXE_MAX_HEAP_SIZE;

/*
 * Common Crypto & security test routines
 */ 
BOOLEAN VerifyX509keyStrength(UINT8* Cert, UINTN CertLen)
{
// * if x509 - parse it and check = public_key_len or 
// * signature_alg ! = 1 2 840 113549 1 1 [5] (Sha1Rsa)
// * signature_alg[6] >=  1 2 840 113549 1 1 [11] (Sha256)
    UINT8               *Key;
    UINTN               KeyLen;
    INTN                err;
    EFI_STATUS 			Status;

//    struct x509_certificate *x509TrustCert;
    
    if(gDstAddress == NULL) {
        Status = gBS->AllocatePool(EfiRuntimeServicesData, gHeapSize, (void**)&gDstAddress);
        if(EFI_ERROR(Status)) {
            return FALSE;
        }
        InitCRmm( (void*)gDstAddress, gHeapSize);
    }
    ResetCRmm();
    err = Pkcs7_x509_return_Cert_pubKey(Cert, (size_t)CertLen, &Key, (size_t*)&KeyLen);

    if(!err && KeyLen >= DEFAULT_RSA_KEY_MODULUS_LEN)
        return TRUE;
    DEBUG((DEBUG_ERROR, "Error %x, x509 key len %x < RSA2048(%x)\n", err, KeyLen, DEFAULT_RSA_KEY_MODULUS_LEN));
/////    
//    x509TrustCert = x509_certificate_parse(Cert, CertLen);
//    if(x509TrustCert &&
//        x509TrustCert->public_key_len >= DEFAULT_RSA_KEY_MODULUS_LEN &&
//        x509TrustCert->signature_alg[6] >= 11)
//    {
//        return TRUE; 
//    } 
/////    
    return FALSE;
}


VOID EFIAPI FirmwareTrustCryptoStrength( VOID )
{
    UINT8 TestBit;
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
//    UINT8            Byte;
    EFI_SIGNATURE_LIST *SigList;
    EFI_SIGNATURE_DATA *SigData;


    TestBit = PcdGet8(AmiPcdHstiCryptoStrengthImplementationBit);
    
    
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "CryptoStrength BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));
    
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "CryptoStrength is not implemented\r\n"));
        return; // no verification bits should be set
    }
    
    
    // Test Crypto Strength 
/*
 *  
 * locate mAmiSig
 * test FwKey from the Hob for strength.
 * if x509 - parse it and check = public_key_len or 
 * signature_alg ! = 1 2 840 113549 1 1 [5] (Sha1Rsa
 * signature_alg[6] >=  1 2 840 113549 1 1 [11] (Sha256)
 * 
 * same test with the PK
 * 
 *  struct x509_certificate *x509TrustCert;
 *  struct x509_certificate *x509_certificate_parse(const u8 *buf, size_t len);
 *  x509TrustCert = x509_certificate_parse(TrustedCert, CertSize);
 *  x509TrustCert->public_key_len
 *  x509TrustCert->signature_alg[6] == 11 , != 5
 * 
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
//                // check If dummy key - return Mode = 0
//            Byte = pPubKeyHndl.Blob[0];
//            for(Size = 1; Size < pPubKeyHndl.BlobSize && (Byte == pPubKeyHndl.Blob[Size]); Size++);
//            if(Size == pPubKeyHndl.BlobSize) {
//                nError = 1;  // Dummy Fw Key. Generic error
//            }
//            if(!nError)
//            {
                if(!guidcmp(&pPubKeyHndl.AlgGuid, &gEfiCertX509Guid))
                {
                    nError = VerifyX509keyStrength(pPubKeyHndl.Blob, pPubKeyHndl.BlobSize)?0:1;
                } else {
                	if(guidcmp(&pPubKeyHndl.AlgGuid, &gEfiCertRsa2048Guid) && 
                	   guidcmp(&pPubKeyHndl.AlgGuid, &gEfiCertSha256Guid)
                	)
                		nError = 1; // Not valid format of a FW key
                }
//            }
        }

/*
 *  2. Locate PK
 */
        Status = GetEfiVariable(EFI_PLATFORM_KEY_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &Var);
        if(!EFI_ERROR(Status)) {
            // Verify the PK SignatureType GUID
            SigList = (EFI_SIGNATURE_LIST *)Var;
//             DEBUG((-1, "PK SignatureType %g\n",  &(SigList->SignatureType)));
            if (!guidcmp ((EFI_GUID*) &(SigList->SignatureType), &gEfiCertX509Guid)
            ){
                SigData   = (EFI_SIGNATURE_DATA *) ((UINT8 *) SigList + sizeof (EFI_SIGNATURE_LIST) + SigList->SignatureHeaderSize);
                nError = VerifyX509keyStrength((UINT8*)SigData->SignatureData, (UINTN)SigList->SignatureSize-sizeof(EFI_GUID))?nError:nError+2;
            } else {
            	if (guidcmp ((EFI_GUID*) &(SigList->SignatureType), &gEfiCertRsa2048Guid))
            	{
            		nError += 2; // not supported by Aptio format of a PK
            	}
            }
        }
        if(Var) pBS->FreePool(Var);
    }
    if (Error || nError)
    {
    	if (Error )
    	{
    	    // Error is already TRUE no need to set it here
    	    // report error
    	    ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_CRYPTO_STRENGTH));
    	}
        if((nError & 1) == 1)
        {
            Error = TRUE;
            ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_CRYPTO_STRENGTH1));
        }
        if((nError & 2) == 2)
        {
            Error = TRUE;
            ReportError(TestBit, 0, STRING_TOKEN(AMI_HSTI_ERROR_CRYPTO_STRENGTH2));
        }
    }
    else 
    {
        DEBUG((DEBUG_INFO, "Setting Platform Security verification bits\n\r"));
        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_SHA256_OR_STRONGER_HASH_VALIDATION / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_SHA256_OR_STRONGER_HASH_VALIDATION % 8));
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_RSA2048_OR_STRONG_SIGNATURE_CHECKING / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_RSA2048_OR_STRONG_SIGNATURE_CHECKING % 8));
#endif
    }

}

