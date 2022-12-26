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
// $Header: /Alaska/BIN/IO/Fintek/F81966/F81966 Board/F81966SmartFan.c 1     7/20/11 4:23a Kasalinyi $Revision: 
//
// $Date:
//*************************************************************************
// Revision History
// ----------------
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81966SmartFan.c>
//
// Description: This is related to individual Smart Fan functions.
//
//<AMI_FHDR_END>
//*************************************************************************
#include <AmiPeiLib.h>
#include <Library/AmiSioPeiLib.h>
#include <Setup.h>
#include <AmiCspLib.h>

#define IDX_FAN_MODE       0
#define IDX_TEMP_HYS       1
#define IDX_FAN_SPEED_MSB  2
#define IDX_FAN_SPEED_LSB  3
#define IDX_TEMP_BOUND1    4
#define IDX_TEMP_BOUND2    5
#define IDX_TEMP_BOUND3    6
#define IDX_TEMP_BOUND4    7
#define IDX_SPEED_SEG1     8
#define IDX_SPEED_SEG2     9
#define IDX_SPEED_SEG3     10
#define IDX_SPEED_SEG4     11
#define IDX_SPEED_SEG5     12
#define IDX_TEMP_SRCSEL    13
#define IDX_FAN_TYPE       14

typedef  struct _SMF_INIT_DATA{
  UINT8       Reg8;
  UINT8       AndData8;
  UINT8       OrData8;    
} SMF_INIT_DATA;

//----------------------------------------------------------------------------------------------
// smart system fan registers need init AfterActivate. !!!AfterActivate
//----------------------------------------------------------------------------------------------
#if defined(F81966_SMF1_SUPPORT) && (F81966_SMF1_SUPPORT == 1)
SMF_INIT_DATA   F81966_FAN1_INIT_TABLE[] = {
    {0x96, 0xFC, 0x00},
    {0x98, 0xF0, 0x02},
    {0xA2, 0xFF, 0x00},
    {0xA3, 0xFF, 0x00},
    {0xA6, 0xFF, 0x00},
    {0xA7, 0xFF, 0x00},
    {0xA8, 0xFF, 0x00},
    {0xA9, 0XFF, 0x00},
    {0xAA, 0xFF, 0xFF},
    {0xAB, 0xFF, 0x00},
    {0xAC, 0xFF, 0x00},
    {0xAD, 0xFF, 0x00},
    {0xAE, 0xFF, 0x00},
    {0xAF, 0xFC, 0x00},
    {0x94, 0xFC, 0x00},
};
#endif

#if defined(F81966_SMF2_SUPPORT) && (F81966_SMF2_SUPPORT == 1)
SMF_INIT_DATA   F81966_FAN2_INIT_TABLE[] = {
  {0x96, 0xF3, 0x00},
    {0x98, 0x0F, 0x20},
  {0xB2, 0xFF, 0x00},
  {0xB3, 0xFF, 0x00},
  {0xB6, 0xFF, 0x00},
  {0xB7, 0xFF, 0x00},
  {0xB8, 0xFF, 0x00},
  {0xB9, 0XFF, 0x00},
  {0xBA, 0xFF, 0xFF},
  {0xBB, 0xFF, 0x00},
  {0xBC, 0xFF, 0x00},
  {0xBD, 0xFF, 0x00},
  {0xBE, 0xFF, 0x00},
  {0xBF, 0xFC, 0x00},
  {0x94, 0xF3, 0x00},
};
#endif

#if defined(F81966_SMF3_SUPPORT) && (F81966_SMF3_SUPPORT == 1)
SMF_INIT_DATA   F81966_FAN3_INIT_TABLE[] = {
  {0x96, 0xCF, 0x00},
  {0x99, 0xF0, 0x02},
  {0xC2, 0xFF, 0x00},
  {0xC3, 0xFF, 0x00},
  {0xC6, 0xFF, 0x00},
  {0xC7, 0xFF, 0x00},
  {0xC8, 0xFF, 0x00},
  {0xC9, 0XFF, 0x00},
  {0xCA, 0xFF, 0xFF},
  {0xCB, 0xFF, 0x00},
  {0xCC, 0xFF, 0x00},
  {0xCD, 0xFF, 0x00},
  {0xCE, 0xFF, 0x00},
  {0xCF, 0xFC, 0x00},
  {0x94, 0xCF, 0x00},
};
#endif

