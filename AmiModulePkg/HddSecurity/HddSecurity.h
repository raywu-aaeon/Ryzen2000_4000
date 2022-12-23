//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file HddSecurity.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the HddSecurity driver

**/

#ifndef _HDD_SECURITY_H_
#define _HDD_SECURITY_H_

#include <Token.h>
#include <PiDxe.h>
#include <HddSecurityCommon.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/DevicePathLib.h>
#include <IndustryStandard/Atapi.h>
#include <IndustryStandard/Pci30.h>
#include <IndustryStandard/Nvme.h>
#include <Protocol/AmiHddSecurityInit.h>
#include <Protocol/NvmExpressPassthru.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/AtaPassThru.h>
//AmiIdeBus.h requires BlockIo.h
#include <Protocol/BlockIo.h>
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT == 1))
#ifndef DLINK
typedef struct _AMI_LINK DLINK;
typedef struct _AMI_LIST DLIST;
#endif
#include <Protocol/AmiAhciBus.h>
#endif
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT == 1))
#include <Protocol/AmiNvmeController.h>
#endif
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT == 1))
#include <Include/NvmeRstPwdIncludes.h>
#endif
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT == 1) )
#include <Protocol/AmiIdeBus.h>
#endif
#include <SecurityCommon.h>

#define HDD_CONVERT_TO_WSTRING(a) L###a

// Size of SMM communicate header, without including the Data.
#define SMM_COMMUNICATE_HEADER_SIZE             (OFFSET_OF (EFI_SMM_COMMUNICATE_HEADER, Data))

#define HDD_SECURITY_DATASIZE                   9
#define HDD_PASSWORD_SIZE                       sizeof(HDD_PASSWORD) // Size of HDD Password DATA structure size

#ifndef SATA_COMMAND_TIMEOUT
#define SATA_COMMAND_TIMEOUT                    5   // 5 Sec
#endif

#ifndef NVME_COMMAND_TIMEOUT
#define NVME_COMMAND_TIMEOUT                    1
#endif

#define HDD_PWD_ENCRYPTION_KEY                  "H?p1mA*k920_84o3d^!z@L.x4$kY64"

// Storage Security Protocol
#define SECURITY_PROTOCOL_INFORMATION           0x00
#define SECURITY_PROTOCOL_1                     0x01
#define SECURITY_PROTOCOL_2                     0x02
#define SECURITY_PROTOCOL_SDCARD_TRUSTED_FLASH  0xED
#define SECURITY_PROTOCOL_IEEE1667              0xEE
#define NVME_SECUIRTY_SECP                      0xEF
#define NVME_SECURITY_RECEIVE_BUFFER_SIZE       0x10
#define NVME_SECURITY_SEND_BUFFER_SIZE          0x24

typedef enum {
    SavePassword,
    RemovePassword
} HDD_SECURITY_PASSWORD_ACTION;

#pragma pack(1)

typedef struct _SP0_TRUSTED_RECEIVE_PARAMETER_DATA { 
    UINT8       Reserved[6]; 
    UINT8       ListLengthHigh; 
    UINT8       ListLengthLow; 
    UINT8       SupportedSPList[502]; 
    UINT8       PadBytesHigh; 
    UINT8       PadBytesLow; 
} SP0_TRUSTED_RECEIVE_PARAMETER_DATA;

typedef struct _HDD_SEC_DATA {
    UINT16      UserMaster;           // Bit 0 - MasterPwd Presence Bit 1 - UserPwd Presence
    UINT16      UserPasswordLength;
    UINT16      MasterPasswordLength;
    UINT8       HddUserPassword[IDE_PASSWORD_LENGTH];
    UINT8       HddMasterPassword[IDE_PASSWORD_LENGTH];
} HDD_SEC_DATA;

#pragma pack()

#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT == 1) ) && (defined(AHCI_SUPPORT) && (AHCI_SUPPORT == 0) )
typedef struct _AHCI_ATAPI_COMMAND{
    UINT8           Ahci_Atapi_Command[0x10];
} AHCI_ATAPI_COMMAND;

typedef struct{
    VOID                        *Buffer;
    UINT32                      ByteCount;
    UINT8                       Features;
    UINT8                       FeaturesExp;
    UINT16                      SectorCount;
    UINT8                       LBALow;
    UINT8                       LBALowExp;
    UINT8                       LBAMid;
    UINT8                       LBAMidExp;
    UINT8                       LBAHigh;
    UINT8                       LBAHighExp;
    UINT8                       Device;
    UINT8                       Command;
    UINT8                       Control;
    AHCI_ATAPI_COMMAND          AtapiCmd;
} COMMAND_STRUCTURE;
#endif


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
);

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
    IN  VOID                        *IdeBusInterface,
    IN UINT16                       Control,
    IN UINT8                        *Buffer,
    IN UINT8                        SecurityCommand,
    IN UINT16                       RevisionCode,
    IN AMI_STORAGE_BUS_INTERFACE    BusInterfaceType
);

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
);

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
);

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
);

/** @internal
    Transfers Stored Data from NVRAM to SMRAM.

    @param *This         Pointer to AMI_HDD_SECURITY_PROTOCOL

    @retval EFI_SUCCESS        Password saved in SMRAM.
    @retval EFI_DEVICE_ERROR   Password not saved in SMRAM.

    @endinternal
**/
EFI_STATUS
TransferPwDataFromNvramToSmram (
    IN  AMI_HDD_SECURITY_PROTOCOL   *This
);

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
);

/** @internal
    Manages HDD Password in SMM area.

    @param *This       Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param Control     Bit 0 : 0/1 User/Master Password
    @param Buffer      Pointer to password buffer which will be used to when sending
                       SecurityCommand.
    @param  Action     Save/remove HDD password in SMM area. 

    @retval EFI_SUCCESS        Password saved which will be used to unlock the drive
                               during S3 resume.
    @retval EFI_DEVICE_ERROR   Error in saving Password.

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
         32 bytes long, pad it with zeros to create a buffer of 32 bytes.
         
    @endinternal
**/

EFI_STATUS
SmmHddPasswordInterface (
    AMI_HDD_SECURITY_PROTOCOL           *This,
    UINT16                              Control,
    UINT8                               *Buffer,
    HDD_SECURITY_PASSWORD_ACTION        PasswordAction
);

/**
    This function creates event to 
    1. store NVMe PCI configuration data to Boot script if NVMe drive
    2. store drive unlock context to boot script
    
    @param BusInterfaceType   Controller Interface type to enable security support

    @retval 
        EFI_SUCCESS           Events created successfully      
        EFI_ERROR             Error in creating events
**/
EFI_STATUS
CreateSmmCommunicateEvents (
    IN AMI_STORAGE_BUS_INTERFACE        BusInterfaceType,
    IN AMI_HDD_SECURITY_INTERFACE       *SecurityInterface
);

/**
    This function allocates Runtime memory for SMM communication buffer
    when SMM HDD security support enabled.

    @param NONE

    @retval 
        EFI_SUCCESS         Runtime memory allocated
        EFI_ERROR           Out of resource.
**/
EFI_STATUS
AllocateSmmCommunicateBuffer ();

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
);

#endif
