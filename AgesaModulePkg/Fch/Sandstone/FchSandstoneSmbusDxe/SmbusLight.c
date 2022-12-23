/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH DXE
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*****************************************************************************
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

#include "SmbusLight.h"
#include <Library/AmdBaseLib.h>

#define SMB_IOREG08            0x8
#define FILECODE UEFI_DXE_SMBUS_SMBUSLIGHT_FILECODE

STATIC SMBUS_INSTANCE               *mSmbus;
STATIC EFI_HANDLE                   mDriverImageHandle;


/********************************************************************************
 * Name: InstallAmdSmbusLightEntryPoint
 *
 * Description
 *   Smbus Entrypoint
 *
 * @param[in]    ImageHandle     Pointer to the image handle
 * @param[in]    SystemTable     Pointer to the EFI system table
 *
 * @retval       EFI_SUCCESS     Driver initialized successfully
 * @retval       EFI_ERROR       Driver initialization failed
 *
 *********************************************************************************/
EFI_STATUS
InstallAmdSmbusLightEntryPoint (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_METRONOME_ARCH_PROTOCOL   *Metronome;
  UINT16                            SmbusIoBase;

  Status = EFI_SUCCESS;
  mDriverImageHandle = ImageHandle;

  // Allocate two contiguous instances for SMBus and ASF
  Status = gBS->AllocatePool (EfiBootServicesData, (sizeof (SMBUS_INSTANCE)) * 2, &mSmbus);
  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    //clear instances content
    gBS->SetMem (mSmbus, (sizeof (SMBUS_INSTANCE)) * 2, 0);
  }



  Status = gBS->LocateProtocol (&gEfiMetronomeArchProtocolGuid, NULL, &Metronome);
  if (EFI_ERROR (Status)) {
    return Status;
  }



  //read SMBus base address from HW
  LibAmdMemRead (AccessWidth16, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG00), &SmbusIoBase, NULL);

  SmbusIoBase &= 0xFF00;

  // Init data - SMBus
  mSmbus->Signature                 = SMBUS_INSTANCE_SIGNATURE;
  mSmbus->SmbusIoBase               = SmbusIoBase;
  mSmbus->StallTime                 = Metronome->TickPeriod;
  mSmbus->IoDone                    = IoDone;
  mSmbus->SmbusIoRead               = SmbusIoRead;
  mSmbus->SmbusIoWrite              = SmbusIoWrite;
  mSmbus->SmbusController.Execute   = SmbusExecute;
  mSmbus->SmbusController.ArpDevice = SmbusArpDevice;
  mSmbus->SmbusController.GetArpMap = SmbusGetArpMap;
  mSmbus->SmbusController.Notify    = SmbusNotify;

// Init data - ASF
  (mSmbus + 1)->Signature                 = SMBUS_INSTANCE_SIGNATURE;
  (mSmbus + 1)->SmbusIoBase               = SmbusIoBase + 0x20;
  (mSmbus + 1)->StallTime                 = Metronome->TickPeriod;
  (mSmbus + 1)->IoDone                    = IoDone;
  (mSmbus + 1)->SmbusIoRead               = SmbusIoRead;
  (mSmbus + 1)->SmbusIoWrite              = SmbusIoWrite;
  (mSmbus + 1)->SmbusController.Execute   = SmbusExecute;
  (mSmbus + 1)->SmbusController.ArpDevice = SmbusArpDevice;
  (mSmbus + 1)->SmbusController.GetArpMap = SmbusGetArpMap;
  (mSmbus + 1)->SmbusController.Notify    = SmbusNotify;

  SetDataAndRegister (mSmbus);
  InitializeListHead (&mSmbus->NotifyFunctionList);
  SetDataAndRegister (mSmbus + 1);
  InitializeListHead (&(mSmbus + 1)->NotifyFunctionList);

  // Install Protocol
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mSmbus->Handle,
                  &gEfiSmbusHcProtocolGuid,
                  &mSmbus->SmbusController,
                  NULL
                  );
  return Status;
}

