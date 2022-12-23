/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD PSP KVM service Protocol definition
 *
 * Contains code to declare AMD PSP KVM service Protocol
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/****************************************************************************
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

#ifndef _AMD_PSP_KVM_SERVICE_PROTOCOL_H_
#define _AMD_PSP_KVM_SERVICE_PROTOCOL_H_

#include <Protocol/GraphicsOutput.h>
#include <IndustryStandard/SmBios.h>
#include <Protocol/Smbios.h>
//
// GUID definition
//
extern EFI_GUID gAmdPspKvmServiceProtocolGuid;

typedef struct _AMD_PSP_KVM_SERVICE_PROTOCOL AMD_PSP_KVM_SERVICE_PROTOCOL;

typedef struct _KVM_IP_INFO {
  UINT32 NetworkType;              // 0 - dynamic, 1 - static. Default should be dynamic.
  UINT8  Ipv4Addr[20];                // Null terminated ascii string indicating the static IPV4 address. ex: 192.168.0.10
  UINT8  Ipv4SubMask[20];        // Null terminated ascii string indicating the Subnet Mask. ex: 255.255.255.0
  UINT8  Ipv4DefGateway[20];  // Null terminated ascii string indicating the Default Gateway. ex:  192.168.0.1
}KVM_IP_INFO;

typedef union {
  struct {
    UINT8  KvmEnabled:1;           ///< [0] 0b: Disabled, 1b: Enabled 
    UINT8  Protocol:3;             ///< [3:1] 001b: Other Protocol, 010b: Raw, 011b: RDP, 100b: VNC
    UINT8  Connectivity:2;         ///< [5:4] 10b: Exclusive Connectivity, 11b: Shared Connectivity
    UINT8  ConcurrentCount:2;      ///< [7:6] 01b: Singular KVM Redirection, 10b: Two Concurrent KVM session possible, 11b: Three Concurrent KVM session possible
  } Field;
  UINT8 Value;
} KVM_SMBIOS_KVM_INFORMATION;

typedef struct {
  SMBIOS_STRUCTURE              Hdr;
  KVM_SMBIOS_KVM_INFORMATION    KvmInformation;
} SMBIOS_TABLE_TYPEA0;

#define KVM_SMBIOS_TYPE_KVM_INFORMATION    0xA0
#define KVM_SMBIOS_KVM_DISABLED            0x0
#define KVM_SMBIOS_KVM_ENABLED             0x1
#define KVM_SMBIOS_PROTOCOL_OTHER          0x1
#define KVM_SMBIOS_PROTOCOL_RAW            0x2
#define KVM_SMBIOS_PROTOCOL_RDP            0x3
#define KVM_SMBIOS_PROTOCOL_VNC            0x4
#define KVM_SMBIOS_CONNECTIVITY_EXCLUSIVE  0x2
#define KVM_SMBIOS_CONNECTIVITY_SHARED     0x3
#define KVM_SMBIOS_CONCURRENTCOUNT_SINGLE  0x1
#define KVM_SMBIOS_CONCURRENTCOUNT_TWO     0x2
#define KVM_SMBIOS_CONCURRENTCOUNT_THREE   0x3


#define KVM_NOT_REQUESTED 0x00000000ul
#define KVM_REQUESTED 0x00000001ul

///Get value of KvmRequest
typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_GET_REQUEST) (
  IN     UINT32                *KvmRequest
  );

///Set value of KvmRequest
typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_SET_REQUEST) (
  IN     UINT32                *KvmRequest
  );

///Get value of KvmSessionProgress
typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_GET_SESSION_PROGRESS) (
  IN     UINT32                *KvmSessionProgress
  );

///Set value of KvmSessionProgress
typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_SET_SESSION_PROGRESS) (
  IN     UINT32                *KvmSessionProgress
  );

///Init KVM
typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_INITIATE_KVM) (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *ModeInfo,
  IN KVM_IP_INFO                       *KvmIpInfo
  );

typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_TERMINATE_KVM) (
  VOID
  );

typedef
EFI_STATUS
(EFIAPI *AMD_PSP_KVM_PROTOCOL_RETRIEVE_SMBIOS_TABLE) (
  IN    UINT8                   KvmEnabled,
  OUT   SMBIOS_TABLE_TYPEA0   **SmbiosTableTypeA0
  );

/// Defines AMD_PSP_KVM_SERVICE_PROTOCOL. This protocol is used for provide all generic service related to AMD KVM

typedef struct _AMD_PSP_KVM_SERVICE_PROTOCOL {
  UINT32                                      Version;
  AMD_PSP_KVM_PROTOCOL_GET_REQUEST            GetRequest;
  AMD_PSP_KVM_PROTOCOL_SET_REQUEST            SetRequest;
  AMD_PSP_KVM_PROTOCOL_GET_SESSION_PROGRESS   GetSessionProgress;
  AMD_PSP_KVM_PROTOCOL_SET_SESSION_PROGRESS   SetSessionProgress;
  AMD_PSP_KVM_PROTOCOL_INITIATE_KVM           InitiateKvm;
  AMD_PSP_KVM_PROTOCOL_TERMINATE_KVM          TerminateKvm;
  AMD_PSP_KVM_PROTOCOL_RETRIEVE_SMBIOS_TABLE  RetrieveSmbiosTable;
} AMD_PSP_KVM_SERVICE_PROTOCOL;

#endif //_AMD_PSP_KVM_SERVICE_PROTOCOL_H_
