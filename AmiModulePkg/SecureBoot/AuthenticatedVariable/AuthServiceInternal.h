//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
    AuthServiceInternal.h: Implement authentication services for the authenticated variable
    service in UEFI2.2+
**/
/** @file
  The internal header file includes the common header files, defines
  internal structure and functions used by AuthService module.

  Caution: This module requires additional review when modified.
  This driver will have external input - variable data. It may be input in SMM mode.
  This external input must be validated carefully to avoid security issue like
  buffer overflow, integer overflow.
  Variable attribute should also be checked to avoid authentication bypass.
     The whole SMM authentication variable design relies on the integrity of flash part and SMM.
  which is assumed to be protected by platform.  All variable code and metadata in flash/SMM Memory
  may not be modified without authorization. If platform fails to protect these resources,
  the authentication service provided in this driver will be broken, and the behavior is undefined.

Copyright (c) 2009 - 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _AUTHSERVICE_INTERNAL_H_
#define _AUTHSERVICE_INTERNAL_H_

#include <Token.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>

#include <AmiDxeLib.h>
#include "NVRAM/NVRAM.h"
#include <Protocol/AmiDigitalSignature.h>
#include <SecureBoot.h>
#include <AmiSecureBootLib.h>

#include <Efi.h>
// All are EDKII defined headers
//#include "WinCertificate.h"
#include <Protocol/Hash.h>

#define HASH_SHA256_LEN                   sizeof(EFI_SHA256_HASH)     // 32
#define HASH_SHA512_LEN                   sizeof(EFI_SHA512_HASH)     // 64
#define HASH_SHA1_LEN                     sizeof(EFI_SHA1_HASH)
#define RSA2048_PUB_KEY_LEN               DEFAULT_RSA_KEY_MODULUS_LEN // 256
#define EFI_CERT_TYPE_RSA2048_SHA256_SIZE RSA2048_PUB_KEY_LEN
//#define EFI_CERT_TYPE_RSA2048_SIZE        RSA2048_PUB_KEY_LEN

///
/// Size of AuthInfo prior to the data payload
///
#define AMI_AUTHINFO_SIZE(Cert) (((UINTN)(((EFI_VARIABLE_AUTHENTICATION *) Cert)->AuthInfo.Hdr.dwLength)) + sizeof(UINT64))
#define AMI_AUTHINFO_2_SIZE(Cert) (((UINTN)(((EFI_VARIABLE_AUTHENTICATION_2 *) Cert)->AuthInfo.Hdr.dwLength)) + sizeof(EFI_TIME))
#define OFFSET_OF_AUTHINFO2_CERT_DATA ((OFFSET_OF (EFI_VARIABLE_AUTHENTICATION_2, AuthInfo)) + (OFFSET_OF (WIN_CERTIFICATE_UEFI_GUID, CertData)))

#ifdef EFI_DEBUG
#define AVAR_TRACE(Arguments) { if (!IsNvramRuntime()) DEBUG(Arguments); }
// do not check in with next line un-commented
//#define AVAR_TRACE(Arguments) { DEBUG(Arguments); }
#else
#define AVAR_TRACE(Arguments)
#endif

typedef enum {
    IsPkVarType = 0,
    IsKekVarType,
    IsDbVarType,
    IsDbrVarType,
    IsPrivateVarType
} AUTHVAR_TYPE;

typedef enum { 
  SecureBootModeTypeUserMode,
  SecureBootModeTypeSetupMode,
  SecureBootModeTypeAuditMode,
  SecureBootModeTypeDeployedMode,
  SecureBootModeTypeMax
} SECURE_BOOT_MODE_TYPE;

//
// Record status info of Customized Secure Boot Mode.
//
typedef struct {
  ///
  /// AuditMode variable value
  ///
  UINT8   AuditMode;
  ///
  /// AuditMode variable RW
  ///
  BOOLEAN IsAuditModeRO;
  ///
  /// DeployedMode variable value
  ///
  UINT8   DeployedMode;
  ///
  /// AuditMode variable RW
  ///
  BOOLEAN IsDeployedModeRO;
  ///
  /// SetupMode variable value
  ///
  UINT8   SetupMode;
  /// 
  /// SetupMode is always RO. Skip IsSetupModeRO;
  ///
  ///
  /// SecureBoot variable value
  ///
  UINT8   SecureBoot;
} SECURE_BOOT_MODE;

#define VENDOR_KEYS_VALID             1
#define VENDOR_KEYS_MODIFIED          0

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AuthService Entry functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
   Initialize Secure Boot variables.
   This function calls InitAuthServiceCallback to initialize 
   DigitalSigProtocol not in SMM by trying to Locate
   DigitalSigProtocol. If Protocol is not installed yet 
   RegisterProtocolCallback will be called.

  @retval none 

**/
VOID AuthVariableServiceInit ( VOID );
VOID AuthVariableServiceInitSMM (VOID );

