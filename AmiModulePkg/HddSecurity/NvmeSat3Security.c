//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file NvmeSat3Security.c
    HDD Security SAT3 Protocol Support Implementation.

**/
#include <HddSecurity.h>

/** @internal
    Sends Security Receive command to NVMe and stores the 
    returned data in Buffer

    @param *BusInterface     A Pointer to current bus interface
    @param BusInterfaceType  Type of storage interface type.
    @param *Buffer           A pointer to the data buffer to transfer between the host
    @param Bufferlength      Length of the data buffer.
    @param CDW10Value        Command10 value.

    @retval EFI_STATUS

    @endinternal
**/
EFI_STATUS
NvmeSecurityRecieveRoutine (
    IN VOID                                 *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE            BusInterfaceType,
    IN OUT UINT8                            *Buffer,
    IN UINT32                               Bufferlength,
    IN UINT32                               CDW10Value
)
{
    EFI_STATUS                                  Status =  EFI_SUCCESS;
    EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET    NvmePacket;
    EFI_NVM_EXPRESS_COMMAND                     NvmeCommand;
    EFI_NVM_EXPRESS_COMPLETION                  NvmeCompletion; 
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL          *EfiNvmePassThru =  NULL;
    UINT32                                      NameSpaceId = 0;
    
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        EfiNvmePassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->PassThru;
        NameSpaceId = ((NVME_RST_INTERFACE *)BusInterface)->RstNamespaceId;
    }
