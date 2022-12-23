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
#include <Token.h>
#include <TpmSmbios.h>
#include <Protocol/TcgPlatformSetupPolicy.h>
#include "AmiTcg/TcmPc.h"
#include <Library/UefiRuntimeServicesTableLib.h>

extern EFI_GUID gTpm20HobGuid;
extern EFI_GUID gAmiTcg2InfoProtocolGuid;
extern EFI_GUID gTcgInternalflagGuid;

VOID* Tpm20LocateATcgHob(
    UINTN                   NoTableEntries,
    EFI_CONFIGURATION_TABLE *ConfigTable,
    EFI_GUID                *HOB_guid );

///
/// TPM Device (Type 43) data
///
GLOBAL_REMOVE_IF_UNREFERENCED AMI_SMBIOS_TABLE_TYPE43 SmbiosTableType43Data = {
  { EFI_SMBIOS_TYPE_TPM_DEVICE, sizeof (AMI_SMBIOS_TABLE_TYPE43), 0 },
  0x00000000, 		///< VendorId
  TO_BE_FILLED,   	///< MajorSpecVer
  TO_BE_FILLED,         ///< MinorSpecVer
  0x00000000,         	///< FirmwareVer1
  0x00000000,           ///< FirmwareVer2
  2,         		///< Description
  {                     ///< Characteristics
    0,                  ///< Bit 0-1  Reserved1                 :2
    0,                  ///< Bit 02 - Unsupport                 :1
    0,                  ///< Bit 03 - ConfigFirmware   		:1
    0,                  ///< Bit 04 - ConfigSoftware            :1
    0,                  ///< Bit 05 - ConfigOem                 :1
    0,                  ///< Bit 6-63 - Reserved 		:58
  },
  0x5A5A5A5A,           ///< OemDefined
};

//
// Supported TPM vendor ID string array
//
TPM_VENDOR_STRING  TpmVendorArray[17]=
{
    {AMD_CAP_ID,"AMD\0"},
    {ATMEL_CAP_ID,"ATMEL\0"},
    {BROADCOM_CAP_ID,"BROADCOM\0"},
    {IBM_CAP_ID,"IBM\0"},
    {INFINEON_CAP_ID,"INFINEON\0"},
    {INTEL_CAP_ID,"INTEL\0"},
    {LENOVO_CAP_ID,"LENOVO\0"},
    {NATIONAL_SEMI_CAP_ID,"NATIONAL SEMI\0"},
    {NATIONZ_CAP_ID,"NATIONZ\0"},
    {NUVOTON_CAP_ID,"NUVOTON\0"},
    {QUALCOMM_CAP_ID,"QUALCOMM\0"},
    {SMSC_CAP_ID,"SMSC\0"},
    {ST_CAP_ID,"ST\0"},
    {SAMSUNG_CAP_ID,"SAMSUNG\0"},
    {SINOSUN_CAP_ID,"SINOSUN\0"},
    {TI_CAP_ID,"TI\0"},
    {WINBOND_CAP_ID,"WINBOND\0"}
};

EFI_SMBIOS_HANDLE mSmbiosType43Handle = 0;
Tpm20DeviceHob  *TpmSupport = NULL;

//
// Module-wide global variables
//
VOID  			      *mSmbiosRegistration;
VOID  			      *mTrEERegistration;
VOID  			      *mTcgRegistration;
EFI_SMBIOS_PROTOCOL 	      *SmbiosProtocol = NULL;
EFI_TREE_PROTOCOL             *TrEEProtocol = NULL;
EFI_TCG_PROTOCOL              *TcgProtocol = NULL;

static AMI_TCG2_TPM_INFO_STRUCT     InternalInfo;
static EFI_HANDLE                   gHandle;


