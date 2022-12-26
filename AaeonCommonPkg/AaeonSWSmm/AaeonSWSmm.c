#include <token.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/PciLib.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmCpu.h>



EFI_SMM_SW_DISPATCH2_PROTOCOL *mSwDispatch;


/**
  The SW SMI callback Function

  @param[in]      DispatchHandle  The handle of this callback, obtained when registering
  @param[in]      CallbackContext Pointer to the EFI_SMM_SW_REGISTER_CONTEXT
  @param[in, out] CommBuffer      Point to the CommBuffer structure
  @param[in, out] CommBufferSize  Point to the Size of CommBuffer structure
**/
VOID
AaeonSwSmiCallback (
  IN EFI_HANDLE                  DispatchHandle,
  IN EFI_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT VOID                    *CommBuffer,
  IN OUT UINTN                   *CommBufferSize
  )
{
  IoWrite8(0x80, SwSMI_RegNum);
}

/**
  Register Aaeon SW SMI dispatch function 

  @param[in] ImageHandle          The image handle of this module
  @param[in] SystemTable          The EFI System Table

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
EFIAPI
InitializeAaeonSWSmm (
  IN      EFI_HANDLE            ImageHandle,
  IN      EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_HANDLE                            SwDispatchHandle;
  EFI_SMM_SW_REGISTER_CONTEXT           SwDispatchContext;

  DEBUG ((DEBUG_INFO, "Aaeon SW SMM () Start\n"));

  //
  // Register Aaeon SW SMI handler
  //
  SwDispatchHandle  = NULL;
  SwDispatchContext.SwSmiInputValue = SwSMI_RegNum;    //Sw Smi register number .
  Status = mSwDispatch->Register (
                          mSwDispatch,
                          (EFI_SMM_HANDLER_ENTRY_POINT2) AaeonSwSmiCallback,
                          &SwDispatchContext,
                          &SwDispatchHandle
                          );
  ASSERT_EFI_ERROR (Status);


  DEBUG ((DEBUG_INFO, "Aaeon SW SMM () End\n"));

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AaeonSWSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS          Status;
  

  DEBUG ((DEBUG_INFO, "AaeonSWSmmEntryPoint()\n"));

  //
  // Locate the SMM SW dispatch protocol
  //
   
  
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSwDispatch2ProtocolGuid,
                    NULL,
                    (VOID **) &mSwDispatch
                    );
  ASSERT_EFI_ERROR (Status);

  Status = InitializeAaeonSWSmm (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "AaeonSWSmm Exit()\n"));
  return EFI_SUCCESS;
}
