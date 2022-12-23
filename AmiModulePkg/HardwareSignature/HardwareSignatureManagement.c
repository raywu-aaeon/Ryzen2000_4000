//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/**@file HardwareSignatureManagement.c
 
  This file will install the HardwareChange protocol. The hardware signature data of the FACS table will be 
  updated when the ReadyToBoot event is signaled.
*/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Uefi.h>
#include <IndustryStandard/Acpi20.h>
#include <Protocol/AcpiSupport.h>
#include <HardwareChangeProtocol.h>
#include <TimeStamp.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <HardwareSignatureLib.h>
#include <Guid/Acpi.h>

//---------------------------------------------------------------------------
// Global Variable declarations
//---------------------------------------------------------------------------

STATIC EFI_GUID  gHardwareChangeProtocolGuid   = AMI_HARDWARE_CHANGE_PROTOCOL_GUID;
STATIC EFI_GUID  gHardwareConfigDataGuid       = AMI_HARDWARE_CONFIG_DATA_GUID;
STATIC EFI_GUID  gSetupUpdateCountGuid         = AMI_SETUP_UPDATE_COUNT_GUID;
//
//Record the hardware change flag if there are some hardware 
//configurations changed. 
//
STATIC UINT32 gHardwareConfigChangeFlag = 0;
//
//Record the current hardware configuration data.
//
STATIC AMI_HARDWARE_SIGNATURE_CONFIG_DATA gCurHardwareConfigData;

//
//Record called times if other module called this protocol
//
STATIC UINT32 gExternalFunCallCount = 0;


AMI_HARDWARE_SIGNATURE_PROTOCOL gHardwareChangeProtocol = 
{
    AmiHardwareSignatureSetHardwareConfigData,
    AmiHardwareSignatureGetHardwareConfigDataFromNvram,
    AmiSignalHardwareSignatureChange
};

/**
 * Entry point of HardwareSignature.
 * 
 * This function is a driver entry point that installs a protocol to set the  
 * hardware configurations. These hardware configurations will determine the  
 * Hardware Signature of the FACS table.  
 * 
 * This function also creates ReadyToBoot event to update the hardware 
 * signature of the FACS table. 
 * 
 * @param[in]    ImageHandle     Image handle
 * @param[in]    SystemTable     Pointer to system table
 * 
 * @retval       EFI_SUCCESS     Function executed successfully.
 * @retval       Other           Function executed unsuccessfully.
**/

EFI_STATUS 
EFIAPI 
HardwareSignatureEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{

    EFI_STATUS          Status;
    EFI_EVENT           ReadyToBootEvent;
    EFI_HANDLE          HardwareChangeHandle = NULL;
    VOID                *Registration;
    //
    // clear the global variable first
    //
    gBS->SetMem(&gCurHardwareConfigData, sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA), 0);

    Status = gBS->InstallProtocolInterface (&HardwareChangeHandle,
                                            &gHardwareChangeProtocolGuid,
                                            EFI_NATIVE_INTERFACE,
                                            &gHardwareChangeProtocol);

    if (EFI_ERROR(Status)) 
        return Status;
    //
    // Register UpdateHardwareSignatureData function for Updating Hardware Signature Data
    //
    Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL,
                               TPL_CALLBACK, 
                              (EFI_EVENT_NOTIFY) UpdateHardwareSignatureData, 
                               NULL, 
                               &ReadyToBootEvent);
    if (!EFI_ERROR(Status)) {
        gBS->RegisterProtocolNotify (&gAmiTseEventBeforeBootGuid, 
                                     ReadyToBootEvent, 
                                     &Registration);
    }   
    //
    // Register UpdateHardwareSignatureData function for Updating Hardware Signature Data
    //
    Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                (EFI_EVENT_NOTIFY) UpdateHardwareSignatureData,
                                NULL,
                                &ReadyToBootEvent);
    if (!EFI_ERROR(Status)) {
        gBS->RegisterProtocolNotify (&gAmiLegacyBootProtocolGuid, 
                                     ReadyToBootEvent, 
                                     &Registration);
    }
    
    return Status;
}

/**
 * AMI Hardware Signature Set hardware configuration data.
 * This function sets the hardware configuration data for each configuration type.
 * 
 * @param[in]    ConfigType              The hardware configuration type 
 * @param[in]    BufferSize              Size of buffer for recording the configuration data.
 * @param[in]    Buffer                  Buffer for recording the configuration data.
 * 
 * @retval       EFI_SUCCESS             Set the hardware configuration data successfully.
 * @retval       EFI_INVALID_PARAMETER   ConfigType is incorrect. Buffer is NULL and BufferSize is not zero.
**/

