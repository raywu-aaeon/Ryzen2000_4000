/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#include <AmdCpmPei.h>

#ifndef AGESA_V9
  #include EFI_PPI_DEFINITION (AmdInitResetPpi)
  #include EFI_PPI_DEFINITION (AgesaMemPpi)
#else
  #include EFI_PPI_DEFINITION (NbioPcieTrainingPpi)
#endif

//extern EFI_GUID gEfiPeiPromotoryGpioPpiGuid;
EFI_GUID  gEfiPeiPromotoryGpioPpiGuid = { 0x31859c50, 0x2845, 0x42da, {0x9f, 0x37, 0xe7, 0x18, 0x67, 0xe3, 0xe0, 0x5e } };

VOID
AmdCpmGpioDeviceInit (
  IN      AMD_CPM_TABLE_PPI           *CpmTablePpiPtr,
  IN      UINT8                       InitFlag
  );

EFI_STATUS
AmdCpmGpioDeviceInitStage2 (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );

EFI_STATUS
EFIAPI
AmdCpmGpioInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

EFI_STATUS
EFIAPI
AmdCpmPtGpioInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

EFI_STATUS
EFIAPI
AmdCpmGpioInitPeimNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

#ifndef AGESA_V9
STATIC EFI_PEI_NOTIFY_DESCRIPTOR mAmdCpmGpioInitStage1PeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPeiInitResetPpiGuid,
  AmdCpmGpioInitPeim
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mAmdCpmGpioInitStage2PeimNotify =
{
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gAgesaMemPpiGuid,
  AmdCpmGpioDeviceInitStage2
};

#else
STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mAmdCpmGpioInitPeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmOverrideTablePpiGuid,
  AmdCpmGpioInitPeimNotifyCallback
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  mAmdCpmGpioInitStage2PeimNotify =
{
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gAmdNbioPcieTrainingDonePpiGuid,
  AmdCpmGpioDeviceInitStage2
};
#endif

