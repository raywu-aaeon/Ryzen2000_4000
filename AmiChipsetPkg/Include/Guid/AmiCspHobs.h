
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

/** @file AmiCspHobs.h
    Definitions of AMI Chipset specific Hobs.

*/

#ifndef _AMI_CSP_HOBS_H_
#define _AMI_CSP_HOBS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <PiDxe.h>

#pragma pack(push,1)

// GUIDed Hob to pass SM Bus ArpMap
// SM_BUS_CONTROLLER_IDENTIFIER_GUID is defined in SmBusPorting.c.
#define AMI_CSP_SMBUS_HOB_GUID  SM_BUS_CONTROLLER_IDENTIFIER_GUID

typedef struct {
    EFI_HOB_GUID_TYPE   Header;
    UINT8               BoardReservedAddressCount;
    UINT32              BoardReservedAddressList;
    UINT8               ArpDeviceCount;
    UINT8               ArpDeviceList[1];
} AMI_CSP_SMBUS_HOB;

#pragma pack(pop)
/****** DO NOT WRITE BELOW THIS LINE *******/
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
