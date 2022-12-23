//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/**
    @file Ntp.h
    AMI NTP Configuration.
**/

#ifndef __NTP__H__
#define __NTP__H__
#ifdef __cplusplus
extern "C" {
#endif

#define NTP_SERVER_OPT_DEFAULT         0
#define NTP_SERVER_OPT_MANUAL          1

#define NTP_CONFIG_LOCAL_IP_STATIC     0   // Ip4Config2PolicyStatic
#define NTP_CONFIG_LOCAL_IP_DYNAMIC    1   // Ip4Config2PolicyDhcp

// Define the time zone offset Start
#define TIME_ZONE_MINUS_12             0
#define TIME_ZONE_MINUS_11             1
#define TIME_ZONE_MINUS_10             2
#define TIME_ZONE_MINUS_9              3
#define TIME_ZONE_MINUS_8              4
#define TIME_ZONE_MINUS_7              5
#define TIME_ZONE_MINUS_6              6
#define TIME_ZONE_MINUS_5              7
#define TIME_ZONE_MINUS_4_30           8
#define TIME_ZONE_MINUS_4              9
#define TIME_ZONE_MINUS_3_30          10
#define TIME_ZONE_MINUS_3             11
#define TIME_ZONE_MINUS_2             12
#define TIME_ZONE_MINUS_1             13
#define TIME_ZONE_0                   14
#define TIME_ZONE_PLUS_1              15
#define TIME_ZONE_PLUS_2              16
#define TIME_ZONE_PLUS_3              17
#define TIME_ZONE_PLUS_3_30           18
#define TIME_ZONE_PLUS_4              19
#define TIME_ZONE_PLUS_4_30           20
#define TIME_ZONE_PLUS_5              21
#define TIME_ZONE_PLUS_5_30           22
#define TIME_ZONE_PLUS_5_45           23
#define TIME_ZONE_PLUS_6              24
#define TIME_ZONE_PLUS_6_30           25
#define TIME_ZONE_PLUS_7              26
#define TIME_ZONE_PLUS_8              27
#define TIME_ZONE_PLUS_9              28
#define TIME_ZONE_PLUS_9_30           29
#define TIME_ZONE_PLUS_10             30
#define TIME_ZONE_PLUS_11             31
#define TIME_ZONE_PLUS_12             32
#define TIME_ZONE_PLUS_13             33
#define TIME_ZONE_PLUS_14             34
// Define the time zone offset End

#define IP4_STRING_SIZE               16
#define IP4_MINIMUM_SIZE               7
#define IP4_MAXIMUM_SIZE              15
#define MAX_STRING_NAME              255

#pragma pack(1)
typedef struct {
    UINT8    Enable;
    UINT8    NsEnable;
} NTP_CONFIG_SUPPORT;

typedef struct {
    UINT8     NtpServerOpt;
    UINT8     LocalAddressOpt;
    CHAR16    NtpServerName[MAX_STRING_NAME];
    CHAR16    LocalAddress[IP4_STRING_SIZE];
    CHAR16    SubnetMask[IP4_STRING_SIZE];
    CHAR16    GatewayAddress[IP4_STRING_SIZE];
    CHAR16    PrimaryDnsServer[IP4_STRING_SIZE];
    UINT8     Timeout;
} NTP_CONFIGURATION;

typedef struct {
    UINT8    TimeZoneOpt;
    UINT8    Daylight;
} NTP_CONFIG_ADJUST_TIME;
#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
