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
// Name:  <W83627DHGDxeInit.c>
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiGenericSio.h>

#include "W83627DHGDxeIoTable.h"
//smart fan
#if W83627DHG_SmartFan_SUPPORT
VOID W83627DHGSmartFanInit(VOID);
#endif
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_ClearDevResource
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
VOID W83627DHG_ClearDevResource(
    IN  SIO_DEV2    *dev
)
{
    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE);

    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_LDN_SEL_REGISTER);
    IoWrite8(W83627DHG_CONFIG_DATA, dev->DeviceInfo->Ldn);

    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_BASE1_HI_REGISTER);
    IoWrite8(W83627DHG_CONFIG_DATA, 0);
    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_BASE1_LO_REGISTER);
    IoWrite8(W83627DHG_CONFIG_DATA, 0);
    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_IRQ1_REGISTER);
    IoWrite8(W83627DHG_CONFIG_DATA, 0);

    IoWrite8(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_EXIT_VALUE);
    
    return;

}

/**
  This function will save registers into bootscript table when more than one Devive or Bank in a table.

  @param  IndexReg              Register of LPC index port.
  @param  DataReg               Register of LPC data port.
  @param  SelectReg             Register to select LDN of SIO or bank of HW Monitor.
  @param  Table                 Pointer to initialize SIO_DEVICE_INIT_DATA table.
  @param  Count                 Count of SIO_DEVICE_INIT_DATA table.
  @param  SaveState             Pointer to EFI_S3_SAVE_STATE_PROTOCOL.
**/
static VOID SioLib_BootScriptSioS3SaveTableEx(
	UINT16 		IndexReg,
	UINT16 		DataReg,
	UINT8 		SelectReg,
	SIO_DEVICE_INIT_DATA  *Table,
	UINT8 		Count,
	EFI_S3_SAVE_STATE_PROTOCOL *SaveState
)
{
	UINT8       i;
	UINT8		val, reg;
	
    for (i=0; i < Count; i++) {
        reg = (UINT8)(Table[i].Reg16 & 0xFF);
        //Select the Bank or LDN first,if it is Select register.
        if(reg == SelectReg){
        	//Select LDN/Bank number Register.
            IoWrite8(IndexReg, SelectReg);
            val = (IoRead8(DataReg) & Table[i].AndData8) | Table[i].OrData8;
            //Write LDN/Bank number.
            IoWrite8(DataReg, val); 
        }else{
            //Select register.
			IoWrite8(IndexReg, reg);
			//Read actual data.
			val = IoRead8(DataReg);
        }
        //Save register into boot script.
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)IndexReg, (UINTN)1, &reg);
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)DataReg,  (UINTN)1, &val);
    }
}


/**
  This function will call back in ready to boot phase to save registers into bootscript table.

  @param  Event                 Event whose notification function is being invoked.
  @param  Context               Pointer to the notification function's context.
**/

#if  AMI_SIO_MINOR_VERSION >= 6
static VOID W83627DHG_SmmGpioRecordBootScript(
		EFI_S3_SAVE_STATE_PROTOCOL      *BootScriptProtocol		
)
{   
    //1,AMI_TODO:enter cfgmode
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);

    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_DATA, \
                            W83627DHG_LDN_SEL_REGISTER, W83627DHG_LDN_GPIO6, BootScriptProtocol);

    //3,save table value
    //If more than one device in DXE_GPIO_Init_Table_After_Active table.
    SioLib_BootScriptSioS3SaveTable(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_DATA, \
            DXE_GPIO_Init_Table_After_Active,sizeof(DXE_GPIO_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);

    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_EXIT_VALUE, BootScriptProtocol);

}
#endif//#if  AMI_SIO_MINOR_VERSION >= 6
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_GpioCallbackReadyToBoot
//
// Description:
//  This function will call back in ready to boot phase to save registers
//  into bootscript table
// Input:
//  IN  EFI_EVENT Event  
//  IN VOID *Context
//
// Output: 
//  NONE
//
//------------------------------------------------------------------------- 
// <AMI_PHDR_END>
static VOID W83627DHG_GpioCallbackReadyToBoot(IN EFI_EVENT Event, IN VOID *Context)
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
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_DATA, \
            W83627DHG_LDN_SEL_REGISTER, W83627DHG_LDN_GPIO6, BootScriptProtocol);

    //3,save table value
    SioLib_BootScriptSioS3SaveTable(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_DATA, \
            DXE_GPIO_Init_Table_After_Active,sizeof(DXE_GPIO_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_MODE_EXIT_VALUE, BootScriptProtocol);
    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);
}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_FDC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_FLOPPY_PORT_PRESENT
EFI_STATUS W83627DHG_FDC_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
//)
AMI_BOARD_INIT_PROTOCOL *This,
IN UINTN                    *Function,
IN OUT VOID                 *ParameterBlock
)

