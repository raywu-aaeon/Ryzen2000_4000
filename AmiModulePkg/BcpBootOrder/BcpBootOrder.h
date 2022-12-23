//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016 American Megatrends Inc.           **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway Suite 200 Norcross GA 30093           **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file BcpBootOrder.h

    This file contains GUIDs, Constants, and Data structures that are 
    used to define and reconstruct a boot order defined by either the 
    build process of by the BCP Utility before flashing.
**/

#ifndef __BcpBootOrder__H__
#define __BcpBootOrder__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Efi.h>
#include <Token.h>

/// GUID of the section that is created by this module to contains the BCP Boot Order
#define BCP_BOOT_ORDER_SECTION_GUID \
    { 0x962BA95F, 0x4704, 0x478e, 0x8E, 0x03, 0x47, 0x09, 0x51, 0xF0, 0xF9, 0x9A }

/// The GUID used to define the correct file within the Section
#define BCP_BOOT_ORDER_FILE_GUID \
    { 0x12bfca88, 0x7a2f, 0x4ab5, 0x9a, 0x5d, 0xc4, 0x0c, 0xa6, 0x8b, 0xf7, 0x5f }

// List of defined device types for use with BCP
#define BCP_FDD0                    0   ///< BCP Type Floppy Disk 0
#define BCP_FDD1                    1   ///< BCP Type Floppy Disk 1
#define BCP_USB_FDD                 2   ///< BCP Type USB Floppy Disk
#define BCP_PM_CD                   16  ///< BCP Type Primary Master CD
#define BCP_PS_CD                   17  ///< BCP Type Primary Slave CD
#define BCP_SM_CD                   18  ///< BCP Type Secondary Master CD
#define BCP_SS_CD                   19  ///< BCP Type Secondary Slave CD
#define BCP_SATA0_CD                20  ///< BCP Type Sata CD 0
#define BCP_SATA1_CD                21  ///< BCP Type Sata CD 1
#define BCP_SATA2_CD                22  ///< BCP Type Sata CD 2
#define BCP_SATA3_CD                23  ///< BCP Type Sata CD 3
#define BCP_SATA4_CD                24  ///< BCP Type Sata CD 4
#define BCP_SATA5_CD                25  ///< BCP Type Sata CD 5
#define BCP_SATA6_CD                26  ///< BCP Type Sata CD 6
#define BCP_SATA7_CD                27  ///< BCP Type Sata CD 7
#define BCP_USB_CD                  28  ///< BCP Type USB CD
#define BCP_PM_HDD                  32  ///< BCP Type Primary Master Hard Drive
#define BCP_PS_HDD                  33  ///< BCP Type Primary Slave Hard Drive
#define BCP_SM_HDD                  34  ///< BCP Type Secondary Master Hard Drive
#define BCP_SS_HDD                  35  ///< BCP Type Secondary Slave Hard Drive
#define BCP_SATA0_HDD               36  ///< BCP Type Sata Hard Drive 0
#define BCP_SATA1_HDD               37  ///< BCP Type Sata Hard Drive 1
#define BCP_SATA2_HDD               38  ///< BCP Type Sata Hard Drive 2
#define BCP_SATA3_HDD               39  ///< BCP Type Sata Hard Drive 3
#define BCP_SATA4_HDD               40  ///< BCP Type Sata Hard Drive 4
#define BCP_SATA5_HDD               41  ///< BCP Type Sata Hard Drive 5
#define BCP_SATA6_HDD               42  ///< BCP Type Sata Hard Drive 6
#define BCP_SATA7_HDD               43  ///< BCP Type Sata Hard Drive 7
#define BCP_USB_HDD                 44  ///< BCP Type USB Hard Drive 0
#define BCP_NVME_HDD				45  ///< BCP Type NVME Hard Drive 0
#define BCP_EMBEDDED_NETWORK        48  ///< BCP Type Embedded Network
#define BCP_BEV                     56  ///< BCP Type Boot Entry Vector

