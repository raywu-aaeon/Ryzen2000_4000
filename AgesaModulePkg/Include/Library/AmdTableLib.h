/* $NoKeywords:$ */
/**
 * @file
 *
 *
 * AMD Register Table Related Functions
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

#ifndef _AMD_TABLE_LIB_H_
#define _AMD_TABLE_LIB_H_
#include "AGESA.h"
#include "Uefi.h"
#include "AMD.h"
#include "SocLogicalId.h"
#include "Library/IdsLib.h"
#pragma pack (push, 1)

/**
 * @page regtableimpl Register Table Implementation Guide
 *
 * This register table implementation is modular and extensible, so that support code as
 * well as table data can be family specific or built out if not needed, and new types
 * of table entries can be added with low overhead.  Because many aspects are now generic,
 * there can be common implementations for CPU revision and platform feature matching and for
 * finding and iterating tables.
 *
 * @par Adding a new table entry type.
 *
 * To add a new table entry type follow these steps.
 * <ul>
 * <li>  Add a member to the enum TABLE_ENTRY_TYPE which is a descriptive name of the entry's purpose
 *       or distinct characteristics.
 *
 * <li>  Create an entry data struct with the customized data needed.  For example, custom register designations,
 *       data and mask sizes, or feature comparisons.  Name your struct by adding "_" and upper-casing the enum name
 *       and adding "_TYPE_ENTRY_DATA" at the end.
 *
 * <li>  Add the entry data type as a member of the TABLE_ENTRY_DATA union.  Be aware of the size of your
 *       entry data struct; all table entries in all tables will share any size increase you introduce!
 *
 * <li>  If your data entry contains any member types except for UINT32, you can't use the generic first union member
 *       for the initializers that make up the actual tables (it's just UINT32's). The generic MSR entry is
 *       an example. Follow the steps below:
 *
 *       <ul>
 *       <li>  Make a union which has your entry data type as the first member.  Use TABLE_ENTRY_DATA as the
 *             second member.  Name this with your register followed by "_DATA_INITIALIZER".
 *
 *       <li>  Make a copy of TABLE_ENTRY_FIELDS, and rename it your register "_TYPE_ENTRY_INITIALIZER".  Rename
 *             the TABLE_ENTRY_DATA member of that struct to have the type you created in the previous step.
 *             This type can be used to declare an array of entries and make a register table in some family specific
 *             file.
 *       </ul>
 *
 * <li>  Add the descriptor that will link table entries of your data type to an implementation for it.
 *       <ul>
 *       <li>  Find the options file which instantiates the CPU_SPECIFIC_SERVICES for each logical model that will
 *             support the new entry type.
 *
 *       <li> From there find the instantiation of its TABLE_ENTRY_TYPE_DESCRIPTOR.  Add a descriptor to the
 *            to the list for your new type.  Provide the name of a function which will implement the
 *            entry data.  The function name should reflect that it implements the action for the entry type.
 *            The function must be an instance of F_DO_TABLE_ENTRY.
 *       </ul>
 *
 * <li>  Implement the function for your entry type data.  (If parts of it are family specific add methods to
 *       CPU_SPECIFIC_SERVICES for that and implement them for each family or model required.)  @n
 *       The definition of the function must conform to F_DO_TABLE_ENTRY.
 *       In the function preamble, include a cross reference to the entry enum:
 *       @code
 *       *
 *       * @TableEntryTypeMethod{::MyRegister}
 *       *
 *       @endcode
 *
 * </ul>
 *
 * @par  Adding a new Register Table
 *
 * To add a new register table for a logical CPU model follow the steps below.
 *
 * <ul>
 * <li>  Find the options file which instantiates the CPU_SPECIFIC_SERVICES for the logical model that
 *       should include the table.
 *
 * <li>  From there find the instantiation of its REGISTER_TABLE list. Add the name of the new register table.
 * </ul>
 *
 */

/*------------------------------------------------------------------------------------------*/
/*
 * Define the supported table entries.
 */
/*------------------------------------------------------------------------------------------*/

