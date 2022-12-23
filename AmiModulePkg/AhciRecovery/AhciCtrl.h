//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AhciCtrl.h
    Ahci Recovery function definition

**/

#ifndef _EFI_AHCI_CTRL_H
#define _EFI_AHCI_CTRL_H

#ifndef ATAPI_BUSY_CLEAR_TIMEOUT
#define     ATAPI_BUSY_CLEAR_TIMEOUT            30000           // 30 Sec
#endif

#ifndef DMA_ATA_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATA_COMMAND_COMPLETE_TIMEOUT    30000           // 30 Sec
#endif

#ifndef DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT
#define     DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT  30000           // 30 Sec
#endif

#define     COMMAND_LIST_SIZE_PORT              0x400

#define     DIRECT_ACCESS_DEVICE                0
#define     CDROM_DEVICE                        5
#define     OPTICAL_MEMORY_DEVICE               7

#define     ATAPI_READ_10                       0x28
#define     ATAPI_READ_CAPACITY                 0x25
#define     ATAPI_REQUEST_SENSE                 0x03
#define     ATAPI_TEST_UNIT_READY               0x00


#define     MEDIUM_NOT_PRESENT                  0x01
#define     BECOMING_READY                      0x02
#define     MEDIA_CHANGED                       0x03
#define     DEVICE_ERROR                        0x04
#define     WRITE_PROTECTED_MEDIA               0x05
#define     POWER_ON_OR_DEVICE_RESET            0x06
#define     ILLEGAL_REQUEST                     0x07

#define     CDROM_BLOCK_SIZE                    2048

#define     CHK                                 0x01
#define     DF                                  0x20

typedef enum {
  ATA = 0,
  ATAPI = 1,
  PMPORT = 2
} DEVICE_TYPE;

typedef VOID (PCIE_CONTROLLER_INIT_FUNCTION)(
    IN EFI_PHYSICAL_ADDRESS PciConfigAddress, IN UINT16  VendorId
);

#pragma pack(1)

typedef struct {
    UINTN                       AhciBaseAddress;
    UINT32                      HBACapability;
    UINT32                      HBAPortImplemented;         // Bit Map
    UINT64                      PortCommandListBaseAddr;
    UINT32                      PortCommandListLength;
    UINT64                      PortCommandTableBaseAddr;
    UINT32                      PortCommandTableLength;
    UINT64                      PortFISBaseAddr;
    UINT64                      PortFISBaseAddrEnd;
    UINT64                      Address1;                   // Unmodified PortFISBaseAddr
    UINT64                      Address2;                   // Unmodified PortCommandListBaseAddr
    UINT8                       NumberofPortsImplemented;   // 1 based Count
    BOOLEAN                     AhciModeInit;
    UINT8                       BusNumber;
    UINT8                       Device;
    UINT8                       Function;
    EFI_DEVICE_PATH             *DevPath;
}AHCI_RECOVERY_CONTROLLER_INFO;

typedef struct {
    AHCI_RECOVERY_CONTROLLER_INFO    *AhciControllerInfo;
    UINT8                            PortNo;
    UINT8                            PMPortNo;
    BOOLEAN                          DevicePresent;
    EFI_PEI_BLOCK_IO_MEDIA           MediaInfo;
    EFI_PEI_BLOCK_IO2_MEDIA          MediaInfo2;
    BOOLEAN                          LookedForMedia;
    DEVICE_TYPE                      RecoveryDeviceType;
    BOOLEAN                          Lba48Bit;
    UINT8                            Lun;
    UINT8                            Atapi_Status;
    UINT64                           PortCommandListBaseAddr;
    UINT64                           PortFISBaseAddr;
    EFI_DEVICE_PATH                  *DevicePath;
    LIST_ENTRY                       Link;
}AHCI_RECOVERY_DEVICE_INFO;
    
