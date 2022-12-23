//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file PeiEhci.c
    This file is the main source file for the EHCI PEI USB
    recovery module.  Its entry point at EhciPeiUsbEntryPoint
    will be executed from the UsbRecoveryInitialize INIT_LIST.

**/

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#include <Ppi/Stall.h>
#include "UsbPei.h"
#include "PeiEhci.h"

extern EFI_PEI_STALL_PPI *gUsbPeiStall;

EFI_STATUS EhciPeiBoardInit (
    IN EFI_PEI_SERVICES     **PeiServices,
    EFI_PEI_PCI_CFG2_PPI    *PciCfgPpi,
    EFI_PEI_STALL_PPI       *StallPpi );


PCI_BUS_DEV_FUNCTION *gEhciControllerPciTable;

UINT32 *gEhciControllerBaseAddress;

BOOLEAN EhciDbg_PortUsed = FALSE;
extern USB_PEI_GLOBAL_DATA    *gUsbPeiData;

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

UINT32
EhciGetOperationalRegisterBase (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN UINT16               ControllerIndex )
{
    UINT32 EhciBaseAddress;

    (*PeiServices)->PciCfg->Read( 
                      (CONST EFI_PEI_SERVICES**)PeiServices, 
                      (*PeiServices)->PciCfg,
                      EfiPeiPciCfgWidthUint32,
                      EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[ControllerIndex].Bus, 
                      gEhciControllerPciTable[ControllerIndex].Device, 
                      gEhciControllerPciTable[ControllerIndex].Function, 
                      EHCI_BASE_ADDR_REG ),
                      &EhciBaseAddress
                      );


    return EhciBaseAddress;
}


/**
    Check debugport of a controlller is in use or not.   

        
    @param PeiServices 
        --  PEI Sevices table pointer
    @param ControllerIndex 
        --  Index of the controller in the global
        PCI_BUS_DEV_FUNCTION array

        Output :

        Note : EhciDbg_PortUsed used to maintain the debugport usage of 
        CURRENT processing controller.
**/

VOID
Update_EhciDbg_PortUsed(
    EFI_PEI_SERVICES    **PeiServices,
    UINT8               Index
)
{
    UINT8   CmdReg = 0;
    UINT16  DebugBase = 0;
    UINT32  EhciBaseMem = 0;

    // Read Command register and check MMIO enabled or not

    (*PeiServices)->PciCfg->Read( 
                      (CONST EFI_PEI_SERVICES**)PeiServices, 
                      (*PeiServices)->PciCfg,
                      EfiPeiPciCfgWidthUint8,
                      EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[Index].Bus, 
                      gEhciControllerPciTable[Index].Device, 
                      gEhciControllerPciTable[Index].Function, 
                      EHCI_CMD_REGISTER ),
                      &CmdReg );
            
    if(!(CmdReg & 2)) { //MMIO is disabled
        EhciDbg_PortUsed =  FALSE;
        return;
    }

    // Retrieve the debugport base offset address
    (*PeiServices)->PciCfg->Read( 
                      (CONST EFI_PEI_SERVICES**)PeiServices, 
                      (*PeiServices)->PciCfg,
                      EfiPeiPciCfgWidthUint16,
                      EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[Index].Bus, 
                      gEhciControllerPciTable[Index].Device, 
                      gEhciControllerPciTable[Index].Function, 
                      DEBUG_BASE ),
                      &DebugBase );

    DebugBase = DebugBase & 0x1FFF; // Bar number hardwired to 001b

    EhciBaseMem = EhciGetOperationalRegisterBase(PeiServices,Index);

    // Check ENABLED_CNT bit of DEBUG status register
    if ((*(volatile UINT32*)(UINTN)(EhciBaseMem + DebugBase)) & BIT28){
        EhciDbg_PortUsed = TRUE;
    }else{
        EhciDbg_PortUsed = FALSE;
    }
}


/**
    This is the entry point into the EHCI controller initialization
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

EFI_STATUS
EhciPeiUsbEntryPoint (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    UINT8                Index;
    UINTN                MemPages;
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    PEI_EHCI_DEV         *EhciDevPtr;
    UINT8                ByteData;
    UINT8                ClassCode[4];
    BOOLEAN              FreeResource;

    if ((gUsbPeiData->UsbPeiFeature & USB_EHCI_PEI_SUPPORT) != USB_EHCI_PEI_SUPPORT)
        return EFI_UNSUPPORTED;

    gEhciControllerPciTable = gUsbPeiData->EhciPciDev;
    gEhciControllerBaseAddress = (UINT32*)gUsbPeiData->EhciIoResource;

    //-------------------------------------------
    // Initialize the EFI_PEI_STALL_PPI interface
    //-------------------------------------------
    if (gUsbPeiStall==NULL) {
        return EFI_UNSUPPORTED;
    }

    //-----------------------------------------
    // board specific initialization to program
    // PCI bridges and enable MMIO
    //-----------------------------------------

    Status = EhciPeiBoardInit(
               PeiServices,
               (*PeiServices)->PciCfg,
               gUsbPeiStall );
    if ( EFI_ERROR( Status ) ) {
        return EFI_UNSUPPORTED;
    }

    //----------------------------------------------------------
    // Allocate EHCI DEVICE OBJECT that holds all necessary
    // information for the Host Controller operational registers
    // for each controller.  Initialze the controller and setup
    // data structures for ready for operation
    //----------------------------------------------------------

    for (Index = 0; Index < gUsbPeiData->EhciHcCount; Index++) {
        (*PeiServices)->PciCfg->Read(
                          (CONST EFI_PEI_SERVICES**)PeiServices,
                          (*PeiServices)->PciCfg,
                          EfiPeiPciCfgWidthUint32, 
                          EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[Index].Bus, 
                          gEhciControllerPciTable[Index].Device, 
                          gEhciControllerPciTable[Index].Function, 
                          PCI_REG_REVID ), ClassCode);
 
        DEBUG((DEBUG_INFO, "USB EHCI#%d PI %x SubClassCode %x BaseCode %x\n", 
            Index, ClassCode[1], ClassCode[2], ClassCode[3]));

        if ((ClassCode[1] != PCI_CLASSC_PI_EHCI) || 
            (ClassCode[2] != PCI_CLASSC_SUBCLASS_SERIAL_USB) ||
            (ClassCode[3] != PCI_CLASSC_BASE_CLASS_SERIAL)) {
            continue;   //This is not an ehci controller.
        }

        FreeResource = FALSE;
        if (EhciGetOperationalRegisterBase(PeiServices, Index) == 0) {
            (*PeiServices)->PciCfg->Write( 
                              (CONST EFI_PEI_SERVICES**)PeiServices, 
                              (*PeiServices)->PciCfg,
                              EfiPeiPciCfgWidthUint32,
                              EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[Index].Bus, 
                              gEhciControllerPciTable[Index].Device, 
                              gEhciControllerPciTable[Index].Function, 
                              EHCI_BASE_ADDR_REG ),
                              &gEhciControllerBaseAddress[Index] );
            FreeResource = TRUE;
        }

        ByteData = 6;   // Enable MMIO and BusMaster

        (*PeiServices)->PciCfg->Write( 
                          (CONST EFI_PEI_SERVICES**)PeiServices, 
                          (*PeiServices)->PciCfg,
                          EfiPeiPciCfgWidthUint8,
                          EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[Index].Bus, 
                          gEhciControllerPciTable[Index].Device, 
                          gEhciControllerPciTable[Index].Function, 
                          EHCI_CMD_REGISTER ),
                          &ByteData );


        Update_EhciDbg_PortUsed(PeiServices,Index);

        // PAGESIZE = 0x1000
        MemPages = sizeof (PEI_EHCI_DEV) / 0x1000 + 1;

        Status = PeiServicesAllocatePages(
                     EfiBootServicesData,
                     MemPages,
                     &TempPtr
                     );
        if ( EFI_ERROR( Status ) )
        {
            return EFI_OUT_OF_RESOURCES;
        }
                (**PeiServices).SetMem((VOID*)(UINTN)TempPtr, sizeof (PEI_EHCI_DEV), 0);

        EhciDevPtr = (PEI_EHCI_DEV *) ( (UINTN) TempPtr );
        EhciDevPtr->Signature = PEI_EHCI_DEV_SIGNATURE;
        EhciDevPtr->PeiServices = PeiServices;
        EhciDevPtr->CpuIoPpi = (*PeiServices)->CpuIo;
        EhciDevPtr->PciCfgPpi = (*PeiServices)->PciCfg;
        EhciDevPtr->UsbHostControllerBaseAddress =
        EhciGetOperationalRegisterBase( PeiServices, Index );
        EhciDevPtr->ControllerIndex = Index;
        EhciDevPtr->FreeResource = FreeResource;

        //Initialize the EHCI Controller for operation

        EhciInitHC( PeiServices, EhciDevPtr );

        //Setup PPI entry point
        EhciDevPtr->UsbHostControllerPpi.ControlTransfer = EhciHcControlTransfer;
        EhciDevPtr->UsbHostControllerPpi.BulkTransfer = EhciHcBulkTransfer;
        EhciDevPtr->UsbHostControllerPpi.SyncInterruptTransfer = EhciHcSyncInterruptTransfer;
        EhciDevPtr->UsbHostControllerPpi.GetRootHubPortNumber = EhciHcGetRootHubPortNumber;
        EhciDevPtr->UsbHostControllerPpi.GetRootHubPortStatus = EhciHcGetRootHubPortStatus;
        EhciDevPtr->UsbHostControllerPpi.SetRootHubPortFeature = EhciHcSetRootHubPortFeature;
        EhciDevPtr->UsbHostControllerPpi.ClearRootHubPortFeature = EhciHcClearRootHubPortFeature;
        EhciDevPtr->UsbHostControllerPpi.Reset = EhciHcReset;

        EhciDevPtr->UsbHostControllerPpi.DebugPortUsed = EhciDbg_PortUsed;
        EhciDevPtr->UsbHostControllerPpi.PreConfigureDevice = NULL;
        EhciDevPtr->UsbHostControllerPpi.EnableEndpoints = NULL;
        EhciDevPtr->UsbHostControllerPpi.ActivatePolling = EhciHcActivatePolling;
        EhciDevPtr->UsbHostControllerPpi.CurrentAddress = 0;

        EhciDevPtr->PpiDescriptor.Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
        EhciDevPtr->PpiDescriptor.Guid = &gAmiPeiUsbHostControllerPpiGuid;
        EhciDevPtr->PpiDescriptor.Ppi = &EhciDevPtr->UsbHostControllerPpi;

        //Now is the time to install the PPI
        Status = PeiServicesInstallPpi (&EhciDevPtr->PpiDescriptor); 
        if ( EFI_ERROR( Status ) )
        {
            return EFI_NOT_FOUND;
        }

    }

    
    return EFI_SUCCESS;

}

/**
    This function adds the QH to a particular periodic schedule

    @param InsertQHAt    One of the pointers of DESC_PTRS to be used to insert
        the new QH at.
        QhToInsert    New QH to be inserted

**/

