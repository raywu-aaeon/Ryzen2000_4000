/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdSmmCommunication.h
 *
 * Contains definition for AmdSmmCommunication
 *
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

#ifndef _AMD_SMBIOS_H_
#define _AMD_SMBIOS_H_

#pragma pack (push, 1)

///
/// Reference SMBIOS 2.7, chapter 6.1.2.
/// The UEFI Platform Initialization Specification reserves handle number FFFEh for its
/// EFI_SMBIOS_PROTOCOL.Add() function to mean "assign an unused handle number automatically."
/// This number is not used for any other purpose by the SMBIOS specification.
///
#define AMD_SMBIOS_HANDLE_PI_RESERVED                       0xFFFE

#define AMD_EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION           4
#define AMD_EFI_SMBIOS_TYPE_CACHE_INFORMATION               7
#define AMD_EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY           16
#define AMD_EFI_SMBIOS_TYPE_MEMORY_DEVICE                   17
#define AMD_EFI_SMBIOS_TYPE_32BIT_MEMORY_ERROR_INFORMATION  18
#define AMD_EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS     19
#define AMD_EFI_SMBIOS_TYPE_MEMORY_DEVICE_MAPPED_ADDRESS    20

///
/// Types 0 through 127 (7Fh) are reserved for and defined by this
/// specification. Types 128 through 256 (80h to FFh) are available for system- and OEM-specific information.  
///
typedef UINT8  AMD_SMBIOS_TYPE;

///
/// Specifies the structure's handle, a unique 16-bit number in the range 0 to 0FFFEh (for version
/// 2.0) or 0 to 0FEFFh (for version 2.1 and later). The handle can be used with the Get SMBIOS
/// Structure function to retrieve a specific structure; the handle numbers are not required to be
/// contiguous. For v2.1 and later, handle values in the range 0FF00h to 0FFFFh are reserved for
/// use by this specification.
/// If the system configuration changes, a previously assigned handle might no longer exist.
/// However once a handle has been assigned by the BIOS, the BIOS cannot re-assign that handle
/// number to another structure.
///
typedef UINT16 AMD_SMBIOS_HANDLE;

///
/// The Smbios structure header.
///
typedef struct {
  AMD_SMBIOS_TYPE    Type;
  UINT8              Length;
  AMD_SMBIOS_HANDLE  Handle;
} AMD_SMBIOS_STRUCTURE;

///
/// Text strings associated with a given SMBIOS structure are returned in the dmiStrucBuffer, appended directly after
/// the formatted portion of the structure. This method of returning string information eliminates the need for
/// application software to deal with pointers embedded in the SMBIOS structure. Each string is terminated with a null
/// (00h) BYTE and the set of strings is terminated with an additional null (00h) BYTE. When the formatted portion of
/// a SMBIOS structure references a string, it does so by specifying a non-zero string number within the structure's
/// string-set. For example, if a string field contains 02h, it references the second string following the formatted portion
/// of the SMBIOS structure. If a string field references no string, a null (0) is placed in that string field. If the
/// formatted portion of the structure contains string-reference fields and all the string fields are set to 0 (no string
/// references), the formatted section of the structure is followed by two null (00h) BYTES.
///
typedef UINT8 AMD_SMBIOS_TABLE_STRING;

///
/// Processor Information - Voltage. 
///
typedef struct {
  UINT8  ProcessorVoltageCapability5V        :1; 
  UINT8  ProcessorVoltageCapability3_3V      :1;  
  UINT8  ProcessorVoltageCapability2_9V      :1;  
  UINT8  ProcessorVoltageCapabilityReserved  :1; ///< Bit 3, must be zero.
  UINT8  ProcessorVoltageReserved            :3; ///< Bits 4-6, must be zero.
  UINT8  ProcessorVoltageIndicateLegacy      :1;
} AMD_PROCESSOR_VOLTAGE;

///
/// Processor ID Field Description
///
typedef struct {
  UINT32  ProcessorSteppingId:4;
  UINT32  ProcessorModel:     4;
  UINT32  ProcessorFamily:    4;
  UINT32  ProcessorType:      2;
  UINT32  ProcessorReserved1: 2;
  UINT32  ProcessorXModel:    4;
  UINT32  ProcessorXFamily:   8;
  UINT32  ProcessorReserved2: 4;
} AMD_PROCESSOR_SIGNATURE;

