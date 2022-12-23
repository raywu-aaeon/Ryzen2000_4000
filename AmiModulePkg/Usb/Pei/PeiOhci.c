//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file PeiOhci.c
    This file is the main source file for the OHCI PEI USB
    recovery module.  Its entry point at OhciPeiUsbEntryPoint
    will be executed from the UsbRecoveryInitialize INIT_LIST.

**/

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#include <Ppi/Stall.h>
#include "UsbPei.h"
#include "PeiOhci.h"

// List of PCI addresses for OHCI controllers
extern PCI_BUS_DEV_FUNCTION  *gOhciControllerPciTable;

// List of OHCI PCI register table
extern PCI_DEV_REGISTER_VALUE  *gOhciPciRegisterTable;


extern EFI_STATUS OhciPeiBoardInit (
    IN EFI_PEI_SERVICES **PeiServices,
    EFI_PEI_PCI_CFG2_PPI *PciCfgPpi,
    EFI_PEI_STALL_PPI   *StallPpi );

extern USB_PEI_GLOBAL_DATA    *gUsbPeiData;
extern EFI_PEI_STALL_PPI *gUsbPeiStall;
/**
    This function uses ControllerIndex and the global PCI_BUS_DEV_FUNCTION
    array to access a particular controller's PCI configuration space in 
    order to obtain the Operational Register base address.

        
    @param PeiServices 
        --  PEI Sevices table pointer
    @param ControllerIndex 
        --  Index of the controller in the global
        PCI_BUS_DEV_FUNCTION array

    @retval 
        UINT32 (Return Value)
        = Base address for this controller's operational
        registers.

**/

UINT32 OhciGetOperationalRegisterBase (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN UINT16               ControllerIndex )
{
    UINT32 OhciBaseAddress;

    (*PeiServices)->PciCfg->Read(
                      (CONST EFI_PEI_SERVICES**)PeiServices,
                      (*PeiServices)->PciCfg,
                      EfiPeiPciCfgWidthUint32,
                      OHCI_PCI_ADDRESS(ControllerIndex, OHCI_BASE_ADDR_REG),
                      &OhciBaseAddress
                      );


    return OhciBaseAddress &= 0xfffffff0;    // Mask lower bits
}


/**
    This is the entry point into the OHCI controller initialization
    subsystem.

        
    @param FfsHeader 
        --  EFI_FFS_FILE_HEADER pointer
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS OhciPeiUsbEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    UINT8                Index;
    UINTN                MemPages;
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    PEI_OHCI_DEV         *OhciDevPtr;
    UINT8                ClassCode[4];

    if ((gUsbPeiData->UsbPeiFeature & USB_OHCI_PEI_SUPPORT) != USB_OHCI_PEI_SUPPORT)
        return EFI_UNSUPPORTED;

    gOhciControllerPciTable = gUsbPeiData->OhciPciDev;
    gOhciPciRegisterTable = gUsbPeiData->OhciRegTbl;
    
    //-------------------------------------------
    // Initialize the EFI_PEI_STALL_PPI interface
    //-------------------------------------------
    if (gUsbPeiStall==NULL){
        return EFI_UNSUPPORTED;
    }

    //-----------------------------------------
    // board specific initialization to program
    // PCI bridges and enable MMIO
    //-----------------------------------------

    Status = OhciPeiBoardInit(
               PeiServices,
               (*PeiServices)->PciCfg,
               gUsbPeiStall
               );
    
    if ( EFI_ERROR( Status ) ) {
        return EFI_UNSUPPORTED;
    }

    //----------------------------------------------------------
    // Allocate OHCI DEVICE OBJECT that holds all necessary
    // information for the Host Controller operational registers
    // for each controller.  Initialze the controller and setup
    // data structures for ready for operation
    //----------------------------------------------------------

    for (Index = 0; Index < gUsbPeiData->OhciHcCount; Index++) {

        (*PeiServices)->PciCfg->Read(
                          (CONST EFI_PEI_SERVICES**)PeiServices,
                          (*PeiServices)->PciCfg,
                          EfiPeiPciCfgWidthUint32, 
                          OHCI_PCI_ADDRESS(Index, PCI_REG_REVID), 
                          ClassCode
                          );
        
        DEBUG((DEBUG_INFO, "USB OHCI#%d PI %x SubClassCode %x BaseCode %x\n", 
            Index, ClassCode[1], ClassCode[2], ClassCode[3]));

        if ((ClassCode[1] != PCI_CLASSC_PI_OHCI) || 
            (ClassCode[2] != PCI_CLASSC_SUBCLASS_SERIAL_USB) ||
            (ClassCode[3] != PCI_CLASSC_BASE_CLASS_SERIAL)) {
            continue;   //This is not an ohci controller.
        }

        // PAGESIZE = 0x1000
        MemPages = sizeof (PEI_OHCI_DEV) / 0x1000 + 1;

        Status = PeiServicesAllocatePages(
                     EfiBootServicesData,
                     MemPages,
                     &TempPtr
                     );
        if ( EFI_ERROR( Status ) ) {
            return EFI_OUT_OF_RESOURCES;
        }

        OhciDevPtr = (PEI_OHCI_DEV *) ( (UINTN) TempPtr );
        OhciDevPtr->Signature = PEI_OHCI_DEV_SIGNATURE;
        OhciDevPtr->PeiServices = PeiServices;
        OhciDevPtr->CpuIoPpi = (*PeiServices)->CpuIo;
        OhciDevPtr->PciCfgPpi = (*PeiServices)->PciCfg;

        OhciDevPtr->UsbHostControllerBaseAddress =
            OhciGetOperationalRegisterBase( PeiServices, Index );

        //Initialize the OHCI Controller for operation

        OhciInitHC( PeiServices, OhciDevPtr, Index );  // 0xff03

        //Setup PPI entry point
        OhciDevPtr->UsbHostControllerPpi.ControlTransfer =
            OhciHcControlTransfer;
        OhciDevPtr->UsbHostControllerPpi.BulkTransfer =
            OhciHcBulkTransfer;
        OhciDevPtr->UsbHostControllerPpi.SyncInterruptTransfer =
            OhciHcSyncInterruptTransfer;
        OhciDevPtr->UsbHostControllerPpi.GetRootHubPortNumber =
            OhciHcGetRootHubPortNumber;
        OhciDevPtr->UsbHostControllerPpi.GetRootHubPortStatus =
            OhciHcGetRootHubPortStatus;
        OhciDevPtr->UsbHostControllerPpi.SetRootHubPortFeature =
            OhciHcSetRootHubPortFeature;
        OhciDevPtr->UsbHostControllerPpi.ClearRootHubPortFeature =
            OhciHcClearRootHubPortFeature;
        OhciDevPtr->UsbHostControllerPpi.PreConfigureDevice = NULL;
        OhciDevPtr->UsbHostControllerPpi.EnableEndpoints = NULL;
        OhciDevPtr->UsbHostControllerPpi.ActivatePolling = OhciHcActivatePolling;
        OhciDevPtr->UsbHostControllerPpi.Reset = OhciHcReset;
        OhciDevPtr->UsbHostControllerPpi.CurrentAddress = 0;

        OhciDevPtr->PpiDescriptor.Flags =
            (EFI_PEI_PPI_DESCRIPTOR_PPI |
             EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
        OhciDevPtr->PpiDescriptor.Guid = &gAmiPeiUsbHostControllerPpiGuid;
        OhciDevPtr->PpiDescriptor.Ppi = &OhciDevPtr->UsbHostControllerPpi;
        OhciDevPtr->ControllerIndex = Index;

        //Now is the time to install the PPI
        Status = PeiServicesInstallPpi (&OhciDevPtr->PpiDescriptor); 
        if (EFI_ERROR(Status)) {
            return EFI_NOT_FOUND;
        }

    }
    
    return EFI_SUCCESS;

}


/**
    This function starts the periodic schedule for the interrupt endpoint-based
    devices (keyboard).

**/

