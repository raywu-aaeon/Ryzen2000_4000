//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
//<AMI_FHDR_START>
//
// Name:  <W83627DHGSetup.c>
//
// Description: GUID or structure Of Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Token.h>
#if W83627DHG_SmartFan_SUPPORT
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "W83627DHGSMF.h"
//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
#define HWM_CONFIG_INDEX        W83627DHG_HWM_BASE_ADDRESS+05
#define HWM_CONFIG_DATA         W83627DHG_HWM_BASE_ADDRESS+06
static SETUP_DATA                      SetupData;
static EFI_EVENT                gEvtReadyToBoot = NULL;
static EFI_GUID                 gEfiBootScriptSaveGuid = EFI_S3_SAVE_STATE_PROTOCOL_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     AccessHwmWithIO
//
// Description: Write the defined value to HWM space register.
//
// Input:     UINT8   Register        -> Register who content the wanted value
//            UINTN   *Value          -> Register value
//
// Output:     NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AccessHwmWithIO (
    IN UINT8 Register,
    IN UINT8 Value
)
{
    IoWrite8(HWM_CONFIG_INDEX, 0x4E);           //Bank Select
    IoWrite8(HWM_CONFIG_DATA,  0x00);           //Bank 0

    IoWrite8(HWM_CONFIG_INDEX, Register);       //HWM_INDEX
    IoWrite8(HWM_CONFIG_DATA,  Value);          //HWM_DATA
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     ReadHwmWithIO
//
// Description: Read the defined value to HWM space register.
//
// Input:     UINT8   Register        -> Register who content the wanted value
//
//
// Output:     NULL
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReadHwmWithIO (
    IN UINT8 Register
)
{
    IoWrite8(HWM_CONFIG_INDEX, 0x4E);           //Bank Select
    IoWrite8(HWM_CONFIG_DATA,  0x00);           //Bank 0

    IoWrite8(HWM_CONFIG_INDEX, Register);       //HWM_INDEX
    return IoRead8(HWM_CONFIG_DATA);            //HWM_DATA
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    InitSmartFan1
//
// Description:    This function initializes the smart fan function of SYSFANOUT
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitSmartFan1(VOID)
{
    UINT8       Val;

    Val = ReadHwmWithIO(0x04);
    
    switch (SetupData.SysSmartFanMode) {
        case 0 :    //SYSFANOUT Manual Mode
            AccessHwmWithIO(0x04, (Val & 0xF3));

            AccessHwmWithIO(0x01, SetupData.SysFanOutValue);                    //Set SYSFANOUT VALUE
            break;
        case 1 :    //SYSFANOUT Thermal CruiseTM Mode
            AccessHwmWithIO(0x04, (Val | 0x04));

            AccessHwmWithIO(0x05, SetupData.SysFanOfTarTemp);                   //Set SYSTIN Target Temperature 
            AccessHwmWithIO(0x07, SetupData.SysTolOfTarTemp);                   //Set Tolerance of SYSTIN Target Temperature

            #if SYSFANOUT_MIN_VALUE
            AccessHwmWithIO(0x08, SYSFAN_STOP_VALUE);                           //Set Value of SYSFANOUT Stop Value Register
            #endif
            AccessHwmWithIO(0x0A, SYSFAN_START_UP_VALUE);                       //Set Value of SYSFANOUT Start-up Value Register
            AccessHwmWithIO(0x0C, SYSFAN_STOP_TIME_VALUE);                      //Set Value of SYSFANOUT Stop Time Register
            break;
        case 2 :    //SYSFANOUT Fan Speed CruiseTM Mode
            AccessHwmWithIO(0x04, (Val | 0x08));

            AccessHwmWithIO(0x05, SetupData.SysFanOfTarSpeed);                  //Set SYSFANIN Target Speed
            AccessHwmWithIO(0x07, SetupData.SysTolOfTarSpeed);                  //Set Tolerance of SYSFANIN Target Speed
            break;
        default :
            break;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    InitSmartFan2
//
// Description:    This function initializes the smart fan function of CPUFANOUT0
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitSmartFan2(VOID)
{
    UINT8       Val;

    Val = ReadHwmWithIO(0x04);
    
    switch (SetupData.CPUSmartFan0Mode) {
        case 0 :    //CPUFANOUT0 Manual Mode
            AccessHwmWithIO(0x04, (Val & 0xCF));

            AccessHwmWithIO(0x03, SetupData.CPUFan0OutValue);                   //Set CPUFANOUT0 VALUE
            break;
        case 1 :    //CPUFANOUT0 Thermal CruiseTM Mode
            AccessHwmWithIO(0x04, (Val | 0x10));

            Val = ReadHwmWithIO(0x07);

            AccessHwmWithIO(0x06, SetupData.CPUFan0OfTarTemp);                  //Set CPUTIN Target Temperature 
            AccessHwmWithIO(0x07, Val | (SetupData.CPUTol0OfTarTemp << 4));     //Set Tolerance of CPUTIN Target Temperature

            #if CPUFANOUT0_MIN_VALUE
            AccessHwmWithIO(0x09, CPUFAN0_STOP_VALUE);                          //Set Value of CPUFANOUT0 Stop Value Register
            #endif
            AccessHwmWithIO(0x0B, CPUFAN0_START_UP_VALUE);                      //Set Value of CPUFANOUT0 Start-up Value Register
            AccessHwmWithIO(0x0D, CPUFAN0_STOP_TIME_VALUE);                     //Set Value of CPUFANOUT0 Stop Time Register
            break;
        case 2 :    //CPUFANOUT0 Fan Speed CruiseTM Mode
            AccessHwmWithIO(0x04, (Val | 0x20));

            Val = ReadHwmWithIO(0x07);

            AccessHwmWithIO(0x06, SetupData.CPUFan0OfTarSpeed);                 //Set CPUFANOUT0 Target Speed
            AccessHwmWithIO(0x07, Val | (SetupData.CPUTol0OfTarSpeed << 4));    //Set Tolerance of CPUFANOUT0 Target Speed
            break;
        case 3 :    //CPUFANOUT0 SMART FANTM III Mode
            AccessHwmWithIO(0x04, (Val | 0x30));

            Val = ReadHwmWithIO(0x07);

            AccessHwmWithIO(0x06, SetupData.CPUFan0OfTarTemp);                  //Set CPUTIN Target Temperature
            AccessHwmWithIO(0x07, Val | (SetupData.CPUTol0OfTarTemp << 4));     //Set Tolerance of CPUTIN Target Temperature

            #if CPUFANOUT0_MIN_VALUE
            AccessHwmWithIO(0x09, CPUFAN0_STOP_VALUE);                          //Set Value of CPUFANOUT0 Stop Value Register
            #endif
            AccessHwmWithIO(0x0D, CPUFAN0_STOP_TIME_VALUE);                     //Set Value of CPUFANOUT0 Stop Time Register
            AccessHwmWithIO(0x67, CPUFAN0_MAX_OUTPUT_VALUE);                    //Set Value of CPUFANOUT0 Maximum Output Value Register
            AccessHwmWithIO(0x68, CPUFAN0_OUTPUT_STEP_VALUE);                   //Set Value of CPUFANOUT0 Output Step Value Register
            break;
        default :
            break;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    InitSmartFan3
//
// Description:    This function initializes the smart fan function of AUXFANOUT
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitSmartFan3(VOID)
{
    UINT8       Val;

    Val = ReadHwmWithIO(0x12);
    
    switch (SetupData.AuxSmartFanMode) {
        case 0 :    //AUXFANOUT Manual Mode
            AccessHwmWithIO(0x12, (Val & 0xFD));

            AccessHwmWithIO(0x11, SetupData.AuxFanOutValue);                    //Set AUXFANOUT VALUE
            break;
        case 1 :    //AUXFANOUT Thermal CruiseTM Mode
            AccessHwmWithIO(0x12, (Val | 0x02));

            AccessHwmWithIO(0x13, SetupData.AuxFanOfTarTemp);                   //Set AUXTIN Target Temperature 
            AccessHwmWithIO(0x14, SetupData.AuxTolOfTarTemp);                    //Set Tolerance of AUXTIN Target Temperature

            #if AUXFANOUT_MIN_VALUE
            AccessHwmWithIO(0x15, AUXFAN_STOP_VALUE);                           //Set Value of AUXFANOUT Stop Value Register
            #endif
            AccessHwmWithIO(0x16, AUXFAN_START_UP_VALUE);                       //Set Value of AUXFANOUT Start-up Value Register
            AccessHwmWithIO(0x17, AUXFAN_STOP_TIME_VALUE);                      //Set Value of AUXFANOUT Stop Time Register
            break;
        case 2 :    //AUXFANOUT Fan Speed CruiseTM Mode
            AccessHwmWithIO(0x12, (Val | 0x04));

            AccessHwmWithIO(0x13, SetupData.AuxFanOfTarSpeed);                  //Set AUXFANIN0 Target Speed
            AccessHwmWithIO(0x14, SetupData.AuxTolOfTarSpeed);                  //Set Tolerance of AUXFANIN0 Target Speed
            break;
        default :
            break;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    InitSmartFan4
//
// Description:    This function initializes the smart fan function of CPUFANOUT1
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitSmartFan4(VOID)
{
    UINT8       Val;

    Val = ReadHwmWithIO(0x62);
    
    switch (SetupData.CPUSmartFan1Mode) {
        case 0 :    //CPUFANOUT1 Manual Mode
            AccessHwmWithIO(0x62, (Val & 0xCF));

            AccessHwmWithIO(0x61, SetupData.CPUFan1OutValue);                   //Set CPUFANOUT1 VALUE
            break;
        case 1 :    //CPUFANOUT1 Thermal CruiseTM Mode
            AccessHwmWithIO(0x62, (Val | 0x10));

            Val = ReadHwmWithIO(0x62) & 0xF0;

            AccessHwmWithIO(0x63, SetupData.CPUFan1OfTarTemp);                  //Set CPUTIN Target Temperature 
            AccessHwmWithIO(0x62, SetupData.CPUTol1OfTarTemp | Val);            //Set Tolerance of CPUTIN Target Temperature

            #if (CPUFANOUT1_MIN_VALUE == 1)
            AccessHwmWithIO(0x64, CPUFAN1_STOP_VALUE);                          //Set Value of CPUFANOUT1 Stop Value Register
            #endif
            AccessHwmWithIO(0x65, CPUFAN1_START_UP_VALUE);                      //Set Value of CPUFANOUT1 Start-up Value Register
            AccessHwmWithIO(0x66, CPUFAN1_STOP_TIME_VALUE);                     //Set Value of CPUFANOUT1 Stop Time Register
            break;
        case 2 :    //CPUFANOUT1 Fan Speed CruiseTM Mode
            AccessHwmWithIO(0x62, (Val | 0x20));

            Val = ReadHwmWithIO(0x62) & 0xF0;

            AccessHwmWithIO(0x63, SetupData.CPUFan1OfTarSpeed);                 //Set CPUFANOUT1 Target Speed
            AccessHwmWithIO(0x62, SetupData.CPUTol1OfTarSpeed | Val);           //Set Tolerance of CPUFANOUT1 Target Speed
            break;
        case 3 :    //CPUFANOUT1 SMART FANTM III Mode
            AccessHwmWithIO(0x62, (Val | 0x30));

            Val = ReadHwmWithIO(0x62) & 0xF0;

            AccessHwmWithIO(0x63, SetupData.CPUFan1OfTarTemp);                  //Set CPUTIN Target Temperature
            AccessHwmWithIO(0x62, SetupData.CPUTol1OfTarTemp | Val);            //Set Tolerance of CPUTIN Target Temperature

            #if (CPUFANOUT1_MIN_VALUE == 1)
            AccessHwmWithIO(0x64, CPUFAN1_STOP_VALUE);                          //Set Value of CPUFANOUT1 Stop Value Register
            #endif
            AccessHwmWithIO(0x66, CPUFAN1_STOP_TIME_VALUE);                     //Set Value of CPUFANOUT1 Stop Time Register
            AccessHwmWithIO(0x69, CPUFAN1_MAX_OUTPUT_VALUE);                    //Set Value of CPUFANOUT1 Maximum Output Value Register
            AccessHwmWithIO(0x6A, CPUFAN1_OUTPUT_STEP_VALUE);                   //Set Value of CPUFANOUT1 Output Step Value Register
            break;
        default :
            break;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    HwmCallbackReadyToBoot
//
// Description:    This function save registers for S3
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS HwmCallbackReadyToBoot(
    IN  EFI_EVENT Event,
    IN  VOID    *Context)
{
    EFI_S3_SAVE_STATE_PROTOCOL *bss;
    EFI_STATUS      Status;
    UINT8           r,v,i;

    Status = pBS->LocateProtocol(&gEfiBootScriptSaveGuid,NULL,&bss);
    if(EFI_ERROR(Status)) return Status;

    // record the register from table into boot script 
    for (i=0; i < ((sizeof(DXE_SMF_SIO_BootScript_Table))/(sizeof(UINT8))); i++) {
        r = DXE_SMF_SIO_BootScript_Table[i];

        //select register
        IoWrite8(HWM_CONFIG_INDEX, r);
        //read actual data
        v = IoRead8(HWM_CONFIG_DATA);

        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_INDEX, 1, &r);
        BOOT_SCRIPT_S3_IO_WRITE_MACRO(bss,EfiBootScriptWidthUint8,HWM_CONFIG_DATA, 1, &v);
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFanFuncStart
//
// Description:    This function start to initialize the smart fan function
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartFanFuncStart(VOID)
{

    EFI_STATUS      Status;

    //--------------------------------------------------------------------------
    // Before speed control, program neccessary registers if needed.
    //--------------------------------------------------------------------------
    AccessHwmWithIO(0x0E, FAN_STEPDOWN_TIME_VALUE);             //Set Value of Fan Output Step Down Time Register
    AccessHwmWithIO(0x0F, FAN_STEPUP_TIME_VALUE);               //Set Value of Fan Output Step Up Time Register
    AccessHwmWithIO(0x12, 0x00 | (CPUFANOUT1_MIN_VALUE << 6) | (SYSFANOUT_MIN_VALUE << 5) | (CPUFANOUT0_MIN_VALUE << 4) | (AUXFANOUT_MIN_VALUE << 3));         //Set Value of FAN minimal value
    AccessHwmWithIO(0x49, 0x00 | ( AUXFANOUT_TEMP_SEL << 3) | CPUFANOUT0_TEMP_SEL);     //Monitor Temperature Source Select Register
    AccessHwmWithIO(0x4A, CPUFANOUT1_TEMP_SEL);                 //Monitor Temperature Source Select Register

    //When reset, clear smart fan mode
    AccessHwmWithIO(0x04, 0x00);
    AccessHwmWithIO(0x62, 0x00);
    //--------------------------------------------------------------------------
    // Start to program the smart fan mode
    //--------------------------------------------------------------------------
    InitSmartFan1();
    InitSmartFan2();
    InitSmartFan3();
    InitSmartFan4();

    //Create event for boot script
    Status = CreateReadyToBootEvent(
        TPL_NOTIFY,
        HwmCallbackReadyToBoot,
        NULL,
        &gEvtReadyToBoot
    );
    ASSERT_EFI_ERROR(Status);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFanFuncDisable
//
// Description:    This function recovery default value for smartfan registers
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartFanFuncDisable(VOID)
{
    //Set Default value for initialize registers
    AccessHwmWithIO(0x0E, 0x00);
    AccessHwmWithIO(0x0F, 0x00);
    AccessHwmWithIO(0x49, 0x00);
    AccessHwmWithIO(0x4A, 0x00);
    //Set fan speed no change
    AccessHwmWithIO(0x04, 0x00);
    AccessHwmWithIO(0x12, 0x00);
    AccessHwmWithIO(0x62, 0x00);

    AccessHwmWithIO(0x01, 0xFF);
    AccessHwmWithIO(0x03, 0xFF);
    AccessHwmWithIO(0x11, 0xFF);
    AccessHwmWithIO(0x61, 0xFF);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    W83627DHGSmartFanDxeInit
//
// Description:    This function initializes the W83627DHG in DXE
//
// Input:        
//      IN      EFI_HANDLE              ImageHandle
//      IN      EFI_SYSTEM_TABLE        SystemTable
//
// Output:      Status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID W83627DHGSmartFanInit (VOID)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN           Size = sizeof(SETUP_DATA);
    EFI_GUID        SetupGuid = SETUP_GUID;

    //Get Setup variable
    Status=pRS->GetVariable( L"Setup", &SetupGuid, NULL, &Size, &SetupData);
    if(Status != EFI_SUCCESS) return;

    //Init the smart fan function
    if(SetupData.SmartFanEnable) {
        //Start to initialize smart fan function    
        SmartFanFuncStart();
    }else{
        SmartFanFuncDisable();
    }

    return;
}
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

