//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file PerformanceMeasurementSmm.c
 *  Get Smm performance data and save to buffer.
 */

#include <AmiDxeLib.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Guid/Performance.h>
#include <Protocol/LoadedImage.h>
#include <protocol/DriverBinding.h>
#include <Protocol/DevicePathToText.h>
#include <Library/UefiLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/PrintLib.h>
#include <Protocol/Performance.h>
#include "PerformanceMeasurement.h"
#include "PerformanceMeasurementSmm.h"

EFI_SMM_SYSTEM_TABLE2           *gSmst2;
EFI_GUID    gAmiSmmGetPerfDataProtocolGuid = PM_GET_SMM_DATA_GUID;

/**
 * Set buffer data info to zero.
 *
 * @param[in]               Buffer              Data.
 * @param[in]               Size                Data size.
 * 
 */
void
ZeroMemorySmm (
    void                            *Buffer,
    UINTN                           Size
 )
{
    UINT8   *Ptr;
    
    Ptr = Buffer;
    while (Size--) {
        *(Ptr++) = 0;
    }
}


/**
 *  Get the PDB file name.
 *    
 * @param[in]                PdbFileName                The long PDB file name.
 * @param[out]               UnicodeBuffer                The output string to be logged by performance logger.
 * 
 */
VOID
GetShortPdbFileName (
  IN  CHAR8     *PdbFileName,
  OUT CHAR16    *UnicodeBuffer
  )
{
  UINTN IndexAscII;     /// Current work location within an ASCII string.
  UINTN IndexUnicode;     /// Current work location within a Unicode string.
  UINTN StartIndex;
  UINTN EndIndex;

  ZeroMemorySmm (UnicodeBuffer, DXE_PERFORMANCE_STRING_LENGTH * sizeof (CHAR16));

  if (PdbFileName == NULL) {
    StrCpy (UnicodeBuffer, L" ");
  } else {
    StartIndex = 0;
    for (EndIndex = 0; PdbFileName[EndIndex] != 0; EndIndex++);
    
    for (IndexAscII = 0; PdbFileName[IndexAscII] != 0; IndexAscII++) {
      if (PdbFileName[IndexAscII] == '\\') {
        StartIndex = IndexAscII + 1;
      }

      if (PdbFileName[IndexAscII] == '.') {
        EndIndex = IndexAscII;
      }
    }

    IndexUnicode = 0;
    for (IndexAscII = StartIndex; IndexAscII < EndIndex; IndexAscII++) {
      UnicodeBuffer[IndexUnicode] = (CHAR16) PdbFileName[IndexAscII];
      IndexUnicode++;
      if (IndexUnicode >= DXE_PERFORMANCE_STRING_LENGTH) {
        UnicodeBuffer[DXE_PERFORMANCE_STRING_LENGTH] = 0;
        break;
      }
    }
  }
}

/**
 * Use handle to get Smm record name.
 *
 * @param[in]               Handle                Record's handle.
 * @param[in]               GaugeString         Record's name data. 
 * @param[in]               LogGuid            Record's GUID.
 *
 *@retval EFI_SUCCESS                         Get record name success.
 */
