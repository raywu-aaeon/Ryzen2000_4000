/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CRAT Services Protocol prototype definition
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
#ifndef _AMD_ACPI_CRAT_SERVICES_PROTOCOL_H_
#define _AMD_ACPI_CRAT_SERVICES_PROTOCOL_H_

#pragma pack (push, 1)

/*----------------------------------------------------------------------------------------
 *                    T Y P E D E F S     A N D     S T R U C T U R E S
 *                            Component Resource Affinity Table
 *----------------------------------------------------------------------------------------
 */
#define L1_CACHE 1
#define L2_CACHE 2
#define L3_CACHE 3

/// Format for CRAT Header
typedef struct {
  UINT8   Sign[4];                   ///< CRAT, Signature for the Component Resource Affinity Table.
  UINT32  Length;                    ///< Length, in bytes, of the entire CRAT
  UINT8   Revision;                  ///< 0
  UINT8   Checksum;                  ///< Entire table must sum to zero.
  UINT8   OemId[6];                  ///< OEM ID
  UINT8   OemTableId[8];             ///< OEM Tabled ID
  UINT32  OemRev;                    ///< OEM Revision
  UINT8   CreatorId[4];              ///< Creator ID
  UINT32  CreatorRev;                ///< Creator Revision
  UINT32  TotalEntries;              ///< total number[n] of entries in the CRAT
  UINT16  NumNodes;                  ///< Number of HSA nodes as defined by NUMA "memory locality"
  UINT8   Reserved[6];               ///< Reserved
} CRAT_HEADER;

/// Flags field of the CRAT HSA Processing Unit Affinity Structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 HotPluggable:1;             ///< Hot Pluggable
  UINT32 CpuPresent:1;               ///< Cpu Present
  UINT32 GpuPresent:1;               ///< Gpu Present
  UINT32 HSAmmuPresent:1;            ///< HSAmmu Present
  UINT32 VALimits:3;                 ///< VALimits
  UINT32 AtomicOps:2;                ///< AtomicOps
  UINT32 :22;                        ///< Reserved
} CRAT_HSA_PROCESSING_UNIT_FLAG;

/// CRAT HSA Processing Unit Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 0 - CRAT HSA Processing Unit Structure
  UINT8  Length;                     ///< 40
  UINT16 Reserved;                   ///< Reserved
  CRAT_HSA_PROCESSING_UNIT_FLAG Flags; ///< Flags - HSA Processing Unit Affinity Structure
  UINT32 ProximityNode;              ///< Integer that represents the proximity node to which the node belongs to
  UINT32 ProcessorIdLow;             ///< Low value  of the logical processor included in this HSA proximity domain
  UINT16 NumCPUCores;                ///< Indicates count of CCompute execution units present in this APU node.
  UINT16 NumSIMDCores;               ///< Indicates maximum count of HCompute SIMD cores present in this node.
  UINT16 MaxWavesSIMD;               ///< This identifies the max. number of launched waves per SIMD.
  UINT16 IoCount;                    ///< Number of discoverable IO Interfaces connecting this node to other components.
  UINT16 HSACapability;              ///< Must be 0
  UINT16 LDSSizeInKB;                ///< Size of LDS memory per SIMD Wavefront
  UINT8  WaveFrontSize;              ///< 64, may be 32 for some FSA based architectures
  UINT8  NumShaderBanks;             ///< Number of Banks or "Shader Engines", typically 1 or 2
  UINT16 uEngineIdentifier;          ///< Identifier (Rev) of the GPU uEngine or firmware
  UINT8  NumArrays;                  ///< Number of SIMD Arrays per Engine
  UINT8  NumCUPerArray;              ///< Number of Compute Units (CU) per SIMD Array
  UINT8  NumSIMDPerCU;               ///< Number of SIMD representing a Compute Unit
  UINT8  MaxSlotsScratchCU;          ///< Max. Number of temp. memory ("scratch") wave slots
                                     ///< available to access, may be 0 if HW has no restrictions
  UINT8  Reserved1[4];               ///< Reserved
} CRAT_HSA_PROCESSING_UNIT;

/// Flags field of the CRAT Memory Affinity Structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 HotPluggable:1;             ///< Hot Pluggable
  UINT32 NonVolatile:1;              ///< If set, the memory region represents Non-Volatile memory
  UINT32 AtomicOpsTarget:2;          ///< AtomicOpsTarget
  UINT32 :27;                        ///< Reserved
} CRAT_MEMORY_FLAG;

