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
// Name:  <IT8728FDxeInit.c>
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
#include "IT8728FDxeIoTable.h"
//RayWu, ADD 2014/07/28 >>
#include <Token.h>
#include <Setup.h>
//RayWu, ADD 2014/07/28 <<
// <AMI_PHDR_START>

//RayWu, REMOVE 2015/05/05 >>
////RayWu, ADD 2014/07/28 >>
//#define IT8728HWMIndex	(UINT16)(IT8728F_HWM_BASE_ADDRESS + 0x05)
//#define IT8728HWMData	(UINT16)(IT8728F_HWM_BASE_ADDRESS + 0x06)	
//
//void IT8728HWMRegisterWrite(UINT8 Index, UINT8 Data)
//{
//	IoWrite8(IT8728HWMIndex, Index);
//	IoWrite8(IT8728HWMData, Data);
//}
//UINT8 IT8728HWMRegisterRead(UINT8 Index)
//{
//	UINT8 RegTmp8;
//	IoWrite8(IT8728HWMIndex, Index);
//	RegTmp8 = IoRead8(IT8728HWMData);
//	return RegTmp8;
//}
//
//#if defined(IT8728F_SMART_FAN_SUPPORT) && (IT8728F_SMART_FAN_SUPPORT == 1)
//#if defined(IT8728_SMF1_SUPPORT) && (IT8728_SMF1_SUPPORT == 1)
//void IT8728SmartFan1Support(UINT8 IT8728SMF1Control, UINT8 IT8728SMF1Mode, UINT8 IT8728SMF1PWMDuty
//			, UINT8 IT8728SMF1SPinPWMDuty, UINT8 IT8728SMF1OffTemp, UINT8 IT8728SMF1StartTemp, UINT8 IT8728SMF1FullTemp
//			, UINT8 IT8728SMF1PWMSlope)
//{
//	UINT8 RegTmp8;
//	
//	switch(IT8728SMF1Control){
//		case 0:	//Smart FAN disable, always running under full speed
//			RegTmp8 = IT8728HWMRegisterRead(0x13);
//			IT8728HWMRegisterWrite( 0x13, RegTmp8&(~BIT0) );
//			RegTmp8 = IT8728HWMRegisterRead(0x14);
//			IT8728HWMRegisterWrite( 0x14, RegTmp8|BIT0 );
//			break;
//		case 1:	//Smart FAN enable
//			RegTmp8 = IT8728HWMRegisterRead(0x13);
//			IT8728HWMRegisterWrite( 0x13, RegTmp8|BIT0 );
//			
//			switch(IT8728SMF1Mode){
//				case 0: //Manual Mode
//					RegTmp8 = IT8728HWMRegisterRead(0x15);
//					IT8728HWMRegisterWrite( 0x15, RegTmp8&(~BIT7) );
//					IT8728HWMRegisterWrite( 0x63, IT8728SMF1PWMDuty );
//					break;
//				case 1: //Automatic Mode
//					RegTmp8 = IT8728HWMRegisterRead(0x15);
//					RegTmp8 |= BIT7;
//					RegTmp8 &= ~(BIT0+BIT1); //Temperature Input Selection: TMPIN1
//					RegTmp8 &= ~BIT2; //Tachometer Closed-loop Mode: Disable
//					IT8728HWMRegisterWrite( 0x15, RegTmp8 );
//					IT8728HWMRegisterWrite( 0x63, IT8728SMF1SPinPWMDuty );
//					IT8728HWMRegisterWrite( 0x60, IT8728SMF1OffTemp );
//					IT8728HWMRegisterWrite( 0x61, IT8728SMF1StartTemp );
//					IT8728HWMRegisterWrite( 0x62, IT8728SMF1FullTemp );
//					IT8728HWMRegisterWrite( 0x64, IT8728SMF1PWMSlope );
//					break;
//				default :
//					break;
//			}
//			break;
//		default :
//			break;
//	} //switch(IT8728SMF1Control)
//}
//#endif //IT8728_SMF1_SUPPORT
//#if defined(IT8728_SMF2_SUPPORT) && (IT8728_SMF2_SUPPORT == 1)
//void IT8728SmartFan2Support(UINT8 IT8728SMF2Control, UINT8 IT8728SMF2Mode, UINT8 IT8728SMF2PWMDuty
//			, UINT8 IT8728SMF2SPinPWMDuty, UINT8 IT8728SMF2OffTemp, UINT8 IT8728SMF2StartTemp, UINT8 IT8728SMF2FullTemp
//			, UINT8 IT8728SMF2PWMSlope)
//{
//	UINT8 RegTmp8;
//	
//	switch(IT8728SMF2Control){
//		case 0:	//Smart FAN disable, always running under full speed
//			RegTmp8 = IT8728HWMRegisterRead(0x13);
//			IT8728HWMRegisterWrite( 0x13, RegTmp8&(~BIT1) );
//			RegTmp8 = IT8728HWMRegisterRead(0x14);
//			IT8728HWMRegisterWrite( 0x14, RegTmp8|BIT1 );
//			break;
//		case 1:	//Smart FAN enable
//			RegTmp8 = IT8728HWMRegisterRead(0x13);
//			IT8728HWMRegisterWrite( 0x13, RegTmp8|BIT1 );
//			
//			switch(IT8728SMF2Mode){
//				case 0: //Manual Mode
//					RegTmp8 = IT8728HWMRegisterRead(0x16);
//					IT8728HWMRegisterWrite( 0x16, RegTmp8&(~BIT7) );
//					IT8728HWMRegisterWrite( 0x6B, IT8728SMF2PWMDuty );
//					break;
//				case 1: //Automatic Mode
//					RegTmp8 = IT8728HWMRegisterRead(0x16);
//					RegTmp8 |= BIT7;
//					RegTmp8 &= ~BIT1; //Temperature Input Selection: TMPIN2
//					RegTmp8 |= BIT0;
//					RegTmp8 &= ~BIT2; //Tachometer Closed-loop Mode: Disable
//					IT8728HWMRegisterWrite( 0x16, RegTmp8 );
//					IT8728HWMRegisterWrite( 0x6B, IT8728SMF2SPinPWMDuty );
//					IT8728HWMRegisterWrite( 0x68, IT8728SMF2OffTemp );
//					IT8728HWMRegisterWrite( 0x69, IT8728SMF2StartTemp );
//					IT8728HWMRegisterWrite( 0x6A, IT8728SMF2FullTemp );
//					IT8728HWMRegisterWrite( 0x6C, IT8728SMF2PWMSlope );
//					break;
//				default :
//					break;
//			}
//			break;
//		default :
//			break;
//	} //switch(IT8728SMF2Control)
//}
//#endif //IT8728_SMF2_SUPPORT
//VOID	IT8728FSmartFanConfig()
//{
//	EFI_STATUS Status = EFI_SUCCESS;
//    	EFI_GUID	SetupGuid = SETUP_GUID;
//    	SETUP_DATA	SetupData;
//    	UINTN		VariableSize = sizeof(SetupData);
//	
//	Status = pRS->GetVariable( L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData );
//
//	#if defined(IT8728_SMF1_SUPPORT) && (IT8728_SMF1_SUPPORT == 1)
//	IT8728SmartFan1Support(SetupData.IT8728SMF1Control, SetupData.IT8728SMF1Mode
//				, SetupData.IT8728SMF1PWMDuty, SetupData.IT8728SMF1SPinPWMDuty, SetupData.IT8728SMF1OffTemp
//				, SetupData.IT8728SMF1StartTemp, SetupData.IT8728SMF1FullTemp
//				, SetupData.IT8728SMF1PWMSlope);
//	#endif
//	#if defined(IT8728_SMF2_SUPPORT) && (IT8728_SMF2_SUPPORT == 1)
//	IT8728SmartFan2Support(SetupData.IT8728SMF2Control, SetupData.IT8728SMF2Mode
//				, SetupData.IT8728SMF2PWMDuty, SetupData.IT8728SMF2SPinPWMDuty, SetupData.IT8728SMF2OffTemp
//				, SetupData.IT8728SMF2StartTemp, SetupData.IT8728SMF2FullTemp
//				, SetupData.IT8728SMF2PWMSlope);
//	#endif
//}
//#endif //IT8728F_SMART_FAN_SUPPORT
////RayWu, ADD 2014/07/28 <<
//RayWu, REMOVE 2015/05/05 <<
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_ClearDevResource
//
// Description:
//  This function will Clear SIO resource
//
// Input:
//  SIO_DEV2* dev
// Output:
//  NONE
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
VOID IT8728F_ClearDevResource(
    IN  SIO_DEV2    *dev
)
{
    IoWrite8(IT8728F_CONFIG_INDEX, 0x87);
    IoWrite8(IT8728F_CONFIG_INDEX, 0x01);
    IoWrite8(IT8728F_CONFIG_INDEX, 0x55);
#if (IT8728F_CONFIG_INDEX == 0x2E)
    IoWrite8(IT8728F_CONFIG_INDEX, 0x55);
#else
    IoWrite8(IT8728F_CONFIG_INDEX, 0xAA);
#endif

    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_LDN_SEL_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA, dev->DeviceInfo->Ldn);

    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_BASE1_HI_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA, 0);
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_BASE1_LO_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA, 0);
    IoWrite8(IT8728F_CONFIG_INDEX, IT8728F_IRQ1_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA, 0);

    IoWrite8(IT8728F_CONFIG_INDEX, 0x02);
    IoWrite8(IT8728F_CONFIG_DATA,  0x02);
    return;

}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_IT8728F_GpioCallbackReadyToBoot
//
// Description:
//  This function will call back in ready to boot phase to save registers
//  into bootscript table
// Input:
//  IN  EFI_EVENT Event
//  IN VOID	*Context
//
// Output:
//  NONE
//
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if IT8728F_GPIO_PORT_PRESENT
static VOID IT8728F_GpioCallbackReadyToBoot(IN EFI_EVENT Event,	IN VOID	*Context)
{
    EFI_STATUS         Status=EFI_SUCCESS;
    UINT8              value=0;
    UINT8              i=0;

    EFI_S3_SAVE_STATE_PROTOCOL * BootScriptProtocol = NULL;
    EFI_GUID gSioEfiS3SaveStateProtocolGuid= EFI_S3_SAVE_STATE_PROTOCOL_GUID;

    Status = pBS->LocateProtocol(&gSioEfiS3SaveStateProtocolGuid,NULL,&BootScriptProtocol);
    if (EFI_ERROR(Status)) {
        TRACE((-1,"GenericSIO: SIODXE fail to locate EfiBootScriptSaveProtocol %r",Status));
        return;
    }
    //1,AMI_TODO:enter cfgmode
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0x87, BootScriptProtocol);
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0x01, BootScriptProtocol);
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0x55, BootScriptProtocol);
#if (IT8728F_CONFIG_INDEX == 0x2E)
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0x55, BootScriptProtocol);
#else
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0xAA, BootScriptProtocol);
#endif
    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(IT8728F_CONFIG_INDEX, IT8728F_CONFIG_DATA, \
                            IT8728F_LDN_SEL_REGISTER, IT8728F_LDN_GPIO, BootScriptProtocol);

    //3,save table value
    SioLib_BootScriptSioS3SaveTable(IT8728F_CONFIG_INDEX, IT8728F_CONFIG_DATA, \
                                    DXE_GPIO_Init_Table_After_Active,sizeof(DXE_GPIO_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(IT8728F_CONFIG_INDEX, 0x02, BootScriptProtocol);
    SioLib_BootScriptIO(IT8728F_CONFIG_DATA, 0x02, BootScriptProtocol);
    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);
}
#endif

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_FDC_Init
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
// Modified:    Nothing
//
// Referrals:   None
//
// Notes:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
#if IT8728F_FLOPPY_PORT_PRESENT
EFI_STATUS IT8728F_FDC_Init(
    IN AMI_BOARD_INIT_PROTOCOL	*This,
    IN UINTN					*Function,
    IN OUT VOID					*ParameterBlock
)

