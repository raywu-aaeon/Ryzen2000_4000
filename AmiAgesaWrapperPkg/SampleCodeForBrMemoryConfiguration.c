//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <Uefi.h>
#include <PiPei.h>
#include <AGESA.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include "OptionMemory.h"
#include "Ppi/AmdMemPpi.h"
#include "Mem/AmdMemCzPei/AmdMemCzPei.h"
#include "PlatformMemoryConfiguration.h"
#include <Library/AmdSocBaseLib.h>


//
// Identify all static PPI produced by this module
//


//
// Define the list of all PPI produced by this module
//


//-----------PORTING REQUIRED-----------------
// !!!!!! PLEASE FILL IN THE VALUE WITH YOUR BOARD SETTING.!!!!!
PSO_ENTRY ROMDATA OemPlatformMemoryConfigurationForAm4[] = {
        DRAM_TECHNOLOGY(ANY_SOCKET, DDR4_TECHNOLOGY),
        NUMBER_OF_CHANNELS_SUPPORTED (ANY_SOCKET, 2),
        NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, CHANNEL_A, DIMM_SLOTS_PER_CHNL),
        NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, CHANNEL_B, DIMM_SLOTS_PER_CHNL),
        MOTHER_BOARD_LAYERS (LAYERS_6),
        // Signal routing for AMD reference board
        MEMCLK_DIS_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        MEMCLK_DIS_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        CKE_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08),
        CKE_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08),
        ODT_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x04, 0x02, 0x08),
        ODT_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x04, 0x02, 0x08),
        CS_TRI_MAP (ANY_SOCKET, CHANNEL_A, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        CS_TRI_MAP (ANY_SOCKET, CHANNEL_B, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00),
        PSO_END
};
//-----------PORTING REQUIRED-----------------


/**
 *  SampleCodePeiEntry
 *
 *  Description:
 *    This function will install BR Memory configuration table.
 *
 *  Parameters:
 *    @param[in]        **PeiServices
 *                      FileHandle
 *
 *
 *    @retval         VOID
 *
 **/
EFI_STATUS
EFIAPI
SampleCodePeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS                                  Status = EFI_SUCCESS;
    EFI_PEI_PPI_DESCRIPTOR                      *MemoryConfigurationPtr;
    AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI    *AmdAgesaMemPlatformConfigurationPpiPtr;
    SOC_ID_STRUCT                               SocId;

    DEBUG ((DEBUG_INFO, "    SampleCodePeiEntry Entry\n"));

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (!SocHardwareIdentificationCheck(&SocId))
    {
        return EFI_UNSUPPORTED;
    }

    Status = (*PeiServices)->AllocatePool (
                           PeiServices,
                           sizeof (EFI_PEI_PPI_DESCRIPTOR),
                           &MemoryConfigurationPtr
                           );
	if (EFI_SUCCESS != Status) {
		DEBUG ((DEBUG_ERROR, "Unable to allocate space for MemoryConfigurationPtr data \n"));
        return Status;
    }

    Status = (*PeiServices)->AllocatePool (
                           PeiServices,
                           sizeof (AMD_AGESA_MEM_PLATFORM_CONFIGURATION_PPI),
                           &AmdAgesaMemPlatformConfigurationPpiPtr
                           );
	if (EFI_SUCCESS != Status) {
		DEBUG ((DEBUG_ERROR, "Unable to allocate space for AmdAgesaMemPlatformConfigurationPpiPtr data \n"));
        return Status;
    }

    AmdAgesaMemPlatformConfigurationPpiPtr->PlatformMemoryConfiguration = OemPlatformMemoryConfigurationForAm4;

    MemoryConfigurationPtr->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    MemoryConfigurationPtr->Guid = &gAmdMemoryPlatformConfigurationPpiGuid;
    MemoryConfigurationPtr->Ppi = AmdAgesaMemPlatformConfigurationPpiPtr;

    Status = (**PeiServices).InstallPpi (PeiServices, MemoryConfigurationPtr);

    DEBUG ((DEBUG_INFO, "    SampleCodePeiEntry Exit\n"));

    return  Status;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
