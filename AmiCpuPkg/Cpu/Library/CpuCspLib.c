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

/** @file CpuCspLib.c
    Contains the CPU library related functions. These functions
    can be linked with various components in the project

**/

#include <Efi.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Smm.h>
#include "Cpu.h"
#include "CpuCspLib.h"
#include "AmiCspLib.h"
#include <Protocol/SmmCpu.h>
#include <Protocol/MpService.h>
// #include "CpuBoard.h"
//---------------------------------------------------------------------------

/**
    This function should not do anything in AMD project. Add
    this function is just to make projects compatible with
    the Smm label 35.

        
    @param gSmmHob 

         
    @retval VOID

**/

VOID
CpuSmmMemoryInit (
  IN OUT    SMM_HOB *gSmmHob
)
{

}

/**
    Initializes an MTRR_COPY_CONTEXT structure

        
    @param Mcc 

         
    @retval VOID

**/

VOID
InitMtrrCopyContext (
  IN OUT    MTRR_COPY_CONTEXT   *Mcc
)
{
    Mcc->BSPisCopied = FALSE;

    if (IsFamily15h())
    {
        Mcc->Size = NUM_COMMON_MTRRS;

        Mcc->MsrIndex[0] = MTRR_PHYS_BASE_0;
        Mcc->MsrIndex[1] = MTRR_PHYS_MASK_0;
        Mcc->MsrIndex[2] = MTRR_PHYS_BASE_1;
        Mcc->MsrIndex[3] = MTRR_PHYS_MASK_1;
        Mcc->MsrIndex[4] = MTRR_PHYS_BASE_2;
    	Mcc->MsrIndex[5] = MTRR_PHYS_MASK_2;
    	Mcc->MsrIndex[6] = MTRR_PHYS_BASE_3;
    	Mcc->MsrIndex[7] = MTRR_PHYS_MASK_3;
    	Mcc->MsrIndex[8] = MTRR_PHYS_BASE_4;
    	Mcc->MsrIndex[9] = MTRR_PHYS_MASK_4;
    	Mcc->MsrIndex[10] = MTRR_PHYS_BASE_5;
    	Mcc->MsrIndex[11] = MTRR_PHYS_MASK_5;
    	Mcc->MsrIndex[12] = MTRR_PHYS_BASE_6;
    	Mcc->MsrIndex[13] = MTRR_PHYS_MASK_6;
    	Mcc->MsrIndex[14] = MTRR_PHYS_BASE_7;
    	Mcc->MsrIndex[15] = MTRR_PHYS_MASK_7;
    	Mcc->MsrIndex[16] = MTRR_FIX_64K_00000;
    	Mcc->MsrIndex[17] = MTRR_FIX_16K_80000;
    	Mcc->MsrIndex[18] = MTRR_FIX_16K_A0000;
    	Mcc->MsrIndex[19] = MTRR_FIX_4K_C0000;
    	Mcc->MsrIndex[20] = MTRR_FIX_4K_C8000;
    	Mcc->MsrIndex[21] = MTRR_FIX_4K_D0000;
    	Mcc->MsrIndex[22] = MTRR_FIX_4K_D8000;
    	Mcc->MsrIndex[23] = MTRR_FIX_4K_E0000;
    	Mcc->MsrIndex[24] = MTRR_FIX_4K_E8000;
    	Mcc->MsrIndex[25] = MTRR_FIX_4K_F0000;
    	Mcc->MsrIndex[26] = MTRR_FIX_4K_F8000;
    	Mcc->MsrIndex[27] = AMD_MSR_TOP_MEM;
    	Mcc->MsrIndex[28] = AMD_MSR_TOP_MEM2;
    	Mcc->MsrIndex[29] = MSR_SYS_CFG;
    	Mcc->MsrIndex[30] = AMD_MSR_IORR_BASE0;
    	Mcc->MsrIndex[31] = 0xC001102A;
    	Mcc->MsrIndex[32] = AMD_MSR_MMIO_CFG_BASE;
    	Mcc->MsrIndex[33] = AMD_PP_MSR_IC_CFG;
    	Mcc->MsrIndex[34] = AMD_PP_MSR_DC_CFG;
    	Mcc->MsrIndex[35] = AMD_MSR_HWCR;
    }
    else
    {
        //The Mcc->Size should not be bigger than NUM_COMMON_MTRRS
        Mcc->Size = 33; //The number is decided by below index

        Mcc->MsrIndex[0] = MTRR_PHYS_BASE_0;
        Mcc->MsrIndex[1] = MTRR_PHYS_MASK_0;
        Mcc->MsrIndex[2] = MTRR_PHYS_BASE_1;
        Mcc->MsrIndex[3] = MTRR_PHYS_MASK_1;
        Mcc->MsrIndex[4] = MTRR_PHYS_BASE_2;
        Mcc->MsrIndex[5] = MTRR_PHYS_MASK_2;
        Mcc->MsrIndex[6] = MTRR_PHYS_BASE_3;
        Mcc->MsrIndex[7] = MTRR_PHYS_MASK_3;
        Mcc->MsrIndex[8] = MTRR_PHYS_BASE_4;
        Mcc->MsrIndex[9] = MTRR_PHYS_MASK_4;
        Mcc->MsrIndex[10] = MTRR_PHYS_BASE_5;
        Mcc->MsrIndex[11] = MTRR_PHYS_MASK_5;
        Mcc->MsrIndex[12] = MTRR_PHYS_BASE_6;
        Mcc->MsrIndex[13] = MTRR_PHYS_MASK_6;
        Mcc->MsrIndex[14] = MTRR_PHYS_BASE_7;
        Mcc->MsrIndex[15] = MTRR_PHYS_MASK_7;
        Mcc->MsrIndex[16] = MTRR_FIX_64K_00000;
        Mcc->MsrIndex[17] = MTRR_FIX_16K_80000;
        Mcc->MsrIndex[18] = MTRR_FIX_16K_A0000;
        Mcc->MsrIndex[19] = MTRR_FIX_4K_C0000;
        Mcc->MsrIndex[20] = MTRR_FIX_4K_C8000;
        Mcc->MsrIndex[21] = MTRR_FIX_4K_D0000;
        Mcc->MsrIndex[22] = MTRR_FIX_4K_D8000;
        Mcc->MsrIndex[23] = MTRR_FIX_4K_E0000;
        Mcc->MsrIndex[24] = MTRR_FIX_4K_E8000;
        Mcc->MsrIndex[25] = MTRR_FIX_4K_F0000;
        Mcc->MsrIndex[26] = MTRR_FIX_4K_F8000;
        Mcc->MsrIndex[27] = AMD_MSR_TOP_MEM;
        Mcc->MsrIndex[28] = AMD_MSR_TOP_MEM2;
        Mcc->MsrIndex[29] = MSR_SYS_CFG;
        Mcc->MsrIndex[30] = AMD_MSR_IORR_BASE0;
        Mcc->MsrIndex[31] = AMD_MSR_MMIO_CFG_BASE;
        Mcc->MsrIndex[32] = AMD_MSR_HWCR;
    }
}

/**
    This function reads the MSRs speficied in the MsrIndex buffer
    and saves the values in the provided ValueBuffer.

        
    @param MsrIndex buffer containing MSR register numbers
    @param ValueBuffer buffer to store the BSP MSR values
    @param Size size of the buffers

         
    @retval VOID

**/

