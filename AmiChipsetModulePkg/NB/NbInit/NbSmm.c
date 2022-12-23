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

/** @file NbSmm.c
    This file contains code for SMM access and control (both the
    protocol defined by Framework

**/


// Module specific Includes
#include "Efi.h"
#include <Hob.h>
#include <Dxe.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdSocBaseLib.h>
// Used Protocols
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/MpService.h>

// Produced Protocols
#include <Protocol/SmmAccess2.h>
#include "AmiCspLib.h"

// GUID Definitions

// Global variable declarations
CPUINFO_HOB						CpuInfoHob;
BOOLEAN                         EnableSmmBaseLock = FALSE;

// The SMRAM combination
//
// +----------------------------------+ Tseg Limit = Tseg Base + Tseg Size
// |                                  |
// | TSEG usable area                 | TSEG_SIZE - EFI_PAGE_SIZE
// |                                  |
// +----------------------------------+ Tseg Base + EFI_PAGE_SIZE
// |                                  |
// | TSEG reserved area for S3        | EFI_PAGE_SIZE
// |                                  |
// +----------------------------------+ Tseg Base
//
EFI_SMRAM_DESCRIPTOR NbSmramMap[] = {
	{
	    0,                                  //PhysicalStart <--To be filled in.
	    0,                                  //CputStart
	    EFI_PAGE_SIZE,                      //PhysicalSize < - To be filled in.
	    EFI_ALLOCATED    				    //RegionState
	},
	{
	    0,                                  //PhysicalStart <--To be filled in.
	    0,                                  //CputStart
	    1024 * 1024,                        //PhysicalSize < - To be filled in.
	    EFI_SMRAM_CLOSED                    //RegionState
	}
};

#define SMRAM_MAP_NUM_DESCRIPTORS (sizeof(NbSmramMap)/sizeof(EFI_SMRAM_DESCRIPTOR))

EFI_HOB_HANDOFF_INFO_TABLE  *Hit;

// Portable Constants

// Function Prototypes

// Function Definition

/**
    This function programs the NB Tseg Base.  

    @param VOID

    @retval EFI_SUCCESS Always

**/

EFI_STATUS
NbSmmProgramTsegBase (
  IN    VOID
)
{
    UINT64  TsegAddress;

    WriteMsr (AMD_MSR_SMM_ADDR_HL, CpuInfoHob.TsegAddress); // TSEG base

    // Program the TSEG size by programming mask register
    TsegAddress = ReadMsr (AMD_MSR_SMM_MASK_HL);
    TsegAddress &= 0x1FFFF; // Mask off unwanted bits
    TsegAddress |= (~(UINT64)(CpuInfoHob.TsegSize - 1)) & 0xFFFFFFFFFFFE0000;
    TsegAddress |= 0x00;
    if (PcdGetBool(PcdSmmTsegWbSupport))
        TsegAddress |= 0x6000;  // Set Tseg cache type as WB
    else
        TsegAddress |= 0x4000;  // Set Tseg cache type as WT
    WriteMsr (AMD_MSR_SMM_MASK_HL, TsegAddress);

    return EFI_SUCCESS;
}

/**
    This function programs the NB chipset registers to enable
    appropriate SMRAM area.  

    @param VOID

    @retval EFI_SUCCESS Always

    @note  CHIPSET AND/OR BOARD PORTING NEEDED
**/

EFI_STATUS
NbSmmEnableSmmAddress (
  IN    VOID
)
{
    UINT64                      TsegAddress;
    EFI_STATUS                  Status;
    EFI_MP_SERVICES_PROTOCOL    *MpServices;

    // Currently TSEG address is assumed to be TOM - TSEG_SIZE
    // THIS CODE SHOULD BE CHANGED TO GET THE TSEG LOCATION FROM CPU INFO HOB
    TsegAddress = Hit->EfiMemoryTop;
    DEBUG((DEBUG_INFO, "TSEG Address = %lx\n", TsegAddress));

    // It is assumed 0xA0000 to 128K is already enabled
    // Program for TSEG start address
    CpuInfoHob.TsegAddress = TsegAddress;
    CpuInfoHob.TsegSize = TSEG_SIZE;

    NbSmmProgramTsegBase(); // For BSP

    // Execute on running APs
    Status = pBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    ASSERT_EFI_ERROR (Status);

    MpServices->StartupAllAPs (MpServices, (EFI_AP_PROCEDURE)NbSmmProgramTsegBase, FALSE,
                 NULL, (UINTN)NULL, (VOID*)NULL, NULL);

    return EFI_SUCCESS;
}

