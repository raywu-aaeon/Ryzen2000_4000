//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TcgNext/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.c 2     10/09/13 6:32p Fredericko $
//
// $Revision: 2 $
//
// $Date: 10/09/13 6:32p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TcgNext/Common/Tpm20PlatformDxe/Tpm20PlatformDxe.c $
//
// 2     10/09/13 6:32p Fredericko
//
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
//
// 5     10/03/13 2:52p Fredericko
//
// 4     9/16/13 1:37p Fredericko
// TPM 2.0 UEFI preboot fixes.
//
// 3     8/30/13 11:03p Fredericko
//
// 2     7/11/13 6:16p Fredericko
// [TAG]        EIP120969
// [Category]   New Feature
// [Description]    TCG (TPM20).
//
// 1     7/10/13 5:57p Fredericko
// [TAG]        EIP120969
// [Category]   New Feature
// [Description]    TCG (TPM20)
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************
#include "Tpm20PlatformDxe.h"
#include <IndustryStandard/SmBios.h>
#include <IndustryStandard/PeImage.h>
#include <Uefi.h>
#include <Guid/ImageAuthentication.h>
#include <Guid/GlobalVariable.h>
#include <IndustryStandard/PeImage.h>
#include <AmiTcg/TrEEProtocol.h>
#include <AmiTcg/tcg.h>
#include <Protocol/DiskIo.h>
#include <Protocol/BlockIo.h>
#include "Protocol/CpuIo.h"
#include "Protocol/FirmwareVolume2.h"
#include "Protocol/AMIPostMgr.h"
#include <Library/DebugLib.h>
#include <Tpm20PlatformDxeStrDefs.h>
#include "Protocol/TcgPlatformSetupPolicy.h"
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/HiiPackageList.h>
#include <Protocol/HiiDatabase.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include "Protocol/DevicePath.h"
#include <Library/DevicePathLib.h>
#include <Library/HiiLib.h>
#include <Library/IoLib.h>
#include <../TcgDxe/Tcg2Dxe.h>
#include<Library/TimerLib.h>
#include <Tpm20PlatformElinks.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/RngLib.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Protocol/LegacyBiosExt.h>
#include "../../CRB_lib/Tpm20CRBLib.h"
#include <AmiTcg/AmiTpmStatusCodes.h>
#include <Guid/Gpt.h>
#include <Protocol/Reset.h>
#include <Guid/AmiTcgGuidIncludes.h>
#include <Protocol/AmiTcgProtocols.h>

#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
#include "MdePkg/Include/Protocol/NvmExpressPassthru.h"
#endif


#include <Token.h>
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
#include <Protocol/VariableLock.h>
#endif


#define AMI_PASSWORD_ADMIN  2
#ifndef EFI_IMAGE_SECURITY_DATABASE3
#define EFI_IMAGE_SECURITY_DATABASE3 L"dbr"
#endif


extern MEASURE_BOOT_VAR_FUNC_PTR MEASURES_BOOT_VARIABLES_DXE_FUNCTION;
MEASURE_BOOT_VAR_FUNC_PTR *MeasureAllBootVariablesFuncPtr = MEASURES_BOOT_VARIABLES_DXE_FUNCTION;

extern TPM20_MEASURE_PLATFORM_CONFIG_FUNC_PTR TPM20_MEASURE_PLATFORM_CONFIG_FUNCTION;
TPM20_MEASURE_PLATFORM_CONFIG_FUNC_PTR *Tpm20MeasureConfigurationInfoFuncPtr = TPM20_MEASURE_PLATFORM_CONFIG_FUNCTION;

typedef VOID (TPM20FUNCTION) (VOID);
extern TPM20FUNCTION TPM2SETUPFUNCTIONS_LIST EndOfTPM2FuncList;
extern TPM20FUNCTION TPM2PHAUTHFUNCTIONS_LIST EndOfTPM2FuncList;
extern TPM20FUNCTION TPM2PPIFUNCTIONS_LIST EndOfTPM2FuncList;

extern EFI_GUID gTcgNvramHobGuid;
extern EFI_GUID gAmiTsePasswordPromptExitGuid;
extern EFI_GUID gAmiTseAdminPasswordValidGuid;

TPM20FUNCTION* Tpm20HandleSetupFunctions[] = {TPM2SETUPFUNCTIONS_LIST NULL};
TPM20FUNCTION* Tpm20PHAuthFunctions[] = {TPM2PHAUTHFUNCTIONS_LIST NULL};
TPM20FUNCTION* Tpm20HandlePpiFunctions[] = {TPM2PPIFUNCTIONS_LIST NULL};

EFI_STATUS Tpm2GetRandom(
    UINTN                   AuthSize,
    UINT8*                  pOutBuf
);

UINT8 ReadPpiRequestEx(UINT32 *Optionaldata);

void WritePpiResult(
    IN UINT8  last_op,
    IN UINT16 status );

EFI_STATUS TcgSetVariableWithNewAttributes(
    IN CHAR16 *Name, IN EFI_GUID *Guid, IN UINT32 Attributes,
    IN UINTN DataSize, IN VOID *Data
);
EFI_STATUS TpmGetMicrocodeFunc(UINT64 *MicrocodeAddress, UINTN *McuLength);

#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
EFI_STATUS
AmiNvmeIssueBlockSid(
    IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *EfiNvmExpressPassThru
);

EFI_STATUS
AmiIsNvmeBlockSidSupported( 
    IN  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *EfiNvmExpressPassThru,
    OUT BOOLEAN                               *BlockSidFeatureSupport
); 

EFI_STATUS
AmiIsNvmeFrozen( 
    IN  EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL    *EfiNvmExpressPassThru,
    OUT BOOLEAN                               *FreezeLocked
); 
#endif

EFI_STATUS
EFIAPI
MeasureVariable (
    IN      UINT32                    PCRIndex,
    IN      UINT32                    EventType,
    IN      CHAR16                    *VarName,
    IN      EFI_GUID                  *VendorGuid,
    IN      VOID                      *VarData,
    IN      UINTN                     VarSize
);

EFI_STATUS dTPMCrbSetReqReadyState(TPM_CRB_ACCESS_REG_PTR dCrbAccessRegPtr);
BOOLEAN isTpm20CrbPresent();
UINT32 NetRandomInitSeed (VOID);

static  void   *OpromContext = NULL;
EFI_EVENT       OpromEvent;
EFI_EVENT       gLegacyBootEvent;

EFI_STATUS
EFIAPI
Tpm2HierarchyChangeAuth (
    IN TPMI_RH_HIERARCHY_AUTH     AuthHandle,
    IN TPMS_AUTH_COMMAND *AuthSession,
    IN TPM2B_AUTH                *NewAuth
);



UINTN      mMeasureGptCount = 0;
EFI_TREE_PROTOCOL   *TrEEProtocolInstance = NULL;
static UINT8              PpiRequest;
static UINT32              PpiRequestOptionalData;

EFI_HII_HANDLE            gHiiHandle=NULL;
EFI_HII_DATABASE_PROTOCOL       *HiiDatabase=NULL;
AMI_POST_MANAGER_PROTOCOL *pAmiPostMgr = NULL;
static PERSISTENT_BIOS_TPM_FLAGS  TpmNvflags;
static BOOLEAN RequestRejected = FALSE;

#if TPM_PASSWORD_AUTHENTICATION


BOOLEAN                   AuthenticateSet;
BOOLEAN                   AdminPasswordValid;
BOOLEAN                   PasswordSupplied;

VOID SignalProtocolEvent(IN EFI_GUID *TcgPasswordAuthenticationGuid);


#endif

static BOOLEAN IsRunPpiUIAlreadyDone = FALSE;
#pragma pack (1)
typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
#if x64_TCG
    UINT64               PostCodeLength;
#else
    UINTN                PostCodeLength;
#endif
} EFI_TCG_EV_POST_CODE;

typedef struct
{
    AMI_EFI_TCG_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} PEI_EFI_POST_CODE;
#pragma pack()


EFI_STATUS getSetupData(
    IN OUT SETUP_DATA** ppsd,
    IN UINT32        * pattr,
    IN UINTN         * psz );


//
//
// Data Table definition
//
typedef struct _AMI_VALID_CERT_IN_SIG_DB
{
    UINT32          SigOffset;
    UINT32          SigLength;
} AMI_VALID_CERT_IN_SIG_DB;

EFI_STATUS
EFIAPI
GetRandomAuthPassword(
    IN     UINT16    RNGValueLength,
    IN OUT UINT8    *RNGValue
)
{
    EFI_STATUS   Status = EFI_SUCCESS;
    return Status;
}


EFI_STATUS
EFIAPI
TpmRevokeTrust (
)
{
    EFI_STATUS     Status = EFI_SUCCESS;
    return Status;
}

VOID HandleTpm20PpiHook(IN EFI_EVENT ev,
                        IN VOID *ctx);


#define GET_HOB_TYPE( Hob )     ((Hob).Header->HobType)
#define GET_HOB_LENGTH( Hob )   ((Hob).Header->HobLength)
#define GET_NEXT_HOB( Hob )     ((Hob).Raw + GET_HOB_LENGTH( Hob ))
#define END_OF_HOB_LIST( Hob )  (GET_HOB_TYPE( Hob ) == \
                                 EFI_HOB_TYPE_END_OF_HOB_LIST)

/**
  Measures Separator event

  @param[in]   UINT32 PcrIndex,

  @return EFI_SUCCESS   on success
  @return Other         reference LocateProtocol, AllocatePool, HashLogExtendEvent
**/
EFI_STATUS
MeasureSeparatorEvent (
    IN  UINT32  PCRIndex
)
{
    UINT32           EventData;
    TrEE_EVENT       *Tpm20Event=NULL;
    UINT64           Flags = 0;
    EFI_STATUS       Status;

    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }
    }

    Status = gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                            sizeof(UINT32) + sizeof(UINT32)),  (void **)&Tpm20Event);

    if(Tpm20Event==NULL || EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;

    EventData = 0;
    Tpm20Event->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + sizeof(EventData);
    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = PCRIndex;
    Tpm20Event->Header.EventType   = EV_SEPARATOR;

    gBS->CopyMem ((UINT32 *)((UINTN)&Tpm20Event->Event[0]),
                  &EventData,
                  sizeof(UINT32));

    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
             Flags, (EFI_PHYSICAL_ADDRESS)&EventData, (UINT64)sizeof(EventData),
             Tpm20Event);

    gBS->FreePool(Tpm20Event);

    TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_UEFI_SEPARATORS_MEASURED | EFI_SOFTWARE_DXE_BS_DRIVER);
    return Status;
}



/**
  Measures secureboot related certificates in db

  @param[in]   UINTN sizeOfCertificate,
               UINT8 *pterCertificate 

  @return EFI_SUCCESS   on success
  @return Other         reference LocateProtocol, AllocatePool, HashLogExtendEvent
**/
EFI_STATUS
MeasureCertificate(UINTN sizeOfCertificate,
                   UINT8 *pterCertificate)
{
    EFI_STATUS                Status;
    TrEE_EVENT               *Tcg20Event = NULL;
    EFI_VARIABLE_DATA        *VarLog = NULL;
    TCG_PLATFORM_SETUP_PROTOCOL *ProtocolInstance;

    UINTN                     i=0;
    UINTN                     VarNameLength;
    static BOOLEAN            initialized = 0;
    static TPM_DIGEST         digestTrackingArray[6];
    static TPM_DIGEST         zeroDigest;
    SHA1_CTX                  Sha1Ctx;
    TCG_DIGEST                Sha1Digest;
    UINT64                    Flags = 0;
    UINT32                    EventSize = 0;
    UINT8                     *EventDataPtr = NULL;

    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL,(void **) &TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }
    }

    VarNameLength = StrLen(L"db");

    EventSize = (UINT32)( sizeof (*VarLog) + VarNameLength
                          * sizeof (CHAR16) + sizeOfCertificate) - 3;

    Status = gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                            sizeof(UINT32) + EventSize), (void **)&Tcg20Event);

    if(Tcg20Event==NULL || EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;

    Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
    if(EFI_ERROR(Status)){
        gBS->FreePool(Tcg20Event);
        return Status;
    }

    if(!initialized)
    {
        for(i=0; i<5; i++)
        {
            gBS->SetMem(digestTrackingArray[i].digest,20, 0);
        }
        gBS->SetMem(zeroDigest.digest,20, 0);
        initialized = TRUE;
    }

    Tcg20Event->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + EventSize;
    Tcg20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tcg20Event->Header.HeaderVersion = 1;
    Tcg20Event->Header.PCRIndex    = 7;
    Tcg20Event->Header.EventType   = 0x800000E0;

    Status = gBS->AllocatePool(EfiBootServicesData, EventSize, (void **)&VarLog);

    if ( EFI_ERROR(Status) || VarLog == NULL )
    {   
        gBS->FreePool(Tcg20Event);
        return EFI_OUT_OF_RESOURCES;
    }

    VarLog->VariableName       = gEfiImageSecurityDatabaseGuid;
    VarLog->UnicodeNameLength  = VarNameLength;
    VarLog->VariableDataLength = sizeOfCertificate;

    gBS->CopyMem((CHAR16*)(VarLog->UnicodeName),
                 L"db",
                 VarNameLength * sizeof (CHAR16));

    gBS->CopyMem((CHAR16*)(VarLog->UnicodeName) + VarNameLength,
                 pterCertificate,
                 sizeOfCertificate);

    //before extending verify if we have already measured it.

    SHA1Init(&Sha1Ctx);

    SHA1Update(&Sha1Ctx,
               VarLog,
               (u32)EventSize);

    SHA1Final((unsigned char *)&Sha1Digest.digest, &Sha1Ctx);

    for(i=0; i<5; i++)
    {
        //tempDigest
        if(!CompareMem(digestTrackingArray[i].digest, &Sha1Digest, 20)){
            gBS->FreePool(Tcg20Event);
            gBS->FreePool(VarLog);
            return EFI_SUCCESS; //already measured
        }

        if(!CompareMem(digestTrackingArray[i].digest, zeroDigest.digest, 20))
            break; //we need to measure

        gBS->CopyMem(digestTrackingArray[i].digest, &Sha1Digest, 20);
    }

    EventDataPtr = (UINT8 *)Tcg20Event;

    EventDataPtr += sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32);

    gBS->CopyMem(EventDataPtr, VarLog, EventSize);

    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
             Flags, (EFI_PHYSICAL_ADDRESS)(UINT8 *)(UINTN)VarLog, (UINT64)EventSize,
             Tcg20Event);

    gBS->FreePool(Tcg20Event);
    
    gBS->FreePool(VarLog);
    return Status;
}




/**
  Measures secureboot related variables (DeployedMode) and AuditMode

  @param[in]   VOID 

  @return EFI_SUCCESS   on success
  @return Other         reference GetVariable, MeasureVariable
**/

EFI_STATUS  MeasureSecondarySecureBootVar()
{
    EFI_STATUS      Status;
    UINTN           VarSize  = sizeof(UINT8);
    UINT8           AuditMode, DeployedMode;
    EFI_GUID        VendorGuid;
    CHAR16         *VarName;
    UINT32          PCRIndex = 7;
       
    Status   = gRT->GetVariable(EFI_DEPLOYED_MODE_NAME,
                                &gEfiGlobalVariableGuid,
                                NULL,
                                &VarSize,
                                &DeployedMode);

    if(!EFI_ERROR(Status))return Status;
    if(DeployedMode == 1){
        DEBUG ((DEBUG_INFO, "Deployed Mode is Enabled\n"));
        PCRIndex = 1;
        return EFI_SUCCESS;
    }
            
    VarName = EFI_DEPLOYED_MODE_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    Status = MeasureVariable (
                 PCRIndex,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 &DeployedMode,
                 VarSize);
    
    if(EFI_ERROR(Status))return Status;
    
    Status   = gRT->GetVariable(EFI_AUDIT_MODE_NAME,
                                &gEfiGlobalVariableGuid,
                                NULL,
                                &VarSize,
                                &AuditMode);
    
    if(EFI_ERROR(Status))return Status;
    
    VarName = EFI_AUDIT_MODE_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    Status = MeasureVariable (
                 PCRIndex,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 &AuditMode,
                 VarSize);
    
   return Status; 
}



/**
  Measures secureboot certificates in db

  @param[in]   void

  @return EFI_SUCCESS   on success
  @return Other         reference GetVariable, AllocatePool
**/
EFI_STATUS FindandMeasureSecureBootCertificate()
{
    EFI_STATUS      Status;
    UINTN           VarSize  = 0;
    UINT8           *SecureDBBuffer = NULL;
    AMI_VALID_CERT_IN_SIG_DB    *CertInfo;
    UINT8           *CertOffsetPtr = NULL;

    VarSize = 0;

    Status   = gRT->GetVariable(L"db",
                                &gEfiImageSecurityDatabaseGuid,
                                NULL,
                                &VarSize,
                                NULL);

    if ( Status != EFI_BUFFER_TOO_SMALL )
    {
        return EFI_NOT_FOUND;
    }

    Status = gBS->AllocatePool(EfiBootServicesData, VarSize, (void **)&SecureDBBuffer);

    if ( SecureDBBuffer != NULL && !EFI_ERROR(Status))
    {
        Status = gRT->GetVariable(L"db",
                                  &gEfiImageSecurityDatabaseGuid,
                                  NULL,
                                  &VarSize,
                                  SecureDBBuffer);

        if ( EFI_ERROR( Status ))
        {
            gBS->FreePool( SecureDBBuffer  );
            return EFI_NOT_FOUND;
        }
    }
    else
    {
        return EFI_OUT_OF_RESOURCES;
    }

    //we need to find the pointer in the EFI system table and work from
    //there
    CertInfo = NULL;
    Status = EfiGetSystemConfigurationTable(&AmiValidBootImageCertTblGuid, (void **)&CertInfo );
    if(CertInfo == NULL || EFI_ERROR(Status))
    {
        gBS->FreePool( SecureDBBuffer);
        return EFI_NOT_FOUND;
    }
    if(CertInfo->SigLength == 0)
    {
        gBS->FreePool( SecureDBBuffer);
        return EFI_NOT_READY;
    }

    CertOffsetPtr = NULL;
    CertOffsetPtr = (SecureDBBuffer + CertInfo->SigOffset);
    MeasureCertificate((UINTN)CertInfo->SigLength,CertOffsetPtr);
    TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_SECURE_BOOT_CERTIFICATE_MEASURED | EFI_SOFTWARE_DXE_BS_DRIVER);
    if(SecureDBBuffer!=NULL)
    {
        gBS->FreePool( SecureDBBuffer  );
    }

    return Status;
}


UINTN Tpm20AsciiStrLen (
    IN CHAR8 *String)
{
    UINTN Length;
    for (Length = 0; *String != '\0'; String++, Length++);
    return Length;
}



EFI_STATUS
EFIAPI
Tpm20MeasureActionI (
    IN  CHAR8 *String,
    IN  UINT32 PCRIndex
)
{
    TCG_PCR_EVENT2_HDR                 TcgEvent;
    AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;

    EFI_STATUS                        Status=EFI_SUCCESS;
    
    if(String == NULL ) return EFI_INVALID_PARAMETER;
    if(PCRIndex > 7) return EFI_INVALID_PARAMETER;

    TcgEvent.PCRIndex     = PCRIndex;
    TcgEvent.EventType    = EV_EFI_ACTION;
    TcgEvent.EventSize    = (UINT32)Tpm20AsciiStrLen (String);

    Status = gBS->LocateProtocol(&AmiProtocolInternalHlxeGuid, NULL, (void **)&InternalHLXE);
    if(EFI_ERROR(Status))return Status;

    Status = InternalHLXE->AmiHashLogExtend2(TrEEProtocolInstance, (UINT8*)String, 0, TcgEvent.EventSize, &TcgEvent, (UINT8*)String);
    return Status;
}