void printbuffer(UINT8 *Buffer, UINTN BufferSize)
{
    UINTN i=0;
    UINTN j=0;

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
  This function is to get GetTpm20Hob 

  @param[in]  NULL
  @retval     TRUE  TPM2.0
**/
EFI_STATUS GetTpm20Hob()
{
  
  if(TpmSupport == NULL) {
    TpmSupport = Tpm20LocateATcgHob( gST->NumberOfTableEntries,gST->ConfigurationTable,&gTpm20HobGuid);
  }

  if(TpmSupport != NULL)
  {
    DEBUG ((DEBUG_INFO, "TpmSupport->Tpm20DeviceState %X\n",TpmSupport->Tpm20DeviceState));
    DEBUG ((DEBUG_INFO, "TpmSupport->InterfaceType %X\n",TpmSupport->InterfaceType));
    DEBUG ((DEBUG_INFO, "TpmSupport->Tpm2FWersion1 %X\n",TpmSupport->Tpm2FWersion1));
    DEBUG ((DEBUG_INFO, "TpmSupport->Tpm2FWersion2 %X\n",TpmSupport->Tpm2FWersion2));	      
    DEBUG ((DEBUG_INFO, "TpmSupport->Tpm2manufacturer %X\n",TpmSupport->Tpm2manufacturer));

    return EFI_SUCCESS;
    
  }
  
  return EFI_UNSUPPORTED;
}

/**
  This function gets registered as a callback to perform 
																																																
  @param[in]  Event     - A pointer to the Event that triggered the callback.
  @param[in]  Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
TpmDxeSmbiosCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS    	  Status;
  UINTN                   Size;
  EFI_SMBIOS_TABLE_HEADER *Record;
  CHAR8			  *TpmFamilyString;
  CHAR8			  *TpmString;
  EFI_SMBIOS_HANDLE       SmbiosHandle;
  CHAR8                   *StringPtr;  
  UINTN                   Str1 = 0;
  UINTN                   Str2 = 0;
  UINTN                   i = 0;
  
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }
  
  if (SmbiosProtocol == NULL) {
	  
    Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &SmbiosProtocol);
    if ( EFI_ERROR( Status ))
    {
      DEBUG ((DEBUG_ERROR, "Error locating gEfiSmbiosProtocolGuid. Status = %r\n", Status));	  	  
      return;
    } 
  }
  
  DEBUG ((DEBUG_INFO, "Smbios MajorVersion = %x\n", SmbiosProtocol->MajorVersion));
  DEBUG ((DEBUG_INFO, "Smbios MinorVersion = %x\n", SmbiosProtocol->MinorVersion));
  //
  // TPM type support start for smbios3.1
  //
#if CHECK_TPM_SMBIOS_VERSION_SUPPORT  
  if ((SmbiosProtocol->MajorVersion <= 3)&&(SmbiosProtocol->MinorVersion < 1)) return;
#endif
  
  // Check if this type already existing
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  do {
    
    Status = SmbiosProtocol->GetNext (SmbiosProtocol, &SmbiosHandle, NULL, &Record, NULL);
    
    if (EFI_ERROR(Status)) {
      break;
    }
    
    if (Record->Type == EFI_SMBIOS_TYPE_TPM_DEVICE) {  
      Status = SmbiosProtocol->Remove (SmbiosProtocol,SmbiosHandle);
      if(EFI_ERROR(Status))
      {
          DEBUG ((DEBUG_INFO, "SmbiosProtocol->Remove Status = %r \n", Status));
      }
      break;
    }
  } while (Record->Type != EFI_SMBIOS_TYPE_TPM_DEVICE);

  if (PcdGetBool(PcdTpmSmbiosCharacteristicSupport)){
    SmbiosTableType43Data.Characteristics.Unsupport = 0;
  }
  
  if (PcdGetBool(PcdTpmSmbiosConfigFirmware)){
    SmbiosTableType43Data.Characteristics.ConfigFirmware = 1;
  }

  if (PcdGetBool(PcdTpmSmbiosConfigSoftware)){
    SmbiosTableType43Data.Characteristics.ConfigSoftware = 1;
  }
  
  if (PcdGetBool(PcdTpmSmbiosConfigOem)){
    SmbiosTableType43Data.Characteristics.ConfigOem = 1;
  }
  
  SmbiosTableType43Data.OemDefined = PcdGet32 (PcdTpmSmbiosOemDefined);
  
  DEBUG ((DEBUG_INFO, "VendorId %x\n",SmbiosTableType43Data.VendorId));
  DEBUG ((DEBUG_INFO, "MajorSpecVer %x\n",SmbiosTableType43Data.MajorSpecVer));
  DEBUG ((DEBUG_INFO, "MinorSpecVer %x\n",SmbiosTableType43Data.MinorSpecVer));  
  DEBUG ((DEBUG_INFO, "FirmwareVer1 %x\n",SmbiosTableType43Data.FirmwareVer1));  
  DEBUG ((DEBUG_INFO, "FirmwareVer2 %x\n",SmbiosTableType43Data.FirmwareVer2));    
  DEBUG ((DEBUG_INFO, "Characteristics.Unsupport %x\n",SmbiosTableType43Data.Characteristics.Unsupport));	  
  DEBUG ((DEBUG_INFO, "Characteristics.ConfigFirmware %x\n",SmbiosTableType43Data.Characteristics.ConfigFirmware));	  
  DEBUG ((DEBUG_INFO, "Characteristics.ConfigSoftware %x\n",SmbiosTableType43Data.Characteristics.ConfigSoftware));	  
  DEBUG ((DEBUG_INFO, "Characteristics.ConfigOem %x\n",SmbiosTableType43Data.Characteristics.ConfigOem));	  
  DEBUG ((DEBUG_INFO, "OemDefined %x\n",SmbiosTableType43Data.OemDefined));
  DEBUG ((DEBUG_INFO, "Description %x\n",SmbiosTableType43Data.Description));	  
  
  ///
  /// Calculate the total size of the full record
  ///
  Size = SmbiosTableType43Data.Hdr.Length;
  
  TpmFamilyString = "\0";
  if(TpmSupport->Tpm20DeviceState == 0) {
      TpmFamilyString = "TPM 1.2\0";
  }else if(TpmSupport->Tpm20DeviceState == 1){
      TpmFamilyString = "TPM 2.0\0";
  }

  Str1 = AsciiStrLen(TpmFamilyString);
  Size += (Str1+1);

  TpmString = "\0";
  for(i=0; i<(sizeof(TpmVendorArray)/sizeof(TPM_VENDOR_STRING)); i++) {
    
    if(TpmVendorArray[i].ID == SwapBytes32(SmbiosTableType43Data.VendorId)) {
      TpmString = TpmVendorArray[i].String;
    }

  }
  
  Str2 = AsciiStrLen(TpmString);
  Size += Str2;
  
  DEBUG ((DEBUG_INFO, "Final table Size %x\n",Size));
  
  ///
  /// Initialize the full record
  ///
  Record = (EFI_SMBIOS_TABLE_HEADER *) AllocateZeroPool (Size+2);
    
  if (Record == NULL) {
      return;
  }
  
  CopyMem(Record, (UINT8 *)&SmbiosTableType43Data, SmbiosTableType43Data.Hdr.Length);
  
  ///
  /// Copy the strings to the end of the record
  ///
  StringPtr = ((CHAR8 *)Record) + SmbiosTableType43Data.Hdr.Length;
  
  if (Str1 != 0) {
    CopyMem(StringPtr, (UINT8 *)TpmFamilyString, Str1);
    StringPtr += (Str1+1);
  }
  
  if (Str2 != 0) {
    CopyMem(StringPtr, (UINT8 *)TpmString, Str2);
  }
  
  //printbuffer((UINT8 *)Record,Size);

  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  Status = SmbiosProtocol->Add (SmbiosProtocol, NULL, &SmbiosHandle, Record);

  DEBUG ((DEBUG_INFO, "SmbiosProtocol->Add Status %r\n",Status));
  
  ASSERT_EFI_ERROR (Status);
  
  FreePool (Record);
    
  return;
}



/**
  This function intializes info with the platform TPM information. 
  See AMI_TCG2_TPM_INFO_STRUCT.
  Returns  EFI_SUCCESS, EFI_INVALID_PARAMETER, See AllocatePool. 
  
  @param[in]  AMI_TCG2_INFO_PROTOCOL
  @param[out] AMI_TCG2_TPM_INFO_STRUCT
  
  
**/

EFI_STATUS
EFIAPI
getAmiTpmInfoStruct (
    IN CONST AMI_TCG2_INFO_PROTOCOL       *This,
    IN OUT AMI_TCG2_TPM_INFO_STRUCT       **info
)
{
    EFI_STATUS Status;
    
    if(This == NULL || info == NULL) return EFI_INVALID_PARAMETER;
    
    Status = gBS->AllocatePool(EfiBootServicesData, sizeof(AMI_TCG2_TPM_INFO_STRUCT), (void **)info);
    if(EFI_ERROR(Status))return Status;
    
    gBS->CopyMem(*info, &InternalInfo, InternalInfo.Size);
    return Status;
}

AMI_TCG2_INFO_PROTOCOL AmiTcg2InfoProtocol =
{   
   0x1,
   getAmiTpmInfoStruct
};

/**
  This function installs AMI_TCG2_INFO_PROTOCOL
                                                                                                                                                                                                
  @param[in]  NONE
  @param[out] NONE
**/
VOID InstallAmiTcg2InfoProtocol()
{
    gBS->InstallProtocolInterface (&gHandle,
                        &gAmiTcg2InfoProtocolGuid, EFI_NATIVE_INTERFACE,
                        &AmiTcg2InfoProtocol);
}


/**
  This function register callback event to install TPM smbios type
																																																
  @param[in]  NONE
  @param[out] NONE
**/
VOID InstallTpmSmbiosTable()
{
  EFI_STATUS    Status;
  EFI_EVENT     CallbackEvent;
  
  //
  // If EfiSmbiosProtocol already installed, invoke the callback directly.
  //
  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &SmbiosProtocol);
	  
  if (!EFI_ERROR (Status)) {
    TpmDxeSmbiosCallback (NULL,NULL);
  } else {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TpmDxeSmbiosCallback,
                    NULL,
                    &CallbackEvent
                    );
    ASSERT_EFI_ERROR (Status);

    Status = gBS->RegisterProtocolNotify (
                    &gEfiSmbiosProtocolGuid,
                    CallbackEvent,
                    &mSmbiosRegistration
                    );
    ASSERT_EFI_ERROR (Status);

  }	
}