EFI_STATUS VerifyVariable (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32   *Attributes,
    IN VOID    **Data,
    IN UINTN    *DataSize, 
    IN VOID     *OldData,
    IN UINTN     OldDataSize,
    IN OUT EXT_SEC_FLAGS *ExtFlags
    );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Misc auxiliary functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
EFI_STATUS AuthServiceInternalFindVariable (
    IN  CHAR16            *VariableName,
    IN  EFI_GUID          *VendorGuid,
    OUT UINT32            *Attributes,
    OUT VOID              **Data,
    OUT UINTN             *DataSize
    );

EFI_STATUS AuthServiceInternalUpdateVariable (
    IN CHAR16             *VariableName,
    IN EFI_GUID           *VendorGuid,
    IN UINT32             Attributes,
    IN VOID               *Data,
    IN UINTN              DataSize
    );

EFI_STATUS AuthServiceInternalSetVariable (
    IN CHAR16             *VariableName,
    IN EFI_GUID           *VendorGuid,
    IN UINT32             Attributes,
    IN VOID               *Data,
    IN UINTN              DataSize
    );

BOOLEAN AuthVariablePhysicalUserOverride (
    VOID 
    ) ;
BOOLEAN PhysicalUserPresent (
    VOID 
    ) ;
BOOLEAN InCustomSecureBootMode (
    VOID
    );
BOOLEAN GetPkPresent (
    VOID 
    );
EFI_STATUS UpdateSecureBootMode(
    IN  SECURE_BOOT_MODE_TYPE  NewMode
    );
EFI_STATUS UpdateTransitionMode(
    IN  SECURE_BOOT_MODE_TYPE  NewMode
    );
EFI_STATUS GetmSecureBootSetup (
    VOID 
    );
INTN StrCmp16 ( 
    IN CHAR16 *Dest, CHAR16 *Src
    );
UINTN StrSize16 (
    IN CHAR16 *String
    );
BOOLEAN IsPkVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );
BOOLEAN IsKekVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );
BOOLEAN IsVendorKeysVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );
BOOLEAN IsDbVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );
BOOLEAN IsDbrVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
    );
BOOLEAN IsDeploymentModeVar(
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid
);
EFI_STATUS IsAppendToSignatureDb (
    IN VOID     *Data,
    IN UINTN    *DataSize,
    IN VOID     *SigDB,
    IN UINTN     SigDBSize
    );
EFI_STATUS VendorKeyIsModified (
    VOID
    );
EFI_STATUS AfterPkVarProcess ( 
    VOID 
    );
EFI_STATUS SetSecureBootVariablesHook ( 
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
    );
EFI_STATUS SetDeploymentModeVarHook ( 
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
    );
EFI_STATUS SetSecureBootSetupVarHook ( 
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
    );
EFI_STATUS SetAuthServicesNVVarHook ( 
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
    );
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NVRAM module defined auxiliary functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOLEAN IsNvramRuntime(
    VOID
    );
EFI_STATUS FindVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID **Data
    );
EFI_STATUS DxeSetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
    );
EFI_STATUS DxeGetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes OPTIONAL,
    IN OUT UINTN *DataSize, OUT VOID *Data
    );
EFI_STATUS AuthServiceInternalFindVariable(
    IN  CHAR16 *VariableName, IN  EFI_GUID *VendorGuid,
    OUT UINT32 *Attributes, 
    OUT VOID  **Data, OUT UINTN *DataSize
);
EFI_STATUS UpdateNonNvVariableInPlace(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINTN DataSize, IN VOID *Data
);

#endif