VOID
EhciScheduleQH(
    EHCI_QH *InsertQHAt,
    EHCI_QH *QHToInsert)
{
    QHToInsert->LinkPointer = InsertQHAt->LinkPointer;
    InsertQHAt->LinkPointer = (UINT32)((UINTN)QHToInsert | EHCI_QUEUE_HEAD);
}


/**
    EHCI controller initialization.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param EhciDevPtr 
        --  PEI_EHCI_DEV pointer
    @param Index 
        --  Index of this controller in the global 
        PCI_BUS_DEV_FUNCTION array

    @retval 
        VOID (Return Value)

    @note  
      EhciDevPtr->UsbHostControllerBaseAddress is is initialized

**/

VOID
EhciInitHC (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_EHCI_DEV     *EhciDevPtr)
{
    UINT8                   *Ptr;
    UINTN                   MemPages;
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    TempPtr;
    EHCI_HC_CAP_REG         *EhciHcCapReg =
                            (EHCI_HC_CAP_REG *)(UINTN)EhciDevPtr->UsbHostControllerBaseAddress;
    EHCI_HC_OPER_REG        *EhciHcOpReg;
    EHCI_DESC_PTRS          *EhciDescPtrs;
    UINT8                   Index;
    BOOLEAN                 SetPortPower = FALSE;

    // Allocate memory for control transfers and bulk transfers
    // Allocate a block of memory and define/initialize 
    // Setup Control and Bulk EDs/TDs
    EhciDescPtrs = &(EhciDevPtr->EhciDescPtrs);

    MemPages = (( 5 * sizeof (EHCI_QTD) ) + (6 * sizeof(EHCI_QH) )) / 0x1000 + 1;

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
    if (Ptr == NULL) {
        return;
    }
    
    ZeroMem(Ptr, 5 * sizeof (EHCI_QTD) + 6 * sizeof(EHCI_QH));

    EhciDescPtrs->Qh1ms = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->Qh8ms = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->Qh32ms = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->QhControl = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->QtdControlSetup = (EHCI_QTD*) Ptr;
    Ptr += sizeof (EHCI_QTD);
    EhciDescPtrs->QtdControlData = (EHCI_QTD*) Ptr;
    Ptr += sizeof (EHCI_QTD);
    EhciDescPtrs->QtdControlStatus = (EHCI_QTD*) Ptr;
    Ptr += sizeof (EHCI_QTD);
    EhciDescPtrs->QhInterrupt = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->QtdInterruptData = (EHCI_QTD*) Ptr;
    Ptr += sizeof (EHCI_QTD);
    EhciDescPtrs->QhBulk = (EHCI_QH*) Ptr;
    Ptr += sizeof (EHCI_QH);
    EhciDescPtrs->QtdBulkData = (EHCI_QTD*) Ptr;

    // Store number of downstream ports into PEI_EHCI_DEV struct
    EhciDevPtr->NumPorts = (UINT8)(EhciHcCapReg->HcsParams.EhciHcsParamsUnion.Field.NumberOfPorts);

    // Read the Capability Registers Length to find the Offset address for the
    // beginning of the operational registers
    EhciHcOpReg = (EHCI_HC_OPER_REG *)((UINTN)EhciHcCapReg + EhciHcCapReg->CapLength);
    EhciDevPtr->EhciHcOpReg = EhciHcOpReg;

    EhciDevPtr->HcStatus = 0;

    // Do a Host Controller reset first
    if(!EhciDbg_PortUsed)
        EhciReset( PeiServices, EhciDevPtr );

    EhciInitializePeriodicSchedule(PeiServices, EhciDevPtr);

    // Schedule QHInterrupt to 1 millisec schedule
    EhciDescPtrs->QhInterrupt->NextqTDPtr      = 1;
    EhciDescPtrs->QhInterrupt->AltNextqTDPtr   = 1;
    EhciDescPtrs->QhInterrupt->LinkPointer     = 1;

    // Schedule the QHInterrupt to 1msec schedule
    EhciScheduleQH(EhciDescPtrs->Qh1ms, EhciDescPtrs->QhInterrupt);

    // Clear status register - all R/WC bits
    EhciHcOpReg->UsbSts.EhciUsbstsUnion.AllBits = 
                   (EHCI_USB_INTERRUPT |        // Interrupt
                   EHCI_USB_ERROR_INTERRUPT |  // Error interrupt
                   EHCI_PORT_CHANGE_DETECT |   // Port Change Detect
                   EHCI_FRAME_LIST_ROLLOVER |  // Frame List Rollover
                   EHCI_HOST_SYSTEM_ERROR |    // Host System Error
                   EHCI_INT_ASYNC_ADVANCE);    // Interrupt on Async Advance

    // Turn HC on
    EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits = EHCI_RUNSTOP | EHCI_INTTHRESHOLD | EHCI_PER_SCHED_ENABLE;

    // Disconnect all ports from companion HC (if any) and route them to EHCI
    EhciHcOpReg->ConfigFlag = 1;

    EHCI_FIXED_DELAY_US(EhciDevPtr, 100);   // 100 us delay to stabilize

    if (EhciHcCapReg->HcsParams.EhciHcsParamsUnion.Field.PortPowerControl == 0) {
        return;
    }
    
    // Enable per port power
    for (Index = 0; Index < EhciDevPtr->NumPorts; Index++) {
        if (EhciHcOpReg->PortSC[Index].EhciPortscUnion.Field.PortPower == 0) {
            EhciHcOpReg->PortSC[Index].EhciPortscUnion.Field.PortPower = 1;
            SetPortPower = TRUE;
        }
    }
    
    if (SetPortPower) {
        EHCI_FIXED_DELAY_MS(EhciDevPtr, 20);
    }
}


