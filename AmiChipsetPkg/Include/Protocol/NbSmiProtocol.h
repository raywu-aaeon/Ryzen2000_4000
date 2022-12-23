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

/** @file NbSmiProtocol.h
    This file contains all definitions for North Bridge SMI driver.

*/

#ifndef _NB_SMI_PROTOCOL_H__
#define _NB_SMI_PROTOCOL_H__

// {FF2D54D4-5C55-4c06-8549-C3627CB8B995}
#define EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL_GUID \
    {0xff2d54d4, 0x5c55, 0x4c06, 0x85, 0x49, 0xc3, 0x62, 0x7c, 0xb8, 0xb9, 0x95}

typedef enum {
  NbErrorNone,
  NbEccError,
  NbPcieError,
  NbErrorMax,
} AMI_NB_ERROR_LOG_TYPE;

// Prototypes
typedef struct _NB_ECC_INFO
{
    UINT32 Correctable:1;
    UINT32 UnCorrectable:1;
    UINT32 EccErrDimmNum:2;   // DIMM 0/1/2/3
    UINT32 Reserved:28;
    UINT32 EccErrLog0;
    UINT32 EccErrLog1;
    UINT32 Ch0EccErrLog0;
    UINT32 Ch0EccErrLog1;
    UINT32 Ch1EccErrLog0;
    UINT32 Ch1EccErrLog1;
} NB_ECC_INFO;

typedef struct _NB_PCIE_INFO
{
  UINT8         Bus;
  UINT8         Dev;
  UINT8         Fun;
  UINT16        VendorId;
  UINT16        DeviceId;
  UINT16        PciCommand;
  UINT16        PciStatus;
  UINT16        PciCCode;
  UINT16        PcieStatus;
  UINT32        PortType;
  UINT8         Version;
  UINT16        SecondaryStatus;
  UINT16        BridgeControl;
  BOOLEAN       Correctable;
  BOOLEAN       NonFatal;
  BOOLEAN       Fatal;
  BOOLEAN       ParityError;
  BOOLEAN       SystemError;
} NB_PCIE_INFO;

typedef struct _NB_ERROR_INFO
{
  UINT8          ErrorType;
  NB_ECC_INFO    EccErrorInfo;
  NB_PCIE_INFO   PcieErrorInfo;
} NB_ERROR_INFO;

typedef struct _EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL;

#ifndef __SMM_CHILD_DISPATCH__H__
#ifndef _SB_SMI_PROTOCOL_H
typedef struct _GENERIC_LINK GENERIC_LINK;
struct _GENERIC_LINK {
    void                    *Link;
};
#endif
#endif

typedef VOID (EFIAPI *EFI_NB_ERROR_LOG_DISPATCH) (
    IN EFI_HANDLE           DispatchHandle,
    IN NB_ERROR_INFO        NbErrorInfo
);

typedef struct _NB_ERROR_LOG_DISPATCH_LINK NB_ERROR_LOG_DISPATCH_LINK;
struct _NB_ERROR_LOG_DISPATCH_LINK {
    IN NB_ERROR_LOG_DISPATCH_LINK   *Link;
    IN EFI_NB_ERROR_LOG_DISPATCH    Function;
};

typedef EFI_STATUS (EFIAPI *EFI_NB_ERROR_LOG_REGISTER) (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_NB_ERROR_LOG_DISPATCH            DispatchFunction,
    OUT EFI_HANDLE                          *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_NB_ERROR_LOG_UNREGISTER) (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                           DispatchHandle
);

struct _EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL {
    EFI_NB_ERROR_LOG_REGISTER       Register;
    EFI_NB_ERROR_LOG_UNREGISTER     UnRegister;
};

extern  EFI_GUID  gNbErrorLogDispatchProtocolGuid;

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
