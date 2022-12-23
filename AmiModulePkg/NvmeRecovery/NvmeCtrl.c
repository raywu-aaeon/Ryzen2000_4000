//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file NvmeCtrl.c
    This file contains the code which provide access to the Nvme 
    Controller/Device

**/

#include "NvmeRecovery.h"

extern EDKII_IOMMU_PPI                  *gEdk2IoMmuPpi;
extern NVME_NAMESPACE_DEVICE_PATH       gPeiNvmePath;

/**
  @internal

    Routine to get the Active NameSpace

    @param NvmeController 
    @param NamespaceId 

    @retval Returns ACTIVE_NAMESPACE_DATA pointer for the NamespaceId

  @endinternal
**/

ACTIVE_NAMESPACE_DATA*
GetActiveNameSpace (
    IN NVME_CONTROLLER_INFO  *NvmeControllerInfo,
    IN UINT32                NamespaceId
)
{
    LIST_ENTRY            *LinkData;
    ACTIVE_NAMESPACE_DATA *ActiveNameSpace = NULL;
    
    if(NvmeControllerInfo == NULL) {
        return NULL;
    }

    for (LinkData = NvmeControllerInfo->ActiveNameSpaceList.ForwardLink; 
            LinkData != &NvmeControllerInfo->ActiveNameSpaceList; 
            LinkData = LinkData->ForwardLink) {

        ActiveNameSpace = BASE_CR(LinkData, ACTIVE_NAMESPACE_DATA, Link);
        
        // If NamespaceId is 0xFFFFFFFF, then return the first valid ActiveNameSpace
        if( NamespaceId == MAX_UINT32 ) {
            return ActiveNameSpace;
        }

        if(ActiveNameSpace->ActiveNameSpaceId == NamespaceId) {
            return ActiveNameSpace;
        }
    }
    return NULL;
}

