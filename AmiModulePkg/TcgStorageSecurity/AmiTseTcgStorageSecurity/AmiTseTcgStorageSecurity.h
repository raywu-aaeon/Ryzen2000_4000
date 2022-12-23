//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
//***********************************************************************

/** @file AmiTseTcgStorageSecurity.h
    AMITSE related includes and defines for OPAL password support.

**/

#ifndef _AMI_TSE_TCG_STORAGE_SECURITY_H_
#define _AMI_TSE_TCG_STORAGE_SECURITY_H_

//---------------------------------------------------------------------------

#include "AMITSEStrTokens.h"

//---------------------------------------------------------------------------

#define     SECURITY_SET_PASSWORD           0xF1
#define     SECURITY_UNLOCK                 0xF2
#define     SECURITY_ERASE_PREPARE          0xF3
#define     SECURITY_ERASE_UNIT             0xF4
#define     SECURITY_FREEZE_LOCK            0xF5
#define     SECURITY_DISABLE_PASSWORD       0xF6
#define     SECURITY_BUFFER_LENGTH          512     // Bytes

#ifndef AMI_STATUS_CODE_CLASS
#define AMI_STATUS_CODE_CLASS   EFI_OEM_SPECIFIC //0x8000
#endif

#ifndef AMI_DXE_BS_EC_INVALID_IDE_PASSWORD
  #define AMI_DXE_BS_EC_INVALID_IDE_PASSWORD (AMI_STATUS_CODE_CLASS\
                                              | 0x00000005)
#endif

#ifndef DXE_INVALID_IDE_PASSWORD
  #define DXE_INVALID_IDE_PASSWORD (EFI_SOFTWARE_DXE_BS_DRIVER\
                                    | AMI_DXE_BS_EC_INVALID_IDE_PASSWORD)
#endif

#define NG_SIZE                     19
#define VARIABLE_ID_AMITSESETUP     5

#define TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC                                96
#define ACPI_FUNCTION_GET_USER_CONFIRMATION_STATUS_FOR_REQUEST          8

#define AMI_TCG_CONFIRMATION_FLAGS_GUID \
    {0x7d3dceee, 0xcbce, 0x4ea7, {0x87, 0x09, 0x6e, 0x55, 0x2f, 0x1e, 0xdb, 0xde}}

typedef struct
{
    UINT32 RQST;                 //Store PPI request
    UINT32 RCNT;                 //Store most recent PPI request
    UINT32 ERROR;                //Store BIOS ERROR information after a PPI request
    UINT32 Flag;                 //Flag used by PPI SMM interface to determine PPI function request
    UINT32 AmiMisc;              //Misc storage not used
    UINT32 OptionalRqstData;     //Store optional data that OS might provide during a PPI request
    UINT32 RequestFuncResponse;  //Store Response of function request. Returned to caller
} AMI_ASL_PPI_NV_VAR;

extern VOID * gHiiHandle;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE *gST;

extern VOID *VarGetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 *attributes, UINTN *size );
extern EFI_STATUS VarSetNvramName( CHAR16 *name, EFI_GUID *guid, UINT32 attributes, VOID *buffer, UINTN size );
extern VOID MemFreePointer (VOID **ptr);
extern VOID MemCopy( VOID *dest, VOID *src, UINTN size );
extern UINT16 HiiAddString( /*EFI_HII_HANDLE*/VOID* handle, CHAR16 *string );
extern VOID    CheckForKeyHook( EFI_EVENT Event, VOID *Context );
extern UINTN TestPrintLength ( IN CHAR16   *String );
extern VOID _DrawPasswordWindow(UINT16 PromptToken, UINTN PasswordLength, UINTN *CurrXPos, UINTN *CurrYPos);
extern VOID _ReportInBox(UINTN PasswordLength, UINT16 BoxToken, UINTN CurrXPos, UINTN CurrYPos, BOOLEAN bWaitForReturn);
extern EFI_STATUS _GetPassword(CHAR16 *PasswordEntered, UINTN PasswordLength, UINTN CurrXPos, UINTN CurrYPos, UINTN *TimeOut);
extern VOID    ClearScreen( UINT8 Attrib );
extern EFI_STATUS ShowPostMsgBox(IN CHAR16  *MsgBoxTitle,IN CHAR16  *Message,IN UINT8  MsgBoxType, UINT8 *pSelection);
extern VOID    *SaveScreen( VOID );
#if TSE_BUILD <= 0x1277
extern CHAR16 *HiiGetString( VOID* handle, UINT16 token );
#else
extern CHAR16 *TseHiiGetString( VOID* handle, UINT16 token );
#endif

#if TSE_BUILD > 0x1206
BOOLEAN 
IsPasswordSupportNonCaseSensitive(
);
VOID 
UpdatePasswordToNonCaseSensitive(
        CHAR16 *Password, 
        UINTN PwdLength
);
#endif
EFI_STRING
TcgSecurityHiiGetString (
  EFI_HII_HANDLE  HiiHandle,
  EFI_STRING_ID   StringId
);

VOID
TcgNotificationFunction (
    EFI_EVENT   Event,
    VOID 		*HddRegContext
);

#if FREEZE_LOCK_OPAL
VOID
TcgStorageReadyToBootNotification (
    EFI_EVENT   Event,
    VOID 		*Context
);
#endif 

EFI_STATUS
TCGPasswordUpdateAllHddWithValidatedPsw (
    UINT8   *Password,
    VOID    *Ptr,
    BOOLEAN bCheckUser
);

VOID
TCGPasswordCheck (
    VOID
);

UINT16
InitTcgSecurityInternalDataPtr(
);

VOID* 
TCGPasswordGetDataPtr( 
        UINTN Index
);

BOOLEAN
OpalPasswordGetDeviceName (
    EFI_HANDLE Controller,
    CHAR16 **DriveStringName
);

BOOLEAN
CheckOpalSecurityStatus (
    AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol,
    BOOLEAN                     *Locked,
    UINT16                      Mask
);

EFI_STATUS
TCGPasswordAuthenticateHdd (
    CHAR16      *Password,
    VOID        * Ptr,
    BOOLEAN     bCheckUser
);

VOID
TCGUpdateConfig (
    VOID  *TempideSecConfig,
    UINTN value
);

VOID TCGUpdateConfigAllHdd(
    VOID  *TempideSecConfig,
    UINTN value 
);

VOID
SearchTseHardDiskField (
    IN  OUT BOOLEAN *pbCheckUser,
    IN  OUT BOOLEAN *pEnabledBit,
    IN  OUT UINT8   *pHardDiskNumber,
    IN  VOID        *data
);


EFI_STATUS
TCGPasswordAuthenticate (
    CHAR16  *Password,
    VOID*   Ptr,
    BOOLEAN bCheckUser
);

EFI_STATUS
EfiLibReportStatusCode (
    IN EFI_STATUS_CODE_TYPE     Type,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA     *Data     OPTIONAL
  );

VOID *
EfiLibAllocateZeroPool (
    IN  UINTN   AllocationSize
);

UINTN
SPrint (
    OUT CHAR16        *Buffer,
    IN  UINTN         BufferSize,
    IN  CONST CHAR16  *Format,
  ...
  );
#if TCG_STORAGE_SEC_SETUP_SAME_SYS_PW
VOID
TcgStorageSecSetupSameSysPw (
    IN EFI_EVENT  Event,
    IN VOID       *Context
);
#endif
#endif 


