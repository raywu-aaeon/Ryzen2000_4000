//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  @brief AMI SMM Communication Mailbox Header File.

  The file contains definitions of the AMI SMM Communication Mailbox data structures,
  as well as API to access the mailbox.
  SMM Communication Mailbox is used by OS applications to access SMM Communication buffer.
**/

#ifndef __AMI_SMM_COMMUNICATION_MAILBOX__H__
#define __AMI_SMM_COMMUNICATION_MAILBOX__H__

#pragma pack(1)

typedef struct {
    UINT32 Size; ///< Requested buffer size
    UINT32 Flags;
} AMI_SMM_COMM_BUFFER_LOCK_PARAMS;

typedef struct {
    UINT32 SwSmiNumber;
    UINT32 Reserved;
    UINT64 Rax;
    UINT64 Rbx;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rsi;
    UINT64 Rdi; 
} AMI_SMM_COMM_BUFFER_X86_REGISTERS;

/// Defines format of the SMM Communication Mailbox
typedef struct {
    // Mailbox header
    UINT64 Revision; ///< Revision of this data structure
    UINT64 PhysicalAddress; ///< Physical address of the SMM Communication buffer
    UINT32 Status; ///< Status of the last SMI call
    UINT32 Token; ///< Token that identifies SMI caller
    // End of the mailbox header

    // The following fields are available starting with revision 2
    // Mailbox function specific data
    union {
        AMI_SMM_COMM_BUFFER_LOCK_PARAMS Lock; ///< Lock function parameters
        AMI_SMM_COMM_BUFFER_X86_REGISTERS Regs; ///< x86 registers
    } Data;
} AMI_SMM_COMMUNICATION_MAILBOX;

#pragma pack()

#define AMI_SMM_COMMUNICATION_MAILBOX_REVISION 2

#define AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_LOCK 0xC0000001
#define AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_UNLOCK 0xC0000002
#define AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_DISPATCH 0xC0000003
#define AMI_SMM_COMMUNICATION_MAILBOX_COMMAND_X86_REGISTERS 0xC0000004

// Flags that are passed as an input to the Lock function
#define AMI_SMM_COMMUNICATION_MAILBOX_LOCK_FLAG_FORCE_LOCK 1

// Flags returned by the Lock function
#define AMI_SMM_COMMUNICATION_MAILBOX_X86_REG_SUPPORTED 1

// AmiPcdSmmCommInterfaceProperties bits
#define AMI_SMM_COMMUNICATION_PROPERTY_NEW_STYLE_INTERFACE_SUPPORT 1
#define AMI_SMM_COMMUNICATION_PROPERTY_X86_REG_SUPPORT 2

#endif
