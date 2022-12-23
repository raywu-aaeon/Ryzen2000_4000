//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**
    @file NtpImpl.c
    AMI NTP implementation.
**/

#include "NtpImpl.h"
#include "Ntp.h"
#include <Token.h>

#if defined(MDE_PKG_VERSION) && (MDE_PKG_VERSION >= 10)
#include <Protocol/Ip4Config2.h>
#endif

STATIC BOOLEAN                    gCompleted             = FALSE;
STATIC EFI_CPU_ARCH_PROTOCOL      *gCpuArchProtocol      = NULL;
STATIC UINT64                     gCurrentTick           = 0;
STATIC UINT64                     gTimerPeriod           = 0;
STATIC UINT64                     gFrequency             = 0;
STATIC UINT32                     gTimeStamp             = 0;
STATIC AMI_POST_MANAGER_PROTOCOL  *gAmiPostMgr           = NULL;
STATIC UINTN                      gPercent               = 0;
STATIC VOID                       *gHandle               = NULL;
STATIC AMI_POST_MGR_KEY           gOutKey;
STATIC EFI_HII_HANDLE             gNtpHiiHandle          = NULL;

STATIC NTP_STRING_TOKEN           gStrTokenList[StrTokenIndexEnd];

STATIC CONST UINTN                gCumulativeDays[2][12] = {
        { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }, // Common year
        { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }  // Leap year
    };

// The list of time zone offset in minute.
STATIC CONST INT16                gTimeZoneList[]        = {
        -720, -660, -600, -540, -480, -420, -360, -300, -270,
        -240, -210, -180, -120,  -60,    0,   60,  120,  180,
         210,  240,  270,  300,  330,  345,  360,  390,  420,
         480,  540,  570,  600,  660,  720,  780,  840,
    };

/**
    Get a token value and return the string with given token index defined in NTP_STRING_TOKEN_INDEX.

    The returned string is allocated using AllocatePool() by HiiGetString().
    The caller is responsible for freeing the allocated buffer using FreePool().

    @param[in]      StrTokenIndex    The token index to be searched.
    @param[in,out]  StrTokenValue    The token value to be returned after searching in token list.

    @retval NULL     Token is not found in token list or the string specified by token value is not present in the string package.
    @retval Other    Token is found in token list and the string was returned.

**/
STATIC
CHAR16 *
GetTokenString (
    IN      NTP_STRING_TOKEN_INDEX    StrTokenIndex,
    IN OUT  EFI_STRING_ID             *StrTokenValue OPTIONAL
    )
{
    UINTN  Index   = 0;

    for (Index = 0; Index < StrTokenIndexEnd; Index++) {
        if (gStrTokenList[Index].Index == StrTokenIndex) {
            if (StrTokenValue != NULL) {
                *StrTokenValue = gStrTokenList[Index].Value;
            }
            return HiiGetString (gNtpHiiHandle, gStrTokenList[Index].Value, NULL);
        }
    }

    return NULL;
}

/**
    Get a time zone offset with given index from user's configuration.

    @param[in]      TimeZoneIndex     The index of user's configuration to be searched.
    @param[in,out]  TimeZoneOffset    The time zone offset to be returned after searching in time zone list.

    @retval  TRUE     Token is found in time zone list.
    @retval  FALSE    Token is not found in time zone list.

**/
STATIC
BOOLEAN
GetTimeZoneValue (
    IN      UINT8    TimeZoneIndex,
    IN OUT  INT16    *TimeZoneOffset
    )
{
    if (TimeZoneIndex >= sizeof (gTimeZoneList))
        return FALSE;

    *TimeZoneOffset = gTimeZoneList[TimeZoneIndex];

    return TRUE;
}

/**
    Display an error message box with given token index defined in NTP_STRING_TOKEN_INDEX.

    @param[in]  MessageTokenIndex    The token index of the error message to be displayed.

    @retval  None

**/
STATIC
VOID
DisplayErrorMsg (
    IN  NTP_STRING_TOKEN_INDEX    MessageTokenIndex
    )
{
    EFI_STATUS  Status;
    CHAR16      *Title   = NULL;
    CHAR16      *Message = NULL;

    if (gAmiPostMgr == NULL) {
        Status = gBS->LocateProtocol (
                    &gAmiPostManagerProtocolGuid,
                    NULL,
                    (VOID **) &gAmiPostMgr
                    );
        if (EFI_ERROR (Status)) {
            return;
        }
    }

    Title   = GetTokenString (StrTokenDisplayTitleError, NULL);
    Message = GetTokenString (MessageTokenIndex, NULL);

    if (Title != NULL && Message != NULL) {
        gAmiPostMgr->DisplayMsgBox (
            Title,
            Message,
            MSGBOX_TYPE_OK,
            NULL
            );
    }

    if (Title != NULL) {
        FreePool (Title);
        Title = NULL;
    }

    if (Message != NULL) {
        FreePool (Message);
        Message = NULL;
    }
}

/**
    Display an information message box with token index defined in NTP_STRING_TOKEN_INDEX.

    @param[in]   TitleTokenIndex      The token index of the title string to be displayed..
    @param[in]   MessageTokenIndex    The token index of the information string to be displayed.
    @param[in]   MsgBoxType           Message box type.
    @param[out]  MsgBoxSel            Selection of the message box to be selected by user.

    @retval  None

**/
STATIC
VOID
DisplayInfoMsg (
    IN      NTP_STRING_TOKEN_INDEX    TitleTokenIndex,
    IN      NTP_STRING_TOKEN_INDEX    MessageTokenIndex,
    IN      UINT8                     MsgBoxType,
       OUT  UINT8                     *MsgBoxSel
    )
{
    EFI_STATUS  Status;
    CHAR16      *Title   = NULL;
    CHAR16      *Message = NULL;

    if (gAmiPostMgr == NULL) {
        Status = gBS->LocateProtocol (
                    &gAmiPostManagerProtocolGuid,
                    NULL,
                    (VOID **) &gAmiPostMgr
                    );
        if (EFI_ERROR (Status)) {
            return;
        }
    }

    Title   = GetTokenString (TitleTokenIndex, NULL);
    Message = GetTokenString (MessageTokenIndex, NULL);

    if (Title != NULL && Message != NULL) {
        gAmiPostMgr->DisplayMsgBox (
            Title,
            Message,
            MsgBoxType,
            MsgBoxSel
            );
    }

    if (Title != NULL) {
       FreePool (Title);
       Title = NULL;
    }

    if (Message != NULL) {
       FreePool (Message);
       Message = NULL;
    }
}

/**
    Update the Progress Box.

    @param[in]      ProgressBoxState    ProgressBox State.
    @param[in]      Percent             Progress number (0-100) to be updated.
    @param[in,out]  Handle              Out HANDLE. Valid Handle for update and close.
    @param[out]     OutKey              Out Key.

    @retval  None

**/
STATIC
VOID
DisplayProgressMsg (
    IN      UINT8               ProgressBoxState,
    IN      UINTN               Percent,
    IN OUT  VOID                **Handle,
       OUT  AMI_POST_MGR_KEY    *OutKey
    )
{
    EFI_STATUS  Status;
    CHAR16      *Title   = NULL;
    CHAR16      *Message = NULL;

    if (gAmiPostMgr == NULL) {
        Status = gBS->LocateProtocol (
                    &gAmiPostManagerProtocolGuid,
                    NULL,
                    (VOID **) &gAmiPostMgr
                    );
        if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_ERROR, "[NTP] Get AmiPostManagerProtocol failed!\n"));
            return;
        }
    }

    Title   = GetTokenString (StrTokenDisplayTitleSync, NULL);
    Message = GetTokenString (StrTokenDisplayMsgSyncWait, NULL);

    if (Title != NULL && Message != NULL) {
        gAmiPostMgr->DisplayProgress (
           ProgressBoxState,
           Title,
           Message,
           NULL,
           Percent,
           Handle,
           OutKey
           );
    }

    if (Title != NULL) {
        FreePool (Title);
        Title = NULL;
    }

    if (Message != NULL) {
        FreePool (Message);
        Message = NULL;
    }
}

/**
    Callback function for the DNS complete event.

    @param[in]  Event      The triggered event.
    @param[in]  Context    The parameter to the function.

    @retval  None

**/
VOID
EFIAPI
NtpDnsComplete (
    IN  EFI_EVENT    Event,
    IN  VOID         *Context
    )
{
    if (Event == NULL || Context == NULL)
        return;

    *((BOOLEAN *) Context) = TRUE;
}

/**
    The notify function of create event when performing a manual configuration.

    @param[in]  Event      The pointer of Event.
    @param[in]  Context    The pointer of Context.

    @retval  None

**/
VOID
EFIAPI
NtpConfig2ManualAddressNotify (
    IN  EFI_EVENT    Event,
    IN  VOID         *Context
    )
{
    if (Event == NULL || Context == NULL)
        return;

    *((BOOLEAN *) Context) = TRUE;
}

