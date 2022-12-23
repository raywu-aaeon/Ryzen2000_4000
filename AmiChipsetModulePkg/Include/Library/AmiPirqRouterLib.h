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

/** @file AmiPirqRouterLib.h
  This file contains South Bridge(LPC) chipset porting library Pirq Router 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_PIRQ_ROUTER_LIB_H__
#define __AMI_PIRQ_ROUTER_LIB_H__

#include <PiDxe.h>
#include "Token.h"
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/LegacyInterrupt.h>


#ifdef __cplusplus
extern "C" {
#endif

#if     CSM_SUPPORT
EFI_STATUS SbGenInitializeRouterRegisters(
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRBIo
);

UINT8 SBGen_GetPIRQIndex(
    IN UINT8 PIRQRegister
);

EFI_STATUS SbGenReadPirq(
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    OUT UINT8                           *PirqData 
);

EFI_STATUS SbGenWritePirq(
    IN EFI_LEGACY_INTERRUPT_PROTOCOL    *This,
    IN UINT8                            PirqNumber,
    IN UINT8                            PirqData
);
#endif

#ifdef __cplusplus
}
#endif
#endif


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
