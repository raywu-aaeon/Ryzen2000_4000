/**
 * @file
 *
 * AMD Integrated Debug Hook Routines
 *
 * Contains all functions related to IDS Hook
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
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
#ifndef _AMD_IDS_HOOK_EXTLIB_H_
#define _AMD_IDS_HOOK_EXTLIB_H_

#include <IdsHookId.h>

///
/// The return status for all IDS HOOK services.
///
typedef enum {
  IDS_HOOK_SUCCESS = 0,       ///< The service completed normally
  IDS_HOOK_UNSUPPORTED,       ///< Unsupported IDS HOOK
  IDS_HOOK_BUFFER_TOO_SMALL,  ///< Too small buffer
  IDS_HOOK_NOT_FOUND,         ///< Haven't found accordingly service entry for specific IDS HOOK ID
  IDS_HOOK_ERROR,             ///< Error happens during service IDS HOOK
  IDS_HOOK_SKIP,              ///< Use to notify the IDS HOOK caller to skip a block of codes, used for IDS_HOOK_SKIP
  IDS_HOOK_NO_SKIP,           ///< Use to notify the IDS HOOK caller not skip a block of codes, used for IDS_HOOK_SKIP
  IDS_HOOK_MAX                ///< Not a status, for limit checking.
} IDS_HOOK_STATUS;
/**
 * Entry function of IDS Ext HOOK
 *
 *
 * @param[in] HookId            ID used to identify the IDS HOOK
 * @param[in,out] Handle        Optional, Used to transfer variable information except the Data.
 *                              e.g. It can set with the service table pointer. Or
 *                              It can set with the global data structure
 * @param[in,out] Data          Point to the data used in the Hook
 *
 * @retval    IDS_HOOK_SUCCESS     Hook execute success
 * @retval    other value          refer to IDS_HOOK_STATUS
 *
 */
IDS_HOOK_STATUS
IdsHookExtEntry (
  HOOK_ID HookId,
  VOID *Handle,
  VOID *Data
  );

/**
 * Get IDS NV Table
 *
 * IDS NV table is a data filled multiple IDS_NV_RECORD structure
 *
 * @param[in,out] IdsNvTable        Data pointer used to filled with multiple IDS_NV_RECORD structure
 *                              The memory space need be pre-allocated before call this routine
 *
 * @param[in,out] IdsNvTableSize   Size of IdsNvTable, if size is less than IdsNvTable occupied, it will
 *                                 filled with the required data size on ouput.
 *                                 On input, the size in bytes allocated for the return IdsNvTable.
 *                                 On output, the size of data returned in IdsNvTable.
 *
 * @retval    IDS_HOOK_SUCCESS     Get IDS NV Table successfully
 * @retval    IDS_HOOK_BUFFER_TOO_SMALL       Buffer too small to hold IdsNvTable
 * @retval    Other                Other error happens during get IDS NV Table
 *
 */
IDS_HOOK_STATUS
GetIdsNvTable (
  IN OUT   VOID *IdsNvTable,
  IN OUT   UINT32 *IdsNvTableSize
  );

#endif //#define _AMD_IDS_HOOK_EXTLIB_H_