EFI_STATUS
EFIAPI
OhciHcActivatePolling(
    IN EFI_PEI_SERVICES **PeiServices,
    IN VOID *UsbDev
)
{
    PEI_USB_DEVICE  *PeiUsbDev = (PEI_USB_DEVICE*)UsbDev;
    PEI_OHCI_DEV    *OhciDev = PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS(PeiUsbDev->UsbHcPpi);

    EFI_STATUS  Status;
    UINT8       *Ptr;
    UINT16      WordData = 0;
    UINT32      DwordData;

    static UINT8 OhciPollingStarted = FALSE;

    if (OhciPollingStarted) return EFI_ALREADY_STARTED;
    OhciPollingStarted = TRUE;

    // Allocate ED and TD, making allocation 64-Bytes aligned
    Status = PeiServicesAllocatePool(
               sizeof(OHCI_ED)+sizeof(OHCI_TD)+64, 
               (VOID**)&Ptr 
               );
    ASSERT(Status == EFI_SUCCESS);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 64-Bytes alignment, assume no deallocation will be necessary,
    // because the original pointer is lost here
    Ptr = (UINT8*)((UINTN)Ptr + 0x40);
    Ptr = (UINT8*)((UINTN)Ptr & ~0x3f);
    OhciDev->OHCIDescPtrs.PstEDInterrupt = (POHCI_ED)Ptr;
    OhciDev->OHCIDescPtrs.PstTDInterruptData = (POHCI_TD)(Ptr + sizeof(OHCI_ED));

    DwordData = (UINT32)PeiUsbDev->IntMaxPkt;
    DwordData <<= 16;                   // DwordData[26:16] = device's packet size
    switch (PeiUsbDev->DeviceSpeed) {
        case USB_SLOW_SPEED_DEVICE: WordData = 1; break;
        case USB_FULL_SPEED_DEVICE: WordData = 2; break;
        default:
             ASSERT(FALSE); // Invalid device speed
    }
    WordData = (WordData & 1) << 13;      // WordData[13] = full/low speed flag
    DwordData |= (ED_SKIP_TDQ | ED_IN_PACKET |(DEFAULT_PACKET_LENGTH  << 16));
    OhciDev->OHCIDescPtrs.PstEDInterrupt->Control = DwordData | WordData;

    // Update the endpoint characteristcs field
    DwordData = ((UINT32)PeiUsbDev->DeviceAddress)  |
                    ((UINT32)PeiUsbDev->IntEndpoint << 7);

    OhciDev->OHCIDescPtrs.PstEDInterrupt->Control |= DwordData;
    OhciDev->OHCIDescPtrs.PstEDInterrupt->HeadPointer =
        OhciDev->OHCIDescPtrs.PstTDInterruptData;
    OhciDev->OHCIDescPtrs.PstEDInterrupt->EDLinkPointer = OHCI_TERMINATE;
    OhciDev->OHCIDescPtrs.PstEDInterrupt->TailPointer = OHCI_TERMINATE;

    OhciDev->OHCIDescPtrs.PstTDInterruptData->ControlStatus =
                (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_INTD |
                GTD_NO_ERRORS | GTD_NOT_ACCESSED_32);
    OhciDev->OHCIDescPtrs.PstTDInterruptData->CSReloadValue =
                (UINT32)(GTD_BUFFER_ROUNDING | GTD_IN_PACKET | GTD_INTD |
                GTD_NO_ERRORS | GTD_NOT_ACCESSED_32);
    OhciDev->OHCIDescPtrs.PstTDInterruptData->CurrentBufferPointer =
                (UINT8*)(UINTN)OhciDev->OHCIDescPtrs.PstTDInterruptData->SetupData;
    OhciDev->OHCIDescPtrs.PstTDInterruptData->BufferEnd =
                (UINT8*)(UINTN)OhciDev->OHCIDescPtrs.PstTDInterruptData->SetupData + 7;
    OhciDev->OHCIDescPtrs.PstTDInterruptData->LinkPointer = OHCI_TERMINATE;
    OhciDev->OHCIDescPtrs.PstTDInterruptData->ActiveFlag = TRUE;

    OhciScheduleED(
        OhciDev,
        OhciDev->OHCIDescPtrs.PstEDInterrupt,
        OhciDev->OHCIDescPtrs.PstED8ms
        );

    OhciDev->OHCIDescPtrs.PstEDInterrupt->Control &= ~ED_SKIP_TDQ;

    return EFI_SUCCESS;
}


/**
    This function adds an ED to the frame list.

    @param 
        pED  - Pointer to the ED to be added
        pPtr - Pointer to the frame list

**/

VOID
OhciAddED(
    POHCI_ED    pED,
    UINTN       *pPtr
)
{
    UINTN CurrentED = *pPtr;
    *pPtr = (UINTN)pED;
    pED->EDLinkPointer = (POHCI_ED)(UINTN)CurrentED;
}


