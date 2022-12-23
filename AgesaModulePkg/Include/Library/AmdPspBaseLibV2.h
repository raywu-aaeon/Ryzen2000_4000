/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 **/
/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Base Library
 *
 * Contains interface to the PSP library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
#ifndef _AMD_PSP_BASELIB_V2_H_
#define _AMD_PSP_BASELIB_V2_H_

#include <AMD.h>
#include <AmdPspDirectory.h>

#define PSP_MAILBOX_BASE            0x70    ///< Mailbox base offset on PCIe BAR
#define PSP_MAILBOX_STATUS_OFFSET   0x4     ///< Staus Offset
#define IS_ADDRESS_MODE_1(a) (((a) >> 62) == 1 ? TRUE : FALSE)  //relative to BIOS image base 0
#define IS_ADDRESS_MODE_2(a) (((a) >> 62) == 2 ? TRUE : FALSE)  //relative to current directory header
#define IS_ADDRESS_MODE_3(a) (((a) >> 62) == 3 ? TRUE : FALSE)  //relative to active image slot address (as of now, active image slot address is equal to PSP L2 base address)
#define IS_SPI_OFFSET(a) (((a) & 0xFF000000) != 0xFF000000 ? TRUE : FALSE)
#define MaxDirEntryNumber 64
#define MaxPspDirSize sizeof(PSP_DIRECTORY_HEADER) + (sizeof(BIOS_DIRECTORY_ENTRY) * MaxDirEntryNumber)

#define MP0PUBLIC0_SMN_ADDR    0x03800000
#define MP0_C2PMSG_28_SMN_ADDR (MP0PUBLIC0_SMN_ADDR + 0x10570)
#define MP0_C2PMSG_29_SMN_ADDR (MP0PUBLIC0_SMN_ADDR + 0x10574)
#define MP0_C2PMSG_30_SMN_ADDR (MP0PUBLIC0_SMN_ADDR + 0x10578)
#pragma pack (push, 1)

///
/// X86 to PSP Buffer which start mapping from C2PMSG_28
///
typedef volatile struct {
  UINT32                    Status:16;      ///< Set by the target to indicate the execution status of last command
  UINT32                    CommandId:8;    ///< Command ID set by host
  UINT32                    Reserved:6;     ///< Reserved
  UINT32                    Recovery:1;     ///< Set by the target to indicate that the host has to execute FW recovery sequence
  UINT32                    Ready:1;        ///< Set by the target to indicate the mailbox interface state.
} PSP_MBOX_V2_CMD_EXT;

typedef volatile union {
  IN  UINT32                 Value;               ///< Cmd register value
  IN  PSP_MBOX_V2_CMD_EXT    Field;                    ///< Extended Cmd register with field definition
} PSP_MBOX_V2_CMD;

typedef volatile struct {
  PSP_MBOX_V2_CMD           Cmd;
  UINT64                    Buffer;        ///< 64 bit Ponter to memory with additional parameter.
} PSP_MBOX_V2;

#define FIRMWARE_TABLE_SIGNATURE  0x55AA55AAul
/// Define the structure OEM signature table
typedef struct _FIRMWARE_ENTRY_TABLEV2 {
  UINT32  Signature;          ///< 0x00 Signature should be 0x55AA55AAul
  UINT32  ImcRomBase;         ///< 0x04 Base Address for Imc Firmware
  UINT32  GecRomBase;         ///< 0x08 Base Address for Gmc Firmware
  UINT32  XHCRomBase;         ///< 0x0C Base Address for XHCI Firmware
  UINT32  LegacyPspDirBase;   ///< 0x10 Base Address of PSP directory for legacy program (ML, BP, CZ, BR, ST)
  UINT32  PspDirBase;         ///< 0x14 Base Address for PSP directory
  UINT32  ZpBiosDirBase;      ///< 0x18 Base Address for ZP BIOS directory
  UINT32  RvBiosDirBase;      ///< 0x1C Base Address for RV BIOS directory
  UINT32  SspBiosDirBase;     ///< 0x20 Base Address for RV BIOS directory
  UINT32  Config;             ///< 0x24 reserved for EFS configuration
  UINT32  NewBiosDirBase;     ///< 0x28 Generic Base address for all program start from RN
  UINT32  PspDirBackupBase;   ///< 0x2C Backup PSP directory address for all programs starting from RMB
} FIRMWARE_ENTRY_TABLEV2;


