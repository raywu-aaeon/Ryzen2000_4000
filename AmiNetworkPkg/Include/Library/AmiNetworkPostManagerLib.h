//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//*************************************************************************
/** @file AmiNetworkPostManagerLib.h
    AmiNetworkPostManagerLib Definitions

**/
//*************************************************************************

#include <Protocol/LoadFile.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/NetLib.h>
#include <Library/UefiLib.h>

#ifndef _AMI_NETWORK_POSTMANAGER_LIB_H_
#define _AMI_NETWORK_POSTMANAGER_LIB_H_

#define PXEBC_CHECK_MEDIA_WAITING_TIME        EFI_TIMER_PERIOD_SECONDS(20)
#define HTTP_BOOT_CHECK_MEDIA_WAITING_TIME    EFI_TIMER_PERIOD_SECONDS(20)

extern EFI_GUID gReadyToPxeBootGuid;        // For pre PXE boot
/**
  This function create pop-up Message 

  @param[in] String            The message in the pop-up.

  @retval VOID

**/

VOID 
AMICreatePopUp(
    IN  CHAR16          *String
);

/**
  This function create pop-up Message 

  @param[in] MsgTitle          Title of the pop-up box.
  @param[in] String            The message in the pop-up.

  @retval VOID

**/
VOID 
AMICreatePopUpEx(
    IN  CHAR16          *MsgTitle,
    IN  CHAR16          *String
);

/**
  This function create pop-up Message 

  @param[in] String            The message in the pop-up.

  @retval VOID

**/

VOID 
AMIPrintText(
    IN  CHAR16          *String
);

/**
  This function used for switch to post screen 

  @retval VOID

**/

VOID 
AMISwitchToPostScreen (
);

/**
  This function clears graphics screen 

  @param  VOID

  @retval VOID

**/

VOID 
ClearGraphicsScreen (
  VOID
);

/**
  Check for invalid character in IP address.

  @param  IpSource               A pointer to a Null-terminated 
                                 Unicode string.

  @return EFI_SUCCESS            If invalid characters are not present
  @return EFI_INVALID_PARAMETER  If in valid characters are present

**/

EFI_STATUS
CheckInvalidCharinIpAddress (
  IN CONST CHAR16       *IpSource,
  IN UINT8              IpMode
);

/**
  Retrieves a string from a string package in a specific language.  If the language
  is not specified, then a string from a string package in the current platform 
  language is retrieved.  If the string can not be retrieved using the specified 
  language or the current platform language, then the string is retrieved from 
  the string package in the first language the string package supports.  The 
  returned string is allocated using AllocatePool().  The caller is responsible 
  for freeing the allocated buffer using FreePool().
  
  If HiiHandle is NULL, then ASSERT().
  If StringId is 0, then ASSET.

  @param[in]  HiiHandle  A handle that was previously registered in the HII Database.
  @param[in]  StringId   The identifier of the string to retrieved from the string 
                         package associated with HiiHandle.
  @param[in]  Language   The language of the string to retrieve.  If this parameter 
                         is NULL, then the current platform language is used.  The 
                         format of Language must follow the language format assumed 
                         the HII Database.

  @retval NULL   The string specified by StringId is not present in the string package.
  @retval Other  The string was returned.

**/

EFI_STRING
EFIAPI
HiiGetString (
  IN EFI_HII_HANDLE  HiiHandle,
  IN EFI_STRING_ID   StringId,
  IN CONST CHAR8     *Language  OPTIONAL
);

/**
  Gets the string form Supported language. If it fails, gets the 
  string from Default language.

    @param HiiHandle StringId Language

    @retval String 
 
**/

CHAR16* NetLibHiiGetString( 
  EFI_HII_HANDLE HiiHandle, 
  EFI_STRING_ID StringId,
  CHAR8 *Language
);

VOID NotifyPrePxeBoot(EFI_LOAD_FILE_PROTOCOL    *ThisCopy);

/**

     Check media status before PXE start and add the console status messages.
 
     @param[in]  This               Protocol instance pointer.
     @param[in]  Controller         The handle where network service binding protocols are installed on.
     @param[in]  MediaDetectCount   Number of media detected.
                        
**/
EFI_STATUS 
PxeCheckMediaState(
        IN EFI_LOAD_FILE_PROTOCOL          *This,
        IN EFI_HANDLE                      Controller,
        IN UINT8                           MediaDetectCount
);

/**
    Checks for ESC key stroke within given no. of seconds by introducing 
    100ms delay for each iteration. Returns EFI_ABORTED, if ESC key is pressed
    within given time else returns EFI_SUCCESS.

    @param 
        UINT8  NumberOfSeconds - No.of seconds

         
    @retval EFI_SUCCESS If ESC key is not pressed with in given time.
    @retval EFI_ABORTED If ESC key is pressed with in given time.


**/
EFI_STATUS
HandleEscKeytoAbortPxeBoot (
  IN UINT8  NumberOfSeconds 
);

/**
  Display the MAC address on PXE boot screen.

  @param[in]  Mac        The pointer to the Mac address.

**/
VOID
PxeBootShowMacAddr (
  IN EFI_MAC_ADDRESS   *Mac
);

/**

     Check media status before HTTP start and add the console status messages.
 
     @param[in]  This               Protocol instance pointer.
     @param[in]  Controller            The handle where network service binding protocols are installed on.
     @param[in]  MediaDetectCount   Number of media detected.
                        
**/

EFI_STATUS 
HttpCheckMediaState(
        IN EFI_LOAD_FILE_PROTOCOL   *This,
        IN EFI_HANDLE               Controller,
        IN UINT8                    MediaDetectCount
);

/**

    Catch ESC to abort.
    Read the key only when keyboard-buffer is not empty.
    Check whether k/b buffer is empty or not at the higher TPL using CheckEvent

**/
EFI_STATUS 
IsEscPressed( );

#endif

