//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SmmHddSecurity.c
    Provide functions to unlock HDD password during S3 resume

**/

#include <SmmHddSecurity.h>

UINT8                                   *gSecurityUnlockCommandBuffer = NULL;
AMI_LIST                                gPasswordList;
UINT8                                   *gSecurityBuffer    = NULL;
RAID_LOCK_BOX_DATA                      *gLockBoxData = NULL;
UINT8                                   gSwSmiPort = 0xB2;
#if (defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0))
AMI_AHCI_BUS_SMM_PROTOCOL               *mAhciSmm = NULL;
#endif
UINT8                                   *gLockBoxMapData;
EFI_PHYSICAL_ADDRESS                    gSecurityUnlockCommandBufferMapped = 0;
BOOLEAN                                 gAhciInit = FALSE;
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
AMI_NVME_PASS_THRU_PROTOCOL             *gSmmNvmePassThru = NULL;
#endif

EFI_GUID                                gSaveHddPasswordGuid = EFI_SMM_SAVE_HDD_PASSWORD_GUID;
EFI_GUID                                gRemoveHddPasswordGuid = EFI_SMM_REMOVE_HDD_PASSWORD_GUID;
EFI_GUID                                gHddSecuritySendCommandDataBufferGuid = AMI_HDD_SECURITY_SEND_COMMAND_DATA_BUFFER_GUID;
EFI_GUID                                gHddSecurityBootScriptSaveTriggerGuid = AMI_HDD_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID;
EFI_GUID                                gNvmeSecurityBootScriptSaveTriggerGuid = AMI_NVME_SECURITY_BOOTSCRIPT_SAVE_TRIGGER_GUID;
EFI_GUID                                gHddSecLockBoxDataGuid = HDD_SEC_LOCK_BOX_DATA_GUID;
EFI_GUID                                gHddSecLockBoxMapDataGuid = HDD_SEC_LOCKBOX_MAP_DATA_GUID;

/** @internal
    Waits for the given bit to be cleared

    @param *pHddPassword        Pointer to HDD_PASSWORD
    @param BitClear             The bit to be cleared within time-out
    @param Timeout              Time limit before which the bit must be cleared.

    @retval EFI_SUCCESS         The bit is cleared before Time-out.
    @retval EFI_TIMEOUT         Time-out before the bit is cleared.

    @note
         1. In this function the wait time is 10 microseconds.
         
    @endinternal
**/
EFI_STATUS
SmmWaitforBitClear (
    IN HDD_PASSWORD        *pHddPassword,
    IN UINT8               BitClear,
    IN UINT32              Timeout
)
{
    UINT8                   Delay;
    UINT8                   Data8;

    for (; Timeout > 0; Timeout--) {
        for (Delay = 100; Delay > 0; Delay--) {
            Data8 = IoRead8 (pHddPassword->DeviceControlReg);
            if (!(Data8 & BitClear)) 
                return EFI_SUCCESS;
            MicroSecondDelay(10);                      // 10 Usec
        }
    }
    return EFI_TIMEOUT;
}

/** @internal
    Checks for a particular Bit to be set for a given amount of time 

    @param *pHddPassword        Pointer to HDD_PASSWORD
    @param BitSet               The bit to be set within the time-out
    @param Timeout              Time limit before which the bit must be set

    @retval EFI_SUCCESS         The bit is set before Time-out.
    @retval EFI_TIMEOUT         Time-out before the bit is set.

    @endinternal
**/

EFI_STATUS
SmmWaitforBitSet (
    IN HDD_PASSWORD                    *pHddPassword,
    IN UINT8                           BitSet,
    IN UINT32                          TimeOut
)
{
    UINT8           Delay;
    UINT8           Data8;

    for (; TimeOut > 0; TimeOut--) {
        for (Delay = 100; Delay > 0; Delay--) {
            Data8 = IoRead8 (pHddPassword->DeviceControlReg);
            if (Data8 & BitSet) {
                return EFI_SUCCESS;
            }
            MicroSecondDelay(10);                      // 10 Usec
        }
    }
    return EFI_TIMEOUT;
}

