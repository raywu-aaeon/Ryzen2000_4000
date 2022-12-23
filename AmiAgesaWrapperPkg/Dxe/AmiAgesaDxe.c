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

/** @file AmiAgesaDxe.c
    AMI DXE AGESA wrapper to build ACPI P-State tables.

**/

#include "PiDxe.h"
#include "AMD.h"
#include "Token.h"
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/BaseLib.h>
#include "AmiAgesaDxe.h"
#include <Protocol/Variable.h>
#include "Guid/AmiGlobalVariable.h"
#include "Library/AmdBaseLib.h"
#include <Library/AmdSocBaseLib.h>
#include <Setup.h>
#include <Protocol/MpService.h>

CHAR16      SpdBypassData[]        = L"SpdBypassData";
CHAR16      SpdBypassSerial[]      = L"SpdBypassSerial";

CHAR16      MemRestoreSerial[]      = L"MemRestoreSerialLength";
CHAR16      MemRestoreCpu[]         = L"MemRestoreCpuId";
CHAR16      MemRestoreConfigId[]    = L"MemRestoreConfigId";
CHAR16      ModuleVersion[]         = L"ModuleVersion";
CHAR16      MemRestoreTime[]        = L"MemRestoreTime";

extern EFI_RUNTIME_SERVICES     *gRT;
extern EFI_BOOT_SERVICES        *gBS;

