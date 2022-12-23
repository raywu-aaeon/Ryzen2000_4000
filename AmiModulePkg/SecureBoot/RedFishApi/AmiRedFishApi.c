//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Library/DxeServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>

#include <SecureBoot.h>
#include <AmiRedFishApi.h>
#include <AmiSecureBootLib.h>

//----------------------------------------------------------------------------
// Function forward declaration
//----------------------------------------------------------------------------

// Delete the content of all UEFI Secure Boot key databases (PK, KEK, DB, DBX). This puts the system in Setup Mode
EFI_STATUS EFIAPI DeleteAllKeys (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
);
// Reset the content of all UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) to factory default values
EFI_STATUS EFIAPI ResetAllKeysToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
);
// Delete the content of the PK UEFI Secure Boot database. This puts the system in Setup Mode.
EFI_STATUS EFIAPI DeletePK (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
);
// Current Secure Boot Mode.
EFI_STATUS EFIAPI SecureBootMode(
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN OUT UINT8 *SecureBootModeType
);
//Secure Boot state during the current boot cycle.
EFI_STATUS EFIAPI SecureBootCurrentBoot (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN OUT UINT8 *SecureBootState
);
// Enable or disable UEFI Secure Boot (takes effect on next boot).
// Setting this property to true enables UEFI Secure Boot, and 
// setting it to false disables it. This property can be enabled only in UEFI boot mode.
EFI_STATUS EFIAPI SetSecureBootEnable (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN BOOLEAN Enable
);    
//Return Secure Boot Setup enable status
EFI_STATUS EFIAPI GetSecureBootEnable (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN OUT UINT8 *SecureBootEnable
);
//Check if a UEFI Secure Boot key database (PK, KEK, DB, DBX,..) is set to factory defaults
EFI_STATUS EFIAPI TestKeyToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN CHAR16* VariableName OPTIONAL
);
//Check if all UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) are set to factory default values
EFI_STATUS EFIAPI TestAllKeysToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
);
// Get SecureBoot Variable data in EFI_SIGNATURE_LIST format
// PK,KEK,db,dbx,...,PKDefault,KEKDefault,dbDefault,dbxDefault,...
EFI_STATUS EFIAPI GetVarEsl (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName,
  IN OUT UINT8       **SignatureList,
  IN OUT UINTN        *Size
);
// Set SecureBoot Variable data provided in EFI_SIGNATURE_LIST format.
// PK,KEK,db,dbx,...
EFI_STATUS EFIAPI SetVarEsl (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName,
  IN UINT8           *SignatureList,
  IN UINTN           Size
);
// Delete one of UEFI Secure Boot key databases (PK, KEK, DB, DBX,..)
EFI_STATUS EFIAPI DeleteVar (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName
);
// Reset the content of one of UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) to factory default values
EFI_STATUS EFIAPI ResetVarToDefault (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName
);
//----------------------------------------------------------------------------
// Protocol Identifiers
//----------------------------------------------------------------------------
AMI_REDFISH_SECBOOT_PROTOCOL mRedfishSecbootAPI = {
  0x10040301,
  DeleteAllKeys,
  ResetAllKeysToDefault,
  DeletePK,
  SecureBootMode,
  SecureBootCurrentBoot,
  SetSecureBootEnable,
  // added in v0101
  GetSecureBootEnable,
  // added in v0201
  TestAllKeysToDefault,
  // added in v0301
  GetVarEsl,
  SetVarEsl,
  // added in v0401
  TestKeyToDefault,
  DeleteVar,
  ResetVarToDefault
};
//----------------------------------------------------------------------------
// Auxiliary functions
//----------------------------------------------------------------------------
static SECURE_BOOT_SETUP_VAR SecureBootSetup;
static EFI_GUID guidSecurity = SECURITY_FORM_SET_GUID;

