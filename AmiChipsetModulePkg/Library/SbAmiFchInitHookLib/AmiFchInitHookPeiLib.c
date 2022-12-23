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

/** @file AmiFchInitHookPeiLib.c
    This file contains code for AmiFchInitHookPeiLib initialization in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>

#include <Token.h>
#include <SbElinks.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef
EFI_STATUS
(SB_UPDATE_FCH_PCDS_FUNC)(
  IN  BOOLEAN	IsPei
  );

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

extern SB_UPDATE_FCH_PCDS_FUNC SB_FCH_PCD_INIT_LIST EndOfList;
SB_UPDATE_FCH_PCDS_FUNC* FchPcdUpdateList[] = { SB_FCH_PCD_INIT_LIST NULL };

// Function Definition(s)

//---------------------------------------------------------------------------

EFI_STATUS
EFIAPI
AmiFchInitHookConstructor (
  IN       EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINTN			i;

	for (i = 0; FchPcdUpdateList[i] != NULL; i++) {
		Status = FchPcdUpdateList[i](TRUE);
	}

	return Status;
}


#if (defined(AmdCpmPkg_FchInitHookPeiLib_SUPPORT) && (AmdCpmPkg_FchInitHookPeiLib_SUPPORT == 0)) || !defined(AmdCpmPkg_FchInitHookPeiLib_SUPPORT)

/**
    This function is the FCH Hook for FchPlatformPTPeiInit.

    @param FchPTData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
FchPlatformPTPeiInit (
  IN      VOID                          *FchPTData
  )
{
	return EFI_SUCCESS;
}

/**
    This function is the FCH Hook for FchPlatformOemPeiInit.

    @param FchData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
FchPlatformOemPeiInit (
  IN      VOID                          *FchData
  )
{
	return EFI_SUCCESS;
}

#endif

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
