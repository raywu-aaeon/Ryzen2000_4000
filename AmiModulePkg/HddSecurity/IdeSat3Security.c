//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file IdeSat3Security.c
    HDD Security SAT3 Protocol Support Implementation.

**/
#include <HddSecurity.h>

/** @internal
    function to Read Write PIO.

    @param *BusInterface         Pointer to current bus interface
    @param *Buffer               Pointer to buffer which will be used when sending 
                                 SecurityCommand.
    @param ByteCount             No.of bytes to read/write 
    @param LBA                   Address of the block of data stored in storage device.
    @param ReadWriteCommand      Command to read/write
    @param ReadWrite             Read/Write = 0/1
    @param BusInterfaceType      Defines type of a Storage Bus Interface.

    @retval *Buffer updated from PIO command.

    @endinternal
**/
EFI_STATUS
IdePioModeReadWrite (
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
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;

    Status = IdeBusInterface->AtaReadWritePio (
                                    IdeBusInterface,
                                    Buffer,
                                    ByteCount,
                                    0,
                                    ReadWriteCommand,
                                    TRUE );
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;   
}
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
/** @internal
    Common Hook which Calls Non Data Command.

    @param *BusInterface        Pointer to current bus interface
    @param CommandStructure     Command details sent to the device
    @param BusInterfaceType     Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS                        Non Data command completed successfully.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/
EFI_STATUS
IdeSendNonDataCommand (
    IN  VOID                        *BusInterface,
    IN  COMMAND_STRUCTURE           CommandStructure,  
    IN  AMI_STORAGE_BUS_INTERFACE   BusInterfaceType
)
{
    EFI_STATUS            Status = EFI_UNSUPPORTED;

    AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;


    if (BusInterfaceType != AmiStorageInterfaceIde) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Unsupported BusInterfaceType : %d\n", __FUNCTION__, BusInterfaceType));
        return Status;
    }
    
    CommandStructure.Device = IdeBusInterface->IdeDevice.Device << 4;

    // IdeBus API changed from Core 4.6.5.2. Added Core Version check for the OLD 
    // Core support.
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028b) 
    Status = IdeBusInterface->IdeNonDataCommand (
                                            IdeBusInterface,
                                            CommandStructure.Features,
                                            (UINT8)CommandStructure.SectorCount,
                                            (UINT8)(CommandStructure.SectorCount >> 8),
                                            CommandStructure.LBALow,
                                            CommandStructure.LBALowExp,
                                            CommandStructure.LBAMid,
                                            CommandStructure.LBAMidExp,
                                            CommandStructure.LBAHigh,
                                            CommandStructure.LBAHighExp,
                                            CommandStructure.Device,
                                            CommandStructure.Command );
#else 
    Status = IdeBusInterface->IdeNonDataCommand (
                                            IdeBusInterface,
                                            CommandStructure.Features,
                                            (UINT8)CommandStructure.SectorCount,
                                            CommandStructure.LBALow,
                                            CommandStructure.LBAMid,
                                            CommandStructure.LBAHigh,
                                            CommandStructure.Device,
                                            CommandStructure.Command );

#endif


    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Common Hook which Calls Pio Data Command.

    @param *IdeBusInterface     IDE protocol pointer
    @param CommandStructure     Pointer to Command details sent to the device

    @retval EFI_SUCCESS                        Pio data command completed.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/
EFI_STATUS
IdeGetIdentifyData (
    IN VOID                             *IdeBusInterface,
    IN COMMAND_STRUCTURE                *CommandStructure
)
{
    EFI_STATUS              Status = EFI_UNSUPPORTED;
    Status  = ((AMI_IDE_BUS_PROTOCOL *)IdeBusInterface)->AtaPioDataIn(
                                                                IdeBusInterface,
                                                                CommandStructure->Buffer,
                                                                CommandStructure->ByteCount,
                                                                CommandStructure->Features,
                                                                (UINT8)CommandStructure->SectorCount,
                                                                CommandStructure->LBALow,
                                                                CommandStructure->LBAMid,
                                                                CommandStructure->LBAHigh,
                                                                CommandStructure->Device,
                                                                CommandStructure->Command,
                                                                FALSE);

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}
#endif


/** @internal
    Update identify data in bus interface data

    @param *BusInterface        Pointer to current bus interface
    @param BusInterfaceType     Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS                        Identify data updated successfully.
    @retval EFI_DEVICE_ERROR/EFI_UNSUPPORTED   Not supported.

    @endinternal
**/
EFI_STATUS
IdeUpdateIdentifyData (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0))
    COMMAND_STRUCTURE               CommandStructure;
    IDENTIFY_DATA                   IdentifyBuffer;
    AMI_IDE_BUS_PROTOCOL            *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;

    ZeroMem (&IdentifyBuffer, sizeof (IdentifyBuffer));
    //  Read Identify data
    CommandStructure.Command   = IDENTIFY_COMMAND;
    CommandStructure.Buffer    = &IdentifyBuffer;
    CommandStructure.ByteCount = sizeof(IDENTIFY_DATA);
    CommandStructure.Device    = IdeBusInterface->IdeDevice.Device << 4;
    Status = IdeGetIdentifyData (
                            IdeBusInterface,
                            &CommandStructure);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a IdeGetIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    // Copy Identify Data
    CopyMem (
        &(IdeBusInterface->IdeDevice.IdentifyData),
        &IdentifyBuffer,
        sizeof(IDENTIFY_DATA));