/**
  Allow un-signed secure boot variable changes by setting SecureBootMode to Custom
  The un-signed variable update is operational if invoked in Efi pre-boot with physical or authenticated user detected

  @param[in]  State of SecureBootMode variable

  @retval     Status
**/
static EFI_STATUS
SecureBootCustom (
    IN OUT UINT8    *NewState
    )
{
    EFI_STATUS  Status;
    UINTN       Size;
    UINT32      Attributes;
    UINT8       OrgState;

    if(NewState == NULL)
       return EFI_INVALID_PARAMETER;

    Size = sizeof(SECURE_BOOT_SETUP_VAR);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, &Attributes, &Size, &SecureBootSetup);
    DEBUG((SecureBoot_DEBUG_LEVEL,"SecureBootMode %d -> %d, %r\n", SecureBootSetup.SecureBootMode, *NewState, Status));
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    if(SecureBootSetup.SecureBootMode == *NewState)
        return Status;

    // Toggle SecureBootMode to Custom or restore Standard
    OrgState = SecureBootSetup.SecureBootMode;
    SecureBootSetup.SecureBootMode = *NewState;
    Status = pRS->SetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, Attributes, Size, &SecureBootSetup);
    // return original state
    *NewState = OrgState;

    return Status;
}
/**
  Provisioning of factory default Secure Boot policy Variables
  Install EFI Variables: PK, KEK, db, dbx, ...

  @param[in]  InstallVars Supported Types: RESET_NV_KEYS & SET_NV_DEFAULT_KEYS

  @retval     Status
**/
static EFI_STATUS
InstallSecureBootDefaults (
    UINT16    InstallVars
    )
{
    EFI_STATUS  Status;
    UINT8       Custom = SECURE_BOOT_MODE_CUSTOM;

    //Unlock Secure Boot variable update by setting SecureBootMode to Custom
    SecureBootCustom(&Custom);
    Status = AmiInstallSecureBootDefaults (InstallVars);
    SecureBootCustom(&Custom);

    return Status;
}
/**
  Set/Delete Secure Boot policy Variables: PK, KEK, db, dbx, ...

  @param[in]  Action - Supported Types:
                SET_SECURE_VARIABLE_DEL 1
                SET_SECURE_VARIABLE_SET 2
                SET_SECURE_VARIABLE_APPEND 8
                SET_SECURE_VARIABLE_SET_RT 4

  @param[in]  SecureVariableName - EFI Variable name
  @param[in]  SecureVariableNameDefault - EFI Variable name for Default version
  @param[in]  SecureVariableGuid - Efi Variable GUID
  @param[in]  pVarBuffer - Variable data buffer
  @param[in]  VarSize - Variable data size
  @param[in]  OPTIONAL - indicator that the parameter is optional

  @retval     Status
**/
static EFI_STATUS
SetSecureBootVariable(
    IN UINT16   Action,
    IN CHAR16   *SecureVariableName,
    IN CHAR16   *SecureVariableNameDefault OPTIONAL,
    IN EFI_GUID *SecureVariableGuid,
    IN UINT8    *pVarBuffer,
    IN UINTN    VarSize
){
    EFI_STATUS  Status;
    UINT8       Custom = SECURE_BOOT_MODE_CUSTOM;

    //Unlock Secure Boot variable update by setting SecureBootMode to Custom
    SecureBootCustom(&Custom);
    Status = AmiSetSecureBootVariable(Action,SecureVariableName, SecureVariableNameDefault, SecureVariableGuid, pVarBuffer, VarSize);
    SecureBootCustom(&Custom);

    return Status;
}
//----------------------------------------------------------------------------
// Protocol Implementation
//----------------------------------------------------------------------------
/**
  Enable or disable UEFI Secure Boot (takes effect on next boot).

  @param[in]  Enable 

  @retval     Status
**/
EFI_STATUS EFIAPI
SetSecureBootEnable(
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN BOOLEAN Enable
    )
{
    EFI_STATUS  Status;
    UINTN       Size;
    UINT32      Attributes;

    Size = sizeof(SECURE_BOOT_SETUP_VAR);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, &Attributes, &Size, &SecureBootSetup);
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;
    SecureBootSetup.SecureBootSupport = Enable;
    Status = pRS->SetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, Attributes, Size, &SecureBootSetup);
