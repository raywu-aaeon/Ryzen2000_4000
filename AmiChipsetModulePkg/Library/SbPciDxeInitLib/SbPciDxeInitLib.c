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
/** @file SbPciDxeInitLib.c
	Sb Pci library link to PciBus.
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
#include <Library/AmiPciBusLib.h>

/**
    To skip device enumeration for AMD Device 14h Function 0 (SMBus).
    The reason is whole the BAR of this device are unavailable.
    AMI PciBus will clear command register it will cause AMD BTS test tools failure.
    (EIP178628 HyperTransport Failed)

    @param Device the device information.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
AmdFchSkipDevice (
  IN PCI_DEV_INFO *Device
  )
{
	EFI_STATUS          			Status = EFI_UNSUPPORTED; //  Unsupported means don't skip it.
	PCI_DEV_INFO        			*dev = Device;
	UINT32							i;
	EFI_PCI_CONFIGURATION_ADDRESS	CONST SkipDevice[1] = {
			// porting : append more device if needed.
			//		.....
			// 	Register	Function	Device	Bus	ExtendedRegister
			{	0, 			0, 			0x14, 	0, 	0}
	};

	for (i = 0; i < sizeof(SkipDevice)/sizeof(PCI_CFG_ADDR); i++) {
		if (dev->Address.Addr.Bus == SkipDevice[i].Bus &&
				dev->Address.Addr.Device == SkipDevice[i].Device &&
				dev->Address.Addr.Function == SkipDevice[i].Function)
		{
			Status = EFI_SUCCESS; // To skip this device.
			break;
		}
	}

	return Status;
}

/**
    SB Pci init routine

    @param This 
    @param Function 
    @param ParameterBlock 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS	CspSbPciInitRoutine (
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

			Status = AmdFchSkipDevice(dev);

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
