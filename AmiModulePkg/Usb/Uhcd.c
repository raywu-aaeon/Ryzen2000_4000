//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Uhcd.c
    AMI USB Host Controller Driver

**/

#include <Token.h>
#include <Setup.h>
#include "Uhcd.h"
#include "UsbBus.h"
#include "EfiUsbKb.h"
#include "ComponentName.h"
#include <Protocol/Emul6064Trap.h>
#include <UsbDevDriverElinks.h>
#include <Protocol/LegacyBiosPlatform.h>
#include <Protocol/AmiUsbHid.h>
#include <Protocol/IoMmu.h>
#include <IndustryStandard/Pci.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Acpi10.h>
#include <Library/TimerLib.h>
#include <Library/AmiUsbHcdLib.h>
#include <Library/PerformanceLib.h>
#include <Xhci.h>
#if defined(CSM_SUPPORT) && CSM_SUPPORT
#include <Protocol/LegacyBiosExt.h>
#ifndef LTEB_GUID
#define LTEB_GUID  \
    {0xC8BCA618, 0xBFC6, 0x46B7, { 0x8D, 0x19, 0x83, 0x14, 0xE2, 0xE5, 0x6E, 0xC1 }}  // LTEB_GUID as defined Csm.c
#endif
#endif

#include "UsbIrq.h"
#include "AmiUsb.h"
EFI_STATUS EFIAPI SettingTimerSMI(IN BOOLEAN EnableSmi);
EFI_STATUS EFIAPI GetSmiSource(IN UINT8 *SmiSource);

extern VOID *gStartPointer;
extern VOID *gEndPointer;
extern EFI_EVENT gEvUsbEnumTimer;
extern UINTN *gCoreStackBuffer;
extern HCD_HEADER *gDxeUsbHcdTable;

const HC_SPECIFIC_INFO gHCSpecificInfo[4] = {
{EFI_PCI_IO_ATTRIBUTE_IO | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER    , USB_UHCI_FRAME_LIST_SIZE, USB_UHCI_FRAME_LIST_ALIGNMENT, DummyHcFunc, DummyHcFunc},  // UHCI
{EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER, USB_OHCI_FRAME_LIST_SIZE, USB_OHCI_FRAME_LIST_ALIGNMENT, DummyHcFunc, DummyHcFunc},  // OHCI
{EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER, USB_EHCI_FRAME_LIST_SIZE, USB_EHCI_FRAME_LIST_ALIGNMENT, PreInitEhci, PostStopEhci}, // EHCI
{EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER, USB_XHCI_FRAME_LIST_SIZE, USB_XHCI_FRAME_LIST_ALIGNMENT, PreInitXhci, PostStopXhci}, // XHCI
};

USB_GLOBAL_DATA             *gUsbData = NULL;
EFI_USB_PROTOCOL            *gAmiUsbController = NULL;
EFI_USB_POLICY_PROTOCOL     gEfiUsbPolicyProtocol;    //(EIP99882+)
BOOLEAN                     gIntTimerLock    = FALSE;

EFI_DRIVER_BINDING_PROTOCOL gAmiUsbDriverBinding = {
    AmiUsbDriverBindingSupported,
    AmiUsbDriverBindingStart,
    AmiUsbDriverBindingStop,
    USB_DRIVER_VERSION,
    NULL,
    NULL
};

EFI_EMUL6064TRAP_PROTOCOL   *gEmulationTrap = 0;
BOOLEAN                     gLegacyUsbStatus=TRUE;
EFI_EVENT                   gUsbIntTimerEvt = NULL;

                                                                                //(EIP71750+)>
typedef EFI_STATUS USB_DEV_EFI_DRIVER_CHECK (EFI_HANDLE, EFI_HANDLE);
extern USB_DEV_EFI_DRIVER_CHECK USB_DEV_EFI_DRIVER EndOfUsbDevEfiDriverList;
USB_DEV_EFI_DRIVER_CHECK* gUsbDevEfiDrivers[]= {USB_DEV_EFI_DRIVER NULL};
                                                                                //<(EIP71750+)
SPECIFIC_USB_CONTROLLER gSpecificControllers[MAX_SPECIFIC_USB_CONTROLLER_COUNT];
AMI_USB_ISR_PROTOCOL    *gAmiUsbIsrProtocol = NULL;

USB_DATA_LIST           *gUsbDataList = NULL;
URP_STRUC               *gParameters = NULL;
HC_STRUC                **gHcTable;
UINT8                   gCurrentDevLink = 0;
QUEUE_T                 gQueueCnnctDisc;
EDKII_IOMMU_PROTOCOL    *gIoMmuProtocol = NULL;
UINT8                   gDisableTimerSmi = FALSE;

EFI_MEMORY_TYPE         gAllocateMemType = EfiRuntimeServicesData;
/**
    This function is a part of binding protocol, it returns
    the string "USB Host Controller".

    @param  ControllerHandle  The handle of a controller that the driver
                              specified by This is managing.  This handle
                              specifies the controller whose name is to be
                              returned.

    @param  ChildHandle       The handle of the child controller to retrieve
                              the name of.  This is an optional parameter that
                              may be NULL.  It will be NULL for device
                              drivers.  It will also be NULL for a bus drivers
                              that wish to retrieve the name of the bus
                              controller.  It will not be NULL for a bus
                              driver that wishes to retrieve the name of a
                              child controller.
    @retval Pointer           Ptr to string pointer.

**/

CHAR16*
AmiUsbDriverGetControllerName(
    EFI_HANDLE  Controller,
    EFI_HANDLE  Child
)
{
    EFI_STATUS            Status;
    EFI_PCI_IO_PROTOCOL   *PciIo;
    HC_STRUC              *HcStruc = NULL;
    UINT8                 PciCfg[0x40];

    if (Child != NULL) {
        return NULL;
    }

    HcStruc = FindHcStruc(Controller);

    if (HcStruc != NULL) {
        PciIo = (EFI_PCI_IO_PROTOCOL*)HcStruc->PciIo;
        if (PciIo != NULL) {
            Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof(PciCfg),
                          PciCfg);
            if (EFI_ERROR(Status) ||
                (!(PciCfg[0xB] == PCI_CLASSC_BASE_CLASS_SERIAL) && (PciCfg[0xA] == PCI_CLASSC_SUBCLASS_SERIAL_USB)))
                return L"AMI USB Host Controller";

            if (PciCfg[0x9] == PCI_CLASSC_PI_UHCI)
                return L"AMI USB Host Controller(UHCI)";

            if (PciCfg[0x9] == PCI_CLASSC_PI_OHCI)
                return L"AMI USB Host Controller(OHCI)";

            if (PciCfg[0x9] == PCI_CLASSC_PI_EHCI)
                return L"AMI USB Host Controller(EHCI)";

            if (PciCfg[0x9] == PCI_CLASSC_PI_XHCI)
                return L"AMI USB Host Controller(XHCI)";
        }
    }
    return NULL;
}

/**
    Usb timer interrupt call back routine

    @param  Event       - Efi event occurred upon IntTimer
    @param  Context     - Not used

    @retval None

**/

VOID
EFIAPI
UsbIntTimerCallback (
    EFI_EVENT    Event,
    VOID         *Context
)
{
    EFI_TPL     OriginalTPL;
    HC_STRUC    *HcStruc;
    UINT8       Index;
    BOOLEAN     Lock;

    if (!(gUsbData->UsbStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {
        return;
    }

    ATOMIC({Lock = gIntTimerLock; gIntTimerLock = TRUE;});

    if (Lock) {
        return;
    }
    
    OriginalTPL = gBS->RaiseTPL (TPL_NOTIFY);

    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
        HcStruc = gHcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (HcStruc->HcFlag & HC_STATE_RUNNING) {
            // Process appropriate interrupt
            AmiUsbProcessInterrupt(HcStruc);
        }
    }
    gIntTimerLock = FALSE;

    gBS->RestoreTPL (OriginalTPL);
}

/**
    This function add/delete the node in DList. The node recode device vendor ID(VID), device ID(DID) 
    and which configuration is the device needed. When new node's VID and DID exist in DList, it will
    delete the old one first then add new node.

    @param  This              A pointer to the EFI_USB_POLICY_PROTOCOL instance.
    @param  DevConfigInfo     A pointer to the USB_DEV_CONFIG_INFO instance.

    @retval EFI_SUCCESS       Succes to config number policy

**/
EFI_STATUS
EFIAPI
UsbDevConfigNumPolicy (
    IN EFI_USB_POLICY_PROTOCOL    *This,
    IN USB_DEV_CONFIG_INFO        *DevConfigInfo
)
{
    LIST_ENTRY          *Link = NULL;
    USB_DEV_CONFIG_LINK *ReadDevConfigLink = NULL;
    UINT8               DevConfigMatch = FALSE;

    if (gCurrentDevLink==MAX_DEV_CONFIG_LINK) return EFI_OUT_OF_RESOURCES;

    for (Link = gUsbData->DevConfigInfoList.ForwardLink;
        Link != (VOID*)&gUsbData->DevConfigInfoList; 
        Link = Link->ForwardLink ) {
        ReadDevConfigLink = BASE_CR(Link, USB_DEV_CONFIG_LINK, Link);
        if (ReadDevConfigLink->DevConfigInfo.Vid == DevConfigInfo->Vid) {
            if (ReadDevConfigLink->DevConfigInfo.Did == DevConfigInfo->Did) {
                CopyMem(&ReadDevConfigLink->DevConfigInfo, DevConfigInfo, sizeof(USB_DEV_CONFIG_INFO));
                DevConfigMatch = TRUE;
                break;
            }
        }  
    }

    if (DevConfigMatch==FALSE){
        if (gCurrentDevLink >= MAX_DEV_CONFIG_LINK) return EFI_OUT_OF_RESOURCES;
        CopyMem(&gUsbData->DevConfigLink[gCurrentDevLink].DevConfigInfo, DevConfigInfo, sizeof(USB_DEV_CONFIG_INFO));
        InsertTailList((VOID*)&gUsbData->DevConfigInfoList, &gUsbData->DevConfigLink[gCurrentDevLink].Link);
        gCurrentDevLink++;
    }

    return EFI_SUCCESS;
}

/**
  This function is call to allocate USB memory.

  @param  MemPages       Memory size in Page.

  @retval EFI_SUCCESS           Succes to allocate system memory.
  @retval EFI_OUT_OF_RESOURCES  Fail to allocate system memory.

**/
EFI_STATUS
EFIAPI
AllocateUsbMemory(
    IN    UINT32    MemPages
)
{
    UINT64    Index;
    UINT32    UsbDataSize;
    VOID      *UsbDataAddress;
    UINT8     *UsbTempBuffer = NULL;
    UINT8     *MemBlockStart = NULL;
    UINT8     *UsbMassConsumeBuffer = NULL;
    UINT32    SkipTabSize;
    UINT8     MaxHidCount;
    UINT8     MaxHubCount;
    UINT8     MaxMassCount;
    UINT8     UnsupportedDevCount;
    UINT8     MaxDevCount;
    UINT32    KbDevTabSize;
    UINT32    MaxDevTabSize;

    SkipTabSize = (UINT32)PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxSkipTableCount);
    SkipTabSize = ((SkipTabSize + 1) * sizeof(USB_SKIP_LIST));

    MaxHidCount            = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxHidDevCount);
    MaxHubCount            = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxHubDevCount);
    MaxMassCount           = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxMassDevCount);
    UnsupportedDevCount    = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxUnsupportedDevCount);

    MaxDevCount = MaxHidCount + MaxHubCount + MaxMassCount + UnsupportedDevCount;
    KbDevTabSize = MaxHidCount * sizeof(DEV_INFO*);
    MaxDevTabSize = MaxDevCount * sizeof(DEV_INFO);

    UsbDataSize = TOTAL_USB_DATA_SIZE + SkipTabSize + KbDevTabSize + MaxDevTabSize;
    UsbDataSize += MemPages << 12;
    UsbDataSize += ((MemPages << 12 / sizeof(MEM_BLK)) / 8);
                  
    // Allocate USB memory (First allocate aligned memory)
    // Can't use AllocAlignedMemory before this.
    UsbDataAddress = AllocAlignedMemory (UsbDataSize, 0x10);
    if (UsbDataAddress == NULL) return EFI_OUT_OF_RESOURCES;

    // Allocate memory for the pool and store it in global data
    MemBlockStart = AllocAlignedMemory(((MemPages << 12) + MAX_CONSUME_BUFFER_SIZE), 0x1000);
    if (MemBlockStart == NULL) return EFI_OUT_OF_RESOURCES; 

    // Allocate a block of memory to be used as a temporary
    // buffer for  USB mass transfer
    UsbMassConsumeBuffer = (UINT8*)((UINTN)MemBlockStart + (MemPages << 12));
    if (UsbMassConsumeBuffer == NULL) return EFI_OUT_OF_RESOURCES; 

    // Allocate a block of memory for the temporary buffer
    UsbTempBuffer = (UINT8*)AllocAlignedMemory (MAX_TEMP_BUFFER_SIZE, 0x1000);
    if (UsbTempBuffer == NULL) return EFI_OUT_OF_RESOURCES; 

    Index = GetPerformanceCounter();
    Index &= 0xf;

    switch (Index) {
        case 0:
        case 1:
        case 2:
               // Init gUsbDataList
               gUsbDataList = (USB_DATA_LIST*)AllocAlignedMemory (sizeof(USB_DATA_LIST), 0x10);
               if (gUsbDataList == NULL) return EFI_OUT_OF_RESOURCES;

               // Allocate USB protocol
               gAmiUsbController = (EFI_USB_PROTOCOL*)AllocAlignedMemory (sizeof(EFI_USB_PROTOCOL), 0x10);
               if (gAmiUsbController == NULL) return EFI_OUT_OF_RESOURCES;

               // Init USB URP
               gParameters = (URP_STRUC*)AllocAlignedMemory (sizeof(URP_STRUC), 0x10);
               if (gParameters == NULL) return EFI_OUT_OF_RESOURCES;        

               // Allocate and initialize USB memory
               gUsbData = (USB_GLOBAL_DATA*)AllocAlignedMemory (sizeof(USB_GLOBAL_DATA), 0x10);
               if (gUsbData == NULL) return EFI_OUT_OF_RESOURCES;
               break;
        case 3:
        case 4:
        case 5:
               // Init gUsbDataList
               gUsbDataList = (USB_DATA_LIST*)AllocAlignedMemory (sizeof(USB_DATA_LIST), 0x10);
               if (gUsbDataList == NULL) return EFI_OUT_OF_RESOURCES;

               // Allocate and initialize USB memory
               gUsbData = (USB_GLOBAL_DATA*)AllocAlignedMemory (sizeof(USB_GLOBAL_DATA), 0x10);
               if (gUsbData == NULL) return EFI_OUT_OF_RESOURCES;

               // Allocate USB protocol
               gAmiUsbController = (EFI_USB_PROTOCOL*)AllocAlignedMemory (sizeof(EFI_USB_PROTOCOL), 0x10);
               if (gAmiUsbController == NULL) return EFI_OUT_OF_RESOURCES;

               // Init USB URP
               gParameters = (URP_STRUC*)AllocAlignedMemory (sizeof(URP_STRUC), 0x10);
               if (gParameters == NULL) return EFI_OUT_OF_RESOURCES;
               break;
        case 6:
        case 7:
        case 8:

               // Init USB URP
               gParameters = (URP_STRUC*)AllocAlignedMemory (sizeof(URP_STRUC), 0x10);
               if (gParameters == NULL) return EFI_OUT_OF_RESOURCES;

               // Init gUsbDataList
               gUsbDataList = (USB_DATA_LIST*)AllocAlignedMemory (sizeof(USB_DATA_LIST), 0x10);
               if (gUsbDataList == NULL) return EFI_OUT_OF_RESOURCES;

               // Allocate and initialize USB memory
               gUsbData = (USB_GLOBAL_DATA*)AllocAlignedMemory (sizeof(USB_GLOBAL_DATA), 0x10);
               if (gUsbData == NULL) return EFI_OUT_OF_RESOURCES;

               // Allocate USB protocol
               gAmiUsbController = (EFI_USB_PROTOCOL*)AllocAlignedMemory (sizeof(EFI_USB_PROTOCOL), 0x10);
               if (gAmiUsbController == NULL) return EFI_OUT_OF_RESOURCES;
               break;
        case 9:
        case 10:
        case 11:
               // Allocate USB protocol
               gAmiUsbController = (EFI_USB_PROTOCOL*)AllocAlignedMemory (sizeof(EFI_USB_PROTOCOL), 0x10);
               if (gAmiUsbController == NULL) return EFI_OUT_OF_RESOURCES;

               // Init USB URP
               gParameters = (URP_STRUC*)AllocAlignedMemory (sizeof(URP_STRUC), 0x10);
               if (gParameters == NULL) return EFI_OUT_OF_RESOURCES; 
               
               // Allocate and initialize USB memory
               gUsbData = (USB_GLOBAL_DATA*)AllocAlignedMemory (sizeof(USB_GLOBAL_DATA), 0x10);
               if (gUsbData == NULL) return EFI_OUT_OF_RESOURCES;      

               // Init gUsbDataList
               gUsbDataList = (USB_DATA_LIST*)AllocAlignedMemory (sizeof(USB_DATA_LIST), 0x10);
               if (gUsbDataList == NULL) return EFI_OUT_OF_RESOURCES;
               break;       

        default:
               // Allocate and initialize USB memory
               gUsbData = (USB_GLOBAL_DATA*)AllocAlignedMemory (sizeof(USB_GLOBAL_DATA), 0x10);
               if (gUsbData == NULL) return EFI_OUT_OF_RESOURCES; 

               // Init gUsbDataList
               gUsbDataList = (USB_DATA_LIST*)AllocAlignedMemory (sizeof(USB_DATA_LIST), 0x10);
               if (gUsbDataList == NULL) return EFI_OUT_OF_RESOURCES;

               // Init USB URP
               gParameters = (URP_STRUC*)AllocAlignedMemory (sizeof(URP_STRUC), 0x10);
               if (gParameters == NULL) return EFI_OUT_OF_RESOURCES; 
               
               // Allocate USB protocol
               gAmiUsbController = (EFI_USB_PROTOCOL*)AllocAlignedMemory (sizeof(EFI_USB_PROTOCOL), 0x10);
               if (gAmiUsbController == NULL) return EFI_OUT_OF_RESOURCES;
               break;
    }

    gUsbDataList->UsbTempBuffer = UsbTempBuffer;
    gUsbDataList->MemBlockStart = MemBlockStart;
    gUsbDataList->UsbMassConsumeBuffer = UsbMassConsumeBuffer;

    // Allocate Timing Policy
    gUsbDataList->UsbTimingPolicy = (USB_TIMING_POLICY*)AllocAlignedMemory (sizeof(USB_TIMING_POLICY), 0x10);
    if (gUsbDataList->UsbTimingPolicy == NULL) return EFI_OUT_OF_RESOURCES; 

    // Allocate Usb Setup data
    gUsbDataList->UsbSetupData = (USB_SUPPORT_SETUP*)AllocAlignedMemory (sizeof(USB_SUPPORT_SETUP), 0x10);
    if (gUsbDataList->UsbSetupData == NULL) return EFI_OUT_OF_RESOURCES; 

    gUsbDataList->HcTable = (HC_STRUC**)AllocAlignedMemory ((sizeof(HC_STRUC*) * MAX_USB_HC), 0x10);
    if (gUsbDataList->HcTable == NULL) return EFI_OUT_OF_RESOURCES;
    gHcTable = gUsbDataList->HcTable;

    // Init Device table memory.
    gUsbData->MaxHidCount  = MaxHidCount;
    gUsbDataList->UsbKbDeviceTable = (DEV_INFO**)AllocAlignedMemory (KbDevTabSize, 0x10);
    if (gUsbDataList->UsbKbDeviceTable == NULL) return EFI_OUT_OF_RESOURCES;

    gUsbData->MaxHubCount  = MaxHubCount;
    gUsbData->MaxMassCount = MaxMassCount;
    
    gUsbData->MaxDevCount  = MaxDevCount;
    gUsbDataList->DevInfoTable = (DEV_INFO*)AllocAlignedMemory (MaxDevTabSize, 0x10);
    if (gUsbDataList->DevInfoTable == NULL) return EFI_OUT_OF_RESOURCES;
   
    gCoreStackBuffer = AllocAlignedMemory (MAX_USB_CORE_STACK_SIZE, 0x10);
    if (gCoreStackBuffer == NULL) return EFI_OUT_OF_RESOURCES;
   
    return EFI_SUCCESS;
}

