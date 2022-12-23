//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NbS3Save.h
    This header file contains constant definitions and structure
    definitions related to S3 resume data for North bridge (NPT)

**/

#pragma pack (push, 1)
typedef struct {
    UINT64                  Address;
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;

typedef struct {
    UINT64                  Index;
    UINT64                  IndexData;
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_INDEX_REGISTER_SAVE;

typedef struct {
	BOOT_SCRIPT_PCI_REGISTER_SAVE *gPciRegisters;
	UINT64	DevAddr;
} gPciRegistersSavelist;

typedef struct {
	BOOT_SCRIPT_PCI_INDEX_REGISTER_SAVE *gPciRegisters;
	UINT64	DevAddr;
} gPciIndexRegistersSavelist;
#pragma pack (pop)

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
