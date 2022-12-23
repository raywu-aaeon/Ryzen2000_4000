/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 SMI Dispatcher Driver Example
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/******************************************************************************
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

#ifndef _FCH_SMM_DISPATCHER_H_
#define _FCH_SMM_DISPATCHER_H_

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/S3BootScriptLib.h>

#include <Protocol/SmmCpu.h>
#include <Protocol/FchSmmSxDispatch2.h>
#include <Protocol/FchSmmSwDispatch2.h>
#include <Protocol/FchSmmPwrBtnDispatch2.h>
#include <Protocol/FchSmmPeriodicalDispatch2.h>
#include <Protocol/FchSmmIoTrapDispatch2.h>
#include <Protocol/FchSmmGpiDispatch2.h>
#include <Protocol/FchSmmUsbDispatch2.h>

#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>


#include "FchSmmSxDispatcher.h"
#include "FchSmmSwDispatcher.h"
#include "FchSmmPwrBtnDispatcher.h"
#include "FchSmmIoTrapDispatcher.h"
#include "FchSmmPeriodicalDispatcher.h"
#include "FchSmmGpiDispatcher.h"
#include "FchSmmUsbDispatcher.h"
#include "FchSmmMiscDispatcher.h"

#include "FchPlatform.h"
#pragma pack (8)

#define Slp_Type    BIT1
#define SmiCmdPort  BIT11
#define UsbSmi      BIT21
#define PwrBtn      BIT19
#define Eos         BIT28
#define IoTrapping0 BIT20
#define IoTrapping1 BIT21
#define IoTrapping2 BIT22
#define IoTrapping3 BIT23
#define ShortTimer  BIT14
#define LongTimer   BIT15
#define Gpe         0xfffffffful
#define Smbus0      BIT15
#define AllGevents  0xfffffffful
#define FchGppSerr0 BIT21
#define FchGppSerr1 BIT22
#define FchGppSerr2 BIT23
#define FchGppSerr3 BIT24
#define FchFakeSts0 BIT1

typedef EFI_STATUS (EFIAPI *AMD_SM_SMM_CHILD_DISPATCHER_HANDLER) (
  IN      EFI_HANDLE     SmmImageHandle,
  IN OUT  VOID           *CommunicationBuffer OPTIONAL,
  IN OUT  UINTN          *SourceSize OPTIONAL
  );


///
/// AMD FCH SMM Dispatcher Structure
///
typedef struct {
  UINT32                                SmiStatusReg;   ///< Status Register
  UINT32                                SmiStatusBit;   ///< Status Bit
} FCH_SMM_COMMUNICATION_BUFFER;

///
/// AMD FCH SMM Dispatcher Structure
///
typedef struct {
  UINT32                                StatusReg;      ///< Status Register
  UINT32                                SmiStatusBit;   ///< Status Bit
  AMD_SM_SMM_CHILD_DISPATCHER_HANDLER   SmiDispatcher;  ///< Dispatcher Address
} FCH_SMM_DISPATCHER_TABLE;

///
/// AMD FCH SMM Dispatcher Structure
///
typedef struct {
  UINT16             ioPort;                            ///< I/O port
  EFI_SMM_IO_WIDTH   ioWidth;                           ///< I/O width
  UINT32             ioValue;                           ///< I/O value
} SAVE_B2B_IO;

///
/// AMD Save/Restore Structure for SMM
///
typedef struct {
  UINT8              Bus;                               ///< PCI Bus
  UINT8              Dev;                               ///< PCI Device
  UINT8              Func;                              ///< PCI Function
  UINT16             Offset;                            ///< Offset registers
  EFI_SMM_IO_WIDTH   DataWidth;                         ///< Data width
  UINT32             DataValue;                         ///< Data value
} SAVE_PCI;

#endif

