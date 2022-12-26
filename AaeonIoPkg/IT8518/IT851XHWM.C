//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//
//*************************************************************************
// $Header: $
//
// $Revision: $
//
// $Date:  $
//*************************************************************************
// Revision History
// ----------------
// $Log: $
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81801HWM.c>
//
// Description: This is related to individual HHM devices.
//
//<AMI_FHDR_END>
//*************************************************************************
#include "IT851XHWM.h"
#include "AaeonIoSetup.h"
#include <SetupStrDefs.h>
#include "EcApiProtocol.h"		//+CSKA_008_Elflo 20150901

#define STR_BUFFER_LENGTH   	0x10
//Defination of function 
#define VOLTAGE             	0x01
#define TEMPERATURE         	0x02
#define FAN_SPEED           	0x03

#define PRESENT             	TRUE
#define ABSENT              	FALSE

#define LEFT_JUSTIFY            0x01
#define PREFIX_SIGN             0x02
#define PREFIX_BLANK            0x04
#define COMMA_TYPE              0x08
#define LONG_TYPE               0x10
#define PREFIX_ZERO             0x20

#define DXE_DEVICE_DISABLED        0
#define DXE_DEVICE_ENABLED         1
#define CHARACTER_NUMBER_FOR_VALUE 30

//#if defined(ON_MODULE_CPU_DTS_SUPPORT) && (ON_MODULE_CPU_DTS_SUPPORT == 1)
//EFI_STATUS
//OnModuleCpuDTSGetTemperature (
//  IN OUT UINTN                   *Temperature
//  )
//{
//	#include "Board\AAEON\AAEON.h"	
//	EFI_STATUS Status = EFI_SUCCESS;
//	UINT8 RegTmp8;
//	UINT64 RegTmp64;
//	
//	RegTmp64 = ReadMsr(IA32_THERM_STATUS);
//	RegTmp8 = (UINT8)TjMax - (UINT8)((RegTmp64 >> 16) & 0x7F);
//	*Temperature = (UINTN)RegTmp8;
//	
//	return Status;
//}
//#endif //ON_MODULE_CPU_DTS_SUPPORT

#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
UINTN AaeonIT851xCpuCoreTemperatureDetection()
{
	UINTN RegTmpN = 0;
	UINT32 RegTmp32 = 0;

	#if defined(AMD_TSI_SUPPORT) && (AMD_TSI_SUPPORT)
	{
		#define PCIE_CFG_ADDR(bus,dev,func,reg) (PCIEX_BASE_ADDRESS + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg)
		//#include "Chipset\SB\SBCspLib.h"		
		UINT8 AmdSBTSICpuTempIntOffset = 0x01;
		UINT16 AmdSBTSIAddr = 0x1E8, AmdSBTSIData = 0x1EC;
				
		WRITE_MEM32(PCIE_CFG_ADDR(0, 0x18, 3, AmdSBTSIAddr), AmdSBTSICpuTempIntOffset);
		RegTmp32 = READ_MEM32(PCIE_CFG_ADDR(0, 0x18, 3, AmdSBTSIData));
	}
	#endif //AMD_TSI_SUPPORT
	#if defined(INTEL_DTS_SUPPORT) && (INTEL_DTS_SUPPORT)
	{
/*		
                #include "Vlv2DeviceRefCodePkg/ValleyView2Soc/CPU/Include/CpuRegs.h"
                extern UINT64 ReadMsr(UINT32 Msr);

                EFI_STATUS Status = EFI_SUCCESS;
                UINT8 RegTmp8, TjMax;
                UINT64 RegTmp64;
                
                TjMax = (UINT8)(ReadMsr(EFI_MSR_CPU_THERM_TEMPERATURE) >> 16);
                RegTmp64 = ReadMsr(EFI_MSR_IA32_CR_THERM_STATUS);
                RegTmp8 = (UINT8)TjMax - (UINT8)((RegTmp64 >> 16) & 0x7F);
                RegTmp32 = (UINT32)RegTmp8;
*/                
        }
	#endif //INTEL_DTS_SUPPORT

	RegTmpN = (UINTN)RegTmp32;
	return RegTmpN;
}
#endif //AAEON_CPU_CORE_TEMP_DETECTION

#if defined(SMBUS_G781_HWM_SUPPORT) && (SMBUS_G781_HWM_SUPPORT == 1)
#define G781_SLAVEADDRESS 0x98

