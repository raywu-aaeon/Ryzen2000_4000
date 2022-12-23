//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    AMI ProcessCapsule protocol definition.
    
	The protocol is used to introduce support for a new capsule type.
	There is no standard GUID for the protocol.
	Each instance of the protocol has GUID of the capsule it processes.
	
	The protocol is published by the module that knows how to process certain type of capsule.
	Generic capsule processing code uses the protocol to perform capsule-type specific processing.
 **/
#ifndef __AMI_PROCESS_CAPSULE_PROTOCOL__H__
#define __AMI_PROCESS_CAPSULE_PROTOCOL__H__

typedef struct _AMI_PROCESS_CAPSULE_PROTOCOL AMI_PROCESS_CAPSULE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *AMI_PROCESS_CAPSULE_PROTOCOL_PROCESS_CAPSULE) (
    IN AMI_PROCESS_CAPSULE_PROTOCOL *This,             //! pointer to AMI_PROCESS_CAPSULE_PROTOCOL instance
    IN VOID                         *Image,            //! pointer to the Capsule Image, including Capsule header
    IN UINTN                        ImageSize          //! Size of the capsule including header
 );

struct _AMI_PROCESS_CAPSULE_PROTOCOL {
    AMI_PROCESS_CAPSULE_PROTOCOL_PROCESS_CAPSULE   ProcessCapsule;
};

#endif
