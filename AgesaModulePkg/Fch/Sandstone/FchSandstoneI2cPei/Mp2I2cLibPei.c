/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */
#include <PiPei.h>
#include <Library/PeiServicesTablePointerLib.h>
#include "FchPlatform.h"
#include <Mp2I2cRegs.h>
#include <Mp2I2cLib.h>

VOID
CleanUpMp2Regs (
  VOID
  )
{
  UINT32 Data32;
  
  Data32 = 0;
  FchSmnWrite(0, MP2_C2PMSG_2, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_3, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_4, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_5, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_6, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_7, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_8, &Data32, NULL);
  FchSmnWrite(0, MP2_C2PMSG_9, &Data32, NULL);
  FchSmnWrite(0, MP2_P2CMSG_INTEN, &Data32, NULL);
  FchSmnRW (0, MP2_P2CMSG_INTSTS, 0, 0xf, NULL);
  FchSmnWrite(0, MP2_P2CMSG_1, &Data32, NULL);
  FchSmnWrite(0, MP2_P2CMSG_2, &Data32, NULL);  
}

EFI_STATUS
Mp2I2cRead (
 IN UINT8  BusId,
 IN UINT8  SlaveAddress,
 IN UINTN  ClockSpeed,
 IN UINT32 Length,
 IN UINT8  *Buffer
 )
{
  EFI_PEI_SERVICES         **PeiServices;
  EFI_STATUS               Status;
  AMD_MP2_I2C_CMD_REG      CmdReg;
  AMD_MP2_I2C_RESPOND_REG  ResReg;
  UINT32                   Data32, Index, TimeoutCount, RemainingLength;
  UINT32                   *I2cBuffer = NULL;
  UINT32                   *AllocatedBuffer = NULL;
  UINT32                   C2PDataBuffer[8];  

  if (Length == 0 || Buffer == NULL || BusId >= 2) {
    return EFI_INVALID_PARAMETER;
  }

  PeiServices = NULL;
  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  if (PeiServices == NULL) {
    return EFI_INVALID_PARAMETER; 
  }   
  
  // Clear I2C status register
  CleanUpMp2Regs();
  LibAmdMemFill(C2PDataBuffer, 0, sizeof(C2PDataBuffer), NULL);  
  CmdReg.Raw = 0;
  ResReg.Raw = 0;  

  CmdReg.Field.i2c_cmd = i2cRead;
  CmdReg.Field.i2cBusId = BusId;
  CmdReg.Field.devAddr = SlaveAddress;
  CmdReg.Field.length = Length;
  if (FS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;
  }
  if (SS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;    
  }
  else{
     CmdReg.Field.i2cSpeed = speed100k;    
  }  
  
  if(Length <= 32) {
    // Using C2PMSG directly.
    CmdReg.Field.memTypeI2cMode = useC2PMsg;
  } else {
    // Using DRAM. And it must be 32 bytes aligned.
    FchSmnRW (0, NBIF0EPF7CFGx00000004, 0xFFFFFFFF, 0x6, NULL);    
    if ((UINTN)Buffer & 0x1F) {
      Status = (*PeiServices)->AllocatePool(PeiServices, Length + 32, &AllocatedBuffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
      (*PeiServices)->SetMem(AllocatedBuffer, Length + 32, 0);      
      I2cBuffer = (UINT32 *)(((UINTN)AllocatedBuffer + 32) & ~0x1F);   
    } else {
      I2cBuffer = (UINT32 *)Buffer;
    }
    Data32 = (UINT32)((UINTN)I2cBuffer & 0xFFFFFFFF);
    FchSmnWrite(0, MP2_C2PMSG_2, &Data32, NULL);      
    Data32 = 0; 
    FchSmnWrite(0, MP2_C2PMSG_3, &Data32, NULL);           
    CmdReg.Field.memTypeI2cMode = useDRAM;    
  }

  // MP2 I2C Operation.
  if (BusId == 0) {
    FchSmnWrite(0, MP2_C2PMSG_0, &CmdReg.Raw, NULL);
  } else {
    FchSmnWrite(0, MP2_C2PMSG_1, &CmdReg.Raw, NULL);  
  } 
  
  //Wait for mp2 response with interrupt.   
  TimeoutCount = 10000000;
  FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
  while (Data32 == 0 && TimeoutCount > 0){
    IoRead8(0xDE);
    FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
    TimeoutCount--;
  }

  if (TimeoutCount == 0) {
    Status = EFI_NO_RESPONSE;
    goto Exit;
  }
  
  FchSmnRead(0, MP2_P2CMSG_INTSTS, &Data32, NULL);  
  if (Data32 == 0) {
    Status = EFI_NO_RESPONSE;
    goto Exit;
  }
  
  if (BusId == 0 ) {  
    FchSmnRead(0, MP2_P2CMSG_1, &ResReg.Raw, NULL);
  } else {
    FchSmnRead(0, MP2_P2CMSG_2, &ResReg.Raw, NULL);
  }
  if (ResReg.Field.response != CommandSuccess || ResReg.Field.status != I2CReadCompleteEvent) {
    Status = EFI_DEVICE_ERROR;
    goto Exit;    
  }

  if(Length <= 32) {
    RemainingLength = Length + (Length % sizeof(UINT32));
    for (Index = 0; 0 < RemainingLength; Index++) {
      FchSmnRead(0, MP2_C2PMSG_2 + Index * sizeof(UINT32), &Data32, NULL);       
      C2PDataBuffer[Index] = Data32;              
      RemainingLength -= sizeof(UINT32);      
    }     
    LibAmdMemCopy(Buffer, C2PDataBuffer, Length, NULL);         
  } else {  
    if (AllocatedBuffer != NULL) {
      LibAmdMemCopy(Buffer, I2cBuffer, Length, NULL);    
    }
  }
  
  Status = EFI_SUCCESS;
  
Exit:  
  // Clear I2C status register
  CleanUpMp2Regs();  
  return Status;
}

EFI_STATUS
Mp2I2cWrite (
 IN UINT8  BusId,
 IN UINT8  SlaveAddress,
 IN UINTN  ClockSpeed,
 IN UINT32 Length,
 IN UINT8  *Buffer
 )
{
  EFI_PEI_SERVICES         **PeiServices;
  EFI_STATUS               Status;
  AMD_MP2_I2C_CMD_REG      CmdReg;
  AMD_MP2_I2C_RESPOND_REG  ResReg;
  UINT32                   Data32, Index, TimeoutCount, RemainingLength;
  UINT32                   *I2cBuffer = NULL;
  UINT32                   *AllocatedBuffer = NULL;
  UINT32                   C2PDataBuffer[8];

  if (Length == 0 || Buffer == NULL || BusId >= 2) {
    return EFI_INVALID_PARAMETER;
  }

  PeiServices = NULL;
  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  if (PeiServices == NULL) {
    return EFI_INVALID_PARAMETER; 
  }       
  
  // Clear I2C status register
  CleanUpMp2Regs();
  LibAmdMemFill(C2PDataBuffer, 0, sizeof(C2PDataBuffer), NULL);
  CmdReg.Raw = 0;
  ResReg.Raw = 0;  

  CmdReg.Field.i2c_cmd = i2cWrite;
  CmdReg.Field.i2cBusId = BusId;
  CmdReg.Field.devAddr = SlaveAddress;
  CmdReg.Field.length = Length;
  if (FS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;
  }
  if (SS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;    
  }
  else{
     CmdReg.Field.i2cSpeed = speed100k;    
  }  
  
  if(Length <= 32) {
    // Using C2PMSG directly.
    LibAmdMemCopy(C2PDataBuffer, Buffer, Length, NULL);
    RemainingLength = Length + (Length % sizeof(UINT32));    
    for (Index = 0; 0 < RemainingLength; Index++) {
      FchSmnWrite(0, MP2_C2PMSG_2 + Index * sizeof(UINT32), &C2PDataBuffer[Index], NULL);          
      RemainingLength -= sizeof(UINT32);
    }  
    CmdReg.Field.memTypeI2cMode = useC2PMsg;
  } else {
    // Pass the data to MP2 from DRAM. And it must be 32 bytes aligned.
    FchSmnRW (0, NBIF0EPF7CFGx00000004, 0xFFFFFFFF, 0x4, NULL);     
    if ((UINTN)Buffer & 0x1F) {
      Status = (*PeiServices)->AllocatePool(PeiServices, Length + 32, &AllocatedBuffer);
      if (EFI_ERROR(Status)) {
        return Status;
      }
      LibAmdMemFill(AllocatedBuffer, 0, Length + 32, NULL);
      I2cBuffer = (UINT32 *)(((UINTN)AllocatedBuffer + 32) & ~0x1F);
      LibAmdMemCopy(I2cBuffer, Buffer, Length, NULL);    
    } else {
      I2cBuffer = (UINT32 *)Buffer;
    }
    Data32 = (UINT32)((UINTN)I2cBuffer & 0xFFFFFFFF);
    FchSmnWrite(0, MP2_C2PMSG_2, &Data32, NULL);    
    Data32 = 0;
    FchSmnWrite(0, MP2_C2PMSG_3, &Data32, NULL);            
    CmdReg.Field.memTypeI2cMode = useDRAM;    
  }

  // MP2 I2C Operation.
  if (BusId == 0) {
    FchSmnWrite(0, MP2_C2PMSG_0, &CmdReg.Raw, NULL);
  } else {
    FchSmnWrite(0, MP2_C2PMSG_1, &CmdReg.Raw, NULL);
  }

  //Wait for mp2 response with interrupt.
  TimeoutCount = 10000000;
  FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
  while (Data32 == 0 && TimeoutCount > 0) {
    IoRead8(0xDE);
    FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
    TimeoutCount--;
  }

  if (TimeoutCount == 0) {
    Status = EFI_NO_RESPONSE;
    goto Exit;
  }
  
  FchSmnRead(0, MP2_P2CMSG_INTSTS, &Data32, NULL);
  if (Data32 == 0) {
    Status = EFI_NO_RESPONSE;
    goto Exit;
  }
  
  if (BusId == 0 ) {  
    FchSmnRead(0, MP2_P2CMSG_1, &ResReg.Raw, NULL);
  } else {
    FchSmnRead(0, MP2_P2CMSG_2, &ResReg.Raw, NULL);
  }
  if (ResReg.Field.response != CommandSuccess || ResReg.Field.status != I2CWriteCompleteEvent) {
    Status = EFI_DEVICE_ERROR;
    goto Exit;    
  }
  
  Status = EFI_SUCCESS;    
  
Exit:  
  // Clear I2C status register
  CleanUpMp2Regs();  
  return Status;
}


EFI_STATUS
Mp2SetBusFrequency (
  IN UINT8  BusId,
  IN UINTN  ClockSpeed
  )
{
  AMD_MP2_I2C_CMD_REG     CmdReg;
  AMD_MP2_I2C_RESPOND_REG ResReg;
  UINTN                   TimeoutCount;
  UINT32                  Data32;
  
  if (BusId >= 2) {
    return EFI_INVALID_PARAMETER;
  }  
  
  // Clear I2C status register
  CleanUpMp2Regs();
  CmdReg.Raw = 0;
  ResReg.Raw = 0;
  
  CmdReg.Field.i2cBusId = BusId;
  CmdReg.Field.i2c_cmd  = i2cEnable;  
  if (FS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;
     Data32 = FS_SPEED;
  }
  if (SS_SPEED < ClockSpeed) {
     CmdReg.Field.i2cSpeed = speed400k;    
     Data32 = FS_SPEED;
  }
  else{
     CmdReg.Field.i2cSpeed = speed100k;    
     Data32 = SS_SPEED;
  }  

  // MP2 I2C transction  
  FchSmnWrite(0, MP2_C2PMSG_2, &Data32, NULL);
  if (BusId == 0) {
    FchSmnWrite(0, MP2_C2PMSG_0, &CmdReg.Raw, NULL);
  } else {
    FchSmnWrite(0, MP2_C2PMSG_1, &CmdReg.Raw, NULL);
  }   

  //Read I2C status
  TimeoutCount = 10000000;
  FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
  while (Data32 == 0 && TimeoutCount > 0){
    IoRead8(0xDE);
    FchSmnRead(0, MP2_P2CMSG_INTEN, &Data32, NULL);
    TimeoutCount--;
  }

  if (TimeoutCount == 0) {
    return EFI_NO_RESPONSE;
  }
  FchSmnRead(0, MP2_P2CMSG_INTSTS, &Data32, NULL);
  if (Data32 == 0) {
    return EFI_NO_RESPONSE;
  }
  
  FchSmnRead(0, MP2_P2CMSG_0, &ResReg.Raw, NULL);
  if (ResReg.Field.response != CommandSuccess || ResReg.Field.status != I2CBusEnableComplete) {
    return EFI_DEVICE_ERROR;
  }

  CleanUpMp2Regs();  
  return EFI_SUCCESS;
}

