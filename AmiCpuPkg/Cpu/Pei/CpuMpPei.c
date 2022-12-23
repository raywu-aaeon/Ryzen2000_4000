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

/** @file CpuMpPei.c
    Cpu MP routines

**/

#include <Efi.h>
#include <Token.h>
#include <AmiLib.h>
#include "Cpu.h"
#include "CpuCspLib.h"
#include <Pei.h>
#include <Ppi/Stall.h>
#include <AmiPeiLib.h>
#include <Library/DebugLib.h>

VOID MpStart();
VOID MpRestart();
VOID SwitchStacks(UINT8, VOID *);
VOID JmpToMpStart();
// extern UINT32 JmpAddress;
extern UINTN JmpAddress;
extern UINT32 JmpToMpStartSize;

typedef struct {
    VOID    (*Function)(UINT8 Cpu, VOID *Context);  //If not zero, CPU thread is executing this function.
    VOID    *Context;           //Cpu context.
    VOID    *Stack;
    UINT32  Id;
    UINT8   Halted;             //Signal to halt CPU.
} CPU_CONTROL;

typedef struct {
    UINT32  Id;
    UINT32  CpuNum;
} CPU_INFO_INIT;

typedef struct {
    UINT64  Gdt;
    UINT32  GdtPadding; // GDT64 takes 10 bytes
    volatile UINT32  NumAps;
    UINT64  ApGlobalData;
    UINT32  PageTable;
    UINT32  Tom;
    volatile UINT32 EnteredHoldLoop;
    UINT32  EightByteAlign;     // padding for GDT, makes 8 byte align
} ZERO_DATA;

typedef struct {
    ZERO_DATA   Zdata;
    UINT64      Gdtr;
    UINT64      Sel_0;
    UINT64      Sel_8;
    UINT64      Sel_10;
    UINT64      Sel_18;
    UINT64      Sel_20;
    UINT64      Sel_28;
    UINT64      Sel_30;
    UINT64      Sel_38;
} ZERO_DATAx;

typedef struct {
    CPU_CONTROL *CpuControl;
    VOID        *HaltLoopEntry;
    VOID        *ReleaseCpu;
    UINT32  Idt;
    UINT8       CpuSync;
    UINT8       Bsp;
    UINT8       NumCpus;
    UINT8       RunningAps;
    UINT8       HaltedCpus;
} AP_GLOBAL_DATA;

#define WAIT_FOR_CPU_COUNT 400

#define ASSERT_ERROR_CPU(Status) ASSERT_PEI_ERROR(PeiServices, Status)
#define STALL_CPU(time) PeiStall->Stall(PeiServices,PeiStall,time)
#define ALLOCATE_MEMORY_CPU(ptr_of_Address, Size) \
        (**PeiServices).AllocatePool(PeiServices, Size, ptr_of_Address)
#define ALLOCATE_PAGES_CPU(ptr_of_Address, Pages) \
        (**PeiServices).AllocatePages(PeiServices, EfiBootServicesData, Pages, ptr_of_Address)
#define FREE_MEMORY_CPU(ptr)

/**
    This function is a wrapper for CopyBspMtrrsToAllRunningApMtrrs
    for executing on APs.  This is needed because in PEI the
    EFI_MP_SERVICES_PROTOCOL is not available.

        
    @param Cpu - Current CPU number
    @param Context - Function Argument Structure

         
    @retval VOID

**/

VOID
WrapCopyBspMtrrsToAllRunningApMtrrs(
  IN    UINT8   Cpu,
  IN    VOID    *Context
)
{
    CopyBspMtrrsToAllRunningApMtrrs (Context);
}

/**
    Copies BSP's MTRRs to all runnint APs' MTRRs

        
    @param PeiServices 
    @param MpData - (void*)AP_GLOBAL_DATA

         
    @retval VOID

    @note  This function is called implicitly with StartAllAps and
          RestartAp.

**/

