//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file HddSecurity.c
    HDD Security SAT3 Protocol Support Implementation.

**/

#include <HddSecurity.h>

//Global Buffers used for SMM Communication 
EFI_SMM_COMMUNICATION_PROTOCOL *gSmmCommunication = NULL;

UINT8     *gHddSecCommunicateBuffer = NULL;
UINT8     *gHddSecCommunicateData = NULL;
EFI_EVENT gNvmeEvtBootScript = NULL;
EFI_EVENT gHddEfiBootScriptEvt = NULL;
EFI_EVENT gReadytoBootEvent = NULL;
EFI_EVENT gHddLegacyBootScriptEvt = NULL;
UINT32    gNvmeSaveEntryCount = 0;

BOOLEAN   gSmmHddSecuritySupport = SMMHDDSECURITY_SUPPORT;
BOOLEAN   gNvmeSavePciBridgeRegs = SAVE_PCI_BRIDGE_REGS;
BOOLEAN   gSat3SendFreezeLockOnS3 = SAT3_FREEZE_LOCK_ON_S3;

EFI_GUID  gNvmeSecurityBootScriptSaveTriggerGuid = AMI_NVME_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID;
EFI_GUID  gHddSecurityBootScriptSaveTriggerGuid = AMI_HDD_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID;
EFI_GUID  gSaveHddPasswordGuid = EFI_SMM_SAVE_HDD_PASSWORD_GUID;
EFI_GUID  gRemoveHddPasswordGuid = EFI_SMM_REMOVE_HDD_PASSWORD_GUID;
EFI_GUID  gBeforeBootGuid = AMITSE_EVENT_BEFORE_BOOT_GUID;
EFI_GUID  gHddSecuritySendCommandDataBufferGuid = AMI_HDD_SECURITY_SEND_COMMAND_DATA_BUFFER_GUID;

extern EFI_GUID gIdeSecurityPwNvguid;

