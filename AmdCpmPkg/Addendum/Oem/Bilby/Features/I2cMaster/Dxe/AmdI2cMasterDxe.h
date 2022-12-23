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

#ifndef _AMD_I2C_MASTER_DXE_H_
#define _AMD_I2C_MASTER_DXE_H_

UINT32 I2cSdpAddressList[] = {
//   0xFEDC2000,
//  0xFEDC3000,
   0xFEDC4000,  //I2C2 maps to SMN space as D4000 - D4FFF and SDP address as FEDC4000 - FEDC4FFF
//   0xFEDC5000,  //I2C3 maps to SMN space as D5000 - D5FFF and SDP address as FEDC5000 - FEDC5FFF.
//   0xFEDC6000,  //I2C4 maps to SMN space as D6000 - D6FFF and SDP address as FEDC6000 - FEDC6FFF.
//   0xFEDCB000
};

typedef struct _I2C_CONFIGURATION {
  UINT32 RxFifoDepth;
  UINT32 TxFifoDepth;
} I2C_CONFIGURATION;

#define I2C_CONTROLLER_COUNT  (sizeof (I2cSdpAddressList) / sizeof (UINT32))

typedef struct _I2CMASTER_PRIVATE
{
    EFI_I2C_MASTER_PROTOCOL   I2cController;
    EFI_HANDLE                Handle;                         ///< Handle
    UINT32                    I2cSdpAddress;
    UINT8                     *WriteData;
    UINT32                    WriteCount;
    UINT8                     *ReadData;
    UINT32                    ReadCount;
    UINT32                    TransferCount;
    I2C_CONFIGURATION         I2cConfiguration;
} I2CMASTER_PRIVATE;

/// Private I2C Master Data Block Structure
typedef struct _AMD_I2C_MASTER_PRIVATE {
  I2CMASTER_PRIVATE   I2cMaster[I2C_CONTROLLER_COUNT];      ///< I2c0~5 Data Block
} AMD_I2C_MASTER_PRIVATE;

EFI_STATUS
EFIAPI
SetBusFrequency (
  IN CONST EFI_I2C_MASTER_PROTOCOL   *This,
  IN UINTN                    *BusClockHertz
  );

EFI_STATUS
EFIAPI
Reset (
  IN CONST EFI_I2C_MASTER_PROTOCOL *This
  );

EFI_STATUS
EFIAPI
StartRequest (
   IN CONST EFI_I2C_MASTER_PROTOCOL    *This,
   IN UINTN                            SlaveAddress,
   IN EFI_I2C_REQUEST_PACKET           *RequestPacket,
   IN EFI_EVENT                        Event      OPTIONAL,
   OUT EFI_STATUS                      *I2cStatus OPTIONAL
  );


//*******************************************************
//      AmdI2cMasterPei.c use only functions prototypes
//*******************************************************

EFI_STATUS
I2cInit(
   IN OUT I2CMASTER_PRIVATE    *Private
   );

EFI_STATUS
I2cWriteRead(
  IN OUT I2CMASTER_PRIVATE    *Private
  );

EFI_STATUS
I2cAccess(
   IN I2CMASTER_PRIVATE             *Private,
   IN UINTN                         SlaveAddress,
   IN OUT EFI_I2C_REQUEST_PACKET    *RequestPacket
  );

EFI_STATUS
I2cDwWaitI2cEnable(
   IN  UINT32   Base,
   IN  UINT32   I2cEnBit
  );

//
// Functions Prototypes
//
EFI_STATUS
EFIAPI
AmdI2cMasterDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  );

#endif // _AMD_I2C_MASTER_DXE_H_