VOID
CpuReadMsrs (
  IN        MTRR_INDEX          MsrIndex,
  IN OUT    MTRR_SAVED_VALUE    ValueBuffer,
  IN        UINT16              Size
)
{
    UINT16  i;
    UINT64  MsrSave;

    // Enable MTRRFix Rd/Wr Dram attributes bits and
    // Enable modification of MTRRFix Rd/Wr Dram attributes bits
    MsrSave = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSave | (3 << MtrrFixDramEnBit));

    for (i = 0; i < Size; i ++)
        ValueBuffer[i] = ReadMsr (MsrIndex[i]);

    // Disable modification of MTRRFix Rd/Wr Dram attributes bits
    WriteMsr (MSR_SYS_CFG, MsrSave & (~(1 << MtrrFixDramModEnBit)));

    return;
}

/**
    This function writes the MSR values stored in the ValueBuffer
    into the MSR registers specified by the MsrIndex buffer.

        
    @param MsrIndex buffer containing MSR register numbers
    @param ValueBuffer buffer to store the BSP MSR values
    @param Size size of the buffers

         
    @retval VOID

**/

VOID
CpuWriteMsrs (
  IN    MTRR_INDEX          MsrIndex,
  IN    MTRR_SAVED_VALUE    ValueBuffer,
  IN    UINT16              Size
)
{
    UINT16  i;
    BOOLEAN InterruptState;
    UINT64  MsrSave;

    // Prepare for MTRR programming by disabling MTRRS & cache
    InterruptState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();
    DisableCacheInCR0();
    WriteMsr(MTRR_DEF_TYPE, 0);

    // Enable MTRRFix Rd/Wr Dram attributes bits and
    // Enable modification of MTRRFix Rd/Wr Dram attributes bits
    MsrSave = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSave | (3 << MtrrFixDramEnBit));

    for (i = 0; i < Size; i ++)
        WriteMsr (MsrIndex[i], ValueBuffer[i]);

    // Disable modification of MTRRFix Rd/Wr Dram attributes bits
    // (Read MSR_SYS_CFG again because it may have changed)
    MsrSave = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSave & (~(1 << MtrrFixDramModEnBit)));

    // Activate changes by enabling MTRRs & cache
    WriteMsr (MTRR_DEF_TYPE, 3 << 10);
    EnableCacheInCR0();
    if (InterruptState)
        CPULib_EnableInterrupt();

    return;
}

/**
    Copies BSP's MTRRs to all running APs' MTRRs

        
    @param pMTRRCopyContext a (void*) pointer to an MTRR_COPY_CONTEXT structure

         
    @retval VOID

    @note  
   This function is called by BSP implicitly with StartAllAps and
   RestartAp, but it should be called explicitly upon changing
   the BSP's MTRRs so that all MTRRs are synchronized with BSP.

   APs should not call this procedure before the BSP.

   This function can be executed on all APs with
   EFI_MP_SERVICES_PROTOCOL.EfiStartupAllAPs() after executing
   it on the BSP first.

**/

EFI_STATUS
CopyBspMtrrsToAllRunningApMtrrs (
  IN    VOID    *MtrrCopyContext
)
{
    MTRR_COPY_CONTEXT *Ctx = (MTRR_COPY_CONTEXT*)MtrrCopyContext;

    if (IsItBsp())
    {
        // Save MSR values of the BSP to buffer
        CpuReadMsrs (Ctx->MsrIndex, Ctx->ValueBuffer, Ctx->Size);
        Ctx->BSPisCopied = 1;
    }
    else
    {
        // It is an error for APs to call this function
        // before the BSP has saved its MSRs into the buffer
        if (!Ctx->BSPisCopied)
            return EFI_ACCESS_DENIED;

        // Write MSR values from buffer to AP's MTRRs
        CpuWriteMsrs (Ctx->MsrIndex, Ctx->ValueBuffer, Ctx->Size);
    }

    return EFI_SUCCESS;
}

/**
    Allows generic calling of CopyBspMtrrsToAllRunningApMtrrs
    by passing pointer to bootservices. Copies BSP's MTRRs to all
    running APs' MTRRs.

        
    @param gBS 

         
    @retval VOID

    @note  
  This function should only be called by the BSP.
  !!! See CopyBspMtrrsToAllRunningApMtrrs()

**/

EFI_STATUS
SynchronizeMtrrs (
  IN    EFI_BOOT_SERVICES   *gBS
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    MTRR_COPY_CONTEXT           MtrrCopyContext;
    EFI_MP_SERVICES_PROTOCOL    *MpServices;

    InitMtrrCopyContext(&MtrrCopyContext);

    Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid,
                   NULL, &MpServices);
    if (Status != EFI_SUCCESS)
        return Status;

    // Execute on BSP
    Status = CopyBspMtrrsToAllRunningApMtrrs ((VOID*)&MtrrCopyContext);
    if (Status != EFI_SUCCESS)
        return Status;

    // Execute on all running APs
    Status = MpServices->StartupAllAPs(MpServices,
                          (EFI_AP_PROCEDURE)CopyBspMtrrsToAllRunningApMtrrs,
                          FALSE, NULL, 0, (VOID*)&MtrrCopyContext, NULL);

    return Status;
}

/**
    Checks whether the processor executing this code is the BSP or
    AP (Boot Strap Processor - BSP, Application Processor - AP)
    by reading the BSP bit in APIC_BASE.

        
    @param VOID

         
    @retval TRUE If the processor is BSP
    @retval FALSE If the processor is AP

**/

BOOLEAN
IsItBsp (
    VOID
)
{
    if ((ReadMsr(MSR_XAPIC_BASE)) & XAPIC_BASE_BSP_BIT_MASK)
        return TRUE;       // BSP
    else
        return FALSE;       // AP
}


/**
    This function writes the CPU MSR with the value provided

        
    @param Msr 32bit MSR index
    @param Value 64bit OR Value
    @param Mask 64Bit AND Mask Value

         
    @retval VOID

**/

VOID
ReadWriteMsr (
  IN    UINT32  Msr,
  IN    UINT64  Value,
  IN    UINT64  Mask
)
{
    UINT64 OrigData = ReadMsr(Msr);
    UINT64 WriteData = (OrigData & Mask) | Value;
    WriteMsr(Msr, WriteData);
}


/**
    Determine if CPU support HT.

        
    @param VOID

         
    @retval True if HT supported.

**/

BOOLEAN
IsHtEnabled (
    VOID
)
{
    return FALSE;   // AMD CPU does not support HT
}

/**
    Determine if CPU supported VT.

        
    @param VOID

         
    @retval True if VT supported.

**/

BOOLEAN
IsXDSupported (
  IN    CPU_FEATURES    *Features
)
{
    UINT32  RegEbx;
    UINT32  RegEcx;
    UINT32  RegEdx;
    UINT32  CpuSignature;
	//AsmCpuid(1, &CpuSignature, NULL, NULL, NULL);
    CPULib_CpuID (1, &CpuSignature, &RegEbx, &RegEcx, &RegEdx);
    return ((CpuSignature >= 0xF41 || (CpuSignature & 0xFF0) == 0x6F0) &&
     Features->ExtFeatureEdx & (1 << 20));
}

