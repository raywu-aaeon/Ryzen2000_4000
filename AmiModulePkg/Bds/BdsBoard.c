//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/**
 * @file BdsBoard.c
 * This file contains BDS/CORE_DXE related OEM code.  There are
 * variables defined in this file that might change for each
 * OEM project
 */

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include <BootOptions.h>
#include <Setup.h>
#include <BootOptioneLinks.h>
#include <Protocol/PlatformDriverOverride.h>
#if (defined(Platform_Driver_Override_SUPPORT) && (Platform_Driver_Override_SUPPORT == 1))
#include <AmiPlatformDriverOverrideHooks.h>
#endif
#include <Protocol/LegacyBiosExt.h>
#include <Library/PcdLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/AmiListLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#define BDS_DP_NODE(NodeType, Type, SubType)  {(Type),(SubType),{sizeof(NodeType),0}}
#define BDS_END_OF_DP BDS_DP_NODE(EFI_DEVICE_PATH_PROTOCOL, END_DEVICE_PATH, END_ENTIRE_SUBTYPE)

//Local function
BOOLEAN IsShellDevicePath(EFI_DEVICE_PATH_PROTOCOL *Dp);
// Defined in Bds.c
EFI_STATUS FwLoadFile (
    IN EFI_LOAD_FILE_PROTOCOL *This, IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
    IN BOOLEAN BootPolicy, IN OUT UINTN *BufferSize,
    IN VOID *Buffer OPTIONAL
);
BOOLEAN IsSecureBoot();
//---------------------------------------------------------------------------
// MACRO Constants
//---------------------------------------------------------------------------
#ifndef FW_ORPHAN_BOOT_OPTIONS_POLICY
#define FW_ORPHAN_BOOT_OPTIONS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_DELETE
#endif
#ifndef NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
#define NON_FW_ORPHAN_BOOT_OPTIONS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_KEEP
#endif
#ifndef ORPHAN_GROUP_HEADERS_POLICY
#define ORPHAN_GROUP_HEADERS_POLICY ORPHAN_BOOT_OPTIONS_POLICY_DELETE
#endif

//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------
typedef enum{
//    BoTagLegacyXxx
//    BoTagUefiXxx
//    BoTagXxx
    BoTagLegacyFloppy,
    BoTagLegacyHardDisk,
    BoTagLegacyCdrom,
    BoTagLegacyPcmcia,
    BoTagLegacyUsb,
    BoTagLegacyEmbedNetwork,
    BoTagLegacyBevDevice,
    BoTagUefi,
    BoTagEmbeddedShell
} BOOT_OPTION_TAG;

//---------------------------------------------------------------------------
// Constant and Variables declarations
//---------------------------------------------------------------------------
#ifndef DEFAULT_BOOT_TIMEOUT
#define DEFAULT_BOOT_TIMEOUT 1
#endif
const   UINT16  DefaultTimeout  = DEFAULT_BOOT_TIMEOUT;

STRING_REF BbsDevTypeNameToken[] = {
    STRING_TOKEN(STR_FD),
    STRING_TOKEN(STR_HD),
    STRING_TOKEN(STR_CD),
    STRING_TOKEN(STR_PCMCIA),
    STRING_TOKEN(STR_USB),
    STRING_TOKEN(STR_NET),
    STRING_TOKEN(STR_BEV),
    STRING_TOKEN(STR_UNKNOWN)
};

struct{
    UINT8   Type;
    UINT8   SubType;
    STRING_REF StrToken;
} DpStrings[] = {
    {MESSAGING_DEVICE_PATH, MSG_ATAPI_DP, STRING_TOKEN(STR_ATAPI)},
    {MESSAGING_DEVICE_PATH, MSG_SCSI_DP, STRING_TOKEN(STR_SCSI)},
    {MESSAGING_DEVICE_PATH, MSG_USB_DP, STRING_TOKEN(STR_USB)},
    {MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP, STRING_TOKEN(STR_NET)},
    {MEDIA_DEVICE_PATH, MEDIA_HARDDRIVE_DP, STRING_TOKEN(STR_HD)},
    {MEDIA_DEVICE_PATH, MEDIA_CDROM_DP, STRING_TOKEN(STR_CD)}
};

//these GUIDs are used by BDS.c
EFI_GUID    SetupEnterProtocolGuid=AMITSE_SETUP_ENTER_GUID;
EFI_GUID    SecondBootOptionProtocolGuid=AMITSE_AFTER_FIRST_BOOT_OPTION_GUID;

struct {
    VENDOR_DEVICE_PATH media;
    EFI_DEVICE_PATH_PROTOCOL end;
} ShellDp = {
    {
        BDS_DP_NODE(VENDOR_DEVICE_PATH, MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP),
        AMI_MEDIA_DEVICE_PATH_GUID
    },
    BDS_END_OF_DP
};

const STRING_REF UnknownDeviceToken = STRING_TOKEN(STR_UNKNOWN);

BOOT_OPTION_TAG LegacyBootOptionTags[] = {
    BoTagLegacyFloppy,
    BoTagLegacyHardDisk,
    BoTagLegacyCdrom,
    BoTagLegacyPcmcia,
    BoTagLegacyUsb,
    BoTagLegacyEmbedNetwork,
    BoTagLegacyBevDevice,
    UNASSIGNED_HIGHEST_TAG
};