#endif
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))   
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
        EfiNvmePassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *)((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->EfiNvmExpressPassThru;
    }
#endif
    
    if (EfiNvmePassThru == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    ZeroMem (&NvmePacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
    ZeroMem (&NvmeCommand, sizeof(EFI_NVM_EXPRESS_COMMAND));
    ZeroMem (&NvmeCompletion, sizeof(EFI_NVM_EXPRESS_COMPLETION));
    
    NvmeCommand.Nsid = 0;
    NvmeCommand.Cdw0.Opcode = NVME_ADMIN_SECURITY_RECEIVE_CMD;
    NvmeCommand.Cdw0.FusedOperation = 0;
    NvmeCommand.Cdw10 = CDW10Value;
    NvmeCommand.Cdw11 = Bufferlength;
    NvmeCommand.Flags = (CDW10_VALID | CDW11_VALID);
    
    NvmePacket.CommandTimeout = MultU64x32 (NVME_COMMAND_TIMEOUT, 10000000);    // 1Sec
    NvmePacket.NvmeCmd = &NvmeCommand;   
    NvmePacket.QueueType = 0;
    NvmePacket.NvmeCompletion = &NvmeCompletion;
    NvmePacket.TransferBuffer = Buffer;
    NvmePacket.TransferLength = Bufferlength;
    
    // Send Command through Passthru API
    Status = EfiNvmePassThru->PassThru ( 
                                    EfiNvmePassThru,
                                    NameSpaceId,
                                    &NvmePacket,
                                    NULL);
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Get Nvme Security Protocol Information

    @param *BusInterface     A Pointer to current bus interface
    @param BusInterfaceType  Type of storage interface type.
    @param *Buffer           A pointer to the data buffer to transfer between the host
    @param BufferLength      Length of the data buffer.     

    @return EFI_STATUS.

    @endinternal
**/
EFI_STATUS 
GetNvmeSecurityProtocolInformation (
    IN VOID                                 *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE            BusInterfaceType,
    IN OUT VOID                             *Buffer,
    IN OUT UINT32                           BufferLength 
)
{
    EFI_STATUS          Status;
    UINT32              CDW10Value = SECURITY_PROTOCOL_INFORMATION << 24; // SP = 0X00, SPSP=0x0000

    Status =  NvmeSecurityRecieveRoutine (
                                    BusInterface,
                                    BusInterfaceType,
                                    Buffer,
                                    BufferLength,
                                    CDW10Value );
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
    
}

/** @internal
    Check for NVME Security Protocol Supported.

    @param *BusInterface     Pointer to current bus interface
    @param BusInterfaceType  Type of storage interface type.
    @param *Sat3Supported    Pointer to SAT3 Security
    @param *TcgSupported     Pointer to TCG Security
        
    @retval EFI_SUCCESS           NVME Security Protocol Supported
    @retval EFI_UNSUPPORTED       NVME Security Protocol not Supported
        
    @endinternal
**/
EFI_STATUS 
IsNvmeSecurityProtocolSupported (
    IN  VOID                                *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE            BusInterfaceType,
    OUT BOOLEAN                             *Sat3Supported,
    OUT BOOLEAN                             *TcgSupported
)
{
    EFI_STATUS                          Status;
    UINT16                              ListLength = 0;
    UINT16                              SpByte = 0;
    SP0_TRUSTED_RECEIVE_PARAMETER_DATA  QueryBuffer;
    UINT32                              QueryBufferSize = sizeof(SP0_TRUSTED_RECEIVE_PARAMETER_DATA);

    *Sat3Supported = FALSE;
    *TcgSupported = FALSE;
    
    ZeroMem (&QueryBuffer, QueryBufferSize);
    
    Status = GetNvmeSecurityProtocolInformation (
                                        BusInterface, 
                                        BusInterfaceType, 
                                        (UINT8*)&QueryBuffer, 
                                        QueryBufferSize);
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a NVMe GetSupportedProtocols Status : %r\n", __FUNCTION__, Status));
    if (EFI_ERROR(Status)) {
        // If GetNvmeSecurityProtocolInformation returns error Status return Unsupported Security Protocol.
        return EFI_UNSUPPORTED;
    }

    // The List Length field indicates the total length, in bytes, of the supported security protocol list.
    ListLength = QueryBuffer.ListLengthHigh << 8 | QueryBuffer.ListLengthLow;
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a NVMe ListLength = %x\n", __FUNCTION__, ListLength));
    if (ListLength == 0) {
        return EFI_UNSUPPORTED;
    }
    
    // Check the security supported Protocol List
    for (SpByte = 0; SpByte < ListLength; SpByte++) {
        DEBUG ((DEBUG_VERBOSE,"HddSecurity:%a SpByte = %x,SupportedProtocolList = %x\n",__FUNCTION__,SpByte,QueryBuffer.SupportedSPList[SpByte]));
        if (QueryBuffer.SupportedSPList[SpByte] == NVME_SECUIRTY_SECP) {
            *Sat3Supported = TRUE;
        }
        
        if (QueryBuffer.SupportedSPList[SpByte] == SECURITY_PROTOCOL_1) {
            *TcgSupported = TRUE;
        }
        
        if (*Sat3Supported && *TcgSupported) {
            return EFI_SUCCESS;
        }
    }
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status:%r,Sat3Supported:%x,TcgSupported:%x\n",__FUNCTION__,Status,*Sat3Supported,*TcgSupported));
    return EFI_SUCCESS;
}

/** @internal
    Gets Nvme Security Status information

    @param *BusInterface     A Pointer to current bus interface
    @param BusInterfaceType  Type of storage interface type.
    @param *Buffer           A pointer to the data buffer to transfer between the host
    @param Bufferlength      Length of the data buffer.

    @return EFI_STATUS.

    @endinternal
**/
EFI_STATUS
GetNvmeDeviceSecurityData (
    IN VOID                                 *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE            BusInterfaceType,
    UINT8                                   *Buffer,
    UINT32                                  Bufferlength
)
{
    EFI_STATUS              Status;
    UINT32                  CDW10Value; 
    
    // SECP = 0XEF, SPSP=0
    CDW10Value =  (UINT32)LShiftU64(NVME_SECUIRTY_SECP,24);
    
    Status = NvmeSecurityRecieveRoutine (
                                   BusInterface,
                                   BusInterfaceType,
                                   Buffer,
                                   Bufferlength,
                                   CDW10Value );
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Builds Nvme Passwords buffer from user entered password in order
    to unlock Master or User password

    @param SecurityCommand     Security command for NVMe
    @param Control             Bit0 - 0/1 Indicates User/Master password    
                               Bit8 - 0/1 High/Maximum Security level
    @param *PasswrdBuffer      Pointer to the password buffer
    @param *Buffer             Pointer to the buffer
    @param RevisionCode        (Valid when Control Bit 0 = 1 of Master Password)
           
    @return VOID

    @endinternal
**/
VOID
BuildNvmeCommandBuffer (
    IN UINT8                SecurityCommand,
    IN UINT16               Control,
    IN UINT8                *PasswrdBuffer,
    IN OUT UINT8            *Buffer,
    IN UINT16               RevisionCode
)
{
    // Bit0 - 0/1 Indicates User/Master password    
    // Bit8 - 0/1 High/Maximum Security level
    Control &= (BIT8 | BIT1 | BIT0);
    Buffer[0] |= Control >> 8;
    Buffer[1] |= (UINT8)Control & BIT0;
    
    // Security Erase command
    // BIT1 - 0/1 Normal Erase/ Enhanced Erase
    if (SecurityCommand == NVME_ATA_SECURITY_ERASE_UNIT) {
        Buffer[0] |= Control >> 1;
    }

    if ((SecurityCommand != NVME_ATA_SECURITY_DISABLE_PASSWORD) &&
        (Control & BIT0) && (RevisionCode != 0) && (RevisionCode != 0xFFFF)) {
        Buffer[34] = RevisionCode >> 8;
        Buffer[35] = (UINT8)RevisionCode;
    }

    CopyMem (&Buffer[2], &PasswrdBuffer[0], IDE_PASSWORD_LENGTH);
}

/** @internal
    Function to send nvme Security command

    @param *BusInterface       Pointer to current bus interface
    @param Control             Bit 0 : 0/1 User/Master Password
                               Bit 8 : 0/1 High/Maximum Security level
    @param *PasswrdBuffer      Pointer to the password buffer
    @param SecurityCommand     Security command for NVMe
    @param RevisionCode        (Valid when Control Bit 0 = 1 of Master Password)
    @param BusInterfaceType    Defines type of a Storage Bus Interface.

    @return EFI_STATUS

    @endinternal
**/
EFI_STATUS
NvmeSecuritySendCommandCommonRoutine (
    IN  VOID                       *BusInterface,
    IN UINT16                      Control,
    IN UINT8                       *PasswrdBuffer,
    IN UINT8                       SecurityCommand,
    IN UINT16                      RevisionCode,
    IN AMI_STORAGE_BUS_INTERFACE   BusInterfaceType
)
{
    EFI_STATUS                                  Status =  EFI_SUCCESS;
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL          *EfiNvmePassThru = NULL;
    EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET    NvmePacket;
    EFI_NVM_EXPRESS_COMMAND                     NvmeCommand;
    EFI_NVM_EXPRESS_COMPLETION                  NvmeCompletion;
    UINT32                                      CommandLength=0;
    UINT32                                      NameSpaceId = 0;
    UINT8                                       NvmeSecurityCmdBuffer[NVME_SECURITY_SEND_BUFFER_SIZE];

    if ((BusInterfaceType != AmiStorageInterfaceNvme) &&
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType != LocalAmiStorageInterfaceRaid)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Un supported bus interface Type status : %r BusInterfaceType : %d\n",
                             __FUNCTION__, EFI_UNSUPPORTED, BusInterfaceType));
        return EFI_UNSUPPORTED;
    }
    
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        EfiNvmePassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *)((NVME_RST_INTERFACE *)BusInterface)->PassThru;
        NameSpaceId = ((NVME_RST_INTERFACE *)BusInterface)->RstNamespaceId;
    }
