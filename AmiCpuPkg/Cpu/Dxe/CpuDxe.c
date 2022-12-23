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

/** @file CpuDxe.c
    Installs CPU Architectural Protocol and initializes the
    processor interrupt vector table. The CPU Architectural
    Protocol enables/disables/get state of interrupts, set
    memory range cache type, and installs/uninstalls
    interrupt handlers.

**/

#include "CpuDxe.h"
#include <CpuBoard.h>
#include <Dxe.h>
#include <ffs.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "CpuCspLib.h"
#include <AmiHobs.h>
#include "CpuInterfaces.h"
#include <Protocol/AmiCpuInfo.h>
#include <Protocol/Variable.h>
#include <Protocol/MpService.h>
#include <Setup.h>
#ifdef AMI_PEI_DEBUG_SUPPORT
  #include "PeiDbgDxeCpuLib.h"
#endif
#include <CpuSetupData.h>
#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
#include <Protocol/LegacyBiosExt.h>
#endif
#include "AMD.h"
#include "Library/CcxPstatesLib.h"
#include <Library/DebugLib.h>
#include <Library/UefiCpuLib.h>
#include <Library/AmiShadowLib.h>

EFI_GUID gAmiCpuinfoHobGuid = AMI_CPUINFO_HOB_GUID;
EFI_GUID gEfiSetupGuid = SETUP_GUID;

CHAR16  CpuS3ResumeVariable[] = CPU_S3_RESUME_VARIABLE;
CHAR16  SetupVariable[] = L"Setup";

CPUINFO_HOB             *CpuInfoHob;
VOID                    *FirstHob;
AMI_CPU_INFO            *gAmiCpuInfo;
CPU_S3_RESUME           *CpuS3Resume;

volatile UINT8  AmiCpuInfoSemaphore = 0;
UINT8           NumCpus = 0;
UINT64          TimerPeriod = 0;
UINT32          NumBoostStates = 0;
BOOLEAN         IsFidSupported = FALSE;
BOOLEAN         IsVidSupported = FALSE;
UINTN           Frequency;
UINTN           VoltageInuV;
UINT32          VoltageInmV;
UINT8           CoreCnt = 0;   // this value will be update at the end of DxeInitializeCPU
BOOLEAN         IsItFamily15h;
SETUP_DATA      SetupData;
BOOLEAN         IsSetupDataValid;
#ifdef EFIx64
UINT16          *IrqRuntimeHandler;
#else
UINT8           *IrqRuntimeHandler;
#endif
INTR_GATE_DESC  *gIdt;

VOID            *MpData;
extern MTRR_SETTINGS   *gMtrrTable;

#pragma pack(1)
typedef struct {
    UINT8   PushOp;
    UINT32  Interrupt;
    UINT8   PushEaxOp;
#ifdef EFIx64
    UINT8   Ext64Op;
#endif
    UINT8   MovEaxOp;
    VOID    *JmpAddr;
    UINT16  JmpOp;          //Jmp ebx/rbx
} INT_ENTRY_POINT;
#pragma pack()

INT_ENTRY_POINT     *IntEntryPoints;

INT_ENTRY_POINT IntEntryTemplate = 
{
    0x68,           //push Int
    0,              //Int
    0x50,           //push eax/rax
#ifdef EFIx64
    0x48,           //Extended Opcode
#endif
    0xB8,           //Mov eax,
    0,              //JmpAddr
    0xE0FF          //Jmp ebx/rbx
};

//This extern is for a table of offset of interrupt routines in Amd64Mp.asm.
extern VOID         *InterruptHandlerStart;
extern UINT32       InterruptHandlerSize;
extern UINT32       InterruptHandlerTblFixup;
// These externs define structures to initialize cache descriptors
extern CPU_CACHE_TABLE  CacheTable[];
extern UINT8            CacheSize;

EFI_STATUS      InitInterrupts();
VOID 	        InterruptHandlerHalt(EFI_EXCEPTION_TYPE Exception,EFI_SYSTEM_CONTEXT Context);
#if USE_AP_HLT
VOID            InterruptHandlerRet(EFI_EXCEPTION_TYPE Exception,EFI_SYSTEM_CONTEXT Context);
VOID            AsmIret(VOID);
#endif
VOID            SetCpuS3ResumeData();
VOID TempGPInterruptHandler(EFI_EXCEPTION_TYPE Exception,EFI_SYSTEM_CONTEXT Context);

CACHE_DESCRIPTOR_INFO CacheDescTable[] = {
    0x2C, 1, 0,   32,  8,
    0x30, 1, 1,   32,  8,
    0x60, 1, 0,   16,  8,
    0x62, 1, 0,   32,  8,
    0x66, 1, 0,    8,  4, 
    0x67, 1, 0,   16,  4,
    0x68, 1, 0,   32,  4,
    0x69, 1, 0,   64,  4,
    0x39, 2, 3,  128,  4,
    0x3A, 2, 3,  192,  6,
    0x3B, 2, 3,  128,  2,
    0x3C, 2, 3,  256,  4,
    0x3D, 2, 3,  384,  6,
    0x3E, 2, 3,  512,  4,
    0x78, 2, 3, 1024,  4,
    0x79, 2, 3,  128,  8,
    0x7A, 2, 3,  256,  8,
    0x7B, 2, 3,  512,  8,
    0x7C, 2, 3, 1024,  8,
    0x7D, 2, 3, 2048,  8,
    0x7F, 2, 3,  512,  2,
    0x86, 2, 3,  512,  4,
    0x87, 2, 3, 1024,  8,
    0x40, 3, 0,    0,  0,   // No L2 cache, or if L2 cache, then no L3 cache.
    0x22, 3, 3,  512,  8,
    0x23, 3, 3, 1024,  8,
    0x25, 3, 3, 2048,  8,
    0x29, 3, 3, 4096,  8,
    0x46, 3, 3, 4096,  4,
    0x47, 3, 3, 8192,  8,
    0x4A, 3, 3, 4096,  8,
    0x4B, 3, 3, 6144, 12,
    0x4C, 3, 3, 8192, 16
};
#define CACHE_DESCRIPTOR_INFO_TABLE_SIZE sizeof (CacheDescTable) / sizeof (CACHE_DESCRIPTOR_INFO)

CACHE_DESCRIPTOR_INFO ZeroCacheDesc = {0, 0, 0, 0, 0};

#define  PCI_ADDRESS(bus, dev, func, reg) \
            ((UINT64) ( (((UINT8)bus) << 16) + (((UINT8)dev) << 11) + \
            (((UINT8)func) << 8) + ((UINT8)reg) )) & 0x00000000ffffffff

/**
    Read the PCI Register

    @param Address :(UINT32) ( (((UINT32)bus) << 24) + (((UINT32)dev) << 19) \
        + (((UINT32)func) << 16) + ((UINT32)reg) )
    @param ExtAccess : TRUE for extended access, FALSE is for normal access

    @retval UINT32 return value from the PCI Register.

**/

UINT32
NbReadPci32(
  IN    UINT32  Address,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  Value32;
    UINT32  AddrCf8 = (1 << 31) + (Address & 0xFFFF00) + (Address & 0xFC);

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        AddrCf8 |= 0x1000000;

    IoWrite32(0xCF8, AddrCf8);
    Value32 = IoRead32(0xCFC);
    return Value32;
}

