//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file NvmeCtrl.c
    Header file for Nvme Controller/device definition

**/

#ifndef _NVME_CTRL_H
#define _NVME_CTRL_H

#define ADMIN_QUEUE_SIZE            0x100
#define IO_QUEUE_SIZE               0x100

#define MAX_MPS_ALLOWED             0x4000      // Maximum memory Page size allowed by NVMe Recovery driver

#pragma pack(1)

// Figure 10 NVM Express 1.1
typedef struct {
    UINT8   Opcode;
    UINT8   FusedOperation : 2;
    UINT8   Reserved1 : 5;
    UINT8   Psdt : 1;
    UINT16  CommandIdentifier;
} STRUC_CMD0;

typedef struct {
    STRUC_CMD0  Cmd0;
    UINT32      Nsid;
    UINT64      Reserved1;
    UINT64      Mptr;
    UINT64      Prp1;
    UINT64      Prp2;
    UINT32      Cdw10;
    UINT32      Cdw11;
    UINT32      Cdw12;
    UINT32      Cdw13;
    UINT32      Cdw14;
    UINT32      Cdw15;
} NVME_ADMIN_COMMAND;

typedef struct {
    NVME_ADMIN_COMMAND    NvmCmd;
    BOOLEAN               AdminOrNVMCmdSet;           // TRUE for Admin
    UINT16                SqIdentifier;               // Queue 0 for Admin cmds and 1 for NVM cmds
    UINT32                CmdTimeOut;                 // In msec.
    UINT8                 RetryCount;
} NVME_COMMAND_WRAPPER;

//Figure 25  NVM Express 1.1 Spec
typedef struct {
    UINT32      Dw0;
    UINT32      Dw1;
    UINT16      SqHeadPointer;
    UINT16      SqIdentifier;
    UINT16      CommandIdentifier;
    UINT16      PhaseTag :  1;
    UINT16      StatusCode :  8;
    UINT16      StatusCodeType : 3;
    UINT16      Reservered1 : 2;
    UINT16      More : 1;
    UINT16      DoNotRetry  : 1;
} COMPLETION_QUEUE_ENTRY;

typedef struct {
    EDKII_PEI_NVM_EXPRESS_PASS_THRU_PPI NvmePassThru;
    UINT64            BarAddress;
    UINT8             BusNumber;
    UINT8             Device;
    UINT8             Function;
    UINT16            CommandIdentifierAdmin;
    UINT16            CommandIdentifierQueue1;
    UINT64            RawNvmeCapability;
    UINT32            MaxQueueEntrySupported;
    BOOLEAN           ContiguousQueueRequired;
    BOOLEAN           ArbitrationMechanismSupport;
    UINT8             TimeOut;
    UINT8             DoorBellStride;
    BOOLEAN           NVMResetSupport;
    UINT8             CmdSetsSupported;
    UINT32            MemoryPageSizeMin;
    UINT32            MemoryPageSizeMax;
    UINT32            MemoryPageSize;

    //----------Admin Nvme Cmds-----------
    UINT64            AdminSubmissionUnAligned;         // Points to the start of the buffer
    UINTN             AdminSubmissionUnAlignedSize;
    UINT64            AdminSubmissionQueue;             // Points to the start of the buffer Aligned
    UINTN             AdminSubmissionQueueSize;
    UINT16            AdminSubmissionQueueHeadPtr;
    UINT16            AdminSubmissionQueueTailPtr;
    
    UINT64            AdminCompletionUnAligned;
    UINTN             AdminCompletionUnAlignedSize;
    UINT64            AdminCompletionQueue;             // Points to the start of the buffer Aligned
    UINTN             AdminCompletionQueueSize;
    UINT16            AdminCompletionQueueHeadPtr;
    UINT16            AdminCompletionQueueTailPtr;
    UINT8             AdminPhaseTag : 1;
    UINT8             Reserved : 7;
    
    //----------Queue1 for Nvme Cmds----------
    UINT16            NVMQueueNumber;
    UINT64            Queue1SubmissionUnAligned;        // Points to the start of the buffer
    UINTN             Queue1SubmissionUnAlignedSize;    // Original size
    UINT64            Queue1SubmissionQueue;            // Aligned address

    UINT64            Queue1CompletionUnAligned;
    UINTN             Queue1CompletionUnAlignedSize;
    UINT64            Queue1CompletionQueue;

    UINT32            Queue1SubmissionQueueSize;
    UINT32            Queue1CompletionQueueSize;
    UINT16            Queue1CompletionQueueHeadPtr;  
    UINT16            Queue1CompletionQueueTailPtr;  
    UINT16            Queue1SubmissionQueueHeadPtr;      // Updated from Completion queue entry
    UINT16            Queue1SubmissionQueueTailPtr;      // Updated when new cmds are issued
    UINT8             Queue1PhaseTag : 1;
    UINT8             Reserved1 : 7;
    
    NVME_ADMIN_CONTROLLER_DATA  *IdentifyData;  
    NVME_COMMAND_WRAPPER        *NvmeCmdWrapper;                  // Will be used by internal routines
    BOOLEAN                     ReInitializingQueue1;             // Flag used to prevent initializing Queue1 in an infinite loop
    EFI_DEVICE_PATH             *DevPath;
    UINT32                      ControllerVersion;
    UINT32                      *ActiveNameSpaceIds;
    UINT32                      TotalActiveNameSpaceCount;
    LIST_ENTRY                  ActiveNameSpaceList;
} NVME_CONTROLLER_INFO;