BOOT_OPTION_TAG BootOptionTagPriorities[] = {
    BOOT_OPTION_TAG_PRIORITIES,
    UNASSIGNED_HIGHEST_TAG
};

BOOLEAN NormalizeBootOptionName = NORMALIZE_BOOT_OPTION_NAME;
BOOLEAN NormalizeBootOptionDevicePath = NORMALIZE_BOOT_OPTION_DEVICE_PATH;

//---------------------------------------------------------------------------
// Function Implementations
//---------------------------------------------------------------------------

/**
 * Search for, and return, a pointer to the specific device path node of type/subtype.
 *
 * @param DevicePath Device Path to search
 * @param Type Device path type to find
 * @param SubType Device path subtype to find
 *
 * @return EFI_DEVICE_PATH_PROTOCOL Pointer to the desired device path node
 * @retval NULL No device path nodes were found
 */
static EFI_DEVICE_PATH_PROTOCOL*
FindDeviceNodeInDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN UINT8 Type,
  IN UINT8 SubType)
{
    while(DevicePath != NULL && !isEndNode(DevicePath))
    {
        if(DevicePath->Type == Type && DevicePath->SubType == SubType)
            return DevicePath;
        DevicePath = NEXT_NODE(DevicePath);
    }
    return NULL;
}

/**
 * This function returns a value of attributes that should be used for UEFI Variables used in Setup
 *
 * @retval UINT32 variable attributes
 */
UINT32 GetSetupVariablesAttributes(){
    SETUP_DATA *SetupData = NULL;
    UINTN VariableSize = 0;
    UINT32 Attributes;
    EFI_STATUS Status;
    static EFI_GUID SetupGuid = SETUP_GUID;

    Status = GetEfiVariable(L"Setup", &SetupGuid, &Attributes, &VariableSize, (VOID**)&SetupData);
    if (EFI_ERROR(Status)) {
        return EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
    } else {
        pBS->FreePool(SetupData);
        return Attributes;
    }
}

/**
 * This function converts node from the device path to a string. Once the whole
 * device path is converted the string is used as a boot option name. This
 * function is only used as a component name protocol, it does not report
 * the device name.
 *
 * @param Dp Pointer to the device path node
 *
 * @retval STRING_REF string token (-1, if the string token is not available)
 */
STRING_REF DevicePathNodeToStrRef(EFI_DEVICE_PATH_PROTOCOL *Dp){
    UINTN i;
    //Built in Shell is a special case
    if (IsShellDevicePath(Dp)) return STRING_TOKEN(STR_SHELL);
    //BBS device path is another special case
    if ( Dp->Type==BBS_DEVICE_PATH ){
        return BbsDevTypeNameToken[BBS_DEVICE_TYPE_TO_INDEX(((BBS_BBS_DEVICE_PATH*)Dp)->DeviceType)];
    }
    for (i=0; i < sizeof(DpStrings)/sizeof(DpStrings[0]); i++){
        if ((Dp->Type==DpStrings[i].Type) && (Dp->SubType==DpStrings[i].SubType)){
            return DpStrings[i].StrToken;
        }
    }//for i

    return INVALID_STR_TOKEN;
}

/**
 * Using the passed BBS_TABLE entry pointer, determine the device type of the associated device
 *
 * @param BbsEntry Pointer to a BBS_TABLE entry
 *
 * @retval UINT16 device type of the BBS entry, see LegacyBios.h for actual values
 *          BBS_FLOPPY
 *          BBS_HARDDISK
 *          BBS_CDROM
 *          BBS_PCMCIA
 *          BBS_USB
 *          BBS_EMBED_NETWORK
 *          BBS_BEV_DEVICE
 */
UINT16 GetBbsEntryDeviceTypeDefault(BBS_TABLE *BbsEntry){
    UINT16 DeviceType = BbsEntry->DeviceType;
#if BBS_USB_DEVICE_TYPE_SUPPORT
    if (   BbsEntry->Class == PCI_CL_SER_BUS
        && BbsEntry->SubClass == PCI_CL_SER_BUS_SCL_USB
    ) return BBS_USB;
#endif
#if BBS_NETWORK_DEVICE_TYPE_SUPPORT
    if (   BbsEntry->Class == PCI_CL_NETWORK
        && BbsEntry->DeviceType == BBS_BEV_DEVICE
    ) return BBS_EMBED_NETWORK;
#endif
    return DeviceType;
}

/**
 * Using the passed BOOT_OPTION structure, which should correspond to a legacy device entry, determine the device type
 *
 * @param Option pointer to the BOOT_OPTION structure for the device in question
 *
 * @retval UINT16 device type of the BOOT_OPTION item, see LegacyBios.h for actual values
 *          BBS_FLOPPY
 *          BBS_HARDDISK
 *          BBS_CDROM
 *          BBS_PCMCIA
 *          BBS_USB
 *          BBS_EMBED_NETWORK
 *          BBS_BEV_DEVICE
 */
UINT16 GetLegacyDevOrderType(BOOT_OPTION *Option){
    return ((BBS_BBS_DEVICE_PATH*)Option->FilePathList)->DeviceType;
}