VOID *
EFIAPI
ReadVariable (
    IN    CHAR16      *VarName,
    IN    EFI_GUID    *VendorGuid,
    OUT   UINTN       *VarSize
)
{
    EFI_STATUS                        Status;
    VOID                              *VarData;

    *VarSize = 0;
    Status = gRT->GetVariable (
                 VarName,
                 VendorGuid,
                 NULL,
                 VarSize,
                 NULL
             );
    if (Status != EFI_BUFFER_TOO_SMALL)
    {
        return NULL;
    }

    Status = gBS->AllocatePool (EfiBootServicesData, *VarSize, (void **)&VarData);
    if (VarData != NULL && !EFI_ERROR(Status))
    {
        Status = gRT->GetVariable (
                     VarName,
                     VendorGuid,
                     NULL,
                     VarSize,
                     VarData
                 );
        if (EFI_ERROR (Status))
        {
            gBS->FreePool (VarData);
            VarData = NULL;
            *VarSize = 0;
        }
    }
    return VarData;
}



EFI_STATUS
EFIAPI
MeasureVariable (
    IN      UINT32                    PCRIndex,
    IN      UINT32                    EventType,
    IN      CHAR16                    *VarName,
    IN      EFI_GUID                  *VendorGuid,
    IN      VOID                      *VarData,
    IN      UINTN                     VarSize
)
{
    EFI_STATUS            Status;
    TrEE_EVENT            *Tpm20Event;
    UINTN                 EventSize;
    UINTN                 VarNameLength;
    EFI_VARIABLE_DATA    *VarLog;

    VarNameLength = StrLen (VarName);

    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }
    }

    EventSize = (UINT32)(sizeof (*VarLog) + VarNameLength * sizeof (*VarName) + VarSize
                         - sizeof (VarLog->UnicodeName) - sizeof (VarLog->VariableData));

  
    gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                            sizeof(UINT32) + EventSize), (void **)&Tpm20Event);

    if(Tpm20Event==NULL)return EFI_OUT_OF_RESOURCES;

    Tpm20Event->Size  = sizeof(TrEE_EVENT_HEADER) + \
                        sizeof(UINT32) + (UINT32)EventSize;

    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = PCRIndex;
    Tpm20Event->Header.EventType   = EventType;


    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->VariableName       = *VendorGuid;
    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeNameLength  = VarNameLength;
    ((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->VariableDataLength = VarSize;

    gBS->CopyMem (((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeName,
                  VarName,
                  VarNameLength * sizeof (*VarName));

    gBS->CopyMem ((CHAR16 *)((EFI_VARIABLE_DATA *)((UINTN)&Tpm20Event->Event[0]))->UnicodeName + VarNameLength,
                  VarData,
                  VarSize);

    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
             0, (EFI_PHYSICAL_ADDRESS)(UINT8 *)(&Tpm20Event->Event[0]), EventSize,
             Tpm20Event);

    if(Tpm20Event!=NULL)
    {
        gBS->FreePool(Tpm20Event);
    }

    return Status;
}


EFI_STATUS
EFIAPI
TcgMeasureGptTable (
    IN  EFI_HANDLE         GptHandle
)
{
    EFI_STATUS                        Status;
    EFI_BLOCK_IO_PROTOCOL             *BlockIo=NULL;
    EFI_DISK_IO_PROTOCOL              *DiskIo=NULL;
    EFI_PARTITION_TABLE_HEADER        *PrimaryHeader=NULL;
    EFI_PARTITION_ENTRY               *PartitionEntry=NULL;
    UINT8                             *EntryPtr=NULL;
    UINTN                             NumberOfPartition;
    UINT32                            Index;
    EFI_GPT_DATA                      *GptData=NULL;
    UINT32                            EventSize;
    MASTER_BOOT_RECORD                *Mbr=NULL;
    UINT8                             Count;
    UINT32                            LBAofGptHeader = 0;
    TCG_PCR_EVENT2_HDR                 TcgEvent;
    AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;


    if (mMeasureGptCount > 0)
    {
        return EFI_SUCCESS;
    }

    Status = gBS->HandleProtocol (GptHandle, &gEfiBlockIoProtocolGuid, (VOID**)&BlockIo);
    if (EFI_ERROR (Status))
    {
        return EFI_UNSUPPORTED;
    }
    Status = gBS->HandleProtocol (GptHandle, &gEfiDiskIoProtocolGuid, (VOID**)&DiskIo);
    if (EFI_ERROR (Status))
    {   
        return EFI_UNSUPPORTED;
    }

    //Read the protective MBR
    Status = gBS->AllocatePool (EfiBootServicesData, BlockIo->Media->BlockSize, (void **)&Mbr);
    if (EFI_ERROR(Status) || Mbr == NULL)
    {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = DiskIo->ReadDisk (
                 DiskIo,
                 BlockIo->Media->MediaId,
                 0 * BlockIo->Media->BlockSize,
                 BlockIo->Media->BlockSize,
                 (UINT8 *)Mbr
             );

    for(Count=0; Count<MAX_MBR_PARTITIONS; Count++)
    {
        if(Mbr->Partition[Count].OSIndicator == 0xEE) //(i.e., GPT Protective)
        {
            LBAofGptHeader = *(Mbr->Partition[Count].StartingLBA);
            break;
        }
    }

    if(LBAofGptHeader == 0x00){//Did not find the correct GPTHeader so return EFI_NOT_FOUND
        gBS->FreePool(Mbr);
        return EFI_NOT_FOUND;
    }

    //
    // Read the EFI Partition Table Header
    //
    Status = gBS->AllocatePool (EfiBootServicesData, BlockIo->Media->BlockSize, (void **)&PrimaryHeader);
    if (EFI_ERROR(Status) || PrimaryHeader == NULL)
    {
        gBS->FreePool(Mbr);
        return EFI_OUT_OF_RESOURCES;
    }

    Status = DiskIo->ReadDisk (
                 DiskIo,
                 BlockIo->Media->MediaId,
                 LBAofGptHeader * BlockIo->Media->BlockSize,
                 BlockIo->Media->BlockSize,
                 (UINT8 *)PrimaryHeader);

//  if(PrimaryHeader->Header.Signature != EFI_GPT_HEADER_ID)//Check for "EFI PART" signature
    if (CompareMem(EFI_GPT_HEADER_ID, &PrimaryHeader->Header.Signature, sizeof(UINT64))) return EFI_NOT_FOUND;

    if (EFI_ERROR (Status) || 
        (PrimaryHeader->Header.Signature != EFI_PTAB_HEADER_ID) ||  
        (PrimaryHeader->PartitionEntryLBA > DivU64x32(MAX_UINTN, BlockIo->Media->BlockSize )) ||
        (PrimaryHeader->SizeOfPartitionEntry != sizeof(EFI_PARTITION_ENTRY)) || 
        (PrimaryHeader->NumberOfPartitionEntries > DivU64x32(MAX_UINTN, PrimaryHeader->SizeOfPartitionEntry)))
    {
        DEBUG ((DEBUG_ERROR, "Failed to Read Partition Table Header!\n"));
        gBS->FreePool (PrimaryHeader);
        gBS->FreePool(Mbr);
        return EFI_DEVICE_ERROR;
    }

    //
    // Read the partition entry.
    //
    Status = gBS->AllocatePool (EfiBootServicesData, PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry, (void **)&EntryPtr);
    if (EFI_ERROR(Status) || EntryPtr == NULL)
    {
        gBS->FreePool (PrimaryHeader);
        gBS->FreePool(Mbr);
        return EFI_OUT_OF_RESOURCES;
    }
    Status = DiskIo->ReadDisk (
                 DiskIo,
                 BlockIo->Media->MediaId,
                 MultU64x32( PrimaryHeader->PartitionEntryLBA, BlockIo->Media->BlockSize ),
                 PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry,
                 EntryPtr
             );
    if (EFI_ERROR (Status))
    {
        gBS->FreePool (PrimaryHeader);
        gBS->FreePool (EntryPtr);
        gBS->FreePool(Mbr);
        return EFI_DEVICE_ERROR;
    }

    //
    // Count the valid partition
    //
    PartitionEntry    = (EFI_PARTITION_ENTRY *)EntryPtr;
    NumberOfPartition = 0;
    for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++)
    {
        if (CompareMem (&PartitionEntry->PartitionTypeGUID, &gEfiPartTypeUnusedGuid, sizeof(EFI_GUID)))
        {
            NumberOfPartition++;
        }
        PartitionEntry++;
    }

    //
    // Prepare Data for Measurement
    //
    EventSize = (UINT32)(sizeof (EFI_GPT_DATA) - sizeof (GptData->Partitions)
                         + NumberOfPartition * PrimaryHeader->SizeOfPartitionEntry);

    Status = gBS->AllocatePool (EfiBootServicesData, EventSize, (void **)&GptData);
    if (EFI_ERROR(Status) || GptData == NULL)
    {
        gBS->FreePool (PrimaryHeader);
        gBS->FreePool (EntryPtr);
        gBS->FreePool(Mbr);
        return EFI_OUT_OF_RESOURCES;
    }

    gBS->SetMem(GptData, EventSize, 0);

    TcgEvent.PCRIndex   = 5;
    TcgEvent.EventType  = EV_EFI_GPT_EVENT;
    TcgEvent.EventSize  = EventSize;


    //
    // Copy the EFI_PARTITION_TABLE_HEADER and NumberOfPartition
    //
    gBS->CopyMem ((UINT8 *)GptData, (UINT8*)PrimaryHeader, sizeof (EFI_PARTITION_TABLE_HEADER));
    GptData->NumberOfPartitions = NumberOfPartition;
    //
    // Copy the valid partition entry
    //
    PartitionEntry    = (EFI_PARTITION_ENTRY*)EntryPtr;
    NumberOfPartition = 0;
    for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++)
    {
        if (CompareMem (&PartitionEntry->PartitionTypeGUID, &gEfiPartTypeUnusedGuid, sizeof(EFI_GUID)))
        {
            gBS->CopyMem (
                (UINT8 *)&GptData->Partitions + NumberOfPartition * sizeof (EFI_PARTITION_ENTRY),
                (UINT8 *)PartitionEntry,
                sizeof (EFI_PARTITION_ENTRY)
            );
            NumberOfPartition++;
        }
        PartitionEntry++;
    }

    //
    // Measure the GPT data
    //
    if(NumberOfPartition > 0)
    {

        Status = gBS->LocateProtocol(&AmiProtocolInternalHlxeGuid, NULL, (void **)&InternalHLXE);
        if(EFI_ERROR(Status))return Status;
        
        if(TrEEProtocolInstance == NULL){
            Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
            if(EFI_ERROR(Status)){
                return Status;
            }
        }

        InternalHLXE->AmiHashLogExtend2(TrEEProtocolInstance, (UINT8 *)GptData, 0, EventSize, &TcgEvent, (UINT8 *)GptData);

        if (!EFI_ERROR (Status))
        {
            mMeasureGptCount++;
            DEBUG ((DEBUG_INFO, "\n GPT measurement successfull !!!\n"));
        }
    }

    gBS->FreePool (PrimaryHeader);
    gBS->FreePool (EntryPtr);
    gBS->FreePool (GptData);
    gBS->FreePool(Mbr);
    return Status;
}

#if defined(MeasureGptFilterIntelIDER) && MeasureGptFilterIntelIDER == 1

EFI_STATUS  SkipIntelIDERDevicePath (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    EFI_STATUS      Status = EFI_UNSUPPORTED;
    UINT8           ParentPortNumber;
    UINT8           InterfaceNumber;

    for ( ; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode (DevicePath))
    {
        if(DevicePath->Type == MESSAGING_DEVICE_PATH)
        {
             if(DevicePath->SubType == MSG_USB_DP)
             {
                 ParentPortNumber = ((USB_DEVICE_PATH*)DevicePath)->ParentPortNumber;
                 InterfaceNumber = ((USB_DEVICE_PATH*)DevicePath)->InterfaceNumber;

                 ///USBR ParentPortNumber is 0xB(PCH-LP) and 0xF(PCH-H)
                 ///     InterfaceNumber is 0 and 1
                 ///If we find this device, skip it

                 if ( ( (ParentPortNumber == 0xB)   || (ParentPortNumber == 0xF) ) &&
                      ( (InterfaceNumber == 0)      || (InterfaceNumber == 1) ) )
                 {
                     Status = EFI_SUCCESS;
                     break;
                 }
             }
        }
    }

    return Status;
}
EFI_STATUS  SkipSpecialDevicePath (EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    EFI_STATUS      Status = EFI_UNSUPPORTED;

    do
    {
        Status = SkipIntelIDERDevicePath( DevicePath );
        if (!EFI_ERROR (Status))
        {
            break;
        }
    } while (FALSE);

    return Status;
}
#endif


EFI_STATUS
EFIAPI
MeasureGptTable ()
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  Handle;
    EFI_HANDLE                  *HandleArray;
    UINTN                       HandleArrayCount;
    UINTN                       Index;
    EFI_DEVICE_PATH_PROTOCOL   *BlockIoDevicePath;
    EFI_DEVICE_PATH_PROTOCOL   *DevicePath;

    DEBUG ((DEBUG_INFO, "MeasureGptTable\n"));
    
    if (PcdGetBool(PcdAmiGptPolicy)){
        return EFI_SUCCESS;
    }
    

    Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &HandleArrayCount, &HandleArray);
    if (EFI_ERROR (Status))
    {
        return Status;
    }
    for (Index=0; Index < HandleArrayCount; Index++)
    {
        Status = gBS->HandleProtocol (HandleArray[Index], &gEfiDevicePathProtocolGuid, (VOID *) &BlockIoDevicePath);
        if (EFI_ERROR (Status) || BlockIoDevicePath == NULL)
        {
            continue;
        }
#if defined(MeasureGptFilterIntelIDER) && MeasureGptFilterIntelIDER == 1
        Status = SkipSpecialDevicePath (BlockIoDevicePath);
        if (!EFI_ERROR (Status))
        {
            continue;
        }
#endif

        for (DevicePath = BlockIoDevicePath; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode (DevicePath))
        {
            if ((DevicePathType (DevicePath) == ACPI_DEVICE_PATH) && (DevicePathSubType (DevicePath) == ACPI_DP))
            {
                Status = gBS->LocateDevicePath (&gEfiBlockIoProtocolGuid, &DevicePath, &Handle);
                if (!EFI_ERROR (Status))
                {
                    Status = TcgMeasureGptTable (Handle);
                    if (!EFI_ERROR (Status))
                    {
                        //
                        // GPT partition check done.
                        //
                        DEBUG ((DEBUG_INFO, "TcgMeasureGptTable Status = %r  \n", Status));                        
                    }
                }
                break;
            }
        }
    }

    gBS->FreePool(HandleArray);
    return Status;
}


EFI_STATUS
MeasureSecureBootState(
    VOID
)
{
    EFI_STATUS          Status;
    UINT32              Attribute;
    UINTN               DataSize;
    UINT8               *Variable = NULL;
    UINT64              MaxStorSize;
    UINT64              RemStorSize;
    UINT64              MaxVarSize;
    CHAR16              *VarName;
    EFI_GUID            VendorGuid;

    Attribute = EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS;

    // Query maximum size of the variable and allocate memory

    Status = gRT->QueryVariableInfo(Attribute, &MaxStorSize, &RemStorSize, &MaxVarSize);
    if (EFI_ERROR(Status))
    {
        return (Status);
    }

    DataSize = (UINTN)MaxStorSize;
    Status = gBS->AllocatePool(EfiBootServicesData, DataSize, (void **)&Variable);
    if (Variable == NULL || EFI_ERROR(Status))
    {
        return EFI_OUT_OF_RESOURCES;
    }
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer

    // 1.Measure Secure Boot Variable Value

    Status = gRT->GetVariable (
                 EFI_SECURE_BOOT_MODE_NAME,
                 &gEfiGlobalVariableGuid,
                 NULL,
                 &DataSize,
                 Variable
             );

    VarName = EFI_SECURE_BOOT_MODE_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    if(EFI_ERROR(Status))
    {
        DataSize = 0;
        *Variable = 0;
    }

    Status = MeasureVariable (
                 7,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 Variable,
                 DataSize
             );

    // 2.Measure PK Variable Value

    DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer

    Status = gRT->GetVariable (
                 EFI_PLATFORM_KEY_NAME,
                 &gEfiGlobalVariableGuid,
                 NULL,
                 &DataSize,
                 Variable
             );

    VarName = EFI_PLATFORM_KEY_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    if(EFI_ERROR(Status))
    {
        DataSize = 0;
        *Variable = 0;
    }

    Status = MeasureVariable (
                 7,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 Variable,
                 DataSize
             );

    // 3.Measure KEK Variable Value

    DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer

    Status = gRT->GetVariable (
                 EFI_KEY_EXCHANGE_KEY_NAME,
                 &gEfiGlobalVariableGuid,
                 NULL,
                 &DataSize,
                 Variable
             );

    VarName = EFI_KEY_EXCHANGE_KEY_NAME;
    VendorGuid = gEfiGlobalVariableGuid;

    if(EFI_ERROR(Status))
    {
        DataSize = 0;
        *Variable = 0;
    }

    Status = MeasureVariable (
                 7,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 Variable,
                 DataSize
             );

    if(EFI_ERROR(Status))
    {
        goto Exit;
    }

    // 4.Measure EFI_IMAGE_SECURITY_DATABASE Variable Value

    DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer

    Status = gRT->GetVariable (
                 EFI_IMAGE_SECURITY_DATABASE,
                 &gEfiImageSecurityDatabaseGuid,
                 NULL,
                 &DataSize,
                 Variable
             );

    VarName = EFI_IMAGE_SECURITY_DATABASE;
    VendorGuid = gEfiImageSecurityDatabaseGuid;

    if(EFI_ERROR(Status))
    {
        DataSize = 0;
        *Variable = 0;
    }

    Status = MeasureVariable (
                 7,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 Variable,
                 DataSize
             );

    if(EFI_ERROR(Status))
    {
        goto Exit;
    }

    // 5.Measure EFI_IMAGE_SECURITY_DATABASE1 Variable Value

    DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer

    Status = gRT->GetVariable (
                 EFI_IMAGE_SECURITY_DATABASE1,
                 &gEfiImageSecurityDatabaseGuid,
                 NULL,
                 &DataSize,
                 Variable
             );

    VarName = EFI_IMAGE_SECURITY_DATABASE1;
    VendorGuid = gEfiImageSecurityDatabaseGuid;

    if(EFI_ERROR(Status))
    {
        DataSize = 0;
        *Variable = 0;
    }

    Status = MeasureVariable (
                 7,
                 EV_EFI_VARIABLE_DRIVER_CONFIG,
                 VarName,
                 &VendorGuid,
                 Variable,
                 DataSize
             );

    if(EFI_ERROR(Status))
    {
        goto Exit;
    }
    
    
    DataSize = (UINTN)MaxStorSize; // DataSize gets updated by GetVariable. So initialize everytime before the call
    gBS->SetMem(Variable, DataSize, 0);  // Clear the buffer
    
    if (PcdGetBool(PcdAmiDbtPolicy)){
    
        DEBUG ((DEBUG_INFO, "Measuring Dbt2 \n"));
        
        Status = gRT->GetVariable (
                     EFI_IMAGE_SECURITY_DATABASE2,
                     &gEfiImageSecurityDatabaseGuid,
                     NULL,
                     &DataSize,
                     Variable
                 );
        
        DEBUG ((DEBUG_INFO, "EFI_IMAGE_SECURITY_DATABASE2 Status = %r\n", Status));
    
        VarName = EFI_IMAGE_SECURITY_DATABASE2;
        VendorGuid = gEfiImageSecurityDatabaseGuid;
    
        if(!EFI_ERROR(Status) && DataSize != 0)
        {
            Status = MeasureVariable (
                            7,
                            EV_EFI_VARIABLE_DRIVER_CONFIG,
                            VarName,
                            &VendorGuid,
                            Variable,
                            DataSize
                        );
            
            if(EFI_ERROR(Status))
            {
                DEBUG ((DEBUG_INFO, "EFI_IMAGE_SECURITY_DATABASE2 Error\n"));
            }
        }
        
        DEBUG ((DEBUG_INFO, "Measuring Dbt3 \n"));
        
        Status = gRT->GetVariable (
                     EFI_IMAGE_SECURITY_DATABASE3,
                     &gEfiImageSecurityDatabaseGuid,
                     NULL,
                     &DataSize,
                     Variable
                 );
        
        DEBUG ((DEBUG_INFO, "EFI_IMAGE_SECURITY_DATABASE2 Status = %r\n", Status));
    
        VarName = EFI_IMAGE_SECURITY_DATABASE3;
        VendorGuid = gEfiImageSecurityDatabaseGuid;
    
        if(!EFI_ERROR(Status) && DataSize != 0)
        {
            Status = MeasureVariable (
                            7,
                            EV_EFI_VARIABLE_DRIVER_CONFIG,
                            VarName,
                            &VendorGuid,
                            Variable,
                            DataSize
                        );
            
            if(EFI_ERROR(Status))
            {
                DEBUG ((DEBUG_INFO, "EFI_IMAGE_SECURITY_DATABASE2 Error\n"));
            }
        }
    }
Exit:
    TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_SECURE_BOOT_VARIABLES_MEASURED | EFI_SOFTWARE_DXE_BS_DRIVER);
    gBS->FreePool(Variable);
    return EFI_SUCCESS;
}


