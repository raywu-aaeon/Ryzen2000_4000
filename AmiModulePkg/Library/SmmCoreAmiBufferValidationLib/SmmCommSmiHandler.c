//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AmiSmmCommunication.h>
#include <Guid/AmiAcpiSmmCommunicationTable.h>
#include <Include/IndustryStandard/Acpi.h>
#include <AmiSmmCommunicationMailbox.h>

// forward declaration
EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibSmiHandlerDestructor(VOID);

#if defined(_MSC_EXTENSIONS)
// Disable 'cast truncates constant value' warning that is generated
// when EFI_STATUS_TO_SMM_MAILBOX_STATUS is used with standard UEFI status constants.
#pragma warning ( disable: 4310 )
#endif

#define EFI_STATUS_TO_SMM_MAILBOX_STATUS(Status) (UINT32)( (EFI_ERROR(Status)) ? 0x80000000|(UINT32)(Status) : (UINT32)(Status) )
#define IS_ENABLED(BitMask, Bit) (((BitMask) & (Bit)) == (Bit))
#define IS_BUFFER_OVERFLOW(BufferAddress, BufferSize) ( (BufferSize) != 0 && (UINTN)(BufferAddress) - 1 + (BufferSize) < (UINTN)(BufferAddress) )

extern BOOLEAN SmmAmiBufferValidationLibSmmIsLocked;

VOID *SmmAmiBufferValidationLibSwDispatchRegistration = NULL;

AMI_SMM_COMMUNICATION_MAILBOX *SmmAmiBufferValidationLibSmmMailBox = NULL;
EFI_PHYSICAL_ADDRESS SmmAmiBufferValidationLibCommunicationBuffer = 0;
UINT32 SmmAmiBufferValidationLibCommunicationBufferSize = 0;
UINT32 SmmAmiBufferValidationLibTransactionId = 0;
BOOLEAN SmmAmiBufferValidationLibBufferLocked = FALSE;
EFI_SMM_CPU_PROTOCOL *SmmAmiBufferValidationLibSmmCpu = NULL;
STATIC EFI_HANDLE AmiSmmCommunicationHandle = NULL;

BOOLEAN SmmAmiBufferValidationLibIsBufferLocked(){
    if (!SmmAmiBufferValidationLibBufferLocked){
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_ACCESS_DENIED);
    }
    return SmmAmiBufferValidationLibBufferLocked;
}

BOOLEAN SmmAmiBufferValidationLibIsMailboxValid(){
    if (    SmmAmiBufferValidationLibSmmMailBox->Revision != AMI_SMM_COMMUNICATION_MAILBOX_REVISION
         || SmmAmiBufferValidationLibSmmMailBox->PhysicalAddress != SmmAmiBufferValidationLibCommunicationBuffer
         || SmmAmiBufferValidationLibSmmMailBox->Token != SmmAmiBufferValidationLibTransactionId
    ){
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_INVALID_PARAMETER);
        return FALSE;
    }
    return TRUE;
}

STATIC EFI_STATUS CheckGetRegisterBlockCall(){
    if (!IS_ENABLED(
        PcdGet32(AmiPcdSmmCommInterfaceProperties),
        AMI_SMM_COMMUNICATION_PROPERTY_X86_REG_SUPPORT
    )) return EFI_UNSUPPORTED;
    
    if (!SmmAmiBufferValidationLibIsBufferLocked()){
        DEBUG((DEBUG_ERROR, "ERROR: Attempt to get register block without locking the buffer.\n"));
        return EFI_NOT_FOUND;
    }
    if (!SmmAmiBufferValidationLibIsMailboxValid()){
        DEBUG((DEBUG_ERROR, "ERROR: Attempt to get register block with invalid mailbox content.\n"));
        return EFI_NOT_FOUND;
    }

    if (    SmmAmiBufferValidationLibSmmMailBox->Status
         != AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_X86_REGISTERS
    ) return EFI_NOT_FOUND;

    return EFI_SUCCESS;
}

