/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD MSCT Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Protocol
 * @e \$Revision:  $   @e \$Date:  $
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
 */

#ifndef _AMD_ACPI_MSCT_SERVICES_PROTOCOL_H_
#define _AMD_ACPI_MSCT_SERVICES_PROTOCOL_H_

#pragma pack (push, 1)

/// Format for MSCT Header
typedef struct {
  UINT8  Signature[4];        ///< 'MSCT' Signature for the Maximum System Characteristics Table
  UINT32 Length;              ///< Length, in bytes, of the entire MSCT
  UINT8  Revision;            ///< 1
  UINT8  Checksum;            ///< Entire table must sum to zero
  UINT8  OemId[6];            ///< OEM ID
  UINT8  OemTableId[8];       ///< For the MSCT, the table ID is the manufacturer model ID
  UINT32 OemRevision;         ///< OEM revision of MSCT for supplied OEM Table ID
  UINT8  CreatorId[4];        ///< Vendor ID of utility that created the table
  UINT32 CreatorRev;          ///< Revision of utility that created the table
  UINT32 OffsetProxDomInfo;   ///< Offset in bytes to the Proximity Domain Information Structure table entry
  UINT32 MaxProxDom;          ///< Maximum number of Proximity Domains ever possible in the system
  UINT32 MaxClkDom;           ///< Maximum number of Clock Domains ever possible in the system
  UINT64 MaxPhysAddr;         ///< Maximum Physical Address ever possible in the system
} MSCT_HEADER;

/// Format for Maximum Proximity Domain Information Structure
typedef struct {
  UINT8  Revision;            ///< 1
  UINT8  Length;              ///< 22
  UINT32 ProximityLow;        ///< Starting proximity domain for the range that this structure is providing information
  UINT32 ProximityHigh;       ///< Ending proximity domain for the range that this structure is providing information
  UINT32 MaxProcCap;          ///< Maximum Procesor Capacity of each of the Proximity Domains specified in the range
  UINT64 MaxMemCap;           ///< Maximum Memory Capacity (in bytes) of the Proximity Domains specified in the range
} MSCT_PROX_DOMAIN_INFO_STRUCT;

/// Format for Maximum Proximity Domain Structure
typedef struct {
  UINT32        ProxDomain;   ///< Proximity Domain
  UINT32        MaxProcCap;   ///< Maximum (Actual) Processor Capacity
  UINT64        MaxMemCap;    ///< Maximum (Actual) Memory Capacity
} MSCT_PROX_DOMAIN_INFO;

/// Forward declaration for AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL
typedef struct _AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_MSCT_SERVICES_GET_MSCT_INFO) (
  IN       AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL  *This,
     OUT   UINT32                                  *HighestProxDomain,
     OUT   UINT32                                  *MaxNumProxDomains,
     OUT   MSCT_PROX_DOMAIN_INFO                  **MsctDomainInfo
  );

/// When installed, the MSCT Services Protocol produces a collection of
/// services related to MSCT
struct _AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL {
  UINTN                                                Revision;                    ///< Revision Number
  AMD_MSCT_SERVICES_GET_MSCT_INFO                      GetMsctInfo;                 ///< Returns information to populate MSCT maximum proximity structures
};

extern EFI_GUID gAmdFabricAcpiMsctServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_ACPI_MSCT_SERVICES_PROTOCOL_H_
