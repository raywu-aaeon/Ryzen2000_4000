/** @file
The CPU specific programming for PiSmmCpuDxeSmm module.

Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiSmm.h>
#include <Library/SmmCpuFeaturesLib.h>
#include <Library/BaseLib.h>
#include <Library/MtrrLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Register/Cpuid.h>
#include <Register/SmramSaveStateMap.h>
//(AMI AMD Porting)>> For getting Smbase
#include <CpuHotPlugData.h>
//(AMI AMD Porting)<<
//
// Machine Specific Registers (MSRs)
//
#define  SMM_FEATURES_LIB_IA32_MTRR_CAP            0x0FE
#define  SMM_FEATURES_LIB_IA32_FEATURE_CONTROL     0x03A
#define  SMM_FEATURES_LIB_IA32_SMRR_PHYSBASE       0x1F2
#define  SMM_FEATURES_LIB_IA32_SMRR_PHYSMASK       0x1F3
#define  SMM_FEATURES_LIB_IA32_CORE_SMRR_PHYSBASE  0x0A0
#define  SMM_FEATURES_LIB_IA32_CORE_SMRR_PHYSMASK  0x0A1
#define    EFI_MSR_SMRR_MASK                       0xFFFFF000
#define    EFI_MSR_SMRR_PHYS_MASK_VALID            BIT11
#define  SMM_FEATURES_LIB_SMM_FEATURE_CONTROL      0x4E0

//
// MSRs required for configuration of SMM Code Access Check
//
#define SMM_FEATURES_LIB_IA32_MCA_CAP              0x17D
#define   SMM_CODE_ACCESS_CHK_BIT                  BIT58

/**
  Internal worker function that is called to complete CPU initialization at the
  end of SmmCpuFeaturesInitializeProcessor().

**/
VOID
FinishSmmCpuFeaturesInitializeProcessor (
  VOID
  );

//
// Set default value to assume SMRR is not supported
//
BOOLEAN  mSmrrSupported = FALSE;

//
// Set default value to assume MSR_SMM_FEATURE_CONTROL is not supported
//
BOOLEAN  mSmmFeatureControlSupported = FALSE;

//
// Set default value to assume IA-32 Architectural MSRs are used
//
UINT32  mSmrrPhysBaseMsr = SMM_FEATURES_LIB_IA32_SMRR_PHYSBASE;
UINT32  mSmrrPhysMaskMsr = SMM_FEATURES_LIB_IA32_SMRR_PHYSMASK;

//
// Set default value to assume MTRRs need to be configured on each SMI
//
BOOLEAN  mNeedConfigureMtrrs = TRUE;

//
// Array for state of SMRR enable on all CPUs
//
BOOLEAN  *mSmrrEnabled;

// (AMI AMD Porting)>> Added AMD SMRAM save state sturcture
extern CPU_HOT_PLUG_DATA      mCpuHotPlugData;
#pragma pack (1)
typedef struct {
    UINT16 SaveStateOffset;
    UINT16 SaveStateWidth;
    BOOLEAN ReadOnly;
} AMD_X64_FORMAT;