/**
  AmiPcdAmdAcpiS3Callback notify callback function, this function is callbacked to
  enable/disable AcpiSleepState function according to PcdAmdAcpiS3Support

  @param  Event    The event of notify protocol.
  @param  Context  Notify event context.

**/
VOID EFIAPI AmiPcdAmdAcpiS3Callback (
    IN EFI_EVENT Event,
    IN VOID      *Context)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINTN                       VariableSize = 0;
    UINT32                      SetupAttributes = 0;
    UINT32                      Attributes = 0;
    SETUP_DATA                  SetupData;
    EFI_GUID                    EfiSetupGuid = SETUP_GUID;
    UINT16                      PcdS3SleepStateBackup = 0;
    UINT16                      CachePcdS3Backup = 0;
    UINT16                      CacheSleepStateBackup = 0;
    UINT16                      CachePcdAmdAcpiS3Support = 0;

    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (L"Setup", &EfiSetupGuid, &SetupAttributes, &VariableSize,
                   &SetupData);
    if (Status) return;

    CachePcdAmdAcpiS3Support = (UINT16)(PcdGetBool(PcdAmdAcpiS3Support));
    VariableSize = sizeof(UINT16);
    Status = gRT->GetVariable (L"AcpiSSBackup", &gAmiAgesaAcpiSleepStateBackupGuid, &Attributes, &VariableSize,
                   &PcdS3SleepStateBackup);
    if (Status == EFI_NOT_FOUND)
    {
        // It's the first time boot, set the default value. We can use AcpiSleepState as the default value.
        // PcdS3SleepStateBackup[15:8] = backup of PcdAmdAcpiS3Support.
        // PcdS3SleepStateBackup[7:0]  = backup of SetupData.AcpiSleepState.
        PcdS3SleepStateBackup = ((CachePcdAmdAcpiS3Support << 8) | SetupData.AcpiSleepState);
        VariableSize = sizeof(UINT16);
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
        Status = gRT->SetVariable (L"AcpiSSBackup", &gAmiAgesaAcpiSleepStateBackupGuid, Attributes,
                      VariableSize, &PcdS3SleepStateBackup);
        ASSERT_EFI_ERROR(Status);
    }

    CachePcdS3Backup = PcdS3SleepStateBackup >> 8;
    CacheSleepStateBackup = PcdS3SleepStateBackup & 0x0FF;

    DEBUG((DEBUG_INFO, " AmiAgesaDxe: Current ACPI SleepState = %lx\n", SetupData.AcpiSleepState));
    DEBUG((DEBUG_INFO, " AmiAgesaDxe: PcdS3SleepStateBackup = %lx\n", PcdS3SleepStateBackup));
    DEBUG((DEBUG_INFO, " AmiAgesaDxe: CachePcdAmdAcpiS3Support = %lx\n", CachePcdAmdAcpiS3Support));

    if (CachePcdAmdAcpiS3Support == 0 && SetupData.AcpiSleepState == 2)
    {
        // Save the original AcpiSleepState and CachePcdAmdAcpiS3Support value before AcpiSleepState is disabled
        PcdS3SleepStateBackup = ((CachePcdAmdAcpiS3Support << 8) | SetupData.AcpiSleepState);
        VariableSize = sizeof(UINT16);
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
        Status = gRT->SetVariable (L"AcpiSSBackup", &gAmiAgesaAcpiSleepStateBackupGuid, Attributes,
                      VariableSize, &PcdS3SleepStateBackup);
        ASSERT_EFI_ERROR(Status);

        // Always set AcpiSleepState to disable when SMT is disabled or downcore is enabled
        SetupData.AcpiSleepState = 0;
        VariableSize = sizeof (SETUP_DATA);
        Status = gRT->SetVariable (L"Setup", &EfiSetupGuid, SetupAttributes,
                      VariableSize, &SetupData);
        ASSERT_EFI_ERROR(Status);
    }
    else if (CachePcdAmdAcpiS3Support == 0 && CachePcdS3Backup == 1 && SetupData.AcpiSleepState == 0)
    {
        // Save the original AcpiSleepState and CachePcdAmdAcpiS3Support value
        PcdS3SleepStateBackup = ((CachePcdAmdAcpiS3Support << 8) | SetupData.AcpiSleepState);
        VariableSize = sizeof(UINT16);
        Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
        Status = gRT->SetVariable (L"AcpiSSBackup", &gAmiAgesaAcpiSleepStateBackupGuid, Attributes,
                      VariableSize, &PcdS3SleepStateBackup);
        ASSERT_EFI_ERROR(Status);
    }
    else if (CachePcdAmdAcpiS3Support == 1 && CachePcdS3Backup == 0)
    {
        // SMT or downcore function are changed, so it needs to restore the original value
         if (CacheSleepStateBackup == 0x2)
         {
             VariableSize = sizeof (SETUP_DATA);
             SetupData.AcpiSleepState = 2;
             Status = gRT->SetVariable (L"Setup", &EfiSetupGuid, SetupAttributes,
                           VariableSize, &SetupData);
             ASSERT_EFI_ERROR(Status);
         }

         PcdS3SleepStateBackup = ((CachePcdAmdAcpiS3Support << 8) | SetupData.AcpiSleepState);
         VariableSize = sizeof(UINT16);
         Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;
         Status = gRT->SetVariable (L"AcpiSSBackup", &gAmiAgesaAcpiSleepStateBackupGuid, Attributes,
                       VariableSize, &PcdS3SleepStateBackup);
         ASSERT_EFI_ERROR(Status);
    }

    gBS->CloseEvent(Event);

    return;
}


/**
    AGESA wrapper DXE phase.
    
    1. Save memory restore context for PEI.

        
    @param ImageHandle 
    @param SystemTable Pointer to system table

         
    @retval EFI_SUCCESS The function completed successfully.

**/

