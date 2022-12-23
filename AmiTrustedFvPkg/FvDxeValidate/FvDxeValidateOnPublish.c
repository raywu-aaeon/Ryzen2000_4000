//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  ROM Layout PEIM hook to PublishFv
 Verify signed DXE FVs (PEI after memory, DXE2 & BDS FVs)
 Locate FvDxeSig FFS in FV_DATA FV, if found - verify the signature of signed FV ranges
 by comparing decrypted hash against a hash value constructed using the ROM map layout
 and stored inside the FV_DATA FvDxeSig Certificate header
 Copy all signed FV Dxe ranges to RAM before performing hash calculation.
 Install a PPI to notify TCG module the good DXE Hash is ready to be extended to PCR
**/
#include <AmiCspLib.h>
#include <AmiHobs.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Ppi/AmiFvDxeValidate.h>

#include <Library/DebugLib.h>

/**
Determine if the Rom Area attributes indicate the FV is measured

@param[in]   Attributes

@retval      TRUE if FV is Measured
**/
BOOLEAN
IsFvMeasured (
  UINT32 Attributes
){
    return ( 
           ((Attributes & AMI_ROM_AREA_MEASURED) == AMI_ROM_AREA_MEASURED)
           ||
           // or predict measured ranges: one of DXE/DXE2/BDS || PEI_AFTER_MEM && not FV_BB
           ((Attributes & AMI_ROM_AREA_FV_ACCESS_ATTRIBUTES) != 0
            &&
            // not FV_BB
            (Attributes & (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)) != (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)
           )
   );
}
/**
 The function will install a FvDxePublishPpi  PPI.

 @param PeiServices Pointer to the Pointer to the Pei Services Table
 @param Area Pointer to the RomArea being checked

 @retval EFI_SUCCESS If FV_MAIN is successfully verified.
*/
EFI_STATUS
InstallFvDxePublishPpi(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN AMI_ROM_AREA *Area
) {
    EFI_STATUS              Status;
    EFI_PEI_PPI_DESCRIPTOR *pPpiDesc;
    AMI_PUBLISH_FV_DXE_PPI *PublishFvDxePpi;

    //--------------------------------------------------------------------------
    //   Allocate dynamic placeholder for FvDxePublish PPI
    //--------------------------------------------------------------------------
    Status = (**PeiServices).AllocatePool(PeiServices,
                                        sizeof(AMI_PUBLISH_FV_DXE_PPI),
                                        (VOID**)&PublishFvDxePpi
                                        );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    CopyMem(&PublishFvDxePpi->Area, Area, sizeof(AMI_ROM_AREA));

    //--------------------------------------------------------------------------
    //   Allocate dynamic placeholder for Descriptor PPI
    //--------------------------------------------------------------------------
    pPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *)AllocateZeroPool(sizeof(EFI_PEI_PPI_DESCRIPTOR));
    ASSERT (pPpiDesc != NULL);    
    if(pPpiDesc == NULL) return EFI_OUT_OF_RESOURCES;
    
    pPpiDesc->Ppi = (VOID*)PublishFvDxePpi;
    pPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    pPpiDesc->Guid = &gAmiPublishFvDxeValidatePpiGuid;
    // Install PPI for current ROM_AREA range
    Status = (*PeiServices)->InstallPpi (PeiServices, pPpiDesc);
    DEBUG ((DEBUG_INFO, "==>     PublishFvDxePpi %X: Area %8X-%X\n", pPpiDesc->Ppi, (UINT32)((AMI_PUBLISH_FV_DXE_PPI*)(pPpiDesc->Ppi))->Area.Address, (UINT32)((AMI_PUBLISH_FV_DXE_PPI*)(pPpiDesc->Ppi))->Area.Size));
    ASSERT_EFI_ERROR(Status);

    return Status;
}

/**
 * Porting hook to support OEM specific FV validation or additional Fv processing. 
 * The Area that is passed in is allowed to be modified by the callee functions.
 *
 * @param PeiServices Pointer to the Pointer to the Pei Services Table
 * @param Area Pointer to the RomArea being checked
 * @param FvType The attributes of the RomArea that is being checked
 *
 * @retval TRUE Validation of the FV passed, continue processing it.
 * @retval FALSE Validation of the FV failed, don't continue processing it.
 */
BOOLEAN BeforeFvDxePublish(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN OUT AMI_ROM_AREA *Area,
    IN UINT32 FvType)
{
    EFI_BOOT_MODE BootMode;
    EFI_STATUS Status;
    RECOVERY_IMAGE_HOB *RecoveryHob = NULL;
    EFI_HOB_GENERIC_HEADER *Hobs = NULL;
    AMI_ROM_AREA *Area1;

    Status = (*PeiServices)->GetBootMode( PeiServices, &BootMode );
    DEBUG ((DEBUG_INFO, "==>TDXE FV %8X-%X, Attr %X, BootMode %X\n", (UINT32)Area->Address, Area->Size, Area->Attributes, BootMode));

    if(!IsFvMeasured(Area->Attributes))
        return TRUE;

    if(EFI_ERROR(Status)
//     || BootMode == BOOT_ON_S3_RESUME
    )
        return  TRUE;

    // Allow Recovery FV to be published. It's been already validated in secure recovery path
    if (BootMode == BOOT_IN_RECOVERY_MODE || 
       (BootMode == BOOT_ON_FLASH_UPDATE && PcdGetBool(PcdUseNewImageOnFlashUpdate)))
    {
        Status = (*PeiServices)->GetHobList(PeiServices, (VOID**)&Hobs);
        if(!EFI_ERROR(Status)) {
            RecoveryHob = GetNextGuidHob(&gAmiRecoveryImageHobGuid, (VOID*)Hobs);
            if(RecoveryHob != NULL) {
                if(RecoveryHob->Status == EFI_SUCCESS && RecoveryHob->Address != 0) {
                    DEBUG ((DEBUG_INFO, "Recovery FV Addr %8X\n", RecoveryHob->Address + Area->Offset));
                    // Recovery passed and Recovery Hob has been created
                    if(RecoveryHob->Address+Area->Offset == Area->Address)
                        return TRUE;
                }
            }
        }
    }
    // Update RomArea with Address in RAM. Must be invoked for FV after mem
    if(PcdGetBool(AmiPcdTdxeShadowFvBeforePublish) &&
            (Area->Attributes & AMI_ROM_AREA_FV_PEI_SHADOW) == AMI_ROM_AREA_FV_PEI_SHADOW) {
        for(Area1 = AmiGetFirstRomArea(); Area1 != NULL; Area1 = AmiGetNextRomArea(Area1)) {
            if(Area1->Offset != Area->Offset )
                continue;
            DEBUG ((DEBUG_INFO, "==>TDXE FvReloc %8X->%X\n", (UINT32)Area1->Address, (UINT32)Area->Address));
            Area1->Address = Area->Address;
            break;
        }
    }
    // Install notification PPI in order to execute FvDxeValidatePpi->FvDxeValidate function
    InstallFvDxePublishPpi(PeiServices, Area);
    // Set attrib to avoid forced Recovery ...yet
    Area->Attributes |= AMI_ROM_AREA_NON_CRITICAL;
    DEBUG((DEBUG_INFO, "<==Exit FV %8X: %r\n",(UINT32)Area->Address, EFI_NOT_READY));
    return FALSE;
}
