//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

#include "TcgStorageSec.h"


EFI_SMM_COMMUNICATION_PROTOCOL  *gSmmCommunication = NULL;

//Global Buffers used for SMM Communication
UINT8                       *gTcgStorageSecCommunicateBuffer = NULL;
UINT8                       *gTcgStorageSecCommunicateData = NULL;
UINTN                       gTcgStorageSecCommunicateBufferSize;

EFI_EVENT   gTcgReadyToBootSmmServiceEvent;
BOOLEAN     gTcgIsReadyToBootEventServiced;

BOOLEAN                             gSmmTcgSecuritySupport = SmmTcgStorageSec_SUPPORT;

EFI_GUID gTcgStorageSecSavePwdGuid = AMI_TCG_STORAGE_SEC_SMM_SAVE_PWD_GUID;
EFI_GUID gTcgStorageSecRemovePwdGuid = AMI_TCG_STORAGE_SEC_SMM_REMOVE_PWD_GUID;
EFI_GUID gTcgGetNonSmramDataTransferBufferGuid = AMI_TCG_GET_NON_SMRAM_DATA_TRANSFER_BUFFER_GUID;
EFI_GUID gTcgStorageSecSmiBootScriptSaveTriggerGuid = AMI_TCG_STORAGE_SEC_SMI_BOOTSCRIPT_SAVE_TRIGGER_GUID;
EFI_GUID gTcgStorageSecNvmeBootScriptSaveTriggerGuid = AMI_TCG_STORAGE_SEC_NVME_BOOTSCRIPT_SAVE_TRIGGER_GUID;

BOOT_SCRIPT_NVME_REG_SAVE gPciRootBridgeRegistersSave[] = {
   {PCI_ROOT_BRIDGE_BUS,   EfiBootScriptWidthUint32, 0xffffffff}, // 0x18
   {PCI_ROOT_BRIDGE_IO,    EfiBootScriptWidthUint16, 0xffff},     // 0x1C
   {PCI_ROOT_BRIDGE_MEM,   EfiBootScriptWidthUint32, 0xffffffff}, // 0x20
   {PCI_ROOT_BRIDGE_PFMEM, EfiBootScriptWidthUint32, 0xffffffff}, // 0x24
   {PCI_ROOT_BRIDGE_CMD,   EfiBootScriptWidthUint8,  0xff},       // 0x04
};

BOOT_SCRIPT_NVME_REG_SAVE gNvmeControllerRegistersSave[] = {
   {NVME_CONTROLLER_BAR0, EfiBootScriptWidthUint32, 0xffffffff}, // 0x10
   {NVME_CONTROLLER_BAR1, EfiBootScriptWidthUint32, 0xffffffff}, // 0x14
   {NVME_CONTROLLER_BAR2, EfiBootScriptWidthUint32, 0xffffffff}, // 0x18
   {NVME_CONTROLLER_BAR3, EfiBootScriptWidthUint32, 0xffffffff}, // 0x1C
   {NVME_CONTROLLER_BAR4, EfiBootScriptWidthUint32, 0xffffffff}, // 0x20
   {NVME_CONTROLLER_BAR5, EfiBootScriptWidthUint32, 0xffffffff}, // 0x24
   {NVME_CONTROLLER_CMD,  EfiBootScriptWidthUint8,  0xff},       // 0x04
};

// Total PCI register count for each device 
#define TOTAL_PCI_REGISTERS_COUNT (sizeof(gPciRootBridgeRegistersSave)/sizeof(BOOT_SCRIPT_NVME_REG_SAVE) + \
                               sizeof(gNvmeControllerRegistersSave)/sizeof(BOOT_SCRIPT_NVME_REG_SAVE))
                               