/// CRAT Memory Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 1 - CRAT Memory Affinity Structure
  UINT8  Length;                     ///< 40
  UINT16 Reserved;                   ///< Reserved
  CRAT_MEMORY_FLAG Flags;            ///< Flags - Memory Affinity Structure. Indicates whether the region of memory is enabled and can be hot plugged
  UINT32 ProximityDomain;            ///< Integer that represents the proximity domain to which the node belongs to
  UINT32 BaseAddressLow;             ///< Low 32Bits of the Base Address of the memory range
  UINT32 BaseAddressHigh;            ///< High 32Bits of the Base Address of the memory range
  UINT32 LengthLow;                  ///< Low 32Bits of the length of the memory range
  UINT32 LengthHigh;                 ///< High 32Bits of the length of the memory range
  UINT32 Width;                      ///< Memory width - Specifies the number of parallel bits of the memory interface
  UINT8  Reserved1[8];               ///< Reserved
} CRAT_MEMORY;

/// Flags field of the CRAT Cache Affinity structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 DataCache:1;                ///< 1 if cache includes data
  UINT32 InstructionCache:1;         ///< 1 if cache includes instructions
  UINT32 CpuCache:1;                 ///< 1 if cache is part of CPU functionality
  UINT32 SimdCache:1;                ///< 1 if cache is part of SIMD functionality
  UINT32 GlobalDataStore:1;          ///< GDS is an explicitly addressed type  of GPU-on chip memory used as cache, this property must be combined with "specialty cache" attribute
  UINT32 AtomicOpsCache:1;           ///< Indicates if AtomicOps are supported within the cache, typically used for explicitly addressed SIMD caches (e.g. L2)
  UINT32 :25;                        ///< Reserved
} CRAT_CACHE_FLAG;

/// CRAT Cache Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 2 - CRAT Cache Affinity Structure
  UINT8  Length;                     ///< 64
  UINT16 Reserved;                   ///< Reserved
  CRAT_CACHE_FLAG Flags;             ///< Flags - Cache Affinity Structure. Indicates whether the region of cache is enabled
  UINT32 ProcessorIdLow;             ///< Low value of a logical processor which includes this component
  UINT8  SiblingMap[32];             ///< Bitmask of  Processor Id sharing this component. 1 bit per logical processor
  UINT32 CacheSize;                  ///< Cache size in KB
  UINT8  CacheLevel;                 ///< Integer representing level: 1, 2, 3, 4, etc.
  UINT8  LinesPerTag;                ///< Cache Lines per tag
  UINT16 CacheLineSize;              ///< Cache line size in bytes
  UINT8  Associativity;              ///< Cache associativity
                                     ///< The associativity fields are encoded as follows:
                                     ///< 00h: Reserved.
                                     ///< 01h: Direct mapped.
                                     ///< 02h-FEh: Associativity. (e.g., 04h = 4-way associative.)
                                     ///< FFh: Fully associative
  UINT8  CacheProperties;            ///< Cache Properties bits [2:0] represent Inclusive/Exclusive property encoded.
                                     ///< 0: Cache is strictly exclusive to lower level caches.
                                     ///< 1: Cache is mostly exclusive to lower level caches.
                                     ///< 2: Cache is strictly inclusive to lower level caches.
                                     ///< 3: Cache is mostly inclusive to lower level caches.
                                     ///< 4: Cache is a "constant cache" (= explicit update)
                                     ///< 5: Cache is a "specialty cache" (e.g. Texture cache)
                                     ///< 6-7: Reserved
                                     ///< CacheProperties bits [7:3] are reserved
  UINT16 CacheLatency;               ///< Cost of time to access cache described in nanoseconds.
  UINT8  Reserved1[8];               ///< Reserved
} CRAT_CACHE;

/// Flags field of the CRAT TLB Affinity structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 DataTLB:1;                  ///< 1 if TLB includes translation information for data.
  UINT32 InstructionTLB:1;           ///< 1 if TLB includes translation information for instructions.
  UINT32 CpuTLB:1;                   ///< 1 if TLB is part of CPU functionality
  UINT32 SimdTLB:1;                  ///< 1 if TLB is part of SIMD functionality
  UINT32 TLB4KBase256:1;             ///< 1 if value in table is factored by 256 to get number of 4K entries
  UINT32 :1;                         ///< Reserved
  UINT32 TLB2MBase256:1;             ///< 1 if value in table is factored by 256 to get number of 2M entries
  UINT32 :1;                         ///< Reserved
  UINT32 TLB1GBase256:1;             ///< 1 if value in table is factored by 256 to get number of 1G entries
  UINT32 :22;                        ///< Reserved
} CRAT_TLB_FLAG;

