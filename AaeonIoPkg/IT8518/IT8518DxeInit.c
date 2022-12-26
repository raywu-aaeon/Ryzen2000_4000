//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <IT8518DxeInit.c>
//
// Description: 1. Port SIO DXE initial table and routine for GenericSio.c
//              2. Define SIO bootscriptable table
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <AmiGenericSio.h>
#include "IT8518DxeIoTable.h"
#include <Setup.h>
#include <Token.h>
#include "EcApiProtocol.c"

//-------------------------------------------------------------------------
// Procedure: IT8518_ClearDevResource
// Description:
// This function will Clear SIO resource
// Input:
// SIO_DEV2* dev
// Output:
// NONE
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID IT8518_ClearDevResource(
    IN  SIO_DEV2    *dev
)
{
    IoWrite8(IT8518_CONFIG_INDEX, IT8518_LDN_SEL_REGISTER);
    IoWrite8(IT8518_CONFIG_DATA, dev->DeviceInfo->Ldn);
    IoWrite8(IT8518_CONFIG_INDEX, IT8518_BASE1_HI_REGISTER);
    IoWrite8(IT8518_CONFIG_DATA, 0);
    IoWrite8(IT8518_CONFIG_INDEX, IT8518_BASE1_LO_REGISTER);
    IoWrite8(IT8518_CONFIG_DATA, 0);
    IoWrite8(IT8518_CONFIG_INDEX, IT8518_IRQ1_REGISTER);
    IoWrite8(IT8518_CONFIG_DATA, 0);
    return;
}
// ---------------------- External Function define ---------------------
#if defined(IT8518_BRAM_PRESENT) && (IT8518_BRAM_PRESENT == 1)

//->>CSKA_009_Elflo 20150903 
//void DynamicDioInit ()
//{
//	EFI_STATUS 	Status = EFI_SUCCESS;
//	EFI_GUID        SetupGuid = SETUP_GUID;
//	SETUP_DATA      SetupData;
//	UINTN		VariableSize = sizeof(SetupData);	
//	UINT8		DdioData;	
//	Status = pRS->GetVariable( L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData );		
//	DdioData = (SetupData.GPI3Type << 3) | (SetupData.GPI2Type << 2) | (SetupData.GPI1Type << 1) | SetupData.GPI0Type;
//	DdioData |= (SetupData.GPO3Type << 7) | (SetupData.GPO2Type << 6) | (SetupData.GPO1Type << 5) | (SetupData.GPO0Type << 4);
//	EcDioDirAccess(ApiRead);
//	EcBramAccess(0x14, &DdioData, ApiWrite);
//	EcDioDirAccess(ApiWrite);
//	DdioData = (SetupData.GPI3Level << 3) | (SetupData.GPI2Level << 2) | (SetupData.GPI1Level << 1) | SetupData.GPI0Level;
//	DdioData |= (SetupData.GPO3Level << 7) | (SetupData.GPO2Level << 6) | (SetupData.GPO1Level << 5) | (SetupData.GPO0Level << 4);
//	EcDioValAccess(ApiRead);
//	EcBramAccess(0x14, &DdioData, ApiWrite);
//	EcDioValAccess(ApiWrite);	
//}
//<<CSKA_009_Elflo 20150903 
//----------------------------------------------------------------------------
// Procedure:   IT851X_SMART_FAN1
//
// Description: 
//  Initiate DIO according to DDIO item in setup menu
//
// Input:
//
// Output:      
//  EFI_SUCCESS
//
//----------------------------------------------------------------------------
#if defined(IT851X_FAN1_ENABLE) && (IT851X_FAN1_ENABLE == 1)
EFI_STATUS IT851X_SMART_FAN1 ()
{
        UINT8       	TmpData;
      
        EFI_STATUS Status = EFI_SUCCESS;
        EFI_GUID        SetupGuid = SETUP_GUID;
        SETUP_DATA      SetupData;
        UINTN           VariableSize = sizeof(SetupData);       
        Status = pRS->GetVariable( L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData );

        EcSmfAccess(0x00,ApiRead);              

        switch (SetupData.IT851XFan1SmartFanMode) 
        {
                case 0:         //Full_Mode           	
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData &= ~BIT7;
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = 0x64;	//Full Mode
			EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
                        break;

                case 1:         //Manual_Mode
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData &= ~BIT7;
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = SetupData.Fan1ManualPWM;
			EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
                        break;

                case 2:         //Auto_Mode_PWM:
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData = BIT7|(SetupData.Fan1Invert)<<6|(SetupData.Fan1MonitorTher)<<0;		
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = SetupData.Fan1StartTemp;
			EcBramAccess(EcReg_Dat4, &TmpData, ApiWrite);
			TmpData= SetupData.Fan1OffTemp;
			EcBramAccess(EcReg_Dat5, &TmpData, ApiWrite);
			TmpData= SetupData.Fan1StartPWM;
			EcBramAccess(EcReg_Dat6, &TmpData, ApiWrite);
			TmpData= SetupData.Fan1Slope;
			EcBramAccess(EcReg_Dat7, &TmpData, ApiWrite);
                        break;

                default:
                        break;
        
        }

        EcSmfAccess(0x00,ApiWrite);               

        return EFI_SUCCESS;
}
#endif //IT851X_FAN1_ENABLE
//----------------------------------------------------------------------------
// Procedure:   IT851X_SMART_FAN2
//
// Description: 
//  Initiate DIO according to DDIO item in setup menu
//
// Input:
//
// Output:      
//  EFI_SUCCESS
//
//----------------------------------------------------------------------------
#if defined(IT851X_FAN2_ENABLE) && (IT851X_FAN2_ENABLE == 1)
EFI_STATUS IT851X_SMART_FAN2 ()
{
        UINT8       TmpData;
//      UINT8       FanMode;

        EFI_STATUS Status = EFI_SUCCESS;
        EFI_GUID        SetupGuid = SETUP_GUID;
        SETUP_DATA      SetupData;
        UINTN           VariableSize = sizeof(SetupData);
        
        Status = pRS->GetVariable( L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData );

        EcSmfAccess(0x01,ApiRead);              

        switch (SetupData.IT851XFan2SmartFanMode) 
        {
                case 0:         //Full_Mode           	
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData &= ~BIT7;
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = 0x64;	//Full Mode
			EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
                        break;

                case 1:         //Manual_Mode
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData &= ~BIT7;
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = SetupData.Fan2ManualPWM;
			EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
                        break;

                case 2:         //Auto_Mode_PWM:
			EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
			TmpData = BIT7|(SetupData.Fan2Invert)<<6|(SetupData.Fan2MonitorTher)<<0;		
			EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
			TmpData = SetupData.Fan2StartTemp;
			EcBramAccess(EcReg_Dat4, &TmpData, ApiWrite);
			TmpData= SetupData.Fan2OffTemp;
			EcBramAccess(EcReg_Dat5, &TmpData, ApiWrite);
			TmpData= SetupData.Fan2StartPWM;
			EcBramAccess(EcReg_Dat6, &TmpData, ApiWrite);
			TmpData= SetupData.Fan2Slope;
			EcBramAccess(EcReg_Dat7, &TmpData, ApiWrite);
                        break;

                default:
                        break;
        
        }

        EcSmfAccess(0x01,ApiWrite);    

        return EFI_SUCCESS;
}
#endif //IT851X_FAN2_ENABLE

