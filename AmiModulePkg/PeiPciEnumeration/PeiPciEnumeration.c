//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file PeiPciEnumeration.c
    This file contains the code to implement
    AMI_PEI_PCI_ENUMERATION_PPI for doing PCI bridge Enumeration.

**/

#include "PeiPciEnumeration.h"

UINT8     gLastUsedBusNumber = 0;

EFI_DEVICE_PATH            *gAcpiDp;

// ACPI Device Path filled with Default values.
ACPI_HID_DEVICE_PATH       gPeiAcpiPath = {
  {
   ACPI_DEVICE_PATH,
   ACPI_DP,
   {sizeof(ACPI_HID_DEVICE_PATH),0}
  },
  EISA_PNP_ID(0x0A03),
  0
};

PCI_DEVICE_PATH            gPeiPciPath = {
  {
   HW_PCI_DP,
   HARDWARE_DEVICE_PATH,
   {sizeof( PCI_DEVICE_PATH ),0}
  },
  0,
  0
};

static 
EFI_DEVICE_PATH            gEndOfDevicePathNode = {
  END_DEVICE_PATH_TYPE, 
  END_ENTIRE_DEVICE_PATH_SUBTYPE,
  {sizeof(EFI_DEVICE_PATH),0}
};

static
EFI_PEI_NOTIFY_DESCRIPTOR EndOfPeiNotifyList = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiEndOfPeiSignalPpiGuid,
    PeiPciNotifyOnEndOfPei
};

static 
EFI_PEI_PPI_DESCRIPTOR gPeiPciResetResourcesDescriptor = {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmiPeiPciResetResourcesPpiGuid,
    NULL
};


/**
    PeiDevicePathCopy copies the user provided device path into a new buffer and
    returns its address.
    
    @param  pDp
    
    @retval Address of the new copy of pDp
**/
VOID* 
PeiDevicePathCopy (
  IN  EFI_DEVICE_PATH       *Dp
)
{
    UINTN                   Length;
    UINT8                   *Ptr;
    
    if (!Dp) {
        return NULL;
    }
    
    Length = PeiDevicePathLength(Dp);
    
    Ptr = AllocateZeroPool(Length);   
    
    if(Ptr != NULL) {
        CopyMem (Ptr, Dp, Length);
    }
    return Ptr;
}

/**    
    PeiDevicePathLength Finds length of the provided device path, 
    (including the size of EndOfDevicePath).
    
     @param  Dp
     
     @retval Size of the device path, Dp, including EndOfDevicePath.
 **/
UINTN 
PeiDevicePathLength (
  IN  EFI_DEVICE_PATH       *Dp
)
{
    UINTN                   Size = 0;
    UINTN                   Length;
    
    if (!Dp) {
        return 0;
    }
    
    for(; !isEndNode(Dp); Dp = NEXT_NODE(Dp)) {
        Length = NODE_LENGTH(Dp);
        //Protection from the junk data.
        //Zero type and zero length are illegal.
        //If we encountered them, return
        if (!Dp->Type || !Length) {
            return Size;
        }
        Size += Length;
    }
    return Size + sizeof(EFI_DEVICE_PATH); // add size of END_DEVICE_PATH node
}

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
)
{
    UINTN                           Length;
    UINT8                           *NewDp;
    UINT8                           *Ptr;
        
    if (!pDp2) {
        return (pDp1)? PeiDevicePathCopy(pDp1) : PeiDevicePathCopy(&gEndOfDevicePathNode);
    }
    
    Length = pDp1 ? PeiDevicePathLength(pDp1) - sizeof(EFI_DEVICE_PATH) : 0;
    
    NewDp = AllocateZeroPool((Length + NODE_LENGTH(pDp2) + sizeof(EFI_DEVICE_PATH)));
    if(NewDp == NULL) {
        return NULL;
    }
    
    Ptr = NewDp;

    if (Length) { 
        CopyMem (Ptr, pDp1, Length); 
        Ptr += Length; 
    }
    
    CopyMem (Ptr, pDp2, NODE_LENGTH(pDp2)); 
    Ptr += NODE_LENGTH(pDp2);
    
    CopyMem (Ptr, &gEndOfDevicePathNode, sizeof(EFI_DEVICE_PATH)); 
    return NewDp;
}

/**
    This routine resets the resources allocated for the available controllers 
    and the PCI to PCI Bridge at end of PEI.

    @param PeiServices 
    @param NotifyDesc 
    @param InvokePpi 

         
    @retval EFI_STATUS this function returns EFI_SUCCESS if the
        PCI Device is reset successfully. Otherwise, returns
        any type of error it encountered during the reset operation.
              
**/
EFI_STATUS
EFIAPI 
PeiPciNotifyOnEndOfPei (
    IN  EFI_PEI_SERVICES             **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDesc,
    IN  VOID                         *InvokePpi
)
{
    AMI_PEI_PCI_ENUMERATION_PPI       *PeiPciEnumerationPpi;
    EFI_STATUS                        Status;
    PEI_PCI_ENUMERATION_PRIVATE_DATA  *PeiPciPrivateData;
    
    Status = PeiServicesLocatePpi(&gAmiPeiPciEnumerationPpiGuid,
                                  0,
                                  NULL,
                                  (VOID**)&PeiPciEnumerationPpi);
    if(EFI_ERROR(Status)) {
        return Status;
    }
    
    PeiPciPrivateData = (PEI_PCI_ENUMERATION_PRIVATE_DATA*)PeiPciEnumerationPpi;
    if( PeiPciPrivateData->DeviceResetDone ) {
        return EFI_SUCCESS;
    } else {
        Status = PeiPciEnumerationPpi->ResetDeviceResources(PeiPciEnumerationPpi);
    }
    return Status;
}

/**
    Assigns the Io and Mmio type Resources for all the devices under Parent bridge.And programs
    the Base and limit registers of the Bridge based on the Resource required for the devices
    under the bridge.This function will be called recursively to handle bridge under bridge 
    case.

    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    
    @retval EFI_SUCCESS - Assigned Resources to the given Input Bridge
**/
EFI_STATUS 
AssignBridgeResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge
)
{
    UINT16                      BridgeBase,BridgeLimit = 0;
    UINT8                       CommandRegister = 0;
    PEI_PCI_DEV_INFO            *PciDeviceInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT     *ChildBridgeExtInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT     *ParentBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT*)(ParentBridge+1);
    PEI_PCI_BRIDGE_INFO_EXT     *RootBridgeExtInfo;
    UINT64                      PciAddr;
    LIST_ENTRY                  *LinkData;
    BOOLEAN                     IsPresent;

    // First Program IO and Mmio Resource for the PCI to PCI Bridge
    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
        // Check whether this belongs to the ParentBridge
        if(PciDeviceInfo->ParentBridge != ParentBridge) {
            continue;
        }
        
        PciAddr = PCI_SEGMENT_LIB_ADDRESS(PciDeviceInfo->Segment,
                                          PciDeviceInfo->Bus,
                                          PciDeviceInfo->Device,
                                          PciDeviceInfo->Function,
                                          0);
        
        if (PciDeviceInfo->Type == tPci2PciBrg) {

            ChildBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT *)(PciDeviceInfo+1);
            if (ChildBridgeExtInfo->BridgeProgrammed) {
                continue;
            }
            
            // If P2P bridge is already pre-programmed, then skip it
            if (ChildBridgeExtInfo->BridgePreProgrammed) {
                continue;
            }
            
            RootBridgeExtInfo = GetRootBridgeExtPtr(ParentBridge);
            if (RootBridgeExtInfo == NULL) {
                continue;
            }
            
            // Read Command Register for Enabling Bridge I/O or Memory Decoding
            CommandRegister = PciSegmentRead8 (PciAddr + PCI_COMMAND_OFFSET);

            if (ChildBridgeExtInfo->IoBaseLength) {
                ChildBridgeExtInfo->BridgeProgrammed = TRUE;
                
                while (TRUE) {
                    // Check this IoBase is already programmed to any other device
                    IsPresent = CheckIfResourcePresent(RootBridgeExtInfo, 
                                                       ParentBridgeExtInfo->IoBase,
                                                       ChildBridgeExtInfo->IoBaseLength,
                                                       tBarIo);
                    if(IsPresent) {
                        DEBUG((DEBUG_INFO, "IoBase already Present - 0x%x, 0x%x\n", ParentBridgeExtInfo->IoBase, ChildBridgeExtInfo->IoBaseLength));
                        
                        // If yes, increment IoBase and check again
                        ParentBridgeExtInfo->IoBase += (P2P_BRG_IO_GRA + 1);
                    } else {
                        break;
                    }
                }
                
                // If range falls in between RB Base and IO limit, then proceed
                if (RootBridgeExtInfo->RbIoLimit) {
                    if (!((RootBridgeExtInfo->RbIoBase <= ParentBridgeExtInfo->IoBase) &&
                         (RootBridgeExtInfo->RbIoLimit >= ParentBridgeExtInfo->IoBase + ChildBridgeExtInfo->IoBaseLength))) {
                        DEBUG((DEBUG_INFO, "IoBase 0x%x, Length - 0x%x\n", ParentBridgeExtInfo->IoBase, ChildBridgeExtInfo->IoBaseLength));
                        DEBUG((DEBUG_INFO, "Exceeds RB IO Limit!!!\n"));
                        continue;
                    }
                }
                
                ChildBridgeExtInfo->IoBase = ParentBridgeExtInfo->IoBase;
                ParentBridgeExtInfo->IoBase += ChildBridgeExtInfo->IoBaseLength;
                
                BridgeBase = (UINT16)(ChildBridgeExtInfo->IoBase >> 8);
                BridgeLimit = (UINT16)((ChildBridgeExtInfo->IoBase + 
                              (ChildBridgeExtInfo->IoBaseLength - 1)) >> 8);
                
                PciSegmentWrite8(PciAddr + PCI_IOBASE, (UINT8)BridgeBase);
                PciSegmentWrite8(PciAddr + PCI_IOLIMIT, (UINT8)BridgeLimit);
                
                // Enabling Bridge IO Decoding.
                CommandRegister |= (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE);
                PciSegmentWrite8 (PciAddr + PCI_COMMAND_OFFSET, CommandRegister);

                DEBUG((DEBUG_INFO,"----------------------------------------------------\n"));
                DEBUG((DEBUG_INFO," Assigned Resource to the Bridge @B[%x]|D[%x]|F[%x]\n",
                                                      PciDeviceInfo->Bus,
                                                      PciDeviceInfo->Device,
                                                      PciDeviceInfo->Function));
               DEBUG((DEBUG_INFO, "Bridge IoBase: 0x%x, IoLimit: 0x%x \n", BridgeBase, BridgeLimit));
           }
           
           if (ChildBridgeExtInfo->MmioBaseLength) {
                ChildBridgeExtInfo->BridgeProgrammed = TRUE;
                
                while (TRUE) {
                    // Check this MmioBase is already programmed to any other device
                    IsPresent = CheckIfResourcePresent(
                                                    RootBridgeExtInfo, 
                                                    ParentBridgeExtInfo->MmioBase,
                                                    ChildBridgeExtInfo->MmioBaseLength,
                                                    tBarMem);
                    if (IsPresent) {
                        // If yes, increment MmioBase and check again
                        DEBUG((DEBUG_INFO, "MmioBase already Present - %lx, %lx\n",
                            ParentBridgeExtInfo->MmioBase, ChildBridgeExtInfo->MmioBaseLength));

                        ParentBridgeExtInfo->MmioBase += (P2P_BRG_MEM_GRA + 1);
                    } else {
                        break;
                    }
                }
                
                // If range falls in between RB limit, then proceed
                if (RootBridgeExtInfo->RbMmioLimit) {
                    if (!((RootBridgeExtInfo->RbMmioBase <= ParentBridgeExtInfo->MmioBase) &&
                         (RootBridgeExtInfo->RbMmioLimit >= ParentBridgeExtInfo->MmioBase + ChildBridgeExtInfo->MmioBaseLength))) {
                        DEBUG((DEBUG_INFO, "MmioBase 0x%lx, Length - 0x%lx\n", ParentBridgeExtInfo->MmioBase, ChildBridgeExtInfo->MmioBaseLength));
                        DEBUG((DEBUG_INFO, "Exceeds RB MMIO Limit!!!\n"));
                        continue;
                    }
                }
                
                ChildBridgeExtInfo->MmioBase = ParentBridgeExtInfo->MmioBase;
                ParentBridgeExtInfo->MmioBase += ChildBridgeExtInfo->MmioBaseLength;
                
                BridgeBase = (UINT16)RShiftU64 (ChildBridgeExtInfo->MmioBase, 16);
                BridgeLimit = (UINT16)RShiftU64 (ChildBridgeExtInfo->MmioBase +
                                      (ChildBridgeExtInfo->MmioBaseLength - 1),16);
                
                
                PciSegmentWrite16 (PciAddr + PCI_MEMBASE, BridgeBase);
                PciSegmentWrite16 (PciAddr + PCI_MEMLIMIT, BridgeLimit);
                
                // Enabling Bridge Memory Decoding.
                CommandRegister |= (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE);
                PciSegmentWrite8 (PciAddr + PCI_COMMAND_OFFSET, CommandRegister);

                DEBUG((DEBUG_INFO,"---------------------------------------------------\n"));
                DEBUG((DEBUG_INFO, "Assigned Resource to the Bridge @B[%x]|D[%x]|F[%x]\n",
                                                        PciDeviceInfo->Bus, 
                                                        PciDeviceInfo->Device, 
                                                        PciDeviceInfo->Function));
                DEBUG((DEBUG_INFO, "Bridge MemBase: 0x%x, MemLimit: 0x%x\n", BridgeBase, BridgeLimit));
            }
            
            // Now assign Resources for the PCI to PCI Bridge behind this bridge.
            AssignBridgeResources (PeiPciPrivateData, PciDeviceInfo);
            
            if (ChildBridgeExtInfo->IoBaseLength) {
                // Bridge Base and Limit registers are programmed 
                // Now start assigning resources to the devices under it
                DEBUG((DEBUG_INFO,"Assigning IO Resources "));
                AssignDeviceResources (PeiPciPrivateData, PciDeviceInfo, tBarIo);
            }
            
            if (ChildBridgeExtInfo->MmioBaseLength) {
                DEBUG((DEBUG_INFO, "Assigning Mmio Resources ")); 
                AssignDeviceResources (PeiPciPrivateData, PciDeviceInfo, tBarMem);
            }
         } 
    } // For Loop
    
    // By this stage all the PCI to PCI bridge devices are assigned with resources
    // start handling the On board Devices
    if(ParentBridge->Type == tPciRootBrg && ParentBridgeExtInfo->ChildDeviceCount ) {

        if (ParentBridgeExtInfo->IoBaseLength) {
            DEBUG((DEBUG_INFO,"Assigning IO Resources "));
            AssignDeviceResources(PeiPciPrivateData, ParentBridge, tBarIo);
        }
        if (ParentBridgeExtInfo->MmioBaseLength) {
            DEBUG((DEBUG_INFO, "Assigning MMIO Resources ")); 
            AssignDeviceResources(PeiPciPrivateData, ParentBridge, tBarMem);
        }
    } 
    return EFI_SUCCESS;
}

