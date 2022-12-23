/* $NoKeywords:$ */
/**
 * @file
 *
 * Memory DMI structures and definitions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
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
 **/


#ifndef _MEM_DMI_H_
#define _MEM_DMI_H_

#include <AGESA.h>

#define MAX_DIMMS_PER_SOCKET          16
#define MEMORY_CAPACITY_SIZE_KB_4GB   0x00400000
#define MEMORY_CAPACITY_SIZE_KB_8GB   0x00800000
#define MEMORY_CAPACITY_SIZE_KB_16GB  0x04000000
#define MEMORY_CAPACITY_SIZE_KB_32GB  0x02000000
#define MEMORY_CAPACITY_SIZE_KB_2TB   0x80000000

#define MAX_T19_REGION_SUPPORTED      3                 ///< Max SMBIOS T19 Memory Region count

/// DMI Type 16 offset 04h - Location
typedef enum {
  OtherLocation = 0x01,                                 ///< Assign 01 to Other
  UnknownLocation,                                      ///< Assign 02 to Unknown
  SystemboardOrMotherboard,                             ///< Assign 03 to systemboard or motherboard
  IsaAddonCard,                                         ///< Assign 04 to ISA add-on card
  EisaAddonCard,                                        ///< Assign 05 to EISA add-on card
  PciAddonCard,                                         ///< Assign 06 to PCI add-on card
  McaAddonCard,                                         ///< Assign 07 to MCA add-on card
  PcmciaAddonCard,                                      ///< Assign 08 to PCMCIA add-on card
  ProprietaryAddonCard,                                 ///< Assign 09 to proprietary add-on card
  NuBus,                                                ///< Assign 0A to NuBus
  Pc98C20AddonCard,                                     ///< Assign 0A0 to PC-98/C20 add-on card
  Pc98C24AddonCard,                                     ///< Assign 0A1 to PC-98/C24 add-on card
  Pc98EAddoncard,                                       ///< Assign 0A2 to PC-98/E add-on card
  Pc98LocalBusAddonCard                                 ///< Assign 0A3 to PC-98/Local bus add-on card
} DMI_T16_LOCATION;

/// DMI Type 16 offset 05h - Memory Error Correction
typedef enum {
  OtherUse = 0x01,                                      ///< Assign 01 to Other
  UnknownUse,                                           ///< Assign 02 to Unknown
  SystemMemory,                                         ///< Assign 03 to system memory
  VideoMemory,                                          ///< Assign 04 to video memory
  FlashMemory,                                          ///< Assign 05 to flash memory
  NonvolatileRam,                                       ///< Assign 06 to non-volatile RAM
  CacheMemory                                           ///< Assign 07 to cache memory
} DMI_T16_USE;

/// DMI Type 16 offset 07h - Maximum Capacity
typedef enum {
  Dmi16OtherErrCorrection = 0x01,                       ///< Assign 01 to Other
  Dmi16UnknownErrCorrection,                            ///< Assign 02 to Unknown
  Dmi16NoneErrCorrection,                               ///< Assign 03 to None
  Dmi16Parity,                                          ///< Assign 04 to parity
  Dmi16SingleBitEcc,                                    ///< Assign 05 to Single-bit ECC
  Dmi16MultiBitEcc,                                     ///< Assign 06 to Multi-bit ECC
  Dmi16Crc                                              ///< Assign 07 to CRC
} DMI_T16_ERROR_CORRECTION;

/// DMI Type 16 - Physical Memory Array
typedef struct {
  OUT DMI_T16_LOCATION          Location;               ///< The physical location of the Memory Array,
                                                        ///< whether on the system board or an add-in board.
  OUT DMI_T16_USE               Use;                    ///< Identifies the function for which the array
                                                        ///< is used.
  OUT DMI_T16_ERROR_CORRECTION  MemoryErrorCorrection;  ///< The primary hardware error correction or
                                                        ///< detection method supported by this memory array.
  OUT UINT16                    NumberOfMemoryDevices;  ///< The number of slots or sockets available
                                                        ///< for memory devices in this array.
} TYPE16_DMI_INFO;