/**
  This function gets TPM_CAP_VERSION_INFO from TPM 1.2 device  
																																																
  @param[in]  EFI_TCG_PROTOCOL
  @param[out] TPM_CAP_VERSION_INFO
**/
TPM12_CapabilitiesVersionInfo Read_TPM_CapVersionInfo(
    IN EFI_TCG_PROTOCOL* tcg )
{

  TPM12_CapabilitiesVersionInfo  *CapVerInfo = NULL;
  EFI_STATUS                     Status;
  TPM_GetCapabilities_Input      cmdGetCap;
  static UINT8                   result[0x100];
  UINT32		         Data32;

  cmdGetCap.Tag         = SwapBytes16( TPM_TAG_RQU_COMMAND );
  cmdGetCap.ParamSize   = SwapBytes32( sizeof (cmdGetCap));
  cmdGetCap.CommandCode = SwapBytes32( TPM_ORD_GetCapability );
  cmdGetCap.CommandCode = SwapBytes32( TPM_ORD_GetCapability );
  cmdGetCap.caparea     = SwapBytes32( TPM_CAP_VERSION_VAL );
  cmdGetCap.subCapSize  = SwapBytes32( 4 ); // subCap is always 32bit long

  Status = tcg->PassThroughToTpm( tcg,
                                  sizeof (cmdGetCap),
                                  (UINT8*)&cmdGetCap,
                                  sizeof (result),
                                  result );
    
  CapVerInfo = (TPM12_CapabilitiesVersionInfo*)result;
    
//  printbuffer(result,0x100);

    
  if ( EFI_ERROR(Status) || ( SwapBytes32(CapVerInfo->RetCode)!=0)) {
	    
    DEBUG((DEBUG_ERROR, "(TPM Error) Status: %r; RetCode: %x.\n", \
                 Status, \
                 SwapBytes32(CapVerInfo->RetCode) ));
    
    DEBUG((DEBUG_ERROR, "RetCode %x\n",CapVerInfo->RetCode));
    return *CapVerInfo;
  }
        
  Data32 = SwapBytes32(CapVerInfo->Version);    
  CapVerInfo->Version = Data32;    
        
  DEBUG((DEBUG_INFO, "Version %x\n",CapVerInfo->Version));        
  DEBUG((DEBUG_INFO, "VendorId %x\n",CapVerInfo->VendorId));    
    
  return *CapVerInfo;
}



