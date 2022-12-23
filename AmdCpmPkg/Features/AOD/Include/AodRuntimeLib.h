/*****************************************************************************
 *
 * Copyright 2017 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */


#ifndef _AMD_AOD_RUNTIME_LIB_H_
#define _AMD_AOD_RUNTIME_LIB_H_

#include <Uefi.h>
#include <Features/AOD/Aod.h>
#include <Features/AOD/Include/SmbusLightSmm.h>

VOID
AodSmnRead (
  IN       UINT8               DieBusNum,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  );

VOID
AodSmnWrite (
  IN       UINT8               DieBusNum,
  IN       UINT32              SmnAddress,
  IN       UINT32              *Value
  );

BOOLEAN
VerifyAcpiSmiTransferBuffer (
  AodNvAreaStruct *AodNvAreaPtr
  );

VOID
FinalizeTransferBuffer (
  AodNvAreaStruct *AodNvAreaPtr,
  EFI_STATUS  Status
  );

EFI_STATUS
GetMemFreqIndexByClk (
  UINT16    MemFreqClk,
  UINT8     *FreqIndex
  );

EFI_STATUS
GetMemFreqClkByIndex (
  UINT8       FreqIndex,
  UINT16     *MemFreqClk
  );


EFI_STATUS
EnableSmMasterDecode (
  );

EFI_STATUS
DisableSmMasterDecode (
  );

EFI_STATUS
InitSmbusData (
  );

EFI_STATUS
EFIAPI
SmbusExecute (
  IN       UINT8                              SmbusSelect,
  IN       EFI_SMBUS_DEVICE_ADDRESS           SlaveAddress,
  IN       EFI_SMBUS_DEVICE_COMMAND           Command,
  IN       EFI_SMBUS_OPERATION                Operation,
  IN       BOOLEAN                            PecCheck,
  IN OUT   UINTN                              *Length,
  IN OUT   VOID                               *Buffer
  );

UINT8
HammingWeight (
  IN UINT32 Value
  );


#endif