/**
    Determine if CPU supports limiting CpuId to 1.

        
    @param VOID

         
    @retval True if supported.

**/

BOOLEAN
IsLimitCpuidSupported(
    VOID
)
{
    UINT32  RegEbx;
    UINT32  RegEcx;
    UINT32  RegEdx;
    UINT32  LargestCpuidFunc;

//    AsmCpuid(0, &LargestCpuidFunc, NULL, NULL, NULL);
	CPULib_CpuID (0, &LargestCpuidFunc, &RegEbx, &RegEcx, &RegEdx);
    return LargestCpuidFunc > 1;
}

/**
    Determine if CPU supports machine check.

        
    @param Features 

         
    @retval True if supported.

**/

BOOLEAN
IsMachineCheckSupported (
  IN    CPU_FEATURES    *Features
)
{
    //Check if MCE and MCA supported.
    return ((Features->FeatureEdx & ((1 << 7) + (1 << 14))) == ((1 << 7) + (1 << 14)));
}


/**
    Use the function to notify CPU if it is BSP or AP.

        
    @param Cpu 
    @param Context 

    @retval VOID

**/

/*
//### Moved to AMD64MP.ASM
VOID
SwitchBspProgramReg (
  IN            UINT8   Cpu,
  IN volatile   VOID    *Context
)
{
    UINT8   NewBsp = (UINT8)Context;

    if (Cpu == NewBsp)
        ReadWriteMsr (0x1B, 1 << 8, 0xFFFFFFFFFFFFFFFF);    // MSR_XAPIC_BASE    Set BSP indicator
    else
        ReadWriteMsr (0x1B, 0, 0xFFFFFFFFFFFFFEFF); // MSR_XAPIC_BASE    Set AP indicator
}
*/


/**
    This routines copies the SMM save state area version 0x30064
    to 0x30003

        
    @param SmmSaveState Pointer to SMM save state
    @param SstSaveState Standard SMM save state

         
    @retval VOID

**/

VOID
CpuGetAmd64SaveState (
  IN    UINT8                   *SmmSaveState,
  IN    EFI_SMI_CPU_SAVE_STATE  *SstSaveState
)
{
    AMD_64_SAVE_STATE *SmmSave = (AMD_64_SAVE_STATE *) SmmSaveState;

    SstSaveState->SMBASE    = SmmSave->SMBASE;
    SstSaveState->SMMRevId  = SmmSave->SMMRevId;
    SstSaveState->IORestart = SmmSave->IORestart;
    SstSaveState->AutoHALTRestart = SmmSave->AutoHALTRestart;
    SstSaveState->ES        = (UINT16)SmmSave->ES[0];
    SstSaveState->CS        = (UINT16)SmmSave->CS[0];
    SstSaveState->SS        = (UINT16)SmmSave->SS[0];
    SstSaveState->DS        = (UINT16)SmmSave->DS[0];
    SstSaveState->FS        = (UINT16)SmmSave->FS[0];
    SstSaveState->GS        = (UINT16)SmmSave->SS[0];
    SstSaveState->LDTBase   = (UINT32)SmmSave->LDTR[1];
// Structure is different whe using Intel Framework, may need to be updated further
//    SstSaveState->GDTBase   = (UINT32)SmmSave->GDTR[1];
//    SstSaveState->IDTBase   = (UINT32)SmmSave->IDTR[1];
    SstSaveState->TR        = (UINT32)(UINT16)SmmSave->TR[0];

    SstSaveState->DR7       = (UINT32)SmmSave->DR7;
    SstSaveState->DR6       = (UINT32)SmmSave->DR6;
    SstSaveState->EAX       = (UINT32)SmmSave->RAX;
    SstSaveState->ECX       = (UINT32)SmmSave->RCX;
    SstSaveState->EDX       = (UINT32)SmmSave->RDX;
    SstSaveState->EBX       = (UINT32)SmmSave->RBX;
    SstSaveState->ESP       = (UINT32)SmmSave->RSP;
    SstSaveState->EBP       = (UINT32)SmmSave->RBP;
    SstSaveState->ESI       = (UINT32)SmmSave->RSI;
    SstSaveState->EDI       = (UINT32)SmmSave->RDI;
    SstSaveState->EIP       = (UINT32)SmmSave->RIP;
    SstSaveState->EFLAGS    = (UINT32)SmmSave->RFLAGS;
    SstSaveState->CR3       = (UINT32)SmmSave->CR3;
    SstSaveState->CR0       = (UINT32)SmmSave->CR0;
// Structure is different whe using Intel Framework, may need to be updated further
//    SstSaveState->CR4       = (UINT32)SmmSave->CR4;
    return;
}

/**
    This routines copies the necessary values from standard
    SMM save state area to version 0x30064 SMM save state area

        
    @param SmmSaveState Pointer to SMM save state
    @param SstSaveState Standard SMM save state

         
    @retval VOID

**/

VOID
CpuRestoreAmd64SaveState (
  IN    UINT8                   *SmmSaveState,
  IN    EFI_SMI_CPU_SAVE_STATE  *SstSaveState
)
{
    AMD_64_SAVE_STATE *SmmSave = (AMD_64_SAVE_STATE *) SmmSaveState;

    SmmSave->IORestart          = (UINT8) SstSaveState->IORestart;
    SmmSave->AutoHALTRestart    = (UINT8) SstSaveState->AutoHALTRestart;

    //Must preserve upper 32 bits of 64 bit register.
    *(UINT32*)&SmmSave->RAX     = SstSaveState->EAX;
    *(UINT32*)&SmmSave->RCX     = SstSaveState->ECX;
    *(UINT32*)&SmmSave->RDX     = SstSaveState->EDX;
    *(UINT32*)&SmmSave->RBX     = SstSaveState->EBX;
    *(UINT32*)&SmmSave->RSP     = SstSaveState->ESP;
    *(UINT32*)&SmmSave->RBP     = SstSaveState->EBP;
    *(UINT32*)&SmmSave->RSI     = SstSaveState->ESI;
    *(UINT32*)&SmmSave->RDI     = SstSaveState->EDI;
    *(UINT32*)&SmmSave->RIP     = SstSaveState->EIP;
    *(UINT32*)&SmmSave->RFLAGS  = SstSaveState->EFLAGS;
    return;
}

/**
    This routines copies the necessary values from standard
    SMM save state area to version 0x30003 SMM save state area

        
    @param SmmBase Pointer to SMM save state
    @param SstSaveState Standard SMM save state

         
    @retval VOID

**/

VOID
CpuRestoreDefaultSaveState (
  IN    UINT8                   *SmmBase,
  IN    EFI_SMI_CPU_SAVE_STATE  *SstSaveState
)
{
    EFI_SMI_CPU_SAVE_STATE *SmmSave = (EFI_SMI_CPU_SAVE_STATE*) SmmBase;

    SmmSave->EFLAGS = SstSaveState->EFLAGS;
    SmmSave->EIP = SstSaveState->EIP;
    SmmSave->EDI = SstSaveState->EDI;
    SmmSave->ESI = SstSaveState->ESI;
    SmmSave->EBP = SstSaveState->EBP;
    SmmSave->ESP = SstSaveState->ESP;
    SmmSave->EBX = SstSaveState->EBX;
    SmmSave->EDX = SstSaveState->EDX;
    SmmSave->ECX = SstSaveState->ECX;
    SmmSave->EAX = SstSaveState->EAX;
    SmmSave->AutoHALTRestart = SstSaveState->AutoHALTRestart;
    SmmSave->IORestart = SstSaveState->IORestart;
}

