//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


/** @file SecMain.c
    SEC phase

**/

#include "SecMain.h"
#include "Token.h"
#include <Library/AmdCapsuleLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Guid/AmiPsp.h>
#if defined(SERIAL_DEBUGGER_SUPPORT) && (SERIAL_DEBUGGER_SUPPORT == 1)
extern UINTN Code_Start_Addr;
extern UINTN Code_End_Addr;
#endif

EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI SecTemporaryRamSupportPpi = {
  TemporaryRamMigration
};

EFI_PEI_PPI_DESCRIPTOR  SecTemporaryRamPpi[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiTemporaryRamSupportPpiGuid,
    &SecTemporaryRamSupportPpi
  }
};

EFI_PEI_PPI_DESCRIPTOR  SecTemporaryRamAndCapsulePpi[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI,
        &gEfiTemporaryRamSupportPpiGuid,
        &SecTemporaryRamSupportPpi
    },
    {
        (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
        &gCapsuleUpdateDetectedPpiGuid,
        NULL
    }
};

//
// These are IDT entries pointing to 10:FFFFFFE4h.
//
UINT64  mIdtEntryTemplate = 0xffff8e000010ffe4ULL;


VOID
EFIAPI
FindAndReportEntryPoints (
  IN  EFI_FIRMWARE_VOLUME_HEADER       *BootFirmwareVolumePtr,
  OUT EFI_PEI_CORE_ENTRY_POINT         *PeiCoreEntryPoint
  );

