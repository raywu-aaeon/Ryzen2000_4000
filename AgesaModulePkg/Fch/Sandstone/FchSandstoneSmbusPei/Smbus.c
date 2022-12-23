/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH PEIM
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH PEIM
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

#include <Library/DebugLib.h>

// Consumed PPI
#include <Ppi/CpuIo.h>
#include <Ppi/Stall.h>

// Produced PPI
#include "Smbus.h"
#define FILECODE UEFI_PEI_SMBUS_SMBUS_FILECODE

extern EFI_GUID gEfiPeiSmbus2PpiGuid;
/*********************************************************************************
 * Name: FchSmbusIoRead8
 *
 * Description
 *   Use the CPU_IO_PPI to do an 8 bits I/O port read
 *
 * Input
 *   Private : a pointer to the private SMBUS data structure
 *   Address : the address to read from
 *
 * Output
 *   UINT8 : the read value
 *
 *********************************************************************************/
UINT8
FchSmbusIoRead8 (
  IN       AMD_SMBUS_PPI_PRIVATE  *Private,
  IN       UINTN                  Address
  )
{
  EFI_PEI_SERVICES    **PeiServices;
  EFI_PEI_CPU_IO_PPI      *CpuIo;

  // Get CPU IO PPI from PEI service pointer
  PeiServices = Private->PeiServices;
  CpuIo = (*PeiServices)->CpuIo;

  // Perform the read
  return (CpuIo->IoRead8 (
                   (CONST EFI_PEI_SERVICES **) PeiServices,
                   CpuIo,
                   Private->BaseAddress + Address
                   ));
}


/*********************************************************************************
 * Name: FchSmbusIoWrite8
 *
 * Description
 *   Use the CPU_IO_PPI to do an 8 bits I/O port write
 *
 * Input
 *   Private : a pointer to the private SMBUS data structure
 *   Address : the address to read from
 *   Data    : the data to write
 *
 * Output
 *
 *********************************************************************************/
VOID
FchSmbusIoWrite8 (
  IN       AMD_SMBUS_PPI_PRIVATE  *Private,
  IN       UINTN                  Address,
  IN       UINT8                  Data
  )
{
  EFI_PEI_SERVICES    **PeiServices;
  EFI_PEI_CPU_IO_PPI      *CpuIo;

  // Get CPU IO PPI from the PEI service pointer
  PeiServices = Private->PeiServices;
  CpuIo = (*PeiServices)->CpuIo;

  // Perform the write
  CpuIo->IoWrite8 (
           (CONST EFI_PEI_SERVICES **) PeiServices,
           CpuIo,
           Private->BaseAddress + Address,
           Data
           );
}


UINT16
ReadPmio16 (
  IN       CONST EFI_PEI_SERVICES    **PeiServices,
  IN       EFI_PEI_CPU_IO_PPI        *CpuIo,
  IN       UINT8                     PmioIndex
  )
{
  UINT16    Value16;

  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD6,
      PmioIndex + 1
      );
  Value16 = (UINT16) (CpuIo->IoRead8 (PeiServices, CpuIo, FCH_IOMAP_REGCD7) << 8);
  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD6,
      PmioIndex
      );
  return (Value16 + CpuIo->IoRead8 (PeiServices, CpuIo, FCH_IOMAP_REGCD7));
}


VOID
WritePmio16 (
  IN       CONST EFI_PEI_SERVICES  **PeiServices,
  IN       EFI_PEI_CPU_IO_PPI      *CpuIo,
  IN       UINT8                   PmioIndex,
  IN       UINT16                  RegValue
  )
{
  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD6,
      PmioIndex + 1
      );
  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD7,
      (UINT8) (RegValue >> 8)
      );
  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD6,
      PmioIndex
      );
  CpuIo->IoWrite8 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_IOMAP_REGCD7,
      (UINT8) (RegValue & 0xFF)
      );
}

