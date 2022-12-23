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

/** @file MemDetect.c
    This file forms like a wrapper for actual memory detection code.
    The project will have two portion of Memory detection related
    code - one in North bridge that provides NB specific interface 
    (PPI/functions) for the memory detection code and the another
    component which is the actual memory detection code. This file
    belong to the second component.  
    This component might be provided in binary format (FFS) by
    some chipset vendor.  In that case, modify the NB.MAK, 
    , MemDetect.SDL and MemDetect.CIF files to remove the files
    MemDetect.c & MemDetect.h and include the provided binary
    in FV_BB. Also make sure the NB side component publishes 
    required PPI for the binary provided by the chipset vendor.
    If this component is created from source (assembly or C) files
    then add those files into MemDetect.CIF. Modify this file 
    to get the data published by NB side component and convert
    into the way the actual memory detection code needs (like a
    wrapper).
    It is responsibility of this component to setup proper
    HOBs related to memory

**/

#include <PiPei.h>
#include "Token.h"
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include "Nb.h"
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#ifdef ACPI_SUPPORT
#include "AmiAcpiS3.h"
#include <Guid/AcpiS3Context.h>
#endif
#include "Ppi/AmdMemPpi.h"
// Produced PPIs
#include <CpuSetupData.h>
#include "Ppi/ReadOnlyVariable2.h"
#include "Memdetect.h"
#include "Guid/AmdMemoryInfoHob.h"
#include <Ppi/Capsule.h>
#include <Cpu.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdCapsuleLib.h>
#include <CpuCspLib.h>
#include <Guid/SmramMemoryReserve.h>

// This is copied from AmdMemoryHobInfoPeim.c
#define MAX_NUMBER_OF_EXTENDED_MEMORY_DESCRIPTOR    19
#define MAX_SIZEOF_AMD_MEMORY_INFO_HOB_BUFFER       (sizeof (AMD_MEMORY_INFO_HOB) +  \
          (MAX_NUMBER_OF_EXTENDED_MEMORY_DESCRIPTOR * sizeof (AMD_MEMORY_RANGE_DESCRIPTOR)))


#if AMI_NB_DEBUG_MESSAGES == 0
#undef DEBUG
#define DEBUG(x)
#endif

#ifndef TSEG_SIZE
#define	TSEG_SIZE 			0
#endif

typedef struct {
    EFI_HOB_GUID_TYPE               EfiHobGuidType;
    EFI_SMRAM_HOB_DESCRIPTOR_BLOCK  SmramHobDescriptor;
} AMI_SMRAM_HOB;

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

CHAR16      NbAcpiS3Variable[] = NB_ACPI_S3_VARIABLE;

// Function prototypes
EFI_STATUS  InstallEfiMemory (EFI_PEI_SERVICES **PeiServices, 
                                UINT32 Tom, UINT64 UmaBase, UINT64 UmaSize );
EFI_STATUS  InstallS3Memory (CONST EFI_PEI_SERVICES **PeiServices,
                             EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadOnlyVariable);


BOOLEAN SbCheckAfterG3(VOID);

/**
    Read UINT32 value from PCI register

        IN UINT32 - Address :(UINT32) ( (((UINT32)bus) << 24) + \
        (((UINT32)dev) << 19) + \
        (((UINT32)func) << 16) + \
        ((UINT32)reg) )   
    @param ExtendReg : external access

    @retval UINT32 value from PCI register.

**/

UINT32 NbPeiReadPCI32(
    IN UINT32 Address,
    IN UINT8  ExtendReg
)
{
    UINT32 Value32;
    UINT64 Value64;
    UINT32 AddrCf8 = ((UINT32)1 << 31) + ((Address >> 8) & 0x0FFFF00) + (Address & 0xFC);

    Value64 = AsmReadMsr64(0xC001001F);
    Value64 |= 0x400000000000;
    AsmWriteMsr64(0xC001001F, Value64);

    if(ExtendReg)
        AddrCf8 |= (1 << 24);

    IoWrite32(0xCf8, AddrCf8);
    Value32 = IoRead32(0xCfC);

    Value64 = AsmReadMsr64(0xC001001F);
    Value64 &= 0xFFFFBFFFFFFFFFFF;
    AsmWriteMsr64(0xC001001F, Value64);

    return Value32;
}

