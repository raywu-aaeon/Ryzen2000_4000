//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file  HardwareChangeDetect.c

  This file will detect the current Hardware configuration.
  
**/

///----------------------------------------------------------------------
/// Include Files
///----------------------------------------------------------------------
#include <Uefi.h>
#include <HardwareChangeProtocol.h>
#include <HardwareSignatureLib.h>
#if HARDWARE_SIGNATURE_PS2_CHANGE
#include <AmiGenericSio.h>
#endif
///---------------------------------------------------------------------------
/// Global Variable declarations
///---------------------------------------------------------------------------

  
STATIC CHAR8 *gMemMapType[] = {
    "reserved  ",
    "LoaderCode",
    "LoaderData",
    "BS_code   ",
    "BS_data   ",
    "RT_code   ",
    "RT_data   ",
    "available ",
    "Unusable  ",
    "ACPI_recl ",
    "ACPI_NVS  ",
    "MemMapIO  ",
    "MemPortIO ",
    "PAL_code  ",
    "PersistentMem"    
};


/**
 * 
 * Check the memory size is different.
 * 
 * This function compares the current and previous memory sizes. 
 * 
 * @param[in]    CurMemorySizeMb     Current memory size (MB)
 * @param[in]    PreMemorySizeMb     Previous memory size (MB)
 * 
 * @retval       TRUE                Memory sizes are different.
 * @retval       FALSE               Memory sizes are similar.
**/

BOOLEAN 
IsDifferentMemorySize (
    IN UINT32 CurMemorySizeMb,
    IN UINT32 PreMemorySizeMb )
{
    BOOLEAN BitDifferent = FALSE;

    DEBUG((DEBUG_INFO, "Diff Mem Size - Cur:0x%x MB, Pre:0x%x MB\n", CurMemorySizeMb, PreMemorySizeMb));

    if (CurMemorySizeMb > PreMemorySizeMb)
    {
        if ((CurMemorySizeMb - PreMemorySizeMb) >=  THRESHOLD_OF_DIFFERENT_MEMORY_SIZE)
        {  
            BitDifferent = TRUE;
        }
    }
    else if (CurMemorySizeMb < PreMemorySizeMb)
    {
        if ((PreMemorySizeMb - CurMemorySizeMb) >=  THRESHOLD_OF_DIFFERENT_MEMORY_SIZE)
        {
            BitDifferent = TRUE;
        }
    }
    return BitDifferent;
}

/**
 * Get memory map data
 * 
 * This function detects the current memory size and memory map data.
 * 
 * @param[in,out]    MemMapConfigData    Current memory map data and memory size(MB)
 * 
 * @retval           EFI_SUCCESS         Detect the current memory map data successfully.
 * @retval           Other               Get MemoryMap failed or allocate pool failed.
**/