EFI_STATUS
MpSynchronizeMtrrs(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    VOID                *MpData
)
{
    MTRR_COPY_CONTEXT   MtrrCopyContext;
    EFI_STATUS          Status;
    InitMtrrCopyContext(&MtrrCopyContext);

    // Save MTRR values of the BSP to buffer
    DEBUG((DEBUG_INFO, "MpSynchronizeMtrrs: Copy BSP to(%X)\n",
           &MtrrCopyContext.ValueBuffer));
    Status = CopyBspMtrrsToAllRunningApMtrrs ((VOID*)&MtrrCopyContext);

    // Write MTRR values from buffer to the APs' MTRRs
    DEBUG((DEBUG_INFO, "MpSynchronizeMtrrs: Write APs from(%X)\n",
           &MtrrCopyContext.ValueBuffer));

    ExecuteFunctionOnRunningCpus (MpData, FALSE, TRUE,
     WrapCopyBspMtrrsToAllRunningApMtrrs, (VOID*)&MtrrCopyContext);

    return EFI_SUCCESS;
}

/**
    Start one or more AP with INIT-SIPI-SIPI.

        
        (PEI Only) IN EFI_PEI_SERVICES      **PeiServices
        (PEI Only) IN EFI_PEI_STALL_PPI     *PeiStall
    @param ApGlobalData 
    @param AllCpus - Start one or all CPUS.
    @param ApicId - This Used if AllCpus == FALSE.

         
    @retval UINT8 Number of CPUs started.
**/

UINT8
StartCpus(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    EFI_PEI_STALL_PPI   *PeiStall,
  IN    AP_GLOBAL_DATA      *ApGlobalData,
  IN    BOOLEAN             AllCpus,
  IN    UINT8               ApicId  // If only 1 cpu
)
{
    ZERO_DATAx               ZeroDataBackUp;
    VOID        *Below1MbStartupBackup;
    UINT8                   NumCpusStarted;
    EFI_STATUS              Status;
    volatile UINT8          ExpectedApCount = AmdCpuCount() - 1;

    Status = ALLOCATE_MEMORY_CPU ((VOID**)&Below1MbStartupBackup, JmpToMpStartSize);
    ASSERT_ERROR_CPU (Status);

    // Back up the original contents at MP_ZERO_DATA_ADDRESS and copy ZERO_DATAx structure
    // to this address. This structure will accessed by APs.
    MemCpy (&ZeroDataBackUp, (VOID*)MP_ZERO_DATA_ADDRESS, sizeof (ZERO_DATAx));

    CPULib_SaveGdt (MP_ZERO_DATA_ADDRESS);  // sgdt fword ptr [0];
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps = 0; // Initialize Count.
//    Agd64 ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT32)ApGlobalData;
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT64)ApGlobalData;

    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->Tom = (UINT32)ReadMsr (AMD_MSR_TOP_MEM);

#if ((MP_JUMP_FUNCTION_ADDRESS & ~0xFF000) != 0)
#error Token MP_JUMP_FUNCTION_ADDRESS must be 4k aligned and less than 1MB
#endif

    // Back up contents of MP_JUMP_FUNCTION_ADDRESS and copy JmpToMpStart()
    // to this address.  APs will begin execution at this address.
    MemCpy (Below1MbStartupBackup, (VOID*)MP_JUMP_FUNCTION_ADDRESS, JmpToMpStartSize);
    MemCpy ((VOID*)MP_JUMP_FUNCTION_ADDRESS, JmpToMpStart, JmpToMpStartSize);

    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop = 0; //Initialize Synchronizer
//#### Changes for GDT above 4G
/*
    *(UINT32*)((UINT32)&JmpAddress - (UINT32)JmpToMpStart + MP_JUMP_FUNCTION_ADDRESS)=
                         AllCpus ? (UINT32)MpStart : (UINT32)MpRestart;
*/                            
    *(UINTN*)((UINT32)&JmpAddress - (UINT32)JmpToMpStart + MP_JUMP_FUNCTION_ADDRESS)=
                        AllCpus ? (UINTN)MpStart : (UINTN)MpRestart;