VOID
EFIAPI
SecCEntry (
  IN UINT32     SizeTmpRam,
  IN UINT32     TmpRamBase,
  IN VOID       *Bfv
  )
{
    EFI_SEC_PEI_HAND_OFF        SecCoreData;
    IA32_DESCRIPTOR             IdtDescriptor;
    SEC_IDT_TABLE               IdtTableInStack;
    UINT32                      Index;
    EFI_STATUS                  Status;
    UINT32                      RegisterEax = 0;
    // Should we identify Fv protocol(AKA-FileSystemGuid).
    EFI_FIRMWARE_VOLUME_HEADER      *FvH = (EFI_FIRMWARE_VOLUME_HEADER*)Bfv;
    EFI_FIRMWARE_VOLUME_EXT_HEADER  *FvExtH = (EFI_FIRMWARE_VOLUME_EXT_HEADER*)((UINT32)FvH + (UINT32)FvH->ExtHeaderOffset);

	InitializeFloatingPointUnits();

	// |-------------------|---->
	// |Idt Table          |
	// |-------------------|
	// |PeiService Pointer |    PeiStackSize
	// |-------------------|
	// |                   |
	// |      Stack        |
	// |-------------------|----> StackBase (MKF_CAR_BASE_ADDRESS + MKF_CAR_TOTAL_SIZE/2)
	// |                   |
	// |                   |
	// |      Heap         |    PeiTemporaryRamSize
	// |                   |
	// |                   |
	// |-------------------|---->  TempRamBase
	IdtTableInStack.PeiService = 0;
	for (Index = 0; Index < SEC_IDT_ENTRY_COUNT; Index ++) {
	    CopyMem ((VOID*)&IdtTableInStack.IdtTable[Index], (VOID*)&mIdtEntryTemplate, sizeof (UINT64));
	}

	IdtDescriptor.Base  = (UINTN) &IdtTableInStack.IdtTable;
	IdtDescriptor.Limit = (UINT16)(sizeof (IdtTableInStack.IdtTable) - 1);
	AsmWriteIdtr (&IdtDescriptor);

	//
	// Setup the default exception handlers
	//
	Status = InitializeCpuExceptionHandlers (NULL);
	ASSERT_EFI_ERROR (Status);

    // EAX : Version Information (Type, Family, Model, and Stepping ID)
    AsmCpuid(AMD_EXT_CPUID_1, &RegisterEax, NULL, NULL, NULL);
#ifdef PSP_FV_BB_SIZE
	#define SEC_C_FV_BB_SIZE PSP_FV_BB_SIZE
    //
    // building individual FV-GUID on ROM.
    // The PeiInitializeFv will install the ppi for Bfv.
    // The kernel will consider we have extra FV in system if FV_BB and FV_BB_AMD_FEATURE_FV were different.
    // but we have to provide the individual FV-GUID for them for the tool to identify each FV if tool has PSP-decompression ability.
    // So sync FV_BB-GUID of memory with FV_BB_AMD_FEATURE_FV-GUID of ROM at this point.
    //
    //###DEBUG ((DEBUG_INFO,"  [%a] Convert the [%g] of memory BB",gEfiCallerBaseName,&FvExtH->FvName));
    CopyGuid(&FvExtH->FvName, &gAmiPspFvBbFirmwareVolumeGuid);
    //###DEBUG ((DEBUG_INFO,"  to [%g] of ROM BB >>\n",&FvExtH->FvName));
#else
    #define SEC_C_FV_BB_SIZE FV_BB_SIZE
#endif
    SecCoreData.DataSize               = (UINT16) sizeof (EFI_SEC_PEI_HAND_OFF);
    SecCoreData.BootFirmwareVolumeBase = Bfv;
    SecCoreData.BootFirmwareVolumeSize = (UINTN)SEC_C_FV_BB_SIZE;
    SecCoreData.TemporaryRamBase       = (VOID*)TmpRamBase; 
    SecCoreData.TemporaryRamSize       = SizeTmpRam;
    SecCoreData.PeiTemporaryRamBase    = (VOID*)TmpRamBase;
    SecCoreData.PeiTemporaryRamSize    = SizeTmpRam/2;
    SecCoreData.StackBase              = (VOID*)(TmpRamBase + SizeTmpRam/2);
    SecCoreData.StackSize              = SizeTmpRam/2;

    //
    // Initialize Debug Agent to support source level debug in SEC/PEI phases before memory ready.
    //
    if ((RegisterEax & AMI_RAW_FAMILY_ID_MASK) == AMI_F15_BR_RAW_ID)
    {   // Family 15
        InitializeDebugAgent (DEBUG_AGENT_INIT_PREMEM_SEC, &SecCoreData, (DEBUG_AGENT_CONTINUE)((UINT64)SecCPhase2));        
    }
    else
    {
#if defined(SERIAL_DEBUGGER_SUPPORT) && (SERIAL_DEBUGGER_SUPPORT == 1)
		//
		// The original value is the following in debugger module.....
		//      -----------------------------------------------------------
		//      --- AMIDebuggerPkg/Debugger/DbgDbgrLib/DbgrHdr.c  ---------
		//                UINTN Code_Start_Addr = (0xffffffff - FLASH_SIZE);
		//                UINTN Code_End_Addr	= 0xffffffff;
		//      -----------------------------------------------------------
		// The debugger suppose the code running in ROM but family17 is in ram.
		//
		// The following implement to solve the debugger issue.
		// When SERIAL_DEBUGGER_SUPPORT turn on. The Code_Start_Addr exist in the DebugAgentLib.
		// For Family17 we can update the global variable->Code_Start_Addr and correct it to memory. For Family15 the coding no effected.
		// The debugger will check the debug symbol of code address whether within Code_Start_Addr or not.
		// then debugger will return correct status.
		//
	#if defined(FV_REBASE_SUPPORT) && (FV_REBASE_SUPPORT == 1)
    	Code_Start_Addr = HIGH_MEMORY_REGION_BB_BASE;
		Code_End_Addr	= (HIGH_MEMORY_REGION_BB_BASE + PSP_FV_BB_SIZE) - 1;
	#endif
#endif

#if FV_REBASE_SUPPORT
    	// ReBase means SecCPhase2 has pointed to high memory.
    	InitializeDebugAgent (DEBUG_AGENT_INIT_PREMEM_SEC, &SecCoreData, (DEBUG_AGENT_CONTINUE)((UINT64)SecCPhase2));
#else
        InitializeDebugAgent (DEBUG_AGENT_INIT_PREMEM_SEC, &SecCoreData, (DEBUG_AGENT_CONTINUE)(((UINT64)SecCPhase2 & (SEC_C_FV_BB_SIZE - 1)) + HIGH_MEMORY_REGION_BB_BASE));
#endif
    }
}

