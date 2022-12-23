//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
#include <Protocol/SmmAccess2.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <Library/UefiLib.h>
#include <Protocol/SmmReadyToLock.h>
#include <Protocol/AmiSmmBufferValidation.h>
#include <Protocol/LegacyBiosPlatform.h>
#include <Guid/MemoryAttributesTable.h>
#include <Guid/PiSmmCommunicationRegionTable.h>

// Defined in SmmCommSmiHandler.c
EFI_STATUS SmmAmiBufferValidationLibCheckSmmCommunicationBuffer(
    CONST VOID* Buffer, CONST UINTN BufferSize
);
EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibSmiHandlerConstructor(VOID);
EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibSmiHandlerDestructor(VOID);

#define IS_BUFFER_OVERFLOW(BufferAddress, BufferSize) ( (BufferSize) != 0 && (UINTN)(BufferAddress) - 1 + (BufferSize) < (UINTN)(BufferAddress) )
#define IS_RT_MEMORY_DESCRIPTOR(Descriptor) (\
     (Descriptor)->Type == EfiReservedMemoryType || (Descriptor)->Type == EfiACPIMemoryNVS\
  || (Descriptor)->Type == EfiRuntimeServicesCode || (Descriptor)->Type == EfiRuntimeServicesData\
)

// Private GCD capability used by DxeMain GCD implementation to track untested memory.
// Since these are not defined in a public header, define them here.
#define EFI_MEMORY_PRESENT      0x0100000000000000ULL

typedef struct {
    EFI_PHYSICAL_ADDRESS Address;
    UINT64 Size;
} SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE;

SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE *SmmAmiBufferValidationLibSmramRanges = NULL;
UINTN SmmAmiBufferValidationLibNumberOfSmramRanges = 0;

SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE *SmmAmiBufferValidationLibMemoryRanges = NULL;
UINTN SmmAmiBufferValidationLibNumberOfMemoryRanges = 0;

SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE *SmmAmiBufferValidationLibMmioRanges = NULL;
UINTN SmmAmiBufferValidationLibNumberOfMmioRanges = 0;

SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE *SmmAmiBufferValidationLibRoRanges = NULL;
UINTN SmmAmiBufferValidationLibNumberOfRoRanges = 0;

VOID *SmmAmiBufferValidationLibReadyToLockRegistration = NULL;

BOOLEAN SmmAmiBufferValidationLibSmmIsLocked = FALSE;
BOOLEAN SmmAmiBufferValidationLibCsmEnabled = FALSE;

EFI_HANDLE SmmAmiBufferValidationLibValidationProtocolHandle = NULL;

// When CSM is enabled we're allowing SMM communication with certain buffers below 1MB.
SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE SmmAmiBufferValidationLibCsmRanges[] = {
    // {0, 0x400} - IVT. Can't be used as SMM communication buffer.
    {0x400, 0xA0000 - 0x400},
    // {0xA0000, 0x40000} - Video buffer and OpROM space. Can't be used as SMM communication buffer.
    // NOTE: OpROM space may span beyond 0xE0000. We're patching this entry in
    //   SmmAmiBufferValidationLibReadyToLock using information returned by CSM.
    {0xE0000, 0x20000}
};

// //////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Functions
// //////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @internal
    Returns an error if buffer overlaps with a list of illegal address ranges.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer
    @param  Range Pointer to array of illegal ranges to check the buffer against
    @param  NumberOfRanges Number of elements in the Range array

    @retval  EFI_SUCCESS - The buffer address range is valid and does not overlap with the address ranges in Range
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with one of the ranges in Range.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS SmmAmiBufferValidationLibCheckBufferAgainstBlockedList(
    CONST VOID* Buffer, CONST UINTN BufferSize,
    CONST SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE* Range, CONST UINTN NumberOfRanges
){
    UINTN  i;
    UINTN BufferAddress;

    if (Buffer == NULL) return EFI_INVALID_PARAMETER;
    if (Range==NULL) return EFI_NOT_FOUND;

    BufferAddress = (UINTN)Buffer;
    if (IS_BUFFER_OVERFLOW(BufferAddress, BufferSize)) return EFI_INVALID_PARAMETER; // overflow
    for (i = 0; i < NumberOfRanges; i ++) {
        if (    BufferAddress >= Range[i].Address
             && BufferAddress < Range[i].Address + Range[i].Size
        ) return EFI_ACCESS_DENIED; // Buffer starts in the blocked list region
        if (    BufferAddress < Range[i].Address
             && BufferAddress+BufferSize > Range[i].Address
        ) return EFI_ACCESS_DENIED; // Buffer overlaps with the blocked list region
    }

    return EFI_SUCCESS;
}

