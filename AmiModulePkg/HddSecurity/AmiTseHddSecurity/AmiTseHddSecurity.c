//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiTseHddSecurity.c
    Provides the Hdd password Screen support in the setup.

**/
#include "AmiTseHddSecurity.h"

EFI_GUID gIDESecGuid                 = IDE_SECURITY_CONFIG_GUID;

#if defined(AmiChipsetPkg_SUPPORT) && AmiChipsetPkg_SUPPORT
#include "SbSataProtocol.h"
SB_HDD_POLICY_PROTOCOL      *gSbHddPolicyPtr = NULL;
EFI_GUID                    gSbHddPolicyProtocolGuid = SB_HDD_POLICY_PROTOCOL_GUID;
#endif

EFI_STRING
HddSecurityHiiGetString (
    IN EFI_HII_HANDLE  HiiHandle,
    IN EFI_STRING_ID   StringId
)
{
#if TSE_BUILD <= 0x1277
    return HiiGetString (HiiHandle, StringId);
#else
    return TseHiiGetString (HiiHandle, StringId);
#endif
}

BOOLEAN                             gCheckAllController = FALSE;
static EFI_HII_STRING_PROTOCOL      *HiiString = NULL;
static CHAR8                        *gSupportedLanguages = NULL;
HDD_SECURITY_INTERNAL_DATA          *HddSecurityInternalData = NULL;
EFI_HANDLE                          gHddSecEndHandle = NULL;
EFI_HANDLE                          HddNotifyHandle;
static  EFI_HANDLE                  *gHandleBuffer = NULL;
EFI_EVENT                           HddNotifyEvent;
VOID                                *HddNotifyRegistration;
BOOLEAN                             gHddFreeze = FALSE;
UINT16                              gHddSecurityCount = 0;
BOOLEAN                             gIsSbHddPolicyPresent = FALSE;
#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
EFI_STRING_ID                       ConfigPromptToken = 0;
extern UINTN                        gInvalidPasswordFailMsgBox;
#else
UINTN                               gCurrIDESecPage;
#endif
#endif

/** @internal
    Register the Protocol call back event

    @param VOID

    @retval TRUE     Protocol registered
    @retval FALSE    Error in registering protocol.

    @endinternal
**/
BOOLEAN
RegisterHddNotification ()
{
    EFI_STATUS                  Status;

    Status = gBS->CreateEvent (  
                        EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK,
                        HddNotificationFunction,
                        &HddNotifyRegistration,
                        &HddNotifyEvent );
    if (EFI_ERROR(Status)) {
        return FALSE;
    }
    Status = gBS->RegisterProtocolNotify (
                                &gAmiHddSecurityEndProtocolGuid,
                                HddNotifyEvent,
                                &HddNotifyRegistration);
    if (EFI_ERROR(Status)) {
        return FALSE;
    }
    //
    // get any of these events that have occurred in the past
    // When no con in devices are present this function is called later in BDS after InitConVars,
    // by that time if more than one controller present, Collect all controller and install gAmiHddPasswordVerifiedGuid
    gCheckAllController = TRUE;
    gBS->SignalEvent (HddNotifyEvent);

    return FALSE;
}

/** @internal
    Locate HDD child Block IO handle of controller handle
    Matching Port number

    @param ControllerHandle   Controller Handle
    @param Port               Port number

    @retval EFI_HANDLE       Block IO Handle

    @endinternal
**/
static
EFI_HANDLE
GetHddBlockIoHandle(
    IN EFI_HANDLE      ControllerHandle,
    IN UINT16          Port
)
{
    EFI_STATUS                              Status;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *Entries;
    UINTN                                   EntryCount;
    UINTN                                   Index;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL                *DpNode;
    SATA_DEVICE_PATH                        *SataDpNode;
    VOID                                    *BlockIo;
    
    DEBUG ((DEBUG_VERBOSE, "%a:POST GetHddBlockIoHandle\n", __FUNCTION__));
    
    Status = gBS->OpenProtocolInformation ( 
                                    ControllerHandle,
                                    &gEfiPciIoProtocolGuid,
                                    &Entries,
                                    &EntryCount );
    if (EFI_ERROR(Status)) {
       return NULL;
    }
    
    DEBUG ((DEBUG_VERBOSE, "%a:POST EntryCount - %d\n", __FUNCTION__, EntryCount));
    
    for (Index = 0; Index < EntryCount; Index++) {
        if (!(Entries[Index].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) {
            continue;
        }
        
        Status = gBS->HandleProtocol (
                                Entries[Index].ControllerHandle,
                                &gEfiBlockIoProtocolGuid,
                                (VOID**)&BlockIo);
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        Status = gBS->HandleProtocol (
                                Entries[Index].ControllerHandle,
                                &gEfiDevicePathProtocolGuid,
                                (VOID**)&DevicePath);
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        for (DpNode = DevicePath; !IsDevicePathEnd(DpNode); DpNode = NextDevicePathNode(DpNode)) {
            
            if ((DpNode->Type == MESSAGING_DEVICE_PATH) && (DpNode->SubType == MSG_SATA_DP)) {
                break;
            }
        }
        
        if (IsDevicePathEnd(DpNode)) {
            continue;
        }
        
        SataDpNode = (SATA_DEVICE_PATH *)DpNode;
        DEBUG ((DEBUG_VERBOSE, "%a:POST HBAPortNumber - 0x%x\n", __FUNCTION__, SataDpNode->HBAPortNumber));
        if ((SataDpNode->HBAPortNumber == (1 << Port)) && (SataDpNode->Lun == 0)) {
            DEBUG ((DEBUG_VERBOSE, "%a:POST BlockIo handle returned\n", __FUNCTION__));
            return Entries[Index].ControllerHandle;
        }
    }
    
    return NULL;
}

/** @internal
    Locate NVMe child Block IO handle of controller handle
    Matching Name space ID.

    @param ControllerHandle   Controller Handle
    @param NamespaceId        Namespace ID

    @retval EFI_HANDLE       Block IO Handle

    @endinternal
**/
static
EFI_HANDLE
GetNvmeBlockIoHandle(
    IN EFI_HANDLE      ControllerHandle,
    IN UINT32          NamespaceId
)
{
    EFI_STATUS                              Status;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     *Entries;
    UINTN                                   EntryCount;
    UINTN                                   Index;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL                *DpNode;
    NVME_NAMESPACE_DEVICE_PATH              *NvmeDpNode;
    VOID                                    *BlockIo;
    SATA_DEVICE_PATH                        *SataDpNode;
    
    DEBUG ((DEBUG_VERBOSE, "%a:POST GetNvmeBlockIoHandle\n", __FUNCTION__));
    
    Status = gBS->OpenProtocolInformation ( 
                                    ControllerHandle,
                                   &gEfiPciIoProtocolGuid,
                                   &Entries,
                                   &EntryCount );
    if (EFI_ERROR(Status)) {
       return NULL;
    }
    
    DEBUG ((DEBUG_VERBOSE, "%a:POST EntryCount - %d\n", __FUNCTION__,EntryCount));
    
    for (Index = 0; Index < EntryCount; Index++) {
        if (!(Entries[Index].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER)) {
            continue;
        }
        
        Status = gBS->HandleProtocol (
                                 Entries[Index].ControllerHandle,
                                 &gEfiBlockIoProtocolGuid,
                                 (VOID**)&BlockIo);
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        Status = gBS->HandleProtocol (
                                 Entries[Index].ControllerHandle,
                                 &gEfiDevicePathProtocolGuid,
                                 (VOID**)&DevicePath);
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        for (DpNode = DevicePath; !IsDevicePathEnd(DpNode); DpNode = NextDevicePathNode(DpNode)) {
            
            // Device handled by Intel VMD
            if ((DpNode->Type == MESSAGING_DEVICE_PATH) && (DpNode->SubType == MSG_NVME_NAMESPACE_DP)) {
                DEBUG ((DEBUG_VERBOSE, "%a:POST NVMe  MSG_NVME_NAMESPACE_DP, Index:%x\n", __FUNCTION__,Index));
                break;
            }
            
            // Device handled by Intel RST
            if ((DpNode->Type == MESSAGING_DEVICE_PATH) && (DpNode->SubType == MSG_SATA_DP)) {
                DEBUG ((DEBUG_VERBOSE, "%a:POST NVMe  MSG_SATA_DP, Index:%x\n", __FUNCTION__,Index));
                break;
            }
        }
        
        if (IsDevicePathEnd(DpNode)) {
            continue;
        }
        
        
        if (DpNode->SubType == MSG_NVME_NAMESPACE_DP) {
            NvmeDpNode = (NVME_NAMESPACE_DEVICE_PATH *)DpNode;
            DEBUG ((DEBUG_VERBOSE, "%a:POST NVMe NamespaceId - 0x%x\n", __FUNCTION__, NvmeDpNode->NamespaceId));
            if (NvmeDpNode->NamespaceId == (UINT32)(1 << (NamespaceId - 1))) {
                DEBUG ((DEBUG_VERBOSE, "%a:POST NVMe1 BlockIo handle returned\n", __FUNCTION__));
                return Entries[Index].ControllerHandle;
            }
        } else {
            SataDpNode = (SATA_DEVICE_PATH *)DpNode;
            DEBUG ((DEBUG_VERBOSE, "%a:POST HBAPortNumber - 0x%x, Index:%x\n",__FUNCTION__, SataDpNode->HBAPortNumber,Index));
            // 1 << x = HBAPortNumber; NameSpaceId = x + 1; 
            if (SataDpNode->HBAPortNumber == (1 << (NamespaceId - 1))) {
                DEBUG ((DEBUG_VERBOSE, "%a:POST NVMe2 BlockIo handle returned\n", __FUNCTION__));
                return Entries[Index].ControllerHandle;
            }
        }
    }
    DEBUG ((DEBUG_VERBOSE, "%a: Returned NULL \n", __FUNCTION__));
    return NULL;
}

/** 
    HDD notification function gets called when HddSecurityEnd Protocol get installed.

    @param Event             Event to signal
    @param HddRegContext     Event specific context (pointer to NotifyRegisteration

    @return VOID

**/
VOID
EFIAPI
HddNotificationFunction (
    IN EFI_EVENT                Event,
    IN VOID                     *HddRegContext
)
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  *HandleBuffer = NULL;
#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
    IDE_SECURITY_CONFIG         *pHddSecurityConfig = NULL;
    IDE_SECURITY_CONFIG          HddSecurityConfig;
    UINTN                       HddSecurityConfigSize = 0;
#endif
    HDD_SECURITY_INTERNAL_DATA  *DataPtr=NULL;
    UINTN                       NumHandles;
    UINTN                       Index=0;
    EFI_HANDLE                  Handle = NULL;
    EFI_GUID                    AmiTseHddNotifyGuid = AMI_TSE_HDD_NOTIFY_GUID;
    UINTN                       BufferSize = sizeof(UINTN);
    EFI_HANDLE                  DeviceHandle;
#if ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0) ) 
    AMI_HDD_SECURITY_INTERFACE  *Security = NULL;
    NVME_RST_INTERFACE          *NvmeRstInterface = NULL;
#endif  

    if (HddRegContext == NULL) {
        return;
    }

#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
    // Initialize IdeSecConfig information if this variable is not set already.
    pHddSecurityConfig = VarGetNvramName (
                                    L"IDESecDev", 
                                    &gIDESecGuid, 
                                    NULL, 
                                    &HddSecurityConfigSize );

    if (!pHddSecurityConfig) {

        pHddSecurityConfig = AllocateZeroPool (sizeof(IDE_SECURITY_CONFIG));

        if (pHddSecurityConfig == NULL) {
            return;
        }
        
        ZeroMem (pHddSecurityConfig, sizeof(IDE_SECURITY_CONFIG));
        VarSetNvramName (
                    L"IDESecDev",
                    &gIDESecGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    pHddSecurityConfig,
                    sizeof(IDE_SECURITY_CONFIG));
    } else {
        FreePool (pHddSecurityConfig);
    }
#endif

    //Locate the handle
    if (gCheckAllController) {
        // Locate all Handles that were installed previously.
        gCheckAllController = FALSE;
        Status = gBS->LocateHandleBuffer (   
                                    ByProtocol,
                                    &gAmiHddSecurityEndProtocolGuid,
                                    NULL,
                                    &NumHandles,
                                    &HandleBuffer);
    } else {
        Status = gBS->LocateHandleBuffer (
                                    ByRegisterNotify,
                                    NULL,
                                    *(VOID**)HddRegContext,
                                    &NumHandles,
                                    &HandleBuffer);
    }

    // If protocol not installed return
    if (EFI_ERROR(Status))
        return;

    //Locate the Security Protocols
    gHddSecurityCount = InitHddSecurityInternalDataPtr();

    for (Index = 0; Index < gHddSecurityCount; Index++) {
        //Initialize the DataPtr
        DataPtr = (HDD_SECURITY_INTERNAL_DATA *) IDEPasswordGetDataPtr(Index);

        // Search for locked Hard disc and not password verification done
        if (DataPtr->Locked && !DataPtr->Validated) {
            break;
        }
    }

    // Validate the password only if HDD is locked
    if ((gHddSecurityCount != 0) && (NULL != DataPtr) &&
        (DataPtr->Locked) && (!DataPtr->Validated)) {

        TSEIDEPasswordCheck();
    }

#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
    else {
          //
          // Update the IdeSecConfig information .
          //
          ZeroMem (&HddSecurityConfig, sizeof(HddSecurityConfig));
          HddSecurityConfig.Count = gHddSecurityCount;
          VarSetNvramName(
                      L"IDESecDev",
                      &gIDESecGuid,
                      EFI_VARIABLE_BOOTSERVICE_ACCESS,
                      &HddSecurityConfig,
                      sizeof(HddSecurityConfig));
    }
#endif

    // ConnectController once HDD is unlocked when no CONOUT present.
    for (Index = 0; Index < gHddSecurityCount; Index++) {
        //Initialize the DataPtr
        DataPtr = (HDD_SECURITY_INTERNAL_DATA *) IDEPasswordGetDataPtr(Index);

        // Connect the drives which had password and unlocked successfully by the USER
        if ((NULL != DataPtr) && (!DataPtr->Locked) && (DataPtr->Validated)) {
            DeviceHandle = DataPtr->DeviceHandle;
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
            Security = (AMI_HDD_SECURITY_INTERFACE *)DataPtr->HddSecurityProtocol;
            NvmeRstInterface = (NVME_RST_INTERFACE *)Security->BusInterface;
            if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)Security->BusInterfaceType == LocalAmiStorageInterfaceRaid) {
                if (NvmeRstInterface->IsRaidHdd) {
                    DeviceHandle = GetHddBlockIoHandle (
                                            NvmeRstInterface->RstControllerHandle, 
                                            NvmeRstInterface->PortNumber );
                } else {
                    DeviceHandle = GetNvmeBlockIoHandle (
                                            NvmeRstInterface->RstControllerHandle, 
                                            NvmeRstInterface->RstNamespaceId );
                }
            }
#endif
            if (DeviceHandle == NULL) {
                continue;
            }
            
            Status = gBS->ConnectController (
                                        DeviceHandle,
                                        NULL,
                                        NULL,
                                        TRUE ); 
            if (EFI_ERROR(Status)){
                continue;
            }
        }

    }
    
    // Install gAmiHddPasswordVerifiedGuid on specific Controller Handle.
    for (Index = 0; Index < NumHandles; Index++) {

        gHddSecEndHandle = HandleBuffer[Index];

        // Install the Unlocked Protocol to notify HDD has been unlocked
        // In case gAmiHddPasswordVerifiedGuid is already installed
        // on gHddSecEndHandle, Error shall be ignored to proceed.
        if (gHddSecEndHandle != NULL) {
            Status = gBS->InstallProtocolInterface (
                                            &gHddSecEndHandle,
                                            &gAmiHddPasswordVerifiedGuid,
                                            EFI_NATIVE_INTERFACE,
                                            NULL);
            if (EFI_ERROR(Status)) {
                continue;
            }
        }
    }

    FreePool (HandleBuffer);
    
    Status = gBS->LocateHandle ( 
                            ByProtocol,
                            &AmiTseHddNotifyGuid,
                            NULL,
                            &BufferSize,
                            &Handle );
    if (Status == EFI_SUCCESS) {
        Status = gBS->ReinstallProtocolInterface (
                                            Handle,
                                            &AmiTseHddNotifyGuid,
                                            NULL,
                                            NULL );
        
        ASSERT_EFI_ERROR(Status);
    } else {
     
        // Notify setup modules that AMITSE initialized HDD data.
        Status = gBS->InstallProtocolInterface (
                                            &Handle, 
                                            &AmiTseHddNotifyGuid, 
                                            EFI_NATIVE_INTERFACE,
                                            NULL );
        ASSERT_EFI_ERROR(Status);
    }
     
}

