//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file BcpBootOrder.c
    The file contains code that will generate and implement the default 
    boot order according to the BCP boot order variable.

**/
//----------------------------------------------------------------------------


#include <BootOptions.h>
#include <Protocol/DevicePath.h>
#include "BcpBootOrder.h"
#include <Protocol/LegacyBios.h>
#include <BcpBootOrderElinks.h>
#include <Protocol/AmiUsbController.h>

typedef UINT8 (BCP_BOOT_OPTIONS_FUNCTION)(EFI_DEVICE_PATH_PROTOCOL *DevicePath);

BCP_BOOT_OPTIONS_FUNCTION* BcpBootOptionFunctions[]=
    { BCP_BOOT_GROUP_DETECTION NULL };

struct {
    VENDOR_DEVICE_PATH media;
    EFI_DEVICE_PATH_PROTOCOL end;
} BcpShellDp = {
    {
        {
            MEDIA_DEVICE_PATH, MEDIA_VENDOR_DP,
            sizeof(VENDOR_DEVICE_PATH)
        },
        AMI_MEDIA_DEVICE_PATH_GUID
    },
    {
        END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
        sizeof(EFI_DEVICE_PATH_PROTOCOL)
    }
};


//----------------------------------------------------------------------------
/// global variable with scope of this file that tracks whether the current boot is the first boot of the BIOS or if system has booted before
/// This is determined on every boot.
static BOOLEAN IsFirstBoot = FALSE;


/**
    This function locates, by GUID, the resource binary that contains the BCP default boot order

        
    @param ResourceGuid pointer to resource GUID
    @param ResourceSectionGuid pointer to resource section GUID
    @param Address pointer to returning address of the resource

    @retval EFI_SUCCESS - resource section found and read into memory
    @retval EFI_NOT_FOUND - no firmware volume protocol was found,
    @retval EFI_UNSUPPORTED - The current handle does not support the specified protocol
    @retval EFI_WARN_BUFFER_TOO_SMALL - The caller-allocated buffer is too small to contain the requested output. The buffer is filled and the output is truncated.
    @retval EFI_OUT_OF_RESOURCES - An allocation failure occurred.
    @retval EFI_NOT_FOUND - The requested file was not found in the firmware volume.
    @retval EFI_NOT_FOUND - The requested section was not found in the specified file.
    @retval EFI_DEVICE_ERROR - A hardware error occurred when attempting to access the firmware volume.
    @retval EFI_ACCESS_DENIED - The firmware volume is configured to disallow reads.
    @retval EFI_PROTOCOL_ERROR - The requested section was not found, but the file could not be fully parsed because a required EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL was not found. It is possible the requested section exists within the file and could be successfully extracted once the required EFI_GUIDED_SECTION_EXTRACTION_PROTOCOL is published.    
**/

static EFI_STATUS LocateSectionResource(
    IN  EFI_GUID *ResourceFileGuid,
    IN  EFI_GUID *ResourceSectionGuid,
    OUT UINT8 **Address )
{
    EFI_STATUS Status;
    EFI_GUID EfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *FwVolumeProtocol = NULL;
    EFI_HANDLE *HandleBuffer = NULL;
    UINTN  NumberOfHandles;
    UINTN  Index;
    UINT32 Authentication;
    UINTN  i;
    EFI_GUID *SectionGuid = NULL;
    UINTN  SectionSize;

    // Locate the Firmware volume protocol
    Status = pBS->LocateHandleBuffer(
        ByProtocol,
        &EfiFirmwareVolumeProtocolGuid,
        NULL,
        &NumberOfHandles,
        &HandleBuffer
    );
    if (EFI_ERROR(Status)) 
        return EFI_NOT_FOUND;
    
    // Find and read raw data
    for (Index = 0; Index < NumberOfHandles; Index++) {

        Status = pBS->HandleProtocol(
            HandleBuffer[Index],
            &EfiFirmwareVolumeProtocolGuid,
            (VOID **)&FwVolumeProtocol
        );
        if (EFI_ERROR(Status)) 
            continue;
        
        i = 0;
        while(1) {
            SectionSize = 0;
            Status = FwVolumeProtocol->ReadSection(
                FwVolumeProtocol,
                ResourceFileGuid,
                EFI_SECTION_FREEFORM_SUBTYPE_GUID,
                i++,
                (VOID **)&SectionGuid,
                &SectionSize,
                &Authentication
            );
            if (EFI_ERROR(Status))
                break;
            else if ( !guidcmp(SectionGuid, ResourceSectionGuid) ) {
                *Address = (UINT8*)SectionGuid;
                goto LocateSectionResource_exit;
            }
            pBS->FreePool(SectionGuid);
            SectionGuid = NULL;
        } 
    }
    
LocateSectionResource_exit:
    pBS->FreePool(HandleBuffer);
    return Status;
}


