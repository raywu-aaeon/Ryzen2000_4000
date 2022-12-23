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

/** @file CpuPei.c
    This file is the main CPU PEI component file. This component
    utilizes CPU I/O & PCI CFG PPI to publish early CPU Init PPI
    which can be used by NB PEI to load itself.  Also this file
    contains a CPU init routine to be executed in permanent memory
    present environment.  This is handled by issuing a notifyPPI
    on permanent memory PPI

**/

#include <Pei.h>
#include <Ppi/Stall.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <AmiPeiLib.h>
#include <CpuPei.h>
#include <AmiSmm.h>
#include <CpuCspLib.h>
#include <Hob.h>
#include <Nb.h>
#include <CpuSetupData.h>
#include <Ppi/CpuPolicy.h>
#include <Library/DebugLib.h>
#include <Library/PciExpressLib.h>
#if PeiRamBootSupport == 1
#if defined(AMD_SKIP_COPY_FV_BB) && (AMD_SKIP_COPY_FV_BB == 1)
#include <PeiRamBoot.h>
#endif
#endif
// Setup GUID variables for installing, locating and notifying PPIs  
EFI_GUID gAmiCpuinfoHobGuid				= AMI_CPUINFO_HOB_GUID;  

CHAR16  CpuS3ResumeVariable[] = CPU_S3_RESUME_VARIABLE;

#define	MEM_DET_COMMON_MEM_ATTR     (EFI_RESOURCE_ATTRIBUTE_PRESENT | \
                                    EFI_RESOURCE_ATTRIBUTE_INITIALIZED | \
                                    EFI_RESOURCE_ATTRIBUTE_TESTED | \
                                    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |\
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE)
                                    
#define	MEM_DET_COMMON_MEM_ATTR_ABOVE4G     (EFI_RESOURCE_ATTRIBUTE_PRESENT | \
                                    EFI_RESOURCE_ATTRIBUTE_INITIALIZED | \
                                    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |\
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE)

extern VOID InitMtrrFamily15(EFI_PEI_SERVICES **PeiServices);

EFI_STATUS
EFIAPI
EndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS 
EFIAPI
CpuInitAfterMemInstalled (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi 
);

static EFI_PEI_NOTIFY_DESCRIPTOR  NotifyList =
{
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiEndOfPeiSignalPpiGuid,
    EndOfPeiCallback
};

static EFI_PEI_NOTIFY_DESCRIPTOR CpuMemInstalledNotifyList[] = 
{
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gEfiPeiMemoryDiscoveredPpiGuid, CpuInitAfterMemInstalled },
};

static EFI_PEI_PPI_DESCRIPTOR  PpiAfterCpuPeiPpi = 
{
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmdAfterCpuPeiPpiGuid,
    NULL
};

#if PeiRamBootSupport == 1
#if defined(AMD_SKIP_COPY_FV_BB) && (AMD_SKIP_COPY_FV_BB == 1)
EFI_GUID    AmdNotSkipCopyFvBbPpiGuid = AMD_NOT_SKIP_COPY_FVBB_PPI_GUID;