/**
    Calculates and returns the I/O or Mmio Resource length used by child Bridges.

    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    @param[in]  ChildBridgeIoLength     Pointer to the Memory location that holds Io Length.
    @param[in]  ChildBridgeMmioLength   Pointer to the Memory location that holds Mmio Length.
    
**/
VOID 
FindChildBridgesLength (
  PEI_PCI_ENUMERATION_PRIVATE_DATA     *PeiPciPrivateData,
  PEI_PCI_DEV_INFO                     *ParentBridge,
  UINT32                               *ChildBridgeIoLength, 
  UINT64                               *ChildBridgeMmioLength
)
{
    PEI_PCI_DEV_INFO            *PciDeviceInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT     *ChildBridgeExtInfo = NULL;
    LIST_ENTRY                  *LinkData;
    
    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
         // Check whether this device belongs to the ParentBridge
         if(PciDeviceInfo->ParentBridge != ParentBridge) {
             continue;
         }
         
         if(PciDeviceInfo->Type == tPci2PciBrg) {
             ChildBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT*)(PciDeviceInfo+1);
             if(ChildBridgeExtInfo->IoBaseLength) {
                 *ChildBridgeIoLength += ChildBridgeExtInfo->IoBaseLength;
             } else if (ChildBridgeExtInfo->MmioBaseLength ){
                 *ChildBridgeMmioLength += ChildBridgeExtInfo->MmioBaseLength;
             }
         }
    }
    return;
}

/**
    Assigns the Resources to the Pci Devices under the give Input Parent Bridge
    one by one based on the Granularity.The device with MaxGranularity will be 
    assigned Resource first.

    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    @param[in]  ResourceType            Resource Type either tBarIo or tBarMem
    
    @retval EFI_SUCCESS - Assigned Resources to the devices under the given Input Bridge.
**/

EFI_STATUS 
AssignDeviceResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge,
    PEI_PCI_BAR_TYPE                    ResourceType
)
{
    EFI_STATUS                 Status;
    UINT8                      CommandRegister = 0;
    PEI_PCI_DEV_INFO           *PciDeviceInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT    *ParentBridgeExtInfo;
    UINT64                     MaxGranularity = 0;
    UINT8                      BridgeChildDevCount = 0;
    UINT64                     BaseAddress = 0;
    UINT8                      CmdRegMask;
    UINT64                     PciAddr;
    UINT32                     BaseAddressUpper32 = 0;
    UINT32                     BaseAddressLower32 = 0;
    PEI_PCI_BRIDGE_INFO_EXT    *RootBridgeExtInfo;
    BOOLEAN                    IsPresent;

    if ((PeiPciPrivateData == NULL) || (ParentBridge == NULL)) {
        return EFI_INVALID_PARAMETER;
    }
    
    DEBUG((DEBUG_INFO, "for the Devices Under bridge @B[%x]|D[%x]|F[%x]\n",
                                                  ParentBridge->Bus, ParentBridge->Device, ParentBridge->Function));
    DEBUG((DEBUG_INFO,"-----------------------------------------------------------------------\n"));
    
    ParentBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT *)(ParentBridge+1);
    
    BridgeChildDevCount = ParentBridgeExtInfo->ChildDeviceCount;
    
    if (ResourceType == tBarIo) {
        BaseAddress = (UINT64) ParentBridgeExtInfo->IoBase;
        CmdRegMask = (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE);
    }
    
    if (ResourceType == tBarMem) {
        BaseAddress = ParentBridgeExtInfo->MmioBase;
        CmdRegMask = (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE);
    }
    
    RootBridgeExtInfo = GetRootBridgeExtPtr(ParentBridge);
    if (RootBridgeExtInfo == NULL) {
        return EFI_NOT_FOUND;
    }
    
    while (BridgeChildDevCount) {
        // Get the first maximum granularity device under this bridge and 
        // program the BAR address
        Status = GetNextMaxGranDevUnderBridge (
                                        PeiPciPrivateData,
                                        ParentBridge,
                                        ResourceType,
                                        &MaxGranularity,
                                        &PciDeviceInfo);
        if (EFI_ERROR(Status) || !PciDeviceInfo || !MaxGranularity) {
            return EFI_NOT_FOUND;
        }
        
        DEBUG((DEBUG_INFO, "    Assigned Bar for Device @B[%x]|D[%x]|F[%X] ",
                    PciDeviceInfo->Bus, PciDeviceInfo->Device, PciDeviceInfo->Function ));
        
        PciAddr = PCI_SEGMENT_LIB_ADDRESS(PciDeviceInfo->Segment,
                                          PciDeviceInfo->Bus,
                                          PciDeviceInfo->Device,
                                          PciDeviceInfo->Function,
                                          0);
        
        // If this allowable device already programmed by other PEI driver, then skip it
        if (PciDeviceInfo->IsBarPreProgrammed) {
            DEBUG((DEBUG_INFO, "BAR programmed already\n"));
            continue;
        }
        
        // If any P2P bridge in root bus is pre-programmed, then assign resources to devices in
        // root bus without resource conflict with those P2P bridge resouces
        if (ParentBridge->Type == tPciRootBrg) {
            while (TRUE) {
                // Check this BaseAddress is already programmed to any other device
                IsPresent = CheckIfResourcePresent(
                                               RootBridgeExtInfo, 
                                               BaseAddress,
                                               PciDeviceInfo->Bar.Length,
                                               ResourceType);
                if(IsPresent) {
                    DEBUG((DEBUG_INFO, "Base Address already Present - 0x%x, 0x%x\n", BaseAddress, PciDeviceInfo->Bar.Length));
                    
                    // If yes, increment BaseAddress and check again
                    BaseAddress += PciDeviceInfo->Bar.Length;
                } else {
                    break;
                }
            }
        }
        
        // Program Bar for this Device and Enable Memory Decoding
        PciDeviceInfo->Bar.Base = BaseAddress;
        BaseAddress += PciDeviceInfo->Bar.Length;
        
        // Programming Bar of the PciDevice
        if (PciDeviceInfo->Bar.Type == tBarIo || PciDeviceInfo->Bar.Type == tBarMmio32) {
            
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, (UINT32)PciDeviceInfo->Bar.Base);
                
         } else if (PciDeviceInfo->Bar.Type == tBarMmio64) {
             // Since in PEI phase we have Memory resource limitation till 4GB
             // A PCI Device that needs 64 bit bar address also will be assigned 
             // and 32 bit address.
             BaseAddressUpper32 = (UINT32)(PciDeviceInfo->Bar.Base);
             PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, BaseAddressUpper32);
             
             BaseAddressLower32 = (UINT32) RShiftU64 (PciDeviceInfo->Bar.Base, 32);
             PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset + 4, BaseAddressLower32);
         }
        
         PciDeviceInfo->IsBarProgrammed = TRUE;
         DEBUG((DEBUG_INFO,": 0x%lx ,Length : 0x%lx\n",PciDeviceInfo->Bar.Base, PciDeviceInfo->Bar.Length));
         BridgeChildDevCount--;
         
         // Enable Memory or IO Space Decoding for the device.
         CommandRegister = PciSegmentRead8(PciAddr + PCI_COMMAND_OFFSET);
         CommandRegister |= CmdRegMask;
         
         PciSegmentWrite8 (PciAddr + PCI_COMMAND_OFFSET, CommandRegister);
    } 
    DEBUG((DEBUG_INFO,"-----------------------------------------------------------------------\n"));
    return EFI_SUCCESS;
}

