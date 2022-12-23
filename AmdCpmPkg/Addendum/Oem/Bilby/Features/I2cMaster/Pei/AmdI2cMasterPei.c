/*****************************************************************************
 *
 * Copyright 2015 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 ******************************************************************************
 */
/*++
Module Name:

  AmdI2cMasterPei.c
  Init I2cMaster interface

Abstract:
--*/

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Ppi/I2cMaster.h>
#include <DwI2cRegs.h>
#include "AmdI2cMasterPei.h"
#include <Fch.h>

#define  I2C2_D3_DevCtrl7   7 
#define  I2C3_D3_DevCtrl8   8

/*++

Routine Description:

  I2C Master Driver Entry. Publish I2c Master Ppi

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdI2cMasterPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  AMD_PEI_I2C_MASTER_PRIVATE *I2cPrivate;
  EFI_PEI_PPI_DESCRIPTOR    *PpiListI2c;
  EFI_I2C_CONTROLLER_CAPABILITIES *I2cControllerCapabilities;
  UINT32 Index;

  //
  // Create the PPIs
  //
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (AMD_PEI_I2C_MASTER_PRIVATE),
                             &I2cPrivate
                             );
  ASSERT_EFI_ERROR (Status);

  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_I2C_CONTROLLER_CAPABILITIES),
                             &I2cControllerCapabilities
                             );
  ASSERT_EFI_ERROR (Status);

  //Init I2C cotroller capabilities data structure
  I2cControllerCapabilities->StructureSizeInBytes = sizeof (EFI_I2C_CONTROLLER_CAPABILITIES);
  I2cControllerCapabilities->MaximumReceiveBytes = 0xFFFFFFFF;
  I2cControllerCapabilities->MaximumTransmitBytes = 0xFFFFFFFF;
  I2cControllerCapabilities->MaximumTotalBytes = 0xFFFFFFFF;

  for (Index = 0; Index < I2C_CONTROLLER_COUNT; Index++) {
     I2cPrivate->I2cMasterPpi[Index].PeiServices                      = (EFI_PEI_SERVICES **)PeiServices;
     I2cPrivate->I2cMasterPpi[Index].I2cSdpAddress                    = I2cSdpAddressList[Index];
     I2cPrivate->I2cMasterPpi[Index].I2cPpi.SetBusFrequency           = SetBusFrequency;
     I2cPrivate->I2cMasterPpi[Index].I2cPpi.Reset                     = Reset;
     I2cPrivate->I2cMasterPpi[Index].I2cPpi.StartRequest              = StartRequest;
     I2cPrivate->I2cMasterPpi[Index].I2cPpi.I2cControllerCapabilities = I2cControllerCapabilities;
     CopyGuid(&I2cPrivate->I2cMasterPpi[Index].I2cPpi.Identifier, &AmdI2cMasterID);
     I2cInit (&I2cPrivate->I2cMasterPpi[Index]);
  }

  //
  // Install the PPIs
  //
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             (sizeof (EFI_PEI_PPI_DESCRIPTOR) * I2C_CONTROLLER_COUNT),
                             &PpiListI2c
                             );

  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < I2C_CONTROLLER_COUNT; Index++) {
     //
     // Create the PPI descriptor
     //
     PpiListI2c[Index].Guid  = &gEfiPeiI2cMasterPpiGuid;
     PpiListI2c[Index].Ppi   = &(I2cPrivate->I2cMasterPpi[Index].I2cPpi);

     if (Index != (I2C_CONTROLLER_COUNT - 1)) {
        PpiListI2c[Index].Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI);
     }
     else {
        PpiListI2c[Index].Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
     }
  }

  //
  // Publish the PPI
  //
  Status = (*PeiServices)->InstallPpi (
                             PeiServices,
                             PpiListI2c
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
  IN EFI_PEI_I2C_MASTER_PPI   *This,
  IN UINTN                    *BusClockHertz
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  I2CMASTER_PPI_PRIVATE *Private;
  UINT32 settings = 0;
  UINT32 Base;
  UINT32 hcnt;
  UINT32 lcnt;

  Private = (I2CMASTER_PPI_PRIVATE*)This;
  Base = Private->I2cSdpAddress;

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
  } else if (SS_SPEED < *BusClockHertz) {
     settings |= DW_I2C_CON_SPEED_FS;
     *BusClockHertz = FS_SPEED;        //Return actually clock setting
  }
  else {
     settings |= DW_I2C_CON_SPEED_SS;
     *BusClockHertz = SS_SPEED;        //Return actually clock setting
  }

  settings |= DW_I2C_CON_IC_RESTART_EN;

  MmioWrite32(Base + DW_IC_CON, settings);

  // Setup spike suppression for SS and FS at 50ns
  MmioWrite32(Base + DW_IC_FS_SPKLEN, configI2C_FS_GLITCH_FILTER);

  // Setup spike suppression for HS at 10ns
  MmioWrite32(Base + DW_IC_FS_SPKLEN, configI2C_FS_GLITCH_FILTER);

  /* Standard-mode 100Khz*/
  // hcnt = i2c_dw_scl_hcnt(configI2C_CLOCK_HZ,
  //                         40,     /* tHD;STA = tHIGH = 4.0 us */
  //                         3,      /* tf = 0.3 us */
  //                         0,      /* 0: DW default, 1: Ideal */
  //                         0);     /* No offset */
  // lcnt = i2c_dw_scl_lcnt(configI2C_CLOCK_HZ,
  //                         47,     /* tLOW = 4.7 us */
  //                         3,      /* tf = 0.3 us */
  //                         0);     /* No offset */

  hcnt = 0x2D7;
  lcnt = 0x2D7;

  MmioWrite32(Base + DW_IC_SS_SCL_HCNT, hcnt); /* std speed high, 4us */
  MmioWrite32(Base + DW_IC_SS_SCL_LCNT, lcnt); /* std speed low, 4.7us */
  MmioWrite32(Base + DW_IC_SDA_HOLD, 0x38);

  DEBUG((EFI_D_ERROR, "Standard-mode HCNT:LCNT = %d:%d\n", hcnt, lcnt));

  /* Fast-mode 400Khz*/
  // hcnt = i2c_dw_scl_hcnt(configI2C_CLOCK_HZ,
  //                         6,      /* tHD;STA = tHIGH = 0.6 us */
  //                         3,      /* tf = 0.3 us */
  //                         0,      /* 0: DW default, 1: Ideal */
  //                         0);     /* No offset */
  // lcnt = i2c_dw_scl_lcnt(configI2C_CLOCK_HZ,
  //                         13,     /* tLOW = 1.3 us */
  //                         3,      /* tf = 0.3 us */
  //                         0);     /* No offset */

  hcnt = 0xA6;
  lcnt = 0xA6;

  MmioWrite32(Base + DW_IC_FS_SCL_HCNT, hcnt);
  MmioWrite32(Base + DW_IC_FS_SCL_LCNT, lcnt);
  MmioWrite32(Base + DW_IC_HS_SCL_HCNT, hcnt);
  MmioWrite32(Base + DW_IC_HS_SCL_LCNT, lcnt);

  DEBUG((EFI_D_ERROR, "Fast-mode HCNT:LCNT = %d:%d\n", hcnt, lcnt));

  return Status;
}

