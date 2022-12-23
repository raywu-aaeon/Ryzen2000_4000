//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
/** @file GnbPei.c
    This file contains code for AMD GNB initialization
    in the PEI stage

**/

#include <PiPei.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>

#include <Token.h>
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include <AmiChipsetModulePkg/Include/Gnb.h>
#include <Ppi/GnbPpi.h>

#include <Library/AmdSocBaseLib.h>

//----------------------------------------------------------------------------

EFI_STATUS GnbCustomerPpiProcess (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi );
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
AMI_GNB_PCI_SSID_TABLE_STRUCT gDefaultSIdTbl[] = {GNB_PCI_DEVICES_SSID_TABLE};

///----------------------------------------------------------------------------
//
///----------------------------------------------------------------------------
//tatic AMI_PEI_NBINIT_POLICY_PPI mAMIPEIGNBInitPolicyPpi =
//   {
//       TRUE
//   };

// PPI that are installed
//static EFI_PEI_PPI_DESCRIPTOR mPpiList[] =
//    { (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
//       &gAmiPEIGnbInitPolicyGuid,
//       &mAMIPEIGNBInitPolicyPpi
//    };

static EFI_PEI_NOTIFY_DESCRIPTOR NotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiGnbCustomPpiGuid, GnbCustomerPpiProcess },
};


/**
    This function programs NB PCI devices sub-vendor ID and
    sub-system ID.

    @param PeiServices Pointer to the PEI services table
    @param PciCfg Pointer to the PCI Configuration PPI

    @retval VOID

    @note  1. This routine only programs the PCI device in NB, hence, we
                 have to check the bus/device/function numbers whether they
                 are a NB PCI device or not.
              2. This routine is invoked by PEI phase.(After PEI permantent
                 memory be installed)
**/

VOID ProgramGnbSubId (
    IN EFI_PEI_SERVICES         **PeiServices)
{
    EFI_STATUS                  	Status;
    AMI_PEI_GNB_CUSTOM_PPI      	*GNBPeiOemPpi;
    AMI_GNB_PCI_SSID_TABLE_STRUCT 	volatile *SsidTblPtr = gDefaultSIdTbl;
    UINT32                          i = 0;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPeiGnbCustomPpiGuid, \
                                        0, \
                                        NULL, \
                                        &GNBPeiOemPpi );
    if (Status == EFI_SUCCESS) {
        if (GNBPeiOemPpi->SsidTable != NULL) {
            SsidTblPtr = GNBPeiOemPpi->SsidTable;
            // AVA9 : AGESAv9 provide SSID PCD. Previous implement is not required.
        }
    } // else use gDefaultSIdTbl if locate Ppi failed

    while (SsidTblPtr[i].PciAddr != 0xffffffffffffffff) {
        UINT32  Ssid = SsidTblPtr[i].Sid;
        switch(SsidTblPtr[i].PciAddr) {
            case GNB_DEV_ACG:
            case GNBACG_BUS_DEV_FUN: //For backward compatibility only, we will remove it in new AMD PI
                if (Ssid != -1) {
                    PcdSet32S (PcdCfgAzaliaSsid , Ssid);
                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "PcdCfgAzaliaSsid=%x \n",PcdGet32(PcdCfgAzaliaSsid)));
                }
                break;
            case GNB_DEV_PCIEBRIDGEx:
            case GNB_PCIEBRIDGEx_BUS_DEV_FUN: //For backward compatibility only, we will remove it in new AMD PI
                if (Ssid != -1) {    
                    PcdSet16S (PcdAmdPcieSubsystemDeviceID, (UINT16)( Ssid >> 16));
                    PcdSet16S (PcdAmdPcieSubsystemVendorID, (UINT16)Ssid);
                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "PcdAmdPcieSubsystemDeviceID=%x \n",PcdGet16(PcdAmdPcieSubsystemDeviceID)));
                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "PcdAmdPcieSubsystemVendorID=%x \n",PcdGet16(PcdAmdPcieSubsystemVendorID)));
                }
                break;
            case GNB_DEV_DGPU:
                if (Ssid != -1) {    
                    PcdSet32S (PcdCpmDgpuSsid , Ssid);
                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "PcdCpmDgpuSsid=%x \n",PcdGet32(PcdCpmDgpuSsid)));
                }
                break;
            case GNB_DEV_DGPU_AUDIO:
                if (Ssid != -1) {    
                    PcdSet32S (PcdCpmDgpuAudioSsid , Ssid);
                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "PcdCpmDgpuAudioSsid=%x \n",PcdGet32(PcdCpmDgpuAudioSsid)));
                }
                break;
            default:
                break;
        }
        i++;
    }


}

/**
    This function can be used to Notify
    PEI permantent memory be installed.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDescriptor Pointer to the descriptor for the
        notification event.
    @param InvokePpi Pointer to the PPI that was installed


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS GnbCustomerPpiProcess (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    ProgramGnbSubId(PeiServices);
    return EFI_SUCCESS;
}

/**
    This function is the entry point for this PEI. This function
    initializes the GNB

    @param FfsHeader Pointer to the FFS file header
    @param PeiServices Pointer to the PEI services table

              
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  This function should initialize North Bridge for memory detection.
              Install AMI_PEI_NBINIT_POLICY_PPI to indicate that GNB Init PEIM
              is installed
              Following things can be done at this point:
                  - Enabling top of 4GB decode for full flash ROM
                  - Programming North Bridge ports to enable access to South
                      Bridge and other I/O bridge access

**/

EFI_STATUS
EFIAPI
GnbPeiInit (
    IN       EFI_PEI_FILE_HANDLE   FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices 
  )
{
    EFI_STATUS                Status = EFI_SUCCESS;
    AMI_PEI_GNB_CUSTOM_PPI    *GNBPeiOemPpi;

    ProgramGnbSubId(PeiServices);
    
    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPeiGnbCustomPpiGuid, \
                                        0, \
                                        NULL, \
                                        &GNBPeiOemPpi );
     if (Status == EFI_SUCCESS) {
         ProgramGnbSubId(PeiServices);
     } else {
         Status = (*PeiServices)->NotifyPpi( PeiServices, NotifyList);
         ASSERT_PEI_ERROR ( PeiServices, Status );
     }

    return Status;
}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