EFI_STATUS
GetNameFromHandleSmm (
  IN EFI_HANDLE   Handle,
  IN OUT CHAR16*    GaugeString,
  IN OUT EFI_GUID **LogGuid
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;
  EFI_DRIVER_BINDING_PROTOCOL *DriverBinding;
  EFI_STRING                  StringPtr;
  EFI_DEVICE_PATH_PROTOCOL    *LoadedImageDevicePath;
  EFI_GUID                    *NameGuid;
  CHAR16                      *NameString;
  UINTN                       StringSize;
  CHAR8                       *PlatformLanguage;
  CHAR8                       *PdbFileName;
  EFI_COMPONENT_NAME2_PROTOCOL      *ComponentName2;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL  *DevicePathToText;

  ///
  /// Method 1: Get the name string from image PDB
  ///
  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **) &Image
                  );

  if (EFI_ERROR (Status)) {
    Status =gBS->OpenProtocol (
                    Handle,
                    &gEfiDriverBindingProtocolGuid,
                    (VOID **) &DriverBinding,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );

    if (!EFI_ERROR (Status)) {
      Status = gBS->HandleProtocol (
                      DriverBinding->ImageHandle,
                      &gEfiLoadedImageProtocolGuid,
                      (VOID **) &Image
                      );
    }
  }

  if (!EFI_ERROR (Status)) {
{
    PdbFileName = PeCoffLoaderGetPdbPointer (Image->ImageBase);
    if (PdbFileName != NULL) {
      GetShortPdbFileName (PdbFileName, GaugeString);
      return EFI_SUCCESS;
    }
}
  }

  ///
  /// Method 2: Get the name string from ComponentName2 protocol
  ///
  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID **) &ComponentName2
                  );

  if (!EFI_ERROR (Status)) {
    ///
    /// Get the current platform language setting
    ///
    GetEfiGlobalVariable2 (L"PlatformLang", (VOID**)&PlatformLanguage, NULL);
    Status = ComponentName2->GetDriverName (
                               ComponentName2,
                               PlatformLanguage != NULL ? PlatformLanguage : "en-US",
                               &StringPtr
                               );
    if (!EFI_ERROR (Status)) {
      StrnCpy (GaugeString, StringPtr, DP_GAUGE_STRING_LENGTH);
      GaugeString[DP_GAUGE_STRING_LENGTH] = 0;
      return EFI_SUCCESS;
    }
  }

  Status =gBS->HandleProtocol (
                  Handle,
                  &gEfiLoadedImageDevicePathProtocolGuid,
                  (VOID **) &LoadedImageDevicePath
                  );
  if (!EFI_ERROR (Status) && (LoadedImageDevicePath != NULL)) {
{
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    DevicePath = LoadedImageDevicePath;

    ///
    /// Try to get image GUID from LoadedImageDevicePath protocol
    ///
    NameGuid = NULL;
    while (!IsDevicePathEndType (DevicePath)) {
      NameGuid = EfiGetNameGuidFromFwVolDevicePathNode ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *) DevicePath);
      if (NameGuid != NULL) {
        break;
      }
      DevicePath = NextDevicePathNode (DevicePath);
    }
}
    if (NameGuid != NULL) {
      ///
      /// Try to get the image's FFS UI section by image GUID
      ///

      NameString = NULL;
      StringSize = 0;
      Status = GetSectionFromAnyFv (
                NameGuid,
                EFI_SECTION_USER_INTERFACE,
                0,
                (VOID **) &NameString,
                &StringSize
                );
      *LogGuid = NameGuid;
      
      if (!EFI_ERROR (Status)) {
        ///
        /// Method 3. Get the name string from FFS UI section
        ///
        StrnCpy (GaugeString, NameString, DP_GAUGE_STRING_LENGTH);
        GaugeString[DP_GAUGE_STRING_LENGTH] = 0;
        gBS->FreePool (NameString);
      } else {
        ///
        /// Method 4: Get the name string from image GUID
        ///
        UnicodeSPrint (GaugeString, sizeof (GaugeString), L"%g", NameGuid);
      }
      return EFI_SUCCESS;
    } else {
      ///
      /// Method 5: Get the name string from image DevicePath
      ///
      Status = gBS->LocateProtocol (
                      &gEfiDevicePathToTextProtocolGuid,
                      NULL,
                      (VOID **) &DevicePathToText
                      );
      if (!EFI_ERROR (Status)) {
        NameString = DevicePathToText->ConvertDevicePathToText (LoadedImageDevicePath, TRUE, FALSE);
        if (NameString != NULL) {
          StrnCpy (GaugeString, NameString, DP_GAUGE_STRING_LENGTH);
          GaugeString[DP_GAUGE_STRING_LENGTH] = 0;
          gBS->FreePool (NameString);
          return EFI_SUCCESS;
        }
      }
    }
  }

  return EFI_NOT_FOUND;
}

/**
 * Get Smm performance record.
 *
 * @param[in]               DispatchHandle            Handle to the Dispatcher.
 * @param[in]               DispatchContext           SW SMM dispatcher context.
 * @param[in]               CommBuffer                Communication buffer.
 * @param[in]               CommBufferSize            Communication buffer size.
 *
 */
