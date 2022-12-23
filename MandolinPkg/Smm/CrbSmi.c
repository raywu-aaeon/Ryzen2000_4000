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

/** @file CrbSmi.c
    This file contains code for all CRB SMI events

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>

#include <Token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.

// Produced Protocols

// Consumed Protocols
#include <Protocol/SmmBase2.h>
#include <Protocol/S3SmmSaveState.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/SmmStandbyButtonDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

#define CRB_GPI_SMI_TEST            0 // switch to turn on GPI smi test.
#if CRB_GPI_SMI_TEST
	//
	// from PI1.2 VOLUME 4:
	// 	6.6 SMM General Purpose Input (GPI) Dispatch Protocol
	//  we should use bits mask as GpiNum.
	//
	// this macro is for compatible some Aptio-4 component to use index base.
	//
    #if GPI_DISPATCH_BY_BITMAP == 1
        #define MACRO_CONVER_TO_GPI(x)     BIT##x
    #else
        #define MACRO_CONVER_TO_GPI(x)     x
    #endif
#else
    #define MACRO_CONVER_TO_GPI(x)     x
#endif

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
    This is a template CRB SMI GetContext for Porting.

    @param VOID

    @retval BOOLEAN FALSE

    @note  Here is the control flow of this function:
              1. Check if CRB Smi source.
              2. If yes, return TRUE.
              3. If not, return FALSE.
**/

BOOLEAN
GetCrbSmiContext (
  VOID
  )
{
    // Porting if needed
    return FALSE;
}

/**
    This is a template CRB SMI Handler for Porting.

    @param VOID

    @retval VOID
**/

VOID
CrbSmiHandler (
  VOID
  )
{
    // Porting if needed
}

/**
    This is a template CRB software SMI Handler for Porting.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval VOID
**/

EFI_STATUS
CrbSwSmiHandler (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID  	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;

	// Porting if needed
    if (CommBuffer != NULL) {
        if (((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort == CRB_SWSMI) {
            DEBUG ((DEBUG_INFO|DEBUG_PLATFORM,"<< CrbSwSmiHandler for CRB testing>>\n"));
            IoWrite16(0x80,0xB2BF);
        	// do something if needed.
        }
    }

//    {
//		//
//		// following items is Aptio-4 compatible.
//		// We should use Mde library instead.
//		//   only one reason to use this library is for get EFI_RUNTIME_SERVICES which located in SMM.
//		//
//    	EFI_TIME                    Time;
//   	DEBUG ((DEBUG_INFO|DEBUG_PLATFORM,"<< CrbSwSmiHandler 001 %x >>\n",pRS->GetTime));
//    	pRS->GetTime(&Time, NULL);
//    	DEBUG ((DEBUG_INFO|DEBUG_PLATFORM,"<< CrbSwSmiHandler Year(%x) Month(%x) Day(%x) Hour(%x) >>\n"
//    		,Time.Year
//			,Time.Month
//			,Time.Day
//			,Time.Hour
//    		));
//    	pRS->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
//    }

    return Status;
}

/**
    This is a template CRB Sx SMI Handler for Porting.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval VOID
**/

EFI_STATUS
CrbSxSmiHandler (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID  	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;
	EFI_SMM_SX_REGISTER_CONTEXT  	*DispatchContext = (EFI_SMM_SX_REGISTER_CONTEXT*)Context;

    if (DispatchContext->Type == SxS4) {
	//### Remove SxS3 due to S3 WOL fail ### || DispatchContext->Type == SxS3) {
    // Workaround to avoid post time too long if user do following step.
    //		OS-> Shutdown-> BIOS Setup-> Reset button-> OS-> post time validation.
    }
	return Status;
}

/**
    This is a template CRB Gpi SMI Handler for Porting.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval VOID
**/

EFI_STATUS
CrbGpiSmiHandler (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID  	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;
	EFI_SMM_GPI_REGISTER_CONTEXT  	*DispatchContext = (EFI_SMM_GPI_REGISTER_CONTEXT*)Context;

    // Porting if needed

    // For GPI 5 for PCIE express card
    if (DispatchContext->GpiNum == MACRO_CONVER_TO_GPI(5)) {

    }

    if (DispatchContext->GpiNum == MACRO_CONVER_TO_GPI(23)) {

    }

    return Status;
}

/**
    This is an entry for CRB SMM Child Dispatcher Handler.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval EFI_STATUS EFI_SUCCESS

    @note  Here is the control flow of this function:
              1. Read SMI source status registers.
              2. If source, call handler.
              3. Repeat #2 for all sources registered.
**/

EFI_STATUS
CrbChildDispatcher (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID 	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;

    if (GetCrbSmiContext()) CrbSmiHandler();

    return Status;
}

/**
    This function is Aptio-4 compatible. not required no more.
    We should use Mde library instead.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

**/

EFI_STATUS
EFIAPI
CrbDummyFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
	EFI_STATUS           	Status = EFI_SUCCESS;
    return Status;
}

/**
    Installs CRB SMM Child Dispatcher Handler.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_NOT_FOUND The SMM Base protocol is not found.
    @retval EFI_SUCCESS Installs CRB SMM Child Dispatcher Handler successfully.
**/

EFI_STATUS
EFIAPI
CrbSmiInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                		Status;
	EFI_SMM_SW_DISPATCH2_PROTOCOL  	*SwDispatch = NULL;
	EFI_SMM_SX_DISPATCH2_PROTOCOL  	*SxDispatch = NULL;
#if CRB_GPI_SMI_TEST
	EFI_SMM_GPI_DISPATCH2_PROTOCOL 	*GpiDispatch = NULL;
#endif
	EFI_SMM_SW_REGISTER_CONTEXT     SwContext = {CRB_SWSMI};
    EFI_SMM_SX_REGISTER_CONTEXT     SxContext = {SxS3, SxEntry};
#if CRB_GPI_SMI_TEST
    EFI_SMM_GPI_REGISTER_CONTEXT    GpiContext = {MACRO_CONVER_TO_GPI(5)}; // _L05 default for PCIExpress card
#endif
    EFI_HANDLE                      Handle = NULL;

    Status  = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, &SwDispatch);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status  = SwDispatch->Register( SwDispatch, \
                                         CrbSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);
    }

    Status  = gSmst->SmmLocateProtocol (&gEfiSmmSxDispatch2ProtocolGuid, NULL, &SxDispatch);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status  = SxDispatch->Register( SxDispatch, \
                                         CrbSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);
        SxContext.Type =  SxS4;
        Status  = SxDispatch->Register( SxDispatch, \
                                         CrbSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);
    }

#if CRB_GPI_SMI_TEST
    Status  = gSmst->SmmLocateProtocol (&gEfiSmmGpiDispatch2ProtocolGuid, NULL, &GpiDispatch);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status  = GpiDispatch->Register( GpiDispatch, \
                                         CrbGpiSmiHandler, \
                                         &GpiContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);

        GpiContext.GpiNum = MACRO_CONVER_TO_GPI(23);
        Status  = GpiDispatch->Register( GpiDispatch, \
                                         CrbGpiSmiHandler, \
                                         &GpiContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);
    }
#endif

    Handle = NULL;
    //Register call backs
    Status = gSmst->SmiHandlerRegister(CrbChildDispatcher, NULL, &Handle);


    //
    // following items is Aptio-4 compatible.
    // We should use Mde library instead.
    //   only one reason to use this library is for get EFI_RUNTIME_SERVICES which located in SMM.
    //
    InitAmiLib(ImageHandle, SystemTable);
    Status = InitSmmHandler(ImageHandle, SystemTable, CrbDummyFunction, NULL);

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