VOID
EFIAPI
SecCPhase2 (
  IN    VOID    *Context
)
{

    EFI_PEI_CORE_ENTRY_POINT    PeiCoreEntryPoint;
    EFI_SEC_PEI_HAND_OFF        *SecCoreData;
    EFI_PEI_PPI_DESCRIPTOR      *PpiList;
    
    SecCoreData = (EFI_SEC_PEI_HAND_OFF *) Context;
    //
    // Find Pei Core entry point. It will report SEC and Pei Core debug information if remote debug
    // is enabled.
    //
    FindAndReportEntryPoints ((EFI_FIRMWARE_VOLUME_HEADER *) SecCoreData->BootFirmwareVolumeBase, &PeiCoreEntryPoint);
    ASSERT (PeiCoreEntryPoint != NULL);
    if (PeiCoreEntryPoint == NULL)
    {
      CpuDeadLoop ();
    }

    // The 8 comes from below code in Startup32.asm
    // SECCore_PspResEntry::
    // mov     esi, eax                ; Save Eax - pointer to PSP_SMM_RSM_MEM_INFO
    // push    53535353h
    // push    ebx                     ; Save Ebx - Signature CAPSULE_UPDATE_SIGNATURE
    if (*(UINT32 *)((UINTN)(SecCoreData->TemporaryRamBase) + SecCoreData->TemporaryRamSize - 8) == 0xCA9501EFul)
    {
        PpiList = &SecTemporaryRamAndCapsulePpi[0];
    }
    else
    {
        PpiList = &SecTemporaryRamPpi[0];
    }

    // Call PEI Foundation entry point
    (*PeiCoreEntryPoint) (SecCoreData, PpiList);
    
    // Should not return here
}