EFI_STATUS 
GetMemMapData (
    IN OUT AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA *MemMapConfigData )
{
    EFI_STATUS                Status = EFI_NOT_READY;
    UINTN                     MemMapSize = 0;
    EFI_MEMORY_DESCRIPTOR     *MemMap = NULL;
    EFI_MEMORY_DESCRIPTOR     *OrigMemMap = NULL;
    UINTN                     MapKey = 0;
    UINTN                     DescriptorSize = 0;
    UINT32                    DescriptorVersion = 0;
    UINTN                     Index = 0;
    UINT64                    TotalMemoryPages= 0;
    UINTN                     AllocateMemMapSize = 0;    
    EFI_PHYSICAL_ADDRESS      EndAddress = 0;
    EFI_PHYSICAL_ADDRESS      StartAddress = 0;
    UINT64                    EntrySize = 0;
    UINT8                     EndAddrChecksum = 0;
    UINT8                     StartAddrChecksum = 0;
    UINT32                    AddrData = 0; 
    UINT8                     MemChecksum = 0;
    CHAR8                     *MemMapType = 0;

    ///Detect the memory map only once.  
    static BOOLEAN            IsMemoryMapDetected = FALSE;
    static AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA DetectMemMapConfigData;

    if (MemMapConfigData == NULL) 
        return EFI_INVALID_PARAMETER;
    ///
    /// To detect the memory map only once
    ///
    if (!IsMemoryMapDetected)    
    {
        gBS->SetMem (&DetectMemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA), 0);
        gBS->SetMem (MemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA), 0);
    } 
    else
    {
        gBS->CopyMem (MemMapConfigData, &DetectMemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA));
        return EFI_SUCCESS;
    }
    
    Status = gBS->GetMemoryMap (&MemMapSize, 
                                MemMap, 
                                &MapKey, 
                                &DescriptorSize, 
                                &DescriptorVersion);
    if (Status != EFI_BUFFER_TOO_SMALL)
        return Status;
  
    MemMapSize += EFI_PAGE_SIZE;
    AllocateMemMapSize = MemMapSize;
    
    Status = gBS->AllocatePool (EfiBootServicesData,
                                AllocateMemMapSize,
                                (VOID**)&MemMap );
    if (EFI_ERROR (Status))
        return Status;

    Status = gBS->GetMemoryMap (&MemMapSize, 
                                MemMap, 
                                &MapKey, 
                                &DescriptorSize, 
                                &DescriptorVersion);
    if (EFI_ERROR (Status))
    {
        gBS->FreePool (MemMap);  
        return Status;
    }
    
    OrigMemMap = MemMap;

    StartAddrChecksum   = 0;
    EndAddrChecksum     = 0;
    MemChecksum         = 0;
    for (Index = 0; Index < MemMapSize / DescriptorSize; Index++)
    {
        ///
        /// Calculate the checksum from StartAddress to EndAddress in each Memory Type,
        /// whereas eliminate the Memory Types which will be released after OS.
        ///
        if (IsRestoreMemoryType(MemMap->Type))
        {

            EntrySize = LShiftU64 (MemMap->NumberOfPages, EFI_PAGE_SHIFT);
            StartAddress = MemMap->PhysicalStart;
            EndAddress = MemMap->PhysicalStart + EntrySize - 1;

            AddrData = (UINT32)(RShiftU64 (EndAddress, EFI_PAGE_SHIFT));
            EndAddrChecksum += (UINT8)(AddrData);
            EndAddrChecksum += (UINT8)(AddrData >> 8);
            EndAddrChecksum += (UINT8)(AddrData >> 16);
            
            AddrData = (UINT32)(RShiftU64 (StartAddress, EFI_PAGE_SHIFT));
            StartAddrChecksum += (UINT8)AddrData;
            StartAddrChecksum += (UINT8)(AddrData >> 8);
            StartAddrChecksum += (UINT8)(AddrData >> 16);
            AddrData = 0;
            //We can use memmap command on SHELL to compare the result with the following debug message.

            MemMapType = gMemMapType[MemMap->Type % EfiMaxMemoryType];
            DEBUG((DEBUG_INFO, "%a %016lX - %016lX: # %016lX %016lX\n", MemMapType, StartAddress, EndAddress, MemMap->NumberOfPages, MemMap->Attribute));
     
            }  
        ///
        /// Accumulate pages of the following memory type for calculate total memory size.
        ///
        switch (MemMap->Type) {
          case EfiLoaderCode:
          case EfiLoaderData:
          case EfiBootServicesCode:
          case EfiBootServicesData:
          case EfiRuntimeServicesCode:
          case EfiRuntimeServicesData:
          case EfiConventionalMemory:
          case EfiPersistentMemory:
          case EfiACPIReclaimMemory:
          case EfiACPIMemoryNVS:
          case EfiPalCode:
               TotalMemoryPages += MemMap->NumberOfPages;
            break;
          default:
            break;
        }               
        MemMap = (EFI_MEMORY_DESCRIPTOR *)((UINTN)MemMap + DescriptorSize);
    }

    MemChecksum = (UINT8)(StartAddrChecksum + EndAddrChecksum);
    DetectMemMapConfigData.MemMapCheckSum = MemChecksum;
    DetectMemMapConfigData.MemoryMbSize = (UINT32)DivU64x32 (MultU64x64 (SIZE_4KB, TotalMemoryPages), SIZE_1MB);//MB
    ///
    ///When all of the DetectMemMapConfigData are saved, this variable is 
    ///changed to "TRUE" 
    ///
    IsMemoryMapDetected = TRUE; 
    DEBUG((DEBUG_INFO, "DetectMemMapConfigData.MemMapCheckSum:%lx\n", DetectMemMapConfigData.MemMapCheckSum));

    gBS->CopyMem (MemMapConfigData, &DetectMemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA));

    DEBUG((DEBUG_INFO, "GetMemMapData - MemoryMbSize:%ld MB\n", MemMapConfigData->MemoryMbSize));

    gBS->FreePool (OrigMemMap);  
    
    return Status;
}

