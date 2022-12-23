//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file AmdGopPlatformToDriver.c
  Implementation of EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL

**/

#include "Token.h"
#include <Uefi.h>
#include <GnbElinks.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Gnb.h>
#include <Protocol/PciIo.h>
#include <Library/AmdPlatformGOPPolicy.h>
#include <Library/GnbPolicy.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Pci.h>
#include <PciBus.h>

#if defined (AMD_GOP_PLATFORMTODRIVER_SUPPORT) && (AMD_GOP_PLATFORMTODRIVER_SUPPORT)

static PLATFORM_TO_AMDGOP_CONFIGURATION ConfigCommonDefault [] = {
  1,           // RevisionCommonConfig
  DisplayDeviceLCD,  // Prioriy1ActiveDisplay LCD
  DisplayDeviceDFP1,  // Prioriy2ActiveDisplay DFP1
  DisplayDeviceDFP2,  // Prioriy3ActiveDisplay DFP2
  DisplayDeviceDFP3,  // Prioriy4ActiveDisplay DFP3
  DisplayDeviceDFP4,  // Prioriy5ActiveDisplay DFP4
  DisplayDeviceCRT,  // Prioriy6ActiveDisplay CRT
  0,0,0,0,0,0, //UINT32 Reserved[6];
  0,           //UINT32 PlatformFeatureEnabled; 
  0,0,0        //UINT32 Reserved[3];
}; 

static PLATFORM_TO_AMDGOP_CONFIGURATION ConfigCommonCrtLcdFull [] = {
  1,           // RevisionCommonConfig
  0x80010100,  // Prioriy1ActiveDisplay CRT
  0x80010400,  // Prioriy2ActiveDisplay LCD
  0x80010300,  // Prioriy3ActiveDisplay DFP1
  0x80010301,  // Prioriy4ActiveDisplay DFP2
  0x80010302,  // Prioriy5ActiveDisplay DFP3
  0x80010303,  // Prioriy6ActiveDisplay DFP4
  0,0,0,0,0,0, //UINT32 Reserved[6];
  0,           //UINT32 PlatformFeatureEnabled; 
  0,0,0        //UINT32 Reserved[3];
}; 

UINT32 GopDeviceTable[10]={DisplayDeviceCRT
                  ,DisplayDeviceLCD
                  ,DisplayDeviceCRT2
                  ,DisplayDeviceDFP1
                  ,DisplayDeviceDFP2
                  ,DisplayDeviceDFP3
                  ,DisplayDeviceDFP4
                  ,DisplayDeviceDFP5
                  ,DisplayDeviceDFP6
                  ,DisplayDeviceDFP7};  

static PLATFORM_TO_AMDGOP_CONFIGURATION1 ConfigCommonCrtLcdFull1 [] = {
    2,//UINT32 Revision;
    0,//UINT32 GPU_Controlled_LCD_PWM_FREQ_InHz;
    0x80,//UINT8 LCD_BootUp_BL_Level;
    0,//UINT8 Reserved;
    0,//UINT8 LCD_Min_BL_Level;
    0,//UINT8 Reserved;
    0,//UINT32 LVDSMiscConfiguration;
    0,//UINT8 LVDSPwrOnDIGONtoDE_in4Ms;
    0,//UINT8 LVDSPwrOnDEtoVARY_BL_in4Ms;
    0,//UINT8 LVDSPwrOnVARY_BLtoBLON_in4Ms;
    0,//UINT8 LVDSPwrOffBLOFFtoVARY_BL_in4Ms;
    0,//UINT8 LVDSPwrOffVARY_BLtoDE_in4Ms;
    0,//UINT8 LVDSPwrOffDEtoDIGON_in4Ms;
    0,//UINT8 LCDOffToOnDelay_in4Ms;
    0,0,0,0,0,0,0,//UINT8 Reserved1[7];
    0,//UINT16 LVDSSpreadSpectrumRateIn10Hz;
    0,//UINT16 LVDSSpreadSpectrumPercentage;
    0,0,0,0,0,0,0,0,0,0,0,0 //UINT32 Reserved1[12];
}; 

AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL AmiPlatformToDriverAgentProtocol = {
        ConfigurationSupported,
        ConfigurationQuery,
        ConfigurationResponse
};


/**
  Find AMD IGD device.

  This function finds appropriate AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL
  instance, based on passed parameters
  
  @param  ControllerHandle  Handle of the controller for which to find the agent
  @param  ChildHandle       Handle of the child of the controller for which to find the agent

  @retval EFI_SUCCESS       AMD IGD is found
  @retval EFI_NOT_FOUND     No appropriate agent for this controller

**/

