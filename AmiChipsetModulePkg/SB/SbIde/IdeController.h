//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file IdeController.h
    Initialize and provide a protocol for the Ide controller.


**/
//**********************************************************************

#ifndef _SBIDE_CONTROLLER_H_
#define _SBIDE_CONTROLLER_H_

//--------------------------------------------
// Aptio definition
//--------------------------------------------
#include <Token.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Pci.h>
#include <Sb.h>
#include <Library/SbPolicy.h>

#include <Library/DebugLib.h>

//--------------------------------------------
// Produce Protocol
//--------------------------------------------
#include <Protocol/IdeControllerInit.h>
#include <Protocol/ComponentName.h>
//--------------------------------------------
// Consume Protocol
//--------------------------------------------
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/DevicePath.h>
#include <Protocol/DriverBinding.h>

#include <AhciBus.h>

// Attention !!!
// Old Protocol should be remove ..\Include\Protocol\PIDEController.h
// But the CSM use this protocol for SATA. This is same as PIDEController.h define.
#define SATA_CONTROLLER_PROTOCOL_GUID \
        { 0x2acb6627, 0xdf02, 0x4e23, 0xb4, 0xf9, 0x6a, 0x93, 0xfa, 0x6e, 0x9d, 0xa6 }

//--// {11D3B055-DDF4-4ecf-B28D-4D0D314ED33D}
//--DEFINE_GUID(<<name>>,
//--0x11d3b055, 0xddf4, 0x4ecf, 0xb2, 0x8d, 0x4d, 0xd, 0x31, 0x4e, 0xd3, 0x3d);
#define PATA_CONTROLLER_GUID \
{0x11d3b055, 0xddf4, 0x4ecf, 0xb2, 0x8d, 0x4d, 0xd, 0x31, 0x4e, 0xd3, 0x3d}

//
// SATA controller
//
#ifdef SB_SATA_CONTROLLER
//---#define CONTROLLER_DRIVER_GUID      SATA_CONTROLLER_DRIVER_GUID
// ..\Include\Protocol\PIDEController.h
// The CSM use this protocol for SATA
#define CONTROLLER_DRIVER_GUID      SATA_CONTROLLER_PROTOCOL_GUID
#define IDE_ENUMER_ALL              FALSE
#define CONTROLLER_SIGNATURE        SIGNATURE_32('S','A','T','A')
#endif
//
// PATA controller
//
#ifdef SB_PATA_CONTROLLER
#define CONTROLLER_DRIVER_GUID      PATA_CONTROLLER_GUID
#define IDE_ENUMER_ALL              FALSE
#define CONTROLLER_SIGNATURE        SIGNATURE_32('P','A','T','A')
#endif

#define AMDSB_CLASS_CODE_AHCI       0x6
#define AMDSB_CLASS_CODE_RAID       0x4

#define CONTROLLER_MAX_CHANNELS         0x2
#define CONTROLLER_MAX_CHANNELS_AHCI    MAX_AHCI_CHANNEL
#define CONTROLLER_MAX_DEVICES          0x2

#define SBIDE_MAX_CHANNELS     CONTROLLER_MAX_CHANNELS_AHCI
#define SBIDE_MAX_DEVICES      2

//
// Ide controller driver private data structure
//
typedef struct _EFI_SBIDE_CONTROLLER_PRIVATE_DATA {
  //
  // Standard signature used to identify Ide controller private data
  //
  UINT32                     Signature;

  //
  // Protocol instance of IDE_CONTROLLER_INIT produced by this driver
  //
  EFI_IDE_CONTROLLER_INIT_PROTOCOL    IdeInit;

  //
  // copy of protocol pointers used by this driver
  //
  EFI_PCI_IO_PROTOCOL        *PciIo;

  //
  // The highest disqulified mode for each attached Ide device.
  // Per ATA/ATAPI spec, if a mode is not supported, the modes higher than
  // it should not be supported
  //
  EFI_ATA_COLLECTIVE_MODE DisqulifiedModes[SBIDE_MAX_CHANNELS][SBIDE_MAX_DEVICES];

  //
  // A copy of IDENTIFY data for each attached Ide device and its flag
  //
  EFI_IDENTIFY_DATA IdentifyData[SBIDE_MAX_CHANNELS][SBIDE_MAX_DEVICES];
  BOOLEAN  IdentifyValid[SBIDE_MAX_CHANNELS][SBIDE_MAX_DEVICES];
} EFI_SBIDE_CONTROLLER_PRIVATE_DATA;

#define SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS(a) BASE_CR(a, EFI_SBIDE_CONTROLLER_PRIVATE_DATA, IdeInit)