/**
    This routine is the generic routine used to copy the CPU
    specific SMM save state to standard save state.

        
    @param SmmBase Pointer to SMM save state
    @param SstSaveState Standard SMM save state

         
    @retval VOID

**/

VOID
CpuGetSaveState (
  IN    UINT8                   *SmmBase,
  IN    EFI_SMI_CPU_SAVE_STATE  *SstSaveState
)
{
    UINT8 *SmmSaveState = ((UINT8 *)SmmBase + 0xFE00);
    UINT32 SmmRevision = ((EFI_SMI_CPU_SAVE_STATE*)(SmmSaveState))->SMMRevId;

    // Porting Required. PERFORM CPU SPECIFIC save state handling
    if ((SmmRevision & 0xFF) == 0x64)
        CpuGetAmd64SaveState (SmmSaveState, SstSaveState);
    else
    {
        UINTN Index;
        // Copy save state area.
        for (Index = 0; Index < (sizeof (EFI_SMI_CPU_SAVE_STATE) / sizeof (UINT32)); Index++)
            *( ((UINT32 *)SstSaveState) + Index) = *((UINT32 *)(SmmBase + 0xFE00) + Index);
    }
}

/**
    This routine is the generic routine used to copy the standard
    SMM save state from CPU specific save state. This routine
    should make sure it does not change read only areas

        
    @param SmmBase Pointer to SMM save state
    @param SstSaveState Standard SMM save state

         
    @retval VOID

**/

VOID
CpuRestoreSaveState (
  IN    UINT8                   *SmmBase,
  IN    EFI_SMI_CPU_SAVE_STATE  *SstSaveState
)
{
    UINT8 *SmmSaveState = ((UINT8 *)SmmBase + 0xFE00);
    UINT32 SmmRevision = ((EFI_SMI_CPU_SAVE_STATE*)(SmmSaveState))->SMMRevId;

    // Porting Required. PERFORM CPU SPECIFIC save state handling
    if ((SmmRevision & 0xFF) == 0x64)
        CpuRestoreAmd64SaveState (SmmSaveState, SstSaveState);
    else
        CpuRestoreDefaultSaveState (SmmBase + 0xFE00, SstSaveState);
}

typedef struct {
    UINT16 SaveStateOffset;
    UINT16 SaveStateWidth;
    UINT16 FrameworkOffset;
    UINT16 FrameworkWidth;
    BOOLEAN ReadOnly;
} AMD_X64_FORMAT;

AMD_X64_FORMAT gAMDX64Format[] = {
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTBASE = 4
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTBASE = 5
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTBASE = 6
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTLIMIT = 7
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTLIMIT = 8
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTLIMIT = 9
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTINFO = 10
    0xFE00, 2, 0x01A8, 2, TRUE, //EFI_SMM_SAVE_STATE_REGISTER_ES = 20
    0xFE10, 2, 0x01AC, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CS = 21
    0xFE20, 2, 0x01B0, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_SS = 22
    0xFE30, 2, 0x01B4, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_DS = 23
    0xFE40, 2, 0x01B8, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_FS = 24
    0xFE50, 2, 0x01BC, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_GS = 25
    0xFE70, 2, 0xFFFF, 0xFF, TRUE, //EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL = 26
    0xFE90, 2, 0x01C4, 2, TRUE,   //EFI_SMM_SAVE_STATE_REGISTER_TR_SEL = 27
    0xFF60, 8, 0x01C8, 4, TRUE,  //EFI_SMM_SAVE_STATE_REGISTER_DR7 = 28
    0xFF68, 8, 0x01FC, 4, TRUE,   //EFI_SMM_SAVE_STATE_REGISTER_DR6 = 29
    0xFFB8, 8, 0xFFFF, 0xFF, FALSE, //EFI_SMM_SAVE_STATE_REGISTER_R8 = 30
    0xFFB0, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R9 = 31
    0xFFA8, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R10 = 32
    0xFFA0, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R11 = 33
    0xFF98, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R12 = 34
    0xFF90, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R13 = 35
    0xFF88, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R14 = 36
    0xFF80, 8, 0xFFFF, 0xFF, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R15 = 37
    0xFFF8, 8, 0x01D0, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RAX = 38
    0xFFF0, 8, 0x01DC, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RBX = 39
    0xFFE8, 8, 0x01D4, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RCX = 40
    0xFFE0, 8, 0x01D8, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RDX = 41
    0xFFD8, 8, 0x01E0, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RSP = 42
    0xFFD0, 8, 0x01E4, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RBP = 43
    0xFFC8, 8, 0x01E8, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RSI = 44
    0xFFC0, 8, 0x01EC, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RDI = 45
    0xFF78, 8, 0x01F0, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RIP = 46
    0, 0, 0, 0, TRUE, // 47
    0, 0, 0, 0, TRUE, // 48
    0, 0, 0, 0, TRUE, // 49
    0, 0, 0, 0, TRUE, // 50
    0xFF70, 8, 0x01F4, 4, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RFLAGS = 51
    0xFF58, 8, 0x01FC, 4, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR0 = 52
    0xFF50, 8, 0x01F8, 4, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR3 = 53
    0xFF48, 8, 0x00F0, 4, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR4 = 54

    //Supported in XMM Save/restore function
    //EFI_SMM_SAVE_STATE_REGISTER_FCW = 256
    //EFI_SMM_SAVE_STATE_REGISTER_FSW = 257
    //EFI_SMM_SAVE_STATE_REGISTER_FTW = 258
    //EFI_SMM_SAVE_STATE_REGISTER_OPCODE = 259
    //EFI_SMM_SAVE_STATE_REGISTER_FP_EIP = 260
    //EFI_SMM_SAVE_STATE_REGISTER_FP_CS = 261
    //EFI_SMM_SAVE_STATE_REGISTER_DATAOFFSET = 262
    //EFI_SMM_SAVE_STATE_REGISTER_FP_DS = 263
    //EFI_SMM_SAVE_STATE_REGISTER_MM0 = 264
    //EFI_SMM_SAVE_STATE_REGISTER_MM1 = 265
    //EFI_SMM_SAVE_STATE_REGISTER_MM2 = 266
    //EFI_SMM_SAVE_STATE_REGISTER_MM3 = 267
    //EFI_SMM_SAVE_STATE_REGISTER_MM4 = 268
    //EFI_SMM_SAVE_STATE_REGISTER_MM5 = 269
    //EFI_SMM_SAVE_STATE_REGISTER_MM6 = 270
    //EFI_SMM_SAVE_STATE_REGISTER_MM7 = 271
    //EFI_SMM_SAVE_STATE_REGISTER_XMM0 = 272
    //EFI_SMM_SAVE_STATE_REGISTER_XMM1 = 273
    //EFI_SMM_SAVE_STATE_REGISTER_XMM2 = 274
    //EFI_SMM_SAVE_STATE_REGISTER_XMM3 = 275
    //EFI_SMM_SAVE_STATE_REGISTER_XMM4 = 276
    //EFI_SMM_SAVE_STATE_REGISTER_XMM5 = 277
    //EFI_SMM_SAVE_STATE_REGISTER_XMM6 = 278
    //EFI_SMM_SAVE_STATE_REGISTER_XMM7 = 279
    //EFI_SMM_SAVE_STATE_REGISTER_XMM8 = 280
    //EFI_SMM_SAVE_STATE_REGISTER_XMM9 = 281
    //EFI_SMM_SAVE_STATE_REGISTER_XMM10 = 282
    //EFI_SMM_SAVE_STATE_REGISTER_XMM11 = 283
    //EFI_SMM_SAVE_STATE_REGISTER_XMM12 = 284
    //EFI_SMM_SAVE_STATE_REGISTER_XMM13 = 285
    //EFI_SMM_SAVE_STATE_REGISTER_XMM14 = 286
    //EFI_SMM_SAVE_STATE_REGISTER_XMM15 = 287
    //
    // Pseudo-Registers
    //
    //EFI_SMM_SAVE_STATE_REGISTER_IO = 512
    //EFI_SMM_SAVE_STATE_REGISTER_LMA = 513
};