EFI_STATUS
ConfigurationSupported(
    IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,
    IN EFI_HANDLE                            ControllerHandle,
    IN EFI_HANDLE                            ChildHandle OPTIONAL)
{

    EFI_STATUS                  Status;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    PCI_TYPE00                  PciConfig;
    //porting here.

    // Get the protocol on this handle
    Status = gBS->HandleProtocol(ControllerHandle, &gEfiPciIoProtocolGuid, &PciIo);
    if (!EFI_ERROR(Status)) {
        // Read Vendor & Device ID.
        Status = PciIo->Pci.Read ( PciIo,
                                EfiPciIoWidthUint8,
                                0,
                                sizeof (PCI_TYPE00),
                                &PciConfig
                                );
        if (!EFI_ERROR(Status)) {
            // Check VGA device.
            if (IS_CLASS1 (&PciConfig, PCI_CLASS_DISPLAY) || IS_CLASS2 (&PciConfig, PCI_CLASS_OLD,  PCI_CLASS_OLD_VGA)) {
                PCI_DEV_INFO    *Dev;
                Dev = (PCI_DEV_INFO*)PciIo;
                if((Dev->ParentBrg->Address.Addr.Bus == 0)
                        && (Dev->ParentBrg->Address.Addr.Device == 8)
                        && (Dev->ParentBrg->Address.Addr.Function == 1)
                        && (Dev->Address.Addr.Device == 0)
                        && (Dev->Address.Addr.Function == 0)){
                    
                        
                        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Gnb:AmdPlatformToDriverAgentProtocol(ConfigurationQuery) .\n"));            
                        return EFI_SUCCESS;                    
                }
            }
        }// end of status
    }
    return EFI_UNSUPPORTED;
}

/**
  AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL Query member function implementation

  This function allow the UEFI driver to query the platform for configuration needed
  to complete driver's Start() operation
  
  @param This                 A pointer to the AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL instance.
  
  @param ControllerHandle     The handle the platform will return
                              configuration information about.
  
  @param ChildHandle          The handle of the child controller to
                              return information on. This is an optional
                              parameter that may be NULL. It will be
                              NULL for device drivers and for bus
                              drivers that attempt to get options for
                              the bus controller. It will not be NULL
                              for a bus driver that attempts to get
                              options for one of its child controllers.
  
  
  @param Instance             Pointer to the Instance value. Zero means
                              return the first query data. The caller should
                              increment this value by one each time to retrieve
                              successive data.

  @param ParameterTypeGuid    An EFI_GUID that defines the contents
                              of ParameterBlock. UEFI drivers must
                              use the ParameterTypeGuid to determine
                              how to parse the ParameterBlock. The caller
                              should not attempt to free ParameterTypeGuid.

  @param ParameterBlock       The platform returns a pointer to the
                              ParameterBlock structure which
                              contains details about the
                              configuration parameters specific to
                              the ParameterTypeGuid. This structure
                              is defined based on the protocol and
                              may be different for different
                              protocols. UEFI driver decodes this
                              structure and its contents based on
                              ParameterTypeGuid. ParameterBlock is
                              allocated by the platform and the
                              platform is responsible for freeing
                              the ParameterBlock after Result is
                              called.

  @param ParameterBlockSize   The platform returns the size of
                              the ParameterBlock in bytes.


  @retval EFI_SUCCESS           The platform return parameter
                                information for ControllerHandle.

  @retval EFI_NOT_FOUND         No more unread Instance exists.

  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.

  @retval EFI_INVALID_PARAMETER Instance is NULL.

  @retval EFI_DEVICE_ERROR      A device error occurred while
                                attempting to return parameter block
                                information for the controller
                                specified by ControllerHandle and
                                ChildHandle.

  @retval EFI_OUT_RESOURCES     There are not enough resources
                                available to set the configuration
                                options for the controller specified
                                by ControllerHandle and ChildHandle.

**/