/**
  @internal

    Function to recreate Admin,IO Submission/Completion queues

    @param  NvmeControllerInfo

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
RecreateAllQueues (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT32          ProgramCc = 0;
    UINT32          Delay;

    ProgramCc = MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET));

    // Check if the controller is already running. If yes stop it.
    Delay = NvmeControllerInfo->TimeOut * 500;
    if (MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET)) & BIT0) {
        
        //  Clear Control register
        MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET), 0);
        
        do {
            if (!(MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT0)) {
                break;
            }
            MicroSecondDelay(1000);

        } while (--Delay);
    }

    if (!Delay) {
        goto  RecreateAllQueues_Error;  
    }

    // Program Admin Queue Size and Base Address
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_AQA_OFFSET),
               ((NvmeControllerInfo->AdminCompletionQueueSize - 1) << 16) + (NvmeControllerInfo->AdminSubmissionQueueSize - 1));

    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ASQ_OFFSET), 
                (UINT32) NvmeControllerInfo->AdminSubmissionQueue);
     
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ASQ_OFFSET + 4), 
                (UINT32) RShiftU64(NvmeControllerInfo->AdminSubmissionQueue, 32));
     
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ACQ_OFFSET), 
                (UINT32)NvmeControllerInfo->AdminCompletionQueue);
     
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ACQ_OFFSET + 4),  
                (UINT32) RShiftU64(NvmeControllerInfo->AdminCompletionQueue, 32));

    NvmeControllerInfo->AdminPhaseTag = FALSE;

    // Enable Controller
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET), (ProgramCc | BIT0));

    // Wait for the controller to get ready
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeControllerInfo->TimeOut * 500;
    do {
        if ((MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT0)) {
            break;
        }
        MicroSecondDelay(1000);
    } while (--Delay);

RecreateAllQueues_Error:
    if (!Delay) {
        Status = EFI_DEVICE_ERROR;
        return Status;
    }

    NvmeControllerInfo->AdminSubmissionQueueHeadPtr = 0;
    NvmeControllerInfo->AdminSubmissionQueueTailPtr = 0;
    NvmeControllerInfo->AdminCompletionQueueHeadPtr = 0;
    NvmeControllerInfo->AdminCompletionQueueTailPtr = 0;
    NvmeControllerInfo->AdminPhaseTag = FALSE;

    if (!NvmeControllerInfo->ReInitializingQueue1) {
        Status = RecreateQueue1 (NvmeControllerInfo);
    }
    return Status;
}

/**  
  @internal

    Function to add command to Admin submission queue

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
AddToAdminSubmissionQueue (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER   *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;

    // Is Admin Queue full?
    if ( NvmeControllerInfo->AdminSubmissionQueueHeadPtr ) {  // Non-zero value
        if ((NvmeControllerInfo->AdminSubmissionQueueTailPtr - 1) == NvmeControllerInfo->AdminSubmissionQueueHeadPtr){
                    
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
          
            Status = RecreateAllQueues (NvmeControllerInfo);
            if (EFI_ERROR(Status)) {            
                return EFI_OUT_OF_RESOURCES;
            }
        }
    } else {
        // If Head is at the start and Tail is at the end, then queue is full
        if (NvmeControllerInfo->AdminSubmissionQueueTailPtr == (NvmeControllerInfo->AdminSubmissionQueueHeadPtr + 
              NvmeControllerInfo->AdminSubmissionQueueSize - 1)) {
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
              Status = RecreateAllQueues (NvmeControllerInfo);
              if (EFI_ERROR(Status)) {            
                  return EFI_OUT_OF_RESOURCES;
              }
        }
    }

    // Copy cmd to Admin Queue
    DestinationAddress = NvmeControllerInfo->AdminSubmissionQueue + (
                              NvmeControllerInfo->AdminSubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND)); 
    DEBUG((DEBUG_VERBOSE,"\n Destination address for Admin Cmd     : %lx\n",DestinationAddress));

    CopyMem ((VOID*)(UINTN)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));

    NvmeControllerInfo->AdminSubmissionQueueTailPtr++;
    
    // Check if there is a roller over
    if (NvmeControllerInfo->AdminSubmissionQueueTailPtr >= (NvmeControllerInfo->AdminSubmissionQueueSize)) {
        NvmeControllerInfo->AdminSubmissionQueueTailPtr = 0;
    }

    return EFI_SUCCESS;
}

/**
  @internal

    Function to create IO Submission/Completion queues

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper
    @param  QueueNumber
    @param  QueueSize

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
CreateAdditionalSubmissionCompletionQueue ( 
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER   *NvmeCmdWrapper,
    IN  UINT16                 QueueNumber,
    IN  UINT32                 QueueSize
)
{
    EFI_STATUS              Status;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    UINTN                   AllocatePageSize;
    UINT64                  QueueAddress = 0;

    ZeroMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));

    // Allocate memory only if the pointer is NULL
    if (NvmeControllerInfo->Queue1CompletionUnAligned == 0) {
        AllocatePageSize = NvmeControllerInfo->MemoryPageSize + QueueSize * sizeof(COMPLETION_QUEUE_ENTRY);

        if (gEdk2IoMmuPpi) {
            Status = gEdk2IoMmuPpi->AllocateBuffer(
                                                  gEdk2IoMmuPpi,
                                                  EfiRuntimeServicesData,
                                                  EFI_SIZE_TO_PAGES(AllocatePageSize),
                                                  (VOID**)&QueueAddress,
                                                  EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                                  );
            if (EFI_ERROR(Status)) {
                return Status;
            }
        } else {
            QueueAddress = (UINT64)(UINTN)AllocateRuntimePages(EFI_SIZE_TO_PAGES(AllocatePageSize));
            if (!QueueAddress) {
                return EFI_OUT_OF_RESOURCES;
            }
        }
        
        ZeroMem((VOID*)(UINTN)QueueAddress, EFI_SIZE_TO_PAGES(AllocatePageSize) * EFI_PAGE_SIZE);

        NvmeControllerInfo->Queue1CompletionUnAligned = QueueAddress;
        NvmeControllerInfo->Queue1CompletionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeControllerInfo->Queue1CompletionQueue = ALIGN_VALUE(QueueAddress, NvmeControllerInfo->MemoryPageSize);

        NvmeControllerInfo->Queue1CompletionQueueSize = QueueSize;
    }

    // Build NVME command
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_CRIOCQ_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.Psdt = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Nsid = 0;
    
    NvmeCmdWrapper->NvmCmd.Prp1 = (UINT64)NvmeControllerInfo->Queue1CompletionQueue;
    NvmeCmdWrapper->NvmCmd.Prp2 = 0;
    NvmeCmdWrapper->NvmCmd.Cdw10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.Cdw11 = 1;           // Contiguous
        
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Cmd issued in Queue0
    NvmeCmdWrapper->CmdTimeOut = 1000;

    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto CreateAdditionalSubmissionCompletionQueue_Exit;
    }

    // Allocate memory only if the pointer is NULL
    if (NvmeControllerInfo->Queue1SubmissionUnAligned == 0) {

        AllocatePageSize = NvmeControllerInfo->MemoryPageSize + 
                           QueueSize * sizeof(NVME_ADMIN_COMMAND);

        if (gEdk2IoMmuPpi) {
            Status = gEdk2IoMmuPpi->AllocateBuffer( gEdk2IoMmuPpi,
                                                    EfiRuntimeServicesData,
                                                    EFI_SIZE_TO_PAGES(AllocatePageSize),
                                                    (VOID**)&QueueAddress,
                                                    EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE );
            if (EFI_ERROR(Status)) {
                return Status;
            }
        } else {
            QueueAddress = (UINT64)(UINTN)AllocateRuntimePages(EFI_SIZE_TO_PAGES(AllocatePageSize));
            if (!QueueAddress) {
                return EFI_OUT_OF_RESOURCES;
            }
        }
        
        ZeroMem((VOID*)(UINTN)QueueAddress, EFI_SIZE_TO_PAGES(AllocatePageSize) * EFI_PAGE_SIZE);

        NvmeControllerInfo->Queue1SubmissionUnAligned = QueueAddress;
        NvmeControllerInfo->Queue1SubmissionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
        NvmeControllerInfo->Queue1SubmissionQueue = ALIGN_VALUE(QueueAddress, NvmeControllerInfo->MemoryPageSize);

        NvmeControllerInfo->Queue1SubmissionQueueSize = QueueSize;
    }

    // Build NVME command
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_CRIOSQ_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.Psdt = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Nsid = 0;
            
    NvmeCmdWrapper->NvmCmd.Prp1 = (UINT64)NvmeControllerInfo->Queue1SubmissionQueue;
    NvmeCmdWrapper->NvmCmd.Prp2 = 0;
    NvmeCmdWrapper->NvmCmd.Cdw10 = ((QueueSize - 1) << 16 )+ QueueNumber;
    NvmeCmdWrapper->NvmCmd.Cdw11 = (QueueNumber << 16) + 1;           // Contiguous

    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Cmd issued to admin queue
    NvmeCmdWrapper->CmdTimeOut = 1000;

    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        return Status;
    }

CreateAdditionalSubmissionCompletionQueue_Exit:
    NvmeControllerInfo->Queue1PhaseTag = FALSE;

    NvmeControllerInfo->Queue1SubmissionQueueTailPtr = 0;
    NvmeControllerInfo->Queue1SubmissionQueueHeadPtr = 0;

    NvmeControllerInfo->Queue1CompletionQueueTailPtr = 0;
    NvmeControllerInfo->Queue1CompletionQueueHeadPtr = 0;

    return Status;
}

/**
  @internal

    Function to recreate IO Submission/Completion queues

    @param  NvmeControllerInfo

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
RecreateQueue1 (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo
)
{
    EFI_STATUS                Status;
    NVME_COMMAND_WRAPPER      *NvmeCmdWrapper = NvmeControllerInfo->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY    CompletionData;
    
    NvmeControllerInfo->ReInitializingQueue1 = TRUE;

    ZeroMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));

    // Build NVME command to delete Submission queue
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_DEIOSQ_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Cdw10 = NvmeControllerInfo->NVMQueueNumber;
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }
    
    // Build NVME command to delete Completion queue
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_DEIOCQ_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Cdw10 = NvmeControllerInfo->NVMQueueNumber;    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;
    
    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, &CompletionData);
    if (EFI_ERROR(Status)) {
        goto RecreateQueue1_Error;
    }

    // Create Submission and Completion Queue1
    Status  = CreateAdditionalSubmissionCompletionQueue(
                                NvmeControllerInfo, 
                                NvmeCmdWrapper, 
                                NvmeControllerInfo->NVMQueueNumber, 
                                NvmeControllerInfo->Queue1SubmissionQueueSize
                                );
RecreateQueue1_Error:
    NvmeControllerInfo->ReInitializingQueue1 = FALSE;
    return Status;
}

/**
  @internal

    Function to add Nvme command in IO submission queue

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper

    @retval EFI_STATUS
	
  @endinternal
**/
EFI_STATUS
AddToQueue1SubmissionQueue (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER   *NvmeCmdWrapper
)
{
    EFI_STATUS          Status;
    UINT64              DestinationAddress;

    // Is Queue full? If Tail is one less than the Head queue is full.
    if (NvmeControllerInfo->Queue1SubmissionQueueHeadPtr) {  // Non-zero value
        if ((NvmeControllerInfo->Queue1SubmissionQueueTailPtr - 1) == NvmeControllerInfo->Queue1SubmissionQueueHeadPtr){
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            Status = RecreateQueue1 (NvmeControllerInfo);
            if (EFI_ERROR(Status)) {    
                return EFI_OUT_OF_RESOURCES;
            }
        }
    } else { 
        // If Head is at the start and Tail is at the end, then queue is full
        if (NvmeControllerInfo->Queue1SubmissionQueueTailPtr == (NvmeControllerInfo->Queue1SubmissionQueueHeadPtr + 
                                    NvmeControllerInfo->Queue1SubmissionQueueSize - 1)) {
            
            // In this design, queue should never get filled up. 
            // If it does something is wrong. Delete and start all over again.
            
            Status = RecreateQueue1 (NvmeControllerInfo);
            if (EFI_ERROR(Status)) {          
                return EFI_OUT_OF_RESOURCES;
            }
        }
    }

    // Copy cmd to Admin Queue
    DestinationAddress = NvmeControllerInfo->Queue1SubmissionQueue + 
                        (NvmeControllerInfo->Queue1SubmissionQueueTailPtr * sizeof(NVME_ADMIN_COMMAND));

    DEBUG((DEBUG_VERBOSE,"\n DestinationAddress for IO command :%lx\n",DestinationAddress));
    CopyMem ((VOID*)(UINTN)DestinationAddress, &(NvmeCmdWrapper->NvmCmd), sizeof(NVME_ADMIN_COMMAND));

    NvmeControllerInfo->Queue1SubmissionQueueTailPtr++;

    // Check if there is a roller over
    if (NvmeControllerInfo->Queue1SubmissionQueueTailPtr >= NvmeControllerInfo->Queue1SubmissionQueueSize) {
        NvmeControllerInfo->Queue1SubmissionQueueTailPtr = 0;
    }
    return EFI_SUCCESS;
}