/**
    This function is call to get PCD policy

    @param  None

    @retval None

**/

VOID
GetUsbPcdPolicy (VOID)
{
    UINT8    Count;
    UINT8    *UsbData;
    
    // Init Usb State flag   
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassEmulationForNoMedia)){
        gUsbData->UsbStateFlag |= USB_FLAG_MASS_EMULATION_FOR_NO_MEDIA;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbEfiMsDirectAccess)){
        gUsbData->UsbStateFlag |= USB_FLAG_EFIMS_DIRECT_ACCESS;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdSkipCardReaderConnectBeep)){
        gUsbData->UsbStateFlag |= USB_FLAG_SKIP_CARD_READER_CONNECT_BEEP;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbIsoctransferSupport)){
        gUsbData->UsbStateFlag |= USB_FLAG_USB_ISOCTRANSFER_SUPPORT;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbItdMemAllocForAllEhci)){
        gUsbData->UsbStateFlag |= USB_FLAG_ITD_MEM_ALLOC_FOR_ALL_EHCI;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbDcbaaMemAllocForAllXhci)){
        gUsbData->UsbStateFlag |= USB_FLAG_DCBAA_MEM_ALLOC_FOR_ALL_XHCI;
    }
    
    // Init Usb Feature Flag
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUhciSupport)){
        gUsbData->UsbFeature |= USB_HC_UHCI_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdOhciSupport)){
        gUsbData->UsbFeature |= USB_HC_OHCI_SUPPORT;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdEhciSupport)){
        gUsbData->UsbFeature |= USB_HC_EHCI_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdXhciSupport)){
        gUsbData->UsbFeature |= USB_HC_XHCI_SUPPORT;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdGpiDispatchByBitmap)){
        gUsbData->UsbFeature |= USB_GPI_DISPATCH_BY_BITMAP;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHotplugFddSupport)){
        gUsbData->UsbFeature |= USB_HOTPLUG_FDD_SUPPORT;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHotplugHddSupport)){
        gUsbData->UsbFeature |= USB_HOTPLUG_HDD_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHotplugCdromSupport)){
        gUsbData->UsbFeature |= USB_HOTPLUG_CDROM_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdDifferentiateMassDeviceName)){
        gUsbData->UsbFeature |= USB_DIFFERENTIATE_DEVICE_NAME;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdHideHispeedSetupQuestion)){
        gUsbData->UsbFeature |= USB_HIDE_HISPEED_SETUP_QUESTION;
    }
    
   if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdExternalUsbControllerSupport)){
        gUsbData->UsbFeature |= USB_EXTERNAL_CONTROLLER_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdSetupVariableRuntimeAccess)){
        gUsbData->UsbFeature |= USB_SETUP_VARIABLE_RUN_ACCESS;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbRegisterPeriodicTimerInDxe)){
        gUsbData->UsbFeature |= USB_REG_PERIODIC_TIMER_IN_DXE;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdStorageDeviceRmbCheck)){
        gUsbData->UsbFeature |= USB_MASS_STORAGE_DEV_RMB_CHECK;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbIrqSupport)){
        gUsbData->UsbFeature |= USB_IRQ_INTERRUPT_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbResetPortPolicy)){
        gUsbData->UsbFeature |= USB_HC_RESET_PORT_POLICY;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHostErrorsSupport)){
        gUsbData->UsbFeature |= USB_HC_SYSTEM_ERRORS_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMouseUpdateEbdaData)){
        gUsbData->UsbFeature |= USB_DEV_MOUSE_UPDATE_EBDA_DATA;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdEhci64bitDataStructure)){
        gUsbData->UsbFeature |= USB_EHCI_64_BIT_DATA_STRUCTURE;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdStartUnitBeforeMsdEnumeration)){
        gUsbData->UsbFeature |= USB_MASS_START_UNIT_BEFORE_MSD_ENUMERATION;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbBeepEnable)){
        gUsbData->UsbFeature |= USB_BEEP_SUPPORT;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdExtraCheckDeviceReady)){
        gUsbData->UsbFeature |= USB_EXTRA_CHECK_DEVICE_READY;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdHidKeyRepeatUseSetIdle)){
        gUsbData->UsbFeature |= USB_HID_USE_SETIDLE;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdBootProtocolSupport)){
        gUsbData->UsbFeature |= USB_BOOT_PROTOCOL_SUPPORT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdClearKbBufferAtReadyToBoot)){
        gUsbData->UsbFeature |= USB_CLEAR_USB_KB_BUFFER_AT_READYTOBOOT;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdSpecificEhciOwnershipChange)){
        gUsbData->UsbFeature |= USB_SPECIFIC_EHCI_OWNERSHIP_CHANGE_MECHANISM;
    }
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdLegacyUsbDisableForUsbMass)){
        gUsbData->UsbFeature |= USB_LEGACY_DISABLE_FOR_USB_MASS;
    }  

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdXhciComplianceMoedWorkrouund)){
        gUsbData->UsbFeature |= USB_XHCI_COMPLIANCE_MODE_WORKAROUND;
    } 

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdShowSkipPortInformation)){
        gUsbData->UsbFeature |= USB_SHOW_SKIP_PORT_INFORMATION;
    } 
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHcInterruptOutSupport)){
        gUsbData->UsbFeature |= USB_EFI_USB_HC_INTERRUPT_OUT_SUPPORT;
    } 
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbIadProtocolSupport)){
        gUsbData->UsbFeature |= USB_IAD_PROTOCOL;
    }     

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbGetBosDescSupport)){
        gUsbData->UsbFeature2 |= USB_GET_BOS_DESC_SUPPORT;
    }  
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdSkipUefiDriver)){
        gUsbData->UsbFeature2 |= USB_SKIP_UEFI_DRIVER;
    }  

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbDisconnectExitBootService)){
        gUsbData->UsbFeature2 |= USB_DISCONNECT_USBIO_EXIT_BOOT;
    } 
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbDebugMessages)){
        gUsbData->UsbFeature2 |= USB_DEBUG_SWITCH;
    }    
    
    //Init Usb device flag
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbKbdDevices)){
        gUsbData->UsbDevSupport |= USB_KB_DEV_SUPPORT;
    } 

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMouseDevices)){
        gUsbData->UsbDevSupport |= USB_MS_DEV_SUPPORT;
    } 

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbHubDevices)){
        gUsbData->UsbDevSupport |= USB_HUB_DEV_SUPPORT;
    } 
    
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassDevices)){
        gUsbData->UsbDevSupport |= USB_MASS_DEV_SUPPORT;
    } 

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbPointDevices)){
        gUsbData->UsbDevSupport |= USB_POINT_DEV_SUPPORT;
    }     
 
    // PcdGetEx8 
    gUsbData->XhciEventServiceMode  = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdXhciEventServiceMode);
    gUsbData->RepeatIntervalMode    = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdKeyrepeatInterval);
    gUsbData->MassStorageDeviceName = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdMassStorageDeviceName);
    gUsbData->UsbRuntimeDriverInSmm = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUsbRuntimeDriverInSmm);
    gUsbData->UsbSendCmdToKbc       = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUsbSendCommandToKbc);
    gUsbData->UsbSwSmi              = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUsbSwSmi);    
    
    // PcdGetEx16 
    gUsbData->FullSpeedMaxBulkDataSizePerFrame = PcdGetEx16(&gAmiUsbPkgTokenSpaceGuid,AmiPcdFullSpeedMaxBulkDataSizePerFrame);
    gUsbData->HighSpeedMaxBulkDataSize         = PcdGetEx16(&gAmiUsbPkgTokenSpaceGuid,AmiPcdHighSpeedMaxBulkDataSize);
    
    // PcdGetEx64
    gUsbData->InterruptPollingPeriod = PcdGetEx64(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUsbInterruptPollingPeriod);
    gUsbData->SizeForFloppyEmulation = PcdGetEx64(&gAmiUsbPkgTokenSpaceGuid,AmiPcdSizeForFloppyEmulation);
    gUsbData->UsbDbgMaskMap          = PcdGetEx64(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUsbDebugMessagesBitMap);
    
    //
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassNativeEmulation)){
        gUsbData->UsbStateFlag |= USB_FLAG_MASS_NATIVE_EMULATION;
    }else if (PcdGetExBool(&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassSizeEmulation)) {        
        gUsbData->UsbStateFlag |= USB_FLAG_MASS_SIZE_EMULATION;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassMediaCheck)) {
        gUsbData->UsbStateFlag |= USB_FLAG_MASS_MEDIA_CHECK;
        if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMassSkipFddMediaCheck))
            gUsbData->UsbStateFlag |= USB_FLAG_MASS_SKIP_FDD_MEDIA_CHECK;
    }
  
    if (gUsbData->RepeatIntervalMode){
        gUsbData->UsbKbcStatusFlag |= ((PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdKeyRepeatDelay) << KBC_TYPE_RATE_BIT_SHIFT_16MS) +
                                       (PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdKeyRepeatInitialDelay) << KBC_TYPE_DELAY_BIT_SHIFT_16MS));
    } else {
        gUsbData->UsbKbcStatusFlag |= ((PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdKeyRepeatDelay) << KBC_TYPE_RATE_BIT_SHIFT_8MS) +
                                       (PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdKeyRepeatInitialDelay) << KBC_TYPE_DELAY_BIT_SHIFT_8MS));    
    }

    // Init Specifc Usb Controller table.
    UsbData = (UINT8*)PcdGetExPtr (&gAmiUsbPkgTokenSpaceGuid, AmiPcdSpecificController);
    SetMem(gSpecificControllers, sizeof(SPECIFIC_USB_CONTROLLER)*MAX_SPECIFIC_USB_CONTROLLER_COUNT, 0);
    Count = *UsbData;
    UsbData++;
    ASSERT(Count<=MAX_SPECIFIC_USB_CONTROLLER_COUNT);
    if (Count > MAX_SPECIFIC_USB_CONTROLLER_COUNT) Count = MAX_SPECIFIC_USB_CONTROLLER_COUNT;
    if (Count) CopyMem(gSpecificControllers, UsbData, sizeof(SPECIFIC_USB_CONTROLLER)*Count);


    // Init SmiPinTable Controller table.
    UsbData = (UINT8*)PcdGetExPtr (&gAmiUsbPkgTokenSpaceGuid, AmiPcdExtHwSmiPin);
    SetMem(&gUsbData->HwSmiPinTable, sizeof(UINT32) * MAX_SMI_PIN_TABLE_COUNT, 0xFF);
    Count = *UsbData;
    UsbData++;
    ASSERT(Count<=MAX_SMI_PIN_TABLE_COUNT);
    if (Count > MAX_SMI_PIN_TABLE_COUNT) Count = MAX_SMI_PIN_TABLE_COUNT;
    if (Count) CopyMem(&gUsbData->HwSmiPinTable, UsbData, sizeof(UINT32) * Count);

    // Init Usb Controller init delay list.
    UsbData = (UINT8*)PcdGetExPtr (&gAmiUsbPkgTokenSpaceGuid, AmiPcdControllersInitialDelayList);
    SetMem(&(gUsbDataList->UsbTimingPolicy->ControllersDelayList), 
            sizeof(CONTROLLERS_INITIAL_DELAY_LIST) * MAX_USB_CONTROLLER_DELAY_LIST_COUNT, 0);
    Count = *UsbData;
    UsbData++;
    ASSERT(Count<=MAX_USB_CONTROLLER_DELAY_LIST_COUNT);
    if (Count > MAX_USB_CONTROLLER_DELAY_LIST_COUNT) Count = MAX_USB_CONTROLLER_DELAY_LIST_COUNT;
    if (Count) CopyMem(&(gUsbDataList->UsbTimingPolicy->ControllersDelayList), 
                         UsbData, sizeof(CONTROLLERS_INITIAL_DELAY_LIST) * Count);

    // Init Bad device table table.
    UsbData = (UINT8*)PcdGetExPtr (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbBadDevices);
    SetMem(&gUsbData->UsbBadDevices, sizeof(USB_BADDEV_STRUC) * MAX_BAD_DEVICE_TABLE_COUNT, 0);
    Count = *UsbData;
    UsbData++;
    ASSERT(Count<=MAX_BAD_DEVICE_TABLE_COUNT);
    if (Count > MAX_BAD_DEVICE_TABLE_COUNT) Count = MAX_BAD_DEVICE_TABLE_COUNT;
    if (Count) CopyMem(&gUsbData->UsbBadDevices, UsbData, sizeof(USB_BADDEV_STRUC) * Count);

    // Performance measurement enable?
    if (PerformanceMeasurementEnabled ()) gUsbData->UsbFeature2 |= USB_PERFORMANCE_INFORMATION;
}
/**
    Entry point for AMI USB EFI driver
    @param  ImageHandle    The firmware allocated handle for the EFI image.
    @param  SystemTable    A pointer to the EFI System Table.

    @retval EFI_STATUS Status of the operation

**/

