//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NbCspLib.h
    This file contains definitions for NB Chipset Library

**/
#ifndef __NBLIB_H__
#define __NBLIB_H__

#include <Efi.h>
#include <Pei.h>
#include <Protocol/PciHostBridgeResourceAllocation.h>
#include <Protocol/PciRootBridgeIo.h>
#include <PciHostBridge.h>
#include <AmiDxeLib.h>
#if PCI_BUS_REVISION <= 16
#include <PciBus.h>
#endif
#include <Protocol/S3SaveState.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    UINT8     ChannelNumber;  //< Zero based channel number.
    UINT8     DimmNumber;     //< Zero based DIMM number.
    UINT8     Rank;           //< Zero based rank number.
    UINT8     Bank;           //< Zero based bank number.
    UINT16    Cas;            //< Zero based CAS number.
    UINT32    Ras;            //< Zero based RAS number.
} NB_ADDRESS_DECODE;


BOOLEAN NbCheckVtdSupport (
    VOID
);

BOOLEAN NbIsDualChannel (
    IN UINT8              MemoryChannelType
);

EFI_STATUS NbLockPavpc (
    IN BOOLEAN            MODE
);

EFI_STATUS NbGetDimmLocInfo (
    IN CONST UINTN        MemoryAddr,
    OUT NB_ADDRESS_DECODE *NbAddressDecode
);

EFI_STATUS NbPamWriteBootScript(
    IN EFI_S3_SAVE_STATE_PROTOCOL    *BootScriptSave
);

//To Exclude AMI Native Root Bridge Driver HOOKS from CSP LIB
#include <Token.h>
#if AMI_ROOT_BRIDGE_SUPPORT == 1

//***********************************************************************
//-----------------------------------------------------------------------
//Function Prototypes for PciRootBridgeIo
//-----------------------------------------------------------------------
//***********************************************************************
extern DXE_SERVICES     *gDxeSvcTbl;


EFI_STATUS HbResAllocNotifyPhase(
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PHASE            Phase );

EFI_STATUS HbResAllocGetNextRootBridge(
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
    IN OUT EFI_HANDLE                                           *RootBridgeHandle);

EFI_STATUS HbResAllocGetAllocAttributes(
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
    IN EFI_HANDLE                                               RootBridgeHandle,
    OUT UINT64                                                  *Attributes);

EFI_STATUS HbResAllocStartBusEnumeration(
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
    IN EFI_HANDLE                                               RootBridgeHandle,
    OUT VOID                                                    **Configuration);

EFI_STATUS HbResAllocSetBusNumbers(
        IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL     *This,
        IN EFI_HANDLE                                           RootBridgeHandle,
        IN VOID                                                 *Configuration);

EFI_STATUS HbResAllocSubmitResources(
        IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
        IN EFI_HANDLE                                               RootBridgeHandle,
        IN VOID                                                     *Configuration);
EFI_STATUS HbResAllocGetProposedResources(
        IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
        IN EFI_HANDLE                                               RootBridgeHandle,
        OUT VOID                                                    **Configuration);

EFI_STATUS HbResAllocPreprocessController(
        IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL         *This,
        IN EFI_HANDLE                                               RootBridgeHandle,
        IN EFI_PCI_CONFIGURATION_ADDRESS                            PciAddress,
        IN EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE             Phase);

EFI_STATUS HbCspAllocateResources( PCI_HOST_BRG_DATA *HostBrgData,
                                PCI_ROOT_BRG_DATA *RootBrgData,
                                UINTN RootBrgIndex);

//***********************************************************************
//Chipset hooks function Prototypes

