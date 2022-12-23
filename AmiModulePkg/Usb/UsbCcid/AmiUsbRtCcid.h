//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiUsbRtCcid.h
    AMI Usb CCID driver definitions

**/

#ifndef _EFI_CCID_RT_H
#define _EFI_CCID_RT_H

//#include    "UsbDef.h"
#include <Uefi.h>
#include <IndustryStandard/Usb.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/UsbIo.h>
#include <Protocol/AmiUsbCcid.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiUsbLib.h>

#ifndef USB_CCID_DEBUG
#define USB_CCID_DEBUG(UsbErrorLevel, ...) \
    if ((gUsbData == NULL) && ((UsbErrorLevel) & (0xFF))){\
        SMDbgPrint( (const CHAR8*) __VA_ARGS__);\
    }
#endif
typedef struct _DEV_INFO DEV_INFO;

//Define USB_DEBUG_MESSAGES_BITMAP
#define DEBUG_HC_POLL       BIT0
#define DEBUG_HC            BIT1
#define DEBUG_BUS           BIT2    //same as org DEBUG_LEVEL_USBBUS
#define DEBUG_DEV_INIT      BIT3    //same as org Lv3

//CCID APIs
#define    USB_CCID_SMARTCLASSDESCRIPTOR   0x000
#define    USB_CCID_ATR                    0x001
#define    USB_CCID_POWERUP_SLOT           0x002
#define    USB_CCID_POWERDOWN_SLOT         0x003
#define    USB_CCID_GET_SLOT_STATUS        0x004
#define    USB_CCID_XFRBLOCK               0x005
#define    USB_CCID_GET_PARAMETERS         0x006

//SMART CARD PROTOCOL APIs
#define    USB_SMART_CARD_READER_CONNECT       0x007
#define    USB_SMART_CARD_READER_DISCONNECT    0x008
#define    USB_SMART_CARD_READER_STATUS        0x009
#define    USB_SMART_CARD_READER_TRANSMIT      0x00A
#define    USB_SMART_CARD_READER_CONTROL       0x00B
#define    USB_SMART_CARD_READER_GET_ATTRIB    0x00C

typedef     struct  _ICC_DEVICE ICC_DEVICE;
typedef     struct  _SMARTCLASS_DESC SMARTCLASS_DESC;
typedef     struct  _ATR_DATA ATR_DATA;

#define    MAX_ATR_LENGTH                32
// ATR data dequence is T0, TA1, TB1, TC1, TD1, TA2, TB2, TC2, TD2, TA3... etcs

//    
//         equates for bVoltageSupport
//
#define    AUTO_VOLT                    0x00
#define    VOLT_5                       0x01
#define    VOLT_3                       0x02
#define    VOLT_18                      0x04


//    
//         equates for Features
//
#define    AUTO_PARAMETER_CONFIG          0x02
#define    AUTO_ACTIVATION_OF_ICC         0x04
#define    AUTO_ACTIVATION_VOLT_SELECTION 0x08
#define    AUTO_ICC_CLOCK_FREQ            0x10
#define    AUTO_BAUD_RATE_SELECTION       0x20
#define    AUTO_PPS_NEGOTIATION_CCID      0x40
#define    AUTO_PPS_NEGOTIATION_ACTIVE    0x80
#define    STOP_CLOCK_MODE                0x100
#define    NAD_OTHER_THAN_00              0x200
#define    AUTO_IFSD_EXCHANGE             0x400
#define    CHARACTER_LEVEL_EXCHANGE       0x00000
#define    TDPU_LEVEL_EXCHANGE            0x10000
#define    SHORT_ADPU_LEVEL_EXCHANGE      0x20000
#define    EXT_ADPU_LEVEL_EXCHANGE        0x40000

#define    PC_TO_RDR_ICCPOWERON           0x62
#define    PC_TO_RDR_ICCPOWEROFF          0x63
#define    PC_TO_RDR_GETSLOTSTATUS        0x65
#define    PC_TO_RDR_XFRBLOCK             0x6F
#define    PC_TO_RDR_GETPARAMETERS        0x6C
#define    PC_TO_RDR_RESETPARAMETERS      0x6D
#define    PC_TO_RDR_SETPARAMETERS        0x61
#define    PC_TO_RDR_ESCAPE               0x6B
#define    PC_TO_RDR_ICCCLOCK             0x6E
#define    PC_TO_RDR_T0APDU               0x6A
#define    PC_TO_RDR_SECURE               0x69
#define    PC_TO_RDR_MECHANICAL           0x71
#define    PC_TO_RDR_ABORT                0x72
#define    PC_TO_RDR_SETDATARATEANDCLOCK  0x73


