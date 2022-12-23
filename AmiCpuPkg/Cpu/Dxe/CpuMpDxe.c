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

/** @file CpuMpDxe.c
    Cpu MP routines

**/

#include <Efi.h>
#include <Token.h>
#include <AmiLib.h>
#include "Cpu.h"
#include "CpuCspLib.h"
#include <AmiDxeLib.h>
#include <Protocol/MpService.h>
#include "CpuDxe.h"
#include <Library/SbCspLib.h>
#include "CpuInterfaces.h"
#include <Library/DebugLib.h>

VOID MpStart();
VOID MpRestart();
VOID SwitchStacks(UINT8, VOID *);
VOID JmpToMpStart();
// extern UINT32 JmpAddress;
extern UINTN JmpAddress;
extern UINT32 JmpToMpStartSize;

// This Variable is initialized at the begin of CpuDxe
extern BOOLEAN IsItFamily15h;

//This will be copied to RAM.
/**
    (DXE Only) This halt loop will be copied to Runtime. Halted
    CPUS will enter into the runtime version.

    @param VOID

    @retval VOID

**/

UINT8
HaltLoop[] =
{
//@@:
    0xFA,       //cli
    0xF4,       //hlt
    0xEB,0xFC   //jmp @b
};
VOID * CpyToRunTime(VOID *Src, UINTN Size);

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
    UINT32  EightByteAlign; // Padding for GDT, makes 8 byte align
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
    UINT32      Idt;
    UINT8       CpuSync;
    UINT8       Bsp;
    UINT8       NumCpus;
    UINT8       RunningAps;
    UINT8       HaltedCpus;
} AP_GLOBAL_DATA;

#define WAIT_FOR_CPU_COUNT 400

typedef struct {
    EFI_MP_SERVICES_PROTOCOL    EfiMpServicesProtocol;
    AP_GLOBAL_DATA              *ApGlobalData;
} PRIVATE_MP_SERVICES;

EFI_STATUS EFIAPI EfiWhoAmI(
    IN EFI_MP_SERVICES_PROTOCOL *This,
    OUT UINTN   *ProcessorNumber
);

VOID
EfiMpFunction(
  IN    UINT8   Cpu,
  IN    VOID    *Context
);

extern PRIVATE_MP_SERVICES gPrivateMpServices;
EFI_MP_SERVICES_PROTOCOL   *gEfiMpServicesProtocol = (EFI_MP_SERVICES_PROTOCOL*) &gPrivateMpServices;
extern DESCRIPTOR_TABLE pIdt;

#define ASSERT_ERROR_CPU(Status) ASSERT_EFI_ERROR(Status)
#define STALL_CPU(time) pBS->Stall(time)
#define ALLOCATE_MEMORY_CPU(ptr_of_Address, Size) \
        pBS->AllocatePool(EfiBootServicesData, Size, ptr_of_Address)
#define FREE_MEMORY_CPU(ptr) \
        pBS->FreePool(ptr);
#define ALLOCATE_PAGES_CPU(ptr_of_Address, Pages) \
        pBS->AllocatePages(AllocateAnyPages, EfiBootServicesData, Pages, ptr_of_Address)

#ifdef EFIx64
extern UINT32  CPULIB_GetPageTable(VOID);
#endif

typedef struct {
    EFI_EVENT   *WaitEvent;
    EFI_EVENT   ThisApTimerEvent;
    UINTN       TimeoutEnd;
    BOOLEAN     *Finished;
    UINT8       ApStatus;
    UINT8       CpuNum;
} THIS_AP_TRACK;

// ApStatus bits definition
#define AP_BUSY         0x01
#define AP_TMOUT_ACT    0x02
#define AP_TMOUT_EXP    0x04

//Create wrapper to interface MpServices calls with existing thread controllers.
typedef struct {
    EFI_AP_PROCEDURE    Function;
    VOID                *Parameters;
} EFI_MP_CONTEXT;

#if (NCPU > 128)
#error Max CPUs is 128 for current code
#endif

EFI_MP_CONTEXT  EfiMpContext[NCPU] = {NULL, NULL};

THIS_AP_TRACK   ThisApDb[NCPU] = {NULL, NULL,0, NULL, 0, 0};


/*
    Global variable for StartAllAp control
*/
EFI_EVENT AllApTimerEvent      = NULL;
BOOLEAN   AllApTimeoutEnable   = FALSE;
BOOLEAN   AllApTimeoutExpired  = FALSE;  
BOOLEAN   AllApTimerEventAlive = FALSE;  //For record if timer is remain alive.
BOOLEAN   AllAPTimerCheckPending = TRUE; //Reduce timer wasted time berfor really need it.
INTN      AllApTimeout = 0;
UINT64    TimeStart;
UINT64    TimeEnd;

EFI_MP_CONTEXT  EfiAllMpContext[1] = {NULL, NULL};

EFI_EVENT AllApWaitEvent = NULL;
BOOLEAN   AllApSingleThread = FALSE;
UINT8     AllApNumWaitStartAp = 0;            //Numer of AP wait dispatch by BSP.
BOOLEAN   AllApTimerDispatcher   = FALSE;     //Enable/Disable AP dispatch in timer evnet. Only use in NonBlock SingleThread.
BOOLEAN   AllApTimerDispatchList[NCPU] = {0}; //Record AP should be dispach in this time. Can use it for process FailedList, Dispatching AP and Block other Mp service assign task to AP.
UINT8     DispatchingAp        = 0xFF;        //AP being dispatch at this time.

BOOLEAN   ApTerminatedTimeout = FALSE;
UINTN     **FailedCpuListPtr = NULL;



EFI_CPU_ARCH_PROTOCOL *gCpuArchProtocol = NULL;

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

        
    @param MpData (void*)AP_GLOBAL_DATA

         
    @retval VOID

    @note  This function is called implicitly with StartAllAps and
          RestartAp.

**/

EFI_STATUS
MpSynchronizeMtrrs(
  IN    VOID    *MpData
)
{
#if (0)
    MTRR_COPY_CONTEXT   MtrrCopyContext;
    EFI_STATUS          Status;

    InitMtrrCopyContext (&MtrrCopyContext);

    // Save MTRR values of the BSP to buffer
    DEBUG((DEBUG_INFO, "MpSynchronizeMtrrs: Copy BSP to(%X)\n",
     &MtrrCopyContext.ValueBuffer));
    Status = CopyBspMtrrsToAllRunningApMtrrs ((VOID*)&MtrrCopyContext);

    // Write MTRR values from buffer to the APs' MTRRs
    DEBUG((DEBUG_INFO, "MpSynchronizeMtrrs: Write APs from(%X)\n",
     &MtrrCopyContext.ValueBuffer));

    ExecuteFunctionOnRunningCpus (MpData, FALSE, TRUE,
     WrapCopyBspMtrrsToAllRunningApMtrrs, (VOID*)&MtrrCopyContext);
#endif
    return EFI_SUCCESS;
}

/**
    Start one or more AP with INIT-SIPI-SIPI.

  @param ApGlobalData - pointer AP_GLOBAL_DATA structure
  @param AllCpus - Start one or all CPUs.
  @param ApicId - This Used if AllCpus == FALSE.

  @retval UINT8 Number of CPUs started.
**/