/**
    This will finds the UnProgrammed Pci Device with the next maximum granularity under
    the given Input Parent Bridge.

    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    @param[in]  ResourceType            Resource Type either tBarIo or tBarMem
    @param[in]  MaxGranularity          Maximum Granularity
    @param[in]  MaxGranPciDeviceInfo    Pci Device Info with Max Granularity
    
    @retval EFI_SUCCESS - Calculated Resources successfully.
**/
EFI_STATUS 
GetNextMaxGranDevUnderBridge(
    IN  PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    IN  PEI_PCI_DEV_INFO                    *ParentBridge,
    IN  PEI_PCI_BAR_TYPE                    ResourceType,
    OUT UINT64                              *MaxGranularity,
    OUT PEI_PCI_DEV_INFO                    **MaxGranPciDeviceInfo
) 
{
    PEI_PCI_DEV_INFO    *PciDeviceInfo = NULL;
    LIST_ENTRY          *LinkData;
    
    // Set Initial value to zero
    *MaxGranularity = 0;
    
    // Calculate maximum granularity for the devices under this  Bridge..
    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
        if (PciDeviceInfo->ParentBridge != ParentBridge) {
            continue;
        }
        
        if ((PciDeviceInfo->Type == tPciDevice) && (!PciDeviceInfo->IsBarProgrammed)) {
            if ((ResourceType == tBarMem) || (ResourceType == tBarIo)) {
                if ((PciDeviceInfo->Bar.Type != tBarMmio32) && 
                    (PciDeviceInfo->Bar.Type != tBarMmio64) &&
                    (PciDeviceInfo->Bar.Type != tBarIo)) {
                    continue;
                }
            }
            
            if ((*MaxGranularity) < PciDeviceInfo->Bar.Gran) {
                *MaxGranularity = PciDeviceInfo->Bar.Gran;
                *MaxGranPciDeviceInfo = PciDeviceInfo;
            }
        } 
    } // for loop
    
    if (*MaxGranularity) {
        return EFI_SUCCESS;
    }
    
    return EFI_NOT_FOUND;
}

/**
    Calculates the resources required for each bridge,This function will be called recursively
    in case of Pci to Pci Bridge under Bridge is found. 

    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    
    @retval EFI_SUCCESS - Calculated Resources successfully.
**/
EFI_STATUS 
CalculateBridgeResources(
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                    *ParentBridge
) 
{
    PEI_PCI_DEV_INFO            *PciDeviceInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT     *ChildBridgeExtInfo = NULL;
    PEI_PCI_BRIDGE_INFO_EXT     *ParentBridgeExtInfo;
    UINT32                      GranRemainderLen = 0;
    LIST_ENTRY                  *LinkData;

    if ((PeiPciPrivateData == NULL) || (ParentBridge == NULL)) {
        return EFI_INVALID_PARAMETER;
    }
    
    if (ParentBridge->Type == tPci2PciBrg) {
        DEBUG((DEBUG_INFO,"-----------------------------------------------------------\n"));
        DEBUG((DEBUG_INFO,"Calculate Resource for the Bridge @B[%X]|D[%X]|F[%X] Start \n", 
                                             ParentBridge->Bus, ParentBridge->Device, ParentBridge->Function ));
        DEBUG((DEBUG_INFO,"-----------------------------------------------------------\n"));
    }
    
    ParentBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT *)(ParentBridge+1);

    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
       
        if (PciDeviceInfo->ParentBridge != ParentBridge) {
            continue;
        }
       
        if (PciDeviceInfo->Type == tPci2PciBrg) {
            // Now start calculating the resources for the child bridge
            CalculateBridgeResources (PeiPciPrivateData,PciDeviceInfo);
           
            ChildBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT *)(PciDeviceInfo+1);
            ParentBridgeExtInfo->IoBaseLength += ChildBridgeExtInfo->IoBaseLength;
            ParentBridgeExtInfo->MmioBaseLength += ChildBridgeExtInfo->MmioBaseLength;
        }
       
        if ((PciDeviceInfo->Type == tPciDevice) && (!PciDeviceInfo->IsBarPreProgrammed)) {
            DEBUG((DEBUG_INFO, "  -- Required Resource for the PCI Device @B[%X]|D[%X]|F[%X] \n", 
                                    PciDeviceInfo->Bus, PciDeviceInfo->Device,PciDeviceInfo->Function));

            DEBUG((DEBUG_INFO, "    Bar Length :%lx, Bar Granularity:%lx, Bar Type :%x\n",
                                    PciDeviceInfo->Bar.Length, PciDeviceInfo->Bar.Gran, PciDeviceInfo->Bar.Type));
           
            // Append the Bar length and  Update the Granularity.
            if (PciDeviceInfo->Bar.Type == tBarIo ) {
                ParentBridgeExtInfo->IoBaseLength += (UINT32)PciDeviceInfo->Bar.Length;
                if (!ParentBridgeExtInfo->IoGranularity ) {
                    ParentBridgeExtInfo->IoGranularity = (UINT32)PciDeviceInfo->Bar.Gran;
                } else if (ParentBridgeExtInfo->IoGranularity < PciDeviceInfo->Bar.Gran ) {
                    ParentBridgeExtInfo->IoGranularity = (UINT32)PciDeviceInfo->Bar.Gran;
                }
            } else if ( PciDeviceInfo->Bar.Type == tBarMmio32 || PciDeviceInfo->Bar.Type == tBarMmio64) {
                ParentBridgeExtInfo->MmioBaseLength += PciDeviceInfo->Bar.Length;
                if (!ParentBridgeExtInfo->MmioGranularity ) {
                    ParentBridgeExtInfo->MmioGranularity = PciDeviceInfo->Bar.Gran;
                } else if (ParentBridgeExtInfo->MmioGranularity < PciDeviceInfo->Bar.Gran ) {
                    ParentBridgeExtInfo->MmioGranularity = PciDeviceInfo->Bar.Gran;
                }
            }
        }
    }
    
    // Check and update the Io Granularity, make sure minimum IO granularity for a bridge is 0xFFF.
    if (ParentBridgeExtInfo->IoBaseLength) {
        GranRemainderLen = ParentBridgeExtInfo->IoBaseLength % (P2P_BRG_IO_GRA + 1);
        if (GranRemainderLen) {
            ParentBridgeExtInfo->IoBaseLength += (UINT32)(P2P_BRG_IO_GRA + 1) - GranRemainderLen;
        }
    }
    
    // Check and update the MMIO Granularity, make sure minimum MMIO granularity for a bridge is 0xFFFFF.
    if(ParentBridgeExtInfo->MmioBaseLength) {
        DivU64x32Remainder(ParentBridgeExtInfo->MmioBaseLength,(UINT32)(P2P_BRG_MEM_GRA +1),&GranRemainderLen);
        if (GranRemainderLen) {
            ParentBridgeExtInfo->MmioBaseLength += (P2P_BRG_MEM_GRA + 1) - GranRemainderLen;
        }
    }
    
    DEBUG((DEBUG_INFO,"Total Resource Required for the Bridge @B[%X]|D[%X]|F[%X] \n   --MMIO Length:%lx,IO Length:%x\n",
                      ParentBridge->Bus, ParentBridge->Device, ParentBridge->Function,
                      ParentBridgeExtInfo->MmioBaseLength,ParentBridgeExtInfo->IoBaseLength));
    DEBUG((DEBUG_INFO,"--------------------------------------------------------- \n\n"));

    return EFI_SUCCESS;
    
} 

/**
    Gets RootBridgeExt pointer from PEI_PCI_DEV_INFO pointer
     
    @param PciDeviceInfo
    
    @return PEI_PCI_BRIDGE_INFO_EXT pointer
 */
PEI_PCI_BRIDGE_INFO_EXT*
GetRootBridgeExtPtr(
    PEI_PCI_DEV_INFO    *PciDeviceInfo
)
{
    while(TRUE) {
        
        if (PciDeviceInfo == NULL) {
            return NULL;
        }
                
        if (PciDeviceInfo->Type == tPciRootBrg) {
            break;
        }
        
        PciDeviceInfo = PciDeviceInfo->ParentBridge;
    }
    
    return (PEI_PCI_BRIDGE_INFO_EXT*)(PciDeviceInfo + 1);
}

/**
    Checks whether the passed resource already assigned to other PCI devices
    
    @param RootBridgeExtInfo
    @param BaseAddr
    @param Length
    @param Type
    
    @return    TRUE  - Already assigned to other PCI devices
    @return    FALSE - Not assigned to other PCI devices
 */
