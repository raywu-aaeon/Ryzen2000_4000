/* $NoKeywords:$ */
/**
 * @file
 *
 * mfS3.h
 *
 * S3 resume memory related functions.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/S3)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 **/
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
*
*/

#ifndef _MFS3_H_
#define _MFS3_H_

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define PRESELFREF 0
#define POSTSELFREF 1
#define DCT0 0
#define DCT1 1
#define DCT0_MASK 0x1
#define DCT1_MASK 0x2
#define DCT0_NBPSTATE_SUPPORT_MASK 0x4
#define DCT1_NBPSTATE_SUPPORT_MASK 0x8
#define DCT0_DDR3_MASK 0x10
#define DCT1_DDR3_MASK 0x20
#define NODE_WITHOUT_DIMM_MASK 0x80
#define DCT0_ANY_DIMM_MASK 0x55
#define DCT1_ANY_DIMM_MASK 0xAA
#define ANY_DIMM_MASK 0xFF

#define DCT_PHY_FLAG 0
#define DCT_EXTRA_FLAG 1
#define SET_S3_SPECIAL_OFFSET(AccessType, Dct, Offset) ((AccessType << 11) | (Dct << 10) | Offset)

#define RESTORE_TRAINING_MODE 1
#define CAPSULE_REBOOT_MODE 2
#define S3_RESUME_MODE 4
#define SAVE_AT_POST_END 8
/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */
/// struct for all the descriptor for pre exit self refresh and post exit self refresh
typedef struct _DESCRIPTOR_GROUP {
  _4BYTE_ALIGN PCI_DEVICE_DESCRIPTOR PCIDevice[2];  ///< PCI device descriptor
  _4BYTE_ALIGN CONDITIONAL_PCI_DEVICE_DESCRIPTOR CPCIDevice[2];  ///< Conditional PCI device descriptor
  _4BYTE_ALIGN MSR_DEVICE_DESCRIPTOR MSRDevice[2];  ///< MSR device descriptor
  _4BYTE_ALIGN CONDITIONAL_MSR_DEVICE_DESCRIPTOR CMSRDevice[2];  ///< Conditional MSR device descriptor
} DESCRIPTOR_GROUP;

/// Northbridge block to be used in S3 resume and save.
typedef struct _S3_MEM_NB_BLOCK {
  _4BYTE_ALIGN UINT8 MemS3SpecialCaseHeapSize; ///< Heap size for the special case register heap.
  _4BYTE_ALIGN UINT32 S3DatablobRev; ///< S3 Datablob Rev
  struct _MEM_NB_BLOCK *NBPtr;    ///< Pointer to the north bridge block.
  _4BYTE_ALIGN VOID (*MemS3ExitSelfRefReg) (MEM_NB_BLOCK *NBPtr, AMD_CONFIG_PARAMS *StdHeaderPtr); ///< S3 Exit self refresh register
  _4BYTE_ALIGN VOID (*MemS3GetConPCIMask) (MEM_NB_BLOCK *NBPtr, DESCRIPTOR_GROUP *DescriptPtr); ///< Get conditional mask for PCI register setting
  _4BYTE_ALIGN VOID (*MemS3GetConMSRMask) (MEM_NB_BLOCK *NBPtr, DESCRIPTOR_GROUP *DescriptPtr); ///< Get conditional mask for MSR register setting
  _4BYTE_ALIGN UINT16 (*MemS3GetRegLstPtr) (MEM_NB_BLOCK *NBPtr, DESCRIPTOR_GROUP *DescriptPtr); ///< Get register list pointer for both PCI and MSR register
  _4BYTE_ALIGN BOOLEAN (*MemS3Resume) (struct _S3_MEM_NB_BLOCK *S3NBPtr, UINT8 NodeID);///< Exit Self Refresh
  _4BYTE_ALIGN VOID (*MemS3RestoreScrub) (MEM_NB_BLOCK *NBPtr, UINT8 NodeID);///< Restore scrubber base
  _4BYTE_ALIGN AGESA_STATUS (*MemS3GetDeviceRegLst) (UINT32 ReigsterLstID, VOID **RegisterHeader, MEM_NB_BLOCK *NBPtr); ///< Get register list for a device
  _4BYTE_ALIGN BOOLEAN (*MemS3PspDetect) (MEM_NB_BLOCK *NBPtr); ///< PSP detection
  _4BYTE_ALIGN BOOLEAN (*MemS3PspPlatformSecureBootEn) (MEM_NB_BLOCK *NBPtr); ///< PSP Platform Secure Boot detection
} S3_MEM_NB_BLOCK;

/// Header for heap space to store the special case register.
typedef struct _S3_SPECIAL_CASE_HEAP_HEADER {
  _1BYTE_ALIGN UINT8 Node;  ///< Node ID for the the header
  _1BYTE_ALIGN UINT8 Offset;  ///< Offset for the target node
} S3_SPECIAL_CASE_HEAP_HEADER;

/// Flag for hob data save and restore
typedef enum _MEM_HOB_DATA_TYPE {
  S3_UMA_SIZE,  ///< UMA size
  S3_UMA_BASE,  ///< UMA base
  S3_UMA_MODE,  ///< UMA mode
  S3_SUB_4G_CACHE_TOP,  ///< Sub 4G Cache Top
  S3_SYSLIMIT,  ///< System limit
  S3_UMA_ATTRIBUTE,  ///< UMA attribute
  S3_VDDIO  ///< VDDIO
} MEM_HOB_DATA_TYPE;