UINT8
StartCpus(
  IN    AP_GLOBAL_DATA  *ApGlobalData,
  IN    BOOLEAN         AllCpus,
  IN    UINT8           ApicId  // If only 1 cpu
)
{
    ZERO_DATAx              ZeroDataBackUp;
    VOID                    *Below1MbStartupBackup;
    UINT8                   NumCpusStarted;
    EFI_STATUS              Status;
    EFI_TPL                 OldTpl;
    volatile UINT8          ExpectedApCount = AmdCpuCount() - 1;
    UINT64                  WaitCount;

    Status = ALLOCATE_MEMORY_CPU ((VOID**)&Below1MbStartupBackup, JmpToMpStartSize);
    ASSERT_ERROR_CPU(Status);

    OldTpl = pBS->RaiseTPL (TPL_HIGH_LEVEL);

    // Back up the original contents at MP_ZERO_DATA_ADDRESS and copy ZERO_DATAx structure
    // to this address. This structure will accessed by APs.
    MemCpy (&ZeroDataBackUp, (VOID*)MP_ZERO_DATA_ADDRESS, sizeof (ZERO_DATAx));

    CPULib_SaveGdt (MP_ZERO_DATA_ADDRESS);  // sgdt fword ptr [0];
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps = 0; // Initialize Count.
//    Agd64 ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT32)ApGlobalData;
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->ApGlobalData = (UINT64)ApGlobalData;

    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->Tom = (UINT32)ReadMsr (AMD_MSR_TOP_MEM);
#ifdef EFIx64
    ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->PageTable = (UINT32)CPULIB_GetPageTable();

    ((ZERO_DATAx*)MP_ZERO_DATA_ADDRESS)->Sel_0 = 0;
    ((ZERO_DATAx*)MP_ZERO_DATA_ADDRESS)->Sel_8 = 0x00CF93000000FFFF; // sel 8 
    ((ZERO_DATAx*)MP_ZERO_DATA_ADDRESS)->Sel_10 = 0x00CF9B000000FFFF; // sel 10 32bit code
    ((ZERO_DATAx*)MP_ZERO_DATA_ADDRESS)->Sel_38 = 0x00AF9B000000FFFF; // sel 38 64bit code
    ((ZERO_DATAx*)MP_ZERO_DATA_ADDRESS)->Gdtr = ((sizeof (ZERO_DATA) + 8 +
                                          MP_ZERO_DATA_ADDRESS) << 16) +
                                          sizeof (UINT64) * 8 - 1;
#endif

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

//    DEBUG((DEBUG_INFO,"StartCpus: Send SIPI to start APs\n"));
    // Send SIPI to start APs
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_HIGH_REGISTER) =  AllCpus ? 0 : ApicId << 24;
    *(UINT32*)(UINTN)(APIC_BASE + APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       INIT + LEVEL_ASSERT;

//    Status = STALL_CPU(10000); 

//    ASSERT_ERROR_CPU(Status);

    *(UINT32*)(UINTN)(APIC_BASE +APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);
    STALL_CPU (200);

    *(UINT32*)(UINTN)(APIC_BASE +APIC_ICR_LOW_REGISTER) = (AllCpus ? ALL_EXCLUDING_SELF : 0) +
                       LEVEL_ASSERT + SIPI + ((UINT32)MP_JUMP_FUNCTION_ADDRESS >> 12);

    if (AllCpus) {
    //        while ( ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps < ExpectedApCount);
        WaitCount = 0;
        while(WaitCount < 2000){
            if( ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop == ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps ) {
                break;
            }
            STALL_CPU(1);     // Wait 1 uS
            WaitCount++;
        }
    } else {
        WaitCount = 0;
        while(WaitCount < 2000){
            if( ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop == 1 ) {
                break;
            }
            STALL_CPU(1);     // Wait 1 uS
            WaitCount++;
        }
    }
    //    while ( ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->EnteredHoldLoop < ExpectedApCount);

// Should not use TRACE After rising the trace level
//    DEBUG((DEBUG_INFO,"StartCpus: Get NumCpusStarted\n"));
    NumCpusStarted = AllCpus ? ((ZERO_DATA*)MP_ZERO_DATA_ADDRESS)->NumAps : 1;

    // Restore original memory contents.
    // This is important for S3 resume.
    MemCpy ((VOID*)MP_ZERO_DATA_ADDRESS, &ZeroDataBackUp, sizeof (ZERO_DATAx));
    MemCpy ((VOID*)MP_JUMP_FUNCTION_ADDRESS, Below1MbStartupBackup, JmpToMpStartSize);

    pBS->RestoreTPL(OldTpl);

//    DEBUG((DEBUG_INFO, "StartCpus: FREE_MEMORY_CPU(%X)\n", Below1MbStartupBackup));
    FREE_MEMORY_CPU (Below1MbStartupBackup);

    return NumCpusStarted;
}

/**
    Start all APs and place in their holding loops for further
    work.

  @param ApGlobalData 

  @retval UINT8  Number of started CPUs
**/

UINT8 
StartAllAps(
  OUT   VOID    **MpData
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

    ApGlobalData->HaltLoopEntry = CpyToRunTime(HaltLoop, sizeof(HaltLoop));
    ApGlobalData->Idt = (UINT32)&pIdt;   //Save Idt table pointer
    DEBUG((DEBUG_INFO,"StartAllAps: Idt table = %lx  \n", &pIdt));
    
//    DEBUG((DEBUG_INFO,"StartAllAps> Before StartCpus()\n"));
    NumCpus = StartCpus((AP_GLOBAL_DATA*)ApGlobalData, TRUE, 0);    // Valid, if only 1 cpu
    
    ++NumCpus;  //Count BSP
    ApGlobalData->NumCpus = NumCpus;
    DEBUG((DEBUG_INFO,"StartAllAps: NumCpus = %x.\n", NumCpus));
    DEBUG((DEBUG_INFO,"StartAllAps: AmdCpuCount() = %x.\n", AmdCpuCount()));

    // Ap gets control, switches to protected mode and is in a holding loop until
    // given a pointer to collect CPU info and give it a number.

    //
    //Get initial CPU Info to sort CPUs.
    //
    Status = ALLOCATE_MEMORY_CPU(&CpuInfoInit, NumCpus * sizeof(CPU_INFO_INIT));
    ASSERT_ERROR_CPU(Status);
    for (i = 0; i < NumCpus; ++i)
    {
        CpuInfoInit[i].CpuNum = 0xFFFFFFFF;
    }


    Status = ALLOCATE_MEMORY_CPU(&CpuControl, NumCpus * sizeof(CPU_CONTROL));
    ASSERT_ERROR_CPU(Status);
    MemSet(CpuControl, NumCpus * sizeof(CPU_CONTROL), 0);   //Initialize

    // Allocate Stack
    // Each AP gets a page of stack. (Only allocate for APs)
    if (NumCpus > 1)
    {
        Status = ALLOCATE_PAGES_CPU (&ApStack, (NumCpus - 1) * (AP_STACK_SIZE / EFI_PAGE_SIZE));
        ASSERT_ERROR_CPU (Status);
    }

    ApGlobalData->CpuControl = CpuControl;
    DEBUG((DEBUG_INFO,"StartAllAps: ApGlobalData = %X. %X\n", ApGlobalData , (AP_GLOBAL_DATA*)ApGlobalData->CpuControl));
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
    ApGlobalData->CpuSync = NumCpus - 1;

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
        {   // BSP
            ApGlobalData->Bsp = (UINT8)i;
            CpuControl[i].Id = BspId;
            CpuControl[i].Function = (VOID(*)(UINT8, VOID*)) - 1;   // BSP is never halted.
        }
        else
        {   // AP
            ApStack += AP_STACK_SIZE;    // Start at top of stack or stack for next AP.
            CpuControl[i].Stack = (VOID*)ApStack;   // Store stack addresses for AP.
        }
        CpuInfoInit[k].CpuNum = (UINT8)i;   //Release Cpu
        ++Id;
    }

    WaitUntilZero8(&ApGlobalData->CpuSync); //Wait 'till all APs are synced.

    gPrivateMpServices.ApGlobalData = (AP_GLOBAL_DATA*)ApGlobalData;

    if (IsFamily15h())
    {
        // Synchronize all APs' MTRRs with BSP's MTRRs
        DEBUG((DEBUG_INFO, "StartAllAps: Before MpSynchronizeMtrrs()\n"));
        MpSynchronizeMtrrs (*MpData);
        DEBUG((DEBUG_INFO, "StartAllAps: After MpSynchronizeMtrrs()\n"));
    }

    // Aps are waiting in a loop, for an address to jump to, or halted.
    return NumCpus;
}