#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Installs AMI Security protocol for IDE

    @param *BusInterface               InterfaceInstance
    @param BusInterfaceType            Type of storage interface type.
    @param SecurityInterface           Pointer to Security Interface
    @param DeviceHandle                Device handle

    @retval EFI_STATUS                 Security protocol installed successfully
            EFI_ERROR                  Error in installing protocol.
    @endinternal
**/
EFI_STATUS
IdeInstallSecurityInterface (
    IN VOID                             *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE        BusInterfaceType,
    IN OUT AMI_HDD_SECURITY_INTERFACE   **pSecurityInterface,
    IN OUT EFI_HANDLE                   *DeviceHandle
 )
 {
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    AMI_IDE_BUS_PROTOCOL            *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
    AMI_HDD_SECURITY_INTERFACE      *SecurityInterface;

    if ((BusInterfaceType != AmiStorageInterfaceIde) ||
        (IdeBusInterface->IdeDevice.DeviceType != ATA)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Un supported bus interface/Device Type status : %r BusInterfaceType : %d DeviceType : %x\n",
                             __FUNCTION__, Status, BusInterfaceType, IdeBusInterface->IdeDevice.DeviceType));
        return Status;
    }

    // Bit 1 of word 82 refers to SECURITY SUPPORTED bit
    if (!(IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82 & BIT1)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a Security not supported Status : %r Command_Set_Supported_82 : %x\n",
                             __FUNCTION__, Status, IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82));
        return Status;
    }
    
    SecurityInterface = AllocateZeroPool (sizeof(AMI_HDD_SECURITY_INTERFACE));

    if (SecurityInterface ==  NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    SecurityInterface->BusInterface    = IdeBusInterface;
    SecurityInterface->BusInterfaceType    = BusInterfaceType;
    *DeviceHandle = IdeBusInterface->IdeDeviceHandle;
    
    Status = InternalInstallSecurityInterface (
                                        BusInterfaceType, 
                                        *DeviceHandle, 
                                        SecurityInterface);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a InternalInstallSecurityInterface status : %r\n", __FUNCTION__, Status));
        FreePool(SecurityInterface);
        return Status;
    }
    
    *pSecurityInterface = SecurityInterface;
    IdeBusInterface->IdeSecurityInterface = (AMI_HDD_SECURITY_PROTOCOL *)SecurityInterface;
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
} 