/**
    This function initializes frame list, updates HC register with the base
    address and adds 1ms QH to the periodic schedule.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param EhciDevPtr 
        --  PEI_EHCI_DEV pointer

**/

VOID
EhciInitializePeriodicSchedule (
    EFI_PEI_SERVICES **PeiServices,
    PEI_EHCI_DEV     *EhciDevPtr)
{
    static UINT16 AsyncListSizeTable[3] = {1024, 512, 256};
    EFI_STATUS  Status;
    EFI_PHYSICAL_ADDRESS TempPtr;
    UINT16      Index;
    UINT32      *FrameListPtr;

    // Read it back and update AsyncListSize field
    Index = (UINT16)(EhciDevPtr->EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.Field.FrameListSize);
    ASSERT(Index < 3);

    EhciDevPtr->AsyncListSize = AsyncListSizeTable[Index];

    DEBUG((DEBUG_INFO, "PEIEHCI AsyncListSize: %d\n", EhciDevPtr->AsyncListSize));

    // Allocate one page of memory for the frame list
    //Status = (**PeiServices).AllocatePages(PeiServices, EfiBootServicesData, 1, &TempPtr);
    Status = PeiServicesAllocatePages(
                 EfiBootServicesData,
                 1,
                 &TempPtr
                 );
    ASSERT(Status == EFI_SUCCESS);
    EhciDevPtr->FrameList = (UINT32*)(UINTN)TempPtr;

    // Initialize the frame list with EHCI_TERMINATE and add 1ms, 8ms, and 32ms periodic schedule
    FrameListPtr = EhciDevPtr->FrameList;
    for (Index = 0; Index < EhciDevPtr->AsyncListSize; Index ++) {
        FrameListPtr[Index] = EHCI_TERMINATE;

        EhciAddPeriodicQH (EhciDevPtr->EhciDescPtrs.Qh1ms, &FrameListPtr[Index]);       // 1 ms

        if (!(Index % 8)) {
            EhciAddPeriodicQH (EhciDevPtr->EhciDescPtrs.Qh8ms, &FrameListPtr[Index]);   // 8 ms
        }
        if (!(Index % 32)) {
            EhciAddPeriodicQH (EhciDevPtr->EhciDescPtrs.Qh32ms, &FrameListPtr[Index]);  // 32 ms
        }
    }

    // Write the base address of the Periodic Frame List to the Host Controller
    EhciDevPtr->EhciHcOpReg->PeriodicListBase = (UINT32)(UINTN)EhciDevPtr->FrameList;
}


/**
    This function sets up the QTD pointers and restarts periodic schedule.

**/

EFI_STATUS
EhciProcessPeriodicList(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EHCI_QH     *PollED,
    IN EHCI_QTD    *PollTD
)
{
    if (PollTD->Token & (QTD_ACTIVE | QTD_HALTED))
    {
        return EFI_NOT_READY;
    }

    // Clear unwanted bits in the dToken
    PollTD->Token &= ~(QTD_XFER_DATA_SIZE | QTD_STATUS_FIELD);

    // Set length
    PollTD->Token |= (UINT32)8 << 16;

    // Update buffer pointers
    EhciSetQTDBufferPointers(PollTD, PollED->DataBuffer, 8);

    // Re-init the QH pointers
    PollED->CurqTDPtr = 0;
    PollED->AltNextqTDPtr = EHCI_TERMINATE;

    // Update next & alternate next qTD pointers
    PollTD->NextqTDPtr = EHCI_TERMINATE;
    PollTD->AltNextqTDPtr = EHCI_TERMINATE;
    PollED->NextqTDPtr = (UINT32)(UINTN)PollTD;

    // Restart the qTD
    PollTD->Token |= (QTD_IOC_BIT |
                      QTD_THREE_ERRORS |
                      QTD_ACTIVE);

    return EFI_SUCCESS;
}


/**
    This function starts the periodic schedule for the interrupt endpoint-based
    devices (keyboard).

**/

EFI_STATUS
EFIAPI
EhciHcActivatePolling(
    IN EFI_PEI_SERVICES **PeiServices,
    IN VOID *UsbDev
)
{
    PEI_USB_DEVICE  *PeiUsbDev = (PEI_USB_DEVICE*)UsbDev;
    PEI_EHCI_DEV    *EhciDev = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS(PeiUsbDev->UsbHcPpi);

    EFI_STATUS  Status;
    UINT8       *Ptr;
    EHCI_QH     *PollED;
    EHCI_QTD    *PollTD;
    UINT32      Tmp; 
    UINT32      Tmp1 = 0;
    
/*
    static EhciPollingStarted = FALSE;

    if (EhciPollingStarted) return EFI_ALREADY_STARTED;

    EhciPollingStarted = TRUE;
*/

    // Allocate QH and qTD, making allocation 64-Bytes aligned
    Status = PeiServicesAllocatePool(
                 sizeof(EHCI_QH)+sizeof(EHCI_QTD)+64, 
                 (VOID**)&Ptr 
                 );
    
    ZeroMem(Ptr, sizeof(EHCI_QH) + sizeof(EHCI_QTD) + 64);

    ASSERT(Status == EFI_SUCCESS);
    if (EFI_ERROR(Status)) return Status;

    // 64-Bytes alignment, assume no deallocation will be necessary,
    // because the original pointer is lost here
    Ptr = (UINT8*)((UINTN)Ptr + 0x40); 
    Ptr = (UINT8*)((UINTN)Ptr & ~0x3f);
    EhciDev->EhciDescPtrs.QhInterrupt = (EHCI_QH*)Ptr;
    EhciDev->EhciDescPtrs.QtdInterruptData = (EHCI_QTD*)(Ptr + sizeof(EHCI_QH));

    // Initialize the variables that would reduce further typecasting
    PollED = EhciDev->EhciDescPtrs.QhInterrupt;
    PollTD = EhciDev->EhciDescPtrs.QtdInterruptData;

    DEBUG((DEBUG_INFO, "EhciHcActivatePolling: PollED %x, PollTD %x\n", PollED, PollTD));

    // Setup the polling QH
    // Set the QH's dNextqTDPtr field to polling qTD and dAltqTDPtr field to
    // EHCI_TERMINATE
    PollED->FirstqTD = PollTD;
    PollED->NextqTDPtr = (UINT32)(UINTN)PollTD;
    PollED->AltNextqTDPtr = EHCI_TERMINATE;
    PollED->LinkPointer = EHCI_TERMINATE;

    // Update the endpoint characteristcs field
    Tmp = ((UINT32)PeiUsbDev->DeviceAddress)  |
                    ((UINT32)PeiUsbDev->IntEndpoint << 8);

    Tmp |= ((UINT32)PeiUsbDev->MaxPacketSize0) << 16;// Set max packet size
    Tmp |= (QH_USE_QTD_DT | QH_HEAD_OF_LIST);      // Set the data toggle control
    // Get device speed: 00/01/10 for HI/LO/FULL
    switch (PeiUsbDev->DeviceSpeed) {
        case USB_SLOW_SPEED_DEVICE: Tmp1 = 1; break;
        case USB_FULL_SPEED_DEVICE: Tmp1 = 2; break;
        case USB_HIGH_SPEED_DEVICE: Tmp1 = 0; break;
        default:
            ASSERT(FALSE); // Invalid device speed
    }

    Tmp |= QH_HIGH_SPEED;  // Assume as a high speed device (10b - High speed)

    if (Tmp1)  // Check for HS, if not - create split transaction for FS/LS
    {
        Tmp1 = (Tmp1 & 1) << 12;  // Bit 12 = full/low speed flag
        Tmp &= ~(QH_ENDPOINT_SPEED);
        Tmp |= Tmp1;

        // Set the hub address and port number
        Tmp1 = PeiUsbDev->TransactionTranslator;
        Tmp1 = (Tmp1 << 16) | (BIT10 + BIT11 + BIT12);    // Split complete Xaction
        PollED->EndPntCap |= Tmp1;
    }

    // Update the endpoint characteristcs field with the data formed
    PollED->EndPntCharac = Tmp;

    // Set a bit in interrupt mask
    PollED->EndPntCap |= (BIT0 + QH_ONE_XFER);

// Fill the polling Qtd with relevant information
// The token field will be set so
//   Direction PID = QTD_IN_TOKEN,
//   Size = size of the data,
//   Data Toggle = QTD_DATA0_TOGGLE,
//   Error Count = QTD_THREE_ERRORS,
//   Status code = QTD_ACTIVE
// The buffer pointers field will point to the Buffer buffer
//   which was before initialized to contain a DeviceRequest struc.
// The NextqTDPtr field will point to the QtdControlSetup
// The AltNextqTDPtr field will be set to EHCI_TERMINATE

    PollTD->Token = QTD_IN_TOKEN |
                    QTD_IOC_BIT |
                    QTD_DATA0_TOGGLE |
                    QTD_THREE_ERRORS |
                    QTD_ACTIVE;
    PollTD->Token |= (UINT32)8 << 16;  // Set length

    // Update buffer pointers
    EhciSetQTDBufferPointers(PollTD, PollED->DataBuffer, 8);

    // Update next & alternate next Qtd pointers
    PollTD->NextqTDPtr = EHCI_TERMINATE;
    PollTD->AltNextqTDPtr = EHCI_TERMINATE;

    EhciScheduleQH(EhciDev->EhciDescPtrs.Qh8ms, PollED);

    return EFI_SUCCESS;
}