EFI_STATUS
MeasureSpecialPlatformState (
  VOID
  )
{
  TrEE_EVENT            *TcgEvent=NULL;
  Manufac_HOB           *TcgMfgModeVar = NULL;
  UINT8                 ManufacturingMode[]="Manufacturing Mode";
  void                  **DummyPtr=NULL;
  UINT64                Flags = 0;
  EFI_STATUS            Status;
  
#if defined(DEBUG_MODE_PLATFORM) && (DEBUG_MODE_PLATFORM == 1)
  UINT8                 DebugMode[]="Debug Mode";
#endif
  
  if(TrEEProtocolInstance == NULL){
      Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
      if(EFI_ERROR(Status)){
          return Status;
      }
  }

  //check for manufacturing mode
  DummyPtr       =  (void **)&TcgMfgModeVar;
  TcgMfgModeVar  = (Manufac_HOB *)LocateATcgHob(
                                  gST->NumberOfTableEntries,
                                  gST->ConfigurationTable,
                                  &gTcgNvramHobGuid);
  
  if(*DummyPtr != NULL)
  {
     if(TcgMfgModeVar->NvramMode & NVRAM_MODE_MANUFACTORING )
     {         
         Status = gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                                     sizeof(UINT32) + (FIRMWARE_MANUFACTURING_MODE_EVENT_STRING_LEN)), (void **)&TcgEvent);
         if(EFI_ERROR(Status))return Status;
         
         TcgEvent->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + FIRMWARE_MANUFACTURING_MODE_EVENT_STRING_LEN;
         TcgEvent->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
         TcgEvent->Header.HeaderVersion = 1;
         TcgEvent->Header.PCRIndex    =   7;
         TcgEvent->Header.EventType   = EV_EFI_ACTION;
         
         gBS->CopyMem ((UINT32 *)((UINTN)&TcgEvent->Event[0]),
                           ManufacturingMode,
                           FIRMWARE_MANUFACTURING_MODE_EVENT_STRING_LEN);
         
         Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                      Flags, (EFI_PHYSICAL_ADDRESS)&ManufacturingMode, (UINT64)FIRMWARE_MANUFACTURING_MODE_EVENT_STRING_LEN,
                      TcgEvent);

         gBS->FreePool(TcgEvent);
         
         return Status;
     }
  }
  
#if defined(DEBUG_MODE_PLATFORM) && (DEBUG_MODE_PLATFORM == 1) 
      Status = gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                                  sizeof(UINT32) + (FIRMWARE_DEBUG_MODE_EVENT_STRING_LEN)), (void **)&TcgEvent);
      if(EFI_ERROR(Status))return Status;
      
      TcgEvent->Size  = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + FIRMWARE_DEBUG_MODE_EVENT_STRING_LEN;
      TcgEvent->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
      TcgEvent->Header.HeaderVersion = 1;
      TcgEvent->Header.PCRIndex    =   7;
      TcgEvent->Header.EventType   = EV_EFI_ACTION;
      
      gBS->CopyMem ((UINT32 *)((UINTN)&TcgEvent->Event[0]),
                   DebugMode,
                   FIRMWARE_DEBUG_MODE_EVENT_STRING_LEN);
      
      Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
                   Flags, (EFI_PHYSICAL_ADDRESS)&DebugMode, (UINT64)FIRMWARE_DEBUG_MODE_EVENT_STRING_LEN,
                   TcgEvent);

      gBS->FreePool(TcgEvent);
#endif

     return EFI_SUCCESS;
}


EFI_STATUS ResetMorVariable()
{
    EFI_STATUS      Status;

    UINT32 Attribs   = EFI_VARIABLE_NON_VOLATILE
                       | EFI_VARIABLE_BOOTSERVICE_ACCESS
                       | EFI_VARIABLE_RUNTIME_ACCESS;

    UINT8 Temp       = 0;
    UINTN TempSize = sizeof (UINT8);



    Status = gRT->GetVariable(
                 L"MemoryOverwriteRequestControl",
                 &gEfiMemoryOverwriteControlDataGuid,
                 &Attribs,
                 &TempSize,
                 &Temp );

    if ( EFI_ERROR( Status ) || Temp != 0 )
    {
        Temp = 0;
        Status = gRT->SetVariable(
                     L"MemoryOverwriteRequestControl",
                     &gEfiMemoryOverwriteControlDataGuid,
                     EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS
                     | EFI_VARIABLE_RUNTIME_ACCESS,
                     sizeof (UINT8),
                     &Temp );
    }
    
    TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_MOR_BIT_CLEARED | EFI_SOFTWARE_DXE_BS_DRIVER);
    return Status;
}




VOID ChangePlatformAuth(void)
{
    TPM2B_AUTH                        NewAuth;
    TCG_PLATFORM_SETUP_PROTOCOL       *ProtocolInstance;

    static UINT16                     HashPolicysize = 0xFFFF;
    EFI_STATUS                        Status;
    
#if (defined(TPM2_DISABLE_PLATFORM_HIERARCHY_RANDOMIZATION) && (TPM2_DISABLE_PLATFORM_HIERARCHY_RANDOMIZATION == 1))
    Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
    if (!EFI_ERROR (Status))
    {
        if(ProtocolInstance->ConfigFlags.Reserved3 == 0)
        {
            DEBUG((DEBUG_INFO, "DisablePhRandomization has been set. Returning\n"));
            return;
        }
    }
#endif

    DEBUG((DEBUG_INFO, "Setting PhRandomization\n"));

    if(HashPolicysize == 0xFFFF)
    {
        Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
        if (EFI_ERROR (Status))
        {
            //use default SHA1 size
            HashPolicysize = SHA1_DIGEST_SIZE;
        }
        else
        {
            ASSERT_EFI_ERROR(Status);
            if(ProtocolInstance->ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2)
            {
                HashPolicysize = SHA1_DIGEST_SIZE;
            }
            else if(ProtocolInstance->ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2)
            {
                HashPolicysize = SHA256_DIGEST_SIZE;
            }
        }
    }

    NewAuth.size = HashPolicysize;

    Tpm2GetRandom(
        NewAuth.size,
        &NewAuth.buffer[0]
    );

    Tpm2HierarchyChangeAuth (TPM_RH_PLATFORM, NULL, &NewAuth);
    TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_PH_RANDOMIZED | EFI_SOFTWARE_DXE_BS_DRIVER);
    return;
}

VOID PHAuthLockHook(VOID)
{
#if TpmPassword_SUPPORT
#else
    UINTN i=0;
    for (i = 0; Tpm20PHAuthFunctions[i] != NULL; i++)
        Tpm20PHAuthFunctions[i]();
#endif
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   ReadAndMeasureBootVariable
//
// Description: Read and Measures Boot Variable
//
// Input:       IN      CHAR16      *VarName,
//              IN      EFI_GUID    *VendorGuid,
//              OUT     UINTN       *VarSize
//              OUT     VOID        **VarData
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS ReadAndMeasureBootVariable(
    IN CHAR16   *VarName,
    IN EFI_GUID *VendorGuid,
    OUT UINTN   *VarSize,
    OUT VOID    **VarData )
{
    EFI_STATUS Status;

    *VarData = ReadVariable( VarName, VendorGuid, VarSize );

    if ( *VarData == NULL )
    {
        return EFI_NOT_FOUND;
    }
    
    Status = MeasureVariable(
                     PCR_FOR_BOOT_VARIABLES,
                     EV_EFI_VARIABLE_BOOT,
                     VarName,
                     VendorGuid,
                     *VarData,
                     *VarSize);
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasureAllBootVariables
//
// Description: Measures all the boot Variables
//
// Input:
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS MeasureAllBootVariables(
    VOID )
{
    EFI_STATUS Status;
    CHAR16     BootVarName[] = L"BootOrder";
    UINT16     *BootOrder=NULL;
    UINTN      BootCount;
    UINTN      Index;
    VOID       *BootVarData = NULL;
    UINTN      Size;

    Status = ReadAndMeasureBootVariable(
                 BootVarName,
                 &gEfiGlobalVariableGuid,
                 &BootCount,
                 (void **)&BootOrder
             );

    if ( Status == EFI_NOT_FOUND )
    {
       if(BootOrder!=NULL){
            gBS->FreePool(BootOrder);
        }
        return EFI_SUCCESS;
    }

    if ( EFI_ERROR( Status ))
    {
       if(BootOrder!=NULL){
            gBS->FreePool(BootOrder);
        }
        return Status;
    }

    BootCount /= sizeof (*BootOrder);

    for ( Index = 0; Index < BootCount; Index++ )
    {

#if defined (TSE_CAPITAL_BOOT_OPTION) && (TSE_CAPITAL_BOOT_OPTION == 0)
        UnicodeSPrint( BootVarName, sizeof(BootVarName), L"Boot%04x",
                       BootOrder[Index] );
#else
        UnicodeSPrint( BootVarName, sizeof(BootVarName), L"Boot%04X",
                       BootOrder[Index] );
#endif

        Status = ReadAndMeasureBootVariable(
                     BootVarName,
                     &gEfiGlobalVariableGuid,
                     &Size,
                     &BootVarData
                 );

        if ( !EFI_ERROR( Status ))
        {
            if ( BootVarData != NULL )
            {
                gBS->FreePool( BootVarData );
            }
        }
    }
    
    if(BootOrder!=NULL){
        gBS->FreePool(BootOrder);
    }
    
    return EFI_SUCCESS;
}


/**
  Enables Block SID on all handles that support the gEfiNvmExpressPassThruProtocolGuid
  and supports Tcg Security protocol on the secure harddrive

  @param[in]   VOID 

  @return EFI_SUCCESS             Enable Block SID command successfully sent
  @return Other                   reference AmiNvmeIssueBlockSid library function in UefiAmiNvmeLib.
**/
#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
EFI_STATUS AmiTcgInternalEnableBlockSID(VOID)
{
    EFI_HANDLE                *NvmePassThruHandles;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   *NvmeDevice;
    UINTN                     NumOfHandles=0;
    UINTN                     Index;
    EFI_STATUS                retStatus, Status;
    BOOLEAN                   SidBlocked;
    
    retStatus = gBS->LocateHandleBuffer (
                 ByProtocol,
                 &gEfiNvmExpressPassThruProtocolGuid,
                 NULL,
                 &NumOfHandles,
                 &NvmePassThruHandles
               );
           
    DEBUG ((DEBUG_INFO, "AmiTcgInternalEnableBlockSID::gBS->LocateHandleBuffer Status = %r \n",retStatus));
    
    if (EFI_ERROR (retStatus)) {
        return retStatus;
    }
           
    for (Index = 0; Index < NumOfHandles; Index++) {
        Status = gBS->HandleProtocol (
                NvmePassThruHandles[Index],
                &gEfiNvmExpressPassThruProtocolGuid,
                (VOID **) &NvmeDevice
        );
       
        DEBUG ((DEBUG_INFO, "AmiTcgInternalEnableBlockSID:: gBS->HandleProtocol Status = %r, NvmeDevice = %x \n",Status,  NvmeDevice));
        
        if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_INFO, "gBS->HandleProtocol: Status=%r\n", Status));
            continue;
        }
        
        Status = AmiIsNvmeFrozen(NvmeDevice, &SidBlocked);
       
        DEBUG ((DEBUG_INFO, "AmiTcgInternalEnableBlockSID::AmiIsNvmeBlockSidSupported Status = %r, SidSupport = %x \n",Status, SidBlocked));
        if(!EFI_ERROR(Status) && SidBlocked != TRUE){
            retStatus = AmiNvmeIssueBlockSid(NvmeDevice);
        }
    }
    
    DEBUG ((DEBUG_INFO, "AmiTcgInternalEnableBlockSID::AmiTcgInternalEnableBlockSID Status = %r\n",retStatus));
    return retStatus;
}
#endif

VOID
EFIAPI
NvReadyToBootLock (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
){
    
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
    EDKII_VARIABLE_LOCK_PROTOCOL    *LockProtocol;
    EFI_STATUS                      Status;
    
    Status =  gBS->LocateProtocol(&gEdkiiVariableLockProtocolGuid, NULL, (void **)&LockProtocol);
    if(!EFI_ERROR(Status))
    {
        Status = LockProtocol->RequestToLock(LockProtocol, L"TcgSIDVariable", &FlagsStatusguid);
        ASSERT_EFI_ERROR(Status);
    }
#endif
}


VOID
EFIAPI
SidRequestOnReadyToBoot(
        IN      EFI_EVENT                 Event,
        IN      VOID                      *Context
    )
{
#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
    EFI_STATUS                Status;
    UINTN                     SidState=1;    
    UINTN                     SidVarSize;

    UINT32                    Attribs   = EFI_VARIABLE_NON_VOLATILE |\
                                          EFI_VARIABLE_BOOTSERVICE_ACCESS;
#endif

   //check block SID request.
#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
    SidVarSize = sizeof(SidState);
    
    Status = gRT->GetVariable(
                 L"TcgSIDVariable",
                 &FlagsStatusguid,
                 &Attribs,
                 &SidVarSize,
                 &SidState );
    
    DEBUG((DEBUG_INFO, "SidState = %x ; Status = %r \n", SidState, Status));
    
    if(EFI_ERROR(Status) || SidState == 1)
    {
        DEBUG((DEBUG_INFO, "Sending EnableBlock SID command \n"));
        AmiTcgInternalEnableBlockSID();
    }
    
    if(SidState == 0){
        SidState = 1;
        Status = TcgSetVariableWithNewAttributes(L"TcgSIDVariable",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof (SidState),
                                  &SidState );
    }
#endif
    gBS->CloseEvent(Event);
}

void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0;
    UINTN j=0;

    DEBUG((DEBUG_INFO,"\n**********PrintBuffer Entry********"));

    for(i=0; i<BufferSize; i++)
    {

        if(i%16 == 0)
        {
            DEBUG((DEBUG_INFO,"\n"));
            DEBUG((DEBUG_INFO,"%04x :", j));
            j+=1;
        }

        DEBUG((DEBUG_INFO,"%02x ", Buffer[i]));
    }
    DEBUG((DEBUG_INFO,"\n"));
}


/**
  Performs Tpm ready to boot actions. Measure configuration info; Measure separators
  measure boot variable, measure GPT and Enable block SID

  @param[in]   EFI_EVENT     Event
  @param[in]   VOID         *Context

  @return VOID
**/
VOID
EFIAPI
Tpm20OnReadyToBoot (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
)
{
    EFI_STATUS                Status;
    UINT32                    PcrIndex;
    static  BOOLEAN           mBootAttempts=0;
    AMI_TCG2_DXE_FUNCTION_OVERRIDE_PROTOCOL     *Tpm20MeasureConfigurationInfoFunc;

    if (mBootAttempts == 0)
    {
        ResetMorVariable();
        
        //
        // This is the first boot attempt
        //
        
        Status = gBS->LocateProtocol(
                     &gAmiTpm20MeasureConfigurationInfoGuid,
                     NULL,
                     (void **)&Tpm20MeasureConfigurationInfoFunc );
        if(!EFI_ERROR(Status))
        {
            Tpm20MeasureConfigurationInfoFunc->Function();
        }
        else
        {
            Tpm20MeasureConfigurationInfoFuncPtr();
        }
        
        //measure smbios tables
#if ( defined(Measure_Boot_Data) && (Measure_Boot_Data!= 0) )
        Status = MeasureAllBootVariablesFuncPtr( );

        if ( EFI_ERROR( Status ))
        {
            DEBUG((DEBUG_ERROR, "Boot Variables not Measured. Error!\n"));
        }
#endif
        Status = Tpm20MeasureActionI (
                     "Calling EFI Application from Boot Option",
                     AMI_PCRi_IPL_CODE
                 );
        if (EFI_ERROR (Status))
        {
            DEBUG ((DEBUG_ERROR, "First boot attempt not Measured.\n"));
        }
        else
        {
            DEBUG((DEBUG_INFO, "First boot attempt measured.\n"));
        }
        //
        // Draw a line between pre-boot env and entering post-boot env
        //
        for (PcrIndex = 0; PcrIndex < 8; PcrIndex++)
        {
            Status = MeasureSeparatorEvent (PcrIndex);
            if (EFI_ERROR (Status))
            {
                DEBUG ((DEBUG_ERROR, "Measuring separator event failed.\n"));
            }
            else
            {
                DEBUG((DEBUG_INFO, "Separator event measured.\n"));
            }

        }

        //
        // Measure GPT
        //
        Status = MeasureGptTable ();
        if (EFI_ERROR (Status))
        {
            DEBUG ((DEBUG_ERROR, "Measuring GPT failed.\n"));
        }
        else
        {
            DEBUG((DEBUG_INFO, "GPT measured.\n"));
        }

        if( PpiRequest )
        {
            DEBUG((DEBUG_INFO, "ReadytoBoot PHAuthLockHook\n", __LINE__));
            PHAuthLockHook();
        }
        
    }

    if (mBootAttempts > 0)
    {
        Status = Tpm20MeasureActionI (
                 "Returning from EFI Application from Boot Option",
                 AMI_PCRi_IPL_CODE);
    }

    //
    // Increase boot attempt counter.
    //

    mBootAttempts++;
#if defined (SetReadyStateOnExitBootServices) && (SetReadyStateOnExitBootServices == 1)
  if( 0xFFFFFFFF != *(UINT32*)(0xFED40000 + 0xC) )
    {
        if( TRUE == isTpm20CrbPresent() )
        {
            dTPMCrbSetReqReadyState( (TPM_CRB_ACCESS_REG_PTR)0xFED40000 );
        }
    }
#endif

}



