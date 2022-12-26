//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file F81804DxeInit.c

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
#include <Setup.h>

#if defined(F81804_SMF_SUPPORT) && (F81804_SMF_SUPPORT == 1)
extern VOID F81804SmartFunction(VOID);
extern VOID SmartFanBootScript(EFI_S3_SAVE_STATE_PROTOCOL *BootScriptProtocol);
#endif //F81801_SMF_SUPPORT == 1

extern DXE_DEVICE_INIT_DATA   F81804_DXE_COM_Mode_Init_Table[];
extern SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[];
extern UINT8 DXE_GPIO_Init_Table_Before_Active_Count;
extern SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[];
extern UINT8 DXE_GPIO_Init_Table_After_Active_Count;
#if F81804_PME_CONTROLLER_PRESENT
extern SIO_DEVICE_INIT_DATA   DXE_PME_Init_Table_Before_Active[];
extern UINT8 DXE_PME_Init_Table_Before_Active_Count;
#endif
#if F81804_HWM_PRESENT
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
VOID F81804_ClearDevResource(
    IN  SIO_DEV2    *Dev
)
{
    //Enter Configuration Mode.    
    IoWrite8(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_ENTER_VALUE);
    //Select device
    IoWrite8(F81804_CONFIG_INDEX, F81804_LDN_SEL_REGISTER);
    IoWrite8(F81804_CONFIG_DATA, Dev->DeviceInfo->Ldn);
    //Clear Base Address
    IoWrite8(F81804_CONFIG_INDEX, F81804_BASE1_HI_REGISTER);
    IoWrite8(F81804_CONFIG_DATA, 0);
    IoWrite8(F81804_CONFIG_INDEX, F81804_BASE1_LO_REGISTER);
    IoWrite8(F81804_CONFIG_DATA, 0);
    //Clear Interrupt
    IoWrite8(F81804_CONFIG_INDEX, F81804_IRQ1_REGISTER);
    IoWrite8(F81804_CONFIG_DATA, 0);
    //Exit Configuration Mode
    IoWrite8(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_EXIT_VALUE);
   
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
static VOID F81804_GpioCallbackReadyToBoot(
    IN EFI_EVENT    Event,
    IN VOID         *Context
    
)
{
    EFI_STATUS         Status;
    
    EFI_S3_SAVE_STATE_PROTOCOL * BootScriptProtocol = NULL;
    EFI_GUID gSioEfiS3SaveStateProtocolGuid= EFI_S3_SAVE_STATE_PROTOCOL_GUID;

    Status = pBS->LocateProtocol(&gSioEfiS3SaveStateProtocolGuid,NULL,&BootScriptProtocol);
    if (EFI_ERROR(Status)) {
        return;
    }
    //1,AMI_TODO:enter cfgmode
    SioLib_BootScriptIO(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
    SioLib_BootScriptIO(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_ENTER_VALUE, BootScriptProtocol);
   
    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(F81804_CONFIG_INDEX, F81804_CONFIG_DATA, \
                            F81804_LDN_SEL_REGISTER, F81804_LDN_GPIO, BootScriptProtocol);

    //3,save table value
    //If only one device in DXE_GPIO_Init_Table_After_Active table.
    SioLib_BootScriptSioS3SaveTable(F81804_CONFIG_INDEX, F81804_CONFIG_DATA, \
                                    DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count, BootScriptProtocol);

    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(F81804_CONFIG_INDEX, F81804_CONFIG_MODE_EXIT_VALUE, BootScriptProtocol);
   
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
EFI_STATUS F81804_COM_Init(
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
    //AAEON_OVERRIDE-- UINT8                           rv; //ComMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81804_ClearDevResource(Dev);
        }
        //Change HID value in DXE phase for correct devcie path.
        if(Dev->DeviceInfo->Uid == 0x01) {
            if (Dev->NvData.DevMode > 0) {
                Dev->EisaId.HID = 0x51041D0;
            }
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //Only decode UART1/UART2. More others UART port is decode in PEI
        //Attention! Remove the more com ports to PEI decode.
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
        if(Dev->DeviceInfo->Uid < 0x02) {
            //Decode?
            if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
                AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            } else {
                AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            }
        }
#endif
#if 0 //AAEON_OVERRIDE: program in uartmode module
        //Program COM RS485/RS232 Mode Registers.
        if(F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8 == 0xFF) {
            rv=F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
        } else {
            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8;
            rv |= F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
        }
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
        ASSERT_EFI_ERROR(Status);
        //Program COM Clock Source Registers.
        if(F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].AndData8 == 0xFF) {
            rv=F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].OrData8;
        } else {
            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].Reg8,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].AndData8;
            rv |= F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].OrData8;
        }
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81804_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+2].Reg8,&rv);
        ASSERT_EFI_ERROR(Status);
        //Program Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        if(Dev->DeviceInfo->Uid == 0x01)    {
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
            //clear Bit4~3 where COM Port mode is:
            rv &= 0xE7;
            switch (Dev->NvData.DevMode) {
                case 0:
                    rv |= 0x00;    //Bit4~3 = 0X,  Disable IR1 function. 
                break;
                case 1:
                    rv |= 0x10;    //Bit4~3 = 10, Enable IR1 function, active pulse is 1.6uS.
                break;
                case 2:
                    rv |= 0x18;    //Bit4~3 = 11, Enable IR1 function, active pulse is 3/16 bit time.
                break;
                default: return EFI_INVALID_PARAMETER;
            }            
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);
        }
        //Program Device to PCI IRQ share mode
        if((Dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && Dev->ResOwner) {
            //Program ResOwner
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,FALSE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xFE;
            rv |= 0x01; //Bit0: 1: IRQ is sharing with other device
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            //Program Device
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xFE;
            rv |= 0x01; //Bit0: 1: IRQ is sharing with other device
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);

        }