/**
 * These are the available types of table entries.
 *
 * Each type corresponds to:
 * - a semantics for the type specific data, for example semantics for a Register value,
 * Data value, and Mask value.
 * - optionally, including a method for type specific matching criteria
 * - a method for writing the desired update to the hardware.
 *
 * All types share in common a method to match CPU Family and Model and a method to match
 * platform feature set.
 *
 * N O T E: We use UINT16 for storing table entry type
 */
typedef enum {
  PciRegister,                 ///< PCI registers.
  PciProfileFixup,             ///< PCI registers which depend on Profile fixups.
  PciCpuRev,                   ///< PCI registers which depend on family / revision.
  MsrRegister,                 ///< MSR registers.
  MsrCpuRev,                   ///< MSR which depend on family / revision.
  MsrCoreRev,                  ///< MSR which depend on family / Core revision. (This type checks CPU core revison, not SoC revison)
  MsrPlatformFeat,             ///< MSR which depend on platform feature.
  MsrCpuRevPlatformFeat,       ///< MSR which depend on family / revision & platform feature.
  SmnRegisters,                ///< SMN registers.
  SmnMultiRegisters,           ///< Multi SMN registers
  SmuIndexRegister,            ///< SMU index data registers.
  SmuIndexProfileFixup,        ///< SMU index data registers which depend on Profile fixups.
  CopyBitField,                ///< Copy bitfield from register A to register B
  TableEntryTypeMax,           ///< Not a valid entry type, use for limit checking.
  TableTerminator = 0xFFFF     ///< A signature to indicate end to Jam table.
} TABLE_ENTRY_TYPE;

/*------------------------------------------------------------------------------------------*/
/*
 * Useful types and defines: Selectors, Platform Features, and type specific features.
 */
/*------------------------------------------------------------------------------------------*/

/**
 * Select tables for the current core.
 *
 * This allows more efficient register table processing, by allowing cores to skip
 * redundantly setting PCI registers, for example.  This feature is not intended to
 * be relied on for function:  it is valid to have a single register table with all settings
 * processed by every core; it's just slower.
 *
 */
typedef enum {
  AllCores,                   ///< Select only tables which apply to all cores.
  ComputeUnitPrimary,         ///< Select tables which apply to the primary core of a compute unit (SharedC, SharedNc).
  ComplexPrimary,             ///< Select tables which apply to the primary core of a complex
  DiePrimary,                 ///< Select tables which apply to the primary core of a DIE
  PrimaryCores,               ///< Select tables which apply to primary cores.
  BscCore,                    ///< Select tables which apply to the boot core.
  TableCoreSelectorMax        ///< Not a valid selector, use for limit checking.
} TABLE_CORE_SELECTOR;

/**
 * Possible time points at which register tables can be processed.
 *
 */
typedef enum {
  AmdRegisterTableTpBeforeApLaunch,         ///< Cpu code just prior to launching APs.
  AmdRegisterTableTpAfterApLaunch,          ///< Cpu code just after all APs have been launched.
  AmdRegisterTableTpBeforeApLaunchSecureS3, ///< Cpu code just prior to launching APs for secure S3
  AmdRegisterTableTpAfterApLaunchSecureS3,  ///< Cpu code just after all APs have been launched for secure S3
  MaxAmdRegisterTableTps                    ///< Not a valid time point, use for limit checking.
} REGISTER_TABLE_TIME_POINT;

//----------------------------------------------------------------------------
//                         SMN REGISTER DEFINITION
//
//----------------------------------------------------------------------------
#define SMN_ON_ALL_DIES 0xFF

//----------------------------------------------------------------------------
//                         CPU PERFORM EARLY INIT ON CORE
//
//----------------------------------------------------------------------------
/// Flag definition.

#define PACKAGE_TYPE_AM4            (1 << 2)

// Condition
#define PERFORM_EARLY_WARM_RESET    0x1          // bit  0 --- the related function needs to be run if it's warm reset
#define PERFORM_EARLY_COLD_BOOT     0x2          // bit  1 --- the related function needs to be run if it's cold boot

