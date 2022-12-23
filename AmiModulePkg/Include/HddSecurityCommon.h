//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file HddSecurityCommon.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the different module parts in the 
    HddSecurity driver

**/

#ifndef _HDD_SECURITY_COMMON_
#define _HDD_SECURITY_COMMON_

#include <Include/AmiStorageFeatures.h>
#include <Library/AmiListLib.h>
#include <Protocol/AmiHddSecurity.h>
#include <Protocol/IoMmu.h>
#include <IndustryStandard/AmiAtaAtapi.h>

#define IDE_SECURITY_PWNV_GUID \
    { 0x69967a8c, 0x1159, 0x4522,  {0xaa, 0x89, 0x74, 0xcd, 0xc6, 0xe5, 0x99, 0xa0}}

#define EFI_SMM_SAVE_HDD_PASSWORD_GUID \
    { 0xeedcf975, 0x4dd3, 0x4d94, { 0x96, 0xff, 0xaa, 0xca, 0x83, 0x53, 0xb8, 0x7b }}

#define EFI_SMM_REMOVE_HDD_PASSWORD_GUID \
    { 0xc2b1e795, 0xf9c5, 0x4829, {0x8a, 0x42, 0xc0, 0xb3, 0xfe, 0x57, 0x15, 0x17 }}

#define AMI_HDD_SECURITY_SEND_COMMAND_DATA_BUFFER_GUID \
    { 0xb3f096e9, 0x2d46, 0x4e8e, { 0xa2, 0x2c, 0x7d, 0xe8, 0xb1, 0x6b, 0x3a, 0x5b }}

#define AMI_HDD_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID \
    { 0x60b0760c, 0x7d1b, 0x43f3, {0x95, 0x25, 0x60, 0x77, 0xbe, 0x41, 0x37, 0xe2 }}

#define AMI_NVME_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID \
    { 0x3fb7e17f, 0x1172, 0x4e2a, { 0x9a, 0x25, 0xba, 0x5f, 0xe6, 0x2c, 0xc7, 0xc8 }}

#define HDD_SEC_LOCKBOX_MAP_DATA_GUID \
    {0x51040161, 0xd30e, 0x4125, {0xa1, 0xe5, 0xf7, 0x36, 0xb8, 0x35, 0xa1, 0x98}};

#ifndef AMITSE_EVENT_BEFORE_BOOT_GUID
#define AMITSE_EVENT_BEFORE_BOOT_GUID \
  { 0x3677770f, 0xefb2, 0x43b2, {0xb8, 0xae, 0xb3, 0x2, 0xe9, 0x60, 0x48, 0x82 }}
#endif

#define HDD_SEC_LOCK_BOX_DATA_GUID \
        {0x8dd26f6a, 0x401a, 0x4d2a, {0xa3, 0x75, 0x22, 0x8c, 0xd, 0x65, 0xc8, 0x48}}

#define PCI_ROOT_BRIDGE_IO_OFFSET               0x1C
#define PCI_ROOT_BRIDGE_MEM_OFFSET              0x20
#define PCI_ROOT_BRIDGE_PFMEM_OFFSET            0x24   // Prefetchable Memory

#define MAX_NVME_DEVICES                        32
#define ADMIN_QUEUE_SIZE                        0x100
#define NVME_SECURITY_SAVE_SIGNATURE            SIGNATURE_32 ('n','s','b','s')
#define HDD_SEC_SMI_UNREGISTER_SIGNATURE        SIGNATURE_64 ('S', 'M', 'I', 'U', 'N', 'R','E','G')
#define HDD_SEC_SIGNATURE                       SIGNATURE_32 ('$','H','D','D')

#define SECURITY_SUPPORTED_MASK                 0x0001
#define SECURITY_ENABLED_MASK                   0x0002
#define SECURITY_LOCKED_MASK                    0x0004
#define SECURITY_FROZEN_MASK                    0x0008

#define  NVME_ATA_SECURITY_SET_PASSWORD         0x1
#define  NVME_ATA_SECURITY_UNLOCK               0x2
#define  NVME_ATA_SECURITY_ERASE_PREPARE        0x3
#define  NVME_ATA_SECURITY_ERASE_UNIT           0x4
#define  NVME_ATA_SECURITY_FREEZE_LOCK          0x5
#define  NVME_ATA_SECURITY_DISABLE_PASSWORD     0x6

#define AMI_HDD_SECURITY_LOAD_SETUP_DEFAULTS_GUID \
        { 0x2ff61c92, 0xdb91, 0x431d, { 0x94, 0xf9, 0x89, 0x92, 0xc3, 0x61, 0x5f, 0x48 } }