/**
    This routine allocates memory for the the Host Controller 
    Communications Area (HCCA), aligned on a 256 byte boundary,
    and updates the HcHcca operational register pointer, as
    well as the corresponding PEI_OHCI_DEV.pFrameList
    pointer.

            
    @param OhciDevPtr 
        --  This is a pointer to a PEI_OHCI_DEV structure
        for an OHCI controller.

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
OhciInitHcca (
    IN PEI_OHCI_DEV *OhciDevPtr
)
{
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;
    POHCI_DESC_PTRS      PstOHCIDescPtrs = &(OhciDevPtr->OHCIDescPtrs);

    UINT16  Index;
    UINT8   *Ptr;
    EFI_STATUS Status;


    // Allocate 256 byte aligned Communication Channel area
    // to the PEI_OHCI_DEV.pFrameList pointer.
    Status = PeiServicesAllocatePages(
                 EfiBootServicesData,
                 (UINTN) (256 / 0x1000) + 1,
                 (EFI_PHYSICAL_ADDRESS *) &OhciDevPtr->FrameList
                 ); 
    ASSERT(Status == EFI_SUCCESS);
    // Zero the memory and update the HcHCCA Host Controller
    // Operational Register.
    (*OhciDevPtr->PeiServices)->SetMem(OhciDevPtr->FrameList, sizeof(HC_HCCA), 0);

    // The TD schedule should be added in proper order otherwise the
    // links will get garbled. The proper order is to add all the 1ms TDs,
    // followed by 2ms, 8ms and finally 32ms TD.
    //
    for (Index = 0; Index < OhciDevPtr->AsyncListSize; Index++) {
        Ptr = (UINT8*) &OhciDevPtr->FrameList[Index];

        PstOHCIDescPtrs->PstED1ms->Control |= ED_SKIP_TDQ;           // Skip this ED
        OhciAddED(PstOHCIDescPtrs->PstED1ms, (UINTN*)Ptr);          // Schedule 1ms ED
        if (!(Index % 2)) {
            PstOHCIDescPtrs->PstED2ms->Control |= ED_SKIP_TDQ;
            OhciAddED (PstOHCIDescPtrs->PstED2ms, (UINTN*)Ptr);      // Schedule 2ms ED
        }
        if (!(Index % 8)) {
            PstOHCIDescPtrs->PstED8ms->Control |= ED_SKIP_TDQ;
            OhciAddED (PstOHCIDescPtrs->PstED8ms, (UINTN*)Ptr);      // Schedule 8ms ED
        }
        if (!(Index % 32)) {
            PstOHCIDescPtrs->PstED32ms->Control |= ED_SKIP_TDQ;
            OhciAddED (PstOHCIDescPtrs->PstED32ms, (UINTN*)Ptr);    // Schedule 32ms TD
        }
    }

    OhciHcReg->HcHcca = (HC_HCCA*) OhciDevPtr->FrameList;
    
    return EFI_SUCCESS;
}


/**
    This function adds the ED provided to the particular ED schedule

    @param 
        OhciDev - PEI_OHCI_DEV* structure
        pX - TD/QH to be scheduled (X)
        pY - TD pointer where the new TD/QH (Y) has to be scheduled

    @note  
  This routine adds a new ED (called 'X') to the 'Y' ED. This is accomplished
  by moving the next field in 'Y' (called 'Z') to the next field of 'X' and
  storing address of 'X' into next field of 'Y'.

**/

VOID
OhciScheduleED(
    PEI_OHCI_DEV* OhciDev,
    POHCI_ED    pX,
    POHCI_ED    pY
)
{
    POHCI_ED pED;

    pED = (POHCI_ED)(UINTN)pY->EDLinkPointer;   // Get the Z ED pointer from Y ED
    pY->EDLinkPointer = (POHCI_ED)(UINTN)pX;      // Store the address of X ED address into next field of Y ED
    pX->EDLinkPointer = (POHCI_ED)(UINTN)pED;

}


/**
    OHCI Host Controller initialization.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param OhciDevPtr 
        --  PEI_OHCI_DEV pointer
    @param Index 
        --  Index of this controller in the global 
        PCI_BUS_DEV_FUNCTION array

    @retval 
        VOID (Return Value)

**/

VOID OhciInitHC (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_OHCI_DEV     *OhciDevPtr,
    IN UINT8            Index )
{
    UINT8      PortNum;
    UINT8      *Ptr;
    UINTN      MemPages;
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    POHCI_DESC_PTRS      PstOHCIDescPtrs;
    OHCI_HC_REGISTERS    *OhciHcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;

    OhciDevPtr->AsyncListSize = OHCI_FRAME_LIST_SIZE;
    OhciDevPtr->MaxBulkDataSize = MAX_OHCI_BULK_DATA_SIZE;
    //OhciDevPtr->Endp0MaxPacket = 0x40;
    //OhciDevPtr->EndpointSpeed = USBSPEED_FULL;


    // Do a Host Controller reset first
    OhciReset( PeiServices, OhciDevPtr );


    //-----------------------------------------------------------------
    // Allocate and initialize the Host Controller Communication
    // area aligned on a 256 byte boundary.
    //
    // This is needed only to poll the HccaDoneHead register
    // in the HCCA, as the periodic list is not implemented.
    //-----------------------------------------------------------------

    // Store number of downstream ports into PEI_OHCI_DEV struct
    OhciDevPtr->NumPorts =
        (UINT8)(OhciHcReg->HcRhDescriptorA.HcRhDescriptorAUnion.Field.NumberDownstreamPorts);

    // Program root hub characteristics:
    OhciHcReg->HcRhDescriptorA.HcRhDescriptorAUnion.AllBits = 
        (NO_OVERCURRENT_PROTECTION |    // No over current protection
        POWERED_INDIVIDUALLY |          // Ports powered individually
        POWER_SWITCHED);                // Ports individually power switched
    OhciHcReg->HcRhDescriptorB.HcRhDescriptorBUnion.AllBits =
        (ALL_REMOVEABLE |               // All devices are removbale
        ALL_PER_PORT_POWER_SWITCHED);   // Power control is per-port
    
    OhciHcReg->HcRhStatus.HcRhStatusUnion.Field.LocalPowerStatusChange = 
        SET_GLOBAL_POWER;               // Turn on power to all ports
        
    // Initialize the frame interval register
    OhciHcReg->HcFmInterval.HcFmIntervalUnion.Field.FrameInterval = 
        FM_INTERVAL_DEFAULT;            // Between Start of Frames (SOFs)
    OhciHcReg->HcFmInterval.HcFmIntervalUnion.Field.FsLargestDataPacket = 
        FS_LARGEST_PACKET_DEFAULT;      // Largest for single transaction

    // Enable the host controller list processing
    OhciHcReg->HcControl.HcControlUnion.Field.BulkListEnable = 1;
    OhciHcReg->HcControl.HcControlUnion.Field.ControlListEnable = 1;
    OhciHcReg->HcControl.HcControlUnion.Field.PeriodicListEnable = 1;

    // Allocate a block of memory and define/initialize 
    // Setup Control and Bulk EDs/TDs
    PstOHCIDescPtrs = &(OhciDevPtr->OHCIDescPtrs);

    MemPages = ( 7 *sizeof (OHCI_ED) ) + ( 6 * sizeof(OHCI_TD) ) / 0x1000 + 1;

    Status = PeiServicesAllocatePages(
                 EfiBootServicesData,
                 MemPages,
                 &TempPtr
                 );
    ASSERT(Status == EFI_SUCCESS);

    if (EFI_ERROR(Status)) {
        return;
    }
    Ptr = (UINT8 *) ( (UINTN) TempPtr );
    ZeroMem(Ptr, 7 * sizeof (OHCI_ED) + 6 * sizeof(OHCI_TD));
    if (!Ptr) {
        return;
    }
    PstOHCIDescPtrs->PstED1ms = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstED2ms = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstED8ms = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstED32ms = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstTD32ms = (POHCI_TD) Ptr;
    Ptr += sizeof (OHCI_TD);
    PstOHCIDescPtrs->PstEDControl = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstTDControlSetup = (POHCI_TD) Ptr;
    Ptr += sizeof (OHCI_TD);
    PstOHCIDescPtrs->PstTDControlData = (POHCI_TD) Ptr;
    Ptr += sizeof (OHCI_TD);
    PstOHCIDescPtrs->PstTDControlStatus = (POHCI_TD) Ptr;
    Ptr += sizeof (OHCI_TD);
    PstOHCIDescPtrs->PstEDBulk = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstTDBulkData = (POHCI_TD) Ptr;
    Ptr += sizeof (OHCI_TD);
    PstOHCIDescPtrs->PstEDInterrupt = (POHCI_ED) Ptr;
    Ptr += sizeof (OHCI_ED);
    PstOHCIDescPtrs->PstTDInterruptData = (POHCI_TD) Ptr;

    OhciInitHcca(OhciDevPtr);

    // Initialize EDInterrupt
    PstOHCIDescPtrs->PstEDInterrupt->Control = ED_SKIP_TDQ;  // Inactive
    OhciScheduleED(OhciDevPtr, PstOHCIDescPtrs->PstEDInterrupt, PstOHCIDescPtrs->PstED1ms);

    // Set the operational bit in the host controller so that power
    // can be applied to the ports.
    OhciHcReg->HcControl.HcControlUnion.Field.HostControllerFunctionalState = 
        SET_USB_OPERATIONAL;
        
    // Enable all the ports.
    for ( PortNum = 0; PortNum < OhciDevPtr->NumPorts; PortNum++ ) {
        OhciHcReg->HcRhPortStatus[PortNum].HcRhPortStatusUnion.AllBits = SET_PORT_POWER;
    }
}


