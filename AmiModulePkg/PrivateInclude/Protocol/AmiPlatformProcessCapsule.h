//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    AMI PlatformProcessCapsule protocol definition.
    
    The protocol is used to initiate processing of capsules at predefined point in the boot flow
 **/
#ifndef __AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL__H__
#define __AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL__H__

#define AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL_GUID \
    { 0xEFE61723, 0xF2EE, 0x4B99, { 0x8E, 0xE7, 0x57, 0x2E, 0x34, 0xA3, 0xE4, 0x29 } }

typedef struct _AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL_PROCESS_CAPSULE_LIST) (
    IN AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL *This,             //! pointer to AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL instance
    IN VOID                                  *Data OPTIONAL     //! pointer to extra data for further improvement
 );

struct _AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL {
    AMI_PLATFORM_PROCESS_CAPSULE_PROTOCOL_PROCESS_CAPSULE_LIST   ProcessCapsuleList;
};

extern EFI_GUID gAmiPlatformProcessCapsuleProtocolGuid;

#endif