typedef struct {
  UINT32  ProcessorFpu       :1;
  UINT32  ProcessorVme       :1;
  UINT32  ProcessorDe        :1;
  UINT32  ProcessorPse       :1;
  UINT32  ProcessorTsc       :1;
  UINT32  ProcessorMsr       :1;
  UINT32  ProcessorPae       :1;
  UINT32  ProcessorMce       :1;
  UINT32  ProcessorCx8       :1;
  UINT32  ProcessorApic      :1;
  UINT32  ProcessorReserved1 :1;
  UINT32  ProcessorSep       :1;
  UINT32  ProcessorMtrr      :1;
  UINT32  ProcessorPge       :1;
  UINT32  ProcessorMca       :1;
  UINT32  ProcessorCmov      :1;
  UINT32  ProcessorPat       :1;
  UINT32  ProcessorPse36     :1;
  UINT32  ProcessorPsn       :1;
  UINT32  ProcessorClfsh     :1;
  UINT32  ProcessorReserved2 :1;
  UINT32  ProcessorDs        :1;
  UINT32  ProcessorAcpi      :1;
  UINT32  ProcessorMmx       :1;
  UINT32  ProcessorFxsr      :1;
  UINT32  ProcessorSse       :1;
  UINT32  ProcessorSse2      :1;
  UINT32  ProcessorSs        :1;
  UINT32  ProcessorReserved3 :1;
  UINT32  ProcessorTm        :1;
  UINT32  ProcessorReserved4 :2;
} AMD_PROCESSOR_FEATURE_FLAGS;

typedef struct {
  AMD_PROCESSOR_SIGNATURE     Signature;
  AMD_PROCESSOR_FEATURE_FLAGS FeatureFlags;
} AMD_PROCESSOR_ID_DATA;

///
/// Processor Information (Type 4).
///
/// The information in this structure defines the attributes of a single processor; 
/// a separate structure instance is provided for each system processor socket/slot. 
/// For example, a system with an IntelDX2 processor would have a single 
/// structure instance, while a system with an IntelSX2 processor would have a structure
/// to describe the main CPU, and a second structure to describe the 80487 co-processor. 
///
typedef struct { 
  AMD_SMBIOS_STRUCTURE      Hdr;
  AMD_SMBIOS_TABLE_STRING   Socket;
  UINT8                     ProcessorType;
  UINT8                     ProcessorFamily;
  AMD_SMBIOS_TABLE_STRING   ProcessorManufacture;
  AMD_PROCESSOR_ID_DATA     ProcessorId;
  AMD_SMBIOS_TABLE_STRING   ProcessorVersion;
  AMD_PROCESSOR_VOLTAGE     Voltage;
  UINT16                    ExternalClock;
  UINT16                    MaxSpeed;
  UINT16                    CurrentSpeed;
  UINT8                     Status;
  UINT8                     ProcessorUpgrade;
  UINT16                    L1CacheHandle;
  UINT16                    L2CacheHandle;
  UINT16                    L3CacheHandle;
  AMD_SMBIOS_TABLE_STRING   SerialNumber;
  AMD_SMBIOS_TABLE_STRING   AssetTag;
  AMD_SMBIOS_TABLE_STRING   PartNumber;
  //
  // Add for smbios 2.5
  //
  UINT8                     CoreCount;
  UINT8                     EnabledCoreCount;
  UINT8                     ThreadCount;
  UINT16                    ProcessorCharacteristics;
  //
  // Add for smbios 2.6
  //
  UINT16                    ProcessorFamily2;
  //
  // Add for smbios 3.0
  //
  UINT16                    CoreCount2;
  UINT16                    EnabledCoreCount2;
  UINT16                    ThreadCount2;
} AMD_SMBIOS_TABLE_TYPE4;

///
/// Cache Information - SRAM Type.
///
typedef struct {
  UINT16  Other         :1;
  UINT16  Unknown       :1;
  UINT16  NonBurst      :1;
  UINT16  Burst         :1;
  UINT16  PipelineBurst :1;
  UINT16  Synchronous   :1;
  UINT16  Asynchronous  :1;
  UINT16  Reserved      :9;
} AMD_CACHE_SRAM_TYPE_DATA;

