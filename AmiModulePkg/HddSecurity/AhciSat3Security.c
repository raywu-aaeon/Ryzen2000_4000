//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AhciSat3Security.c
    HDD Security SAT3 Protocol Support Implementation.

**/
#include <HddSecurity.h>

/** @internal
    Send Ata command using Passthru protocol

    @param *BusInterface       Pointer to current bus interface
    @param Acb                 Pointer to ACB structure
    @param CommandTimeout      Command time out
    @param AtaProtocol         Protocol to send
     
    @retval EFI_SUCCESS         Command sent successfully
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/ 
EFI_STATUS
SendAtaCommand(
    IN VOID                            *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE       BusInterfaceType,
    IN EFI_ATA_COMMAND_BLOCK           *Acb,
    IN UINT8                           CommandTimeout, // in seconds
    IN EFI_ATA_PASS_THRU_CMD_PROTOCOL  AtaProtocol
)
{
    EFI_STATUS                          Status = EFI_UNSUPPORTED;
    UINT16                              PortNumber;
    UINT16                              PmPortNumber;
    EFI_ATA_STATUS_BLOCK                *Asb;
    EFI_ATA_PASS_THRU_COMMAND_PACKET    Packet;
    EFI_ATA_PASS_THRU_PROTOCOL          *AtaPassThru = NULL;
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        AtaPassThru = ((SATA_DEVICE_INTERFACE *)BusInterface)->AtaPassThru;
        PortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PMPortNumber;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
        AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->PassThru;
        PortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PmPortNumber;
#endif
    }

    
    if (AtaPassThru == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    Asb = AllocateAlignedPages (
                    EFI_SIZE_TO_PAGES(sizeof(EFI_ATA_STATUS_BLOCK)), 
                    AtaPassThru->Mode->IoAlign );
    if (Asb == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ZeroMem (Asb, sizeof(EFI_ATA_STATUS_BLOCK));
    ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));

    Packet.Asb        = Asb;
    Packet.Acb        = Acb;
    Packet.Timeout    = EFI_TIMER_PERIOD_SECONDS(CommandTimeout);
    Packet.Protocol   = AtaProtocol;
    
    Status = AtaPassThru->PassThru (
                                AtaPassThru,
                                PortNumber,
                                PmPortNumber,
                                &Packet,
                                NULL );
    FreePages (Asb, EFI_SIZE_TO_PAGES(sizeof(EFI_ATA_STATUS_BLOCK)));
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    
    return Status;
}

/** @internal
    Send PIO read and write command using Passthru protocol

    @param *BusInterface       Pointer to current bus interface
    @param Buffer              Pointer to buffer to read or write
    @param ByteCount           No of bytes to read or write
    @param LBA                 Logical block address to read to write
    @param ReadWriteCommand    Command 
    @param ReadWrite           Read or Write
    @param BusInterfaceType    Bus interface type
     
    @retval EFI_SUCCESS         Command sent successfully
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/ 
EFI_STATUS 
AhciPioModeReadWrite (
    IN VOID                             *BusInterface,
    IN OUT VOID                         *Buffer,
    IN UINTN                            ByteCount,
    IN UINT64                           LBA,
    IN UINT8                            ReadWriteCommand,
    IN BOOLEAN                          ReadWrite,
    IN AMI_STORAGE_BUS_INTERFACE        BusInterfaceType
)
{
    EFI_STATUS                          Status = EFI_UNSUPPORTED;
    UINT16                              PortNumber;
    UINT16                              PmPortNumber;
    EFI_ATA_COMMAND_BLOCK               Acb;
    EFI_ATA_STATUS_BLOCK                *Asb;
    EFI_ATA_PASS_THRU_COMMAND_PACKET    Packet;
    EFI_ATA_PASS_THRU_PROTOCOL          *AtaPassThru = NULL;
    VOID                                *AlignedBuffer = NULL;
   
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        AtaPassThru = ((SATA_DEVICE_INTERFACE *)BusInterface)->AtaPassThru;
        PortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PMPortNumber;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
        AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->PassThru;
        PortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PmPortNumber;
#endif
    }


    if (AtaPassThru == NULL) {
        return EFI_INVALID_PARAMETER;
    }
        
    Asb = AllocateAlignedPages (
                        EFI_SIZE_TO_PAGES(sizeof(EFI_ATA_STATUS_BLOCK)), 
                        AtaPassThru->Mode->IoAlign );
        
    if(Asb == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
        
    // Allocate buffer based on IoAlign
    AlignedBuffer = AllocateAlignedPages ( 
                                EFI_SIZE_TO_PAGES (ByteCount),
                                AtaPassThru->Mode->IoAlign );
        
    if (AlignedBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
        
    ZeroMem(&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
    ZeroMem(Asb, sizeof(EFI_ATA_STATUS_BLOCK));
    ZeroMem(&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
    
    Packet.Asb     = Asb;
    Packet.Acb     = &Acb;
    Packet.Timeout = EFI_TIMER_PERIOD_SECONDS(3);
        
    Acb.AtaCommand = ReadWriteCommand;
        
    if(ReadWrite) {
        CopyMem (AlignedBuffer, Buffer, ByteCount);
        Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT;
        Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
        Packet.OutDataBuffer     = AlignedBuffer;
        Packet.OutTransferLength = (UINT32)ByteCount;
    } else {
        Packet.Protocol         = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
        Packet.Length           = EFI_ATA_PASS_THRU_LENGTH_BYTES;
        Packet.InDataBuffer     = AlignedBuffer;
        Packet.InTransferLength = (UINT32)ByteCount;
    }
    
    Status = AtaPassThru->PassThru ( 
                                AtaPassThru,
                                PortNumber,
                                PmPortNumber,
                                &Packet,
                                NULL );
    DEBUG((DEBUG_INFO, "HddSecurity:%a PassThru Command - 0x%x Status - %r\n",__FUNCTION__, ReadWriteCommand, Status));
    if (!EFI_ERROR(Status) && !ReadWrite && (Buffer != NULL)) {
        CopyMem (Buffer, AlignedBuffer, ByteCount);
    }
        
    FreeAlignedPages (Asb, EFI_SIZE_TO_PAGES (sizeof (EFI_ATA_STATUS_BLOCK)));
    FreeAlignedPages (AlignedBuffer, EFI_SIZE_TO_PAGES (ByteCount));

    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
  @internal
  
    Gets Identify Data of SATA SSD
    
    @param AtaPassThru      Pass thru protocol
    @param Port             Port number
    @param PmPort           port multiplier number
    @param Buffer           Buffer to update Identify data

    @return EFI_STATUS
    
  @endinternal
**/
EFI_STATUS
GetAtaIdentifyData (
    IN EFI_ATA_PASS_THRU_PROTOCOL      *AtaPassThru,
    IN UINT16                          Port,
    IN UINT16                          PmPort,
    IN VOID                            *Buffer
)
{
    EFI_STATUS                          Status;
    EFI_ATA_COMMAND_BLOCK               Acb;
    EFI_ATA_STATUS_BLOCK                *Asb;
    EFI_ATA_PASS_THRU_COMMAND_PACKET    Packet;
    UINT32                              BufferLength = sizeof(ATA_IDENTIFY_DATA);
    VOID                                *AlignedBuffer = NULL;
    
    if (AtaPassThru == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Allocate buffer based on IoAlign
    AlignedBuffer = AllocateAlignedPages ( 
                            EFI_SIZE_TO_PAGES (BufferLength),
                            AtaPassThru->Mode->IoAlign );
    if (AlignedBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    Asb = AllocateAlignedPages (
                    EFI_SIZE_TO_PAGES(sizeof(EFI_ATA_STATUS_BLOCK)), 
                    AtaPassThru->Mode->IoAlign );
    if (Asb == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
    ZeroMem (Asb, sizeof(EFI_ATA_STATUS_BLOCK));
    ZeroMem (&Packet, sizeof(EFI_ATA_PASS_THRU_COMMAND_PACKET));
    
    Acb.AtaCommand           = ATA_CMD_IDENTIFY_DRIVE;

    Packet.Acb               = &Acb;
    Packet.Asb               = Asb;
    Packet.Protocol          = EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN;
    Packet.InDataBuffer      = AlignedBuffer;
    Packet.InTransferLength  = BufferLength;
    Packet.Length            = EFI_ATA_PASS_THRU_LENGTH_BYTES;
    Packet.Timeout           = EFI_TIMER_PERIOD_SECONDS(3);
    
    Status = AtaPassThru->PassThru ( 
                                AtaPassThru,
                                Port,
                                PmPort,
                                &Packet,
                                0 );
    if (!EFI_ERROR(Status)) {
        CopyMem (Buffer, AlignedBuffer, BufferLength);
    }
    
    FreePages (Asb, EFI_SIZE_TO_PAGES(sizeof(EFI_ATA_STATUS_BLOCK)));
    FreePages (AlignedBuffer, EFI_SIZE_TO_PAGES(BufferLength));
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Checks if device supports TCG Security protocol or not.

    @param *BusInterface       Pointer to current bus interface
    @param BusInterfaceType    Defines type of a Storage Bus Interface.
    @param *SAT3Supported      Pointer to SAT3Supported Security
    @param *TcgSupported       Pointer to TCGSupported Security
    
    @retval EFI_SUCCESS                        Security Mode supported.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/ 

EFI_STATUS
IsSecurityProtocolSupported (
   IN  VOID                         *BusInterface,
   IN  AMI_STORAGE_BUS_INTERFACE    BusInterfaceType,
   OUT BOOLEAN                      *Sat3Supported,
   OUT BOOLEAN                      *TcgSupported  
)
{
    EFI_STATUS                              Status;
    SP0_TRUSTED_RECEIVE_PARAMETER_DATA      QueryBuffer;
    UINTN                                   QueryBufferSize = sizeof(SP0_TRUSTED_RECEIVE_PARAMETER_DATA);
    UINTN                                   SpByte;
    EFI_STORAGE_SECURITY_COMMAND_PROTOCOL   *StorageSecurityProtocol = NULL;
    UINT16                                  ListLength = 0;
    UINT32                                  MediaId;
    IDENTIFY_DATA                           IdentifyData;
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        MediaId = ((SATA_DEVICE_INTERFACE *)BusInterface)->SataBlkIo->BlkIo.Media->MediaId;
        StorageSecurityProtocol = ((SATA_DEVICE_INTERFACE *)BusInterface)->StorageSecurityInterface;
        CopyMem (&IdentifyData, &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData, sizeof(IdentifyData));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
        MediaId = 0;
        StorageSecurityProtocol = (EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->EfiStorageSecInterface;
        CopyMem (&IdentifyData, ((NVME_RST_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else {
        return EFI_UNSUPPORTED;
    }

    
    if (!(IdentifyData.Trusted_Computing_Support & BIT0)) {
        *TcgSupported = FALSE;
        return EFI_SUCCESS;
     }
    
    // Return error if EfiStorageSecurityProtocol is not installed for AHCI devices
    if (!StorageSecurityProtocol) {
        *TcgSupported = FALSE ;
        return EFI_UNSUPPORTED;
    }
    
    ZeroMem (&QueryBuffer, QueryBufferSize);
    // SPC Spec Section 7.7.1 has details on decoding the data
    Status = StorageSecurityProtocol->ReceiveData( 
                                            StorageSecurityProtocol,
                                            MediaId, // Media ID
                                            SATA_COMMAND_TIMEOUT * 10000000,    // 5 sec 
                                            SECURITY_PROTOCOL_INFORMATION,   // Security Protocol ID
                                            0x00,                            // SP specific id
                                            0x200,                           // Transfer Length
                                            &QueryBuffer,
                                            &QueryBufferSize );                // Transferred Length
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity: GetSupportedProtocols Status = %r\n", Status));
    
    if (EFI_ERROR(Status)) {
        // If GetSecurityProtocolInformation returns error Status return Unsupported Security Protocol.
        return EFI_UNSUPPORTED;
    }

    // The List Length field indicates the total length, in bytes, of the supported security protocol list.
    ListLength = QueryBuffer.ListLengthHigh  <<  8 | QueryBuffer.ListLengthLow;
    DEBUG((DEBUG_VERBOSE, "HddSecurity: ListLength = %x\n", ListLength));
    
    if (ListLength == 0) {
        return EFI_UNSUPPORTED;
    }

    // Check Security supported Protocol List for Protocol ID 1
    for (SpByte = 0; SpByte < ListLength; SpByte++) {
        DEBUG ((DEBUG_VERBOSE, "HddSecurity: SpByte = %x, SupportedProtocolList = %x\n", SpByte, QueryBuffer.SupportedSPList[SpByte]));
        if (QueryBuffer.SupportedSPList[SpByte] == SECURITY_PROTOCOL_1) {
            *TcgSupported = TRUE;
        }
      
        if (*Sat3Supported && *TcgSupported ) {
            break;
        }
    }
    
    return EFI_SUCCESS;   
}

/** @internal
    Installs AMI Security protocol for SATA

    @param *BusInterface               InterfaceInstance
    @param BusInterfaceType            Type of storage interface type.
    @param SecurityInterface           Pointer to Security Interface
    @param DeviceHandle                Device handle

    @retval EFI_STATUS                 Security protocol installed successfully
            EFI_ERROR                  Error in installing protocol.
    @endinternal
**/
EFI_STATUS
AhciInstallSecurityInterface (
    IN VOID                                    *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE                BusInterfaceType,
    IN OUT AMI_HDD_SECURITY_INTERFACE           **pSecurityInterface,
    IN OUT EFI_HANDLE                           *DeviceHandle
) 
{
    
    EFI_STATUS                     Status = EFI_UNSUPPORTED;
    BOOLEAN                         IsSat3Supported;
    BOOLEAN                         IsTcgSupported = FALSE;
    AMI_HDD_SECURITY_INTERFACE      *SecurityInterface = NULL;
    IDENTIFY_DATA                   IdentifyData;
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
    SATA_DEVICE_INTERFACE           *SataDevInterface = (SATA_DEVICE_INTERFACE *)BusInterface;
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
    NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
#endif
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        if (SataDevInterface->DeviceType != ATA) {
            return EFI_UNSUPPORTED;
        }
        *DeviceHandle = SataDevInterface->IdeDeviceHandle;
        CopyMem (&IdentifyData, &SataDevInterface->IdentifyData, sizeof(IdentifyData));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0) )    
        *DeviceHandle = NvmeRstInterface->RstDeviceHandle;
        CopyMem (&IdentifyData, NvmeRstInterface->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else {
        return EFI_UNSUPPORTED;
    }
    
    // Bit 1 of word 82 refers to SECURITY SUPPORTED bit
    if (!(IdentifyData.Command_Set_Supported_82 & BIT1)) {
        return EFI_UNSUPPORTED;
    }
    
    IsSat3Supported = TRUE;
    
    // Check whether the device supports TCG security protocol         
    Status = IsSecurityProtocolSupported (
                                    BusInterface, 
                                    BusInterfaceType, 
                                    &IsSat3Supported, 
                                    &IsTcgSupported );
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Protocol Supported : %r\n", Status));

    // Some devices returns error for the SECURITY_PROTOCOL_INFORMATION command once the device gets locked
    // In case of error assuming that device supports SAT3 security command and proceed.
    if (!EFI_ERROR(Status)) {
        
        DEBUG((DEBUG_VERBOSE, "HddSecurity HDD: IsSAT3Supported: %d, IsTCGSupported: %d\n", IsSat3Supported, IsTcgSupported));
        
        // If device does not support SAT security protocol then return.
        if (!IsSat3Supported ) {
            return EFI_UNSUPPORTED;
        }
    
        // If device supports both SAT and TCG security protocol
        // then proceed based on SELECT_SAT3_OPAL_SECURITY_PROTOCOL SDL token
#if (defined(SELECT_SAT3_OPAL_SECURITY_PROTOCOL) && !SELECT_SAT3_OPAL_SECURITY_PROTOCOL) 
        if (IsTcgSupported) {
            // Check if SAT3 Security is enabled. If so, allow HddSecurity driver to handle the device.
            if (!(IdentifyData.Security_Status_128 & BIT1)) {
                DEBUG ((DEBUG_INFO, "HddSecurity:%a SELECT_SAT3_OPAL_SECURITY_PROTOCOL = 0.\n", __FUNCTION__));
                return EFI_UNSUPPORTED;
            }
        }
#endif
    }
    
    SecurityInterface = AllocateZeroPool(sizeof(AMI_HDD_SECURITY_INTERFACE));

    if (SecurityInterface == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))  
        SecurityInterface->BusInterface    = SataDevInterface;
        SataDevInterface->IdeSecurityInterface = (AMI_HDD_SECURITY_PROTOCOL *)SecurityInterface;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
        NvmeRstInterface->SecurityInterface = SecurityInterface;
        SecurityInterface->BusInterface     = NvmeRstInterface; 
#endif
    }

    
    // Update the Identify device buffer before installing the protocol as 
    // Other driver can use the Protocol interface on a callback.
    Status = UpdateIdentifyData (SecurityInterface->BusInterface, BusInterfaceType);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData Status : %r\n", __FUNCTION__, Status));
        FreePool (SecurityInterface);
        return Status;
    }
    
    Status = InternalInstallSecurityInterface (
                                    BusInterfaceType,
                                    *DeviceHandle,
                                    SecurityInterface);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a InternalInstallSecurityInterface Status : %r\n", __FUNCTION__, Status));
        FreePool (SecurityInterface);
        return Status;
    }
    
    *pSecurityInterface = SecurityInterface;
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
        
    return Status;
}

/** @internal
    Sets AHCI password

    @param This                 Pointer HDD security protocol.
    @param ControlBit           0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level
    @param Buffer               Pointer to password buffer which will be used to 
                                when sending SecurityCommand.
    @param RevisionCode         (Valid for Master password)

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciSecuritySetPassword (
    IN  AMI_HDD_SECURITY_PROTOCOL       *This,
    IN UINT16                           Control,
    IN UINT8                            *Buffer,
    IN UINT16                           RevisionCode
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    UINT16                          MasterPwdIdentifier;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    IDENTIFY_DATA                   IdentifyData;

    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        CopyMem (&IdentifyData, &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
        CopyMem (&IdentifyData, ((NVME_RST_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else {
        return EFI_UNSUPPORTED;
    }
    
    MasterPwdIdentifier = IdentifyData.Master_Password_Rev_92;
    
    // Only for master password, Revision code can be changed.
    if ((Control & BIT0) && (RevisionCode == 0)) {
        RevisionCode = DetermineMasterPwdRevisionCode (MasterPwdIdentifier, RevisionCode);
    }
    
    Status = SecurityCommonRoutine (
                                BusInterface,
                                Control,
                                Buffer,
                                SECURITY_SET_PASSWORD,
                                RevisionCode,
                                BusInterfaceType );
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Unlocks AHCI password

    @param This                 Pointer HDD security protocol.
    @param Control              Bit 0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level
    @param Buffer               Pointer to password buffer which will be used to 
                                when sending SecurityCommand.
    @param SecurityStatus       Security status provided for the storage device.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciSecurityUnlockPassword (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer,
    IN UINT16                      SecurityStatus
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    IDENTIFY_DATA                   IdentifyData;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterfaceType;
    
#if (defined (PORTRESET_ON_HDD_PWD_VERIFICATION) && (PORTRESET_ON_HDD_PWD_VERIFICATION != 0))
    EFI_ATA_COMMAND_BLOCK           Acb;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL  AtaProtocol;
    UINT8                           CommandTimeout;
#endif
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        CopyMem (&IdentifyData, &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
        CopyMem (&IdentifyData, ((NVME_RST_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    }

    // When in Setup, Current Password is prompted for consistency when Setting a New Password
    // Or Disabling the Existing Password. Follow a Special Path only in this case.
    //*****This Case Applies on only when (1)Password is Set & Security Enabled
    //                                    (2)Unlocked
    if ((SecurityStatus & BIT1) && (!(SecurityStatus & BIT2))) {
            
        if (!(Control & BIT0)) {
#if (defined (PORTRESET_ON_HDD_PWD_VERIFICATION) && (PORTRESET_ON_HDD_PWD_VERIFICATION != 0))
            
            //
            // AHCI MODE:  Changing or Clearing User Password.
            //  1. Send the Disable Software Preservation if the HDD is unlocked state 
            //  2. Issue Port reset to put back the HDD into Locked State 
            //  3. Send the Unlock command to verify the current password 
            //
            if ((IdentifyData.Reserved_76_79[0] != 0xFFFF )&&
                (IdentifyData.Reserved_76_79[2] & 0x0040)&&           // Software Preservation support
                (IdentifyData.Security_Status_128 & 0x0002)&&         // Security enabled
                (!(IdentifyData.Security_Status_128 & 0x0004))) {     // Security not locked

                // Send Disable Software Preservation command.
                ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
                Acb.AtaCommand = ATA_CMD_SET_FEATURES;
                Acb.AtaFeatures = ATA_SUB_CMD_DISABLE_SATA_FEATURE;
                CommandTimeout = 3; // in seconds
                AtaProtocol    = EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET;
                
                Status = SendAtaCommand (
                                    BusInterface,
                                    BusInterfaceType,
                                    &Acb, 
                                    CommandTimeout, 
                                    AtaProtocol);
                if (EFI_ERROR(Status)) {
                    DEBUG((DEBUG_ERROR,"HddSecurity: %a Failed to disable SATA software preservation with Status:%r\n",__FUNCTION__,Status));
                    return Status;
                }
            }
            
            // Generate the port Reset to put the HDD into Locked State
            ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
            CommandTimeout = 3; // in seconds
            AtaProtocol    = EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET;
            
            Status = SendAtaCommand(BusInterface, BusInterfaceType, &Acb, CommandTimeout, AtaProtocol);
            if(EFI_ERROR(Status)) {
                DEBUG((DEBUG_ERROR,"HddSecurity:%a GeneratePortReset failed with Status:%r\n",__FUNCTION__,Status));
                return Status;
            }
            
            Status = SecurityCommonRoutine (
                                    BusInterface,
                                    Control,
                                    Buffer,
                                    SECURITY_UNLOCK,
                                    0,
                                    BusInterfaceType);
            
#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
            if (EFI_ERROR(Status)) {

                EFI_STATUS TempPassWordStatus;
                UINT8      TempPassWordBuffer[IDE_PASSWORD_LENGTH];
                
                TempPassWordStatus = GetHddSecDataFromNvram (
                                                        BusInterface,
                                                        BusInterfaceType,
                                                        Control,
                                                        TempPassWordBuffer );
                if (!EFI_ERROR(TempPassWordStatus)) {
                    SecurityCommonRoutine(
                                    BusInterface,
                                    Control,
                                    TempPassWordBuffer,
                                    SECURITY_UNLOCK,
                                    0,
                                    BusInterfaceType
                                    );
                }
            } 
#endif
            DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Unlock Password Status = %r\n", Status));
#else 
            // 
            // (a)For Changing or Clearing User Password.
            //  1.Send a disable Password Command from the String Obtained from user.
            //  2.If Success Set the Password Same Password.
            //  3.Suitable if Logged in as Both User or Master
            //
            Status = SecurityCommonRoutine (
                                        BusInterface,
                                        Control,
                                        Buffer,
                                        SECURITY_DISABLE_PASSWORD,
                                        0,
                                        BusInterfaceType );
            
            if (!EFI_ERROR(Status)) {
                SecurityCommonRoutine (
                                BusInterface,
                                Control,
                                Buffer,
                                SECURITY_SET_PASSWORD,
                                0, // RevisionCode
                                BusInterfaceType );
            }
            
            DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Unlock Password Status = %r\n", Status));
#endif
            return Status;
        }
    }
    Status = SecurityCommonRoutine (
                            BusInterface,
                            Control,
                            Buffer,
                            SECURITY_UNLOCK,
                            0,
                            BusInterfaceType ); 
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // Update the Identify device buffer
    Status = UpdateIdentifyData( BusInterface, BusInterfaceType );
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
    
}

/** @internal
    Freeze AHCI Lock

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciSecurityFreezeLock (
    IN AMI_HDD_SECURITY_PROTOCOL *This
)
{
    EFI_STATUS                      Status;
    EFI_STATUS                      DcoFreezeLockStatus;
    UINT16                          SecurityStatus = 0;
    IDENTIFY_DATA                   IdentifyData;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterfaceType;
    EFI_ATA_COMMAND_BLOCK           Acb;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL  AtaProtocol;
    UINT8                           CommandTimeout;
    
    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        CopyMem (&IdentifyData, &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
        CopyMem (&IdentifyData, ((NVME_RST_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else {
        return EFI_UNSUPPORTED;
    }
    
#if !DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT
    if (SecurityStatus & BIT1) {
        if (IdentifyData.Reserved_76_79[3] & 0x0040) {
            Status = TransferPwDataFromNvramToSmram (This);
            ASSERT_EFI_ERROR( Status );
        }
    }
#endif

    // Freeze Lock command will not work with the HDD is in Locked State.
    // So return with Success if the HDD is either in Locked State or Frozen state.
    if (SecurityStatus & (BIT3 | BIT2)) {
        DEBUG ((DEBUG_VERBOSE, "HddSecurity: HDD already in locked state\n"));
        return EFI_SUCCESS;
    }
    
    ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
    Acb.AtaCommand = ATA_CMD_SECURITY_FREEZE_LOCK;
    CommandTimeout = 3; // in seconds
    AtaProtocol    = EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA;
    
    Status = SendAtaCommand (
                        BusInterface, 
                        BusInterfaceType,
                        &Acb, 
                        CommandTimeout, 
                        AtaProtocol);
    // if Device Configuration Overlay(DCO) feature set supported, then issue the
    // Device configure Freeze lock command.
    // After sending DCO FreezeLock cmd without error, a device shall abort further
    // DCO FreezeLock cmd until after completing the subsequent power-on reset(cold boot).
    // So,DCO FreezeLock cmd may fails in warm boots.
    if (IdentifyData.Command_Set_Supported_83 & 0x800) {
        
        ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
        Acb.AtaCommand  = ATA_CMD_DEV_CONFIG_OVERLAY;
        Acb.AtaFeatures = ATA_CMD_DEV_CONFIG_FREEZELOCK_FEATURE;
        CommandTimeout  = 3; // in seconds
        AtaProtocol     = EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA;
        
        DcoFreezeLockStatus = SendAtaCommand (
                                        BusInterface,
                                        BusInterfaceType,
                                        &Acb,
                                        CommandTimeout, 
                                        AtaProtocol);
        
        if (EFI_ERROR(DcoFreezeLockStatus)) {
            DEBUG((DEBUG_ERROR, "HddSecurity: DcoFreezeLockStatus Status = %r\n", DcoFreezeLockStatus));
        }
    }
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Freeze Lock Status = %r\n", Status));

    //  Update the Identify device buffer
    Status = UpdateIdentifyData( BusInterface, BusInterfaceType );

    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Erase AHCI Unit

    @param This                 Pointer HDD security protocol.
    @param Control              Bit 0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level
    @param Buffer               Pointer to password buffer which will be used to 
                                when sending SecurityCommand.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciSecurityEraseUnit (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    EFI_ATA_COMMAND_BLOCK           Acb;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL  AtaProtocol;
    UINT8                           CommandTimeout;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    // Issue Security Erase Unit
    Control &= (BIT1 | BIT0);  // Bit0 and Bit 1 is valid

    // Update the Identify device buffer
    Status = UpdateIdentifyData( BusInterface, BusInterfaceType );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    ZeroMem (&Acb, sizeof(EFI_ATA_COMMAND_BLOCK));
    Acb.AtaCommand  = ATA_CMD_SECURITY_ERASE_PREPARE;
    CommandTimeout  = 3; // in seconds
    AtaProtocol     = EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA;
    
    Status = SendAtaCommand (
                        BusInterface,
                        BusInterfaceType,
                        &Acb,
                        CommandTimeout,
                        AtaProtocol);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = SecurityCommonRoutine (
                            BusInterface,
                            Control,
                            Buffer,
                            SECURITY_ERASE_UNIT,
                            0,
                            BusInterfaceType );

    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Erase Unit Status = %r\n", Status));

    // Update the Identify device buffer
    Status = UpdateIdentifyData( BusInterface, BusInterfaceType );

    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Update identify data in bus interface data

    @param *BusInterface        Pointer to current bus interface
    @param BusInterfaceType     Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS                        Identify data updated successfully.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/
EFI_STATUS
AhciUpdateIdentifyData (
    IN VOID                       *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINT16                      PortNumber;
    UINT16                      PmPortNumber;
    IDENTIFY_DATA               *IdentifyData;
    EFI_ATA_PASS_THRU_PROTOCOL  *AtaPassThru;
    

    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        AtaPassThru = ((SATA_DEVICE_INTERFACE *)BusInterface)->AtaPassThru;
        PortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((SATA_DEVICE_INTERFACE *)BusInterface)->PMPortNumber;
        IdentifyData = &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0) )
        AtaPassThru = (EFI_ATA_PASS_THRU_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->PassThru;
        PortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PortNumber;
        PmPortNumber = ((NVME_RST_INTERFACE *)BusInterface)->PmPortNumber;
        IdentifyData = ((NVME_RST_INTERFACE *)BusInterface)->IdentifyData;
#endif
    } else {
        return EFI_UNSUPPORTED;
    }

    Status = GetAtaIdentifyData (
                            AtaPassThru,
                            PortNumber,
                            PmPortNumber,
                            IdentifyData );

    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    return device security status

    @param This                 Pointer HDD security protocol.
    @param SecurityStatus       Security status provided for the storage device.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciReturnSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL       *This,
    IN UINT16                          *SecurityStatus
)
{
    IDENTIFY_DATA                   IdentifyData;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        CopyMem (&IdentifyData, &((SATA_DEVICE_INTERFACE *)BusInterface)->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
        NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
        CopyMem (&IdentifyData, NvmeRstInterface->IdentifyData, sizeof(IDENTIFY_DATA));
#endif
    } else {
        return EFI_UNSUPPORTED;
    }

    //  Check if Word 82 Bit 1 is set
    if ((IdentifyData.Command_Set_Supported_82 & BIT1)) {
        *SecurityStatus = IdentifyData.Security_Status_128;
    }
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Status : %x\n", *SecurityStatus));

    return EFI_SUCCESS;
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
AhciStopSecurityModeSupport (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  DeviceHandle;
    AMI_HDD_SECURITY_INTERFACE  *SecurityInterface = NULL;
    
    if (BusInterfaceType == AmiStorageInterfaceAhci) {
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
        SATA_DEVICE_INTERFACE       *SataDevInterface = (SATA_DEVICE_INTERFACE *)BusInterface;
        SecurityInterface = (AMI_HDD_SECURITY_INTERFACE *)SataDevInterface->IdeSecurityInterface;
        DeviceHandle = SataDevInterface->IdeDeviceHandle;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
        NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
    SecurityInterface = (AMI_HDD_SECURITY_INTERFACE*)NvmeRstInterface->SecurityInterface;
    DeviceHandle = NvmeRstInterface->RstDeviceHandle;
#endif
    }
    if (SecurityInterface == NULL) {
        return EFI_SUCCESS;
    }
    
    //  Install Devicepath and BLOCK_IO on a new handle
    Status = gBS->UninstallMultipleProtocolInterfaces (
                                                DeviceHandle,
                                                &gAmiHddSecurityProtocolGuid,
                                                SecurityInterface,
                                                NULL );

    if (Status == EFI_SUCCESS) {
        FreePool (SecurityInterface);
        SecurityInterface = NULL;
    }

    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}