#if defined(MDE_PKG_VERSION) && (MDE_PKG_VERSION >= 10)
/**
    Poll and check if the IPv4 is configured.

    @param[in]   Ip4Config2    The Ip4Config2 protocol.

    @retval  TRUE    IPv4 is configured successfully.
    @retval  FALSE   IPv4 is not configured.

**/
STATIC
BOOLEAN
IsIp4ConfigDone (
    IN  EFI_IP4_CONFIG2_PROTOCOL    *Ip4Config2
    )
{
    EFI_STATUS  Status;
    UINTN       DataSize     = 0;
    BOOLEAN     IsIpDone     = FALSE;
    BOOLEAN     IsDnsDone    = FALSE;
    EFI_EVENT   TimeoutEvent;
    EFI_STATUS  TimeoutStatus;

    if (Ip4Config2 == NULL)
        return FALSE;

    Status = gBS->CreateEvent (
                EVT_TIMER,
                TPL_NOTIFY,
                NULL,
                NULL,
                &TimeoutEvent
                );
    if (EFI_ERROR (Status)) {
        return FALSE;
    }

    gBS->SetTimer (TimeoutEvent, TimerRelative, 50000000);

    IsIpDone  = FALSE;
    IsDnsDone = FALSE;

    do {
        TimeoutStatus = gBS->CheckEvent (TimeoutEvent);

        if (!IsIpDone) {
            DataSize = 0;
            Status = Ip4Config2->GetData (
                        Ip4Config2,
                        Ip4Config2DataTypeInterfaceInfo,
                        &DataSize,
                        NULL
                        );
            if (!EFI_ERROR (Status) || Status == EFI_BUFFER_TOO_SMALL) {
                IsIpDone = TRUE;
            } else if (Status == EFI_NOT_FOUND) {
                continue;
            } else {
                break;
            }
        }

        if (!IsDnsDone) {
            DataSize = 0;
            Status = Ip4Config2->GetData (
                        Ip4Config2,
                        Ip4Config2DataTypeDnsServer,
                        &DataSize,
                        NULL
                        );
            if (!EFI_ERROR (Status) || Status == EFI_BUFFER_TOO_SMALL) {
                IsDnsDone = TRUE;
            } else if (Status == EFI_NOT_FOUND) {
                continue;
            } else {
                break;
            }
        }

        if (IsIpDone && IsDnsDone)
            break;

    } while (TimeoutStatus == EFI_NOT_READY);

    gBS->SetTimer (TimeoutEvent, TimerCancel, 0);
    gBS->CloseEvent (TimeoutEvent);

    if (!IsIpDone || !IsDnsDone)
        return FALSE;

    return TRUE;
}

/**
    Use the Ip4Config2 Protocol to get IPv4 configuration data.

    @param[in]   Ip4Config2    The Ip4Config2 protocol.
    @param[in]   DataType      The type of data to get.
    @param[out]  DataSize      The size of the configuration data.
    @param[out]  Data          The data of the configuration data is returned.

    @retval  EFI_SUCCESS    Get the configuration data successfully.
    @retval  Other          Fail to get the configuration data.

**/
STATIC
EFI_STATUS
GetIp4Config2Data (
    IN      EFI_IP4_CONFIG2_PROTOCOL     *Ip4Config2,
    IN      EFI_IP4_CONFIG2_DATA_TYPE    DataType,
       OUT  UINTN                        *DataSize,
       OUT  VOID                         **Data
    )
{
    EFI_STATUS  Status;
    VOID        *TempData = NULL;

    if (Ip4Config2 == NULL || Data == NULL)
        return EFI_INVALID_PARAMETER;

    Status = Ip4Config2->GetData (
                Ip4Config2,
                DataType,
                DataSize,
                NULL
                );
    if (EFI_ERROR (Status) && Status != EFI_BUFFER_TOO_SMALL) {
        return Status;
    }

    TempData = AllocateZeroPool (*DataSize);
    if (TempData == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        DEBUG ((DEBUG_ERROR, "[NTP] GetIp4Config2Data- Allocate memory %r\n", Status));
        return Status;
    }

    Status = Ip4Config2->GetData (
                Ip4Config2,
                DataType,
                DataSize,
                TempData
                );
    if (EFI_ERROR (Status)) {
        FreePool (TempData);
        TempData = NULL;
    }

    *Data = TempData;

    DEBUG ((DEBUG_INFO, "[NTP] GetIp4Config2Data- GetData (Type %d) %r\n", DataType, Status));
    return Status;
}
#endif

/**
    Retrieve the DNS server Ipv4 address from the configuration in Setup.

    @param[in]      NtpConfigVar    The configuration in Setup.
    @param[in,out]  DnsConfig       The data buffer for DNS server.

    @retval  EFI_SUCCESS    Get the DNS server configuration successfully.
    @retval  Other          Fail to get the DNS server configuration.

**/
STATIC
EFI_STATUS
RetrieveDnsServerIpList (
    IN      NTP_CONFIGURATION    NtpConfigVar,
    IN OUT  DNS_SERVER_CONFIG    *DnsConfig
    )
{
    EFI_STATUS        Status;

    if (DnsConfig == NULL || (IsZeroBuffer (NtpConfigVar.PrimaryDnsServer, sizeof (NtpConfigVar.PrimaryDnsServer))))
        return EFI_INVALID_PARAMETER;

    DnsConfig->DnsServerListCount = 1;
    DnsConfig->DnsServerList = (EFI_IPv4_ADDRESS *) AllocateZeroPool (DnsConfig->DnsServerListCount * sizeof (EFI_IPv4_ADDRESS));

    if (DnsConfig->DnsServerList == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = NetLibStrToIp4 (NtpConfigVar.PrimaryDnsServer, &DnsConfig->DnsServerList[0]);
    if (EFI_ERROR (Status)) {
        FreePool (DnsConfig->DnsServerList);
        DnsConfig->DnsServerList = NULL;
        return Status;
    }

    return Status;
}

/**
    Retrieve the configuration from Setup and set local Ipv4 address.

    @param[in]      NtpConfigAVar    The configuration in Setup.
    @param[in,out]  Private          The Ntp private data.

    @retval  EFI_SUCCESS    Get the Ipv4 address successfully.
    @retval  Other          Fail to get the Ipv4 address.

**/
STATIC
EFI_STATUS
NtpConfigLocalAddr (
    IN      NTP_CONFIGURATION    NtpConfigVar,
    IN OUT  NTP_PRIVATE_DATA     *Private
    )
{
#if defined(MDE_PKG_VERSION) && (MDE_PKG_VERSION >= 10)
    EFI_STATUS                      Status;
    EFI_HANDLE                      *HandleBuffer  = NULL;
    UINTN                           HandleCount    = 0;
    UINTN                           Index          = 0;
    EFI_IP4_CONFIG2_PROTOCOL        *Ip4Config2    = NULL;
    EFI_IP4_CONFIG2_POLICY          Policy;
    EFI_IP4_CONFIG2_MANUAL_ADDRESS  ManualAddress;
    UINTN                           DataSize       = 0;
    EFI_IP4_CONFIG2_INTERFACE_INFO  *InterfaceInfo = NULL;
    UINTN                           TableNum       = 0;

    EFI_EVENT                       TimeoutEvent;
    EFI_EVENT                       SetAddressEvent;
    BOOLEAN                         IsAddressOk;

    if (Private == NULL)
        return EFI_INVALID_PARAMETER;

    Status = gBS->LocateHandleBuffer (
                ByProtocol,
                &gEfiIp4ServiceBindingProtocolGuid,
                NULL,
                &HandleCount,
                &HandleBuffer
                );
    if (EFI_ERROR (Status)) {
        if (HandleBuffer != NULL) {
            FreePool (HandleBuffer);
            HandleBuffer = NULL;
        }
        return Status;
    }

    for (Index = 0; Index < HandleCount; Index++) {
        Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiIp4Config2ProtocolGuid,
                    (VOID **) &Ip4Config2
                    );
        if (EFI_ERROR (Status))
            continue;
        if (Ip4Config2 == NULL) {
            Status = EFI_NOT_FOUND;
            continue;
        }

        Private->ControllerHandle = HandleBuffer[Index];

        if (NtpConfigVar.LocalAddressOpt == Ip4Config2PolicyStatic) {

            Status = NetLibStrToIp4 (NtpConfigVar.LocalAddress, &Private->AddrConfig.SrcAddress);
            if (EFI_ERROR (Status)) continue;

            Status = NetLibStrToIp4 (NtpConfigVar.SubnetMask, &Private->AddrConfig.SubnetMask);
            if (EFI_ERROR (Status)) continue;

            Status = NetLibStrToIp4 (NtpConfigVar.GatewayAddress, &Private->AddrConfig.Gateway);
            if (EFI_ERROR (Status)) continue;

            Status = RetrieveDnsServerIpList (NtpConfigVar, &Private->DnsConfig);
            if (EFI_ERROR (Status)) {
                DEBUG ((DEBUG_ERROR, "[NTP] RetrieveDnsServerIpList %r\n", Status));
                continue;
            }

            Policy = Ip4Config2PolicyStatic;
            Status = Ip4Config2->SetData (
                        Ip4Config2,
                        Ip4Config2DataTypePolicy,
                        sizeof (EFI_IP4_CONFIG2_POLICY),
                        &Policy
                        );
            if (EFI_ERROR (Status)) continue;

            ZeroMem (&ManualAddress, sizeof (ManualAddress));
            TimeoutEvent = NULL;
            SetAddressEvent = NULL;

            Status = NetLibStrToIp4 (NtpConfigVar.LocalAddress, &ManualAddress.Address);
            if (EFI_ERROR (Status)) continue;

            Status = NetLibStrToIp4 (NtpConfigVar.SubnetMask, &ManualAddress.SubnetMask);
            if (EFI_ERROR (Status)) continue;

            //
            // Create events & timers for asynchronous settings.
            //
            Status = gBS->CreateEvent (
                        EVT_TIMER,
                        TPL_CALLBACK,
                        NULL,
                        NULL,
                        &TimeoutEvent
                        );
            if (EFI_ERROR (Status)) {
                continue;
            }

            Status = gBS->CreateEvent (
                        EVT_NOTIFY_SIGNAL,
                        TPL_NOTIFY,
                        NtpConfig2ManualAddressNotify,
                        &IsAddressOk,
                        &SetAddressEvent
                        );
            if (EFI_ERROR (Status)) {
                if (SetAddressEvent != NULL) {
                    gBS->CloseEvent (SetAddressEvent);
                }

                if (TimeoutEvent != NULL) {
                    gBS->CloseEvent (TimeoutEvent);
                }
                continue;
            }

            IsAddressOk = FALSE;

            Status = Ip4Config2->RegisterDataNotify (
                        Ip4Config2,
                        Ip4Config2DataTypeManualAddress,
                        SetAddressEvent
                        );
            if (EFI_ERROR (Status)) {
                if (SetAddressEvent != NULL) {
                    gBS->CloseEvent (SetAddressEvent);
                }

                if (TimeoutEvent != NULL) {
                    gBS->CloseEvent (TimeoutEvent);
                }
                continue;
            }

            //
            // Set ManualAddress.
            //
            DataSize = sizeof (EFI_IP4_CONFIG2_MANUAL_ADDRESS);
            Status = Ip4Config2->SetData (
                        Ip4Config2,
                        Ip4Config2DataTypeManualAddress,
                        DataSize,
                        (VOID *) &ManualAddress
                        );

            if (Status == EFI_NOT_READY) {
                gBS->SetTimer (TimeoutEvent, TimerRelative, 50000000);
                while (EFI_ERROR (gBS->CheckEvent (TimeoutEvent))) {
                    if (IsAddressOk) {
                        Status = EFI_SUCCESS;
                        break;
                    }
                }
            }

            Ip4Config2->UnregisterDataNotify (
                Ip4Config2,
                Ip4Config2DataTypeManualAddress,
                SetAddressEvent
                );

            if (SetAddressEvent != NULL) {
                gBS->CloseEvent (SetAddressEvent);
            }

            if (TimeoutEvent != NULL) {
                gBS->CloseEvent (TimeoutEvent);
            }

            if (EFI_ERROR (Status)) {
                continue;
            }

            //
            // Set Gateway.
            //
            DataSize = sizeof (EFI_IPv4_ADDRESS);
            Status = Ip4Config2->SetData (
                        Ip4Config2,
                        Ip4Config2DataTypeGateway,
                        DataSize,
                        &Private->AddrConfig.Gateway
                        );
            if (EFI_ERROR (Status)) {
                continue;
            }

            //
            //  Set DNS server.
            //
            DataSize = Private->DnsConfig.DnsServerListCount * sizeof (EFI_IPv4_ADDRESS);
            Status = Ip4Config2->SetData (
                        Ip4Config2,
                        Ip4Config2DataTypeDnsServer,
                        DataSize,
                        Private->DnsConfig.DnsServerList
                        );

            if (EFI_ERROR (Status))
                continue;

            break; // Configure success then break
        } else if (NtpConfigVar.LocalAddressOpt == Ip4Config2PolicyDhcp) {
            Policy = Ip4Config2PolicyDhcp;
            Status = Ip4Config2->SetData (
                        Ip4Config2,
                        Ip4Config2DataTypePolicy,
                        sizeof (EFI_IP4_CONFIG2_POLICY),
                        &Policy
                        );
            if (EFI_ERROR (Status)) {
                continue;
            }

            if (!IsIp4ConfigDone (Ip4Config2)) {
                DEBUG ((DEBUG_ERROR, "[NTP] Wait for configuring Ip4 time out. Try to get the configuration.\n"));
            }

            Status = GetIp4Config2Data (
                        Ip4Config2,
                        Ip4Config2DataTypeInterfaceInfo,
                        &DataSize,
                        (VOID **) &InterfaceInfo
                        );
            if (EFI_ERROR (Status)) {
                if (InterfaceInfo != NULL) {
                    FreePool (InterfaceInfo);
                    InterfaceInfo = NULL;
                }
                continue;
            }

            if (InterfaceInfo == NULL) {
                Status = EFI_NOT_FOUND;
                continue;
            }

            for (Index = 0; Index < InterfaceInfo->RouteTableSize; Index++) {
                if (!EFI_IP4_EQUAL (&InterfaceInfo->RouteTable[Index].GatewayAddress, &mZeroIp4Addr)) {
                    TableNum = Index;
                    break;
                }
            }

            IP4_COPY_ADDRESS (&Private->AddrConfig.SrcAddress, &InterfaceInfo->StationAddress);
            IP4_COPY_ADDRESS (&Private->AddrConfig.SubnetMask, &InterfaceInfo->SubnetMask);
            IP4_COPY_ADDRESS (&Private->AddrConfig.Gateway, &InterfaceInfo->RouteTable[TableNum].GatewayAddress);

            if (InterfaceInfo != NULL) {
                FreePool (InterfaceInfo);
                InterfaceInfo = NULL;
            }

            //
            //  DNS server
            //
            DataSize = 0;

            Status = GetIp4Config2Data (
                        Ip4Config2,
                        Ip4Config2DataTypeDnsServer,
                        &DataSize,
                        (VOID **) &Private->DnsConfig.DnsServerList
                        );
            if (EFI_ERROR (Status)) {
                if (Private->DnsConfig.DnsServerList != NULL) {
                    FreePool (Private->DnsConfig.DnsServerList);
                    Private->DnsConfig.DnsServerList = NULL;
                    Private->DnsConfig.DnsServerListCount = 0;
                }
                continue;
            } else if (Private->DnsConfig.DnsServerList == NULL) {
                Status = EFI_NOT_FOUND;
                continue;
            } else {
                Private->DnsConfig.DnsServerListCount = DataSize / sizeof (EFI_IPv4_ADDRESS);
                for (Index = 0; Index < Private->DnsConfig.DnsServerListCount; Index++) {
                    DEBUG ((DEBUG_INFO, "[NTP] DNS server #%d: ", Index));
                    NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->DnsConfig.DnsServerList[Index].Addr);
                }
            }

            if (EFI_ERROR (Status))
                continue;

            break; // Configure success then break
        } else {
            Status = EFI_UNSUPPORTED;
            break;
        }

    }  // End for handle count

    if (HandleBuffer != NULL) {
        FreePool (HandleBuffer);
        HandleBuffer = NULL;
    }

    return Status;
