/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

#include <Library/IoLib.h>
#include <Features/Aod/Include/SmbusLightSmm.h>

#define SMB_IOREG08            0x8

STATIC UINTN mSmbusIoBase0;
STATIC UINTN mSmbusIoBase1;
UINT32       mStallTime;
BOOLEAN      mSmMasterEnabled = FALSE;

EFI_STATUS
EnableSmMasterDecode (
  )
{
  UINT32  DecodeEnValue;

  DecodeEnValue = MmioRead32 (ACPI_MMIO_BASE + PMIO_BASE + 0x00);
  MmioWrite32 (ACPI_MMIO_BASE + PMIO_BASE + 0x00, (DecodeEnValue | (UINT32) BIT16));
  mSmMasterEnabled = TRUE;

  return EFI_SUCCESS;
}

EFI_STATUS
DisableSmMasterDecode (
  )
{
  UINT32  DecodeEnValue;

  if (mSmMasterEnabled) {
    DecodeEnValue = MmioRead32 (ACPI_MMIO_BASE + PMIO_BASE + 0x00);
    DecodeEnValue &= ~BIT16;
    MmioWrite32 (ACPI_MMIO_BASE + PMIO_BASE + 0x00, DecodeEnValue);
    mSmMasterEnabled = FALSE;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
InitSmbusData (
  )
{
  EFI_STATUS                        Status;
  EFI_METRONOME_ARCH_PROTOCOL      *Metronome;

  Status = gBS->LocateProtocol (&gEfiMetronomeArchProtocolGuid, NULL, &Metronome);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  mStallTime = Metronome->TickPeriod;
  DEBUG ((DEBUG_INFO, "\tmStallTime = 0x%x\n", mStallTime));

  //read SMBus base address from HW
  mSmbusIoBase0 = MmioRead16 (ACPI_MMIO_BASE + PMIO_BASE + 0x00);
  mSmbusIoBase0 &= 0xFF00;
  mSmbusIoBase1 = mSmbusIoBase0 + 0x20;

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
  IN UINT8                      SmbusSelect
  )
{
  SmbusIoWrite (SmbusSelect, HSTS, HSTS_ALL);
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
  IN UINT8                      SmbusSelect,
  IN UINT8                      Offset
  )
{
  if (SmbusSelect == 0) {
    return IoRead8 (mSmbusIoBase0 + Offset);
  } else if (SmbusSelect == 1) {
    return IoRead8 (mSmbusIoBase1 + Offset);
  } else {
    ASSERT (FALSE);
  }
  return 0xFF;
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
  IN UINT8                      SmbusSelect,
  IN UINT8                      Offset,
  IN UINT8                      Data
  )
{
  if (SmbusSelect == 0) {
    IoWrite8 (mSmbusIoBase0 + Offset, Data);
  } else if (SmbusSelect == 1) {
    IoWrite8 (mSmbusIoBase1 + Offset, Data);
  } else {
    ASSERT (FALSE);
  }
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
  IN UINT8                       SmbusSelect,
  IN UINT8                      *StsReg
  )
{
  BOOLEAN                       Ret;
  UINTN                         StallTries;
  UINTN                         StallIndex;

  Ret = FALSE;

  for (StallTries = STALL_TIME / mStallTime, StallIndex = 0; StallIndex < StallTries; ++StallIndex) {
    *StsReg = SmbusIoRead (SmbusSelect, HSTS);
    if (*StsReg & (INTR | BYTE_DONE_STS | DERR | BERR)) {
      Ret = TRUE;
      break;
    }
    //gBS->Stall (Private->StallTime);
    IoRead8 (0xED);
  }

  return Ret;
}


EFI_STATUS
CheckSlaveStatus (
  IN UINT8                       SmbusSelect
  )
{
  UINT32        LoopCount;
  UINT32        LoopCount1;
  UINT8         dbSmbusTempVar;
  BOOLEAN   ControllerBusy;

  ControllerBusy = TRUE;
  LoopCount1 = 3;
  dbSmbusTempVar = 0;

  while (LoopCount1 && ControllerBusy) {
    LoopCount = 100;

    while (LoopCount && ControllerBusy) {
      SmbusIoWrite (SmbusSelect, SMBUS_R_SSTS, SMBUS_B_SSTS_ALL); // out index 00h, 0ffh to clear status.
      //gBS->Stall (2);
      IoRead8 (0xED);
      dbSmbusTempVar = SmbusIoRead (SmbusSelect, SMBUS_R_SSTS);

      if ( dbSmbusTempVar & SMBUS_B_SBSY ) {
        // Bit0 = 1, controller is still busy!
        LoopCount--;
      } else {
        ControllerBusy = FALSE;
      }
    } // end of while (loopCount)

    if (ControllerBusy) {
      SmbusIoWrite (SmbusSelect, SMBUS_R_SSTS, SMBUS_B_SINIT);    // slave init
      LoopCount1--;
    }
  }

  if (ControllerBusy) {
    return EFI_TIMEOUT;
  } else {
    return EFI_SUCCESS;
  }
}


/*********************************************************************************
 * Name: SmBusExecute
 *
 * Description
 *   Execute the SMBUS command by calling the worker functions
 *
 * Input
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
  IN       UINT8                              SmbusSelect,
  IN       EFI_SMBUS_DEVICE_ADDRESS           SlaveAddress,
  IN       EFI_SMBUS_DEVICE_COMMAND           Command,
  IN       EFI_SMBUS_OPERATION                Operation,
  IN       BOOLEAN                            PecCheck,
  IN OUT   UINTN                              *Length,
  IN OUT   VOID                               *Buffer
  )
{
  EFI_STATUS                                  Status;
  UINT8                                       StsReg,
                                              SlaveAddressReg,
                                              HostCommandReg,
                                              *Buf;
  UINTN                                       Count,
                                              Index,
                                              SmbusCommand;
  UINT32                                      LoopCount;
  UINT8                                       dbSmbusTempVar;
  BOOLEAN                                     IsBusy;
  UINT8                                       retryCount;

  Status = EFI_SUCCESS;
  Buf = (UINT8 *)Buffer;
  SetDataAndRegister (SmbusSelect);

  //
  // Host get SMBUS ownership
  //
  LoopCount = 500;
  while (LoopCount) {
    dbSmbusTempVar = SmbusIoRead (SmbusSelect, SMB_IOREG08);
    if (dbSmbusTempVar & BIT6) {
      LoopCount--;
    } else {
      break;
    }
  }

  dbSmbusTempVar |= BIT4;
  SmbusIoWrite (SmbusSelect, SMB_IOREG08, dbSmbusTempVar);

  if (Operation != EfiSmbusQuickRead && Operation != EfiSmbusQuickWrite && (Length == NULL ||  Buffer == NULL)) {
    Status = EFI_INVALID_PARAMETER;
  }
  IsBusy = TRUE;
  retryCount = 3;
  while (retryCount--) {
    LoopCount = 100;
    do {
      dbSmbusTempVar = 0x1f;
      SmbusIoWrite (SmbusSelect, 0, dbSmbusTempVar);
      IoRead8 (0xED);
      IoRead8 (0xED);
      dbSmbusTempVar = SmbusIoRead (SmbusSelect, 0);
      if ( ! ( dbSmbusTempVar & BIT0) ) {
        IsBusy = FALSE;         // Bit0 = 0, controller is idle
        break;
      }
    } while (LoopCount--);
    if (!IsBusy) {
      break;
    }
    dbSmbusTempVar = BIT1;
    SmbusIoWrite (SmbusSelect, 2, dbSmbusTempVar);
  }

  if (!EFI_ERROR (Status)) {
    StsReg = SmbusIoRead (SmbusSelect, HSTS);
    if ((StsReg & IUS) != 0) {
      Status = EFI_TIMEOUT;
    } else if (StsReg & HBSY) {
      SmbusIoWrite (SmbusSelect, HSTS, HSTS_ALL);
      Status = EFI_TIMEOUT;
    } else {
      Status = CheckSlaveStatus (SmbusSelect);
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

        SmbusIoWrite (SmbusSelect, HSTS, (HBSY + INTR + DERR + BERR + FAIL));
        SmbusIoWrite (SmbusSelect, TSA, SlaveAddressReg);
        SmbusIoWrite (SmbusSelect, HCMD, HostCommandReg);
        SmbusIoWrite (SmbusSelect, HCTL, (UINT8) (SmbusCommand));
        //
        // Do a read from Reg02 to reset
        // the counter if it going to be a
        // block read/write operation
        //
        StsReg = SmbusIoRead (SmbusSelect, HCTL);
        if ((SlaveAddressReg & READ_ENABLE) != 0) {
          if (SmbusCommand == SMB_CMD_BLOCK) {
            SmbusIoWrite (SmbusSelect, HD0, (UINT8)*Length);
          }
        } else {
          if (SmbusCommand == SMB_CMD_BLOCK) {
            SmbusIoWrite (SmbusSelect, HD0, (UINT8)*Length);
            for (Index = 0; Index < *Length; Index++) {
              SmbusIoWrite (SmbusSelect, HBD, Buf [Index]);
            }
          } else if (SmbusCommand == SMB_CMD_WORD_DATA) {
            SmbusIoWrite (SmbusSelect, HD1, Buf [1]);
            SmbusIoWrite (SmbusSelect, HD0, Buf [0]);
          } else {
            SmbusIoWrite (SmbusSelect, HD0, Buf [0]);
          }
        }

        SmbusIoWrite (SmbusSelect, HCTL, (UINT8) (SmbusCommand + START + ((PecCheck) ? (StsReg | 0xA0) : 0)));

        if (! (IoDone (SmbusSelect, &StsReg))) {
          Status = EFI_TIMEOUT;
          break;
        } else if (StsReg & DERR) {
          Status = EFI_DEVICE_ERROR;
          break;
        } else if (StsReg & BERR) {
          Status = EFI_DEVICE_ERROR;
          SmbusIoWrite (SmbusSelect, HSTS, BERR);
          continue;
        }

        Status = SuccessfulCompletion (Operation, SmbusSelect, Buf, Length);

        if ((StsReg & BERR) && (Status != EFI_BUFFER_TOO_SMALL)) {
          Status = EFI_DEVICE_ERROR;
          SmbusIoWrite (SmbusSelect, HSTS, BERR);
          continue;
        } else {
          break;
        }
      } // end for

      SmbusIoWrite (SmbusSelect, HSTS, (HBSY + INTR + DERR + BERR + FAIL));
    } //end if (!EFI_ERROR (Status))
  } //end if (!EFI_ERROR (Status))

  //
  // release SMBUS ownership
  //
  dbSmbusTempVar = SmbusIoRead (SmbusSelect, SMB_IOREG08);
  dbSmbusTempVar |= BIT5;
  SmbusIoWrite (SmbusSelect, SMB_IOREG08, dbSmbusTempVar);
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
  IN       UINT8                      SmbusSelect,
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
    Buf [1] = SmbusIoRead (SmbusSelect, HD1);

  case EfiSmbusReadByte:
    Buf [0] = SmbusIoRead (SmbusSelect, HD0);
    break;

  case EfiSmbusReadBlock:
    BlockCount = SmbusIoRead (SmbusSelect, HD0);
    if (*Length < BlockCount) {
      BlockCount = *Length;
    }
    for (Index = 0; Index < BlockCount; ++Index) {
      Buf [Index] = SmbusIoRead (SmbusSelect, HBD);
    }
    *Length = BlockCount;
    break;

  default:
    break;
  }
  return Status;
}