//    DEBUG((SecureBoot_DEBUG_LEVEL,"Update %s Var %r\n", AMI_SECURE_BOOT_SETUP_VAR, Status));

    return Status;
}
/**
  Secure Boot state during the current boot cycle.

  @retval     SecureBootState
  @retval     Status
**/
EFI_STATUS EFIAPI
GetSecureBootEnable( 
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    UINT8 *SecureBootEnable
    )
{
    EFI_STATUS  Status;
    UINTN       Size;

    if(SecureBootEnable==NULL)
        return EFI_INVALID_PARAMETER;

    Size = sizeof(SECURE_BOOT_SETUP_VAR);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, NULL, &Size, &SecureBootSetup);
    if(!EFI_ERROR(Status)) {
        *SecureBootEnable = SecureBootSetup.SecureBootSupport;
    }

    return Status;
}

/**
  Secure Boot state during the current boot cycle.

  @retval     SecureBootState
  @retval     Status
**/
EFI_STATUS EFIAPI
SecureBootCurrentBoot( 
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    UINT8 *SecureBootState
    )
{
    UINTN       Size;

    if(SecureBootState==NULL)
        return EFI_INVALID_PARAMETER;

    Size = sizeof(UINT8);
    return pRS->GetVariable(EFI_SECURE_BOOT_NAME, &gEfiGlobalVariableGuid, NULL, &Size, SecureBootState);
}

/**
  Return Current Secure Boot Mode.

  SetupMode    0 Secure Boot is currently in Setup Mode
  UserMode     1 Secure Boot is currently in User Mode
  AuditMode    2 Secure Boot is currently in Audit Mode
  DeployedMode 3 Secure Boot is currently in Deployed Mode

  @retval     SecureBootModeType
  @retval     Status
**/
EFI_STATUS EFIAPI
SecureBootMode( 
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN OUT UINT8 *SecureBootModeType
    )
{
    EFI_STATUS  Status;
    UINTN       Size;
    UINT8       SetupMode, AuditMode, DeployedMode;

    if(SecureBootModeType==NULL)
        return EFI_INVALID_PARAMETER;

    Size = sizeof(UINT8);
    Status = pRS->GetVariable(EFI_SETUP_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &SetupMode);
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    // User=1/Setup=0
    *SecureBootModeType = (UINT8)((SetupMode==1)?AmiRfSetupMode:AmiRfUserMode);

    // Update Audit/Deployed Vars
    Size = sizeof(UINT8);
    if(EFI_ERROR(pRS->GetVariable(EFI_AUDIT_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &AuditMode)))
        return Status;

    Size = sizeof(UINT8);
    if(EFI_ERROR(pRS->GetVariable(EFI_DEPLOYED_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &DeployedMode)))
        return Status; // User/Setup

    if(AuditMode) {
        *SecureBootModeType = (UINT8)AmiRfAuditMode;
    }
    else
        if(DeployedMode) {
            *SecureBootModeType = (UINT8)AmiRfDeployedMode;
        }

    return Status;
}

/**
  Delete the content of the PK UEFI Secure Boot database. This puts the system in Setup Mode.

  @retval     Status
**/
EFI_STATUS EFIAPI
DeletePK(
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
    )
{
    EFI_STATUS Status;
    // try to erase. should succeed if system in pre-boot and physical user authenticated mode
    Status = SetSecureBootVariable(SET_SECURE_VARIABLE_DEL, SecureVariableFileName[PkVar], NULL, &gEfiGlobalVariableGuid, NULL, 0 );
    DEBUG((SecureBoot_DEBUG_LEVEL,"Del Var %s, Status %r\n",SecureVariableFileName[PkVar], Status));
    return Status;
}

/**
  Delete the content of all UEFI Secure Boot key databases (PK, KEK, DB, DBX,..). This puts the system in Setup Mode

  @retval     Status
**/
EFI_STATUS EFIAPI
DeleteAllKeys(
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
    )
{
    return InstallSecureBootDefaults(RESET_NV_KEYS);    // erase
}

/**
  Reset the content of all UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) to factory default values

  @retval     Status
**/
EFI_STATUS EFIAPI
ResetAllKeysToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
    )
{
    InstallSecureBootDefaults(RESET_NV_KEYS); // erase all secure boot NV variables before installing selected defaults
    return InstallSecureBootDefaults(SET_NV_DEFAULT_KEYS);
}

