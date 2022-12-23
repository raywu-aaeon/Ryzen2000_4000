//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file GnbPciBoardDxeInitLib.c

**/
//**********************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <PciBus.h>
#include <PciHostBridge.h>
#include <Setup.h>

#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Protocol/AmiBoardInitPolicy.h>
#include <Protocol/LegacyBiosExt.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmiPciBusLib.h>
#include <Library/AmiSdlLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/GnbGuid.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/PciLib.h>

#define ATI_VGA_VID   0x1002

typedef struct {
	PCI_DEV_INFO		*Dev;
	UINT16          	DeviceId;
	PCI_DATA_STRUCTURE	*Pcir;
}DGPU_BACK_UP;

/**
    This function decide to launch or not UEFI compatible
    Option ROM.

    @param Dev PCI Device.

    @retval BOOLEAN
        TRUE             		Launch UEFI Option ROM
        FALSE                   NOT Launch UEFI Option ROM
**/
BOOLEAN GnbIsUefiOpromPolicy(PCI_DEV_INFO *Dev)
{
    EFI_STATUS Status;
    AMI_OPROM_POLICY_PROTOCOL *AmiOpromPolicyProtocol;

    Status = pBS->LocateProtocol(&gAmiOpromPolicyProtocolGuid, NULL, (VOID**)&AmiOpromPolicyProtocol);
    if(EFI_ERROR(Status))   //if CSM OptOut is disabled we should always launch UEFI OpROM
        return TRUE;

    Status = AmiOpromPolicyProtocol->CheckUefiOpromPolicy(AmiOpromPolicyProtocol, Dev->Class.BaseClassCode);
    return (EFI_ERROR(Status)) ? FALSE : TRUE;
}

/**
    Workaround to modify the DID of AMD legacy VGA oprom before AMI-IGD GOP launch and
    restore back in ready to boot.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID GnbDgpuDidSaveRestore (
    IN EFI_EVENT   Event,
    IN VOID        *Context )
{
	EFI_STATUS		Status = EFI_SUCCESS;
	DGPU_BACK_UP	*DevBackup = Context;

	if (Event == NULL) {
		PCI_DEV_INFO        	*dev = DevBackup->Dev;
		PCI_STD_OPT_ROM_HEADER	*StdRomHdr = dev->PciIo.RomImage;
		PCI_DATA_STRUCTURE		*Pcir = (PCI_DATA_STRUCTURE*)(((UINT8*)StdRomHdr) + StdRomHdr->PcirOffset);

		DevBackup->DeviceId = 0;
		// CodeType 0: Intel x86,PC-AT compatible
		// CodeType 3: EFI
		if(Pcir->CodeType == 0x00 ) {
			UINTN					ImageSize = Pcir->ImageLength*512;
			PCI_EFI_OPT_ROM_HEADER	*EfiRomHeader2 = (PCI_EFI_OPT_ROM_HEADER*)((UINT8*)StdRomHdr + ImageSize);
			if (EfiRomHeader2->Signature == 0xAA55) {

			} else {
				// Workaround in here
				// If external VGA card is legacy only and use GOP mode, we change DID for Workaround.
				// Avoid generic gop driver connect external legacy vga card.
				//
				// Store context
				DevBackup->DeviceId = Pcir->DeviceId;
				DevBackup->Pcir = Pcir;
				// override DID for workaround.
				Pcir->DeviceId = 0x1234;
			}
		}
	} else {
		if (DevBackup != NULL) {
			PCI_DATA_STRUCTURE		*Pcir = DevBackup->Pcir;
			// Restore DID
			if (DevBackup->DeviceId != 0) Pcir->DeviceId = DevBackup->DeviceId;
			Status = pBS->FreePool(DevBackup);
			ASSERT_EFI_ERROR (Status);
		}

		Status = pBS->CloseEvent(Event);
		ASSERT_EFI_ERROR (Status);
	}
}

/**
    This function will override the dGPU DID for the IGD-GOP.

    @param Device 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
GnbIgdGopWorkaround (
  IN PCI_DEV_INFO *Device
  )
{
	EFI_STATUS          	Status = EFI_SUCCESS;
	PCI_DEV_INFO        	*dev = Device;
	// not IGD
	if ( !(dev->ParentBrg->Address.Addr.Bus == 0
			&& dev->ParentBrg->Address.Addr.Device == 8
			&& dev->ParentBrg->Address.Addr.Function == 1
			&& dev->Address.Addr.Device == 0
			&& dev->Address.Addr.Function == 0)
			)
	{
		// any discrete VGA.
		if (dev->Class.BaseClassCode == PCI_CL_DISPLAY || (dev->Class.BaseClassCode == PCI_CL_OLD && dev->Class.SubClassCode == PCI_CL_OLD_SCL_VGA)) {
			// check if it is UEFI video policy. We can do the workaround on legacy VBIOS.
			if (GnbIsUefiOpromPolicy(dev)) {
				// if it is AMD discrete VGA.
				if (dev->DevVenId.VenId == ATI_VGA_VID) {
					if (dev->PciIo.RomImage != NULL) {
						EFI_EVENT		Event = NULL;
						DGPU_BACK_UP	*DevBackup = AllocateZeroPool(sizeof(DGPU_BACK_UP));

						DevBackup->Dev = dev;
						// first call for DID overridden.
						GnbDgpuDidSaveRestore(NULL, DevBackup);
						// restore back when ready to boot
						Status = EfiCreateEventReadyToBootEx(TPL_NOTIFY, GnbDgpuDidSaveRestore, (VOID*)DevBackup, &Event);
						ASSERT_EFI_ERROR (Status);
					}
				}
			}
		}
	}
	return Status;
}

/*
 * Check RV1 or RV2
 *
 * @retval    TRUE    This is RV1
 *            FALSE   This is RV2
 *
 */