EFI_STATUS 
EFIAPI 
GetPerfSmmData (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
)
{
    EFI_STATUS              Status = EFI_NOT_FOUND;
    PERFORMANCE_PROTOCOL    *Performance;
    UINTN                   LogEntryKey = 0;
    UINTN                   TotalNumber = 0;
    GAUGE_DATA_ENTRY        *OrgData;
    PM_SMM_DATA_STRUCTURE   *SmmBufferData;
    MEASUREMENT_RECORD      *RecordBuffer = NULL;
    UINTN                   Count = 0;
    EFI_GUID                *LogGuid = NULL;
    CHAR16                  *DataName;
    CHAR8                   *TempHost;
    CHAR8                   *Destination;
    CHAR16                  *Source;
    EFI_LOADED_IMAGE_PROTOCOL *pImage;
    
    SmmBufferData = (PM_SMM_DATA_STRUCTURE*)CommBuffer;
    
    gBS->AllocatePool(EfiBootServicesData, DATA_NAME_LENGTH * sizeof(CHAR16), (VOID**)&DataName);
    ZeroMemorySmm (DataName, DATA_NAME_LENGTH * sizeof(CHAR16));
    
    gBS->AllocatePool(EfiBootServicesData, TEMP_HOST_LENGTH * sizeof(CHAR8), (VOID**)&TempHost);
    ZeroMemorySmm (DataName, TEMP_HOST_LENGTH * sizeof(CHAR8));
    
    if (!SmmBufferData) {
        return Status; 
    }
    
    if ((UINT32) SmmBufferData->Signature != '$PM') {
        return Status;
    }
    Status = gSmst2->SmmLocateProtocol( &gSmmPerformanceProtocolGuid, NULL, (VOID**)&Performance);
    if (EFI_ERROR(Status)){
        return Status;
    }

    while (1) {
        Status = Performance->GetGauge(LogEntryKey, &OrgData);
        if (EFI_ERROR(Status)) {
            break;
        }
        LogEntryKey ++;
        TotalNumber ++;
    }
    
    gBS->AllocatePool(EfiBootServicesData, (TotalNumber + 3) * sizeof(MEASUREMENT_RECORD), (VOID**)&RecordBuffer);
    ZeroMemorySmm (RecordBuffer, (TotalNumber + 3) * sizeof(MEASUREMENT_RECORD));
    LogEntryKey = 0;
    while (1) {
        Status = Performance->GetGauge(LogEntryKey, &OrgData);
        if (EFI_ERROR(Status)) {
            break;
        }
        if (OrgData->StartTimeStamp == 0 && OrgData->EndTimeStamp == 0) {
            LogEntryKey ++;
            continue;
        }
        LogGuid = NULL;
        Status = GetNameFromHandleSmm((EFI_HANDLE)(OrgData->Handle), DataName, &LogGuid);
        if (!EFI_ERROR(Status)) {
            Source = DataName;
            Destination = (UINT8 *) TempHost;
            while (*Source) *Destination++ = (UINT8) (*Source++);
            *Destination = 0;
            MemCpy(&RecordBuffer[Count].PdbFileName, TempHost, EFI_PERF_PDBFILENAME_LENGTH * sizeof(CHAR8)); 
        }

        if (OrgData->Token[0] != 0) {
            Strcpy(RecordBuffer[Count].Token, OrgData->Token);
        }
        if ( OrgData->Module[0] != 0) {
            Strcpy(RecordBuffer[Count].Module, OrgData->Module);
        }
        RecordBuffer[Count].StartTimeStamp = OrgData->StartTimeStamp;
        RecordBuffer[Count].EndTimeStamp = OrgData->EndTimeStamp;
        if (OrgData->Handle != 0) {
            RecordBuffer[Count].Handle = (EFI_HANDLE)OrgData->Handle;
        }
        if (LogGuid != NULL) { 
            MemCpy(&RecordBuffer[Count].GuidName, LogGuid, sizeof(EFI_GUID)); 
        } else {
            Status = gBS->HandleProtocol (RecordBuffer[Count].Handle,&gEfiLoadedImageProtocolGuid, (VOID**)&pImage);
            if (!EFI_ERROR(Status)
                 && pImage->FilePath->Type ==  MEDIA_DEVICE_PATH
                 && pImage->FilePath->SubType == MEDIA_FV_FILEPATH_DP) {
                gBS->CopyMem (&(RecordBuffer[Count].GuidName), &( ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*) pImage->FilePath)->FvFileName), sizeof (EFI_GUID)); 
            }
        }
        LogEntryKey ++;
        Count ++;
    }
    
    SmmBufferData->RecordNumbers = Count;
    SmmBufferData->BufferAddress = (UINT8*)RecordBuffer;
    
    return EFI_SUCCESS;
       
}

/**
 * Initialize Smm data.
 *
 * @param[in]               ImageHandle                The firmware allocated handle for the EFI image.
 * @param[in]               SystemTable                A pointer to the EFI System Table.
 *
 * @retval EFI_SUCCESS                    Initialize success.
 */
EFI_STATUS 
EFIAPI 
SmmInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 )
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;

    EFI_SMM_BASE2_PROTOCOL          *SmmBase2;

    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    if (EFI_ERROR(Status)) { 
        return Status;
    }
    
    Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &SmmBase2);
    
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    ///
    /// We are in SMM, retrieve the pointer to SMM System Table
    ///
    Status = SmmBase2->GetSmstLocation( SmmBase2, &gSmst2);
    if (EFI_ERROR(Status)) {  
        return EFI_UNSUPPORTED;
    }

    Status = gSmst2->SmiHandlerRegister(
        (VOID *)GetPerfSmmData,
        &gAmiSmmGetPerfDataProtocolGuid,
        &Handle
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    return EFI_SUCCESS;
}

/**
 * Smm function entry point.
 *    
 * @param[in]   ImageHandle                The firmware allocated handle for the EFI image. 
 * @param[in]   SystemTable                A pointer to the EFI System Table.
 *
 * @retval EFI_SUCCESS                    The entry point is executed successfully.
 */
EFI_STATUS 
EFIAPI 
PerformanceMeasurementSmmEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle,SystemTable);
        
    return InitSmmHandler(ImageHandle, SystemTable, SmmInSmmFunction, NULL);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
