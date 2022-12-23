/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#ifndef _AMD_SOC_H_
#define _AMD_SOC_H_

/// CPUID related registers
#define AMD_CPUID_FMF               0x80000001ul  // Family Model Features information
#define AMD_CPUID_APICID_LPC_BID    0x00000001ul  // Local APIC ID, Logical Processor Count, Brand ID

#define CPUID_STEPPING_MASK      0x0000000Ful
#define CPUID_BASE_MODEL_MASK    0x000000F0ul
#define CPUID_BASE_FAMILY_MASK   0x00000F00ul
#define CPUID_EXT_MODEL_MASK     0x000F0000ul
#define CPUID_EXT_FAMILY_MASK    0x0FF00000ul

#define RAW_FAMILY_ID_MASK (UINT32) (CPUID_EXT_FAMILY_MASK | CPUID_EXT_MODEL_MASK | CPUID_BASE_FAMILY_MASK)

#define F17_ZP_RAW_ID   0x00800F00ul

/// Family 17 package type

/// Zeppelin package type
typedef enum {
  ZP_SP4   = 1,           ///< Embedded, two ZP die MCM, single and dual socket
  ZP_AM4   = 2,           ///< Desptop, single die, single socket
  ZP_SP4r2 = 3,           ///< Embedded, single die, single socket
  ZP_SP3   = 4,           ///< Server, four ZP die MCM, single socket
  TR_SP3r2 = 7,           ///< Two TR die MCM, single socket
  ZP_UNKNOWN  = 0xFF      ///< Unknown package type
} FAMILY17_PACKAGE_TYPE;

#define ZP_PKG_SP4       1
#define ZP_PKG_AM4       2
#define ZP_PKG_SP4r2     3
#define ZP_PKG_SP3       4
#define ZP_PKG_SP3r2     7


#define F17_SSP_RAW_ID  0x00830F00ul
#define F17_MTS_RAW_ID  0x00870F00ul
/// Starship package type
typedef enum {
  SSP_SP4   = 1,          ///< Embedded, two SSP die MCM, single and dual socket
  SSP_AM4   = 2,          ///< Desptop, single die, single socket
  SSP_SP4r2 = 3,          ///< Embedded, single die, single socket
  SSP_SP3   = 4,          ///< Server, four SSP die MCM, single socket
  CP_SP3r3  = 7,          ///< Two CP die MCM, single socket
  SSP_UNKNOWN  = 0xFF     ///< Unknown package type
} FAMILY17_PACKAGE_TYPE;

#define SSP_PKG_SP4      1
#define SSP_PKG_AM4      2
#define SSP_PKG_SP4r2    3
#define SSP_PKG_SP3      4
#define CP_PKG_SP3r3     7


#define F15_BR_RAW_ID   0x00660F00ul

/// Bristol package type
typedef enum {
  BR_FP4   = 0,           ///< Notebook BGA Package
  BR_AM4   = 2,           ///< Performance class with DDR4 support
  BR_FM2r2 = 3,           ///< DesktopuPGA Package
  BR_UNKNOWN  = 0xFF      ///< Unknown package type
} BR_PACKAGE_TYPE;

#define BR_PKG_FP4       0
#define BR_PKG_AM4       2
#define BR_PKG_FM2r2     3

#define F17_RV_RAW_ID   0x00810F00ul
#define F17_RV2_RAW_ID  0x00820F00ul
#define F17_PIC_RAW_ID  0x00810F80ul

/// Raven package type
typedef enum {
  RV_FP5   = 0,           ///< Notebook BGA Package
  RV_AM4   = 2,           ///< Performance class with DDR4 support
  RV_FT5   = 3,           ///< Smaller form factor for BGA with LPDDR4
  RV_UNKNOWN  = 0xFF      ///< Unknown package type
} RV_PACKAGE_TYPE;

#define RV_PKG_FP5       0
#define RV_PKG_AM4       2
#define RV_PKG_FT5       3

#define F17_RN_RAW_ID   0x00860F00ul

/// Renior package type
typedef enum {
  RN_FP6   = 0,           ///< Notebook BGA Package
  RN_AM4   = 2,           ///< Performance class with DDR4 support
  RN_UNKNOWN  = 0xFF      ///< Unknown package type
} RN_PACKAGE_TYPE;

#define RN_PKG_FP6       0
#define RN_PKG_AM4       2

/// SOC ID Structure
typedef struct _SOC_ID_STRUCT {
  UINT32            SocFamilyID;    ///< SOC family ID
  UINT8             PackageType;    ///< SOC package type
} SOC_ID_STRUCT;

//Move to separate public header file.
typedef enum {
  PCD_BOOL = 0,             ///< PCD data type : boolean
  PCD_UINT8,                ///< PCD data type : byte
  PCD_UINT16,               ///< PCD data type : word
  PCD_UINT32,               ///< PCD data type : dword
  PCD_UINT64,               ///< PCD data type : qword
  PCD_PTR                   ///< PCD data type : pointer
} AMD_PCD_DATA_TYPE;

/**
 * An AMD AGESA Configuration Parameter Group List.
 */

typedef struct {
  UINTN BufferSize;         ///< PCD PTR buffer size
  void   *Buffer;           ///< PCD PTR buffer pointer
} AMD_PCD_PTR;


typedef struct {
  EFI_GUID *AmdConfigurationParameterPcdGuid;     ///< PCD GUID
  UINTN AmdConfigurationParameterPcdTokenNumber;  ///< PCD Token number
  UINT64   Value;                                 ///< Configurtion Parameter overwrite value.
  AMD_PCD_DATA_TYPE AmdPcdDataType;               ///< Configurtion Parameter PCD data type.
} AMD_PCD_LIST;

typedef struct {
  EFI_GUID *PlatformGroupGuid;          ///< Group List GUID pass from platform BIOS
  UINT32   NumberOfPcdEntries;          ///< number of PCD in list.
  AMD_PCD_LIST   *ListEntry;            ///< Group List version.
} AMD_GROUP_LIST_HEADER;

typedef struct {
  UINT32   Version;                     ///< Group List version.
  UINT32   NumberOfGroupsList;          ///< number of groups list.
  AMD_GROUP_LIST_HEADER   *GroupList;   ///< Group List entry
  EFI_GUID *PlatformGroupGuid;          ///< Group List GUID pass from platform BIOS
} AMD_PCD_PLATFORM_GROUP_LIST;

#endif  // _AMD_SOC_H_

