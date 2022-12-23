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

/** @file NbDxe.c
    This file contains code for Template Northbridge initialization
    in the DXE stage

**/

// Module specific Includes

#include <Uefi.h>
#include <Library/UefiLib.h>
#include "Token.h"
#include <Dxe.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "AmiCspLib.h"
#include "NbDxeBoard.h"
#include "Nb.h"
#include "NbS3Save.h"
#include "Ppi/Nbppi.h"
#include "Library/NbPolicy.h"
#include "Guid/AmdMemoryInfoHob.h"
#include <Protocol/S3SaveState.h>
#include <Protocol/MpService.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/DebugLib.h>

#define  PCI_ADDRESS(bus, dev, func, reg) \
            ((UINT64) ( (((UINT8)bus) << 16) + (((UINT8)dev) << 11) + \
            (((UINT8)func) << 8) + ((UINT8)reg) )) & 0x00000000FFFFFFFF

// Build flag adjustments
#ifndef		SMM_SUPPORT
#define		SMM_SUPPORT			0
#endif

// Start S3 declaration
VOID SavePciRegisters(gPciRegistersSavelist *gPciRegistersSavelisttbl);
VOID SavePciIndexRegisters(gPciIndexRegistersSavelist *gPciIndexRegistersSavelisttbl);
VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context);
EFI_STATUS  CreateNbMemoryInfo (IN  EFI_SYSTEM_TABLE    *SystemTable);
EFI_S3_SAVE_STATE_PROTOCOL          *gBootScriptSave;
EFI_STATUS  SaveAmdMemInfoHob();
//End S3 declaration
CHAR16      NbAcpiS3Variable[] = NB_ACPI_S3_VARIABLE;

// External data definitions
EFI_GUID    gEfiSetupGuid = SETUP_GUID;

//VOID        SetMemClrFlag(IN EFI_EVENT Event, IN VOID *Context);

/*
//
//  Name: NbCspResTable
//
//
//      UEFI References:
//          Platform Initialization Specification (Ver. 1.0)
//              Pre-EFI Initialization Core Interface
//                  Services - DXE Services
//                      Global Coherency Domain Services:
//                          AddMemorySpace()
//                          EFI_GCD_MEMORY_TYPE (also see DXE.h)
//          UEFI Specification (Ver. 2.1)
//              Services - Boot Services
//                  Memory Allocation Services
//                      GetMemoryMap
//                          Memory Attribute Definitions (Also see EFI.h)
//
//
//      Example entry into NbCspResTable for flash device:
//
//          FLASH_SIZE = 0x100000 => FLASH_DEVICE_BASE_ADDRESS = FFF00000
//                                => FWH_FEATURE_SPACE_BASE    = FFB00000
//
//          CSP_RES_ITEM NbCspResTable[] =
//          {
//            { 0xFFF00000,                        // ResBase = Flash base
//	            0x100000,                          // ResLength = 1 MB region
//	            EfiGcdMemoryTypeMemoryMappedIo,    // ResType
//	            EFI_MEMORY_UC|EFI_MEMORY_RUNTIME } // Attributes
//          }
//
//      THIS TABLE MUST BE FILLED WITH RESOURCE REGIONS DECODED
//      BY THE NB FOR ITSELF. !!! Use  Attributes field == -1
//      to mark an IO Space Resource. You must provide valid
//      attributes for Memory Mapped IO regions.
//
*/
//============================================================================
//
//----------------------------------------------------------------------------
CSP_RES_ITEM NbCspResTable[] = {

//==============================================================================//
//{UINT64 ResBase, UINTN ResLength, GCD_MEMORY_TYPE ResType, UINT64 Attributes}	//
//==============================================================================//

// 16k of dmi registers
//{ 0xFED00000, 0x00100000, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC)},

// Cpu's local apic dedicated space
{ APIC_BASE, 0x00100000, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)},

// Here goes reserved i/o space
// I/O used for pci config access
{ 0xCF8, 0x00000008, EfiGcdIoTypeIo, -1},

