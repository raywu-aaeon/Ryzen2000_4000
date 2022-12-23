//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  SmiFlash SMM Driver Sub-Procedure File.
**/

//----------------------------------------------------------------------
// header includes
#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol/AmiSmiFlash.h>
#include <Setup.h>
#include <Protocol/AmiFlash.h>
#include <SMIFlashELinks.h>
#include <ImageAuthentication.h>
#include <TimeStamp.h>
#if AMIUSB_SUPPORT == 1
#include <Protocol/AmiUsbController.h>
extern EFI_GUID gAmiUsbSmmProtocolGuid;
#endif  // #if AMIUSB_SUPPORT == 1

//----------------------------------------------------------------------
// component MACROs
#define DEFAULT_VARIABLE_NAME_SIZE     100

#ifndef AMI_SECURE_BOOT_SETUP_VAR
#define AMI_SECURE_BOOT_SETUP_VAR  L"SecureBootSetup"
#endif  // #ifndef AMI_SECURE_BOOT_SETUP_VAR

#pragma pack(1)
typedef struct {
    CHAR16      *BootVarName;
    EFI_GUID    Guid;
    UINT32      Attrib;
    UINTN       Size;
    UINT8       *Data;
    VOID        *NextData;
} SAVED_VAR;

typedef struct {
    CHAR16      *Name;
    EFI_GUID    Guid;
    UINT8       IsAuthVars;
    VOID        *pVariable;
} NVAR_LIST;

// Replace WIN_CERTIFICATE_UEFI_GUID_1 with WIN_CERTIFICATE_EFI_PKCS1_15 for
// avoiding to include AmiCertificate.h of AmiCryptoPkg.
typedef struct {
    EFI_TIME                            TimeStamp;
    WIN_CERTIFICATE_EFI_PKCS1_15         AuthInfo;
} AMI_EFI_VARIABLE_AUTHENTICATION_2;

#pragma pack()

//----------------------------------------------------------------------
// Module defined global variables

#if !defined _OUTSIDE_SMM_
//*********** INSIDE SMM ***********************************************
#include <Library/SmmServicesTableLib.h>
#if defined EMUL6064_SUPPORT && (EMUL6064_SUPPORT == 1)
#include <Protocol/Emul6064Trap.h>
EFI_EMUL6064TRAP_PROTOCOL *gEmulationTrap = NULL;
#endif

#if AMIUSB_SUPPORT == 1
#if USB_DRIVER_MAJOR_VER >= 10
API_FUNC gUsbRtKbcAccessControl = NULL;
#else
EFI_KBC_ACCESS_CONTROL gUsbRtKbcAccessControl = NULL;
#endif
#endif

EFI_FFS_FILE_STATE  NvramFFSState;
EFI_FFS_FILE_STATE  *NvramFFSStatePtr;
SAVED_VAR           *gRestoreVarList = NULL;

NVAR_LIST gFixedSaveVarsList[] = {
    SMIFLASH_SAVE_VARS_LIST
    { NULL, { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } }, FALSE, NULL }
};

EFI_GUID gSmiFlashSaveGuidsList[] = {
    SMIFLASH_SAVE_GUIDS_LIST
    { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } }
};

typedef EFI_STATUS (*SHOW_BOOT_TIME_VARIABLES)(BOOLEAN Show);
typedef struct{
    SHOW_BOOT_TIME_VARIABLES ShowBootTimeVariables;
} AMI_NVRAM_CONTROL_PROTOCOL;

AMI_NVRAM_CONTROL_PROTOCOL *gSfAmiNvramControl;

//----------------------------------------------------------------------
// externally defined variables

//----------------------------------------------------------------------
// Function definitions
/**
 * Procedure to locates the Nvram Control Protocol for enabling Boot Time Variable search.
 *
 * @retval AMI_NVRAM_CONTROL_PROTOCOL* Nvram Control Protocol pointer.
 * @retval NULL Nvram Control Protocol not located.
 */
