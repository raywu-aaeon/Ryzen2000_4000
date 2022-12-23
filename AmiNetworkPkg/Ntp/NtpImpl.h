//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**
    @file NtpImpl.h
    AMI NTP implementation.
**/
#ifndef __NTP_IMPL_H__
#define __NTP_IMPL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Library/HiiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/AMIPostMgr.h>
#include <Library/UefiLib.h>
#include <Protocol/Cpu.h>
#include <Uefi.h>
#include <Library/NetLib.h>
#include <NetworkStackSetup.h>
#include <Protocol/Dns4.h>
#include <Library/UdpIoLib.h>

#define NTP_CONFIG_SUPPORT_VARIABLE_NAME        L"NtpConfigSupport"
#define NTP_CONFIGURATION_VARIABLE_NAME         L"NtpConfig"
#define NTP_CONFIG_ADJUST_TIME_VARIABLE_NAME    L"NtpConfigAdjustTime"

#define NTP_IPV4_ADDRESS_DISPLAY(ErrorLevel,Addr)                                 \
    {                                                                             \
        DEBUG ((ErrorLevel, "%d.%d.%d.%d\n", Addr[0], Addr[1], Addr[2], Addr[3]));\
    }

#define IsLeap(y)          (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))
#define SECSPERMIN         (60)
#define MINPERHOUR         (60)
#define SECSPERHOUR        (60 * 60)
#define SECSPERDAY         (24 * SECSPERHOUR)

//
// Usage for the Lvm fields
//  0----------1 2-------3-------4 5-----6------7  (bit)
//  |<--Leap-->| |<---Version--->| |<---Mode--->|  (field)
//
#define NTP_LVM_TO_LEAP(Lvm)       ((Lvm >> 6) & 0x3)
#define NTP_LVM_TO_VERSION(Lvm)    ((Lvm >> 3) & 0x7)
#define NTP_LVM_TO_MODE(Lvm)       ((Lvm & 0x7))
#define NTP_TO_LVM(Leap, Version, Mode)\
    (((Leap << 6) & 0xC0) | ((Version << 3) & 0x38) | (Mode & 0x7))

//
// Define the usages to follow spec.
//
#define NTP_CLIENT_MODE     3
#define NTP_VERSION         4
#define NTP_LEAP_UNKNOWN    3
#define NTP_SERVER_PORT     123

typedef enum {
    StrTokenConfigServerHostNameDefault,
    StrTokenDisplayTitleError,
    StrTokenDisplayTitleSync,
    StrTokenDisplayMsgSyncWait,
    StrTokenDisplayTitleTimeUpdate,
    StrTokenDisplayMsgTimeUpdateFailed,
    StrTokenDisplayTitleConfigFailed,
    StrTokenDisplayMsgConfigCheck,
    StrTokenDisplayMsgConfigRetry,
    StrTokenDisplayTitleConfigChanged,
    StrTokenDisplayMsgConfigSave,
    StrTokenDisplayTitleSyncConfirm,
    StrTokenDisplayMsgSyncConfirm,
    StrTokenDisplayErrorMsgIpConfig,
    StrTokenDisplayErrorMsgNtpRetry,
    StrTokenDisplayErrorMsgNtpConfig,
    StrTokenDisplayErrorMsgAny,
    StrTokenDisplayErrorMsgResponse,
    StrTokenDisplayErrorMsgRequest,
    StrTokenDisplayErrorMsgTimerEvent,
    StrTokenDisplayErrorMsgInvalidIp,
    StrTokenIndexEnd
} NTP_STRING_TOKEN_INDEX;

typedef struct _NTP_STRING_TOKEN {
    NTP_STRING_TOKEN_INDEX    Index;
    UINT16                    Value;
} NTP_STRING_TOKEN;

typedef struct _NTP_UINT64 {
    UINT32    Hi;
    UINT32    Lo;
} NTP_UINT64;

typedef struct _NTP_PACKET {
    UINT8         Lvm;      // LI:2 (bits), VN:3 (bits), Mode:3 (bits)
    UINT8         Stratum;
    INT8          Poll;
    INT8          Precision;
    UINT32        RootDelay;
    UINT32        RootDispresion;
    UINT32        ReferenceId;
    NTP_UINT64    ReferenceTimeStamp;
    NTP_UINT64    OriginateTimeStamp;
    NTP_UINT64    ReceiveTimeStamp;
    NTP_UINT64    TransmitTimeStamp;
    // Reserve extension fields here
} NTP_PACKET;

typedef struct _NTP_UDP_UDP_ADDRESS_CONFIG {
    EFI_IPv4_ADDRESS    DstAddress;
    EFI_IPv4_ADDRESS    SrcAddress;
    EFI_IPv4_ADDRESS    Gateway;
    EFI_IPv4_ADDRESS    SubnetMask;
    UINT16              DestPort;
} NTP_UDP_ADDRESS_CONFIG;

typedef struct _DNS_SERVER_CONFIG {
    UINTN               DnsServerListCount;
    EFI_IPv4_ADDRESS    *DnsServerList;
} DNS_SERVER_CONFIG;

typedef struct _NTP_PRIVATE_DATA {
    EFI_HANDLE                ControllerHandle;
    EFI_HANDLE                ImageHandle;
    UDP_IO                    *UdpIo;
    NTP_UDP_ADDRESS_CONFIG    AddrConfig;
    DNS_SERVER_CONFIG         DnsConfig;
    NTP_PACKET                NtpPacket;
    UINT8                     TimeoutValue; // Time out in second.
    EFI_EVENT                 TimeoutEvent;
} NTP_PRIVATE_DATA;

VOID
EFIAPI
NtpSyncStartImpl (
    IN  EFI_GUID      *SetupVarGuid,
    IN  EFI_HANDLE    DriverHandle
    );

EFI_STATUS
EFIAPI
NtpVerifyIpAddressImpl (
    IN  EFI_HII_HANDLE    HiiHandle,
    IN  UINT16            IpStringValue
    );

VOID
EFIAPI
InitNtpStringsImpl (
    IN  EFI_HII_HANDLE      HiiHandle,
    IN  EFI_GUID            *SetupVarGuid,
    IN  NTP_STRING_TOKEN    *InitStrTokenList
    );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif // __NTP_IMPL_H__
