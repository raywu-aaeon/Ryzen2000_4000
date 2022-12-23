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

//*************************************************************************
/** @file GnbPolicy.h
    Gnb setup data header file, define all the Gnb setup items
    and a structures in this file. 

**/
//*************************************************************************

#ifndef _AMI_GNB_SETUP_POLICY_H // To Avoid this header get compiled twice
#define _AMI_GNB_SETUP_POLICY_H

#include <Setup.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
typedef struct _GNB_CONFIG_DATA
{
    // GNB Setup header
    UINT32  GnbPolicyVersion;

    // Other items
#if EXTERNAL_VGA_CONTROL
    UINT8   PrimaryVideo;		// 0= IGD;1= PCIe
#endif
    UINT8   AmdGopPlatformToDriver;
    UINT32  AmdGopPlatformToDriverData1;
    UINT32  AmdGopPlatformToDriverData2;
    UINT32  AmdGopPlatformToDriverData3;
    UINT32  AmdGopPlatformToDriverData4;
    UINT32  AmdGopPlatformToDriverData5;
    UINT32  AmdGopPlatformToDriverData6;
    UINT8   AmdGopLcdBootUpBlLevel;
    UINT8   iGpuControl;
    UINT8   UmaFrameBufferSize;
    UINT8   PsppPolicy;
#if GNB_IOMMU_SUPPORT
    UINT8   IommuSupport;
#endif
    UINT8   GnbRemoteDisplaySupport;
    UINT8   GnbHdAudio;

    UINT8 GraphicsFeatures;
    UINT8 PxDynamicMode;
    UINT8 BrightnesLevel;
    UINT8 TvStandard;
    UINT8 PanelexPansion;

}GNB_CONFIG_DATA;
#pragma pack(pop)

typedef struct _GNB_CONFIG_DATA GNB_SETUP_DATA;

typedef VOID (GNB_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT GNB_SETUP_DATA   *GnbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

VOID GetGnbSetupData (
    IN VOID                 *Service,
    IN OUT GNB_SETUP_DATA   *GnbSetupData,
    IN BOOLEAN              Pei
);

#define GNB_SD_AUTO    0xFF  //Gnb Setup default Auto

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