EFI_STATUS BRAM_Init(
    IN AMI_BOARD_INIT_PROTOCOL         *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
        //Update Standard parameter block
        AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
        SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
        AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
        EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
        SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;

        EFI_STATUS                      Status=EFI_SUCCESS;
        //Check if parameters passed are VALID and
        if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

        switch (InitStep) {
                case isGetSetupData:
                        break;

                case isPrsSelect:
                        break;

                case isAfterActivate:
//>>CSKUA_022_Elflo 20160422				
//                        #if defined(IT851X_FAN1_ENABLE) && (IT851X_FAN1_ENABLE == 1)
//                              IT851X_SMART_FAN1();
//                        #endif        //IT851X_FAN2_ENABLE
//                        #if defined(IT851X_FAN2_ENABLE) && (IT851X_FAN2_ENABLE == 1)
//                              IT851X_SMART_FAN2();
//                        #endif        //IT851X_FAN2_ENABLE
//<<CSKUA_022_Elflo 20160422                              
                        //-     DynamicDioInit();	//-CSKA_009_Elflo 20150903                       
                              
                        break;

                case isAfterBootScript:
                        break;

                case isGetModeData:
                        break;

                case isBeforeActivate:
                        break;

            #if  AMI_SIO_MINOR_VERSION >= 6     
                case isAfterSmmBootScript:      
                        break;
            #endif

                default:
                        Status=EFI_INVALID_PARAMETER;
        } //switch

        return Status;
}
#endif //IT8518_BRAM_PRESENT
//RayWu, ADD 2014/07/17 <<
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8518_COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_BOARD_INIT_PROTOCOL         *This - AMI Board Int Protocol.
//  IN  UINTN                           *Function - AMI Sdl SIO Init Routine.
//  IN  OUT VOID                        *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if IT8518_SERIAL_PORT1_PRESENT | IT8518_SERIAL_PORT2_PRESENT
EFI_STATUS IT8518_COM_Init(
    IN AMI_BOARD_INIT_PROTOCOL     *This,
    IN UINTN                    *Function,
    IN OUT VOID                 *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        // Disable IODecode?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8518_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2014/03/26 >>
//        //Only decode UART1/UART2. More others UART port is decode in PEI
//        //Attention! Remove the more com ports to PEI decode.
//        if(dev->DeviceInfo->Uid < 0x02) {
//            //Decode?
//            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            } else {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }
//        }
//RayWu, REMOVE 2014/03/26 <<
        break;

    case isGetModeData:
        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    }//switch
    return Status;
}
#endif
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8518_KBC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_BOARD_INIT_PROTOCOL         *This - AMI Board Int Protocol.
//  IN  UINTN                           *Function - AMI Sdl SIO Init Routine.
//  IN  OUT VOID                        *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if IT8518_KEYBOARD_PRESENT
EFI_STATUS IT8518_KBC_Init(
    IN AMI_BOARD_INIT_PROTOCOL         *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;

    EFI_STATUS                      Status=EFI_SUCCESS;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
    case isPrsSelect:
    case isAfterActivate:
    case isAfterBootScript:
    case isGetModeData:
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2014/03/26 >>
//        //Decode?
//        if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        } else {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        }
//RayWu, REMOVE 2014/03/26 <<
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8518_CIR_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_BOARD_INIT_PROTOCOL         *This - AMI Board Int Protocol.
//  IN  UINTN                           *Function - AMI Sdl SIO Init Routine.
//  IN  OUT VOID                        *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//            EFI_STATUS
//            EFI_SUCCESS - Initial step sucessfully
//            EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if IT8518_CIR_PORT_PRESENT
EFI_STATUS IT8518_CIR_Init(
    IN AMI_BOARD_INIT_PROTOCOL         *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    EFI_STATUS                      Status=EFI_SUCCESS;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        // Disable IODecode?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8518_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        break;
    case isGetModeData:
        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