BOOLEAN
CheckIfResourcePresent(
    PEI_PCI_BRIDGE_INFO_EXT     *RootBridgeExtInfo,
    UINT64                      BaseAddr,
    UINT64                      Length,
    PEI_PCI_BAR_TYPE            Type
)
{
    PCI_RESOURCE_EXCEPTION    *PciResourceException;
    LIST_ENTRY                *LinkData;
    
    for (LinkData = RootBridgeExtInfo->ResourceExceptionList.ForwardLink; 
         LinkData != &RootBridgeExtInfo->ResourceExceptionList; 
         LinkData = LinkData->ForwardLink) {
        
        PciResourceException = BASE_CR(LinkData, PCI_RESOURCE_EXCEPTION, Link);
        
        if(PciResourceException->Bar.Type != Type) {
            continue;
        }
        
        // This if check whether the requested resource completely falls inside exception resource
        if((BaseAddr >= PciResourceException->Bar.Base) &&
           ((BaseAddr + Length) <= (PciResourceException->Bar.Base + PciResourceException->Bar.Length))) {
            DEBUG((DEBUG_INFO, "Completely falls inside exception Resource Base: 0x%lx, Length: 0x%lx\n", 
                                PciResourceException->Bar.Base, PciResourceException->Bar.Length));
            return TRUE;
        }

        // This if check whether the requested resource overlaps with exception resource
        if((BaseAddr < PciResourceException->Bar.Base) && 
           ((BaseAddr + Length) > PciResourceException->Bar.Base)) {
            DEBUG((DEBUG_INFO, "(BaseAddr + Length) Overlaps with exception Resource Base: 0x%lx, Length: 0x%lx\n", 
                                PciResourceException->Bar.Base, PciResourceException->Bar.Length));
            return TRUE;
        }
        
        // This if check whether the requested resource overlaps with exception resource
        if((BaseAddr > PciResourceException->Bar.Base) && 
           ((BaseAddr) < (PciResourceException->Bar.Base + PciResourceException->Bar.Length))) {
            DEBUG((DEBUG_INFO, "BaseAddr Overlaps with exception Resource Base: 0x%lx, Length: 0x%lx\n", 
                                PciResourceException->Bar.Base, PciResourceException->Bar.Length));
            return TRUE;
        }
    }
    
    return FALSE;
}

/**
    Checks whether the PCI device programmed with BAR by other PEI drivers
    
    @param ParentBridge
    @param Segment
    @param Bus
    @param Device
    @param Function
    
    @return     TRUE  - BAR already programmed
    @return     FALSE - BAR not programmed
 */
BOOLEAN
CheckIsDeviceProgrammedAlready(
    PEI_PCI_DEV_INFO        *ParentBridge,
    UINT8                   Segment,
    UINT8                   Bus,
    UINT8                   Device,
    UINT8                   Function
)
{
    EFI_STATUS                Status;
    UINT8                     BarIndex;
    BOOLEAN                   AlreadyProgrammed = FALSE;
    PEI_PCI_BRIDGE_INFO_EXT   *RootBridgeExtInfo;
    PCI_RESOURCE_EXCEPTION    *PciResourceException;
    PEI_PCI_DEV_INFO          TempPciDevice;
    
    TempPciDevice.Type = tPciDevice;
    TempPciDevice.SkipDevice = TRUE;
    TempPciDevice.Segment = Segment;
    TempPciDevice.Bus = Bus;
    TempPciDevice.Device = Device;
    TempPciDevice.Function = Function;
    
    for (BarIndex = 0; BarIndex < PCI_MAX_BAR; BarIndex++) {
        
        // Checks all BARs whether it has value or not
        TempPciDevice.Bar.Offset = PCI_BASE_ADDRESSREG_OFFSET + (BarIndex * 4);
        Status = QueryPciDeviceResources(&TempPciDevice);
        if (EFI_ERROR(Status) || TempPciDevice.Bar.Type == tBarUnused) {
            continue;
        }
        
        if (TempPciDevice.Bar.Type == tBarMmio64) {
            BarIndex++;
        }
        
        // If BAR offset has value, then add it to ExceptionList
        if (TempPciDevice.Bar.Base != 0) {
            
            DEBUG((DEBUG_INFO, "BAR Index [%d] already programmed with 0x%lx\n", BarIndex, TempPciDevice.Bar.Base));
            
            AlreadyProgrammed = TRUE;
            
            if (TempPciDevice.Bar.Type != tBarIo) {
                TempPciDevice.Bar.Type = tBarMem;
            }
            
            RootBridgeExtInfo = GetRootBridgeExtPtr(ParentBridge);
            if (RootBridgeExtInfo == NULL) {
                return AlreadyProgrammed;
            }

            PciResourceException = AllocateZeroPool (sizeof(PCI_RESOURCE_EXCEPTION));
            if (PciResourceException == NULL) {
                return AlreadyProgrammed;
            }
            
            CopyMem (&PciResourceException->Bar, &TempPciDevice.Bar, sizeof(PEI_PCI_BAR));
            
            // Add Resource to exception list. So that this resource won't be allocated to other devices
            InsertTailList (&RootBridgeExtInfo->ResourceExceptionList, &PciResourceException->Link);
        }
    }
    
    return AlreadyProgrammed;
}

/**
    If allowable PCI device already programmed with BAR, this routine checks whether 
    the requested BAR offset already programmed or not
    
    @param PciAddr
    @param BarOffset
    
    @return TRUE  - Requested BAR offset already programmed
    @return FALSE - Requested BAR offset not programmed
 */
BOOLEAN
IsRequestedBarProgrammed(
    UINT64      PciAddr,
    UINT8       BarOffset
)
{
    EFI_STATUS                Status;
    PEI_PCI_DEV_INFO          TempPciDevice;
    UINT8                     CmdRegMask;
    UINT8                     CommandRegister;
    
    TempPciDevice.Type = tPciDevice;
    TempPciDevice.SkipDevice = TRUE;
    TempPciDevice.Segment = (UINT8)RShiftU64(PciAddr, 32);
    TempPciDevice.Bus = (UINT8)(RShiftU64(PciAddr, 20));
    TempPciDevice.Device = (UINT8)((RShiftU64(PciAddr, 15)) & 0x1F);
    TempPciDevice.Function = (UINT8)((RShiftU64(PciAddr, 12)) & 0x7);
    TempPciDevice.Bar.Offset = BarOffset;
    
    Status = QueryPciDeviceResources (&TempPciDevice);
    if(EFI_ERROR(Status)) {
        return FALSE;
    }
    
    if(TempPciDevice.Bar.Base != 0) {
        DEBUG((DEBUG_INFO, "Requested BAR Offset [0x%x] Pre-Programmed\n", BarOffset));
        
        if(TempPciDevice.Bar.Type == tBarIo) {
            CmdRegMask = (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_IO_SPACE);
        } else {
            CmdRegMask = (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE);
        }
        
        CommandRegister = PciSegmentRead8(PciAddr + PCI_COMMAND_OFFSET);
        if(!(CommandRegister & CmdRegMask)) {
            CommandRegister |= CmdRegMask;
            PciSegmentWrite8(PciAddr + PCI_COMMAND_OFFSET, CommandRegister);
        }
        
        return TRUE;
    }
    
    return FALSE;
}

/** 
    Based on the ClassCode Input verified whether this device has to skipped or handled
    by checking through the list of class codes provided through the PEI_PCI_CLASS_CODE_LIST. 
    
    @param   PciAddr
    @param   PciClassCode
    @param   BarOffset
    @param   IsProgrammed
    
    @retval EFI_SUCCESS                 The operation succeeded.
**/
BOOLEAN
IsAllowedClassCodeDevice (
    IN  UINT64                 PciAddr,
    IN  AMI_PEI_PCI_CLASSCODE  *PciClassCode, 
    OUT UINT8                  *BarOffset,
    IN OUT BOOLEAN             *IsProgrammed
)
{
    BOOLEAN                    IsReqBarProgrammed;
    PCI_DEVICE_CLASSCODE_ENTRY PciDeviceClassCodeList[] = {PEI_PCI_CLASS_CODE_LIST
                                                               {0xff, 0xff, 0xff, 0xff}};
    UINT8      Index;
    
    for (Index = 0; PciDeviceClassCodeList[Index].BaseClassCode != 0xFF; Index++) {

        if (PciDeviceClassCodeList[Index].BaseClassCode ==  PciClassCode->BaseClassCode && 
                PciDeviceClassCodeList[Index].SubClassCode ==  PciClassCode->SubClassCode) {
            
            if (PciDeviceClassCodeList[Index].ProgrammingInterface != 0xFF) {
                if (PciDeviceClassCodeList[Index].ProgrammingInterface != PciClassCode->ProgrammingInterface) { 
                    continue;  
                }
            }
            
            // Check for Valid BAR offset.  
            if ((PciDeviceClassCodeList[Index].BarIndex) > PCI_MAX_BAR - 1) {
                // Invalid Bar offset
                continue;
            } else {
                *BarOffset = (UINT8)(PCI_BASE_ADDRESSREG_OFFSET + (PciDeviceClassCodeList[Index].BarIndex) * 4);
                
                // IsProgrammed flag is set, then check for requested BAR is programmed or not
                // if not programmed already, then clear the flag
                if (*IsProgrammed) {
                    IsReqBarProgrammed = IsRequestedBarProgrammed(PciAddr, *BarOffset);
                    if (!IsReqBarProgrammed) {
                        *IsProgrammed = FALSE;
                    }
                }
                return TRUE;
            } 
        }
    }
    return FALSE;
}

/** 
  Queries the Resources Required for the Pci Device provided as input.
  
  @param[in]      PciDeviceInfo       Specified the pointer to the PCI_DEVICE_INFO structure
                                      of the device whose Resources needs to be queried.
  
  @retval EFI_SUCCESS                 The operation succeeded.PciDevice resource is found. 
 **/
