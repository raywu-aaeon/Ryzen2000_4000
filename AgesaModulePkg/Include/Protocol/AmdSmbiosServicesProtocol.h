/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD SMBIOS Services Protocol prototype definition
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
#ifndef _AMD_SMBIOS_SERVICES_PROTOCOL_H_
#define _AMD_SMBIOS_SERVICES_PROTOCOL_H_

#include <MemDmi.h>

#pragma pack (push, 1)

// SMBIOS constant definition
#define CENTRAL_PROCESSOR               0x03
#define EXTERNAL_CLOCK_100MHZ           100
#define P_FAMILY_UNKNOWN                0x02
#define P_ENGINEERING_SAMPLE            0x00
#define P_ZEN_PROCESSOR_FAMILY          0x6B
#define P_CHARACTERISTICS               0xEC
#define P_CHARACTERISTICS_ZEN           0xFC
#define CACHE_CFG_L1                    0x180 // Write Back, Enabled, Not Socketed, L1
#define CACHE_CFG_L2                    0x181 // Write Back, Enabled, Not Socketed, L2
#define CACHE_CFG_L3                    0x182 // Write Back, Enabled, Not Socketed, L3
#define CACHE_CFG_NO_CACHE              0x360
#define SRAM_TYPE_UNKNOWN               0x02
#define SRAM_TYPE_PIPELINE_BURST        0x10
#define ERR_CORRECT_TYPE_UNKNOWN        0x02
#define ERR_CORRECT_TYPE_MULTI_BIT_ECC  0x06
#define CACHE_TYPE_UNKNOWN              0x05
#define CACHE_TYPE_INSTRUCTION          0x03
#define CACHE_TYPE_DATA                 0x04
#define CACHE_TYPE_UNIFIED              0x05
#define DMI_ASSOCIATIVE_OTHER           0x01
#define DMI_ASSOCIATIVE_UNKNOWN         0x02
#define DMI_ASSOCIATIVE_DIRECT_MAPPED   0x03
#define DMI_ASSOCIATIVE_2_WAY           0x04
#define DMI_ASSOCIATIVE_4_WAY           0x05
#define DMI_ASSOCIATIVE_FULLY           0x06
#define DMI_ASSOCIATIVE_8_WAY           0x07
#define DMI_ASSOCIATIVE_16_WAY          0x08
#define DMI_ASSOCIATIVE_12_WAY          0x09
#define DMI_ASSOCIATIVE_24_WAY          0x0A
#define DMI_ASSOCIATIVE_32_WAY          0x0B
#define DMI_ASSOCIATIVE_48_WAY          0x0C
#define DMI_ASSOCIATIVE_64_WAY          0x0D
#define DMI_ASSOCIATIVE_20_WAY          0x0E
#define SOCKET_POPULATED                0x40
#define CPU_STATUS_UNKNOWN              0x00
#define CPU_STATUS_ENABLED              0x01
#define P_UPGRADE_UNKNOWN               0x02
#define P_UPGRADE_NONE                  0x06
#define P_UPGRADE_AM4                   0x31
#define P_UPGRADE_SP3                   0x37
#define P_UPGRADE_SP3r2                 0x38

#define PROC_VERSION_LENGTH             48
#define PROC_MANU_LENGTH                29

/// Structure for processor stepping and features
typedef struct _AMD_PROCESSOR_ID {
  UINT32   EaxFamilyId;                            ///< Family, Model, Stepping Identifiers
  UINT32   EdxFeatureId;                           ///< EDX Feature Identifiers
} AMD_PROCESSOR_ID;

/// Structure for Core DMI information
typedef struct _AMD_CCX_CORE_DMI_INFO {
  UINT8    ProcessorType;                          ///< Processor type
  UINT16   ProcessorFamily;                        ///< Processor family
  AMD_PROCESSOR_ID   ProcessorID;                  ///< Raw processor identification data
  UINT8    Voltage;                                ///< Voltage
  UINT16   ExternalClock;                          ///< External clock
  UINT16   MaxSpeed;                               ///< Max speed
  UINT16   CurrentSpeed;                           ///< Current speed
  UINT8    Status;                                 ///< Status
  UINT8    ProcessorUpgrade;                       ///< Processor upgrade
  UINT16   CoreCount;                              ///< Core count
  UINT16   CoreEnabled;                            ///< Core enabled
  UINT16   ThreadCount;                            ///< Thread count
  UINT16   ProcessorCharacteristics;               ///< Processor characteristics
  CHAR8    ProcessorVersion[PROC_VERSION_LENGTH];  ///< Cpu version
  CHAR8    ProcessorManufacturer[PROC_MANU_LENGTH]; ///< Manufacturer
} AMD_CCX_CORE_DMI_INFO;