{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK	*Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP        			InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL     			*AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL  			*PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    //---------------------------------------
    EFI_STATUS  					Status=EFI_SUCCESS;
    SIO_DEV2    					*dev=(SIO_DEV2*)AmiSio;
    UINT8       					rv;     //FdcMode Register
//---------------------------------
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        // Disable IODecode?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8728F_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2014/07/28 >>
//        //Decode?
//        if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        } else {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        }
//RayWu, REMOVE 2014/07/28 <<
        //AMI_TODO: please check the register define and program FDC mode
        //Read FDC Mode register
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);

        if(dev->NvData.DevMode)rv |= 0x01; //Bit00 set = FDD is Write Protect
        else rv &= (UINT8)(~0x01);

        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;


    case isGetModeData: {
        //FDC Has 2 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        static CHAR16 FdcModeStr1[] = L"Read Write";
        static CHAR16 FdcModeStr2[] = L"Write Protect";
        static CHAR16 FdcModeHelp[] = L"Change mode of Floppy Disk Controller. Select 'Read Write' for normal operation. Select 'Write Protect' mode for read only operation.";
        //---------------------------------------------------
        dev->DevModeCnt=2;
        //Make room for 2 floppy modes + Help String...
        dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(dev->DevModeCnt+1));
        if(dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        dev->DevModeStr[0]=&FdcModeStr1[0];
        dev->DevModeStr[1]=&FdcModeStr2[0];
        dev->DevModeStr[2]=&FdcModeHelp[0];
    }
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
#endif //#if IT8728F_FLOPPY_PORT_PRESENT
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_COM_Init
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
EFI_STATUS IT8728F_COM_Init(
    IN AMI_BOARD_INIT_PROTOCOL  *This,
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
//    UINT8                           rv; //ComMode Register //RayWu, REMOVE 2015/05/05
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear devcie resource ?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8728F_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2014/07/28 >>
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
//RayWu, REMOVE 2014/07/28 <<
//RayWu, REMOVE 2015/05/05 >>
//        // Program COM Clock Source Registers.
//        if(IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//            rv=IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8;
//            rv |= IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,IT8728F_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
//RayWu, REMOVE 2015/05/05 <<
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
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_LPT_Init
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
#if IT8728F_PARALLEL_PORT_PRESENT
EFI_STATUS IT8728F_LPT_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv; //LptMode Register
    ACPI_HDR                        *dsdt;
    EFI_PHYSICAL_ADDRESS            a;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear devcie resource ?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8728F_ClearDevResource(dev);
        }
        break;

    case isPrsSelect:
        //depend on LPT Mode it may or may not use a DMA channel
        //Strcpy(&dev->DeviceInfo->AslName[0],"LPTE");
        //EFI_DEADLOOP();
        if(dev->NvData.DevMode&0x02) { //4 mode
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT
                //last parameter is 0-based index in IT8728F_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(dev,"EPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SioDxeLibSetLptPrs(dev, TRUE);
            }
            //Get DSDT.. we have to update it.
            Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
            if(EFI_ERROR(Status)) {
                SIO_TRACE((TRACE_SIO,"IT8728F_LPT_Init: Fail to Get DSDT - returned %r\n", Status));
                ASSERT_EFI_ERROR(Status);
            } else dsdt=(ACPI_HDR*)a;
            Status=UpdateAslNameOfDevice(dsdt, dev->DeviceInfo->AslName, "_HID", 0x0104D041);
            //Checksum
            dsdt->Checksum = 0;
            dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
        } else {
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(dev,"LPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SioDxeLibSetLptPrs(dev, FALSE);
            }
        }
        ASSERT_EFI_ERROR(Status);
        break;

    case isBeforeActivate:
//RayWu, REMOVE 2014/07/28 >>
//        //Decode?
//        if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        } else {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        }
//RayWu, REMOVE 2014/07/28 <<
        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        //Program Lpt Mode register following SIO Specification instructions.
        //Set mode:Bit1-0 set = LPT mode
        //clear lowest 3 bits where LPT mode is:
        rv&=0xFC;
        switch (dev->NvData.DevMode) {
        case 0:
            rv|=0; //Standard Parallet Port mode(SPP)
            break;
        case 1:
            rv|=1; //EPP Mode
            break;
        case 2:
            rv|=2; //ECP Mode
            break;
        case 3:
            rv|=3; //EPP mode & ECP mode
            break;
        default:
            return EFI_INVALID_PARAMETER;
        }
        //Program back Device Mode register
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
        //LPT Has 4 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        //static CHAR16 LptModeStr1[] = L"Standard Parallet Port mode(SPP)"; //FINETUNE_081_RayWu, REMOVE 2015/01/27
        static CHAR16 LptModeStr1[] = L"Standard Parallel Port mode(SPP)"; //FINETUNE_081_RayWu, ADD 2015/01/27
        static CHAR16 LptModeStr2[] = L"EPP Mode";
        static CHAR16 LptModeStr3[] = L"ECP Mode";
        static CHAR16 LptModeStr4[] = L"EPP mode & ECP mode";
        static CHAR16 LptModeHelp[] = L"Change Parallel Port mode. Some of the Modes required a DMA resource. After Mode changing, Reset the System to reflect actual device settings.";
        //---------------------------------------------------
        dev->DevModeCnt=4;
        //Make room for 2 floppy modes + Help String...
        dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(dev->DevModeCnt+1));
        if(dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }

        dev->DevModeStr[0]=&LptModeStr1[0];
        dev->DevModeStr[1]=&LptModeStr2[0];
        dev->DevModeStr[2]=&LptModeStr3[0];
        dev->DevModeStr[3]=&LptModeStr4[0];
        dev->DevModeStr[4]=&LptModeHelp[0];
    }
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
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_KBC_Init
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
#if IT8728F_KEYBOARD_PRESENT
EFI_STATUS IT8728F_KBC_Init(
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
//RayWu, REMOVE 2014/07/28 >>
//        //Decode?
//        if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable) {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        } else {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//        }
//RayWu, REMOVE 2014/07/28 <<
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
// Procedure: IT8728F_HWM_Init
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
#if IT8728F_HWM_PRESENT
EFI_STATUS IT8728F_HWM_Init(
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

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
//    EFI_S3_SAVE_STATE_PROTOCOL      *BootScriptProtocol;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
    case isGetModeData:
        break;

    case isBeforeActivate:
        // HWM registers initial if needed.
        // OEM_TODO: You need to fill DXE_ENV_Init_Table_Before_Active[] first.
//    	BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)dev->Owner->SaveState; //No use
        ProgramIsaRegisterTable(IT8728F_CONFIG_INDEX, IT8728F_CONFIG_DATA,\
                                DXE_ENV_Init_Table_Before_Active,sizeof(DXE_ENV_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        break;

    case isAfterActivate:
        // HWM registers initial if needed.
        // OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
    // >> Move to PEI Init Phase
    //    ProgramIsaRegisterTable(IT8728F_HWM_INDEX_PORT, IT8728F_HWM_DATA_PORT,\
    //                            DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
    // << Move to PEI Init Phase
        //RayWu, REMOVE 2015/05/05 >>
        ////RayWu, ADD 2014/07/28 >>
        //#if defined(IT8728F_SMART_FAN_SUPPORT) && (IT8728F_SMART_FAN_SUPPORT == 1)
        //IT8728FSmartFanConfig();
        //#endif //IT8728F_SMART_FAN_SUPPORT
        ////RayWu, ADD 2014/07/28 <<
        //RayWu, REMOVE 2015/05/05 <<
        break;

    case isAfterBootScript:
        // Restore HWM registers after Sx resume, if needed.
        // Below HWM read/write interface is LPC/ISA interface,
        // if other interface, please re-program it.
        // This, Width, Address, Count, Buffer
    // >> Because the Hardware Monitor Init has been moved to PEI Init phase, so it is no longer needed BootScript
    //    SioLib_BootScriptSioS3SaveTable(IT8728F_HWM_INDEX_PORT, IT8728F_HWM_DATA_PORT, \
    //                                    DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
    // << Because the Hardware Monitor Init has been moved to PEI Init phase, so it is no longer needed BootScript
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
// Procedure: IT8728F_GPIO_Init
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
#if IT8728F_GPIO_PORT_PRESENT
EFI_STATUS IT8728F_GPIO_Init(
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

    EFI_STATUS                      Status=EFI_SUCCESS;
    EFI_EVENT                       GpioReadytoBoot;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
    case isGetModeData:
        break;

    case isBeforeActivate:
        // Initial GPIO register if you need.
        // OEM_TODO: You need to fill DXE_GPIO_Init_Table_Before_Active[] first.
        break;

    case isAfterActivate:

        // Initial GPIO register if you need.
        // OEM_TODO: You need to fill DXE_GPIO_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(IT8728F_CONFIG_INDEX, IT8728F_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_After_Active,sizeof(DXE_GPIO_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

        //Create event for boot script
        //Because Gpio is not standar device which have no activate reg0x30,so create event to save regs
        Status = CreateReadyToBootEvent(
                     TPL_NOTIFY,
                     IT8728F_GpioCallbackReadyToBoot,
                     NULL,
                     &GpioReadytoBoot
                 );
        ASSERT_EFI_ERROR(Status);

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
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8728F_CIR_Init
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
#if IT8728F_CIR_PORT_PRESENT
EFI_STATUS IT8728F_CIR_Init(
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
        //Clear devcie resource ?
        if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)) {
            IT8728F_ClearDevResource(dev);
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
