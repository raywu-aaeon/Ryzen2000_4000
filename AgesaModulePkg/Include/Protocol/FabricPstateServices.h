/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Pstate Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
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

#ifndef _FABRIC_PSTATE_SERVICES_PROTOCOL_H_
#define _FABRIC_PSTATE_SERVICES_PROTOCOL_H_

///
/// Forward declaration for the AMD_FABRIC_PSTATE_SERVICES_PROTOCOL.
///
typedef struct _AMD_FABRIC_PSTATE_SERVICES_PROTOCOL AMD_FABRIC_PSTATE_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_FABRIC_PSTATE_SERVICES_GET_SYSTEM_INFO) (
  IN       AMD_FABRIC_PSTATE_SERVICES_PROTOCOL   *This,
     OUT   BOOLEAN                               *AreAllSocketPstatesInTheSameDomain
  );

typedef
EFI_STATUS
(EFIAPI *AMD_FABRIC_PSTATE_SERVICES_GET_SOCKET_INFO) (
  IN       AMD_FABRIC_PSTATE_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
     OUT   BOOLEAN                               *AreAllDiePstatesInTheSameDomain
  );

typedef
EFI_STATUS
(EFIAPI *AMD_FABRIC_PSTATE_SERVICES_GET_DIE_INFO) (
  IN       AMD_FABRIC_PSTATE_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
  IN       UINTN                                 Die,
     OUT   BOOLEAN                               *IsSwitchingEnabled,
     OUT   UINTN                                 *TotalNumberOfStates
  );

typedef
EFI_STATUS
(EFIAPI *AMD_FABRIC_PSTATE_SERVICES_GET_PSTATE_INFO) (
  IN       AMD_FABRIC_PSTATE_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
  IN       UINTN                                 Die,
  IN       UINTN                                 Pstate,
     OUT   UINTN                                 *Frequency,
     OUT   UINTN                                 *Voltage,
     OUT   UINTN                                 *Power,
     OUT   UINTN                                 *AssociatedMstate
  );

typedef
EFI_STATUS
(EFIAPI *AMD_FABRIC_PSTATE_SERVICES_GET_CURRENT_PSTATE) (
  IN       AMD_FABRIC_PSTATE_SERVICES_PROTOCOL   *This,
  IN       UINTN                                 Socket,
  IN       UINTN                                 Die,
     OUT   UINTN                                 *Pstate
  );

///
/// When installed, the Fabric P-state Services Protocol produces a collection of
/// services that return various information about the fabric P-states.
///
struct _AMD_FABRIC_PSTATE_SERVICES_PROTOCOL {
  AMD_FABRIC_PSTATE_SERVICES_GET_SYSTEM_INFO      GetSystemInfo;
  AMD_FABRIC_PSTATE_SERVICES_GET_SOCKET_INFO      GetSocketInfo;
  AMD_FABRIC_PSTATE_SERVICES_GET_DIE_INFO         GetDieInfo;
  AMD_FABRIC_PSTATE_SERVICES_GET_PSTATE_INFO      GetPstateInfo;
  AMD_FABRIC_PSTATE_SERVICES_GET_CURRENT_PSTATE   GetCurrentPstate;
};

extern EFI_GUID gAmdFabricPstateServicesProtocolGuid;

#endif