/// Types of cache levels
typedef enum {
  CpuL1Cache,                                     ///< L1 Cache
  CpuL2Cache,                                     ///< L2 Cache
  CpuL3Cache,                                     ///< L3 Cache
  CpuLmaxCache                                    ///< Not a cache type, used for limit checking
} AMD_CACHE_LEVEL;

/// Structure for Cache Level DMI information
typedef struct _AMD_CACHE_EACH_LEVEL_DMI_INFO {
  UINT16   CacheCfg;                               ///< Cache cfg
  UINT16   MaxCacheSize;                           ///< Max size
  UINT16   InstallSize;                            ///< Install size
  UINT16   SupportedSramType;                      ///< Supported Sram Type
  UINT16   CurrentSramType;                        ///< Current type
  UINT8    CacheSpeed;                             ///< Speed
  UINT8    ErrorCorrectionType;                    ///< ECC type
  UINT8    SystemCacheType;                        ///< Cache type
  UINT8    Associativity;                          ///< Associativity
  UINT32   MaxCacheSize2;                          ///< MaxCacheSize2
  UINT32   InstallSize2;                           ///< InstallSize2
} AMD_CACHE_EACH_LEVEL_DMI_INFO;

/// Structure for Cache DMI information
typedef struct _AMD_CACHE_DMI_INFO {
  AMD_CACHE_EACH_LEVEL_DMI_INFO    CacheEachLevelInfo[CpuLmaxCache];    ///< Cache info
} AMD_CACHE_DMI_INFO;

///
/// Forward declaration for the AMD_CCX_SMBIOS_SERVICES_PROTOCOL.
///
typedef struct _AMD_CCX_SMBIOS_SERVICES_PROTOCOL AMD_CCX_SMBIOS_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_SMBIOS_SERVICES_GET_CORE_DMI_INFO) (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CCX_CORE_DMI_INFO                  *CoreDmiInfo
  );

typedef
EFI_STATUS
(EFIAPI *AMD_SMBIOS_SERVICES_GET_CACHE_DMI_INFO) (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CACHE_DMI_INFO                     *CacheDmiInfo
  );


///
/// When installed, the SMBIOS Services Protocol produces a collection of
/// services that return various information to generate SMBIOS
///
struct _AMD_CCX_SMBIOS_SERVICES_PROTOCOL {
  UINTN                                            Revision;               ///< Revision Number
  AMD_SMBIOS_SERVICES_GET_CORE_DMI_INFO            GetCoreDmiInfo;         ///< Core info
  AMD_SMBIOS_SERVICES_GET_CACHE_DMI_INFO           GetCacheDmiInfo;        ///< Cache info
};

///
/// Forward declaration for the AMD_MEM_SMBIOS_SERVICES_PROTOCOL.
///
typedef struct _AMD_MEM_SMBIOS_SERVICES_PROTOCOL AMD_MEM_SMBIOS_SERVICES_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMD_SMBIOS_SERVICES_GET_MEM_DMI_INFO) (
  IN       AMD_MEM_SMBIOS_SERVICES_PROTOCOL       *This,
     OUT   DMI_INFO                               *MemDmiInfo
  );

///
/// When installed, the SMBIOS Services Protocol indicates that the Memory
/// DMI info has been collected in heap
///
struct _AMD_MEM_SMBIOS_SERVICES_PROTOCOL {
  UINTN                                            Revision;               ///< Revision Number
  AMD_SMBIOS_SERVICES_GET_MEM_DMI_INFO             GetMemDmiInfo;          ///< Pointer to Memory DMI info
};

#define SMBIOS_3_0_0 300
#define SMBIOS_3_1_1 311

extern EFI_GUID gAmdCcxSmbiosServicesProtocolGuid;
extern EFI_GUID gAmdMemSmbiosServicesProtocolGuid;

#pragma pack (pop)
#endif // _AMD_SMBIOS_SERVICES_PROTOCOL_H_

