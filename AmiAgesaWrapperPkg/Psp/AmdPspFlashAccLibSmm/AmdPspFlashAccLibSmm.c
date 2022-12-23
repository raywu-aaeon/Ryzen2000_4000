/*****************************************************************************
 *
 * Copyright 2008 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software (the Materials)
 * pursuant to the terms and conditions of your Software License Agreement
 * with AMD.  This header does *NOT* give you permission to use the Materials
 * or any rights under AMD's intellectual property.  Your use of any portion
 * of these Materials shall constitute your acceptance of those terms and
 * conditions.  If you do not agree to the terms and conditions of the Software
 * License Agreement, please do not use any portion of these Materials.
 *
 * CONFIDENTIALITY:  The Materials and all other information, identified as
 * confidential and provided to you by AMD shall be kept confidential in
 * accordance with the terms and conditions of the Software License Agreement.
 *
 * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
 * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
 * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
 * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
 * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
 * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
 * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
 * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
 * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
 * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
 *
 * AMD does not assume any responsibility for any errors which may appear in
 * the Materials or any other related information provided to you by AMD, or
 * result from use of the Materials or any related information.
 *
 * You agree that you will not reverse engineer or decompile the Materials.
 *
 * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
 * further information, software, technical information, know-how, or show-how
 * available to you.  Additionally, AMD retains the right to modify the
 * Materials at any time, without notice, and is not obligated to provide such
 * modified Materials to you.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgement of AMD's proprietary rights in them.
 *
 * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
 * direct product thereof will be exported directly or indirectly, into any
 * country prohibited by the United States Export Administration Act and the
 * regulations thereunder, without the required authorization from the U.S.
 * government nor will be used for any purpose prohibited by the same.
 ******************************************************************************
 */
#include <PiSmm.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Token.h>
#include <Protocol/FlashProtocol.h>
#include <Protocol/SmmBase2.h>
#include <Library/AmiBufferValidationLib.h>
#include <Library/BaseMemoryLib.h>

#if defined(AMI_DEBUGGER_SUPPORT) && (AMI_DEBUGGER_SUPPORT == 1)
#include <Library/IoLib.h>
// Check if SCI turn on (EnableAcpiMode).
#undef DEBUG_INFO
#define DEBUG_INFO ((IoRead16(PM_BASE_ADDRESS + 0x04) & BIT0) ? 0 : 0x00000040)
#endif

FLASH_PROTOCOL          *AmiPspFlash = NULL;
UINTN                   AmiFlashBlockSize;
FLASH_PROTOCOL          AmiAgesaFlashProtocol;  // this is an original flash protocol copy

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
  *BlockSize = AmiFlashBlockSize;
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

  if (AmiPspFlash == NULL) {
    return (EFI_NOT_FOUND);
  }

  DEBUG ((DEBUG_INFO , "PspReadFlash %x %x\n", FlashAddress, *NumBytes));
  Status = AmiAgesaFlashProtocol.Read ((VOID*)FlashAddress, *NumBytes, Buffer);

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
  IN UINTN                                        FlashAddress,
  IN OUT UINTN                                    *NumBytes,
  IN UINT8                                        *Buffer
  )
{
  EFI_STATUS  Status;

  if (AmiPspFlash == NULL) {
    return (EFI_NOT_FOUND);
  }
  
  DEBUG ((DEBUG_INFO , "PspWriteFlash %x %x\n", FlashAddress, *NumBytes));
  Status = AmiAgesaFlashProtocol.Write ((VOID*)FlashAddress, *NumBytes, Buffer);

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
  IN UINTN                                        FlashAddress,
  IN OUT UINTN                                    *NumBytes
  )
{
  EFI_STATUS  Status;

  if (AmiPspFlash == NULL) {
    return (EFI_NOT_FOUND);
  }

  ASSERT ((*NumBytes) % AmiFlashBlockSize == 0);
  DEBUG ((DEBUG_INFO , "PspEraseFlash %x %x\n", FlashAddress, *NumBytes));

  Status = AmiAgesaFlashProtocol.Erase ((VOID*)FlashAddress, *NumBytes);

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
  //EFI_STATUS  Status;

  //if (mPspRpmcIncMc == NULL) {
    return (EFI_NOT_FOUND);
  /*}
  DEBUG ((EFI_D_INFO , "PspRpmcIncMc %x %x\n", CounterAddr, CounterData));

  Status = mPspRpmcIncMc (
                          CounterAddr,
                          CounterData,
                          Signature
                          );

  return (Status);*/
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
  //EFI_STATUS  Status;

  //if (mPspRpmcReqMc == NULL) {
    return (EFI_NOT_FOUND);
  /*}
  DEBUG ((EFI_D_INFO , "PspRpmcReqMc %x\n", Req->CounterAddr));

  Status = mPspRpmcReqMc (CounterAddr, Tag, Signature, CounterData);
  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_INFO , "CounterData %x\n", *CounterData));
  }

  return (Status);*/
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


  DEBUG ((DEBUG_INFO , "AmdPspFlashAccLibSmmConstructor Entry\n"));

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
  //Locate Flash access protocol, the protocol GUID, definition, implementation can be varies between different platform
  //gSmmFlashAccessProtocollGuid is just a example
  if (AmiPspFlash == NULL)
  {
      // The Flash protocol that we locate at the first time is not modified by security flash module
      Status = Smst->SmmLocateProtocol (
                    &gFlashSmmProtocolGuid,
                    NULL,
                    &AmiPspFlash
                    );
      if (EFI_ERROR(Status)) {
          return Status;
      }
      CopyMem(&AmiAgesaFlashProtocol, AmiPspFlash, sizeof(AmiAgesaFlashProtocol));
  }

  AmiFlashBlockSize = FLASH_BLOCK_SIZE;
  DEBUG ((DEBUG_INFO , "AmiFlashBlockSize = %x\n", AmiFlashBlockSize));

  return EFI_SUCCESS;
}

