//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file PeiPciEnumeration.h
    This file contains the structures definitions required for PeiPciEnumeration
**/
#ifndef __PEI_PCI_ENUMERATION__H__
#define __PEI_PCI_ENUMERATION__H__

#include  <Token.h>
#include  <Base.h>
#include  <Uefi.h>
#include  <Library/BaseLib.h>
#include  <Library/PeiServicesLib.h>
#include  <Library/PciSegmentLib.h>
#include  <Library/PciLib.h>
#include  <Library/PcdLib.h>
#include  <Library/HobLib.h>
#include  <Library/DebugLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Ppi/AmiPeiPciEnumeration.h>
#include  <Ppi/AmiPeiPciResetResources.h>
#include  <PeiPciEnumerationElink.h>
#include  <IndustryStandard/Pci.h>

// PCI 2 PCI Bridge Config
#define PCI_IOBASE                      0x001C  // I/O base Register
#define PCI_IOLIMIT                     0x001D  // I/O Limit Register
#define PCI_MEMBASE                     0x0020  // Memory Base Register
#define PCI_MEMLIMIT                    0x0022  // Memory Limit Register
#define PEI_PCI_MAX_SUBORDINATE_NUMBER  0x10
#define P2P_BRG_MEM_GRA                 0xFFFFF //naturally, P2P Brg MMIO aligned to the 1M boundary
#define P2P_BRG_IO_GRA                  0xFFF   //naturally, P2P Brg IO aligned to the 4k boundary

#define NEXT_NODE(pPath)                ((EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(pPath)+NODE_LENGTH(pPath)))
#define NODE_LENGTH(pPath)              ((pPath)->Length[0]+((pPath)->Length[1]<<8))
#define isEndNode(pDp)                  ((pDp->Type == END_DEVICE_PATH_TYPE) && (pDp->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE))

#ifndef DEVICE_ID_NOCARE
#define DEVICE_ID_NOCARE                0xFFFF
#endif

/**
    This ENUM definition used to identify PCI Device different BAR types

    @note  Don't cange the order! Some PCI Bus internal routines rely on it!

 Fields:        
    Name                Type            Description
   ------------------------------------------------------------------
    tPciUnknown         ENUM            PCI Bus Driver wasn't able to Identify the Device
    tPciRootBrg         ENUM            Device is a PCI Root Bridge Device (A virtual device the root of PCI tree)
    tPci2PciBrg         ENUM            Device is a PCI to PCI Bridge Device
    tUncompatibleDevice ENUM            Device is an Uncompatible PCI Device
    tPciMaxDevice       ENUM            Last valid value of this ENUM 
**/
typedef enum {
    tPciUnknown = 0,
    tPciRootBrg,         //1
    tPci2PciBrg,         //2
    tPciDevice,          //3
    tUncompatibleDevice, //4
    tPciMaxDevice        //5
} PEI_PCI_DEVICE_TYPE;

/**
    This ENUM value used to identify PCI Device different BAR types.

 Fields:        
    Name            Type                    Description
   ------------------------------------------------------------------
    tBarUnused      ENUM    BAR is not used to Specify Device Resources(empty)
    tBarMmio32      ENUM    BAR is used to Specify Device's MMIO 32bit Resources
    tBarMmio64      ENUM    BAR is used to Specify Device's MMIO 64bit Resources
    tBarIo          ENUM    BAR is used to Specify Device's IO Resources.
    tBarMem         ENUM    A superset of PCI_BAR_TYPE tBarMmio32 and tBarMmio64
    tBarMaxType     ENUM    Last valid value of this ENUM 
**/
typedef enum {
    tBarUnused = 0,
    tBarIo16,       //1
    tBarIo32,       //2
    tBarMmio32,     //3
    tBarMmio64,     //4
    tBarIo,         //5
    tBarMem,        //6
    tBarMaxType     //7
} PEI_PCI_BAR_TYPE;

#pragma pack(1)

typedef struct {
    UINT8    BaseClassCode;
    UINT8    SubClassCode;
    UINT8    ProgrammingInterface;
    UINT8    BarIndex;
} PCI_DEVICE_CLASSCODE_ENTRY;