/**
    Read a CMOS byte

        
    @param Index 

         
    @retval UINT8 Value

**/

UINT8
EfiReadCmosByte(
  IN    UINT8   Index
)
{
    if (Index & 0x80)
    {
        // Upper CMOS Read
        IoWrite8 (0x72, Index);
        return IoRead8 (0x73);
    }
    else
    {
        // Lower CMOS Read
        IoWrite8 (0x70, Index);
        return IoRead8 (0x71);
    }
}

/**
    From entry in Cache Descriptor Table from Descriptor.

        
    @param Desc 

         
    @retval CACHE_DESCRIPTOR_INFO cache information

**/

CACHE_DESCRIPTOR_INFO
*GetPtrCacheDescr(
  IN    UINT8   Desc
)
{
    UINT8   i;
    for(i = 0; i < CACHE_DESCRIPTOR_INFO_TABLE_SIZE; ++i)
        if (CacheDescTable[i].Desc == Desc)
            return &CacheDescTable[i];
    return 0;
}

DESCRIPTOR_TABLE pIdt, pGdt;

// This is a table of pointers to installed interrupt handlers.
// It will be initialized as NULL, meaning no interrupt handler installed.
EFI_CPU_INTERRUPT_HANDLER   *InterruptPtrTable;

//This will be copied to runtime memory.
UINT64 GDT[] = {
    0,                  //NULL_SEL
    0x00CF93000000FFFF, //DATA_SEL 8, Data 0-ffffffff 32 bit
    0x00CF9B000000FFFF, //CODE_SEL 10h, CODE 0-ffffffff 32 bit

// We only need this because Intel DebugSupport driver
// (RegisterPeriodicCallback funciton) assumes that selector 0x20 is valid
// The funciton sets 0x20 as a code selector in IDT
    0x00CF93000000FFFF, // YET_ANOTHER_DATA_SEL, 0x18, Data 0-ffffffff 32 bit	
    0x00CF9B000000FFFF, //YET_ANOTHER_CODE_SEL, 0x20, CODE 0-ffffffff 32 bit
#ifdef EFIx64
    0,                  //Spare
    0x00CF93000000FFFF, //64 Data.
    0x00AF9B000000FFFF, //64 Code
    0                   //Spare
#endif
};

/**
    Allocate memory in runtime and copy data.

        
    @param Src 
    @param Size 

         
    @retval VOID return the runtime address

**/

VOID
*CpyToRunTime(
  IN    VOID    *Src,
  IN    UINTN   Size
)
{
	EFI_STATUS	Status;
	VOID		*Dest;

    // Align to 16.
    Status = pBS->AllocatePool (EfiACPIMemoryNVS, Size + 16, &Dest);
    ASSERT_EFI_ERROR (Status);

    Dest = (VOID*)(((UINTN)Dest + 0xF) & ~(UINTN)0xF);
    MemCpy (Dest, Src, Size);
    return Dest;
}

/**
    Handler executed for ReadyToBoot

        
    @param Event 
    @param Context 

         
    @retval VOID

**/

VOID
ExecuteAtReadyToBoot(
  IN    EFI_EVENT   Event,
  IN    VOID        *Context
)
{
    UINT8   Value8;

#if (ENABLE_ROM_CACHE_IN_DXE == 1)
    WriteMsr(MTRR_PHYS_MASK_7, 0);
    WriteMsr(MTRR_PHYS_BASE_7, 0);
#endif
    SynchronizeMtrrs (pBS);
    SetCpuS3ResumeData();

    IoWrite8 (0x72, PcdGet8 (PcdCmosAgesaSpecified));
    Value8 = IoRead8 (0x73);    // Read from CMOS
    Value8 |= BIT1; 
    IoWrite8 (0x73, Value8);    // Save to CMOS

    pBS->CloseEvent(Event);
}

/**
    The last boot point on UEFI boot path in CPU code.
    This will be the last time we sync the MSRs on all cores before
    booting to UEFI OS.

        
    @param Event 
    @param Context 
         
    @retval VOID

**/

VOID
EFIAPI
CpuBootOnExitBootService(
  IN    EFI_EVENT   Event,
  IN    VOID        *Context
)
{
    UINT16  i;

#if (ENABLE_ROM_CACHE_IN_DXE == 1)
    WriteMsr(MTRR_PHYS_MASK_7, 0);
    WriteMsr(MTRR_PHYS_BASE_7, 0);
#endif
    SynchronizeMtrrs(pBS);

    CPULib_DisableInterrupt();

    //The interrupts are programmed to a default runtime handler. This is because
    //earlier OSes that don't support multi-processors will not take control of APs.
    //If this happens, and the AP gets an exception, such as the machine check
    // exception, the system will hang or reset.
    for (i = 0; i < 256; ++i)
    {
        gIdt[i].LoOffset = (UINT16)IrqRuntimeHandler;
        gIdt[i].HiOffset = (UINT16)((UINT32)IrqRuntimeHandler >> 16);
	}

    HaltAllAps (MpData, TRUE);  // If legacy, CSM halts them.
    pBS->CloseEvent(Event);
}

/**
    The last boot point on legacy boot path in CPU code.
    This will be the last time we sync the MSRs on all cores before
    booting to legacy OS.

        
    @param Event 
    @param Context 
         
    @retval VOID

**/

VOID
CpuBootOnLegacyBoot(
    IN EFI_EVENT Event,
    IN VOID *Context)
{
	SynchronizeMtrrs(pBS);

    pBS->CloseEvent(Event);
}

/**
    Calculate CPU time period.

        
    @param VOID

         
    @retval UINT64 Timer Period
**/

UINT64
CalculateTimerPeriod(
    VOID
)
{
	UINT64	Timer1;
	UINT64	Timer2;

	EFI_TPL	OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

	Timer1 = ReadRtdsc();

	pBS->Stall(DELAY_CALCULATE_CPU_PERIOD);

	Timer2 = ReadRtdsc();

	pBS->RestoreTPL(OldTpl);

    return Div64 (DELAY_CALCULATE_CPU_PERIOD * (UINT64)1000000000,
            (UINT32)(Timer2 - Timer1), NULL);    // 50us * 10E15  femtosec;
}

/**
    Enable CPU Interrupts.

        
    @param This 

         
    @retval EFI_STATUS EFI_SUCCESS (Always)
**/

EFI_STATUS
EFIAPI
EfiCpuEnableInterrupt (
  IN    EFI_CPU_ARCH_PROTOCOL   *This
)
{
	CPULib_EnableInterrupt ();
    return EFI_SUCCESS;
}


/**
    Disable CPU Interrupts

        
    @param This 

         
    @retval EFI_STATUS EFI_SUCCESS (Always)

**/

EFI_STATUS
EFIAPI
EfiCpuDisableInterrupt (
  IN    EFI_CPU_ARCH_PROTOCOL   *This
)
{
	CPULib_DisableInterrupt ();
    return EFI_SUCCESS;
}


/**
    Return State (Disable/Enable) CPU Interrupts.

        
    @param This 
    @param State *State=FALSE if Disable.

         
    @retval EFI_STATUS EFI_SUCCESS (Always)
**/