//***********************************************************************
//  This hooks will be called from Notify Phase Host Bridge Resource 
//  Allocation Protocol member function 
//***********************************************************************
//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeBeginEnumeration
EFI_STATUS HbNotifyCspBeforeEnumeration(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeBeginBusAllocation
EFI_STATUS HbNotifyCspBeginBusAllocation(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeEndBusAllocation
EFI_STATUS HbNotifyCspEndBusAllocation(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeBeginResourceAllocation
EFI_STATUS HbNotifyCspBeginResourceAllocation(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeAllocateResources
EFI_STATUS HbNotifyCspAllocateResources(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeSetResources
EFI_STATUS HbNotifyCspSetResources(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol when NotifyPhase function is called
//with phase EfiPciHostBridgeEndResourceAllocation
EFI_STATUS HbNotifyCspEndResourceAllocation(
        EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
        UINTN                                               RbCount );

//***********************************************************************
//  This hooks will be called from Other Host Bridge Resource 
//  Allocation Protocol member functions
//***********************************************************************

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol StartBusEnumeration function
EFI_STATUS HbCspStartBusEnumeration(
        PCI_HOST_BRG_DATA *HostBrgData,PCI_ROOT_BRG_DATA *RootBrgData,UINTN RootBrgIndex);

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol SetBusNumbers function
EFI_STATUS HbCspSetBusNnumbers(
        PCI_HOST_BRG_DATA *HostBrgData,PCI_ROOT_BRG_DATA *RootBrgData,UINTN RootBrgIndex);

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol SubmitResources function
EFI_STATUS HbCspSubmitResources(
        PCI_HOST_BRG_DATA *HostBrgData,PCI_ROOT_BRG_DATA *RootBrgData,UINTN RootBrgIndex);

//-----------------------------------------------------------------------
//CSP Function invoked in PCI Host Bridge Protocol SubmitResources function
EFI_STATUS HbCspAdjustMemoryMmioOverlap(
        PCI_HOST_BRG_DATA *HostBrgData,PCI_ROOT_BRG_DATA *RootBrgData,UINTN RootBrgIndex);

//-----------------------------------------------------------------------
//BASIC Chipset initialization function calle after Initialization of generic part of the 
//Host and Root Bridges. All Handles for PCIHostBrg and PciRootBrg has been created and 
//Protocol Intergaces installed
//Need to update this function from Aptio core Version 4.6.2 onwards
//##<AAV>###if ((CORE_MINOR_VERSION >=6) && (CORE_REVISION > 1))
#if (CORE_COMBINED_VERSION > 0x4028B)
EFI_STATUS HbCspBasicChipsetInit(PCI_HOST_BRG_DATA *HostBrg0);
#else
EFI_STATUS HbCspBasicChipsetInit( IN  EFI_HANDLE              ImageHandle,PCI_HOST_BRG_DATA *HostBrg0);
#endif

//-----------------------------------------------------------------------
//Csp Function which will return PCI Segment Number for 
//Chipsets that capable of having multiple PCI segments
//Parameters UINTN  HostNumber, UINTN RootNumber is ZERO based
UINTN HbCspGetPciSegment(UINTN  HostBridgeNumber, UINTN RootBridgeNumber);

//-----------------------------------------------------------------------
//Csp Function which will be called each time PciBus Enumerator finds Pci Device
//on the bus. This Function will allow to program particular device registers before
//resource requirements are collected from that device.
EFI_STATUS HbCspPreprocessController(PCI_HOST_BRG_DATA *HostBrgData, PCI_ROOT_BRG_DATA *RootBrgData, 
                                UINTN RootBrgNumber, EFI_PCI_CONFIGURATION_ADDRESS PciAddress, 
                                EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE Phase);



//-----------------------------------------------------------------------
//Chipset Specific function to Map Internal Device address 
//residing ABOVE 4G to the BELOW 4G address space for DMA. 
//MUST BE IMPLEMENTED if CHIPSET supports address space 
//decoding ABOVE 4G.
EFI_STATUS RbCspIoPciMap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
    IN EFI_PHYSICAL_ADDRESS                         HostAddress,
    IN OUT UINTN                                    *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
    OUT VOID                                        **Mapping);

//-----------------------------------------------------------------------
//Chipset Specific function to UnMap result of previouse PciRbIo->Map
//operation
EFI_STATUS RbCspIoPciUnmap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN PCI_ROOT_BRIDGE_MAPPING                      *Mapping);

//-----------------------------------------------------------------------
//Chipset Specific function to Sets attributes for a resource range 
//on a PCI root bridge.
EFI_STATUS RbCspIoPciAttributes(PCI_ROOT_BRG_DATA *RbData,
                                IN     UINT64   Attributes,
                                IN OUT UINT64   *ResourceBase OPTIONAL,
                                IN OUT UINT64   *ResourceLength OPTIONAL);

//-----------------------------------------------------------------------
//Csp Function which actualy access PCI Config Space
//Chipsets that capable of having PCI EXPRESS Ext Cfg Space transactions 
//Must Implement this access routine here
EFI_STATUS RootBridgeIoPciRW (
    IN VOID                                     *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
    IN UINT64                                   Address,
    IN UINTN                                    Count,
    IN OUT VOID                                 *Buffer,
    IN BOOLEAN                                  Write);


//Pci RB CSP function prototypes
EFI_STATUS RbCspIoPciUnmap (
    IN  PCI_ROOT_BRG_DATA                           *RbData, 
    OUT PCI_ROOT_BRIDGE_MAPPING                     *Mapping);

EFI_STATUS RbCspIoPciMap (
    IN PCI_ROOT_BRG_DATA                            *RbData,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation,
    IN EFI_PHYSICAL_ADDRESS                         HostAddress,
    IN OUT UINTN                                    *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
    OUT VOID                                        **Mapping);

//--------------------------------------
//#if AMI_ROOT_BRIDGE_SUPPORT == 1
#endif 
#ifdef __cplusplus
}
#endif
#endif


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