// [Fam15 only]
/**
    Create MTRR Hob. Will not save Var MTRR 20E and 20F.

        
    @param PeiServices 

         
    @retval VOID

**/

VOID
CreateMtrrHob(IN CONST EFI_PEI_SERVICES **PeiServices)
{
	MTRR_HOB	*MtrrHob;
    UINT32      VarMtrrMsr;
    UINT8       Index;
	EFI_STATUS	Status;

	// Create hob for storing MTRR Data
	Status = (**PeiServices).CreateHob(PeiServices,
		EFI_HOB_TYPE_GUID_EXTENSION,
		sizeof(MTRR_HOB),
  		&MtrrHob);
	ASSERT_EFI_ERROR(Status);

	MtrrHob->EfiHobGuidType.Name = gAmiMtrrHobGuid;

    for (VarMtrrMsr = MTRR_PHYS_BASE_0, Index = 0; VarMtrrMsr < MTRR_PHYS_BASE_7; VarMtrrMsr += 2, Index++)
    {
   	    MtrrHob->VarMtrrBase[Index] = AsmReadMsr64(VarMtrrMsr);
   	    MtrrHob->VarMtrrMask[Index] = AsmReadMsr64(VarMtrrMsr + 1);

        //Clear the 0x200~0x20D MTRR registers, leave ROM cache MTRR 0x20E-0x20F
   	    AsmWriteMsr64(VarMtrrMsr + 1, 0);      // Always clear mask first then Base
   	    AsmWriteMsr64(VarMtrrMsr, 0);
    }
}

/**
    This function saves top of memory for =< 4GB region

        
    @param PeiServices Pointer to the PEI services table
    @param TOM 32-bit address of top of memory 

         
    @retval EFI_STATUS Return Status 

**/

EFI_STATUS
SaveTom(
  IN  EFI_PEI_SERVICES  **PeiServices,
  IN  UINT32            Tom )
{
    EFI_PEI_PPI_DESCRIPTOR *PpiSaveTom;
    EFI_PEI_SAVE_TOM_PPI   *SaveTomPpi;
    EFI_STATUS              Status;

    // allocate memory for EFI_PEI_PPI_DESCRIPTOR PpiSaveDTOM
    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof(EFI_PEI_PPI_DESCRIPTOR), &PpiSaveTom);
    ASSERT_EFI_ERROR(Status);
    
    // allocate memory for EFI_PEI_SAVE_DTOM_PPI SaveTomPpi
    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof(EFI_PEI_SAVE_TOM_PPI), &SaveTomPpi);
    ASSERT_EFI_ERROR(Status);
    
    // Save the value of dTOM in PpiSaveTom to be used later in CpuPeiEntry
    SaveTomPpi->Value = Tom;
    
    // Initialize the EFI_PEI_PPI_DESCRIPTOR PpiSaveTom
    PpiSaveTom->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    PpiSaveTom->Guid = &gAmiDTomGuid;
    PpiSaveTom->Ppi = SaveTomPpi;
    
    // Install the EFI_PEI_SAVE_DTOM_PPI to retrieve dTOM value later in CpuPeiEntry
    Status = (*PeiServices)->InstallPpi(PeiServices, PpiSaveTom);
    ASSERT_EFI_ERROR(Status);
    return Status;
}

/**
    This function saves top of memory for > 4GB region

        
    @param PeiServices Pointer to the PEI services table
    @param Base The base address of top of memory > 4GB
    @param Size The size of top of memory > 4GB

         
    @retval EFI_STATUS Return Status 

**/
EFI_STATUS
SaveTom2 (
  IN  EFI_PEI_SERVICES  **PeiServices,
  IN  UINT64            Base,
  IN  UINT64            Size )
{
    EFI_PEI_PPI_DESCRIPTOR *PpiSaveTom2;
    EFI_PEI_SAVE_TOM2_PPI  *SaveTom2Ppi;
    EFI_STATUS Status;

    // allocate memory for EFI_PEI_PPI_DESCRIPTOR PpiSaveTom2
    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof(EFI_PEI_PPI_DESCRIPTOR), &PpiSaveTom2);
    ASSERT_EFI_ERROR(Status);

    // allocate memory for EFI_PEI_SAVE_DTOM2_PPI SaveTom2Ppi
    Status = (*PeiServices)->AllocatePool(PeiServices, sizeof(EFI_PEI_SAVE_TOM2_PPI), &SaveTom2Ppi);
    ASSERT_EFI_ERROR(Status);

    // Save the value of dTOM2 in PpiSaveTom2 to be used later in CpuPeiEntry
    SaveTom2Ppi->Base = Base;
    SaveTom2Ppi->Size = Size;

    DEBUG ((DEBUG_INFO, "TOM2 Base = %16lx\n", SaveTom2Ppi->Base));
    DEBUG ((DEBUG_INFO, "TOM2 Size = %16lx\n", SaveTom2Ppi->Size));

    // Initialize the EFI_PEI_PPI_DESCRIPTOR PpiSaveTom2
    PpiSaveTom2->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    PpiSaveTom2->Guid = &gAmiDTom2Guid;
    PpiSaveTom2->Ppi = SaveTom2Ppi;

    // Install the EFI_PEI_SAVE_DTOM2_PPI to retrieve Tom2 value later in CpuPeiEntry
    Status = (*PeiServices)->InstallPpi(PeiServices, PpiSaveTom2);
    ASSERT_EFI_ERROR(Status);
    
    return Status;
}

