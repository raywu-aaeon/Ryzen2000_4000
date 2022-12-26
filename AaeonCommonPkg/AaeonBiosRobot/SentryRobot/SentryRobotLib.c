#include <Efi.h>
#include <Token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Library/IoLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Ppi/Smbus2.h>
#include <Protocol/SmbusHc.h>
#include <SentryRobotLib.h>
#include <Library/PciCf8Lib.h>
#include <AaeonBiosRobotCommonLib.h>
#include <Library\AmiChipsetIoLib.h>
#include "AaeonCommonLib.h"

UINT8 GetSmbusValue(UINT8 SlaveAdd, UINT8 offset)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_SMBUS_DEVICE_ADDRESS    SlaveAddress;
    UINTN                       Length = 1;
    UINT8                       data = 0;
    EFI_SMBUS_HC_PROTOCOL       *gSmbusProtocol = NULL;
    
    if (gSmbusProtocol == NULL)
    {
        Status = gBS->LocateProtocol (&gEfiSmbusHcProtocolGuid, NULL, (VOID **) &gSmbusProtocol);
        if (EFI_ERROR(Status))
        {
          return (UINT8)data;
        }            
    }
    
    SlaveAddress.SmbusDeviceAddress = SlaveAdd;
     
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddress, offset, EfiSmbusReadByte, FALSE, &Length, &data);
    
    return (UINT8)data;
}

#if defined (AaeonDio3_SUPPORT) && AaeonDio3_SUPPORT
UINT8 GetTheDioValue(UINT8  RobotNum,SETUP_DATA SetupData)
{
    UINT8               WatchValue=0;
    
    // Call AaeonCommonLib
    WatchValue = AaeonGetGpio(SetupData.DioSource,SetupData.SentryDioNum[RobotNum]);
        
    return WatchValue;
}
#endif

UINT8 GetTheLegacyIoValue(UINT32 IoAdd)
{
    UINT8               WatchValue=0;
    WatchValue = IoRead8(IoAdd);
    
    return WatchValue;
}

UINT8 GetTheIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8               WatchValue=0;
    
    WatchValue = AaeonGetIoLdnValue(ROBOT_MONITOR_SIO_CHIP_TYPE,IOLDN,RegisterOffset);
    
    return WatchValue;
}

//----------------------------------------------------------------------------
//
// Procedure:   GetTheWatchValue
//
// Description: Read WatchValue from device for Sentry Robot to check,
//              according to setup configurations.
//
// Input:       
//
// Output:      
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 GetTheWatchValue(UINT8  RobotNum,SETUP_DATA SetupData)
{
    UINT8 WatchValue=0;
    UINT64 Address=0;
    UINT8 BUS;
    UINT8 DEV;
    UINT8 FUN;
    UINT8 OFFSET;
    UINT8 IoLdn;
    
    switch (SetupData.SentryRobotType[RobotNum]) {
    
    case 1:    // PCI Register
        
        BUS = SetupData.SentryCheckBus[RobotNum];
        DEV = SetupData.SentryCheckDev[RobotNum];
        FUN = SetupData.SentryCheckFun[RobotNum];

        OFFSET = SetupData.SentryRegOffset[RobotNum];

        if(SetupData.SentryInCondition[RobotNum] == 0)
            WatchValue = READ_PCI8(BUS,DEV,FUN,0);
        else
            WatchValue = READ_PCI8(BUS,DEV,FUN,OFFSET);
        break;
#if defined (AaeonDio3_SUPPORT) && AaeonDio3_SUPPORT
    case 2:    // DIO level

        WatchValue = GetTheDioValue(RobotNum,SetupData);

        break;
#endif
    case 3:    // SMBUS register

        Address = SetupData.SentrySmbusSlave[RobotNum];
        if(SetupData.SentryInCondition[RobotNum] == 0)
            OFFSET = 0x00;
        else
            OFFSET = SetupData.SentryRegOffset[RobotNum];

        WatchValue = GetSmbusValue((UINT8)Address,OFFSET);

        break;

    case 4:    // Legacy IO

        Address = SetupData.SentryIoAddress[RobotNum];       
        WatchValue = GetTheLegacyIoValue((UINT32)Address);

        break;

    case 5:    // Super I/O register

        if(SetupData.SentryInCondition[RobotNum] == 0)
            OFFSET = 0x20;
        else
            OFFSET =  SetupData.SentryRegOffset[RobotNum];
        
        IoLdn = SetupData.SentryIoLdn[RobotNum];
        WatchValue = GetTheIoLdnValue(IoLdn,OFFSET);

        break;

    case 6:    // MMIO Register

        Address = SetupData.SentryMmioAddress[RobotNum];
        WatchValue = MmioRead8(Address);

        break;
    }
    
    return WatchValue;
}