/**
  This function restarts the CPU when timeout expired
        
      (PEI Only) IN EFI_PEI_SERVICES      **PeiServices
      (PEI Only) IN EFI_PEI_STALL_PPI     *PeiStall
  @param MpData - pointer to AP_GLOBAL_DATA structure
  @param Cpu - Cpu to restart.

  @retval VOID
**/

VOID 
ResetAp(
  IN VOID     *MpData,
  IN UINT8    Cpu )
{
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;

    if (Cpu == ApGlobalData->Bsp || Cpu >= ApGlobalData->NumCpus) return;

    ApGlobalData->ReleaseCpu = (VOID*)(UINTN)Cpu;  //Assign CPU number.
    ApGlobalData->Idt = (UINT32)&pIdt;   //Save Idt table pointer

    StartCpus(
        (AP_GLOBAL_DATA*)ApGlobalData,
        FALSE,
        CpuControl[Cpu].Id
    );

    // Synchronize all APs' MTRRs with BSP's MTRRs
//###    DEBUG((DEBUG_INFO,"ResetAp: Before MpSynchronizeMtrrs()"));
    MpSynchronizeMtrrs(MpData);
//###    DEBUG((DEBUG_INFO,"ResetAp: After MpSynchronizeMtrrs()"));
}

/**
  After CPU has been halted, this function restarts the CPU.
        
  @param MpData - pointer to AP_GLOBAL_DATA structure
  @param Cpu - Cpu to restart.

    @retval VOID

**/

VOID
RestartAp(
  IN    VOID    *MpData,
  IN    UINT8   Cpu
)
{
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumberCpus = ApGlobalData->NumCpus;

    if (Cpu == ApGlobalData->Bsp || Cpu >= NumberCpus)
        return;
    if (!CpuControl[Cpu].Halted)
        return;

    ApGlobalData->ReleaseCpu = (VOID*)(UINTN)Cpu;  //Assign CPU number.

    StartCpus(
        (AP_GLOBAL_DATA*)ApGlobalData,
        FALSE,
        CpuControl[Cpu].Id
    );

    // Synchronize all APs' MTRRs with BSP's MTRRs
    MpSynchronizeMtrrs (MpData);
}

/**
  Get number of CPUs, that has been found.

  @param MpData - pointer to AP_GLOBAL_DATA structure

  @retval UINT8 - Number of CPUs found.
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
    BOOLEAN IntState;

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
        IntState = CPULib_GetInterruptState();
        CPULib_DisableInterrupt();  
        CpuControl[i].Context = Context;    // Must set Context first.
        CpuControl[i].Function = Function;  // This releases the CPU.
#if USE_AP_HLT        
        // generate NMI for AP
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[i].Id << 24);
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
        if (IsItFamily15h)
            STALL_CPU(500);
#endif
    }

    if (ExecuteOnBsp) Function(ApGlobalData->Bsp, Context);

    if (Block)
        WaitUntilZero8 (&ApGlobalData->RunningAps);
    if(IntState)    CPULib_EnableInterrupt();   
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
    BOOLEAN     IntState;
    volatile AP_GLOBAL_DATA *ApGlobalData = (volatile AP_GLOBAL_DATA *)MpData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8               NumberCpus = ApGlobalData->NumCpus;
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

    CPULib_LockByteInc(RunningAps);        //Increase number of CPUs running.
    IntState = CPULib_GetInterruptState();

    CpuControl[Cpu].Context = Context;      //Must set Context first.
    CpuControl[Cpu].Function = Function;    //This releases the CPU.
#if USE_AP_HLT
    // Generate NMI for AP
    *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[Cpu].Id << 24);
    *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
    if (IsItFamily15h)
        STALL_CPU(500);
#endif    
    if (Block)
        WaitUntilZero8 (RunningAps);
    if(IntState)    CPULib_EnableInterrupt();   

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
#if USE_AP_HLT
        // Generate NMI for AP
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[i].Id << 24);
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
        if (IsItFamily15h)
            STALL_CPU(500);
#endif         
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
#if USE_AP_HLT
    // Generate NMI for AP
    *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[Cpu].Id << 24);
    *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
    if (IsItFamily15h)
        STALL_CPU(500);
#endif 
    if (WaitUntilHalted) WaitUntilZero32(&CpuControl[Cpu].Function);
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

  @param VOID* pointer to AP_GLOBAL DATA structure 

  @retval UINT8 the BSP value
  
**/

UINT8
WhoIsBsp(
  IN    VOID    *MpData
)
{
    return ((AP_GLOBAL_DATA*)MpData)->Bsp;
}

////////////////////////////////////////////////////////////
//////////////////CPU MP Services Protocol//////////////////
////////////////////////////////////////////////////////////

typedef struct {
    UINT64      CpusWaiting00;      // Bit map of CPUs waiting.
    UINT64      CpusWaiting64;      // Bit map of CPUs waiting.
    VOID        *MpData;            // Private Data
    EFI_EVENT   Event;              // Event to signal when all CPUs are finished.
    BOOLEAN     *Finished;          // For StartupThisAp()
} TRACK_CPUS_WAITING;





VOID
ProcessAllApTimeout(
  IN  AP_GLOBAL_DATA  *ApGlobalData
)
{   
    volatile CPU_CONTROL    *CpuControl = ApGlobalData->CpuControl;
    EFI_STATUS     Status;
    UINT8          i = 0;
    UINT8          NumCpus = ApGlobalData->NumCpus;
    UINT8          Bsp = WhoIsBsp((VOID *)ApGlobalData);
    UINT8          NumOfFailedCpus = 0;
    UINT8          CpuIdx;

    //Get number of failed AP and process AllApTimerDispatchList.
    if(AllApSingleThread)
    {
        //Single Thread, non dispatched AP will filled in FailedList.
        if (!IsCpuIdle(ApGlobalData, DispatchingAp))
        {
            NumOfFailedCpus++;
            AllApTimerDispatchList[DispatchingAp] = TRUE;
        }
        for(i = DispatchingAp + 1; i < NumCpus; i++)
            if (AllApTimerDispatchList[i])
                NumOfFailedCpus++;
    }
    else
    {
        //Non Single Thread, check if dispatched AP which is not finished its task before timeout.
        for (i = 0; i < NumCpus; ++i)
        {
            if (!AllApTimerDispatchList[i])
                continue;
            if (IsCpuIdle(ApGlobalData, i))
            {
                AllApTimerDispatchList[i] = FALSE;
                continue;
            }
            NumOfFailedCpus++;
        }
    }

    //If get number of failed AP is zero, don't create report.
    if((FailedCpuListPtr != NULL) && (NumOfFailedCpus != 0))
    {
        Status = pBS->AllocatePool(EfiBootServicesData,
                                    (NumOfFailedCpus + 1) * sizeof(UINTN),
                                     FailedCpuListPtr);
        if(Status != EFI_SUCCESS)
            FailedCpuListPtr = NULL;
    }
    else
        FailedCpuListPtr = NULL;

    CpuIdx = 0;
    for (i = 0; i < NumCpus; ++i)
    {
        // Check if AP have responsibility this time.
        if(!AllApTimerDispatchList[i])
            continue;

        ApTerminatedTimeout = TRUE;

        if(!IsCpuIdle(ApGlobalData, i))
        {
            ResetAp((VOID*)ApGlobalData, i);
            ApGlobalData->RunningAps--;
        }
        // Fill out FailedCPUList
        if((FailedCpuListPtr != NULL)&&(*FailedCpuListPtr != NULL))
        {
            (*FailedCpuListPtr)[CpuIdx++] = i;
        }
    }

    if ((FailedCpuListPtr != NULL) && (*FailedCpuListPtr != NULL))
    {
        (*FailedCpuListPtr)[CpuIdx] = END_OF_CPU_LIST;
    }
}