/**
 * For the passed Tag entry, return the correct boot priority based on  the BootOptionTagPriorities global variable that is filled out based on the SDL Token BOOT_OPTION_TAG_PRIORITIES.
 *
 * @param Tag one of the following items of the BOOT_OPTION_TAG enum:
 *          BoTagLegacyFloppy
 *          BoTagLegacyHardDisk
 *          BoTagLegacyCdrom
 *          BoTagLegacyPcmcia
 *          BoTagLegacyUsb
 *          BoTagLegacyEmbedNetwork
 *          BoTagLegacyBevDevice
 *          BoTagUefi
 *          BoTagEmbeddedShell
 *
 * @retval The index of this item in the BootOptionTagPriorities structure, which also corresponds to the boot priority that should be assigned to this class of device
 */
UINT32 FindTagPriority(UINT16 Tag){
    UINT32 i;
    for(i=0; BootOptionTagPriorities[i]!=UNASSIGNED_HIGHEST_TAG; i++)
        if (Tag==BootOptionTagPriorities[i]) return i;
    return UNASSIGNED_HIGHEST_TAG;
}

/**
 * Determine if the passed BOOT_OPTION is the built in EFI Shell
 *
 * @param Option the boot option in question
 *
 * @retval BOOLEAN TRUE - this boot option represent the built in EFI Shell
 * @retval FALSE this is not the built in EFI Shell
 */
BOOLEAN IsShellDevicePath(EFI_DEVICE_PATH_PROTOCOL *Dp){

    if (Dp==NULL) return FALSE;
    if (   NODE_LENGTH(Dp)!=NODE_LENGTH(&ShellDp.media.Header)
        || MemCmp(Dp,&ShellDp.media.Header,NODE_LENGTH(Dp))!=0
    ) return FALSE;
    Dp=NEXT_NODE(Dp);
    if (isEndNode(Dp)) return TRUE;

    if (   Dp->Type==MEDIA_DEVICE_PATH
        && Dp->SubType==MEDIA_FV_FILEPATH_DP
        && guidcmp(&((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)Dp)->FvFileName, PcdGetPtr(PcdShellFile))==0
    ) return TRUE;

    return FALSE;
}

/**
 * Go through the entire boot option list and Apply priorities for each entry in the list.
 *
 * @param BootOptionList the entire Boot Option List
 *
 * @note  To change boot order priorities, do not modify this function, modify the SDL Token BootOptionTagPriorities.
 */
VOID SetBootOptionTags(){
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT32 UefiBootOptionsInc = 0x100;

    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        UINT32 TagPriority;
        UINT32 BaseTag = UNASSIGNED_HIGHEST_TAG;
        if (IsLegacyBootOption(Option)){
            UINT16 DeviceType;
            if (Option->FilePathList==NULL)
                DeviceType = GetBbsEntryDeviceType(Option->BbsEntry);
            else
                DeviceType = ((BBS_BBS_DEVICE_PATH*)Option->FilePathList)->DeviceType;
            BaseTag = LegacyBootOptionTags[BBS_DEVICE_TYPE_TO_INDEX(DeviceType)];
        }else
        if (IsShellDevicePath(Option->FilePathList)) BaseTag = BoTagEmbeddedShell;
        else BaseTag = BoTagUefi;
        if (BaseTag == UNASSIGNED_HIGHEST_TAG) continue;
        TagPriority = FindTagPriority((UINT16)BaseTag);
        //UEFI boot options must have unique tags, otherwise then will be grouped when
        //GROUP_BOOT_OPTIONS_BY_TAG tokens is enabled
        if (BaseTag == BoTagUefi || BaseTag == BoTagEmbeddedShell)
            BaseTag += UefiBootOptionsInc++;
        Option->Tag = BootOptionTag(BaseTag, TagPriority);
    }
}

/**
 * Create a Group Header Entry for the passed BOOT_OPTION and add the group header
 * to the master boot options list
 *
 * @param BootOptionList the master boot options list to add the newly created group item
 * @param FirstGroupOption the boot option which needs linked to a group item
 */
VOID CreateGroupHeader(DLIST *BootOptions, BOOT_OPTION *FirstGroupOption){
    static struct {
        BBS_BBS_DEVICE_PATH bbs;
        EFI_DEVICE_PATH_PROTOCOL end;
    } BbsDpTemplate =  {
        {
            BDS_DP_NODE(BBS_BBS_DEVICE_PATH,BBS_DEVICE_PATH,BBS_BBS_DP),
            BBS_HARDDISK,0,{0}
        },
        BDS_END_OF_DP
    };

    BOOT_OPTION *Option;

    if (!IsLegacyBootOption(FirstGroupOption)) return;
    Option = CreateBootOption(BootOptions);
    Option->BootOptionNumber = FirstGroupOption->BootOptionNumber;
    Option->Priority = FirstGroupOption->Priority;
    Option->Tag = FirstGroupOption->Tag;
    Option->FwBootOption = TRUE;
    Option->GroupHeader = TRUE;
    BbsDpTemplate.bbs.DeviceType=GetBbsEntryDeviceType(FirstGroupOption->BbsEntry);
    Option->FilePathList = DPCopy(&BbsDpTemplate.bbs.Header);
    Option->FilePathListLength = DPLength(Option->FilePathList);
    ConstructBootOptionName(Option);
}

/**
 * Go through the boot option list and set the priorities of each group of devices
 *
 * @param BootOptionList the master list of boot options
 */
