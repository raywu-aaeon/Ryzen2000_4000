//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**
 * @file
 * Internal header of the Setup Component
 */

#ifndef __SetupPrivate__H__
#define __SetupPrivate__H__
#include <SetupStrDefs.h>
#include <Setup.h>
/// Private data structure to keep track of data associated with the setup form
typedef struct
{
    EFI_HII_CONFIG_ACCESS_PROTOCOL HiiAccessProtocol;   ///< Instance of the HiiAccessProtocol that is produced by this module
    EFI_HANDLE CallbackHandle;                          ///< Handle that the HiiAccessProtocol is installed upon
    EFI_HII_HANDLE HiiHandle;                           ///< HiiHandle returned when NewPack is called when installing the String Database
    EFI_GUID FormGuid;                                  ///< GUID of the formset produced by this module
} SETUP_FORM_PRIVATE_DATA;

#endif