/** @internal
    Add the String to HII Database using HiiString Protocol

    @param HiiHandle     Handle to HII database
    @param String        Points to the new null-terminated string.

    @retval EFI_STRING_ID    String is added to HII Database 
    @return Other            Return error status.

    @endinternal
**/
EFI_STRING_ID
PrivateHiiAddString (
    IN  EFI_HII_HANDLE      HiiHandle,
    IN  CHAR16 *            String
)
{
    EFI_STATUS              Status;
    CHAR8*                  Languages = NULL;
    UINTN                   LangSize = 0;
    CHAR8*                  CurrentLanguage;
    BOOLEAN                 LastLanguage = FALSE;
    EFI_STRING_ID           StringId = 0;

    if (HiiString == NULL) {
        Status = gBS->LocateProtocol (
                                &gEfiHiiStringProtocolGuid, 
                                NULL, 
                                (VOID **) &HiiString);
        if (EFI_ERROR(Status)) {
            return 0;
        }
    }

    if (gSupportedLanguages == NULL) {
        Status = HiiString->GetLanguages (
                                    HiiString, 
                                    HiiHandle, 
                                    Languages, 
                                    &LangSize);
        if (Status == EFI_BUFFER_TOO_SMALL) {
            Languages = AllocatePool (LangSize);
            if (Languages == NULL) {
                //not enough resources to allocate string
                return 0;
            }
            Status = HiiString->GetLanguages (
                                        HiiString, 
                                        HiiHandle, 
                                        Languages, 
                                        &LangSize);
            if (EFI_ERROR(Status)) {
                return 0;
            }
        }
        gSupportedLanguages = Languages;
    } else {
        Languages = gSupportedLanguages;
    }
    
    if (Languages == NULL) {
        return 0;
    }

    while (!LastLanguage) {
        //point CurrentLanguage to start of new language
        CurrentLanguage = Languages;
        while (*Languages != ';' && *Languages != 0)
            Languages++;

        //Last language in language list
        if (*Languages == 0) {
            LastLanguage = TRUE;
            if (StringId == 0) {
                Status = HiiString->NewString (
                                        HiiString, 
                                        HiiHandle, 
                                        &StringId, 
                                        CurrentLanguage, 
                                        NULL, 
                                        String, 
                                        NULL );
            } else {
                Status = HiiString->SetString (
                                        HiiString, 
                                        HiiHandle, 
                                        StringId, 
                                        CurrentLanguage, 
                                        String, 
                                        NULL);
            }
            if (EFI_ERROR(Status)) {
                return 0;
            }
        } else {
            //put null-terminator
            *Languages = 0;
            if (StringId == 0) {
                Status = HiiString->NewString (
                                        HiiString, 
                                        HiiHandle, 
                                        &StringId, 
                                        CurrentLanguage, 
                                        NULL, 
                                        String, 
                                        NULL);
            } else {
                Status = HiiString->SetString (
                                        HiiString, 
                                        HiiHandle, 
                                        StringId, 
                                        CurrentLanguage, 
                                        String, 
                                        NULL);
            }
            *Languages = ';';       //restore original character
            Languages++;
            if (EFI_ERROR(Status)) {
                return 0;
            }
        }
    }
    return StringId;
}

/** @internal
    Add the String to HiiDatabase

    @param HiiHandle     Handle to HII database
    @param String        Points to the new null-terminated string.

    @retval EFI_STRING_ID    String is added to HII Database 

    @endinternal
**/
EFI_STRING_ID
PasswordHiiAddString (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16          *String
)
{
    EFI_STRING_ID   StringId = 0;

    StringId = PrivateHiiAddString (HiiHandle, String);

    // Error in Adding String. Try with Default function that AMITSE has.
    if (StringId == 0) {
        StringId = HiiAddString( HiiHandle, String );
    }

    return StringId;
}

/** @internal
    Function checks the Locally stored AmiHddSecurityProtocol handles are valid or not

    @param HandleBuffer       Handle to the buffer
    @param Count              Number of HDD connected.

    @retval BOOLEAN

    @endinternal
**/

BOOLEAN 
IsStoredPasswordDevHandleValid (
    IN EFI_HANDLE    *HandleBuffer,
    IN UINTN          Count
)
{
    UINTN           Index, Index1;
    BOOLEAN         AllPwddDevHandleAreValid = TRUE;
    
    for (Index = 0; Index < gHddSecurityCount; Index++) {
        for (Index1 = 0; Index1 < Count; Index1++) {
            if (gHandleBuffer[Index] == HandleBuffer[Index1]) {
                break;
            }
        }
        if (Index1 == Count) {
            gHandleBuffer[Index] = 0;
            AllPwddDevHandleAreValid = FALSE;
        }
    }
    
    if (gHddSecurityCount != Count) {
        return FALSE;
    }
    
    return AllPwddDevHandleAreValid;
}

