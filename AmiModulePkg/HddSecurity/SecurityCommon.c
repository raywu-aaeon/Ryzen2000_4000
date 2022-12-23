//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SecurityCommon.c
    HDD Security SAT3 Protocol Support Implementation.

**/
#include <HddSecurity.h>

extern BOOLEAN gMasterPasswordEnable;

/** @internal

    @endinternal
**/
UINT16
ToBigLittleEndianWord (
    IN UINT16 EndianWord
)
{
    return (((EndianWord >> 8) & 0xFF) + (EndianWord << 8));
}


/** @internal
    Updates Identify command data.IDENTIFY_DATA(Command Code: 0xEC)
    command used to update the Identify data buffer.

        
    @param *BusInterface       Pointer to current bus interface
    @param BusInterfaceType    Defines type of a Storage Bus Interface.

    @retval EFI_SUCCESS   Identify data updated successfully.
    @retval EFI_ERROR     Failed to update the identify data.

    @note  ATA/ATAPI device type should have been known already.

    @endinternal
**/
EFI_STATUS
UpdateIdentifyData (
    IN  VOID                       *BusInterface,
    IN  AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
)
{
    EFI_STATUS          Status = EFI_SUCCESS;

    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeUpdateIdentifyData (
                                BusInterface, 
                                BusInterfaceType);
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciUpdateIdentifyData (
                                BusInterface, 
                                BusInterfaceType);
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeUpdateIdentifyData (
                                BusInterface, 
                                BusInterfaceType);
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciUpdateIdentifyData (
                                        BusInterface, 
                                        BusInterfaceType);
            } else {
                Status = NvmeUpdateIdentifyData (
                                        BusInterface, 
                                        BusInterfaceType);
            }
            
        }
#endif
        
    }
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Returns whether the Device supports Security Mode or not.
    If supported, the current status of the device is returned.
    Security status information will be retrieved from buffer
    updated by IDENTIFY DEVICE(Command Code : 0xEC) command.
        
    @param *This              Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param *SecurityStatus    Security status provided for the storage device.

    @retval EFI_SUCCESS       Security Mode supported
    @retval EFI_UNSUPPORTED   Security Mode Not supported

    @retval UINT16      *SecurityStatus
    @retval             Bit 0 : Security Supported
    @retval             Bit 1 : Security Enabled
    @retval             Bit 2 : Security Locked
    @retval             Bit 3 : Security Frozen
    @retval             Bit 4 : Security Count Expired
    @retval             Bit 5 : Enhanced Security Erase supported
    @retval             Bit 6 : Enhanced Security Erase supported
    @retval             Bit 8 : Security Level 0:High, 1:Maximum

**/

EFI_STATUS
EFIAPI
ReturnSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL        *This,
    IN UINT16                           *SecurityStatus
)
{
    EFI_STATUS                   Status = EFI_SUCCESS;
    VOID                         *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE    BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeReturnSecurityStatus (
                                    This, 
                                    SecurityStatus);
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciReturnSecurityStatus (
                                    This, 
                                    SecurityStatus);
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeReturnSecurityStatus (
                                    This, 
                                    SecurityStatus);
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciReturnSecurityStatus (
                                            This, 
                                            SecurityStatus);
            } else {
                Status = NvmeReturnSecurityStatus (
                                            This, 
                                            SecurityStatus);
            }
            
        }
#endif
    }
    
     DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Sets User/Master Password using SECURITY_SET_PASSWORD
    (Command Code : 0xF1) security command.

        
    @param *This              Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param Control            Bit 0 : 0/1 User/Master Password
                              Bit 8 : 0/1 High/Maximum Security level        
    @param *Buffer(32 Bytes)  Pointer to buffer which will be used when 
                              sending SecurityCommand.
    @param  RevisionCode (Valid when Control
            Bit 0 = 1 of Master Password)

    
    @retval EFI_SUCCESS       Password set.
    @retval EFI_ERROR         Error in setting Password.

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not 32
     bytes long,pad it with zeros to create a buffer of 32 bytes.
      2. If a MasterPassword with a valid Revision code(0x0001 through 0xFFFE)
     already exists, a new MasterPassword with a different revision code
     cannot be installed.MasterPassword needs to be unlocked, disabled and
     then a new password can be installed.

