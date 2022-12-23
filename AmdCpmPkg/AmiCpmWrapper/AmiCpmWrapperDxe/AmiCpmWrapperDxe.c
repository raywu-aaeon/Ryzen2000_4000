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
/** @file AmiCpmWrapperDxe.c
    This file contains code for AmiCpmWrapperDxe.c
    in the DXE stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#ifdef _AUTOGENH_D60CF145_F97C_4085_A73D_8D399757DFE9
// The condition is the definition of AutoGen. This is for internal use to separate AM4/FP5 in one C source.
#define __AMI_CPM_WRAPPER_FP5
#endif

#ifdef _AUTOGENH_D60CF145_F97C_4085_A73D_8D399757DFEA
// The condition is the definition of AutoGen. This is for internal use to separate AM4/FP5 in one C source.
#define __AMI_CPM_WRAPPER_AM4
#endif

// UDK Header
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/S3PciLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#ifdef __AMI_CPM_WRAPPER_AM4
#include <AmiDxeLib.h>
#include <Setup.h>
#endif

#include <AmdCpmDxe.h>
#include CPM_PROTOCOL_DEFINITION (AmdCpmDisplayFeatureProtocol)

#include <Token.h>
// AMI Compatibility Header.
//--#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
//--#include <AmiCspLib.h> // Optional. should use Mde Library instead.
//--#include <Setup.h> // Optional. should use Mde Library instead.

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**

    @param Event The event
    @param Context The context

    @retval VOID

    @note  .
**/
VOID
EFIAPI
CpmTblCallBack (
  IN EFI_EVENT          Event,
  IN VOID               *Context
  )
{
	EFI_STATUS							Status = EFI_SUCCESS;
	AMD_CPM_TABLE_PROTOCOL				*AmdCpmTableProtocolPtr = NULL;
	AMD_CPM_DISPLAY_FEATURE_TABLE		*CpmDisplayFeatureTbl = NULL;

	Status = gBS->LocateProtocol(&gAmdCpmTableProtocolGuid, NULL, &AmdCpmTableProtocolPtr);
	if (!EFI_ERROR(Status)) {
		CpmDisplayFeatureTbl = AmdCpmTableProtocolPtr->CommonFunction.GetTablePtr (AmdCpmTableProtocolPtr, CPM_SIGNATURE_DISPLAY_FEATURE);

	// set the BIT0 otherwise SSID can't be update outside CPM
#if defined(IGNORE_CPM_IGD_SSID_PROGRAM) && (IGNORE_CPM_IGD_SSID_PROGRAM != 0)
	CpmDisplayFeatureTbl->FunctionDisableMask |= BIT0;
#else
#if defined(OEM_IGPU_SSID) && (OEM_IGPU_SSID != 0)
	CpmDisplayFeatureTbl->FunctionDisableMask |= BIT0;
#endif
#endif

	// Sync Aptio4 gCpmDisplayFeatureTable
	#if defined(AmdCpmDisplayFeatureMxmOverTAsl_SUPPORT) && (AmdCpmDisplayFeatureMxmOverTAsl_SUPPORT == 0)
		CpmDisplayFeatureTbl->MxmOverTempEvent = 0xFF;
		CpmDisplayFeatureTbl->MxmOverTempStateId = 0xFF;
	#endif

		gBS->CloseEvent(Event);
	}

}

/**
    This function is the entry point for AmiCpmWrapperDxe driver.
    This function initializes the AmiCpmWrapperDxe in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  .
**/

EFI_STATUS
EFIAPI
AmiCpmWrapperDxeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_EVENT               Event = NULL;
    VOID                    *Registration;
    
    Event = EfiCreateProtocolNotifyEvent (
             &gAmdCpmTableProtocolGuid,
             TPL_CALLBACK,
             CpmTblCallBack,
             NULL,
             &Registration
             );
    ASSERT (Event != NULL);

    
    return Status;
}

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