/// Unified Boot BIOS Directory structure
enum _BIOS_DIRECTORY_ENTRY_TYPE {
  BIOS_PUBLIC_KEY               = 0x05,       ///< PSP entry points to BIOS public key stored in SPI space
  BIOS_RTM_SIGNATURE            = 0x07,       ///< PSP entry points to signed BIOS RTM hash stored  in SPI space
  BIOS_APCB_INFO                = 0x60,       ///< Agesa PSP Customization Block (APCB)
  BIOS_APOB_INFO                = 0x61,       ///< Agesa PSP Output Block (APOB) target location
  BIOS_FIRMWARE                 = 0x62,       ///< BIOS Firmware volumes
  APOB_NV_COPY                  = 0x63,       ///< APOB data copy on non-volatile storage which will used by ABL during S3 resume
  PMU_INSTRUCTION               = 0x64,       ///< Location field pointing to the instruction portion of PMU firmware
  PMU_DATA                      = 0x65,       ///< Location field pointing to the data portion of PMU firmware
  UCODE_PATCH                   = 0x66,       ///< Microcode patch
  CORE_MCEDATA                  = 0x67,       ///< Core MCE data
  BIOS_APCB_INFO_BACKUP         = 0x68,       ///< Backup Agesa PSP Customization Block (APCB)
  BIOS_DIR_LV2                  = 0x70,       ///< BIOS entry points to Level 2 BIOS DIR
};

/// Directory type
typedef enum _DIRECTORY_TYPE {
  DIR_TYPE_PSP_LV2               = 0,         ///< Level 2 PSP DIR
  DIR_TYPE_BIOS_LV2              = 1,         ///< Level 2 BIOS DIR
} DIRECTORY_TYPE;

/// Type attribute for BIOS Directory entry
typedef struct {
  UINT32 Type : 8 ;          ///< Type of BIOS entry
  UINT32 RegionType : 8;     ///< 0 Normal memory, 1 TA1 memory, 2 TA2 memor
  UINT32 BiosResetImage: 1;  ///< Set for SEC or EL3 fw, which will be authenticate by PSP FW known as HVB
  UINT32 Copy: 1;            ///< Copy: 1- copy BIOS image image from source to destination 0- Set region attribute based on <ReadOnly, Source, size> attributes
  UINT32 ReadOnly : 1;       ///< 1: Set region to read-only (applicable for ARM- TA1/TA2) 0: Set region to read/write
  UINT32 Compressed : 1;     ///< 1: Compresed
  UINT32 Instance : 4;       ///< Specify the Instance of an entry
  UINT32 SubProgram : 3;       ///< Specify the SubProgram
  UINT32 RomId:2;           ///< Specify the RomId
  UINT32 Reserved : 3;      ///< Reserve for future use
} TYPE_ATTRIB;


/// Structure for PSP Entry
typedef struct {
  TYPE_ATTRIB                 TypeAttrib;       ///< Type of PSP entry; 32 bit long
  UINT32                      Size;             ///< Size of PSP Entry in bytes
  UINT64                      Location;         ///< Location of PSP Entry (byte offset from start of SPI-ROM)
  UINT64                      Destination;      ///< Destination of PSP Entry copy to
} BIOS_DIRECTORY_ENTRY;

#define BIOS_DIRECTORY_HEADER_SIGNATURE 0x44484224ul   ///< $BHD BIOS Directory Signature
#define BIOS_LV2_DIRECTORY_HEADER_SIGNATURE 0x324C4224ul   ///< $BL2 BIOS Directory Lv2 Signature
/// Structure for BIOS directory
typedef struct {
  PSP_DIRECTORY_HEADER  Header;           ///< PSP directory header
  BIOS_DIRECTORY_ENTRY  BiosEntry[1];      ///< Array of PSP entries each pointing to a binary in SPI flash
                                          ///< The actual size of this array comes from the
                                          ///< header (PSP_DIRECTORY.Header.TotalEntries)
} BIOS_DIRECTORY;

/// Structure for PSP Combo directory
#define PSP_COMBO_DIRECTORY_COOKIE      0x50535032ul   ///< 2PSP PSP Combo Directory Signature
#define BIOS_COMBO_DIRECTORY_COOKIE     0x44484232ul     ///< "BHD2" BIOS Combo Directory Signature
typedef struct {
  UINT32  PspCookie;      ///< "2PSP"
  UINT32  Checksum;       ///< 32 bit CRC of header items below and the entire table
  UINT32  TotalEntries;   ///< Number of PSP Entries
  UINT32  LookUpMode;     ///< 0 - Dynamic look up through all entries, 1 - PSP/chip ID match.
  UINT8   Reserved[16];   ///< Reserved
} PSP_COMBO_DIRECTORY_HEADER;

/// Structure for PSP Combo directory entry
typedef struct {
  UINT32 IdSelect;        ///< 0 - Compare PSP ID, 1 - Compare chip family ID
  UINT32 Id;              ///< 32-bit Chip/PSP ID
  UINT64 PspDirTableAddr; ///< Point to PSP directory table (level 2)
} PSP_COMBO_DIRECTORY_ENTRY;

