//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file TpmSmbiosDxe.c
    Install Tpm Device type in Smbios table

**/

//---------------------------------------------------------------------------
#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Token.h>
#include "MdePkg/Include/Protocol/NvmExpressPassthru.h"
#include <Setup.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Guid/AmiTcgGuidIncludes.h>
#include <AmiTcg/TCGMisc.h>
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
#include <Protocol/VariableLock.h>
#endif
    

void         *Callbackregistration = NULL;
EFI_EVENT     EventRegistration = NULL;

#define TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC     96
#define TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC    97

extern EFI_GUID gEdkiiVariableLockProtocolGuid;
extern EFI_GUID gEfiNvmExpressPassThruProtocolGuid;

/**
  Entry point for the driver.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
TpmNvmeSupportDxeEntry (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  EFI_STATUS        Status;
  AMI_PPI_NV_VAR    Ppivar;
  UINT32 Attribs2 = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS 
                    | EFI_VARIABLE_RUNTIME_ACCESS;
  UINTN PpivarSize = sizeof (AMI_PPI_NV_VAR);
  SETUP_DATA          SetupDataBuffer;
  UINTN               SetupVariableSize = sizeof(SETUP_DATA);
  UINT32              SetupVariableAttributes;
  
  DEBUG((DEBUG_INFO," \n TpmNvmeSupportDxeEntry  \n "));
  
  Status = gRT->GetVariable ( L"Setup",
                              &gSetupVariableGuid,
                              &SetupVariableAttributes,
                              &SetupVariableSize,
                              &SetupDataBuffer);
  
  if(!EFI_ERROR(Status)){
      
      if(SetupDataBuffer.BlockSidSetup){
          SetupDataBuffer.BlockSidSetup = 0;
               
          Status = gRT->SetVariable (
                        L"Setup",
                        &gSetupVariableGuid,
                        SetupVariableAttributes,
                        SetupVariableSize,
                        &SetupDataBuffer);
           
          Ppivar.RQST    = TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC;
          Ppivar.RCNT    = 0;
          Ppivar.ERROR   = 0;
          Ppivar.Flag    = 0;
          Ppivar.AmiMisc = 0;
           
          Status = gRT->SetVariable(L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid,
                                                                Attribs2, PpivarSize, &Ppivar);
      }
     
  }
  
  return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
