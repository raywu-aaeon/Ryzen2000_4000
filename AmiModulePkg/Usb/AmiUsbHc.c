//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AmiUsbHc.c
    USB_HC_PROTOCOL implementation

**/

#include "Uhcd.h"
#include <Xhci.h>
#include "Tree.h"
#include <Protocol/Cpu.h>
#include <Protocol/AmiUsbHcMemRecordProtocol.h>

extern USB_GLOBAL_DATA *gUsbData;
extern USB_DATA_LIST   *gUsbDataList;
extern URP_STRUC       *gParameters;
extern HC_STRUC        **gHcTable;

static UINT8 gSpeedMap[] = { 0x10, 0x01, 0, 0 };

UINT8   *gUsbBusTempBuffer = NULL;
UINTN   gTempBufferPages = 0;
UINTN   *gCoreStackBuffer = NULL;

/**
    Function returns a pointer to HcProtocol2 record of a given protocol

    @param   Protocol  EFI USB2 Hc protocol

    @retval  Pointer   Function returns a pointer to HcProtocol2 record of a given protocol

**/

static HC_DXE_RECORD* GetThis(EFI_USB2_HC_PROTOCOL* Protocol)
{
    return (HC_DXE_RECORD*)((char*)Protocol - (UINTN)&((HC_DXE_RECORD*)0)->HcProtocol2);
}


/**
    Function returns a pointer to HcProtocol record of a given protocol

    @param   Protocol  EFI USB Hc protocol

    @retval  Pointer   Function returns a pointer to HcProtocol record of a given protocol

**/

static HC_DXE_RECORD* GetThis1 (EFI_USB_HC_PROTOCOL* Protocol)
{
    return (HC_DXE_RECORD*)((char*)Protocol - (UINTN)&((HC_DXE_RECORD*)0)->HcProtocol);
}


/**
    Function converts the bitmap of DevInfo->UsbLastCommandStatusExtended into
    a valid USB error.

**/

static UINT32 GetTransferStatus(
  IN DEV_INFO    *DevInfo        
)
{
    static struct { UINT32 BitDst, BitSrc; } ErrorMap[] = {
        {EFI_USB_ERR_STALL,      USB_TRSFR_STALLED},
        {EFI_USB_ERR_STALL,      USB_BULK_STALLED},
        {EFI_USB_ERR_STALL,      USB_CONTROL_STALLED},
        {EFI_USB_ERR_BUFFER,     USB_TRSFR_BUFFER_ERROR},
        {EFI_USB_ERR_BABBLE,     USB_TRNSFR_BABBLE},
        {EFI_USB_ERR_NAK,        USB_TRNSFR_NAK},
        {EFI_USB_ERR_CRC,        USB_TRNSFR_CRCERROR},
        {EFI_USB_ERR_TIMEOUT,    USB_TRNSFR_TIMEOUT},     //(EIP84790)
        {EFI_USB_ERR_BITSTUFF,   USB_TRNSFR_BITSTUFF},
        {EFI_USB_ERR_SYSTEM, 0}
    };
    UINT32 Err = 0;
    UINT32 Status = DevInfo->UsbLastCommandStatusExtended;
    UINT8  Index;

    for (Index = 0; Index<COUNTOF(ErrorMap); ++Index){
        if( Status & ErrorMap[Index].BitSrc ) {
            Err |= ErrorMap[Index].BitDst;
        }
    }

    if( Status == 0 ) {
        return EFI_USB_NOERROR;
    } else {
        return Err;
    }
}

enum {
    UsbCoreGetDescriptor,
    UsbCoreReConfigDevice,
    UsbCoreReConfigDevice2,
    UsbCoreAllocDevInfo,
    UsbCorePrepareForLegacyOS,
    UsbCoreResetAndReconfigDev,
    UsbCoreDevDriverDisconnect,
    UsbCorePeriodicEvent,
    UsbCoreLast,
};

INT32 gCoreprocStackSize[] = {
    6*sizeof(VOID*), // UsbCoreGetDescriptor
    2*sizeof(VOID*), // UsbCoreReConfigDevice
    4*sizeof(VOID*), // UsbCoreReConfigDevice2
    1*sizeof(VOID*), // UsbCoreAllocDevInfo
    1*sizeof(VOID*), // UsbCorePrepareForLegacyOS
    2*sizeof(VOID*), // UsbCoreResetAndReconfigDev
    2*sizeof(VOID*), // UsbCoreDevDriverDisconnect
    0,               // UsbCorePeriodicEvent
};

/**
    Bridge between DXE code and function in USB Core proc table which is inside
    our SMI code.

    @param Func - function number opUSBCORE_XXX which corresponds to index in 
           Core Proc table. Rest of the parameters coresponds the callee interface

    @retval Value  Whatever callee returns

**/
UINTN EFIAPI UsbSmiCore( UINT8 Func, ...  )
{
    UINTN       Index;
    VA_LIST     ArgList;
   
    ASSERT(Func < COUNTOF(gCoreprocStackSize));
    ASSERT(gCoreprocStackSize[Func] < MAX_USB_CORE_STACK_SIZE);

    if (gCoreStackBuffer==NULL) return USB_ERROR; 

    VA_START(ArgList, Func);

    for (Index = 0; Index < gCoreprocStackSize[Func] / sizeof(VOID*); Index++) {
        gCoreStackBuffer[Index] = VA_ARG(ArgList, UINTN);
    }

    VA_END(ArgList);

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CORE_PROC;
    gParameters->SubFunc = Func;
    gParameters->RetValue = USB_ERROR;       //(EIP91840+)
    gParameters->ApiData.CoreProc.ParamBuffer = gCoreStackBuffer;
    gParameters->ApiData.CoreProc.ParamSize = (UINT32)gCoreprocStackSize[Func];
    gParameters->ApiData.CoreProc.RetVal = 0; //(EIP91840+)
    USB_DEBUG(DEBUG_MISC,
        "call CORE SMI proc(%d); params: %x\n", Func, gParameters->ApiData.CoreProc.ParamBuffer);

    InvokeUsbApi(gParameters);

    return gParameters->ApiData.CoreProc.RetVal;
}


/**
    SW SMI to execute GetDescriptor transfer

    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure
    @param Buffer           Buffer for return.
    @param Length           Buffer Length
    @param DescType         Descriptor type
    @param DescIndex        Descriptor Index
    
    @retval Buffer          Descriptior data in Buffer
    @retval NULl            Get descriptor ommand fail

**/