EFI_STATUS
EFIAPI
AmiAgesaDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    MEMRESTORE_SERIAL_HOB       *MemRestoreSerialHob = NULL;
    UINT32                      RegEax = 0;
    UINT8                       Value8 = 0;
    UINTN                       VariableSize = 0;
    UINT32                      AgesaModuleRevision = 0;
    EFI_TIME                    CurrentTime;
    MEM_RESTORE_HOB             *MemRestoreHob = NULL;
    SOC_ID_STRUCT               SocId;
    EFI_EVENT                   AmiPcdAmdAcpiS3Event;
    VOID                        *AmiPcdAmdAcpiS3EventReg;

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (!SocHardwareIdentificationCheck (&SocId))
    {
        Status = gBS->CreateEvent( EVT_NOTIFY_SIGNAL,
                                   TPL_CALLBACK, AmiPcdAmdAcpiS3Callback, NULL, &AmiPcdAmdAcpiS3Event);
        DEBUG((DEBUG_INFO, "CreateEvent AmiPcdAmdAcpiS3Callback status = %r\n", Status));

        Status = gBS->RegisterProtocolNotify(&gEfiMpServiceProtocolGuid, AmiPcdAmdAcpiS3Event, &AmiPcdAmdAcpiS3EventReg);
        DEBUG((DEBUG_INFO, "RegisterProtocolNotify AmiPcdAmdAcpiS3Callback status = %r\n", Status));

        return  EFI_SUCCESS;
        // Family17 don't need to do memory restore function.
    }

    if (PcdGet16(PcdAgesaMemrestoreSupport))
    {
        MemRestoreSerialHob = GetFirstGuidHob(&gAmiAgesaMemRestoreSerialHobGuid);
        if (MemRestoreSerialHob)
        {
            // check if we need to set variable or not
            if (MemRestoreSerialHob->SPDUpdate == 1)
            {
                // Save SPD Serial Number to NvRam
                Status = gRT->SetVariable(
                    MemRestoreSerial, &gAmiGlobalVariableGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    MEMRESTORE_SERIAL_HOB_LENGTH, &(MemRestoreSerialHob->SPD_Serial)
                );
            }
        }

        MemRestoreHob = GetFirstGuidHob(&gAmiAgesaMemRestoreGuid);
        
        if (MemRestoreHob != NULL)
        {
  	        DEBUG((DEBUG_INFO, " AmiAgesaDxe: MemRestoreHob->Count = %x\n", MemRestoreHob->Count));
            if (MemRestoreHob->SaveMemContext)
            {
                Status = gRT->SetVariable(
                                L"MemContext",
                                &gAmiAgesaMemRestoreGuid,
                                EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                EFI_VARIABLE_NON_VOLATILE,
                                sizeof(AMI_S3_PARAMS),
                                &MemRestoreHob->MemContext
                             );
                DEBUG((DEBUG_INFO, "\n\n AmiAgesaDxe: SetVariable(MemContext) = %r\n", Status));
            }
        }

        //Set CPUID in the nvram
        AsmCpuid(1, &RegEax, NULL, NULL, NULL);
        Status = gRT->SetVariable(
            MemRestoreCpu, &gAmiGlobalVariableGuid,
            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
            sizeof(UINT32), &RegEax);
        DEBUG((DEBUG_INFO, "AmiAgesaDxe: SetVariable MemRestoreCpu - %r\n", Status));

        if (EFI_ERROR(Status)) {
            return Status;
        }

        // Set current date to NVRAM
        Status = gRT->GetTime(&CurrentTime, 0);

        if (Status == EFI_SUCCESS)
        {
            //Check if we need to set this current date!
            IoWrite8(0x72, PcdGet8(PcdCmosAgesaSpecified));
            IoRead8(0x61);
            Value8 = IoRead8(0x73); // Read from CMOS

            if (Value8 & BIT2) {
            Status = gRT->SetVariable(
                        MemRestoreTime, &gAmiGlobalVariableGuid,
                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        sizeof(EFI_TIME), &CurrentTime);
            }
        }

        // Set Module_Revision to NVRAM
        VariableSize = sizeof(UINT32);
        Status = gRT->GetVariable(ModuleVersion, &gAmiGlobalVariableGuid,
                   NULL, &VariableSize, &AgesaModuleRevision);

        DEBUG((DEBUG_INFO, ">> >>AmiAgesaDxe.GetVariable() Status = %r, AgesaModuleRevision = %x\n", Status, AgesaModuleRevision));

        if ((AgesaModuleRevision != AGESA_MODULE_REVISION) || (EFI_ERROR(Status)))
        {
            AgesaModuleRevision = AGESA_MODULE_REVISION;
            Status = gRT->SetVariable(
                ModuleVersion, &gAmiGlobalVariableGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                sizeof(UINT32), &AgesaModuleRevision);
        }
    }   // if (PcdGet16(PcdAgesaMemrestoreSupport))

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
