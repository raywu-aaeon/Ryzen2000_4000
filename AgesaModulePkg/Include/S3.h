/* $NoKeywords:$ */
/**
 * @file
 *
 *  ACPI S3 support definitions.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU
 * @e \$Revision: 313524 $   @e \$Date: 2015-02-24 12:01:43 +0800 (Tue, 24 Feb 2015) $
 *
 */
/*
*****************************************************************************
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

#ifndef _S3_H_
#define _S3_H_


/*---------------------------------------------------------------------------------------
 *          M I X E D   (Definitions And Macros / Typedefs, Structures, Enums)
 *---------------------------------------------------------------------------------------
 */


/*---------------------------------------------------------------------------------------
 *                 D E F I N I T I O N S     A N D     M A C R O S
 *---------------------------------------------------------------------------------------
 */
#define RESTART_FROM_BEGINNING_LIST 0xFFFFFFFFul

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */

/* Device related definitions */

/// S3 device types
typedef enum {
  DEV_TYPE_PCI_PRE_ESR,               ///< PCI device before exiting self-refresh
  DEV_TYPE_PCI,                       ///< PCI device after exiting self-refresh
  DEV_TYPE_CPCI_PRE_ESR,              ///< 'conditional' PCI device before exiting self-refresh
  DEV_TYPE_CPCI,                      ///< 'conditional' PCI device after exiting self-refresh
  DEV_TYPE_MSR_PRE_ESR,               ///< MSR device before exiting self-refresh
  DEV_TYPE_MSR,                       ///< MSR device after exiting self-refresh
  DEV_TYPE_CMSR_PRE_ESR,              ///< 'conditional' MSR device before exiting self-refresh
  DEV_TYPE_CMSR                       ///< 'conditional' MSR device after exiting self-refresh
} S3_DEVICE_TYPES;

/// S3 restoration call points
typedef enum {
  INIT_RESUME,                        ///< AMD_INIT_RESUME
  S3_LATE_RESTORE,                    ///< AMD_S3LATE_RESTORE
  PSP_INIT_RESUME,                    ///< AMD_PSP_INIT_RESUME
} CALL_POINTS;

/// S3 device common header
typedef struct {
  _4BYTE_ALIGN UINT32 RegisterListID; ///< Unique ID of this device
  _1BYTE_ALIGN UINT8 Type; ///< Appropriate S3_DEVICE_TYPES type
} DEVICE_DESCRIPTOR;

/// S3 PCI device header
typedef struct {
  _4BYTE_ALIGN UINT32 RegisterListID; ///< Unique ID of this device
  _1BYTE_ALIGN UINT8 Type; ///< DEV_TYPE_PCI / DEV_TYPE_PCI_PRE_ESR
  _1BYTE_ALIGN UINT8 Node; ///< Zero-based node number
} PCI_DEVICE_DESCRIPTOR;

/// S3 'conditional' PCI device header
typedef struct {
  _4BYTE_ALIGN UINT32 RegisterListID; ///< Unique ID of this device
  _1BYTE_ALIGN UINT8 Type; ///< DEV_TYPE_CPCI / DEV_TYPE_CPCI_PRE_ESR
  _1BYTE_ALIGN UINT8 Node; ///< Zero-based node number
  _1BYTE_ALIGN UINT8 Mask1; ///< Conditional mask 1
  _1BYTE_ALIGN UINT8 Mask2; ///< Conditional mask 2
} CONDITIONAL_PCI_DEVICE_DESCRIPTOR;

/// S3 MSR device header
typedef struct {
  _4BYTE_ALIGN UINT32 RegisterListID; ///< Unique ID of this device
  _1BYTE_ALIGN UINT8 Type; ///< DEV_TYPE_MSR / DEV_TYPE_MSR_PRE_ESR
} MSR_DEVICE_DESCRIPTOR;

/// S3 'conditional' MSR device header
typedef struct {
  _4BYTE_ALIGN UINT32 RegisterListID; ///< Unique ID of this device
  _1BYTE_ALIGN UINT8 Type; ///< DEV_TYPE_CMSR / DEV_TYPE_CMSR_PRE_ESR
  _1BYTE_ALIGN UINT8 Mask1; ///< Conditional mask 1
  _1BYTE_ALIGN UINT8 Mask2; ///< Conditional mask 2
} CONDITIONAL_MSR_DEVICE_DESCRIPTOR;

