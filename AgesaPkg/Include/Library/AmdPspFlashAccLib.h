/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Flash Access Library Routines declaration
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspStorage Library
 * @e \$Revision$   @e \$Date$
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

#ifndef _PSP_FLASH_ACC_LIB_H_
#define _PSP_FLASH_ACC_LIB_H_

#include "Uefi.h"

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
  OUT UINTN                                       *BlockSize
  );

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
  IN UINTN                                        FlashAddress,
  IN OUT UINTN                                    *NumBytes,
  IN UINT8                                        *Buffer
  );

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
  );

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
  );

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
  );

/**
 * Request the Monotonic counter value inside the Serial Flash Device
 *
 *
 * @param[in]       CounterAddr   CounterAddr for ReqMc command
 * @param[in]       Tag           Tag for ReqMc command
 * @param[in]       Signature     Point to the 32 bytes Signature for ReqMc command
 * @param[in, out]  CounterData   Point to the output CounterData for ReqMc command
 
 * @retval EFI_SUCCESS      Command success, CounterData is valid
 * @retval Others           Error happens during handling the command
 */
EFI_STATUS
EFIAPI
PspRpmcReqMc (
  IN   UINT8   CounterAddr,
  IN   UINT8   *Tag,
  IN   UINT8   *Signature,
  IN  OUT UINT32  *CounterData,
  IN  OUT UINT8   *OutputSignature
  );
#endif  //_PSP_FLASH_ACC_LIB_H_

