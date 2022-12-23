//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiTlsCertificate.h
	Contains interfaces to access the TLS Certificates.
**/

#ifndef _AMI_TLS_CERTIFICATE_H_
#define _AMI_TLS_CERTIFICATE_H_

#define AMITLSCERTIFICATE_PROTOCOL_VERSION 1

#define AMITLSCERTIFICATE_PROTOCOL_GUID \
  { \
    0x870a69cf, 0xda97, 0x4da9, 0x85, 0xa, 0x4d, 0x76, 0xe4, 0xd, 0x22, 0x93 } \
  }

typedef struct _AMI_TLS_CERTIFICATE_PROTOCOL AMI_TLS_CERTIFICATE_PROTOCOL;

/**
  List the TLS Certificates

  @param[in]   	AMI_TLS_CERTIFICATE_PROTOCOL*   This
  @param[out]   CertificateDataSize Size of the buffer Data in bytes.
  @param[out]   X509CertificateData The buffer contains certificate information.

  @retval EFI_SUCCESS             The TLS Certificates list provided.
  @retval EFI_NOT_FOUND           No TLS Certificates found.
**/
typedef
EFI_STATUS
(EFIAPI *AMI_TLS_CERTIFICATE_LIST)(
        IN AMI_TLS_CERTIFICATE_PROTOCOL	*This,
        OUT UINTN                      	*CertificateDataSize,
        OUT VOID						**X509CertificateData
);

/**
  Set the TLS Certificate data to TLS Certificate NVRAM Variable
  @param[in]   This               Pointer to the AMI_TLS_CERTIFICATE_PROTOCOL instance.
  @param[in]   EFI_GUID			  OwnerGuid
  @param[in]   DataSize           Size of the buffer pointed to by Data in bytes.
  @param[in]   CertificateData    The data buffer in the form of x509 Certificate.

  @retval EFI_SUCCESS             The specified certificate set successfully.
  @retval EFI_INVALID_PARAMETER   One or more of the following are TRUE:
                                  This is NULL.
                                  Data is NULL.
                                  DataSize is Zero.
  @retval EFI_DEVICE_ERROR		  The variable could not be saved due to a hardware failure.
**/
typedef
EFI_STATUS
(EFIAPI *AMI_TLS_CERTIFICATE_ENROLL) (
  IN AMI_TLS_CERTIFICATE_PROTOCOL  	*This,
  EFI_GUID							OwnerGuid,
  IN UINTN                          CertificateDataSize,
  IN VOID 							*CertificateData
  );

/**
  Delete the TLS Ceritificates

  @param[in]   AMI_TLS_CERTIFICATE_PROTOCOL*   This
  @param[in]   EFI_GUID						OwnerGuid
  @retval EFI_SUCCESS             The TLS Certificates in NV Variable deleted.
  @retval EFI_NOT_FOUND           The certificate with OwnerGuid not found.
  @retval EFI_DEVICE_ERROR		  The variable could not be deleted due to a hardware failure.
**/
typedef
EFI_STATUS
(EFIAPI *AMI_TLS_CERTIFICATE_DELETE)(
    IN AMI_TLS_CERTIFICATE_PROTOCOL		*This,
    EFI_GUID							OwnerGuid
);

/**
  Delete all the TLS Ceritificates

  @param[in]   AMI_TLS_CERTIFICATE_PROTOCOL*   This
  @retval EFI_SUCCESS             All the TLS Certificates in NV Variable deleted.
  @retval EFI_NOT_FOUND           TLS Certificate NV Variable Not found.
  @retval EFI_DEVICE_ERROR		  The variable could not be deleted due to a hardware failure.
**/
typedef
EFI_STATUS
(EFIAPI *AMI_TLS_CERTIFICATE_DELETE_ALL)(
    IN AMI_TLS_CERTIFICATE_PROTOCOL		*This
);

///
/// The AMI_TLS_CERTIFICATE_PROTOCOL is designed to update the TLS Certificate
/// used for the HTTPS Communication.
///
struct _AMI_TLS_CERTIFICATE_PROTOCOL {
    UINTN                     				Version;
    AMI_TLS_CERTIFICATE_LIST				GetCertificateList;
    AMI_TLS_CERTIFICATE_ENROLL				EnrollCertificate;
    AMI_TLS_CERTIFICATE_DELETE				DeleteCertificate;
    AMI_TLS_CERTIFICATE_DELETE_ALL			DeleteAllCertificates;
};

extern EFI_GUID gAMITLSCertificateProtocolGuid;

#endif