/* Special case related definitions */

/**
 * PCI special case save handler
 *
 * @param[in]     AccessWidth   8, 16, or 32 bit wide access
 * @param[in]     Address       full PCI address of the register to save
 * @param[out]    Value         Value read from the register
 * @param[in]     ConfigPtr     AMD standard header config parameter
 *
 */
typedef VOID (*PF_S3_SPECIAL_PCI_SAVE) (
  IN       ACCESS_WIDTH AccessWidth,
  IN       PCI_ADDR     Address,
     OUT   VOID         *Value,
  IN       VOID         *ConfigPtr
  );

/**
 * PCI special case restore handler
 *
 * @param[in]     AccessWidth   8, 16, or 32 bit wide access
 * @param[in]     Address       full PCI address of the register to save
 * @param[in]     Value         Value to write to the register
 * @param[in]     ConfigPtr     AMD standard header config parameter
 *
 */
typedef VOID (*PF_S3_SPECIAL_PCI_RESTORE) (
  IN       ACCESS_WIDTH       AccessWidth,
  IN       PCI_ADDR           PciAddress,
  IN       VOID               *Value,
  IN       VOID               *StdHeader
  );

/**
 * MSR special case save handler
 *
 * @param[in]     MsrAddress    Address of model specific register to save
 * @param[out]    Value         Value read from the register
 * @param[in]     ConfigPtr     AMD standard header config parameter
 *
 */
typedef VOID (*PF_S3_SPECIAL_MSR_SAVE) (
  IN       UINT32             MsrAddress,
     OUT   UINT64             *Value,
  IN       VOID               *StdHeader
  );

/**
 * MSR special case restore handler
 *
 * @param[in]     MsrAddress    Address of model specific register to restore
 * @param[in]     Value         Value to write to the register
 * @param[in]     ConfigPtr     AMD standard header config parameter
 *
 */
typedef VOID (*PF_S3_SPECIAL_MSR_RESTORE) (
  IN       UINT32             MsrAddress,
  IN       UINT64             *Value,
  IN       VOID               *StdHeader
  );

/// PCI special case save/restore structure.
typedef struct {
  _4BYTE_ALIGN PF_S3_SPECIAL_PCI_SAVE Save; ///< Save routine
  _4BYTE_ALIGN PF_S3_SPECIAL_PCI_RESTORE Restore; ///< Restore routine
} PCI_SPECIAL_CASE;

/// MSR special case save/restore structure.
typedef struct {
  _4BYTE_ALIGN PF_S3_SPECIAL_MSR_SAVE Save; ///< Save routine
  _4BYTE_ALIGN PF_S3_SPECIAL_MSR_RESTORE Restore; ///< Restore routine
} MSR_SPECIAL_CASE;

/* Register related definitions */
#ifdef NON_BIT_REGISTER_TYPE
  /// S3 register type fields without bit definition
  typedef struct {
    _1BYTE_ALIGN UINT8 SpecialCaseIndex ;///< Special Case array index
    _1BYTE_ALIGN UINT8 RegisterSize ;///< For PCI, 1 = byte, 2 = word, else = dword.
                         ///< For MSR, don't care
    _1BYTE_ALIGN UINT8 SpecialCaseFlag  ;///< Indicates special case
  } S3_REGISTER_TYPE;
#else
  /// S3 register type bit fields
  typedef struct {
    _1BYTE_ALIGN UINT8 SpecialCaseIndex :5; ///< Special Case array index
    _1BYTE_ALIGN UINT8 RegisterSize :2; ///< For PCI, 1 = byte, 2 = word, else = dword.
                         ///< For MSR, don't care
    _1BYTE_ALIGN UINT8 SpecialCaseFlag  :1; ///< Indicates special case
  } S3_REGISTER_TYPE;
#endif
/// S3 PCI register descriptor.
typedef struct {
  _4BYTE_ALIGN S3_REGISTER_TYPE Type; ///< Type[7] = special case flag,
                           ///< Type[6:5] = register size in by
                           ///< Type[4:0] = special case index
  _1BYTE_ALIGN UINT8 Function; ///< PCI function of the register
  _2BYTE_ALIGN UINT16 Offset; ///< PCI offset of the register
  _4BYTE_ALIGN UINT32 AndMask; ///< AND mask to be applied to the value before saving
  _1BYTE_ALIGN UINT8 BootMode; ///< Boot mode
} PCI_REG_DESCRIPTOR;