/**
    This function performs a software reset of the host controller.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param OhciDevPtr 
        --  PEI_OHCI_DEV pointer

    @retval 
        VOID (Return Value)

    @note  
      It is assumed that all necessary operational register data has been 
      saved prior to calling this function.

**/

VOID OhciReset (
    EFI_PEI_SERVICES **PeiServices,
    PEI_OHCI_DEV     *OhciDevPtr )
{
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;

    // Initiate a software reset 
    OhciHcReg->HcCommandStatus.HcCommandStatusUnion.AllBits = SET_CONTROLLER_RESET;

    //Wait for 2ms
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 2);

    //Do USBRESET to reset roothub and downstream port
    OhciHcReg->HcControl.HcControlUnion.Field.HostControllerFunctionalState = SET_USB_RESET;

    //wait for 10ms
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 10);

    // Note:    HcInterruptStatus.Field.RootHubStatusChange bit should 
    //          now be set if any devices are connected to a port
    //          on this controller. 
    
    return;
}


/**
    This function obtains the port status and port change status for
    a port specified by PortNumber and updates the EFI_USB_PORT_STATUS 
    data structure as specified the the PortStatus pointer parameter.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param PortNumber 
        --  Port number for which status is requested
    @param PortStatus 
        --  EFI_USB_PORT_STATUS pointer's data is updated

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
EFIAPI
OhciHcGetRootHubPortStatus(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    OUT EFI_USB_PORT_STATUS        *PortStatus
)
{
    PEI_OHCI_DEV      *OhciDevPtr =
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    HC_RH_PORT_STATUS HcPortStatus;

    HcPortStatus = ( (OHCI_HC_REGISTERS *)(UINTN)
                    OhciDevPtr->UsbHostControllerBaseAddress )->
                       HcRhPortStatus[PortNumber - 1];

    PortStatus->PortStatus = 0;
    PortStatus->PortChangeStatus = 0;

    if (HcPortStatus.HcRhPortStatusUnion.Field.CurrentConnectStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_CONNECTION;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.PortEnableStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_ENABLE;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.PortSuspendStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_SUSPEND;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.PortResetStatus) {
        PortStatus->PortStatus |= USB_PORT_STAT_RESET;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.LowSpeedDeviceAttached) {
        PortStatus->PortStatus |= USB_PORT_STAT_LOW_SPEED;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.ConnectStatusChange) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.PortEnableStatusChange) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_ENABLE;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.PortResetStatusChange) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_RESET;
    }
    if (HcPortStatus.HcRhPortStatusUnion.Field.CurrentConnectStatus) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }

    return EFI_SUCCESS;

}


/**
    This function returns the number of downstream ports as specified 
    in the HcRhDescriptorA operational register.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param PortNumber 
        --  Number of downstream ports

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
EFIAPI
OhciHcGetRootHubPortNumber(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    OUT UINT8                      *PortNumber
)
{

    PEI_OHCI_DEV        *OhciDevPtr = PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;
        
    if (PortNumber == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    *PortNumber = (UINT8)(OhciHcReg->HcRhDescriptorA.HcRhDescriptorAUnion.Field.NumberDownstreamPorts);

    return EFI_SUCCESS;
}


/**
    This function sets an OHCI specification port feature as specified by
    PortFeature for the port specified by PortNumber.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param PortNumber 
        --  Port number whose feature is to be set
    @param PortFeature 
        --  Feature to set

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
EFIAPI
OhciHcSetRootHubPortFeature(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature
)
{
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS    *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;

    if (PortNumber > OhciHcReg->HcRhDescriptorA.HcRhDescriptorAUnion.Field.NumberDownstreamPorts){
        return EFI_INVALID_PARAMETER;
    }

    switch (PortFeature) {

        case EfiUsbPortSuspend:
             OhciHcReg->HcRhPortStatus[PortNumber - 1].HcRhPortStatusUnion.AllBits = SET_PORT_SUSPEND;
             break;

        case EfiUsbPortReset:
             OhciHcReg->HcRhPortStatus[PortNumber - 1].HcRhPortStatusUnion.AllBits = SET_PORT_RESET;
             break;

        case EfiUsbPortPower:
             break;

        case EfiUsbPortEnable:
             OhciHcReg->HcRhPortStatus[PortNumber - 1].HcRhPortStatusUnion.AllBits = SET_PORT_ENABLE;
             break;

        default:
             return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


/**
    This function clears an OHCI specification port feature as specified
    by PortFeature for the port specified by PortNumber.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param PortNumber 
        --  Port number whose feature is to be set
    @param PortFeature 
        --  Feature to set

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
EFIAPI
OhciHcClearRootHubPortFeature(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature
)
{
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;
    HC_RH_PORT_STATUS   *Pstatus;

    if (PortNumber > OhciHcReg->HcRhDescriptorA.HcRhDescriptorAUnion.Field.NumberDownstreamPorts){
        return EFI_INVALID_PARAMETER;
    }

    Pstatus = &OhciHcReg->HcRhPortStatus[PortNumber - 1];
    
    switch (PortFeature) {
        // clear PORT_ENABLE feature means disable port.
        // This is accomplished by writing a 1 to the CurrentConnectStatus
        // field.
        case EfiUsbPortEnable:
             Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_PORT_ENABLE;
             break;

        // clear PORT_SUSPEND feature means resume the port.
        // (cause a resume on the specified port if in suspend mode)
        // This is accomplished by writing a 1 to the PortOverCurrentIndicator
        // field.     
        case EfiUsbPortSuspend:
             Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_SUSPEND_STATUS;
             break;

        case EfiUsbPortPower:
             break;


        // clear PORT_RESET means clear the reset signal.
        // This is accomplished by writing a 1 to the PortResetStatusChange
        // field.  No assumption is made that the appropriate delay
        // was implemented.
        case EfiUsbPortReset:

             break;

        // clear connect status change by writing
        // a 1 to the ConnectStatusChange field
        case EfiUsbPortConnectChange:
             Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_CONNECT_STATUS_CHANGE;
             break;

        // clear enable/disable status change by writing
        // a 1 to the PortEnableStatusChange field
        case EfiUsbPortEnableChange:
             Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_PORT_ENABLE_STATUS_CHANGE;
             break;

        // root hub does not support these requests
        case EfiUsbPortSuspendChange:
        case EfiUsbPortOverCurrentChange:
        case EfiUsbPortResetChange:
             Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_PORT_RESET_STATUS_CHANGE;
             break;

        default:
             return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}


/**
    This routine resets the Host Controler 

    @param EFI_PEI_SERVICES             **PeiServices,
           PEI_USB_HOST_CONTROLLER_PPI  *This,
           UINT16                       Attributes         

    @retval 
        EFI_SUCCESS     Successfully reset controller.

**/