AMD_CPM_INIT_FLAG_TABLE gCpmInitFlagTable = {
  {CPM_SIGNATURE_INIT_FLAG, sizeof (gCpmInitFlagTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
};

AMD_CPM_PT_GPIO_DEVICE_STAGE1_INIT_TABLE gCpmPtGpioStage1Table = {
  {CPM_SIGNATURE_PT_GPIO_DEVICE_STAGE1_INIT, sizeof (gCpmPtGpioStage1Table) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpmPtGpioInitPeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiPromotoryGpioPpiGuid,
  AmdCpmPtGpioInitPeim
};

/*----------------------------------------------------------------------------------------*/
/**
 * Init Promontory GPIO pins
 *
 * This function initializes Promontory GPIO Device
 * after AGESA FCH Promotory Gpio PPI is installed.
 *
 * @param[in]     PeiServices       Pointer to Pei Services
 * @param[in]     NotifyDescriptor  The descriptor for the notification event
 * @param[in]     Ppi               Pointer to the PPI in question.
 *
 * @retval        EFI_SUCCESS       Module initialized successfully
 * @retval        EFI_ERROR         Initialization failed (see error for more details)
 *
 */
EFI_STATUS
AmdCpmPtGpioInitPeim (
  IN  EFI_PEI_SERVICES          **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN  VOID                      *Ppi
  )
{
  EFI_STATUS                                Status;
  AMD_CPM_TABLE_PPI                         *CpmTablePtr;
  AMD_CPM_PT_GPIO_INIT_TABLE                *PtTablePtr;
  Promontory_GPIO_COMMON_SETTING            *PtGpioTablePtr;
  AMD_CPM_PT_GPIO_DEVICE_STAGE1_INIT_TABLE  *PtGpioStage1Ptr;
  EFI_PT_GPIO_PPI                           *PtGpioPpi;
  UINT8                                     Type;
  UINT8                                     Index;

  Status = (*PeiServices)->LocatePpi (
            (CPM_PEI_SERVICES**)PeiServices,
            &gAmdCpmTablePpiGuid,
            0,
            NULL,
            (VOID**)&CpmTablePtr
            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CpmTablePtr) {
    PtTablePtr = CpmTablePtr->CommonFunction.GetTablePtr (CpmTablePtr, CPM_SIGNATURE_PT_GPIO_INIT);

    if (PtTablePtr) {

      PtGpioTablePtr = (void *)&(PtTablePtr->GpioCommon);
      Status = (*PeiServices)->LocatePpi (
                (CPM_PEI_SERVICES**)PeiServices,
                &gEfiPeiPromotoryGpioPpiGuid,
                0,
                NULL,
                (VOID**)&PtGpioPpi
                );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Status = PtGpioPpi->PTInitiialGpio (
                PeiServices,
                PtGpioTablePtr
                );
      if (EFI_ERROR (Status)) {
        return Status;
      }

      PtGpioStage1Ptr = CpmTablePtr->CommonFunction.GetTablePtr (CpmTablePtr, CPM_SIGNATURE_PT_GPIO_DEVICE_STAGE1_INIT);
      if (PtGpioStage1Ptr) {
        for (Index = 0; Index < AMD_PT_GPIO_DEVICE_INIT_SIZE; Index ++) {
          Type = PtGpioStage1Ptr->DeviceInitList[Index].Type;
          if (Type == 0xFF) {
            break;
          }
          switch (Type) {
          case CPM_POWER_SET:
            CpmTablePtr->CommonFunction.SetGpio (
                                CpmTablePtr,
                                PtGpioStage1Ptr->DeviceInitList[Index].Config.Gpio.Pin,
                                PtGpioStage1Ptr->DeviceInitList[Index].Config.Gpio.Value
                                );
            break;
          case CPM_POWER_WAIT:
            while (CpmTablePtr->CommonFunction.GetGpio (CpmTablePtr, PtGpioStage1Ptr->DeviceInitList[Index].Config.Gpio.Pin) !=
                   PtGpioStage1Ptr->DeviceInitList[Index].Config.Gpio.Value) {
            }
            break;
          case CPM_PT_POWER_DELAY:
            CpmTablePtr->CommonFunction.Stall (CpmTablePtr, PtGpioStage1Ptr->DeviceInitList[Index].Config.Stall);
            break;
          }
        } // End of for (Index = 0; Index < AMD_PT_GPIO_DEVICE_INIT_SIZE; Index ++)
      } // End of if (PtGpioStage1Ptr)
    } // End of if (PtTablePtr)
  } // End of if (CpmTablePtr)
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * CPM GPIO Device Init Stage 2
 *
 * This function initializes GPIO Device in stage 2
 * after AGESA MEM PPI is installed.
 *
 * @param[in]     PeiServices    Pointer to Pei Services
 * @param[in]     NotifyDesc     The descriptor for the notification event
 * @param[in]     InvokePpi      Pointer to the PPI in question.
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 *
 */
EFI_STATUS
AmdCpmGpioDeviceInitStage2 (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
  EFI_STATUS                  Status;
  AMD_CPM_TABLE_PPI           *CpmTablePtr;

  RECORD_TIME_PEI (BeginAmdCpmGpioInitStage2);

  Status = (*PeiServices)->LocatePpi (
                              (CPM_PEI_SERVICES**)PeiServices,
                              &gAmdCpmTablePpiGuid,
                              0,
                              NULL,
                              (VOID**)&CpmTablePtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CpmTablePtr->CommonFunction.LoadPreInitTable (CpmTablePtr, CPM_PRE_INIT_STAGE_2);

  AmdCpmGpioDeviceInit (CpmTablePtr, GPIO_DEVICE_INIT_STAGE_2);

  RECORD_TIME_PEI (EndAmdCpmGpioInitStage2);

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to init GPIO pins
 *
 * @param[in]     CpmTablePpiPtr  Pointer to AMD CPM Table Ppi
 *
 */

VOID
AmdCpmPeiGpioInit (
  IN      AMD_CPM_TABLE_PPI       *CpmTablePpiPtr
  )
{
  AMD_CPM_GPIO_INIT_TABLE         *GpioTablePtr;
  AMD_CPM_GPIO_ITEM               *TablePtr;

  if (CpmTablePpiPtr) {
    GpioTablePtr     = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_INIT);

    if (GpioTablePtr) {
      TablePtr = &GpioTablePtr->GpioList[0];
      while (TablePtr->Pin != 0xFF ) {
        CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, TablePtr->Pin, TablePtr->Setting.Raw);
        TablePtr++;
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to pre-process GPIO Device tables
 *
 * @param[in]     CpmTablePpiPtr    Pointer to AMD CPM Table Ppi
 * @param[in]     ConfigTablePtr    Pointer to AMD CPM GPIO Device Config Table
 * @param[in]     PowerTablePtr     Pointer to AMD CPM GPIO Device Power Table
 * @param[in]     DetectionTablePtr Pointer to AMD CPM GPIO Device Detection Table
 * @param[in]     ResetTablePtr     Pointer to AMD CPM GPIO Device Reset Table
 * @param[in]     InitFlagTablePtr  Pointer to AMD CPM Init Flag Table
 * @param[in]     InitFlag          Init Flag
 *
 */

UINT32
CpmGpioDevicePreInit (
  IN      AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr,
  IN      AMD_CPM_GPIO_DEVICE_CONFIG_TABLE    *ConfigTablePtr,
  IN      AMD_CPM_GPIO_DEVICE_POWER_TABLE     *PowerTablePtr,
  IN      AMD_CPM_GPIO_DEVICE_DETECTION_TABLE *DetectionTablePtr,
  IN      AMD_CPM_GPIO_DEVICE_RESET_TABLE     *ResetTablePtr,
  IN      AMD_CPM_INIT_FLAG_TABLE             *InitFlagTablePtr,
  IN      UINT8                               InitFlag
  )
{
  AMD_CPM_GPIO_DEVICE_CONFIG          *TablePtr;
  UINT8                               Index;
  UINT32                              ResetStall;
  UINT8                               GpioDeviceId;

  ResetStall = 0;
  if (ConfigTablePtr) {
    if (InitFlag <= GPIO_DEVICE_INIT_STAGE_1) {
      for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
        if (ResetTablePtr && InitFlagTablePtr) {
          InitFlagTablePtr->ResetInitFlag[Index] = ResetTablePtr->DeviceResetList[Index].InitFlag;
        }
      }
      for (Index = 0; Index < AMD_GPIO_DEVICE_POWER_SIZE; Index ++) {
        if (PowerTablePtr && InitFlagTablePtr) {
          InitFlagTablePtr->PowerInitFlag[Index] = PowerTablePtr->DevicePowerList[Index].InitFlag;
        }
      }
      TablePtr = &ConfigTablePtr->DeviceList[0];
      while (TablePtr->DeviceId != 0xFF && TablePtr->DeviceId != 0x00) {
        if (CpmTablePpiPtr && TablePtr->Config.Setting.Enable == 2) {
          TablePtr->Config.Setting.Enable = CpmTablePpiPtr->CommonFunction.DetectDevice (CpmTablePpiPtr, TablePtr->DeviceId, NULL);
        }
        if (ResetTablePtr && TablePtr->Config.Setting.Enable < 2) {
          for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
            GpioDeviceId = ResetTablePtr->DeviceResetList[Index].DeviceId;
            if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
              break;
            }
            if (InitFlagTablePtr && GpioDeviceId == TablePtr->DeviceId) {
              if (ResetTablePtr->DeviceResetList[Index].Mode == 0) {
                if ((InitFlagTablePtr->ResetInitFlag[Index] <= GPIO_DEVICE_INIT_STAGE_1) || !(TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetAssert)) {
                  InitFlagTablePtr->ResetInitFlag[Index] = TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetAssert;
                }
              } else if (ResetTablePtr->DeviceResetList[Index].Mode == 1) {
                if ((InitFlagTablePtr->ResetInitFlag[Index] <= GPIO_DEVICE_INIT_STAGE_1) || !(TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetDeassert)) {
                  InitFlagTablePtr->ResetInitFlag[Index] = TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetDeassert;
                }
              } else if (ResetTablePtr->DeviceResetList[Index].Mode == 2) {
                if ((InitFlagTablePtr->ResetInitFlag[Index] <= GPIO_DEVICE_INIT_STAGE_1) || !(TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetDeassert)) {
                  InitFlagTablePtr->ResetInitFlag[Index] = TablePtr->Config.Setting.Enable & TablePtr->Config.Setting.ResetDeassert;
                }
              }
            }
          }
        }
        if (PowerTablePtr && TablePtr->Config.Setting.Enable < 2) {
          for (Index = 0; Index < AMD_GPIO_DEVICE_POWER_SIZE; Index ++) {
            GpioDeviceId = PowerTablePtr->DevicePowerList[Index].DeviceId;
            if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
              break;
            }
            if (InitFlagTablePtr && GpioDeviceId == TablePtr->DeviceId) {
              if (PowerTablePtr->DevicePowerList[Index].Mode == TablePtr->Config.Setting.Enable) {
                if (InitFlagTablePtr->PowerInitFlag[Index] <= GPIO_DEVICE_INIT_STAGE_1) {
                  InitFlagTablePtr->PowerInitFlag[Index] = 1;
                }
              } else {
                InitFlagTablePtr->PowerInitFlag[Index] = 0;
              }
            }
          }
        }
        TablePtr++;
      }
    }
    if (ResetTablePtr) {
      for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
        GpioDeviceId = ResetTablePtr->DeviceResetList[Index].DeviceId;
        if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
          break;
        }
        if (ResetTablePtr->DeviceResetList[Index].Mode == 2 && InitFlagTablePtr->ResetInitFlag[Index] == InitFlag) {
          ResetStall = ResetTablePtr->DeviceResetList[Index].Config.Stall;
        }
      }
    }
  }
  return ResetStall;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to toggle one GPIO pin to reset the device
 *
 * @param[in]     CpmTablePpiPtr  Pointer to AMD CPM Table Ppi
 * @param[in]     ResetItemPtr    Pointer to AMD CPM GPIO Device Reset item.
 *
 */

VOID
CpmGpioDeviceReset (
  IN      AMD_CPM_TABLE_PPI           *CpmTablePpiPtr,
  IN      AMD_CPM_GPIO_DEVICE_RESET   *ResetItemPtr
  )
{
  if (CpmTablePpiPtr && ResetItemPtr) {
    switch (ResetItemPtr->Type) {
    case 0:
      CpmTablePpiPtr->CommonFunction.SetGpio (
                                              CpmTablePpiPtr,
                                              ResetItemPtr->Config.Gpio.Pin,
                                              ResetItemPtr->Config.Gpio.Value
                                             );
      break;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to init on-board device.
 *
 * @param[in]     CpmTablePpiPtr  Pointer to AMD CPM Table Ppi
 * @param[in]     InitFlag        Init flag. 1: In stage1 2. In Stage2
 *
 */

VOID
AmdCpmGpioDeviceInit (
  IN      AMD_CPM_TABLE_PPI       *CpmTablePpiPtr,
  IN      UINT8                   InitFlag
  )
{
  AMD_CPM_GPIO_DEVICE_CONFIG_TABLE    *ConfigTablePtr;
  AMD_CPM_GPIO_DEVICE_POWER_TABLE     *PowerTablePtr;
  AMD_CPM_GPIO_DEVICE_DETECTION_TABLE *DetectionTablePtr;
  AMD_CPM_GPIO_DEVICE_RESET_TABLE     *ResetTablePtr;
  AMD_CPM_INIT_FLAG_TABLE             *InitFlagTablePtr;
  AMD_CPM_PT_GPIO_DEVICE_STAGE1_INIT_TABLE  *PtGpioStage1Ptr;
  UINT8                               Index;
  UINT32                              ResetStall;
  UINT8                               GpioDeviceId;
  UINT8                               PtIndex;

  if (CpmTablePpiPtr) {
    ConfigTablePtr      = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_CONFIG);
    PowerTablePtr       = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_POWER);
    DetectionTablePtr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_DETECTION);
    ResetTablePtr       = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_RESET);

    PtIndex = 0;
    if (InitFlag == GPIO_DEVICE_INIT_STAGE_1) {
      InitFlagTablePtr  = CpmTablePpiPtr->CommonFunction.AddTable (CpmTablePpiPtr, &gCpmInitFlagTable);
      PtGpioStage1Ptr   = CpmTablePpiPtr->CommonFunction.AddTable (CpmTablePpiPtr, &gCpmPtGpioStage1Table);
      PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
    } else {
      InitFlagTablePtr  = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_INIT_FLAG);
      PtGpioStage1Ptr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PT_GPIO_DEVICE_STAGE1_INIT);
    }
    ResetStall = CpmGpioDevicePreInit (CpmTablePpiPtr, ConfigTablePtr, PowerTablePtr, DetectionTablePtr, ResetTablePtr, InitFlagTablePtr, InitFlag);

    if (ResetTablePtr && PtGpioStage1Ptr) {
      for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
        GpioDeviceId = ResetTablePtr->DeviceResetList[Index].DeviceId;
        if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
          break;
        }
        if (InitFlagTablePtr->ResetInitFlag[Index] == InitFlag) {
          switch (ResetTablePtr->DeviceResetList[Index].Mode) {
          case CPM_RESET_ASSERT:
            if ((InitFlag == GPIO_DEVICE_INIT_STAGE_1) && ((ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin & 0x300) == 0x300)) {
              // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = CPM_POWER_SET;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Pin   = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Value = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Value;
              PtIndex++;
              if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
                DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmGpioDeviceInit-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
                PtIndex--;
              }
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
            } else {
              CpmGpioDeviceReset (CpmTablePpiPtr, &ResetTablePtr->DeviceResetList[Index]);
            }
            break;
          }
        }
      }
    }
    if (PowerTablePtr && PtGpioStage1Ptr) {
      for (Index = 0; Index < AMD_GPIO_DEVICE_POWER_SIZE; Index ++) {
        GpioDeviceId = PowerTablePtr->DevicePowerList[Index].DeviceId;
        if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
          break;
        }
        if (InitFlagTablePtr->PowerInitFlag[Index] == InitFlag) {
          switch (PowerTablePtr->DevicePowerList[Index].Type) {
          case CPM_POWER_SET:
            if ((InitFlag == GPIO_DEVICE_INIT_STAGE_1) && ((PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin & 0x300) == 0x300)) {
              // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = CPM_POWER_SET;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Pin   = PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Value = PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Value;
              PtIndex++;
              if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
                DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmGpioDeviceInit-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
                PtIndex--;
              }
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
            } else {
              CpmTablePpiPtr->CommonFunction.SetGpio (
                                CpmTablePpiPtr,
                                PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin,
                                PowerTablePtr->DevicePowerList[Index].Config.SetGpio.Value
                              );
            }
            break;
          case CPM_POWER_WAIT:
            if ((InitFlag == GPIO_DEVICE_INIT_STAGE_1) && ((PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Pin & 0x300) == 0x300)) {
              // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = CPM_POWER_WAIT;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Pin   = PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Pin;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Value = PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Value;
              PtIndex++;
              if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
                DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmGpioDeviceInit-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
                PtIndex--;
              }
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
            } else {
              while (CpmTablePpiPtr->CommonFunction.GetGpio (
                                CpmTablePpiPtr,
                                PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Pin
                              ) != PowerTablePtr->DevicePowerList[Index].Config.WaitGpio.Value) {
              }
            }
            break;
          case CPM_POWER_DELAY:
            CpmTablePpiPtr->CommonFunction.Stall (CpmTablePpiPtr, PowerTablePtr->DevicePowerList[Index].Config.Stall);
            break;
          case CPM_PT_POWER_DELAY:
            if (InitFlag == GPIO_DEVICE_INIT_STAGE_1) {
              // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = CPM_PT_POWER_DELAY;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Stall = PowerTablePtr->DevicePowerList[Index].Config.Stall;
              PtIndex++;
              if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
                DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmGpioDeviceInit-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
                PtIndex--;
              }
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
            }
            break;
          }
        }
      }
    }
    if (ResetTablePtr && PtGpioStage1Ptr) {
      CpmTablePpiPtr->CommonFunction.Stall (CpmTablePpiPtr, ResetStall);
      for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
        GpioDeviceId = ResetTablePtr->DeviceResetList[Index].DeviceId;
        if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
          break;
        }
        if (InitFlagTablePtr->ResetInitFlag[Index] == InitFlag) {
          switch (ResetTablePtr->DeviceResetList[Index].Mode) {
          case CPM_RESET_DEASSERT:
            if ((InitFlag == GPIO_DEVICE_INIT_STAGE_1) && ((ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin & 0x300) == 0x300)) {
              // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = CPM_POWER_SET;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Pin   = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin;
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Value = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Value;
              PtIndex++;
              if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
                DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmGpioDeviceInit-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
                PtIndex--;
              }
              PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
            } else {
              CpmGpioDeviceReset (CpmTablePpiPtr, &ResetTablePtr->DeviceResetList[Index]);
            }
            break;
          }
        }
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to reset on-board device.
 *
 * @param[in]     This          Pointer to AMD CPM Table Ppi
 * @param[in]     ResetId       Device Id of on-board device
 * @param[in]     ResetControl  Reset Control Flag. 0: Reset assert. 1: Reset deassert
 */