EFI_PEI_PPI_DESCRIPTOR NotSkipCopyFvBbPpiList[] = {
  { (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &AmdNotSkipCopyFvBbPpiGuid,
    NULL
    }
};
#endif
#endif

/**
    This collects all CPU features from CPUID. It provides in *Features the
    common features supported from all CPUs and returns CPU with the least number of
    features.

        
    @param VOID

         
    @retval UINT8 bFlag

**/

UINT8
IsBsp(
    VOID
)
{
    UINT8   Flag = 1;   // 1 = BSP, 0 = AP
    UINT64  Buffer64;

    Buffer64 = ReadMsr (MSR_XAPIC_BASE);
    if ((Buffer64 & 0x0100) == 0)
        Flag = 0;

    return Flag;
}

/**
    This is an initialization routine for Zeppelin BSP.

    @param CpuInfoHob   - CPU information HOB
    @param CpuSetupData - CPU setup data

    @retval VOID

**/
VOID
InitializeZpCpu(
    IN EFI_PEI_SERVICES **PeiServices,
    IN CPUINFO_HOB      *CpuInfoHob,
    IN CPU_SETUP_DATA   *CpuSetupData)
{
    UINT32          Value;
    UINT32          CpuSignature;
    UINT64          CpuFeatureInfo;
    UINT32          FeatureFlagsEdx;
    UINT32          FeatureFlagsEcx;
    UINT32          RegEbx;
    CPUINFO         *CpuInfo = &CpuInfoHob->Cpuinfo[0];
#if defined F17_LOCAL_APIC_MASK_WORKROUND_SUPPORT && F17_LOCAL_APIC_MASK_WORKROUND_SUPPORT == 1
    UINT32          PciAddress;
    UINT32          AmdApicMaskCtrl;
#endif
    CPULib_CpuID(1, &CpuSignature, &RegEbx,
                 &FeatureFlagsEcx, &FeatureFlagsEdx);

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
    
    DEBUG((DEBUG_INFO, "Pei>InitializeCpu: ApicId=%X  CpuSignature=%X  CpuRevision=%X\n",
               CpuInfo->ApicId, CpuInfo->CpuSignature, CpuInfo->CpuRevision));
    
    // Read SVR data from Local APIC
    Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER);
    //Clear SVR, Use Vector 0Fh
    Value &= 0x0F;
    Value |= 1 << 8;    //Enable Apic
    *(UINT32*)(UINTN)(APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER) = Value;

    //--------------------------
    //Program Virtual Wire Mode.
    //--------------------------
    //Program LINT0 vector as ExtInt
    Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT0_REGISTER);
    Value &= 0xFFFE58FF;
    Value |= 0x700;
    *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT0_REGISTER) = Value;

    //Program the LINT1 vector entry as NMI
    Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT1_REGISTER);
    Value &= 0xFFFE58FF;

    Value |= 0x400;

    *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT1_REGISTER) = Value;

    WriteMsr (MSR_SYS_CFG,
              ReadMsr (MSR_SYS_CFG) & (~(UINT64)(1 << MtrrFixDramModEnBit)) );
#if defined F17_LOCAL_APIC_MASK_WORKROUND_SUPPORT && F17_LOCAL_APIC_MASK_WORKROUND_SUPPORT == 1
    // Set D18F5x104[8] = 1, 
    // for set APICx350 and APICx360 mask bit(Bit 16) to 1 while APICxF0[APICSWEn] = 0
    PciAddress = PCI_EXPRESS_LIB_ADDRESS(0, 0x18, 0x5, 0x104);
    AmdApicMaskCtrl = PciExpressRead32(PciAddress);

    if(AmdApicMaskCtrl != 0xFFFFFFFF)
    {
        AmdApicMaskCtrl |= BIT8;
        PciExpressWrite32(PciAddress, AmdApicMaskCtrl);
    }
	
    DEBUG((DEBUG_INFO, "D18F5x104 = %X\n", AmdApicMaskCtrl));
	
    if((AmdApicMaskCtrl == 0xFFFFFFFF) || ((PciExpressRead32(PciAddress) & BIT8) == 0))
    {
        DEBUG((DEBUG_ERROR, "Set D18F5x104[8] failed\n"));
    }
