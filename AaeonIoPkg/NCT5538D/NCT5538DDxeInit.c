//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file NCT5538DDxeInit.c

  1. Port SIO DXE initial table and routine for GenericSio.c
  2. Define SIO bootscriptable table
**/
//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiGenericSio.h>
#include <Library/AmiSioDxeLib.h>

extern DXE_DEVICE_INIT_DATA   NCT5538D_DXE_COM_Mode_Init_Table[];
extern SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[];
extern UINT8 DXE_GPIO_Init_Table_Before_Active_Count;
extern SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[];
extern UINT8 DXE_GPIO_Init_Table_After_Active_Count;
#if NCT5538D_PME_CONTROLLER_PRESENT
extern SIO_DEVICE_INIT_DATA   DXE_PME_Init_Table_Before_Active[];
extern UINT8 DXE_PME_Init_Table_Before_Active_Count;
#endif
#if NCT5538D_HWM_PRESENT
extern SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[];
extern UINT8 DXE_HWM_Init_Table_After_Active_Count;
#endif

//----------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//----------------------------------------------------------------------
/**
  This function will clear SIO resource.

  @param  Dev                   Pointer to SIO device private data structure.
**/
VOID NCT5538D_ClearDevResource(
    IN  SIO_DEV2    *Dev
)
{
    //Enter Configuration Mode.
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE);
    //Select device
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_LDN_SEL_REGISTER);
    IoWrite8(NCT5538D_CONFIG_DATA, Dev->DeviceInfo->Ldn);
    //Clear Base Address
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_BASE1_HI_REGISTER);
    IoWrite8(NCT5538D_CONFIG_DATA, 0);
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_BASE1_LO_REGISTER);
    IoWrite8(NCT5538D_CONFIG_DATA, 0);
    //Clear Interrupt
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_IRQ1_REGISTER);
    IoWrite8(NCT5538D_CONFIG_DATA, 0);
    //Exit Configuration Mode
    IoWrite8(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_EXIT_VALUE);
    return;
}

/**
  This function will call back in ready to boot phase to save registers into bootscript table.

  @param  Event                 Event whose notification function is being invoked.
  @param  Context               Pointer to the notification function's context.
**/

static VOID NCT5538D_GpioCallbackReadyToBoot(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_STATUS         Status;

    EFI_S3_SAVE_STATE_PROTOCOL * BootScriptProtocol = NULL;
    EFI_GUID gSioEfiS3SaveStateProtocolGuid= EFI_S3_SAVE_STATE_PROTOCOL_GUID;

    Status = pBS->LocateProtocol(&gSioEfiS3SaveStateProtocolGuid,NULL,&BootScriptProtocol);
    if (EFI_ERROR(Status)) {
        TRACE((-1,"GenericSIO: SIODXE fail to locate EfiBootScriptSaveProtocol %r",Status));
        return;
    }
    //1,AMI_TODO:enter cfgmode
    SioLib_BootScriptIO(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
    SioLib_BootScriptIO(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);

    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_DATA, \
                            NCT5538D_LDN_SEL_REGISTER, NCT5538D_LDN_GPIO2, BootScriptProtocol);

    //3,save table value
    SioLib_BootScriptSioS3SaveTable(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_DATA, \
                                    DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count, BootScriptProtocol);
    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_MODE_EXIT_VALUE, BootScriptProtocol);
    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);
}


//----------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//----------------------------------------------------------------------

/**
  This function provide COMs initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/

EFI_STATUS NCT5538D_COM_Init(
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
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
//    UINT8                           rv; //ComMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            NCT5538D_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
//        //Only decode UART1/UART2. More others UART port is decode in PEI
//        //Attention! Remove the more com ports to PEI decode.
//        if(Dev->DeviceInfo->Uid < 0x02) {
//            //Decode?
//            if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
//            } else {
//                AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
//            }
//        }
//        //Program COM RS485/RS232 Mode Registers.
//        if(NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//            rv=NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8;
//            rv |= NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
//        //Program COM Clock Source Registers.
//        if(NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].AndData8 == 0xFF) {
//            rv=NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].AndData8;
//            rv |= NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,NCT5538D_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+1].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
        //Program Device Mode register here(if NEEDED)use AmiSioProtocol
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


/**
  This function provide KBC initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if NCT5538D_KEYBOARD_PRESENT
EFI_STATUS NCT5538D_KBC_Init(
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
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;

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
//        //Decode
//        AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
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

/**
  This function provide PME initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if NCT5538D_PME_CONTROLLER_PRESENT
EFI_STATUS NCT5538D_PME_Init(
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
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //PME registers initial if needed.
        //OEM_TODO: You need to fill DXE_PME_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_DATA,\
                                DXE_PME_Init_Table_Before_Active,DXE_PME_Init_Table_Before_Active_Count);

        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
    case isGetModeData:
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

/**
  This function provide HWM initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if NCT5538D_HWM_PRESENT
EFI_STATUS NCT5538D_HWM_Init(
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
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
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
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
//        BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;
        ProgramIsaRegisterTable(NCT5538D_HWM_INDEX_PORT, NCT5538D_HWM_DATA_PORT,\
                                DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count);
        break;

    case isAfterBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
        BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;
        SioLib_BootScriptSioS3SaveTable(NCT5538D_HWM_INDEX_PORT, NCT5538D_HWM_DATA_PORT, \
                                        DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count, BootScriptProtocol);
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

/**
  This function provide GPIO initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/

EFI_STATUS NCT5538D_GPIO_Init(
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
        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_Before_Active,DXE_GPIO_Init_Table_Before_Active_Count);

        break;

    case isAfterActivate:

        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(NCT5538D_CONFIG_INDEX, NCT5538D_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count);

        //Create event for boot script
        //Because Gpio is not standard device which have no activate reg0x30,so create event to save regs
        Status = CreateReadyToBootEvent(
                     TPL_NOTIFY,
                     NCT5538D_GpioCallbackReadyToBoot,
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

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


