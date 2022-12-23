/** @file
  This file defines TlsCaCertificate variable.

Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __TLS_AUTHENTICATION_H__
#define __TLS_AUTHENTICATION_H__

// Private variable for CA Certificate configuration
//
#define EFI_TLS_CA_CERTIFICATE_GUID \
  { \
    0xfd2340D0, 0x3dab, 0x4349, { 0xa6, 0xc7, 0x3b, 0x4f, 0x12, 0xb4, 0x8e, 0xae } \
  }

#define EFI_TLS_CA_CERTIFICATE_VARIABLE       L"TlsCaCertificate"

#define TLS_RECORD_HEADER_LENGTH   5

//
// The length (in bytes) of the TLSPlaintext records payload MUST NOT exceed 2^14.
// Refers to section 6.2 of RFC5246. 
//
#define TLS_PLAINTEXT_RECORD_MAX_PAYLOAD_LENGTH   16384

//
// The length (in bytes) of the TLSCiphertext records payload MUST NOT exceed 2^14 + 2048.
// Refers to section 6.2 of RFC5246. 
//
#define TLS_CIPHERTEXT_RECORD_MAX_PAYLOAD_LENGTH   18432

extern EFI_GUID gEfiTlsCaCertificateGuid;

#endif

