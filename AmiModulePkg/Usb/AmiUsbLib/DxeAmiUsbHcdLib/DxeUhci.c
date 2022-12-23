//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DxeUhci.c
   AMI USB UHCI DXE driver
**/


#include <AmiDef.h>
#include <UsbDef.h>

UINT32  EFIAPI HcReadPciReg(HC_STRUC*, UINT32);
VOID    EFIAPI HcWordWritePciReg(HC_STRUC*, UINT32, UINT16);


/**
    This routine is call to enable legacy register
    
    @param HcStruc   Ptr to the host controller structure
    
    @retval EFI_SUCCESS    Success to enable legacy register
        
**/

EFI_STATUS
EFIAPI
UhciEnableLegacyReg(
    HC_STRUC    *HcStruc
)
{
    return EFI_SUCCESS;
}

/**
    This routine is call to check legacy register
    
    @param HcStruc   Ptr to the host controller structure
    
    @retval TRUE     Legacy regiser is enable
    @retval FALSE    Legacy regiser is disable
        
**/
UINT8
EFIAPI
UhciCheckLegacyReg(
    HC_STRUC    *HcStruc
)
{
    return TRUE;
}

/**
    This routine is call to disable legacy register
    
    @param HcStruc   Ptr to the host controller structure
    
    @retval EFI_SUCCESS    Success to disable legacy register
        
**/
EFI_STATUS
EFIAPI
UhciDisableLegacyReg(
    HC_STRUC    *HcStruc
)
{
    return EFI_SUCCESS;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
