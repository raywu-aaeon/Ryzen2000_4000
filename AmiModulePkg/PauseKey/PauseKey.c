//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file PauseKey.c
   Implements the functions of PauseKey driver.
    
    This driver registers notify functions for the pause key stroke and 
    the keystrokes to end the paused state. The notify functions detect 
    the paused state or detect the end of the paused state.
    The driver also installs an instance of the AMI_PAUSE_PROTOCOL.  
    This protocol is called by BDS and TSE.  The Pause protocol will
    pause the system based on the pause state as detected by the 
    notification functions.
**/

#include <AmiDxeLib.h>
#include <Protocol/AmiPause.h>
#include <Protocol/SimpleTextInEx.h>
#include <Library/HiiLib.h>
#include <Protocol/AMIPostMgr.h>
#include "Token.h"
#include <Protocol/SimpleTextInEx.h>
#include <Library/UefiLib.h>

// GUID for Pause key strings package
#define PAUSEKEY_STRING_PACKAGE_GUID\
       { 0x4edd1379, 0x7bbe, 0x4d32, { 0xb4, 0x5d, 0x85, 0xd3, 0xe5, 0xc5, 0x91, 0x65 } }

// module global variable for the Ami Post Manager Protocol
AMI_POST_MANAGER_PROTOCOL   *gPostMgr = NULL;

// global variable for ST->ConInHandle's  SimpleTextInEx protocol pointer
EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *gSimpleEx = NULL;   

// Global pointer for retrieved unicode string from the HII database for Pause Message 
CHAR16          *gString;

// Global pointer for retrieved unicode string from the HII database to erase Pause Message 
CHAR16          *gBlankString;

// Sets the pause key scan code, unicode and key state values
EFI_KEY_DATA    gPauseKeyData = { { SCAN_PAUSE, CHAR_NULL} , { 0, 0} };
EFI_KEY_DATA    gAnyKeyData = { { 0, 0} , { 0, 0} };

// Handle for string resources that are part of the module
EFI_HII_HANDLE gHiiHandle = 0;

// Unique handle to be assigned for registered pause key notification.
VOID            *gPauseKeyNotifyHandle;
VOID            *gAnyKeyNotifyHandle;
EFI_EVENT       ReadyToBootEvent; ///  This will unregister the key notifications

// global pause state.  Volatile because the pause state can be changed in 
//  notification functions while looping in a paused state.
volatile BOOLEAN gPause = FALSE;

EFI_STATUS
PauseKeyNotificationFunction(
    IN EFI_KEY_DATA *RegisteredKeyData
    );

EFI_STATUS
AnyKeyNotificationFunction(
    IN EFI_KEY_DATA *RegisteredKeyData
    );

VOID EFIAPI Pause(VOID);

VOID PauseKey_ConInInstalledCallback(IN EFI_EVENT Event, IN VOID *Context);

VOID
EFIAPI
ReadyToBootUnregisterKeypress(
    IN EFI_EVENT    Event, 
    IN VOID         *Context
);

// Pause Protocol Definition 
AMI_PAUSE_PROTOCOL  gAmiPauseKeyProtocol = { Pause };

//----------------------------------------------------------------------------

// pauses between the checks for changes in the pause state
VOID StallForPause(VOID)
{
    UINTN i;
    for (i = 0; i < 100; i++) {
        if (gPause == FALSE) {
            break;
        }
        pBS->Stall(1 * 1000); // 1ms
    }
}