EFI_STATUS
EFIAPI
AmiUsbDriverEntryPoint(
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_HANDLE          UsbHandle = NULL;
    EFI_STATUS          Status;
    EFI_STATUS          SetupStatus;
    UINTN               VariableSize;
    USB_SUPPORT_SETUP   SetupData;
    EFI_EVENT           PciIoEvent;
    UINT8               DevDriverIndex;
    EFI_EVENT           ReadyToBootEvent;
    EFI_EVENT           EndOfDxeEvent;
    UINT32              DataSize;
    VOID                *PciIoNotifyReg = NULL;
    EFI_EVENT           LegacyBootEvent;
    EFI_EVENT           ExitBootServicesEvent;
    EFI_GUID            EfiSetupGuid = SETUP_GUID;
    VOID                *NonSmmEmul6064NotifyContext = NULL;
    VOID                *NonSmmEmul6064Registration = NULL;
    UINT32              MemPages;
    EFI_EVENT           AddUsbHcEvent;
    
    
    VariableSize = sizeof(USB_SUPPORT_SETUP);
    SetupStatus = gRT->GetVariable( L"UsbSupport", &EfiSetupGuid, NULL,
                        &VariableSize, &SetupData );

    if (SetupStatus == EFI_SUCCESS && SetupData.UsbMainSupport == 0) {
        InitUsbSetupVars(NULL);
        return EFI_UNSUPPORTED;
    }
    
#if defined(CSM_SUPPORT) && CSM_SUPPORT
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUseBsInUefi)){
        SETUP_DATA  SetupData2;
        VariableSize = sizeof(SETUP_DATA);
        SetupStatus = gRT->GetVariable( L"Setup", &EfiSetupGuid, NULL,
                        &VariableSize, &SetupData2 );

        if (!EFI_ERROR(SetupStatus)){
            if (SetupData2.CsmSupport == 0){
                gAllocateMemType = EfiBootServicesData;
            }
        }
    }
#else
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUseBsInUefi)){
        gAllocateMemType = EfiBootServicesData;
    }
#endif

    REPORT_STATUS_CODE(EFI_PROGRESS_CODE,DXE_USB_BEGIN);

    MemPages = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbMemPageCount);
    
    // Allocate USB memory
    Status = AllocateUsbMemory(MemPages);
    ASSERT_EFI_ERROR(Status);

    //
    // Initialize the state flag
    //
    gUsbData->UsbStateFlag = 0;

    gUsbData->DeviceAddressMap = (UINT64)(~BIT0);

    //
    // Enable beep message during device connect/disconnect
    //
    gUsbData->UsbStateFlag |= USB_FLAG_ENABLE_BEEP_MESSAGE;
    gUsbData->UsbStateFlag |= USB_FLAG_RUNNING_UNDER_EFI;

//    // Init USB URP
    gUsbDataList->UsbUrp = gParameters;
    
    InitializeListHead((VOID*)&gUsbData->DevConfigInfoList);

    // Get PCD Policy
    GetUsbPcdPolicy();

    gUsbData->ProcessingPeriodicList = TRUE;
    gUsbData->NumberOfFDDs = 0;
    gUsbData->NumberOfHDDs = 0;
    gUsbData->NumberOfCDROMs = 0;

    gQueueCnnctDisc.Data = (VOID*)gUsbDataList->QueueData;
    gQueueCnnctDisc.Maxsize = COUNTOF(gUsbDataList->QueueData);
    gQueueCnnctDisc.Head = 0;
    gQueueCnnctDisc.Tail = 0;

    Status = InitUsbSetupVars(gUsbData);
    ASSERT_EFI_ERROR(Status);
                                                                                //(EIP99882)>

    gEfiUsbPolicyProtocol.UsbDevPlcy = gUsbDataList->UsbSetupData;
    gEfiUsbPolicyProtocol.AmiUsbHwSmiHcTable.HcCount = 0;
    gEfiUsbPolicyProtocol.UsbDevConfigNumPolicy = UsbDevConfigNumPolicy;
    gEfiUsbPolicyProtocol.RegisterUsbSmiBeforeEndOfDxe = TRUE;
    
    // Install USB policy protocol
    Status = gBS->InstallProtocolInterface(
                      &ImageHandle,
                      &gEfiUsbPolicyProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &gEfiUsbPolicyProtocol
                      );

    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "UsbPolicyProtocol Install %r\n", Status);
    }
                                                                                //<(EIP99882)
    ASSERT_EFI_ERROR(Status);

    // Init Usb Timing Policy
    gUsbDataList->UsbTimingPolicy->UsbTimingPolicyRevision = 01;
    gUsbDataList->UsbTimingPolicy->UsbTimingPolicyLength = 14;
    gUsbDataList->UsbTimingPolicy->EhciPortPowerOnDelay = 100;
    gUsbDataList->UsbTimingPolicy->EhciPortConnect = 20;
    gUsbDataList->UsbTimingPolicy->EhciPortReset = 50;
    gUsbDataList->UsbTimingPolicy->OhciHcResetDelay= 10;
    gUsbDataList->UsbTimingPolicy->OhciPortEnable = 100;
    gUsbDataList->UsbTimingPolicy->OhciHcReset = 2;
    gUsbDataList->UsbTimingPolicy->UhciGlobalReset = 10;
    gUsbDataList->UsbTimingPolicy->UhciPortEnable = 100;
    gUsbDataList->UsbTimingPolicy->HubPortConnect = 50;
    gUsbDataList->UsbTimingPolicy->HubPortEnable = 50;
    gUsbDataList->UsbTimingPolicy->MassDeviceComeUp = 500;
    gUsbDataList->UsbTimingPolicy->RmhPowerOnDelay= 100;

    Status = gBS->InstallProtocolInterface(
                    &ImageHandle,
                    &gUsbTimingPolicyProtocolGuid, 
                    EFI_NATIVE_INTERFACE,
                    gUsbDataList->UsbTimingPolicy);
                
    if (EFI_ERROR(Status)) {
        return Status;
    }

    gUsbData->MemPages = MemPages;
    gUsbData->MemBlkStsBytes = ((gUsbData->MemPages << 12) / sizeof(MEM_BLK)) / 8;

    // Initialize the memory block status array to free
    gUsbDataList->MemBlkSts = AllocAlignedMemory(gUsbData->MemBlkStsBytes, 0x10);
    ASSERT(gUsbDataList->MemBlkSts != NULL);
    SetMem(gUsbDataList->MemBlkSts, gUsbData->MemBlkStsBytes, 0xFF);

    // Allocate Skip Table memory
    DataSize = (UINT32)PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxSkipTableCount);
    gUsbData->MaxSkipListCount = (UINT8)DataSize+1;
    DataSize = ((DataSize+1) * sizeof(USB_SKIP_LIST));
    gUsbDataList->UsbSkipListTable = AllocAlignedMemory(DataSize, 0x10);
    ASSERT(gUsbDataList->UsbSkipListTable != NULL);

#ifndef KBC_SUPPORT
    if (gUsbData->UsbRuntimeDriverInSmm)
        gUsbData->KbcSupport = (IoRead8(0x64)==0xff)? 0 : 1;
#else
    gUsbData->KbcSupport = KBC_SUPPORT;
