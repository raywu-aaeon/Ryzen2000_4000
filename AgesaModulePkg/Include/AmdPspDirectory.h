/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Directory definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 317842 $   @e \$Date: 2015-04-29 15:06:52 +0800 (Wed, 29 Apr 2015) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 **/

#ifndef _AMD_PSP_DIR_H_
#define _AMD_PSP_DIR_H_

#pragma pack (push, 1)
#define PSP_DIRECTORY_HEADER_SIGNATURE  0x50535024ul   ///< $PSP
#define PSP_LV2_DIRECTORY_HEADER_SIGNATURE 0x324C5024ul   ///< $PL2
/// Define structure for PSP directory
typedef struct {
  UINT32  PspCookie;      ///< "$PSP"
  UINT32  Checksum;       ///< 32 bit CRC of header items below and the entire table
  UINT32  TotalEntries;   ///< Number of PSP Entries
  UINT32  Reserved;       ///< Unused
} PSP_DIRECTORY_HEADER;

typedef struct {
  UINT32 Type:8 ;          ///< Type of PSP Directory entry
  UINT32 SubProgram:8;       ///< Specify the SubProgram
  UINT32 RomId:2;            ///< Specify the ROM ID
  UINT32 Reserved:14;        ///< Reserved
} PSP_DIRECTORY_ENTRY_TYPE_FIELD;

typedef union {
  PSP_DIRECTORY_ENTRY_TYPE_FIELD Field; // Definition of each filed
  UINT32                         Value; // Group it as 32bits Int
} PSP_DIRECTORY_ENTRY_TYPE;

