//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        GNB_IOMMU.asl
//
// Description: GNb asl code for IOMMU
//
// Notes:
//
//<AMI_FHDR_END>
//*************************************************************************
		Name(_HID, EISAID("PNP0C02"))	// System board resources device node ID
		Name(_UID, 0x15)		// Unique ID. 
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadOnly, ASL_GNB_IOMMU_BASE_ADDRESS, ASL_GNB_IOMMU_LENGTH) //Non-writeable (Default Values) Report IOMMU
		}		// End of ResourceTemplate
		)		// end of CRS
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************