#define BCP_UEFI_OTHER              0x40 ///< 64 BCP Type Non Specified Device
#define BCP_UEFI_USB                0x41 ///< 65 BCP Type USB Grouping
#define BCP_UEFI_HDD                0x42 ///< 66 BCP Type Hard Drive
#define BCP_UEFI_CD                 0x43 ///< 67 BCP Type CD/DVD drives
#define BCP_UEFI_NETWORK            0x44 ///< 68 BCP Type Network Devices
#define BCP_UEFI_FDD                0x45 ///< 69 BCP Type USB Floppy
#define BCP_UEFI_EMBEDDED_SHELL     0x46 ///< 70 BCP Type Embedded Shell


#define BCP_UNDEFINED               0xFF ///< BCP Undefined Type

// The following code is designed to support USB device grouping.  definitions and logic come from UsbInt13.c
#if defined (BBS_USB_DEVICE_TYPE_SUPPORT) && (BBS_USB_DEVICE_TYPE_SUPPORT == 1)
#define USB_FLOPPY_BBS_TYPE 		BBS_USB
#define USB_HDD_BBS_TYPE 			BBS_USB
#define USB_CDROM_BBS_TYPE 			BBS_USB
#else
#define USB_FLOPPY_BBS_TYPE 		BBS_FLOPPY
#define USB_HDD_BBS_TYPE 			BBS_HARDDISK
#define USB_CDROM_BBS_TYPE 			BBS_CDROM
#endif


/** Array of device types with their corresponding information 
	This array is used to help identify devices as they are prioritized 
	into the Boot Order
*/
//  ======================================================================
//   BCP Type (TokenNumber)   BBS Type             MSG_DP SubType  Order 
#define BCP_DEVICE_INFO_ARRAY \
   {{BCP_FDD0,                BBS_FLOPPY,          BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_FDD1,                BBS_FLOPPY,          BCP_UNDEFINED,  BCP_UNDEFINED},\
	{BCP_USB_FDD,             USB_FLOPPY_BBS_TYPE, MSG_USB_DP,     BCP_UNDEFINED},\
	{BCP_PM_CD,               BBS_CDROM,           MSG_ATAPI_DP,   0},\
    {BCP_PS_CD,               BBS_CDROM,           MSG_ATAPI_DP,   1},\
    {BCP_SM_CD,               BBS_CDROM,           MSG_ATAPI_DP,   2},\
    {BCP_SS_CD,               BBS_CDROM,           MSG_ATAPI_DP,   3},\
    {BCP_SATA0_CD,            BBS_CDROM,           MSG_SATA_DP,    0},\
    {BCP_SATA1_CD,            BBS_CDROM,           MSG_SATA_DP,    1},\
    {BCP_SATA2_CD,            BBS_CDROM,           MSG_SATA_DP,    2},\
    {BCP_SATA3_CD,            BBS_CDROM,           MSG_SATA_DP,    3},\
    {BCP_SATA4_CD,            BBS_CDROM,           MSG_SATA_DP,    4},\
    {BCP_SATA5_CD,            BBS_CDROM,           MSG_SATA_DP,    5},\
    {BCP_SATA6_CD,            BBS_CDROM,           MSG_SATA_DP,    6},\
    {BCP_SATA7_CD,            BBS_CDROM,           MSG_SATA_DP,    7},\
	{BCP_USB_CD,              USB_CDROM_BBS_TYPE,  MSG_USB_DP,     BCP_UNDEFINED},\
    {BCP_PM_HDD,              BBS_HARDDISK,        MSG_ATAPI_DP,   0},\
    {BCP_PS_HDD,              BBS_HARDDISK,        MSG_ATAPI_DP,   1},\
    {BCP_SM_HDD,              BBS_HARDDISK,        MSG_ATAPI_DP,   2},\
    {BCP_SS_HDD,              BBS_HARDDISK,        MSG_ATAPI_DP,   3},\
    {BCP_SATA0_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    0},\
    {BCP_SATA1_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    1},\
    {BCP_SATA2_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    2},\
    {BCP_SATA3_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    3},\
    {BCP_SATA4_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    4},\
    {BCP_SATA5_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    5},\
    {BCP_SATA6_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    6},\
    {BCP_SATA7_HDD,           BBS_HARDDISK,        MSG_SATA_DP,    7},\
	{BCP_USB_HDD,             USB_HDD_BBS_TYPE,    MSG_USB_DP,     BCP_UNDEFINED},\
	{BCP_NVME_HDD,            BBS_HARDDISK,        MSG_NVME_NAMESPACE_DP,    BCP_UNDEFINED},\
    {BCP_EMBEDDED_NETWORK,    BBS_EMBED_NETWORK,   BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_BEV,                 BBS_BEV_DEVICE,      BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_OTHER,          BCP_UNDEFINED,       BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_USB,            BCP_UEFI_USB,        BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_HDD,            BCP_UEFI_HDD,        BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_CD,             BCP_UEFI_CD,         BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_NETWORK,        BCP_UEFI_NETWORK,    BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_FDD,            BCP_UEFI_FDD,        BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UEFI_EMBEDDED_SHELL, BCP_UNDEFINED,       BCP_UNDEFINED,  BCP_UNDEFINED},\
    {BCP_UNDEFINED,           BCP_UNDEFINED,       BCP_UNDEFINED,  BCP_UNDEFINED}}

            
