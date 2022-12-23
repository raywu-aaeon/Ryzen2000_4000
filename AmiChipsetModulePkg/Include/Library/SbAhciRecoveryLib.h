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

/** @file SbAhciRecoveryLib.h
  This file contains South Bridg chipset porting library Ahci recovery
  functions and data structure definitions for PEI stages.
  
*/

#ifndef __AMI_AHCI_RECOVERY_LIB_H__
#define __AMI_AHCI_RECOVERY_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif


#if AhciRecovery_SUPPORT

VOID
SbSataHbaReset(
        IN EFI_PHYSICAL_ADDRESS PciConfigAddress, IN UINT16  VendorId
);

#endif  // #if AhciRecovery_SUPPORT

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