#define PERFORM_EARLY_ANY_CONDITION (PERFORM_EARLY_WARM_RESET | PERFORM_EARLY_COLD_BOOT)

// Initializer bit pattern values for platform features.
// Keep in synch with the PLATFORM_FEATURES struct!

#define AMD_PF_AM4     BIT0
#define AMD_PF_X2APIC  BIT1
#define AMD_PF_APIC    BIT2

// Not a platform type, but treat all others as AND
#define AMD_PF_AND            BIT31

#define AMD_PF_ALL    (AMD_PF_AM4 | AMD_PF_X2APIC | AMD_PF_APIC)
// Do not include AMD_PF_AND in AMD_PF_ALL !

/**
 * The current platform features.
 *
 * Keep this in sync with defines above that are used in the initializers!
 *
 * The comments with the bit number are useful for the computing the reserved member size, but
 * do not write code that assumes you know what bit number one of these members is.
 *
 * These platform features are standard for all logical families and models.
 */
typedef struct {
  UINT32          PlatformAm4:1;              ///< BIT_0 AM4 package
  UINT32          PlatformX2Apic:1;           ///< BIT_1 x2APIC mode desired
  UINT32          PlatformApic:1;             ///< BIT_2 APIC mode desired
  UINT32          :(30 - 3);                  ///< The possibilities are (not quite) endless.
  UINT32          AndPlatformFeats:1;         ///< BIT_31
} PLATFORM_FEATURES;

/**
 * Platform Features
 */
typedef union {
  UINT32            PlatformValue;            ///< Describe Platform Features in UINT32.
  ///< This one goes first, because then initializers use it automatically for the union.
  PLATFORM_FEATURES PlatformFeatures;         ///< Describe Platform Features in structure
} PLATFORM_FEATS;

// Initializer bit patterns for PROFILE_FEATS.

#define PERFORMANCE_AND                       BIT31

#define PERFORMANCE_PROFILE_ALL   (0)
// Do not include PERFORMANCE_AND in PERFORMANCE_PROFILE_ALL !

/**
 * Profile specific Type Features.
 *
 * Register settings for the different control flow modes can have additional dependencies
 */
typedef struct {
  UINT32       :(30 - 0);                      ///< available for future expansion.
  UINT32       AndPerformanceFeats:1;          ///< BIT_31.  AND other selected features.
} PROFILE_FEATURES;

/**
 * Profile features.
 */
typedef union {
  UINT32              ProfileValue;     ///< Initializer value.
  PROFILE_FEATURES    ProfileFeatures;  ///< The profile features.
} PROFILE_FEATS;

/*------------------------------------------------------------------------------------------*/
/*
 * The specific data for each table entry.
 */
/*------------------------------------------------------------------------------------------*/
#define BSU8(u8)      ((UINT8) (u8)  & 0xFF)
#define BSU16(u16)    ((UINT16) (u16) & 0xFF), (((UINT16) (u16) >> 8) & 0xFF)
#define BSU32(u32)    ((UINT32) (u32) & 0xFF), (((UINT32) (u32) >> 8) & 0xFF), (((UINT32) (u32) >> 16) & 0xFF), (((UINT32) (u32) >> 24) & 0xFF)
#define BSU64(u64)    ((UINT64) (u64) & 0xFF), (((UINT64) (u64) >> 8) & 0xFF), (((UINT64) (u64) >> 16) & 0xFF), (((UINT64) (u64) >> 24) & 0xFF), \
                      (((UINT64) (u64) >> 32) & 0xFF), (((UINT64) (u64) >> 40) & 0xFF), (((UINT64) (u64) >> 48) & 0xFF), (((UINT64) (u64) >> 56) & 0xFF)

#define MAKE_ENTRY_TYPE(Type)                      BSU16 (Type)
#define MAKE_PROFILE_FEATS(TypeFeats)              BSU32 (TypeFeats)
#define MAKE_SOC_LOGICAL_ID(Family, Revision)      BSU32 (Family), BSU16 (Revision)
#define MAKE_CPU_CORE_LOGICAL_ID(Family, Revision) BSU32 (Family), BSU16 (Revision)
#define MAKE_TABLE_TERMINATOR BSU16 (TableTerminator)

