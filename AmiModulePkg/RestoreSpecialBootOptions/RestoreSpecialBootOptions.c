//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file RestoreSpecialBootOptions.c

    Restore some special boot options, for example, WindowsToGo, 
    and only for UEFI boot options.
*/

#include <AmiDxeLib.h>
#include <RestoreSpecialBootOptions.h>
#include <BootOptions.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/VariableFormat.h>
#include <Library/DebugLib.h>

//
// GLOBAL VARIABLE
//
static DLIST BootOptionLinkListStructure = {0};
static DLIST *BootOptionLinkList = &BootOptionLinkListStructure;
static CHAR16 *gRestoreBootOptionsByName[] = {RESTORED_BOOT_OPTION_NAMES NULL};
static UINT8 gRegisteredBootOptionNames = sizeof(gRestoreBootOptionsByName)/sizeof(CHAR16*) - 1; // minus NULL

//
// TYPEDEF
//
typedef VOID (*PROC_FUNC)(BOOT_OPTION *Option, const int Policy);
typedef struct
{
	DLINK Link;
    BOOT_OPTION *Option;
}BOOT_OPTION_LINK;

//
// EXTERN
//
extern EFI_GUID EfiVariableGuid;

//
// DEFINE
//
#define FOR_EACH_BUCKUP_BOOT_OPTION(List,Link,Element)\
    FOR_EACH_LIST_ELEMENT((List)->pHead,Link,Element,BOOT_OPTION_LINK)

#ifndef BOOT_ORDER_COUNT
#define BOOT_ORDER_COUNT(a) (((UINT16)a) / sizeof(UINT16))
#endif

/**
    Unmask the file path that was masked before.

    @param  Option   The boot option's file path to be unmasked
*/
VOID UnMaskFilePathList(BOOT_OPTION *Option) {
    VENDOR_DEVICE_PATH *MaskedDp;
    UINTN MaskedDpLength;

    MaskedDp = (VENDOR_DEVICE_PATH*)Option->FilePathList;
    MaskedDpLength = DPLength(&MaskedDp->Header);
    if (Option->FilePathListLength <= MaskedDpLength) return;
    Option->FilePathListLength -=MaskedDpLength;
    MemCpy(
        Option->FilePathList, (UINT8*)Option->FilePathList+MaskedDpLength,
        Option->FilePathListLength
    );
}

/**
    Copy Boot Option.

    @param  DestOption    Target boot option of copy
    @param  SourceOption  Boot Option to copy from

    @retval   EFI_INVALID_PARAMETER   SourceOption or DestOption is NULL
    @retval   EFI_OUT_OF_RESOURCES    AllocateCopyPool call is failed
    @return   EFI_SUCCESS             Copy successfully
*/
EFI_STATUS CopyBootOption(
    BOOT_OPTION *DestOption, BOOT_OPTION *SourceOption
)
{
    BOOLEAN FailToCopyFlag = FALSE;
    
    if(!SourceOption || !DestOption) return EFI_INVALID_PARAMETER;

    pBS->CopyMem(DestOption, SourceOption, sizeof(BOOT_OPTION));

    //
    // Since some fields in BOOT_OPTION are pointer, 
    // we need to alocate the space for them. 
    //

    //
    // Copy Description
    //
    if(SourceOption->Description)
    {
        //
        // length = sizeof(CHAR16) * (unicode characters + 1)
        //
        DestOption->Description = AllocateCopyPool(StrSize(SourceOption->Description), SourceOption->Description);
        if(!DestOption->Description)
        {
            FailToCopyFlag = TRUE;
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "CopyBootOption :: Fails to copy (DestOption->Description)\n"));
        }
    }
    //
    // Copy FilePathList
    //
    if(SourceOption->FilePathListLength)
    {
        DestOption->FilePathList = AllocateCopyPool(SourceOption->FilePathListLength, SourceOption->FilePathList);
        if(!DestOption->FilePathList)
        {
            FailToCopyFlag = TRUE;
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "CopyBootOption :: Fails to copy (DestOption->FilePathList)\n"));
        }
    }
    //
    // Copy OptionalData
    //
    if(SourceOption->OptionalDataSize)
    {
        DestOption->OptionalData = AllocateCopyPool(SourceOption->OptionalDataSize, SourceOption->OptionalData);
        if(!DestOption->OptionalData)
        {
            FailToCopyFlag = TRUE;
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "CopyBootOption :: Fails to copy (DestOption->OptionalData)\n"));
        }
    }
    //
    // Copy BbsEntry
    //
    if(SourceOption->BbsEntry)
    {
        DestOption->BbsEntry = AllocateCopyPool(EFI_FIELD_SIZE(BOOT_OPTION, BbsEntry), SourceOption->BbsEntry);
        if(!DestOption->BbsEntry )
        {
            FailToCopyFlag = TRUE;
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "CopyBootOption :: Fails to copy (DestOption->BbsEntry)\n"));
        }
    }

    //
    // if fail...
    //
    if(FailToCopyFlag)
    {
        if(DestOption->Description)
            pBS->FreePool((VOID*)DestOption->Description);
        if(DestOption->FilePathList)
            pBS->FreePool((VOID*)DestOption->FilePathList);
        if(DestOption->OptionalData)
            pBS->FreePool((VOID*)DestOption->OptionalData);
        if(DestOption->BbsEntry )
            pBS->FreePool((VOID*)DestOption->BbsEntry);

        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}