/// define various enum type for PSP entry type
enum _PSP_DIRECTORY_ENTRY_TYPE {
  AMD_PUBLIC_KEY                  = 0x00,           ///< PSP entry pointer to AMD public key
  PSP_FW_BOOT_LOADER              = 0x01,           ///< PSP entry points to PSP boot loader in SPI space
  PSP_FW_TRUSTED_OS               = 0x02,           ///< PSP entry points to PSP Firmware region in SPI space
  PSP_FW_RECOVERY_BOOT_LOADER     = 0x03,           ///< PSP entry point to PSP recovery region.
  PSP_NV_DATA                     = 0x04,           ///< PSP entry points to PSP data region in SPI space
  BIOS_PUBLIC_KEY_V1              = 0x05,           ///< PSP entry points to BIOS public key stored in SPI space
  BIOS_RTM_FIRMWARE_V1            = 0x06,           ///< PSP entry points to BIOS RTM code (PEI volume) in SPI space
  BIOS_RTM_SIGNATURE_V1           = 0x07,           ///< PSP entry points to signed BIOS RTM hash stored  in SPI space
  SMU_OFFCHIP_FW                  = 0x08,           ///< PSP entry points to SMU image
  AMD_SEC_DBG_PUBLIC_KEY          = 0x09,           ///< PSP entry pointer to Secure Unlock Public key
  OEM_PSP_FW_PUBLIC_KEY           = 0x0A,           ///< PSP entry pointer to an optional public part of the OEM PSP Firmware Signing Key Token
  AMD_SOFT_FUSE_CHAIN_01          = 0x0B,           ///< PSP entry pointer to 64bit PSP Soft Fuse Chain
  PSP_BOOT_TIME_TRUSTLETS         = 0x0C,           ///< PSP entry points to boot-loaded trustlet binaries
  PSP_BOOT_TIME_TRUSTLETS_KEY     = 0x0D,           ///< PSP entry points to key of the boot-loaded trustlet binaries
  PSP_AGESA_RESUME_FW             = 0x10,           ///< PSP Entry points to PSP Agesa-Resume-Firmware
  SMU_OFF_CHIP_FW_2               = 0x12,           ///< PSP entry points to secondary SMU image
  PSP_EARLY_UNLOCK_DEBUG_IMAGE    = 0x13,           ///< PSP entry points to PSP early secure unlock debug image
  PSP_S3_NV_DATA                  = 0x1A,           ///< PSP entry pointer to S3 Data Blob
  HW_IP_CONFIG_FILE               = 0x20,           ///< PSP entry points to HW IP configuration file
  WRAPPED_IKEK                    = 0x21,           ///< PSP entry points to Wrapped iKEK
  PSP_TOKEN_UNLOCK_DATA           = 0x22,           ///< PSP entry points to PSP token unlock data
  PSP_DIAG_BOOT_LOADER            = 0x23,           ///< PSP entry points to PSP Diag BL on non-secure part via fuse
  SECURE_GASKET_BINARY            = 0x24,           ///< PSP entry points to security gasket binary
  KVM_ENGINE_BINARY               = 0x29,           ///< PSP entry points to PSP KVM Engine binary
  TEE_WONE_NVRAM                  = 0x2C,           ///< PSP entry points to TEE_WONE_NVRAM binary
  AGESA_BOOT_LOADER_0             = 0x30,           ///< PSP entry points to PSP AGESA Binary 0
  AGESA_BOOT_LOADER_1             = 0x31,           ///< PSP entry points to PSP AGESA Binary 1
  AGESA_BOOT_LOADER_2             = 0x32,           ///< PSP entry points to PSP AGESA Binary 2
  AGESA_BOOT_LOADER_3             = 0x33,           ///< PSP entry points to PSP AGESA Binary 3
  AGESA_BOOT_LOADER_4             = 0x34,           ///< PSP entry points to PSP AGESA Binary 4
  AGESA_BOOT_LOADER_5             = 0x35,           ///< PSP entry points to PSP AGESA Binary 5
  AGESA_BOOT_LOADER_6             = 0x36,           ///< PSP entry points to PSP AGESA Binary 6
  AGESA_BOOT_LOADER_7             = 0x37,           ///< PSP entry points to PSP AGESA Binary 7
  PSP_VM_GUARD_DATA               = 0x38,           ///< PSP entry points to VM Guard data
  PSP_DIR_LV2                     = 0x40,           ///< PSP entry points to Level 2 PSP DIR
  PSP_REGION_A_DIR                = 0x48,           ///< PSP entry points to PSP DIR in Region A
  BIOS_REGION_DIR                 = 0x49,           ///< PSP entry points to BIOS DIR in Region A or B
  PSP_REGION_B_DIR                = 0x4A,           ///< PSP entry points to PSP DIR in Region B
  PSP_NVRAM                       = 0x54,           ///< PSP entry points to PSP NVRAM for RPMC
  AMD_SCS_BINARY                  = 0x5F,           ///< Software Configuration Settings Data Block
  PSP_BOOT_OEM_TRUSTLET           = 0x80,           ///< PSP entry points to boot-loaded OEM trustlet binary
  PSP_BOOT_OEM_TRUSTLET_KEY       = 0x81,           ///< PSP entry points to key of the boot-loaded OEM trustlet binary
};

/// Structure for PSP Entry
typedef struct {
  PSP_DIRECTORY_ENTRY_TYPE    Type;       ///< Type of PSP entry; 32 bit long
  UINT32                      Size;       ///< Size of PSP Entry in bytes
  UINT64                      Location;   ///< Location of PSP Entry (byte offset from start of SPI-ROM)
} PSP_DIRECTORY_ENTRY;

/// Structure for PSP directory
typedef struct {
  PSP_DIRECTORY_HEADER  Header;           ///< PSP directory header
  PSP_DIRECTORY_ENTRY   PspEntry[1];      ///< Array of PSP entries each pointing to a binary in SPI flash
                                          ///< The actual size of this array comes from the
                                          ///< header (PSP_DIRECTORY.Header.TotalEntries)
} PSP_DIRECTORY;

#pragma pack (pop)
#endif //_AMD_PSP_DIR_H_