/**
    This function set AP smram.

    @param VOID

    @retval EFI_SUCCESS Always

**/

EFI_STATUS
ApSetSmram(
  IN    VOID    *SmramState
)
{
    UINT64  MtrrVal;
    UINT64  Value64;

	if (ReadMsr (AMD_MSR_HWCR) & 0x01)
        return EFI_ACCESS_DENIED;   // If device is locked, return error.
	
    // Enable RDMem & WRMem bits visible in fixed MTRR
    MtrrVal = ReadMsr (MSR_SYS_CFG);
    MtrrVal |= ((UINT32)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrVal);

    if (*(UINT64*)SmramState == EFI_SMRAM_OPEN)
    {
        // Enable 0xA0000 read/write
        WriteMsr (MTRR_FIX_16K_A0000, 0x1C1C1C1C1C1C1C1C);
    }
    else if (*(UINT64*)SmramState == EFI_SMRAM_CLOSED)
    {
        // Disable 0xA0000 read/write
        WriteMsr (MTRR_FIX_16K_A0000, 0x0404040404040404);
    }
	
    // Disable RDMem & WRMem bits visible in fixed MTRR
    MtrrVal = ReadMsr (MSR_SYS_CFG);
    MtrrVal &= ~((UINT64)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrVal);

    // Disable/Enable ASEG & TSEG SMRAM for VGA access
    MtrrVal = ReadMsr (AMD_MSR_SMM_MASK_HL);
    if (*(UINT64*)SmramState == EFI_SMRAM_OPEN)
    {
        MtrrVal &= ~((UINT64)3);
    }
    else if (*(UINT64*)SmramState == EFI_SMRAM_LOCKED)
    {
        MtrrVal |= 3;
    }
    WriteMsr (AMD_MSR_SMM_MASK_HL, MtrrVal);

    if (*(UINT64*)SmramState == EFI_SMRAM_LOCKED)
    {
        Value64 = ReadMsr(AMD_MSR_HWCR);
        Value64 |= 0x01;    // SMM lock bit
        // Lock SmmBaseLock if it is Family 17h CPU/APU
        if (EnableSmmBaseLock)
            Value64 |= BIT31;   // SmmBaseLock bit
        WriteMsr (AMD_MSR_HWCR, Value64);
    }
	return	EFI_SUCCESS;
}

/**
    This function set all AP smram.

    @param VOID

    @retval VOID

**/

VOID
AllApSetSmram(
  IN    UINT64  SmramState
)
{
    EFI_STATUS                  Status;
    EFI_MP_SERVICES_PROTOCOL    *MpServices;

    Status = pBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
    ASSERT_EFI_ERROR (Status);

    MpServices->StartupAllAPs(MpServices, (EFI_AP_PROCEDURE)ApSetSmram,
                 TRUE, NULL, (UINTN)NULL, (VOID*)&SmramState, NULL); 
}

/**
    This function programs the NB chipset registers to open
    the SMRAM area.

    @param This Pointer to the SMM access protocol
    @param DescriptorIndex Index of SMM Descriptor

           
    @retval EFI_SUCCESS Opened the SMM area.
    @retval EFI_INVALID_PARAMETER Descriptor doesn't exist.
    @retval EFI_ACCESS_DENIED SMM area locked

    @note  CHIPSET AND/OR BOARD PORTING NEEDED
				Here is the control flow of this function:
					1. If invalid Descriptor return EFI_INVALID_PARAMETER.
					2. Read NB SMM register.
					3. If locked, return EFI_ACCESS_DENIED
					4. Set Value for register to Open SMM area (0a0000 - bffff)
					5. Write Register.
					6. Set OpenState to TRUE.
					7. Set the RegionState to EFI_SMRAM_OPEN.
					8. Return EFI_SUCCESS.
**/