/**
  Handler for periodic timer event used in StartupThisAP() function
  
  @param Event - Event handle
  @param Context - pointer to AP number
  
  @retval VOID
*/

VOID
EFIAPI
ThisApTimerHandler(
  IN EFI_EVENT Event, 
  IN VOID *Context
)
{
    UINT64          CurrentTime;
    EFI_STATUS      Status;
    AP_GLOBAL_DATA  *ApGlobalData;
    UINT8           Cpu;
    
    Cpu = *((UINT8*)Context);
    if(Cpu >= NCPU)
        return;
    ApGlobalData = gPrivateMpServices.ApGlobalData;
    
    if((ThisApDb[Cpu].TimeoutEnd != 0)&&(gCpuArchProtocol != 0))
    {
        Status = gCpuArchProtocol->GetTimerValue(
                                          gCpuArchProtocol,
                                          0,            // TimerIndex
                                          &CurrentTime,   // TimerValue
                                          NULL          // period in femtoSec
                                        );
        if(CurrentTime > ThisApDb[Cpu].TimeoutEnd)
        {
            ThisApDb[Cpu].ApStatus |= AP_TMOUT_EXP;
            ThisApDb[Cpu].ApStatus &= ~AP_TMOUT_ACT;
            ThisApDb[Cpu].TimeoutEnd = 0;
            // Stop periodic timer
            pBS->SetTimer(ThisApDb[Cpu].ThisApTimerEvent, TimerCancel, 0);
            if(ThisApDb[Cpu].ThisApTimerEvent != NULL)
                pBS->CloseEvent(ThisApDb[Cpu].ThisApTimerEvent);
            if(!IsCpuIdle(ApGlobalData, Cpu))
            {
                ResetAp((VOID*)ApGlobalData, Cpu);
                ApGlobalData->RunningAps--;
                ThisApDb[Cpu].ApStatus &= ~AP_BUSY;
            }
            if(ThisApDb[Cpu].WaitEvent != NULL)
            {
                if(ThisApDb[Cpu].Finished)
                    *(ThisApDb[Cpu].Finished) = FALSE;
                // Signal event
                pBS->SignalEvent(ThisApDb[Cpu].WaitEvent);
                ThisApDb[Cpu].WaitEvent = NULL;
            }
        }
        else
        {
            // Check if AP finished before timeout
            if (IsCpuIdle (ApGlobalData, Cpu) && (ThisApDb[Cpu].ApStatus & AP_TMOUT_ACT))
            {
                // Stop periodic timer
                pBS->SetTimer (ThisApDb[Cpu].ThisApTimerEvent, TimerCancel, 0);
                if (ThisApDb[Cpu].ThisApTimerEvent != NULL)
                    pBS->CloseEvent(ThisApDb[Cpu].ThisApTimerEvent);
                if (ThisApDb[Cpu].WaitEvent)
                {
                    if (ThisApDb[Cpu].Finished)
                        *(ThisApDb[Cpu].Finished) = TRUE;
                    // Signal event
                    pBS->SignalEvent(ThisApDb[Cpu].WaitEvent);
                    ThisApDb[Cpu].WaitEvent = NULL;
                }
            }
        }
    }
}

/**
  Handler for periodic timer event used in StartupAllAPs() function
  
  @param Event - Event handle
  @param Context - pointer to AP number
  
  @retval VOID
*/
VOID 
AllApTimerHandler(
  IN EFI_EVENT Event, 
  IN VOID *Context
)
{
    AP_GLOBAL_DATA  *ApGlobalData = (AP_GLOBAL_DATA*)Context;
//  volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT64          CurrentTime;
    EFI_STATUS      Status;
    UINT8           i = 0;
    UINT8           NumCpus = ApGlobalData->NumCpus;
    BOOLEAN         IntState = FALSE;
    BOOLEAN         Finished = FALSE;
    UINT8           *RunningAps = (UINT8*)&ApGlobalData->RunningAps;
    volatile CPU_CONTROL    *CpuControl = ApGlobalData->CpuControl;
  
    //Reduce time waste in timer before really need it.
    if(AllAPTimerCheckPending)
        return;
    if (AllApTimeoutEnable)
    {
        AllApTimeout -= 500;
        if ((TimeEnd != 0) && (gCpuArchProtocol != 0))
        {
            Status = gCpuArchProtocol->GetTimerValue (gCpuArchProtocol, 0, &CurrentTime, NULL);
            if (CurrentTime >= TimeEnd)
            {
                AllApTimeout = -1;
                TimeEnd = 0;
            }
        }
        if (AllApTimeout < 0)
            AllApTimeoutExpired = TRUE;
    }

    //If is single thread non block mode, dispatch AP which not yet dispatched.
    if(!AllApTimeoutExpired && AllApTimerDispatcher)
    {
        //Check if privious AP is finished.
        if(!IsCpuIdle(ApGlobalData, DispatchingAp))
            return;
        //Search AP require to be dispatch by BSP.
        for (i = DispatchingAp + 1; i < NumCpus; i++)
        {
            if (AllApTimerDispatchList[i] == TRUE)
            {
                AllApNumWaitStartAp--;
                DispatchingAp = i;
                AllApTimerDispatchList[i] = FALSE;

                IntState = CPULib_GetInterruptState();
                CPULib_DisableInterrupt();  

                CPULib_LockByteInc(RunningAps);        // Increase number of CPUs running.
                CpuControl[i].Context = &EfiAllMpContext[0];      //Must set Context first.
                CpuControl[i].Function = EfiMpFunction;    //This releases the CPU.
#if USE_AP_HLT        
                // Generate NMI for AP
                *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[i].Id << 24);
                *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
                if (IsItFamily15h)
                    STALL_CPU(500);
#endif            
                if(IntState)
                    CPULib_EnableInterrupt();
                break;
            }
        }
        //There is no AP wait for dispatch, stop the dispatcher.
        if (AllApNumWaitStartAp == 0)
            AllApTimerDispatcher = FALSE;
    }

    // Check if all AP done its task.
    if(AllApSingleThread)
    {
        if(AllApNumWaitStartAp == 0)
            if(IsCpuIdle(ApGlobalData, DispatchingAp))
                    Finished = TRUE;
    }
    else
    {
        Finished = TRUE;
        //Go through AllApTimerDispatchList for AP required to be start and check if AP done its task.
        for (i = 0; i < NumCpus; i++)
        {
            if(!AllApTimerDispatchList[i])
                continue;
            if(!IsCpuIdle(ApGlobalData, i))
            {
                Finished = FALSE;
                break;
            }
        }
    }

    //If timeout or all AP done its task, kill event and signal the wait event.
    if (AllApTimeoutExpired || Finished)
    {
        AllApTimerDispatcher = FALSE;

        //Finished and timeout at same time treat as not timeout.
        if(Finished)
            AllApTimeoutExpired = FALSE;
        
        //Kill event
        pBS->SetTimer (AllApTimerEvent, TimerCancel, 0);
        if (AllApTimerEvent != NULL)
        {
            pBS->CloseEvent(AllApTimerEvent);
            AllApTimerEventAlive = FALSE;
        }
        if(AllApTimeoutExpired)
        {
            ProcessAllApTimeout (ApGlobalData);
            DEBUG((DEBUG_INFO, "MP All AP Ends On Timeout.\n"));
        }

        // Signal event
        if (AllApWaitEvent != NULL)
        {
            pBS->SignalEvent(AllApWaitEvent);
            AllApWaitEvent = NULL;
        }
    }
}