{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    //---------------------------------------
    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv;     //FdcMode Register
//---------------------------------
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep)
    {
        case isGetSetupData:
            // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)){
                W83627DHG_ClearDevResource(dev);
            }
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
//RayWu, REMOVE 2015/08/07 >>
//            //Decode?
//            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
//                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }else{
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }
//RayWu, REMOVE 2015/08/07 <<
            //AMI_TODO: please check the register define and program FDC mode

            //Read FDC Mode register
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;

            if(dev->NvData.DevMode)rv |= 0x01; //Bit00 set = FDD is Write Protect
            else rv &= (UINT8)(~0x01);

            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);

        break;

        case isGetModeData:
 
        {
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

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
        case isAfterSmmBootScript:      
        break;
#endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif //#if W83627DHG_FLOPPY_PORT_PRESENT
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_SERIAL_PORT1_PRESENT | W83627DHG_SERIAL_PORT2_PRESENT
EFI_STATUS W83627DHG_COM_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
        AMI_BOARD_INIT_PROTOCOL *This,
        IN UINTN                    *Function,
        IN OUT VOID                 *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    //---------------------------------------
    EFI_STATUS  Status=EFI_SUCCESS;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;
//RayWu, REMOVE 2015/08/07 >>
//    UINT8       rv;
//
//    ACPI_HDR                        *dsdt;
//    EFI_PHYSICAL_ADDRESS            a;
//RayWu, REMOVE 2015/08/07 <<

    switch (InitStep)
    {
        case isGetSetupData:
            // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)){
                W83627DHG_ClearDevResource(dev);
            }
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
//RayWu, REMOVE 2015/08/07 >>
//            //Only decode UART1/UART2. More others UART port is decode in PEI
//            //Attention! Remove the more com ports to PEI decode.
//            if(dev->DeviceInfo->Uid < 0x02){
//                //Decode?
//                if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
//                    AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//                }else{
//                    AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//                }
//            }
//            // Program COM Clock Source Registers.
//            if(W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//                rv=W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//            } else {
//                Status=AmiSio->Access(AmiSio, FALSE, FALSE, W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//                ASSERT_EFI_ERROR(Status);
//                rv &= W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].AndData8;
//                rv |= W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].OrData8;
//            }
//            Status=AmiSio->Access(AmiSio,TRUE,FALSE,W83627DHG_DXE_COM_Mode_Init_Table[dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);           
//            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//            if(dev->DeviceInfo->Uid == 0x01) {
//                //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//                Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
//                ASSERT_EFI_ERROR(Status);
//                if(EFI_ERROR(Status))return Status;
//                //clear Bit5~3 where COM Port mode is:
//                rv &= 0xC7;
//                switch (dev->NvData.DevMode) {
//                    case 0:
//                        rv |= 0x00;    //Bit5~3 = 000, Standard Serial Port Mode
//                    break;
//                    case 1:
//                        rv |= 0x10;    //Bit5~3 = 010, IrDA, active pulse is 1.6uS
//                    break;
//                    case 2:
//                        rv |= 0x18;    //Bit5~3 = 011, IrDA, active pulse is 3/16 bit time
//                    break;
//                    case 3:
//                        rv |= 0x38;    //Bit5~3 = 111, ASK-IR 
//                    break;
//                    default: return EFI_INVALID_PARAMETER;
//                }
//                Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
//                ASSERT_EFI_ERROR(Status);
//                if(EFI_ERROR(Status))return Status;
//                
//                if (dev->NvData.DevMode > 0){
//                    //Get DSDT.. we have to update it.
//                    Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
//                    if(EFI_ERROR(Status)){
//                        SIO_TRACE((TRACE_SIO,"W83627DHG_COM_Init: Fail to Get DSDT - returned %r\n", Status));
//                        ASSERT_EFI_ERROR(Status);
//                    } else dsdt=(ACPI_HDR*)a;
//                    Status=UpdateAslNameOfDevice(dsdt, dev->DeviceInfo->AslName, "_HID", 0x1005D041);
//
//                    //Checksum
//                    dsdt->Checksum = 0;
//                    dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
//                }
//            }
//RayWu, REMOVE 2015/08/07 <<

        break;
        case isGetModeData:
//RayWu, REMOVE 2015/08/07 >>
//        if(dev->DeviceInfo->Uid == 0x01)
//        {
//            //IRDA Has 4 possible modes
//            //Make sure Device Mode Strings are Static VAR!
//            //Otherwise The string will gone after control flow leave this function
//            static CHAR16 IrdaModeStr1[] = L"Standard Serial Port Mode";
//            static CHAR16 IrdaModeStr2[] = L"IrDA Active pulse 1.6 uS";
//            static CHAR16 IrdaModeStr3[] = L"IrDA Active pulse 3/16 bit time";
//            static CHAR16 IrdaModeStr4[] = L"ASKIR Mode";
//            static CHAR16 IrdaModeHelp[] = L"Change the Serial Port mode. Select <High Speed> or <Normal mode> mode";
//            //---------------------------------------------------   
//            dev->DevModeCnt=4;
//            //Make room for 2 floppy modes + Help String...
//            dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(dev->DevModeCnt+1));
//            if(dev->DevModeStr==NULL) {
//                Status=EFI_OUT_OF_RESOURCES;
//                ASSERT_EFI_ERROR(Status);
//                return Status;
//            }
//            dev->DevModeStr[0]=&IrdaModeStr1[0];
//            dev->DevModeStr[1]=&IrdaModeStr2[0];
//            dev->DevModeStr[2]=&IrdaModeStr3[0];
//            dev->DevModeStr[3]=&IrdaModeStr4[0];
//            dev->DevModeStr[4]=&IrdaModeHelp[0];
//        }
//RayWu, REMOVE 2015/08/07 <<
	break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
        case isAfterSmmBootScript:      
        break;
#endif

        default: Status=EFI_INVALID_PARAMETER;
    }//switch
    return Status;
}
#endif //#if W83627DHG_SERIAL_PORT1_PRESENT | W83627DHG_SERIAL_PORT2_PRESENT
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_LPT_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_PARALLEL_PORT_PRESENT
EFI_STATUS W83627DHG_LPT_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
    AMI_BOARD_INIT_PROTOCOL *This,
    IN UINTN                    *Function,
    IN OUT VOID                 *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    //---------------------------------------
    EFI_STATUS  Status=EFI_SUCCESS;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;
    UINT8       rv;                //LptMode Register

    ACPI_HDR                        *dsdt;
    EFI_PHYSICAL_ADDRESS            a;

    switch (InitStep) {
        case isGetSetupData:
            // Disable IODecode?
            if((!dev->DeviceInfo->Implemented) || (!dev->NvData.DevEnable)){
                W83627DHG_ClearDevResource(dev);
            }
        break;

        case isPrsSelect:
            //depend on LPT Mode it may or may not use a DMA channel
            Strcpy(&dev->DeviceInfo->AslName[0],"LPTE");
            if(dev->NvData.DevMode&0x02) {
                #if ACPI_SUPPORT
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(dev,"EPPR", 1);
                #else
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SioDxeLibSetLptPrs(dev, TRUE);
                #endif
                //Get DSDT.. we have to update it.
                Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
                if(EFI_ERROR(Status)){
                    SIO_TRACE((TRACE_SIO,"W83627DHG_LPT_Init: Fail to Get DSDT - returned %r\n", Status));
                    ASSERT_EFI_ERROR(Status);
                } else dsdt=(ACPI_HDR*)a;
                Status=UpdateAslNameOfDevice(dsdt, dev->DeviceInfo->AslName, "_HID", 0x0104D041);

                //Checksum
                dsdt->Checksum = 0;
                dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
            }else {
                #if ACPI_SUPPORT
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(dev,"LPPR", 1);
                #else
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SioDxeLibSetLptPrs(dev, FALSE);
                #endif
            }
            ASSERT_EFI_ERROR(Status);

        break;

        case isBeforeActivate:
//RayWu, REMOVE 2015/08/07 >>
//            //Decode?
//            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
//                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }else{
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }
//RayWu, REMOVE 2015/08/07 <<
            //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
            //Program Lpt Mode register following SIO Specification instructions.
            //Set mode:Bit2-0 set = LPT mode
            //clear lowest 3 bits where LPT mode is:
            rv&=0xF8;
            switch (dev->NvData.DevMode) {
                    case 0:    rv|=4; //STD Printer Mode
                        break;
                    case 1:    rv|=0; //SPP Mode
                        break;
                    case 2:    rv|=1; //EPP-1.9 and SPP Mode
                        break;
                    case 3:    rv|=5; //EPP-1.7 and SPP Mode
                        break;
                    case 4:    rv|=2; //ECP Mode
                        break;
                    case 5:    rv|=3; //ECP and EPP-1.9 Mode
                        break;
                    case 6:    rv|=7; //ECP and EPP-1.7 Mode
                        break;
                default: return EFI_INVALID_PARAMETER;
            }
            //Program back Device Mode register
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);

        break;

        case isGetModeData:
        {
            //LPT Has 7 possible modes
            //Make sure Device Mode Strings are Static VAR!
            //Otherwise The string will gone after control flow leave this function
            static CHAR16 LptModeStr1[] = L"STD Printer Mode";
            static CHAR16 LptModeStr2[] = L"SPP Mode";
            static CHAR16 LptModeStr3[] = L"EPP-1.9 and SPP Mode";
            static CHAR16 LptModeStr4[] = L"EPP-1.7 and SPP Mode";
            static CHAR16 LptModeStr5[] = L"ECP Mode";
            static CHAR16 LptModeStr6[] = L"ECP and EPP 1.9 Mode";
            static CHAR16 LptModeStr7[] = L"ECP and EPP 1.7 Mode";
            static CHAR16 LptModeHelp[] = L"Change Parallel Port mode. Some of the Modes required a DMA resource. After Mode changing, Reset the System to reflect actual device settings.";
        //---------------------------------------------------   
            dev->DevModeCnt=7;
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
            dev->DevModeStr[4]=&LptModeStr5[0];
            dev->DevModeStr[5]=&LptModeStr6[0];
            dev->DevModeStr[6]=&LptModeStr7[0];
            dev->DevModeStr[7]=&LptModeHelp[0];
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

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif //#if W83627DHG_PARALLEL_PORT_PRESENT
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_KBC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_KEYBOARD_PRESENT
EFI_STATUS W83627DHG_KBC_Init(
//    IN    AMI_SIO_PROTOCOL     *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL  *PciIo,
//    IN    SIO_INIT_STEP        InitStep
    AMI_BOARD_INIT_PROTOCOL *This,
    IN UINTN                    *Function,
    IN OUT VOID                 *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;

    //---------------------------------------
    EFI_STATUS  Status=EFI_SUCCESS;

    switch (InitStep) {
        case isGetSetupData:
        case isPrsSelect:
        case isAfterActivate:
        case isAfterBootScript:

        case isGetModeData:

        break;

        case isBeforeActivate:
//RayWu, REMOVE 2015/08/07 >>
//            //Decode?
//            if(dev->DeviceInfo->Implemented && dev->NvData.DevEnable){
//                AmiSioLibSetLpcDeviceDecoding(PciIo,dev->VlData.DevBase1, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }else{
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, dev->DeviceInfo->Uid, dev->DeviceInfo->Type);
//            }
//RayWu, REMOVE 2015/08/07 <<
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
        case isAfterSmmBootScript:      
        break;
#endif

        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif //#if W83627DHG_KEYBOARD_PRESENT

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_HWM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_HWM_PRESENT
EFI_STATUS W83627DHG_HWM_Init(
    AMI_BOARD_INIT_PROTOCOL         *This,
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
    EFI_S3_SAVE_STATE_PROTOCOL      *BootScriptProtocol;

    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:

        case isGetModeData:
        break;

        case isBeforeActivate:
        break;

        case isAfterActivate:
            // HWM registers initial if needed.
            // OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
            ProgramIsaRegisterTable(W83627DHG_HWM_INDEX_PORT, W83627DHG_HWM_DATA_PORT,\
                    DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

            #if W83627DHG_SmartFan_SUPPORT
            W83627DHGSmartFanInit();
            #endif
        break;

        case isAfterBootScript:
            // Restore HWM registers after Sx resume, if needed.
            // Below HWM read/write interface is LPC/ISA interface,
            // if other interface, please re-program it.
            // This, Width, Address, Count, Buffer
        	BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)dev->Owner->SaveState;
            SioLib_BootScriptSioS3SaveTable(W83627DHG_HWM_INDEX_PORT, W83627DHG_HWM_DATA_PORT, \
                    DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
        break;
#if  AMI_SIO_MINOR_VERSION >= 6    	
        case isAfterSmmBootScript:   	
            //Restore HWM registers after Sx resume, if needed.
            //Below HWM read/write interface is LPC/ISA interface,
            //if other interface, please re-program it.
            //This, Width, Address, Count, Buffer
        	BootScriptProtocol=(EFI_S3_SMM_SAVE_STATE_PROTOCOL*)Args->Param3;
        	//If Bank exist in HWM Config register.
            SioLib_BootScriptSioS3SaveTable(W83627DHG_HWM_INDEX_PORT, W83627DHG_HWM_DATA_PORT, \
                    DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
        break;
#endif 
        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_GPIO_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
EFI_STATUS W83627DHG_GPIO_Init(
    AMI_BOARD_INIT_PROTOCOL         *This,
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
#if  AMI_SIO_MINOR_VERSION < 6
    EFI_EVENT                       GpioReadytoBoot;
#else       
	EFI_S3_SAVE_STATE_PROTOCOL     *BootScriptProtocol;
#endif 	 
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        case isGetModeData:
        break;

        case isBeforeActivate:
        break;

        case isAfterActivate:
            
            // Initial GPIO register if you need.
            // OEM_TODO: You need to fill DXE_GPIO_Init_Table_After_Active[] first.
            ProgramIsaRegisterTable(W83627DHG_CONFIG_INDEX, W83627DHG_CONFIG_DATA,\
                    DXE_GPIO_Init_Table_After_Active,sizeof(DXE_GPIO_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
#if  AMI_SIO_MINOR_VERSION < 6  
            //Create event for boot script
            //Because Gpio is not standar device which have no activate reg0x30,so create event to save regs
            Status = CreateReadyToBootEvent(
                TPL_NOTIFY,
                W83627DHG_GpioCallbackReadyToBoot,
                NULL,
                &GpioReadytoBoot
            );
            ASSERT_EFI_ERROR(Status);
#endif
        break;

        case isAfterBootScript:
        break;
#if  AMI_SIO_MINOR_VERSION >= 6    	
        case isAfterSmmBootScript:   	
			BootScriptProtocol=(EFI_S3_SMM_SAVE_STATE_PROTOCOL*)Args->Param3;
			W83627DHG_SmmGpioRecordBootScript(BootScriptProtocol);
        break;
#endif 
        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_SPI_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_SPI_PORT_PRESENT
EFI_STATUS W83627DHG_SPI_Init(
//    IN    AMI_SIO_PROTOCOL        *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL     *PciIo,
//    IN    SIO_INIT_STEP           InitStep
        AMI_BOARD_INIT_PROTOCOL     *This,
        IN UINTN                    *Function,
        IN OUT VOID                 *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS  Status=EFI_SUCCESS;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
        break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;

        case isGetModeData:
        break;
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:   	
        break;
#endif 
        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif //#if W83627DHG_ACPI_PORT_PRESENT
// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: W83627DHG_ACPI_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
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
#if W83627DHG_ACPI_PRESENT
EFI_STATUS W83627DHG_ACPI_Init(
//    IN    AMI_SIO_PROTOCOL        *AmiSio,
//    IN    EFI_PCI_IO_PROTOCOL     *PciIo,
//    IN    SIO_INIT_STEP           InitStep
        AMI_BOARD_INIT_PROTOCOL     *This,
        IN UINTN                    *Function,
        IN OUT VOID                 *ParameterBlock )
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS  Status=EFI_SUCCESS;
    SIO_DEV2    *dev=(SIO_DEV2*)AmiSio;
    #if W83627DHG_AC_POWER_LOSS
    SETUP_DATA  SetupData;
    EFI_GUID    SetupGuid = SETUP_GUID;
    UINTN       Size = sizeof(SETUP_DATA);
    UINT8       Val;
    #endif

    switch (InitStep) {
        case isGetSetupData:
        break;

        case isPrsSelect:
        break;

        case isBeforeActivate:
            #if W83627DHG_AC_POWER_LOSS
            //Get Setup variable
            Status=pRS->GetVariable( L"Setup", &SetupGuid, NULL, &Size, &SetupData);
            if(Status != EFI_SUCCESS) return Status;
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xE4,&Val);    //LPT Configuration Reg, Read the reg value
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
            //0x00->always turn off
            //0x01->always turn on
            //0x02->dependen on the state before the power loss
            //0x03->User defines the state before power loss. CRE6[4]:0/1->on/off
            //Clear bit5,6
            Val &=0x9F;
            //Set bit5,6 by SetupData.LastState setting
            Val |= ((UINT8)((SetupData.LastState)<<5));
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xE4,&Val);    //LPT Configuration Reg, Read the reg value
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
            #endif
        break;

        case isAfterActivate:
        break;

        case isAfterBootScript:
        break;


        case isGetModeData:
        break;
 
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:   	
        break;
#endif 
        default: Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif //#if W83627DHG_ACPI_PRESENT
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
