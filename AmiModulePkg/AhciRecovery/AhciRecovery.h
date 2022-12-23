//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AhciRecovery.h
    Ahci Recovery function definition

**/
#ifndef _EFI_AHCI_RECOVERY_H_
#define _EFI_AHCI_RECOVERY_H_

#include    <Token.h>
#include    <Ppi/BlockIo2.h>
#include    <Ppi/EndOfPeiPhase.h>
#include    <Ppi/BootInRecoveryMode.h>
#include    "AhciCtrl.h"
#include    "AhciRecoveryElink.h"
#include    <IndustryStandard/Pci.h>
#include    <Library/PciLib.h>
#include    <Library/HobLib.h>
#include    <Library/IoLib.h>
#include    <Library/DebugLib.h>
#include    <Ppi/AmiPeiPciEnumeration.h>
#include    <Library/PeiServicesLib.h>
#include    <Library/MemoryAllocationLib.h>
#include    <Library/BaseMemoryLib.h>
#include    <Library/TimerLib.h>
#include    <Ppi/IoMmu.h>

#define AHCI_CLASS_CODE       0x01
#define AHCI_SUBCLASS_CODE    0x06
#define AHCI_HBA_PI           0x01
#define ABAR_OFFSET           0x24

#define AMI_EXTENSION_SIGNATURE        SIGNATURE_64('A', 'H','C','I','_','R','E','C')
#define END_DEVICE_PATH                END_DEVICE_PATH_TYPE
#define END_ENTIRE_SUBTYPE             END_ENTIRE_DEVICE_PATH_SUBTYPE

#define NEXT_NODE(pPath) ((EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(pPath)+NODE_LENGTH(pPath)))
#define NODE_LENGTH(pPath) ((pPath)->Length[0]+((pPath)->Length[1]<<8))
#define isEndNode(pDp) ((pDp)->Type==END_DEVICE_PATH)


EFI_STATUS
EFIAPI
AhciGetNumberOfBlockDevices (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI   *This,
    OUT UINTN                           *NumberBlockDevices
);

EFI_STATUS
EFIAPI
AhciGetBlockDeviceMediaInfo (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI   *This,
    IN  UINTN                           DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA          *MediaInfo
);

EFI_STATUS
EFIAPI
AhciReadBlocks (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI   *This,
    IN  UINTN                           DeviceIndex,
    IN  EFI_PEI_LBA                     StartLba,
    IN  UINTN                           BufferSize,
    OUT VOID                            *Buffer
);

EFI_STATUS
EFIAPI
AhciGetNumberOfBlockDevices2 (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI   *This,
    OUT UINTN                           *NumberBlockDevices
);

EFI_STATUS
EFIAPI
AhciGetBlockDeviceMediaInfo2 (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI   *This,
    IN  UINTN                           DeviceIndex,
    OUT EFI_PEI_BLOCK_IO2_MEDIA          *MediaInfo
);

EFI_STATUS
EFIAPI
AhciReadBlocks2 (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI   *This,
    IN  UINTN                           DeviceIndex,
    IN  EFI_PEI_LBA                     StartLba,
    IN  UINTN                           BufferSize,
    OUT VOID                            *Buffer
);

EFI_STATUS
AhciTestUnitReady (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo
);

EFI_STATUS
AhciAtapiReadSectors (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDevInfo,
    IN  OUT VOID                        *Buffer,
    IN  UINTN                           ByteCount,
    IN  UINT64                          LBA,
    IN  UINT32                          BlockSize
);

EFI_STATUS
DetectAtapiMedia (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo
);

EFI_STATUS
ExecutePacketCommand (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  COMMAND_STRUCTURE               *CommandStructure,
    IN  BOOLEAN                         READWRITE
);

EFI_STATUS
HandleAtapiError (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo
);