#else
    return EFI_UNSUPPORTED;
#endif
}

/**
    Destroy DNS service and clean related data.

    @param[in]  Private           The Ntp private data.
    @param[in]  ProtocolHandle    The DNS protocol handle.
    @param[in]  Dns4              The DNS protocol.
    @param[in]  Token             Point to the completion token.

    @retval  None

**/
STATIC
VOID
CleanDnsServiceInfo (
    IN  NTP_PRIVATE_DATA             *Private,
    IN  EFI_HANDLE                   ProtocolHandle,
    IN  EFI_DNS4_PROTOCOL            *Dns4,
    IN  EFI_DNS4_COMPLETION_TOKEN    *Token
    )
{
    if (Token != NULL) {
        if (Token->Event != NULL) {
            gBS->CloseEvent (Token->Event);
        }
        if (Token->RspData.H2AData != NULL) {
            if (Token->RspData.H2AData->IpList != NULL) {
                FreePool (Token->RspData.H2AData->IpList);
                Token->RspData.H2AData->IpList = NULL;
            }
            FreePool (Token->RspData.H2AData);
            Token->RspData.H2AData = NULL;
        }
    }

    if (Dns4 != NULL) {
        Dns4->Configure (Dns4, NULL);
        if (Private != NULL) {
            gBS->CloseProtocol (
                ProtocolHandle,
                &gEfiDns4ProtocolGuid,
                Private->ImageHandle,
                Private->ControllerHandle
                );
        }
    }

    if (ProtocolHandle != NULL) {
        if (Private != NULL) {
            NetLibDestroyServiceChild (
                Private->ControllerHandle,
                Private->ImageHandle,
                &gEfiDns4ServiceBindingProtocolGuid,
                ProtocolHandle
                );
        }
    }
}