/*********************************************************************************
 * Name: SmBusExecute
 *
 * Description
 *   Execute the SMBUS command by calling the worker functions
 *
 * Input
 *   PeiServices  : pointer to the PEI service table (SmBusExecute only)
 *   This         : pointer to the SMBUS (2) PPI instance
 *   SlaveAddress :
 *   Command      :
 *   PecCheck     :
 *   Length       :
 *   Buffer       :
 *
 * Output
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmBusExecute (
  IN       CONST EFI_PEI_SMBUS2_PPI   *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS   SlaveAddress,
  IN       EFI_SMBUS_DEVICE_COMMAND   Command,
  IN       EFI_SMBUS_OPERATION        Operation,
  IN       BOOLEAN                    PecCheck,
  IN OUT   UINTN                      *Length,
  IN OUT   VOID                       *Buffer
  )
{
  AMD_SMBUS_PPI_PRIVATE  *PeiPrivate;
  AMD_SMBUS_PPI_PRIVATE  Private;
  EFI_STATUS             Status;
  EFI_PEI_CPU_IO_PPI         *CpuIo;
  UINT16                 LoopCount;
  UINT8                  retryCount;
  UINT8                  bValue;
  BOOLEAN                IsBusy;
  BOOLEAN                BufferTooSmall;
  UINT8                  SmbusOperation;
  UINT8                  SlvAddrReg;
  UINT8                  HostCmdReg;
  UINT8                  *CallBuffer;
  UINT8                  Index;
  UINT8                  StsReg;
  UINT8                  BlockCount;
  EFI_PEI_SERVICES       **PeiServices;
  UINT32                 DwLoopCount;

  StsReg      = 0;
  BlockCount  = 0;
  CallBuffer  = Buffer;
  Status      = EFI_SUCCESS;

  // Get the PEI service pointer from the private data structure
  PeiPrivate = (AMD_SMBUS_PPI_PRIVATE*) (This);

  // Create the private structure used by the library

  Private.IoRead8     = FchSmbusIoRead8;
  Private.IoWrite8    = FchSmbusIoWrite8;
  Private.PeiServices = PeiPrivate->PeiServices;

  PeiServices = Private.PeiServices;
  CpuIo = (*(Private.PeiServices))->CpuIo;
  Private.BaseAddress = PeiPrivate->BaseAddress;

  //
  // Main I/O sequence starts here
  //
  if (! ((Operation == EfiSmbusQuickRead) || (Operation == EfiSmbusQuickWrite))) {
    if ((Length == NULL) || (Buffer == NULL)) {
      return EFI_INVALID_PARAMETER;
    }
  }


  // Keep polling until host gets SMBUS control
  LoopCount = 100;
  do {
    bValue = Private.IoRead8 (&Private, SMB_IOREG08);
    bValue |= BIT4;       // Set HostSemaphore
    Private.IoWrite8 (&Private, SMB_IOREG08, bValue);
    bValue = CpuIo->IoRead8 (
                      (CONST EFI_PEI_SERVICES **) PeiServices,
                      CpuIo,
                      0xed
                      ); // 0xed IO Delay
    bValue = CpuIo->IoRead8 (
                      (CONST EFI_PEI_SERVICES **) PeiServices,
                      CpuIo,
                      0xed
                      ); // 0xed IO Delay

    bValue = Private.IoRead8 (&Private, SMB_IOREG08);
    LoopCount--;
    if (LoopCount == 0) {
      return EFI_TIMEOUT;
    }
  } while ((bValue & BIT4) == 0);     // Loop until semaphore has established


  // Clear host status and wait until host is idle
  IsBusy = TRUE;
  retryCount = 3;
  while (retryCount--) {
    LoopCount = 100;
    do {
      Private.IoWrite8 (&Private, SMB_IOREG00, SMB_ALL_HOST_STATUS); // Clear all status bits
      bValue = CpuIo->IoRead8 (
                        (CONST EFI_PEI_SERVICES **) PeiServices,
                        CpuIo,
                        0xed
                        );
      bValue = CpuIo->IoRead8 (
                        (CONST EFI_PEI_SERVICES **) PeiServices,
                        CpuIo,
                        0xed
                        );
      bValue = Private.IoRead8 (&Private, SMB_IOREG00);
      if ( ! ( bValue & BIT0) ) {
        IsBusy = FALSE;         // Bit0 = 0, controller is idle
        break;
      }
    } while (LoopCount--);
    if (!IsBusy) {
      break;
    }
    Private.IoWrite8 (&Private, SMB_IOREG02, BIT1);     // Set [1] = Kill current host transaction
  }
  if (IsBusy) {
    return EFI_TIMEOUT;
  }

  // Clear slave status and wait until slave is idle
  IsBusy = TRUE;
  retryCount = 3;
  while (retryCount--) {
    LoopCount = 100;
    do {
      Private.IoWrite8 (&Private, SMB_IOREG01, 0x3f);     // Clear SMB_ALL_SLAVE_STATUS
      bValue = CpuIo->IoRead8 (
                        (CONST EFI_PEI_SERVICES **) PeiServices,
                        CpuIo,
                        0xed
                        );
      bValue = CpuIo->IoRead8 (
                        (CONST EFI_PEI_SERVICES **) PeiServices,
                        CpuIo,
                        0xed
                        );
      bValue = Private.IoRead8 (&Private, SMB_IOREG01);
      if ( ! ( bValue & BIT0) ) {
        IsBusy = FALSE;         // Bit0 = 0, slave is idle
        break;
      }
    } while (LoopCount--);
    if (!IsBusy) {
      break;
    }
    Private.IoWrite8 (&Private, SMB_IOREG01, BIT1);     // Set BIT1 = SlaveInit
  }
  if (IsBusy) {
    return EFI_TIMEOUT;
  }

  // Initialize variables
  SmbusOperation  = SMB_CMD_QUICK;
  SlvAddrReg      = (UINT8) ((SlaveAddress.SmbusDeviceAddress << 1) | SMBUS_READ_ENABLE);
  HostCmdReg      = (UINT8) Command;

  // Process Operation
  switch (Operation) {
  case EfiSmbusQuickWrite:
    SlvAddrReg &= ~SMBUS_READ_ENABLE;
    break;

  case EfiSmbusQuickRead:
    if (PecCheck) {
      Status = EFI_UNSUPPORTED;
    }
    break;

  case EfiSmbusSendByte:
    HostCmdReg = CallBuffer[0];
    SlvAddrReg &= ~SMBUS_READ_ENABLE;
    break;

  case EfiSmbusReceiveByte:
    SmbusOperation = SMB_CMD_BYTE;
    if (*Length < 1) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 1;
    break;

  case EfiSmbusWriteByte:
    SlvAddrReg &= ~SMBUS_READ_ENABLE;

  case EfiSmbusReadByte:
    SmbusOperation = SMB_CMD_BYTE_DATA;
    if (*Length < 1) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 1;
    break;

  case EfiSmbusReadWord:
    SmbusOperation = SMB_CMD_WORD_DATA;
    if (*Length < 2) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 2;
    break;

  case EfiSmbusWriteWord:
    SmbusOperation = SMB_CMD_WORD_DATA;
    SlvAddrReg &= ~SMBUS_READ_ENABLE;
    if (*Length < 2) {
      Status = EFI_BUFFER_TOO_SMALL;
    }
    *Length = 2;
    break;

  case EfiSmbusWriteBlock:
    SlvAddrReg &= ~SMBUS_READ_ENABLE;
    BlockCount = (UINT8) (*Length);
    SmbusOperation = SMB_CMD_BLOCK;
    break;

  case EfiSmbusReadBlock:
    SmbusOperation = SMB_CMD_BLOCK;
    if ((*Length < 1) || (*Length > 72)) {
      Status = EFI_INVALID_PARAMETER;
      break;
    }
    break;

  case EfiSmbusBWBRProcessCall:
    Status = EFI_UNSUPPORTED;
    break;

  default:
    Status = EFI_INVALID_PARAMETER;
    break;
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // If the operation results in a Smbus collision with another master on the bus, it attempts
  // the requested transaction again for at least TRY_TIMES attempts. We assume the value of
  // TRY_TIMES is 3.
  //
  for (retryCount = 0; retryCount < TRY_TIMES; retryCount++) {
    // Clear all status Bits
    Private.IoWrite8 (&Private, SMB_IOREG00, SMB_ALL_HOST_STATUS);

    // Set SMBus slave address for the device to send/receive from
    Private.IoWrite8 (&Private, SMB_IOREG04, SlvAddrReg);

    // Set Command register
    Private.IoWrite8 (&Private, SMB_IOREG03, HostCmdReg);

    // Select SMBus protocol
    Private.IoWrite8 (&Private, SMB_IOREG02, (UINT8)SmbusOperation);

    //
    // Do a read from Reg02 to reset the counter if it's going to be a
    // block read/write operation
    //
    StsReg = Private.IoRead8 (&Private, SMB_IOREG02);


    if (SlvAddrReg & SMBUS_READ_ENABLE) {
      if (SmbusOperation == SMB_CMD_BLOCK) {
        Private.IoWrite8 (&Private, SMB_IOREG05, *(UINT8*)Length);
      }
    } else {
      if (SmbusOperation == SMB_CMD_BLOCK) {
        Private.IoWrite8 (&Private, SMB_IOREG05, *(UINT8*)Length);
        for (Index = 0; Index < *Length; Index++) {
          Private.IoWrite8 (&Private, SMB_IOREG07, CallBuffer[Index]);
        }
      } else if (SmbusOperation == SMB_CMD_WORD_DATA) {
        Private.IoWrite8 (&Private, SMB_IOREG06, CallBuffer[1]);
        Private.IoWrite8 (&Private, SMB_IOREG05, CallBuffer[0]);
      } else {
        Private.IoWrite8 (&Private, SMB_IOREG05, CallBuffer[0]);
      }
    }

    // Set Control Register (Initiate Operation, Interrupt disabled)
    Private.IoWrite8 (&Private, SMB_IOREG02, \
                        (UINT8) (SmbusOperation + BIT6 + ((PecCheck) ? (StsReg | 0xA0) : 0)));  // [6] = Start

    // Wait for controller IO to finish work
    do {
      DwLoopCount = 100;
      do {
        bValue = CpuIo->IoRead8 (
                          (CONST EFI_PEI_SERVICES **) PeiServices,
                          CpuIo,
                          0xed
                          );
        bValue = CpuIo->IoRead8 (
                          (CONST EFI_PEI_SERVICES **) PeiServices,
                          CpuIo,
                          0xed
                          );
        StsReg = Private.IoRead8 (&Private, SMB_IOREG00);
        if ( ! ( StsReg & BIT0) ) {
          break;   // SmBusStat Bit0 = 0, Host is not busy
        }
      } while (--DwLoopCount);
      if ( DwLoopCount == 0) {
        Private.IoWrite8 (&Private, SMB_IOREG02, BIT1);     // Set [1] = Kill current host transaction
        return EFI_TIMEOUT;
      }
      bValue = CpuIo->IoRead8 (
                          (CONST EFI_PEI_SERVICES **) PeiServices,
                          CpuIo,
                          0xed
                          );
      bValue = CpuIo->IoRead8 (
                          (CONST EFI_PEI_SERVICES **) PeiServices,
                          CpuIo,
                          0xed
                          );
      StsReg = Private.IoRead8 (&Private, SMB_IOREG00);
    } while ((StsReg & (BIT3 + BIT2 + BIT1)) == 0);

    if (StsReg & BIT2) {
      Status = EFI_DEVICE_ERROR;
      break;
    }
    if (StsReg & BIT3) {
      // Clear bus error for another try
      Private.IoWrite8 (&Private, SMB_IOREG00, BIT3);
      continue;
    }


    //
    // Successful completion
    //
    switch (Operation) {
    case EfiSmbusReadWord:

    case EfiSmbusProcessCall:
      // Read a byte from Host data 1
      CallBuffer[1] = Private.IoRead8 (&Private, SMB_IOREG06);
      CallBuffer[0] = Private.IoRead8 (&Private, SMB_IOREG05);
      break;

    case EfiSmbusReceiveByte:
    case EfiSmbusReadByte:
      // Read a byte from Host data 0
      CallBuffer[0] = Private.IoRead8 (&Private, SMB_IOREG05);
      break;

    case EfiSmbusReadBlock:
      BufferTooSmall = FALSE;
      BlockCount = Private.IoRead8 (&Private, SMB_IOREG02);
      BlockCount = Private.IoRead8 (&Private, SMB_IOREG05);
      if (*Length < BlockCount) {
        BufferTooSmall = TRUE;
      } else {
        for (Index = 0; Index < BlockCount; Index++) {
          // Read the byte
          CallBuffer[Index] = Private.IoRead8 (&Private, SMB_IOREG07);
        }
      }
      *Length = BlockCount;
      if (BufferTooSmall) {
        Status = EFI_BUFFER_TOO_SMALL;
      }
      break;

    default:
      break;
    }

    if ((StsReg & BIT3) && (Status != EFI_BUFFER_TOO_SMALL)) {
      // Clear 'Bus Error' bit of 'Status Register'
      Status = EFI_DEVICE_ERROR;
      Private.IoWrite8 (&Private, SMB_IOREG00, BIT3);
      continue;
    } else {
      break;
    }
  }

  // Clear host controller status
  Private.IoWrite8 (&Private, SMB_IOREG00, SMB_ALL_HOST_STATUS);


  // Release SMBUS ownership
  bValue = Private.IoRead8 (&Private, SMB_IOREG08);
  bValue |= BIT5;        // Clear Host Semaphore
  Private.IoWrite8 (&Private, SMB_IOREG08, bValue);

  return Status;
}


/********************************************************************************
 * Name: SmBusArpDevice
 *
 * Description
 *   Perform ARP resolution. function currently not supported
 *
 * Input
 *
 * Output
 *   EFI_UNSUPPORTED : unsupported function
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmBusArpDevice (
  IN       CONST EFI_PEI_SMBUS2_PPI      *This,
  IN       BOOLEAN                       ArpAll,
  IN       EFI_SMBUS_UDID                *SmbusUdid,   OPTIONAL
  IN OUT   EFI_SMBUS_DEVICE_ADDRESS      *SlaveAddress OPTIONAL
  )
{
  // currently not supported
  return EFI_UNSUPPORTED;
}


/*********************************************************************************
 * Name: SmBusGetArpMap
 *
 * Description
 *   Get the ARP map. function currently not supported
 *
 * Input
 *
 * Output
 *   EFI_UNSUPPORTED : unsupported function
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmBusGetArpMap (
  IN       CONST EFI_PEI_SMBUS2_PPI  *This,
  IN OUT   UINTN                     *Length,
  IN OUT   EFI_SMBUS_DEVICE_MAP      **SmbusDeviceMap
  )
{
  // currently not supported
  return EFI_UNSUPPORTED;
}


/*********************************************************************************
 * Name: SmBusNotify
 *
 * Description
 *   Register a notify function. function currently not supported
 *
 * Input
 *
 * Output
 *   EFI_UNSUPPORTED : unsupported function
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
SmBusNotify (
  IN       CONST EFI_PEI_SMBUS2_PPI         *This,
  IN       EFI_SMBUS_DEVICE_ADDRESS         SlaveAddress,
  IN       UINTN                            Data,
  IN       EFI_PEI_SMBUS_NOTIFY2_FUNCTION   NotifyFunction
  )
{
  // currently not supported
  return EFI_UNSUPPORTED;
}




/*********************************************************************************
 * Name: AmdSmbusPeiInit
 *
 * Description
 *   Entry point of the AMD SMBUS PEIM
 *   Initialize the SMBUS controller and publish the PPIs (both version 1 and 2
 *   are supported)
 *
 * Input
 *   FfsHeader   : pointer to the firmware file system header
 *   PeiServices : pointer to the PEI service table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
AmdSmbusPeiInit (
  IN       EFI_PEI_FILE_HANDLE    FileHandle,
  IN       CONST EFI_PEI_SERVICES **PeiServices
  )
{
  EFI_STATUS                Status;
  AMD_PEI_FCH_SMBUS_PRIVATE *SmbusPrivate;
  EFI_PEI_PPI_DESCRIPTOR    *PpiListSmBus;
  EFI_PEI_CPU_IO_PPI        *CpuIo;
  UINT16                    Value16;

  CpuIo = (*PeiServices)->CpuIo;

  //
  // Create the PPIs
  //
  Status = (*PeiServices)->AllocatePool (
                             (CONST EFI_PEI_SERVICES **) PeiServices,
                             sizeof (AMD_PEI_FCH_SMBUS_PRIVATE),
                             (VOID **)&SmbusPrivate
                             );

  ASSERT_EFI_ERROR (Status);

  //
  // Initialize the structure
  //

  SmbusPrivate->SmbusPpi0.PeiServices        = (EFI_PEI_SERVICES **)PeiServices;
  SmbusPrivate->SmbusPpi0.SmbusPpi.Execute   = SmBusExecute;
  SmbusPrivate->SmbusPpi0.SmbusPpi.ArpDevice = SmBusArpDevice;
  SmbusPrivate->SmbusPpi0.SmbusPpi.GetArpMap = SmBusGetArpMap;
  SmbusPrivate->SmbusPpi0.SmbusPpi.Notify    = SmBusNotify;

  Value16 = ReadPmio16 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_PMIOA_REG04
      );
  WritePmio16 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_PMIOA_REG04,
      Value16 | BIT1
      );
  Value16 = ReadPmio16 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_PMIOA_REG00
      );
  ASSERT (Value16);
  WritePmio16 (
      (CONST EFI_PEI_SERVICES **) PeiServices,
      CpuIo,
      FCH_PMIOA_REG00,
      Value16 | BIT4
      );
  Value16 &= 0xFF00;
  SmbusPrivate->SmbusPpi0.BaseAddress        = Value16;
  SmbusPrivate->SmbusPpi0.RegisterIndex      = FCH_PMIOA_REG00;

  SmbusPrivate->SmbusPpi1.PeiServices        = (EFI_PEI_SERVICES **)PeiServices;
  SmbusPrivate->SmbusPpi1.SmbusPpi.Execute   = SmBusExecute;
  SmbusPrivate->SmbusPpi1.SmbusPpi.ArpDevice = SmBusArpDevice;
  SmbusPrivate->SmbusPpi1.SmbusPpi.GetArpMap = SmBusGetArpMap;
  SmbusPrivate->SmbusPpi1.SmbusPpi.Notify    = SmBusNotify;

  SmbusPrivate->SmbusPpi1.BaseAddress        = Value16 + 0x20;
  SmbusPrivate->SmbusPpi1.RegisterIndex      = FCH_PMIOA_REG00;

  //
  // Install the PPIs
  //
  Status = (*PeiServices)->AllocatePool (
                             (CONST EFI_PEI_SERVICES **) PeiServices,
                             (sizeof (EFI_PEI_PPI_DESCRIPTOR) * 2),
                             (VOID **)&PpiListSmBus
                             );

  ASSERT_EFI_ERROR (Status);
  //
  // Create the PPI descriptor
  //
  PpiListSmBus[0].Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI);
  PpiListSmBus[0].Guid  = &gEfiPeiSmbus2PpiGuid;
  PpiListSmBus[0].Ppi   = &(SmbusPrivate->SmbusPpi0.SmbusPpi);

  PpiListSmBus[1].Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  PpiListSmBus[1].Guid  = &gEfiPeiSmbus2PpiGuid;
  PpiListSmBus[1].Ppi   = &(SmbusPrivate->SmbusPpi1.SmbusPpi);
  PpiListSmBus[1].Ppi   = &(SmbusPrivate->SmbusPpi1.SmbusPpi);

  // The SMBUS host controllers should have been enabled earlier so nothing need to do here

  //
  // Publish the PPI
  //
  Status = (*PeiServices)->InstallPpi (
                             (CONST EFI_PEI_SERVICES **) PeiServices,
                             PpiListSmBus
                             );
  return Status;
}