//============================================================================

};
UINTN   NbCspResCount = sizeof (NbCspResTable) / sizeof (CSP_RES_ITEM);

// Produced Protocols

// GUID Definitions

// Global variable declarations
EFI_EVENT           EvtBootScript;
//EFI_EVENT           EvtSetMemClrFlag;

// Portable Constants

// Function Prototypes
#if SMM_SUPPORT
EFI_STATUS EFIAPI NbSmmInit (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
#endif

/**
    AMD PciConfig read function....Reads Normal and Extended PCI space

        
    @param Address 
    @param ExtAccess use Extended PCI space access if TRUE

         
    @retval UINT32 The value read from the indicated Address.

    @note  
  Supports only 32 bit read only to be used for S3 Feature

**/

UINT32
AmdPciConfigRead(
  IN    UINT32  Address,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = ((UINT32)1 << 31) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 16) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 11) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register);

    PciAddress &= 0xFFFFFFFC;   // Dword align

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress |= 0x1000000;

    IoWrite32 (0xCF8, PciAddress);
    return IoRead32 (0xCFC);    // Return the read value
}


/**
    Write a value into the PCI register indicated

        
    @param Address 
    @param Value 
    @param ExtAccess 

         
    @retval VOID

**/

VOID
AmdPciConfigWrite(
  IN    UINT32  Address,
  IN    UINT32  Value,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = ((UINT32)1 << 31) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 16) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 11) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register);

    PciAddress &= 0xFFFFFFFC;

    // If extended config Access requested then add the extended config address  bit (24 to 27)
    if (ExtAccess)
        PciAddress |= 0x1000000;

    IoWrite32 (0xCF8, PciAddress);	// Select the register to write
    IoWrite32 (0xCFC, Value);	// Write the Value
}

/**
    Reserve the resource that NB needs.

        
    @param ImgHandle 
    @param CntrHandle 

         
    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
ReserveNbResources(
  IN    EFI_HANDLE  ImgHandle,
  IN    EFI_HANDLE  CntrHandle
)
{
	EFI_STATUS			Status = EFI_SUCCESS;

//#if CORE_COMBINED_VERSION > 4600
    Status = LibAllocCspResource (NbCspResTable, NbCspResCount, ImgHandle, CntrHandle);
//#endif
    return Status;
}


/**
    NB late init.

        
    @param ImageHandle 
    @param SystemTable 

         
    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
DoNbLateInit(
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    return Status;
}

/**
    This function is the entry point for this DXE. This function
    initializes the chipset NB

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS Return Status based on errors that occurred while waiting for
        time to expire.

**/