/// DMI Type 17 offset 0Eh - Form Factor
typedef enum {
  OtherFormFactor = 0x01,                               ///< Assign 01 to Other
  UnknowFormFactor,                                     ///< Assign 02 to Unknown
  SimmFormFactor,                                       ///< Assign 03 to SIMM
  SipFormFactor,                                        ///< Assign 04 to SIP
  ChipFormFactor,                                       ///< Assign 05 to Chip
  DipFormFactor,                                        ///< Assign 06 to DIP
  ZipFormFactor,                                        ///< Assign 07 to ZIP
  ProprietaryCardFormFactor,                            ///< Assign 08 to Proprietary Card
  DimmFormFactorFormFactor,                             ///< Assign 09 to DIMM
  TsopFormFactor,                                       ///< Assign 10 to TSOP
  RowOfChipsFormFactor,                                 ///< Assign 11 to Row of chips
  RimmFormFactor,                                       ///< Assign 12 to RIMM
  SodimmFormFactor,                                     ///< Assign 13 to SODIMM
  SrimmFormFactor,                                      ///< Assign 14 to SRIMM
  FbDimmFormFactor                                      ///< Assign 15 to FB-DIMM
} DMI_T17_FORM_FACTOR;

/// DMI Type 17 offset 12h - Memory Type
typedef enum {
  OtherMemType = 0x01,                                  ///< Assign 01 to Other
  UnknownMemType,                                       ///< Assign 02 to Unknown
  DramMemType,                                          ///< Assign 03 to DRAM
  EdramMemType,                                         ///< Assign 04 to EDRAM
  VramMemType,                                          ///< Assign 05 to VRAM
  SramMemType,                                          ///< Assign 06 to SRAM
  RamMemType,                                           ///< Assign 07 to RAM
  RomMemType,                                           ///< Assign 08 to ROM
  FlashMemType,                                         ///< Assign 09 to Flash
  EepromMemType,                                        ///< Assign 10 to EEPROM
  FepromMemType,                                        ///< Assign 11 to FEPROM
  EpromMemType,                                         ///< Assign 12 to EPROM
  CdramMemType,                                         ///< Assign 13 to CDRAM
  ThreeDramMemType,                                     ///< Assign 14 to 3DRAM
  SdramMemType,                                         ///< Assign 15 to SDRAM
  SgramMemType,                                         ///< Assign 16 to SGRAM
  RdramMemType,                                         ///< Assign 17 to RDRAM
  DdrMemType,                                           ///< Assign 18 to DDR
  Ddr2MemType,                                          ///< Assign 19 to DDR2
  Ddr2FbdimmMemType,                                    ///< Assign 20 to DDR2 FB-DIMM
  Ddr3MemType = 0x18,                                   ///< Assign 24 to DDR3
  Fbd2MemType,                                          ///< Assign 25 to FBD2
  Ddr4MemType,                                          ///< Assign 26 to DDR4
  LpDdrMemType,                                         ///< Assign 27 to LPDDR
  LpDdr2MemType,                                        ///< Assign 28 to LPDDR2
  LpDdr3MemType,                                        ///< Assign 29 to LPDDR3
  LpDdr4MemType,                                        ///< Assign 30 to LPDDR4
} DMI_T17_MEMORY_TYPE;

/// DMI Type 17 offset 13h - Type Detail
typedef struct {
  OUT UINT16                    Reserved1:1;            ///< Reserved
  OUT UINT16                    Other:1;                ///< Other
  OUT UINT16                    Unknown:1;              ///< Unknown
  OUT UINT16                    FastPaged:1;            ///< Fast-Paged
  OUT UINT16                    StaticColumn:1;         ///< Static column
  OUT UINT16                    PseudoStatic:1;         ///< Pseudo-static
  OUT UINT16                    Rambus:1;               ///< RAMBUS
  OUT UINT16                    Synchronous:1;          ///< Synchronous
  OUT UINT16                    Cmos:1;                 ///< CMOS
  OUT UINT16                    Edo:1;                  ///< EDO
  OUT UINT16                    WindowDram:1;           ///< Window DRAM
  OUT UINT16                    CacheDram:1;            ///< Cache Dram
  OUT UINT16                    NonVolatile:1;          ///< Non-volatile
  OUT UINT16                    Registered:1;           ///< Registered (Buffered)
  OUT UINT16                    Unbuffered:1;           ///< Unbuffered (Unregistered)
  OUT UINT16                    LRDIMM:1;               ///< LRDIMM
} DMI_T17_TYPE_DETAIL;