/**
    Backup boot option according to policy.

    @param  Option  The boot option to be backed up
    @param  Policy   The policy to follow, valid values are
                        ORPHAN_BOOT_OPTIONS_POLICY_DELETE
                        ORPHAN_BOOT_OPTIONS_POLICY_DISABLE
                        ORPHAN_BOOT_OPTIONS_POLICY_KEEP
*/
VOID BackupBootOptionByPolicy(
    BOOT_OPTION *Option, const int Policy
)
{
    BOOT_OPTION       *BootOption = NULL;
    BOOT_OPTION_LINK  *BootOptionLink = NULL;
    EFI_STATUS        Status;

    if(Policy == ORPHAN_BOOT_OPTIONS_POLICY_DELETE)
    {
        //
        // Allocate the Variables
        //
        BootOption = MallocZ(sizeof(BOOT_OPTION));
        BootOptionLink = MallocZ(sizeof(BOOT_OPTION_LINK));

        if(NULL == BootOptionLink || NULL == BootOption)
        {
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "BackupBootOptionByPolicy :: Fails to MallocZ (BootOptionLink or BootOption)\n"));
            if(NULL != BootOptionLink)
                pBS->FreePool((VOID*)BootOptionLink);
            if(NULL != BootOption)
                pBS->FreePool((VOID*)BootOption);
            return;
        }

        //
        // Backup the Boot Option
        //
        Status = CopyBootOption(BootOption, Option);
        if(EFI_ERROR(Status))
        {
            DEBUG((DEBUG_BM | DEBUG_VERBOSE | DEBUG_ERROR, "BackupBootOptionByPolicy :: CopyBootOption Fail\n"));
            pBS->FreePool((VOID*)BootOptionLink);
            pBS->FreePool((VOID*)BootOption);
            return;
        }

        BootOptionLink->Option = BootOption;

        //
        // Add to BootOptionLinkList
        //
        DListAdd(BootOptionLinkList, &BootOptionLink->Link);
    }
}

/** 
    Restore orphan boot option by policy.

    @param  Option   The orphan boot option
    @param  Policy   The policy to follow, valid values are
                        ORPHAN_BOOT_OPTIONS_POLICY_DELETE
                        ORPHAN_BOOT_OPTIONS_POLICY_DISABLE
                        ORPHAN_BOOT_OPTIONS_POLICY_KEEP
*/
VOID RestoreBootOptionByPolicy(
    BOOT_OPTION *Option, int const Policy
)
{
    /*
    if(Policy==ORPHAN_BOOT_OPTIONS_POLICY_DELETE){
     }else*/
    if(Policy==ORPHAN_BOOT_OPTIONS_POLICY_DISABLE) {
        Option->Attributes |= LOAD_OPTION_ACTIVE;
    } else if(Policy==ORPHAN_BOOT_OPTIONS_POLICY_HIDE) {
        Option->Attributes &= ~LOAD_OPTION_HIDDEN;
        UnMaskFilePathList(Option);
    }
}

/**
    Find the special boot options and pass them to ProcessFunction.
    
    @param  ProcessFunction   Function that deals with boot options. 
*/    
VOID ProcessSpecialBootOptions(PROC_FUNC ProcessFunction)
{
    DLINK *Link;
    BOOT_OPTION *Option;
    UINT8 NameIndex;
    UINT8 Counter;

    if(0 == gRegisteredBootOptionNames
            || NULL == ProcessFunction) return;

    Counter = 0;
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
    {
        //
        //  Only for UEFI
        //
        if(IsLegacyBootOption(Option))
            continue;

        //
        //  Orphan?
        //
        if(IsBootOptionWithDevice(Option))
            continue;

        //
        // Has Description?
        //
        if(!Option->Description)
            continue;

        for (NameIndex = 0; NULL != gRestoreBootOptionsByName[NameIndex]; NameIndex++)
        {
            DEBUG((DEBUG_BM | DEBUG_VERBOSE, "ProcessSpecialBootOptions :: Description(%S) : (%S)\n", Option->Description, gRestoreBootOptionsByName[NameIndex]));
            if(!Wcscmp(Option->Description, gRestoreBootOptionsByName[NameIndex]))
            {
                DEBUG((DEBUG_BM | DEBUG_VERBOSE, "\tMatched\n"));
                if(Option->FwBootOption)
                {
                    (*ProcessFunction)(Option, FW_ORPHAN_BOOT_OPTIONS_POLICY);
                }
                else
                {
                    (*ProcessFunction)(Option, NON_FW_ORPHAN_BOOT_OPTIONS_POLICY);
                }

                if(++Counter == gRegisteredBootOptionNames) return;

                break;
            }
        }
    }
}

