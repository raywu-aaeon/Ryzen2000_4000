//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file HddSecurity.c
    HDD Security SAT3 Protocol Support Implementation.

**/

#include <HddSecurity.h>

AMI_HDD_SECURITY_INIT_PROTOCOL *gHddSecurityInitProtocol;

const CHAR16 *gOemMasterPasswordTag = HDD_CONVERT_TO_WSTRING(OEM_MASTER_PASSWORD_TAG);
const CHAR16 *gDefaultMasterPasswordTag = HDD_CONVERT_TO_WSTRING(DEFAULT_MASTER_PASSWORD_TAG);

BOOLEAN gMasterPasswordEnable = MASTER_PASSWORD_ENABLE;
EFI_GUID gIdeSecurityPwNvguid = IDE_SECURITY_PWNV_GUID;

extern BOOLEAN gSmmHddSecuritySupport;

/** @internal
    Encodes/Decodes Password with encryption key.

    @param InputString     Password before Encoding/Decoding with encryption key.
    @param OutputString    Password after Encoding/Decoding with encryption key.
    @param StringLen       Length of the Password.

    @return VOID
    
    @note 
        1. HDD_PWD_ENCRYPTION_KEY is used to encrypt/decrypt the password.

    @endinternal
**/
VOID
EncodeDecodePassword (
    IN  UINT8           *InputString,
    OUT UINT8           *OutputString,
    IN  UINT32          StringLength
)
{
    UINT8               *Key;
    UINT32              Index;
    UINT32              KeyIndex;
    UINT32              KeyLength;


    if ((InputString == NULL) || (StringLength == 0)) {
        return;
    }

    KeyLength = (UINT32)(AsciiStrLen(HDD_PWD_ENCRYPTION_KEY));
    
    Key = AllocateZeroPool (KeyLength);
    if (Key == NULL) {
        return;
    }

    CopyMem (Key, HDD_PWD_ENCRYPTION_KEY, KeyLength);

    for (Index = 0, KeyIndex = 0; Index < StringLength; Index++, KeyIndex++) {
        if (KeyIndex == (KeyLength - 1)) {
            KeyIndex = 0;
        }
        OutputString[Index] = (UINT8)(InputString[Index] ^ Key[KeyIndex]);
    }

    FreePool(Key);
}

/** @internal
    Sets default Master Password with disabled revision code.
    SECURITY_SET_PASSWORD(Command code : 0xF1) security command
    used to set default master password.

    @param *This          Pointer to AmiHddSecurityProtocol
     @param Control       Bit 0 : 0/1 User/Master Password
                          Bit 8 : 0/1 High/Maximum Security level
    @param *Buffer        Pointer to password buffer which will be used when 
                          sending SECURITY_DISABLE_PASSWORD command.
    @param  RevisionCode (Valid when Control Bit 0 = 1 of Master Password)

    @retval EFI_SUCCESS   Password set
    @retval EFI_ERROR     Error in setting Password

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
     32 bytes long,pad it with zeros to create a buffer of 32 bytes.

      2. If a MasterPassword with a valid Revision code already exists, a new
     MasterPassword with a different revision code cannot be installed.
     MasterPassword needs to be unlocked, disabled and then a new password
     can be installed.

    @endinternal
**/
EFI_STATUS
SecuritySetDefaultMasterPassword (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer,
    IN UINT16                      RevisionCode
)
{
    EFI_STATUS                  Status;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterfaceType;


#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    UINT32     HddDataId        = 0;
#endif

    if ((BusInterfaceType < AmiStorageInterfaceIde) || 
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_UNSUPPORTED;
    }

    Control &= 0x0101;          // Bit0 and Bit 8 are valid

    // Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
        case AmiStorageInterfaceAhci:
             Status = SecurityCommonRoutine (
                                         BusInterface,
                                         Control,
                                         Buffer,
                                         ATA_CMD_SECURITY_SET_PASSWORD,
                                         RevisionCode,
                                         BusInterfaceType );
            break;
        case AmiStorageInterfaceNvme:
            Status = NvmeSecuritySendCommandCommonRoutine (
                                                    BusInterface,
                                                    Control,
                                                    Buffer,
                                                    NVME_ATA_SECURITY_SET_PASSWORD,
                                                    RevisionCode,
                                                    BusInterfaceType );
            break;
            
        case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
            {
                NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
                if (NvmeRstInterface->IsRaidHdd) {
                    Status = SecurityCommonRoutine (
                                                BusInterface,
                                                Control,
                                                Buffer,
                                                NVME_ATA_SECURITY_SET_PASSWORD,
                                                RevisionCode,
                                                BusInterfaceType );
                } else {
                    Status = NvmeSecuritySendCommandCommonRoutine(
                                                            BusInterface,
                                                            Control,
                                                            Buffer,
                                                            NVME_ATA_SECURITY_SET_PASSWORD,
                                                            RevisionCode,
                                                            BusInterfaceType ); 
                }
            }
#endif
            break;
    }

    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Set password status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    // Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
    
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    // If Password is set successfully, save it.
    if (gSmmHddSecuritySupport) {
        Status = SmmHddPasswordInterface (
                                      This,
                                      Control,
                                      Buffer,
                                      SavePassword );
    }
    
