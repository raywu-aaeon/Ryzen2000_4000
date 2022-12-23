//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiTseHddSecurity.h
    Header file for the HddPassword

**/

#ifndef _HDD_SECURITY_AMITSE_H_
#define _HDD_SECURITY_AMITSE_H_

#include <Token.h>
#include <PiDxe.h>
#include <AMIVfr.h>
#include <HddSecurityCommon.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PrintLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/BaseLib.h>
#include <Protocol/DevicePath.h>
#include <Protocol/HiiString.h>
#include <Protocol/AmiHddSecurity.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/AMIPostMgr.h>
//AmiIdeBus.h requires BlockIo.h
#include <Protocol/BlockIo.h>
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT == 1))
#ifndef DLINK
typedef struct _AMI_LINK DLINK;
typedef struct _AMI_LIST DLIST;
#endif
#include <Protocol/AmiAhciBus.h>
#endif
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT == 1))
#include <Protocol/AmiNvmeController.h>
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT == 1))
#include <Include/NvmeRstPwdIncludes.h>
#endif
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT == 1) )
#include <Protocol/AmiIdeBus.h>
#endif
#include "AMITSEStrTokens.h"
#if SETUP_SAME_SYS_HDD_PW
#include "Core/em/AMITSE/Inc/PwdLib.h"
#include "Core/em/AMITSE/Inc/variable.h"
#endif

#define     SECURITY_SET_PASSWORD           0xF1
#define     SECURITY_UNLOCK                 0xF2
#define     SECURITY_ERASE_PREPARE          0xF3
#define     SECURITY_ERASE_UNIT             0xF4
#define     SECURITY_FREEZE_LOCK            0xF5
#define     SECURITY_DISABLE_PASSWORD       0xF6
#define     SECURITY_BUFFER_LENGTH          512     // Bytes
#define     HDD_MODEL_NUMBER_LENGTH         39     // Model number is 40 (0-39) bytes
#define     SPACE_ASCII_VALUE               0x20

#ifndef AMI_DXE_BS_EC_INVALID_IDE_PASSWORD
#define AMI_DXE_BS_EC_INVALID_IDE_PASSWORD (EFI_OEM_SPECIFIC | 0x00000005)
#endif

#ifndef DXE_INVALID_IDE_PASSWORD
#define DXE_INVALID_IDE_PASSWORD (EFI_SOFTWARE_DXE_BS_DRIVER | AMI_DXE_BS_EC_INVALID_IDE_PASSWORD)
#endif

#define NG_SIZE                             19
#define VARIABLE_ID_AMITSESETUP             5

#if !defined(SECURITY_SETUP_ON_SAME_PAGE) || SECURITY_SETUP_ON_SAME_PAGE == 0
#define INVALID_HANDLE  ((VOID*)-1)
#endif
extern VOID * gHiiHandle;

#if TSE_BUILD <= 0x1277
extern CHAR16 *HiiGetString (VOID    *handle, UINT16  token);
#else
extern CHAR16 *TseHiiGetString( VOID* handle, UINT16 token );
#endif

extern VOID CheckForKeyHook (EFI_EVENT Event, VOID *Context);
extern UINTN TestPrintLength (IN CHAR16  *String);
extern VOID _DrawPasswordWindow (UINT16  PromptToken, UINTN  PasswordLength, UINTN  *CurrXPos, UINTN  *CurrYPos);
extern VOID _ReportInBox (UINTN PasswordLength, UINT16 BoxToken, UINTN CurrXPos, UINTN CurrYPos, BOOLEAN bWaitForReturn);
extern EFI_STATUS _GetPassword (CHAR16 *PasswordEntered, UINTN PasswordLength, UINTN CurrXPos, UINTN CurrYPos, UINTN *TimeOut);
extern VOID ClearScreen (UINT8 Attrib);
extern EFI_STATUS ShowPostMsgBox (IN CHAR16  *MsgBoxTitle, IN CHAR16  *Message, IN UINT8  MsgBoxType, UINT8 *pSelection);
extern VOID *SaveScreen (VOID);
extern  VOID TSEIDEPasswordCheck ();
extern  VOID MouseRefresh ();
extern VOID *VarGetNvramName (CHAR16    *name, EFI_GUID  *guid, UINT32 *attributes, UINTN  *size);
extern EFI_STATUS VarSetNvramName (CHAR16    *name, EFI_GUID  *guid, UINT32    attributes, VOID  *buffer, UINTN size);
extern UINT16 HiiAddString (VOID    *handle, CHAR16  *string);