/**
    Translate the host name of NTP server to Ipv4 address.

    @param[in,out]  Private     The Ntp private data.
    @param[in]      HostName    Name of the NTP server.

    @retval  EFI_SUCCESS    The operation completed successfully.
    @retval  Other          The operation failed.

**/
STATIC
EFI_STATUS
NtpServerAddressFromHostName (
    IN OUT    NTP_PRIVATE_DATA    *Private,
    IN        CHAR16              *HostName
    )
{
    EFI_STATUS                 Status;
    EFI_HANDLE                 ProtocolHandle = NULL;
    EFI_DNS4_PROTOCOL          *Dns4          = NULL;
    EFI_DNS4_CONFIG_DATA       Dns4CfgData;
    EFI_DNS4_COMPLETION_TOKEN  Token;
    BOOLEAN                    IsDone         = FALSE;
    EFI_IPv4_ADDRESS           *ServerAddress = NULL;

    if (Private == NULL || HostName == NULL) {
        DEBUG ((DEBUG_ERROR, "[NTP] Convert server name to address invalid parameter\n"));
        return EFI_INVALID_PARAMETER;
    }

    ZeroMem (&Dns4CfgData, sizeof (Dns4CfgData));
    ZeroMem (&Token, sizeof (Token));

    ServerAddress = &Private->AddrConfig.DstAddress;

    Status = NetLibCreateServiceChild (
                Private->ControllerHandle,
                Private->ImageHandle,
                &gEfiDns4ServiceBindingProtocolGuid,
                &ProtocolHandle
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Create Dns4 service %r\n", Status));
        CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
        return Status;
    }

    Status = gBS->OpenProtocol (
                ProtocolHandle,
                &gEfiDns4ProtocolGuid,
                (VOID **)&Dns4,
                Private->ImageHandle,
                Private->ControllerHandle,
                EFI_OPEN_PROTOCOL_BY_DRIVER
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Open Dns4 protocol %r\n", Status));
        CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
        return Status;
    }

    Dns4CfgData.DnsServerListCount = Private->DnsConfig.DnsServerListCount;
    Dns4CfgData.DnsServerList      = Private->DnsConfig.DnsServerList;
    Dns4CfgData.UseDefaultSetting  = FALSE;

    IP4_COPY_ADDRESS (&Dns4CfgData.StationIp, &Private->AddrConfig.SrcAddress);
    IP4_COPY_ADDRESS (&Dns4CfgData.SubnetMask, &Private->AddrConfig.SubnetMask);

    Dns4CfgData.EnableDnsCache = TRUE;
    Dns4CfgData.Protocol       = EFI_IP_PROTO_UDP;
    Status = Dns4->Configure (
                Dns4,
                &Dns4CfgData
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Configure Dns4 data %r\n", Status));
        CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
        return Status;
    }

    Status = gBS->CreateEvent (
                EVT_NOTIFY_SIGNAL,
                TPL_NOTIFY,
                NtpDnsComplete,
                &IsDone,
                &Token.Event
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Create Dns4 event %r\n", Status));
        CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
        return Status;
    }

    //
    // Start asynchronous name resolution.
    //
    Token.Status = EFI_NOT_READY;
    IsDone       = FALSE;
    Status = Dns4->HostNameToIp (Dns4, HostName, &Token);
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Dns4 resolution HostNameToIp %r\n", Status));
        CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
        return Status;
    }

    while (!IsDone) {
        Dns4->Poll (Dns4);
    }

    //
    // Name resolution is done, check result.
    //
    Status = Token.Status;
    if (!EFI_ERROR (Status)) {
        if (Token.RspData.H2AData == NULL) {
            DEBUG ((DEBUG_ERROR, "[NTP] Dns4 resolution done but response data is NULL!\n"));
            Status = EFI_DEVICE_ERROR;
            CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
            return Status;
        }

        if (Token.RspData.H2AData->IpCount == 0 || Token.RspData.H2AData->IpList == NULL) {
            DEBUG ((DEBUG_ERROR, "[NTP] Dns4 resolution done but some data is NULL!\n"));
            Status = EFI_DEVICE_ERROR;
            CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
            return Status;
        }

        //
        // Return the first IP address from DNS.
        //
        IP4_COPY_ADDRESS (ServerAddress, Token.RspData.H2AData->IpList);
        Status = EFI_SUCCESS;

        DEBUG ((DEBUG_INFO, "[NTP] NTP server:\n"));
        NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, ServerAddress->Addr);
    } else if (Status == EFI_TIMEOUT) {
        DEBUG ((DEBUG_ERROR, "[NTP] NTP server resolution time out.\n"));
    } else {
        DEBUG ((DEBUG_ERROR, "[NTP] NTP server resolution failed.\n"));
    }

    DEBUG ((DEBUG_INFO, "[NTP] NTP server resolution %r\n", Status));
    CleanDnsServiceInfo (Private, ProtocolHandle, Dns4, &Token);
    return Status;
}

/**
    Configure NTP server information.

    @param[in]      NtpConfigVar    The configuration in Setup.
    @param[in,out]  Private         The Ntp private data.

    @retval  EFI_SUCCESS    The operation completed successfully.
    @retval  Other          The operation failed.

**/
STATIC
EFI_STATUS
NtpConfigServerInfo (
    IN      NTP_CONFIGURATION    NtpConfigVar,
    IN OUT  NTP_PRIVATE_DATA     *Private
    )
{
    if (Private == NULL)
        return EFI_INVALID_PARAMETER;

    if (NtpConfigVar.NtpServerOpt == NTP_SERVER_OPT_DEFAULT) {
        Private->AddrConfig.DestPort = NTP_SERVER_PORT;
        return NtpServerAddressFromHostName (Private, NTP_DEFAULT_SERVER_HOSTNAME);
    } else if (NtpConfigVar.NtpServerOpt == NTP_SERVER_OPT_MANUAL) {
        if (IsZeroBuffer (NtpConfigVar.NtpServerName, sizeof (NtpConfigVar.NtpServerName))) {
            return EFI_INVALID_PARAMETER;
        }
        Private->AddrConfig.DestPort = NTP_SERVER_PORT;
        return NtpServerAddressFromHostName (Private, NtpConfigVar.NtpServerName);
    }

    return EFI_UNSUPPORTED;
}

/**
    Configure a UDP IO to receive packets.

    @param[in]  UdpIo      The UDP IO to configure.
    @param[in]  Context    The context to the function.

    @retval  EFI_SUCCESS    The UDP IO is successfully configured.
    @retval  Other          Failed to configure the UDP child.

**/
EFI_STATUS
EFIAPI
NtpConfigUdpIo (
    IN  UDP_IO    *UdpIo,
    IN  VOID      *Context
    )
{
    EFI_UDP4_CONFIG_DATA  UdpConfigData;
    NTP_PRIVATE_DATA      *UdpConfig;

    UdpConfig = (NTP_PRIVATE_DATA *) Context;

    ZeroMem (&UdpConfigData, sizeof (EFI_UDP4_CONFIG_DATA));

    UdpConfigData.AcceptBroadcast    = TRUE;
    UdpConfigData.AcceptPromiscuous  = FALSE;
    UdpConfigData.AcceptAnyPort      = FALSE;
    UdpConfigData.AllowDuplicatePort = TRUE;
    UdpConfigData.TypeOfService      = 0;
    UdpConfigData.TimeToLive         = 64;
    UdpConfigData.DoNotFragment      = FALSE;
    UdpConfigData.ReceiveTimeout     = 0;
    UdpConfigData.TransmitTimeout    = 0;

    UdpConfigData.UseDefaultAddress  = FALSE;
    UdpConfigData.StationPort        = 0;
    UdpConfigData.RemotePort         = UdpConfig->AddrConfig.DestPort;

    ZeroMem (&UdpConfigData.StationAddress, sizeof (EFI_IPv4_ADDRESS));
    ZeroMem (&UdpConfigData.SubnetMask, sizeof (EFI_IPv4_ADDRESS));
    ZeroMem (&UdpConfigData.RemoteAddress, sizeof (EFI_IPv4_ADDRESS));

    IP4_COPY_ADDRESS (&UdpConfigData.StationAddress, &UdpConfig->AddrConfig.SrcAddress);
    IP4_COPY_ADDRESS (&UdpConfigData.RemoteAddress, &UdpConfig->AddrConfig.DstAddress);
    IP4_COPY_ADDRESS (&UdpConfigData.SubnetMask, &UdpConfig->AddrConfig.SubnetMask);

    return UdpIo->Protocol.Udp4->Configure (UdpIo->Protocol.Udp4, &UdpConfigData);;
}

/**
    Callback function for the net buffer to release the packet.

    @param[in]  Arg    The packet to release

    @retval  None

**/
VOID
EFIAPI
NtpPacketFree (
    IN  VOID    *Arg
    )
{
    FreePool (Arg);
}

/**
    Get and record current processor timer value.

    @param  None

    @retval  None

**/
STATIC
VOID
RecordCurrentTime (
    VOID
    )
{
    EFI_STATUS  Status;

    gCurrentTick = 0;
    gTimerPeriod = 0;

    if (gCpuArchProtocol == NULL) {
        Status = gBS->LocateProtocol (
                    &gEfiCpuArchProtocolGuid,
                    NULL,
                    (VOID **) &gCpuArchProtocol
                    );
        if (EFI_ERROR (Status)) {
            return;
        }
    }

    if (gCpuArchProtocol != NULL) {
        Status = gCpuArchProtocol->GetTimerValue (gCpuArchProtocol, 0, &gCurrentTick, &gTimerPeriod);
        if (EFI_ERROR (Status)) {
            gCurrentTick = 0;
            gTimerPeriod = 0;
        }
    }
}

/**
    Release the net buffer when packet is sent.

    @param[in]  Packet      The UDP packets received.
    @param[in]  EndPoint    The local/remote UDP access point
    @param[in]  IoStatus    The status of the UDP receive
    @param[in]  Context     The opaque parameter to the function.

    @retval  None

**/
VOID
EFIAPI
NtpOnPacketSent (
    IN  NET_BUF          *Packet,
    IN  UDP_END_POINT    *EndPoint,
    IN  EFI_STATUS       IoStatus,
    IN  VOID             *Context
    )
{
    NetbufFree (Packet);
}

/**
    Calculate current time value to be filled in sending packet.

    @param[in,out]  TimeStamp    The buffer for the time stamp.

    @retval  None

**/
STATIC
VOID
LocalTimeStampConstruct (
    IN OUT  NTP_UINT64    *TimeStamp
    )
{
    UINT32      Second    = 0;
    UINT32      TotalDays = 0;
    UINTN       YearCount = 0;
    EFI_STATUS  Status;
    EFI_TIME    Time;

    ZeroMem (&Time, sizeof (Time));

    Status = gRT->GetTime (&Time, NULL);

    // Use local TimeStamp.
    if (TimeStamp == NULL || EFI_ERROR (Status) || Time.Year < 1900 || Time.Year >= 2036) {
        // Record current TimeStamp.
        RecordCurrentTime ();
        DEBUG ((DEBUG_ERROR, "[NTP] GetTime failed. Record current time tick 0x%x\n", gCurrentTick));
        return;
    }

    // Construct TimeStamp for NTP format.
    TotalDays = 0;
    for (YearCount = 1900; YearCount < Time.Year; YearCount++) {
        TotalDays += (UINT32) gCumulativeDays [IsLeap (YearCount)][11];
    }

    if (Time.Month > 1) {
        TotalDays += (UINT32) gCumulativeDays [IsLeap (Time.Year)][(Time.Month - 1) - 1];
    }

    TotalDays += (Time.Day - 1);

    Second = TotalDays * SECSPERDAY + Time.Hour * SECSPERHOUR +
             Time.Minute * SECSPERMIN + Time.Second;

    TimeStamp->Hi = (UINT32) NTOHL (Second);
}