/** @internal
    Waits for BSY bit to get clear

    @param *pHddPassword        Pointer to HDD_PASSWORD

    @retval EFI_SUCCESS         BSY bit is cleared before time-out.
    @retval EFI_DEVICE_ERROR    Device error while waiting for clearing BSY bit

    @note  Wait for BSY bit to get clear. Check for any errors.

    @endinternal
**/
EFI_STATUS
SmmWaitForCmdCompletion (
    IN HDD_PASSWORD                    *pHddPassword
)
{
    UINT8                       Data8;
    EFI_STATUS                  Status;

    //  Read ATL_STATUS and ignore the result. Just a delay
    IoRead8 (pHddPassword->DeviceControlReg);
    
    //  Check for BSY bit to be clear
    Status = SmmWaitforBitClear (
                       pHddPassword, 
                       IDE_BSY, 
                       DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    //  Check for errors. 
    Data8 = IoRead8 (pHddPassword->BaseAddress + 7);

    if (Data8 & (IDE_ERR | IDE_DF)) {
        return EFI_DEVICE_ERROR;  
    }

    return EFI_SUCCESS;
}

/** @internal
    This function Locates the AhciSmm protocol from the Smm

    @param *VariableGuid         Pointer to GUID value that uniquely identifies 
                                    the system configuration table.
    @param **VariablePointer     Pointer to the table associated with VariableGuid.

    @retval EFI_SUCCESS          AhciSmm protocol is located.
    @retval EFI_NOT_FOUND        AhciSmm protocol is not found.

    @endinternal
**/
EFI_STATUS
LocateSmmServices (
    IN  EFI_GUID    *VariableGuid,
    IN  VOID        **VariablePointer
)
{
    UINTN           Index;

    for (Index = 0; Index < gSmst->NumberOfTableEntries; ++Index) {
        if (CompareGuid(&gSmst->SmmConfigurationTable[Index].VendorGuid,VariableGuid)) {
            break;
        }
    }

    if (Index != gSmst->NumberOfTableEntries) {
        *VariablePointer = gSmst->SmmConfigurationTable[Index].VendorTable;
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

/** @internal
    This function Locates the AHCI SMM protocols and saves in global pointer

    @param VOID

    @return VOID

    @endinternal
**/
VOID 
LocateAhciSmmProtocols()
{
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )
    if (mAhciSmm == NULL) {
        LocateSmmServices (
                    &gAmiAhciSmmProtocolGuid,
                    (VOID **)&mAhciSmm);
    }
#endif
}

/** @internal
    This Function unlocks HDD password during S3 resume in 
    Ahci Mode Using Int 13.

    @param *pHddPassword        Pointer to HDD_PASSWORD

    @retval EFI_SUCCESS         HDD password is unlocked in Ahci mode
    @retval EFI_DEVICE_ERROR    Device error in unlocking the HDD password.
    
    @endinternal
**/
EFI_STATUS
SmmAhciSecurityUnlockCommand (
    IN HDD_PASSWORD                    *pHddPassword
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )    
    UINT32                      AhciBar = 0;
    UINT8                       Index;
    UINT8                       SccReg;
    BOOLEAN                     ControllerinAhciMode = FALSE;
    UINT32                      GlobalControl;
    COMMAND_STRUCTURE           CommandStructure;
    UINT32                      NoOfPorts = 0;
    UINT64                      FisBaseAddress = 0;
    UINT64                      OrgFisBaseAddress = 0;
    UINT64                      PortCommandListBaseAddr = 0;
    VOID                        *Mapping = NULL;
    UINTN                       Size = 512;
    EDKII_IOMMU_OPERATION       Operation;
    EDKII_IOMMU_PROTOCOL        *EdkiiIoMmu = NULL;
    BOOLEAN                     ValidPwd = FALSE;
    
    LocateAhciSmmProtocols ();
    if (mAhciSmm == NULL) {
        return EFI_NOT_FOUND;
    }

    //    1. Check if Controller is in AHCI Mode.
    //    2. Read ABAR Offset and Get HbaAddress.
    //    3. Disable AHCI_ENABLE. 
    //    4. Issue Controller Reset. 
    //    5. Wait for HBA Reset to Complete.
    //    6. Enable AHCI_ENABLE.

    AhciBar = PciRead32 (PCI_LIB_ADDRESS (
                                    pHddPassword->BusNo,
                                    pHddPassword->DeviceNo,
                                    pHddPassword->FunctionNo,
                                    AHCI_BAR ));
    AhciBar &= 0xFFFFFFF0;
    
    mAhciSmm->AhciBaseAddress = AhciBar;

    // Find Number of Ports from BIT0:BIT4 of the HBA_CAP register
    NoOfPorts = ((MmioRead32 (AhciBar + HBA_CAP)) & HBA_CAP_NP_MASK) + 1;

    // Check if AHCI MMIO address space resides in SMRAM region. If yes, don't proceed.
    if (AmiValidateMmioBuffer (
                    (VOID *)(UINTN)mAhciSmm->AhciBaseAddress, 
                    HBA_PORTS_START + (NoOfPorts * HBA_PORTS_REG_WIDTH))) {
        return EFI_NOT_FOUND;
    }

    if (!gAhciInit) {
        SccReg = PciRead8 (PCI_LIB_ADDRESS (
                                pHddPassword->BusNo,
                                pHddPassword->DeviceNo,
                                pHddPassword->FunctionNo,
                                PCI_SCC ));   // Get Scc Register;
        if ((SccReg & 0x06) || (SccReg & 0x04)) { 
            ControllerinAhciMode = TRUE;
        }

        if (ControllerinAhciMode) {
            GlobalControl = MmioRead32 (AhciBar + 0x04);

            GlobalControl &= 0x7FFFFFFF;
            MmioWrite32 (AhciBar + 0x04, GlobalControl);

            GlobalControl = 0x01;
            MmioWrite32 (AhciBar + 0x04, GlobalControl);

            MicroSecondDelay (5000);   // 5 milliSec Delay

            GlobalControl = 0x80000000;
            MmioWrite32 (AhciBar + 0x04, GlobalControl);

            MicroSecondDelay (1000000);   // 1 Second Delay
        }
        gAhciInit = TRUE;
    }   

    // If unlock buffer not available, return error
    if (gSecurityUnlockCommandBuffer == NULL) {
        return EFI_UNSUPPORTED;
    }
    
    //  Clear the Buffer
    ZeroMem (gSecurityUnlockCommandBuffer, 512);
    gSecurityUnlockCommandBuffer[0] = pHddPassword->Control & BIT0;
    if (gSecurityUnlockCommandBuffer[0]) {
        //Copy 32 Bytes of Password
        CopyMem (&gSecurityUnlockCommandBuffer[2], pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
    } else {
        //Copy 32 Bytes of Password
        CopyMem (&gSecurityUnlockCommandBuffer[2], pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
    }
    
    //Locate the Edk2IommuProtocol
    Status = gSmst->SmmLocateProtocol (
                                &gEdkiiIoMmuProtocolGuid, 
                                NULL, 
                                (VOID**)&EdkiiIoMmu );
    
    if (!EFI_ERROR(Status) && EdkiiIoMmu) { 
        Status = EdkiiIoMmu->AllocateBuffer (
                                       EdkiiIoMmu,
                                       0,
                                       0,
                                       EFI_SIZE_TO_PAGES(RECEIVED_FIS_SIZE + 0x100), 
                                       (VOID**)&FisBaseAddress,
                                       0 );
        ASSERT_EFI_ERROR (Status);
        
        // Store IOMMU allocated buffer in both variables as Mapped address is used in controller init
        OrgFisBaseAddress = mAhciSmm->PortFISBaseAddr;
        mAhciSmm->PortFISBaseAddr = mAhciSmm->PortFISMappedBaseAddr = ((FisBaseAddress & (~0xFF))+ 0x100);
        ZeroMem ((VOID *)mAhciSmm->PortFISBaseAddr, RECEIVED_FIS_SIZE);
        
        Status = EdkiiIoMmu->AllocateBuffer (
                                    EdkiiIoMmu,
                                    0,
                                    0,
                                    EFI_SIZE_TO_PAGES(COMMAND_LIST_SIZE_PORT * 2),
                                    (VOID**)&PortCommandListBaseAddr,
                                    0 );
        ASSERT_EFI_ERROR (Status);
        mAhciSmm->PortCommandListBaseAddr  = mAhciSmm->PortCommandListMappedBaseAddr = PortCommandListBaseAddr;
        mAhciSmm->PortCommandTableBaseAddr = mAhciSmm->PortCommandTableMappedBaseAddr = mAhciSmm->PortCommandListMappedBaseAddr + 0x80;
        
        ZeroMem ((VOID *)mAhciSmm->PortCommandListBaseAddr, COMMAND_LIST_SIZE_PORT);
        
        Operation = EdkiiIoMmuOperationBusMasterRead;
        Status = EdkiiIoMmu->Map(
                                EdkiiIoMmu, 
                                Operation,
                                gSecurityUnlockCommandBuffer,
                                &Size,
                                &gSecurityUnlockCommandBufferMapped,
                                &Mapping);
        ASSERT_EFI_ERROR (Status);
    }
    //
    //Resuming from S3. So bring back the AHCI controller to working state
    //
    mAhciSmm->AhciSmmInitPortOnS3Resume (mAhciSmm,(UINT8)pHddPassword->PortNumber);
    
    // Password data will start after two bytes.
    // Checking whether Password data is non-zero to issue to Unlock cmd
    for (Index = 0; Index < IDE_PASSWORD_LENGTH; Index++) {
        if (gSecurityUnlockCommandBuffer[Index+2] != 0) {
            ValidPwd = TRUE;
            break;
        }
    }
     
     // Password data will start after two bytes.
     // Checking whether Password data is non-zero to issue to Unlock cmd
     if (ValidPwd){
    
         //Setup the Unlock command 
         ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
         CommandStructure.SectorCount = 1;
         CommandStructure.LBALow = 0;
         CommandStructure.LBAMid = 0;
         CommandStructure.LBAHigh = 0;
         CommandStructure.Device = 0x40;
         CommandStructure.Command = SECURITY_UNLOCK;
         CommandStructure.Buffer = gSecurityUnlockCommandBufferMapped ? (VOID *)gSecurityUnlockCommandBufferMapped : gSecurityUnlockCommandBuffer;
         CommandStructure.ByteCount = 512;
         //
         //Issue the unlock command
         //
         Status = mAhciSmm->AhciSmmExecutePioDataCommand ( 
                                                   mAhciSmm,
                                                   &CommandStructure,
                                                   (UINT8)pHddPassword->PortNumber,
                                                   0xFF,
                                                   ATA,
                                                   TRUE );
         DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a AHCI Security Unlock Status = %r",__FUNCTION__, Status));
     }
 
#if DISABLE_SOFT_SET_PREV 
    ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = DISABLE_SATA2_SOFTPREV;         // Disable Software Preservation
    CommandStructure.SectorCount = 6;
    CommandStructure.Command = SET_FEATURE_COMMAND;

    mAhciSmm->AhciSmmExecuteNonDataCommand (
                                     mAhciSmm,
                                     CommandStructure,
                                     (UINT8)pHddPassword->PortNumber,
                                     0xFF,
                                     ATA );
#endif

    //
    //Issue the Security Freeze lock command
    //
    ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Command = SECURITY_FREEZE_LOCK;
    Status = mAhciSmm->AhciSmmExecuteNonDataCommand (
                                              mAhciSmm,
                                              CommandStructure,
                                              (UINT8)pHddPassword->PortNumber,
                                              0xFF,
                                              ATA );
    
    DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a AHCI FreezaeLock Cmd Status = %r",__FUNCTION__, Status));

    //Issue the Device configure Freeze lock command 
    ZeroMem (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Command = DEV_CONFIG_FREEZE_LOCK;
    CommandStructure.Features = DEV_CONFIG_FREEZE_LOCK_FEATURES;
    Status = mAhciSmm->AhciSmmExecuteNonDataCommand ( 
                                              mAhciSmm,
                                              CommandStructure,
                                              (UINT8)pHddPassword->PortNumber,
                                               0xFF,
                                               ATA );
    DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a AHCI DCO FreezaeLock Cmd Status = %r",__FUNCTION__, Status));
    //clear the password buffer
    ZeroMem (gSecurityUnlockCommandBuffer, 512);

    if (EdkiiIoMmu) {
    
        if (Mapping){
            EdkiiIoMmu->Unmap(EdkiiIoMmu, Mapping);    
            gSecurityUnlockCommandBufferMapped = 0;
        }
        
        Status = EdkiiIoMmu->FreeBuffer (
                                    EdkiiIoMmu,
                                    EFI_SIZE_TO_PAGES(COMMAND_LIST_SIZE_PORT * 2),
                                    (void *)PortCommandListBaseAddr );
        ASSERT_EFI_ERROR (Status);
        
        Status = EdkiiIoMmu->FreeBuffer (
                                    EdkiiIoMmu,
                                    EFI_SIZE_TO_PAGES(RECEIVED_FIS_SIZE + 0x100),
                                    (void *)FisBaseAddress );
        ASSERT_EFI_ERROR (Status);
        
        mAhciSmm->PortFISBaseAddr = OrgFisBaseAddress;
    }
#endif
    return Status;
}


/** @internal
    Issues Set Feature command (Non Data)

    @param *pHddPassword       Pointer to HDD_PASSWORD
    @param Features            Hdd commands written to the given port.
    @param SectorCount         Command structure written to the given port.
    @param LBALow              Location of Block of data written to the given port.
    @param LBAMid              Location of Block of data written to the given port.
    @param LBAHigh             Location of Block of data written to the given port.
    @param Command             Security commands written to the given port.

    @retval EFI_SUCCESS             The command issued successfully.
    @retval EFI_DEVICE_ERROR        Device error when checking for controller presence.
    @retval EFI_TIMEOUT             Time to wait for BSY and DRQ bit has crossed the required time.

    @endinternal
**/
EFI_STATUS 
SmmIdeNonDataCommand (
    IN  HDD_PASSWORD                     *pHddPassword,
    IN  UINT8                            Features,
    IN  UINT8                            SectorCount,
    IN  UINT8                            LBALow,
    IN  UINT8                            LBAMid,
    IN  UINT8                            LBAHigh,
    IN  UINT8                            Command
) 
{

    EFI_STATUS                      Status;
    UINT8                           Data8;

    //  Select the drive
    IoWrite8 (
          pHddPassword->BaseAddress + 6, 
          pHddPassword->Device << 4 );

    //  Check for Controller presence
    Data8 = IoRead8 (pHddPassword->DeviceControlReg);
    if (Data8 == 0xFF) {
        ASSERT (Data8 != 0xFF);
        return EFI_DEVICE_ERROR;
    }

    //  Before Writing to Sector Count Register, BSY and DRQ bit should be zero
    Status = SmmWaitforBitClear (pHddPassword, IDE_BSY, S3_BUSY_CLEAR_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    //  Check for DRDY
    Status = SmmWaitforBitSet (pHddPassword, IDE_DRDY, DRDY_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return EFI_TIMEOUT;
    }

    //  Issue command
    IoWrite8 (pHddPassword->BaseAddress + 1, Features);
    IoWrite8 (pHddPassword->BaseAddress + 2, SectorCount);
    IoWrite8 (pHddPassword->BaseAddress + 3, LBALow);
    IoWrite8 (pHddPassword->BaseAddress + 4, LBAMid);
    IoWrite8 (pHddPassword->BaseAddress + 5, LBAHigh);
    IoWrite8 (pHddPassword->BaseAddress + 7, Command);

    return EFI_SUCCESS;
}

/** @internal
    This Function unlocks HDD password during S3 resume.

    @param *pHddPassword        Pointer to HDD_PASSWORD

    @retval EFI_SUCCESS         HDD password is unlocked
    @retval EFI_DEVICE_ERROR    Device error in unlocking the HDD password.

    @endinternal
**/
EFI_STATUS
SmmIdeSecurityUnlockCommand (
    IN HDD_PASSWORD                    *pHddPassword
)
{
    EFI_STATUS                      Status;
    UINT8                           Data8;
    UINT16                          Reg;
    UINT16                          Count;
    VOID                            *Buffer;

    //  Disable Interrupt
    IoWrite8 (pHddPassword->DeviceControlReg, 2);

    //  Select the drive
    IoWrite8 (pHddPassword->BaseAddress + 6, pHddPassword->Device << 4);

    //  Wait for BSY to go low
    Status = SmmWaitforBitClear (pHddPassword, IDE_BSY, S3_BUSY_CLEAR_TIMEOUT);
    if (EFI_ERROR(Status)) 
        return EFI_DEVICE_ERROR;

    //  Clear the Buffer
    ZeroMem (gSecurityBuffer, 512);

    gSecurityBuffer[0] = pHddPassword->Control & BIT0;

    if (gSecurityBuffer[0]) {
        //  Copy 32 Bytes of Passwordfrom offset 2 for word aligned password buffer
        CopyMem (&gSecurityBuffer[2], pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
    } else {
        // Copy 32 Bytes of Password from offset 2 for word aligned password buffer
        CopyMem (&gSecurityBuffer[2], pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
    }

    Status = SmmIdeNonDataCommand (
                             pHddPassword, 
                             0,
                             0,
                             0,
                             0,
                             0, 
                             SECURITY_UNLOCK ); 
    DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a IDE Security Unlock Status = %r",__FUNCTION__, Status));
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    //  Wait for Command completion
    Status = SmmWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    //  Check for DRQ
    Status = SmmWaitforBitSet (pHddPassword, IDE_DRQ, DRQ_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    Reg = pHddPassword->BaseAddress;
    Buffer = gSecurityBuffer;
//  Status = IdeWriteMultipleWord (pHddPassword->BaseAddress, 256, &SecurityBuffer);
    Count = 256;
    while (Count--) {
        IoWrite16 (Reg, *(UINT16 *)Buffer);
        Reg = Reg + 2;
        Buffer  = (UINT8 *)Buffer + 2;
    }

    //  Wait for Command completion
    Status = SmmWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    //  Check for errors. 
    Data8 = IoRead8 (pHddPassword->BaseAddress + 7);
    if (Data8 & 0x21) {          // ERR OR DF bit set ?
        return EFI_DEVICE_ERROR;  
    }

#if DISABLE_SOFT_SET_PREV 
    Status = SmmIdeNonDataCommand (
                            pHddPassword, 
                            DISABLE_SATA2_SOFTPREV,
                            6,
                            0,
                            0,
                            0, 
                            SET_FEATURE_COMMAND );

    if (EFI_ERROR(Status)) {
        return Status;
    }
    //  Check for errors
    Status = SmmWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) {
        return Status;
    }
#endif

    Status = SmmIdeNonDataCommand (
                            pHddPassword, 
                            DEV_CONFIG_FREEZE_LOCK_FEATURES,
                            0,
                            0,
                            0,
                            0, 
                            DEV_CONFIG_FREEZE_LOCK );
    if (EFI_ERROR(Status)) {
        return Status;
    }

     // Wait for Command completion
    Status = SmmWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return EFI_SUCCESS;
}

#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
/** @internal
    Routine to get Nvme controller security data

    @param *SmmNvmeController       Pointer to AMI_NVME_CONTROLLER_PROTOCOL
    @param *SecurityStatus          Pointer to security status of Nvme device.

    @retval EFI_SUCCESS      Nvme device security status returned successfully.
    @return Other            Return error status.      

    @endinternal
**/
EFI_STATUS
GetNvmeDeviceSecurityStatus(
    IN AMI_NVME_CONTROLLER_PROTOCOL  *SmmNvmeController,
    IN UINT16                        *SecurityStatus 
)
{
    EFI_STATUS                      Status;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper = SmmNvmeController->NvmeCmdWrapper;
    NVME_SECURITY_RECEIVE_BUFFER    *SecReceiveBuffer;
    COMPLETION_QUEUE_ENTRY          *NvmeCompletionData;  // Use Global buffer for NVMe completion entry
    EDKII_IOMMU_PROTOCOL            *EdkiiIoMmu = NULL;
    EDKII_IOMMU_OPERATION           Operation;
    VOID                            *Mapping = NULL;
    UINTN                           Size = 512; // allocate the  size as 512 
    
    // If unlock buffer not available, return error
    if (gSecurityUnlockCommandBuffer == NULL) {
        return EFI_UNSUPPORTED;
    }
    
    if (gSmmNvmePassThru == NULL) {
        Status = gSmst->SmmLocateProtocol (
                                    &gAmiSmmNvmePassThruProtocolGuid, 
                                    NULL, 
                                    (VOID **)&gSmmNvmePassThru);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    SecReceiveBuffer = (NVME_SECURITY_RECEIVE_BUFFER *)gSecurityUnlockCommandBuffer;
    NvmeCompletionData = (COMPLETION_QUEUE_ENTRY *)(gSecurityUnlockCommandBuffer+100);  // Use Global buffer for NVMe completion entry
     // Locate EdkiiIoMmuProtocol
    Status = gSmst->SmmLocateProtocol (
                                &gEdkiiIoMmuProtocolGuid, 
                                NULL, 
                                (VOID**)&EdkiiIoMmu );

    if (!EFI_ERROR(Status) && EdkiiIoMmu) {
        
        Operation = EdkiiIoMmuOperationBusMasterWrite;
        Status = EdkiiIoMmu->Map (
                          EdkiiIoMmu,
                          Operation,
                          SecReceiveBuffer,
                          &Size,
                          &gSecurityUnlockCommandBufferMapped,
                          &Mapping );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        SecReceiveBuffer = (NVME_SECURITY_RECEIVE_BUFFER *)gSecurityUnlockCommandBufferMapped;
        NvmeCompletionData = (COMPLETION_QUEUE_ENTRY *) (gSecurityUnlockCommandBufferMapped + 100);
    }

    ZeroMem (NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    ZeroMem (SecReceiveBuffer,  sizeof(NVME_SECURITY_RECEIVE_BUFFER));
    ZeroMem (NvmeCompletionData, sizeof(COMPLETION_QUEUE_ENTRY));
    
    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = SECURITY_RECEIVE;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;
#if NVME_DRIVER_VERSION > 10
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->NvmeDxeSmmDataArea->CommandIdentifierAdmin;
#else
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->CommandIdentifierAdmin;
#endif
    NvmeCmdWrapper->NvmCmd.NSID = 0;
    NvmeCmdWrapper->NvmCmd.MPTR = 0;
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;  // Queue 0 for Admin cmds,1 for I/O command
    NvmeCmdWrapper->CmdTimeOut = NVME_COMMAND_TIMEOUT * 0x1000;
    
    NvmeCmdWrapper->NvmCmd.CDW10 = (((UINT32)NVME_SECUIRTY_SECP)<<24);
    NvmeCmdWrapper->NvmCmd.CDW11 = 0x10;
    NvmeCmdWrapper->NvmCmd.PRP1 = gSecurityUnlockCommandBufferMapped ? gSecurityUnlockCommandBufferMapped : (UINT64)gSecurityUnlockCommandBuffer;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    
    Status = gSmmNvmePassThru->ExecuteNvmeCmd (
                                      SmmNvmeController, 
                                      NvmeCmdWrapper, 
                                      NvmeCompletionData );

    if (Mapping){
        EdkiiIoMmu->Unmap(EdkiiIoMmu, Mapping);    
        gSecurityUnlockCommandBufferMapped = 0;
    }
    // Return Nvme device security status
    *SecurityStatus  = (SecReceiveBuffer->NvmeSecStatus >> 8) | (SecReceiveBuffer->NvmeSecStatus << 8);
    DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Nvme Device Security Status = %x",__FUNCTION__ ,*SecurityStatus));
    return Status;
}

/** @internal

Called from InstallSmiHandler


@param ImageHandle Image handle

@param *SystemTable Pointer to EFI_SYSTEM_TABLE


@retval EFI_SUCCESS SMI handler added successfully.

@retval EFI_INVALID_PARAMETER Handler is NULL or DispatchHandle is NULL. 


@endinternal

**/
EFI_STATUS
SendNvmeFreezeLockCommand (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *SmmNvmeController
)
{
    EFI_STATUS                          Status;
    NVME_COMMAND_WRAPPER                *NvmeCmdWrapper = SmmNvmeController->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY              NvmeCompletionData;

    //  Clear the Buffer
    ZeroMem (NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));

    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = SECURITY_SEND;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;

#if NVME_DRIVER_VERSION > 10
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->NvmeDxeSmmDataArea->CommandIdentifierAdmin;
#else
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->CommandIdentifierAdmin;
#endif

    NvmeCmdWrapper->NvmCmd.NSID = 0;
    NvmeCmdWrapper->NvmCmd.MPTR = 0;
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;  // Queue 0 for Admin cmds,1 for I/O command
    NvmeCmdWrapper->CmdTimeOut = NVME_COMMAND_TIMEOUT * 0x1000;
    
    NvmeCmdWrapper->NvmCmd.CDW10 = (((UINT32)NVME_SECUIRTY_SECP)<<24) + (((UINT32)NVME_ATA_SECURITY_FREEZE_LOCK)<<8);
    NvmeCmdWrapper->NvmCmd.CDW11 = 0;
    
    Status = gSmmNvmePassThru->ExecuteNvmeCmd (
                                      SmmNvmeController, 
                                      NvmeCmdWrapper, 
                                      &NvmeCompletionData );

    return Status;
}

/** @internal
    Routine sends SecurityUnlock command to Nvme controller

    @param *SmmNvmeController        Pointer to AMI_NVME_CONTROLLER_PROTOCOL
    @param *pHddPassword             Pointer to HDD_PASSWORD

    @retval EFI_SUCCESS       SecurityUnlock command is sent to Nvme controller
    @return Other             Return error status.
    
    @note
         1. Clear the NvmeCmdWrapper and buffer.
         2. Check for user/master password and copy them to Buffer.
         3. Clear NameSpaceId and MetaDataPointer and set Command set as Admin.
    @endinternal
**/
EFI_STATUS
SendNvmeSecurityUnlockCommand (
    IN AMI_NVME_CONTROLLER_PROTOCOL    *SmmNvmeController,
    IN HDD_PASSWORD                    *pHddPassword
)
{
    EFI_STATUS                      Status;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper = SmmNvmeController->NvmeCmdWrapper;
    UINT8                           *Buffer;
    COMPLETION_QUEUE_ENTRY          NvmeCompletionData;
    EDKII_IOMMU_PROTOCOL            *EdkiiIoMmu = NULL;
    EDKII_IOMMU_OPERATION           Operation;
    VOID                            *Mapping = NULL;
    UINTN                           Size = 512;
    
    // If unlock buffer not available, return error
    if (gSecurityUnlockCommandBuffer == NULL) {
        return EFI_UNSUPPORTED;
    }
    
    if (gSmmNvmePassThru == NULL) {
        Status = gSmst->SmmLocateProtocol(
                                &gAmiSmmNvmePassThruProtocolGuid, 
                                NULL, 
                                (VOID **)&gSmmNvmePassThru);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    Buffer = gSecurityUnlockCommandBuffer;
    //SMM IOMMU
    Status = gSmst->SmmLocateProtocol (
                                &gEdkiiIoMmuProtocolGuid, 
                                NULL, 
                                (VOID**)&EdkiiIoMmu );
    
    if (!EFI_ERROR(Status) && EdkiiIoMmu){
     
        Operation = EdkiiIoMmuOperationBusMasterRead;
        Status = EdkiiIoMmu->Map (
                                EdkiiIoMmu,
                                Operation,
                                gSecurityUnlockCommandBuffer,
                                &Size,
                                &gSecurityUnlockCommandBufferMapped,
                                &Mapping );
        if (EFI_ERROR(Status)){
            return Status;
        }
    }
    
    //  Clear the Buffer
    ZeroMem (NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    ZeroMem (Buffer, 512);

    Buffer[1] = (UINT8)(pHddPassword->Control & BIT0);

    // Buffer[1] will 0/1 i.e. User/Master password
    if( Buffer[1] ){
        // Match has been found. Just copy the Password buffer
        CopyMem (&Buffer[2], pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
    } else {
        // Match has been found. Just copy the Password buffer
        CopyMem (&Buffer[2], pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
    }

    NvmeCmdWrapper->NvmCmd.CMD0.Opcode = SECURITY_SEND;
    NvmeCmdWrapper->NvmCmd.CMD0.FusedOperation = 0;

#if NVME_DRIVER_VERSION > 10
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->NvmeDxeSmmDataArea->CommandIdentifierAdmin;
#else
    NvmeCmdWrapper->NvmCmd.CMD0.CommandIdentifier = SmmNvmeController->CommandIdentifierAdmin;
#endif

    NvmeCmdWrapper->NvmCmd.NSID = 0;
    NvmeCmdWrapper->NvmCmd.MPTR = 0;
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SQIdentifier = 0;  // Queue 0 for Admin cmds,1 for I/O command
    NvmeCmdWrapper->CmdTimeOut = NVME_COMMAND_TIMEOUT * 0x1000;
    
    NvmeCmdWrapper->NvmCmd.CDW10 = (((UINT32)NVME_SECUIRTY_SECP)<<24) + (((UINT32)NVME_ATA_SECURITY_UNLOCK)<<8);
    NvmeCmdWrapper->NvmCmd.CDW11 = NVME_SECURITY_SEND_BUFFER_SIZE;
    NvmeCmdWrapper->NvmCmd.PRP1  = gSecurityUnlockCommandBufferMapped ? gSecurityUnlockCommandBufferMapped : (UINT64)gSecurityUnlockCommandBuffer;
    NvmeCmdWrapper->NvmCmd.PRP2 = 0;
    
    Status = gSmmNvmePassThru->ExecuteNvmeCmd (
                                      SmmNvmeController, 
                                      NvmeCmdWrapper, 
                                      &NvmeCompletionData );
    // clear password
    ZeroMem (Buffer, 512);

    if (Mapping){
        EdkiiIoMmu->Unmap(EdkiiIoMmu, Mapping);    
        gSecurityUnlockCommandBufferMapped = 0;
    }
    return Status;
}

/** @internal
    This function Locates the protocols to access Nvme controller and saves in global pointer

    @param NvmeControllerHandle       Nvme Controller Handle
    @param **SmmNvmeController        Pointer to AMI_NVME_CONTROLLER_PROTOCOL

    @retval EFI_SUCCESS              The required protocol is located.
    @retval EFI_NOT_FOUND            The required protocol is not found.
    @retval EFI_BUFFER_TOO_SMALL     The buffer is not sufficient to hold the data.

    @endinternal
**/
EFI_STATUS 
LocateNvmeSmmProtocols (
    IN EFI_HANDLE                    NvmeControllerHandle,
    IN AMI_NVME_CONTROLLER_PROTOCOL  **SmmNvmeController
)
{
    EFI_STATUS                  Status = EFI_NOT_FOUND;
    EFI_HANDLE                  *HandleBuffer = NULL;
    UINTN                       HandleBufferSize = 0;
    UINTN                       Index;

    Status = gSmst->SmmLocateHandle (
                              ByProtocol, 
                              &gAmiSmmNvmeControllerProtocolGuid,
                              NULL,
                              &HandleBufferSize, 
                              HandleBuffer );
        
    if (EFI_ERROR(Status)) {
        if (Status == EFI_BUFFER_TOO_SMALL) {
            HandleBuffer = AllocateRuntimePool (HandleBufferSize);
            if (HandleBuffer == NULL) {
                return EFI_OUT_OF_RESOURCES;
            }

            Status = gSmst->SmmLocateHandle (
                                      ByProtocol, 
                                      &gAmiSmmNvmeControllerProtocolGuid,
                                      NULL,
                                      &HandleBufferSize, 
                                      HandleBuffer );
        }
    }
    
    if (HandleBuffer == NULL) {
        return EFI_NOT_FOUND;
    }

    if (!EFI_ERROR(Status)) {
        for (Index = 0; Index < HandleBufferSize / sizeof(EFI_HANDLE); Index++) {
            Status = gSmst->SmmHandleProtocol (
                                      HandleBuffer[Index], 
                                      &gAmiSmmNvmeControllerProtocolGuid, 
                                      (VOID **)SmmNvmeController );
                
            if (!EFI_ERROR(Status) && (*SmmNvmeController)->ControllerHandle == NvmeControllerHandle) {
                Status = EFI_SUCCESS;
                break;
            }
        }

        if (Index == (HandleBufferSize / sizeof(EFI_HANDLE))) {
            Status = EFI_NOT_FOUND;
        }
    }

    // Free HandleBuffer memory
    FreePool(HandleBuffer);

    return Status;
}
#endif

/** @internal
    Routine to Unlock Nvme controller

    @param pHddPassword       Pointer to HDD_PASSWORD

    @retval EFI_SUCCESS           Nvme Controller is unlocked successfully
    @retval EFI_DEVICE_ERROR      Failed to Unlock the Nvme Controller.

    @note 
        1. Locate the protocols to access Nvme controller.
        2. Initialize Nvme in S3 path.
        3. Check if the device is locked. if yes unlock the device.
    @endinternal
**/
EFI_STATUS
SmmUnlockNvmeDevice (
    HDD_PASSWORD    *pHddPassword
)
{
    EFI_STATUS                    Status = EFI_SUCCESS;
#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) )
    UINT16                        SecurityStatus;
    AMI_NVME_CONTROLLER_PROTOCOL  *SmmNvmeController = NULL;
    UINT64                        NvmeBarOffset = 0;

    if (EFI_ERROR(LocateNvmeSmmProtocols (pHddPassword->DevHandle, &SmmNvmeController))) {
        return EFI_DEVICE_ERROR;
    }
    
    // Check if the controller is already running. If yes check the Admin Completion Queue base address.
    NvmeBarOffset = SmmNvmeController->NvmeBarOffset;
    if (MmioRead32 (NvmeBarOffset + Offset_CC) & BIT0) {
        if (MmioRead32 (NvmeBarOffset + Offset_CSTS) & BIT0) {
            // If Admin Completion Queue base address is not the same as the one AMI NVME bus driver loaded 
            // we should not unlock the device.
            // This is to prevent device unlocking, if SMI is invoked from a source other than during S3 resume.
            if (MmioRead64 (NvmeBarOffset + Offset_Acq) != SmmNvmeController->AdminCompletionQueueMappedAddr) {
                DEBUG((DEBUG_VERBOSE,"\n %a : Unlock Password can't be proceeded !! Admin Completion Queue",__FUNCTION__));
                DEBUG((DEBUG_VERBOSE," Address is not matched with Aptio NVMe driver assigned value\n"));
                return EFI_UNSUPPORTED;
            }
        }
    }

    Status = SmmNvmeController->NvmeInitController (SmmNvmeController);

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    Status = GetNvmeDeviceSecurityStatus (
                                SmmNvmeController,
                                &SecurityStatus );

    // if Nvme device is locked, send Unlock command
    if (!EFI_ERROR(Status) && (SecurityStatus & NVME_SECURITY_LOCK_MASK)) {
        Status = SendNvmeSecurityUnlockCommand (
                                         SmmNvmeController,
                                         pHddPassword );
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Nvme Security Unlock Status = %r",__FUNCTION__ ,Status));
    }
    if (!EFI_ERROR(Status))  {
        // Freeze Lock command will not work with the Nvme in Locked State.
        // if the Nvme is either in Locked State or Frozen state, not issuing Frezelock
        // Bit3 : Security Freeze Lock status
        
        if (!(SecurityStatus & BIT3)) {
            Status = SendNvmeFreezeLockCommand (SmmNvmeController);
            DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Nvme FreezeLock Cmd Status = %r",__FUNCTION__, Status));
        }
    }
    

    // Function used to stop/release resources in S3 path
    Status = SmmNvmeController->NvmeStopController (SmmNvmeController);
#endif
    return Status;
}

/** 
  Save the RAID device data to LockBox.
  
  @param[in]  HddPassword      Password buffer to store in LockBox
  
  @retval EFI_STATUS
**/
EFI_STATUS
SaveToLockBox (
    IN HDD_PASSWORD     *HddPassword
) 
{
    EFI_STATUS                        Status;
    UINTN                             LockBoxSize;
    static UINTN                      DeviceCount = 0;
    UINT16                            Index;
    RAID_LOCK_BOX_DATA                *LockBoxData;
    VOID                              *PasswordPtr;
    
    // Maintain local LockBox data to avoid updating LockBox with same device data again
    if (gLockBoxData == NULL) {
        
        gLockBoxData = LockBoxData = AllocateZeroPool (sizeof(RAID_LOCK_BOX_DATA));
        
    } else {
        
        for (Index = 0; Index < DeviceCount; Index++) {
            if (CompareMem (gLockBoxData[Index].ModelSerialNo, HddPassword->ModelSerialNo, sizeof(HddPassword->ModelSerialNo)) == 0) {
                break;
            }
        }
        
        // Data already present in LockBox
        if (Index < DeviceCount) {
            LockBoxData = &gLockBoxData[Index];
        } else {
        
            gLockBoxData = ReallocatePool (
                                    DeviceCount * sizeof(RAID_LOCK_BOX_DATA),        // OldSize
                                    (DeviceCount + 1) * sizeof(RAID_LOCK_BOX_DATA),    // NewSize
                                    gLockBoxData );
            LockBoxData = &gLockBoxData[DeviceCount];
        }
    }
    
    LockBoxData->IsTcgPwd = FALSE;
    LockBoxData->IsMasterPwd = (BOOLEAN)HddPassword->Control;
    LockBoxData->IsRaidHdd = HddPassword->IsRaidHdd;
    
    // Copy Password to LockBox.
    if (LockBoxData->IsMasterPwd) {
        PasswordPtr = HddPassword->MasterPassword;
    } else {
        PasswordPtr = HddPassword->UserPassword;
    }
    
    if (PasswordPtr == NULL) {
        return EFI_NOT_FOUND;
    }
    
    CopyMem (LockBoxData->PwdBuffer, PasswordPtr, IDE_PASSWORD_LENGTH);
    CopyMem (LockBoxData->ModelSerialNo, HddPassword->ModelSerialNo, sizeof(HddPassword->ModelSerialNo));
    
    LockBoxSize = ((DeviceCount + 1) * sizeof(RAID_LOCK_BOX_DATA));
    
    Status = SaveLockBox ( 
                     &gHddSecLockBoxDataGuid,
                     gLockBoxData, 
                     LockBoxSize );
    if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED))
        return Status;
    
    if (Status == EFI_SUCCESS) {
        // This case will be entered on first time saving data to SMM lock box.
        // So enable the required lock box attributes.
        Status = SetLockBoxAttributes (
                           &gHddSecLockBoxDataGuid,
                           LOCK_BOX_ATTRIBUTE_RESTORE_IN_S3_ONLY );
    } else if (Status == EFI_ALREADY_STARTED) {
        // Lock box already started, so update LockBox with local LockBox data.
        Status = UpdateLockBox (
                           &gHddSecLockBoxDataGuid,
                           0,
                           gLockBoxData,
                           LockBoxSize );
    }

    if (!EFI_ERROR(Status))
        DeviceCount++;

    return Status;
}

/** 
    Update Iommu Mapped Address.
  
    @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
    @param Context         Points to an optional handler context which was specified when the
                           handler was registered.
    @param CommBuffer      A pointer to a collection of data in memory that will
                           be conveyed from a non-SMM environment into an SMM environment.
    @param CommBufferSize  The size of the CommBuffer.
    
    @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
UpdateIommuMappedBufferHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
)
{
    EFI_STATUS                    Status;
    UINT8                         DeviceCount;
    UINT8                         Index;
    IOMMU_MAP_INFORMATION         *MapInfo;
    UINT8                         *Temp;
    UINTN                         Size = sizeof(Temp);

    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a() Invalid Pointer CommBuffer : %x CommBufferSize : %x\n", __FUNCTION__, CommBuffer, CommBufferSize));
        return EFI_SUCCESS;
    }
    
    Status = AmiValidateMemoryBuffer ((VOID*)CommBuffer, *CommBufferSize);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_VERBOSE ,"SmmHddSec: %a() CommBuffer overlaps with SMRAM region Status: %r\n", __FUNCTION__, Status));
        return EFI_SUCCESS;
    }
    // Added this check to confirm that this handler gets control only during S3 resume
    // RestoreLockBox() returns EFI_ACCESS_DENIED if LockBox data restored other than S3 resume path
    // as LOCK_BOX_ATTRIBUTE_RESTORE_IN_S3_ONLY is set
    // RestoreLockBox() returns EFI_BUFFER_TOO_SMALL in S3 resume path as mention LockBox size is less.
    Status = RestoreLockBox (
                        &gHddSecLockBoxMapDataGuid, 
                        &Temp, 
                        &Size );
    if (Status != EFI_BUFFER_TOO_SMALL) {
        DEBUG ((DEBUG_VERBOSE ,"SmmHddSec:%a() RestoreLockBox Status: %r\n", __FUNCTION__, Status));
        return EFI_SUCCESS;
    }

    DeviceCount = *(UINT8 *)CommBuffer;
    MapInfo = (IOMMU_MAP_INFORMATION *)((UINT8 *)CommBuffer + 1);
    
    for (Index = 0; Index < DeviceCount; Index++, MapInfo++) {
        
        if (MapInfo->BusInterfaceType == AmiStorageInterfaceAhci) {
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )
            if (MapInfo->Address1 != 0) { // If error occurred while mapping, then it'll be 0
                mAhciSmm->PortFISMappedBaseAddr = MapInfo->Address1;
                mAhciSmm->PortCommandListMappedBaseAddr = ALIGN_VALUE(mAhciSmm->PortFISMappedBaseAddr + RECEIVED_FIS_SIZE, 0x400);
                mAhciSmm->PortCommandTableMappedBaseAddr = mAhciSmm->PortCommandListMappedBaseAddr + 0x80;
            }
#endif
        } else if (MapInfo->BusInterfaceType == AmiStorageInterfaceNvme) {
#if ( defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0) )
            {
                AMI_NVME_CONTROLLER_PROTOCOL  *SmmNvmeController = NULL;
                if (EFI_ERROR(LocateNvmeSmmProtocols ((VOID *)MapInfo->DevHandle, &SmmNvmeController))) {
                    continue;
                }

                if ((MapInfo->Address1 != 0) && (MapInfo->Address2 != 0)) {
                    SmmNvmeController->AdminSubmissionQueueMappedAddr = MapInfo->Address1;
                    SmmNvmeController->AdminCompletionQueueMappedAddr = MapInfo->Address2;
                }
            }
#endif
        } else if (MapInfo->DevHandle == MAX_UINT64) { // Unlock buffer
            if (MapInfo->Address1 != 0) {
                gSecurityUnlockCommandBufferMapped = MapInfo->Address1;
            }
        }
    }
    
    return EFI_SUCCESS;
}

/** 
  Save Iommu Address info in LockBox.
  
  @param[in]  pHddPassword      Password buffer to store in LockBox
  
  @retval EFI_STATUS
**/
VOID
StoreAddressInfoInLockBox (
    IN HDD_PASSWORD    *pHddPassword
)
{
    EFI_STATUS                    Status;
    EDKII_IOMMU_PROTOCOL          *EdkiiIoMmu = NULL;
    UINT8                         Index;
    static UINT8                  DeviceCount = 0;
    static BOOLEAN                IsHddSaved = FALSE;
    UINTN                         LockBoxSize;
    IOMMU_MAP_INFORMATION         *MapInfoPtr;
    
    // As only one AhciSmm protocol (for all SATA controllers) is available and
    // its buffer information already stored in LockBox, return
    if (IsHddSaved && (pHddPassword->BusInterfaceType == AmiStorageInterfaceAhci)) {
        return;
    }
    
    // If SMM IOMMU protocol available, then return
    Status = gSmst->SmmLocateProtocol (
                                &gEdkiiIoMmuProtocolGuid, 
                                NULL, 
                                (VOID**)&EdkiiIoMmu );
    if (!EFI_ERROR(Status)) {
        return;
    }

    // In Intel and AMD platforms, when IOMMU is disabled control will come here
    // and addresses will be saved in LockBox. HddSecurityPei driver will map these addresses
    // only if IoMmu PPI is available. So, HddSecurityPei driver will not process this LockBox data
    // and UpdateIommuMappedBufferHandler() will not get control when IOMMU is disabled
    
    // LockBox data structure
    // ---------------------------
    // |      UINT8 - Count      |
    // ---------------------------
    // |  IOMMU_MAP_INFORMATION  |
    // ---------------------------
    // |  IOMMU_MAP_INFORMATION  |
    // ---------------------------
    // |          .....          |
    // ---------------------------
    
    if (gLockBoxMapData == NULL) {
        // Allocate memory for first device and unlock buffer
        gLockBoxMapData = AllocateZeroPool(sizeof(UINT8) + (sizeof(IOMMU_MAP_INFORMATION) * 2));
        
        // Add entry for unlock buffer
        MapInfoPtr             = (IOMMU_MAP_INFORMATION *)&gLockBoxMapData[1];
        MapInfoPtr->Address1   = (EFI_PHYSICAL_ADDRESS)gSecurityUnlockCommandBuffer;
        MapInfoPtr->Length1    = 512;
        MapInfoPtr->Operation1 = EdkiiIoMmuOperationBusMasterCommonBuffer;
        MapInfoPtr->DevHandle  = MAX_UINT64;
        MapInfoPtr++;
        DeviceCount++;
    } else {
        MapInfoPtr = (IOMMU_MAP_INFORMATION *)&gLockBoxMapData[1];
        for (Index = 0; Index < DeviceCount; Index++, MapInfoPtr++) {
            if (MapInfoPtr->DevHandle == (EFI_PHYSICAL_ADDRESS)pHddPassword->DevHandle) {
                break;
            }
        }
         
         // Data already present in LockBox
         if (Index < DeviceCount) {
             return;
         }
         
         gLockBoxMapData = ReallocatePool (
                                  (DeviceCount * sizeof(IOMMU_MAP_INFORMATION)) + sizeof(UINT8),       // OldSize
                                  ((DeviceCount + 1) * sizeof(IOMMU_MAP_INFORMATION)) + sizeof(UINT8), // NewSize
                                  gLockBoxMapData );
         MapInfoPtr = (IOMMU_MAP_INFORMATION *)(&gLockBoxMapData[1] + (DeviceCount * sizeof(IOMMU_MAP_INFORMATION)));
    }
    
    if (pHddPassword->BusInterfaceType == AmiStorageInterfaceAhci) {
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )
        LocateAhciSmmProtocols ();
        if (mAhciSmm == NULL) {
            return;
        }
        MapInfoPtr->Address1   = mAhciSmm->PortFISBaseAddr;
        MapInfoPtr->Length1    = EFI_PAGE_SIZE;
        MapInfoPtr->Operation1 = EdkiiIoMmuOperationBusMasterCommonBuffer;
        IsHddSaved = TRUE;
#endif
    } else if (pHddPassword->BusInterfaceType == AmiStorageInterfaceNvme) {
#if (defined(NVMe_SUPPORT) && (NVMe_SUPPORT != 0))
        {
            AMI_NVME_CONTROLLER_PROTOCOL        *SmmNvmeController = NULL;
            if (EFI_ERROR(LocateNvmeSmmProtocols (pHddPassword->DevHandle, &SmmNvmeController))) {
                return;
            }
    
            MapInfoPtr->Address1   = SmmNvmeController->AdminSubmissionAligned;
            MapInfoPtr->Length1    = (UINT32)SmmNvmeController->AdminSubmissionAlignedSize;
            MapInfoPtr->Operation1 = EdkiiIoMmuOperationBusMasterCommonBuffer;
    
            MapInfoPtr->Address2   = SmmNvmeController->AdminCompletionAligned;
            MapInfoPtr->Length2    = (UINT32)SmmNvmeController->AdminCompletionAlignedSize;
            MapInfoPtr->Operation2 = EdkiiIoMmuOperationBusMasterCommonBuffer;
        }
#endif
    }
    
    gLockBoxMapData[0]           = ++DeviceCount;
    MapInfoPtr->DevHandle        = (EFI_PHYSICAL_ADDRESS)pHddPassword->DevHandle;
    MapInfoPtr->BusInterfaceType = pHddPassword->BusInterfaceType;
    
    LockBoxSize = sizeof(UINT8) + (DeviceCount * sizeof(IOMMU_MAP_INFORMATION));
    
    Status = SaveLockBox ( 
                     &gHddSecLockBoxMapDataGuid,
                     gLockBoxMapData, 
                     LockBoxSize );
    if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED)) {
        return;
    }
    
    if (Status == EFI_SUCCESS) {
        // This case will be entered on first time saving data to SMM lock box.
        // So enable the required lock box attributes.
        Status = SetLockBoxAttributes (
                           &gHddSecLockBoxMapDataGuid,
                           LOCK_BOX_ATTRIBUTE_RESTORE_IN_S3_ONLY );
    } else if (Status == EFI_ALREADY_STARTED) {
        // Lock box already started, so update LockBox with local LockBox data.
        Status = UpdateLockBox (
                           &gHddSecLockBoxMapDataGuid, 
                           0, 
                           gLockBoxMapData, 
                           LockBoxSize );
    }
}

/** 
    This function saves the HDD password and other information 
    necessary to unlock HDD password during S3 Resume.

    @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
    @param Context         Points to an optional handler context which was specified when the
                           handler was registered.
    @param CommBuffer      A pointer to a collection of data in memory that will
                           be conveyed from a non-SMM environment into an SMM environment.
    @param CommBufferSize  The size of the CommBuffer.

    @retval EFI_SUCCESS      Command is handled successfully.

**/
EFI_STATUS 
EFIAPI
SaveHddPassword (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT VOID        *CommBuffer      OPTIONAL,
    IN  OUT UINTN       *CommBufferSize  OPTIONAL
)
{

    EFI_STATUS          Status = EFI_SUCCESS;
    HDD_PASSWORD        *pHddPassword;
    HDD_PASSWORD        *StoredHddList;
    AMI_LINK            *dlink;
    BOOLEAN             UserOrMaster = FALSE;
    BOOLEAN             MatchFound = FALSE;
    UINT64              HddSecSmiUnRegSignature =  0;

    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid Pointer CommBuffer : %x CommBufferSize : %x\n", __FUNCTION__, CommBuffer, CommBufferSize));
        return EFI_SUCCESS;
    }
    
    //  This Communicate call is initiated to Save password data to SMRAM
    //  CommBuffer contains HDD_PASSWORD buffer and password buffer
    if ((*CommBufferSize != (sizeof(HDD_PASSWORD) + (2 * IDE_PASSWORD_LENGTH))) &&
        (*CommBufferSize != sizeof(UINT64))) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid CommBufferSize : %x\n", __FUNCTION__, *CommBufferSize));
        return Status;
    }
    
    // Validate if CommBuffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer ((VOID *)CommBuffer, *CommBufferSize);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_VERBOSE ,"SmmHddSec:%a() CommBuffer overlaps with SMRAM region Status: %r\n", __FUNCTION__, Status));
        return EFI_SUCCESS;
    }
    
    // Check whether this Communicate call is initiated to UnRegister this SMI handler
    HddSecSmiUnRegSignature = *(UINT64 *)CommBuffer;
        
    if (HddSecSmiUnRegSignature == HDD_SEC_SMI_UNREGISTER_SIGNATURE) {
        Status = gSmst->SmiHandlerUnRegister (DispatchHandle);
        return EFI_SUCCESS;
    }
    
    pHddPassword = (HDD_PASSWORD *)CommBuffer;

    //  Check if signature is present or not
    if ((UINT32)pHddPassword->Signature != HDD_SEC_SIGNATURE) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid Signature : %x\n", __FUNCTION__, (UINT32)pHddPassword->Signature));
        return Status;
    }
    
    if ((pHddPassword->BusInterfaceType < AmiStorageInterfaceIde) || 
        ((LOCAL_AMI_STORAGE_BUS_INTERFACE)pHddPassword->BusInterfaceType >= LocalAmiStorageInterfaceMax)) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid Interface type BusInterfaceType : %x\n", __FUNCTION__, pHddPassword->BusInterfaceType));
        return Status;
    }

    UserOrMaster = (BOOLEAN)((pHddPassword->Control) & BIT0);
    
    if (UserOrMaster) {
        Status = AmiValidateMemoryBuffer ((VOID *)pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
    } else {
        Status = AmiValidateMemoryBuffer ((VOID *)pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
    }
    
    if (EFI_ERROR(Status))  {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a Password Buffer overlaps with SMRAM region \n",__FUNCTION__));
        return EFI_SUCCESS;
    }
    
    // Save re-mapped device information in LockBox. It'll be used in NvmeUnlockPei driver
    // to get the MmioBase of re-mapped NVMe
    if ((LOCAL_AMI_STORAGE_BUS_INTERFACE)pHddPassword->BusInterfaceType == LocalAmiStorageInterfaceRaid) {
        
        Status = SaveToLockBox (pHddPassword);
        DEBUG((DEBUG_VERBOSE,"SmmHddSec:%a SaveToLockBox Status : %r!!!\n",__FUNCTION__,Status));
        return EFI_SUCCESS;
    }
    
    // Check whether info about the HDD is already present
    dlink = gPasswordList.pHead;
    for (; dlink; dlink = dlink->pNext) {
        StoredHddList = BASE_CR(dlink, HDD_PASSWORD, LinkList);
        MatchFound = FALSE;

        // Check if drive is connected to same controller
        if ((StoredHddList->BusNo != pHddPassword->BusNo) ||
            (StoredHddList->DeviceNo != pHddPassword->DeviceNo) ||
            (StoredHddList->FunctionNo != pHddPassword->FunctionNo)) {
            continue;
        }

        if (StoredHddList->BusInterfaceType == AmiStorageInterfaceAhci) {
            if ((StoredHddList->PortNumber == pHddPassword->PortNumber) && 
                (StoredHddList->PMPortNumber == pHddPassword->PMPortNumber)) {
                MatchFound = TRUE;
            }
        } else if (StoredHddList->BusInterfaceType == AmiStorageInterfaceIde) {
            if ((StoredHddList->BaseAddress == pHddPassword->BaseAddress) && 
                (StoredHddList->Device == pHddPassword->Device)) {
                MatchFound = TRUE;
            }
        } else { // i.e. StoredHddList->BusInterfaceType == AmiStorageInterfaceNvme
            if (StoredHddList->DevHandle == pHddPassword->DevHandle) {
                MatchFound = TRUE;
            }
        }

        if (MatchFound) {
            if (UserOrMaster) {
                if (StoredHddList->MasterPassword == NULL) {
                    Status = SmmAllocateConfidentialPool (IDE_PASSWORD_LENGTH, (void **)(&StoredHddList->MasterPassword));
                    if (EFI_ERROR(Status) || (StoredHddList->MasterPassword == NULL)) {
                        DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Failed to allocate confidential memory for MasterPassword \n",__FUNCTION__));
                        return EFI_SUCCESS;
                    }
                }
                
                // Match has been found. Just copy the Password buffer
                CopyMem (StoredHddList->MasterPassword, pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
         
            } else {
                if (StoredHddList->UserPassword == NULL) {
                    Status = SmmAllocateConfidentialPool (IDE_PASSWORD_LENGTH, (void **)(&StoredHddList->UserPassword));
                    if (EFI_ERROR(Status) || (StoredHddList->UserPassword == NULL)) {
                        DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Failed to allocate confidential memory for UserPassword \n",__FUNCTION__));
                        return EFI_SUCCESS;
                    }
                }
                // Match has been found. Just copy the Password buffer
                CopyMem (StoredHddList->UserPassword, pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
            }
            
            //use last give password for unlock in S3 path.
            StoredHddList->Control = pHddPassword->Control;
            return Status;
        }
    }

    //  Allocate memory needed while unlocking the Password. Done only once. 
    //  Same buffer will be reused.
    if (gSecurityBuffer == NULL) { 
        gSecurityBuffer = AllocateRuntimePool (512);
    }

    //  Match has not been found. Allocate memory and copy the buffer.
    StoredHddList = AllocateRuntimePool (sizeof(HDD_PASSWORD));
    if (StoredHddList == NULL) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a Failed to allocate memory for Password data\n",__FUNCTION__));
        return EFI_SUCCESS;
    }
    
    CopyMem (StoredHddList, pHddPassword, sizeof(HDD_PASSWORD));
    
    //save the password to allocated Confidential memory
    if (UserOrMaster) {
        Status = SmmAllocateConfidentialPool (IDE_PASSWORD_LENGTH, (void **)(&StoredHddList->MasterPassword));
        if (EFI_ERROR(Status) || (StoredHddList->MasterPassword == NULL)) {
            return Status;
        }
        CopyMem (StoredHddList->MasterPassword, pHddPassword->MasterPassword, IDE_PASSWORD_LENGTH);
    } else {
        Status = SmmAllocateConfidentialPool (IDE_PASSWORD_LENGTH, (void **)(&StoredHddList->UserPassword));
        if (EFI_ERROR(Status) || (StoredHddList->UserPassword == NULL)) {
            return Status;
        }
        CopyMem (StoredHddList->UserPassword, pHddPassword->UserPassword, IDE_PASSWORD_LENGTH);
    }
    
    AmiListAdd (&gPasswordList, &StoredHddList->LinkList); 

    return Status;
}

/** @internal
    This Function unlocks HDD password during S3 resume.

    @param DispatchHandle  Handle to the Dispatcher
    @param Context         A Pointer to EFI_SMM_SW_REGISTER_CONTEXT.
    @param CommBuffer      A pointer to EFI_SMM_SW_CONTEXT.
    @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.
  
  @endinternal

**/
EFI_STATUS 
EFIAPI
UnlockHddPassword (
    IN  EFI_HANDLE       DispatchHandle,
    IN  CONST VOID       *DispatchContext OPTIONAL,
    IN  OUT VOID         *CommBuffer OPTIONAL,
    IN  OUT UINTN        *CommBufferSize OPTIONAL
)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    HDD_PASSWORD            *StoredHddList;
    AMI_LINK                *dlink;
    HDD_PASSWORD            *StoredHddList2;
    AMI_LINK                *dlink2;

    dlink = gPasswordList.pHead;
    for (; dlink; dlink = dlink->pNext) {
        StoredHddList = BASE_CR(dlink, HDD_PASSWORD, LinkList);

        if (StoredHddList->Signature == HDD_SEC_SIGNATURE) {
            if (StoredHddList->BusInterfaceType == AmiStorageInterfaceIde) {
                
                Status = SmmIdeSecurityUnlockCommand (StoredHddList);
                DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a HDD (IDE Mode) Unlock Status = %r",__FUNCTION__,Status));
                
            } else if (StoredHddList->BusInterfaceType == AmiStorageInterfaceAhci){
                // Check if this is the first entry for this controller.
                // If yes, we have to make sure the controller will be fully re-initialized
                gAhciInit = FALSE;
                for (dlink2 = dlink->pPrev; dlink2; dlink2 = dlink2->pPrev) {
                    StoredHddList2 = BASE_CR(dlink2, HDD_PASSWORD, LinkList);
                    if ((StoredHddList2->BusNo == StoredHddList->BusNo) &&
                        (StoredHddList2->DeviceNo == StoredHddList->DeviceNo) &&
                        (StoredHddList2->FunctionNo == StoredHddList->FunctionNo)) {
                        // there was another one previously, so initialization is already done
                        gAhciInit = TRUE;
                        break;
                    }
                }
                Status = SmmAhciSecurityUnlockCommand (StoredHddList);
                DEBUG ((DEBUG_VERBOSE, "SmmHddSec: %a HDD (AHCI Mode) Unlock Status = %r",__FUNCTION__,Status));
            } else if (StoredHddList->BusInterfaceType == AmiStorageInterfaceNvme) {
                
                Status = SmmUnlockNvmeDevice (StoredHddList);
                DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a NVMe device Unlock Status = %r",__FUNCTION__ ,Status));
            }
        }
    }

    return Status;
}

/** @internal
    This Function removes HDD password from the internal database

    @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
    @param Context         Points to an optional handler context which was specified when the
                            handler was registered.
    @param CommBuffer      A pointer to a collection of data in memory that will
                            be conveyed from a non-SMM environment into an SMM environment.
    @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS       Command is handled successfully.
  
  @endinternal

**/
EFI_STATUS
EFIAPI
RemoveHddPassword (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST VOID      *DispatchContext OPTIONAL,
    IN  OUT VOID        *CommBuffer      OPTIONAL,
    IN  OUT UINTN       *CommBufferSize  OPTIONAL
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    HDD_PASSWORD    *pHddPassword;
    HDD_PASSWORD    *StoredHddList;
    AMI_LINK        *dlink;
    UINT64          HddSecSmiUnRegSignature =  0;
    BOOLEAN         MatchFound = FALSE;

    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid Pointer CommBuffer : %x CommBufferSize : %x\n", __FUNCTION__, CommBuffer, CommBufferSize));
        return EFI_SUCCESS;
    }
    
    //  This Communicate call is initiated to Save password data to SMRAM
    //  CommBuffer contains HDD_PASSWORD buffer and password buffer
    if ((*CommBufferSize != (sizeof(HDD_PASSWORD) + (2 * IDE_PASSWORD_LENGTH))) &&
        (*CommBufferSize != sizeof(UINT64))) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid CommBufferSize : %x\n", __FUNCTION__, *CommBufferSize));
        return Status;
    }
    // Validate if CommBuffer address is an non-SMRAM region to avoid SMRAM data 
    // corruption through SMI handlers
    Status = AmiValidateMemoryBuffer ((VOID*)CommBuffer, *CommBufferSize);
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_VERBOSE ,"SmmHddSec:%a() CommBuffer overlaps with SMRAM region Status: %r\n", __FUNCTION__, Status));
        return EFI_SUCCESS;
    }
    
    // Check whether this Communicate call is initiated to UnRegister this SMI handler
    HddSecSmiUnRegSignature = *(UINT64 *)CommBuffer;
        
    if (HddSecSmiUnRegSignature == HDD_SEC_SMI_UNREGISTER_SIGNATURE) {
        Status = gSmst->SmiHandlerUnRegister(DispatchHandle);
        return EFI_SUCCESS;
    }
    
    pHddPassword = (HDD_PASSWORD *)CommBuffer;

    //  Check if signature is present or not
    if ((UINT32) pHddPassword->Signature != HDD_SEC_SIGNATURE) {
        DEBUG ((DEBUG_VERBOSE, "SmmHddSec:%a() Invalid Signature : %x\n", __FUNCTION__, (UINT32)pHddPassword->Signature));
        return Status;
    }
    
    //  Check whether info about the HDD is already present
    dlink = gPasswordList.pHead;
    for (; dlink; dlink = dlink->pNext) {
        StoredHddList = BASE_CR(dlink, HDD_PASSWORD, LinkList);

        // Check if drive is connected to same controller
        if ((StoredHddList->BusNo != pHddPassword->BusNo) ||
            (StoredHddList->DeviceNo != pHddPassword->DeviceNo) ||
            (StoredHddList->FunctionNo != pHddPassword->FunctionNo)) {
            continue;
        }
        
        // Free pool the allocated Confidential memory if match found
        if (StoredHddList->BusInterfaceType == AmiStorageInterfaceAhci) {
            if ((StoredHddList->PortNumber == pHddPassword->PortNumber) && 
                (StoredHddList->PMPortNumber == pHddPassword->PMPortNumber)) {
                MatchFound = TRUE;
            }
        } else if (StoredHddList->BusInterfaceType == AmiStorageInterfaceIde) {
            if ((StoredHddList->BaseAddress == pHddPassword->BaseAddress) && 
                (StoredHddList->Device == pHddPassword->Device)) {
                MatchFound = TRUE;
            }
        } else if (StoredHddList->BusInterfaceType == AmiStorageInterfaceNvme) {
            if (StoredHddList->DevHandle == pHddPassword->DevHandle) {
                MatchFound = TRUE;
            }
        }
        
        if (MatchFound == TRUE) {
            
            if (SAT3_FREEZE_LOCK_ON_S3) {
                // Instead of removing the password, filling the NULL data in MasterPassword
                // and UserPassword buffer for sending the FreezeLock Command during
                // S3 resume.
                if (StoredHddList->Control & BIT0) {
                    ZeroMem (StoredHddList->MasterPassword, IDE_PASSWORD_LENGTH);
                } else {
                    ZeroMem (StoredHddList->UserPassword, IDE_PASSWORD_LENGTH);
                }
            } else {
                if (StoredHddList->MasterPassword != NULL)
                    SmmFreeConfidentialPool ((void **)&StoredHddList->MasterPassword);
                if (StoredHddList->UserPassword != NULL)
                    SmmFreeConfidentialPool((void**)&StoredHddList->UserPassword);
            
                AmiListDelete (&gPasswordList, &StoredHddList->LinkList);
                //free the memory for structure corresponding to the Double Linked List
                FreePool ((VOID *)StoredHddList);
            }
            
            break;
        }
    }
    return Status;
}