/**
   This is the driver entrypoint.  
   
    This driver installs the string packages that are connected to 
    the driver image.  After installing the package, it gets the two strings
    uased in the driver.  It then installs a callback on the SimpleTextInEx Protocol
    It also installs the AMI_PAUSE_PROTOCOL instance.
    A Ready to Boot callback is created to unregister the key presses.

  @param ImageHandle  Handle of the driver image
  @param SystemTable  Pointer to the system table
  
  @return EFI_STATUS
  @retval EFI_SUCCESS   
**/
EFI_STATUS
EFIAPI
PauseKeyDriverEntryPoint(    
        IN EFI_HANDLE       ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
        )
{
    EFI_STATUS                          Status;
#if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))
    EFI_HII_HANDLE                      gPauseKeyStringPackHandle = NULL;
    EFI_GUID gPausekeyStringPackageGuid = PAUSEKEY_STRING_PACKAGE_GUID;
#endif
    EFI_EVENT                           Event;
    VOID                                *pRegistration;

    InitAmiLib(ImageHandle, SystemTable);

#if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))
    

    // Load the Language strings for use when creating the strings into the Hii database
    Status = LoadStrings(ImageHandle, &gHiiHandle);
    ASSERT(Status == EFI_SUCCESS);
    if (EFI_ERROR(Status))
        return Status;


    // Gets the "STR_BLANK_LINE_STRING" string from HII database 
    gBlankString = HiiGetString(gHiiHandle, STRING_TOKEN(STR_BLANK_LINE_STRING), NULL);

    // Gets the "STR_PAUSEKEY_PRESSED_MSG" string from HII database 
    gString = HiiGetString(gHiiHandle, STRING_TOKEN(STR_PAUSEKEY_PRESSED_MSG), NULL);

#endif  // end of #if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))


    Status = pBS->InstallProtocolInterface(  
            &ImageHandle,
            &gAmiPauseProtocolGuid,
            EFI_NATIVE_INTERFACE,
            &gAmiPauseKeyProtocol);
    
    // register a callback for ConIn to be installed
    RegisterProtocolCallback(&gEfiSimpleTextInputExProtocolGuid, PauseKey_ConInInstalledCallback, NULL, &Event,&pRegistration);
    Status = EfiCreateEventReadyToBootEx(
                TPL_NOTIFY, ReadyToBootUnregisterKeypress, 
                NULL, &ReadyToBootEvent);
    ASSERT_EFI_ERROR(Status);
    return EFI_SUCCESS;   
}

/**
    SimpleTextInputEx Protocol Callback which installs the event and notification used to 
    handle the Pause Key State.
    
    First it checks to see in the SystemTable->ConIn Pointer has been updated,
    This check is to see if the Consplitter has been installed.  If it has,
    and the ConInHandle is valid, it is used to handle the SimpleTextInEx Protocol.  
    If the ConInHandle is not valid, then try the ConOutHandle.  The core uses the 
    same handle for both.  Once the Handle is found, the SimpleTextInEx Event is 
    closed, because no more processing is needed.
    Once the handle is defined, the system calls RegisterKeyNotify to get a 
    callback on a Pause key press. A second RegisterKeyNotify is created to be called 
    on any keypress.  This function will clear the pause state 

    @param Event The pointer created to identify this callback
    @param Context data passed in from the create event call for use in the function
    
    @return None
 */
VOID 
EFIAPI
PauseKey_ConInInstalledCallback(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS      Status;
    EFI_HANDLE      ConsoleInHandle;
    
    // If the SystemTable ConIn Pointer is NULL exit out and wait until ConIn is defined
    if (pST->ConIn == NULL)
        return;
    else 
    {
        // neither handle has been defined yet. wait until the next call, we can't do anything without the handle
        if ((pST->ConsoleInHandle == NULL) && (pST->ConsoleOutHandle == NULL))
            return; 
        // Both use the same handle, but the call may have happened before the pST->ConInHandle is set
        else if (pST->ConsoleInHandle == NULL)
            ConsoleInHandle = pST->ConsoleOutHandle;
        else 
            ConsoleInHandle = pST->ConsoleInHandle;
    }
    
    // Get the SimpleTextInEx Protocol from the ConInHandle in the System Table
    Status = pBS->HandleProtocol (
            ConsoleInHandle,
            &gEfiSimpleTextInputExProtocolGuid,
            (VOID**)&gSimpleEx
            );
    if (EFI_ERROR(Status))
    {
        // if the SimpleTextInputEx is not on the handle, exit and wait for the next call
        DEBUG((DEBUG_ERROR, "SimpleTxtInEx not found.\n\r"));
        ASSERT_EFI_ERROR (Status); 
        return;
    }
        
    //register RegisterKeyNotify
    Status = gSimpleEx->RegisterKeyNotify(
            gSimpleEx,
            &gPauseKeyData,
            PauseKeyNotificationFunction,
            &gPauseKeyNotifyHandle
            );

    if (EFI_ERROR(Status))
    {
        // The RegisterKeyNotify did not happen as expected, exit here and wait for next call
        DEBUG((DEBUG_ERROR, "PauseKey RegisterKeyNotify Failed.\n\r"));
        return;
    }

    DEBUG((DEBUG_INFO, "Pause key notification registered!! \n\r"));

    //register RegisterKeyNotify
    Status = gSimpleEx->RegisterKeyNotify(
            gSimpleEx,
            &gAnyKeyData,
            AnyKeyNotificationFunction,
            &gAnyKeyNotifyHandle
            );

    if (EFI_ERROR(Status))
    {
        // The RegisterKeyNotify did not happen as expected, exit here and wait for next call
        DEBUG((DEBUG_ERROR, "AnyKey RegisterKeyNotify Failed.\n\r"));
        Status = gSimpleEx->UnregisterKeyNotify(
                gSimpleEx,
                &gPauseKeyNotifyHandle
                );
        return;
    }

    DEBUG((DEBUG_INFO, "Anykey notification registered!! \n\r"));

    // we no longer need this event all registrations have completed properly
    pBS->CloseEvent(Event);

}