EFI_STATUS
EFIAPI
NbDxeInit (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable
)
{
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo;
    EFI_STATUS                          Status = EFI_SUCCESS;
    EFI_MP_SERVICES_PROTOCOL            *MpServices;
    UINTN                               NumEnCpus;
    UINTN                               NumCpus = 1;
    NB_ACPI_S3_VARIABLE_SET             *NbAcpiS3VariableSet;
    EFI_PHYSICAL_ADDRESS                AcpiMemoryBase;
    SOC_ID_STRUCT                       SocId;

	InitAmiLib(ImageHandle, SystemTable);
    PROGRESS_CODE(DXE_NB_INIT);
    Status = pBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status = MpServices->GetNumberOfProcessors(MpServices, &NumCpus, &NumEnCpus );
        ASSERT_EFI_ERROR(Status);
    }

    NbAcpiS3VariableSet = (NB_ACPI_S3_VARIABLE_SET*) 0xFFFFFFFF;
    Status = pBS->AllocatePages(
        AllocateMaxAddress,
        EfiACPIMemoryNVS,
        EFI_SIZE_TO_PAGES(sizeof(NB_ACPI_S3_VARIABLE_SET)),
        (EFI_PHYSICAL_ADDRESS*)&NbAcpiS3VariableSet
    );
    ASSERT_EFI_ERROR(Status);
    pBS->SetMem(NbAcpiS3VariableSet, sizeof(NB_ACPI_S3_VARIABLE_SET),0);

    // Allocate ACPI reserved memory for S3 resume.
    Status = pBS->AllocatePages (
        AllocateAnyPages,
        EfiACPIMemoryNVS,
        EFI_SIZE_TO_PAGES(S3_BASE_MEMORY_SIZE + S3_MEMORY_SIZE_PER_CPU * NumCpus),
        &AcpiMemoryBase
        );
    ASSERT_EFI_ERROR(Status);

    NbAcpiS3VariableSet->AcpiReservedMemoryBase = (EFI_PHYSICAL_ADDRESS)AcpiMemoryBase;
    NbAcpiS3VariableSet->AcpiReservedMemorySize = S3_BASE_MEMORY_SIZE + S3_MEMORY_SIZE_PER_CPU * (UINT32)NumCpus;

    DEBUG ((DEBUG_INFO, "AcpiMemoryBase = %x\n", AcpiMemoryBase));
    DEBUG ((DEBUG_INFO, "AcpiReservedMemorySize = %x\n", NbAcpiS3VariableSet->AcpiReservedMemorySize));

    Status = pRS->SetVariable(
            NbAcpiS3Variable,
            &gNbAcpiS3VariableGuid,
            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
            sizeof(UINT32),
            &NbAcpiS3VariableSet
        );

	Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
	ASSERT_EFI_ERROR(Status);
	
	Status = pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid, NULL, &gBootScriptSave);
	
	ASSERT_EFI_ERROR(Status);

    ReserveNbResources (ImageHandle, SystemTable);
    ASSERT_EFI_ERROR (Status);

#if SMM_SUPPORT
#if defined (AmdCpuPkg_SUPPORT) && (AmdCpuPkg_SUPPORT)
// Skip installation of SmmAccess Protocol if AmdCpuPkg used
#else
    PROGRESS_CODE(DXE_NB_SMM_INIT);
/*	Status = NBSMM_Init (ImageHandle, SystemTable);
	if (Status != EFI_SUCCESS) {
		DEBUG ((DEBUG_ERROR, "NBSMM_Init() = %r\n", Status));
		return Status;
	}
*/
#endif	
#endif

    Status = CreateNbMemoryInfo (SystemTable);

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (SocHardwareIdentificationCheck(&SocId))
    {
        Status = CreateReadyToBootEvent (TPL_NOTIFY, CallbackBootScript, NULL, &EvtBootScript);
        ASSERT_EFI_ERROR(Status);
    }
    // [Fam15 only] >
    // Create ready to boot event for SetMemClrFlag
    /*
    Status = pBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    SetMemClrFlag,
                    NULL,
                    &gEfiEndOfDxeEventGroupGuid,
                    &EvtSetMemClrFlag
                    );
    ASSERT_EFI_ERROR (Status);
    */
    // [Fam15 only] <
    
    Status = SaveAmdMemInfoHob();

    return EFI_SUCCESS;
}

// [Fam15 only]
/**
    This function set the memory clear flag

        
    @param Event 
    @param Context 

         
    @retval VOID

**/
/*
VOID
SetMemClrFlag(
  IN    EFI_EVENT   Event,
  IN    VOID        *Context
)
{
    SETUP_DATA      SetupData;
    UINTN           VariableSize = sizeof(SETUP_DATA);
    EFI_STATUS      Status;
    UINT32          Attributes;

    Status = pRS->GetVariable (L"Setup", &gEfiSetupGuid, &Attributes, &VariableSize,
                   &SetupData);
    if(EFI_ERROR(Status))
        DEBUG((EFI_ERROR, "NBDXE SetMemClrFlag GetVariable Error\n"));
    
    SetupData.MemClrFlag = 1;   // Set memory clear flag before boot
    
    pRS->SetVariable (L"Setup", &gEfiSetupGuid, Attributes, VariableSize, &SetupData);
    if(EFI_ERROR(Status))
        DEBUG((EFI_ERROR, "NBDXE SetMemClrFlag SetVariable Error\n"));
    
    // Kill the Event
    pBS->CloseEvent(Event);
}
*/