/** @internal
    If buffer is within SMM Communication Buffer, makes sure it was properly allocated.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer

    @retval  EFI_SUCCESS - The buffer is valid
    @retval  EFI_ACCESS_DENIED - The buffer can't be used
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
**/
EFI_STATUS SmmAmiBufferValidationLibCheckSmmCommunicationBuffer(
    CONST VOID* Buffer, CONST UINTN BufferSize
){
    UINTN BufferAddress;
    EFI_PHYSICAL_ADDRESS EndOfCommBuffer;

    if (Buffer == NULL) return EFI_INVALID_PARAMETER;

    if (SmmAmiBufferValidationLibSmmMailBox == NULL) return EFI_SUCCESS;
    BufferAddress = (UINTN)Buffer;
    if (IS_BUFFER_OVERFLOW(BufferAddress, BufferSize)) return EFI_INVALID_PARAMETER; // overflow

    EndOfCommBuffer = SmmAmiBufferValidationLibCommunicationBuffer + SmmAmiBufferValidationLibCommunicationBufferSize;
    // If buffer is outside SMM Communication buffer, return EFI_SUCCESS
    if (    BufferAddress >= EndOfCommBuffer
         || BufferAddress+BufferSize <= SmmAmiBufferValidationLibCommunicationBuffer
    ) return EFI_SUCCESS;

    // If buffer overlaps with the SMM Communication buffer, but is not entirely
    // in the SMM Communication buffer, return an error
    if (    BufferAddress < SmmAmiBufferValidationLibCommunicationBuffer
         || BufferAddress+BufferSize > EndOfCommBuffer
    ){
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_ACCESS_DENIED);
        return EFI_ACCESS_DENIED;
    }
    // If buffer is in the SMM Communication buffer, the size can't be zero
    if (BufferSize == 0){
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_INVALID_PARAMETER);
        return EFI_INVALID_PARAMETER;
    }

    // Buffer must be locked before it's used.
    // Owner must initialized mailbox field Token before every call.
    if (    !SmmAmiBufferValidationLibBufferLocked
         || SmmAmiBufferValidationLibSmmMailBox->Token != SmmAmiBufferValidationLibTransactionId
    ){
        DEBUG_CODE(
            if (!SmmAmiBufferValidationLibBufferLocked)
                DEBUG((DEBUG_ERROR, "ERROR: Application SMM communication buffer is unlocked.\n"));
            else
                DEBUG((DEBUG_ERROR, "ERROR: Application SMM communication buffer access token is invalid.\n"));
        );
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_ACCESS_DENIED);
        return EFI_ACCESS_DENIED;
    }
    if (EFI_ERROR(CheckGetRegisterBlockCall())){
        SmmAmiBufferValidationLibSmmMailBox->Status = 0;
    }
    return EFI_SUCCESS;
}

////// New Style Interface
VOID SmmAmiBufferValidationLibMailboxReset(){
    SmmAmiBufferValidationLibSmmMailBox->Token = 0;
    SmmAmiBufferValidationLibSmmMailBox->Status = 0;
    SmmAmiBufferValidationLibSmmMailBox->Revision = 0;
    SmmAmiBufferValidationLibSmmMailBox->PhysicalAddress = 0;
}

/**
    Returns address and size of the SMM Communication buffer
    
    @param[out] Address address of the SMM Communication buffer
    @param[out] Size    size of the SMM Communication buffer
**/
STATIC EFI_STATUS GetCommunicationBuffer(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    OUT UINT64 *Address, OUT UINT32 *Size
){
    if (Address == NULL || Size == NULL) return EFI_INVALID_PARAMETER;
    if (SmmAmiBufferValidationLibCommunicationBuffer == 0) return EFI_UNSUPPORTED;
    *Address = SmmAmiBufferValidationLibCommunicationBuffer;
    *Size = SmmAmiBufferValidationLibCommunicationBufferSize;
    return EFI_SUCCESS;
}