VOID
EFIAPI
TCGTpm20HsTiPrepare (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
)
{
    static  BOOLEAN     bRunOnce=0;
#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
    BOOLEAN             sidSupport = FALSE;
    EFI_HANDLE          *NvmePassThruHandles;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL   *NvmeDevice;
    UINTN               NumOfHandles=0;
    UINTN               Index;
    EFI_STATUS          Status;
#endif
    
    DEBUG((DEBUG_INFO, "[%d]: Enter TCGTpm20HsTiPrepare(...)\n", __LINE__));

    if (bRunOnce == 0)
    {
#if defined(TCG_AMI_MODULE_PKG_VERSION) && (TCG_AMI_MODULE_PKG_VERSION == 1)
        Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiNvmExpressPassThruProtocolGuid,
                  NULL,
                  &NumOfHandles,
                  &NvmePassThruHandles
                );
        
        DEBUG ((DEBUG_INFO, "TCGTpm20HsTiPrepare::gBS->LocateHandleBuffer Status = %r\n",Status));
        
        if (EFI_ERROR (Status)) {
            sidSupport=0;
        }
        
        for (Index = 0; Index < NumOfHandles; Index++) {
           Status = gBS->HandleProtocol (
               NvmePassThruHandles[Index],
               &gEfiNvmExpressPassThruProtocolGuid,
               (VOID **) &NvmeDevice
           );
            
           DEBUG ((DEBUG_INFO, "TCGTpm20HsTiPrepare::gBS->HandleProtocol Status = %r ,"
                                                   " NvmeDevice = %x \n",Status, NvmeDevice));
           
           if (EFI_ERROR (Status)) {
             DEBUG ((DEBUG_INFO, "gBS->HandleProtocol: Status=%r\n", Status));
             continue;
           }
            
           Status = AmiIsNvmeBlockSidSupported(NvmeDevice, &sidSupport);
           
           DEBUG ((DEBUG_INFO, "TCGTpm20HsTiPrepare::AmiIsNvmeBlockSidSupported Status = %r ,"
                                                   " sidSupport = %x \n",Status, sidSupport));

           if (sidSupport != FALSE  && !EFI_ERROR(Status)) {
               break;
           }
       }
        
        
        DEBUG((DEBUG_INFO, "Tpm20PlatformDxe::sidSupport = %x \n", sidSupport));
        
    #if NVRAM_VERSION > 6
            Status = TcgSetVariableWithNewAttributes(L"SIDSUPPORT",
                                                  &FlagsStatusguid,
                                                  EFI_VARIABLE_NON_VOLATILE
                                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                                  EFI_VARIABLE_RUNTIME_ACCESS,
                                                  sizeof (BOOLEAN),
                                                  &sidSupport );
            
    #else
            Status = TcgSetVariableWithNewAttributes(L"SIDSUPPORT",
                                                  &FlagsStatusguid,
                                                  EFI_VARIABLE_NON_VOLATILE
                                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                                  sizeof (BOOLEAN),
                                                  &sidSupport );
    #endif
#endif

        if( PpiRequest == 0  )
        {
            DEBUG((DEBUG_INFO, "HSTI PHAuthLockHook\n", __LINE__));
            PHAuthLockHook();
        }

    }
    //
    // Increase boot attempt counter.
    //
    bRunOnce++;
    gBS->CloseEvent(Event);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GetStringFromToken
//
// Description: Gets a UNI string by Token
//
// Input:       IN      STRING_REF                Token,
//              OUT     CHAR16                    **String
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS GetStringFromToken(
    IN STRING_REF Token,
    OUT CHAR16    **String )
{
    *String = HiiGetString (
                  gHiiHandle,
                  Token,
                  NULL
              );
    
    if (*String == NULL)
    {
        return EFI_NOT_FOUND;
    }

    return EFI_SUCCESS;
}


/**
  Send ClearControl command to TPM2.

  @param Disable           if we need disable owner clear flag.

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR Unexpected device behavior.
**/
EFI_STATUS
EFIAPI
Tpm2ClearControl (
    IN TPMI_YES_NO          Disable
)
{
    EFI_STATUS                        Status;
    TPM2_CLEAR_CONTROL_COMMAND        Cmd;
    TPM2_CLEAR_CONTROL_RESPONSE       Res;
    UINT32                            ResultBufSize;
    UINT32                            CmdSize;
    UINT32                            RespSize;
    UINT8                             *Buffer;
    UINT8                             *AuthSizeOffset;

    Cmd.Header.tag         = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.Header.commandCode = SwapBytes32(TPM_CC_ClearControl);
    Cmd.Auth               = SwapBytes32(TPM_RH_PLATFORM);

    Buffer = (UINT8 *)&Cmd.AuthorizationSize;

    //
    // Add in Auth session
    //
    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    // authHandle
    *(UINT32 *)Buffer = SwapBytes32(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = SwapBytes32((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

    // disable
    *(UINT8 *)Buffer = Disable;
    Buffer += sizeof(UINT8);

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.Header.paramSize   = SwapBytes32(CmdSize);

    ResultBufSize = sizeof(Res);
    Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance,CmdSize,(UINT8 *)&Cmd , ResultBufSize , (UINT8 *)&Res);

    if (EFI_ERROR(Status))
    {
        return Status;
    }

    if (ResultBufSize > sizeof(Res))
    {
        DEBUG((DEBUG_ERROR, "ClearControl: Failed ExecuteCommand: Buffer Too Small\r\n"));
        Status = EFI_BUFFER_TOO_SMALL;
        goto ClearControlEND;
    }

    //
    // Validate response headers
    //
    RespSize = SwapBytes32(Res.Header.paramSize);
    if (RespSize > sizeof(Res))
    {
        DEBUG((DEBUG_ERROR, "ClearControl: Response size too large! %d\r\n", RespSize));
        Status = EFI_BUFFER_TOO_SMALL;
        goto ClearControlEND;
    }

    //
    // Fail if command failed
    //
    if (SwapBytes32(Res.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG((DEBUG_ERROR, "ClearControl: Response Code error! 0x%08x\r\n", SwapBytes32(Res.Header.responseCode)));
        Status = EFI_DEVICE_ERROR;
        goto ClearControlEND;
    }

    //
    // Unmarshal the response
    //

    // None

    Status = EFI_SUCCESS;

ClearControlEND:
    return Status;
}



EFI_STATUS
EFIAPI
Tpm2Clear (
    VOID
)
{
    EFI_STATUS                        Status;
    TPM2_CLEAR_COMMAND                Cmd;
    TPM2_CLEAR_RESPONSE               Res;
    UINT32                            ResultBufSize;
    UINT32                            CmdSize;
    UINT32                            RespSize;
    UINT8                             *Buffer;
    UINT8                             *AuthSizeOffset;

    Cmd.Header.tag         = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.Header.commandCode = SwapBytes32(TPM_CC_Clear);
    Cmd.Auth               = SwapBytes32(TPM_RH_PLATFORM);

    Buffer = (UINT8 *)&Cmd.AuthorizationSize;

    //
    // Add in Auth session
    //
    AuthSizeOffset = Buffer;
    *(UINT32 *)Buffer = 0;
    Buffer += sizeof(UINT32);

    // authHandle
    *(UINT32 *)Buffer = SwapBytes32(TPM_RS_PW);
    Buffer += sizeof(UINT32);

    // nonce = nullNonce
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // sessionAttributes = 0
    *(UINT8 *)Buffer = 0;
    Buffer += sizeof(UINT8);

    // auth = nullAuth
    *(UINT16 *)Buffer = 0;
    Buffer += sizeof(UINT16);

    // authorizationSize
    *(UINT32 *)AuthSizeOffset = SwapBytes32((UINT32)(Buffer - AuthSizeOffset - sizeof(UINT32)));

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.Header.paramSize   = SwapBytes32(CmdSize);

    ResultBufSize = sizeof(Res);

    Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance,CmdSize,(UINT8 *)&Cmd , ResultBufSize , (UINT8 *)&Res);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    if (ResultBufSize > sizeof(Res))
    {
        DEBUG((DEBUG_ERROR, "Clear: Failed ExecuteCommand: Buffer Too Small\r\n"));
        Status = EFI_BUFFER_TOO_SMALL;
        goto ClearEND;
    }

    //
    // Validate response headers
    //
    RespSize = SwapBytes32(Res.Header.paramSize);
    if (RespSize > sizeof(Res))
    {
        DEBUG((DEBUG_ERROR, "Clear: Response size too large! %d\r\n", RespSize));
        Status = EFI_BUFFER_TOO_SMALL;
        goto ClearEND;
    }

    //
    // Fail if command failed
    //
    if (SwapBytes32(Res.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG((DEBUG_ERROR, "Clear: Response Code error! 0x%08x\r\n", SwapBytes32(Res.Header.responseCode)));
        Status = EFI_DEVICE_ERROR;
        goto ClearEND;
    }

    //
    // Unmarshal the response
    //

    // None

    Status = EFI_SUCCESS;

ClearEND:
    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  CopyAuthSessionCommand
//
// Description:
//
//
// Input:       UINT8  AuthSessionIn
//
// Output:      TPMS_AUTH_RESPONSE* AuthSessionOut
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT32
EFIAPI
CopyAuthSessionCommand (
    IN      TPMS_AUTH_COMMAND         *AuthSessionIn, OPTIONAL
    OUT     UINT8                             *AuthSessionOut
)
{
    UINT8  *Buffer;

    Buffer = (UINT8 *)AuthSessionOut;

    //
    // Add in Auth session
    //
    if (AuthSessionIn != NULL)
    {
        //  sessionHandle
        WriteUnaligned32 ((UINT32 *)Buffer, SwapBytes32(AuthSessionIn->sessionHandle));
        Buffer += sizeof(UINT32);

        // nonce
        WriteUnaligned16 ((UINT16 *)Buffer, SwapBytes16 (AuthSessionIn->nonce.size));
        Buffer += sizeof(UINT16);

        CopyMem (Buffer, AuthSessionIn->nonce.buffer, AuthSessionIn->nonce.size);
        Buffer += AuthSessionIn->nonce.size;

        // sessionAttributes
        *(UINT8 *)Buffer = *(UINT8 *)&AuthSessionIn->sessionAttributes;
        Buffer += sizeof(UINT8);

        // hmac
        WriteUnaligned16 ((UINT16 *)Buffer, SwapBytes16 (AuthSessionIn->hmac.size));
        Buffer += sizeof(UINT16);

        CopyMem (Buffer, AuthSessionIn->hmac.buffer, AuthSessionIn->hmac.size);
        Buffer += AuthSessionIn->hmac.size;
    }
    else
    {
        //  sessionHandle
        WriteUnaligned32 ((UINT32 *)Buffer, SwapBytes32(TPM_RS_PW));
        Buffer += sizeof(UINT32);

        // nonce = nullNonce
        WriteUnaligned16 ((UINT16 *)Buffer, SwapBytes16(0));
        Buffer += sizeof(UINT16);

        // sessionAttributes = 0
        *(UINT8 *)Buffer = 0x00;
        Buffer += sizeof(UINT8);

        // hmac = nullAuth
        WriteUnaligned16 ((UINT16 *)Buffer, SwapBytes16(0));
        Buffer += sizeof(UINT16);
    }

    return (UINT32)(UINTN)(Buffer - (UINT8 *)AuthSessionOut);
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  CopyAuthSessionResponse
//
// Description:
//
//
// Input:       UINT8  AuthSessionIn
//
// Output:      TPMS_AUTH_RESPONSE* AuthSessionOut
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT32
EFIAPI
CopyAuthSessionResponse (
    IN      UINT8                              *AuthSessionIn,
    OUT     TPMS_AUTH_RESPONSE         *AuthSessionOut OPTIONAL
)
{
    UINT8                             *Buffer;
    TPMS_AUTH_RESPONSE         LocalAuthSessionOut;

    if (AuthSessionOut == NULL)
    {
        AuthSessionOut = &LocalAuthSessionOut;
    }

    Buffer = (UINT8 *)AuthSessionIn;

    // nonce
    AuthSessionOut->nonce.size = SwapBytes16 (ReadUnaligned16 ((UINT16 *)Buffer));
    Buffer += sizeof(UINT16);

    CopyMem (AuthSessionOut->nonce.buffer, Buffer, AuthSessionOut->nonce.size);
    Buffer += AuthSessionOut->nonce.size;

    // sessionAttributes
    *(UINT8 *)&AuthSessionOut->sessionAttributes = *(UINT8 *)Buffer;
    Buffer += sizeof(UINT8);

    // hmac
    AuthSessionOut->hmac.size = SwapBytes16 (ReadUnaligned16 ((UINT16 *)Buffer));
    Buffer += sizeof(UINT16);

    CopyMem (AuthSessionOut->hmac.buffer, Buffer, AuthSessionOut->hmac.size);
    Buffer += AuthSessionOut->hmac.size;

    return (UINT32)(UINTN)(Buffer - (UINT8 *)AuthSessionIn);
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Tpm2GetRandom
//
// Description: gets random bytes from the TPM
//
//
// Input:       AuthSize
//
// Output:      UINT8* pOutBuf
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Tpm2GetRandom(
    UINTN                   AuthSize,
    UINT8*                  pOutBuf
)
{
    EFI_STATUS              Status = EFI_SUCCESS;

    TPM2_GetRandom_COMMAND  GetRandom_cmd;
    TPM2_GetRandom_RESPONSE GetRandom_ret;
    UINT32                  RetSize;
    UINT32                  RandomVal=0;
    TREE_BOOT_SERVICE_CAPABILITY ProtocolCapability;
#if (defined(INTEL_ARCHITECTURE_SUPPORT_TCG) && (INTEL_ARCHITECTURE_SUPPORT_TCG == 1))
    UINTN                   i=0;
#endif

    // Check the Request Size
    if( AuthSize > sizeof(TPM2B_DIGEST) - sizeof(UINT16) )
    {
        DEBUG(( DEBUG_ERROR, "Tpm2GetRandom Error. Request too large\n"));
        return EFI_BUFFER_TOO_SMALL;
    }
    
    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            DEBUG(( DEBUG_ERROR, "TrEE Protocol not found. Exiting...\n"));
            return Status;
        }
    }
     
    ProtocolCapability.Size = sizeof(TREE_BOOT_SERVICE_CAPABILITY);       
    Status = TrEEProtocolInstance->GetCapability(TrEEProtocolInstance, &ProtocolCapability);
     
    if(EFI_ERROR(Status)){
       DEBUG(( DEBUG_ERROR, "TCG get Capability failed. Aborting. ..\n"));
       return Status;
    }

    DEBUG(( DEBUG_INFO, "ManufacturerID = %x\n", ProtocolCapability.ManufacturerID));
        
#if (defined(INTEL_ARCHITECTURE_SUPPORT_TCG) && (INTEL_ARCHITECTURE_SUPPORT_TCG == 1))
    if( (ProtocolCapability.ManufacturerID == 0x494E5443) ) // INTC
    {
        DEBUG(( DEBUG_INFO, "Matched. ..\n"));
        for (i=0; i<AuthSize; i++){
            GetRandomNumber32(&RandomVal);
            pOutBuf[i] = (UINT8)RandomVal;
        }
        return EFI_SUCCESS; 
    }
#endif

    SetMem( &GetRandom_cmd, sizeof(GetRandom_cmd), 0 );
    SetMem( &GetRandom_ret, sizeof(GetRandom_ret), 0 );

    GetRandom_cmd.Header.tag =  SwapBytes16(TPM_ST_NO_SESSIONS);
    GetRandom_cmd.Header.commandCode = SwapBytes32(TPM_CC_GetRandom);
    GetRandom_cmd.Header.paramSize = SwapBytes32( sizeof(GetRandom_cmd) );
    GetRandom_cmd.bytesRequested = SwapBytes16(((UINT16)AuthSize));

    RetSize = sizeof(GetRandom_ret);

    Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance, sizeof(GetRandom_cmd), (UINT8*)&GetRandom_cmd,  RetSize, (UINT8*)&GetRandom_ret );
    if (EFI_ERROR (Status))
    {
        DEBUG(( DEBUG_ERROR, "Tpm2GetRandom TrEEProtocolInstance->SubmitCommand = %r \n", Status));
        return Status;
    }

    if (SwapBytes32(GetRandom_ret.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG(( DEBUG_ERROR, "Tpm2GetRandom TrEEProtocolInstance->SubmitCommand Response Code error! = %x \n", SwapBytes32(GetRandom_ret.Header.responseCode)));
        return EFI_DEVICE_ERROR;
    }

    CopyMem( pOutBuf, &GetRandom_ret.randomBytes.buffer[0], AuthSize );

    return Status;
}







//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Tpm2HierarchyChangeAuth
//
// Description: allows the authorization secret for a hierarchy or lockout to be changed using the current
//              authorization value
//
//
// Input:       AuthHandle, AuthSession, NewAuth
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
Tpm2HierarchyChangeAuth (
    IN TPMI_RH_HIERARCHY_AUTH     AuthHandle,
    IN TPMS_AUTH_COMMAND *AuthSession,
    IN TPM2B_AUTH                *NewAuth
)
{
    EFI_STATUS                           Status;
    TPM2_HIERARCHY_CHANGE_AUTH_COMMAND   Cmd;
    TPM2_HIERARCHY_CHANGE_AUTH_RESPONSE  Res;
    UINT32                               CmdSize;
    UINT32                               RespSize;
    UINT8                                *Buffer;
    UINT32                               SessionInfoSize;
    UINT8                                *ResultBuf;
    UINT32                               ResultBufSize;

    //
    // Construct command
    //
    Cmd.Header.tag          = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.Header.paramSize    = SwapBytes32(sizeof(Cmd));
    Cmd.Header.commandCode  = SwapBytes32(TPM_CC_HierarchyChangeAuth);
    Cmd.AuthHandle          = SwapBytes32(AuthHandle);

    //
    // Add in Auth session
    //
    Buffer = (UINT8 *)&Cmd.AuthSession;

    // sessionInfoSize
    SessionInfoSize = CopyAuthSessionCommand (AuthSession, Buffer);
    Buffer += SessionInfoSize;
    Cmd.AuthorizationSize = SwapBytes32(SessionInfoSize);

    // New Authorization size
    WriteUnaligned16 ((UINT16 *)Buffer, SwapBytes16(NewAuth->size));
    Buffer += sizeof(UINT16);

    // New Authorizeation
    CopyMem(Buffer, NewAuth->buffer, NewAuth->size);
    Buffer += NewAuth->size;

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.Header.paramSize = SwapBytes32(CmdSize);

    ResultBuf     = (UINT8 *) &Res;
    ResultBufSize = sizeof(Res);

    Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance, CmdSize, (UINT8*)&Cmd,  ResultBufSize, ResultBuf );

    if (EFI_ERROR(Status))return Status;

    //
    // Validate response headers
    //
    RespSize = SwapBytes32(Res.Header.paramSize);
    if (RespSize > sizeof(Res))
    {
        DEBUG ((EFI_D_ERROR, "HierarchyChangeAuth: Response size too large! %d\r\n", RespSize));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Fail if command failed
    //
    if (SwapBytes32(Res.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG((EFI_D_ERROR,"HierarchyChangeAuth: Response Code error! 0x%08x\r\n", SwapBytes32(Res.Header.responseCode)));
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  Tpm2HierarchyControl
//
// Description: enables and disables use of a hierarchy
//
//
// Input:       AuthSize
//
// Output:      UINT8* pOutBuf
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
Tpm2HierarchyControl (
    IN TPMI_RH_HIERARCHY              AuthHandle,
    IN TPMS_AUTH_COMMAND      *AuthSession,
    IN TPMI_RH_HIERARCHY              Hierarchy,
    IN TPMI_YES_NO                    State
)
{
    EFI_STATUS                       Status;
    AMI_TPM2_HIERARCHY_CONTROL_COMMAND   Cmd;
    AMI_TPM2_HIERARCHY_CONTROL_RESPONSE  Res;
    UINT32                           CmdSize;
    UINT32                           RespSize;
    UINT8                            *Buffer;
    UINT32                           SessionInfoSize;
    UINT8                            *ResultBuf;
    UINT32                           ResultBufSize;

    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }
    }
    //
    // Construct command
    //
    Cmd.Header.tag          = SwapBytes16(TPM_ST_SESSIONS);
    Cmd.Header.paramSize    = SwapBytes32(sizeof(Cmd));
    Cmd.Header.commandCode  = SwapBytes32(TPM_CC_HierarchyControl);
    Cmd.AuthHandle          = SwapBytes32(AuthHandle);

    //
    // Add in Auth session
    //
    Buffer = (UINT8 *)&Cmd.AuthSession;

    // sessionInfoSize
    SessionInfoSize = CopyAuthSessionCommand (AuthSession, Buffer);
    Buffer += SessionInfoSize;
    Cmd.AuthorizationSize = SwapBytes32(SessionInfoSize);

    WriteUnaligned32 ((UINT32 *)Buffer, SwapBytes32(Hierarchy));
    Buffer += sizeof(UINT32);

    *(UINT8 *)Buffer = State;
    Buffer += sizeof(UINT8);

    CmdSize = (UINT32)(Buffer - (UINT8 *)&Cmd);
    Cmd.Header.paramSize = SwapBytes32(CmdSize);

    ResultBuf     = (UINT8 *) &Res;
    ResultBufSize = sizeof(Res);

    Status = TrEEProtocolInstance->SubmitCommand(TrEEProtocolInstance, CmdSize, (UINT8 *)&Cmd,  ResultBufSize, ResultBuf );
    if (EFI_ERROR (Status))
    {
        DEBUG(( EFI_D_ERROR, "Tpm2GetRandom TrEEProtocolInstance->SubmitCommand = %r \n", Status));
        return Status;
    }

    if (ResultBufSize > sizeof(Res))
    {
        DEBUG ((EFI_D_ERROR, "HierarchyControl: Failed ExecuteCommand: Buffer Too Small\r\n"));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Validate response headers
    //
    RespSize = SwapBytes32(Res.Header.paramSize);
    if (RespSize > sizeof(Res))
    {
        DEBUG ((EFI_D_ERROR, "HierarchyControl: Response size too large! %d\r\n", RespSize));
        return EFI_BUFFER_TOO_SMALL;
    }

    //
    // Fail if command failed
    //
    if (SwapBytes32(Res.Header.responseCode) != TPM_RC_SUCCESS)
    {
        DEBUG((EFI_D_ERROR,"HierarchyControl: Response Code error! 0x%08x\r\n", SwapBytes32(Res.Header.responseCode)));
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

VOID
EFIAPI
DoResetOnEvent(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
    gRT->ResetSystem( EfiResetCold, 0, 0, NULL );
    return;
}


VOID HandleTpm20Setup(VOID)
{
    EFI_STATUS                        Status = EFI_SUCCESS;
    TCG_PLATFORM_SETUP_PROTOCOL       *ProtocolInstance;

    BOOLEAN                           ResetRequired=FALSE;
#if (defined(CONFIRM_SETUP_CHANGE) && (CONFIRM_SETUP_CHANGE == 1))
    EFI_EVENT                         ev;
    void                              *SimpleIn = NULL;
    static void                       *reg;
#endif

    Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
    if (EFI_ERROR (Status))
    {
        return;
    }

    if(!ProtocolInstance->ConfigFlags.EndorsementHierarchy)
    {
        DEBUG((DEBUG_INFO,"Disable EndorsementHierarchy \n"));
        Status = Tpm2HierarchyControl(TPM_RH_PLATFORM,  NULL, TPM_RH_ENDORSEMENT,  0);
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_EH_DISABLED);
        if(EFI_ERROR(Status)){
            TpmDxeReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_ERR_EH_DISABLE_FAIL | EFI_SOFTWARE_DXE_BS_DRIVER); 
        }
    }else{
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_EH_ENABLED | EFI_SOFTWARE_DXE_BS_DRIVER);
    }

    if(!ProtocolInstance->ConfigFlags.StorageHierarchy)
    {
        DEBUG((DEBUG_INFO,"Disable StorageHierarchy \n"));
        Status = Tpm2HierarchyControl(TPM_RH_PLATFORM,  NULL, TPM_RH_OWNER,  0);
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_SH_DISABLED);
        if(EFI_ERROR(Status)){
            TpmDxeReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_ERR_SH_DISABLE_FAIL | EFI_SOFTWARE_DXE_BS_DRIVER); 
        }
    }else{
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_SH_ENABLED | EFI_SOFTWARE_DXE_BS_DRIVER);
    }

    if(!ProtocolInstance->ConfigFlags.PlatformHierarchy)
    {
        Status = Tpm2HierarchyControl(TPM_RH_PLATFORM,  NULL, TPM_RH_PLATFORM,  0);
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_PH_DISABLED | EFI_SOFTWARE_DXE_BS_DRIVER);
        if(EFI_ERROR(Status)){
            TpmDxeReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MAJOR, AMI_SPECIFIC_TPM_ERR_PH_DISABLE_FAIL | EFI_SOFTWARE_DXE_BS_DRIVER); 
        }
    }else{
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_2_0_PH_ENABLED | EFI_SOFTWARE_DXE_BS_DRIVER);
    }

    if(ProtocolInstance->ConfigFlags.TpmOperation == 1)
    {
#if (defined(CONFIRM_SETUP_CHANGE) && (CONFIRM_SETUP_CHANGE == 1))
        PpiRequest = TPM20_PP_CLEAR_CONTROL_CLEAR;
        
        ProtocolInstance->ConfigFlags.Reserved5 = TRUE;
        ProtocolInstance->ConfigFlags.TpmOperation = 0;
        ProtocolInstance->UpdateStatusFlags(&ProtocolInstance->ConfigFlags, TRUE);
        
        Status = gBS->LocateProtocol( &gEfiSimpleTextInProtocolGuid,
                                       NULL,
                                       (void **)&SimpleIn );
        if ( !EFI_ERROR( Status ))
        {
            HandleTpm20PpiHook( NULL, NULL );
            return;
        }
        else
        {
            Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                       EFI_TPL_CALLBACK,
                                       HandleTpm20PpiHook,
                                       0,
                                       &ev );
            if(EFI_ERROR(Status))
            {
                return;
            }

            Status = gBS->RegisterProtocolNotify(
                         &gBdsAllDriversConnectedProtocolGuid,
                         ev,
                         &reg );
            return;
        }