typedef enum {
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT8 = 0,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT16 = 1,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT32 = 2,
    CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT64 = 3
} CPULIB_SMM_SAVE_STATE_IO_WIDTH;

typedef enum {
    CPULIB_SMM_SAVE_STATE_IO_TYPE_INPUT = 1,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_OUTPUT = 2,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_STRING = 4,
    CPULIB_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX = 8
} CPULIB_SMM_SAVE_STATE_IO_TYPE;

typedef struct  {
    UINT64 IoData;
    UINT16 IoPort;
    CPULIB_SMM_SAVE_STATE_IO_WIDTH IoWidth;
    CPULIB_SMM_SAVE_STATE_IO_TYPE IoType;
} CPULIB_SMM_SAVE_STATE_IO_INFO;


/**
    Read SMM Save state from combination of SMM save state and copy.
    If frame copy exists, use its data instead from actual save state.
    A different function gets information for floating point and XMM.

        
    @param SmmBase SmmBase of CPU to read Save State.
    @param SstSaveState SMM Save state copy for Framework.
    @param UseSstSaveState True if Save state copy exists.
    @param Width Width in Bytes of register.
    @param Register Register Token in PI SMM.
    @param Buffer Read register into this buffer.

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
CpuLibSmmReadSaveState(
  IN    UINT8   *SmmBase,
  IN    UINT8   *SstSaveState,
  IN    BOOLEAN UseSstSaveState,
  IN    UINT8   Width,
  IN    UINT32  Register,
  OUT   VOID    *Buffer
)
{
    UINT32  Index = 0xFFFFFFFF;
//    UINTN   Offset;
    if (Register >= 47 && Register <= 50)
        return EFI_INVALID_PARAMETER;
    if (Register >= 20 && Register <= 54)
        Index = Register - 20;

    if (Index != 0xFFFFFFFF)
    {
        if (Width > gAMDX64Format[Index].SaveStateWidth)
            return EFI_INVALID_PARAMETER;

        switch (Width)
        {
            case 1:
                // Use SMM framework buffer if available, because copy may be updated by Framework driver, and copy will overwrite actual save state at end.
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT8*)Buffer = *(SstSaveState + gAMDX64Format[Index].FrameworkOffset);
                else
                    *(UINT8*)Buffer = *(SmmBase + gAMDX64Format[Index].SaveStateOffset);
                return EFI_SUCCESS;
            case 2:
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT16*)Buffer = *(UINT16*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset);
                else
                    *(UINT16*)Buffer = *(UINT16*)(SmmBase + gAMDX64Format[Index].SaveStateOffset);
                return EFI_SUCCESS;
            case 4:
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT32*)Buffer = *(UINT32*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset);
                else
                    *(UINT32*)Buffer = *(UINT32*)(SmmBase + gAMDX64Format[Index].SaveStateOffset);
                return EFI_SUCCESS;
            case 8:
                *(UINT64*)Buffer = *(UINT64*)(SmmBase + gAMDX64Format[Index].SaveStateOffset);

                // Use copy if available, because copy may be updated by Framework driver, and copy will overwrite actual save state at end. Copy doesn't support upper bits.
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT32*)Buffer = *(UINT32*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset);
                return EFI_SUCCESS;
        }
    }
    if (Register == EFI_SMM_SAVE_STATE_REGISTER_GDTBASE)
    {   // GDT
        if (Width != 4 && Width != 8)
            return EFI_INVALID_PARAMETER;
        if (Width == 8)
            *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xFE6C);
        *(UINT32*)Buffer =  *(UINT32*)(SmmBase + 0xFE68);

        // Use copy for lower 32-bits
        if (UseSstSaveState)
            *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x188);
        return EFI_SUCCESS;
    }

    if (Register == EFI_SMM_SAVE_STATE_REGISTER_IDTBASE)
    {   // IDT
        if (Width != 4 && Width != 8)
            return EFI_INVALID_PARAMETER;
        if (Width == 8)
            *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xFE8C);
        *(UINT32*)Buffer =  *(UINT32*)(SmmBase + 0xFE88);

        // Use copy for lower 32-bits
        if (UseSstSaveState)
            *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x194);
        return EFI_SUCCESS;
    }
    if (Register == EFI_SMM_SAVE_STATE_REGISTER_LDTBASE)
    {   // LDT
        if (Width != 4 && Width != 8)
            return EFI_INVALID_PARAMETER;
        if (Width == 8)
            *((UINT32*)Buffer + 1) =  *(UINT32*)(SmmBase + 0xFE7C);
        *(UINT32*)Buffer =  *(UINT32*)(SmmBase + 0xFE78);

        // Use copy for lower 32-bits
        if (UseSstSaveState)
            *(UINT32*)Buffer = *(UINT32*)(SstSaveState + 0x1C0);
        return EFI_SUCCESS;
    }

    if (Register == EFI_SMM_SAVE_STATE_REGISTER_LMA)
    {   // EFER
        UINT16  Efer;

        if (Width != 1)
            return EFI_INVALID_PARAMETER;

        Efer = *(UINT16*)(SmmBase + 0xFED0);
        *(UINT8*)Buffer = (Efer & BIT10) == BIT10 ? 64 : 32;
        return EFI_SUCCESS;
    }

    if (Register == EFI_SMM_SAVE_STATE_REGISTER_IO)
    {
        // Write code to save Io instruction data
        UINT32  IoMisc = *(UINT32*)(SmmBase + 0xFEC0);

        if (!(IoMisc & BIT01))
            return EFI_NOT_FOUND;   // If not valid return

        if (IoMisc & BIT04)
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoWidth = CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT8;
        else if (IoMisc & BIT05)
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoWidth = CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT16;
        else
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoWidth = CPULIB_SMM_SAVE_STATE_IO_WIDTH_UINT32;

        ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoPort = (UINT16)(IoMisc >> 16);

        if (IoMisc & BIT00)
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoType = CPULIB_SMM_SAVE_STATE_IO_TYPE_INPUT; // In
        else
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoType = CPULIB_SMM_SAVE_STATE_IO_TYPE_OUTPUT;    // Out

        if (IoMisc * BIT02)
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoType = CPULIB_SMM_SAVE_STATE_IO_TYPE_STRING;    // String

        if (IoMisc * BIT03)
            ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoType = CPULIB_SMM_SAVE_STATE_IO_TYPE_REP_PREFIX;    // Repeat

        // IO Restart RSI has the source value.
        ((CPULIB_SMM_SAVE_STATE_IO_INFO*)Buffer)->IoData = *(UINT64*)(SmmBase + 0xFEB0);    // Get RSI Value

        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED; //Register not supported.
}

/**
    Read SMM Save state for floating point and XMM.

        
    @param FxSave FxSave buffer.
    @param Width Width in Bytes of register.
    @param Register Register Token in PI SMM.
    @param Buffer Read register into this buffer.

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
CpuLibSmmReadSaveStateFxSave(
  IN    UINT8   *FxSave,
  IN    UINT8   Width,
  IN    UINT32  Register,
  OUT   VOID    *Buffer
)
{
    if (Register == 256)
    {   // FCW
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)Buffer = *(UINT16*)FxSave;
        return EFI_SUCCESS;
    }
    if (Register == 257)
    {   // FSW
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)Buffer = *(UINT16*)(FxSave + 2);
        return EFI_SUCCESS;
    }
    if (Register == 258)
    {   // FTW
        if (Width != 1)
            return EFI_INVALID_PARAMETER;

        *(UINT8*)Buffer = *(UINT8*)(FxSave + 4);
        return EFI_SUCCESS;
    }
    if (Register == 259)
    {   // FOP
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)Buffer = *(UINT16*)(FxSave + 6);
        return EFI_SUCCESS;
    }

    if (Register == 260)
    {   // FPU IP
        if (Width == 4)
        {
            MemCpy (Buffer, FxSave + 8, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8)
        {
            MemCpy (Buffer, FxSave + 8, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 261)
    {   // CS
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)Buffer = *(UINT16*)(FxSave + 12);
    }
#endif

    if (Register == 262)
    {   // FPU DP (DataOffset)
        if (Width == 4)
        {
            MemCpy (Buffer, FxSave + 16, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8)
        {
            MemCpy (Buffer, FxSave + 16, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 263)
    {   // DS
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)Buffer = *(UINT16*)(FxSave + 20);
    }
#endif

    if (Register >= 264 && Register <= 271)
    {   // MM0 - MM7
        if (Width != 10)
            return EFI_INVALID_PARAMETER;

        MemCpy (Buffer, FxSave + 32 + 16 * (Register - 264), 10);
        return EFI_SUCCESS;
    }
    if (Register >= 272 && Register <= 287)
    {   // XMM0 - XMM15
        if (Width != 16)
            return EFI_INVALID_PARAMETER;

        MemCpy (Buffer, FxSave + 160 + 16 * (Register - 272), 16);
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

/**
    Write SMM Save state from combination of SMM save state and copy.
    If frame copy exists, use its data instead from actual save state.
    A different function gets information for floating point and XMM.

        
    @param SmmBase SmmBase of CPU to read Save State.
    @param SstSaveState SMM Save state copy for Framework.
    @param UseSstSaveState True if Save state copy exists.
    @param Width Width in Bytes of register.
    @param Register Register Token in PI SMM.
    @param Buffer Write register into this buffer.

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
CpuLibSmmWriteSaveState(
  IN OUT    UINT8   *SmmBase,
  IN OUT    UINT8   *SstSaveState,
  IN        BOOLEAN UseSstSaveState,
  IN        UINT8   Width,
  IN        UINT32  Register,
  IN        VOID    *Buffer
)
{
    UINT32  Index = 0xFFFFFFFF;

    if (Register >= 47 && Register <= 50)
        return EFI_INVALID_PARAMETER;
    if (Register >= 20 && Register <= 54)
        Index = Register - 20;

    if (gAMDX64Format[Index].ReadOnly)
        return EFI_UNSUPPORTED;

    if (Index != 0xFFFFFFFF)
    {
        if (Width > gAMDX64Format[Index].SaveStateWidth)
            return EFI_INVALID_PARAMETER;

        switch (Width)
        {
            case 1:
                *(SmmBase + gAMDX64Format[Index].SaveStateOffset) = *(UINT8*)Buffer;

                // Copy to save state buffer for SMM framework.
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(SstSaveState + gAMDX64Format[Index].FrameworkOffset) = *(UINT8*)Buffer;
                return EFI_SUCCESS;
            case 2:
                *(UINT16*)(SmmBase + gAMDX64Format[Index].SaveStateOffset) = *(UINT16*)Buffer;
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT16*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset) = *(UINT16*)Buffer;
                return EFI_SUCCESS;
            case 4:
                *(UINT32*)(SmmBase + gAMDX64Format[Index].SaveStateOffset) = *(UINT32*)Buffer;
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT32*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset) = *(UINT32*)Buffer;
                return EFI_SUCCESS;
            case 8:
                *(UINT64*)(SmmBase + gAMDX64Format[Index].SaveStateOffset) = *(UINT64*)Buffer;
                if (UseSstSaveState && gAMDX64Format[Index].FrameworkWidth != 0xFF)
                    *(UINT32*)(SstSaveState + gAMDX64Format[Index].FrameworkOffset) = *(UINT32*)Buffer;
                return EFI_SUCCESS;
        }
    }

    return EFI_UNSUPPORTED;
}

/**
    Write SMM Save state for floating point and XMM.

        
    @param FxSave FxSave buffer.
    @param Width Width in Bytes of register.
    @param Register Register Token in PI SMM.
    @param Buffer Write register into this buffer.

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
CpuLibSmmWriteSaveStateFxSave(
  IN    UINT8   *FxSave,
  IN    UINT8   Width,
  IN    UINT32  Register,
  IN    VOID    *Buffer
)
{
    if (Register == 256)
    {   // FCW
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)FxSave = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 257)
    {   // FSW
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)(FxSave + 2) = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 258)
    {   // FTW
        if (Width != 1)
            return EFI_INVALID_PARAMETER;

        *(UINT8*)(FxSave + 4) = *(UINT8*)Buffer;
        return EFI_SUCCESS;
    }
    if (Register == 259)
    {   // FOP
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)(FxSave + 6) = *(UINT16*)Buffer;
        return EFI_SUCCESS;
    }

    if (Register == 260)
    {   // FPU IP
        if (Width == 4)
        {
            MemCpy (FxSave + 8, Buffer, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8)
        {
            MemCpy (FxSave + 8, Buffer, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 261)
    {   // CS
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)(FxSave + 12) = *(UINT16*)Buffer;
    }
#endif

    if (Register == 262)
    {   // FPU DP (DataOffset)
        if (Width == 4)
        {
            MemCpy (FxSave + 16, Buffer, 4);
            return EFI_SUCCESS;
        }
#if x64_BUILD
        if (Width == 8)
        {
            MemCpy (FxSave + 16, Buffer, 8);
            return EFI_SUCCESS;
        }
#endif
        return EFI_INVALID_PARAMETER;
    }

#if x64_BUILD == 0
    if (Register == 263)
    {   // DS
        if (Width != 2)
            return EFI_INVALID_PARAMETER;

        *(UINT16*)(FxSave + 20) = *(UINT16*)Buffer ;
    }
#endif

    if (Register >= 264 && Register <= 271)
    {   // MM0 - MM7
        if (Width != 10)
            return EFI_INVALID_PARAMETER;

        MemCpy (FxSave + 32 + 16 * (Register - 264), Buffer, 10);
        return EFI_SUCCESS;
    }
    if (Register >= 272 && Register <= 287)
    {   // XMM0 - XMM15
        if (Width != 16)
            return EFI_INVALID_PARAMETER;

        MemCpy (FxSave + 160 + 16 * (Register - 272), Buffer, 16);
        return EFI_SUCCESS;
    }
    return EFI_UNSUPPORTED;
}

/**
    This routine checks to see if the cpu caused an software smi.

        
    @param SmmBase 
    @param SwSmiPort 

         
    @retval EFI_STATUS return the EFI status

**/

