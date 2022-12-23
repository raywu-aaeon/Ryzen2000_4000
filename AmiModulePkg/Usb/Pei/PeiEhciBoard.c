//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file PeiEhciBoard.c
    This file contains routines that are board specific for
    initializing the EHCI controller in the USB Recovery module.

**/

#include <Ppi/Stall.h>
#include "PeiEhci.h"

//----------------------------------------------------------------------------
// Porting Steps:
//
// 1)  define/undefine the appropriate southbridge type
// 2)  define registers and their set/clear bits for each register to be
//     modified in each controller's PCI configuration space
// 3)  do not do any generic initialization - programming of BAR and command
//     register is done generically
//
//----------------------------------------------------------------------------



/**
    This is a porting hook for board-specific EHCI controller
    initialization

        
    @param PeiServices 
    @param Pci 
    @param StallPpi 

         
    @retval EFI_SUCCESS

**/

EFI_STATUS EhciPeiBoardInit (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI *Pci,
    IN EFI_PEI_STALL_PPI    *StallPpi )
{
    EFI_STATUS Status = EFI_SUCCESS;

    return Status;

}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
