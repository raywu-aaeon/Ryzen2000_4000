//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file F81866DxeInit.c

  1. Port SIO DXE initial table and routine for GenericSio.c
  2. Define SIO bootscriptable table
**/
//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Library/AmiSioDxeLib.h>
#include <AmiGenericSio.h>
#include "F81866DxeIoTable.h"
#include <F81866SmartFansSetup.h>
#include <Protocol\SmmVariable.h>

/**
  This function will clear SIO resource.

  @param  Dev                   Pointer to SIO device private data structure.
**/
VOID F81866_ClearDevResource(
    IN  SIO_DEV2    *Dev
)
{
    //Enter Configuration Mode.
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    //Seclect device
    IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, Dev->DeviceInfo->Ldn);
    //Clear Base Address
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_HI_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_LO_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    //Clear Interrupt
    IoWrite8(F81866_CONFIG_INDEX, F81866_IRQ1_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    //Exit Configuration Mode
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);

    return;
}

/**
    Get the register value form HWM space register.

    @param  Register  Register value.
    @param  *Value    Data in the register.

**/
void
GetValueWithIO (
    IN UINT8 Register,
    OUT UINT8 *Value
)
{
    //Read the data from register
    IoWrite8(F81866_HWM_INDEX_PORT, Register);
    *Value = IoRead8(F81866_HWM_DATA_PORT);
    return;
}

/**
    Write the register value to HWM space register.

    @param  SaveState Point to s3 save state protocol.
    @param  Register  Register value.
    @param  *Value    Data in the register.

**/
void
WriteValueWithIO (
    IN EFI_S3_SAVE_STATE_PROTOCOL *SaveState,
    IN UINT8 Register,
    IN UINT8 Value
)
{
    UINT16      IndexReg = F81866_HWM_INDEX_PORT;
    UINT16      DataReg = F81866_HWM_DATA_PORT;
    
    if(SaveState == NULL) {      
        //Write the value to register
        IoWrite8(IndexReg, Register);
        IoWrite8(DataReg, Value);
    }
    else {
        //Save register into boot script.
        //Select register.
        IoWrite8(IndexReg, Register);
        //Read actual data.
        Value = IoRead8(DataReg);
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)IndexReg, (UINTN)1, &Register);
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)DataReg,  (UINTN)1, &Value);
    }

    return;
}