AMI_NVRAM_CONTROL_PROTOCOL *LocateNvramControlSmmProtocol(VOID){
    static EFI_GUID gAmiNvramControlProtocolGuid = \
    { 0xf7ca7568, 0x5a09, 0x4d2c, { 0x8a, 0x9b, 0x75, 0x84, 0x68, 0x59, 0x2a, 0xe2 } };
    return GetSmstConfigurationTable(&gAmiNvramControlProtocolGuid);
}

/**
 * Procedure to update the authentication Header of Variable.
 *
 * @param pVar Pointer to the Variable.
 */
#if defined SecureBoot_SUPPORT && SecureBoot_SUPPORT == 1
#if defined SECURE_BOOT_MODULE_REVISION && SECURE_BOOT_MODULE_REVISION < 14
static VOID FillAuthHeader(
    UINT8*  pVar
)
{
    AMI_EFI_VARIABLE_AUTHENTICATION_2 *AuthHdr2;
    EFI_GUID        EfiCertTypePkcs7Guid = EFI_CERT_TYPE_PKCS7_GUID;
    EFI_TIME        EfiTime = { FOUR_DIGIT_YEAR_INT, \
                                TWO_DIGIT_MONTH_INT, \
                                TWO_DIGIT_DAY_INT, \
                                TWO_DIGIT_HOUR_INT, \
                                TWO_DIGIT_MINUTE_INT, \
                                TWO_DIGIT_SECOND_INT, \
                                0,0,0,0,0};

    AuthHdr2 = (AMI_EFI_VARIABLE_AUTHENTICATION_2*)pVar;
    MemCpy (&AuthHdr2->TimeStamp, &EfiTime, sizeof (EFI_TIME));
    AuthHdr2->AuthInfo.Hdr.dwLength = sizeof(WIN_CERTIFICATE_EFI_PKCS1_15);
    AuthHdr2->AuthInfo.Hdr.wRevision = 0x200;
    AuthHdr2->AuthInfo.Hdr.wCertificateType = WIN_CERT_TYPE_EFI_GUID;
    AuthHdr2->AuthInfo.HashAlgorithm = EfiCertTypePkcs7Guid;
    return;
}
#endif  // #if defined SECURE_BOOT_MODULE_REVISION && SECURE_BOOT_MODULE_REVISION < 14
#endif  // #if defined SecureBoot_SUPPORT && SecureBoot_SUPPORT == 1

/**
 * Procedure to check whether it's a Boot LoadOption variable.
 *
 * @param Name Variable Name Pointer.
 * @param Guid Variable GUID Pointer.
 * @param Data Variable Data Pointer.
 */
BOOLEAN
IsEfiBootVarsValid (
    IN CHAR16               *Name,
    IN EFI_GUID             *Guid,
    IN VOID                 *Data
)
{
    CHAR16      *p;
    EFI_GUID    BootVarGuid = EFI_GLOBAL_VARIABLE;

    // Check for EFI Boot Variable.
    if (Data == NULL) {
        // Validate Boot Variable Name "BootXXXX"
        if (MemCmp((VOID*)Name, L"Boot", StrLen(L"Boot"))) return FALSE;
        if (guidcmp(Guid, &BootVarGuid)) return FALSE;
        if (StrLen(Name) != StrLen(L"BootXXXX")) return FALSE;
        for (p = Name + 4; p < (Name + 8); p++) {
            if (((*p >= L'0') && (*p <= L'9')) || ((*p >= L'A') && (*p <= L'F')))
                return TRUE;
        }
    } else {
        // Skip Attrib, Length and Description.
        for(p = (CHAR16*)Data + 3; *p != 0 ; p++);
        // if the device path is HDD + File , assume this BOOTxxxx is for EFI OS.
        if ((*(++p) == 0x0104) && (*(p + (*(p + 1) / 2)) == 0x0404)) return TRUE;
    }
    return FALSE;
}

/**
 * Procedure to preserve NVRAM Variables before re-flashing.
 *
 */