/********************************************************************************
 * Name: SetDataAndRegister
 *
 * Description
 *   Init BaseAddress
 *
 * Input
 *   Smbus : a pointer to the SMBUS data structure
 *
 * Output
 *
 *
 *********************************************************************************/
VOID
SetDataAndRegister (
  IN SMBUS_INSTANCE             *Smbus
  )
{
  SmbusIoWrite (Smbus, HSTS, HSTS_ALL);
}


/*********************************************************************************
 * Name: SmbusIoRead
 *
 * Description
 *   Use the PCI_ROOT_Bridge_IO to do an 8 bits I/O port read
 *
 * Input
 *   Private : a pointer to the SMBUS data structure
 *   Offset  : the address to read from
 *
 * Output
 *   UINT8   : the read value
 *
 *********************************************************************************/
UINT8
SmbusIoRead (
  IN SMBUS_INSTANCE     *Private,
  IN UINT8                      Offset
  )
{
  UINT8                                                         FchSmbusData8;

  LibAmdIoRead (AccessWidth8, Private->SmbusIoBase + Offset, &FchSmbusData8, NULL);

  return FchSmbusData8;
}

/*********************************************************************************
 * Name: SmbusIoRead
 *
 * Description
 *   Use the PCI_ROOT_Bridge_IO to do an 8 bits I/O port write
 *
 * Input
 *   Private : a pointer to the SMBUS data structure
 *   Offset  : the address to read from
 *   Data    : the write value
 *
 * Output
 *
 *********************************************************************************/
VOID
SmbusIoWrite (
  IN SMBUS_INSTANCE     *Private,
  IN UINT8                      Offset,
  IN UINT8                      Data
  )
{
  LibAmdIoWrite (AccessWidth8, Private->SmbusIoBase + Offset, &Data, NULL);
}

/*********************************************************************************
 * Name: IoDone
 *
 * Description
 *   Check SMBUS status register
 *
 * Input
 *   Private : a pointer to the SMBUS data structure
 *   StsReg  : Test Bit
 *
 * Output
 *   BOOLEAN : Timeout or succesfully
 *
 *********************************************************************************/
BOOLEAN
IoDone (
  IN SMBUS_INSTANCE             *Private,
  IN UINT8                      *StsReg
  )
{
  BOOLEAN                       Ret;
  UINTN                         StallTries;
  UINTN                         StallIndex;

  Ret = FALSE;

  for (StallTries = STALL_TIME / Private->StallTime, StallIndex = 0; StallIndex < StallTries; ++StallIndex) {
    *StsReg = Private->SmbusIoRead (Private, HSTS);
    if (*StsReg & (INTR | BYTE_DONE_STS | DERR | BERR)) {
      Ret = TRUE;
      break;
    }
    gBS->Stall (Private->StallTime);
  }

  return Ret;
}

