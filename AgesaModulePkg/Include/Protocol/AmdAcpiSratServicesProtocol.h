/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD SRAT Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#ifndef _AMD_ACPI_SRAT_SERVICES_PROTOCOL_H_
#define _AMD_ACPI_SRAT_SERVICES_PROTOCOL_H_

#pragma pack (push, 1)

/*----------------------------------------------------------------------------------------
 *                    T Y P E D E F S     A N D     S T R U C T U R E S
 *                            System Resource Affinity Table
 *----------------------------------------------------------------------------------------
 */
/// Format for SRAT Header
typedef struct {
  UINT8   Sign[4];                   ///< SRAT, Signature for the System Resource Affinity Table
  UINT32  Length;                    ///< Length, in bytes, of the entire SRAT
  UINT8   Revision;                  ///< 0
  UINT8   Checksum;                  ///< Entire table must sum to zero.
  UINT8   OemId[6];                  ///< OEM ID
  UINT8   OemTableId[8];             ///< OEM Tabled ID
  UINT32  OemRev;                    ///< OEM Revision
  UINT8   CreatorId[4];              ///< Creator ID
  UINT32  CreatorRev;                ///< Creator Revision
  UINT32  Reserved;                  ///< Reserved to be 1 for backward compatibility
  UINT8   Reserved2[8];              ///< Reserved
} SRAT_HEADER;

/// Format for Processor Local APIC/SAPIC Affinity Structure
typedef struct {
  UINT32  Enabled:1 ;                ///< Enabled
  UINT32  :31;                       ///< Reserved
} SRAT_APIC_FLAG;

/// Format for Processor Local APIC/SAPIC Affinity Structure
typedef struct {
  UINT8   Type;                      ///< 0 Processor Local APIC/SAPIC Affinity Structure
  UINT8   Length;                    ///< 16
  UINT8   ProximityDomain_7_0;       ///< Bit [7:0] of the proximity domain to which the processor belongs
  UINT8   ApicId;                    ///< The processor local APIC ID
  SRAT_APIC_FLAG Flags;              ///< Flags
  UINT8   LocalSapicEid;             ///< The processor local SAPIC EID
  UINT8   ProximityDomain_31_8[3];   ///< Bit [31:8] of the proximity domain to which the processor belongs
  UINT32  ClockDomain;               ///< The clock domain to which the processor belongs
} SRAT_APIC;

/// Format for Memory Affinity Structure
typedef struct {
  UINT32  Enabled:1;                 ///< Enabled
  UINT32  HotPluggable:1;            ///< Hot pluggable
  UINT32  NonVolatile:1;             ///< Non Volatile
  UINT32  :29;                       ///< Reserved
} SRAT_MEMORY_FLAG;

/// Format for Memory Affinity Structure
typedef struct {
  UINT8   Type;                      ///< 1 Memory Affinity Structure
  UINT8   Length;                    ///< 40
  UINT32  ProximityDomain;           ///< Integer that represents the proximity domain to which the processor belongs
  UINT8   Reserved[2];               ///< Reserved
  UINT32  BaseAddressLow;            ///< Low 32 Bits of the Base Address of the memory range
  UINT32  BaseAddressHigh;           ///< High 32 Bits of the Base Address of the memory range
  UINT32  LengthLow;                 ///< Low 32 Bits of the length of the memory range
  UINT32  LengthHigh;                ///< High 32 Bits of the length of the memory range
  UINT8   Reserved2[4];              ///< Reserved
  SRAT_MEMORY_FLAG Flags;            ///< Flags
  UINT8   Reserved3[8];              ///< Reserved
} SRAT_MEMORY;

/// Format for Processor Local x2APIC Affinity Structure
typedef struct {
  UINT8   Type;                      ///< 2 Processor Local APIC/SAPIC Affinity Structure
  UINT8   Length;                    ///< 24
  UINT8   Reserved[2];               ///< Reserved - Must be zero
  UINT32  ProximityDomain;           ///< The proximity domain to which the logical processor belongs
  UINT32  x2ApicId;                  ///< The processor local x2APIC ID
  SRAT_APIC_FLAG Flags;              ///< Flags
  UINT32  ClockDomain;               ///< The clock domain to which the processor belongs
  UINT8   Reserved2[4];              ///< Reserved
} SRAT_x2APIC;