#define    RDR_TO_PC_DATABLOCK            0x80
#define    RDR_TO_PC_SLOTSTATUS           0x81
#define    RDR_TO_PC_PARAMETERS           0x82
#define    RDR_TO_PC_ESCAPE               0x83
#define    RDR_TO_PC_DATARATEANDCLOCK     0x84

#define RDR_TO_PC_NOTIFYSLOTCHANGE        0x50
#define RDR_TO_PC_HARDWAREERROR           0x51
//
// BIT definition for ConfiguredStatus
//
#define ICCPRESENT                        0x01
#define VOLTAGEAPPLIED                    0x02
#define BAUDRATEPROGRAMMED                0x04
#define ATRDATAPRESENT                    0x08
#define CARDREMOVED                       0x40
#define CONFIGFAILED                      0x80

#define IBLOCK      0x00
#define RBLOCK      0x80
#define SBLOCK      0xC0


// Codes for access mode
#define SCARD_AM_READER                   0x0001 // Exclusive access to reader
#define SCARD_AM_CARD                     0x0002 // Exclusive access to card

// Codes for card action
#define SCARD_CA_NORESET                  0x0000 // Do not reset card
#define SCARD_CA_COLDRESET                0x0001 // Perform a cold reset
#define SCARD_CA_WARMRESET                0x0002 // Perform a warm reset
#define SCARD_CA_UNPOWER                  0x0003 // Power off the card
#define SCARD_CA_EJECT                    0x0004 // Eject the card

// Protocol types
#define SCARD_PROTOCOL_UNDEFINED          0x0000
#define SCARD_PROTOCOL_T0                 0x0001
#define SCARD_PROTOCOL_T1                 0x0002
#define SCARD_PROTOCOL_RAW                0x0004

// Smart Card Reader Status
#define SCARD_UNKNOWN                     0x0000
#define SCARD_ABSENT                      0x0001
#define SCARD_INACTIVE                    0x0002
#define SCARD_ACTIVE                      0x0003


#define EP_DESC_FLAG_TYPE_BITS  0x03    //Bit 1-0: Indicate type of transfer on endpoint
#define EP_DESC_FLAG_TYPE_CONT  0x00    //Bit 1-0: 00 = Endpoint does control transfers
#define EP_DESC_FLAG_TYPE_ISOC  0x01    //Bit 1-0: 01 = Endpoint does isochronous transfers
#define EP_DESC_FLAG_TYPE_BULK  0x02    //Bit 1-0: 10 = Endpoint does bulk transfers
#define EP_DESC_FLAG_TYPE_INT   0x03    //Bit 1-0: 11 = Endpoint does interrupt transfers
#define DESC_TYPE_CONFIG        2   // Configuration Descriptor (Type 2)
#define DESC_TYPE_INTERFACE     4   // Interface Descriptor (Type 4)
#define DESC_TYPE_ENDPOINT      5   // Endpoint Descriptor (Type 5)
#define USB_REQ_TYPE_DEVICE         0x00    //  00000 = Device
#define USB_REQ_TYPE_INTERFACE      0x01    //  00001 = Interface
#define USB_REQ_TYPE_STANDARD       0x00    //  00 = Standard USB request
#define USB_REQ_TYPE_CLASS          0x20    //  01 = Class specific
#define USB_REQ_TYPE_OUTPUT         0x00    //  0 = Host sending data to device
#define USB_REQ_TYPE_INPUT          0x80    //  1 = Device sending data to host
#define EP_DESC_ADDR_DIR_BIT    0x80    //Bit 7: Direction of endpoint, 1/0 = In/Out
#define EP_DESC_ADDR_EP_NUM     0x0F    //Bit 3-0: Endpoint number
#define USB_RQ_GET_DESCRIPTOR       ((0x06 << 8) | USB_REQ_TYPE_INPUT  | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE)

//CCID Class specific request
#define CCID_CLASS_SPECIFIC_ABORT                   (0x01 << 8) | USB_REQ_TYPE_DEVICE | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE     
#define CCID_CLASS_SPECIFIC_GET_CLOCK_FREQUENCIES   (0x02 << 8) | USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE    
#define CCID_CLASS_SPECIFIC_GET_DATA_RATES          (0x03 << 8) | USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE     

// Error returned from API handler
#define USB_SUCCESS             0x000
#define USB_PARAMETER_ERROR     0x010
#define USB_NOT_SUPPORTED       0x020
#define USBAPI_INVALID_FUNCTION 0x0F0
#define USB_ERROR               0x0FF

typedef enum {
  T0_PROTOCOL,
  T1_PROTOCOL    
} TRANSMISSION_PROTOCOL;