UINT8*
UsbSmiGetDescriptor (
    HC_STRUC*   HostController,
    DEV_INFO*   Device,
    UINT8*      Buffer,
    UINT16      Length,
    UINT8       DescType,
    UINT8       DescIndex
)
{
    EFI_STATUS      Status;
    UINT8           *DataBuffer = Buffer;
    UINTN           ReturnValue;

    if (RShiftU64((UINTN)Buffer, 32)) {
        if (gUsbBusTempBuffer == NULL || Length > (gTempBufferPages << 12)) {
            if (gUsbBusTempBuffer) {
                gBS->FreePages((EFI_PHYSICAL_ADDRESS)gUsbBusTempBuffer, gTempBufferPages);
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
            gTempBufferPages = EFI_SIZE_TO_PAGES(Length);
            gUsbBusTempBuffer = (UINT8*)(UINTN)0xFFFFFFFF;
            Status = gBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData,
                            gTempBufferPages, (EFI_PHYSICAL_ADDRESS*)&gUsbBusTempBuffer);
            if (!EFI_ERROR(Status)) {
                SetMem (gUsbBusTempBuffer, gTempBufferPages << 12, 0);
            } else {
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
        }

        if (gUsbBusTempBuffer) {
                    DataBuffer = gUsbBusTempBuffer;
        }
    }

    ReturnValue = UsbSmiCore(
                    UsbCoreGetDescriptor,
                    HostController, 
                    Device, 
                    DataBuffer, 
                    Length, 
                    DescType, 
                    DescIndex
                    );

    if (ReturnValue == 0) {
        return NULL;
    }
    
    if (DataBuffer != Buffer) {
        CopyMem (Buffer, DataBuffer, Length);
    }

    return Buffer;
}

/**
    Perform the device specific configuration
    
    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure

    @retval Value  Whatever callee returns
**/

UINT8
UsbSmiReConfigDevice(
    HC_STRUC*   HostController,
    DEV_INFO*   Device
)
{
    return (UINT8)UsbSmiCore(UsbCoreReConfigDevice, HostController, Device);
}


/**
    Allocate the empty buffer for USB device

    @retval Pointer  Device pointer.
**/

DEV_INFO*
UsbAllocDevInfo()
{
    return (DEV_INFO*)UsbSmiCore(UsbCoreAllocDevInfo, 1);
}


/**
    Callback on LEGACY_BOOT event

**/

VOID
EFIAPI
UsbPrepareForLegacyOS()
{
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CORE_PROC;
    gParameters->SubFunc = UsbCorePrepareForLegacyOS;
    gParameters->RetValue = USB_ERROR;
    gParameters->ApiData.CoreProc.ParamBuffer = NULL;
    gParameters->ApiData.CoreProc.ParamSize = sizeof(VOID*);
    gParameters->ApiData.CoreProc.RetVal = 0;
    USBGenerateSWSMI(gUsbData->UsbSwSmi);

}

/**
    Reset device and reconfig device.

    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure

    @retval Value  Whatever callee returns
    
**/

UINT8
UsbResetAndReconfigDev(
    HC_STRUC*   HostController,
    DEV_INFO*   Device
)
{
    return (UINT8)UsbSmiCore(UsbCoreResetAndReconfigDev, HostController, Device);
}

/**
    Device driver disconnect

    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure

    @retval Value  Whatever callee returns
**/

UINT8
UsbDevDriverDisconnect(
    HC_STRUC*   HostController,
    DEV_INFO*   Device
)
{
    return (UINT8)UsbSmiCore(UsbCoreDevDriverDisconnect, HostController, Device);
}

INT32 gHcprocStackSize[] = {
    sizeof(VOID*) * 1, // AmiUsbHc_Start
    sizeof(VOID*) * 1, // AmiUsbHc_Stop
    sizeof(VOID*) * 1, // AmiUsbHc_EnumeratePorts
    sizeof(VOID*) * 1, // AmiUsbHc_DisableInterrupts
    sizeof(VOID*) * 1, // AmiUsbHc_EnableInterrupts
    sizeof(VOID*) * 1, // AmiUsbHc_ProcessInterrupt
    sizeof(VOID*) * 3, // AmiUsbHc_GetRootHubStatus
    sizeof(VOID*) * 2, // AmiUsbHc_DisableRootHub
    sizeof(VOID*) * 2, // AmiUsbHc_EnableRootHub
    sizeof(VOID*) * 7, // AmiUsbHc_ControlTransfer
    sizeof(VOID*) * 5, // AmiUsbHc_BulkTransfer
    sizeof(VOID*) * 6, // AmiUsbHc_IsocTransfer
    sizeof(VOID*) * 6, // AmiUsbHc_InterruptTransfer
    sizeof(VOID*) * 2, // AmiUsbHc_DeactivatePolling
    sizeof(VOID*) * 2, // AmiUsbHc_ActivatePolling
    sizeof(VOID*) * 3, // AmiUsbHc_EnableEndpoints
    sizeof(VOID*) * 1, // AmiUsbHc_DisableKeyRepeat
    sizeof(VOID*) * 1, // AmiUsbHc_EnableKeyRepeat
    sizeof(VOID*) * 4, // AmiUsbHc_InitDeviceData
    sizeof(VOID*) * 2, // AmiUsbHc_DeinitDeviceData
    sizeof(VOID*) * 2, // AmiUsbHc_ResetRootHub
    sizeof(VOID*) * 3, // AmiUsbHc_ClearEndpointState
    sizeof(VOID*) * 1, // AmiUsbHc_GlobalSuspend
    sizeof(VOID*) * 2, // AmiUsbHc_SmiControl
};

/**
    Bridge between DXE code and SMI function in USB HC driver.

    @param Func     function number AmiUsbHc_XXX which corresponds to index in HCD_HEADER
    @param HcType   type of USB HC controller; selects an HC driver to call
                    Rest of the parameters coresponds the callee interface

    @retval Value   Whatever callee returns

**/
UINTN 
EFIAPI
UsbSmiHc(
    UINT8 Func,
    UINT8 HcType,
    ...
)
{
    UINTN       Index = 0;
    VA_LIST     ArgList;

    ASSERT(Func < COUNTOF(gHcprocStackSize));
    ASSERT(gHcprocStackSize[Func] > 0);
    ASSERT(gHcprocStackSize[Func] < MAX_USB_CORE_STACK_SIZE);

    if (gCoreStackBuffer==NULL) return USB_ERROR; 

    VA_START(ArgList, HcType);

    for (Index = 0; Index < gHcprocStackSize[Func] / sizeof(VOID*); Index++) {
        gCoreStackBuffer[Index] = VA_ARG(ArgList, UINTN);
    }
    VA_END(ArgList);

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_HC_PROC;
    gParameters->SubFunc = Func;
    gParameters->RetValue = USB_ERROR;       //(EIP91840+)
    gParameters->ApiData.HcProc.ParamBuffer = (VOID*)gCoreStackBuffer;
    gParameters->ApiData.HcProc.ParamSize = (UINT32)gHcprocStackSize[Func];
    gParameters->ApiData.HcProc.HcType = HcType;
    gParameters->ApiData.HcProc.RetVal = 0;   //(EIP91840+)
    USB_DEBUG(DEBUG_MISC,
        "call HC SMI driver(type:%d;func:%d); params at %x\n",
            HcType, Func, gParameters->ApiData.HcProc.ParamBuffer);

    InvokeUsbApi(gParameters);
    return gParameters->ApiData.HcProc.RetVal;
}

/**
    Usb Periodic Event
**/

VOID
UsbSmiPeriodicEvent(VOID)
{

}

/**
    Wrappers for calling USB HC driver functions in USBSMI service

    @param HcStruc   Ptr to the host controller structure
    @param PortNum   Usb port number
    @param ClearChangeBits   Clear change bits.
    
    @retval Value    Usb Port status.
**/

UINT32
UsbSmiGetRootHubStatus(
    HC_STRUC    *HcStruc,
    UINT8       PortNum, 
    BOOLEAN     ClearChangeBits
)
{
    return (UINT32)UsbSmiHc(
            AmiUsbHc_GetRootHubStatus, HcStruc->HcType, HcStruc, PortNum, ClearChangeBits);
}

/**
    Wrappers for calling USB HC driver functions in USBSMI service

    @param HcStruc   Ptr to the host controller structure
    @param PortNum   Usb port number
    
    @retval USB_SUCCESS   Success to enable root hub.
**/
UINT8 UsbSmiEnableRootHub(HC_STRUC* HcStruc, UINT8 PortNum)
{
    return (UINT8)UsbSmiHc(
            AmiUsbHc_EnableRootHub, HcStruc->HcType, HcStruc, PortNum);
}

/**
    Wrappers for calling USB HC driver functions in USBSMI service

    @param HcStruc   Ptr to the host controller structure
    @param PortNum   Usb port number
    
    @retval USB_SUCCESS   Success to disable root hub.
**/
UINT8 UsbSmiDisableRootHub(HC_STRUC* HcStruc, UINT8 PortNum)
{
    return (UINT8)UsbSmiHc(
            AmiUsbHc_DisableRootHub, HcStruc->HcType, HcStruc, PortNum);
}

/**
    Wrappers for calling USB HC driver functions in USBSMI service

    @param HcStruc   Ptr to the host controller structure
    @param PortNum   Usb port number
    @param Desc      Usb descriptor
    
    @retval USB_SUCCESS   Success to enable enable endpoint
**/
UINT8 UsbSmiEnableEndpoints(HC_STRUC* HcStruc, DEV_INFO* DevInfo, UINT8 *Desc)
{
    return (UINT8) UsbSmiHc(
            AmiUsbHc_EnableEndpoints, HcStruc->HcType, HcStruc, DevInfo, Desc);
}

/**
    Wrappers for calling USB HC driver USB transfer functions

    @param HcStruc       Ptr to the host controller structure
    @param Device        Ptr to the device info structure
    @param Request       Usb Request
    @param Index         Index
    @param Value         Value
    @param Buffer        Buffer
    @param Length        Buffer length

    @retval Value        Number of bytes actually transferred

**/

UINT16
UsbSmiControlTransfer (
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length)
{
    EFI_STATUS      Status;
    UINT8           *DataBuffer = Buffer;
    UINTN           ReturnValue;
    
    if (RShiftU64((UINTN)Buffer, 32)) {
        
        if (gUsbBusTempBuffer == NULL || Length > (gTempBufferPages << 12)) {
            if (gUsbBusTempBuffer) {
                gBS->FreePages((EFI_PHYSICAL_ADDRESS)gUsbBusTempBuffer, gTempBufferPages);
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
            gTempBufferPages = EFI_SIZE_TO_PAGES(Length);
            gUsbBusTempBuffer = (UINT8*)(UINTN)0xFFFFFFFF;
            Status = gBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData,
                            gTempBufferPages, (EFI_PHYSICAL_ADDRESS*)&gUsbBusTempBuffer);
            if (!EFI_ERROR(Status)) {
                SetMem (gUsbBusTempBuffer, gTempBufferPages << 12, 0);
            } else {
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
        }
        
        if (gUsbBusTempBuffer) {
            DataBuffer = gUsbBusTempBuffer;
        }
    }

    if (DataBuffer != Buffer) {
        if (!(Request & USB_REQ_TYPE_INPUT)) {
            CopyMem(DataBuffer, Buffer, Length);
        }
    }
    
    ReturnValue = UsbSmiHc(AmiUsbHc_ControlTransfer,
                    HcStruc->HcType, HcStruc, DevInfo,
                    Request, Index, Value, DataBuffer, Length);
    
    if (DataBuffer != Buffer) {
        if (Request & USB_REQ_TYPE_INPUT) {
            CopyMem(Buffer, DataBuffer, Length);
        }
    }

    return (UINT16)ReturnValue;
}

/**
    Wrappers for calling USB HC driver USB Bulk transfer functions

    @param HcStruc       Ptr to the host controller structure
    @param Device        Ptr to the device info structure
    @param XferDir       Transfer direction
    @param Buffer        Buffer containing data to be sent to the device 
                         or buffer to be used to receive data value
    @param Length        Length request parameter, number of bytes of data 
                         to be transferred in or out of the HC
    @retval Value        Number of bytes actually transferred

**/
UINT32
UsbSmiBulkTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length
)
{
    EFI_STATUS      Status;
    UINT8           *DataBuffer = Buffer;
    UINTN           ReturnValue;
    
    if (RShiftU64((UINTN)Buffer, 32)) {
        if (gUsbBusTempBuffer == NULL || Length > (gTempBufferPages << 12)) {
            if (gUsbBusTempBuffer) {
                gBS->FreePages((EFI_PHYSICAL_ADDRESS)gUsbBusTempBuffer, gTempBufferPages);
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
            gTempBufferPages = EFI_SIZE_TO_PAGES(Length);
            gUsbBusTempBuffer = (UINT8*)(UINTN)0xFFFFFFFF;
            Status = gBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData,
                             gTempBufferPages, (EFI_PHYSICAL_ADDRESS*)&gUsbBusTempBuffer);
            if (!EFI_ERROR(Status)) {
                SetMem (gUsbBusTempBuffer, gTempBufferPages << 12, 0);
            } else {
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
        }
        if (gUsbBusTempBuffer) {
                DataBuffer = gUsbBusTempBuffer;
        }
    }
    
    if (DataBuffer != Buffer) {
        if (!(XferDir & BIT7)) {
            CopyMem(DataBuffer, Buffer, Length);
        }
    }
        
    ReturnValue = UsbSmiHc(AmiUsbHc_BulkTransfer,
    HcStruc->HcType, HcStruc, DevInfo, XferDir, DataBuffer, Length);
    
    if (DataBuffer != Buffer) {
       if (XferDir & BIT7) {
           CopyMem(Buffer, DataBuffer, Length);
       }
    }

    return (UINT32)ReturnValue;
}

/**
    Wrappers for calling USB HC driver USB Isoc transfer functions

    @param HcStruc       Ptr to the host controller structure
    @param Device        Ptr to the device info structure
    @param XferDir       Transfer direction
    @param Buffer        Buffer containing data to be sent to the device 
                         or buffer to be used to receive data value
    @param Length        Length request parameter, number of bytes of data 
                         to be transferred in or out of the HC
    @param Async         Async Indicator
    @retval Value        Number of bytes actually transferred

**/
UINT32
UsbSmiIsocTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length,
    UINT8       *Async
)
{
    return (UINT32)UsbSmiHc(AmiUsbHc_IsocTransfer,
      HcStruc->HcType, HcStruc, DevInfo, XferDir, Buffer, Length, Async );
}

/**
    Wrappers for calling USB HC driver USB Interrupt transfer functions

    @param HcStruc       Ptr to the host controller structure
    @param Device        Ptr to the device info structure
    @param EndpointAddress EndPoint address.
    @param MaxPktSize    Max packet size.
    @param Buffer        Buffer containing data to be sent to the device 
                         or buffer to be used to receive data value
    @param Length        Length request parameter, number of bytes of data 
                         to be transferred in or out of the HC
    
    @retval Value        Number of bytes actually transferred

**/
UINT16
UsbSmiInterruptTransfer(
    HC_STRUC*   HcStruc,
    DEV_INFO*   DevInfo,
    UINT8       EndpointAddress,
    UINT16      MaxPktSize,
    UINT8       *Buffer,
    UINT16      Length
)
{
    EFI_STATUS      Status;
    UINT8           *DataBuffer = Buffer;
    UINTN           ReturnValue;
    
    if (RShiftU64((UINTN)Buffer, 32)) {
        if (gUsbBusTempBuffer == NULL || Length > (gTempBufferPages << 12)) {
            if (gUsbBusTempBuffer) {
                gBS->FreePages((EFI_PHYSICAL_ADDRESS)gUsbBusTempBuffer, gTempBufferPages);
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
            gTempBufferPages = EFI_SIZE_TO_PAGES(Length);
            gUsbBusTempBuffer = (UINT8*)(UINTN)0xFFFFFFFF;
            Status = gBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData,
                            gTempBufferPages, (EFI_PHYSICAL_ADDRESS*)&gUsbBusTempBuffer);
            if (!EFI_ERROR(Status)) {
                SetMem (gUsbBusTempBuffer, gTempBufferPages << 12, 0);
            } else {
                gUsbBusTempBuffer = NULL;
                gTempBufferPages = 0;
            }
        }
        if (gUsbBusTempBuffer) {
            DataBuffer = gUsbBusTempBuffer;
        }
    }
    
    if (DataBuffer != Buffer) {
        if (!(EndpointAddress & BIT7)) {
            CopyMem(DataBuffer, Buffer, Length);
        }
    }

    ReturnValue = UsbSmiHc(AmiUsbHc_InterruptTransfer,
                    HcStruc->HcType, HcStruc, DevInfo, 
                    EndpointAddress, MaxPktSize, DataBuffer, Length);
    
    if (DataBuffer != Buffer) {
        if (EndpointAddress & BIT7) {
             CopyMem(Buffer, DataBuffer, Length);
        }
    }
    
    return (UINT16)ReturnValue;
}

/**
    Wrappers for calling USB HC driver USB Deactive polling functions

    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure

    @retval Value  Whatever callee returns
**/
UINT8 UsbSmiDeactivatePolling (HC_STRUC* HostController, DEV_INFO* DevInfo )
{
    return (UINT8)UsbSmiHc( AmiUsbHc_DeactivatePolling,
            HostController->HcType, HostController, DevInfo );
}

/**
    Wrappers for calling USB HC driver USB Active polling functions

    @param HostController   Ptr to the host controller structure
    @param Device           Ptr to the device info structure

    @retval Value  Whatever callee returns
**/
UINT8   UsbSmiActivatePolling (HC_STRUC* HostController, DEV_INFO* DevInfo )
{
    return (UINT8)UsbSmiHc( AmiUsbHc_ActivatePolling,
            HostController->HcType, HostController, DevInfo );
}


/**
    Converts one bit-strng to another using a convertion table

    @param Val     intial 32 bit wide bit-string
    @param BitT    array of bitmaptable_t recodrds
    @param Cnt     number of records in array BitT
    
    @retval Value  32 bit wide bit-string - result of conversion applied to Val

**/

struct BITMAPTABLE_T {
           UINT32 Src; 
           UINT32 Dst;
};

UINT32
ConvertBitmaps(
    UINT32 Val,
    struct BITMAPTABLE_T* BitT,
    UINT32 Cnt
)
{
    UINT32 Res = 0;
    UINT32 Index;
    for( Index=0; (BitT->Src !=0)&& ( Index < Cnt); ++Index, BitT++ ){
        if( BitT->Src & Val )
            Res |= BitT->Dst;
    }
    return Res;
}


/**
    Enumerates DEV_INFO structures in DevInfoTable array of USB data to find
    one that matches the specified USB address and connects to a specified USB
    host controller.

    
    @param DEV_INFO    Start Pointer to the device info structure from
                       where the search begins (if 0 start from first entry)
    @param DevAddr     Device address
    @param HcStruc     Pointer to the HCStruc structure

    @retval Pointer    Pointer to DEV_INFO structure, NULL if device is not found

**/

DEV_INFO*
SearchDevinfoByAdr(
    DEV_INFO*   Start,
    UINT8       DevAddr,
    HC_STRUC*   HcStruc
)
{
    DEV_INFO*   DevInfo;
    DEV_INFO*   Dev = gUsbDataList->DevInfoTable + gUsbData->MaxDevCount;

    for ( DevInfo = Start!=NULL?Start:&gUsbDataList->DevInfoTable[1];
            DevInfo != Dev; ++DevInfo ){
        if ((DevInfo->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_DUMMY)) ==
                        DEV_INFO_VALID_STRUC) {
            if(( gHcTable[DevInfo->HcNumber - 1] == HcStruc) &&
                ( DevInfo->DeviceAddress == DevAddr )){
                    return DevInfo;
            }
        }
    }
    return NULL;
}


/**
    Returns a DEV_INFO that corresponds to a device that is connected to a
    specified host controller and has a specified address

    @param Addr    Device address
    @param Hc      Pointer to the HCStruc structure

    @retval Pointer Pointer to DEV_INFO structure, NULL if device is not found

**/

DEV_INFO*
DevAddr2Info(
    UINT8 Addr,
    HC_STRUC* Hc
)
{
    DEV_INFO* Dev = SearchDevinfoByAdr(NULL, Addr, Hc);
    USB_DEBUG(DEBUG_MISC,
        "\tDevAddr2Info %x -> %x(hc:%x;hub:%x;port:%x;if:%x)\n",
            Addr, Dev, Dev->HcNumber, Dev->HubDeviceNumber,
            Dev->HubPortNumber, Dev->InterfaceNum );
    return Dev;
}


