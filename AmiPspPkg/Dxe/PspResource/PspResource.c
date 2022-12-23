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
 
//**********************************************************************
//
/** @file PspResource.c
    PSP Resource driver   

**/

#include "Token.h"
#include <Pci.h>
#include <AmiDxeLib.h>
#include <AcpiRes.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspBaseLibV1.h>
#include <Library/AmdHeapLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/FabricResourceReportToGcdLib.h>

#define ZEN_MAX_SOCKET              2
#define ZEN_MAX_DIE_PER_SOCKET      4

EFI_EVENT   ReadyToBootEvent;

EFI_STATUS
EFIAPI
PspResourceEntryPoint (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
);

CSP_RES_ITEM AmdNonPciReserved[] = { 
    {0xFD800000, 0x800000, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME)},
    {0,                 0, EfiGcdMemoryTypeMemoryMappedIo, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME)}    // It might got second mmio for die0
}; // Amd non-PCI resource table

UINTN   AmdNonPciResCount = sizeof(AmdNonPciReserved) / sizeof(CSP_RES_ITEM);

/**
    This function is to reserve PSP BAR3 for family 15h.

    @param Event 
    @param Context 

    @retval VOID

**/
VOID    
AmiPspResourceReserved15h(
  IN    EFI_EVENT   Event, 
  IN    VOID        *Context
)
{    
    EFI_STATUS                  Status;
    UINT32                      PspMmioBase;
    EFI_PHYSICAL_ADDRESS        Dsdtaddr = 0;

    if (GetPspMmioBase (&PspMmioBase))
    {
        Status = LibGetDsdt(&Dsdtaddr, EFI_ACPI_TABLE_VERSION_ALL);
        if (!EFI_ERROR(Status)) {
            Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "PSPA", PspMmioBase);
            DEBUG ((DEBUG_INFO, " BR PspResource : UpdateAslNameObject PSPA status = %r\n", Status));
            Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "LENA", 0x100000);
            DEBUG ((DEBUG_INFO, " BR PspResource : UpdateAslNameObject ALEN status = %r\n", Status));
            Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "PSPB", 0);
            DEBUG ((DEBUG_INFO, " BR PspResource : UpdateAslNameObject PSPB status = %r\n", Status));
            Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "LENB", 0);
            DEBUG ((DEBUG_INFO, " BR PspResource : UpdateAslNameObject LENB status = %r\n", Status));
        }
        else {
            DEBUG ((DEBUG_ERROR, "BR PspAslNameUpdate: LibGetDsdt - %r \n", Status));
        }
    }
    
    pBS->CloseEvent(Event);
}

/**
    This function is to reserve AMD non pci MMIO in OS for family 17h.

    @param Event 
    @param Context 

    @retval VOID

**/
VOID    
ReserveAmdNonPciMmioAsl(
  IN    EFI_EVENT   Event, 
  IN    VOID        *Context
)
{    
    EFI_STATUS                  Status;
    EFI_PHYSICAL_ADDRESS        Dsdtaddr = 0;

    Status = LibGetDsdt(&Dsdtaddr, EFI_ACPI_TABLE_VERSION_ALL);
    if (!EFI_ERROR(Status)) {
        Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "PSPA", (UINT32)AmdNonPciReserved[0].ResBase);
        DEBUG ((DEBUG_INFO, " SM or RV PspResource : UpdateAslNameObject PSPA status = %r\n", Status));
        Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "LENA", (UINT32)AmdNonPciReserved[0].ResLength);
        DEBUG ((DEBUG_INFO, " SM or RV PspResource : UpdateAslNameObject LENA status = %r\n", Status));

        Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "PSPB", (UINT32)AmdNonPciReserved[1].ResBase);
        DEBUG ((DEBUG_INFO, " SM or RV PspResource : UpdateAslNameObject PSPB status = %r\n", Status));
        Status = UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "LENB", (UINT32)AmdNonPciReserved[1].ResLength);
        DEBUG ((DEBUG_INFO, " SM or RV PspResource : UpdateAslNameObject LENB status = %r\n", Status));

    }else {
        DEBUG ((DEBUG_ERROR, " SM or RV PspAslNameUpdate: LibGetDsdt - %r \n", Status));
    }

    pBS->CloseEvent(Event);
}

/**
 *
 * Report AMD Non-Pci MMIO regions to GCD
 *
 *    @param ImageHandle 
 */
