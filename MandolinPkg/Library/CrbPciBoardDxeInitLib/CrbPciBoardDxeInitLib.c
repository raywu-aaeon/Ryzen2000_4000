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


/** @file CrbPciBoardDxeInitLib.c

**/

#include <AmiDxeLib.h>
#include <Token.h>
#include <PciBus.h>
#include <PciHostBridge.h>
#include <Setup.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Protocol/AmiBoardInitPolicy.h>
#include <Library/AmiPciBusLib.h>
#if defined(AmiNetworkPkg_SUPPORT)&&(AmiNetworkPkg_SUPPORT==1)
#include <Guid/NetworkStackSetup.h>
#endif

#if defined(CRB_PXE_LOADER_SUPPORT) && (CRB_PXE_LOADER_SUPPORT == 0)
/**
  dispatch UEFI PXE depend on the setup item of Network.

  @param[in]  Device  The pointer to PCI_DEV_INFO which is from PciBus driver.


  @return EFI_SUCCESS               No error
  @return Others Errors             No NetworkStackVar support.

**/
EFI_STATUS
AmiCrbPciePxeLoader (
  IN PCI_DEV_INFO *Device
  )
{

    EFI_STATUS  	Status = EFI_SUCCESS;
    PCI_DEV_INFO	*dev = Device;

#if defined(AmiNetworkPkg_SUPPORT) && (AmiNetworkPkg_SUPPORT == 1)
    UINTN    		Size;
    NETWORK_STACK	mNetworkStackData;

    if (dev->DevVenId.DevId == CRB_PXE_DID && dev->DevVenId.VenId == CRB_PXE_VID) {
		Size = sizeof(NETWORK_STACK);
		Status = pRS->GetVariable(L"NetworkStackVar",&gEfiNetworkStackSetupGuid, NULL, &Size, &mNetworkStackData);
		if (Status == EFI_SUCCESS) {
			 if (mNetworkStackData.Enable == 0 ) {
				if(dev->EmbRomCnt > 0) {
					EMB_ROM_INFO	*embrom;
					UINTN 			i;

					for(i = 0; i < dev->EmbRomCnt; i++) {
						embrom = dev->EmbRoms[i];
						if(embrom->UefiDriver) {
							// Remove PXE UEFI driver.
							embrom->UefiDriver = FALSE;
							embrom->EmbRomDevVenId.DEV_VEN_ID = -1;
						}
					}
				}
			 }
		}
    }
#endif

    return Status;
}

#endif


/**
    SB Pci init routine

        AMI_BOARD_INIT_PROTOCOL		*This,
    @param Function 
    @param ParameterBlock 

    @retval EFI_STATUS Status

**/
EFI_STATUS	CrbPciInitRoutine (
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
			DEBUG((DEBUG_VERBOSE," (isPciSkipDevice); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciSetAttributes:
			DEBUG((DEBUG_VERBOSE," (isPciSetAttributes); " ));

		break;
	//-------------------------------------------------------------------------
		case isPciProgramDevice:
			DEBUG((DEBUG_VERBOSE," (isPciProgramDevice); " ));

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
			// PXE dispatch.
		#if defined(CRB_PXE_LOADER_SUPPORT) && (CRB_PXE_LOADER_SUPPORT == 0)
			Status = AmiCrbPciePxeLoader(dev);
		#endif

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