//---------------------
// v0301
//---------------------
/**
  Check if a UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) 
  is set to factory defaults

  @retval     Status
  EFI_SUCCESS    Only default keys are installed
  EFI_NOT_READY  Not all keys are Default
  EFI_NOT_FOUND  No keys are installed
**/
EFI_STATUS EFIAPI
TestKeyToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
    IN CHAR16* VariableName OPTIONAL
    )
{
    EFI_STATUS Status;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;
    UINTN       Size1, Size2;
    UINT8       *Buf1, *Buf2;
    BOOLEAN     bVendor;     // Vendor keys

    Status = EFI_NOT_FOUND;
    Index = 0;
    bVendor = TRUE;
    while(bVendor == TRUE && SecureVariableFileName[Index] != NULL)
    {
        if(VariableName != NULL && StrCmp(SecureVariableFileName[Index],VariableName)) {
            Index++;
            continue;
        }

        if(Index < SecureVariableSigDatabaseCount)
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;

        Size1 = 0;
        //get Default Key from Volatile key var (use NV Key size)
        Status = pRS->GetVariable( SecureVariableFileNameDefault[Index], &gEfiGlobalVariableGuid, NULL, &Size1, NULL);
        DEBUG((SecureBoot_DEBUG_LEVEL,"%d:%s(%Xh),  status=%r\n",  Index, SecureVariableFileNameDefault[Index], Size1, Status));
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Buf1 = NULL;
            Buf1 = (UINT8*)AllocateZeroPool(Size1);
            if(Buf1 == NULL) 
                return EFI_OUT_OF_RESOURCES;

            Status = pRS->GetVariable( SecureVariableFileNameDefault[Index], &gEfiGlobalVariableGuid, NULL, &Size1, Buf1);
            DEBUG((SecureBoot_DEBUG_LEVEL,"  %s(%Xh),  status=%r\n", SecureVariableFileNameDefault[Index], Size1, Status));
            if(!EFI_ERROR(Status)) {
                Buf2 = NULL;
                Size2 = Size1;
                Buf2 = (UINT8*)AllocateZeroPool(Size2);
                if(Buf2 == NULL) {
                    FreePool(Buf1);
                    return EFI_OUT_OF_RESOURCES;
                }

                //get Key from NV
                Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &Size2, Buf2);
                DEBUG((SecureBoot_DEBUG_LEVEL,"  %s(%Xh),  status=%r\n\n", SecureVariableFileName[Index], Size2, Status));
                if(EFI_ERROR(Status) ||
                   Size1 != Size2 || 
                   MemCmp(Buf1, Buf2, Size1)
                   ) {
                    bVendor = FALSE;
                }
                FreePool(Buf2);
            }
            FreePool(Buf1);
        } else {
            // Default Key does not exist but NV key may be installed
            Size1 = 0;
            //get Key from NV
            Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &Size1, NULL);
            DEBUG((SecureBoot_DEBUG_LEVEL,"  %s(%Xh),  status=%r\n\n", SecureVariableFileName[Index], Size1, Status));
            if(Status == EFI_BUFFER_TOO_SMALL) {
                bVendor = FALSE;
            }
        }
        if(VariableName != NULL)
            break;

        Index++;
   }
   // No Keys are installed
   DEBUG((SecureBoot_DEBUG_LEVEL,"bVendor %d, Index %d-%d, %r\n", bVendor, Index, MaxVarCount, Status));
   if(bVendor && Index == MaxVarCount && Status == EFI_NOT_FOUND) // last default
       return EFI_NOT_FOUND;

   return (bVendor)?EFI_SUCCESS:EFI_NOT_READY;
}
/**
  Check if all UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) are set to factory default values

  @retval     Status
  EFI_SUCCESS    Only default keys are installed
  EFI_NOT_READY  Not all keys are Default
  EFI_NOT_FOUND  No keys are installed
**/
EFI_STATUS EFIAPI
TestAllKeysToDefault (
    IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This
    )
{
    return TestKeyToDefault(This, NULL);
}
//---------------------
// v0301
//---------------------
/**
  Get Secure Boot key databases (PK, KEK, DB, DBX,...,PKdefault,...) in EFI_SIGNATURE_LIST format
  @param[in]  VariableName
  @param[out]  SignatureList
  @param[out]  SignatureListSize

  @retval     Status
  EFI_SUCCESS    Variable content returned successfully
  EFI_NOT_FOUND  Variable is not installed
**/
EFI_STATUS EFIAPI 
GetVarEsl (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName,
  IN OUT UINT8      **SignatureList,
  IN OUT UINTN       *SignatureListSize
) {
    EFI_STATUS Status;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;
    UINT8       *Buf;
    UINTN       Size;

    if(SignatureList == NULL || SignatureListSize == NULL )
        return EFI_INVALID_PARAMETER;

    Status = EFI_NOT_FOUND;
    Index = 0;
    while(SecureVariableFileName[Index] != NULL)
    {
        if(!StrCmp(SecureVariableFileName[Index],VariableName) || 
           !StrCmp(SecureVariableFileNameDefault[Index],VariableName)
        ){
            if(Index < SecureVariableSigDatabaseCount && !StrCmp(SecureVariableFileName[Index],VariableName))
                EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
            else
                EfiVarGuid = &gEfiGlobalVariableGuid;

            Size = 0;
            Status = pRS->GetVariable( VariableName, EfiVarGuid, NULL, &Size, NULL);
            DEBUG((SecureBoot_DEBUG_LEVEL,"%d:%s(sz %X) %r\n",  Index, VariableName, Size, Status));
            if(Status == EFI_BUFFER_TOO_SMALL) {
                Buf = NULL;
                Buf = (UINT8*)AllocateZeroPool(Size);
                if(Buf == NULL) 
                    return EFI_OUT_OF_RESOURCES;

                Status = pRS->GetVariable( VariableName, EfiVarGuid, NULL, &Size, Buf);
                DEBUG((SecureBoot_DEBUG_LEVEL,"  %s(sz %X) %r\n", VariableName, Size, Status));
                if(!EFI_ERROR(Status)) {
                    *SignatureList = Buf;
                    *SignatureListSize = Size;
                } else
                    FreePool(Buf);
            }
            break;
        }
        Index++;
    }
    DEBUG((SecureBoot_DEBUG_LEVEL,"GetVar %s Index %d(%d), %r\n", VariableName, Index, MaxVarCount, Status));
    if(Index == MaxVarCount || Status == EFI_NOT_FOUND) // last
        return EFI_NOT_FOUND;

    return Status;
}