/**
    This Function Saves SMI value and SW SMI Port Address 
    in Boot Script for S3 resume during ReadytoBoot

    @param DispatchHandle  Handle to the Dispatcher
    @param Context         A Pointer to EFI_SMM_SW_REGISTER_CONTEXT.
    @param CommBuffer      A pointer to EFI_SMM_SW_CONTEXT.
    @param CommBufferSize  The size of the CommBuffer.

    @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
EFIAPI
BootScriptSaveHddSecSmmEventForS3 (
    IN  EFI_HANDLE       DispatchHandle,
    IN  CONST VOID       *DispatchContext OPTIONAL,
    IN  OUT VOID         *CommBuffer OPTIONAL,
    IN  OUT UINTN        *CommBufferSize OPTIONAL
)
{
    UINT8                   Value = SW_SMI_HDD_UNLOCK_PASSWORD;
    HDD_PASSWORD            *StoredHddList;
    AMI_LINK                *dlink;

#ifdef  SW_SMI_IO_ADDRESS
    gSwSmiPort = SW_SMI_IO_ADDRESS;
#endif
    
    S3BootScriptSaveIoWrite (
                        S3BootScriptWidthUint8,
                        (UINTN)gSwSmiPort,
                        1,
                        &Value );
    
    // Save buffer information in LockBox to map it using IOMMU PPI
    dlink = gPasswordList.pHead;
    for (; dlink; dlink = dlink->pNext) {
        StoredHddList = BASE_CR(dlink, HDD_PASSWORD, LinkList);
        if (StoredHddList->Signature == HDD_SEC_SIGNATURE) {
            StoreAddressInfoInLockBox (StoredHddList);
        }
    }
    
    // UnRegister SMI handler as we have saved SW SMI port & value to the boot script
    gSmst->SmiHandlerUnRegister (DispatchHandle);

    return EFI_SUCCESS;
}

/** @internal
    This function registers Boot script for Nvme devices to initialize Nvme 
    controller along with PCI root bridge BAR,CMD, BUS PCI Configuration 
    values in S3 resume path

    @param DispatchHandle  Handle to the Dispatcher
    @param Context         A Pointer to EFI_SMM_SW_REGISTER_CONTEXT.
    @param CommBuffer      A pointer to EFI_SMM_SW_CONTEXT.
    @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.
  
  @endinternal

**/
EFI_STATUS 
EFIAPI
BootScriptSaveNvmeSecSmmEventForS3 (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
 )
{
    EFI_STATUS                           Status;
    UINT32                               SmmNvmeSaveEntryCount = 0;
    UINTN                                NvmeBootScriptSaveBufferSize = 0;
    UINT32                               EntryIndex = 0;
    UINT16                               Segment;
    UINTN                                PciAddress;
    EFI_BOOT_SCRIPT_WIDTH                Width;
    UINTN                                Value;
    BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY *NvmeBootScriptSaveBuffer = NULL;
    
    // If input is invalid, stop processing this SMI
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        return EFI_SUCCESS;
    }
    
    NvmeBootScriptSaveBufferSize = *CommBufferSize;
    
    // Confirm that communication buffer contains required data
    NvmeBootScriptSaveBuffer = (BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY *)CommBuffer;
    
    // Make sure that "NvmeBootScriptSaveBufferSize" should be greater than "2*sizeof(UINT32)" size
    if( (NvmeBootScriptSaveBufferSize <= 2 * sizeof(UINT32)) ) {
        DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a BootScriptSaveNvmeSecSmmEventForS3() CommBufferSize is invalid\n",__FUNCTION__ ));
        return EFI_SUCCESS;
    }
    
    Status = AmiValidateMemoryBuffer((VOID*)NvmeBootScriptSaveBuffer, NvmeBootScriptSaveBufferSize);
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a BootScriptSaveNvmeSecSmmEventForS3() CommBuffer overlaps with SMRAM region\n",__FUNCTION__ ));
       return EFI_SUCCESS;
    }
    
    SmmNvmeSaveEntryCount = *(UINT32 *)(((UINT8 *)NvmeBootScriptSaveBuffer + NvmeBootScriptSaveBufferSize) - sizeof(UINT32));

    // "SmmNvmeSaveEntryCount" value should be greater than 1 as it is known that 
    // more than one Bootscript entry for NVMe device must have been added by HddSecurity DXE driver
    if (SmmNvmeSaveEntryCount == 0) {
        DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a Bootscript entry is 0 for NVMe device\n",__FUNCTION__ ));
        return EFI_SUCCESS;
    }
    
    Status = AmiValidateMemoryBuffer(
                            (VOID *)NvmeBootScriptSaveBuffer,
                            SmmNvmeSaveEntryCount * sizeof(BOOT_SCRIPT_NVME_SECURITY_SAVE_ENTRY) + 2 * sizeof(UINT32) );
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a CommBuffer passed with NVMe BootScript overlaps with SMRAM space.",__FUNCTION__ ));
        DEBUG((DEBUG_VERBOSE,"Either CommBuffer or CommBufferSize is invalid.\n"));
        return EFI_SUCCESS;
    }

    // Check for Signature at the End of "NvmeBootScriptSaveBuffer" CommBuffer
    if (*(UINT32 *)(&NvmeBootScriptSaveBuffer[SmmNvmeSaveEntryCount]) != NVME_SECURITY_SAVE_SIGNATURE ) {
        DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a CommBuffer passed with NVMe BootScript doesn't have valid signature\n",__FUNCTION__ ));
        return EFI_SUCCESS; 
    }

    // Parse the NvmeBootScriptSaveBuffer for the Entry List and save the values to the BootScript.
    for (EntryIndex = 0; EntryIndex < SmmNvmeSaveEntryCount; EntryIndex++) {
        Segment = (UINT16)NvmeBootScriptSaveBuffer[EntryIndex].Segment;
        PciAddress = NvmeBootScriptSaveBuffer[EntryIndex].PciAddress;
        Width = NvmeBootScriptSaveBuffer[EntryIndex].Width;
        Value = NvmeBootScriptSaveBuffer[EntryIndex].Value;

        DEBUG((DEBUG_VERBOSE, "SmmHddSec: %a BootScriptSaveNvmeSecSmmEventForS3... EntryIndex:%x Segment:%x PciAddress:%x Width:%x Value:%x\n",
                                __FUNCTION__,EntryIndex, Segment, PciAddress, Width, Value ));

        S3BootScriptSavePciCfg2Write (
                                  Width,
                                  Segment,
                                  PciAddress,
                                  1,
                                  &Value);
    }
    
    // UnRegister Smi handler as we have saved the values to boot script
    Status = gSmst->SmiHandlerUnRegister (DispatchHandle);

    return EFI_SUCCESS;
}

