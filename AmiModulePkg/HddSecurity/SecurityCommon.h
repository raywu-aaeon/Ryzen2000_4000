//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SecurityCommon.h
    HDD Security SAT3 Protocol Support Implementation.

**/

#ifndef _AMI_SECURITY_COMMON_H_
#define _AMI_SECURITY_COMMON_H_

/** @internal

    @endinternal
**/
UINT16
ToBigLittleEndianWord (
    IN UINT16 EndianWord
);

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
);

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
);

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
    IN  AMI_HDD_SECURITY_PROTOCOL   *This,
    UINT16                          Control,
    UINT8                           *Buffer,
    UINT16                          RevisionCode
);

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
    AMI_HDD_SECURITY_PROTOCOL   *This,
    UINT16                      Control,
    UINT8                       *Buffer
);

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
);

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
);

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
    AMI_HDD_SECURITY_PROTOCOL   *This,
    UINT16                      Control,
    UINT8                       *Buffer
);

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
    AMI_HDD_SECURITY_PROTOCOL   *This,
    UINT32                      *IdePasswordFlags
);

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
    AMI_STORAGE_BUS_INTERFACE  BusInterfaceType,
    EFI_HANDLE                      DeviceHandle,
    AMI_HDD_SECURITY_INTERFACE      *SecurityInterface
);

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
    IN OUT AMI_HDD_SECURITY_INTERFACE   **SecurityInterface,
    IN OUT EFI_HANDLE                   *DeviceHandle
 );

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
);

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
);

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
);

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
);

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
);

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
);

/** @internal
    Unlocks HDD password

    @param This                 Pointer HDD security protocol.
    @param ControlBit           0 : 0/1 User/Master Password
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
        
);

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
);

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
        
);

/** @internal
    Freeze HDD password

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
IdeSecurityFreezeLock(
    IN AMI_HDD_SECURITY_PROTOCOL               *This
);

/** @internal
    Freeze AHCI Lock

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
AhciSecurityFreezeLock (
    IN AMI_HDD_SECURITY_PROTOCOL *This
);

/** @internal
    Freeze NVMe Lock

    @param This                 Pointer HDD security protocol.

    @retval EFI_STATUS         EFI_SUCCESS/EFI_DEVICE_ERROR

    @endinternal
**/
EFI_STATUS
NvmeSecurityFreezeLock (
    IN AMI_HDD_SECURITY_PROTOCOL        *This
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);

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
);
#endif