VOID PreserveVariables(VOID)
{
    UINTN       VarNameSize, VariableSize, ExtAuthHdrSize, Result;
    UINTN       MaxVarNameSize;
    CHAR16      *VarName = NULL, *OldVarName = NULL;
    UINT8       *VariableData, *pData, i, j;
    UINT32      VariableAttr;
    EFI_GUID    VarGuid;
    EFI_STATUS  Status;
    SAVED_VAR   *pLastVar = NULL;

    // Locate a big enough buffer for following process.
    VarNameSize = MaxVarNameSize = DEFAULT_VARIABLE_NAME_SIZE;
    Status = gSmst->SmmAllocatePool (
        EfiRuntimeServicesData,
        VarNameSize, (VOID**)&VarName
    );
    if(EFI_ERROR(Status)) return;

    // Set Show BootTime Variable flag for Searvhing Win8 Debug Variables.
    gSfAmiNvramControl = LocateNvramControlSmmProtocol();
    if (gSfAmiNvramControl) gSfAmiNvramControl->ShowBootTimeVariables(TRUE);

    // Get frist variable
    VarName[0] = 0;
    do{
        VarNameSize = MaxVarNameSize;
        Status = pRS->GetNextVariableName (&VarNameSize, VarName, &VarGuid);

        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            // Default Buffer is not enough, allocate new enough buffer.
            OldVarName = VarName;
            Status = gSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VarNameSize, (VOID**)&VarName);

            if(EFI_ERROR(Status)) {
                // Disabled Searching Boot Time Variables
                if (gSfAmiNvramControl) gSfAmiNvramControl->ShowBootTimeVariables(FALSE);
                return;
            }

            // Update last Variable Name to New Buffer for continuing search.
            MemCpy(VarName, OldVarName, MaxVarNameSize);

            // Free old working buffer and update Max Buffer size.
            gSmst->SmmFreePool(OldVarName);
            MaxVarNameSize = VarNameSize;
            continue;
        }
        if(!EFI_ERROR(Status))
        {
            // 1. Check By Fixed Save Variables list .
            for(i = 0, Result = (UINTN)-1, ExtAuthHdrSize = 0; \
                                gFixedSaveVarsList[i].Name != NULL; i++) {

                Result = MemCmp((VOID*)gFixedSaveVarsList[i].Name, \
                                                    (VOID*)VarName, VarNameSize);
                if (Result == 0) {
                    Result = guidcmp(&gFixedSaveVarsList[i].Guid, &VarGuid);
                    if (Result != 0) continue;
                    if (gFixedSaveVarsList[i].IsAuthVars == TRUE)
                        ExtAuthHdrSize = sizeof(AMI_EFI_VARIABLE_AUTHENTICATION_2);
                    break;
                }
            }

            // 2. Check By Save Guids list .
            if (Result != 0) {
                for(j = 0; gSmiFlashSaveGuidsList[j].Data1 !=  0; j++) {
                    Result = guidcmp(&gSmiFlashSaveGuidsList[j], &VarGuid);
                    if (Result == 0) break;
                }
            }
            if (Result != 0)
            {
#if PRESERVE_EFIBOOTORDER
                // Check the valid Boot Order Name "BootXXXX".
                if (!IsEfiBootVarsValid(VarName, &VarGuid, NULL))
#endif  //  #if PRESERVE_EFIBOOTORDER
                {
                    continue;
                }
            }

            VariableSize = 0;
            Status = pRS->GetVariable(VarName, &VarGuid,
                                      &VariableAttr, &VariableSize, NULL);

            if(Status != EFI_BUFFER_TOO_SMALL) continue;

            Status = gSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VariableSize + ExtAuthHdrSize, (VOID**)&VariableData);

            if(EFI_ERROR(Status)) continue;

            Status = pRS->GetVariable(VarName, &VarGuid, \
                            &VariableAttr, &VariableSize, \
                            VariableData + ExtAuthHdrSize);

            if(EFI_ERROR(Status))
            {
                gSmst->SmmFreePool(VariableData);
                continue;
            }