#endif

    gUsbData->PciExpressBaseAddress = (UINTN)PcdGet64(PcdPciExpressBaseAddress);  
    gUsbData->UsbDataList = gUsbDataList;
    
    if (gAllocateMemType == EfiBootServicesData){
    	gUsbData->UsbFeature2 |= USE_BS_MEM_IN_UEFI;
    } else { 
        if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUseBsInUefi)){
    	    EFI_HANDLE    Handle = NULL;   
            Status = gBS->InstallProtocolInterface (
                            &Handle,
                            &gAmiUsbSmmDepxProtocolGuid,
                            EFI_NATIVE_INTERFACE,
                            NULL
                            );
            if (EFI_ERROR(Status)) {
                USB_DEBUG(DEBUG_DEV_INIT, "InstallProtocolInterface gAmiUsbSmmDepxProtocolGuid %r\n", Status);
            }
        }
    }
    //
    // Install USB protocol
    //
    USB_DEBUG(DEBUG_DEV_INIT, "AmiUsb Version: %d\n", USB_MAJOR_VER);
    USB_DEBUG(DEBUG_DEV_INIT, "AMIUHCD USB Init: data located at........... %x\n", (UINTN)gUsbData);
    USB_DEBUG(DEBUG_DEV_INIT, "Log address: %x\n", &gUsbData->ErrorLogBuffer[0]);
    USB_DEBUG(DEBUG_DEV_INIT, "Memory map: %x\n", &gUsbDataList->MemBlkSts[0]);
    USB_DEBUG(DEBUG_DEV_INIT, "Device address map: %x\n", &gUsbData->DeviceAddressMap);

    gAmiUsbController->USBDataPtr                = gUsbData;
    gAmiUsbController->UsbReportDevices          = ReportDevices;
    gAmiUsbController->UsbGetNextMassDeviceName  = GetNextMassDeviceName;
    gAmiUsbController->UsbChangeEfiToLegacy      = UsbChangeEfiToLegacy;
    gAmiUsbController->UsbGetRuntimeRegion       = UsbGetRuntimeRegion;
    gAmiUsbController->InstallUsbLegacyBootDevices = Dummy2;
    gAmiUsbController->UsbInstallLegacyDevice    = Dummy1;
    gAmiUsbController->UsbUninstallLegacyDevice  = Dummy1;
    gAmiUsbController->UsbGetAssignBootPort      = OemGetAssignUsbBootPort;
    gAmiUsbController->UsbRtShutDownLegacy       = UsbRtShutDownLegacy;    //<(EIP52339+)
    gAmiUsbController->UsbCopySkipTable          = UsbGetSkipList;         //(EIP51653+)
    gAmiUsbController->UsbRtStopController       = UsbRtStopController;    //(EIP74876+)

    Status = gBS->InstallProtocolInterface(
                &UsbHandle,
                &gEfiUsbProtocolGuid,
                EFI_NATIVE_INTERFACE,
                gAmiUsbController
                );
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "Fail to install UsbProtocol(%r)\n", Status);
        return Status;
    }

    if (!(gUsbData->UsbFeature2 & USB_SKIP_UEFI_DRIVER)) {
        gAmiUsbDriverBinding.DriverBindingHandle = ImageHandle;
        gAmiUsbDriverBinding.ImageHandle = ImageHandle;

        // Install driver binding protocol here
        Status = EfiLibInstallDriverBindingComponentName2 (
                     ImageHandle,
                     SystemTable,
                     &gAmiUsbDriverBinding,
                     gAmiUsbDriverBinding.DriverBindingHandle,
                     NULL,
                     &gComponentNameUsb
                     );
    
        if (EFI_ERROR(Status)) {
            return Status;
        }
    
        for (DevDriverIndex = 0; gUsbDevEfiDrivers[DevDriverIndex]; DevDriverIndex++) {
            Status = gUsbDevEfiDrivers[DevDriverIndex](ImageHandle, 0);
            ASSERT_EFI_ERROR(Status);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
        //
        // Create the notification and register callback function on the PciIo installation
        //
        Status = gBS->CreateEvent(
                     EVT_NOTIFY_SIGNAL, 
                     TPL_CALLBACK,
                     UhcdPciIoNotifyCallback, 
                     NULL, 
                     &PciIoEvent);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return Status;

        Status = gBS->RegisterProtocolNotify (
                   &gEfiPciIoProtocolGuid, 
                   PciIoEvent, 
                   &PciIoNotifyReg
                   );
        ASSERT_EFI_ERROR(Status);
    }

#if defined(CSM_SUPPORT) && CSM_SUPPORT         //(EIP69136)
    // Install HW interrupt handler
    {
        EFI_LEGACY_BIOS_PLATFORM_PROTOCOL   *LegacyBiosProtocol = NULL;
        VOID        *LegacyBiosProtocolNotifyReg = NULL;
        VOID        *LegacyBiosProtocolNotifyContext = NULL;
        VOID        *Registration = NULL;
        VOID        *NotifyContext = NULL;
        EFI_GUID    LegacyToEfiGuid = LTEB_GUID;
        EFI_EVENT   BackToEfiEvent;

        gBS->CreateEventEx (
               EVT_NOTIFY_SIGNAL,
               TPL_CALLBACK,
               UsbLegcyToEfiNotify,
               NULL,
               &LegacyToEfiGuid,
               &BackToEfiEvent
               );

        Status = EfiNamedEventListen(
                 &gAmiPciIrqProgramGuid,
                 TPL_CALLBACK,
                 UhcdPciIrqPgmNotifyCallback,
                 NotifyContext,
                 Registration);
        ASSERT_EFI_ERROR(Status);
        Status = gBS->LocateProtocol(&gEfiLegacyBiosPlatformProtocolGuid, NULL, (VOID**)&LegacyBiosProtocol);
        if (EFI_ERROR(Status)) {
            Status = EfiNamedEventListen(
                     &gEfiLegacyBiosPlatformProtocolGuid,
                     TPL_CALLBACK,
                     LegacyBiosProtocolNotifyCallback,
                     LegacyBiosProtocolNotifyContext,
                     LegacyBiosProtocolNotifyReg);
            ASSERT_EFI_ERROR(Status);
        } else {
            gUsbData->UsbStateFlag |= USB_FLAG_CSM_ENABLED;
        }
    }
#endif

    Status = gBS->LocateProtocol (&gNonSmmEmul6064TrapProtocolGuid, NULL, (VOID**)&gEmulationTrap);
    if (EFI_ERROR(Status)) {
        Status = EfiNamedEventListen(
                     &gNonSmmEmul6064TrapProtocolGuid,
                     TPL_CALLBACK,
                     Emul6064NotifyCallback,
                     NonSmmEmul6064NotifyContext,
                     &NonSmmEmul6064Registration);

        if (EFI_ERROR (Status)) {
            USB_DEBUG(DEBUG_DEV_INIT, "Register Protocol Callback Emul6064Event Status %r\n", Status);
        }
    }
    
    Status = EfiCreateEventLegacyBootEx(
                TPL_NOTIFY, 
                OnLegacyBoot,
                NULL, 
                &LegacyBootEvent);
    
    if (EFI_ERROR (Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "Create Event LegacyBoot Status %r\n", Status);
    }
    
    Status = gBS->CreateEvent(
                EVT_SIGNAL_EXIT_BOOT_SERVICES,
                TPL_NOTIFY, 
                OnExitBootServices,
                NULL, 
                &ExitBootServicesEvent);
    if (EFI_ERROR (Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "Create Event Exit Boot Services Status %r\n", Status);
    }

    if (!(gUsbData->UsbFeature2 & USB_SKIP_UEFI_DRIVER)) {
        if (((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == 0) &&
            (gUsbData->UsbRuntimeDriverInSmm != USB_RUNTIME_DRV_MODE_1)) {
            Status = gBS->CreateEvent(
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY, UsbIntTimerCallback, 0, &gUsbIntTimerEvt);
            
            if (EFI_ERROR (Status)) {
                USB_DEBUG(DEBUG_DEV_INIT, "Create Event UsbIntTimerCallback Status %r\n", Status);
            }
            Status = gBS->SetTimer(gUsbIntTimerEvt, 
                        TimerPeriodic, gUsbData->InterruptPollingPeriod);
            if (EFI_ERROR (Status)) {
                USB_DEBUG(DEBUG_DEV_INIT, "Event UsbIntTimerCallback Set Timer Status %r\n", Status);
            }
        }
        Status = EfiCreateEventReadyToBootEx(TPL_CALLBACK, ReadyToBootNotify, NULL, &ReadyToBootEvent);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        Status = gBS->CreateEventEx(
            EVT_NOTIFY_SIGNAL, TPL_CALLBACK, EndOfDxeEventCallback,
            NULL, &gEfiEndOfDxeEventGroupGuid, &EndOfDxeEvent);
        ASSERT_EFI_ERROR(Status);
    }
    Status = gBS->CreateEventEx(        //Collect USB controller data
        EVT_NOTIFY_SIGNAL, TPL_CALLBACK, UsbAddHcControllerCallback,
        NULL, &gUsbAddHcEventGroupGuid, &AddUsbHcEvent);
    ASSERT_EFI_ERROR(Status); 
    
    return Status;
}

/**
    60/64 emulation call back routine

    @param  Event       - Efi event occurred upon 6064 notify
    @param  Context     - Not used
**/
VOID
EFIAPI
Emul6064NotifyCallback(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    EFI_STATUS  Status;

    Status = gBS->LocateProtocol (&gNonSmmEmul6064TrapProtocolGuid, NULL, (VOID**)&gEmulationTrap);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "LocateProtocol NonSmmEmul6064TrapProtocol %r.\n", Status);
        return;
    }
}


#if defined(CSM_SUPPORT) && CSM_SUPPORT         //(EIP69136)
/**
    Uhcd PCI irq notify call back routine

    @param  Event       - Efi event occurred upon Uhcd PCI irq notify
    @param  Context     - Not used
**/
VOID
EFIAPI
UhcdPciIrqPgmNotifyCallback(
    EFI_EVENT Event,
    VOID      *Context
)
{
    PROGRAMMED_PCIIRQ_CTX   *PciIrqCtx;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    UINTN       Seg;
    UINTN       Bus;
    UINTN       Dev;
    UINTN       Func;
    EFI_STATUS  Status;

    Status = gBS->LocateProtocol(&gAmiPciIrqProgramGuid , NULL, (VOID**)&PciIrqCtx);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "USBHC:: can not locate PCI IRQ program interface.\n");
        return;
    }

    PciIo = (EFI_PCI_IO_PROTOCOL*)PciIrqCtx->PciIo;
    if (PciIo == NULL) return;

    Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Func);
    ASSERT_EFI_ERROR(Status);
    
    USB_DEBUG(DEBUG_DEV_INIT, "Ready to install interrupt handler for IRQ%d for PCI B%d/D%d/F%d\n",
            PciIrqCtx->Irq, Bus, Dev, Func);

}

/**
    LegacyBiosProtocol notification callback.

    @param Event     event signaled by the CSM installs the legacy bios platform protocol.
    @param Context   event context

**/

VOID
EFIAPI
LegacyBiosProtocolNotifyCallback(
    EFI_EVENT Event,
    VOID      *Context
)
{
    gUsbData->UsbStateFlag |= USB_FLAG_CSM_ENABLED;
    gBS->CloseEvent(Event);
}

#endif

/**
    PciIo notification callback. It calls UpdateHcPciInfo porting function
    to update the PCI information in the HC device table.

    @param Event     event signaled by the DXE Core upon PciIo installation
    @param Context   event context

**/

VOID
EFIAPI
UhcdPciIoNotifyCallback (
    EFI_EVENT Event,
    VOID      *Context
)
{
    // Porting hook that updates a list of PCI devices that will be used during enumeration
    UpdateHcPciInfo();
    // this is one time callback
    gBS->CloseEvent(Event);
}

/**
    This function check whether the Interface Type is supported.

    @param InterfaceType   Pci class code

    @retval TRUE           USB class code match
    @retval FALSE          USB class code not match
**/

/**
    Test to see if this driver supports ControllerHandle.

    @param This                 Protocol instance pointer
    @param Controller           Handle of device to test
    @param RemainingDevicePath  Optional parameter use to pick a specific child
                                device to start.

    @retval EFI_SUCCESS         This driver supports this device.
    @retval EFI_UNSUPPORTED     This driver does not support this device.

**/

EFI_STATUS
EFIAPI
AmiUsbDriverBindingSupported (
    EFI_DRIVER_BINDING_PROTOCOL    *This,
    EFI_HANDLE                     Controller,
    EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
    )

{
    EFI_STATUS                  Status;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    USB_CLASSC                  UsbClassCReg;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;

    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = PciIo->Pci.Read (
                      PciIo,
                      EfiPciIoWidthUint8,
                      CLASSC,
                      sizeof(USB_CLASSC) / sizeof(UINT8),
                      &UsbClassCReg);

    gBS->CloseProtocol (
           Controller,
           &gEfiPciIoProtocolGuid,
           This->DriverBindingHandle,
           Controller);

    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    if ((UsbClassCReg.BaseCode != PCI_CLASSC_BASE_CLASS_SERIAL) || 
        (UsbClassCReg.SubClassCode != PCI_CLASSC_SUBCLASS_SERIAL_USB) ||
        !IsSupportedInterfaceType(UsbClassCReg.PI)) {
        return EFI_UNSUPPORTED;
    }
    
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    (VOID**)&DevicePath,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller);

    if ((gUsbData->UsbFeature & USB_EXTERNAL_CONTROLLER_SUPPORT) == 0)
        if (IsExternalController(DevicePath)) {
            return EFI_UNSUPPORTED;
        }

    return EFI_SUCCESS;

}  // end of AmiUsbDriverBindingSupported


/**
    Binding protocol function to start the AMI USB driver

    @param This                 Protocol instance pointer.
    @param Controller           Handle of device to test
    @param RemainingDevicePath  Optional parameter use to pick a specific child
                                device to start.

    @retval EFI_SUCCESS This driver supports this device.
    @retval EFI_UNSUPPORTED This driver does not support this device.
    @retval EFI_DEVICE_ERROR This driver cannot be started due to device

**/

EFI_STATUS
EFIAPI
AmiUsbDriverBindingStart (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath )
{
    EFI_STATUS                       Status;
    EFI_PCI_IO_PROTOCOL             *PciIo;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    UINTN               SegNum;
    UINTN               BusNum;
    UINTN               DevNum;
    UINTN               FuncNum;
    UINT8               PciCfg[0x40];
    HC_STRUC            *HcStruc;
    UINT64              OrgCapabilities;
    CHAR8               TokenName[15];
    CHAR8               UhciToken[] = "UhciHost";
    CHAR8               OhciToken[] = "OhciHost";
    CHAR8               EhciToken[] = "EhciHost";
    CHAR8               XhciToken[] = "XhciHost";

    USB_DEBUG(DEBUG_DEV_INIT, "AmiUsbDriverBindingStart for %x\n", Controller);
        
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = PciIo->GetLocation(PciIo, &SegNum, &BusNum, &DevNum, &FuncNum);
    if (EFI_ERROR(Status)) {
        gBS->CloseProtocol (
               Controller,
               &gEfiPciIoProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        return EFI_DEVICE_ERROR;
    }

    Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof(PciCfg),
                          PciCfg);
    if (EFI_ERROR(Status)) {
        gBS->CloseProtocol (
               Controller,
               &gEfiPciIoProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        return EFI_DEVICE_ERROR;
    }

    // Get the device path
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    (VOID**)&DevicePath,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR(Status)) {
        gBS->CloseProtocol (
               Controller,
               &gEfiPciIoProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        return Status;
    }

    USB_DEBUG(DEBUG_DEV_INIT, "USB HC Bus# %x Dev# %x Func# %x, PI %x\n", BusNum, DevNum, FuncNum ,PciCfg[0x9]);
    
    // Try to locate EHCI controller
    if ((PciCfg[0x9] == PCI_CLASSC_PI_UHCI) || (PciCfg[0x9] == PCI_CLASSC_PI_OHCI) ) {
        LocateEhciController(This, Controller, DevicePath);
    }
    Status = AmiEnableUsbPciAttributes((VOID*)PciIo, &OrgCapabilities);
    if (EFI_ERROR(Status)) {
    	
    	USB_DEBUG(DEBUG_DEV_INIT, "Fail to enable PciIo attribute!\n");
        PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        OrgCapabilities,
                        NULL
                        );
        gBS->CloseProtocol (
               Controller,
               &gEfiPciIoProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        gBS->CloseProtocol (
               Controller,
               &gEfiDevicePathProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        return EFI_DEVICE_ERROR;
    }

    HcStruc = CheckUsbController( Controller, DevicePath);
    if (HcStruc == NULL){
        HcStruc = AddHC( Controller, DevicePath);
    }
    
    if (HcStruc == NULL) {
        PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        OrgCapabilities,
                        NULL
                        );
        gBS->CloseProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);
        gBS->CloseProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);
        return EFI_OUT_OF_RESOURCES;
    }
    
    if ((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == USB_IRQ_INTERRUPT_SUPPORT){
        // Find the AMI USB ISR protocol.
        if (gAmiUsbIsrProtocol == NULL) {
            Status = gBS->LocateProtocol(&gAmiUsbIsrProtocolGuid, NULL, (VOID**)&gAmiUsbIsrProtocol);
            if (EFI_ERROR (Status)){
                return Status;
            }
        }
        if (gAmiUsbIsrProtocol != NULL) {
            gAmiUsbIsrProtocol->InstallUsbIsr(gAmiUsbIsrProtocol);
        }
    }
    // Get Host Token name.
    switch (HcStruc->HcType) {
            case USB_HC_UHCI:
                AsciiStrnCpyS(&TokenName[0], sizeof(TokenName), &UhciToken[0], sizeof(UhciToken));
                break;
            case USB_HC_OHCI:
                AsciiStrnCpyS(&TokenName[0], sizeof(TokenName), &OhciToken[0], sizeof(OhciToken));
                break;
            case USB_HC_EHCI:
                AsciiStrnCpyS(&TokenName[0], sizeof(TokenName), &EhciToken[0], sizeof(EhciToken));
                break;
            case USB_HC_XHCI:
                AsciiStrnCpyS(&TokenName[0], sizeof(TokenName), &XhciToken[0], sizeof(XhciToken));
                break;
            default:
                break;
    }

    // PERF_START
    AmiUsbPerfStart(NULL, TokenName, "AmiUsb", 0);
    // Initialize host controller
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_HC_START_STOP;
    gParameters->ApiData.HcStartStop.Start = START_HOST_CONTROLLER;
    gParameters->ApiData.HcStartStop.HcStruc = HcStruc;

    if ((gUsbData->UsbFeature2 & USE_BS_MEM_IN_UEFI)== USE_BS_MEM_IN_UEFI){
        InvokeUsbApi(gParameters);
    } else {
        if (gUsbData->UsbRuntimeDriverInSmm != USB_RUNTIME_DRV_MODE_0) {
            USBGenerateSWSMI(gUsbData->UsbSwSmi);
        } else {
            InvokeUsbApi(gParameters);
        }
    }
    // PERF_END
    AmiUsbPerfEnd(NULL, TokenName, "AmiUsb", 0);
    
    USB_DEBUG(DEBUG_DEV_INIT, "HC start completed, exit code %d.\n", gParameters->RetValue);

    Status = InstallHcProtocols(This, Controller, PciIo, HcStruc);
    if (EFI_ERROR(Status)) {
        PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        HcStruc->OrgPciAttributes,
                        NULL
                        );
        gBS->CloseProtocol (
               Controller,
               &gEfiPciIoProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        gBS->CloseProtocol (
               Controller,
               &gEfiDevicePathProtocolGuid,
               This->DriverBindingHandle,
               Controller);
        return Status;
    }
    
    REPORT_STATUS_CODE(EFI_PROGRESS_CODE, DXE_USB_ENABLE);
    return EFI_SUCCESS;

} // end of AmiUsbDriverBindingStart


