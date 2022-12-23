//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file FastBootOption.c
 *   FastBootOption Support.
 */

#include "FastBootOption.h"
#include <Setup.h>
#include <Protocol/FastBootProtocol2.h>
#include <FastBoot2.h>

#define EFI_TPL_NOTIFY TPL_NOTIFY

#define FASTBOOT_DP_NODE(NodeType, Type, SubType)  {(Type),(SubType),{sizeof(NodeType),0}}
#define FASTBOOT_END_OF_DP FASTBOOT_DP_NODE(EFI_DEVICE_PATH_PROTOCOL, END_DEVICE_PATH, END_ENTIRE_SUBTYPE)

EFI_EVENT gExitBootServicesEvent;

TEMP_DEVICE_MAP BootOptionTemp[]={
    { TempUefiOddDevice, "UEFI:CD/DVD Drive" },
#if (!USBClassBoot_SUPPORT)
    { TempUefiRemDevice, "UEFI:Removable Device" },
#endif
    { TempUefiNetDevice, "UEFI:Network Device" }
};

extern IS_CORRECT_BOOT_OPTION_FUNC_PTR  IS_CORRECT_BOOT_OPTION_FUNCTION;

IS_CORRECT_BOOT_OPTION_FUNC_PTR *gIsCorrectBootoptionPtr = IS_CORRECT_BOOT_OPTION_FUNCTION;

/**
 * Get Variable Boot#### and return data pointer.
 *    
 * @param[in]   BootIndex            Boot option index. 
 *
 * @retval      BootOption           Buffer for BootXXX variables.
 */

EFI_LOAD_OPTION* 
GetUefiBootName(
    IN UINT16   BootIndex
)
{
    EFI_STATUS Status;
    UINTN OptionSize;
    CHAR16 BootVarName[BOOT_VAR_NAME_MAX];
    EFI_LOAD_OPTION *BootOption;                 ///buffer for BootXXX variables

    UnicodeSPrint (BootVarName, sizeof(BootVarName), gBootName, BootIndex);

    OptionSize = 0;
    Status = gRT->GetVariable( BootVarName, &gEfiGlobalVariableGuid, NULL, &OptionSize, NULL);
    if (Status != EFI_NOT_FOUND)
    {
        BootOption = Malloc( OptionSize );
        Status = gRT->GetVariable( BootVarName, &gEfiGlobalVariableGuid, NULL, &OptionSize, BootOption);
        if (!EFI_ERROR(Status)) {
            return BootOption;
        }
        return NULL;
    }
    else
        return NULL;

}

/**
 * Calculate DevicePath length.
 *    
 * @param[in]   Number             Boot option number. 
 * @param[in]   Dp                 Boot option device path.
 * @param[in]   Attributes         Boot option attributes.
 * @param[in]   OptionsName        Boot option names.
 * @param[in]   OptionsSize        Boot option names size.
 * @param[in]   DefaultName        Default boot option names.
 *
 * @retval      EFI_SUCCESS        Add boot option name success.
 */

EFI_STATUS 
AddBootOption(
    IN UINT16                   Number,
    IN EFI_DEVICE_PATH_PROTOCOL *Dp,
    IN UINT32                   Attributes, 
    IN VOID                     *OptionsName, 
    IN UINTN                    OptionsSize, 
    IN CHAR16                   *DefaultName
)
{

    EFI_LOAD_OPTION *Option;
    UINTN Size = 0, Length;
    CHAR16 BootVarName[BOOT_VAR_NAME_MAX]; ///Boot0000
    CHAR16 NameStr[NAME_STRING_LENGTH];
    EFI_STATUS Status;

    Length = DPLength(Dp);

    if ( !OptionsName ) 
        OptionsSize = 0;
    else
    {
        UnicodeSPrint (NameStr, sizeof(NameStr), L"%a", OptionsName);
        Size = (Wcslen(NameStr) + 1) * sizeof(CHAR16);
    }
    Option = Malloc(sizeof(*Option) + Size + Length);
    if (!Option) return EFI_OUT_OF_RESOURCES;

    Option->Attributes = Attributes;
    Option->FilePathListLength = (UINT16)Length;

    if (OptionsSize)
        gBS->CopyMem(Option + 1, NameStr, Size);

    gBS->CopyMem((UINT8*)(Option + 1) + Size, Dp, Length);

    UnicodeSPrint (BootVarName, sizeof(BootVarName), gBootName, Number);
    DEBUG((DEBUG_INFO,"[FastBootOption] Add %S (%S)\n", BootVarName, NameStr)); 
    Status = gRT->SetVariable(
        BootVarName, &gEfiGlobalVariableGuid,
        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
        sizeof(*Option) + Size + Length, Option
    );

    gBS->FreePool(Option);
    return Status;
}

