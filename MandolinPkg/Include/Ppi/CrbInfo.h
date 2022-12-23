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

//*************************************************************************
/** @file CrbInfo.h
    This header file contains the CrbInfo.h definition.

**/
//*************************************************************************

#ifndef _AMI_PPI_CRBINFO_H_
#define _AMI_PPI_CRBINFO_H_

#define AMI_PEI_CRBINFO_PPI_GUID \
	{ 0x1b1924c3, 0x6321, 0x484f, { 0x83, 0xef, 0x88, 0x94, 0xb2, 0x1d, 0xe2, 0x58 } }
	// {1B1924C3-6321-484f-83EF-8894B21DE258}

typedef struct _AMI_PEI_CRBINFO_PPI  AMI_PEI_CRBINFO_PPI;

#pragma pack(1)

typedef
UINT8
(EFIAPI *AMI_PEI_CRBINFO_GET_CHIPSET_VENDOR_NO)(
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

typedef
UINT32
(EFIAPI *AMI_PEI_CRBINFO_GET_CPU_ID)(
  IN  CONST AMI_PEI_CRBINFO_PPI  	*This
);

typedef
UINT32
(EFIAPI *AMI_PEI_CRBINFO_GET_NB_PCI_ID)(
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

typedef
UINT32
(EFIAPI *AMI_PEI_CRBINFO_GET_SB_PCI_ID)(
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

typedef
CHAR8*
(EFIAPI *AMI_PEI_CRBINFO_GET_PROJECT_ID)(
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

typedef
UINT16
(EFIAPI *AMI_PEI_CRBINFO_GET_BIOS_REVISION)(
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

struct _AMI_PEI_CRBINFO_PPI {
  AMI_PEI_CRBINFO_GET_CHIPSET_VENDOR_NO GetChipsetVendorNo;
  AMI_PEI_CRBINFO_GET_CPU_ID GetCpuId;
  AMI_PEI_CRBINFO_GET_NB_PCI_ID GetNorthBridgePciId;
  AMI_PEI_CRBINFO_GET_SB_PCI_ID GetSouthBridgePciId;
  AMI_PEI_CRBINFO_GET_PROJECT_ID GetProjectId;
  AMI_PEI_CRBINFO_GET_BIOS_REVISION GetBiosRevision;
};

extern EFI_GUID   gAmiPeiCrbInfoPpiGuid;

#pragma pack()

#endif /* _AMI_PPI_CRBINFO_H_ */

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
