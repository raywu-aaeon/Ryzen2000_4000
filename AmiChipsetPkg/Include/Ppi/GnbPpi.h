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

/** @file GnbPpi.h
    This header file contains GNB protocol definitions and structure
    definitions.

**/

#ifndef FILE_PEI_GNB_PPI_H_
#define FILE_PEI_GNB_PPI_H_

// {584CC99F-4BE8-43d1-A45A-933DC39479FC}
#define AMI_PEI_GNB_CUSTOM_PPI_GUID \
 {0x584cc99f, 0x4be8, 0x43d1, 0xa4, 0x5a, 0x93, 0x3d, 0xc3, 0x94, 0x79, 0xfc}

typedef struct _AMI_GNB_PCI_SSID_TABLE_STRUCT  AMI_GNB_PCI_SSID_TABLE_STRUCT;
typedef struct _AMI_PEI_GNB_CUSTOM_PPI         AMI_PEI_GNB_CUSTOM_PPI;

#pragma pack (push, 1)

struct _AMI_GNB_PCI_SSID_TABLE_STRUCT {
    UINT64  PciAddr;
    UINT32  Sid;
};

///
/// The AMI_PEI_GNB_CUSTOM_PPI interfaces are used to provide AMI interface for customer
///
struct _AMI_PEI_GNB_CUSTOM_PPI {
    AMI_GNB_PCI_SSID_TABLE_STRUCT *SsidTable;
};
#pragma pack (pop)

extern EFI_GUID gAmiPeiGnbCustomPpiGuid;

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