EFI_STATUS
G781GetTemperature (
  IN OUT UINTN                   *Temperature
  )
{
	#include <Protocol\Smbus.h>
	
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_SMBUS_HC_PROTOCOL *gSmbusProtocol;
	EFI_SMBUS_DEVICE_ADDRESS SlaveAddress;
	UINTN Length = 1;
	
	Status = pBS->LocateProtocol(&gEfiSmbusProtocolGuid, NULL, &gSmbusProtocol);
	SlaveAddress.SmbusDeviceAddress = G781_SLAVEADDRESS >> 1;
	Status = gSmbusProtocol->Execute( gSmbusProtocol, SlaveAddress, 0x01, EfiSmbusReadByte, FALSE, &Length, Temperature );

	return Status;
}
#endif //SMBUS_G781_HWM_SUPPORT
//----------------------------------------------------------------------------
// Procedure:    IT851X_HWM_CallBack
//
// Description:  Form Callback Function.Will be called every 100m Polling for data Updates.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void IT851X_HWM_CallBack(
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16 Class, 
    IN UINT16 SubClass, 
    IN UINT16 Key
)
{  
        EFI_STATUS         Status;
        STRING_REF         Token;          //String token
        UINT8           OddPos;         //Define how much is odd
        UINTN           DataValue;
//------------------------------------------------------------------------
//AMI_TO:  AMI need to porting the register where they goto read.
//-----------------------------------------------------------------------
        OddPos = 0x00;

//#if defined(ON_MODULE_CPU_DTS_SUPPORT) && (ON_MODULE_CPU_DTS_SUPPORT == 1)
//{
//	Status = OnModuleCpuDTSGetTemperature(&DataValue);
//	if (EFI_ERROR(Status)) return;
//	Token = STRING_TOKEN(STR_ON_MODULE_CPU_DTS_TEMP_VALUE);
//	It851XHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
//}
//#endif //ON_MODULE_CPU_DTS_SUPPORT

#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
{
	DataValue = AaeonIT851xCpuCoreTemperatureDetection();
	Token = STRING_TOKEN(STR_ON_MODULE_CPU_DTS_TEMP_VALUE);
	AaeonHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
}
#endif //AAEON_CPU_CORE_TEMP_DETECTION

#if defined(SMBUS_G781_HWM_SUPPORT) && (SMBUS_G781_HWM_SUPPORT == 1)
{
	Status = G781GetTemperature(&DataValue);
	if (EFI_ERROR(Status)) return;
	Token = STRING_TOKEN(STR_G781_TEMP_VALUE);
	AaeonHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
}
#endif //SMBUS_G781_HWM_SUPPORT




//
//    DTS:
//
#if defined(IT851X_PECI_ENABLE) && (IT851X_PECI_ENABLE)
        Status = It851XGetDTS1(&DataValue);
        if (EFI_ERROR(Status)) return;
        Token = STRING_TOKEN(STR_IT851X_DTS_TEMP1_VALUE);
        AaeonHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
#endif
//
//    Temperature 1:
//
#if defined(IT851X_TEMP1_ENABLE) && (IT851X_TEMP1_ENABLE == 1)
        Status = It851XGetTemperature1(&DataValue);
        if (EFI_ERROR(Status)) return;
        Token = STRING_TOKEN(STR_IT851X_SYS_TEMP1_VALUE);
        AaeonHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
#endif
//
//    Temperature 2:
//
#if defined(IT851X_TEMP2_ENABLE) && (IT851X_TEMP2_ENABLE == 1)
        Status = It851XGetTemperature2(&DataValue);
        if (EFI_ERROR(Status)) return;
        Token = STRING_TOKEN(STR_IT851X_SYS_TEMP2_VALUE);
        AaeonHHMCommon((UINT8)DataValue, TEMPERATURE, Token, OddPos, HiiHandle);
#endif

        OddPos = 0x00;

        //
        //   Get Fan 1: 
        // 
        Status = It851XGetFan1Speed(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_IT851X_FAN1_SPEED_VALUE);
        AaeonHHMCommon((UINT16)DataValue, FAN_SPEED, Token, OddPos, HiiHandle);
        //
        //   Get Fan 2: 
        // 
        Status = It851XGetFan2Speed(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_IT851X_FAN2_SPEED_VALUE);
        AaeonHHMCommon((UINT16)DataValue, FAN_SPEED, Token, OddPos, HiiHandle);

        OddPos = 0x03;

        //
        //   VIN0(VCC3) reading
        //   
        Status = It851XGetVIN0Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN0_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN1(Vcore) reading
        //   
        Status = It851XGetVIN1Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN1_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN2 reading
        // 
        Status = It851XGetVIN2Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN2_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN3 reading
        //   
        Status = It851XGetVIN3Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN3_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN4 reading
        //   
        Status = It851XGetVIN4Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN4_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN5 reading
        //   
        Status = It851XGetVIN5Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN5_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN6 reading
        //   
        Status = It851XGetVIN6Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN6_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);
        //
        //   VIN7 reading
        //   
        Status = It851XGetVIN7Voltage(&DataValue);
        if (EFI_ERROR(Status)) return ;
        Token = STRING_TOKEN(STR_EC1_IT85XX_VIN7_VALUE);
        AaeonHHMCommon((UINT16)DataValue, VOLTAGE, Token, OddPos, HiiHandle);

        return ;
}


