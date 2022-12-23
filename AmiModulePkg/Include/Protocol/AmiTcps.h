//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************
/** @file
    AMI TCPS protocol definition
**/
#ifndef __AMI_TCPS_PROTOCOL__H__
#define __AMI_TCPS_PROTOCOL__H__

#include <Library/NetLib.h>

typedef enum {
  AmiTcpsMethodGet,
  AmiTcpsMethodMax
} AMI_TCPS_METHOD;

typedef struct _AMI_TCPS_PROTOCOL AMI_TCPS_PROTOCOL;

///
/// AMI_TCPS_REQUEST_DATA
///
typedef struct {
  ///
  /// The Tcp method (e.g. GET, POST) for this Tcp Request.
  ///
  AMI_TCPS_METHOD               Method;
  ///
  /// The URI of a remote host. From the information in this field
  ///
  CHAR16                        *Url;
  UINT16                        Port;
} AMI_TCPS_REQUEST_DATA;

///
/// AMI_TCPS_RESPONSE_DATA
///
typedef struct {
  ///
  /// Response status code returned by the remote host.
  ///
  NET_FRAGMENT          NetFrag;
} AMI_TCPS_RESPONSE_DATA;

///
/// AMI_TCPS_MESSAGE
///
typedef struct {
  ///
  /// TCPS message data.
  ///
  union {
    ///
    /// When the token is used to send a request, Request is a pointer to storage that
    /// contains such data as URL and Tcps method
    ///
	AMI_TCPS_REQUEST_DATA       *Request;
    ///
    /// When used to await a response, Response points to storage containing response
    /// status code.
    ///
	AMI_TCPS_RESPONSE_DATA      *Response;
  } Data;
  ///
  /// Length in bytes of the TCPS body.
  ///
  UINTN                         BodyLength;
  ///
  /// Body associated with the TCPS request or response.
  ///
  VOID                          *Body;
  ///
  /// Temp Certs buffer associated with the TCPS request or response.
  ///
} AMI_TCPS_MESSAGE;

///
/// AMI_TCPS_TOKEN
///
typedef struct {
  ///
  /// This Event will be signaled after the Status field is updated by the EFI TCPS
  /// Protocol driver. The type of Event must be EFI_NOTIFY_SIGNAL. The Task Priority
  /// Level (TPL) of Event must be lower than or equal to TPL_CALLBACK.
  ///
  EFI_EVENT                     Event;
  ///
  /// Status will be set to one of the following value if the request is
  /// successfully sent or if an unexpected error occurs:
  ///   EFI_SUCCESS:      The TCP request was successfully sent to the remote host.
  ///   EFI_ABORTED:      The TCP request was cancelled by the caller and removed from
  ///                     the transmit queue.
  ///   EFI_TIMEOUT:      The TCP request timed out before reaching the remote host.
  ///   EFI_DEVICE_ERROR: An unexpected system or network error occurred.
  ///
  EFI_STATUS                    Status;
  ///
  /// Pointer to storage containing TCPS message data.
  ///
  AMI_TCPS_MESSAGE              *Message;
} AMI_TCPS_TOKEN;

typedef
EFI_STATUS
(EFIAPI *AMI_TCPS_REQUEST) (
  IN  AMI_TCPS_PROTOCOL         *This,
  IN  AMI_TCPS_TOKEN            *Token
);

struct _AMI_TCPS_PROTOCOL {
	AMI_TCPS_REQUEST            Request;
};

extern EFI_GUID gAmiTcpsProtocolGuid;
extern EFI_GUID gAmiTcpsServiceBindingProtocolGuid;

#endif
