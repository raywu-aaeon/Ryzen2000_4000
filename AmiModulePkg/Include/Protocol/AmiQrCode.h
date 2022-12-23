//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AmiQrCode.h
  @brief AMI QR Code protocol definition
**/

#include <Protocol/GraphicsOutput.h>

#ifndef __AMI_QR_CODE_PROTOCOL_H__
#define __AMI_QR_CODE_PROTOCOL_H__

#define AMI_QR_CODE_PROTOCOL_GUID \
    { 0x86C98398, 0x959F, 0x4B57, { 0x8E, 0x00, 0xB3, 0xD7, 0x91, 0x30, 0x42, 0xA7 }}

#define AMI_QR_CASE_SENSITIVE_OFF       FALSE
#define AMI_QR_CASE_SENSITIVE_ON        TRUE
#define AMI_QR_CODE_MIN_VERSION         1
#define AMI_QR_CODE_MAX_VERSION         40
#define AMI_QR_CODE_MIN_SCALE_FACTOR    1
#define AMI_QR_CODE_MAX_SCALE_FACTOR    10

// Level of error correction.
typedef enum {
    AmiQrEcLevelL = 0, ///< lowest
    AmiQrEcLevelM,
    AmiQrEcLevelQ,
    AmiQrEcLevelH      ///< highest
} AMI_QR_ERROR_CORRECTION_LEVEL;

// Encoding mode.
typedef enum {
    AmiQrModeNum = 0,   ///< Numeric mode
    AmiQrModeAn,        ///< Alphabet-numeric mode
    AmiQrMode8,         ///< 8-bit data mode
    AmiQrModeKanji,     ///< Kanji (shift-jis) mode
    AmiQrModeStructure, ///< Internal use only
    AmiQrModeEci,       ///< ECI mode
    AmiQrModeFnc1First, ///< FNC1, first position
    AmiQrModeFnc1Second,///< FNC1, second position
    AmiQrModeEnd = -1   ///< Terminator (NUL character). Internal use only
} AMI_QR_ENCODE_MODE;

/**
    Sets QR Code attributes.

    @param[in] Version         Version of the QR Code. If 0, the library chooses the minimum
                               version for the given input string.
    @param[in] Level           Error correction level.
    @param[in] EncodeMode      Encode Mode, need to tell the Library how encoding needs to
                               be done
    @param[in] Color           Color of QR code output,
    @param[in] CaseSensitive   Case-sensitive(1) or not(0).
    @param[in] ScaleFactor     Used to enlarge the QR Code data.

    @retval EFI_SUCCESS            QR Code attributes are updated successfully.
    @retval EFI_INVALID_PARAMETER  Invalid input data

    @note
    1. All parameters should be valid
    2. Supported encoding modes - 8 bit (binary) and Kanji
**/
typedef
EFI_STATUS
(EFIAPI *AMI_SET_QR_CODE_ATTRIBUTES) (
    IN UINT32                         Version,
    IN AMI_QR_ERROR_CORRECTION_LEVEL  Level,
    IN AMI_QR_ENCODE_MODE             EncodeMode,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Color,
    IN BOOLEAN                        CaseSensitive,
    IN UINT8                          ScaleFactor
);

/**
    Generates QR code and returns BLT data of QR code.

    @param[in]      String       String to be converted into QR code
    @param[out]     BltBuffer    The BLT Output Buffer. A pointer to buffer of
                                 EFI_GRAPHICS_OUTPUT_BLT_PIXEL and is allocated
                                 by this service and it is the caller's
                                 responsibility to free this buffer when the
                                 caller no longer requires the buffer's contents.
    @param[out]     QrCodeWidth  QRCode BLT buffer for image in square
                                 dimensions(Width = Height) of pixels unit.This
                                 can be used to display QRcode on the screen.

    @retval EFI_SUCCESS             QR Code generated successfully
    @retval EFI_INVALID_PARAMETER   Input parameter is invalid
    @retval EFI_OUT_OF_RESOURCES    Buffer allocation failed
**/
typedef
EFI_STATUS
(EFIAPI *AMI_GENERATE_QR_BUFFER)  (
    IN     CHAR8                              *String,
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL         **BltBuffer,
    OUT    UINTN                              *Qrcodewidth
);

typedef struct {
    AMI_SET_QR_CODE_ATTRIBUTES  SetQrCodeAttributes;
    AMI_GENERATE_QR_BUFFER      GenerateQrBuffer;
} AMI_QR_CODE_PROTOCOL;

extern EFI_GUID gAmiQrCodeProtocolGuid;
#endif