#endif
        break;

    case isGetModeData:

    	#if defined(F81804_SERIAL_PORT2_IR_SUPPORT) && (F81804_SERIAL_PORT2_IR_SUPPORT == 1)
        if(Dev->DeviceInfo->Uid == 0x01)
        {
            //IRDA Has 3 possible modes
            //Make sure Device Mode Strings are Static VAR!
            //Otherwise The string will gone after control flow leave this function
            static CHAR16 IrdaModeStr1[] = L"Disable IR1 function";
            static CHAR16 IrdaModeStr2[] = L"Enable IR1 function, active pulse is 1.6uS.";
            static CHAR16 IrdaModeStr3[] = L"Enable IR1 function, active pulse is 3/16 bit time";
            static CHAR16 IrdaModeHelp[] = L"Change the Serial Port mode. Select <IR1 mode> or <Normal mode> mode";
            //---------------------------------------------------
            Dev->DevModeCnt=3;
            //Make room for 3 SIR modes + Help String...
            Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
            if(Dev->DevModeStr==NULL) {
                Status=EFI_OUT_OF_RESOURCES;
                ASSERT_EFI_ERROR(Status);
                return Status;
            }
            Dev->DevModeStr[0]=&IrdaModeStr1[0];
            Dev->DevModeStr[1]=&IrdaModeStr2[0];
            Dev->DevModeStr[2]=&IrdaModeStr3[0];
            Dev->DevModeStr[4]=&IrdaModeHelp[0];
        }        
        #endif //(F81804_SERIAL_PORT2_IR_SUPPORT) && (F81804_SERIAL_PORT2_IR_SUPPORT == 1)
        
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
#if F81804_KEYBOARD_PRESENT
EFI_STATUS F81804_KBC_Init(
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
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:   	
#endif    	
        break;

    case isBeforeActivate:
        //Decode
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
        AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
#endif
        break;

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
#if F81804_PME_CONTROLLER_PRESENT
EFI_STATUS F81804_PME_Init(
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
        ProgramIsaRegisterTable(F81804_CONFIG_INDEX, F81804_CONFIG_DATA,\
                                DXE_PME_Init_Table_Before_Active,DXE_PME_Init_Table_Before_Active_Count);

        break;

    case isAfterActivate:
        break;
        
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:   	
        break;
#endif
        
    case isAfterBootScript:
    case isGetModeData:
        break;

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
#if F81804_HWM_PRESENT
EFI_STATUS F81804_HWM_Init(
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
    UINT8                           BankRegister = 0x9F; //Need porting
    
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
    case isGetModeData:
        break;

    case isBeforeActivate:
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_ENV_Init_Table_Before_Active[] first.
        break;

    case isAfterActivate:
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(F81804_HWM_INDEX_PORT, F81804_HWM_DATA_PORT,\
                                DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count);
        
#if defined(F81804_SMF_SUPPORT) && (F81804_SMF_SUPPORT == 1)
        F81804SmartFunction();
#endif
        break;

    case isAfterBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
    	BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;

    	//If Bank exist in HWM Config register.
        SioLib_BootScriptSioS3SaveTableEx(F81804_HWM_INDEX_PORT, F81804_HWM_DATA_PORT, BankRegister, \
                                                DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count, BootScriptProtocol);
        
#if defined(F81804_SMF_SUPPORT) && (F81804_SMF_SUPPORT == 1)
        SmartFanBootScript(BootScriptProtocol);
#endif

        break;
        
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
    	BootScriptProtocol=(EFI_S3_SMM_SAVE_STATE_PROTOCOL*)Args->Param3;
    	//If Bank exist in HWM Config register.
        SioLib_BootScriptSioS3SaveTableEx(F81804_HWM_INDEX_PORT, F81804_HWM_DATA_PORT, BankRegister, \
                                                DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count, BootScriptProtocol);                                    
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
EFI_STATUS F81804_GPIO_Init(
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
        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_Before_Active[] first.
#if 0 //AAEON_OVERRIDE: Programed in PEI phase
        ProgramIsaRegisterTable(F81804_CONFIG_INDEX, F81804_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_Before_Active,DXE_GPIO_Init_Table_Before_Active_Count);
#endif
        break;

    case isAfterActivate:

        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_After_Active[] first.
#if 0 //AAEON_OVERRIDE: Programed in PEI phase
        ProgramIsaRegisterTable(F81804_CONFIG_INDEX, F81804_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count);
#endif
#if  AMI_SIO_MINOR_VERSION < 6 
        //Create event for boot script
        //Because Gpio is not standard device which have no activate reg0x30,so create event to save regs
        Status = CreateReadyToBootEvent(
                     TPL_NOTIFY,
                     F81804_GpioCallbackReadyToBoot,
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
        SioLib_BootScriptSioS3SaveTable(F81804_CONFIG_INDEX, F81804_CONFIG_DATA, \
                                        DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count, BootScriptProtocol);
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
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