EFI_STATUS
EFIAPI
NbSmmOpenSmram (
  IN    EFI_SMM_ACCESS2_PROTOCOL    *This
)
{
    // All regions must open and close at the same time.
    UINT64  MtrrValue;
    UINTN   i;

    if (ReadMsr (AMD_MSR_HWCR) & 0x01)
        return  EFI_ACCESS_DENIED;  // If device is locked, return error.

    // Enable RDMem & WRMem bits visible in fixed MTRR
    MtrrValue = ReadMsr (MSR_SYS_CFG);
    MtrrValue |= ((UINT32)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrValue);

    // Enable 0xA0000 read/write
    WriteMsr (MTRR_FIX_16K_A0000, 0x1C1C1C1C1C1C1C1C);

    // Disable RDMem & WRMem bits visible in fixed MTRR
    MtrrValue = ReadMsr (MSR_SYS_CFG);
    MtrrValue &= ~((UINT64)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrValue);

    // Disable ASEG & TSEG SMRAM for VGA access
    MtrrValue = ReadMsr (AMD_MSR_SMM_MASK_HL);
    MtrrValue &= ~((UINT64)3);
    WriteMsr (AMD_MSR_SMM_MASK_HL, MtrrValue);

    AllApSetSmram (EFI_SMRAM_OPEN);

    // Update appropriate flags
    This->OpenState = TRUE;
    for (i = 0; i < SMRAM_MAP_NUM_DESCRIPTORS; ++i) 
        NbSmramMap[i].RegionState = EFI_SMRAM_OPEN;

	return EFI_SUCCESS;
}

/**
    This function programs the NB chipset registers to close
    the SMRAM area.

    @param This Pointer to the SMM access protocol
    @param DescriptorIndex Index of SMM Descriptor

           
    @retval EFI_SUCCESS Closed the SMM area.
    @retval EFI_INVALID_PARAMETER Descriptor doesn't exist.
    @retval EFI_ACCESS_DENIED SMM area locked

    @note  CHIPSET AND/OR BOARD PORTING NEEDED
				Here is the control flow of this function:
					1. If invalid Descriptor return EFI_INVALID_PARAMETER.
					2. Read NB SMM register.
					3. If locked, return EFI_ACCESS_DENIED
					4. Set Value for register to close SMM area (0a0000 - bffff)
					5. Write Register.
					6. Set OpenState to FALSE.
					7. Set the RegionState to EFI_SMRAM_CLOSED & EFI_ALLOCATED
					8. Return EFI_SUCCESS.
**/

EFI_STATUS
EFIAPI
NbSmmCloseSmram (
  IN    EFI_SMM_ACCESS2_PROTOCOL    *This
)
{
    // All regions must open and close at the same time.
    UINT64  MtrrValue;
    UINTN   i;

	if (ReadMsr(AMD_MSR_HWCR) & 0x01)
		return EFI_ACCESS_DENIED;   //If device is locked, return error.

    // Enable RDMem & WRMem bits visible in fixed MTRR
    MtrrValue = ReadMsr (MSR_SYS_CFG);
    MtrrValue |= ((UINT32)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrValue);

    // Disable 0xA0000 read/write
    WriteMsr (MTRR_FIX_16K_A0000, 0x0404040404040404);

    // Disable RDMem & WRMem bits visible in fixed MTRR
    MtrrValue = ReadMsr (MSR_SYS_CFG);
    MtrrValue &= ~((UINT64)1 << MtrrFixDramModEnBit);
    WriteMsr (MSR_SYS_CFG, MtrrValue);

    // Enable ASEG & TSEG SMRAM for VGA access
    //MTRRValue = ReadMsr (AMD_MSR_SMM_MASK_HL);
    //MTRRValue |= 3;
    //WriteMsr (AMD_MSR_SMM_MASK_HL, MtrrValue);

    AllApSetSmram (EFI_SMRAM_CLOSED);

    // Update appropriate flags
    This->OpenState = FALSE;
    for (i = 0; i < SMRAM_MAP_NUM_DESCRIPTORS; ++i) 
        NbSmramMap[i].RegionState = EFI_SMRAM_CLOSED | EFI_ALLOCATED;

	return EFI_SUCCESS;
}