EFI_STATUS
EFIAPI
OhciHcReset(
     IN EFI_PEI_SERVICES             **PeiServices,
     IN PEI_USB_HOST_CONTROLLER_PPI  *This,
     IN UINT16                       Attributes
)
{
    PEI_OHCI_DEV               *OhciDev = 
                               PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS (This);
    volatile OHCI_HC_REGISTERS *OhciHcReg;
    UINT16                     RegisterIndex;
    UINT64                     Val64;
    EFI_PEI_PCI_CFG2_PPI       *Pci = (*PeiServices)->PciCfg;

    switch (Attributes) {
        case EFI_USB_HC_RESET_GLOBAL:

             OhciHcReg = (OHCI_HC_REGISTERS*)(UINTN)OhciDev->UsbHostControllerBaseAddress;

             // Stop periodic schedule
             OhciHcReg->HcControl.HcControlUnion.Field.PeriodicListEnable = 0;                              
             
             // Reset host controller
             OhciReset (PeiServices, OhciDev);
             
             // Clear PCI resource
             Val64 = 0;
             
             // Clear BAR
             Pci->Write( (CONST EFI_PEI_SERVICES**)PeiServices, Pci,
                     EfiPeiPciCfgWidthUint32,
                     OHCI_PCI_ADDRESS(OhciDev->ControllerIndex, OHCI_BASE_ADDR_REG),
                     &Val64);
             
             // Clear all other registers using gOhciPciRegisterTable[]
             for (RegisterIndex = 0;
                     RegisterIndex < gUsbPeiData->OhciRegInitCount;
                     RegisterIndex++) {

                 EFI_PEI_PCI_CFG_PPI_WIDTH Width;
             
                 switch (gOhciPciRegisterTable[RegisterIndex].Size) {
                     case 8: 
                             Width = EfiPeiPciCfgWidthUint8; 
                             break;
                     case 16:        
                             Width = EfiPeiPciCfgWidthUint16; 
                             break;
                     case 32:        
                             Width = EfiPeiPciCfgWidthUint32; 
                             break;
                     case 64:        
                             Width = EfiPeiPciCfgWidthUint64; 
                             break;
                     default:
                             continue;
                 }
             
                 Pci->Write(
                        (CONST EFI_PEI_SERVICES**)PeiServices, 
                        Pci,
                        Width,
                        OHCI_PCI_ADDRESS(OhciDev->ControllerIndex, gOhciPciRegisterTable[RegisterIndex].Register),
                        &Val64
                        );
             
             }

             break;                    
        default:
             return EFI_UNSUPPORTED;
    }
    
    return EFI_SUCCESS;  
}

/**
    This function enables a root hub port as specified by PortNumber.

        
    @param OhciDevPtr 
        --  PEI_OHCI_DEV pointer
    @param PortNumber 
        --  Root hub port number to be enabled

    @retval 
        VOID (Return Value)

**/

VOID OhciHcEnableRootHub (
    IN PEI_OHCI_DEV *OhciDevPtr,
    IN UINT8        PortNumber )
{
    OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;
    volatile HC_RH_PORT_STATUS *Pstatus = &OhciHcReg->HcRhPortStatus[PortNumber - 1];
    
    // Enable the port
    Pstatus->HcRhPortStatusUnion.AllBits = SET_PORT_ENABLE;

    // Wait for port enable to stabilize (100ms delay)
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 100 );

    // Reset the port
    Pstatus->HcRhPortStatusUnion.AllBits = SET_PORT_RESET;
    
    // Wait for reset to complete by polling the PortResetStatus field
    // as it is cleared at the end of the reset sequence
    while (Pstatus->HcRhPortStatusUnion.Field.PortResetStatus == RH_RESET_ACTIVE );

    // Wait an additional delay
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 500 ); 

    // Clear the PortResetStatus and PortResetStatusChange fields
    // by writing a 1 to the PortResetStatusChange field
    Pstatus->HcRhPortStatusUnion.AllBits = CLEAR_PORT_RESET_STATUS_CHANGE;

    // 1/2 second Wait for devices connected to the port to stabilize
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 500 );

}