#pragma pack (push, 1)
typedef struct
{
    EFI_HOB_GUID_TYPE       EfiHobGuidType;
    AMD_MEMORY_INFO_HOB     MemInfoHob;
}AMI_AMD_MEM_INFO_HOB;
#pragma pack (pop)

/**
    Saves AMD_MEMORY_INFO_HOB into NVRAM variable AmiMemInfo.

        
    @param VOID

         
    @retval EFI_SUCCESS HOB found and variable saved
    @retval EFI_NOT_FOUND HOB not found

**/

EFI_STATUS 
SaveAmdMemInfoHob(
  IN    VOID
)
{
    AMI_AMD_MEM_INFO_HOB        *TempHob;
    AMD_MEMORY_INFO_HOB         *MemInfoHob;
    AMD_MEMORY_RANGE_DESCRIPTOR *MemRangDesc;
    AMI_MEM_INFO                AmiMemInfo = {0};
    EFI_STATUS                  Status;
    EFI_GUID                    HobListGuid = HOB_LIST_GUID;
    UINT32                      Index = 0;
    UINT32                      TempLowestLoMemAddr = 0;
    UINT64                      TempHigestHiMemAddr = 0;
    
    TempHob = (AMI_AMD_MEM_INFO_HOB *)GetEfiConfigurationTable(pST, &HobListGuid);

    if (TempHob == NULL)
    {
        DEBUG ((DEBUG_ERROR, "Can't find Hob list"));
        return EFI_NOT_FOUND;
    }
    else
    {
        Status = FindNextHobByGuid(&gAmdMemoryInfoHobGuid, &TempHob);
        if (!EFI_ERROR(Status))
        {
            MemInfoHob = &(TempHob->MemInfoHob);
            MemRangDesc = &MemInfoHob->Ranges[0];
        }
        else
        {
            DEBUG ((DEBUG_ERROR, "Can't find gAmdMemoryInfoHobGuid"));
            return EFI_NOT_FOUND;
        }
    }

    AmiMemInfo.UmaBase = 0;
    AmiMemInfo.UmaSize = 0;
    DEBUG ((DEBUG_INFO, "MemInfoHob->NumberOfDescriptor = %x\n", MemInfoHob->NumberOfDescriptor));
    //MemRangDesc = &MemInfoHob->Ranges[0];

    for (Index = 0; Index < MemInfoHob->NumberOfDescriptor; Index++)
    {
        if ((MemRangDesc[Index].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) && (MemRangDesc[Index].Base < 0x100000000))
            if (TempLowestLoMemAddr < (UINT32)(MemRangDesc[Index].Base + MemRangDesc[Index].Size))
            {
                TempLowestLoMemAddr = (UINT32)(MemRangDesc[Index].Base + MemRangDesc[Index].Size);
                DEBUG ((DEBUG_INFO, "TempLowestLoMemAddr = %lx \n", TempLowestLoMemAddr));
            }

        if ((MemRangDesc[Index].Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) && (MemRangDesc[Index].Base >= 0x100000000))
        {
            if (TempHigestHiMemAddr < (UINT32)(MemRangDesc[Index].Base + MemRangDesc[Index].Size))
            {
                TempHigestHiMemAddr = MemRangDesc[Index].Base + MemRangDesc[Index].Size;
                DEBUG ((DEBUG_INFO, "TempHigestHiMemAddr = %lx \n", TempHigestHiMemAddr));
            }
        }

        if (MemRangDesc[Index].Attribute == AMD_MEMORY_ATTRIBUTE_UMA)
        {
            AmiMemInfo.UmaBase = MemRangDesc[Index].Base;
            AmiMemInfo.UmaSize = MemRangDesc[Index].Size;
        }
    }

    AmiMemInfo.LoMemBase = (UINT32)MemRangDesc[0].Base;
    AmiMemInfo.LoMemSize = TempLowestLoMemAddr - AmiMemInfo.LoMemBase;
    if (TempHigestHiMemAddr != 0)
    {
        AmiMemInfo.HiMemBase = 0x100000000;
        AmiMemInfo.HiMemSize = TempHigestHiMemAddr - 0x100000000;
    }
    else
    {
        AmiMemInfo.HiMemBase = 0;
        AmiMemInfo.HiMemSize = 0;
    }
    DEBUG ((DEBUG_INFO, "AmiMemInfo.LoMemBase = %lx \n", AmiMemInfo.LoMemBase));
    DEBUG ((DEBUG_INFO, "AmiMemInfo.LoMemSize = %lx \n", AmiMemInfo.LoMemSize));
    DEBUG ((DEBUG_INFO, "AmiMemInfo.HiMemBase = %lx \n", AmiMemInfo.HiMemBase));
    DEBUG ((DEBUG_INFO, "AmiMemInfo.HiMemSize = %lx \n", AmiMemInfo.HiMemSize));
    DEBUG ((DEBUG_INFO, "Uma Base = %lx\n", AmiMemInfo.UmaBase));
    DEBUG ((DEBUG_INFO, "Uma Size = %lx\n", AmiMemInfo.UmaSize));
    Status = pRS->SetVariable (L"AmiMemInfo", &gAmiMemInfoGuid, EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS, sizeof (AMI_MEM_INFO), &AmiMemInfo);
    return Status;
}

