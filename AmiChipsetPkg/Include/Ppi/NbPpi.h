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

/** @file NbPpi.h
    This header file contains the PPI definition for the NB.

*/

#ifndef FILE_PEI_NB_PPI_H_
#define FILE_PEI_NB_PPI_H_

// {9CE4D938-9C87-41d0-9E55-34923FAF8B4F}
#define AMI_PEI_NBINIT_POLICY_PPI_GUID \
 {0x9ce4d938, 0x9c87, 0x41d0, 0x9e, 0x55, 0x34, 0x92, 0x3f, 0xaf, 0x8b, 0x4f}

// {E813E116-C099-4D21-9c34-A552D5E9A5D0}
#define AMI_PEI_MRC_DEFAULT_GUID \
 {0xe813e116, 0xc099, 0x4d21, 0x9c, 0x34, 0xa5, 0x52, 0xd5, 0xe9, 0xa5, 0xd0}

// {71A8917B-0891-4E27-8A73-A9B334840393}
#define AMI_PEI_BEFORE_MRC_GUID \
 {0x71a8917b, 0x891, 0x4e27, 0x8a, 0x73, 0xa9, 0xb3, 0x34, 0x84, 0x3, 0x93}

// {64C96700-6B4C-480C-A3E1-B8BDE8F602B2}
#define AMI_PEI_AFTER_MRC_GUID \
 {0x64c96700, 0x6b4c, 0x480c, 0xa3, 0xe1, 0xb8, 0xbd, 0xe8, 0xf6, 0x2, 0xb2}

// {633194BE-1697-11E1-B5F0-2CB24824019B}
#define AMI_PEI_END_OF_MRC_GUID \
 {0x633194be, 0x1697, 0x11e1, 0xb5, 0xf0, 0x2c, 0xb2, 0x48, 0x24, 0x01, 0x9b}

// {9F58E424-B96B-45A5-ADDC-D2FE394A99D9}
#define AMI_PEI_END_MEMORY_DETECT_GUID \
 {0x9f58e424, 0xb96b, 0x45a5, 0xad, 0xdc, 0xd2, 0xfe, 0x39, 0x4a, 0x99, 0xd9}

typedef struct _AMI_PEI_NBINIT_POLICY_PPI     AMI_PEI_NBINIT_POLICY_PPI;

#pragma pack (push, 1)
struct _AMI_PEI_NBINIT_POLICY_PPI {
  UINTN                   unFlag;
};

#pragma pack (pop)

extern EFI_GUID gAmiPeiNbInitPolicyGuid;
extern EFI_GUID gAmiPeiMrcDefaultGuid;
extern EFI_GUID gAmiPeiBeforeMrcGuid;
extern EFI_GUID gAmiPeiAfterMrcGuid;
extern EFI_GUID gAmiPeiEndOfMemDetectGuid;

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
