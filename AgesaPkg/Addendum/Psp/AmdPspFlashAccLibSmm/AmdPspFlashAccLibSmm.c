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
#include <PiSmm.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Protocol/SmmBase2.h>

typedef
EFI_STATUS
EFIAPI
(*FP_PSP_READ_FLASH) (
  IN       UINTN                                        FlashAddress,
  IN OUT   UINTN                                        *NumBytes,
     OUT   UINT8                                        *Buffer
  );

typedef
EFI_STATUS
EFIAPI
(*FP_PSP_WRITE_FLASH) (
  IN UINTN                                        FlashAddress,
  IN OUT UINTN                                    *NumBytes,
  IN UINT8                                        *Buffer
  );

typedef
EFI_STATUS
EFIAPI
(*FP_PSP_ERASE_FLASH) (
  IN UINTN                                        FlashAddress,
  IN OUT UINTN                                    *NumBytes
  );

typedef
EFI_STATUS
EFIAPI
(*FP_PSP_RPMC_INCMC) (
  IN UINT8   CounterAddr,
  IN UINT32  CounterData,
  IN UINT8*  Signature
  );

typedef
EFI_STATUS
EFIAPI
(*FP_PSP_RPMC_REQMC) (
  IN   UINT8   CounterAddr,
  IN   UINT8   *Tag,
  IN   UINT8   *Signature,
  IN  OUT UINT32  *CounterData
  );

UINTN                                 mBlockSize, mTotalBlocks;
FP_PSP_READ_FLASH                     mPspReadFlash = NULL;
FP_PSP_WRITE_FLASH                    mPspWriteFlash = NULL;
FP_PSP_ERASE_FLASH                    mPspEraseFlash = NULL;
FP_PSP_RPMC_INCMC                     mPspRpmcIncMc = NULL;
FP_PSP_RPMC_REQMC                     mPspRpmcReqMc = NULL;

/**
 * Retrieve block size of Flash Device
 *
 * @param[in]       BlockSize       Size of each block
 *
 * @retval EFI_SUCCESS      Initial success
 * @retval Others           Error happens during initialize
 */
EFI_STATUS
EFIAPI
PspGetFlashBlockSize (
     OUT   UINTN                                       *BlockSize
  )
{
  *BlockSize = mBlockSize;
  return EFI_SUCCESS;
}

/**
 * Read data from Flash device
 *
 * @param[in]       FlashAddress Physical flash address
 * @param[in, out]  NumBytes     Number in Byte; return Bytes been read on output
 * @param[in]       Buffer       Buffer contain the read data (Allocated by caller)
 *
 * @retval EFI_SUCCESS      Initial success
 * @retval Others           Error happens during initialize
 */
EFI_STATUS
EFIAPI
PspReadFlash (
  IN       UINTN                                        FlashAddress,
  IN OUT   UINTN                                        *NumBytes,
     OUT   UINT8                                        *Buffer
  )
{
  EFI_STATUS  Status;

  if (mPspReadFlash == NULL) {
    return (EFI_NOT_FOUND);
  }
  DEBUG ((EFI_D_INFO , "PspReadFlash %x %x\n", FlashAddress, *NumBytes));

  Status =  mPspReadFlash (
                        FlashAddress,
                        NumBytes,
                        Buffer
                        );

  return Status;
}


/**
 * Write data to Flash device
 *
 * @param[in]       FlashAddress Physical flash address
 * @param[in, out]  NumBytes     Number in Byte; return Bytes been written on output
 * @param[in]       Buffer       Buffer contain the written data (Allocated by caller)
 *
 * @retval EFI_SUCCESS      Initial success
 * @retval Others           Error happens during initialize
 */
EFI_STATUS
EFIAPI
PspWriteFlash (
  IN       UINTN                                    FlashAddress,
  IN OUT   UINTN                                    *NumBytes,
  IN       UINT8                                    *Buffer
  )
{
  EFI_STATUS  Status;

  if (mPspWriteFlash == NULL) {
    return (EFI_NOT_FOUND);
  }
  DEBUG ((EFI_D_INFO , "PspWriteFlash %x %x\n", FlashAddress, *NumBytes));

  Status = mPspWriteFlash (
                        FlashAddress,
                        NumBytes,
                        Buffer
                        );

  return Status;
}