EFI_STATUS 
EFIAPI
AmiHardwareSignatureSetHardwareConfigData (
    IN AMI_HARDWARE_SIGNATURE_CONFIG_TYPE ConfigType, 
    IN UINTN          BufferSize,
    IN VOID           *Buffer )
{
    EFI_STATUS Status;

    if ((Buffer == NULL && BufferSize != 0) || ConfigType >= AMI_HARDWARE_SIGNATURE_MAX_TYPE_NUMBER)
        return EFI_INVALID_PARAMETER;
  
    switch(ConfigType)
    {
#if HARDWARE_SIGNATURE_PS2_CHANGE  
        case AMI_HARDWARE_SIGNATURE_PS2_CONFIG:
            Status = DetectAndSetPs2Config(BufferSize, Buffer);
            break;
#endif          
        case AMI_HARDWARE_SIGNATURE_MEMORY_SIZE_CONFIG:
            Status = DetectAndSetMemorySizeConfig(BufferSize, Buffer);
            break;
          
        case AMI_HARDWARE_SIGNATURE_MEMORY_MAP_CONFIG:
            Status = DetectAndSetMemoryMapConfig(BufferSize, Buffer);
            break;
          
        case AMI_HARDWARE_SIGNATURE_PCI_CONFIG:
            Status = DetectAndSetPciConfig(BufferSize, Buffer);
            break;
#if HARDWARE_SIGNATURE_USB_CHANGE          
        case AMI_HARDWARE_SIGNATURE_USB_CONFIG:
            Status = DetectAndSetUsbConfig(BufferSize, Buffer);
            break;
#endif
        case AMI_HARDWARE_SIGNATURE_VIDEO_CONFIG:
            Status = DetectAndSetVideoConfig(BufferSize, Buffer);
            break;
        case AMI_HARDWARE_SIGNATURE_DISK_CONFIG:
            Status = DetectAndSetDiskConfig(BufferSize, Buffer);
            break;   
        default:
            Status = EFI_INVALID_PARAMETER;
            break;
    }
      
    return Status;
}

/**
 * Get the hardware configuration data.
 * This function gets the hardware configuration data from NVRAM.
 * 
 * @param[in,out]    HardwareConfigData      The hardware configuration data of NVRAM.
 * 
 * @retval           EFI_SUCCESS              Get the hardware configuration data successfully.
 * @retval           EFI_INVALID_PARAMETER    HardwareConfigData is NULL.
 * @retval           EFI_NOT_FOUND            It is the first boot. There is no Hardware configuration data.
**/

EFI_STATUS 
EFIAPI
AmiHardwareSignatureGetHardwareConfigDataFromNvram (
    IN OUT AMI_HARDWARE_SIGNATURE_CONFIG_DATA *HardwareConfigData )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA);

    if (HardwareConfigData == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = gRT->GetVariable (HARDWARE_CONFIG_DATA_VARIABLE, 
                               &gHardwareConfigDataGuid,
                               NULL, 
                               &VarSize, 
                               HardwareConfigData); 
    if (EFI_ERROR(Status))
    {
        gBS->SetMem (HardwareConfigData, sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA), 0);
    }
    return Status;    
}

/**
 * Provide a protocol for other modules setting return value. 
 * This function will update the global variable 'gExternalFunCallCount' and
 * save the checksum value in the global variable
 * gCurHardwareConfigData(ReturnChecksum array).
 * 
 * The global variable gExternalFunCallCount will be increased.
 * 
 * @param[in]   ReturnChecksum              The checksum value that external function gives.
 * @retval      EFI_SUCCESS                 Record the checksum which external function gives successfully
 * @retval      EFI_OUT_OF_RESOURCES        The global variable 'gExternalFunCallCount' is larger than 
 *                                          and equal to AMI_HARDWARE_SIGNATURE_PROTOCOL_MAX_CALL_TIMES.
**/

EFI_STATUS
EFIAPI
AmiSignalHardwareSignatureChange ( 
    IN UINT32 ReturnChecksum )
{

    if (gExternalFunCallCount >= AMI_HARDWARE_SIGNATURE_PROTOCOL_MAX_CALL_TIMES)
        return EFI_OUT_OF_RESOURCES;
    else
    {
        gCurHardwareConfigData.ReturnChecksum[gExternalFunCallCount] = ReturnChecksum;   
        gExternalFunCallCount++;
    }   
    return EFI_SUCCESS;
}

#if HARDWARE_SIGNATURE_PS2_CHANGE
/**
 * 
 * Set Ps2Keyboard state
 * 
 * This function sets the PS2 Keyboard configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]  Present      If value is TRUE, PS2 Keyboard is present. 
 *                          If value is FALSE, PS2 Keyboard is not present.   
 * @retval         None.
**/

VOID 
SetPs2KeyboardState (
    IN BOOLEAN Present )
{
    if (Present)
    {    
        gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_PS2_KEYBOARD_CHANGE_FLAG; 

        gCurHardwareConfigData.BitPs2Keyboard = TRUE;
    }
    else 
    {   
        gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_PS2_KEYBOARD_CHANGE_FLAG; 
        //no PS2 Keyboard  
        gCurHardwareConfigData.BitPs2Keyboard = FALSE;
    }    
    return;
}

/**
 * 
 * Set Ps2Mouse state
 * 
 * This function sets the PS2 Mouse configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]    Present        If value is TRUE, PS2 Mouse is present. 
 *                              If value is FALSE, PS2 Mouse is not present. 
 *                                
 * @retval       None.
**/

VOID 
SetPs2MouseState (
    IN BOOLEAN Present )
{
    if (Present)
    {    
        gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_PS2_MOUSE_CHANGE_FLAG; 
        gCurHardwareConfigData.BitPs2Mouse = TRUE;
    }
    else 
    {
        gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_PS2_MOUSE_CHANGE_FLAG;     
        //no PS2 Mouse
        gCurHardwareConfigData.BitPs2Mouse = FALSE;
    }
    return;
}
#endif