///
/// Cache Information (Type 7).
///
/// The information in this structure defines the attributes of CPU cache device in the system. 
/// One structure is specified for each such device, whether the device is internal to
/// or external to the CPU module.  Cache modules can be associated with a processor structure
/// in one or two ways, depending on the SMBIOS version.
///
typedef struct {
  AMD_SMBIOS_STRUCTURE      Hdr;
  AMD_SMBIOS_TABLE_STRING   SocketDesignation;
  UINT16                    CacheConfiguration;
  UINT16                    MaximumCacheSize;
  UINT16                    InstalledSize;
  AMD_CACHE_SRAM_TYPE_DATA  SupportedSRAMType;
  AMD_CACHE_SRAM_TYPE_DATA  CurrentSRAMType;
  UINT8                     CacheSpeed;
  UINT8                     ErrorCorrectionType;
  UINT8                     SystemCacheType;
  UINT8                     Associativity;
  //
  // Add for smbios 3.1.0
  //
  UINT32                    MaximumCacheSize2;
  UINT32                    InstalledSize2;
} AMD_SMBIOS_TABLE_TYPE7;

///
/// Physical Memory Array - Location.
///
typedef enum {
  AmdMemoryArrayLocationOther                 = 0x01,
  AmdMemoryArrayLocationUnknown               = 0x02,
  AmdMemoryArrayLocationSystemBoard           = 0x03,
  AmdMemoryArrayLocationIsaAddonCard          = 0x04,
  AmdMemoryArrayLocationEisaAddonCard         = 0x05,
  AmdMemoryArrayLocationPciAddonCard          = 0x06,
  AmdMemoryArrayLocationMcaAddonCard          = 0x07,
  AmdMemoryArrayLocationPcmciaAddonCard       = 0x08,
  AmdMemoryArrayLocationProprietaryAddonCard  = 0x09,
  AmdMemoryArrayLocationNuBus                 = 0x0A,
  AmdMemoryArrayLocationPc98C20AddonCard      = 0xA0,
  AmdMemoryArrayLocationPc98C24AddonCard      = 0xA1,
  AmdMemoryArrayLocationPc98EAddonCard        = 0xA2,
  AmdMemoryArrayLocationPc98LocalBusAddonCard = 0xA3
} AMD_SMEMORY_ARRAY_LOCATION;

///
/// Physical Memory Array - Use.
///
typedef enum {
  AmdMemoryArrayUseOther                      = 0x01,
  AmdMemoryArrayUseUnknown                    = 0x02,
  AmdMemoryArrayUseSystemMemory               = 0x03,
  AmdMemoryArrayUseVideoMemory                = 0x04,
  AmdMemoryArrayUseFlashMemory                = 0x05,
  AmdMemoryArrayUseNonVolatileRam             = 0x06,
  AmdMemoryArrayUseCacheMemory                = 0x07
} AMD_SMEMORY_ARRAY_USE;

///
/// Physical Memory Array - Error Correction Types. 
///
typedef enum {
  AmdMemoryErrorCorrectionOther               = 0x01,
  AmdMemoryErrorCorrectionUnknown             = 0x02,
  AmdMemoryErrorCorrectionNone                = 0x03,
  AmdMemoryErrorCorrectionParity              = 0x04,
  AmdMemoryErrorCorrectionSingleBitEcc        = 0x05,
  AmdMemoryErrorCorrectionMultiBitEcc         = 0x06,
  AmdMemoryErrorCorrectionCrc                 = 0x07
} AMD_SMEMORY_ERROR_CORRECTION;

///
/// Physical Memory Array (Type 16).
///
/// This structure describes a collection of memory devices that operate 
/// together to form a memory address space. 
///
typedef struct {
  AMD_SMBIOS_STRUCTURE      Hdr;
  UINT8                     Location;                       ///< The enumeration value from AMD_MEMORY_ARRAY_LOCATION.
  UINT8                     Use;                            ///< The enumeration value from AMD_MEMORY_ARRAY_USE.
  UINT8                     MemoryErrorCorrection;          ///< The enumeration value from AMD_MEMORY_ERROR_CORRECTION.
  UINT32                    MaximumCapacity;
  UINT16                    MemoryErrorInformationHandle;
  UINT16                    NumberOfMemoryDevices;
  //
  // Add for smbios 2.7
  //
  UINT64                    ExtendedMaximumCapacity;
} AMD_SMBIOS_TABLE_TYPE16;

///
/// Memory Device - Form Factor.
///
typedef enum {
  AmdMemoryFormFactorOther                    = 0x01,
  AmdMemoryFormFactorUnknown                  = 0x02,
  AmdMemoryFormFactorSimm                     = 0x03,
  AmdMemoryFormFactorSip                      = 0x04,
  AmdMemoryFormFactorChip                     = 0x05,
  AmdMemoryFormFactorDip                      = 0x06,
  AmdMemoryFormFactorZip                      = 0x07,
  AmdMemoryFormFactorProprietaryCard          = 0x08,
  AmdMemoryFormFactorDimm                     = 0x09,
  AmdMemoryFormFactorTsop                     = 0x0A,
  AmdMemoryFormFactorRowOfChips               = 0x0B,
  AmdMemoryFormFactorRimm                     = 0x0C,
  AmdMemoryFormFactorSodimm                   = 0x0D,
  AmdMemoryFormFactorSrimm                    = 0x0E,
  AmdMemoryFormFactorFbDimm                   = 0x0F
} AMD_SMEMORY_FORM_FACTOR;