/**
    This function intiates a USB control transfer and waits on it to 
    complete.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param bDeviceAddress 
        --  USB address of the device for which the control 
        transfer is to be issued
    @param DeviceType 
        --  Not used
    @param MaximumPacketLength 
        --  Maximum number of bytes that can be sent to or 
        received from the endpoint in a single data packet
    @param Request 
        --  EFI_USB_DEVICE_REQUEST pointer
    @param TransferDirection 
        --  Direction of transfer
    @param DataBuffer 
        --  Pointer to source or destination buffer
    @param DataLength 
        --  Length of buffer
    @param TimeOut 
        --  Not used
    @param TransferResult 
        --  Not used

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

typedef struct _D_REQUEST
{
    UINT8  RequestType;
    UINT8  Request;
    UINT16 Value;
    UINT16 Index;
    UINT16 Length;
} D_REQUEST;

EFI_STATUS
EFIAPI
OhciHcControlTransfer(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT8                       MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN EFI_USB_DEVICE_REQUEST      *Request,
    IN EFI_USB_DATA_DIRECTION      TransferDirection,
    IN OUT VOID *DataBuffer        OPTIONAL,
    IN OUT UINTN *DataLength       OPTIONAL,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult
)
{
    UINT16            *Data;
    POHCI_ED          ED;
    POHCI_TD          TD;
    UINT32            DwordData;
    UINT16            WordData;
    UINT16            WordRequest;
    UINT16            WordIndex;
    UINT16            WordValue;
    EFI_STATUS        Status = EFI_DEVICE_ERROR;
    PEI_OHCI_DEV      *OhciDevPtr =
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    POHCI_DESC_PTRS   DescPtrs =
        &(OhciDevPtr->OHCIDescPtrs);
    OHCI_HC_REGISTERS *HcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;
    UINT8               CompletionCode;

    // 5 ms delay is necessary for OHCI host controllers
    OHCI_FIXED_DELAY_MS( OhciDevPtr, 5 );

    WordRequest = (Request->Request << 8) | Request->RequestType;
    WordValue = Request->Value;
    WordIndex = Request->Index;

    //
    // Build the device request in the data area of the control setup qTD
    //
    Data = (UINT16 *) DescPtrs->PstTDControlSetup->SetupData;
    *Data++ = WordRequest;
    *Data++ = WordValue;
    *Data++ = WordIndex;
    *Data++ = (UINT16) *DataLength;
    *(UINT32 *) Data = (UINT32)(UINTN) DataBuffer;

    //
    // Prepare some registers that will be used in building the TDs below.
    // wLength  contains the data length.
    // Buffer contains the absolute address of the data buffer.
    // WordRequest contains the request type (bit 7 = 0/1 for Out/In).
    // DevInfo will contain a pointer to the DeviceInfo structure for
    // the given device.
    //
    // Ready the EDControl for the control transfer.
    //
    ED = DescPtrs->PstEDControl;
    //
    // The ED control field will be set so
    //   Function address & Endpoint number = ESI,
    //   Direction = From TD,
    //   Speed = DeviceInfo.EndpointSpeed,
    //   Skip = 1, Format = 0,
    //   Max packet size  = DeviceInfo.wEndp0MaxPacket
    // The HeadPointer field will be set to TDControlSetup
    // The TailPointer field will be set to OHCI_TERMINATE
    // The LinkPointer field will be set to OHCI_TERMINATE
    //

    // if wEndp0MaxPacket is NULL, then use default
    // packet size
    DwordData = MaximumPacketLength;

    // Force the max packet size to 64 bytes
    if (DwordData > 0x40 || DwordData == 0) {
        DwordData = 0x40;
    }
    DwordData <<= 16;                                       // DwordData[26:16] = device's packet size
    WordData = (UINT16) DeviceSpeed;                                            // 00/01/10 for HI/LO/FULL
    WordData = (WordData & 1) << 13;                          // WordData[13] = full/low speed flag
    WordData |= DeviceAddress | ED_SKIP_TDQ;
    ED->Control = DwordData | WordData;
    ED->TailPointer = 0;
    ED->EDLinkPointer = 0;

    TD = DescPtrs->PstTDControlSetup;
    //
    // The ControlStatus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_SETUP_PACKET,
    //   Delay Interrupt = GTD_INTD,
    //   Data Toggle = GTD_SETUP_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to the TD's SetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The BufferEnd field will point to the last byte of the TD's SetupData
    //   buffer.
    // The LinkPointer field will point to the TDControlData if data will
    //   be sent/received or to the TDControlStatus if no data is expected.
    // The CSReloadValue field will contain 0 because this is a "one shot"
    //   packet.
    // The pCallback will be set to point to the OHCI_ControlTDCallback
    //   routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control TDs
    //  do not need rebinding to the EDControl.
    //
    TD->ControlStatus = (UINT32) ( GTD_BUFFER_ROUNDING |
                                     GTD_SETUP_PACKET | GTD_SETUP_TOGGLE |
                                     GTD_NO_ERRORS | GTD_NOT_ACCESSED_32 );

    TD->CurrentBufferPointer = TD->SetupData;
    TD->BufferEnd = TD->SetupData + 7; // size of aSetupData - 1

    if (*DataLength) {  // some data to transfer

        // Fill in various fields in the TDControlData.
        TD = DescPtrs->PstTDControlData;
        //
        // The ControlStatus field will be set so
        //   Buffer Rounding = 1,
        //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
        //   Delay Interrupt = GTD_INTD,
        //   Data Toggle = GTD_DATA1_TOGGLE,
        //   Error Count = GTD_NO_ERRORS,
        //   Condition Code = GTD_NOT_ACCESSED
        // The CurrentBufferPointer field will point to the caller's buffer
        //   which is now in EBP.
        // The BufferEnd field will point to the last byte of the caller's
        //   buffer.
        // The LinkPointer field will point to the TDControlStatus.
        // The CSReloadValue field will contain 0 because this is a
        //   "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback
        //   routine.
        // The ActiveFlag field will be set to TRUE.
        // The DeviceAddress field does not need to be set since the Control
        //   TDs do not need rebinding to the EDControl.
        // The CSReloadValue field will contain 0 because this is a
        //   "one shot" packet.
        // The pCallback will be set to point to the OHCI_ControlTDCallback
        //   routine.
        // The ActiveFlag field will be set to TRUE.    return  USB_SUCCESS;
        // The DeviceAddress field does not need to be set since the Control
        //   TDs do not need rebinding to the EDControl.
        //
        DwordData = (UINT32) ( GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE
                          | GTD_NO_ERRORS | GTD_NOT_ACCESSED_32 );
        DwordData = (WordRequest & BIT7)
                ? (DwordData | GTD_IN_PACKET | GTD_INTD)
                : (DwordData | GTD_OUT_PACKET);
        TD->ControlStatus = DwordData;
        TD->CurrentBufferPointer = (UINT8 *) DataBuffer;

        WordData = (UINT16)((*DataLength < MAX_CONTROL_DATA_SIZE)
                ? *DataLength
                : MAX_CONTROL_DATA_SIZE);
        TD->BufferEnd = (UINT8 *) DataBuffer + WordData - 1;
    }

    // Fill in various fields in the TDControlStatus.
    TD = DescPtrs->PstTDControlStatus;
    //
    // The ControlStaus field will be set so
    //   Buffer Rounding = 1,
    //   Direction PID = GTD_OUT_PACKET/GTD_IN_PACKET,
    //   Delay Interrupt = GTD_INTD,
    //   Data Toggle = GTD_DATA1_TOGGLE,
    //   Error Count = GTD_NO_ERRORS,
    //   Condition Code = GTD_NOT_ACCESSED
    // The CurrentBufferPointer field will point to NULL
    // The BufferEnd field will point to NULL.
    // The LinkPointer field will point to OHCI_TERMINATE.
    // The CSReloadValue field will contain 0 because this is a
    //   "one shot" packet.
    // The pCallback will be set to point to the OHCI_ControlTdCallback
    //   routine.
    // The ActiveFlag field will be set to TRUE.
    // The DeviceAddress field does not need to be set since the Control
    //   TDs do not need rebinding to the EdControl.
    //
    // Note: For OUT control transfer status should be IN and
    //       for IN cotrol transfer, status should be OUT.
    //
    DwordData = (UINT32) ( GTD_BUFFER_ROUNDING | GTD_DATA1_TOGGLE
                      | GTD_NO_ERRORS | GTD_NOT_ACCESSED_32 );
    DwordData = (WordRequest & BIT7)
            ? (DwordData | GTD_OUT_PACKET)
            : (DwordData | GTD_IN_PACKET | GTD_INTD);
    TD->ControlStatus = DwordData;
    TD->CurrentBufferPointer = NULL;
    TD->BufferEnd = NULL;
    TD->LinkPointer = NULL;

    //
    // Link all the pointers together
    //
    TD = DescPtrs->PstTDControlSetup;
    ED->HeadPointer = TD;
    if (*DataLength) {  // chain in data TD
        TD->LinkPointer = (UINT8 *) DescPtrs->PstTDControlData;
        TD = DescPtrs->PstTDControlData;
    }
    TD->LinkPointer = (UINT8 *) DescPtrs->PstTDControlStatus;

    DescPtrs->PstTDControlStatus->LinkPointer = NULL;

    TD = DescPtrs->PstTDControlSetup;
    do {
        TD->CSReloadValue = 0;
        TD->ActiveFlag = TRUE;
        TD = (POHCI_TD) TD->LinkPointer;
    } while (TD);

    // clear the WriteBackDoneHead status bit in
    // the HcInterruptStatus register
    HcReg->HcInterruptStatus.HcInterruptStatusUnion.Field.WriteBackDoneHead = HCINT_STATUS_CLEAR;

    //
    // Now control queue is complete, so set ED_SKIP_TDQ=0
    //
    ED->Control &= ~ED_SKIP_TDQ;
    //
    // Set the HcControlHeadED register to point to the EDControl.
    //
    HcReg->HcControlHeadEd = (UINTN) ED;

    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the ControllListFilled field of HcCommandStatus reg.
    // This will cause the HC to execute the transaction in the next
    // active frame.
    //
    HcReg->HcCommandStatus.HcCommandStatusUnion.AllBits = SET_CONTROL_LIST_FILLED;

    //
    // Now wait for the control status TD to complete.  When it has completed,
    // the OHCI_ControlTDCallback will set its active flag to FALSE.
    Status = OhciHcWaitForTransferComplete( PeiServices, OhciDevPtr,
               DescPtrs->PstTDControlStatus );

    //
    // Stop the HC from processing the EDControl by setting its Skip bit.
    //
    ED->Control |= ED_SKIP_TDQ;

    //
    // Finally check for any error bits set in both the TDControlStatus.
    // If the TD did not complete successfully, return STC.
    //

    // DwordData[3:0] = Completion status
    CompletionCode = (UINT8)(DescPtrs->PstTDControlStatus->ControlStatus >> 28);

	switch (CompletionCode) {
        case GTD_NO_ERROR:
            *TransferResult = EFI_USB_NOERROR;
            Status = EFI_SUCCESS;
			break;
		case GTD_STALL:
            *TransferResult = EFI_USB_ERR_STALL;
			break;
        case GTD_NOT_ACCESSED:
            *TransferResult = EFI_USB_ERR_TIMEOUT;
            Status = EFI_TIMEOUT;
            break;
		default:
			break;
	}

    return Status;

}

/**
    This function intiates a USB bulk transfer and waits on it to 
    complete.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param This 
        --  PEI_USB_HOST_CONTROLLER_PPI pointer
    @param DeviceAddress 
        --  USB address of the device for which the control 
        transfer is to be issued
    @param EndPointAddress 
        --  Particular endpoint for the device
    @param MaximumPacketLength 
        --  Maximum number of bytes that can be sent to or 
        received from the endpoint in a single data packet
    @param DataBuffer 
        --  Pointer to source or destination buffer
    @param DataLength 
        --  Length of buffer
    @param DataToggle 
        --  Used to update the control/status DataToggle field
        of the Transfer Descriptor
    @param TimeOut 
        --  Not used
    @param TransferResult 
        --  Not used

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS
EFIAPI
OhciHcBulkTransfer(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       EndPointAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT16                      MaximumPacketLength,
    IN UINT16                      TransactionTranslator    OPTIONAL,
    IN OUT VOID                    *DataBuffer,
    IN OUT UINTN                   *DataLength,
    IN OUT UINT8                   *DataToggle,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult
)
{
    UINT32          DwordData;
    UINT16          MaxPkt;
    EFI_STATUS      Status = EFI_DEVICE_ERROR;
    UINT8           Endp;
    UINT8           Toggle;
    PEI_OHCI_DEV        *OhciDevPtr = 
        PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS( This );
    POHCI_DESC_PTRS     DescPtrs = &(OhciDevPtr->OHCIDescPtrs);
    OHCI_HC_REGISTERS   *HcReg =
        (OHCI_HC_REGISTERS *) OhciDevPtr->UsbHostControllerBaseAddress;
    UINT8               CompletionCode;

    MaxPkt = MaximumPacketLength;

    if (MaxPkt == 0) {
        *DataLength = 0;
        return EFI_NOT_FOUND;
    }

    //Clear Bulk ED and TD
    ZeroMem(DescPtrs->PstEDBulk, sizeof(OHCI_ED));
    ZeroMem(DescPtrs->PstTDBulkData, sizeof(OHCI_TD));
    //
    //  Set the SKIP bit in the EdBulk to avoid accidental scheduling
    //
    DescPtrs->PstEDBulk->Control = ED_SKIP_TDQ;
    //
    // Set the ED's head pointer field to bulk data TD and tail pointer
    // field to OHCI_TERMINATE. Also set ED's link pointer to
    // OHCI_TERMINATE.
    //
    DescPtrs->PstEDBulk->HeadPointer = DescPtrs->PstTDBulkData;
    DescPtrs->PstEDBulk->TailPointer = OHCI_TERMINATE;
    DescPtrs->PstEDBulk->EDLinkPointer = OHCI_TERMINATE;
    //
    // Form the data needed for ED's control field with the available
    // information
    //
    Endp = EndPointAddress & 0x7f;
    DwordData = (EndPointAddress & 0x80) ? ED_IN_PACKET : ED_OUT_PACKET;
    DwordData |= DeviceAddress;
    DwordData |= (UINT16) Endp << 7;
    DwordData |= (UINT32) MaxPkt << 16;

    //
    // Update the ED's control field with the data formed
    // ASSUME ALL MASS DEVICES ARE FULL SPEED DEVICES.
    //
    DescPtrs->PstEDBulk->Control = DwordData;
    //
    // Fill the general bulk data TD with relevant information.  Set the
    // TD's control field with buffer rounding set to 1, direction PID to
    // don't care, delay interrupt to INTD, data toggle to the latest data
    // toggle value, error count to no errors and condition code to not
    // accessed.
    //
    // Set the data toggle to DATA0 (SETUP_TOGGLE)
    DescPtrs->PstTDBulkData->ControlStatus = (UINT32) (
        GTD_BUFFER_ROUNDING |
        GTD_IN_PACKET |
        GTD_INTD |
        GTD_SETUP_TOGGLE |
        GTD_NO_ERRORS |
        GTD_NOT_ACCESSED_32
                                                );
    DescPtrs->PstTDBulkData->ControlStatus |= (UINT32) *DataToggle << 24;

    //
    // GTD current buffer pointer field will point to the caller's buffer which
    // now in the variable Buffer
    //
    DescPtrs->PstTDBulkData->CurrentBufferPointer = (UINT8 *) DataBuffer;
    DescPtrs->PstTDBulkData->BufferEnd = (UINT8 *) DataBuffer +
                                             *DataLength - 1;
    DescPtrs->PstTDBulkData->LinkPointer = OHCI_TERMINATE;
    //
    // GTD's CSReloadValue field will contain 0 because this is a
    // "one shot" packet
    //
    DescPtrs->PstTDBulkData->CSReloadValue = 0;
    DescPtrs->PstTDBulkData->ActiveFlag = TRUE;

    // Set the HCBulkHeadED register to point to the bulk ED
    DescPtrs->PstEDBulk->Control &= ~ED_SKIP_TDQ;
    HcReg->HcBulkHeadEd = (UINT32) DescPtrs->PstEDBulk;
    
    // Enable the bulk list processing
    HcReg->HcCommandStatus.HcCommandStatusUnion.AllBits = SET_BULK_LIST_FILLED;

    Status = OhciHcWaitForTransferComplete( PeiServices, OhciDevPtr,
        DescPtrs->PstTDBulkData );
    //
    // Stop the HC from processing the EDBulk by setting its Skip bit.
    //
    DescPtrs->PstEDBulk->Control |= ED_SKIP_TDQ;
    //
    // Update the data toggle value into the mass info structure
    //

    *DataToggle = (UINT8) ( ( (DescPtrs->PstTDBulkData->ControlStatus &
                               GTD_DATA_TOGGLE) >> 24 ) & 1 );
    Toggle = (UINT8) ( (DescPtrs->PstTDBulkData->ControlStatus &
                        GTD_DATA_TOGGLE) >> 24 );
    if ( (Toggle & 0x02) == 0 ) {
        //Use the Carry
        DwordData = (UINT32) DescPtrs->PstEDBulk->HeadPointer;
        DwordData &= 0x00000002;
        DwordData = DwordData >> 1;
        DwordData &= 0x00000001;
        *DataToggle = (UINT8)DwordData;
    }
    //
    // Check for the error conditions - if possible recover from them
    //
    CompletionCode = (UINT8)(DescPtrs->PstTDBulkData->ControlStatus >> 28);
    
	switch (CompletionCode) {
        case GTD_NO_ERROR:
            *TransferResult = EFI_USB_NOERROR;
            Status = EFI_SUCCESS;
			break;
		case GTD_STALL:
            *TransferResult = EFI_USB_ERR_STALL;
            *DataLength = 0;
			break;
        case GTD_NOT_ACCESSED:
            *TransferResult = EFI_USB_ERR_TIMEOUT;
            *DataLength = 0;
            Status = EFI_TIMEOUT;
            break;
		default:
            *DataLength = 0;
			break;
	}

    if (Status != EFI_SUCCESS) {
        return Status;
    }
    
    //
    // Get the size of data transferred
    //
    // Size transferred is calculated by subtracting end address with current
    // buffer pointer and subtracting that value from the total size
    //
    if (!DescPtrs->PstTDBulkData->CurrentBufferPointer) {
        //All data are transfered.
        return EFI_SUCCESS;
    }
    DwordData = (UINT32)DescPtrs->PstTDBulkData->BufferEnd;
    DwordData = DwordData -
            (UINT32)DescPtrs->PstTDBulkData->CurrentBufferPointer;
    
    if (DwordData != 0) {
        *DataLength = *DataLength - DwordData - 1;
    }
    
    return Status;

}

/**
    This function processes a USB interrupt transfer within a given timeout.

    @retval 
        EFI_INVALID_PARAMETER   Invalid data, datalength, datatoggle
        EFI_NOT_FOUND   No endpoint found that matches the given parameters.
        EFI_TIMEOUT     No transfer during the given timeout.
        EFI_SUCCESS     Successful transfer, data is copied to the given data buffer.

**/