/** @internal
    Locate the Security Protocols and return the information

    @param VOID

    @retval HDDCount     Count of Hdd connected.

    @endinternal
**/
UINT16
InitHddSecurityInternalDataPtr ()
{
    EFI_STATUS                      Status;
    EFI_HANDLE                      *HandleBuffer = NULL;
    UINT16                          Index, Index1, HDDCount = 0;
    UINTN                           Count;
    CHAR16                          *Name, *Temp1;
    CHAR16                          Temp[60];
    AMI_HDD_SECURITY_PROTOCOL       *HddSecurityProtocol = NULL;
    HDD_SECURITY_INTERNAL_DATA      *DataPtr = NULL;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
    PCI_DEVICE_PATH                 *PciDevicePath = NULL;
    AMI_HDD_SECURITY_INTERFACE      *Security = NULL;
    UINT32                          HddPortNumber = 0xFF;
    CHAR16                          *Buff = L"P";
    EFI_DISK_INFO_PROTOCOL          *DiskInfoPtr = NULL;
    UINT32                          PortNumber;
    HDD_SECURITY_INTERNAL_DATA      *TempIDEPasswordSecurityData = NULL;
#if defined(AmiChipsetPkg_SUPPORT) && AmiChipsetPkg_SUPPORT
    UINT32                          IdeChannel;
    UINT32                          IdeDevice;
#endif
    BOOLEAN                         IsRaidNvme = FALSE;
#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    if (ConfigPromptToken == 0)
        ConfigPromptToken = PasswordHiiAddString( gHiiHandle, L"HDD Security Configuration" );
#endif
#endif
    Status = gBS->LocateHandleBuffer (
                                ByProtocol,
                                &gAmiHddSecurityProtocolGuid,
                                NULL,
                                &Count,
                                &HandleBuffer);
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "%a: Locate AmiHddSecurityProtocol failed = %r\n",__FUNCTION__ ,Status));
        
        // if Locate AmiHddSecurityProtocol is failed, then there is no vaild storage device which supports SAT3 Security. 
        return 0;
    }
    
    // If already data has been found return with that information
    if ((gHddSecurityCount != 0) && (HddSecurityInternalData != NULL)) {
        // Check the locally stored AmiHddSecurityProtocol handles are valid or not
        if (IsStoredPasswordDevHandleValid (HandleBuffer,Count)) {
            return gHddSecurityCount;     // HddSecurityInternalData is valid
        }
    }

     //
     // New HDD device found. Need to validate the password for the new HDD
     // and skip the HDD that has been already validated.
     //
     TempIDEPasswordSecurityData = HddSecurityInternalData;
     
     HddSecurityInternalData = AllocateZeroPool (Count * sizeof(HDD_SECURITY_INTERNAL_DATA));
     if (HddSecurityInternalData) {
         ZeroMem (HddSecurityInternalData, sizeof(HDD_SECURITY_INTERNAL_DATA) * Count);
     }

     DataPtr = HddSecurityInternalData;
    if (DataPtr == NULL) {
        return 0;
    }

    for (Index = 0; Index < Count; Index++) {

        // Check if already Validate or not. If already validate don't verify the password again.
        if ((gHandleBuffer != NULL) && (gHddSecurityCount != 0)) {
            Index1 = gHddSecurityCount;

            do {
                if (HandleBuffer[Index] == gHandleBuffer[Index1-1]) {
                    break;
                }
                Index1--;
            } while (Index1 != 0);

            if (Index1 != 0) {
                CopyMem ((HddSecurityInternalData + Index), (TempIDEPasswordSecurityData + (Index1-1)), sizeof(HDD_SECURITY_INTERNAL_DATA));
                HDDCount++;
                continue;
            }
        }

        DataPtr = HddSecurityInternalData + Index;

        // Get the PasswordSecurity Protocol
        Status = gBS->OpenProtocol ( 
                            HandleBuffer[Index],
                            &gAmiHddSecurityProtocolGuid,
                            (VOID**) &HddSecurityProtocol,
                            NULL,
                            HandleBuffer[Index],
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        if (EFI_ERROR(Status))
            continue;
        
        Security = (AMI_HDD_SECURITY_INTERFACE *)HddSecurityProtocol;
        Security->PostHddCount = (VOID*)&gHddSecurityCount;
        Security->PostHddData = (VOID**)&HddSecurityInternalData;
        
        if (Security->BusInterfaceType == AmiStorageInterfaceIde) {

            // Handle the DiskInfo Protocol
            Status = gBS->OpenProtocol (
                                    HandleBuffer[Index],
                                    &gEfiDiskInfoProtocolGuid,
                                    (VOID**) &DiskInfoPtr,
                                    NULL,
                                    HandleBuffer[Index],
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
            if (EFI_ERROR(Status)) {
                continue;
            }

        // Locate the device path Protocol
        Status = gBS->OpenProtocol (
                            HandleBuffer[Index],
                            &gEfiDevicePathProtocolGuid,
                            (VOID**)&DevicePath,
                            NULL,
                            HandleBuffer[Index],
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);

        if (EFI_ERROR(Status)) {
            continue;
        }

        DevicePathNode = DevicePath;
        //
        // Traverse the Device Path structure till we reach HARDWARE_DEVICE_PATH
        //
        while (!IsDevicePathEndType(DevicePathNode)) {

            if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                (DevicePathNode->SubType == HW_PCI_DP)) {

                PciDevicePath = (PCI_DEVICE_PATH *)DevicePathNode;
                break;
            }

            DevicePathNode = NextDevicePathNode (DevicePathNode);
        }

        if (PciDevicePath == NULL) continue;

        }
        
        
        if (Security->BusInterfaceType == AmiStorageInterfaceAhci) {
            //
            //  Controller is in AHCI Mode, Call WhichIde function to find out Port Number
            //
            //DiskInfoPtr->WhichIde(DiskInfoPtr,&PortNumber,&PMPortNumber);
            //
            //  Assign the PortNumber to HddPortNumber.This Port Number is displayed in Setup.
            //
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
            PortNumber = ((SATA_DEVICE_INTERFACE *)(Security->BusInterface))->PortNumber;
#endif
            
            HddPortNumber = PortNumber;

            gIsSbHddPolicyPresent = TRUE;

        } else if (Security->BusInterfaceType == AmiStorageInterfaceIde) {


#if defined(AmiChipsetPkg_SUPPORT) && AmiChipsetPkg_SUPPORT

            if (gSbHddPolicyPtr == NULL) {
                Status = gBS->LocateProtocol (
                                        &gSbHddPolicyProtocolGuid,
                                        NULL,
                                        (VOID**)&gSbHddPolicyPtr);
            }

            if (gSbHddPolicyPtr != NULL) {

                //
                //  Find out the Primary/Secondary,Master/Slave Info from WhichIde function
                //
                DiskInfoPtr->WhichIde (DiskInfoPtr,&IdeChannel,&IdeDevice);
                //
                //  Get the Port Number to which the HDD is connected
                //
                gSbHddPolicyPtr->GeneratePortNumber (
                                            PciDevicePath->Device,
                                            PciDevicePath->Function,
                                            IdeChannel,
                                            IdeDevice,
                                            &PortNumber);

                HddPortNumber = PortNumber;

                gIsSbHddPolicyPresent = TRUE;

            } else {

                //
                // SB HDD Policy Protocol is not Present.
                //
                gIsSbHddPolicyPresent = FALSE;
            }
#endif
        } else if( (LOCAL_AMI_STORAGE_BUS_INTERFACE)Security->BusInterfaceType == LocalAmiStorageInterfaceRaid ) {
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0)) 
            
            if (((NVME_RST_INTERFACE *)Security->BusInterface)->IsRaidHdd) {
                
                PortNumber = ((NVME_RST_INTERFACE *)Security->BusInterface)->PortNumber;
            } else {
                IsRaidNvme = TRUE;
            }
#endif
            HddPortNumber = PortNumber;
            gIsSbHddPolicyPresent = TRUE;
        }

        if (CheckSecurityStatus (HddSecurityProtocol, &(DataPtr->Locked), SECURITY_LOCKED_MASK)) {
            DataPtr->HddSecurityProtocol = HddSecurityProtocol;

            if (HddPasswordGetDeviceName (HandleBuffer[Index], &Name)) {

                DataPtr->NameToken = PasswordHiiAddString (gHiiHandle, Name);

                if ((Security->BusInterfaceType == AmiStorageInterfaceNvme) || IsRaidNvme) {
                    //  Display the Port Number in Setup
                    UnicodeSPrint (Temp, 60, L"%s",Name);
                    DataPtr->PromptToken = PasswordHiiAddString (gHiiHandle, Temp);
                } else {
                    if (gIsSbHddPolicyPresent) {

                        //  Display the Port Number in Setup
                        UnicodeSPrint (Temp, 60, L"%s%d:%s", Buff, HddPortNumber, Name);
                        DataPtr->PromptToken = PasswordHiiAddString (gHiiHandle, Temp);
                    } else {

                        //  If SB HDD Policy Protocol is not Installed Use STR_IDE_SECURITY_PROMPT
                        //  token to display the String Information.
                        Temp1 = HddSecurityHiiGetString (gHiiHandle, STRING_TOKEN(STR_IDE_SECURITY_PROMPT));
                        UnicodeSPrint (Temp, 60, L"%s%d:%s", Temp1,HDDCount,Name);
                        DataPtr->PromptToken = PasswordHiiAddString (gHiiHandle, Temp);
                        FreePool (Temp1);
                    }
                }
            } 
            DataPtr->Validated = FALSE;
            DataPtr->PostHiiHandle = gHiiHandle;
            DataPtr->DeviceHandle = HandleBuffer[Index];
            HDDCount++;
         }// end if

    }// end of for

    if (gHandleBuffer != NULL) {
        FreePool (gHandleBuffer);
    }
    gHandleBuffer = AllocateZeroPool (sizeof(EFI_HANDLE) * Count);
    CopyMem (gHandleBuffer, HandleBuffer, sizeof(EFI_HANDLE) * Count);

    FreePool (HandleBuffer);
    if (TempIDEPasswordSecurityData != NULL) {
        FreePool (TempIDEPasswordSecurityData);
    }
    //
    //if no HDD is supported
    //
    if (HDDCount == 0) {
        FreePool (HddSecurityInternalData);
        HddSecurityInternalData = NULL;
    }

    return HDDCount;
}

/** @internal
    Return HDD Locked Information

    @param Index         Number of Hard Disk connected.

    @retval BOOLEAN

    @endinternal
**/
BOOLEAN
IDEPasswordGetLocked (
    IN UINTN   Index
)
{
    HDD_SECURITY_INTERNAL_DATA   *DataPtr = (HDD_SECURITY_INTERNAL_DATA *)IDEPasswordGetDataPtr (Index);

    if (DataPtr == NULL) {
        return 0;
    }
    return DataPtr->Locked;
}

/** @internal
    Return the Security Status Information

    @param *HddSecurityProtocol    Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param *ReqStatus              Pointer to Mask security status 
    @param Mask                    Flags for security.
    
    @retval TRUE        Security Status Information is valid.
    @retval FALSE       Unable to get security status     

    @endinternal
**/
BOOLEAN
CheckSecurityStatus (
    IN AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol,
    IN BOOLEAN                     *ReqStatus,
    IN UINT16                      Mask
)
{
    UINT16                      SecurityStatus = 0;
    EFI_STATUS                  Status;

    //get the security status of the device
    Status = HddSecurityProtocol->ReturnSecurityStatus (
                                            HddSecurityProtocol, 
                                            &SecurityStatus );

    if (EFI_ERROR(Status))
        return FALSE;

    *ReqStatus = (BOOLEAN)((SecurityStatus & Mask) ? TRUE : FALSE);
    
    return TRUE;
}