VOID SetBootOptionPriorities(){
    DLINK *Link;
#if GROUP_BOOT_OPTIONS_BY_TAG
    UINT16 PreviousBootOptionNumber = INVALID_BOOT_OPTION_NUMBER;
    UINT32 PreviousTag = UNASSIGNED_HIGHEST_TAG;
#endif
    UINT32 PreviousPriority=0;
    BOOT_OPTION *Option;
    UINT16 NextOptionNumber;

    //Detect first unused boot option number
    NextOptionNumber = 0;
    if (!DListEmpty(BootOptionList)){
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
            if (   Option->BootOptionNumber != INVALID_BOOT_OPTION_NUMBER
                && Option->BootOptionNumber > NextOptionNumber
            ) NextOptionNumber = Option->BootOptionNumber;
        }
        NextOptionNumber++;
    }

    SortList(BootOptionList, CompareTagThenPriority);
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
#if GROUP_BOOT_OPTIONS_BY_TAG
        if (Option->BootOptionNumber==INVALID_BOOT_OPTION_NUMBER){
            if (   PreviousTag != Option->Tag
                || Option->Tag==UNASSIGNED_LOWEST_TAG
                || Option->Tag==UNASSIGNED_HIGHEST_TAG
            ) PreviousBootOptionNumber=NextOptionNumber++;
            Option->BootOptionNumber=PreviousBootOptionNumber;
            Option->Priority=++PreviousPriority;
        }else{
            PreviousBootOptionNumber = Option->BootOptionNumber;
            PreviousPriority = Option->Priority;
        }
        PreviousTag = Option->Tag;
#else
        if (Option->BootOptionNumber==INVALID_BOOT_OPTION_NUMBER){
            Option->BootOptionNumber=(NextOptionNumber)++;
            Option->Priority=++PreviousPriority;
        }else{
            PreviousPriority = Option->Priority;
        }
#endif
    }
    DUMP_BOOT_OPTION_LIST(BootOptionList,"After Setting Priorities");
}

/**
 * Go through the the boot option list and  create group header items for
 * groups of items with the same tag value.
 *
 * @param Pointer to the group of boot options
 *
 * @note  This function assumes that the BootOptionList is already sorted by tag and then by priority.  \
 * Failure to adhere to those assumptions will cause undesired behavior
 */
VOID CreateGroupHeaders(DLIST *BootOptions){
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT32 PreviousTag = UNASSIGNED_LOWEST_TAG;

    //PRECONDITION: Boot Option List is sorted by tag then by priority

    DUMP_BOOT_OPTION_LIST(BootOptions,"Before Adding Group Headers");
    FOR_EACH_BOOT_OPTION(BootOptions,Link,Option){
        if (PreviousTag == Option->Tag) continue;
        PreviousTag = Option->Tag;
        if (   Option->Tag==UNASSIGNED_LOWEST_TAG
            || Option->Tag==UNASSIGNED_HIGHEST_TAG
        ) continue;
        if (!Option->GroupHeader) CreateGroupHeader(BootOptions,Option);
    }
}


/**
 * Apply the correct policy to the passed orphaned boot options
 *
 * @param BootOptionList the master boot option list
 * @param Option The orphaned boot option
 * @param Policy the policy to follow, valid values are
 *      ORPHAN_BOOT_OPTIONS_POLICY_DELETE
 *      ORPHAN_BOOT_OPTIONS_POLICY_DISABLE
 *      ORPHAN_BOOT_OPTIONS_POLICY_KEEP
 */
VOID ApplyOrphanBootOptionPolicy(
    DLIST *BootOptions, BOOT_OPTION *Option, const int Policy
){
    if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DELETE){
        if (Option->BootOptionNumber!=INVALID_BOOT_OPTION_NUMBER){
            CHAR16 BootStr[9];
            UnicodeSPrint(BootStr, 9*sizeof(CHAR16), L"Boot%04X",Option->BootOptionNumber);
            pRS->SetVariable(
                BootStr, &gEfiGlobalVariableGuid, 0, 0, NULL
            );
        }
        DeleteBootOption(BootOptions, Option);
    }else if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_DISABLE){
        Option->Attributes &= ~LOAD_OPTION_ACTIVE;
    }else if (Policy==ORPHAN_BOOT_OPTIONS_POLICY_HIDE){
        Option->Attributes |= LOAD_OPTION_HIDDEN;
        MaskFilePathList(Option);
    }
}

/**
 * Attempts to find stale boot options in the master boot option list, and apply the specified policy to them.
 *
 * @note Policy is based on SDL tokens: FW_ORPHAN_BOOT_OPTIONS_POLICY and NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
 */
VOID PreProcessBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    // Process boot options not associated with the particular boot device.
    // We can't process group headers just yet because groups that
    // are non-empty now, can become empty at the end of this loop
    // once their orphan members are deleted.
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        //skip group headers for now; we'll process them later
        //in the PostProcessBootOptions
        if (Option->GroupHeader || IsBootOptionWithDevice(Option))
            continue;
        if (Option->FwBootOption)
            ApplyOrphanBootOptionPolicy(
                BootOptionList, Option, FW_ORPHAN_BOOT_OPTIONS_POLICY
            );
        else
            ApplyOrphanBootOptionPolicy(
                BootOptionList, Option, NON_FW_ORPHAN_BOOT_OPTIONS_POLICY
            );
    }
}

