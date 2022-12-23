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
/** @file SbAhciRecoveryLib.c
    This file contains south bridge related Ahci recovery library
    instance

**/
//**********************************************************************

// Module specific Includes
//#include "Efi.h"
#include "Uefi.h"
#include "Token.h"
#include "Sb.h"
#include <AmiCspLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>

#include "AmiModulePkg/AhciRecovery/AhciRecovery.h"

#include <Library/SbAhciRecoveryLib.h>
#include <IndustryStandard/Pci.h>

/**
    This function perform HBA reset.

    @param PciConfigAddress

    @retval void

**/

VOID
SbSataHbaReset(
    IN EFI_PHYSICAL_ADDRESS PciConfigAddress, 
    IN UINT16  VendorId
    )
{
    UINT32  Delay = 0;
    UINT64  GlobalControl = 0x1;
    UINT32  AhciBaseAddr;

    DEBUG((DEBUG_INFO,"\n SbSataHbaReset - PciConfigAddress = 0x%x", PciConfigAddress));
    
    AhciBaseAddr = MmioRead32((UINTN)PciConfigAddress +  PCI_BASE_ADDRESSREG_OFFSET + (PCI_BAR_IDX5 * 4));
    DEBUG((DEBUG_INFO,"\n SbSataHbaReset - AhciBaseAddr = 0x%x", AhciBaseAddr));
    
    // Perform HBA reset.
    GlobalControl = 0x01;
    HBA_WRITE_REG32(AhciBaseAddr, HBA_GHC, GlobalControl);
    
    // After issuing HBA reset software should wait till GHC.HR bit get cleared 
    // by HBA.
    for(Delay = 100; Delay > 0 ; Delay--) {
        if(!(HBA_REG32(AhciBaseAddr, HBA_GHC) & BIT0)) {
            DEBUG((DEBUG_ERROR,"\n HBA Reset Success!!"));
            break;
        }
        //Status = (**PeiServices).LocatePpi( PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, &gStallPpi );
        //    if ( EFI_ERROR( Status )) {
        //        return EFI_DEVICE_ERROR;
        //    }
        //gStallPpi->Stall( PeiServices, gStallPpi, 10000 ); // 10 msec.
    }
 
    // If HBA has not cleared GHC.HR to 0 with in 1 second then HBA is in 
    // hung or locked state.
    if( !Delay && (HBA_REG32(AhciBaseAddr, HBA_GHC) & BIT0)) {
        DEBUG((-1,"\n HBA Reset Failed"));
        ASSERT(FALSE);
    }
    DEBUG((-1,"\n Hba reset done."));
}

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