/**
  @internal

    Function used to update the Door bell register to process 
    Nvme command

    @param  NvmeControllerInfo
    @param  QueueNumber
    @param  Value

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
UpdateDoorBellRegister (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    IN  UINT16                 QueueNumber,
    IN  UINT32                 Value
)
{
    UINT32      Offset;

    // Update Door Bell Register
    Offset = NVME_SQTDBL_OFFSET(QueueNumber, NvmeControllerInfo->DoorBellStride);
    
#if ENABLE_NVME_RECOVERY_TRACES
    DEBUG((DEBUG_VERBOSE,"\n DoorBell Offset %lx Value %x\n", NvmeControllerInfo->BarAddress + Offset, Value));
#endif

    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + Offset), Value);
    return EFI_SUCCESS;
}

/**
  @internal

    Function used to send the Nvme command to the Nvme Controler/Drive

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper
    @param  CmdCompletionData

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
ExecuteNvmeCmd (
    IN  NVME_CONTROLLER_INFO     *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER     *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY   *CmdCompletionData
)
{
    EFI_STATUS      Status;

    PrintExecuteNvmeCmdData(NvmeCmdWrapper);

    do {
        // Because of recursive nature and retry mechanism, cmd identifier needs to be updated just before giving the call.
        NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->CommandIdentifierAdmin : \
                                                                           NvmeControllerInfo->CommandIdentifierQueue1;
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? (Status = AddToAdminSubmissionQueue(NvmeControllerInfo, NvmeCmdWrapper)) : \
                (Status = AddToQueue1SubmissionQueue(NvmeControllerInfo, NvmeCmdWrapper));
    
        if (EFI_ERROR(Status)) {
            continue;
        }
    
        Status = UpdateDoorBellRegister(NvmeControllerInfo, 
                                        NvmeCmdWrapper->SqIdentifier,
                                        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->AdminSubmissionQueueTailPtr :
                                                NvmeControllerInfo->Queue1SubmissionQueueTailPtr 
                                        );

        if (EFI_ERROR(Status)) {
            continue;
        }

        //Wait for cmd to complete
        if (NvmeCmdWrapper->NvmCmd.Cmd0.Opcode != NVME_ADMIN_ASYNC_EVENT_REQUEST_CMD) {
            Status = WaitForCompletionQueueUpdate(NvmeControllerInfo, NvmeCmdWrapper, CmdCompletionData);
        }
    
    } while (EFI_ERROR(Status) && NvmeCmdWrapper->RetryCount--);

    DEBUG((DEBUG_VERBOSE,"\n ExecuteNvmeCmd :Status: %r ", Status));

    return  Status;
}

/**
  @internal

    Function checks Nvme controller for the completion of the command sent

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper
    @param  CmdCompletionData

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
WaitForCompletionQueueUpdate (
    IN  NVME_CONTROLLER_INFO       *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER       *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY     *CmdCompletionData 
)
{
    EFI_STATUS              Status;
    UINT32                  TimeOut = NvmeCmdWrapper->CmdTimeOut;
    UINT32                  Offset;
    COMPLETION_QUEUE_ENTRY  *pCmdCompletionData;
    UINT16                  CommandIdentifier = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->CommandIdentifierAdmin : \
                                                NvmeControllerInfo->CommandIdentifierQueue1; 
    
    UINT64                  CompletionQueueStart = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->AdminCompletionQueue : \
                                                   NvmeControllerInfo->Queue1CompletionQueue; 
    
    UINT16                  CompletionQueueHeadPtr = NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->AdminCompletionQueueHeadPtr :\
                                                     NvmeControllerInfo->Queue1CompletionQueueHeadPtr;

    // Toggle expected phase tag on every roll over
    if (CompletionQueueHeadPtr == 0) {
            NvmeCmdWrapper->AdminOrNVMCmdSet ? (NvmeControllerInfo->AdminPhaseTag = ~NvmeControllerInfo->AdminPhaseTag) : \
                        (NvmeControllerInfo->Queue1PhaseTag = ~NvmeControllerInfo->Queue1PhaseTag);
    }

    // Get the offset to the Command Completion Queue Head Pointer
    pCmdCompletionData = (COMPLETION_QUEUE_ENTRY *)((UINTN)CompletionQueueStart + \
            CompletionQueueHeadPtr * sizeof(COMPLETION_QUEUE_ENTRY));

    do {
        // Check whether Command Identifier, SQ ID matches and Phase Tag matches with the cmd issued.
        if ((pCmdCompletionData->CommandIdentifier == CommandIdentifier) && \
            (pCmdCompletionData->SqIdentifier == NvmeCmdWrapper->SqIdentifier) && \
            (pCmdCompletionData->PhaseTag == (NvmeCmdWrapper->AdminOrNVMCmdSet ? \
             NvmeControllerInfo->AdminPhaseTag : NvmeControllerInfo->Queue1PhaseTag)))
        {
            break;
        }
        
        // check if there are any fatal errors
        if (MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT1) {
            return EFI_DEVICE_ERROR;
        }
        // 1msec delay
        MicroSecondDelay(1000);
        
    } while (--TimeOut);
    
    if (!TimeOut) {
        
        // This is a fatal condition. We should expect some kind of response from the controller. 
        // If not we have to either wait for more time or delete and recreate the queue
        
        NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->CommandIdentifierAdmin++ : \
                                           NvmeControllerInfo->CommandIdentifierQueue1++;
        
        if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
            Status = RecreateAllQueues(NvmeControllerInfo);
        } else {
            Status = RecreateQueue1(NvmeControllerInfo);
        }
        
        if (EFI_ERROR(Status)) {
            // If recreating the queue gets an error. nothing can be done.
            NvmeCmdWrapper->RetryCount = 0;
        } else {
            // Retry the cmd one more time
            NvmeCmdWrapper->RetryCount++;
        }
        return EFI_DEVICE_ERROR;
    }

    // Update HeadPtr from Completion Queue. 
    // Check what Queue was cmd posted to and then update the corresponding Head/Tail pointer
    if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
        NvmeControllerInfo->AdminSubmissionQueueHeadPtr = pCmdCompletionData->SqHeadPointer;
        NvmeControllerInfo->AdminCompletionQueueHeadPtr = NvmeControllerInfo->AdminSubmissionQueueHeadPtr;
        Offset = NVME_CQHDBL_OFFSET(NvmeCmdWrapper->SqIdentifier, NvmeControllerInfo->DoorBellStride);
        MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + Offset), NvmeControllerInfo->AdminCompletionQueueHeadPtr);
    } else { 
        NvmeControllerInfo->Queue1SubmissionQueueHeadPtr = pCmdCompletionData->SqHeadPointer;
        NvmeControllerInfo->Queue1CompletionQueueHeadPtr = NvmeControllerInfo->Queue1SubmissionQueueHeadPtr;
        Offset = NVME_CQHDBL_OFFSET(NvmeCmdWrapper->SqIdentifier, NvmeControllerInfo->DoorBellStride);
        MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + Offset), NvmeControllerInfo->Queue1CompletionQueueHeadPtr);   
    }
    
    // Check whether all cmds submitted has been completed. CompletionQueue Head pointer should give a clue on
    // how many cmds where executed.
    if ( pCmdCompletionData->StatusCode || pCmdCompletionData->StatusCodeType ) {
        Status = EFI_DEVICE_ERROR;
    } else {
        Status = EFI_SUCCESS;
    }

#if ENABLE_NVME_RECOVERY_TRACES
    if (NvmeCmdWrapper->AdminOrNVMCmdSet) {
        DEBUG((DEBUG_VERBOSE,"\nAdminSubmissionQueueHeadPtr %08X\n", NvmeControllerInfo->AdminSubmissionQueueHeadPtr));
        DEBUG((DEBUG_VERBOSE,"AdminSubmissionQueueTailPtr %08X\n", NvmeControllerInfo->AdminSubmissionQueueTailPtr));
        DEBUG((DEBUG_VERBOSE,"AdminCompletionQueueHeadPtr %08X\n", NvmeControllerInfo->AdminCompletionQueueHeadPtr));
        DEBUG((DEBUG_VERBOSE,"AdminCompletionQueueTailPtr %08X\n", NvmeControllerInfo->AdminCompletionQueueTailPtr));
    } else {
        DEBUG((DEBUG_VERBOSE,"\nQueue1SubmissionQueueHeadPtr %08X\n", NvmeControllerInfo->Queue1SubmissionQueueHeadPtr));
        DEBUG((DEBUG_VERBOSE,"Queue1SubmissionQueueTailPtr %08X\n", NvmeControllerInfo->Queue1SubmissionQueueTailPtr));
        DEBUG((DEBUG_VERBOSE,"Queue1CompletionQueueHeadPtr %08X\n", NvmeControllerInfo->Queue1CompletionQueueHeadPtr));
        DEBUG((DEBUG_VERBOSE,"Queue1CompletionQueueTailPtr %08X\n", NvmeControllerInfo->Queue1CompletionQueueTailPtr));
    }
#endif

    // Update o/p buffer
    CopyMem ((VOID *)CmdCompletionData, pCmdCompletionData, sizeof(COMPLETION_QUEUE_ENTRY));

    NvmeCmdWrapper->AdminOrNVMCmdSet ? NvmeControllerInfo->CommandIdentifierAdmin++ : NvmeControllerInfo->CommandIdentifierQueue1++;
    return Status;
}

/**
  @internal

    Functin to get the Identify data of the Nvme controller or Namespace

    @param  NvmeControllerInfo
    @param  IdentifyData
    @param  ControllerNameSpaceStructure
    @param  NameSpaceId

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
GetIdentifyData (
    IN  NVME_CONTROLLER_INFO     *NvmeControllerInfo, 
    OUT VOID                     *IdentifyData,
    IN  NVME_ADMIN_IDENTIFY_CNS  ControllerNameSpaceStructure, 
    IN  UINT32                   NameSpaceId
)
{
    EFI_STATUS              Status;
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper = NvmeControllerInfo->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    UINTN                   BufferSize;
    EFI_PHYSICAL_ADDRESS    Prp1_MappedBaseAddr;
    VOID                    *Mapping = NULL;
    UINT64                  Prp1Buffer;
    UINTN                   TransferSize;
    
    if (ControllerNameSpaceStructure == IdentifyControllerCns) {
        BufferSize = sizeof(NVME_ADMIN_CONTROLLER_DATA);
    } else if (ControllerNameSpaceStructure == IdentifyNamespaceCns) {
        BufferSize = sizeof(NVME_ADMIN_NAMESPACE_DATA);
    } else if(ControllerNameSpaceStructure == IdentifyActiveNsListCns ) {
        BufferSize = 4096;
    } else {
	    return EFI_UNSUPPORTED;
    }

    ZeroMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
    
    if (gEdk2IoMmuPpi) {
        Status = gEdk2IoMmuPpi->Map( gEdk2IoMmuPpi,
                                     EdkiiIoMmuOperationBusMasterWrite,
                                     (VOID*)IdentifyData,
                                     &BufferSize,
                                     &Prp1_MappedBaseAddr,
                                     &Mapping );
        if (EFI_ERROR (Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
    }

    // Build NVME command
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_IDENTIFY_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.FusedOperation = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.Psdt = 0;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;
    NvmeCmdWrapper->NvmCmd.Nsid = NameSpaceId;
            
    if (gEdk2IoMmuPpi) {
        Prp1Buffer = Prp1_MappedBaseAddr;
    } else {
        Prp1Buffer = (UINT64)(UINTN)IdentifyData;
    }
    
    Status = ProgramPrpEntry(NvmeControllerInfo, 
                             NvmeCmdWrapper, 
                             BufferSize, 
                             (VOID*)(UINTN)Prp1Buffer, 
                             NULL, 
                             &TransferSize);
    if(EFI_ERROR(Status)) {
        return Status;
    }

    NvmeCmdWrapper->NvmCmd.Cdw10 = (UINT32)ControllerNameSpaceStructure; 
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;

    Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, &CompletionData);
	
    DEBUG((DEBUG_VERBOSE,"\n GetIdentify ExecuteNvmeCmd Status :%r",Status));
	
    if (gEdk2IoMmuPpi) {
        gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, Mapping);
    }
#if ENABLE_NVME_RECOVERY_TRACES
    if (!EFI_ERROR(Status)) {
        PrintIdentifyDataStructure (IdentifyData, ControllerNameSpaceStructure);
    }
#endif

    return Status;
}


/**
  @internal

    Configures Specific Active Namespace of the Nvme Contoller

    @param  NvmeControllerInfo
    @param  ActiveNameSpaceId

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
ConfigureActiveNamespace(
    NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    UINT32                 ActiveNameSpaceId
)
{
    EFI_STATUS                    Status;
    ACTIVE_NAMESPACE_DATA         *ActiveNameSpaceData;
    UINTN                         Size;
    UINT64                        Prp2BaseAddr;
    LIST_ENTRY                    *LinkData;
    
    for (LinkData = NvmeControllerInfo->ActiveNameSpaceList.ForwardLink; 
                        LinkData != &NvmeControllerInfo->ActiveNameSpaceList; 
                         LinkData = LinkData->ForwardLink) {
                                 
        ActiveNameSpaceData = BASE_CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
        
        // Check if it is an already enumerated NameSpace
        if(ActiveNameSpaceData->ActiveNameSpaceId == ActiveNameSpaceId ){
            DEBUG((DEBUG_INFO,"\nActiveNameSpaceId %x already enumerated",ActiveNameSpaceId));
            return EFI_ALREADY_STARTED;
        }
    }
    
    ActiveNameSpaceData = AllocateZeroPool(sizeof(ACTIVE_NAMESPACE_DATA));
    if(ActiveNameSpaceData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ActiveNameSpaceData->ActiveNameSpaceId = ActiveNameSpaceId;
    ActiveNameSpaceData->NvmeControllerInfo = NvmeControllerInfo;

    // Get list of Active NameSpace Data
    Status = GetIdentifyData ( NvmeControllerInfo, 
                               &ActiveNameSpaceData->IdentifyNamespaceData,
                               IdentifyNamespaceCns, 
                               ActiveNameSpaceId );
    if( EFI_ERROR(Status) ) {
        return Status;
    }

    // Prp2List will be cleared when used
    Size = NvmeControllerInfo->MemoryPageSize;

    if (gEdk2IoMmuPpi) {
        Status = gEdk2IoMmuPpi->AllocateBuffer(gEdk2IoMmuPpi,
                                               EfiRuntimeServicesData,
                                               EFI_SIZE_TO_PAGES(Size),
                                               (VOID**)&Prp2BaseAddr,
                                               EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else {
        Prp2BaseAddr = (UINT64)(UINTN)AllocateRuntimePages(EFI_SIZE_TO_PAGES(Size));
        if(!Prp2BaseAddr) {
            return EFI_OUT_OF_RESOURCES;
        }
    }
    
    ZeroMem((VOID*)(UINTN)Prp2BaseAddr, EFI_SIZE_TO_PAGES(Size) * EFI_PAGE_SIZE);

    ActiveNameSpaceData->Prp2List = (UINT64*)(UINTN)Prp2BaseAddr;
    
    ActiveNameSpaceData->MediaInfo.MediaPresent = TRUE;
    ActiveNameSpaceData->MediaInfo.DeviceType = MaxDeviceType;
    ActiveNameSpaceData->MediaInfo.LastBlock = (UINTN)ActiveNameSpaceData->IdentifyNamespaceData.Nsze - 1;      // Name space Size
    
    Size = ActiveNameSpaceData->IdentifyNamespaceData.LbaFormat[ActiveNameSpaceData->IdentifyNamespaceData.Flbas & 0xF].Lbads;
    ActiveNameSpaceData->MediaInfo.BlockSize = (UINT32) LShiftU64(1, Size);
    
    // Creates Nvme Path for the valid Device Detected and 
    // appends with previously created Device Path.
    gPeiNvmePath.NamespaceId   = ActiveNameSpaceData->ActiveNameSpaceId;
    gPeiNvmePath.NamespaceUuid = ActiveNameSpaceData->IdentifyNamespaceData.Eui64;
    NvmeControllerInfo->DevPath = PeiDpAddNode (NvmeControllerInfo->DevPath, &(gPeiNvmePath.Header));          

    // Create Submission and Completion Queue1
    NvmeControllerInfo->NVMQueueNumber = 1;
    Status  = CreateAdditionalSubmissionCompletionQueue ( NvmeControllerInfo, 
                                                          NvmeControllerInfo->NvmeCmdWrapper, 
                                                          NvmeControllerInfo->NVMQueueNumber, 
                                                          (NvmeControllerInfo->MaxQueueEntrySupported >= IO_QUEUE_SIZE)?
                                                          IO_QUEUE_SIZE : NvmeControllerInfo->MaxQueueEntrySupported );
    if(!EFI_ERROR(Status)) {
        NvmeControllerInfo->TotalActiveNameSpaceCount++;
        InsertTailList (&NvmeControllerInfo->ActiveNameSpaceList, &ActiveNameSpaceData->Link);
    }
    
    return Status;
}

/**
  @internal

    Function to read buffer from Nvme controller

    @param  ActiveNameSpace
    @param  LBA
    @param  BufferSize
    @param  Buffer
    @param  NvmeCompletionData

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
NvmeReadBlocks (
    IN  ACTIVE_NAMESPACE_DATA    *ActiveNameSpace,
    IN  EFI_LBA                   Lba,
    IN  UINTN                     BufferSize,
    OUT VOID                      *Buffer,
    IN OUT COMPLETION_QUEUE_ENTRY *NvmeCompletionData
)
{
    EFI_STATUS                      Status;
    UINTN                           DataN;
    EFI_PEI_BLOCK_IO_MEDIA          MediaInfo = ActiveNameSpace->MediaInfo;
    UINTN                           MaxTransferBufferSize = BufferSize;
    NVME_CONTROLLER_INFO            *NvmeControllerInfo = ActiveNameSpace->NvmeControllerInfo;
    NVME_COMMAND_WRAPPER            *NvmeCmdWrapper = NvmeControllerInfo->NvmeCmdWrapper;
    UINT32                          LbaCountInOneTransfer;
    UINTN                           TransferSize;
    COMPLETION_QUEUE_ENTRY          CompletionData;
    COMPLETION_QUEUE_ENTRY          *pCompletionData = &CompletionData;
    UINTN                           MaxAllowableTransferSize =0;
    EFI_PHYSICAL_ADDRESS            TransferBufferMappedAddr;
    VOID                            *TransferBufferUnMap = NULL;
    UINT64                          Prp1Buffer;
    
    if (BufferSize == 0) {
        return EFI_SUCCESS;
    }
    
    // Check whether the block size is multiple of BlkMedia->BlockSize
    DataN = BufferSize % MediaInfo.BlockSize;
    if (DataN){
        return EFI_BAD_BUFFER_SIZE;
    }
    
    // Check for Valid start Lba #
    if ( Lba > MediaInfo.LastBlock ) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Check for Valid End Lba #
    DataN = BufferSize / MediaInfo.BlockSize;
    if (Lba + DataN > MediaInfo.LastBlock + 1) {
        return EFI_INVALID_PARAMETER;
    }
    
    MaxAllowableTransferSize = (UINTN)LShiftU64(1, NvmeControllerInfo->IdentifyData->Mdts) * \
                                 NvmeControllerInfo->MemoryPageSizeMin;
    
    do {
        // Limit the transfer size to MDTS value
        if (NvmeControllerInfo->IdentifyData->Mdts && (MaxTransferBufferSize > MaxAllowableTransferSize)) {
            MaxTransferBufferSize = MaxAllowableTransferSize;
        }
        
        ZeroMem (NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));
        
        if (gEdk2IoMmuPpi) {
            Status = gEdk2IoMmuPpi->Map( gEdk2IoMmuPpi,
                                         EdkiiIoMmuOperationBusMasterWrite,
                                         Buffer,
                                         &MaxTransferBufferSize,
                                         &TransferBufferMappedAddr,
                                         &TransferBufferUnMap );
            if (EFI_ERROR (Status)) {
                return Status;
            }
            
            Prp1Buffer = TransferBufferMappedAddr;
        } else {
            Prp1Buffer = (UINT64)(UINTN)Buffer;
        }
        
        Status = ProgramPrpEntry(NvmeControllerInfo, 
                                 NvmeCmdWrapper, 
                                 MaxTransferBufferSize, 
                                 (VOID*)(UINTN)Prp1Buffer, 
                                 ActiveNameSpace->Prp2List, 
                                 &TransferSize);
        if(EFI_ERROR(Status)) {
            return Status;
        }
        
        LbaCountInOneTransfer =  TransferSize / MediaInfo.BlockSize;
        
        // Build NVME command
        NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_IO_READ_OPC;
        NvmeCmdWrapper->NvmCmd.Cmd0.FusedOperation = 0;
        NvmeCmdWrapper->NvmCmd.Cmd0.Psdt = 0;
        NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierQueue1;
        NvmeCmdWrapper->NvmCmd.Nsid = ActiveNameSpace->ActiveNameSpaceId;
        
        NvmeCmdWrapper->NvmCmd.Mptr = 0;
        NvmeCmdWrapper->NvmCmd.Cdw10 = (UINT32)Lba;
        NvmeCmdWrapper->NvmCmd.Cdw11 = (UINT32) RShiftU64 (Lba, 32);
        NvmeCmdWrapper->NvmCmd.Cdw12 = 0x80000000 + (LbaCountInOneTransfer - 1);
        NvmeCmdWrapper->NvmCmd.Cdw13 = 0;
        NvmeCmdWrapper->NvmCmd.Cdw14 = 0;
            
        NvmeCmdWrapper->AdminOrNVMCmdSet = FALSE;
        NvmeCmdWrapper->SqIdentifier = NvmeControllerInfo->NVMQueueNumber;
        NvmeCmdWrapper->CmdTimeOut = 1000;
        
        // If caller has passed buffer to return controller status, use it.
        if (NvmeCompletionData) {
            pCompletionData = NvmeCompletionData;
        }

        Status = ExecuteNvmeCmd (NvmeControllerInfo, NvmeCmdWrapper, pCompletionData);
        if (EFI_ERROR(Status)) {
            if (TransferBufferUnMap){
                gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, TransferBufferUnMap);  
            }
            break;
        }

        // Remaining Bytes to be transferred
        MaxTransferBufferSize -= (LbaCountInOneTransfer * MediaInfo.BlockSize);

        // Update Lba # for next transfer if needed        
        Lba += LbaCountInOneTransfer;
        
        // Adjust the Buffer address
        Buffer =(VOID*) ((UINTN) Buffer + (LbaCountInOneTransfer * MediaInfo.BlockSize));
        BufferSize -= (LbaCountInOneTransfer * MediaInfo.BlockSize);

        // if Buffer read for MaxTransferBufferSize is not completed fully, read for the remaining size
        if (MaxTransferBufferSize == 0) {
            MaxTransferBufferSize = BufferSize;
        }
        
        if (TransferBufferUnMap){
            gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, TransferBufferUnMap);  
        }
        
    } while(MaxTransferBufferSize);

    return Status;
}

/**
  @internal

    Programms Prp2 list

    @param  Prp2List
    @param  PageSize
    @param  BufferAddress
    @param  BufferSize
    @param  Pep2TransferSize

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
ProgramPrp2List (
    IN  UINT64  *Prp2List, 
    IN  UINT32  PageSize, 
    IN  UINTN   BufferAddress,
    IN  UINTN   BufferSize,
    IN  UINTN   *Prp2TransferSize
)
{
    
    UINTN    TotalNumberOfEntries = PageSize / 8;        // Each entry 64 bytes long
            
    *Prp2TransferSize = 0;
    
    do {
        
        *Prp2List++ = BufferAddress;
        if (BufferSize >= PageSize) {
            *Prp2TransferSize += PageSize;
            BufferAddress += PageSize;
            BufferSize -= PageSize;
        } else {
              *Prp2TransferSize = *Prp2TransferSize + (UINT32)BufferSize;
              BufferAddress += BufferSize;
              BufferSize = 0;
        }
        
    } while (--TotalNumberOfEntries && (BufferSize > 0));
    
    return  EFI_SUCCESS;
}
/**
  @internal

    Programs PRP1 and PRP2. Also checks whether PRP2 list needed or not.
	If needed calls ProgramPrp2List()

    @param  NvmeControllerInfo
    @param  NvmeCmdWrapper
    @param  TransferLength
    @param  Buffer
    @param  Prp2List
    @param  BufferSize

    @retval EFI_STATUS

  @endinternal
**/
EFI_STATUS
ProgramPrpEntry(
    IN  NVME_CONTROLLER_INFO        *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER        *NvmeCmdWrapper,
    IN  UINTN                       TransferLength,
    IN  VOID                        *Buffer,
    IN  UINT64                      *Prp2List,
    OUT UINTN                       *BufferSize
)
{
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    TransferBuffer;
    UINTN                   Prp1TransferSize;
    UINTN                   Prp2TransferSize = 0;
    
    TransferBuffer = (EFI_PHYSICAL_ADDRESS) (UINTN) Buffer;

    NvmeCmdWrapper->NvmCmd.Prp1 = (UINT64) TransferBuffer;
    Prp1TransferSize = NvmeControllerInfo->MemoryPageSize - 
                        (TransferBuffer & ((UINTN)(NvmeControllerInfo->MemoryPageSize) - 1));
    
    // If all data can be transferred using only Prp1 then do that.
    if (Prp1TransferSize >= TransferLength) {
        Prp1TransferSize = TransferLength;
    }
    
    // Check Transfer size and use Prp2 if needed
    if (TransferLength - Prp1TransferSize) {

        // Do we need either a Prp2 pointer or a List
        if (TransferLength - Prp1TransferSize <= NvmeControllerInfo->MemoryPageSize) {
            NvmeCmdWrapper->NvmCmd.Prp2 = NvmeCmdWrapper->NvmCmd.Prp1 + Prp1TransferSize;
            Prp2TransferSize = TransferLength - Prp1TransferSize;
        } else {
            
            if(Prp2List != NULL) {
            
                // We need Prp2 List
                Status = ProgramPrp2List(Prp2List, 
                                         NvmeControllerInfo->MemoryPageSize,
                                         (UINTN)TransferBuffer + Prp1TransferSize,
                                         TransferLength -  Prp1TransferSize, 
                                         &Prp2TransferSize );
                if (EFI_ERROR(Status)) {
                    return Status;
                }
                
                NvmeCmdWrapper->NvmCmd.Prp2 = (UINT64)(UINTN)Prp2List;
            }
        }
    }
    
    *BufferSize = (UINTN)(Prp1TransferSize + Prp2TransferSize);
    
    return EFI_SUCCESS;
}

