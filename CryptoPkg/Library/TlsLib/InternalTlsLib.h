//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Internal include file for TlsLib.

Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __INTERNAL_TLS_LIB_H__
#define __INTERNAL_TLS_LIB_H__

#undef _WIN32
#undef _WIN64

#include <Token.h>                //APTIOV OVERRIDE
#include <Library/BaseCryptLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#if MDE_PKG_VERSION > 18         //APTIOV OVERRIDE
#include <Library/SafeIntLib.h>    
#endif                           //APTIOV OVERRIDE
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

typedef struct {
  //
  // Main SSL Connection which is created by a server or a client
  // per established connection.
  //
  SSL                             *Ssl;
  //
  // Memory BIO for the TLS/SSL Reading operations.
  //
  BIO                             *InBio;
  //
  // Memory BIO for the TLS/SSL Writing operations.
  //
  BIO                             *OutBio;
} TLS_CONNECTION;

#endif