/**
    Configure NTP packet and sent it to server.

    @param[in,out]  Private    The Ntp private data.

    @retval  EFI_SUCCESS    The UDP IO is successfully configured.
    @retval  Other          Failed to configure the UDP child.

**/
STATIC
EFI_STATUS
NtpSendRequestPacket (
    IN OUT  NTP_PRIVATE_DATA    *Private
    )
{
    EFI_STATUS      Status;
    NTP_PACKET      *NtpPacket = NULL;
    UINT32          PacketSize = 0;
    NET_FRAGMENT    Frag;
    NET_BUF         *Wrap      = NULL;
    UDP_END_POINT   EndPoint;
    EFI_IP_ADDRESS  Gateway;

    // Configure NTP sending packet.
    PacketSize = sizeof (NTP_PACKET);
    NtpPacket = (NTP_PACKET *) AllocateZeroPool (PacketSize);
    if (NtpPacket == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    NtpPacket->Lvm = NTP_TO_LVM (NTP_LEAP_UNKNOWN, NTP_VERSION, NTP_CLIENT_MODE);
    LocalTimeStampConstruct (&NtpPacket->TransmitTimeStamp);

    DEBUG ((DEBUG_INFO, "[NTP] Ntp LocalTimeStamp Hi : 0x%x\n", NtpPacket->TransmitTimeStamp.Hi));

    //
    // Wrap the NTP packet into a net buffer.
    //
    Frag.Bulk = (UINT8 *) NtpPacket;
    Frag.Len  = PacketSize;
    Wrap      = NetbufFromExt (&Frag, 1, 0, 0, NtpPacketFree, NtpPacket);
    if (Wrap == NULL) {
        DEBUG ((DEBUG_ERROR, "[NTP] Ntp packet created failed.\n"));
        Status = EFI_OUT_OF_RESOURCES;
        FreePool (NtpPacket);
        return Status;
    }

    //
    // Set the local address and local port to ZERO.
    //
    ZeroMem (&EndPoint, sizeof (UDP_END_POINT));

    //
    // Set the destination address and destination port.
    //
    IP4_COPY_ADDRESS (&EndPoint.RemoteAddr.v4, &Private->AddrConfig.DstAddress);
    EndPoint.RemoteAddr.Addr[0] = EFI_NTOHL (Private->AddrConfig.DstAddress);
    EndPoint.RemotePort = Private->AddrConfig.DestPort;

    //
    // Set the local address and gateway.
    //
    IP4_COPY_ADDRESS (&EndPoint.LocalAddr.v4, &Private->AddrConfig.SrcAddress);
    EndPoint.LocalAddr.Addr[0] = EFI_NTOHL (Private->AddrConfig.SrcAddress);
    EndPoint.LocalPort = 0;

    ZeroMem (&Gateway, sizeof (EFI_IP_ADDRESS));
    IP4_COPY_ADDRESS (&Gateway.v4, &Private->AddrConfig.Gateway);
    Gateway.Addr[0] = EFI_NTOHL (Private->AddrConfig.Gateway);

    //
    // Transmit the NTP packet.
    //
    Status = UdpIoSendDatagram (
                Private->UdpIo,
                Wrap,
                &EndPoint,
                &Gateway,
                NtpOnPacketSent,
                (VOID *) Private
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Ntp packet sending failed.\n"));
        if (Wrap != NULL) {
            NetbufFree (Wrap);
            Wrap = NULL;
        }
    }

    return Status;
}

/**
    Clean up the private data.

    @param[in,out]  Private    The Ntp private data.

    @retval  None

**/
STATIC
VOID
NtpSyncDone (
    IN OUT  NTP_PRIVATE_DATA    **Private
    )
{
    if (*Private == NULL) {
        return;
    }

    if ((*Private)->TimeoutEvent != NULL) {
        gBS->SetTimer ((*Private)->TimeoutEvent, TimerCancel, 0);
        gBS->CloseEvent ((*Private)->TimeoutEvent);
        (*Private)->TimeoutEvent = NULL;
        DEBUG ((DEBUG_INFO, "[NTP] Close Ntp time out event.\n"));
    }

    if ((*Private)->DnsConfig.DnsServerList != NULL) {
        FreePool ((*Private)->DnsConfig.DnsServerList);
        (*Private)->DnsConfig.DnsServerList = NULL;
    }

    if ((*Private)->UdpIo == NULL) {
        FreePool ((*Private));
        (*Private) = NULL;
        return;
    }

    UdpIoCleanIo ((*Private)->UdpIo);
    gBS->CloseProtocol (
        (*Private)->UdpIo->UdpHandle,
        &gEfiUdp4ProtocolGuid,
        (*Private)->ImageHandle,
        (*Private)->ControllerHandle
        );

    UdpIoFreeIo ((*Private)->UdpIo);
    (*Private)->UdpIo = NULL;

    FreePool ((*Private));
    (*Private) = NULL;
}

/**
    Handle the received packets.

    @param[in]  UdpPacket    The UDP packets received.
    @param[in]  EndPoint     The local/remote UDP access point.
    @param[in]  IoStatus     The status of the UDP receive.
    @param[in]  Context      The opaque parameter to the function.

    @retval  None

**/
VOID
EFIAPI
NtpPacketReceive (
    IN  NET_BUF          *UdpPacket,
    IN  UDP_END_POINT    *EndPoint,
    IN  EFI_STATUS       IoStatus,
    IN  VOID             *Context
    )
{
    NTP_PRIVATE_DATA  *Private   = NULL;
    UINT32            Len        = 0;
    UINTN             PacketSize = 0;

    Private = (NTP_PRIVATE_DATA*) Context;

    DEBUG ((DEBUG_INFO, "[NTP] **NtpReceive....\n"));

    if (EFI_ERROR (IoStatus)) {
        DEBUG ((DEBUG_ERROR, "[NTP] NtpPacketReceive IoStatus %r\n", IoStatus));
        if (UdpPacket != NULL) {
            NetbufFree (UdpPacket);
        }
        return;
    }

    if (UdpPacket == NULL) {
        DEBUG ((DEBUG_ERROR, "[NTP] NtpPacketReceive UdpPacket is NULL.\n"));
        return;
    }

    //
    // Validate the packet received
    //
    if (UdpPacket->TotalSize < sizeof (NTP_PACKET)) {
        NetbufFree (UdpPacket);
        return;
    }

    Len = UdpPacket->TotalSize;

    PacketSize = NetbufCopy (UdpPacket, 0, Len, (UINT8*)&Private->NtpPacket);

    if (Len != PacketSize) {
        DEBUG ((DEBUG_ERROR, "[NTP] NtpPacketReceive Len != PacketSize\n"));
        ZeroMem (&Private->NtpPacket, sizeof (Private->NtpPacket));
        NetbufFree (UdpPacket);
        return;
    }

    if (UdpPacket != NULL) {
        NetbufFree (UdpPacket);
    }

    if (PacketSize != 0) {
        gCompleted = TRUE;
    }

    DEBUG ((DEBUG_INFO, "[NTP] NtpPacketReceive End.\n"));
}

/**
    Create a process of receiving response.

    @param[in,out]  Private    The Ntp private data.

    @retval EFI_SUCCESS    The receiving process has been started.
    @retval Others         Failed to start the receiving process.

**/
STATIC
EFI_STATUS
NtpReceiveResponsePacket (
    IN OUT  NTP_PRIVATE_DATA    *Private
    )
{
    EFI_STATUS  Status = EFI_NOT_READY;

    if (Private == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (!gCompleted) {
        DEBUG ((DEBUG_INFO, "[NTP] Start to receive NTP response.\n"));

        // Start to receive the NTP response.
        Status = UdpIoRecvDatagram (Private->UdpIo, NtpPacketReceive, Private, 0);
        if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_ERROR, "[NTP] Create UdpIoRecvDatagram %r\n", Status));
            return Status;
        }

        DEBUG ((DEBUG_INFO, "[NTP] UdpIoRecvDatagram End %r\n", Status));
    }

    return Status;
}

/**
    Calculate delay time of the transmission.

    The delay time of the NTP is (CurrentTime - OriginateTime) - (EndTime - StartTime).
    CurrentTime is the local/client time stamp when receiving the response packet.

    @param[in]  StartTime        The server time stamp when receiving a request packet.
    @param[in]  EndTime          The server time stamp when sending a response packet.
    @param[in]  OriginateTime    The local/client time stamp when sending a request packet.

    @return  Delay time.

**/
STATIC
UINTN
DelayTimeCalculate (
    IN  UINTN    StartTime,
    IN  UINTN    EndTime,
    IN  UINTN    OriginateTime
    )
{
    UINT64      Delay      = 0;
    UINTN       TotalDays  = 0;
    EFI_TIME    Time;
    EFI_STATUS  Status;
    UINTN       YearCount;
    UINTN       Second;

    if (OriginateTime != 0) {
        // Use system time.
        ZeroMem (&Time, sizeof (Time));
        Status = gRT->GetTime (&Time, NULL);

        if (EFI_ERROR (Status) || Time.Year < 1900 || Time.Year >= 2036) {
            Delay = 0;
        } else {
            for (YearCount = 1900; YearCount < Time.Year; YearCount++) {
                TotalDays += gCumulativeDays [IsLeap (YearCount)][11];
            }
            if (Time.Month > 1) {
                TotalDays += gCumulativeDays [IsLeap (Time.Year)][(Time.Month - 1) - 1];
            }
            TotalDays += (Time.Day - 1);

            Second = TotalDays * SECSPERDAY + Time.Hour * SECSPERHOUR +
                     Time.Minute * SECSPERMIN + Time.Second;
            Delay = (UINT64) ((Second - OriginateTime) - (EndTime - StartTime));
        }

        DEBUG ((DEBUG_INFO, "[NTP] Delay Time of the transmission: 0x%x\n", Delay));
    } else {
        // Use local timer.

        UINT64    FormerTick = gCurrentTick;

        RecordCurrentTime ();
        DEBUG ((DEBUG_INFO, "[NTP] FormerTick 0x%x, gCurrentTick 0x%x\n", FormerTick, gCurrentTick));

        if (gCurrentTick == 0)
            return 0;

        gFrequency = DivU64x64Remainder (1000000000000000ULL, gTimerPeriod, NULL);
        DEBUG ((DEBUG_INFO, "[NTP] gFrequency 0x%x\n", gFrequency));

        Delay = (gCurrentTick - FormerTick);
        Delay = DivU64x64Remainder (Delay, gFrequency, NULL); // in second
        DEBUG ((DEBUG_INFO, "[NTP] Delay Time: 0x%d \n", Delay));

        if (Delay >= (EndTime - StartTime)) {
            Delay = Delay - (EndTime - StartTime);
            DEBUG ((DEBUG_INFO, "[NTP] Delay Time of the transmission: 0x%x\n", Delay));
        } else
            Delay = 0;
    }

    DEBUG ((DEBUG_INFO, "[NTP] Final Delay Time: 0x%x\n", Delay));

    return (UINTN) Delay;
}

