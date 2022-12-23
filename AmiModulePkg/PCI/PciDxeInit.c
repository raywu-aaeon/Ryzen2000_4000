//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985 - 2021, American Megatrends International LLC. *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//**********************************************************************
/** @file PciDxeInit.c
    Anchor Driver for PCI Initialization DXE Driver.
	Implements Default Function 0 of the AMI_BOARD_INIT_PROTOCOL 
	Rest of the functions delivered from different sources in a form of Libraries
	and linked with this driver 

**/
//**********************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <PciBus.h>
#include <PciHostBridge.h>
#include <Setup.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/AmiBoardInfo2.h>
#include <Protocol/AmiBoardInitPolicy.h>
#include <PciBusDevHooksElink.h>
#include  <Library/PcdLib.h>
#include "PciDxeInitPrivate.h"

UINTN         gDriverVersion=PCI_BUS_VER_COMBINED;
CHAR8         *gPciName="AMI PCI Bus Driver";
UINTN         gPciPlatformId=0x1;
EFI_HANDLE    gPciInitHandle=NULL;

//This is to declare external functions...
#define ANY_PCI_DEV_CALLBACK( VendorId, DeviceId, Callback ) Callback
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_GET_SETUP_CONFIG_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_SKIP_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_PROGRAM_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_GET_OPT_ROM_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_ATTRIBUTES_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_QUERY_PHASE_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_READY_TO_BOOT_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_GET_RB_ASL_NAME_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCIE_INIT_LINK_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCIE_SET_ASPM_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCIE_SET_LNK_SPEED_CALLBACKS_LIST EndOfList;
extern AMI_BOARD_INIT_FUNCTION_PROTOTYPE AMI_ANY_DEV_HOOK_PCI_ATTRIBUTES_CALLBACKS_LIST EndOfList;
#undef ANY_PCI_DEV_CALLBACK 