#define NUMBER_OF_TABLE_ENTRIES(Table) ((sizeof (Table) / sizeof (Table[0])) - 1)

/**
 * Table Entry Data for MSR Registers.
 *
 * Apply data to register after mask, for MSRs.
 */
typedef struct {
  UINT32  Address;                    ///< MSR address
  UINT64  Data;                       ///< Data to set in the MSR
  UINT64  Mask;                       ///< Mask to be applied to the MSR. Set every bit of all updated fields.
} MSR_TYPE_ENTRY_DATA;
#define MAKE_MSR_DATA(Address, Data, Mask) BSU32 (Address), BSU64 (Data), BSU64 (Mask)
#define MAKE_MSR_ENTRY(Address, Data, Mask) MAKE_ENTRY_TYPE (MsrRegister), MAKE_MSR_DATA(Address, Data, Mask)

/**
 * Table Entry Data for PCI Registers.
 *
 * Apply data to register after mask, for PCI Config registers.
 */
typedef struct {
  PCI_ADDR  Address;                  ///< Address should contain Function, Offset only.  It will apply to all CPUs
  UINT32    Data;                     ///< Data to be written into PCI device
  UINT32    Mask;                     ///< Mask to be used before data write. Set every bit of all updated fields.
} PCI_TYPE_ENTRY_DATA;
#define MAKE_PCI_DATA(Address, Data, Mask) BSU32 (Address), BSU32 (Data), BSU32 (Mask)
#define MAKE_PCI_ENTRY(Address, Data, Mask) MAKE_ENTRY_TYPE (PciRegister), MAKE_PCI_DATA(Address, Data, Mask)

/**
 * Table Entry Data for Profile Fixup Registers.
 *
 * If TypeFeats matches current config, apply data to register after mask for PCI Config registers.
 */
typedef struct {
  PROFILE_FEATS TypeFeats;             ///< Profile Fixup Features.
  PCI_TYPE_ENTRY_DATA PciEntry;        ///< The PCI Register entry data.
} PCI_PROFILE_FIXUP_TYPE_ENTRY_DATA;
#define MAKE_PCI_PROFILE_FIXUP_ENTRY(TypeFeats, Address, Data, Mask) MAKE_ENTRY_TYPE (PciProfileFixup), MAKE_PROFILE_FEATS (TypeFeats), MAKE_PCI_DATA (Address, Data, Mask)

/**
 * Table Entry Data for CPU revision specific PCI Registers.
 *
 * Apply data to register after mask, for PCI Config registers.
 */
typedef struct {
  SOC_LOGICAL_ID  CpuRevision;        ///< Common CPU Logical ID match criteria.
  PCI_ADDR        Address;            ///< Address should contain Function, Offset only.  It will apply to all CPUs
  UINT32          Data;               ///< Data to be written into PCI device
  UINT32          Mask;               ///< Mask to be used before data write. Set every bit of all updated fields.
} PCI_CPU_REV_TYPE_ENTRY_DATA;
#define MAKE_PCI_CPU_REV_ENTRY(Family, Revision, Address, Data, Mask) MAKE_ENTRY_TYPE (PciCpuRev), MAKE_SOC_LOGICAL_ID (Family, Revision), MAKE_PCI_DATA (Address, Data, Mask)

/**
 * Table Entry Data for CPU revision (SoC revison) specific MSRs.
 *
 * Apply data to register after mask, for MSRs.
 */
typedef struct {
  SOC_LOGICAL_ID  CpuRevision;        ///< Common CPU Logical ID match criteria.
  MSR_TYPE_ENTRY_DATA MsrEntry;       ///< MSR entry data.
} MSR_CPU_REV_TYPE_ENTRY_DATA;
#define MAKE_MSR_CPU_REV_ENTRY(Family, Revision, Address, Data, Mask) MAKE_ENTRY_TYPE (MsrCpuRev), MAKE_SOC_LOGICAL_ID (Family, Revision), MAKE_MSR_DATA (Address, Data, Mask)

