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
/** @file IT8625DxeInit.c

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
#include <IT8625SmartFansSetup.h>
#include <Protocol\SmmVariable.h>

extern DXE_DEVICE_INIT_DATA   IT8625_DXE_COM_Mode_Init_Table[];
extern SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[];
extern UINT8 DXE_GPIO_Init_Table_After_Active_Count;
extern SIO_DEVICE_INIT_DATA   DXE_ENV_Init_Table_Before_Active[];
extern UINT8 DXE_ENV_Init_Table_Before_Active_Count;
extern SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[];
extern UINT8 DXE_HWM_Init_Table_After_Active_Count;

//----------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//----------------------------------------------------------------------
/**
  This function will clear SIO resource.

  @param  Dev                   Pointer to SIO device private data structure.
**/
VOID IT8625_ClearDevResource(
    IN  SIO_DEV2    *Dev
)
{
    //Enter Configuration Mode.
    IoWrite8(IT8625_CONFIG_INDEX, 0x87);
    IoWrite8(IT8625_CONFIG_INDEX, 0x01);
    IoWrite8(IT8625_CONFIG_INDEX, 0x55);
    #if (IT8625_CONFIG_INDEX == 0x2E)
    IoWrite8(IT8625_CONFIG_INDEX, 0x55);
    #else
    IoWrite8(IT8625_CONFIG_INDEX, 0xAA);
    #endif
    //Select device
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_LDN_SEL_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, Dev->DeviceInfo->Ldn);
    //Clear Base Address
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_BASE1_HI_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, 0);
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_BASE1_LO_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, 0);
    //Clear Interrupt
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_IRQ1_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, 0);
    //Exit Configuration Mode
    IoWrite8(IT8625_CONFIG_INDEX, 0x02);
    IoWrite8(IT8625_CONFIG_DATA,  0x02);
    return;
}

/**
  This function will call back in ready to boot phase to save registers into bootscript table.

  @param  Event                 Event whose notification function is being invoked.
  @param  Context               Pointer to the notification function's context.
**/
static VOID IT8625_GpioCallbackReadyToBoot(
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
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0x87, BootScriptProtocol);
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0x01, BootScriptProtocol);
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0x55, BootScriptProtocol);
    #if (IT8625_CONFIG_INDEX == 0x2E)
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0x55, BootScriptProtocol);
    #else
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0xAA, BootScriptProtocol);
    #endif
    //2,AMI_TODO:select gpio device
    SioLib_BootscriptLdnSel(IT8625_CONFIG_INDEX, IT8625_CONFIG_DATA, \
                            IT8625_LDN_SEL_REGISTER, IT8625_LDN_GPIO, BootScriptProtocol);

    //3,save table value
    SioLib_BootScriptSioS3SaveTable(IT8625_CONFIG_INDEX, IT8625_CONFIG_DATA, \
                                    DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count, BootScriptProtocol);
    //4,AMI_TODO:exit cfg mode
    SioLib_BootScriptIO(IT8625_CONFIG_INDEX, 0x02, BootScriptProtocol);
    SioLib_BootScriptIO(IT8625_CONFIG_DATA, 0x02, BootScriptProtocol);
    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);
}

/**
    Get the register value form HWM space register.

    @param  BankNo    Bank Number.
    @param  Register  Register value.
    @param  *Value    Data in the register.

**/
void
GetValueWithIO (
    IN UINT8 BankNo,
    IN UINT8 Register,
    OUT UINT8 *Value
)
{
    UINT8       Temp;

    // Enter Bank NO!
    IoWrite8(IT8625_HWM_INDEX_PORT, 0x06);
    Temp = IoRead8(IT8625_HWM_DATA_PORT);
    Temp &= 0x9F ;// Bit6-5
    IoWrite8(IT8625_HWM_DATA_PORT, (Temp | BankNo));

    //Read the data from register
    IoWrite8(IT8625_HWM_INDEX_PORT, Register);
    *Value = IoRead8(IT8625_HWM_DATA_PORT);
    return;
}

/**
    Write the register value to HWM space register.

    @param  BankNo    Bank Number.
    @param  Register  Register value.
    @param  *Value    Data in the register.

**/
void
WriteValueWithIO (
    IN EFI_S3_SAVE_STATE_PROTOCOL *SaveState,        
    IN UINT8 BankNo,
    IN UINT8 Register,
    IN UINT8 Value
)
{
    UINT8       Temp;
    UINT16      IndexReg = IT8625_HWM_INDEX_PORT;
    UINT16      DataReg = IT8625_HWM_DATA_PORT;
    UINT8       BankSel = 0x06;
    
    IoWrite8(IndexReg, BankSel);
    Temp = IoRead8(DataReg);
    Temp &= 0x9F ;// Bit6-5
    Temp |= (BankNo << 5);
    IoWrite8(DataReg, Temp);
    if(SaveState == NULL) {      
        //Write the value to register
        IoWrite8(IndexReg, Register);
        IoWrite8(DataReg, Value);
    }
    else {
        //Save register into boot script.
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)IndexReg, (UINTN)1, &BankSel);
        SaveState->Write(SaveState, 0x00, EfiBootScriptWidthUint8, (UINT64)DataReg,  (UINTN)1, &Temp);
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