/**
   Data Structure that defines that entries in the BCP_DEVICE_INFO_ARRAY
 */
typedef struct {
    UINT8  TokenNumber;  ///< Index of the boot order option 
    UINT16 BbsType;	 ///< BBS Type of the device 
    UINT8  MsgDpSubType; ///< Messaging Device Path Sub type that defines the device in more detail.  Used for legacy Only
    UINT8  BusOrder;	 ///< unique value input that identifies the device.  Used for legacy Only
} BCP_BOOT_ORDER_ITEM_INFO;

#pragma pack(1)

/**
 Data Structure that defines the File Section
 */
typedef struct { 
    EFI_GUID Guid; ///< GUID of the Section that contains the BCP Boot Order
    UINT16   NumberOfOptions; ///< Number of options in the boot order
    UINT16   Option[1]; ///< list of boot options
} BCP_BOOT_ORDER_SECTION;


typedef struct {
    UINT16 Length; 
    UINT16 Order[]; 
} BCP_BOOT_ORDER_STRUC;

#if (BCP_ENABLE_CUSTOM_GROUPING_SUPPORT == 1)
/**
 This structure defines the make up of a custom group entry that will be recognized by AMI BCP
 
 */
typedef struct _STRING_ENTRY{
    UINT16    Token; ///< token that is associated with the string
    UINT16    BBSGroup; ///< Device type definitions - For new groups this can be any unused value
    CHAR16    String[BCP_GROUPING_MAX_STRING_LENGTH]; ///< String to be displayed for this entry
}STRING_ENTRY;

/**
 This structure defines the whole list of String entries
 */
typedef struct _STRING_BLOCK
{
    UINT16        NoOfStrings; ///< number of string entries in this structure
    STRING_ENTRY  StringDefs[BCP_NUM_NEW_STRINGS]; ///< Array of STRING_ENTRIES
} STRING_BLOCK;

/**
	Structure created to concatenate the two types structure above so that the 
	resulting Section does not have any extra bytes between entries
*/
typedef struct {
    BCP_BOOT_ORDER_STRUC   BcpBootOrder; ///< BCP_BOOT_ORDER_STRUC
    STRING_BLOCK            StringBlock; ///< STRING_BLOCK
} BCP_BOOT_ORDER_PACKAGE;
#endif //(BCP_ENABLE_CUSTOM_GROUPING_SUPPORT == 1)

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016 American Megatrends Inc.           **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway Suite 200 Norcross GA 30093           **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