typedef struct {
    UINT8       Segment;
    UINT8       BusBase;
    UINT8       BusLimit;
    UINT16      PciResourceIoBase;
    UINT16      PciResourceIoLimit;
    UINT32      PciResourceMemBase;
    UINT32      PciResourceMemLimit;
} PCI_ROOT_BRIDGE_RESOURCE;

/**
    This Structure used to store information about PCI Device 
    Base Address Register (BAR)

 Fields:        
    Name            Type                    Description
   ------------------------------------------------------------------
    Type            PCI_BAR_TYPE        Type of PCI Device BAR may be converted
    Base            UINT64              Base Address of the Resource assigned to this BAR
    Length          UINT64              Length of the Resource assigned to this BAR in bytes
    Gran            UINT64              Granularity of the Resource assigned to this BAR - a value that was read back after all ONEs was applied to the BAR.
    Offset          UINT8               Offset of the PCI Configuration Space where this bar Located 
**/
typedef struct {
    PEI_PCI_BAR_TYPE          Type;
    UINT64                    Base;
    UINT64                    Length;
    UINT64                    Gran;
    UINT8                     Offset; //offset of this bar register in PCI_CFG space 
} PEI_PCI_BAR;

/**
 * This Structure will contain information about the discovered
 * Pci Root Bridge, Pci2Pci Bridge or Pci Devices.
 */

typedef struct _PEI_PCI_DEV_INFO PEI_PCI_DEV_INFO;

struct _PEI_PCI_DEV_INFO {
    PEI_PCI_DEVICE_TYPE             Type;       ///Identifies the device
    UINT8                           Segment;
    UINT8                           Bus;
    UINT8                           Device;
    UINT8                           Function;            
    BOOLEAN                         SkipDevice;
    PEI_PCI_DEV_INFO                *ParentBridge;
    PEI_PCI_BAR                     Bar;
    BOOLEAN                         IsBarProgrammed;
    BOOLEAN                         IsBarPreProgrammed;
    AMI_PEI_PCI_CLASSCODE           PciDeviceClass;
    EFI_DEVICE_PATH                 *DevPath;
    LIST_ENTRY                      Link;
};

/**
 * This Structure will contain Additional or Extended information about the discovered
 * for a PCI Root Bridge, Pci2Pci Bridge. This will be always followed by the corresponding
 * PCI_DEVICE_INFO structure of the PCI Root Bridge or Pci2Pci Bridge.
 */
typedef struct {
    UINT8        Segment;
    UINT8        PrimaryBusNumber;
    UINT8        SecondaryBusNumber;
    UINT8        SubordinateBusNumber;
    BOOLEAN      BridgeProgrammed;
    BOOLEAN      BridgePreProgrammed;
    UINT32       RbIoBase;
    UINT32       RbIoLimit;
    UINT32       IoBase;
    UINT64       RbMmioBase;
    UINT64       RbMmioLimit;
    UINT64       MmioBase;
    UINT32       IoBaseLength;
    UINT64       MmioBaseLength;
    UINT32       IoGranularity;
    UINT64       MmioGranularity;
    UINT8        RbIndex;
    UINT8        ChildDeviceCount;
    LIST_ENTRY   ResourceExceptionList;
    LIST_ENTRY   BusExceptionList;
    UINT8        ChildBridgeCount;
} PEI_PCI_BRIDGE_INFO_EXT;

typedef struct{
    PEI_PCI_BAR  Bar;
    LIST_ENTRY   Link;
} PCI_RESOURCE_EXCEPTION;

typedef struct{
    UINT8        BusBase;
    UINT8        BusLimit;
    UINT64       MmioBase;
    UINT64       MmioLimit;
    UINT32       IoBase;
    UINT32       IoLimit;
    LIST_ENTRY   Link;
}PCI_BUS_EXCEPTION;
/**
 * This Structure will contain the Private Data for Pei Pci Enumeration.
 * 
 */

typedef struct {
    AMI_PEI_PCI_ENUMERATION_PPI             PeiPciEnumerationPpi;
    BOOLEAN                                 HaveEnumeratedDevices;
    UINTN                                   PciDeviceCount;
    LIST_ENTRY                              PciDeviceList;
    BOOLEAN                                 DeviceResetDone;
} PEI_PCI_ENUMERATION_PRIVATE_DATA;

#pragma pack()