/**
    Convert the NTP time format to EFI_TIME.

    @param[in]      Private          The Ntp private data.
    @param[in,out]  Time             The buffer of EFI_TIME to be updated to system.
    @param[in]      NtpAdjustTime    The configuration in Setup.

    @retval EFI_SUCCESS    The time is converted successfully.

**/
STATIC
EFI_STATUS
NtpConvertTime (
    IN      NTP_PRIVATE_DATA          *Private,
    IN OUT  EFI_TIME                  *Time,
    IN      NTP_CONFIG_ADJUST_TIME    NtpAdjustTime
    )
{
    UINTN  Year       = 0, Month         = 0, Day         = 0;
    UINTN  Hour       = 0, Min           = 0, Second      = 0;
    UINTN  Days       = 0, DayRemainder  = 0;
    UINTN  TransmitTs = 0, ReceiveTs     = 0, OriginateTs = 0;
    UINTN  MonthCount = 0, HourRemainder = 0;
    UINTN  Delay      = 0;
    UINTN  AdjustedTs = 0;
    INT16  TimeZone   = 0;
    UINT8  Daylight   = 0;
    UINTN  TotalDays;

    if (Private == NULL || Time == NULL)
        return EFI_INVALID_PARAMETER;

    TransmitTs  = (UINTN) NTOHL (Private->NtpPacket.TransmitTimeStamp.Hi);
    ReceiveTs   = (UINTN) NTOHL (Private->NtpPacket.ReceiveTimeStamp.Hi);
    OriginateTs = (UINTN) NTOHL (Private->NtpPacket.OriginateTimeStamp.Hi);

    //
    // Adjust time with delay.
    //
    Delay = DelayTimeCalculate (ReceiveTs, TransmitTs, OriginateTs);
    AdjustedTs = TransmitTs + Delay;

    //
    // Adjust time with time zone and daylight saving time.
    //
    if (GetTimeZoneValue (NtpAdjustTime.TimeZoneOpt, &TimeZone)) {
        AdjustedTs += TimeZone * SECSPERMIN;
    } else {
        DEBUG ((DEBUG_ERROR, "[NTP] Time zone offset is not found.\n"));
    }

    if (NtpAdjustTime.Daylight) {
        AdjustedTs += SECSPERHOUR;
        TimeZone += MINPERHOUR;
        Daylight = EFI_TIME_IN_DAYLIGHT;
    }

    Days = DivU64x64Remainder (AdjustedTs, SECSPERDAY, &DayRemainder);
    Hour = DivU64x64Remainder (DayRemainder, SECSPERHOUR, &HourRemainder);
    Min  = DivU64x64Remainder (HourRemainder, SECSPERMIN, &Second);

    for (Year = 1900; Days > 0; Year++) {
        TotalDays = gCumulativeDays [IsLeap(Year)][11];
        if (Days >= TotalDays) {
            Days = Days - TotalDays;
        } else {
            break;
        }
    }

    for (MonthCount = 12; MonthCount > 0; MonthCount--) {
        TotalDays =  gCumulativeDays [IsLeap(Year)][MonthCount - 1];
        if (Days >= TotalDays) {
            Days = Days - TotalDays;
            Month = MonthCount + 1;
            break;
        }
    }

    if (Month == 0)
        Month = Month + 1;

    Day = Days + 1;

    DEBUG ((DEBUG_INFO, "[NTP] Year :%d, Month :%d, Day :%d\n", Year, Month, Day));
    DEBUG ((DEBUG_INFO, "[NTP] Hour :%d, Minute :%d, Second :%d\n", Hour, Min, Second));

    Time->Day      = (UINT8)  Day;
    Time->Month    = (UINT8)  Month;
    Time->Year     = (UINT16) Year;
    Time->Hour     = (UINT8)  Hour;
    Time->Minute   = (UINT8)  Min;
    Time->Second   = (UINT8)  Second;
    Time->TimeZone = (INT16)  (-TimeZone); // Adjust to UEFI format:Localtime = UTC - TimeZone (in minutes).
    Time->Daylight = (UINT8)  Daylight;

    return EFI_SUCCESS;
}

/**
    Handle the NTP time stamp translation and update time to system.

    @param[in]  Private                   The Ntp private data.
    @param[in]  NtpConfigAdjustTimeVar    The configuration in Setup.

    @retval  EFI_SUCCESS    The operation completed successfully.
    @retval  Other          The operation failed.

**/
STATIC
EFI_STATUS
NtpTimeUpdate (
    IN  NTP_PRIVATE_DATA          *Private,
    IN  NTP_CONFIG_ADJUST_TIME    NtpConfigAdjustTimeVar
    )
{
    EFI_STATUS  Status;
    EFI_TIME    Time;

    if (Private == NULL)
        return EFI_INVALID_PARAMETER;

    DEBUG ((DEBUG_INFO, "[NTP] Translate to EFI_TIME...\n"));

    //
    // Convert to EFI_TIME.
    //
    ZeroMem (&Time, sizeof (Time));

    Status = NtpConvertTime (Private, &Time, NtpConfigAdjustTimeVar);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    DEBUG ((DEBUG_INFO, "[NTP] EFI_TIME. %d/%d/%d %d:%d:%d\n",
                         Time.Year, Time.Month, Time.Day,
                         Time.Hour, Time.Minute, Time.Second
                         ));

    //
    // Update time to system.
    //
    Status = gRT->SetTime (&Time);
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Set EFI_TIME %r\n", Status));
        return Status;
    }

    DEBUG ((DEBUG_INFO, "[NTP] Set EFI_TIME finish.\n"));

    return Status;
}

/**
    Check the configuration is changed.

    @param[in]   NtpConfigSupportVar           The configuration in Setup.
    @param[in]   NtpConfigSupportVarSize       The size of NtpConfigVar.
    @param[in]   NtpConfigVar                  The configuration in Setup.
    @param[in]   NtpConfigVarSize              The size of NtpConfigAddrVar.
    @param[in]   NtpConfigAdjustTimeVar        The configuration in Setup.
    @param[in]   NtpConfigAdjustTimeVarSize    The size of NtpConfigAdjustTimeVar.
    @param[in]   SetupVarGuid                  The GUID of the variable to get configuration.
    @param[out]  Ischanged                     TRUE  - The configuration has changed.
                                               FALSE - The configuration is not changed.

    @retval  EFI_SUCCESS    The operation completed successfully.
    @retval  Other          The operation failed.

**/
STATIC
EFI_STATUS
IsConfigChanged (
    IN      NTP_CONFIG_SUPPORT        NtpConfigSupportVar,
    IN      UINTN                     NtpConfigSupportVarSize,
    IN      NTP_CONFIGURATION         NtpConfigVar,
    IN      UINTN                     NtpConfigVarSize,
    IN      NTP_CONFIG_ADJUST_TIME    NtpConfigAdjustTimeVar,
    IN      UINTN                     NtpConfigAdjustTimeVarSize,
    IN      EFI_GUID                  *SetupVarGuid,
       OUT  BOOLEAN                   *Ischanged
    )
{
    NTP_CONFIG_SUPPORT      ConfigSupport;
    NTP_CONFIGURATION       Config;
    NTP_CONFIG_ADJUST_TIME  ConfigAdjustTime;
    UINTN                   ConfigSupportSize    = 0;
    UINTN                   ConfigSize           = 0;
    UINTN                   ConfigAdjustTimeSize = 0;

    *Ischanged = FALSE;

    if (NtpConfigSupportVarSize == 0 || NtpConfigVarSize == 0 || NtpConfigAdjustTimeVarSize == 0)
        return EFI_INVALID_PARAMETER;

    ConfigSupportSize    = sizeof (ConfigSupport);
    ConfigSize           = sizeof (Config);
    ConfigAdjustTimeSize = sizeof (ConfigAdjustTime);

    if (ConfigSupportSize != NtpConfigSupportVarSize || ConfigSize != NtpConfigVarSize || ConfigAdjustTimeSize != NtpConfigAdjustTimeVarSize)
        return EFI_INVALID_PARAMETER;

    ZeroMem (&ConfigSupport, ConfigSupportSize);
    ZeroMem (&Config, ConfigSize);
    ZeroMem (&ConfigAdjustTime, ConfigAdjustTimeSize);

    if (!HiiGetBrowserData (
             SetupVarGuid,
             NTP_CONFIG_SUPPORT_VARIABLE_NAME,
             ConfigSupportSize,
             (UINT8*) &ConfigSupport
             )
        ) {
        return EFI_NOT_FOUND;
    }

    if (CompareMem (&ConfigSupport, &NtpConfigSupportVar, NtpConfigSupportVarSize) != 0) {
        *Ischanged = TRUE;
    }

    if (!HiiGetBrowserData (
             SetupVarGuid,
             NTP_CONFIGURATION_VARIABLE_NAME,
             ConfigSize,
             (UINT8*) &Config
             )
        ) {
        return EFI_NOT_FOUND;
    }

    if (Config.LocalAddressOpt == NTP_CONFIG_LOCAL_IP_STATIC) {
        if (IsZeroBuffer (Config.LocalAddress, sizeof (Config.LocalAddress))         ||
            IsZeroBuffer (Config.GatewayAddress, sizeof (Config.GatewayAddress))     ||
            IsZeroBuffer (Config.SubnetMask, sizeof (Config.SubnetMask))             ||
            IsZeroBuffer (Config.PrimaryDnsServer, sizeof (Config.PrimaryDnsServer))
            ) {
            return EFI_ABORTED;
        }
    }

    if (Config.NtpServerOpt == NTP_SERVER_OPT_MANUAL) {
        if (IsZeroBuffer (Config.NtpServerName, sizeof (Config.NtpServerName))) {
            return EFI_ABORTED;
        }
    }

    if (CompareMem (&Config, &NtpConfigVar, NtpConfigVarSize) != 0) {
        *Ischanged = TRUE;
    }

    if (!HiiGetBrowserData (
             SetupVarGuid,
             NTP_CONFIG_ADJUST_TIME_VARIABLE_NAME,
             ConfigAdjustTimeSize,
             (UINT8*) &ConfigAdjustTime
             )
        ) {
        return EFI_NOT_FOUND;
    }

    if (CompareMem (&ConfigAdjustTime, &NtpConfigAdjustTimeVar, NtpConfigAdjustTimeVarSize) != 0) {
        *Ischanged = TRUE;
    }

    return EFI_SUCCESS;
}

