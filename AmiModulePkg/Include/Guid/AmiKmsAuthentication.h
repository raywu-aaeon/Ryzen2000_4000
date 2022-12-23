//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************
/** @file
    AMI KMS Authentication variable definitions
**/
#ifndef __AMI_KMS_AUTHENTICATION__H__
#define __AMI_KMS_AUTHENTICATION__H__

#define AMI_KMS_CLIENT_CERTIFICATE_VAR L"KmsClientCertificate"
#define AMI_KMS_CLIENT_PRIVATE_KEY_VAR  L"KmsClientPrivateKey"
#define AMI_KMS_CA_CERTIFICATE_VAR     L"KmsCAcertificate"

extern EFI_GUID gAmiKmsClientCertificateGuid;
extern EFI_GUID gAmiKmsClientPrivateKeyGuid;
extern EFI_GUID gAmiKmsCaCertificateGuid;

#endif