/// S3 'conditional' PCI register descriptor.
typedef struct {
  _4BYTE_ALIGN S3_REGISTER_TYPE Type; ///< Type[7] = special case flag,
                           ///< Type[6:3] = register size in bytes,
                           ///< Type[2:0] = special case index
  _1BYTE_ALIGN UINT8 Function; ///< PCI function of the register
  _2BYTE_ALIGN UINT16 Offset; ///< PCI offset of the register
  _4BYTE_ALIGN UINT32 AndMask; ///< AND mask to be applied to the value before saving
  _1BYTE_ALIGN UINT8 Mask1; ///< conditional mask 1
  _1BYTE_ALIGN UINT8 Mask2; ///< conditional mask 2
  _1BYTE_ALIGN UINT8 BootMode; ///< Boot mode
} CONDITIONAL_PCI_REG_DESCRIPTOR;

/// S3 MSR register descriptor.
typedef struct {
  _4BYTE_ALIGN S3_REGISTER_TYPE Type; ///< Type[7] = special case flag,
                           ///< Type[6:3] = reserved,
                           ///< Type[2:0] = special case index
  _4BYTE_ALIGN UINT32 Address; ///< MSR address
  _8BYTE_ALIGN UINT64 AndMask; ///< AND mask to be applied to the value before saving
  _1BYTE_ALIGN UINT8 BootMode; ///< Boot mode
} MSR_REG_DESCRIPTOR;

/// S3 'conditional' MSR register descriptor.
typedef struct {
  _4BYTE_ALIGN S3_REGISTER_TYPE  Type;             ///< Type[7] = special case flag,
                                      ///< Type[6:3] = reserved,
                                      ///< Type[2:0] = special case index
  _4BYTE_ALIGN UINT32 Address; ///< MSR address
  _8BYTE_ALIGN UINT64 AndMask; ///< AND mask to be applied to the value before saving
  _1BYTE_ALIGN UINT8 Mask1; ///< conditional mask 1
  _1BYTE_ALIGN UINT8 Mask2; ///< conditional mask 2
  _1BYTE_ALIGN UINT8 BootMode; ///< Boot mode
} CONDITIONAL_MSR_REG_DESCRIPTOR;

/// Common header at the beginning of an S3 register list.
typedef struct {
  _2BYTE_ALIGN UINT16 Version; ///< Version of header
  _2BYTE_ALIGN UINT16 NumRegisters; ///< Number of registers in the list
} REGISTER_BLOCK_HEADER;

/// S3 PCI register list header.
typedef struct {
  _2BYTE_ALIGN UINT16 Version; ///< Version of header
  _2BYTE_ALIGN UINT16 NumRegisters; ///< Number of registers in the list
  _4BYTE_ALIGN PCI_REG_DESCRIPTOR *RegisterList; ///< Pointer to the first register descriptor
  _4BYTE_ALIGN PCI_SPECIAL_CASE *SpecialCases; ///< Pointer to array of special case handlers
} PCI_REGISTER_BLOCK_HEADER;

/// S3 'conditional' PCI register list header.
typedef struct {
  _2BYTE_ALIGN UINT16 Version; ///< Version of header
  _2BYTE_ALIGN UINT16 NumRegisters; ///< Number of registers in the list
  _4BYTE_ALIGN CONDITIONAL_PCI_REG_DESCRIPTOR *RegisterList; ///< Pointer to the first register descriptor
  _4BYTE_ALIGN PCI_SPECIAL_CASE *SpecialCases; ///< Pointer to array of special case handlers
} CPCI_REGISTER_BLOCK_HEADER;

/// S3 MSR register list header.
typedef struct {
  _2BYTE_ALIGN UINT16 Version; ///< Version of header
  _2BYTE_ALIGN UINT16 NumRegisters; ///< Number of registers in the list
  _4BYTE_ALIGN MSR_REG_DESCRIPTOR *RegisterList; ///< Pointer to the first register descriptor
  _4BYTE_ALIGN MSR_SPECIAL_CASE *SpecialCases; ///< Pointer to array of special case handlers
} MSR_REGISTER_BLOCK_HEADER;