AMD_X64_FORMAT gAmdX64Format[] = {
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTBASE = 4
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTBASE = 5
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTBASE = 6
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_GDTLIMIT = 7
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_IDTLIMIT = 8
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTLIMIT = 9
    //Treat special case - EFI_SMM_SAVE_STATE_REGISTER_LDTINFO = 10
    0xfe00, 2, TRUE, //EFI_SMM_SAVE_STATE_REGISTER_ES = 20
    0xfe10, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CS = 21
    0xfe20, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_SS = 22
    0xfe30, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_DS = 23
    0xfe40, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_FS = 24
    0xfe50, 2, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_GS = 25
    0xfe70, 2, TRUE, //EFI_SMM_SAVE_STATE_REGISTER_LDTR_SEL = 26
    0xfe90, 2, TRUE,   //EFI_SMM_SAVE_STATE_REGISTER_TR_SEL = 27
    0xff60, 8, TRUE,  //EFI_SMM_SAVE_STATE_REGISTER_DR7 = 28
    0xff68, 8, TRUE,   //EFI_SMM_SAVE_STATE_REGISTER_DR6 = 29
    0xffb8, 8, FALSE, //EFI_SMM_SAVE_STATE_REGISTER_R8 = 30
    0xffb0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R9 = 31
    0xffa8, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R10 = 32
    0xffa0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R11 = 33
    0xff98, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R12 = 34
    0xff90, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R13 = 35
    0xff88, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R14 = 36
    0xff80, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_R15 = 37
    0xfff8, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RAX = 38
    0xffe0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RBX = 39
    0xfff0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RCX = 40
    0xffe8, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RDX = 41
    0xffd8, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RSP = 42
    0xffd0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RBP = 43
    0xffc8, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RSI = 44
    0xffc0, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RDI = 45
    0xff78, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RIP = 46
    0, 0, TRUE, // 47
    0, 0, TRUE, // 48
    0, 0, TRUE, // 49
    0, 0, TRUE, // 50
    0xff70, 8, FALSE,//EFI_SMM_SAVE_STATE_REGISTER_RFLAGS = 51
    0xff58, 8, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR0 = 52
    0xff50, 8, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR3 = 53
    0xff48, 8, TRUE,//EFI_SMM_SAVE_STATE_REGISTER_CR4 = 54

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
#pragma pack ()
// (AMI AMD Porting)<< 
/**
  The constructor function

  @param[in]  ImageHandle  The firmware allocated handle for the EFI image.
  @param[in]  SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS      The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
SmmCpuFeaturesLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // (AMI AMD Porting)>> AMD doesn't have these features
  /*
  UINT32  RegEax;
  UINT32  RegEdx;
  UINTN   FamilyId;
  UINTN   ModelId;

  //
  // Retrieve CPU Family and Model
  //
  AsmCpuid (CPUID_VERSION_INFO, &RegEax, NULL, NULL, &RegEdx);
  FamilyId = (RegEax >> 8) & 0xf;
  ModelId  = (RegEax >> 4) & 0xf;
  if (FamilyId == 0x06 || FamilyId == 0x0f) {
    ModelId = ModelId | ((RegEax >> 12) & 0xf0);
  }

  //
  // Check CPUID(CPUID_VERSION_INFO).EDX[12] for MTRR capability
  //
  if ((RegEdx & BIT12) != 0) {
    //
    // Check MTRR_CAP MSR bit 11 for SMRR support
    //
    if ((AsmReadMsr64 (SMM_FEATURES_LIB_IA32_MTRR_CAP) & BIT11) != 0) {
      mSmrrSupported = TRUE;
    }
  }

  //
  // Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  // Volume 3C, Section 35.3 MSRs in the Intel(R) Atom(TM) Processor Family
  //
  // If CPU Family/Model is 06_1CH, 06_26H, 06_27H, 06_35H or 06_36H, then
  // SMRR Physical Base and SMM Physical Mask MSRs are not available.
  //
  if (FamilyId == 0x06) {
    if (ModelId == 0x1C || ModelId == 0x26 || ModelId == 0x27 || ModelId == 0x35 || ModelId == 0x36) {
      mSmrrSupported = FALSE;
    }
  }

  //
  // Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  // Volume 3C, Section 35.2 MSRs in the Intel(R) Core(TM) 2 Processor Family
  //
  // If CPU Family/Model is 06_0F or 06_17, then use Intel(R) Core(TM) 2
  // Processor Family MSRs
  //
  if (FamilyId == 0x06) {
    if (ModelId == 0x17 || ModelId == 0x0f) {
      mSmrrPhysBaseMsr = SMM_FEATURES_LIB_IA32_CORE_SMRR_PHYSBASE;
      mSmrrPhysMaskMsr = SMM_FEATURES_LIB_IA32_CORE_SMRR_PHYSMASK;
    }
  }

  //
  // Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  // Volume 3C, Section 34.4.2 SMRAM Caching
  //   An IA-32 processor does not automatically write back and invalidate its
  //   caches before entering SMM or before exiting SMM. Because of this behavior,
  //   care must be taken in the placement of the SMRAM in system memory and in
  //   the caching of the SMRAM to prevent cache incoherence when switching back
  //   and forth between SMM and protected mode operation.
  //
  // An IA-32 processor is a processor that does not support the Intel 64
  // Architecture.  Support for the Intel 64 Architecture can be detected from
  // CPUID(CPUID_EXTENDED_CPU_SIG).EDX[29]
  //
  // If an IA-32 processor is detected, then set mNeedConfigureMtrrs to TRUE,
  // so caches are flushed on SMI entry and SMI exit, the interrupted code
  // MTRRs are saved/restored, and MTRRs for SMM are loaded.
  //
  AsmCpuid (CPUID_EXTENDED_FUNCTION, &RegEax, NULL, NULL, NULL);
  if (RegEax >= CPUID_EXTENDED_CPU_SIG) {
    AsmCpuid (CPUID_EXTENDED_CPU_SIG, NULL, NULL, NULL, &RegEdx);
    if ((RegEdx & BIT29) != 0) {
      mNeedConfigureMtrrs = FALSE;
    }
  }

  //
  // Allocate array for state of SMRR enable on all CPUs
  //
  mSmrrEnabled = (BOOLEAN *)AllocatePool (sizeof (BOOLEAN) * PcdGet32 (PcdCpuMaxLogicalProcessorNumber));
  ASSERT (mSmrrEnabled != NULL);
*/
  mNeedConfigureMtrrs = FALSE;
  // (AMI AMD Porting)<<
  return EFI_SUCCESS;
}

