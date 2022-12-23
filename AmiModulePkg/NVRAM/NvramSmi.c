//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

/** @file
    NvramSmi helps secure a system by providing a set of variable service functions
    which route variable access through the SMM interface.
**/
#include <AmiDxeLib.h>
#include <Library/AmiBufferValidationLib.h>
#include "NvramSmi.h"
#include "NvramDxeCommon.h"
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

EFI_HANDLE  VarSmiHandle = NULL;

EFI_STATUS SmmSetVariable(
    IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid,
    IN UINT32 Attributes, IN UINTN DataSize, IN VOID *Data
);

EFI_STATUS GetVariableSmmHandler(
    SMI_GET_VARIABLE_BUFFER *GetVarBuffer, UINTN BufferSize
){
    CHAR16 *VariableName = NULL;
    SMI_GET_VARIABLE_BUFFER GetVar;
    EFI_STATUS Status;
    // Validate input buffer before accessing it.
    if (BufferSize <= sizeof(SMI_GET_VARIABLE_BUFFER)) return EFI_INVALID_PARAMETER;
    CopyMem (&GetVar, GetVarBuffer, sizeof (SMI_GET_VARIABLE_BUFFER));
    
    BufferSize -= sizeof(SMI_GET_VARIABLE_BUFFER);
    // Variable name must contains at least one character (zero terminator). String size must be an even number
    if (   GetVar.VariableNameSize<sizeof(CHAR16)
        || (GetVar.VariableNameSize & 1) != 0
    ) return EFI_INVALID_PARAMETER;
    if (BufferSize < GetVar.VariableNameSize) return EFI_INVALID_PARAMETER;
    BufferSize -= (UINTN)GetVar.VariableNameSize;
    VariableName = AllocateCopyPool ((UINTN)GetVar.VariableNameSize, (VOID *)(GetVarBuffer+1));
    if (VariableName == NULL) return EFI_OUT_OF_RESOURCES;
    // Make sure variable name is zero terminated.
    if (VariableName[(UINTN)GetVar.VariableNameSize/sizeof(CHAR16)-1]) return EFI_INVALID_PARAMETER;
    if (BufferSize != GetVar.DataSize) return EFI_INVALID_PARAMETER;

    Status = DxeGetVariableWrapper (
        VariableName, &GetVar.Guid,
        &GetVarBuffer->Attributes, (UINTN*)&GetVar.DataSize,
        (BufferSize==0) ? NULL : (VOID*)((UINT8*)(GetVarBuffer+1) + GetVar.VariableNameSize)
    );
    GetVarBuffer->DataSize = GetVar.DataSize;
    if (VariableName != NULL) {
        FreePool (VariableName);
    }
    return Status;
}

EFI_STATUS GetNextVariableNameSmmHandler(
    SMI_GET_NEXT_VARIABLE_NAME_BUFFER *GetNextVarNameBuffer, UINTN BufferSize
){
    CHAR16 *VariableName = NULL;
    SMI_GET_NEXT_VARIABLE_NAME_BUFFER GetNextVarName;
    EFI_STATUS Status;
    //Validate input buffer before accessing it.
    if (BufferSize <= sizeof(SMI_GET_NEXT_VARIABLE_NAME_BUFFER)) return EFI_INVALID_PARAMETER;
    CopyMem (&GetNextVarName, GetNextVarNameBuffer, sizeof (SMI_GET_NEXT_VARIABLE_NAME_BUFFER));
    BufferSize -= sizeof(SMI_GET_NEXT_VARIABLE_NAME_BUFFER);
    if (BufferSize != GetNextVarName.DataSize) return EFI_INVALID_PARAMETER;
    // Input variable name must contains at least one character (zero terminator).
    if (GetNextVarName.DataSize<sizeof(CHAR16)) return EFI_INVALID_PARAMETER;
    //Validating VariableName
    VariableName = AllocateCopyPool ((UINTN)GetNextVarName.DataSize, (VOID *)(GetNextVarNameBuffer+1));
    if (VariableName == NULL) return EFI_OUT_OF_RESOURCES;
    if (GetVariableNameSize(VariableName, (UINTN)GetNextVarName.DataSize) > GetNextVarName.DataSize) return EFI_INVALID_PARAMETER;

    Status = DxeGetNextVariableNameWrapper(
        (UINTN*)&GetNextVarName.DataSize,
        VariableName, &GetNextVarName.Guid
    );
    if (!EFI_ERROR (Status)) {
        StrCpyS ((CHAR16 *)(GetNextVarNameBuffer+1), (UINTN) GetNextVarName.DataSize, VariableName);
        CopyMem (&GetNextVarNameBuffer->Guid, &GetNextVarName.Guid, sizeof(EFI_GUID));
    }
    GetNextVarNameBuffer->DataSize = GetNextVarName.DataSize;
    if (VariableName != NULL) {
        FreePool (VariableName);
    }
    return Status;
}

