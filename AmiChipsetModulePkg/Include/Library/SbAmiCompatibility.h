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

/** @file SbAmiCompatibility.h
  This header file contains AmiCompatiblityPkg items which are separated from SbCspLib.h.
  It help us to use SbCspLib.h without the dependence of AmiCompatiblityPkg.
  For future the definition of AmiCompatiblityPkg maybe deprecated.

*/

#ifndef _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_SBAMICOMPATIBILITY_H_
#define _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_SBAMICOMPATIBILITY_H_

#include <Protocol/AmiSio.h>

#pragma pack(1)

EFI_STATUS SbLibSetLpcDeviceDecoding(
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT8                    DevUid,
    IN SIO_DEV_TYPE             Type
);

EFI_STATUS SbLibSetLpcGenericDecoding(
    IN EFI_PCI_IO_PROTOCOL      *LpcPciIo,
    IN UINT16                   Base,
    IN UINT16                   Length,
    IN BOOLEAN                  Enable
);

#pragma pack()

#endif /* _AMICHIPSETMODULEPKG_INCLUDE_LIBRARY_SBAMICOMPATIBILITY_H_ */

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
