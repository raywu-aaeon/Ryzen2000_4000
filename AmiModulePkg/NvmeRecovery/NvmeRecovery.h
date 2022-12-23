//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file NvmeRecovery.h
    Header file contains structure and function declaration used 
    for Nvme PCI enumeration

**/

#ifndef _NVME_RECOVERY_H_
#define _NVME_RECOVERY_H_

#include <Token.h>
#include <Uefi.h>
#include <Ppi/BlockIo.h>
#include <Ppi/IoMmu.h>
#include <Ppi/AmiPeiPciEnumeration.h>
#include <Ppi/NvmExpressHostController.h>
#include <Ppi/NvmExpressPassThru.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/TimerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Nvme.h>
#include "NvmeCtrl.h"

#define NVME_CLASS_CODE       0x01
#define NVME_SUBCLASS_CODE    0x08
#define NVME_INTERFACE_CODE   0x02

#define AMI_EXTENSION_SIGNATURE        SIGNATURE_64('N', 'V','M','E','_','R','E','C')
#define END_DEVICE_PATH                END_DEVICE_PATH_TYPE
#define END_ENTIRE_SUBTYPE             END_ENTIRE_DEVICE_PATH_SUBTYPE

#define NEXT_NODE(pPath) ((EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(pPath)+NODE_LENGTH(pPath)))
#define NODE_LENGTH(pPath) ((pPath)->Length[0]+((pPath)->Length[1]<<8))
#define isEndNode(pDp) ((pDp)->Type==END_DEVICE_PATH)

#define NVME_SPEC_VS_1_1    0x10100       // Spec version value for 1.1 compliant controllers 
#define NVME_SPEC_VS_1_2_1  0x10201       // Spec version value for 1.2.1 compliant controllers 

#ifndef IS_ALIGNED
#define IS_ALIGNED(addr, size) (((addr) & (size - 1)) ? 0 : 1)
#endif

typedef struct {
    EFI_PEI_RECOVERY_BLOCK_IO_PPI  RecoveryBlkIo;
    UINT64                         AmiExtSig;
    BOOLEAN                        HaveEnumeratedDevices;
    UINTN                          TotalDeviceCount;
    UINTN                          TotalControllerCount;
    NVME_CONTROLLER_INFO           *NvmeControllerInfo[MAX_NVME_RECOVERY_DEVICE];
} NVME_RECOVERY_BLK_IO_DEV;

typedef struct {
    UINT8            BusNumber;
    UINT8            Device;
    UINT8            Function;
    BOOLEAN          IsMmioDevice;
    UINT64           BaseAddress;
    EFI_DEVICE_PATH  *DevPath;
} NVME_PCI_DEVICE_INFO;

EFI_STATUS
EFIAPI
Nvme_GetBlockDeviceMediaInfo (
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN  UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA        *MediaInfo
);

EFI_STATUS
EFIAPI
Nvme_ReadBlocks (
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN  UINTN                         DeviceIndex,
    IN  EFI_PEI_LBA                   StartLba,
    IN  UINTN                         BufferSize,
    OUT VOID                          *Buffer
);

EFI_STATUS
EFIAPI
Nvme_GetNumberOfBlockDevices(
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                         *NumberBlockDevices
);

EFI_STATUS
EFIAPI
NotifyOnNvmeRecoveryCapsuleLoaded (
    IN  EFI_PEI_SERVICES          **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN  VOID                      *InvokePpi
);

EFI_STATUS
EnumerateNvmeDevices(
    IN OUT NVME_RECOVERY_BLK_IO_DEV   *NvmeBlkIoDev
);

EFI_STATUS
InitializeNvmeController (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
);

VOID
PrintExecuteNvmeCmdData (
    IN NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
);

EFI_STATUS 
EFIAPI 
InstallPeiRecoveryBlkIoPpi ();

VOID* 
PeiDpAddNode (
    IN EFI_DEVICE_PATH *pDp1, 
    IN EFI_DEVICE_PATH *pDp2
);

UINTN 
PeiDpLength (
    IN EFI_DEVICE_PATH *pDp
);

VOID* 
PeiDpCopy (
    IN EFI_DEVICE_PATH *pDp
);

EFI_STATUS
InitAndConfigNvmeController (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
);

EFI_STATUS
ProgramPrpEntry(
    IN  NVME_CONTROLLER_INFO        *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER        *NvmeCmdWrapper,
    IN  UINTN                       TransferLength,
    IN  VOID                        *Buffer,
    IN  UINT64                      *Prp2List,
    OUT UINTN                       *BufferSize
);

EFI_STATUS
InstallNvmePassThruPpi(
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
);

ACTIVE_NAMESPACE_DATA*
GetActiveNameSpace (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo,
    IN UINT32               NamespaceId
);

#endif //_AMI_NVME_RECOVERY_H_