//I-Block information
#define NSBIT       0x40
#define MBIT       0x20

// S-Block Information
#define     RESYNCH_REQUEST     0xC0
#define     IFS_REQUEST         0xC1
#define     ABORT_REQUEST       0xC2
#define     WTX_REQUEST         0xC3

#define     WTX_RESPONSE        0xE3
#define     ABORT_RESPONSE      0xE2
#define     IFS_RESPONSE        0xE1
#define     RESYNCH_RESPONSE    0xE0


#define     I_BLOCK_MATCH                       0x01
#define     I_BLOCK_RESEND                      0x02

#define     SEND_R_BLOCK_0                      0x03
#define     SEND_R_BLOCK_1                      0x04

#define     GET_DATA_T1_CHAR                    0x05

#define     T1_CHAR_CMD_PHASE                   0x06
#define     T1_CHAR_DATA_PHASE                  0x07
#define     RESEND_BLOCK                        0x08


    
#define     BLOCK_TRANSMISSION_TERMINATE        0xFF
#define     BLOCK_TRANSMISION_SUCCESS           0x00
#define     MAX_CCID_DATA_RATES                 255
#define     MAX_CLOCK_FREQUENCIES               255
#define     MAX_ICC_DEVICE                      255
#define     MAX_CCID_DEV_INFO                   255
#define     USB_API_CCID_DEVICE_REQUEST         0x34
#define     MAX_CCID_NOTIFICATIONS_COUNT             100
#define USB_CCID_USE_INT_INS_REMOVAL                  0x00080000
#define USB_CCID_DEV_SUPPORT            0x00000020

// Definition of CCID class
#define BASE_CLASS_CCID_STORAGE     0x0B        // SMART device class
#define SUB_CLASS_CCID              0x00        // SubClass
#define PROTOCOL_CCID               0x00        // Interface Protocol
#define DESC_TYPE_SMART_CARD        0x21         // Smart Card Descriptor (Type 21h)

#define MICROSECOND                 10
#define MILLISECOND                 (1000 * MICROSECOND)
#define ONESECOND                   (1000 * MILLISECOND)
#define COUNTOF(x) (sizeof(x)/sizeof((x)[0]))
#define USB_CCID_TRANSFER_TIMEOUT   200
#define USB_CCID_BULK_TIMEOUT       200
#define MAX_CCID_CONTROL_DATA_SIZE  0x200

#define ATOMIC(a) {\
        EFI_TPL savetpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);\
        {a;}\
        gBS->RestoreTPL(savetpl);   \
}\
/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_GETSMARTCLASSDESCRIPTOR CCID_GETSMARTCLASSDESCRIPTOR;
typedef struct _CCID_GETSMARTCLASSDESCRIPTOR *FPCCID_GETSMARTCLASSDESCRIPTOR;
struct _CCID_GETSMARTCLASSDESCRIPTOR{
    OUT UINTN            ResponseBuffer;
    IN  UINT8            Slot;
    OUT UINTN            DevInfo;            
};


/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_ATR CCID_ATR;
typedef struct _CCID_ATR *FPCCID_ATR;
struct _CCID_ATR{
    IN UINT8            Slot;
    IN OUT UINTN        ATRData;
    OUT UINTN           DevInfo;
};