#endif
    return;
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
  IN    UINT8   Cpu,
  IN    VOID    *Context
)
{
    UINT32		    Value;
    UINT32		    CpuSignature;
    UINT64		    CpuFeatureInfo;
    UINT32	        FeatureFlagsEdx;
    UINT32	        FeatureFlagsEcx;
    UINT32	        RegEbx;
    PEI_AP_DATA	    *PeiApData = (PEI_AP_DATA*)Context;
    CPU_SETUP_DATA  *CpuSetupData = PeiApData->CpuSetupData;
    CPUINFO	        *CpuInfo = &PeiApData->Cpuinfo[Cpu];
    CPU_FEATURES    *Features = PeiApData->CpuFeatures;
    UINT64          Msr64Data;
    UINT32          MsrAddr;
    UINT8           Data8;
    
    // Due to the malfunction of InitMtrrCopyContext, we need to restore the SMM addr and mask
    // in this way.
    if ((PeiApData->CpuS3Resume) != 0)
    {
        // BE CAREFULL!! this index is decided by MtrrRegs in CPU.h
        // if you change the order of AMD_MSR_SMM_ADDR_HL and AMD_MSR_SMM_MASK_HL
        // in MtrrRegs[], you need to change the following index.
        MsrAddr = (UINT32)PeiApData->CpuS3Resume->MtrrValue[27].Msr;
        Msr64Data = (UINT64)PeiApData->CpuS3Resume->MtrrValue[27].Value;
        WriteMsr(MsrAddr, Msr64Data);

        MsrAddr = (UINT32)PeiApData->CpuS3Resume->MtrrValue[28].Msr;
        Msr64Data = (UINT64)PeiApData->CpuS3Resume->MtrrValue[28].Value;
        WriteMsr(MsrAddr, Msr64Data);
        // Set SMM Base
        Msr64Data = (UINT64)PeiApData->CpuS3Resume->SmmBase.SmmBaseVal[Cpu];
        WriteMsr(AMD_MSR_SMM_BASE, Msr64Data);

        Msr64Data = ReadMsr(AMD_MSR_HWCR);
        Msr64Data |= 0x1; //Bit0     Set SMM lock
        WriteMsr(AMD_MSR_HWCR, Msr64Data);
    }

    Msr64Data = ReadMsr(0xC0010114);
    Msr64Data &= ~0x0010;       // default is enabled
    if (CpuSetupData->SVM_MODE == 0)
        Msr64Data |= 0x0010;

    Msr64Data |= 0x08;          // Set SVM lock
    WriteMsr(0xC0010114, Msr64Data);

    if (CpuSetupData->NX_MODE == 0)
    {
        Msr64Data = ReadMsr(0xC0011005);
        Msr64Data &= ~0x100000;     // Disable NX function, bit20
        WriteMsr(0xC0011005, Msr64Data);
    }

    // P-state adjust
    Data8 = CpuSetupData->PSTATE_CTRL;
    Msr64Data = ReadMsr(0xC0010063);
    Msr64Data &= 0xFFFFFFF8;
    Msr64Data |= Data8;     // Set new P-state
    WriteMsr(0xC0010062, Msr64Data);
        
    CPULib_CpuID (1, &CpuSignature, &RegEbx, &FeatureFlagsEcx, &FeatureFlagsEdx);

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

    // Semaphore lock here
    WaitForSemaphore (&PeiApData->Semaphore);

    if (IsBsp())
    {
        DEBUG((DEBUG_INFO, "Pei>InitializeCpu: ApicId=%X  CpuSignature=%X  CpuRevision=%X\n",
         CpuInfo->ApicId, CpuInfo->CpuSignature, CpuInfo->CpuRevision));
    }
    //Semaphore unlock here
    PeiApData->Semaphore = 0;

    if (IsBsp())
    {
        // Read SVR data from Local APIC
        Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER);
        //Clear SVR, Use Vector 0Fh
        Value &= 0x0F;
        Value |= 1 << 8;	//Enable Apic
        *(UINT32*)(UINTN)(APIC_BASE + APIC_SPURIOUS_VECTOR_REGISTER) = Value;
    }

    //--------------------------
    //Program Virtual Wire Mode.
    //--------------------------
    if (IsBsp())
    {
        // Program LINT0 vector as ExtInt
        Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT0_REGISTER);
        Value &= 0xFFFE58FF;
        Value |= 0x700;
        *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT0_REGISTER) = Value;

        //Program the LINT1 vector entry as NMI
        Value = *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT1_REGISTER);
        Value &= 0xFFFE58FF;

        Value |= 0x400;

        *(UINT32*)(UINTN)(APIC_BASE + APIC_LVT_LINT1_REGISTER) = Value;

    }

    WriteMsr (MSR_SYS_CFG, ReadMsr (MSR_SYS_CFG) & (~(UINT64)(1 << MtrrFixDramModEnBit)));

	return;
}