/**
    This function looks for specified device path type within the device path.

    @param Dp   pointer to device path
    @param Type requested device path type to search for

    @retval NULL - Device Path not found
    @retval pointer to the EFI_DEVICE_PATH_PROTOCOL node that was found.
**/

static EFI_DEVICE_PATH_PROTOCOL* GetDevicePathNodeOfType( EFI_DEVICE_PATH_PROTOCOL *Dp, UINT8 Type )
{
    if (Dp == NULL) 
        return NULL;

    for( ; !(isEndNode(Dp)); Dp = NEXT_NODE(Dp) )
        if (Dp->Type == Type) 
            return Dp;
    return NULL;
}


/**
 * Determine if the passed BOOT_OPTION is the built in EFI Shell
 * 
 * @param Option the boot option in question
 * 
 * @retval BOOLEAN TRUE - this boot option represent the built in EFI Shell
 * @retval FALSE this is not the built in EFI Shell
 */
BOOLEAN IsEmbeddedShell(BOOT_OPTION *Option){
    EFI_DEVICE_PATH_PROTOCOL *Dp = Option->FilePathList;

    if (Dp==NULL) return FALSE;
    if (   NODE_LENGTH(Dp)==NODE_LENGTH(&BcpShellDp.media.Header)
        && MemCmp(Dp,&BcpShellDp.media.Header,NODE_LENGTH(Dp))==0 ) 
        {
            return TRUE;
        }

    return FALSE;
}


/**
 * Search for, and return, a pointer to the specific device path node of type/subtype.
 *
 * @param DevicePath Device Path to search
 * @param Type Device path type to find
 * @param SubType Device path subtype to find
 *
 * @return EFI_DEVICE_PATH_PROTOCOL Pointer to the desired device path node
 * @retval NULL No device path nodes were found
 */
static EFI_DEVICE_PATH_PROTOCOL* 
FindDeviceNodeInDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN UINT8 Type,
  IN UINT8 SubType)
{
    while(DevicePath != NULL && !isEndNode(DevicePath))
    {
        if(DevicePath->Type == Type && DevicePath->SubType == SubType)
            return DevicePath;
        DevicePath = NEXT_NODE(DevicePath);
    }
    return NULL;
} 

/**
    This function checks to see if one of the three USB Messaging Device Paths
    SubTypes exists in the Device Path for DevicePath
    
    @param DevicePath  pointer to a Device Path
    
    @return UINT8
    @retval BCP_UEFI_USB - BCP value that represents the UEFI Group for USB
    @retval 0 - not a USB device
*/
UINT8 MatchUefiUsbBootGroup(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    // if any of the three USB Messaging device paths are found then it is a 
    // USB device and this function should return TRUE
    if ( (FindDeviceNodeInDevicePath(DevicePath, MESSAGING_DEVICE_PATH, MSG_USB_DP) != NULL) || 
                (FindDeviceNodeInDevicePath(DevicePath, MESSAGING_DEVICE_PATH, MSG_USB_CLASS_DP) != NULL) ||
                (FindDeviceNodeInDevicePath(DevicePath, MESSAGING_DEVICE_PATH, MSG_USB_WWID_DP) != NULL) )
    {
        return BCP_UEFI_USB;
    }
    // if none of the USB messaging subTypes are found return FALSE
    return 0;
}

/**
    This function checks to see if the Media Hard Drive Device Path
    SubType exists in the Device Path for DevicePath
    
    @param DevicePath  pointer to a Device Path
    
    @return UINT8
    @retval BCP_UEFI_HDD - BCP value that represents the UEFI Group for HDD
    @retval 0
*/
UINT8 MatchUefiHddBootGroup(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    if (FindDeviceNodeInDevicePath(DevicePath, MEDIA_DEVICE_PATH, MEDIA_HARDDRIVE_DP) != NULL)
    {
#if UEFI_USB_DEVICE_TYPE_SUPPORT
        if (MatchUefiUsbBootGroup(DevicePath)) // Exclude the device of type UEFI USB-HDD, it should be classified as BCP_UEFI_USB.
        {
            return 0;
        }
#endif

        return BCP_UEFI_HDD;
    }
    return 0;
}