/**
 * Go through the master boot option list and apply orphan boot option policy to the boot option groups
 */
VOID PostProcessBootOptions(){
    DLINK *Link;
    BOOT_OPTION *Option;

    SortList(BootOptionList, CompareTagThenPriority);
    //Now we are ready for the processing of orphan group headers.
    //process empty groups ( groups with just the header)
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (!Option->GroupHeader) continue;
        if (   Link==NULL
            || OUTTER(Link,Link,BOOT_OPTION)->Tag != Option->Tag
        ) ApplyOrphanBootOptionPolicy(
            BootOptionList, Option, ORPHAN_GROUP_HEADERS_POLICY
          );
    }

#if GROUP_BOOT_OPTIONS_BY_TAG
    CreateGroupHeaders(BootOptionList);
#endif
}

/**
 * Based on the passed boot option, determine if a prefix needs prepended to the front
 * of the boot option name.  If return value is non-zero, then the returned number of
 * CHAR16s from the Name buffer should prepended to the front of the boot option name
 *
 * @param Option boot option in question
 * @param Name pointer to the buffer in which to return the prefix
 * @param NameSize size of the buffer being passed
 *
 * @retval Number of Unicode characters printed into the Name buffer excluding the terminating zero.
 */
UINTN ConstructBootOptionNamePrefixDefault(BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize){
    EFI_STATUS Status;
    if (IsLegacyBootOption(Option)) return 0;
    Status = HiiLibGetString(HiiHandle, STRING_TOKEN(STR_UEFI_PREFIX), &NameSize, Name);
    if(!EFI_ERROR(Status))
        return (NameSize/sizeof(CHAR16))-1;
    else
        return UnicodeSPrint(Name, NameSize, L"UEFI: ");
}

/**
 * Based on the passed boot option, determine if anything needs appended
 * to the boot option name string.  If return value is not zero, then the
 * returned number of characters should be appended to the end of the name
 * string buffer.
 *
 * @param Option the boot option in question
 * @param Name pointer to the buffer to return the append string
 * @param NameSize the size of the buffer being passed
 */
UINTN ConstructBootOptionNameSuffixDefault(
    BOOT_OPTION *Option, CHAR16 *Name, UINTN NameSize
){
    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL;
    HARDDRIVE_DEVICE_PATH *HddDp = NULL;

    EFI_STATUS Status;
    CHAR16 Buffer[30];
    UINTN Size = sizeof(Buffer);

    if (IsLegacyBootOption(Option)) return 0;
    Status = pBS->HandleProtocol(Option->DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID**)&Dp);
    if(!EFI_ERROR(Status)) {
        HddDp = (HARDDRIVE_DEVICE_PATH*)FindDeviceNodeInDevicePath(Dp, MEDIA_DEVICE_PATH, MEDIA_HARDDRIVE_DP);
        if(HddDp != NULL) {
            Status = HiiLibGetString(HiiHandle, STRING_TOKEN(STR_PARTITION), &Size, Buffer);
            if(!EFI_ERROR(Status)) {
                NameSize = UnicodeSPrint(Name, NameSize, L", %s %d", Buffer, HddDp->PartitionNumber);
                return NameSize;
            }
        }
    }
    return 0;
}

VOID CreateShellBootOption(){
    DLINK *Link;
    BOOT_OPTION *Option;
    EFI_HANDLE Handle;
    EFI_DEVICE_PATH_PROTOCOL *Dp;
    EFI_STATUS Status;
    UINTN BufferSize;

    // Check if Shell boot option already exists
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (IsShellDevicePath(Option->FilePathList)){
            return;
        }
    }
    // Do not create Shell boot option if secure boot is on
    if (IsSecureBoot()) return;
    Dp = &ShellDp.media.Header;
    // Locate FW LoadFile instance
    Status=pBS->LocateDevicePath(
        &gEfiLoadFileProtocolGuid, &Dp, &Handle
    );
    if (EFI_ERROR(Status)) return;
    // Check if Shell is part of the ROM image
    BufferSize = 0;
    Status = FwLoadFile(NULL, NULL, TRUE, &BufferSize, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL)  return;
    Option = CreateBootOption(BootOptionList);
    ASSERT(Option!=NULL);
    if (Option==NULL) return;
    Option->DeviceHandle = Handle;
    Option->FwBootOption = TRUE;
    ConstructBootOptionName(Option);
    if (!BuildBootOptionFilePath(Option)){
        Option->FilePathList=NULL;
        Option->FilePathListLength=0;
    }
    Option->DeviceHandle = INVALID_HANDLE;
}

VOID DeleteShellBootOptionOnSecureBoot(){
    DLINK *Link;
    BOOT_OPTION *Option;

    if (!IsSecureBoot()) return;
    // Check if Shell boot option already exists
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option){
        if (IsShellDevicePath(Option->FilePathList)){
            // Since Shell is not a trusted application,
            // Shell boot option should not exist when secure boot is on.
            // Shell is not considered trusted because it contains commands that allow direct memory and disk modification.
            // These commands can be used to bypass secure boot protections.
            if (Option->BootOptionNumber!=INVALID_BOOT_OPTION_NUMBER){
                CHAR16 BootStr[9];
                UnicodeSPrint(BootStr, 9*sizeof(CHAR16), L"Boot%04X",Option->BootOptionNumber);
                pRS->SetVariable(
                    BootStr, &gEfiGlobalVariableGuid, 0, 0, NULL
                );
            }
            DeleteBootOption(BootOptionList,Option);
            DEBUG((DEBUG_INFO,"Secure boot is enabled. Deleting Shell boot option.\n"));
            return;
        }
    }
}