EFI_STATUS SetVariableSmmHandler(
    SMI_SET_VARIABLE_BUFFER *SetVarBuffer, UINTN BufferSize
){
    CHAR16 *VariableName = NULL;
    SMI_SET_VARIABLE_BUFFER SetVar;
    VOID *VariableData = NULL;
    EFI_STATUS Status;
    //Validate input buffer before accessing it.
    if (BufferSize <= sizeof(SMI_SET_VARIABLE_BUFFER)) return EFI_INVALID_PARAMETER;
    BufferSize -= sizeof(SMI_SET_VARIABLE_BUFFER);
    CopyMem (&SetVar, SetVarBuffer, sizeof (SMI_SET_VARIABLE_BUFFER));
    // Variable name must contains at least one character (zero terminator). String size must be an even number
    if (   SetVar.VariableNameSize<sizeof(CHAR16)
        || (SetVar.VariableNameSize & 1) != 0
    ) return EFI_INVALID_PARAMETER;
    if (BufferSize < SetVar.VariableNameSize) return EFI_INVALID_PARAMETER;
    BufferSize -= (UINTN)SetVar.VariableNameSize;
    VariableName = AllocateCopyPool ((UINTN)SetVar.VariableNameSize, (VOID *)(SetVarBuffer+1));
    if (VariableName == NULL) return EFI_OUT_OF_RESOURCES;
    // Make sure variable name is zero terminated.
    if (VariableName[(UINTN)SetVar.VariableNameSize/sizeof(CHAR16)-1]) return EFI_INVALID_PARAMETER;
    if (BufferSize != SetVar.DataSize) return EFI_INVALID_PARAMETER;
    if (BufferSize !=0){
        VariableData = AllocateCopyPool (SetVar.DataSize, (VOID*)((UINT8*)(SetVarBuffer+1) + SetVarBuffer->VariableNameSize));
        if (VariableData == NULL) return EFI_OUT_OF_RESOURCES;
    }
    Status = SmmSetVariable (
        VariableName, &SetVar.Guid,
        SetVar.Attributes, (UINTN)SetVar.DataSize,
        VariableData
    );
    if (VariableName != NULL) {
            FreePool (VariableName);
    }
    if (VariableData != NULL) {
            FreePool (VariableData);
    }
    return Status;
    
}

EFI_STATUS QueryVariableInfoSmmHandler(
    SMI_QUERY_VARIABLE_INFO_BUFFER *QueryVarInfoBuffer, UINTN BufferSize
){
    UINT32 Attributes;
    //Validate input buffer before accessing it.
    if (BufferSize != sizeof(SMI_QUERY_VARIABLE_INFO_BUFFER)) return EFI_INVALID_PARAMETER;
    Attributes = QueryVarInfoBuffer->Attributes;
    return QueryVariableInfo (
        Attributes,
        &QueryVarInfoBuffer->MaximumVariableStorageSize,
        &QueryVarInfoBuffer->RemainingVariableStorageSize,
        &QueryVarInfoBuffer->MaximumVariableSize
    );
}

EFI_STATUS RequestToLockSmmHandler(
    SMI_REQUEST_TO_LOCK_BUFFER *RequestToLockBuffer, UINTN BufferSize
){
    CHAR16 *VariableName = NULL;
    SMI_REQUEST_TO_LOCK_BUFFER RequestToLock;
    EFI_STATUS Status;

    //Validate input buffer before accessing it.
    if (BufferSize <= sizeof(SMI_REQUEST_TO_LOCK_BUFFER)) return EFI_INVALID_PARAMETER;
    BufferSize -= sizeof(SMI_REQUEST_TO_LOCK_BUFFER);
    CopyMem (&RequestToLock, RequestToLockBuffer, sizeof (SMI_REQUEST_TO_LOCK_BUFFER));
    if (BufferSize != RequestToLock.DataSize) return EFI_INVALID_PARAMETER;
    // Variable name must contains at least one character (zero terminator). String size must be an even number
    if (   RequestToLock.DataSize<sizeof(CHAR16)
        || (RequestToLock.DataSize & 1) != 0
    ) return EFI_INVALID_PARAMETER;
    VariableName = AllocateCopyPool ((UINTN)RequestToLock.DataSize, (VOID *)(RequestToLockBuffer+1));
    if (VariableName == NULL) return EFI_OUT_OF_RESOURCES;
    // Make sure variable name is zero terminated.
    if (VariableName[(UINTN)RequestToLock.DataSize/sizeof(CHAR16)-1]) return EFI_INVALID_PARAMETER;

    Status = DxeRequestToLock(
        NULL,VariableName,&RequestToLock.Guid
    );
    if (VariableName != NULL) {
        FreePool (VariableName);
    }
    return Status;
}

