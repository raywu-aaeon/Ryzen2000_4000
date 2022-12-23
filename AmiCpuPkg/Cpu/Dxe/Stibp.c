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

/** @file Stibp.c

**/
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Token.h>
#include <Protocol/Variable.h>
#include <Protocol/MpService.h>
#include <Setup.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include "Library/AmdBaseLib.h"
#include <Library/AmdSocBaseLib.h>


EFI_GUID gEfiSetupGuid = SETUP_GUID;

SETUP_DATA      SetupData;

// Summit
#define F17_00_0F_B0        0x00800F10
#define F17_00_0F_B1        0x00800F11
#define F17_00_0F_B2        0x00800F12
// Pinnacle
#define F17_00_0F_B2_PR     0x00800F82

// Raven
#define F17_10_1F_B0        0x00810F10


/* -----------------------------------------------------------------------------*/
/**
 *
 *  SetStibpMsr
 *
 *  Description:
 *    This routine sets STIBP MSR:
 *
 */
VOID
SetStibpMsr (
  IN       VOID  *Void
  )
{
    UINT64     LocalMsrRegister;

    // Force recalc of TSC on all threads after loading patch
    LocalMsrRegister = AsmReadMsr64 (0xC001102E);
    LocalMsrRegister |= 0x14008000;
    AsmWriteMsr64 (0xC001102E, LocalMsrRegister);
}

/**
    StibpEntryPoint

        
    @param ImageHandle 
    @param SystemTable 

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
StibpEntryPoint(
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                      Status;
    UINTN                           VariableSize;
    UINT32                          Attributes = 0;
    UINT32                          RegEax = 0;
    SOC_ID_STRUCT                   SocId;
    UINT64                          Value64 = 0;
    CHAR16                          SetupVariable[] = L"Setup";
    EFI_MP_SERVICES_PROTOCOL        *MpServices;


    DEBUG((DEBUG_INFO, " Stibp entry\n"));

    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (SetupVariable, &gEfiSetupGuid, &Attributes, &VariableSize,
                   &SetupData);
    if (EFI_ERROR(Status))
        return Status;

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;
    if (SocHardwareIdentificationCheck (&SocId))
    {
        SetupData.HideStibp = 1;
        //Family 15h don't need to apply STIBP
        Status = gRT->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                      VariableSize, &SetupData);
        return EFI_SUCCESS;
    }

    Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    if (EFI_ERROR(Status))
        return Status;

    AsmCpuid(1, &RegEax, NULL, NULL, NULL);
    DEBUG((DEBUG_INFO, " CPUID 0x00000001 Eax = 0x%lX\n", RegEax));

    // only for Family 17h 00h-0Fh, rev B0/B1/B2, and Family 17h 10-1Fh, rev B0
    if ((RegEax == F17_00_0F_B0) || (RegEax == F17_00_0F_B1) || (RegEax == F17_00_0F_B2) ||
        (RegEax == F17_00_0F_B2_PR) || (RegEax == F17_10_1F_B0))
    {
        if (SetupData.HideStibp == 1)
        {
            SetupData.HideStibp = 0;
            Status = gRT->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                          VariableSize, &SetupData);
        }
        if (SetupData.StibpStatus == 1)
        {
            Value64 = AsmReadMsr64(0xC001102E);
            //MSR 0xC001_102E[28,26,15] = 1 for enable
            Value64 |= 0x14008000;
            AsmWriteMsr64(0xC001102E, Value64);

            MpServices->StartupAllAPs (
                    MpServices,
                    SetStibpMsr,
                    TRUE,
                    NULL,
                    0,
                    NULL,
                    NULL
            );
        }
    }
    else
    {
        // we hide this option if the CPU is not affected
        if (SetupData.HideStibp == 0)
        {
            SetupData.HideStibp = 1;
            Status = gRT->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                          VariableSize, &SetupData);
        }
    }

    DEBUG((DEBUG_INFO, " Stibp exit\n"));

    return EFI_SUCCESS;
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