/**
  @internal

    Function initializes the Number of queues for the Nvme controller

    @param  NvmeControllerInfo

    @retval VOID

  @endinternal
**/
EFI_STATUS
SetNumberOfQueues (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
)
{
    EFI_STATUS              Status;
    NVME_COMMAND_WRAPPER    *NvmeCmdWrapper = NvmeControllerInfo->NvmeCmdWrapper;
    COMPLETION_QUEUE_ENTRY  CompletionData;
    
    ZeroMem(NvmeCmdWrapper, sizeof(NVME_COMMAND_WRAPPER));

    // Build NVME command for Set Number of queue to 1
    NvmeCmdWrapper->NvmCmd.Cmd0.Opcode = NVME_ADMIN_SET_FEATURES_CMD;
    NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier = NvmeControllerInfo->CommandIdentifierAdmin;

    NvmeCmdWrapper->NvmCmd.Cdw10 = 0x7; // Number of Queues FID
    NvmeCmdWrapper->NvmCmd.Cdw11 = BIT16 | BIT0;
    
    NvmeCmdWrapper->AdminOrNVMCmdSet = TRUE;
    NvmeCmdWrapper->SqIdentifier = 0;           // Queue 0 for Admin cmds
    NvmeCmdWrapper->CmdTimeOut = 1000;

    Status = ExecuteNvmeCmd ( NvmeControllerInfo, NvmeCmdWrapper, &CompletionData );
    return Status;
}

