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

//*************************************************************************
/** @file SmmChildDispatchProtocol.c
    This file contains code for SmmChildDispatchProtocol.c.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>

#include <Token.h>
// AMI Compatibility Header.
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include "SmmChildDispatch.h"
#include "SmmChildDispatchProtocol.h"


// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
#define SMI_HANDLER_SIGNATURE 0x48494d53    //SMIH

// Macro Definition(s)

// Type Definition(s)

///
/// Soft SMI Node
///
typedef struct _FCH_SMM_SW_NODE {
  EFI_HANDLE                         DispatchHandle;         ///< Dispatch Hangle
  FCH_SMM_SW_REGISTER_CONTEXT        Context;                ///< Register context
  FCH_SMM_SW_HANDLER_ENTRY_POINT2    CallBack2Function;      ///< SMM handler entry point 2
  struct _FCH_SMM_SW_NODE            *FchSwNodePtr;          ///< pointer to next node
} FCH_SMM_SW_NODE;


// Function Prototype(s)
UINTN GetEAX(UINTN);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

EFI_SMM_SW_REGISTER2    		static gOriginalRegister;
EFI_SMM_SW_UNREGISTER2  		static gOriginalUnRegister;
EFI_SMM_HANDLER_ENTRY_POINT2 	static gOriginalHandler;

DLIST                   static gTheSwSmiList;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    Hook EXTENDED_SMI for support DWORD SW SMI in AMD reference code base.

    @param DispatchHandle EFI Handle
    @param Context OPTIONAL - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param CommBuffer OPTIONAL
    @param CommBufferSize OPTIONAL

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
AmdFchSmmDwordSwSmi (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
  )
{
	EFI_STATUS					Status = EFI_SUCCESS;
	EFI_SMM_SW_REGISTER_CONTEXT	*DispatchContext = (EFI_SMM_SW_REGISTER_CONTEXT*)Context;
	UINTN       				Cpu = (UINTN)-1;

    if (CommBuffer != NULL && CommBufferSize != NULL) {
        Cpu = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->SwSmiCpuIndex;
    }

    if (DispatchContext->SwSmiInputValue == GetEAX(Cpu)) {
        FCH_SMM_SW_NODE     			*TheDwordSwSmiHandle = DispatchHandle;
        EFI_SMM_HANDLER_ENTRY_POINT2 	CallBack2Function = TheDwordSwSmiHandle->CallBack2Function;
        // Call user DWORD SW-SMI.
        Status = CallBack2Function (
                        TheDwordSwSmiHandle->DispatchHandle,
                        Context,
                        CommBuffer,
                        CommBufferSize
                        );
    }
    return Status;
}

/**
    EFI_SMM_SW_DISPATCH2_PROTOCOL Register function.

    @param This Pointer to EFI_SMM_SW_DISPATCH2_PROTOCOL
    @param DispatchFunction Pointer to callback function
    @param RegisterContext Pointer to callback context
    @param DispatchHandle Pointer to store registered handle

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
DwordSwSmiRegister2 (
  IN  CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  OUT   EFI_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  )
{
	EFI_STATUS 						Status = EFI_SUCCESS;
	FCH_SMM_SW_NODE 				*OriginalHandle, *TheDwordSwSmiHandle;

	//
	// User DWORD-SW-SMI
	// 1. record user DWORD-SW-SMI in new handle.
	// 2. register our callback and hook it.
	// 3. steal DispatchHandle from AMD handle. replace it with ours.
	// 4. when DWORD-SW-SMI come in. we translate it to user callback.
	// 5. restore back AMD DispatchHandle while unregister.
	//

	Status = gOriginalRegister(This, AmdFchSmmDwordSwSmi, RegisterContext, DispatchHandle);

	// Replace original DispatchHandle as our DWORD-SW-SMI handle
	OriginalHandle = (FCH_SMM_SW_NODE*)*DispatchHandle;
	Status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, sizeof (FCH_SMM_SW_NODE), &OriginalHandle->DispatchHandle);
	ASSERT_EFI_ERROR(Status);
	TheDwordSwSmiHandle = OriginalHandle->DispatchHandle;
	TheDwordSwSmiHandle->CallBack2Function = (FCH_SMM_SW_HANDLER_ENTRY_POINT2)DispatchFunction;
	// save original handle that AMD create, Let we have chance to use it when unRetister.
	TheDwordSwSmiHandle->DispatchHandle = OriginalHandle;


	return Status;
}

/**
    EFI_SMM_SW_DISPATCH2_PROTOCOL Unregister function.

    @param This Pointer to the EFI_SMM_SW_DISPATCH2_PROTOCOL
    @param DispatchHandle Handle to unregister

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
DwordSwSmiUnregister2 (
  IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                     DispatchHandle
  )
{
    EFI_STATUS  	Status = EFI_NOT_FOUND;
    FCH_SMM_SW_NODE *OriginalHandle = DispatchHandle;
    FCH_SMM_SW_NODE *TheDwordSwSmiHandle = NULL;

	// if DWORD SW SMI
	switch (OriginalHandle->Context.AmdSwValue & 0xff) {
		case EXTENDED_SMI:
			TheDwordSwSmiHandle = OriginalHandle->DispatchHandle;
			// recovery the AMD handle
			OriginalHandle->DispatchHandle = TheDwordSwSmiHandle->DispatchHandle;
			// free DWORD-SW-SMI handle which we created.
			gSmst->SmmFreePool(TheDwordSwSmiHandle);
			break;
		default:
			break;
	}

	Status = gOriginalUnRegister (This, DispatchHandle);

    return Status;
}

/**
    Collect AMD SW SMI NODE and translate to AMI HANDLER_LINK.

    @param DispatchHandle EFI Handle
    @param Context OPTIONAL - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
    @param CommBuffer OPTIONAL
    @param CommBufferSize OPTIONAL

    @retval VOID

**/
VOID
AmdFchSmmSwNodeTranslateToAMI (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
  )
{
    EFI_STATUS          Status;
    FCH_SMM_SW_NODE     static *CurrentFchSmmSwNodePtr = NULL;
    HANDLER_LINK        *HandlerLink = NULL;

    // the flow is ==> our dump function then user dump function.
    // 1. We got the first DispatchHandle right now.
    // 2. copy the context of FCH_SMM_SW_NODE to HANDLER_LINK.
    // 3. Call user dump function and pass the head of HANDLER_LINK.

    if (CurrentFchSmmSwNodePtr == NULL) {
        // We got the first DispatchHandle right now.
        CurrentFchSmmSwNodePtr = GET_FCH_SMM_SW_NODE_FROM_HANDLE(DispatchHandle);
        DListInit(&gTheSwSmiList);

        while (CurrentFchSmmSwNodePtr->FchSwNodePtr != NULL) {
            Status = pSmst->SmmAllocatePool(EfiRuntimeServicesData,
                                         sizeof(HANDLER_LINK) + sizeof(EFI_SMM_SW_DISPATCH_CONTEXT) - 1,
                                         &HandlerLink);
            if(EFI_ERROR(Status))
                return;
            HandlerLink->Callback = CurrentFchSmmSwNodePtr->CallBack2Function;
            HandlerLink->Signature = SMI_HANDLER_SIGNATURE;
            MemCpy(HandlerLink->Context, &CurrentFchSmmSwNodePtr->Context, sizeof(EFI_SMM_SW_DISPATCH_CONTEXT));

            DListAdd(&gTheSwSmiList, (DLINK *)HandlerLink);

            CurrentFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
        }
    }

    //###if (DispatchHandle == gOriginalSwSmiHandle)
    {
        HANDLER_LINK *Handler = (HANDLER_LINK *)gTheSwSmiList.pHead;
        // call user dump function and pass the Head.
        gOriginalHandler(Handler, Context, CommBuffer, CommBufferSize);
    }
}