**/
EFI_STATUS
EFIAPI
SecuritySetPassword (
    IN AMI_HDD_SECURITY_PROTOCOL        *This,
    IN UINT16                           Control,
    IN UINT8                            *Buffer,
    IN UINT16                           RevisionCode
)
{
    EFI_STATUS                          Status;
    VOID                                *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE           BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    UINT32                              HddDataId  = 0;
#endif

    if ((BusInterfaceType < AmiStorageInterfaceIde) || 
       ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_UNSUPPORTED;
    }
    
    // Bit0 and Bit 8 are valid
    Control &= (BIT8 | BIT0);          
    
    //  Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
    
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeSecuritySetPassword (
                                    This,
                                    Control,
                                    Buffer,
                                    RevisionCode);
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciSecuritySetPassword (
                                    This,
                                    Control,
                                    Buffer,
                                    RevisionCode);
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeSecuritySetPassword (
                                    This,
                                    Control,
                                    Buffer,
                                    RevisionCode);
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciSecuritySetPassword (
                                            This,
                                            Control,
                                            Buffer,
                                            RevisionCode);
            } else {
                Status = NvmeSecuritySetPassword (
                                            This,
                                            Control,
                                            Buffer,
                                            RevisionCode);
            }
        }
#endif
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity: Security Set Password Status = %r\n", Status));
    
    //  Update the Identify device buffer
    Status = UpdateIdentifyData ( BusInterface, BusInterfaceType );

    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    //  If Password is set successfully, save it.
    if (!(Control & BIT0)) {
        SmmHddPasswordInterface ( 
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
    
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a GatherIdeInfo status : %r\n", __FUNCTION__, Status));
        return Status;
    }

    Status = SetHddSecDataInNvram (
                            BusInterface,
                            &HddDataId,
                            Control,
                            Buffer );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a SetHddSecDataInNvram status : %r\n", __FUNCTION__, Status));
        return Status;
    }
#endif

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Unlocks the devices for media access using
    SECURITY_UNLOCK(Command Code : 0xF2) security command.

        
    @param *This           Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param Control         Bit 0 : 0/1 User/Master Password 
    @param *Buffer         Pointer to password buffer which will be used to unlock 
                           the drive

    @retval EFI_SUCCESS           Hard disk is unlocked.
    @retval EFI_DEVICE_ERROR      Failed to unlock the drive.

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
     32 bytes long, pad it with zeros to create a buffer of 32 bytes.
      2. If the password compare fails then the device returns command aborted
     to the host and decrements the unlock counter. This counter is initially
     set to five and is decremented for each password mismatch when SECURITY
     UNLOCK is issued and the device is locked. When this counter reaches
     zero then SECURITY UNLOCK and SECURITY ERASE UNIT commands are command
     aborted until a power-on reset or a hardware reset.SECURITY UNLOCK
     commands issued when the device is unlocked have no effect on the unlock
     counter.
      3. SECURITY_DISABLE_PASSWORD and SECURITY_SET_PASSWORD commands used when
     security password is set and HDD is in unlocked state. This is done to
     have consistency of output from this function.
**/

EFI_STATUS
EFIAPI
SecurityUnlockPassword (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                  Status;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    UINT16                      SecurityStatus = 0;
    UINT32                      IdePasswordFlags = 0;
#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    UINT32                      HddDataId  = 0;
#endif
    
    if ((BusInterfaceType < AmiStorageInterfaceIde) || 
       ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_UNSUPPORTED;
    }
    
    // Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a UpdateIdentifyData status : %r\n", __FUNCTION__, Status));
        return Status;
    }
    
    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a ReturnSecurityStatus status : %r\n", __FUNCTION__, Status));
        return Status;
    }

    Control &= BIT0;         // Bit0 is valid
    
    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeSecurityUnlockPassword (
                                        This,
                                        Control,
                                        Buffer,
                                        SecurityStatus);
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciSecurityUnlockPassword (
                                        This,
                                        Control,
                                        Buffer,
                                        SecurityStatus);
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeSecurityUnlockPassword (
                                        This,
                                        Control,
                                        Buffer,
                                        SecurityStatus);
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciSecurityUnlockPassword (
                                                This,
                                                Control,
                                                Buffer,
                                                SecurityStatus);
            } else {
                Status = NvmeSecurityUnlockPassword (
                                                This,
                                                Control,
                                                Buffer,
                                                SecurityStatus);
            }
        }
