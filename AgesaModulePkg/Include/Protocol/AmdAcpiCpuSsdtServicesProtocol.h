/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX base Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 */
/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#ifndef _AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL_H_
#define _AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL_H_
#pragma pack (push, 1)

#define MAX_CORE_NUMBER_PER_SOCKET 64

/// P-state structure for each state
typedef struct {
  IN OUT   UINT32               PStateEnable;                ///< Pstate enable
  IN OUT   UINT32               CoreFreq;                    ///< MHz
  IN OUT   UINT32               Power;                       ///< milliWatts
  IN OUT   UINT32               SwPstateNumber;              ///< Software P-state number
} S_PSTATE_VALUES;

/// P-state structure for socket
typedef struct {
  IN OUT   UINT8                SocketNumber;                ///< Physical socket number of this socket
  IN OUT   UINT8                TotalLogicalCores;           ///< Logical core number in this socket
  IN OUT   BOOLEAN              CreateAcpiTables;            ///< Create table flag
  IN OUT   UINT8                LocalApicId[MAX_CORE_NUMBER_PER_SOCKET]; ///< Local Apic Id
  IN OUT   UINT8                PStateMaxValue;              ///< Max p-state number in this core
  IN OUT   UINT32               TransitionLatency;           ///< Transition latency
  IN OUT   BOOLEAN              IsPsdDependent;              ///< Dependent or Independent PSD
  IN OUT   S_PSTATE_VALUES      PStateStruct[1];             ///< P state structure
} AMD_PSTATE_SOCKET_INFO;

/// P-state structure for whole system
typedef struct {
  IN OUT   UINT8                TotalSocketInSystem;         ///< Total node number in system
  IN OUT   UINT32               SizeOfBytes;                 ///< Structure size
  IN OUT   AMD_PSTATE_SOCKET_INFO PStateSocketStruct[1];     ///< P state structure for socket
} AMD_PSTATE_SYS_INFO;


/// C-state structure
typedef struct {
  IN OUT   BOOLEAN              IsCstateEnabled;         ///< Is Cstate enabled
  IN OUT   UINT32               IoCstateAddr;            ///< Io Cstate address
  IN OUT   BOOLEAN              IsCsdGenerated;          ///< Is _CSD needed
  IN OUT   BOOLEAN              IsMonitorMwaitSupported; ///< Should C1 FFH be declared
  IN OUT   UINT16               C1Latency;               ///< C1 Latency
  IN OUT   UINT16               C2Latency;               ///< C2 Latency
  IN OUT   UINT16               C3Latency;               ///< C3 Latency. A non-zero value results in C3 declaration.
} AMD_CSTATE_INFO;

///
/// Forward declaration for the AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL.
///
typedef struct _AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_SSDT_SERVICES_GET_PSTATE_INFO) (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_PSTATE_SYS_INFO                   **PstateSysInfoPtr
  );

typedef
EFI_STATUS
(EFIAPI *AMD_SSDT_SERVICES_GET_CSTATE_INFO) (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
     OUT   AMD_CSTATE_INFO                       **CstateInfo
  );

typedef
UINT32
(EFIAPI *AMD_SSDT_SERVICES_GET_PSD_DOMAIN_FOR_INDEP) (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       UINT8                                   LocalApicId
  );

typedef
EFI_STATUS
(EFIAPI *AMD_SSDT_SERVICES_GET_PSTATE_POWER) (
  IN       AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL    *This,
  IN       CCX_PSTATE                             Pstate,
     OUT   UINTN                                  *PowerInmW
  );

///
/// ACPI Processor SSDT services protocol
///
struct _AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL {
  UINTN                                            Revision;               ///< Revision Number
  AMD_SSDT_SERVICES_GET_PSTATE_INFO                GetPstateInfo;          ///< Get Pstate information for whole system
  AMD_SSDT_SERVICES_GET_CSTATE_INFO                GetCstateInfo;          ///< Get Cstate information
  AMD_SSDT_SERVICES_GET_PSD_DOMAIN_FOR_INDEP       GetPsdDomain;           ///< Get PDS domain for independency
  AMD_SSDT_SERVICES_GET_PSTATE_POWER               GetPstatePower;         ///< Returns power in mW for specified Pstate
};


extern EFI_GUID gAmdAcpiCpuSsdtServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_ACPI_CPU_SSDT_SERVICES_PROTOCOL_H_

