/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/xGbEI2cMaster.h>
#include <DwI2cRegs.h>
#include "xGbEI2cMasterDxe.h"

extern  EFI_BOOT_SERVICES       *gBS;

//
// Driver Global Data
//

/*********************************************************************************
 * Name: xGbEI2cMasterDxeInit
 *
 * Description
 *   Entry point of the XGBE I2C Master DXE driver
 *   Perform the configuration init, resource reservation, early post init
 *   and install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
xGbEI2cMasterDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle;
  XGBE_I2CMASTER_PRIVATE *I2cPrivate;

  Status = gBS->AllocatePool (EfiBootServicesData, sizeof (XGBE_I2CMASTER_PRIVATE), &I2cPrivate);
  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    //clear instances content
    gBS->SetMem (I2cPrivate, sizeof (XGBE_I2CMASTER_PRIVATE), 0);
  }

  Handle = ImageHandle;

  I2cPrivate->I2cController.BaseAddress               = 0;
  I2cPrivate->I2cController.SetBusFrequency           = SetBusFrequency;
  I2cPrivate->I2cController.I2cInit                   = I2cInit;
  I2cPrivate->I2cController.StartRequest              = StartRequest;
//  I2cInit (I2cPrivate);

  // Install Protocol
  Status = gBS->InstallProtocolInterface (
                &I2cPrivate->Handle,
                &gxGbEI2cMasterProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &I2cPrivate->I2cController
                );

  return (Status);
}

static
UINT32
i2c_dw_scl_hcnt(UINT32 ic_clk, UINT32 tSYMBOL, UINT32 tf, UINT32 cond, UINT32 offset)
{
       if (cond)
               /*
                * Conditional expression:
                *
                *   IC_[FS]S_SCL_HCNT + (1+4+3) >= IC_CLK * tHIGH
                *
                * This is based on the DW manuals, and representing an
                * ideal configuration.  The resulting I2C bus speed will
                * be faster than any of the others.
                *
                * If your hardware is free from tHD;STA issue, try this one.
                */
               return (ic_clk * tSYMBOL + 5000) / 10000 - 8 + offset;
       else
               /*
                * Conditional expression:
                *
                *   IC_[FS]S_SCL_HCNT + 3 >= IC_CLK * (tHD;STA + tf)
                *
                * This is just experimental rule; the tHD;STA period turned
                * out to be proportinal to (_HCNT + 3).  With this setting,
                * we could meet both tHIGH and tHD;STA timing specs.
                *
                * If unsure, you'd better to take this alternative.
                *
                * The reason why we need to take into account "tf" here,
                * is the same as described in i2c_dw_scl_lcnt().
                */
               return (ic_clk * (tSYMBOL + tf) + 5000) / 10000 - 3 + offset;
}