#else
        
        Status = Tpm2ClearControl(0);
        if(!EFI_ERROR(Status))
        {
            Status = Tpm2Clear();
            if(EFI_ERROR(Status))
            {
                DEBUG ((DEBUG_INFO, "Tpm2Clear Status = %r \n", Status));
            }

        }
        ProtocolInstance->ConfigFlags.TpmOperation = 0;
        ProtocolInstance->UpdateStatusFlags(&ProtocolInstance->ConfigFlags, TRUE);
        TpmDxeReportStatusCode(EFI_PROGRESS_CODE, AMI_SPECIFIC_TPM_DEVICE_CLEARED | EFI_SOFTWARE_DXE_BS_DRIVER);
        ResetRequired = TRUE;
#endif        
    }
    
    if(ResetRequired == TRUE)
    {
        static void             *Resetreg = NULL;
        static EFI_EVENT        ResetOnBdsEv = NULL;

#if defined (ALLOCATE_PCR_AFTER_SMM_INIT) && (ALLOCATE_PCR_AFTER_SMM_INIT == 1)
        Status = gBS->CreateEvent( EVT_NOTIFY_SIGNAL,
                                   EFI_TPL_CALLBACK, DoResetOnEvent, NULL, &ResetOnBdsEv);

        if(EFI_ERROR(Status))
        {
            DEBUG ((DEBUG_INFO, "DoResetOnEvent Status = %r \n", Status));
        }

        Status = gBS->RegisterProtocolNotify(&gBdsAllDriversConnectedProtocolGuid, ResetOnBdsEv, &Resetreg);
#else
        gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
        
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                                       EFI_TPL_CALLBACK, DoResetOnEvent, NULL, &ResetOnBdsEv);
        if(EFI_ERROR(Status))
        {
            DEBUG ((DEBUG_INFO, "DoResetOnEvent Status = %r \n", Status));
        }
        
        Status = gBS->RegisterProtocolNotify(&gEfiResetArchProtocolGuid, ResetOnBdsEv, &Resetreg);
#endif
    }

    return;
}

VOID ClearFastBootLastBootFailedFlag()
{
    EFI_STATUS Status;
    UINT32 LastBootFailed;
    UINTN Size = sizeof(UINT32);



    Status = gRT->GetVariable(L"LastBootFailed", &FastBootVariableGuid, NULL, &Size, &LastBootFailed);
    if(!EFI_ERROR(Status))
    {
        Status = gRT->SetVariable(L"LastBootFailed",
                                  &FastBootVariableGuid,
                                  EFI_VARIABLE_NON_VOLATILE,
                                  0,
                                  &LastBootFailed);

        DEBUG ((DEBUG_INFO, "Tpm20ClearFastBootLastBootFailedFlag SetVariable Status = %r \n", Status));
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SignalProtocolEvent
//
// Description:
//  Internal function that installs/uninstalls protocol with a specified
//  GUID and NULL interface. Such protocols can be used as event
//  signaling mechanism.
//
// Input:
//      IN EFI_GUID *TcgPasswordAuthenticationGuid - Pointer to the protocol GUID
//
// Output:
//     VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if TPM_PASSWORD_AUTHENTICATION

VOID
SignalProtocolEvent (
    IN EFI_GUID    *TcgPasswordAuthenticationGuid )
{
    EFI_HANDLE  Handle = NULL;
    gBS->InstallProtocolInterface (
        &Handle, TcgPasswordAuthenticationGuid, EFI_NATIVE_INTERFACE, NULL
    );
    gBS->UninstallProtocolInterface (
        Handle, TcgPasswordAuthenticationGuid, NULL
    );
    return;
}
#endif

#if TPM_PASSWORD_AUTHENTICATION
//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OnAdminPasswordValid
//
// Description: Sets AdminPasswordValid to TRUE [If TPM_PASSWORD_AUTHENTICATION]
//
//
// Input:       IN EFI_EVENT ev,
//              IN VOID *ctx
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID EFIAPI OnAdminPasswordValid(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
    AdminPasswordValid = TRUE;
    return;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OnPasswordSupplied
//
// Description: Sets PasswordSupplied to TRUE and runs PPI User Interface
//
//
// Input:       IN EFI_EVENT ev,
//              IN VOID *ctx
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID EFIAPI OnPasswordSupplied(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
    PasswordSupplied = TRUE;
    if(RequestRejected == TRUE) return ;
    HandleTpm20PpiHook( ev, ctx);
    return ;
}


//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: check_authenticate_set
//
// Description: checks if password authentication set in Setup
//
//
// Input:
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
BOOLEAN check_authenticate_set( )
{
    EFI_STATUS Status;
    SETUP_DATA *sd           = NULL;
    BOOLEAN    CheckPassword = FALSE;

    if ( AuthenticateSet )
    {
        return TRUE;
    }
    Status = getSetupData( &sd, NULL, NULL );

    if ( !EFI_ERROR( Status ))
    {
        CheckPassword = sd->TpmAuthenticate;
    }

    if ( CheckPassword )
    {
        AuthenticateSet = TRUE;
        gBS->FreePool(sd);
        return TRUE;
    }
    gBS->FreePool(sd);
    return FALSE;
}

//****************************************************************************************
//<AMI_PHDR_START>
//
// Procedure: check_user_is_administrator
//
// Description: check if user was authenticated as an administrator (optional)
//
//
// Input:
//
// Output:      BOOLEAN
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//****************************************************************************************
BOOLEAN check_user_is_administrator( )
{
    if ( check_authenticate_set( ))
    {
        if ( AdminPasswordValid )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    return TRUE;
}


EFI_STATUS PasswordAuthHelperFunction( )
{
    UINT32      GlobalVariable = 0;
    EFI_STATUS  Status;
    EFI_EVENT   ev;
    static VOID *reg;

    //
    // Hook Up Admin Password Notification ;
    //
    AuthenticateSet    = check_authenticate_set( );
    AdminPasswordValid = FALSE;
    PasswordSupplied   = FALSE;
    {
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_NOTIFY,
                                   OnAdminPasswordValid,
                                   &reg,
                                   &ev );
        ASSERT( !EFI_ERROR( Status ));
        Status = gBS->RegisterProtocolNotify( &gAmiTseAdminPasswordValidGuid,
                                              ev,
                                              &reg );
    }

    {
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_NOTIFY,
                                   OnPasswordSupplied,
                                   &reg,
                                   &ev );
        ASSERT( !EFI_ERROR( Status ));
        Status = gBS->RegisterProtocolNotify( &gAmiTsePasswordPromptExitGuid,
                                              ev,
                                              &reg );
    }

    Status = gRT->SetVariable(
                 L"AskPassword",
                 &gTcgEfiGlobalVariableGuid,
                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                 sizeof (UINT32),
                 &GlobalVariable );

    return Status;
}


BOOLEAN AdminUserActionRequired()
{

    EFI_STATUS Status;
    UINTN AdminPassInstallSize = sizeof(UINT32);
    UINT32 AdminPsswdInstallVar;

    Status = gRT->GetVariable(L"AmiTcgAdminPasswdIsInstalled",
                              &TcgPasswordAuthenticationGuid,
                              NULL,
                              &AdminPassInstallSize,
                              &AdminPsswdInstallVar);

    if(EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "AdminUserActionRequire return FALSE\n"));
        return FALSE;
    }
    if(AdminPsswdInstallVar & AMI_PASSWORD_ADMIN)
    {
        DEBUG((DEBUG_INFO, "AdminUserActionRequire return TRUE\n"));
        return TRUE;
    }

    DEBUG((DEBUG_INFO, "AdminUserActionRequire return FALSE\n"));
    return FALSE;
}



#endif


//Default does not hash anything
EFI_STATUS Tpm20PlatformHashConfig()
{

    return EFI_SUCCESS;
}