//--------------------------------------------------------------------------
// Definition of smart fan functions
//--------------------------------------------------------------------------
VOID F81966SmartFunction (SETUP_DATA *SetupData);
VOID F81966_FAN_Full();
static VOID SmartFanFuncStart(SETUP_DATA *SetupData);

#if defined(F81966_SMF1_SUPPORT) && (F81966_SMF1_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFan1OrData
//
// Description:    This function start to initialize the smart fan function
//
// Input:        UINT8 Index
//              UINT8 OrData8
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartFan1OrData(UINT8 Index, UINT8 OrData8)
{
  UINT8   temp;

  IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN1_INIT_TABLE[Index].Reg8 ); 
  if(F81966_FAN1_INIT_TABLE[Index].AndData8 == 0xFF) {
      temp = OrData8;
  } else {
      temp = IoRead8(F81966_HWM_DATA_PORT);
      temp &= F81966_FAN1_INIT_TABLE[Index].AndData8;
      temp |= OrData8;
  }
  IoWrite8(F81966_HWM_DATA_PORT, temp); 
}
#endif
#if defined(F81966_SMF2_SUPPORT) && (F81966_SMF2_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFan2OrData
//
// Description:    This function start to initialize the smart fan function
//
// Input:        UINT8 Index
//              UINT8 OrData8
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartFan2OrData(UINT8 Index, UINT8 OrData8)
{
  UINT8   temp;

  IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN2_INIT_TABLE[Index].Reg8 ); 
  if(F81966_FAN2_INIT_TABLE[Index].AndData8 == 0xFF) {
      temp = OrData8;
  } else {
      temp = IoRead8(F81966_HWM_DATA_PORT);
      temp &= F81966_FAN2_INIT_TABLE[Index].AndData8;
      temp |= OrData8;
  }
  IoWrite8(F81966_HWM_DATA_PORT, temp); 
}
#endif
#if defined(F81966_SMF3_SUPPORT) && (F81966_SMF3_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    SmartFan3OrData
//
// Description:    This function start to initialize the smart fan function
//
// Input:        UINT8 Index
//              UINT8 OrData8
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmartFan3OrData(UINT8 Index, UINT8 OrData8)
{
  UINT8   temp;

  IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN3_INIT_TABLE[Index].Reg8 ); 
  if(F81966_FAN3_INIT_TABLE[Index].AndData8 == 0xFF) {
      temp = OrData8;
  } else {
      temp = IoRead8(F81966_HWM_DATA_PORT);
      temp &= F81966_FAN3_INIT_TABLE[Index].AndData8;
      temp |= OrData8;
  }
  IoWrite8(F81966_HWM_DATA_PORT, temp); 
}
#endif