// Global buffers used for collecting NVMe controller and its PCI bridge configuration space 
// register data to save it in Boot script table. 
BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY    gNvmeSaveEntry[TOTAL_PCI_REGISTERS_COUNT * MAX_NVME_DEVICES];
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *gPciRootBridgeIo = NULL;
UINT32                                  gNvmeSaveEntryCount = 0;


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
    
    //return success if SMM support is disabled.
    if (!gSmmTcgSecuritySupport) {
        return EFI_SUCCESS;
    }     

    // Buffers Allocated for SMM Communication As new core doesn't allow Buffers which are allocated after EndofDXE.
    // Maximum Size of Buffer allocated for reuse
    gTcgStorageSecCommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + TCG_STORAGE_SECURITY_PASSWORD_SIZE \
                                + sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*(TOTAL_PCI_REGISTERS_COUNT * MAX_NVME_DEVICES)+(2*OPAL_PASSWORD_LENGTH);
    
    gTcgStorageSecCommunicateBuffer = AllocateRuntimePool (gTcgStorageSecCommunicateBufferSize);
    
    if (gTcgStorageSecCommunicateBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
            
    gTcgStorageSecCommunicateData = AllocateReservedPool (512);

    if (gTcgStorageSecCommunicateData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}

/** @internal
    Transfer BS buffer to SmmTcgStorageSec driver

    @param None

    @retval EFI_STATUS

    @endinternal
**/
EFI_STATUS
TransferDmaBufferToSmram (
    IN  EFI_EVENT   Event, 
    IN  VOID        *Context
)
{
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader;
    EFI_STATUS                  Status;
    UINTN                       CommunicateBufferSize = 0;

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = (((UINTN) &(((EFI_SMM_COMMUNICATE_HEADER *)0)->Data))) + sizeof (UINT8 *);

    gBS->SetMem( gTcgStorageSecCommunicateBuffer, CommunicateBufferSize, 0);

    // Copy Smm Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gTcgStorageSecCommunicateBuffer;
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgGetNonSmramDataTransferBufferGuid, sizeof( EFI_GUID ));
    SmmCommunicateHeader->MessageLength  = sizeof(UINT8 *);

    gBS->CopyMem( &SmmCommunicateHeader->Data, &gTcgStorageSecCommunicateData, sizeof(UINT8 *));
    
    if(gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;  
        }
    }

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;  
    }
    gBS->CloseEvent(Event);
    return Status; 
}

/** @internal
    It uses EFI_SMM_COMMUNICATION_PROTOCOL API to transfer data from Non-SMM
    mode NVME BootScript Data to SMM mode. 
    
    @param pData - Pointer to data to be transfered
    @param DataSize - Size of the data
    @param pGuid  - Pointer to GUID identifier for the data
        
    @retval EFI_STATUS
    
    @endinternal
**/
EFI_STATUS
TcgTransferNvmeBootScriptDataToSmm ( 
    IN  VOID      *Data, 
    IN  UINTN     DataSize, 
    IN  EFI_GUID  *Guid 
)
{
    EFI_SMM_COMMUNICATE_HEADER     *SmmCommunicateHeader;
    EFI_STATUS                     Status;
    UINTN                          CommunicateBufferSize;

    if ( Data == NULL || DataSize == 0 || Guid == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + DataSize; // Header size (without data) + data size
    
    gBS->SetMem( gTcgStorageSecCommunicateBuffer, CommunicateBufferSize, 0 );

    // Copy SMM Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gTcgStorageSecCommunicateBuffer;

    // Copy data GUID
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, Guid, sizeof( EFI_GUID ));

    // Updated data length
    SmmCommunicateHeader->MessageLength  = DataSize;

    // Copy Data Here
    gBS->CopyMem( &SmmCommunicateHeader->Data, Data, DataSize);

    // Locate EFI_SMM_COMMUNICATION_PROTOCOL
    if(gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;  
        }
    }

    // Send data to SMM using protocol API
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;  
    }
    
    return EFI_SUCCESS;
}