/**
    This function programs the NB chipset registers to lock
    the SMRAM area from opening/closing.  Only system level reset
    can unlock the SMRAM lock.

    @param This Pointer to the SMM access protocol
    @param DescriptorIndex Index of SMM Descriptor

           
    @retval EFI_SUCCESS Locked the SMM area.
    @retval EFI_INVALID_PARAMETER Descriptor doesn't exist.
    @retval EFI_DEVICE_ERROR SMM area is opened, need to be
        closed first before locking

    @note  CHIPSET AND/OR BOARD PORTING NEEDED
				Here is the control flow of this function:
					1. If invalid Descriptor return EFI_INVALID_PARAMETER.
					2. Read NB SMM register.
					3. If opened, return EFI_ACCESS_DENIED
					4. Set Value for register to lock SMM area (0a0000 - bffff)
					5. Write Register.
					6. Set the RegionState to EFI_SMRAM_CLOSED & EFI_ALLOCATED
					7. Return EFI_SUCCESS.
**/

EFI_STATUS
EFIAPI
NbSmmLockSmram (
  IN    EFI_SMM_ACCESS2_PROTOCOL    *This
)
{
    UINT64  MtrrValue;
    UINTN   i;
    UINT64  Value64;

    AsmWbinvd();
    // Enable ASEG & TSEG SMRAM for VGA access
    MtrrValue = ReadMsr (AMD_MSR_SMM_MASK_HL);
    MtrrValue |= 3;
    WriteMsr (AMD_MSR_SMM_MASK_HL, MtrrValue);

    AllApSetSmram (EFI_SMRAM_LOCKED);

    // Lock the region
    // Errata 342
    Value64 = ReadMsr (AMD_MSR_HWCR);
    Value64 |= 0x01;    //Smm lock bit
    // Lock SmmBaseLock if it is Family 17h CPU/APU
    if (EnableSmmBaseLock)
        Value64 |= BIT31;    //SmmBaseLock bit
    WriteMsr (AMD_MSR_HWCR, Value64);

    // Update appropriate flags
    This->LockState = TRUE;
    for (i = 0; i < SMRAM_MAP_NUM_DESCRIPTORS; ++i) 
        NbSmramMap[i].RegionState = EFI_SMRAM_LOCKED;

	return EFI_SUCCESS;
}

/**
    This function returns the current SMRAM area map information
    such as number of regions and its start address and size

    @param This Pointer to the SMM access protocol
    @param SmramMapSize Size of the SMRAM map buffer provided
    @param SmramMap Buffer to copy the SMRAM map information

           
    @retval EFI_SUCCESS Smram Map copied into buffer
    @retval EFI_BUFFER_TOO_SMALL Indicates that provided buffer is
        not enough SmramMapSize filled with required/updated size

    @note  CHIPSET AND/OR BOARD PORTING NEEDED
				Here is the control flow of this function:
					1. If Smram Map Size less than the actual map size, set 
						the map size and return EFI_BUFFER_TOO_SMALL.
					2. Copy the Smram Map descriptors into the supplied buffer.
					3. Set the map size in *SmramMapSize, just in case is larger 
						than the actual buffer.
					4. Return EFI_SUCCESS.
**/

EFI_STATUS
EFIAPI
NbSmmGetCapabilities (
  IN CONST  EFI_SMM_ACCESS2_PROTOCOL    *This,
  IN OUT    UINTN                   *SmramMapSize,
  OUT       EFI_SMRAM_DESCRIPTOR    *SmramMap
)
{
	UINTN		i;

	if (*SmramMapSize < sizeof(NbSmramMap))
    {
        // If input map size to small report the correct map size and return error.
        *SmramMapSize = sizeof (NbSmramMap);
        return  EFI_BUFFER_TOO_SMALL;
    }

    for (i = 0; i < SMRAM_MAP_NUM_DESCRIPTORS; ++i) 
        SmramMap[i] = NbSmramMap[i];

	*SmramMapSize = sizeof(NbSmramMap);			//Set the correct map size in case too large.
	return EFI_SUCCESS;
}

