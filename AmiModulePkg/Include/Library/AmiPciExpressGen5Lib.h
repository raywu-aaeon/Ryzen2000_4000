//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985 - 2020, American Megatrends International LLC. *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiPciExpressGen5Lib.h
   
    Library Class for AMI Pci Express GEN5 Support Functions.

**/

#ifndef _AMI_PCI_EXPRESS_GEN_5_LIB_H_
#define _AMI_PCI_EXPRESS_GEN_5_LIB_H_

//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <IndustryStandard/PciExpress50.h>
#include <Pci.h>
#include <PciE.h>
#include <PciE21.h>
#include <PciE30.h>
#include <PciBus.h>
#include <AmiLib.h>
#include <AcpiRes.h>
#include <Protocol/PciIo.h>

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------


/**
     

    @param Device Pointer to device private data structure
    @param Pcie4LnkStatus Pointer to PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_STATUS structure

    @retval EFI_STATUS Return Status
    @retval EFI_SUCCESS Set successfully.
    @retval EFI_INVALID_PARAMETER the Input parameter is invalid. 

**/
EFI_STATUS Pcie5GetEqualizationStatus(PCI_DEV_INFO *Device, PCI_EXPRESS_REG_PHYSICAL_LAYER_32_0_STATUS *Pcie5LnkStatus);

/**
    This function will Update Speed encoding and 
    display content of LNK_CAP2_REG.
    
    @param Device Pointer to PCI Device Private Data structure. 

    @retval VOID  

**/
VOID Pcie5InitDisplayPcie5Data(PCI_DEV_INFO *Device);




/**
    This function will Allocate the memory for Pcie5
    and Getting Content of LaneErrSts and MaxLanesCount
    
    @param Device Pointer to PCI Device Private Data structure.
    @param Pcie3CapOffset offset for Secondary PCIe Ext Capability.

    @retval   EFI_STATUS
        EFI_SUCCESS             When everything is going on fine!
        EFI_DEVICE_ERROR        When driver fails access PCI Bus.
        EFI_INVALID_PARAMETER   When some of the parameters are invalid. 

**/
EFI_STATUS Pcie5AllocateInitPcie5Data(PCI_DEV_INFO *Device, UINT32 Pcie5CapOffset);



/**
    Function detects if Device PCIe v5.x and up compatible

    @param Device Pointer to device private data structure

    @retval TRUE if Compatible FALSE otherwise.

**/
BOOLEAN Pcie5CheckPcie5Compatible(PCI_DEV_INFO	*Device);


#endif //_AMI_PCI_EXPRESS_GEN_5_LIB_H_
