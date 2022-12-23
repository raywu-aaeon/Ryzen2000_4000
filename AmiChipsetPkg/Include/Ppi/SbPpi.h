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

/** @file SbPpi.h
    This header file contains the PPI definition for the SB.

*/

#ifndef FILE_PEI_SB_PPI_H_
#define FILE_PEI_SB_PPI_H_

// {95E8152B-1B98-4f11-8A77-DB26583EBC42}
#define AMI_PEI_SBINIT_POLICY_PPI_GUID  \
 {0x95e8152b, 0x1b98, 0x4f11, 0x8a, 0x77, 0xdb, 0x26, 0x58, 0x3e, 0xbc, 0x42}

// {38965BB5-8097-40f5-B742-8CC14A649B64}
#define AMI_PEI_SB_CUSTOM_PPI_GUID  \
 {0x38965bb5, 0x8097, 0x40f5, 0xb7, 0x42, 0x8c, 0xc1, 0x4a, 0x64, 0x9b, 0x64}

typedef struct _AMI_PEI_SBINIT_POLICY_PPI   AMI_PEI_SBINIT_POLICY_PPI;

struct _AMI_PEI_SBINIT_POLICY_PPI {
    UINTN                       unFlag;
};

typedef struct _AMI_SB_PCI_SSID_TABLE_STRUCT AMI_SB_PCI_SSID_TABLE_STRUCT;

struct _AMI_SB_PCI_SSID_TABLE_STRUCT {
    UINT64                      PciAddr;
    UINT32                      Sid;
};

typedef struct _AMI_GPIO_INIT_PPI           AMI_GPIO_INIT_PPI;

struct _AMI_GPIO_INIT_PPI {
    UINT32                      GpioBaseAddr;
    VOID                        *GpioTable;
    UINTN                       TableSize;    
    BOOLEAN                     InitDefaultGpioSetting;
};

typedef struct _AMI_PEI_SB_CUSTOM_PPI       AMI_PEI_SB_CUSTOM_PPI;

struct _AMI_PEI_SB_CUSTOM_PPI {
    AMI_GPIO_INIT_PPI            *GpioInit;
    AMI_SB_PCI_SSID_TABLE_STRUCT *SsidTable;
};


extern EFI_GUID gAmiPeiSbCustomPpiGuid;
extern EFI_GUID gAmiPeiSbInitPolicyGuid;

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