/** @internal
    Stores the buffer which will be used for unlocking the HDD

    @param DispatchHandle  Handle to the Dispatcher
    @param Context         A Pointer to EFI_SMM_SW_REGISTER_CONTEXT. 
    @param CommBuffer      A pointer to EFI_SMM_SW_CONTEXT.
    @param CommBufferSize  The size of the CommBuffer.

    @retval EFI_SUCCESS              Command is handled successfully.
    @retval EFI_INVALID_PARAMETER    The given parameter is invalid.
    
    @endinternal

**/
EFI_STATUS 
EFIAPI
ReceiveCommandDataBuffer (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
 )
{
    
    EFI_STATUS                  Status;
    
    if (gSecurityUnlockCommandBuffer == NULL) {
        
        // Unlock command Buffer
        gSecurityUnlockCommandBuffer = (UINT8 *)(*(UINTN *)CommBuffer);
    
        // Validate the gSecurityUnlockCommandBuffer not resides in SMRAM region
        Status = AmiValidateMemoryBuffer ((VOID*)gSecurityUnlockCommandBuffer, 512);
        if (EFI_ERROR(Status)) {
            gSecurityUnlockCommandBuffer = NULL;
            DEBUG((DEBUG_VERBOSE,"SmmHddSec: %a gSecurityUnlockCommandBuffer overlaps with SMRAM region\n",__FUNCTION__ ));
            return EFI_SUCCESS;
        }
    }   
    
    // UnRegister Smi handler as we have located the protocol
    Status = gSmst->SmiHandlerUnRegister (DispatchHandle);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}

