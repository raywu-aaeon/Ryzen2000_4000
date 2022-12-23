//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
/** @file GetCpmSetupDataLib.c
    Custom CPU setup data behavior implementation

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>
#include <PiDxe.h>

#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>

// AMI Compatibility header
#include <CpmElinks.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID (CPM_OEM_SETUP_CALLBACK) (
    IN VOID                 	*Services,
    IN OUT AMD_PBS_SETUP_OPTION	*CpmSetupData,
    IN AMD_PBS_SETUP_OPTION    	*SetupData,
    IN BOOLEAN              	Pei
);

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// External Declaration(s)
extern CPM_OEM_SETUP_CALLBACK CPM_OEM_SETUP_CALLBACK_LIST EndOfList;

// Variable Declaration(s)
CPM_OEM_SETUP_CALLBACK* CpmOemSetupCallbackList[] = \
                                            {CPM_OEM_SETUP_CALLBACK_LIST NULL};

// GUID Definition(s)

// Protocol/Ppi Definition(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for OEM/custom setup.
    This function will be called in "GetAmdPbsConfiguration".

    @param *Services    - Pointer to PeiServices or RuntimeServices
        structure
        *SBSetupData - Pointer to custom setup data to return
        *SetupData   - Pointer to system setup data.
        Pei          - Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/

VOID CpmOemSetupCallbacks (
    IN VOID       				*Services,
    IN OUT AMD_PBS_SETUP_OPTION	*CpmSetupData,
    IN AMD_PBS_SETUP_OPTION    	*SetupData,
    IN BOOLEAN              	Pei )
{
    UINTN   i;

    for (i = 0; CpmOemSetupCallbackList[i] != NULL; i++)
        CpmOemSetupCallbackList[i]( Services, CpmSetupData, SetupData, Pei);
}

/**
	!!! DO NOT USE this function !!!!
	This is just old sample. AMD has provide "AmdPbsConfigLib" please use it
	to get SETUP item.

    @param Service pointer to PeiServices or RuntimeServices structure
    @param CpmSetupData pointer to custom setup data to return
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID

    @note  PORTING REQUIRED

**/

VOID GetCpmSetupData(
    IN  VOID            		*Services,
    OUT AMD_PBS_SETUP_OPTION	*CpmSetupData,
    IN  BOOLEAN         		Pei
)
{
/*
    if (EFI_ERROR(Status))
    {
        CpmOemSetupCallbacks(Services, CpmSetupData, NULL, Pei);
    }
    else
    {
        CpmOemSetupCallbacks(Services, CpmSetupData, &SetupData, Pei);
    }
    */
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************