void HandleSIDPpi()
{
    BOOLEAN             UserAction = FALSE;
    UINT8               StringType = 0;
    UINTN               CurX, CurY;
    CHAR16              *String=NULL;
    EFI_INPUT_KEY       key;
    UINTN               Count = 0;
#if (AUTO_ACCEPT_PPI) == 0   
    EFI_TPL             CurrentTpl;
#endif
    EFI_STATUS          Status;
    UINTN               SidState=1;
    AMI_CONFIRMATION_OVERRIDE_PROTOCOL *ConfirmOverride;
    UINT8                   OemConfirmUserResponse;

    DEBUG((DEBUG_INFO, "HandleSIDPpi Entry \n"));
    
    if(PpiRequest < TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC || \
       PpiRequest > TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
    {
        DEBUG((DEBUG_ERROR, "Not SID Error \n"));
        return;
    }
    
    if(IsRunPpiUIAlreadyDone ==TRUE)
    {
        DEBUG((DEBUG_ERROR, "IsRunPpiUIAlreadyDone \n"));
        return;
    }
    
    if(gST->ConIn == NULL){
        DEBUG((DEBUG_ERROR, "Con In not available returning \n"));
        return;
    }

    if (pAmiPostMgr == NULL)
    {
        Status = gBS->LocateProtocol( &gAmiPostManagerProtocolGuid,
                                      NULL,
                                      (void **)&pAmiPostMgr );
        if (EFI_ERROR(Status))
        {
            DEBUG((DEBUG_ERROR, "Cannot Initialize pAmiPostMgr \n"));
            return;
        }
    }
    
    if (PcdGetBool(PcdPostStatusCheck))
    {
        if(pAmiPostMgr->GetPostStatus() < TSE_POST_STATUS_IN_POST_SCREEN) return;
    }
    
    UserAction = FALSE;
    switch(PpiRequest)
    {
        case TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC \n"));
            if(TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc == 1)
            {
                UserAction = TRUE;
                StringType = 5;
            }
            break;
            
        case TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC \n"));
            if(TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc == 1)
            {
                UserAction = TRUE;
                StringType = 5;
            }
            break;
                
        case TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE \n"));
            UserAction = FALSE;
            StringType = 0;
            break;
            
        case TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE \n"));
            if(TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc != 0)
            {
                UserAction = TRUE;
                StringType = 5;
            }
            break;
            
        case TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE \n"));
            UserAction = FALSE;
            StringType = 0;
            break;
                   
        case TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE:
             DEBUG((DEBUG_INFO, "case TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE \n"));
             if(TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc != 0)
             {
                 UserAction = TRUE;
                 StringType = 5;
             }
             break;
            
        default:
            return;
    }
    if(UserAction)
    {
        pAmiPostMgr->SwitchToPostScreen( );
        
        if(StringType == 5)
        {
            String = NULL;
            DEBUG((DEBUG_INFO, "String type \n"));
            Status = GetStringFromToken( STRING_TOKEN(TPM_SIDHDR_STR), &String );
            DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX +=(StrLen(String));
            CurY -=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);           
            gBS->FreePool(String);
            String = NULL;
            if(PpiRequest == TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC){
                Status = GetStringFromToken( STRING_TOKEN( TPM_ENABLEBLOCKSID_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
                if(EFI_ERROR(Status))return;
                pAmiPostMgr->DisplayPostMessage( String );
                gBS->FreePool(String);
                String = NULL;                
            }
            
            if(PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC){
                Status = GetStringFromToken( STRING_TOKEN( TPM_DISABLEBLOCKSID_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
                if(EFI_ERROR(Status))return;
                pAmiPostMgr->DisplayPostMessage( String );
                gBS->FreePool(String);
                String = NULL;                
            }
            
            if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE){
                Status = GetStringFromToken( STRING_TOKEN( TPM_SETPPREQUIREDFORENABLEBLOCKSIDFUNCFALSE_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
                if(EFI_ERROR(Status))return;
                pAmiPostMgr->DisplayPostMessage( String );
                gBS->FreePool(String);
                String = NULL;                
            }
            
            if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE){
                Status = GetStringFromToken( STRING_TOKEN( TPM_SETPPREQUIREDFORDISABLEBLOCKSIDFUNCFALSE_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
                if(EFI_ERROR(Status))return;
                pAmiPostMgr->DisplayPostMessage( String );
                gBS->FreePool(String);
                String = NULL;                
            }
            if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE){
                Status = GetStringFromToken( STRING_TOKEN( TPM_SID_ACCEPT_ENABLE_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
            }
            else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE){
                Status = GetStringFromToken( STRING_TOKEN( TPM_SID_ACCEPT_DISABLE_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
            }else{
                Status = GetStringFromToken( STRING_TOKEN( TPM_SID_ACCEPT_STR ), &String );
                DEBUG((DEBUG_INFO, "GetStringFromToken return Status = %r \n", Status));
            }
            
            if(EFI_ERROR(Status))return;    
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_SID_REJECT_STR ), &String );
            DEBUG((DEBUG_ERROR, "GetStringFromToken return Status = %r \n", Status));
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
        }
        
        
        Status = gBS->LocateProtocol( &gAmiOsPpiConfirmationOverrideGuid, NULL, (void **)&ConfirmOverride);
        if(!EFI_ERROR(Status)){
            OemConfirmUserResponse = ConfirmOverride->ConfirmUser(PpiRequest, PpiRequestOptionalData);
            if(!OemConfirmUserResponse){
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                RequestRejected = TRUE;
                return;
             }
             Count = 0;
        }else
        {
             if ( gST->ConIn )
             {
                   Count = 0;
                  #if (AUTO_ACCEPT_PPI) == 0                    
                           CurrentTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
                           gBS->RestoreTPL (TPL_APPLICATION);
                  #endif
                   Count = 0;
                   while ( Count < 15000)
                   {
    #if (AUTO_ACCEPT_PPI) == 1
                       MicroSecondDelay(20000); //20ms
                       Status = EFI_SUCCESS;
                       goto AutoAcceptSkip;      
    #endif
    
                       Status =  gBS->CheckEvent( gST->ConIn->WaitForKey );
                       if(Status ==  EFI_NOT_READY)
                       {
                           MicroSecondDelay(20000); //20ms
                           Count+=1;
                           continue;
                       }
           
                       Status = gST->ConIn->ReadKeyStroke( gST->ConIn, &key );
                       if ( Status == EFI_SUCCESS )
                       {
                           if(PpiRequest == TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC  ||
                                   PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC ||
                                   PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE ||
                                   PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
                           {
       
                               if ( key.ScanCode == TCG_CONFIGURATION_ACCEPT_KEY )
                               {
                                   goto RestoreTplContinue;
                               }
                               else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                               {
                                   WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                                   goto RestoreTplReturn;
                               }
                           }
                       }
                       MicroSecondDelay(20000); //20ms
                       Count+=1;
                   }
    RestoreTplReturn:
               RequestRejected = TRUE;
    #if (AUTO_ACCEPT_PPI) == 0
               gBS->RaiseTPL( TPL_HIGH_LEVEL );
               gBS->RestoreTPL( CurrentTpl );
    #endif
               return;
    RestoreTplContinue:
    #if (AUTO_ACCEPT_PPI) == 0
               gBS->RaiseTPL( TPL_HIGH_LEVEL );
               gBS->RestoreTPL( CurrentTpl );
    #else
               Count = 0;
    #endif
           }
           else
           {
               Count = 15000;
           }
        }  
    }
#if (AUTO_ACCEPT_PPI) == 1
AutoAcceptSkip:
#endif
   //if timeout
   if(Count >= 15000)
   {
       DEBUG((DEBUG_INFO, "Count >= 15000 \n"));
       WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
       return;
   }

   if(PpiRequest == TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC ||
      PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC)
   {
       if(PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC){
           SidState = 0;
       }
       
       DEBUG((DEBUG_INFO, "Ppi_request::EnableBlock request State = %x \n", SidState));
       Status = TcgSetVariableWithNewAttributes(L"TcgSIDVariable",
                                 &FlagsStatusguid,
                                 EFI_VARIABLE_NON_VOLATILE
                                 | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                 sizeof (SidState),
                                 &SidState );
       
       DEBUG((DEBUG_INFO, "Ppi_request::Status = %r \n", Status));
       if(!EFI_ERROR(Status)){
           WritePpiResult( PpiRequest, (UINT16)(0));
       }else{
           WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
       }
       
   }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE ||
           PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE ||
           PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE ||
           PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
  {
      if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE){
          TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc = 1;
      }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE){
          TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc = 0;
      }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE){
          TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc = 1;
      }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE){
          TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc = 0;
      }
      
#if NVRAM_VERSION > 6
       Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                 &FlagsStatusguid,
                                 EFI_VARIABLE_NON_VOLATILE
                                 | EFI_VARIABLE_BOOTSERVICE_ACCESS
                                 | EFI_VARIABLE_RUNTIME_ACCESS,
                                 sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                 &TpmNvflags );

#else
       Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                 &FlagsStatusguid,
                                 EFI_VARIABLE_NON_VOLATILE
                                 | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                 sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                 &TpmNvflags );
#endif
       if(!EFI_ERROR(Status)){
           WritePpiResult( PpiRequest, (UINT16)(0));
       }else{
           WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
       }
  }else
  {
      WritePpiResult( PpiRequest, (UINT16)(0));
  }

   DEBUG((DEBUG_INFO, "Handle SID PPI Done\n"));
   ClearFastBootLastBootFailedFlag();
   gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);


}

void HandleTpm20Ppi()
{
    BOOLEAN             UserAction = FALSE;
    UINT8               StringType = 0;
    UINTN               CurX, CurY;
    CHAR16              *StrBuffer = NULL;
    CHAR16              *String=NULL;
    EFI_INPUT_KEY       key;
    UINTN               Count = 0;
#if (AUTO_ACCEPT_PPI) == 0   
    EFI_TPL             CurrentTpl;
#endif
    EFI_STATUS          Status;
    BOOLEAN             Comma=FALSE;
    UINTN               Size = sizeof(AMI_PPI_NV_VAR);
    AMI_PPI_NV_VAR      Temp;
    AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
    TCG_PLATFORM_SETUP_PROTOCOL       *ProtocolInstance;
    AMITCGSETUPINFOFLAGS    SupportedBankBitMap;
    UINT32              TpmErrorCode;
    SETUP_DATA          SetupDataBuffer;
    UINTN               SetupVariableSize = sizeof(SETUP_DATA);
    UINT32              SetupVariableAttributes;
    UINTN               SidState=1;

    AMI_CONFIRMATION_OVERRIDE_PROTOCOL *ConfirmOverride;
    UINT8                   OemConfirmUserResponse;
 #if TPM_PASSWORD_AUTHENTICATION
    UINT32     GlobalVariable;
    //Do not use the same variable or GetVariable "AMITCGPPIVAR" will fail below
    UINTN      PasswordSize = sizeof(GlobalVariable);
#endif

    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return;
        }
    }
    
#if TPM_PASSWORD_AUTHENTICATION
    if ( PasswordSupplied  && AdminUserActionRequired())
    {
        goto CheckConfirm;
    }
    else if(PasswordSupplied && !(AdminUserActionRequired()))
    {
        goto CheckConfirm;
    }

    if(IsRunPpiUIAlreadyDone ==TRUE)
    {
        DEBUG((DEBUG_INFO, " TPM_PASSWORD_AUTHENTICATION IsRunPpiUIAlreadyDone is True \n"));
        return;
    }

    if ( PasswordSupplied )
    {
        goto CheckConfirm;
    }
#else
    if(IsRunPpiUIAlreadyDone ==TRUE)
    {
        return;
    }
#endif

    IsRunPpiUIAlreadyDone = TRUE;
    DEBUG((DEBUG_INFO, "HandleTpm20Ppi Entry \n"));
    if (pAmiPostMgr == NULL)
    {
        Status = gBS->LocateProtocol( &gAmiPostManagerProtocolGuid,
                                      NULL,
                                      (void **)&pAmiPostMgr );
        if (EFI_ERROR(Status))
        {
            DEBUG((DEBUG_ERROR, "Cannot Initialize pAmiPostMgr \n"));
            return;
        }
    }
    
    //
    // Calling GetPostStatus() to check current TSE_POST_STATUS
    //
    if (PcdGetBool(PcdPostStatusCheck))
    {
        if(pAmiPostMgr->GetPostStatus() < TSE_POST_STATUS_IN_POST_SCREEN) return;
    }

#if (defined(CONFIRM_SETUP_CHANGE) && (CONFIRM_SETUP_CHANGE == 1))
    Status = gBS->LocateProtocol(&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "Error locating gTcgPlatformSetupPolicyGuid \n"));      
        return;
    }
#endif
    
    UserAction = FALSE;
    switch(PpiRequest)
    {
        case TCPA_PPIOP_SET_PCR_BANKS:
            DEBUG((DEBUG_INFO, "case TCPA_PPIOP_SET_PCR_BANKS \n"));
            if(TpmNvflags.Ppi1_3_Flags.PpRequiredForChangePCRS == 1)
            {
                UserAction = TRUE;
                StringType = 3;
            }
            break;

        case TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_FALSE:
            UserAction = TRUE;
            StringType = 4;
            break;

        case TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_TRUE:
            UserAction = FALSE;
            StringType = 4;
            break;
            
        case TPM20_PP_NO_ACTION_MAX:
            DEBUG((DEBUG_INFO, "case TPM20_PP_NO_ACTION_MAX \n"));
            return;

        case TPM20_PP_CLEAR_CONTROL_CLEAR:
        case TPM20_PP_CLEAR_CONTROL_CLEAR_2:
        case TPM20_PP_CLEAR_CONTROL_CLEAR_3:
        case TPM20_PP_CLEAR_CONTROL_CLEAR_4:
            DEBUG((DEBUG_INFO, "case TPM20_PP_CLEAR_CONTROL_CLEAR \n"));
            if(TpmNvflags.NoPpiClear != 1)
            {
                UserAction = TRUE;
                StringType = 1;

            }
            break;
        case TPM20_PP_SET_NO_PPI_CLEAR_FALSE:
            DEBUG((DEBUG_INFO, "case TPM20_PP_SET_NO_PPI_CLEAR_FALSE \n"));
            UserAction = FALSE;
            StringType = 0;
            break;

        case TPM20_PP_SET_NO_PPI_CLEAR_TRUE:
            DEBUG((DEBUG_INFO, "case TPM20_PP_SET_NO_PPI_CLEAR_TRUE \n"));
            if(TpmNvflags.NoPpiClear != 1)
            {
                UserAction = TRUE;
                StringType = 2;

            }
            break;
            
        default:
            DEBUG((DEBUG_INFO, "case default \n"));
            if (PpiRequest <= TPM20_PP_NO_ACTION_MAX)
            {
                WritePpiResult( PpiRequest, (UINT16)(0));
            }
            else
            {
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
            }
            return;
    }

#if (defined(CONFIRM_SETUP_CHANGE) && (CONFIRM_SETUP_CHANGE == 1))
    if(ProtocolInstance->ConfigFlags.Reserved5 == TRUE)
    {
        ProtocolInstance->ConfigFlags.Reserved5 = FALSE;
        UserAction = TRUE;
        ProtocolInstance->UpdateStatusFlags(&ProtocolInstance->ConfigFlags, TRUE);
    }
#endif

    DEBUG((DEBUG_INFO, "UserAction = %x \n", UserAction));
    if(UserAction)
    {
        pAmiPostMgr->SwitchToPostScreen( );

        Status = gBS->AllocatePool(EfiBootServicesData,
                                   sizeof (CHAR16) * 0x200,
                                   (VOID*) &StrBuffer);

        if ( EFI_ERROR( Status ) || StrBuffer == NULL )
        {
            DEBUG((DEBUG_ERROR, "UserAction::AllocatePool fail \n"));
            return;
        }

        gBS->SetMem( StrBuffer, sizeof (CHAR16) * 0x200, 0 );

        pAmiPostMgr->DisplayPostMessage( StrBuffer );

        pAmiPostMgr->GetCurPos(&CurX, &CurY);

        CurX =  0;
        CurY -= PPI_DISPLAY_OFFSET;

        if(StringType == 1)
        {
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN(TPM_CLEAR_STR), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY-=2;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_WARNING_CLEAR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_CAUTION_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX += StrLen(String)+1;
            CurY-=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;

        }
        else if(StringType == 2)
        {
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN(TPM_PPI_HEAD_STR), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_NOTE_CLEAR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_ACCEPT_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX += StrLen(String)+1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
        }
        else if(StringType == 3)
        {
            String = NULL;
            DEBUG((DEBUG_INFO,"PpiRequestOptionalData = %x \n", PpiRequestOptionalData));
            Status = GetStringFromToken( STRING_TOKEN(TPM_PPI_PCR_A_STR), &String );
            if(EFI_ERROR(Status))return;
            StrCpyS(StrBuffer,0x200,String);
            if(PpiRequestOptionalData & TREE_BOOT_HASH_ALG_SHA1)
            {
                if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L"SHA-1")))
                    return;
                Comma = TRUE;
            }

            if(PpiRequestOptionalData & TREE_BOOT_HASH_ALG_SHA256)
            {
                if(Comma)
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L",SHA256")))
                        return;
                }
                else
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L"SHA256")))
                        return;
                }
                Comma = TRUE;
            }

            if(PpiRequestOptionalData & TREE_BOOT_HASH_ALG_SHA384)
            {
                if(Comma)
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L",SHA384")))
                        return;
                }
                else
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L"SHA384")))
                        return;
                }
                Comma = TRUE;
            }

            if(PpiRequestOptionalData & TREE_BOOT_HASH_ALG_SHA512)
            {
                if(Comma)
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L",SHA512")))
                        return;
                }
                else
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L"SHA512")))
                            return;
                }
                Comma = TRUE;
            }

            if(PpiRequestOptionalData & TREE_BOOT_HASH_ALG_SM3)
            {
                if(Comma)
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L",SM3")))
                        return;
                }
                else
                {
                    if(EFI_ERROR(StrCatS(StrBuffer, 0x200, L"SM3")))
                        return;
                }
            }
            pAmiPostMgr->DisplayPostMessage( StrBuffer );
            gBS->FreePool(StrBuffer);
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_WARNING1_PCR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_WARNING2_PCR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_CAUTION_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            CurX += (StrLen(String));
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_PCR_ACCEPT ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_REJECT_ONLY_KEY), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX += (StrLen(String));
            CurY -=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_PCR_DECLINE ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
        }
        else if(StringType == 4)
        {
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN(TPM_PPI_HEAD2_STR), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX += 1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_PPI_HEAD2_PCR_STR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            Status = GetStringFromToken( STRING_TOKEN( TPM_CAUTION_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX +=(StrLen(String));
            CurY -=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_PPI_OS_FUTURE ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX +=(StrLen(String));
            CurY -=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_PPI_OS_FUTURE_PCR ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX =0;
            CurY+=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_REJECT_ONLY_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            pAmiPostMgr->GetCurPos(&CurX, &CurY);
            CurX +=(StrLen(String));
            CurY -=1;
            pAmiPostMgr->SetCurPos(CurX, CurY);
            gBS->FreePool(String);
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_PPI_OS_FUTURE_REJECT ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
        }

        if(StringType != 3 && StringType != 4 && StringType != 5)
        {
            String = NULL;
            Status = GetStringFromToken( STRING_TOKEN( TPM_REJECT_KEY ), &String );
            if(EFI_ERROR(Status))return;
            pAmiPostMgr->DisplayPostMessage( String );
            gBS->FreePool(String);
            String = NULL;
        }

        Status = gBS->LocateProtocol( &gAmiOsPpiConfirmationOverrideGuid, NULL, (void **)&ConfirmOverride);

        if(!EFI_ERROR(Status)){
            OemConfirmUserResponse = ConfirmOverride->ConfirmUser(PpiRequest, PpiRequestOptionalData);
            if(!OemConfirmUserResponse){
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                RequestRejected = TRUE;
                return;
            }
            Count = 0;
        }else
        {
            if ( gST->ConIn )
            {
                Count = 0;

#if (AUTO_ACCEPT_PPI) == 0                    
                    CurrentTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
                    gBS->RestoreTPL (TPL_APPLICATION);
#endif
                Count = 0;
                while ( Count < 15000)
                {
#if (AUTO_ACCEPT_PPI) == 1
                    MicroSecondDelay(20000); //20ms
                    Status = EFI_SUCCESS;
                    goto AutoAcceptSkip;      
#endif

                    Status =  gBS->CheckEvent( gST->ConIn->WaitForKey );
                    if(Status ==  EFI_NOT_READY)
                    {
                        MicroSecondDelay(20000); //20ms
                        Count+=1;
                        continue;
                    }
    
                    Status = gST->ConIn->ReadKeyStroke( gST->ConIn, &key );
                    if ( Status == EFI_SUCCESS )
                    {
                        if ( PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR ||
                                PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_2 ||
                                PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_3 ||
                                PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_4 )
                        {
                            if ( key.ScanCode == TCG_CLEAR_REQUEST_KEY )
                            {
                                goto RestoreTplContinue;
                            }
                            else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                            {
                                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                                goto RestoreTplReturn;
                            }
                        }
                        else if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE ||
                                PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_TRUE  || 
                                PpiRequest == TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC  ||
                                PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC ||
                                PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE ||
                                PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
                        {
    
                            if ( key.ScanCode == TCG_CONFIGURATION_ACCEPT_KEY )
                            {
                                goto RestoreTplContinue;
                            }
                            else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                            {
                                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                                goto RestoreTplReturn;
                            }
                        }
                        else if(PpiRequest == TCPA_PPIOP_SET_PCR_BANKS ||
                                PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_FALSE)
                        {
    
                            if ( key.ScanCode == TCG_CLEAR_REQUEST_KEY )
                            {
                                goto RestoreTplContinue;
                            }
                            else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                            {
                                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                                goto RestoreTplReturn;
                            }
                        }else if ( key.ScanCode == TCG_CONFIGURATION_IGNORE_KEY )
                        {
                            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
                            goto RestoreTplReturn;
                        }
                    }
                    MicroSecondDelay(20000); //20ms
                    Count+=1;
                }
    RestoreTplReturn:
                RequestRejected = TRUE;
#if (AUTO_ACCEPT_PPI) == 0
                gBS->RaiseTPL( TPL_HIGH_LEVEL );
                gBS->RestoreTPL( CurrentTpl );
#endif
                return;
    RestoreTplContinue:
#if (AUTO_ACCEPT_PPI) == 0
                gBS->RaiseTPL( TPL_HIGH_LEVEL );
                gBS->RestoreTPL( CurrentTpl );
#else
                Count = 0;
#endif
            }
            else
            {
                Count = 15000;
            }
        }
    }
    
#if (AUTO_ACCEPT_PPI) == 1
AutoAcceptSkip:
#endif

    //if timeout
    if(Count >= 15000)
    {
        DEBUG((DEBUG_INFO, "Count >= 15000 \n"));
        WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_USERABORT));
        return;
    }

#if TPM_PASSWORD_AUTHENTICATION
    DEBUG((DEBUG_INFO, " TPM_PASSWORD_AUTHENTICATION check_authenticate_set is True \n"));
    if ( check_authenticate_set( ))
    {
        GlobalVariable = 0x58494d41;
        PasswordSize = sizeof (GlobalVariable);
        Status         = gRT->SetVariable(
                             L"AskPassword",
                             &gTcgEfiGlobalVariableGuid,
                             EFI_VARIABLE_BOOTSERVICE_ACCESS,
                             PasswordSize,
                             &GlobalVariable
                         );

        if ( EFI_ERROR( Status ))
        {
            PasswordSize = sizeof (GlobalVariable);
            Status = gRT->GetVariable(
                         L"AskPassword",
                         &gTcgEfiGlobalVariableGuid,
                         NULL,
                         &PasswordSize,
                         &GlobalVariable
                     );
            GlobalVariable = 0x58494d41; // "AMIX"
            Status         = gRT->SetVariable(
                                 L"AskPassword",
                                 &gTcgEfiGlobalVariableGuid,
                                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                 PasswordSize,
                                 &GlobalVariable
                             );
        }
#if TPM_PASSWORD_AUTHENTICATION
        SignalProtocolEvent(&TcgPasswordAuthenticationGuid);
#endif
        if(AdminUserActionRequired())
        {
            DEBUG((DEBUG_INFO, "Admin password is set"));
            return;
        }
        else if(check_authenticate_set( ) == TRUE)
        {
            goto AuthCheckEnabledNoAdmin;
        }
        return;
    }