/**
    Get memory size below 4GB.

        
    @param PeiServices 

         
    @retval UINT64 SystemMemoryLength

**/

UINT64
GetSystemMemoryLength(
  IN    EFI_PEI_SERVICES    **PeiServices
)
{
    // Please refer to EIP 30689 and EIP 30223 to understand why the above
    // implementation was broken and commented out
    EFI_PEI_SAVE_TOM_PPI    *SaveTomPpi;
    UINT64                  SystemMemoryLength = 0x100000;
    EFI_STATUS			    Status;

    // Locate EFI_PEI_SAVE_TOM_PPI published in memdetect.c
    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmiDTomGuid, 0, NULL, &SaveTomPpi);
    ASSERT_PEI_ERROR (PeiServices, Status);

    if (SaveTomPpi->Value == 0x100000)
        ASSERT_PEI_ERROR (PeiServices,EFI_NOT_FOUND);

    // The following calculation is based on InstallEfiMemory in memdetect.c
    // May need some modifications per project
    SystemMemoryLength = (UINT64)(SaveTomPpi->Value - TSEG_SIZE);
    return SystemMemoryLength;
}

/**
    Create CPU Hob and fill in default data.

        
    @param PeiServices 
    @param NumCpus 

         
    @retval CPUINFO_HOB CpuinfoHob

**/

CPUINFO_HOB
*CreateCpuHobWithDefaults(
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    UINT8               NumCpus
)
{
    CPUINFO_HOB	*CpuinfoHob;
    EFI_STATUS	Status;
    UINT8		i;

    // Create hob for storing Cpu Data
    //NOTE: sizeof(CPUINFO_HOB) already includes size of one CPUINFO structure
    Status = (**PeiServices).CreateHob (PeiServices, EFI_HOB_TYPE_GUID_EXTENSION,
                              sizeof (CPUINFO_HOB) + (NumCpus - 1) * sizeof (CPUINFO),
                              &CpuinfoHob);
    ASSERT_PEI_ERROR (PeiServices, Status);

    CpuinfoHob->EfiHobGuidType.Name = gAmiCpuinfoHobGuid;
    CpuinfoHob->CpuCount = NumCpus;
    CpuinfoHob->BspNo = 0; //BSP is always 0
    CpuinfoHob->CacheLineSize = 64;
    CpuinfoHob->NodeCount = AmdNodeCount();
    CpuinfoHob->TsegAddress = (EFI_PHYSICAL_ADDRESS)GetSystemMemoryLength (PeiServices);
    CpuinfoHob->TsegSize = TSEG_SIZE;

    DEBUG((DEBUG_INFO, "CreateCpuHobWithDefaults: NodeCount = 0x%X\n",
            CpuinfoHob->NodeCount));

    for (i = 0; i < NumCpus; ++i)
    {
        CpuinfoHob->Cpuinfo[i].Valid	= FALSE;
        CpuinfoHob->Cpuinfo[i].Disabled	= FALSE;
    }
    return CpuinfoHob;
}


/**
    Returns pointer to S3 Resume data in memory.

        
    @param PeiServices 
    @param ReadOnlyVariable 

         
    @retval CPU_S3_RESUME CpuS3Resume

**/

CPU_S3_RESUME
*GetS3ResumeVariable(
  IN    EFI_PEI_SERVICES                **PeiServices,
  IN    EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable
)
{
    CPU_S3_RESUME	*CpuS3Resume = 0;
    EFI_STATUS		Status;
    UINTN           VariableSize = sizeof(CPU_S3_RESUME*);

    Status = ReadOnlyVariable->GetVariable (ReadOnlyVariable, CpuS3ResumeVariable,
                                &gCpuS3ResumeGuid, NULL, &VariableSize, &CpuS3Resume);
    if (EFI_ERROR (Status))
    {
        DEBUG((DEBUG_ERROR, "Smm S3 Resume -- No CPU S3 Resume Variable\n"));
        PEI_ERROR_CODE(PeiServices, PEI_S3_RESUME_ERROR, EFI_ERROR_MAJOR);
    }

    return CpuS3Resume;
}