EFI_STATUS
QueryPciDeviceResources(
    PEI_PCI_DEV_INFO         *PciDeviceInfo
) 
{
    UINT64       Buffer64;
    UINT32       Buffer32;
    UINT64       PciAddr;
    UINT32       Lower32 = 0;
    UINT32       Upper32 = 0;
    UINT16       CommandReg;
     
    // Currently handling PciDevice resource checking
    if(PciDeviceInfo->Type != tPciDevice) {
        return EFI_UNSUPPORTED;
    }
    
    PciAddr = PCI_SEGMENT_LIB_ADDRESS(PciDeviceInfo->Segment,
                                      PciDeviceInfo->Bus,
                                      PciDeviceInfo->Device,
                                      PciDeviceInfo->Function,
                                      0);
    
    Buffer32 = PciSegmentRead32(PciAddr + PciDeviceInfo->Bar.Offset);

    // Check what type of resource the Pci device requires
    if(Buffer32 & BIT0) {
        PciDeviceInfo->Bar.Type = tBarIo;
    } else {
        switch (Buffer32 & 0x0F) {
            case 0x0 : 
                PciDeviceInfo->Bar.Type = tBarMmio32;
                break;
            case 0x4 : 
                PciDeviceInfo->Bar.Type = tBarMmio64;
                break;
            default : 
                return EFI_UNSUPPORTED;
        }
    }
    
    CommandReg = PciSegmentRead16(PciAddr + PCI_COMMAND_OFFSET);
    if (CommandReg & (EFI_PCI_COMMAND_BUS_MASTER|EFI_PCI_COMMAND_MEMORY_SPACE|EFI_PCI_COMMAND_IO_SPACE)) {
        PciSegmentWrite16(
                    PciAddr + PCI_COMMAND_OFFSET, 
                    CommandReg & (~(EFI_PCI_COMMAND_BUS_MASTER|EFI_PCI_COMMAND_MEMORY_SPACE|EFI_PCI_COMMAND_IO_SPACE)));
    }
    // Now try to find the Device Decode Range.
    switch (PciDeviceInfo->Bar.Type) {
        case tBarMmio64:
            
            Lower32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset);
            Upper32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset + 4);
                
            PciDeviceInfo->Bar.Base = LShiftU64(Upper32, 32) + Lower32;
            PciDeviceInfo->Bar.Base &= (~0x0F); // Mask don't care bits for MMIO
            
            // Write
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, MAX_UINT32);
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset + 4, MAX_UINT32);
                            
            // Read Back
            Lower32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset);
            Upper32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset + 4);
                
            Buffer64 = LShiftU64(Upper32, 32) + Lower32;
            Buffer64 &= (~0x0F); // Mask don't care bits for MMIO
                
            if(Buffer64) {
                PciDeviceInfo->Bar.Gran = (UINTN)(~Buffer64);
                PciDeviceInfo->Bar.Length = PciDeviceInfo->Bar.Gran+1;
            } else {
                PciDeviceInfo->Bar.Type = tBarUnused;
            }
            
            // As to get length wrote 0xFF, now BAR will give length information for every read
            // So, restore BAR again
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, (UINT32)PciDeviceInfo->Bar.Base);
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset + 4, (UINT32)RShiftU64(PciDeviceInfo->Bar.Base, 32));
            
            break;
            
        case tBarMmio32:
        case tBarIo:

            Buffer32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset);
            if(PciDeviceInfo->Bar.Type == tBarIo) {
                Buffer32 &= ~0x03; // Mask Don't care bits for IO
            } else {
                Buffer32 &= ~0x0F; // Mask Don't care bits for MMIO
            }
                
            PciDeviceInfo->Bar.Base = Buffer32;
            
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, MAX_UINT32);
            Buffer32 = PciSegmentRead32 (PciAddr + PciDeviceInfo->Bar.Offset);
                
            if(PciDeviceInfo->Bar.Type == tBarIo) {
                Buffer32 &= ~0x03; // Mask Don't care bits for IO
            } else {
                Buffer32 &= ~0x0F; // Mask Don't care bits for MMIO
            }
    
            if(Buffer32){
                PciDeviceInfo->Bar.Gran = (UINT32)(~Buffer32);
                PciDeviceInfo->Bar.Length = PciDeviceInfo->Bar.Gran + 1;
            } else {
                PciDeviceInfo->Bar.Type = tBarUnused;
            }
            
            // As to get length wrote 0xFF, now BAR will give length information for every read
            // So, restore BAR again
            PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, (UINT32)PciDeviceInfo->Bar.Base);

            break;
            
         default: 
             PciDeviceInfo->Bar.Type = tBarUnused;
    }//switch  
    
    if(!PciDeviceInfo->SkipDevice) {
        DEBUG((DEBUG_INFO, "Bar Type:%x,Bar.Length:%lx, Bar.Gran:%lx \n",
                            PciDeviceInfo->Bar.Type, PciDeviceInfo->Bar.Length,PciDeviceInfo->Bar.Gran));
    }
    
    // restore command register
    if (CommandReg & (EFI_PCI_COMMAND_BUS_MASTER|EFI_PCI_COMMAND_MEMORY_SPACE|EFI_PCI_COMMAND_IO_SPACE)) {
        PciSegmentWrite16(
                    PciAddr + PCI_COMMAND_OFFSET, 
                    CommandReg);
    }

    return EFI_SUCCESS;    
}

/**
  Checks whether the input BusBase is already present in Bus Exception List.
  
  @param RootBridgeExtInfo    Pointer to Root Bridge information
  @param BusBase              Bus Number to check if present in Exception List
  
  @return TRUE - Bus Number is already present in Exception List.
  @return FALSE - Bus Number is not present in Exception List.
 */
BOOLEAN
CheckIfBusResourcePresent(
    PEI_PCI_BRIDGE_INFO_EXT   *RootBridgeExtInfo,
    UINT8                     BusBase
)
{
    PCI_BUS_EXCEPTION    *PciBusException;
    LIST_ENTRY           *LinkData;
    
    for (LinkData = RootBridgeExtInfo->BusExceptionList.ForwardLink; 
         LinkData != &RootBridgeExtInfo->BusExceptionList; 
         LinkData = LinkData->ForwardLink) {
        
        PciBusException = BASE_CR(LinkData, PCI_BUS_EXCEPTION, Link);
        
        if ((BusBase >= PciBusException->BusBase) &&
           (BusBase <= PciBusException->BusLimit)) {
            DEBUG((DEBUG_INFO, "Bus Number available in Exception list\n"));
            DEBUG((DEBUG_INFO, "BusBase - 0x%x, BusLimit - 0x%x, Input Bus - 0x%x\n", 
                    PciBusException->BusBase, PciBusException->BusLimit, BusBase));
            return TRUE;
        }
    }
    return FALSE;
}

/**
  Checks if the input Bridge is already programmed by the chipset code.
  If yes, then adds Resource to the exception list, so that this resource 
  won't be allocated to other devices.
  
  @param ParentBridge
  @param PciAddr
  @param PciBusExceptionPtr
  
  @return TRUE  Bridge is Pre-Programmed
  @return FALSE Bridge Not Programmed
 */
BOOLEAN
CheckIsBridgePreProgrammed(
    PEI_PCI_DEV_INFO        *ParentBridge,
    UINT64                  PciAddr,
    PCI_BUS_EXCEPTION       **PciBusExceptionPtr
)
{
    PEI_PCI_BRIDGE_INFO_EXT   *RootBridgeExtInfo;
    PCI_BUS_EXCEPTION         *PciBusException;
    PCI_RESOURCE_EXCEPTION    *PciIoResourceException;
    PCI_RESOURCE_EXCEPTION    *PciMmioResourceException;
    UINT8                     SecondaryBus = 0;
    UINT8                     SubordinateBus = 0;
    UINT16                    BridgeMemBase = 0;
    UINT16                    BridgeMemLimit = 0;
    UINT8                     BridgeIoBase = 0;
    UINT8                     BridgeIoLimit = 0;
    
    SecondaryBus = PciSegmentRead8(PciAddr + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET);
    SubordinateBus = PciSegmentRead8(PciAddr + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET);
    BridgeMemBase = PciSegmentRead16(PciAddr + PCI_MEMBASE);
    BridgeIoBase = PciSegmentRead8(PciAddr + PCI_IOBASE);
    
    if(!(SecondaryBus && SubordinateBus && BridgeMemBase && BridgeIoBase)) {
        DEBUG((DEBUG_INFO, " -- Bridge Not Programmed \n"));
        return FALSE;
    }
    
    DEBUG((DEBUG_INFO, "  -- Bridge Already Programmed \n"));
    
    RootBridgeExtInfo = GetRootBridgeExtPtr(ParentBridge);
    if(RootBridgeExtInfo == NULL) {
        return FALSE;
    }
        
    PciBusException = AllocateZeroPool(sizeof(PCI_BUS_EXCEPTION));
    if(PciBusException == NULL) {
        return FALSE;
    }
    
    PciBusException->BusBase = SecondaryBus;
    PciBusException->BusLimit = SubordinateBus;
    
    PciBusException->MmioBase = (UINT32)(BridgeMemBase << 16);
    BridgeMemLimit = PciSegmentRead16(PciAddr + PCI_MEMLIMIT);
    PciBusException->MmioLimit = (UINT32)(BridgeMemLimit << 16);
    
    PciBusException->IoBase = (UINT32)(BridgeIoBase << 8);
    BridgeIoLimit = PciSegmentRead8(PciAddr + PCI_IOLIMIT);
    PciBusException->IoLimit = (UINT32)(BridgeIoLimit << 8);
    
    DEBUG((DEBUG_INFO, "    -- Add BusBase and BusLimit to BusExceptionList\n"));
    DEBUG((DEBUG_INFO, "    -- BusBase - %x\n", PciBusException->BusBase));
    DEBUG((DEBUG_INFO, "    -- BusLimit - %x\n", PciBusException->BusLimit));
    DEBUG((DEBUG_INFO, "    -- MmioBase - %lx\n", PciBusException->MmioBase));
    DEBUG((DEBUG_INFO, "    -- MmioLimit - %lx\n", PciBusException->MmioLimit));
    DEBUG((DEBUG_INFO, "    -- IoBase - %x\n", PciBusException->IoBase));
    DEBUG((DEBUG_INFO, "    -- IoLimit - %x\n", PciBusException->IoLimit));
    
    // Add Bridge resource to exception list. So that this resource won't be allocated to other devices
    InsertTailList (&RootBridgeExtInfo->BusExceptionList, &PciBusException->Link);
    
    if(PciBusException->MmioBase && PciBusException->MmioLimit) {
        PciMmioResourceException = AllocateZeroPool (sizeof(PCI_RESOURCE_EXCEPTION));
        if (PciMmioResourceException == NULL) {
            return TRUE;
        }
        
        PciMmioResourceException->Bar.Type = tBarMem;
        PciMmioResourceException->Bar.Base = PciBusException->MmioBase;
        PciMmioResourceException->Bar.Length = PciBusException->MmioLimit - PciBusException->MmioBase;
        
        // Add MMIO Resource to exception list. So that this resource won't be allocated to other devices
        InsertTailList (&RootBridgeExtInfo->ResourceExceptionList, &PciMmioResourceException->Link);
    }

    if(PciBusException->IoBase && PciBusException->IoLimit) {   
        PciIoResourceException = AllocateZeroPool (sizeof(PCI_RESOURCE_EXCEPTION));
        if (PciIoResourceException == NULL) {
            return TRUE;
        }
    
        PciIoResourceException->Bar.Type = tBarIo;
        PciIoResourceException->Bar.Base = PciBusException->IoBase;
        PciIoResourceException->Bar.Length = PciBusException->IoLimit - PciBusException->IoBase;
        
        // Add IO Resource to exception list. So that this resource won't be allocated to other devices
        InsertTailList (&RootBridgeExtInfo->ResourceExceptionList, &PciIoResourceException->Link);
    }
            
    *PciBusExceptionPtr = PciBusException;
        
    return TRUE;
}

