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

#ifndef _AMI_PSP_H_
#define _AMI_PSP_H_

// Dxe signature file
#define DXE_SIG_FFS_GUID \
	{0xDD9D5D5E,0xA5DD,0x4402,{0x9F,0x7C,0xF0,0x52,0xFC,0xDC,0xEA,0x36}}
    
extern EFI_GUID gDxeSigFfsGuid;

// Dxe signature file section
#define DXE_SIG_SECTION_GUID \
	{0x5AAEBF51,0x1414,0x47e8,{0xB6,0x62,0x2D,0x20,0x9D,0xCA,0xDF,0xE7}}
    
extern EFI_GUID gDxeSigSectionGuid;


extern EFI_GUID gAmiPspS3SmmCommunicationGuid;
extern EFI_GUID gAmiPspFtpmHobGuid;
extern EFI_GUID gAmiPspFtpmSmmCommunicationGuid;
extern EFI_GUID gAmiPspFvBbFirmwareVolumeGuid;

#endif

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