/**
    This function adds a QH to the frame list

    @param Pointer to the QH to be added
        Absolute pointer to the frame list

    @retval VOID

**/

VOID
EhciAddPeriodicQH(
    EHCI_QH *Qh,
    UINT32  *FrameListPtr)
{
    UINT32 SavAddr = *FrameListPtr;

    // Initialize the QH structure
    Qh->NextqTDPtr = EHCI_TERMINATE;
    Qh->AltNextqTDPtr = EHCI_TERMINATE;
    Qh->EndPntCharac = ((UINT32)0x40 << 16) + QH_HIGH_SPEED;

    // Save the 32bit absolute QH address in the current frame list pointer
    *(UINT32*)FrameListPtr = (UINT32)((UINTN)Qh | EHCI_QUEUE_HEAD);

    // Link the old frame list pointer address in the link pointer of ED
    Qh->LinkPointer = SavAddr | EHCI_QUEUE_HEAD;

}


/**
    This function performs a software reset of the host controller.

        
    @param PeiServices 
        --  EFI_PEI_SERVICES pointer
    @param EhciDevPtr 
        --  PEI_EHCI_DEV pointer

    @retval 
        VOID (Return Value)

    @note  
      It is assumed that all necessary operational register data has been 
      saved prior to calling this function.

**/

VOID
EhciReset (
    EFI_PEI_SERVICES **PeiServices,
    PEI_EHCI_DEV     *EhciDevPtr )
{
    UINT32  UsbCmd;
    UINT32  Count;

    // Check HC is halted: attempting to reset an actively running HC will
    // result in undefined behavior.
    if (EhciDevPtr->EhciHcOpReg->UsbSts.EhciUsbstsUnion.Field.HCHalted == 0) {
        DEBUG((DEBUG_ERROR, "EHCI HC RESET ERROR: HC is running.\n"));
        EhciDevPtr->HcStatus = EHCI_RESET_ERROR;
        return;
    }

    // Issue reset
    UsbCmd = EhciDevPtr->EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits | EHCI_HCRESET;
    EhciDevPtr->EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits = UsbCmd;
    
    // EHCI_HCRESET bit is set to zero by the Host Controller when the reset
    // process is complete.
    for (Count = 0; Count < PEI_EHCI_RESET_TIMEOUT_MS * 10; Count++) {
        if (EhciDevPtr->EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.Field.HcReset == 0) {
            return;
        }
        EHCI_FIXED_DELAY_US(EhciDevPtr, 100);   // 100 us delay
    }

    DEBUG((DEBUG_ERROR, "EHCI HC RESET ERROR: timeout.\n"));
    EhciDevPtr->HcStatus = EHCI_RESET_ERROR;

    return;
}

/**

    @param 

    @retval VOID

**/