/**
    Enumerates the Bridge and finds the Devices under the bridge, if a bridge is found
    under parent bridge again call this EnumerateBus() function in recursive manner. 

    @param[in]  ParentDp                Pointer to DevicePath
    @param[in]  PeiPciPrivateData       Pointer to the PEI_PCI_ENUMERATION_PRIVATE_DATA
    @param[in]  ParentBridge            Pointer to the parent bridge PCI_DEVICE_INFO
    
    @retval EFI_OUT_OF_RESOURCES - Resource is not enough for storing
                                   Device Info
    @retval EFI_SUCCESS - Bus has been enumerated successfully.
    @note
    1.ParentDp used to keep the track of Previous Device Path.
    2.ParentDp initially holds the Acpi Device Path and it will be appended 
    further with newly found PCI-PCI Bridge until Detecting Valid Device.
**/
EFI_STATUS 
EnumerateBus(
    EFI_DEVICE_PATH                       *ParentDp,
    PEI_PCI_ENUMERATION_PRIVATE_DATA      *PeiPciPrivateData,
    PEI_PCI_DEV_INFO                      *ParentBridge
)
{
    EFI_STATUS                          Status;
    UINT8                               Bus;
    UINT8                               Device;
    UINT8                               Function;
    UINT16                              VendorId;
    UINT8                               HeaderType;
    UINT8                               BarOffset = PCI_BASE_ADDRESSREG_OFFSET;
    UINT32                              VendorDeviceId;
    UINT32                              RevisionId;
    BOOLEAN                             MultiFunc = FALSE;
    AMI_PEI_PCI_CLASSCODE               PciDeviceClass;
    PEI_PCI_DEV_INFO                    *PciDeviceInfo;
    PEI_PCI_BRIDGE_INFO_EXT             *ParentBridgeExtInfo;
    PEI_PCI_BRIDGE_INFO_EXT             *ChildBridgeExtInfo;
    PEI_PCI_BRIDGE_INFO_EXT             *RootBridgeExtInfo;
    EFI_DEVICE_PATH                     *ChildBridgeDp;
    UINT64                              PciAddr;
    UINT8                               Segment;
    BOOLEAN                             IsProgrammed = FALSE;
    PCI_BUS_EXCEPTION                   *PciBusException;
    
    ParentBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT*)(ParentBridge+1);
    Bus = ParentBridgeExtInfo->SecondaryBusNumber;
    Segment = ParentBridge->Segment;
    
    for (Device = 0; Device <= PCI_MAX_DEVICE; Device++) {
        
        for (Function = 0; Function <= PCI_MAX_FUNC; Function++) {
            
            PciAddr = PCI_SEGMENT_LIB_ADDRESS(Segment, Bus, Device, Function, 0);
           
            VendorId = PciSegmentRead16(PciAddr + PCI_VENDOR_ID_OFFSET);

            DEBUG((DEBUG_INFO,"Enumerating B[%x]|D[%x]|F[%x] Vendor ID:%X \n", Bus, Device,Function,VendorId));

            // Check for valid Device/Bridge
            if ((Function == 0) && VendorId == DEVICE_ID_NOCARE) {
                break;
            } else if (VendorId == DEVICE_ID_NOCARE ) {
                continue;
            }

            HeaderType = PciSegmentRead8(PciAddr + PCI_HEADER_TYPE_OFFSET);

            DEBUG((DEBUG_INFO, "HeaderType:%x\n", HeaderType));

            // Check whether it is a multi function Device.
            if( Function == 0) {
                if(HeaderType & HEADER_TYPE_MULTI_FUNCTION) {
                    MultiFunc = TRUE;
                }
            }
            

            switch (HeaderType & HEADER_LAYOUT_CODE) {
            
                case HEADER_TYPE_DEVICE :
                    DEBUG((DEBUG_INFO, "Found PCI Target Device @B[%x]|D[%x]|F[%x]\n",Bus, Device, Function ));
                    
                    IsProgrammed = CheckIsDeviceProgrammedAlready (ParentBridge, Segment, Bus, Device, Function);
                    
                    VendorDeviceId = PciSegmentRead32 (PciAddr + PCI_VENDOR_ID_OFFSET);
                    
                    // Pre-Enumeration porting function
                    ProcessPreEnumerationInit (
                                            Segment, 
                                            Bus, 
                                            Device, 
                                            Function, 
                                            (UINT16)VendorDeviceId, 
                                            (UINT16)(VendorDeviceId >> 16));
                    
                    RevisionId = PciSegmentRead32 (PciAddr + PCI_REVISION_ID_OFFSET);

                    PciDeviceClass.BaseClassCode = (UINT8)(RevisionId >> 24);
                    PciDeviceClass.SubClassCode = (UINT8)(RevisionId >> 16);
                    PciDeviceClass.ProgrammingInterface = (UINT8)(RevisionId >> 8);
                    
                    // Verify whether this device is to be handled or not
                    // based on the class code list.
                    if (IsAllowedClassCodeDevice(PciAddr, &PciDeviceClass, &BarOffset, &IsProgrammed)) {
                       
                       PciDeviceInfo = AllocateZeroPool (sizeof(PEI_PCI_DEV_INFO));
                       if (PciDeviceInfo == NULL) {
                           return EFI_OUT_OF_RESOURCES;
                       }
                       
                       PciDeviceInfo->Type = tPciDevice;
                       PciDeviceInfo->Segment = ParentBridge->Segment;
                       PciDeviceInfo->Bus = Bus;
                       PciDeviceInfo->Device = Device;
                       PciDeviceInfo->Function = Function;
                       CopyMem (&PciDeviceInfo->PciDeviceClass, &PciDeviceClass, sizeof(PciDeviceClass));
                       PciDeviceInfo->Bar.Offset = BarOffset;
                       PciDeviceInfo->ParentBridge = ParentBridge;

                       // Creates hardware PCI Path for PCI-PCI bridge and 
                       // appends with previously created Device Path       
                       gPeiPciPath.Function = Function;
                       gPeiPciPath.Device = Device;                       
                       PciDeviceInfo->DevPath = PeiDevicePathAddNode (ParentDp, &(gPeiPciPath.Header));
                       
                       // Finds the PCI Target device resource requirement
                       if (!IsProgrammed) {
                           Status = QueryPciDeviceResources(PciDeviceInfo);
                           if (EFI_ERROR(Status)) {
                               continue;
                           }
                       } else {
                           // If device is already programmed with BAR, then don't query it
                           PciDeviceInfo->IsBarProgrammed = TRUE;
                           PciDeviceInfo->IsBarPreProgrammed = TRUE;
                       }
                       
                       ParentBridgeExtInfo->ChildDeviceCount++;
                       PeiPciPrivateData->PciDeviceCount++;
                       InsertTailList (&PeiPciPrivateData->PciDeviceList, &PciDeviceInfo->Link);
                    }
                    break;

                case HEADER_TYPE_PCI_TO_PCI_BRIDGE:
                    
                    DEBUG((DEBUG_INFO, "Discovered PCI 2 PCI Bridge Device @B[%X]|D[%X]|F[%X]\n",
                                                                 Bus,Device,Function));
                    
                    RootBridgeExtInfo = GetRootBridgeExtPtr(ParentBridge);
                    if(RootBridgeExtInfo == NULL) {
                        return EFI_NOT_FOUND;
                    }
                    
                    // Check whether the P2P bridge is pre-programmed. If yes, get its Secondary and Subordinate
                    // bus numbers and enumerate devices using it.
                    // If bridge is not pre-programmed, then get the secondary bus number being assigned to
                    // this bridge
                    // Note: 1. If P2P bridge is pre-programmed, then assumes that all the devices under it are also pre-programmed
                    // 2. Assuming that P2P bridge pre-initialized with full PCI enumeration data. Means Secondary, Subordinate bus number
                    //programmed for P2P bridges during full PCI enumeration, assigned same to P2P bridge during pre-initialization
                    IsProgrammed = CheckIsBridgePreProgrammed(ParentBridge, PciAddr, &PciBusException);
                    if(!IsProgrammed) {
                        while(CheckIfBusResourcePresent(RootBridgeExtInfo, ++gLastUsedBusNumber));
                    }
                    
                    PciDeviceInfo = AllocateZeroPool (sizeof(PEI_PCI_DEV_INFO) + sizeof(PEI_PCI_BRIDGE_INFO_EXT));
                    if (PciDeviceInfo == NULL) {
                        return EFI_OUT_OF_RESOURCES;
                    }
                    
                    PciDeviceInfo->Type = tPci2PciBrg;
                    PciDeviceInfo->Segment = ParentBridge->Segment;
                    PciDeviceInfo->Bus = Bus;
                    PciDeviceInfo->Device = Device;
                    PciDeviceInfo->Function = Function;
                    PciDeviceInfo->ParentBridge = ParentBridge;
                    
                    // Creates Hardware PCI Device Path for PCI-PCI Bridge and 
                    // appends with Previously Created Device Path                                          
                    gPeiPciPath.Function = Function;
                    gPeiPciPath.Device = Device;                                        
                    ChildBridgeDp = PeiDevicePathAddNode(ParentDp, &gPeiPciPath.Header);
                    
                    ChildBridgeExtInfo = (PEI_PCI_BRIDGE_INFO_EXT*)(PciDeviceInfo+1);
                    ChildBridgeExtInfo->PrimaryBusNumber = Bus;
                    
                    if (gLastUsedBusNumber >= ParentBridgeExtInfo->SubordinateBusNumber) {
                        return EFI_OUT_OF_RESOURCES;
                    }

                    if(!IsProgrammed) {
                        ChildBridgeExtInfo->SecondaryBusNumber = gLastUsedBusNumber;
                        
                        // Assign Subordinate Bus number with the max value,
                        // Subordinate Bus Number of the bridge will be later updated
                        // if any bridge is found under this P2P bridge.
                        ChildBridgeExtInfo->SubordinateBusNumber = ParentBridgeExtInfo->SubordinateBusNumber;
        
                        // Program the Primary,Secondary & Subordinate Bus no. for Root Bridge.
                        PciSegmentWrite8(PciAddr + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, ChildBridgeExtInfo->PrimaryBusNumber);
                        PciSegmentWrite8(PciAddr + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, ChildBridgeExtInfo->SecondaryBusNumber);
                        PciSegmentWrite8(PciAddr + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, ChildBridgeExtInfo->SubordinateBusNumber);
                    } else {
                        ChildBridgeExtInfo->SecondaryBusNumber = PciBusException->BusBase;
                        ChildBridgeExtInfo->SubordinateBusNumber = PciBusException->BusLimit;
                        
                        // If P2P bridge programmed already by other PEI driver, then RbMmioBase and RbIoBase will
                        // have programmed bridge's MmioBase and IoBase
                        ChildBridgeExtInfo->BridgePreProgrammed = TRUE;
                        ChildBridgeExtInfo->RbMmioBase = PciBusException->MmioBase;
                        ChildBridgeExtInfo->RbMmioLimit = PciBusException->MmioLimit;
                        ChildBridgeExtInfo->RbIoBase = PciBusException->IoBase;
                        ChildBridgeExtInfo->RbIoLimit = PciBusException->IoLimit;
                    }

                    // Enumerate the Device's/Bridge's under this Bridge.
                    Status = EnumerateBus(
                                      ChildBridgeDp, 
                                      PeiPciPrivateData, 
                                      PciDeviceInfo);
                    if (EFI_ERROR(Status)) {
                        return Status;
                    }
                    
                    // If allowable child device found, then add bridge details to list
                    if ((ChildBridgeExtInfo->ChildDeviceCount) ||(ChildBridgeExtInfo->ChildBridgeCount)) {
                        InsertTailList (&PeiPciPrivateData->PciDeviceList, &PciDeviceInfo->Link);
                        ParentBridgeExtInfo->ChildBridgeCount++;       
                        PeiPciPrivateData->PciDeviceCount++;
                    }
                        
                    // Current PCI/PCI bridge enumeration is done now Set the SubBus Number for this 
                    // Bridge with the  highest numbered Pci bus segment which is behind (subordinate to)
                    // the bridge.
                    if(!IsProgrammed) {
                        ChildBridgeExtInfo->SubordinateBusNumber = gLastUsedBusNumber;
                        PciSegmentWrite8(PciAddr + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, ChildBridgeExtInfo->SubordinateBusNumber);
                    }
                    
                    break;
                    
                default:
                    break;
            } // Switch
            
            if ((Function == 0) && !MultiFunc) {
                break;
            } else if (MultiFunc) {
                MultiFunc = FALSE;
            }
        } // Function loop
    } // Device Loop
    return EFI_SUCCESS;
}

