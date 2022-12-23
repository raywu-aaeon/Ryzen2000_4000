//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file GnbDxe.c
    This file contains code for AMD NBIO (GNB) initialization
    in the DXE stage

**/

// Module specific Includes

#include <Token.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/S3SaveState.h>
#include <IndustryStandard/Pci.h>
#include <PciBus.h>

#include <AmiDxeLib.h>
#include <Gnb.h>
#include <GnbS3Save.h>
#include <AmiChipsetIoLib.h>
#include <Library/GnbPolicy.h>
#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
#include <Protocol/LegacyBiosExt.h>
#endif
//### RVA9 : AM4 ####if (defined(AmdCpmDisplayFeature_SUPPORT) && (AmdCpmDisplayFeature_SUPPORT != 0))
//### RVA9 : AM4 ####include <Library/Protocol/AmdCpmDisplayFeatureProtocol/AmdCpmDisplayFeatureProtocol.h>
//### RVA9 : AM4 ####endif
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>

// Constant Definition(s)

#if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))
VOID GnbCheckOprom (
    IN EFI_EVENT   Event,
    IN VOID        *Context
	);
#endif  // #if (defined(CSM_SUPPORT) && (CSM_SUPPORT != 0))

void SavePciRegisters(gPciRegistersSavelist *gPciRegistersSavelisttbl);
void SavePciIndexRegisters(gPciIndexRegistersSavelist *gPciIndexRegistersSavelisttbl);
void CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context);

// Global variable declarations
EFI_S3_SAVE_STATE_PROTOCOL          *gBootScriptSave;
EFI_EVENT           				gEvtBootScript;
VOID					STATIC		*VbiosRegistration = NULL;

// Portable Constants

// Function Prototypes

/**
    This function call back after EFI_PCI_IO_PROTOCOL is installed.

    @param Event
    @param Context

    @retval VOID

**/
VOID
GnbPciIoCallBack (
	IN EFI_EVENT Event,
	IN VOID *Context
	)
{
// AVA9 : due to AGESA V9 architecture change. So no AGESA ELINK.
// 		This is refer to GnbAgesaCustomizeDxe.c

#if GNB_IOAPIC_SUPPORT
    UINT64 					Address;
    UINT32 					VarTmp;
    UINT8  					IoApicId;

    // Get GNB IOAPIC.
    IoApicId = PcdGet8(AmiPcdGnbIoApicId);
    // Set GNB IOAPIC ID
    Address = GNB_IOAPIC_BASE_ADDRESS;
    VarTmp = 0;
    MmioWrite32 (Address, VarTmp);
    Address = GNB_IOAPIC_BASE_ADDRESS + 0x10;
    VarTmp = IoApicId << 24;
    MmioWrite32 (Address, VarTmp);
#endif // if GNB_IOAPIC_SUPPORT

	gBS->CloseEvent(Event);
}

