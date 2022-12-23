//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//*************************************************************************
/** @file AmiNetworkPostManagerLib.c
    AmiNetworkPostManagerLib Definitions

**/
//*************************************************************************
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/AmiNetworkPostManagerLib.h>
#include <Protocol/AMIPostMgr.h>
#include <NetworkStackSetup.h>

EFI_GUID AmiPostMgrProtocolGuid=AMI_POST_MANAGER_PROTOCOL_GUID;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL ForeGround = {0xFF,0xFF,0xFF,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackGround = {0,0,0,0};
AMI_POST_MANAGER_PROTOCOL *pAmiPostMgr = NULL;
//
// Macro definitions
//
#define IP_MODE_IP4               0
#define IP_MODE_IP6               1
#define ONE_MS                    1000          // 1000us = 1 milli second
#define HUNDRED_MS                (100*ONE_MS)    // 100 milli seconds
#define FIVE_HUNDRED_MS           (500*ONE_MS)   // 500 milli seconds
#define ONE_SECOND                (1000*ONE_MS)   // 1000ms = 1 second


INTN
EFIAPI
CompareMem (
  IN CONST VOID  *DestinationBuffer,
  IN CONST VOID  *SourceBuffer,
  IN UINTN       Length
  );

/*++

Routine Description:

  Call AMI Post Manager protocol to create Popup.

Arguments:

  String - String for display.

Returns:

  None.

--*/

VOID 
AMICreatePopUp(
  IN  CHAR16    *String  
  )
{
  UINT8      MsgBoxSel;
  EFI_STATUS Status = EFI_SUCCESS;
     
        if (pAmiPostMgr == NULL) {
            Status =  gBS->LocateProtocol(&AmiPostMgrProtocolGuid, NULL, (void **)&pAmiPostMgr);   // AMI PORTING : Added to resolve the build error with GCC compiler.
        }

        if (EFI_ERROR (Status)) return;
	  
        pAmiPostMgr->DisplayMsgBox(
                   L" ISCSI Message",
                   String,
                   MSGBOX_TYPE_OK,
                   &MsgBoxSel
                   );
   
    }

/*++

Routine Description:

  Call AMI Post Manager protocol to create Popup.

Arguments:

  String   - String for display.
  MsgTitle - String for PopUp Title

Returns:

  None.

--*/

VOID 
AMICreatePopUpEx (
  IN  CHAR16     *MsgTitle,
  IN  CHAR16     *String
  )
{
  UINT8      MsgBoxSel;
  EFI_STATUS Status = EFI_SUCCESS;
 
  if (pAmiPostMgr == NULL) {
      Status =  gBS->LocateProtocol(&AmiPostMgrProtocolGuid, NULL, (void **)&pAmiPostMgr);   
  }

  if (EFI_ERROR (Status)) return;
  
  pAmiPostMgr->DisplayMsgBox(
                 MsgTitle,
                 String,
                 MSGBOX_TYPE_OK,
                 &MsgBoxSel
                 );

}

/*++

Routine Description:

  Call AMI Post Manager protocol to create Popup.

Arguments:

  String - String for display.

Returns:

  None.

--*/

VOID 
AMIPrintText (
  IN  CHAR16     *String  )
{
  EFI_STATUS Status = EFI_SUCCESS;

        if (pAmiPostMgr == NULL) {
            Status =  gBS->LocateProtocol(&AmiPostMgrProtocolGuid, NULL, (void **)&pAmiPostMgr);   // AMI PORTING : Added to resolve the build error with GCC compiler.
        }

        if (EFI_ERROR (Status)) return;
				
  pAmiPostMgr->DisplayPostMessage(String);
  pAmiPostMgr->DisplayQuietBootMessage(
                 String, 
                 0, 
                 0, 
                 CA_AttributeLeftTop,
                 ForeGround, 
                 BackGround
                 );

    }


/*++

Routine Description:

  Call AMI Post Manager protocol for switch to post screen.

Arguments:

  None.

Returns:

  None.

--*/

VOID  
AMISwitchToPostScreen ()
{
        EFI_STATUS Status = EFI_SUCCESS;
	      if (pAmiPostMgr == NULL) {
            Status =  gBS->LocateProtocol(&AmiPostMgrProtocolGuid, NULL, (void **)&pAmiPostMgr);   // AMI PORTING : Added to resolve the build error with GCC compiler.
        }

        if (EFI_ERROR (Status))
        {
            return;
        }
        pAmiPostMgr->SwitchToPostScreen( );
		
}

/*++

Routine Description:

  Clears graphics screen using GOP protocol.

Arguments:

  None.

Returns:

  None.

--*/

VOID 
ClearGraphicsScreen (
 VOID ) 
{
  EFI_STATUS      Status = EFI_SUCCESS;
  EFI_UGA_PIXEL   UgaBlt={0,0,0,0};
  UINT32          HorizontalResolution = 0;
  UINT32          VerticalResolution = 0;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *pGOP = NULL;
     
        
            Status =  gBS->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (void **)&pGOP);   // AMI PORTING : Added to resolve the build error with GCC compiler.
            if ( EFI_ERROR (Status) ) {
                pGOP = NULL;
                return;
            }

  HorizontalResolution = pGOP->Mode->Info->HorizontalResolution;
  VerticalResolution = pGOP->Mode->Info->VerticalResolution;
  pGOP->Blt(
          pGOP,
          &UgaBlt,
          EfiBltVideoFill,
          0, 
          0,
          0, 
          0,
          HorizontalResolution, 
          VerticalResolution,
          0 
          );
}

