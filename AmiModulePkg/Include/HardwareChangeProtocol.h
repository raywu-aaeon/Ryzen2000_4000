//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file  HardwareChangeProtocol.h

  The header file for Hardware change protocol. 

**/

#ifndef _HARDWARE_CHANGE_PROTOCOL_H_
#define _HARDWARE_CHANGE_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

// {43169678-506C-46fe-B32A-FCB301F74FBD}
#define AMI_HARDWARE_CHANGE_PROTOCOL_GUID \
   { 0x43169678, 0x506c, 0x46fe, { 0xb3, 0x2a, 0xfc, 0xb3, 0x1, 0xf7, 0x4f, 0xbd } }

// {B80A8E5B-C02A-4a31-AE12-58E46E803E89}
#define AMI_HARDWARE_CONFIG_DATA_GUID \
   { 0xb80a8e5b, 0xc02a, 0x4a31, { 0xae, 0x12, 0x58, 0xe4, 0x6e, 0x80, 0x3e, 0x89 } }

// {81c76078-bfde-4368-9790-570914c01a65}
#define AMI_SETUP_UPDATE_COUNT_GUID \
   { 0x81c76078, 0xbfde, 0x4368, { 0x97, 0x90, 0x57, 0x09, 0x14, 0xc0, 0x1a, 0x65 } }

#define AMI_HARDWARE_SIGNATURE_SETUP_UPDATE_COUNT_VARIABLE L"AmiHardwareSignatureSetupUpdateCountVar"

/**
 * Define Hardware Signature Change Flags.
 */
#define AMI_HARDWARE_SIGNATURE_PS2_KEYBOARD_CHANGE_FLAG         BIT0 
#define AMI_HARDWARE_SIGNATURE_PS2_MOUSE_CHANGE_FLAG            BIT1 
#define AMI_HARDWARE_SIGNATURE_MEMORY_SIZE_CHANGE_FLAG          BIT2 
#define AMI_HARDWARE_SIGNATURE_MEMORY_MAP_CHANGE_FLAG           BIT3 
#define AMI_HARDWARE_SIGNATURE_PCI_CHANGE_FLAG                  BIT4 
#define AMI_HARDWARE_SIGNATURE_USB_CHANGE_FLAG                  BIT5 
#define AMI_HARDWARE_SIGNATURE_VIDEO_CHANGE_FLAG                BIT6 
#define AMI_HARDWARE_SIGNATURE_DISK_CHANGE_FLAG                 BIT7

/**
 * Define the max times of Hardware Signature protocol can be called.
 */
#define AMI_HARDWARE_SIGNATURE_PROTOCOL_MAX_CALL_TIMES 20

/**
 * Hardware Signature Configuration Type
 */
typedef enum {
    AMI_HARDWARE_SIGNATURE_PS2_CONFIG,
    AMI_HARDWARE_SIGNATURE_MEMORY_SIZE_CONFIG, 
    AMI_HARDWARE_SIGNATURE_MEMORY_MAP_CONFIG,  
    AMI_HARDWARE_SIGNATURE_PCI_CONFIG,         
    AMI_HARDWARE_SIGNATURE_USB_CONFIG,         
    AMI_HARDWARE_SIGNATURE_VIDEO_CONFIG,       
    AMI_HARDWARE_SIGNATURE_DISK_CONFIG,      
    AMI_HARDWARE_SIGNATURE_MAX_TYPE_NUMBER,    
} AMI_HARDWARE_SIGNATURE_CONFIG_TYPE;


/**
 * The AMI Hardware Signature Memory Map Information Structure records 
 * the memory map information which contains memory size(Megabyte) 
 * and checksum of the runtime memory type.
**/
typedef struct {
    UINT8   MemMapCheckSum;   ///< Checksum of the runtime memory type.
    UINT32  MemoryMbSize;     ///< Total memory size(Megabyte)
} AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA;

/**
 * This AMI Hardware Signature PCI Configuration Information Structure 
 * is used for recording the PCI configuration data information  
 * includes PciNumber, BusNumber, DeviceNumber, FunctionNumber, 
 * DeviceId, VendorId.
**/
typedef struct {
    UINT16  PciNumber;
    UINT8   BusNumber;
    UINT8   DeviceNumber;
    UINT8   FunctionNumber;
    UINT16  DeviceId;
    UINT16  VendorId;
} AMI_HARDWARE_SIGNATURE_PCI_CONFIG_INFO;

/**
*  This AMI Hardware Signature PCI Data Structure records PCI configuration checksum. 
*  The checksum is calculated by using CRC32, and the CRC32 data include PciNumber, 
*  BusNumber, DeviceNumber, FunctionNumber, DeviceId, and VendorId.
**/
typedef struct {
    UINT32    PciInfoChecksum;
} AMI_HARDWARE_SIGNATURE_PCI_DATA;

/**
 * AMI Hardware Signature USB Data Structure records the USB configuration data which 
 * contains number of USB devices, checksum of VID/PID, and checksum of Port number 
 * and Interface number.
**/
typedef struct {
    UINT16  UsbNum;                       ///< Number of USB devices.
    UINT8   VidPidChecksum;               ///< Checksum of VID/PID
    UINT8   PortNumInterfaceNumChecksum;  ///< Checksum of Port number and Interface number.
} AMI_HARDWARE_SIGNATURE_USB_DATA;