EFI_STATUS 
ReserveAmdNonPciMmioForPciBus(
  IN    EFI_HANDLE          ImageHandle
){
    UINT8                     i;
    UINT8                     j;
    UINT8                     TempSocket;
    UINT8                     TempDie;
    EFI_STATUS                Status = EFI_SUCCESS;
    LOCATE_HEAP_PTR           LocateHeapParams;
    FABRIC_MMIO_MANAGER      *FabricMmioManager;

    // Find MMIO manager in heap
    LocateHeapParams.BufferHandle = AMD_MMIO_MANAGER;
    if (HeapLocateBuffer (&LocateHeapParams, NULL) != AGESA_SUCCESS) {
      ASSERT(FALSE);
    }
    FabricMmioManager = (FABRIC_MMIO_MANAGER *) LocateHeapParams.BufferPtr;

    if (FabricMmioManager != NULL) {
        for (i = 0; i < ZEN_MAX_SOCKET; i++) {
            for (j = 0; j < ZEN_MAX_DIE_PER_SOCKET; j++) {
                if (FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci != 0) {
                    AmdNonPciReserved[0].ResBase =  FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci;
                    AmdNonPciReserved[0].ResLength = FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci;
                }
            }
        }
        DEBUG((DEBUG_INFO, "AmdNonPciReserved[0].ResBase %X\n", AmdNonPciReserved[0].ResBase));
        DEBUG((DEBUG_INFO, "AmdNonPciReserved[0].ResLength %X\n", AmdNonPciReserved[0].ResLength));

        // Check Die0's 2nd MMIO
        if (FabricMmioManager->PrimaryRbHas2ndMmioBelow4G) {
            TempSocket = (FabricMmioManager->PrimaryRb2ndMmioPairBelow4G >> 4) & 0xF;
            TempDie = FabricMmioManager->PrimaryRb2ndMmioPairBelow4G & 0xF;
            DEBUG((DEBUG_INFO, "Die0Has2ndMmioBelow4G TempSocket = %X TempDie = %X\n", TempSocket, TempDie));
            if (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempDie].SizeNonPci != 0) {
                //Update table
                AmdNonPciReserved[1].ResBase =  FabricMmioManager->MmioRegionBelow4G[TempSocket][TempDie].BaseNonPci;
                AmdNonPciReserved[1].ResLength = FabricMmioManager->MmioRegionBelow4G[TempSocket][TempDie].SizeNonPci;
                DEBUG((DEBUG_INFO, "AmdNonPciReserved[1].ResBase %X\n", AmdNonPciReserved[1].ResBase));
                DEBUG((DEBUG_INFO, "AmdNonPciReserved[1].ResLength %X\n", AmdNonPciReserved[1].ResLength));
            }
        }
    }

    if (AmdNonPciReserved[1].ResLength == 0)
        AmdNonPciResCount -= 1;

    Status = LibAllocCspResource (AmdNonPciReserved, AmdNonPciResCount, ImageHandle, NULL);
    DEBUG((DEBUG_INFO, "LibAllocCspResource AmdNonPciReserved status = %r\n", Status));

    return Status;
}


/**
    PSP resource driver entry point

               
    @param ImageHandle 
    @param SystemTable 

    @retval EFI_STATUS Return the EFI  Status

**/

EFI_STATUS
EFIAPI
PspResourceEntryPoint (
  IN    EFI_HANDLE          ImageHandle,
  IN    EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS              Status = EFI_SUCCESS;
    SOC_ID_STRUCT           SocId;
    EFI_EVENT               PspAslNameEvent = NULL;
    VOID                    *PspAslNameRegister = NULL;
    UINT32                  PspMmioBase = NULL;
    EFI_PHYSICAL_ADDRESS    Dsdtaddr = 0;

    InitAmiLib(ImageHandle, SystemTable);
    
    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    if (!SocHardwareIdentificationCheck(&SocId))
    {
        Status = ReserveAmdNonPciMmioForPciBus(ImageHandle);
        DEBUG((DEBUG_INFO, "AMI report AMD Non-Pci MMIO region GCD %r\n", Status));
        ASSERT_EFI_ERROR(Status);
        Status = CreateReadyToBootEvent(TPL_NOTIFY, ReserveAmdNonPciMmioAsl, NULL, &ReadyToBootEvent);
    }else{
        // Family 15h needs to reserve PSP BAR 3
        Status = CreateReadyToBootEvent(TPL_NOTIFY, AmiPspResourceReserved15h, NULL, &ReadyToBootEvent);
    }

    return Status;
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
