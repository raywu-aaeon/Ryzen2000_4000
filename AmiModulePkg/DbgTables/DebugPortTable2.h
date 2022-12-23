//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

#ifndef __DBG2_H__
#define __DBG2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <Acpi50.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/AcpiSupport.h>
#include <Protocol/ConsoleControl.h>
#include <AmiProtocol.h>

#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D) \
    (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))

//
// Signature for Debug port 2
//
#define DBG2_SIG	EFI_SIGNATURE_32('D', 'B', 'G', '2')

//
// ACPI DBG2 - Debug Device Name Space String
//
#define DBG2_DEV_INFO_DEFAULT_NAME_SPACE	"."

//
// ACPI DBG2 - Debug Device Information Structure - Length of AddressSize[]
//
#define ADDRESS_SIZE_LENGTH 4
//
//Debug port types and sub-types
//
//Searial-------------------------------------------------------------------------
#define DBG2_TYPE_SERIAL                                                0x8000
#define DBG2_SUBTYPE_SERIAL_FULL_16550                                  0x0
#define DBG2_SUBTYPE_SERIAL_16550_SUBSET_COMPATIBLE_WITH_MS_DBGP_SPEC   0x1
//1394----------------------------------------------------------------------------
#define DBG2_TYPE_1394                                                  0x8001
#define DBG2_SUBTYPE_1394_STANDARD                                      0x0
//USB-----------------------------------------------------------------------------
#define DBG2_TYPE_USB                                         0x8002
#define DBG2_SUBTYPE_USB_XHCI                                 0x0
#define DBG2_SUBTYPE_USB_EHCI                                 0x1
//NET-----------------------------------------------------------------------------
#define DBG2_TYPE_NET                                         0x8003

#pragma pack(1)

//==============================================================
//               Debug Port Table 2(DBG2)
//==============================================================
//-----------------------------------------------------------------
//
// Debug Device Information structure
//
typedef struct {
  UINT8     Revision;
  UINT16    Length;
  UINT8     NumberOfGenericAddressRegisters;
  UINT16    NameSpaceStringLength;
  UINT16    NameSpaceStringOffset;
  UINT16    OemDataLength;
  UINT16    OemDataOffset;
  UINT16    PortType;
  UINT16    PortSubtype;
  UINT8     Reserved[2];
  UINT16    BaseAddressRegisterOffset;
  UINT16    AddressSizeOffset;
} DBG_DEV_INFO_STRUCT;

//
// Debug Port 2 Table definition.
//
typedef struct _DBG_PORT_2_TABLE
{
    ACPI_HDR    AcpiHeader;   //0..35
    UINT32      OffsetDbgDeviceInfo;
    UINT32      NumberDbgDeviceInfo;
}DBG_PORT_2_TABLE;

#pragma pack()
//=============================================================

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