/**
    This function checks to see if the Media CD-ROM Device Path
    SubType exists in the Device Path for DevicePath
    
    @param DevicePath  pointer to a Device Path
    
    @return UINT8
    @retval BCP_UEFI_CD - BCP value that represents the UEFI Group for CD
    @retval 0
*/
UINT8 MatchUefiCdBootGroup(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    if (FindDeviceNodeInDevicePath(DevicePath, MEDIA_DEVICE_PATH, MEDIA_CDROM_DP) != NULL)
    {
        return BCP_UEFI_CD;
    }
    return 0;
}

/**
    This function checks to see if the Device is a Network Device
    
    This function uses the Messaging MAC Device Path to determine if 
    the device is a Network Device
    
    @param DevicePath  pointer to a Device Path
    
    @return UINT8
    @retval BCP_UEFI_NETWORK - BCP value that represents the UEFI Group for 
    @retval 0
*/
UINT8 MatchUefiNetworkBootGroup(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    // this uses the MAC address device path subtype to determine if it 
    // is a network device.
    if (FindDeviceNodeInDevicePath(DevicePath, MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP) != NULL)
    {
        return BCP_UEFI_NETWORK;
    }
    return 0;
}

/**
    Checks if the device is a USB Floppy
    
    This function checks to see if the device is a USB device then
    checks to make sure that it isn't a Hard Drive or CD-ROM.  If 
    it makes it past those, then it is a Floppy drive by elimination
    
    @param DevicePath  pointer to a Device Path
    
    @return UINT8
    @retval BCP_UEFI_FDD - BCP value that represents the UEFI Group for 
    @retval 0
*/
UINT8 MatchUefiFloppyBootGroup(EFI_DEVICE_PATH_PROTOCOL *DevicePath)
{
    // First check if device is a USB
    if (MatchUefiUsbBootGroup(DevicePath))
    {
        // Then make sure it is not a Hard Drive or CDROM 
        if (!MatchUefiHddBootGroup(DevicePath) && !MatchUefiCdBootGroup(DevicePath))
            // By process of elimination it must then be a Floppy
            return BCP_UEFI_FDD;
    }
    return 0;
}


/**
 This function compares the boot option that is passed in to see if it matches 
    the UEFI group type that is passed in.
  
  @return BOOLEAN
  @retval TRUE - the devices match up
  @retval FALSE - the the device and the UEFI Group do not match
  
 */
BOOLEAN UefiDoesDeviceMatch( 
        IN BCP_BOOT_ORDER_ITEM_INFO *BcpBootOrderItemInfo, 
        IN BOOT_OPTION *Option )
{
    EFI_DEVICE_PATH_PROTOCOL *DevicePath = NULL;
    EFI_STATUS Status;
    UINT8 idx;
    
    // get the device path handle for the device.
    Status = pBS->HandleProtocol(Option->DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID **)&DevicePath);
    if (EFI_ERROR(Status))
    {
        return FALSE;
    }
    
    for(idx = 0; BcpBootOptionFunctions[idx] != NULL; idx++){
        if (BcpBootOptionFunctions[idx](DevicePath) == BcpBootOrderItemInfo->BbsType ) 
        {
            return TRUE;
        }
    }
    return FALSE;
}



