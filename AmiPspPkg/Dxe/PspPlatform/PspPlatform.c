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

/** @file PspPlatform.c
    PSP Platform driver

**/

#include <Protocol/PspPlatformProtocol.h>
#include "Token.h"
#include <Library/DebugLib.h>

EFI_HANDLE  PspPlatformHandle = NULL;

#define RESUME_BSP_STACK_SIZE   CAR_TOTAL_SIZE
#define RESUME_AP_STACK_SIZE    AP_STACK_SIZE

PSP_PLATFORM_PROTOCOL PspPlatformProtocol = {
  TRUE,                   // Support CPU Context Resume
  PSP_NOTIFY_SMM_SW_SMI,  // SW SMI Command for Build Context
  RESUME_BSP_STACK_SIZE,  // BSP Stack Size
  RESUME_AP_STACK_SIZE,   // AP Stack Size
  NULL                    // Address of PEI Info Structure
};

EFI_BOOT_SERVICES   *gBS;

/**
    PSP Platform driver entry point

               
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
EFIAPI
PspPlatformEntry (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    UINT64              RsmInfoLocation = 0;
    EFI_STATUS          Status;
    UINT32  volatile    *Rom;
    UINT64              SecLabel;
    UINT64				EndOfSec;

    gBS = SystemTable->BootServices;

    // Search the SEC_BSPStart label
#if defined(PSP_FV_BB_COMPRESS) && (PSP_FV_BB_COMPRESS == 1)
	EndOfSec = (UINT64)(HIGH_MEMORY_REGION_BB_BASE + (PSP_FV_BB_SIZE - 0x10));
	SecLabel = *(UINT64*)EndOfSec;
	SecLabel = EndOfSec - ((SecLabel >> 24) & 0xFFFF); // End of SEC - SEC near jump
	SecLabel = (UINT64)ALIGN_POINTER(SecLabel, 4); // 4 alignment
#else
	EndOfSec = 0xFFFFFF00;
    SecLabel = *(UINT64*)0x0FFFFFFF0;
    SecLabel = (SecLabel >> 24) & 0x0000FFF0;   // 4 alignment
    SecLabel |= 0xFFFF0000;
#endif
    Rom = (UINT32*)SecLabel;

    while (Rom < (UINT32*)EndOfSec)
    {
        if (*Rom == 0x54535251)
        {
            RsmInfoLocation = (UINT32)(Rom + 1);
            break;
        }
        Rom++;
    }

    DEBUG((DEBUG_INFO, "PSPplatform RsmInfoLocation = %x\n", RsmInfoLocation));
    ASSERT (RsmInfoLocation);

    PspPlatformProtocol.RsmHandOffInfo = (RSM_HANDOFF_INFO *)RsmInfoLocation;

    // Install Protocol
    Status = gBS->InstallProtocolInterface (&PspPlatformHandle, &gPspPlatformProtocolGuid,
                   EFI_NATIVE_INTERFACE, &PspPlatformProtocol);
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