/** @internal
    Copies PciRegisters from NvmeController or PCI Root Bridge devices 
    to S3 Buffer Structure for saving Data in Bootscript for S3 Resume.

    @param PciAddress - Physical Pci Address of register to be stored
    @param Width - Width of the data to be stored
    @param Value  - Value to be saved for Bootscript
        
    @retval EFI_STATUS
    
    @endinternal

**/
EFI_STATUS
TcgCopyPciDataToS3BufferStructure (
  IN    UINTN                           PciAddr,
  IN    EFI_BOOT_SCRIPT_WIDTH           Width,
  IN    UINTN                           Value
){
    DEBUG((DEBUG_VERBOSE,"\n TcgCopyPciDataToS3BufferStructure - %x %x %x %x", gNvmeSaveEntryCount, PciAddr, Width, Value ));
    
    if(gNvmeSaveEntryCount >= (TOTAL_PCI_REGISTERS_COUNT * MAX_NVME_DEVICES)) {
        ASSERT_EFI_ERROR(EFI_OUT_OF_RESOURCES);
        return EFI_OUT_OF_RESOURCES;
    }

    // Save the bootScript save entries to the array list
    gNvmeSaveEntry[gNvmeSaveEntryCount].PciAddress = PciAddr;
    gNvmeSaveEntry[gNvmeSaveEntryCount].Width = Width;
    gNvmeSaveEntry[gNvmeSaveEntryCount].Value = Value;
    gNvmeSaveEntryCount++;
    
    return EFI_SUCCESS;
}

/** @internal
    Function stores PCI bridge BAR,CMD,BUS PCI Configuration values

    @param BusNum
    @param DevNum
    @param FuncNum

    @retval EFI_STATUS
    
    @endinternal
**/