EFI_STATUS
EFIAPI
EfiCpuGetInterruptState (
  IN    EFI_CPU_ARCH_PROTOCOL   *This,
  OUT   BOOLEAN                 *State
)
{
	*State = CPULib_GetInterruptState ();
    return EFI_SUCCESS;
}

/**
    Send INIT to the CPU.

        
    @param This 
    @param InitType 

         
    @retval EFI_STATUS Never returns.

**/

EFI_STATUS
EFIAPI
EfiCpuInitialization (
  IN    EFI_CPU_ARCH_PROTOCOL   *This,
  IN    EFI_CPU_INIT_TYPE       InitType
)
{
	IoWrite8 (0x64, 0xFE);  // Reset system using keyboard controller.
    WaitForever();  // Wait until reset.
    return EFI_DEVICE_ERROR;
}

/**
    Install or Uninstall Interrupt Handler.

        
    @param This 
    @param InterruptType 
    @param InterruptHandler 

         
    @retval EFI_SUCCESS Interrupt handler was uninstalled/installed.
    @retval EFI_ALREADY_STARTED Attempt to install an Interrupt Handler
        when one is already installed.
    @retval EFI_INVALID_PARAMETER Attempt to uninstall an Interrupt Handler
        when one is not installed.
    @retval EFI_UNSUPPORTED Interrupt Type not supported.

**/

EFI_STATUS
EFIAPI
EfiCpuRegisterInterruptHandler (
  IN    EFI_CPU_ARCH_PROTOCOL       *This,
  IN    EFI_EXCEPTION_TYPE          InterruptType,
  IN    EFI_CPU_INTERRUPT_HANDLER   InterruptHandler
)
{
    if ((UINTN)InterruptType > 255)
        return EFI_UNSUPPORTED;
    if (InterruptHandler != NULL && InterruptPtrTable[InterruptType] != NULL)
        return EFI_ALREADY_STARTED;
    if (InterruptHandler == NULL && InterruptPtrTable[InterruptType] == NULL)
        return EFI_INVALID_PARAMETER;

    InterruptPtrTable[InterruptType] = InterruptHandler;

#ifdef	AMI_PEI_DEBUG_SUPPORT
    IsItPEIDebugIRQHandlerToHookup(InterruptType,InterruptHandler);
#endif

    return EFI_SUCCESS;
}

/**
    For a CPU timer, return its current value.

        
    @param This 
    @param TimerIndex 
    @param CurTimerValue 
    @param CurTimerPeriod OPTIONAL

         
    @retval EFI_SUCCESS The time value is returned.
    @retval EFI_INVALID_PARAMETER TimerIndex is greater than 0.
        Only timer exists.
    @retval EFI_INVALID_PARAMETER TimerValue is NULL.

**/

EFI_STATUS EFIAPI EfiCpuGetTimerValue (
  IN    EFI_CPU_ARCH_PROTOCOL   *This,
  IN    UINT32                  TimerIndex,
  OUT   UINT64                  *CurTimerValue,
  OUT   UINT64                  *CurTimerPeriod OPTIONAL
)
{
    if (TimerIndex > 0)
        return EFI_INVALID_PARAMETER;
    if (CurTimerValue == NULL)
        return EFI_INVALID_PARAMETER;
    if (CurTimerPeriod != NULL)
    {
        if (!TimerPeriod)
            TimerPeriod = CalculateTimerPeriod();
        *CurTimerPeriod = TimerPeriod;
    }

    *CurTimerValue = ReadRtdsc();

    return EFI_SUCCESS;
}

/**
    Install Interrupt Handlers for 0 to 19, to the routine
    InterruptHalt. Initialize the interrupt descriptors.
    Execute assembly instruction LIDT.

        
    @param VOID

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
InitInterrupts(
    VOID
)
{
    UINT32          i;
    UINT16      	Segment;
	VOID			*InterruptHandler;
    EFI_STATUS		Status;

#ifdef	AMI_PEI_DEBUG_SUPPORT
	// Porting to support PEI Debugger
	// Obtain info about Exception and INT handlers use by PEI Debugger
	SetupPEIDebuggerExceptionHandlers();
#endif

    // Allocate memory for addresses of interrupt Handlers.
    Status = pBS->AllocatePool (EfiACPIMemoryNVS, 256 * sizeof (EFI_CPU_INTERRUPT_HANDLER), 
                   (VOID*)&InterruptPtrTable);
    ASSERT_EFI_ERROR (Status);

    MemSet (InterruptPtrTable, 256 * sizeof (EFI_CPU_INTERRUPT_HANDLER), 0);    // Clear addresses.

    // Allocate memory for addresses of interrupt Handlers.
    Status = pBS->AllocatePool (EfiACPIMemoryNVS, sizeof (*IrqRuntimeHandler),
                   (VOID*)&IrqRuntimeHandler);
    ASSERT_EFI_ERROR(Status);

#ifdef EFIx64
    *IrqRuntimeHandler = 0xCF48;    // IRET
#else
    *IrqRuntimeHandler = 0xCF;  // IRET
#endif

    // InterruptHandler must be set to runtime address before copying interrupt handler.
    InterruptHandler = CpyToRunTime (InterruptHandlerStart, InterruptHandlerSize);
    *(VOID**)((UINT8*)InterruptHandler + InterruptHandlerTblFixup) = InterruptPtrTable;
    IntEntryTemplate.JmpAddr = InterruptHandler;

    // Allocate interrupt entry points and copy.
    // Alocate space for Interrupt Descriptor Table. 256 entries/8 bytes.
    Status = pBS->AllocatePool (EfiACPIMemoryNVS, 256 * sizeof (INT_ENTRY_POINT), &IntEntryPoints);
    ASSERT_EFI_ERROR (Status);
    
    for (i = 0; i < 256; ++i)
    {
        IntEntryTemplate.Interrupt = i;
        IntEntryPoints[i] = IntEntryTemplate;
    }

    // Alocate space for Interrupt Descriptor Table. 256 entries/8 bytes.
    Status = pBS->AllocatePool (EfiACPIMemoryNVS, 256 * sizeof (*gIdt), &gIdt);
    ASSERT_EFI_ERROR (Status);

    for (i = 0; i <= 19; ++i)
        EfiCpuRegisterInterruptHandler(0, i, InterruptHandlerHalt);

#if USE_AP_HLT    
    // INT2 handler
    EfiCpuRegisterInterruptHandler(0,2,InterruptHandlerRet);
#endif    
    Segment = GetCsSegment();

    for (i = 0; i < 256; ++i)
    {
        UINTN   IntHndlrAddr = (UINTN)&IntEntryPoints[i];
        gIdt[i].LoOffset = *(UINT16*)&IntHndlrAddr;
        gIdt[i].HiOffset = *(((UINT16*)&IntHndlrAddr) + 1);
#if USE_AP_HLT
        if(i == 2){
            UINTN AsmIretAddr = (UINTN)AsmIret;
            gIdt[i].LoOffset=*(UINT16*)&AsmIretAddr;
            gIdt[i].HiOffset=*(((UINT16*)&AsmIretAddr)+1);
        }
#endif        
        gIdt[i].Segment = Segment;
        gIdt[i].DescBits = 0x8E00;  // Present = 1, DPL = 0, D = 1 (32bit)
#ifdef EFIx64
        gIdt[i].Hi32Offset = 0;
        gIdt[i].Rsv = 0;
#endif
#ifdef	AMI_PEI_DEBUG_SUPPORT
		FixUpPEIDebuggerExceptionHandlers((IDTEntry_T*)gIdt,i);
#endif
    }

    pIdt.Base = (UINT32)(UINTN)gIdt;

#ifdef EFIx64
    pIdt.Limit = 16 * 256 - 1;
#else
    pIdt.Limit = 8 * 256 - 1;
#endif

    return EFI_SUCCESS;
}

/**
    CPU exception

        
    @param Exception 
    @param Context 

         
    @retval VOID

**/