/**
  @internal

    Prints NvmeCmdWrapper info passed to ExecuteNvmeCmd function

    @param NvmeCmdWrapper

    @retval VOID
	
  @endinternal
**/
VOID
PrintExecuteNvmeCmdData (
     IN NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
)
{
#if ENABLE_NVME_RECOVERY_TRACES
    DEBUG((DEBUG_VERBOSE,"\n *****  ExecuteNvmeCmd  ***** \n"));
    DEBUG((DEBUG_VERBOSE,"\n Opcode                                  : %16lx", NvmeCmdWrapper->NvmCmd.Cmd0.Opcode));
    DEBUG((DEBUG_VERBOSE,"\n CommandIdentifier                       : %16lx",NvmeCmdWrapper->NvmCmd.Cmd0.CommandIdentifier));
    DEBUG((DEBUG_VERBOSE,"\n Nsid                                    : %08X",NvmeCmdWrapper->NvmCmd.Nsid));
    DEBUG((DEBUG_VERBOSE,"\n CmdTimeOut                              : %08X", NvmeCmdWrapper->CmdTimeOut));
    DEBUG((DEBUG_VERBOSE,"\n AdminOrNVMCmdSet                        : %08X",NvmeCmdWrapper->AdminOrNVMCmdSet));
    DEBUG((DEBUG_VERBOSE,"\n Prp1                                    : %016lX",NvmeCmdWrapper->NvmCmd.Prp1));
    DEBUG((DEBUG_VERBOSE,"\n Prp2                                    : %016lX",NvmeCmdWrapper->NvmCmd.Prp2));
    DEBUG((DEBUG_VERBOSE,"\n Cdw10                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw10));
    DEBUG((DEBUG_VERBOSE,"\n Cdw11                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw11));
    DEBUG((DEBUG_VERBOSE,"\n Cdw12                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw12));
    DEBUG((DEBUG_VERBOSE,"\n Cdw13                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw13));
    DEBUG((DEBUG_VERBOSE,"\n Cdw14                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw14));
    DEBUG((DEBUG_VERBOSE,"\n Cdw15                                   : %08X",NvmeCmdWrapper->NvmCmd.Cdw15));
    
#endif
}

/**
  @internal

    Prints Controller capabilities

    @param NvmeControllerInfo

    @retval VOID

  @endinternal
**/
VOID
PrintNvmeCapability (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
)
{

#if ENABLE_NVME_RECOVERY_TRACES
    DEBUG((DEBUG_VERBOSE,"\n *****  Controller capabilities  ***** \n"));
    DEBUG((DEBUG_VERBOSE,"\n NvmeBarAddress                          : %x\n",NvmeControllerInfo->BarAddress));
    DEBUG((DEBUG_VERBOSE,"\n Controller Capabilities Reg Value       : %16lx\n",NvmeControllerInfo->RawNvmeCapability));
    DEBUG((DEBUG_VERBOSE,"\n Max. Queue Entrys Supported             : %08X\n",NvmeControllerInfo->MaxQueueEntrySupported));
    DEBUG((DEBUG_VERBOSE,"\n Contiguous Queue Required               : %08X\n",NvmeControllerInfo->ContiguousQueueRequired));
    DEBUG((DEBUG_VERBOSE,"\n Arbitration Mode Supported              : %08X\n",NvmeControllerInfo->ArbitrationMechanismSupport));
    DEBUG((DEBUG_VERBOSE,"\n TimeOut in 500msec unit                 : %08X\n",NvmeControllerInfo->TimeOut));
    DEBUG((DEBUG_VERBOSE,"\n Doorbell Stride                         : %08X\n",NvmeControllerInfo->DoorBellStride));
    DEBUG((DEBUG_VERBOSE,"\n NVM Subsystem Reset Support             : %08X\n",NvmeControllerInfo->NVMResetSupport));
    DEBUG((DEBUG_VERBOSE,"\n Command Sets Supported                  : %08X\n",NvmeControllerInfo->CmdSetsSupported));
    DEBUG((DEBUG_VERBOSE,"\n Memory Page Size Min.in Bytes           : %08X\n",NvmeControllerInfo->MemoryPageSizeMin));
    DEBUG((DEBUG_VERBOSE,"\n Memory Page Size Max.in Bytes           : %08X\n",NvmeControllerInfo->MemoryPageSizeMax));
#endif
    return;
}

/**
    Initialize Nvme controller and ADMIN submission and Completion 
    queues

    @param  NvmeControllerInfo 
    @param  PciDeviceInfo 

    @retval EFI_STATUS

**/
EFI_STATUS
InitializeNvmeController (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
)
{
    EFI_STATUS                    Status;
    UINT64                        ControllerCapabilities;
    UINTN                         Delay;
    UINTN                         AllocatePageSize;
    UINT32                        ProgramCc;
    EFI_PHYSICAL_ADDRESS          AdminQueueAddress = 0;

    ControllerCapabilities = LShiftU64(MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + 4)), 32) + 
                                       MmioRead32((UINTN)NvmeControllerInfo->BarAddress);
    NvmeControllerInfo->RawNvmeCapability = ControllerCapabilities;
    
    NvmeControllerInfo->MaxQueueEntrySupported = (ControllerCapabilities & 0xFFFF) + 1;
    NvmeControllerInfo->ContiguousQueueRequired = (BOOLEAN)(RShiftU64((ControllerCapabilities & 0x10000), 16));
    NvmeControllerInfo->ArbitrationMechanismSupport = (BOOLEAN)(RShiftU64((ControllerCapabilities & 0x60000), 17));
    NvmeControllerInfo->TimeOut = (UINT8)RShiftU64((ControllerCapabilities & 0xFF000000), 24);  // 500msec units
    NvmeControllerInfo->DoorBellStride = (UINT8)(RShiftU64((ControllerCapabilities & 0xF00000000), 32));
    NvmeControllerInfo->NVMResetSupport = (BOOLEAN) (RShiftU64((ControllerCapabilities & 0x1000000000), 36));
    NvmeControllerInfo->CmdSetsSupported = (UINT8)(RShiftU64((ControllerCapabilities & 0x1FE000000000), 37));
    NvmeControllerInfo->MemoryPageSizeMin = (UINT32) LShiftU64(1,(UINTN)(RShiftU64( \
                                            (ControllerCapabilities & 0xF000000000000), 48) + 12));  // In Bytes
    NvmeControllerInfo->MemoryPageSizeMax = (UINT32) LShiftU64(1,(UINTN)(RShiftU64(\
                                            (ControllerCapabilities & 0xF0000000000000), 52) + 12)); // In Bytes
    NvmeControllerInfo->ControllerVersion = MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_VER_OFFSET));

    PrintNvmeCapability(NvmeControllerInfo);
    
    // Is NVM command set supported
    if (!(NvmeControllerInfo->CmdSetsSupported & BIT0)) {
        return EFI_UNSUPPORTED;
    }
    
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeControllerInfo->TimeOut * 500;

    // Check if the controller is still in shutdown process occurring state
    do {
     
        if (!(MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT2)) {
            break;
        }
        MicroSecondDelay(1000); // 1msec delay
        
    }while (--Delay);

    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    
    Delay = NvmeControllerInfo->TimeOut * 500;
    if (MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET)) & BIT0) {
        
        //  Disable Enable bit
        MmioAnd32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET),(UINT32)~(BIT0));
        do {
            if (!(MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT0)) {
                break;
            }
            MicroSecondDelay(1000); // 1msec delay
        } while (--Delay);
    }
    
    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    
    // Initialize Controller configuration register. 
    // Select Round Robin and NVM Command Set (both values are zero)
    NvmeControllerInfo->MemoryPageSize = (NvmeControllerInfo->MemoryPageSizeMax > MAX_MPS_ALLOWED) ? \
                                          MAX_MPS_ALLOWED : NvmeControllerInfo->MemoryPageSizeMax;
    
    ProgramCc = (UINT32) LShiftU64((UINTN)RShiftU64(NvmeControllerInfo->MemoryPageSize, 13), 7);

    // Initialize with default value. Later it can be modified
    ProgramCc |= (6 << 16);     // I/O Submission Queue Entry Size
    ProgramCc |= (4 << 20);     // I/O Completion Queue Entry Size
    
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET), ProgramCc);

    // Allocate memory for Admin Queue. Each entry is 64bytes long and queue should be aligned on MemoryPageSize
    AllocatePageSize = NvmeControllerInfo->MemoryPageSize + ADMIN_QUEUE_SIZE * sizeof (NVME_ADMIN_COMMAND);

    if (gEdk2IoMmuPpi) {
        Status = gEdk2IoMmuPpi->AllocateBuffer(
                                              gEdk2IoMmuPpi,
                                              EfiRuntimeServicesData,
                                              EFI_SIZE_TO_PAGES(AllocatePageSize),
                                              (VOID**)&AdminQueueAddress,
                                              EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                              );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else {
        AdminQueueAddress = (UINT64)(UINTN)AllocateRuntimePages(EFI_SIZE_TO_PAGES(AllocatePageSize));
        if(!AdminQueueAddress) {
            return EFI_OUT_OF_RESOURCES;
        }
    }
    
    NvmeControllerInfo->AdminSubmissionUnAligned = AdminQueueAddress;
    NvmeControllerInfo->AdminSubmissionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
    NvmeControllerInfo->AdminSubmissionQueue = (AdminQueueAddress & ~(NvmeControllerInfo->MemoryPageSize - 1)) + 
                                                    NvmeControllerInfo->MemoryPageSize;

    if (gEdk2IoMmuPpi) {
        Status = gEdk2IoMmuPpi->AllocateBuffer( gEdk2IoMmuPpi,
                                                EfiRuntimeServicesData,
                                                EFI_SIZE_TO_PAGES(AllocatePageSize),
                                                (VOID**)&AdminQueueAddress,
                                                EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else {
        AdminQueueAddress = (UINT64)(UINTN)AllocateRuntimePages(EFI_SIZE_TO_PAGES(AllocatePageSize));
        if(!AdminQueueAddress) {
            return EFI_OUT_OF_RESOURCES;
        }
    }

    NvmeControllerInfo->AdminCompletionUnAligned = AdminQueueAddress;
    NvmeControllerInfo->AdminCompletionUnAlignedSize = EFI_SIZE_TO_PAGES(AllocatePageSize);
    NvmeControllerInfo->AdminCompletionQueue = (AdminQueueAddress & ~(NvmeControllerInfo->MemoryPageSize - 1)) + 
                                                    NvmeControllerInfo->MemoryPageSize;
    
#if ENABLE_NVME_RECOVERY_TRACES
    DEBUG((DEBUG_VERBOSE,"\n AdminSubmissionQueue Base %x",NvmeControllerInfo->AdminSubmissionQueue));
    DEBUG((DEBUG_VERBOSE,"\n AdminCompletionQueue Base %x",NvmeControllerInfo->AdminCompletionQueue));
#endif
    
    NvmeControllerInfo->AdminSubmissionQueueSize = ADMIN_QUEUE_SIZE;
    NvmeControllerInfo->AdminCompletionQueueSize = ADMIN_QUEUE_SIZE;
    
    ZeroMem((VOID*)(UINTN)NvmeControllerInfo->AdminSubmissionQueue, ADMIN_QUEUE_SIZE * sizeof(NVME_ADMIN_COMMAND));
    ZeroMem((VOID*)(UINTN)NvmeControllerInfo->AdminCompletionQueue, ADMIN_QUEUE_SIZE * sizeof(NVME_ADMIN_COMMAND));
    
    // Program Admin Queue Size and Base Address
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_AQA_OFFSET),   
               ((NvmeControllerInfo->AdminCompletionQueueSize - 1) << 16) + (NvmeControllerInfo->AdminSubmissionQueueSize - 1));
    
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ASQ_OFFSET), 
                (UINT32) NvmeControllerInfo->AdminSubmissionQueue);
    
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ASQ_OFFSET + 4), 
                (UINT32) RShiftU64(NvmeControllerInfo->AdminSubmissionQueue, 32));
    
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ACQ_OFFSET), 
                (UINT32)NvmeControllerInfo->AdminCompletionQueue);
    
    MmioWrite32((UINTN)(NvmeControllerInfo->BarAddress + NVME_ACQ_OFFSET + 4),  
                (UINT32) RShiftU64(NvmeControllerInfo->AdminCompletionQueue, 32));
    
    NvmeControllerInfo->AdminPhaseTag = FALSE;
    
    NvmeControllerInfo->NvmeCmdWrapper = AllocateZeroPool(sizeof(NVME_COMMAND_WRAPPER));
    if(NvmeControllerInfo->NvmeCmdWrapper == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Enable Controller
    MmioOr32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CC_OFFSET), BIT0);
    
    // Wait for the controller to get ready
    // Check if the controller is already running. If yes stop it.
    Delay = NvmeControllerInfo->TimeOut * 500;
    do {
        if ((MmioRead32((UINTN)(NvmeControllerInfo->BarAddress + NVME_CSTS_OFFSET)) & BIT0)) {
            break;
        }
        MicroSecondDelay(1000); // 1msec delay
    } while (--Delay);
        
    if (!Delay) {
        return EFI_DEVICE_ERROR;
    }
    Status = SetNumberOfQueues (NvmeControllerInfo);
    return Status;
}