/**
 * Set memory size configuration state.
 * 
 * This function sets the memory size configurations to global variable 
 * gCurHardwareConfigData.
 * 
 * @param[in]    MemorySizeMb                Current memory size (MB)         
 * @param[in]    BufferSize                  Size of buffer for recording the memory size.
 * 
 * @retval       EFI_SUCCESS                 Memory size configuration. sets successfully
 * @retval       EFI_INVALID_PARAMETER       Buffer size is too small to record the memory size.
**/

EFI_STATUS 
SetMemorySizeConfigState (
    IN UINT32 MemorySizeMb, 
    IN UINTN  BufferSize )
{

    if (BufferSize < sizeof(UINT32)) {
        return EFI_INVALID_PARAMETER;
    }
    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_MEMORY_SIZE_CHANGE_FLAG; 

    gCurHardwareConfigData.MemMapData.MemoryMbSize = MemorySizeMb;
        
    return EFI_SUCCESS;
}

/**
 * Set memory map configuration state.
 * 
 * This function sets the memory map configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]    MemMapConfig   Current memory map data  
 * @retval       None.
**/

VOID 
SetMemoryMapConfigState (
    IN AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA MemMapConfig )
{    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_MEMORY_MAP_CHANGE_FLAG;        
    gCurHardwareConfigData.MemMapData.MemMapCheckSum = MemMapConfig.MemMapCheckSum;
    
    return;
}

/**
 * 
 * Set PCI configuration state.
 * 
 * This function sets the PCI configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]    PciConfig   Current PCI data                        
 * @retval       None. 
**/

VOID 
SetPciConfigState (
    IN AMI_HARDWARE_SIGNATURE_PCI_DATA PciConfig )
{    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_PCI_CHANGE_FLAG; 
       
    gCurHardwareConfigData.PciData.PciInfoChecksum = PciConfig.PciInfoChecksum;
    
    return;
}

#if HARDWARE_SIGNATURE_USB_CHANGE
/**
  Set USB configuration state.
  
  This function sets the USB configurations to global variable 
  gCurHardwareConfigData.

  @param[in]    UsbConfig   Current USB data                        
  
  @retval       None.
  
**/

VOID 
SetUsbConfigState (
    IN AMI_HARDWARE_SIGNATURE_USB_DATA UsbConfig )
{    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_USB_CHANGE_FLAG; 
       
    gCurHardwareConfigData.UsbData.UsbNum = UsbConfig.UsbNum;
    gCurHardwareConfigData.UsbData.VidPidChecksum = UsbConfig.VidPidChecksum;
    gCurHardwareConfigData.UsbData.PortNumInterfaceNumChecksum = UsbConfig.PortNumInterfaceNumChecksum;
         
    return;
}
#endif

/**
 * Set Video configuration state.
 * This function sets the Video configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]    VideoConfig   Current Video data                        
 * @retval       None. 
**/

VOID 
SetVideoConfigState (
    IN AMI_HARDWARE_SIGNATURE_VIDEO_DATA VideoConfig )
{    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_VIDEO_CHANGE_FLAG; 
       
    gCurHardwareConfigData.VideoData.EdidCheckNum = VideoConfig.EdidCheckNum;
    gCurHardwareConfigData.VideoData.ResolutionChecksum = VideoConfig.ResolutionChecksum;
           
    return;
}

/**
 * Set disk configuration state.
 * This function sets the Disk configurations to global variable gCurHardwareConfigData.
 * 
 * @param[in]    DiskConfig   Current Disk data                        
 * @retval       None. 
**/

VOID 
SetDiskConfigState (
    IN AMI_HARDWARE_SIGNATURE_DISK_DATA DiskConfig )
{    
    gHardwareConfigChangeFlag |= AMI_HARDWARE_SIGNATURE_DISK_CHANGE_FLAG; 
       
    gCurHardwareConfigData.DiskData.DiskInfoChecksum = DiskConfig.DiskInfoChecksum;
    
    return;
}

#if HARDWARE_SIGNATURE_PS2_CHANGE
/**
 * Detect and set Ps2 Keyboard/Mouse configuration.
 * 
 * This function detects the PS2 KB/Mouse configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected data to gCurHardwareConfigData. Otherwise,  it will compare the 
 * input data and the  detected data to determine the PS2 KB/Mouse is present or not.
 * 
 * @param[in]  BufferSize   Size of buffer for recording the PS2 KB/Mouse configuration. 
 *                          It should be one byte. 
 *                          
 * @param[in]  Buffer       Buffer for recording the PS2 KB/Mouse configuration. 
 *                          If *Buffer is 1, it means the PS2 KB/Mouse is present. 
 *                          If *Buffer is 0, the PS2 KB/Mouse is not present                                  
 * @retval  EFI_SUCCESS     PS2 KB/Mouse configuration is set successfully.
 * @retval  EFI_NOT_FOUND   Detect PS2 KB/Mouse configuration failed.
 * @retval  Other           Set PS2 KB/Mouse configuration failed.
**/
EFI_STATUS 
DetectAndSetPs2Config (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    AMI_HARDWARE_SIGNATURE_PS2_DATA       DetectPs2Present;
    BOOLEAN             BitPs2KeyboardPresent = FALSE;
    BOOLEAN             BitPs2MousePresent = FALSE;

	DetectPs2Present.Keyboard = FALSE;
    DetectPs2Present.Mouse = FALSE;

    Status = DetectPs2KeyboardMouseState (&DetectPs2Present);
    
    if (EFI_ERROR(Status)) 
        return Status;

    if (BufferSize == 0 && Buffer == NULL)
    {
        BitPs2KeyboardPresent = DetectPs2Present.Keyboard;
        BitPs2MousePresent    = DetectPs2Present.Mouse;
    }
    else
    {     
        /*PS2 Keyboard*/
		if ((*(BOOLEAN *)Buffer) == 0 && DetectPs2Present.Keyboard == 0)
            BitPs2KeyboardPresent = FALSE;        
        else
            BitPs2KeyboardPresent = TRUE;
        
		/*PS2 Mouse*/
        if ((*(BOOLEAN *)Buffer) == 0 && DetectPs2Present.Mouse == 0)
            BitPs2MousePresent = FALSE;        
        else
            BitPs2MousePresent = TRUE;
    }

    SetPs2KeyboardState (BitPs2KeyboardPresent);
    SetPs2MouseState (BitPs2MousePresent);

    return Status;
}