// PciCfg register values for PCI bridge
BOOT_SCRIPT_NVME_REG_SAVE gPciBridgeRegistersSave[] = {
  { PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,     EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x18
  { PCI_ROOT_BRIDGE_IO_OFFSET,                  EfiBootScriptWidthUint16,   MAX_UINT16 }, // 0x1C
  { PCI_ROOT_BRIDGE_MEM_OFFSET,                 EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x20
  { PCI_ROOT_BRIDGE_PFMEM_OFFSET,               EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x24
  { PCI_COMMAND_OFFSET,                         EfiBootScriptWidthUint8,    MAX_UINT8  }, // 0x04
};

// PciCfg register values for NVMe device
BOOT_SCRIPT_NVME_REG_SAVE gNvmeControllerRegistersSave[] = {
  { PCI_BASE_ADDRESSREG_OFFSET,                 EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x10
  { PCI_BASE_ADDRESSREG_OFFSET + 4,             EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x14
  { PCI_BASE_ADDRESSREG_OFFSET + 8,             EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x18
  { PCI_BASE_ADDRESSREG_OFFSET + 12,            EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x1C
  { PCI_BASE_ADDRESSREG_OFFSET + 16,            EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x20
  { PCI_BASE_ADDRESSREG_OFFSET + 20,            EfiBootScriptWidthUint32,   MAX_UINT32 }, // 0x24
  { PCI_COMMAND_OFFSET,                         EfiBootScriptWidthUint8,    MAX_UINT8  }, // 0x04
};

#define TOTAL_REGISTERS_COUNT ((sizeof(gPciBridgeRegistersSave) / sizeof(BOOT_SCRIPT_NVME_REG_SAVE)) + \
                               (sizeof(gNvmeControllerRegistersSave) / sizeof(BOOT_SCRIPT_NVME_REG_SAVE)))
        
BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY gNvmeSaveEntry[TOTAL_REGISTERS_COUNT * MAX_NVME_DEVICES];

/**
    This function allocates Runtime memory for SMM communication buffer
    when SMM HDD security support enabled.

    @param NONE

    @retval 
        EFI_SUCCESS         Runtime memory allocated
        EFI_ERROR           Out of resource.
**/
EFI_STATUS
AllocateSmmCommunicateBuffer ()
{

    UINTN           HddSecCommunicateBufferSize;
    
    //return success if SMM support is disabled.
    if (!gSmmHddSecuritySupport) {
        return EFI_SUCCESS;
    }     

    // Buffers Allocated for SMM Communication As new core doesn't allow Buffers which are allocated after EndofDXE.
    // Maximum Size of Buffer allocated for reuse
    HddSecCommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + HDD_PASSWORD_SIZE + sizeof (UINT8 *) + (2 * IDE_PASSWORD_LENGTH) +
                                   (sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY) * MAX_NVME_DEVICES * TOTAL_REGISTERS_COUNT) + (2 * sizeof(UINT32));

    // Allocate Memory for Communication buffer.   
    gHddSecCommunicateBuffer = AllocateRuntimePool (HddSecCommunicateBufferSize);
    
    if (gHddSecCommunicateBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    gHddSecCommunicateData = AllocateReservedPool (512);

    if (gHddSecCommunicateData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}

/** @internal
    Triggers SMM Communication event to save SwSmi port address and 
    HddSecurity password Unlock SMI handler context in BootScript table.
    During S3 resume using this stored boot script data an SMI 
    will be generated that unlocks the drive. Then unregisters SMI handlers that Stores 
    and Removes password in SMRAM.
        
    @param Event      Event whose notification function is being invoked.
    @param *Context   Pointer to the notification function's context.
         
    @retval VOID

    @note  Unlock SMI handler will be called only if HDD loses power in S3 state. 
           A SW SMI will be created during S3 resume, to unlock the HDD and put it in
           Freeze state.
           
    @endinternal

**/
VOID
EFIAPI
StoreUnlockSmiContextInBootScript (
    IN  EFI_EVENT               Event,
    IN  VOID                    *Context
)
{
    EFI_STATUS                  Status;
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader;
    static BOOLEAN              BootScriptStored = FALSE;
    UINTN                       CommunicateBufferSize;
    UINT64                      SmiUnRegSignature = HDD_SEC_SMI_UNREGISTER_SIGNATURE;

    if (BootScriptStored) {
        gBS->CloseEvent (Event);
        return;
    }

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof (UINT8 *);
    
    ZeroMem (gHddSecCommunicateBuffer, CommunicateBufferSize);
    
    // Copy SMM Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gHddSecCommunicateBuffer;
    CopyMem (&SmmCommunicateHeader->HeaderGuid, &gHddSecurityBootScriptSaveTriggerGuid, sizeof(EFI_GUID));
    
    //Notification call to store boot script data. Only message length update and no message data
    SmmCommunicateHeader->MessageLength = sizeof(UINT8 *);

    if (gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (
                            &gEfiSmmCommunicationProtocolGuid,
                            NULL,
                            (VOID **)&gSmmCommunication );
        if (EFI_ERROR(Status)) {
            return;  
        }
    }

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );
    if (EFI_ERROR(Status)) {
        return;  
    }
    
    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof(SmiUnRegSignature);
    ZeroMem (gHddSecCommunicateBuffer, CommunicateBufferSize);
        
    // UnRegister Save Password SMI handler
    CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gSaveHddPasswordGuid);
    CopyMem (&SmmCommunicateHeader->Data, &SmiUnRegSignature, sizeof(SmiUnRegSignature));
    SmmCommunicateHeader->MessageLength  = sizeof(SmiUnRegSignature);

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );
    if (EFI_ERROR(Status)) {
        return;
    }
    
    // Now UnRegister Remove Password SMI handler
    CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gRemoveHddPasswordGuid);

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );
    if (EFI_ERROR(Status)) {
        return;
    }
    
    // Free the RT service memory buffer that is allocated for SMM communication operation.
    if (gHddSecCommunicateBuffer != NULL) {
        gBS->FreePool(gHddSecCommunicateBuffer);
        gHddSecCommunicateBuffer = NULL;
    }

    BootScriptStored = TRUE;

    gBS->CloseEvent(Event);
}

/** @internal
    Copies Pci Registers from NvmeController or PCI Bridge devices 
    to S3 Buffer Structure for saving Data in Boot script.

    @param PciAddr     Physical PCI Address of register to be stored
    @param Width       Width of the data to be stored
    @param Value       Value to be saved for Boot script
        
    @retval EFI_SUCCESS              PciRegisters are copied successfully to S3 Buffer Structure.
    @retval EFI_OUT_OF_RESOURCES     If the NvmeSaveEntryCount is greater than allocated buffer size.

    @endinternal
**/
EFI_STATUS
CopyPciDataToBootScriptBuffer (
    IN UINTN                          Segment,
    IN UINTN                          PciAddr,
    IN EFI_BOOT_SCRIPT_WIDTH           Width,
    IN UINTN                           Value
)
{

    DEBUG((DEBUG_VERBOSE, "HddSecurity: CopyPciDataToBootScriptBuffer - gNvmeSaveEntryCount:%x Segment:%x PciAddr:%x Width:%x Value:%x\n",
          gNvmeSaveEntryCount, Segment, PciAddr, Width, Value ));
    
    if (gNvmeSaveEntryCount >= (TOTAL_REGISTERS_COUNT * MAX_NVME_DEVICES)) {
        ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
        return EFI_OUT_OF_RESOURCES;
    }

    // Save the bootScript save entries to the array list
    gNvmeSaveEntry[gNvmeSaveEntryCount].Segment = Segment;
    gNvmeSaveEntry[gNvmeSaveEntryCount].PciAddress = PciAddr;
    gNvmeSaveEntry[gNvmeSaveEntryCount].Width = Width;
    gNvmeSaveEntry[gNvmeSaveEntryCount].Value = Value;
    gNvmeSaveEntryCount++;
    
    return EFI_SUCCESS;
}
/** @internal
    Function stores PCI root port / P2P bridge BAR, CMD, BUS PCI Configuration values to BootScript

    @param PciIo     Pointer to PCI IO protocol

    @retval EFI_SUCCESS           PCI bridge BAR,CMD, BUS PCI Configuration values
                                  are stored successfully. 
    @retval EFI_NOT_FOUND         No protocol instances were found that match Protocol and
                                  Registration.
    
    @endinternal
**/

EFI_STATUS
StorePciBridgePciCfgRegs (
    EFI_PCI_IO_PROTOCOL     *PciIo
)
{
    EFI_STATUS              Status;
    UINTN                   Data32;
    UINTN                   Index;
    UINTN                   PciSeg, PciBus, PciDev, PciFunc;
    UINT64                  PciAddress;
    

    Status = PciIo->GetLocation (
                            PciIo, 
                            &PciSeg, 
                            &PciBus, 
                            &PciDev, 
                            &PciFunc);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    for (Index = 0; Index < (sizeof(gPciBridgeRegistersSave) / sizeof(BOOT_SCRIPT_NVME_REG_SAVE)); Index++) {

        PciAddress = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS (PciBus, PciDev, PciFunc, gPciBridgeRegistersSave[Index].RegNum);
        
        Status = PciIo->Pci.Read (
                                PciIo,
                                gPciBridgeRegistersSave[Index].Width,
                                gPciBridgeRegistersSave[Index].RegNum,
                                1,
                                &Data32);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        Data32 &= gPciBridgeRegistersSave[Index].Mask;
        

        // Copy Root port/P2P Bridge PCI Data to be saved in BootScript to entry list one by one to transfer to Smm
        Status = CopyPciDataToBootScriptBuffer (
                                            PciSeg,
                                            (UINTN)PciAddress,
                                            gPciBridgeRegistersSave[Index].Width,
                                            Data32 );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    return EFI_SUCCESS;
}

/** @internal
    It uses EFI_SMM_COMMUNICATION_PROTOCOL API to transfer NVME BootScript data from 
    Non-SMM mode to SMM mode.

    @param pData      Pointer to data to be transfered
    @param DataSize   Size of the data
    @param pGuid      Pointer to GUID identifier for the data
        
    @retval EFI_SUCCESS             Successfully transfered data from Non-SMM mode
                                    NVME BootScript Data to SMM mode.
    @retval EFI_INVALID_PARAMETER   The given data is invalid.

    @endinternal
**/
EFI_STATUS
TransferNvmeBootScriptDataToSmm ( 
    IN VOID                     *pData, 
    IN UINTN                    DataSize, 
    IN EFI_GUID                 *pGuid 
)
{
    EFI_STATUS                     Status;
    EFI_SMM_COMMUNICATE_HEADER     *SmmCommunicateHeader;
    UINTN                          CommunicateBufferSize;

    if ((pData == NULL) || (DataSize == 0) || (pGuid == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + DataSize; // Header size (without data) + data size

    ZeroMem( gHddSecCommunicateBuffer, CommunicateBufferSize);
    
    // Copy SMM Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gHddSecCommunicateBuffer;

    // Copy data GUID
    CopyMem (&SmmCommunicateHeader->HeaderGuid, pGuid, sizeof(EFI_GUID));

    // Updated data length
    SmmCommunicateHeader->MessageLength  = DataSize;

    // Copy Data Here
    CopyMem (&SmmCommunicateHeader->Data, pData, DataSize);

    if (gSmmCommunication == NULL) {
        // Locate EFI_SMM_COMMUNICATION_PROTOCOL
        Status = gBS->LocateProtocol (
                            &gEfiSmmCommunicationProtocolGuid,
                            NULL,
                            (VOID **)&gSmmCommunication );
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;  
        }
    }

    // Send data to SMM using protocol API
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );
    return Status;  
}
/** @internal
    This routine collects NVMe controller and its corresponding PCI bridge 
    register data to save it in Boot script table. During S3 resume PCI register 
    information stored in Boot Script will be programmed to PCI configuration space 
    registers. So that NVMe device can be unlocked and used during S3 resume.
    
    @param Event        Pointer to an event structure.
    @param Context      Event specific context
    
    @retval VOID
    
    @note If SAVE_PCI_ROOTBRIDGE_REGS token is disabled only NVMe controller
      PCI configuration space registers will be saved. If this token is enabled PCI bridge
      register data under which NVMe controller is connected also will be saved to BootScript.
      
    @endinternal
**/

VOID
StoreNvmePciConfigDataInBootScript (
    IN  EFI_EVENT               Event,
    IN  VOID                    *Context
)
{
    EFI_STATUS                              Status;
    UINTN                                   PciSeg, PciBus, PciDev, PciFunc;
    EFI_PCI_IO_PROTOCOL                     *PciIo;
    UINTN                                   Data32 = 0;
    UINT32                                  Index;
    UINT32                                  Index1;
    UINTN                                   HandleCount;
    EFI_HANDLE                              *HandleBuffer;
    UINT64                                  PciAddress;
    EFI_HANDLE                              MatchedDevicePathHandle;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePathNode;
    EFI_DEVICE_PATH_PROTOCOL                *HeadDevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL                *TempHeadDevicePath;
    BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY    *TransferBuffer = NULL;
    EFI_S3_SAVE_STATE_PROTOCOL              *S3BootScriptSaveProtocol;

    gBS->CloseEvent (Event);
        
    Status = gBS->LocateProtocol(
                          &gEfiS3SaveStateProtocolGuid,
                          NULL,
                          (VOID**)&S3BootScriptSaveProtocol);

    if (EFI_ERROR( Status)) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    Status = gBS->LocateHandleBuffer(
                              ByProtocol,
                              &gAmiNvmeControllerProtocolGuid,
                              NULL,
                              &HandleCount,
                              &HandleBuffer);

    if (EFI_ERROR(Status)) {
        return;
    }

    for (Index = 0; Index < HandleCount; Index++) {
        
        if (gNvmeSavePciBridgeRegs) {
            // Get the Device path Protocol interface
            Status = gBS->HandleProtocol( 
                                    HandleBuffer[Index],
                                    &gEfiDevicePathProtocolGuid,
                                    (void**)&DevicePath );
        
            if (EFI_ERROR(Status)) {
                continue;
            }
            
            DevicePathNode = DevicePath;
            HeadDevicePath = NULL;
        
            for (; !IsDevicePathEndType(DevicePathNode); DevicePathNode = NextDevicePathNode (DevicePathNode)) {
        
                TempHeadDevicePath = HeadDevicePath;
                HeadDevicePath = AppendDevicePathNode(HeadDevicePath, DevicePathNode);
        
                if (TempHeadDevicePath != NULL) {
                    FreePool (TempHeadDevicePath);
                }
        
                // Check to identify the PCI device Path
                if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                    (DevicePathNode->SubType == HW_PCI_DP)) {
        
                    TempHeadDevicePath = HeadDevicePath;
        
                    Status = gBS->LocateDevicePath ( 
                                            &gEfiDevicePathProtocolGuid,
                                            &TempHeadDevicePath,
                                            &MatchedDevicePathHandle );
                    if (EFI_ERROR(Status)) {
                        continue;
                    }
        
                    Status = gBS->HandleProtocol ( 
                                            MatchedDevicePathHandle,
                                            &gEfiPciIoProtocolGuid,
                                            (void **) &PciIo );
                    if (EFI_ERROR(Status)) {
                        continue;
                    }
                        
                    Status = PciIo->Pci.Read ( 
                                            PciIo,
                                            EfiPciIoWidthUint32,
                                            PCI_REVISION_ID_OFFSET,
                                            1,
                                            &Data32);
                    
                    if (EFI_ERROR(Status)) {
                        continue;
                    }
        
                    // Check Class code to identify whether it is a PCI bridge device or not
                    if ((Data32 >> 24) == PCI_CLASS_BRIDGE) {
                        // Store PCI bridge device PCI configuration values
                        Status = StorePciBridgePciCfgRegs (PciIo);
                        if (EFI_ERROR(Status)) {
                            return;
                        }
                    }
                }
            }
        }
        
        // PCI bridge register data has been stored above. Now gather NVMe controller's
        // PCI configuration space data to save in Boot Script.
        
        // Get the PCIIO protocol installed on the handle
        Status = gBS->HandleProtocol( 
                                HandleBuffer[Index],
                                &gEfiPciIoProtocolGuid,
                                (VOID**) &PciIo );
        if (EFI_ERROR(Status)) {
            continue;
        }
    
        Status = PciIo->GetLocation(
                                PciIo, 
                                &PciSeg, 
                                &PciBus, 
                                &PciDev, 
                                &PciFunc );
        
        if (EFI_ERROR(Status)) {
            continue;
        }
        
        Status = PciIo->Pci.Read (
                            PciIo,
                            EfiBootScriptWidthUint32,
                            PCI_VENDOR_ID_OFFSET,
                            1,
                            &Data32 );
        if (EFI_ERROR(Status) || (Data32 == MAX_UINT32)) {
            continue;
        }
        
        for (Index1 = 0; Index1 < (sizeof(gNvmeControllerRegistersSave)/sizeof(BOOT_SCRIPT_NVME_REG_SAVE)); Index1++) {
            Status = PciIo->Pci.Read(
                                  PciIo,
                                  gNvmeControllerRegistersSave[Index1].Width,
                                  gNvmeControllerRegistersSave[Index1].RegNum,
                                  1,
                                  &Data32 );
            if (EFI_ERROR(Status)) {
                continue;
            }
                
            Data32 &= gNvmeControllerRegistersSave[Index1].Mask;
            
            PciAddress = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS(PciBus, PciDev, PciFunc, gNvmeControllerRegistersSave[Index1].RegNum);

            // Copy NVMe PCI Data to be saved in BootScript to entry list one by one to transfer to SMM
            Status = CopyPciDataToBootScriptBuffer (
                                            PciSeg,
                                            (UINTN)PciAddress, 
                                            gNvmeControllerRegistersSave[Index1].Width, 
                                            Data32 );
            if (EFI_ERROR(Status)) {
                return;
            }
        }
    }

    // Allocate a buffer that will hold the entry list of BootScript saved along with the Nvme BootScript Signature
    // and Total bootscript entry count @ the end
    //          Buffer will be as of below
    
    //  ===============================     ======================================== 
    //          Buffer entries                              Size  
    //  ===============================     ========================================  
    //       NvmeSaveEntry[0]                   sizeof(BOOT_SCRIPT_NVME_REG_SAVE)
    //       NvmeSaveEntry[1]                   sizeof(BOOT_SCRIPT_NVME_REG_SAVE)
    //       NvmeSaveEntry[2]                   sizeof(BOOT_SCRIPT_NVME_REG_SAVE)
    //          .
    //          .
    //          .
    //       NvmeSaveEntry[n]                   sizeof(BOOT_SCRIPT_NVME_REG_SAVE)  where n is Total Entry Count
    //       NVME Boot Script Signature         UINT32   ('n','s','b','s')
    //       gNvmeSaveEntryCount                UINT32
    //
    TransferBuffer = AllocateZeroPool ((sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY) * gNvmeSaveEntryCount) + (2 * sizeof(UINT32)));
    if (TransferBuffer == NULL) {
        return;
    }

    // Copy the saved entry list to the buffer allocated
    CopyMem (TransferBuffer, gNvmeSaveEntry, (sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*gNvmeSaveEntryCount));

    // Append the Signature and Bootscript Entry Count to the buffer.
    *(UINT32*)(&TransferBuffer[gNvmeSaveEntryCount]) = NVME_SECURITY_SAVE_SIGNATURE;
    *(UINT32*)(&TransferBuffer[gNvmeSaveEntryCount + 1]) = gNvmeSaveEntryCount;

    // Transfer NVMe boot script buffer with size to communication buffer to transfer to SMM 
    TransferNvmeBootScriptDataToSmm ( 
                                TransferBuffer,
                                (sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*gNvmeSaveEntryCount) + (2 * sizeof(UINT32)), 
                                &gNvmeSecurityBootScriptSaveTriggerGuid );

    // Free the unused memory
    FreePool (TransferBuffer);
    FreePool (HandleBuffer);
}

/** @internal
    Generate the SMI to pass the buffer for Unlock command
    and Locate the AhciSMM Protocol that is used by SmmHddSecurity

    @param Event        Handle to an event structure.
    @param *Context     Pointer to the notification function's context.

    @retval VOID
    
    @endinternal
**/
VOID
EFIAPI
SendSmmCommandDataBuffer (
    EFI_EVENT                   Event,
    VOID                        *Context
)
{
    EFI_STATUS                  Status;
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader;
    UINTN                       CommunicateBufferSize;

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof (UINT8 *);
    
    ZeroMem (gHddSecCommunicateBuffer, CommunicateBufferSize);
    
    // Copy Smm Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gHddSecCommunicateBuffer;
    
    CopyMem (&SmmCommunicateHeader->HeaderGuid, &gHddSecuritySendCommandDataBufferGuid, sizeof(EFI_GUID));
    
    SmmCommunicateHeader->MessageLength  = sizeof(UINT8 *);

    CopyMem (&SmmCommunicateHeader->Data, &gHddSecCommunicateData, sizeof(UINT8 *));
    
    if (gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (
                            &gEfiSmmCommunicationProtocolGuid,
                            NULL,
                            (VOID **) &gSmmCommunication );
        if (EFI_ERROR(Status)) {
            return;  
        }
    }

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );
    gBS->CloseEvent(Event);
}

/** @internal
    Manages HDD Password in SMM area.

    @param *This       Pointer to AMI_HDD_SECURITY_PROTOCOL
    @param Control     Bit 0 : 0/1 User/Master Password
    @param Buffer      Pointer to password buffer which will be used to when sending
                       SecurityCommand.
    @param  Action     Save/remove HDD password in SMM area. 

    @retval EFI_SUCCESS        Password saved which will be used to unlock the drive
                               during S3 resume.
    @retval EFI_DEVICE_ERROR   Error in saving Password.

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
         32 bytes long, pad it with zeros to create a buffer of 32 bytes.
         
    @endinternal
**/

EFI_STATUS
SmmHddPasswordInterface (
    AMI_HDD_SECURITY_PROTOCOL           *This,
    UINT16                              Control,
    UINT8                               *Buffer,
    HDD_SECURITY_PASSWORD_ACTION        PasswordAction
)
{
    EFI_STATUS                              Status;
    EFI_SMM_COMMUNICATE_HEADER              *SmmCommunicateHeader;
    UINTN                                   CommunicateBufferSize;
    HDD_PASSWORD                            *HddPasswordBuffer;
    VOID                                    *BusInterface = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE               BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE* )This)->BusInterfaceType;
    EFI_PCI_IO_PROTOCOL                     *PciIo = NULL;
    UINTN                                   SegNum;
    UINTN                                   BusNum;
    UINTN                                   DevNum;
    UINTN                                   FuncNum;
    
    if ((PasswordAction < SavePassword) || (PasswordAction > RemovePassword)) {
        return EFI_INVALID_PARAMETER;
    }
    
    if ((BusInterfaceType < AmiStorageInterfaceIde) || 
       ((LOCAL_AMI_STORAGE_BUS_INTERFACE)BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        return EFI_UNSUPPORTED;
    }

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + HDD_PASSWORD_SIZE + (2 * IDE_PASSWORD_LENGTH);
    
    ZeroMem (gHddSecCommunicateBuffer, CommunicateBufferSize);
    
    // Copy Smm Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gHddSecCommunicateBuffer;
    
    //Copy HDD_PASSWORD here
    HddPasswordBuffer = (HDD_PASSWORD *)&SmmCommunicateHeader->Data;
    
   
    if (PasswordAction == SavePassword) {
        CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gSaveHddPasswordGuid);
    } else if (PasswordAction == RemovePassword) {
        CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gRemoveHddPasswordGuid);
    }

    SmmCommunicateHeader->MessageLength  = HDD_PASSWORD_SIZE + (2 * IDE_PASSWORD_LENGTH);
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceIde:
#if (defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0))
            {
                AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
                    
                //  If HDD is not going to lose power in S3, no need to unlock password and put it in
                //  Freeze state during S3 resume.
                if (!(IdeBusInterface->IdeBusInitInterface->Flags & S3_RESUME_UNLOCK_HDD_PASSWORD)) {
                    return EFI_SUCCESS;
                }
            
                HddPasswordBuffer->BaseAddress = IdeBusInterface->IdeDevice.Regs.CommandBlock.DataReg;
                HddPasswordBuffer->Device = IdeBusInterface->IdeDevice.Device;
                HddPasswordBuffer->DeviceControlReg = IdeBusInterface->IdeDevice.Regs.ControlBlock.DeviceControlReg;
                PciIo = IdeBusInterface->PciIO;
            }