CheckConfirm:
#endif


#if TPM_PASSWORD_AUTHENTICATION
    if ( check_authenticate_set( ))
    {
        GlobalVariable = 0;
        PasswordSize = sizeof (GlobalVariable);
        Status         = gRT->SetVariable(
                             L"AskPassword",
                             &gTcgEfiGlobalVariableGuid,
                             EFI_VARIABLE_BOOTSERVICE_ACCESS,
                             PasswordSize,
                             &GlobalVariable
                         );

        if ( EFI_ERROR( Status ))
        {
            PasswordSize = sizeof (GlobalVariable);
            Status = gRT->GetVariable(
                         L"AskPassword",
                         &gTcgEfiGlobalVariableGuid,
                         NULL,
                         &PasswordSize,
                         &GlobalVariable
                     );
            GlobalVariable = 0;
            Status         = gRT->SetVariable(
                                 L"AskPassword",
                                 &gTcgEfiGlobalVariableGuid,
                                 EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                 PasswordSize,
                                 &GlobalVariable
                             );
        }

        if ( !check_user_is_administrator( ))
        {
            WritePpiResult( PpiRequest, TCPA_PPI_USERABORT );
            return;
        }
    }


AuthCheckEnabledNoAdmin:
#endif

    if ( PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR ||
            PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_2 ||
            PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_3 ||
            PpiRequest == TPM20_PP_CLEAR_CONTROL_CLEAR_4 )
    {
        Status = Tpm2ClearControl(0);
        if(!EFI_ERROR(Status))
        {

            Status = Tpm2Clear();
            if(EFI_ERROR(Status))
            {
                DEBUG((DEBUG_ERROR, "Error Clearing TPM20 device\n"));
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
            }
            else
            {
                DEBUG((DEBUG_INFO, "TPM20 device cleared\n"));
                WritePpiResult( PpiRequest, (UINT16)(0));
            }
        }
        else
        {
            DEBUG((DEBUG_ERROR, "Tpm2ClearControl failure\n"));
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
    }
    else if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE ||
            PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_TRUE)
    {
        if(PpiRequest == TPM20_PP_SET_NO_PPI_CLEAR_FALSE)
        {
            TpmNvflags.NoPpiClear = 0;

        }
        else
        {
            TpmNvflags.NoPpiClear = 1;
        }
        
        TpmNvflags.Ppi1_3_Flags.PpRequiredForClear = (TpmNvflags.NoPpiClear == 1) ? 0:1;
        
#if NVRAM_VERSION > 6
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS
                                  | EFI_VARIABLE_RUNTIME_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );

#else
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );
#endif

        if(EFI_ERROR(Status))
        {
            DEBUG((DEBUG_ERROR, "Error Clearing TPM20 device\n"));
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
        else
        {
            WritePpiResult( PpiRequest, (UINT16)(0));
        }
    }
    else if(PpiRequest == TCPA_PPIOP_SET_PCR_BANKS)
    {

        Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
        if (EFI_ERROR (Status))
        {
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
            return;
        }

        Size = sizeof(Temp);
        Status = gRT->GetVariable( L"AMITCGPPIVAR", \
                                   &AmitcgefiOsVariableGuid, \
                                   NULL, \
                                   &Size, \
                                   &Temp );

        DEBUG((DEBUG_INFO,"Temp.OptionalData = %x \n", Temp.OptionalData));
        DEBUG((DEBUG_INFO,"Status = %r File %s Line %d  \n", Status, __FILE__, __LINE__));
        if(!EFI_ERROR(Status))
        {
            //ProtocolInstance->ConfigFlags.PcrBanks = Temp.OptionalData;
            //ProtocolInstance->UpdateStatusFlags(&ProtocolInstance->ConfigFlags, TRUE);
            //WritePpiResult( PpiRequest, (UINT16)(0));
            Status = gBS->LocateProtocol(&AmiProtocolInternalHlxeGuid, NULL, (void **)&InternalHLXE);
            if(EFI_ERROR(Status))
            {
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
                return;
            }
//already LocateProtocol Policyguid above
/*            Status = gBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
            if(EFI_ERROR(Status))
            {
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
                return;
            }
*/
            Size =sizeof(AMITCGSETUPINFOFLAGS);
            Status = gRT->GetVariable(  L"PCRBitmap", \
                                        &gTcgInternalflagGuid, \
                                        NULL, \
                                        &Size, \
                                        &SupportedBankBitMap );

            if(EFI_ERROR(Status))
            {
                WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
                return;
            }


            Status = InternalHLXE->AmiAllocatePcrBank(Temp.OptionalData,
                     ProtocolInstance->ConfigFlags.PcrBanks,
                     SupportedBankBitMap.SupportedPcrBitMap, &TpmErrorCode);

            DEBUG((DEBUG_INFO,"Temp.OptionalData = %x \n", Temp.OptionalData));
            DEBUG((DEBUG_INFO,"PpiRequestOptionalData[1] = %x \n", PpiRequestOptionalData));
            DEBUG((DEBUG_INFO,"Status = %r \n", Status));

            if(!EFI_ERROR(Status))
            {
                Status = gRT->GetVariable (
                             L"Setup",
                             &gSetupVariableGuid,
                             &SetupVariableAttributes,
                             &SetupVariableSize,
                             &SetupDataBuffer);

                if(EFI_ERROR(Status))
                {
                    DEBUG((DEBUG_ERROR,"Status Setup= %r \n", Status));
                    WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
                    return ;
                }

                SetupDataBuffer.Sha1 = 0;
                SetupDataBuffer.Sha256 = 0;
                SetupDataBuffer.Sha384 = 0;
                SetupDataBuffer.Sha512 = 0;
                SetupDataBuffer.SM3 = 0;

                if( Temp.OptionalData & TREE_BOOT_HASH_ALG_SHA1)
                {
                    SetupDataBuffer.Sha1 = TREE_BOOT_HASH_ALG_SHA1;
                }
                if( Temp.OptionalData & TREE_BOOT_HASH_ALG_SHA256)
                {
                    SetupDataBuffer.Sha256 = TREE_BOOT_HASH_ALG_SHA256;
                }
                if( Temp.OptionalData & TREE_BOOT_HASH_ALG_SHA384)
                {
                    SetupDataBuffer.Sha384 = TREE_BOOT_HASH_ALG_SHA384;
                }
                if( Temp.OptionalData & TREE_BOOT_HASH_ALG_SHA512)
                {
                    SetupDataBuffer.Sha512 = TREE_BOOT_HASH_ALG_SHA512;
                }
                if( Temp.OptionalData & TREE_BOOT_HASH_ALG_SM3)
                {
                    SetupDataBuffer.SM3 = 1;
                }

                Status = gRT->SetVariable (
                             L"Setup",
                             &gSetupVariableGuid,
                             SetupVariableAttributes,
                             SetupVariableSize,
                             &SetupDataBuffer);

                if(EFI_ERROR(Status))
                {
                    DEBUG((DEBUG_ERROR,"Status Setup= %r \n", Status));
                    WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
                    return ;
                }

                WritePpiResult( PpiRequest, (UINT16)(0));
            }
            else
            {
                WritePpiResult( PpiRequest, (UINT16)(TpmErrorCode));
            }
        }

    }
    else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_FALSE ||
            PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_TRUE)
    {
        if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_CHANGE_PCR_FALSE)
        {
            TpmNvflags.Ppi1_3_Flags.PpRequiredForChangePCRS = 0;
        }
        else
        {
            TpmNvflags.Ppi1_3_Flags.PpRequiredForChangePCRS = 1;
        }

#if NVRAM_VERSION > 6
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS
                                  | EFI_VARIABLE_RUNTIME_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );

#else
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );
#endif

        if(EFI_ERROR(Status))
        {
            DEBUG((DEBUG_ERROR, "Error Clearing TPM20 device\n"));
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
        else
        {
            WritePpiResult( PpiRequest, (UINT16)(0));
        }
    }else if(PpiRequest == TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC ||
             PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC)
    {
        if(PpiRequest == TCPA_PPIOP_DISABLE_BLOCK_SID_FUNC){
            SidState = 0;
        }
        
        DEBUG((DEBUG_INFO, "Ppi_request::EnableBlock request State = %x \n", SidState));
        Status = TcgSetVariableWithNewAttributes(L"TcgSIDVariable",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof (SidState),
                                  &SidState );
        
        DEBUG((DEBUG_INFO, "Ppi_request::Status = %r \n", Status));
        if(!EFI_ERROR(Status)){
            WritePpiResult( PpiRequest, (UINT16)(0));
        }else{
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
        
    }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE ||
            PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE ||
            PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE ||
            PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
   {
       if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_TRUE){
           TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc = 1;
       }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_ENABLE_BLOCK_SID_FUNC_FALSE){
           TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc = 0;
       }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_TRUE){
           TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc = 1;
       }else if(PpiRequest == TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE){
           TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc = 0;
       }
       
#if NVRAM_VERSION > 6
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS
                                  | EFI_VARIABLE_RUNTIME_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );

#else
        Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                  &FlagsStatusguid,
                                  EFI_VARIABLE_NON_VOLATILE
                                  | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                  sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                  &TpmNvflags );
#endif
        if(!EFI_ERROR(Status)){
            WritePpiResult( PpiRequest, (UINT16)(0));
        }else{
            WritePpiResult( PpiRequest, (UINT16)(TCPA_PPI_BIOSFAIL));
        }
   }else
   {
       WritePpiResult( PpiRequest, (UINT16)(0));
   }

    DEBUG((DEBUG_INFO, "TPM20 changes made reseting system\n"));
    ClearFastBootLastBootFailedFlag();
    gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
}

VOID
EFIAPI
Tpm20OnExitBootServices (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
)
{
    EFI_STATUS    Status;
    UINT8         *FinalsTable = NULL;

    //
    // Measure invocation of ExitBootServices,
    //
    Status = Tpm20MeasureActionI (
                 "Exit Boot Services Invocation", AMI_PCRi_IPL_CONFIG_AND_DATA);

    //
    // Measure success of ExitBootServices
    //
    Status = Tpm20MeasureActionI (
                 "Exit Boot Services Returned with Success", AMI_PCRi_IPL_CONFIG_AND_DATA);
    
    Status = EfiGetSystemConfigurationTable (&gTcg2FinalEventsTableGuid, (VOID **)&FinalsTable);
    
    if(FinalsTable != NULL && !EFI_ERROR(Status)){
       DEBUG((DEBUG_INFO, "Finals Table installed\n")); 
	}
    
#if defined (SetReadyStateOnExitBootServices) && (SetReadyStateOnExitBootServices == 1)
  if( 0xFFFFFFFF != *(UINT32*)(0xFED40000 + 0xC) )
    {
        if( TRUE == isTpm20CrbPresent() )
        {
            dTPMCrbSetReqReadyState( (TPM_CRB_ACCESS_REG_PTR)0xFED40000 );
        }
    }
#endif
}



VOID
EFIAPI
Tpm20OnExitBootServicesFailed (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
)
{
    EFI_STATUS    Status;
    Status = Tpm20MeasureActionI (
                 "Exit Boot Services Returned with Failure", AMI_PCRi_IPL_CONFIG_AND_DATA);
    if(EFI_ERROR(Status)){
        ASSERT_EFI_ERROR(Status);
    }
}



#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
VOID
EFIAPI
Tpm20OnVariableLockProtocolGuid (
    IN      EFI_EVENT                 Event,
    IN      VOID                      *Context
)
{
    EDKII_VARIABLE_LOCK_PROTOCOL    *LockProtocol;
    EFI_STATUS                      Status;

    DEBUG((DEBUG_INFO, "Tpm20OnVariableLockProtocolGuid callback entry\n"));

    Status =  gBS->LocateProtocol(&gEdkiiVariableLockProtocolGuid, NULL, (void **)&LockProtocol);
    if(!EFI_ERROR(Status))
    {
        Status = LockProtocol->RequestToLock(LockProtocol, L"TPMPERBIOSFLAGS", &FlagsStatusguid);
        ASSERT_EFI_ERROR(Status);
        Status = LockProtocol->RequestToLock(LockProtocol, L"AMITCGPPIVAR", &AmitcgefiOsVariableGuid);
    }
    ASSERT_EFI_ERROR(Status);
}
#endif




//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasurePciOptionRom
//
// Description: Measures EV_ID_OPROM_EXECUTE event
//              address (PFA) and with digest of the specified PCI device
//              OpRom image
//
//
// Input:       IN VOID  *pImage,
//              IN UINTN len,
//              IN UINT16   pfa
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Tpm2MeasurePciOptionRom(
    IN VOID  *pImage,
    IN UINTN len,
    UINT16   pfa   )
{
    EFI_STATUS           Status;
    TCG_PLATFORM_SETUP_PROTOCOL       *PolicyInstance = NULL;
    TCG_PCR_EVENT2_HDR   TcgEvent;
    UINT8                BlobDescription[]="Embedded UEFI Driver";
    SHA1_CTX             Sha1Ctx;
    SHA2_CTX             Sha2Ctx;
    SHA384_CTX           Sha384Ctx;
    SHA512_CTX           Sha512Ctx;
    SM3_CTX              Sm3Ctx;
    UINTN                               count=0;
    AMI_INTERNAL_HLXE_PROTOCOL        *InternalHLXE = NULL;
    AMI_PLATFORM_FIRMWARE_BLOB2_STRUCT *EmbeddedEvent = NULL;
    UINT8                *TempPtr;

    DEBUG((DEBUG_INFO, "Measuring image @ %x, image len = %x, pfa = %x  \n", pImage, len, pfa));
    
    if(pImage == NULL || len == 0){
        return EFI_SUCCESS;
    }
    
    if(TrEEProtocolInstance == NULL){
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }
    }
    
    Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&PolicyInstance);
    if(EFI_ERROR(Status)){
        return Status;
    }
    
    TcgEvent.PCRIndex    = 0;
    TcgEvent.EventType   = (UINT32)EV_POST_CODE;
    TcgEvent.EventSize   = sizeof(BlobDescription)-1 + sizeof(UINT8) + sizeof(EFI_PHYSICAL_ADDRESS)
                           + sizeof(UINT64);
    
    Status = gBS->AllocatePool(EfiBootServicesData, TcgEvent.EventSize,
                                         (void **)&EmbeddedEvent);    
        
    if(EFI_ERROR(Status))return Status;
    
    if(PolicyInstance->ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_1_2)
    {
        SHA1Init( &Sha1Ctx );
        SHA1Update(&Sha1Ctx,pImage,(u32)len);
        TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SHA1;
        SHA1Final((unsigned char *)&TcgEvent.Digests.digests[count].digest.sha1, &Sha1Ctx);
        count+=1;
    }
    else if(PolicyInstance->ConfigFlags.Tcg2SpecVersion == TCG2_PROTOCOL_SPEC_TCG_2)
    {
       if((PolicyInstance->ConfigFlags.PcrBanks & TREE_BOOT_HASH_ALG_SHA1))
       {
           SHA1Init( &Sha1Ctx );
           SHA1Update(&Sha1Ctx,pImage,(u32)len);
           TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SHA1;
           SHA1Final((unsigned char *)&TcgEvent.Digests.digests[count].digest.sha1, &Sha1Ctx);
           count+=1;
       }
       
       if((PolicyInstance->ConfigFlags.PcrBanks & TREE_BOOT_HASH_ALG_SHA256))
       {
           sha256_init(&Sha2Ctx);
           sha256_process( &Sha2Ctx, pImage, (u32)len );
           TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SHA256;
           sha256_done( &Sha2Ctx, (unsigned char *)&TcgEvent.Digests.digests[count].digest.sha256 );
           count+=1;
       }
       
       if((PolicyInstance->ConfigFlags.PcrBanks & TREE_BOOT_HASH_ALG_SHA384))
       {
           sha384_init(&Sha384Ctx);
           sha512_process( &Sha384Ctx, pImage, (u32)len);
           TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SHA384;
           sha384_done( &Sha384Ctx, (unsigned char *)&TcgEvent.Digests.digests[count].digest.sha384 );
           count+=1;
       }
       
       if((PolicyInstance->ConfigFlags.PcrBanks & TREE_BOOT_HASH_ALG_SHA512))
       {
           sha512_init(&Sha512Ctx);
           sha512_process( &Sha512Ctx, pImage, (u32)len );
           TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SHA512;
           sha512_done( &Sha512Ctx, (unsigned char *)&TcgEvent.Digests.digests[count].digest.sha512 );
           count+=1;
       }

       if((PolicyInstance->ConfigFlags.PcrBanks & TREE_BOOT_HASH_ALG_SM3))
       {
           sm3_init(&Sm3Ctx);
           sm3_update( &Sm3Ctx, pImage, (u32)len );
           TcgEvent.Digests.digests[count].hashAlg = TPM2_ALG_SM3_256;
           sm3_final((unsigned char *)&TcgEvent.Digests.digests[count].digest.sm3_256, &Sm3Ctx);
           count+=1;
       }

    }
    
    TcgEvent.Digests.count = (UINT32)count;
    
    Status = gBS->LocateProtocol(&AmiProtocolInternalHlxeGuid, NULL, (void **)&InternalHLXE);
    if(EFI_ERROR(Status)){
        gBS->FreePool(EmbeddedEvent);
        return Status;
    }
    
    EmbeddedEvent->BlobDescriptionSize = sizeof(BlobDescription)-1; 
    Status = AsciiStrnCpyS((CHAR8 *)EmbeddedEvent->BlobDescription, 
                            sizeof(EmbeddedEvent->BlobDescription),
                            (CHAR8 *)BlobDescription, (UINTN)EmbeddedEvent->BlobDescriptionSize);
    
    if(!EFI_ERROR(Status))
    {
        TempPtr = EmbeddedEvent->BlobDescription;
        TempPtr += EmbeddedEvent->BlobDescriptionSize;
        
        *(EFI_PHYSICAL_ADDRESS *)TempPtr = (EFI_PHYSICAL_ADDRESS )pImage;
        TempPtr+= sizeof(EFI_PHYSICAL_ADDRESS);
        *(UINT64 *)TempPtr = (UINT64)len;
        Status = InternalHLXE->AmiHashLogExtend2(TrEEProtocolInstance, NULL, 0, 0, &TcgEvent, (UINT8 *)EmbeddedEvent);
    }
    
    gBS->FreePool(EmbeddedEvent);

    return Status;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   GET_PFA