/// CRAT TLB Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 3 - CRAT TLB  Affinity Structure
  UINT8  Length;                     ///< 64
  UINT16 Reserved;                   ///< Reserved
  CRAT_TLB_FLAG Flags;               ///< Flags - TLB Affinity Structure. Indicates whether the TLB is enabled and defined
  UINT32 ProcessorIdLow;             ///< Low value of a logical processor which includes this component.
  UINT8  SiblingMap[32];             ///< Bitmask of Processor Id sharing this component. 1 bit per logical processor
  UINT32 TlbLevel;                   ///< Integer representing level: 1, 2, 3, 4, etc.
  UINT8  DataTlbAssociativity2MB;    ///< Data TLB associativity for 2MB pages
                                     ///< The associativity fields are encoded as follows:
                                     ///< 00h: Reserved.
                                     ///< 01h: Direct mapped.
                                     ///< 02h-FEh: Associativity. (e.g., 04h = 4-way associative.)
                                     ///< FFh: Fully associative.
  UINT8  DataTlbSize2MB;             ///< Data TLB number of entries for 2MB.
  UINT8  InstructionTlbAssociativity2MB;      ///< Instruction TLB associativity for 2MB pages
                                     ///< The associativity fields are encoded as follows:
                                     ///< 00h: Reserved.
                                     ///< 01h: Direct mapped.
                                     ///< 02h-FEh: Associativity. (e.g., 04h = 4-way associative.)
                                     ///< FFh: Fully associative.
  UINT8  InstructionTlbSize2MB;      ///< Instruction TLB number of entries for 2MB pages.
  UINT8  DTLB4KAssoc;                ///< Data TLB Associativity for 4KB pages
  UINT8  DTLB4KSize;                 ///< Data TLB number of entries for 4KB pages
  UINT8  ITLB4KAssoc;                ///< Instruction TLB Associativity for 4KB pages
  UINT8  ITLB4KSize;                 ///< Instruction TLB number of entries for 4KB pages
  UINT8  DTLB1GAssoc;                ///< Data TLB Associativity for 1GB pages
  UINT8  DTLB1GSize;                 ///< Data TLB number of entries for 1GB pages
  UINT8  ITLB1GAssoc;                ///< Instruction TLB Associativity for 1GB pages
  UINT8  ITLB1GSize;                 ///< Instruction TLB number of entries for 1GB pages
  UINT8  Reserved1[4];               ///< Reserved
} CRAT_TLB;

/// Flags field of the CRAT FPU Affinity structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 :31;                        ///< Reserved
} CRAT_FPU_FLAG;

/// CRAT FPU Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 4 - CRAT FPU Affinity Structure
  UINT8  Length;                     ///< 64
  UINT16 Reserved;                   ///< Reserved
  CRAT_FPU_FLAG Flags;               ///< Flags - FPU Affinity Structure. Indicates whether the region of FPU affinity structure is enabled and defined
  UINT32 ProcessorIdLow;             ///< Low value of a logical processor which includes this component.
  UINT8  SiblingMap[32];             ///< Bitmask of  Processor Id sharing this component. 1 bit per logical processor
  UINT32 FPUSize;                    ///< Product specific
  UINT8  Reserved1[16];              ///< Reserved
} CRAT_FPU;

/// Flags field of the CRAT IO Affinity structure
typedef struct {
  UINT32 Enabled:1;                  ///< Enabled
  UINT32 Coherency:1;                ///< If set, IO interface supports coherent transactions (natively or through protocol extensions)
  UINT32 :30;                        ///< Reserved
} CRAT_IO_FLAG;