/**
    Returns register block data structure from the SMM Communication mailbox
    
    @param[in]  SwSmiNumber      SW SMI number of the handler that uses the interface
    @param[out] RegisterBlock    Copy of the AMI_SMM_COMM_BUFFER_X86_REGISTERS 
                                 data structure from the SMM Communication mailbox
**/
STATIC EFI_STATUS GetRegisterBlock(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    IN UINT32 SwSmiNumber,
    OUT AMI_SMM_COMM_BUFFER_X86_REGISTERS *RegisterBlock
){
    EFI_STATUS Status = CheckGetRegisterBlockCall();

    if (!EFI_ERROR(Status)){
        if (    SmmAmiBufferValidationLibSmmMailBox->Status
             != AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_X86_REGISTERS
        ){
            Status = EFI_NOT_FOUND;
        } else {
            if (SmmAmiBufferValidationLibSmmMailBox->Data.Regs.SwSmiNumber != SwSmiNumber)
                Status = EFI_INVALID_PARAMETER;
        }
    }
    if (EFI_ERROR(Status)){
        SmmAmiBufferValidationLibMailboxReset();
        return Status;
    }
    if (RegisterBlock != NULL){
        CopyMem(
            RegisterBlock, 
            &SmmAmiBufferValidationLibSmmMailBox->Data.Regs,
            sizeof(SmmAmiBufferValidationLibSmmMailBox->Data.Regs)
        );
    }
    return EFI_SUCCESS;
}

/**
    Updates register block data structure in the SMM Communication mailbox

    @param[in]  SwSmiNumber      SW SMI number of the handler that uses the interface
    @param[in]  RegisterBlock    register block data structure to copy 
                                 to the SMM Communication mailbox
**/
STATIC EFI_STATUS EFIAPI SetRegisterBlock(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    IN UINT32 SwSmiNumber,
    IN AMI_SMM_COMM_BUFFER_X86_REGISTERS *RegisterBlock
){
    EFI_STATUS Status;
    
    if (RegisterBlock == NULL) return EFI_INVALID_PARAMETER;
    Status = GetRegisterBlock(This, SwSmiNumber, NULL);
    if (EFI_ERROR(Status)) return Status;
    CopyMem(
        &SmmAmiBufferValidationLibSmmMailBox->Data.Regs,
        RegisterBlock, 
        sizeof(SmmAmiBufferValidationLibSmmMailBox->Data.Regs)
    );
    SmmAmiBufferValidationLibMailboxReset();
    return EFI_SUCCESS;
}

STATIC AMI_SMM_COMMUNICATION_PROTOCOL AmiSmmCommunication = {
    /// Version of the protocol interface structure
    1,
    /// Returns address and size of the SMM Communication buffer
    GetCommunicationBuffer,
    /// Returns register block data structure from the SMM Communication mailbox 
    GetRegisterBlock,
    /// Updates register block data structure in the SMM Communication mailbox
    SetRegisterBlock
};

