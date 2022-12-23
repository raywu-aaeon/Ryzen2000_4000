//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985 - 2020, American Megatrends International LLC. *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file PciDxeInitPrivate.h
  Pci Dxe Initialization header
*/

#ifndef __AMI_PCI_DXE_INIT_PRIVATE__H__
#define __AMI_PCI_DXE_INIT_PRIVATE__H__

#include <Uefi.h>
#include <Protocol/AmiBoardInitPolicy.h>  


extern AMI_BOARD_INIT_PROTOCOL *gPciInitProtocolPtr;


//Data structure of CallBack delivered through eLink


typedef EFI_STATUS (AMI_BOARD_INIT_FUNCTION_PROTOTYPE) (
    IN AMI_BOARD_INIT_PROTOCOL              *This,
    IN UINTN                                *Function,
    IN OUT AMI_BOARD_INIT_PARAMETER_BLOCK   *ParameterBlock
);

typedef struct {
    UINT16                              VendorId;
    UINT16                              DeviceId;
    AMI_BOARD_INIT_FUNCTION_PROTOTYPE   *Callback;
} AMI_PCI_DEVICE_CALLBACK;

#endif