/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_POWERUP_SLOT CCID_POWERUP_SLOT;
typedef struct _CCID_POWERUP_SLOT *FPCCID_POWERUP_SLOT;
struct _CCID_POWERUP_SLOT{
    IN UINT8             Slot;
    OUT UINT8            Status;
    OUT UINT8            Error;
    IN OUT UINTN         ATRData;
    OUT UINTN            DevInfo;                        
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_POWERDOWN_SLOT CCID_POWERDOWN_SLOT;
typedef struct _CCID_POWERDOWN_SLOT *FPCCID_POWERDOWN_SLOT;
struct _CCID_POWERDOWN_SLOT{
    IN  UINT8            Slot;
    OUT UINT8            Status;
    OUT UINT8            Error;
    OUT UINTN            DevInfo;            
};


/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_GETSLOT_STATUS CCID_GETSLOT_STATUS;
typedef struct _CCID_GETSLOT_STATUS *FPCCID_GETSLOT_STATUS;
struct _CCID_GETSLOT_STATUS{
    OUT UINT8            Status;
    OUT UINT8            Error;
    OUT UINT8            ClockStatus;    
    IN  UINT8            Slot;
    OUT UINTN            DevInfo;            
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_CCID_XFRBLOCK CCID_XFRBLOCK;
typedef struct _CCID_CCID_XFRBLOCK *FPCCID_XFRBLOCK;
struct _CCID_CCID_XFRBLOCK{
    IN UINTN             CmdLength;
    IN UINTN             CmdBuffer;
    IN UINT8             ISBlock;
    OUT UINT8            Status;
    OUT UINT8            Error;
    IN OUT UINTN         ResponseLength;
    OUT UINTN            ResponseBuffer;
    IN  UINT8            Slot;
    OUT UINTN            DevInfo;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _CCID_GET_PARAMS CCID_GET_PARAMS;
typedef struct _CCID_GET_PARAMS *FPCCID_GET_PARAMS;
struct _CCID_GET_PARAMS{
    OUT UINT8            Status;
    OUT UINT8            Error;
    IN OUT UINTN         ResponseLength;
    OUT UINTN            ResponseBuffer;
    IN  UINT8            Slot;
    OUT UINTN            DevInfo;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_CONNECT SMART_CARD_READER_CONNECT;
typedef struct _SMART_CARD_READER_CONNECT *FPSMART_CARD_READER_CONNECT;
struct _SMART_CARD_READER_CONNECT{
    IN  UINT8            Slot;
    IN  UINTN            DevInfo;
    IN  UINT32           AccessMode;
    IN  UINT32           CardAction;
    IN  UINT32           PreferredProtocols;
    OUT UINTN            ActiveProtocol;
    OUT EFI_STATUS       EfiStatus;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_DISCONNECT SMART_CARD_READER_DISCONNECT;
typedef struct _SMART_CARD_READER_DISCONNECT *FPSMART_CARD_READER_DISCONNECT;
struct _SMART_CARD_READER_DISCONNECT{
    IN  UINT8            Slot;
    IN  UINTN            DevInfo; 
    IN  UINT32           CardAction;
    OUT EFI_STATUS       EfiStatus;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_STATUS SMART_CARD_READER_STATUS;
typedef struct _SMART_CARD_READER_STATUS *FPSMART_CARD_READER_STATUS;
struct _SMART_CARD_READER_STATUS {
    IN  UINT8            Slot;
    IN  UINTN            DevInfo;
    OUT UINTN            ReaderName;
    IN OUT UINTN         ReaderNameLength;
    OUT UINTN            State;
    OUT UINTN            CardProtocol;
    OUT UINTN            Atr;
    IN OUT UINTN         AtrLength;
    OUT EFI_STATUS       EfiStatus;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_TRANSMIT SMART_CARD_READER_TRANSMIT;
typedef struct _SMART_CARD_READER_TRANSMIT *FPSMART_CARD_READER_TRANSMIT;
struct _SMART_CARD_READER_TRANSMIT{
    IN  UINT8            Slot;
    IN  UINTN            DevInfo;
    IN  UINTN            CAPDU;
    IN  UINTN            CAPDULength;
    OUT UINTN            RAPDU;
    IN OUT UINTN         RAPDULength;
    OUT EFI_STATUS       EfiStatus;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_CONTROL SMART_CARD_READER_CONTROL;
typedef struct _SMART_CARD_READER_CONTROL *FPSMART_CARD_READER_CONTROL;
struct _SMART_CARD_READER_CONTROL{
    IN  UINT8            Slot;
    IN  UINTN            DevInfo;
    IN UINT32            ControlCode;
    IN UINTN             InBuffer;
    IN UINTN             InBufferLength;
    OUT UINTN            OutBuffer;
    IN OUT UINTN         OutBufferLength;
    OUT EFI_STATUS       EfiStatus;
};

/**
    This is a Core Procedure URP  structure for
    the BIOS API call USB_API_CCID_DEVICE_REQUEST command (API #2Fh )
**/
typedef struct _SMART_CARD_READER_GETATTRIB SMART_CARD_READER_GETATTRIB;
typedef struct _SMART_CARD_READER_GETATTRIB *FPSMART_CARD_READER_GETATTRIB;
struct _SMART_CARD_READER_GETATTRIB{
    IN  UINT8            Slot;
    IN  UINTN            DevInfo;
    IN UINT32            Attrib;
    OUT UINTN            OutBuffer;
    IN OUT UINTN         OutBufferLength;
    OUT EFI_STATUS       EfiStatus;
};
//    Time extension Calculation (worst case scenario assumed)

//1ETU = F/D * 1/f =  2048/1*1/4Mhz = 0.000512sec

// Use Maximum value for BWI which is 9 and minimum Freq 4Mhz for calculation
//BWT = 11 ETU + (2BWI * 960 * 372/Clock Frequency) = 11ETU + ( 2* 9 * 960* 372/4000000) = 11+1.607040 = 12ETU = 0.00614sec = 6msec

//WWT = 960 * WI * F / Clock Frequency
// Character Level
//The "waiting time" (see 7.2) shall be: WT =WI x960x Fi/f = 255 * 960 * 2048/4000000 = 125ETU = 0.064sec = 64msec

#define        INITWAITTIME            64    // 64msec worst case assuming T0

#pragma pack(push, 1)

typedef struct _CCID_DEV_INFO CCID_DEV_INFO;

struct _CCID_DEV_INFO {
    VOID        *CcidDescriptor;      // Ptr to CCID descriptor
    UINT32      *DataRates;           // List of DataRates supported by CCID  
    UINT32      *ClockFrequencies;    // List of Frequencies suported by CCID
    LIST_ENTRY  IccDeviceList;        // Linked list of ICC devices. :Linked to "ICCDeviceLink"
};

struct    _ATR_DATA {
    UINT8        TS;                 
    UINT8        T0;                 
    BOOLEAN      TA1Present;             
    UINT8        TA1;
    BOOLEAN      TB1Present;
    UINT8        TB1;
    BOOLEAN      TC1Present;
    UINT8        TC1;
    BOOLEAN      TD1Present;
    UINT8        TD1;