#endif
            break;
            
        case AmiStorageInterfaceAhci:
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
            {
                SATA_DEVICE_INTERFACE *SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;
                
                PciIo = SataDevInterface->AhciBusInterface->PciIO;
                HddPasswordBuffer->PortNumber   = SataDevInterface->PortNumber;
                HddPasswordBuffer->PMPortNumber = SataDevInterface->PMPortNumber;
            }
#endif
            break;
            
        case AmiStorageInterfaceNvme:
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
            {
                PciIo = ((AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface)->PciIO;
                HddPasswordBuffer->DevHandle = ((AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface)->ControllerHandle;
            }
#endif
            break;
            
        case LocalAmiStorageInterfaceRaid:
#if (defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0))   
            {
                NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE*)BusInterface;
                HddPasswordBuffer->IsRaidHdd = NvmeRstInterface->IsRaidHdd;
                PciIo = NvmeRstInterface->PciIO;
                CopyMem (
                     HddPasswordBuffer->ModelSerialNo, 
                     NvmeRstInterface->ModelSerialNo,
                     sizeof(NvmeRstInterface->ModelSerialNo) );
            }
#endif    
            break;
    }
    
    if (PciIo == NULL) {
        return EFI_UNSUPPORTED;
    }
    
    // Get PCI Bus/Device/Function number
    Status = PciIo->GetLocation ( 
                            PciIo,
                            &SegNum,
                            &BusNum,
                            &DevNum,
                            &FuncNum );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Save it for IdeSmm to initialize the controller.
    HddPasswordBuffer->BusNo      = (UINT8)BusNum;
    HddPasswordBuffer->DeviceNo   = (UINT8)DevNum;
    HddPasswordBuffer->FunctionNo = (UINT8)FuncNum;

    HddPasswordBuffer->Signature = HDD_SEC_SIGNATURE; // 0x44444824; //
    HddPasswordBuffer->Control   = Control;
    HddPasswordBuffer->BusInterfaceType  = BusInterfaceType;

    //HDDPasswordBuffer->RevisionCode = RevisionCode;
    if (Control & 0x01) {
        // gHddSecCommunicateBuffer comprises SmmCommunicateHeader, HDD_PASSWORD data and User & Master password
        HddPasswordBuffer->MasterPassword = (UINT8 *)&SmmCommunicateHeader->Data + HDD_PASSWORD_SIZE;
        if (Buffer == NULL) {
            // Filling Zero in Password data to create device entry in SaveHddPassword() 
            ZeroMem (HddPasswordBuffer->MasterPassword, IDE_PASSWORD_LENGTH);
        } else {
            CopyMem (HddPasswordBuffer->MasterPassword, Buffer, IDE_PASSWORD_LENGTH);
        }
    } else {
        // User password is located after Master password in gHddSecCommunicateBuffer
        HddPasswordBuffer->UserPassword = (UINT8 *)&SmmCommunicateHeader->Data + HDD_PASSWORD_SIZE + IDE_PASSWORD_LENGTH;
        CopyMem (HddPasswordBuffer->UserPassword, Buffer, IDE_PASSWORD_LENGTH);
    }

    if (gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (
                                &gEfiSmmCommunicationProtocolGuid,
                                NULL,
                                (VOID **)&gSmmCommunication );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    // Send data to SMM.
    Status = gSmmCommunication->Communicate (
                                    gSmmCommunication,
                                    gHddSecCommunicateBuffer,
                                    &CommunicateBufferSize );

    return Status;
}
/**
    This function creates event to 
    1. store NVMe PCI configuration data to Boot script if NVMe drive
    2. store drive unlock context to boot script
    
    @param BusInterfaceType   Controller Interface type to enable security support

    @retval 
        EFI_SUCCESS           Events created successfully      
        EFI_ERROR             Error in creating events
**/
EFI_STATUS
CreateSmmCommunicateEvents (
    IN AMI_STORAGE_BUS_INTERFACE        BusInterfaceType,
    IN AMI_HDD_SECURITY_INTERFACE       *SecurityInterface
)
{
    EFI_STATUS                          Status =  EFI_UNSUPPORTED;
    VOID                                *EvtRegistration;
    
    //return success if SMM support is disabled.
    if (!gSmmHddSecuritySupport) {
        return EFI_SUCCESS;
    }  
    
    if ((gNvmeEvtBootScript == NULL) && (BusInterfaceType == AmiStorageInterfaceNvme)) {
        // Create event for NVMe boot script
        Status = EfiCreateEventReadyToBootEx (
                                    TPL_NOTIFY,
                                    StoreNvmePciConfigDataInBootScript,
                                    NULL,
                                    &gNvmeEvtBootScript );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    if (gHddEfiBootScriptEvt == NULL) {
        Status = gBS->CreateEvent ( 
                                EVT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                StoreUnlockSmiContextInBootScript,
                                NULL,
                                &gHddEfiBootScriptEvt );
        
        if (!EFI_ERROR(Status)) {
            Status = gBS->RegisterProtocolNotify ( 
                                            &gBeforeBootGuid,
                                            gHddEfiBootScriptEvt,
                                            &EvtRegistration );
        }
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    if (gHddLegacyBootScriptEvt == NULL) {
        // Create legacy boot event for boot script
        Status = EfiCreateEventLegacyBootEx (
                                    TPL_NOTIFY,
                                    StoreUnlockSmiContextInBootScript,
                                    NULL,
                                    &gHddLegacyBootScriptEvt );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    // To Send data to SMM, locate SMM communicate protocol.
    if (gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (
                                &gEfiSmmCommunicationProtocolGuid,
                                NULL, 
                                (VOID **) &gSmmCommunication);
        
         if (EFI_ERROR(Status)) {
             gSmmCommunication = NULL;
         }
     }
    
    // Install the Readytoboot event to send command data buffer to be used in SMM
    if (gReadytoBootEvent == NULL) {
        // Create event for AhciSmm Services
        Status = EfiCreateEventReadyToBootEx (
                                    TPL_CALLBACK,
                                    SendSmmCommandDataBuffer,
                                    NULL,
                                    &gReadytoBootEvent );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    if (gSat3SendFreezeLockOnS3) {
        // Save device information to send FreezeLock Cmd during S3 resume
        Status = SmmHddPasswordInterface( 
                                (AMI_HDD_SECURITY_PROTOCOL *)SecurityInterface,
                                 0x01,
                                 NULL,
                                 SavePassword );
    }
    
    return Status;
}

/** @internal
    Transfers Stored Data from NVRAM to SMRAM.

    @param *This         Pointer to AMI_HDD_SECURITY_PROTOCOL

    @retval EFI_SUCCESS        Password saved in SMRAM.
    @retval EFI_DEVICE_ERROR   Password not saved in SMRAM.

    @endinternal
**/
EFI_STATUS
TransferPwDataFromNvramToSmram (
    IN AMI_HDD_SECURITY_PROTOCOL           *This
)
{
    EFI_STATUS                      Status;
    UINT32                          HddDataId = 0;
    CHAR16                          HddSecutiyData [HDD_SECURITY_DATASIZE];
    HDD_SEC_DATA                    *HddSecData;
    VOID                            *BusInterface = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE       BusInterfaceType = ((AMI_HDD_SECURITY_INTERFACE *)This)->BusInterfaceType;
    UINT16                          Control;
    UINTN                           HddSecDataSize = sizeof(HDD_SEC_DATA);
    UINT8                           CryptBuffer [IDE_PASSWORD_LENGTH];
    UINT8                           Buffer [IDE_PASSWORD_LENGTH];
    UINT16                          SecurityStatus = 0;
    
    //return success if SMM support is disabled.
    if (!gSmmHddSecuritySupport) {
        return EFI_SUCCESS;
    }  
    
    Status = ReturnSecurityStatus (This, &SecurityStatus);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Hdd Password Nvram Variable will not be available if the HDD is in locked state. 
    // So return without copying the password to Smram as the password 
    // data is not available
    
    if (SecurityStatus & BIT2) {
        return EFI_SUCCESS;
    }

    Status = GatherIdeInfo (
                        BusInterface, 
                        BusInterfaceType, 
                        &HddDataId );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    UnicodeSPrint (
            HddSecutiyData, 
            HDD_SECURITY_DATASIZE * sizeof(CHAR16), 
            L"%d",
            HddDataId );

    HddSecData = AllocateZeroPool (sizeof(HDD_SEC_DATA));
    if (HddSecData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ZeroMem (Buffer, IDE_PASSWORD_LENGTH);

    Status = gRT->GetVariable(
                        HddSecutiyData,
                        &gIdeSecurityPwNvguid,
                        NULL,
                        &HddSecDataSize,
                        HddSecData );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Control = HddSecData->UserMaster;
    
    // Check Password Presence in NVRAM. If Password not present, return.
    if (!(Control & (BIT1|BIT0))) {
        return EFI_DEVICE_ERROR;
    }

    if (Control & BIT0) {
        CopyMem (CryptBuffer, HddSecData->HddMasterPassword, sizeof(HddSecData->HddMasterPassword));
        EncodeDecodePassword (CryptBuffer, Buffer, HddSecData->MasterPasswordLength);
    } else {
        CopyMem (CryptBuffer, HddSecData->HddUserPassword, sizeof(HddSecData->HddUserPassword));
        EncodeDecodePassword (CryptBuffer, Buffer, HddSecData->UserPasswordLength);
    }

    SmmHddPasswordInterface ( 
                        This,
                        Control,
                        Buffer,
                        SavePassword );

    FreePool( HddSecData );
    return Status;
}
