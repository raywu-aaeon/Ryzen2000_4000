//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  @brief AMI barcode base protocol definition
  
  The protocol is used to render bar code image
**/

#ifndef __AMI_BARCODE_BASE_PROTOCOL_H__
#define __AMI_BARCODE_BASE_PROTOCOL_H__

#include <Protocol/GraphicsOutput.h>

#define AMI_BARCODE_BASE_PROTOCOL_GUID \
{ 0x593ed818, 0x1ad7, 0x4f04, { 0x94, 0x5e, 0x4d, 0x6d, 0xe, 0x79, 0x42, 0xaf } }

typedef struct _AMI_BARCODE_BASE_PROTOCOL AMI_BARCODE_BASE_PROTOCOL;

//
// Error codes

#define AMI_BARCODE_SUCCESS         0

// The barcode type is not registered
#define AMI_BARCODE_NOT_REGISTERED  ENCODE_ERROR (1)

// EFI_GRAPHICS_OUTPUT_PROTOCOL not found
#define AMI_BARCODE_GOP_NOT_FOUND   ENCODE_ERROR (2)

// The image is too wide for the screen
#define AMI_BARCODE_OFFSCREEN_X     ENCODE_ERROR (3)

// The image is too tall for the screen
#define AMI_BARCODE_OFFSCREEN_Y     ENCODE_ERROR (4)

// The image is wider than requested
#define AMI_BARCODE_TOO_WIDE        ENCODE_ERROR (5)

// The image is taller than requested
#define AMI_BARCODE_TOO_TALL        ENCODE_ERROR (6)

// ConOut query mode error
#define AMI_BARCODE_CONOUT_ERROR    ENCODE_ERROR (7)

// Barcode encoder error
#define AMI_BARCODE_ENCODER_ERROR   ENCODE_ERROR (8)

typedef enum {
    AmiBarcode_Code128, // Included in the driver release package
    AmiBarcode_GS1_128,
    AmiBarcode_EAN,
    AmiBarcode_UPC,
    AmiBarcode_QR,
    AmiBarcode_PDF417,
    AmiBarcode_PostNet,
    AmiBarcode_AztecCode,
    AmiBarcode_Max
} AMI_BARCODE_TYPE;


///
/// Barcode image display parameter structure
///
typedef struct {
    ///
    /// INPUT
    ///  A switch indicating whether the generated barcode is displayed on the screen
    ///
    BOOLEAN DisplayBarcode;
    
    ///
    /// INPUT|OUTPUT
    ///  Input:
    ///   The zero based column (PosX) and row (PosY) of the barcode text. If
    ///   DisplayText is FALSE, these fields are the coordinates of the left top
    ///   corner of the image to be displayed on the screen. These coordinates should
    ///   not exceed the current console mode screen dimensions (80x25, 100x31, etc.),
    ///   otherwise the error is returned.
    ///  Output:
    ///   On return these fields contain the pixel coordinates of the left upper
    ///   corner of the barcode image.
    /// NOTE
    ///  These fields are ignored when DisplayBarcode is FALSE.
    ///
    UINT32  PosX;
    UINT32  PosY;
    
    ///
    /// INPUT
    ///  Barcode image magnification scale: 1 for 100%, 2 for 200%, etc.
    ///  The value of 1 will generate the smallest possible image of the
    ///  barcode based on the current video output parameters such as
    ///  video resolution and the dimensions of the output device.
    ///
    UINT32  Scale;
    
    ///
    /// INPUT|OUTPUT
    ///  Input:
    ///   Barcode image dimensions, in pixels. This input data is OPTIONAL.
    ///   If the input is zero, then the barcode image width and/or height is calculated
    ///   based on the encoded Data size and the Scale.
    ///   If either Width or Height is not zero, the driver will attempt to use them
    ///   considering the barcode specification requirements.
    ///  Output:
    ///   When input is zero, on return these fields are updated with the calculated data.
    ///
    UINT32  Width;
    UINT32  Height;
    
    ///
    /// OUTPUT
    ///   If DisplayBarcode is TRUE:
    ///     This field contains the pointer to the image which was replaced by the barcode.
    ///     The caller can use this image along with the returned PosX, PosY, Width, and Height
    ///     to restore the part of the screen which was painted over with the barcode.
    ///     Note: It is the caller's responsibility to call EFI_BOOT_SERVICES.FreePool() on
    ///     BarcodeBltBuffer when the caller no longer required the contents of BarcodeBltBuffer.
    ///   If DisplayBarcode is FALSE:
    ///     This field contains the pointer to Blt buffer with the generated barcode.
    ///     Note: It is the caller's responsibility to call EFI_BOOT_SERVICES.FreePool() on
    ///     BarcodeBltBuffer when the caller no longer required the contents of BarcodeBltBuffer.
    ///
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL   *BarcodeBltBuffer;
    
    ///
    /// INPUT
    ///  This field specifies whether or not the text is displayed along with the barcode image.
    ///  If this parameter is TRUE, additional fields are used to specify the text alignment.
    ///  The text will be shown using console output with the default system font and its size.
    /// NOTE
    ///  This field is ignored when DisplayBarcode is FALSE.
    ///
    BOOLEAN DisplayText;
    
    ///
    /// INPUT
    ///  When TRUE, the barcode image is displayed above the text. When FALSE, the barcode is
    ///  displayed below the text.
    /// NOTE
    ///  This field is ignored when DisplayBarcode is FALSE or DisplayText is FALSE.
    ///
    BOOLEAN ImageAboveText;
} AMI_BARCODE_DISPLAY_DATA;


/**
  Produce barcode and optionally draw it on the screen.

  @param[in]      This                  The protocol instance pointer.
  @param[in]      BarcodeType           One of the registered barcode types.
  @param[in]      Data                  The alphanumeric data to be encoded.
  @param[in,out]  BarcodeDisplayData    The barcode image display parameters.
  @param[out]     ExtendedStatus        The details of the status of the operation.

**/
typedef
EFI_STATUS
(EFIAPI *AMI_BARCODE_BASE_PROTOCOL_BARCODE_PRODUCER) (
    IN AMI_BARCODE_BASE_PROTOCOL    *This,
    IN AMI_BARCODE_TYPE             BarcodeType,
    IN CHAR16                       *Data,
    IN OUT AMI_BARCODE_DISPLAY_DATA *BarcodeDisplayData,
    OUT UINTN                       *ExtendedStatus
);

struct _AMI_BARCODE_BASE_PROTOCOL {
    AMI_BARCODE_BASE_PROTOCOL_BARCODE_PRODUCER BarcodeProducer;
};

extern EFI_GUID gAmiBarcodeBaseProtocolGuid;

#endif