    BOOLEAN      TA2Present;
    UINT8        TA2;
    BOOLEAN      TB2Present;
    UINT8        TB2;
    BOOLEAN      TC2Present;
    UINT8        TC2;
    BOOLEAN      TD2Present;
    UINT8        TD2;

    BOOLEAN      TD15Present;
    UINT8        TD15;
    BOOLEAN      TA15Present;
    UINT8        TA15;

    UINT8        NumberofHystoricalBytes;    

};

#define ICC_DEVICE_SIG       SIGNATURE_32('I','C','C','D') 

struct _ICC_DEVICE {
    LIST_ENTRY      Link;                   // Linked to ICCDeviceList
    UINT32          Signature;
    EFI_HANDLE      ChildHandle;
    EFI_HANDLE      SCardChildHandle;
    UINT8           Slot;                   // slot number
    UINT8           SlotConnectStatus;
    UINT8           RawATRData[32];
    ATR_DATA        AtrData;                // Processed ATR data
    UINT8           TransmissionProtocolSupported; // BitMap
    UINT8           NumofTransmissionProtocolSupported; // Count 1 based
    UINT8           Current;
    UINT8           Status;            // Holds the status of the last cmd
    UINT8           Error;             // Holds the Slot error value of the last cmd
    UINT8           ConfiguredStatus;   // See the bit defenitions above ICCPresent etc

    UINT16          ETU;                // 1etu = F/D * 1/f  (Elementary time unit) This will hold the timing in Micro sec
    UINT16          GlobalFi;           // Clock Rate Conversion Integer
    UINT8           GlobalDi;           // Baude rate Adjustment
    UINT8           GlobalFmax;         // Max Frequency
    UINT8           TransmissionProtocol; // Higher nibble what is supported, Lower nibble what is selected

    UINT8           ExtraGuardTime;     // N = TC1 
    UINT8           BWI;                // From TB of T=1
    UINT8           CWI;                // From TB of T=1
    UINT8           BWT;                // Max. Block width time
    UINT8           IFSC;               // Default Information Filed Size (IFSC)
    UINT8           IFSD;               //
    UINT8           NAD;                 

    UINT8           EpilogueFields;     // First TC for T=1

    BOOLEAN         SpecificMode;        // BIT7 set in TA2

    UINT8           ClassABC;           // Updated from T15->TA
    UINT8           StopClockSupport;   // Updated from T15->TA 00: Not supported, 1 : State L, 2 : State H, 3 : No preference
    
    UINT8           ClockStatus;       // PlaceHolder for Clockstatus from the last RDR_to_PC_SlotStatus cmd
    UINT8           ChainParameter;    // PlaceHolder for ChainParameter from the last RDR_to_PC_DataBlock

    // This structure should be same as RDR_TO_PC_PARAMETERS_T1_STRUC. Don't add or remove the next 8 bytes
    UINT8           ProtocolNum;        // PlaceHolder for bProtocolNum from RDR_to_PC_Parameters
    UINT8           FindIndex;
    UINT8           TCCKST;
    UINT8           GuardTime;
    UINT8           WaitingInteger;
    UINT8           ClockStop;
    UINT8           IFSC1;
    UINT8           NadValue;
    //End

    // From GetDataRateAndClockFrequency
    UINT32          ClockFrequency;
    UINT32          DataRate;

    UINT32          WTwaittime;          // (in ETU units) Based on T0 BWT/WWT time will be updated once ATR data is available 
    UINT32          WaitTime;            // Final Wait time used in msec

