//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file ZpRomLayout.c
    This file contains code for ZpRomLayout base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/AmiRomLayoutLib.h>
#include <AmdSoc.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/HobLib.h>

#include <Token.h>
// AMI Compatibility header

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------


/**
  The routine is to adjust BB from ROM to memory

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/
BOOLEAN
ZpPeiProcessFvBeforePublishing(
  IN CONST EFI_PEI_SERVICES **PeiServices,
  IN OUT AMI_ROM_AREA *Area,
  IN UINT32 FvType
  )
{
    SOC_ID_STRUCT    SocId;

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;
    if (!SocHardwareIdentificationCheck (&SocId))
    {
        // Only Family 17 CPUs need adjust BB from ROM to memory
        if ((Area->Address == FV_BB_BASE)
        		&& ( (Area->Attributes & AMI_ROM_AREA_FV_PEI) == AMI_ROM_AREA_FV_PEI && (Area->Attributes & AMI_ROM_AREA_FV_PEI_SHADOW) == 0))
        {
	        Area->Address = HIGH_MEMORY_REGION_BB_BASE;
        }
#if defined(SMBIOS_DMIEDIT_DATA_LOC) && (SMBIOS_DMIEDIT_DATA_LOC == 0)
    	// if RomLayoutPei looking for FV-DXE at gAmiReadyToLoadDxeCorePpiGuid. that meaning system is entering DXE.
    	//  Let's change FV_BB info to ROM.
    	if ((Area->Attributes & (AMI_ROM_AREA_FV_DXE)) == AMI_ROM_AREA_FV_DXE) {
    		EFI_HOB_FIRMWARE_VOLUME			*FvHob = (EFI_HOB_FIRMWARE_VOLUME *)GetFirstHob (EFI_HOB_TYPE_FV);

			while (FvHob != NULL) {
				if (FvHob->BaseAddress == HIGH_MEMORY_REGION_BB_BASE) {
					FvHob->BaseAddress = FV_BB_BASE;
				}
				FvHob = (EFI_HOB_FIRMWARE_VOLUME *)GetNextHob (EFI_HOB_TYPE_FV, (VOID *)((UINTN)FvHob + FvHob->Header.HobLength));
			}
    	}
#endif
    }
    return TRUE;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