/**
    Get the TSEG base

    @param PeiApData 

    @retval UINT32 TSEG Base

**/

UINT32
GetTsegBase(
  IN    PEI_AP_DATA *PeiApData
)
{
    return (UINT32)PeiApData->TopOfMemory;
}

/**
    Change SMM base

        
    @param Cpu 
    @param Context 

         
    @retval VOID

**/

VOID
SmmCpuBaseChange(
  IN    UINT8   Cpu,
  IN    VOID    *Context
)
{
    SmmBaseChangeOnCpu(Context);    //Context = Smmbase
}


/**
    Creates HOB resource descriptor for memory above 4Gb.

        
    @param PeiServices pointer to PEI services structure

          
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
ReportTom2(
  IN    EFI_PEI_SERVICES    **PeiServices
)
{
    EFI_PEI_SAVE_TOM2_PPI   *SaveTom2Ppi;
    EFI_STATUS              Status;

    // Locate EFI_PEI_SAVE_TOM_PPI published in memdetect.c
    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmiDTom2Guid, 0, NULL,
                              &SaveTom2Ppi);
    if (EFI_ERROR(Status))  // If not found then no TOM2
        return Status;

    Status = CreateHobResourceDescriptor (PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY,
              MEM_DET_COMMON_MEM_ATTR_ABOVE4G, SaveTom2Ppi->Base, SaveTom2Ppi->Size);

    if (Status != EFI_SUCCESS) 
        DEBUG((DEBUG_ERROR, "Above 4GB system memory reporting HOB creation failed.\n"));

    return Status;
}

/**
    Reads PSP enabled/disabled status

    @param None 

    @retval BOOLEAN TRUE - PSP enabled
                    FALSE - PSP disabled

**/

BOOLEAN
AmiIsPspEn(
VOID
)
{
    //PSP should never be disabled.
    return  TRUE;
}

/**
    Disable Rom Caching on APs

        
    @param Cpu 
    @param Context 

         
    @retval VOID

**/

VOID
DisableRomCachingAp(
    IN UINT8    Cpu, 
    IN VOID     *Context
)
{
    WriteMsr(MTRR_PHYS_MASK_7, 0);
    WriteMsr(MTRR_PHYS_BASE_7, 0);
}