/**
  Install periodic timer used in StartupThisAP() function
  
  @param TimeOutInMicroseconds - Timeout in microseconds
  @param WaitEvent - Event to signal when timeout expired or AP finishes
  @param Cpu - AP number
  @param ApGlobalData - pointer to AP_GLOBAL_DATA structure
  
  @retval EFI_SUCCESS Timer installed
*/

EFI_STATUS
SetupThisApTimer(    
  IN  UINTN     TimeOutInMicroseconds,
  IN  EFI_EVENT WaitEvent,
  IN  UINT8     Cpu,
  IN  AP_GLOBAL_DATA  *ApGlobalData )
{
    EFI_STATUS  Status;
    UINT64      TimerPeriod;
    UINT64      TimerStartValue;

    if(Cpu >= NCPU)
        return EFI_INVALID_PARAMETER;

    ThisApDb[Cpu].TimeoutEnd = 0;
    ThisApDb[Cpu].CpuNum = Cpu;
    ThisApDb[Cpu].ApStatus = AP_TMOUT_ACT;
    if (TimeOutInMicroseconds > 0)
    {
        if (gCpuArchProtocol == NULL)
            Status = pBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &gCpuArchProtocol);

        if (gCpuArchProtocol != NULL)
        {
            Status = gCpuArchProtocol->GetTimerValue (gCpuArchProtocol, 0, &TimerStartValue, &TimerPeriod);
            ThisApDb[Cpu].TimeoutEnd = TimerStartValue + Div64 (Mul64 (TimeOutInMicroseconds, 1000000000), TimerPeriod, NULL);
        }
    }
    if (WaitEvent != NULL)
        ThisApDb[Cpu].WaitEvent = WaitEvent;

    Status = pBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_NOTIFY, ThisApTimerHandler,
                               (VOID*)&(ThisApDb[Cpu].CpuNum), &(ThisApDb[Cpu].ThisApTimerEvent));
    if (Status != EFI_SUCCESS)
        return  Status;
    Status = pBS->SetTimer (ThisApDb[Cpu].ThisApTimerEvent, TimerPeriodic, 10*500); // 500us
    return  Status;
}

/**
  Install periodic timer used in StartupAllAPs() function
  
  @param TimeOutInMicroseconds - Timeout in microseconds
  @param WaitEvent - Event to signal when timeout expired or AP finishes
  @param ApGlobalData - pointer to AP_GLOBAL_DATA structure
  
  @retval EFI_SUCCESS - Timer installed
*/

EFI_STATUS
SetupAllApTimer(
  IN  UINTN TimeOutInMicroseconds,
  EFI_EVENT   WaitEvent,
  IN  AP_GLOBAL_DATA  *ApGlobalData )
{
    EFI_STATUS  Status;
    UINT64      TimerPeriod;

    Status = pBS->CreateEvent(
          EVT_TIMER | EVT_NOTIFY_SIGNAL,
          TPL_NOTIFY,
          AllApTimerHandler,
          (VOID*)ApGlobalData,
          &AllApTimerEvent
        );
    if (gCpuArchProtocol == NULL)
        Status = pBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &gCpuArchProtocol);

    if (gCpuArchProtocol != NULL)
    {
        Status = gCpuArchProtocol->GetTimerValue (gCpuArchProtocol, 0, &TimeStart, &TimerPeriod);
        TimeEnd = TimeStart + Div64 (Mul64 (TimeOutInMicroseconds, 1000000000), TimerPeriod, NULL);
    }

    AllApTimerEventAlive = TRUE;
    Status = pBS->SetTimer (AllApTimerEvent, TimerPeriodic, 10*500); // 500 uS

    return Status;
}

/**
  Check if CPUs being checked are idle by a periodic timer.
    If so, signal tracked  event and close this event.

  @param Event - Periodic timer event handler
  @param Context - Pointer to TRACK_CPUS_WAITING structure

  @retval VOID
**/

VOID 
EFIAPI
CheckCpuWaiting(
  IN EFI_EVENT Event, 
  IN VOID *Context )
{
    TRACK_CPUS_WAITING  *Track = (TRACK_CPUS_WAITING*) Context;
    UINT64              CpusWaiting00 = Track->CpusWaiting00;
    UINT64              CpusWaiting64 = Track->CpusWaiting64;
    UINTN  i;

    // For finished CPUs, the bit in the map is cleared.
    for (i = 0; CpusWaiting00 && i < 64; ++i)
    {
        if (CpusWaiting00 & 1)
            if (IsCpuIdle (Track->MpData, (UINT8)i))
                Track->CpusWaiting00 &= ~(Shl64 (1, (UINT8)i));

        CpusWaiting00 = Shr64 (CpusWaiting00, 1);
    }
    for (i = 0; CpusWaiting64 && i < 64; ++i)
    {
        if (CpusWaiting64 & 1)
            if (IsCpuIdle (Track->MpData, (UINT8)i + 64))
                Track->CpusWaiting64 &= ~(Shl64 (1, (UINT8)i));

        CpusWaiting64 = Shr64 (CpusWaiting64, 1);
    }

    //If all CPUs have finished, signal the event, and clean up.
    if ((!Track->CpusWaiting00) && (!Track->CpusWaiting64))
    {
        if(Track->Finished)
            *(Track->Finished) = TRUE;
        pBS->SignalEvent(Track->Event);
        pBS->FreePool(Track);
        pBS->CloseEvent(Event);
    }
}

/**
  Setup periodic timer to check if CPUs are idle. This function
    works with function CheckCpuWaiting.

  @param MpData - pointer to AP_GLOBAL_DATA structure
  @param CpusWaiting00 - bitmap of running APs (1-63) to check 
  @param CpusWaiting64 - bitmap of running APs (64-127) to check 
  @param Event - event to signal when APs finishes
  @param Finished - pointer to BOOLEAN variable, reflecting if AP finished job

  @retval EFI_STATUS return the EFI status
**/

EFI_STATUS 
SetupCheckCpus(
  IN VOID       *MpData,
  IN UINT64     CpusWaiting00,
  IN UINT64     CpusWaiting64,
  IN EFI_EVENT  Event,
  IN BOOLEAN    *Finished )
{
    TRACK_CPUS_WAITING *Track;
    EFI_STATUS          Status;
    EFI_EVENT           CheckCpusEvent;

    Status = pBS->AllocatePool (EfiBootServicesData, sizeof(TRACK_CPUS_WAITING), &Track);
    if (EFI_ERROR(Status))
        return Status;

    Track->CpusWaiting00 = CpusWaiting00;
    Track->CpusWaiting64 = CpusWaiting64;
    Track->MpData = MpData;
    Track->Event = Event;
    Track->Finished = Finished;

    // Create a timer event, to check when APs have finished.
    Status = pBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY, CheckCpuWaiting, Track, &CheckCpusEvent);
    if (EFI_ERROR (Status))
        goto CREATE_EVENT_ERROR;

    Status = pBS->SetTimer (CheckCpusEvent, TimerPeriodic, 10 * 100); // 100us
    if (EFI_ERROR (Status))
        goto SET_TIMER_ERROR;

    return EFI_SUCCESS;

SET_TIMER_ERROR:
    pBS->CloseEvent(CheckCpusEvent);

CREATE_EVENT_ERROR:
    pBS->FreePool(Track);
    return Status;
}

/**
  A wrapper function to call EFI_MP_SERVICES_PROTOCOL function
    to execute on CPUs.

  @param Cpu - AP number
  @param Context - pointer to EFI_MP_CONTEXT structure

    @retval VOID

**/

VOID
EfiMpFunction(
  IN    UINT8   Cpu,
  IN    VOID    *Context
)
{
    EFI_MP_CONTEXT *Mp = (EFI_MP_CONTEXT*)Context;
    Mp->Function(Mp->Parameters);
}