/**
    This function is the entry point for this PEI. This function
    auto detects the memory installed and configures it

    @param FileHandle Handle of the file being invoked
    @param PeiServices Pointer to the PEI services table

    @retval EFI_STATUS Return Status based on errors that occurred while waiting for
        time to expire.

**/

EFI_STATUS
EFIAPI
MemDetectSupportInit (
    IN EFI_PEI_FILE_HANDLE      FileHandle,
    IN CONST EFI_PEI_SERVICES   **PeiServices
)
{
    UINT32                          Tom = 0;
    UINT64                          Tom2 = 0;
    EFI_STATUS                      Status;
    UINT64                          UmaSize = 0;
    UINT64                          UmaBase = 0;
    EFI_BOOT_MODE                   BootMode;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    AMD_MEMORY_INFO_HOB             *MemInfoHob;
    AMD_MEMORY_RANGE_DESCRIPTOR     *MemRangDesc;
    EFI_PEI_HOB_POINTERS            GuidHob;
    AMI_MEM_INFO                    AmiMemInfo;
    UINTN                           VarSize = sizeof(UINT64);
    UINTN                           VarAttrib = 0;
    UINT32                          MemRangeIndex = 0;

    Status = (*PeiServices)->LocatePpi(
                 PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL,
                 &ReadOnlyVariable );
    ASSERT_EFI_ERROR(Status);

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_EFI_ERROR(Status);

    if (BootMode == BOOT_ON_S3_RESUME)
    {
        //Read Tom Value from NVRAM and report it.
        VarSize = sizeof(AMI_MEM_INFO);
        Status = ReadOnlyVariable->GetVariable (ReadOnlyVariable,
                        L"AmiMemInfo",
                        &gAmiMemInfoGuid,
                        &VarAttrib,
                        &VarSize,
                        &AmiMemInfo);   // This info is a must for S3resume.
        if (EFI_ERROR(Status))
        {
            DEBUG ((DEBUG_ERROR, "S3 memory failure....Cannot restore system"));
            //PEI_ERROR_CODE(PeiServices, PEI_MEMORY_S3_RESUME_FAILED, EFI_ERROR_MAJOR);
            IoWrite8(0x80, 0xE8);
            ASSERT_EFI_ERROR(Status);
            CpuDeadLoop();
        }
        if ((AmiMemInfo.UmaBase < 0x100000000) && (AmiMemInfo.UmaSize != 0))
        {
            if (AmiMemInfo.LoMemSize > (UINT32)(AmiMemInfo.UmaBase))
            {
                DEBUG((DEBUG_INFO, "Adjust TOM to UMA base. TOM from %X set to %X\n", AmiMemInfo.LoMemSize, (UINT32)(AmiMemInfo.UmaBase)));
                AmiMemInfo.LoMemSize = (UINT32)(AmiMemInfo.UmaBase);
            }
        }
        if (IsFamily15h())
            if (AmiMemInfo.HiMemBase == 0)
                AmiMemInfo.LoMemSize -= 0x1000000; // PSP, C6 used fixed 16MB on BR CPU

        AmiMemInfo.LoMemSize &= TSEG_ALIGN;
        Status = SaveTom(PeiServices, AmiMemInfo.LoMemSize);
        Status = InstallS3Memory(PeiServices, ReadOnlyVariable);
        return Status;
    }

    Status = (*PeiServices)->GetHobList (PeiServices, &GuidHob.Raw);
    ASSERT_EFI_ERROR(Status);

    MemInfoHob = NULL;
    while (!END_OF_HOB_LIST (GuidHob)) {
      if (GuidHob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
          CompareGuid ( &GuidHob.Guid->Name, &gAmdMemoryInfoHobGuid)) {
          MemInfoHob = (AMD_MEMORY_INFO_HOB *)(GuidHob.Raw +
                            sizeof (EFI_HOB_GENERIC_HEADER) +
                            sizeof (EFI_GUID));
        Status = EFI_SUCCESS;
        break;
      }
      GuidHob.Raw = GET_NEXT_HOB (GuidHob);
    }

    if (MemInfoHob != NULL)
    {
        DEBUG ((DEBUG_INFO, "MemInfoHob->NumberOfDescriptor = %x\n", MemInfoHob->NumberOfDescriptor));
        MemRangDesc = &MemInfoHob->Ranges[0];

        for (MemRangeIndex = 0; MemRangeIndex < MemInfoHob->NumberOfDescriptor; MemRangeIndex++)
        {
            if ((MemRangDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) && (MemRangDesc[MemRangeIndex].Base < 0x100000000))
            {
                if (Tom < (UINT32) (MemRangDesc[MemRangeIndex].Base + MemRangDesc[MemRangeIndex].Size))
                {
                    Tom = (UINT32)(MemRangDesc[MemRangeIndex].Base + MemRangDesc[MemRangeIndex].Size);
                    DEBUG ((DEBUG_INFO, "Temporary TOM = %x\n", Tom));
                }
            }

            if ((MemRangDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) && (MemRangDesc[MemRangeIndex].Base >= 0x100000000))
            {
                // Do not report TOM2 when capsule.
                // ROM image is under 4GB.
                // This TOM2 HOB resource descriptor will lead Capsule->Coalesce to search ROM image on above 4GB.
                if (AmdCapsuleGetStatus() == FALSE)
                {
                    if (Tom2 < (MemRangDesc[MemRangeIndex].Base + MemRangDesc[MemRangeIndex].Size))
                    {
                        Tom2 = MemRangDesc[MemRangeIndex].Base + MemRangDesc[MemRangeIndex].Size;
                        Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY, MEM_DET_COMMON_MEM_ATTR_ABOVE4G,
                                                             MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size);
                        DEBUG ((DEBUG_VERBOSE, "MemDescriptor[%2d] -- Base: %16lx -- Length: %16lx -- Attribute: %x HobStatus: %r\n", 
                                                            MemRangeIndex, MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size, MemRangDesc[MemRangeIndex].Attribute, Status));
                        DEBUG ((DEBUG_VERBOSE, "Temporary TOM2 = %lx\n", Tom2));
                    }
                }
            }

            if ((MemRangDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_RESERVED) && (MemRangDesc[MemRangeIndex].Base >= 0x100000000))
            {
                Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_MEMORY_RESERVED, MEM_DET_COMMON_MEM_ATTR,
                                                     MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size);
                DEBUG ((DEBUG_VERBOSE, "MemDescriptor[%2d] -- Base: %16lx -- Length: %16lx -- Attribute: %x HobStatus: %r\n", 
                                                     MemRangeIndex, MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size, MemRangDesc[MemRangeIndex].Attribute, Status));
            }

            if (MemRangDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_UMA)
            {
                UmaBase = MemRangDesc[MemRangeIndex].Base;
                UmaSize = MemRangDesc[MemRangeIndex].Size;
                DEBUG ((DEBUG_VERBOSE, "Temporary UMA Base = %lx\n", UmaBase));
                DEBUG ((DEBUG_VERBOSE, "Temporary UMA Size = %lx\n", UmaSize));
            }
        }
    }
    if ((UmaBase < 0x100000000) && (UmaSize != 0))
    {
        if (Tom > (UINT32)(UmaBase))
        {
            DEBUG((DEBUG_INFO, "Adjust TOM to UMA base. TOM from %X set to %X\n", Tom, (UINT32)(UmaBase)));
            Tom = (UINT32)(UmaBase);
        }
    }
    if (IsFamily15h())
        if (Tom2 == 0)
            Tom -= 0x1000000; // PSP, C6 used fixed 16MB on BR CPU

    Tom &= TSEG_ALIGN; //(TSEG_SIZE) Align
    ASSERT (Tom != 0 || TSEG_ALIGN != 0);
    
    DEBUG ((DEBUG_INFO, "Final TOM = %x\n", Tom));
    DEBUG ((DEBUG_INFO, "Available MEM above 4G = %lx\n", Tom2));
    DEBUG ((DEBUG_INFO, "Final UMA Base = %lx\n", UmaBase));
    DEBUG ((DEBUG_INFO, "Final UMA Size = %lx\n", UmaSize));
    Status = SaveTom (PeiServices, Tom);

    /*if (IsFamily15h())
        if (Tom2 == 0)
            Tom += 0x1000000; // PSP, C6 used fixed 16MB on BR CPU but it doesn't report to reserved memory*/

    if (!AmdCapsuleGetStatus())
        if (IsFamily15h())
            CreateMtrrHob(PeiServices);

    Status = InstallEfiMemory ((EFI_PEI_SERVICES**)PeiServices, Tom, UmaBase, UmaSize);

    return Status;
}