VOID
AmdCpmResetDevice (
  IN      VOID                        *This,
  IN      UINT8                       ResetId,
  IN      UINT8                       ResetControl
  )
{
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr = This;
  AMD_CPM_GPIO_DEVICE_RESET_TABLE     *ResetTablePtr;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  AMD_CPM_PT_GPIO_DEVICE_STAGE1_INIT_TABLE  *PtGpioStage1Ptr;
  UINT8                               Index;
  UINT8                               GpioDeviceId;
  UINT8                               PtIndex;

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimResetDeviceBegin);

  MainTablePtr  = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  ResetTablePtr = 0;
  PtGpioStage1Ptr = 0;
  if (CpmTablePpiPtr->MainTablePtr->Header.TableSignature == CPM_SIGNATURE_MAIN_TABLE) {
    ResetTablePtr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_DEVICE_RESET);
    PtGpioStage1Ptr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PT_GPIO_DEVICE_STAGE1_INIT);
  } else {
    CpmTablePpiPtr->CommonFunction.PostCode (CpmTpErrorMainTablePointerInvalid);
    DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmResetDevice-CPM_DEADLOOP\n"));
    CPM_DEADLOOP ();
  }

  PtIndex = 0;
  if (PtGpioStage1Ptr) {
    while (PtGpioStage1Ptr->DeviceInitList[PtIndex].Type != 0xFF && PtIndex <= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
      PtIndex++;
    }
  }

  if (ResetTablePtr && PtGpioStage1Ptr) {
    for (Index = 0; Index < AMD_GPIO_DEVICE_RESET_SIZE; Index ++) {
      GpioDeviceId = ResetTablePtr->DeviceResetList[Index].DeviceId;
      if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
        break;
      }
      if ((GpioDeviceId == ResetId) && (ResetTablePtr->DeviceResetList[Index].Mode == ResetControl)) {
        if (((UINT32)MainTablePtr->PtBrMemIoBaseAddr == 0) && ((ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin & 0x300) == 0x300)) {
          // Use PT GPIO: PT is not ready, save in PtGpioStage1 Table
          PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0;
          PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Pin   = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Pin;
          PtGpioStage1Ptr->DeviceInitList[PtIndex].Config.Gpio.Value = ResetTablePtr->DeviceResetList[Index].Config.Gpio.Value;
          PtIndex++;
          if (PtIndex >= AMD_PT_GPIO_DEVICE_INIT_SIZE) {
            DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmResetDevice-ERROR ERROR ERROR ERROR ERROR PtIndex overflow\n"));
            PtIndex--;
          }
          PtGpioStage1Ptr->DeviceInitList[PtIndex].Type = 0xFF;
        } else {
          CpmGpioDeviceReset (CpmTablePpiPtr, &ResetTablePtr->DeviceResetList[Index]);
        }
        break;
      }
    }
  }
  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimResetDeviceEnd);
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set Memory Voltage
 *
 * This function sets GPIO pins to control memory volatge according to memory modules to
 * be plugged in.
 *
 * @param[in]     This      Pointer to AMD CPM Table Ppi
 * @param[in]     Voltage   Memory voltage to be set. 1: 1.5 Volt. 2: 1.35 Volt. 3: 1.25 Volt
 *
 */