/**
    Program smart fan with setup setting.

    @param  SaveState Point to s3 save state protocol.
    @param  InSmm     Indicate in smm or not.
**/
VOID ProgramSmartFan(EFI_S3_SAVE_STATE_PROTOCOL *SaveState, BOOLEAN InSmm) 
{
    F81866_SMF_CONTROL          FanControl;
    UINTN                       Size = sizeof(F81866_SMF_CONTROL);
    EFI_GUID                    F81866HwmConfigGuid = F81866_SMF_GUID;
    EFI_STATUS                  Status;
    UINT8                       TempData;
    EFI_SMM_VARIABLE_PROTOCOL   *SmmVariable;
    UINT8                       Index;
    
    if(InSmm == FALSE) {
    //Get Setup variable
    Status = pRS->GetVariable( L"F81866_SMF", &F81866HwmConfigGuid, NULL, &Size, &FanControl);
    if(EFI_ERROR(Status))
        return;
    }
    else {
        Status = pSmst->SmmLocateProtocol(&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&SmmVariable);
        if(EFI_ERROR(Status))
            return;        
        Status = SmmVariable->SmmGetVariable (
                                 L"F81866_SMF",
                                 &F81866HwmConfigGuid,
                                 NULL,
                                 &Size,
                                 &FanControl
                                 );
        if(EFI_ERROR(Status))
            return;        
    }
    
    //Fan 1 setting
    switch (FanControl.Fan1SmartMode) {
    case 0://Manual Mode
        //Index 96h[1] = 1 [0]:0/1 RPM/PWM
        GetValueWithIO(0x96, &TempData);
        TempData &= ~BIT0;
        WriteValueWithIO(SaveState, 0x96, TempData | BIT1 | FanControl.Fan1Type); //Index 0x96[1-0]
        WriteValueWithIO(SaveState, 0xA2, (UINT8)FanControl.Fan1ManualControl); //Index 0xA2(MSB) Control value.
        WriteValueWithIO(SaveState, 0xA3, (UINT8)(FanControl.Fan1ManualControl >> 8)); //Index 0xA3(LSB) Control value.
        break;
    case 1://Automatic Mode
        //Index 96h[1] = 0 [0]:0/1 RPM/PWM
        //Fan type & mode            
        GetValueWithIO(0x96, &TempData);
        TempData &= ~(BIT0 | BIT1);
        WriteValueWithIO(SaveState, 0x96, TempData | FanControl.Fan1Type); //Index 0x96[1-0]
        GetValueWithIO(0xAF, &TempData);
        TempData &= ~(BIT0 | BIT1 | BIT7);
        WriteValueWithIO(SaveState, 0xAF, TempData | FanControl.Fan1Tempin); //Index 0xAF[7,1-0]
        //Set Boundary hysteresis 98h[3-0]
        GetValueWithIO(0x98, &TempData);
        TempData &= ~(BIT0 | BIT1 | BIT2 | BIT3);
        WriteValueWithIO(SaveState, 0x98, TempData | FanControl.Fan1Hysteresis);
        for(Index = 0;Index < 4;Index ++) {
            // Boundary A6h~A9h
            WriteValueWithIO(SaveState, 0xA6 + Index, FanControl.Fan1Boundary[Index]);
        }
        for(Index = 0;Index < 5;Index ++) {
            // Speed AAh~AEh
            TempData = FanControl.Fan1Segment[Index];
            if(FanControl.Fan1Type == 0) {
                //RPM mode
                //X% of full speed = (100-X)*32/X
                FanControl.Fan1Segment[Index] = (100 - TempData) * 32 / TempData;
            }
            else {
                FanControl.Fan1Segment[Index] = 0xFF * TempData / 100;
            }
            WriteValueWithIO(SaveState, 0xAA + Index, FanControl.Fan1Segment[Index]);
        }
        //Multi temperature 94h, 95h, 96h(9Fh[7]=1)
        if(FanControl.MultiTemp == 1) {
            GetValueWithIO(0x9F, &TempData);
            WriteValueWithIO(SaveState, 0x9F, TempData | BIT7);
            WriteValueWithIO(SaveState, 0x94, FanControl.Fan1Tb);
            WriteValueWithIO(SaveState, 0x96, FanControl.Fan1Ta);
            GetValueWithIO(0x95, &TempData);
            TempData &= ~(BIT6 | BIT5 | BIT4 | BIT2 | BIT1 | BIT0);
            WriteValueWithIO(SaveState, 0x95, (TempData | (FanControl.Fan1Ctup << 4) | FanControl.Fan1Ctdn));
            GetValueWithIO(0x9F, &TempData);
            TempData &= ~BIT7;
            WriteValueWithIO(SaveState, 0x9F, TempData);
        }
        break;
    }
    
    //Fan 2 setting
    switch (FanControl.Fan2SmartMode) {
    case 0://Manual Mode
        //Index 96h[3] = 1 [2]:0/1 RPM/PWM
        GetValueWithIO(0x96, &TempData);
        TempData &= ~(BIT2 | BIT3);
        WriteValueWithIO(SaveState, 0x96, TempData | BIT1 | FanControl.Fan2Type); //Index 0x96[3-2]
        WriteValueWithIO(SaveState, 0xB2, (UINT8)FanControl.Fan2ManualControl); //Index 0xB2(MSB) Control value.
        WriteValueWithIO(SaveState, 0xB3, (UINT8)(FanControl.Fan2ManualControl >> 8)); //Index 0xB3(LSB) Control value.
        break;
    case 1://Automatic Mode
        //Index 96h[3] = 0 [2]:0/1 RPM/PWM
        //Fan type & mode            
        GetValueWithIO(0x96, &TempData);
        TempData &= ~(BIT2 | BIT3);
        WriteValueWithIO(SaveState, 0x96, TempData | FanControl.Fan2Type); //Index 0x96[3-2]
        GetValueWithIO(0xBF, &TempData);
        TempData &= ~(BIT0 | BIT1 | BIT7);
        WriteValueWithIO(SaveState, 0xBF, TempData | FanControl.Fan2Tempin); //Index 0xAF[7,1-0]
        //Set Boundary hysteresis 98h[7-4]
        GetValueWithIO(0x98, &TempData);
        TempData &= ~(BIT4 | BIT5 | BIT6 | BIT7);
        WriteValueWithIO(SaveState, 0x98, TempData | FanControl.Fan2Hysteresis);
        for(Index = 0;Index < 4;Index ++) {
            // Boundary B6h~B9h
            WriteValueWithIO(SaveState, 0xB6 + Index, FanControl.Fan2Boundary[Index]);
        }
        for(Index = 0;Index < 5;Index ++) {
            // Speed BAh~BEh
            TempData = FanControl.Fan2Segment[Index];
            if(FanControl.Fan2Type == 0) {
                //RPM mode
                //X% of full speed = (100-X)*32/X
                FanControl.Fan2Segment[Index] = (100 - TempData) * 32 / TempData;
            }
            else {
                FanControl.Fan2Segment[Index] = 0xFF * TempData / 100;
            }
            WriteValueWithIO(SaveState, 0xBA + Index, FanControl.Fan2Segment[Index]);
        }
        break;
    }
    
    //Fan 3 setting
    switch (FanControl.Fan3SmartMode) {
    case 0://Manual Mode
        //Index 96h[5] = 1 [4]:0/1 RPM/PWM
        GetValueWithIO(0x96, &TempData);
        TempData &= ~(BIT4 | BIT5);
        WriteValueWithIO(SaveState, 0x96, TempData | BIT1 | FanControl.Fan3Type); //Index 0x96[5-4]
        WriteValueWithIO(SaveState, 0xC2, (UINT8)FanControl.Fan3ManualControl); //Index 0xC2(MSB) Control value.
        WriteValueWithIO(SaveState, 0xC3, (UINT8)(FanControl.Fan3ManualControl >> 8)); //Index 0xC3(LSB) Control value.
        break;
    case 1://Automatic Mode
        //Index 96h[5] = 0 [4]:0/1 RPM/PWM
        //Fan type & mode
        GetValueWithIO(0x96, &TempData);
        TempData &= ~(BIT4 | BIT5);
        WriteValueWithIO(SaveState, 0x96, TempData | FanControl.Fan3Type); //Index 0x96[5-4]
        GetValueWithIO(0xCF, &TempData);
        TempData &= ~(BIT0 | BIT1 | BIT7);
        WriteValueWithIO(SaveState, 0xCF, TempData | FanControl.Fan3Tempin); //Index 0xCF[7,1-0]
        //Set Boundary hysteresis 99h[3-0]
        GetValueWithIO(0x99, &TempData);
        TempData &= ~(BIT0 | BIT1 | BIT2 | BIT3);
        WriteValueWithIO(SaveState, 0x99, TempData | FanControl.Fan3Hysteresis);
        for(Index = 0;Index < 4;Index ++) {
            // Boundary C6h~C9h
            WriteValueWithIO(SaveState, 0xC6 + Index, FanControl.Fan3Boundary[Index]);
        }
        for(Index = 0;Index < 5;Index ++) {
            // Speed CAh~CEh
            TempData = FanControl.Fan3Segment[Index];
            if(FanControl.Fan3Type == 0) {
                //RPM mode
                //X% of full speed = (100-X)*32/X
                FanControl.Fan3Segment[Index] = (100 - TempData) * 32 / TempData;
            }
            else {
                FanControl.Fan3Segment[Index] = 0xFF * TempData / 100;
            }
            WriteValueWithIO(SaveState, 0xCA + Index, FanControl.Fan3Segment[Index]);
        }
        break;
    }
}