/**
    This function is called after the permanent memory is installed
    in the system.  This function does the initializes CPU in the memory
    present environment.

    @param FileHandle Handle of the file being invoked
    @param PeiServices Pointer to the PEI services table

    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI
CpuInitAfterMemInstalled(
  IN    EFI_PEI_SERVICES             **PeiServices,
  IN    EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN    VOID                         *InvokePpi 
)
{
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    EFI_PEI_STALL_PPI               *PeiStall;
    EFI_BOOT_MODE                   BootMode;
    EFI_STATUS                      Status;
    CPUINFO_HOB                     *CpuinfoHob;
    CPU_SETUP_DATA                  CpuSetupData;
    PEI_AP_DATA                     PeiApData;  // This is used pass data to APs. Global Variables won't in ROM.
    VOID                            *MpData;
    UINT64                          SystemMemoryLength;
    UINT8                           NumCpus;
    BOOLEAN                         IsPspEnabled = TRUE;
    BOOLEAN                         Family15;

    Family15 = IsFamily15h();

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR (PeiServices, Status);

    Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid,
                              0, NULL, &ReadOnlyVariable);
    ASSERT_PEI_ERROR (PeiServices, Status);

    if (BootMode == BOOT_ON_S3_RESUME )
    {
        IsPspEnabled = AmiIsPspEn();    // Check PSP fuse
        PeiApData.CpuS3Resume = GetS3ResumeVariable (PeiServices, ReadOnlyVariable);
    }
    else
    {
        PeiApData.CpuS3Resume = 0;
    }

    //----------------------------------------------//
    // Execute this function ASAP for performance. //
    //            This enables BSP cache.           //
    //----------------------------------------------//

    SystemMemoryLength = GetSystemMemoryLength(PeiServices);
    DEBUG((DEBUG_INFO, "SystemMemoryLength= %dMB\n",
               ((UINT32)SystemMemoryLength / (1024 * 1024)) ));
    PEI_PROGRESS_CODE(PeiServices, PEI_CPU_CACHE_INIT);
    if (PeiApData.CpuS3Resume) 
    {
        if (Family15)
            ProgramS3ResumeMtrrs(PeiApData.CpuS3Resume->MtrrValue, IsPspEnabled);
    }
	else if (BootMode != BOOT_ON_FLASH_UPDATE)
	{
	    InitMtrrFamily15(PeiServices);
	}
    if ((BootMode == BOOT_ON_S3_RESUME) && (Family15))
    {
        UINT32  MsrBase = 0;
        UINT64  Value64 = 0;

        MsrBase = MTRR_PHYS_BASE_7;
        Value64 = (0x0100000000 - FLASH_SIZE + 0x5);
        WriteMsr (MsrBase, Value64);
        Value64 = 0xFFFFFFFFFF & (~(FLASH_SIZE - 1) + (1 << 11));
        WriteMsr (MsrBase + 1, Value64);
    }

    Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, &PeiStall);
    ASSERT_PEI_ERROR (PeiServices, Status);

    GetCpuSetupData(PeiServices, &CpuSetupData, TRUE);

    if (Family15)
    {
        // It's family 15h
        PeiApData.BootMode = BootMode;
        PeiApData.CpuSetupData = &CpuSetupData;
        PeiApData.IsSetupDataValid = EFI_SUCCESS;
        PeiApData.TopOfMemory = SystemMemoryLength;
        PeiApData.NumCpusDisabled = 0;

        //Intialize MPs. This must done before number of CPUs is known.
        DEBUG((DEBUG_INFO, "CPUPEI: Before StartAllAps AmdCpuCount() = %x.\n", AmdCpuCount()));

        PEI_PROGRESS_CODE(PeiServices, PEI_CPU_AP_INIT);
        StartAllAps(PeiServices, PeiStall, &MpData);

        //After initialized, APs are in holding loop until halted.
        NumCpus = GetNumCpus(MpData);

        DEBUG((DEBUG_INFO, "CPUPEI: GetNumCpus returned %d\n", NumCpus));

        //After initialized, APs are in holding loop until halted.
        CpuinfoHob = CreateCpuHobWithDefaults(PeiServices, NumCpus);
        //    CpuinfoHob->CpuFeatures = Features;
        PeiApData.Cpuinfo = &CpuinfoHob->Cpuinfo[0];

        //All CPUs initialized including BSP.
        DEBUG((DEBUG_INFO, "CPUPEI: Before ExecuteFunctionOnRunningCpus\n"));
        PeiApData.PeiServices = PeiServices;
        PeiApData.Semaphore = 0;
        // All CPUs must execute InitializeCpu
        PEI_PROGRESS_CODE(PeiServices, PEI_CPU_INIT);
        ExecuteFunctionOnRunningCpus(
                MpData, TRUE, TRUE, InitializeCpu, &PeiApData
        );

        // Explicitly synchronize all APs' MTRRs with BSP's MTRRs
        MpSynchronizeMtrrs(PeiServices, MpData);

        // Disable Rom Caching for APs
        if (BootMode == BOOT_ON_FLASH_UPDATE )
        {
            ExecuteFunctionOnRunningCpus(MpData, FALSE, TRUE, DisableRomCachingAp, NULL );
        }

        HaltAllAps(MpData, TRUE);
    }
    else
    {
        // It's family 17h

        NumCpus = (UINT8)AmdCpuCount();
        // AP are not enabled at PEI phase in Summit, but CPU_INFO is a must
        CpuinfoHob = CreateCpuHobWithDefaults(PeiServices, NumCpus);

        InitializeZpCpu(PeiServices, CpuinfoHob, &CpuSetupData);
    }

    if (!ReadMsr(AMD_MSR_MCODE_SIGNATURE))
        PEI_PROGRESS_CODE (PeiServices, PEI_CPU_NO_MICROCODE);

    Status = (**PeiServices).NotifyPpi (PeiServices, &NotifyList);
    if(EFI_ERROR(Status))
        DEBUG((DEBUG_ERROR, "CPUPEI: Notify EndOfPeiSignalPpi %r\n", Status));

    Status = (*PeiServices)->InstallPpi (PeiServices, &PpiAfterCpuPeiPpi);

    return  Status;
}


/**
    This function is called after the permanent memory is installed
    in the system.  This function does the initializes CPU in the memory
    present environment.

    @param FileHandle Handle of the file being invoked
    @param PeiServices Pointer to the PEI services table

    @retval EFI_SUCCESS always success

**/
EFI_STATUS 
CpuPeiEntry(
  IN       EFI_PEI_FILE_HANDLE      FileHandle,  
  IN CONST EFI_PEI_SERVICES         **PeiServices
)
{

	EFI_STATUS			Status;
    Status = (*PeiServices)->NotifyPpi( PeiServices, CpuMemInstalledNotifyList );
    ASSERT_PEI_ERROR ( PeiServices, Status );

#if PeiRamBootSupport == 1
#if defined(AMD_SKIP_COPY_FV_BB) && (AMD_SKIP_COPY_FV_BB ==1)
    if (IsFamily15h())
    {
        Status = (*PeiServices)->InstallPpi (PeiServices, &NotSkipCopyFvBbPpiList[0]);
        DEBUG ((DEBUG_INFO, "    Install NotSkipCopyFvBbPpiList for BR = %r\n", Status));
        ASSERT_PEI_ERROR ( PeiServices, Status );
    }
#endif
#endif

	return Status;
}