//    DEBUG((DEBUG_INFO, PeiServices,"StartCpus: Send SIPI to start APs\n"));
    // Send SIPI to start APs
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_HIGH_REGISTER) =  AllCpus ? 0 : ApicId << 24;
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       INIT + LEVEL_ASSERT;

    Status = STALL_CPU(10000);

    ASSERT_ERROR_CPU(Status);

    *(UINT32*)(UINTN)(APIC_BASE +APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);
    STALL_CPU (200);

    *(UINT32*)(UINTN)(APIC_BASE +APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);

    if (AllCpus)
        while (((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps < ExpectedApCount);
    while (((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop < ExpectedApCount);

//Should not use TRACE After rising the trace level
//    DEBUG((DEBUG_INFO, "StartCpus: Get NumCpusStarted\n"));
    NumCpusStarted = AllCpus ? ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps : 1;

    // Restore original memory contents.
    // This is important for S3 resume.
    MemCpy ((VOID*)MP_ZERO_DATA_ADDRESS, &ZeroDataBackUp, sizeof (ZERO_DATAx));
    MemCpy ((VOID*)MP_JUMP_FUNCTION_ADDRESS, Below1MbStartupBackup, JmpToMpStartSize);

//    DEBUG((DEBUG_INFO, "StartCpus: FREE_MEMORY_CPU(%X)\n", Below1MbStartupBackup));
    FREE_MEMORY_CPU (Below1MbStartupBackup);

    return NumCpusStarted;
}

/**
    Start all APs and place in their holding loops for further
    work.

        
        (PEI Only) IN EFI_PEI_SERVICES      **PeiServices
        (PEI Only) IN EFI_PEI_STALL_PPI     *PeiStall
    @param ApGlobalData 

    @retval VOID

**/
VOID
StartAllAps(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    EFI_PEI_STALL_PPI   *PeiStall,
  OUT   VOID                **MpData
)
{
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    ApStack;
    UINTN                   i;
    UINTN                   j;
    UINT8                   NumCpus;
    UINT32                  BspId;
    UINT32                  Id;
    volatile AP_GLOBAL_DATA *ApGlobalData;
    CPU_INFO_INIT           *CpuInfoInit;
    CPU_CONTROL             *CpuControl;

    Status = ALLOCATE_MEMORY_CPU((VOID**)&ApGlobalData, sizeof(AP_GLOBAL_DATA));
    ASSERT_ERROR_CPU(Status);

    MemSet((VOID*)ApGlobalData, sizeof(AP_GLOBAL_DATA), 0);
    *MpData = (VOID*)ApGlobalData;

//    DEBUG((DEBUG_INFO, "StartAllAps> Before StartCpus()\n"));
    NumCpus = StartCpus (PeiServices, PeiStall, (AP_GLOBAL_DATA*)ApGlobalData, TRUE, 0);    // Valid, if only 1 cpu

    ++NumCpus;  //Count BSP
    ApGlobalData->NumCpus = NumCpus;
    DEBUG((DEBUG_INFO, "StartAllAps: NumCpus = %x.\n", NumCpus));
    DEBUG((DEBUG_INFO, "StartAllAps: AmdCpuCount() = %x.\n", AmdCpuCount()));

    //Ap gets control, switches to protected mode and is in a holding loop until
    //given a pointer to collect CPU info and give it a number.

    //
    //Get initial CPU Info to sort CPUs.
    //
    Status = ALLOCATE_MEMORY_CPU(&CpuInfoInit, NumCpus * sizeof(CPU_INFO_INIT));
    ASSERT_ERROR_CPU(Status);
    for (i = 0; i < NumCpus; ++i)
        CpuInfoInit[i].CpuNum = 0xFFFFFFFF;


    Status = ALLOCATE_MEMORY_CPU(&CpuControl, NumCpus * sizeof(CPU_CONTROL));
    ASSERT_ERROR_CPU(Status);
    MemSet(CpuControl, NumCpus * sizeof(CPU_CONTROL), 0);   //Initialize

    // Allocate Stack
    // Each AP gets a page of stack. (Only allocate for APs)
    if (NumCpus > 1)
    {
        Status = ALLOCATE_PAGES_CPU (&ApStack, (NumCpus - 1));
        ASSERT_ERROR_CPU (Status);
    }

    ApGlobalData->CpuControl = CpuControl;

    // Release CPUs and Collect Ids.
    ApGlobalData->CpuSync = NumCpus - 1;

    BspId = MemRead32((UINT32*)(APIC_BASE + APIC_ID_REGISTER)) >> 24;
    CpuInfoInit[0].Id = BspId;

    // Give CPU an address to collect ApicIDs.
    // This is used to sort CPUs by ApicId.
    for (i = 1; i < NumCpus; ++i)
    {
        ApGlobalData->ReleaseCpu = &CpuInfoInit[i];
        //Wait 'till AP clears number.
        WaitUntilZero32(&ApGlobalData->ReleaseCpu);
    }
    WaitUntilZero8(&ApGlobalData->CpuSync); //Wait 'till all APs are synced.

    // CPUs are held waiting for a Number and stack.


    // Sort CPUs by APIC ID. Fill in Cpu structure to give it a stack.
    // After a assigning a number, the CPU will be put in its main wait loop,
    // so it can execute functions.


    //Give lowest CPU ID, lowest CpuControl structure.
    Id = 0;
    for (i = 0; i < NumCpus; ++i)
    {
        UINTN   k = 0;
        UINT32  NearestId = 0xFFFFFFFF;
        for (j = 0; j < NumCpus; ++j)
        {
            if (CpuInfoInit[j].Id == Id)
            {
                k = j;
                break;
            }
            if (CpuInfoInit[j].Id > Id && CpuInfoInit[j].Id < NearestId)
            {
                k = j;
                NearestId = CpuInfoInit[j].Id;
            }
        }
        if (j == NumCpus)
            Id = NearestId;

        if (k == 0)
        { //BSP
            ApGlobalData->Bsp = (UINT8)i;
            CpuControl[i].Id = BspId;
            CpuControl[i].Function = (VOID(*)(UINT8, VOID*)) - 1;   // BSP is never halted.
        }
        else
        {   // AP
            ApStack += 4096;    // Start at top of stack or stack for next AP.
            CpuControl[i].Stack = (VOID*)ApStack;   // Store stack addresses for AP.
        }
        CpuInfoInit[k].CpuNum = (UINT8)i;   //Release Cpu
        ++Id;
    }

    // Synchronize all APs' MTRRs with BSP's MTRRs
    DEBUG((DEBUG_INFO, "StartAllAps: Before MpSynchronizeMtrrs()\n"));
    MpSynchronizeMtrrs (PeiServices, *MpData);
    DEBUG((DEBUG_INFO, "StartAllAps: After MpSynchronizeMtrrs()\n"));

    //Aps are waiting in a loop, for an address to jump to, or halted.

}

/**
    Start one AP with INIT-SIPI-SIPI.

        
        (PEI Only) IN EFI_PEI_SERVICES		**PeiServices
        (PEI Only) IN EFI_PEI_STALL_PPI	    *PeiStall
    @param ApGlobalData 
    @param AllCpus - Start one or all CPUS.
    @param ApicId - This Used if AllCpus == FALSE. 

         
    @retval UINT8 Number of CPUs started.
**/

UINT8
StartThisCpu(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    EFI_PEI_STALL_PPI   *PeiStall,
  IN    AP_GLOBAL_DATA      *ApGlobalData,
  IN    BOOLEAN             AllCpus,
  IN    UINT8               ApicId  // If only 1 cpu
)
{
	ZERO_DATAx				ZeroDataBackUp;
    VOID        *Below1MbStartupBackup;
	UINT8					NumCpusStarted;
	EFI_STATUS				Status;
	volatile UINT8          ExpectedApCount = AmdCpuCount() - 1;

    Status = ALLOCATE_MEMORY_CPU ((VOID**)&Below1MbStartupBackup, JmpToMpStartSize);
    ASSERT_ERROR_CPU (Status);

    // Back up the original contents at MP_ZERO_DATA_ADDRESS and copy ZERO_DATAx structure
    // to this address. This structure will accessed by APs.
    MemCpy (&ZeroDataBackUp, (VOID*)MP_ZERO_DATA_ADDRESS, sizeof (ZERO_DATAx));

    CPULib_SaveGdt (MP_ZERO_DATA_ADDRESS);  // sgdt fword ptr [0];
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps = 0; // Initialize Count.
//    Agd64	((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT32)ApGlobalData;
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT64)ApGlobalData;

    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->Tom = (UINT32)ReadMsr (AMD_MSR_TOP_MEM);

#if ((MP_JUMP_FUNCTION_ADDRESS & ~0xFF000) != 0)
#error Token MP_JUMP_FUNCTION_ADDRESS must be 4k aligned and less than 1MB
#endif

    // Back up contents of MP_JUMP_FUNCTION_ADDRESS and copy JmpToMpStart() 
    // to this address.  APs will begin execution at this address.
    MemCpy (Below1MbStartupBackup, (VOID*)MP_JUMP_FUNCTION_ADDRESS, JmpToMpStartSize);
    MemCpy ((VOID*)MP_JUMP_FUNCTION_ADDRESS, JmpToMpStart, JmpToMpStartSize);

	((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop = 0; //Initialize Synchronizer
//#### Changes for GDT above 4G
/* 
	*(UINT32*)((UINT32)&JmpAddress - (UINT32)JmpToMpStart
                           + MP_JUMP_FUNCTION_ADDRESS)=
		                    AllCpus ? (UINT32)MpStart : (UINT32)MpRestart;
*/
    *(UINTN*)((UINT32)&JmpAddress - (UINT32)JmpToMpStart + MP_JUMP_FUNCTION_ADDRESS) =
                        AllCpus ? (UINTN)MpStart : (UINTN)MpRestart;
//    DEBUG((DEBUG_INFO, "StartCpus: Send SIPI to start APs\n"));

    // Send SIPI to start APs
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_HIGH_REGISTER) = AllCpus ? 0 : ApicId << 24;
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       INIT + LEVEL_ASSERT;

	Status = STALL_CPU(10000);
	ASSERT_ERROR_CPU(Status);

    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);

	STALL_CPU(200);

    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);

    if (AllCpus)
      while (((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps < ExpectedApCount);

//	while ( ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop < ExpectedAPCount);

//Should not use TRACE After rising the trace level
//    DEBUG((DEBUG_INFO, "StartCpus: Get NumCpusStarted\n"));
	NumCpusStarted = AllCpus ? ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps : 1;

    // Restore original memory contents. 
    // This is important for S3 resume.
    MemCpy ((VOID*)MP_ZERO_DATA_ADDRESS, &ZeroDataBackUp, sizeof (ZERO_DATAx));
    MemCpy ((VOID*)MP_JUMP_FUNCTION_ADDRESS, Below1MbStartupBackup, JmpToMpStartSize);


//    DEBUG((DEBUG_INFO, "StartCpus: FREE_MEMORY_CPU(%X)\n", Below1MbStartupBackup));
    FREE_MEMORY_CPU (Below1MbStartupBackup);

	return NumCpusStarted;
}


/**
    After CPU has been halted, this restarts the CPU.

        
        (PEI Only) IN EFI_PEI_SERVICES      **PeiServices
        (PEI Only) IN EFI_PEI_STALL_PPI     *PeiStall
    @param MpData 
    @param Cpu - Cpu to restart.

    @retval VOID

**/

VOID
RestartAp(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    EFI_PEI_STALL_PPI   *PeiStall,
  IN    VOID                *MpData,
  IN    UINT8               Cpu
)
{
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    if (Cpu == ApGlobalData->Bsp || Cpu >= NumberCpus)
        return;
    if (!CpuControl[Cpu].Halted)
        return;

    ApGlobalData->ReleaseCpu = (VOID*)(UINTN)Cpu;   // Assign CPU number.

    StartThisCpu (PeiServices, PeiStall, (AP_GLOBAL_DATA*)ApGlobalData, FALSE,
     CpuControl[Cpu].Id);

    // Synchronize all APs' MTRRs with BSP's MTRRs
    DEBUG((DEBUG_INFO, "RestartAp: Before MpSynchronizeMtrrs()\n"));
    MpSynchronizeMtrrs (PeiServices, MpData);
    DEBUG((DEBUG_INFO, "RestartAp: After MpSynchronizeMtrrs()\n"));
}


/**
    Get number of CPUs, that has been found.

    @param MpData 

    @retval UINT8 Number of CPUs found.

**/

UINT8
GetNumCpus(
  IN    VOID    *MpData
)
{
    return ((AP_GLOBAL_DATA*)MpData)->NumCpus;
}

/**
    Each CPU will execute this function.

        
    @param MpData 
    @param ExecuteOnBsp - TRUE if BSP executes this function.
    @param Block - TRUE if BSP should wait on APs.
    @param Function - Function to call.
    @param Context - This value is passed to the function.

    @retval VOID

**/

VOID
ExecuteFunctionOnRunningCpus(
  IN    VOID    *MpData,
  IN    BOOLEAN ExecuteOnBsp,
  IN    BOOLEAN Block,
  IN    VOID    (*Function)(UINT8 Cpu, VOID *Context),
  IN    VOID    *Context
)
{
    UINT8   i;
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    WaitUntilZero8(&ApGlobalData->RunningAps);

    ApGlobalData->RunningAps = (NumberCpus - 1) - ApGlobalData->HaltedCpus;

    for (i = 0; i < NumberCpus; ++i)
    {
        if (i == ApGlobalData->Bsp)
            continue;
        if (CpuControl[i].Halted == TRUE)
            continue;
        CpuControl[i].Context = Context;    // Must set Context first.
        CpuControl[i].Function = Function;  // This releases the CPU.
    }

    if (ExecuteOnBsp)
        Function (ApGlobalData->Bsp, Context);

    if (Block)
        WaitUntilZero8 (&ApGlobalData->RunningAps);
}

/**
    This function provides a mechanism to execute a function
    onthe specific CPU

    @param MpData MP data structure
    @param Cpu Cpu to execute function.
    @param Block TRUE if BSP should wait on APs.
    @param Function Function to call.
    @param Context This value is passed to the function.

    @retval TRUE on successful completion, FALSE otherwise

**/

BOOLEAN
ExecuteFunctionOnCpu(
  IN VOID       *MpData,
  IN UINT8      Cpu,
  IN BOOLEAN    Block,
  IN VOID       (*Function)(UINT8 Cpu, VOID *Context),
  IN VOID       *Context
)
{
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;
    UINT8               *RunningAps = (UINT8*)&ApGlobalData->RunningAps;

    if (Cpu == ApGlobalData->Bsp)
    {
        Function (Cpu, Context);
        return TRUE;
    }

    if (Cpu >= NumberCpus)
        return FALSE;
    if (CpuControl[Cpu].Halted == TRUE)
        return FALSE;

    //Check if running, if not wait until finished.
    WaitUntilZero32(&CpuControl[Cpu].Function);

    CPULib_LockByteInc(RunningAps); // Increase umber of CPUs running.

    CpuControl[Cpu].Context = Context;      //Must set Context first.
    CpuControl[Cpu].Function = Function;    //This releases the CPU.

    if (Block)
        WaitUntilZero8 (RunningAps);

    return TRUE;
}

/**
    Halt all the APs.

        
    @param MpData 
    @param WaitUntilHalted - TRUE if BSP should wait on APs to halt.

    @retval VOID

**/

VOID
HaltAllAps(
  IN    VOID    *MpData,
  IN    BOOLEAN WaitUntilHalted
)
{
    UINT8   i;
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    for (i = 0; i < NumberCpus; ++i)
    {
        if (i == ApGlobalData->Bsp)
            continue;   // Can't halt BSP.
        CpuControl[i].Halted = TRUE;
    }

    if (WaitUntilHalted)
    {
        for(i = 0; i < NumberCpus; ++i)
        {
            if (i == ApGlobalData->Bsp)
                continue;   // BSP not halted.
            WaitUntilZero32 (&CpuControl[i].Function);
        }
    }
}

/**
    Halt the CPU.

        
    @param MpData 
    @param Cpu - Cpu to halt.
    @param WaitUntilHalted - TRUE if BSP should wait on APs to halt.

    @retval VOID

**/

VOID
HaltCpu(
  IN    VOID    *MpData,
  IN    UINT8   Cpu,
  IN    BOOLEAN WaitUntilHalted
)
{
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    if (Cpu == ApGlobalData->Bsp)
        return; // Can't halt BSP
    if (Cpu >= NumberCpus)
        return;
    CpuControl[Cpu].Halted = TRUE;
    if (WaitUntilHalted)
        WaitUntilZero32 (&CpuControl[Cpu].Function);
}

/**
    Check if a Cpu is halted.

        
    @param MpData 
    @param Cpu 

    @retval TRUE CPU is halted
    @retval FALSE CPU is not halted

**/

BOOLEAN
IsCpuHalted(
  IN    VOID    *MpData,
  IN    UINT8   Cpu
)
{
    AP_GLOBAL_DATA *ApGlobalData = (AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    if (Cpu >= NumberCpus)
        return TRUE;
    return CpuControl[Cpu].Halted && !CpuControl[Cpu].Function;
}

/**
    Check if a CPU is Idle.

        
    @param MpData 
    @param Cpu 

    @retval TRUE CPU is idle
    @retval FALSE CPU is not idle

**/

BOOLEAN
IsCpuIdle(
  IN    VOID    *MpData,
  IN    UINT8   Cpu
)
{
    AP_GLOBAL_DATA *ApGlobalData = (AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    if (Cpu >= NumberCpus)
        return TRUE;
    return !CpuControl[Cpu].Function;
}

/**
    Determine which CPU is the BSP.

    @param MpData 

    @retval UINT8 the BSP value

**/

UINT8
WhoIsBsp(
  IN    VOID    *MpData
)
{
    return ((AP_GLOBAL_DATA*)MpData)->Bsp;
}

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
