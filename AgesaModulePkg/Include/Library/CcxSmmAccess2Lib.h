/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains implementation for the SMM Access2 Protocol
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision:  $   @e \$Date: $
 *
 */
/*
 ******************************************************************************
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

#ifndef _CCX_SMM_ACCESS2_LIB_H_
#define _CCX_SMM_ACCESS2_LIB_H_

#include <Protocol/SmmAccess2.h>

#define  SMMADDR_ADDRESS      0xC0010112ul
#define  SMMMASK_ADDRESS      0xC0010113ul
#define      SMMLOCK          0x0000000000000001ull
#define  FCH_MMIO_ADDRESS     0xFED80000ull
#define  SMI_REGISTER_SPACE   0x00000200ull
#define  SMI_TRIG0_OFFSET     0x00000098ull
#define      SMIENB           0x80000000ul

///  Struct for Tseg configuration
typedef struct {
  IN      UINT64 TsegBase;  ///< TsegBase
  IN      UINT64 TsegMask;  ///< TsegMask
} CCX_SMM_TSEG_CONFIG;


EFI_STATUS
EFIAPI
CcxSmmOpen2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  );

EFI_STATUS
EFIAPI
CcxSmmClose2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  );

EFI_STATUS
EFIAPI
CcxSmmLock2 (
  IN       EFI_SMM_ACCESS2_PROTOCOL *This
  );

EFI_STATUS
EFIAPI
CcxSmmGetCapabilities2 (
  IN CONST EFI_SMM_ACCESS2_PROTOCOL *This,
  IN OUT   UINTN                    *SmramMapSize,
  IN OUT   EFI_SMRAM_DESCRIPTOR     *SmramMap
  );

EFI_STATUS
EFIAPI
CcxSmmAccess2ProtocolInstall (
);

#endif