/**
  Find core image base.
  
  @param   BootFirmwareVolumePtr    Point to the boot firmware volume.
  @param   SecCoreImageBase         The base address of the SEC core image.
  @param   PeiCoreImageBase         The base address of the PEI core image.

**/
EFI_STATUS
EFIAPI
FindImageBase (
  IN  EFI_FIRMWARE_VOLUME_HEADER       *BootFirmwareVolumePtr,
  OUT EFI_PHYSICAL_ADDRESS             *SecCoreImageBase,
  OUT EFI_PHYSICAL_ADDRESS             *PeiCoreImageBase
  )
{
  EFI_PHYSICAL_ADDRESS        CurrentAddress;
  EFI_PHYSICAL_ADDRESS        EndOfFirmwareVolume;
  EFI_FFS_FILE_HEADER         *File;
  UINT32                      Size;
  EFI_PHYSICAL_ADDRESS        EndOfFile;
  EFI_COMMON_SECTION_HEADER   *Section;
  EFI_PHYSICAL_ADDRESS        EndOfSection;

  *SecCoreImageBase = 0;
  *PeiCoreImageBase = 0;

  CurrentAddress = (EFI_PHYSICAL_ADDRESS)(UINTN) BootFirmwareVolumePtr;
  EndOfFirmwareVolume = CurrentAddress + BootFirmwareVolumePtr->FvLength;

  //
  // Loop through the FFS files in the Boot Firmware Volume
  //
    for (EndOfFile = CurrentAddress + BootFirmwareVolumePtr->HeaderLength; ; )
    {
        CurrentAddress = (EndOfFile + 7) & 0xFFFFFFFFFFFFFFF8ULL;
        if (CurrentAddress > EndOfFirmwareVolume)
            return EFI_NOT_FOUND;

        File = (EFI_FFS_FILE_HEADER*)(UINTN) CurrentAddress;
        if (IS_FFS_FILE2 (File))
        {
            Size = FFS_FILE2_SIZE (File);
            if (Size <= 0x00FFFFFF)
                return EFI_NOT_FOUND;
        }
        else
        {
            Size = FFS_FILE_SIZE (File);
            if (Size < sizeof (EFI_FFS_FILE_HEADER))
                return EFI_NOT_FOUND;
        }

        EndOfFile = CurrentAddress + Size;
        if (EndOfFile > EndOfFirmwareVolume)
            return EFI_NOT_FOUND;

        //
        // Look for SEC Core / PEI Core files
        //
        if (File->Type != EFI_FV_FILETYPE_SECURITY_CORE &&
             File->Type != EFI_FV_FILETYPE_PEI_CORE)
            continue;

        //
        // Loop through the FFS file sections within the FFS file
        //
        if (IS_FFS_FILE2 (File))
            EndOfSection = (EFI_PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) File + sizeof (EFI_FFS_FILE_HEADER2));
        else
            EndOfSection = (EFI_PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) File + sizeof (EFI_FFS_FILE_HEADER));

        for (;;)
        {
            CurrentAddress = (EndOfSection + 3) & 0xFFFFFFFFFFFFFFFCULL;
            Section = (EFI_COMMON_SECTION_HEADER*)(UINTN) CurrentAddress;

            if (IS_SECTION2 (Section))
            {
                Size = SECTION2_SIZE (Section);
                if (Size <= 0x00FFFFFF)
                    return EFI_NOT_FOUND;
            }
            else
            {
                Size = SECTION_SIZE (Section);
                if (Size < sizeof (EFI_COMMON_SECTION_HEADER))
                    return EFI_NOT_FOUND;
            }

            EndOfSection = CurrentAddress + Size;
            if (EndOfSection > EndOfFile)
                return EFI_NOT_FOUND;

            //
            // Look for executable sections
            //
            if (Section->Type == EFI_SECTION_PE32 || Section->Type == EFI_SECTION_TE)
            {
                if (File->Type == EFI_FV_FILETYPE_SECURITY_CORE)
                {
                    if (IS_SECTION2 (Section))
                        *SecCoreImageBase = (PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) Section + sizeof (EFI_COMMON_SECTION_HEADER2));
                    else
                        *SecCoreImageBase = (PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) Section + sizeof (EFI_COMMON_SECTION_HEADER));
                }
                else
                {
                    if (IS_SECTION2 (Section))
                        *PeiCoreImageBase = (PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) Section + sizeof (EFI_COMMON_SECTION_HEADER2));
                    else
                        *PeiCoreImageBase = (PHYSICAL_ADDRESS) (UINTN) ((UINT8 *) Section + sizeof (EFI_COMMON_SECTION_HEADER));
                }
                break;
            }
        }

        //
        // Both SEC Core and PEI Core images found
        //
        if (*SecCoreImageBase != 0 && *PeiCoreImageBase != 0)
            return EFI_SUCCESS;
    }
}

/**
    Returns PEI Core Entry point. Used for debug.

        
    @param BootFirmwareVolumePtr 
    @param PeiCoreEntryPoint 

         
    @retval VOID

**/

VOID
EFIAPI
FindAndReportEntryPoints (
  IN  EFI_FIRMWARE_VOLUME_HEADER    *BootFirmwareVolumePtr,
  OUT EFI_PEI_CORE_ENTRY_POINT      *PeiCoreEntryPoint
  )
{
    EFI_STATUS                       Status;
    EFI_PHYSICAL_ADDRESS             SecCoreImageBase;
    EFI_PHYSICAL_ADDRESS             PeiCoreImageBase;
    PE_COFF_LOADER_IMAGE_CONTEXT     ImageContext;

    //
    // Find SEC Core and PEI Core image base
    //
    Status = FindImageBase (BootFirmwareVolumePtr, &SecCoreImageBase, &PeiCoreImageBase);
    ASSERT_EFI_ERROR (Status);

    ZeroMem ((VOID *) &ImageContext, sizeof (PE_COFF_LOADER_IMAGE_CONTEXT));
    //
    // Report SEC Core debug information when remote debug is enabled
    //
    ImageContext.ImageAddress = SecCoreImageBase;
    ImageContext.PdbPointer = PeCoffLoaderGetPdbPointer ((VOID*) (UINTN) ImageContext.ImageAddress);
    PeCoffLoaderRelocateImageExtraAction (&ImageContext);

    //
    // Report PEI Core debug information when remote debug is enabled
    //
    ImageContext.ImageAddress = PeiCoreImageBase;
    ImageContext.PdbPointer = PeCoffLoaderGetPdbPointer ((VOID*) (UINTN) ImageContext.ImageAddress);
    PeCoffLoaderRelocateImageExtraAction (&ImageContext);

    //
    // Find PEI Core entry point
    //
    Status = PeCoffLoaderGetEntryPoint ((VOID *) (UINTN) PeiCoreImageBase, (VOID**) PeiCoreEntryPoint);
    if (EFI_ERROR (Status))
        *PeiCoreEntryPoint = 0;

    return;

}

