//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file PeiPciEnumerationResouceLib.c
    This file contains the porting function which return RootBridge resources.

**/
#include <PeiPciEnumeration.h>

/**
    Routine returns Root Bridge count
    
    @param  None
    
    @return UINT8
**/
UINT8
GetRootBridgeCount (
)
{
    return 1; //There will be one minimum root bridge available in pltform.
}

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
)
{
    RbResource->Segment = 0x00;
    RbResource->BusBase = 0x0;
    RbResource->BusLimit = 0xFF;
    RbResource->PciResourceMemBase = 0xFC000000;
    RbResource->PciResourceMemLimit = RbResource->PciResourceMemBase + 0x4000000 - 1;
    RbResource->PciResourceIoBase = 0x1000;
    RbResource->PciResourceIoLimit = RbResource->PciResourceIoBase + 0xF000 - 1;
    
    
    DEBUG((DEBUG_INFO, "RbIndex - 0x%x\n", RbIndex));
    DEBUG((DEBUG_INFO, "Segment - 0x%x\n", RbResource->Segment));
    DEBUG((DEBUG_INFO, "BusBase - 0x%x\n", RbResource->BusBase));
    DEBUG((DEBUG_INFO, "BusLimit - 0x%x\n", RbResource->BusLimit));
    DEBUG((DEBUG_INFO, "PciResourceMemBase - 0x%x\n", RbResource->PciResourceMemBase));
    DEBUG((DEBUG_INFO, "PciResourceMemLimit - 0x%x\n", RbResource->PciResourceMemLimit));
    DEBUG((DEBUG_INFO, "PciResourceIoBase - 0x%x\n", RbResource->PciResourceIoBase));
    DEBUG((DEBUG_INFO, "PciResourceIoLimit - 0x%x\n", RbResource->PciResourceIoLimit));
    
    return EFI_SUCCESS;
}

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
)
{
    return;
}