/**
    Display an error or a success message box.
    If it's a success message, get and display current time.

    @param[in]  Success    TRUE  - Display current time message box.
                           FALSE - Display an error message.

    @retval  None

**/
STATIC
VOID
DisplaySuccessMsg (
    IN  BOOLEAN    Success
    )
{
    EFI_STATUS  Status;
    EFI_TIME    Time;
    CHAR16      OutputStr[20]; // String display form : "mm/dd/yyyy hh:mm:ss".
    CHAR16      *Title        = NULL;

    if (!Success) {
        DisplayInfoMsg (
            StrTokenDisplayTitleTimeUpdate,
            StrTokenDisplayMsgTimeUpdateFailed,
            MSGBOX_TYPE_OK,
            NULL
            );
        return;
    }

    ZeroMem (&Time, sizeof (EFI_TIME));
    ZeroMem (OutputStr, sizeof (OutputStr));

    Status = gRT->GetTime (&Time, NULL);
    if (EFI_ERROR (Status)) {
        return;
    }

    UnicodeSPrint (
        OutputStr,
        sizeof (OutputStr),
        L"%02d/%02d/%04d %02d:%02d:%02d",
        Time.Month, Time.Day, Time.Year,
        Time.Hour, Time.Minute, Time.Second
        );

    if (gAmiPostMgr == NULL) {
        Status = gBS->LocateProtocol (
                    &gAmiPostManagerProtocolGuid,
                    NULL,
                    (VOID **) &gAmiPostMgr
                    );
        if (EFI_ERROR (Status)) {
            return;
        }
    }

    Title = GetTokenString (StrTokenDisplayTitleTimeUpdate, NULL);

    if (Title != NULL && gAmiPostMgr != NULL) {
        gAmiPostMgr->DisplayMsgBox (
            Title,
            OutputStr,
            MSGBOX_TYPE_OK,
            NULL
            );
    }

    if (Title != NULL) {
       FreePool (Title);
       Title = NULL;
    }
}

/**
    Callback function for updating the Progress Box.

    @param[in]  Event      The triggered event.
    @param[in]  Context    The parameter to the function.

    @retval  None

**/
VOID
EFIAPI
ProgressIncrease (
    IN  EFI_EVENT    Event,
    IN  VOID         *Context
    )
{
    if (gPercent < 90)
        gPercent ++;

    DisplayProgressMsg (
        AMI_PROGRESS_BOX_UPDATE,
        gPercent,
        &gHandle,
        &gOutKey
        );
}

/**
    Clear the timer event to terminate the progress updating.

    @param[in]  Event    The event to be closed.

    @retval  None

**/
STATIC
VOID
TerminateProgressEvent (
    IN OUT  EFI_EVENT    *Event
    )
{
    if (*Event == NULL)
        return;

    gBS->SetTimer (*Event, TimerCancel, 0);
    gBS->CloseEvent (*Event);
    *Event = NULL;
}

/**
    Verify Ipv4 address.

    @param[in]  IpStr    String of the Ipv4 address.

    @retval  TRUE     The address is valid.
    @retval  FALSE    The address is invalid.

**/
STATIC
BOOLEAN
NtpValidateIp (
    IN  CHAR16    *IpStr
    )
{
    UINTN  Index       = 0;
    UINTN  Number      = 0;
    UINTN  NumberCount = 0;

    if (IpStr == NULL)
        return FALSE;

    while (*IpStr != L'\0') {
        if (Index > 3)
            return FALSE;

        if (*IpStr == L'.') {
            if (NumberCount == 0)
                return FALSE;
            IpStr++;
            Index++;
            Number = 0;
            NumberCount = 0;
            continue;
        }

        if ((*IpStr >= L'0') && (*IpStr <= L'9')) {
            Number = Number * 10 + (*IpStr - L'0');
        } else if ((*IpStr != L'\0') && (*IpStr != L'.')) {
            return FALSE;
        }

        if (Number > 0xFF)
            return FALSE;

        IpStr++;
        NumberCount++;
    }

    if (Index != 3 || NumberCount == 0) {
        return FALSE;
    }

    return TRUE;
}