/**
    This function is used to report the installed memory size
    to the Core Services. This function also creates appropriate
    HOBs

    @param PeiServices Pointer to the PEI services table
    @param TOM 0 - TOM1 (exclude UMA)
    @param UmaBase The base address of UMA
    @param UmaSize The size of UMA

    @retval EFI_STATUS Return Status

**/

EFI_STATUS
InstallEfiMemory(
    IN  EFI_PEI_SERVICES        **PeiServices,
    IN  UINT32                  Tom,
    IN  UINT64                  UmaBase,
    IN  UINT64                  UmaSize
)
{
    UINT32                      MemBegin = MM_LEGACY_RESERVE_MEM;
    EFI_STATUS                  Status;
    PEI_CAPSULE_PPI             *Capsule;
    BOOLEAN                     CapsulePresent = FALSE;
    VOID                        *Buffer;
    UINTN                       CapsuleSize = 0;
    UINT8                       Value8 = 0;
    UINT64                      Value64;
    UINT64                      Tom2 = 0;
    UINT8                       *MemInfoHobBuffer;
    AMD_MEMORY_INFO_HOB         *MemInfoHob;
    AMD_MEMORY_RANGE_DESCRIPTOR *MemRangDesc;
    VOID                        *HobStart;
    VOID                        *ResultHobStart;
    EFI_PEI_HOB_POINTERS        GuidHob;
    UINT32                      MemRangeIndex;
    AMI_SMRAM_HOB                   *AmiSmramHob;
    // Check if Bit6 is set for capsule
    IoWrite8(0x72, PcdGet8(PcdCmosAgesaSpecified));
    Value8 = IoRead8(0x73);
#if defined(CAPSULE_RESET_MODE) && CAPSULE_RESET_MODE == 1
    Value8 |= BIT6;
#endif

    Status = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiCapsulePpiGuid, 0, NULL, &Capsule);
    DEBUG ((DEBUG_INFO, "Locate gEfiPeiCapsulePpiGuid = %x\n", Status));
    if (!EFI_ERROR(Status))
    {
        Status = EFI_NOT_FOUND;// We may not go into the Capsule->Coalesce.
        					   // A successful status results in CapsluePresent and an error action occurs.
        Buffer = (VOID *)(UINTN)MemBegin;
        // In PSP system CPU stack will be allocated near TOM on S3 resume path, and there is a probability
        // to destroy CPU stack when coalescing since kernel doesn't know that CPU stack is allocated in high
        // memory(in general, CPU stack is allocated on 30000h).
        CapsuleSize = (UINTN)(Tom / 2);

        DEBUG ((DEBUG_INFO, "Buffer = %x\n", Buffer));
        DEBUG ((DEBUG_INFO, "CapsuleSize = %x\n", CapsuleSize));

        // we do capsule only when the following conditions are satisfied
        // 1. system is boot from S3 or warm reset
        // 2. capsule flag is set
        if ((!SbCheckAfterG3()) && AmdCapsuleGetStatus())
        {
            // Open SMRAM for searching ROM image
            Value64 = AsmReadMsr64(0xC0010113);
            Value64 &= 0xFFFFFFFC;
            AsmWriteMsr64(0xC0010113, Value64);
            IoWrite8(0x80, 0xC0);
            Status = Capsule->Coalesce(PeiServices, &Buffer, &CapsuleSize);
            IoWrite8(0x80, 0xC1);
            DEBUG ((DEBUG_INFO, "After Coalesce Status = %x\n", Status));
            DEBUG ((DEBUG_INFO, "After Coalesce Buffer = %x\n", Buffer));
            DEBUG ((DEBUG_INFO, "After Coalesce Size = %x\n", CapsuleSize));
        }

        //clear the capsule flag anyway no matter the Coalesce is successful or not
        IoWrite8(0x72, PcdGet8(PcdCmosAgesaSpecified));
        Value8 &= ~BIT6;
        IoWrite8(0x73, Value8);

        if (!EFI_ERROR(Status))
        {
            CapsulePresent = TRUE;
        }
    }

    if (AmdCapsuleGetStatus() == FALSE)
    {
        goto    DoNotReportTom2;
    }

    // Report Tom2 in this way when capsule mode
    Status = (*PeiServices)->GetHobList (PeiServices, &HobStart);
    ASSERT_EFI_ERROR(Status);

    Status = (*PeiServices)->AllocatePool(PeiServices, 
                        MAX_SIZEOF_AMD_MEMORY_INFO_HOB_BUFFER, &MemInfoHobBuffer);
    ASSERT_EFI_ERROR(Status);

    ResultHobStart = GetNextGuidHob(&gAmdMemoryInfoHobGuid, HobStart);
    // If we don't find this HOB, which is essential, 
    // we report PEI_MEMORY_NOT_DETECTED
    if(ResultHobStart == NULL)
    {
        PEI_ERROR_CODE(PeiServices, PEI_MEMORY_NOT_DETECTED, EFI_ERROR_MAJOR);
        ASSERT_EFI_ERROR(Status);
    }
    GuidHob.Guid = (EFI_HOB_GUID_TYPE *)ResultHobStart;
    MemInfoHobBuffer = (UINT8 *)(&GuidHob.Guid->Name) +  sizeof (EFI_GUID);
   
    //Get Tom from AMD HOB
    MemInfoHob = (AMD_MEMORY_INFO_HOB *) &MemInfoHobBuffer[0];
    DEBUG ((DEBUG_INFO, "CreateHobResourceDescriptor from AMD_MEMORY_INFO_HOB\n"));
    if (MemInfoHob != NULL)
    {
        DEBUG ((DEBUG_INFO, "Number of Descriptors: %d\n", MemInfoHob->NumberOfDescriptor ));
        
        MemRangDesc = &MemInfoHob->Ranges[0];
        for (MemRangeIndex = 0; MemRangeIndex < MemInfoHob->NumberOfDescriptor; MemRangeIndex++)
        {
            if ((MemRangDesc[MemRangeIndex].Base >= 0x100000000 && (MemRangDesc[MemRangeIndex].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE)))
            {
                Tom2 += MemRangDesc[MemRangeIndex].Size;
                Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY, MEM_DET_COMMON_MEM_ATTR_ABOVE4G,
                                                    MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size);
                DEBUG ((DEBUG_VERBOSE, "MemDescriptor[%2d] -- Base: %16lx -- Length: %16lx -- Attribute: %x HobStatus: %r\n", 
                                                    MemRangeIndex, MemRangDesc[MemRangeIndex].Base, MemRangDesc[MemRangeIndex].Size, MemRangDesc[MemRangeIndex].Attribute, Status));
            }
        }
    }
    DEBUG ((DEBUG_INFO, "Available MEM above 4G = %lx\n", Tom2));