/**
  This function gets TPM_CAP_VERSION_INFO from TPM 1.2 device  
                                                                                                                                                                                                
  @param[in]  EFI_TCG_PROTOCOL
  @param[out] TPM_CAP_VERSION_INFO
**/
TPM12_CapabilitiesVersionInfo Read_TCM_CapVersionInfo(
    IN EFI_TCG_PROTOCOL* tcg )
{

  TPM12_CapabilitiesVersionInfo  *CapVerInfo = NULL;
  EFI_STATUS                     Status;
  TPM_GetCapabilities_Input      cmdGetCap;
  static UINT8                   result[0x100];
  UINT32                 Data32;

  cmdGetCap.Tag         = SwapBytes16( TPM_TAG_RQU_COMMAND );
  cmdGetCap.ParamSize   = SwapBytes32( sizeof (cmdGetCap));
  cmdGetCap.CommandCode = SwapBytes32( TCM_ORD_GetCapability );
  cmdGetCap.CommandCode = SwapBytes32( TCM_ORD_GetCapability );
  cmdGetCap.caparea     = SwapBytes32( TPM_CAP_VERSION_VAL );
  cmdGetCap.subCapSize  = SwapBytes32( 4 ); // subCap is always 32bit long

  Status = tcg->PassThroughToTpm( tcg,
                                  sizeof (cmdGetCap),
                                  (UINT8*)&cmdGetCap,
                                  sizeof (result),
                                  result );
    
  CapVerInfo = (TPM12_CapabilitiesVersionInfo*)result;
    
//  printbuffer(result,0x100);
    
  if ( EFI_ERROR(Status) || ( SwapBytes32(CapVerInfo->RetCode)!=0)) {
        
    DEBUG((DEBUG_ERROR, "(TPM Error) Status: %r; RetCode: %x.\n", \
                 Status, \
                 SwapBytes32(CapVerInfo->RetCode) ));
    
    DEBUG((DEBUG_ERROR, "RetCode %x\n",CapVerInfo->RetCode));
    return *CapVerInfo;
  }
        
  Data32 = SwapBytes32(CapVerInfo->Version);    
  CapVerInfo->Version = Data32;    
         
  DEBUG((DEBUG_INFO, "Version %x\n",CapVerInfo->Version));        
  DEBUG((DEBUG_INFO, "VendorId %x\n",CapVerInfo->VendorId));    
    
  return *CapVerInfo;
}



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   read_TPM_capabilities
//
// Description: Executes TPM operation to read capabilities
//
// Input:       IN EFI_TCG_PROTOCOL* tcg
//
// Output:      TPM capabilities structure
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS read_TPM_capabilities(
    IN EFI_TCG_PROTOCOL* tcg, TPM_Capabilities_PermanentFlag *cap )
{
    EFI_STATUS                     Status;
    TPM_GetCapabilities_Input      cmdGetCap;

    cmdGetCap.Tag         = SwapBytes16( TPM_TAG_RQU_COMMAND );
    cmdGetCap.ParamSize   = SwapBytes32( sizeof (cmdGetCap));
    
    if(cap == NULL)return EFI_INVALID_PARAMETER;

    if(IsTcmSupportType())
    {
        cmdGetCap.CommandCode = SwapBytes32( TCM_ORD_GetCapability );
        cmdGetCap.caparea     = SwapBytes32( TCM_CAP_FLAG );
        cmdGetCap.subCap      = SwapBytes32( TCM_CAP_FLAG_PERMANENT );
    }
    else
    {
        cmdGetCap.CommandCode = SwapBytes32( TPM_ORD_GetCapability );
        cmdGetCap.caparea     = SwapBytes32( TPM_CAP_FLAG );
        cmdGetCap.subCap      = SwapBytes32( TPM_CAP_FLAG_PERMANENT );
    }

    cmdGetCap.subCapSize  = SwapBytes32( 4 ); // subCap is always 32bit long

    Status = tcg->PassThroughToTpm( tcg,
                                    sizeof (cmdGetCap),
                                    (UINT8*)&cmdGetCap,
                                    sizeof (TPM_Capabilities_PermanentFlag),
                                    (UINT8 *)cap );

    if(EFI_ERROR(Status))return Status;

    DEBUG((DEBUG_INFO,
           "GetCapability: %r; size: %x; retCode:%x; tag:%x; bytes %08x\n", Status,
           SwapBytes32(cap->ParamSize ), SwapBytes32(cap->RetCode ),
           (UINT32) SwapBytes16(cap->tag ), SwapBytes32( *(UINT32*)&cap->disabled )));
    
    return Status;
}