BOOLEAN
IsSwSmiTrigger (
  IN    UINT8   *SmmBase,
  IN    UINT16  SwSmiPort
)
{
//    UINT32 IO_MISC_INFO = *(UINT32*)(SmmBase + 0xFFA4);

//    if (!(IO_MISC_INFO & 1)) return FALSE;  // For valid data, this should be 1.
//    return (*((UINT16*)&IO_MISC_INFO + 1) == SwSmiPort);  //[31:16]

    UINT16              SmmRevision;
    UINT32              IoTrap;
    AMD_64_SAVE_STATE   *SmmSave;

    SmmBase = ((UINT8 *)SmmBase + 0xFE00);
    SmmSave = (AMD_64_SAVE_STATE *) SmmBase;
    SmmRevision = (UINT16)((EFI_SMI_CPU_SAVE_STATE*)SmmBase)->SMMRevId;
    IoTrap = SmmSave->IOTrap;

    // Check the SMM save state revision
    if ((SmmRevision & 0xFF) == 0x64)
    {
        // Check the I/O trap register validity
        if ((IoTrap & 0x02) && (!(IoTrap & 0x01)))
        {
            // I/O trap is valid and it is write to I/O port
            // Check for I/O port match
            if ((IoTrap >> 16) == SwSmiPort)
                return TRUE;
        }
    }
    return FALSE;
}