EFI_STATUS
EFIAPI
Reset (
   IN CONST EFI_PEI_I2C_MASTER_PPI  *This
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
StartRequest (
   IN CONST EFI_PEI_I2C_MASTER_PPI     *This,
   IN UINTN                            SlaveAddress,
   IN EFI_I2C_REQUEST_PACKET           *RequestPacket
  )
{
   EFI_STATUS    Status = EFI_SUCCESS;

   Status = I2cAccess((I2CMASTER_PPI_PRIVATE*)This, SlaveAddress, RequestPacket);

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
   UINT32 I2cPollTime = (100 * 1000000) / configI2C_MAX_SPEED;

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
  UINT32 I2cPollTime = (100 * 1000000) / configI2C_MAX_SPEED;

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
  UINT32 I2cPollTime = (100 * 1000000) / configI2C_MAX_SPEED;

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
   UINT32 I2cPollTime = (100 * 1000000) / configI2C_MAX_SPEED;

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

EFI_STATUS
I2cInit(
   IN OUT I2CMASTER_PPI_PRIVATE    *Private
   )
{
  EFI_STATUS Status;
  UINT32 Base = Private->I2cSdpAddress;
  UINTN BusClockHertz;
  I2C_CONFIGURATION * configuration = &Private->I2cConfiguration;
  UINT8 Index;
  
  Index = (UINT8) (((Base >> 12) & 0x0F) + 3);  // AOAC I2C Device Index
  if ( Index == I2C2_D3_DevCtrl7 || Index == I2C3_D3_DevCtrl8) {  // Enable I2C2 I2C3 
    if ((MmioRead8 (FCH_AOACx40_D3_CONTROL + (Index << 1)) & 3) == 0x3) { //Checking if Device in D3Cold
      MmioAnd8 ((FCH_AOACx40_D3_CONTROL + (Index << 1)), 0xFC);  // Clear Bit[1:0] TargetedDeviceState.
      MmioOr8 ((FCH_AOACx40_D3_CONTROL + (Index << 1)), AOAC_PWR_ON_DEV);   // Set Bit[3] PwrOnDev 
      do {
         //check Device status in 'AOAC Device D3 State' register
      } while ((MmioRead8 ((FCH_AOACx40_D3_CONTROL +1) + (Index << 1)) & 7) != 7);
    }
  }

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
  Status= SetBusFrequency(&Private->I2cPpi, &BusClockHertz);
  return Status;
}

/**
  This function sets the target address for device on I2C bus
  @param Chip - Address of I2C device
  @retval EFI_STATUS
*/

EFI_STATUS
I2cSetTarget(
   IN  UINT32    Chip,
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
       I2cPollTime = (100 * 1000000) / configI2C_MAX_SPEED;
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
  IN OUT I2CMASTER_PPI_PRIVATE    *Private
)
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINT32   Base;
   UINT32   TxFifoCount;
   UINT32   RxFifoCount;
   UINT32   Index;

   Base = Private->I2cSdpAddress;  // For convenience

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
   IN     I2CMASTER_PPI_PRIVATE     *Private,
   IN     UINTN                     SlaveAddress,
   IN OUT EFI_I2C_REQUEST_PACKET    *RequestPacket
)
{
  BOOLEAN     IsWriteOperation;
  UINT32      Base = Private->I2cSdpAddress;
  EFI_STATUS  Status = EFI_SUCCESS;

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
      return EFI_INVALID_PARAMETER;
    }
  }
  Private->TransferCount = Private->ReadCount + Private->WriteCount;

  //Set target device slave address
  if (I2cSetTarget(SlaveAddress, Private->I2cSdpAddress) != EFI_SUCCESS) {
    return EFI_DEVICE_ERROR;
  }

  Status = I2cWriteRead(Private);

  // Disable the interface
  DEBUG((EFI_D_ERROR, "9 : disable I2C interface\n"));
  MmioWrite32(Base + DW_IC_ENABLE, 0);
  I2cDwWaitI2cEnable(Base, CHECK_IC_EN_HIGH);  //Wait controller status change

  return Status;
}
