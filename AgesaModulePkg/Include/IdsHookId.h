/* $NoKeywords:$ */
/**
 * @file
 *
 * IdsHookId.h
 *
 * Contains HOOKID definition
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project: (Proc/Ids/Internal)
 * @e \$Revision: 328983 $   @e \$Date: 2015-10-14 20:56:31 +0800 (Wed, 14 Oct 2015) $
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

#ifndef _IDS_HOOKID_H_
#define _IDS_HOOKID_H_

typedef UINT32 HOOK_ID;
// 0x00000001 - 0x10000000 for CCX
#define IDS_HOOK_CCX_BEFORE_AP_LAUNCH   0x00000001ul
#define IDS_HOOK_CCX_AFTER_AP_LAUNCH    0x00000002ul
#define IDS_HOOK_CCX_AFTER_PWR_MNG      0x00000003ul
#define IDS_HOOK_CCX_SKIP_UCODE_PATCH   0x00000004ul
#define IDS_HOOK_CCX_SMM                0x00000005ul
#define IDS_HOOK_CCX_SKIP_SMEE          0x00000006ul
#define IDS_HOOK_CCX_PEI                0x00000007ul
#define IDS_HOOK_CCX_CUSTOM_PSTATES     0x00000011ul
#define IDS_HOOK_CCX_SKIP_SMM_LOCK      0x00000012ul
#define IDS_HOOK_CCX_CORE_DIS_MASK      0x00000013ul
#define IDS_HOOK_CCX_READY_TO_BOOT      0x00000014ul
#define IDS_HOOK_C2_LATENCY             0x00000015ul
#define IDS_HOOK_C3_LATENCY             0x00000016ul
#define IDS_HOOK_C1_LATENCY             0x00000017ul

// 0x20000001 - 0x30000000 for DF
#define IDS_HOOK_DF_AFTER_AP_LAUNCH     0x20000001ul
#define IDS_HOOK_DF_DXE_INIT            0x20000002ul
#define IDS_HOOK_DF_RAS_INIT            0x20000003ul
#define IDS_HOOK_DF_RAS_INIT2           0x20000004ul
#define IDS_HOOK_DF_CLK_GATING          0x20000005ul
#define IDS_HOOK_PIE_PWR_MGMT_INIT      0x20000006ul
#define IDS_HOOK_PIE_PWR_MGMT_INIT2     0x20000007ul
#define IDS_HOOK_PIE_PWR_MGMT_INIT3     0x20000008ul
#define IDS_HOOK_PIE_REDIRECT_SCRUB_CTRL_INIT 0x20000009ul
#define IDS_HOOK_PIE_DRAM_SCRUB_TIME_INIT     0x2000000Aul
#define IDS_HOOK_FABRIC_PEI_INIT_END    0x2000000Bul
#define IDS_HOOK_DF_CS_INIT1            0x2000000Cul
#define IDS_HOOK_DF_CS_INIT2            0x2000000Dul

// 0x30000001 - 0x40000000 for PSP
#define IDS_HOOK_PSP_MEM_RESTORE_ENABLED      0x30000001ul

//Special HOOK ID reserved for get IDS NV table

#define IDS_HOOK_BEFORE_MEM_INIT        0x60000001ul

// 0xB0000000 - 0xCFFFFFFF for NBIO
#define IDS_HOOK_NBIO_INIT_EARLY        0xB0000001ul
#define IDS_HOOK_NBIO_INIT_ENV          0xB0000002ul
#define IDS_HOOK_NBIO_BASE_INIT         0xB0000003ul
#define IDS_HOOK_NBIO_LOAD_BUILD_OPTION 0xB0000004ul
#define IDS_HOOK_NBIO_SMUV9_INIT        0xB0000005ul
#define IDS_HOOK_NBIO_DEVICE_REMAP      0xB0000006ul
#define IDS_HOOK_NBIO_PCIE_TOPOLOGY     0xB0000007ul
#define IDS_HOOK_NBIO_PCIE_USER_CONFIG  0xB0000008ul
#define IDS_HOOK_NBIO_PCIE_AER_INIT     0xB0000009ul
#define IDS_HOOK_NBIO_SMUV10_INIT       0xB000000Aul
#define IDS_HOOK_NBIO_SMUV9_INIT_CMN    0xB000000Bul
#define IDS_HOOK_NBIO_GFX_INIT_CONFIG   0xB000000Cul
#define IDS_HOOK_NBIO_GFX_INIT_FRAME_BUFFER 0xB000000Dul
#define IDS_HOOK_NBIO_GFX_VGA_REGISTER_CONFIG 0xB000000Eul
#define IDS_HOOK_NBIO_PSPP_TUNING       0xB000000Ful
#define IDS_HOOK_NBIO_AFTER_CCX         0xB0000010ul
#define IDS_HOOK_NBIO_SMUV10_INIT_CMN   0xB0000011ul
#define IDS_HOOK_NBIO_SMU_INIT          0xB0000012ul
#define IDS_HOOK_NBIO_PCIE_TUNING       0xB0000013ul

// 0xD0000000 - 0xDFFFFFFF for FCH
#define IDS_HOOK_FCH_INIT_RESET         0xD0000001ul
#define IDS_HOOK_FCH_INIT_ENV           0xD0000002ul

// Common
#define IDS_HOOK_BEGINNING_OF_AGESA     0xE0000000ul

#define IDS_HOOK_GET_NV_TABLE           0xFFFFFFFEul
#endif // _IDS_HOOKID_H_

