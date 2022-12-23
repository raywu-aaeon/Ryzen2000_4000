/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Zen - Zeppelin API, and related functions.
 *
 * Contains code that initializes the core complex
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
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
/*++
Module Name:

  CcxZenZpCacheInit.c
  Initialize Cache

Abstract:
--*/

#include <Library/BaseLib.h>
#include <AGESA.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxBaseX86Lib.h>

#define FILECODE CCX_ZEN_CCXZENZPPEI_CCXZENZPCACHEINIT_FILECODE


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 * Program MTRRs to describe given range as given cache type.  Use MTRR pairs
 * starting with the given MTRRphys Base address, and use as many as is
 * required up to (excluding) MSR 020C, which is reserved for OS.
 *
 * "Limit" in the context of this procedure is not the numerically correct
 * limit, but rather the Last address+1, for purposes of coding efficiency
 * and readability.  Size of a region is then Limit-Base.
 *
 * 1. Size of each range must be a power of two
 * 2. Each range must be naturally aligned (Base is same as size)
 *
 * There are two code paths: the ascending path and descending path (analogous
 * to bsf and bsr), where the next limit is a function of the next set bit in
 * a forward or backward sequence of bits (as a function of the Limit).  We
 * start with the ascending path, to ensure that regions are naturally aligned,
 * then we switch to the descending path to maximize MTRR usage efficiency.
 * Base=0 is a special case where we start with the descending path.
 * Correct Mask for region is 2comp(Size-1)-1,
 * which is 2comp(Limit-Base-1)-1 *
 * @param[in]     Base - Base address[47:16] of specified range.
 * @param[in]     *LimitPtr - Limit address[47:16] of specified range.
 * @param[in]     MtrrAddr - address of var MTRR pair to start using.
 * @param[in]     MtrrType - Cache type for the range.
 * @param[in]  StdHeader         Config handle for library and services
 *
 *
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
SetVariableMTRRs (
  IN       UINT32            Base,
  IN OUT   UINT32            *LimitPtr,
  IN       UINT32            MtrrAddr,
  IN       UINT8             MtrrType,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT64 LocalMsrRegister;
  UINT32 CurBase;
  UINT32 CurLimit;
  UINT32 CurSize;
  UINT32 CurAddr;
  UINT32 Value32;

  CurBase = Base;
  CurLimit = *LimitPtr;
  CurAddr = MtrrAddr;

  while ((CurAddr >= 0x200) && (CurAddr < 0x20C) && (CurBase < *LimitPtr)) {
    CurSize = CurLimit = (UINT32) 1 << (LowBitSet32 (CurBase) == -1 ? 31 : LowBitSet32 (CurBase)) ;
    CurLimit += CurBase;
    if ((CurBase == 0) || (*LimitPtr < CurLimit)) {
      CurLimit = *LimitPtr - CurBase;
      CurSize = CurLimit = (UINT32) 1 << (HighBitSet32 (CurLimit) == -1 ? 31 : HighBitSet32 (CurLimit));
      CurLimit += CurBase;
    }

    // prog. MTRR with current region Base
    LocalMsrRegister = (CurBase << 16) | (UINT32) MtrrType;
    AsmWriteMsr64 (CurAddr, LocalMsrRegister);

    // prog. MTRR with current region Mask
    CurAddr++;                              // other half of MSR pair
    Value32 = CurSize - (UINT32) 1;
    Value32 = ~Value32;
    LocalMsrRegister = 0xFFFF00000000ull | (Value32 << 16) | ((UINT32) 1 << 11);
    AsmWriteMsr64 (CurAddr, LocalMsrRegister);

    CurBase = CurLimit;
    CurAddr++;                              // next MSR pair
  }

  if (CurLimit < *LimitPtr) {
    // Announce failure
    *LimitPtr = CurLimit;
    IDS_ERROR_TRAP;
  }

  while ((CurAddr >= 0x200) && (CurAddr <= 0x20F)) {
    // Check if this vMTRR caches SPI ROM, skip it if yes
    if ((CurAddr % 2) == 0) {
      LocalMsrRegister = AsmReadMsr64 (CurAddr);
      if ((LocalMsrRegister & 0xFFFFFFFFFFFFFFF8ull) >= 0xFF000000) {
        CurAddr += 2;
        continue;
      }
    }

    LocalMsrRegister = 0;
    AsmWriteMsr64 (CurAddr, LocalMsrRegister);
    CurAddr++;
  }

  return AGESA_SUCCESS;
}

/*++

Routine Description:

  Zen - Zeppelin Microcode Patch loading

Arguments:
  AMD_CONFIG_PARAMS *

Returns:

--*/
VOID
CcxZenZpCacheInit (
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT32        Cache32bTOP;
  UINT64        LocalMsrRegister;
  AGESA_STATUS  Status;

  LocalMsrRegister = AsmReadMsr64 (0xC001001A);

  Cache32bTOP = (UINT32) (RShiftU64 (LocalMsrRegister, 16) & 0xFFFFFFFF);

  //
  //======================================================================
  // Set default values for CPU registers
  //======================================================================
  //
  AsmMsrOr64 (0xC0010010, BIT19);

  LocalMsrRegister = 0x1E1E1E1E1E1E1E1Eull;
  AsmWriteMsr64 (0x250, LocalMsrRegister);      // 0 - 512K = WB Mem
  LocalMsrRegister = 0x1E1E1E1E1E1E1E1Eull;
  AsmWriteMsr64 (0x258, LocalMsrRegister);      // 512K - 640K = WB Mem

  //
  //======================================================================
  // Set variable MTRR values
  //======================================================================
  //
  Status = SetVariableMTRRs (0, &Cache32bTOP, 0x200, 6, StdHeader);

  AsmMsrOr64 (0xC0010010, (BIT18 | BIT20));

  LocalMsrRegister = AsmReadMsr64 (0xC0010010);
  if ((LocalMsrRegister & BIT21) != 0) {
    LocalMsrRegister |= BIT22;
  }

  LocalMsrRegister &= ~BIT19;
  AsmWriteMsr64 (0xC0010010, LocalMsrRegister);
}