/**
    This function is called at end of PEI phase. It disables the 
    ROM cache to avoid the problem with flash.
				

    @param Pointer to PeiServices
    @param Pointer to NotifyDesc
    @param InvokePpi 

    @retval EFI_SUCCESS always success

**/
EFI_STATUS
EFIAPI
EndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{

    EFI_PEI_READ_ONLY_VARIABLE2_PPI		*ReadOnlyVariable;
    EFI_BOOT_MODE                   	BootMode;
    CPU_S3_RESUME						*CpuS3Resume;
    EFI_STATUS                      	Status;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if(EFI_ERROR(Status))
        DEBUG((DEBUG_ERROR, "CPUPEI: EndOfPeiCallback GetBootMode %r\n", Status));

    Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid,
                              0, NULL, &ReadOnlyVariable);
    if(EFI_ERROR(Status))
        DEBUG((DEBUG_ERROR, "CPUPEI: EndOfPeiCallback ReadOnlyVariable %r\n", Status));
    
    if (BootMode == BOOT_ON_S3_RESUME )
    {
    	// We do it again because some modules would change the MTRR setting after
    	// We restore MTRR in CpuInitAfterMemInstalled.
    	// And this is the last point to restore MTRR during S3.
        CpuS3Resume = GetS3ResumeVariable (PeiServices, ReadOnlyVariable);
        ProgramS3ResumeMtrrs(CpuS3Resume->MtrrValue, AmiIsPspEn());
    }

#if (ENABLE_ROM_CACHE_IN_DXE == 0)
    // Disable caching of ROM at the end of PEI to avoid problems
    // with flash
    WriteMsr(MTRR_PHYS_MASK_7, 0);
    WriteMsr(MTRR_PHYS_BASE_7, 0);
#endif

    if (!IsFamily15h())
    {
        // Disable caching of HIGH_MEMORY_REGION_BB_BASE at the end of PEI
        WriteMsr(MTRR_PHYS_MASK_6, 0);
        WriteMsr(MTRR_PHYS_BASE_6, 0);
        if (BootMode == BOOT_ON_S3_RESUME )
        {
            IoWrite8(SW_SMI_IO_ADDRESS, CPU_SWSMI);
        }
    }
    return  EFI_SUCCESS;
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

