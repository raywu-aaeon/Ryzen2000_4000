//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#ifndef _AMI_RSD_CONFIG__H_
#define _AMI_RSD_CONFIG__H_

#include <Library/UefiLib.h>

#define ISCSI_MAX_MAC_STRING_LEN	96
#define ATTEMPT_NAME_SIZE         	12
#define ISCSI_CHAP_SECRET_STORAGE 	17
#define ISCSI_CHAP_NAME_STORAGE    	127
#define ISCSI_TARGET_URI_MAX_SIZE  	255
#define ISCSI_NAME_MAX_SIZE       	224

#pragma pack(1)
typedef struct _ISCSI_SESSION_CONFIG_NVDATA {
  UINT16            TargetPort;
  UINT8             Enabled;
  UINT8             IpMode;

  EFI_IP_ADDRESS    LocalIp;
  EFI_IPv4_ADDRESS  SubnetMask;
  EFI_IP_ADDRESS    Gateway;

  BOOLEAN           InitiatorInfoFromDhcp;
  BOOLEAN           TargetInfoFromDhcp;

  CHAR8             TargetName[ISCSI_NAME_MAX_SIZE];
  EFI_IP_ADDRESS    TargetIp;
  UINT8             PrefixLength;
  UINT8             BootLun[8];

  UINT16            ConnectTimeout; ///< timout value in milliseconds.
  UINT8             ConnectRetryCount;
  UINT8             IsId[6];

  BOOLEAN           RedirectFlag;
  UINT16            OriginalTargetPort;     // The port of proxy/virtual target.
  EFI_IP_ADDRESS    OriginalTargetIp;       // The address of proxy/virtual target.

  BOOLEAN           DnsMode;  // Flag indicate whether the Target address is expressed as URL format.
  CHAR8             TargetUrl[ISCSI_TARGET_URI_MAX_SIZE];

} ISCSI_SESSION_CONFIG_NVDATA;

typedef struct _ISCSI_CHAP_AUTH_CONFIG_NVDATA {
  UINT8 CHAPType;
  CHAR8 CHAPName[ISCSI_CHAP_NAME_STORAGE];
  CHAR8 CHAPSecret[ISCSI_CHAP_SECRET_STORAGE];
  CHAR8 ReverseCHAPName[ISCSI_CHAP_NAME_STORAGE];
  CHAR8 ReverseCHAPSecret[ISCSI_CHAP_SECRET_STORAGE];
} ISCSI_CHAP_AUTH_CONFIG_NVDATA;

typedef struct _AMI_ISCSI_ATTEMPT_CONFIG_NVDATA {
  LIST_ENTRY                       Link;
  UINT8                            NicIndex;
  UINT8                            AttemptConfigIndex;
  BOOLEAN                          DhcpSuccess;
  BOOLEAN                          ValidiBFTPath;
  BOOLEAN                          ValidPath;
  UINT8                            AutoConfigureMode;
  EFI_STRING_ID                    AttemptTitleToken;
  EFI_STRING_ID                    AttemptTitleHelpToken;
  CHAR8                            AttemptName[ATTEMPT_NAME_SIZE];
  CHAR8                            MacString[ISCSI_MAX_MAC_STRING_LEN];
  EFI_IP_ADDRESS                   PrimaryDns;
  EFI_IP_ADDRESS                   SecondaryDns;
  EFI_IP_ADDRESS                   DhcpServer;
  ISCSI_SESSION_CONFIG_NVDATA      SessionConfigData;
  UINT8                            AuthenticationType;
  union {
    ISCSI_CHAP_AUTH_CONFIG_NVDATA  CHAP;
  } AuthConfigData;
  BOOLEAN                          AutoConfigureSuccess;
  UINT8                            Actived;
  UINT8                            AttemptType;
  UINT8                            VlanEnable;
  UINT16                           VlanId;
  UINT8                            RouterAdvertisement;
  CHAR8                            IScsiInitiatorName[ISCSI_NAME_MAX_SIZE];
} AMI_ISCSI_ATTEMPT_CONFIG_NVDATA;
#pragma pack()

#endif
