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


/** @file CpuCspLib.h
    This file declares/defines data types, functions, and
    constants that are used in the CPU module's CSP library. 

**/


#ifndef __CPULIB_H__
#define __CPULIB_H__

#include <Efi.h>
#include <Pei.h>
#include "AmiHobs.h"
#include "Smm.h"
#include "Cpu.h"
// Add this header for conditional use of SMM_MINOR_VER 
#include <Token.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
typedef struct 
{
	UINT64	ES[2];
	UINT64	CS[2];
	UINT64	SS[2];
	UINT64	DS[2];
	UINT64	FS[2];
	UINT64	GS[2];
	UINT64	GDTR[2];
	UINT64	LDTR[2];
	UINT64	IDTR[2];
	UINT64	TR[2];
	UINT64	Reserved1[4];
	UINT32	IOTrap;
	UINT32	LocalSmiStatus;
	UINT8	IORestart;
	UINT8	AutoHALTRestart;
	UINT8	Reserved3[6];
	UINT64	EFER;
	UINT8	Reserved9[36];
	UINT32	SMMRevId;
	UINT32	SMBASE;
	UINT8	Reserved4[68];
	UINT64	CR4;
	UINT64	CR3;
	UINT64	CR0;
	UINT64	DR7;
	UINT64	DR6;
	UINT64	RFLAGS;
	UINT64	RIP;
	UINT64	R15;
	UINT64	R14;
	UINT64	R13;
	UINT64	R12;
	UINT64	R11;
	UINT64	R10;
	UINT64	R9;
	UINT64	R8;
	UINT64	RDI;
	UINT64	RSI;
	UINT64	RBP;
	UINT64	RSP;
	UINT64	RBX;
	UINT64	RDX;
	UINT64	RCX;
	UINT64	RAX;
} AMD_64_SAVE_STATE;

#pragma pack()

BOOLEAN IsItBsp(
    VOID );

UINT64 ReadMsr (
    UINT32 Msr );

void WriteMsr (
    UINT32 Msr, 
    UINT64 Value );

void ReadWriteMsr (
    UINT32 Msr, 
    UINT64 Value, 
    UINT64 Mask );

void CPULib_CpuID (
    UINT32 CpuIDIndex, 
    UINT32 * RegEAX, 
    UINT32 * RegEBX, 
    UINT32 * RegECX,
    UINT32 * RegEDX );

UINT8 NumCpuCores (
    VOID );

BOOLEAN IsHtEnabled (
    VOID );

BOOLEAN IsDualNode (
    VOID );

BOOLEAN isXDSupported (
    CPU_FEATURES *Features );

BOOLEAN isLimitCpuidSupported (
    VOID );

BOOLEAN IsMachineCheckSupported ( 
    CPU_FEATURES *Features );

VOID DisableCacheInCR0 (
    VOID );

VOID EnableCacheInCR0 (
    VOID );

VOID CPULib_DisableInterrupt (
    VOID );

VOID CPULib_EnableInterrupt (
    VOID );

BOOLEAN	CPULib_GetInterruptState (
    VOID );

UINT16 GetCsSegment (
    VOID );

UINT64 ReadRtdsc (
    VOID );

VOID WaitForever (
    VOID );

VOID HltCpu (
    VOID );

VOID WaitForSemaphore (
    volatile VOID* );

VOID WaitUntilZero8 (
    volatile VOID* );

VOID WaitUntilZero32 (
    volatile VOID* );

UINT16 GetCsSegment (
    VOID );

VOID SwitchBspProgramReg(
    IN UINT8 Cpu, 
    IN volatile VOID *Context );

VOID *InitMemPageMapping(
	IN EFI_PEI_SERVICES **PeiServices );

VOID EnableLongMode (
    VOID *PageTable, 
    VOID *Function, 
    VOID *Parameter1 );

VOID CPU_GetSaveState (
	UINT8						*SmmBase, 
	EFI_SMI_CPU_SAVE_STATE		*SstSaveState );

VOID CPU_RestoreSaveState (
	UINT8						*SmmBase, 
	EFI_SMI_CPU_SAVE_STATE		*SstSaveState );

BOOLEAN IsSwSmiTrigger (
    UINT8 *SmmBase,
    UINT16 SwSmiPort );

