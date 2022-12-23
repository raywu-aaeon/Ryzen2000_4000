//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
/** @file
  Define

**/

#ifndef  _AmdPlatformGOPPolicy_H   //To Avoid this header get compiled twice
#define  _AmdPlatformGOPPolicy_H

#include "Token.h"

#if defined (AMD_GOP_PLATFORMTODRIVER_SUPPORT) && (AMD_GOP_PLATFORMTODRIVER_SUPPORT)
#include <Protocol/PlatformToDriverConfiguration.h>
#include <Protocol/AmiPlatformToDriverAgent.h>
#endif

#define ATI_VGA_VID   0x1002

#if defined (AMD_GOP_PLATFORMTODRIVER_SUPPORT) && (AMD_GOP_PLATFORMTODRIVER_SUPPORT)

extern EFI_GUID gEfiPlatformToAmdGopConfigurationGuid;

typedef enum 	{
   DisplayDeviceCRT = 0x80010100,
   DisplayDeviceLCD = 0x80010400,
   DisplayDeviceCRT2= 0x80010101,
   DisplayDeviceDFP1= 0x80010300,
   DisplayDeviceDFP2= 0x80010301,
   DisplayDeviceDFP3= 0x80010302,
   DisplayDeviceDFP4= 0x80010303,
   DisplayDeviceDFP5= 0x80010304,
   DisplayDeviceDFP6= 0x80010305,
   DisplayDeviceDFP7= 0x80010306,
};

typedef struct {
    UINT32 Revision;
    UINT32 Priority1ActiveDisplay;
    UINT32 Priority2ActiveDisplay;
    UINT32 Priority3ActiveDisplay;
    UINT32 Priority4ActiveDisplay;
    UINT32 Priority5ActiveDisplay;
    UINT32 Priority6ActiveDisplay;
    UINT32 Reserved1[6];
    UINT32 PlatformFeatureEnabled;
    UINT32 Reserved2[3];
} PLATFORM_TO_AMDGOP_CONFIGURATION;

typedef struct {
    UINT32 Revision;
    UINT32 GPU_Controlled_LCD_PWM_FREQ_InHz;
    UINT8 LCD_BootUp_BL_Level;
    UINT8 Reserved;
    UINT8 LCD_Min_BL_Level;
    UINT8 Reserved2;
    UINT32 LVDSMiscConfiguration;
    UINT8 LVDSPwrOnDIGONtoDE_in4Ms;
    UINT8 LVDSPwrOnDEtoVARY_BL_in4Ms;
    UINT8 LVDSPwrOnVARY_BLtoBLON_in4Ms;
    UINT8 LVDSPwrOffBLOFFtoVARY_BL_in4Ms;
    UINT8 LVDSPwrOffVARY_BLtoDE_in4Ms;
    UINT8 LVDSPwrOffDEtoDIGON_in4Ms;
    UINT8 LCDOffToOnDelay_in4Ms;
    UINT8 Reserved3[7];
    UINT16 LVDSSpreadSpectrumRateIn10Hz;
    UINT16 LVDSSpreadSpectrumPercentage;
    UINT32 Reserved4[12];
}PLATFORM_TO_AMDGOP_CONFIGURATION1;

EFI_STATUS ConfigurationSupported (
   IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,    
   IN EFI_HANDLE ControllerHandle,
   IN EFI_HANDLE ChildHandle OPTIONAL
);

EFI_STATUS ConfigurationQuery (
   IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,    
   IN  EFI_HANDLE ControllerHandle,
   IN  EFI_HANDLE ChildHandle OPTIONAL,
   IN  UINTN      *Instance,
   OUT EFI_GUID   **ParameterTypeGuid,
   OUT VOID       **ParameterBlock,
   OUT UINTN      *ParameterBlockSize
);

EFI_STATUS ConfigurationResponse (
   IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,    
   IN EFI_HANDLE                        ControllerHandle,
   IN EFI_HANDLE                        ChildHandle OPTIONAL,
   IN UINTN                             *Instance,
   IN EFI_GUID                          *ParameterTypeGuid,
   IN VOID                              *ParameterBlock,
   IN UINTN                             ParameterBlockSize,
   IN EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
);
#endif

typedef struct {
    UINT16          VendorId;
    UINT16          DeviceId;
    EFI_PHYSICAL_ADDRESS Address;         // pcir Address
} GNB_EFI_ROM_PCIR;


#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