/// CRAT IO Affinity Structure
typedef struct {
  UINT8  Type;                       ///< 5 - CRAT IO Affinity Structure
  UINT8  Length;                     ///< 64
  UINT16 Reserved;                   ///< Reserved
  CRAT_IO_FLAG Flags;                ///< Flags - IO Affinity Structure. Indicates whether the region of IO affinity structure is enabled and defined.
  UINT32 ProximityDomainFrom;        ///< Integer that represents the proximity domain to which the IO Interface belongs to
  UINT32 ProximityDomainTo;          ///< Integer that represents the other proximity domain to which the IO Interface belongs to
  UINT8  IoType;                     ///< IO Interface type. Values defined are
                                     ///< 0: Undefined
                                     ///< 1: Hypertransport
                                     ///< 2: PCI Express
                                     ///< 3: Other (e.g. internal)
                                     ///< 4-255: Reserved
  UINT8  VersionMajor;               ///< Major version of the Bus interface
  UINT16 VersionMinor;               ///< Minor version of the Bus interface ((optional)
  UINT32 MinimumLatency;             ///< Cost of time to transfer, described in nanoseconds.
  UINT32 MaximumLatency;             ///< Cost of time to transfer, described in nanoseconds.
  UINT32 MinimumBandwidth;           ///< Minimum interface Bandwidth in MB/s
  UINT32 MaximumBandwidth;           ///< Maximum interface Bandwidth in MB/s
  UINT32 RecommendedTransferSize;    ///< Recommended transfer size to reach maximum interface bandwidth in Bytes
  UINT8  Reserved1[24];              ///< Reserved
} CRAT_IO;

/// CRAT entry type
typedef enum {
  CRAT_HSA_PROC_UNIT_TYPE = 0,       ///< 0 - CRAT HSA Processing Unit Structure
  CRAT_MEMORY_TYPE,                  ///< 1 - CRAT Memory Affinity Structure
  CRAT_CACHE_TYPE,                   ///< 2 - CRAT Cache Affinity Structure
  CRAT_TLB_TYPE,                     ///< 3 - CRAT TLB  Affinity Structure
  CRAT_FPU_TYPE,                     ///< 4 - CRAT FPU Affinity Structure
  CRAT_IO_TYPE,                      ///< 5 - CRAT IO Affinity Structure
  CRAT_MAX_TYPE,                     ///< MaxValue
} CRAT_ENTRY_TYPE;

/*----------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                H S A   C A C H E   T L B
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_CRAT_SERVICES_GET_HSA_PROC_CCX_ENTRY) (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

typedef
EFI_STATUS
(EFIAPI *AMD_CRAT_SERVICES_GET_CACHE_ENTRY) (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

typedef
EFI_STATUS
(EFIAPI *AMD_CRAT_SERVICES_GET_TLB_ENTRY) (
  IN       AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN       CRAT_HEADER                            *CratHeaderStructPtr,
  IN OUT   UINT8                                 **TableEnd
  );

///
/// When installed, the CRAT Services Protocol produces a collection of
/// services that return various information to generate CRAT
///
struct _AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL {
  UINTN                                            Revision;                ///< Revision Number
  AMD_CRAT_SERVICES_GET_HSA_PROC_CCX_ENTRY         GetCratHsaProcCcxEntry;  ///< HSA processor info --- Ccx part
  AMD_CRAT_SERVICES_GET_CACHE_ENTRY                GetCratCacheEntry;       ///< Cache info
  AMD_CRAT_SERVICES_GET_TLB_ENTRY                  GetCratTlbEntry;         ///< TLB info
};


/*----------------------------------------------------------------------------------------
 *                M E M O R Y
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_CRAT_SERVICES_CREATE_MEMORY) (
  IN       AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL     *This,
  IN       CRAT_HEADER                                *CratHeaderStructPtr,
  IN OUT   UINT8                                     **TableEnd
  );

///
/// When installed, the CRAT Services Protocol produces a collection of
/// services that return various information to generate CRAT
///
struct _AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL {
  UINTN                                Revision;       ///< Revision Number
  AMD_CRAT_SERVICES_CREATE_MEMORY      CreateMemory;   ///< Create Memory Affinity Structure
};

/*----------------------------------------------------------------------------------------
 *               i G P U
 *----------------------------------------------------------------------------------------
 */

///
/// Forward declaration for the AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL.
///
typedef struct _AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_CRAT_SERVICES_GET_HSA_PROC_IGPU_ENTRY) (
  IN       AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL    *This,
  IN OUT   CRAT_HSA_PROCESSING_UNIT               *CratHsaEntry
  );

///
/// When installed, the CRAT Services Protocol produces a collection of
/// services that return various information to generate CRAT
///
struct _AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL {
  UINTN                                            Revision;                ///< Revision Number
  AMD_CRAT_SERVICES_GET_HSA_PROC_IGPU_ENTRY        GetCratHsaProcIGpuEntry;  ///< HSA processor info --- IGPU part
};

extern EFI_GUID gAmdCcxAcpiCratServicesProtocolGuid;
extern EFI_GUID gAmdFabricAcpiCratServicesProtocolGuid;
extern EFI_GUID gAmdIGpuAcpiCratServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_ACPI_CRAT_SERVICES_PROTOCOL_H_