DoNotReportTom2:
    
    // Report the memory to EFI (MemoryBegin to TOM - TSEGSize - MemoryBegin)
    Status = (*PeiServices)->InstallPeiMemory(PeiServices, MemBegin, (Tom - (MemBegin + TSEG_SIZE)));
    if (Status != EFI_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "Memory reporting failed.\n"));
        return Status;
    }

    if (CapsulePresent) {
        Capsule->CreateState(PeiServices, Buffer, CapsuleSize);
    }

    // Report first 640KB of memory
    Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY,
                                         MEM_DET_COMMON_MEM_ATTR, 0, (640 * 1024));
    if (Status != EFI_SUCCESS) {
    	DEBUG ((DEBUG_ERROR, "640KB Mem reporting HOB creation failed.\n"));
        return Status;
    }

    // Report first 0A0000h - 0FFFFFh as RESERVED memory
    Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_MEMORY_RESERVED,
                                         MEM_DET_COMMON_MEM_ATTR, 0xA0000, (384 * 1024));
    if (Status != EFI_SUCCESS) {
    	DEBUG ((DEBUG_ERROR, "SMRAM ASEG reporting HOB creation failed.\n"));
        return Status;
    }

    // Report UMA range as reserved memory
    if (UmaSize)
    {
        Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_MEMORY_RESERVED,
                                         MEM_DET_COMMON_MEM_ATTR, UmaBase, UmaSize);
        if (Status != EFI_SUCCESS) {
        	DEBUG ((DEBUG_ERROR, "UMA reporting HOB creation failed.\n"));
		    return Status;
	    }
    }