/** 
  Performs Partial Enumeration and initializes the devices based on the Class code
  specified through the ELink PEI_PCI_CLASSCODE_LIST.
  
  Follows the Below Steps:
  ------------------------
  1. First Discovers the Devices under Root Bridge or any particular Pci to Pci bridge and 
     store the location information in the PEI_PCI_DEV_INFO Structure.
  2. Calculates the Resources required by each Bridge and stores the info in the PEI_PCI_BRIDGE_INFO_EXT
  3. Assign the resources to each Pci device.
  4. Updates the Subordinate Bus Number of the Pci to Pci Bridge.
  
  @param[in]  This                  AMI_PEI_PCI_ENUMERATION_PPI instance. 
  @retval EFI_SUCCESS               The operation succeeded. A list of Pci Devices enumerated
                                    is returned
  @retval EFI_INVALID_PARAMETER     The input parameter is illegal.  
  @retval EFI_OUT_OF_RESOURCES      There is insufficient memory to store the PCI Device Data.
**/

EFI_STATUS
EFIAPI
InitializePciDevices (
    IN  AMI_PEI_PCI_ENUMERATION_PPI     *This
)
{
    EFI_STATUS                         Status;
    PEI_PCI_ENUMERATION_PRIVATE_DATA   *PeiPciPrivateData;
    PEI_PCI_DEV_INFO                   *PciRootBridgeInfo;       
    PEI_PCI_DEV_INFO                   *PciDeviceInfo;       
    PEI_PCI_BRIDGE_INFO_EXT            *PciRootBridgeInfoExt;
    UINT8                              TotalPciDevice = 0;
    UINT8                              RbCount;
    UINT8                              RbIndex;
    PCI_ROOT_BRIDGE_RESOURCE           RbResource;
    PEI_PCI_DEV_INFO                   **RootBridgeData;
    LIST_ENTRY                         *LinkData;
    
    PeiPciPrivateData = (PEI_PCI_ENUMERATION_PRIVATE_DATA*)This;
    
    // Check whether Enumeration is done already or not
    if (PeiPciPrivateData->HaveEnumeratedDevices) {
        DEBUG((DEBUG_INFO, "PCI Device Enumeration Done Already\n"));
        return EFI_SUCCESS;
    }
   
    RbCount = GetRootBridgeCount();
    if (!RbCount) {
        DEBUG((DEBUG_ERROR, "No Root Bridge found!!!\n"));
        return EFI_NOT_FOUND;
    }
    
    RootBridgeData = (PEI_PCI_DEV_INFO**)AllocateZeroPool(RbCount * sizeof(PEI_PCI_DEV_INFO *));
    if (RootBridgeData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    InitializeListHead (&PeiPciPrivateData->PciDeviceList);
    
    for (RbIndex = 0; RbIndex < RbCount; RbIndex++) {
        
        // Get resource for every Root Bridge
        Status = GetResourceForRootBridge (RbIndex, &RbResource);
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        gPeiAcpiPath.UID = RbIndex;
        
        // Creates ACPI Device Node, it is the First Node of the Device Path and 
        // Storing its Address to the Global Pointer.    
        gAcpiDp = PeiDevicePathAddNode(NULL, (EFI_DEVICE_PATH *)&gPeiAcpiPath); 
        
        // Framing RootBridge Device Info Structure.
        PciRootBridgeInfo = AllocateZeroPool(sizeof(PEI_PCI_DEV_INFO) + sizeof(PEI_PCI_BRIDGE_INFO_EXT));
        if (PciRootBridgeInfo == NULL) {
            return EFI_OUT_OF_RESOURCES;
        }
        
        RootBridgeData[RbIndex] = PciRootBridgeInfo;

        PciRootBridgeInfo->Type = tPciRootBrg;
        PciRootBridgeInfo->Bus = RbResource.BusBase;
        PciRootBridgeInfo->Segment = RbResource.Segment;
        
        PciRootBridgeInfoExt = (PEI_PCI_BRIDGE_INFO_EXT *)(PciRootBridgeInfo+1);
        
        PciRootBridgeInfoExt->RbIndex = RbIndex;
        PciRootBridgeInfoExt->Segment = RbResource.Segment;
        
        // Root bridge PrimaryBusnumber and SecondaryBusNumber points to BusBase
        // SubordinateBusNumber points to BusLimit for RootBridge
        PciRootBridgeInfoExt->PrimaryBusNumber = RbResource.BusBase;
        PciRootBridgeInfoExt->SecondaryBusNumber = RbResource.BusBase;
        PciRootBridgeInfoExt->SubordinateBusNumber = RbResource.BusLimit;
        
        PciRootBridgeInfoExt->MmioBase = RbResource.PciResourceMemBase;
        PciRootBridgeInfoExt->RbMmioBase = RbResource.PciResourceMemBase;
        PciRootBridgeInfoExt->RbMmioLimit = RbResource.PciResourceMemLimit;
        
        PciRootBridgeInfoExt->IoBase = RbResource.PciResourceIoBase;
        PciRootBridgeInfoExt->RbIoBase = RbResource.PciResourceIoBase;
        PciRootBridgeInfoExt->RbIoLimit = RbResource.PciResourceIoLimit;
        
        gLastUsedBusNumber = RbResource.BusBase;
        
        InitializeListHead(&PciRootBridgeInfoExt->ResourceExceptionList);
        InitializeListHead(&PciRootBridgeInfoExt->BusExceptionList);
        
        DEBUG((DEBUG_INFO,"Enumerating RB:[%x], Segment:[%x], Root Bus:[%x]\n", 
                                    RbIndex, RbResource.Segment, RbResource.BusBase)); 
        Status = EnumerateBus( 
                            gAcpiDp, 
                            PeiPciPrivateData, 
                            PciRootBridgeInfo);
        
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR,"Enumeration failed!!! for RB:[%x], Segment:[%x], Root Bus:[%x] = %r\n", 
                                        RbIndex, RbResource.Segment, RbResource.BusBase, Status));
        }
        
        // Last Bus number assigned under this Root Bridge
        PciRootBridgeInfoExt->SubordinateBusNumber = gLastUsedBusNumber;
    }
    
    // Check whether any Pci Device is found
    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        if(PciDeviceInfo->Type == tPciDevice) {
            TotalPciDevice++;
        }
    }
    
    DEBUG((DEBUG_INFO, "PEI PCI: Total PCI Device Found:%d\n", TotalPciDevice));
    if (!TotalPciDevice)  {
        // We didn't find any PCI Target device to proceed further so returning from here
        PeiPciPrivateData->HaveEnumeratedDevices = TRUE;
        return EFI_NOT_FOUND;
    }
    
    // We discovered PCI devices, now start calculating Resource requirement and 
    // assign resources to the devices.
    DEBUG((DEBUG_INFO,"---------------RESOURCE CALCULATION STARTS----------------\n"));
    
    for (RbIndex = 0; RbIndex < RbCount; RbIndex++) {
        DEBUG((DEBUG_INFO, "PEI PCI: RB: [%x] - CalculateBridgeResources Starts!!!\n\n", RbIndex));
        Status = CalculateBridgeResources (PeiPciPrivateData, RootBridgeData[RbIndex]);
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR, "PEI PCI: RB: [%x] - CalculateBridgeResources Status = %r!!!\n\n", RbIndex, Status));
        }
    }
    
    DEBUG((DEBUG_INFO,"---------------RESOURCE CALCULATION ENDS------------------\n\n"));
    
    DEBUG((DEBUG_INFO,"--------------RESOURCE ASSIGNMENT STARTS------------------\n"));
    
    for(RbIndex = 0; RbIndex < RbCount; RbIndex++) {
        DEBUG((DEBUG_INFO, "PEI PCI: RB: [%x] - AssignBridgeResources Starts!!!\n", RbIndex));
        Status = AssignBridgeResources (PeiPciPrivateData, RootBridgeData[RbIndex]);
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR, "PEI PCI: RB: [%x] - AssignBridgeResources Status = %r!!!\n",RbIndex, Status));
        }
    }
    
    DEBUG((DEBUG_INFO,"--------------RESOURCE ASSIGNMENT ENDS--------------------\n"));
    
    PeiPciPrivateData->HaveEnumeratedDevices = TRUE;
    
    // Register a Notification function that frees Up the resources allocated for PCI to PCI Bridge
    // and the PCI Controllers at the End of PEI phase
    PeiServicesNotifyPpi(&EndOfPeiNotifyList);
    
    return Status;
}

/** 
  Based on the specified Class Code input and DevInstance Number,Finds the PCI devices. 
  
  @param[in]      This                AMI_PEI_PCI_ENUMERATION_PPI instance. 
  @param[in]      ClassCode           Specifies the Class Code of the PCI Device to fetch.
  @param[in]      DevInstance         Instance number to discover.
  @param[in, out] PciDevice           Pointer to reference the found PciDevice.
  
  @retval EFI_SUCCESS                 The operation succeeded.PciDevice data is found. 
  @retval EFI_NOT_FOUND               No PciDevice is found at that instance.
 **/