EFI_STATUS
EFIAPI
OhciHcSyncInterruptTransfer(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI  *This,
    IN     UINT8                    DeviceAddress,
    IN     UINT8                    EndPointAddress,
    IN     UINT8                    DeviceSpeed,
    IN     UINT8                    MaximumPacketLength,
    IN UINT16                       TransactionTranslator,
    IN OUT VOID                     *Data,
    IN OUT UINTN                    *DataLength,
    IN OUT UINT8                    *DataToggle,
    IN     UINTN                    TimeOut,
    OUT    UINT32                   *TransferResult
)
{
    PEI_OHCI_DEV    *OhciDev = PEI_RECOVERY_USB_OHCI_DEV_FROM_THIS(This);
    volatile OHCI_HC_REGISTERS   *OhciHcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDev->UsbHostControllerBaseAddress;
    POHCI_DESC_PTRS pDescPtrs = &OhciDev->OHCIDescPtrs;

    UINTN           Count;
    UINT8           *Src;
    UINT8           *Dst;

    if (Data == NULL || DataLength == NULL) {
        ASSERT(FALSE);
        return EFI_INVALID_PARAMETER;
    }

    for (Count = 0; Count < TimeOut; Count++) {
        // Check if the memory dword at HCCADONEHEAD has been updated to contain the head
        // pointer of the linked list of TDs that have completed.
        if (OhciHcReg->HcHcca->HccaDoneHead != 0) {
            break;
        }

        OHCI_FIXED_DELAY_MS(OhciDev, 1);  // 1 msec
    }

    // Clear the link pointer. It may point to some other TD
    pDescPtrs->PstTDInterruptData->LinkPointer = OHCI_TERMINATE;
    pDescPtrs->PstTDInterruptData->ControlStatus = pDescPtrs->PstTDInterruptData->CSReloadValue;
    pDescPtrs->PstTDInterruptData->CurrentBufferPointer = pDescPtrs->PstTDInterruptData->SetupData;

    pDescPtrs->PstEDInterrupt->HeadPointer = (POHCI_TD)((UINTN)pDescPtrs->PstEDInterrupt->HeadPointer & ED_TOGGLE_CARRY);
    pDescPtrs->PstEDInterrupt->HeadPointer = (POHCI_TD)((UINTN)pDescPtrs->PstEDInterrupt->HeadPointer | (UINTN)pDescPtrs->PstTDInterruptData);
    pDescPtrs->PstTDInterruptData->ActiveFlag = TRUE;

    if (Count == TimeOut) return EFI_TIMEOUT;

    // Get the data and return success
    for (Src = pDescPtrs->PstTDInterruptData->SetupData,
         Dst = (UINT8*)Data,
         Count = 0; Count < 8; Count++)
    {
        *Dst++ = *Src++;
    }

    return EFI_SUCCESS;
}