static
UINT32
i2c_dw_scl_lcnt(UINT32 ic_clk, UINT32 tLOW, UINT32 tf, UINT32 offset)
{
       /*
        * Conditional expression:
        *
        *   IC_[FS]S_SCL_LCNT + 1 >= IC_CLK * (tLOW + tf)
        *
        * DW I2C core starts counting the SCL CNTs for the LOW period
        * of the SCL clock (tLOW) as soon as it pulls the SCL line.
        * We need to take into account tf to meet the tLOW timing spec.
        * Default tf value should be 0.3 us, for safety.
        */
       return ((ic_clk * (tLOW + tf) + 5000) / 10000) - 1 + offset;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function use for change AGESA configuration parameter PCD for multiplatform support.
 *
 * It will prepare AGESA configuration group list and return to SOC driver.
 * then the SOC driver will update the PCD value based on the list provide by this function.
 *
 * @param[in]   PeiServices
 * @param[in]   SocId
 * @param[out]  PlalformGroupGuid
 *
 */
EFI_STATUS
EFIAPI
SetBusFrequency (
  IN CONST XGBE_I2C_MASTER_PROTOCOL   *This,
  IN UINTN                    *BusClockHertz
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  XGBE_I2CMASTER_PRIVATE *Private;
  UINT32 settings = 0;
  UINT32 Base;
  UINT32 hcnt;
  UINT32 lcnt;

  Private = (XGBE_I2CMASTER_PRIVATE*)This;
  Base = Private->I2cController.BaseAddress;

  // Disable the interface
  MmioWrite32(Base + DW_IC_ENABLE, 0);
  if (I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH)) {
     return EFI_NOT_READY;
  }

  settings |= DW_I2C_CON_MASTER_MODE | DW_I2C_CON_IC_SLAVE_DISABLE;

  if (FS_SPEED < *BusClockHertz) {
     settings |= DW_I2C_CON_SPEED_HS;
     *BusClockHertz = FS_SPEED;        //Return actually clock setting
//     *BusClockHertz = HS_SPEED;
  }
  if (SS_SPEED < *BusClockHertz) {
     settings |= DW_I2C_CON_SPEED_FS;
     *BusClockHertz = FS_SPEED;        //Return actually clock setting
  } 
  else{
     settings |= DW_I2C_CON_SPEED_SS;
     *BusClockHertz = SS_SPEED;        //Return actually clock setting
  }

  settings |= DW_I2C_CON_IC_RESTART_EN;

  MmioWrite32(Base + DW_IC_CON, settings);

  // Setup spike suppression for SS and FS 
  MmioWrite32(Base + DW_IC_FS_SPKLEN, configXGBEI2C_FS_GLITCH_FILTER);

  // Setup spike suppression for HS at 10ns
  MmioWrite32(Base + DW_IC_HS_SPKLEN, configI2C_HS_GLITCH_FILTER);

  /* Standard-mode 100Khz*/
  hcnt = i2c_dw_scl_hcnt(configI2C_CLOCK_HZ,
                          40,     /* tHD;STA = tHIGH = 4.0 us */
                          3,      /* tf = 0.3 us */
                          0,      /* 0: DW default, 1: Ideal */
                          0);     /* No offset */
  lcnt = i2c_dw_scl_lcnt(configI2C_CLOCK_HZ,
                          47,     /* tLOW = 4.7 us */
                          3,      /* tf = 0.3 us */
                          0);     /* No offset */
						  
  //PLAT-42040 -  Set hcnt and lcnt same (0x866) for 50% duty cycle	
  hcnt 	= 0x866;  // 0x1E8 for Standard Speed
  lcnt  = 0x866;

  MmioWrite32(Base + DW_IC_SS_SCL_HCNT, hcnt); /* std speed high, 4us */
  MmioWrite32(Base + DW_IC_SS_SCL_LCNT, lcnt); /* std speed low, 4.7us */
  MmioWrite32(Base + DW_IC_SDA_HOLD, 0xAB); 

  DEBUG((EFI_D_ERROR, "Standard-mode HCNT:LCNT = %d:%d\n", hcnt, lcnt));

  /* Fast-mode 400Khz*/
  hcnt = i2c_dw_scl_hcnt(configI2C_CLOCK_HZ,
                          6,      /* tHD;STA = tHIGH = 0.6 us */
                          3,      /* tf = 0.3 us */
                          0,        /* 0: DW default, 1: Ideal */
                          0);       /* No offset */
  lcnt = i2c_dw_scl_lcnt(configI2C_CLOCK_HZ,
                          13,     /* tLOW = 1.3 us */
                          3,      /* tf = 0.3 us */
                          0);     /* No offset */
						  
  //PLAT-42040 -  Set hcnt and lcnt same (0x20A) for 50% duty cycle	
  hcnt 	= 0x20A;  // 0x72 for high Speed
  lcnt  = 0x20A;

  MmioWrite32(Base + DW_IC_FS_SCL_HCNT, hcnt);
  MmioWrite32(Base + DW_IC_FS_SCL_LCNT, lcnt);
  MmioWrite32(Base + DW_IC_HS_SCL_HCNT, hcnt);
  MmioWrite32(Base + DW_IC_HS_SCL_LCNT, lcnt);

  DEBUG((EFI_D_ERROR, "Fast-mode HCNT:LCNT = %d:%d\n", hcnt, lcnt));

  return Status;
}