/*********************************************************************************
 * Name: SmBusExecute
 *
 * Description
 *   Execute the SMBUS command by calling the worker functions
 *
 * Input
 *   This         :
 *   SlaveAddress :
 *   Command      :
 *   Operation    :
 *   PecCheck     :
 *   Length       :
 *   Buffer       :
 *
 * Output
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmbusExecute (
  IN       CONST EFI_SMBUS_HC_PROTOCOL        *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS           SlaveAddress,
  IN       EFI_SMBUS_DEVICE_COMMAND           Command,
  IN       EFI_SMBUS_OPERATION                Operation,
  IN       BOOLEAN                            PecCheck,
  IN OUT   UINTN                              *Length,
  IN OUT   VOID                               *Buffer
  )
{
  EFI_STATUS                                  Status;
  SMBUS_INSTANCE                              *Smbus;
  UINT8                                       StsReg,
                                              SlaveAddressReg,
                                              HostCommandReg,
                                              *Buf;
  UINTN                                       Count,
                                              Index,
                                              SmbusCommand;
  UINT32                                      LoopCount;
  UINT8                                       dbSmbusTempVar;
  UINT8                                       bValue;
  BOOLEAN                                     IsBusy;
  UINT8                                       retryCount;

  Status = EFI_SUCCESS;
  Buf = (UINT8 *)Buffer;
  Smbus = SMBUS_INSTANCE_FROM_THIS (This);
  SetDataAndRegister (Smbus);

  //
  // Host get SMBUS ownership
  //
  LoopCount = 500;
  while (LoopCount) {
    LibAmdIoRead (AccessWidth8,  Smbus->SmbusIoBase + SMB_IOREG08, &dbSmbusTempVar, NULL);
    if (dbSmbusTempVar & BIT6) {
      LoopCount--;
    } else {
      break;
    }
  }

  dbSmbusTempVar |= BIT4;
  LibAmdIoWrite (AccessWidth8,  Smbus->SmbusIoBase + SMB_IOREG08, &dbSmbusTempVar, NULL);

  if (Operation != EfiSmbusQuickRead && Operation != EfiSmbusQuickWrite && (Length == NULL ||  Buffer == NULL)) {
    Status = EFI_INVALID_PARAMETER;
  }
  IsBusy = TRUE;
  retryCount = 3;
  while (retryCount--) {
    LoopCount = 100;
    do {
      dbSmbusTempVar = 0x1f;
      LibAmdIoWrite (AccessWidth8,  Smbus->SmbusIoBase, &dbSmbusTempVar, NULL);
      LibAmdIoRead (AccessWidth8, 0xed, &bValue, NULL);
      LibAmdIoRead (AccessWidth8, 0xed, &bValue, NULL);
      LibAmdIoRead (AccessWidth8,  Smbus->SmbusIoBase, &dbSmbusTempVar, NULL);
      if ( ! ( dbSmbusTempVar & BIT0) ) {
        IsBusy = FALSE;         // Bit0 = 0, controller is idle
        break;
      }
    } while (LoopCount--);
    if (!IsBusy) {
      break;
    }
    dbSmbusTempVar = BIT1;
    LibAmdIoWrite (AccessWidth8,  Smbus->SmbusIoBase + 2, &dbSmbusTempVar, NULL);
  }

  if (!EFI_ERROR (Status)) {
    StsReg = Smbus->SmbusIoRead (Smbus, HSTS);
    if ((StsReg & IUS) != 0) {
      Status = EFI_TIMEOUT;
    } else if (StsReg & HBSY) {
      Smbus->SmbusIoWrite (Smbus, HSTS, HSTS_ALL);
      Status = EFI_TIMEOUT;
    } else {
      Status = CheckSlaveStatus (Smbus);
    }

    if (!EFI_ERROR (Status)) {
      for (Count = 0; Count < TRY_TIMES; ++Count) {
        SmbusCommand = SMB_CMD_QUICK;
        SlaveAddressReg = (UINT8) ((SlaveAddress.SmbusDeviceAddress << 1) | READ_ENABLE);
        HostCommandReg = (UINT8)Command;
        Status = ProcessOperation (
                   Operation,
                   PecCheck,
                   Length,
                   *Buf,
                   &SlaveAddressReg,
                   &HostCommandReg,
                   &SmbusCommand
                   );

        if (EFI_ERROR (Status)) {
          break;
        }

        Smbus->SmbusIoWrite (Smbus, HSTS, (HBSY + INTR + DERR + BERR + FAIL));
        Smbus->SmbusIoWrite (Smbus, TSA, SlaveAddressReg);
        Smbus->SmbusIoWrite (Smbus, HCMD, HostCommandReg);
        Smbus->SmbusIoWrite (Smbus, HCTL, (UINT8) (SmbusCommand));
        //
        // Do a read from Reg02 to reset
        // the counter if it going to be a
        // block read/write operation
        //
        StsReg = Smbus->SmbusIoRead (Smbus, HCTL);
        if ((SlaveAddressReg & READ_ENABLE) != 0) {
          if (SmbusCommand == SMB_CMD_BLOCK) {
            Smbus->SmbusIoWrite (Smbus, HD0, (UINT8)*Length);
          }
        } else {
          if (SmbusCommand == SMB_CMD_BLOCK) {
            Smbus->SmbusIoWrite (Smbus, HD0, (UINT8)*Length);
            for (Index = 0; Index < *Length; Index++) {
              Smbus->SmbusIoWrite (Smbus, HBD, Buf [Index]);
            }
          } else if (SmbusCommand == SMB_CMD_WORD_DATA) {
            Smbus->SmbusIoWrite (Smbus, HD1, Buf [1]);
            Smbus->SmbusIoWrite (Smbus, HD0, Buf [0]);
          } else {
            Smbus->SmbusIoWrite (Smbus, HD0, Buf [0]);
          }
        }

        Smbus->SmbusIoWrite (Smbus, HCTL, (UINT8) (SmbusCommand + START + ((PecCheck) ? (StsReg | 0xA0) : 0)));

        if (! (Smbus->IoDone (Smbus, &StsReg))) {
          Status = EFI_TIMEOUT;
          break;
        } else if (StsReg & DERR) {
          Status = EFI_DEVICE_ERROR;
          break;
        } else if (StsReg & BERR) {
          Status = EFI_DEVICE_ERROR;
          Smbus->SmbusIoWrite (Smbus, HSTS, BERR);
          continue;
        }

        Status = SuccessfulCompletion (Operation, Smbus, Buf, Length);

        if ((StsReg & BERR) && (Status != EFI_BUFFER_TOO_SMALL)) {
          Status = EFI_DEVICE_ERROR;
          Smbus->SmbusIoWrite (Smbus, HSTS, BERR);
          continue;
        } else {
          break;
        }
      } // end for

      Smbus->SmbusIoWrite (Smbus, HSTS, (HBSY + INTR + DERR + BERR + FAIL));
    } //end if (!EFI_ERROR (Status))
  } //end if (!EFI_ERROR (Status))

  //
  // release SMBUS ownership
  //
  LibAmdIoRead (AccessWidth8, Smbus->SmbusIoBase + SMB_IOREG08, &dbSmbusTempVar, NULL);
  dbSmbusTempVar |= BIT5;
  LibAmdIoWrite (AccessWidth8, Smbus->SmbusIoBase + SMB_IOREG08, &dbSmbusTempVar, NULL);
  return Status;
}

/*********************************************************************************
 * Name: ProcessOperation
 *
 * Description
 *   Setting flags for access SMBUS operation
 *
 * Input
 *   Operation       :
 *   PecCheck        :
 *   Length          :
 *   Len             :
 *   SlaveAddressReg :
 *   HostCommandReg  :
 *   SmbusCommand    :
 *
 * Output
 *   EFI_STATUS : input is avaliable or invalid
 *
 *********************************************************************************/
