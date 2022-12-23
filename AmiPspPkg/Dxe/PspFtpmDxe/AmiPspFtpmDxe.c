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

/** @file AmiPspFtpmDxe.c
    PSP Ftpm DXE driver

**/

#include "Token.h"
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/AmiPsp.h>
#include <AmiPspFtpm.h>
#include <Protocol/SmmCommunication.h>


// Size of SMM communicate header, without including the Data.
#define SMM_COMMUNICATE_HEADER_SIZE  (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data))

EFI_SMM_COMMUNICATION_PROTOCOL  *SmmCommunication = NULL;
UINT8                           *CommunicateBuffer = NULL;
UINTN                           CommunicateBufferSize;

/**
    AMI PSP Ftpm DXE driver entry point.
    Check if we need to erase the PSP NVRAM.
               
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
EFIAPI
AmiPspFtpmDxeDriverEntry (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS              Status;
    AMI_PSP_FTPM_HOB        *AmiPspFtpmHob;
    VOID                    *FirstHob;

    DEBUG((DEBUG_INFO, "AmiPspFtpmDxeDriverEntry Entry\n"));

    Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &FirstHob);
    if (EFI_ERROR(Status)) return Status;

    AmiPspFtpmHob = GetNextGuidHob(&gAmiPspFtpmHobGuid, FirstHob);
    if (!AmiPspFtpmHob) return EFI_NOT_FOUND;

    if (AmiPspFtpmHob->ClearPspNvram == PSP_FTPM_FLAG_CLEAR)
    {
        // WSMT requirement : communication buffer must be allocated before end of DXE.
        CommunicateBufferSize = SMM_COMMUNICATE_HEADER_SIZE + sizeof(UINT8);
        DEBUG((DEBUG_INFO, "CommunicateBufferSize for AmiPspFtpmNvSmi = 0x%lx\n", CommunicateBufferSize));

        Status = gBS->AllocatePool(EfiRuntimeServicesData,
                                   CommunicateBufferSize,
                                   (VOID**)&CommunicateBuffer);
        if (!EFI_ERROR(Status))
        {
            gBS->SetMem(CommunicateBuffer, CommunicateBufferSize, 0);
        }
        DEBUG((DEBUG_INFO, "CommunicateBuffer = 0x%lx\n", CommunicateBuffer));
        PcdSet32S(PcdFtpmSmmCommunicateBuffer, (UINT32)CommunicateBuffer);
        PcdSet32S(PcdFtpmSmmCommunicateBufferSize, (UINT32)CommunicateBufferSize);
    }
    DEBUG((DEBUG_INFO, "AmiPspFtpmDxeDriverEntry Exit\n"));

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