/**
 * Create variable Boot####.
 *    
 * @param[in]   OptionNumber        Boot option number. 
 * @param[in]   DevType             Boot option device type.
 * @param[in]   Description         Boot option names.
 *
 */

void 
CreateBootOption(
    IN UINT16 OptionNumber, 
    IN UINT16 DevType, 
    IN CHAR8 *Description
)
{

static struct {
    BBS_BBS_DEVICE_PATH Bbs;
    EFI_DEVICE_PATH_PROTOCOL End;
} LegacyDp = {
        {
            FASTBOOT_DP_NODE(BBS_BBS_DEVICE_PATH,BBS_DEVICE_PATH,BBS_BBS_DP),
            0xff,0,{0}
        },
        FASTBOOT_END_OF_DP
    };

    
    LegacyDp.Bbs.DeviceType = DevType;

    AddBootOption(
            OptionNumber, &LegacyDp.Bbs.Header,
            LOAD_OPTION_ACTIVE, 
            Description, sizeof(Description) + 1, NULL);

}

/**
 * This hook will check temp boot option should add to boot option list or not.
 *    
 *
 * @retval TRUE             Add this temp boot option to list.
 * @retval FALSE            Skip this temp boot option to list.
 */
BOOLEAN 
EFIAPI 
IsCorrectBootoption(
    UINT16 DeviceTypeId
)
{
    /// User can use this hook to check this boot option 
    /// meet their requirement or not. About device type, 
    /// please check FastBootOption.h for reference.

    return TRUE;
}

/**
 * This function will create temp boot option for OS use.
 *    
 *
 * @retval EFI_SUCCESS            Create temp boot option success.
 */

EFI_STATUS 
CreateTempBootOption()
{
    EFI_STATUS Status;
    UINT16 *BootOrder = NULL, NewBootOrder[BOOT_ORDER_LENGTH];
    UINTN BootOrderSize = 0;
    INT16 Counter = 0;
    UINT16 MapIndex, BootIndex = 1;
    BOOLEAN TempDeviceFound = FALSE;
    EFI_LOAD_OPTION *BootOption;
    BBS_BBS_DEVICE_PATH *Bbsdp;

    Status = GetEfiVariable( L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize, (VOID**)&BootOrder);

    if ( !EFI_ERROR(Status) )
    {
        for ( Counter = 0; Counter < BootOrderSize / sizeof(UINT16); Counter++)
        {
            BootOption=GetUefiBootName( BootOrder[Counter] );

            if ( BootOption )
            {
                Bbsdp = (BBS_BBS_DEVICE_PATH*) ((UINT8*)(BootOption + 1)                         
                    + (Wcslen((CHAR16*)(BootOption + 1)) + 1) * sizeof(CHAR16));

                if ( Bbsdp->Header.Type == BBS_DEVICE_PATH )
                {
                    switch ( Bbsdp->DeviceType )
                    {
                        case TempUefiHddDevice:
                        case TempUefiOddDevice:
                        case TempUefiRemDevice:
                        case TempUefiNetDevice:
                            TempDeviceFound = TRUE;
                            break;
                    }
                }

                gBS->FreePool(BootOption);
            }

            if ( TempDeviceFound )
                break;
        }

        gBS->CopyMem(NewBootOrder, BootOrder, BootOrderSize);
        gBS->FreePool(BootOrder);
        
        //DEBUG((DEBUG_INFO,"CreateTempBootOption::TempDeviceFound(%d)\n", TempDeviceFound));
        ///already create temp device?
        if ( TempDeviceFound )
            return EFI_SUCCESS;
    }

    for ( MapIndex = 0; MapIndex < (sizeof(BootOptionTemp) / sizeof(TEMP_DEVICE_MAP)); MapIndex++)
    {
        /// Check temp boot option should be added to list.
        if (!gIsCorrectBootoptionPtr(BootOptionTemp[MapIndex].DeviceTypeId)) {
            /// Skip this temp boot option.
            continue;
        }

        for ( Counter = 0; Counter < (BootOrderSize / sizeof(UINT16)); Counter++)
        {
            if ( NewBootOrder[Counter] == BootIndex )
            {
                BootIndex++;
                Counter = -1;
                continue;
            }
        }

        NewBootOrder[Counter] = BootIndex;
        BootOrderSize += sizeof(UINT16);

        CreateBootOption( BootIndex, BootOptionTemp[MapIndex].DeviceTypeId, BootOptionTemp[MapIndex].TempName );
    }

    ///Update Variable "BootOrder".
    if ( BootOrderSize )
    {
        gRT->SetVariable(
                L"BootOrder",
                &gEfiGlobalVariableGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                BootOrderSize,
                &NewBootOrder[0]);
    }

    return Status;
}

