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

/** @file CpuSmm.c
    This file contains code for Cpu Smm events

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiSmm.h>
#include <Library/BaseLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Token.h>


// Produced Protocols

// Consumed Protocols
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
#define MSR_HWCR    0xC0010015
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
 AP task to sync MSRs with the BSC


    @param[in]  Temp          Not used

    @retval VOID
 */
VOID
CpuSetSmmLockBit (
  IN       VOID *Temp
  )
{
    AsmMsrAndThenOr64(MSR_HWCR, ~(UINT64)BIT0, (UINT64)BIT0);
}

/**
    This is to set SMM lock bit to each of AP.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval VOID
**/

EFI_STATUS
CpuSwSmiHandler (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID  	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;
	UINTN                           Index = 1;
	UINT64                          MsrValue;

	if (CommBuffer != NULL)
	{
	    if (((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort == CPU_SWSMI)
	    {
	        DEBUG ((DEBUG_INFO,"CpuSwSmiHandler Entry \n"));

	        MsrValue = AsmReadMsr64(MSR_HWCR);
	        // Check if SMM lock bit is already set
	        if (MsrValue & BIT0)
	        {
	            return  Status;
	        }
	        // Set BSP SMM lock bit first
	        MsrValue |= BIT0;
	        AsmWriteMsr64(MSR_HWCR, MsrValue);

	        for (Index = 1; Index < gSmst->NumberOfCpus; Index++)
	        {
	            // Set AP SMM lock bit
                gSmst->SmmStartupThisAp (
                CpuSetSmmLockBit,
                Index,
                NULL
                );
	        }
	    }
	}

    return Status;
}


/**
    Installs CPU SMM Handler.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_NOT_FOUND The SMM Base protocol is not found.
    @retval EFI_SUCCESS Installs CRB SMM Child Dispatcher Handler successfully.
**/

EFI_STATUS
EFIAPI
CpuSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                		Status;
	EFI_SMM_SW_DISPATCH2_PROTOCOL  	*SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext = {CPU_SWSMI};
    EFI_HANDLE                      Handle = NULL;


    Status  = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, &SwDispatch);
    DEBUG ((DEBUG_INFO,"Locate gEfiSmmSwDispatch2ProtocolGuid status = %r \n", Status));
    if (!EFI_ERROR(Status)) {
        Status  = SwDispatch->Register( SwDispatch, \
                                         CpuSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
        DEBUG ((DEBUG_INFO,"Register CpuSwSmiHandler status = %r \n", Status));
    }

    return Status;
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