/**
    Reserve the resource that NB needs.

        
    @param ImgHandle 
    @param CntrHandle 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS ReserveGnbResources(IN EFI_HANDLE	ImgHandle, IN EFI_HANDLE	CntrHandle)
{
	EFI_STATUS			  Status = EFI_SUCCESS;
	EFI_PHYSICAL_ADDRESS  PcieBaseAddr;
    DXE_SERVICES          *DxeSvcTbl;
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR     GcdDescriptor;  
    
    PcieBaseAddr = (UINT64)PcdGet64(PcdPciExpressBaseAddress);
    
    Status = LibGetDxeSvcTbl(&DxeSvcTbl);
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "LibGetDxeSvcTbl(&DxeSvcTbl)%r.\n", Status));

    if (!EFI_ERROR (Status)) {
      Status = DxeSvcTbl->AllocateMemorySpace (
                            EfiGcdAllocateAddress,
                            EfiGcdMemoryTypeMemoryMappedIo,
                            0,
                            PCIEX_LENGTH,
                            &PcieBaseAddr,
                            ImgHandle,
                            NULL
                            );

      
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "Fail to Allocate Memory Space for PciExpressBaseAddress.\n"));
      } else {
        Status = DxeSvcTbl->GetMemorySpaceDescriptor (PcieBaseAddr, &GcdDescriptor);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "Fail to get PCIEx GcdDescriptor at %x.\n", PcieBaseAddr));
        } else {
          DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, " GcdDescriptor.Attributes%x.\n", GcdDescriptor.Attributes));
          Status = DxeSvcTbl->SetMemorySpaceAttributes (
                                PcieBaseAddr,
                                PCIEX_LENGTH,
                                GcdDescriptor.Attributes | EFI_MEMORY_RUNTIME | EFI_MEMORY_UC
                                );
          if (EFI_ERROR (Status)) {
            DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "Unable to add EFI_MEMORY_RUNTIME attribute to PCIEx region %r.\n", Status));
          }
        }
      }
    }


    return Status;
}


/**
    This function is the entry point for this DXE. This function
    initializes the chipset NBIOS (GNB)

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

           
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
EFIAPI
GnbDxeInit (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable
)
{
    EFI_STATUS                          Status = EFI_SUCCESS;
    VOID								*Registration = NULL;

    InitAmiLib(ImageHandle, SystemTable);

    Status = gBS->LocateProtocol(
                            &gEfiS3SaveStateProtocolGuid,
                            NULL,
                            &gBootScriptSave);
    ASSERT_EFI_ERROR(Status);


	Status = CreateReadyToBootEvent(
		TPL_NOTIFY, // Due to SMM lock. we use AmiCspSmmBootScriptLib. This TPL is before CSP_DECONSTRUCT_SMM_COMMUNICATION_OPCODE.
		CallbackBootScript,
		NULL,
		&gEvtBootScript
	);
    ASSERT_EFI_ERROR(Status);

    Status = EfiNamedEventListen ( // EfiCreateProtocolNotifyEvent
				&gEfiPciIoProtocolGuid,
				TPL_CALLBACK,
				GnbPciIoCallBack,
				NULL,
				&Registration
				);
    ASSERT_EFI_ERROR (Status);

    ReserveGnbResources(ImageHandle, SystemTable);
	ASSERT_EFI_ERROR(Status);

#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
	//
	// Call back when CSM dispatch VBIOS.
	//
	Status = EfiNamedEventListen (
				&gOpromStartEndProtocolGuid,
				TPL_NOTIFY,
				GnbCheckOprom,
				NULL,
				&VbiosRegistration
				);
	ASSERT_EFI_ERROR (Status);
#endif

    return EFI_SUCCESS;
}

#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
/**
    This callback function is called before/after processing all
    PCI optonal ROM.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID GnbCheckOprom (
    IN EFI_EVENT   Event,
    IN VOID        *Context
	)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    AMD_PBS_SETUP_OPTION      	AmdPbsSetup;
    CSM_PLATFORM_POLICY_DATA    *Data = NULL;
    UINTN                       BufferSize = sizeof(EFI_HANDLE);
    EFI_HANDLE                  Handle;
    SETUP_DATA                  *gSetupData;
    EFI_GUID                    gSetupGuid = SETUP_GUID;
    UINTN                       Size = 0;

    Status = gBS->LocateHandle( ByRegisterNotify, \
                                NULL, \
                                VbiosRegistration, \
                                &BufferSize, \
                                &Handle );
    if (EFI_ERROR(Status)) return;

    // Locate CSM Platform Policy data
    Status = gBS->HandleProtocol( Handle, &gOpromStartEndProtocolGuid, &Data );

    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return;

    if (Data == NULL) return;
    if (Data->PciIo == NULL) return;
    //###if (Data->PciHandle == NULL) return;

    Status = GetAmdPbsConfiguration(&AmdPbsSetup);
    if (!EFI_ERROR(Status)) {
        // Legacy video only
        Status = GetVariable2(L"Setup", &gSetupGuid, &gSetupData, &Size);
	    if(!EFI_ERROR(Status) && gSetupData->VideoOpRom == 2) {
    	    //
    	    // The dGPU bridge is prior to IGPU.
    	    //	1. HybridGraphics ==> IGD first
    	    //  2. Primary video select to IGD ==> disable dGPU VBIOS.
    	    //
    	    if (AmdPbsSetup.SpecialVgaFeature == 4 || AmdPbsSetup.PrimaryVideoAdaptor == 1) {
    		    PCI_TYPE00				PciConfig;
    		    EFI_PCI_IO_PROTOCOL    	*PciIo = Data->PciIo;

			    Status = PciIo->Pci.Read ( PciIo,
				    					EfiPciIoWidthUint8,
				    					0,
				    					sizeof (PCI_TYPE00),
				    					&PciConfig
				    					);
			    if (IS_CLASS1 (&PciConfig, PCI_CLASS_DISPLAY) || IS_CLASS2 (&PciConfig, PCI_CLASS_OLD,  PCI_CLASS_OLD_VGA)) {
				    //  if IGD
	                PCI_DEV_INFO    *Dev;
	                Dev = (PCI_DEV_INFO*)PciIo;
	                if((Dev->ParentBrg->Address.Addr.Bus == 0)
	                    && (Dev->ParentBrg->Address.Addr.Device == 8)
	                    && (Dev->ParentBrg->Address.Addr.Function == 1)
	                    && (Dev->Address.Addr.Device == 0)
	                    && (Dev->Address.Addr.Function == 0)){
	                           Data->ExecuteThisRom = TRUE;
	                 } else {
	                           Data->ExecuteThisRom = FALSE;
				     }
                     DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "\n Gnb:ExecuteThisRom(%x).\n",Data->ExecuteThisRom));  
			    }// end of if IS_CLASS1

    	   } // end of AmdPbsSetup
	    }
    } // end of status
}
#endif


//////////////////////////////S3 PCI Context Starts /////////////////////////////////////////
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_GNB[] = {
	0x0C,  EfiBootScriptWidthUint32,
	GNB_D0F0_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xA8,  EfiBootScriptWidthUint32,
	0xAC,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_IGD[] = {
	0x4C,  EfiBootScriptWidthUint32,
	IGD_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xA0,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_IGDHDA[] = {
	0x4C,  EfiBootScriptWidthUint32,
	IGD_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xFF, 0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_DGPU[] = {
	0x4C,  EfiBootScriptWidthUint32,
	IGD_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_DCARD[] = {
	0x2C,  EfiBootScriptWidthUint32,
	0x2C,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_MXMCARD[] = {
	0x19,  EfiBootScriptWidthUint8,
	0x1A,  EfiBootScriptWidthUint8,
	0xFF,  0xFF
};
BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_DGPUHDA[] = {
	0x4C,  EfiBootScriptWidthUint32,
	IGD_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gPciGNBRegistersSave_ACG[] = {
	0x4C,  EfiBootScriptWidthUint32,
	IGD_SSID_MIRROR,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gInternalBridgeA[] = {
	0x18,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gInternalBridgeB[] = {
	0x18,  EfiBootScriptWidthUint32,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gRegistersSaveIommu[] = {
	0x4,  EfiBootScriptWidthUint8,
	0x3C,  EfiBootScriptWidthUint8,
	0xFF,  0xFF
};

BOOT_SCRIPT_PCI_INDEX_REGISTER_SAVE gNBMiscellaneousRegsSave[] = {
	{0xFF, 0xFF, 0xFF},
};

BOOT_SCRIPT_PCI_INDEX_REGISTER_SAVE gGNBIndexRegsSave[] = {
    {GNB_D0F0_WRAPPER_INDEX, GNB_D0F0_WRAPPER_INDEX_SSID, EfiBootScriptWidthUint32},
    {0xFF, 0xFF, 0xFF},
};

/**
    This function saves the boot script

        
    @param Event 
    @param Context 

         
    @retval VOID

**/


