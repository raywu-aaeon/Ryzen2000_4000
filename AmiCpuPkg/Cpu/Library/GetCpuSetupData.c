//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file GetCpuSetupData.c
    Custom CPU setup data behavior implementation

**/

#include <PiPei.h>
#include <Setup.h>
#include <Ppi/ReadOnlyVariable2.h>
#include "CpuSetupData.h"
#include <CpuElinks.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID (CPU_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT CPU_SETUP_DATA   *CpuSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// External Declaration(s)
extern CPU_OEM_SETUP_CALLBACK CPU_OEM_SETUP_CALLBACK_LIST EndOfCpuList;

// Variable Declaration(s)

// GUID Definition(s)
static EFI_GUID gSetupGuid = SETUP_GUID;

// Protocol/Ppi Definition(s)

// Function Definition(s)
CPU_OEM_SETUP_CALLBACK *CpuOemSetupCallbackList[] = {CPU_OEM_SETUP_CALLBACK_LIST NULL};

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for OEM/custom setup.

    @param Services Pointer to PeiServices or RuntimeServices
        structure  
    @param SBSetupData Pointer to custom setup data to return
    @param SetupData Pointer to system setup data.
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/

VOID
CpuOemSetupCallbacks (
  IN        VOID            *Services,
  IN OUT    CPU_SETUP_DATA  *CpuSetupData,
  IN        SETUP_DATA      *SetupData,
  IN        BOOLEAN         Pei
)
{
    UINTN   i;

    for (i = 0; CpuOemSetupCallbackList[i] != NULL; i++)
        CpuOemSetupCallbackList[i]( Services, CpuSetupData, SetupData, Pei);   
}

/**
    This function returns custom setup data from system SetupData variable

    @param Service pointer to PeiServices or RuntimeServices structure
    @param CpuSetupData pointer to custom setup data to return
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID

    @note  PORTING REQUIRED

**/

VOID
GetCpuSetupData(
  IN    VOID            *Services, 
  OUT   CPU_SETUP_DATA  *CpuSetupData, 
  IN    BOOLEAN         Pei
)
{
    EFI_STATUS                      Status;
    SETUP_DATA                      SetupData;
    EFI_PEI_SERVICES                **PeiServices;
    EFI_RUNTIME_SERVICES            *pRS;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
    UINTN                           VariableSize;

    if(Pei)
    {
        PeiServices = (EFI_PEI_SERVICES **)Services;
	    Status = (*PeiServices)->LocatePpi(PeiServices, 
                                           &gEfiPeiReadOnlyVariable2PpiGuid,
					                       0, NULL, &ReadOnlyVariable); 
        if(!EFI_ERROR(Status))
        {
            VariableSize = sizeof (SETUP_DATA);
            Status = ReadOnlyVariable->GetVariable (ReadOnlyVariable,
                                        L"Setup", &gSetupGuid, NULL, 
                                        &VariableSize, &SetupData);
        }
    }
    else
    {
        pRS = (EFI_RUNTIME_SERVICES *)Services;

        VariableSize = sizeof(SETUP_DATA);
        Status = pRS->GetVariable(L"Setup", &gSetupGuid, NULL, &VariableSize, 
                                  &SetupData);
    }

    if(EFI_ERROR(Status))
    {
        //Default Value setting 
        // L"Setup"
        CpuSetupData->PNOW_ASL_MODE = 1;
        CpuSetupData->PSTATE_CTRL = 0; // [Fam15 only]
        CpuSetupData->PPC_CTRL = 0;
        CpuSetupData->SVM_MODE = 1;
        CpuSetupData->NX_MODE = 1;

        CpuSetupData->C6Mode = 1; // [Fam15 only]
        CpuSetupData->CpbMode = 0; // [Fam15 only]

        CpuOemSetupCallbacks(Services, CpuSetupData, NULL, Pei);
    }
    else
    {
        // L"Setup"
        CpuSetupData->PNOW_ASL_MODE = SetupData.PNOW_ASL_MODE;
        CpuSetupData->PSTATE_CTRL = SetupData.PSTATE_CTRL; // [Fam15 only]
        CpuSetupData->PPC_LIMIT = SetupData.PPC_LIMIT;
        CpuSetupData->PPC_CTRL = SetupData.PPC_CTRL;
        CpuSetupData->SVM_MODE = SetupData.SVM_MODE;
        CpuSetupData->NX_MODE = SetupData.NX_MODE;

        CpuSetupData->C6Mode = SetupData.C6Mode; // [Fam15 only]
        CpuSetupData->CpbMode = SetupData.CpbMode; // [Fam15 only]

        CpuOemSetupCallbacks(Services, CpuSetupData, &SetupData, Pei);
    }
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************