/**
 * @brief PSP/BIOS entry region with start address and size
 *
 */
typedef struct {
  UINT64 Address;
  UINT32 Size;
} ENTRY_REGION;

/// RECOVERY_REASON_VERSION
typedef enum {
  RECOVERY_REASON_VERSION_IGNORE = 0xFFFFFFFFul, //before RN
  RECOVERY_REASON_VERSION_1 = 1,   //RN, CZN
  RECOVERY_REASON_VERSION_2 = 2,   //Starting from VN
} RECOVERY_REASON_VERSION;

#define ZP_PSP_CHIP_ID   0xBC090000  ///< ZP Chip ID in combo structure
#define RV_PSP_CHIP_ID   0xBC0A0000  ///< RV Chip ID in combo structure
#define RV2_PSP_CHIP_ID  0xBC0A0100  ///< RV2 Chip ID in combo structure
#define SSP_PSP_CHIP_ID  0xBC0B0000  ///< SSP Chip ID in combo structure
#define MTS_PSP_CHIP_ID  0xBC0B0500  ///< MTS Chip ID in combo structure
#define RN_PSP_CHIP_ID   0xBC0C0000  ///< RN Chip ID in combo structure
#define VMR_PSP_CHIP_ID  0xBC0B0500  ///< VMR Chip ID in combo structure
#define GN_PSP_CHIP_ID   0xBC0B0D00  ///< GN Chip ID in combo structure
#define CZN_PSP_CHIP_ID  0xBC0C0140  ///< CZN Chip ID in combo structure
#define BA_PSP_CHIP_ID   0xBC0B0F00  ///< BA Chip ID in combo structure
#define MR_PSP_CHIP_ID   0xBC0B0800  ///< MR Chip ID in combo structure
#define VN_PSP_CHIP_ID   0xBC0B0800  ///< VN Chip ID in combo structure
#define RMB_PSP_CHIP_ID  0xBC0D0200  ///< RMB chip ID
#define RS_PSP_CHIP_ID   0XBC0D0111  ///< Stone chip id

typedef struct {
  PSP_COMBO_DIRECTORY_HEADER  Header;       ///< PSP Combo directory header
  PSP_COMBO_DIRECTORY_ENTRY ComboEntry[1];  ///<  Array of PSP combo entries each pointing to level 2 PSP Direcotry header
} PSP_COMBO_DIRECTORY;

// define PSB & HSTI status structure
typedef struct {
  UINT32 PsbTestStatus : 8 ;          ///< Set to the PSB Test result as one byte value, definition varies between program
  UINT32 PsbFusingReadiness : 1;      ///< 1 if the PSB fusing is allowed by a BIOS command, 0 otherwise
  UINT32 Reserved : 19;               ///< Set to zero
  UINT32 HstiState : 4;               ///< HstiState
} PSB_HSTI_STATUS_1;

typedef struct {
  UINT32 PlatformVendorId : 8 ;             ///< Platform Vendor ID is a 8-bit integer value assigned by AMD for each OEM/ODM.
  UINT32 PlatformModelId : 4;               ///< Platform Model ID is 4-bit integer value assigned to a platform by the OEM/ODM
  UINT32 BiosKeyRevisionId : 4;             ///< BIOS Key Revision ID is an integer value assigned by OEM/ODM.
  UINT32 RootKeySelect : 4;                 ///< Current selected AMD Root Key ID
  UINT32 Reserved1 : 4;                     ///< Set to zero
  UINT32 PlatformSecureBootEn : 1;          ///< Fuse bit that controls Platform Secure Boot Enable & Enforced mode
  UINT32 DisableBiosKeyAntiRollback : 1;    ///< Fuse bit that controls if BIOS Key Anti-Rollback feature is enabled or not
  UINT32 DisableAmdKeyUsage : 1;            ///< Fuse bit that controls of BIOS signed by an AMD Key (with vendor ID == 0) is permitted to boot on a CPU with non-zero Vendor ID
  UINT32 DisableSecureDebugUnlock : 1;      ///< Fuse bit that controls if Secure Debug Unlock feature is disabled permanently or not
  UINT32 CustomerKeyLock : 1;               ///< Fuse bit that controls of customer region fuse bits can be programmed or not.
  UINT32 Reserved2 : 3;                     ///< Set to zero
} PSB_STATUS_2;

#pragma pack (pop)
BOOLEAN
MapSpiDataToBuffer (
  IN       UINT32                      Address,
  IN OUT   VOID                        *Buffer,
  IN       UINT32                      Size
  );

/**
 * @brief translate entry offset to correct location based on address mode
 *
 * @param EntryLocation     the location of the entry before translation
 * @param DirectoryHdrAddr  directory header address
 * @param ImageSlotAddr     image slot address if applicable, if no image slot, leave it as 0
 * @return UINT64           return translated entry location
 */
