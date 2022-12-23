//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file GnbAmiNbioDxeLib.c
    This file contains code for GnbAmiNbioDxeLib.c
    in the DXE stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>

#include <Token.h>
// AMI Compatibility Header.
#include <Protocol/AmiBoardInfo2.h>
#include <Library/GnbPolicy.h>
#include <AmiHobs.h> //### Remove AmiCompatibilityPkg later. It is limited by CPUINFO_HOB

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    Update the correct GNB IO APCI ID to Route table for Mp table create.

    @param ApicId
    @param ApicAddress

    @retval VOID

**/
VOID
UpdateGnbIoApicIdToRouteTable(
    IN UINT8   ApicId,
    IN UINT32  ApicAddress
)
{
//### <AAV> : make a generic routine later.
#if defined AmiBoardInfo_SUPPORT &&  AmiBoardInfo_SUPPORT == 1
    AMI_BOARD_INFO2_PROTOCOL	*AmiBoardInfo2Protocol = NULL;
    AMI_SDL_PCI_DEV_INFO   		*RouteTable = NULL;
    UINT8           			BuildIoApicId = 1;
    UINT32           			i, j, Count;
    EFI_STATUS              	Status;

    Status = gBS->LocateProtocol(&gAmiBoardInfo2ProtocolGuid, NULL, (VOID**)&AmiBoardInfo2Protocol);
    if (!EFI_ERROR(Status))
    {
        Count = AmiBoardInfo2Protocol->ApicBrdData->IoApicCount;

        // Update Correct APICID to AMI_SDL_IO_APIC_INFO
        //-----------------
        for(i = 0; i < Count; i++) {
        	// Find the SB - IOAPIC
            if (AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicAddress == ApicAddress) {
                BuildIoApicId = AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicIdBuild;
                AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicIdBuild = ApicId;
            }
        } 

        Count = (UINT32)AmiBoardInfo2Protocol->PciBrdData->PciDevCount;
   
        RouteTable = AmiBoardInfo2Protocol->PciBrdData->PciDevices ;

        // Update Correct APICID to PCI RouteTable
        for(i = 0; i < Count; i++)
        {
            for(j = 0; j < 4; j++)
            {
			// SB IoApic: 0~23
			// GNB IoApic: 24~55
                if( RouteTable[i].ApicIrq[j].IoApicId == BuildIoApicId && (
                		(RouteTable[i].ApicIrq[j].IoApicItin >= 24) && (RouteTable[i].ApicIrq[j].IoApicItin < 56))){
                    RouteTable[i].ApicIrq[j].IoApicId = ApicId;
                }
            }   
        }
        

     }
#endif
}


/**
    This function is the constructor for AmdNbioBaseXXDxeEntry driver.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
GnbAmiNbioDxeConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    CPUINFO_HOB             *CpuInfoHob;
    UINT8                   GnbIoApicId;
    UINT8                   StartLocalApicId;
    EFI_GUID                CpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;

    GNB_SETUP_DATA      GnbSetupData;

    GetGnbSetupData(gRT, &GnbSetupData, FALSE);

#if GNB_IOAPIC_SUPPORT
    // Put the I/O APIC in Virtual wire mode

    // CHIPSET PROGRAMMING TO ENABLE IOAPIC GOES HERE

     CpuInfoHob = (CPUINFO_HOB*)GetFirstGuidHob(&CpuInfoHobGuid);

    if(CpuInfoHob != NULL) {
      // For systems with >= 16 APICs, put the IO-APICs at 0..n and
      // put the local-APICs at m..z
      // For systems with < 16 APICs, put the Local-APICs at 0..n and
      // put the IO-APICs at (n + 1)..z
      // This is needed because many IO-APIC devices only have 4 bits
      // for their APIC id and therefore must reside at 0..15
        //check the local APIC ID
        StartLocalApicId = CpuInfoHob->Cpuinfo->ApicId;
        if (StartLocalApicId >= 16 )
        {
            GnbIoApicId = 1;
        } else {
            GnbIoApicId = CpuInfoHob->CpuCount+2;
        }
    } else {
        GnbIoApicId = NCPU + 2;
    }

    // Set GNB IOAPIC.
    PcdSet8S(AmiPcdGnbIoApicId, GnbIoApicId);
    //Update the ApicRoutTable and ApicInfoTable
    UpdateGnbIoApicIdToRouteTable(GnbIoApicId, GNB_IOAPIC_BASE_ADDRESS);

    //
    // AVA9 :
    //		This is part of GnbAgesaHookInitLate.
    //
    PcdSet64S(PcdCfgGnbIoapicAddress, GNB_IOAPIC_BASE_ADDRESS);
    PcdSet8S(PcdCfgGnbIoapicId, GnbIoApicId);

#endif // if GNB_IOAPIC_SUPPORT

#if GNB_IOMMU_SUPPORT

	//PcdSetBoolS(PcdCfgIommuSupport, GnbSetupData.IommuSupport);
	PcdSet8S(PcdCfgFchIoapicId, GnbIoApicId - 1);

	// Refer to GnbAgesaHookInitEnv
    if (PcdGetBool (PcdCfgIommuSupport))
    {
        // Wirte IOMMU base address to Bus0, Device 0, Function 2, Register 0x48
        PciWrite32 (PCI_LIB_ADDRESS(0, 0, 2, 0x44), GNB_IOMMU_BASE_ADDRESS);
        // Write 1 to IommuEnable of Bus0, Device 0, Function 2, Register 0x44
        PciOr32 (PCI_LIB_ADDRESS(0, 0, 2, 0x44), BIT0);
    }

#else
    //PcdSetBoolS(PcdCfgIommuSupport, FALSE);
#endif

    //PcdSetBoolS(PcdCfgGnbRemoteDisplaySupport, GnbSetupData.GnbRemoteDisplaySupport); // GnbAgesaHookInitEnv


    return Status;
}

