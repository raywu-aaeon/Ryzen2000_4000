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

/** @file GetSetupData.c
    Custom North Bridge setup data behavior implementation

**/


#include <Setup.h>
#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/GnbPolicy.h>
#include <GnbElinks.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
extern GNB_OEM_SETUP_CALLBACK GNB_OEM_SETUP_CALLBACK_LIST EndOfList;
GNB_OEM_SETUP_CALLBACK* GnbOemSetupCallbackList[] = { GNB_OEM_SETUP_CALLBACK_LIST NULL };


#define GNB_SD_AUTO    0xFF  //Gnb Setup default Auto
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

// GUID Definition(s)

static EFI_GUID gSetupGuid = SETUP_GUID;

// Protocol/Ppi Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for OEM/custom setup.

    @param Services Pointer to PeiServices or RuntimeServices
        structure  
    @param GnbSetupData Pointer to custom setup data to return
    @param SetupData Pointer to system setup data.
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/

VOID GnbOemSetupCallbacks (
    IN VOID                 *Services,
    IN OUT GNB_SETUP_DATA    *GnbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
  )
{
  UINT32                  Index;

  for (Index = 0; GnbOemSetupCallbackList[Index] != NULL; Index++) {
    GnbOemSetupCallbackList[Index](Services, GnbSetupData, SetupData, Pei);
  }
}

/**
    This function returns custom setup data from system SetupData
    variable 

    @param Services Pointer to PeiServices or RuntimeServices structure  
    @param GnbSetupData Pointer to custom setup data to return
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID

    @note  PORTING REQUIRED
**/
VOID GetGnbSetupData (
    IN VOID                 *Services,
    IN OUT GNB_SETUP_DATA    *GnbSetupData,
    IN BOOLEAN              Pei
)
{
    EFI_STATUS                      Status;
    SETUP_DATA                      SetupData;
    EFI_PEI_SERVICES                **PeiServices;
    EFI_RUNTIME_SERVICES            *RunServices;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
    UINTN                           VariableSize = sizeof(SETUP_DATA);


    if (Pei) {
        PeiServices = (EFI_PEI_SERVICES **)Services;
        Status = (*PeiServices)->LocatePpi( PeiServices, \
                                            &gEfiPeiReadOnlyVariable2PpiGuid, \
                                            0, \
                                            NULL, \
                                            &ReadOnlyVariable );

        if (!EFI_ERROR(Status)) {
            Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                    L"Setup", \
                                                    &gSetupGuid, \
                                                    NULL, \
                                                    &VariableSize, \
                                                    &SetupData );
        }
    } else {
        RunServices = (EFI_RUNTIME_SERVICES *)Services;
        Status = RunServices->GetVariable( L"Setup", \
                                           &gSetupGuid, \
                                           NULL, \
                                           &VariableSize, \
                                           &SetupData );
    }

    GnbSetupData->GnbPolicyVersion = 0x010; // This value must be updated if 
                                          // the structure of GNB_SETUP_DATA 
                                          // is changed.
                                          // Porting required.

    if (EFI_ERROR(Status)) {
        // Porting Start
        // Update NB_SETUP_DATA according to the default values.

#if EXTERNAL_VGA_CONTROL
    	GnbSetupData->PrimaryVideo = 0;
#endif

        GnbSetupData->GraphicsFeatures = 0;
        GnbSetupData->PxDynamicMode = 0;
        GnbSetupData->BrightnesLevel = 1;
        GnbSetupData->TvStandard = 0;
        GnbSetupData->PanelexPansion = 0;

        GnbSetupData->iGpuControl = 0;
    	GnbSetupData->UmaFrameBufferSize = GNB_SD_AUTO; //Auto
    	GnbSetupData->PsppPolicy = GNB_SD_AUTO; //Auto
#if GNB_IOMMU_SUPPORT
    	GnbSetupData->IommuSupport = 0;
#endif
        GnbSetupData->GnbRemoteDisplaySupport = 1;
        GnbSetupData->GnbHdAudio = 1;
#if AMD_GOP_PLATFORMTODRIVER_SUPPORT
        GnbSetupData->AmdGopPlatformToDriver = 0;
        GnbSetupData->AmdGopPlatformToDriverData1 = 0;
        GnbSetupData->AmdGopPlatformToDriverData2 = 1;
        GnbSetupData->AmdGopPlatformToDriverData3 = 3;
        GnbSetupData->AmdGopPlatformToDriverData4 = 4;
        GnbSetupData->AmdGopPlatformToDriverData5 = 5;
        GnbSetupData->AmdGopPlatformToDriverData6 = 7;
        GnbSetupData->AmdGopLcdBootUpBlLevel = 0;
#endif
        // Porting End
        GnbOemSetupCallbacks( Services, GnbSetupData, NULL, Pei );
    } else {
        // Porting Start
        // Update NB_SETUP_DATA according to the setup datas.

#if EXTERNAL_VGA_CONTROL
#if (defined(AmdCpmDisplayFeature_SUPPORT) && (AmdCpmDisplayFeature_SUPPORT != 0))
        if (SetupData.PrimaryVideoAdaptor)
            GnbSetupData->PrimaryVideo = SetupData.PrimaryVideoAdaptor - 1;
        else
            GnbSetupData->PrimaryVideo = SetupData.PrimaryVideoAdaptor;  //PrimaryVideoAdaptor-> Auto == PrimaryVideo->IGD 
#else
        GnbSetupData->PrimaryVideo = SetupData.PrimaryVideo;
#endif
#endif

        GnbSetupData->iGpuControl = SetupData.iGpuControl;
    	GnbSetupData->UmaFrameBufferSize = SetupData.UmaFrameBufferSize;
    	GnbSetupData->PsppPolicy = SetupData.PsppPolicy;
#if GNB_IOMMU_SUPPORT
    	GnbSetupData->IommuSupport = SetupData.IommuSupport;
#endif
        GnbSetupData->GnbRemoteDisplaySupport = SetupData.GnbRemoteDisplaySupport;
        GnbSetupData->GnbHdAudio = SetupData.GnbHdAudio;
#if AMD_GOP_PLATFORMTODRIVER_SUPPORT
        GnbSetupData->AmdGopPlatformToDriver = SetupData.AmdGopPlatformToDriver;
        GnbSetupData->AmdGopPlatformToDriverData1 = SetupData.AmdGopPlatformToDriverData1;
        GnbSetupData->AmdGopPlatformToDriverData2 = SetupData.AmdGopPlatformToDriverData2;
        GnbSetupData->AmdGopPlatformToDriverData3 = SetupData.AmdGopPlatformToDriverData3;
        GnbSetupData->AmdGopPlatformToDriverData4 = SetupData.AmdGopPlatformToDriverData4;
        GnbSetupData->AmdGopPlatformToDriverData5 = SetupData.AmdGopPlatformToDriverData5;
        GnbSetupData->AmdGopPlatformToDriverData6 = SetupData.AmdGopPlatformToDriverData6;
        GnbSetupData->AmdGopLcdBootUpBlLevel      = SetupData.AmdGopLcdBootUpBlLevel;
#endif
        // Porting End
        GnbOemSetupCallbacks( Services, GnbSetupData, &SetupData, Pei );
    }
}

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