/**
  Check for invalid character in IP address.

  @param  Source        A pointer to a Null-terminated Unicode string.

  @return 
  EFI_SUCCESS - If invalid characters are not present
  EFI_INVALID_PARAMETER - If in valid characters are present

**/
EFI_STATUS
CheckInvalidCharinIpAddress (
  IN CONST CHAR16       *IpSource,
  IN UINT8              IpMode
  )
{
    //
    // For IP4 address format: Below are the valid characters
    // 1) "0-9" 2) "."(DOT)
    //
    if ( IpMode == IP_MODE_IP4 ) {
        while (*IpSource != '\0') {
            if ( ( ((*IpSource >= '0') && (*IpSource <= '9')) ||\
                   (*IpSource =='.') ) != TRUE ) {
                return EFI_INVALID_PARAMETER;
            }
            IpSource++;
        }
    } else if ( IpMode == IP_MODE_IP6 ) {
        //
        // For IP6 address format: Below are the valid characters
        // 1) "0-9" 2) ":"(COLON) 3) "a-f" 4) "A-F"
        //
        while (*IpSource != '\0') {
            if ( ( ((*IpSource >= '0') && (*IpSource <= '9')) ||\
                   ((*IpSource >= 'a') && (*IpSource <= 'f')) ||\
                   ((*IpSource >= 'A') && (*IpSource <= 'F')) ||\
                   (*IpSource ==':') ) != TRUE ) {
                return EFI_INVALID_PARAMETER;
            }
            IpSource++;
        }
    } else {
        return EFI_INVALID_PARAMETER;
    }
    return EFI_SUCCESS;
}

/**
  Gets the string form Supported language. If it fails, gets the string from Default language.

  @param EFI_HII_HANDLE HiiHandle
  		 EFI_STRING_ID StringId
		 CHAR8 *Language

  @return CHAR16* 
 
**/


CHAR16* NetLibHiiGetString( EFI_HII_HANDLE HiiHandle, EFI_STRING_ID StringId, CHAR8 *Language)
{
	EFI_STRING String = NULL;
	CHAR8 *Lang = "en-US";

	String = HiiGetString(HiiHandle,StringId,Language);

	if(String == NULL && (Language == NULL || CompareMem(Language,Lang,5)))
	{
		String = HiiGetString(HiiHandle,StringId,Lang);
	}
	
	return String;
}

VOID PrePxeBootDummyFunction(IN EFI_EVENT Event, IN VOID *Context) {}