/**
    This function waits for a tranfer to complete by polling the 
    HcInterruptStatus register's WritebackDoneHead field.
      
        
    @param OhciDevPtr 
        --  PEI_OHCI_DEV pointer
    @param Td 
        --  Not used

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS OhciHcWaitForTransferComplete (
	IN EFI_PEI_SERVICES	**PeiServices,
    IN PEI_OHCI_DEV *OhciDevPtr,
    IN POHCI_TD     Td )
{
    UINT32              Count;
    OHCI_HC_REGISTERS   *HcReg =
        (OHCI_HC_REGISTERS *)(UINTN) OhciDevPtr->UsbHostControllerBaseAddress;
    HC_INTERRUPT_STATUS *HcIntStatus = &HcReg->HcInterruptStatus;
	UINT32				DoneHead;

    // Poll (up to 4 seconds) or until the
    // WriteBackDoneHead status bit is set in
    // the HcInterruptStatus operational register.

    // if the WriteBackDoneHead is set, then clear 
    // HccaDoneHead in the HCCA and WriteBackDoneHead
    // and then return EFI_SUCCESS to continue execution.

    for (Count = 0; Count < 1000; Count++) {
        if (HcIntStatus->HcInterruptStatusUnion.Field.WriteBackDoneHead == HCINT_WB_DONE ) {
			DoneHead = HcReg->HcHcca->HccaDoneHead;
			HcReg->HcHcca->HccaDoneHead = 0;
            HcIntStatus->HcInterruptStatusUnion.Field.WriteBackDoneHead = HCINT_STATUS_CLEAR;
			if (DoneHead == (UINT32)(UINTN)Td) {
            	return EFI_SUCCESS;
			}
        }
        OHCI_FIXED_DELAY_MS( OhciDevPtr, 4 ); // 4 ms

    }
	
	DEBUG((DEBUG_ERROR, "OHCI Time-Out:\n"));
    return EFI_NOT_FOUND;

}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
