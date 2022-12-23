/** @file
  Support for HSTI 1.0 specification, defined at 
  Microsoft Hardware Security Testability Specification.

  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
#ifndef __HSTI_H__
#define __HSTI_H__

#include <Token.h>

#define HSTI_WINDOWS_SECURITY_FEATURE_MAX_BYTES                                        48

#define HSTI_WINDOWS_SECURITY_FEATURE_PLATFORM_SECURE_BOOT                              0 //BIT0
#define HSTI_WINDOWS_SECURITY_FEATURE_SILICON_SECURE_FIRMWARE_UPDATE                    1 //BIT1
#define HSTI_WINDOWS_SECURITY_FEATURE_MOR_BIT_ENABLED                                   2 //BIT2
#define HSTI_WINDOWS_SECURITY_FEATURE_SILICON_NO_TEST_KEY_IN_USE                        3 //BIT3
#define HSTI_WINDOWS_SECURITY_FEATURE_NO_UNAUTHENTICATED_DMA                            4 //BIT4
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_TEST_KEYS                                 5 //BIT5
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_FIRMWARE_ROLLBACK_PROTECTION                 6 //BIT6
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_SECURE_BOOT_BYPASS                        7 //BIT7
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_SHA256_OR_STRONGER_HASH_VALIDATION      8 //BIT8
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_ONLY_RSA2048_OR_STRONG_SIGNATURE_CHECKING    9 //BIT9
#define HSTI_WINDOWS_SECURITY_FEATURE_BIOS_SECURE_FIRMWARE_UPDATE                       10 //BIT10
#define HSTI_WINDOWS_SECURITY_FEATURE_HARDWARE_DEBUGGING_OF_BIOS_DISABLED               11 //BIT11
#define HSTI_WINDOWS_SECURITY_FEATURE_HARDWARE_DEBUGGING_OF_SILICON_DISABLED            12 //BIT12
// Bits 13-127 are reserved

#pragma pack(1)

#define ADAPTER_INFO_PLATFORM_SECURITY_GUID \
  {0x6be272c7, 0x1320, 0x4ccd, { 0x90, 0x17, 0xd4, 0x61, 0x2c, 0x01, 0x2b, 0x25 }}
// AMI PORTING BEGIN
#if defined(HSTI_REVISION) && (HSTI_REVISION == 0)
#define PLATFORM_SECURITY_VERSION_VNEXTCS         0x00000003
#else
#define PLATFORM_SECURITY_VERSION_VNEXTCS         0x00000004
#endif
// AMI PORTING END

#define PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE 0x00000001  // IHV
#define PLATFORM_SECURITY_ROLE_PLATFORM_IBV       0x00000002
#define PLATFORM_SECURITY_ROLE_IMPLEMENTOR_OEM    0x00000003 
#define PLATFORM_SECURITY_ROLE_IMPLEMENTOR_ODM    0x00000004  

typedef struct {
  //
  //  Return PLATFORM_SECURITY_VERSION_VNEXTCS
  //
  UINT32  Version;
  //
  // The role of the publisher of this interface.  Reference platform designers
  // such as IHVs and IBVs are expected to return PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE
  // and PLATFORM_SECURITY_ROLE_PLATFORM_IBV respectively.
  // If the test modules from the designers are unable to fully verify all
  // security features, then the platform implementers, OEMs and ODMs, will
  // need to publish this interface with a role of Implementer.
  //
  UINT32  Role;
  //
  // Human readable vendor, model, & version of this implementation.
  //
  CHAR16  ImplementationID[256];
  //
  // The size in bytes of the SecurityFeaturesImplemented and SecurityFeaturesVerified arrays.
  // The arrays must be the same size.
  //
  UINT32  SecurityFeaturesSize;
// AMI PORTING BEGIN
  //
  // IHV-defined bitfield corresponding to all security features which must be
  // implemented to meet the security requirements defined by PLATFORM_SECURITY_VERSION Version.
  //
//UINT8   SecurityFeaturesRequired[];     //Ignored for non-IHV
// AMI PORTING END
  //
  // Publisher-defined bitfield corresponding to all security features which
  // have implemented programmatic tests in this module.
  //
//UINT8   SecurityFeaturesImplemented[];
  //
  // Publisher-defined bitfield corresponding to all security features which
  // have been verified implemented by this implementation.
  //
//UINT8   SecurityFeaturesVerified[];
// AMI PORTING BEGIN
  //
  // Declareation from HSTI object party that they have implemented and successfully verified 
  // a security feature which maps to the feature specified in the Windows Bitfield
  //
//UINT32   WindowsSecurityFeaturesVerified[],
// AMI PORTING END
  //
  // A Null-terminated string, one failure per line (CR/LF terminated), with a
  // unique identifier that the OEM/ODM can use to locate the documentation
  // which will describe the steps to remediate the failure - a URL to the
  // documentation is recommended.
  //
//CHAR16	ErrorString[];
} ADAPTER_INFO_PLATFORM_SECURITY;

#pragma pack()

extern EFI_GUID gAdapterInfoPlatformSecurityGuid;

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************