VOID NotifyPrePxeBoot(EFI_LOAD_FILE_PROTOCOL    *ThisCopy)
{
    EFI_STATUS Status;
    EFI_EVENT ReadyToPxeBoot;
    
    Status = gBS->CreateEventEx(
            EVT_NOTIFY_SIGNAL,
            TPL_CALLBACK,
            PrePxeBootDummyFunction,
            NULL,
            &gReadyToPxeBootGuid,
            &ReadyToPxeBoot);
    
      if ( !EFI_ERROR(Status) ) {
          
          gRT->SetVariable (
                  L"PxePreBootContext",
                  &gReadyToPxeBootGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof(ThisCopy),
                  &ThisCopy);
          
          gBS->SignalEvent(ReadyToPxeBoot);
          gBS->CloseEvent(ReadyToPxeBoot);
          
          gRT->SetVariable (
                  L"PxePreBootContext",
                  &gReadyToPxeBootGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  0,
                  NULL);
      }
}

/**

     Check media status before PXE start and add the console status messages.
 
     @param[in]  This               Protocol instance pointer.
     @param[in]  Private            The handle where network service binding protocols are installed on.
     @param[in]  MediaDetectCount   Number of media detected.
                        
**/

EFI_STATUS 
PxeCheckMediaState(
        IN EFI_LOAD_FILE_PROTOCOL   *This,
        IN EFI_HANDLE               Controller,
        IN UINT8                    MediaDetectCount
)
{
    UINTN                       NoofIterations;
    EFI_STATUS                  MediaStatus;
    
    AMISwitchToPostScreen();
    gST->ConOut->SetAttribute(gST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
    gST->ConOut->ClearScreen (gST->ConOut);
    gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
    
    //
    // Clear Graphics screen
    //
    ClearGraphicsScreen ();
    //
    // AMI PORTING END.
    //

    // AMI PORTING for pre PXE boot
    NotifyPrePxeBoot(This);       
    // AMI PORTING END
    AsciiPrint ("\n>>Checking Media Presence......");
    MediaStatus = EFI_SUCCESS;
    //
    // AMI PORTING START : Fix for adding Media Detect Time.
    //

    //
    // Number of iterations to check if media is found in a controller.
    //
    NoofIterations = MediaDetectCount; 
    while (TRUE) {
     NetLibDetectMediaWaitTimeout (Controller, PXEBC_CHECK_MEDIA_WAITING_TIME, &MediaStatus);
        
      //
      // Check whether NoofIterations equal to one if yes break from the loop.
      //
      if(NoofIterations-- <= MIN_MEDIA_DETECT_COUNT) {
          EFI_STATUS StatusFlush = EFI_SUCCESS;
          EFI_INPUT_KEY  FlushKeys;
          //
          // Read the buffer until it becomes empty so that no action will take place when Media is not present.
          //
          do {
                StatusFlush = gST->ConIn->ReadKeyStroke(gST->ConIn, &FlushKeys);
          } while (!EFI_ERROR(StatusFlush));        
          break;
      }
      if (MediaStatus != EFI_SUCCESS) {
        //
        // Give delay for 500 ms.  
        //
        gBS->Stall (FIVE_HUNDRED_MS);

      } else {
          //
          // Media is found so break from the loop.
          //
          break;
      }
    }
    //
    // AMI PORTING END : Fix for adding Media Detect Time.
    //
    if (MediaStatus != EFI_SUCCESS) {
      AsciiPrint ("\n>>No Media Present......");
      return EFI_NO_MEDIA;
    }
    if (!EFI_ERROR (MediaStatus)) { 
        AsciiPrint ("\n>>Media Present......");
    }
    return EFI_SUCCESS;
}

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
  IN UINT8  NumberOfSeconds )
{
    EFI_INPUT_KEY   InputKey;
    UINTN           NumberOfIterations;
    EFI_STATUS      Status;

    //
    // Print PXE boot wait time message
    //
    AsciiPrint (". Press ESC key to abort PXE boot");

    //
    // Calculate No.of iterations to read the key stroke based on 100ms delay.
    //
    NumberOfIterations = NumberOfSeconds * (ONE_SECOND/HUNDRED_MS);

    while ( TRUE ) {
        
        // Read the key only when keyboard-buffer is not empty.
        // Check whether k/b buffer is empty or not at the higher TPL using CheckEvent
        Status = gBS->CheckEvent( gST->ConIn->WaitForKey );
        if(Status != EFI_NOT_READY){ 
        //
        // Read the key stroke if any and check for ESC key
        // If ESC key is found, return status as EFI_ABORTED.
        //
        Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &InputKey);
        if ( !EFI_ERROR (Status) && (InputKey.ScanCode == SCAN_ESC) ) {
            return EFI_ABORTED;
        }
        }
        //
        // Return EFI_SUCCESS if NumberOfIterations is zero.
        //
        if ( --NumberOfIterations == 0x00 ) {
            return EFI_SUCCESS;
        }
        //
        // Give 100 milli seconds delay
        //
        gBS->Stall (HUNDRED_MS);
    } // while loop

}

