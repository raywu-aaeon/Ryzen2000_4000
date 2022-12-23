//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file CrbPxeLoader.c
    This file contains code for CRB PXE function.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Protocol/LegacyBiosExt.h>
#include <Protocol/PciIo.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Token.h>
#include <Setup.h>
#include <Sb.h>
#if defined(AmiNetworkPkg_SUPPORT)&&(AmiNetworkPkg_SUPPORT==1)
#include <Guid/NetworkStackSetup.h>
#endif

// Produced Protocols

// Consumed Protocols

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
VOID		static *Registration = NULL;
SETUP_DATA	static *gSetupData = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// GUID Definition(s)

// External Declaration(s)
extern EFI_GUID gCrbPxeDriverLoaderGuid;

// Function Definition(s)

//---------------------------------------------------------------------------

#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
/**
    This callback function is called before/after processing all
    PCI optonal ROM.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID CrbPxeCheckOprom (
    IN EFI_EVENT   Event,
    IN VOID        *Context )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    CSM_PLATFORM_POLICY_DATA    *Data = NULL;
    //UINTN                       Seg;
    //UINTN                       Bus;
    //UINTN                       Dev;
    //UINTN                       Fun;
    UINT8                       ConfigSpaceHeader[0x40];
    UINT16			DID;
    UINT16			VID;
    UINTN                       BufferSize = sizeof(EFI_HANDLE);
    EFI_HANDLE                  Handle;

    Status = gBS->LocateHandle( ByRegisterNotify, \
                                NULL, \
                                Registration, \
                                &BufferSize, \
                                &Handle );
    if (EFI_ERROR(Status)) return;

    // Locate CSM Platform Policy data
    Status = gBS->HandleProtocol( Handle, &gOpromStartEndProtocolGuid, &Data );

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    if (Data == NULL) return;
    if (Data->PciIo == NULL) return;

    //Status = Data->PciIo->GetLocation( Data->PciIo, &Seg, &Bus, &Dev, &Fun );
    //ASSERT_EFI_ERROR(Status);
    Status = Data->PciIo->Pci.Read( Data->PciIo, EfiPciIoWidthUint8, 0x0, 0x40, ConfigSpaceHeader);
    ASSERT_EFI_ERROR(Status);

    if (!EFI_ERROR(Status)) {
    	// The CSM will skip the legacy PXE if class code doesn't match.
    	// Check DID and VID for PXE function.
    	// So this is a easy solution.
	    VID=ConfigSpaceHeader[1]*0x100+ConfigSpaceHeader[0];
	    DID=ConfigSpaceHeader[3]*0x100+ConfigSpaceHeader[2];
	
    	if ( VID == CRB_PXE_VID && DID == CRB_PXE_DID ) {
			SETUP_DATA                  *SetupData = Context;

			if (SetupData != NULL) {
				if (SetupData->PxeOpRom == 2 && SetupData->OnBoardPXENIC) Data->ExecuteThisRom = TRUE;

				//    Do not dispatch Legacy-PXE when select "Legacy" in the "Other PCI devices" setup option.
				if (SetupData->OldOpRom == 0 && SetupData->PxeOpRom != 2 || SetupData->OnBoardPXENIC ==0 ) Data->ExecuteThisRom = FALSE;
			}
    	}

    }
}
#endif

/**
    This function is the entry point for CRB DXE driver.
    This function initializes the CRB in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

    @note  This routine is called very early, to register event on CSM.
**/

EFI_STATUS
EFIAPI
CrbPxeLoaderInit (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    NETWORK_STACK			*mNetworkStackData = NULL;
    UINTN                   Size = 0;
#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
	EFI_GUID                gSetupGuid = SETUP_GUID;

	Status = GetVariable2(L"Setup", &gSetupGuid, &gSetupData, &Size);
	ASSERT_EFI_ERROR(Status);
	if (!EFI_ERROR(Status)) {
        EFI_EVENT				Event;
	    // unreadVariable warning happened under MARCO "ASSERT"(\MdePkg\Include\Library\DebugLib.h)
	    // cppcheck-suppress unreadVariable
	    Event = EfiCreateProtocolNotifyEvent (
					&gOpromStartEndProtocolGuid,
					TPL_NOTIFY,
					CrbPxeCheckOprom,
					gSetupData,
					&Registration
					);
		ASSERT (Event != NULL);
	}
#endif

	Size = 0;
	Status = GetVariable2(L"NetworkStackVar", &gEfiNetworkStackSetupGuid, &mNetworkStackData, &Size);
    if (!EFI_ERROR(Status)) {
        if (mNetworkStackData != NULL && mNetworkStackData->Enable == 1
            #if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
            && (gSetupData->PxeOpRom == 1 || gSetupData->CsmSupport == 0)
            #endif
            ) {
            Status = gBS->InstallMultipleProtocolInterfaces(
                         &ImageHandle,
                         &gCrbPxeDriverLoaderGuid,
                         NULL,
                         NULL
                        );
        }
    }
    
    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