/** @internal
    Return the Device path Length

    @param *pDp     Pointer to obtain generic path/location information concerning
                      the physical device or logical device.

    @retval END_DEVICE_PATH_LENGTH    Length of the device path is obtained successfully.
    @return  Other                    Return error status.

    @endinternal
**/
UINTN
HddPasswordDPLength (
    IN EFI_DEVICE_PATH_PROTOCOL    *pDp
)
{
    UINTN               Size = 0;

    for (; !(IsDevicePathEnd (pDp)); pDp = NextDevicePathNode(pDp))
        Size += DevicePathNodeLength(pDp);

    // add size of END_DEVICE_PATH node
    return Size + END_DEVICE_PATH_LENGTH;
}
 
/** @internal
    Returns pointer on very last DP node before END_OF_DEVICE_PATH node

    @param *pDp       Pointer to obtain generic path/location information concerning
                      the physical device or logical device.

    @retval VOID

    @endinternal
**/
VOID *
HddPasswordDPGetLastNode (
    IN EFI_DEVICE_PATH_PROTOCOL    *pDp
)
{
    EFI_DEVICE_PATH_PROTOCOL        *dp = NULL;

    for (; !IsDevicePathEnd(pDp); pDp = NextDevicePathNode(pDp))
        dp = pDp;

    return dp;
}

/** @internal
    Copy the Device path to another Memory buffer

    @param *pDp     Pointer to obtain generic path/location information concerning
                      the physical device or logical device.
    @retval VOID

    @endinternal
**/
VOID*
HddPasswordDPCopy (
    IN EFI_DEVICE_PATH_PROTOCOL    *pDp
)
{
    UINTN           Length  = HddPasswordDPLength (pDp);
    UINT8           *ptr = AllocateZeroPool(Length);

    CopyMem (ptr, pDp, Length);
    return ptr;
}

/** @internal
    Return the Drive String Name

    @param Controller    The handle of the drive
    @param **wsName      Returned pointer to the drive string

    @retval TRUE     Drive string has been found and is in wsName
    @retval FALSE    Drive string has not been found

    @note  It is the caller's responsibility to deallocate the space used for
           DriveStringName

    @endinternal
**/
BOOLEAN
HddPasswordGetDeviceName (
    IN EFI_HANDLE  Controller,
    IN CHAR16      **DriveStringName
)
{
    EFI_STATUS                  Status;
    AMI_HDD_SECURITY_INTERFACE  *Security = NULL;

    CHAR16              *DeviceName;
    BOOLEAN             ReturnStatus = FALSE;
    UINT8               Index;
    UINTN               DriveStringLength;
    
    // Get the AMI_HDD_SECURITY_INTERFACE (actually getting the AMI_HDD_SECURITY_PROTOCOL, but
    //  the AMI_HDD_SECURITY_INTERFACE is an extended version with more information)
    Status = gBS->HandleProtocol (
                            Controller, 
                            &gAmiHddSecurityProtocolGuid, 
                            (VOID**)&Security);
    if (!EFI_ERROR(Status)) {
        
        if ((Security->BusInterfaceType < AmiStorageInterfaceIde) || 
           ((LOCAL_AMI_STORAGE_BUS_INTERFACE)Security->BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
            return FALSE;
        }
        
        switch (Security->BusInterfaceType) {
            case AmiStorageInterfaceIde:
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0))
                DeviceName = ((AMI_IDE_BUS_PROTOCOL *)Security->BusInterface)->IdeDevice.UDeviceName->UnicodeString;
#endif
                break;
                    
            case AmiStorageInterfaceAhci:
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
                DeviceName = ((SATA_DEVICE_INTERFACE *)Security->BusInterface)->UDeviceName->UnicodeString;
#endif
                break;
                    
            case AmiStorageInterfaceNvme:
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
                DeviceName = ((AMI_NVME_CONTROLLER_PROTOCOL *)Security->BusInterface)->UDeviceName->UnicodeString;
#endif
                break;
                    
            case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))
                DeviceName = ((NVME_RST_INTERFACE *)Security->BusInterface)->UDeviceName->UnicodeString;
#endif
                break;
            default:
                return FALSE;
            }
        
        }
        
        // Allocate space to copy the UNICODE device name string
        DriveStringLength = (StrLen(DeviceName) + 1);
        *DriveStringName = AllocateZeroPool (sizeof(CHAR16) * DriveStringLength);

        if (*DriveStringName != NULL) {
            // To remove the spaces from the HardDisk Model Number
            for (Index = HDD_MODEL_NUMBER_LENGTH; Index > 0; Index--) {

                if (DeviceName[Index] != SPACE_ASCII_VALUE) { 
                    break;
                }
                DeviceName[Index] = 0;
            }
            StrCpyS (*DriveStringName, DriveStringLength, DeviceName);
            ReturnStatus = TRUE;
        }

    // Return true to signify that a device name was discovered
    return ReturnStatus;
}