//-#if PRESERVE_EFIBOOTORDER
//-            // check the BootXXXX contains "Windows Boot Manager" for EFI OS.
//-            if (IsEfiBootVars == TRUE) {
//-                if (!IsEfiBootVarsValid(NULL, NULL, (VOID*)VariableData)) {
//-                    pSmst->SmmFreePool (VariableData);
//-                    continue;
//-                }
//-                // Reset "IsEfiBootVars" for next variable check.
//-                IsEfiBootVars = FALSE;
//-            }
//-#endif  // #if PRESERVE_EFIBOOTORDER

            // Store variable in Link list
            Status = gSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          sizeof(SAVED_VAR), (VOID**)&pData);

            if(EFI_ERROR(Status))
                continue;

            Status = gSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VarNameSize, (VOID**)&OldVarName);

            if(EFI_ERROR(Status))
                continue;

            MemCpy(OldVarName, VarName, VarNameSize);

            MemCpy(&((SAVED_VAR*)pData)->Guid, &VarGuid, sizeof(EFI_GUID));

            ((SAVED_VAR*)pData)->BootVarName = OldVarName;
            ((SAVED_VAR*)pData)->Attrib = VariableAttr;
            ((SAVED_VAR*)pData)->Size = VariableSize + ExtAuthHdrSize;
            ((SAVED_VAR*)pData)->Data = VariableData;
            ((SAVED_VAR*)pData)->NextData = NULL;

            if (gFixedSaveVarsList[i].Name != NULL) {
#if defined SecureBoot_SUPPORT && SecureBoot_SUPPORT == 1
#if defined SECURE_BOOT_MODULE_REVISION && SECURE_BOOT_MODULE_REVISION < 14
                // Saved variable pointer to FixedSavedVarsList table in order
                // to restore Secure Boot Variables by order (dbx->db->kek->pk).
                if (gFixedSaveVarsList[i].IsAuthVars == TRUE)
                    FillAuthHeader (VariableData);
#endif  // #if defined SECURE_BOOT_MODULE_REVISION && SECURE_BOOT_MODULE_REVISION < 14
#endif  // #if defined SecureBoot_SUPPORT && SecureBoot_SUPPORT == 1
                gFixedSaveVarsList[i].pVariable = (UINT8*)pData;
            }
            else
            {
                // Init Variable List
                if (gRestoreVarList == NULL) {
                    gRestoreVarList = (SAVED_VAR*)pData;
                    pLastVar = NULL;
                }
                if (pLastVar != NULL) pLastVar->NextData = (VOID*)pData;
                pLastVar = (SAVED_VAR*)pData;
            }
            // Reset ExtAuthHdrSize for next search..
            ExtAuthHdrSize = 0;
        }
        //If any other error, break for avoiding dead loop
        if(EFI_ERROR(Status)&&(Status!=EFI_BUFFER_TOO_SMALL))
            break;

    }while(Status != EFI_NOT_FOUND);
    // Disabled Searching Boot Time Variables
    if (gSfAmiNvramControl) gSfAmiNvramControl->ShowBootTimeVariables(FALSE);
    gSmst->SmmFreePool(VarName);
}

/**
 * Procedure to restore the preserved Variables after re-flashing.
 *
 */