/**
    Initializes HDD Security SMM Drivers.

    @param ImageHandle      Image handle
    @param *SystemTable     Pointer to EFI_SYSTEM_TABLE

    @retval EFI_STATUS

    @note Here is the control flow of this function

**/

EFI_STATUS
EFIAPI
HddSecuritySmmInit (
    IN  EFI_HANDLE                  ImageHandle,
    IN  EFI_SYSTEM_TABLE            *SystemTable
)
{
    EFI_STATUS                      Status;
    EFI_SMM_SW_REGISTER_CONTEXT     UnlockHddPasswordContext = {SW_SMI_HDD_UNLOCK_PASSWORD};
    EFI_HANDLE                      Handle;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *SwDispatch;

    AmiListInit (&gPasswordList);

    Status = gSmst->SmiHandlerRegister (
                                SaveHddPassword,
                                &gSaveHddPasswordGuid,
                                &Handle );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gSmst->SmiHandlerRegister (
                                RemoveHddPassword,
                                &gRemoveHddPasswordGuid,
                                &Handle );

    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    // This SMI handler is used to get Mapped Addresses from PEI
    Status = gSmst->SmiHandlerRegister(
                                UpdateIommuMappedBufferHandler,
                                &gHddSecLockBoxMapDataGuid,
                                &Handle );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status  = gSmst->SmmLocateProtocol (
                               &gEfiSmmSwDispatch2ProtocolGuid, 
                               NULL, 
                               (VOID**)&SwDispatch );
    
    if (EFI_ERROR(Status)) {  
        return EFI_UNSUPPORTED;
    }
    
    Status = SwDispatch->Register (
                            SwDispatch,
                            UnlockHddPassword,
                            &UnlockHddPasswordContext,
                            &Handle );
    if (EFI_ERROR(Status)) {
        return Status;
    }
 
    Status = gSmst->SmiHandlerRegister (
                                BootScriptSaveHddSecSmmEventForS3,
                                &gHddSecurityBootScriptSaveTriggerGuid,
                                &Handle );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gSmst->SmiHandlerRegister (
                           BootScriptSaveNvmeSecSmmEventForS3,
                          &gNvmeSecurityBootScriptSaveTriggerGuid,
                          &Handle );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gSmst->SmiHandlerRegister (
                            ReceiveCommandDataBuffer,
                            &gHddSecuritySendCommandDataBufferGuid,
                            &Handle );
    
    return Status;
}
