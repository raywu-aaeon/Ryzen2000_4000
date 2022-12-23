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

/** @file LegacyRegion.c
    Legacy Region functions implementation

**/

//#include <efi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol/LegacyRegion.h>
#include <Protocol/LegacyRegion2.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/BootScriptSave.h>
#include <Protocol/Cpu.h>

EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

EFI_EVENT   gEvtBootScript;
EFI_CPU_ARCH_PROTOCOL   Cpu;
EFI_CPU_ARCH_PROTOCOL   *pCpu;

/**
    Saves the PAM registers to Boot Script

        
    @param Event 
    @param Context 
         
    @retval VOID

**/
VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_S3_SAVE_STATE_PROTOCOL    *BootScriptSave;
    EFI_STATUS  Status;


    Status = pBS->LocateProtocol(
        &gEfiBootScriptSaveProtocolGuid,
        NULL,
        &BootScriptSave
        );
    if (EFI_ERROR(Status)) return;

    NbPamWriteBootScript(BootScriptSave);
	
    //
    //Kill the Event
    //
    pBS->CloseEvent(Event);

}


/**
    Program 0xc0000 - 0xfffff regions to Lock/Unlock.

    @param StartAddress 
    @param Length 
    @param Setting 
    @param Granularity 

    @retval EFI_STATUS Status of the operation

    @note  Here is the control flow of this function:
              1. Search the structure for the first entry matching
                  the StartAddress.
              2. If not found, return EFI_INVALID_PARAMETER.
              3. Find the last entry in structure for the region to program,
                  by adding the lengths of the entries.
              4. If not found, return EFI_INVALID_PARAMETER.
              5. Read/Write each register for the entry to set region.
              6. Return the Granularity for the region.
**/

EFI_STATUS ProgramPamRegisters(
    UINT32  StartAddress,
    UINT32  Length,
    UINT8   Setting,
    UINT32  *Granularity)
{
    EFI_STATUS      Status;
    UINT64          Attributes;

    Status = NbProgramPamRegisters (pBS, pRS, StartAddress, Length, Setting, Granularity);
    if (Status != EFI_SUCCESS) return Status;

//  Program the MTRRs
    switch (Setting) {

        case LEGACY_REGION_LOCK:
            Attributes = EFI_MEMORY_WP;
            break;

        case LEGACY_REGION_BOOT_LOCK:
            Attributes = EFI_MEMORY_WP;
            break;

        case LEGACY_REGION_UNLOCK:
            Attributes = EFI_MEMORY_WT;
            break;

        default:
        Attributes = EFI_MEMORY_UC;

    }

//  Status=DxeSvcTbl->SetMemorySpaceAttributes(StartAddress,Length,Attributes);
    pCpu->SetMemoryAttributes(pCpu, StartAddress, Length, Attributes);

    return Status;
}

/**
    Program chipset to allow decoding of 0xc0000 - 0xfffff.

        
    @param This 
    @param Start 
    @param Length 
    @param On 

         
    @retval EFI_STATUS Status of the operation

**/
EFI_STATUS EFIAPI Decode(
    IN EFI_LEGACY_REGION_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    IN BOOLEAN                      *On
)
{
    UINT32  Granularity;
    if (*On) {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, &Granularity);
    } else {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_DECODE_ROM, &Granularity);
    }
}

/**
    Program chipset to allow decoding of 0xc0000 - 0xfffff.

        
    @param This 
    @param Start 
    @param Length 
    @param Granularity 
    @param On 

         
    @retval EFI_STATUS Status of the operation

**/
EFI_STATUS EFIAPI LegacyRegionDecode(
    IN EFI_LEGACY_REGION2_PROTOCOL   *This,
    IN UINT32                       Start,
    IN UINT32                       Length,
    OUT UINT32                      *Granularity,
    IN BOOLEAN                      *On
)
{
    if (*On) {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
    } else {
        return ProgramPamRegisters(Start, Length, LEGACY_REGION_DECODE_ROM, Granularity);
    }
}

/**
    To disallow writes to memory 0xc0000 - 0xfffff.

        
    @param This 
    @param Start 
    @param Length 
    @param Granularity OPTIONAL

         
    @retval EFI_STATUS Status of the operation

**/
EFI_STATUS EFIAPI Lock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_LOCK, Granularity);
}

