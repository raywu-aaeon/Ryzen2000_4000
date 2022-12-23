//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SmmOhci.c
   AMI USB OHCI SMM driver
**/


#include <AmiDef.h>
#include <UsbDef.h>

VOID    EFIAPI HcWriteHcMem(HC_STRUC*, UINT32, UINT32);

/**
    This routine is call to enable control register.
    
    @param HcStruc   Ptr to the host controller structure
    
    @retval EFI_SUCCESS    Success to enable control register.
        
**/

EFI_STATUS
EFIAPI
OhciEnableControlReg(
    HC_STRUC    *HcStruc
)
{
    UINT32          OhciControlReg;
    //
    // Start the host controller for periodic list and control list.
    //
    OhciControlReg = (PERIODIC_LIST_ENABLE | CONTROL_LIST_ENABLE |
        BULK_LIST_ENABLE | USBOPERATIONAL);
    if (!(HcStruc->HcFlag & HC_STATE_EXTERNAL)) {
        OhciControlReg |= INTERRUPT_ROUTING;
    }
    HcWriteHcMem(HcStruc, OHCI_CONTROL_REG, OhciControlReg);
    return EFI_SUCCESS;
}
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