VOID
AmdCpmSetMemVoltage (
  IN      VOID                        *This,
  IN      UINT8                       Voltage
  )
{
  AMD_CPM_GPIO_MEM_VOLTAGE_TABLE      *TablePtr;
  UINT8                               Index;
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;
#ifdef AMD_BIOS_BOOT_TIME_RECORD
  EFI_PEI_SERVICES                    **PeiServices;
  PeiServices = (EFI_PEI_SERVICES**) ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr->Service.Pointer;
#endif

  RECORD_TIME_PEI (BeginAmdCpmSetMemVoltage);

  CpmTablePpiPtr = This;
  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimSetMemVoltageBegin);

  TablePtr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_SET_MEM_VOLTAGE);
  if (TablePtr) {
    for (Index = 0; Index < AMD_GPIO_MEM_VOLTAGE_SIZE; Index++) {
      if (TablePtr->Item[Index].Voltage == 0xFF) {
        break;
      } else if (TablePtr->Item[Index].Voltage == Voltage) {
        if (TablePtr->Item[Index].GpioPin1 != 0xFF) {
          CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, TablePtr->Item[Index].GpioPin1, TablePtr->Item[Index].Value1);
        }
        if (TablePtr->Item[Index].GpioPin2 != 0xFF) {
          CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, TablePtr->Item[Index].GpioPin2, TablePtr->Item[Index].Value2);
        }
      }
    }
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimSetMemVoltageEnd);
  RECORD_TIME_PEI (EndAmdCpmSetMemVoltage);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set VDDP/VDDR Voltage
 *
 * This function sets GPIO pins to control VDDP/VDDR volatge according to the fuse value
 *
 * @param[in]     This      Pointer to AMD CPM Table Ppi
 * @param[in]     VddpVddrVoltage VDDP/VDDR voltage to be set. 0: 0.95 Volt. 1: 1.05 Volt.
 *
 */

