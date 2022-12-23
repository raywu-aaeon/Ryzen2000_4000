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

/** @file SbSmiProtocol.h
    South Bridge SMI Dispatch Protocol header.

*/

#ifndef  _SB_SMI_PROTOCOL_H
#define  _SB_SMI_PROTOCOL_H

#pragma pack(push, 1)

// {589BC616-BB4F-47ed-92F7-93393C697E25}
#define AMI_SB_SMI_PROTOCOL_GUID \
    {0x589bc616, 0xbb4f, 0x47ed, 0x92, 0xf7, 0x93, 0x39, 0x3c, 0x69, 0x7e, 0x25}

#define EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL_GUID \
    {0xf281fc6e, 0xf4c4, 0x431c, 0x96, 0x2b, 0x2f, 0x13, 0xae, 0x79, 0x84, 0xec}

#define AMI_SMBUS_SMM_PROTOCOL_GUID \
  {0x72e40094, 0x2ee1, 0x497a, 0x8f, 0x33, 0x4c, 0x93, 0x4a, 0x9e, 0x9c, 0xc}

#ifndef __SMM_CHILD_DISPATCH__H__
typedef struct _GENERIC_LINK GENERIC_LINK;
typedef struct _GENERIC_LINK {
    void                    *Link;
};
#endif

typedef struct _SB_PCIE_ERR
{
  UINT32  PcieAddress;
  UINT8   Bus;
  UINT8   Dev;
  UINT8   Fun;
  UINT16  VendorId;
  UINT16  DeviceId;
  UINT16  PciCommand;
  UINT16  PciStatus;
  UINT16  PciCCode;
  UINT16  PcieStatus;
  UINT32  PortType;
  UINT8   Version;
  UINT16  SecondaryStatus;
  UINT16  BridgeControl;
  BOOLEAN Correctable;
  BOOLEAN NonFatal;
  BOOLEAN Fatal;
  BOOLEAN ParityError;
  BOOLEAN SystemError;
} SB_PCIE_ERR;

typedef struct _EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL;

typedef VOID (EFIAPI *EFI_SB_PCIE_ERROR_LOG_DISPATCH) (
    IN EFI_HANDLE           DispatchHandle,
    IN SB_PCIE_ERR          SbPcieErrorInfo
);

typedef struct _SB_PCIE_ERROR_LOG_DISPATCH_LINK SB_PCIE_ERROR_LOG_DISPATCH_LINK;
struct _SB_PCIE_ERROR_LOG_DISPATCH_LINK {
    IN SB_PCIE_ERROR_LOG_DISPATCH_LINK   *Link;
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH    Function;
};

typedef EFI_STATUS (EFIAPI *EFI_SB_PCIE_ERROR_LOG_REGISTER) (
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH            DispatchFunction,
    OUT EFI_HANDLE                               *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SB_PCIE_ERROR_LOG_UNREGISTER) (
    IN EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                                DispatchHandle
);

struct _EFI_SB_PCIE_ERROR_LOG_DISPATCH_PROTOCOL {
    EFI_SB_PCIE_ERROR_LOG_REGISTER       Register;
    EFI_SB_PCIE_ERROR_LOG_UNREGISTER     UnRegister;
};

#pragma pack(pop)

extern  EFI_GUID  gSbPcieErrorLogDispatchProtocolGuid;
extern  EFI_GUID  gAmiSbSmiProtocolGuid;
extern  EFI_GUID  gAmiSmbusSmmProtocolGuid;

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