// Remove below code when gTseEscOnPwdPromptGuid 
// definition is added in AmiTsePkg.dec
#ifndef AMITSE_ESC_ON_PWD_PROMPT_GUID 
#define AMITSE_ESC_ON_PWD_PROMPT_GUID \
    {0x5b5d1d38, 0x1fa9, 0x433b, {0x97, 0xd6, 0xf8, 0x26, 0x77, 0xab, 0x3f, 0xe4}}
#endif

typedef struct {
    UINT32                              RegNum;
    EFI_BOOT_SCRIPT_WIDTH               Width;
    UINT32                              Mask;
} BOOT_SCRIPT_NVME_REG_SAVE;

typedef struct {
    UINTN                               Segment;
    UINTN                               PciAddress;
    EFI_BOOT_SCRIPT_WIDTH               Width;
    UINTN                               Value;
} BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY;

typedef struct {
    UINT32                    Signature;
    // Changed UserPassword and MasterPassword array to pointer 
    // since separate Confidential pool will be allocated for password in SMRAM
    UINT8                     *UserPassword;   
    UINT8                     *MasterPassword;
    UINT16                    BaseAddress;
    UINT16                    DeviceControlReg;
    UINT8                     Device;             // Master/Slave
    UINT16                    Control;
    UINT16                    RevisionCode;
    UINT16                    PortNumber;
    UINT16                    PMPortNumber;
    EFI_HANDLE                DevHandle;
    UINT8                     BusNo;
    UINT8                     DeviceNo;
    UINT8                     FunctionNo;
    AMI_STORAGE_BUS_INTERFACE BusInterfaceType;
    BOOLEAN                   IsRaidHdd;    
    AMI_LINK                  LinkList;
    UINT64                    AdminQueueAddress;
    CHAR8                     ModelSerialNo[60];
} HDD_PASSWORD;

typedef struct {
    AMI_HDD_SECURITY_PROTOCOL *HddSecurityProtocol;
    EFI_HANDLE                PostHiiHandle;
    UINT16                    NameToken;
    UINT16                    PromptToken;
    BOOLEAN                   Locked;
    BOOLEAN                   LoggedInAsMaster;
    BOOLEAN                   Validated;
    UINT8                     PWD[IDE_PASSWORD_LENGTH + 1];
    EFI_HANDLE                DeviceHandle;
} HDD_SECURITY_INTERNAL_DATA;

typedef struct _AMI_HDD_SECURITY_INTERFACE { 
    AMI_HDD_SECURITY_PROTOCOL            HddSecurityProtocol;
    VOID                                 *BusInterface;
    AMI_STORAGE_BUS_INTERFACE            BusInterfaceType;
    VOID                                 *PostHddCount;
    VOID                                 **PostHddData;
} AMI_HDD_SECURITY_INTERFACE;

typedef struct {
    CHAR8            ModelSerialNo[60];
    UINT8            PwdBuffer[IDE_PASSWORD_LENGTH];
    BOOLEAN          IsMasterPwd;        // 0 - User Password, 1 - Master Password
    BOOLEAN          IsTcgPwd;           // 0 - SAT3 Password set, 1- TCG Password set
    BOOLEAN          IsRaidHdd;          // 0 - NVMe, 1 - SATA 
} RAID_LOCK_BOX_DATA;

typedef struct {
    EFI_PHYSICAL_ADDRESS        Address1;
    EFI_PHYSICAL_ADDRESS        Address2;
    UINT32                      Length1;
    UINT32                      Length2;
    EDKII_IOMMU_OPERATION       Operation1;
    EDKII_IOMMU_OPERATION       Operation2;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType;
    EFI_PHYSICAL_ADDRESS        DevHandle;
} IOMMU_MAP_INFORMATION;

/// Defines type of a Storage Bus Interface.
/* Local definition to add Raid support. TODO this will be removed
 *  Once AmiStorageInterfaceRaid type added to AMI_STORAGE_BUS_INTERFACE in 
 *  core file "AmiStorageFeatures.h"
 */
typedef enum {
    LocalAmiStorageInterfaceIde,
    LocalAmiStorageInterfaceAhci,
    LocalAmiStorageInterfaceNvme,
    LocalAmiStorageInterfaceRaid,
    LocalAmiStorageInterfaceMax
} LOCAL_AMI_STORAGE_BUS_INTERFACE;

#define AMI_TSE_HDD_NOTIFY_GUID \
        { 0x6de538e4, 0xe391, 0x4881, { 0x80, 0x6c, 0xc8, 0xf9, 0x66, 0xfb, 0xee, 0x35 } }

#endif

