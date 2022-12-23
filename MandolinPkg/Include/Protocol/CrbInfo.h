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

#ifndef _AMI_PROTOCOL_CRBINFO_H_
#define _AMI_PROTOCOL_CRBINFO_H_

#define AMI_EFI_CRBINFO_H_PROTOCOL_GUID \
	{ 0xe516acef, 0xfa3c, 0x4068, { 0x8c, 0xe4, 0x88, 0x8d, 0x62, 0xb0, 0xe4, 0x97 } }
	// {E516ACEF-FA3C-4068-8CE4-888D62B0E497}


typedef struct _AMI_EFI_CRBINFO_PROTOCOL  AMI_EFI_CRBINFO_PROTOCOL;

#pragma pack(1)

typedef
UINT8
(EFIAPI *AMI_EFI_CRBINFO_GET_CHIPSET_VENDOR_NO)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

typedef
UINT32
(EFIAPI *AMI_EFI_CRBINFO_GET_CPU_ID)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  	*This
);

typedef
UINT32
(EFIAPI *AMI_EFI_CRBINFO_GET_NB_PCI_ID)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

typedef
UINT32
(EFIAPI *AMI_EFI_CRBINFO_GET_SB_PCI_ID)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

typedef
CHAR8*
(EFIAPI *AMI_EFI_CRBINFO_GET_PROJECT_ID)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

typedef
UINT16
(EFIAPI *AMI_EFI_CRBINFO_GET_BIOS_REVISION)(
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

struct _AMI_EFI_CRBINFO_PROTOCOL {
  AMI_EFI_CRBINFO_GET_CHIPSET_VENDOR_NO GetChipsetVendorNo;
  AMI_EFI_CRBINFO_GET_CPU_ID GetCpuId;
  AMI_EFI_CRBINFO_GET_NB_PCI_ID GetNorthBridgePciId;
  AMI_EFI_CRBINFO_GET_SB_PCI_ID GetSouthBridgePciId;
  AMI_EFI_CRBINFO_GET_PROJECT_ID GetProjectId;
  AMI_EFI_CRBINFO_GET_BIOS_REVISION GetBiosRevision;
};

extern EFI_GUID   gAmiEfiCrbInfoProtocolGuid;

#pragma pack()

#endif /* _AMI_PROTOCOL_CRBINFO_H_ */

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