#endif
    }

    // When in Setup, Current Password is prompted for consistency when Setting a New Password
    // Or Disabling the Existing Password. Follow a Special Path only in this case.
    //*****This Case Applies on only when (1)Password is Set & Security Enabled
    //                                    (2)Unlocked
    if ((SecurityStatus & BIT1) && (!(SecurityStatus & BIT2))) {
        if (!(Control & BIT0)) {
            return Status;
        }
    }
    
    
    if (!EFI_ERROR(Status)) {
        // Save the Password if unlocked Successfully.
        SmmHddPasswordInterface (
                            This,
                            Control,
                            Buffer,
                            SavePassword );
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
            DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a SetHddSecDataInNvram status : %r\n", __FUNCTION__, Status));
            ASSERT_EFI_ERROR(Status);
        }
#endif

        // After unlock the HDD set the OEM default master password
        // Check if OEM_DEFAULT_MASTER_PASSWORD is enabled and
        // DISPLAY_MASTER_PASSWORD is Disabled.
        if (gMasterPasswordEnable) {
            Status = ReturnIdePasswordFlags (
                                        This,
                                        &IdePasswordFlags );
            if (!EFI_ERROR(Status) && (IdePasswordFlags & 0x0800) && (!(IdePasswordFlags & 0x0008))) {
                Status = OemSetMasterPassword (This);
            }
        }
    }

    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Disables Password authentication before media access.
    SECURITY_DISABLE_PASSWORD(Command Code : 0xF6) security
    command is used to remove the user password.

    @param *This       Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param Control    Bit 0 : 0/1 User/Master Password,
    @param *Buffer     Pointer to password buffer which will be used to when sending
                      SECURITY_DISABLE_PASSWORD command.


    @retval EFI_SUCCESS        Security mode feature disabled.
    @retval EFI_DEVICE_ERROR   Security command failed.

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
     32 bytes long,pad it with zeros to create a buffer of 32 bytes.
      2. Password should be unlocked before disabling it.
      3. SECURITY_DISABLE_PASSWORD command does not change the Master password
     that may be reactivated later by setting a User password.
      4. Normal erase mode is selected, the SECURITY ERASE UNIT command writes
     binary zeroes to all user data areas.

**/

EFI_STATUS
EFIAPI
SecurityDisablePassword (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                  Status;
    VOID                        *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE   BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;

#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    UINT32     HddDataId = 0;
    UINT8      EmptyBuffer[IDE_PASSWORD_LENGTH];
#endif

    if ((BusInterfaceType < AmiStorageInterfaceIde) || 
       ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a un supported Bus interface type : %d\n", __FUNCTION__, BusInterfaceType));
        return EFI_UNSUPPORTED;
    }

    Control &= BIT0;             // Bit0 is valid
    
#if (!DISABLE_SOFT_SET_PREV && !FORCE_HDD_PASSWORD_PROMPT ) || HDD_PASSWORD_ON_NVRAM
    //Update the Nvram buffer with NULL string.
    ZeroMem (EmptyBuffer, IDE_PASSWORD_LENGTH);

    Status = GatherIdeInfo (
                        BusInterface, 
                        BusInterfaceType, 
                        &HddDataId );

    if (!EFI_ERROR(Status)) {
        Status = SetHddSecDataInNvram (
                                BusInterface, 
                                &HddDataId, 
                                Control, 
                                EmptyBuffer );
        ASSERT_EFI_ERROR( Status );
    }
#endif
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
        case AmiStorageInterfaceAhci:
            Status = SecurityCommonRoutine (
                                        BusInterface,
                                        Control,
                                        Buffer,
                                        SECURITY_DISABLE_PASSWORD,
                                        0,
                                        BusInterfaceType );
            break;
            
        case AmiStorageInterfaceNvme:
            Status = NvmeSecuritySendCommandCommonRoutine (
                                                    BusInterface,
                                                    Control,
                                                    Buffer,
                                                    NVME_ATA_SECURITY_DISABLE_PASSWORD,
                                                    0,
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
                                                SECURITY_DISABLE_PASSWORD,
                                                0,
                                                BusInterfaceType );
                } else {
                    Status = NvmeSecuritySendCommandCommonRoutine (
                                                            BusInterface,
                                                            Control,
                                                            Buffer,
                                                            NVME_ATA_SECURITY_DISABLE_PASSWORD,
                                                            0,
                                                            BusInterfaceType );
                }
            }