/**
    This function is to get the memory length information(TOM)
    from PEI by HOB. And save it to variable for S3 resume.

        
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS Return Status

**/

EFI_STATUS
CreateNbMemoryInfo (
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                  Status;
    EFI_GUID                    HobListGuid = HOB_LIST_GUID;
    CHAR16                      NbMemoryLengthVar[] = NB_MEMORY_LENGTH_VARIABLE;
    NB_MEMORY_LENGTH            NbMemoryLength;
    NB_MEMORY_LENGTH            LastNbMemoryLength;
    VOID				        *FirstHob;
    EFI_HOB_RESOURCE_DESCRIPTOR *ResDescHob;
    UINTN                       DataSize = sizeof (NB_MEMORY_LENGTH);


    NbMemoryLength.MemoryLengthBelow4G = 0;
    NbMemoryLength.MemoryLengthAbove4G = 0;

    FirstHob = GetEfiConfigurationTable (SystemTable, &HobListGuid);
    if (!FirstHob)
        ASSERT_EFI_ERROR (EFI_NOT_FOUND);
    ResDescHob = (EFI_HOB_RESOURCE_DESCRIPTOR*) FirstHob;

    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_RESOURCE_DESCRIPTOR,
                                &ResDescHob)))
    {
		if (ResDescHob->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY)
		{
			if (ResDescHob->PhysicalStart >= 0x100000)
            {
                NbMemoryLength.MemoryLengthAbove4G += ResDescHob->ResourceLength;
                if (ResDescHob->PhysicalStart <= 0xFFFFFFFF)
           	        NbMemoryLength.MemoryLengthBelow4G += ResDescHob->ResourceLength;
            }
		}
	}
    NbMemoryLength.MemoryLengthAbove4G -= NbMemoryLength.MemoryLengthBelow4G;
    Status = pRS->GetVariable (NbMemoryLengthVar, &gNbMemoryLengthGuid, NULL,
                   &DataSize, &LastNbMemoryLength);

    if (Status != EFI_SUCCESS)
    {
        Status = pRS->SetVariable (NbMemoryLengthVar, &gNbMemoryLengthGuid,
                       EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                       sizeof (NbMemoryLength), &NbMemoryLength);
        ASSERT_EFI_ERROR (Status);
    }
    else
    {
        if (MemCmp ((VOID*)&NbMemoryLength, (UINT8*)&LastNbMemoryLength, DataSize) != 0)
        {
            Status = pRS->SetVariable (NbMemoryLengthVar, &gNbMemoryLengthGuid,
                           EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                           sizeof (NbMemoryLength), &NbMemoryLength);
            ASSERT_EFI_ERROR(Status);
        }
    }
    return EFI_SUCCESS;
}