UINT32 SmmGetBaseSaveBufferSize();
VOID SmmSetupDefaultHandler(IN VOID *SmmBaseSaveBuffer, IN SMM_HOB *SmmHob);
VOID SmmRemoveDefaultHandler(IN VOID *SmmBaseSaveBuffer);
VOID SmmBaseChangeOnCpu(IN VOID *SmmBase);

VOID    CPULib_Pause();
// PAM-related declarations

#pragma pack (push, 1)
typedef struct {
    UINT8 ClkModEn;     //> 0 if Clk Mod En.
} CPU_LIB_SMM_SAVE_RESTORE_DATA;
#pragma pack (pop)

VOID CpuLibSmmSaveCpuState(IN OUT CPU_LIB_SMM_SAVE_RESTORE_DATA*);
VOID CpuLibSmmRestoreCpuState(IN CPU_LIB_SMM_SAVE_RESTORE_DATA*);

EFI_STATUS CPULib_SmmReadSaveState(
    UINT8       *SmmBase, 
    UINT8		*SstSaveState,
    BOOLEAN     UseSstSaveState,
    IN UINT8    Width,
    IN UINT32	Register,
    OUT VOID    *Buffer
);

EFI_STATUS CpuLib_SmmReadSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        OUT VOID    *Buffer
);

EFI_STATUS CPULib_SmmWriteSaveState(
    UINT8       *SmmBase, 
    UINT8		*SstSaveState,
    BOOLEAN     UseSstSaveState,
    IN UINT8    Width,
    IN UINT32	Register,
    OUT CONST VOID    *Buffer
);

EFI_STATUS CpuLib_SmmWriteSaveStateFxSave(
        IN UINT8    *FxSave,
        IN UINT8    Width,
        IN UINT32   Register,
        OUT VOID    *Buffer
);


#define NUM_COMMON_MTRRS 36
typedef UINT32 MTRR_INDEX[NUM_COMMON_MTRRS]; 
typedef UINT64 MTRR_SAVED_VALUE[NUM_COMMON_MTRRS]; 

#pragma pack (push, 1)
typedef struct 
{
    MTRR_INDEX          MsrIndex;
	MTRR_SAVED_VALUE    ValueBuffer;    
    UINT8               Size;
    BOOLEAN             BSPisCopied;
} MTRR_COPY_CONTEXT;
#pragma pack (pop)

// This function is essential for SMM label 36 or later
VOID CpuSmmMemoryInit (
    IN OUT SMM_HOB *gSmmHob );

VOID InitMtrrCopyContext (
    IN OUT  MTRR_COPY_CONTEXT *Mcc );

VOID CpuReadMsrs (
    IN     MTRR_INDEX           MsrIndex,
	IN OUT MTRR_SAVED_VALUE     ValueBuffer,    
    IN     UINT16               Size );

VOID CpuWriteMsrs (
    IN MTRR_INDEX           MsrIndex,
	IN MTRR_SAVED_VALUE     ValueBuffer,    
    IN UINT16               Size );

EFI_STATUS CopyBspMtrrsToAllRunningApMtrrs (
    VOID *MtrrCopyContext );

EFI_STATUS SynchronizeMtrrs (
    IN EFI_BOOT_SERVICES *gBS );

VOID EnableMachineCheck ( VOID );

VOID CPULib_LockByteInc ( 
    UINT8* ptr );

VOID CPULib_LockByteDec ( 
    UINT8* ptr );

VOID CPULib_LoadGdt ( 
    VOID *ptr );

VOID CPULib_SaveGdt ( 
    VOID *ptr );

VOID CPULib_LoadIdt ( 
    VOID *ptr );

VOID CPULib_SaveIdt ( 
    VOID *ptr );

UINT32 MemRead32 ( 
    UINT32 *Address );

VOID MemReadWrite32 ( 
    UINT32 *Address, 
    UINT32 Value, 
    UINT32 Mask );

UINT32 AmdCpuCount (
    VOID );

UINT32 AmdNodeCount (
    VOID );

BOOLEAN IsFamily15h(
    VOID 
);

UINT32
GetCpuRawId(
    VOID
);
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
