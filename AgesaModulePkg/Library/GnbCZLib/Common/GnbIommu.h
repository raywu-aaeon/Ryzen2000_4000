/**
 * @file
 *
 * Misc common definition
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 316101 $   @e \$Date: 2015-04-03 09:33:53 +0800 (Fri, 03 Apr 2015) $
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
#ifndef _GNBIOMMU_H_
#define _GNBIOMMU_H_

#pragma pack (push, 1)


/// IVRS block
typedef enum {
  IvrsIvhdBlock10h            = 0x10,       ///< I/O Virtualization Hardware Definition Block
  IvrsIvhdBlock11h            = 0x11,       ///< I/O Virtualization Hardware Definition Block
  IvrsIvmdBlock               = 0x20,       ///< I/O Virtualization Memory Definition Block for all peripherals
  IvrsIvmdBlockSingle         = 0x21,       ///< IVMD block for specified peripheral
  IvrsIvmdBlockRange          = 0x22,       ///< IVMD block for peripheral range
  IvrsIvhdrBlock40h           = 0x40,       ///< IVHDR (Relative) block
  IvrsIvhdrBlock41h           = 0x41,       ///< IVHDR (Relative) block
  IvrsIvmdrBlock              = 0x50,       ///< IVMDR (Relative) block for all peripherals
  IvrsIvmdrBlockSingle        = 0x51        ///< IVMDR block for last IVHDR
} IVRS_BLOCK_TYPE;

#define DEVICE_ID(PciAddress) (UINT16) (((PciAddress).Address.Bus << 8) | ((PciAddress).Address.Device << 3) | (PciAddress).Address.Function)

/// IVHD entry types
typedef enum {
  IvhdEntryPadding            =  0,         ///< Table padding
  IvhdEntrySelect             =  2,         ///< Select
  IvhdEntryStartRange         =  3,         ///< Start Range
  IvhdEntryEndRange           =  4,         ///< End Range
  IvhdEntryAliasSelect        =  66,        ///< Alias select
  IvhdEntryAliasStartRange    =  67,        ///< Alias start range
  IvhdEntryExtendedSelect     =  70,        ///< Extended select
  IvhdEntryExtendedStartRange =  71,        ///< Extended Start range
  IvhdEntrySpecialDevice      =  72         ///< Special device
} IVHD_ENTRY_TYPE;

/// Special device variety
typedef enum {
  IvhdSpecialDeviceIoapic     = 0x1,        ///< IOAPIC
  IvhdSpecialDeviceHpet       = 0x2         ///< HPET
} IVHD_SPECIAL_DEVICE;


#define IVHD_FLAG_PPRSUB            BIT7
#define IVHD_FLAG_PREFSUP           BIT6
#define IVHD_FLAG_COHERENT          BIT5
#define IVHD_FLAG_IOTLBSUP          BIT4
#define IVHD_FLAG_ISOC              BIT3
#define IVHD_FLAG_RESPASSPW         BIT2
#define IVHD_FLAG_PASSPW            BIT1
#define IVHD_FLAG_HTTUNEN           BIT0

#define IVHD_EFR_XTSUP_OFFSET       0
#define IVHD_EFR_NXSUP_OFFSET       1
#define IVHD_EFR_GTSUP_OFFSET       2
#define IVHD_EFR_GLXSUP_OFFSET      3
#define IVHD_EFR_IASUP_OFFSET       5
#define IVHD_EFR_GASUP_OFFSET       6
#define IVHD_EFR_HESUP_OFFSET       7
#define IVHD_EFR_PASMAX_OFFSET      8
#define IVHD_EFR_PNCOUNTERS_OFFSET  13
#define IVHD_EFR_PNBANKS_OFFSET     17
#define IVHD_EFR_MSINUMPPR_OFFSET   23
#define IVHD_EFR_GATS_OFFSET        28
#define IVHD_EFR_HATS_OFFSET        30

#define IVINFO_HTATSRESV_MASK       0x00400000ul
#define IVINFO_VASIZE_MASK          0x003F8000ul
#define IVINFO_PASIZE_MASK          0x00007F00ul
#define IVINFO_GASIZE_MASK          0x000000E0ul
#define IVINFO_EFRSUP_MASK          0x00000001ul

#define IVHD_INFO_MSINUM_OFFSET     0
#define IVHD_INFO_UNITID_OFFSET     8

#define IVMD_FLAG_EXCLUSION_RANGE   BIT3
#define IVMD_FLAG_IW                BIT2
#define IVMD_FLAG_IR                BIT1
#define IVMD_FLAG_UNITY             BIT0

/// IVRS header
typedef struct {
  UINT8   Sign[4];           ///< Signature
  UINT32  TableLength;       ///< Table Length
  UINT8   Revision;          ///< Revision
  UINT8   Checksum;          ///< Checksum
  UINT8   OemId[6];          ///< OEM ID
  UINT8   OemTableId[8];     ///< OEM Tabled ID
  UINT32  OemRev;            ///< OEM Revision
  UINT8   CreatorId[4];      ///< Creator ID
  UINT32  CreatorRev;        ///< Creator Revision
  UINT32  IvInfo;            ///< IvInfo
  UINT64  Reserved;          ///< Reserved
} IOMMU_IVRS_HEADER;

/// IVRS IVHD Entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT8   Flags;              ///< Flags
  UINT16  Length;             ///< Length
  UINT16  DeviceId;           ///< DeviceId
  UINT16  CapabilityOffset;   ///< CapabilityOffset
  UINT64  BaseAddress;        ///< BaseAddress
  UINT16  PciSegment;         ///< Pci segment
  UINT16  IommuInfo;          ///< IOMMU info
} IVRS_IVHD_ENTRY;

/// IVRS IVHD Entry
typedef struct {
  IVRS_IVHD_ENTRY Ivhd;       ///< Ivhd
  UINT32          IommuEfr;   ///< Extended Features Register
} IVRS_IVHD_ENTRY_10H;

/// IVRS IVHD Entry
typedef struct {
  IVRS_IVHD_ENTRY Ivhd;               ///< Ivhd
  UINT32          IommuAttributes;    ///< Attributes
  UINT64          IommuEfr;           ///< Extended Features Register
  UINT64          Reserved;           ///< reserved
} IVRS_IVHD_ENTRY_11H;

/// IVHD generic entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT16  DeviceId;           ///< Device id
  UINT8   DataSetting;        ///< Data settings
} IVHD_GENERIC_ENTRY;

///IVHD alias entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT16  DeviceId;           ///< Device id
  UINT8   DataSetting;        ///< Data settings
  UINT8   Reserved;           ///< Reserved
  UINT16  AliasDeviceId;      ///< Alias device id
  UINT8   Reserved2;          ///< Reserved
} IVHD_ALIAS_ENTRY;

///IVHD extended entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT16  DeviceId;           ///< Device id
  UINT8   DataSetting;        ///< Data settings
  UINT32  ExtSetting;         ///< Extended settings
} IVHD_EXT_ENTRY;

/// IVHD special entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT16  Reserved;           ///< Reserved
  UINT8   DataSetting;        ///< Data settings
  UINT8   Handle;             ///< Handle
  UINT16  AliasDeviceId;      ///< Alis device id
  UINT8   Variety;            ///< Variety
} IVHD_SPECIAL_ENTRY;

/// IVRS IVMD Entry
typedef struct {
  UINT8   Type;               ///< Type
  UINT8   Flags;              ///< Flags
  UINT16  Length;             ///< Length
  UINT16  DeviceId;           ///< DeviceId
  UINT16  AuxiliaryData;      ///< Auxiliary data
  UINT64  Reserved;           ///< Reserved (0000_0000_0000_0000)
  UINT64  BlockStart;         ///< IVMD start address
  UINT64  BlockLength;        ///< IVMD memory block length
} IVRS_IVMD_ENTRY;

/// MMIO Offset 0x30
typedef union {
  struct {                                           ///<
    UINT64                PreFSup:1;                 ///<
    UINT64                PPRSup:1;                  ///<
    UINT64                XTSup:1;                   ///<
    UINT64                NXSup:1;                   ///<
    UINT64                GTSup:1;                   ///<
    UINT64                EFRignored:1;              ///<
    UINT64                IASup:1;                   ///<
    UINT64                GASup:1;                   ///<
    UINT64                HESup:1;                   ///<
    UINT64                PCSup:1;                   ///<
    UINT64                HATS:2;                    ///<
    UINT64                GATS:2;                    ///<
    UINT64                GLXSup:2;                  ///<
    UINT64                SmiFSup:2;                 ///<
    UINT64                SmiFRC:3;                  ///<
    UINT64                GAMSup:3;                  ///<
    UINT64                Reserved_31_24:8;          ///<
    UINT64                PASmax:5;                  ///<
    UINT64                Reserved_63_37:27;         ///<
  } Field;

  UINT64 Value;
} MMIO_0x30;

/// MMIO Offset 0x18
typedef union {
  struct {                                           ///<
    UINT64                IommuEn:1;                 ///<
    UINT64                HtTunEn:1;                 ///<
    UINT64                Field_7_2:6;               ///<
    UINT64                PassPW:1;                  ///<
    UINT64                ResPassPW:1;               ///<
    UINT64                Coherent:1;                ///<
    UINT64                Isoc:1;                    ///<
    UINT64                Field_63_12:52;            ///<
  } Field;

  UINT64 Value;
} MMIO_0x18;

/// MMIO Offset 0x4000
typedef union {
  struct {                                           ///<
    UINT64               Reserved_6_0:7;             ///<
    UINT64               NCounter:4;                 ///<
    UINT64               Reserved_11:1;              ///<
    UINT64               NCounterBanks:6;            ///<
    UINT64               Reserved_63_18:46;          ///<
  } Field;

  UINT64 Value;
} MMIO_0x4000;

/// Capability offset 0
typedef union {
  struct {                                           ///<
    UINT32                IommuCapId:8;              ///<
    UINT32                IommuCapPtr:8;             ///<
    UINT32                IommuCapType:3;            ///<
    UINT32                IommuCapRev:5;             ///<
    UINT32                IommuIoTlbsup:1;           ///<
    UINT32                IommuHtTunnelSup:1;        ///<
    UINT32                IommuNpCache:1;            ///<
    UINT32                IommuEfrSup:1;             ///<
    UINT32                Reserved_31_28:4;          ///<
  } Field;

  UINT32 Value;
} CAPABILITY_REG;

#pragma pack (pop)

#endif