#if TSE_BUILD > 0x1206
BOOLEAN 
IsPasswordSupportNonCaseSensitive();

VOID 
UpdatePasswordToNonCaseSensitive(
    CHAR16 *Password, 
    UINTN PwdLength
);
#endif

/** @internal
    Validates the password for the current HDD alone.

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticateHdd (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
);

/** 
    HDD notification function gets called when HddSecurityEnd Protocol get installed.

    @param Event             Event to signal
    @param HddRegContext     Event specific context (pointer to NotifyRegisteration

    @return VOID

**/
VOID
EFIAPI
HddNotificationFunction (
    IN EFI_EVENT                Event,
    IN VOID                     *HddRegContext
);

/** @internal
    Function Unlock the Hdd with Valid Password

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS       Hdd Unlocked successfully
    @retval EFI_NOT_FOUND     Hdd not found.

    @endinternal
**/
EFI_STATUS
IDEPasswordUpdateAllHddWithValidatedPsw (
    IN UINT8                *Password,
    IN VOID                 *Ptr,
    IN BOOLEAN              bCheckUser
);

/** @internal
    Locate the Security Protocols and return the information

    @param VOID

    @retval HDDCount     Count of Hdd connected.

    @endinternal
**/
UINT16
InitHddSecurityInternalDataPtr ();

/** @internal
    Get the internal Data pointer

    @param Index       Index of HDD

    @return VOID

    @endinternal
**/
VOID *
IDEPasswordGetDataPtr (
    IN UINTN                Index
);

/** @internal
    Return the Drive String Name

    @param Controller    The handle of the drive
    @param **wsName      Returned pointer to the drive string

    @retval TRUE     Drive string has been found and is in wsName
    @retval FALSE    Drive string has not been found

    @note  It is the caller's responsibility to deallocate the space used for
           DriveStringName

    @endinternal
**/
BOOLEAN
HddPasswordGetDeviceName (
    IN EFI_HANDLE  Controller,
    IN CHAR16      **DriveStringName
);

/** @internal
    Return the Security Status Information

    @param *HddSecurityProtocol    Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param *ReqStatus              Pointer to Mask security status 
    @param Mask                    Flags for security.
    
    @retval TRUE        Security Status Information is valid.
    @retval FALSE       Unable to get security status     

    @endinternal
**/
BOOLEAN
CheckSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol,
    IN BOOLEAN                     *ReqStatus,
    IN UINT16                      Mask
);

/** @internal
    Validates the password for the current HDD alone.

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticateHdd (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
);

/** @internal
    Hook function to Initialize the structure IDE_SECURITY_CONFIG
    for the HDDs based on the token ALL_HDD_SAME_PW.

    @param *ptrHddSecurityConfig     Pointer to IDE_SECURITY_CONFIG
    @param value                     Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
IDEUpdateConfig (
    IN VOID             *ptrHddSecurityConfig,
    IN UINTN            Value
);

/** @internal
    Function to search TSE hard disk field.

    @param *pbCheckUser       Password type - User/Master
    @param *pEnabledBit       Password is set/not
    @param *pHardDiskNumber   HDD index
    @param *data              Pointer to data.

    @return VOID
    @endinternal
**/
VOID
SearchTseHardDiskField (
    IN  OUT BOOLEAN         *pbCheckUser,
    IN  OUT BOOLEAN         *pEnabledBit,
    IN  OUT UINT8           *pHardDiskNumber,
    IN  VOID                *data
);

/** @internal
    Validates the password for the current HDD alone.

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticateHdd (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
);

/** @internal
    Hook function to validate Password for the HDDs based on
    the token ALL_HDD_SAME_PW

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.

    @return EFI_SUCCESS         Password for current HDD is validated successfully.
    @return EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticate (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
);
#endif 

