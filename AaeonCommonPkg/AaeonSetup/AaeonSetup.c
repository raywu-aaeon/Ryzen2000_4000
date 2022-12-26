/** @file AaeonSetup.c
    Main file for AaeonSetup style module.

**/
//**********************************************************************
#include "AaeonSetup.h"
//20171031 Carson-Fix issue Os Indications Support-add >>
#include "bootflow.h"
#include <AutoId.h>
#include    <Token.h>

extern BOOT_FLOW	*gBootFlowTable;
//20171031 Carson-Fix issue Os Indications Support-add <<

extern VOID HandleSaveAndReset( VOID );

/**
    Function to handle Save and Exit Hotkey action

    @param app HOTKEY_DATA hotkey, VOID *cookie

    @retval VOID

**/
VOID AaeonHandleSaveExitKey( VOID *vapp, VOID *hotkey, VOID *cookie )
{
//	APPLICATION_DATA *app = (APPLICATION_DATA *)vapp;
//	app->Quit = SaveAndReset();
	HandleSaveAndReset();
}

//20171031 Carson-Fix issue Os Indications Support-add >>
/**
    A hook function to modify BIOS behavior after OS request entering setup.

    @param  N/A

    @retval VOID

**/
VOID AaeonOsIndicationsSupportHook()
{
	BOOT_FLOW *bootFlowPtr;
	//
	// Update the first entry of setup page to the PageFormID defined in AaeonSetup.sdl.
	// BIOS will enter this page after OS request entering setup.
	//
	bootFlowPtr = gBootFlowTable;
	for ( bootFlowPtr = gBootFlowTable;
			bootFlowPtr->Condition != BOOT_FLOW_CONDITION_NULL; bootFlowPtr++ )
	{
		if ( bootFlowPtr->Condition == BOOT_FLOW_CONDITION_FIRST_BOOT)
		{
			bootFlowPtr->PageFormID = OS_INDICATIONS_SUPPORT_FIRST_PAGE;
		}
	}
}
//20171031 Carson-Fix issue Os Indications Support-add <<