EFI_STATUS
ProcessOperation (
  IN       EFI_SMBUS_OPERATION        Operation,
  IN       BOOLEAN                    PecCheck,
  IN OUT   UINTN                      *Length,
  IN       UINT8                      Len,
     OUT   UINT8                      *SlaveAddressReg,
     OUT   UINT8                      *HostCommandReg,
     OUT   UINTN                      *SmbusCommand
  )
{
  EFI_STATUS                          Status;

  Status = EFI_SUCCESS;
  switch (Operation) {
  case EfiSmbusQuickWrite:
    *SlaveAddressReg &= ~READ_ENABLE;

  case EfiSmbusQuickRead:
    if (PecCheck) {
      Status = EFI_UNSUPPORTED;
    }
    break;

  case EfiSmbusSendByte:
    *HostCommandReg = Len;
    *SlaveAddressReg &= ~READ_ENABLE;

  case EfiSmbusReceiveByte:
    *SmbusCommand = SMB_CMD_BYTE;
    if (*Length < 1) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 1;
    break;

  case EfiSmbusWriteByte:
    *SlaveAddressReg &= ~READ_ENABLE;

  case EfiSmbusReadByte:
    *SmbusCommand = SMB_CMD_BYTE_DATA;
    if (*Length < 1) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 1;
    break;

  case EfiSmbusReadWord:
    *SmbusCommand = SMB_CMD_WORD_DATA;
    if (*Length < 2) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 2;
    break;

  case EfiSmbusWriteWord:
    *SmbusCommand = SMB_CMD_WORD_DATA;
    *SlaveAddressReg &= ~READ_ENABLE;
    if (*Length < 2) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 2;
    break;

  case EfiSmbusWriteBlock:
    *SlaveAddressReg &= ~READ_ENABLE;
    *SmbusCommand = SMB_CMD_BLOCK;
    break;

  case EfiSmbusReadBlock:
    *SmbusCommand = SMB_CMD_BLOCK;
    if ((*Length < 1) || (*Length > 72)) {
      Status = EFI_INVALID_PARAMETER;
    }
    break;

  case EfiSmbusBWBRProcessCall:
    Status = EFI_UNSUPPORTED;
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
    break;
  }
  return Status;
}