///
/// Memory Device - Type
///
typedef enum {
  AmdMemoryTypeOther                          = 0x01,
  AmdMemoryTypeUnknown                        = 0x02,
  AmdMemoryTypeDram                           = 0x03,
  AmdMemoryTypeEdram                          = 0x04,
  AmdMemoryTypeVram                           = 0x05,
  AmdMemoryTypeSram                           = 0x06,
  AmdMemoryTypeRam                            = 0x07,
  AmdMemoryTypeRom                            = 0x08,
  AmdMemoryTypeFlash                          = 0x09,
  AmdMemoryTypeEeprom                         = 0x0A,
  AmdMemoryTypeFeprom                         = 0x0B,
  AmdMemoryTypeEprom                          = 0x0C,
  AmdMemoryTypeCdram                          = 0x0D,
  AmdMemoryType3Dram                          = 0x0E,
  AmdMemoryTypeSdram                          = 0x0F,
  AmdMemoryTypeSgram                          = 0x10,
  AmdMemoryTypeRdram                          = 0x11,
  AmdMemoryTypeDdr                            = 0x12,
  AmdMemoryTypeDdr2                           = 0x13,
  AmdMemoryTypeDdr2FbDimm                     = 0x14,
  AmdMemoryTypeDdr3                           = 0x18,
  AmdMemoryTypeFbd2                           = 0x19,
  AmdMemoryTypeDdr4                           = 0x1A,
  AmdMemoryTypeLpddr                          = 0x1B,
  AmdMemoryTypeLpddr2                         = 0x1C,
  AmdMemoryTypeLpddr3                         = 0x1D,
  AmdMemoryTypeLpddr4                         = 0x1E
} AMD_MEMORY_DEVICE_TYPE;

typedef struct {
  UINT16    Reserved        :1;
  UINT16    Other           :1;
  UINT16    Unknown         :1;
  UINT16    FastPaged       :1;
  UINT16    StaticColumn    :1;
  UINT16    PseudoStatic    :1;
  UINT16    Rambus          :1;
  UINT16    Synchronous     :1;
  UINT16    Cmos            :1;
  UINT16    Edo             :1;
  UINT16    WindowDram      :1;
  UINT16    CacheDram       :1;
  UINT16    Nonvolatile     :1;
  UINT16    Registered      :1;
  UINT16    Unbuffered      :1;
  UINT16    LrDimm          :1;
} AMD_MEMORY_DEVICE_TYPE_DETAIL;

///
/// Memory Device (Type 17).
///
/// This structure describes a single memory device that is part of 
/// a larger Physical Memory Array (Type 16).
/// Note:  If a system includes memory-device sockets, the SMBIOS implementation 
/// includes a Memory Device structure instance for each slot, whether or not the 
/// socket is currently populated.
///
typedef struct {
  AMD_SMBIOS_STRUCTURE          Hdr;
  UINT16                        MemoryArrayHandle;
  UINT16                        MemoryErrorInformationHandle;
  UINT16                        TotalWidth;
  UINT16                        DataWidth;
  UINT16                        Size;
  UINT8                         FormFactor;                     ///< The enumeration value from AMD_MEMORY_FORM_FACTOR.
  UINT8                         DeviceSet;
  AMD_SMBIOS_TABLE_STRING       DeviceLocator;
  AMD_SMBIOS_TABLE_STRING       BankLocator;
  UINT8                         MemoryType;                     ///< The enumeration value from AMD_MEMORY_DEVICE_TYPE.
  AMD_MEMORY_DEVICE_TYPE_DETAIL TypeDetail;
  UINT16                        Speed;
  AMD_SMBIOS_TABLE_STRING       Manufacturer;
  AMD_SMBIOS_TABLE_STRING       SerialNumber;
  AMD_SMBIOS_TABLE_STRING       AssetTag;
  AMD_SMBIOS_TABLE_STRING       PartNumber;
  //
  // Add for smbios 2.6
  //  
  UINT8                     Attributes;
  //
  // Add for smbios 2.7
  //
  UINT32                    ExtendedSize;
  UINT16                    ConfiguredMemoryClockSpeed;
  //
  // Add for smbios 2.8.0
  //
  UINT16                    MinimumVoltage;
  UINT16                    MaximumVoltage;
  UINT16                    ConfiguredVoltage;
} AMD_SMBIOS_TABLE_TYPE17;