/**
    Stop this driver on ControllerHandle. Support stoping any
    child handles created by this driver.

    @param This              Protocol instance pointer.
    @param DeviceHandle      Handle of device to stop driver on
    @param NumberOfChildren  Number of Children in the ChildHandleBuffer
    @param ChildHandleBuffer List of handles for the children we
                             need to stop.
    @retval EFI_SUCCESS      This driver is removed ControllerHandle
    @retval other            This driver was not removed from this device

**/

EFI_STATUS
EFIAPI
AmiUsbDriverBindingStop (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE Controller,
    IN UINTN      NumberOfChildren,
    IN EFI_HANDLE *ChildHandleBuffer
)
{
    EFI_STATUS Status;
    EFI_USB_HC_PROTOCOL     *HcProtocol;
    EFI_USB2_HC_PROTOCOL    *HcProtocol2;
    EFI_PCI_IO_PROTOCOL     *PciIo;
    HC_DXE_RECORD           *DxeRecord;
    HC_STRUC                *HcStruc;
    UINT64                  Capabilities;
    UINT64                  OrgPciAttributes;

    USB_DEBUG(DEBUG_DEV_INIT, "AmiUsbDriverBindingStop for %x\n", Controller);

    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiUsbHcProtocolGuid,
                    (VOID**)&HcProtocol,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiUsb2HcProtocolGuid,
                    (VOID**)&HcProtocol2,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    DxeRecord = (HC_DXE_RECORD*)(UINTN)HcProtocol;
    HcStruc = DxeRecord->HcStruc;
    PciIo = HcStruc->PciIo;

    // Stop host controller
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_HC_START_STOP;
    gParameters->ApiData.HcStartStop.Start = STOP_HOST_CONTROLLER;
    gParameters->ApiData.HcStartStop.HcStruc = HcStruc;
    InvokeUsbApi(gParameters);

    USB_DEBUG(DEBUG_DEV_INIT, "HC stop completed, exit code %d.\n", gParameters->RetValue);

    // Disconnect devices and uninstall usb device related protocols
    UsbHcOnTimer(gEvUsbEnumTimer, NULL);

    Status = gBS->UninstallMultipleProtocolInterfaces ( 
                    Controller,
                    &gEfiUsbHcProtocolGuid, HcProtocol,
                    &gEfiUsb2HcProtocolGuid, HcProtocol2,
                    NULL
                    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    HcStruc->HcFlag &= ~HC_STATE_USED;

    gUsbDataList->NumOfHc--;

    // Disable the device
    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationSupported, 
                      0,
                      &Capabilities
                      );         // Get device capabilities
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    // Disable device
    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationDisable,
                      Capabilities & (EFI_PCI_DEVICE_ENABLE | EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE),
                      NULL
                      );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    //
    // Restore original PCI attributes
    //
    if(HcStruc->HcType == USB_HC_XHCI){
        USB3_HOST_CONTROLLER *Usb3Hc;
        Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->Usb3HcData;
        OrgPciAttributes = Usb3Hc->OrgPciAttributes;
    } else {
        OrgPciAttributes = HcStruc->OrgPciAttributes;
    }
    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationSet,
                      OrgPciAttributes,
                      NULL
                      );
    ASSERT_EFI_ERROR(Status);
    HcStruc->OrgPciAttributes = 0;

    Status = gBS->CloseProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    This->DriverBindingHandle,
                    Controller
                    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gBS->CloseProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Free memory allocated in Start function
    gBS->FreePool(DxeRecord);

    return EFI_SUCCESS;

} // End of UHCIDriverBindingStop


/**
    This function returns TRUE if there is a need for extra USB
    devices that might be inserted/enumerated after legacy boot

    @retval TRUE       Hotplug enable
    @retval FALSE      Hotplug disable
**/

BOOLEAN HotplugIsEnabled()
{
    BOOLEAN FddHotplug;
    BOOLEAN HddHotplug;
    BOOLEAN CdromHotplug;

    FddHotplug = ((gUsbDataList->UsbSetupData->UsbHotplugFddSupport == SETUP_DATA_HOTPLUG_ENABLED)
        || ((gUsbDataList->UsbSetupData->UsbHotplugFddSupport == SETUP_DATA_HOTPLUG_AUTO)
            && (gUsbData->NumberOfFDDs == 0)));

    HddHotplug = ((gUsbDataList->UsbSetupData->UsbHotplugHddSupport == SETUP_DATA_HOTPLUG_ENABLED)
        || ((gUsbDataList->UsbSetupData->UsbHotplugHddSupport == SETUP_DATA_HOTPLUG_AUTO)
            && (gUsbData->NumberOfHDDs == 0)));

    CdromHotplug = ((gUsbDataList->UsbSetupData->UsbHotplugCdromSupport == SETUP_DATA_HOTPLUG_ENABLED)
        || ((gUsbDataList->UsbSetupData->UsbHotplugCdromSupport == SETUP_DATA_HOTPLUG_AUTO)
            && (gUsbData->NumberOfCDROMs == 0)));

    return FddHotplug || HddHotplug || CdromHotplug;
}


/**
    EXIT_BOOT_SERVICES notification callback function.

    @param  Event       Efi event occurred upon exit boot services
    @param  Context     Not use
**/

VOID
EFIAPI
OnExitBootServices(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    HC_STRUC    *HcStruc;
    UINT8       Index;
    EFI_STATUS  Status;
    UINTN       UsbIoHandleCount;
    UINTN       HandleIndex;
    EFI_HANDLE  *UsbIoHandles;
    EFI_TPL     OldTpl;

    EFI_PCI_IO_PROTOCOL  *PciIo;
    
    UsbIoHandles        = NULL;
    UsbIoHandleCount    = 0;
    HandleIndex         = 0;
    HcStruc             = NULL;
    PciIo               = NULL;
    
    if (gUsbIntTimerEvt != NULL) {
        gBS->SetTimer(gUsbIntTimerEvt, TimerCancel, 0);
        gBS->CloseEvent(gUsbIntTimerEvt);
    }

    if ((gUsbData->UsbFeature2 & USB_DISCONNECT_USBIO_EXIT_BOOT)== USB_DISCONNECT_USBIO_EXIT_BOOT){
        Status = gBS->LocateHandleBuffer (
                        ByProtocol,
                        &gEfiUsbIoProtocolGuid,
                        NULL,
                        &UsbIoHandleCount,
                        &UsbIoHandles
                        );
        if (UsbIoHandles != NULL) {
            OldTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
            gBS->RestoreTPL(TPL_APPLICATION);
            for (HandleIndex = 0; HandleIndex < UsbIoHandleCount; HandleIndex++) {
                Status = gBS->DisconnectController (UsbIoHandles[HandleIndex], NULL, NULL);
                if (EFI_ERROR(Status)) {
                    USB_DEBUG(DEBUG_DEV_INIT, "UsbIo DisconnectController_%x %r \n",HandleIndex,Status);
                }
            }
            gBS->RaiseTPL(TPL_HIGH_LEVEL);
            gBS->RestoreTPL(OldTpl);
            gBS->FreePool(UsbIoHandles);
        }
    }
    
    if ((gUsbData->UsbStateFlag & USB_FLAG_CSM_ENABLED) && 
        (gUsbData->UsbRuntimeDriverInSmm>USB_RUNTIME_DRV_MODE_0)) {
        for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
            HcStruc = gHcTable[Index];
            if (HcStruc == NULL) {
                continue;
            }
            if (!(HcStruc->HcFlag & HC_STATE_RUNNING)) { 
                continue;
            }
            if (HcStruc->HwSmiHandle != NULL) {
                if (gUsbData->UsbRuntimeDriverInSmm == USB_RUNTIME_DRV_MODE_2) {
                    if ((gUsbData->UsbFeature2 & USE_BS_MEM_IN_UEFI)== 0){
                        AmiUsbSmiControl(HcStruc, TRUE);
                    }
                }
                continue;
            }
            // Stop host controller
            gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
            gParameters->FuncNumber = USB_API_HC_START_STOP;
            gParameters->ApiData.HcStartStop.Start = STOP_HOST_CONTROLLER;
            gParameters->ApiData.HcStartStop.HcStruc = HcStruc;
            InvokeUsbApi(gParameters);
        }
        //
        //Enable the KBC Emulation SMI's
        //
        if (gEmulationTrap != NULL && gLegacyUsbStatus) {
            gEmulationTrap->TrapEnable(gEmulationTrap);
        }
    } else {
        gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
        gParameters->FuncNumber = USB_API_STOP;
        gParameters->SubFunc = 0;
        InvokeUsbApi(gParameters);
    }
    if (gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON){
        for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
            HcStruc = gHcTable[Index];
            if (HcStruc == NULL){
                continue;
            }
            PciIo = HcStruc->PciIo;
            
            if(HcStruc->HcType == USB_HC_XHCI){
                USB3_HOST_CONTROLLER *Usb3Hc;
                
                Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->Usb3HcData;
                Status = PciIo->Unmap(PciIo, (VOID *)(Usb3Hc->DcbaaPtrMapping));
                if (EFI_ERROR(Status)) {
                    USB_DEBUG(DEBUG_DEV_INIT, "Unmap DcbaaPtrMapping %r \n",Status);
                }
            }
            
            if(HcStruc->MemBlockStartMapping != NULL){
                Status = PciIo->Unmap(PciIo, (VOID *)(HcStruc->MemBlockStartMapping));
                if (EFI_ERROR(Status)) {
                    USB_DEBUG(DEBUG_DEV_INIT, "Unmap MemBlockStartMapping %r \n",Status);
                }
            }
        }
    }
    
    gUsbData->UsbStateFlag &= ~(USB_FLAG_RUNNING_UNDER_EFI);

    if ((gUsbData->UsbFeature2 & USE_BS_MEM_IN_UEFI)== 0){
	    if (gUsbData->UsbRuntimeDriverInSmm) {
	        // Switch Global data to SMM
	        gParameters->SubFunc = USB_DATA_DXE_TO_SMM;
	        gParameters->FuncNumber = USB_API_LOCK_USB_SW_SMI;
	        USBGenerateSWSMI(gUsbData->UsbSwSmi);
	    }
    }
}


/**
    This function is invoked when on Legacy Boot

    @param Event       Efi event occurred upon legacyboot
    @param Context     Not used

**/

VOID
EFIAPI
OnLegacyBoot (
    IN EFI_EVENT  Event,
    IN VOID       *Context
)
{
    CONNECTED_USB_DEVICES_NUM   Devs;
    UINT8                       UsbLegacySupport;
    UINT32                      EbdaAddr = (UINT32)(*((UINT16*)(UINTN)0x40E)) << 4;

    *(UINT32*)(UINTN)(EbdaAddr + USB_PROTOCOL_EBDA_OFFSET) = (UINT32)(UINTN)gAmiUsbController;

    UsbLegacySupport = UsbSetupGetLegacySupport();

    USB_DEBUG(DEBUG_DEV_INIT, "AMIUHCD::OnLegacyBoot::%d\n", UsbLegacySupport);

    //
    //Enable the KBC Emulation SMI's
    //
    if(gEmulationTrap != NULL && gLegacyUsbStatus) {
        gEmulationTrap->TrapEnable(gEmulationTrap);
    }

    switch (UsbLegacySupport) {
        case 0: break;  // Enable
        case 2: // Auto - check for devices, stop USB if none are present.
            if (HotplugIsEnabled()) break;  // Do not stop as Hotplug devices will be inserted
            ReportDevices(&Devs);
            if (Devs.NumUsbKbds+Devs.NumUsbMice+Devs.NumUsbPoint+Devs.NumUsbMass+Devs.NumUsbHubs) {    //(EIP38434)
                break;
            }
        case 1: // Disable - stop USB controllers
            UsbRtShutDownLegacy();
            return;
    }
{
    EFI_HANDLE *Handle;
    UINTN      Number;
    EFI_STATUS Status;
    EFI_TPL    OldTpl;

    if (gUsbData->UsbFeature2 & USB_SKIP_UEFI_DRIVER) {
    	UINTN      Index;
        //Get a list of all PCI devices
        Status = gBS->LocateHandleBuffer(
                        ByProtocol,
                        &gEfiUsb2HcProtocolGuid, 
                        NULL, 
                        &Number, 
                        &Handle 
                        );
        if (!EFI_ERROR(Status)) {
            OldTpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);
            gBS->RestoreTPL (TPL_APPLICATION);
        
            for( Index=0; Index<Number; Index++) {
                gBS->DisconnectController (Handle[Index], NULL, NULL);
            }
            gBS->FreePool(Handle);
        
            gBS->RaiseTPL (TPL_HIGH_LEVEL);
            gBS->RestoreTPL(OldTpl);
        }
        
        for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
            UINT64   OrgCapabilities;
            Status = AmiEnableUsbPciAttributes((VOID*)gHcTable[Index]->PciIo, &OrgCapabilities);
        }
    }
}
    UsbPrepareForLegacyOS();
    gUsbData->UsbStateFlag |= USB_FLAG_BOOT_EVENT;
    gUsbData->UsbStateFlag  &= ~(USB_FLAG_RUNNING_UNDER_EFI);
}