/**
  This function provide Floppy port initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if F81866_FLOPPY_PORT_PRESENT
EFI_STATUS F81866_FDC_Init(
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
    UINT8                           rv; //FdcMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        }
        //AMI_TODO: please check the register define and program FDC mode
        //Read FDC Mode register
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        if(Dev->NvData.DevMode)rv |= 0x10; //Bit00 set = FDD is Write Protect
        else rv &= (UINT8)(~0x10);
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
        //FDC Has 2 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        static CHAR16 FdcModeStr1[] = L"Read Write";
        static CHAR16 FdcModeStr2[] = L"Write Protect";
        static CHAR16 FdcModeHelp[] = L"Change mode of Floppy Disk Controller. Select 'Read Write' for normal operation. Select 'Write Protect' mode for read only operation.";
        //---------------------------------------------------
        Dev->DevModeCnt=2;
        //Make room for 2 floppy modes + Help String...
        Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
        if(Dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        Dev->DevModeStr[0]=&FdcModeStr1[0];
        Dev->DevModeStr[1]=&FdcModeStr2[0];
        Dev->DevModeStr[2]=&FdcModeHelp[0];
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

/**
  This function provide COMs initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
//#if F81866_SERIAL_PORT1_PRESENT | F81866_SERIAL_PORT2_PRESENT
EFI_STATUS F81866_COM_Init(
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
    UINT8                           rv; //ComMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //Only decode UART1/UART2. More others UART port is decode in PEI
        //Attention! Remove the more com ports to PEI decode.
        if(Dev->DeviceInfo->Uid < 0x02) {
            //Decode?
            if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
                AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            } else {
                AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            }
        }
        //Program COM RS485/RS232 Mode Registers.
        if(F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8 == 0xFF) {
            rv=F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
        } else {
            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8;
            rv |= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
        }
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
        ASSERT_EFI_ERROR(Status);
        //Program COM Clock Source Registers.
        if(F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].AndData8 == 0xFF) {
            rv=F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].OrData8;
        } else {
            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].Reg8,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].AndData8;
            rv |= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].OrData8;
        }
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].Reg8,&rv);
        ASSERT_EFI_ERROR(Status);
        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        if(Dev->DeviceInfo->Uid == 0x05) {
            //if(Dev->DeviceInfo->Uid == 0x01)    {
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);
            if(EFI_ERROR(Status))return Status;
            //clear Bit4~3 where COM Port mode is:
            rv &= 0xE7;
            switch (Dev->NvData.DevMode) {
            case 0:
                rv |= 0x00;    //Bit4~3 = 000, Disable IR1 function
                break;
            case 1:
                rv |= 0x10;    //Bit4~3 = 010, Enable IR1 function, active pulse is 1.6uS
                break;
            case 2:
                rv |= 0x18;    //Bit4~3 = 011, Enable IR1 function, active pulse is 3/16 bit time
                break;
            default:
                return EFI_INVALID_PARAMETER;
            }
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
            ASSERT_EFI_ERROR(Status);

            if (Dev->NvData.DevMode > 0) {
                //Get DSDT.. we have to update it.
                ACPI_HDR                        *dsdt;
                EFI_PHYSICAL_ADDRESS            a;

                Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
                if(EFI_ERROR(Status)) {
                    SIO_TRACE((TRACE_SIO,"F81866_COM_Init: Fail to Get DSDT - returned %r\n", Status));
                    ASSERT_EFI_ERROR(Status);
                } else dsdt=(ACPI_HDR*)a;
                Status=UpdateAslNameOfDevice(dsdt, Dev->DeviceInfo->AslName, "_HID", 0x1005D041);
                ASSERT_EFI_ERROR(Status);
                //Checksum
                dsdt->Checksum = 0;
                dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
            }
        }
        //Programm Device to PCI IRQ shanre mode
        if((Dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && Dev->ResOwner) {
            //Programm ResOwner
            //1. Config the share bit
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,FALSE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xFC;
            rv |= 0x01; //Bit0: 1: IRQ is ahring with other device
                        //Bit1: 0: Sharing IRQ active low level mode
            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            //Programm Device
            //1. Config the share bit
            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            rv &= 0xFC;
            rv |= 0x01; //Bit0: 1: IRQ is ahring with other device
                        //Bit1: 1: Sharing IRQ active low level mode
            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
            ASSERT_EFI_ERROR(Status);
            //2. Config the IRQ resource
            //Status=AmiSio->Access(AmiSio,FALSE,FALSE,0x70,&rv);
            //ASSERT_EFI_ERROR(Status);
            //rv = Dev->ResOwner->VlData.DevIrq1; //Get the IRQ from the ResOwner
            //Status=AmiSio->Access(AmiSio,TRUE,FALSE,0x70,&rv);
            //ASSERT_EFI_ERROR(Status);
            //3. Update the Device Private Data
            //Dev->VlData.DevIrq1 = Dev->ResOwner->VlData.DevIrq1;
        }
        break;

    case isGetModeData:
        if(Dev->DeviceInfo->Uid == 0x05) {
            //COM6 Has 3 possible modes
            //Make sure Device Mode Strings are Static VAR!
            //Otherwise The string will gone after control flow leave this function
            static CHAR16 Com6ModeStr1[] = L"Disable IR1";
            static CHAR16 Com6ModeStr2[] = L"Enable IR1 (pulse 1.6uS)";
            static CHAR16 Com6ModeStr3[] = L"Enable IR1 (pulse 3/16 bit time)";
            static CHAR16 Com6ModeHelp[] = L"Change the Serial Port mode. Enable, Disable and Configure IR function.";
            //---------------------------------------------------
            Dev->DevModeCnt=3;
            //Make room for 2 floppy modes + Help String...
            Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
            if(Dev->DevModeStr==NULL) {
                Status=EFI_OUT_OF_RESOURCES;
                ASSERT_EFI_ERROR(Status);
                return Status;
            }
            Dev->DevModeStr[0]=&Com6ModeStr1[0];
            Dev->DevModeStr[1]=&Com6ModeStr2[0];
            Dev->DevModeStr[2]=&Com6ModeStr3[0];
            Dev->DevModeStr[3]=&Com6ModeHelp[0];
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
    }//switch
    return Status;
}
//#endif

/**
  This function provide LPT initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if F81866_PARALLEL_PORT_PRESENT
EFI_STATUS F81866_LPT_Init(
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
    UINT8                           rv; //LptMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        //depend on LPT Mode it may or may not use a DMA channel
        //Strcpy(&Dev->DeviceInfo->AslName[0],"LPTE");
        //EFI_DEADLOOP();
        if(Dev->NvData.DevMode >3 ) {  //7 mode
            //if(Dev->NvData.DevMode&0x02) { //4 mode
            ACPI_HDR                        *dsdt;
            EFI_PHYSICAL_ADDRESS            a;

            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT
                //last parameter is 0-based index in F81866_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"EPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, TRUE);
            }
            //Get DSDT.. we have to update it.
            Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
            if(EFI_ERROR(Status)) {
                SIO_TRACE((TRACE_SIO,"F81866_LPT_Init: Fail to Get DSDT - returned %r\n", Status));
                ASSERT_EFI_ERROR(Status);
            } else dsdt=(ACPI_HDR*)a;
            Status=UpdateAslNameOfDevice(dsdt, Dev->DeviceInfo->AslName, "_HID", 0x0104D041);
            //Checksum
            dsdt->Checksum = 0;
            dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
        } else {
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"LPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, FALSE);
            }
        }
        ASSERT_EFI_ERROR(Status);
        break;

    case isBeforeActivate:
        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        }
        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        //Program Lpt Mode register following SIO Specification instructions.
        //Set mode:Bit2-0 set = LPT mode
        //clear lowest 3 bits where LPT mode is:
        rv&=0xF8;
        switch (Dev->NvData.DevMode) {
        case 0:
            rv|=4; //STD Printer Mode
            break;
        case 1:
            rv|=0; //SPP Mode
            break;
        case 2:
            rv|=1; //EPP-1.9 and SPP Mode
            break;
        case 3:
            rv|=5; //EPP-1.7 and SPP Mode
            break;
        case 4:
            rv|=2; //ECP Mode
            break;
        case 5:
            rv|=3; //ECP and EPP-1.9 Mode
            break;
        case 6:
            rv|=7; //ECP and EPP-1.7 Mode
            break;
        default:
            return EFI_INVALID_PARAMETER;
        }
        //Program back Device Mode register
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
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
        Dev->DevModeCnt=7;
        //Make room for 2 floppy modes + Help String...
        Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
        if(Dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        Dev->DevModeStr[0]=&LptModeStr1[0];
        Dev->DevModeStr[1]=&LptModeStr2[0];
        Dev->DevModeStr[2]=&LptModeStr3[0];
        Dev->DevModeStr[3]=&LptModeStr4[0];
        Dev->DevModeStr[4]=&LptModeStr5[0];
        Dev->DevModeStr[5]=&LptModeStr6[0];
        Dev->DevModeStr[6]=&LptModeStr7[0];
        Dev->DevModeStr[7]=&LptModeHelp[0];
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

/**
  This function provide PS/2 KBC initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if F81866_KEYBOARD_PRESENT
EFI_STATUS F81866_KBC_Init(
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
        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
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
#endif

/**
  This function provide PME initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
#if F81866_PME_CONTROLLER_PRESENT
EFI_STATUS F81866_PME_Init(
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
        ProgramIsaRegisterTable(F81866_CONFIG_INDEX, F81866_CONFIG_DATA,\
                                DXE_PME_Init_Table_Before_Active,sizeof(DXE_PME_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

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
#if F81866_HWM_PRESENT
EFI_STATUS F81866_HWM_Init(
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
        ProgramIsaRegisterTable(F81866_HWM_INDEX_PORT, F81866_HWM_DATA_PORT,\
                                DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        ProgramSmartFan(NULL, FALSE);
        break;

    case isAfterBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
        BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;
        SioLib_BootScriptSioS3SaveTable(F81866_HWM_INDEX_PORT, F81866_HWM_DATA_PORT, \
                                        DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
        ProgramSmartFan(BootScriptProtocol, FALSE);
        break;
#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:   
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
        BootScriptProtocol=(EFI_S3_SMM_SAVE_STATE_PROTOCOL*)Args->Param3;
        //If No Bank exist in HWM Config register.
        SioLib_BootScriptSioS3SaveTable(F81866_HWM_INDEX_PORT, F81866_HWM_DATA_PORT, 
                                        DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)),BootScriptProtocol);
        ProgramSmartFan(BootScriptProtocol, TRUE);
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
//#if F81866_GPIO_PORT_PRESENT
EFI_STATUS F81866_GPIO_Init(
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
    case isGetModeData:
        break;

    case isBeforeActivate:
        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(F81866_CONFIG_INDEX, F81866_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_Before_Active,sizeof(DXE_GPIO_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

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
//#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