EFI_STATUS
StorePciRootBridgePciCfgRegs (
  EFI_PCI_IO_PROTOCOL     *PciIo
)
{
    EFI_STATUS    Status;
    UINTN         Data32;
    UINTN         Index;
    UINTN         PciSeg, PciBus, PciDev, PciFunc;
    UINTN         RbPciAddress;
    

    Status = PciIo->GetLocation(
                            PciIo, 
                            &PciSeg, 
                            &PciBus, 
                            &PciDev, 
                            &PciFunc);
    if (EFI_ERROR( Status )) {
        return Status;
    }
    for (Index = 0; Index < sizeof(gPciRootBridgeRegistersSave)/sizeof(BOOT_SCRIPT_NVME_REG_SAVE); Index++) {
        
        RbPciAddress = EFI_PCI_CFG_ADDRESS (PciBus, PciDev, PciFunc, gPciRootBridgeRegistersSave[Index].RegNum);


        Status = PciIo->Pci.Read(
                                PciIo,
                                gPciRootBridgeRegistersSave[Index].Width,
                                gPciRootBridgeRegistersSave[Index].RegNum,
                                1,
                                &Data32);
        if (EFI_ERROR( Status )) {
            return Status;
        }
        Data32 &= gPciRootBridgeRegistersSave[Index].Mask;
        
        // Copy Root Bridge Pci Data to be saved in BootScript to entry list one by one to transfer to Smm
        // in global buffer gNvmeSaveEntry.
        Status = TcgCopyPciDataToS3BufferStructure(RbPciAddress, gPciRootBridgeRegistersSave[Index].Width, Data32);
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    return EFI_SUCCESS;
}

#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) )
/** @internal
    This routine collects NVMe controller and its corresponding PCI bridge 
    register data to save it in Boot script table.During S3 resume PCI register 
    information stored in Boot Script will be programmed to PCI configuration space 
    registers.So that NVMe device can be unlocked and used during S3 resume.
    
    @param  VOID
    
    @retval VOID
    
    @note If TCG_STORAGE_SEC_SAVE_PCI_ROOTBRIDGE_REGS token is disabled only NVMe controller
          PCI configuration space registers will be saved.If this token is enabled PCI bridge
          register data under which NVMe controller is connected also will be saved to BootScript.
    
    @endinternal
**/

VOID
EFIAPI
StoreNvmePciConfigDataInBootScript (
)
{
    EFI_STATUS                              Status;
    UINTN                                   PciSeg, PciBus, PciDev, PciFunc;
    EFI_PCI_IO_PROTOCOL                     *PciIO;
    UINTN                                   Data32 = 0;
    UINT32                                  RegIndex;
    UINT32                                  Index;
    UINTN                                   HandleCount;
    EFI_HANDLE                              *HandleBuffer;
    UINTN                                   PciAddress;
    BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY    *TransferBuffer = NULL;
#if TCG_STORAGE_SEC_SAVE_PCI_ROOTBRIDGE_REGS
    EFI_HANDLE                              MatchedDevicePathHandle;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL                *DevicePathNode;
    EFI_DEVICE_PATH_PROTOCOL                *HeadDevicePath = NULL;
    EFI_DEVICE_PATH_PROTOCOL                *TempHeadDevicePath;
#endif
    AMI_NVME_CONTROLLER_PROTOCOL            *NvmeDevInterface;
    ACTIVE_NAMESPACE_DATA                   *ActiveNameSpace = NULL;

    Status = gBS->LocateHandleBuffer(
                  ByProtocol,
                  &gAmiNvmeControllerProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                 );

    if ( EFI_ERROR( Status )) {
        return;
    }
    
    for( Index = 0; Index < HandleCount; Index++ ) {
        
        Status = gBS->HandleProtocol(
                      HandleBuffer[Index],
                      &gAmiNvmeControllerProtocolGuid,
                      (VOID *)&NvmeDevInterface
                      );

        if(EFI_ERROR(Status)) {
            continue;
        }
        
        ActiveNameSpace = GetActiveNameSpace( NvmeDevInterface, MAX_UINT32 );
        
        if (ActiveNameSpace == NULL) {
            continue;
        }

        // Verify whether gAmiTcgStorageSecurityProtocolGuid is installed or not ?
        Status = gBS->OpenProtocol ( ActiveNameSpace->NvmeDeviceHandle, 
                                     &gAmiTcgStorageSecurityProtocolGuid, 
                                     NULL, 
                                     NULL, 
                                     NULL, 
                                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                                     );
        if(EFI_ERROR(Status)) {
            continue;
        }
#if TCG_STORAGE_SEC_SAVE_PCI_ROOTBRIDGE_REGS
        // Get the Device path Protocol interface
        Status = gBS->HandleProtocol( HandleBuffer[Index],
                                      &gEfiDevicePathProtocolGuid,
                                      (void**)&DevicePath
                                      );
    
        if(!EFI_ERROR(Status)) {
        
            DevicePathNode = DevicePath;
            HeadDevicePath = NULL;
            // From DP obtain each PCI DP node, if its a PCI bridge node then gather PCI bridge's 
            // PCI configuration space register data to save in boot script table.
            for ( ;!IsDevicePathEnd(DevicePathNode); DevicePathNode = NextDevicePathNode (DevicePathNode)) {
    
                TempHeadDevicePath = HeadDevicePath;
                HeadDevicePath = AppendDevicePathNode(HeadDevicePath,DevicePathNode);
    
                if(TempHeadDevicePath != NULL) {
                    gBS->FreePool(TempHeadDevicePath);
                }
    
                // Check to identify the PCI device Path
                if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                            (DevicePathNode->SubType == HW_PCI_DP)) {
    
                    TempHeadDevicePath = HeadDevicePath;
    
                    Status = gBS->LocateDevicePath( &gEfiDevicePathProtocolGuid,
                                                    &TempHeadDevicePath,
                                                    &MatchedDevicePathHandle
                                                    );
                    if ( EFI_ERROR( Status )) {
                        ASSERT_EFI_ERROR (Status);
                        continue;
                    }
    
                    Status = gBS->HandleProtocol( MatchedDevicePathHandle,
                                                  &gEfiPciIoProtocolGuid,
                                                  (void **) &PciIO
                                                  );
                    if ( EFI_ERROR( Status )) {
                        ASSERT_EFI_ERROR (Status);
                        continue;
                    }
                    
                    Status = PciIO->Pci.Read(PciIO, 
                                             EfiPciIoWidthUint32, 
                                             PCI_RID, 
                                             1, 
                                             &Data32);
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR (Status);
                        continue;
                    }
    
                    // Check Class code to identify whether it is a PCI root bridge device or not
                    if((Data32>>24) == PCI_CL_BRIDGE) {
                        // Store PCI bridge device PCI configuration values
                        Status = StorePciRootBridgePciCfgRegs(PciIO);

                        if ( EFI_ERROR( Status )) {
                            ASSERT_EFI_ERROR (Status);
                            return;
                        }
                    }
                }
            }
        } else {
            ASSERT_EFI_ERROR (Status);
            continue;
        }
#endif
        // PCI bridge register data has been stored above.Now gather NVMe controller's
        // PCI configuration space data to save in Boot Script.
        
        // Get the PCIIO protocol installed on the handle
        Status = gBS->HandleProtocol( HandleBuffer[Index],
                                      &gEfiPciIoProtocolGuid,
                                      (void**) &PciIO
                                      );
    
        if ( EFI_ERROR( Status )) {
            ASSERT_EFI_ERROR (Status);
            continue;
        }
    
        Status = PciIO->GetLocation(PciIO, &PciSeg, &PciBus, &PciDev, &PciFunc);
        if ( EFI_ERROR( Status )) {
            ASSERT_EFI_ERROR (Status);
            continue;
        }
        
        Status = PciIO->Pci.Read( \
                        PciIO, \
                        EfiBootScriptWidthUint32, \
                        PCI_VID, \
                        1, \
                        &Data32);
    
        if ( EFI_ERROR( Status )) {
            ASSERT_EFI_ERROR (Status);
            continue;
        }
        
        if (Data32 != 0xffffffff) {
            for (RegIndex = 0; RegIndex < sizeof(gNvmeControllerRegistersSave)/sizeof(BOOT_SCRIPT_NVME_REG_SAVE); RegIndex++) {
                Status = PciIO->Pci.Read( \
                         PciIO, \
                         gNvmeControllerRegistersSave[RegIndex].Width, \
                         gNvmeControllerRegistersSave[RegIndex].RegNum, \
                         1, \
                         &Data32);
                if ( EFI_ERROR( Status )) {
                    ASSERT_EFI_ERROR (Status);
                    continue;
                }
                
                Data32 &= gNvmeControllerRegistersSave[RegIndex].Mask;
                
                PciAddress =   EFI_PCI_CFG_ADDRESS( PciBus, PciDev, PciFunc, gNvmeControllerRegistersSave[RegIndex].RegNum);

                // Copy NVMe PCI data to be saved in BootScript to entry list one by one to transfer to SMM
                Status = TcgCopyPciDataToS3BufferStructure(PciAddress, gNvmeControllerRegistersSave[RegIndex].Width, Data32);

                if (EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR (Status);
                    return;
                }
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
    Status = gBS->AllocatePool( EfiBootServicesData,
                                sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*(gNvmeSaveEntryCount) + 
                                2*sizeof(UINT32),
                                (VOID**)&TransferBuffer);
    
    if ( EFI_ERROR( Status )) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    // Copy the saved entry list to the buffer allocated
    gBS->CopyMem(TransferBuffer, gNvmeSaveEntry, sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*(gNvmeSaveEntryCount));

    // Append the Signature and Boot script Entry Count to the buffer.
    *(UINT32*)(&TransferBuffer[gNvmeSaveEntryCount]) = NVME_SECURITY_SAVE_SIGNATURE;
    *(UINT32*)(((UINT8*)&TransferBuffer[gNvmeSaveEntryCount]) + sizeof(UINT32)) = gNvmeSaveEntryCount;

    // Transfer NVMe boot script buffer with size to communication buffer to trasfer to SMM 
    TcgTransferNvmeBootScriptDataToSmm ( TransferBuffer,
                                         sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY)*(gNvmeSaveEntryCount) + 
                                         2*sizeof(UINT32), 
                                         &gTcgStorageSecNvmeBootScriptSaveTriggerGuid );

    // Free the unused memory
    gBS->FreePool(TransferBuffer);
    gBS->FreePool(HandleBuffer);
    
    return;
}
#endif

/** @internal
    Triggers SMM Communication event to save SwSmi port address and 
    TCG storage password Unlock SMI handler context in BootScript table.
    During S3 resume using this stored boot script data an SMI(UnlockOPALPassword) 
    will be generated that unlocks the TCG drive.
    
    @param  VOID
         
    @retval VOID

    @note  Unlock SMI handler will be called only if OPAL device loses power
    in S3 state.A SW SMI will be generated during S3 resume, to unlock the OPAL 
    device and also to put the TCG device in Freeze state.
    
    @endinternal
**/
VOID
EFIAPI
StoreUnlockSmiContextInBootScript(
) 
{
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader=NULL;
    EFI_STATUS                  Status;
    UINTN                       CommunicateBufferSize;
    
    if (gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return ;  
        }
    }
    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof (UINT8 *);

    gBS->SetMem( gTcgStorageSecCommunicateBuffer, CommunicateBufferSize, 0 );

    //
    // Copy Smm Communicate Header Here
    //
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gTcgStorageSecCommunicateBuffer;
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgStorageSecSmiBootScriptSaveTriggerGuid, sizeof( EFI_GUID ) );
    SmmCommunicateHeader->MessageLength  = sizeof(UINT8 *);

    //
    // Send data to SMM.
    //
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
    }
    return;
}
/** @internal
    Triggers SMM Communication event to UnRegister SaveOPALPassword and 
    RemoveOPALPassword SMI handlers.

    @param  VOID

    @retval VOID

    @endinternal
**/
VOID
EFIAPI
UnRegisterSaveRemovePwdSmiHandlers ()
{
    EFI_STATUS                  Status;
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader=NULL;
    UINTN                       CommunicateBufferSize;
    UINT64                      TcgSmiUnRegSignature = TCG_SMI_UNREGISTER_SIGNATURE;

    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + sizeof (TcgSmiUnRegSignature);
    
    gBS->SetMem( gTcgStorageSecCommunicateBuffer, CommunicateBufferSize, 0 );
    
    //
    // Copy SMM Communicate Header Here
    //
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gTcgStorageSecCommunicateBuffer;
    
    //
    // UnRegister Save Password SMI handler
    //
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgStorageSecSavePwdGuid, sizeof( EFI_GUID ) );
    gBS->CopyMem( &SmmCommunicateHeader->Data, &TcgSmiUnRegSignature, sizeof( TcgSmiUnRegSignature ) );
    SmmCommunicateHeader->MessageLength  = sizeof(TcgSmiUnRegSignature);

    if(gSmmCommunication == NULL) {
        Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return ;  
        }
    }
    //
    // Send data to SMM.
    //
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return ;  
    }
    //
    // Now UnRegister Remove Password SMI handler
    //
    gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgStorageSecRemovePwdGuid, sizeof( EFI_GUID));
    //
    // Send data to SMM.
    //
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
    }
    return;
}