/**
  Display the MAC address on PXE boot screen.

  @param[in]  Mac        The pointer to the Mac address.

**/
VOID
PxeBootShowMacAddr (
  IN EFI_MAC_ADDRESS   *Mac
  )
{
    UINTN                 Index;
  
    AsciiPrint (" on MAC: ");

    for (Index = 0; Index < 6; Index++) {
      AsciiPrint ("%02x", Mac->Addr[Index]);
      if (Index < 5) {
        AsciiPrint ("-");
      }
    }
}


/**

     Check media status before HTTP start and add the console status messages.
 
     @param[in]  This               Protocol instance pointer.
     @param[in]  Private            The handle where network service binding protocols are installed on.
     @param[in]  MediaDetectCount   Number of media detected.
                        
**/

EFI_STATUS 
HttpCheckMediaState(
        IN EFI_LOAD_FILE_PROTOCOL   *This,
        IN EFI_HANDLE               Controller,
        IN UINT8                    MediaDetectCount
)
{
    UINTN                       NoofIterations;
    EFI_STATUS                  MediaStatus;
    EFI_STATUS                  Status;
    
    AMISwitchToPostScreen();
    gST->ConOut->SetAttribute( gST->ConOut, EFI_BACKGROUND_BLACK | EFI_WHITE);
    gST->ConOut->ClearScreen (gST->ConOut);
    gST->ConOut->SetCursorPosition(gST->ConOut,0,0);
    
    //
    // Clear Graphics screen
    //
    ClearGraphicsScreen ();
    
    //
    // Add the console status messages.
    //
    AsciiPrint ("\n>>Checking Media Presence......");
   
    MediaStatus = EFI_SUCCESS;
    NoofIterations = MediaDetectCount;
    while(TRUE){
        Status = NetLibDetectMediaWaitTimeout (Controller, HTTP_BOOT_CHECK_MEDIA_WAITING_TIME, &MediaStatus);
        //
        // Check whether NoofIterations equal to one if yes break from the loop.
        //
        if(NoofIterations-- <= MIN_MEDIA_DETECT_COUNT) {
            break;
        }
        
        if (MediaStatus != EFI_SUCCESS) {
            //
            // Give delay for 500 ms.  
            //
            gBS->Stall (FIVE_HUNDRED_MS);
        } else {
            //
            // Media is found so break from the loop.
            //
            break;
        }
    }
    
    if (MediaStatus != EFI_SUCCESS) {
        AsciiPrint ("\n>>No Media Present......");    // AMI PORTING
        return EFI_NO_MEDIA;
    }
    
    if (!EFI_ERROR (Status)) {
        AsciiPrint ("\n>>Media Present......");  // AMI PORTING
    }
    return EFI_SUCCESS;
}

//
// Catch ESC to abort.
//

// Read the key only when keyboard-buffer is not empty.
// Check whether k/b buffer is empty or not at the higher TPL using CheckEvent
EFI_STATUS 
IsEscPressed( )
{
    EFI_STATUS              Status = EFI_NOT_READY;
    EFI_INPUT_KEY           Key;  

    if(NULL != gST->ConIn)
    {
        Status = gBS->CheckEvent( gST->ConIn->WaitForKey );
        if(Status != EFI_NOT_READY){
            Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
            if (!EFI_ERROR (Status)) {
                if (Key.ScanCode == SCAN_ESC || Key.UnicodeChar == (0x1F & 'c')) {
                    Status = EFI_ABORTED;
                }
            }
        }
    }
    return Status;
}