BOOLEAN
CheckRvOpnB4 (
 
  )
{ 
  UINT32        OpnIndex32;
  UINT32        TempData32;
  UINT32        RegisterData;
  UINT64        Address;

  //TempData32 = PciExpressRead32 (PCI_EXPRESS_LIB_ADDRESS (0,0,0,0xB8));
  Address = PCI_LIB_ADDRESS(0x0,0x0,0x0,0xB8);
  TempData32 = PciRead32(Address);

  //PciExpressWrite32 (PCI_EXPRESS_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5C0);
  OpnIndex32 = 0x0005D5C0;
  PciWrite32(Address,OpnIndex32);
  
  //RegisterData = PciExpressRead32 (PCI_EXPRESS_LIB_ADDRESS (0,0,0,0xBC));
  Address = PCI_LIB_ADDRESS(0x0,0x0,0x0,0xBC);
  RegisterData = PciRead32(Address);
  
  //PciExpressWrite32 (PCI_EXPRESS_LIB_ADDRESS (0, 0, 0, 0xB8), Index32);
  Address = PCI_LIB_ADDRESS(0x0,0x0,0x0,0xB8);
  PciWrite32(Address,TempData32);

  TempData32 =  (RegisterData >> 30) & 0x3;

  if (TempData32 == 1) {
    return FALSE;
  } else if (TempData32 == 3) {
    return FALSE;
  }

  return TRUE;  
}