    // Information stored for TDPU transmission
    UINT8           NaSInterface;        // This holds the last N(S) value transmitted.
    UINT8           NaSCard;             // This holds the last N(S) received from card
    UINT8           RBlockCounter;
    UINT8           IFSD1;              // Max. size of the information field of blocks that can be received by the interface device.
    BOOLEAN         Chaining;           // Indicates M bit is set or not

    BOOLEAN         T1CharCmdDataPhase; // TRUE for Cmd Phase/False for Data Phase

    //LIST_ENTRY      ICCDeviceLink;       // Linked to ICCDeviceList
    DEV_INFO        *DevInfo;
    
};

struct _SMARTCLASS_DESC{
    UINT8           DescLength;
    UINT8           DescType;
    UINT16          BcdCCID;
    UINT8           MaxSlotIndex;
    UINT8           VoltageSupport;
    UINT32          Protocols;
    UINT32          DefaultClock;
    UINT32          MaximumClock;
    UINT8           NumClockSupported;
    UINT32          DataRate;
    UINT32          MaxDataRate;
    UINT8           NumDataRatesSupported;
    UINT32          MaxIFSD;
    UINT32          SynchProtocols;
    UINT32          Mechanical;
    UINT32          Features;
    UINT32          MaxCCIDMessageLength;
    UINT8           ClassGetResponse;
    UINT8           ClassEnvelope;
    UINT16          LcdLayout;
    UINT8           PINSupport;
    UINT8           MaxCCIDBusySlots;
};

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           PowerSlot;
    UINT16          RFU;
} PC_TO_RDR_ICCPOWERON_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_ICCPOWEROFF_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_GETSLOT_STATUS_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           BWI;
    UINT16          LevelParameter;
} PC_TO_RDR_XFRBLOCK_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_GETPARAMETERS_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_RESETPARAMETERS_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           ProtocolNum;
    UINT8           RFU[2];
    UINT8           FindDindex;
    UINT8           TCCKST0;
    UINT8           GuardTimeT0;
    UINT8           WaitingIntergerT0;
    UINT8           ClockStop;
} PC_TO_RDR_SETPARAMETERS_T0_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           ProtocolNum;
    UINT8           RFU[2];
    UINT8           FindDindex;
    UINT8           TCCKST1;
    UINT8           GuardTimeT1;
    UINT8           WaitingIntergersT1;
    UINT8           ClockStop;
    UINT8           IFSC;
    UINT8           NadValue;
} PC_TO_RDR_SETPARAMETERS_T1_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_ESCAPE_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           ClockCommand;
    UINT8           RFU[2];
} PC_TO_RDR_ICCCLOCK_STRUC;

typedef struct {
    UINT8            MessageType;
    UINT32           Length;
    UINT8            Slot;
    UINT8            Seq;
    UINT8            Changes;
    UINT8            ClassGetResponse;
    UINT8            ClassEnvelope;
} PC_TO_RDR_T0APDU_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           BWI;
    UINT16          LevelParameter;
} PC_TO_RDR_SECURE_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Function;
    UINT8           RFU[2];
} PC_TO_RDR_MECHANICAL_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
} PC_TO_RDR_ABORT_STRUC;


typedef struct {
    UINT8           MessageType;
    UINT32          Length;
    UINT8           Slot;
    UINT8           Seq;
    UINT8           RFU[3];
    UINT32          CloclFrequency;
    UINT32          DataRate;
} PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;        // Size of abData
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Status;
    UINT8           Error;    
    UINT8           Data;            // Usage depends on diffeent Message type
} RDR_HEADER;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;        // Size of abData
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Status;
    UINT8           Error;
    UINT8           ChainParameter;
} RDR_TO_PC_DATABLOCK_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;        
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Status;
    UINT8           Error;
    UINT8           ClockStatus;
} RDR_TO_PC_SLOTSTATUS_STRUC;

typedef struct {
    UINT8           FindDindex;
    UINT8           TCCKST0;
    UINT8           GuardTimeT0;
    UINT8           WaitingIntergerT0;
    UINT8           ClockStop;
} PROTOCOL_DATA_T0;

typedef struct {
    UINT8           FindDindex;
    UINT8           TCCKST1;
    UINT8           GuardTimeT1;
    UINT8           WaitingIntergersT1;
    UINT8           ClockStop;
    UINT8           IFSC;
    UINT8           NadValue;
} PROTOCOL_DATA_T1;

typedef struct {
    RDR_HEADER          Header;
    PROTOCOL_DATA_T0    ProtocolData;
} RDR_TO_PC_PARAMETERS_T0_STRUC;