EFI_STATUS 
EnumerateBus(
    EFI_DEVICE_PATH                       *ParentDp,
    PEI_PCI_ENUMERATION_PRIVATE_DATA      *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                      *ParentBridge
);

BOOLEAN
IsAllowedClassCodeDevice (
    IN  UINT64                 PciAddr,
    IN  AMI_PEI_PCI_CLASSCODE  *PciClassCode, 
    OUT UINT8                  *BarOffset,
    IN OUT BOOLEAN             *IsProgrammed
);

EFI_STATUS 
QueryPciDeviceResources(
    PEI_PCI_DEV_INFO                    *ParentBridge
);

EFI_STATUS 
CalculateBridgeResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge
);

EFI_STATUS 
AssignBridgeResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge
);

EFI_STATUS 
GetNextMaxGranDevUnderBridge(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge,
    PEI_PCI_BAR_TYPE                    ResourceType,
    UINT64                              *MaxGranularity,
    PEI_PCI_DEV_INFO                    **MaxGranPciDeviceInfo
); 

EFI_STATUS 
AssignDeviceResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge,
    PEI_PCI_BAR_TYPE                    ResourceType
);

EFI_STATUS
EFIAPI 
PeiPciNotifyOnEndOfPei (
    IN  EFI_PEI_SERVICES          **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN  VOID                      *InvokePpi
);

VOID 
FindChildBridgesLength (
    PEI_PCI_ENUMERATION_PRIVATE_DATA     *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                     *ParentBridge,
    UINT32                               *ChildBridgeIoLength, 
    UINT64                               *ChildBridgeMmioLength
);

/**
    PeiDevicePathAddNode adds the very first element of pDp2 to pDp1 just 
    before its device path terminator. 

    @param  pDp1  - Pointer to device path 
    @param  pDp2  - Pointer to device path
    
    @retval Address of the newly allocated modified device path
    
    @note
    1.pDp1 is the device path to be appended to pDp2
    2.Device Path read from pDp2, and its very first element will be 
      appended to pDp1.
**/
VOID * 
PeiDevicePathAddNode (
  IN EFI_DEVICE_PATH                *pDp1, 
  IN EFI_DEVICE_PATH                *pDp2
);

/**    
    PeiDevicePathLength Finds length of the provided device path, 
    (including the size of EndOfDevicePath).
    
     @param  Dp
     
     @retval Size of the device path, Dp, including EndOfDevicePath.
 **/
UINTN 
PeiDevicePathLength (
  IN  EFI_DEVICE_PATH       *Dp
);

/**
    PeiDevicePathCopy copies the user provided device path into a new buffer and
    returns its address.
    
    @param  pDp
    
    @retval Address of the new copy of pDp
**/
VOID* 
PeiDevicePathCopy (
  IN  EFI_DEVICE_PATH       *Dp
);

PEI_PCI_BRIDGE_INFO_EXT*
GetRootBridgeExtPtr(
    PEI_PCI_DEV_INFO    *PciDeviceInfo
);

BOOLEAN
CheckIfResourcePresent(
    PEI_PCI_BRIDGE_INFO_EXT     *RootBridgeExtInfo,
    UINT64                      BaseAddr,
    UINT64                      Length,
    PEI_PCI_BAR_TYPE            Type
);

/**
    Routine returns Root Bridge count
    
    @param  None
    
    @return UINT8
**/
UINT8
GetRootBridgeCount (
);

/**
    Routine returns Root Bridge's resources based on Root Bridge Index
    
    @param  RbIndex
    @param  RbResource
    
    @return EFI_STATUS
**/
EFI_STATUS
GetResourceForRootBridge (
    IN   UINT8                       RbIndex,
    OUT  PCI_ROOT_BRIDGE_RESOURCE    *RbResource
);

/**
   Certain PCI controllers requires additional Initialization before
   Enumerating the device. This routine will help to do initialization
   
   @param Segment
   @param Bus
   @param Device
   @param Function
   @param VendorId
   @param DeviceId
   
   @return None
 */
VOID
ProcessPreEnumerationInit (
    IN UINT8                   Segment,
    IN UINT8                   Bus,
    IN UINT8                   Device,
    IN UINT8                   Function,
    IN UINT16                  VendorId, 
    IN UINT16                  DeviceId
);

#endif