typedef struct {
    EFI_PEI_RECOVERY_BLOCK_IO_PPI           RecoveryBlkIo;
    EFI_PEI_RECOVERY_BLOCK_IO2_PPI          RecoveryBlkIo2;
	UINT64                                  AmiExtSig;
    BOOLEAN                                 HaveEnumeratedDevices;
    UINTN                                   DeviceCount;
    LIST_ENTRY                              DeviceList;
} AHCI_RECOVERY_BLK_IO_DEV;

typedef enum {
    NON_DATA_CMD = 0,
    PIO_DATA_IN_CMD = 1,
    PIO_DATA_OUT_CMD = 2,
    DMA_DATA_IN_CMD = 3,
    DMA_DATA_OUT_CMD = 4,
    PACKET_PIO_DATA_IN_CMD = 5,
    PACKET_PIO_DATA_OUT_CMD = 6,
    PACKET_DMA_DATA_IN_CMD = 7,
    PACKET_DMA_DATA_OUT_CMD = 8,
} COMMAND_TYPE;

typedef struct{
//    UINT16 GeneralConfiguration_0;
//    UINT16 Data_1_58[58];
//    UINT32 TotalUserAddressableSectors_60;
//    UINT16 Data_61_255[195];
    UINT16  GeneralConfiguration_0;
    UINT16  Reserved_1;
    UINT16  Special_Config_2;
    UINT16  Reserved_3;
    UINT16  Reserved_4;
    UINT16  Reserved_5;
    UINT16  Reserved_6;
    UINT16  Reserved_7;
    UINT16  Reserved_8;
    UINT16  Reserved_9;
    UINT8   Serial_Number_10[20];
    UINT16  Reserved_20;
    UINT16  Reserved_21;
    UINT16  Reserved_22;
    UINT8   Firmware_Revision_23[8];
    UINT8   Model_Number_27[40];
    UINT16  Maximum_Sector_Multiple_Command_47;
    UINT16  Trusted_Computing_Support;
    UINT16  Capabilities_49;
    UINT16  Capabilities_50;
    UINT16  PIO_Mode_51;
    UINT16  Reserved_52;
    UINT16  Valid_Bits_53;
    UINT16  Reserved_54_58[5];
    UINT16  Valid_Bits_59;
    UINT32  TotalUserAddressableSectors_60;
    UINT16  SingleWord_DMA_62;
    UINT16  MultiWord_DMA_63;
    UINT16  PIO_Mode_64;
    UINT16  Min_Multiword_DMA_timing_65;
    UINT16  Manuf_Multiword_DMA_timing_66;
    UINT16  Min_PIO_Mode_timing_67;
    UINT16  Min_PIO_Mode_timing_68;
    UINT16  Reserved_69_74[6];
    UINT16  Queue_Depth_75;
    UINT16  Reserved_76_79[4];
    UINT16  Major_Revision_80;
    UINT16  Minor_Revision_81;
    UINT16  Command_Set_Supported_82;
    UINT16  Command_Set_Supported_83;
    UINT16  Command_Set_Supported_84;
    UINT16  Command_Set_Enabled_85;
    UINT16  Command_Set_Enabled_86;
    UINT16  Command_Set_Enabled_87;
    UINT16  UDMA_Mode_88;
    UINT16  Time_security_Earse_89;
    UINT16  Time_Esecurity_Earse_90;
    UINT16  Current_Power_Level_91;
    UINT16  Master_Password_Rev_92;
    UINT16  Hard_Reset_Value_93;
    UINT16  Acoustic_Level_94;
    UINT16  Reserved_95_99[5];
    UINT64  LBA_48;
    UINT16  Reserved_104_126[23];
    UINT16  Status_Notification_127;
    UINT16  Security_Status_128;
    UINT16  Reserved_129_159[31];
    UINT16  CFA_Power_Mode_160;
    UINT16  Reserved_161_175[15];
    UINT16  Media_Serial_Number_176_205[30];
    UINT16  Reserved_206_254[49];
    UINT16  Checksum_255;
} ATA_IDENTIFY_DATA;

#pragma pack()