/**
 * Table Entry Data for Core revision (Silicon revison) specific MSRs.
 *
 * Apply data to register after mask, for MSRs.
 */
typedef struct {
  CORE_LOGICAL_ID CoreRevision;       ///< Common CPU Core Logical ID match criteria.
  MSR_TYPE_ENTRY_DATA MsrEntry;       ///< MSR entry data.
} MSR_CORE_REV_TYPE_ENTRY_DATA;
#define MAKE_MSR_CORE_REV_ENTRY(Family, Revision, Address, Data, Mask) MAKE_ENTRY_TYPE (MsrCoreRev), MAKE_CPU_CORE_LOGICAL_ID (Family, Revision), MAKE_MSR_DATA (Address, Data, Mask)

/**
 * Table Entry Data for MSRs that depend on Platform Features.
 *
 * Apply data to register after mask, for MSRs.
 */
typedef struct {
  PLATFORM_FEATS      TypeFeats;          ///< Platform feature match criteria.
  MSR_TYPE_ENTRY_DATA MsrEntry;           ///< MSR entry data.
} MSR_PLATFORM_FEAT_ENTRY_DATA;
#define MAKE_MSR_PLATFORM_FEAT_ENTRY(TypeFeats, Address, Data, Mask) MAKE_ENTRY_TYPE (MsrPlatformFeat), MAKE_PROFILE_FEATS (TypeFeats), MAKE_MSR_DATA (Address, Data, Mask)

/**
 * Table Entry Data for MSRs that depend on CPU revision & Platform Features.
 *
 * Apply data to register after mask, for MSRs.
 */
typedef struct {
  SOC_LOGICAL_ID      CpuRevision;        ///< Common CPU Logical ID match criteria.
  PLATFORM_FEATS      TypeFeats;          ///< Platform feature match criteria.
  MSR_TYPE_ENTRY_DATA MsrEntry;           ///< MSR entry data.
} MSR_CPU_REV_PLATFORM_FEAT_ENTRY_DATA;
#define MAKE_MSR_CPU_REV_PLATFORM_FEAT_ENTRY(Family, Revision, TypeFeats, Address, Data, Mask) MAKE_ENTRY_TYPE (MsrCpuRevPlatformFeat), MAKE_SOC_LOGICAL_ID (Family, Revision), MAKE_PROFILE_FEATS (TypeFeats), MAKE_MSR_DATA (Address, Data, Mask)

/**
 * Table Entry Data for SMN registers.
 *
 * Apply data to register after mask, for SMNs.
 */
typedef struct {
  UINT32          InstanceId;         ///< The unique identifier of the NBIO instance associated with this socket/die
  UINT32          RegisterIndex;      ///< The index of the register
  UINT32          Data;               ///< Data to be written into SMN
  UINT32          Mask;               ///< Mask to be used before data write. Set every bit of all updated fields.
} SMN_TYPE_ENTRY_DATA;
#define MAKE_SMN_DATA(InstanceId, RegisterIndex, Data, Mask) BSU32 (InstanceId), BSU32 (RegisterIndex), BSU32 (Data), BSU32 (Mask)
#define MAKE_SMN_ENTRY(InstanceId, RegisterIndex, Data, Mask) MAKE_ENTRY_TYPE (SmnRegisters), MAKE_SMN_DATA(InstanceId, RegisterIndex, Data, Mask)

/**
 * Table Entry Data for SMN Multi registers.
 *
 * Apply data to register after mask, for SMNs.
 */
typedef struct {
  UINT32          InstanceId;         ///< The unique identifier of the NBIO instance associated with this socket/die
  UINT32          RegisterIndexStart; ///< Index Start
  UINT32          RegisterIndexEnd;   ///< Index End
  UINT32          Steps;              ///< Steps
  UINT32          Data;               ///< Data to be written into SMN
  UINT32          Mask;               ///< Mask to be used before data write. Set every bit of all updated fields.
} SMN_MULTI_TYPE_ENTRY_DATA;