VOID CallbackBootScript(IN EFI_EVENT Event, IN VOID *Context)
{
    static BOOLEAN BootScriptSaved = FALSE;

    gPciIndexRegistersSavelist gPciIndexRegistersSavelisttbl[] = 
    {
        {gGNBIndexRegsSave, (UINT64)GNB_PCI_CFG_ADDRESS(GNB_BUS, GNB_DEV, GNB_FUN, 0)},
        {(BOOT_SCRIPT_PCI_INDEX_REGISTER_SAVE *)0xFF, 0xFF},
    };

    gPciRegistersSavelist gPciGNBRegistersSavelisttbl[] = 
    {
    	{gInternalBridgeA,      (UINT64)GNB_PCI_CFG_ADDRESS(0, 8, 1, 0)},
		//{gInternalBridgeB,      (UINT64)GNB_PCI_CFG_ADDRESS(0, 8, 2, 0)},
		{gRegistersSaveIommu,      (UINT64)GNB_PCI_CFG_ADDRESS(0, 0, 2, 0)},
        {(BOOT_SCRIPT_PCI_REGISTER_SAVE *)0xFF, 0xFF},
    };
    
    if (BootScriptSaved) return;

    //save the define pcireg
    SavePciIndexRegisters(gPciIndexRegistersSavelisttbl);
    SavePciRegisters(gPciGNBRegistersSavelisttbl);

    BootScriptSaved = TRUE;

}
/**
    Save the gPciRegisterSaveListtbl pci devices save the reg
    for S3 resume wirte back.

        
    @param gPciRegistersSavelist *gPciRegistersSavelisttbl

         
    @retval VOID

**/