void F81966_FAN_Full(VOID)
{
  // Full Speed 
  // Manual Duty Mode
#if defined(F81966_SMF_SUPPORT) && (F81966_SMF_SUPPORT == 1)
  UINT8   i, temp;
#endif
  
#if defined(F81966_SMF1_SUPPORT) && (F81966_SMF1_SUPPORT == 1)
  for(i=0; i<( (sizeof(F81966_FAN1_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN1_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN1_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN1_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN1_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN1_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }  

  SmartFan1OrData(IDX_FAN_MODE, 0x03);//mode
  SmartFan1OrData(IDX_FAN_SPEED_LSB, 0xFF);
#endif

#if defined(F81966_SMF2_SUPPORT) && (F81966_SMF2_SUPPORT == 1)
  for(i=0; i<( (sizeof(F81966_FAN2_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN2_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN2_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN2_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN2_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN2_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }  

  SmartFan2OrData(IDX_FAN_MODE, 0x0C);//mode
  SmartFan2OrData(IDX_FAN_SPEED_LSB, 0xFF);
#endif

#if defined(F81966_SMF3_SUPPORT) && (F81966_SMF3_SUPPORT == 1)
  for(i=0; i<( (sizeof(F81966_FAN3_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN3_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN3_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN3_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN3_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN3_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }  

  SmartFan3OrData(IDX_FAN_MODE, 0x30);//mode
  SmartFan3OrData(IDX_FAN_SPEED_LSB, 0xFF);
#endif
}

#if defined(F81966_SMF1_SUPPORT) && (F81966_SMF1_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81966_SMF1_INIT
//
// Description:    This function do smart fan1 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void  F81966_SMF1_INIT(SETUP_DATA *SetupData)
{
  UINT8   i, temp;
  
  for(i=0; i<( (sizeof(F81966_FAN1_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN1_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN1_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN1_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN1_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN1_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }

  switch (SetupData->Fan1SmartFanMode) {
    case 0:
    // Manual RPM Mode
      SmartFan1OrData(IDX_FAN_MODE, 0x02);//mode
      SmartFan1OrData(IDX_FAN_TYPE, SetupData->Fan1OutputType); //output type
      SmartFan1OrData(IDX_FAN_SPEED_MSB, (UINT8)(1500000/SetupData->Fan1Mode0FixedSpeed >> 8));//mode
      SmartFan1OrData(IDX_FAN_SPEED_LSB, (UINT8)(1500000/SetupData->Fan1Mode0FixedSpeed & 0xFF));//mode
    break;
    case 1:
      // Manual Duty Mode
      SmartFan1OrData(IDX_FAN_MODE, 0x03);//mode
      SmartFan1OrData(IDX_FAN_TYPE, SetupData->Fan1OutputType); //output type
      SmartFan1OrData(IDX_FAN_SPEED_LSB, (UINT8)SetupData->Fan1Mode1FixedDuty*0xFF/100);//mode
    break;
    case 2:
      // Auto RPM Mode
      SmartFan1OrData(IDX_FAN_MODE, 0x00);//mode
      SmartFan1OrData(IDX_FAN_TYPE, SetupData->Fan1OutputType); //output type
      SmartFan1OrData(IDX_TEMP_HYS, 0x02); // Set hysteresis as 2
      SmartFan1OrData(IDX_TEMP_BOUND1, SetupData->Fan1Mode2AutoRpmT1);
      SmartFan1OrData(IDX_TEMP_BOUND2, SetupData->Fan1Mode2AutoRpmT2);
      SmartFan1OrData(IDX_TEMP_BOUND3, SetupData->Fan1Mode2AutoRpmT3);
      SmartFan1OrData(IDX_TEMP_BOUND4, SetupData->Fan1Mode2AutoRpmT4); 
      SmartFan1OrData(IDX_SPEED_SEG1, (UINT8)((100-SetupData->Fan1Mode2AutoRpmF1)*32/SetupData->Fan1Mode2AutoRpmF1)); 
      SmartFan1OrData(IDX_SPEED_SEG2, (UINT8)((100-SetupData->Fan1Mode2AutoRpmF2)*32/SetupData->Fan1Mode2AutoRpmF2));
      SmartFan1OrData(IDX_SPEED_SEG3, (UINT8)((100-SetupData->Fan1Mode2AutoRpmF3)*32/SetupData->Fan1Mode2AutoRpmF3));       
      SmartFan1OrData(IDX_SPEED_SEG4, (UINT8)((100-SetupData->Fan1Mode2AutoRpmF4)*32/SetupData->Fan1Mode2AutoRpmF4));  
      SmartFan1OrData(IDX_SPEED_SEG5, (UINT8)((100-SetupData->Fan1Mode2AutoRpmF5)*32/SetupData->Fan1Mode2AutoRpmF5));  
      SmartFan1OrData(IDX_TEMP_SRCSEL, SetupData->Fan1TempSrc);
    break;
    case 3:
      // Auto Duty-Cycle Mode
      SmartFan1OrData(IDX_FAN_MODE, 0x01);//mode
      SmartFan1OrData(IDX_FAN_TYPE, SetupData->Fan1OutputType); //output type
      SmartFan1OrData(IDX_TEMP_HYS, 0x02); // Set hysteresis as 2      
      SmartFan1OrData(IDX_TEMP_BOUND1, SetupData->Fan1Mode3AutoDutyT1);
      SmartFan1OrData(IDX_TEMP_BOUND2, SetupData->Fan1Mode3AutoDutyT2);
      SmartFan1OrData(IDX_TEMP_BOUND3, SetupData->Fan1Mode3AutoDutyT3);
      SmartFan1OrData(IDX_TEMP_BOUND4, SetupData->Fan1Mode3AutoDutyT4); 
      SmartFan1OrData(IDX_SPEED_SEG1, (UINT8)(SetupData->Fan1Mode3AutoDutyF1*0xFF/100)); 
      SmartFan1OrData(IDX_SPEED_SEG2, (UINT8)(SetupData->Fan1Mode3AutoDutyF2*0xFF/100)); 
      SmartFan1OrData(IDX_SPEED_SEG3, (UINT8)(SetupData->Fan1Mode3AutoDutyF3*0xFF/100)); 
      SmartFan1OrData(IDX_SPEED_SEG4, (UINT8)(SetupData->Fan1Mode3AutoDutyF4*0xFF/100));   
      SmartFan1OrData(IDX_SPEED_SEG5, (UINT8)(SetupData->Fan1Mode3AutoDutyF5*0xFF/100));   
      SmartFan1OrData(IDX_TEMP_SRCSEL, SetupData->Fan1TempSrc);
    break;
    default:
    break;
  }
}
#endif

#if defined(F81966_SMF2_SUPPORT) && (F81966_SMF2_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81966_SMF2_INIT
//
// Description:    This function do smart fan2 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void  F81966_SMF2_INIT(SETUP_DATA *SetupData)
{
  UINT8   i, temp;

  for(i=0; i<( (sizeof(F81966_FAN2_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN2_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN2_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN2_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN2_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN2_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }

  switch (SetupData->Fan2SmartFanMode) {
    case 0:
    // Manual RPM Mode
      SmartFan2OrData(IDX_FAN_MODE, (0x02 << 2));//mode
      SmartFan2OrData(IDX_FAN_TYPE, (SetupData->Fan2OutputType << 2)); //output type
      SmartFan2OrData(IDX_FAN_SPEED_MSB, (UINT8)(1500000/SetupData->Fan2Mode0FixedSpeed >> 8));//mode
      SmartFan2OrData(IDX_FAN_SPEED_LSB, (UINT8)(1500000/SetupData->Fan2Mode0FixedSpeed & 0xFF));//mode
    break;
    case 1:
      // Manual Duty Mode
      SmartFan2OrData(IDX_FAN_MODE, (0x03 << 2));//mode
      SmartFan2OrData(IDX_FAN_TYPE, (SetupData->Fan2OutputType << 2)); //output type
      SmartFan2OrData(IDX_FAN_SPEED_LSB, (UINT8)SetupData->Fan2Mode1FixedDuty*0xFF/100);//mode
    break;
    case 2:
      // Auto RPM Mode
      SmartFan2OrData(IDX_FAN_MODE, 0x00);//mode
      SmartFan2OrData(IDX_FAN_TYPE, (SetupData->Fan2OutputType << 2)); //output type
      SmartFan2OrData(IDX_TEMP_HYS, (0x02 << 4)); // Set hysteresis as 2
      SmartFan2OrData(IDX_TEMP_BOUND1, SetupData->Fan2Mode2AutoRpmT1);
      SmartFan2OrData(IDX_TEMP_BOUND2, SetupData->Fan2Mode2AutoRpmT2);
      SmartFan2OrData(IDX_TEMP_BOUND3, SetupData->Fan2Mode2AutoRpmT3);
      SmartFan2OrData(IDX_TEMP_BOUND4, SetupData->Fan2Mode2AutoRpmT4); 
      SmartFan2OrData(IDX_SPEED_SEG1, (UINT8)((100-SetupData->Fan2Mode2AutoRpmF1)*32/SetupData->Fan2Mode2AutoRpmF1)); 
      SmartFan2OrData(IDX_SPEED_SEG2, (UINT8)((100-SetupData->Fan2Mode2AutoRpmF2)*32/SetupData->Fan2Mode2AutoRpmF2));
      SmartFan2OrData(IDX_SPEED_SEG3, (UINT8)((100-SetupData->Fan2Mode2AutoRpmF3)*32/SetupData->Fan2Mode2AutoRpmF3));       
      SmartFan2OrData(IDX_SPEED_SEG4, (UINT8)((100-SetupData->Fan2Mode2AutoRpmF4)*32/SetupData->Fan2Mode2AutoRpmF4));  
      SmartFan2OrData(IDX_SPEED_SEG5, (UINT8)((100-SetupData->Fan2Mode2AutoRpmF5)*32/SetupData->Fan2Mode2AutoRpmF5));  
      SmartFan2OrData(IDX_TEMP_SRCSEL, SetupData->Fan2TempSrc);
    break;
    case 3:
      // Auto Duty-Cycle Mode
      SmartFan2OrData(IDX_FAN_MODE, (0x01 << 2));//mode
      SmartFan2OrData(IDX_FAN_TYPE, (SetupData->Fan2OutputType << 2)); //output type
      SmartFan2OrData(IDX_TEMP_HYS, (0x02 << 4)); // Set hysteresis as 2
      SmartFan2OrData(IDX_TEMP_BOUND1, SetupData->Fan2Mode3AutoDutyT1);
      SmartFan2OrData(IDX_TEMP_BOUND2, SetupData->Fan2Mode3AutoDutyT2);
      SmartFan2OrData(IDX_TEMP_BOUND3, SetupData->Fan2Mode3AutoDutyT3);
      SmartFan2OrData(IDX_TEMP_BOUND4, SetupData->Fan2Mode3AutoDutyT4); 
      SmartFan2OrData(IDX_SPEED_SEG1, (UINT8)(SetupData->Fan2Mode3AutoDutyF1*0xFF/100)); 
      SmartFan2OrData(IDX_SPEED_SEG2, (UINT8)(SetupData->Fan2Mode3AutoDutyF2*0xFF/100)); 
      SmartFan2OrData(IDX_SPEED_SEG3, (UINT8)(SetupData->Fan2Mode3AutoDutyF3*0xFF/100)); 
      SmartFan2OrData(IDX_SPEED_SEG4, (UINT8)(SetupData->Fan2Mode3AutoDutyF4*0xFF/100));   
      SmartFan2OrData(IDX_SPEED_SEG5, (UINT8)(SetupData->Fan2Mode3AutoDutyF5*0xFF/100));   
      SmartFan2OrData(IDX_TEMP_SRCSEL, SetupData->Fan2TempSrc);
    break;
    default:
    break;
  }
}
#endif

#if defined(F81966_SMF3_SUPPORT) && (F81966_SMF3_SUPPORT == 1)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81966_SMF3_INIT
//
// Description:    This function do smart fan2 config
//
// Input:        NULL
//
//
// Output:      NULL
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void  F81966_SMF3_INIT(SETUP_DATA *SetupData)
{
  UINT8   i, temp;
  
  for(i=0; i<( (sizeof(F81966_FAN3_INIT_TABLE))/(sizeof(SMF_INIT_DATA)) ); i++) {
      IoWrite8(F81966_HWM_INDEX_PORT, F81966_FAN3_INIT_TABLE[i].Reg8 ); 
      if(F81966_FAN3_INIT_TABLE[i].AndData8 == 0xFF) {
          temp = F81966_FAN3_INIT_TABLE[i].OrData8;
      } else {
          temp = IoRead8(F81966_HWM_DATA_PORT);
          temp &= F81966_FAN3_INIT_TABLE[i].AndData8;
          temp |= F81966_FAN3_INIT_TABLE[i].OrData8;
      }
      IoWrite8(F81966_HWM_DATA_PORT, temp); 
  }

  switch (SetupData->Fan3SmartFanMode) {
    case 0:
    // Manual RPM Mode
      SmartFan3OrData(IDX_FAN_MODE, (0x02 << 4));//mode
      SmartFan3OrData(IDX_FAN_TYPE, (SetupData->Fan3OutputType << 4)); //output type
      SmartFan3OrData(IDX_FAN_SPEED_MSB, (UINT8)(1500000/SetupData->Fan3Mode0FixedSpeed >> 8));//mode
      SmartFan3OrData(IDX_FAN_SPEED_LSB, (UINT8)(1500000/SetupData->Fan3Mode0FixedSpeed & 0xFF));//mode
    break;
    case 1:
      // Manual Duty Mode
      SmartFan3OrData(IDX_FAN_MODE, (0x03 << 4));//mode
      SmartFan3OrData(IDX_FAN_TYPE, (SetupData->Fan3OutputType << 4)); //output type
      SmartFan3OrData(IDX_FAN_SPEED_LSB, (UINT8)SetupData->Fan3Mode1FixedDuty*0xFF/100);//mode
    break;
    case 2:
      // Auto RPM Mode
      SmartFan3OrData(IDX_FAN_MODE, 0x00);//mode
      SmartFan3OrData(IDX_FAN_TYPE, (SetupData->Fan3OutputType << 4)); //output type
      SmartFan3OrData(IDX_TEMP_HYS, 0x02); // Set hysteresis as 2
      SmartFan3OrData(IDX_TEMP_BOUND1, SetupData->Fan3Mode2AutoRpmT1);
      SmartFan3OrData(IDX_TEMP_BOUND2, SetupData->Fan3Mode2AutoRpmT2);
      SmartFan3OrData(IDX_TEMP_BOUND3, SetupData->Fan3Mode2AutoRpmT3);
      SmartFan3OrData(IDX_TEMP_BOUND4, SetupData->Fan3Mode2AutoRpmT4); 
      SmartFan3OrData(IDX_SPEED_SEG1, (UINT8)((100-SetupData->Fan3Mode2AutoRpmF1)*32/SetupData->Fan3Mode2AutoRpmF1)); 
      SmartFan3OrData(IDX_SPEED_SEG2, (UINT8)((100-SetupData->Fan3Mode2AutoRpmF2)*32/SetupData->Fan3Mode2AutoRpmF2));
      SmartFan3OrData(IDX_SPEED_SEG3, (UINT8)((100-SetupData->Fan3Mode2AutoRpmF3)*32/SetupData->Fan3Mode2AutoRpmF3));       
      SmartFan3OrData(IDX_SPEED_SEG4, (UINT8)((100-SetupData->Fan3Mode2AutoRpmF4)*32/SetupData->Fan3Mode2AutoRpmF4));  
      SmartFan3OrData(IDX_SPEED_SEG5, (UINT8)((100-SetupData->Fan3Mode2AutoRpmF5)*32/SetupData->Fan3Mode2AutoRpmF5));  
      SmartFan3OrData(IDX_TEMP_SRCSEL, SetupData->Fan3TempSrc);
    break;
    case 3:
      // Auto Duty-Cycle Mode
      SmartFan3OrData(IDX_FAN_MODE, (0x01 << 4));//mode
      SmartFan3OrData(IDX_FAN_TYPE, (SetupData->Fan3OutputType << 4)); //output type
      SmartFan3OrData(IDX_TEMP_HYS, 0x02); // Set hysteresis as 2      
      SmartFan3OrData(IDX_TEMP_BOUND1, SetupData->Fan3Mode3AutoDutyT1);
      SmartFan3OrData(IDX_TEMP_BOUND2, SetupData->Fan3Mode3AutoDutyT2);
      SmartFan3OrData(IDX_TEMP_BOUND3, SetupData->Fan3Mode3AutoDutyT3);
      SmartFan3OrData(IDX_TEMP_BOUND4, SetupData->Fan3Mode3AutoDutyT4); 
      SmartFan3OrData(IDX_SPEED_SEG1, (UINT8)(SetupData->Fan3Mode3AutoDutyF1*0xFF/100)); 
      SmartFan3OrData(IDX_SPEED_SEG2, (UINT8)(SetupData->Fan3Mode3AutoDutyF2*0xFF/100)); 
      SmartFan3OrData(IDX_SPEED_SEG3, (UINT8)(SetupData->Fan3Mode3AutoDutyF3*0xFF/100)); 
      SmartFan3OrData(IDX_SPEED_SEG4, (UINT8)(SetupData->Fan3Mode3AutoDutyF4*0xFF/100));   
      SmartFan3OrData(IDX_SPEED_SEG5, (UINT8)(SetupData->Fan3Mode3AutoDutyF5*0xFF/100));   
      SmartFan3OrData(IDX_TEMP_SRCSEL, SetupData->Fan3TempSrc);
    break;
    default:
    break;
  }
}
#endif

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
static VOID SmartFanFuncStart(SETUP_DATA *SetupData)
{
    //--------------------------------------------------------------------------
    // Before speed control, program neccessary registers if needed.
    //--------------------------------------------------------------------------
   
    //--------------------------------------------------------------------------
    // Start to program the smart fan mode
    //--------------------------------------------------------------------------
  #if defined(F81966_SMF1_SUPPORT) && (F81966_SMF1_SUPPORT == 1)
    F81966_SMF1_INIT(SetupData);
  #endif

  #if defined(F81966_SMF2_SUPPORT) && (F81966_SMF2_SUPPORT == 1)
    F81966_SMF2_INIT(SetupData);
  #endif

  #if defined(F81966_SMF3_SUPPORT) && (F81966_SMF3_SUPPORT == 1)
    F81966_SMF3_INIT(SetupData);
  #endif
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:    F81966SmartFunction
//
// Description:    This function initializes the IT8783 in BDS phase
//
// Input:        
//      IN      EFI_HANDLE              ImageHandle
//      IN      EFI_SYSTEM_TABLE        SystemTable
//
// Output:      Status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID F81966SmartFunction (SETUP_DATA *SetupData)
{
#if defined(F81966_SMF_SUPPORT) && (F81966_SMF_SUPPORT == 1)
    //Init the smart fan function
    if(SetupData->SmartFanEnable)  
      SmartFanFuncStart(SetupData);
    else
#endif
      F81966_FAN_Full();
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