/**
  Called during the very first SMI into System Management Mode to initialize
  CPU features, including SMBASE, for the currently executing CPU.  Since this
  is the first SMI, the SMRAM Save State Map is at the default address of
  SMM_DEFAULT_SMBASE + SMRAM_SAVE_STATE_MAP_OFFSET.  The currently executing
  CPU is specified by CpuIndex and CpuIndex can be used to access information
  about the currently executing CPU in the ProcessorInfo array and the
  HotPlugCpuData data structure.

  @param[in] CpuIndex        The index of the CPU to initialize.  The value
                             must be between 0 and the NumberOfCpus field in
                             the System Management System Table (SMST).
  @param[in] IsMonarch       TRUE if the CpuIndex is the index of the CPU that
                             was elected as monarch during System Management
                             Mode initialization.
                             FALSE if the CpuIndex is not the index of the CPU
                             that was elected as monarch during System
                             Management Mode initialization.
  @param[in] ProcessorInfo   Pointer to an array of EFI_PROCESSOR_INFORMATION
                             structures.  ProcessorInfo[CpuIndex] contains the
                             information for the currently executing CPU.
  @param[in] CpuHotPlugData  Pointer to the CPU_HOT_PLUG_DATA structure that
                             contains the ApidId and SmBase arrays.
**/
VOID
EFIAPI
SmmCpuFeaturesInitializeProcessor (
  IN UINTN                      CpuIndex,
  IN BOOLEAN                    IsMonarch,
  IN EFI_PROCESSOR_INFORMATION  *ProcessorInfo,
  IN CPU_HOT_PLUG_DATA          *CpuHotPlugData
  )
{
  SMRAM_SAVE_STATE_MAP  *CpuState;
  // (AMI AMD Porting)>> AMD doesn't have these features
  /*
  UINT64                FeatureControl;
  UINT32                RegEax;
  UINT32                RegEdx;
  UINTN                 FamilyId;
  UINTN                 ModelId;
*/
  // (AMI AMD Porting)<<
  //
  // Configure SMBASE.
  //
  CpuState = (SMRAM_SAVE_STATE_MAP *)(UINTN)(SMM_DEFAULT_SMBASE + SMRAM_SAVE_STATE_MAP_OFFSET);
  CpuState->x86.SMBASE = (UINT32)CpuHotPlugData->SmBase[CpuIndex];
  // (AMI AMD Porting)>> AMD doesn't h have these features
  /*
  //
  // Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  // Volume 3C, Section 35.2 MSRs in the Intel(R) Core(TM) 2 Processor Family
  //
  // If Intel(R) Core(TM) Core(TM) 2 Processor Family MSRs are being used, then
  // make sure SMRR Enable(BIT3) of MSR_FEATURE_CONTROL MSR(0x3A) is set before
  // accessing SMRR base/mask MSRs.  If Lock(BIT0) of MSR_FEATURE_CONTROL MSR(0x3A)
  // is set, then the MSR is locked and can not be modified.
  //
  if (mSmrrSupported && mSmrrPhysBaseMsr == SMM_FEATURES_LIB_IA32_CORE_SMRR_PHYSBASE) {
    FeatureControl = AsmReadMsr64 (SMM_FEATURES_LIB_IA32_FEATURE_CONTROL);
    if ((FeatureControl & BIT3) == 0) {
      if ((FeatureControl & BIT0) == 0) {
        AsmWriteMsr64 (SMM_FEATURES_LIB_IA32_FEATURE_CONTROL, FeatureControl | BIT3);
      } else {
        mSmrrSupported = FALSE;
      }
    }
  }

  //
  // If SMRR is supported, then program SMRR base/mask MSRs.
  // The EFI_MSR_SMRR_PHYS_MASK_VALID bit is not set until the first normal SMI.
  // The code that initializes SMM environment is running in normal mode
  // from SMRAM region.  If SMRR is enabled here, then the SMRAM region
  // is protected and the normal mode code execution will fail.
  //
  if (mSmrrSupported) {
    //
    // SMRR size cannot be less than 4-KBytes
    // SMRR size must be of length 2^n
    // SMRR base alignment cannot be less than SMRR length
    //
    if ((CpuHotPlugData->SmrrSize < SIZE_4KB) ||
        (CpuHotPlugData->SmrrSize != GetPowerOfTwo32 (CpuHotPlugData->SmrrSize)) ||
        ((CpuHotPlugData->SmrrBase & ~(CpuHotPlugData->SmrrSize - 1)) != CpuHotPlugData->SmrrBase)) {
      //
      // Print message and halt if CPU is Monarch
      //
      if (IsMonarch) {
        DEBUG ((DEBUG_ERROR, "SMM Base/Size does not meet alignment/size requirement!\n"));
        CpuDeadLoop ();
      }
    } else {
      AsmWriteMsr64 (mSmrrPhysBaseMsr, CpuHotPlugData->SmrrBase | MTRR_CACHE_WRITE_BACK);
      AsmWriteMsr64 (mSmrrPhysMaskMsr, (~(CpuHotPlugData->SmrrSize - 1) & EFI_MSR_SMRR_MASK));
      mSmrrEnabled[CpuIndex] = FALSE;
    }
  }

  //
  // Retrieve CPU Family and Model
  //
  AsmCpuid (CPUID_VERSION_INFO, &RegEax, NULL, NULL, &RegEdx);
  FamilyId = (RegEax >> 8) & 0xf;
  ModelId  = (RegEax >> 4) & 0xf;
  if (FamilyId == 0x06 || FamilyId == 0x0f) {
    ModelId = ModelId | ((RegEax >> 12) & 0xf0);
  }

  //
  // Intel(R) 64 and IA-32 Architectures Software Developer's Manual
  // Volume 3C, Section 35.10.1 MSRs in 4th Generation Intel(R) Core(TM)
  // Processor Family.
  //
  // If CPU Family/Model is 06_3C, 06_45, or 06_46 then use 4th Generation
  // Intel(R) Core(TM) Processor Family MSRs.
  //
  if (FamilyId == 0x06) {
    if (ModelId == 0x3C || ModelId == 0x45 || ModelId == 0x46 ||
        ModelId == 0x3D || ModelId == 0x47 || ModelId == 0x4E || ModelId == 0x4F ||
        ModelId == 0x3F || ModelId == 0x56 || ModelId == 0x57 || ModelId == 0x5C) {
      //
      // Check to see if the CPU supports the SMM Code Access Check feature
      // Do not access this MSR unless the CPU supports the SmmRegFeatureControl
      //
      if ((AsmReadMsr64 (SMM_FEATURES_LIB_IA32_MCA_CAP) & SMM_CODE_ACCESS_CHK_BIT) != 0) {
        mSmmFeatureControlSupported = TRUE;
      }
    }
  }
*/
  // (AMI AMD Porting)<<
  //
  //  Call internal worker function that completes the CPU initialization
  //
  FinishSmmCpuFeaturesInitializeProcessor ();
}