//////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------
// Procedure:   GetTemperature1
//
// Description: Get Temperature1 value in HWM space register.
//
// Input:       UINTN    *Temperature         -> Temp to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetDTS1 (
  IN OUT UINTN                   *Temperature
  )
{
        EFI_STATUS  Status;
        
        Status = It851XGetValueWithBram(0x10,Temperature) ;
        if((UINT8)(*Temperature) == 0x80) *Temperature = 0;     // No device on the sensor

        return Status;
}

//----------------------------------------------------------------------------
// Procedure:   GetTemperature1
//
// Description: Get Temperature1 value in HWM space register.
//
// Input:       UINTN    *Temperature         -> Temp to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetTemperature1 (
  IN OUT UINTN                   *Temperature
  )
{
        EFI_STATUS  Status;
        
        Status = It851XGetValueWithBram(0,Temperature) ;
        if((UINT8)(*Temperature) == 0x80) *Temperature = 0;     // No device on the sensor

        return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetTemperature2
//
// Description: Get the second System temperature value in HWM space register.
//
// Input:       UINTN    *Temperature         -> Temp to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetTemperature2 (
  IN OUT UINTN                    *Temperature
  )
{
        EFI_STATUS  Status;

        Status = It851XGetValueWithBram(1,Temperature) ;
        if((UINT8)(*Temperature) == 0x80) *Temperature = 0;     // No device on the sensor

        return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     GetFan1Speed
//
// Description:   Get the First FAN Speed value in HWM space register.
//
// Input:         UINTN    *Speed -> Temp to content the register value
//
// Output:        Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetFan1Speed (
 IN OUT UINTN                    *Speed
  )
{
        EFI_STATUS  Status;

        Status = It851XGetValueWithBram(2,Speed) ;
        //*Speed = 36000 / *Speed * 60;

        return EFI_SUCCESS;

//    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     GetFan1Speed
//
// Description:   Get the First FAN Speed value in HWM space register.
//
// Input:         UINTN    *Speed -> Temp to content the register value
//
// Output:        Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetFan2Speed (
 IN OUT UINTN                    *Speed
  )
{
        EFI_STATUS  Status;

        Status = It851XGetValueWithBram(3,Speed) ;
        //*Speed = 36000 / *Speed * 60;

        return EFI_SUCCESS;

//    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetVIN0Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN0         -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN0Voltage (
IN OUT UINTN                    *VIN0
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN0_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN0_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(4,VIN0) ;
    *VIN0 = (*VIN0)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetVIN1Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN1         -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN1Voltage (
IN OUT UINTN                    *VIN1
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN1_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN1_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(5,VIN1) ;
    *VIN1 = (*VIN1)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetVIN2Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN2        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN2Voltage (
IN OUT UINTN                    *VIN2
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN2_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN2_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(6,VIN2) ;
    *VIN2 = (*VIN2)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}
//----------------------------------------------------------------------------
// Procedure:   GetVIN3Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN2        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN3Voltage (
IN OUT UINTN                    *VIN3
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN3_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN3_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(7,VIN3) ;
    *VIN3 = (*VIN3)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}
//----------------------------------------------------------------------------
// Procedure:   GetVIN4Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN2        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN4Voltage (
IN OUT UINTN                    *VIN4
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN4_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN4_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(8,VIN4) ;
    *VIN4 = (*VIN4)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// Procedure:   GetVIN5Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN5        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN5Voltage (
IN OUT UINTN                    *VIN5
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN5_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN5_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(9,VIN5) ;
    *VIN5 = (*VIN5)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// Procedure:   GetVIN6Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN6        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN6Voltage (
IN OUT UINTN                    *VIN6
  )
{
    EFI_STATUS  Status;
    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN6_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN6_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(10,VIN6) ;
    *VIN6 = (*VIN6)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// Procedure:   GetVIN7Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:       UINTN    *VIN7        -> Voltage to content the register value
//
// Output:      Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN7Voltage (
IN OUT UINTN                    *VIN7
  )
{
    EFI_STATUS  Status;

    UINT8 R1;
    UINT8 R2;

    R1 = (UINT8)(IT851X_VIN7_R1R2 >> 8);
    R2 = (UINT8)(IT851X_VIN7_R1R2 & 0xFF);
    Status = It851XGetValueWithBram(11,VIN7) ;
    *VIN7 = (*VIN7)*1000*(R1+R2)/R2/341;

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// Procedure:     It851XGetValueWithBram
//
// Description: Get the register value form HWM space register.
//
// Input:     UINT8     Index,
//            UINTN   *Value          -> Register value
//
// Output:     Status
//
//----------------------------------------------------------------------------
EFI_STATUS
It851XGetValueWithBram (
    IN UINT8 Index,
    OUT UINTN *Value
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    BRAM_HWM_MAP BramHwmReg[] = 
		{
			0, 0xFF, (0x14+IT851X_PECI_ENABLE),		// Index 0, TMPIN0
			0, 0xFF, (0x15+IT851X_PECI_ENABLE),		// Index 1, TMPIN1
			0, 0x14, 0x15,		// FAN1
			0, 0x14, 0x15,		// FAN2
			0, 0x14, 0x15,		// Index 0, VIN0
			0, 0x16, 0x17,		// Index 1, VIN1
			0, 0x18, 0x19,		// Index 2, VIN2
			0, 0x1A, 0x1B,		// Index 3, VIN3
			0, 0x14, 0x15,		// Index 4, VIN4
			0, 0x16, 0x17,		// Index 5, VIN5
			0, 0x18, 0x19,		// Index 6, VIN6
			0, 0x1A, 0x1B,		// Index 7, VIN7
			0, 0x14, 0x15,		// Index 0, 
			0, 0x16, 0x17,		// Index 1, 
			0, 0x18, 0x19,		// Index 2, 
			0, 0x1A, 0x1B,		// Index 3, 
			0, 0xFF, 0x14,		// Index 0, TMPIN0 
    		};

	switch(Index)
		{
			case 2:	
				Status = EcSmfAccess(0x00,ApiRead);
				break;			

			case 3: 
				Status = EcSmfAccess(0x01,ApiRead);
				break;

			case 4:	case 5:	case 6:	case 7: 
				Status = EcHwmAccess(0x01,ApiRead);
				break;

			case 8:	case 9:	case 10: case 11:
				Status = EcHwmAccess(0x02,ApiRead);
				break;
			
			case 0:	case 1: case 16: default:
				Status = EcHwmAccess(0x00,ApiRead);
				break;
	
		}
	
	if (Status)
	{
	  *Value = EcReadByte(BramHwmReg[Index].LByteOffset);
	  if(BramHwmReg[Index].HByteOffset != 0xFF)
	  {*Value += EcReadByte(BramHwmReg[Index].HByteOffset)<<8;}
	}
	else
	{ *Value = 0xffff;}
	
	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:  It851XHHMEfiValueToString
//
// Description: This function Adjust the String shows in setup screen
//
// Input:     INT64       Value       ->Value need change to string
//            UINTN       Flags       ->Comma type
//            UINTN       Width       ->Character number for value
//            CHAR16      *Buffer     ->Temp string for this change
// Output:     
//
// OPTIONAL:  None
//
// Returns:   Index
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN
It851XHHMEfiValueToString (
    IN  OUT CHAR16  *Buffer, 
    IN  INT64       Value, 
    IN  UINTN       Flags,
    IN  UINTN       Width
) {
    CHAR16      TempBuffer[CHARACTER_NUMBER_FOR_VALUE];
    CHAR16      *TempStr;
    CHAR16      *BufferPtr;
    UINTN       Count;
    UINTN       ValueCharNum;
    UINTN       Remainder;
    CHAR16      Prefix;
    UINTN       Index;
    BOOLEAN     ValueIsNegative;

    TempStr           = TempBuffer;
    BufferPtr         = Buffer;
    Count             = 0;
    ValueCharNum      = 0;
    ValueIsNegative   = FALSE;

    if (Width > CHARACTER_NUMBER_FOR_VALUE - 1) {
        Width = CHARACTER_NUMBER_FOR_VALUE - 1;
    }

    if (Value < 0) {
        *(TempStr++) = '-';
        Value        = -Value;
        ValueCharNum++;
        Count++;
        ValueIsNegative = TRUE;
    }
    do {
        if ((Width != 0) && (Count >= Width)) break;

        Value = (UINT64)Div64 ((UINT64)Value, 10, &Remainder);
        *(TempStr++) = (CHAR16)(Remainder + '0');
        ValueCharNum++;
        Count++;

        if ((Flags & COMMA_TYPE) == COMMA_TYPE) {
            if (Value != 0) {
                if ((ValueIsNegative && (ValueCharNum % 3 == 1)) || ((!ValueIsNegative) && (ValueCharNum % 3 == 0))) {
                    *(TempStr++) = ',';
                    Count++;
                }
            }
        }
    } while (Value != 0);

    if (Flags & PREFIX_ZERO) Prefix = '0';
    else Prefix = ' ';

    Index = Count;

    if (!(Flags & LEFT_JUSTIFY)) {
        for (; Index < Width; Index++) 
            *(TempStr++) = Prefix;
    }
//
// Reverse temp string into Buffer.
//
    if (Width == 0) {
        while (TempStr != TempBuffer) 
            *(BufferPtr++) = *(--TempStr);
    } else {
        Index = 0;
        while ((TempStr != TempBuffer) && (Index++ < Width))
        *(BufferPtr++) = *(--TempStr);
    } 
    *BufferPtr = 0;
    return Index;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    It851XAdjustString
//
// Description:  Adjust string with float point
//
// Input:        Buffer          -> defautl string.  ": N/A    ". Buffer length should more than 0x10
//               StringToChged   -> Raw data
//               STCLen          -> String total length
//               HeadBuf         -> Header of string
//               HeadLen         -> Header length
//               Flag            -> TRUE indicate is a float data, False indicate it's a integet data.
//               MidPos          -> Float point position. eg: 0.076 is 0x3
//               TailBuf         -> unit of string data 
//               TailLen         -> Length of unit
//
// Output:       Return string in Buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID It851XAdjustString(
    IN OUT  CHAR16  * Buffer,
    IN      CHAR16  * StringToChged,
    IN      UINT8   STCLen,
    IN      CHAR16  * HeadBuf,
    IN      UINT8   HeadLen,
    IN      BOOLEAN Flag,
    IN      UINT8   MidPos,
    IN      CHAR16  * TailBuf,
    IN      UINT8   TailLen
) {
    CHAR16     *temp        = Buffer;
    CHAR16     *TempSrc     = StringToChged;
    CHAR16     dod[]        ={L"."};
    CHAR16     Zero[]       ={L"0"};

    pBS->SetMem(temp, STR_BUFFER_LENGTH * sizeof(CHAR16), 0);

    if(HeadLen) {
//Add the leading string
        pBS->CopyMem(temp, HeadBuf, (HeadLen * sizeof(CHAR16)));
        temp +=  HeadLen;
    }
    if (!Flag) {
//Add the float point->L"."
        pBS->CopyMem(temp, TempSrc, (STCLen * sizeof(CHAR16))); 		//Add the string before float point
        temp += STCLen; TempSrc += STCLen;
        goto not_float_data;
    }

    if(STCLen <= MidPos) {
//make up with a zero
        pBS->CopyMem(temp, Zero, (0x01 * sizeof(CHAR16)));      		//Copy a 0
        temp++;
    } else {
        pBS->CopyMem(temp, TempSrc, ((STCLen - MidPos) * sizeof(CHAR16))); 	//Add the string before float point
        temp += (STCLen - MidPos); TempSrc += (STCLen - MidPos);
    }
    pBS->CopyMem(temp, dod, 0x01 * sizeof(CHAR16));             		//Add the float point->L"."
    temp++;
    if(STCLen < MidPos) {
//make up with a zero
        pBS->CopyMem(temp, Zero, ((MidPos - STCLen) * sizeof(CHAR16)));		//Copy a 0
        pBS->CopyMem(temp, TempSrc, ((STCLen) * sizeof(CHAR16)));    		//Add the string after float point
        temp += MidPos; TempSrc += MidPos;
    } else {
        pBS->CopyMem(temp, TempSrc, ((MidPos) * sizeof(CHAR16)));    		//Add the string after float point
        temp += MidPos; TempSrc += MidPos;
    }
    not_float_data:
    if (TailLen) {
//Add the unit
        pBS->CopyMem(temp, TailBuf, (TailLen * sizeof(CHAR16)));        
    }
    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    It851XHHMCommon
//
// Description:  Update option with the data read from register
//
// Input:        RegData         -> data from SIO registers
//               Func            -> Fan Speed,Voltage and Temperature
//               StrToken        -> String token
//               OddPos          -> Odd position
//               hiiHandle       
//               gblHii
//
// Output:       Return string in Buffer
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID It851XHHMCommon(
    IN      UINT16    RegData,
    IN      UINT8     Func,
    IN      UINT16    StrToken,
    IN      UINT8     OddPos,
    IN      EFI_HII_HANDLE    hiiHandle
) {
    CHAR16          TailRound[]     = L" RPM";          //Fan uint
    CHAR16          TailVoltg[]     = L" V";            //Voltage uint
    CHAR16          TailTempt[]     = L" C";            //Temperature uint
    CHAR16          LeadingMini[]   = L": -";           //Fix 
    CHAR16          LeadingPlus[]   = L": +";           //Fix 
    CHAR16          LeadingSpac[]   = L": ";            //Fix
    CHAR16          AllSpace[]      = L": N/A       ";  //Fix
    CHAR16          *TempStr        = AllSpace;
    UINT8           StrLen;
    UINT64          NData;
    CHAR16          StrUp[STR_BUFFER_LENGTH] = L": N/A     "; //Don't change this line    
    CHAR16          *StrUpdated = StrUp;

	BOOLEAN			T_flag = 1;
    TailTempt[1]=0x2103;
    NData = (UINT64)(RegData);
//The following may be ported by each SIO
//if((Func == TEMPERATURE) && (NData & 0x80)) NData =(~(NData - 1))& 0x7f;

    if((Func == TEMPERATURE) & (NData > 0x7F) & (NData <= 0xFF)) //If get temperature data, and data range is 128~255, define minus data
    {
        T_flag = 0;               //Use symbol "-"
        NData = 0x100 - NData;     //Convert minus data
    }

        if(NData>9999)      StrLen = 0x5;               //As now, it support max length is five
        else if(NData>999)  StrLen = 0x4;
        else if(NData>99)   StrLen = 0x3;
        else if(NData>9)    StrLen = 0x2;
        else                StrLen = 0x1;    

        if(NData == 0x00) StrUpdated = StrUp;            //When device not present, update to 'N/A'
        else {
            It851XHHMEfiValueToString(TempStr, NData, 0, StrLen);
            switch(Func) {
                case    VOLTAGE:                       //Indicate it's voltage
                    It851XAdjustString(StrUpdated, TempStr, StrLen, LeadingPlus, 0x03,\
                                OddPos?TRUE:FALSE, OddPos, TailVoltg, 0x02);
                    break;

                case    TEMPERATURE:                   //Indicate it's Temperature
//                   It851XAdjustString(StrUpdated, TempStr, StrLen, LeadingPlus, 0x03,\
//                             OddPos?TRUE:FALSE, OddPos, TailTempt, 0x02);

				It851XAdjustString(StrUpdated, TempStr, StrLen, T_flag?LeadingPlus:LeadingMini, 0x03,\
                                OddPos?TRUE:FALSE, OddPos, TailTempt, 0x02);
                    break;

                case    FAN_SPEED:                     //Indicate it's fan
                    It851XAdjustString(StrUpdated, TempStr, StrLen, LeadingSpac, 0x02,\
                                OddPos?TRUE:FALSE, OddPos, TailRound, 0x04);
                    break;
                default :                              //Default to " N/A "
                    break;
            }
        }

    InitString(hiiHandle, StrToken, StrUpdated);

        return;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