//Bus 0, Device 0x18, Function 0
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciRegistersSave_F0[] = {
//	AMD_K8_nF0_LDT0_CTL,  EfiBootScriptWidthUint32,
//	AMD_K8_nF0_LDT0_REV,  EfiBootScriptWidthUint32,

	AMD_K8_nF0_LDT0_BCT,  EfiBootScriptWidthUint32,
	AMD_K8_nF0_LDT0_BUSN, EfiBootScriptWidthUint32,
	AMD_K8_nF0_LDT1_BCT, EfiBootScriptWidthUint32,
	AMD_K8_nF0_LDT2_BUSN, EfiBootScriptWidthUint32,
	AMD_K8_nF0_LDT_TRAN_CTL,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

//Bus 0, Device 0x18, Function 1
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciRegistersSave_F1[] = {
//Save DRAM BASE Limit
	AMD_K8_nF1_DRAM_L0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L3,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B3,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L4,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B4,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L5,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B5,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L6,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B6,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_L7,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_DRAM_B7,  EfiBootScriptWidthUint32,
//Save MMIO
	AMD_K8_nF1_MMIO_L0,  EfiBootScriptWidthUint32,
    AMD_K8_nF1_MMIO_B0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L3,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B3,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L4,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B4,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L5,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B5,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L6,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B6,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_L7,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_MMIO_B7,  EfiBootScriptWidthUint32,
//SAVE PCI IO
	AMD_K8_nF1_PCIIO_L0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_B0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_L1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_B1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_L2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_B2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_L3,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_PCIIO_B3,  EfiBootScriptWidthUint32,
//Save CFG Base and limit
	AMD_K8_nF1_CFGBASE0,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_CFGBASE1,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_CFGBASE2,  EfiBootScriptWidthUint32,
	AMD_K8_nF1_CFGBASE3,  EfiBootScriptWidthUint32,
//Save DRAM Hole
	AMD_K8_nF1_DRAM_HOLE + 3, EfiBootScriptWidthUint8,
	AMD_K8_nF1_DRAM_HOLE + 2, EfiBootScriptWidthUint8,
	AMD_K8_nF1_DRAM_HOLE + 1, EfiBootScriptWidthUint8,
	AMD_K8_nF1_DRAM_HOLE, EfiBootScriptWidthUint8,
	0xF4,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

//Bus 0, Device 0x18, Function 2
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciRegistersSave_F2[] = {
	//AMD_K8_nF2_TSC_LOW,  EfiBootScriptWidthUint32,
	//AMD_K8_nF2_TSC_UPR,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_BASE,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_CURR,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_CTRL,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_START,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_STOP,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRACE_CAPT,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRIG0_CMDL,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRIG0_CMDH,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRIG0_MSKL,  EfiBootScriptWidthUint32,
	AMD_K8_nF2_TRIG0_MSKH,  EfiBootScriptWidthUint32,
	//As per AMD
//	0xE0,	EfiBootScriptWidthUint32,
//	0xE4,	EfiBootScriptWidthUint32,
//	0xE8,	EfiBootScriptWidthUint32,
//	0xEC,	EfiBootScriptWidthUint32,
//	0x78,   EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

//Bus 0, Device 0x18, Function 3
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciRegistersSave_F3[] = {

	AMD_K8_nF3_MCA_NBCTL,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_MCA_NBCFG,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_SCRUB_ADL,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_SCRUB_ADH,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_SCRUB_CTL,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_PM_CTL_LOW,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_PM_CTL_HIGH,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_NB_CFG_LOW,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_NB_CFG_HIGH,  EfiBootScriptWidthUint32,
	0x94, EfiBootScriptWidthUint32,
	0x98, EfiBootScriptWidthUint32,
	0x90, EfiBootScriptWidthUint32,
	AMD_K8_nF3_CLK_PWR_LOW,  EfiBootScriptWidthUint32,
	AMD_K8_nF3_CLK_PWR_HIGH,  EfiBootScriptWidthUint32,

	AMD_K8_nF3_HT_PTR_OPT_REG,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

// [Fam15 only]
/**
    This function saves the boot script

        
    @param Event 
    @param Context 

         
    @retval VOID

**/

VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context)
{
	static BOOLEAN BootScriptSaved = FALSE;

	gPciRegistersSavelist gPciRegistersSavelisttbl[] =
    {
        {gPciRegistersSave_F0, (UINT64)NB_PCI_CFG_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, 0)},
        {gPciRegistersSave_F1, (UINT64)NB_PCI_CFG_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_ADRM_FUNC, 0)},
        {gPciRegistersSave_F2, (UINT64)NB_PCI_CFG_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_DDR_FUNC, 0)},
        {gPciRegistersSave_F3, (UINT64)NB_PCI_CFG_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_MISC_FUNC, 0)},
        {(BOOT_SCRIPT_PCI_REGISTER_SAVE *)0xFF, 0xFF},
    };

    if (BootScriptSaved) return;

	// Save the define PciReg
	SavePciRegisters (gPciRegistersSavelisttbl);

	BootScriptSaved = TRUE;

}