/**
    Move memory content from Temporary Memory to Permanent Memory.

        
    @param PeiServices 
    @param TemporaryMemoryBase 
    @param PermanentMemoryBase 
    @param CopySize 

         
    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS
TemporaryRamMigration(
  IN CONST  EFI_PEI_SERVICES        **PeiServices,
  IN        EFI_PHYSICAL_ADDRESS    TemporaryMemoryBase,
  IN        EFI_PHYSICAL_ADDRESS    PermanentMemoryBase,
  IN        UINTN                   CopySize
)
{
    IA32_DESCRIPTOR   IdtDescriptor;
    VOID*             OldHeap;
    VOID*             NewHeap;
    VOID*             OldStack;
    VOID*             NewStack;
    DEBUG_AGENT_CONTEXT_POSTMEM_SEC  DebugAgentContext;
//--    UINTN             Offset;

    if (TemporaryMemoryBase > PermanentMemoryBase)
        if ((PermanentMemoryBase + CopySize) > TemporaryMemoryBase)
            return EFI_INVALID_PARAMETER;

//      MemCpy((VOID*) PermanentMemoryBase, (VOID*) TemporaryMemoryBase, CopySize); //remove original

 //  Temporary Memory
 // |-------------------|
 // |                   |
 // |                   |
 // |                   |    PeiStackSize
 // |     Stack         |
 // |                   |
 // |                   |
 // |-------------------|----> StackBase (TempRamBase + CopySize/2)
 // |                   |
 // |                   |       PeiTemporayRamSize
 // |      Heap         |
 // |                   |
 // |                   |
 // |-------------------|---->  TempRamBase




 //  Permanent Memory
 // |-------------------|---->  (PermanentMemoryBase + CopySize)
 // |                   |
 // |                   |
 // |                   |
 // |     Heap          |
 // |                   |
 // |                   |
 // |-------------------|----> NewHeap (PermanentMemoryBase + CopySize/2)
 // |                   |
 // |                   |
 // |       Stack       |
 // |                   |
 // |                   |
 // |                   |
 // |-------------------|---->  PermanentMemoryBase (NewStack)

    OldHeap = (VOID*)(UINTN)TemporaryMemoryBase;
    NewHeap = (VOID*)((UINTN)PermanentMemoryBase + CopySize/2 );

    OldStack = (VOID*)((UINTN)TemporaryMemoryBase + CopySize/2 );
    NewStack = (VOID*)((UINTN)PermanentMemoryBase );

    DebugAgentContext.HeapMigrateOffset = (UINTN)NewHeap - (UINTN)OldHeap;
    DebugAgentContext.StackMigrateOffset = (UINTN)NewStack - (UINTN)OldStack;     

    InitializeDebugAgent (DEBUG_AGENT_INIT_POSTMEM_SEC, (VOID *) &DebugAgentContext, NULL);
    
    //
    // Migrate Heap
    //
    CopyMem(NewHeap, OldHeap, CopySize/2);

    //
    // Migrate Stack
    //
    CopyMem(NewStack, OldStack, CopySize/2);


    //                                                                          
    // Rebase IDT table in permanent memory                                     
    //                                                                            //
    AsmReadIdtr (&IdtDescriptor);                                                 // SecSwitchStack function must be invoked after the memory migration
    IdtDescriptor.Base = IdtDescriptor.Base - (UINTN)OldStack + (UINTN)NewStack;  // immediately, also we need fixup the stack change caused by new call into
                                                                                // permanent memory.
    AsmWriteIdtr (&IdtDescriptor);                                                //

    SecSwitchStack (
    (UINT32) (UINTN) OldStack,
    (UINT32) ((UINTN) NewStack)
    );

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
