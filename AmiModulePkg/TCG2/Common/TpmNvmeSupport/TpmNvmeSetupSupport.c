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
    

/**
  Entry point for the driver.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
VOID InitTcgNvme(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
    EFI_STATUS           Status;
    EFI_HANDLE           *NvmePassThruHandles;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   *NvmeDevice;
    UINTN                NumOfHandles=0;
    UINTN                Index;
    BOOLEAN              Found = FALSE;
    UINT8                SetupDataBuffer;
    UINTN                SetupVariableSize = sizeof(UINT8);
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
    EDKII_VARIABLE_LOCK_PROTOCOL    *LockProtocol;
#endif
    
    SetupDataBuffer = 0;
    Status = gRT->SetVariable (
               L"TcgNvmeVar",
               &gSetupVariableGuid,
               EFI_VARIABLE_BOOTSERVICE_ACCESS,
               SetupVariableSize,
               &SetupDataBuffer);
    
    if(EFI_ERROR(Status))return;
        
    Status = gBS->LocateHandleBuffer (
                     ByProtocol,
                     &gEfiNvmExpressPassThruProtocolGuid,
                     NULL,
                     &NumOfHandles,
                     &NvmePassThruHandles
                   );
    
    if(EFI_ERROR(Status)){
        if(NumOfHandles){
            gBS->FreePool(NvmePassThruHandles);
        }
        
        return;
    }
        
    for (Index = 0; Index < NumOfHandles; Index++) {

       Status = gBS->HandleProtocol (
               NvmePassThruHandles[Index],
               &gEfiNvmExpressPassThruProtocolGuid,
               (VOID **) &NvmeDevice);
               
       if (EFI_ERROR (Status)) {
         DEBUG ((DEBUG_INFO, "gBS->HandleProtocol: Status=%r\n", Status));
         continue;
       }
        
       if (!EFI_ERROR(Status)) {
           Found = TRUE;
           break;
       }
   }
        

   SetupDataBuffer = Found;
   
   Status = gRT->SetVariable (
                L"TcgNvmeVar",
                &gSetupVariableGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                SetupVariableSize,
                &SetupDataBuffer);
   
   if(EFI_ERROR(Status)){
       DEBUG ((DEBUG_INFO, "Set TcgNvmeVar Status = %r\n", Status));
   }
   DEBUG ((DEBUG_INFO, "Set NvmeDeviceFound Status = %r\n", Status));
   
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
   Status =  gBS->LocateProtocol(&gEdkiiVariableLockProtocolGuid, NULL, (void **)&LockProtocol);
   if(!EFI_ERROR(Status))
   {
       LockProtocol->RequestToLock(LockProtocol, L"TcgNvmeVar", &gSetupVariableGuid);
   }
#endif

   if(NumOfHandles){
       gBS->FreePool(NvmePassThruHandles);
   }
   return;
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