typedef struct {
    UINT32                        Signature;
    UINT32                        ActiveNameSpaceId;
    NVME_ADMIN_NAMESPACE_DATA     IdentifyNamespaceData;
    UINT64                        *Prp2List;                       // if the data transfer size is more than twice the max. page size 
    EFI_PEI_BLOCK_IO_MEDIA        MediaInfo;
    BOOLEAN                       LookedForMedia;
    EFI_DEVICE_PATH               *DevicePath;
    NVME_CONTROLLER_INFO          *NvmeControllerInfo;
    LIST_ENTRY                    Link;
} ACTIVE_NAMESPACE_DATA;

#pragma pack()

EFI_STATUS
ExecuteNvmeCmd (
    IN  NVME_CONTROLLER_INFO    *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER    *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY  *CmdCompletionData
);

EFI_STATUS
RecreateQueue1 (
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo
);

EFI_STATUS
CreateAdditionalSubmissionCompletionQueue ( 
    IN  NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER   *NvmeCmdWrapper,
    IN  UINT16                 QueueNumber,
    IN  UINT32                 QueueSize
);

EFI_STATUS
WaitForCompletionQueueUpdate (
    IN  NVME_CONTROLLER_INFO       *NvmeControllerInfo,
    IN  NVME_COMMAND_WRAPPER       *NvmeCmdWrapper,
    OUT COMPLETION_QUEUE_ENTRY     *CmdCompletionData 
);

EFI_STATUS
ConfigureActiveNamespace(
    NVME_CONTROLLER_INFO   *NvmeControllerInfo,
    UINT32                 ActiveNameSpaceId
);

EFI_STATUS  
GetIdentifyData (
    IN  NVME_CONTROLLER_INFO        *NvmeControllerInfo, 
    OUT VOID                        *IdentifyData,
    IN  NVME_ADMIN_IDENTIFY_CNS     ControllerNameSpaceStructure, 
    IN  UINT32                      NameSpaceID
);

EFI_STATUS
SetNumberOfQueues (
    NVME_CONTROLLER_INFO *NvmeControllerInfo
);

EFI_STATUS
NvmeReadBlocks (
    IN  ACTIVE_NAMESPACE_DATA    *ActiveNameSpace,
    IN  EFI_LBA                   Lba,
    IN  UINTN                     BufferSize,
    OUT VOID                      *Buffer,
    IN OUT COMPLETION_QUEUE_ENTRY *NvmeCompletionData
);

EFI_STATUS
ProgramPrp2List (
    IN  UINT64  *Prp2List, 
    IN  UINT32  PageSize, 
    IN  UINTN   BufferAddress,
    IN  UINTN   BufferSize,
    IN  UINTN   *Prp2TransferSize
);

VOID
PrintExecuteNvmeCmdData (
    IN NVME_COMMAND_WRAPPER    *NvmeCmdWrapper
);

VOID
PrintIdentifyDataStructure (
    IN  VOID                      *IdentifyData, 
    IN  NVME_ADMIN_IDENTIFY_CNS   ControllerNameSpaceStructure
);

#endif // _AMI_NVME_CTRL_H
