//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  @brief AMI barcode type registration interface
  
  The header defines AmiBarcodeTypeRegistration protocols that is used 
  by drivers supporting specific barcode type to register their rendering API 
  with the top level bar code driver publishing AmiBarcodeBase protocol.
**/

#ifndef __AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL_H__
#define __AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL_H__

#include <Protocol/AmiBarcodeBase.h>

#define AMI_BARCODE_TYPE_REGISTRATION_GUID \
        { 0xdcdae0b8, 0xc136, 0x4a2a, { 0x97, 0x8e, 0x84, 0x2, 0x4a, 0xa6, 0xd5, 0x55 } }

typedef struct _AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL;

// Format of data passed to the BarcodeBase from barcode type drivers during registration
//
typedef struct {
    AMI_BARCODE_TYPE BarcodeType;
    AMI_BARCODE_BASE_PROTOCOL_BARCODE_PRODUCER BarcodeTypeProducer;
} AMI_BARCODE_TYPE_REGISTRATION_DATA;

// Registration function prototype
//
typedef
EFI_STATUS (EFIAPI *AMI_BARCODE_TYPE_REGISTRATION) (
    IN AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL *This,
    IN AMI_BARCODE_TYPE_REGISTRATION_DATA *BarcodeRegistrationData
 );

// Barcode type registration protocol
//
struct _AMI_BARCODE_TYPE_REGISTRATION_PROTOCOL {
    AMI_BARCODE_TYPE_REGISTRATION   RegisterBarcodeType;
};

extern EFI_GUID gAmiBarcodeTypeRegistrationProtocolGuid;

#endif  //  __AMI_BARCODE_BASE_H__