/// Header for heap space to store reduced memory internal data
typedef struct _REDUCED_MEM_BLOCK_HEAP_HEADER {
  _2BYTE_ALIGN UINT16 Version;                 ///< Version of header
  _1BYTE_ALIGN   UINT8  NumNodes;                ///< Number of reduced NB blocks in the list
} REDUCED_MEM_BLOCK_HEAP_HEADER;

/// Reduced NB Block to store data during memory context save/restore
typedef struct _REDUCED_NB_BLOCK {
  _4BYTE_ALIGN UINT32       NodeMemSize;             ///< Base[47:16], total DRAM size controlled by both DCT0 and DCT1 of this Node.
  _4BYTE_ALIGN UINT32       NodeSysBase;             ///< System base of this node
  _1BYTE_ALIGN UINT8        NumDcts;                 ///< Number of reduced DCT blocks in the list
  _4BYTE_ALIGN UMA_MODE     UmaMode;                 ///< Indicate the mode of Uma
  _4BYTE_ALIGN UINT32       UmaBase;                 ///< UmaBase[63:0] = Addr[63:0]
  _4BYTE_ALIGN UINT32       UmaSize;                 ///< UmaSize[31:0] = Addr[31:0]
  _4BYTE_ALIGN UINT32       UmaAttributes;           ///< Indicate the attribute of Uma
  _4BYTE_ALIGN UINT32       SysLimit;                ///< Limit[47:16] (system address).
  _4BYTE_ALIGN UINT32       Sub4GCacheTop;           ///< If not zero, the 32-bit top of cacheable memory.
  _4BYTE_ALIGN DIMM_VOLTAGE DDRVoltage;              ///< Find support voltage and send back to platform BIOS for DDR3 or DDR4.
} REDUCED_NB_BLOCK;

/// Reduced DCT Block to store data during memory context save/restore
typedef struct _REDUCED_DCT_BLOCK {
  _1BYTE_ALIGN UINT8  Dct;                     ///< Dct Number
  _4BYTE_ALIGN UINT32 DctMemSize;              ///< Base[47:16], total DRAM size controlled by this DCT.
  _1BYTE_ALIGN UINT8  EnabledChipSels;         ///< Number of enabled chip selects on current DCT
  _1BYTE_ALIGN UINT8  BankAddrMap;             ///< Bank Address Mapping
  _1BYTE_ALIGN BOOLEAN BkIntDis;               ///< Bank interleave requested but not enabled on current DCT
} REDUCED_DCT_BLOCK;

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */
AGESA_STATUS
AmdMemS3Resume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
MemS3ResumeInitNB (
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
MemS3Deallocate (
  IN   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
MemFS3GetPciDeviceRegisterList (
  IN       PCI_DEVICE_DESCRIPTOR     *Device,
     OUT   PCI_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

AGESA_STATUS
MemFS3GetCPciDeviceRegisterList (
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
     OUT   CPCI_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  );

AGESA_STATUS
MemFS3GetMsrDeviceRegisterList (
  IN       MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   MSR_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

AGESA_STATUS
MemFS3GetCMsrDeviceRegisterList (
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   CMSR_REGISTER_BLOCK_HEADER            **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                     *StdHeader
  );

AGESA_STATUS
MemFS3GetDeviceList (
  IN OUT   DEVICE_BLOCK_HEADER **DeviceBlockHdrPtr,
  IN       VOID *OptionMemoryInstallPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

BOOLEAN
MemNS3ResumeUNb (
  IN OUT   S3_MEM_NB_BLOCK *S3NBPtr,
  IN       UINT8 NodeID
  );

VOID
MemNS3GetBitFieldNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3SetBitFieldNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3RestoreScrubNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Node
  );

AGESA_STATUS
MemS3InitNB (
  IN OUT   S3_MEM_NB_BLOCK **S3NBPtr,
  IN OUT   MEM_DATA_STRUCT **MemPtr,
  IN OUT   MEM_MAIN_DATA_BLOCK *mmData,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MemNS3SetPreDriverCalUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

BOOLEAN
MemNS3DctCfgSelectUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  );

VOID
MemNS3GetNBPStateDepRegUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3SetNBPStateDepRegUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3SaveNBRegisterUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3RestoreNBRegisterUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3SetMemClkFreqValUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3ChangeMemPStateContextNb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3ForceNBP0Unb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNS3ReleaseNBPSUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNSaveHobDataUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

VOID
MemNRestoreHobDataUnb (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );

AGESA_STATUS
AmdMemDoResume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  );

AGESA_STATUS
AmdMemS3DatablobRevMatch (
  IN   VOID              *Storage,
  IN   AMD_CONFIG_PARAMS *StdHeader
  );

BOOLEAN
MemS3PspNotDetected (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
MemNS3ConfigureDisDllShutdownSrKV (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR Address,
  IN OUT   VOID *Value,
  IN OUT   VOID *ConfigPtr
  );
#endif //_MFS3_H_