// Set SecureBoot Variable data provided in EFI_SIGNATURE_LIST format
/**
  Set Secure Boot key databases (PK, KEK, DB, DBX,...)
  SecureBoot Variable data provided in EFI_SIGNATURE_LIST format

  @param[in]  VariableName
  @param[in]  SignatureList
  @param[in]  SignatureListSize

  @retval     Status
  EFI_SUCCESS    Variable content returned successfully
  EFI_NOT_FOUND  Variable is not installed
**/
EFI_STATUS EFIAPI 
SetVarEsl (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName,
  IN UINT8           *SignatureList,
  IN UINTN           SignatureListSize
) {
    EFI_STATUS  Status;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;
    UINT8* VarData = NULL;
    UINTN  VarSize, HdrSize;

    if(SignatureList == NULL || !SignatureListSize )
        return EFI_INVALID_PARAMETER;

    Status = EFI_NOT_FOUND;
    Index = 0;

    // Validate Signature List integrity 
    if(EFI_ERROR(AmiValidateSignatureList (SignatureList, SignatureListSize, NULL, NULL)))
        return EFI_INVALID_PARAMETER;

    HdrSize = sizeof(AMI_EFI_VARIABLE_AUTHENTICATION_2);
    //
    // Construct Efi AuthVar2 Hdr on top of a SigList payload
    //
    //Allocate new Size
    VarSize = HdrSize+SignatureListSize; 
    VarData = (UINT8*)AllocateZeroPool(VarSize);
    if(VarData == NULL) 
        return EFI_OUT_OF_RESOURCES;

    // Append AuthHdr to Var data.
    AmiFillAuthenticatedHdr2(VarData, SET_SECURE_VARIABLE_SET);
    MemCpy ((VOID*)((UINTN)VarData+HdrSize), SignatureList, SignatureListSize);

    while(SecureVariableFileName[Index] != NULL)
    {
        if(!StrCmp(SecureVariableFileName[Index],VariableName)
        ){
            if(Index < SecureVariableSigDatabaseCount)
                EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
            else
                EfiVarGuid = &gEfiGlobalVariableGuid;

            Status = SetSecureBootVariable(SET_SECURE_VARIABLE_SET,VariableName, NULL, EfiVarGuid, VarData, VarSize );
            break;
        }
        Index++;
    }

   if(VarData)
       FreePool(VarData);

    DEBUG((SecureBoot_DEBUG_LEVEL,"SetVar %s Index %d(%d), %r\n", VariableName, Index, MaxVarCount, Status));
    if(Index == MaxVarCount || Status == EFI_NOT_FOUND) // last default
        return EFI_NOT_FOUND;

    return Status;
}
/**
  Delete one of UEFI Secure Boot key databases (PK, KEK, DB, DBX,..)

  @param[in]  VariableName

  @retval     Status
  EFI_SUCCESS    Operation completed successfully
  EFI_NOT_FOUND  Operation failed
**/
EFI_STATUS EFIAPI 
DeleteVar (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName
){
    EFI_STATUS  Status;
    UINT8       Custom = SECURE_BOOT_MODE_CUSTOM;

    //Unlock Secure Boot variable update by setting SecureBootMode to Custom
    SecureBootCustom(&Custom);
    Status = AmiUpdateSecureBootVariable(RESET_NV_KEYS,VariableName);
    SecureBootCustom(&Custom);

    return Status;
}