/**
 * Erase Flash region according to input in unit of block size
 *
 *
 * @param[in]       FlashAddress Physical flash address
 * @param[in, out]  NumBytes     Number in Byte; return Bytes been erased on output
 *
 * @retval EFI_SUCCESS      Initial success
 * @retval Others           Error happens during initialize
 */
EFI_STATUS
EFIAPI
PspEraseFlash (
  IN       UINTN                                    FlashAddress,
  IN OUT   UINTN                                    *NumBytes
  )
{
  EFI_STATUS  Status;

  if (mPspEraseFlash == NULL) {
    return (EFI_NOT_FOUND);
  }
  DEBUG ((EFI_D_INFO , "PspEraseFlash %x %x\n", FlashAddress, *NumBytes));

  Status = mPspEraseFlash (
                          FlashAddress,
                          NumBytes
                          );

  return (Status);
}

/**
 * Increment the Monotonic counter by 1 inside the Serial Flash Device
 *
 *
 * @param[in]       CounterAddr   CounterAddr for IncMc command
 * @param[in]       CounterData   CounterData for IncMc command
 * @param[in]       Signature     Point to the 32 bytes Signature for IncMc command
 *
 * @retval EFI_SUCCESS      Command success
 * @retval Others           Error happens during handling the command
 */
EFI_STATUS
EFIAPI
PspRpmcIncMc (
  IN UINT8   CounterAddr,
  IN UINT32  CounterData,
  IN UINT8*  Signature
  )
{
  EFI_STATUS  Status;

  if (mPspRpmcIncMc == NULL) {
    return (EFI_NOT_FOUND);
  }
  DEBUG ((EFI_D_INFO , "PspRpmcIncMc %x %x\n", CounterAddr, CounterData));

  Status = mPspRpmcIncMc (
                          CounterAddr,
                          CounterData,
                          Signature
                          );

  return (Status);
}

/**
 * Request the Monotonic counter value inside the Serial Flash Device
 *
 *
 * @param[in]       CounterAddr   CounterAddr for ReqMc command
 * @param[in]       Tag           Tag for ReqMc command
 * @param[in]       Signature     Point to the 32 bytes Signature for ReqMc command
 * @param[in, out]  CounterData   Point to the output CounterData for ReqMc command
  *
 * @retval EFI_SUCCESS      Command success, CounterData is valid
 * @retval Others           Error happens during handling the command
 */
EFI_STATUS
EFIAPI
PspRpmcReqMc (
  IN   UINT8   CounterAddr,
  IN   UINT8   *Tag,
  IN   UINT8   *Signature,
  IN  OUT UINT32  *CounterData
  )
{
  EFI_STATUS  Status;

  if (mPspRpmcReqMc == NULL) {
    return (EFI_NOT_FOUND);
  }
  DEBUG ((EFI_D_INFO , "PspRpmcReqMc %x\n", Req->CounterAddr));

  Status = mPspRpmcReqMc (CounterAddr, Tag, Signature, CounterData);
  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_INFO , "CounterData %x\n", *CounterData));
  }

  return (Status);
}
/**
 * Initial Psp Storage required information
 *
 *
 * @param[in]  SystemTable Point to EFI system table structure
 *
 * @retval EFI_SUCCESS    Initial success
 * @retval Others         Error happens during initialize
 */
EFI_STATUS
EFIAPI
AmdPspFlashAccLibSmmConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_SMM_BASE2_PROTOCOL         *SmmBase2;
  BOOLEAN                        InSmm;
  EFI_SMM_SYSTEM_TABLE2          *Smst;


  DEBUG ((EFI_D_INFO , "AmdPspFlashAccLibSmmConstructor Entry\n"));

  Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**) &SmmBase2);
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  Status = SmmBase2->InSmm (SmmBase2, &InSmm);
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  if (!InSmm) {
    return EFI_SUCCESS;
  }
  Status = SmmBase2->GetSmstLocation (SmmBase2, &Smst);
  if (EFI_ERROR (Status)) {
    return RETURN_SUCCESS;
  }
  //Locate Flash access library required information, the implementation can be varies
  mBlockSize   =  < Filled by OEM > ;
  mPspReadFlash = < Filled by OEM > ;
  mPspWriteFlash = < Filled by OEM > ;
  mPspEraseFlash =  < Filled by OEM > ;
  mPspRpmcIncMc = <Filled by OEM>;
  mPspRpmcReqMc = <Filled by OEM>;

  return EFI_SUCCESS;
}