/** @internal
    Get the password and Validate the HDD password

    @param PromptToken     Security internal data
    @param *DataPtr        Pointer to HDD_SECURITY_INTERNAL_DATA

    @retval VOID

    @endinternal
**/
VOID
AmiCheckIDEPassword (
    IN UINT16           PromptToken,
    IN VOID             *DataPtr
)
{
    UINTN                       CurrXPos, CurrYPos, Index;
    CHAR16                      *PasswordEntered;
    EFI_STATUS                  Status = EFI_ACCESS_DENIED;

#if SETUP_ASK_MASTER_PASSWORD
    UINT32                      IdePasswordFlags = 0;
    CHAR16                      *HelpMsgToken = NULL;
    BOOLEAN                     MasterPwdInstalled = FALSE;
#endif

    UINTN                       BoxLength  = IDE_PASSWORD_LENGTH;
    CHAR16                      *DescToken = NULL;
    
    UINT16                      SecurityStatus=0;
    AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol = NULL;
    CHAR16                      *UnlckHddCBToken = NULL;
    UINTN                       CBBoxLength=0;
    

    CheckForKeyHook ((EFI_EVENT)NULL, NULL);
    gST->ConIn->Reset (gST->ConIn, FALSE);
    
    HddSecurityProtocol = ((HDD_SECURITY_INTERNAL_DATA *)DataPtr)->HddSecurityProtocol;
    
    DescToken = HddSecurityHiiGetString (gHiiHandle, STRING_TOKEN( STR_IDE_ENTER_USER));
    if (DescToken) {
        if ((TestPrintLength (DescToken) / NG_SIZE) > BoxLength) {
            BoxLength = TestPrintLength (DescToken) / NG_SIZE;
        }
    }
    FreePool (DescToken);

    UnlckHddCBToken = HddSecurityHiiGetString( gHiiHandle, STRING_TOKEN(STR_IDE_UNLCK_COLD));
    if ( UnlckHddCBToken ) {
        CBBoxLength = TestPrintLength( UnlckHddCBToken ) / NG_SIZE;
    }
    FreePool (UnlckHddCBToken);
    
#if SETUP_ASK_MASTER_PASSWORD
    Status = HddSecurityProtocol->ReturnIdePasswordFlags (
                                                HddSecurityProtocol,
                                                &IdePasswordFlags );
    if ((Status == EFI_SUCCESS) && (IdePasswordFlags & BIT16)) {
        MasterPwdInstalled = TRUE;
        HelpMsgToken = HddSecurityHiiGetString (gHiiHandle, STRING_TOKEN( STR_IDE_HELP_MESSAGE));
        if (HelpMsgToken) {
           if ((TestPrintLength (HelpMsgToken) / NG_SIZE) > BoxLength) {
               BoxLength = TestPrintLength (HelpMsgToken) / NG_SIZE;
           }
        }
        FreePool (HelpMsgToken);
    }
#endif
    
    REPORT_STATUS_CODE (EFI_PROGRESS_CODE,(EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_AUTHENTICATE_BEGIN));
    //
    //Draw password window
    //
#if ALL_HDD_SAME_PW
    PromptToken = STRING_TOKEN (STR_IDE_SECURITY_PROMPT);
#endif
    _DrawPasswordWindow (PromptToken, BoxLength, &CurrXPos, &CurrYPos);

    PasswordEntered = AllocateZeroPool ((IDE_PASSWORD_LENGTH + 1) * sizeof(CHAR16));
    
    //
    //Give number of chances to enter user password as per USER_PASSWORD_RETRY_ATTEMPTS SDL token.
    //
    for (Index = 0; Index < USER_PASSWORD_RETRY_ATTEMPTS; Index++ ) {
        Status = HddSecurityProtocol->ReturnSecurityStatus(
                                                    HddSecurityProtocol, 
                                                    &SecurityStatus );
        if ((Status == EFI_SUCCESS) && (SecurityStatus >> 4)& BIT0) {
            _DrawPasswordWindow (PromptToken, CBBoxLength, &CurrXPos, &CurrYPos);
            _ReportInBox (CBBoxLength, STRING_TOKEN(STR_IDE_UNLCK_COLD), CurrXPos, CurrYPos, TRUE);
            REPORT_STATUS_CODE (EFI_PROGRESS_CODE,(EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_AUTHENTICATE_END));
            if (gST->ConOut != NULL) {
                //Disable cursor, set desired attributes and clear screen
                gST->ConOut->EnableCursor (gST->ConOut, FALSE);
                gST->ConOut->SetAttribute (gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
                gST->ConOut->ClearScreen (gST->ConOut);
                MouseRefresh();
            }

            return;
        }
        _ReportInBox (BoxLength, STRING_TOKEN(STR_IDE_ENTER_USER), CurrXPos, CurrYPos - 1 , FALSE);
#if SETUP_ASK_MASTER_PASSWORD
        if (MasterPwdInstalled) {
            _ReportInBox (BoxLength, STRING_TOKEN(STR_IDE_HELP_MESSAGE), CurrXPos, CurrYPos + 1 , FALSE);
        }
#endif
        
        Status = _GetPassword (
                            PasswordEntered,
                            IDE_PASSWORD_LENGTH,
                            CurrXPos,
                            CurrYPos,
                            NULL );
        if (EFI_SUCCESS != Status) {
            break;
        } // end if

        //
        // Validate the Password
        //
        Status = IDEPasswordAuthenticate (PasswordEntered, DataPtr, TRUE);

        if (EFI_SUCCESS == Status) {
            break;
        } else if ((Index + 1) != USER_PASSWORD_RETRY_ATTEMPTS ) {
            _ReportInBox (IDE_PASSWORD_LENGTH, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, TRUE);
        }
    }// end of for

#if SETUP_ASK_MASTER_PASSWORD

    if (EFI_SUCCESS != Status) {
        
        if ((EFI_ABORTED != Status) && (MAXIMUM_HDD_UNLOCK_ATTEMPTS != USER_PASSWORD_RETRY_ATTEMPTS)) {
            _ReportInBox (IDE_PASSWORD_LENGTH, STRING_TOKEN(STR_ERROR_PSWD), CurrXPos, CurrYPos, TRUE);
        }
        //
        // Checking if the master password is installed
        //
        if (MasterPwdInstalled) {
            if (Index < MAXIMUM_HDD_UNLOCK_ATTEMPTS) {
                BoxLength = IDE_PASSWORD_LENGTH;
                DescToken = HddSecurityHiiGetString (gHiiHandle, STRING_TOKEN( STR_IDE_ENTER_MASTER));

                if (DescToken) {
                    if ((TestPrintLength( DescToken ) / NG_SIZE) > BoxLength) {
                        BoxLength = TestPrintLength (DescToken) / NG_SIZE;
                    }
                }
                FreePool (DescToken);

                ClearScreen (EFI_BACKGROUND_BLACK | EFI_LIGHTGRAY);
                MouseRefresh();
                
                //
                //Draw password window
                //
                _DrawPasswordWindow (PromptToken, BoxLength, &CurrXPos, &CurrYPos);
            }

            //
            //Give remaining chances to enter Master password
            //
            for (; Index < MAXIMUM_HDD_UNLOCK_ATTEMPTS; Index++) {
                Status = HddSecurityProtocol->ReturnSecurityStatus (
                                                        HddSecurityProtocol, 
                                                        &SecurityStatus );
                if ((Status == EFI_SUCCESS) && (SecurityStatus >> 4) & BIT0) {
                    _DrawPasswordWindow (PromptToken, CBBoxLength, &CurrXPos, &CurrYPos);
                    _ReportInBox (CBBoxLength, STRING_TOKEN(STR_IDE_UNLCK_COLD), CurrXPos, CurrYPos, TRUE);
                    REPORT_STATUS_CODE (EFI_PROGRESS_CODE, (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_AUTHENTICATE_END));
                    if (gST->ConOut != NULL) {
                        //Disable cursor, set desired attributes and clear screen
                        gST->ConOut->EnableCursor (gST->ConOut, FALSE);
                        gST->ConOut->SetAttribute (gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
                        gST->ConOut->ClearScreen (gST->ConOut);
                        MouseRefresh();
                    }
                    
                    return;
                }
                _ReportInBox (BoxLength, STRING_TOKEN(STR_IDE_ENTER_MASTER ), CurrXPos, CurrYPos - 1, FALSE);

                Status = _GetPassword (
                                 PasswordEntered, 
                                 IDE_PASSWORD_LENGTH, 
                                 CurrXPos,
                                 CurrYPos, 
                                 NULL );
                if (EFI_SUCCESS != Status) {
                    break;
                }

                // validate the Master password
                Status = IDEPasswordAuthenticate (PasswordEntered, DataPtr, FALSE);

                if (EFI_SUCCESS == Status) {
                    break;
                } else {
                    if ( (Index + 1) != MAXIMUM_HDD_UNLOCK_ATTEMPTS) {
                        _ReportInBox (
                                IDE_PASSWORD_LENGTH,
                                STRING_TOKEN(STR_ERROR_PSWD),
                                CurrXPos,
                                CurrYPos,
                                TRUE );
                    }
                }
            }// end of for
        } else {
            // User password entered wrongly and Master Password support enabled but not set.
            // As User Password unlock status replaced with ReturnIdePasswordFlags() status,
            // forcing status to EFI_ABORTED to display "HDD Locked" message 
            Status = EFI_ABORTED;
        }
    }// end if
#endif

    ZeroMem (PasswordEntered, (IDE_PASSWORD_LENGTH + 1) * sizeof(CHAR16));

    FreePool (PasswordEntered);

    if ((EFI_SUCCESS != Status) || Index >= MAXIMUM_HDD_UNLOCK_ATTEMPTS) {
        //Report Invalid password
        _ReportInBox (
                   IDE_PASSWORD_LENGTH, 
                   STRING_TOKEN(STR_IDE_ERROR_PSWD ),
                   CurrXPos, 
                   CurrYPos, 
                   TRUE );
        // Unlock failed.
        REPORT_STATUS_CODE (
                        EFI_ERROR_CODE | EFI_ERROR_MAJOR,
                        DXE_INVALID_IDE_PASSWORD );
    }
    REPORT_STATUS_CODE (
            EFI_PROGRESS_CODE,
            (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_AUTHENTICATE_END) );
    if (gST->ConOut != NULL) {
        //Disable cursor, set desired attributes and clear screen
        gST->ConOut->EnableCursor (gST->ConOut, FALSE);
        gST->ConOut->SetAttribute (gST->ConOut, (EFI_BACKGROUND_BLACK | EFI_WHITE));
        gST->ConOut->ClearScreen (gST->ConOut);
        MouseRefresh();
    }
}

/** @internal
    Send Freeze command to all the HDD

    @param VOID

    @retval VOID

    @endinternal
**/
VOID
IDEPasswordFreezeDevices ()
{
    EFI_STATUS                  Status;
    EFI_HANDLE                  *HandleBuffer;
    UINT16                      Index;    
    UINTN                       Count;
    AMI_HDD_SECURITY_PROTOCOL   *HddSecurityProtocol = NULL;

    // Return if Hdd FreezeLock command is already sent
    if (gHddFreeze) {
        return;
    }

    Status = gBS->LocateHandleBuffer (
                                ByProtocol,
                                &gAmiHddSecurityProtocolGuid,
                                NULL,
                                &Count,
                                &HandleBuffer );

    if (EFI_ERROR(Status)) {
        return;
    }

    for (Index = 0; Index < Count; Index++) {
        // get password security protocol
        Status = gBS->OpenProtocol (
                                HandleBuffer[Index],
                                &gAmiHddSecurityProtocolGuid,
                                (VOID**) &HddSecurityProtocol,
                                NULL,
                                HandleBuffer[Index],
                                EFI_OPEN_PROTOCOL_GET_PROTOCOL );

        if (EFI_ERROR(Status)) {
            continue;
        }

        //
        //Send Freeze lock command
        //
        Status= HddSecurityProtocol->SecurityFreezeLock (HddSecurityProtocol);
        if (EFI_ERROR(Status)) {
             DEBUG((DEBUG_ERROR, "%a: SecurityFreezeLock Status = %r\n",__FUNCTION__,Status));
        }
        
    }// end of for
    
    gHddFreeze = TRUE;
    FreePool (HandleBuffer);
}

/** @internal
    Updates the HDD password for the current HDD alone.
    
    @param Index          Number of Hard Disk connected.
    @param *Password      Pointer to Password for security.
    @param bCheckUser     Boolean value to check for user Password/Master Password.

    @retval TRUE     HDD Password updated successfully
    @retval FALSE    Error in updating HDD Password.

    @endinternal
**/
BOOLEAN
IDEPasswordUpdateHdd (
    IN UINT32               Index,
    IN CHAR16               *Password,
    IN BOOLEAN              bCheckUser
)
{
    AMI_HDD_SECURITY_PROTOCOL       *HddSecurityProtocol = NULL;
    UINT16                          Control = bCheckUser ? 0 : 1;
    UINT8                           RevisionCode = 0;
    BOOLEAN                         Locked, Enabled;
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    UINT8                           Buffer[IDE_PASSWORD_LENGTH + 1];
    UINT8                           Selection;
    CHAR16                          *MsgToken = NULL;
    #if !SETUP_SAME_SYS_HDD_PW
    UINTN                           Index1;
    #endif
    HDD_SECURITY_INTERNAL_DATA      *DataPtr;

//
// While password is set via hook in TSE to perform some OEM feature
// and SETUP_PASSWORD_NON_CASE_SENSITIVE is set, even then the
// password will be updated as if it is case sensitive but Authenticates
// as non case sensitive so in order to avoid such situation making
// IDEPasswordUpdateHdd() symmetric with IDEPasswordAuthenticateHdd()
// to update case sensitivity {EIP99649}
//
#if defined(SETUP_PASSWORD_NON_CASE_SENSITIVE) && SETUP_PASSWORD_NON_CASE_SENSITIVE
    UpdatePasswordToNonCaseSensitive (Password, StrLen(Password));
#endif

    DataPtr = (HDD_SECURITY_INTERNAL_DATA *)IDEPasswordGetDataPtr (Index);
    
    if (DataPtr == NULL) {
        MsgToken = HddSecurityHiiGetString (
                                    gHiiHandle,
                                    STRING_TOKEN(STR_IDE_SECURITY_UNSUPPORTED));
        ShowPostMsgBox (
                NULL,
                MsgToken,
                MSGBOX_TYPE_OK,
                &Selection ); // ShowPostMsgBox
        FreePool (MsgToken);
        return FALSE;
    }
    HddSecurityProtocol = DataPtr->HddSecurityProtocol;

    //
    //get the status of the device
    //
    if ( !(CheckSecurityStatus (HddSecurityProtocol, &Locked, SECURITY_LOCKED_MASK) && 
           CheckSecurityStatus (HddSecurityProtocol, &Enabled, SECURITY_ENABLED_MASK))) {
        return FALSE;
    }

    if (!Locked) {
        if (Password[0] == 0) {
            //
            //empty string is entered -> disable password
            //
            Status = HddSecurityProtocol->SecurityDisablePassword (
                                                        HddSecurityProtocol,
                                                        Control,
                                                        HddSecurityInternalData[Index].PWD );
        } else {
            //
            //set new password
            //
            ZeroMem (&Buffer, IDE_PASSWORD_LENGTH + 1);
#if !SETUP_SAME_SYS_HDD_PW

            for ( Index1 = 0; Index1 < IDE_PASSWORD_LENGTH + 1; Index1++) {
                Buffer[Index1] = (UINT8)Password[Index1];

                if ( Password[Index1] == L'\0' ) {
                    break;
                }
            }// end of for
#else
            CopyMem (Buffer, Password, IDE_PASSWORD_LENGTH + 1);
#endif

            Status = HddSecurityProtocol->SecuritySetPassword (
                                                        HddSecurityProtocol,
                                                        Control,
                                                        Buffer,
                                                        RevisionCode );
        }
    }// end if(!Locked)

    if (EFI_ERROR(Status)) {
        return FALSE;
    }

    return TRUE;
}

/** @internal
    Updates the HDD password for all the HDDs present.

    @param Index          Number of Hard Disk connected.
    @param *Password      Pointer to Password for security.
    @param bCheckUser     Boolean value to check for user Password/Master Password.

    @return TRUE     HDD Password updated successfully
    @return FALSE    Error in updating HDD Password.

    @endinternal
**/
BOOLEAN
IDEPasswordUpdateAllHdd (
    IN UINT32               Index,
    IN CHAR16               *Password,
    IN BOOLEAN              bCheckUser
)
{
    UINTN                   Index1;
    BOOLEAN                 Status = FALSE;
        for (Index1 = 0; Index1 < gHddSecurityCount; Index1++ ) {
            Status = IDEPasswordUpdateHdd ((UINT32)Index1, Password, bCheckUser);
        }
    return Status;
}

/** @internal
    Hook function to update the password for the HDDs based
    on the token ALL_HDD_SAME_PW.

    @param Index          Number of Hard Disk connected.
    @param *Password      Pointer to Password for security.
    @param bCheckUser     Boolean value to check for user Password/Master Password.

    @return TRUE     HDD Password updated successfully
    @return FALSE    Error in updating HDD Password.

    @endinternal
**/
BOOLEAN
IDEPasswordUpdate (
    IN UINT32               Index,
    IN CHAR16               *Password,
    IN BOOLEAN              bCheckUser
)
{
#if ALL_HDD_SAME_PW
     return IDEPasswordUpdateAllHdd (Index, Password, bCheckUser);
#else
     return IDEPasswordUpdateHdd (Index, Password, bCheckUser);
#endif

}
/** @internal
    Unlock the HDD

    @param VOID

    @return VOID

    @endinternal
**/
VOID
UnlockHDD ()
{
    
#if SETUP_SAME_SYS_HDD_PW
    UINTN                       Size = 0, Index;
    AMITSESETUP                 *TSESetup;
    HDD_SECURITY_INTERNAL_DATA  *DataPtr;
    EFI_STATUS                  Status;
    EFI_GUID                    AmiTseSetupGuid = AMITSESETUP_GUID;

    //
    //Do not proceed if ADMIN password is not set
    //
    if (!(AMI_PASSWORD_USER & PasswordCheckInstalled())) {
        return;
    }

    //
    //Get password from NVRAM
    //
    Size = 0;
    TSESetup = VarGetNvramName (L"AMITSESetup", &AmiTseSetupGuid, NULL, &Size);

    if (Size) {
        //
        //For all drives
        //
        DataPtr = HddSecurityInternalData;

        for (Index = 0; Index < gHddSecurityCount; Index++) {
            if (DataPtr->Locked && !DataPtr->Validated) {
                //
                //ask for the password if locked
                //
                DataPtr->Validated = TRUE;
                Status = IDEPasswordAuthenticateHdd (
                                            TSESetup->UserPassword,
                                            DataPtr,
                                            TRUE );

                if (EFI_SUCCESS != Status) {
                    //
                    // Unlock failed.
                    //
                    REPORT_STATUS_CODE (
                                    EFI_ERROR_CODE | EFI_ERROR_MAJOR,
                                    DXE_INVALID_IDE_PASSWORD );
                }
            }
            DataPtr++;
        } // end of for
    } // end if

    FreePool (TSESetup);
#endif //#if SETUP_SAME_SYS_HDD_PW
}

/** @internal
    Set the HDD password

    @param VOID

    @return VOID

    @endinternal
**/
VOID
SetHDDPassword ()
{
    
#if SETUP_SAME_SYS_HDD_PW
    UINTN                       Size = 0, Index;
    AMITSESETUP                 *TSESetup;
    BOOLEAN                     BoolStatus;
    EFI_GUID                    AmiTseSetupGuid = AMITSESETUP_GUID;
    
    //
    //Get password from NVRAM
    //
    Size = 0;
    TSESetup = VarGetNvramName (L"AMITSESetup", &AmiTseSetupGuid, NULL, &Size);

    if (Size) {
        //
        //For all drives
        //
        for (Index = 0; Index < gHddSecurityCount; Index++) {
            BoolStatus = IDEPasswordUpdateHdd ((UINT32)Index, TSESetup->UserPassword, TRUE);
            DEBUG((DEBUG_VERBOSE, "HddSecurity: %a IDEPasswordUpdateHdd Status :%d\n",__FUNCTION__,BoolStatus));
        }
    }

    FreePool (TSESetup);
#endif //#if SETUP_SAME_SYS_HDD_PW
}

/** @internal
    Validate the HDD password

    @param VOID

    @return VOID

    @endinternal
**/
VOID
IDEPasswordCheck ()
{
    
#if !SETUP_SAME_SYS_HDD_PW
    HDD_SECURITY_INTERNAL_DATA          *DataPtr;
    UINT16                              Index;
#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    UINTN                               HddIndex = 0;
#endif
#endif
#endif
#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
    IDE_SECURITY_CONFIG                 HddSecurityConfig;
#endif

    // build IDESecurity data
    gHddSecurityCount = InitHddSecurityInternalDataPtr ();

    if ((HddSecurityInternalData == NULL) || (gHddSecurityCount == 0) || gHddFreeze) {
        return;
    }

#if SETUP_SAME_SYS_HDD_PW
        UnlockHDD();
#else
    DataPtr = HddSecurityInternalData;
#if !ALL_HDD_SAME_PW
    for (Index = 0; Index < gHddSecurityCount; Index++) {
        if (DataPtr->Locked && (!DataPtr->Validated)) {
            //ask for the password if locked
            DataPtr->Validated = TRUE;
            AmiCheckIDEPassword (DataPtr->PromptToken, (VOID*)DataPtr);
        }
        DataPtr++;
    }// end of for
#else

    for (Index = 0; Index < gHddSecurityCount; Index++) {
        // Check if Password is validated for a Device, if yes, Use the same Password buffer
        if (DataPtr->Validated && !DataPtr->Locked) {

            if (!EFI_ERROR(IDEPasswordUpdateAllHddWithValidatedPsw (
                                                            DataPtr->PWD,
                                                            DataPtr,
                                                            DataPtr->LoggedInAsMaster? 0:1 ))) {
                break;
            }
        }
        DataPtr++;
    }// end of for
    
    // Ask Password from User
    if (Index == gHddSecurityCount) {
        DataPtr = HddSecurityInternalData;
        if (DataPtr->Locked && (!DataPtr->Validated)) {
            //ask for the password if locked
            DataPtr->Validated = TRUE;
            AmiCheckIDEPassword (DataPtr->PromptToken, (VOID*)DataPtr);
        }
    }
#endif
#endif

#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
    ZeroMem (&HddSecurityConfig, sizeof(HddSecurityConfig));
    HddSecurityConfig.Count = gHddSecurityCount;
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    for (HddIndex = 0; HddIndex < gHddSecurityCount; HddIndex++) {
        IDEUpdateConfig (&HddSecurityConfig, HddIndex);
    }
#endif
    VarSetNvramName (
                L"IDESecDev",
                &gIDESecGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                &HddSecurityConfig,
                sizeof(HddSecurityConfig));
#endif
}


#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
/** @internal
    Initializes the structure IDE_SECURITY_CONFIG for the current
    HDD if the data pointer to the structure HDD_SECURITY_INTERNAL_DATA is
    initialized already.

    @param *ptrHddSecurityConfig     Pointer to IDE_SECURITY_CONFIG
    @param value                     Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
UpdateSetupDataByHddIndex (
    IN VOID                     *ptrHddSecurityConfig,
    IN UINTN                    Value
)
{
    HDD_SECURITY_INTERNAL_DATA    *DataPtr = NULL;
    AMI_HDD_SECURITY_PROTOCOL     *HddSecurityProtocol = NULL;
    BOOLEAN                       Status;
    UINT32                        IdePasswordFlags = 0;
    EFI_STATUS                    ReturnStatus;
    IDE_SECURITY_CONFIG           *HddSecurityConfig = (IDE_SECURITY_CONFIG *)ptrHddSecurityConfig;

    //Set current HDD security page
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE

    if ((gHddSecurityCount == 0) || (HddSecurityInternalData == NULL)) {
        //try to initialize, if not initialized
        gHddSecurityCount = InitHddSecurityInternalDataPtr();
    }

    for (Value = 0; Value < gHddSecurityCount; Value++) {
        DataPtr = (HDD_SECURITY_INTERNAL_DATA *)IDEPasswordGetDataPtr (Value);

        if (DataPtr) {
            HddSecurityProtocol = DataPtr->HddSecurityProtocol;

            CheckSecurityStatus (
                            HddSecurityProtocol,
                            &Status,
                            SECURITY_SUPPORTED_MASK );
            HddSecurityConfig->Supported[value] = Status ? 1 : 0;
            
            CheckSecurityStatus (
                            HddSecurityProtocol,
                            &Status,
                            SECURITY_ENABLED_MASK );
            HddSecurityConfig->Enabled[value] = Status ? 1 : 0;
            
            CheckSecurityStatus (
                            HddSecurityProtocol,
                            &Status,
                            SECURITY_LOCKED_MASK );
            HddSecurityConfig->Locked[value] = Status ? 1 : 0;
            
            CheckSecurityStatus (
                            HddSecurityProtocol,
                            &Status,
                            SECURITY_FROZEN_MASK );
            HddSecurityConfig->Frozen[value] = Status ? 1 : 0;
            
            ReturnStatus = HddSecurityProtocol->ReturnIdePasswordFlags (
                                                               HddSecurityProtocol,
                                                               &IdePasswordFlags );

            if (EFI_ERROR(ReturnStatus)) {
                return;
            }

            HddSecurityConfig->UserPasswordStatus[value] = (IdePasswordFlags & 0x00020000) ? 1 : 0;
            HddSecurityConfig->MasterPasswordStatus[value] = (IdePasswordFlags & 0x00010000) ? 1 : 0;
            HddSecurityConfig->ShowMaster[value] = 0x0000;

            if (HddSecurityConfig->Locked[value] &&  HddSecurityConfig->MasterPasswordStatus[value]) {
                HddSecurityConfig->ShowMaster[value] = 0x0001;
            } else if ((DataPtr->LoggedInAsMaster)) {
                HddSecurityConfig->ShowMaster[value] = 0x0001;
            } else if (!(HddSecurityConfig->UserPasswordStatus[value])) {
                HddSecurityConfig->ShowMaster[value] = 0x0001;
            }
        }// end if
    }
#else
    gCurrIDESecPage = Value;

    DataPtr = (HDD_SECURITY_INTERNAL_DATA*)IDEPasswordGetDataPtr(Value);

    if (DataPtr) {
        HddSecurityProtocol = DataPtr->HddSecurityProtocol;

        CheckSecurityStatus (
                        HddSecurityProtocol,
                        &Status,
                        SECURITY_SUPPORTED_MASK );
        HddSecurityConfig->Supported = Status ? 1 : 0;
        
        CheckSecurityStatus (
                        HddSecurityProtocol,
                        &Status,
                        SECURITY_ENABLED_MASK );
        HddSecurityConfig->Enabled = Status ? 1 : 0;
        
        CheckSecurityStatus (
                        HddSecurityProtocol,
                        &Status,
                        SECURITY_LOCKED_MASK );
        HddSecurityConfig->Locked = Status ? 1 : 0;
        
        CheckSecurityStatus (
                        HddSecurityProtocol,
                        &Status,
                        SECURITY_FROZEN_MASK );
        HddSecurityConfig->Frozen = Status ? 1 : 0;
        
        ReturnStatus = HddSecurityProtocol->ReturnIdePasswordFlags (
                                                            HddSecurityProtocol,
                                                            &IdePasswordFlags );

        if (EFI_ERROR(ReturnStatus)) {
            return;
        }

        HddSecurityConfig->UserPasswordStatus = (IdePasswordFlags & 0x00020000) ? 1 : 0;
        HddSecurityConfig->MasterPasswordStatus = (IdePasswordFlags & 0x00010000) ? 1 : 0;
        HddSecurityConfig->ShowMaster = 0x0000;

        if (HddSecurityConfig->Locked && HddSecurityConfig->MasterPasswordStatus) {
            HddSecurityConfig->ShowMaster = 0x0001;
        } else if ((DataPtr->LoggedInAsMaster)) {
            HddSecurityConfig->ShowMaster = 0x0001;
        } else if (!(HddSecurityConfig->UserPasswordStatus)) {
            HddSecurityConfig->ShowMaster = 0x0001;
        }
    }// end if
#endif
}

/** @internal
    Initializes the structure IDE_SECURITY_CONFIG for all the
    HDDs present if the data pointer to the structure
    HDD_SECURITY_INTERNAL_DATA is initialized already.

    @param *ptrHddSecurityConfig     Pointer to IDE_SECURITY_CONFIG
    @param value                     Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
UpdateSetupDataForAllHdd (
    IN VOID             *ptrHddSecurityConfig,
    IN UINTN            Value
)
{
    Value = 0;

    //Set current HDD security page
    #if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
        UpdateSetupDataByHddIndex (ptrHddSecurityConfig, Value);
    #else
        for (; value < gHddSecurityCount; Value++) {
            UpdateSetupDataByHddIndex (ptrHddSecurityConfig, value);
        }
    #endif

}

/** @internal
    Hook function to Initialize the structure IDE_SECURITY_CONFIG
    for the HDDs based on the token ALL_HDD_SAME_PW.

    @param *ptrHddSecurityConfig     Pointer to IDE_SECURITY_CONFIG
    @param value                     Number of HDD connected.

    @return VOID

    @endinternal
**/
VOID
IDEUpdateConfig (
    IN VOID             *ptrHddSecurityConfig,
    IN UINTN            Value
)
{
#if ALL_HDD_SAME_PW
     UpdateSetupDataForAllHdd (ptrHddSecurityConfig, Value);
#else
     UpdateSetupDataByHddIndex (ptrHddSecurityConfig, Value);
#endif

}
/** @internal
    Get the Hdd name

    @param Index        Number of Hard Disk connected.   

    @return VOID

    @endinternal
**/
UINT16
IDEPasswordGetName (
    IN UINT16           Index
)
{
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
    // workaround for code in special.c which fills "goto string" token with
    // HDD name string token. In this case we do not need that.
    return ConfigPromptToken;
#else
    UINTN                         size = 0;
    IDE_SECURITY_CONFIG           *HddSecurityConfig;
    HDD_SECURITY_INTERNAL_DATA    *DataPtr = NULL;

    HddSecurityConfig = VarGetNvramName (L"IDESecDev", &gIDESecGuid, NULL, &size);
    UpdateSetupDataByHddIndex (HddSecurityConfig, Index);
    VarSetNvramName (
                L"IDESecDev",
                &gIDESecGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                HddSecurityConfig,
                size);

    FreePool (HddSecurityConfig);

    DataPtr = (HDD_SECURITY_INTERNAL_DATA*)IDEPasswordGetDataPtr(Index);

    if (DataPtr == NULL) {
        return 0;
    }

    return DataPtr->PromptToken;
#endif
}
#endif

/** @internal
    Function Unlock the Hdd with Valid Password

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS       Hdd Unlocked successfully
    @retval EFI_NOT_FOUND     Hdd not found.

    @endinternal
**/
EFI_STATUS
IDEPasswordUpdateAllHddWithValidatedPsw (
    IN UINT8                *Password,
    IN VOID                 *Ptr,
    IN BOOLEAN              bCheckUser
)
{
#if ALL_HDD_SAME_PW
    HDD_SECURITY_INTERNAL_DATA      *DataPtr;
    UINTN                           Index;
    EFI_STATUS                      Status;
    CHAR16                          PassWordBuffer[IDE_PASSWORD_LENGTH + 1];

    //For all drives
    DataPtr = HddSecurityInternalData;

    if (DataPtr == NULL) {
        return EFI_NOT_FOUND;
    }

    for (Index = 0; Index < IDE_PASSWORD_LENGTH + 1; Index++) {
        PassWordBuffer[Index] = Password[Index];

        if ( Password[Index] == '\0' ) {
            break;
        }
    }

    for (Index = 0; Index < gHddSecurityCount; Index++) {

        if (DataPtr->Locked && !DataPtr->Validated) {

            DataPtr->Validated = TRUE;
            Status = IDEPasswordAuthenticateHdd ( 
                                            PassWordBuffer,
                                            DataPtr,
                                            bCheckUser );
            if (EFI_SUCCESS != Status) {
                // Unlock failed.
                REPORT_STATUS_CODE (
                                EFI_ERROR_CODE | EFI_ERROR_MAJOR,
                                DXE_INVALID_IDE_PASSWORD );
            }            
        }
        DataPtr++;
    }
#endif
    return EFI_SUCCESS;
}

/** @internal
    Validates the password for the current HDD alone.

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticateHdd (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
)
{
    UINT16              Control = 0;
    EFI_STATUS          Status;
    UINT8               Buffer[IDE_PASSWORD_LENGTH + 1];

#if !SETUP_SAME_SYS_HDD_PW
    UINTN                       Index;
#endif
    HDD_SECURITY_INTERNAL_DATA  *DataPtr = (HDD_SECURITY_INTERNAL_DATA*)Ptr;

    ZeroMem (&Buffer, IDE_PASSWORD_LENGTH + 1);

#if defined(SETUP_PASSWORD_NON_CASE_SENSITIVE) && SETUP_PASSWORD_NON_CASE_SENSITIVE
    UpdatePasswordToNonCaseSensitive (Password, StrLen(Password));
#endif

#if !SETUP_SAME_SYS_HDD_PW

    for (Index = 0; Index < IDE_PASSWORD_LENGTH + 1; Index++) {
        Buffer[Index] = (UINT8)Password[Index];

        if (Password[Index] == L'\0') {
            break;
        }
    }
#else
    CopyMem (Buffer, Password, IDE_PASSWORD_LENGTH + 1);
#endif

    Control = bCheckUser ? 0 : 1;

    Status = (DataPtr->HddSecurityProtocol)->SecurityUnlockPassword (
                                                            DataPtr->HddSecurityProtocol,
                                                            Control,
                                                            Buffer );

    if (EFI_ERROR(Status)) {
        return EFI_ACCESS_DENIED;
    }

    //
    //save password in case we need to disable it during the setup
    //
    CopyMem (&(DataPtr->PWD), &Buffer, IDE_PASSWORD_LENGTH + 1);
    DataPtr->Locked = FALSE;

    if (!bCheckUser) {
        DataPtr->LoggedInAsMaster = TRUE;
    }

    return EFI_SUCCESS;
}

/** @internal
    Validates the password for all the HDDs Present.

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.
    
    @retval EFI_SUCCESS         Password for current HDD is validated successfully.
    @retval EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticateAllHdd (
    IN CHAR16               *Password,
    IN VOID                 *Ptr,
    IN BOOLEAN              bCheckUser
)
{
    HDD_SECURITY_INTERNAL_DATA  *DataPtr;
    UINTN                       Index;
    EFI_STATUS                  Status = EFI_NOT_FOUND;

    //For all drives
    //
    DataPtr = HddSecurityInternalData;

    if (DataPtr == NULL) {
        return EFI_NOT_FOUND;
    }
        

    for (Index = 0; Index < gHddSecurityCount; Index++) {

        Status = IDEPasswordAuthenticateHdd (
                                        Password,
                                        DataPtr,
                                        bCheckUser );
        if (EFI_SUCCESS != Status) {
            //
            // Unlock failed.
            //
            REPORT_STATUS_CODE (
                            EFI_ERROR_CODE | EFI_ERROR_MAJOR,
                            DXE_INVALID_IDE_PASSWORD );
        }
        DataPtr++;
    }
    return Status;
}

/** @internal
    Hook function to validate Password for the HDDs based on
    the token ALL_HDD_SAME_PW

    @param *Password      Pointer to Password for security.
    @param *Ptr           Pointer to HDD_SECURITY_INTERNAL_DATA
    @param bCheckUser     Boolean value to check for user Password/Master Password.

    @return EFI_SUCCESS         Password for current HDD is validated successfully.
    @return EFI_ACCESS_DENIED   Access for HDD is denied.

    @endinternal
**/
EFI_STATUS
IDEPasswordAuthenticate (
    IN CHAR16           *Password,
    IN VOID             *Ptr,
    IN BOOLEAN          bCheckUser
)
{
#if ALL_HDD_SAME_PW
     return IDEPasswordAuthenticateAllHdd (Password, Ptr, bCheckUser);
#else
     return IDEPasswordAuthenticateHdd (Password, Ptr, bCheckUser);
#endif

}

/** @internal
    Get the internal Data pointer

    @param Index       Index of HDD

    @return VOID

    @endinternal
**/
VOID *
IDEPasswordGetDataPtr (
    IN UINTN                Index
)
{
    HDD_SECURITY_INTERNAL_DATA  *DataPtr;

    if ((gHddSecurityCount == 0) || (HddSecurityInternalData == NULL)) {
        //try to initialize, if not initialized
        gHddSecurityCount = InitHddSecurityInternalDataPtr();
    }

   if ((gHddSecurityCount == 0) || (HddSecurityInternalData == NULL) || (Index >= gHddSecurityCount)) {
        return NULL;
    }

    DataPtr = (HDD_SECURITY_INTERNAL_DATA *)HddSecurityInternalData;

    return (VOID *)&DataPtr[Index];
}

#if defined(SETUP_IDE_SECURITY_SUPPORT) && SETUP_IDE_SECURITY_SUPPORT
#if defined(SECURITY_SETUP_ON_SAME_PAGE) && SECURITY_SETUP_ON_SAME_PAGE
/** @internal
    Function to update the HDD password

    @param *control        Selected password control data
    @param *saveData       New password

    @retval EFI_SUCCESS        HDD password updated successfully
    @retval EFI_UNSUPPORTED    HDD password not updated.

    @endinternal
**/
EFI_STATUS
FramePwdCallbackIdePasswordUpdate (
    IN CONTROL_DATA                 *control,
    IN CHAR16                       *saveData
)
{
    BOOLEAN                 bCheckUser = FALSE;
    VOID                    *data = control->ControlData.ControlPtr;
    UINT8                   HardDiskNumber = 0xFF;

    // Check whether selected password control is a HDD Password control
    if (control->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY) {
        // find index of currently selected HDD and type of password(user/master) to update
        SearchTseHardDiskField (&bCheckUser, NULL, &HardDiskNumber, data);

        if (HardDiskNumber != 0xFF) {// If HDD index is valid
            IDEPasswordUpdate ((UINT32)HardDiskNumber, (CHAR16*) saveData, bCheckUser); //update it
        }
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
}

/** @internal
    Function to authenticate the HDD password

    @param *popuppassword      Pointer to POPUP_PASSWORD_DATA  
    @param *AbortUpdate        Pointer to Password update
                               0 - Password updated
                               1 - Password not updated
    @param *data               Pointer to data

    @retval EFI_SUCCESS        Password authentication success
    @retval EFI_NOT_FOUND      Data not found
    @retval EFI_UNSUPPORTED    The operation is not supported.

    @endinternal
**/
EFI_STATUS
PopupPwdAuthenticateIDEPwd (
    IN POPUP_PASSWORD_DATA          *popuppassword,
    IN BOOLEAN                      *AbortUpdate,
    IN VOID                         *data
)
{
    EFI_STATUS                  Status;
    CHAR16                      *Text=NULL;
    UINT8                       HardDiskNumber = 0xFF;

    // Check whether selected password control is a HDD Password control
    if (popuppassword->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY) {
        BOOLEAN             bCheckUser = FALSE;
        BOOLEAN             EnabledBit = FALSE;
        UINTN               size = 0;
        IDE_SECURITY_CONFIG *ideSecConfig;

        ideSecConfig = VarGetVariable (VARIABLE_ID_IDE_SECURITY, &size); // Get the data from setup page
        if (NULL == ideSecConfig) {
            return EFI_NOT_FOUND;
        }
    // find index of currently selected HDD and type of password(user/master) to authenticate
        SearchTseHardDiskField (&bCheckUser, &EnabledBit, &HardDiskNumber, data);
        // Check if password has been set for selected HDD
        if ((HardDiskNumber != 0xFF )  && ideSecConfig->Enabled[HardDiskNumber]) {
                EnabledBit = TRUE;
        }

        // If password has been set then proceed
        if (EnabledBit) {
            if (bCheckUser || ideSecConfig->MasterPasswordStatus[HardDiskNumber]) {
                // Ask for the password
                Status = _DoPopupEdit (popuppassword, STRING_TOKEN(STR_OLD_PSWD), &Text);
                if (EFI_SUCCESS != Status) {
                    *AbortUpdate = TRUE; // Status: Password not updated
                } else {
                    // Get AMI_HDD_SECURITY_PROTOCOL instance for current HDD
                    void* DataPtr = TSEIDEPasswordGetDataPtr (HardDiskNumber);
                    Status = TSEIDEPasswordAuthenticate (Text, DataPtr, bCheckUser); //Authenticate it
                    if (EFI_ERROR(Status)) {
                        // Show error message if password is wrong
                        CallbackShowMessageBox ((UINTN)gInvalidPasswordFailMsgBox, MSGBOX_TYPE_OK);
                        *AbortUpdate = TRUE; // Status: Password not updated
                    }
                    StringZeroFreeMemory ((VOID **)&Text); // Erase string and free allocated memory
                }
            }
        }

        FreePool (ideSecConfig); // Free setup data memory
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

/** @internal
    Function to report status of HDD password

    @param *popuppassword        Pointer to POPUP_PASSWORD_DATA

    @retval EFI_SUCCESS        Status reported successfully
    @retval EFI_NOT_FOUND      Data not found
    @retval EFI_UNSUPPORTED    The operation is not supported.
   
    @endinternal
**/
EFI_STATUS
CheckForIDEPasswordInstalled (
    IN POPUP_PASSWORD_DATA          *popuppassword
)
{
    UINT8               HardDiskNumber = 0xFF;
    VOID                *data = popuppassword->ControlData.ControlPtr;
    
    // Check whether selected password control is a HDD Password control
    if (popuppassword->ControlData.ControlVariable == VARIABLE_ID_IDE_SECURITY) {
        BOOLEAN             bCheckUser = FALSE;
        BOOLEAN             EnabledBit = FALSE;
        UINTN               size = 0;
        IDE_SECURITY_CONFIG *ideSecConfig;

        ideSecConfig = VarGetVariable (VARIABLE_ID_IDE_SECURITY, &size); // Get the data from setup page
        if (NULL == ideSecConfig) {
            return EFI_NOT_FOUND;
        }
    // find index of currently selected HDD and type of password(user/master) to authenticate
        SearchTseHardDiskField (&bCheckUser, &EnabledBit, &HardDiskNumber, data);
        // Check if password has been set for selected HDD
        if ((HardDiskNumber != 0xFF)  && ideSecConfig->Enabled[HardDiskNumber]) {
            EnabledBit = TRUE;
        }

        // If password has been set then proceed
        if (EnabledBit) {
            if (bCheckUser || ideSecConfig->MasterPasswordStatus[HardDiskNumber]) {
                FreePool (ideSecConfig); // Free setup data memory
                return EFI_SUCCESS;
            }
        }

        FreePool (ideSecConfig); // Free setup data memory
    }
    
    return EFI_UNSUPPORTED;
}

/** @internal
    Function to update the setup configure page after HDD password update

    @param VOID

    @return VOID
    
    @endinternal
**/

VOID
PopupPwdUpdateIDEPwd ()
{
    UINTN                   size = 0;
    IDE_SECURITY_CONFIG     *HddSecurityConfig;
    UINT8                   HardDiskNumber = 0xFF;

    // Get the old setup configure data
    HddSecurityConfig = VarGetVariable (VARIABLE_ID_IDE_SECURITY, &size);
    if (NULL == HddSecurityConfig) {
        return;
    }
    // Update setup data for all HDDs
    for (HardDiskNumber = 0; HardDiskNumber < HddSecurityConfig->Count; HardDiskNumber++) {
        IDEUpdateConfig ((VOID*)HddSecurityConfig, HardDiskNumber);
    }
    // Set the new setup configure data
    VarSetValue (VARIABLE_ID_IDE_SECURITY, 0, size, HddSecurityConfig);
    if (gApp != NULL)
    gApp->CompleteRedraw = TRUE; // redraw setup configure page to reflect updated configuration
    FreePool (HddSecurityConfig);
}

/** @internal
    Function to search TSE hard disk field.

    @param *pbCheckUser       Password type - User/Master
    @param *pEnabledBit       Password is set/not
    @param *pHardDiskNumber   HDD index
    @param *data              Pointer to data.

    @return VOID
    @endinternal
**/
VOID
SearchTseHardDiskField (
    IN  OUT BOOLEAN         *pbCheckUser,
    IN  OUT BOOLEAN         *pEnabledBit,
    IN  OUT UINT8           *pHardDiskNumber,
    IN  VOID                *data
)
{
    UINTN                   size = 0;
    IDE_SECURITY_CONFIG     *HddSecurityConfig;

    HddSecurityConfig = VarGetVariable (VARIABLE_ID_IDE_SECURITY, &size);

    // Check if User password field is selected, if yes then set HDD index
    if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword)) {
        *pHardDiskNumber = 0;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword_HDD2)) {
        *pHardDiskNumber = 1;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword_HDD3)) {
        *pHardDiskNumber = 2;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword_HDD4)) {
        *pHardDiskNumber = 3;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword_HDD5)) {
        *pHardDiskNumber = 4;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEUserPassword_HDD6)) {
        *pHardDiskNumber = 5;
        *pbCheckUser = TRUE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword)) {
        // Check if Master password field is selected, if yes then set HDD index
        *pHardDiskNumber = 0;
        *pbCheckUser = FALSE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword_HDD2)) {
        *pHardDiskNumber = 1;
        *pbCheckUser = FALSE;
    } else if (UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword_HDD3)) {
        *pHardDiskNumber = 2;
        *pbCheckUser = FALSE;
    } else if( UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword_HDD4)) {
        *pHardDiskNumber = 3;
        *pbCheckUser = FALSE;
    } else if( UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword_HDD5)) {
        *pHardDiskNumber = 4;
        *pbCheckUser = FALSE;
    } else if( UefiGetQuestionOffset(data) == STRUCT_OFFSET(IDE_SECURITY_CONFIG,IDEMasterPassword_HDD6)) {
        *pHardDiskNumber = 5;
        *pbCheckUser = FALSE;
    } else {
        // Question offset is not from any of the password fields
        *pHardDiskNumber = 0xFF; // No HDD selected
        if (pEnabledBit != NULL) {
                *pEnabledBit = FALSE; // No HDD ie no password is set
        }
    }
    // if HDD index is invalid, set it to 0xFF
    if (*pHardDiskNumber >= HddSecurityConfig->Count) {
        *pHardDiskNumber = 0xFF;
    }

    FreePool (HddSecurityConfig);
}
#endif
#endif