//
// Forward reference for pure ANSI compatibility
//
typedef struct _AHCI_COMMAND_FIS AHCI_COMMAND_FIS;
typedef struct _AHCI_ATAPI_COMMAND AHCI_ATAPI_COMMAND;
typedef struct _AHCI_COMMAND_PRDT AHCI_COMMAND_PRDT;

#pragma pack(1)

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
}COMMAND_STRUCTURE;
//
// Command List Structure
//
typedef struct {
    UINT32          Ahci_Cmd_CFL:5;
    UINT32          Ahci_Cmd_A:1;
    UINT32          Ahci_Cmd_W:1;
    UINT32          Ahci_Cmd_P:1;
    UINT32          Ahci_Cmd_R:1;
    UINT32          Ahci_Cmd_B:1;
    UINT32          Ahci_Cmd_C:1;
    UINT32          Ahci_Cmd_Rsvd1:1;
    UINT32          Ahci_Cmd_PMP:4;
    UINT32          Ahci_Cmd_PRDTL:16;
    UINT32          Ahci_Cmd_PRDBC;
    UINT32          Ahci_Cmd_CTBA;
    UINT32          Ahci_Cmd_CTBAU;
    UINT32          Ahci_Cmd_Rsvd2[4];
} AHCI_COMMAND_LIST;

typedef struct {
    UINT8           Ahci_Dsfis[0x1C];               // DMA Setup Fis
    UINT8           Ahci_Dsfis_Rsvd[0x04];
    UINT8           Ahci_Psfis[0x14];               // PIO Setup Fis
    UINT8           Ahci_Psfis_Rsvd[0x0C];
    UINT8           Ahci_Rfis[0x14];                // D2H Register Fis
    UINT8           Ahci_Rfis_Rsvd[0x04];
    UINT64          Ahci_Sdbfis;                    // Set Device Bits Fis
    UINT8           Ahci_Ufis[0x40];                // Unknown FIS
    UINT8           Ahci_Ufis_Rsvd[0x60];
} AHCI_RECEIVED_FIS;

//
// Register - Host to Device FIS Layout
//
typedef struct _AHCI_COMMAND_FIS{
    UINT8           Ahci_CFis_Type;
    UINT8           AHci_CFis_PmPort:4;
    UINT8           Ahci_CFis_Rsvd1:1;
    UINT8           Ahci_CFis_Rsvd2:1;
    UINT8           Ahci_CFis_Rsvd3:1;
    UINT8           Ahci_CFis_C:1;
    UINT8           Ahci_CFis_Cmd;
    UINT8           Ahci_CFis_Features;
    UINT8           Ahci_CFis_SecNum;
    UINT8           Ahci_CFis_ClyLow;
    UINT8           Ahci_CFis_ClyHigh;
    UINT8           Ahci_CFis_DevHead;
    UINT8           Ahci_CFis_SecNumExp;
    UINT8           Ahci_CFis_ClyLowExp;
    UINT8           Ahci_CFis_ClyHighExp;
    UINT8           Ahci_CFis_FeaturesExp;
    UINT8           Ahci_CFis_SecCount;
    UINT8           Ahci_CFis_SecCountExp;
    UINT8           Ahci_CFis_Rsvd4;
    UINT8           Ahci_CFis_Control;
    UINT8           Ahci_CFis_Rsvd5[4];
    UINT8           Ahci_CFis_Rsvd6[44];
} AHCI_COMMAND_FIS;

//
// Physical Region Descriptor Table
//
typedef struct _AHCI_COMMAND_PRDT{
    UINT32          Ahci_Prdt_DBA;
    UINT32          Ahci_Prdt_DBAU;
    UINT32          Ahci_Prdt_Rsvd;
    UINT32          Ahci_Prdt_DBC:22;
    UINT32          Ahci_Prdt_Rsvd1:9;
    UINT32          Ahci_Prdt_I:1;
} AHCI_COMMAND_PRDT;