extern DEVICE_PATH_TO_DEVICE_MATCH_TEST BOOT_OPTION_DP_MATCHING_FUNCTIONS EndOfDpMatchingFunctions;
DEVICE_PATH_TO_DEVICE_MATCH_TEST *DpMatchingFunction[] = {
    BOOT_OPTION_DP_MATCHING_FUNCTIONS NULL
};

extern BOOT_OPTION_TO_DEVICE_MATCH_TEST BOOT_OPTION_MATCHING_FUNCTIONS EndOfMatchingFunctions;
BOOT_OPTION_TO_DEVICE_MATCH_TEST *MatchingFunction[] = {
    BOOT_OPTION_MATCHING_FUNCTIONS NULL
};

extern FILTER_BOOT_DEVICE_TEST BOOT_OPTION_BOOT_DEVICE_FILTERING_FUNCTIONS EndOfFilteringFunctions;
FILTER_BOOT_DEVICE_TEST *FilteringFunction[] = {
    BOOT_OPTION_BOOT_DEVICE_FILTERING_FUNCTIONS NULL
};

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_BUILD_NAME_FUNCTIONS EndOfBuildNameFunctions;
CONSTRUCT_BOOT_OPTION_NAME *BuildNameFunctions[] = {
    BOOT_OPTION_BUILD_NAME_FUNCTIONS NULL
};

extern BUILD_BOOT_OPTION_FILE_PATH_LIST BOOT_OPTION_BUILD_FILE_PATH_FUNCTIONS EndOfBuildFilePathFunctions;
BUILD_BOOT_OPTION_FILE_PATH_LIST *BuildFilePathFunctions[] = {
  BOOT_OPTION_BUILD_FILE_PATH_FUNCTIONS NULL
};

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_NAME_PREFIX_FUNCTION;
CONSTRUCT_BOOT_OPTION_NAME *ConstructBootOptionNamePrefix = BOOT_OPTION_NAME_PREFIX_FUNCTION;

extern CONSTRUCT_BOOT_OPTION_NAME BOOT_OPTION_NAME_SUFFIX_FUNCTION;
CONSTRUCT_BOOT_OPTION_NAME *ConstructBootOptionNameSuffix = BOOT_OPTION_NAME_SUFFIX_FUNCTION;

#ifndef BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION
#define BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION GetBbsEntryDeviceTypeDefault
#endif
extern GET_BBS_ENTRY_DEVICE_TYPE BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION;
GET_BBS_ENTRY_DEVICE_TYPE *GetBbsEntryDeviceType = BOOT_OPTION_GET_BBS_ENTRY_DEVICE_TYPE_FUNCTION;

#if FAST_BOOT_SUPPORT
VOID FastBoot();
BOOLEAN IsFastBoot();
/**
 * Helper function which calls the IsFastBoot() function to check if the system in in the
 * fast boot path. If it returns TRUE, then the FastBoot function is called.
 */
VOID FastBootHook(){
    if(IsFastBoot()) FastBoot();
}
#endif

extern BDS_CONTROL_FLOW_FUNCTION BDS_CONTROL_FLOW EndOfBdsControlFlowFunctions;
BDS_CONTROL_FLOW_FUNCTION *BdsControlFlowFunctions[] = {
    BDS_CONTROL_FLOW NULL
};
CHAR8 *BdsControlFlowFunctionNames[] = {
    BDS_CONTROL_FLOW_NAMES NULL
};

CONST CHAR16 *FirmwareVendorString = CONVERT_TO_WSTRING(CORE_VENDOR);
CONST UINT32 FirmwareRevision = CORE_COMBINED_VERSION;

UINT32 BootOptionSupport = BOOT_MANAGER_CAPABILITIES;
UINT64 OsIndicationsSupported = OS_INDICATIONS_SUPPORTED ;

#ifndef BDS_MEMORY_USAGE_INFO_DEFINED
typedef struct{
    UINT32 Type;
    UINT32 Previous,Current,Next;
} BDS_MEMORY_USAGE_INFO;

typedef BOOLEAN (BDS_UPDATE_MEMORY_USAGE_INFORMATION)(BDS_MEMORY_USAGE_INFO *MemoryInfo, UINTN NumberOfElements);
#endif
extern BDS_UPDATE_MEMORY_USAGE_INFORMATION BDS_UPDATE_MEMORY_USAGE_INFORMATION_FUNCTION;
BDS_UPDATE_MEMORY_USAGE_INFORMATION *UpdateMemoryUsageInformation = BDS_UPDATE_MEMORY_USAGE_INFORMATION_FUNCTION;

//****************************************************************************
// Platform Driver Override protocol Prototypes and Protocol definition
#if (defined(Platform_Driver_Override_SUPPORT) && (Platform_Driver_Override_SUPPORT == 1))
EFI_STATUS EFIAPI EfiPlatformDriverOverride_GetDriver(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL              *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_HANDLE                                     *DriverImageHandle
  );