#endif
            break;
    }
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Security Disable Password Status = %r\n", Status));

    // Update the Identify device buffer
    Status = UpdateIdentifyData (BusInterface, BusInterfaceType);

    if (!EFI_ERROR(Status)) {
        SmmHddPasswordInterface (
                            This,
                            Control,
                            Buffer,
                            RemovePassword );
    }

    // If the Empty string entered for the master password, Set the OEM
    // disable password with Disabled revision code.
    if (Control & BIT0) {
        EFI_STATUS      DefaultStatus;
        DefaultStatus = SetDefaultMasterPassword (This);
        ASSERT_EFI_ERROR(DefaultStatus);
    }
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** 
    Prevents any further alteration of security status on the
    device leaving the hard disk in Frozen mode. Frozen mode is
    disabled by power-off or hardware reset. SECURITY_FREEZE_LOCK
    (Command Code : 0xF5)security command is used to freeze hard disk.

        
    @param *This          Pointer to AmiHddSecurityProtocol

    @retval EFI_SUCCESS   Hard disk is successfully kept in FROZEN state.
    @retval EFI_ERROR     Security Freeze command failed.

    @note  
  Commands disabled by SECURITY FREEZE LOCK are:
      - SECURITY SET PASSWORD
      - SECURITY UNLOCK
      - SECURITY DISABLE PASSWORD
      - SECURITY ERASE PREPARE
      - SECURITY ERASE UNIT
 
**/

EFI_STATUS
EFIAPI
SecurityFreezeLock (
    IN  AMI_HDD_SECURITY_PROTOCOL *This
)
{
    EFI_STATUS                   Status = EFI_UNSUPPORTED;
    VOID                         *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE    BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterfaceType;
    
    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeSecurityFreezeLock (This);
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciSecurityFreezeLock (This);
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeSecurityFreezeLock (This);
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciSecurityFreezeLock (This);
            } else {
                Status = NvmeSecurityFreezeLock (This);
            }
            
        }
#endif
    }
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/** 
    Erases the Device content.SECURITY_ERASE_UNIT
    (Command code : 0xF4) security command is used for device erasing.
      
    @param *This         Pointer to AmiHddSecurityProtocol
    @param Control       Bit 0 : 0/1 User/Master Password
                         Bit 1 : 0/1 Normal Erase/ Enhanced Erase
    @param *Buffer       Pointer to password buffer which will be used to when 
                         sending SECURITY_ERASE_UNIT command.

    @retval EFI_SUCCESS        Successful completion of Erase command.
    @retval EFI_DEVICE_ERROR   EraseUnit command failed to complete.

    @note  
      If a device is locked with USER PASSWORD and Maximum security level set
      then only way to unlock the device with MASTER password is to erase the
      contents of the device.

**/
EFI_STATUS
EFIAPI
SecurityEraseUnit (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT16                      Control,
    IN UINT8                       *Buffer
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    if (BusInterfaceType == AmiStorageInterfaceIde) {
        
        Status = IdeSecurityEraseUnit (
                                    This,
                                    Control,
                                    Buffer );
        
    } else if (BusInterfaceType == AmiStorageInterfaceAhci) {
        
        Status = AhciSecurityEraseUnit (
                                    This,
                                    Control,
                                    Buffer );
        
    } else if (BusInterfaceType == AmiStorageInterfaceNvme) {
        
        Status = NvmeSecurityEraseUnit (
                                    This,
                                    Control,
                                    Buffer );
        
    } else if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE *)BusInterface;
            
            if (NvmeRstInterface->IsRaidHdd) {
                Status = AhciSecurityEraseUnit (
                                            This,
                                            Control,
                                            Buffer );
            } else {
                Status = NvmeSecurityEraseUnit (
                                            This,
                                            Control,
                                            Buffer );
            }
            
        }
#endif
    }
    
    DEBUG ((DEBUG_VERBOSE, "HddSecurity:%a exit status : %r\n", __FUNCTION__, Status));
    return Status;
}