#if HARDWARE_SIGNATURE_PS2_CHANGE
/**
  Detect PS2 Keyboard/Mouse State

  This function gets the SIO variable from NVRAM. It records the PS2 KB/Mouse
  are present or not.

  The tokens "GenericSio_SUPPORT" need to enable. 

  @param[in,out]       Present            Current Type is present or not.

  @retval              EFI_SUCCESS        Get SIO variable successfully.
  @retval              EFI_NOT_FOUND      Get SIO variable failed.

**/
EFI_STATUS 
DetectPs2KeyboardMouseState (
  IN OUT AMI_HARDWARE_SIGNATURE_PS2_DATA *Present )
{
    EFI_GUID       SioDevStatusVarGuid = SIO_DEV_STATUS_VAR_GUID;
    UINTN          SioDevStatusVarSize = sizeof(SIO_DEV_STATUS);
    SIO_DEV_STATUS SioDevStatus;
    UINT32         SioDevStatusVarAttributes = 0;
    EFI_STATUS     Status;
    DEBUG((DEBUG_INFO,"[HardwareSignature]HardwareChangeDetect\n"));
    //
    // Get the SIO variable.
    //
    Status = gRT->GetVariable( SIO_DEV_STATUS_VAR_NAME, 
                                &SioDevStatusVarGuid, 
                                &SioDevStatusVarAttributes,
                                &SioDevStatusVarSize, 
                                &SioDevStatus.DEV_STATUS);

    if(Status == EFI_NOT_FOUND)
    {   //Can't detect SIO_DEV_STATUS_VAR_NAME, present states of KB/Mouse is false.
        
        Present->Keyboard   = FALSE;
        Present->Mouse      = FALSE;
        
        return EFI_NOT_FOUND;
    }
    else if(Status == EFI_SUCCESS)
    {   //Get GenericSio variable success.
        
        if(SioDevStatus.Key60_64 == 1)
        {   //PS2 Keyboard is present 
            Present->Keyboard = TRUE;
        }
        else
        {   //PS2 Keyboard isn't present 
            Present->Keyboard = FALSE;
        }
        
        if(SioDevStatus.Ps2Mouse == 1)
        {   //PS2 Mouse is present 
            Present->Mouse = TRUE;
        }
        else
        {   //PS2 Mouse isn't present
            Present->Mouse = FALSE;
        }
    }

    return Status;
    
}
#endif

/**
*  Get PCI device data
*
*  This function gathers the PCI Information excepting on-board PCI device and calculates the checksum  
*  of Bus number/Device number/Function number, VID/DID.
*
*  @param[in,out]   HardwarePciData             Report PCI info checksum.
*                                           
*  @retval          EFI_SUCCESS                 Detect the current PCI data successfully.
*  @retval          EFI_INVALID_PARAMETER       Input data HardwarePciData is NULL 
*  @retval          Other                       Get PCI data failed.
**/