/**
    Return CPU information.

    @param This 
    @param NumberOfProcessors 
    @param NumberOfEnabledProcessors 

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiGetNumberOfProcessors (
  IN    EFI_MP_SERVICES_PROTOCOL    *This,
  OUT   UINTN                       *NumberOfProcessors,
  OUT   UINTN                       *NumberOfEnabledProcessors
)
{
    AP_GLOBAL_DATA *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
    UINTN   ExecutingCpu;

    if ((NumberOfProcessors == NULL) || (NumberOfEnabledProcessors == NULL)) {
        return EFI_INVALID_PARAMETER;
    }
    // Function can be called only by BSP
    EfiWhoAmI(This, &ExecutingCpu);
    if(ExecutingCpu != ApGlobalData->Bsp) {
        return EFI_DEVICE_ERROR;
    }
    
    *NumberOfProcessors = ApGlobalData->NumCpus;
    *NumberOfEnabledProcessors = ApGlobalData->NumCpus - ApGlobalData->HaltedCpus;
    
    DEBUG((DEBUG_INFO, "EfiGetNumberOfProcessors \n"));
    DEBUG((DEBUG_INFO, "NumberOfProcessors = %x \n", ApGlobalData->NumCpus));
    DEBUG((DEBUG_INFO, "NumberOfEnabledProcessors =%x \n", *NumberOfEnabledProcessors));

    return EFI_SUCCESS;
}

/**
    Return processor information.

        
    @param This This object
    @param ProcessorNumber Number of processor
    @param ProcessorInfoBuffer Buffer

  @retval EFI_SUCCESS if returned successful.
  @retval EFI_INVALID_PARAMETER if CPU not present.
**/

EFI_STATUS
EFIAPI
EfiGetProcessorInfo(
  IN        EFI_MP_SERVICES_PROTOCOL    *This,
  IN        UINTN                       ProcessorNumber,
  IN OUT    EFI_PROCESSOR_INFORMATION   *ProcessorInfoBuffer
)
{
    AP_GLOBAL_DATA *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8   NumCpus = ApGlobalData->NumCpus;
    UINTN   ExecutingCpu;

    if (ProcessorNumber >= NumCpus)
        return EFI_NOT_FOUND;

    if(ProcessorInfoBuffer == NULL)
        return EFI_INVALID_PARAMETER;

    // Function can be called only by BSP
    EfiWhoAmI (This, &ExecutingCpu);
    if(ExecutingCpu != ApGlobalData->Bsp)
        return EFI_DEVICE_ERROR;

    DEBUG((DEBUG_INFO, "Getting EfiGetProcessorInfo \n"));
    ProcessorInfoBuffer->ProcessorId = CpuControl[ProcessorNumber].Id;

    if (ApGlobalData->Bsp == ProcessorNumber)
    {
        // It's BSP
        ProcessorInfoBuffer->StatusFlag = 0x7;  // Healthy Enabled BSP.
    }
    else
    {
        // It's AP
        ProcessorInfoBuffer->StatusFlag = 0x6;  // Healthy Enabled AP.
        if (CpuControl[ProcessorNumber].Halted)
          ProcessorInfoBuffer->StatusFlag &= ~(UINT32)0x2; // Clear PROCESSOR_ENABLED_BIT
    }

    ProcessorInfoBuffer->Location.Package = 0;
    ProcessorInfoBuffer->Location.Core = 0;
    ProcessorInfoBuffer->Location.Thread = 0;
    DEBUG((DEBUG_VERBOSE, "ProcessorId       = %X \n", ProcessorInfoBuffer->ProcessorId));
    DEBUG((DEBUG_VERBOSE, "StatusFlag        = %X \n", ProcessorInfoBuffer->StatusFlag));
    DEBUG((DEBUG_VERBOSE, "Location.Package  = %X \n", ProcessorInfoBuffer->Location.Package));
    DEBUG((DEBUG_VERBOSE, "Location.Core     = %X \n", ProcessorInfoBuffer->Location.Core));
    DEBUG((DEBUG_VERBOSE, "Location.Thread   = %X \n", ProcessorInfoBuffer->Location.Thread));
    return EFI_SUCCESS;
}