EFI_STATUS EFIAPI EfiPlatformDriverOverride_GetDriverPath(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL              *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL                       **DriverImagePath
  );

EFI_STATUS EFIAPI EfiPlatformDriverOverride_DriverLoaded(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL          *This,
  IN EFI_HANDLE                                     ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL                       *DriverImagePath,
  IN EFI_HANDLE                                     DriverImageHandle
  );

EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL EfiPlatformDriverOverrideProtocol = {
  EfiPlatformDriverOverride_GetDriver,
  EfiPlatformDriverOverride_GetDriverPath,
  EfiPlatformDriverOverride_DriverLoaded
};

///
/// This is the structure that tracks a Controller Handle as it goes through the Platform Driver Override process
typedef struct _OVERRIDE_LIST_ENTRY{
    /// Pointers used to move between the members of the Linked List
    AMI_LINK Link;
    /// Handle of the device that we are checking for an override driver for
    EFI_HANDLE ControllerHandle;
    /// The last HAndle that was returned from one of the elinked functions
    EFI_HANDLE DriverImageHandle;
    /// This is the index into the elinked functions that should be called on next entry.
    UINTN Index;
} OVERRIDE_LIST_ENTRY;
        
AMI_LIST PlatformDriverOverrideHandleList;

//****************************************************************************
// Platform Driver Override protocol installation function

VOID InstallPlatformDriverOverrideProtocol(IN EFI_HANDLE Handle)
{
    AmiListInit(&PlatformDriverOverrideHandleList);
    
    if ( PlatformDriverOverrideFunctions != NULL)
    {
        pBS->InstallMultipleProtocolInterfaces(
            &Handle,
            &gEfiPlatformDriverOverrideProtocolGuid, &EfiPlatformDriverOverrideProtocol,
            NULL
        );
    }
}


//****************************************************************************
// Platform Driver Override start
/**
 This function searches a list of controller Handle entries and returns that entry if found
 
 @param Handle - this is the Conroller Handle we are searching for
 @param Entry - this is used to return the entry form the list if found.  Data is only valid when reurn value is TRUE
 
 @return BOOLEAN 
 @retval TRUE - Handle was found in the list, Entry is valid
 @retval FALSE - Handle was not found, Entry data is NOT valid
 */
BOOLEAN IsHandleInList(EFI_HANDLE Handle, OUT OVERRIDE_LIST_ENTRY **Entry)
{
    AMI_LINK *ListPtr;
    OVERRIDE_LIST_ENTRY *ListEntry;
    
    // loop through the current list and find if the handle is already has an entry in the list
    // if so, return it.   Otherwise, return FALSE
    ListPtr = PlatformDriverOverrideHandleList.pHead;
    while (ListPtr != NULL)
    {
        ListEntry = BASE_CR(ListPtr, OVERRIDE_LIST_ENTRY, Link);  
        
        if (ListEntry->ControllerHandle == Handle )
        {
            *Entry = ListEntry;
            return TRUE;
        }
        ListPtr = ListPtr->pNext;
    }

    return FALSE;
}

/**
 * This function looks for an entry in a linked list that matches the ControllerHandle passed in.  
 * If the controller handle is not found, a new entry is created, added to the list and returned.
 * 
 * @param ControllerHandle
 * @param NewEntry
 * @return EFI_STATUS 
 * @retval EFI_OUT_OF_RESOURCES - There is not memory to create an entry on the list
 * @retval EFI_SUCCESS - New Entry points to a valid structure about the Controller Handle 
 */
EFI_STATUS FindIndexForControllerHandle (
        EFI_HANDLE ControllerHandle, 
        OVERRIDE_LIST_ENTRY **NewEntry)
{
    // go through the current list and find if the controller handle is already part of the list
    if (!IsHandleInList(ControllerHandle, NewEntry))
    {
        // if not create new entry for the controller handle and add it to the list
        *NewEntry = AllocateZeroPool(sizeof(OVERRIDE_LIST_ENTRY));
        if (*NewEntry == NULL)
            return EFI_OUT_OF_RESOURCES;
       
        (*NewEntry)->Index = 0;
        (*NewEntry)->ControllerHandle = ControllerHandle;
        (*NewEntry)->DriverImageHandle = NULL;
        AmiListAdd(&PlatformDriverOverrideHandleList, (AMI_LINK *)(*NewEntry));
    }

    return EFI_SUCCESS;
}


