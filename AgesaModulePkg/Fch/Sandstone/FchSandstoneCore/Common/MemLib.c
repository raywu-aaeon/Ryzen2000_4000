/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH memory access lib
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*
*****************************************************************************
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
#include "FchPlatform.h"
#define FILECODE FCH_TAISHAN_FCHTAISHANCORE_COMMON_MEMLIB_FILECODE


/**
 * ReadMem - Read FCH BAR Memory
 *
 * @param[in] Address    - Memory BAR address
 * @param[in] OpFlag     - Access width
 * @param[in] *ValuePtr  - In/Out value pointer
 *
 */
VOID
ReadMem (
  IN  UINT32     Address,
  IN  UINT8      OpFlag,
  IN  VOID       *ValuePtr
  )
{
  OpFlag = OpFlag & 0x7f;

  switch ( OpFlag ) {
  case AccessWidth8:
    *((UINT8*)ValuePtr) = *((volatile UINT8*) ((UINTN)Address));
    break;

  case AccessWidth16:
    *((UINT16*)ValuePtr) = *((volatile UINT16*) ((UINTN)Address));
    break;

  case AccessWidth32:
    *((UINT32*)ValuePtr) = *((volatile UINT32*) ((UINTN)Address));
    break;

  default:
    ASSERT (FALSE);
    break;
  }
}

/**
 * WriteMem - Write FCH BAR Memory
 *
 * @param[in] Address    - Memory BAR address
 * @param[in] OpFlag     - Access width
 * @param[in] *ValuePtr  - In/Out Value pointer
 *
 */
VOID
WriteMem (
  IN  UINT32     Address,
  IN  UINT8      OpFlag,
  IN  VOID       *ValuePtr
  )
{
  OpFlag = OpFlag & 0x7f;

  switch ( OpFlag ) {
  case AccessWidth8 :
    *((volatile UINT8*) ((UINTN)Address)) = *((UINT8*)ValuePtr);
    break;

  case AccessWidth16:
    *((volatile UINT16*) ((UINTN)Address)) = *((UINT16*)ValuePtr);
    break;

  case AccessWidth32:
    *((volatile UINT32*) ((UINTN)Address)) = *((UINT32*)ValuePtr);
    break;

  default:
    ASSERT (FALSE);
    break;
  }
}

/**
 * RwMem - Read & Write FCH BAR Memory
 *
 * @param[in] Address    - Memory BAR address
 * @param[in] OpFlag     - Access width
 * @param[in] Mask       - Mask Value of data
 * @param[in] Data       - Write data
 *
 */
VOID
RwMem (
  IN  UINT32     Address,
  IN  UINT8      OpFlag,
  IN  UINT32     Mask,
  IN  UINT32     Data
  )
{
  UINT32 Result;

  ReadMem (Address, OpFlag, &Result);
  Result = (Result & Mask) | Data;
  WriteMem (Address, OpFlag, &Result);
  ReadMem (Address, OpFlag, &Result);
}