typedef struct {
    UINT64                  Address;
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;

//-------------------------------------------------------
// Driver binding functions declaration
//-------------------------------------------------------

EFI_STATUS
EFIAPI
SbIdeControllerSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL       *This,
  IN EFI_HANDLE                        Controller,
  IN EFI_DEVICE_PATH_PROTOCOL          *RemainingDevicePath
  );


EFI_STATUS
EFIAPI
SbIdeControllerStart (
  IN EFI_DRIVER_BINDING_PROTOCOL        *This,
  IN EFI_HANDLE                         Controller,
  IN EFI_DEVICE_PATH_PROTOCOL           *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
SbIdeControllerStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL       *This,
  IN  EFI_HANDLE                        Controller,
  IN  UINTN                             NumberOfChildren,
  IN  EFI_HANDLE                        *ChildHandleBuffer
  );

//-------------------------------------------------------
// IDE controller init functions declaration
//-------------------------------------------------------

EFI_STATUS
IdeInitGetChannelInfo(
  IN   EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN   UINT8                               Channel,
  OUT  BOOLEAN                             *Enabled,
  OUT  UINT8                               *MaxDevices
  );

EFI_STATUS
IdeInitNotifyPhase(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  EFI_IDE_CONTROLLER_ENUM_PHASE     Phase,
  OUT UINT8                             Channel
  );

EFI_STATUS
IdeInitSubmitData(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  UINT8                             Channel,
  IN  UINT8                             Device,
  IN  EFI_IDENTIFY_DATA                 *IdentifyData
  );

EFI_STATUS
IdeInitSubmitFailingModes(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  UINT8                             Channel,
  IN  UINT8                             Device
  );

EFI_STATUS
IdeInitDisqualifyMode(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  UINT8                             Channel,
  IN  UINT8                             Device,
  IN  EFI_ATA_COLLECTIVE_MODE           *BadModes
  );

EFI_STATUS
IdeInitCalculateMode(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  UINT8                             Channel,
  IN  UINT8                             Device,
  IN  EFI_ATA_COLLECTIVE_MODE           **SupportedModes
);

EFI_STATUS
IdeInitSetTiming(
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  UINT8                             Channel,
  IN  UINT8                             Device,
  IN  EFI_ATA_COLLECTIVE_MODE           *Modes
);

EFI_STATUS
CalculateBestPioMode (
  IN  EFI_IDENTIFY_DATA      * IdentifyData,
  IN  UINT16                 *DisPioMode OPTIONAL,
  OUT UINT16                 *SelectedMode
  );

EFI_STATUS
CalculateBestUdmaMode (
  IN  EFI_IDENTIFY_DATA      * IdentifyData,
  IN  UINT16                 *DisUDmaMode OPTIONAL,
  OUT UINT16                 *SelectedMode
  );

//-------------------------------------------------------
// Component Name Protocol
//-------------------------------------------------------

EFI_STATUS
IdeControllerGetDriverName (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
);

EFI_STATUS
IdeControllerGetControllerName (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  EFI_HANDLE                   ControllerHandle,
  IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **ControllerName
  );

//-------------------------------------------------------
// External function definitions
//-------------------------------------------------------
EFI_STATUS
IdeControllerCheck (
  IN EFI_PCI_IO_PROTOCOL   *PciIo
  );

EFI_STATUS
InitIdeController (
  IN EFI_PCI_IO_PROTOCOL      *PciIo
  );

EFI_STATUS
IdeInitSetUdmaTiming (
  IN  UINT8                       Channel,
  IN  UINT8                       Device,
  IN  EFI_PCI_IO_PROTOCOL         *PciIo,
  IN  EFI_ATA_COLLECTIVE_MODE     *Modes
  );

EFI_STATUS
IdeInitSetPioTiming (
  IN  UINT8                       Channel,
  IN  UINT8                       Device,
  IN  EFI_PCI_IO_PROTOCOL         *PciIo,
  IN  EFI_IDENTIFY_DATA           *IdentifyData,
  IN  EFI_ATA_COLLECTIVE_MODE     *Modes
  );

VOID MultiCallBack(IN EFI_EVENT Event, IN VOID *Context);

EFI_STATUS
UserIdeMode(
  IN SB_SETUP_DATA                  *SetupData,
  IN  UINT8                         Channel,
  IN  UINT8                         Device,
  IN OUT EFI_ATA_COLLECTIVE_MODE    **SupportedModes
  );

UINT8 GetMaxChannels(VOID);

VOID PciIoCallBackScriptSave(VOID);
VOID ReadyToBootCallBackScriptSave(VOID);

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