/*********************************************************************************
 * Name: SuccessfulCompletion
 *
 * Description
 *
 *
 * Input
 *   Operation    :
 *   Smbus        :
 *   Buf          :
 *   Length       :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
SuccessfulCompletion (
  IN       EFI_SMBUS_OPERATION        Operation,
  IN       SMBUS_INSTANCE             *Smbus,
  IN       UINT8                      *Buf,
  IN OUT   UINTN                      *Length
  )
{
  EFI_STATUS                          Status;
  UINTN                               Index,
                                      BlockCount;

  Status = EFI_SUCCESS;

  switch (Operation) {
  case EfiSmbusReadWord:
  case EfiSmbusProcessCall:
    Buf [1] = Smbus->SmbusIoRead (Smbus, HD1);

  case EfiSmbusReadByte:
    Buf [0] = Smbus->SmbusIoRead (Smbus, HD0);
    break;

  case EfiSmbusReadBlock:
    BlockCount = Smbus->SmbusIoRead (Smbus, HD0);
    if (*Length < BlockCount) {
      BlockCount = *Length;
    }
    for (Index = 0; Index < BlockCount; ++Index) {
      Buf [Index] = Smbus->SmbusIoRead (Smbus, HBD);
    }
    *Length = BlockCount;
    break;

  default:
    break;
  }
  return Status;
}

/*********************************************************************************
 * Name: SmbusArpDevice
 *
 * Description
 *   Perform ARP resolution.
 *
 * Input
 *   This          :
 *   ArpAll        :
 *   SmbusUdid     :
 *   SlaveAddress  :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmbusArpDevice (
  IN       CONST EFI_SMBUS_HC_PROTOCOL    *This,
  IN       BOOLEAN                        ArpAll,
  IN       EFI_SMBUS_UDID                 *SmbusUdid,
  IN OUT   EFI_SMBUS_DEVICE_ADDRESS       *SlaveAddress
  )
{
  EFI_STATUS                           Status;
  EFI_SMBUS_DEVICE_ADDRESS             DeviceAddress;
  EFI_SMBUS_DEVICE_MAP                 *DeviceMap;
  SMBUS_INSTANCE                       *Smbus;
  UINTN                                Length;
  UINT8                                FchSmbusData8;

  Status = EFI_SUCCESS;
  Smbus = SMBUS_INSTANCE_FROM_THIS (This);
  SetDataAndRegister (Smbus);

  if (ArpAll) {
    FchSmbusData8 = DATA_PREPARE_TO_ARP;
    Length = 1;
    DeviceAddress.SmbusDeviceAddress = ADDRESS_ARP;
    Status = SmbusExecute (This, DeviceAddress, 0, EfiSmbusSendByte, TRUE, &Length, &FchSmbusData8);

    if (!EFI_ERROR (Status)) {
      do {
        DeviceMap = &Smbus->DeviceMap [Smbus->DeviceMapEntries];
        if (EFI_ERROR (GetUdidData (Smbus, DeviceMap))) {
          break;
        }

        if (DeviceMap->SmbusDeviceAddress.SmbusDeviceAddress == (0xFF >> 1)) {
          if (EFI_ERROR (GetNextDeviceAddress (Smbus, &DeviceMap->SmbusDeviceAddress))) {
            Status = EFI_OUT_OF_RESOURCES;
            break;
          }
        } else if (((DeviceMap->SmbusDeviceUdid.DeviceCapabilities) & 0xC0) != 0) {
          if (!CheckDeviceAddress (Smbus, DeviceMap->SmbusDeviceAddress)) {
            if (EFI_ERROR (GetNextDeviceAddress (Smbus, &DeviceMap->SmbusDeviceAddress))) {
              Status = EFI_OUT_OF_RESOURCES;
              break;
            }
          }
        }

        Status = AssignAddress (Smbus, DeviceMap);
        if (EFI_ERROR (Status)) {
          if (Status != EFI_DEVICE_ERROR) {
            break;
          }
        } else {
          ++Smbus->DeviceMapEntries;
        }
      } while (Smbus->DeviceMapEntries < MAX_SMBUS_DEVICES);
    } else {
      if (Status == EFI_DEVICE_ERROR) {
        Status = EFI_SUCCESS;
      }
    }
  } else {
    if (SmbusUdid != NULL && SlaveAddress != NULL) {
      if (Smbus->DeviceMapEntries >= MAX_SMBUS_DEVICES) {
        Status = EFI_OUT_OF_RESOURCES;
      }

      if (!EFI_ERROR (Status)) {
        DeviceMap = &Smbus->DeviceMap [Smbus->DeviceMapEntries];
        if (EFI_ERROR (GetNextDeviceAddress (Smbus, &DeviceMap->SmbusDeviceAddress))) {
          Status = EFI_OUT_OF_RESOURCES;
        }
        if (!EFI_ERROR (Status)) {
          DeviceMap->SmbusDeviceUdid = *SmbusUdid;
          Status = AssignAddress (Smbus, DeviceMap);

          if (!EFI_ERROR (Status)) {
            ++Smbus->DeviceMapEntries;
            SlaveAddress->SmbusDeviceAddress = DeviceMap->SmbusDeviceAddress.SmbusDeviceAddress;
          }
        }
      }
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }
  return Status;
}

/*********************************************************************************
 * Name: GetUdidData
 *
 * Description
 *
 *
 * Input
 *   Smbus          :
 *   DeviceMap      :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
GetUdidData (
  IN       SMBUS_INSTANCE          *Smbus,
  IN OUT   EFI_SMBUS_DEVICE_MAP    *DeviceMap
  )
{
  EFI_SMBUS_DEVICE_ADDRESS         DeviceAddress;
  EFI_STATUS                       Status;
  UINTN                            Length;
  EFI_SMBUS_DEVICE_MAP             Temp;

  DeviceAddress.SmbusDeviceAddress = ADDRESS_ARP;
  Length = sizeof (EFI_SMBUS_DEVICE_MAP);

  Status = SmbusExecute (
             &Smbus->SmbusController,
             DeviceAddress,
             DATA_RESET_DEVICE,
             EfiSmbusReadBlock,
             TRUE,
             &Length,
             &Temp
             );

  if (!EFI_ERROR (Status)) {
    if (Length != sizeof (EFI_SMBUS_DEVICE_MAP)) {
      Status = EFI_DEVICE_ERROR;
    } else {
      *DeviceMap = Temp;
    }
  }
  return Status;
}

/*********************************************************************************
 * Name: GetNextDeviceAddress
 *
 * Description
 *
 *
 * Input
 *   Smbus          :
 *   DeviceAddress  :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
GetNextDeviceAddress (
  IN SMBUS_INSTANCE            *Smbus,
  IN EFI_SMBUS_DEVICE_ADDRESS  *DeviceAddress
  )
{
  EFI_STATUS                    Status;

  Status = EFI_OUT_OF_RESOURCES;

  for (DeviceAddress->SmbusDeviceAddress = 0x03; DeviceAddress->SmbusDeviceAddress < 0x7F; ++DeviceAddress->SmbusDeviceAddress) {
    if (CheckDeviceAddress (Smbus, *DeviceAddress)) {
      Status = EFI_SUCCESS;
      break;
    }
  }
  return Status;
}

/*********************************************************************************
 * Name: CheckDeviceAddress
 *
 * Description
 *
 *
 * Input
 *   Smbus          :
 *   DeviceAddress  :
 *
 * Output
 *   BOOLEAN
 *
 *********************************************************************************/