/**
    This function Compares the Boot option being passed in to the type of device 
    currently being looked for.  If it is the right type of device, then give it a unique 
    value that defines it. 
               
    @param BcpBootOrderItemInfo pointer to BCP item info for the current type of device being looked for
    @param Option  pointer to the BDS boot option that we are trying to sort

    @retval TRUE device matches the type being looked for and the Bus Order value is set.
    @retval FALSE device does not match the type
**/
BOOLEAN LegacyDoesDeviceMatch( 
    IN BCP_BOOT_ORDER_ITEM_INFO *BcpBootOrderItemInfo, 
    IN BOOT_OPTION *Option )
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL;
    UINTN BusOrder = BCP_UNDEFINED;

    // Compare the BBS type of the passed-in boot option to the BBS type of the entry in 
    //	the BCP_DEVICE_INFO_ARRAY for the current device in the priority boot order
    // if it does't match exit
    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "BcpBootOrderItem BbsType = %X Option DeviceType = %X\n", BcpBootOrderItemInfo->BbsType, Option->BbsEntry->DeviceType));
    
    if (BcpBootOrderItemInfo->BbsType != Option->BbsEntry->DeviceType)
    {
        DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Wrong BBS Type\n"));
		return FALSE;
    }
    // Now verify that the Messaging Device Path Type for the current device in the 
    //	priority boot order is defined
    if (BcpBootOrderItemInfo->MsgDpSubType != BCP_UNDEFINED) {

        // Locate device path by handle
        Status = pBS->HandleProtocol(
            Option->DeviceHandle,
            &gEfiDevicePathProtocolGuid,
            (VOID **)&Dp
        );
        if (EFI_ERROR(Status)) 
        {
            DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "No device Path\n"));
        	return FALSE;
        }

        // find the current boot option's messaging device path
        Dp = GetDevicePathNodeOfType(Dp, MESSAGING_DEVICE_PATH);
        if ( (Dp == NULL) || (Dp->SubType != BcpBootOrderItemInfo->MsgDpSubType) )
        {        	
            DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Bad device Path\n"));
            return FALSE;
        }
        
        // Based on the Type of Messaging device Path set the bus order.
        switch(Dp->SubType) {
    
            // 0=PM, 1=PS, 2=SM, 3=SS
            case MSG_ATAPI_DP:
                BusOrder = 0;
                if ( ((ATAPI_DEVICE_PATH*)Dp)->PrimarySecondary ) 
                    BusOrder |= BIT1; // zero for primary, one for secondary
                if ( ((ATAPI_DEVICE_PATH*)Dp)->SlaveMaster )
                    BusOrder |= BIT0; // zero for master, one for slave mode
            break;
    
            // SATA SATA_DEVICE_PATH includes location information 
            //	so use the HBA Port number to create a unique sorting value
            case MSG_SATA_DP:
                BusOrder = ((SATA_DEVICE_PATH*)Dp)->HBAPortNumber;
            break;

            default:
                BusOrder = BCP_UNDEFINED;
            break;
        }
    }

    if (BcpBootOrderItemInfo->BusOrder != BusOrder) 
    {
		return FALSE;
    }

#if defined (BBS_USB_DEVICE_TYPE_SUPPORT) && (BBS_USB_DEVICE_TYPE_SUPPORT == 1)
	if (BcpBootOrderItemInfo->BbsType == BBS_USB)
	{
		if ((BcpBootOrderItemInfo->TokenNumber == BCP_USB_FDD) && ( (((Option->BbsEntry->InitPerReserved) >> 24) & 0xf) == BAID_TYPE_RMD_FDD ))
		{
		    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Identified as a USB Floppy\n"));
		}
		else if ((BcpBootOrderItemInfo->TokenNumber == BCP_USB_HDD) && ((((Option->BbsEntry->InitPerReserved) >> 24) & 0xf) == BAID_TYPE_RMD_HDD ))
		{
		    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Identified as a USB Hard Drive\n"));
		}
		else if ((BcpBootOrderItemInfo->TokenNumber == BCP_USB_CD) && ( (((Option->BbsEntry->InitPerReserved) >> 24) & 0xf) == BAID_TYPE_CDROM ))
		{
		    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Identified as a USB CDROM\n"));
		}
		else 
			return FALSE;
	}
#endif

    return TRUE;
}

/**
    This function is a parent function that determines whether the device is a Legacy Device or not and then calling the appropriate 
	function.
    @param 	BcpBootOrderItemInfo Pointer to BCP item info for the current type of device type being looked for
    @param 	Option  Pointer to the BDS boot option that we are trying to sort

	@return BOOLEAN
    @retval TRUE - The device matches the device type passed in
	@retval FALSE - The device does not match the device type

*/
BOOLEAN IsDeviceMatch( 
        IN BCP_BOOT_ORDER_ITEM_INFO *BcpBootOrderItemInfo, 
        IN BOOT_OPTION *Option )
{
    
    if (IsLegacyBootOption(Option))
        return LegacyDoesDeviceMatch(BcpBootOrderItemInfo, Option);
    
    return UefiDoesDeviceMatch(BcpBootOrderItemInfo, Option);
}



/**
    This is the Entry point.  If first boot detected then a global variable is set to signal
    SetDefaultBcpBootOptionPriorities function that sorting is needed.

    @param VOID

    @retval VOID

**/