EFI_STATUS 
GetPciDeviceData (
    IN OUT AMI_HARDWARE_SIGNATURE_PCI_DATA *HardwarePciData )
{
    EFI_STATUS          Status;
    EFI_HANDLE          *HandleBuffer;
    AMI_HARDWARE_SIGNATURE_PCI_CONFIG_INFO  *PciConfigInfo  = NULL;
    UINTN               NumberOfPciHandles  = 0;
    EFI_PCI_IO_PROTOCOL *EfiPciIoProtocol = NULL; 
    UINTN               SegmentNumber   = 0;
    UINTN               BusNumber       = 0;
    UINTN               DeviceNumber    = 0;
    UINTN               FunctionNumber  = 0;
    UINT32              VidDid          = 0; 
    UINT16              Index;

    if (HardwarePciData == NULL)
        return EFI_INVALID_PARAMETER;

    gBS->SetMem (HardwarePciData, sizeof(AMI_HARDWARE_SIGNATURE_PCI_DATA), 0);
    
    // Locate handle buffer for PCI IO Protocol.
    Status = gBS->LocateHandleBuffer (ByProtocol, 
                                      &gEfiPciIoProtocolGuid, 
                                      NULL, 
                                      &NumberOfPciHandles, 
                                      &HandleBuffer);
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    Status = gBS->AllocatePool (EfiBootServicesData,
                                NumberOfPciHandles * sizeof(AMI_HARDWARE_SIGNATURE_PCI_CONFIG_INFO),
                                (VOID**)&PciConfigInfo);
    if (EFI_ERROR(Status)) {
        gBS->FreePool (HandleBuffer);
        return Status;
    }
        
    gBS->SetMem (PciConfigInfo, NumberOfPciHandles * sizeof (AMI_HARDWARE_SIGNATURE_PCI_CONFIG_INFO), 0);

    for (Index = 0; Index < NumberOfPciHandles; Index++) {
        // Handle PCI IO Protocol.
        Status = gBS->HandleProtocol (HandleBuffer[Index],
                                      &gEfiPciIoProtocolGuid, 
                                      (VOID**)&EfiPciIoProtocol);
        if (EFI_ERROR(Status)) {
            gBS->FreePool (HandleBuffer);
            gBS->FreePool (PciConfigInfo);
            return Status;
            }

        // Get PCI IO location.
        Status = EfiPciIoProtocol->GetLocation (EfiPciIoProtocol, &SegmentNumber, &BusNumber, &DeviceNumber, &FunctionNumber);
        if (EFI_ERROR(Status)) { 
            gBS->FreePool (HandleBuffer);
            gBS->FreePool (PciConfigInfo);
            return Status;
        }

        // Skip on-board device. 
        if (BusNumber == 0) 
            continue;

        Status = EfiPciIoProtocol->Pci.Read (EfiPciIoProtocol, EfiPciIoWidthUint32, 0, 1, &VidDid);
        if (EFI_ERROR (Status))
            continue;
                
        // Gather the PCI Bus Number 
        PciConfigInfo[Index].BusNumber      = (UINT8)BusNumber;
        // Gather the PCI Device Number
        PciConfigInfo[Index].DeviceNumber   = (UINT8)DeviceNumber;
        // Gather the PCI Function Number
        PciConfigInfo[Index].FunctionNumber = (UINT8)FunctionNumber;
        // Gather the PCI Vendor ID.
        PciConfigInfo[Index].VendorId       = (UINT16)(VidDid);
        // Gather the PCI Device ID.
        PciConfigInfo[Index].DeviceId       = (UINT16)(VidDid >> 16);

        DEBUG((DEBUG_INFO, "Get PCI Configuration Info : Bus: %X , Device: %X, Function: %X, VenderId:%X, DeviceId:%X\n", 
                PciConfigInfo[Index].BusNumber,
                PciConfigInfo[Index].DeviceNumber, 
                PciConfigInfo[Index].FunctionNumber, 
                PciConfigInfo[Index].VendorId, 
                PciConfigInfo[Index].DeviceId));
    }
    //
    // Calculate CRC 32
    //
    Status = gBS->CalculateCrc32 (&PciConfigInfo[0].PciNumber, (UINT16)(NumberOfPciHandles * sizeof(AMI_HARDWARE_SIGNATURE_PCI_CONFIG_INFO)), &HardwarePciData->PciInfoChecksum);
     
    if (EFI_ERROR (Status)) {   
        DEBUG((DEBUG_ERROR, "ERROR: PCI Configuration Info CRC32 calculation failed :%r\n", Status));   
    } 
    
    DEBUG((DEBUG_INFO, "PCI Configuration Info CRC32 calculation :%x\n", HardwarePciData->PciInfoChecksum));   
    
    gBS->FreePool (HandleBuffer);
    gBS->FreePool (PciConfigInfo);

    return Status;
}

/**
 * Get USB device data
 * 
 * This function detects the current number of the USB devices and calculate  
 * the checksum of Parent Port Number/Interface Number, and VID/PID.
 * 
 * @param[in,out]    HardwareUsbData         Get current USB data.
 * 
 * @retval           EFI_SUCCESS             Detect the current USB data successfully.
 * @retval           EFI_INVALID_PARAMETER   Input data HardwareUsbData is NULL 
 * @retval           Other                   Get USB data failed.
**/