#endif

/**
 * Detect and set MemorySize configuration.
 * This function detects the memory size configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected size(DetectMemSize) to gCurHardwareConfigData. Otherwise, it  
 * will compare the input data(Buffer) and the detected size(DetectMemSize) 
 * to determine which one should be saved. 
 * 
 * @param[in]    BufferSize      Size of buffer for recording the memory size                                  
 * @param[in]    Buffer          Buffer for recording the memory size.                                
 * 
 * @retval       EFI_SUCCESS     Memory size configuration is set successfully.
 * @retval       Other           Detect the memory size failed or set the memory size 
 * configuration failed.
**/

EFI_STATUS 
DetectAndSetMemorySizeConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINT32              CurrentMemSize= 0;
    UINTN               TempSize = 0;
    UINT32              DetectMemSize = 0;
    BOOLEAN             BitDifferent = FALSE;
    AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA  DetectMemMapConfigData;

    gBS->SetMem (&DetectMemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA), 0);

    Status = GetMemMapData (&DetectMemMapConfigData);

    if (EFI_ERROR(Status)) 
        return Status;

    DetectMemSize = DetectMemMapConfigData.MemoryMbSize;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        CurrentMemSize = DetectMemSize;
        TempSize = sizeof (CurrentMemSize);
    }
    else
    {     
        BitDifferent = IsDifferentMemorySize (DetectMemSize, (*(UINT32 *)Buffer));
      
        if (BitDifferent)
            CurrentMemSize = DetectMemSize; 
        else
            CurrentMemSize = (*(UINT32 *)Buffer);

        TempSize = BufferSize;
    }

    Status = SetMemorySizeConfigState (CurrentMemSize, TempSize);

    return Status;
    
}

/**
 * Detect and set MemoryMap configuration.
 * 
 * This function detects the memory map configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected memory map data to gCurHardwareConfigData. Otherwise, it will 
 * save the input data(Buffer).
 * 
 * @param[in]    BufferSize                  Size of buffer for recording the memory map data.                                  
 * @param[in]    Buffer                      Buffer for recording the memory map data.                                
 * 
 * @retval       EFI_SUCCESS                 Memory map configuration is set successfully.
 * @retval       EFI_INVALID_PARAMETER       BufferSize is incorrect.
 * @retval       Other                       Get memory map data failed.
**/

EFI_STATUS 
DetectAndSetMemoryMapConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               TempSize = 0;
    AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA  DetectMemMapConfigData;
    AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA  CurMemMapConfigData;
    
    gBS->SetMem (&DetectMemMapConfigData, sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA), 0);

    Status = GetMemMapData (&DetectMemMapConfigData);
    if (EFI_ERROR(Status)) 
        return Status;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        TempSize = sizeof(DetectMemMapConfigData.MemMapCheckSum);       
        gBS->CopyMem (&CurMemMapConfigData, &DetectMemMapConfigData, TempSize);
    }
    else
    {     
        TempSize = sizeof(DetectMemMapConfigData.MemMapCheckSum);
        if (BufferSize < TempSize || BufferSize > sizeof(AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA))
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        TempSize = BufferSize;
        gBS->CopyMem (&CurMemMapConfigData, Buffer, TempSize);
    }

    SetMemoryMapConfigState (CurMemMapConfigData);

    return Status;
    
}

/**
 * Detect and set PCI configuration.
 * 
 * This function detects the PCI configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected PCI data to gCurHardwareConfigData. Otherwise, it will save 
 * the input data (Buffer). 
 * 
 * @param[in]    BufferSize                  Size of buffer for recording the PCI data.                                  
 * @param[in]    Buffer                      Buffer for recording the PCI data.                                
 * 
 * @retval       EFI_SUCCESS                 PCI configuration is set successfully.
 * @retval       EFI_INVALID_PARAMETER       BufferSize is incorrect.
 * @retval       Other                       Get PCI data failed.
**/

EFI_STATUS 
DetectAndSetPciConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS                          Status;
    UINTN                               TempSize = 0;
    AMI_HARDWARE_SIGNATURE_PCI_DATA     DetectPciConfigData;
    AMI_HARDWARE_SIGNATURE_PCI_DATA     CurrentPciConfigData;

    Status = GetPciDeviceData (&DetectPciConfigData);
    if (EFI_ERROR(Status)) 
        return Status;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_PCI_DATA);
        gBS->CopyMem (&CurrentPciConfigData, &DetectPciConfigData, TempSize);
    }
    else
    {     
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_PCI_DATA);
        if (BufferSize != TempSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        gBS->CopyMem (&CurrentPciConfigData, Buffer, TempSize);
    }

    SetPciConfigState (CurrentPciConfigData);

    return Status;
    
}