/**
    Returns Password Variables and Flags.

    @param *This               Pointer to AmiHddSecurityProtocol
    @param *IdePasswordFlags   Pointer to Password Flags

    @retval EFI_SUCCESS    Password Status Flag is returned in IdePasswordFlags.
    @retval EFI_ERROR      Error while retrieving the SecurityStatus.


    @note IdePasswordFlags:
     **TBD Only Bit1, Bit03, Bit11, Bit16, Bit17 are Supported Currently

         BIT0                             User Password Support;
         BIT1                             Master Password Support;
         BIT2                             Display User Password;
         BIT3                             Display Master Password;
         BIT4                             Display User Password Status;
         BIT5                             Display Master Password Status;
         BIT6                             Freeze Lock Hdds;
         BIT7                             Single User Password;
         BIT8                             Single Master Password;
         BIT9                             System User Password as Hdd User Password;
         BIT10                            System Admin Password as Hdd Master Password;
         BIT11                            OEM Default Master Password
         BIT12                            Prompt for User Password in Post
         BIT13                            Prompt for Master Password in Post
         BIT14                            Display Security Status in Setup
         BIT15                            DUMMY Security Token.
         BIT16                            MasterPassword Set Status.
         BIT17                            UserPassword Set Status.

**/

EFI_STATUS
EFIAPI
ReturnIdePasswordFlags (
    IN AMI_HDD_SECURITY_PROTOCOL   *This,
    IN UINT32                      *IdePasswordFlags
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    UINT32                          Temp = 0;
    UINT16                          MasterPwdRev = 0;
    UINT16                          SecurityStatus = 0;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    
    if ((BusInterface ==  NULL) || 
        (BusInterfaceType < AmiStorageInterfaceIde) || 
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a unsupported bus interface type status : %r\n", __FUNCTION__, EFI_UNSUPPORTED));
        return EFI_UNSUPPORTED;
    }
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0))
            {
                AMI_IDE_BUS_PROTOCOL        *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
                MasterPwdRev = IdeBusInterface->IdeDevice.IdentifyData.Master_Password_Rev_92;
            }
#endif
            break;
        case AmiStorageInterfaceAhci:
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
            {
                SATA_DEVICE_INTERFACE       *SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;
                MasterPwdRev = SataDevInterface->IdentifyData.Master_Password_Rev_92;
            }
#endif
            break;
        case AmiStorageInterfaceNvme:
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
            {
                AMI_NVME_CONTROLLER_PROTOCOL    *NvmeDevInterface = (AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface;   
                MasterPwdRev = ToBigLittleEndianWord (NvmeDevInterface->SecReceiveBuffer.MasterPwdIdentifier);
            }
#endif
            break;
        case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            {
                NVME_RST_INTERFACE             *NvmeRstInterface = (NVME_RST_INTERFACE*)BusInterface;
            
                //TODO update HDD/NVMe from RAID driver.
                if (NvmeRstInterface->IsRaidHdd) {
                    MasterPwdRev = ((IDENTIFY_DATA *)NvmeRstInterface->IdentifyData)->Master_Password_Rev_92;
                } else {
                    MasterPwdRev = ToBigLittleEndianWord (NvmeRstInterface->SecReceiveBuffer.MasterPwdIdentifier);
                }
            }
#endif
            break;
    }
    
    if (gMasterPasswordEnable) {
        Temp |= BIT1;
    }


    if (DISPLAY_MASTER_PASSWORD) {
        Temp |= BIT3;
    }

    if (OEM_DEFAULT_MASTER_PASSWORD) {
        Temp |= BIT11;
    }
    
#if MASTER_PASSWORD_BEHAVIOUR
    if ((MasterPwdRev != 0x0000) && (MasterPwdRev != 0xFFFF) &&
        (MasterPwdRev != DISABLED_MASTER_PASSWORD_REVISION)) {
#else
    // If Master Password Revision is 0xFFFE, then it might set during manufacture. So skip it.
    if ((MasterPwdRev != 0x0000) && (MasterPwdRev != 0xFFFE) && (MasterPwdRev != 0xFFFF) &&
        (MasterPwdRev != DISABLED_MASTER_PASSWORD_REVISION)) {
#endif
        Temp |= BIT16;
    }

    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR, "HddSecurity:%a ReturnSecurityStatus status : %r\n", __FUNCTION__, Status));
        return Status;
    }

    if (SecurityStatus & BIT1) {
        Temp |= BIT17;
    }

    *IdePasswordFlags = (UINT32)Temp;
    
    DEBUG((DEBUG_VERBOSE, "HddSecurity: Password Flags : %x\n", *IdePasswordFlags));

    return EFI_SUCCESS;
}
    