VOID
InterruptHandlerHalt(
  IN    EFI_EXCEPTION_TYPE  Exception,
  IN    EFI_SYSTEM_CONTEXT  Context
)
{
	checkpoint ((UINT8)Exception);

    DEBUG ((DEBUG_INFO, "ERROR: CPU Exception %X\n", Exception));

    DEBUG ((EFI_D_ERROR, "!!!! X64 Exception Type - %016lx !!!!\n", Exception));

    DEBUG ((EFI_D_ERROR, "RIP - %016lx, CS - %016lx, RFLAGS - %016lx\n",
           Context.SystemContextX64->Rip,
           Context.SystemContextX64->Cs,
           Context.SystemContextX64->Rflags));

    DEBUG ((EFI_D_ERROR, "RAX - %016lx, RCX - %016lx, RDX - %016lx\n",
           Context.SystemContextX64->Rax,
           Context.SystemContextX64->Rcx,
           Context.SystemContextX64->Rdx));

    DEBUG ((EFI_D_ERROR, "RBX - %016lx, RSP - %016lx, RBP - %016lx\n",
           Context.SystemContextX64->Rbx,
           Context.SystemContextX64->Rsp,
           Context.SystemContextX64->Rbp));

    DEBUG ((EFI_D_ERROR, "RSI - %016lx, RDI - %016lx\n",
           Context.SystemContextX64->Rsi,
           Context.SystemContextX64->Rdi));

    DEBUG ((EFI_D_ERROR, "R8 - %016lx, R9 - %016lx, R10 - %016lx\n",
           Context.SystemContextX64->R8,
           Context.SystemContextX64->R9,
           Context.SystemContextX64->R10));

    DEBUG ((EFI_D_ERROR, "R11 - %016lx, R12 - %016lx, R13 - %016lx\n",
           Context.SystemContextX64->R11,
           Context.SystemContextX64->R12,
           Context.SystemContextX64->R13));

    DEBUG ((EFI_D_ERROR, "R14 - %016lx, R15 - %016lx\n",
           Context.SystemContextX64->R14,
           Context.SystemContextX64->R15));

    DEBUG ((EFI_D_ERROR, "DS - %016lx, ES - %016lx, FS - %016lx\n",
           Context.SystemContextX64->Ds,
           Context.SystemContextX64->Es,
           Context.SystemContextX64->Fs));

    DEBUG ((EFI_D_ERROR, "GS - %016lx, SS - %016lx\n",
           Context.SystemContextX64->Gs,
           Context.SystemContextX64->Ss));

    DEBUG ((EFI_D_ERROR, "GDTR - %016lx %016lx, LDTR - %016lx\n",
           Context.SystemContextX64->Gdtr[0],
           Context.SystemContextX64->Gdtr[1],
           Context.SystemContextX64->Ldtr));

    DEBUG ((EFI_D_ERROR, "IDTR - %016lx %016lx, TR - %016lx\n",
           Context.SystemContextX64->Idtr[0],
           Context.SystemContextX64->Idtr[1],
           Context.SystemContextX64->Tr));

    DEBUG ((EFI_D_ERROR, "CR0 - %016lx, CR2 - %016lx, CR3 - %016lx\n",
           Context.SystemContextX64->Cr0,
           Context.SystemContextX64->Cr2,
           Context.SystemContextX64->Cr3));

    DEBUG ((EFI_D_ERROR, "CR4 - %016lx, CR8 - %016lx\n",
           Context.SystemContextX64->Cr4,
           Context.SystemContextX64->Cr8));

    DEBUG ((EFI_D_ERROR, "DR0 - %016lx, DR1 - %016lx, DR2 - %016lx\n",
           Context.SystemContextX64->Dr0,
           Context.SystemContextX64->Dr1,
           Context.SystemContextX64->Dr2));

    DEBUG ((EFI_D_ERROR, "DR3 - %016lx, DR6 - %016lx, DR7 - %016lx\n",
           Context.SystemContextX64->Dr3,
           Context.SystemContextX64->Dr6,
           Context.SystemContextX64->Dr7));

    // HltCpu();
    CpuDeadLoop ();
}

/**
    Interrup function for AP halt.

        
    @param Exception 
    @param Context

**/
#if USE_AP_HLT
VOID InterruptHandlerRet(
    IN EFI_EXCEPTION_TYPE Exception,
    IN EFI_SYSTEM_CONTEXT Context)
{
    AsmIret();
}
#endif
/**
    Protocol function to get Cpu Info.

        
    @param This 
    @param Cpu 
    @param Info 

         
    @retval EFI_STATUS return the EFI status

**/
EFI_STATUS EFIAPI GetCpuInfo(
  IN    AMI_CPU_INFO_PROTOCOL   *This,
  IN    UINTN                   Cpu,
  OUT   AMI_CPU_INFO            **Info
)
{
    if (Cpu >= NumCpus)
        return EFI_INVALID_PARAMETER;
    *Info = &gAmiCpuInfo[Cpu];

    return EFI_SUCCESS;
}

/**
    This function executed on AP core and reads SMM Base MSR

        
    @param pSmmBase pointer to SmmBase value

         
    @retval EFI_STATUS return EFI_INVALID_PARAMETER if input pointer NULL, 
        EFI_SUCCESS in all other cases.

**/

EFI_STATUS
ApGetSmmBase (
  IN    VOID    *SmmBase
)
{
    if (SmmBase == NULL)
        return EFI_INVALID_PARAMETER;
    if (IsItBsp())
        return EFI_SUCCESS;
    
    *((UINTN*)SmmBase) = ReadMsr (AMD_MSR_SMM_BASE);
    return  EFI_SUCCESS;
}


/**
    Store S3 resume data in memory, and store its pointer in NVRAM.
    Halt All Aps

        
    @param VOID

         
    @retval VOID

**/