VOID
AmdCpmSetVddpVddrVoltage (
  IN      VOID                        *This,
  IN      VDDP_VDDR_VOLTAGE           VddpVddrVoltage
  )
{
  AMD_CPM_GPIO_VDDP_VDDR_VOLTAGE_TABLE  *TablePtr;
  UINT8                                 Index;
  AMD_CPM_TABLE_PPI                     *CpmTablePpiPtr;

  CpmTablePpiPtr = This;
  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimSetVddpVddrVoltageBegin);

  TablePtr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_SET_VDDP_VDDR_VOLTAGE);
  if (TablePtr && VddpVddrVoltage.IsValid) {
    for (Index = 0; Index < AMD_GPIO_VDDP_VDDR_VOLTAGE_SIZE; Index++) {
      if (TablePtr->Item[Index].Voltage == 0xFF) {
        break;
      } else if (TablePtr->Item[Index].Voltage == VddpVddrVoltage.Voltage) {
        if (TablePtr->Item[Index].GpioPin1 != 0xFF) {
          CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, TablePtr->Item[Index].GpioPin1, TablePtr->Item[Index].Value1);
        }
      }
    }
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimSetVddpVddrVoltageEnd);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * CPM External ClkGen Init
 *
 * This function initializes external Clock Generator in early post
 *
 * @param[in]     CpmTablePpiPtr  Pointer to AMD CPM Table Ppi
 *
 */

VOID
AmdCpmPeiExtClkGenInit (
  IN      AMD_CPM_TABLE_PPI       *CpmTablePpiPtr
  )
{
  AMD_CPM_EXT_CLKGEN_TABLE        *ExtClkGenTablePtr;
  AMD_CPM_EXT_CLKGEN_ITEM         *TablePtr;
  UINT8                           Data;

  if (!(CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT1)) {
    ExtClkGenTablePtr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_EXT_CLKGEN);
    if (ExtClkGenTablePtr) {
      TablePtr = &ExtClkGenTablePtr->Item[0];
      while (TablePtr->Function != 0xFF ) {
        if (TablePtr->Function == CpmTablePpiPtr->MainTablePtr->ExtClkGen) {
          CpmTablePpiPtr->CommonFunction.ReadSmbusBlock (
                                                  CpmTablePpiPtr,
                                                  ExtClkGenTablePtr->SmbusSelect,
                                                  ExtClkGenTablePtr->SmbusAddress,
                                                  TablePtr->Offset,
                                                  1,
                                                  &Data
                                                  );
          Data = (Data & TablePtr->AndMask) | TablePtr->OrMask;
          CpmTablePpiPtr->CommonFunction.WriteSmbusBlock (
                                                  CpmTablePpiPtr,
                                                  ExtClkGenTablePtr->SmbusSelect,
                                                  ExtClkGenTablePtr->SmbusAddress,
                                                  TablePtr->Offset,
                                                  1,
                                                  &Data
                                                  );
        }
        TablePtr++;
      }
    }
  }
}