#define MAKE_SMN_MULTI_DATA(InstanceId, RegisterIndexStart, RegisterIndexEnd, Steps, Data, Mask) BSU32 (InstanceId), BSU32 (RegisterIndexStart), BSU32 (RegisterIndexEnd), BSU32 (Steps), BSU32 (Data), BSU32 (Mask)
#define MAKE_SMN_MULTI_ENTRY(InstanceId, RegisterIndexStart, RegisterIndexEnd, Steps, Data, Mask) MAKE_ENTRY_TYPE (SmnMultiRegisters), MAKE_SMN_MULTI_DATA(InstanceId, RegisterIndexStart, RegisterIndexEnd, Steps, Data, Mask)
/**
 * Table Entry Data for SMU Index/Data D0F0xBC_xxxx_xxxx Registers.
 *
 * Apply data to register after mask, for PCI Config registers.
 */
typedef struct {
  UINT32    Index;                    ///< SMU index address
  UINT32    Data;                     ///< Data to be written into PCI device
  UINT32    Mask;                     ///< Mask to be used before data write. Set every bit of all updated fields.
} SMU_INDEX_ENTRY_DATA;
#define MAKE_SMU_INDEX_ENTRY_DATA(Index, Data, Mask) BSU32 (Index), BSU32 (Data), BSU32 (Mask)
#define MAKE_SMU_INDEX_ENTRY(Index, Data, Mask) MAKE_ENTRY_TYPE (SmuIndexRegister), MAKE_SMU_INDEX_ENTRY_DATA(Index, Data, Mask)

#define SMU_INDEX_ADDRESS (MAKE_SBDFO (0, 0, 0, 0, 0xB8))


/**
 * Table Entry Data for Profile Fixup to SMU Index/Data D0F0xBC_xxxx_xxxx Registers.
 *
 * If TypeFeats matches current config, apply data to register after mask for SMU Index/Data D0F0xBC_xxxx_xxxx registers.
 */
typedef struct {
  PROFILE_FEATS TypeFeats; ///< Profile Fixup Features.
  SMU_INDEX_ENTRY_DATA SmuIndexEntry;  ///< The SMU Index/Data D0F0xBC_xxxx_xxxx register entry data.
} SMU_INDEX_PROFILE_FIXUP_ENTRY_DATA;
#define MAKE_SMU_INDEX_PROFILE_FIXUP_ENTRY(TypeFeats, Index, Data, Mask) MAKE_ENTRY_TYPE (SmuIndexProfileFixup), MAKE_PROFILE_FEATS (TypeFeats), MAKE_SMU_INDEX_ENTRY_DATA (Index, Data, Mask)

/**
 * Bit field description
 *
 * Describe register type, address, MSB, LSB
 */
typedef struct {
  UINT16           RegType;            ///< Register type
  UINT32           Address;            ///< Address
  UINT8            MSB;                ///< Most Significant Bit
  UINT8            LSB;                ///< Least Significant Bit
} COPY_BIT_FIELD_DESCRIPTION;
#define MAKE_COPY_BIT_FIELD_DESCRIPTION(RegType, Address, Msb, Lsb) MAKE_ENTRY_TYPE (RegType), BSU32 (Address), BSU8 (Msb), BSU8 (Lsb)

/**
 * Table Entry Data for copying bitfield from register A to register B.
 *
 * Copy bitfield from register A to register B.
 */
typedef struct {
  COPY_BIT_FIELD_DESCRIPTION Destination; ///< Destination register descriptor
  COPY_BIT_FIELD_DESCRIPTION Source;      ///< Source register descriptor
} COPY_BIT_FIELD_ENTRY_DATA;
#define COPY_BIT_FIELD_DEST(RegType, Address, Msb, Lsb) MAKE_COPY_BIT_FIELD_DESCRIPTION (RegType, Address, Msb, Lsb)
#define COPY_BIT_FIELD_SOURCE(RegType, Address, Msb, Lsb) MAKE_COPY_BIT_FIELD_DESCRIPTION (RegType, Address, Msb, Lsb)
#define MAKE_COPY_BIT_FIELD_ENTRY(Dest, Src) MAKE_ENTRY_TYPE (CopyBitField), Dest, Src
/*------------------------------------------------------------------------------------------*/
/*
 * A complete register table and table entries.
 */