UINT64
TranslateEntryLocation (
  IN       UINT64                      EntryLocation,
  IN       UINT64                      DirectoryHdrAddr,
  IN       UINT32                      ImageSlotAddr
  );

/**
  This function is to get the PSP level 2 directory buffer.

  @param[out]  pointer to PSP level 2 directory base

  @retval TRUE            Successfully get the valid PSP level 2 directory.
  @retval FALSE           Valid PSP level 2 directory is not found.

**/
BOOLEAN
GetPspLv2DirBaseV2 (
  IN       UINT64             PspLevel2BaseAddress,
  IN OUT   PSP_DIRECTORY     **PspLv2Dir
  );

BOOLEAN
GetPspDirBaseV2 (
  IN OUT   PSP_DIRECTORY     **PspDir
  );

/**
  This function is to get the BIOS level 2 directory buffer.

  @param[out]  pointer to BIOS level 2 directory base

  @retval TRUE            Successfully get the valid BIOS level 2 irectory.
  @retval FALSE           Valid BIOS level 2 directory is not found.

**/
BOOLEAN
GetBiosLv2DirBaseV2 (
  IN       UINT64             BiosLevel2BaseAddress,
  IN OUT   BIOS_DIRECTORY     **BiosLv2Dir
  );

BOOLEAN
GetBiosDirBaseV2 (
  IN OUT   BIOS_DIRECTORY     **BiosDir
  );

BOOLEAN
PSPEntryInfoV2 (
  IN      UINT32                      EntryType,
  IN OUT  UINT64                      *EntryAddress,
  IN      UINT32                      *EntrySize
  );

#define INSTANCE_IGNORED 0xFF
#define SUBPROGRAM_IGNORED 0xFF
BOOLEAN
BIOSEntryInfo (
  IN       UINT8                       EntryType,
  IN       UINT8                       EntryInstance,
  IN OUT   TYPE_ATTRIB                 *TypeAttrib,
  IN OUT   UINT64                      *EntryAddress,
  IN OUT   UINT32                      *EntrySize,
  IN OUT   UINT64                      *EntryDest
  );

/**
 * @brief Get the PSP level 2 Base Address
 *
 * @param PspLv2BaseAddress  the pointer to save the PSP level 2 base address
 * @return BOOLEAN           return TRUE if correct address found, otherise, return FALSE
 */
BOOLEAN
GetPspLv2BaseAddr (
  IN OUT UINT64                      *PspLv2BaseAddress
  );

/**
 * @brief Get the Base Addresses of both PSP level 2 and BIOS level 2
 *
 * @param PspLv2BaseAddress   the pointer to save the PSP level 2 base address
 * @param BiosLv2BaseAddress  the pointer to save the BIOS level 2 base address
 * @return BOOLEAN            return TRUE if correct addresses found, otherise, return FALSE
 */
BOOLEAN
GetPspBiosLv2BaseAddr (
  IN OUT UINT64                      *PspLv2BaseAddress,
  IN OUT UINT64                      *BiosLv2BaseAddress
  );

BOOLEAN
GetPspEntryScsBinaryV2 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  );

BOOLEAN
GetPspEntryPspNvDataV2 (
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  );

BOOLEAN
CheckPspDevicePresentV2 (
  VOID
  );

BOOLEAN
CheckPspPlatformSecureEnableV2 (
  VOID
  );

BOOLEAN
CheckPspRecoveryFlagV2 (
  VOID
  );

BOOLEAN
GetPspMmioBase (
  IN OUT   UINT32 *PspMmioBase
  );

BOOLEAN
GetPspMboxLocation (
  IN OUT   PSP_MBOX_V2 **PspMbox
  );

VOID
PspBarInitEarlyV2 (
  VOID
  );

typedef
BOOLEAN
(* FP_CONDITIONER) (
  IN       VOID        *Context
  );

BOOLEAN
PspLibTimeOutV2 (
  IN       UINT64              uSec,
  IN       FP_CONDITIONER      Conditioner,
  IN       VOID                *Context
  );

BOOLEAN
GetFtpmControlAreaV2 (
  IN OUT   VOID **FtpmControlArea
  );

VOID
SwitchPspMmioDecodeV2 (
  IN       BOOLEAN SwitchFlag,
  IN OUT   UINT32 *RegisterCopy
  );

VOID
AcquirePspSmiRegMutexV2 (
  VOID
  );

VOID
ReleasePspSmiRegMutexV2 (
  VOID
  );

BOOLEAN
GetPsbHstiStatus1 (
  PSB_HSTI_STATUS_1 *PsbHstiStatus1
  );

BOOLEAN
GetPsbStatus2 (
  PSB_STATUS_2 *PsbStatus2
  );

#endif // _AMD_LIB_H_

