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
/** @file CrbPcie.h
    This header file contains the CrbPcie.h definition.

**/
//*************************************************************************

#ifndef _AMI_CRB_PCIE_H_
#define _AMI_CRB_PCIE_H_

#pragma pack(1)

#define AMD_PCIE_INFO_HOB_GUID \
	{0x8196e94a, 0xe7ae, 0x452c, 0xa0, 0x12, 0x6, 0x30, 0x2a, 0xc, 0xa6, 0x63}

/// PCIe port configuration data
typedef struct _AMD_PCIE_PORT_DATA
{
    UINT8                   PortPresent;           
    UINT8                   DeviceNumber;             
    UINT8                   FunctionNumber;          
    UINT8                   LinkAspm;                 
    UINT8                   LinkHotplug;             
} AMD_PCIE_PORT_DATA;

typedef struct {
    EFI_HOB_GUID_TYPE Header;
    UINT8 AmdPcieDeviceCount;
    AMD_PCIE_PORT_DATA AmdPcieDeviceList[8];
} AMD_PCIE_DEVICE_HOB;

typedef struct {
    UINT8 DeviceEnable;
    UINT8 DeviceAspmMode;
    UINT8 DeviceHotPlug;
} AMD_PCIE_SETUP_DATA;

#pragma pack()

#endif //_AMI_CRB_PCIE_H_

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