/** @internal
    Returns EFI_SUCCESS and sets *bHddStatus = TRUE if number of
    attempt to unlock HDD has reached MAXIMUM_HDD_UNLOCK_ATTEMPTS.

    @param *DataPtr       Pointer to HDD_SECURITY_INTERNAL_DATA
    @param *bHddStatus    Pointer to HDD status 
                          0 - number of attempt to unlock HDD has not reached MAXIMUM_HDD_UNLOCK_ATTEMPTS.
                          1 - number of attempt to unlock HDD has reached MAXIMUM_HDD_UNLOCK_ATTEMPTS.
                          
    @retval EFI_SUCCESS    HDD unlocked successfully.
    @return Other          Return error status.
    
    @endinternal
**/

EFI_STATUS
HDDStatus (
    IN VOID             *DataPtr,         
    IN BOOLEAN          *bHddStatus        
)
{
    EFI_STATUS                   Status = 0;
    UINT16                       SecurityStatus = 0;
    HDD_SECURITY_INTERNAL_DATA   *Ptr = (HDD_SECURITY_INTERNAL_DATA *)DataPtr;

    *bHddStatus = FALSE;

    Status = Ptr->HddSecurityProtocol->ReturnSecurityStatus (
                                                    Ptr->HddSecurityProtocol, 
                                                    &SecurityStatus );
    if (EFI_ERROR(Status))
        return Status;

    if (SecurityStatus & 0x10) {
        *bHddStatus = TRUE;
        DEBUG((DEBUG_VERBOSE, "HddSecurity: %a HDD unlock attempts reached maximum\n",__FUNCTION__));
    }

    return EFI_SUCCESS;
}

