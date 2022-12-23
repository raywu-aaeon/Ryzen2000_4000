//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985 - 2020, American Megatrends International LLC. *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiPciExpressGen5Lib.c
    Library Class for AMI Pci Express GEN 5 Support Functions. Dummy Instance


**/

//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiLib.h>
#include <AcpiRes.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Library/AmiPciBusLib.h>

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------


/**
    This function will Get & display Content of the 
    LNK_STA2 register and Check equalization Status.
    
    @param Device Pointer to PCI Device Private Data structure.
    @param LinkSpeed check LNK SPEED VECTOR.

    @retval EFI_STATUS Return Status
    @retval EFI_SUCCESS Set successfully.
    @retval EFI_INVALID_PARAMETER the Input parameter is invalid. 

**/
EFI_STATUS Pcie5GetEqualizationStatus(PCI_DEV_INFO *Device, UINT8 LinkSpeed){

    return EFI_SUCCESS;
}

/**
    This function will Update Speed encoding and 
    display content of LNK_CAP2_REG.
    
    @param Device Pointer to PCI Device Private Data structure. 

    @retval VOID  

**/
VOID Pcie5InitDisplayPcie5Data(PCI_DEV_INFO *Device){
	return;
}

/**
    This function will Allocate the memory for Pcie5
    and Getting Content of LaneErrSts and MaxLanesCount
    
    @param Device Pointer to PCI Device Private Data structure.
    @param Pcie4CapOffset offset for Secondary PCIe Ext Capability.

    @retval   EFI_STATUS
        EFI_SUCCESS             When everything is going on fine!
        EFI_DEVICE_ERROR        When driver fails access PCI Bus.
        EFI_INVALID_PARAMETER   When some of the parameters are invalid. 

**/
EFI_STATUS Pcie5AllocateInitPcie5Data(PCI_DEV_INFO *Device, UINT32 Pcie5CapOffset){
    return EFI_SUCCESS;
}

/**
    Function detects if Device PCIe v5.x and up compatible

    @param Device Pointer to device private data structure

    @retval TRUE if Compatible FALSE otherwise.

**/
BOOLEAN Pcie5CheckPcie5Compatible(PCI_DEV_INFO	*Device){
	return FALSE;
}