//
// Command table
//
typedef struct _AHCI_COMMAND_TABLE{
    AHCI_COMMAND_FIS        CFis;
    AHCI_ATAPI_COMMAND      AtapiCmd;
    UINT8                   Rsvd[0x30];
    AHCI_COMMAND_PRDT       PrdtTable[256];
}   AHCI_COMMAND_TABLE;

#pragma pack()

#define         ATA_SIGNATURE_32                0x00000101
#define         ATAPI_SIGNATURE_32              0xEB140101
#define         PMPORT_SIGNATURE                0x96690101
#define         PRD_MAX_DATA_COUNT              0x400000

#define         IDENTIFY_COMMAND                0xEC
#define         IDENTIFY_PACKET_COMMAND         0xA1
#define         PACKET_COMMAND                  0xA0

#define         MAX_SECTOR_COUNT_PIO            256
#if LBA48_SUPPORT
#define         MAX_SECTOR_COUNT_PIO_48         65536
#endif

#define         RECEIVED_FIS_SIZE               0x100
//
//Generic Host Control Registers
//
#define         HBA_CAP                         0x0000
#define         HBA_CAP_NP_MASK                 0x1F
#define         HBA_CAP_SAM                     BIT18
#define         HBA_CAP_SSS                     BIT27
#define         HBA_GHC                         0x0004
#define         HBA_GHC_AE                      0x80000000
#define         HBA_PI                          0x000C

//
//Port Registers
//
#define         HBA_PORTS_START                 0x0100
#define         HBA_PORTS_REG_WIDTH             0x0080
#define         HBA_PORTS_CLB                   0x0000
#define         HBA_PORTS_FB                    0x0008
#define         HBA_PORTS_IS                    0x0010
#define         HBA_PORTS_IS_CLEAR              0xFFC000FF
#define         HBA_PORTS_IS_ERR_CHK            BIT4 + BIT6 + BIT23 + BIT24 + BIT27 + \
                                                BIT28 + BIT29 + BIT30 + BIT31

#define         HBA_PORTS_CMD                   0x0018
#define         HBA_PORTS_CMD_ST                BIT0
#define         HBA_PORTS_CMD_SUD               BIT1
#define         HBA_PORTS_CMD_POD               BIT2
#define         HBA_PORTS_CMD_CR                BIT15
#define         HBA_PORTS_CMD_FRE               BIT4
#define         HBA_PORTS_CMD_FR                BIT14
#define         HBA_PORTS_CMD_CPD               BIT20
#define         HBA_PORTS_TFD                   0x0020
#define         HBA_PORTS_TFD_MASK              (BIT7 | BIT3 | BIT0)
#define         HBA_PORTS_TFD_BSY               BIT7
#define         HBA_PORTS_TFD_DRQ               BIT3
#define         HBA_PORTS_TFD_ERR               BIT0
#define         HBA_PORTS_SIG                   0x0024
#define         HBA_PORTS_SSTS                  0x0028
#define         HBA_PORTS_SSTS_DET_MASK         0x000F
#define         HBA_PORTS_SSTS_DET              0x0001
#define         HBA_PORTS_SSTS_DET_PCE          0x0003
#define         HBA_PORTS_SCTL                  0x002C
#define         HBA_PORTS_SCTL_DET_MASK         0x000F
#define         HBA_PORTS_SCTL_DET_INIT         0x0001
#define         HBA_PORTS_SCTL_SPD_NSNR         0x0
#define         HBA_PORTS_SCTL_IPM_DIS          0x00
#define         HBA_PORTS_SCTL_IPM_PSD          0x01
#define         HBA_PORTS_SCTL_IPM_PSSD         0x03
#define         HBA_PORTS_SCTL_IPM_PSD_SSD      0x0300
#define         HBA_PORTS_SERR                  0x0030
#define         HBA_PORTS_SERR_RDIE             BIT0
#define         HBA_PORTS_SERR_RCE              BIT1
#define         HBA_PORTS_SERR_TDIE             BIT8
#define         HBA_PORTS_SERR_PCDIE            BIT9
#define         HBA_PORTS_SERR_PE               BIT10
#define         HBA_PORTS_SERR_IE               BIT11
#define         HBA_PORTS_SERR_PRC              BIT16
#define         HBA_PORTS_SERR_PIE              BIT17
#define         HBA_PORTS_SERR_CW               BIT18
#define         HBA_PORTS_SERR_BDE              BIT19
#define         HBA_PORTS_SERR_DE               BIT20                // Not used
#define         HBA_PORTS_SERR_CRCE             BIT21
#define         HBA_PORTS_SERR_HE               BIT22
#define         HBA_PORTS_SERR_LSE              BIT23
#define         HBA_PORTS_SERR_TSTE             BIT24
#define         HBA_PORTS_SERR_UFT              BIT25
#define         HBA_PORTS_SERR_EX               BIT26