EFI_STATUS
EFIAPI
NotifyOnAhciRecoveryCapsuleLoaded (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
EFIAPI
InstallPeiRecoveryBlkIoPpi ();

EFI_STATUS
AhciEnumerateDevices (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  AHCI_RECOVERY_BLK_IO_DEV        *AhciBlkIoDev
);

EFI_STATUS
AhciInitController (
    IN  OUT AHCI_RECOVERY_CONTROLLER_INFO *AhciControllerInfo
);

EFI_STATUS
WaitForMemClear (
    IN  UINTN  BaseAddr,
    IN  UINT8  Port,
    IN  UINT8  Register,
    IN  UINT32 AndMask,
    IN  UINT32 WaitTimeInMs
);

EFI_STATUS
CheckDevicePresence (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort
);

EFI_STATUS
DetectAndConfigureDevice (
    IN  AHCI_RECOVERY_BLK_IO_DEV        *AhciBlkIoDev,
    IN   AHCI_RECOVERY_CONTROLLER_INFO  *AhciControllerInfo,
    IN  UINT8                            Port,
    IN  UINT8                            PMPort
);

EFI_STATUS
CheckPortImplemented (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port
);

EFI_STATUS
CheckValidDevice (
    IN  AHCI_RECOVERY_CONTROLLER_INFO    *AhciControllerInfo,
    IN  UINT8                            Port,
    IN  UINT8                            PMPort
);

EFI_STATUS
WaitForMemSet (
    IN  UINTN   BaseAddr,
    IN  UINT8   Port,
    IN  UINT8   Register,
    IN  UINT32  AndMask,
    IN  UINT32  TestValue,
    IN  UINT32  WaitTimeInMs
);

EFI_STATUS
GetIdentifyData (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort,
    IN  ATA_IDENTIFY_DATA               *AtaIdentifyData
);

EFI_STATUS
ExecutePioDataCommand (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  OUT COMMAND_STRUCTURE           *CommandStructure,
    IN  BOOLEAN                         READWRITE
);

EFI_STATUS
WaitforCommandComplete (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  COMMAND_TYPE                    CommandType,
    IN  UINTN                           TimeOut
);

EFI_STATUS
BuildCommandFIS (
    IN  AHCI_RECOVERY_DEVICE_INFO        *AhciRecDeviceInfo,
    IN  COMMAND_STRUCTURE                *CommandStructure,
    IN  AHCI_COMMAND_LIST                *CommandList,
    IN  AHCI_COMMAND_TABLE               *Commandtable
);

EFI_STATUS
BuildAtapiCMD(
    IN  AHCI_RECOVERY_DEVICE_INFO        *AhciRecDeviceInfo,
    IN  COMMAND_STRUCTURE                *CommandStructure,
    IN  AHCI_COMMAND_LIST                *CommandList,
    IN  AHCI_COMMAND_TABLE               *Commandtable
);

EFI_STATUS
BuildPRDT (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  COMMAND_STRUCTURE               *CommandStructure,
    IN  AHCI_COMMAND_LIST               *CommandList,
    IN  AHCI_COMMAND_TABLE              *Commandtable
);

EFI_STATUS
StartController (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  UINT32                          CIBitMask
);

EFI_STATUS
BuildCommandList (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  AHCI_COMMAND_LIST               *CommandList,
    IN  UINT64                          CommandTableBaseAddr
);

EFI_STATUS
ReadytoAcceptCmd (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo
);

EFI_STATUS
StopController (
    IN  AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN  BOOLEAN                         StartOrStop
);

EFI_STATUS
AhciAtaReadSectors (
    IN  AHCI_RECOVERY_DEVICE_INFO        *AhciRecDevInfo,    
    IN  OUT VOID                         *Buffer,
    IN  UINTN                            ByteCount,
    IN  UINT64                           LBA,
    IN  UINT32                           BlockSize
);

UINT32
ReadSCRRegister (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort,
    IN  UINT8                           Register
);

EFI_STATUS
WriteSCRRegister (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort,
    IN  UINT8                           Register,
    IN  UINT32                          Data32
);

EFI_STATUS
GeneratePortReset (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort,
    IN  UINT8                           Speed,
    IN  UINT8                           PowerManagement
);

EFI_STATUS
HandlePortComReset (
    IN  AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo,
    IN  UINT8                           Port,
    IN  UINT8                           PMPort
);

UINTN 
PeiDPLength (
    IN  EFI_DEVICE_PATH *pDp
);

VOID* 
PeiDPCopy (
    IN  EFI_DEVICE_PATH *pDp
);

VOID* 
PeiDPAddNode (
    IN EFI_DEVICE_PATH *pDp1, 
    IN EFI_DEVICE_PATH *pDp2
);

EFI_STATUS
ConfigureDevices (
    IN   AHCI_RECOVERY_CONTROLLER_INFO *AhciControllerInfo,
    IN   AHCI_RECOVERY_BLK_IO_DEV      *AhciBlkIoDev
);

#if RECOVERY_DATA_PORT_ACCESS
UINT32
ReadDataDword(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
);

UINT16
ReadDataWord(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
);

UINT8
ReadDataByte(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index
);

VOID
WriteDataDword(
    IN  UINTN   BaseAddr,
    IN  UINTN   Index,
    IN  UINTN   Data
);

VOID
WriteDataWord (
    IN  UINTN   BaseAddr,
    IN  UINTN   Index,
    IN  UINTN   Data
);

VOID
WriteDataByte (
    IN  UINTN   BaseAddr,
    IN  UINTN   Index,
    IN  UINTN   Data
);
#endif

VOID
PrintAhciCapability  (
  IN AHCI_RECOVERY_CONTROLLER_INFO     *AhciControllerInfo
); 

VOID
PrintCommandFIS (
  IN COMMAND_STRUCTURE    *CommandStructure
) ;

EFI_STATUS
CreateSataDevicePath (
    IN   AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN   AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo
);
#endif //_EFI_AHCI_RECOVERY_H_