#if	SMM_SUPPORT
    // Report 1MB to (TOM - TSEG_SIZE) as system memory
    Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY,
                                         MEM_DET_COMMON_MEM_ATTR, 0x100000,
                                         (Tom - (TSEG_SIZE + 0x100000)));
    if (Status != EFI_SUCCESS) {
    	DEBUG ((DEBUG_ERROR, "System memory reporting HOB creation failed.\n"));
        return Status;
    }

    // Report (TOM - TSEG_SIZE) to TSEG_SIZE as reserved memory (SMRAM TSEG)
    Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_MEMORY_RESERVED,
                                         MEM_DET_COMMON_MEM_ATTR, (Tom - TSEG_SIZE), TSEG_SIZE);
    if (Status != EFI_SUCCESS) {
    	DEBUG ((DEBUG_ERROR, "SMRAM TSEG reporting HOB creation failed.\n"));
        return Status;
    }
    
    // Create EFI_SMRAM_HOB_DESCRIPTOR_BLOCK for SmmAccess protocol
    Status = (**PeiServices).CreateHob(PeiServices,
                                       EFI_HOB_TYPE_GUID_EXTENSION,
                                       sizeof(AMI_SMRAM_HOB) + (2 * sizeof(EFI_SMRAM_DESCRIPTOR)),
                                       &AmiSmramHob
                                      );
    if (Status != EFI_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "EFI_SMRAM_HOB_DESCRIPTOR_BLOCK HOB creation failed.\n"));
        return Status;
    }

    // The SMRAM combination
    //
    // +----------------------------------+ Tseg Limit = Tseg Base + Tseg Size
    // |                                  |
    // | TSEG usable area                 | TSEG_SIZE - EFI_PAGE_SIZE
    // |                                  |
    // +----------------------------------+ Tseg Base + EFI_PAGE_SIZE
    // |                                  |
    // | TSEG reserved area for S3        | EFI_PAGE_SIZE(4k)
    // |                                  |
    // +----------------------------------+ Tseg Base
    //

    AmiSmramHob->EfiHobGuidType.Name = gEfiSmmPeiSmramMemoryReserveGuid;
    AmiSmramHob->SmramHobDescriptor.NumberOfSmmReservedRegions = 2;
    AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalStart = Tom - TSEG_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[0].CpuStart = Tom - TSEG_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalSize = EFI_PAGE_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[0].RegionState = EFI_ALLOCATED;
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalStart = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalStart));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[0].CpuStart = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[0].CpuStart));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalSize = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalSize));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[0].RegionState = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[0].RegionState));
    