EFI_STATUS 
GetUsbDeviceData (
    IN OUT AMI_HARDWARE_SIGNATURE_USB_DATA *HardwareUsbData )
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  *HandleBuffer;
    UINTN                       HandleCount = 0;
    EFI_USB_IO_PROTOCOL         *UsbIo;      
    EFI_USB_DEVICE_DESCRIPTOR   DevDes;        
    UINT16                      Vid;
    UINT16                      Pid;
    UINT8                       VidPidChecksum;   
    EFI_GUID                    EfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePathNode;
    UINT8                       PortNumInterfaceNumChecksum = 0;
    UINT8                       InterfaceNumber;
    UINT8                       ParentPortNumber;
    UINT16                      UsbNum = 0;
    UINT16                      Index;

    if (HardwareUsbData == NULL)
        return EFI_INVALID_PARAMETER;

    gBS->SetMem (HardwareUsbData, sizeof(AMI_HARDWARE_SIGNATURE_USB_DATA), 0);
    
    // Locate handle buffer for USB IO Protocol
    Status = gBS->LocateHandleBuffer (ByProtocol, 
                                      &gEfiUsbIoProtocolGuid, 
                                      NULL, 
                                      &HandleCount, 
                                      &HandleBuffer);
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    Vid = 0; 
    Pid = 0;
    InterfaceNumber = 0; 
    ParentPortNumber = 0;
    VidPidChecksum = 0;
    PortNumInterfaceNumChecksum = 0;

    for (Index = 0; Index < HandleCount; Index++) {
        // Handle USB IO Protocol
        Status = gBS->HandleProtocol (HandleBuffer[Index],
                                      &gEfiUsbIoProtocolGuid, 
                                      (VOID**)&UsbIo);
        if (EFI_ERROR(Status)) { 
            gBS->FreePool (HandleBuffer);
            return Status;
        }

        // Get USB IO Descriptor
        Status = UsbIo->UsbGetDeviceDescriptor (UsbIo, &DevDes);
        if (EFI_ERROR(Status)) {
            gBS->FreePool (HandleBuffer);
            return Status;
        }
    
        Vid = DevDes.IdVendor;
        Pid = DevDes.IdProduct;

        VidPidChecksum += ((UINT8)Vid + (UINT8)(Vid >> 8));
        VidPidChecksum += ((UINT8)Pid + (UINT8)(Pid >> 8));

        UsbNum++;
        // Get USB DevicePath
        Status = gBS->HandleProtocol (HandleBuffer[Index],
                                      &EfiDevicePathProtocolGuid, 
                                      (VOID *)&DevicePath );
        if (EFI_ERROR(Status)) 
            continue;

        // Is USB Device Path ?
        DevicePathNode = DevicePath;
        while (!IsDevicePathEnd (DevicePathNode)) {
            if (DevicePathNode->Type == MESSAGING_DEVICE_PATH) {
                if (DevicePathNode->SubType == MSG_USB_DP) {     
              
                    ParentPortNumber = ((USB_DEVICE_PATH*)DevicePathNode)->ParentPortNumber;
                    InterfaceNumber = ((USB_DEVICE_PATH*)DevicePathNode)->InterfaceNumber;

                    PortNumInterfaceNumChecksum += (UINT8)(ParentPortNumber + InterfaceNumber);
                    DEBUG((DEBUG_INFO, "Index:%x - USB(0x%x, 0x%x)\n", Index, ParentPortNumber, InterfaceNumber));
                }
                
            } 
            DevicePathNode = NextDevicePathNode (DevicePathNode);
        }
    }
    gBS->FreePool (HandleBuffer);

    HardwareUsbData->UsbNum = UsbNum;
    HardwareUsbData->VidPidChecksum = CalculateCheckSum8 (&VidPidChecksum, sizeof(UINT8)); 
    HardwareUsbData->PortNumInterfaceNumChecksum = CalculateCheckSum8 (&PortNumInterfaceNumChecksum, sizeof(UINT8)); 
    
    DEBUG((DEBUG_INFO, "Usb#:%d, Checksum -VID DID:%x , PortNum_InterNum:%x\n", HardwareUsbData->UsbNum, HardwareUsbData->VidPidChecksum, HardwareUsbData->PortNumInterfaceNumChecksum));
    
    return Status;
}

/**
 * Get Edid data.
 * 
 * This function gets the checksum data of EDID.
 * 
 * @param[in,out]    HardwareVideoData           Record the EdidCheckNum of  current Video data.
 * 
 * @retval           EFI_SUCCESS                 Detect the current EDID successfully.
 * @retval           EFI_INVALID_PARAMETER       Invalid parameter.
 * @retval           EFI_NOT_FOUND               EfiEdidDiscoveredProtocolGuid interface not found.
**/