#endif
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))   
    if ((BusInterfaceType == AmiStorageInterfaceNvme)) { 
        EfiNvmePassThru = (EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *)((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->EfiNvmExpressPassThru;
    }
#endif

    ZeroMem (NvmeSecurityCmdBuffer, NVME_SECURITY_SEND_BUFFER_SIZE);
    ZeroMem (&NvmePacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
    ZeroMem (&NvmeCommand, sizeof(EFI_NVM_EXPRESS_COMMAND));
    ZeroMem (&NvmeCompletion, sizeof(EFI_NVM_EXPRESS_COMPLETION));
    
    if ((SecurityCommand != NVME_ATA_SECURITY_ERASE_PREPARE) && 
        (SecurityCommand != NVME_ATA_SECURITY_FREEZE_LOCK)) {

        BuildNvmeCommandBuffer(
                        SecurityCommand,
                        Control,
                        PasswrdBuffer,
                        NvmeSecurityCmdBuffer,
                        RevisionCode );
        CommandLength = NVME_SECURITY_SEND_BUFFER_SIZE;
    }

    NvmeCommand.Nsid = 0;
    NvmeCommand.Cdw0.Opcode = NVME_ADMIN_SECURITY_SEND_CMD;
    NvmeCommand.Cdw0.FusedOperation = 0;
    NvmeCommand.Cdw10 = (((UINT32)NVME_SECUIRTY_SECP) << 24) | (((UINT32)SecurityCommand) << 8);
    NvmeCommand.Cdw11 = CommandLength;
    
    NvmeCommand.Flags = (CDW10_VALID | CDW11_VALID);
    
    // Update the Timeout value based on the Command send to controller.
    // The Timeout value for the Secure Erase Unit should be coming from device
    if (SecurityCommand == NVME_ATA_SECURITY_ERASE_UNIT) {
        // Is Enhanced Security Erase requested
        if (Control & BIT1) {
            // Enhanced Security Erase Timeout
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
            if (BusInterfaceType == AmiStorageInterfaceNvme) {
                NvmePacket.CommandTimeout = \
                        (UINT64)ToBigLittleEndianWord (((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->SecReceiveBuffer.EnhancedSecEraseT);
            }
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
                NvmePacket.CommandTimeout = \
                        (UINT64)ToBigLittleEndianWord (((NVME_RST_INTERFACE *)BusInterface)->SecReceiveBuffer.EnhancedSecEraseT); 
            }
#endif
        } else {
            // Normal Security Erase Timeout
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
            if (BusInterfaceType == AmiStorageInterfaceNvme) {
                NvmePacket.CommandTimeout =(UINT64)ToBigLittleEndianWord (((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->SecReceiveBuffer.SecEraseTime );
            }
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
                NvmePacket.CommandTimeout = (UINT64)ToBigLittleEndianWord (((NVME_RST_INTERFACE*)BusInterface)->SecReceiveBuffer.SecEraseTime); 
            }
#endif
        }
        
        if (NvmePacket.CommandTimeout <= 254) {
            // For values between (0001h - 00FEh) timeout should be Value * 2 Minutes
            NvmePacket.CommandTimeout = MultU64x32 (NvmePacket.CommandTimeout , 120);  //Value * 60 * 2
            
            // Timeout in 100 ns units for the execution of this NVM Express Command Packet
            NvmePacket.CommandTimeout = MultU64x32 (NvmePacket.CommandTimeout , 10000000);  
        } else {
            NvmePacket.CommandTimeout = 0;
        }
    } else {
        // For all other command the timeout is 1 Sec 
        NvmePacket.CommandTimeout = MultU64x32 (NVME_COMMAND_TIMEOUT, 10000000);    
    }

    NvmePacket.NvmeCmd = &NvmeCommand;   
    NvmePacket.QueueType = 0;
    NvmePacket.NvmeCompletion = &NvmeCompletion;
    NvmePacket.TransferBuffer = NvmeSecurityCmdBuffer;
    NvmePacket.TransferLength = CommandLength;

    // Send Command through Pass thru API
    Status = EfiNvmePassThru->PassThru ( 
                                    EfiNvmePassThru,
                                    NameSpaceId,
                                    &NvmePacket,
                                    NULL );
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Installs AMI Security protocol for NVMe

    @param *BusInterface               InterfaceInstance
    @param BusInterfaceType            Type of storage interface type.
    @param SecurityInterface           Pointer to Security Interface
    @param DeviceHandle                Device handle

    @retval EFI_STATUS                 Security protocol installed successfully
            EFI_ERROR                  Error in installing protocol.
    @endinternal
**/
EFI_STATUS
NvmeInstallSecurityInterface (
    IN VOID                                 *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE            BusInterfaceType,
    IN OUT AMI_HDD_SECURITY_INTERFACE       **pSecurityInterface,
    IN OUT EFI_HANDLE                       *DeviceHandle
) 
{

    EFI_STATUS                              Status = EFI_UNSUPPORTED;
//#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) ) || ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0) ) 
    AMI_HDD_SECURITY_INTERFACE              *SecurityInterface = NULL;
    UINT16                                  NvmeSecurityStatus=0;
    UINT16                                  OACS = 0;
    BOOLEAN                                 IsSat3Supported = FALSE;
    BOOLEAN                                 IsTcgSupported = FALSE;

#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
    AMI_NVME_CONTROLLER_PROTOCOL    *NvmeDevInterface = (AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface;
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))    
    NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE*)BusInterface;
#endif
    
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        OACS = NvmeRstInterface->OACS;
        *DeviceHandle = NvmeRstInterface->RstDeviceHandle;
    }
#endif
#if (defined(NVMe_SUPPORT) && ( NVMe_SUPPORT != 0))
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
        OACS = NvmeDevInterface->IdentifyControllerData->OACS;
        *DeviceHandle = NvmeDevInterface->ControllerHandle;
    }
#endif
    
    // Check the Security Send and Receive command Support
    if ((OACS & BIT0) == 0) {
        return EFI_UNSUPPORTED;
    }
    
    Status = IsNvmeSecurityProtocolSupported (
                                    BusInterface,
                                    BusInterfaceType,
                                    &IsSat3Supported, 
                                    &IsTcgSupported );
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Nvme Security Protocol Supported : %r\n", Status));
    
    // Some devices returns error for the SECURITY_PROTOCOL_INFORMATION command once the device gets locked
    // In case of error assuming that device supports SAT3 security command and proceed.
    if (!EFI_ERROR(Status)) {
        
        DEBUG((DEBUG_VERBOSE, "HddSecurity : Nvme IsSAT3Supported: %d, IsTCGSupported: %d\n", IsSat3Supported, IsTcgSupported));
        
        // if device does not support SAT security protocol then return.
        if (!IsSat3Supported) {
            DEBUG ((DEBUG_INFO, "HddSecurity:%a SAT3 not supported IsSat3Supported : %x\n", __FUNCTION__, IsSat3Supported));
            return EFI_UNSUPPORTED;
        }
        
        //  Update the Identify device buffer
        Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
        
        // If the device doesn't support getting the Security Protocol 0xEF information
        // Return with not supported
        if (EFI_ERROR(Status)) {
            DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData Status : %r\n", __FUNCTION__, Status));
            return EFI_UNSUPPORTED;
        }
    
        // Return Nvme device security status
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
        if (BusInterfaceType == AmiStorageInterfaceNvme) {
            NvmeSecurityStatus = ToBigLittleEndianWord (NvmeDevInterface->SecReceiveBuffer.NvmeSecStatus); 
        } 
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
        if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
            NvmeSecurityStatus = ToBigLittleEndianWord(NvmeRstInterface->SecReceiveBuffer.NvmeSecStatus); 
        }
#endif
        // Check if the Security is supported
        if (!(NvmeSecurityStatus & BIT0)) {
            DEBUG ((DEBUG_INFO, "HddSecurity:%a Security not supported NvmeSecurityStatus : %x\n", __FUNCTION__, NvmeSecurityStatus));
            return EFI_UNSUPPORTED;
        }
            
#if (defined(SELECT_SAT3_OPAL_SECURITY_PROTOCOL) && !SELECT_SAT3_OPAL_SECURITY_PROTOCOL) 
        if (IsTcgSupported) {
        // Check if SAT3 Security is enabled. If so, allow HddSecurity driver to handle the device.
            if (!(NvmeSecurityStatus & BIT1)) {
                DEBUG ((DEBUG_INFO, "HddSecurity:%a SELECT_SAT3_OPAL_SECURITY_PROTOCOL = 0.NvmeSecurityStatus : %x\n", __FUNCTION__, NvmeSecurityStatus));
                return EFI_UNSUPPORTED;
            }
        }
#endif
    }
    
    SecurityInterface = AllocateZeroPool (sizeof(AMI_HDD_SECURITY_INTERFACE));

    if (SecurityInterface ==  NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
        NvmeDevInterface->SecurityInterface = SecurityInterface;
        SecurityInterface->BusInterface     = NvmeDevInterface; 
    }
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        NvmeRstInterface->SecurityInterface = SecurityInterface;
        SecurityInterface->BusInterface     = NvmeRstInterface; 
    }