/*------------------------------------------------------------------------------------------*/

/**
 * Format of table entries :
 *
 *  UINT16          EntryType \
 *  VariableLength  EntryData / one entry
 *  UINT16          EntryType \
 *  VariableLength  EntryData / one entry
 *  ...                       \
 *  ...                       / more entries...
 */

/**
 * All the available entry data types.
 *
 * we use TABLE_ENTRY_DATA in copy bitfield entry
 *
 */
typedef union {
  PCI_TYPE_ENTRY_DATA                              PciEntry;                  ///< PCI entry.
  PCI_PROFILE_FIXUP_TYPE_ENTRY_DATA                PciProfileFixupEntry;      ///< PCI Profile Fixup entry.
  PCI_CPU_REV_TYPE_ENTRY_DATA                      PciCpuRevEntry;            ///< PCI CPU revision dependent entry.
  MSR_TYPE_ENTRY_DATA                              MsrEntry;                  ///< MSR entry.
  MSR_CPU_REV_TYPE_ENTRY_DATA                      MsrCpuRevEntry;            ///< MSR Cpu Rev dependent entry.
  MSR_PLATFORM_FEAT_ENTRY_DATA                     MsrPlatformFeatEntry;      ///< MSR Platform feature dependent entry.
  MSR_CPU_REV_PLATFORM_FEAT_ENTRY_DATA             MsrCpuRevPlatformFeatEntry;///< MSR Cpu Rev & Platform feature dependent entry.
  SMU_INDEX_ENTRY_DATA                             SmuIndexEntry;             ///< SMU Index Data entry.
  SMU_INDEX_PROFILE_FIXUP_ENTRY_DATA               ProfileFixupSmuIndexEntry; ///< SMU index Data dependent entry.
  COPY_BIT_FIELD_ENTRY_DATA                        CopyBitFieldEntry;         ///< Copy bitfield entry.
} TABLE_ENTRY_DATA;

/**
 * Register Table Entry common fields.
 *
 * All the various types of register table entries are subclasses of this object.
 */
typedef struct {
  UINT16                 EntryType;                  ///< The type of table entry this is.
  TABLE_ENTRY_DATA       EntryData;                  ///< The pointer to the first entry.
} TABLE_ENTRY_FIELDS;

/**
 * An entire register table.
 */
typedef struct {
  UINT32               Selector;                     ///< For efficiency, these cores should process this table
  CONST UINT8*         Table;                        ///< The table entries.
} REGISTER_TABLE;

/**
 * An entire register table at given time point.
 */
typedef struct {
  REGISTER_TABLE_TIME_POINT TimePoint;               ///< Time point
  CONST REGISTER_TABLE**    TableList;               ///< The table list.
} REGISTER_TABLE_AT_GIVEN_TP;

/**
 * A Family Specific Workaround method.
 *
 * \@TableTypeFamSpecificInstances.
 *
 * When called, the entry's CPU Logical ID and Platform Features matched the current config.
 * The method must implement any specific criteria checking for the workaround.
 *
 * See if you can use the other entries or make an entry specifically for the fix.
 * After all, the purpose of having a table entry is to @b NOT have code which
 * isn't generic feature code, but is family/model specific.
 *
 * @param[in]     Data       The table data value, for example to indicate which CPU and Platform types matched.
 * @param[in]     StdHeader  Config params for library, services.
 */
typedef VOID F_FAM_SPECIFIC_WORKAROUND (
  IN       UINT32              Data,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );
/// Reference to a method.
typedef F_FAM_SPECIFIC_WORKAROUND *PF_FAM_SPECIFIC_WORKAROUND;

/*------------------------------------------------------------------------------------------*/
/*
 * Describe implementers for table entries.
 */
/*------------------------------------------------------------------------------------------*/

/**
 * Implement the semantics of a Table Entry Type.
 *
 * @TableEntryTypeInstances.
 *
 * @param[in]       CurrentEntry        The type specific entry data to be implemented (that is written).
 * @param[in]       StdHeader           Config params for library, services.
 */