EFI_STATUS 
GetEdidData (
    IN OUT AMI_HARDWARE_SIGNATURE_VIDEO_DATA *HardwareVideoData )
{
    EFI_STATUS                         Status;    
    UINT8                              EdidChecksum = 0;  
    UINT32                             Index = 0;
    EFI_EDID_DISCOVERED_PROTOCOL       *EdidDiscoveredProtocol;

    HardwareVideoData->EdidCheckNum = 0;

    Status = gBS->LocateProtocol (&gEfiEdidDiscoveredProtocolGuid,
                                    NULL,
                                   (VOID**)&EdidDiscoveredProtocol);
    
    DEBUG((DEBUG_INFO, "Locate EDID discovered protocol:%r\n", Status));

    if (EFI_ERROR(Status)) 
        return Status;

    DEBUG((DEBUG_INFO, "EDID Size:%d\n", EdidDiscoveredProtocol->SizeOfEdid));

    Status = EFI_NOT_FOUND; 
    if (EdidDiscoveredProtocol->SizeOfEdid != 0 && EdidDiscoveredProtocol->Edid != NULL) {
        if (EdidDiscoveredProtocol->SizeOfEdid == VESA_BIOS_EXTENSIONS_EDID_BLOCK_SIZE) {
            Index = EdidDiscoveredProtocol->SizeOfEdid - 1;
            EdidChecksum = EdidDiscoveredProtocol->Edid[Index];
            Status = EFI_SUCCESS;    
        }        
    }

    if (!EFI_ERROR(Status)) {
        HardwareVideoData->EdidCheckNum = EdidChecksum;
        DEBUG((DEBUG_INFO, "EdidCheckNum:0x%x\n", EdidChecksum));
    }    

    return Status;
}

/**
 * Get Resolution data
 * 
 * This function gets all resolution data and calculates the the checksum of resolution data.
 * 
 * @param[in,out]    HardwareVideoData           Record the ResolutionChecksum of current Video data.
 * 
 * @retval           EFI_SUCCESS                 Get all resolution data and calculate checksum successfully.
 * @retval           EFI_INVALID_PARAMETER       Invalid parameter.
 * @retval           EFI_NOT_FOUND               EfiGraphicsOutputProtocolGuid interface not found.
**/

EFI_STATUS 
GetResolutionData (
    IN OUT AMI_HARDWARE_SIGNATURE_VIDEO_DATA *HardwareVideoData )
{
    EFI_STATUS                                   Status;
    UINT8                                        TotalChecksum  = 0;
    UINT8                                        Checksum       = 0;
    UINT8                                        CountOfPixel;
    EFI_GRAPHICS_OUTPUT_PROTOCOL                 *GraphicsOutput;
    UINT32                                       TmpSum = 0;
    BOOLEAN                                      GetData = TRUE;

    HardwareVideoData->ResolutionChecksum = 0;

    
    Status = gBS->LocateProtocol (&gEfiGraphicsOutputProtocolGuid,
                                  NULL,
                                 (VOID**)&GraphicsOutput);
    if (EFI_ERROR(Status))
    {
        GetData = FALSE;
    }
    else 
    {   
        // 1. TmpSum: Sum of HorizontalResolution + VerticalResolution
        // 2. CheckSum: the checksum of TmpSum
        // 3. TotalCheckSum: sum of CheckSum           
        TmpSum = GraphicsOutput->Mode->Info->HorizontalResolution + 
                 GraphicsOutput->Mode->Info->VerticalResolution;

            Checksum = (UINT8)TmpSum;
            for( CountOfPixel = 1; CountOfPixel < sizeof(TmpSum); CountOfPixel++) {    
                TmpSum = TmpSum >> 8;
                Checksum = Checksum + (UINT8)TmpSum;
            }

            TotalChecksum = TotalChecksum + Checksum;
    }   

    if (GetData)
    {
        TotalChecksum = CalculateCheckSum8 (&TotalChecksum, sizeof(UINT8));
        DEBUG((DEBUG_INFO, "Resolution TotalCheckSum:0x%x\n", TotalChecksum));
        HardwareVideoData->ResolutionChecksum = TotalChecksum;
        Status = EFI_SUCCESS;
    }
    else
    {
        Status = EFI_NOT_FOUND;
    }
    return Status;
}