/**
    This function is invoked when on ReadyToBoot

    @param Event       Efi event occurred upon ReadyToBoot
    @param Context     Not used

**/

VOID
EFIAPI
ReadyToBootNotify(
    EFI_EVENT   Event, 
    VOID        *Context
)
{
    if (gAmiUsbController->USBDataPtr) {
        ((USB_GLOBAL_DATA*)(gAmiUsbController->USBDataPtr))->UsbDataList = NULL;
    }
    gAmiUsbController->USBDataPtr = NULL;
    gUsbData->UsbStateFlag |= USB_FLAG_BOOT_EVENT;
    gBS->CloseEvent(Event);
}

/**
    This function is invoked when on EndOfDxe

    @param Event       Efi event occurred upon EndOfDxe
    @param Context     Not used

**/

VOID
EFIAPI
EndOfDxeEventCallback(
    EFI_EVENT   Event, 
    VOID        *Context
)
{
    gUsbData->UsbStateFlag |= USB_FLAG_AFTER_END_OF_DXE;
    if (gUsbData->UsbRuntimeDriverInSmm) {
        ((USB_GLOBAL_DATA*)(gAmiUsbController->USBDataPtr))->UsbDataList = NULL;
        gAmiUsbController->USBDataPtr = NULL;
    }
}

/**
  This function is invoked when signal gUsbAddHcEventGroupGuid.
  1.Enable Usb Host controller pci attribute.
  2.Add Usb Host Controller.

  @param  Event    The instance of EFI_EVENT.
  @param  Context  The parameter passed in.
**/

VOID
EFIAPI
UsbAddHcControllerCallback(
    EFI_EVENT   Event, 
    VOID        *Context
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  *Handle;
    UINTN       Number;
    UINTN       Index;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
    HC_STRUC    *HcStruc;
    EFI_PCI_IO_PROTOCOL                     *PciIo;
    UINT64                                  OrgCapabilities;
    
    USB_DEBUG(DEBUG_DEV_INIT, "UsbAddHcControllerCallback  \n");
    //Get a list of all USB Controllers
    Status = GetPciHandleByClassHc (PCI_CLASS_SERIAL, PCI_CLASS_SERIAL_USB, &Number, &Handle);
    
    if (EFI_ERROR (Status)){
        USB_DEBUG(DEBUG_DEV_INIT, "GetPciHandleByClassHc %r \n",Status);
    }
    for (Index = 0 ; Index < Number; Index++) {
        Status = gBS->OpenProtocol (
                        Handle[Index],
                        &gEfiPciIoProtocolGuid,
                        (VOID **) &PciIo,
                        NULL,
                        NULL,
                        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                        );
        if (EFI_ERROR (Status)){
            USB_DEBUG(DEBUG_DEV_INIT, "error gEfiPciIoProtocolGuid %r\n",Status);
            return;
        } 
        Status = gBS->OpenProtocol (
                        Handle[Index],
                        &gEfiDevicePathProtocolGuid,
                        (VOID **) &DevicePath,
                        NULL,
                        NULL,
                        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
                        );
        if (EFI_ERROR (Status)){
            USB_DEBUG(DEBUG_DEV_INIT, "error DevicePathProtocolGuid %r\n",Status);
            return;
        }
        Status = AmiEnableUsbPciAttributes((VOID*)PciIo, &OrgCapabilities);
        
        if (EFI_ERROR (Status)){
            USB_DEBUG(DEBUG_DEV_INIT, " AmiEnableUsbPciAttributes %r\n",Status);
            return;
        }
        
        HcStruc = AddHC( Handle[Index], DevicePath);
        USB_DEBUG(DEBUG_DEV_INIT, " Callback Add hc HcStruc %x\n",HcStruc);
        if(HcStruc == NULL){
            PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSet,
                    OrgCapabilities,
                    NULL
            );
        }else{
            HcStruc->OrgPciAttributes = OrgCapabilities;
        }
    }
    
    if (Handle != NULL) {
        gBS->FreePool(Handle);
    }
}

/**
    This function is invoked when on LegcyToEfi event

    @param  Event       Efi event occurred upon LegcyToEfi
    @param  Context     Not used

**/

VOID
EFIAPI
UsbLegcyToEfiNotify(
    EFI_EVENT   Event, 
    VOID        *Context
)
{
    gParameters->FuncNumber = USB_API_MOVE_DATA_AREA;
    gParameters->SubFunc = USB_DATA_SMM_TO_DXE;
    gParameters->RetValue = USB_ERROR;
    USBGenerateSWSMI(gUsbData->UsbSwSmi);

}

/**
    This function checks if the controller has integrated 
    USB 2.0 Rate Matching Hubs (RMH).
    @param HCStruc    Pointer to the HCStruc structure

**/
VOID
CheckSpecificController (
    HC_STRUC    *HcStruc
)
{
    UINT8       Index;
    UINT32      Flag;

    for (Index = 0; Index < MAX_SPECIFIC_USB_CONTROLLER_COUNT; Index++) {
    
        if ((gSpecificControllers[Index].Vid == 0) &&
            (gSpecificControllers[Index].Did == 0)) return;
                    
        if ((gSpecificControllers[Index].Vid == HcStruc->Vid) &&
            (gSpecificControllers[Index].Did == HcStruc->Did)) {
            Flag = (UINT32) LShiftU64 (1, (gSpecificControllers[Index].Flag));
            HcStruc->HcFlag |= Flag;
        }
    
    }
}

/**
    Compare two device path is same of not.

    @param  DpSrc      the first Device path to compare.  
    @param  DpTarget   the second device path to compare.
           
    @retval TRUE       These devicePaths are same.
    @retval FALSE      These devicePaths are different.

**/
BOOLEAN
IsSameDevicePath(
  IN EFI_DEVICE_PATH_PROTOCOL *DpSrc,
  IN EFI_DEVICE_PATH_PROTOCOL *DpTarget
)
{
  UINTN Len;  
  
  //if both devicePaths are null, return true.
  if(!DpSrc && !DpTarget) return TRUE;
  
  // Only one is null, return false.
  if(!DpSrc || !DpTarget) return FALSE;
  Len = GetDevicePathSize(DpTarget);
  if (GetDevicePathSize (DpSrc) == Len){
    if (CompareMem(DpSrc, DpTarget, Len) == 0) return  TRUE;
    else return FALSE;
  } 
  return FALSE;
}

/**
    This function checks the controller data of Usb Controller which is exist. If HC is found appropriate, then
    return HCStruc.

    @param  Controller  Host controller handle number
    @param  DevicePath  Point to DevicePath protocol 
            
    @retval HC_STRUC    Point to host controller struct
**/
HC_STRUC*
CheckUsbController (
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath  
)
{
    UINT8       Index;
    HC_STRUC    *HcStruc;
    
    if (gUsbDataList->HcTableCount){
        for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
            HcStruc = gHcTable[Index];
            if (HcStruc->Controller == Controller) {
                if(HcStruc->HcFlag & HC_STATE_USED){
                    USB_DEBUG(DEBUG_DEV_INIT, "HcStruc aleady exist and start Vid %x Did %x BusDevFuncNum %x HcNumber %x HcFlag %x\n",HcStruc->Vid,HcStruc->Did,HcStruc->BusDevFuncNum,HcStruc->HcNumber,HcStruc->HcFlag);
                    return  HcStruc;
                }
                
            }
        }
    }
    USB_DEBUG(DEBUG_DEV_INIT, "New Usb Hc Add Hc Structure \n");
    return  NULL;
}
/**
    This function checks the type of controller and its PCI info
    against gHcPciInfo data table; if HC is found appropriate, then
    it allocates the frame list for this HC and adds the new HCStruc
    entry.

    @param  Controller  Host controller handle number
    @param  DevicePath  Point to DevicePath protocol 
            
    @retval HC_STRUC    Point to host controller struct

**/