VOID RestoreVariables (VOID)
{
    SAVED_VAR   *TempPoint;
    UINTN       Index = 0;

    if (gSfAmiNvramControl) gSfAmiNvramControl->ShowBootTimeVariables(TRUE);
    while ((gFixedSaveVarsList[Index].Name != NULL) || (gRestoreVarList != NULL)) {

        // In order to restore Secure Boot Variables by order (dbx->db->kek->pk).
        if (gFixedSaveVarsList[Index].Name != NULL) {
            if (gFixedSaveVarsList[Index].pVariable == NULL) {Index++; continue;}
            TempPoint = (SAVED_VAR*)gFixedSaveVarsList[Index].pVariable;
            gFixedSaveVarsList[Index++].pVariable = NULL;
        } else if (gRestoreVarList != NULL) {
            TempPoint = gRestoreVarList;
            gRestoreVarList = TempPoint->NextData;
        } else return;          // This condition should not happen.

/*      **** System hangs if use GetVariable call, Mark out for now. ****

        // Allocate memory for read variable back before update.
        VariableSize = TempPoint->Size;
        Status = pSmst->SmmAllocatePool (EfiRuntimeServicesData,
                                              VariableSize, &VariableData);
        if (!EFI_ERROR(Status)) {
            // Read variable back before update.
            Status = pRS->GetVariable (  TempPoint->BootVarName,
                                         &TempPoint->Guid,
                                         NULL,
                                         &VariableSize,
                                         &VariableData );
            if (!EFI_ERROR(Status) && (VariableSize == sizeof(AMITSESETUP))) {
                // check for skip update if variable contents not changed.
                if (MemCmp(VariableData, TempPoint->Data, VariableSize))
                    Status = EFI_NOT_FOUND;
            }
            // Free read variable memory
            pSmst->SmmFreePool(VariableData);
        }
        if (Status == EFI_NOT_FOUND)
        **** System hangs if use GetVariable call, Mark out for now. *****/
        {
#if PRESERVE_PASSWORDS
            // Restore SilentBoot to Default setting if AMITSE Setup variable.
            if (!MemCmp((VOID*)TempPoint->BootVarName, \
                            L"AMITSESetup", StrLen(L"AMITSESetup"))) {
                ((AMITSESETUP*)TempPoint->Data)->AMISilentBoot = DEFAULT_QUIET_BOOT;
            }
#endif  // #if PRESERVE_PASSWORDS

            pRS->SetVariable (TempPoint->BootVarName, &TempPoint->Guid, \
                        TempPoint->Attrib, TempPoint->Size, TempPoint->Data );
        }
        gSmst->SmmFreePool(TempPoint->BootVarName);
        gSmst->SmmFreePool(TempPoint->Data);
        gSmst->SmmFreePool(TempPoint);
    }
    if (gSfAmiNvramControl) gSfAmiNvramControl->ShowBootTimeVariables(FALSE);
}

/**
 * Procedure to re-enable the BIOS Write Enable bit before Write/Erase procedures
 * if BIOS_LOCK_ENABLE is set.
 *
 */
VOID
BiosLockEnablePatchHook (
    IN      UINT8   SwSmiNum,
    IN  OUT UINT64  Buffer
)
{
 /*   if ((SwSmiNum != 0x22) && (SwSmiNum != 0x23))return;
    ChipsetFlashDeviceWriteEnable ();*/
}

/**
 * Procedure to Disable Power Button while flashing.
 *
 */
VOID DisablePowerButton(VOID)
{
    // Disable PWR Button SMI
    IoWrite16(PM_BASE_ADDRESS + 0x02, IoRead16(PM_BASE_ADDRESS + 0x02) & 0xFEDF);
}

/**
 * Procedure to Enable Power Button after flashing.
 *
 */
VOID EnablePowerButton (VOID)
{
    //Clear All PM  Statuses
    IoWrite16(PM_BASE_ADDRESS,IoRead16(PM_BASE_ADDRESS));
    // Re-ensable PWR Button SMI
    IoWrite16(PM_BASE_ADDRESS + 0x02, BIT05 + BIT08);
}

/**
    Procedure to Wait till KBC I/P buffer is free..

    @retval EFI_SUCCESS KBC I/P buffer is free.
    @retval EFI_TIMEOUT Wait for KBC I/P buffer free is Timeout.
    @retval EFI_NO_RESPONSE KBC is not supproted.
**/
static
EFI_STATUS
KbcIbFree(
    VOID
)
{
#if defined(KBC_SUPPORT) && (KBC_SUPPORT == 0)
    return EFI_NO_RESPONSE;
#else
    UINT32  Index;

    if( (IoRead8( 0x64 ) == 0xFF) )
        return EFI_NO_RESPONSE;

    for( Index = 0; Index < 0x100000; Index++ )
    {
        if( (IoRead8( 0x64 ) & BIT01) == 0 )
            return EFI_SUCCESS;
    }

    return EFI_TIMEOUT;
#endif
}