/**
  Retrieves the image handle of the platform override driver for a controller in the system.

  @param  This                  A pointer to the EFI_PLATFORM_DRIVER_OVERRIDE_
                                PROTOCOL instance.
  @param  ControllerHandle      The device handle of the controller to check if a driver override
                                exists.
  @param  DriverImageHandle     On input, a pointer to the previous driver image handle returned
                                by GetDriver(). On output, a pointer to the next driver
                                image handle.

  @retval EFI_SUCCESS           The driver override for ControllerHandle was returned in
                                DriverImageHandle.
  @retval EFI_NOT_FOUND         A driver override for ControllerHandle was not found.
  @retval EFI_INVALID_PARAMETER The handle specified by ControllerHandle is NULL.
  @retval EFI_INVALID_PARAMETER DriverImageHandle is not a handle that was returned on a
                                previous call to GetDriver().
**/
EFI_STATUS
EFIAPI 
EfiPlatformDriverOverride_GetDriver(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL              *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_HANDLE                                     *DriverImageHandle
  )
{
    EFI_STATUS Status = EFI_NOT_FOUND;
    UINTN i;
    OVERRIDE_LIST_ENTRY *Entry;
    
    // verify the parameter input
    if ( (This == NULL) || (ControllerHandle == NULL) || (DriverImageHandle == NULL))
    {
        return EFI_INVALID_PARAMETER;
    }

    // verify that there is a list of eLinks
    if (PlatformDriverOverrideFunctions == NULL)
    {
        return EFI_NOT_FOUND;
    }

    // Finds the previous entry or creates new entry for the controller handle
    if (EFI_ERROR(FindIndexForControllerHandle(ControllerHandle, &Entry)))
    {
        return EFI_INVALID_PARAMETER;
    }

    // if the *DriverImageHandle does not equal the last one
    // and is not NULL. It is an invalid parameter
    if ((*DriverImageHandle != NULL ) && (Entry->DriverImageHandle != *DriverImageHandle))
    {
        return EFI_INVALID_PARAMETER;
    }
    
    // There is a possibility that after ConnectController is called 
    //  DisconnectCotroller and a second call to ConnectController is called
    //  This would need Entry->Index to 0 to get the DriverImageHandles all over again
    //  
    if (*DriverImageHandle == NULL)
    {
        Entry->DriverImageHandle = *DriverImageHandle;
        Entry->Index = 0;
    }
    
    // loop through list of eLinks and give control to each one.
    for(i = Entry->Index; PlatformDriverOverrideFunctions[i] != NULL; i++, Entry->Index++)
    {
        Status = PlatformDriverOverrideFunctions[i](This, ControllerHandle, &Entry->DriverImageHandle);
        // if success, return the Driver image handle of the override driver
        if (Status == EFI_SUCCESS)
        {
            *DriverImageHandle = Entry->DriverImageHandle;
            return EFI_SUCCESS;
        }
        else if (Status == EFI_NOT_FOUND)
        {
            // the current override function does not have a driver image for this
            // controller handle.  reset the controller handle for the next override function
            *DriverImageHandle = NULL;
            Entry->DriverImageHandle = NULL;
        }
        else 
        {
            return Status; // should only be EFI_INVALID_PARAMETER
        }
    } 
    
    return Status;
}


/**
  Retrieves the device path of the platform override driver for a controller in the system.

  @param  This                  A pointer to the EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL instance.
  @param  ControllerHandle      The device handle of the controller to check if a driver override
                                exists.
  @param  DriverImagePath       On input, a pointer to the previous driver device path returned by
                                GetDriverPath(). On output, a pointer to the next driver
                                device path. Passing in a pointer to NULL will return the first
                                driver device path for ControllerHandle.

  @retval EFI_SUCCESS           The driver override for ControllerHandle was returned in
                                DriverImageHandle.
  @retval EFI_UNSUPPORTED       The operation is not supported.
  @retval EFI_NOT_FOUND         A driver override for ControllerHandle was not found.
  @retval EFI_INVALID_PARAMETER The handle specified by ControllerHandle is NULL.
  @retval EFI_INVALID_PARAMETER DriverImagePath is not a device path that was returned on a
                                previous call to GetDriverPath().
**/
EFI_STATUS
EFIAPI
EfiPlatformDriverOverride_GetDriverPath(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL              *This,
  IN     EFI_HANDLE                                     ControllerHandle,
  IN OUT EFI_DEVICE_PATH_PROTOCOL                       **DriverImagePath
  )
{
    return EFI_UNSUPPORTED;
}


/**
  Used to associate a driver image handle with a device path that was returned on a prior call to the
  GetDriverPath() service. This driver image handle will then be available through the
  GetDriver() service.

  @param  This                  A pointer to the EFI_PLATFORM_DRIVER_OVERRIDE_
                                PROTOCOL instance.
  @param  ControllerHandle      The device handle of the controller.
  @param  DriverImagePath       A pointer to the driver device path that was returned in a prior
                                call to GetDriverPath().
  @param  DriverImageHandle     The driver image handle that was returned by LoadImage()
                                when the driver specified by DriverImagePath was loaded
                                into memory.

  @retval EFI_SUCCESS           The association between DriverImagePath and
                                DriverImageHandle was established for the controller specified
                                by ControllerHandle.
  @retval EFI_UNSUPPORTED       The operation is not supported.
  @retval EFI_NOT_FOUND         DriverImagePath is not a device path that was returned on a prior
                                call to GetDriverPath() for the controller specified by
                                ControllerHandle.
  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.
  @retval EFI_INVALID_PARAMETER DriverImagePath is not a valid device path.
  @retval EFI_INVALID_PARAMETER DriverImageHandle is not a valid image handle.
**/
EFI_STATUS
EFIAPI 
EfiPlatformDriverOverride_DriverLoaded(
  IN EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL          *This,
  IN EFI_HANDLE                                     ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL                       *DriverImagePath,
  IN EFI_HANDLE                                     DriverImageHandle
  )
{
    return EFI_UNSUPPORTED;
}
#endif