HC_STRUC*
AddHC (
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    HC_STRUC                                *HcStruc = NULL;
    UINT8                                   Index;
    UINT16                                  PciAddr;
    EFI_STATUS                              Status;
    UINT64                                  Supports;
    EFI_ACPI_QWORD_ADDRESS_SPACE_DESCRIPTOR *Resources = NULL;
    AMI_USB_HW_SMI_HC_CONTEXT               *HcContext;
    EFI_PHYSICAL_ADDRESS                    PhyAddr;
    VOID                                    *Mapping;
    EFI_PCI_IO_PROTOCOL_OPERATION           Operation;
    UINTN                                   Bytes;
    UINT8                                   HcIndex;
    UINTN                                   Size;
    UINT64                                  UsbdataPhyAddr = 0;
    VOID                                    *UsbdataMapping = NULL;
    USB3_HOST_CONTROLLER                    **Usb3HcMem = NULL;
    UINTN                                   Usb3HcIndex;
    USB3_HOST_CONTROLLER                    *Usb3Hc = NULL;
    UINTN                                   PciSeg;
    UINTN                                   PciBus;
    UINTN                                   PciDev;
    UINTN                                   PciFunc;
    EFI_PCI_IO_PROTOCOL                     *PciIo;
    UINT8                                   HcType;
    UINT8                                   Irq;
    UINT8                                   HCSpecificInfoSize;
    
    USB_DEBUG(DEBUG_DEV_INIT, "AddHC \n");
    
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIo,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC PciIo %r \n", Status);
        return NULL;
    }
    

    Status = PciIo->GetLocation(PciIo, &PciSeg, &PciBus, &PciDev, &PciFunc);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC Pci GetLocation %r \n", Status);
        return NULL;
    }
    
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, PCI_CLASSCODE_OFFSET, 1, &HcType);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC Pci Get PCI_CLASSCODE_OFFSET %r \n", Status);
        return NULL;
    }
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, PCI_INT_LINE_OFFSET, 1, &Irq);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC Pci Get PCI_INT_LINE_OFFSET %r \n", Status);
        return NULL;
    }
    if((HcType + USB_HC_UHCI) == USB_HC_XHCI){
        if (gUsbDataList == NULL) return NULL;
        if (gUsbDataList->Usb3HcMem == NULL) return NULL;
        if ((gUsbData->UsbFeature & USB_HC_XHCI_SUPPORT) == 0) return NULL;
        
        Usb3HcMem = (USB3_HOST_CONTROLLER**)gUsbDataList->Usb3HcMem;
        for (Usb3HcIndex = 0; Usb3HcIndex < gUsbDataList->Usb3HcCount; Usb3HcIndex++) {
            Usb3Hc = (USB3_HOST_CONTROLLER*)((UINTN)Usb3HcMem + ((sizeof(USB3_HOST_CONTROLLER*)) * gUsbDataList->Usb3HcCount) + ((sizeof(USB3_HOST_CONTROLLER)) * Usb3HcIndex));
            if(Usb3Hc->Controller == Controller){
                if (Usb3Hc->DcbaaPages == 0x00) {
                    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Xhci: DcbaaPages is 0 HC unsupported \n");
                    return NULL;
                }
            }
        }
    }
    //PciAddr   Bit15-Bit8:Bus, Bit7-Bit3:Device,
    //          Bit2-Bit0:Function
    PciAddr = (UINT16)((PciBus << 8) | (PciDev << 3) | PciFunc);
    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
        if (gHcTable[Index] == NULL) {
            continue;
        }
        if (gHcTable[Index]->HcFlag & HC_STATE_USED) {
            continue;
        }
        if (IsSameDevicePath(gHcTable[Index]->HcDevicePath, DevicePath)) { 
            break;
        }
    }

    if (Index != gUsbDataList->HcTableCount) {
        HcStruc = gHcTable[Index];
    } else {
        gUsbDataList->HcTableCount++;
        
        for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
            if (gHcTable[Index] == NULL) {
                break;
            }
        }

        if (Index == gUsbDataList->HcTableCount) {
            return NULL;
        }
        HcStruc = (HC_STRUC*)AllocAlignedMemory (sizeof(HC_STRUC), 0x10);
        if (HcStruc == NULL) return NULL;
    }

    gHcTable[Index] = HcStruc;
        
    USB_DEBUG(DEBUG_DEV_INIT, "AddHC for device %x HcStruc %x Index %x \n", PciAddr,HcStruc,Index);

    //
    // Initialize the HC_STRUC with available values
    //
    HcStruc->HcFlag |= HC_STATE_USED;
    HcStruc->HcNumber = Index + 1;
    HcStruc->HcType = (UINT8)(HcType + USB_HC_UHCI);
    HcStruc->BusDevFuncNum = PciAddr;
    HcStruc->Controller = Controller;
    HcStruc->Irq = Irq;
    HcStruc->HcDevicePath = DevicePath;
    HcStruc->PciIo = PciIo;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint16, PCI_VENDOR_ID_OFFSET, 1, &HcStruc->Vid);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC Read Vendor error: %r at %x\n", Status, PCI_VENDOR_ID_OFFSET);
        return NULL;
    }

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint16, PCI_DEVICE_ID_OFFSET, 1, &HcStruc->Did);
    if (EFI_ERROR(Status)) {
        USB_DEBUG(DEBUG_DEV_INIT, "HC Read Device error: %r at %x\n", Status, PCI_DEVICE_ID_OFFSET);
        return NULL;
    }

    Status = PciIo->GetBarAttributes(PciIo, 0, &Supports, (VOID**)&Resources);
    if (!EFI_ERROR (Status)) {
        HcStruc->BaseAddressSize = (UINTN)Resources->AddrLen;
        gBS->FreePool(Resources);
    }
    
    CheckSpecificController(HcStruc);

    //
    // Allocate memory for Host Controller
    // HC Type Index: 0/1/2/3 for U/O/E/XHCI
    //
    HcIndex = (UINT8)(HcType >> 4);
    HCSpecificInfoSize = (sizeof(gHCSpecificInfo)/sizeof(HC_SPECIFIC_INFO)) - 1;
    ASSERT(!(HCSpecificInfoSize<HcIndex));
    
    Status = gHCSpecificInfo[HcIndex].HcPreInit(Controller, HcStruc);
    if (EFI_ERROR(Status)) {
        SetMem(HcStruc, sizeof(HC_STRUC), 0);
        return NULL;
    }

    if (gHCSpecificInfo[HcIndex].FrameListSize) {
        if (HcStruc->FrameList == NULL) {
            HcStruc->FrameList = (UINT32*)AllocateHcMemory ( PciIo,
                                    EFI_SIZE_TO_PAGES(gHCSpecificInfo[HcIndex].FrameListSize), 
                                    gHCSpecificInfo[HcIndex].FrameListAlignment);

            if (HcStruc->FrameList == NULL) {
                SetMem(HcStruc, sizeof(HC_STRUC), 0);
                return NULL;
            }
            USB_DEBUG(DEBUG_DEV_INIT, "Frame List AllocateHcMemory at %x.\n", HcStruc->FrameList);
        }
        Status = UsbHcMemoryRecord(HcStruc->Controller,
                     (EFI_PHYSICAL_ADDRESS)HcStruc->FrameList,
                     EFI_SIZE_TO_PAGES(gHCSpecificInfo[HcIndex].FrameListSize));
        if(EFI_ERROR(Status)){
            return NULL;
        }
        SetMem(HcStruc->FrameList, gHCSpecificInfo[HcIndex].FrameListSize, 0);
        USB_DEBUG(DEBUG_DEV_INIT, "Frame List is allocated at %016lx.\n", HcStruc->FrameList);

        if ((!(gUsbData->UsbStateFlag & USB_FLAG_AFTER_END_OF_DXE)) &&
            (gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON) &&
            (HcStruc->FrameListMapping == NULL)) {
            Operation = EfiPciIoOperationBusMasterCommonBuffer;
            Bytes = gHCSpecificInfo[HcIndex].FrameListSize;
            Status = PciIo->Map(PciIo, Operation, HcStruc->FrameList, &Bytes, &PhyAddr, &Mapping);

            if ((!EFI_ERROR(Status)) && (Bytes == gHCSpecificInfo[HcIndex].FrameListSize)) {
                HcStruc->FrameListPhyAddr = (VOID*)(UINTN)PhyAddr;
                HcStruc->FrameListMapping = Mapping;
                USB_DEBUG(DEBUG_DEV_INIT, "HcStruc->FrameList %x Mapping %x\n", PhyAddr, Mapping);
            } else {
                HcStruc->FrameListPhyAddr = HcStruc->FrameList;
                HcStruc->FrameListMapping = NULL;
                USB_DEBUG(DEBUG_DEV_INIT, "HcStruc->FrameList PciIo->Map Status %r \n", Status);
            }
        }
    }

    for (Index = 0; Index < gEfiUsbPolicyProtocol.AmiUsbHwSmiHcTable.HcCount; Index++) {
        HcContext = gEfiUsbPolicyProtocol.AmiUsbHwSmiHcTable.HcContext[Index];

        if(IsSameDevicePath(HcContext->Device, HcStruc->HcDevicePath)) {
            HcStruc->HwSmiHandle = HcContext->HwSmiHandle;
            break;
        }
    }

    if ((HcStruc->HwSmiHandle == NULL) && (IsExternalController(DevicePath))) {
        HcStruc->HcFlag |= HC_STATE_EXTERNAL;
    }

    if ((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == USB_IRQ_INTERRUPT_SUPPORT) {
        HcStruc->HcFlag |= HC_STATE_IRQ;
    }

    if (!(gUsbData->UsbStateFlag & USB_FLAG_AFTER_END_OF_DXE)) {
        if (gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON) {
            Size = ((UINTN)(gUsbData->MemPages) << 12);
            Size += (UINTN)MAX_CONSUME_BUFFER_SIZE;
            Size += (UINTN)MAX_TEMP_BUFFER_SIZE;
            USB_DEBUG(DEBUG_DEV_INIT, "UsbdataPhyAddr  %lx  %lx %lx %r (gUsbDataList->MemBlockStart + Size) %x \n", UsbdataPhyAddr, gUsbDataList->MemBlockStart, UsbdataMapping, Status, (gUsbDataList->MemBlockStart + Size));
            Status = PciIo->Map(PciIo, EfiPciIoOperationBusMasterCommonBuffer, gUsbDataList->MemBlockStart, &Size, (EFI_PHYSICAL_ADDRESS *)&UsbdataPhyAddr, &UsbdataMapping);
            if (!EFI_ERROR (Status)) {
                USB_DEBUG(DEBUG_DEV_INIT, "UsbdataPhyAddr  %lx  %lx %lx %r  (UsbdataPhyAddr + size) %x  \n", UsbdataPhyAddr, gUsbDataList->MemBlockStart, UsbdataMapping, Status, (UsbdataPhyAddr + Size));
                HcStruc->MemBlockStartPhy = (UINT8*)(VOID*)(UINTN)UsbdataPhyAddr;
                HcStruc->MemBlockStartMapping = UsbdataMapping;
                USB_DEBUG(DEBUG_DEV_INIT, "MemBlockStartMapping %x\n", HcStruc->MemBlockStartMapping);
            } else {
                HcStruc->MemBlockStartPhy = gUsbDataList->MemBlockStart;
                HcStruc->MemBlockStartMapping = NULL;
                USB_DEBUG(DEBUG_DEV_INIT, "MemBlockStart PciIo->Map Status %r MemBlockStartMapping %x \n", Status,HcStruc->MemBlockStartMapping);
            }
        }
    }

    gUsbDataList->NumOfHc++;

    USB_DEBUG(DEBUG_DEV_INIT, "Controller #%x added to HCStrucTable\n", HcStruc->HcNumber);

    return HcStruc;
}


/**
    This function invokes USB Mass Storage API handler to
    check whether device is ready. If called for the first time,
    this function retrieves the mass storage device geometry
    and fills the corresponding FpDevInfo fields.

    @param DevInfo    Pointer to device which needs to be checked

**/

VOID
CheckDeviceReady(DEV_INFO* DevInfo)
{
    if ((gUsbData->UsbDevSupport & USB_MASS_DEV_SUPPORT) == USB_MASS_DEV_SUPPORT){
        USB_DEBUG(DEBUG_DEV_INIT, "UHCD CheckDeviceReady-->");
        
        //
        // Prepare URP_STRUC with USB_MassRead attributes
        //
        gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
        gParameters->FuncNumber  = USB_API_MASS_DEVICE_REQUEST;
        gParameters->SubFunc   = USB_MASSAPI_CHECK_DEVICE;
        gParameters->ApiData.MassChkDevReady.FpDevInfo = DevInfo;
        
        InvokeUsbApi(gParameters);
        USB_DEBUG(DEBUG_DEV_INIT, "-->done.\n");
    }

}

/**
    This function returns a name string of connected mass storage
    device.

    @param Data      Pointer to a string buffer to be filled
    @param DataSize  Size of the data to copy to a buffer
    @param DevIndex  Device index
    @retval Value    The updated device index, see below.

    @note  Initially DevIndex should be set to 0. This function returns
              the name of the first mass storage device (if no device found
              it returns DevIndex as 0FFh) and also updates DevIndex to the
              device address of the current mass storage device. If no other
              mass storage device is found then the routine sets the bit7 to 1
              indicating current information is valid but no more mass device
              found in the system. The caller can get the next device info if
              DevIndex is not 0FFh and bit7 is not set.

**/

UINT8
EFIAPI
GetNextMassDeviceName(
    UINT8   *Data,
    UINT8   DataSize,
    UINT8   DevIndex
)
{
    UINT8   Index;
    UINT8   CurrentDevIndex;

    for (Index = DevIndex; Index < gUsbData->MaxDevCount; Index++) {
        if (!(gUsbDataList->DevInfoTable[Index].Flag & DEV_INFO_DEV_PRESENT)) {
            continue;
        }
        if (gUsbDataList->DevInfoTable[Index].DeviceType == BIOS_DEV_TYPE_STORAGE) {
            break;
        }
    }
    if (Index == gUsbData->MaxDevCount) {
        // No mass storage devices present
        return USB_ERROR;
    }

    //
    // Copy device name
    //
    CopyMem(Data, &gUsbDataList->DevInfoTable[Index].DevNameString, DataSize);

    CurrentDevIndex = Index;
    
    //
    // Look for the other devices for any subsequent calls
    //
    for (Index++; Index < gUsbData->MaxDevCount; Index++) {
        if (gUsbDataList->DevInfoTable[Index].DeviceType == BIOS_DEV_TYPE_STORAGE) {
            break;
        }
    }
    if (Index == gUsbData->MaxDevCount) {
        // No other devices, return current device w/ bit7
        CurrentDevIndex |= 0x80;
    } else {
        // Return next device index
        CurrentDevIndex = Index;
    }

    return CurrentDevIndex;

}

/**
    Clear legacy usb keybaord buffer.
**/

VOID
ClearLegacyUsbKbdBuffer(
    VOID
)
{

    SetMem(gUsbData->KbcCharacterBufferStart, sizeof(gUsbData->KbcCharacterBufferStart), 0);
    gUsbDataList->KbcCharacterBufferHead = gUsbData->KbcCharacterBufferStart;
    gUsbDataList->KbcCharacterBufferTail = gUsbData->KbcCharacterBufferStart;
    
    SetMem(gUsbData->KbcScanCodeBufferStart, sizeof(gUsbData->KbcScanCodeBufferStart), 0);
    gUsbDataList->KbcScanCodeBufferPtr = gUsbData->KbcScanCodeBufferStart;
                                    
    SetMem(gUsbData->KbcDeviceIdBufferStart, sizeof(gUsbData->KbcDeviceIdBufferStart), 0);               //(EIP102150+)
    SetMem(gUsbData->KbcShiftKeyStatusBufferStart, sizeof(gUsbData->KbcShiftKeyStatusBufferStart), 0);   //(EIP102150+)    
    
    SetMem(gUsbData->UsbKbInputBuffer, sizeof(gUsbData->UsbKbInputBuffer), 0);
}

/**
    This is the interface function that reports switches between EFI and
    Legacy USB operation.

    @param EfiToLegacy  Switch that indicates where the switch should be turned:
                        1 - from EFI to Legacy
                        0 - from Legacy to EFI

**/

VOID
EFIAPI
UsbChangeEfiToLegacy(
    UINT8 EfiToLegacy
)
{
                                        //(EIP96616+)>
    DEV_INFO        *DevInfo =  NULL; 
    DEV_INFO        *DevInfoEnd = gUsbDataList->DevInfoTable + gUsbData->MaxDevCount;
    UINTN           Index = 0;
    HC_STRUC        *HcStruc = NULL;
    EFI_TPL         OldTpl = 0;
    EFI_STATUS      Status;
    UINT8           ExtUsbHost = FALSE;
    UINT8           SmiSource;

    if (gUsbData->UsbFeature2 & USB_SKIP_UEFI_DRIVER) return;

    if (EfiToLegacy) {  // Changing to Legacy
        if(gEmulationTrap != NULL && gLegacyUsbStatus) {
            gEmulationTrap->TrapEnable(gEmulationTrap);
        }
        ClearLegacyUsbKbdBuffer();
        
        // Find the AMI USB ISR protocol.
        if ((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == USB_IRQ_INTERRUPT_SUPPORT){
            if (gAmiUsbIsrProtocol != NULL) {
                gAmiUsbIsrProtocol->InstallLegacyIsr(gAmiUsbIsrProtocol);
            }
        }


        gUsbData->UsbStateFlag &= ~USB_FLAG_RUNNING_UNDER_EFI;

        if (((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == 0) &&
            (gUsbData->UsbRuntimeDriverInSmm == USB_RUNTIME_DRV_MODE_2)) {
            // get HCD protocol
            if (gDxeUsbHcdTable == NULL){
                Status = GetHcdTable();
                if (EFI_ERROR(Status)){
                    USB_DEBUG(DEBUG_DEV_INIT, "error GetHcdTable %r\n",Status);
                }
            }
            OldTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
            for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
                HcStruc = gHcTable[Index];
                if (HcStruc == NULL) {
                    continue;
                }
                if (HcStruc->HcFlag & HC_STATE_RUNNING) { 
                    if (HcStruc->HcFlag & HC_STATE_EXTERNAL) ExtUsbHost = TRUE;
                    if ((gUsbData->UsbFeature2 & USE_BS_MEM_IN_UEFI)== 0){
                        AmiUsbSmiControl(HcStruc, TRUE);
                    }
                }
            }
            
            // Check External USB host. Enable Timer SMI before enter legacy OS.
            if (((gUsbData->UsbFeature & USB_EXTERNAL_CONTROLLER_SUPPORT) == USB_EXTERNAL_CONTROLLER_SUPPORT) &&
                (gUsbData->UsbRuntimeDriverInSmm>USB_RUNTIME_DRV_MODE_0)){
                
                Status = GetSmiSource(&SmiSource);
                if ((!EFI_ERROR(Status)) && (ExtUsbHost==TRUE)){
                    if (!(SmiSource&PERIODIC_TIMER_SMI_SOURCE_IS_ENABLE)) gDisableTimerSmi = TRUE;
                }
                if (gDisableTimerSmi) SettingTimerSMI(TRUE);
            }
            gBS->RestoreTPL(OldTpl);
        }

    } else {           // Changing to EFI

        if (((gUsbData->UsbFeature & USB_IRQ_INTERRUPT_SUPPORT) == 0) &&
            (gUsbData->UsbRuntimeDriverInSmm == USB_RUNTIME_DRV_MODE_2)) {
            // get HCD protocol
            if (gDxeUsbHcdTable == NULL){
                Status = GetHcdTable();
                if (EFI_ERROR(Status)){
                    USB_DEBUG(DEBUG_DEV_INIT, "error GetHcdTable %r\n",Status);
                }
            }
            OldTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
            for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
                HcStruc = gHcTable[Index];
                if (HcStruc == NULL) {
                    continue;
                }
                if (HcStruc->HcFlag & HC_STATE_RUNNING) { 
                    if ((gUsbData->UsbFeature2 & USE_BS_MEM_IN_UEFI)== 0){
                        AmiUsbSmiControl(HcStruc, FALSE);
                    }
                }
            }

            // Check External USB host. Enable Timer SMI before enter UEFI.
            if (((gUsbData->UsbFeature & USB_EXTERNAL_CONTROLLER_SUPPORT) == USB_EXTERNAL_CONTROLLER_SUPPORT) &&
                (gUsbData->UsbRuntimeDriverInSmm>USB_RUNTIME_DRV_MODE_0)){
                if (gDisableTimerSmi) SettingTimerSMI(FALSE);
            }
            gBS->RestoreTPL(OldTpl);
        }

        if (gEmulationTrap != NULL && gLegacyUsbStatus) {
            gEmulationTrap->TrapDisable(gEmulationTrap);
        }
        ClearLegacyUsbKbdBuffer();
        
        for (DevInfo = &gUsbDataList->DevInfoTable[1]; DevInfo != DevInfoEnd; ++DevInfo ){
            if (DevInfo->BusErrorStaus != BUS_NO_ERROR_DEVICE_CONFIG_DESCRIPTOR) {
                continue;
            }
            if (DevInfo->Flag & DEV_INFO_IN_QUEUE) {
                continue;
            }
            if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT) == DEV_INFO_VALID_STRUC) {
                if (DevInfo->Flag & DEV_INFO_DEV_BUS) {
                    QueuePut(&gQueueCnnctDisc, DevInfo);
                    DevInfo->Flag |= DEV_INFO_IN_QUEUE;
                    continue;
                }
            }
            if ((DevInfo->Flag & DEV_INFO_VALIDPRESENT) == DEV_INFO_VALIDPRESENT) {
                if (!(DevInfo->Flag & DEV_INFO_DEV_BUS)) {
                    QueuePut(&gQueueCnnctDisc, DevInfo);
                    DevInfo->Flag |= DEV_INFO_IN_QUEUE;
                }
            }
        }
        gUsbData->UsbStateFlag |= USB_FLAG_RUNNING_UNDER_EFI;
    }
                                        //<(EIP96616+)
}


