//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CrbDsmAslDxe.c
    This file contains code for install SSDT for CRB DSM asl
    in the DXE stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiTable.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// The definition refer to AmiCompatibilityPkg. we do not include AmiCompatibilityPkg because of it will be removed.
#define CREATOR_ID_AMI 0x20494D41  //" IMA""AMI "(AMI) .
#define	CREATOR_REV	0x00000000

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function is the entry point for Test driver.
    This function initializes the Test in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
CrbDsmAslDxeEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_ACPI_TABLE_PROTOCOL	*AcpiTableProtocol;
    UINTN					SectionInstance = 0;

	Status = gBS->LocateProtocol (
					&gEfiAcpiTableProtocolGuid,
					NULL,
					&AcpiTableProtocol
					);
	ASSERT_EFI_ERROR(Status);

	 while (Status == EFI_SUCCESS && SectionInstance < 5) {
		EFI_ACPI_COMMON_HEADER	*Header = NULL;
		UINTN					Size = 0;

		Status = GetSectionFromFv (&gEfiCallerIdGuid, EFI_SECTION_RAW, SectionInstance, &Header, &Size);
		if (!EFI_ERROR (Status)) {
			EFI_ACPI_DESCRIPTION_HEADER		*DescriptionHeader = (EFI_ACPI_DESCRIPTION_HEADER*)Header;

			// find SSDT - CRBDSM.
			if (DescriptionHeader->Signature == SIGNATURE_32('S', 'S', 'D', 'T')
				&& DescriptionHeader->OemTableId == SIGNATURE_64 ('C', 'R', 'B', 'D', 'S', 'M', 0, 0)) {
				UINTN	TableKey = 0;

				// Let's use PCD instead later. most module still use the token definition.
				// PcdGet32 (PcdAcpiDefaultOemRevision);
				// PcdGet32 (PcdAcpiDefaultCreatorId);
				// PcdGet32 (PcdAcpiDefaultCreatorRevision);
				DescriptionHeader->CreatorId = CREATOR_ID_AMI;
				DescriptionHeader->CreatorRevision = CREATOR_REV;

				Status = AcpiTableProtocol->InstallAcpiTable(
												AcpiTableProtocol,
												DescriptionHeader,
												DescriptionHeader->Length,
												&TableKey
												);
				ASSERT_EFI_ERROR(Status);
			}
		}
		SectionInstance++; // the AML section should within 5 instance.
	}

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