/**
    Execute function on all APs.

    @param This 
    @param Procedure 
    @param SingleThread 
        - if TRUE, execute one function on one CPU at a time.
        - if FALSE, execute function on all CPUs at the same time.
    @param WaitEvent OPTIONAL
        - Event to signal when CPUs have completed executing.
    @param TimeoutInMicroSecs Indicates the time limit in microseconds for APs to return from Procedure, either
                              for blocking or non-blocking mode. Zero means infinity.
    @param ProcArguments OPTIONAL
        - Paramter to pass to function.
    @param FailedCPUList OPTIONAL      (Unsupported)

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiStartupAllAps(
  IN        EFI_MP_SERVICES_PROTOCOL    *This,
  IN        EFI_AP_PROCEDURE            Procedure,
  IN        BOOLEAN                     SingleThread,
  IN        EFI_EVENT                   WaitEvent OPTIONAL,
  IN        UINTN                       TimeoutInMicroSecs,
  IN OUT    VOID                        *ProcArguments OPTIONAL,
  OUT UINTN       **FailedCPUList OPTIONAL
)
{
    AP_GLOBAL_DATA      *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
    BOOLEAN             IsBlock = (WaitEvent == NULL) ? TRUE : FALSE;
volatile CPU_CONTROL    *CpuControl = ApGlobalData->CpuControl;
    UINT8               Bsp = WhoIsBsp ((VOID *)ApGlobalData);
    UINT8               NumCpus = ApGlobalData->NumCpus;
    UINT8               i;
    UINTN               ExecutingCpu;
    BOOLEAN             IntState;
    UINT8               *RunningAps = (UINT8*)&ApGlobalData->RunningAps;

    // No enabled APs exist in the system.
    if ((ApGlobalData->NumCpus - ApGlobalData->HaltedCpus) == 1)
        return EFI_NOT_STARTED;

    if (Procedure == NULL)
        return EFI_INVALID_PARAMETER;

    // Function can be called only by BSP
    EfiWhoAmI (This, &ExecutingCpu);
    if (ExecutingCpu != ApGlobalData->Bsp)
        return EFI_DEVICE_ERROR;

    if(AllApTimerEventAlive)
        return EFI_NOT_READY;

    // All Enabled CPUs must be idle.
    for (i = 0; i < NumCpus; ++i)
    {
        if (i == Bsp)
            continue;
        if (CpuControl[i].Halted)
        {
            DEBUG((DEBUG_INFO, "CPU %X is Halted\n", i));
            continue;
        }
        if (!IsCpuIdle (ApGlobalData, i))
        {
            DEBUG((DEBUG_INFO, "CPU %X is Not Ready\n", i));
            return EFI_NOT_READY;
        }
    }

    DEBUG((DEBUG_INFO, "StartAllAps OT   %d   WE   %X   MS   %d   FailedCPUList   %X\n", SingleThread, ((WaitEvent != NULL) ? 1 : 0), TimeoutInMicroSecs, FailedCPUList));

    //Initial global variable for later use.
    EfiAllMpContext[0].Function = Procedure;
    EfiAllMpContext[0].Parameters = ProcArguments;

    FailedCpuListPtr = FailedCPUList;

    AllApTimeoutExpired = FALSE;
    
    ApTerminatedTimeout = FALSE;
    AllApTimerDispatcher  = FALSE;
    
    AllApWaitEvent      = WaitEvent;

    if(SingleThread)
        AllApSingleThread = TRUE;
    else
        AllApSingleThread = FALSE;

    if (TimeoutInMicroSecs)
    {
        AllApTimeout        = TimeoutInMicroSecs;
        AllApTimeoutEnable  = TRUE;
    }
    else
        AllApTimeoutEnable  = FALSE;

    AllApNumWaitStartAp = 0;
    DispatchingAp = 0xFF;
    //Process an Ap list which is required for dispatch in this time. And record their's total number.
    for (i = 0; i < NumCpus; ++i)
    {
        AllApTimerDispatchList[i] = FALSE;
        if (i == Bsp)
            continue;
        if (CpuControl[i].Halted)
            continue;
        if (IsCpuIdle (ApGlobalData, i))
        {
            AllApTimerDispatchList[i] = TRUE;
            AllApNumWaitStartAp++;
        }
    }

    //Start up an event for check if AP timeout and responsible to restart AP when it timeout.
    AllAPTimerCheckPending = TRUE;
    if((TimeoutInMicroSecs != 0) || (WaitEvent != 0))
        SetupAllApTimer(TimeoutInMicroSecs, WaitEvent, ApGlobalData);

    for (i = 0; i < NumCpus; ++i)
    {
        if (i == Bsp)
            continue;
        // Skip disabled CPUs
        if (CpuControl[i].Halted) 
            continue;

        // Disable interrupt when assign task to AP.
        IntState = CPULib_GetInterruptState();
        CPULib_DisableInterrupt();  

        // Decrease total AP numbers wait for assigned task.
        AllApNumWaitStartAp--;

        CPULib_LockByteInc(RunningAps);                   // Increase number of CPUs running.
        CpuControl[i].Context = &EfiAllMpContext[0];      //Must set Context first.
        CpuControl[i].Function = EfiMpFunction;           //This releases the CPU.
#if USE_AP_HLT        
        // Generate NMI for AP
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER) ) = (UINT32)((UINT8)CpuControl[i].Id << 24);
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER) ) = 0x00000400;
        if (IsItFamily15h)
            STALL_CPU(500);
#endif            
        // Enable interrupt after assigned task to AP.
        if(IntState)
            CPULib_EnableInterrupt();
        
        // Single Thread after AP being dispatched, remove it from list and record its number.
        // Non Single Thread must keep list not change for check if AP finished task.
        if(!SingleThread)
            continue;
        else
        {
            DispatchingAp = i;
            AllApTimerDispatchList[i] = FALSE;
        }

        // If Block mode wait until timeout or AP finished its task.
        if(IsBlock)
        {
            AllAPTimerCheckPending = FALSE;
            while ((ApGlobalData->RunningAps) && (!AllApTimeoutExpired))
                CpuPause();
            if(AllApTimeoutExpired)
                break;
            AllAPTimerCheckPending = TRUE;
        }
        else
        {
            // Single Thread and NonBlocking mode enable keep dispatching AP listed in list.
            if(SingleThread)
                AllApTimerDispatcher = TRUE;
            break;
        }

    }

    if(IsBlock)
    {
        // For case non single thread block mode.
        if(!SingleThread)
        {
            AllAPTimerCheckPending = FALSE;
            while ((ApGlobalData->RunningAps) && (!AllApTimeoutExpired))
                CpuPause();
            AllAPTimerCheckPending = TRUE;
        }

        // Call Timer again let it self kill.
        if(AllApTimerEventAlive)
        {
            AllAPTimerCheckPending = FALSE; 
			//speed up timer self kill.
            AllApTimeoutEnable = AllApTimeoutExpired = FALSE;
            AllApTimerHandler(NULL, NULL);
        }

        if (ApTerminatedTimeout)
            return EFI_TIMEOUT;
    }
    else
        AllAPTimerCheckPending = FALSE;
    return EFI_SUCCESS;
}

/**
    Execute function on Cpu.

    @param This 
    @param Procedure 
    @param ProcessorNumber 
    @param WaitEvent OPTIONAL
        - Event to signal when CPUs have completed executing.
    @param TimeoutInMicroSecs OPTIONAL  (Unsupported)
    @param ProcArguments OPTIONAL
        - Paramter to pass to function.

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiStartupThisAp(
  IN        EFI_MP_SERVICES_PROTOCOL    *This,
  IN        EFI_AP_PROCEDURE            Procedure,
  IN        UINTN                       ProcessorNumber,
  IN        EFI_EVENT                   WaitEvent OPTIONAL,
  IN        UINTN                       TimeoutInMicroSecs OPTIONAL,
  IN OUT VOID         *ProcArguments OPTIONAL,
  OUT BOOLEAN         *Finished
)
{
         AP_GLOBAL_DATA  *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
         BOOLEAN         IsBlock = TRUE;
volatile CPU_CONTROL     *CpuControl = ApGlobalData->CpuControl;
         UINT8           NumCpus = ApGlobalData->NumCpus;
         UINT8           Bsp = WhoIsBsp ((VOID *)ApGlobalData);
         UINTN           ExecutingCpu;
         UINT8           *RunningAps = (UINT8*)&ApGlobalData->RunningAps;
         EFI_STATUS      Status;
    
    if ((ProcessorNumber == Bsp) || (Procedure == NULL))
        return EFI_INVALID_PARAMETER;
    if (ProcessorNumber >= NumCpus)
        return EFI_NOT_FOUND;

    // Check if AP is disabled
    if (CpuControl[ProcessorNumber].Halted) 
        return EFI_INVALID_PARAMETER;

    //Not ready if Ap busy or it's in BSP dispatch list.
    if (!IsCpuIdle (ApGlobalData, (UINT8)ProcessorNumber) || ((AllApTimerDispatchList[(UINT8)ProcessorNumber]) && (AllApWaitEvent != NULL)))
        return EFI_NOT_READY;

    // Function can be called only by BSP
    EfiWhoAmI (This, &ExecutingCpu);
    if(ExecutingCpu != Bsp)
        return EFI_DEVICE_ERROR;


    DEBUG((DEBUG_INFO, "EfiStartupThisAp assigned ProcessorNumber %d\n", ProcessorNumber));
    EfiMpContext[ProcessorNumber].Function = Procedure;
    EfiMpContext[ProcessorNumber].Parameters = ProcArguments;

    //Create periodic timer event for CPUs.
    if (WaitEvent && (TimeoutInMicroSecs == 0))
    {
        UINT64      CpusWaiting00 = 0;
        UINT64      CpusWaiting64 = 0;
        EFI_STATUS  Status;
        if (ProcessorNumber < 64)
          CpusWaiting00 = Shl64(1, (UINT8)ProcessorNumber);
        else
          CpusWaiting64 = Shl64 (1, (UINT8)ProcessorNumber - 64);

        // If returns an error, execute, but BSP must wait for APs.
        // Before non-block works, both the Timer and the CPU architectural
        // protocols must be installed.
        Status = SetupCheckCpus(ApGlobalData, CpusWaiting00, CpusWaiting64, WaitEvent, Finished);
        if (!EFI_ERROR(Status))
            IsBlock = FALSE;
    }

    if (TimeoutInMicroSecs != 0)
    {
        Status = SetupThisApTimer (TimeoutInMicroSecs, WaitEvent, (UINT8)ProcessorNumber, ApGlobalData);
        if (!EFI_ERROR(Status))
            IsBlock = FALSE;
        WaitUntilZero32 (&CpuControl[ProcessorNumber].Function);

        if(WaitEvent && Finished)
            ThisApDb[ProcessorNumber].Finished = Finished;
        CPULib_LockByteInc(RunningAps);        // Increase number of CPUs running.

        CpuControl[ProcessorNumber].Context = &EfiMpContext[ProcessorNumber];      // Must set Context first.
        CpuControl[ProcessorNumber].Function = EfiMpFunction;    // This releases the CPU.
#if USE_AP_HLT        
        // Generate NMI for AP
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_HIGH_REGISTER)) = (UINT32)((UINT8)CpuControl[ProcessorNumber].Id << 24);
        *((UINT32*)(LOCAL_APIC_BASE | APIC_ICR_LOW_REGISTER)) = 0x00000400;
        if (IsItFamily15h)
            STALL_CPU(500);
#endif        

        if (IsBlock)
        {
            WaitUntilZero8 (RunningAps);
            if (WaitEvent)
            {
                if(Finished)
                    *Finished = TRUE;
                pBS->SignalEvent(WaitEvent);
            }
            return EFI_SUCCESS;
        }
        else
        {
            if (WaitEvent)
                return EFI_SUCCESS;
            while ((ApGlobalData->RunningAps != 0) && ((ThisApDb[ProcessorNumber].ApStatus & AP_TMOUT_EXP) != AP_TMOUT_EXP))
                CpuPause();
            if(ThisApDb[ProcessorNumber].ApStatus & AP_TMOUT_EXP)
            {
                ThisApDb[ProcessorNumber].ApStatus &= ~AP_TMOUT_EXP;
                return  EFI_TIMEOUT;
            }
        }
    }
    
    if (TimeoutInMicroSecs == 0)
        ExecuteFunctionOnCpu (ApGlobalData, (UINT8)ProcessorNumber, IsBlock, EfiMpFunction, &EfiMpContext[ProcessorNumber]);

    // If an error occurred on setting up non-blocking, signal event here.
    if (IsBlock && WaitEvent)
        pBS->SignalEvent(WaitEvent);

    return EFI_SUCCESS;
}

/**
    Switch BSP to another CPU.

        
    @param This 
    @param ProcessorNumber 
    @param EnableOldBSP (FALSE - disable current BSP)

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiSwitchBsp(
  IN    EFI_MP_SERVICES_PROTOCOL    *This,
  IN    UINTN                       ProcessorNumber,
  IN    BOOLEAN                     EnableOldBsp
)
{
    AP_GLOBAL_DATA  *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
    volatile        CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT8           OldBsp;
    UINTN           ExecutingCpu;
    BOOLEAN         CpuInterruptState;

    if (ProcessorNumber >= ApGlobalData->NumCpus)
        return EFI_NOT_FOUND;
    if (ProcessorNumber == ApGlobalData->Bsp)
        return EFI_INVALID_PARAMETER;
    // Check if AP is disabled
    if (CpuControl[ProcessorNumber].Halted)
        return EFI_INVALID_PARAMETER;
    if (!IsCpuIdle (ApGlobalData, (UINT8)ProcessorNumber) || ((AllApTimerDispatchList[(UINT8)ProcessorNumber]) && (AllApWaitEvent != NULL)))
        return EFI_NOT_READY;
    // Function can be called only by BSP
    EfiWhoAmI (This, &ExecutingCpu);
    if (ExecutingCpu != ApGlobalData->Bsp)
        return EFI_DEVICE_ERROR;
    
    CpuInterruptState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

    OldBsp = WhoIsBsp (ApGlobalData);
    DEBUG((DEBUG_INFO," OldBsp = %x Keep Enable %d\n", OldBsp, EnableOldBsp));
    DEBUG((DEBUG_INFO," Switch BSP to = %lx\n", ProcessorNumber));

    SwitchBsp (ApGlobalData, (UINT8)ProcessorNumber, SwitchBspProgramReg, (VOID*) ProcessorNumber);

    // Now, Old bsp is in wait loop, and New Bsp is executing here.

    if (!EnableOldBsp)
        HaltCpu(ApGlobalData, OldBsp, FALSE);

    if(CpuInterruptState)
        CPULib_EnableInterrupt();
    
    return EFI_SUCCESS;
}


/**
    (UNSUPPORTED) Send IPI to CPU.

        
    @param This 
    @param ProcessorNumber 
    @param VectorNumber 
    @param DeliveryMode 

         
    @retval EFI_UNSUPPORTED always unsupported

**/