/**
 * Procedure to Disable USB Keyboard while flashing.
 *
 */
VOID DisableUSBKBD(VOID)
{
    EFI_STATUS Status;
#if AMIUSB_SUPPORT == 1
#if USB_DRIVER_MAJOR_VER >= 10
    AMI_USB_SMM_PROTOCOL    *UsbSmmProtocol = NULL;
    URP_STRUC               UrpStruc;
    Status = gSmst->SmmLocateProtocol(&gAmiUsbSmmProtocolGuid, NULL, (VOID**)&UsbSmmProtocol);
    if (EFI_ERROR(Status)) return;
    // USBAPI_KbcAccessControl is the 17th API_FUNC in UsbApiTable.
    UrpStruc.ApiData.KbcControlCode = 1;
    gUsbRtKbcAccessControl = (API_FUNC)UsbSmmProtocol->UsbApiTable[17];
    if (gUsbRtKbcAccessControl != NULL) gUsbRtKbcAccessControl(&UrpStruc);
#else
    UINTN    VariableSize = sizeof(UINTN);
    EFI_GUID AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    Status = pRS->GetVariable (L"USB_POINT", \
                &AmiGlobalVariableGuid, NULL, &VariableSize, &gUsbRtKbcAccessControl);
    if (EFI_ERROR(Status)) return;
    // Directly invoke th UsbRtKbcAccessContol avoiding to call outside SMM.
    if (gUsbRtKbcAccessControl != NULL) gUsbRtKbcAccessControl(1);
#endif
#endif

    // Disable KBC.
#if defined EMUL6064_SUPPORT && (EMUL6064_SUPPORT == 1)
    Status = gSmst->SmmLocateProtocol(&gEmul6064TrapProtocolGuid, NULL, &gEmulationTrap);
    if (!EFI_ERROR(Status)) {
#if defined KBCEMULATION_DRIVER_VERSION && (KBCEMULATION_DRIVER_VERSION >= 4)
        if (!gEmulationTrap->GetTrapStatus(gEmulationTrap)) gEmulationTrap = NULL;
#endif
        if (gEmulationTrap) gEmulationTrap->TrapDisable(gEmulationTrap);
    } else gEmulationTrap = NULL;
#endif
    Status = KbcIbFree();
    if (!EFI_ERROR(Status)) IoWrite8(0x64, 0xad);
}


/**
 * Procedure to Re-enable USB Keyboard after flashing.
 *
 */
VOID EnableUSBKBD (VOID)
{
    // Enable KBC.
    if (!EFI_ERROR(KbcIbFree())) IoWrite8(0x64, 0xae);
#if defined EMUL6064_SUPPORT && (EMUL6064_SUPPORT == 1)
    if (gEmulationTrap) gEmulationTrap->TrapEnable(gEmulationTrap);
#endif
#if AMIUSB_SUPPORT == 1
{
#if USB_DRIVER_MAJOR_VER >= 10
    URP_STRUC   UrpStruc;
    UrpStruc.ApiData.KbcControlCode = 0;
    if (gUsbRtKbcAccessControl != NULL) gUsbRtKbcAccessControl(&UrpStruc);
#else
    if (gUsbRtKbcAccessControl != NULL) gUsbRtKbcAccessControl(0);
#endif
}
#endif
}

#else // #if defined _OUTSIDE_SMM_
//*********** OUTSIDE SMM ***********************************************
#include <Protocol/MmCommunication.h>

#include <Protocol/AmiSmiFlash.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

extern AMI_FLASH_PROTOCOL *Flash;

#if defined(RECOVERY_PRESERVE_VARS_IN_SMM) && (RECOVERY_PRESERVE_VARS_IN_SMM == 1)