/** @internal
    Installs AMI Security protocol in device handle

    @param BusInterfaceType            Type of storage interface type.
    @param DeviceHandle                Device handle
    @param SecurityInterface           Pointer to Security Interface


    @retval EFI_STATUS                 Security protocol installed successfully
            EFI_ERROR                  Error in installing protocol.
    @endinternal
**/
EFI_STATUS
InternalInstallSecurityInterface (
    IN AMI_STORAGE_BUS_INTERFACE       BusInterfaceType,
    IN EFI_HANDLE                      DeviceHandle,
    IN AMI_HDD_SECURITY_INTERFACE      *SecurityInterface
)
{
    
    EFI_STATUS                          Status;
    
    // Return error if gAmiHddSecurityProtocolGuid is already installed on the Device Handle
    Status = gBS->OpenProtocol ( 
                            DeviceHandle,
                            &gAmiHddSecurityProtocolGuid,
                            NULL,
                            NULL,
                            NULL,
                            EFI_OPEN_PROTOCOL_TEST_PROTOCOL );
    
    if (!EFI_ERROR(Status)) {
        return EFI_ALREADY_STARTED;
    }

    SecurityInterface->HddSecurityProtocol.ReturnSecurityStatus    = ReturnSecurityStatus;
    SecurityInterface->HddSecurityProtocol.SecuritySetPassword     = SecuritySetPassword;
    SecurityInterface->HddSecurityProtocol.SecurityUnlockPassword  = SecurityUnlockPassword;
    SecurityInterface->HddSecurityProtocol.SecurityDisablePassword = SecurityDisablePassword;
    SecurityInterface->HddSecurityProtocol.SecurityFreezeLock      = SecurityFreezeLock;
    SecurityInterface->HddSecurityProtocol.SecurityEraseUnit       = SecurityEraseUnit;
    SecurityInterface->HddSecurityProtocol.ReturnIdePasswordFlags  = ReturnIdePasswordFlags;
    SecurityInterface->BusInterfaceType = BusInterfaceType;
    //  Install the protocol on the device
    Status = gBS->InstallMultipleProtocolInterfaces (
                                                &DeviceHandle,
                                                &gAmiHddSecurityProtocolGuid,
                                                SecurityInterface,
                                                NULL );
    DEBUG((DEBUG_INFO, "HddSecurity: AmiHddSecurityProtocol Install Status = %r\n", Status));
    return Status;
}

/** @internal
    Determines Master password revision code.

    @param MasterPwdIdentifier      Pointer HDD security protocol.
    @param RevisionCode             0 : 0/1 User/Master Password

    @retval UINT16                  Revision code.

    @endinternal
**/
UINT16
DetermineMasterPwdRevisionCode (
    IN UINT16               MasterPwdIdentifier,
    IN UINT16               RevisionCode
)
{
    
    UINT16                Temp = 0;

    if (MASTER_PASSWORD_REVISION_SWITCH == 0) {
        RevisionCode = DEFAULT_MASTER_PASSWORD_REVISION;
    } else if (MASTER_PASSWORD_REVISION_SWITCH == 1) {
        RevisionCode = CHANGED_MASTER_PASSWORD_REVISION;
    } else if (MASTER_PASSWORD_REVISION_SWITCH == 2) {
        Temp = MasterPwdIdentifier;
        Temp++;
                
#if MASTER_PASSWORD_BEHAVIOUR
        if ((Temp == 0) || (Temp == 0xFFFF)) {
#else
        // If Master Password Revision is 0xFFFE, then it might set during manufacture. So consider that as invalid Revision Code.
        if ((Temp == 0) || (Temp == 0xFFFE) || (Temp == 0xFFFF)) {
#endif
            Temp++;
                    
            if (Temp == 0xFFFF) {
                Temp++;
            }
                    
            if (Temp == 0) {
                Temp++;
            }
        }
        RevisionCode = Temp;

        if (RevisionCode == DISABLED_MASTER_PASSWORD_REVISION) {
            RevisionCode++;

#if MASTER_PASSWORD_BEHAVIOUR
            if ((RevisionCode == 0) || (RevisionCode == 0xFFFF)) {
#else
            if ((RevisionCode == 0) || (RevisionCode == 0xFFFE) || (RevisionCode == 0xFFFF)) {
#endif
                RevisionCode++;
                        
                if (RevisionCode == 0xFFFF) {
                    RevisionCode++;
                }
                        
                if (RevisionCode == 0) {
                    RevisionCode++;
                }
            }
        }
    }
        
    return RevisionCode;
}
