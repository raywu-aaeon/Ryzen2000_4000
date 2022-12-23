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

/** @file CpuPei.h
    Cpu Pei header file

**/

#ifndef __CPU_PEI_H__
#define __CPU_PEI_H__

#ifndef PEI_COMPILE
#define PEI_COMPILE	//This is used in Cpu.h.
#endif

#include <Efi.h>
//#include <Ppi\MicrocodeLoader.h>
#include <Hob.h>
#include <AmiHobs.h>
#include "Cpu.h"
#include "CpuInterfaces.h"
#include <Token.h>
#include <CpuSetupData.h>


#ifdef __cplusplus
extern "C" {
#endif

#pragma pack (push, 1)
typedef struct {
	EFI_BOOT_MODE			BootMode;
//	LOAD_MICRO_CODE			LoadMicroCode;
	CPU_FEATURES            *CpuFeatures;
	CPUINFO					*Cpuinfo;
	EFI_PHYSICAL_ADDRESS	TopOfMemory;
	CPU_S3_RESUME			*CpuS3Resume;
	CPU_SETUP_DATA          *CpuSetupData;
	BOOLEAN					IsSetupDataValid;
	UINT8					NumCpusDisabled;
    EFI_PEI_SERVICES 		**PeiServices;
    volatile UINT8          Semaphore;
} PEI_AP_DATA;
#pragma pack (pop)

VOID ProgramS3ResumeMtrrs(MTRR_VALUE *MtrrValues, BOOLEAN IsPspEnabled);


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