/**
    Perform the NTP synchronization.

    @param[in]  SetupVarGuid    The GUID of the variable to get configuration.
    @param[in]  DriverHandle    The driver image handle.

    @retval  None

**/
VOID
EFIAPI
NtpSyncStartImpl (
    IN  EFI_GUID      *SetupVarGuid,
    IN  EFI_HANDLE    DriverHandle
    )
{
    EFI_STATUS              Status;
    UINT32                  VariableAttributes         = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    NTP_CONFIGURATION       NtpConfigVar;
    NTP_CONFIG_SUPPORT      NtpConfigSupportVar;
    NTP_CONFIG_ADJUST_TIME  NtpConfigAdjustTimeVar;
    UINTN                   NtpConfigVarSize           = 0;
    UINTN                   NtpConfigSupportVarSize    = 0;
    UINTN                   NtpConfigAdjustTimeVarSize = 0;
    BOOLEAN                 IsChanged                  = 0;
    NTP_PRIVATE_DATA        *Private                   = NULL;
    UINT8                   MsgCheckKey;
    UINTN                   Index                      = 0;
    EFI_EVENT               ProgressEvent              = NULL;
    EFI_STATUS              TimeoutStatus;

    NtpConfigVarSize = sizeof (NtpConfigVar);
    Status = gRT->GetVariable (
                NTP_CONFIGURATION_VARIABLE_NAME,
                SetupVarGuid,
                &VariableAttributes,
                &NtpConfigVarSize,
                &NtpConfigVar
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] GetVariable NtpConfigAddrVar Status: %r\n", Status));
        return;
    }

    NtpConfigSupportVarSize = sizeof (NtpConfigSupportVar);
    Status = gRT->GetVariable (
                NTP_CONFIG_SUPPORT_VARIABLE_NAME,
                SetupVarGuid,
                &VariableAttributes,
                &NtpConfigSupportVarSize,
                &NtpConfigSupportVar
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] GetVariable NtpConfigVar Status: %r\n", Status));
        return;
    }

    NtpConfigAdjustTimeVarSize = sizeof (NtpConfigAdjustTimeVar);
    Status = gRT->GetVariable (
                NTP_CONFIG_ADJUST_TIME_VARIABLE_NAME,
                SetupVarGuid,
                &VariableAttributes,
                &NtpConfigAdjustTimeVarSize,
                &NtpConfigAdjustTimeVar
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] GetVariable NtpConfigAdjustTime Status: %r\n", Status));
        return;
    }

    Status = IsConfigChanged (
                NtpConfigSupportVar,
                NtpConfigSupportVarSize,
                NtpConfigVar,
                NtpConfigVarSize,
                NtpConfigAdjustTimeVar,
                NtpConfigAdjustTimeVarSize,
                SetupVarGuid,
                &IsChanged
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] GetBrowserData Status: %r\n", Status));
        if (Status == EFI_ABORTED) {
            DisplayInfoMsg (
                StrTokenDisplayTitleConfigFailed,
                StrTokenDisplayMsgConfigCheck,
                MSGBOX_TYPE_OK,
                NULL
                );
        } else {
            DisplayInfoMsg (
                StrTokenDisplayTitleConfigFailed,
                StrTokenDisplayMsgConfigRetry,
                MSGBOX_TYPE_OK,
                NULL
                );
        }

        return;
    }

    if (IsChanged) {
        DisplayInfoMsg (
            StrTokenDisplayTitleConfigChanged,
            StrTokenDisplayMsgConfigSave,
            MSGBOX_TYPE_OK,
            NULL
            );
        return;
    }

    DisplayInfoMsg (
        StrTokenDisplayTitleSyncConfirm,
        StrTokenDisplayMsgSyncConfirm,
        MSGBOX_TYPE_YESNO,
        &MsgCheckKey
        );
    if (MsgCheckKey == MSGBOX_NO)
        return;

    Private = (NTP_PRIVATE_DATA *) AllocateZeroPool (sizeof (NTP_PRIVATE_DATA));
    if (Private == NULL) {
        DEBUG ((DEBUG_ERROR, "[NTP] Allocate pool for NTP_PRIVATE_DATA failed!\n"));
        return;
    }

    Private->ImageHandle = DriverHandle; // Driver image handle
    gCompleted           = FALSE;
    gCurrentTick         = 0;
    gTimerPeriod         = 0;
    gPercent             = 0;

    gHandle              = NULL;
    ZeroMem (&gOutKey, sizeof (gOutKey));

    DisplayProgressMsg (
        AMI_PROGRESS_BOX_INIT,
        0,
        &gHandle,
        &gOutKey
        );

    Status = gBS->CreateEvent (
                EVT_TIMER | EVT_NOTIFY_SIGNAL,
                TPL_CALLBACK,
                ProgressIncrease,
                NULL,
                &ProgressEvent
                );
    if (EFI_ERROR (Status)) {
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgAny);
        NtpSyncDone (&Private);
        DEBUG ((DEBUG_ERROR, "[NTP] Create progress update event failed!\n"));
        return;
    }

    Status = gBS->SetTimer (ProgressEvent, TimerPeriodic, MultU64x32 (80, TICKS_PER_MS));
    if (EFI_ERROR (Status)) {
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgAny);
        NtpSyncDone (&Private);
        DEBUG ((DEBUG_ERROR, "[NTP] SetTimer() for progress update failed!\n"));
        return;
    }

    //
    // Get local IP address.
    //
    Status = NtpConfigLocalAddr (NtpConfigVar, Private);
    if (EFI_ERROR (Status)) {
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgIpConfig);
        NtpSyncDone (&Private);
        return;
    }

    DEBUG ((DEBUG_INFO, "[NTP] SrcAddress:\n"));
    NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->AddrConfig.SrcAddress.Addr);

    DEBUG ((DEBUG_INFO, "[NTP] SubnetMask:\n"));
    NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->AddrConfig.SubnetMask.Addr);

    DEBUG ((DEBUG_INFO, "[NTP] GatewayAddress:\n"));
    NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->AddrConfig.Gateway.Addr);

    DEBUG ((DEBUG_INFO, "[NTP] DNS Address:\n"));
    for (Index = 0; Index < Private->DnsConfig.DnsServerListCount; Index++) {
        NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->DnsConfig.DnsServerList[Index].Addr);
    }

    //
    // Get server IP address.
    //
    Status = NtpConfigServerInfo (NtpConfigVar, Private);
    if (EFI_ERROR (Status)) {
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );

        if (Status == EFI_TIMEOUT) {
            DisplayErrorMsg (StrTokenDisplayErrorMsgNtpRetry);
        } else {
            DisplayErrorMsg (StrTokenDisplayErrorMsgNtpConfig);
        }

        NtpSyncDone (&Private);
        return;
    }

    DEBUG ((DEBUG_INFO, "[NTP] NTP Server Address:\n"));
    NTP_IPV4_ADDRESS_DISPLAY (DEBUG_INFO, Private->AddrConfig.DstAddress.Addr);

    Private->TimeoutValue = NtpConfigVar.Timeout;

    //
    // Create UDP IO.
    //
    Private->UdpIo = UdpIoCreateIo (
                        Private->ControllerHandle,
                        Private->ImageHandle,
                        NtpConfigUdpIo,
                        UDP_IO_UDP4_VERSION,
                        Private
                        );
    if (Private->UdpIo == NULL) {
        DEBUG ((DEBUG_ERROR, "[NTP] UdpIo created failed.\n"));
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgAny);
        NtpSyncDone (&Private);
        return;
    }

    //
    // Create time out event.
    //
    Status = gBS->CreateEvent (
                EVT_TIMER,
                TPL_NOTIFY,
                NULL,
                NULL,
                &Private->TimeoutEvent
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] TimeoutEvent created failed.\n"));
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgAny);
        NtpSyncDone (&Private);
        return;
    }

    //
    // Construct and wait for receiving packet.
    //
    Status = NtpReceiveResponsePacket (Private);
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Configure or receive response failed.\n"));
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgResponse);
        NtpSyncDone (&Private);
        return;
    }

    //
    // Configure and send packet.
    //
    DEBUG ((DEBUG_INFO, "[NTP] Sending....\n"));
    Status = NtpSendRequestPacket (Private);
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Configure or send request failed.\n"));
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
            AMI_PROGRESS_BOX_CLOSE,
            0,
            &gHandle,
            &gOutKey
            );
        DisplayErrorMsg (StrTokenDisplayErrorMsgRequest);
        NtpSyncDone (&Private);
        return;
    }

    //
    // Start counting the time out.
    //
    Status = gBS->SetTimer (
                Private->TimeoutEvent,
                TimerRelative,
                MultU64x32 (TICKS_PER_SECOND, Private->TimeoutValue)
                );
    if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "[NTP] Trigger timer event %r\n", Status));
        TerminateProgressEvent (&ProgressEvent);
        DisplayProgressMsg (
                    AMI_PROGRESS_BOX_CLOSE,
                    0,
                    &gHandle,
                    &gOutKey
                    );
        DisplayErrorMsg (StrTokenDisplayErrorMsgTimerEvent);
        NtpSyncDone (&Private);
        return;
    }

    DEBUG ((DEBUG_INFO, "[NTP] Waiting....\n"));

    Status = EFI_NOT_READY;
    do {
        TimeoutStatus = gBS->CheckEvent (Private->TimeoutEvent);

        DEBUG ((DEBUG_INFO, "[NTP] ...\n"));
        if (gCompleted) {
            Status = NtpTimeUpdate (Private, NtpConfigAdjustTimeVar);
            DEBUG ((DEBUG_INFO, "[NTP] NtpTimeUpdate %r\n", Status));
            break;
        }
    } while (TimeoutStatus == EFI_NOT_READY);

    TerminateProgressEvent (&ProgressEvent);

    DisplayProgressMsg (
        AMI_PROGRESS_BOX_UPDATE,
        100,
        &gHandle,
        &gOutKey
        );

    DisplayProgressMsg (
        AMI_PROGRESS_BOX_CLOSE,
        0,
        &gHandle,
        &gOutKey
        );

    NtpSyncDone (&Private);

    if (!EFI_ERROR (Status)) {
        DisplaySuccessMsg (TRUE);
    } else {
        DisplaySuccessMsg (FALSE);
    }

    DEBUG ((DEBUG_INFO, "[NTP] NtpSyncStart() End....\n"));
}

/**
    Retrieve the Ipv4 address and verify the Ipv4 address.

    @param[in]  HiiHandle        HII handle of formset.
    @param[in]  IpStringValue    The string token value for the string control data.

    @retval  EFI_SUCCESS    The operation completed successfully.
    @retval  Other          The operation failed.

**/
EFI_STATUS
EFIAPI
NtpVerifyIpAddressImpl (
    IN  EFI_HII_HANDLE    HiiHandle,
    IN  UINT16            IpStringValue
    )
{
    EFI_STATUS  Status;
    CHAR16      *IpString = NULL;

    IpString = HiiGetString (HiiHandle, IpStringValue, NULL);

    if (!NtpValidateIp (IpString)) {
        Status = EFI_INVALID_PARAMETER;
        DisplayErrorMsg (StrTokenDisplayErrorMsgInvalidIp);
    } else {
        Status = EFI_SUCCESS;
    }

    if (IpString != NULL) {
        FreePool (IpString);
        IpString = NULL;
    }

    return Status;
}

/**
    Initializes the NTP related setup option values.

    @param[in]  HiiHandle       Handle to HII database
    @param[in]  SetupVarGuid    The GUID of the variable to get configuration.
    @param[in]  InitStrToken    The string token to be initialized.

    @retval  None

**/
VOID
EFIAPI
InitNtpStringsImpl (
    IN  EFI_HII_HANDLE      HiiHandle,
    IN  EFI_GUID            *SetupVarGuid,
    IN  NTP_STRING_TOKEN    *InitStrTokenList
    )
{
    EFI_STATUS         Status;
    UINT32             VariableAttributes      = EFI_VARIABLE_BOOTSERVICE_ACCESS;
    NTP_CONFIG_SUPPORT NtpConfigSupportVar;
    UINTN              NtpConfigSupportVarSize = 0;
    NETWORK_STACK      NetworkStackSetupData;
    UINTN              VarSize                 = 0;
    EFI_STRING_ID      StringId                = 0;
    CHAR16             *String                 = NULL;

    gNtpHiiHandle = HiiHandle;

    ZeroMem (gStrTokenList, sizeof (gStrTokenList));
    CopyMem (gStrTokenList, InitStrTokenList, sizeof (gStrTokenList));

    NtpConfigSupportVarSize = sizeof (NTP_CONFIG_SUPPORT);
    Status = gRT->GetVariable (
                NTP_CONFIG_SUPPORT_VARIABLE_NAME,
                SetupVarGuid,
                &VariableAttributes,
                &NtpConfigSupportVarSize,
                &NtpConfigSupportVar
                );
    if (Status != EFI_SUCCESS) {
        return;
    }

    NtpConfigSupportVar.NsEnable = TRUE;

    VarSize = sizeof (NETWORK_STACK);
    Status = gRT->GetVariable (
                L"NetworkStackVar",
                &gEfiNetworkStackSetupGuid,
                NULL,
                &VarSize,
                &NetworkStackSetupData
                );

    if (Status == EFI_SUCCESS) {
        if (NetworkStackSetupData.Enable == FALSE)
            NtpConfigSupportVar.NsEnable = FALSE;
    }

    String = GetTokenString (StrTokenConfigServerHostNameDefault, &StringId);
    if (String != NULL) {
        HiiSetString (HiiHandle, StringId, NTP_DEFAULT_SERVER_HOSTNAME, NULL);
        FreePool (String);
        String = NULL;
    }

    gRT->SetVariable (
        NTP_CONFIG_SUPPORT_VARIABLE_NAME,
        SetupVarGuid,
        VariableAttributes,
        NtpConfigSupportVarSize,
        &NtpConfigSupportVar
        );
}