/// DMI Type 17 - Memory Device
typedef struct {
  OUT UINT16                    Handle;                 ///< The temporary handle, or instance number, associated with the structure
  OUT UINT16                    TotalWidth;             ///< Total Width, in bits, of this memory device, including any check or error-correction bits.
  OUT UINT16                    DataWidth;              ///< Data Width, in bits, of this memory device.
  OUT UINT16                    MemorySize;             ///< The size of the memory device.
  OUT DMI_T17_FORM_FACTOR       FormFactor;             ///< The implementation form factor for this memory device.
  OUT UINT8                     DeviceSet;              ///< Identifies when the Memory Device is one of a set of
                                                        ///< Memory Devices that must be populated with all devices of
                                                        ///< the same type and size, and the set to which this device belongs.
  OUT CHAR8                     DeviceLocator[8];       ///< The string number of the string that identifies the physically labeled socket or board position where the memory device is located.
  OUT CHAR8                     BankLocator[13];        ///< The string number of the string that identifies the physically labeled bank where the memory device is located.
  OUT DMI_T17_MEMORY_TYPE       MemoryType;             ///< The type of memory used in this device.
  OUT DMI_T17_TYPE_DETAIL       TypeDetail;             ///< Additional detail on the memory device type
  OUT UINT16                    Speed;                  ///< Identifies the speed of the device, in megahertz (MHz).
  OUT UINT64                    ManufacturerIdCode;     ///< Manufacturer ID code.
  OUT CHAR8                     SerialNumber[9];        ///< Serial Number.
  OUT CHAR8                     PartNumber[21];         ///< Part Number.
  OUT UINT8                     Attributes;             ///< Bits 7-4: Reserved, Bits 3-0: rank.
  OUT UINT32                    ExtSize;                ///< Extended Size.
  OUT UINT16                    ConfigSpeed;            ///< Configured memory clock speed
  OUT UINT16                    MinimumVoltage;         ///< Minimum operating voltage for this device, in millivolts
  OUT UINT16                    MaximumVoltage;         ///< Maximum operating voltage for this device, in millivolts
  OUT UINT16                    ConfiguredVoltage;      ///< Configured voltage for this device, in millivolts
} TYPE17_DMI_INFO;

/// Memory DMI Type 17 - for memory use
typedef struct {
  OUT UINT8                     Socket:3;               ///< Socket ID
  OUT UINT8                     Channel:2;              ///< Channel ID
  OUT UINT8                     Dimm:2;                 ///< DIMM ID
  OUT UINT8                     DimmPresent:1;          ///< Dimm Present
  OUT UINT16                    Handle;                 ///< The temporary handle, or instance number, associated with the structure
  OUT UINT16                    TotalWidth;             ///< Total Width, in bits, of this memory device, including any check or error-correction bits.
  OUT UINT16                    DataWidth;              ///< Data Width, in bits, of this memory device.
  OUT UINT16                    MemorySize;             ///< The size of the memory device.
  OUT DMI_T17_FORM_FACTOR       FormFactor;             ///< The implementation form factor for this memory device.
  OUT UINT8                     DeviceLocator;          ///< The string number of the string that identifies the physically labeled socket or board position where the memory device is located.
  OUT UINT8                     BankLocator;            ///< The string number of the string that identifies the physically labeled bank where the memory device is located.
  OUT UINT16                    Speed;                  ///< Identifies the speed of the device, in megahertz (MHz).
  OUT UINT64                    ManufacturerIdCode;     ///< Manufacturer ID code.
  OUT UINT8                     SerialNumber[9];        ///< Serial Number.
  OUT UINT8                     PartNumber[21];         ///< Part Number.
  OUT UINT8                     Attributes;             ///< Bits 7-4: Reserved, Bits 3-0: rank.
  OUT UINT32                    ExtSize;                ///< Extended Size.
  OUT UINT16                    ConfigSpeed;            ///< Configured memory clock speed
  OUT UINT16                    MinimumVoltage;         ///< Minimum operating voltage for this device, in millivolts
  OUT UINT16                    MaximumVoltage;         ///< Maximum operating voltage for this device, in millivolts
  OUT UINT16                    ConfiguredVoltage;      ///< Configured voltage for this device, in millivolts
} MEM_DMI_PHYSICAL_DIMM_INFO;