#endif
       
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
//#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Sets NVMe password

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
NvmeSecuritySetPassword (
    IN  AMI_HDD_SECURITY_PROTOCOL       *This,
    IN UINT16                           Control,
    IN UINT8                            *Buffer,
    IN UINT16                           RevisionCode
) 
{
    
    EFI_STATUS                  Status = EFI_UNSUPPORTED;

    UINT16                      MasterPwdIdentifier = 0;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        MasterPwdIdentifier = ToBigLittleEndianWord (((NVME_RST_INTERFACE *)BusInterface)->SecReceiveBuffer.MasterPwdIdentifier);
    }
#endif

#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
        MasterPwdIdentifier = ToBigLittleEndianWord (((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->SecReceiveBuffer.MasterPwdIdentifier);
    }
#endif
    
    // Only for master password, Revision code can be changed.
    if ((Control & BIT0) && (RevisionCode == 0)) {
        RevisionCode = DetermineMasterPwdRevisionCode (MasterPwdIdentifier, RevisionCode);
    }

    Status = NvmeSecuritySendCommandCommonRoutine (
                                            BusInterface,
                                            Control,
                                            Buffer,
                                            NVME_ATA_SECURITY_SET_PASSWORD,
                                            RevisionCode,
                                            BusInterfaceType );
 
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Unlocks NVMe password

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
NvmeSecurityUnlockPassword (
    IN AMI_HDD_SECURITY_PROTOCOL        *This,
    IN UINT16                           Control,
    IN UINT8                            *Buffer,
    IN UINT16                           SecurityStatus
        
) 
{
    EFI_STATUS                          Status = EFI_UNSUPPORTED;
    UINT16                              RevisionCode = 0;
    VOID                                *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE           BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    // When in Setup, Current Password is prompted for consistency when Setting a New Password
    // Or Disabling the Existing Password. Follow a Special Path only in this case.
    //*****This Case Applies on only when (1)Password is Set & Security Enabled
    //                                    (2)Unlocked
    
    if ((SecurityStatus & BIT1) && (!(SecurityStatus & BIT2))) {
            
        if (!(Control & BIT0)) {
            Status = NvmeSecuritySendCommandCommonRoutine (
                                                    BusInterface,
                                                    Control,
                                                    Buffer,
                                                    NVME_ATA_SECURITY_DISABLE_PASSWORD,
                                                    0,
                                                    BusInterfaceType );
            
            if (!EFI_ERROR(Status)) {
                NvmeSecuritySendCommandCommonRoutine (
                                                BusInterface,
                                                Control,
                                                Buffer,
                                                NVME_ATA_SECURITY_SET_PASSWORD,
                                                RevisionCode,
                                                BusInterfaceType );
            }
        
            DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Unlock Password Status = %r\n", Status));
            return Status;
        }
    }
    
    Status = NvmeSecuritySendCommandCommonRoutine(
                                    BusInterface,
                                    Control,
                                    Buffer,
                                    NVME_ATA_SECURITY_UNLOCK,
                                    0,
                                    BusInterfaceType );
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: %a Security Unlock Password Status = %r\n", __FUNCTION__,Status));
    
    // Unlock failure status should be reported as it is.
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // Update the Identify device buffer
    Status = UpdateIdentifyData( BusInterface, BusInterfaceType );
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Freeze NVMe Lock

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
NvmeSecurityFreezeLock (
    IN AMI_HDD_SECURITY_PROTOCOL        *This
)
{
    EFI_STATUS                          Status;
    UINT16                              SecurityStatus = 0;
    AMI_STORAGE_BUS_INTERFACE           BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    VOID                                *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    
    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
#if !DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT
    if (SecurityStatus & BIT1) {
        Status = TransferPwDataFromNvramToSmram (This);
        ASSERT_EFI_ERROR(Status);
    }
#endif

    // Freeze Lock command will not work with the HDD is in Locked State.
    // So return with Success if the HDD is either in Locked State or Frozen state.
    if (SecurityStatus & (BIT3|BIT2)) {
        DEBUG((DEBUG_VERBOSE, "HddSecurity: HDD already in locked state\n"));
        return EFI_SUCCESS;
    }
    
    Status = NvmeSecuritySendCommandCommonRoutine (
                                            BusInterface,
                                            0,
                                            0,
                                            NVME_ATA_SECURITY_FREEZE_LOCK,
                                            0,
                                            BusInterfaceType );
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a Security Freeze Lock Status = %r\n",__FUNCTION__,Status));

    //  Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Erase NVMe Unit

    @param This                 Pointer HDD security protocol.
    @param Control              Bit 0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level
    @param Buffer               Pointer to password buffer which will be used to 
                                when sending SecurityCommand.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
NvmeSecurityEraseUnit (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;

    // Issue Security Erase Unit
    Control &= (BIT1 | BIT0);  // Bit0 and Bit 1 is valid

    // Update the Identify device buffer
    Status = UpdateIdentifyData ( BusInterface, BusInterfaceType );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    // Send Nvme Security Erase prepare command
    Status = NvmeSecuritySendCommandCommonRoutine(
                                            BusInterface,
                                            0,
                                            0,
                                            NVME_ATA_SECURITY_ERASE_PREPARE,
                                            0,
                                            BusInterfaceType );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Secure Erase Prepare Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    // Send Nvme Security Erase command
    Status = NvmeSecuritySendCommandCommonRoutine (
                                BusInterface,
                                Control,
                                Buffer,
                                NVME_ATA_SECURITY_ERASE_UNIT,
                                0,
                                BusInterfaceType );
    
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Security Erase Unit Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    // Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
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
NvmeUpdateIdentifyData (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                     Status = EFI_SUCCESS;
    
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
        NVME_SECURITY_RECEIVE_BUFFER   SecReceiveBuffer;
        
        ZeroMem (&SecReceiveBuffer, NVME_SECURITY_RECEIVE_BUFFER_SIZE);
        Status = GetNvmeDeviceSecurityData (
                                    BusInterface,
                                    BusInterfaceType,
                                    (UINT8*)&SecReceiveBuffer,
                                    NVME_SECURITY_RECEIVE_BUFFER_SIZE );
        if (!EFI_ERROR(Status)) {
            ((AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface)->SecReceiveBuffer = SecReceiveBuffer;  
        }
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
        NVME_RST_SECURITY_RECEIVE_BUFFER   NvmeRstSecReceive;
        ZeroMem (&NvmeRstSecReceive, NVME_SECURITY_RECEIVE_BUFFER_SIZE);
        Status = GetNvmeDeviceSecurityData (
                                    BusInterface,
                                    BusInterfaceType,
                                    (UINT8*)&NvmeRstSecReceive,
                                    NVME_SECURITY_RECEIVE_BUFFER_SIZE);
        if (!EFI_ERROR(Status)) {
            ((NVME_RST_INTERFACE*)BusInterface)->SecReceiveBuffer = NvmeRstSecReceive;  
        }
#endif
    }
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
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
NvmeReturnSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL        *This,
    IN UINT16                           *SecurityStatus
)
{
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
        AMI_NVME_CONTROLLER_PROTOCOL    *NvmeDevInterface = (AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface;  
        // Return Nvme device security status
        *SecurityStatus = ToBigLittleEndianWord (NvmeDevInterface->SecReceiveBuffer.NvmeSecStatus);
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
        NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
        *SecurityStatus = ToBigLittleEndianWord (NvmeRstInterface->SecReceiveBuffer.NvmeSecStatus);
#endif
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
NvmeStopSecurityModeSupport (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
    EFI_HANDLE                  DeviceHandle = NULL;
    AMI_HDD_SECURITY_INTERFACE  *SecurityInterface = NULL;
    
    if (BusInterfaceType == AmiStorageInterfaceNvme) {
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
        AMI_NVME_CONTROLLER_PROTOCOL    *NvmeDevInterface = (AMI_NVME_CONTROLLER_PROTOCOL *)BusInterface;  
        
        SecurityInterface = (AMI_HDD_SECURITY_INTERFACE *)NvmeDevInterface->SecurityInterface;
        DeviceHandle = NvmeDevInterface->ControllerHandle;
#endif
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
        NVME_RST_INTERFACE           *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
        
        SecurityInterface = (AMI_HDD_SECURITY_INTERFACE *)NvmeRstInterface->SecurityInterface;
        DeviceHandle = NvmeRstInterface->RstDeviceHandle;
#endif
    }
    
    if (SecurityInterface == NULL) {
        return EFI_SUCCESS;
    }

    if (DeviceHandle != NULL) {
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
    }
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity:%a exit Status : %r\n", __FUNCTION__, Status));
    return Status;
}