/**
    This Ready to Boot service call back will perform below functions:
     
    1) StoreNvmePciConfigDataInBootScript() - Store NVMe Controller and
       PCI bridge register data in BootScript table.
    2) StoreUnlockSmiContextInBootScript() - Store Unlock SMI handler 
       context to BootScript.
    3) TransferPwDataFromNvramToSmram - If FORCE_TCG_OPAL_PASSWORD_PROMPT 
       support is disabled transfers the password data stored from NVRAM to SMRAM.
    4) UnRegisterSaveRemovePwdSmiHandlers - UnRegisters SMI handlers that Stores 
       and Removes password in SMRAM.
    5) Finally frees the global Runtime memory allocated for SMM communication
       operation.(This operation should be performed at last in this callback)
    6) Close this Event.

    @param Event    - Event that was triggered
    @param Context  - Point to calling context
         
    @retval VOID

    @note 1. Will be called only if OPAL device loses power in S3 state. A SW SMI will
        be created during S3 resume, to unlock the OPAL device and put it in
        Freeze state.
        2.The above mentioned function execution order should not be disturbed.

**/
VOID
EFIAPI
TcgReadyToBootSmmServiceCallback (
    IN  EFI_EVENT Event,
    IN  VOID      *Context
)
{
#if ( FORCE_TCG_OPAL_PASSWORD_PROMPT == 0 )
    EFI_STATUS    Status = EFI_SUCCESS;
#endif
    gTcgIsReadyToBootEventServiced = TRUE;
    
#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) )
    // Store NVMe Controller and PCI bridge register data in BootScript table.
    StoreNvmePciConfigDataInBootScript();
#endif
    // Store TCG Unlock SMI Handler context in BootScript table
    StoreUnlockSmiContextInBootScript();
    
    // Transfer password data from NVRAM to SMRAM
#if ( FORCE_TCG_OPAL_PASSWORD_PROMPT == 0 )
    Status = TcgTransferPwDataFromNvramToSmram();
    ASSERT_EFI_ERROR(Status);
#endif

    // Unregister password save and remove SMI Handlers.
    UnRegisterSaveRemovePwdSmiHandlers();
    //
    // Free the RT service memory buffer that is allocated for SMM communication operation.
    //
    if( gTcgStorageSecCommunicateBuffer != NULL ) {        

        gBS->FreePool(gTcgStorageSecCommunicateBuffer);
        gTcgStorageSecCommunicateBuffer = NULL;
    }
    //Close the Event
    gBS->CloseEvent( Event );
    return;
    
}

