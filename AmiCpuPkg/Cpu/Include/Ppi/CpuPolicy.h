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

/** @file CPUPolicy.h
    Contains PEI cpu policy Structure definition.

**/


#ifndef FILE_PEI_CPUINIT_POLICY_PPI_H_
#define FILE_PEI_CPUINIT_POLICY_PPI_H_

// {F824CCBB-D8E0-4522-8AA8-65F04B463DB5}
#define AMI_PEI_CPUINIT_POLICY_PPI_GUID \
	{0xf824ccbb, 0xd8e0, 0x4522, 0x8a, 0xa8, 0x65, 0xf0, 0x4b, 0x46, 0x3d, 0xb5}

//EFI_GUID_STRING(AMI_PEI_CPUINIT_POLICY_PPI_GUID, "AMICPUPeiInitPolicy", "AMI Generic CPU PEI Init Policy");


typedef struct _AMI_PEI_CPUINIT_POLICY_PPI	AMI_PEI_CPUINIT_POLICY_PPI;

#pragma pack (1)
typedef struct _AMI_PEI_CPUINIT_POLICY_PPI {
  UINTN                   Flag;
} AMI_PEI_CPUINIT_POLICY_PPI;
#pragma pack()

extern EFI_GUID gAmdAfterCpuPeiPpiGuid;

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