/**
 * The AMI Hardware Signature Video Data Structure records the Video configuration data 
 * which contains checksum of EDID data, and checksum of resolution.   
**/
typedef struct {
    UINT8   EdidCheckNum;         ///< Checksum of EDID data. 
    UINT8   ResolutionChecksum;   ///< Checksum of resolution.
} AMI_HARDWARE_SIGNATURE_VIDEO_DATA;

/**
 * This structure represents the Disk configuration data which contains port number 
 * and serial number .
**/
typedef struct {
    UINT32    PortNumber;        ///< Port number.
    UINT8     IdentifyData[20];  ///< Identify Data.
} AMI_HARDWARE_SIGNATURE_DISK_CONFIG_INFO; 

/**
*  This AMI Hardware Signature DISK Data structure records the Disk configuration data 
*  with checksum.
**/
typedef struct {
    UINT32    DiskInfoChecksum; ///< The checksum included IDE Channel, Device , Serial number.
} AMI_HARDWARE_SIGNATURE_DISK_DATA;

/** 
 * The AMI Hardware Signature Configuration Data structure records the hardware configuration 
 * data which contains PS2 Keyboard/Mouse configuration, Memory Map configuration, 
 * PCI configuration Data, USB configuration Data,  Video configuration data, Disk configuration data, 
 * Firmware update date/time, and Checksum which external function given. 
**/  
typedef struct {
    BOOLEAN                                     BitPs2Keyboard;     ///< The present state of PS2 Keyboard.
    BOOLEAN                                     BitPs2Mouse;        ///< The present state of PS2 Mouse.  
    AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA      MemMapData;         ///< Memory configuration data.
    AMI_HARDWARE_SIGNATURE_PCI_DATA             PciData;            ///< PCI configuration data.
    AMI_HARDWARE_SIGNATURE_USB_DATA             UsbData;            ///< USB configuration data.
    AMI_HARDWARE_SIGNATURE_VIDEO_DATA           VideoData;          ///< Video configuration data.
    AMI_HARDWARE_SIGNATURE_DISK_DATA            DiskData;           ///< Disk configuration data.
    UINT32                                      SetupUpdateCount;
    UINT32                                      ReturnChecksum[AMI_HARDWARE_SIGNATURE_PROTOCOL_MAX_CALL_TIMES]; ///< Checksum which the external function given.
    UINT16                                      BiosBuildYear;
    UINT8                                       BiosBuildMonth;
    UINT8                                       BiosBuildDay;
    UINT8                                       BiosBuildHour;
    UINT8                                       BiosBuildMinute;
    UINT8                                       BiosBuildSecond;
} AMI_HARDWARE_SIGNATURE_CONFIG_DATA;

/**
 * The AMI Set Hardware Signature Configuration Data function is used for setting configuration data.
**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_SET_HARDWARE_SIGNATURE_CONFIG_DATA) (
    IN AMI_HARDWARE_SIGNATURE_CONFIG_TYPE ConfigType, 
    IN UINTN BufferSize,
    IN VOID *Buffer
);

/** 
 * The AMI Get Hardware Signature Configuration Data From NVRAM function is used for getting configuration data from NVRAM.
**/
typedef 
EFI_STATUS 
(EFIAPI *AMI_GET_HARDWARE_SIGNATURE_CONFIG_DATA_FROM_NVRAM) (
    IN OUT AMI_HARDWARE_SIGNATURE_CONFIG_DATA *HardwareConfigData ///< The checksum of hardware configuration data.
);

/**
 * The AMI Signal Hardware Signature Change function is used for other modules setting return value.
**/ 
typedef 
EFI_STATUS 
(EFIAPI *AMI_SIGNAL_HARDWARE_SIGNATURE_CHANGE) (
    IN UINT32 ReturnChecksum ///<The checksum that external function reported.
);

/**
 * This structure represents the HardwareSignature protocol.   
**/  
typedef struct {
    AMI_SET_HARDWARE_SIGNATURE_CONFIG_DATA              SetHardwareConfigData;
    AMI_GET_HARDWARE_SIGNATURE_CONFIG_DATA_FROM_NVRAM   GetHardwareConfigDataFromNvram;
    AMI_SIGNAL_HARDWARE_SIGNATURE_CHANGE                SignalHardwareSignatureChange;
} AMI_HARDWARE_SIGNATURE_PROTOCOL;

EFI_STATUS 
EFIAPI
AmiHardwareSignatureSetHardwareConfigData(
    IN AMI_HARDWARE_SIGNATURE_CONFIG_TYPE ConfigType, 
    IN UINTN BufferSize,
    IN VOID *Buffer
);

EFI_STATUS 
EFIAPI
AmiHardwareSignatureGetHardwareConfigDataFromNvram(
    IN OUT AMI_HARDWARE_SIGNATURE_CONFIG_DATA *HardwareConfigData
);

EFI_STATUS 
EFIAPI 
AmiSignalHardwareSignatureChange( 
    IN UINT32 ReturnChecksum );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