EFI_STATUS
EFIAPI
GetNextPciDeviceByClassCode (
  IN  AMI_PEI_PCI_ENUMERATION_PPI             *This,
  IN  AMI_PEI_PCI_CLASSCODE                   PciClassCode,
  IN  UINT8                                   DevInstance,
  IN  OUT AMI_PEI_PCI_DEVICE_LOCATION         *PciDevice
)
{
    EFI_STATUS                         Status;
    AMI_PEI_PCI_CLASSCODE              *PciDeviceClassCode;
    PEI_PCI_ENUMERATION_PRIVATE_DATA   *PeiPciPrivateData;
    LIST_ENTRY                         *LinkData;
    PEI_PCI_DEV_INFO                   *PciDeviceInfo;
    
    PeiPciPrivateData = (PEI_PCI_ENUMERATION_PRIVATE_DATA*)This;
    
    if (PciDevice == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    if (!PeiPciPrivateData->HaveEnumeratedDevices) {
        // PCI Bridge Enumeration is not done before, so doing now
        Status = InitializePciDevices(This);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    for (LinkData = PeiPciPrivateData->PciDeviceList.ForwardLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->ForwardLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
        if (PciDeviceInfo->Type != tPciDevice) {
            continue;
        }
        
        PciDeviceClassCode = &PciDeviceInfo->PciDeviceClass;
        
        if ((PciDeviceClassCode->BaseClassCode == PciClassCode.BaseClassCode) &&
           (PciDeviceClassCode->SubClassCode == PciClassCode.SubClassCode)) {
            
			// When PI value is 0xFF, the PI value is not needed to be considered, skip 
            // checking PI.
            if(PciClassCode.ProgrammingInterface != 0xFF) {
                if(PciDeviceClassCode->ProgrammingInterface != PciClassCode.ProgrammingInterface) {  
                    continue;
                }
            }
            if(DevInstance == 0) {
                PciDevice->SegmentNumber = PciDeviceInfo->Segment;
                PciDevice->BusNumber = PciDeviceInfo->Bus;
                PciDevice->DeviceNumber = PciDeviceInfo->Device;
                PciDevice->FunctionNumber = PciDeviceInfo->Function;
                PciDevice->DevicePath = PciDeviceInfo->DevPath;
                DEBUG((DEBUG_INFO, "\n PeiPciEnumeration GetNextPciDeviceByClassCode: EFI_SUCCESS"));
                return EFI_SUCCESS;
            }
            DevInstance--;
        }
    }
    return EFI_NOT_FOUND;
}

/** 
  Resets the resources allocated to the PCI Devices,like Secondary Bus Number,
  Subordinate Bus Number, MEM/IO Base Address and Limit Register values.
  This is to avoid the conflict with DXE drivers. 
  
  @param[in]  PeiServices       Specifies pointer to the PEI Services data structure.
  @param[in]  This              Indicates the AMI_PEI_PCI_ENUMERATION_PPI instance. 
  @retval EFI_SUCCESS           The operation succeeded. Root Bridge Resources are cleared
  @retval EFI_INVALID_PARAMETER The input parameter is illegal.   
**/

EFI_STATUS
EFIAPI
ResetPciDeviceResources (
  IN  AMI_PEI_PCI_ENUMERATION_PPI     *This
)
{
    UINT8                             CmdReg;
    UINT32                            ResetBuffer = 0;
    PEI_PCI_DEV_INFO                  *PciDeviceInfo = NULL;
    PEI_PCI_ENUMERATION_PRIVATE_DATA  *PeiPciPrivateData = (PEI_PCI_ENUMERATION_PRIVATE_DATA*)This;
    EFI_STATUS                        Status;
    UINT64                            PciAddr;
    LIST_ENTRY                        *LinkData;
    
    // Check whether Device reset is already done
    if (PeiPciPrivateData->DeviceResetDone) {
        // Reset done already so returning from here
        return EFI_SUCCESS;
    }
    
    // The PPI has NULL interface. It is installed prior to release of PCI resources. 
    // PCI device managing PEIMs can register callback
    // on installation of this PPI to perform any required device specific processing prior
    // to the PCI device disabling by the PCI enumeration PEIM.
    Status = PeiServicesInstallPpi (&gPeiPciResetResourcesDescriptor);
    ASSERT_EFI_ERROR(Status);
    
    for (LinkData = PeiPciPrivateData->PciDeviceList.BackLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->BackLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
        PciAddr = PCI_SEGMENT_LIB_ADDRESS(PciDeviceInfo->Segment,
                                          PciDeviceInfo->Bus,
                                          PciDeviceInfo->Device,
                                          PciDeviceInfo->Function,
                                          0);
        
        // Reset the Resources Allocated for Target Pci Device
        if ((PciDeviceInfo->Type == tPciDevice) && (!PciDeviceInfo->IsBarPreProgrammed)) {
            DEBUG((DEBUG_INFO,"\nPeiPciEnumeration: Resetting assigned PCI end device resource @S[%X]|B[%X]|D[%X]|F[%X]", \
                PciDeviceInfo->Segment, PciDeviceInfo->Bus, PciDeviceInfo->Device, PciDeviceInfo->Function ));
            
            // Disable Memory and IO Space Decoding for this device.
            CmdReg = PciSegmentRead8(PciAddr + PCI_COMMAND_OFFSET);
            CmdReg &= ~(EFI_PCI_COMMAND_IO_SPACE | EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER );
            PciSegmentWrite8(PciAddr + PCI_COMMAND_OFFSET, CmdReg);
            
            // Reset the Base Address Assigned.
            if (PciDeviceInfo->Bar.Length) {
                
                PciSegmentWrite32 (PciAddr + PciDeviceInfo->Bar.Offset, ResetBuffer);

                if (PciDeviceInfo->Bar.Type == tBarMmio64) {
                    PciSegmentWrite32(PciAddr + PciDeviceInfo->Bar.Offset + 4, ResetBuffer);
                }
            }
            
        }
    }
    
    /* Don't clear Bridge resource
    for (LinkData = PeiPciPrivateData->PciDeviceList.BackLink; 
         LinkData != &PeiPciPrivateData->PciDeviceList; 
         LinkData = LinkData->BackLink) {
        
        PciDeviceInfo = BASE_CR(LinkData, PEI_PCI_DEV_INFO, Link);
        
        PciAddr = PCI_SEGMENT_LIB_ADDRESS(PciDeviceInfo->Segment,
                                          PciDeviceInfo->Bus,
                                          PciDeviceInfo->Device,
                                          PciDeviceInfo->Function,
                                          0);
        
        // Reset the Resources Allocated for Pci2PciBridge Device
        if(PciDeviceInfo->Type == tPci2PciBrg) {
            DEBUG((DEBUG_INFO,"\nPeiPciEnumeration: resetting assigned bridge resource @S[%X]|B[%X]|D[%X]|F[%X]", 
                    PciDeviceInfo->Segment, PciDeviceInfo->Bus, PciDeviceInfo->Device, PciDeviceInfo->Function ));
            PciBridgeInfoExt = (PEI_PCI_BRIDGE_INFO_EXT*)(PciDeviceInfo + 1);
            
            PciSegmentWrite8(PciAddr + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, BusNumber);
            PciSegmentWrite8(PciAddr + PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET, BusNumber);
            PciSegmentWrite8(PciAddr + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, BusNumber);

            if(PciBridgeInfoExt->BridgeProgrammed) {
                // Now reset MemBase and Limit registers
                if (PciBridgeInfoExt->MmioBaseLength) {
                    PciSegmentWrite16(PciAddr + PCI_MEMBASE, (UINT16)ResetBuffer);
                    PciSegmentWrite16(PciAddr + PCI_MEMLIMIT, (UINT16)ResetBuffer);
                }

                if( PciBridgeInfoExt->IoBaseLength ) {
                    PciSegmentWrite8(PciAddr + PCI_IOBASE, (UINT8)ResetBuffer);
                    PciSegmentWrite8(PciAddr + PCI_IOLIMIT, (UINT8)ResetBuffer);
                }
            }
            
            // Disable Memory and IO Space Decoding for this device.
            CmdReg = PciSegmentRead8(PciAddr + PCI_COMMAND_OFFSET);
            CmdReg &= ~(EFI_PCI_COMMAND_IO_SPACE | EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER );
            PciSegmentWrite8(PciAddr + PCI_COMMAND_OFFSET, CmdReg);
            
        } // Type Pci2PciBridge
    } // For loop
    */
    PeiPciPrivateData->DeviceResetDone = TRUE;
    DEBUG((DEBUG_INFO,"\n PeiPciEnumeration: Assigned PCI Device Resources reset is Successful"));
    return EFI_SUCCESS;
}

/**
    Entry Point for PeiPciEnumeration PEIM, Allocates memory for the 
    PEI_PCI_ENUMERATION_PRIVATE_DATA and Installs the AMI_PEI_PCI_ENUMERATION_PPI.
 
    @param    FileHandle
    @param    PeiServices

    @return   EFI_STATUS
 */

EFI_STATUS
EFIAPI
PeiPciEnumerationEntry(
    IN  EFI_PEI_FILE_HANDLE     FileHandle,
    IN  CONST EFI_PEI_SERVICES  **PeiServices
)
{
    EFI_STATUS                          Status;
    EFI_PEI_PPI_DESCRIPTOR              *PeiPciEnumerationDescriptor;
    PEI_PCI_ENUMERATION_PRIVATE_DATA    *PeiPciPrivateData; 
    
    PeiPciEnumerationDescriptor = (EFI_PEI_PPI_DESCRIPTOR *)AllocateZeroPool (sizeof(EFI_PEI_PPI_DESCRIPTOR));
    PeiPciPrivateData = (PEI_PCI_ENUMERATION_PRIVATE_DATA *)AllocateZeroPool (sizeof(PEI_PCI_ENUMERATION_PRIVATE_DATA));
    if((PeiPciEnumerationDescriptor == NULL) || (PeiPciPrivateData == NULL)) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    PeiPciPrivateData->PeiPciEnumerationPpi.InitDevices = InitializePciDevices;
    PeiPciPrivateData->PeiPciEnumerationPpi.GetNextDeviceByClassCode = GetNextPciDeviceByClassCode;
    PeiPciPrivateData->PeiPciEnumerationPpi.ResetDeviceResources = ResetPciDeviceResources;
    
    PeiPciEnumerationDescriptor->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    PeiPciEnumerationDescriptor->Guid = &gAmiPeiPciEnumerationPpiGuid;
    PeiPciEnumerationDescriptor->Ppi = &PeiPciPrivateData->PeiPciEnumerationPpi;
    Status = PeiServicesInstallPpi(PeiPciEnumerationDescriptor);
    DEBUG((DEBUG_INFO, "PeiPciEnumeration Entry: Installation of AMI_PEI_PCI_ENUMERATION_PPI Status:%r\n", Status));
    
    return Status;
}