/** @internal
    Returns an error if buffer does not fit into one of the dedicated address ranges.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer
    @param  Range Pointer to array of dedicated ranges to check the buffer against
    @param  NumberOfRanges Number of elements in the Range array

    @retval  EFI_SUCCESS - The buffer address range is valid and is a subregion of one of the address ranges in Range
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because it is not a subregion of an address ranges in Range
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS SmmAmiBufferValidationLibCheckBufferAgainstAllowedList(
    CONST VOID* Buffer, CONST UINTN BufferSize,
    CONST SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE* Range, CONST UINTN NumberOfRanges
){
    UINTN  i;
    UINTN BufferAddress;

    if (Buffer == NULL) return EFI_INVALID_PARAMETER;
    if (Range==NULL) return EFI_NOT_FOUND;

    BufferAddress = (UINTN)Buffer;
    if (IS_BUFFER_OVERFLOW(BufferAddress, BufferSize)) return EFI_INVALID_PARAMETER; // overflow
    for (i = 0; i < NumberOfRanges; i ++) {
        if (    BufferAddress >= Range[i].Address
             && BufferAddress+BufferSize <= Range[i].Address + Range[i].Size
        ) return EFI_SUCCESS; // Entire Buffer is in the Allowed list region
    }

    return EFI_ACCESS_DENIED;
}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////
// AmiBufferValidationLib Library Class Functions
// //////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    Validates memory buffer.

    The function verifies the buffer to make sure its address range is legal for a memory buffer.
    SMI handlers that receive buffer address and/or size from outside of SMM at runtime must validate
    the buffer using this function prior to using it or passing to other SMM interfaces.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer

    @retval  EFI_SUCCESS - The buffer address range is valid and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS EFIAPI SmmAmiBufferValidationLibAmiValidateMemoryBuffer(CONST VOID* Buffer, CONST UINTN BufferSize){
    EFI_STATUS Status;

    Status = SmmAmiBufferValidationLibCheckBufferAgainstBlockedList(
        Buffer,BufferSize,
        SmmAmiBufferValidationLibSmramRanges,SmmAmiBufferValidationLibNumberOfSmramRanges
    );
    if (EFI_ERROR(Status)){
        DEBUG((DEBUG_ERROR, "ERROR: SMM communication buffer is in SMRAM.\n"));
        return Status;
    }

    if (   (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_ACCESS_TO_OS_MEMORY) == 0
         && SmmAmiBufferValidationLibSmmIsLocked
    ) {
        if (SmmAmiBufferValidationLibRoRanges != NULL){
            Status = SmmAmiBufferValidationLibCheckBufferAgainstBlockedList(
                Buffer,BufferSize,
                SmmAmiBufferValidationLibRoRanges,SmmAmiBufferValidationLibNumberOfRoRanges
            );
            if (EFI_ERROR(Status)){
                DEBUG((DEBUG_ERROR, "ERROR: SMM communication buffer overlaps with RT driver code section.\n"));
                return Status;
            }
        }
        Status = SmmAmiBufferValidationLibCheckBufferAgainstAllowedList(
            Buffer,BufferSize,
            SmmAmiBufferValidationLibMemoryRanges,SmmAmiBufferValidationLibNumberOfMemoryRanges
         );
        if (EFI_ERROR(Status)){
            // When CSM is enabled we're allowing SMM communication with certain buffers below 1MB.
            if (SmmAmiBufferValidationLibCsmEnabled){
                Status = SmmAmiBufferValidationLibCheckBufferAgainstAllowedList(
                    Buffer,BufferSize,
                    SmmAmiBufferValidationLibCsmRanges,ARRAY_SIZE(SmmAmiBufferValidationLibCsmRanges)
                 );
            }
            if (EFI_ERROR(Status))
                DEBUG((DEBUG_ERROR, "ERROR: SMM communication buffer is NOT in the region reserved by firmware for RT access.\n"));
        } else {
            Status = SmmAmiBufferValidationLibCheckSmmCommunicationBuffer(Buffer, BufferSize);
        }
    }

    return Status;
}

/**
    Validates MMIO buffer.

    The function verifies the buffer to make sure its address range is legal for a MMIO buffer.
    SMI handlers that receive buffer address and/or size from outside of SMM at runtime must validate
    the buffer using this function prior to using it or passing to other SMM interfaces.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer

    @retval  EFI_SUCCESS - The buffer address range is valid and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because its address range overlaps with protected area such as SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS EFIAPI SmmAmiBufferValidationLibAmiValidateMmioBuffer(CONST VOID* Buffer, CONST UINTN BufferSize){

    EFI_STATUS Status;

    Status = SmmAmiBufferValidationLibCheckBufferAgainstBlockedList(
        Buffer,BufferSize,
        SmmAmiBufferValidationLibSmramRanges,SmmAmiBufferValidationLibNumberOfSmramRanges
    );
    if (EFI_ERROR(Status)) return Status;

    if (!SmmAmiBufferValidationLibSmmIsLocked) return Status;

    Status = SmmAmiBufferValidationLibCheckBufferAgainstAllowedList(
        Buffer,BufferSize,
        SmmAmiBufferValidationLibMmioRanges,SmmAmiBufferValidationLibNumberOfMmioRanges
    );

    return Status;
}

EFI_STATUS EFIAPI AmiValidateMemoryBuffer(CONST VOID* Buffer, CONST UINTN BufferSize){
    EFI_STATUS Status = SmmAmiBufferValidationLibAmiValidateMemoryBuffer(Buffer, BufferSize);
    if (EFI_ERROR(Status))
        DEBUG((DEBUG_ERROR,
            "[%a]: SMM buffer security violation.\n(Address=%p; Size=%X).\n",
            gEfiCallerBaseName, Buffer, BufferSize
        ));
    return Status;
}

EFI_STATUS EFIAPI AmiValidateMmioBuffer(CONST VOID* Buffer, CONST UINTN BufferSize){
    EFI_STATUS Status = SmmAmiBufferValidationLibAmiValidateMmioBuffer(Buffer, BufferSize);
    if (EFI_ERROR(Status))
        DEBUG((DEBUG_ERROR,
            "[%a]: SMM buffer security violation.\nBased on GCD map, MMIO Buffer(Address=%p; Size=%X) is NOT in the region where MMIO is allowed.\n",
            gEfiCallerBaseName, Buffer, BufferSize
        ));
    return Status;
}

/**
    Validates SMRAM buffer.

    The function verifies the buffer to make sure it resides in the SMRAM.

    @param  Buffer Buffer address
    @param  BufferSize Size of the Buffer

    @retval  EFI_SUCCESS - The buffer resides in the SMRAM and can be safely used.
    @retval  EFI_ACCESS_DENIED - The buffer can't be used because at least one byte of the buffer is outside of SMRAM.
    @retval  EFI_INVALID_PARAMETER - The buffer can't be used because its address range is invalid.
    @retval  EFI_NOT_FOUND - The buffer can't be used because its validity cannot be verified.
**/
EFI_STATUS EFIAPI AmiValidateSmramBuffer(CONST VOID* Buffer, CONST UINTN BufferSize){
    return SmmAmiBufferValidationLibCheckBufferAgainstAllowedList(
        Buffer,BufferSize,
        SmmAmiBufferValidationLibSmramRanges,SmmAmiBufferValidationLibNumberOfSmramRanges
    );
}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////
// Library Initialization Functions
// //////////////////////////////////////////////////////////////////////////////////////////////////////////
EFI_STATUS SmmAmiBufferValidationLibGetMemMap(){
    EFI_STATUS Status;
    UINTN Size;
    EFI_MEMORY_DESCRIPTOR *MemMap = NULL;
    EFI_MEMORY_DESCRIPTOR *Descriptor;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
    UINTN i;

    Size = 0;
    Status = gBS->GetMemoryMap(&Size, MemMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    ASSERT(Status==EFI_BUFFER_TOO_SMALL);
    if (Status!=EFI_BUFFER_TOO_SMALL) return Status;

    // The following memory allocation may alter memory map.
    // Let's add space for 16 more descriptors to be sure the buffer is big enough.
    Size += 16 * DescriptorSize;
    Status = gBS->AllocatePool(EfiBootServicesData, Size, (VOID**)&MemMap);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->GetMemoryMap(&Size, MemMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)){
        gBS->FreePool(MemMap);
        return Status;
    }
    for(   Descriptor = MemMap
         ; (UINT8*)Descriptor < (UINT8*)MemMap+Size
         ; Descriptor = NEXT_MEMORY_DESCRIPTOR(Descriptor,DescriptorSize)
    ){
        if (IS_RT_MEMORY_DESCRIPTOR(Descriptor)) SmmAmiBufferValidationLibNumberOfMemoryRanges++;
    }

    SmmAmiBufferValidationLibMemoryRanges = AllocatePool (
        SmmAmiBufferValidationLibNumberOfMemoryRanges * sizeof(SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE)
    );
    ASSERT (SmmAmiBufferValidationLibMemoryRanges != NULL);
    if (SmmAmiBufferValidationLibMemoryRanges == NULL){
        SmmAmiBufferValidationLibNumberOfMemoryRanges = 0;
        gBS->FreePool(MemMap);
        return EFI_OUT_OF_RESOURCES;
    }
    for(   Descriptor = MemMap, i=0
         ; (UINT8*)Descriptor < (UINT8*)MemMap+Size
         ; Descriptor = NEXT_MEMORY_DESCRIPTOR(Descriptor,DescriptorSize)
    ){
        if (IS_RT_MEMORY_DESCRIPTOR(Descriptor)){
            ASSERT((UINTN)Descriptor->NumberOfPages == Descriptor->NumberOfPages);
            if (Descriptor->Type == EfiReservedMemoryType){
               EFI_GCD_MEMORY_SPACE_DESCRIPTOR  GcdDescriptor;
               // Reserved memory requires additional verification step.
               // UEFI memory map includes two types of reserved memory:
               // - Memory allocated with AllocatePages/AllocatePool.
               //   This memory can be used as SMM communication buffer.
               // - Memory imported from GCD map.
               //   This memory cannot be used as SMM communication buffer.
               Status = gDS->GetMemorySpaceDescriptor(Descriptor->PhysicalStart,&GcdDescriptor);
               if (EFI_ERROR(Status)) continue;
               if (    GcdDescriptor.GcdMemoryType != EfiGcdMemoryTypeSystemMemory
                    && GcdDescriptor.GcdMemoryType != EfiGcdMemoryTypeMoreReliable
                    && GcdDescriptor.GcdMemoryType != EfiGcdMemoryTypePersistentMemory
               ) continue;
            }
            SmmAmiBufferValidationLibMemoryRanges[i].Address = Descriptor->PhysicalStart;
            SmmAmiBufferValidationLibMemoryRanges[i].Size = EFI_PAGES_TO_SIZE((UINTN)Descriptor->NumberOfPages);
            i++;
        }
    }
    ASSERT(i<=SmmAmiBufferValidationLibNumberOfMemoryRanges);
    SmmAmiBufferValidationLibNumberOfMemoryRanges = i;
    gBS->FreePool(MemMap);
    return EFI_SUCCESS;
}