EFI_STATUS EFIAPI LegacyRegionLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_LOCK, Granularity);
}

/**
    To permanently disallow writes to memory 0xc0000 - 0xffff.

        
    @param This 
    @param Start 
    @param Length 
    @param Granularity OPTIONAL

         
    @retval EFI_STATUS Status of the operation

**/
EFI_STATUS EFIAPI BootLock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
  if ((Start < 0xC0000) || ((Start + Length - 1) > 0xFFFFF)) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_UNSUPPORTED;
}

EFI_STATUS EFIAPI LegacyRegionBootLock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
  if ((Start < 0xC0000) || ((Start + Length - 1) > 0xFFFFF)) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_UNSUPPORTED;
}

/**
    To allow read/write of memory 0xc0000-0xfffff.

        
    @param This 
    @param Start 
    @param Length 
    @param Granularity OPTIONAL

         
    @retval EFI_STATUS Status of the operation

**/
EFI_STATUS EFIAPI Unlock(
    IN  EFI_LEGACY_REGION_PROTOCOL  *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
}

EFI_STATUS EFIAPI LegacyRegionUnlock(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    IN  UINT32                      Start,
    IN  UINT32                      Length,
    OUT UINT32                      *Granularity  OPTIONAL
)
{
    return ProgramPamRegisters(Start, Length, LEGACY_REGION_UNLOCK, Granularity);
}

/**
    This function is used to discover the granularity of the attributes
    for the memory in the legacy region. Each attribute may have a different
    granularity and the granularity may not be the same for all memory ranges
    in the legacy region.  

        
    @param This 
        --  Indicates the EFI_LEGACY_REGION_PROTOCOL instance.

         
    @retval EFI_UNSUPPORTED This function is not supported
    @retval EFI_SUCCESS The following information structure is returned:
        OUT UINT32                          *DescriptorCount
        --  The number of region descriptor entries returned in the Descriptor
        buffer. See EFI_LEGACY_REGION_DESCRIPTOR definition for reference.
        OUT EFI_LEGACY_REGION_DESCRIPTOR    **Descriptor
        --  A pointer to a pointer used to return a buffer where the legacy
        region information is deposited. This buffer will contain a list
        of DescriptorCount number of region descriptors. This function will
        provide the memory for the buffer.

**/
EFI_STATUS EFIAPI GetLegacyRegionInfo(
    IN  EFI_LEGACY_REGION2_PROTOCOL *This,
    OUT UINT32                      *DescriptorCount,
    OUT EFI_LEGACY_REGION_DESCRIPTOR    **Descriptor
)
{
    return EFI_UNSUPPORTED; // Note: to support this function there is a need
                            // to update NB template.
}

EFI_LEGACY_REGION_PROTOCOL gLegacyRegionProtocol =
{
    Decode, Lock, BootLock, Unlock
};

EFI_LEGACY_REGION2_PROTOCOL gLegacyRegion2Protocol =
{
    LegacyRegionDecode, LegacyRegionLock,
    LegacyRegionBootLock, LegacyRegionUnlock,
    GetLegacyRegionInfo
};


/**
    Install the legacy region protocol.

        
    @param ImageHandle 
    @param SystemTable 

         
    @retval EFI_STATUS Status of the operation

    @note  
  Here is the control flow of this function:
  1. Get root bridge io protocol.
  2. Install legacy region protocol.

**/
EFI_STATUS EFIAPI InitializeLegacyRegion(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status;

    InitAmiLib(ImageHandle, SystemTable);

    pCpu = &Cpu;
    Status = pBS->LocateProtocol(&gEfiCpuArchProtocolGuid, NULL, &pCpu);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    Status = pBS->LocateProtocol(
            &gEfiPciRootBridgeIoProtocolGuid,
            NULL,
            &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    //Create event for boot script
    Status = CreateReadyToBootEvent(
        TPL_NOTIFY,
        CallbackBootScript,
        NULL,
        &gEvtBootScript
    );
    ASSERT_EFI_ERROR(Status);

    return pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiLegacyRegionProtocolGuid, &gLegacyRegionProtocol,
        &gEfiLegacyRegion2ProtocolGuid, &gLegacyRegion2Protocol,
        NULL
        );
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