/** @internal
    Sets HDD password

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
IdeSecuritySetPassword (
    IN  AMI_HDD_SECURITY_PROTOCOL       *This,
    IN UINT16                           Control,
    IN UINT8                            *Buffer,
    IN UINT16                           RevisionCode
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    UINT16                          MasterPwdIdentifier;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;

    MasterPwdIdentifier = ((AMI_IDE_BUS_PROTOCOL  *)BusInterface)->IdeDevice.IdentifyData.Master_Password_Rev_92;
    
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
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Unlocks HDD password

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
IdeSecurityUnlockPassword (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer,
    IN UINT16                      SecurityStatus
        
)
{
    
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    EFI_STATUS                  Status1;
    UINT16                      RevisionCode = 0;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    AMI_IDE_BUS_PROTOCOL        *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
    EFI_BLOCK_IO_PROTOCOL       *BlockIo;

    
    // When in Setup, Current Password is prompted for consistency when Setting a New Password
    // Or Disabling the Existing Password. Follow a Special Path only in this case.
    //*****This Case Applies on only when (1)Password is Set & Security Enabled
    //                                    (2)Unlocked
    if ((SecurityStatus & BIT1) && (!(SecurityStatus & BIT2))) {
        if (!(Control & BIT0)) {
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
                    SecurityCommonRoutine(
                                BusInterface,
                                Control,
                                Buffer,
                                SECURITY_SET_PASSWORD,
                                RevisionCode,
                                BusInterfaceType );
                }
        }
        DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Unlock Password Status = %r\n", Status));
        return Status;
    }
    
    
    Status = SecurityCommonRoutine (
                            BusInterface,
                            Control,
                            Buffer,
                            SECURITY_UNLOCK,
                            0,
                            BusInterfaceType );

    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "HddSecurity: %a Security Unlock Password Status = %r\n", __FUNCTION__, Status));
        return Status;
    }
        
    // Update the Identify device buffer
    Status = IdeUpdateIdentifyData ( 
                            BusInterface, 
                            BusInterfaceType );
    
    if (!EFI_ERROR(Status)) {
        // Check if BlockIO Protocol is already present on this device.
        Status1 = gBS->HandleProtocol(
                                IdeBusInterface->IdeDeviceHandle,
                                &gEfiBlockIoProtocolGuid,
                                (VOID**)&BlockIo);

        // Connect only if BloCkIO protocol is not installed on the device.
        if (EFI_ERROR(Status1)) {
            Status = gBS->ConnectController (
                                      IdeBusInterface->IdeControllerInterfaceHandle,
                                      NULL,
                                      NULL,   
                                      TRUE );
            if (EFI_ERROR(Status)) {
                DEBUG((DEBUG_ERROR, "HddSecurity: Failed to Connect IdeControllerHandle Status = %r\n", Status));
            }
        }
    }
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Freeze HDD Lock

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
IdeSecurityFreezeLock(
    IN AMI_HDD_SECURITY_PROTOCOL               *This
)
{
    EFI_STATUS                              Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    EFI_STATUS                              DcoFreezeLockStatus;
    UINT16                                  SecurityStatus = 0;
    COMMAND_STRUCTURE                       CommandStructure;
    IDENTIFY_DATA                           IdentifyData;
    VOID                                    *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE               BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a ReturnSecurityStatus status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    CopyMem (&IdentifyData, &((AMI_IDE_BUS_PROTOCOL *)BusInterface)->IdeDevice.IdentifyData, sizeof(IdentifyData));
    
    
#if !DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT
    if (SecurityStatus & BIT1) {
       if (IdentifyData.Reserved_76_79[3] & BIT6) {
           Status = TransferPwDataFromNvramToSmram (This);
           ASSERT_EFI_ERROR(Status);
       }
    }
#endif
    
    // Freeze Lock command will not work with the HDD is in Locked State.
    // So return with Success if the HDD is either in Locked State or Frozen state.
    if (SecurityStatus & (BIT3|BIT2)) {
       DEBUG((DEBUG_VERBOSE, "HddSecurity: HDD already in locked state\n"));
       return EFI_SUCCESS;
    }
    
    ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Command = SECURITY_FREEZE_LOCK;
    
    Status =  IdeSendNonDataCommand (
                                BusInterface,
                                CommandStructure,
                                BusInterfaceType );
    
    // if Device Configuration Overlay(DCO) feature set supported, then issue the
    // Device configure Freeze lock command.
    // After sending DCO FreezeLock cmd without error, a device shall abort further
    // DCO FreezeLock cmd until after completing the subsequent power-on reset(cold boot).
    // So,DCO FreezeLock cmd may fails in warm boots.
    if (IdentifyData.Command_Set_Supported_83 & BIT11){
        CommandStructure.Features = DEV_CONFIG_FREEZE_LOCK_FEATURES;
        CommandStructure.Command  = DEV_CONFIG_FREEZE_LOCK;
        DcoFreezeLockStatus       = IdeSendNonDataCommand ( 
                                                       BusInterface,
                                                       CommandStructure,
                                                       BusInterfaceType );
       if (EFI_ERROR (DcoFreezeLockStatus)){
           DEBUG((DEBUG_ERROR, "HddSecurity: DcoFreezeLockStatus Status = %r\n", DcoFreezeLockStatus));
       }
    }

    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Freeze Lock Status = %r\n", Status));
    
    //  Update the Identify device buffer
    Status = IdeUpdateIdentifyData (BusInterface, BusInterfaceType);
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** @internal
    Erase HDD Unit

    @param This                 Pointer HDD security protocol.
    @param Control              Bit 0 : 0/1 User/Master Password
                                Bit 8 : 0/1 High/Maximum Security level
    @param Buffer               Pointer to password buffer which will be used to 
                                when sending SecurityCommand.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
IdeSecurityEraseUnit (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;    
    COMMAND_STRUCTURE           CommandStructure;

    // Issue Security Erase Unit
    Control &= (BIT1|BIT0);  // Bit0 and Bit 1 is valid

    // Update the Identify device buffer
    IdeUpdateIdentifyData (BusInterface, BusInterfaceType);
    
    ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Command = SECURITY_ERASE_PREPARE;

    Status = IdeSendNonDataCommand ( 
                                BusInterface, 
                                CommandStructure, 
                                BusInterfaceType );
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "HddSecurity: %a IdeSendNonDataCommand Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    Status = SecurityCommonRoutine (
                            BusInterface,
                            Control,
                            Buffer,
                            SECURITY_ERASE_UNIT,
                            0,
                            BusInterfaceType );
    
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "HddSecurity: %a Security Erase Unit Status = %r\n", __FUNCTION__, Status));
        return Status;
    }

    // Update the Identify device buffer
    Status = IdeUpdateIdentifyData (BusInterface, BusInterfaceType);
#endif
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
IdeReturnSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL    *This,
    OUT UINT16                      *SecurityStatus
)
{
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    VOID                  *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL *)BusInterface;
 
    //  Check if Word 82 Bit 1 is set
    if ((IdeBusInterface->IdeDevice.IdentifyData.Command_Set_Supported_82 & BIT1)) {
        *SecurityStatus = IdeBusInterface->IdeDevice.IdentifyData.Security_Status_128;
    }
    
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit SecurityStatus : %x\n", __FUNCTION__, *SecurityStatus));
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
IdeStopSecurityModeSupport(
    IN VOID                       *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS                  Status = EFI_UNSUPPORTED;
#if ( defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) )
    EFI_HANDLE                  DeviceHandle;
    AMI_HDD_SECURITY_INTERFACE  *SecurityInterface = NULL;
    AMI_IDE_BUS_PROTOCOL        *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL *)BusInterface;

    SecurityInterface = (AMI_HDD_SECURITY_INTERFACE *)IdeBusInterface->IdeSecurityInterface;
    DeviceHandle = IdeBusInterface->IdeDeviceHandle;
    
    if (SecurityInterface == NULL) {
        return EFI_SUCCESS;
    }

    //UnInstall HDD security protocol in device handle
    Status = gBS->UninstallMultipleProtocolInterfaces(
                                            DeviceHandle,
                                            &gAmiHddSecurityProtocolGuid,
                                            SecurityInterface,
                                            NULL);

    if (!EFI_ERROR(Status)) {
        FreePool (SecurityInterface);
        SecurityInterface = NULL;
        IdeBusInterface->IdeSecurityInterface = NULL;
    }
#endif
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;   
}