VOID
SetCpuS3ResumeData(
    VOID
)
{
	EFI_STATUS			Status;
    UINT8               i;
	UINT64				MsrSysCfg64;
    EFI_MP_SERVICES_PROTOCOL    *MpServices;
    UINTN                       NumCpus=0;
    UINTN                       NumEnCpus=0;

    Status = pBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    if (Status == EFI_SUCCESS)
    {
        Status = MpServices->GetNumberOfProcessors (MpServices, &NumCpus, &NumEnCpus);
        for (i = 1; i < NumEnCpus; i++)
        {
            // Execute on all running APs
            Status = MpServices->StartupThisAP (MpServices, (EFI_AP_PROCEDURE)
                                  ApGetSmmBase, i, NULL, 0,
                                  (VOID*)&(CpuS3Resume->SmmBase.SmmBaseVal[i]), NULL);
        }
    }
    // Get SmmBase for BSP
    CpuS3Resume->SmmBase.SmmBaseVal[0] = ReadMsr (AMD_MSR_SMM_BASE);

    CpuS3Resume->Idt = pIdt;

    MsrSysCfg64 = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSysCfg64 | (3 << MtrrFixDramEnBit));
    ASSERT (sizeof (MtrrRegs) / sizeof (UINT32) == NUM_OF_MTRR_SAVED);

    for(i = 0; i < NUM_OF_MTRR_SAVED; i++)
    {
        CpuS3Resume->MtrrValue[i].Msr = MtrrRegs[i];
        CpuS3Resume->MtrrValue[i].Value = (MtrrRegs[i] == MSR_SYS_CFG) ? MsrSysCfg64 :
                                   ReadMsr(MtrrRegs[i]);
    }
	WriteMsr(MSR_SYS_CFG, MsrSysCfg64);

    Status = pRS->SetVariable (CpuS3ResumeVariable, &gCpuS3ResumeGuid,
                   EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                   sizeof (UINT32), &CpuS3Resume);
}

/**
    Write a value into the PCI register indicated

        
    @param Address 
    @param Value 
    @param ExtAccess 

         
    @retval VOID

**/

VOID
AMDPciConfigWrite(
  IN    UINT32  Address,
  IN    UINT32  Value,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = (1 << 31) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 16) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 11) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register);

    PciAddress &= 0xFFFFFFFC;
    if(ExtAccess)   // If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress |= 0x1000000;
    IoWrite32 (0xCF8, PciAddress);  // Select the register to write
    IoWrite32 (0xCFC, Value);   // Write the Value
}

/**
    Read a value from the PCI register indicated

        
    @param Address 
    @param ExtAccess 

         
    @retval UINT32 Value

**/
UINT32
AMDPciConfigRead(
  IN    UINT32  Address,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = (1 << 31) +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus      << 16 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device   << 11 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8  )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register       );

    PciAddress &= 0xFFFFFFFC;   // Dword Align

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress |= 0x1000000;

    IoWrite32 (0xCF8, PciAddress);
    return IoRead32 (0xCFC);    // Return the read value
}

// [Fam15 only]
/**
    Get CPU voltage

        
    @param cpuVid 

         
    @retval UINT32 Value

**/

UINT32
GetCpuVoltage(
  IN    UINT8   CpuVid
)
{
    UINT32  Address32;
    UINT32  Buffer32;
    UINT32  v_x10000;

    Address32 = (UINT32)AMD_PCI_CFG_ADDRESS_S3 (0, (0), AMD_K8_MISC_FUNC, AMD_K8_nF3_PWR_CTRL_MISC);
    Buffer32 = AMDPciConfigRead (Address32, FALSE);

    /* Check pvi/svi mode */
    if (Buffer32 & 0x00000100)
    {
        // PVI Mode PVIFlag = TRUE;
        /* Set cpuVid value in case CPU is in PVI mode */
        if (CpuVid > 0x5D)
            CpuVid = 0x3F;
        else if (CpuVid > 0x3E)
            CpuVid -= 0x1F;
        else
            CpuVid = (CpuVid >> 1);

        /* PVI Encoding */
        if (CpuVid >= 0x20)
            v_x10000 = 7625L - (125L * (CpuVid - 0x20));
        else
            v_x10000 = 15500L - (250L * CpuVid);
    }
    else
    {
        // SVI Mode
        if (CpuVid > 0x7C)
            v_x10000 = 0;
        else
            v_x10000 = 15500L - (125L * CpuVid);
    }

    return v_x10000;
}

/**
    This is an initialization routine for BSP and all APs.
    BSP has CPU number 0, and APs > 1. After init, BSP number may change.

        
    @param Cpu - number associated with CPU.
    @param Context 

         
    @retval VOID

**/