EFI_STATUS SmmAmiBufferValidationLibGetGcdMap(){
    UINTN NumberOfDescriptors, i, j;
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR *GcdMap;
    EFI_STATUS Status;

    Status = gDS->GetMemorySpaceMap (&NumberOfDescriptors, &GcdMap);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    for (i = 0; i < NumberOfDescriptors; i++) {
        if (    GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo
             || (  GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeNonExistent
                && (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_MMIO_IN_NON_EXISTENT_REGIONS)
                )
             || (  GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeReserved
                && (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_MMIO_IN_RESERVED_REGIONS)
                )
        ) SmmAmiBufferValidationLibNumberOfMmioRanges++;
    }

    SmmAmiBufferValidationLibMmioRanges = AllocatePool (
        SmmAmiBufferValidationLibNumberOfMmioRanges * sizeof(SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE)
    );
    ASSERT (SmmAmiBufferValidationLibMmioRanges != NULL);
    if (SmmAmiBufferValidationLibMmioRanges == NULL){
        SmmAmiBufferValidationLibNumberOfMmioRanges = 0;
        gBS->FreePool(GcdMap);
        return EFI_OUT_OF_RESOURCES;
    }
    for (i = 0, j=0; i < NumberOfDescriptors; i++) {
        if (    GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo
             || (  GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeNonExistent
                && (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_MMIO_IN_NON_EXISTENT_REGIONS)
                )
             || (  GcdMap[i].GcdMemoryType == EfiGcdMemoryTypeReserved
                && (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_MMIO_IN_RESERVED_REGIONS)
                // Memory above 4GB is typically reported by MRC as untested in the resource HOB.
                // GCD converts such untested memory into Reserved region with
                // private(not defined by PI spec) EFI_MEMORY_PRESENT attribute.
                // The region is converted to conventional system memory at
                // some point during the boot process and should not be treated
                // as valid MMIO region.
                && (GcdMap[i].Capabilities & EFI_MEMORY_PRESENT) == 0
                )
        ){
            SmmAmiBufferValidationLibMmioRanges[j].Address = GcdMap[i].BaseAddress;
            SmmAmiBufferValidationLibMmioRanges[j].Size = GcdMap[i].Length;
            j++;
        }
    }
    ASSERT(j<=SmmAmiBufferValidationLibNumberOfMmioRanges);
    SmmAmiBufferValidationLibNumberOfMmioRanges = j;
    gBS->FreePool (GcdMap);
    return EFI_SUCCESS;
}