/**
    This is the interface function that reports the number of devices
    currently controlled by the driver.

    @param Devs    Pointer to a structure that indicates the number of connected devices.

**/

VOID
EFIAPI
ReportDevices(
    IN OUT CONNECTED_USB_DEVICES_NUM    *Devs
)
{
    HC_STRUC    *HcStruc;
    UINT8       Index;
    UINT8       Kbd = 0;
    UINT8       Hub = 0;
    UINT8       Mouse = 0;
    UINT8       Mass = 0;
    UINT8       Point = 0;
    UINT8       Uhci = 0;
    UINT8       Ohci = 0;
    UINT8       Ehci = 0;
    UINT8       Xhci = 0;
    
    for (Index = 1; Index < gUsbData->MaxDevCount; Index++) {

        if ((gUsbDataList->DevInfoTable[Index].Flag & DEV_INFO_VALIDPRESENT) 
            != DEV_INFO_VALIDPRESENT) {
            continue;
        }
        switch (gUsbDataList->DevInfoTable[Index].DeviceType) {
            case BIOS_DEV_TYPE_HID:
                if (gUsbDataList->DevInfoTable[Index].HidDevType & HID_DEV_TYPE_KEYBOARD) {
                    Kbd++;
                }
                if (gUsbDataList->DevInfoTable[Index].HidDevType & HID_DEV_TYPE_MOUSE) {
                    Mouse++;
                }
                if (gUsbDataList->DevInfoTable[Index].HidDevType & HID_DEV_TYPE_POINT) {
                    Point++;
                }
                break;
            case BIOS_DEV_TYPE_HUB:
                Hub++;
                break;
            case BIOS_DEV_TYPE_STORAGE:
                Mass++;
                break;
            default:
                break;
        }
    } 

    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
        HcStruc = gHcTable[Index];
        if (HcStruc == NULL) {
            continue;
        }
        if (!(HcStruc->HcFlag & HC_STATE_USED)) {
            continue;
        }
        switch (HcStruc->HcType) {
            case USB_HC_UHCI:
                Uhci++;
                break;
            case USB_HC_OHCI:
                Ohci++;
                break;
            case USB_HC_EHCI:
                Ehci++;
                break;
            case USB_HC_XHCI:
                Xhci++;
                break;
            default:
                break;
        }
    } 
    
    (*Devs).NumUsbKbds = Kbd;
    (*Devs).NumUsbMice = Mouse;
    (*Devs).NumUsbPoint = Point;
    (*Devs).NumUsbMass = Mass;
    (*Devs).NumUsbHubs = Hub;
    (*Devs).NumUhcis = Uhci;
    (*Devs).NumOhcis = Ohci;
    (*Devs).NumEhcis = Ehci;
    (*Devs).NumXhcis = Xhci;

}

/**
    Stop USB controller in legacy.

**/
VOID
EFIAPI
UsbRtShutDownLegacy(
    VOID
)
{
    if (gLegacyUsbStatus) {
        gLegacyUsbStatus=FALSE;
        gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
        gParameters->FuncNumber = USB_API_STOP;
        gParameters->SubFunc = 0;
        USB_DEBUG(DEBUG_DEV_INIT, "Stop USB controllers.\n");
        InvokeUsbApi(gParameters);
        // Disconnect devices and uninstall usb device related protocols
        if (gEvUsbEnumTimer != 0) {
            UsbHcOnTimer(gEvUsbEnumTimer, NULL);
        }
    }
}    
                                                                                //(EIP74876+)>
/**
    This function stops the USB host controllers of a given 
    Bus Dev Function
    @param HcBusDevFuncNum    PCI bus/dev/fun

**/

VOID
EFIAPI
UsbRtStopController(
    UINT16 HcBusDevFuncNum
)
{
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_USB_STOP_CONTROLLER;
    gParameters->ApiData.HcBusDevFuncNum = HcBusDevFuncNum;
    InvokeUsbApi(gParameters);
    
    // Disconnect devices and uninstall usb device related protocols
    if (gEvUsbEnumTimer != 0) {
        UsbHcOnTimer(gEvUsbEnumTimer, NULL);
    }
}
                                                                                //<(EIP74876+)

/**
    Visit all companions as different PCI functions of the same
    PCI device as Controller (enumerate HCPCIInfo ). For each
    companion function locate corresponding PCI_IO handle, execute
    ConnectController if necessary; add them to aHCStrucTable.

    @param This                 Protocol instance pointer.
    @param Controller           Handle of device to test
    @param RemainingDevicePath  Optional parameter use to pick a specific child
                                device to start.
    @retval EFI_SUCCESS         Success to connect EHCI controller before 1.0 init 
                                controller.

**/

EFI_STATUS
LocateEhciController(
    IN EFI_DRIVER_BINDING_PROTOCOL      *This,
    IN EFI_HANDLE                       Controller,
    IN EFI_DEVICE_PATH_PROTOCOL         *CompanionDevicePath
)
{
    EFI_STATUS                  Status;
    EFI_DEVICE_PATH_PROTOCOL    *Dp = CompanionDevicePath;
    EFI_DEVICE_PATH_PROTOCOL    *DpLastPciNode = NULL;
    EFI_DEVICE_PATH_PROTOCOL    *DpBridge;
    EFI_DEVICE_PATH_PROTOCOL    *DpRemaining;
    EFI_HANDLE                  Bridge = NULL;
    UINT8                       EhciFunc;
    EFI_DEVICE_PATH_PROTOCOL    *DpEhci;
    PCI_DEVICE_PATH             *DpEhciPciNode;
    EFI_HANDLE                  Ehci = NULL;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    UINTN                       SegNum;
    UINTN                       BusNum;
    UINTN                       DevNum;
    UINTN                       FuncNum;
    USB_CLASSC                  UsbClassCReg;
    EFI_USB2_HC_PROTOCOL        *UsbHc2Protocol;
    UINT8                       ConnectAttempt;

    USB_DEBUG(DEBUG_DEV_INIT, "LocateEhciController..\n");

    while(!IsDevicePathEnd(Dp)) {
        Dp = NextDevicePathNode(Dp);
        if ((Dp->Type == HARDWARE_DEVICE_PATH) && 
            (Dp->SubType == HW_PCI_DP)) {
            DpLastPciNode = Dp;
        }
    }

    if (DpLastPciNode == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    DpBridge = DuplicateDevicePath(CompanionDevicePath);
    if (DpBridge == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Dp = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)DpBridge +
            ((UINT8*)DpLastPciNode - (UINT8*)CompanionDevicePath));

    Dp->Type = END_DEVICE_PATH_TYPE;
    Dp->SubType = END_ENTIRE_DEVICE_PATH_SUBTYPE;
    SetDevicePathNodeLength(Dp, sizeof(EFI_DEVICE_PATH_PROTOCOL));

    DpRemaining = DpBridge;
    Status = gBS->LocateDevicePath(
                    &gEfiDevicePathProtocolGuid,
                    &DpRemaining,
                    &Bridge);
    gBS->FreePool(DpBridge);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    DpEhci = DuplicateDevicePath(CompanionDevicePath);
    if (DpEhci == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    DpEhciPciNode = (PCI_DEVICE_PATH*)((UINT8*)DpEhci +
            ((UINT8*)DpLastPciNode - (UINT8*)CompanionDevicePath)); // Locate last PCI node
    EhciFunc = ((PCI_DEVICE_PATH*)DpLastPciNode)->Function;

    for (EhciFunc++; EhciFunc <= 7; EhciFunc++) {
        DpEhciPciNode->Function = EhciFunc;

        ConnectAttempt = 0;
        do {
            USB_DEBUG(DEBUG_DEV_INIT, "\ttry Dev# %x Func# %x...",
                    DpEhciPciNode->Device, DpEhciPciNode->Function);

            DpRemaining = DpEhci;
            // Locate EHCI handle using device path
            Status = gBS->LocateDevicePath(
                            &gEfiPciIoProtocolGuid,
                            &DpRemaining,
                            &Ehci);
            if (!EFI_ERROR(Status)) {
                Status = gBS->OpenProtocol(
                            Ehci,
                            &gEfiPciIoProtocolGuid,
                            (VOID**)&PciIo,
                            This->DriverBindingHandle,
                            Ehci,
                            EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
                ASSERT_EFI_ERROR(Status);
                if (EFI_ERROR(Status)) {
                    break;
                }
                Status = PciIo->GetLocation(
                            PciIo, 
                            &SegNum, 
                            &BusNum, 
                            &DevNum, 
                            &FuncNum);
                ASSERT_EFI_ERROR(Status);
                if (EFI_ERROR(Status)) {
                    break;
                }
                if ((DevNum == DpEhciPciNode->Device) &&
                    (FuncNum == DpEhciPciNode->Function)) {
                    Status = PciIo->Pci.Read(
                            PciIo,
                            EfiPciIoWidthUint8,
                            CLASSC,
                            sizeof(USB_CLASSC),
                            &UsbClassCReg);
                    ASSERT_EFI_ERROR(Status);
                    if (EFI_ERROR(Status) ||
                        (UsbClassCReg.BaseCode != PCI_CLASSC_BASE_CLASS_SERIAL) ||
                        (UsbClassCReg.SubClassCode != PCI_CLASSC_SUBCLASS_SERIAL_USB) ||
                        (UsbClassCReg.PI != PCI_CLASSC_PI_EHCI)) {
                        USB_DEBUG(DEBUG_DEV_INIT, "BaseCode %x, SubClassCode %x, PI %x...", 
                            UsbClassCReg.BaseCode, UsbClassCReg.SubClassCode, UsbClassCReg.PI);
                        Status = EFI_NOT_FOUND;
                        USB_DEBUG(DEBUG_DEV_INIT, "%r\n", Status);
                        break;
                    }
                    Status = gBS->OpenProtocol(
                            Ehci,
                            &gEfiUsbHcProtocolGuid,
                            (VOID**)&UsbHc2Protocol,
                            This->DriverBindingHandle,
                            Ehci,
                            EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
                    if (!EFI_ERROR(Status)) {
                        Status = EFI_ALREADY_STARTED;
                        USB_DEBUG(DEBUG_DEV_INIT, "%r\n", Status);
                        break;
                    }
                    
                        Status = gBS->ConnectController(Ehci, NULL, NULL, FALSE);
                        if (EFI_ERROR(Status)) {
                            USB_DEBUG(DEBUG_DEV_INIT, "EHCI ConnectController %r\n", Status);
                        }
                        break;
                    }
                }

            // ConnectController to produce EHCI handle.
            // Do not assert on EFI_ERROR because controller
            // might not be functional (hidden for example) due
            // to the board implementation or project policy and
            // unsuccessfull connection is okay.
            Status = gBS->ConnectController(Bridge, 0,
                    (EFI_DEVICE_PATH_PROTOCOL*)DpEhciPciNode, FALSE);
        } while (!EFI_ERROR(Status) && (++ConnectAttempt < 2));
    }

    gBS->FreePool(DpEhci);

    return EFI_SUCCESS;
}

/**
    This function returns the beginning and the end of USB 
    runtime memory region.

    @param  Start        Ptr to memory start address.
    @param  End          Ptr to memory end address.
    @retval EFI_SUCCESS  Success to get runtime region.
**/

EFI_STATUS
EFIAPI
UsbGetRuntimeRegion(
    EFI_PHYSICAL_ADDRESS *Start,
    EFI_PHYSICAL_ADDRESS *End
)
{
    GetRuntimeRegion (Start, End);
    return EFI_SUCCESS;
}


/**
    This function is a legacy mass storage support API stub,
    replaced by the API producer.
    @param Device             Ptr to USB_MASS_DEV.
    @retval EFI_UNSUPPORTED   This routne is dummy.

**/

EFI_STATUS
EFIAPI
Dummy1(
    USB_MASS_DEV*   Device
)
{
    return EFI_UNSUPPORTED;
}

/**
    This function is a legacy mass storage support API stub,
    replaced by the API producer.

    @param  None
    @retval EFI_UNSUPPORTED   This routne is dummy.

**/

EFI_STATUS
EFIAPI
Dummy2(
    VOID
)
{
    return EFI_UNSUPPORTED;
}


/**
    This function is dummy HC memory allocation routine.

    @param  Handle            Handle number
    @param  HCStruc           Pointer to the HCStruc structure

    @retval EFI_SUCCESS       This routne is dummy.

**/

EFI_STATUS
DummyHcFunc(
    EFI_HANDLE  Handle,
    HC_STRUC    *HcStruc
)
{
    return EFI_SUCCESS;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