EFI_STATUS ExitBootServicesSmmHandler(
    SMI_EXIT_BOOT_SERVICES_BUFFER *ExitBootServicesBuffer, UINTN BufferSize
){
    //Validate input buffer before accessing it.
    if (BufferSize != sizeof(SMI_EXIT_BOOT_SERVICES_BUFFER)) return EFI_INVALID_PARAMETER;
    SwitchToRuntime();
    return EFI_SUCCESS;
}

/**
     SMI handler for NVRAM SMM Communication API.

    @param DispatchHandle - Dispatch Handle
    @param Context - Pointer to the passed context
    @param CommBuffer - Pointer to the passed Communication Buffer
    @param CommBufferSize - Pointer to the Comm Buffer Size


    @retval EFI_STATUS based on result

**/
EFI_STATUS EFIAPI NvramSmmCommunicationHandler (
  IN EFI_HANDLE DispatchHandle, IN CONST VOID *Context,
  IN OUT VOID *CommBuffer, IN OUT UINTN *CommBufferSize
){
    EFI_STATUS  Status;
    UINT64 *Command;
    VOID *Tmp;
    UINTN BufferSize;

    // Validate the buffer
    BufferSize = *CommBufferSize;
    Status = AmiValidateMemoryBuffer(CommBuffer, BufferSize);
    // A list of SMI handler return codes in defined by PI specification.
    // We can't return arbitrary error here.
    if (EFI_ERROR(Status)) return EFI_SUCCESS;
    if (BufferSize < sizeof(*Command))  return EFI_SUCCESS;

    // The CommBuffer is a pointer passed to SMM Communicate incremented to strip the header (GUID and MessageSize).
    // Since message size is UINTN, the pointer will not be naturally aligned in 32-bit mode.
    // We're aligning pointer to guarantee natural alignment.
    // See NVRAM_COMMUNICATION_BUFFER definition in NvramSmiDxe.c (The structure is naturally aligned).
    Tmp = ALIGN_POINTER(CommBuffer,sizeof(*Command));
    BufferSize -= (UINTN)Tmp-(UINTN)CommBuffer;
    CommBuffer = Tmp;
    Command = (UINT64*)CommBuffer;

    // Perform basic buffer size validation.
    // A more advanced validation is performed by the command handling functions.
    if (BufferSize < sizeof(*Command))  return EFI_SUCCESS;
    switch (*Command){
        case NVRAM_SMM_COMMAND_GET_VARIABLE: //GetVariable
            Status = GetVariableSmmHandler((SMI_GET_VARIABLE_BUFFER*)CommBuffer, BufferSize);
            break;
        case NVRAM_SMM_COMMAND_GET_NEXT_VARIABLE_NAME: //GetNextVariableName
            Status = GetNextVariableNameSmmHandler((SMI_GET_NEXT_VARIABLE_NAME_BUFFER*)CommBuffer, BufferSize);
            break;
        case NVRAM_SMM_COMMAND_SET_VARIABLE: //SetVariable
            Status = SetVariableSmmHandler((SMI_SET_VARIABLE_BUFFER*)CommBuffer, BufferSize);
            break;
        case NVRAM_SMM_COMMAND_QUERY_VARIABLE_INFO: //QueryVariableInfo
            Status = QueryVariableInfoSmmHandler((SMI_QUERY_VARIABLE_INFO_BUFFER*)CommBuffer, BufferSize);
            break;
        case NVRAM_SMM_COMMAND_REQUEST_TO_LOCK:
            Status = RequestToLockSmmHandler((SMI_REQUEST_TO_LOCK_BUFFER*)CommBuffer, BufferSize);
            break;
        case NVRAM_SMM_COMMAND_EXIT_BOOT_SERVICES:
            Status = ExitBootServicesSmmHandler((SMI_EXIT_BOOT_SERVICES_BUFFER*)CommBuffer, BufferSize);
            break;
        default:
            Status = EFI_INVALID_PARAMETER;
            break;
    }
    *Command = EFI_STATUS_TO_NVRAM_SMM_STATUS(Status);

    return EFI_SUCCESS;
}

/**
    Entry point.

    @param  ImageHandle - Image Handle
    @param  SystemTable - Pointer to a System Table

    @retval EFI_STATUS based on result

**/
EFI_STATUS EFIAPI NvramSmiEntry(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
){
    EFI_STATUS Status;

    InitAmiSmmLib (ImageHandle, SystemTable);
    ASSERT (pSmst != NULL);
    Status = pSmst->SmiHandlerRegister(NvramSmmCommunicationHandler, &gAmiNvramSmmCommunicationGuid, &VarSmiHandle);
    ASSERT_EFI_ERROR (Status);

    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