**/
/* // >> AAEON_OVERRIDE --
VOID ProgramSmartFan(EFI_S3_SAVE_STATE_PROTOCOL *SaveState, BOOLEAN InSmm) 
{
    IT8625_SMF_CONTROL        SMFControl;
    UINTN                       Size = sizeof(IT8625_SMF_CONTROL);
    EFI_GUID                    It8625HwmConfigGuid = IT8625_SMF_GUID;
    EFI_STATUS                  Status;
    UINT8                       TempData;
    EFI_SMM_VARIABLE_PROTOCOL   *SmmVariable;
    
    if(InSmm == FALSE) {
    //Get Setup variable
    Status = pRS->GetVariable( L"IT8625_SMF", &It8625HwmConfigGuid, NULL, &Size, &SMFControl);
    if(EFI_ERROR(Status))
        return;
    }
    else {
        Status = pSmst->SmmLocateProtocol(&gEfiSmmVariableProtocolGuid, NULL, (VOID**)&SmmVariable);
        if(EFI_ERROR(Status))
            return;        
        Status = SmmVariable->SmmGetVariable (
                                 L"IT8625_SMF",
                                 &It8625HwmConfigGuid,
                                 NULL,
                                 &Size,
                                 &SMFControl
                                 );
        if(EFI_ERROR(Status))
            return;        
    }
    //Fan Polarity
    GetValueWithIO(0, 0x14, &TempData);
    TempData &= 0x7F;
    WriteValueWithIO(SaveState, 0, 0x14, TempData | (SMFControl.FanPolarity << 7)); //Bank 0 Index 0x14[7]
    
    //Fan 1 setting
    switch (SMFControl.Fan1SmartMode) {
    case 0://Software Mode
        //Index 15h[7] = 0
        GetValueWithIO(0, 0x15, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x15, TempData); //Bank 0 Index 0x15
        WriteValueWithIO(SaveState, 0, 0x63, SMFControl.Fan1PwmControl); //Bank 0 Index 0x63 PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 15h[7] = 1
        //Fan type & mode            
        WriteValueWithIO(SaveState, 0, 0x15,(SMFControl.Fan1Type << 2) | 0x80); //Bank 0 Index 0x15        
        WriteValueWithIO(SaveState, 0, 0x60, SMFControl.Fan1TempOffLimit); //Bank 0 Index 0x60 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0x61, SMFControl.Fan1TempStartLimit); //Bank 0 Index 0x61 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0x62, SMFControl.Fan1TempFullSpeedLimit); //Bank 0 Index 0x62 Temperature Limit of full speed
        if(SMFControl.Fan1Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x15, &TempData);
            TempData &= 0xC7;
            WriteValueWithIO(SaveState, 0, 0x15, (SMFControl.Fan1Tempin << 3) | TempData); //Bank 0 Index 0x15[5-3]
            SMFControl.Fan1StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0x63, (UINT8)SMFControl.Fan1StartLimit); //Bank 0 Index 0x63 Minumum(RPM)
            SMFControl.Fan1Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0x64, (UINT8)SMFControl.Fan1Slope | 0x80); //Bank 0 Index 0x64 Slope(RPM)
            SMFControl.Fan1TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0x66, SMFControl.Fan1TargetZone); //Bank 0 Index 0x66 Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0x63, (UINT8)SMFControl.Fan1StartLimit); //Bank 0 Index 0x63 Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0x64, (UINT8)SMFControl.Fan1Slope | 0x80); //Bank 0 Index 0x64 Slope
        }        
        GetValueWithIO(0, 0x65, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0x65, TempData | SMFControl.Fan1TempInterval); //Bank 0 Index 0x65[4-0]
        GetValueWithIO(2, 0x5D, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x5D, TempData | SMFControl.Fan1Smooth); //Bank 2 Index 0x5D[5-0]
        //Curves count(Min: 1, Max: 4)
        SMFControl.Fan1CurveCount --;
        if(SMFControl.Fan1CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x10, SMFControl.Fan1ExtraAStartLimit); //Bank 2 Index 0x10
        //Temperature Input
        GetValueWithIO(2, 0x12, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x12, TempData | (SMFControl.Fan1ExtraATempIn << 5)); //Bank 2 Index 0x12[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan1ExtraASlopeType)
            SMFControl.Fan1ExtraASlopeType = 0x80;
        SMFControl.Fan1ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x13, SMFControl.Fan1ExtraASlopeType | SMFControl.Fan1ExtraARange); //Bank 2 Index 0x13
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan1Type == 1) {
            SMFControl.Fan1ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x11, (UINT8)SMFControl.Fan1ExtraASlope | 0x80); //Bank 2 Index 0x11(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x11, (UINT8)SMFControl.Fan1ExtraASlope | 0x80); //Bank 2 Index 0x11(PWM)
        SMFControl.Fan1CurveCount --;
        if(SMFControl.Fan1CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x14, SMFControl.Fan1ExtraBStartLimit); //Bank 2 Index 0x14
        //Temperature Input
        GetValueWithIO(2, 0x16, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x16, TempData | SMFControl.Fan1ExtraBTempIn); //Bank 2 Index 0x16[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan1ExtraBSlopeType &= 0x80;
        SMFControl.Fan1ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x17, SMFControl.Fan1ExtraBSlopeType | SMFControl.Fan1ExtraBRange); //Bank 2 Index 0x17
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x15, SMFControl.Fan1ExtraBSlope | 0x80); //Bank 2 Index 0x15
        SMFControl.Fan1CurveCount --;
        if(SMFControl.Fan1CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x18, SMFControl.Fan1ExtraCStartLimit); //Bank 2 Index 0x18
        //Temperature Input
        GetValueWithIO(2, 0x1A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x1A, TempData | SMFControl.Fan1ExtraCTempIn); //Bank 2 Index 0x1A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan1ExtraBSlopeType &= 0x80;
        SMFControl.Fan1ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x1B, SMFControl.Fan1ExtraCSlopeType | SMFControl.Fan1ExtraCRange); //Bank 2 Index 0x1B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x19, SMFControl.Fan1ExtraCSlope | 0x80); //Bank 2 Index 0x19
        break;
    }

//Fan 2 setting
    switch (SMFControl.Fan2SmartMode) {
    case 0://Software Mode
        //Index 16h[7] = 0
        GetValueWithIO(0, 0x16, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x16, TempData); //Bank 0 Index 0x16[7]
        WriteValueWithIO(SaveState, 0, 0x6B, SMFControl.Fan2PwmControl); //Bank 0 Index 0x6B PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 16h[7] = 1
        //Curves count(Min: 1, Max: 4)        
        //Fan type & mode
        WriteValueWithIO(SaveState, 0, 0x16, (SMFControl.Fan2Type << 2) | 0x80); //Bank 0 Index 0x16[2]&[7]
        WriteValueWithIO(SaveState, 0, 0x68, SMFControl.Fan2TempOffLimit); //Bank 0 Index 0x68 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0x69, SMFControl.Fan2TempStartLimit); //Bank 0 Index 0x69 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0x6A, SMFControl.Fan2TempFullSpeedLimit); //Bank 0 Index 0x6A Temperature Limit of full speed
        if(SMFControl.Fan2Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x16, &TempData);
            TempData &= 0xC7;            
            WriteValueWithIO(SaveState, 0, 0x16, (SMFControl.Fan2Tempin << 3) | TempData); //Bank 0 Index 0x16[5-3]
            SMFControl.Fan2StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0x6B, (UINT8)SMFControl.Fan2StartLimit); //Bank 0 Index 0x6B Minumum(RPM)
            SMFControl.Fan2Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0x6C, (UINT8)SMFControl.Fan2Slope | 0x80); //Bank 0 Index 0x6C Slope(RPM)
            SMFControl.Fan2TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0x6E, SMFControl.Fan2TargetZone); //Bank 0 Index 0x6E Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0x6B, (UINT8)SMFControl.Fan2StartLimit); //Bank 0 Index 0x6B Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0x6C, (UINT8)SMFControl.Fan2Slope | 0x80); //Bank 0 Index 0x6C Slope
        }        
        GetValueWithIO(0, 0x6D, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0x6D, TempData | SMFControl.Fan2TempInterval); //Bank 0 Index 0x6D[4-0]
        GetValueWithIO(2, 0x5E, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x5E, TempData | SMFControl.Fan2Smooth); //Bank 2 Index 0x5E[5-0]
        SMFControl.Fan2CurveCount --;
        if(SMFControl.Fan2CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x20, SMFControl.Fan2ExtraAStartLimit); //Bank 2 Index 0x20
        //Temperature Input
        GetValueWithIO(2, 0x22, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x22, TempData | (SMFControl.Fan2ExtraATempIn << 5)); //Bank 2 Index 0x22[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan2ExtraASlopeType)
            SMFControl.Fan2ExtraASlopeType = 0x80;
        SMFControl.Fan2ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x23, SMFControl.Fan2ExtraASlopeType | SMFControl.Fan2ExtraARange); //Bank 2 Index 0x23
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan2Type == 1) {
            SMFControl.Fan2ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x21, (UINT8)SMFControl.Fan2ExtraASlope | 0x80); //Bank 2 Index 0x21(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x21, (UINT8)SMFControl.Fan2ExtraASlope | 0x80); //Bank 2 Index 0x21(PWM)
        SMFControl.Fan2CurveCount --;
        if(SMFControl.Fan2CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x24, SMFControl.Fan2ExtraBStartLimit); //Bank 2 Index 0x24
        //Temperature Input
        GetValueWithIO(2, 0x26, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x26, TempData | SMFControl.Fan2ExtraBTempIn); //Bank 2 Index 0x26[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan2ExtraBSlopeType &= 0x80;
        SMFControl.Fan2ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x27, SMFControl.Fan2ExtraBSlopeType | SMFControl.Fan2ExtraBRange); //Bank 2 Index 0x27
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x25, SMFControl.Fan2ExtraBSlope | 0x80); //Bank 2 Index 0x25
        SMFControl.Fan2CurveCount --;
        if(SMFControl.Fan2CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x28, SMFControl.Fan2ExtraCStartLimit); //Bank 2 Index 0x28
        //Temperature Input
        GetValueWithIO(2, 0x2A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x2A, TempData | SMFControl.Fan2ExtraCTempIn); //Bank 2 Index 0x2A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan2ExtraBSlopeType &= 0x80;
        SMFControl.Fan2ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x2B, SMFControl.Fan2ExtraCSlopeType | SMFControl.Fan2ExtraCRange); //Bank 2 Index 0x2B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x29, SMFControl.Fan2ExtraCSlope | 0x80); //Bank 2 Index 0x29
        break;
    }

//Fan 3 setting
    switch (SMFControl.Fan3SmartMode) {
    case 0://Software Mode
        //Index 17h[7] = 0
        GetValueWithIO(0, 0x17, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x17, TempData); //Bank 0 Index 0x17[7]
        WriteValueWithIO(SaveState, 0, 0x73, SMFControl.Fan3PwmControl); //Bank 0 Index 0x73 PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 17h[7] = 1
        //Curves count(Min: 1, Max: 4)
        //Fan type & mode
        WriteValueWithIO(SaveState, 0, 0x17, (SMFControl.Fan3Type << 2) | 0x80); //Bank 0 Index 0x17[2]&[7]
        WriteValueWithIO(SaveState, 0, 0x70, SMFControl.Fan3TempOffLimit); //Bank 0 Index 0x70 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0x69, SMFControl.Fan3TempStartLimit); //Bank 0 Index 0x69 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0x72, SMFControl.Fan3TempFullSpeedLimit); //Bank 0 Index 0x72 Temperature Limit of full speed
        if(SMFControl.Fan3Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x17, &TempData);
            TempData &= 0xC7;            
            WriteValueWithIO(SaveState, 0, 0x17, (SMFControl.Fan3Tempin << 3) | TempData); //Bank 0 Index 0x17[5-3]
            SMFControl.Fan3StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0x73, (UINT8)SMFControl.Fan3StartLimit); //Bank 0 Index 0x73 Minumum(RPM)
            SMFControl.Fan3Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0x74, (UINT8)SMFControl.Fan3Slope | 0x80); //Bank 0 Index 0x74 Slope(RPM)
            SMFControl.Fan3TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0x76, SMFControl.Fan3TargetZone); //Bank 0 Index 0x76 Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0x73, (UINT8)SMFControl.Fan3StartLimit); //Bank 0 Index 0x73 Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0x74, (UINT8)SMFControl.Fan3Slope | 0x80); //Bank 0 Index 0x74 Slope
        }        
        GetValueWithIO(0, 0x75, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0x75, TempData | SMFControl.Fan3TempInterval); //Bank 0 Index 0x75[4-0]
        GetValueWithIO(2, 0x5F, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x5F, TempData | SMFControl.Fan3Smooth); //Bank 2 Index 0x5F[5-0]
        SMFControl.Fan3CurveCount --;
        if(SMFControl.Fan3CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x30, SMFControl.Fan3ExtraAStartLimit); //Bank 2 Index 0x30
        //Temperature Input
        GetValueWithIO(2, 0x32, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x32, TempData | (SMFControl.Fan3ExtraATempIn << 5)); //Bank 2 Index 0x32[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan3ExtraASlopeType)
            SMFControl.Fan3ExtraASlopeType = 0x80;
        SMFControl.Fan3ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x33, SMFControl.Fan3ExtraASlopeType | SMFControl.Fan3ExtraARange); //Bank 2 Index 0x33
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan3Type == 1) {
            SMFControl.Fan3ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x31, (UINT8)SMFControl.Fan3ExtraASlope | 0x80); //Bank 2 Index 0x31(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x31, (UINT8)SMFControl.Fan3ExtraASlope | 0x80); //Bank 2 Index 0x31(PWM)
        SMFControl.Fan3CurveCount --;
        if(SMFControl.Fan3CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x34, SMFControl.Fan3ExtraBStartLimit); //Bank 2 Index 0x34
        //Temperature Input
        GetValueWithIO(2, 0x36, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x36, TempData | SMFControl.Fan3ExtraBTempIn); //Bank 2 Index 0x36[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan3ExtraBSlopeType &= 0x80;
        SMFControl.Fan3ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x37, SMFControl.Fan3ExtraBSlopeType | SMFControl.Fan3ExtraBRange); //Bank 2 Index 0x37
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x35, SMFControl.Fan3ExtraBSlope | 0x80); //Bank 2 Index 0x35
        SMFControl.Fan3CurveCount --;
        if(SMFControl.Fan3CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x38, SMFControl.Fan3ExtraCStartLimit); //Bank 2 Index 0x38
        //Temperature Input
        GetValueWithIO(2, 0x3A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x3A, TempData | SMFControl.Fan3ExtraCTempIn); //Bank 2 Index 0x3A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan3ExtraBSlopeType &= 0x80;
        SMFControl.Fan3ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x3B, SMFControl.Fan3ExtraCSlopeType | SMFControl.Fan3ExtraCRange); //Bank 2 Index 0x3B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x39, SMFControl.Fan3ExtraCSlope | 0x80); //Bank 2 Index 0x39
        break;
    }

//Fan 4 setting
    switch (SMFControl.Fan4SmartMode) {
    case 0://Software Mode
        //Index 15h[7] = 0
        GetValueWithIO(0, 0x1E, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x1E, TempData); //Bank 0 Index 0x1E
        WriteValueWithIO(SaveState, 0, 0x7B, SMFControl.Fan4PwmControl); //Bank 0 Index 0x7B PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 15h[7] = 1
        //Curves count(Min: 1, Max: 4)
        //Fan type & mode            
        WriteValueWithIO(SaveState, 0, 0x1E, (SMFControl.Fan4Type << 2) | 0x80); //Bank 0 Index 0x1E[2]&[7]
        WriteValueWithIO(SaveState, 0, 0x78, SMFControl.Fan4TempOffLimit); //Bank 0 Index 0x78 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0x79, SMFControl.Fan4TempStartLimit); //Bank 0 Index 0x79 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0x7A, SMFControl.Fan4TempFullSpeedLimit); //Bank 0 Index 0x7A Temperature Limit of full speed
        if(SMFControl.Fan4Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x1E, &TempData);
            TempData &= 0xC7;            
            WriteValueWithIO(SaveState, 0, 0x1E, (SMFControl.Fan4Tempin << 3) | TempData); //Bank 0 Index 0x1E[5-3]
            SMFControl.Fan4StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0x7B, (UINT8)SMFControl.Fan4StartLimit); //Bank 0 Index 0x7B Minumum(RPM)
            SMFControl.Fan4Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0x7C, (UINT8)SMFControl.Fan4Slope | 0x80); //Bank 0 Index 0x7C Slope(RPM)
            SMFControl.Fan4TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0x7E, SMFControl.Fan4TargetZone); //Bank 0 Index 0x7E Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0x7B, (UINT8)SMFControl.Fan4StartLimit); //Bank 0 Index 0x7B Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0x7C, (UINT8)SMFControl.Fan4Slope | 0x80); //Bank 0 Index 0x7C Slope
        }        
        GetValueWithIO(0, 0x7D, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0x7D, TempData | SMFControl.Fan4TempInterval); //Bank 0 Index 0x7D[4-0]
        GetValueWithIO(2, 0x6D, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x6D, TempData | SMFControl.Fan4Smooth); //Bank 2 Index 0x6D[5-0]
        SMFControl.Fan4CurveCount --;
        if(SMFControl.Fan4CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x40, SMFControl.Fan4ExtraAStartLimit); //Bank 2 Index 0x40
        //Temperature Input
        GetValueWithIO(2, 0x42, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x42, TempData | (SMFControl.Fan4ExtraATempIn << 5)); //Bank 2 Index 0x42[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan4ExtraASlopeType)
            SMFControl.Fan4ExtraASlopeType = 0x80;
        SMFControl.Fan4ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x43, SMFControl.Fan4ExtraASlopeType | SMFControl.Fan4ExtraARange); //Bank 2 Index 0x43
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan4Type == 1) {
            SMFControl.Fan4ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x41, (UINT8)SMFControl.Fan4ExtraASlope | 0x80); //Bank 2 Index 0x41(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x41, (UINT8)SMFControl.Fan4ExtraASlope | 0x80); //Bank 2 Index 0x41(PWM)
        SMFControl.Fan4CurveCount --;
        if(SMFControl.Fan4CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x44, SMFControl.Fan4ExtraBStartLimit); //Bank 2 Index 0x44
        //Temperature Input
        GetValueWithIO(2, 0x46, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x46, TempData | SMFControl.Fan4ExtraBTempIn); //Bank 2 Index 0x46[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan4ExtraBSlopeType &= 0x80;
        SMFControl.Fan4ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x47, SMFControl.Fan4ExtraBSlopeType | SMFControl.Fan4ExtraBRange); //Bank 2 Index 0x47
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x45, SMFControl.Fan4ExtraBSlope | 0x80); //Bank 2 Index 0x45
        SMFControl.Fan4CurveCount --;
        if(SMFControl.Fan4CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x48, SMFControl.Fan4ExtraCStartLimit); //Bank 2 Index 0x48
        //Temperature Input
        GetValueWithIO(2, 0x4A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x4A, TempData | SMFControl.Fan4ExtraCTempIn); //Bank 2 Index 0x4A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan4ExtraBSlopeType &= 0x80;
        SMFControl.Fan4ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x4B, SMFControl.Fan4ExtraCSlopeType | SMFControl.Fan4ExtraCRange); //Bank 2 Index 0x4B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x49, SMFControl.Fan4ExtraCSlope | 0x80); //Bank 2 Index 0x49
        break;
    }

    //Fan 5 setting
    switch (SMFControl.Fan5SmartMode) {
    case 0://Software Mode
        //Index 1Fh[7] = 0
        GetValueWithIO(0, 0x1F, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x1F, TempData); //Bank 0 Index 0x1F
        WriteValueWithIO(SaveState, 0, 0xA3, SMFControl.Fan5PwmControl); //Bank 0 Index 0xA3 PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 15h[7] = 1
        //Curves count(Min: 1, Max: 4)
        //Fan type & mode
        WriteValueWithIO(SaveState, 0, 0x1F, (SMFControl.Fan5Type << 2) | 0x80); //Bank 0 Index 0x1F[2]&[7]
        WriteValueWithIO(SaveState, 0, 0xA0, SMFControl.Fan5TempOffLimit); //Bank 0 Index 0xA0 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0xA1, SMFControl.Fan5TempStartLimit); //Bank 0 Index 0xA1 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0xA2, SMFControl.Fan5TempFullSpeedLimit); //Bank 0 Index 0xA2 Temperature Limit of full speed
        if(SMFControl.Fan5Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x1F, &TempData);
            TempData &= 0xC7;            
            WriteValueWithIO(SaveState, 0, 0x1F, (SMFControl.Fan5Tempin << 3) | TempData); //Bank 0 Index 0x1F[5-3]
            SMFControl.Fan5StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0xA3, (UINT8)SMFControl.Fan5StartLimit); //Bank 0 Index 0xA3 Minumum(RPM)
            SMFControl.Fan5Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0xA4, (UINT8)SMFControl.Fan5Slope | 0x80); //Bank 0 Index 0xA4 Slope(RPM)
            SMFControl.Fan5TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0xA6, SMFControl.Fan5TargetZone); //Bank 0 Index 0xA6 Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0xA3, (UINT8)SMFControl.Fan5StartLimit); //Bank 0 Index 0xA3 Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0xA4, (UINT8)SMFControl.Fan5Slope | 0x80); //Bank 0 Index 0xA4 Slope
        }        
        GetValueWithIO(0, 0xA5, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0xA5, TempData | SMFControl.Fan5TempInterval); //Bank 0 Index 0xA5[4-0]
        GetValueWithIO(2, 0x6E, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x6E, TempData | SMFControl.Fan5Smooth); //Bank 2 Index 0x6E[5-0]
        SMFControl.Fan5CurveCount --;
        if(SMFControl.Fan5CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x50, SMFControl.Fan5ExtraAStartLimit); //Bank 2 Index 0x50
        //Temperature Input
        GetValueWithIO(2, 0x52, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x52, TempData | (SMFControl.Fan5ExtraATempIn << 5)); //Bank 2 Index 0x52[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan5ExtraASlopeType)
            SMFControl.Fan5ExtraASlopeType = 0x80;
        SMFControl.Fan5ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x53, SMFControl.Fan5ExtraASlopeType | SMFControl.Fan5ExtraARange); //Bank 2 Index 0x53
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan5Type == 1) {
            SMFControl.Fan5ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x51, (UINT8)SMFControl.Fan5ExtraASlope | 0x80); //Bank 2 Index 0x51(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x51, (UINT8)SMFControl.Fan5ExtraASlope | 0x80); //Bank 2 Index 0x51(PWM)
        SMFControl.Fan5CurveCount --;
        if(SMFControl.Fan5CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x54, SMFControl.Fan5ExtraBStartLimit); //Bank 2 Index 0x54
        //Temperature Input
        GetValueWithIO(2, 0x56, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x56, TempData | SMFControl.Fan5ExtraBTempIn); //Bank 2 Index 0x56[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan5ExtraBSlopeType &= 0x80;
        SMFControl.Fan5ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x57, SMFControl.Fan5ExtraBSlopeType | SMFControl.Fan5ExtraBRange); //Bank 2 Index 0x57
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x55, SMFControl.Fan5ExtraBSlope | 0x80); //Bank 2 Index 0x55
        SMFControl.Fan5CurveCount --;
        if(SMFControl.Fan5CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x58, SMFControl.Fan5ExtraCStartLimit); //Bank 2 Index 0x58
        //Temperature Input
        GetValueWithIO(2, 0x5A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x5A, TempData | SMFControl.Fan5ExtraCTempIn); //Bank 2 Index 0x5A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan5ExtraBSlopeType &= 0x80;
        SMFControl.Fan5ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x5B, SMFControl.Fan5ExtraCSlopeType | SMFControl.Fan5ExtraCRange); //Bank 2 Index 0x5B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x59, SMFControl.Fan5ExtraCSlope | 0x80); //Bank 2 Index 0x59
        break;
    }

    //Fan 6 setting
    switch (SMFControl.Fan6SmartMode) {
    case 0://Software Mode
        //Index 92h[7] = 0
        GetValueWithIO(0, 0x92, &TempData);
        TempData &= 0x7F;
        WriteValueWithIO(SaveState, 0, 0x92, TempData); //Bank 0 Index 0x92
        WriteValueWithIO(SaveState, 0, 0xAB, SMFControl.Fan6PwmControl); //Bank 0 Index 0xAB PWM Control value.
        break;
    case 1://Automatic Mode
        //Index 15h[7] = 1
        //Curves count(Min: 1, Max: 4)
        //Fan type & mode            
        WriteValueWithIO(SaveState, 0, 0x92,(SMFControl.Fan6Type << 2) | 0x80); //Bank 0 Index 0x91[2]&[7]        
        WriteValueWithIO(SaveState, 0, 0xA8, SMFControl.Fan6TempOffLimit); //Bank 0 Index 0xA8 Temperature Limit of fan off
        WriteValueWithIO(SaveState, 0, 0xA9, SMFControl.Fan6TempStartLimit); //Bank 0 Index 0xA9 Temperature Limit of fan start(PWM)
        WriteValueWithIO(SaveState, 0, 0xAA, SMFControl.Fan6TempFullSpeedLimit); //Bank 0 Index 0xAA Temperature Limit of full speed
        if(SMFControl.Fan6Type == 1) {
            //Temperature inpute
            GetValueWithIO(0, 0x92, &TempData);
            TempData &= 0xC7;            
            WriteValueWithIO(SaveState, 0, 0x92, (SMFControl.Fan6Tempin << 3) | TempData); //Bank 0 Index 0x92[5-3]
            SMFControl.Fan6StartLimit /= 32;
            WriteValueWithIO(SaveState, 0, 0xAB, (UINT8)SMFControl.Fan6StartLimit); //Bank 0 Index 0xAB Minumum(RPM)
            SMFControl.Fan6Slope /= 8;
            WriteValueWithIO(SaveState, 0, 0xAC, (UINT8)SMFControl.Fan6Slope | 0x80); //Bank 0 Index 0xAC Slope(RPM)
            SMFControl.Fan6TargetZone /= 8;
            WriteValueWithIO(SaveState, 0, 0xAE, SMFControl.Fan6TargetZone); //Bank 0 Index 0xAE Target Zone(RPM)
        }
        else {
            WriteValueWithIO(SaveState, 0, 0xAB, (UINT8)SMFControl.Fan6StartLimit); //Bank 0 Index 0xAB Minumum(PWM)
            WriteValueWithIO(SaveState, 0, 0xAC, (UINT8)SMFControl.Fan6Slope | 0x80); //Bank 0 Index 0xAC Slope
        }        
        GetValueWithIO(0, 0xAD, &TempData);
        TempData &= 0xE0;
        WriteValueWithIO(SaveState, 0, 0xAD, TempData | SMFControl.Fan6TempInterval); //Bank 0 Index 0xAD[4-0]
        GetValueWithIO(2, 0x6F, &TempData);
        TempData &= 0xC0;
        WriteValueWithIO(SaveState, 2, 0x6F, TempData | SMFControl.Fan6Smooth); //Bank 2 Index 0x6F[5-0]
        SMFControl.Fan6CurveCount --;
        if(SMFControl.Fan6CurveCount == 0)
            break;
        //Extra vector A
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x60, SMFControl.Fan6ExtraAStartLimit); //Bank 2 Index 0x60
        //Temperature Input
        GetValueWithIO(2, 0x62, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x62, TempData | (SMFControl.Fan6ExtraATempIn << 5)); //Bank 2 Index 0x62[7-5]
        //Positive/Negative Slope & Range value
        if(SMFControl.Fan6ExtraASlopeType)
            SMFControl.Fan6ExtraASlopeType = 0x80;
        SMFControl.Fan6ExtraARange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x63, SMFControl.Fan6ExtraASlopeType | SMFControl.Fan6ExtraARange); //Bank 2 Index 0x63
        //Slope value & Enable Extra Vector.
        if(SMFControl.Fan6Type == 1) {
            SMFControl.Fan6ExtraASlope /= 8;
            WriteValueWithIO(SaveState, 2, 0x61, (UINT8)SMFControl.Fan6ExtraASlope | 0x80); //Bank 2 Index 0x61(RPM)
        }
        else
            WriteValueWithIO(SaveState, 2, 0x61, (UINT8)SMFControl.Fan6ExtraASlope | 0x80); //Bank 2 Index 0x61(PWM)
        SMFControl.Fan6CurveCount --;
        if(SMFControl.Fan6CurveCount == 0)
            break;
        //Extra vector B        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x64, SMFControl.Fan6ExtraBStartLimit); //Bank 2 Index 0x64
        //Temperature Input
        GetValueWithIO(2, 0x66, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x66, TempData | SMFControl.Fan6ExtraBTempIn); //Bank 2 Index 0x66[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan6ExtraBSlopeType &= 0x80;
        SMFControl.Fan6ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x67, SMFControl.Fan6ExtraBSlopeType | SMFControl.Fan6ExtraBRange); //Bank 2 Index 0x67
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x65, SMFControl.Fan6ExtraBSlope | 0x80); //Bank 2 Index 0x65
        SMFControl.Fan6CurveCount --;
        if(SMFControl.Fan6CurveCount == 0)
            break;
        //Extra vector C        
        //START Limit
        WriteValueWithIO(SaveState, 2, 0x68, SMFControl.Fan6ExtraCStartLimit); //Bank 2 Index 0x68
        //Temperature Input
        GetValueWithIO(2, 0x6A, &TempData);
        TempData &= 0x1F;
        WriteValueWithIO(SaveState, 2, 0x6A, TempData | SMFControl.Fan6ExtraCTempIn); //Bank 2 Index 0x6A[7-5]
        //Positive/Negative Slope & Range value
        SMFControl.Fan6ExtraBSlopeType &= 0x80;
        SMFControl.Fan6ExtraBRange &= 0x7F;
        WriteValueWithIO(SaveState, 2, 0x6B, SMFControl.Fan6ExtraCSlopeType | SMFControl.Fan6ExtraCRange); //Bank 2 Index 0x6B
        //Slope value & Enable Extra Vector.
        WriteValueWithIO(SaveState, 2, 0x69, SMFControl.Fan6ExtraCSlope | 0x80); //Bank 2 Index 0x69
        break;
    }
}
*/ // << AAEON_OVERRIDE --
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
EFI_STATUS IT8625_COM_Init(
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
// AAEON_OVERRIDE -     UINT8                           rv; //ComMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            IT8625_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
// >> 2020/05/18 AAEON_OVERRIDE
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
//        //Program COM RS485/RS232 Mode And Clock Source Registers.
//        if(IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//            rv=IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8;
//            rv |= IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,IT8625_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
// << 2020/05/18 AAEON_OVERRIDE
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
  This function provide LPT initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
EFI_STATUS IT8625_LPT_Init(
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
            IT8625_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        //depend on LPT Mode it may or may not use a DMA channel
        //Strcpy(&Dev->DeviceInfo->AslName[0],"LPTE");
        //EFI_DEADLOOP();
        if(Dev->NvData.DevMode&0x02) { //4 mode
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT
                //last parameter is 0-based index in IT8625_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"EPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function setting
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, TRUE);
            }
            //Change HID value in DXE phase for correct devcie path.
            Dev->EisaId.HID = 0x40141D0;
        } else {
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"LPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function setting
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, FALSE);
            }
        }
        ASSERT_EFI_ERROR(Status);
        break;

    case isBeforeActivate:
// >> 2020/05/18 AAEON_OVERRIDE
//        //Decode?
//        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
//        } else {
//            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
//        }
// << 2020/05/18 AAEON_OVERRIDE
        //Program Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        //Program Lpt Mode register following SIO Specification instructions.
        //Set mode:Bit1-0 set = LPT mode
        //clear lowest 3 bits where LPT mode is:
        rv&=0xFC;
        switch (Dev->NvData.DevMode) {
                case 0:    rv|=0; //Standard Parallel Port mode(SPP)
                    break;
                case 1:    rv|=1; //EPP Mode
                    break;
                case 2:    rv|=2; //ECP Mode
                    break;
                case 3:    rv|=3; //EPP mode & ECP mode
                    break;
            default: return EFI_INVALID_PARAMETER;
        }
        //Program back Device Mode register
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
        //LPT Has 4 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        static CHAR16 LptModeStr1[] = L"Standard Parallel Port mode(SPP)";
        static CHAR16 LptModeStr2[] = L"EPP Mode";
        static CHAR16 LptModeStr3[] = L"ECP Mode";
        static CHAR16 LptModeStr4[] = L"EPP mode & ECP mode";
        static CHAR16 LptModeHelp[] = L"Change Parallel Port mode. Some of the Modes required a DMA resource. After Mode changing, Reset the System to reflect actual device settings.";
        //---------------------------------------------------
        Dev->DevModeCnt=4;
        //Make room for 2 PRT modes + Help String...
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
        Dev->DevModeStr[4]=&LptModeHelp[0];
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