/**
 * EXIT_BOOT_SERVICES notification callback function.
 *    
 * @param[in]   Event            The Event that is being processed.
 * @param[in]   Context          The Event Context.
 *
 */

VOID 
EFIAPI 
OnExitBootServices(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_STATUS Status;
    EFI_GUID   FastBootPolicyGuid = FAST_BOOT_POLICY_PROTOCOL2_GUID;
    FAST_BOOT_POLICY2    *gFastBootPolicy;
    EFI_GUID GuidBootFlow = BOOT_FLOW_VARIABLE_GUID;
    UINT32 BootFlow;
    UINTN Size;

    DEBUG((DEBUG_INFO,"FastBootOption OnExitBootServices event .............\n"));
    Status = gBS->LocateProtocol(&FastBootPolicyGuid, NULL, (VOID**)&gFastBootPolicy);

    DEBUG((DEBUG_INFO,"FastBootOption gFastBootPolicy->FastBootEnable = %d\n", gFastBootPolicy->FastBootEnable));
    if (EFI_ERROR(Status) || gFastBootPolicy->FastBootEnable == FALSE) {
        gBS->CloseEvent (Event);
        return;
    }
    Status = gRT->GetVariable(L"BootFlow", &GuidBootFlow, NULL, &Size, &BootFlow);
    DEBUG((DEBUG_INFO,"FastBootOption BootFlow = %d\n", BootFlow));

    if (!EFI_ERROR(Status) && (BootFlow == BOOT_FLOW_CONDITION_FAST_BOOT)) 
        CreateTempBootOption();
    
    gBS->CloseEvent (Event);
}

/**
 * This function is the entry point for FastBootOption Driver.
 *    
 * @param[in]   ImageHandle                The firmware allocated handle for the EFI image. 
 * @param[in]   SystemTable                A pointer to the EFI System Table.
 *
 * @retval      EFI_SUCCESS                The entry point is executed successfully.
 */

EFI_STATUS 
EFIAPI 
FastBootOptionEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable 
)
{
    EFI_STATUS Status = EFI_SUCCESS;

    InitAmiLib( ImageHandle, SystemTable );

    DEBUG((DEBUG_INFO,"FastBootOptionEntryPoint.............\n"));

    gBS->CreateEvent (
                EVT_SIGNAL_EXIT_BOOT_SERVICES,
                EFI_TPL_NOTIFY,
                OnExitBootServices,
                NULL,
                &gExitBootServicesEvent
            );

    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

