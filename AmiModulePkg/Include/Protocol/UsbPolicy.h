//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbPolicy.h
    Protocol used for USB policy definitions

**/

#ifndef _USB_POLICY_H_
#define _USB_POLICY_H_

#define EFI_USB_POLICY_PROTOCOL_GUID \
  { 0x5859cb76, 0x6bef, 0x468a, { 0xbe, 0x2d, 0xb3, 0xdd, 0x1a, 0x27, 0xf0, 0x12 }}
#define USB_TIMING_POLICY_PROTOCOL_GUID \
  { 0x89e3c1dc, 0xb5e3, 0x4d34, { 0xae, 0xad, 0xdd, 0x7e, 0xb2, 0x82, 0x8c, 0x18 }}

#ifndef VFRCOMPILE
typedef enum {
        USBMASS_EMU_AUTO,
        USBMASS_EMU_FDD,
        USBMASS_EMU_FORCED_FDD,
        USBMASS_EMU_HDD,
        USBMASS_EMU_CD
} USBMASS_EMU_TYPE;
#endif

#define USB_DEVPLCY_STATUS_PRESENT      1

#ifndef TYPEDEF_USB_SUPPORT_SETUP
#define TYPEDEF_USB_SUPPORT_SETUP
typedef struct {
        UINT8   UsbMainSupport;
        UINT8   UsbLegacySupport;
        UINT8   UsbEhciHandoff;
        UINT8   UsbOhciHandoff;
        UINT8   UsbHotplugFddSupport;
        UINT8   UsbHotplugHddSupport;
        UINT8   UsbHotplugCdromSupport;
        UINT8   UsbEmul6064;
        UINT8   UsbMassResetDelay;
        UINT8   UsbControlTimeOut;  //(EIP30079+)
        UINT8   UsbEmu1;
        UINT8   UsbEmu2;
        UINT8   UsbEmu3;
        UINT8   UsbEmu4;
        UINT8   UsbEmu5;
        UINT8   UsbEmu6;
        UINT8   UsbEmu7;
        UINT8   UsbEmu8;
        UINT8   UsbEmu9;
        UINT8   UsbEmu10;
        UINT8   UsbEmu11;
        UINT8   UsbEmu12;
        UINT8   UsbEmu13;
        UINT8   UsbEmu14;
        UINT8   UsbEmu15;
        UINT8   UsbEmu16;
        UINT8   UsbEmu17;
        UINT8   UsbEmu18;
        UINT8   UsbEmu19;
        UINT8   UsbEmu20;
        UINT8	UsbEmu21;
        UINT8	UsbEmu22;
        UINT8	UsbEmu23;
        UINT8	UsbEmu24;
        UINT8	UsbEmu25;
        UINT8	UsbEmu26;
        UINT8	UsbEmu27;
        UINT8	UsbEmu28;
        UINT8	UsbEmu29;
        UINT8	UsbEmu30;
        UINT8	UsbEmu31;
        UINT8	UsbEmu32;
        UINT8   UsbXhciSupport;
        UINT8   UsbXhciHandoff;
        UINT8   PowerGoodDeviceDelay;
        UINT8   PowerGoodDeviceNumDelay;
        UINT8   UsbHiSpeedSupport;
        UINT8   UsbMassDriverSupport;           //(EIP99882+)
        UINT8   UsbS5WakeupSupport;
} USB_SUPPORT_SETUP;
#endif

#ifndef TYPEDEF_USB_MASS_DEV_VALID
#define TYPEDEF_USB_MASS_DEV_VALID
typedef struct{
        UINT8   UsbEmu1Valid;
        UINT8   UsbEmu2Valid;
        UINT8   UsbEmu3Valid;
        UINT8   UsbEmu4Valid;
        UINT8   UsbEmu5Valid;
        UINT8   UsbEmu6Valid;
        UINT8   UsbEmu7Valid;
        UINT8   UsbEmu8Valid;
        UINT8   UsbEmu9Valid;
        UINT8   UsbEmu10Valid;
        UINT8   UsbEmu11Valid;
        UINT8   UsbEmu12Valid;
        UINT8   UsbEmu13Valid;
        UINT8   UsbEmu14Valid;
        UINT8   UsbEmu15Valid;
        UINT8   UsbEmu16Valid;
        UINT8   UsbEmu17Valid;
        UINT8   UsbEmu18Valid;
        UINT8   UsbEmu19Valid;
        UINT8   UsbEmu20Valid;
        UINT8	UsbEmu21Valid;
        UINT8	UsbEmu22Valid;
        UINT8	UsbEmu23Valid;
        UINT8	UsbEmu24Valid;
        UINT8	UsbEmu25Valid;
        UINT8	UsbEmu26Valid;
        UINT8	UsbEmu27Valid;
        UINT8	UsbEmu28Valid;
        UINT8	UsbEmu29Valid;
        UINT8	UsbEmu30Valid;
        UINT8	UsbEmu31Valid;
        UINT8	UsbEmu32Valid;
} USB_MASS_DEV_VALID;
#endif