/// S3 'conditional' MSR register list header.
typedef struct {
  _2BYTE_ALIGN UINT16 Version; ///< Version of header
  _2BYTE_ALIGN UINT16 NumRegisters; ///< Number of registers in the list
  _4BYTE_ALIGN  CONDITIONAL_MSR_REG_DESCRIPTOR *RegisterList; ///< Pointer to the first register descriptor
  _4BYTE_ALIGN  MSR_SPECIAL_CASE *SpecialCases; ///< Pointer to array of special case handlers
} CMSR_REGISTER_BLOCK_HEADER;

/// S3 device descriptor pointers for ease of proper pointer advancement.
typedef union {
  _4BYTE_ALIGN DEVICE_DESCRIPTOR *CommonDeviceHeader; ///< Common header
  _4BYTE_ALIGN PCI_DEVICE_DESCRIPTOR *PciDevice; ///< PCI header
  _4BYTE_ALIGN CONDITIONAL_PCI_DEVICE_DESCRIPTOR *CPciDevice; ///< 'conditional' PCI header
  _4BYTE_ALIGN MSR_DEVICE_DESCRIPTOR *MsrDevice; ///< MSR header
  _4BYTE_ALIGN CONDITIONAL_MSR_DEVICE_DESCRIPTOR *CMsrDevice; ///< 'conditional' MSR header
} DEVICE_DESCRIPTORS;

/// S3 register list header pointers for ease of proper pointer advancement.
typedef union {
  _4BYTE_ALIGN DEVICE_DESCRIPTOR *CommonDeviceHeader; ///< Common header
  _4BYTE_ALIGN PCI_REGISTER_BLOCK_HEADER *PciRegisters; ///< PCI header
  _4BYTE_ALIGN CPCI_REGISTER_BLOCK_HEADER *CPciRegisters; ///< 'conditional' PCI header
  _4BYTE_ALIGN MSR_REGISTER_BLOCK_HEADER *MsrRegisters; ///< MSR header
  _4BYTE_ALIGN CMSR_REGISTER_BLOCK_HEADER *CMsrRegisters; ///< 'conditional' MSR header
} REGISTER_BLOCK_HEADERS;

/// S3 Volatile Storage Header
typedef struct {
  _4BYTE_ALIGN UINT32 HeapOffset; ///< Offset to beginning of heap data
  _4BYTE_ALIGN UINT32 HeapSize; ///< Size of the heap data
  _4BYTE_ALIGN UINT32 RegisterDataOffset; ///< Offset to beginning of raw save data
  _4BYTE_ALIGN UINT32 RegisterDataSize; ///< Size of raw save data
} S3_VOLATILE_STORAGE_HEADER;


/*---------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *---------------------------------------------------------------------------------------
 */
UINT32
GetWorstCaseContextSize (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       CALL_POINTS         CallPoint,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
SaveDeviceListContext (
  IN       DEVICE_BLOCK_HEADER *DeviceList,
  IN       VOID                *Storage,
  IN       CALL_POINTS         CallPoint,
     OUT   UINT32              *ActualBufferSize,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
RestorePreESRContext (
     OUT   VOID **OrMaskPtr,
  IN       VOID *Storage,
  IN       CALL_POINTS       CallPoint,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
RestorePostESRContext (
  IN       VOID *OrMaskPtr,
  IN       VOID *Storage,
  IN       CALL_POINTS       CallPoint,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

VOID
S3DataBlockInitializer (
     OUT   S3_DATA_BLOCK *S3DataBlock
  );

VOID
GetNonMemoryRelatedDeviceList (
     OUT   DEVICE_BLOCK_HEADER **NonMemoryRelatedDeviceList,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  );

AGESA_STATUS
S3GetPciDeviceRegisterList (
  IN       PCI_DEVICE_DESCRIPTOR     *Device,
     OUT   PCI_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

AGESA_STATUS
S3GetCPciDeviceRegisterList (
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
     OUT   CPCI_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  );

AGESA_STATUS
S3GetMsrDeviceRegisterList (
  IN       MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   MSR_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

AGESA_STATUS
S3GetCMsrDeviceRegisterList (
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR *Device,
     OUT   CMSR_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  );


#endif  // _S3_H_