typedef struct {
    RDR_HEADER          Header;
    PROTOCOL_DATA_T1    ProtocolData;
} RDR_TO_PC_PARAMETERS_T1_STRUC;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;        // Size of abData
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Status;
    UINT8           Error;
    UINT8           RFU;
} RDR_TO_PC_ESCAPE_STATUS;

typedef struct {
    UINT8           MessageType;
    UINT32          Length;        // Should be 8
    UINT8           Slot;
    UINT8           Seq;
    UINT8           Status;
    UINT8           Error;
    UINT8           RFU;
    UINT32          ClockFrequency;
    UINT32          DataRate;
} RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC;

typedef struct _USB_GLOBAL_DATA USB_GLOBAL_DATA;
struct _USB_GLOBAL_DATA{
    UINT32          UsbFeature;
    UINT32          UsbDevSupport;
    UINT8           MaxDevCount;
    UINT8           CcidSequence;
    UINT8           UseT0T1Protocol;
};

struct _DEV_INFO {
    EFI_USB_IO_PROTOCOL     *UsbIo;
    CCID_DEV_INFO           CcidDevData;
    SMARTCLASS_DESC         CcidDesc;
    EFI_HANDLE              Handle;
    UINT32                  CcidDataRates[MAX_CCID_DATA_RATES];
    UINT32                  ClockFrequencies[MAX_CLOCK_FREQUENCIES];
    ICC_DEVICE              IccDevice[MAX_ICC_DEVICE];
    UINT8                   StrProduct;
    UINT8                   BulkInEndpoint;
    UINT8                   BulkOutEndpoint;
    UINT16                  BulkInMaxPkt;
    UINT16                  BulkOutMaxPkt;
    UINT16                  IntInMaxPkt;
    UINT8                   IntInEndpoint;
    UINT8                   PollInterval;
    UINT16                  PollingLength;
};

typedef struct _QUEUE_T QUEUE_T;
struct _QUEUE_T{
    VOID* volatile* Data;
    UINTN Maxsize;
    volatile UINTN Head;
    volatile UINTN Tail;
};

typedef struct _USB_DATA_LIST USB_DATA_LIST;
struct _USB_DATA_LIST{
    DEV_INFO        DevInfoTable[MAX_CCID_DEV_INFO];
    DEV_INFO        *QueueData[MAX_CCID_NOTIFICATIONS_COUNT];
    QUEUE_T         ICCQueueCnnctDisc;
    DEV_INFO*       ICCQueueData[6];

};

/**
    This is a union data type of all the API related data

**/

typedef union {
    //    CCID APIs
    CCID_GETSMARTCLASSDESCRIPTOR   CcidSmartClassDescriptor;
    CCID_ATR                       CcidAtr;
    CCID_POWERUP_SLOT              CcidPowerupSlot;
    CCID_POWERDOWN_SLOT            CcidPowerdownSlot;
    CCID_GETSLOT_STATUS            CcidGetSlotStatus;
    CCID_XFRBLOCK                  CcidXfrBlock;
    CCID_GET_PARAMS                CcidGetParameters;

    // SMART CARD READER PROTOCOL APIs
    SMART_CARD_READER_CONNECT      SmartCardReaderConnect;
    SMART_CARD_READER_DISCONNECT   SmartCardReaderDisconnect;
    SMART_CARD_READER_STATUS       SmartCardReaderStatus;
    SMART_CARD_READER_TRANSMIT     SmartCardReaderTransmit;
    SMART_CARD_READER_CONTROL      SmartCardReaderControl;
    SMART_CARD_READER_GETATTRIB    SmartCardReaderGetAttrib;
} U_API_DATA;

typedef struct _URP_STRUC URP_STRUC;
struct _URP_STRUC {
    UINT8       FuncNumber;
    UINT8       SubFunc;
    UINT8       RetValue;
    U_API_DATA  ApiData;
};

#pragma pack(pop)

typedef VOID (EFIAPI *API_FUNC)(URP_STRUC*);
VOID
EFIAPI
UsbCcidInitialize(
    VOID
);

UINT8
EFIAPI
UsbCcidCheckForDevice (
    DEV_INFO    *FpDevInfo,
    UINT8       BaseClass,
    UINT8       SubClass,
    UINT8       Protocol
);

UINT8
EFIAPI
UsbCcidDisconnectDevice (
    DEV_INFO    *FpDevInfo
);

DEV_INFO*
EFIAPI
UsbCcidConfigureDevice (
    DEV_INFO        *FpDevInfo,
    UINT8           *FpDesc,
    UINT16          StartOffset,
    UINT16          EndOffset
);

UINT32
UsbCcidIssueBulkTransfer (
    DEV_INFO*   FpDevInfo, 
    UINT8       XferDir,
    UINT8*      CmdBuffer, 
    UINT32      Size
);