EFI_STATUS
EFIAPI
I2cInit(
   IN CONST XGBE_I2C_MASTER_PROTOCOL *This
   )
{
  EFI_STATUS Status;
  XGBE_I2CMASTER_PRIVATE *Private;
  UINT32 Base;
  UINTN BusClockHertz;
  I2C_CONFIGURATION * configuration;

  Private = (XGBE_I2CMASTER_PRIVATE*)This;
  configuration = &Private->I2cConfiguration;
  Base = Private->I2cController.BaseAddress;

  DEBUG((DEBUG_INFO, "I2cInit Base = %x\n", Base));

  // Disable the interface
  MmioWrite32(Base + DW_IC_ENABLE, 0);
  if (I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH)) {
     return EFI_NOT_READY;
  }

  //Mask Interrupt and Clear interrupt status
  MmioWrite32(Base + DW_IC_INTR_MASK, 0);
  (void)MmioRead32(Base + DW_IC_CLR_INTR);
  (void)MmioRead32(Base + DW_IC_CLR_TX_ABRT);

  configuration->RxFifoDepth = ((MmioRead32(Base + DW_IC_COMP_PARAM_1) & DW_I2C_RX_BUFFER_DEPTH_MASK) >> DW_I2C_RX_BUFFER_DEPTH_SHIFT) + 1;
  configuration->TxFifoDepth = ((MmioRead32(Base + DW_IC_COMP_PARAM_1) & DW_I2C_TX_BUFFER_DEPTH_MASK) >> DW_I2C_TX_BUFFER_DEPTH_SHIFT) + 1;

  //Set default to Standard Speed
  BusClockHertz = SS_SPEED;
  Status= SetBusFrequency(&Private->I2cController, &BusClockHertz);
  return Status;
}

EFI_STATUS
EFIAPI
StartRequest (
   IN CONST XGBE_I2C_MASTER_PROTOCOL    *This,
   IN UINTN                            SlaveAddress,
   IN EFI_I2C_REQUEST_PACKET           *RequestPacket,
   IN EFI_EVENT                        Event      OPTIONAL,
   OUT EFI_STATUS                      *I2cStatus OPTIONAL
  )
{
   EFI_STATUS    Status = EFI_SUCCESS;

   DEBUG((DEBUG_INFO, "StartRequest SlaveAddress = %x\n", SlaveAddress));
   I2cAccess((XGBE_I2CMASTER_PRIVATE*)This, SlaveAddress, RequestPacket);

  return Status;
}

/**
  This function checks for errors during SMBUS access

  @param Base - Base address of I2C controller

  @retval EFI_STATUS
*/

UINT32
I2cDwCheckErrors(
   IN  UINT32   Base
)
{
   UINT32 I2cStatusCnt = DW_STATUS_WAIT_RETRY;
   UINT32 TxAbrt = 0;
   UINT32 Status = MmioRead32(Base + DW_IC_RAW_INTR_STAT);
   UINT32 I2cPollTime = (100 * 1000000) / SS_SPEED;

   if (Status & DW_IC_INTR_RX_UNDER)
       MmioRead32(Base + DW_IC_CLR_RX_UNDER);

   if (Status & DW_IC_INTR_RX_OVER)
       MmioRead32(Base + DW_IC_CLR_RX_OVER);

   if (Status & DW_IC_INTR_TX_ABRT) {
       Status = MmioRead32(Base + DW_IC_TX_ABRT_SOURCE);
       MmioRead32(Base + DW_IC_CLR_TX_ABRT);
       DEBUG((EFI_D_ERROR, "I2C: TX_ABORT Error\n"));
   }

   if (Status & DW_IC_ERR_CONDITION) {
       if (Status || TxAbrt)
           DEBUG((EFI_D_ERROR, "Errors on I2C bus %08x %08x: \n", Status, TxAbrt));

       MmioWrite32(Base + DW_IC_ENABLE, 0); // Disable the adapter
       I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH);  //Wait controller status change
       do {
           MicroSecondDelay(I2cPollTime);
           if (I2cStatusCnt == 0)
               DEBUG((EFI_D_ERROR, "I2C: Timeout during disable \n"));
       } while (((MmioRead32(Base + DW_IC_ENABLE_STATUS) & 0x01)) && I2cStatusCnt--);
       MmioWrite32(Base + DW_IC_TAR, 0); // Clear Target address
   }

   return (Status & DW_IC_ERR_CONDITION);
}


/**
  This function waits for bus to not be busy
  @param Base - Base address of I2C controller
  @retval TRUE - Timeout while waiting for not busy
  @retval FALSE - Bus is not busy
*/

BOOLEAN
I2cDwWaitBusNotBusy(
   IN  UINT32   Base
)
{
   INTN Timeout = DW_BUS_WAIT_TIMEOUT;

   while (MmioRead32(Base + DW_IC_STATUS) & 0x20) {
       if (Timeout <= 0) {
           DEBUG((EFI_D_ERROR, "I2C: Timeout waiting for bus ready\n"));
           return TRUE;
       }
   Timeout--;
   MicroSecondDelay(1000);
   }
   return FALSE;
}

/**
  This function waits for the TX FIFO to be available
  @param Base - Base address of I2C controller
  @retval EFI_STATUS
*/

