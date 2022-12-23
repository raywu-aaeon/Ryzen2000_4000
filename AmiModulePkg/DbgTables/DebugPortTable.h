//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

#ifndef __DBGP_H__
#define __DBGP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <Acpi50.h>
#include <PiDxe.h>
#include <Setup.h>

#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>

#include <Protocol/AcpiSupport.h>
#include <Protocol/ConsoleControl.h>
#include <AmiProtocol.h>

#if ACPI_SUPPORT    
#include <AcpiOemElinks.h>
#endif

#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D) \
	(EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))

#define DEBUG_PORT_SIG	EFI_SIGNATURE_32('D', 'B', 'G', 'P')

#pragma pack(1)
//==============================================================
//               Debug Port Table (DBGP)
//==============================================================
//-----------------------------------------------------------------
typedef struct _DBG_PORT_TABLE
{
	ACPI_HDR	AcpiHeader;   //0..35
	UINT8		InterfaceType;
	UINT8		Reserved1[3];
	GAS_30		BaseAddress;
}DBG_PORT_TABLE;
#pragma pack()
//=============================================================

EFI_STATUS
EFIAPI
DebugPortTable2Dxe(
  VOID
  );

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