UINT32
UsbCcidIssueControlTransfer(
    DEV_INFO*   FpDevInfo,     
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *FpBuffer,
    UINT16      Length
);

EFI_STATUS
PCToRDRXfrBlock (
    IN DEV_INFO             *FpDevInfo,
    IN ICC_DEVICE           *FpICCDevice,
    IN UINT32               CmdLength,
    IN UINT8                *CmdBuffer,
    IN UINT8                BlockWaitingTime,
    IN UINT16               LevelParameter    

);

EFI_STATUS
ConstructBlockFrame(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice,
    IN UINT8            Nad,
    IN UINT8            PCB,
    IN UINT32           InfLength,
    IN UINT8            *InfBuffer,
    OUT UINT8           *LevelParameter,
    OUT UINT32          *BlockFrameLength,
    OUT UINT8           **BlockFrame
);

UINT8   
HandleReceivedBlock (
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice,
    IN UINT32           OriginalBlockFrameLength,
    IN UINT8            *OriginalBlockFrame,
    IN UINT32           SentBlockFrameLength,
    IN UINT8            *SentBlockFrame,
    IN UINT8            *ReceivedBlockFrame
);

EFI_STATUS
TxRxT1TDPUChar (
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    IN UINT8            ISBlock,
    OUT UINT32          *ResponseLength,
    OUT UINT8           *ResponseBuffer
);

EFI_STATUS
TxRxT1Adpu (
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    OUT UINT32          *ResponseLength,
    OUT UINT8           *ResponseBuffer
);

EFI_STATUS
PCToRDRGetSlotStatus(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice
);

EFI_STATUS
RDRToPCSlotStatus(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice
);

EFI_STATUS
PCToRDRGetParameters(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice
);

EFI_STATUS
RDRToPCParameters(
    IN DEV_INFO           *FpDevInfo,
    IN ICC_DEVICE        *FpICCDevice
);

EFI_STATUS
RDRToPCDataBlock(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice,
    IN OUT UINT32       *Length,
    OUT UINT8           *Buffer

);

EFI_STATUS
ICCInsertEvent(
    DEV_INFO    *FpDevInfo,
    UINT8       Slot
);

EFI_STATUS
ICCRemovalEvent(
    IN DEV_INFO    *FpDevInfo,
    IN UINT8        Slot
);

VOID
IccQueuePut(
    VOID * IccDev
);

VOID 
PrintPCParameters(
    IN UINT8   *Data
);

TRANSMISSION_PROTOCOL GetDefaultProtocol (
    IN ICC_DEVICE        *FpICCDevice
);

VOID
CalculateLRCChecksum (
    IN UINT8       *BlockFrame, 
    IN UINT32      BlockFrameLength
);

EFI_STATUS
PCtoRDRIccPowerOff(
    IN DEV_INFO         *FpDevInfo,
    IN ICC_DEVICE       *FpICCDevice
);

VOID
PrintDescriptorInformation (
    SMARTCLASS_DESC *FpCCIDDesc
);

VOID
EFIAPI
UsbCcidSmartClassDescriptor (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbCcidAtr (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbCcidPowerupSlot (
    IN OUT URP_STRUC *Urp

);

VOID
EFIAPI
UsbCcidPowerDownSlot (
    IN OUT URP_STRUC *Urp

);

VOID
EFIAPI
UsbCcidGetSlotStatus (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbCcidXfrBlock (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbCcidGetParameters (
    IN OUT URP_STRUC *Urp

);

EFI_STATUS
ConfigureCcid(
    DEV_INFO          *FpDevInfo,
    ICC_DEVICE        *FpICCDevice
);

VOID
EFIAPI
UsbSCardReaderConnect (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbSCardReaderDisConnect (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbSCardReaderStatus (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbSCardReaderTransmit (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbSCardReaderControl (
    IN OUT URP_STRUC *Urp
);

VOID
EFIAPI
UsbSCardReaderGetAttrib (
    IN OUT URP_STRUC *Urp
);

ICC_DEVICE*
GetIccDevice(
    DEV_INFO        *DevInfo, 
    UINT8            Slot
);

VOID
PrintTimingInfo(
    ICC_DEVICE    *FpICCDevice
);

VOID
PrintATRData(
    UINT8            *ATRData
);

UINT8
FindNumberOfTs(
    UINT8    Data
);

VOID EFIAPI UsbApiCcidRequest(URP_STRUC*);                       // API 34h  Stop this API support

extern EFI_COMPONENT_NAME_PROTOCOL  gUsbCcidComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL  gUsbCcidComponentName2;
#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