EFI_SMM_ACCESS2_PROTOCOL    SmmAccess = {
    NbSmmOpenSmram,
    NbSmmCloseSmram,
    NbSmmLockSmram,
    NbSmmGetCapabilities,
    FALSE,
    FALSE
};

/**
    This function is invoked from NB DXE to initialize SMM
    related stuff in NorthBridge and install appropriate
    SMM protocols such as SMM Access & SMM Control

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS Return Status based on errors that occurred while waiting for
        time to expire.

**/

EFI_STATUS
EFIAPI
NbSmmInit (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    SOC_ID_STRUCT               SocId;

    Hit = GetEfiConfigurationTable (SystemTable, &gEfiHobListGuid);

    // The SMRAM combination
    //
    // +----------------------------------+ Tseg Limit = Tseg Base + Tseg Size
    // |                                  |
    // | TSEG usable area                 | TSEG_SIZE - EFI_PAGE_SIZE
    // |                                  |
    // +----------------------------------+ Tseg Base + EFI_PAGE_SIZE
    // |                                  |
    // | TSEG reserved area for S3        | EFI_PAGE_SIZE
    // |                                  |
    // +----------------------------------+ Tseg Base
    //

    NbSmramMap[0].PhysicalStart = Hit->EfiMemoryTop;
    NbSmramMap[0].CpuStart = Hit->EfiMemoryTop;
    NbSmramMap[0].PhysicalSize = EFI_PAGE_SIZE;
    NbSmramMap[0].RegionState = EFI_ALLOCATED;
    DEBUG ((DEBUG_INFO, "NbSmramMap[0].PhysicalStart = %lx\n", NbSmramMap[0].PhysicalStart));
    DEBUG ((DEBUG_INFO, "NbSmramMap[0].CpuStart = %lx\n", NbSmramMap[0].CpuStart));
    DEBUG ((DEBUG_INFO, "NbSmramMap[0].PhysicalSize = %lx\n", NbSmramMap[0].PhysicalSize));
    DEBUG ((DEBUG_INFO, "NbSmramMap[0].RegionState = %lx\n", NbSmramMap[0].RegionState));

    NbSmramMap[1].PhysicalStart = Hit->EfiMemoryTop + EFI_PAGE_SIZE;
    NbSmramMap[1].CpuStart = Hit->EfiMemoryTop + EFI_PAGE_SIZE;
    NbSmramMap[1].PhysicalSize = TSEG_SIZE - EFI_PAGE_SIZE;
    NbSmramMap[1].RegionState = EFI_SMRAM_CLOSED;
    DEBUG ((DEBUG_INFO, "NbSmramMap[1].PhysicalStart = %lx\n", NbSmramMap[1].PhysicalStart));
    DEBUG ((DEBUG_INFO, "NbSmramMap[1].CpuStart = %lx\n", NbSmramMap[1].CpuStart));
    DEBUG ((DEBUG_INFO, "NbSmramMap[1].PhysicalSize = %lx\n", NbSmramMap[1].PhysicalSize));
    DEBUG ((DEBUG_INFO, "NbSmramMap[1].RegionState = %lx\n", NbSmramMap[1].RegionState));

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;
    if (!SocHardwareIdentificationCheck (&SocId))
    {
        // PSP have to fix issue first or there will be some problem when doing capsule.
        //EnableSmmBaseLock = TRUE;
    }

    // Enable SMM address range by programming appropriate chipset registers
    NbSmmEnableSmmAddress();
    return  pBS->InstallMultipleProtocolInterfaces(&ImageHandle,
                  &gEfiSmmAccess2ProtocolGuid, &SmmAccess,	NULL, NULL);
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