EFI_STATUS
I2cDwWaitTxData(
   IN  UINT32   Base
)
{
  INTN Timeout = DW_TX_DATA_RETRY;
  UINT32 I2cPollTime = (100 * 1000000) / SS_SPEED;

  while (0 == (MmioRead32(Base + DW_IC_STATUS) & DW_I2C_STATUS_TFE)) {
    if (Timeout <= 0) {
      DEBUG((EFI_D_ERROR, "I2C: Timeout waiting for Tx Fifo full empty \n"));
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(I2cPollTime);
  }
  DEBUG((EFI_D_ERROR, "I2C_STATUS : %x, Tx timeout remaining : %d of %d\n", MmioRead32(Base + DW_IC_STATUS), Timeout, DW_TX_DATA_RETRY));
  return EFI_SUCCESS;
}

EFI_STATUS
I2cDwWaitRxData(
   IN  UINT32   Base,
   IN  UINT32   RxFifoDepth
)
{
  INTN Timeout = DW_TX_DATA_RETRY;
  UINT32 I2cPollTime = (100 * 1000000) / SS_SPEED;

  while (MmioRead32(Base + DW_IC_RXFLR) < RxFifoDepth) {
    if (Timeout <= 0) {
      DEBUG((EFI_D_ERROR, "I2C: Timeout waiting for Rx data ready\n"));
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(I2cPollTime);
  }
  DEBUG((EFI_D_ERROR, "I2C_STATUS : %x, Rx timeout remaining : %d of %d\n", MmioRead32(Base + DW_IC_STATUS), Timeout, DW_TX_DATA_RETRY));
  return EFI_SUCCESS;
}

/**
  This function waits for the TX FIFO to be available
  @param Base - Base address of I2C controller
  @retval EFI_STATUS
*/

EFI_STATUS
I2cDwWaitI2cEnable(
   IN  UINT32   Base,
   IN  UINT32   I2cEnBit
)
{
   INTN Timeout = DW_STATUS_WAIT_RETRY;
   UINT32 I2cPollTime = (100 * 1000000) / SS_SPEED;

   while (I2cEnBit == (MmioRead32(Base + DW_IC_ENABLE_STATUS) & DW_I2C_EN_STATUS_IC_EN)) {
       if (Timeout <= 0) {
           DEBUG((EFI_D_ERROR, "I2C: Timeout waiting for I2C Enable : %x\n", (MmioRead32(Base + DW_IC_ENABLE_STATUS))));
           return EFI_TIMEOUT;
       }
   Timeout--;
   MicroSecondDelay(I2cPollTime);
   }
   return EFI_SUCCESS;
}

/**
  This function sets the target address for device on I2C bus
  @param Chip - Address of I2C device
  @retval EFI_STATUS
*/

EFI_STATUS
I2cSetTarget(
   IN  UINT32   Chip,
   IN  UINT32   Base
)
{
   UINT32 I2cStatusCnt;
   UINT32 I2cPollTime;
   EFI_STATUS Status = EFI_SUCCESS;

   if (MmioRead32(Base + DW_IC_TAR) != Chip) {
       MmioWrite32(Base + DW_IC_ENABLE, 0); // Disable the Controller
       if (I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH)) {
          return EFI_NOT_READY;
       }
       I2cPollTime = (100 * 1000000) / SS_SPEED;
       I2cStatusCnt = DW_STATUS_WAIT_RETRY;

       do {
           MicroSecondDelay(I2cPollTime);
           if (I2cStatusCnt == 0) {
               DEBUG((EFI_D_ERROR, "I2C Set Target: Timeout during disable\n"));
               MmioWrite32(Base + DW_IC_TAR, 0); // Clear Target Address
               Status = EFI_DEVICE_ERROR;
               return Status;
           }
       } while (((MmioRead32(Base + DW_IC_ENABLE_STATUS) & 0x01)) && I2cStatusCnt--);

       MmioWrite32(Base + DW_IC_TAR, Chip); // Set Target Address
       DEBUG((EFI_D_ERROR, "I2C Target Set - Chip Address:%x\n", Chip));
       I2cStatusCnt = DW_STATUS_WAIT_RETRY;
       MmioWrite32(Base + DW_IC_ENABLE, 1); // Enable the Controller
       I2cDwWaitI2cEnable(Base, CHECK_IC_EN_LOW);  //Check IC_EN bit
       do {
           MicroSecondDelay(I2cPollTime);
           if (I2cStatusCnt == 0) {
               DEBUG((EFI_D_ERROR, "I2C Set Target: Timeout during enable\n"));
               MmioWrite32(Base + DW_IC_TAR, 0); // Clear Target Address
               Status = EFI_DEVICE_ERROR;
               return Status;
           }
       } while ((!(MmioRead32(Base + DW_IC_ENABLE_STATUS) & 0x01)) && I2cStatusCnt--);

       if (MmioRead32(Base + DW_IC_TAR) != Chip) {
           DEBUG((EFI_D_ERROR, "Cannot set the target on I2c bus to %x\n", Chip));
           Status = EFI_INVALID_PARAMETER;
       }
   }
   return Status;
}

EFI_STATUS
I2cWriteRead(
  IN OUT XGBE_I2CMASTER_PRIVATE    *Private
)
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINT32   Base;
   UINT32   TxFifoCount;
   UINT32   RxFifoCount;
   UINT32   Index;

   Base = Private->I2cController.BaseAddress;  // For convenience

   if (I2cDwWaitBusNotBusy(Base)) {
       return EFI_NOT_READY;
   }

   MmioWrite32(Base + DW_IC_INTR_MASK, 0);
   (void)MmioRead32(Base + DW_IC_CLR_INTR);

   DEBUG((EFI_D_ERROR, "1 : Enable I2C interface\n"));
   // Enable the interface
   MmioWrite32(Base + DW_IC_ENABLE, DW_I2C_ENABLE);
   if (I2cDwWaitI2cEnable(Base, CHECK_IC_EN_LOW)) {
      return EFI_NOT_READY;
   }

#if 0
 // If both RX and TX counts are zero then just ping the device with a read
 if (0 == Private->TransferCount)
 Private->TransferCount = 1;
#endif

  // Load up the TX FIFO
  if (0 < Private->TransferCount) {
    while (0 < Private->WriteCount) {
      TxFifoCount = (Private->I2cConfiguration.TxFifoDepth < Private->WriteCount) ? Private->I2cConfiguration.TxFifoDepth : Private->WriteCount;
      DEBUG((EFI_D_ERROR, "2 : Load up the TX FIFO, TxFifofDepth: %d\n", TxFifoCount));
      for (Index = 0; Index < TxFifoCount ; Index++) {
        if ((Private->TransferCount == 1) && (Private->ReadCount == 0)) {
          DEBUG((EFI_D_ERROR, "Write Data: 0x%x\n", *(Private->WriteData)));
          MmioWrite32(Base + DW_IC_DATA_CMD, (*(Private->WriteData++) & DW_I2C_DATA_MASK) | DW_I2C_DATA_STOP);
        }
        else {
          DEBUG((EFI_D_ERROR, "Write Data: 0x%x\n", *(Private->WriteData)));
          MmioWrite32(Base + DW_IC_DATA_CMD, *(Private->WriteData++) & DW_I2C_DATA_MASK);
        }
        Private->WriteCount--;
        Private->TransferCount--;
      }
      DEBUG((EFI_D_ERROR, "3 : Wait for TxFifo empty\n"));
      //Wait for TxFifo empty
      Status = I2cDwWaitTxData(Base);
      if (Status) {
        //Transcation failed, send STOP command to free the bus
		DEBUG((EFI_D_ERROR, "Wait for TxFifo empty failed\n"));
        MmioWrite32(Base + DW_IC_DATA_CMD, DW_I2C_DATA_STOP);
        return Status;
      }
    }
  }
  DEBUG((EFI_D_ERROR, "Write Count : %d, Transfer Count : %d\n", Private->WriteCount, Private->TransferCount));

  if (0 < Private->TransferCount) {
    DEBUG((EFI_D_ERROR, "4 : Start Read trasaction\n"));

    while (0 < Private->ReadCount) {
      RxFifoCount = (Private->I2cConfiguration.RxFifoDepth < Private->ReadCount) ? Private->I2cConfiguration.RxFifoDepth : Private->ReadCount;
      DEBUG((EFI_D_ERROR, "5 : fille up Rx Fifo, RxFifoDepth : %d\n", RxFifoCount));
      // Fill up Rx Fifo
      for (Index = 0; Index < RxFifoCount ; Index++) {
          if (Private->ReadCount == 1) {
              MmioWrite32(Base + DW_IC_DATA_CMD, DW_I2C_DATA_CMD | DW_I2C_DATA_STOP);
          }
          else {
              MmioWrite32(Base + DW_IC_DATA_CMD, DW_I2C_DATA_CMD);
          }
          Private->ReadCount--;
          Private->TransferCount--;
      }
      DEBUG((EFI_D_ERROR, "6 : Wait Rx data ready \n"));
      // Waiting for Rx data ready
      Status = I2cDwWaitRxData(Base, RxFifoCount);
      if (Status) {
          //Transcation failed, send STOP command to free the bus
		  DEBUG((EFI_D_ERROR, "Rx data Transcation failed  \n"));
          MmioWrite32(Base + DW_IC_DATA_CMD, DW_I2C_DATA_STOP);
         return Status;
      }
      DEBUG((EFI_D_ERROR, "7 : Read data from Rxfifo\n"));
      for (Index = 0; Index < RxFifoCount; Index++) {
        if (I2cDwCheckErrors(Base)) {
          MmioWrite32(Base + DW_IC_DATA_CMD, DW_I2C_DATA_STOP);
          return EFI_DEVICE_ERROR;
        }
        *(Private->ReadData++) = (UINT8)(MmioRead32(Base + DW_IC_DATA_CMD) & DW_I2C_DATA_MASK); // Receive data unit from RxFifo
      }
      *(Private->ReadData++) = MmioRead32(Base + DW_IC_DATA_CMD) & DW_I2C_DATA_MASK;
      DEBUG((EFI_D_ERROR, "Read Count : %d, Transfer Count : %d\n", Private->ReadCount, Private->TransferCount));
    }
  }

  // Transaction complete
  DEBUG((EFI_D_ERROR, "8 : transaction complete\n"));

  return EFI_SUCCESS;
}

