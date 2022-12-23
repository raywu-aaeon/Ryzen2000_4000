/* $NoKeywords:$ */
/**
 * @file
 *
 * PspP2Cmbox Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspP2Cmbox Driver
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

#ifndef _PSP_P2C_MBOX_H_
#define _PSP_P2C_MBOX_H_

#include <Base.h>
#include <Pi/PiFirmwareVolume.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/FchSmmSwDispatch2.h>
#include <Protocol/FchSmmMiscDispatch.h>

#include <Library/AmdPspFlashAccLib.h>

#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Protocol/PspMboxSmmBufferAddressProtocol.h>

#define EFI_LBA_LIST_TERMINATOR   0xFFFFFFFFFFFFFFFFULL


P2C_MBOX_STATUS
EFIAPI
ProcessPspCommand (
  IN UINT64                 Cmd,
  IN MBOX_DEFAULT_BUFFER   *MboxBuffer
);

EFI_STATUS
PspFlashAccSmmCommunicateHandler (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context,
  IN OUT VOID    *CommBuffer,
  IN OUT UINTN   *CommBufferSize
  );
/// SMI command target NV region
typedef enum {
  SMI_TARGET_NVRAM = 0,           ///< PSP NVRAM
  SMI_TARGET_TOKEN_UNLOCK = 1,            ///< PSP token unlock data
  SMI_TARGET_VM_GUARD = 2,            ///< VM Guard data region
  SMI_TARGET_COREMCE_DATA = 3,   ///< core machine check exception
  SMI_TARGET_TEE_WONE_NVRAM = 4,   ///< TEE_WONE_NVRAM data
  SMI_TARGET_PSP_NVRAM = 5,      ///< PSP NVRAM for RPMC
  SMI_TARGET_NO_USE = 0xFE,           ///< Not used
  SMI_TARGET_END = 0xFF,            ///< End flag
} SMI_TARGET_ID;

/// Directory type
typedef enum {
  DIR_TYPE_PSP = 0,               ///< PSP Directory
  DIR_TYPE_BIOS = 1,                ///< BIOS Directory
  DIR_TYPE_END = 0xFF,                ///< End flag
} DIR_TYPE;

///< Structure describe PSP NV Region
typedef struct _PSP_NV_DESCRIPTOR {
  UINT32           TargetID;            ///< Target NV ID, defined in SMI_TARGET_ID
  DIR_TYPE         Directory;           ///< Directory Type, defined in DIR_TYPE
  UINT8            DirEntryID;            ///< Entry ID
  BOOLEAN          Detected;            ///< Flag to present if entry detected
  UINT64           NvRegionBase;            ///< Region base
  UINT32           NvRegionSize;            ///< Region Size
} PSP_NV_DESCRIPTOR;
#endif  //_PSP_P2C_MBOX_H_

