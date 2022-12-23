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
/*++
Module Name:

  AmiPspFtpmPei.c

--*/

#include <PiPei.h>
#include <Ppi/AmdPspFtpmPpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/AmdPspFtpmLib.h>
#include <Guid/AmiPsp.h>
#include <AmiPspFtpm.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Setup.h>

EFI_STATUS EFIAPI AmiPspFtpmHobInstalled (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi 
);

static EFI_PEI_NOTIFY_DESCRIPTOR AmiPspFtpmNotifyList[] = 
{
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmdPspFtpmFactoryResetPpiGuid, AmiPspFtpmHobInstalled },
};

/**
    This function is called after the AMD Psp Ftpm factory reset is installed
    in the system.  It will create a HOB for notifying DXE about clearing the PSP NVRAM
    when CPU swap.

    @param FileHandle Handle of the file being invoked
    @param PeiServices Pointer to the PEI services table

    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI
AmiPspFtpmHobInstalled(
  IN    EFI_PEI_SERVICES             **PeiServices,
  IN    EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN    VOID                         *InvokePpi 
)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    AMI_PSP_FTPM_HOB        *AmiPspFtpmHob;

    DEBUG((DEBUG_INFO, "AmiPspFtpmHobInstalled Entry\n"));

    // Create hob for notifying DXE about clearing PSP NVRAM
    Status = (**PeiServices).CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof (AMI_PSP_FTPM_HOB),
                                       &AmiPspFtpmHob);
    DEBUG((DEBUG_INFO, "AmiPspFtpmHobInstalled Create Hob Status = %r\n", Status));
    if (Status == EFI_SUCCESS)
    {
        AmiPspFtpmHob->EfiHobGuidType.Name = gAmiPspFtpmHobGuid;
        AmiPspFtpmHob->ClearPspNvram = PSP_FTPM_FLAG_CLEAR;
    }

    // Disable Ftpm since CPU is swapped
    PcdSet8(PcdAmdPspSystemTpmConfig, 0);

    DEBUG((DEBUG_INFO, "AmiPspFtpmHobInstalled Exit\n"));

    return  Status;
}

/**
    AMI PSP Ftpm Driver Entry. Create a notify ppi list on gAmdPspFtpmFactoryResetPpiGuid.

    @param FileHandle Handle of the file being invoked
    @param PeiServices Pointer to the PEI services table

    @retval EFI_SUCCESS always success

**/
EFI_STATUS
AmiPspFtpmPeiDriverEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS                          Status = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    UINTN                               VariableSize = sizeof(SETUP_DATA);
    SETUP_DATA                          SetupData;
    EFI_GUID                            SetupGuid = SETUP_GUID;

    DEBUG((DEBUG_INFO, "AmiPspFtpmPeiDriverEntry Entry\n"));

    Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid,
                              0, NULL, &ReadOnlyVariable);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable,
                                L"Setup",
                                &SetupGuid,
                                NULL,
                                &VariableSize,
                                &SetupData);
    if (EFI_ERROR(Status)) return Status;

    if (SetupData.EraseFtpmNv == 1)
    {
        Status = (*PeiServices)->NotifyPpi(PeiServices, AmiPspFtpmNotifyList);
    }


    DEBUG((DEBUG_INFO, "AmiPspFtpmPeiDriverEntry Exit\n"));

    return Status;
}

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