#define         HBA_PORTS_ERR_CHK           (HBA_PORTS_SERR_TDIE + HBA_PORTS_SERR_PCDIE +\
                                            HBA_PORTS_SERR_PE + HBA_PORTS_SERR_IE + \
                                            HBA_PORTS_SERR_PIE + \
                                            HBA_PORTS_SERR_BDE + \
                                            HBA_PORTS_SERR_DE + HBA_PORTS_SERR_CRCE + \
                                            HBA_PORTS_SERR_HE +  HBA_PORTS_SERR_LSE + \
                                            HBA_PORTS_SERR_TSTE + HBA_PORTS_SERR_UFT  + \
                                            HBA_PORTS_SERR_EX)

#define         HBA_PORTS_ERR_CLEAR         (HBA_PORTS_SERR_RDIE + HBA_PORTS_SERR_RCE +\
                                            HBA_PORTS_SERR_TDIE + HBA_PORTS_SERR_PCDIE +\
                                            HBA_PORTS_SERR_PE + HBA_PORTS_SERR_IE + \
                                            HBA_PORTS_SERR_PRC + HBA_PORTS_SERR_PIE + \
                                            HBA_PORTS_SERR_CW + HBA_PORTS_SERR_BDE + \
                                            HBA_PORTS_SERR_DE + HBA_PORTS_SERR_CRCE + \
                                            HBA_PORTS_SERR_HE +  HBA_PORTS_SERR_LSE + \
                                            HBA_PORTS_SERR_TSTE + HBA_PORTS_SERR_UFT  + \
                                            HBA_PORTS_SERR_EX)

#define         HBA_PORTS_CI                 0x0038

//
//  FIS Types
//
#define         FIS_REGISTER_H2D               0x27           // Host To Device
#define         FIS_REGISTER_H2D_LENGTH        20
#define         FIS_REGISTER_D2H               0x34           // Device To Host
#define         FIS_PIO_SETUP                  0x5F           // Device To Host
#define         HBA_CR_CLEAR_TIMEOUT           500          // AHCI 1.2 spec 10.1.2
#define         HBA_FR_CLEAR_TIMEOUT           500          // AHCI 1.2 spec 10.1.2
#define         HBA_PRESENCE_DETECT_TIMEOUT    10           // 10msec Serial ATA 1.0 Sec 5.2
#define         HBA_CI_CLEAR_TIMEOUT           200          // 200ms
#ifndef         HBA_DRQ_BSY_CLEAR_TIMEOUT
#define         HBA_DRQ_BSY_CLEAR_TIMEOUT      10000        // 10sec
#endif

#if RECOVERY_DATA_PORT_ACCESS
    //
    //Index , Data port access 
    //
#define     HBA_PORT_REG_BASE(Port) \
            (UINTN) (Port * HBA_PORTS_REG_WIDTH + HBA_PORTS_START)

#define     HBA_REG32( BaseAddr, Register ) \
            (ReadDataDword ((BaseAddr), (Register)))

