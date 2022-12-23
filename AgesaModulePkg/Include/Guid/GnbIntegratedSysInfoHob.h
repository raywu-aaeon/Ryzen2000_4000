/* $NoKeywords:$ */
/**
 * @file
 *
 * Gnb Frame Buffer Data Hob GUID definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Gnb
 * @e \$Revision: 309090 $   @e \$Date: 2017-11-13 04:30:05 +0800 (Mon, 13 Nov 2017) $
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
 **/
#ifndef _GNB_INTEGRATED_SYSINFO_HOB_H_
#define _GNB_INTEGRATED_SYSINFO_HOB_H_

#define _GNB_INTEGRATED_SYSINFO_HOB_GUID \
{ \
  0x0664BCCF, 0x0A93, 0x407C, 0xA5, 0x8B, 0x2A, 0x56, 0xE4, 0x88, 0x6A, 0x24 \
}
extern EFI_GUID gGnbIntegratedSysInfoHobGuid;

#include <NbioGfx.h>

#pragma pack (push, 1)

/// Memory descriptor structure for each memory rang
typedef struct {
  UINT64  Base;                             ///< Base address of memory rang
  UINT64  Size;                             ///< Size of memory rang
} NBIO_UMA_DESCRIPTOR;

/// Frame Buffer Data HOB data
typedef struct _NBIO_Frame_Buffer_DATA_HOB {
  EFI_HOB_GUID_TYPE              EfiHobGuidType;                             ///< GUID Hob type structure
  ATOM_FUSION_SYSTEM_INFO_V9     AtomFusionSystemInfoV9;                      ///< Platform Config Structure
  NBIO_UMA_DESCRIPTOR            UMAInfo;
} NBIO_Frame_Buffer_DATA_HOB;

#pragma pack (pop)

#endif