/**
  This function gets registered as a callback to perform
																																																
  @param[in]  Event     - A pointer to the Event that triggered the callback.
  @param[in]  Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
TpmDxeTcgCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS        		Status;
  TPM12_CapabilitiesVersionInfo	CapVersionInfo;
  TPM_Capabilities_PermanentFlag TpmPermFlags;
  AMITCGSETUPINFOFLAGS       SetupInfo;
	    
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  DEBUG ((DEBUG_INFO, "TpmDxeTcgCallback\n"));
    
  //
  // If gEfiTrEEProtocolGuid already installed, invoke the callback directly.
  //
  if (TcgProtocol == NULL) {
    Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &TcgProtocol);
    if ( EFI_ERROR( Status )) {
        DEBUG ((DEBUG_ERROR, "Error locating gEfiTcgProtocolGuid. Status = %r\n", Status));	  	  
        return;
    } 
  }
  
  //Read_TCM_CapVersionInfo
  if(IsTcmSupportType())
  {
      CapVersionInfo = Read_TCM_CapVersionInfo(TcgProtocol);
  }else{
      CapVersionInfo = Read_TPM_CapVersionInfo(TcgProtocol);
  }
  
  if(CapVersionInfo.RetCode != 0) return;
  
  gBS->SetMem(&InternalInfo, sizeof(AMI_TCG2_TPM_INFO_STRUCT), 0);
  
  InternalInfo.Tpm2Vendor       = CapVersionInfo.VendorId;
  
  Status = read_TPM_capabilities(TcgProtocol, &TpmPermFlags);
  
  if(EFI_ERROR(Status)){
      return;  //don't install smbios table
  }
  
  InternalInfo.TpmState         =  (TpmPermFlags.disabled == 1)?0:1;
  
  if(IsTcmSupportType())
  {
      InternalInfo.TpmDeviceType    = 3; //TCM 1.0
  }else{
      InternalInfo.TpmDeviceType    = 1; //TPM 1.2
  }
  
  InternalInfo.TpmFwUpdateInterface = 0;
  
  InternalInfo.TpmFwVersion1    = CapVersionInfo.Version;
  InternalInfo.TpmFwVersion2    = 0;
  
  if(IsTcmSupportType())
  {
      InternalInfo.TpmPCRBanks      = BIT1;
  }else{
      InternalInfo.TpmPCRBanks      = BIT0; //SHA-1
  }
  SetupInfo.TpmManufacturer = CapVersionInfo.VendorId;
  SetupInfo.TpmFwVersion = CapVersionInfo.Version;
  Status = gRT->SetVariable( L"Tpm12VersionInfo", \
                             &gTcgInternalflagGuid, \
                             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE, \
                             sizeof(AMITCGSETUPINFOFLAGS), \
                             &SetupInfo);
  if(EFI_ERROR(Status)){
      DEBUG(( DEBUG_INFO," Unable to Set TPM 1.2 Setup Struct \n"));
  }
  
  if (PcdGetBool(PcdTpmSmbiosConfigFirmware))
  {
      InternalInfo.TpmFwUpdateInterface = 1;  //firmware update
      
  }else if(PcdGetBool(PcdTpmSmbiosConfigOem))
  {
      InternalInfo.TpmFwUpdateInterface = 3;  //OEM defined
      
  }else if(PcdGetBool(PcdTpmSmbiosConfigSoftware))
  {
      InternalInfo.TpmFwUpdateInterface = 2;  //software update eg: Via BIOS setup
  }
  
  InternalInfo.Size = sizeof(AMI_TCG2_TPM_INFO_STRUCT);
  InstallAmiTcg2InfoProtocol();     //install info protocol
    
  // The smbios only specifies TPM1.2 or TPM2.0
  if(IsTcmSupportType())
  {
    return;
  }
  
  //Update Offset 08h - 09h 
  SmbiosTableType43Data.MajorSpecVer = TPM_1_2_MAJOR_SPEC;
  SmbiosTableType43Data.MinorSpecVer = TPM_1_2_MINOR_SPEC;
    
  //Update Offset 0Ah 
  SmbiosTableType43Data.FirmwareVer1 = CapVersionInfo.Version;
    
  //Update Offset 0Eh 
  SmbiosTableType43Data.FirmwareVer2 = 0;
  
  SmbiosTableType43Data.VendorId = CapVersionInfo.VendorId;
  
  InstallTpmSmbiosTable();
  return;
}

/**
  This function gets registered as a callback to perform
																																																
  @param[in]  Event     - A pointer to the Event that triggered the callback.
  @param[in]  Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
TpmDxeTrEECallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS        		Status;
  TREE_BOOT_SERVICE_CAPABILITY  ProtocolCapability;
  TCG_PLATFORM_SETUP_PROTOCOL  *ProtocolInstance;
  UINT32                        Data32 = 0;
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  DEBUG ((DEBUG_INFO, "TpmDxeTrEECallback\n"));

  //
  // If gEfiTrEEProtocolGuid already installed, invoke the callback directly.
  //
  if (TrEEProtocol == NULL) {
    Status = gBS->LocateProtocol (&gEfiTrEEProtocolGuid, NULL, (VOID **) &TrEEProtocol);
    if ( EFI_ERROR( Status ))
    {
      DEBUG ((DEBUG_ERROR, "Error locating gEfiTrEEProtocolGuid. Status = %r\n", Status));	  	  
      return;
    } 
  }
  
  Status = gBS->LocateProtocol (&gTcgPlatformSetupPolicyGuid,  NULL, (void **)&ProtocolInstance);
  if (EFI_ERROR (Status))
  {
      return;
  }
  
  if ( EFI_ERROR( GetTpm20Hob() )) {
      DEBUG ((DEBUG_ERROR, "Error GetTpm20Hob. Status = %r\n", Status));	  	  
      return;
  }

  ProtocolCapability.Size = sizeof(TREE_BOOT_SERVICE_CAPABILITY);
  
  Status = TrEEProtocol->GetCapability(TrEEProtocol, &ProtocolCapability);
  
  if ( EFI_ERROR( Status )) {
    DEBUG ((DEBUG_ERROR, "Error GetCapability. Status = %r\n", Status));	  	  
    return;
  }
  DEBUG ((DEBUG_INFO, "Size = %x\n", ProtocolCapability.Size));
  DEBUG ((DEBUG_INFO, "StructureVersion.Major = %x\n", ProtocolCapability.StructureVersion.Major));
  DEBUG ((DEBUG_INFO, "StructureVersion.Minor = %x\n", ProtocolCapability.StructureVersion.Minor));
  DEBUG ((DEBUG_INFO, "ProtocolVersion.Major = %x\n", ProtocolCapability.ProtocolVersion.Major));
  DEBUG ((DEBUG_INFO, "ProtocolVersion.Minor = %x\n", ProtocolCapability.ProtocolVersion.Minor));
  DEBUG ((DEBUG_INFO, "ProtocolCapability.ManufacturerID = %x\n", ProtocolCapability.ManufacturerID));

 
  InternalInfo.Tpm2Vendor       = ProtocolCapability.ManufacturerID;
  InternalInfo.TpmDeviceType    = 2; //TPM 2.0
  InternalInfo.TpmFwUpdateInterface = 0;
     
  InternalInfo.TpmFwVersion1    = TpmSupport->Tpm2FWersion1;
  InternalInfo.TpmFwVersion2    = TpmSupport->Tpm2FWersion2;
      
  InternalInfo.TpmPCRBanks      = (UINT16)ProtocolInstance->ConfigFlags.PcrBanks; //SHA-1
    
  if (PcdGetBool(PcdTpmSmbiosConfigFirmware))
  {
      InternalInfo.TpmFwUpdateInterface = 1;  //firmware update
      
  }else if(PcdGetBool(PcdTpmSmbiosConfigOem))
  {
      InternalInfo.TpmFwUpdateInterface = 3;  //OEM defined
      
  }else if(PcdGetBool(PcdTpmSmbiosConfigSoftware))
  {
      InternalInfo.TpmFwUpdateInterface = 2;  //software update eg: Via BIOS setup
  }
  
  InternalInfo.Size = sizeof(AMI_TCG2_TPM_INFO_STRUCT);
  
  InternalInfo.TpmState = (ProtocolInstance->ConfigFlags.StorageHierarchy == 0 && \
                           ProtocolInstance->ConfigFlags.EndorsementHierarchy == 0)? 0:1;
  
  InstallAmiTcg2InfoProtocol();     //install info protocol
         
  // The smbios only specifies TPM1.2 or TPM2.0
  if(IsTcmSupportType())
  {
    return;
  }
  
  //Update Offset 08h - 09h 
  SmbiosTableType43Data.MajorSpecVer = TPM_2_0_MAJOR_SPEC;
  SmbiosTableType43Data.MinorSpecVer = TPM_2_0_MINOR_SPEC;
   
  //Update Offset 0Ah 
  SmbiosTableType43Data.FirmwareVer1 = TpmSupport->Tpm2FWersion1;
   
  //Update Offset 0Eh 
  SmbiosTableType43Data.FirmwareVer2 = TpmSupport->Tpm2FWersion2;
   
  Data32 = SwapBytes32(ProtocolCapability.ManufacturerID);
  
  SmbiosTableType43Data.VendorId = Data32;
  InstallTpmSmbiosTable();
  return;
}

/**
  Entry point for the driver.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
TpmSmbiosDxeEntry (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_EVENT     TrEECallbackEvent;
  EFI_EVENT     TcgCallbackEvent;
  
  DEBUG ((DEBUG_INFO, "TpmSmbiosDxeEntry\n"));
  
  gHandle = ImageHandle;
  
  //
  // If gEfiTrEEProtocolGuid already installed, invoke the callback directly.
  //
  Status = gBS->LocateProtocol (&gEfiTrEEProtocolGuid, NULL, (VOID **) &TrEEProtocol);
  if (!EFI_ERROR (Status)) {
    TpmDxeTrEECallback (NULL,NULL);
  } else {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TpmDxeTrEECallback,
                    NULL,
                    &TrEECallbackEvent
                    );
    
    if(EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_INFO, "TrEECallbackEvent Status = %r \n", Status));
        return EFI_SUCCESS;
    }

    Status = gBS->RegisterProtocolNotify (
                    &gEfiTrEEProtocolGuid,
                    TrEECallbackEvent,
                    &mTrEERegistration
                    );
    
    if(EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_INFO, "TrEECallbackEvent Status = %r \n", Status));
        return EFI_SUCCESS;
    }

  }
  //
  // If gEfiTcgProtocolGuid already installed, invoke the callback directly.
  //
  Status = gBS->LocateProtocol (&gEfiTcgProtocolGuid, NULL, (VOID **) &TcgProtocol);
  if (!EFI_ERROR (Status)) {
    TpmDxeTcgCallback (NULL,NULL);
  } else {
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    TpmDxeTcgCallback,
                    NULL,
                    &TcgCallbackEvent
                    );
    if(EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_INFO, "TcgCallbackEvent Status = %r \n", Status));
        return EFI_SUCCESS;
    }

    Status = gBS->RegisterProtocolNotify (
                    &gEfiTcgProtocolGuid,
                    TcgCallbackEvent,
                    &mTcgRegistration
                    );
    
    if(EFI_ERROR(Status))
    {
        DEBUG ((DEBUG_INFO, "TcgCallbackEvent Status = %r \n", Status));
        return EFI_SUCCESS;
    }
  }

  return EFI_SUCCESS;
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