/**
 * 
 * Get Video data
 * 
 * This function gets the checksum of EDID and calculates the checksum 
 * of all resolution data.
 * 
 * @param[out]   HardwareVideoData   Get current Video data.
 * 
 * @retval       EFI_SUCCESS         Get the current Video data successfully.
 * @retval       EFI_UNSUPPORTED     Get the current Video data failed.  
**/

EFI_STATUS 
GetVideoData (
    OUT AMI_HARDWARE_SIGNATURE_VIDEO_DATA *HardwareVideoData )
{
    EFI_STATUS                    Status;
    BOOLEAN                       BitSuccess = FALSE;
    
    Status = GetEdidData (HardwareVideoData);
    DEBUG((DEBUG_INFO, "GetEdidData: %r\n", Status));
    if (!EFI_ERROR(Status))
        BitSuccess = TRUE;
    
    Status = GetResolutionData (HardwareVideoData);
    DEBUG((DEBUG_INFO, "GetResolutionData: %r\n", Status));
    if (!EFI_ERROR(Status))
        BitSuccess = TRUE;
        
    if (BitSuccess)
        return EFI_SUCCESS;

    return EFI_UNSUPPORTED;
    
}

/**
* Get disk Information data
*  
* Calculate the disk checksum , include port number and serial number.
* Calculate the CRC32 checksum with port number and serial number of all disks.
*
* @param[out]   HardwareDiskData    Get current Disk data.
*
* @retval       HardwareDiskData    Report current Disk data.
*                                   CRC32 checksum      Get the current Disk data successfully.
*                                   ~(DiskChecksum of previous disk data)   Get the current Disk data failure
*               
* @retval       EFI_SUCCESS         Get the current Disk data successfully.
*               EFI_NOT_READY       Get the current Disk data unsuccessfully.
*               
**/