BOOLEAN
CheckDeviceAddress (
  IN SMBUS_INSTANCE                                         *Smbus,
  IN EFI_SMBUS_DEVICE_ADDRESS                               DeviceAddress
  )
{
  BOOLEAN                                                   Ret;
  UINT8                                                     Index;

  Ret = TRUE;
  for (Index = 0; Index < Smbus->DeviceMapEntries; ++Index) {
    if (DeviceAddress.SmbusDeviceAddress == Smbus->DeviceMap [Index].SmbusDeviceAddress.SmbusDeviceAddress) {
      Ret = FALSE;
      break;
    }
  }
  return Ret;
}

/*********************************************************************************
 * Name: AssignAddress
 *
 * Description
 *
 *
 * Input
 *   Smbus          :
 *   DeviceMap      :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
AssignAddress (
  IN       SMBUS_INSTANCE          *Smbus,
  IN OUT   EFI_SMBUS_DEVICE_MAP    *DeviceMap
  )
{
  EFI_SMBUS_DEVICE_ADDRESS         DeviceAddress;
  EFI_STATUS                       Status;
  UINTN                            Length;
  EFI_SMBUS_DEVICE_MAP             Temp;

  Temp = *DeviceMap;
  DeviceAddress.SmbusDeviceAddress = ADDRESS_ARP;
  Length = sizeof (EFI_SMBUS_DEVICE_MAP);
  Status = SmbusExecute (
             &Smbus->SmbusController,
             DeviceAddress,
             DATA_RESET_DEVICE,
             EfiSmbusWriteBlock,
             TRUE,
             &Length,
             &Temp
             );

  return Status;
}

/*********************************************************************************
 * Name: SmbusGetArpMap
 *
 * Description
 *
 *
 * Input
 *   This           :
 *   Length         :
 *   SmbusDeviceMap :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmbusGetArpMap (
  IN       CONST EFI_SMBUS_HC_PROTOCOL    *This,
  IN OUT   UINTN                          *Length,
  IN OUT   EFI_SMBUS_DEVICE_MAP           **SmbusDeviceMap
  )
{
  SMBUS_INSTANCE                    *Smbus;

  Smbus = SMBUS_INSTANCE_FROM_THIS (This);
  *Length = Smbus->DeviceMapEntries;
  *SmbusDeviceMap = Smbus->DeviceMap;

  return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: SmbusNotify
 *
 * Description
 *   Register a notify function
 *
 * Input
 *   This           :
 *   SlaveAddress   :
 *   Data           :
 *   NotifyFunction :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmbusNotify (
  IN       CONST EFI_SMBUS_HC_PROTOCOL  *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS     SlaveAddress,
  IN       UINTN                        Data,
  IN       EFI_SMBUS_NOTIFY_FUNCTION    NotifyFunction
  )
{
  EFI_STATUS                          Status;
  SMBUS_INSTANCE                      *Smbus;
  SMBUS_NOTIFY_FUNCTION_LIST_NODE     *Node;

  Status = EFI_UNSUPPORTED;
  Smbus = SMBUS_INSTANCE_FROM_THIS (This);

  if (NotifyFunction == NULL) {
    if (Smbus->NotificationEvent == NULL) {
      if (!EFI_ERROR (
        gBS->CreateEvent (
               EVT_TIMER | EVT_NOTIFY_SIGNAL,
               TPL_CALLBACK,
               SmbusNotifyFunction,
               NULL,
               &Smbus->NotificationEvent
               ))) {
        if (!EFI_ERROR (
          gBS->SetTimer (Smbus->NotificationEvent, TimerPeriodic, NOTIFYTIME)
          )) {
          gBS->AllocatePool (EfiBootServicesData, sizeof (SMBUS_NOTIFY_FUNCTION_LIST_NODE), &Node);
          gBS->SetMem (Node, sizeof (SMBUS_NOTIFY_FUNCTION_LIST_NODE), 0);
          Node->Signature = SMBUS_INSTANCE_SIGNATURE;
          Node->SlaveAddress.SmbusDeviceAddress = SlaveAddress.SmbusDeviceAddress;
          Node->Data = Data;
          Node->NotifyFunction = NotifyFunction;
          InsertTailList (&Smbus->NotifyFunctionList, &Node->Link);
        }
      }
    }
  } else {
    Status = EFI_INVALID_PARAMETER;
  }
  return Status;
}

/*********************************************************************************
 * Name: SmbusNotifyFunction
 *
 * Description
 *   Register a notify function
 *
 * Input
 *   Event     :
 *   Context   :
 *
 * Output
 *
 *
 *********************************************************************************/