#if HARDWARE_SIGNATURE_USB_CHANGE
/**
 * 
 * Detect and set USB configuration.
 * 
 * This function detects the USB configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected USB data to gCurHardwareConfigData. Otherwise, it will save 
 * the input data (Buffer). 
 * 
 * @param[in]    BufferSize              Size of buffer for recording the USB data.                                  
 * @param[in]    Buffer                  Buffer for recording the USB data.                                
 * 
 * @retval       EFI_SUCCESS             USB configuration is set successfully.
 * @retval       EFI_INVALID_PARAMETER   BufferSize is incorrect.
 * @retval       Other                   Get USB data failed.
**/

EFI_STATUS 
DetectAndSetUsbConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               TempSize = 0;
    AMI_HARDWARE_SIGNATURE_USB_DATA         DetectUsbConfigData;
    AMI_HARDWARE_SIGNATURE_USB_DATA         CurrentUsbConfigData;

    Status = GetUsbDeviceData (&DetectUsbConfigData);
      
    if (EFI_ERROR(Status)) 
        return Status;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_USB_DATA);
        gBS->CopyMem (&CurrentUsbConfigData, &DetectUsbConfigData, TempSize);
    }
    else
    {     
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_USB_DATA);
        if(BufferSize != TempSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        gBS->CopyMem (&CurrentUsbConfigData, Buffer, TempSize);
    }

    SetUsbConfigState (CurrentUsbConfigData);

    return Status;
    
}

#endif

/**
 * Detect and set Video configuration.
 * 
 * This function detects the Video configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected Video data to gCurHardwareConfigData. Otherwise, it will save 
 * the input data (Buffer). 
 * 
 * @param[in]    BufferSize                  Size of buffer for recording the Video data.                                  
 * @param[in]    Buffer                      Buffer for recording the Video data.                                
 * 
 * @retval       EFI_SUCCESS                 Video configuration is set successfully.
 * @retval       EFI_INVALID_PARAMETER       BufferSize is incorrect.
 * @retval       Other                       Get Video data failed.
**/

EFI_STATUS 
DetectAndSetVideoConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               TempSize = 0;
    AMI_HARDWARE_SIGNATURE_VIDEO_DATA       DetectVideoData;
    AMI_HARDWARE_SIGNATURE_VIDEO_DATA       CurrentVideoData;  
    
    Status = GetVideoData (&DetectVideoData);
      
    if (EFI_ERROR(Status)) 
        return Status;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_VIDEO_DATA);
        gBS->CopyMem (&CurrentVideoData, &DetectVideoData, TempSize);
    }
    else
    {     
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_VIDEO_DATA);
        if (BufferSize != TempSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        gBS->CopyMem (&CurrentVideoData, Buffer, TempSize);
    }

    SetVideoConfigState (CurrentVideoData);

    return Status;
    
}

/**
 * 
 * Detect and set Disk configuration.
 * This function detects the Disk configurations and sets this  
 * configuration to global variable gCurHardwareConfigData.
 * 
 * If Buffer is NULL and BufferSize is 0, the function will save the 
 * detected Disk data to gCurHardwareConfigData. Otherwise, it will save 
 * the input data (Buffer). 
 * 
 * @param[in]    BufferSize                  Size of buffer for recording the Disk data.                                  
 * @param[in]    Buffer                      Buffer for recording the Disk data.                                
 * 
 * @retval       EFI_SUCCESS                 Disk configuration is set successfully.
 * @retval       EFI_INVALID_PARAMETER       BufferSize is incorrect.
 * @retval       Other                       Get Disk data failed.
**/

EFI_STATUS 
DetectAndSetDiskConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer )
{
    EFI_STATUS          Status;
    UINTN               TempSize = 0;
    AMI_HARDWARE_SIGNATURE_DISK_DATA        DetectDiskData;
    AMI_HARDWARE_SIGNATURE_DISK_DATA        CurrentDiskData;  

    Status = GetDiskInfoData (&DetectDiskData);
    if (EFI_ERROR(Status))
        return Status;
      
    if (BufferSize == 0 && Buffer == NULL)
    {
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_DISK_DATA);
        gBS->CopyMem (&CurrentDiskData, &DetectDiskData, TempSize);
    }
    else
    {     
        TempSize = sizeof(AMI_HARDWARE_SIGNATURE_DISK_DATA);
        if (BufferSize != TempSize )
        {
            Status = EFI_INVALID_PARAMETER;
            return Status;
        }
        
        gBS->CopyMem (&CurrentDiskData, Buffer, TempSize);
    }

    SetDiskConfigState (CurrentDiskData);

    return Status;
    
}

/**
 * Save Hardware configuration data to NVRAM.
 * This function writes the hardware configurations to NVRAM.
 * 
 * @param[in]    HardwareConfigData      current HW configuration data                        
 * 
 * @retval       EFI_SUCCESS             HW configuration is written successfully
 * @retval       EFI_INVALID_PARAMETER   HardwareConfigData is invalid
**/