/** @internal
    Manages OPAL Password in SMM area.

    @param This    - AMI_HDD_SECURITY_PROTOCOL instance
    @param Control - Bit 0 : 0/1 User/Master Password
                     Bit 1 : Password Buffer has 
                             Old Admin(Master) Password and 
                             New User/Master Password

    @param Buffer (32 Bytes) - Buffer with password data
    @param Action - value from TCG_STORAGE_SEC_PASSWORD_ACTION

    @retval EFI_SUCCESS      : Password saved which will be used to unlock the drive
                               during S3 resume.
    @retval EFI_NOT_FOUND : Action not valid

    @note  
      1. Buffer should be 32 bytes long (Mandatory). Even if Password is not
     32 bytes long, pad it with zeros to create a buffer of 32 bytes.
    
    @endinternal
**/

EFI_STATUS
SmmTcgPasswordInterface (
    IN  AMI_HDD_SECURITY_PROTOCOL   *This,
    IN  UINT16                      Control,
    IN  UINT8                       *Buffer,
    IN  TCG_STORAGE_SEC_PASSWORD_ACTION     Action
)
{
    EFI_STATUS                 Status;
    UINTN                      Index;
    EFI_SMM_COMMUNICATE_HEADER *SmmCommunicateHeader;
    UINTN                      CommunicateBufferSize;
    TCG_STORAGE_SECURITY_PASSWORD   *OpalPasswordBuffer;
    VOID                       *BusInterface   \
        = ((AMI_TCG_STORAGE_SECURITY_INTERFACE* )This)->BusInterface;
    AMI_STORAGE_BUS_INTERFACE    BusInterfaceType   \
        = ((AMI_TCG_STORAGE_SECURITY_INTERFACE* )This)->BusInterfaceType;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    UINTN               SegNum;
    UINTN               BusNum;
    UINTN               DevNum;
    UINTN               FuncNum;
    
    // Calculate Size of Communication buffer
    CommunicateBufferSize  = SMM_COMMUNICATE_HEADER_SIZE + TCG_STORAGE_SECURITY_PASSWORD_SIZE + (2* OPAL_PASSWORD_LENGTH);

    gBS->SetMem( gTcgStorageSecCommunicateBuffer,CommunicateBufferSize, 0);
        
    // Copy Smm Communicate Header Here
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)gTcgStorageSecCommunicateBuffer;

    if (Action == SavePassword || Action == SaveDeviceInfo) {
        gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgStorageSecSavePwdGuid, sizeof( EFI_GUID ));
            
    } else if (Action == RemovePassword) {
        gBS->CopyMem( &SmmCommunicateHeader->HeaderGuid, &gTcgStorageSecRemovePwdGuid, sizeof( EFI_GUID ) );
           
    } else {
        ASSERT(FALSE);
        return EFI_NOT_FOUND;
    }

    SmmCommunicateHeader->MessageLength  = TCG_STORAGE_SECURITY_PASSWORD_SIZE + (2* OPAL_PASSWORD_LENGTH);
    
    //Copy TCG_STORAGE_SECURITY_PASSWORD here
    OpalPasswordBuffer = (TCG_STORAGE_SECURITY_PASSWORD *) &SmmCommunicateHeader->Data;
    
    switch (BusInterfaceType) {
        case AmiStorageInterfaceAhci:
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )
            PciIo = ((SATA_DEVICE_INTERFACE*)BusInterface)->AhciBusInterface->PciIO;
            OpalPasswordBuffer->DevHandle = ((SATA_DEVICE_INTERFACE*)BusInterface)->IdeDeviceHandle;
            OpalPasswordBuffer->PortNumber  = ((SATA_DEVICE_INTERFACE*)BusInterface)->PortNumber;
            OpalPasswordBuffer->PMPortNumber =  ((SATA_DEVICE_INTERFACE*)BusInterface)->PMPortNumber;
