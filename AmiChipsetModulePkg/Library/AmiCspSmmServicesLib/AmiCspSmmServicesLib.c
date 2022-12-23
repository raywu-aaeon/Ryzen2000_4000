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

/** @file AmiCspSmmServicesLib.c
    South Bridge Csp Smm Services Library implementation

*/
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

//
// The following is for the backward compatible after EIP383015 and EIP428272.
// Due to S5SleepSmiOccurred->SbWindownsFirmwareUpdateCapsuleS5->SBLib_ResetSystem->AmdWarmReset->SBLib_S3InsteadOfWarmReset
//					->SBLib_S3InsteadOfWarmResetCallBack->AmiPspCapsuleCallback
EFI_SMM_SYSTEM_TABLE2	*pSmst;
EFI_RUNTIME_SERVICES 	*pRS;
//


EFI_STATUS
EFIAPI
AmiGetSmmConfigurationTable (
    IN  EFI_GUID              *TableGuid,
    OUT VOID                  **Table
)
{
    EFI_CONFIGURATION_TABLE   *CfgTable;
    UINTN                     Index;

    ASSERT (TableGuid != NULL);
    ASSERT (Table != NULL);
    ASSERT (gSmst != NULL);
    
    CfgTable = gSmst->SmmConfigurationTable;
    *Table = NULL;
    
    for (Index = 0; Index < gSmst->NumberOfTableEntries; Index++) {
      if (CompareGuid (TableGuid, &(CfgTable[Index].VendorGuid))) {
        *Table = CfgTable[Index].VendorTable;
        return EFI_SUCCESS;
      }
    }
    
    return EFI_NOT_FOUND;
}

EFI_STATUS CspInitSmmHandler(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_STATUS       (*InSmmFunction)(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
)
{
    EFI_STATUS          Status;
    VOID                *SmmRsTable;

    Status = AmiGetSmmConfigurationTable(&gAmiSmmRsTableGuid, (VOID**)&SmmRsTable);
    if ((!EFI_ERROR(Status)) && (SmmRsTable != NULL)) {
    	gRT = SmmRsTable;

		//
		// The following is for the backward compatible after EIP383015 and EIP428272.
		// Due to S5SleepSmiOccurred->SbWindownsFirmwareUpdateCapsuleS5->SBLib_ResetSystem->AmdWarmReset->SBLib_S3InsteadOfWarmReset
		//					->SBLib_S3InsteadOfWarmResetCallBack->AmiPspCapsuleCallback
		//	Still use pSmst.
      	//
    	pSmst = gSmst;
    	pRS = gRT;
    }

    return InSmmFunction(ImageHandle,SystemTable);
}

/**
    To construct gRT of RuntimeSmm for who use this library.

    @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiCspSmmServicesLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	EFI_STATUS          Status;
    VOID                *SmmRsTable;

    Status = AmiGetSmmConfigurationTable(&gAmiSmmRsTableGuid, (VOID**)&SmmRsTable);
    if ((!EFI_ERROR(Status)) && (SmmRsTable != NULL)) {
    	gRT = SmmRsTable;

		//
		// The following is for the backward compatible after EIP383015 and EIP428272.
		// Due to S5SleepSmiOccurred->SbWindownsFirmwareUpdateCapsuleS5->SBLib_ResetSystem->AmdWarmReset->SBLib_S3InsteadOfWarmReset
		//					->SBLib_S3InsteadOfWarmResetCallBack->AmiPspCapsuleCallback
		//	Still use pSmst.
      	//
    	pSmst = gSmst;
    	pRS = gRT;
    }
    return EFI_SUCCESS;
}

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