EFI_STATUS 
SetHardwareConfigDataToNvram (
    IN AMI_HARDWARE_SIGNATURE_CONFIG_DATA *HardwareConfigData )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA);

    if (HardwareConfigData == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = gRT->SetVariable (HARDWARE_CONFIG_DATA_VARIABLE,
                                &gHardwareConfigDataGuid,
                                EFI_VARIABLE_NON_VOLATILE |
                                EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                EFI_VARIABLE_RUNTIME_ACCESS,
                                VarSize, 
                                HardwareConfigData); 
    return Status;    
}

/**

  This function scan ACPI table in XSDT.

  @param Xsdt      ACPI XSDT
  @param Signature ACPI table signature

  @return ACPI table

**/

VOID *
HardwareSignatureScanTableInXSDT (
    IN EFI_ACPI_DESCRIPTION_HEADER    *Xsdt,
    IN UINT32                         Signature )
{
    UINTN                          Index;
    UINT32                         EntryCount;
    UINT64                         EntryPointer;
    UINTN                          BasePointer ;
    EFI_ACPI_DESCRIPTION_HEADER    *Table;

    if (Xsdt == NULL) 
        return NULL;
    
    EntryCount = (Xsdt->Length - sizeof (EFI_ACPI_DESCRIPTION_HEADER)) / sizeof(UINT64);
    BasePointer = (UINTN)(Xsdt + 1);
    
    for (Index = 0; Index < EntryCount; Index ++) {
        CopyMem (&EntryPointer, (VOID *)(BasePointer + Index * sizeof(UINT64)), sizeof(UINT64));
        Table = (EFI_ACPI_DESCRIPTION_HEADER *)((UINTN)(EntryPointer));

        if (Table == NULL)
            continue;
        
        if (Table->Signature == Signature) 
            return Table;
        
    }
    return NULL;
}

/**

  This function scan ACPI table in RSDT.

  @param Rsdt      ACPI RSDT
  @param Signature ACPI table signature

  @return ACPI table

**/

VOID *
HardwareSignatureScanTableInRSDT (
    IN EFI_ACPI_DESCRIPTION_HEADER    *Rsdt,
    IN UINT32                         Signature
  )
{
    UINTN                              Index;
    UINT32                             EntryCount;
    UINT32                             *EntryPointer;
    EFI_ACPI_DESCRIPTION_HEADER        *Table;

    if (Rsdt == NULL) 
        return NULL;
 
    EntryCount = (Rsdt->Length - sizeof (EFI_ACPI_DESCRIPTION_HEADER)) / sizeof(UINT32);
    EntryPointer = (UINT32 *)(Rsdt + 1);
    for (Index = 0; Index < EntryCount; Index ++, EntryPointer ++) {
      Table = (EFI_ACPI_DESCRIPTION_HEADER *)((UINTN)(*EntryPointer));

      if (Table == NULL)
          continue;
      
      if (Table->Signature == Signature) 
          return Table;
      
    }
  
    return NULL;
}

/**
  To find Facs in FADT.

  @param Fadt   FADT table pointer
  
  @return  Facs table pointer.
**/

EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE  *
HardwareSignatureFindAcpiFacsFromFadt (
  IN EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE     *Fadt )
{
  EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE  *Facs;
  UINT64                                        Data64;

  if (Fadt == NULL) {
    return NULL;
  }

  if (Fadt->Header.Revision < EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_REVISION) {
    Facs = (EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *)(UINTN)Fadt->FirmwareCtrl;

  } else {
    if (Fadt->FirmwareCtrl != 0) {
      Facs = (EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *)(UINTN)Fadt->FirmwareCtrl;
    } else {
      CopyMem (&Data64, &Fadt->XFirmwareCtrl, sizeof(UINT64));
      Facs = (EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *)(UINTN)Data64;
    }
  }
  return Facs;
}

/**
 * To find FACS in ACPI Tables.
 * 
 * To find Firmware ACPI control strutcure in ACPI Tables since the S3 waking vector is stored 
 * in the table.
 * 
 * @param AcpiTableGuid   The guid used to find ACPI table in UEFI ConfigurationTable.
 * @return  Facs table pointer.
**/

EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE  *
HardwareSignatureFindAcpiFacsTableByAcpiGuid (
    IN EFI_GUID  *AcpiTableGuid )
{
    EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;
    EFI_ACPI_DESCRIPTION_HEADER                   *Rsdt;
    EFI_ACPI_DESCRIPTION_HEADER                   *Xsdt;
    EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE     *Fadt;
    EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE  *Facs;
    UINTN                                         Index;
    Rsdp  = NULL;
    
    //
    // Find ACPI table RSD_PTR(Root System Description Pointer) from system table
    //
    for (Index = 0; Index < gST->NumberOfTableEntries; Index++) {
        if (CompareGuid (&(gST->ConfigurationTable[Index].VendorGuid), AcpiTableGuid)) {
            //
            // A match was found.
            //
            Rsdp = gST->ConfigurationTable[Index].VendorTable;
            break;
        }
    }
    if (Rsdp == NULL) {
        return NULL;
    }
    //
    // Search XSDT (Extended System Description Table)
    //
    if (Rsdp->Revision >= EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION) {
        Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN) Rsdp->XsdtAddress;
        Fadt = HardwareSignatureScanTableInXSDT (Xsdt, EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE);
        if (Fadt != NULL) {
            Facs = HardwareSignatureFindAcpiFacsFromFadt (Fadt);
            if (Facs != NULL) {
                return Facs;
            }
        }
    }
    //
    // Search RSDT
    //
    Rsdt = (EFI_ACPI_DESCRIPTION_HEADER *)(UINTN) Rsdp->RsdtAddress;
    Fadt = HardwareSignatureScanTableInRSDT (Rsdt, EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE);
    if (Fadt != NULL) {
        Facs = HardwareSignatureFindAcpiFacsFromFadt (Fadt);
        if (Facs != NULL) {
            return Facs;
        }
    }

    return NULL;
}