#define MAX_USB_MASS                            8
#define SETUP_DATA_HOTPLUG_ENABLED      1
#define SETUP_DATA_HOTPLUG_DISABLED     2
#define SETUP_DATA_HOTPLUG_AUTO         3
#define SETUP_DATA_RESETDELAY_20S       1

#define USB_HC_UHCI                 0x10
#define USB_HC_OHCI                 0x20
#define USB_HC_EHCI                 0x30
#define USB_HC_XHCI                 0x40

#ifndef VFRCOMPILE
typedef struct _USB_POLICY_PROTOCOL EFI_USB_POLICY_PROTOCOL;

typedef struct {
  UINT8                         Type;
  EFI_DEVICE_PATH_PROTOCOL      *Device;
  EFI_HANDLE                    HwSmiHandle;
} AMI_USB_HW_SMI_HC_CONTEXT;

typedef struct{
    UINT8                       HcCount;
    AMI_USB_HW_SMI_HC_CONTEXT   **HcContext;    
} AMI_USB_HW_SMI_HC_TABLE;


typedef struct{
    UINT16  Vid;
    UINT16  Did;
    UINT8   Config;
} USB_DEV_CONFIG_INFO;

typedef
EFI_STATUS
(EFIAPI *AMI_USB_DEV_CONFIG_INFO)(
    IN EFI_USB_POLICY_PROTOCOL    *This,
    IN USB_DEV_CONFIG_INFO        *DevConfigInfo
);

struct _USB_POLICY_PROTOCOL {
    USB_SUPPORT_SETUP           *UsbDevPlcy;
    AMI_USB_HW_SMI_HC_TABLE     AmiUsbHwSmiHcTable;
    AMI_USB_DEV_CONFIG_INFO     UsbDevConfigNumPolicy;
    BOOLEAN                     RegisterUsbSmiBeforeEndOfDxe;
};
#endif

#define EMULATION_FAKE_INTERFACE        1

#ifndef TYPEDEF_USB_MASS_DEV_NUM
#define TYPEDEF_USB_MASS_DEV_NUM
typedef struct {
        UINT8   UsbMassDevNum;
        UINT8   IsInteractionAllowed;
} USB_MASS_DEV_NUM;
#endif

#ifndef TYPEDEF_USB_CONTROLLER_NUM
#define TYPEDEF_USB_CONTROLLER_NUM
typedef struct {
    UINT8   UhciNum;
    UINT8   OhciNum;
    UINT8   EhciNum;
    UINT8   XhciNum;
} USB_CONTROLLER_NUM;
#endif

typedef struct {
    UINT16  Vid;
    UINT16  Did;
    UINT16  DelayTime;
} CONTROLLERS_INITIAL_DELAY_LIST;

#define MAX_USB_CONTROLLER_DELAY_LIST_COUNT       3

typedef struct {
    UINT16  UsbTimingPolicyRevision;
    UINT16  UsbTimingPolicyLength;
    UINT16  EhciPortPowerOnDelay;
    UINT16  EhciPortConnect;
    UINT16  EhciPortReset;
    UINT16  OhciHcResetDelay;
    UINT16  OhciPortEnable;
    UINT16  OhciHcReset;
    UINT16  UhciGlobalReset;
    UINT16  UhciPortEnable;
    UINT16  HubPortConnect;
    UINT16  HubPortEnable;
    UINT16  MassDeviceComeUp;
    UINT16  RmhPowerOnDelay;
    CONTROLLERS_INITIAL_DELAY_LIST ControllersDelayList[MAX_USB_CONTROLLER_DELAY_LIST_COUNT];
} USB_TIMING_POLICY;

extern  EFI_GUID gEfiUsbPolicyProtocolGuid;
extern  EFI_GUID gUsbTimingPolicyProtocolGuid;

#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