EFI_STATUS ConfigurationQuery (
    IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,
    IN  EFI_HANDLE ControllerHandle,
    IN  EFI_HANDLE ChildHandle OPTIONAL,
    IN  UINTN      *Instance,
    OUT EFI_GUID   **ParameterTypeGuid,
    OUT VOID       **ParameterBlock,
    OUT UINTN      *ParameterBlockSize
){
    UINT8       CheckData[10] ={0,0,0,0,0,0,0,0,0,0};    //CRT~DFP7
    UINT8       i,j;
    UINT8       Counter=0;
    GNB_SETUP_DATA  GnbSetupData;     

    if(ControllerHandle == NULL || Instance == NULL)
        return EFI_INVALID_PARAMETER;
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Gnb:AmdPlatformToDriverAgentProtocol(ConfigurationQuery) .\n"));
    //porting here.
    GetGnbSetupData(gRT, &GnbSetupData, FALSE);
    *ParameterTypeGuid = &gEfiPlatformToAmdGopConfigurationGuid;

    if(*Instance){ // For LCD
        *ParameterBlockSize = sizeof(PLATFORM_TO_AMDGOP_CONFIGURATION1);
        ConfigCommonCrtLcdFull1->LCD_BootUp_BL_Level = GnbSetupData.AmdGopLcdBootUpBlLevel;
        *ParameterBlock = (VOID *)(&ConfigCommonCrtLcdFull1);

    } else
    if (*Instance == 0){ // For priority

        *ParameterBlockSize = sizeof(PLATFORM_TO_AMDGOP_CONFIGURATION);

        if (GnbSetupData.AmdGopPlatformToDriver == 0 ){  // default 
            *ParameterBlock = (VOID *)(&ConfigCommonDefault);
        }else
        if ( GnbSetupData.AmdGopPlatformToDriver == 1 ){ // manually

            ConfigCommonCrtLcdFull->Priority1ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData1];
            ConfigCommonCrtLcdFull->Priority2ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData2];
            ConfigCommonCrtLcdFull->Priority3ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData3];
            ConfigCommonCrtLcdFull->Priority4ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData4];
            ConfigCommonCrtLcdFull->Priority5ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData5];
            ConfigCommonCrtLcdFull->Priority6ActiveDisplay = GopDeviceTable[GnbSetupData.AmdGopPlatformToDriverData6];

            // Count the Gop priority device , avoid assign the same device twice.
            // It could happen abnormal behavior if use the same GOP priority.
            // Try to find it and set it to zero.
            CheckData[GnbSetupData.AmdGopPlatformToDriverData1]++;
            CheckData[GnbSetupData.AmdGopPlatformToDriverData2]++;
            CheckData[GnbSetupData.AmdGopPlatformToDriverData3]++;
            CheckData[GnbSetupData.AmdGopPlatformToDriverData4]++;
            CheckData[GnbSetupData.AmdGopPlatformToDriverData5]++;
            CheckData[GnbSetupData.AmdGopPlatformToDriverData6]++;

            for (i=0; i<sizeof(CheckData); i++){
                Counter=0;
                if (CheckData[i] >= 2){  // We found secondary the same GOP priority.
                    for(j=1;j<=6;j++){
                        // Try to find secondary GOP priority device
                         if ( *(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+j*4) ==  GopDeviceTable[i])
                        // Found first GOP priority.
                         Counter++;
                         if (Counter >= 2){         
                            if (*(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+j*4) == GopDeviceTable[i])
                            // Found secondary GOP priority and clean it.
                             *(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+j*4)=0; 

                         } // end of counter==2                          
                    } // end of j
                } // end of checkdata
            } // end of i

            // Move zero to last position
            for(i=2;i<=5;i++){
                if (*(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+i*4) == 0 ){
                for(j=i;j<=5;j++)
                    *(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+j*4) =  *(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+(j+1)*4);  
                *(UINT32 *)((EFI_PHYSICAL_ADDRESS)(&ConfigCommonCrtLcdFull)+6*4)=0;             
                }
            }


        *ParameterBlock = (VOID *)(&ConfigCommonCrtLcdFull);

      } // end of Instance=0


    }     

    return EFI_SUCCESS;
}

/**
  AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL Response member function implementation

  This function tell the platform what actions where taken by the driver after processing
  the data returned from Query
  
  @param This                A pointer to the AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL instance.

  @param ControllerHandle    The handle the driver is returning
                             configuration information about.

  @param ChildHandle         The handle of the child controller to
                             return information on. This is an optional
                             parameter that may be NULL. It will be
                             NULL for device drivers, and for bus
                             drivers that attempt to get options for
                             the bus controller. It will not be NULL
                             for a bus driver that attempts to get
                             options for one of its child controllers.
                             Instance Instance data returned from
                             Query().

  @param Instance            Instance data passed to Query().

  @param ParameterTypeGuid   ParameterTypeGuid returned from Query.

  @param ParameterBlock      ParameterBlock returned from Query.

  @param ParameterBlockSize  The ParameterBlock size returned from Query.

  @param ConfigurationAction The driver tells the platform what
                             action is required for ParameterBlock to
                             take effect.
  
  
  @retval EFI_SUCCESS           The platform return parameter information
                                for ControllerHandle.
  
  @retval EFI_NOT_FOUND         Instance was not found.
  
  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.
 
  @retval EFI_INVALID_PARAMETER Instance is zero.
  
**/

EFI_STATUS ConfigurationResponse (
    IN AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *This,        
    IN EFI_HANDLE                        ControllerHandle,
    IN EFI_HANDLE                        ChildHandle OPTIONAL,
    IN UINTN                             *Instance,
    IN EFI_GUID                          *ParameterTypeGuid,
    IN VOID                              *ParameterBlock,
    IN UINTN                             ParameterBlockSize,
    IN EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
){
    //porting here.
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Gnb:AmdPlatformToDriverAgentProtocol(ConfigurationResponse).\n"));
    return EFI_SUCCESS;
}

#endif //defined (AMD_GOP_PLATFORMTODRIVER_SUPPORT) && (AMD_GOP_PLATFORMTODRIVER_SUPPORT)


/**
  The user Entry Point for module AmdGopPlatformToDriver. The user code starts with this function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS EFIAPI AmdGopPlatformToDriverEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status = EFI_SUCCESS;
#if defined (AMD_GOP_PLATFORMTODRIVER_SUPPORT) && (AMD_GOP_PLATFORMTODRIVER_SUPPORT)
    EFI_HANDLE Handle = NULL;

    Status = gBS->InstallMultipleProtocolInterfaces (
                                &Handle,
                                &gAmiPlatformToDriverAgentProtocolGuid, 
                                &AmiPlatformToDriverAgentProtocol,
                                NULL);

#endif
    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