VOID
SavePciRegisters(IN gPciRegistersSavelist *gPciRegistersSavelisttbl)
{
    UINT8                           i, j;
    UINT8                           Buffer8;
    UINT32                          Buffer32;
    UINT16                          Buffer16;
    UINT64                          Address64;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
    EFI_STATUS                      Status;

    Status = gBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
    if(EFI_ERROR(Status))
        return;

    j = 0;
    while(gPciRegistersSavelisttbl[j].DevAddr != 0xFF)
    {
        i = 0;
        while(gPciRegistersSavelisttbl[j].gPciRegisters[i].Address != 0xFF)
        {
            Address64 = (UINT64)(gPciRegistersSavelisttbl[j].DevAddr +
                                 gPciRegistersSavelisttbl[j].gPciRegisters[i].Address);

            switch(gPciRegistersSavelisttbl[j].gPciRegisters[i].Width)
            {
                case EfiBootScriptWidthUint8:
                    PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                              gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                              Address64,
                                              1,
                                              &Buffer8);
                    //LibNbWritePci8_S3(gBootScriptSave, Address64, Buffer8);
                    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint8,
                                                Address64,
                                                1,
                                                &Buffer8 );

                    break;
                case EfiBootScriptWidthUint16:
                    PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                              gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                              Address64,
                                              1,
                                              &Buffer16);
                    //LibNbWritePci16_S3(gBootScriptSave, Address64, Buffer16);
                    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint16,
                                                Address64,
                                                1,
                                                &Buffer16 );
                    break;
                case EfiBootScriptWidthUint32:
                    PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                              gPciRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                              Address64,
                                              1,
                                              &Buffer32);
                    //LibNbWritePci32_S3(gBootScriptSave, Address64, Buffer32);
                    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32,
                                                Address64,
                                                1,
                                                &Buffer32 );
                    break;
            }   // end of switch(gPciRegistersSavelisttbl[j].gPciRegisters[i].Width)
            i++;
        }   // end of while(gPciRegistersSavelisttbl[j].gPciRegisters[i].Address != 0xFF)
        j++;
    }   // end of while(gPciRegistersSavelisttbl[j].DevAddr != 0xFF)
}

/**
    Save the gPciIndexRegisterSaveListtbl pci devices save the reg
    for S3 resume wirte back.

        
    @param gPciIndexRegistersSavelist *gPciIndexRegistersSavelisttbl

         
    @retval VOID

**/

VOID
SavePciIndexRegisters(IN gPciIndexRegistersSavelist *gPciIndexRegistersSavelisttbl)
{
    UINT8                           i, j;
    UINT32                          Buffer32;
    UINT64                          Address64;	
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
    EFI_STATUS                      Status;

    Status = gBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
    if(EFI_ERROR(Status))
        return;

    j = 0;
    while(gPciIndexRegistersSavelisttbl[j].DevAddr != 0xFF)
    {
        i = 0;
        while(gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index != 0xFF)
        {
            Address64 = (UINT64)(gPciIndexRegistersSavelisttbl[j].DevAddr +
                                 gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index);
            if((gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x60) ||
               (gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x94))
            {
                Buffer32 = (UINT32)gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].IndexData;
                if (gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x60)
                    Buffer32 |= 0x80;               // Set write enable bit
                else if (gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x94)
                    Buffer32 |= 0x100;

                // Trigger Index register
                WRITE_PCI32(AMD_BUS0, AMD_RC_DEV,AMD_RC_FUN,Address64, Buffer32);
                    
                //LibNbWritePci32_S3(gBootScriptSave, Address64, Buffer32);   // Write index register
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32,
                                                Address64,
                                                1,
                                                &Buffer32 );
                Address64 += 0x04;              // Prepare to read into index data register

                PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                          gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                          Address64,
                                          1,
                                          &Buffer32);

//              LibNbWritePci32_S3(gBootScriptSave, Address64, Buffer32);   // Write index data register

                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32,
                                                Address64,
                                                1,
                                                &Buffer32 );
                Address64 -= 0x04;              // Prepare to disable write enable bit

                PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                          gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                          Address64,
                                          1,
                                          &Buffer32);
                if(gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x60)
                    Buffer32 &= 0xFFFFFF7F;         // Clear write enable bit
                else if(gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0x94)
                    Buffer32 &= 0xFFFFFEFF;
                PciRootBridgeIo->Pci.Write(PciRootBridgeIo,
                                           gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                           Address64,
                                           1,
                                           &Buffer32);
            }
            else if(gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Index == 0xE0)
            {
                Buffer32 = (UINT32)gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].IndexData;
 
                // Trigger Index register
                WRITE_PCI32(AMD_BUS0, AMD_RC_DEV,AMD_RC_FUN,Address64, Buffer32);

                    //LibNbWritePci32_S3(gBootScriptSave, Address64, Buffer32);   // Write index register
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32,
                                                Address64,
                                                1,
                                                &Buffer32 );
                Address64 += 0x04;              // Prepare to read into index data register

                PciRootBridgeIo->Pci.Read(PciRootBridgeIo,
                                          gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Width,
                                          Address64,
                                          1,
                                          &Buffer32);

               // LibNbWritePci32_S3(gBootScriptSave, Address64, Buffer32);   // Write index data register
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                                EfiPciWidthUint32,
                                                Address64,
                                                1,
                                                &Buffer32 );
            }
            i++;
        }   // end of while(gPciIndexRegistersSavelisttbl[j].gPciRegisters[i].Address != 0xFF)
        j++;
    }   // end of while(gPciIndexRegistersSavelisttbl[j].DevAddr != 0xFF)
}

