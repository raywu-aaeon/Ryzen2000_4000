//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  @brief AMI SMM Communication Protocol definition
**/
#ifndef __AMI_SMM_COMMUNICATION_PROTOCOL__H__
#define __AMI_SMM_COMMUNICATION_PROTOCOL__H__

#include <AmiSmmCommunicationMailbox.h>

#define AMI_SMM_COMMUNICATION_PROTOCOL_GUID\
    { 0xca4148b9, 0x47f9, 0x4f50, { 0x93, 0xc0, 0xdb, 0x13, 0x6b, 0xfd, 0x9d, 0x9 } }

#define AMI_SMM_COMMUNICATION_PROTOCOL_REVISION 1

typedef struct _AMI_SMM_COMMUNICATION_PROTOCOL AMI_SMM_COMMUNICATION_PROTOCOL;

/**
    Returns address and size of the SMM Communication buffer
    
    @param[out] Address address of the SMM Communication buffer
    @param[out] Size    size of the SMM Communication buffer
**/
typedef EFI_STATUS (EFIAPI * AMI_SMM_COMMUNICATION_GET_BUFFER)(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    OUT UINT64 *Address, OUT UINT32 *Size
);

/**
    Returns register block data structure from the SMM Communication mailbox
    
    @param[in]  SwSmiNumber      SW SMI number of the handler that uses the interface
    @param[out] RegisterBlock    Copy of the AMI_SMM_COMM_BUFFER_X86_REGISTERS 
                                 data structure from the SMM Communication mailbox
**/
typedef EFI_STATUS (EFIAPI * AMI_SMM_COMMUNICATION_GET_REGISTERS)(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    IN UINT32 SwSmiNumber,
    OUT AMI_SMM_COMM_BUFFER_X86_REGISTERS *RegisterBlock
);

/**
    Updates register block data structure in the SMM Communication mailbox

    @param[in]  SwSmiNumber      SW SMI number of the handler that uses the interface
    @param[in]  RegisterBlock    register block data structure to copy 
                                 to the SMM Communication mailbox
**/
typedef EFI_STATUS (EFIAPI * AMI_SMM_COMMUNICATION_SET_REGISTERS)(
    IN AMI_SMM_COMMUNICATION_PROTOCOL *This,
    IN UINT32 SwSmiNumber,
    IN AMI_SMM_COMM_BUFFER_X86_REGISTERS *RegisterBlock
);

struct _AMI_SMM_COMMUNICATION_PROTOCOL{
    /// Version of the protocol interface structure
    UINT64 Revision;
    /// Returns address and size of the SMM Communication buffer
    AMI_SMM_COMMUNICATION_GET_BUFFER GetCommunicationBuffer;
    /// Returns register block data structure from the SMM Communication mailbox 
    AMI_SMM_COMMUNICATION_GET_REGISTERS GetRegisterBlock;
    /// Updates register block data structure in the SMM Communication mailbox
    AMI_SMM_COMMUNICATION_SET_REGISTERS SetRegisterBlock;
};

extern EFI_GUID gAmiSmmCommunicationProtocolGuid;

#endif