EFI_STATUS
I2cAccess(
   IN     XGBE_I2CMASTER_PRIVATE    *Private,
   IN     UINTN                     SlaveAddress,
   IN OUT EFI_I2C_REQUEST_PACKET    *RequestPacket
)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  BOOLEAN     IsWriteOperation;
  UINT32      Base = Private->I2cController.BaseAddress;

  //No PEC, ProcessCall and BlkProcessCall support
  if (RequestPacket->Operation[0].Flags & (I2C_FLAG_SMBUS_PEC | I2C_FLAG_SMBUS_PROCESS_CALL)) {
    Status = EFI_UNSUPPORTED;
    return Status;
  }

  //No QuickRead & QuickWrite
  if (0 == RequestPacket->Operation[0].LengthInBytes) {
    Status = EFI_UNSUPPORTED;
    return Status;
  }

  if (RequestPacket->OperationCount == 1) {
    if (RequestPacket->Operation[0].Flags & I2C_FLAG_READ) {
      //command READ
      Private->ReadCount = RequestPacket->Operation[0].LengthInBytes;
      Private->ReadData = RequestPacket->Operation[0].Buffer;
      Private->WriteCount = 0;
      Private->WriteData = NULL;
    }
    else {
      //command WRITE
      Private->ReadCount = 0;
      Private->ReadData = NULL;
      Private->WriteCount = RequestPacket->Operation[0].LengthInBytes;
      Private->WriteData = RequestPacket->Operation[0].Buffer;
    }
  }
  else if (RequestPacket->OperationCount == 2) {
    IsWriteOperation = (RequestPacket->Operation[1].Flags & I2C_FLAG_READ) ? FALSE : TRUE;
    if (RequestPacket->Operation[1].Flags & I2C_FLAG_READ) {
      //ReceviedByte
      Private->ReadCount = RequestPacket->Operation[1].LengthInBytes;
      Private->ReadData = RequestPacket->Operation[1].Buffer;
      Private->WriteCount = RequestPacket->Operation[0].LengthInBytes;
      Private->WriteData = RequestPacket->Operation[0].Buffer;
    }
    else {
      //only READ operation has two OperationCount
      Status = EFI_INVALID_PARAMETER;
      return Status;			
    }
  }
  Private->TransferCount = Private->ReadCount + Private->WriteCount;

  //Set target device slave address
  if (I2cSetTarget((UINT32)SlaveAddress, Private->I2cController.BaseAddress) != EFI_SUCCESS) {
    Status = EFI_DEVICE_ERROR;
    return Status;		
  }

  Status = I2cWriteRead(Private);

  // Disable the interface
  DEBUG((EFI_D_ERROR, "9 : disable I2C interface\n"));
  MmioWrite32(Base + DW_IC_ENABLE, 0);
  I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH);  //Wait controller status change

  return Status;
}