#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    Status = GatherIdeInfo ( 
                       BusInterface, 
                       BusInterfaceType, 
                       &HddDataId );
            
    if (!EFI_ERROR(Status)) {
        Status = SetHddSecDataInNvram ( 
                                  BusInterface,
                                  &HddDataId,
                                  Control,
                                  Buffer );
        ASSERT_EFI_ERROR(Status);
    }
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Sets the Default Password String provided by OEM as
    Master Password.

    @param *This           Pointer to AmiHddSecurityProtocol

    @retval EFI_SUCCESS   Default master password is set.
    @retval EFI_ERROR     Default master password is not set.

    @note  
      DEFAULT_MASTER_PASSWORD_TAG token string will be set as master password.
      
    @endinternal
**/
EFI_STATUS
SetDefaultMasterPassword (
    IN  AMI_HDD_SECURITY_PROTOCOL   *This
)
{
    EFI_STATUS              Status;
    UINT8                   Buffer[IDE_PASSWORD_LENGTH];
    UINT16                  Control = 1;
    UINT16                  RevisionCode = DISABLED_MASTER_PASSWORD_REVISION;
    UINTN                   Index;
    UINT16                  SecurityStatus = 0;

    ZeroMem (&Buffer, IDE_PASSWORD_LENGTH);

    for (Index = 0; Index < IDE_PASSWORD_LENGTH; Index++) {

        Buffer[Index] = (UINT8)gDefaultMasterPasswordTag[Index];

        if (gDefaultMasterPasswordTag[Index] == L'\0') {
            break;
        }
    }

    // Set the OEM master password if the HDD is not in Frozen or locked state.
    Status = ReturnSecurityStatus (This, &SecurityStatus);

    if (!((SecurityStatus & BIT2) || (SecurityStatus & BIT3))) {
        Status = SecuritySetDefaultMasterPassword( 
                                                This,
                                                Control,
                                                Buffer,
                                                RevisionCode );
    }
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Sets the Default Password String provided by OEM as
    Master Password. SECURITY_SET_PASSWORD(Command Code : 0xF1)
    security command is used to set the master password.

    @param *This        Pointer to AMI_HDD_SECURITY_PROTOCOL

    @retval EFI_SUCCESS   OEM Master password set successfully.
    @retval EFI_ERROR     Failed to set OEM Master password to the hard disk.

    @note OEM_MASTER_PASSWORD_TAG token string will be set as OEM master password.

    @endinternal
**/

EFI_STATUS
OemSetMasterPassword (
    IN  AMI_HDD_SECURITY_PROTOCOL   *This
)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    UINT8                   Buffer[IDE_PASSWORD_LENGTH];
    UINT16                  Control = 1;
    UINT16                  RevisionCode = 0xFFFE;
    UINTN                   Index;
    UINT16                  SecurityStatus = 0;

    ZeroMem (&Buffer, IDE_PASSWORD_LENGTH);

    for (Index = 0; Index < IDE_PASSWORD_LENGTH; Index++) {
        Buffer[Index] = (UINT8)gOemMasterPasswordTag[Index];

#if defined SETUP_PASSWORD_NON_CASE_SENSITIVE && SETUP_PASSWORD_NON_CASE_SENSITIVE 
        Buffer[Index] = ((Buffer[Index]>='a') && (Buffer[Index]<='z')) ? (Buffer[Index]+'A'-'a') : Buffer[Index];
#endif
        if (gOemMasterPasswordTag[Index] == L'\0') {
            break;
        }
    }

    //
    //Set the OEM master password if the HDD is not in Frozen or locked state.
    //
    Status = ReturnSecurityStatus (This, &SecurityStatus);

    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a ReturnSecurityStatus status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    if (!((SecurityStatus & BIT2) || (SecurityStatus & BIT3))) {
        Status = SecuritySetPassword (
                                This, 
                                Control, 
                                Buffer, 
                                RevisionCode );
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** 
    Stops the security mode support by uninstalling the
    security interface.

        
    @param *BusInterface        Pointer to current bus interface

    @param BusInterfaceType     Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS           Security Mode supported
    @retval EFI_DEVICE_ERROR      Security Mode Not supported    

**/

EFI_STATUS
EFIAPI
StopSecurityModeSupport (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
    
    if ((BusInterface == NULL) ||
        (BusInterfaceType < AmiStorageInterfaceIde) || 
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_INVALID_PARAMETER;
    }
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
            Status = IdeStopSecurityModeSupport (
                                            BusInterface, 
                                            BusInterfaceType);
            break;
        case AmiStorageInterfaceAhci:
            Status = AhciStopSecurityModeSupport (
                                            BusInterface, 
                                            BusInterfaceType);
            break;
        case AmiStorageInterfaceNvme:
            Status = NvmeStopSecurityModeSupport (
                                            BusInterface, 
                                            BusInterfaceType);
            break;
        case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            {
                NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
                if (NvmeRstInterface->IsRaidHdd) {
                    Status = AhciStopSecurityModeSupport (
                                                    BusInterface, 
                                                    BusInterfaceType);
                } else {
                    Status = NvmeStopSecurityModeSupport (
                                                    BusInterface, 
                                                    BusInterfaceType);
                }
            }
#endif
            break;
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Checks whether the device supports Security mode or not.
    If yes, installs SecurityProtocol.

    @param *BusInterface      Pointer to current bus interface
    @param BusInterfaceType   Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS                         Security Mode supported.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED    Security Mode Not supported.
    @retval EFI_ALREADY_STARTED                 The protocol has already been started.

**/
EFI_STATUS
EFIAPI
InstallSecurityInterface (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    EFI_HANDLE                      DeviceHandle = NULL;
    AMI_HDD_SECURITY_INTERFACE      *SecurityInterface = NULL;
    UINT32                          IdePasswordFlags = 0;
    
    if ((BusInterface == NULL) ||
        (BusInterfaceType < AmiStorageInterfaceIde) || 
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_INVALID_PARAMETER;
    }
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
            Status = IdeInstallSecurityInterface ( 
                                            BusInterface, 
                                            BusInterfaceType,
                                            &SecurityInterface, 
                                            &DeviceHandle);
            break;
        case AmiStorageInterfaceAhci:
            Status = AhciInstallSecurityInterface (
                                            BusInterface, 
                                            BusInterfaceType,
                                            &SecurityInterface,
                                            &DeviceHandle);
            break;
        case AmiStorageInterfaceNvme:
            Status = NvmeInstallSecurityInterface (
                                            BusInterface, 
                                            BusInterfaceType,
                                            &SecurityInterface,
                                            &DeviceHandle);
            break;
        case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            {
                NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
                if (NvmeRstInterface->IsRaidHdd) {
                    Status = AhciInstallSecurityInterface (
                                                    BusInterface, 
                                                    BusInterfaceType,
                                                    &SecurityInterface,
                                                    &DeviceHandle);
                } else {
                    Status = NvmeInstallSecurityInterface (
                                                    BusInterface, 
                                                    BusInterfaceType,
                                                    &SecurityInterface,
                                                    &DeviceHandle);
                }
            }
#endif
            break;
    }
    
    DEBUG ((DEBUG_INFO, "HddSecurity:%a Install Status = %r\n", __FUNCTION__, Status));
    
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Install Status = %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    // Check whether gAmiKeepDeviceLockedProtocolGuid is installed on the device handle.
    // If yes, no need to handle this device. Uninstall security protocol. 
    Status = gBS->OpenProtocol ( 
                            DeviceHandle,
                            &gAmiKeepDeviceLockedProtocolGuid, 
                            NULL, 
                            NULL, 
                            NULL, 
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );
    
    if (!EFI_ERROR(Status)) {
        DEBUG((DEBUG_INFO, "HddSecurity: AmiKeepDeviceLocked Protocol is installed. So, Uninstalling AmiHddSecurity Protocol\n"));
        StopSecurityModeSupport (
                            BusInterface, 
                            BusInterfaceType);
        return EFI_SUCCESS;
    }
    
    Status = CreateSmmCommunicateEvents (
                                BusInterfaceType,
                                SecurityInterface);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a CreateSmmCommunicateEvents Status = %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    if (gMasterPasswordEnable) {
        // Check if OEM_DEFAULT_MASTER_PASSWORD is enabled and
        // DISPLAY_MASTER_PASSWORD is Disabled
        Status = ReturnIdePasswordFlags (
                                    (AMI_HDD_SECURITY_PROTOCOL *)SecurityInterface,
                                    &IdePasswordFlags);
        if (EFI_ERROR(Status)) {
            DEBUG ((DEBUG_ERROR, "HddSecurity:%a ReturnIdePasswordFlags Status = %r\n", __FUNCTION__, Status));
            return Status;
        }

        if ((IdePasswordFlags & BIT11) && (!(IdePasswordFlags & BIT3))) {
            Status = OemSetMasterPassword ((AMI_HDD_SECURITY_PROTOCOL *)SecurityInterface);
        }
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    This function is the entry point for HddSecurity Driver.

    @param ImageHandle           A collection of related interfaces.
    @param *SystemTable          Pointer to the EFI system table.                     
    @retval 
        EFI_SUCCESS         Security interface installed.
        EFI_ERROR           Security interface not installed or unable to locate
                            some protocol.

    @note  
  Entry Points are used to locate or install protocol interfaces and
  notification events.

**/

EFI_STATUS
EFIAPI
HddSecurityEntryPoint (
    IN  EFI_HANDLE        ImageHandle,
    IN  EFI_SYSTEM_TABLE  *SystemTable
)
{
    EFI_STATUS          Status;
    EFI_HANDLE          Handle = NULL;

    gHddSecurityInitProtocol = AllocateZeroPool (sizeof(AMI_HDD_SECURITY_INIT_PROTOCOL));
                        
    if (gHddSecurityInitProtocol == NULL) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a AllocateZeroPool Status = %r\n", __FUNCTION__, EFI_OUT_OF_RESOURCES));
        return EFI_OUT_OF_RESOURCES;
    }

    gHddSecurityInitProtocol->InstallSecurityInterface = InstallSecurityInterface;
    gHddSecurityInitProtocol->StopSecurityModeSupport  = StopSecurityModeSupport;

    Status = gBS->InstallProtocolInterface(
                                &Handle,
                                &gAmiHddSecurityInitProtocolGuid,
                                EFI_NATIVE_INTERFACE,
                                gHddSecurityInitProtocol );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a InstallProtocolInterface Status = %r\n", __FUNCTION__, Status));
        return Status;
    }
    Status = AllocateSmmCommunicateBuffer ();

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Common Hook which Calls Read Write PIO.

    @param *BusInterface         Pointer to current bus interface
    @param *Buffer               Pointer to buffer which will be used when sending 
                                 SecurityCommand.
    @param ByteCount             No.of bytes to read/write 
    @param LBA                   Address of the block of data stored in storage device.
    @param ReadWriteCommand      Command to read/write
    @param ReadWrite Read/Write = 0/1
    @param BusInterfaceType      Defines type of a Storage Bus Interface.

    @retval *Buffer updated from PIO command.

    @endinternal
**/
EFI_STATUS 
CommonReadWritePioHook (
    IN VOID                         *BusInterface,
    IN OUT VOID                     *Buffer,
    IN UINTN                        ByteCount,
    IN UINT64                       LBA,
    IN UINT8                        ReadWriteCommand,
    IN BOOLEAN                      ReadWrite,
    IN AMI_STORAGE_BUS_INTERFACE    BusInterfaceType
)
{
    EFI_STATUS            Status = EFI_UNSUPPORTED;

    if (BusInterfaceType == AmiStorageInterfaceIde) {
        Status = IdePioModeReadWrite (
                        BusInterface,
                        Buffer,
                        ByteCount,
                        LBA,
                        ReadWriteCommand,
                        ReadWrite,
                        BusInterfaceType );
    } else if ((BusInterfaceType == AmiStorageInterfaceAhci) || 
               ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid)) {
        Status = AhciPioModeReadWrite (
                        BusInterface,
                        Buffer,
                        ByteCount,
                        LBA,
                        ReadWriteCommand,
                        ReadWrite,
                        BusInterfaceType );
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    This is common security routine which will be called from
    security routines. It is from this routine most of the security
    commands are sent to the drive.
        
    @param *BusInterface      Pointer to current bus interface
    @param Control            Bit 0 : 0/1 User/Master Password
                              Bit 8 : 0/1 High/Maximum Security level
    @param *Buffer            Pointer to password buffer which will be used to 
                              when sending SecurityCommand.
    @param SecurityCommand    Security command for NVMe
    @param RevisionCode       (Valid for Master password)
    @param BusInterfaceType   Bus interface type.

    @return EFI_STATUS   EFI_SUCCESS/EFI_DEVICE_ERROR

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
         32 bytes long, pad it with zeros to create a buffer of 32 bytes.

    @endinternal
**/
EFI_STATUS
SecurityCommonRoutine (
    IN  VOID                        *BusInterface,
    IN UINT16                       Control,
    IN UINT8                        *Buffer,
    IN UINT8                        SecurityCommand,
    IN UINT16                       RevisionCode,
    IN AMI_STORAGE_BUS_INTERFACE    BusInterfaceType
)
{
    EFI_STATUS                  Status;
    UINT16                      *SecurityBuffer;

    // Allocate 512 Bytes
    SecurityBuffer = AllocateZeroPool (ATA_SECURITY_BUFFER_LENGTH);

    if (SecurityBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    //first word denotes 
    SecurityBuffer[0] = Control;

    // Copy 32 Bytes
    CopyMem (&(SecurityBuffer[1]), Buffer, IDE_PASSWORD_LENGTH);

    // If Security Set password command is for Master, then update the
    // revision code at offset 17[word].
    if ((SecurityCommand == ATA_CMD_SECURITY_SET_PASSWORD) & (Control & 1)) {
        if ((RevisionCode != 0) && (RevisionCode != 0xFFFF)) {
            SecurityBuffer[17] = RevisionCode;
        }
    }

    // Write 512 Bytes
    Status = CommonReadWritePioHook (
                                BusInterface,
                                SecurityBuffer,
                                ATA_SECURITY_BUFFER_LENGTH,
                                0,
                                SecurityCommand,
                                TRUE,
                                BusInterfaceType );

    FreePool (SecurityBuffer);
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Gathers Device's Bus,Func,Device & PM/PS/SM/SS Info.

    @param *BusInterface      AMI_HDD_SECURITY_PROTOCOL
    @param BusInterfaceType   Defines type of a Storage Bus Interface.
    @param *HddDataId         Pointer to Data ID of HDD

    @retval EFI_SUCCESS   IDE info retrieved successfully.
    @retval EFI_ERROR     Failed to get IDE info.

    @endinternal
**/
EFI_STATUS
GatherIdeInfo (
    IN  VOID                            *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE       BusInterfaceType,
    OUT UINT32                          *HddDataId
)
{
    EFI_STATUS                          Status;
    UINTN                               SegNum;
    UINTN                               BusNum;
    UINTN                               DevNum;
    UINTN                               FuncNum;
    UINT16                              wBDF;
    UINT16                              wPortPMModeFlag = 0;
    UINT8                               ChannelorPort = 0;
    UINT8                               DeviceorPMPort = 0;
    EFI_PCI_IO_PROTOCOL                 *PciIo = NULL;

    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0))
            {
                AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
                PciIo          = IdeBusInterface->PciIO;
                ChannelorPort  = IdeBusInterface->IdeDevice.Channel;
                DeviceorPMPort = IdeBusInterface->IdeDevice.Device;
            }
#endif
            break;
            
        case AmiStorageInterfaceAhci:
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
            {
                SATA_DEVICE_INTERFACE *SataDevInterface = (SATA_DEVICE_INTERFACE *)BusInterface;
                PciIo          = SataDevInterface->AhciBusInterface->PciIO;
                ChannelorPort  = SataDevInterface->PortNumber;
                DeviceorPMPort = SataDevInterface->PMPortNumber;
            }
#endif
            break;
        case AmiStorageInterfaceNvme:
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
            {
                PciIo = ((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->PciIO;
            }
#endif
            break;
        case LocalAmiStorageInterfaceRaid:
#if ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
            {
                PciIo = ((NVME_RST_INTERFACE *)BusInterface)->PciIO;
                if (((NVME_RST_INTERFACE *)BusInterface)->IsRaidHdd) {
                    ChannelorPort  = (UINT8)((NVME_RST_INTERFACE *)BusInterface)->PortNumber;
                    DeviceorPMPort =  (UINT8)((NVME_RST_INTERFACE *)BusInterface)->PmPortNumber;
                }
            }
#endif
            break;
        default :
            return EFI_UNSUPPORTED;
            
    }
    
    if (PciIo == NULL) {
        return EFI_UNSUPPORTED;
    }

    Status = PciIo->GetLocation( 
                            PciIo, 
                            &SegNum, 
                            &BusNum, 
                            &DevNum, 
                            &FuncNum );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    wBDF = (UINT16)((BusNum << 8) | (DevNum << 3) | FuncNum);

    // wPortPMModeFlag=0 for Nvme
    if (BusInterfaceType != AmiStorageInterfaceNvme) {
        wPortPMModeFlag = (UINT16)((ChannelorPort << 12) |
                                   (DeviceorPMPort << 4) |
                                   ((UINT8)BusInterfaceType));
    }

    *HddDataId = (UINT32)(((UINT16)wBDF << 16) + ((UINT16)wPortPMModeFlag));

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r HddDataId : %x\n", __FUNCTION__, Status, *HddDataId));
    
    return EFI_SUCCESS;
}

/** @internal
    Gets Hdd Security Data in NVRAM Area.
  
    @param *BusInterface        Pointer to current bus interface
    @param *BusInterfaceType    Defines type of a Storage Bus Interface.
    @param Control              Bit 0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level 
    @param *Buffer              Pointer to buffer which will be used when sending 
                                SecurityCommand.
                               
    @retval EFI_SUCCESS     Getting HDDPassword is success.                         
    @retval EFI_NOT_FOUND   Failed to get the HDD password.    
    
    @endinternal                                   
**/
EFI_STATUS 
GetHddSecDataFromNvram (
    IN VOID                         *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE    BusInterfaceType,
    IN UINT16                       Control,
    IN OUT UINT8                    *Buffer 
)
{

    EFI_STATUS                      Status;
    UINT32                          HddDataId = 0;
    CHAR16                          HddSecutiyData [HDD_SECURITY_DATASIZE];
    HDD_SEC_DATA                    *HddSecData;
    UINTN                           HddSecDataSize = sizeof(HDD_SEC_DATA);
    UINT8                           CryptBuffer [IDE_PASSWORD_LENGTH];

    Status = GatherIdeInfo ( 
                        BusInterface, 
                        BusInterfaceType, 
                        &HddDataId );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a GatherIdeInfo Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    UnicodeSPrint (
            HddSecutiyData, 
            HDD_SECURITY_DATASIZE * sizeof(CHAR16), 
            L"%d",
            HddDataId );

    HddSecData = AllocateZeroPool(sizeof(HDD_SEC_DATA));
    if (HddSecData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ZeroMem (Buffer,  IDE_PASSWORD_LENGTH);

    Status = gRT->GetVariable(
                           HddSecutiyData,
                           &gIdeSecurityPwNvguid,
                           NULL,
                           &HddSecDataSize,
                           HddSecData );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a GetVariable Status = %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    if (Control & BIT0) {
        // Check Master Password Presence
        if (HddSecData->UserMaster & BIT0) {
            CopyMem (CryptBuffer, HddSecData->HddMasterPassword, sizeof(HddSecData->HddMasterPassword));
            EncodeDecodePassword (CryptBuffer, Buffer, HddSecData->MasterPasswordLength);
        } else {
            Status = EFI_NOT_FOUND;
        }
    } else {
        // Check User Password Presence
        if (HddSecData->UserMaster & BIT1) {
            CopyMem (CryptBuffer, HddSecData->HddUserPassword, sizeof(HddSecData->HddUserPassword));
            EncodeDecodePassword (CryptBuffer, Buffer, HddSecData->UserPasswordLength);
        } else {
            Status = EFI_NOT_FOUND;
        }
    }

    FreePool (HddSecData);
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}


/** @internal
    Sets Hdd Security Data in NVRAM Area.

    @param *BusInterface     Pointer to current bus interface
    @param *HddDataId       Pointer to  Data Id of HDD
    @param Control          Bit 0 : 0/1 User/Master Password
                            Bit 8 : 0/1 High/Maximum Security level 
    @param *Buffer          Pointer to password buffer which will be used when 
                            sending SecurityCommand.
 
    @retval EFI_SUCCESS    HDDPassword saved in NVRAM which later will be transfered to
                           SMRAM.
    @retval EFI_ERROR      Failed to save the HDD password in NVRAM.
    
    @endinternal
**/
EFI_STATUS
SetHddSecDataInNvram (
    IN  VOID                *BusInterface,
    IN UINT32               *HddDataId,
    IN UINT16               Control,
    IN UINT8                *Buffer
)
{
    EFI_STATUS              Status;
    HDD_SEC_DATA            *HddSecData;
    CHAR16                  HddSecutiyData[HDD_SECURITY_DATASIZE] = {0};
    UINT8                   CryptBuffer[IDE_PASSWORD_LENGTH];
    UINTN                   HddSecDataSize = sizeof(HDD_SEC_DATA);
    UINT16                  ParseIndex;
    UINT32                  Attribute = 0;

    HddSecData = AllocateZeroPool(sizeof(HDD_SEC_DATA));
    if (HddSecData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    UnicodeSPrint (
            HddSecutiyData, 
            HDD_SECURITY_DATASIZE * sizeof(CHAR16), 
            L"%d",
            *HddDataId );

    // Get the password variable so that other password will be
    // maintained in the NVRAM variable.
    Status = gRT->GetVariable (
                           HddSecutiyData,
                           &gIdeSecurityPwNvguid,
                           &Attribute,
                           &HddSecDataSize,
                           HddSecData );

    if (EFI_ERROR(Status)) {
        ZeroMem (HddSecData, sizeof(HDD_SEC_DATA));
        if (Attribute == 0) {
            Attribute = (UINT32)(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
        }
    }


    for (ParseIndex = 0; ParseIndex < IDE_PASSWORD_LENGTH; ParseIndex++) {
        if (Buffer[ParseIndex] == 0) {
            break;
        }
    }

    if (Control & BIT0) {
        // Check for Empty Buffer
        if (ParseIndex != 0) {
            HddSecData->UserMaster |= BIT0;  // Set Master Password Present Bit
        } else {
            HddSecData->UserMaster &= ~BIT0; // Clear Master Password Present Bit
        }
        HddSecData->MasterPasswordLength = ParseIndex;
        
        EncodeDecodePassword (Buffer, CryptBuffer, ParseIndex);

        ZeroMem (HddSecData->HddMasterPassword, sizeof(HddSecData->HddMasterPassword));
        CopyMem (HddSecData->HddMasterPassword, CryptBuffer, ParseIndex);
        
    } else {
        // Check for Empty Buffer
        if (ParseIndex != 0) {
            HddSecData->UserMaster |= BIT1;   // Set User Password Present Bit
        } else {
            HddSecData->UserMaster &= ~BIT1;  // Clear User Password Present Bit
        }
        HddSecData->UserPasswordLength = ParseIndex;
        
        EncodeDecodePassword (Buffer, CryptBuffer, ParseIndex);

        ZeroMem (HddSecData->HddUserPassword, sizeof(HddSecData->HddUserPassword));
        CopyMem (HddSecData->HddUserPassword, CryptBuffer, ParseIndex);

    }

    Status = gRT->SetVariable(
                           HddSecutiyData,
                           &gIdeSecurityPwNvguid,
                           Attribute,
                           HddSecDataSize,
                           HddSecData );
    FreePool (HddSecData);
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}