/**
    Backup special orphan boot options that will be deleted later.
*/
VOID BackupSpecialOrphanBootOptions()
{
    ProcessSpecialBootOptions((PROC_FUNC)&BackupBootOptionByPolicy);
}

/**
    Get the final boot option of Legacy Group.
    
    @param  BootOption   The start boot option of legacy group.

    @retval  BOOT_OPTION   The final boot option of this group.
*/
BOOT_OPTION* GetFinalLegacyGroupBootOption(BOOT_OPTION *BootOption)
{
    BOOT_OPTION *NextOption;
    DLINK       *Link;

    if(!BootOption)
        return NULL;

    if(!IsLegacyBootOption(BootOption))
        return NULL;

    Link = &(BootOption->Link);

    while(Link)
    {
        NextOption = OUTTER(Link->pNext, Link, BOOT_OPTION);

        if(BootOption->BootOptionNumber != NextOption->BootOptionNumber)
            return OUTTER(Link, Link, BOOT_OPTION);

        Link = Link->pNext;
    }

    return BootOption;
}

/**
    Insert boot options that backuped before.

    @param  OptionLink   Link that points to boot option.
*/
VOID InsertBackupBootOption(BOOT_OPTION_LINK *OptionLink)
{
    UINT16  i;
    UINT16  j;

    BOOT_OPTION  *Option;
    DLINK        *After = NULL;
    DLINK        *Link;

    EFI_STATUS    Status;
    UINT16        *BootOrder = NULL;
	UINTN         BootOrderSize;
    UINT16        BootOrderCount;

    if(!OptionLink)
        return;

    Status = GetEfiVariable(
                L"BootOrder",
                &EfiVariableGuid,
                NULL,
                &BootOrderSize,
                (VOID**)&BootOrder
             );

    if(!EFI_ERROR(Status))
    {
        BootOrderCount = BOOT_ORDER_COUNT(BootOrderSize);

        for(i = 0; i < BootOrderCount; i++)
        {
            if(BootOrder[i] == (UINT16)OptionLink->Option->BootOptionNumber)
                break;
        }

        if(i == BootOrderCount)
        {
            DEBUG((DEBUG_BM | DEBUG_VERBOSE, "InsertBackupBootOption :: i == BootOrderCount\n"));
            pBS->FreePool(BootOrder);
            return;
        }

        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
            for(j = 0; j < i; j++)
            {
                if(BootOrder[j] == Option->BootOptionNumber)
                {
                    if(IsLegacyBootOption(Option))
                        Option = GetFinalLegacyGroupBootOption(Option);
                    After = &(Option->Link);
                    j++;
                    break;
                }
            }

            if(j >= i)
                break;
        }

        DListInsert(BootOptionList, &(OptionLink->Option->Link), After);
        pBS->FreePool(BootOrder);

#ifdef EFI_DEBUG
        {
            BOOT_OPTION *O;
            if(After)
            {
                O = OUTTER(After, Link, BOOT_OPTION);
                DEBUG((DEBUG_BM | DEBUG_VERBOSE, "InsertBackupBootOption :: After Description(%S)\n", O->Description));
            }
            else
            {
                DEBUG((DEBUG_BM | DEBUG_VERBOSE, "InsertBackupBootOption :: After is NULL\n"));
            }
            DEBUG((DEBUG_BM | DEBUG_VERBOSE, "InsertBackupBootOption :: BackupOptionName(%S)\n", OptionLink->Option->Description));
            DUMP_BOOT_OPTION_LIST(BootOptionList, "BackupList");
        }
#endif
    }
}

/**
    Add backup Boot Options back to list.
*/
VOID AddBackupBootOptionBack(VOID)
{
    DLINK                     *Link;
    BOOT_OPTION_LINK          *BootOptionLink;
      
    if(!BootOptionLinkList->Size)
    {
        DEBUG((DEBUG_BM | DEBUG_VERBOSE, "AddBackupBootOptionBack :: BootOptionLinkList->Size is 0\n"));
        return;
    }

    FOR_EACH_BUCKUP_BOOT_OPTION(BootOptionLinkList, Link, BootOptionLink)
    {
        InsertBackupBootOption(BootOptionLink);
        
        //
        // Delete BootOptionLink entry and Release Memory
        //
        DListDelete(BootOptionLinkList, &BootOptionLink->Link);
        pBS->FreePool((VOID*)BootOptionLink);
    }
}

/**
    This eLink restores the target orphan boot options that have been applied 
    orphan policy on.

*/
VOID RestoreSpecialOrphanBootOptions() 
{
    ProcessSpecialBootOptions((PROC_FUNC)&RestoreBootOptionByPolicy);

    //
    // Restore Deleted Boot Options
    //
    AddBackupBootOptionBack();
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