/**
  This function updates the SMRAM save state on the currently executing CPU
  to resume execution at a specific address after an RSM instruction.  This
  function must evaluate the SMRAM save state to determine the execution mode
  the RSM instruction resumes and update the resume execution address with
  either NewInstructionPointer32 or NewInstructionPoint.  The auto HALT restart
  flag in the SMRAM save state must always be cleared.  This function returns
  the value of the instruction pointer from the SMRAM save state that was
  replaced.  If this function returns 0, then the SMRAM save state was not
  modified.

  This function is called during the very first SMI on each CPU after
  SmmCpuFeaturesInitializeProcessor() to set a flag in normal execution mode
  to signal that the SMBASE of each CPU has been updated before the default
  SMBASE address is used for the first SMI to the next CPU.

  @param[in] CpuIndex                 The index of the CPU to hook.  The value
                                      must be between 0 and the NumberOfCpus
                                      field in the System Management System Table
                                      (SMST).
  @param[in] CpuState                 Pointer to SMRAM Save State Map for the
                                      currently executing CPU.
  @param[in] NewInstructionPointer32  Instruction pointer to use if resuming to
                                      32-bit execution mode from 64-bit SMM.
  @param[in] NewInstructionPointer    Instruction pointer to use if resuming to
                                      same execution mode as SMM.

  @retval 0    This function did modify the SMRAM save state.
  @retval > 0  The original instruction pointer value from the SMRAM save state
               before it was replaced.
**/
UINT64
EFIAPI
SmmCpuFeaturesHookReturnFromSmm (
  IN UINTN                 CpuIndex,
  IN SMRAM_SAVE_STATE_MAP  *CpuState,
  IN UINT64                NewInstructionPointer32,
  IN UINT64                NewInstructionPointer
  )
{
  return 0;
}