#if !defined(SETUP_IDE_SECURITY_SUPPORT) || SETUP_IDE_SECURITY_SUPPORT == 0
extern BOOLEAN      gBrowserCallbackEnabled;
EFI_GUID            gHddSecurityLoadSetupDefaultsGuid = AMI_HDD_SECURITY_LOAD_SETUP_DEFAULTS_GUID;
EFI_EVENT           gHddSecurityLoadSetupDefaultsEvent = NULL;

/** 
    Notification function for "Load Default" action in BIOS setup. This function
    will re-initialize the HDD security setup data.

    @param Event       Event to signal
    @param *Context    Event specific context

    @return VOID

**/
VOID
EFIAPI
HddSecurityLoadSetupDefaultsFunc (
    IN EFI_EVENT            Event,
    IN VOID                 *Context
)
{
    //pBS->CloseEvent(Event);
}

/** @internal
    Notification function for "Load Default" action in BIOS setup. This function
    will re-initialize the HDD security setup data.
    
    @return VOID
    
    @endinternal
**/
VOID
HddSecurityLoadSetupDefaults (
    IN VOID             *defaults,
    IN UINTN            data 
)
{
    EFI_STATUS          Status;
    
    if (gHddSecurityLoadSetupDefaultsEvent == NULL) {
        Status = gBS->CreateEventEx (
                                EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                HddSecurityLoadSetupDefaultsFunc,
                                NULL,
                                &gHddSecurityLoadSetupDefaultsGuid,
                                &gHddSecurityLoadSetupDefaultsEvent);
        if (EFI_ERROR(Status)) {
            return;
        }
    }
    gBrowserCallbackEnabled = TRUE;
    gBS->SignalEvent (gHddSecurityLoadSetupDefaultsEvent);
    gBrowserCallbackEnabled = FALSE;
}

#endif