#define     HBA_WRITE_REG32( BaseAddr, Register, Data ) \
            (WriteDataDword( BaseAddr, Register, Data ))

#define     HBA_REG16( BaseAddr, Register ) \
            (ReadDataWord( BaseAddr, Register ))

#define     HBA_WRITE_REG16( BaseAddr, Register, Data ) \
            (WriteDataWord( BaseAddr, Register, Data ))

#define     HBA_REG8( BaseAddr, Register ) \
            (ReadDataByte ((BaseAddr), (Register)))

#define     HBA_WRITE_REG8( BaseAddr, Register, Data ) \
            (WriteDataByte( BaseAddr, Register, Data ))

#define     HBA_REG8_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) | ((UINT8) (OrData))))

#define     HBA_REG16_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) | ((UINT16) (OrData))))

#define     HBA_REG32_OR( BaseAddr, Register, OrData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) | ((UINT32) (OrData))))

#define     HBA_REG8_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))))

#define     HBA_REG16_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) (AndData))))
 
#define     HBA_REG32_AND( BaseAddr, Register, AndData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))))

#define     HBA_REG8_AND_OR( BaseAddr, Register, AndData, OrData) \
            HBA_WRITE_REG8(BaseAddr, Register, ((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData)) | ((UINT8) (OrData))))

#define     HBA_REG16_AND_OR( BaseAddr, Register, AndData, OrData) \
            HBA_WRITE_REG16(BaseAddr, Register, ((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) (AndData)) | ((UINT16) (OrData))))

#define     HBA_REG32_AND_OR( BaseAddr, Register,AndData,  OrData) \
            HBA_WRITE_REG32(BaseAddr, Register, ((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData)) | ((UINT32) (OrData))))
  
//Ports
#define     HBA_PORT_REG8(BaseAddr, Port, Register) \
            (HBA_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG16(BaseAddr, Port, Register) \
            (HBA_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG32(BaseAddr, Port, Register) \
            (HBA_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))
		
#define     HBA_PORT_WRITE_REG8(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), Data))

#define     HBA_PORT_WRITE_REG16(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_WRITE_REG32(BaseAddr, Port, Register,Data) \
            (HBA_WRITE_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_REG8_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG8_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG16_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG16_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG32_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG32_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG8_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG8_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG16_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG16_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG32_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG32_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG8_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG8_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG16_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG16_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG32_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG32_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#else
    //
    //MMIO Access
    //
#define     MmAddress( BaseAddr, Register ) \
            ((UINTN)(BaseAddr) + \
            (UINTN)(Register) \
             )
#define     Mm32Ptr( BaseAddr, Register ) \
            ((volatile UINT32 *)MmAddress (BaseAddr, Register ))

#define     Mm16Ptr( BaseAddr, Register ) \
            ((volatile UINT16 *)MmAddress (BaseAddr, Register ))

#define     Mm8Ptr( BaseAddr, Register ) \
            ((volatile UINT8 *)MmAddress (BaseAddr, Register ))
//
//HBA Generic
//
#define     HBA_PORT_REG_BASE(Port) \
             (UINTN) (Port * HBA_PORTS_REG_WIDTH + HBA_PORTS_START)

#define     HBA_REG32( BaseAddr, Register ) \
            (*Mm32Ptr ((BaseAddr), (Register)))

#define     HBA_REG16( BaseAddr, Register ) \
            (*Mm16Ptr ((BaseAddr), (Register)))

#define     HBA_REG8( BaseAddr, Register ) \
            (*Mm8Ptr ((BaseAddr), (Register)))

#define     HBA_WRITE_REG32( BaseAddr, Register, Data ) \
            (HBA_REG32 ((BaseAddr), (Register))) = ((UINT32) (Data))

#define     HBA_WRITE_REG16( BaseAddr, Register, Data ) \
            (HBA_REG16 ((BaseAddr), (Register))) = ((UINT16) (Data))

#define     HBA_WRITE_REG8( BaseAddr, Register, Data ) \
            (HBA_REG8 ((BaseAddr), (Register))) = ((UINT8) (Data))

#define     HBA_REG8_OR( BaseAddr, Register, OrData) \
            (HBA_REG8 ((BaseAddr), (Register))) |= ((UINT8) (OrData))

#define     HBA_REG16_OR( BaseAddr, Register, OrData) \
            (HBA_REG16 ((BaseAddr), (Register))) |= ((UINT16) (OrData))

#define     HBA_REG32_OR( BaseAddr, Register, OrData) \
            (HBA_REG32 ((BaseAddr), (Register))) = (HBA_REG32 ((BaseAddr), (Register))) | ((UINT32) (OrData))

#define     HBA_REG8_AND( BaseAddr, Register, AndData) \
            (HBA_REG8 ((BaseAddr), (Register))) = (HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))

#define     HBA_REG16_AND( BaseAddr, Register, AndData) \
            (HBA_REG16 ((BaseAddr), (Register))) &= ((UINT16) (AndData))

#define     HBA_REG32_AND( BaseAddr, Register, AndData) \
            (HBA_REG32 ((BaseAddr), (Register))) = (HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))