/**
    EFI_SMM_SW_DISPATCH2_PROTOCOL Register function.

    @param This Pointer to EFI_SMM_SW_DISPATCH2_PROTOCOL
    @param DispatchFunction Pointer to callback function
    @param RegisterContext Pointer to callback context
    @param DispatchHandle Pointer to store registered handle

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EfiSmmSwRegister2 (
  IN  CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  OUT   EFI_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  )
{
	EFI_STATUS 						Status = EFI_SUCCESS;

    switch (RegisterContext->SwSmiInputValue & 0xFF) {
#ifdef DUMP_REGISTERED_SWSMI
    case DUMP_REGISTERED_SWSMI:
    	gOriginalHandler = DispatchFunction;
    	Status = gOriginalRegister(This, (EFI_SMM_HANDLER_ENTRY_POINT2)AmdFchSmmSwNodeTranslateToAMI, RegisterContext, DispatchHandle);
    	break;
#endif
	case EXTENDED_SMI:
#ifdef EXTENDED_SMI1
        case EXTENDED_SMI1:
#endif
#ifdef EXTENDED_SMI2
        case EXTENDED_SMI2:
#endif
#ifdef EXTENDED_SMI3
        case EXTENDED_SMI3:
#endif
#ifdef EXTENDED_SMI4
        case EXTENDED_SMI4:
#endif

		Status = DwordSwSmiRegister2(This, DispatchFunction, RegisterContext, DispatchHandle);
		break;
	default:
		Status = gOriginalRegister(This, DispatchFunction, RegisterContext, DispatchHandle);
		break;
	}

	return Status;
}

/**
    EFI_SMM_SW_DISPATCH2_PROTOCOL Unregister function.

    @param This Pointer to the EFI_SMM_SW_DISPATCH2_PROTOCOL
    @param DispatchHandle Handle to unregister

              
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EfiSmmSwUnregister2 (
  IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                     DispatchHandle
  )
{
    EFI_STATUS  	Status = EFI_NOT_FOUND;

    Status = DwordSwSmiUnregister2(This, DispatchHandle);

    return Status;
}

/**
    A hook function for dump SW-SMI value.
    Hook on to AMD FchSmmDispatcher.

    @param Protocol this event GUID
    @param Interface this event Interface.
    @param Handle this event Handle.

              
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SwSmiHook (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;
	EFI_SMM_SW_DISPATCH2_PROTOCOL	*SmmSwProtocol = Interface;

	gOriginalRegister = SmmSwProtocol->Register;
	gOriginalUnRegister = SmmSwProtocol->UnRegister;

	SmmSwProtocol->Register = EfiSmmSwRegister2;
	SmmSwProtocol->UnRegister = EfiSmmSwUnregister2;

	return Status;
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