/**
    Returns the total number of CPU cores in the system

        
    @param VOID

         
    @retval UINT32 CPU core count

**/

UINT32
AmdCpuCount(
    VOID
)
{
    UINT32  CpuCnt = 0;
    UINT32  RegEcx = 0;
 
    if (IsFamily15h())
    {//It's family 15
        IoWrite32(0xCF8, (1 << 31) | (AMD_K8_BUS_DEV << 11) | \
                    (AMD_K8_LDT_FUNC << 8) | AMD_K8_nF0_NODE_ID); // 0x60
        CpuCnt = (IoRead32(0xCFC) >> 16) & 0x1F;
        CpuCnt++;   // Zero base , so add one to the correct value
    }
    else
    {//It's family 17
        AsmCpuid(AMD_EXT_CPUID_8, NULL, NULL, &RegEcx, NULL);
        CpuCnt = (RegEcx & 0x0FF) + 1;
    }

    return CpuCnt;
}

/**
    Return the Smrr Base Msr

        
    @param VOID

         
    @retval UINT32 SMRR Base

**/

UINT32
GetSmrrBaseMsr(
    VOID
)
{
    return 0xA0;
}


/**
    This is SMM code copied to 3000:8000 to set the SmmBase and IED.

        
    @param VOID

         
    @retval VOID

    @note  
      This is in real mode. To generate 16-bit code opcodes, use a small asm
      file to generate a listing.
**/

UINT8
SmmBaseChangeCopy[] =
{                                       //cs = 0x3000
    0x66, 0xB8, 0x00, 0x00, 0x00, 0x00, //0x8000    mov eax, SMM_BASE
    0xBB, 0x00, 0x00,                   //0x8006    mov bx, 0     ;Location SM BASE OFFSET
    0x66, 0x2E, 0x89, 0x07,             //0x8009    mov cs:[bx], eax
// This is essential for SMM label 36 or later
    0x66, 0xBB, 0x01, 0x00, 0x00, 0x00, //0x800d    mov ebx, 1
    0x67, 0x66, 0x89, 0x98, 4,0x80,0,0, //0x8013    mov [eax + 8004h], ebx  ;Set SMM initialization
// Below code related to SMRR is not appropriate with AMD processors, all fill in NOP(0x90) instruction
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x801b    mov eax, IED_BASE
    0x90, 0x90, 0x90,                   // 0x8021    mov bx, 0     ;Location of IED_SAVESTATE_OFFSET
    0x90, 0x90, 0x90, 0x90,             // 0x8024    mov cs:[bx], eax
    0x90, 0x90,                         // 0x8028    jmp NO_SMRR   ;If SMRR, this will be changed to NOPs.
//SMRR:
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x802a    mov ecx, 0    ;MSR_SMRR_PHYS_BASE will be updated after copy.
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x8030    mov eax, 0    ;This will be updated after copy.
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x8036    mov edx, 0    ;This will be updated after copy.
    0x90, 0x90,                         // 0x803c    wrmsr
    0x90, 0x90,                         // 0x803e    inc ecx       ;MSR_SMRR_PHYS_MASK
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x8040    mov eax, 0    ;This will be updated after copy.
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // 0x8046    mov edx, 0    ;This will be updated after copy.
    0x90, 0x90,                         // 0x804c    wrmsr
//NO_SMRR:
    0xB0, 0x01,                         //0x804e    mov al, 1
    0x2E, 0xA2, 0x56, 0x80,             //0x8050    mov cs:[0x8056], al     ;set flag
    0x0F, 0xAA,                         //0x8054    rsm
    0x00                                //0x8056    SmmBaseChangeFlag label byte
};

// This initialization is essential for SMM label 36 or later
    #define SMM_ASM_FIXUP_SMM_BASE                  0x38002
    #define SMM_ASM_FIXUP_SMM_BASE_SAVESTATE_OFFSET 0x38007
    #define SMM_ASM_FIXUP_IED_BASE                  0x3801D
    #define SMM_ASM_FIXUP_IED_SAVESTATE_OFFSET      0x38022
    #define SMM_ASM_FIXUP_USE_SMRR                  0x38028
    #define SMM_ASM_FIXUP_MSR_SMRR_BASE             0x3802C
    #define SMM_ASM_FIXUP_SMRR_BASE_EAX             0x38032
    #define SMM_ASM_FIXUP_SMRR_BASE_EDX             0x38038
    #define SMM_ASM_FIXUP_SMRR_MASK_EAX             0x38042
    #define SMM_ASM_FIXUP_SMRR_MASK_EDX             0x38048
    #define SMM_ASM_BASE_CHANGE_FLAG                0x38056

/**
    Each CPU calls this routine one at a time. This routine causes
    its CPU to enter in SMI.

        
    @param VOID

         
    @retval VOID

    @note  
      Each CPU generates its on SMI to solve earlier syncronization issues causing
      some CPUs multiple cores to be in SMM at the same time corrupting the
      save state.

**/

UINT32
SmmGetBaseSaveBufferSize(
    VOID
)
{
    return sizeof(SmmBaseChangeCopy) + MAX_SMM_SAVE_STATE_SIZE;
}

/**
    Determine if Smrr is enabled.

        
    @param VOID

         
    @retval BOOLEAN True if Smrr is enabled.

**/

