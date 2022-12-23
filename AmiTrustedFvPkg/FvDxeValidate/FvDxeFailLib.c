//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file 
    NULL library instance
**/
#include <Token.h> 
#include <AmiPeiLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>

#include <AmiHobs.h>
#include <Library/HobLib.h>
#include <Library/PostCodeLib.h>

#include <Ppi/AmiFvDxeValidate.h>

#include <Library/DebugLib.h>

//-------------------------------------------------------------------------
static EFI_PEI_PPI_DESCRIPTOR RecoveryModePpi = {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiBootInRecoveryModePpiGuid, NULL
};
//-------------------------------------------------------------------------
/**
 * Function that will force the system into recovery mode
 *
 * @param PeiServices Pointer to the Pointer to the Pei Services Table
 */
VOID ExecuteActionOnFailureToValidateFv(IN CONST EFI_PEI_SERVICES **PeiServices)
{
    EFI_BOOT_MODE BootMode;
    EFI_STATUS Status;
    RECOVERY_IMAGE_HOB *RecoveryHob = NULL;
    EFI_HOB_GENERIC_HEADER *Hobs = NULL;
    UINT32  ErrorCode;

    ErrorCode = FVDXE_VERIFY_FAILED_POSTCODE;

    (*PeiServices)->ReportStatusCode (
              PeiServices,
              EFI_ERROR_CODE, // Type
              ErrorCode,      // Value
              0,
              NULL,
              NULL
    );
    PostCode (ErrorCode);
    DEBUG ((DEBUG_ERROR, "[FvDxeFailLibNull.c] FvDxe Fail to Validate Policy=%d.\n", PcdGet32(AmiPcdTdxeFailedRecoveryPolicy)));

    // AmiPcdTdxeFailedRecoveryPolicy
    // 0 - Invoke BIOS recovery process
    // 1 - Hang in CPU dead loop
    if (PcdGet32(AmiPcdTdxeFailedRecoveryPolicy) == 0) {
        Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
        ASSERT_EFI_ERROR(Status);
        DEBUG ((DEBUG_ERROR, "==>FvDxe Recovery, Get BootMode %r %X\n", Status, BootMode));
        if(EFI_ERROR(Status)) 
            CpuDeadLoop ();

        if(BootMode != BOOT_IN_RECOVERY_MODE) {
            // block system boot on failed recovery image
            if(!PcdGetBool (AmiPcdForceShutdownOnFailedRecovery)){
                PcdSetBoolS(AmiPcdForceShutdownOnFailedRecovery,TRUE);
            }
            (*PeiServices)->SetBootMode(PeiServices, BOOT_IN_RECOVERY_MODE);
            (*PeiServices)->InstallPpi(PeiServices, &RecoveryModePpi);
            PEI_PROGRESS_CODE(PeiServices, PEI_RECOVERY_AUTO);
//            return;
//        } else {
//            // check if Recovery is already being processed
//            Status = (*PeiServices)->GetHobList(PeiServices, (VOID**)&Hobs);
//            if(!EFI_ERROR(Status)) {
//                RecoveryHob = GetNextGuidHob(&gAmiRecoveryImageHobGuid, (VOID*)Hobs);
//                if(RecoveryHob != NULL)
//                {
//                    if(RecoveryHob->Status == EFI_SUCCESS && RecoveryHob->Address != 0)
//                    {
//                        return;
//                    }
//                }
//            }
        }
        return;
    }
    CpuDeadLoop ();
}