EFI_STATUS 
GetDiskInfoData (
    OUT AMI_HARDWARE_SIGNATURE_DISK_DATA *HardwareDiskData )
{

    EFI_HANDLE             *HandleBuffer;
    EFI_DISK_INFO_PROTOCOL *DiskInfo;   
    AMI_HARDWARE_SIGNATURE_DISK_CONFIG_INFO         *DiskStructure;
    EFI_STATUS             Status;
    UINTN                  NumberOfDiskHandles = 0;
    UINT8                  Index;
    UINT32                 IdeChannel; 
    UINT32                 IdeDevice;
    UINT32                 IdentifyDataSize; 
    VOID                   *IdentifyData = NULL;
    // 
    // According to VOLUME 5: Platform Initialization Specification Standards Version 1.4 Page 77.
    // we can use IDE Disk Information Protocol to gather IdeChannel, IdentifyData.
    //
    Status = gBS->LocateHandleBuffer (ByProtocol,
                                      &gEfiDiskInfoProtocolGuid,
                                      NULL,
                                      &NumberOfDiskHandles,
                                      &HandleBuffer);
    if (EFI_ERROR(Status))
    {
        HardwareDiskData->DiskInfoChecksum = 0xff;
        return EFI_NOT_READY;
    }
    
    Status = gBS->AllocatePool (EfiBootServicesData,
                                NumberOfDiskHandles * sizeof (AMI_HARDWARE_SIGNATURE_DISK_CONFIG_INFO),
                                (VOID**)&DiskStructure);
    if (EFI_ERROR(Status)) {
        gBS->FreePool (HandleBuffer);
        return Status;
    }
    
    gBS->SetMem (DiskStructure, NumberOfDiskHandles * sizeof (AMI_HARDWARE_SIGNATURE_DISK_CONFIG_INFO), 0);
    
    for (Index = 0; Index < NumberOfDiskHandles; Index++)
    {
        Status = gBS->HandleProtocol (HandleBuffer[Index], &gEfiDiskInfoProtocolGuid, (VOID**)&DiskInfo );
        if (EFI_ERROR(Status)) continue;
        //            
        // If GUID is IDE, then gather IDE disk information into checksum.
        //        
        if (CompareGuid (&DiskInfo->Interface, &gEfiDiskInfoIdeInterfaceGuid)) {
            //
            // 1.Gather channel number
            //
            Status = DiskInfo->WhichIde (DiskInfo, &IdeChannel, &IdeDevice);
            if (!EFI_ERROR(Status)) {
                DiskStructure[Index].PortNumber = IdeChannel;
            }
            //
            // 2.Gather serial number 
            //
            // According to DiskInfoIdentify in IdeBus.c, the identify data uses IDENTIFY_DATA as data structure.
            IdentifyDataSize = sizeof(IDENTIFY_DATA);
            gBS->AllocatePool (EfiBootServicesData, 
                               IdentifyDataSize, 
                               (VOID**) &IdentifyData);
            
            Status = DiskInfo->Identify (DiskInfo, IdentifyData, &IdentifyDataSize);
            if (EFI_ERROR(Status)) continue;

            gBS->CopyMem (&DiskStructure[Index].IdentifyData, &((IDENTIFY_DATA*)IdentifyData)->Serial_Number_10, ATA_SERIAL_NUMBER_LENGTH);  
           
            if (IdentifyData) {            
                gBS->FreePool (IdentifyData);
                IdentifyData = NULL;
            }
        }
        //            
        // If GUID is NVME, then gather NVME disk information into checksum.
        //        
        else if (CompareGuid (&DiskInfo->Interface, &gEfiDiskInfoNvmeInterfaceGuid)) {
            //
            // 1.Gather channel number
            //
            Status = DiskInfo->WhichIde (DiskInfo, &IdeChannel, &IdeDevice);
            if (!EFI_ERROR(Status)) {
                DiskStructure[Index].PortNumber = IdeChannel;
            }
            //
            // 2.Gather NVME IEEE Extended Unique Identifier (EUI64) 
            //
            IdentifyDataSize = sizeof(NVME_IDENTIFY_NAMESPACE_DATA);
            gBS->AllocatePool (EfiBootServicesData, 
                               IdentifyDataSize, 
                               (VOID**) &IdentifyData);
           
            gBS->SetMem (IdentifyData, IdentifyDataSize, 0);

            Status = DiskInfo->Identify (DiskInfo, IdentifyData, &IdentifyDataSize);
            if (EFI_ERROR(Status)) continue;
            
            gBS->CopyMem (&DiskStructure[Index].IdentifyData[0], &((NVME_IDENTIFY_NAMESPACE_DATA*)IdentifyData)->Eui64, sizeof(UINT64));
           
            if (IdentifyData) {            
                gBS->FreePool (IdentifyData);
                IdentifyData = NULL;
            }
        }
        //            
        // If GUID is AHCI, then gather AHCI disk information into checksum.
        //
        else if (CompareGuid (&DiskInfo->Interface, &gEfiDiskInfoAhciInterfaceGuid)) {
            //
            // 1.Gather channel number
            //
            Status = DiskInfo->WhichIde (DiskInfo, &IdeChannel, &IdeDevice);
            if (!EFI_ERROR(Status)) 
                DiskStructure[Index].PortNumber = IdeChannel;
            //
            // 2.Gather serial number 
            //
            // According to DiskInfoIdentify in AhciBus.c, the identify data uses IDENTIFY_DATA as data structure.
            IdentifyDataSize = sizeof(IDENTIFY_DATA);
            gBS->AllocatePool (EfiBootServicesData, 
                               IdentifyDataSize, 
                               (VOID**)&IdentifyData);
           
            gBS->SetMem (IdentifyData, sizeof(IDENTIFY_DATA), 0);

            Status = DiskInfo->Identify (DiskInfo, IdentifyData, &IdentifyDataSize);
            if (EFI_ERROR(Status)) continue;
           
            gBS->CopyMem (&DiskStructure[Index].IdentifyData, &((IDENTIFY_DATA*)IdentifyData)->Serial_Number_10, ATA_SERIAL_NUMBER_LENGTH);  

            if (IdentifyData) {            
                gBS->FreePool (IdentifyData);
                IdentifyData = NULL;
            }
        }
    }   
    //
    // Calculate CRC 32
    //
    Status = gBS->CalculateCrc32 (&DiskStructure[0].PortNumber, (UINT16)(NumberOfDiskHandles * sizeof(AMI_HARDWARE_SIGNATURE_DISK_CONFIG_INFO)), &HardwareDiskData->DiskInfoChecksum);
    if (EFI_ERROR (Status)) {   
        DEBUG((DEBUG_INFO, "ERROR: CRC32 calculation failed :%r\n", Status));   
    } 

    gBS->FreePool (DiskStructure);
    gBS->FreePool (HandleBuffer);
        
    return EFI_SUCCESS;
}
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