BOOLEAN
CpuLibIsSmrrEnabled(
    VOID
)
{
   return FALSE;
}

/**
    Save original memory, and copy SMM default handler.

        
    @param SmmBaseSaveBuffer 
    @param SmmHob 

         
    @retval VOID

**/

VOID
SmmSetupDefaultHandler(
  IN    VOID    *SmmBaseSaveBuffer,
  IN    SMM_HOB *SmmHob
)
{
    //Perserve 3000:8000 used by SMM. It will be overwritten.
    MemCpy(SmmBaseSaveBuffer, (VOID*)0x38000, sizeof(SmmBaseChangeCopy));

    MemCpy((UINT8*)SmmBaseSaveBuffer + sizeof(SmmBaseChangeCopy),
            (UINT8*)0x40000 - MAX_SMM_SAVE_STATE_SIZE, MAX_SMM_SAVE_STATE_SIZE);
    MemCpy((VOID*)0x38000, SmmBaseChangeCopy, sizeof(SmmBaseChangeCopy));
// The code below is used only with SMM label 36 or later
    *(UINT16*)SMM_ASM_FIXUP_SMM_BASE_SAVESTATE_OFFSET = SMM_BASE_SAVE_STATE_OFFSET;
//    *(UINT16*)SMM_ASM_FIXUP_IED_SAVESTATE_OFFSET = IED_SAVESTATE_OFFSET;

    // Initialize SMRR
    if (CpuLibIsSmrrEnabled())
    {   // Could be disabled. Reset may not clear lock.
        UINT64  TsegMask = (0xFFFFFFFFF & (~(SmmHob->TsegLength - 1))) | (1 << 11);
        *(UINT16*)SMM_ASM_FIXUP_USE_SMRR = 0x9090;  // Jmp changed to NOPs.
        // Update SMRR MSR.
        *(UINT32*)SMM_ASM_FIXUP_MSR_SMRR_BASE = GetSmrrBaseMsr();
        // Update SMRR Base
        *(UINT32*)SMM_ASM_FIXUP_SMRR_BASE_EAX = (UINT32)SmmHob->Tseg;   // Lower 32-bits.
        *(UINT32*)SMM_ASM_FIXUP_SMRR_BASE_EDX = 0;  // Upper 32-bits.
        // Update SMRR Mask
        *(UINT32*)SMM_ASM_FIXUP_SMRR_MASK_EAX = (UINT32)TsegMask;   // Lower 32-bits.
        *(UINT32*)SMM_ASM_FIXUP_SMRR_MASK_EDX = 0;  // Upper 32-bits. SMRR Mask Reserved bits.
    }
}

/**
    Execute on each CPU to change its own base.

        
    @param SmmBase 

         
    @retval VOID

**/

VOID
SmmBaseChangeOnCpu(
  IN    VOID    *SmmBase
)
{
    UINT8   ApicId = (UINT8)(*(UINT32*)(LOCAL_APIC_BASE + APIC_ID_REGISTER) >> 24);
// The code below is used only with SMM label 36 or later
    *(UINT32*)SMM_ASM_FIXUP_SMM_BASE = (UINT32)SmmBase;
    *(UINT8*)SMM_ASM_BASE_CHANGE_FLAG  = 0;  //Initialize Flag

    // Send SMM IPI
    MemReadWrite32 ((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_HIGH_REGISTER), ApicId << 24, 0x00FFFFFF);
    MemReadWrite32 ((UINT32*)(LOCAL_APIC_BASE + APIC_ICR_LOW_REGISTER), (0 << 18) + (1 << 14) + (2 << 8), 0);

    while (!(*(volatile UINT8*)SMM_ASM_BASE_CHANGE_FLAG))
        CPULib_Pause(); // Wait on Flag
}


/**
    Remove default SMM Handler from memory and restore original data.

        
    @param SmmBaseSaveBuffer 

         
    @retval VOID

**/

VOID
SmmRemoveDefaultHandler(
  IN    VOID    *SmmBaseSaveBuffer
)
{
    // Restore 3000:8000 overwritten for SMM
    MemCpy((VOID*)0x38000, SmmBaseSaveBuffer, sizeof(SmmBaseChangeCopy));
    MemCpy((UINT8*)0x40000 - MAX_SMM_SAVE_STATE_SIZE,
            (UINT8*)SmmBaseSaveBuffer + sizeof(SmmBaseChangeCopy), MAX_SMM_SAVE_STATE_SIZE);
}

/**
    Returns the total number of Nodes in the system

        
    @param VOID

         
    @retval UINT32 CPU Node count

**/

UINT32
AmdNodeCount(
    VOID
)
{
    return 1;   // Suppose it's 1 for mobile and desktop system
}

/**
    Determine if CPU is DualNode.

    @param VOID

         
    @retval TRUE if DualNode.

**/

BOOLEAN
IsDualNode(
    VOID
)
{
    IoWrite32 (0xCF8, (1 << 31) | (AMD_K8_BUS_DEV << 11) | (AMD_K8_MISC_FUNC << 8) | AMD_K8_nF3_NB_CAP);    // 0xE8
    return (IoRead32 (0xCFC) & 1);
}

/**
    Save CPU state in SMM.

        
    @param State Track CPU state.

    @retval VOID
**/

VOID
CpuLibSmmSaveCpuState(
  IN OUT    CPU_LIB_SMM_SAVE_RESTORE_DATA   *State
)
{

}

/**
    Restore CPU state in SMM.

        
    @param State Track CPU state.

    @retval VOID
**/

VOID
CpuLibSmmRestoreCpuState(
  IN    CPU_LIB_SMM_SAVE_RESTORE_DATA   *State
)
{

}



/**
    Check if this is family 15h CPU in the system 

        
    @param VOID

         
    @retval BOOLEAN True - It's family 15h CPU(BR)

**/

BOOLEAN
IsFamily15h(VOID)
{
    UINT32  RegEax = 0;

    AsmCpuid(AMD_EXT_CPUID_1, &RegEax, NULL, NULL, NULL);
    if ((RegEax & AMI_RAW_FAMILY_ID_MASK) == AMI_F15_BR_RAW_ID)
    {//It's family 15
        return TRUE;
    }
    else
    {//It's family 17
        return FALSE;
    }

}

/**
    Clear MemSafe bit when setup option changes something. Clear BIT1, PcdCmosAgesaSpecified (CMOS_AGESA_SPECIFIED)

    @param VOID

    @retval VOID

**/

VOID
SetupQuestionChanged(
    VOID
)
{
    UINT8   Value8;

    IoWrite8 (0x72, PcdGet8 (PcdCmosAgesaSpecified));
    Value8 = IoRead8 (0x73);    // Read from CMOS
    Value8 &= ~BIT1;
    IoWrite8(0x73, Value8); // Save to CMOS
}

/**
    Return CpuId for checking CPU now on board.

        
    @param VOID

         
    @retval UINT32 CpuId read from cpu instruction 0x80000001.

**/

UINT32
GetCpuRawId(VOID)
{
    UINT32  RegEax = 0;

    AsmCpuid(AMD_EXT_CPUID_1, &RegEax, NULL, NULL, NULL);
    return (RegEax & AMI_RAW_FAMILY_ID_MASK);
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