//50EE27A5-98CD-4F2E-914D-AA399B1D3D71
#define SMIFLASH_COMMUNICATE_GUID \
    { \
        0x50EE27A5, 0x98CD, 0x4F2E, { 0x91, 0x4D, 0xAA, 0x39, 0x9B, 0x1D, 0x3D, 0x71 } \
    }

/**
    Procedure to preserve variable in SMM before BIOS recovery.
**/
VOID
ReflashBeforeUpdateHook(
    VOID
)
{
    EFI_STATUS                      Status;
    EFI_MM_COMMUNICATION_PROTOCOL   *MmCommunicate;
    UINTN                           VarSize;
    EFI_GUID                        AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    EFI_MM_COMMUNICATE_HEADER       *MmCommHeader;
    UINTN                           MmCommSize;
    EFI_GUID                        SmiFlashCommunicateGuid = SMIFLASH_COMMUNICATE_GUID;

    Status = gBS->LocateProtocol(
                    &gEfiMmCommunicationProtocolGuid,
                    NULL,
                    (VOID**)&MmCommunicate );
    if( !EFI_ERROR(Status) )
    {
        VarSize = sizeof(VOID*);
        Status = gRT->GetVariable(
                        L"SFPFREC",
                        &AmiGlobalVariableGuid,
                        NULL,
                        &VarSize,
                        (VOID*)&MmCommHeader);
        if( !EFI_ERROR(Status) )
        {
            MmCommSize = sizeof(EFI_MM_COMMUNICATE_HEADER);
            SetMem( (VOID*)MmCommHeader, MmCommSize, 0 );
            CopyGuid( &MmCommHeader->HeaderGuid, &SmiFlashCommunicateGuid );
            MmCommHeader->MessageLength = MmCommSize;
            MmCommHeader->Data[0] = (UINT8)AMI_SMI_FLASH_ENABLE_FLASH_SMI;

            MmCommunicate->Communicate( MmCommunicate, (VOID*)MmCommHeader, &MmCommSize );
        }
    }

#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    // For following DeviceWriteEnable call of reflash.c.
    Flash->DeviceWriteDisable();
#endif
}

/**
    Procedure to restores variables from SMM after BIOS recovery.
**/
VOID
ReflashAfterUpdateHook(
    VOID
)
{
    EFI_STATUS                      Status;
    EFI_MM_COMMUNICATION_PROTOCOL   *MmCommunicate;
    UINTN                           VarSize;
    EFI_GUID                        AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
    EFI_MM_COMMUNICATE_HEADER       *MmCommHeader;
    UINTN                           MmCommSize;
    EFI_GUID                        SmiFlashCommunicateGuid = SMIFLASH_COMMUNICATE_GUID;

#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    // For following DeviceWriteDisable call of smiflash func#24.
    Flash->DeviceWriteEnable();
#endif

    Status = gBS->LocateProtocol(
                    &gEfiMmCommunicationProtocolGuid,
                    NULL,
                    (VOID**)&MmCommunicate );
    if( !EFI_ERROR(Status) )
    {
        VarSize = sizeof(VOID*);
        Status = gRT->GetVariable(
                        L"SFPFREC",
                        &AmiGlobalVariableGuid,
                        NULL,
                        &VarSize,
                        (VOID*)&MmCommHeader);
        if( !EFI_ERROR(Status) )
        {
            MmCommSize = sizeof(EFI_MM_COMMUNICATE_HEADER);
            SetMem( (VOID*)MmCommHeader, MmCommSize, 0 );
            CopyGuid( &MmCommHeader->HeaderGuid, &SmiFlashCommunicateGuid );
            MmCommHeader->MessageLength = MmCommSize;
            MmCommHeader->Data[0] = (UINT8)AMI_SMI_FLASH_DISABLE_FLASH_SMI;

            MmCommunicate->Communicate( MmCommunicate, (VOID*)MmCommHeader, &MmCommSize );
        }
    }
}
#endif // if defined RECOVERY_PRESERVE_IN_SMM && RECOVERY_PRESERVE_IN_SMM == 1
#endif // if defined _OUTSIDE_SMM_