VOID
EhciReleasePortOwner (
    EFI_PEI_SERVICES **PeiServices,
    PEI_EHCI_DEV     *EhciDevPtr,
    UINT8            PortNumber
)
{
    EHCI_PORTSC     *PortScReg = &EhciDevPtr->EhciHcOpReg->PortSC[PortNumber - 1];
    UINT32          Index ;
    
    // Clear connect status change bit
    PortScReg->EhciPortscUnion.Field.ConnectStatusChange = 1;
    
    // Release port owner
    PortScReg->EhciPortscUnion.Field.PortOwner = 1;
    for (Index = 0; Index < PEI_EHCI_RELEASE_PORT_TIMEOUT_MS * 10; Index++) {
        if (PortScReg->EhciPortscUnion.Field.ConnectStatusChange != 0) {
            break;
        }
        EHCI_FIXED_DELAY_US(EhciDevPtr, 100);   // 100 us delay
    }
    
    PortScReg->EhciPortscUnion.Field.ConnectStatusChange = 1;       
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
EhciHcGetRootHubPortStatus(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    OUT EFI_USB_PORT_STATUS        *PortStatus
)
{
    PEI_EHCI_DEV    *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This );
    EHCI_PORTSC     *PortScReg = &EhciDevPtr->EhciHcOpReg->PortSC[PortNumber - 1];

    if (PortNumber > EhciDevPtr->NumPorts) {
        return EFI_INVALID_PARAMETER;
    }

    DEBUG((DEBUG_INFO, "EHCI port[%d] status: %08x\n", PortNumber, PortScReg->EhciPortscUnion.AllBits));
    PortStatus->PortStatus = 0;
    PortStatus->PortChangeStatus = 0;

    if (PortScReg->EhciPortscUnion.Field.CurrentConnectStatus != 0 && 
        PortScReg->EhciPortscUnion.Field.PortEnable == 0 &&
        PortScReg->EhciPortscUnion.Field.LineStatus == 0x1) {
        EhciReleasePortOwner(PeiServices, EhciDevPtr, PortNumber);
    }

    if (PortScReg->EhciPortscUnion.Field.CurrentConnectStatus != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_CONNECTION;
        if (PortScReg->EhciPortscUnion.Field.PortEnable != 0) {
            PortStatus->PortStatus |= USB_PORT_STAT_ENABLE;
            PortStatus->PortStatus |= USB_PORT_STAT_HIGH_SPEED;
        }
    }
    if (PortScReg->EhciPortscUnion.Field.ConnectStatusChange != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_CONNECTION;
    }
    if (PortScReg->EhciPortscUnion.Field.PortEnableChange != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_ENABLE;
    }
    if (PortScReg->EhciPortscUnion.Field.OvercurrentActive != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_OVERCURRENT;
    }
    if (PortScReg->EhciPortscUnion.Field.OvercurrentChange != 0) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_OVERCURRENT;
    }
    if (PortScReg->EhciPortscUnion.Field.Suspend != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_SUSPEND;
    }
    if (PortScReg->EhciPortscUnion.Field.PortReset != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_RESET;
    }
    if (PortScReg->EhciPortscUnion.Field.PortPower != 0) {
        PortStatus->PortStatus |= USB_PORT_STAT_POWER;
    }
    if (PortScReg->EhciPortscUnion.Field.PortOwner != 1) {
        PortStatus->PortStatus |= USB_PORT_STAT_OWNER;
    }
    if (EhciDevPtr->PortResetStatusChangeMap & (1 << (PortNumber - 1))) {
        PortStatus->PortChangeStatus |= USB_PORT_STAT_C_RESET;
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
EhciHcGetRootHubPortNumber(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    OUT UINT8                      *PortNumber
)
{

    PEI_EHCI_DEV *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This );
        
    if (PortNumber == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    *PortNumber = EhciDevPtr->NumPorts;

    return EFI_SUCCESS;
}


/**
    This function sets port feature as specified by
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
EhciHcSetRootHubPortFeature(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature
)
{
    PEI_EHCI_DEV *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This ); 
    EHCI_PORTSC     *PortScReg = &EhciDevPtr->EhciHcOpReg->PortSC[PortNumber - 1];
    UINT32          PortSc = 0;
    UINT32          Index;

    if (PortNumber > EhciDevPtr->NumPorts) {
        return EFI_INVALID_PARAMETER;
    }

    PortSc = PortScReg->EhciPortscUnion.AllBits;
    PortSc &= ~(EHCI_CONNECTSTATUSCHANGE | EHCI_PORTENABLESTATUSCHANGE | EHCI_OVERCURRENTCAHGE);

    switch (PortFeature) {
        case EfiUsbPortEnable:
             break;
        
        case EfiUsbPortSuspend:
             PortSc |= EHCI_SUSPEND;
             break;
        
        case EfiUsbPortReset:
             PortSc = PortScReg->EhciPortscUnion.AllBits;
             PortSc &= ~(EHCI_CONNECTSTATUSCHANGE | EHCI_PORTENABLESTATUSCHANGE | EHCI_OVERCURRENTCAHGE);
             PortScReg->EhciPortscUnion.AllBits = (PortSc & ~EHCI_PORTENABLE) | EHCI_PORTRESET;
             EHCI_FIXED_DELAY_MS( EhciDevPtr, 50);   // 50 msec delay
        
             PortSc = PortScReg->EhciPortscUnion.AllBits;
             PortSc &= ~(EHCI_PORTRESET | EHCI_CONNECTSTATUSCHANGE | EHCI_PORTENABLESTATUSCHANGE | 
                                                EHCI_OVERCURRENTCAHGE);
             PortScReg->EhciPortscUnion.AllBits = PortSc;
        
             for (Index = 0; Index < PEI_EHCI_RESET_PORT_TIMEOUT_MS * 10; Index++) {
                 if (PortScReg->EhciPortscUnion.Field.PortReset == 0) {
                     break;
                 }
                     EHCI_FIXED_DELAY_US(EhciDevPtr, 100);   // 100 us delay
             }
        
             if (PortScReg->EhciPortscUnion.Field.PortEnable != 0) {
                 EhciDevPtr->PortResetStatusChangeMap |= (1 << (PortNumber - 1));
             } else {
                 EhciReleasePortOwner(PeiServices, EhciDevPtr, PortNumber);
             }
             //break;
             return EFI_SUCCESS;
        
        case EfiUsbPortPower:
             PortSc |= EHCI_PORTPOWER;
             break; 
        
        default:
        return EFI_INVALID_PARAMETER;
    }
    PortScReg->EhciPortscUnion.AllBits = PortSc;

    return EFI_SUCCESS;
}


/**
    This function clears an EHCI specification port feature as specified
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
EhciHcClearRootHubPortFeature(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature 
)
{
    PEI_EHCI_DEV *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This );
    UINT32 PortSc = 0;

    if (PortNumber > EhciDevPtr->NumPorts) {
        return EFI_INVALID_PARAMETER;
    }

    PortSc = EhciDevPtr->EhciHcOpReg->PortSC[PortNumber - 1].EhciPortscUnion.AllBits;
    PortSc &= ~(EHCI_CONNECTSTATUSCHANGE | EHCI_PORTENABLESTATUSCHANGE | EHCI_OVERCURRENTCAHGE);

    switch (PortFeature) {
        case EfiUsbPortEnable:
             PortSc &= ~EHCI_PORTENABLE;
             break;
        
        case EfiUsbPortSuspend:
             PortSc |= EHCI_FORCEPORTRESUME;
             break;
        
        case EfiUsbPortReset:
             PortSc &= ~EHCI_PORTRESET;
             break;
        
        case EfiUsbPortPower:
             PortSc &= ~EHCI_PORTPOWER;
             break; 
        
        case EfiUsbPortOwner:
             EhciReleasePortOwner(PeiServices, EhciDevPtr, PortNumber);
             return EFI_SUCCESS;
        
        case EfiUsbPortConnectChange:
             PortSc |= EHCI_CONNECTSTATUSCHANGE;
             break;
        
        case EfiUsbPortEnableChange:
             PortSc |= EHCI_PORTENABLESTATUSCHANGE;
             break;
        
        case EfiUsbPortSuspendChange:
             break;
        
        case EfiUsbPortOverCurrentChange:
             PortSc |= EHCI_OVERCURRENTCAHGE;
             break;
        
        case EfiUsbPortResetChange:
             EhciDevPtr->PortResetStatusChangeMap &= ~(1 << (PortNumber - 1));
             return EFI_SUCCESS;
        
        default:
             return EFI_INVALID_PARAMETER;
    }
    EhciDevPtr->EhciHcOpReg->PortSC[PortNumber - 1].EhciPortscUnion.AllBits = PortSc;

    return EFI_SUCCESS;
}


/**
    This routine resets the Host Controler and its USB bus 
    according to the attributes
    @param EFI_PEI_SERVICES            **PeiServices,
        PEI_USB_HOST_CONTROLLER_PPI	*This,
        UINT16                      Attributes

         
    @retval EFI_SUCCESS The reset operation succeeded.
    @retval EFI_UNSUPPORTED The type of reset specified by Attributes is not
        currently supported.
    @retval EFI_ACCESS_DENIED Reset operation is rejected due to the debug 
        port being configured and active; only
        EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG or 
        EFI_USB_HC_RESET_HOST_WITH_DEBUG reset Attributes
        can be used to perform reset operation for this 
        host controller.

**/

EFI_STATUS
EFIAPI
EhciHcReset(
  IN EFI_PEI_SERVICES                   **PeiServices,
  IN PEI_USB_HOST_CONTROLLER_PPI        *This,
  IN UINT16                         Attributes
)
{    
    UINTN            Index;
    PEI_EHCI_DEV     *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS (This);     
    EHCI_HC_OPER_REG *EhciHcOpReg = EhciDevPtr->EhciHcOpReg;
    UINT64           Val64;
        
    switch (Attributes) {
        case EFI_USB_HC_RESET_GLOBAL:   
             // Stop periodic scheduling
             EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits &= ~EHCI_PER_SCHED_ENABLE;
             for (Index = 0; Index < PEI_EHCI_RESET_TIMEOUT_MS * 10; Index++) {
                 if (EhciHcOpReg->UsbSts.EhciUsbstsUnion.Field.PeriodicSheduleStatus == 0) {
                     break;
                 }
                 EHCI_FIXED_DELAY_US(EhciDevPtr, 100);   // 100 us
             }
        
            // Check HC is runnning, if so STOP before proceeding       
            if (EhciHcOpReg->UsbSts.EhciUsbstsUnion.Field.HCHalted == 0) {
                EhciHcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits &= ~(EHCI_RUNSTOP);
                for (Index = 0; Index < 16; Index++) {
                    EHCI_FIXED_DELAY_US(EhciDevPtr, 125);   // 125 us
                    if (EhciHcOpReg->UsbSts.EhciUsbstsUnion.Field.HCHalted) break;
                }
            }

            if (EhciDevPtr->UsbHostControllerPpi.DebugPortUsed)
                return EFI_ACCESS_DENIED; 
            
            // Reset Host Controller
            EhciReset (PeiServices, EhciDevPtr);

            Val64 = 0;

            // Check flag 'EhciDevPtr->FreeResource' and clear resource
            if (EhciDevPtr->FreeResource) {	
                // Clear PCI_BAR0
                (*PeiServices)->PciCfg->Write(
                                  (CONST EFI_PEI_SERVICES**)PeiServices, 
                                  (*PeiServices)->PciCfg,
                                  EfiPeiPciCfgWidthUint32,
                                  EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Bus, 
                                  gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Device, 
                                  gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Function, 
                                  EHCI_BASE_ADDR_REG ),
                                  &Val64);
			
                // Clear PCI_CMD
                (*PeiServices)->PciCfg->Write(
                                  (CONST EFI_PEI_SERVICES**)PeiServices, 
                                  (*PeiServices)->PciCfg,
                                  EfiPeiPciCfgWidthUint8,
                                  EFI_PEI_PCI_CFG_ADDRESS( gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Bus, 
                                  gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Device, 
                                  gEhciControllerPciTable[EhciDevPtr->ControllerIndex].Function, 
                                  EHCI_CMD_REGISTER ),
                                  &Val64);
            }
			
            break;
        default:
            return EFI_UNSUPPORTED;
	}

    return EFI_SUCCESS;    
}