EFI_STATUS SmmAmiBufferValidationLibGetMemoryAttributesTable(){
    EFI_STATUS Status;
    EFI_MEMORY_ATTRIBUTES_TABLE  *AttrTable;
    EFI_MEMORY_DESCRIPTOR *Descriptor;
    EFI_MEMORY_DESCRIPTOR *FirstDescriptor;
    EFI_MEMORY_DESCRIPTOR *EndOfDescriptors;
    UINTN i;


    Status = EfiGetSystemConfigurationTable(&gEfiMemoryAttributesTableGuid, (VOID**)&AttrTable);
    if (EFI_ERROR(Status)) return Status;

    FirstDescriptor = (EFI_MEMORY_DESCRIPTOR*)(AttrTable + 1);
    EndOfDescriptors = (EFI_MEMORY_DESCRIPTOR*)(
                           (UINT8*)FirstDescriptor + AttrTable->NumberOfEntries * AttrTable->DescriptorSize
                       );

    for(   Descriptor = FirstDescriptor
         ; Descriptor < EndOfDescriptors
         ; Descriptor = NEXT_MEMORY_DESCRIPTOR(Descriptor,AttrTable->DescriptorSize)
    ){
        if (    (Descriptor->Attribute & EFI_MEMORY_RO) != 0
             && (    Descriptor->Type == EfiRuntimeServicesCode
                  || Descriptor->Type == EfiRuntimeServicesData
                )
        ) SmmAmiBufferValidationLibNumberOfRoRanges++;
    }
    SmmAmiBufferValidationLibRoRanges = AllocatePool (
            SmmAmiBufferValidationLibNumberOfRoRanges * sizeof(SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE)
    );
    ASSERT (SmmAmiBufferValidationLibRoRanges != NULL);
    if (SmmAmiBufferValidationLibRoRanges == NULL){
        SmmAmiBufferValidationLibNumberOfRoRanges = 0;
        return EFI_OUT_OF_RESOURCES;
    }
    for(   Descriptor = FirstDescriptor, i=0
         ; Descriptor < EndOfDescriptors
         ; Descriptor = NEXT_MEMORY_DESCRIPTOR(Descriptor,AttrTable->DescriptorSize)
    ){
        if (    (Descriptor->Attribute & EFI_MEMORY_RO) != 0
             && Descriptor->Type == EfiRuntimeServicesCode
        ){
            ASSERT((UINTN)Descriptor->NumberOfPages == Descriptor->NumberOfPages);
            SmmAmiBufferValidationLibRoRanges[i].Address = Descriptor->PhysicalStart;
            SmmAmiBufferValidationLibRoRanges[i].Size = EFI_PAGES_TO_SIZE((UINTN)Descriptor->NumberOfPages);
            i++;
        }
    }
    ASSERT(i==SmmAmiBufferValidationLibNumberOfRoRanges);
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI SmmAmiBufferValidationLibReadyToLock (
    IN CONST EFI_GUID *Protocol, IN VOID *Interface, IN EFI_HANDLE Handle
){
    if ( (PcdGet32(AmiPcdSmmMemLibProperties) & AMI_BUFFER_VALIDATION_LIB_ALLOW_ACCESS_TO_OS_MEMORY) == 0 ){
        EFI_LEGACY_BIOS_PLATFORM_PROTOCOL *CsmPlatform;
        VOID *DummyPtr;
        UINTN DummyInt;
        UINTN MaxOpRomAddress;
        EFI_STATUS Status;

        // Get UEFI memory map and save runtime memory ranges
        SmmAmiBufferValidationLibGetMemMap();
        // Get memory attributes table and save read-only RT code regions
        SmmAmiBufferValidationLibGetMemoryAttributesTable();
        // Check if CSM is enabled.
        // If CSM is enabled we're allowing SMM communication with buffers below 1MB.
        // See AmiValidateMemoryBuffer for details.
        if ( !EFI_ERROR( gBS->LocateProtocol(&gEfiLegacyBiosPlatformProtocolGuid, NULL, (VOID**)&CsmPlatform) ) ){
            SmmAmiBufferValidationLibCsmEnabled = TRUE;
            Status = CsmPlatform->GetPlatformInfo(
                CsmPlatform, EfiGetPlatformEndOpromShadowAddr,
                &DummyPtr, &DummyInt, &MaxOpRomAddress, &DummyInt, 0, 0
            );
            if (!EFI_ERROR(Status) && MaxOpRomAddress > 0xE0000 && MaxOpRomAddress < 0x100000){
                MaxOpRomAddress++;
                SmmAmiBufferValidationLibCsmRanges[1].Address = MaxOpRomAddress;
                SmmAmiBufferValidationLibCsmRanges[1].Size = 0x100000 - MaxOpRomAddress;
            }
        }
    }
    // Get GCD memory map and save MMIO ranges
    SmmAmiBufferValidationLibGetGcdMap();

    SmmAmiBufferValidationLibSmmIsLocked = TRUE;
    return EFI_SUCCESS;
}

AMI_SMM_BUFFER_VALIDATION_PROTOCOL SmmAmiBufferValidationLibValidationProtocol = {
    SmmAmiBufferValidationLibAmiValidateMemoryBuffer,
    SmmAmiBufferValidationLibAmiValidateMmioBuffer,
    AmiValidateSmramBuffer
};

EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS Status;
    EFI_SMM_ACCESS2_PROTOCOL *SmmAccess;
    EFI_SMRAM_DESCRIPTOR *SmramRanges;
    UINTN Size;
    UINTN i;
    UINT32                                   DescriptorSize = sizeof(EFI_MEMORY_DESCRIPTOR);
    EDKII_PI_SMM_COMMUNICATION_REGION_TABLE  *PiSmmCommunicationRegionTable;
    EFI_MEMORY_DESCRIPTOR                    *Entry;
    EFI_PHYSICAL_ADDRESS                     SmmCommunicationBufferCompatibility = 0;

    // EDKII Compatibility.
    // EDKII modules use SMM communication buffer advertised using special configuration table attached to the UEFI system table.
    // Allocate the bBuffer and publish the table.

    Status = gBS->AllocatePool(
            EfiReservedMemoryType, sizeof(EDKII_PI_SMM_COMMUNICATION_REGION_TABLE) + DescriptorSize,
            (VOID **)&PiSmmCommunicationRegionTable
        );
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status = gBS->AllocatePages(
                AllocateAnyPages, EfiReservedMemoryType,
                4,
                &SmmCommunicationBufferCompatibility
            );
        ASSERT_EFI_ERROR(Status);
        if (!EFI_ERROR(Status)) {
            gBS->SetMem((VOID*)PiSmmCommunicationRegionTable, sizeof(EDKII_PI_SMM_COMMUNICATION_REGION_TABLE) + DescriptorSize, 0);

            PiSmmCommunicationRegionTable->Version         = EDKII_PI_SMM_COMMUNICATION_REGION_TABLE_VERSION;
            PiSmmCommunicationRegionTable->NumberOfEntries = 1;
            PiSmmCommunicationRegionTable->DescriptorSize  = DescriptorSize;

            Entry = (EFI_MEMORY_DESCRIPTOR *)(PiSmmCommunicationRegionTable + 1);
            Entry->Type          = EfiConventionalMemory;
            Entry->PhysicalStart = SmmCommunicationBufferCompatibility;
            Entry->NumberOfPages = 4;

            Status = gBS->InstallConfigurationTable (&gEdkiiPiSmmCommunicationRegionTableGuid, PiSmmCommunicationRegionTable);
            ASSERT_EFI_ERROR (Status);
        }
        else {
            gBS->FreePool(PiSmmCommunicationRegionTable);
        }
    }

    // Get SMRAM information
    Status = gBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
    if (EFI_ERROR(Status)) return Status;

    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    ASSERT (Status == EFI_BUFFER_TOO_SMALL);
    if (Status != EFI_BUFFER_TOO_SMALL) return Status;
    Status = gBS->AllocatePool (EfiBootServicesData, Size, (VOID **)&SmramRanges);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, SmramRanges);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)){
        gBS->FreePool(SmramRanges);
        return Status;
    }
    SmmAmiBufferValidationLibNumberOfSmramRanges = Size / sizeof (EFI_SMRAM_DESCRIPTOR);
    SmmAmiBufferValidationLibSmramRanges = AllocatePool (
            SmmAmiBufferValidationLibNumberOfSmramRanges * sizeof(SMM_AMI_BUFFER_VALIDATION_LIB_ADDRESS_RANGE)
    );
    ASSERT (SmmAmiBufferValidationLibSmramRanges != NULL);
    if (SmmAmiBufferValidationLibSmramRanges == NULL){
        SmmAmiBufferValidationLibNumberOfSmramRanges = 0;
        gBS->FreePool(SmramRanges);
        return EFI_OUT_OF_RESOURCES;
    }
    for(i=0; i<SmmAmiBufferValidationLibNumberOfSmramRanges; i++){
        SmmAmiBufferValidationLibSmramRanges[i].Address = SmramRanges[i].CpuStart;
        SmmAmiBufferValidationLibSmramRanges[i].Size = SmramRanges[i].PhysicalSize;
    }
    gBS->FreePool(SmramRanges);

    Status = gSmst->SmmRegisterProtocolNotify(
        &gEfiSmmReadyToLockProtocolGuid,
        SmmAmiBufferValidationLibReadyToLock,
        &SmmAmiBufferValidationLibReadyToLockRegistration
    );
    ASSERT_EFI_ERROR (Status);
    Status = gSmst->SmmInstallProtocolInterface(
        &SmmAmiBufferValidationLibValidationProtocolHandle,
        &gAmiSmmBufferValidationProtocolGuid,
        EFI_NATIVE_INTERFACE, &SmmAmiBufferValidationLibValidationProtocol
    );
    ASSERT_EFI_ERROR (Status);

    Status = SmmCoreAmiBufferValidationLibSmiHandlerConstructor();
    ASSERT_EFI_ERROR (Status);

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI SmmCoreAmiBufferValidationLibDestructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    if (SmmAmiBufferValidationLibSmramRanges != NULL) FreePool(SmmAmiBufferValidationLibSmramRanges);
    if (SmmAmiBufferValidationLibMemoryRanges != NULL) FreePool(SmmAmiBufferValidationLibMemoryRanges);
    if (SmmAmiBufferValidationLibMmioRanges != NULL) FreePool(SmmAmiBufferValidationLibMmioRanges);

    gSmst->SmmRegisterProtocolNotify(
        &gEfiSmmReadyToLockProtocolGuid, NULL, &SmmAmiBufferValidationLibReadyToLockRegistration
    );
    gSmst->SmmUninstallProtocolInterface(
        SmmAmiBufferValidationLibValidationProtocolHandle,
        &gAmiSmmBufferValidationProtocolGuid,
        &SmmAmiBufferValidationLibValidationProtocol
    );
    SmmCoreAmiBufferValidationLibSmiHandlerDestructor();

    return EFI_SUCCESS;
}
