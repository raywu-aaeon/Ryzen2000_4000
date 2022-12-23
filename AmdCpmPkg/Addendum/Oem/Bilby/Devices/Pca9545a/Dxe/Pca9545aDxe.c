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

#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/I2cMaster.h>
#include <Protocol/Pca9545aProtocol.h>
#include "Pca9545aDxe.h"

extern  EFI_BOOT_SERVICES       *gBS;

EFI_DXE_PCA9545A_PROTOCOL mDxePca9545aProtocol = {
  PCA9545A_DXE_REVISION,
  Pca9545aSetDxe,
  Pca9545aGetDxe
};

//
// Driver Global Data
//

/*********************************************************************************
 * Name: Pca9545aDxeInit
 *
 * Description
 *   Entry point of the AMD PCA9545A DXE driver
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
Pca9545aDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle;

  Handle = ImageHandle;

  // Publish Error Log service Protocol For IP driver
  Status = gBS->InstallProtocolInterface (
                &Handle,
                &gPca9545aProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mDxePca9545aProtocol
                );

  return (Status);
}

EFI_STATUS
EFIAPI
Pca9545aSetDxe (
  IN       EFI_DXE_PCA9545A_PROTOCOL  *This,
  IN       UINTN             BusSelect,
  IN       UINTN             SlaveAddress,
  IN       UINT8             ControlByte
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_I2C_MASTER_PROTOCOL  *I2cMaster;
  EFI_I2C_REQUEST_PACKET  RequestPacket;
  EFI_I2C_OPERATION       *Operation;

  Status = gBS->LocateProtocol (&gEfiI2cMasterProtocolGuid, NULL, &I2cMaster);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //Write Byte Operation
  Operation   = RequestPacket.Operation;
  RequestPacket.OperationCount = 1;
  Operation[0].Flags           = 0;
  Operation[0].LengthInBytes   = 1;
  Operation[0].Buffer          = &ControlByte;

  Status = I2cMaster->StartRequest(I2cMaster, SlaveAddress, &RequestPacket, NULL, NULL);

  return Status;
}

EFI_STATUS
EFIAPI
Pca9545aGetDxe (
  IN       EFI_DXE_PCA9545A_PROTOCOL  *This,
  IN       UINTN             BusSelect,
  IN       UINTN             SlaveAddress,
  OUT      UINT8             *ControlByte
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_I2C_MASTER_PROTOCOL  *I2cMaster;
  EFI_I2C_REQUEST_PACKET  RequestPacket;
  EFI_I2C_OPERATION       *Operation;

  Status = gBS->LocateProtocol (&gEfiI2cMasterProtocolGuid, NULL, &I2cMaster);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Operation   = RequestPacket.Operation;
  RequestPacket.OperationCount = 1;
  Operation[0].Flags            = I2C_FLAG_READ;
  Operation[0].LengthInBytes    = 1;
  Operation[0].Buffer           = ControlByte;

  Status = I2cMaster->StartRequest(I2cMaster, SlaveAddress, &RequestPacket, NULL, NULL);

  return Status;
}