/// Memory DMI Type 20 - for memory use
typedef struct {
  OUT UINT8                     Socket:3;               ///< Socket ID
  OUT UINT8                     Channel:2;              ///< Channel ID
  OUT UINT8                     Dimm:2;                 ///< DIMM ID
  OUT UINT8                     DimmPresent:1;          ///< Dimm Present
  OUT BOOLEAN                   Interleaved;            ///< Interleaved;
  OUT UINT32                    StartingAddr;           ///< The physical address, in kilobytes, of a range
                                                        ///< of memory mapped to the referenced Memory Device.
  OUT UINT32                    EndingAddr;             ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  OUT UINT16                    MemoryDeviceHandle;     ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  OUT UINT64                    ExtStartingAddr;        ///< The physical address, in bytes, of a range of
                                                        ///< memory mapped to the referenced Memory Device.
  OUT UINT64                    ExtEndingAddr;          ///< The physical ending address, in bytes, of the last of
                                                        ///< a range of addresses mapped to the referenced Memory Device.
} MEM_DMI_LOGICAL_DIMM_INFO;

/// DMI Type 19 - Memory Array Mapped Address
typedef struct {
  OUT UINT32                    StartingAddr;           ///< The physical address, in kilobytes,
                                                        ///< of a range of memory mapped to the
                                                        ///< specified physical memory array.
  OUT UINT32                    EndingAddr;             ///< The physical ending address of the
                                                        ///< last kilobyte of a range of addresses
                                                        ///< mapped to the specified physical memory array.
  OUT UINT16                    MemoryArrayHandle;      ///< The handle, or instance number, associated
                                                        ///< with the physical memory array to which this
                                                        ///< address range is mapped.
  OUT UINT8                     PartitionWidth;         ///< Identifies the number of memory devices that
                                                        ///< form a single row of memory for the address
                                                        ///< partition defined by this structure.
  OUT UINT64                    ExtStartingAddr;        ///< The physical address, in bytes, of a range of
                                                        ///< memory mapped to the specified Physical Memory Array.
  OUT UINT64                    ExtEndingAddr;          ///< The physical address, in bytes, of a range of
                                                        ///< memory mapped to the specified Physical Memory Array.
} TYPE19_DMI_INFO;

///DMI Type 20 - Memory Device Mapped Address
typedef struct {
  OUT UINT32                    StartingAddr;           ///< The physical address, in kilobytes, of a range
                                                        ///< of memory mapped to the referenced Memory Device.
  OUT UINT32                    EndingAddr;             ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  OUT UINT16                    MemoryDeviceHandle;     ///< The handle, or instance number, associated with
                                                        ///< the Memory Device structure to which this address
                                                        ///< range is mapped.
  OUT UINT16                    MemoryArrayMappedAddressHandle; ///< The handle, or instance number, associated
                                                        ///< with the Memory Array Mapped Address structure to
                                                        ///< which this device address range is mapped.
  OUT UINT8                     PartitionRowPosition;   ///< Identifies the position of the referenced Memory
                                                        ///< Device in a row of the address partition.
  OUT UINT8                     InterleavePosition;     ///< The position of the referenced Memory Device in
                                                        ///< an interleave.
  OUT UINT8                     InterleavedDataDepth;   ///< The maximum number of consecutive rows from the
                                                        ///< referenced Memory Device that are accessed in a
                                                        ///< single interleaved transfer.
  OUT UINT64                    ExtStartingAddr;        ///< The physical address, in bytes, of a range of
                                                        ///< memory mapped to the referenced Memory Device.
  OUT UINT64                    ExtEndingAddr;          ///< The physical ending address, in bytes, of the last of
                                                        ///< a range of addresses mapped to the referenced Memory Device.
} TYPE20_DMI_INFO;

/// Collection of pointers to the DMI records
typedef struct {
  OUT TYPE16_DMI_INFO           T16;                          ///< Type 16 struc
  OUT TYPE17_DMI_INFO           T17[MAX_SOCKETS_SUPPORTED][MAX_CHANNELS_PER_SOCKET][MAX_DIMMS_PER_CHANNEL]; ///< Type 17 struc
  OUT TYPE19_DMI_INFO           T19[MAX_T19_REGION_SUPPORTED];                                              ///< Type 19 struc
  OUT TYPE20_DMI_INFO           T20[MAX_SOCKETS_SUPPORTED][MAX_CHANNELS_PER_SOCKET][MAX_DIMMS_PER_CHANNEL]; ///< Type 20 struc
} DMI_INFO;

AGESA_STATUS
MemConstructDmiInfo (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN OUT   DMI_INFO              **DmiTable
  );

#endif