EFI_STATUS EFIAPI SmmAmiBufferValidationLibSmmMailBoxHandler(
    IN EFI_HANDLE DispatchHandle, IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL, IN OUT UINTN *CommBufferSize OPTIONAL
){
    UINT32 Command;
    EFI_SMM_COMMUNICATE_HEADER *SmmCommHeader;
    EFI_STATUS Status;
    
    if (    SmmAmiBufferValidationLibSmmMailBox == NULL
         || CommBuffer == NULL || CommBufferSize == NULL || *CommBufferSize != sizeof(EFI_SMM_SW_CONTEXT)
    ) return EFI_SUCCESS;

    Command = SmmAmiBufferValidationLibSmmMailBox->Status;

    if (Command == AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_LOCK ){
        // Lock
        UINT32 BufferSize = SmmAmiBufferValidationLibSmmMailBox->Data.Lock.Size;
        UINT32 Flags = SmmAmiBufferValidationLibSmmMailBox->Data.Lock.Flags;

        if (    SmmAmiBufferValidationLibBufferLocked
             && (Flags & AMI_SMM_COMMUNICATION_MAILBOX_LOCK_FLAG_FORCE_LOCK)==0
        ){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to lock application SMM communication buffer that is already locked.\n"));
            SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_ACCESS_DENIED);
            return EFI_SUCCESS;
        }

        if (BufferSize > SmmAmiBufferValidationLibCommunicationBufferSize){
            DEBUG((DEBUG_ERROR,
                "ERROR: Requested application SMM communication buffer size is not supported.\nRequested size=%X; Supported size=%X.\n",
                BufferSize, SmmAmiBufferValidationLibCommunicationBufferSize
            ));
            SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_BAD_BUFFER_SIZE);
            SmmAmiBufferValidationLibSmmMailBox->Data.Lock.Size = SmmAmiBufferValidationLibCommunicationBufferSize;
            return EFI_SUCCESS;
        }
        SmmAmiBufferValidationLibTransactionId++;
        SmmAmiBufferValidationLibBufferLocked = TRUE;
        SmmAmiBufferValidationLibSmmMailBox->Revision = AMI_SMM_COMMUNICATION_MAILBOX_REVISION;
        SmmAmiBufferValidationLibSmmMailBox->PhysicalAddress = SmmAmiBufferValidationLibCommunicationBuffer;
        SmmAmiBufferValidationLibSmmMailBox->Token = SmmAmiBufferValidationLibTransactionId;
        SmmAmiBufferValidationLibSmmMailBox->Status = 0;
        SmmAmiBufferValidationLibSmmMailBox->Data.Lock.Flags = 
            IS_ENABLED(
                PcdGet32(AmiPcdSmmCommInterfaceProperties),
                AMI_SMM_COMMUNICATION_PROPERTY_X86_REG_SUPPORT
            ) ? 1 : 0;
    } else if (Command == AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_UNLOCK ){
        // Unlock
        if (!SmmAmiBufferValidationLibIsBufferLocked()){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to unlock application SMM communication buffer that is not locked.\n"));
            return EFI_SUCCESS;
        }
        if (!SmmAmiBufferValidationLibIsMailboxValid()){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to unlock SMM communication buffer with invalid mailbox content.\n"));
            return EFI_SUCCESS;
        }
        SmmAmiBufferValidationLibBufferLocked = FALSE;
        SmmAmiBufferValidationLibMailboxReset();
    } else if (Command == AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_DISPATCH ){
        if (!SmmAmiBufferValidationLibIsBufferLocked()){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to start SMM communication without locking the buffer.\n"));
            return EFI_SUCCESS;
        }
        if (!SmmAmiBufferValidationLibIsMailboxValid()){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to start SMM communication with invalid mailbox content.\n"));
            return EFI_SUCCESS;
        }
        SmmCommHeader = (EFI_SMM_COMMUNICATE_HEADER*)(UINTN)SmmAmiBufferValidationLibCommunicationBuffer;
        if (SmmCommHeader->MessageLength > SmmAmiBufferValidationLibCommunicationBufferSize){
            DEBUG((
                DEBUG_ERROR, // %p is used to properly handle UINTN value
                "ERROR: SMM communication buffer with invalid message length(%p).\n",
                SmmCommHeader->MessageLength
            ));
            return EFI_SUCCESS;
        }
        Status = gSmst->SmiManage (
            &SmmCommHeader->HeaderGuid, NULL,
            SmmCommHeader->Data, &SmmCommHeader->MessageLength
        );
        SmmAmiBufferValidationLibMailboxReset();
        if (Status != EFI_SUCCESS) Status = EFI_NOT_FOUND;
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(Status);
    } else {
        SmmAmiBufferValidationLibSmmMailBox->Status = EFI_STATUS_TO_SMM_MAILBOX_STATUS(EFI_UNSUPPORTED);
        return EFI_SUCCESS;
    }
    return EFI_SUCCESS;
}

////// Legacy Interface
VOID SmmAmiBufferValidationLibSetSmiStatus(UINTN CpuIndex, EFI_STATUS Status){

    UINT32 SmiStatus = EFI_STATUS_TO_SMM_MAILBOX_STATUS(Status);

    Status = SmmAmiBufferValidationLibSmmCpu->WriteSaveState(
        SmmAmiBufferValidationLibSmmCpu,4, EFI_SMM_SAVE_STATE_REGISTER_RCX, CpuIndex, &SmiStatus
    );
    ASSERT_EFI_ERROR(Status);
}