/**
  Hook point in normal execution mode that allows the one CPU that was elected
  as monarch during System Management Mode initialization to perform additional
  initialization actions immediately after all of the CPUs have processed their
  first SMI and called SmmCpuFeaturesInitializeProcessor() relocating SMBASE
  into a buffer in SMRAM and called SmmCpuFeaturesHookReturnFromSmm().
**/
VOID
EFIAPI
SmmCpuFeaturesSmmRelocationComplete (
  VOID
  )
{
}

/**
  Determines if MTRR registers must be configured to set SMRAM cache-ability
  when executing in System Management Mode.

  @retval TRUE   MTRR registers must be configured to set SMRAM cache-ability.
  @retval FALSE  MTRR registers do not need to be configured to set SMRAM
                 cache-ability.
**/
BOOLEAN
EFIAPI
SmmCpuFeaturesNeedConfigureMtrrs (
  VOID
  )
{
  return mNeedConfigureMtrrs;
}

/**
  Disable SMRR register if SMRR is supported and SmmCpuFeaturesNeedConfigureMtrrs()
  returns TRUE.
**/
VOID
EFIAPI
SmmCpuFeaturesDisableSmrr (
  VOID
  )
{
  if (mSmrrSupported && mNeedConfigureMtrrs) {
    AsmWriteMsr64 (mSmrrPhysMaskMsr, AsmReadMsr64(mSmrrPhysMaskMsr) & ~EFI_MSR_SMRR_PHYS_MASK_VALID);
  }
}

/**
  Enable SMRR register if SMRR is supported and SmmCpuFeaturesNeedConfigureMtrrs()
  returns TRUE.
**/
VOID
EFIAPI
SmmCpuFeaturesReenableSmrr (
  VOID
  )
{
  if (mSmrrSupported && mNeedConfigureMtrrs) {
    AsmWriteMsr64 (mSmrrPhysMaskMsr, AsmReadMsr64(mSmrrPhysMaskMsr) | EFI_MSR_SMRR_PHYS_MASK_VALID);
  }
}