VOID CheckIfFirstBoot(VOID)
{
    DLINK *Link = NULL;
    BOOT_OPTION *Option = NULL;

    // Newly connected devices are have LOWEST_BOOT_OPTION_PRIORITY priority.
    // During the very first there are no boot options in the NVRAM, 
    // which means that all the boot option in the boot list must have 
    // LOWEST_BOOT_OPTION_PRIORITY priority.
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
    {
        // Check if priority not equal LOWEST_BOOT_OPTION_PRIORITY 
        // then it's not a first boot, no action needed.
        if ( Option->Priority != LOWEST_BOOT_OPTION_PRIORITY ) 
            return;
    }
    IsFirstBoot = TRUE;
}


/**
    On the first boot this function sorts the boot options as defined by the BCP Boot Order information

    The BCP boot order defines priorities of boot devices during the first system 
    boot.  If there are no boot options in the NVRAM. Our hook is called after 
    adding all boot options to the boot list and before setting priorities. 
    The boot options in the boot list come from two sources: NVRAM and newly 
    connected devices. NVRAM boot options have priority derived from the BootOrder
    NVRAM variable. 

    @param VOID

    @retval VOID

**/
VOID SetDefaultBcpBootOptionPriorities(VOID)
{
    EFI_GUID BcpBootOrderSectionGuid = BCP_BOOT_ORDER_SECTION_GUID;
    EFI_GUID BcpBootOrderFileGuid = BCP_BOOT_ORDER_FILE_GUID;
    BCP_BOOT_ORDER_ITEM_INFO BcpBootOrderItemInfo[] = BCP_DEVICE_INFO_ARRAY;
    DLINK *Link = NULL;
    BOOT_OPTION *Option = NULL;
    EFI_STATUS Status;
    BCP_BOOT_ORDER_SECTION *BcpSection = NULL;
    UINT32 Priority = 0; 
    UINTN  i; 
    UINTN  j;
    UINT16 OptionNumber;
    BOOT_OPTION *Option2;
    UINT32 OptionPriority;

    // This code should only execute on the first boot.
    if (!IsFirstBoot) 
        return;
    
    DUMP_BOOT_OPTION_LIST(BootOptionList,"Before BCP Boot Order");

    // STEP 1:
    // Read BCP Default Boot Order Section from the FFS file
    // the format of the section is defined by the BCP_BOOT_ORDER_SECTION type.
    // The values in the Option array are defined by the BCP_BOOT_ORDER_ITEM array
    // Locate default BCP Boot Order GUIDed section
    Status = LocateSectionResource(
        &BcpBootOrderFileGuid, 
        &BcpBootOrderSectionGuid, 
        (UINT8 **)&BcpSection
     );
    if (EFI_ERROR(Status)) {
        return;
    }
    // sort list before processing to make sure group headers are with the boot option 
    //  device type and are first within that group.
    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nAfter first sort of Boot Order");

    //STEP 2:
    // Assign priorities to all the boot options
    
    // Loop through all the boot option to Give the Group Headers a unique Priority value 
    //  that will identify it as not assigned yet
    FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
    {
        if (Option->GroupHeader) 
        {
            Option->Priority = 0xFF00;
        }   
    }

    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nBefore matching boot options");

    // Go though the BCP boot order variable to find all the devices of each type and give it the 
    // proper priority order.
    for ( i = 0; i < BcpSection->NumberOfOptions; i++ ) {
        // Find the matching description item for option from BCP order from the 
    	// BCP_DEVICE_INFO_ARRAY.
        for ( j = 0; j < ( sizeof(BcpBootOrderItemInfo) / sizeof(BCP_BOOT_ORDER_ITEM_INFO) ); j++ ) {
            if ( BcpBootOrderItemInfo[j].TokenNumber == BcpSection->Option[i] )
            {
                break;
            }
        }
        if(j == ( sizeof(BcpBootOrderItemInfo) / sizeof(BCP_BOOT_ORDER_ITEM_INFO) ))
            continue;

        DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "\nBCP Type %d\n", BcpSection->Option[i]));
        // Loop through all the boot option to set priority for each one
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
        	// Check for embedded shell and handle this
            if (BcpSection->Option[i] == BCP_UEFI_EMBEDDED_SHELL)
            {
                if (IsEmbeddedShell(Option))
                {
                    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Found Shell!!\n"));
                	Option->Priority = Priority++;
                }
				continue;
            }
            
            // This handles setting the priority value for group headers so that they can be 
            //	grouped with the first entry of their device types
            if (Option->GroupHeader) 
            {
                if ((Option->Priority == 0xFF00) && 
                        ( GetLegacyDevOrderType(Option) == BcpBootOrderItemInfo[j].BbsType ))
                {
                    DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Found a group header!!\n"));
                	Option->Priority = Priority++;
                }
                continue;
            }

            // sets the priority of the boot option if the option is of the same 
            //  BCP Type that we are currently trying to order
            if ( IsDeviceMatch(&BcpBootOrderItemInfo[j],Option) ) {
                DEBUG((BCP_DEBUG_MESSAGES_LEVEL, "Found: Device matched!!\n"));
                Option->Priority = Priority++;
            }
        }
    }
    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nAfter matching boot options");

    SortList(BootOptionList, ComparePriorityThenBootOptionNumber);
    
    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nAfter Sort following matching");

    // updating the device priority based on highest(lowest number value) priority of a given type
    Link = BootOptionList->pHead;
    while(Link != NULL) {
        Option = OUTTER(Link,Link,BOOT_OPTION);
        OptionNumber = Option->BootOptionNumber;
        OptionPriority = LOWEST_BOOT_OPTION_PRIORITY;

        // This tries to find the highest Priority(lowest value) of all the devices 
        // of a given type
        while(Link != NULL) {
            Option2 = OUTTER(Link, Link, BOOT_OPTION);
            if (OptionNumber != Option2->BootOptionNumber) 
                break;
            if (Option->Priority < OptionPriority) 
                OptionPriority = Option->Priority;
            Link = Link->pNext;
        }
        
        // This assigns the highest Priority(lowest value) found above to the beginning
        // of the Priority value to help with sorting in the next step.
        Link = &Option->Link;
        while(Link != NULL) {
            Option2 = OUTTER(Link,Link,BOOT_OPTION);
            if (OptionNumber != Option2->BootOptionNumber) 
                break;
            Option2->Priority |= OptionPriority << 16;
            Link = Link->pNext;
        }
    }

    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nbefore Boot Option List sort");

    
    // If the group by tag is on, make sure that all boot options with the same boot Option Numer are grouped together
    if ( GROUP_BOOT_OPTIONS_BY_TAG == 1)
    {
    	UINT32 Idx;
        DLINK *Temp = NULL, *Link2 = NULL;

        Link = BootOptionList->pHead;
        while(Link != NULL) {
            Option = OUTTER(Link,Link,BOOT_OPTION);
            // No more options in the List
            if (Link->pNext == NULL)
            	break; 
            Link2 = Link->pNext;
            Option2 = OUTTER(Link2, Link, BOOT_OPTION);
            if (Option->BootOptionNumber == Option2->BootOptionNumber)
            {
            	Link = Link2;
            	continue;
            }
            else 
            {
            	Link2 = Link2->pNext;
            	while (Link2 != NULL)
            	{
                    Option2 = OUTTER(Link2, Link, BOOT_OPTION);
                    if (Option->BootOptionNumber == Option2->BootOptionNumber)
                    {
                    	// Add code here to move Link2 from where it is to after Link in the list
                    	Temp = Link2->pPrev;
                    	Link2->pPrev->pNext = Link2->pNext;
                    	if (Link2->pNext != NULL)
                    		Link2->pNext->pPrev = Link2->pPrev;
                    	
                    	Link2->pPrev = Link;
                    	Link2->pNext = Link->pNext;

                    	Link->pNext->pPrev = Link2;
                    	Link->pNext = Link2;

                    	// now that the boot option has been moved, re-initialize Link2 to the node before where Link2 was
                    	Link2 = Temp;
                    }
                    Link2 = Link2->pNext;
            		
            	}
            }
        	Link = Link->pNext;
        }

        DUMP_BOOT_OPTION_LIST(BootOptionList,"\nAfter BootOption Sort");

        // Update Priority
        Idx = 0;
        FOR_EACH_BOOT_OPTION(BootOptionList,Link,Option)
        {
        	Option->Priority = Idx++;
        }
    }
    
    DUMP_BOOT_OPTION_LIST(BootOptionList,"\nAfter BCP Processing");
    pBS->FreePool(BcpSection);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