EFI_STATUS EFIAPI SmmAmiBufferValidationLibLegacySmmMailBoxHandler(
    IN EFI_HANDLE DispatchHandle, IN CONST VOID *Context OPTIONAL,
    IN OUT VOID *CommBuffer OPTIONAL, IN OUT UINTN *CommBufferSize OPTIONAL
){
    EFI_STATUS Status;
    UINTN CpuIndex;
    UINT32 Command;
    EFI_PHYSICAL_ADDRESS MailboxAddress;

    if (    SmmAmiBufferValidationLibSmmMailBox == NULL
         || SmmAmiBufferValidationLibSmmCpu == NULL
         || CommBuffer == NULL || CommBufferSize == NULL || *CommBufferSize != sizeof(EFI_SMM_SW_CONTEXT)
    ) return EFI_SUCCESS;

    CpuIndex = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->SwSmiCpuIndex;
    Status = SmmAmiBufferValidationLibSmmCpu->ReadSaveState(
        SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RCX, CpuIndex, &Command
    );
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    if (Command == AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_LOCK ){
        // Lock
        UINT32 BufferSize;
        UINT32 Flags;

        Status = SmmAmiBufferValidationLibSmmCpu->ReadSaveState(
            SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RSI, CpuIndex, &BufferSize
        );
        if (EFI_ERROR(Status)) return EFI_SUCCESS;
        Status = SmmAmiBufferValidationLibSmmCpu->ReadSaveState(
            SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RDI, CpuIndex, &Flags
        );
        if (EFI_ERROR(Status)) return EFI_SUCCESS;

        if (    SmmAmiBufferValidationLibBufferLocked
             && (Flags & AMI_SMM_COMMUNICATION_MAILBOX_LOCK_FLAG_FORCE_LOCK)==0
        ){
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to lock application SMM communication buffer that is already locked.\n"));
            Status = EFI_ACCESS_DENIED;
            SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,Status);
            return EFI_SUCCESS;
        }

        if (BufferSize > SmmAmiBufferValidationLibCommunicationBufferSize){
            DEBUG((DEBUG_ERROR,
                "ERROR: Requested application SMM communication buffer size is not supported.\nRequested size=%X; Supported size=%X.\n",
                BufferSize, SmmAmiBufferValidationLibCommunicationBufferSize
            ));
            Status = EFI_BAD_BUFFER_SIZE;
            SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,Status);
            BufferSize = SmmAmiBufferValidationLibCommunicationBufferSize;
            Status = SmmAmiBufferValidationLibSmmCpu->WriteSaveState(
                SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RSI, CpuIndex, &BufferSize
            );
            ASSERT_EFI_ERROR(Status);
            return EFI_SUCCESS;
        }
        SmmAmiBufferValidationLibTransactionId++;
        SmmAmiBufferValidationLibBufferLocked = TRUE;
        SmmAmiBufferValidationLibSmmMailBox->Revision = 1;
        SmmAmiBufferValidationLibSmmMailBox->PhysicalAddress = SmmAmiBufferValidationLibCommunicationBuffer;
        SmmAmiBufferValidationLibSmmMailBox->Token = SmmAmiBufferValidationLibTransactionId;
        SmmAmiBufferValidationLibSmmMailBox->Status = 0;

        MailboxAddress = (UINTN)SmmAmiBufferValidationLibSmmMailBox;
        Status = SmmAmiBufferValidationLibSmmCpu->WriteSaveState(
            SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RSI, CpuIndex, &MailboxAddress
        );
        ASSERT_EFI_ERROR(Status);
        Status = SmmAmiBufferValidationLibSmmCpu->WriteSaveState(
            SmmAmiBufferValidationLibSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RDI, CpuIndex, (UINT32*)&MailboxAddress + 1
        );
        ASSERT_EFI_ERROR(Status);
    }else if (Command == AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_UNLOCK ){
        // Unlock
        if (!SmmAmiBufferValidationLibBufferLocked){
            Status = EFI_ACCESS_DENIED;
            SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,Status);
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to unlock application SMM communication buffer that is not locked.\n"));
            return EFI_SUCCESS;
        }
        if (    SmmAmiBufferValidationLibSmmMailBox->Revision != 1
             || SmmAmiBufferValidationLibSmmMailBox->PhysicalAddress != SmmAmiBufferValidationLibCommunicationBuffer
             || SmmAmiBufferValidationLibSmmMailBox->Token != SmmAmiBufferValidationLibTransactionId
        ){
            Status = EFI_INVALID_PARAMETER;
            SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,Status);
            DEBUG((DEBUG_ERROR, "ERROR: Attempt to unlock SMM communication buffer with invalid mailbox content.\n"));
            return EFI_SUCCESS;
        }
        SmmAmiBufferValidationLibBufferLocked = FALSE;
        SmmAmiBufferValidationLibSmmMailBox->Token = 0;
        SmmAmiBufferValidationLibSmmMailBox->Status = 0;
    }else {
        SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,EFI_UNSUPPORTED);
        return EFI_SUCCESS;
    }
    SmmAmiBufferValidationLibSetSmiStatus(CpuIndex,EFI_SUCCESS);
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI SmmAmiBufferValidationLibSwDispatch (
    IN CONST EFI_GUID *Protocol, IN VOID *Interface, IN EFI_HANDLE Handle
){
    EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch = Interface;
    EFI_SMM_SW_REGISTER_CONTEXT Context;
    EFI_HANDLE SmiHandle;
    EFI_STATUS Status;
    EFI_SMM_HANDLER_ENTRY_POINT2 Handler;

    if (SmmAmiBufferValidationLibSmmIsLocked) return EFI_SUCCESS;
    if (SmmAmiBufferValidationLibSmmMailBox != NULL) return EFI_SUCCESS;
    
    SmmAmiBufferValidationLibCommunicationBufferSize = PcdGet32(AmiPcdSmmCommunicationBufferSize);
    Status = gBS->AllocatePages(
        AllocateAnyPages, EfiRuntimeServicesData,
        EFI_SIZE_TO_PAGES(SmmAmiBufferValidationLibCommunicationBufferSize),
        &SmmAmiBufferValidationLibCommunicationBuffer
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)){
        SmmAmiBufferValidationLibCommunicationBuffer = 0;
        SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
        return EFI_SUCCESS;
    }

    Status = gBS->AllocatePool(
        EfiRuntimeServicesData, sizeof(AMI_SMM_COMMUNICATION_MAILBOX),
        (VOID **)&SmmAmiBufferValidationLibSmmMailBox
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)){
        SmmAmiBufferValidationLibSmmMailBox = NULL;
        SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
        return EFI_SUCCESS;
    }

    if ( IS_ENABLED(
            PcdGet32(AmiPcdSmmCommInterfaceProperties),
            AMI_SMM_COMMUNICATION_PROPERTY_NEW_STYLE_INTERFACE_SUPPORT
    ) ){
        AMI_ACPI_SMM_COMMUNICATION_TABLE Table;
        EFI_ACPI_TABLE_PROTOCOL *AcpiTable;
        UINTN TableKey;
        
        // Publish AmiSmmCommunication protocol
        Status = gSmst->SmmInstallProtocolInterface(
            &AmiSmmCommunicationHandle,
            &gAmiSmmCommunicationProtocolGuid,
            EFI_NATIVE_INTERFACE, &AmiSmmCommunication
        );
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)){
            AmiSmmCommunicationHandle = NULL;
            SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
            return EFI_SUCCESS;
        }
        // Publish ACPI table
        Status = gBS->LocateProtocol(
            &gEfiAcpiTableProtocolGuid, NULL,
            (VOID**)&AcpiTable
        );
        if (EFI_ERROR(Status)){
            SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
            return EFI_SUCCESS;
        }
        Table.UefiAcpiDataTable.Header.Signature = EFI_ACPI_5_0_UEFI_ACPI_DATA_TABLE_SIGNATURE;
        Table.UefiAcpiDataTable.Header.Length = sizeof(AMI_ACPI_SMM_COMMUNICATION_TABLE);
        Table.UefiAcpiDataTable.Header.Revision = 1;
        Table.UefiAcpiDataTable.Header.Checksum = 0;
        CopyMem(
            Table.UefiAcpiDataTable.Header.OemId,
            PcdGetPtr (PcdAcpiDefaultOemId),
            sizeof (Table.UefiAcpiDataTable.Header.OemId)
        );
        Table.UefiAcpiDataTable.Header.OemTableId = PcdGet64(PcdAcpiDefaultOemTableId);
        Table.UefiAcpiDataTable.Header.OemRevision = PcdGet32(PcdAcpiDefaultOemRevision);
        Table.UefiAcpiDataTable.Header.CreatorId = PcdGet32(PcdAcpiDefaultCreatorId);
        Table.UefiAcpiDataTable.Header.CreatorRevision = PcdGet32(PcdAcpiDefaultCreatorRevision);
        CopyGuid(
            &Table.UefiAcpiDataTable.Identifier,
            &gAmiAcpiSmmCommunucationTableGuid
        );
        Table.UefiAcpiDataTable.DataOffset = OFFSET_OF(AMI_ACPI_SMM_COMMUNICATION_TABLE, Revision);
        Table.Revision = AMI_SMM_COMMUNICATION_MAILBOX_REVISION;
        Table.SwSmiNumber = PcdGet8(AmiPcdSmmCommunicationBufferSwSmi);
        Table.MailboxAddress = (UINTN)SmmAmiBufferValidationLibSmmMailBox;
        Table.MailboxHeaderSize = OFFSET_OF(AMI_SMM_COMMUNICATION_MAILBOX, Data);
        Status = AcpiTable->InstallAcpiTable(
            AcpiTable, &Table, sizeof(Table), &TableKey
        );
        if (EFI_ERROR(Status)){
            SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
            return EFI_SUCCESS;
        }        
        Handler = SmmAmiBufferValidationLibSmmMailBoxHandler;
    }
    else {
        Status = gSmst->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, (VOID**)&SmmAmiBufferValidationLibSmmCpu);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)){
            SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
            return EFI_SUCCESS;
        }
        Handler = SmmAmiBufferValidationLibLegacySmmMailBoxHandler;
    }
    
    Context.SwSmiInputValue = PcdGet8(AmiPcdSmmCommunicationBufferSwSmi);
    Status = SwDispatch->Register(
        SwDispatch, Handler, &Context, &SmiHandle
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)){
        SmmCoreAmiBufferValidationLibSmiHandlerDestructor();
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibSmiHandlerConstructor(VOID){
    return gSmst->SmmRegisterProtocolNotify(
        &gEfiSmmSwDispatch2ProtocolGuid,
        SmmAmiBufferValidationLibSwDispatch,
        &SmmAmiBufferValidationLibSwDispatchRegistration
    );
}
        
EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibSmiHandlerDestructor(VOID){
    EFI_STATUS Status;
    
    Status = gSmst->SmmRegisterProtocolNotify(
        &gEfiSmmSwDispatch2ProtocolGuid, NULL, &SmmAmiBufferValidationLibSwDispatchRegistration
    );
    if (SmmAmiBufferValidationLibCommunicationBuffer != 0){
        gBS->FreePages(
                SmmAmiBufferValidationLibCommunicationBuffer,
            EFI_SIZE_TO_PAGES(SmmAmiBufferValidationLibCommunicationBufferSize)
        );
        SmmAmiBufferValidationLibCommunicationBuffer = 0;
    }
    if (SmmAmiBufferValidationLibSmmMailBox != NULL){
        gBS->FreePool(SmmAmiBufferValidationLibSmmMailBox);
        SmmAmiBufferValidationLibSmmMailBox = NULL;
    }
    if (AmiSmmCommunicationHandle != NULL){
        gSmst->SmmUninstallProtocolInterface(
            AmiSmmCommunicationHandle,
            &gAmiSmmCommunicationProtocolGuid,
            &AmiSmmCommunication
        );
    }
    return Status;
}