/**
  To find Facs in Acpi tables.
 
  To find Firmware ACPI control strutcure in Acpi Tables since the S3 waking vector is stored 
  in the table.
  
  @return  Facs table pointer.
**/

EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE  *
HardwareSignatureFindAcpiFacsTable (
  VOID )
{
  EFI_ACPI_2_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *Facs;

  Facs = HardwareSignatureFindAcpiFacsTableByAcpiGuid (&gEfiAcpi20TableGuid);
  if (Facs != NULL) {
    return Facs;
  }

  return HardwareSignatureFindAcpiFacsTableByAcpiGuid (&gEfiAcpi10TableGuid);
}

/**
 * SwapChecksum
 * 
 * This function swaps the two input data.
 * 
 * @param[in,out]    LChecksumPosition   Left checksum position
 * @param[in,out]    RChecksumPosition   Right checksum position
 * 
 * @retval           None.
**/

VOID 
SwapChecksum (
    IN OUT UINT32 *LChecksumPosition,
    IN OUT UINT32 *RChecksumPosition )
{
    UINT32 Temp = *LChecksumPosition;
    
    *LChecksumPosition  = *RChecksumPosition;
    *RChecksumPosition  = Temp;
    
    return;
}

/**
 * 
 * QuickSort
 * 
 * This function sorts the external checksum in ascending order.
 * The sorted data will be saved in ChecksumData.
 * 
 * @param[in,out]    ChecksumData            all checksum data
 * @param[in]        LChecksumPosition       the first position of checksum data 
 * @param[in]        RChecksumPosition       the last position of checksum data 
 * 
 * @retval  None.
**/

VOID 
QuickSort(
    IN OUT UINT32 *ChecksumData, 
    IN     UINT32 LChecksumPosition, 
    IN     UINT32 RChecksumPosition )
{
    UINT32 Pivot; 
    UINT32 LeftIncPosition;
    UINT32 RightDecPostion;

    if (LChecksumPosition >= RChecksumPosition) { return; }

    Pivot = ChecksumData [LChecksumPosition];

    LeftIncPosition = LChecksumPosition + 1;
    RightDecPostion = RChecksumPosition;

    while (1)
    {
        while (LeftIncPosition <= RChecksumPosition)
        {
            if (ChecksumData[LeftIncPosition] > Pivot)
                break;
            LeftIncPosition = LeftIncPosition + 1;
        }

        while (RightDecPostion > LChecksumPosition)
        {
            if (ChecksumData[RightDecPostion] < Pivot)
                break;
            RightDecPostion = RightDecPostion - 1;
        }

        if (LeftIncPosition > RightDecPostion)
            break;

        SwapChecksum (&ChecksumData[LeftIncPosition], &ChecksumData[RightDecPostion]);
    }

    SwapChecksum (&ChecksumData[LChecksumPosition], &ChecksumData[RightDecPostion]);

    QuickSort (ChecksumData, LChecksumPosition, RightDecPostion - 1);
    QuickSort (ChecksumData, RightDecPostion + 1, RChecksumPosition);
    
    return;
}

/**
 * Update HardwareSignature Data\
 * This function will be called when ReadyToBoot event will be signaled and 
 * will update the hardware signature data of the FACS table.
 * 
 * This function also writes the hardware configurations to NVRAM.   
 * @param[in]    Event           signaled event
 * @param[in]    Context         calling context
 * 
 * @retval       EFI_SUCCESS     Hardware Signature was updated successfully.
 * @retval       EFI_NOT_READY   GetFacsTable() can't find the EfiAcpiSupportGuid protocol.
 * @retval       EFI_NOT_FOUND   GetFacsTable() can't find the FADT table. 
 * @retval       Other           Hardware Signature could't be updated.
**/

EFI_STATUS 
EFIAPI
UpdateHardwareSignatureData (
    IN EFI_EVENT Event, 
    IN VOID      *Context )
{   
    EFI_STATUS                     Status;
    UINTN                          VarSize = sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA);
    UINT32                         FacsSignature = 0;
    UINT32                         SetupCount = 0;
    UINTN                          NumberOfExternelFunCall;
    EFI_TIME                       BiosBuildTime = { FOUR_DIGIT_YEAR_INT, 
                                                     TWO_DIGIT_MONTH_INT, 
                                                     TWO_DIGIT_DAY_INT, 
                                                     TWO_DIGIT_HOUR_INT, 
                                                     TWO_DIGIT_MINUTE_INT, 
                                                     TWO_DIGIT_SECOND_INT, 
                                                     0,0,0,0,0};
    EFI_ACPI_4_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *Facs;

    
#if HARDWARE_SIGNATURE_PS2_CHANGE  
    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_PS2_CONFIG, 0, NULL);
#endif
    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_MEMORY_SIZE_CONFIG, 0, NULL);

    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_MEMORY_MAP_CONFIG, 0, NULL);

    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_PCI_CONFIG, 0, NULL);
        