/**
    This function will override the original iGPU DID/VID in SDL
    for the current IGD.

    @param Device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
GnbIsPciGetOptionRom (
  IN PCI_DEV_INFO *Device
  )
{
	EFI_STATUS          	Status = EFI_SUCCESS;
	PCI_DEV_INFO        	*dev = Device;
	VOID					*RomFile;
	UINTN					RomSize;
	PCI_STD_OPT_ROM_HEADER	*StdRomHdr;
	PCI_DATA_STRUCTURE		*PcirStruct;
	AMI_SDL_PCI_DEV_INFO	*romSdlData;
    BOOLEAN                 IsRavenOpn;
	
	// check if it is AMD IGD. (The first device behind B0D8F1 bridge)
	if (dev->ParentBrg->Address.Addr.Bus == 0
			&& dev->ParentBrg->Address.Addr.Device == 8
			&& dev->ParentBrg->Address.Addr.Function == 1
			&& dev->Address.Addr.Device == 0
			&& dev->Address.Addr.Function == 0)
	{
		UINTN	i;

		for (i = 0; i < dev->SdlDevCount; i++) {
			// find legacy rom.
			Status = PciBusReadNextEmbeddedRom(dev, i, &romSdlData, &RomFile, &RomSize);
			//#### The PciBusReadNextEmbeddedRom will return non-EmbeddedRom item. So remove this line.//if(EFI_ERROR(Status)) break;
			if (romSdlData->PciDevFlags.Bits.EmbededRom != 1) continue;
			//####ifdef AMI_MODULE_PKG_VERSION
			//####if AMI_MODULE_PKG_VERSION > 18
			if (romSdlData->PciDevFlags.Bits.UefiDriverBin == 1) continue;

            //check OPN for correct VBIOS
            //if(CheckRvOrRv2Vbios()) continue;
            IsRavenOpn = CheckRvOpnB4();
            if ((IsRavenOpn && CompareMem(&gRavenVbiosRomSectionGuid,  &romSdlData->RomSectionGuid, sizeof(EFI_GUID)) == 0) ||                  
                (!IsRavenOpn && CompareMem(&gRaven2VbiosRomSectionGuid, &romSdlData->RomSectionGuid, sizeof(EFI_GUID)) == 0)
            ){
            
                StdRomHdr = (PCI_STD_OPT_ROM_HEADER*)RomFile;
                //STD ROM Image... read VID/DID info from PCIR struct.
                PcirStruct = (PCI_DATA_STRUCTURE*)(((UINT8*)RomFile) + StdRomHdr->PcirOffset);
    
                // update DID/VID in the PCIR header.
                PcirStruct->DeviceId = dev->DevVenId.DevId;
                PcirStruct->VendorId = dev->DevVenId.VenId;
    
                dev->PciIo.RomImage = RomFile;
                dev->PciIo.RomSize = RomSize;
                //Update Capabilities...
                dev->Capab |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
                dev->Attrib  |= (EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM);
                break;
            }

		}
	}

	return Status;
}


/**
    This function to turn on bus master of IOMMU device to met AMD PPR.
    	!!!! This function will be removed once AMD program it in RC. !!!!

    @param Device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
NbioIommuBusMaster (
  IN PCI_DEV_INFO *Device
  )
{
	EFI_STATUS          	Status = EFI_SUCCESS;
	PCI_DEV_INFO        	*dev = Device;
	// If IOMMU device.
	if ( dev->Address.Addr.Bus == 0
			&& dev->Address.Addr.Device == 0
			&& dev->Address.Addr.Function == 2
			)
	{
		EFI_PCI_IO_PROTOCOL		*PciIo = &dev->PciIo;
		UINT64      			Attr;

		Status = PciIo->Attributes(PciIo,
								   EfiPciIoAttributeOperationSupported,
								   0,&Attr
									);

		if (!EFI_ERROR (Status)) {
			// Turn on bus master. Please refer to AMD PPR.
			Attr &= EFI_PCI_IO_ATTRIBUTE_BUS_MASTER;

			Status = PciIo->Attributes( PciIo,
										EfiPciIoAttributeOperationSet,
										Attr,
										NULL
										);
		}
	}

	return Status;
}

/**
    GNB Pci init routine

    @param This 
    @param Function 
    @param ParameterBlock 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS	CspGnbPciInitRoutine (
		AMI_BOARD_INIT_PROTOCOL		*This,
		IN UINTN					*Function,
		IN OUT VOID					*ParameterBlock
)
{
//Update Standard parameter block
	AMI_BOARD_INIT_PARAMETER_BLOCK	*Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
	PCI_INIT_STEP        			InitStep=(PCI_INIT_STEP)Args->InitStep;
    PCI_DEV_INFO   					*dev=(PCI_DEV_INFO*)Args->Param1;
    EFI_STATUS  					Status=EFI_UNSUPPORTED;

//---------------------------------
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_PCI_PARAM_SIG) return EFI_INVALID_PARAMETER;
    if(InitStep>=isPciMaxStep) return EFI_INVALID_PARAMETER;

    switch (InitStep)
    {
	//-------------------------------------------------------------------------
		case isPciGetSetupConfig:
			DEBUG((DEBUG_VERBOSE," (isPciGetSetupConfig); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciSkipDevice:
			DEBUG((DEBUG_VERBOSE," (isPciSkipDevice); %r",Status ));

		break;
	//-------------------------------------------------------------------------
		case isPciSetAttributes:
			DEBUG((DEBUG_VERBOSE," (isPciSetAttributes); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciProgramDevice:
//### RVA9 : check later ###			Status = GnbIgdGopWorkaround(dev);
			Status = NbioIommuBusMaster(dev);
			DEBUG((DEBUG_VERBOSE," (isPciProgramDevice); %r",Status ));

		break;
	//-------------------------------------------------------------------------
		case isPcieInitLink:
			DEBUG((DEBUG_VERBOSE," (isPcieInitLink); " ));

		break;
	//-------------------------------------------------------------------------
		case isPcieSetAspm:
			DEBUG((DEBUG_VERBOSE," (isPcieSetAspm); " ));

		break;
	//-------------------------------------------------------------------------
		case isPcieSetLinkSpeed:
			DEBUG((DEBUG_VERBOSE," (isPcieSetLinkSpeed); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciGetOptionRom:
			DEBUG((DEBUG_VERBOSE," (isPciGetOptionRom); " ));
			Status = GnbIsPciGetOptionRom(dev);


		break;
	//-------------------------------------------------------------------------
		case isPciOutOfResourcesCheck:
			DEBUG((DEBUG_VERBOSE," (isPciOutOfResourcesCheck); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciReadyToBoot:
			DEBUG((DEBUG_VERBOSE," (isPciReadyToBoot); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciQueryDevice:
			DEBUG((DEBUG_VERBOSE," (isPciQueryDevice); " ));

		break;
	//-------------------------------------------------------------------------
		case isHbBasicInit:
			DEBUG((DEBUG_VERBOSE," (isHbBasicInit); " ));

		break;
	//-------------------------------------------------------------------------
		case isRbCheckPresence:
			DEBUG((DEBUG_VERBOSE," (isRbCheckPresence); " ));

		break;
	//-------------------------------------------------------------------------
		case isRbBusUpdate:
			DEBUG((DEBUG_VERBOSE," (isRbBusUpdate); " ));

		break;
	//-------------------------------------------------------------------------
		default:
			Status=EFI_INVALID_PARAMETER;
			DEBUG((DEBUG_VERBOSE," (!!!isPciMaxStep!!!); " ));
    }//switch

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