#if(CORE_COMBINED_VERSION <= 0x5000e)
    // Workaround for EIP 481375.
    MemSet((VOID*)AmiSmramHob->SmramHobDescriptor.Descriptor[0].PhysicalStart, EFI_PAGE_SIZE, 0);
#endif

    AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalStart = Tom - TSEG_SIZE + EFI_PAGE_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[1].CpuStart = Tom - TSEG_SIZE + EFI_PAGE_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalSize = TSEG_SIZE - EFI_PAGE_SIZE;
    AmiSmramHob->SmramHobDescriptor.Descriptor[1].RegionState = EFI_SMRAM_CLOSED;
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalStart = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalStart));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[1].CpuStart = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[1].CpuStart));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalSize = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[1].PhysicalSize));
    DEBUG ((DEBUG_INFO, "AmiSmramHob->SmramHobDescriptor.Descriptor[1].RegionState = %x\n", AmiSmramHob->SmramHobDescriptor.Descriptor[1].RegionState));
    
#else			// SMM_SUPPORT
    DEBUG ((DEBUG_INFO, "Creating resource (1M to size:%x)\n", (Tom - 0x100000)));
    // Report 1MB to TOM as system memory
    Status = CreateHobResourceDescriptor(PeiServices, NULL, EFI_RESOURCE_SYSTEM_MEMORY,
                                         MEM_DET_COMMON_MEM_ATTR, 0x100000, (Tom - 0x100000) );
    if (Status != EFI_SUCCESS) {
    	DEBUG ((DEBUG_ERROR, "System memory reporting HOB creation failed.\n"));
        return Status;
    }