#if HARDWARE_SIGNATURE_USB_CHANGE
    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_USB_CONFIG, 0, NULL);
#endif
    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_DISK_CONFIG, 0, NULL);

    AmiHardwareSignatureSetHardwareConfigData (AMI_HARDWARE_SIGNATURE_VIDEO_CONFIG,0, NULL);
    
    DEBUG((DEBUG_INFO, "[-------Hardware Signature Debug Message----START------]\n"));   
    
    gCurHardwareConfigData.BiosBuildYear    = BiosBuildTime.Year;
    gCurHardwareConfigData.BiosBuildMonth   = BiosBuildTime.Month;
    gCurHardwareConfigData.BiosBuildDay     = BiosBuildTime.Day;
    gCurHardwareConfigData.BiosBuildHour    = BiosBuildTime.Hour;
    gCurHardwareConfigData.BiosBuildMinute  = BiosBuildTime.Minute;
    gCurHardwareConfigData.BiosBuildSecond  = BiosBuildTime.Second;
    
    DEBUG((DEBUG_INFO, "BIOS Build Date:%d/%d/%d Time:%d:%d:%d\n",gCurHardwareConfigData.BiosBuildYear, 
                                                                  gCurHardwareConfigData.BiosBuildMonth,
                                                                  gCurHardwareConfigData.BiosBuildDay, 
                                                                  gCurHardwareConfigData.BiosBuildHour,
                                                                  gCurHardwareConfigData.BiosBuildMinute,
                                                                  gCurHardwareConfigData.BiosBuildSecond));
      
    DEBUG((DEBUG_INFO, "Ps2KeyBoard: %x, Ps2Mouse:%x\n", gCurHardwareConfigData.BitPs2Keyboard, gCurHardwareConfigData.BitPs2Mouse));
    DEBUG((DEBUG_INFO, "MemMapCheckSum: %lx\n", gCurHardwareConfigData.MemMapData.MemMapCheckSum));
    DEBUG((DEBUG_INFO, "MemorySize: %ld MB\n", gCurHardwareConfigData.MemMapData.MemoryMbSize));
    DEBUG((DEBUG_INFO, "PciInfoChecksum: %lx\n", gCurHardwareConfigData.PciData.PciInfoChecksum));
    DEBUG((DEBUG_INFO, "USB#: %x,VID: %x, Port: %x\n", gCurHardwareConfigData.UsbData.UsbNum, gCurHardwareConfigData.UsbData.VidPidChecksum, gCurHardwareConfigData.UsbData.PortNumInterfaceNumChecksum));
    DEBUG((DEBUG_INFO, "Edid Chk: 0x%x, Resolution Chk: 0x%x\n", gCurHardwareConfigData.VideoData.EdidCheckNum, gCurHardwareConfigData.VideoData.ResolutionChecksum));
    DEBUG((DEBUG_INFO, "DiskInfoChecksum: %lx\n", gCurHardwareConfigData.DiskData.DiskInfoChecksum));

    Status = gRT->GetVariable (AMI_HARDWARE_SIGNATURE_SETUP_UPDATE_COUNT_VARIABLE, 
                               &gSetupUpdateCountGuid,
                               NULL, 
                               &VarSize, 
                               &SetupCount); 
    if (!EFI_ERROR (Status)) {
        gCurHardwareConfigData.SetupUpdateCount = SetupCount;
        DEBUG((DEBUG_INFO, "Setup Update Count:%d\n",SetupCount));
    }
    
    if (gExternalFunCallCount != 0)
    {
        for (NumberOfExternelFunCall= 0; NumberOfExternelFunCall < gExternalFunCallCount; NumberOfExternelFunCall++)
            DEBUG((DEBUG_INFO, "Used Protocol Checksum:%x\n", gCurHardwareConfigData.ReturnChecksum[NumberOfExternelFunCall]));

        QuickSort (gCurHardwareConfigData.ReturnChecksum , 0, gExternalFunCallCount - 1);

        for (NumberOfExternelFunCall = 0; NumberOfExternelFunCall < gExternalFunCallCount; NumberOfExternelFunCall++)
            DEBUG((DEBUG_INFO, "After Sorting :%x\n", gCurHardwareConfigData.ReturnChecksum[NumberOfExternelFunCall]));
    }

    Status = gBS->CalculateCrc32 (&gCurHardwareConfigData.BitPs2Keyboard, (UINT16)(sizeof(AMI_HARDWARE_SIGNATURE_CONFIG_DATA)), &FacsSignature);
    if (EFI_ERROR (Status)) {        
        DEBUG((DEBUG_INFO, "CheckCrc32: Crc calculation failed :%r\n", Status));      
        return Status;
    }
    DEBUG((DEBUG_INFO, "Update Current FACS Signature Variable: %lX\n", FacsSignature));
    
    DEBUG((DEBUG_INFO, "[-------Hardware Signature Debug Message----END------]\n"));   
    ///
    /// Update Hardware Signature of FACS table
    ///
    

    Facs = (EFI_ACPI_4_0_FIRMWARE_ACPI_CONTROL_STRUCTURE *)HardwareSignatureFindAcpiFacsTable ();
    if (Facs == NULL) {
        gBS->CloseEvent (Event);
        return Status;
    }
    Facs->HardwareSignature = FacsSignature;
    

    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