VOID
SmbusNotifyFunction (
  IN EFI_EVENT                        Event,
  IN VOID                             *Context
  )
{
  LIST_ENTRY                       *Link;
  EFI_SMBUS_DEVICE_ADDRESS            DeviceAddress;
  SMBUS_NOTIFY_FUNCTION_LIST_NODE     *Node;
  UINT8                               FchSmbusData8;
  UINTN                               DataN;

  SetDataAndRegister (mSmbus);
  FchSmbusData8 = mSmbus->SmbusIoRead (mSmbus, SSTS);
  if ((FchSmbusData8 & HOST_NOTIFY_STS) != 0) {
    DeviceAddress.SmbusDeviceAddress = (mSmbus->SmbusIoRead (mSmbus, NDA)) >> 1;

    for (
    Link = GetFirstNode (&mSmbus->NotifyFunctionList);
    !IsNull (&mSmbus->NotifyFunctionList, Link);
    Link = GetNextNode (&mSmbus->NotifyFunctionList, &Node->Link)
    ) {
      Node = SMBUS_NOTIFY_FUNCTION_LIST_NODE_FROM_LINK (Link);
      if (Node->SlaveAddress.SmbusDeviceAddress == DeviceAddress.SmbusDeviceAddress) {
        DataN = (mSmbus->SmbusIoRead (mSmbus, NDHB) << 8)
          + (mSmbus->SmbusIoRead (mSmbus, NDLB));
        if ((UINT16)Node->Data == (UINT16)DataN) {
          Node->NotifyFunction (DeviceAddress, DataN);
        }
      }
    }
    mSmbus->SmbusIoWrite (mSmbus, SSTS, HOST_NOTIFY_STS);
  }
}