/**
    This function initializes the queue head with default values

    @param QH    Pointer to queue head

**/

VOID
EhciInitializeQueueHead(EHCI_QH *QH)
{
    QH->NextqTDPtr       = 1;
    QH->AltNextqTDPtr    = 1;
    QH->CurqTDPtr        = 1;

    QH->EndPntCap        = QH_ONE_XFER;
    QH->Token            = 0;
    QH->EndPntCharac     = 0;
    QH->BufferPtr0       = 0;
    QH->BufferPtr1       = 0;
    QH->BufferPtr2       = 0;
    QH->BufferPtr3       = 0;
    QH->BufferPtr4       = 0;
    QH->ErrorStatus      = 0;
}


/**
    This function will set the 5 buffer pointer in the Qtd
    appropriately depending upon the input size

    @param Qtd   - Pointer to the Qyd
        Buf   - 32bit absolute buffer pointer
        Size   - Amount of data to be transferred

    @retval VOID

**/

VOID
EhciSetQTDBufferPointers(
    EHCI_QTD    *Qtd,
    UINT8       *Buf,
    UINT32      Size
)
{
    UINT16      BufSize;
    UINT8       *Buffer   = Buf;
    UINT32      *BufferPtr;
    UINT16      Mem4KRemainder;

    //
    // Fill the buffer pointers with 0s
    //
    Qtd->BufferPtr0      = 0;
    Qtd->BufferPtr1      = 0;
    Qtd->BufferPtr2      = 0;
    Qtd->BufferPtr3      = 0;
    Qtd->BufferPtr4      = 0;
    Qtd->AltNextqTDPtr   = 1;

    //
    // If size to transfer is 0 skip updating pointers
    //
    if (!Size)
    {
        return;
    }

    //
    // Make sure the amount of data to be xferred is 16K or less
    //
    BufSize = (UINT16)((Size > PEI_MAX_EHCI_DATA_SIZE) ? PEI_MAX_EHCI_DATA_SIZE : Size);

    BufferPtr = &Qtd->BufferPtr0;

    for (;;) {
        *BufferPtr = (UINT32)(UINTN)Buffer;
        //
        // Calculate the number of bytes that can be transferred using current
        // buffer pointer
        //
        Mem4KRemainder = (UINT16)((((UINT32)((UINTN)Buffer+0x1000)) & 0xFFFFF000) -
                                        (UINT32)(UINTN)Buffer);

        //
        // Check whether all the bytes can be accomadated in the current buffer
        //
        if (Mem4KRemainder >= BufSize)
        {
            break;  // Yes. Current Buffer is sufficient for the rest of data
        }

        //
        // We have more data to transfer - adjust data and store it in the next pointer
        //
        BufSize = (UINT16)(BufSize - Mem4KRemainder);   // Amount of data remaining
        Buffer = Buffer + Mem4KRemainder;     // Adjust buffer (4K bound)
        BufferPtr++;                          // Next buffer pointer
    }
}


/**
    This function starts the asynchronous schedule

**/

VOID
EhciStartAsyncSchedule(
    EHCI_HC_OPER_REG    *HcOpReg
)
{
    // Start the Async schedule
    HcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits |= EHCI_ASYNC_SCHED_ENABLE;

    // Make sure the HC started the async. execution
    for (;HcOpReg->UsbSts.EhciUsbstsUnion.Field.AsyncSheduleStatus == 0;) {}
}


/**
    This function stops the asynchronous transfer and sets the
    asynchronous pointer to null

**/

VOID
EhciStopAsyncSchedule(
    EHCI_HC_OPER_REG    *HcOpReg
)
{
    // Stop the Async schedule
    HcOpReg->UsbCmd.EhciUsbcmdUnion.AllBits &= ~EHCI_ASYNC_SCHED_ENABLE;

    // Make sure the HC stopped the async. execution
    for (;HcOpReg->UsbSts.EhciUsbstsUnion.Field.AsyncSheduleStatus != 0;) {}
}


/**
    This function whether all the TD's in the QH is completed

    @param QH    - Pointer to the QH which has to be completed

**/

VOID
EhciProcessQH(
    EHCI_QH *QH
)
{
    EHCI_QTD *QTD = QH->FirstqTD;

    for (;;) {
        //
        // Check whether the Qtd is active, if so. Exit!
        //
        if (QTD->Token & QTD_ACTIVE) {
            return; // Not complete
        }

        //
        // Check for halt condition, if halted - exit
        //
        if (QTD->Token & QTD_HALTED) {
            //
            // Set the QH halted status
            //
            QH->ErrorStatus = QTD_HALTED;
            //
            // Set the QH as in-active
            //
            QH->Active = FALSE;

            return; // Complete
        }
        //
        // Qtd is not active and not halted. That is it is completed successfully
        // Check whether this Qtd is the last one in the list
        //
        if (QTD->NextqTDPtr & EHCI_TERMINATE) {
            //
            // Set the QH as in-active
            //
            QH->Active = FALSE;
            return; //  Complete
        }
        //
        // More qTDs are in the list. Process next qTD
        //
        QTD = (EHCI_QTD*)(UINTN)QTD->NextqTDPtr;
    }
}


/**
    This function waits for asynchronous transfer completion.

**/