/**
    Searches a DEV_INFO that was used as a temporary structure for the USB transfer.
 
    @param HubPortNumber   Hub port number
    @param HubDeviceNumber Hub device number
    @param EndPoint        Interrupt Endpoint number that was assigned to temporary structure
    @param HCStruc         Pointer to the HCStruc structure

    @retval Pointer        Pointer to DeviceInfo Structure NULL if device is not found

**/

DEV_INFO*
FindOldTransfer(
    UINT8 HubPortNumber,
    UINT8 HubDeviceNumber,
    UINT8 EndPoint,
    HC_STRUC* HcStruc
)
{
    DEV_INFO *Dev;
    DEV_INFO *LastDev = gUsbDataList->DevInfoTable + 
                          gUsbData->MaxDevCount;

    for ( Dev = &gUsbDataList->DevInfoTable[1]; Dev != LastDev; ++Dev ){
        if( ((Dev->Flag & (DEV_INFO_VALID_STRUC|DEV_INFO_DEV_PRESENT|DEV_INFO_DEV_DUMMY) )==
            (DEV_INFO_VALID_STRUC|DEV_INFO_DEV_PRESENT|DEV_INFO_DEV_DUMMY)) &&
            (Dev->HcNumber == HcStruc->HcNumber ) &&
            (Dev->HubPortNumber == HubPortNumber ) &&
            (Dev->HubDeviceNumber == HubDeviceNumber ) &&
            (Dev->IntInEndpoint == EndPoint )) 
        {
            return Dev;
        }
    }
    return NULL;
}


/**
    Allocates temporary DEV_INFO structure in USB data area for use in USB transfer.

    @retval Pointer Pointer to a DEV_INFO structure
**/

DEV_INFO*
AllocDevInfo()
{
    DEV_INFO* Dev = UsbAllocDevInfo();
    ASSERT(Dev);
    if(Dev){
        Dev->DeviceType = BIOS_DEV_TYPE_USBBUS_SHADOW;
        Dev->Flag |= DEV_INFO_DEV_DUMMY;
    }
    return Dev;
}


/**
    Marks DEV_INFO structure that it is free for use in consequent operations.
**/

VOID
FreeDevInfo(
    DEV_INFO* Dev
)
{
    ASSERT(Dev);
    if (Dev) {
      Dev->Flag &= ~(DEV_INFO_VALID_STRUC |  DEV_INFO_DEV_PRESENT | DEV_INFO_DEV_DUMMY | DEV_INFO_DEV_DUMMY_CANCEL);
    }
}

/**
    Translate interval
    @param Speed     Speed
    @param Interval  Interval

    @retval Value    Translate interval
**/
UINT8
TranslateInterval(
    UINT8   Speed,
    UINTN   Interval
)
{
    UINT8  BitCount = 0;

    if (Speed == EFI_USB_SPEED_LOW ||
        Speed == EFI_USB_SPEED_FULL) {
        return (UINT8)Interval;
    }

    for (BitCount = 0; Interval != 0; BitCount++) {
        Interval >>= 1;
    }
    return (BitCount + 2);
}

/////////////////////////////////////////////////////////////////////////////
//                  USB Host Controller API functions
/////////////////////////////////////////////////////////////////////////////

/**
    Provides software reset for the USB host controller.

    @param This        A pointer to the EFI_USB_HC_PROTOCOL instance. Type
                       EFI_USB_HC_PROTOCOL is defined in Section 14.1.
    @param Attributes  A bit mask of the reset operation to perform.

    @retval EFI_SUCCESS             The reset operation succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
    @retval EFI_UNSUPPORTED         The type of reset specified by Attributes is
                                    not currently supported by the host controller
                                    hardware.
    @retval EFI_DEVICE_ERROR        An error was encountered while attempting to
                                    perform the reset operation.

**/

EFI_STATUS
EFIAPI
AmiUsbHcReset(
    IN EFI_USB_HC_PROTOCOL  *This,
    IN UINT16               Attributes
)
{
    REPORT_STATUS_CODE(EFI_PROGRESS_CODE,DXE_USB_RESET);

    if (!(Attributes & (EFI_USB_HC_RESET_GLOBAL | EFI_USB_HC_RESET_HOST_CONTROLLER))) {
        return EFI_INVALID_PARAMETER;
    }

    USB_DEBUG(DEBUG_DEV_INIT, "AmiUsbHcReset:");

    return EFI_UNSUPPORTED;
}


/**
    Protocol USB HC function that returns Host Controller state.

    @param This        A pointer to the EFI_USB_HC_PROTOCOL instance. Type
                       EFI_USB_HC_PROTOCOL is defined in Section 14.1.
    @param State       A pointer to state

    @retval EFI_SUCCESS             The get state operation succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcGetState(
    IN  EFI_USB_HC_PROTOCOL  *This,
    OUT EFI_USB_HC_STATE     *State
)
{
    return AmiUsb2HcGetState(&GetThis1(This)->HcProtocol2, State);
}


/**
    Protocol USB HC function that sets Host Controller state.
    @param This        A pointer to the EFI_USB_HC_PROTOCOL instance. Type
                       EFI_USB_HC_PROTOCOL is defined in Section 14.1.
    @param State       A pointer to state

    @retval EFI_SUCCESS             The set state operation succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcSetState(
    IN EFI_USB_HC_PROTOCOL *This,
    IN EFI_USB_HC_STATE State
)
{
    USB_DEBUG(DEBUG_DEV_INIT, "USB HC:\t\tsetState, %d\n", State);
    return AmiUsb2HcSetState(&GetThis1(This)->HcProtocol2, State);
}


/**
    Protocol USB HC function that performs USB transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  IsSlowDevice            Slow device check
    @param  MaximumPacketLength     Max packet of device
    @param  Request                 Point to transfer requestion
    @param  TransferDirection       Transfer directioin
    @param  Data                    Point to control transfer data
    @param  DataLength              Point to control transfer data length
    @param  Timeout                 Time out value
    @param  TransferResult          Point to transfer result
    
    @retval EFI_SUCCESS             The control transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcControlTransfer(
    IN EFI_USB_HC_PROTOCOL          *HcProtocol,
    IN     UINT8                    DeviceAddress,
    IN     BOOLEAN                  IsSlowDevice,
    IN     UINT8                    MaximumPacketLength,
    IN     EFI_USB_DEVICE_REQUEST   *Request,
    IN     EFI_USB_DATA_DIRECTION   TransferDirection,
    IN OUT VOID                     *Data,
    IN OUT UINTN                    *DataLength,
    IN     UINTN                    Timeout,
    OUT    UINT32                   *TransferResult
)
{
    return AmiUsb2HcControlTransfer(
             &GetThis1(HcProtocol)->HcProtocol2,
             DeviceAddress,
             IsSlowDevice?EFI_USB_SPEED_LOW:EFI_USB_SPEED_FULL,
             MaximumPacketLength, 
             Request, 
             TransferDirection, 
             Data,
             DataLength, 
             Timeout, 
             NULL, 
             TransferResult
             );
}


/**
    Protocol USB HC function that performs USB bulk transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  MaximumPacketLength     Max packet of device
    @param  Data                    Point to Bulk transfer data
    @param  DataLength              Point to bulk transfer data length
    @param  DataToggle              Point to data toggole
    @param  Timeout                 Time out value
    @param  Translator              Point to usb2 hc transaction translator
    @param  TransferResult          Point to transfer result
    
    @retval EFI_SUCCESS             The bulk transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS 
EFIAPI 
AmiUsbHcBulkTransfer(
    IN EFI_USB_HC_PROTOCOL  *HcProtocol,
    IN  UINT8               DeviceAddress,
    IN  UINT8               EndpointAddress,
    IN  UINT8               MaximumPacketLength,
    IN OUT VOID             *Data,
    IN OUT UINTN            *DataLength,
    IN OUT UINT8            *DataToggle,
    IN  UINTN               Timeout,
    OUT UINT32              *TransferResult
)
{
    //
    // Check for valid maximum packet length is 8, 16, 32 or 64
    //
    if ( MaximumPacketLength != 8 &&
         MaximumPacketLength != 16 &&
         MaximumPacketLength != 32 &&
         MaximumPacketLength != 64 ) return EFI_INVALID_PARAMETER;

    return AmiUsb2HcBulkTransfer(
             &GetThis1(HcProtocol)->HcProtocol2,
             DeviceAddress, 
             EndpointAddress, 
             EFI_USB_SPEED_FULL,
             MaximumPacketLength, 
             1, 
             &Data, 
             DataLength,
             DataToggle, 
             Timeout, 
             NULL, 
             TransferResult
             );
}


/**
    Protocol USB HC function that performs USB async interrupt transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Endpoint address
    @param  IsSlowDevice            Slow device check
    @param  MaxPacket               Max packet of device
    @param  IsNewTransfer           New transfer check
    @param  DataToggle              Point to data toogle
    @param  PollingInterval         Polling interval
    @param  DataLength              Data length
    @param  CallbackFunction        callback function
    @param  Context                 Point to Context
    
    @retval EFI_SUCCESS             The Async interrupt transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcAsyncInterruptTransfer(
  IN EFI_USB_HC_PROTOCOL                  *HcProtocol,
  IN     UINT8                            DeviceAddress,
  IN     UINT8                            EndpointAddress,
  IN     BOOLEAN                          IsSlowDevice,
  IN     UINT8                            MaxPacket,
  IN     BOOLEAN                          IsNewTransfer,
  IN OUT UINT8                            *DataToggle,
  IN     UINTN                            PollingInterval,
  IN     UINTN                            DataLength,
  IN     EFI_ASYNC_USB_TRANSFER_CALLBACK  CallbackFunction,
  IN     VOID                             *Context)
{
    return AmiUsb2HcAsyncInterruptTransfer(
             &GetThis1(HcProtocol)->HcProtocol2,
             DeviceAddress, 
             EndpointAddress,
             IsSlowDevice?EFI_USB_SPEED_LOW:EFI_USB_SPEED_FULL,
             MaxPacket, 
             IsNewTransfer, 
             DataToggle,
             PollingInterval, 
             DataLength, 
             NULL, 
             CallbackFunction, 
             Context
             );
}


/**
    Protocol USB HC function that performs USB sync interrupt transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Endpoint address
    @param  IsSlowDevice            Slow device check
    @param  MaximumPacketLength     Max packet of device
    @param  Data                    Point to interrupt transfer data
    @param  DataLength              Point to interrupt transfer data length
    @param  DataToggle              Point to data toogle
    @param  Timeout                 Time out value
    @param  TransferResult          Point to transfer result
    
    @retval EFI_SUCCESS             The interrupt transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcSyncInterruptTransfer(
  IN EFI_USB_HC_PROTOCOL    *HcProtocol,
  IN     UINT8              DeviceAddress,
  IN     UINT8              EndpointAddress,
  IN     BOOLEAN            IsSlowDevice,
  IN     UINT8              MaximumPacketLength,
  IN OUT VOID               *Data,
  IN OUT UINTN              *DataLength,
  IN OUT UINT8              *DataToggle,
  IN     UINTN              Timeout,
  OUT    UINT32             *TransferResult
)
{
    return AmiUsb2HcSyncInterruptTransfer(
             &GetThis1(HcProtocol)->HcProtocol2,
             DeviceAddress, 
             EndpointAddress,
             IsSlowDevice?EFI_USB_SPEED_LOW:EFI_USB_SPEED_FULL,
             MaximumPacketLength,
             Data, 
             DataLength, 
             DataToggle, 
             Timeout, 
             NULL, 
             TransferResult 
             );
}


/**
    Protocol USB HC function that performs USB sync isochronous transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Endpoint address
    @param  MaximumPacketLength     Max packet of device
    @param  Data                    Point to interrupt transfer data
    @param  DataLength              Point to interrupt transfer data length
    @param  TransferResult          Point to transfer result
    
    @retval EFI_UNSUPPORTED         The featue not support.
**/

EFI_STATUS
EFIAPI
AmiUsbHcIsochronousTransfer(
  IN EFI_USB_HC_PROTOCOL    *This,
  IN     UINT8              DeviceAddress,
  IN     UINT8              EndpointAddress,
  IN     UINT8              MaximumPacketLength,
  IN OUT VOID               *Data,
  IN OUT UINTN              DataLength,
  OUT    UINT32             *TransferResult
)
{
    return EFI_UNSUPPORTED;
}


/**
    Protocol USB HC function that performs USB async isochronous transfer.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Endpoint address
    @param  MaximumPacketLength     Max packet of device
    @param  Data                    Point to Async interrupt transfer data
    @param  DataLength              Point to Ansync interrupt transfer data length
    @param  IsochronousCallback     Point to call back function.
    @param  Context                 Point to Context
    
    @retval EFI_UNSUPPORTED         The featue not support.
**/

EFI_STATUS
EFIAPI
AmiUsbHcAsyncIsochronousTransfer(
  IN EFI_USB_HC_PROTOCOL              *This,
  IN     UINT8                        DeviceAddress,
  IN     UINT8                        EndpointAddress,
  IN     UINT8                        MaximumPacketLength,
  IN OUT VOID                         *Data,
  IN     UINTN                        DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallback,
  IN VOID                             *Context
  )
{
    return EFI_UNSUPPORTED;
}


/**
    Protocol USB HC function that returns the number of ports of a root hub
    on a given controller.

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Pointer to Port number
    
    @retval EFI_SUCCESS             The get root hub port number succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
EFIAPI
AmiUsbHcGetRootHubPortNumber (
    IN  EFI_USB_HC_PROTOCOL *HcProtocol,
    OUT UINT8               *PortNumber
)
{
    HC_DXE_RECORD *This = GetThis1(HcProtocol);

    USB_DEBUG(DEBUG_DEV_INIT,
        "USB HC:\t\tget_roothub_port_number\n");

    if (PortNumber == NULL) return EFI_INVALID_PARAMETER;

    *PortNumber = This->HcStruc->NumPorts;

    return EFI_SUCCESS;
}


/**
    Protocol USB HC function that returns the root port status
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortStatus              Pointer to Port status
    
    @retval EFI_SUCCESS             The get root hub port status succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
    
**/

