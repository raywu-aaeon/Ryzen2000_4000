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

/** @file GetSetupData.c
    Custom North Bridge setup data behavior implementation

**/


#include <Setup.h>
#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/NbPolicy.h>
#include <NbElinks.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
extern NB_OEM_SETUP_CALLBACK NB_OEM_SETUP_CALLBACK_LIST EndOfList;
NB_OEM_SETUP_CALLBACK* NbOemSetupCallbackList[] = { NB_OEM_SETUP_CALLBACK_LIST NULL };

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

// GUID Definition(s)

static EFI_GUID gSetupGuid = SETUP_GUID;

// Protocol/Ppi Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for OEM/custom setup.

    @param *Services    - Pointer to PeiServices or RuntimeServices
        structure  
        *NbSetupData - Pointer to custom setup data to return
        *SetupData   - Pointer to system setup data.
        Pei          - Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/

VOID NbOemSetupCallbacks (
    IN VOID                 *Services,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
  )
{
  UINTN                     i;

  for (i = 0; NbOemSetupCallbackList[i] != NULL; i++)
    NbOemSetupCallbackList[i]( Services, NbSetupData, SetupData, Pei);
}

/**
    This function returns custom setup data from system SetupData
    variable 

    @param *Services    - Pointer to PeiServices or RuntimeServices
        structure  
        *NbSetupData - Pointer to custom setup data to return
        Pei          - Pei flag. If TRUE we are in PEI phase

    @retval VOID

    @note  PORTING REQUIRED
**/
VOID GetNbSetupData (
    IN VOID                 *Services,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN BOOLEAN              Pei
)
{
    EFI_STATUS                      Status;
    SETUP_DATA                      SetupData;
    EFI_PEI_SERVICES                **PeiServices;
    EFI_RUNTIME_SERVICES            *RunServices;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
    UINTN                           VariableSize = sizeof(SETUP_DATA);


    if (Pei) {
        PeiServices = (EFI_PEI_SERVICES **)Services;
        Status = (*PeiServices)->LocatePpi( PeiServices, \
                                            &gEfiPeiReadOnlyVariable2PpiGuid, \
                                            0, \
                                            NULL, \
                                            &ReadOnlyVariable );

        if (!EFI_ERROR(Status)) {
            Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                    L"Setup", \
                                                    &gSetupGuid, \
                                                    NULL, \
                                                    &VariableSize, \
                                                    &SetupData );
        }
    } else {
        RunServices = (EFI_RUNTIME_SERVICES *)Services;
        Status = RunServices->GetVariable( L"Setup", \
                                           &gSetupGuid, \
                                           NULL, \
                                           &VariableSize, \
                                           &SetupData );
    }

    NbSetupData->NbPolicyVersion = 0x012; // This value must be updated if 
                                          // the structure of NB_SETUP_DATA 
                                          // is changed.
                                          // Porting required.

    if (EFI_ERROR(Status)) {
        // Porting Start
        // Update NB_SETUP_DATA according to the default values.

    	NbSetupData->EnableBankIntlv = 0; // [Fam15 only]
        NbSetupData->EnableChannelIntlv = 0; // [Fam15 only]
    	NbSetupData->MemClk = 0; // [Fam15 only]
    	NbSetupData->MemClrFlag = 0; // [Fam15 only]
    	NbSetupData->MemClr = 0; // [Fam15 only]
        // Porting End
        NbOemSetupCallbacks( Services, NbSetupData, NULL, Pei );
    } else {
        // Porting Start
        // Update NB_SETUP_DATA according to the setup datas.

    	NbSetupData->EnableBankIntlv = SetupData.EnableBankIntlv; // [Fam15 only]
        NbSetupData->EnableChannelIntlv = SetupData.EnableChannelIntlv; // [Fam15 only]
    	NbSetupData->MemClk = SetupData.MemClk; // [Fam15 only]
    	NbSetupData->MemClrFlag = SetupData.MemClrFlag; // [Fam15 only]
    	NbSetupData->MemClr = SetupData.MemClr; // [Fam15 only]

        // Porting End
        NbOemSetupCallbacks( Services, NbSetupData, &SetupData, Pei );
    }
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