#endif
            break;
        case AmiStorageInterfaceNvme:  
#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) )
        {
            ACTIVE_NAMESPACE_DATA                   *ActiveNameSpace = NULL;
            ActiveNameSpace = GetActiveNameSpace( (AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface, MAX_UINT32 );
            if (ActiveNameSpace != NULL) {
                OpalPasswordBuffer->DevHandle = ActiveNameSpace->NvmeDeviceHandle;
            }
        }
            PciIo = ((AMI_NVME_CONTROLLER_PROTOCOL*)BusInterface)->PciIO;
#endif
            break;
        case LocalAmiStorageInterfaceRaid:
#if ( defined(NvmeRstPassword_SUPPORT) && (NvmeRstPassword_SUPPORT != 0) )
        {
            NVME_RST_INTERFACE  *NvmeRstInterface = (NVME_RST_INTERFACE*)BusInterface;
            OpalPasswordBuffer->IsRaidHdd = NvmeRstInterface->IsRaidHdd;
            PciIo = NvmeRstInterface->PciIO;
            CopyMem( 
                OpalPasswordBuffer->ModelSerialNo, 
                NvmeRstInterface->ModelSerialNo, 
                sizeof(NvmeRstInterface->ModelSerialNo) );
            
        }
#endif
            break;
        default:
            DEBUG ((DEBUG_ERROR, "TcgStorageSecurity:%a Unsupported BusInterfaceType : %d\n", __FUNCTION__, BusInterfaceType));
            return EFI_UNSUPPORTED;
    }

    if( PciIo == NULL ) {
        DEBUG ((DEBUG_INFO, "SmmTcgPasswordInterface: PciIo or DevHandle is Null \n"));
        return EFI_NOT_FOUND;
    }
    
    // Get PCI Bus/Device/Function number
    Status = PciIo->GetLocation ( PciIo,
                                  &SegNum,
                                  &BusNum,
                                  &DevNum,
                                  &FuncNum
                                  );
    ASSERT_EFI_ERROR (Status);
    
    // Save it to initialize the controller.
    OpalPasswordBuffer->BusNo=(UINT8)BusNum;
    OpalPasswordBuffer->DeviceNo=(UINT8)DevNum;
    OpalPasswordBuffer->FunctionNo=(UINT8)FuncNum;

    OpalPasswordBuffer->Signature = OPAL_PASSWORD_SIGNATURE; // 0x4C504F24; //
    OpalPasswordBuffer->Control   = Control;
    OpalPasswordBuffer->BusInterfaceType  = BusInterfaceType;
    
    // SaveDeviceInfo does not contain password information so skip below code
    if (Action == SavePassword) {
        if ( Control & 0x01 ) {
            // gTcgStorageSecCommunicateBuffer comprises SmmCommunicateHeader, TCG_STORAGE_SECURITY_PASSWORD data and User & Master password
            OpalPasswordBuffer->MasterPassword = (UINT8 *)&SmmCommunicateHeader->Data + TCG_STORAGE_SECURITY_PASSWORD_SIZE;
            for ( Index = 0; Index < OPAL_PASSWORD_LENGTH; Index++ ) {
                OpalPasswordBuffer->MasterPassword[Index] = Buffer[Index];
            } // end of for
        } else {
            // User password is located after Master password in gTcgStorageSecCommunicateBuffer
            OpalPasswordBuffer->UserPassword = (UINT8 *)&SmmCommunicateHeader->Data + TCG_STORAGE_SECURITY_PASSWORD_SIZE + OPAL_PASSWORD_LENGTH;
            for ( Index = 0; Index < OPAL_PASSWORD_LENGTH; Index++ ) {
                OpalPasswordBuffer->UserPassword[Index] = Buffer[Index];
            } // end of for
        }
    }
    

    if(gSmmCommunication == NULL) {
        
        Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &gSmmCommunication);

        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;  
        }
    }

    // Send data to SMM.
    Status = gSmmCommunication->Communicate (gSmmCommunication, gTcgStorageSecCommunicateBuffer, &CommunicateBufferSize);

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;  
    }
    // Clear the Password data stored in global buffer
    gBS->SetMem(gTcgStorageSecCommunicateBuffer,CommunicateBufferSize + (2*OPAL_PASSWORD_LENGTH),0);
    return EFI_SUCCESS;
}
