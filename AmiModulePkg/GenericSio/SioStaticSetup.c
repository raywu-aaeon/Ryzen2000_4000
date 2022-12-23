//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file SioStaticSetup.c

    Sub Module Strings override routines to dynamically change Setup.
**/ 
//**********************************************************************
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include <AmiGenericSio.h>
#include <SioSetup.h>
#include <Library/PrintLib.h>
#if SIO_SUPPORT
#include "SIOElink.h"

STR_UID STR_TABLE_LIST[]= {SIO_Init_Str_LIST {dsNone, 0x00, 0x00}};
#else
STR_UID STR_TABLE_LIST[]= {{dsNone, 0x00, 0x00}};
#endif

//**********************************************************************
/**
        
    Certain strings in the terminal setup page can only be
    updated at runtime, which is what this function does.
    The pci serial port names are changed to contain the
    location (device and function numbers) of the port.
    If any serial ports are disabled, "Disabled"
    is concatenated to their names.

    @param[in] HiiHandle    Handle to HII database.
    @param[in] Class        Indicates the setup class.
**/
VOID EFIAPI SioSetupStringsInit(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
    static EFI_GUID    siopg=EFI_AMI_SIO_PROTOCOL_GUID;
    static EFI_GUID    DevicePathProtocolGuid=EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_DEVICE_PATH_PROTOCOL            *DevicePath = NULL;
    BOOLEAN IsGsio=FALSE; 
    SIO_DEV2    *dev;
    UINTN        i,hcnt;
    EFI_HANDLE    *hbuff;
    EFI_STATUS    Status=0;
//------------------------------------
//DEBUG    
//EFI_DEADLOOP();    
//DEBUG    

    if(Class == ADVANCED_FORM_SET_CLASS) {
        Status=pBS->LocateHandleBuffer(ByProtocol,&siopg, NULL, &hcnt,&hbuff);
        if (EFI_ERROR(Status)) hcnt = 0;
        for (i=0; i<hcnt; i++) {
            Status = pBS->HandleProtocol ( hbuff[i],&siopg,(VOID*)&dev);
            ASSERT_EFI_ERROR(Status);
            Status = pBS->HandleProtocol ( hbuff[i],&DevicePathProtocolGuid,(VOID*)&DevicePath);
            ASSERT_EFI_ERROR(Status);            
            
            if (DevicePath == NULL) continue;
            
            while (!isEndNode (DevicePath)) {
                if (DevicePath->Type == HARDWARE_DEVICE_PATH && DevicePath->SubType== HW_PCI_DP){
                    IsGsio=TRUE;
                    break;
                }
                DevicePath = NEXT_NODE (DevicePath);
            }
            if(!IsGsio) continue; //If device path has no HARDWARE_DEVICE_PATH, skip it.
            if(dev->DeviceInfo->HasSetup) SetSioStrings(dev, HiiHandle);
        }
    }
}

/**
    This function provide SIO's each logic device Setup screen display string.
        
    @param[in] Dev                  SPIO Device Private Data section.
    @param[in] HiiHandle            Handle to HII database.
**/
VOID EFIAPI SetSioStrings(
    VOID            *DevVoid,
    EFI_HII_HANDLE  HiiHandle)
{
    UINT8       i;
    CHAR16      pString16[80];
    UINTN       StringSize = sizeof(pString16);
    SIO_DEV2    *Dev = (SIO_DEV2 *)DevVoid;

    if((!Dev->NvData.DevEnable) || (!Dev->VlData.DevImplemented)) return;

    if(Dev->VlData.DevDma1) {
        if(Dev->VlData.DevIrq1)
            UnicodeSPrint(pString16, StringSize,  L"IO=%Xh; IRQ=%d; DMA=%d;", Dev->VlData.DevBase1,Dev->VlData.DevIrq1,Dev->VlData.DevDma1);
        else
            UnicodeSPrint(pString16, StringSize, L"IO=%Xh; DMA=%d;",Dev->VlData.DevBase1, Dev->VlData.DevDma1);
    }
    else {
        if(Dev->VlData.DevIrq1)
            UnicodeSPrint(pString16, StringSize, L"IO=%Xh; IRQ=%d;",Dev->VlData.DevBase1,Dev->VlData.DevIrq1);
        else
            UnicodeSPrint(pString16, StringSize, L"IO=%Xh;",Dev->VlData.DevBase1);
    }

    for(i=0; i<(sizeof(STR_TABLE_LIST)/sizeof(STR_UID)); i++) {
        if((STR_TABLE_LIST[i].UID == Dev->DeviceInfo->Uid) && \
           (STR_TABLE_LIST[i].Type == Dev->DeviceInfo->Type)) {
            InitString(HiiHandle,STR_TABLE_LIST[i].StrTokenV,pString16);
            return;
        }

    }
    return;
}

/**
    This function will return the power raised to the base number.

    @param Base     Base number.
    @param Power    Power value.
     
    @retval Data    the power raised to the base number

**/ 
UINTN
Pow (UINT8 Base, UINT8 Power)
{
    UINT8   Index;
    UINTN   Data = 1;
    for(Index = 0;Index < Power;Index ++) {
        Data *= Base;
    }
    return Data;
}

/**
    Update option with the data read from register.
        
    @param[in] RegData      Data from SIO registers.
    @param[in] Func         Fan Speed,Voltage and Temperature.
    @param[in] StrToken     String token.
    @param[in] OddPos       Odd position.
    @param[in] hiiHandle    HII Handle.
**/
VOID EFIAPI HHMCommon(
    IN      UINT64     RegData,
    IN      UINT8     Func,
    IN      UINT16    StrToken,
    IN      UINT8     OddPos,
    IN      EFI_HII_HANDLE    hiiHandle
) {
    INT64           NData;
    CHAR16          StrUpdated[100];
    UINTN           StrSize = 100;
    CHAR16          Leading[2];
    CHAR16          Tail[4];
    UINT64          IntData;
    UINT64          FloatData;

    NData = (INT64)(RegData);
    StrCpyS(Leading, 2, L"+");
    //add negative value handle
    if(NData<0) {
        NData = -NData;
        StrCpyS(Leading, 2, L"-");
    }

    switch(Func) {
    case    VOLTAGE:                       //Indicate it's voltage
        StrCpyS(Tail, 2, L"V");
        break;
    case    TEMPERATURE:                   //Indicate it's Temperature
        StrCpyS(Tail, 2, L"\x2103");
        break;
    case    FAN_SPEED:                     //Indicate it's fan
        StrCpyS(Tail, 4, L"RPM");
        StrCpyS(Leading, 1, L"");
        break;
    default :                              
        break;
    }
    //When device not present, update to 'N/A'
    if(NData == 0x00) {
        StrCpyS(StrUpdated, 11, L": N/A     ");
    }
    else {
        if(OddPos) {
            FloatData = NData % Pow(10, OddPos);
            IntData = NData / Pow(10, OddPos);
            UnicodeSPrint(StrUpdated, StrSize, L": %s%d.%0*d %s", Leading, IntData, OddPos, FloatData, Tail);
        }
        else {
            IntData = NData;
            UnicodeSPrint(StrUpdated, StrSize, L": %s%d %s", Leading, IntData, Tail);
        }
    }
    
    InitString(hiiHandle, StrToken, StrUpdated);

    return;
}

