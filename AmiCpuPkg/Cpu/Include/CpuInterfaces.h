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

/** @file Cpuinterfaces.h
    Cpu interfaces definition

**/

#ifndef _CPU_INTERFACES_H_
#define _CPU_INTERFACES_H_

#ifdef __cplusplus
extern "C" {
#endif


#define CPU_S3_RESUME_VARIABLE L"CpuS3Resume"


extern EFI_GUID gCpuS3ResumeGuid;

#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINT64  Base;       //32-bit only needs UINT32, but this structure is shared between
                        //DXE and PEI.
} DESCRIPTOR_TABLE;

typedef struct {
    UINT64          SmmBaseVal [FixedPcdGet32 (PcdCpuMaxCores)];
} CPU_S3_RESUME2;

typedef struct {
    UINT32 Msr;
    UINT64 Value;
} MTRR_VALUE;

typedef struct {
	DESCRIPTOR_TABLE	Idt;
    CPU_S3_RESUME2      SmmBase;
    MTRR_VALUE          MtrrValue[NUM_OF_MTRR_SAVED];
} CPU_S3_RESUME;
#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
