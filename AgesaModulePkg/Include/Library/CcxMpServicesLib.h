/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX MP Services Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 312770 $   @e \$Date: 2015-02-11 13:24:42 +0800 (Wed, 11 Feb 2015) $
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
 **/

#ifndef _CCX_MP_SERVICES_LIB_H_
#define _CCX_MP_SERVICES_LIB_H_
#include "Library/IdsLib.h"
#include <Protocol/MpService.h>
#pragma pack (push, 1)

/// Core Selector
typedef enum {
  ALL_THREADS,                    ///< Run function on all threads
  ALL_CORE_PRIMARY,               ///< Run function on all core primary (thread 0 of every core)
  ALL_COMPLEX_PRIMARY,            ///< Run function on all complex primary (logical core 0 of every complex)
  ALL_CCD_PRIMARY,                ///< Run function on all CCD primary (logical core 0 of every CCD)
  ALL_DIE_PRIMARY,                ///< Run function on all DIE primary (logical core 0 of every DIE)
  ALL_SOCKET_PRIMARY,             ///< Run function on all socket primary (logical core 0 of every socket)
} CCX_MP_SERVICES_CORE_SELECTOR;

/// Blocking Mode
typedef enum {
  BLOCKING_MODE,                  ///< execute in blocking mode. BSP waits until this AP finishes
  NON_BLOCKING_MODE,              ///< execute in non-blocking mode. BPS won't wait for AP
} CCX_MP_SERVICES_BLOCKING_MODE;

/*---------------------------------------------------------------------------------------*/
/**
 * Run function on selected APs
 *
 *
 * @param[in]  CoreSelector       core selector
 * @param[in]  RunThisFunction    function
 * @param[in]  Argument           argument
 * @param[in]  BlockingMode       BLOCKING_MODE     - execute in blocking mode. BSP waits until this AP finishes
 *                                NON_BLOCKING_MODE - execute in non-blocking mode. BPS won't wait for AP
 *                                WARNING: LIB instance for SMM won't support NonBlockingMode
 *
 */
EFI_STATUS
CcxRunFunctionOnAps (
  IN       CCX_MP_SERVICES_CORE_SELECTOR  CoreSelector,
  IN       EFI_AP_PROCEDURE               RunThisFunction,
  IN       VOID                          *Argument,
  IN       CCX_MP_SERVICES_BLOCKING_MODE  BlockingMode
  );

#pragma pack (pop)
#endif // _CCX_MP_SERVICES_LIB_H_