VOID
InitializeCpu(
  IN    UINT8           Cpu,
  IN    volatile VOID   *Context
)
{
    AMI_CPU_INFO            *AmiCpuInfo = &gAmiCpuInfo[Cpu];
    UINT32                  CpuSignature;
    UINT64                  CpuFeatureInfo;
    UINT32                  FeatureFlagsEdx;
    UINT32                  FeatureFlagsEcx;
    UINT32                  RegEbx;
    CHAR8                   *BrandString;
    UINT8                   i; 
    UINT8                   j;
    UINT8                   Associativity;
    UINT64                  TimerPeriod;
    EFI_STATUS              Status;
    REGISTER_TABLE          Reg;
    CACHE_DESCRIPTOR_INFO   *CacheInfo;
    CPUINFO                 *CpuInfo = (CPUINFO*)&CpuInfoHob->Cpuinfo[Cpu];
    UINT64                  Msr64Data;

    CPULib_LoadIdt (&pIdt);  // Load idt address for each cpu in memory

    // Need semaphore lock here for allocating memory
    WaitForSemaphore (&AmiCpuInfoSemaphore);

    if (!IsItFamily15h)
        InitializeFloatingPointUnits();

    // Set SVM and NX for Family 17
    if ((!IsItFamily15h) && (IsSetupDataValid))
    {
        Msr64Data = ReadMsr(0xC0010114);
        Msr64Data &= ~0x0010;       // default is enabled
        if (SetupData.SVM_MODE == 0)
            Msr64Data |= 0x0010;

        Msr64Data |= 0x08;          // Set SVM lock
        WriteMsr(0xC0010114, Msr64Data);

        if (SetupData.NX_MODE == 0)
        {
            Msr64Data = ReadMsr(0xC0011005);
            Msr64Data &= ~0x100000;     // Disable NX function, bit20
            WriteMsr(0xC0011005, Msr64Data);
        }
    }

    if (!IsItFamily15h)
    {
        CPULib_CpuID(1, &CpuSignature, &RegEbx, &FeatureFlagsEcx, &FeatureFlagsEdx);

        CpuFeatureInfo = Shl64(FeatureFlagsEcx, 32) + FeatureFlagsEdx;

        CpuInfo->Valid = TRUE;
        CpuInfo->CpuSignature = CpuSignature;
        CpuInfo->CpuFeatureInfo = CpuFeatureInfo;
        CpuInfo->BIST = 0;

        // Get the CPU revision information from the scratch pad register
        CpuInfo->CpuRevision = (CpuSignature & 0xFF);
        CpuInfo->ApicId = *(UINT32*) (UINTN)(APIC_BASE + APIC_ID_REGISTER) >> 24;
        CpuInfo->ApicEId = 0;
        CpuInfo->ApicVer = (UINT8)*(UINT32*)(UINTN)(APIC_BASE + APIC_VERSION_REGISTER);
	}

    // Allocate cache descriptor info structures for this CPU
    Status = pBS->AllocatePool (EfiBootServicesData,
                   (CacheSize + 1) * sizeof (CACHE_DESCRIPTOR_INFO), &CacheInfo);
    ASSERT_EFI_ERROR (Status);

    AmiCpuInfo->CacheInfo = (VOID*)CacheInfo;

    // Initialize Cache Descriptors
    for (i = 0; i < CacheSize; i++)
    {
        if (i == 0 || (CacheTable[i].FCpuID != CacheTable[i - 1].FCpuID)) 
            CPULib_CpuID (CacheTable[i].FCpuID, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);

        AmiCpuInfo->CacheInfo[i].Desc = 0xFF;   // Non-zero value
        AmiCpuInfo->CacheInfo[i].Level = CacheTable[i].Level;
        AmiCpuInfo->CacheInfo[i].Type = CacheTable[i].Type;

        if (CacheTable[i].Level == EFI_CACHE_L3)
        {
            AmiCpuInfo->CacheInfo[i].Size = (Reg[CacheTable[i].Register] >> CacheTable[i].SShift) &
             CacheTable[i].SMask;
            AmiCpuInfo->CacheInfo[i].Size = AmiCpuInfo->CacheInfo[i].Size / 2;  // Size in MB;
        }
        else
            AmiCpuInfo->CacheInfo[i].Size = (Reg[CacheTable[i].Register] >> CacheTable[i].SShift) &
             CacheTable[i].SMask;   // Size in KB

        // Determine cache associativity
        Associativity = (Reg[CacheTable[i].Register] >> CacheTable[i].AShift) & CacheTable[i].AMask;
        for (j = 0; j < CacheTable[i].ATable.size; j++)
        {
            if (Associativity == CacheTable[i].ATable.Map[j].FieldValue)
            {
                AmiCpuInfo->CacheInfo[i].Associativity = CacheTable[i].ATable.Map[j].SMBiosValue;
                break;
            }
        }
        // Default Associativity is CacheAssociativityUnknown.
        if (j == CacheTable[i].ATable.size) 
            AmiCpuInfo->CacheInfo[i].Associativity = CacheAssociativityUnknown;
    }
    AmiCpuInfo->CacheInfo[i].Desc = 0;  // Null descriptor at end of list

    // Allocate and initialize brand string
    Status = pBS->AllocatePool(EfiBootServicesData, 49, &BrandString);
    ASSERT_EFI_ERROR(Status);

    AmiCpuInfo->BrandString = BrandString;
    CPULib_CpuID (AMD_CPU_NAME_CPUID_1, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    *(UINT32*)BrandString = Reg[EAX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EBX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[ECX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EDX];
    BrandString += 4;

    CPULib_CpuID (AMD_CPU_NAME_CPUID_2, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    *(UINT32*)BrandString = Reg[EAX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EBX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[ECX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EDX];
    BrandString += 4;

    CPULib_CpuID (AMD_CPU_NAME_CPUID_3, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    *(UINT32*)BrandString = Reg[EAX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EBX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[ECX];
    BrandString += 4;
    *(UINT32*)BrandString = Reg[EDX];
    BrandString += 4;
    *BrandString = '\0';

    // Remove leading spaces. After removing leading spaces, the Brand String can not be
    // freed. However, it should never be freed.
    while (*AmiCpuInfo->BrandString == ' ')
        ++AmiCpuInfo->BrandString;

    CPULib_CpuID (1, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    AmiCpuInfo->Version = Reg[EAX];
    AmiCpuInfo->Features = Shl64 (Reg[ECX], 32) + Reg[EDX];
    AmiCpuInfo->NumCores = (Reg[EDX] & (1 << 28)) ? ((Reg[EBX] >> 16) & 0xFF) : 0;
    if(AmiCpuInfo->NumCores == 0)
    {
        CPULib_CpuID (AMD_EXT_CPUID_8, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
        AmiCpuInfo->NumCores = (UINT8)((Reg[ECX] & 0xFF) + 1);
    }
	AmiCpuInfo->NumHts		= IsHtEnabled() * 2;	//Either 2 or 0.
    AmiCpuInfo->FSBFreq     = 0; //MHZ -- FSB not supported since its HT Speed.
	AmiCpuInfo->MicroCodeVers	= (UINT32)ReadMsr(AMD_MSR_MCODE_SIGNATURE);


    TimerPeriod = CalculateTimerPeriod();	//10^-15 s.
    AmiCpuInfo->ActualFreq  = 1000000000 / (UINT32)TimerPeriod;

    if (IsFidSupported)
    {
        AmiCpuInfo->IntendedFreq = (UINT32)Frequency;
    }

    if (IsVidSupported)
    {
        if (IsItFamily15h)
        {
            AmiCpuInfo->Voltage = VoltageInmV;
        }
        else
        {
            AmiCpuInfo->Voltage = (UINT32)(VoltageInuV / 1000);
        }
    }
    // Semaphore unlock here
    AmiCpuInfoSemaphore = 0;
}


AMI_CPU_INFO_PROTOCOL gAmiCpuInfoProtocol = {GetCpuInfo};

EFI_CPU_ARCH_PROTOCOL gEfiCpuArchProtocol = {
    EfiCpuFlushDataCache,
    EfiCpuEnableInterrupt,
    EfiCpuDisableInterrupt,
    EfiCpuGetInterruptState,
    EfiCpuInitialization,
    EfiCpuRegisterInterruptHandler,
    EfiCpuGetTimerValue,
    EfiCpuSetMemoryAttributes,
    1,
    32
};

/**
    A routine to set MSR for BTS.

        
    @param Cpu 
    @param Context 

         
    @retval VOID

**/

VOID
SetAmdMsrRegforBts(
  IN            UINT8   Cpu,
  IN volatile   VOID    *Context
)
{
    UINT64  NbCfg;
    UINT64  Hwcr_Value;

    if (IsItFamily15h)
    {
        //Disable the Extended Config Space.
        NbCfg = ReadMsr(AMD_MSR_NB_CFG);
        NbCfg = NbCfg & 0xFFFFBFFFFFFFFFFF;
        WriteMsr(AMD_MSR_NB_CFG, NbCfg);
    }
	
	//Enable the time stamp counter
	Hwcr_Value = ReadMsr(AMD_MSR_HWCR);
	Hwcr_Value = (Hwcr_Value | (1 << 24));
	WriteMsr(AMD_MSR_HWCR, Hwcr_Value);

}


/**
    This is to set a default value to E000/F000 when CSM is disabled.

    @param  VOID

    @retval VOID
**/
VOID
SetEsegFsegWhenCsmOff(
    VOID)
{
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
    if ((IsSetupDataValid) && (SetupData.CsmSupport == 0))
    {
#endif
        DEBUG((DEBUG_INFO, "***SetEsegFsegWhenCsmOff   CSM is OFF\n"));

        switch  (CPU_E000_DEFAULT) {

            case 0:
                // Read only / WP   0x1515151515151515
                NbProgramPamRegisters(pBS, NULL, 0xE0000, 0x8000, LEGACY_REGION_LOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE0000, 0x8000, EFI_MEMORY_WP);
                break;
            case 1:
                // Read Write / WT     0x1C1C1C1C1C1C1C1C
                NbProgramPamRegisters(pBS, NULL, 0xE0000, 0x8000, LEGACY_REGION_UNLOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE0000, 0x8000, EFI_MEMORY_WT);
                break;
            case 2:
                // Read Write ROM / UC      0x0000000000000000
                NbProgramPamRegisters(pBS, NULL, 0xE0000, 0x8000, LEGACY_REGION_DECODE_ROM, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE0000, 0x8000, EFI_MEMORY_UC);
                break;
        }

        switch  (CPU_E800_DEFAULT) {

            case 0:
                // Read only / WP   0x1515151515151515
                NbProgramPamRegisters(pBS, NULL, 0xE8000, 0x8000, LEGACY_REGION_LOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE8000, 0x8000, EFI_MEMORY_WP);
                break;
            case 1:
                // Read Write / WT     0x1C1C1C1C1C1C1C1C
                NbProgramPamRegisters(pBS, NULL, 0xE8000, 0x8000, LEGACY_REGION_UNLOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE8000, 0x8000, EFI_MEMORY_WT);
                break;
            case 2:
                // Read Write ROM / UC      0x0000000000000000
                NbProgramPamRegisters(pBS, NULL, 0xE8000, 0x8000, LEGACY_REGION_DECODE_ROM, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xE8000, 0x8000, EFI_MEMORY_UC);
                break;
        }

        switch  (CPU_F000_DEFAULT) {

            case 0:
                // Read only / WP   0x1515151515151515
                NbProgramPamRegisters(pBS, NULL, 0xF0000, 0x10000, LEGACY_REGION_LOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xF0000, 0x10000, EFI_MEMORY_WP);
                break;
            case 1:
                // Read Write / WT     0x1C1C1C1C1C1C1C1C
                NbProgramPamRegisters(pBS, NULL, 0xF0000, 0x10000, LEGACY_REGION_UNLOCK, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xF0000, 0x10000, EFI_MEMORY_WT);
                break;
            case 2:
                // Read Write ROM / UC      0x0000000000000000
                NbProgramPamRegisters(pBS, NULL, 0xF0000, 0x10000, LEGACY_REGION_DECODE_ROM, NULL);
                EfiCpuSetMemoryAttributes(NULL, 0xF0000, 0x10000, EFI_MEMORY_UC);
                break;
        }
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
    }
#endif

}

/**
    A routine to set SMM BASE MSR for capsule update.

        
    @param Cpu 
    @param Context 

         
    @retval VOID

**/
VOID
SetSMMBaseMsrForCapsule(
IN UINT8 Cpu,
IN volatile VOID *Context)
{
    WriteMsr(AMD_MSR_SMM_BASE, 0x30000);
}
/**
    Install Interrupt Handlers for 0 to 19, to the routine

        
    @param ImageHandle 
    @param SystemTable 

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
EFIAPI
DxeInitializeCpu(
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS          Status;
    EFI_HANDLE          Handle = 0;
    UINTN               VariableSize;
    VOID                *RuntimeGdt;
    SETUP_CPU_FEATURES  SetupCpuFeatures;
    CPU_FEATURES        *CpuFeatures;
    EFI_EVENT           ReadyToBootEvent;
    EFI_EVENT           ExitBootServiceEvent;
    UINT64				HwcrValue;
    VOID                *Registration = NULL;
    UINT64              Buffer64;
    UINT32              Attributes = 0;
    UINT32              Buffer32 = 0;
    UINT32              RegValue, CurFid, CurDid, CurVid;
    UINTN               PowerInmW;
    REGISTER_TABLE      Reg;
    CPU_SETUP_DATA      CpuSetupData;
    UINTN               i;
#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
	EFI_EVENT           LegacyBootEvent;
#endif

    EFI_HOB_HANDOFF_INFO_TABLE      *HandoffInfoTable;

    InitAmiLib(ImageHandle, SystemTable);

    PROGRESS_CODE(DXE_CPU_INIT);

    VariableSize = sizeof (SETUP_DATA);
    Status = pRS->GetVariable (SetupVariable, &gEfiSetupGuid, &Attributes, &VariableSize,
                   &SetupData);
    IsSetupDataValid = !EFI_ERROR (Status);

    FirstHob = GetEfiConfigurationTable (SystemTable, &gEfiHobListGuid);
    if (!FirstHob)
        return EFI_INVALID_PARAMETER;	

    IsItFamily15h = IsFamily15h();  // Initialize the IsItFamily15h value

    // Set PPC_LIMIT
    if (IsSetupDataValid)
    {
        Buffer64 = ReadMsr(0xC0010061);
        Buffer32 = (UINT32)((Buffer64 >> 4) & 0x7); // Get PstateMaxVal: P-state maximum value.
        SetupData.PPC_LIMIT = (UINT8)Buffer32;
        Status = pRS->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                   VariableSize, &SetupData);
    }

    HwcrValue = ReadMsr (AMD_MSR_HWCR);
    HwcrValue = HwcrValue | (1 << 24);
    WriteMsr (AMD_MSR_HWCR, HwcrValue);

    // Set PPCV value for AMD driver
    GetCpuSetupData(pRS, &CpuSetupData, FALSE);
    PcdSet8(PcdAmdAcpiCpuPerfPresentCap, CpuSetupData.PPC_CTRL);

    CpuInfoHob = (CPUINFO_HOB*)FirstHob;

    // Find CPUINFO_HOB Hob.
    while (!EFI_ERROR (Status = FindNextHobByType (EFI_HOB_TYPE_GUID_EXTENSION, &CpuInfoHob)))
        if (guidcmp (&CpuInfoHob->EfiHobGuidType.Name, &gAmiCpuinfoHobGuid) == 0)
            break;
    if (EFI_ERROR(Status))
        return Status;

//    NumCpus = CpuInfoHob->CpuCount;
    CpuFeatures = &CpuInfoHob->CpuFeatures;

    // If the CPU supports FID and/or VID control, then set CurFID and MaxFID
    // from the FIDVID_CTL Register. Otherwise, CurFID and MaxFID will be 
    // obtained from the hardware configuration register.
    CPULib_CpuID(AMD_EXT_CPUID_0, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    if (Reg[EAX] >= AMD_EXT_CPUID_7)
    {
        CPULib_CpuID (AMD_EXT_CPUID_7, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
        if (Reg[EDX] & BIT07)
        {   // HWPState
            IsFidSupported = TRUE;
            IsVidSupported = TRUE;
        }
    }

    if (IsItFamily15h)
    {
        Buffer64 = ReadMsr(AMD_MSR_NB_CFG);
        if (!(Buffer64 & Shl64(1, 46)))  // if bit 46 EnableCf8ExtCfg is not then set it for accessing D18F4x15C
        {
            WriteMsr(AMD_MSR_NB_CFG, Buffer64 | Shl64(1, 46));
            Buffer64 &= ~Shl64(1, 46);
        }
    	NumBoostStates = NbReadPci32 (PCI_ADDRESS (0, 0x18, 4, 0x15C), TRUE);
        WriteMsr(AMD_MSR_NB_CFG, Buffer64); // restore the original value to NB_CFG
    	NumBoostStates = (UINT32)(Shr64 (NumBoostStates, 2) & 0x7); // Get NumBoostStates

        // Fill this field with current voltage
        if ((IsFidSupported) || (IsVidSupported))
        {
            RegValue = (UINT32)ReadMsr (0xC0010064 + NumBoostStates);

            // Find the current pstate msr
            // Extract the fid and DID.
            // Frequency = ((fid+10h) * 200)/(2^DID)
            CurFid = (UINT8)RegValue & 0x3F;
            CurDid = (UINT8)(RegValue >> 6) & 7;
            CurDid = (UINT8)Shl64 (1, CurDid);   // 2^DID
            Frequency = (CurFid + 0x10);
            Frequency = (Frequency * 100 ) / CurDid;

            CurVid = (UINT8) ((RegValue & 0x0000FE00) >> 9);
            VoltageInmV = GetCpuVoltage (CurVid) / 10;
        }

        if (IsSetupDataValid)
        {
            if (SetupData.HideF15Op != 0)
            {
                SetupData.HideF15Op = 0;
                Status = pRS->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                               VariableSize, &SetupData);
                DEBUG((DEBUG_INFO, " SetVariable HideF15Op Status = %x\n", Status));
            }
        }
    }
    else
    {
        if (IsSetupDataValid)
        {
            if (SetupData.HideF15Op != 1)
            {
                SetupData.HideF15Op = 1;
                Status = pRS->SetVariable (SetupVariable, &gEfiSetupGuid, Attributes,
                               VariableSize, &SetupData);
                DEBUG((DEBUG_INFO, " SetVariable HideF15Op Status = %x\n", Status));
            }
        }

        // Fill this field with current voltage
        if ((IsFidSupported) || (IsVidSupported))
        {
            CcxGetPstateInfo (0, SwPstate0, &Frequency, &VoltageInuV, &PowerInmW, NULL);
        }
    }

    DEBUG((DEBUG_INFO, "DxeInitializeCpu: Before InitInterrupts\n"));
    Status = InitInterrupts();
    ASSERT_EFI_ERROR(Status);

    RuntimeGdt = CpyToRunTime(GDT, sizeof(GDT));
    pGdt.Limit = sizeof(GDT) - 1;
    pGdt.Base = (UINTN)RuntimeGdt;

    DEBUG((DEBUG_INFO, "DxeInitializeCpu: Before CPULib_LoadGdt\n"));
    CPULib_LoadGdt(&pGdt);		//load gdt address for each cpu in memory

    Status =  EfiCpuRegisterInterruptHandler(NULL, 13, NULL);
    ASSERT_EFI_ERROR(Status);

    Status = EfiCpuRegisterInterruptHandler(0, 13, TempGPInterruptHandler);
    ASSERT_EFI_ERROR(Status);

    NumCpus = StartAllAps (&MpData);

    // Allocate memory for AMI_CPU_INFO. This will be filled by CPU initialization.
    Status = pBS->AllocatePool (EfiBootServicesData, sizeof (AMI_CPU_INFO) * NumCpus, &gAmiCpuInfo);
    ASSERT_EFI_ERROR(Status);
	CpuInfoHob->CpuCount = NumCpus;

    DEBUG((DEBUG_INFO, "%d CPU is start success\n", NumCpus));
	for (i = 0; i < NumCpus; i++)
        CpuInfoHob->Cpuinfo[i].Valid    = TRUE;
	
    ExecuteFunctionOnRunningCpus (MpData, TRUE, TRUE, InitializeCpu, NULL);

//    if (!IsItFamily15h)
//    {
//        //The AP information in CPUINFO_HOB is NULL, since APs are not enabled in PEI on ZP
//        ExecuteFunctionOnRunningCpus(MpData, FALSE, TRUE, UpdateCpuInfoHobZp, (VOID*)CpuInfoHob);
//        InitializeFloatingPointUnits();
//    }

    Status = EfiCpuRegisterInterruptHandler(NULL, 13, NULL);
    ASSERT_EFI_ERROR(Status);

    Status = EfiCpuRegisterInterruptHandler(0, 13, InterruptHandlerHalt);	//Normal Handler.
    ASSERT_EFI_ERROR(Status);

    BoardCpuInit();             //Initialize any Board specific Cpu things.

    //This may be needed to be moved, to only show as supported if all are supported.
    MemSet(&SetupCpuFeatures, sizeof(SetupCpuFeatures), 0); //Just in case someone forgets to fill part of the structure.
    SetupCpuFeatures.HTAvailable = IsHtEnabled();
    SetupCpuFeatures.LimitCpuidAvailable = 1;   // Always available...C0010015 bit 11...used to restric limitcpuid
    SetupCpuFeatures.NodeCount = CpuInfoHob->NodeCount;
    SetupCpuFeatures.DualNode = IsDualNode();
    SetupCpuFeatures.PopScktCount = SetupCpuFeatures.DualNode ? SetupCpuFeatures.NodeCount / 2 :
                                    SetupCpuFeatures.NodeCount;

    Status = pRS->SetVariable (L"SetupCpuFeatures", &gEfiSetupGuid,
                   EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                   sizeof (SETUP_CPU_FEATURES), &SetupCpuFeatures);
    ASSERT_EFI_ERROR (Status);

    // This is used by the event.
//    Status = pBS->AllocatePool (EfiACPIMemoryNVS, sizeof (CPU_S3_RESUME), &CpuS3Resume);
    CpuS3Resume = (CPU_S3_RESUME*)0xFFFFFFFF;
    Status = pBS->AllocatePages (AllocateMaxAddress, EfiACPIMemoryNVS,
                   EFI_SIZE_TO_PAGES (sizeof (CPU_S3_RESUME)),
                   (EFI_PHYSICAL_ADDRESS*)&CpuS3Resume);
    ASSERT_EFI_ERROR (Status);

    Status = pBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_CALLBACK, CpuBootOnExitBootService,
                   (VOID *)TRUE, &ExitBootServiceEvent);
    ASSERT_EFI_ERROR (Status);

    // In cases where core does not support a call back before option roms are executed.
    // The calling outside of SMM will be disabled before shell or a OS is loaded.
    Status = CreateReadyToBootEvent (TPL_CALLBACK, ExecuteAtReadyToBoot, NULL, &ReadyToBootEvent);
    ASSERT_EFI_ERROR (Status);

#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
    Status = CreateLegacyBootEvent(TPL_CALLBACK, CpuBootOnLegacyBoot,
              NULL,  &LegacyBootEvent);
#endif
    Status = pBS->AllocatePool(EfiACPIMemoryNVS, sizeof (MTRR_SETTINGS), &gMtrrTable);

    Status = pBS->InstallMultipleProtocolInterfaces (&Handle,
                   &gEfiCpuArchProtocolGuid, &gEfiCpuArchProtocol,
                   &gEfiMpServiceProtocolGuid, gEfiMpServicesProtocol,
                   &gAmiCpuInfoProtocolGuid, &gAmiCpuInfoProtocol, NULL);
    ASSERT_EFI_ERROR (Status);

    SetEsegFsegWhenCsmOff();

    ExecuteFunctionOnRunningCpus (MpData, TRUE, TRUE, SetAmdMsrRegforBts, NULL);
    HandoffInfoTable = GetEfiConfigurationTable(SystemTable, &gEfiHobListGuid);
    if (!HandoffInfoTable) return EFI_INVALID_PARAMETER;
    
    if (HandoffInfoTable->BootMode == BOOT_ON_FLASH_UPDATE)
    {
        DEBUG((DEBUG_INFO, "\n  !!!!! SetSmmBaseMsrForCapsule\n"));
        ExecuteFunctionOnRunningCpus(MpData, TRUE, TRUE, SetSMMBaseMsrForCapsule, NULL);
    }

    return EFI_SUCCESS;
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