/**
  This Protocol function checks the global pause state.  If set, it
  will loop until the global Pause state clears.
  
  This function handles the display of the message strings and the change of 
  the global pause state to end the Pause.  The function checks the Global 
  Pause state, if clear, the function exits.  Next it displays a message on 
  the screen and waits for the global Pause state to clear.  Once clear, the 
  message is erased and the function returns.
 
  @return VOID
  @retval none
*/

VOID EFIAPI Pause(VOID)
{
#if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))
    EFI_STATUS                  Status;
    UINTN                       PostStatus = TSE_POST_STATUS_IN_TSE;       
    UINTN                       CurrRow;
    UINTN                       CurrColumn;
#endif // end of #if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))
    UINTN                       Index = 0;

    if (gPause == 0)
    {
        return;
    }
    

#if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))
    if (gPostMgr == NULL)
    {
        // Locates the AMI_POST_MANAGER_PROTOCOL interface
        Status = pBS->LocateProtocol(
                            &gAmiPostManagerProtocolGuid, 
                            NULL,
                            (void**) &gPostMgr
                            );
        if (EFI_ERROR(Status))
        {
            ASSERT_EFI_ERROR(Status);
            return;
        }
    }

    // Gets the current post status 
    PostStatus = gPostMgr->GetPostStatus();

    // Handle messaging actions if it is in Test-mode
    if ((PostStatus != TSE_POST_STATUS_IN_TSE) && (PostStatus != TSE_POST_STATUS_PROCEED_TO_BOOT))
    {
        // Gets the cursor's current position
        gPostMgr->GetCurPos(&CurrColumn, &CurrRow);
        gPostMgr->SetCurPos(0, CurrRow + 1);
        if (EFI_ERROR(Status))
        {
            gPostMgr->SetCurPos(0, CurrRow);
        }
            
        // Displays the message on next line 
        gPostMgr->DisplayPostMessageEx(gString, PM_EX_DONT_ADVANCE_TO_NEXT_LINE);
        gPostMgr->SetCurPos(CurrColumn, CurrRow);
    }   
    else if (PostStatus == TSE_POST_STATUS_PROCEED_TO_BOOT)
    {
        // Gets the cursor's current position
        CurrRow = pST->ConOut->Mode->CursorRow;
        CurrColumn = pST->ConOut->Mode->CursorColumn;

        Status = pST->ConOut->SetCursorPosition(pST->ConOut, 0, CurrRow + 1);
            
        if (Status == EFI_UNSUPPORTED)
        {
            // at the bottom of the screen
            Status = pST->ConOut->SetCursorPosition(pST->ConOut, 0, CurrRow);
        }
        // Displays the message on next line 
        pST->ConOut->OutputString(pST->ConOut, gString);
        pST->ConOut->SetCursorPosition(pST->ConOut, CurrColumn, CurrRow);
    }
#endif  // end of #if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))

    // Loop until the global pause state is cleared
    while (TRUE) {
        if (gPause == FALSE)
            break;
        StallForPause();
    }    

    DEBUG((-1, "Exiting Pause!! \n\r"));

#if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))  
    if ((PostStatus != TSE_POST_STATUS_IN_TSE) && (PostStatus != TSE_POST_STATUS_PROCEED_TO_BOOT))
    {        
        // Clears the printed message, by printing a blank line string
        // Go to beginning of line
        gPostMgr->SetCurPos(0, CurrRow + 1);
        gPostMgr->DisplayPostMessageEx(gBlankString, PM_EX_DONT_ADVANCE_TO_NEXT_LINE);
        
        // Sets the cursor position to previous position 
        gPostMgr->SetCurPos(CurrColumn, CurrRow);
    }
    else if (PostStatus == TSE_POST_STATUS_PROCEED_TO_BOOT)
    {
        Status = pST->ConOut->SetCursorPosition(pST->ConOut, 0, CurrRow + 1);
        if (Status == EFI_UNSUPPORTED)
        {
            // at the bottom of the screen
            Status = pST->ConOut->SetCursorPosition(pST->ConOut, 0, CurrRow);
        }
        // Displays the message on next line 
        pST->ConOut->OutputString(pST->ConOut, gBlankString);
        pST->ConOut->SetCursorPosition(pST->ConOut, CurrColumn, CurrRow);
    }
#endif // end of #if (defined(SUPPRESS_PAUSE_MESSAGE) && (SUPPRESS_PAUSE_MESSAGE == 0))

}