EFI_STATUS
EFIAPI
EfiSendIPI(
  IN EFI_MP_SERVICES_PROTOCOL   *This,
  IN UINTN                      ProcessorNumber,
  IN UINTN                      VectorNumber,
  IN UINTN                      DeliveryMode
)
{
    // Only the CPU module should Send IPI.
    return EFI_UNSUPPORTED;
}

/**
    Enable or disable a AP

        
    @param This 
    @param ProcessorNumber 
    @param Enable 
    @param HealthState OPTIONAL

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiEnableDisableAp(
  IN    EFI_MP_SERVICES_PROTOCOL    *This,
  IN    UINTN                       ProcessorNumber,
  IN    BOOLEAN                     Enable,
  IN    UINT32                      *HealthState OPTIONAL
)
{
         AP_GLOBAL_DATA *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
volatile CPU_CONTROL    *CpuControl = ApGlobalData->CpuControl;
         UINTN          ExecutingCpu;

    if (ProcessorNumber >= ApGlobalData->NumCpus) 
        return EFI_NOT_FOUND;

    if (ProcessorNumber == ApGlobalData->Bsp) 
        return EFI_INVALID_PARAMETER;
        
    // Function can be called only by BSP
    EfiWhoAmI (This, &ExecutingCpu);
    if (ExecutingCpu != ApGlobalData->Bsp)
        return EFI_DEVICE_ERROR;
    
    if (!IsCpuIdle (ApGlobalData, (UINT8)ProcessorNumber) || ((AllApTimerDispatchList[(UINT8)ProcessorNumber]) && (AllApWaitEvent != NULL)))
        return EFI_UNSUPPORTED;

    if (!Enable)
    {
        DEBUG((DEBUG_INFO, "EfiEnableDisableAp Disable Cpu number: %x\n", ProcessorNumber));
        if (!CpuControl[ProcessorNumber].Halted)
        {
            UINT8   HaltedCpus = ApGlobalData->HaltedCpus;

            HaltCpu (ApGlobalData, (UINT8)ProcessorNumber, FALSE);
            while (HaltedCpus == ApGlobalData->HaltedCpus)
                CpuPause();
        }
        // If AP disabled (halted) already - do nothing
    }
    else
    {
        DEBUG((DEBUG_INFO, "EfiEnableDisableAp Enable Cpu number: %x\n", ProcessorNumber));
        if(CpuControl[ProcessorNumber].Halted)
            RestartAp (ApGlobalData, (UINT8)ProcessorNumber);
        // If AP enabled already - do nothing
    }

    if (HealthState != NULL)
        *HealthState = (UINT32)PROCESSOR_HEALTH_STATUS_BIT;     // Healthy enabled/Disabled

    return EFI_SUCCESS;
}


/**
    Return assigned number to CPU calling this.

        
    @param This 
    @param ProcessorNumber 

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
EfiWhoAmI(
    IN EFI_MP_SERVICES_PROTOCOL *This,
    OUT UINTN   *ProcessorNumber
)
{
    AP_GLOBAL_DATA *ApGlobalData = ((PRIVATE_MP_SERVICES *)This)->ApGlobalData;
    volatile CPU_CONTROL *CpuControl = ApGlobalData->CpuControl;
    UINT32  Id = MemRead32((UINT32*)(APIC_BASE + APIC_ID_REGISTER)) >> 24;
    UINT8   NumCpu = ApGlobalData->NumCpus;
    UINTN   i;

    if (ProcessorNumber == NULL)
        return EFI_INVALID_PARAMETER;
    // Search CPU ID that matches this CPU.
    for (i = 0; i < NumCpu; ++i)
    {
        if (CpuControl[i].Id == Id)
        {
            *ProcessorNumber = i;
            return EFI_SUCCESS;
        }
    }

    return EFI_UNSUPPORTED;
}

PRIVATE_MP_SERVICES gPrivateMpServices = {
    {
        EfiGetNumberOfProcessors,
        EfiGetProcessorInfo,
        EfiStartupAllAps,
        EfiStartupThisAp,
        EfiSwitchBsp,
        EfiEnableDisableAp,
        EfiWhoAmI
    },
    0
};

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