VOID
AmdCpmPeiAddOneItemInClkList (
  IN      AMD_CPM_EXT_CLKGEN_TABLE    *ExtClkGenTablePtr,
  IN      AMD_CPM_EXT_CLKGEN_ITEM     *ListPtr,
  IN      UINT8                       *ListNum,
  IN      UINT8                       ClkNum,
  IN      UINT8                       ClkReq
  )
{
  AMD_CPM_EXT_CLKGEN_ITEM     *CurrentItemPtr;
  UINT8   Index;
  UINT8   Index2;
  if (ClkNum == 0xFE) {
    return;
  }
  for (Index = 0; Index < AMD_EXT_CLKGEN_SIZE; Index++) {
    if (ExtClkGenTablePtr->Item[Index].Function == 0xFF) {
      break;
    }
    if (ExtClkGenTablePtr->Item[Index].Function == ClkNum + 0x80 && ClkReq == 0) {
      CurrentItemPtr = &ExtClkGenTablePtr->Item[Index];
    } else if (ExtClkGenTablePtr->Item[Index].Function == ClkReq + 0x8F && ClkReq != 0xFF && ClkReq != 0) {
      CurrentItemPtr = &ExtClkGenTablePtr->Item[Index];
    } else {
      continue;
    }
    for (Index2 = 0; Index2 < (*ListNum); Index2++) {
      if (ListPtr[Index2].Offset == CurrentItemPtr->Offset) {
        ListPtr[Index2].AndMask &= CurrentItemPtr->AndMask;
        ListPtr[Index2].OrMask |= CurrentItemPtr->OrMask;
        break;
      }
    }
    if (Index2 == (*ListNum)) {
      ListPtr[Index2].Function = 0;
      ListPtr[Index2].Offset = CurrentItemPtr->Offset;
      ListPtr[Index2].AndMask = CurrentItemPtr->AndMask;
      ListPtr[Index2].OrMask = CurrentItemPtr->OrMask;
      (*ListNum) ++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * CPM External PCIe Clock Init
 *
 * This function initializes external Clock Generator for PCIe clock.
 *
 * @param[in]     CpmTablePpiPtr  Pointer to AMD CPM Table Ppi
 *
 */
VOID
AmdCpmPcieExtClockInit (
  IN      AMD_CPM_TABLE_PPI       *CpmTablePpiPtr
  )
{
  AMD_CPM_PCIE_CLOCK_TABLE        *CpmPcieClockTablePtr;
  AMD_CPM_PCIE_CLOCK_ITEM         *TablePtr;
  UINT8                           SlotStatus;
  BOOLEAN                         ClockType;
  AMD_CPM_EXT_CLKGEN_TABLE        *ExtClkGenTablePtr;
  AMD_CPM_EXT_CLKGEN_ITEM         ClkGen[AMD_PCIE_CLOCK_SIZE];
  AMD_CPM_SAVE_CONTEXT_TABLE      *SaveContextTablePtr;
  UINT8                           Index;
  UINT8                           Data;
  UINT8                           i;
  UINT32                          PcieSlotStatus;
  UINT32                          PcieSlotStatusHigh;

  ExtClkGenTablePtr = NULL;
  Index = 0;
  PcieSlotStatus = 0;
  PcieSlotStatusHigh = 0;

  if (CpmTablePpiPtr->CommonFunction.GetBootMode () != CPM_BOOT_MODE_S3) {
    return;
  }

  SaveContextTablePtr   = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_SAVE_CONTEXT);
  CpmPcieClockTablePtr  = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_CLOCK);
  ClockType             = (BOOLEAN) CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT1;

  ExtClkGenTablePtr     = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_EXT_CLKGEN);
  if (!ExtClkGenTablePtr || ClockType) {
    return;
  }

  if (SaveContextTablePtr && CpmPcieClockTablePtr) {
    PcieSlotStatusHigh = (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x07);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x06);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x05);
    PcieSlotStatusHigh = (PcieSlotStatusHigh << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x04);
    PcieSlotStatus = (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x03);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x02);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x01);
    PcieSlotStatus = (PcieSlotStatus << 8) + (UINT32) CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieClockSlotStatus) + 0x00);
    i = 0;
    TablePtr = &CpmPcieClockTablePtr->Item[0];
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));
    while (TablePtr->ClkId != 0xFF) {
      SlotStatus = 0;
      if (TablePtr->SlotCheck & BIT1) {
        SlotStatus = CpmTablePpiPtr->CommonFunction.DetectDevice (CpmTablePpiPtr, TablePtr->DeviceId, NULL) ? BIT1 : 0;
      }
      if (TablePtr->SlotCheck & (BIT3 + BIT2 + BIT0)) {
        if (i < 8) {
          SlotStatus |=  (UINT8) ((PcieSlotStatus >> (4 * i)) & 0xF);
        } else {
          SlotStatus |=  (UINT8) ((PcieSlotStatusHigh >> (4 * (i - 8))) & 0xF);
        }
      }
      DEBUG((DEBUG_INFO, "  Item[%X] Socket=%02X Die=%02X Bridge=%02X Miscid=%02X", i, \
            (TablePtr->SpecialFunctionId >> 24) & 0xF, (TablePtr->SpecialFunctionId >> 20) & 0xF, \
            (TablePtr->SpecialFunctionId >> 16) & 0xF, (TablePtr->SpecialFunctionId >> 28) & 0xF));
      DEBUG((DEBUG_INFO, " Device=%02X  Function=%02X  SlotCheck=%02X  SpecialFunctionId=%X  SlotStatus=%02X\n", \
            TablePtr->Device, TablePtr->Function, TablePtr->SlotCheck, (TablePtr->SpecialFunctionId & 0xFFFF), SlotStatus));
      if ((SlotStatus > 0) && (((SlotStatus & 0xFE) & TablePtr->SlotCheck) == 0)) {
        DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmPcieExtClockInit-SlotStatus > 0 & ((SlotStatus & 0xFE) & TablePtr->SlotCheck) = 0\n"));
        DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmPcieExtClockInit-Set ClkReqExt = 0xFF\n"));
        TablePtr->ClkReqExt = 0xFF;
      }
      if ((SlotStatus == 0) && ((TablePtr->SlotCheck & (BIT1 + BIT0)) > 0) && CpmTablePpiPtr->MainTablePtr->UnusedGppClkOffEn) {
        DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmPcieExtClockInit-SlotStatus=0 & (SlotCheck&(BIT1+BIT0))>0 & UnusedGppClkOffEn=1\n"));
        DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmPcieExtClockInit-Set ClkReqExt = 0\n"));
        TablePtr->ClkReqExt = 0;
      }
      DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmPcieExtClockInit-AmdCpmPeiAddOneItemInClkList\n"));
      AmdCpmPeiAddOneItemInClkList (ExtClkGenTablePtr, &ClkGen[0], &Index, TablePtr->ClkIdExt, TablePtr->ClkReqExt);
      TablePtr++;
      i++;
    }
    DEBUG((DEBUG_INFO, "\n==============================================================================\n"));
    i = 0;
    while (Index > 0) {
      if (CpmTablePpiPtr->CommonFunction.ReadSmbusBlock) {
        CpmTablePpiPtr->CommonFunction.ReadSmbusBlock (
                                              CpmTablePpiPtr,
                                              ExtClkGenTablePtr->SmbusSelect,
                                              ExtClkGenTablePtr->SmbusAddress,
                                              ClkGen[i].Offset,
                                              1,
                                              &Data
                                              );
        Data = (Data & ClkGen[i].AndMask) | ClkGen[i].OrMask;
        CpmTablePpiPtr->CommonFunction.WriteSmbusBlock (
                                              CpmTablePpiPtr,
                                              ExtClkGenTablePtr->SmbusSelect,
                                              ExtClkGenTablePtr->SmbusAddress,
                                              ClkGen[i].Offset,
                                              1,
                                              &Data
                                              );
      }
      Index --;
      i ++;
    }
  }
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * CPM GPIO Device Init
 *
 * This function registers the public functions which will be used outside of CPM,
 * initializes GPIO Device stage 1 after AMD PEI INIT RESET PPI is installed.
 *
 * @param[in]     PeiServices       Pointer to Pei Services
 * @param[in]     NotifyDescriptor  The descriptor for the notification event
 * @param[in]     Ppi               Pointer to the PPI in question.
 *
 * @retval        EFI_SUCCESS       Module initialized successfully
 * @retval        EFI_ERROR         Initialization failed (see error for more details)
 *
 */