#define     HBA_REG8_AND_OR( BaseAddr, Register, AndData, OrData) \
            (HBA_REG8 ((BaseAddr), (Register)) = \
                (((HBA_REG8 ((BaseAddr), (Register))) & ((UINT8) (AndData))) | ((UINT8) (OrData))))

#define     HBA_REG16_AND_OR( BaseAddr, Register, AndData, OrData) \
            (HBA_REG16 ((BaseAddr), (Register)) = \
                (((HBA_REG16 ((BaseAddr), (Register))) & ((UINT16) AndData)) | ((UINT16) (OrData))))

#define     HBA_REG32_AND_OR( BaseAddr, Register,AndData,  OrData) \
            (HBA_REG32 ((BaseAddr), (Register)) = \
                (((HBA_REG32 ((BaseAddr), (Register))) & ((UINT32) (AndData))) | ((UINT32) (OrData))))

//
//Ports
//
#define     HBA_PORT_REG8(BaseAddr, Port, Register) \
            (HBA_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG16(BaseAddr, Port, Register) \
            (HBA_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG32(BaseAddr, Port, Register) \
            (HBA_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port))))

#define     HBA_PORT_REG64(BaseAddr, Port, Register) \
             ((LShiftU64(((UINT64)(HBA_PORT_REG32(BaseAddr, Port, (Register+4)))),32)) | \
               (HBA_PORT_REG32(BaseAddr, Port, Register)))

#define     HBA_PORT_WRITE_REG8(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG8 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), Data))

#define     HBA_PORT_WRITE_REG16(BaseAddr, Port, Register, Data) \
            (HBA_WRITE_REG16 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_WRITE_REG32(BaseAddr, Port, Register,Data) \
            (HBA_WRITE_REG32 ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)),Data))

#define     HBA_PORT_WRITE_REG64(BaseAddr, Port, Register,Data)\
             HBA_PORT_WRITE_REG32(BaseAddr, Port, (Register+4), ((UINT32)(RShiftU64(Data,32)))); \
             HBA_PORT_WRITE_REG32(BaseAddr, Port, Register, ((UINT32)Data))
	

#define     HBA_PORT_REG8_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG8_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG16_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG16_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG32_OR(BaseAddr, Port, Register, OrData) \
            (HBA_REG32_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (OrData)))

#define     HBA_PORT_REG8_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG8_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG16_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG16_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG32_AND(BaseAddr, Port, Register, AndData) \
            (HBA_REG32_AND ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData)))

#define     HBA_PORT_REG8_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG8_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG16_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG16_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#define     HBA_PORT_REG32_AND_OR(BaseAddr, Port, Register, AndData, OrData) \
            (HBA_REG32_AND_OR ((BaseAddr), ((Register) + HBA_PORT_REG_BASE (Port)), (AndData), (OrData)))

#endif

#endif
