//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************

/** @file SdioInt13Protocol.h
    Sdio Int13 protocol header definition.
**/

#ifndef _SDIO_INT13_PROT_H
#define _SDIO_INT13_PROT_H

#ifdef __cplusplus
extern "C" {
#endif

//GUID_VARIABLE_DECLARATION(gEfiSdioProtocolGuid,EFI_SDIO_PROTOCOL_GUID);
extern EFI_GUID gEfiSdioProtocolGuid;


// Values for Mass Storage Device type
//-------------------------------------
#define SDIO_MASS_DEV_HDD        1
#define SDIO_MASS_DEV_ARMD       2

typedef struct {
    UINT16      wBlockSize;         
    UINT32      dMaxLba;            
    UINT8       bHeads;             
    UINT8       bSectors;           
    UINT16      wCylinders;         
    UINT8       bNonLBAHeads;       
    UINT8       bNonLBASectors;     
    UINT16      wNonLBACylinders;   
} SDIO_DEV_INFO;

typedef struct {
    VOID                    *DevInfo;
    UINT16                  LogicalAddress;
    EFI_HANDLE              Handle;
    UINT16                  PciBDF;
    UINT8                   *DevString;
    UINT8                   StorageType;
} SDIO_MASS_DEV;

typedef EFI_STATUS (EFIAPI *EFI_SDIO_INSTALL_LEGACY_DEVICE)(SDIO_MASS_DEV*);
typedef EFI_STATUS (EFIAPI *EFI_INSTALL_SDIO_LEGACY_BOOT_DEVICES)(VOID);

typedef struct {
    EFI_SDIO_INSTALL_LEGACY_DEVICE          SdioInstallLegacyDevice;
    EFI_INSTALL_SDIO_LEGACY_BOOT_DEVICES    InstallSdioLegacyBootDevices;
} EFI_SDIO_PROTOCOL;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif 

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Parkway, Norcross, GA 30093              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