/**
  Reset the content of one of UEFI Secure Boot key databases (PK, KEK, DB, DBX,..) to factory default values

  @param[in]  VariableName

  @retval     Status
  EFI_SUCCESS    Operation completed successfully
  EFI_NOT_FOUND  Operation failed
**/
EFI_STATUS 
EFIAPI ResetVarToDefault (
  IN CONST AMI_REDFISH_SECBOOT_PROTOCOL *This,
  IN CHAR16          *VariableName
){
    EFI_STATUS  Status;
    UINT8       Custom = SECURE_BOOT_MODE_CUSTOM;

    //Unlock Secure Boot variable update by setting SecureBootMode to Custom
    SecureBootCustom(&Custom);
    Status = AmiUpdateSecureBootVariable(RESET_NV_KEYS | SET_NV_DEFAULT_KEYS, VariableName);
    SecureBootCustom(&Custom);

    return Status;
}
////////////////////////////////////////////////////////////////////////////////////////
/**
  Entry point of RedFish Secure Boot DXE driver
  @param[in]  EFI_HANDLE 
  @param[in]  EFI_SYSTEM_TABLE 
  
  @retval     Status
**/
EFI_STATUS EFIAPI 
RedFishApi_Init (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
    )
{
    EFI_HANDLE Handle;

    InitAmiLib(ImageHandle, SystemTable);

    Handle = NULL;

    mRedfishSecbootAPI.Version = AmiRedFishApi_VERSION; // 0x01040401
/*
 0-15 - Protocol version
      0- 7  Min version
      8-15  Major
 16-31 - Compatible RedFish SecBoot resource spec version:01.04
 
New in Protocol ver 01.01: Add GetSecureBootEnable;
New in ver 02.01: Add TestAllKeysToDefault;
New in ver 03.01: Add GetVarEsl; SetVarEsl;
New in ver 03.02: API Caller no longer needs to set SecureBootMode to Custom on each call
New in ver 04.01; Add DellVar, ResetVarToDefault,TestkeyToDefault
*/
    return pBS->InstallMultipleProtocolInterfaces (
                    &Handle,
                    &gAmiRedFishSecBootApiGuid,
                    &mRedfishSecbootAPI,
                    NULL
                    );
}