VOID
EhciWaitForAsyncTransferComplete (
    EFI_PEI_SERVICES    **PeiServices,
    PEI_EHCI_DEV        *EhciDevPtr,
    EHCI_QH             *QHead,
    UINT32              TimeOut
)
{
    UINT32              Count;

    for (Count = 0; Count < TimeOut; Count++) {
        EhciProcessQH(QHead);

        if (QHead->Active == FALSE) {
            return;
        }
        EHCI_FIXED_DELAY_MS( EhciDevPtr, 1);   // 1 msec delay
    }

    DEBUG((DEBUG_ERROR, "EHCI Time-Out:\n"));
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
    @param DeviceSpeed 
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

EFI_STATUS
EFIAPI
EhciHcControlTransfer(
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
    UINT16            WordRequest;
    EFI_STATUS        Status = EFI_SUCCESS;
    PEI_EHCI_DEV        *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS(This);
    EHCI_HC_OPER_REG    *HcOpReg = EhciDevPtr->EhciHcOpReg;
    EHCI_DESC_PTRS      *DescPtrs = &EhciDevPtr->EhciDescPtrs;
    UINT16              Length = (DataLength != NULL)? (UINT16) *DataLength : 0;
    EHCI_QH             *QhCtl;
    EHCI_QTD            *QtdCtlSetup;
    EHCI_QTD            *QtdCtlData;
    EHCI_QTD            *QtdCtlStatus;
    UINT32              Tmp;
    UINT32              Tmp1;

    *TransferResult = EFI_USB_NOERROR;

    WordRequest = (Request->Request << 8) | Request->RequestType;

    //
    // Intialize the queue head with null pointers
    //
    QhCtl = DescPtrs->QhControl;
    EhciInitializeQueueHead(QhCtl);

    //
    // Assume as a high speed device
    //
    Tmp = QH_HIGH_SPEED;   // 10b - High speed

    if (DeviceSpeed != USB_HIGH_SPEED_DEVICE && TransactionTranslator != 0)
    {
        // Low/Full speed device OR device is connected to a root port
        // DeviceSpeed = 1 (low) or 2 (full)
        Tmp = (UINT32)((DeviceSpeed & 1) << 12);    // Bit 12 = full/low speed flag
        Tmp |= QH_CONTROL_ENDPOINT;
        //
        // Set the hub address and port number
        //
        Tmp1 = (TransactionTranslator << 16) | (BIT10+BIT11+BIT12);    // Split complete Xaction
        QhCtl->EndPntCap |= Tmp1;
    }

    Tmp |= (QH_USE_QTD_DT | QH_HEAD_OF_LIST);
    Tmp |= (UINT32)DeviceAddress;

    //
    // dTmp[Bits 6:0] = Dev. Addr
    // dTmp[Bit7] = I bit(0)
    // dTmp[Bits11:8] = Endpoint (0)
    //
    Tmp1 = MaximumPacketLength;
    Tmp |= (Tmp1 << 16);  // Tmp[Bits26:16] = device's packet size
    QhCtl->EndPntCharac = Tmp;

    //
    // Fill in various fields in the qTDControlSetup.
    //
    QtdCtlSetup = DescPtrs->QtdControlSetup;

    //
    // The token field will be set so
    //   Direction PID = QTD_SETUP_TOKEN,
    //   Size = size of the data,
    //   Data Toggle = QTD_SETUP_TOGGLE,
    //   Error Count = QTD_NO_ERRORS,
    //   Status code = QTD_DO_OUT + QTD_ACTIVE
    // The buffer pointers field will point to the ControlSetupData buffer
    //   which was before initialized to contain a DeviceRequest struc.
    // The NextqTDPtr field will point to the QtdControlData if data will
    //   be sent/received or to the qTDControlStatus if no data is expected.
    // The AltNextqTDPtr field will be set to EHCI_TERMINATE
    //
    QtdCtlSetup->Token = QTD_SETUP_TOKEN | QTD_SETUP_TOGGLE | QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_DO_OUT | QTD_ACTIVE | 
                (8 << 16);  // Data size

    //
    // Update buffer pointers
    //
    EhciSetQTDBufferPointers(QtdCtlSetup,
            (UINT8*)Request,
            8);
    QtdCtlData = DescPtrs->QtdControlData;

    if (Length != 0 && DataBuffer != NULL)    // br if no data to transfer
    {
        //
        // Fill in various fields in the QtdControlData
        //
        // The token field will be set so
        //   Direction PID = QTD_OUT_TOKEN/QTD_IN_TOKEN,
        //   Size = size of the data,
        //   Data Toggle = QTD_DATA1_TOGGLE,
        //   Error Count = QTD_NO_ERRORS,
        //   Status code = QTD_DO_OUT(if it is out) + QTD_ACTIVE
        // The buffer pointers field will point to the Buffer buffer
        //   which was before initialized to contain a DeviceRequest struc.
        // The dNextqTDPtr field will point to the qTDControlSetup
        // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
        //
        QtdCtlData->Token = QTD_IN_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_ACTIVE;
        if ((WordRequest & BIT7) == 0) // Br if host sending data to device (OUT)
        {
            QtdCtlData->Token    = QTD_OUT_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
        }

        //
        // Set length
        //
        QtdCtlData->Token |= ((UINT32)Length << 16);

        //
        // Update buffer pointers
        //
        EhciSetQTDBufferPointers(QtdCtlData,
                (UINT8*)DataBuffer,
                (UINT32)Length);
    }

    //
    // Fill in various fields in the qTDControlStatus
    //
    QtdCtlStatus = DescPtrs->QtdControlStatus;

    //
    // The token field will be set so
    //   Direction PID = QTD_OUT_TOKEN/QTD_IN_TOKEN,
    //   Size = 0,
    //   Data Toggle = QTD_DATA1_TOGGLE,
    //   Error Count = QTD_NO_ERRORS,
    //   Status code = QTD_DO_OUT(if it is out) + QTD_ACTIVE
    // The buffer pointers field will be 0
    // The dNextqTDPtr field will set to EHCI_TERMINATE
    // The dAltNextqTDPtr field will be set to EHCI_TERMINATE
    //
    // For OUT control transfer status should be IN and
    // for IN cotrol transfer, status should be OUT
    //
    QtdCtlStatus->Token = QTD_IN_TOKEN | 
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_ACTIVE;
    if((WordRequest & BIT7) != 0)
    {
        QtdCtlStatus->Token  = QTD_OUT_TOKEN |
                QTD_DATA1_TOGGLE | QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
    }

    EhciSetQTDBufferPointers(QtdCtlStatus, NULL, 0);

    //
    // Link the Qtd formed now and connect them with the control queue head
    //
    QhCtl->FirstqTD     = QtdCtlSetup;
    QhCtl->NextqTDPtr    = (UINT32)(UINTN)QtdCtlSetup;

    if (Length != 0)
    {
        QtdCtlSetup->NextqTDPtr  = (UINT32)(UINTN)QtdCtlData;
        QtdCtlData->NextqTDPtr   = (UINT32)(UINTN)QtdCtlStatus;
    }
    else
    {
        QtdCtlSetup->NextqTDPtr  = (UINT32)(UINTN)QtdCtlStatus;
    }

    QtdCtlStatus->NextqTDPtr = EHCI_TERMINATE;

    //
    // Set the ASYNCLISTADDR register to point to the QHControl
    //
    HcOpReg->AsyncListAddr = (UINT32)(UINTN)QhCtl;

    //
    // Set next QH pointer to itself (circular link)
    //
    QhCtl->LinkPointer = (UINT32)((UINTN)QhCtl | EHCI_QUEUE_HEAD);
    QhCtl->Active = TRUE;

    //
    // Now put the control setup, data and status into the HC's schedule by
    // setting the Async. schedule enabled field of USBCMD register
    // This will cause the HC to execute the transaction in the next active frame.
    //
    EhciStartAsyncSchedule(HcOpReg);

    EhciWaitForAsyncTransferComplete(PeiServices, EhciDevPtr, QhCtl, TimeOut);

    //
    // Stop the Async transfer
    //
    EhciStopAsyncSchedule(HcOpReg);

    //
    // Check whether the QH stopped or timed out
    //
    if (QhCtl->Active == TRUE) {

        QhCtl->Active = FALSE;
        Status = EFI_TIMEOUT;
        *TransferResult |= EFI_USB_ERR_TIMEOUT;
    }

    //
    // Check for the stall condition
    //
    if (QhCtl->ErrorStatus & QTD_HALTED) {
        //
        // Command stalled set the error bit appropriately
        //
        Status = EFI_DEVICE_ERROR;
        *TransferResult |= EFI_USB_ERR_STALL;
    }

    QhCtl->FirstqTD     = 0;
    QhCtl->NextqTDPtr    = EHCI_TERMINATE;

    return  Status;
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
EhciHcBulkTransfer(
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
    PEI_EHCI_DEV        *EhciDevPtr = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This );
    EHCI_HC_OPER_REG    *HcOpReg = EhciDevPtr->EhciHcOpReg;
    EHCI_DESC_PTRS      *DescPtrs = &EhciDevPtr->EhciDescPtrs;
    EFI_STATUS          Status = EFI_SUCCESS;
    UINT32              BytesToTransfer;
    UINT32              Tmp, Tmp1;
    EHCI_QH             *QHBulk;
    EHCI_QTD            *QTDBulkData;

    *TransferResult = EFI_USB_NOERROR;

    //DEBUG((DEBUG_INFO, "bulk..%x, device address %d\n", *DataLength, DeviceAddress));

    BytesToTransfer =
        (*DataLength < PEI_MAX_EHCI_DATA_SIZE)? (UINT32)*DataLength : PEI_MAX_EHCI_DATA_SIZE;

    //
    // Set the QH's NextqTDPtr field to bulk data qTD and dAltqTDPtr field to
    // EHCI_TERMINATE. Also set QH's link pointer to itself
    //
    QHBulk = DescPtrs->QhBulk;
    QTDBulkData = DescPtrs->QtdBulkData;

    //
    // Intialize the queue head
    //
    EhciInitializeQueueHead(QHBulk);

    //
    // Set the first qTD pointer
    //
    QHBulk->FirstqTD    = QTDBulkData;
    QHBulk->NextqTDPtr   = (UINT32)(UINTN)QTDBulkData;
    QHBulk->LinkPointer  = (UINT32)((UINTN)QHBulk | EHCI_QUEUE_HEAD);

    //
    // Device address, Endpoint, max packet size, data toggle control
    //
    Tmp = (UINT32)(DeviceAddress | (EndPointAddress << 8));
    Tmp |= ((UINT32)MaximumPacketLength << 16);
    Tmp |= (QH_USE_QTD_DT | QH_HEAD_OF_LIST);

    //
    // Assume as a high speed device
    //
    Tmp |= QH_HIGH_SPEED;   // 10b - High speed

    if (DeviceSpeed != USB_HIGH_SPEED_DEVICE && TransactionTranslator != 0)
    {
        // Note: low speed bulk endpoints are not supported
        Tmp1 = BIT12;    // Bit 12 = full speed flag
        Tmp &= ~(QH_ENDPOINT_SPEED);
        Tmp |= Tmp1;
            //
            // Set the hub address and port number
            //
        Tmp1   = (TransactionTranslator << 16) | BIT14;    // Hispeed hub port number & device number
        QHBulk->EndPntCap |= Tmp1;   // Split complete Xaction
    }

    //
    // Update the endpoint characteristcs field with the data formed
    //
    QHBulk->EndPntCharac = Tmp;

    //
    // Fill the bulk data qTD with relevant information
    //
    if ((EndPointAddress & BIT7) != 0)
    {
        QTDBulkData->Token   = QTD_IN_TOKEN |
                QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_ACTIVE;
    }
    else
    {
        QTDBulkData->Token   = QTD_OUT_TOKEN |
                QTD_IOC_BIT |
                QTD_NO_ERRORS | QTD_DO_OUT | QTD_ACTIVE;
    }

    //
    // Set the data toggle depending on the DatToggle value
    //
    QTDBulkData->Token |= ((UINT32)(*DataToggle)) << 31;

    //
    // Set length
    //
    QTDBulkData->Token |= (BytesToTransfer << 16);

    //
    // Update buffer pointers
    //
    EhciSetQTDBufferPointers(
        QTDBulkData, (UINT8*)DataBuffer, BytesToTransfer);

    //
    // Update next & alternate next qTD pointers
    //
    QTDBulkData->NextqTDPtr      = EHCI_TERMINATE;
    QTDBulkData->AltNextqTDPtr   = EHCI_TERMINATE;

    //
    // Set the ASYNCLISTADDR register to point to the QHBulk
    //
    HcOpReg->AsyncListAddr = (UINT32)(UINTN)QHBulk;

    QHBulk->Active   = TRUE;

    //
    // Now put the bulk QH into the HC's schedule by
    // setting the Async. schedule enabled field of USBCMD register
    // This will cause the HC to execute the transaction in the next active frame.
    //
    EhciStartAsyncSchedule(HcOpReg);

    EhciWaitForAsyncTransferComplete(PeiServices, EhciDevPtr, QHBulk, TimeOut);

    //
    // Stop the Async transfer
    //
    EhciStopAsyncSchedule(HcOpReg);

    Tmp = 0;    // Return value

    //
    // Check whether the QH stopped or timed out
    //
    if (QHBulk->Active == TRUE) {

        QHBulk->Active = FALSE;

        //
        // Set time out status
        //
        Status = EFI_TIMEOUT;
        *TransferResult |= EFI_USB_ERR_TIMEOUT;
    }

    //
    // Check for the error conditions - if possible recover from them
    //
    if (QHBulk->ErrorStatus & QTD_HALTED) {
        //
        // Indicate Stall condition
        //
        Status = EFI_DEVICE_ERROR;
        *TransferResult |= EFI_USB_ERR_STALL;
    }

    if (Status == EFI_SUCCESS) {

        *DataToggle = (UINT8)(((QHBulk->Token & QH_DATA_TOGGLE) >> 31) & 1);
        //
        // Get the size of data transferred
        //
        Tmp = (QTDBulkData->Token & ~(QTD_DATA_TOGGLE)) >> 16;
        Tmp = (Tmp != 0)? BytesToTransfer-Tmp : BytesToTransfer;
    }

    QHBulk->FirstqTD = 0;
    QHBulk->NextqTDPtr = EHCI_TERMINATE;

    *DataLength = (UINTN)Tmp;
    return  Status;
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
EhciHcSyncInterruptTransfer(
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
    PEI_EHCI_DEV    *EhciDev = PEI_RECOVERY_USB_EHCI_DEV_FROM_THIS( This );
    UINTN           Count;
    EFI_STATUS      Status;
    UINT8           *Src;
    UINT8           *Dst;

    if (Data == NULL || DataLength == NULL) {
        ASSERT(FALSE);
        return EFI_INVALID_PARAMETER;
    }

    for (Count = 0, Status = EFI_NOT_READY; Count < TimeOut; Count++)
    {
        Status = EhciProcessPeriodicList(PeiServices,
            EhciDev->EhciDescPtrs.QhInterrupt,
            EhciDev->EhciDescPtrs.QtdInterruptData);

        if (Status == EFI_SUCCESS) break;

        EHCI_FIXED_DELAY_MS(EhciDev, 1);  // 1 msec
    }

    if (EFI_ERROR(Status)) return EFI_TIMEOUT;

    // Get the data and return success
    for (Src = EhciDev->EhciDescPtrs.QhInterrupt->DataBuffer,
         Dst = (UINT8*)Data,
         Count = 0; Count < 8; Count++)
    {
        *Dst++ = *Src++;
    }

    return EFI_SUCCESS;

}


/**
    This routine reads a DWORD from the specified Memory Address

    @param BaseAddr   - Memory address to read
        bOffset     - Offset of dBaseAddr

    @retval Value read

**/

UINT32
DwordReadMem(
    UINT32 BaseAddr,
    UINT16 Offset)
{
    return *(volatile UINT32*)(UINTN)(BaseAddr+Offset);
}


/**
    This routine writes a DWORD to a specified Memory Address

    @param dBaseAddr   - Memory address to write
        bOffset     - Offset of dBaseAddr
        dValue      - Data to write

**/

VOID
DwordWriteMem(
    UINT32 BaseAddr,
    UINT16 Offset,
    UINT32 Value)
{
    *(volatile UINT32*)(UINTN)(BaseAddr+Offset) = Value;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