EFI_STATUS
EFIAPI
AmiUsbHcGetRootHubPortStatus(
    EFI_USB_HC_PROTOCOL *HcProtocol,
    UINT8               PortNumber,
    EFI_USB_PORT_STATUS *PortStatus
)
{
    HC_DXE_RECORD *This = GetThis1( HcProtocol );

    static struct BITMAPTABLE_T StatusTable[] = {
        {USB_PORT_STAT_DEV_CONNECTED,USB_PORT_STAT_CONNECTION},
        {USB_PORT_STAT_DEV_LOWSPEED,USB_PORT_STAT_LOW_SPEED},
        {USB_PORT_STAT_DEV_SUPERSPEED, USB_PORT_STAT_SUPER_SPEED},
        {USB_PORT_STAT_DEV_SUPERSPEED_PLUS, USB_PORT_STAT_SUPER_SPEED},
        {USB_PORT_STAT_DEV_ENABLED, USB_PORT_STAT_ENABLE},
        {USB_PORT_STAT_DEV_SUSPEND, USB_PORT_STAT_SUSPEND},
        {USB_PORT_STAT_DEV_OVERCURRENT, USB_PORT_STAT_OVERCURRENT},
        {USB_PORT_STAT_DEV_RESET, USB_PORT_STAT_RESET},
        {USB_PORT_STAT_DEV_POWER, USB_PORT_STAT_POWER},
        {USB_PORT_STAT_DEV_OWNER, USB_PORT_STAT_OWNER}
    };
    static struct BITMAPTABLE_T ChangeStatusMapTable[] = {
        {USB_PORT_STAT_DEV_CONNECT_CHANGED,USB_PORT_STAT_C_CONNECTION},
        {USB_PORT_STAT_DEV_ENABLE_CHANGED, USB_PORT_STAT_C_ENABLE},
        {USB_PORT_STAT_DEV_OVERCURRENT_CHANGED, USB_PORT_STAT_C_OVERCURRENT},
        {USB_PORT_STAT_DEV_RESET_CHANGED, USB_PORT_STAT_C_RESET}
    };

    UINT32  PortSts;

    USB_DEBUG(DEBUG_DEV_INIT, "USB HC:\t\tget_roothub_port_status\n" );

    if (PortStatus == NULL || PortNumber >= This->HcStruc->NumPorts)
        return EFI_INVALID_PARAMETER;

    PortSts = UsbSmiGetRootHubStatus(This->HcStruc,(UINT8)PortNumber + 1, FALSE);

    PortStatus->PortStatus = (UINT16)ConvertBitmaps(
                  PortSts, StatusTable, COUNTOF(StatusTable));
    PortStatus->PortChangeStatus = (UINT16)ConvertBitmaps(
                  PortSts, ChangeStatusMapTable, COUNTOF(ChangeStatusMapTable)) ;

    if (((PortSts & USB_PORT_STAT_DEV_CONNECTED) != 0) &&
        ((PortSts & USB_PORT_STAT_DEV_SPEED_MASK) == 0)) {
        PortStatus->PortStatus |= USB_PORT_STAT_HIGH_SPEED;
    }

    USB_DEBUG(DEBUG_DEV_INIT, "\t\tStatus=%x, PortStatus=%x, PortChangeStatus=%x\n",
        PortSts, PortStatus->PortStatus, PortStatus->PortChangeStatus );

    return EFI_SUCCESS;
}


/**
    Protocol USB HC function set root hub port feature
    
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortFeature             Port feature.
    
    @retval EFI_SUCCESS             The set root hub port feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcSetRootHubPortFeature(
    IN EFI_USB_HC_PROTOCOL  *HcProtocol,
    IN UINT8                PortNumber,
    IN EFI_USB_PORT_FEATURE PortFeature
)
{
    HC_DXE_RECORD *This = GetThis1(HcProtocol);

    USB_DEBUG(DEBUG_DEV_INIT, "USB HC:\t\tset_roothub_port_feature\n" );

    if ( PortNumber >= This->HcStruc->NumPorts)
        return EFI_INVALID_PARAMETER;

    switch( PortFeature ){
        case EfiUsbPortEnable:
            UsbSmiEnableRootHub(This->HcStruc, PortNumber + 1);
            break;
    
        default:
            return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


/**
    Protocol USB HC function clear root hub port feature

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortFeature             Port feature.
    
    @retval EFI_SUCCESS             The clear root hub port feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsbHcClearRootHubPortFeature(
    IN EFI_USB_HC_PROTOCOL    *HcProtocol,
    IN UINT8                  PortNumber,
    IN EFI_USB_PORT_FEATURE   PortFeature
)
{
    HC_DXE_RECORD *This = GetThis1(HcProtocol);

    USB_DEBUG(DEBUG_DEV_INIT, "USB HC:\t\tclear_roothub_port_feature\n");

    if (PortNumber >= This->HcStruc->NumPorts) return EFI_INVALID_PARAMETER;

    switch (PortFeature ) {
        case EfiUsbPortEnable:
            UsbSmiDisableRootHub(This->HcStruc, PortNumber + 1);
            break;
    
        default:
            return EFI_INVALID_PARAMETER;
    }
    return EFI_SUCCESS;
}


/////////////////////////////////////////////////////////////////////////////
//                  USB2 Host Controller API functions
/////////////////////////////////////////////////////////////////////////////

/**
    This is USB2HC API to get the host controller capability.

    @param  This                    Pointer to EFI_USB2_HC_PROTOCOL
    @param  MaxSpeed                Pointer to Max Speed.
    @param  PortNumber              Pointer to port number.
    @param  Is64BitCapable          Pointer to 64-bit capable
    
    @retval EFI_SUCCESS             The get capability feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
EFIAPI
AmiUsb2HcGetCapability(
  IN  EFI_USB2_HC_PROTOCOL  *This,
  OUT UINT8                 *MaxSpeed,
  OUT UINT8                 *PortNumber,
  OUT UINT8                 *Is64BitCapable
)
{
    HC_DXE_RECORD *Rec = GetThis(This);
    USB3_HOST_CONTROLLER    *Usb3Hc;

    if (MaxSpeed == NULL || PortNumber == NULL || Is64BitCapable == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    switch (Rec->HcStruc->HcType) {
        case USB_HC_OHCI:
        case USB_HC_UHCI:
            *Is64BitCapable = FALSE;
            *MaxSpeed = EFI_USB_SPEED_FULL;
            break;
        case USB_HC_EHCI:
            *Is64BitCapable = FALSE;
            *MaxSpeed = EFI_USB_SPEED_HIGH;
            break;
        case USB_HC_XHCI:
            Usb3Hc = (USB3_HOST_CONTROLLER*)Rec->HcStruc->Usb3HcData;
            if (Usb3Hc->CapRegs.HccParams1.Ac64) {
                *Is64BitCapable = TRUE;
            } else {
                *Is64BitCapable = FALSE;
            }
            *MaxSpeed = EFI_USB_SPEED_SUPER;
            break;
    }

    *PortNumber = Rec->HcStruc->NumPorts;

    return EFI_SUCCESS;
}


/**
    This is USB2HC API to perform host controller reset.

    @param  This                    Pointer to EFI_USB2_HC_PROTOCOL
    @param  Attributes              Reset Attributes

    
    @retval EFI_UNSUPPORTED         This feature unsupported.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsb2HcReset(
  IN EFI_USB2_HC_PROTOCOL   *This,
  IN UINT16                 Attributes
)
{
    REPORT_STATUS_CODE(EFI_PROGRESS_CODE,DXE_USB_RESET);

    if (Attributes == 0 || (Attributes & ~(EFI_USB_HC_RESET_GLOBAL
        | EFI_USB_HC_RESET_HOST_CONTROLLER | EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG
        | EFI_USB_HC_RESET_HOST_WITH_DEBUG))==0 )
    {
        return EFI_INVALID_PARAMETER;
    }

    return EFI_UNSUPPORTED;
}


/**
    This is USB2HC API to get the host controller state.

    @param  This                    Pointer to EFI_USB2_HC_PROTOCOL
    @param  State                   Pointer to Host state
    
    @retval EFI_SUCCESS             The get Host state feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsb2HcGetState(
  IN  EFI_USB2_HC_PROTOCOL    *This,
  OUT EFI_USB_HC_STATE        *State
)
{

    HC_DXE_RECORD *Rec = GetThis(This);
    
    if (State == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (Rec->HcStruc->HcFlag & HC_STATE_RUNNING) {
        *State = EfiUsbHcStateOperational;
        return EFI_SUCCESS;
    }

    if (Rec->HcStruc->HcFlag & HC_STATE_SUSPEND) {
        *State = EfiUsbHcStateSuspend;
        return EFI_SUCCESS;
    }

    *State = EfiUsbHcStateHalt;

    return EFI_SUCCESS;
}


/**
    This is USB2HC API to set the host controller state.
    @param  This    Pointer to EFI_USB2_HC_PROTOCOL
    @param  State   USB host controller state

    @retval EFI_SUCCESS             The set Host state feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsb2HcSetState(
  IN EFI_USB2_HC_PROTOCOL    *This,
  IN EFI_USB_HC_STATE        State
)
{
    HC_DXE_RECORD       *Rec = GetThis(This);
    EFI_USB_HC_STATE    CurrentState;
    EFI_STATUS          Status;
    UINT8               UsbStatus = USB_SUCCESS;

    Status = AmiUsb2HcGetState(This, &CurrentState);

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    if (CurrentState == State) {
        return Status;
    }

    switch (State) {
        case EfiUsbHcStateHalt:
            UsbStatus = (UINT8)UsbSmiHc(AmiUsbHc_Stop, Rec->HcStruc->HcType, Rec->HcStruc);
            break;
        case EfiUsbHcStateOperational:
            UsbStatus = (UINT8)UsbSmiHc(AmiUsbHc_Start, Rec->HcStruc->HcType, Rec->HcStruc);
            break;
        case EfiUsbHcStateSuspend:
            UsbStatus = (UINT8)UsbSmiHc(AmiUsbHc_GlobalSuspend, Rec->HcStruc->HcType, Rec->HcStruc);
            break;
        default:
            Status = EFI_INVALID_PARAMETER;
            break;
    }

    if (UsbStatus != USB_SUCCESS) {
        Status = EFI_DEVICE_ERROR;
    }
    
    return Status;
}

/**
    This function checks if queue has a new transfer. If yes, calls a
    callback with data from transfer.

    @param  Event       Efi event occurred upon AsyncInterrupt
    @param  Context     Usb Hc interrupt device info

**/

VOID
EFIAPI
AsyncInterruptOnTimer (
    EFI_EVENT   Event,
    VOID        *Ctx
)
{
    USBHC_INTERRUPT_DEVNINFO_T *IntDeviceInfo = (USBHC_INTERRUPT_DEVNINFO_T*)Ctx;
    BOOLEAN Lock;
    VOID    *Data;
    UINTN   DataLength;
        
    if (IntDeviceInfo == NULL) {
      return;
    }    
    //
    // Check re-entrance
    //
    ATOMIC({Lock = IntDeviceInfo->Lock; IntDeviceInfo->Lock = TRUE;});
    if (Lock) {
      return; //control is already inside
    }

    if (QueueSize(&IntDeviceInfo->QCompleted)) {
        if (QueueSize(&IntDeviceInfo->QCompleted) > IntDeviceInfo->DataLength) {
            while (QueueSize(&IntDeviceInfo->QCompleted) >= IntDeviceInfo->DataLength) {
                 ATOMIC(Data = QueueRemoveMsg(&IntDeviceInfo->QCompleted, IntDeviceInfo->DataLength));
                if (IntDeviceInfo->CallbackFunction == NULL) {
                    USB_DEBUG (DEBUG_DEV_INIT,"[IntDeviceInfo] CallbackFunction is NULL\n");
                    return;
                }
                IntDeviceInfo->CallbackFunction(
                                 Data,
                                 IntDeviceInfo->DataLength, 
                                 IntDeviceInfo->Context, 
                                 EFI_USB_NOERROR
                                 );
                                                   
            } 
        } else {
            DataLength = QueueSize(&IntDeviceInfo->QCompleted);
            ATOMIC(Data = QueueRemoveMsg(&IntDeviceInfo->QCompleted, DataLength));
            if (IntDeviceInfo->CallbackFunction == NULL) {
                USB_DEBUG (DEBUG_DEV_INIT,"[IntDeviceInfo] CallbackFunction is NULL\n");
                return;
            }
            IntDeviceInfo->CallbackFunction(
                             Data, 
                             DataLength,
                             IntDeviceInfo->Context, 
                             EFI_USB_NOERROR
                             );
      
        }
    }

    IntDeviceInfo->Lock = FALSE;
}