/**
    Save the gPciRegisterSaveListtbl pci devices save the reg
    for S3 resume wirte back.

        
    @param gPciRegistersSavelisttbl 

         
    @retval VOID

**/

VOID SavePciRegisters( IN gPciRegistersSavelist *gPciRegistersSavelisttbl)
{
    UINT8   j;
    UINT8   i;
    UINT8   Buffer8;
    UINT32  Buffer32;
    UINT16  Buffer16;
    UINT64  Address64;

    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
    EFI_STATUS  Status;

    Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid,NULL,&PciRootBridgeIo);
    if (EFI_ERROR(Status)) return;

	j  =  0;
    while(gPciRegistersSavelisttbl[j].DevAddr != 0xFF)
    {
        i = 0;
    	while(gPciRegistersSavelisttbl[j].gPciRegisters[i].Address != 0xFF)
        {
            Address64 = (UINT64)(gPciRegistersSavelisttbl[j].DevAddr +
                                gPciRegistersSavelisttbl[j].gPciRegisters[i].Address);

            switch(gPciRegistersSavelisttbl[j].gPciRegisters[i].Width)
            {
                case    EfiBootScriptWidthUint8:
						PciRootBridgeIo->Pci.Read(
        	 			   	PciRootBridgeIo,
        	  			   	gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
        	  			   	Address64,
        	  			   	1,
        	 			   	&Buffer8
        					);
                        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                             CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                             EfiPciWidthUint8, Address64, 1, &Buffer8);

					break;
				case	EfiBootScriptWidthUint16:
						PciRootBridgeIo->Pci.Read(
        	 			   	PciRootBridgeIo,
        	  			   	gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
        	  			   	Address64,
        	  			   	1,
        	 			   	&Buffer16
        					);
                           BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint16, Address64, 1, &Buffer16);

					break;
				case	EfiBootScriptWidthUint32:
						PciRootBridgeIo->Pci.Read(
        	 			   	PciRootBridgeIo,
        	  			   	gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
        	  			   	Address64,
        	  			   	1,
        	 			   	&Buffer32
        					);
              BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32, Address64, 1, &Buffer32);

					break;
			}   // end of switch(gPciRegistersSavelisttbl[j].gPciRegisters[i].Width)
			i++;
    	}   // end of while(gPciRegistersSavelisttbl[j].gPciRegisters[i].Address != 0xFF)
		j++;
	}   // end of while(gPciRegistersSavelisttbl[j].DevAddr != 0xFF)
}
//////////////////////////////S3 PCI Context ends /////////////////////////////////////////

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