///
/// 32-bit Memory Error Information - Error Type. 
///
typedef enum {  
  AmdMemoryErrorOther             = 0x01,
  AmdMemoryErrorUnknown           = 0x02,
  AmdMemoryErrorOk                = 0x03,
  AmdMemoryErrorBadRead           = 0x04,
  AmdMemoryErrorParity            = 0x05,
  AmdMemoryErrorSigleBit          = 0x06,
  AmdMemoryErrorDoubleBit         = 0x07,
  AmdMemoryErrorMultiBit          = 0x08,
  AmdMemoryErrorNibble            = 0x09,
  AmdMemoryErrorChecksum          = 0x0A,
  AmdMemoryErrorCrc               = 0x0B,
  AmdMemoryErrorCorrectSingleBit  = 0x0C,
  AmdMemoryErrorCorrected         = 0x0D,
  AmdMemoryErrorUnCorrectable     = 0x0E
} AMD_MEMORY_ERROR_TYPE;

///
/// 32-bit Memory Error Information - Error Granularity. 
///
typedef enum {  
  AmdMemoryGranularityOther               = 0x01,
  AmdMemoryGranularityOtherUnknown        = 0x02,
  AmdMemoryGranularityDeviceLevel         = 0x03,
  AmdMemoryGranularityMemPartitionLevel   = 0x04
} AMD_MEMORY_ERROR_GRANULARITY;

///
/// 32-bit Memory Error Information - Error Operation. 
///
typedef enum {  
  AmdMemoryErrorOperationOther            = 0x01,
  AmdMemoryErrorOperationUnknown          = 0x02,
  AmdMemoryErrorOperationRead             = 0x03,
  AmdMemoryErrorOperationWrite            = 0x04,
  AmdMemoryErrorOperationPartialWrite     = 0x05
} AMD_MEMORY_ERROR_OPERATION;

///
/// 32-bit Memory Error Information (Type 18).
/// 
/// This structure identifies the specifics of an error that might be detected 
/// within a Physical Memory Array.
///
typedef struct {
  AMD_SMBIOS_STRUCTURE      Hdr;
  UINT8                     ErrorType;                  ///< The enumeration value from AMD_MEMORY_ERROR_TYPE.
  UINT8                     ErrorGranularity;           ///< The enumeration value from AMD_MEMORY_ERROR_GRANULARITY.
  UINT8                     ErrorOperation;             ///< The enumeration value from AMD_MEMORY_ERROR_OPERATION.
  UINT32                    VendorSyndrome;
  UINT32                    MemoryArrayErrorAddress;
  UINT32                    DeviceErrorAddress;
  UINT32                    ErrorResolution;
} AMD_SMBIOS_TABLE_TYPE18;

///
/// Memory Array Mapped Address (Type 19).
///
/// This structure provides the address mapping for a Physical Memory Array.  
/// One structure is present for each contiguous address range described.
///
typedef struct {
  AMD_SMBIOS_STRUCTURE  Hdr;
  UINT32                StartingAddress;
  UINT32                EndingAddress;
  UINT16                MemoryArrayHandle;
  UINT8                 PartitionWidth;
  //
  // Add for smbios 2.7
  //
  UINT64                ExtendedStartingAddress;
  UINT64                ExtendedEndingAddress;
} AMD_SMBIOS_TABLE_TYPE19;

///
/// Memory Device Mapped Address (Type 20).
///
/// This structure maps memory address space usually to a device-level granularity.  
/// One structure is present for each contiguous address range described. 
///
typedef struct {
  AMD_SMBIOS_STRUCTURE  Hdr;
  UINT32                StartingAddress;
  UINT32                EndingAddress;
  UINT16                MemoryDeviceHandle;
  UINT16                MemoryArrayMappedAddressHandle;
  UINT8                 PartitionRowPosition;
  UINT8                 InterleavePosition;
  UINT8                 InterleavedDataDepth;
  //
  // Add for smbios 2.7
  //
  UINT64                ExtendedStartingAddress;
  UINT64                ExtendedEndingAddress;
} AMD_SMBIOS_TABLE_TYPE20;

#pragma pack (pop)
#endif // _AMD_SMBIOS_H_