//
// Description: Returns PCI device Bus Device Function infomation
//
//
// Input:       EFI_PCI_IO_PROTOCOL   *pciIo
//
// Output:      UINT16
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
UINT16 GET_PFA(
    IN EFI_PCI_IO_PROTOCOL *pciIo )
{
    UINTN      seg;
    UINTN      bus;
    UINTN      dev;
    UINTN      func;
    EFI_STATUS Status;

    Status = pciIo->GetLocation( pciIo, &seg, &bus, &dev, &func );
    ASSERT( !EFI_ERROR( Status ));

    if (     EFI_ERROR( Status ))
    {
        return 0;
    }
    ASSERT( func < 8 );
    ASSERT( dev < 32 );
    ASSERT( bus < 256 );
    return (UINT16)((bus << 8) | (dev << 3) | func );
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   OnPciIOInstalled
//
// Description: Checks if PCI device has an Option Rom and initiates the
//              Option rom measurment
//
// Input:
//              IN  EFI_EVENT       ev
//              IN  VOID            *ctx
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
VOID EFIAPI OnPciIOInstalled(
    IN EFI_EVENT ev,
    IN VOID      *ctx )
{
#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
    EFI_STATUS                   Status;
    UINTN                        handlesSize = sizeof(EFI_HANDLE);
    EFI_HANDLE                   handles;
    CSM_PLATFORM_POLICY_DATA    *OpRomStartEndProtocol=NULL;

    DEBUG((DEBUG_INFO, "OnPciIOInstalled\n"));
    
    Status = gBS->LocateHandle(ByRegisterNotify,
                               NULL,
                               OpromContext,
                               &handlesSize,
                               &handles );

    DEBUG((DEBUG_INFO, "OnPciIOInstalled LocateHandle = %r \n", Status));

    Status = gBS->HandleProtocol(handles, &gOpromStartEndProtocolGuid, (VOID **)&OpRomStartEndProtocol);

    DEBUG((DEBUG_INFO, "OnPciIOInstalled HandleProtocol = %r \n", Status));

    if (EFI_ERROR(Status))
    {
        return;
    }

    DEBUG((DEBUG_INFO, "OpRomStartEndProtocol located \n"));

    if((OpRomStartEndProtocol == NULL))
    {
        return;
    }

    // Prevent for access NULL point
    if(OpRomStartEndProtocol->PciIo == NULL)
    {
        return;
    }

    //don't measure OP-ROM if executeRom is not set
    if (OpRomStartEndProtocol->ExecuteThisRom == FALSE) {
            return;
    }

    DEBUG((DEBUG_INFO, "OpRomStartEndProtocol->PciIo->RomImage = %x \n", OpRomStartEndProtocol->PciIo->RomImage));
    DEBUG((DEBUG_INFO, "OpRomStartEndProtocol->PciIo->RomSize = %x \n", OpRomStartEndProtocol->PciIo->RomSize));

    DEBUG((DEBUG_INFO, "Measuring legacy image \n"));

    Status = Tpm2MeasurePciOptionRom(OpRomStartEndProtocol->PciIo->RomImage,
                                     (UINT32) OpRomStartEndProtocol->PciIo->RomSize,
                                     GET_PFA(OpRomStartEndProtocol->PciIo ));

    return;
#else
    return;
#endif
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   MeasurePCIOproms
//
// Description: Sets callback to measure PCI option roms that are given control
//
// Input:       NONE
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI Tpm20MeasurePCIOproms()
{
    EFI_STATUS Status;

    Status    = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                  TPL_NOTIFY,
                                  OnPciIOInstalled,
                                  OpromContext,
                                  &OpromEvent );

    ASSERT( !EFI_ERROR( Status ));
    Status = gBS->RegisterProtocolNotify( &gOpromStartEndProtocolGuid,
                                          OpromEvent,
                                          &OpromContext );

    return EFI_SUCCESS;
}


//*************************************************************************
//<AMI_PHDR_START>
//
// Name: Tpm20LoadStrings
//
// Description:
//  EFI_STATUS LoadStrings(EFI_HANDLE ImageHandle,
// EFI_HII_HANDLE *pHiiHandle) - loads HII string packages associated with
// the specified image and publishes them to the HII database
//
// Input:
//  EFI_HANDLE ImageHandle - Image Handle
//  EFI_HII_HANDLE *pHiiHandle - HII package list handle
//
// Output:
//   EFI_STATUS
//
//<AMI_PHDR_END>
//*************************************************************************
EFI_STATUS Tpm20LoadStrings(
    EFI_HANDLE ImageHandle, EFI_HII_HANDLE *pHiiHandle
)
{
    EFI_STATUS                      Status;
    EFI_HII_PACKAGE_LIST_HEADER     *PackageList;

    //
    // Retrieve HII package list from ImageHandle
    //
    Status = gBS->OpenProtocol (
                 ImageHandle,
                 &gEfiHiiPackageListProtocolGuid,
                 (VOID **) &PackageList,
                 ImageHandle,
                 NULL,
                 EFI_OPEN_PROTOCOL_GET_PROTOCOL
             );
    if (EFI_ERROR (Status))
    {
        DEBUG((DEBUG_ERROR,"gEfiHiiPackageListProtocolGuid protocol is not found\n"));
        return Status;
    }

    Status = gBS->LocateProtocol (
                 &gEfiHiiDatabaseProtocolGuid,
                 NULL,
                 (void **)&HiiDatabase
             );
    if (EFI_ERROR (Status))
    {
        DEBUG((DEBUG_ERROR,"gEfiHiiDatabaseProtocolGuid protocol is not found\n"));
        return Status;
    }

    //
    // Publish HII package list to HII Database.
    //

    Status = HiiDatabase->NewPackageList (
                 HiiDatabase,
                 PackageList,
                 NULL,
                 pHiiHandle
             );
    
    DEBUG((DEBUG_INFO,"NewPackageList status: %r\n",Status));
    return Status;
}


//**********************************************************************
//<AMI_PHDR_START>
//
// Name: doCpuMicrocodeTcgEvent
//
// Description: Measures EV_CPU_MICROCODE event
//
// Input:       IN      Buffer
//              IN      size
//
// Output:      Device path size
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS Tpm2CpuMicrocodeEvent(
    IN EFI_PHYSICAL_ADDRESS  *MCUEntryPoint,
    IN UINTN size )
{
    EFI_STATUS        Status;
    TrEE_EVENT       *Tpm20Event=NULL;
    UINT64           Flags = 0;
    CHAR16              MicroCodeStr[] = L"CPU Microcode";

    DEBUG((DEBUG_INFO, "Tpm2CpuMicrocodeEvent \n"));
        Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
        if(EFI_ERROR(Status)){
            return Status;
        }

        
    Status = gBS->AllocatePool(EfiBootServicesData, (sizeof(TrEE_EVENT_HEADER) + \
                                                    sizeof(UINT32) + sizeof(MicroCodeStr)), (void **)&Tpm20Event);

    if(EFI_ERROR(Status) || Tpm20Event == NULL){
        return EFI_OUT_OF_RESOURCES;
    }
    
    Tpm20Event->Size = sizeof(TrEE_EVENT_HEADER) + sizeof(UINT32) + sizeof(MicroCodeStr);
    
    Tpm20Event->Header.HeaderSize = sizeof(TrEE_EVENT_HEADER);
    Tpm20Event->Header.HeaderVersion = 1;
    Tpm20Event->Header.PCRIndex    = 1;
    Tpm20Event->Header.EventType   = EV_CPU_MICROCODE;
    
    gBS->CopyMem ((UINT32 *)((UINTN)&Tpm20Event->Event[0]),
                  &MicroCodeStr[0],
                  sizeof(MicroCodeStr));

    
    Status = TrEEProtocolInstance->HashLogExtendEvent(TrEEProtocolInstance,
             Flags, (EFI_PHYSICAL_ADDRESS)MCUEntryPoint, size,
             Tpm20Event);
    
    return Status;
}

    
    
#if (defined(MeasureCPUMicrocodeToken) && (MeasureCPUMicrocodeToken == 1))
VOID EFIAPI GetAndHashMcuBuffer(    
        IN      EFI_EVENT                 Event,
        IN      VOID                      *Context)
{
    EFI_STATUS                   Status;
    UINT64                       MicrocodeBuffer;
    UINTN                        MicrocodeSize;
        
    DEBUG((DEBUG_INFO, "GetAndHashMcuBuffer Entry\n"));
            
    
    Status = TpmGetMicrocodeFunc(&MicrocodeBuffer, &MicrocodeSize);
    if(EFI_ERROR(Status)){
        DEBUG((DEBUG_INFO, "Microcode not found Status = %r\n", Status));
        //if not found set callback
        
        return;
    }

    DEBUG((DEBUG_INFO, "Microcode Found TpmGetMicrocodePtr Status = %r \n", Status));
    DEBUG((DEBUG_INFO, "Microcode Found MicrocodeBuffer = %x \n", MicrocodeBuffer));
    DEBUG((DEBUG_INFO, "Microcode Found MicrocodeSize = %x \n", MicrocodeSize));
    
    Status = Tpm2CpuMicrocodeEvent( (EFI_PHYSICAL_ADDRESS *)(UINTN)MicrocodeBuffer, MicrocodeSize );
    
    DEBUG((DEBUG_INFO, "GetAndHashMcuBuffer Tpm2CpuMicrocodeEvent Status = %r \n", Status));
    
    return;
}
#endif

    
VOID HandleTpm20SetupHook(VOID)
{
    UINTN i=0;
    DEBUG((DEBUG_INFO, "HandleTpm20SetupHookEntry\n"));
    for (i = 0; Tpm20HandleSetupFunctions[i] != NULL; i++)
        Tpm20HandleSetupFunctions[i]();
}


VOID EFIAPI Tcg2MeasureSetupEntry(IN EFI_EVENT Event, IN VOID *Context)
{
    Tpm20MeasureActionI("Entering ROM Based Setup", AMI_PCRi_HOST_PLATFORM_CONFIG);
}
    
    
    
VOID HandleTpm20PpiHook(IN EFI_EVENT ev,
                        IN VOID *ctx)
{
    UINTN           i=0;
    EFI_STATUS      Status = EFI_SUCCESS;

    DEBUG((DEBUG_INFO, "HandleTpm20PpiHookEntry\n"));
    DEBUG((DEBUG_INFO, "PpiRequest = %d\n", PpiRequest));
    if (gHiiHandle == NULL)
    {
        Status = Tpm20LoadStrings( gImageHandle, &gHiiHandle );
        if (EFI_ERROR (Status))
        {
            DEBUG((DEBUG_ERROR, "Failed to get the gHiiHandle - %r\n", Status));
        }
    }

    if(PpiRequest >= TCPA_PPIOP_ENABLE_BLOCK_SID_FUNC && \
       PpiRequest <= TCPA_PPIOP_SET_PPREQUIRED_FOR_DISABLE_BLOCK_SID_FUNC_FALSE)
    {
        HandleSIDPpi();
    }else{
        for (i = 0; Tpm20HandlePpiFunctions[i] != NULL; i++){
            Tpm20HandlePpiFunctions[i]();
        }
    }
}

VOID EFIAPI OnTreeProtocolInstall(IN EFI_EVENT ev,
                        IN VOID *ctx)
{
    EFI_STATUS          Status;
    EFI_EVENT           ReadyToBootEvent;
    EFI_EVENT           ExitBSEvent;
    EFI_EVENT           ExitBSEvent2;
    EFI_EVENT           evt;
    static VOID         *regt;
             
     Status = MeasureSecureBootState();
     if (EFI_ERROR (Status))
     {
         TpmDxeReportStatusCode(EFI_ERROR_CODE|EFI_ERROR_MINOR, AMI_SPECIFIC_TPM_ERR_NO_SECBOOT_VAR_SECBOOT_DISABLED | EFI_SOFTWARE_DXE_BS_DRIVER);
         DEBUG ((DEBUG_ERROR, "Measuring secure boot state failed.\n"));
     }
     else
     {
         DEBUG((DEBUG_INFO, "Secure boot state measured.\n"));
     }
     
                 
     Status = EfiCreateEventReadyToBootEx(TPL_CALLBACK,
                                          Tpm20OnReadyToBoot,
                                          NULL,
                                          &ReadyToBootEvent);
     if(EFI_ERROR(Status))return;

     Status = Tpm20MeasurePCIOproms();
     ASSERT( !EFI_ERROR( Status ));

 #if (defined(MeasureCPUMicrocodeToken) && (MeasureCPUMicrocodeToken == 1))
     GetAndHashMcuBuffer(NULL, NULL);
 #endif

     Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  EFI_TPL_NOTIFY,
                  Tpm20OnExitBootServices,
                  NULL,
                  &ExitBSEvent
              );
     if(EFI_ERROR(Status))return;
     
	 
	 Status = gBS->CreateEventEx (
                         EVT_NOTIFY_SIGNAL,
                         TPL_NOTIFY,
                         Tpm20OnExitBootServicesFailed,
                         NULL,
                         &gEventExitBootServicesFailedGuid,
                         &ExitBSEvent2
                         );
     if(EFI_ERROR(Status))return;

     Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                EFI_TPL_CALLBACK,
                                &TCGTpm20HsTiPrepare,
                                0,
                                &evt );

     if(EFI_ERROR(Status))
     {
         DEBUG(( DEBUG_ERROR, "[%d]: Error for Create BDS TCGTpm20HsTiPrepare(...)\n", __LINE__));
     }
     else
     {

         Status = gBS->RegisterProtocolNotify(
                      &gBdsAllDriversConnectedProtocolGuid,
                      evt,
                      &regt );

         if(EFI_ERROR(Status))
         {
             DEBUG(( DEBUG_ERROR, "[%d]: Error for Register BDS TCGTpm20HsTiPrepare(...)\n", __LINE__));
         }
     }
                               
     ASSERT_EFI_ERROR(Status);
     PpiRequest &= 0xFF;
     
     HandleTpm20SetupHook();
}



EFI_STATUS
EFIAPI
Tpm20PlatformEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS          Status;
    EFI_EVENT           ev;
    static VOID         *reg;
    EFI_EVENT           Treeev;
    EFI_EVENT           SidReadyToBootEvent;
    static VOID         *Treereg;
    UINTN               Size = sizeof(PERSISTENT_BIOS_TPM_FLAGS);
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
    EFI_EVENT           VarLockEvent;
    static VOID         *VarLockreg;
#endif
    EFI_EVENT           SetupEntryEvent;
    static EFI_EVENT    EnterSetupEvent;
    VOID                *SetupRegistration = NULL;
    VOID                *SetupEnterNotifyReg = NULL;

        
    
    Status = gRT->GetVariable( L"TPMPERBIOSFLAGS", \
                                    &FlagsStatusguid, \
                                    NULL, \
                                    &Size, \
                                    &TpmNvflags );

     if(EFI_ERROR(Status))
     {
         TpmNvflags.NoPpiProvision = NO_PPI_PROVISION_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForTurnON = (TpmNvflags.NoPpiProvision == 1) ? 0:1;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForTurnOff = (TpmNvflags.NoPpiProvision == 1) ? 0:1;
         TpmNvflags.NoPpiClear = NO_PPI_CLEAR_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForClear = (TpmNvflags.NoPpiClear == 1) ? 0:1;
         TpmNvflags.NoPpiMaintenance = NO_PPI_MAINTENANCE_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForChangeEPS = PPI_REQUIRED_FOR_CHANGE_EPS_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForChangePCRS = PPI_REQUIRED_FOR_CHANGE_PCR_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForEnable_BlockSIDFunc = PPI_REQUIRED_FOR_ENABLE_BLOCK_SID_DEFAULT;
         TpmNvflags.Ppi1_3_Flags.PpRequiredForDisable_BlockSIDFunc = PPI_REQUIRED_FOR_DISABLE_BLOCK_SID_DEFAULT;
         
 #if NVRAM_VERSION > 6
         Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                   &FlagsStatusguid,
                                   EFI_VARIABLE_NON_VOLATILE
                                   | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                   EFI_VARIABLE_RUNTIME_ACCESS,
                                   sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                   &TpmNvflags );

 #else
         Status = TcgSetVariableWithNewAttributes(L"TPMPERBIOSFLAGS",
                                   &FlagsStatusguid,
                                   EFI_VARIABLE_NON_VOLATILE
                                   | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                   sizeof (PERSISTENT_BIOS_TPM_FLAGS),
                                   &TpmNvflags );
 #endif

         if(EFI_ERROR(Status))return Status;
     }
    
    //get PpiRequest
    PpiRequest = ReadPpiRequestEx(&PpiRequestOptionalData);

    DEBUG((DEBUG_INFO, "PpiRequest = %d \n", PpiRequest));
    if(PpiRequest > 0  &&  PpiRequest <= TCPA_PPIOP_VENDOR)
    {
        Tpm20LoadStrings( ImageHandle, &gHiiHandle );
        
    #if TPM_PASSWORD_AUTHENTICATION
            Status = PasswordAuthHelperFunction( );
    #endif

    #if TPM_PASSWORD_AUTHENTICATION
            AuthenticateSet = check_authenticate_set( );
    #endif

            Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                       EFI_TPL_CALLBACK,
                                       HandleTpm20PpiHook,
                                       0,
                                       &ev );

            if(EFI_ERROR(Status))
            {
                return Status;
            }

            Status = gBS->RegisterProtocolNotify(
                         &gBdsAllDriversConnectedProtocolGuid,
                         ev,
                         &reg );
            if(EFI_ERROR(Status))
            {
                return Status;
            }
    }else{
#if defined (CORE_BUILD_NUMBER) && (CORE_BUILD_NUMBER > 0xA) && NVRAM_VERSION > 6
         Status = gBS->CreateEvent (EFI_EVENT_NOTIFY_SIGNAL,
                                    EFI_TPL_CALLBACK,
                                    Tpm20OnVariableLockProtocolGuid,
                                    NULL,
                                    &VarLockEvent);

         if(!EFI_ERROR(Status))
         {
             Status = gBS->RegisterProtocolNotify(
                          &gEdkiiVariableLockProtocolGuid,
                          VarLockEvent,
                          &VarLockreg );
             
             if(EFI_ERROR(Status))
             {
                 return Status;
             }
         }
#endif
         Status = EfiCreateEventReadyToBootEx(TPL_CALLBACK,
                                              SidRequestOnReadyToBoot,
                                              NULL,
                                              &SidReadyToBootEvent);
         if(EFI_ERROR(Status))
         {
             return EFI_SUCCESS;
         }
         
         Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                    EFI_TPL_CALLBACK,
                                    Tcg2MeasureSetupEntry,
                                    0,
                                    &EnterSetupEvent );
         
          if(!EFI_ERROR(Status))
          {
              Status = gBS->RegisterProtocolNotify(
                           &gAmiTseEventAfterBootGuid,
                           EnterSetupEvent,
                           &SetupRegistration );
              
              if(EFI_ERROR(Status))
              {
                  return Status;
              }
          }
             
         //Install callback on entering into Setup 
          Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                              EFI_TPL_CALLBACK,
                                              Tcg2MeasureSetupEntry,
                                              0,
                                              &SetupEntryEvent );
                   
          if(!EFI_ERROR(Status))
          {
              Status = gBS->RegisterProtocolNotify(
                             &gAmiTseSetupEnterGuid,
                             SetupEntryEvent,
                             &SetupEnterNotifyReg );
                
              if(EFI_ERROR(Status))
              {
                  return Status;
              }
          }
    }

    Status = gBS->LocateProtocol(&gEfiTrEEProtocolGuid, NULL, (void **)&TrEEProtocolInstance);
    if(EFI_ERROR(Status)){
        
        Status = gBS->CreateEvent( EFI_EVENT_NOTIFY_SIGNAL,
                                   EFI_TPL_CALLBACK,
                                   OnTreeProtocolInstall,
                                   0,
                                   &Treeev );

        if(EFI_ERROR(Status))
        {
            return EFI_SUCCESS;
        }

        Status = gBS->RegisterProtocolNotify(
                     &gEfiTrEEProtocolGuid,
                     Treeev,
                     &Treereg );
        
        if(EFI_ERROR(Status))
        {
            return EFI_SUCCESS;
        }
    }else{
        OnTreeProtocolInstall(NULL, NULL);
    }

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
