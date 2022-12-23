//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**
    @file Ntp.c
    AMI NTP implementation.
**/

#include "Ntp.h"
#include "NtpImpl.h"
#include <Setup.h>

STATIC EFI_GUID    gEfiSetupGuid   = SETUP_GUID;
extern EFI_HANDLE  ThisImageHandle;

/**
    Perform the NTP synchronization.

    @param[in]  HiiHandle    HII handle of formset.
    @param[in]  Class        Class of formset.
    @param[in]  SubClass     Subclass of formset.
    @param[in]  Key          Id of setup control.

    @retval  None

**/
VOID
EFIAPI
NtpSyncStart (
    IN  EFI_HII_HANDLE    HiiHandle,
    IN  UINT16            Class,
    IN  UINT16            SubClass,
    IN  UINT16            Key
    )
{
    CALLBACK_PARAMETERS *Callback = NULL;

    Callback = GetCallbackParameters ();

    if (!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return;

    NtpSyncStartImpl (&gEfiSetupGuid, ThisImageHandle);
}

/**
    Initializes the NTP related setup option values.

    @param[in]  HiiHandle    Handle to HII database.
    @param[in]  Class        Indicates the setup class.

    @retval  None

**/
VOID
EFIAPI
InitNtpStrings (
    IN  EFI_HII_HANDLE    HiiHandle,
    IN  UINT16            Class
    )
{
    NTP_STRING_TOKEN  StrTokenList[] = {
        { StrTokenConfigServerHostNameDefault, STRING_TOKEN (STR_NTP_CONFIG_SERVER_HOST_NAME_DEFAULT)  },
        { StrTokenDisplayTitleError,           STRING_TOKEN (STR_NTP_DISPLAY_TITLE_ERROR)              },
        { StrTokenDisplayTitleSync,            STRING_TOKEN (STR_NTP_DISPLAY_TITLE_SYNC)               },
        { StrTokenDisplayMsgSyncWait,          STRING_TOKEN (STR_NTP_DISPLAY_MSG_SYNC_WAIT)            },
        { StrTokenDisplayTitleTimeUpdate,      STRING_TOKEN (STR_NTP_DISPLAY_TITLE_TIME_UPDATE)        },
        { StrTokenDisplayMsgTimeUpdateFailed,  STRING_TOKEN (STR_NTP_DISPLAY_MSG_TIME_UPDATE_FAILED)   },
        { StrTokenDisplayTitleConfigFailed,    STRING_TOKEN (STR_NTP_DISPLAY_TITLE_CONFIG_FAILED)      },
        { StrTokenDisplayMsgConfigCheck,       STRING_TOKEN (STR_NTP_DISPLAY_MSG_CONFIG_CHECK)         },
        { StrTokenDisplayMsgConfigRetry,       STRING_TOKEN (STR_NTP_DISPLAY_MSG_CONFIG_RETRY)         },
        { StrTokenDisplayTitleConfigChanged,   STRING_TOKEN (STR_NTP_DISPLAY_TITLE_CONFIG_CHANGED)     },
        { StrTokenDisplayMsgConfigSave,        STRING_TOKEN (STR_NTP_DISPLAY_MSG_CONFIG_SAVE)          },
        { StrTokenDisplayTitleSyncConfirm,     STRING_TOKEN (STR_NTP_DISPLAY_TITLE_SYNC_CONFIRM)       },
        { StrTokenDisplayMsgSyncConfirm,       STRING_TOKEN (STR_NTP_DISPLAY_MSG_SYNC_CONFIRM)         },
        { StrTokenDisplayErrorMsgIpConfig,     STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_IP_CONFIG)      },
        { StrTokenDisplayErrorMsgNtpRetry,     STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_NTP_RETRY)      },
        { StrTokenDisplayErrorMsgNtpConfig,    STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_NTP_CONFIG)     },
        { StrTokenDisplayErrorMsgAny,          STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_ANY)            },
        { StrTokenDisplayErrorMsgResponse,     STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_RESPONSE)       },
        { StrTokenDisplayErrorMsgRequest,      STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_REQUEST)        },
        { StrTokenDisplayErrorMsgTimerEvent,   STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_TIMER_EVENT)    },
        { StrTokenDisplayErrorMsgInvalidIp,    STRING_TOKEN (STR_NTP_DISPLAY_ERROR_MSG_INVALID_IP)     },
    };

    InitNtpStringsImpl (HiiHandle, &gEfiSetupGuid, StrTokenList);
}

/**
    Verify Ipv4 address.

    @param[in]  HiiHandle    HII handle of formset.
    @param[in]  Class        Class of formset.
    @param[in]  SubClass     Subclass of formset.
    @param[in]  Key          Id of setup control.

    @retval  EFI_SUCCESS    The Ipv4 address is valid.
    @retval  Other          The Ipv4 address is invalid.

**/
EFI_STATUS
EFIAPI
NtpVerifyIpAddress (
    IN  EFI_HII_HANDLE    HiiHandle,
    IN  UINT16            Class,
    IN  UINT16            SubClass,
    IN  UINT16            Key
    )
{
    CALLBACK_PARAMETERS  *Callback     = NULL;
    UINT16               IpStringValue = 0;

    Callback = GetCallbackParameters ();

    if (!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return EFI_INVALID_PARAMETER;

    // Get the string Token value for the string control data
    IpStringValue = Callback->Value->u16;

    return NtpVerifyIpAddressImpl (HiiHandle, IpStringValue);
}