///
///Data Delivered from eLinks...
///
//This one to feed the data.
#define ANY_PCI_DEV_CALLBACK( VendorId, DeviceId, Callback )  { VendorId, DeviceId, (AMI_BOARD_INIT_FUNCTION_PROTOTYPE*)&Callback }
AMI_PCI_DEVICE_CALLBACK gGetSetupData[] ={ AMI_ANY_DEV_HOOK_PCI_GET_SETUP_CONFIG_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gSkipDevice[]   ={ AMI_ANY_DEV_HOOK_PCI_SKIP_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gProgramDevice[]={ AMI_ANY_DEV_HOOK_PCI_PROGRAM_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gSetAspm[]      ={ AMI_ANY_DEV_HOOK_PCIE_SET_ASPM_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gSetLnkSpeed[]  ={ AMI_ANY_DEV_HOOK_PCIE_SET_LNK_SPEED_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gQueryDevice[]  ={ AMI_ANY_DEV_HOOK_PCI_QUERY_PHASE_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gAttributes[]   ={ AMI_ANY_DEV_HOOK_PCI_ATTRIBUTES_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gGetOptRom[]    ={ AMI_ANY_DEV_HOOK_PCI_GET_OPT_ROM_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gInitLink[]     ={ AMI_ANY_DEV_HOOK_PCIE_INIT_LINK_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gReadyBoot[]    ={ AMI_ANY_DEV_HOOK_PCI_READY_TO_BOOT_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gGetRbAslName[] ={ AMI_ANY_DEV_HOOK_PCI_GET_RB_ASL_NAME_CALLBACKS_LIST { 0, 0, NULL } };
AMI_PCI_DEVICE_CALLBACK gHpUpdPadding[] ={ AMI_ANY_DEV_HOOK_PCIE_INIT_LINK_CALLBACKS_LIST { 0, 0, NULL } };
#undef ANY_PCI_DEV_CALLBACK 

///
///All RB and HB related initialization must be handled on SDL Database basis
///and must be defined. Hence - will not be represented in global hooks list.
///
////////////////////////////////////////////////////////////////////////////
/// IMPORTANT NOTE:
///   Once adding new list entry make sure that Table Index exactly
///   matches with PCI_INIT_STEP enum from AmiModulePkg/Protocol/AmiBoardInitPolicy.h 
////////////////////////////////////////////////////////////////////////////

AMI_PCI_DEVICE_CALLBACK *gBigList[isPciMaxStep]={
        NULL,                   //isPciNone = 0,              //0 
        &gGetSetupData[0],      //isPciGetSetupConfig,        //1
        &gSkipDevice[0],        //isPciSkipDevice,            //2
        &gAttributes[0],        //isPciSetAttributes,         //3
        &gProgramDevice[0],     //isPciProgramDevice,         //4
        &gInitLink[0],          //isPcieInitLink,             //5
        &gSetAspm[0],           //isPcieSetAspm,              //6
        &gSetLnkSpeed[0],       //isPcieSetLinkSpeed,         //7
        &gGetOptRom[0],         //isPciGetOptionRom,          //8
///......................................................................
///For "Out Of Resources" one by one approach is more efficient
///It must be handled on SLOT/Onboard device basis all this 
///must be defined in AMI SDL Data structures. 
        NULL,                   //isPciOutOfResourcesCheck,   //9
///......................................................................
        &gReadyBoot[0],         //isPciReadyToBoot,           //10    
        &gQueryDevice[0],       //isPciQueryDevice,           //11
        NULL,                   //isHbBasicInit,              //12
        NULL,                   //isRbCheckPresence,          //13
        NULL,                   //isRbBusUpdate,              //14
        &gHpUpdPadding[0],      //isHpUpdatePadding,          //15
        gGetRbAslName          //isPciGetRbAslName,          //16
        //isPciMaxStep                //17...so far
};




//-------------------------------------------------------------------------
/**
    NEW
    In Label12 of PciBus Driver this will be the common function called for eLINKS
    Based on VID/DID hook selection.
    All Init Functions will have same calling interface and delivered to the PciDxeInit Driver 
    Same way!
    
    OLD
    Default Init Function - FUNC 0. Must present always. 
    Could be used for validation of the protocol instance 
        
    @param This Pointer to the AMI_BOARD_INIT_PROTOCOL instance
    @param Function Function number that called (must be 0 for function #0)
    @param ParameterBlock pointer at the Protocol's Parameters block

    @retval EFI_STATUS Return Status
    @retval EFI_SUCCESS Initial step successfully
    @retval EFI_INVALID_PARAMETER not find the initial step

**/
EFI_STATUS EFIAPI Func0(
    AMI_BOARD_INIT_PROTOCOL                          *This,
    IN UINTN                                         *Function,
    IN OUT AMI_BOARD_INIT_PARAMETER_BLOCK            *ParameterBlock
)
{
    EFI_STATUS                          Status=EFI_UNSUPPORTED;
    AMI_PCI_DEVICE_CALLBACK             *List;
    EFI_STATUS                          retStatus=EFI_UNSUPPORTED;
    //Update Standard parameter block
    //START: Fix for Coverity Issue : REVERSE_INULL
    AMI_BOARD_INIT_PARAMETER_BLOCK      *Args;
    PCI_INIT_STEP                       InitStep;
    PCI_DEV_INFO                        *Device;
    //END: Fix for Coverity Issue : REVERSE_INULL
//-------------------
    //Check passed parameters first...
    if((This==NULL) || (*Function != 0) || (ParameterBlock==NULL)) return EFI_INVALID_PARAMETER;
    //START: Fix for Coverity Issue : REVERSE_INULL
    Args = ParameterBlock;
    InitStep = (PCI_INIT_STEP)Args->InitStep;
    Device = (PCI_DEV_INFO*)Args->Param1;
    //END: Fix for Coverity Issue : REVERSE_INULL
    if(Args->Signature != AMI_PCI_PARAM_SIG) return EFI_INVALID_PARAMETER;

    List=gBigList[InitStep];
    if(List==NULL) return retStatus;
    
    while(List->Callback!=NULL)
    {
        AMI_BOARD_INIT_FUNCTION HookFunction=(AMI_BOARD_INIT_FUNCTION)(UINTN)(List->Callback);
    //--------------------------------
        if( ((List->VendorId & Device->DevVenId.VenId)==Device->DevVenId.VenId) && 
            ((List->DeviceId & Device->DevVenId.DevId)==Device->DevVenId.DevId) )
        {
            DEBUG((DEBUG_VERBOSE, "\n DevCmnHook: B%X|D%X|F%X (VID=0x%X; DID=0x%X; Mask(0x%X:0x%X) InitStep=%d;", 
            Device->Address.Addr.Bus,Device->Address.Addr.Device,Device->Address.Addr.Function, 
            Device->DevVenId.VenId, Device->DevVenId.DevId, List->VendorId,List->DeviceId, InitStep));

            Status = HookFunction(gPciInitProtocolPtr, Function, Args);
            DEBUG((DEBUG_VERBOSE, ")=%r;\n", Status));
 
            if( EFI_ERROR(Status) && (Status!=EFI_UNSUPPORTED))return Status;
            else if(Status==EFI_SUCCESS)retStatus=Status;
        }
        List++;
    }

    return retStatus;
}

///
/// Including AUTO generated by AMI SDL Function list and interface declaration
///

#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

#include <PCIDXEINIT.h>

/**
    This function is the entry point of this Driver. 
    Since Driver follows UEFI driver model in it's entry point
    it will initialize some global data and install
    EFI_DRIVER_BINDING_PROTOCOL. 

        
    @param ImageHandle Image handle.
    @param SystemTable Pointer to the EFI system table.

    @retval EFI_STATUS
        EFI_SUCCESS         When everything is going on fine!
        EFI_NOT_FOUND       When something required is not found!
        EFI_DEVICE_ERROR    When the device is not responding!

    @note  
  Entry Points are used to locate or install protocol interfaces and
 notification events. 

**/

EFI_STATUS EFIAPI PciDxeInitEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS              Status;
//-----------------
    InitAmiLib(ImageHandle,SystemTable);
    
    //Now install all Protocol Instances defined in SIOINITSDL.H
    Status=pBS->InstallMultipleProtocolInterfaces(
        &gPciInitHandle,
        &gAmiBoardPciInitProtocolGuid, gPciInitProtocolPtr, NULL
        //&gF81866InitPolicyGuid, &gF81866InitProtocol, NULL
    );
    ASSERT_EFI_ERROR(Status);
    
    return Status;

}
//============================================================
//---- DO Not modify this code!
//============================================================


// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: DeviceXXXX_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
//  IN  AMI_SIO_PROTOCOL    *AmiSio - Logical Device's information
//  IN  EFI_PCI_IO_PROTOCOL *PciIo - Read/Write PCI config space
//  IN  SIO_INIT_STEP       InitStep - Initial routine step
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:    Nothing
//
// Referrals:   None
//
// Notes:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS PciDevXXX_Init(
AMI_BOARD_INIT_PROTOCOL     *This,
IN UINTN                    *Function,
IN OUT VOID                 *ParameterBlock
)
{
//Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    PCI_INIT_STEP                   InitStep=(PCI_INIT_STEP)Args->InitStep;
    PCI_DEV_INFO                    *dev=(PCI_DEV_INFO*)Args->Param1;
    EFI_STATUS                      Status=EFI_UNSUPPORTED;
    
    //Check if parameters passed are VALID and
   if(Args->Signature != AMI_PCI_PARAM_SIG) return EFI_INVALID_PARAMETER;
   if(InitStep>=isPciMaxStep) return EFI_INVALID_PARAMETER;
    switch (InitStep)
    {
    //-------------------------------------------------------------------------
        case isPciGetSetupConfig:
            DEBUG((DEBUG_VERBOSE," (isPciGetSetupConfig); " ));
                                        
            if (dev->PciExpress != NULL) {
               if (dev->PciExpress->Pcie2 != NULL) {
                   dev->PciExpress->Pcie2->Pcie2Setup.AriFwd = PcdGetBool(PcdCfgPcieAriSupport);
                   Status=EFI_SUCCESS;
               }
            }

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
    }//switch

    return Status;
}