/// Format for GICC Affinity Structure
typedef struct {
  UINT32  Enabled:1 ;                ///< Enabled
  UINT32  :31;                       ///< Reserved
} SRAT_GICC_FLAG;

/// Format for GICC Affinity Structure
typedef struct {
  UINT8   Type;                      ///< 3 GICC Affinity Structure
  UINT8   Length;                    ///< 18
  UINT32  ProximityDomain;           ///< The proximity domain to which the logical processor belongs
  UINT32  AcpiProcessorUid;          ///< The ACPI Processor UID of the associated GICC
  SRAT_GICC_FLAG Flags;              ///< Flags
  UINT32  ClockDomain;               ///< The clock domain to which the processor belongs
} SRAT_GICC;

/// SRAT struct type
typedef enum {
  SRAT_LOCAL_APIC_TYPE = 0,          ///< 0 - SRAT Processor Local APIC/SAPIC Affinity Structure
  SRAT_MEMORY_TYPE,                  ///< 1 - SRAT Memory Affinity Structure
  SRAT_LOCAL_X2_APIC_TYPE,           ///< 2 - SRAT Processor Local x2APIC Affinity Structure
  SRAT_GICC_TYPE,                    ///< 3 - SRAT GICC Affinity Structure
} SRAT_STRUCT_TYPE;

// Memory Info structure
typedef struct {
  UINT32   Domain;                   ///< Domain number
  UINT64   RegionSize;               ///< Size of memory region in this domain
} MEMORY_INFO;
/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                L O C A L     A P I C
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_SRAT_SERVICES_CREATE_LAPIC) (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

typedef
EFI_STATUS
(EFIAPI *AMD_SRAT_SERVICES_CREATE_X2APIC) (
  IN       AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL    *This,
  IN       SRAT_HEADER                            *SratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

///
/// When installed, the SRAT Services Protocol produces a collection of
/// services that return various information to generate SRAT
///
struct _AMD_CCX_ACPI_SRAT_SERVICES_PROTOCOL {
  UINTN                                Revision;       ///< Revision Number
  AMD_SRAT_SERVICES_CREATE_LAPIC       CreateLapic;    ///< Create Processor Local APIC/SAPIC Affinity Structure
  AMD_SRAT_SERVICES_CREATE_X2APIC      CreateX2Apic;   ///< Create Processor X2 APIC Affinity Structure
};

/*----------------------------------------------------------------------------------------
 *                M E M O R Y
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_SRAT_SERVICES_CREATE_MEMORY) (
  IN       AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL     *This,
  IN       SRAT_HEADER                                *SratHeaderStructPtr,
  IN OUT   UINT8                                     **TableEnd
  );

typedef
EFI_STATUS
(EFIAPI *AMD_SRAT_SERVICES_GET_MEMORY_INFO) (
  IN       AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL      *This,
     OUT   UINT32                                      *NumberOfDomains,
     OUT   MEMORY_INFO                                **MemoryInfo
  );
///
/// When installed, the SRAT Services Protocol produces a collection of
/// services that return various information to generate SRAT
///
struct _AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL {
  UINTN                                Revision;       ///< Revision Number
  AMD_SRAT_SERVICES_CREATE_MEMORY      CreateMemory;   ///< Create Memory Affinity Structure
  AMD_SRAT_SERVICES_GET_MEMORY_INFO    GetMemoryInfo;  ///< Return Memory Affinity Information
};

extern EFI_GUID gAmdCcxAcpiSratServicesProtocolGuid;
extern EFI_GUID gAmdFabricAcpiSratServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_ACPI_SRAT_SERVICES_PROTOCOL_H_