/*********************************************************************************
 * Name: CheckSlaveStatus
 *
 * Description
 *
 *
 * Input
 *   Smbus     :
 *
 * Output
 *   EFI_STATUS
 *
 *********************************************************************************/
EFI_STATUS
CheckSlaveStatus (
  IN SMBUS_INSTANCE       *Smbus
  )
{
  UINT32        LoopCount;
  UINT32        LoopCount1;
  UINT8         dbSmbusTempVar;
  BOOLEAN   ControllerBusy;

  ControllerBusy = TRUE;
  LoopCount1 = 3;

  while (LoopCount1 && ControllerBusy) {
    LoopCount = 100;

    while (LoopCount && ControllerBusy) {
      Smbus->SmbusIoWrite (Smbus, SMBUS_R_SSTS, SMBUS_B_SSTS_ALL); // out index 00h, 0ffh to clear status.
      gBS->Stall (2);
      dbSmbusTempVar = Smbus->SmbusIoRead (Smbus, SMBUS_R_SSTS);

      if ( dbSmbusTempVar & SMBUS_B_SBSY ) {
        // Bit0 = 1, controller is still busy!
        LoopCount--;
      } else {
        ControllerBusy = FALSE;
      }
    } // end of while (loopCount)

    if (ControllerBusy) {
      Smbus->SmbusIoWrite (Smbus, SMBUS_R_SSTS, SMBUS_B_SINIT);    // slave init
      LoopCount1--;
    }
  }

  if (ControllerBusy) {
    return EFI_TIMEOUT;
  } else {
    return EFI_SUCCESS;
  }
}


