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
// $Date: $
//*************************************************************************
// Revision History
// ----------------
// $Log:  $
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81801HWM.h>
//
// Description: Structures of HardwareMonitor functions
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _ECHWM_H
#define _ECHWM_H

#include "token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
//#include <SetupStrTokens.h>

#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)

#if defined(AMD_TSI_SUPPORT) && (AMD_TSI_SUPPORT)
#include "Chipset\SB\SBCspLib.h"
#endif //AMD_TSI_SUPPORT

#if defined(INTEL_DTS_SUPPORT) && (INTEL_DTS_SUPPORT)
#endif //INTEL_DTS_SUPPORT

#endif //AAEON_CPU_CORE_TEMP_DETECTION

#ifndef VFRCOMPILE
#define STRING_TOKEN(x) x
#endif



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      IT851X_HWM_CallBack
//
// Description:    This function show setup items call back. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void IT851X_HWM_CallBack (
    EFI_HII_HANDLE HiiHandle,
    UINT16 Class, 
    UINT16 SubClass, 
    UINT16 Key
);

typedef struct {
    UINT8 Bank;
    UINT8 HByteOffset;
    UINT8 LByteOffset;
} BRAM_HWM_MAP;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      APreadEC
//
// Description:    This function show the value for IO. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
APreadEC (
    IN UINT8 HAddr,
    IN UINT8 LAddr,
    OUT UINTN *Value
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      IT851x_BRAM_ADC
//
// Description:    This function show the value for IO. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IT851x_BRAM_ADC (
    IN UINT8 Index,
    OUT UINTN *Value
);

//----------------------------------------------------------------------------
// Procedure:      IT851x_BRAM_FAN
//
// Description:    This function show the value for IO. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
IT851x_BRAM_FAN (
    IN UINT8 Index,
    OUT UINTN *Value
);

//----------------------------------------------------------------------------
// Procedure:      It851XGetValueWithBram
//
// Description:    This function show the value for IO. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetValueWithBram (
    IN UINT8 Index,
    OUT UINTN *Value
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      GetVIN(0-2)Voltage,GetVSB5Voltage,GetVBATVoltage
//
// Description:    This function show the value for Voltage. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetVIN0Voltage (
IN OUT UINTN                    *VIN0
);

EFI_STATUS
It851XGetVIN1Voltage (
IN OUT UINTN                    *VIN1
);

EFI_STATUS
It851XGetVIN2Voltage (
IN OUT UINTN                    *VIN2
);

EFI_STATUS
It851XGetVIN3Voltage (
IN OUT UINTN                    *VIN3
);

EFI_STATUS
It851XGetVIN4Voltage (
IN OUT UINTN                    *VIN4
);

EFI_STATUS
It851XGetVIN5Voltage (
IN OUT UINTN                    *VIN5
);

EFI_STATUS
It851XGetVIN6Voltage (
IN OUT UINTN                    *VIN6
);

EFI_STATUS
It851XGetVIN7Voltage (
IN OUT UINTN                    *VIN7
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      GetTemperature1,GetTemperature2
//
// Description:    This function show the value for temperature. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
It851XGetDTS1 (
IN OUT UINTN                    *Temperature
);

EFI_STATUS
It851XGetTemperature1 (
IN OUT UINTN                    *Temperature
);
EFI_STATUS
It851XGetTemperature2 (
IN OUT UINTN                    *Temperature
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:      GetFan1Speed,GetFan2Speed,GetFan3Speed
//
// Description:    This function show the value for Fan Speed. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
It851XGetFan1Speed (
IN OUT UINTN                    *Speed
);

EFI_STATUS
It851XGetFan2Speed (
IN OUT UINTN                    *Speed
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    AdjustString
//
// Description:    Definition of AdjustString
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void It851XAdjustString(
    IN OUT  CHAR16  * Buffer,
    IN      CHAR16  * StringToChged,
    IN      UINT8   STCLen,
    IN      CHAR16  * HeadBuf,
    IN      UINT8   HeadLen,
    IN      BOOLEAN Flag,
    IN      UINT8   MidPos,
    IN      CHAR16  * TailBuf,
    IN      UINT8   TailLen
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    HHMCommon
//
// Description:    This function show the value to setup
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void It851XHHMCommon(
    IN      UINT16  RegData,
    IN      UINT8   Func,
    IN      UINT16  StrToken,
    IN      UINT8   RefValue,
    EFI_HII_HANDLE    hiiHandle
);

#endif

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
//*************************************************************************