/**
  Processor specific hook point each time a CPU enters System Management Mode.

  @param[in] CpuIndex  The index of the CPU that has entered SMM.  The value
                       must be between 0 and the NumberOfCpus field in the
                       System Management System Table (SMST).
**/
VOID
EFIAPI
SmmCpuFeaturesRendezvousEntry (
  IN UINTN  CpuIndex
  )
{
  //
  // If SMRR is supported and this is the first normal SMI, then enable SMRR
  //
  if (mSmrrSupported && !mSmrrEnabled[CpuIndex]) {
    AsmWriteMsr64 (mSmrrPhysMaskMsr, AsmReadMsr64 (mSmrrPhysMaskMsr) | EFI_MSR_SMRR_PHYS_MASK_VALID);
    mSmrrEnabled[CpuIndex] = TRUE;
  }
}

/**
  Processor specific hook point each time a CPU exits System Management Mode.

  @param[in] CpuIndex  The index of the CPU that is exiting SMM.  The value must
                       be between 0 and the NumberOfCpus field in the System
                       Management System Table (SMST).
**/
VOID
EFIAPI
SmmCpuFeaturesRendezvousExit (
  IN UINTN  CpuIndex
  )
{
}

/**
  Check to see if an SMM register is supported by a specified CPU.

  @param[in] CpuIndex  The index of the CPU to check for SMM register support.
                       The value must be between 0 and the NumberOfCpus field
                       in the System Management System Table (SMST).
  @param[in] RegName   Identifies the SMM register to check for support.

  @retval TRUE   The SMM register specified by RegName is supported by the CPU
                 specified by CpuIndex.
  @retval FALSE  The SMM register specified by RegName is not supported by the
                 CPU specified by CpuIndex.
**/
BOOLEAN
EFIAPI
SmmCpuFeaturesIsSmmRegisterSupported (
  IN UINTN         CpuIndex,
  IN SMM_REG_NAME  RegName
  )
{
  if (mSmmFeatureControlSupported && RegName == SmmRegFeatureControl) {
    return TRUE;
  }
  return FALSE;
}

/**
  Returns the current value of the SMM register for the specified CPU.
  If the SMM register is not supported, then 0 is returned.

  @param[in] CpuIndex  The index of the CPU to read the SMM register.  The
                       value must be between 0 and the NumberOfCpus field in
                       the System Management System Table (SMST).
  @param[in] RegName   Identifies the SMM register to read.

  @return  The value of the SMM register specified by RegName from the CPU
           specified by CpuIndex.
**/
UINT64
EFIAPI
SmmCpuFeaturesGetSmmRegister (
  IN UINTN         CpuIndex,
  IN SMM_REG_NAME  RegName
  )
{
  if (mSmmFeatureControlSupported && RegName == SmmRegFeatureControl) {
    return AsmReadMsr64 (SMM_FEATURES_LIB_SMM_FEATURE_CONTROL);
  }
  return 0;
}

/**
  Sets the value of an SMM register on a specified CPU.
  If the SMM register is not supported, then no action is performed.

  @param[in] CpuIndex  The index of the CPU to write the SMM register.  The
                       value must be between 0 and the NumberOfCpus field in
                       the System Management System Table (SMST).
  @param[in] RegName   Identifies the SMM register to write.
                       registers are read-only.
  @param[in] Value     The value to write to the SMM register.
**/
VOID
EFIAPI
SmmCpuFeaturesSetSmmRegister (
  IN UINTN         CpuIndex,
  IN SMM_REG_NAME  RegName,
  IN UINT64        Value
  )
{
  if (mSmmFeatureControlSupported && RegName == SmmRegFeatureControl) {
    AsmWriteMsr64 (SMM_FEATURES_LIB_SMM_FEATURE_CONTROL, Value);
  }
}

