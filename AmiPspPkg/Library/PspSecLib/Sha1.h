//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file sha1.h
    Header file for sha1.c

**/
#ifndef _SHA1_H_
#define _SHA1_H_

//#include "token.h"


#define SHA1_160_HASH_LEN       0x14

typedef struct _SHA1_DIGEST{
  UINT8                             digest[SHA1_160_HASH_LEN];
} SHA1_DIGEST;

typedef struct __SHA1_CTX
{
    UINT8 M[64];
    SHA1_DIGEST Digest;
    EFI_STATUS Status;
    UINT64     Length;
    UINTN      Count;
} SHA1_CTX;

typedef struct _PEIM_SHA
{
    UINT32  Hash[5];
    UINT32  Length;
    UINT32  Mark;
    UINT32  Start;
} PEIM_SHA;

VOID
ShaWrap(
    VOID
);

EFI_STATUS
__stdcall Sha1Init (
  IN    SHA1_CTX    *Sha1Ctx
);

EFI_STATUS
__stdcall Sha1Update (
  IN    SHA1_CTX    *Sha1Ctx,
  IN    VOID        *Data,
  IN    UINTN       DataLen
);

EFI_STATUS
__stdcall Sha1Final (
  IN    SHA1_CTX    *Sha1Ctx,
  OUT   SHA1_DIGEST **Digest
);

#endif  // _SHA1_H_

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************