/**
  This function provide KBC initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
EFI_STATUS IT8625_KBC_Init(
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
// >> 2020/05/18 AAEON_OVERRIDE
//        //Decode
//        AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
// << 2020/05/18 AAEON_OVERRIDE
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

/**
  This function provide HWM initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
EFI_STATUS IT8625_HWM_Init(
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
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_ENV_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(IT8625_CONFIG_INDEX, IT8625_CONFIG_DATA,\
                                DXE_ENV_Init_Table_Before_Active,DXE_ENV_Init_Table_Before_Active_Count);
        break;

    case isAfterActivate:
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(IT8625_HWM_INDEX_PORT, IT8625_HWM_DATA_PORT,\
                                DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count);
        // AAEON_OVERRIDE - ProgramSmartFan(NULL, FALSE);
        break;

    case isAfterBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
    	BootScriptProtocol=(EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;
        SioLib_BootScriptSioS3SaveTable(IT8625_HWM_INDEX_PORT, IT8625_HWM_DATA_PORT, \
                                        DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count, BootScriptProtocol);
        // AAEON_OVERRIDE - ProgramSmartFan(BootScriptProtocol, FALSE);
        break;
#if  AMI_SIO_MINOR_VERSION >= 6    	
    case isAfterSmmBootScript:  
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
    	BootScriptProtocol=(EFI_S3_SMM_SAVE_STATE_PROTOCOL*)Args->Param3;
    	//If No Bank exist in HWM Config register.
        SioLib_BootScriptSioS3SaveTable(IT8625_HWM_INDEX_PORT, IT8625_HWM_DATA_PORT, 
                                        DXE_HWM_Init_Table_After_Active,DXE_HWM_Init_Table_After_Active_Count,BootScriptProtocol);
        // AAEON_OVERRIDE - ProgramSmartFan(BootScriptProtocol, TRUE);
        break;
#endif    
    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

/**
  This function provide GPIO initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
EFI_STATUS IT8625_GPIO_Init(
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
        break;

    case isAfterActivate:
        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(IT8625_CONFIG_INDEX, IT8625_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count);
#if  AMI_SIO_MINOR_VERSION < 6 
        //Create event for boot script
        //Because Gpio is not standard device which have no activate reg0x30,so create event to save regs
        Status = CreateReadyToBootEvent(
                     TPL_NOTIFY,
                     IT8625_GpioCallbackReadyToBoot,
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
        SioLib_BootScriptSioS3SaveTable(IT8625_CONFIG_INDEX, IT8625_CONFIG_DATA, \
                                    DXE_GPIO_Init_Table_After_Active,DXE_GPIO_Init_Table_After_Active_Count, BootScriptProtocol);
        break;
#endif    
    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}

/**
  This function provide CIR initial routine in GenericSio.c

  @param  This                      AMI board initial protocol.
  @param  Function                  AMI sdl SIO initial routine.
  @param  ParameterBlock            SIO component initial routine parameters block...

  @retval  EFI_SUCCESS              Initial step sucessfully.
  @retval  EFI_INVALID_PARAMETER    Not find the initial step.
**/
EFI_STATUS IT8625_CIR_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock )
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
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            IT8625_ClearDevResource(Dev);
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