/**
    This function performs USB2 HC Bulk Transfer

    @param HcProtocol    Pointer to EFI_USB2_HC_PROTOCOL
    @param DeviceAddress USB device address
    @param EndpointAddress Endpoint address
    @param DeviceSpeed   Usb Device speed
    @param MaximumPacketLength Max packet size
    @param DataBuffersNumber Data buffer number
    @param Data          Buffer containing data to be sent to the device 
                         or buffer to be used to receive data value
    @param DataLength    Length request parameter, number of bytes of data 
                         to be transferred in or out of the HC
    @param DataToggle    Point to data toogle
    @param Timeout       Time out value
    @param Translator    Point to EFI_USB2_HC_TRANSACTION_TRANSLATOR
    @param TransferResult Point to transfer result

    @retval EFI_SUCCESS             The bulk transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
EFIAPI
AmiUsb2HcBulkTransfer(
    IN EFI_USB2_HC_PROTOCOL *HcProtocol,
    IN  UINT8       DeviceAddress,
    IN  UINT8       EndpointAddress,
    IN  UINT8       DeviceSpeed,
    IN  UINTN       MaximumPacketLength,
    IN  UINT8       DataBuffersNumber,
    IN OUT VOID     *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
    IN OUT UINTN    *DataLength,
    IN OUT UINT8    *DataToggle,
    IN  UINTN       Timeout,
    IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    OUT UINT32      *TransferResult
)
{
    UINT32  SmiRes;
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    DEV_INFO* DevInfo;
    DEV_INFO* DevSrc = DevAddr2Info( DeviceAddress, This->HcStruc );
    UINT8 XferDir = 0;
    UINT16 CurrentTimeout;
    UINT8 ToggleBit = (EndpointAddress & 0xF) - 1;

    //
    // Check Params
    //
    if (DevSrc == NULL || Data == NULL || Data[0] == NULL ||
        (*DataToggle != 0 && *DataToggle != 1) ||
        (DeviceSpeed != EFI_USB_SPEED_SUPER && DeviceSpeed != EFI_USB_SPEED_HIGH 
        && DeviceSpeed != EFI_USB_SPEED_FULL) ||
        *DataLength == 0 || TransferResult == NULL ||
        MaximumPacketLength == 0 ) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Check for valid maximum packet length
    //
    if (DeviceSpeed == EFI_USB_SPEED_SUPER && MaximumPacketLength > 1024) {
        return EFI_INVALID_PARAMETER;
    }
    if (DeviceSpeed == EFI_USB_SPEED_HIGH && MaximumPacketLength > 512) {
        return EFI_INVALID_PARAMETER;
    }
    if (DeviceSpeed == EFI_USB_SPEED_FULL && MaximumPacketLength > 64) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Alloc DEV_INFO
    //
    DevInfo = AllocDevInfo();

    if (DevInfo == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Fill DEV_INFO
    //
    DevInfo->DeviceAddress = DeviceAddress;
    DevInfo->HcNumber = This->HcStruc->HcNumber;
    DevInfo->EndpointSpeed = gSpeedMap[DeviceSpeed];
    DevInfo->HubDeviceNumber = DevSrc->HubDeviceNumber;
    DevInfo->HubPortNumber = DevSrc->HubPortNumber;
    DevInfo->DevMiscInfo = DevSrc->DevMiscInfo; //(EIP84790+)

    if (EndpointAddress & 0x80) {
        XferDir = 0x80;
        DevInfo->BulkInEndpoint = EndpointAddress & 0xF;
        DevInfo->BulkInMaxPkt = (UINT16)MaximumPacketLength;
        DevInfo->DataInSync = (UINT16)(*DataToggle) << ToggleBit;
    } else {
        XferDir = 0x0;
        DevInfo->BulkOutEndpoint = EndpointAddress & 0xF;
        DevInfo->BulkOutMaxPkt = (UINT16)MaximumPacketLength;
        DevInfo->DataOutSync = (UINT16)(*DataToggle) << ToggleBit;
    }

    //
    // Call SMI routine and retrieve last status
    // if any error
    //
    CRITICAL_CODE( TPL_NOTIFY, {
        CurrentTimeout = gUsbData->UsbReqTimeOutValue;
        gUsbData->UsbReqTimeOutValue = (UINT16)Timeout;
        DevInfo->UsbLastCommandStatusExtended = 0;
        SmiRes = UsbSmiBulkTransfer(
                   This->HcStruc, DevInfo,
                   XferDir,
                  (UINT8*)Data[0],
                  (UINT32)*DataLength );
        *TransferResult = GetTransferStatus(DevInfo);
        gUsbData->UsbReqTimeOutValue = CurrentTimeout;
    });

    //
    // Update the data length
    //
    *DataLength = (UINTN)SmiRes;

    //
    // Update Toggle bit
    //
    if (XferDir) {
        *DataToggle = (UINT8)(DevInfo->DataInSync >> ToggleBit) & 0x1;
    } else {
        *DataToggle = (UINT8)(DevInfo->DataOutSync >> ToggleBit) & 0x1;
    }
    FreeDevInfo(DevInfo);

    if ((*TransferResult) & EFI_USB_ERR_TIMEOUT) {
        return EFI_TIMEOUT;
    }
    return (*TransferResult)? EFI_DEVICE_ERROR:EFI_SUCCESS;
}


/**
    This function performs USB2 HC Async Interrupt Transfer
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Address of Endpoint
    @param  DeviceSpeed             Speed of Device
    @param  MaxPacket               Max Packet of Device
    @param  IsNewTransfer           Check is new transfer or not
    @param  DataToggle              Data toggle
    @param  PollingInterval         Polling interval
    @param  DataLength              Data length
    @param  Translator              Point to usb2 hc transaction translator
    @param  CallbackFunction        Interrupt call back function
    @param  Context                 Point to transfer context

    @retval EFI_SUCCESS             The Async interrupt transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.   
**/

EFI_STATUS
EFIAPI
AmiUsb2HcAsyncInterruptTransfer(
    IN EFI_USB2_HC_PROTOCOL *HcProtocol,
    IN UINT8                DeviceAddress,
    IN UINT8                EndpointAddress,
    IN UINT8                DeviceSpeed,
    IN UINTN                MaxPacket,
    IN BOOLEAN              IsNewTransfer,
    IN OUT UINT8            *DataToggle,
    IN UINTN                PollingInterval,
    IN UINTN                DataLength,
    IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    IN EFI_ASYNC_USB_TRANSFER_CALLBACK  CallbackFunction ,
    IN VOID                 *Context
)
{
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    DEV_INFO* DevInfo;
    DEV_INFO* DevInfoSrc = DevAddr2Info( DeviceAddress, This->HcStruc );
    USBHC_INTERRUPT_DEVNINFO_T* AsyncTransfer = 0;
    UINT8     SmiStatus = USB_SUCCESS;
    UINT8     ToggleBit = (EndpointAddress & (BIT0 | BIT1 | BIT2 | BIT3))-1;
    EFI_STATUS  Status;
    DEV_INFO  *LastDev = gUsbDataList->DevInfoTable + gUsbData->MaxDevCount;
    BOOLEAN   FreeDummyDevInfo = FALSE;

    if (DeviceSpeed != EFI_USB_SPEED_SUPER && 
         DeviceSpeed != EFI_USB_SPEED_HIGH &&
         DeviceSpeed != EFI_USB_SPEED_FULL &&
         DeviceSpeed != EFI_USB_SPEED_LOW){
         return EFI_INVALID_PARAMETER;
    }

    if (!(EndpointAddress & BIT7)) {
        return EFI_INVALID_PARAMETER;
    }

    if( DevInfoSrc == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    DevInfo = FindOldTransfer( DevInfoSrc->HubPortNumber, 
                               DevInfoSrc->HubDeviceNumber, 
                               EndpointAddress, This->HcStruc );
    
    if (IsNewTransfer){

        if (DataLength == 0) {
            return EFI_INVALID_PARAMETER;
        }

        if (*DataToggle != 0 && *DataToggle != 1) {
            return EFI_INVALID_PARAMETER;
        }

        if (PollingInterval < 1 || PollingInterval > 255) {     //Input polling interval should be less than 255
            return EFI_INVALID_PARAMETER;                       //and should be greater than 1, or return
        }                                                       //invalid parameter
        
        if( CallbackFunction == NULL) {
            return EFI_INVALID_PARAMETER;
        }
        if( DevInfo != NULL ){
            USB_DEBUG(DEBUG_DEV_INIT,"Stacked AsyncInterrupt request are not supported\n");
            return EFI_INVALID_PARAMETER;
        }
        DevInfo = AllocDevInfo();
        CopyMem(DevInfo, DevInfoSrc, sizeof(DEV_INFO));
        DevInfo->IntInEndpoint = EndpointAddress;
        DevInfo->EndpointSpeed = gSpeedMap[DeviceSpeed];
        DevInfo->IntInMaxPkt = (UINT16)MaxPacket;    //(EIP84790+)
        DevInfo->PollInterval = TranslateInterval(DeviceSpeed, PollingInterval);
        DevInfo->HubDeviceNumber = DevInfoSrc->HubDeviceNumber;
        DevInfo->HubPortNumber = DevInfoSrc->HubPortNumber;
        DevInfo->DeviceAddress = DeviceAddress;
        DevInfo->PollingLength = (UINT16)DataLength;

        //create new transfer
        gBS->AllocatePool (EfiBootServicesData,
               sizeof(USBHC_INTERRUPT_DEVNINFO_T) + DataLength*INTERRUPTQUEUESIZE,
               (VOID**)&AsyncTransfer );
        SetMem(AsyncTransfer, sizeof(USBHC_INTERRUPT_DEVNINFO_T)+
          DataLength*INTERRUPTQUEUESIZE, 0);
        DevInfo->ExtraData = (UINT8*)AsyncTransfer;
        AsyncTransfer->QCompleted.Data = (VOID *volatile *)AsyncTransfer->Data;
        AsyncTransfer->QCompleted.Maxsize = DataLength * INTERRUPTQUEUESIZE;
        AsyncTransfer->DataLength = DataLength;
        AsyncTransfer->EndpointAddress = EndpointAddress;
        InitializeListHead(&AsyncTransfer->Link);

        DevInfo->Flag |= DEV_INFO_DEV_DUMMY;
        
        Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK, AsyncInterruptOnTimer,
                        AsyncTransfer,&AsyncTransfer->Event);
        
        ASSERT_EFI_ERROR(Status);
        
        if (EFI_ERROR(Status)) {
            return Status;
        }

        PollingInterval = PollingInterval < 32 ? 32 : PollingInterval;      //Polling interval for setTimer()
                                                                            //should be greater than 32
        Status = gBS->SetTimer(
                        AsyncTransfer->Event, 
                        TimerPeriodic,
                        PollingInterval * MILLISECOND
                        );
                
        ASSERT_EFI_ERROR(Status);
                
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        AsyncTransfer->CallbackFunction = CallbackFunction;
        AsyncTransfer->Context = Context;
        if(EndpointAddress & BIT7) {
            DevInfo->DataInSync = (UINT16)(*DataToggle) << ToggleBit;
        } else {
            DevInfo->DataOutSync = (UINT16)(*DataToggle) << ToggleBit;
        }

        //
        // Activate transfer
        //
        SmiStatus = UsbSmiActivatePolling(This->HcStruc, DevInfo);
        ASSERT(SmiStatus==USB_SUCCESS);
    } else {
        
        if( DevInfo == NULL  || DevInfo->ExtraData == NULL ){
            
            //
            // Search the DevInfo by DEV_INFO_DEV_DUMMY_CANCEL
            //
            for ( DevInfo = &gUsbDataList->DevInfoTable[1]; DevInfo != LastDev; ++DevInfo ){
                
                if ((DevInfo->Flag & (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_DUMMY | DEV_INFO_DEV_DUMMY_CANCEL)) ==
                                     (DEV_INFO_VALID_STRUC | DEV_INFO_DEV_DUMMY | DEV_INFO_DEV_DUMMY_CANCEL)) {
                            FreeDummyDevInfo = TRUE;
                            break;
                }
            }

            if(FreeDummyDevInfo == FALSE){
                USB_DEBUG(DEBUG_DEV_INIT, "[AsyncInterruptTransfer]Dummy DevInfo not found when canceling\n");
                return EFI_INVALID_PARAMETER;
            }
        }
        AsyncTransfer = (USBHC_INTERRUPT_DEVNINFO_T*)DevInfo->ExtraData;
        DevInfo->ExtraData = 0;
        // 
        // Deactivate transfer
        //
        SmiStatus = UsbSmiDeactivatePolling (This->HcStruc, DevInfo);
        if (DataToggle){
            if(EndpointAddress & BIT7) {
                *DataToggle = (UINT8)(DevInfo->DataInSync >> ToggleBit) & BIT0;
            } else {
                *DataToggle = (UINT8)(DevInfo->DataOutSync >> ToggleBit) & BIT0;
            }
        }
        gBS->SetTimer(AsyncTransfer->Event, TimerCancel, 0);
        gBS->CloseEvent(AsyncTransfer->Event);
        gBS->FreePool(AsyncTransfer);
        FreeDevInfo(DevInfo);
    }

    return SmiStatus == USB_SUCCESS? EFI_SUCCESS : EFI_DEVICE_ERROR;
}


/**
    This function performs USB2 HC Sync Interrupt Transfer
    
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Address of Endpoint
    @param  DeviceSpeed             Device speed
    @param  MaxPacket               Max packet of device
    @param  Data                    Point to interrupt transfer data
    @param  DataLength              Point to interrupt transfer data length
    @param  DataToggle              Point to interrupt transfer data toggle
    @param  Timeout                 Time out value
    @param  Translator              Point to usb2 hc transaction translator
    @param  TransferResult          Point to transfer result

    @retval EFI_SUCCESS             The Sync interrupt transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid. 
**/

