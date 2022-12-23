/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP common service PPI prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#ifndef _AMD_PSP_COMMONSERVICE_PPI_H_
#define _AMD_PSP_COMMONSERVICE_PPI_H_

#include <AmdPspDirectory.h>

///Function used to get Ftpm control area address
typedef
BOOLEAN
(*FP_GET_FTPM_CONTROLAREA) (
  IN OUT   VOID **FtpmControlArea
  );

///Function used to turn on/restore PSP MMIO decode
typedef
VOID
(*FP_SWITCH_PSP_MMIO_DECODE) (
  IN       BOOLEAN SwitchFlag,
  IN OUT   UINT32 *RegisterCopy
  );

///Function used to check PSP Device present by checking fuse receipt copy
typedef
BOOLEAN
(*FP_CHECK_PSP_DEVICE_PRESENT) (
  VOID
  );

///Function used to check Ftpm support
typedef
EFI_STATUS
(*FP_CHECK_FTPM_CAPS) (
  UINT32 *Caps
  );

typedef
BOOLEAN
(*FP_PSPENTRYINFO) (
  IN      UINT32                       EntryType,
  IN OUT  UINT64                      *EntryAddress,
  IN      UINT32                      *EntrySize
  );

typedef
BOOLEAN
(* FP_CONDITIONER) (
  IN       VOID        *Context
  );

typedef
BOOLEAN
(*FP_PSP_LIB_TIMEOUT) (
  IN       UINT64              uSec,
  IN       FP_CONDITIONER      Conditioner,
  IN       VOID                *Context
  );

typedef
VOID
(*FP_ACQUIRE_PSPSMIREGMUTEX) (
  VOID
  );

typedef
VOID
(*FP_RELEASE_PSPSMIREGMUTEX) (
  VOID
  );

typedef
EFI_STATUS
(*FP_CHECK_PSP_CAPS) (
  IN OUT   UINT32 *PspCaps
  );
///
/// PPI prototype
///
/// Defines AMD_PSP_COMMON_SERVICE_PPI, which public the common PSP service across all programs
///
typedef struct _AMD_PSP_COMMON_SERVICE_PPI {
  FP_GET_FTPM_CONTROLAREA       GetFtpmControlArea;     ///< Get FTPM control Area
  FP_SWITCH_PSP_MMIO_DECODE     SwitchPspMmioDecode;     ///< Turn on/off Psp MMIO
  FP_CHECK_PSP_DEVICE_PRESENT   CheckPspDevicePresent;     ///< Check if PSP Device Present
  FP_CHECK_FTPM_CAPS            CheckFtpmCaps;     ///< Check if Ftpm supported
  FP_PSPENTRYINFO               PSPEntryInfo;           ///< Get specific PSP Entry information
  FP_PSP_LIB_TIMEOUT            PspLibTimeOut;     ///< Delay function
  FP_ACQUIRE_PSPSMIREGMUTEX     AcquirePspSmiRegMutex;  ///< Acquire Psp SmiReg Mutex
  FP_RELEASE_PSPSMIREGMUTEX     ReleasePspSmiRegMutex;  ///< Release Psp SmiReg Mutex
  FP_CHECK_PSP_CAPS             CheckPspCaps;     ///< Check PSP caps
} AMD_PSP_COMMON_SERVICE_PPI;

extern EFI_GUID gAmdPspCommonServicePpiGuid;

#endif //_AMD_PSP_COMMONSERVICE_PPI_H_