/**
  @internal
    Initializes NVMe controller and Configures ActiveNamespaces
    
    @param NvmeControllerInfo
    
    @return EFI_STATUS
  @endinternal
**/
EFI_STATUS
InitAndConfigNvmeController (
    IN NVME_CONTROLLER_INFO *NvmeControllerInfo
)
{
    EFI_STATUS                 Status;
    NVME_ADMIN_CONTROLLER_DATA *Identifydata;
    UINT32                     *ActiveNameSpaceIds;
    UINT32                     Index;
    
    // Initialize NVMe Controller
    Status = InitializeNvmeController( NvmeControllerInfo );
    DEBUG((DEBUG_INFO, "InitializeNvmeController Status - %r\n", Status));
    if ( EFI_ERROR(Status) ) {
        return Status;
    }
    
    Identifydata = AllocateZeroPool(sizeof(NVME_ADMIN_CONTROLLER_DATA));
    if(Identifydata == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    NvmeControllerInfo->IdentifyData = Identifydata;

    // Get Identify Controller Data Structure
    Status = GetIdentifyData ( NvmeControllerInfo, 
                               Identifydata,
                               IdentifyControllerCns,
                               0 );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    ActiveNameSpaceIds = AllocatePages(EFI_SIZE_TO_PAGES(4096+4));
    if(ActiveNameSpaceIds == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    ZeroMem(ActiveNameSpaceIds, EFI_SIZE_TO_PAGES(4096+4) * EFI_PAGE_SIZE);
    
    NvmeControllerInfo->ActiveNameSpaceIds = ActiveNameSpaceIds;
    
    Status = EFI_DEVICE_ERROR;
    if (NvmeControllerInfo->ControllerVersion >= NVME_SPEC_VS_1_1) {
        Status = GetIdentifyData ( NvmeControllerInfo, 
                                   (VOID*)(ActiveNameSpaceIds + 1), 
                                   IdentifyActiveNsListCns, 
                                   0 );
    }
    
    if(EFI_ERROR(Status)) {
        for (Index=1; Index < Identifydata->Nn + 1; Index++ ) {
            ActiveNameSpaceIds[Index] = Index;
        }    
    }

    InitializeListHead(&NvmeControllerInfo->ActiveNameSpaceList);
     
    for (Index = 1; (Index <= 1024) && NvmeControllerInfo->ActiveNameSpaceIds[Index]; Index++) {
        // Configure Namespaces of Nvme Controller
        Status = ConfigureActiveNamespace(NvmeControllerInfo, NvmeControllerInfo->ActiveNameSpaceIds[Index]);
        DEBUG((DEBUG_INFO, "ConfigureActiveNamespace Status - %r, Nsid - %x\n", Status, Index));
    }
    
    // Install NvmePassThru PPI
    Status = InstallNvmePassThruPpi(NvmeControllerInfo);
    
    return Status;
}
/**
    Prints Identfiy data information for the Nvme controller/Namespace based on
    the ControllerNameSpaceStructure input value.

    @param  NvmeControllerInfo 
    @param  PciDeviceInfo 

    @retval EFI_STATUS

**/
VOID
PrintIdentifyDataStructure (
    IN  VOID                      *IdentifyData, 
    IN  NVME_ADMIN_IDENTIFY_CNS   ControllerNameSpaceStructure
)
{
#if ENABLE_NVME_RECOVERY_TRACES
    NVME_ADMIN_CONTROLLER_DATA  *IdentifyControllerData = (NVME_ADMIN_CONTROLLER_DATA *)IdentifyData;
    NVME_ADMIN_NAMESPACE_DATA   *IdentifyNameSpaceData = (NVME_ADMIN_NAMESPACE_DATA *)IdentifyData;
    UINT32                      *ActiveNameSapceID = (UINT32 *)IdentifyData;
    UINT32                      i;
    UINT64                      FirmwareVersion;
    
    switch (ControllerNameSpaceStructure) {
    
        case IdentifyControllerCns:
            FirmwareVersion = *(UINT64 *)(IdentifyControllerData->Fr);
            
            DEBUG((DEBUG_VERBOSE, "\n Identify Controller Data Structure\n " ));

            DEBUG((DEBUG_VERBOSE,"Vendor ID                                 : %x\n", IdentifyControllerData->Vid));
            DEBUG((DEBUG_VERBOSE,"SubSystem Vendor ID                       : %x\n", IdentifyControllerData->Ssvid));
            DEBUG((DEBUG_VERBOSE, "Firmware Version                         : %x\n", FirmwareVersion));
            DEBUG((DEBUG_VERBOSE,"NameSpace Sharing Capability              : %x\n", IdentifyControllerData->Cmic));
            DEBUG((DEBUG_VERBOSE,"Max. Data Transfer Size                   : %x\n", IdentifyControllerData->Mdts));
            DEBUG((DEBUG_VERBOSE,"Controller ID                             : %08X\n", IdentifyControllerData->Cntlid));
            DEBUG((DEBUG_VERBOSE,"Optional Admin Cmd Support                : %08X\n", IdentifyControllerData->Oacs));
            DEBUG((DEBUG_VERBOSE,"Abort Command Limit                       : %08X\n", IdentifyControllerData->Acl));
            DEBUG((DEBUG_VERBOSE,"Asyn. Event Request Limit                 : %08X\n", IdentifyControllerData->Aerl));
            DEBUG((DEBUG_VERBOSE,"Firmware Updates                          : %08X\n", IdentifyControllerData->Frmw));
            DEBUG((DEBUG_VERBOSE,"Log Page Attribute                        : %08X\n", IdentifyControllerData->Lpa));
            DEBUG((DEBUG_VERBOSE,"# of Power state supported                : %08X\n", IdentifyControllerData->Npss));
            DEBUG((DEBUG_VERBOSE,"Admin Vendor Specific cmd                 : %08X\n", IdentifyControllerData->Avscc));
            DEBUG((DEBUG_VERBOSE,"Autonomous Power state attrib             : %08X\n", IdentifyControllerData->Apsta));
            DEBUG((DEBUG_VERBOSE,"Submission queue Entry Size               : %08X\n", IdentifyControllerData->Sqes));
            DEBUG((DEBUG_VERBOSE,"Completion queue Entry Size               : %08X\n", IdentifyControllerData->Cqes));
            DEBUG((DEBUG_VERBOSE,"Number of NameSpace                       : %08X\n", IdentifyControllerData->Nn));
            DEBUG((DEBUG_VERBOSE,"Optional NVM Command Support              : %08X\n", IdentifyControllerData->Oncs));
            DEBUG((DEBUG_VERBOSE,"Fused Operation Support                   : %08X\n", IdentifyControllerData->Fuses));
            DEBUG((DEBUG_VERBOSE,"Format NVM Attribute                      : %08X\n", IdentifyControllerData->Fna));
            DEBUG((DEBUG_VERBOSE,"Volatile Write Cache                      : %08X\n", IdentifyControllerData->Vwc));
            DEBUG((DEBUG_VERBOSE,"Atomic Write Unit Normal                  : %08X\n", IdentifyControllerData->Awun));
            DEBUG((DEBUG_VERBOSE,"Atomic Write Unit Power Fail              : %08X\n", IdentifyControllerData->Awupf));
            DEBUG((DEBUG_VERBOSE,"NVM VS CMD Config                         : %08X\n", IdentifyControllerData->Nvscc));
            DEBUG((DEBUG_VERBOSE,"Atomic Compare & Write Unit               : %08X\n", IdentifyControllerData->Acwu));
            DEBUG((DEBUG_VERBOSE,"SGL Support                               : %08X\n", IdentifyControllerData->Sgls));
            break;
            
        case IdentifyNamespaceCns:
            DEBUG((DEBUG_VERBOSE,"\nIdentify NameSpace Data Structure\n"));
            DEBUG((DEBUG_VERBOSE, "NameSpace Size                             : %08X\n", IdentifyNameSpaceData->Nsze));
            DEBUG((DEBUG_VERBOSE, "NameSpace Capacity                         : %08X\n", IdentifyNameSpaceData->Ncap));
            DEBUG((DEBUG_VERBOSE, "NameSpace Utilization                      : %08X\n", IdentifyNameSpaceData->Nuse));
            DEBUG((DEBUG_VERBOSE,"NameSpace Features                          : %08X\n", IdentifyNameSpaceData->Nsfeat));
            DEBUG((DEBUG_VERBOSE,"No. of LBA Formats (0 Based)                : %08X\n", IdentifyNameSpaceData->Nlbaf));
            DEBUG((DEBUG_VERBOSE, "Formatted LBA Size                         : %08X\n", IdentifyNameSpaceData->Flbas));
            DEBUG((DEBUG_VERBOSE, "MetaData Capabilities                      : %08X\n", IdentifyNameSpaceData->Mc));
            DEBUG((DEBUG_VERBOSE, "End-to-end data Protection cap             : %08X\n", IdentifyNameSpaceData->Dpc));
            DEBUG((DEBUG_VERBOSE, "End-to-end data Protection settings        : %08X\n", IdentifyNameSpaceData->Dps));
            DEBUG((DEBUG_VERBOSE,"NameSpace Sharing                           : %08X\n", IdentifyNameSpaceData->Nmic));
            DEBUG((DEBUG_VERBOSE,"Reservation Capabilities                    : %08X\n", IdentifyNameSpaceData->Rescap));
            DEBUG((DEBUG_VERBOSE, "IEEE Extended Unique Identifier            : %016lx\n", IdentifyNameSpaceData->Eui64));
            for (i=0; i<16; i++){
                DEBUG((DEBUG_VERBOSE ,"LBA Format %02X Support                 : %08X\n", i, *(UINT32 *)&(IdentifyNameSpaceData->LbaFormat[i])));
            }
            break;
            
        case IdentifyActiveNsListCns:
            DEBUG((DEBUG_VERBOSE,"\nActive NameSpace IDs\n"));
            for (i=0; i<1024 && ActiveNameSapceID[i]; i++) {
                DEBUG((DEBUG_VERBOSE ,"    %X\n", i, ActiveNameSapceID[i]));
            }
    }
#endif
}