/**
  Read an SMM Save State register on the target processor.  If this function
  returns EFI_UNSUPPORTED, then the caller is responsible for reading the
  SMM Save Sate register.

  @param[in]  CpuIndex  The index of the CPU to read the SMM Save State.  The
                        value must be between 0 and the NumberOfCpus field in
                        the System Management System Table (SMST).
  @param[in]  Register  The SMM Save State register to read.
  @param[in]  Width     The number of bytes to read from the CPU save state.
  @param[out] Buffer    Upon return, this holds the CPU register value read
                        from the save state.

  @retval EFI_SUCCESS           The register was read from Save State.
  @retval EFI_INVALID_PARAMTER  Buffer is NULL.
  @retval EFI_UNSUPPORTED       This function does not support reading Register.

**/
EFI_STATUS
EFIAPI
SmmCpuFeaturesReadSaveStateRegister (
  IN  UINTN                        CpuIndex,
  IN  EFI_SMM_SAVE_STATE_REGISTER  Register,
  IN  UINTN                        Width,
  OUT VOID                         *Buffer
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Writes an SMM Save State register on the target processor.  If this function
  returns EFI_UNSUPPORTED, then the caller is responsible for writing the
  SMM Save Sate register.

  @param[in] CpuIndex  The index of the CPU to write the SMM Save State.  The
                       value must be between 0 and the NumberOfCpus field in
                       the System Management System Table (SMST).
  @param[in] Register  The SMM Save State register to write.
  @param[in] Width     The number of bytes to write to the CPU save state.
  @param[in] Buffer    Upon entry, this holds the new CPU register value.

  @retval EFI_SUCCESS           The register was written to Save State.
  @retval EFI_INVALID_PARAMTER  Buffer is NULL.
  @retval EFI_UNSUPPORTED       This function does not support writing Register.
**/
EFI_STATUS
EFIAPI
SmmCpuFeaturesWriteSaveStateRegister (
  IN UINTN                        CpuIndex,
  IN EFI_SMM_SAVE_STATE_REGISTER  Register,
  IN UINTN                        Width,
  IN CONST VOID                   *Buffer
  )
{
//(AMI AMD Porting)>> Added the method of how to update AMD SMRAM save state 
    UINT32  Index = 0xffffffff;
    UINT8   *SmmBase;
    
    if (Register >= 47 && Register <= 50) return EFI_INVALID_PARAMETER;
    if (Register >= 20 && Register <= 54) Index = Register - 20;
    
    if(gAmdX64Format[Index].ReadOnly) return EFI_UNSUPPORTED;
    
    SmmBase = (UINT8*)mCpuHotPlugData.SmBase[CpuIndex];

    if (Index != 0xffffffff) {
        if (Width > gAmdX64Format[Index].SaveStateWidth) return EFI_INVALID_PARAMETER;
        switch(Width) {
        case 1:
            *(SmmBase + gAmdX64Format[Index].SaveStateOffset) = *(UINT8*)Buffer;
            return EFI_SUCCESS;
        case 2:
            *(UINT16*)(SmmBase + gAmdX64Format[Index].SaveStateOffset) = *(UINT16*)Buffer;
            return EFI_SUCCESS;
        case 4:
            *(UINT32*)(SmmBase + gAmdX64Format[Index].SaveStateOffset) = *(UINT32*)Buffer;
            return EFI_SUCCESS;
        case 8:
            *(UINT64*)(SmmBase + gAmdX64Format[Index].SaveStateOffset) = *(UINT64*)Buffer;
            return EFI_SUCCESS;
        default:
            return  EFI_INVALID_PARAMETER;
        }
    }
  return EFI_INVALID_PARAMETER;
//  return EFI_UNSUPPORTED;
//(AMI AMD Porting)<<
}

/**
  This function is hook point called after the gEfiSmmReadyToLockProtocolGuid
  notification is completely processed.
**/
VOID
EFIAPI
SmmCpuFeaturesCompleteSmmReadyToLock (
  VOID
  )
{
}

/**
  This API provides a method for a CPU to allocate a specific region for storing page tables.

  This API can be called more once to allocate memory for page tables.

  Allocates the number of 4KB pages of type EfiRuntimeServicesData and returns a pointer to the
  allocated buffer.  The buffer returned is aligned on a 4KB boundary.  If Pages is 0, then NULL
  is returned.  If there is not enough memory remaining to satisfy the request, then NULL is
  returned.

  This function can also return NULL if there is no preference on where the page tables are allocated in SMRAM.

  @param  Pages                 The number of 4 KB pages to allocate.

  @return A pointer to the allocated buffer for page tables.
  @retval NULL      Fail to allocate a specific region for storing page tables,
                    Or there is no preference on where the page tables are allocated in SMRAM.

**/
VOID *
EFIAPI
SmmCpuFeaturesAllocatePageTableMemory (
  IN UINTN           Pages
  )
{
  return NULL;
}