EFI_STATUS
EFIAPI
AmdCpmGpioInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  EFI_STATUS                      Status;
  AMD_CPM_TABLE_PPI               *CpmTablePpiPtr;
  AMD_CPM_GPIO_INIT_FINISHED_PPI  *CpmGpioInitFinishedPpiPtr;
  EFI_PEI_PPI_DESCRIPTOR          *PpiListCpmGpioInitFinishedPtr;
  AMD_CPM_WIRELESS_BUTTON_TABLE   *WirelessButtonTablePtr;
  AMD_CPM_SAVE_CONTEXT_TABLE      *SaveContextTablePtr;
  AMD_CPM_PCIE_CLOCK_TABLE        *CpmPcieClockTablePtr;
  AMD_CPM_PCIE_CLOCK_ITEM         *TablePtr;
  UINT8                           BootStatus;
  UINT8                           PreviousPowerStatus;
  UINT8                           OtherStatus;
  UINT8                           WirelessStatus;
  UINT8                           RadioStatus;

  RECORD_TIME_PEI (BeginAmdCpmGpioInitStage1);

  Status = (*PeiServices)->LocatePpi (
                              (CPM_PEI_SERVICES**)PeiServices,
                              &gAmdCpmTablePpiGuid,
                              0,
                              NULL,
                              (VOID**)&CpmTablePpiPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimDriverBegin);

  CpmTablePpiPtr->CommonFunction.LoadPreInitTable (CpmTablePpiPtr, CPM_PRE_INIT_STAGE_1);

  AmdCpmPeiGpioInit (CpmTablePpiPtr);
  AmdCpmGpioDeviceInit (CpmTablePpiPtr, GPIO_DEVICE_INIT_STAGE_1);
  AmdCpmPeiExtClkGenInit (CpmTablePpiPtr);
  AmdCpmPcieExtClockInit (CpmTablePpiPtr);

  Status = (**PeiServices).NotifyPpi (PeiServices, &mCpmPtGpioInitPeimNotify);

  CpmTablePpiPtr->PeimPublicFunction.SetMemVoltage    = AmdCpmSetMemVoltage;
  CpmTablePpiPtr->PeimPublicFunction.SetVddpVddrVoltage = AmdCpmSetVddpVddrVoltage;
  CpmTablePpiPtr->CommonFunction.ResetDevice          = AmdCpmResetDevice;

  WirelessButtonTablePtr  = CpmTablePpiPtr->CommonFunction.GetTablePtr2 (CpmTablePpiPtr, CPM_SIGNATURE_WIRELESS_BUTTON);
  SaveContextTablePtr     = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_SAVE_CONTEXT);
  CpmPcieClockTablePtr    = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_CLOCK);

  BootStatus = CpmTablePpiPtr->CommonFunction.GetBootMode ();
  if (WirelessButtonTablePtr) {
    OtherStatus = CpmTablePpiPtr->CommonFunction.GetDeviceConfig (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdOther);
    WirelessStatus = CpmTablePpiPtr->CommonFunction.GetDeviceConfig (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdPower);
    RadioStatus = CpmTablePpiPtr->CommonFunction.GetDeviceConfig (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdRadio);
    if (OtherStatus == 0) {
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdOther, CPM_POWER_OFF);
      WirelessButtonTablePtr->DeviceIdOther = 0;
    }
    if (WirelessStatus == 0) {
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdRadio, CPM_POWER_OFF);
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdPower, CPM_POWER_OFF);
      WirelessButtonTablePtr->DeviceIdRadio = 0;
      WirelessButtonTablePtr->DeviceIdPower = 0;
    }
    if ((BootStatus == CPM_BOOT_MODE_S3 || BootStatus == CPM_BOOT_MODE_S4) && CpmTablePpiPtr->MainTablePtr->WirelessButtonEn && SaveContextTablePtr) {
      PreviousPowerStatus = CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, WirelessButtonStatus));
      if (CpmTablePpiPtr->MainTablePtr->WirelessButtonEn == 2) {
        CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdPower, PreviousPowerStatus);
      }
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdRadio, PreviousPowerStatus);
      if (OtherStatus) {
        CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdOther, PreviousPowerStatus);
      }
    } else {
      if (SaveContextTablePtr) {
        CpmTablePpiPtr->CommonFunction.SetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, WirelessButtonStatus), CPM_POWER_ON);
      }
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdPower, CPM_POWER_ON);
      CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdRadio, CPM_POWER_ON);
      if (OtherStatus) {
        CpmTablePpiPtr->CommonFunction.PowerOnDevice (CpmTablePpiPtr, WirelessButtonTablePtr->DeviceIdOther, CPM_POWER_ON);
      }
    }
  }
  if (CpmPcieClockTablePtr && (CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT1)) {
    TablePtr = &CpmPcieClockTablePtr->Item[0];
    while (TablePtr->ClkId != 0xFF) {
      if (TablePtr->ClkId != 0xFE) {
        CpmTablePpiPtr->CommonFunction.SetClkReq (CpmTablePpiPtr, (UINT8) ((TablePtr->SpecialFunctionId >> 24) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 20) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 16) & 0xF), (UINT8) ((TablePtr->SpecialFunctionId >> 28) & 0xF), TablePtr->ClkId, 0xFF);
      }
      TablePtr++;
    }
  }
  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpGpioInitPeimDriverEnd);

  Status = (*PeiServices)->AllocatePool (
                              (CPM_PEI_SERVICES**)PeiServices,
                              sizeof (AMD_CPM_GPIO_INIT_FINISHED_PPI),
                              (VOID**)&CpmGpioInitFinishedPpiPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = (*PeiServices)->AllocatePool (
                              (CPM_PEI_SERVICES**)PeiServices,
                              sizeof (EFI_PEI_PPI_DESCRIPTOR),
                              (VOID**)&PpiListCpmGpioInitFinishedPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  PpiListCpmGpioInitFinishedPtr->Flags   = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  PpiListCpmGpioInitFinishedPtr->Guid    = &gAmdCpmGpioInitFinishedPpiGuid;
  PpiListCpmGpioInitFinishedPtr->Ppi     = CpmGpioInitFinishedPpiPtr;

  Status = (*PeiServices)->InstallPpi (
                              (CPM_PEI_SERVICES**)PeiServices,
                              PpiListCpmGpioInitFinishedPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  RECORD_TIME_PEI (EndAmdCpmGpioInitStage1);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM GPIO Init PEIM driver
 *
 * This function registers the functions to initialize GPIO pins, GEVENT pins, PCIe
 * reference clock and on-board devices.
 *
 * @param[in]     FileHandle     Pointer to the firmware file system header
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmGpioInitPeimEntryPoint (
  IN        CPM_PEI_FILE_HANDLE   FileHandle,
  IN        CPM_PEI_SERVICES      **PeiServices
  )
{
  EFI_STATUS                      Status;
#ifndef AGESA_V9
  EFI_PEI_NOTIFY_DESCRIPTOR       NotifyDescriptor;
  VOID                            *Ppi = NULL;
#endif

#ifdef AGESA_V9
  Status = (**PeiServices).NotifyPpi (PeiServices, &mAmdCpmGpioInitPeimNotify);
#else
  Status = AmdCpmGpioInitPeimNotifyCallback ((EFI_PEI_SERVICES**)PeiServices,
                               &NotifyDescriptor,
                               Ppi);
#endif
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback Function of the AMD CPM GPIO Init PEIM driver
 *
 * This function registers the functions to initialize GPIO pins, GEVENT pins, PCIe
 * reference clock and on-board devices.
 *
 * @param[in]     PeiServices       The PEI core services table.
 * @param[in]     NotifyDescriptor  The descriptor for the notification event.
 * @param[in]     Ppi               Pointer to the PPI in question
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmGpioInitPeimNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  EFI_STATUS                      Status;
#ifdef AGESA_V9
  EFI_PEI_NOTIFY_DESCRIPTOR       NotifyDescriptorV9;
  VOID                            *PpiV9 = NULL;
#endif

  RECORD_TIME_PEI (BeginAmdCpmGpioInitPeimDriver);

#ifndef AGESA_V9
  Status = (**PeiServices).NotifyPpi (PeiServices, &mAmdCpmGpioInitStage1PeimNotify);
#else
  Status = AmdCpmGpioInitPeim ((EFI_PEI_SERVICES**)PeiServices,
                               &NotifyDescriptorV9,
                               PpiV9);
#endif
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = (**PeiServices).NotifyPpi (PeiServices, &mAmdCpmGpioInitStage2PeimNotify);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  RECORD_TIME_PEI (EndAmdCpmGpioInitPeimDriver);

  return EFI_SUCCESS;
}