//----------------------------------------------------------------------------
//
// Procedure:   SentryRobot
//
// Description: This function will follow bios setting to check 
//              configuration.
// Input:       
//
// Output:      
//
// Notes:       
//----------------------------------------------------------------------------
VOID
EFIAPI
SentryRobot(SETUP_DATA   SetupData,UINT32  Attributes)
{

    BOOLEAN             Mismatch = FALSE;
    UINT8               ResetCount = 0;
    UINT8               WatchValue = 0;
    UINT8               DelayCount = 0;
    UINT8               BitValue=0;
    UINT8               ByteValue=0;

    EFI_GUID            SetupGuid = SETUP_GUID;
    EFI_STATUS          Status = 0;
    UINTN               VariableSize = sizeof(SETUP_DATA);
    UINT8               RobotCount = SENTRY_ROBOT_NUMBER;
    UINT8               RobotNum;  

    while (1)
    {
        Mismatch = FALSE;
        
        for (RobotNum = 0; RobotNum < RobotCount; RobotNum++)
        {
            if (SetupData.SentryRobotType[RobotNum] == 0)    // Disabled?
                continue;   // Skip if it is disabled
            
            WatchValue = GetTheWatchValue(RobotNum,SetupData);    // Get value for this SetryRobot to watch
            
#if defined (AaeonDio3_SUPPORT) && AaeonDio3_SUPPORT
            if (SetupData.SentryRobotType[RobotNum] == 2)    // Watch DIO?
            {
                
                if ((WatchValue != SetupData.SentryDioLevel[RobotNum]) == SetupData.SentryRevert[RobotNum])
                    Mismatch = TRUE;
            }
#endif
            if (SetupData.SentryInCondition[RobotNum] == 1 && SetupData.SentryRobotType[RobotNum] != 2)    // Watch register value?
            {
                switch (SetupData.SentryAddCondition[RobotNum]) {
            
                case 0:    // Bitwise equal to
                    
                    BitValue = (WatchValue & (BIT0 << SetupData.SentryBitOffset[RobotNum])) >> (SetupData.SentryBitOffset[RobotNum]);                    
                    
                    if ((BitValue != SetupData.SentryBitValue[RobotNum]) == SetupData.SentryRevert[RobotNum] )
                        Mismatch = TRUE;
                                        
                    break;
                
                case 1:    // Bytewise equal to
                    
                    ByteValue = SetupData.SentryByteValue[RobotNum];
                    if ((WatchValue != ByteValue) == SetupData.SentryRevert[RobotNum] )
                        Mismatch = TRUE;
                
                    break;
                
                case 2:    // Bytewise lesser than

                    ByteValue = SetupData.SentryByteValue[RobotNum];
                    if ((ByteValue < WatchValue) == SetupData.SentryRevert[RobotNum] )
                        Mismatch = TRUE;

                    break;
                
                case 3:    // Bytewise greater than

                    ByteValue = SetupData.SentryByteValue[RobotNum];
                    if ((ByteValue > WatchValue) == SetupData.SentryRevert[RobotNum] )
                        Mismatch = TRUE;                 
   
                    break;
                
                }    // End switch SentryAddCondition
            }    // End Watch register value?
            
            if(SetupData.SentryInCondition[RobotNum] == 0 && SetupData.SentryRobotType[RobotNum] != 2)   // Watch device precence?
            {
                if ((WatchValue == 0xff)  == SetupData.SentryRevert[RobotNum] )
                    Mismatch = TRUE;
            }
        }   // End For RobotNum
  
        if (SetupData.SentryAction == 1 && Mismatch == TRUE )   // Hold system when mismatch?
        {
            if (SetupData.SentryHoldTime == DelayCount)
                break;
            else {
                DelayCount++;
                gBS->Stall(1000000);
            }
        } else {
            break;
        }

    }//while loop;
    
    // ROBOT_TO_DO : SentryBootCount has no default value
    if (SetupData.SentryAction == 0)    // Reset system?
    {
        ResetCount = SetupData.SentryBootCount;
       
        if ((Mismatch == 1) && (ResetCount < SetupData.SentryRetryCount) )
        {
            ResetCount++;
            SetupData.SentryBootCount = ResetCount;
            Status = gRT->SetVariable(L"Setup", &SetupGuid, Attributes, VariableSize, &SetupData);
            
             if(SetupData.SentryResetType == 0)         
                 gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
         
             if(SetupData.SentryResetType == 1)    
                 gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);             
        } else {
            SetupData.SentryBootCount = 0;
            Status = gRT->SetVariable(L"Setup", &SetupGuid, Attributes, VariableSize, &SetupData);
        }
    }
    
}

//----------------------------------------------------------------------------
//
// Procedure:   SentryRobotCheckFunction
//
// Description: This function will follow bios setting to check 
//              Device#1~#5 detecting configuration.
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called after system show logo.
//----------------------------------------------------------------------------
VOID
EFIAPI
SentryRobotCheckFunction(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS          Status = 0;
    UINTN               VariableSize = sizeof(SETUP_DATA);
    EFI_GUID            SetupGuid = SETUP_GUID;
    SETUP_DATA          SetupData;
    UINT32              Attributes;
    
    Status = gRT->GetVariable( L"Setup", &SetupGuid, &Attributes, &VariableSize, &SetupData );
    if (SetupData.SentryActionTime == 0)  
        SentryRobot(SetupData,Attributes);
    
}

//----------------------------------------------------------------------------
//
// Procedure:   SentryRobotCheckBeforeLogo
//
// Description: This function will follow bios setting to check 
//              Device#1~#5 detecting configuration.
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called before system show logo.
//----------------------------------------------------------------------------
VOID
EFIAPI
SentryRobotCheckBeforeLogo(IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS          Status = 0;
    UINTN               VariableSize = sizeof(SETUP_DATA);
    EFI_GUID            SetupGuid = SETUP_GUID;
    SETUP_DATA          SetupData;
    UINT32              Attributes;
    
    VariableSize = sizeof(SetupData);
  
    Status = gRT->GetVariable( L"Setup", &SetupGuid, &Attributes, &VariableSize, &SetupData );
    if (SetupData.SentryActionTime == 1)
        SentryRobot(SetupData,Attributes);

}