EFI_STATUS
EFIAPI
AmiUsb2HcSyncInterruptTransfer(
    IN EFI_USB2_HC_PROTOCOL    *HcProtocol,
    IN     UINT8                DeviceAddress,
    IN     UINT8                EndpointAddress,
    IN     UINT8                DeviceSpeed,
    IN     UINTN                MaximumPacketLength,
    IN OUT VOID                 *Data,
    IN OUT UINTN                *DataLength,
    IN OUT UINT8                *DataToggle,
    IN     UINTN                Timeout,
    IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    OUT    UINT32                *TransferResult
)
{
    UINT16      SmiRes;
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    DEV_INFO    *DevInfo;
    DEV_INFO*   DevSrc = DevAddr2Info( DeviceAddress, This->HcStruc );
    UINT16      CurrentTimeout;
    UINT8       ToggleBit = (EndpointAddress & (BIT0 | BIT1 | BIT2 | BIT3))-1;
    UINT16      *wDataSync;

    if (DeviceSpeed != EFI_USB_SPEED_SUPER && 
        DeviceSpeed != EFI_USB_SPEED_HIGH && 
        DeviceSpeed != EFI_USB_SPEED_FULL && 
        DeviceSpeed != EFI_USB_SPEED_LOW) {
        return EFI_INVALID_PARAMETER;
    }

    if ((gUsbData->UsbFeature & USB_EFI_USB_HC_INTERRUPT_OUT_SUPPORT) == 0){
        if (!(EndpointAddress & BIT7)) {
            return EFI_INVALID_PARAMETER;
        }
    }

    if (Data == NULL || DataLength == NULL ||
        *DataLength == 0 || TransferResult == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if ( DeviceSpeed == EFI_USB_SPEED_LOW  && MaximumPacketLength != 8) {   //Device is low speed and maximum packet
        return EFI_INVALID_PARAMETER;                                       //should be 8, or return invalid parameter
    }

    if (DeviceSpeed == EFI_USB_SPEED_FULL &&            //Device is full speed and maximum packet should be
        (MaximumPacketLength != 8 &&                    // 8/16/32/64 , or return invalid parameter
        MaximumPacketLength != 16 &&
        MaximumPacketLength != 32 &&
        MaximumPacketLength != 64)) {
        return EFI_INVALID_PARAMETER;
    }

    if (DeviceSpeed == EFI_USB_SPEED_HIGH && MaximumPacketLength > 3072 ) { //Device is high speed and maximum packet
        return EFI_INVALID_PARAMETER;                                       //should be less than 3072, or return
    }                                                                       //invalid parameter

    if (*DataToggle != 0 && *DataToggle != 1) return EFI_INVALID_PARAMETER;
        
    if (DevSrc == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    DevInfo = AllocDevInfo();
    DevInfo->DeviceAddress = DeviceAddress;
    DevInfo->HcNumber = This->HcStruc->HcNumber;
    DevInfo->EndpointSpeed = gSpeedMap[DeviceSpeed];
    DevInfo->PollInterval = TranslateInterval(DeviceSpeed, 1);
    DevInfo->HubDeviceNumber = DevSrc->HubDeviceNumber;
    DevInfo->HubPortNumber = DevSrc->HubPortNumber;
    DevInfo->DevMiscInfo = DevSrc->DevMiscInfo;     //(EIP84790+)

    wDataSync = (EndpointAddress & BIT7) ? &DevInfo->DataInSync : 
                &DevInfo->DataOutSync;

    *wDataSync = (UINT16)(*DataToggle) << ToggleBit;

    CRITICAL_CODE( TPL_NOTIFY, {
        CurrentTimeout = gUsbData->UsbReqTimeOutValue;
        gUsbData->UsbReqTimeOutValue = (UINT16)Timeout;
        DevInfo->UsbLastCommandStatusExtended = 0;
        SmiRes = UsbSmiInterruptTransfer(
                   This->HcStruc,
                   DevInfo,
                   EndpointAddress,
                   (UINT16)MaximumPacketLength,
                   (UINT8*)Data,
                   (UINT16)*DataLength
                   );
        *TransferResult = GetTransferStatus(DevInfo);
        gUsbData->UsbReqTimeOutValue = CurrentTimeout;
    });

    *DataLength = (UINTN)SmiRes;
    *DataToggle = (UINT8)(*wDataSync >> ToggleBit) & BIT0;

    FreeDevInfo(DevInfo);
    //
    // Return with error or success
    //
    if ( (*TransferResult) &  EFI_USB_ERR_TIMEOUT ) return EFI_TIMEOUT;
    return (*TransferResult)? EFI_DEVICE_ERROR:EFI_SUCCESS;
}


/**
    This function performs USB2 HC Isochronous Transfer

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Address of Endpoint
    @param  DeviceSpeed             Device speed
    @param  MaximumPacketLength     Max packet of device
    @param  DataBuffersNumber       Data buffer number
    @param  Data                    Point to interrupt transfer data
    @param  DataLength              Point to interrupt transfer data length
    @param  Translator              Point to usb2 hc transaction translator
    @param  TransferResult          Point to transfer result

    @retval EFI_SUCCESS             The Isochronous transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid. 
**/

EFI_STATUS
EFIAPI
AmiUsb2HcIsochronousTransfer(
    IN     EFI_USB2_HC_PROTOCOL               *HcProtocol,
    IN     UINT8                              DeviceAddress,
    IN     UINT8                              EndPointAddress,
    IN     UINT8                              DeviceSpeed,
    IN     UINTN                              MaximumPacketLength,
    IN     UINT8                              DataBuffersNumber,
    IN OUT VOID                               *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    IN     UINTN                              DataLength,
    IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    OUT    UINT32                             *TransferResult
)
{
    HC_DXE_RECORD   *This;
    DEV_INFO        *DevInfo;
    UINT32          SmiRes;

    if (Data == NULL || Data[0] == NULL || DataLength == 0 ||
        (DeviceSpeed != EFI_USB_SPEED_SUPER && DeviceSpeed != EFI_USB_SPEED_HIGH 
        && DeviceSpeed != EFI_USB_SPEED_FULL) || TransferResult == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    if ((DeviceSpeed == EFI_USB_SPEED_HIGH || DeviceSpeed == EFI_USB_SPEED_SUPER)
        && MaximumPacketLength > 1024) {
        return EFI_INVALID_PARAMETER;
    }
    if (DeviceSpeed == EFI_USB_SPEED_FULL && MaximumPacketLength > 1023) {
        return EFI_INVALID_PARAMETER;
    }

    This = GetThis(HcProtocol);

    // Several DevInfo might have same DeviceAddress, validate it using
    // endpoint address
    for (DevInfo = NULL; ;DevInfo++) {
        DevInfo = SearchDevinfoByAdr(DevInfo, DeviceAddress, This->HcStruc);
        if (DevInfo == NULL || DevInfo->IsocDetails.Endpoint == EndPointAddress) break;
    }
    
    ASSERT(DevInfo);
    if (DevInfo == NULL) {
        return EFI_NOT_FOUND;
    }

    CRITICAL_CODE( TPL_NOTIFY, {
        DevInfo->UsbLastCommandStatusExtended = 0;
        SmiRes = UsbSmiIsocTransfer(
                   This->HcStruc,
                   DevInfo,
                   EndPointAddress & 0x80,
                   (UINT8*)Data[0],
                   (UINT32)DataLength,
                   NULL
                   );
        *TransferResult = GetTransferStatus(DevInfo);
    });
    USB_DEBUG(DEBUG_HC, "Isoc Transfer:transferred bytes: %x \n", SmiRes);
    //
    // Return with error or success
    //
    if ((*TransferResult) & EFI_USB_ERR_TIMEOUT) {
        return EFI_TIMEOUT;
    }
    return (*TransferResult) ? EFI_DEVICE_ERROR:EFI_SUCCESS;
}

/**
    This function checks if queue has a new transfer. If yes, calls a
    callback with data from transfer.

    @param  Event       Efi event occurred upon Isochronous.
    @param  Context     Usb Hc interrupt device info

**/
VOID
EFIAPI
AsyncIsochOnTimer (
    EFI_EVENT   Event,
    VOID        *Context
)
{
    USBHC_ASYNC_ISOC_CONTEXT *Ctx = (USBHC_ASYNC_ISOC_CONTEXT*)Context;

    if (Ctx->Complete)
    {
        Ctx->CallbackFunction(Ctx->Data, Ctx->DataLength, Ctx->Context, 0);

        gBS->CloseEvent(Ctx->Event);
        gBS->FreePool(Ctx);
    }
}


/**
    This function performs USB2 HC Async Isochronous Transfer

    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  EndpointAddress         Endpoint address
    @param  DeviceSpeed             Device speed
    @param  MaximumPacketLength     Max packet of device
    @param  DataBuffersNumber       Data buffer number
    @param  Data                    Point to Async interrupt transfer data
    @param  DataLength              Point to Ansync interrupt transfer data length
    @param  IsochronousCallback     Point to call back function.
    @param  Translator              Point to usb2 hc transaction translator
    @param  Context                 Point to Context
    
    @retval EFI_SUCCESS             The Async isochronous transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid. 
**/

EFI_STATUS
EFIAPI
AmiUsb2HcAsyncIsochronousTransfer(
    IN     EFI_USB2_HC_PROTOCOL               *HcProtocol,
    IN     UINT8                              DeviceAddress,
    IN     UINT8                              EndPointAddress,
    IN     UINT8                              DeviceSpeed,
    IN     UINTN                              MaximumPacketLength,
    IN     UINT8                              DataBuffersNumber,
    IN OUT VOID                               *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    IN     UINTN                              DataLength,
    IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    IN     EFI_ASYNC_USB_TRANSFER_CALLBACK    IsochronousCallBack,
    IN     VOID                               *Context OPTIONAL
)
{
    HC_DXE_RECORD   *This;
    DEV_INFO        *DevInfo;
    USBHC_ASYNC_ISOC_CONTEXT    *AsyncIsocTransfer;

    if (Data == NULL || Data[0] == NULL || DataLength == 0 ||
        (DeviceSpeed != EFI_USB_SPEED_SUPER && DeviceSpeed != EFI_USB_SPEED_HIGH 
        && DeviceSpeed != EFI_USB_SPEED_FULL)) {
        return EFI_INVALID_PARAMETER;
    }

    if ((DeviceSpeed == EFI_USB_SPEED_HIGH || DeviceSpeed == EFI_USB_SPEED_SUPER)
        && MaximumPacketLength > 1024) {
        return EFI_INVALID_PARAMETER;
    }
    if (DeviceSpeed == EFI_USB_SPEED_FULL && MaximumPacketLength > 1023) {
        return EFI_INVALID_PARAMETER;
    }

    This = GetThis(HcProtocol);

    // Several DevInfo might have same DeviceAddress, validate it using
    // endpoint address
    for (DevInfo = NULL; ;DevInfo++) {
        DevInfo = SearchDevinfoByAdr(DevInfo, DeviceAddress, This->HcStruc);
        if (DevInfo == NULL || DevInfo->IsocDetails.Endpoint == EndPointAddress) {
            break;
        }
    }
    
    ASSERT(DevInfo);
    if (DevInfo == NULL) {
        return EFI_NOT_FOUND;
    }

    // create new transfer
    gBS->AllocatePool (EfiBootServicesData, sizeof(USBHC_ASYNC_ISOC_CONTEXT), (VOID**)&AsyncIsocTransfer );
    
    AsyncIsocTransfer->CallbackFunction = IsochronousCallBack;
    AsyncIsocTransfer->Context = Context;
    AsyncIsocTransfer->Data = Data[0];
    AsyncIsocTransfer->DataLength = DataLength;
    AsyncIsocTransfer->Complete = 0;

    gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
           TPL_CALLBACK, AsyncIsochOnTimer, AsyncIsocTransfer, &AsyncIsocTransfer->Event);
    
    gBS->SetTimer(AsyncIsocTransfer->Event, TimerPeriodic, 55 * MILLISECOND);

    DevInfo->UsbLastCommandStatusExtended = 0;
    
    UsbSmiIsocTransfer(
      This->HcStruc,
      DevInfo,
      EndPointAddress & 0x80,
      (UINT8*)Data[0],
      (UINT32)DataLength,
      &AsyncIsocTransfer->Complete
      );

    return EFI_SUCCESS;
}


/**
    This function performs USB2 HC Control Transfer
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  DeviceAddress           Device address
    @param  DeviceSpeed             Device speed
    @param  MaximumPacketLength     Max packet of device
    @param  Request                 Point to transfer requestion
    @param  TransferDirection       Transfer directioin
    @param  Data                    Point to interrupt transfer data
    @param  DataLength              Point to interrupt transfer data length
    @param  Timeout                 Time out value
    @param  Translator              Point to usb2 hc transaction translator
    @param  TransferResult          Point to transfer result

    @retval EFI_SUCCESS             The control transfer succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid. 
**/

EFI_STATUS
EFIAPI
AmiUsb2HcControlTransfer(
    IN EFI_USB2_HC_PROTOCOL           *HcProtocol,
    IN     UINT8                      DeviceAddress,
    IN     UINT8                      DeviceSpeed,
    IN     UINTN                      MaximumPacketLength,
    IN     EFI_USB_DEVICE_REQUEST     *Request,
    IN     EFI_USB_DATA_DIRECTION     TransferDirection,
    IN OUT VOID                       *Data ,
    IN OUT UINTN                      *DataLength,
    IN     UINTN                      Timeout,
    IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    OUT    UINT32                     *TransferResult
)
{
    UINT16      SmiRes;
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    DEV_INFO    *DevInfo;
    DEV_INFO    *DevSrc = DevAddr2Info( DeviceAddress, This->HcStruc );
    UINT16      CurrentTimeout;
    EFI_STATUS  Status;

    if ((DeviceSpeed != EFI_USB_SPEED_SUPER && DeviceSpeed != EFI_USB_SPEED_HIGH
            && DeviceSpeed != EFI_USB_SPEED_FULL && DeviceSpeed != EFI_USB_SPEED_LOW)
            || DevSrc == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (TransferDirection < EfiUsbDataIn || TransferDirection > EfiUsbNoData) {
        return EFI_INVALID_PARAMETER;
    }

    if (TransferDirection == EfiUsbNoData && (Data != NULL || *DataLength != 0)) {
        return EFI_INVALID_PARAMETER;
    }

    if (TransferDirection != EfiUsbNoData && (Data == NULL || *DataLength == 0)) {
        return EFI_INVALID_PARAMETER;
    }

    if (Request == NULL || TransferResult == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (DeviceSpeed == EFI_USB_SPEED_LOW  && MaximumPacketLength != 8) {        //Device is low speed and maximum
        return EFI_INVALID_PARAMETER;                                           //packet should be 8, or return
    }                                                                           //invalid parameter

    if ((DeviceSpeed == EFI_USB_SPEED_HIGH || DeviceSpeed == EFI_USB_SPEED_FULL) && //Device is high/full speed
            ( MaximumPacketLength != 8 &&                                           //and maximum packet should
             MaximumPacketLength != 16 &&                                           //be 8/16/32/64, or return
             MaximumPacketLength != 32 &&                                           //invalid parameter
             MaximumPacketLength != 64 )) {
        return EFI_INVALID_PARAMETER;
    }

    if (DeviceSpeed == EFI_USB_SPEED_SUPER && MaximumPacketLength != 512) {     //Device is super speed and
        return EFI_INVALID_PARAMETER;                                       //maximum packet should be 512,
    }                                                                       // or return invalid parameter

    DevInfo = AllocDevInfo();
    DevInfo->DeviceAddress = DeviceAddress;
    DevInfo->HcNumber = This->HcStruc->HcNumber;
    DevInfo->EndpointSpeed = gSpeedMap[DeviceSpeed];
    DevInfo->Endp0MaxPacket = (UINT16)MaximumPacketLength;
    DevInfo->HubDeviceNumber = DevSrc->HubDeviceNumber;
    DevInfo->HubPortNumber = DevSrc->HubPortNumber;
    DevInfo->DevMiscInfo = DevSrc->DevMiscInfo; //(EIP84790+)

    CRITICAL_CODE( TPL_NOTIFY, {
        CurrentTimeout = gUsbData->UsbReqTimeOutValue;
        gUsbData->UsbReqTimeOutValue = (UINT16)Timeout;
        DevInfo->UsbLastCommandStatusExtended = 0;
        SmiRes = UsbSmiControlTransfer(
                   This->HcStruc, DevInfo,
                   (UINT16)((( TransferDirection == EfiUsbDataIn?1:0) << 7) |
                   (((UINT16)Request->RequestType)) |
                   (((UINT16)Request->Request)<<8)),
                   (UINT16)Request->Index, 
                   (UINT16)Request->Value,
                   (UINT8*)Data, 
                   (UINT16)Request->Length
                   );
        *TransferResult = GetTransferStatus(DevInfo);
        gUsbData->UsbReqTimeOutValue = CurrentTimeout;
    });

    Status = EFI_SUCCESS;

    if ((*TransferResult) & EFI_USB_ERR_TIMEOUT) {
        Status = EFI_TIMEOUT;
    }
    if ((*TransferResult) & ~EFI_USB_ERR_TIMEOUT) {
        Status = EFI_DEVICE_ERROR;
    }

    *DataLength = (UINTN)SmiRes;

    FreeDevInfo(DevInfo);

    return Status;
}


/**
    This function returns HC root port status.
    
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortStatus              Pointer to Port status
    
    @retval EFI_SUCCESS             The get root hub port status succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsb2HcGetRootHubPortStatus (
    EFI_USB2_HC_PROTOCOL *HcProtocol,
    UINT8               PortNumber,
    EFI_USB_PORT_STATUS *PortStatus
)
{
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    return AmiUsbHcGetRootHubPortStatus(
             &This->HcProtocol, 
             PortNumber, 
             PortStatus
             );
}


/**
    This function set root hub port features.
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortFeature             Port feature.
    
    @retval EFI_SUCCESS             The set root hub port feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS
EFIAPI
AmiUsb2HcSetRootHubPortFeature(
    IN EFI_USB2_HC_PROTOCOL *HcProtocol,
    IN UINT8                PortNumber,
    IN EFI_USB_PORT_FEATURE PortFeature
)
{
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    return AmiUsbHcSetRootHubPortFeature(
             &This->HcProtocol, 
             PortNumber, 
             PortFeature
             );
}


/**
    This function clears root hub port feature.
    @param  HcProtocol              Pointer to EFI_USB2_HC_PROTOCOL
    @param  PortNumber              Port number
    @param  PortFeature             Port feature.
    
    @retval EFI_SUCCESS             The clear root hub port feature succeeded.
    @retval EFI_INVALID_PARAMETER   Input is not valid.
**/

EFI_STATUS EFIAPI
AmiUsb2HcClearRootHubPortFeature(
    IN EFI_USB2_HC_PROTOCOL *HcProtocol,
    IN UINT8                PortNumber,
    IN EFI_USB_PORT_FEATURE PortFeature
)
{
    HC_DXE_RECORD *This = GetThis( HcProtocol );
    return AmiUsbHcClearRootHubPortFeature(
             &This->HcProtocol, 
             PortNumber, 
             PortFeature
             );
}


/**
    Search gUsbData for information about HC linked to an EFI handle

    @param Controller   Host Controller handle
    @retval Pointer     Ptr to Host struc
**/

HC_STRUC* FindHcStruc(
    EFI_HANDLE Controller
)
{
    UINTN Index;
    for (Index = 0; Index < gUsbDataList->HcTableCount; Index++) {
        if (gHcTable[Index] == NULL) {
            continue;
        }
        if (!(gHcTable[Index]->HcFlag & HC_STATE_USED)) {
            continue;
        }
        if (gHcTable[Index]->Controller == Controller )
            return gHcTable[Index];
    }
    return NULL;
}

/**
    Start the AMI USB driver; Sets USB_FLAG_DRIVER_STARTED
 
    @param This                Protocol instance pointer.
    @param Controller          Handle of controller
    @param PciIo               Ptr to EFI_PCI_IO_PROTOCOL
    @param HCStruc             Pointer to the HCStruc structure

    @retval EFI_SUCCESS          USB HC devices were initialized.
    @retval EFI_UNSUPPORTED      This device is not supported by USB driver.
    @retval EFI_DEVICE_ERROR     This driver cannot be started due to device error
    @retval EFI_OUT_OF_RESOURCES Allocate memory fail.

**/

EFI_STATUS
EFIAPI
InstallHcProtocols(
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_PCI_IO_PROTOCOL          *PciIo,
    IN HC_STRUC                     *HcStruc
)
{
    HC_DXE_RECORD           *Rec;
    USB3_HOST_CONTROLLER    *Usb3Hc;
    EFI_STATUS              Status;
    UINT16                  ExtendedCapOffset;
    UINT32                  TempAddress;
    XHCI_EXT_CAP            *XhciExtCap = (XHCI_EXT_CAP*)&TempAddress;
    
    //
    // Create HcDxeRecord
    //

    Status = gBS->AllocatePool(
                    EfiBootServicesData,
                    sizeof(HC_DXE_RECORD),
                    (VOID**)&Rec
                    );
    
    ASSERT_EFI_ERROR(Status);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
        
    Rec->HcStruc = HcStruc;
    Rec->PciIo = PciIo;

    InitializeListHead(&Rec->AsyncTransfers.Link);
    Rec->AsyncTransfers.Size = 0;

    Rec->HcProtocol.Reset = AmiUsbHcReset;
    Rec->HcProtocol.GetState = AmiUsbHcGetState;
    Rec->HcProtocol.SetState = AmiUsbHcSetState;
    Rec->HcProtocol.ControlTransfer = AmiUsbHcControlTransfer;
    Rec->HcProtocol.BulkTransfer = AmiUsbHcBulkTransfer;
    Rec->HcProtocol.AsyncInterruptTransfer = AmiUsbHcAsyncInterruptTransfer;
    Rec->HcProtocol.SyncInterruptTransfer = AmiUsbHcSyncInterruptTransfer;
    Rec->HcProtocol.IsochronousTransfer = AmiUsbHcIsochronousTransfer;
    Rec->HcProtocol.AsyncIsochronousTransfer = AmiUsbHcAsyncIsochronousTransfer;
    Rec->HcProtocol.GetRootHubPortNumber = AmiUsbHcGetRootHubPortNumber;
    Rec->HcProtocol.GetRootHubPortStatus = AmiUsbHcGetRootHubPortStatus;
    Rec->HcProtocol.SetRootHubPortFeature = AmiUsbHcSetRootHubPortFeature;
    Rec->HcProtocol.ClearRootHubPortFeature = AmiUsbHcClearRootHubPortFeature;

    //
    // Fill USB Revision fields based on type of HC
    //
    // USB_HC_UHCI USB_HC_OHCI -> 1.1
    // USB_HC_EHCI   -> 2.0
    // USB_HC_XHCI xHCI Supported Protocol Capability

    switch (HcStruc->HcType) {
        case USB_HC_UHCI:
        case USB_HC_OHCI:
            Rec->HcProtocol.MajorRevision = 1;
            Rec->HcProtocol.MinorRevision = 1;
            break;
        case USB_HC_EHCI:
            Rec->HcProtocol.MajorRevision = 2;
            Rec->HcProtocol.MinorRevision = 0;
            break;
        case USB_HC_XHCI:
            Rec->HcProtocol.MajorRevision = 3;
            Rec->HcProtocol.MinorRevision = 0;
            Usb3Hc = (USB3_HOST_CONTROLLER*)HcStruc->Usb3HcData;
            ExtendedCapOffset = (UINT16)Usb3Hc->CapRegs.HccParams1.Xecp;
            
            ExtendedCapOffset = (UINT16)LShiftU64(ExtendedCapOffset, 2);
            // Traverse Supported capability structures
            for (;;) {
                Status = PciIo->Mem.Read (PciIo, EfiPciIoWidthUint32, 0, ExtendedCapOffset, 1, XhciExtCap);
                if (EFI_ERROR (Status)) {
                   USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HC, "Xhci HC: Extended Capability error: %r at %x\n", Status, ExtendedCapOffset);
                   break;
                }
                if (XhciExtCap->CapId == XHCI_EXT_CAP_SUPPORTED_PROTOCOL) {
                    if (((XHCI_EXT_PROTOCOL*)XhciExtCap)->Field.MajorRev == XHCI_EXT_PROTOCOL_MAJOR_REV_03) {
                        Rec->HcProtocol.MinorRevision = (UINT16)(((XHCI_EXT_PROTOCOL*)XhciExtCap)->Field.MinorRev);
                        break;
                    }
                }
                if (XhciExtCap->NextCapPtr == 0) {
                    break;
                }
                // Point to next capability
                ExtendedCapOffset += (UINT16)LShiftU64(XhciExtCap->NextCapPtr, 2);
            }
            break;
        default:
            break;
    }

    Rec->HcProtocol2.GetCapability = AmiUsb2HcGetCapability;
    Rec->HcProtocol2.Reset = AmiUsb2HcReset;
    Rec->HcProtocol2.GetState = AmiUsb2HcGetState;
    Rec->HcProtocol2.SetState = AmiUsb2HcSetState;
    Rec->HcProtocol2.ControlTransfer = AmiUsb2HcControlTransfer;
    Rec->HcProtocol2.BulkTransfer = AmiUsb2HcBulkTransfer;
    Rec->HcProtocol2.AsyncInterruptTransfer = AmiUsb2HcAsyncInterruptTransfer;
    Rec->HcProtocol2.SyncInterruptTransfer = AmiUsb2HcSyncInterruptTransfer;
    Rec->HcProtocol2.IsochronousTransfer = AmiUsb2HcIsochronousTransfer;
    Rec->HcProtocol2.AsyncIsochronousTransfer = AmiUsb2HcAsyncIsochronousTransfer;
    Rec->HcProtocol2.GetRootHubPortStatus = AmiUsb2HcGetRootHubPortStatus;
    Rec->HcProtocol2.SetRootHubPortFeature = AmiUsb2HcSetRootHubPortFeature;
    Rec->HcProtocol2.ClearRootHubPortFeature = AmiUsb2HcClearRootHubPortFeature;
    Rec->HcProtocol2.MajorRevision = Rec->HcProtocol.MajorRevision;
    Rec->HcProtocol2.MinorRevision = Rec->HcProtocol.MinorRevision;


    //
    // Instal USB_HC_PROTOCOL
    //
    gBS->InstallProtocolInterface(
           &Controller,
           &gEfiUsbHcProtocolGuid, 
           EFI_NATIVE_INTERFACE, 
           &Rec->HcProtocol
           );
    gBS->InstallProtocolInterface(
           &Controller,
           &gEfiUsb2HcProtocolGuid, 
           EFI_NATIVE_INTERFACE, 
           &Rec->HcProtocol2
           );

    return EFI_SUCCESS;
}



/**
    This function allocates memory for EHCI iTD list.
    
    @param  Handle  Handle number of HC
    @param  HCStruc Pointer to the HC information structure

    @retval EFI_SUCCESS Success to pre-initial EHCI
**/

EFI_STATUS PreInitEhci(
    EFI_HANDLE  Handle,
    HC_STRUC    *HcStruc
)
{
    VOID                    **IsocTdsDataPtr = NULL;
    EHCI_ITD_DATA           *IsocTdsData = NULL;
    UINTN                   Index;
    EFI_PCI_IO_PROTOCOL     *PciIo = HcStruc->PciIo;
    UINT64                  MappedBaseAddr = 0;
    VOID                    *MapedAddress = NULL;
    UINTN                   TempMemSize;
    UINTN                   TotalMemSize;
    EFI_STATUS              Status;
    VOID                    *TempAddress = NULL;
    VOID                    *IsocTdsHostAddr;

    if (((gUsbData->UsbFeature & USB_HC_EHCI_SUPPORT) == USB_HC_EHCI_SUPPORT) &&
        ((gUsbData->UsbStateFlag & USB_FLAG_USB_ISOCTRANSFER_SUPPORT) == USB_FLAG_USB_ISOCTRANSFER_SUPPORT)){
        if (HcStruc->IsocTds == NULL) {

            if (gUsbDataList->IsocTdsData == NULL) {
                USB_DEBUG(DEBUG_DEV_INIT, "EFI_OUT_OF_RESOURCES gUsbDataList->IsocTdsData %x\n", gUsbDataList->IsocTdsData);
                return EFI_UNSUPPORTED;
            }

            IsocTdsDataPtr = (VOID**)(gUsbDataList->IsocTdsData);
            USB_DEBUG(DEBUG_DEV_INIT, "IsocTdsDataPtr %x \n", IsocTdsDataPtr);
            for (Index = 0; Index < gUsbDataList->IsocTdsDataCount; Index++) {
                IsocTdsData = IsocTdsDataPtr[Index];
                if (IsocTdsData == NULL) continue;
                if ((HcStruc->Vid == IsocTdsData->Vid) && (HcStruc->Did == IsocTdsData->Did) && (HcStruc->Controller == IsocTdsData->Controller)) {
                    break;
                }
                IsocTdsData = NULL;
            }
            if (IsocTdsData == NULL) {
                return EFI_UNSUPPORTED;
            }
            HcStruc->IsocTds = (VOID*)(UINTN)IsocTdsData->IsocTds;
            if (gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON) {
                TempMemSize = EFI_PAGES_TO_SIZE(EFI_SIZE_TO_PAGES(EHCI_FRAMELISTSIZE * sizeof(EHCI_ITD)));
                if ((gUsbData->UsbStateFlag & USB_FLAG_ITD_MEM_ALLOC_FOR_ALL_EHCI) == USB_FLAG_ITD_MEM_ALLOC_FOR_ALL_EHCI) {
                    HcStruc->FrameList = (UINT32*)((UINTN)IsocTdsData->IsocTds - USB_EHCI_FRAME_LIST_SIZE);
                    USB_DEBUG(DEBUG_DEV_INIT, "HcStruc->FrameList %x \n", HcStruc->FrameList);
                    TotalMemSize = TempMemSize + USB_EHCI_FRAME_LIST_SIZE;
                    TempAddress = (VOID *)HcStruc->FrameList;
                } else {
                    TempAddress = (VOID *)IsocTdsData->IsocTds;
                    TotalMemSize = TempMemSize;
                }
                Status = PciIo->Map(
                                  PciIo,
                                  EfiPciIoOperationBusMasterCommonBuffer,
                                  (VOID *)TempAddress,
                                  &TotalMemSize,
                                  (EFI_PHYSICAL_ADDRESS *)&MappedBaseAddr,
                                  &MapedAddress
                                  );
                if (!EFI_ERROR (Status)) {
                    if ((gUsbData->UsbStateFlag & USB_FLAG_ITD_MEM_ALLOC_FOR_ALL_EHCI) == USB_FLAG_ITD_MEM_ALLOC_FOR_ALL_EHCI) {
                        HcStruc->IsocTds = (VOID*)((UINTN)MappedBaseAddr + USB_EHCI_FRAME_LIST_SIZE);
                        HcStruc->FrameListPhyAddr = (VOID*)(UINTN)MappedBaseAddr;
                        HcStruc->FrameListMapping = MapedAddress;
                        USB_DEBUG(DEBUG_DEV_INIT, "HcStruc->FrameListPhyAddr %x HcStruc->FrameListMapping %x \n", MappedBaseAddr, MapedAddress);
                    } else {
                        HcStruc->IsocTds = (VOID*)(UINTN)MappedBaseAddr;
                    }
                } else {
                    HcStruc->FrameListPhyAddr = HcStruc->FrameList;
                    HcStruc->FrameListMapping = NULL;
                }
            }
        }
        if((gUsbData->UsbStateFlag & USB_FLAG_EDKII_IOMMU_PROTOCOL_ON) && (HcStruc->FrameListMapping != NULL)){
            IsocTdsHostAddr = (VOID*)((UINTN)HcStruc->IsocTds + (UINTN)HcStruc->FrameList - (UINTN)HcStruc->FrameListPhyAddr); //UnMap
            SetMem(IsocTdsHostAddr, EHCI_FRAMELISTSIZE * sizeof(EHCI_ITD), 0);
        } else {
            SetMem(HcStruc->IsocTds, EHCI_FRAMELISTSIZE * sizeof(EHCI_ITD), 0);
        }

        USB_DEBUG(DEBUG_DEV_INIT, "PreInitEhci: ITD buffer address: %x\n", (UINTN)HcStruc->IsocTds);
    }

    return EFI_SUCCESS;
}

/**

    This function frees the memory previously allocated for iTDs.
   
    @param  Handle  Handle number of HC
    @param  HCStruc Pointer to the HC information structure

    @retval EFI_SUCCESS Success to stop EHCI
**/

EFI_STATUS PostStopEhci(
    EFI_HANDLE  Handle,
    HC_STRUC    *HcStruc
)
{
    return EFI_SUCCESS;
}


/**
    This function initializes XHCI data structures, allocates HC memory and
    updates the relevant fields in HcStruc. At this point the controller's
    resources are assigned and accessible.

    @param  Handle  Handle number of HC
    @param  HCStruc Pointer to the HC information structure

    @retval EFI_SUCCESS Success to pre-init xhci

**/

EFI_STATUS
PreInitXhci(
    EFI_HANDLE  Handle,
    HC_STRUC    *HcStruc
)
{
    UINT8   MaxSlots;
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL     *PciIo = HcStruc->PciIo;
    USB3_HOST_CONTROLLER    **Usb3HcMem = NULL;
    USB3_HOST_CONTROLLER    *Usb3Hc = NULL;
    UINTN                   Index;
    if ((gUsbData->UsbFeature & USB_HC_XHCI_SUPPORT) == 0) return EFI_UNSUPPORTED;

    if (HcStruc->Usb3HcData == NULL) {
        if (gUsbDataList == NULL) {
           return EFI_UNSUPPORTED;
        }
        if (gUsbDataList->Usb3HcMem == NULL) {
            USB_DEBUG(DEBUG_DEV_INIT, "EFI_OUT_OF_RESOURCES gUsbDataList->Usb3HcMem %x\n", gUsbDataList->Usb3HcMem);
            return EFI_UNSUPPORTED;
        }
        Usb3HcMem = (USB3_HOST_CONTROLLER**)(gUsbDataList->Usb3HcMem);
        for (Index = 0; Index < gUsbDataList->Usb3HcCount; Index++) {
            Usb3Hc = Usb3HcMem[Index];
            if (Usb3Hc == NULL) continue;
            if ((HcStruc->Vid == Usb3Hc->Vid) && (HcStruc->Did == Usb3Hc->Did) && (HcStruc->Controller == Usb3Hc->Controller)) {
                break;
            }
            Usb3Hc = NULL;
        }
    } else {
        Usb3Hc = HcStruc->Usb3HcData;
    }

    if (Usb3Hc == NULL) {
        return EFI_UNSUPPORTED;
    }
    Usb3Hc->Controller = Handle;

    // Get Capability Registers offset off the BAR
                                        //(EIP101226)>
    Status = PciIo->Pci.Read (
                      PciIo, 
                      EfiPciIoWidthUint32, 
                      PCI_BASE_ADDRESSREG_OFFSET, 
                      1, 
                      &HcStruc->BaseAddress
                      );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    if (((UINT8)HcStruc->BaseAddress & (BIT1 |BIT2)) == BIT2) {
        Status = PciIo->Pci.Read(
                          PciIo, 
                          EfiPciIoWidthUint32, 
                          PCI_BASE_ADDRESSREG_OFFSET, 
                          (sizeof(VOID*)/sizeof(UINT32)), 
                          &HcStruc->BaseAddress
                          );
        if (EFI_ERROR (Status)) {
            return Status;
        }
    }

                                        //<(EIP101226)
    //clear all attributes before use
    HcStruc->BaseAddress &= ~(0x7F);

    HcStruc->OpRegOffset = Usb3Hc->CapRegs.CapLength;
    HcStruc->NumPorts = (UINT8)Usb3Hc->CapRegs.HcsParams1.MaxPorts;

    // OEM might change the default number of MaxSlots
    MaxSlots = (UINT8)Usb3Hc->CapRegs.HcsParams1.MaxSlots;
    Status = Usb3OemGetMaxDeviceSlots(HcStruc, &MaxSlots);

    if (!EFI_ERROR(Status)) {
        // Validate the porting function output
        ASSERT(MaxSlots > 0 && MaxSlots <= Usb3Hc->CapRegs.HcsParams1.MaxSlots);
        if (MaxSlots < Usb3Hc->CapRegs.HcsParams1.MaxSlots){
        Usb3Hc->CapRegs.HcsParams1.MaxSlots = MaxSlots;
        }
    }

    USB_DEBUG(DEBUG_DEV_INIT, "XHCI: MaxSlots %x, MaxIntrs %x, Doorbell Offset %x\n", 
            Usb3Hc->CapRegs.HcsParams1.MaxSlots, 
            Usb3Hc->CapRegs.HcsParams1.MaxIntrs,
            Usb3Hc->CapRegs.DbOff);
    HcStruc->Usb3HcData = (VOID*)Usb3Hc;
    
    return EFI_SUCCESS;
}

/**
    This function frees the HC memory and clears XHCI data structures.
    @param  Handle  Handle number of HC
    @param  HCStruc Pointer to the HC information structure

    @retval EFI_SUCCESS Success to stop xhci
**/

EFI_STATUS
PostStopXhci(
    EFI_HANDLE  Handle,
    HC_STRUC    *HcStruc
)
{
    return EFI_SUCCESS;
}


/**
    This function check whether the Programming Interface Type is supported.

    @param InterfaceType   Pci Programming Interface

    @retval TRUE           Support PI match
    @retval FALSE          Support PI not match
**/

BOOLEAN
IsSupportedInterfaceType (
    UINT8    InterfaceType
)
{
    if ((gUsbData->UsbFeature & USB_HC_UHCI_SUPPORT) == USB_HC_UHCI_SUPPORT){
        if(InterfaceType == PCI_CLASSC_PI_UHCI) return TRUE;
    }
    if ((gUsbData->UsbFeature & USB_HC_OHCI_SUPPORT) == USB_HC_OHCI_SUPPORT){
        if(InterfaceType == PCI_CLASSC_PI_OHCI) return TRUE;
    }
    if ((gUsbData->UsbFeature & USB_HC_EHCI_SUPPORT) == USB_HC_EHCI_SUPPORT){
        if(InterfaceType == PCI_CLASSC_PI_EHCI) return TRUE;
    }
    if ((gUsbData->UsbFeature & USB_HC_XHCI_SUPPORT) == USB_HC_XHCI_SUPPORT){
        if(InterfaceType == PCI_CLASSC_PI_XHCI) return TRUE;
    }
    return FALSE;
}

/**
    Return a buffer of handle that contain PciIo protocols, and whose class/subclass
    match the passed class/subclasses.

    @param Class The class of PCI devices to search
    @param SubClass The subclass of PCI devices to search
    @param NumberOfHandles Pointer to the buffer of the number of Handles being returned
    @param HandleBuffer Double pointer used to return a buffer of PCI handles that match

    @retval EFI_NOT_FOUND No Handles were found that match the search criteria
    @retval EFI_SUCCESS The HandlerBuffer and NumberOfHandles being returned are valid

**/
EFI_STATUS
EFIAPI
GetPciHandleByClassHc (
    IN     UINT8       Class,
    IN     UINT8       SubClass,
    IN     UINTN       *NumberOfHandles,
    IN OUT EFI_HANDLE  **HandleBuffer
    )
{
    EFI_STATUS           Status;
    EFI_HANDLE           *Handle;
    UINTN                Number;
    UINTN                Index;
    EFI_PCI_IO_PROTOCOL  *PciIo = NULL;
    USB_CLASSC           UsbClassCReg;
    
    if (!NumberOfHandles || !HandleBuffer) return EFI_INVALID_PARAMETER;
    //Get a list of all PCI devices
    Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiPciIoProtocolGuid, NULL, &Number, &Handle);
    if (EFI_ERROR (Status)) return Status;
    *NumberOfHandles = 0;
    for (Index=0; Index  <Number; Index++) {
        Status=gBS->HandleProtocol (Handle[Index], &gEfiPciIoProtocolGuid, (VOID**)&PciIo);
        if (EFI_ERROR (Status)) continue;
        
        Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          CLASSC,
                          sizeof(USB_CLASSC) / sizeof(UINT8),
                          &UsbClassCReg);
        
        if ((UsbClassCReg.BaseCode != PCI_CLASSC_BASE_CLASS_SERIAL) || 
            (UsbClassCReg.SubClassCode != PCI_CLASSC_SUBCLASS_SERIAL_USB) ||
            !IsSupportedInterfaceType(UsbClassCReg.PI) || EFI_ERROR (Status) ) {
            continue;
        }else{
            Handle[(*NumberOfHandles)++] = Handle[Index];
        }
    }
    if (*NumberOfHandles == 0) {
        gBS->FreePool(Handle);
        return EFI_NOT_FOUND;
    }
    *HandleBuffer = Handle;
    return EFI_SUCCESS;
}


//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