#endif

    return Status;
//Above 4GB Memory will be reported in CPUPei.c file.
}

/**
    This function is used to report the installed memory size
    during the S3 resume. It reports the memory from the value
    stored in the NVRAM

    @param PeiServices Pointer to the PEI services table
    @param ReadOnlyVariable Pointer to the Read Only Variable PPI

    @retval EFI_STATUS Return Status

**/

EFI_STATUS
InstallS3Memory(
    IN  EFI_PEI_SERVICES          **PeiServices,
    IN  EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable
)
{
    EFI_STATUS			Status;
    UINTN				S3MemoryBase;
    UINTN				S3MemorySize;
    NB_MEMORY_LENGTH    NbMemoryLength;
    UINTN				        VarSize = sizeof(UINT32);
    UINTN				VarAttrib = 0;
    NB_ACPI_S3_VARIABLE_SET     *NbAcpiS3VariableSet = NULL;
    CHAR16              NbMemoryLengthVar[] = NB_MEMORY_LENGTH_VARIABLE;

    // Get type of EfiACPIMemoryNVS memory (AcpiS3Save.c)
	Status = ReadOnlyVariable->GetVariable (ReadOnlyVariable,
		        NbAcpiS3Variable,
				&gNbAcpiS3VariableGuid,
				NULL,
    			&VarSize,
				&NbAcpiS3VariableSet);
    if (EFI_ERROR (Status) || (NbAcpiS3VariableSet == NULL))
        return EFI_OUT_OF_RESOURCES;

    S3MemoryBase = (UINTN)(NbAcpiS3VariableSet->AcpiReservedMemoryBase);
    S3MemorySize = (UINTN)(NbAcpiS3VariableSet->AcpiReservedMemorySize);

    DEBUG ((DEBUG_INFO, "Installing S3 PEI Memory. SysMem : %dKB \n", (S3MemorySize / 1024)));

    // Report Memory to EFI
    Status = (*PeiServices)->InstallPeiMemory (
                 PeiServices, S3MemoryBase, S3MemorySize);
    ASSERT_EFI_ERROR(Status);

    VarSize = sizeof(NbMemoryLength);
    VarAttrib = 0;

    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                            NbMemoryLengthVar, \
                                            &gNbMemoryLengthGuid, \
                                            &VarAttrib, \
                                            &VarSize, \
                                            &NbMemoryLength );
    if (EFI_ERROR(Status)) return EFI_OUT_OF_RESOURCES;

    DEBUG ((DEBUG_INFO, "Create S3 Memory HOB. Below 4G : %dMB \n",
            ((UINT32)NbMemoryLength.MemoryLengthBelow4G / (1024 * 1024))));
    Status = CreateHobResourceDescriptor( PeiServices, NULL, \
                                          EFI_RESOURCE_SYSTEM_MEMORY, \
                                          MEM_DET_COMMON_MEM_ATTR, 0x100000, \
                                          NbMemoryLength.MemoryLengthBelow4G);
    ASSERT_EFI_ERROR (Status);

    if (NbMemoryLength.MemoryLengthAbove4G) {
        DEBUG ((DEBUG_INFO, "Create S3 Memory HOB. Above 4G : %dMB \n",
                ((UINT32)NbMemoryLength.MemoryLengthAbove4G / (1024 * 1024))));
        Status = CreateHobResourceDescriptor( PeiServices, NULL, \
                                              EFI_RESOURCE_SYSTEM_MEMORY, \
                                              MEM_DET_COMMON_MEM_ATTR, \
                                              0x100000000, \
                                              NbMemoryLength.MemoryLengthAbove4G);

        ASSERT_EFI_ERROR (Status);
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
