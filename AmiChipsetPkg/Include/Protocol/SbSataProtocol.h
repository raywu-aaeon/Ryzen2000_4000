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

/** @file SbSataProtocol.h
    South Bridge SATA Protocol header.

*/

#ifndef  _SB_SATA_PROTOCOL_H
#define  _SB_SATA_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#define  SB_HDD_POLICY_PROTOCOL_GUID \
  {0x75CA7C9D, 0x502E, 0x468a, 0x9A, 0xAF, 0x7F, 0x2A, 0x29, 0xE6, 0xDB, 0xCF}

#pragma pack(1)

typedef EFI_STATUS (*GENERATE_PORT_NUMBER)(
    IN    UINT8     DeviceNumber,
    IN    UINT8     FunctionNumber,
    IN    UINT32    IdeChannel,
    IN    UINT32    IdeDevice,
    OUT   UINT32    *PortNumber
);

typedef struct{
    GENERATE_PORT_NUMBER	  GeneratePortNumber;
}SB_HDD_POLICY_PROTOCOL;

#pragma pack()

extern EFI_GUID	gAmiSbHddPolicyProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif 

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