/**
   This is the registered notify function for pause key stroke.  Once the 
   pause key is pressed this function will be invoked. The global variable 
   that tracks the pause state is set and function returns.
    
  @param RegisteredKeyData - Registered key data

  @return EFI_STATUS
  @retval EFI_SUCCESS     - If this function is executed successfully.
    
**/

EFI_STATUS 
EFIAPI
PauseKeyNotificationFunction ( IN EFI_KEY_DATA *KeyData )
{
    gPause = TRUE;
    DEBUG((DEBUG_INFO, "Set Pause!! \n\r"));

    return EFI_SUCCESS;
}

//==============================================================================================================
//==============================================================================================================
//==============================================================================================================

/**
   This is the registered notify function for the end of pause key stroke.
    This this will be called after every keypress.  If the key was not the 
    Pause key, then the global pause state is cleared. 
    
  @param RegisteredKeyData - Registered key data

  @return EFI_STATUS
  @retval EFI_SUCCESS     - If this function is executed successfully.
    
**/
EFI_STATUS 
EFIAPI
AnyKeyNotificationFunction ( IN EFI_KEY_DATA *KeyData )
{
    
    if ((gPause == TRUE) && (KeyData->Key.ScanCode != SCAN_PAUSE ))
    {
        gPause = FALSE;
        DEBUG((DEBUG_INFO, "Clear Pause!! \n\r"));
    }
    return EFI_SUCCESS;
}


/**
    This function is called at the Ready To Boot event.  
    It unregisters the Key Press notifications

    @param Event - Event created during registration
    @param Context - pointer to data registered when event was created
 */
VOID
EFIAPI
ReadyToBootUnregisterKeypress(
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    EFI_STATUS      Status;
    EFI_HANDLE      ConsoleInHandle;

    if (pST->ConIn == NULL)
    {
        return;
    }
    else 
    {
        // neither handle has been defined yet. wait until the next call, we can't do anything without the handle
        if ((pST->ConsoleInHandle == NULL) && (pST->ConsoleOutHandle == NULL))
            return; 
        // Both use the same handle, but the call may have happened before the pST->ConInHandle is set
        else if (pST->ConsoleInHandle == NULL)
            ConsoleInHandle = pST->ConsoleOutHandle;
        else 
            ConsoleInHandle = pST->ConsoleInHandle;
    }
    
    // Get the SimpleTextInEx Protocol from the ConInHandle in the System Table
    Status = pBS->HandleProtocol (
            ConsoleInHandle,
            &gEfiSimpleTextInputExProtocolGuid,
            (VOID**)&gSimpleEx
            );
    if (EFI_ERROR(Status))
    {
        // if the SimpleTextInputEx is not on the handle, exit and wait for the next call
        DEBUG((DEBUG_ERROR, "SimpleTxtInEx not found.\n\r"));
        ASSERT_EFI_ERROR (Status); 
        return;
    }


    //register RegisterKeyNotify
    Status = gSimpleEx->UnregisterKeyNotify(
            gSimpleEx,
            &gPauseKeyNotifyHandle
            );

    if (EFI_ERROR(Status))
    {
        // The UnRegisterKeyNotify did not happen as expected
        DEBUG((DEBUG_ERROR, "PauseKey UnRegisterKeyNotify Failed.\n\r"));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Pause key notification Unregistered!! \n\r"));
    }

    //Unregister Any Key
    Status = gSimpleEx->UnregisterKeyNotify(
            gSimpleEx,
            &gAnyKeyNotifyHandle
            );

    if (EFI_ERROR(Status))
    {
        // The RegisterKeyNotify did not happen as expected, exit here and wait for next call
        DEBUG((DEBUG_ERROR, "AnyKey UnregisterKeyNotify Failed.\n\r"));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Anykey notification unregistered!! \n\r"));
    }

    // we no longer need this event all registrations have completed properly
    pBS->CloseEvent(Event);

        
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