typedef VOID F_DO_TABLE_ENTRY (
  IN       UINT8                 **CurrentEntry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );
/// Reference to a method
typedef F_DO_TABLE_ENTRY *PF_DO_TABLE_ENTRY;

/**
 * Describe the attributes of a Table Entry Type.
 */
typedef struct {
  UINT16                 EntryType;                  ///< The type of table entry this describes.
  PF_DO_TABLE_ENTRY      DoTableEntry;               ///< Provide all semantics associated with TABLE_ENTRY_DATA
} TABLE_ENTRY_TYPE_DESCRIPTOR;

/*------------------------------------------------------------------------------------------*/
/*
 * Table related function prototypes (many are instance of F_DO_TABLE_ENTRY method).
 */
/*------------------------------------------------------------------------------------------*/

/**
 * Get the next register table
 */
REGISTER_TABLE **GetNextRegisterTable (
  IN       UINT32                  Selector,
  IN       REGISTER_TABLE        **RegisterTableList,
  IN OUT   REGISTER_TABLE       ***RegisterTableHandle,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * If current core is CoreSelector core
 */
BOOLEAN
IsCoreSelector (
  IN       UINT32                    Selector,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

/**
 * Set the registers for this core based on entries in a list of Register Table.
 */
VOID
SetRegistersFromTable (
  IN       UINT8                  *RegisterEntry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Set the registers for this core based on entries in a list of Register Table.
 */
VOID
SetRegistersFromTableList (
  IN       REGISTER_TABLE         **RegisterTableList,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Processes the register table at the given time point.
 */
AGESA_STATUS
SetRegistersFromTablesAtGivenTimePoint (
  IN       REGISTER_TABLE_AT_GIVEN_TP *RegTableListAtGivenTP,
  IN       REGISTER_TABLE_TIME_POINT  TimePoint,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

/**
 * Find the features of the running platform.
 */
VOID
GetPlatformFeatures (
     OUT   PLATFORM_FEATS    *Features,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );


/**
 * Returns the profile features list of the currently running processor core.
 */
VOID
GetPerformanceFeatures (
     OUT   PROFILE_FEATS      *Features,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

/**
 * Checks register table entry type specific criteria to the platform.
 */
BOOLEAN
DoesEntryTypeSpecificInfoMatch (
  IN       UINT32   PlatformTypeSpecificFeatures,
  IN       UINT32   EntryTypeFeatures
  );

/**
 * Perform the MSR Register Entry.
 */
VOID
SetMsrEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the CPU (SoC) Rev MSR Entry.
 */
VOID
SetMsrCpuRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the Core (silicon) Rev MSR Entry.
 */
VOID
SetMsrCoreRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the Platform feature dependent MSR Entry.
 */
VOID
SetMsrPlatformFeatEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the CPU Rev & Platform feature dependent MSR Entry.
 */
VOID
SetMsrCpuRevPlatformFeatEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the PCI Register Entry.
 */
VOID
SetPciEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the PCI Register Entry.
 */
VOID
SetPciCpuRevEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the Profile PCI Register Entry.
 */
VOID
SetPciProfileFixupEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the SMN Register Entry.
 */
VOID
SetSmnEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Sub-function for SMN Register Entry.
 */
VOID
SetSmnEntryLib (
  IN       UINT32                  InstanceId,
  IN       UINT32                  RegisterIndex,
  IN       UINT32                  RegisterANDValue,
  IN       UINT32                  RegisterORValue
  );

/**
 * Perform the SMN Multi Register Entry.
 */
VOID
SetSmnMultiEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the SMU Index/Data Register Entry.
 */
VOID
SetSmuIndexEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the Profile SMU Index/Data Register Entry.
 */
VOID
SetSmuIndexProfileFixupEntry (
  IN       UINT8                  **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/**
 * Perform the Copy Bitfield Entry.
 */
VOID
CopyBitFieldEntry (
  IN       UINT8                 **Entry,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

#pragma pack (pop)
#endif // _AMD_TABLE_LIB_H_

