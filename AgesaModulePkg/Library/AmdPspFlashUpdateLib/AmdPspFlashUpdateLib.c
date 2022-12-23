/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Flash Access DXE Library
 * It will route the Flash access to SMM libary through SMM communication protocol
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspStorage Library
 * @e \$Revision$   @e \$Date$
 *
 *//*****************************************************************************
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
#include <PiDxe.h>
#include <Library/AmdPspFlashAccLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPFLASHUPDATELIB_AMDPSPFLASHUPDATELIB_FILECODE


/**
 *  Update Flash region with Buffer
 *
 *  @param[in]  Address   Address on flash
 *  @param[in]  Size      Size of the buffer
 *  @param[in]  Buffer    Pointing to the start of the Buffer
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
PspUpdateFlash (
  IN       UINT32 Address,
  IN       UINT32 Size,
  IN       VOID  *Buffer
  )
{
  EFI_STATUS                      Status;
  UINTN                           FlashStartAddr;
  UINTN                           FlashBytes;
  UINT8                           *TempBuffer;
  UINTN                           NumBytes;
  UINTN                           BlockSize;

  IDS_HDT_CONSOLE_PSP_TRACE ("Updating SPI %x %x %x\n", Address, Size, Buffer);
  //Get the block size
  PspGetFlashBlockSize (&BlockSize);
  //Make sure the address on the boundary of SPI block size
  FlashStartAddr = Address & (~ (BlockSize - 1));
  if (((Address + Size) % BlockSize) == 0) {
    FlashBytes = ((UINTN) Address + Size) - FlashStartAddr;
  } else {
    FlashBytes = (((UINTN) Address + Size + BlockSize) & (~ (BlockSize - 1))) - FlashStartAddr;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Calc FlashAddr %x %x\n", FlashStartAddr, FlashBytes);
  //Read the block
  TempBuffer = NULL;
  TempBuffer = AllocateRuntimeZeroPool (FlashBytes);
  ASSERT (TempBuffer != NULL);
  CopyMem (TempBuffer, (VOID *) FlashStartAddr, FlashBytes);
  //Update the block
  CopyMem (TempBuffer + (Address - FlashStartAddr), Buffer, Size);
  //Erase the blocks
  NumBytes = FlashBytes;
  Status = EFI_UNSUPPORTED;
  Status = PspEraseFlash (FlashStartAddr, &NumBytes);
  ASSERT (NumBytes == FlashBytes);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    FreePool(TempBuffer);
    return Status;
  }
  //Write the data
  NumBytes = FlashBytes;
  Status = EFI_UNSUPPORTED;
  Status = PspWriteFlash (FlashStartAddr, &NumBytes, TempBuffer);
  ASSERT (NumBytes == FlashBytes);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    FreePool(TempBuffer);
    return Status;
  }
  FreePool(TempBuffer);
  IDS_HDT_CONSOLE_PSP_TRACE ("Updated\n");

  return EFI_SUCCESS;
}

