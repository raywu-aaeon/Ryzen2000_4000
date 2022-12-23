//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file OptionRomPolicyPrivate.h
    Header file for OptionRomPolicy module
**/

#ifndef _AMI_OPTION_ROM_POLICY_PRIVATE_H_
#define _AMI_OPTION_ROM_POLICY_PRIVATE_H_

#include <Efi.h>
#include <UefiHii.h>
#include <PciBus.h>
#include <Guid/MdeModuleHii.h>
#include <Library/BaseMemoryLib.h>

///Custom policy override mode
#define AMI_OPT_ITEM_PRIORITY               0
#define AMI_OPT_GROUP_PRIORITY              1

///Fail to Boot/no Video trigger var definitions
#define     ROM_FAIL_TO_BOOT                1
#define     ROM_NO_VIDEO_FOUND              2

#define     MAX_BUFFER_LEN                  1000

typedef struct _ROM_POLICY_CB_DATA{
    PCI_DEV_INFO                *PciDevInfo;
    PCI_DEV_INFO                *ParentBrgInfo;
    AMI_SDL_PCI_DEV_INFO        *PciSdlInfo;
    ROM_POLICY_VAR              *PolicyVarPtr;
    UINTN                       SdlIdx;
    EFI_STRING_ID               CbPromptStringId;
    EFI_STRING_ID               CbHelpStringId;
    UINT16                      HiiKey;
    BOOLEAN                     ShowItem;
} ROM_POLICY_CB_DATA;

typedef struct _OPROM_PCI_DEV_DATA_LIST{
    //-- Onboard Devices: to make it as T_ITEM_LST -----------
    UINTN                   ObInitCount;
    UINTN                   ObDevCount;
    ROM_POLICY_CB_DATA      **OnboardDevData;
    //-- Slot Devices: to make it as T_ITEM_LST -----------
    UINTN                   SlotInitCount;
    UINTN                   SlotDevCount;
    ROM_POLICY_CB_DATA      **SlotDevData;
} OPROM_PCI_DEV_DATA_LIST;

// main IFR form data structure
typedef struct _ROM_POLICY_INFO {
    VOID                    *StartOpCodeHandle;
    VOID                    *EndOpCodeHandle;
    EFI_IFR_GUID_LABEL      *StartLabel;
    EFI_IFR_GUID_LABEL      *EndLabel;
    ROM_SETUP_DATA          *RomSetup;
    CSM_SETUP_DATA          *CsmSetup;
//-- to make it as T_ITEM_LST -----------
    UINTN                   InitCount;
    UINTN                   RomItemsCount;
    ROM_POLICY_CB_DATA      **RomPolicyCbData;
} ROM_POLICY_INFO;

#endif  //_AMI_OPTION_ROM_POLICY_PRIVATE_H_


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

