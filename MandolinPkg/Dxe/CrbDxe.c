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

/** @file CrbDxe.c
    This file contains code for Chipset Reference Board Template
    initialization in the DXE stage

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiDxe.h>
#include <Protocol/CrbInfo.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <AcpiRes.h>
#include <AmiLib.h>
#include <Acpi.h>
#include <Setup.h>
#include <Pci.h>




// Produced Protocols

// Consumed Protocols
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/PciHotPlugInit.h>
#include <Protocol/S3SaveState.h>
#if HOTPLUG_SUPPORT
#include <AcpiRes.h>
#include <Protocol/PciHotPlugInit.h>
#endif

#include <Protocol/AmiUsbController.h>            
#if defined(AmiNetworkPkg_SUPPORT)&&(AmiNetworkPkg_SUPPORT==1)
#include <Guid/NetworkStackSetup.h>
#endif

#include <AmdSoc.h>
#include <Library/AmdSocBaseLib.h>
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiTable.h>

#define EFI_ACPI_SUPPORT_GUID \
  { \
    0xdbff9d55, 0x89b7, 0x46da, {0xbd, 0xdf, 0x67, 0x7d, 0x3d, 0xc0, 0x24, 0x1d } \
  }

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)
typedef struct _CRB_SYS_MEM_ASL{
    UINT8 CrbMITTWITTControl;
    UINT8 CrbTouchPanel;
    UINT8 CrbTouchPad;
    UINT8 CrbNfcSensor;
    UINT8 CrbamdLightSensor;
    UINT8 CrbAmdDptcControl;
    UINT8 CrbRV2Identify;
    UINT8 CrbIsds;
}CRB_SYS_MEM_ASL;

// Function Prototype(s)
UINT8
CrbDxeGetChipsetVendorNo (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

UINT32
CrbDxeGetCpuId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  	*This
);

UINT32
CrbDxeGetNorthBridgePciId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

UINT32
CrbDxeGetSouthBridgePciId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

CHAR8*
CrbDxeGetProjectId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

UINT16
CrbDxeGetBiosRevision (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
);

VOID
CrbAcpiSdtCallBack (
	IN EFI_EVENT Event,
	IN VOID *Context
	);

//-------------------------------------------------------------------
// PciHotPlugInit Protocol
//-------------------------------------------------------------------
EFI_STATUS
GetRootHpcList (
  IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL    *This,
  OUT UINTN                            *HpcCount,
  OUT EFI_HPC_LOCATION                 **HpcList
  );

EFI_STATUS
InitializeRootHpc (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL      *This,
  IN  EFI_DEVICE_PATH_PROTOCOL            *HpcDevicePath,
  IN  UINT64                              HpcPciAddress,
  IN  EFI_EVENT                           Event, OPTIONAL
  OUT EFI_HPC_STATE                       *HpcState
  );

EFI_STATUS
GetResourcePadding (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN  UINT64                          HpcPciAddress,
  OUT EFI_HPC_STATE                   *HpcState,
  OUT VOID                            **Padding,
  OUT EFI_HPC_PADDING_ATTRIBUTES      *Attributes
  );

VOID
CRBReadyToBoot(
    IN EFI_EVENT Event,
    IN VOID *Context
);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
CHAR8 CONST ProjectTag[5] = CONVERT_TO_STRING(CRB_PROJECT_TAG);
EFI_EVENT       gCrbReadyToBoot;

CRB_SYS_MEM_ASL *gSystemMemoryAsl = NULL;

// GUID Definition(s)

// Protocol Definition(s)
AMI_EFI_CRBINFO_PROTOCOL	gAmiCrbInforProtocol = {
	CrbDxeGetChipsetVendorNo,
	CrbDxeGetCpuId,
	CrbDxeGetNorthBridgePciId,
	CrbDxeGetSouthBridgePciId,
	CrbDxeGetProjectId,
	CrbDxeGetBiosRevision,
};
#if HOTPLUG_SUPPORT
EFI_PCI_HOT_PLUG_INIT_PROTOCOL  HotPlugProtocol = {
    GetRootHpcList,
    InitializeRootHpc,
    GetResourcePadding
};
#endif

// GUID Definition(s)

// External Declaration(s)
//BOOLEAN       FchCheckPicasso (VOID);
// Function Definition(s)

//---------------------------------------------------------------------------


/**
    Provide the chipset vendor number.

    @param This 

    @retval 0 Unknown.
    @retval 1 Intel.
    @retval 2 AMD.

    @note  .
**/
UINT8
CrbDxeGetChipsetVendorNo (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
  )
{
	UINT32      Index;
	UINT32      RegisterEax;
	UINT32      RegisterEbx;
	UINT32      RegisterEcx;
	UINT32      RegisterEdx;
	// Intel
	// EBX 756E6547 "uneG"
	// ECX 6C65746E "letn"
	// EDX 49656e69 "Ieni"
	// AMD
	//EBX 68747541 "htuA"
	//ECX 444D4163 "DMAc"
	//EDX 69746E65 "itne"
	CHAR8 CONST Intel[5] = "letnI";
	CHAR8 CONST Amd[3] = "DMA";
	CHAR8 MyString[5];
	UINT8 ChipsetVendorNo = 0;

	Index = 0;
	Index = AsmCpuid(Index, &RegisterEax, &RegisterEbx, &RegisterEcx, &RegisterEdx);
	MyString[4] = ((CHAR8*)&RegisterEdx)[3];
	MyString[3] = ((CHAR8*)&RegisterEcx)[0];
	MyString[2] = ((CHAR8*)&RegisterEcx)[1];
	MyString[1] = ((CHAR8*)&RegisterEcx)[2];
	MyString[0] = ((CHAR8*)&RegisterEcx)[3];

	if (CompareMem(MyString, Intel, 5) == 0) {
		ChipsetVendorNo = 1;
	} else if (CompareMem(MyString, Amd, 3) == 0) {
		ChipsetVendorNo = 2;
	}

	return ChipsetVendorNo;
}

/**
    Provide the CPU ID.

        
    @param This 

    @retval UINT32 EAX : Version Information (Type, Family, Model, and Stepping ID)

    @note  .
**/
UINT32
CrbDxeGetCpuId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  	*This
  )
{
	UINT32	Index = 1;
	UINT32	RegisterEax = -1;
	// EAX : Version Information (Type, Family, Model, and Stepping ID)
	Index = AsmCpuid(Index, &RegisterEax, NULL, NULL, NULL);
	return RegisterEax;
}

/**
    Provide the PCI DID/VID of the north bridge.

    @param This 

        -1 - Undefined.
    @retval others PCI DID/VID.

    @note  .
**/
UINT32
CrbDxeGetNorthBridgePciId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
  )
{
	UINT32 PciId = -1;

	if (This->GetChipsetVendorNo(This) == 1) {
		PciId = PciRead32(PCI_LIB_ADDRESS(0, 0, 0, 0));
	} else if (This->GetChipsetVendorNo(This) == 2){
		PciId = PciRead32(PCI_LIB_ADDRESS(0, 0, 0, 0));
	}

	return PciId;
}

/**
    Provide the PCI DID/VID of the south bridge.

    @param This 

        -1 - Undefined.
    @retval others PCI DID/VID.

    @note  .
**/
UINT32
CrbDxeGetSouthBridgePciId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
  )
{
	UINT32 PciId = -1;

	if (This->GetChipsetVendorNo(This) == 1) {
		PciId = PciRead32(PCI_LIB_ADDRESS(0, 31, 0, 0));
	} else if (This->GetChipsetVendorNo(This) == 2){
		PciId = PciRead32(PCI_LIB_ADDRESS(0, 20, 0, 0));
	}

	return PciId;
}

/**
    Provide the project ID.

    @param This 

    @retval NULL Undefined / error.
    @retval others Project ID.

    @note  .
**/
CHAR8*
CrbDxeGetProjectId (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
  )
{
	return ProjectTag;
}

/**
    Provide the BIOS revision.

    @param This 

        -1 - Undefined / error.
    @retval others BIOS revision.

    @note  .
**/
UINT16
CrbDxeGetBiosRevision (
  IN  CONST AMI_EFI_CRBINFO_PROTOCOL  *This
  )
{
	return (CRB_PROJECT_MAJOR_VERSION << 8) | CRB_PROJECT_MINOR_VERSION;
}


/**
    This callback function is called after USB Protocol is 
    installed.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID CrbUsbProtocolCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    
    pBS->CloseEvent(Event);
}

/**
    This function would allocate/reserve NVS memory for ACPI usage,
    This memory will use for sync CPS setup value

    @param VOID

    @retval VOID
**/

EFI_STATUS CrbPbsSetupUpdateToAslSysMem(
		VOID)
{
	EFI_STATUS	                Status = EFI_SUCCESS;
	AMD_PBS_SETUP_OPTION        AmdPbsSetup;
//	UINT32                      TempData32;
	
	Status = GetAmdPbsConfiguration(&AmdPbsSetup);
	if(EFI_ERROR(Status)) return EFI_NOT_FOUND;
			
	Status = gBS->AllocatePool (EfiACPIMemoryNVS,
								sizeof (CRB_SYS_MEM_ASL),
								&gSystemMemoryAsl
								);
	
	gSystemMemoryAsl->CrbMITTWITTControl = AmdPbsSetup.MITTWITTControl;
	/*gSystemMemoryAsl->CrbTouchPanel = AmdPbsSetup.TouchPanel;
	gSystemMemoryAsl->CrbTouchPad = AmdPbsSetup.TouchPad;
	gSystemMemoryAsl->CrbNfcSensor = AmdPbsSetup.NfcSensor;
	gSystemMemoryAsl->CrbamdLightSensor = AmdPbsSetup.amdLightSensor;
	gSystemMemoryAsl->CrbAmdDptcControl = AmdPbsSetup.AmdDptcControl;*/
//	if (FchCheckPicasso()){
//           gSystemMemoryAsl->CrbRV2Identify = 0;
//	} else {
//           gSystemMemoryAsl->CrbRV2Identify = 1;
//	}
//	
//	gSystemMemoryAsl->CrbIsds = 0;
//	TempData32 = (PcdGet32 (PcdGetRVFamilyOPN) >> 30) & 0x3;
//	if (TempData32 == 2 || TempData32 == 3){
//	    gSystemMemoryAsl->CrbIsds = 1;
//	}
	
	return Status;
}

/**
    This function is the entry point for CRB DXE driver.
    This function initializes the CRB in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

    @note  This routine is called very early, prior to SBDXE and NBDXE.
**/

EFI_STATUS EFIAPI CrbDxeInit (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;
#if HOTPLUG_SUPPORT
    EFI_HANDLE            	Handle = NULL;
#endif
    EFI_EVENT       CrbEvtUsbProtocol  = NULL;
    VOID            *CrbRegUsbProtocol = NULL;
    VOID					*Registration = NULL;
        static EFI_GUID Acpisupguid = EFI_ACPI_SUPPORT_GUID;
    
    InitAmiLib(ImageHandle, SystemTable);

#if HOTPLUG_SUPPORT
    Status = gBS->InstallProtocolInterface (
        &Handle,
        &gEfiPciHotPlugInitProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &HotPlugProtocol
    );
    ASSERT_EFI_ERROR (Status);
#endif

    // The Event ready to boot
    Status = CreateReadyToBootEvent(TPL_NOTIFY, CRBReadyToBoot, NULL, &gCrbReadyToBoot);
    //--Status = EfiCreateEventReadyToBootEx(TPL_NOTIFY, CRBReadyToBoot, NULL, &gCrbReadyToBoot);
    ASSERT_EFI_ERROR (Status);

    Status = EfiNamedEventListen ( // EfiCreateProtocolNotifyEvent
				&Acpisupguid,
				TPL_CALLBACK,
				CrbAcpiSdtCallBack,
				NULL,
				&Registration
				);
    ASSERT_EFI_ERROR (Status);

    Status = CrbPbsSetupUpdateToAslSysMem();
    
    Status = gBS->InstallMultipleProtocolInterfaces(
                    &ImageHandle,
                    &gAmiEfiCrbInfoProtocolGuid, &gAmiCrbInforProtocol,
                    NULL
                    );

    Status = RegisterProtocolCallback( &gEfiUsbProtocolGuid,\
                   CrbUsbProtocolCallback,\
                   NULL,\
                   &CrbEvtUsbProtocol,\
                   &CrbRegUsbProtocol );

    return Status;
}

#if HOTPLUG_SUPPORT

#define ACPI \
    {{ACPI_DEVICE_PATH,ACPI_DP,ACPI_DEVICE_PATH_LENGTH}, EISA_PNP_ID(0x0A03),0}

#define PCI(Device, Function) \
    {{HARDWARE_DEVICE_PATH, HW_PCI_DP, HW_PCI_DEVICE_PATH_LENGTH}, (Function),(Device)}

#define END \
    {END_DEVICE_PATH,END_ENTIRE_SUBTYPE,END_DEVICE_PATH_LENGTH}

typedef struct PCIE_HOT_PLUG_DEVICE_PATH {
  ACPI_HID_DEVICE_PATH      PciRootBridgeNode;
  PCI_DEVICE_PATH           PciRootPortNode;
  EFI_DEVICE_PATH_PROTOCOL  EndDeviceNode;
} PCIE_HOT_PLUG_DEVICE_PATH;

//#define PCIE_NUM  (10)

//
// Instantiation of Driver private data.
//
PCIE_HOT_PLUG_DEVICE_PATH mPcieList[] = {

  OEM_CHIP_HOTPLUG_DEVICE

 {
    ACPI,
    PCI(0xFF, 0xFF),
    END
  },   // PCI Express 5

};
//<<  GPPHotPlug
/**
    This procedure returns a list of Root Hot Plug controllers that require
    initialization during boot process
        
    @param This The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
    @param HpcCount The number of Root HPCs returned.
    @param HpcList The list of Root HPCs. HpcCount defines the number of elements in this list.
    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
GetRootHpcList (
  IN EFI_PCI_HOT_PLUG_INIT_PROTOCOL    *This,
  OUT UINTN                            *HpcCount,
  OUT EFI_HPC_LOCATION                 **HpcList
  )
{

//  GPPHotPlug>>
   UINT8 PCIE_NUM=0;
   UINT8 i=0;
   EFI_HPC_LOCATION *PcieLocation;
   EFI_HPC_LOCATION *Hotptr;

   while (mPcieList[PCIE_NUM].PciRootPortNode.Device != 0xff) PCIE_NUM++;

   PcieLocation=MallocZ(PCIE_NUM*sizeof(EFI_HPC_LOCATION));

   Hotptr=PcieLocation;
   for (i=0;i<PCIE_NUM;i++ )
   {
    Hotptr->HpcDevicePath=(EFI_DEVICE_PATH_PROTOCOL *)&mPcieList[i];
    Hotptr->HpbDevicePath=(EFI_DEVICE_PATH_PROTOCOL *)&mPcieList[i];
    Hotptr++;
   }

  *HpcCount = PCIE_NUM;
  *HpcList  = PcieLocation;
//  <<GPPHotPlug
  return EFI_SUCCESS;
}

/**
    This procedure Initializes one Root Hot Plug Controller
    This process may casue initialization of its subordinate buses
        
    @param This The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
    @param HpcDevicePath The Device Path to the HPC that is being initialized.
    @param HpcPciAddress The address of the Hot Plug Controller function on the PCI bus.
    @param Event The event that should be signaled when the Hot Plug Controller initialization is complete. Set to NULL if the caller wants to wait until the entire initialization process is complete. The event must be of the type EFI_EVT_SIGNAL.
    @param HpcState The state of the Hot Plug Controller hardware. The type EFI_Hpc_STATE is defined in section 3.1.
    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
InitializeRootHpc (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL      *This,
  IN  EFI_DEVICE_PATH_PROTOCOL            *HpcDevicePath,
  IN  UINT64                              HpcPciAddress,
  IN  EFI_EVENT                           Event, OPTIONAL
  OUT EFI_HPC_STATE                       *HpcState
  )
{
  if (Event) {
    gBS->SignalEvent (Event);
  }

  *HpcState = EFI_HPC_STATE_INITIALIZED;

  return EFI_SUCCESS;
}

/**
    Returns the resource padding required by the PCI bus that is controlled by the specified Hot Plug Controller.
        
    @param This The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol. initialized.
    @param HpcDevicePath The Device Path to the Hot Plug Controller.
    @param HpcPciAddress The address of the Hot Plug Controller function on the PCI bus.
    @param HpcState The state of the Hot Plug Controller hardware. The type EFI_HPC_STATE is defined in section 3.1.
    @param Padding This is the amount of resource padding required by the PCI bus under the control of the specified Hpc. Since the caller does not know the size of this buffer, this buffer is allocated by the callee and freed by the caller.
    @param Attribute Describes how padding is accounted for.
    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
GetResourcePadding (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *HpcDevicePath,
  IN  UINT64                          HpcPciAddress,
  OUT EFI_HPC_STATE                   *HpcState,
  OUT VOID                            **Padding,
  OUT EFI_HPC_PADDING_ATTRIBUTES      *Attributes
  )
{
    ASLR_QWORD_ASD  *Resource;
    ASLRF_L_HDR     LargeResourceHdr;
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT8           RsvdExtraBusNum = RSVD_EXT_BUS; //2
    UINT8           RsvdPcieMegaMem = RSVD_PCI_MEM;//10;
    UINT8           RsvdPcieKiloIo = RSVD_PCI_IO; //4
//  GPPHotPlug>>
    UINT8           PCIE_NUM=0;

   while (mPcieList[PCIE_NUM].PciRootPortNode.Device != 0xff) PCIE_NUM++;
//  <<GPPHotPlug
    Resource = MallocZ(5*sizeof(ASLR_QWORD_ASD) + sizeof(ASLRF_L_HDR)); //P091214A
    ASSERT (Resource != NULL);

    *Padding = (VOID *)Resource;

    //
    // Check if PCIe Root Hob Controller need to reserve bus for docking downstream P2P hotplug
    //

    //--  PORT_HOPLUG_MASK


    LargeResourceHdr.Name       = ASLV_RT_QWORD_ASD;
    LargeResourceHdr.Type       = ASLV_LARGE_RES;
    LargeResourceHdr.Length     = sizeof(ASLR_QWORD_ASD)-sizeof(ASLRF_L_HDR);
    //
    // Padding for bus
    //
    *Attributes = EfiPaddingPciBus;

    Resource->Hdr            = LargeResourceHdr;
    Resource->Type           = ASLRV_SPC_TYPE_BUS;
    Resource->GFlags.GFLAGS  = 0x0;
    Resource->TFlags.TFLAGS  = 0;
    Resource->_MIN           = 0;
    Resource->_MAX           = 0;
    Resource->_LEN           = RsvdExtraBusNum;

    //
    // Padding for non-prefetchable memory
    //
    Resource++;
    Resource->Hdr            = LargeResourceHdr;
    Resource->Type           = ASLRV_SPC_TYPE_MEM;
    Resource->GFlags.GFLAGS  = 0x0;
    Resource->TFlags.TFLAGS  = 0;
    Resource->_GRA           = 32;
    Resource->_MIN           = 0;
    Resource->_MAX           = 1;
    Resource->_LEN           = RsvdPcieMegaMem * 0x100000;

    //
    // Padding for prefetchable memory
    //
    Resource++;
    Resource->Hdr                   = LargeResourceHdr;
    Resource->Type                  = ASLRV_SPC_TYPE_MEM;
    Resource->GFlags.GFLAGS         = 0x0;
    Resource->TFlags.MEM_FLAGS._MEM = ASLRV_MEM_CEPF; // Cacheable and Prefatchable
    Resource->_GRA                  = 32;
    Resource->_MIN                  = 0;
if (HpcDevicePath == (EFI_DEVICE_PATH_PROTOCOL *) &mPcieList[1] ) //Port 3 prfatchable memory
    Resource->_LEN                  = 0x20000000;
else
    Resource->_LEN                  = 0x10000000;

    //
    // Pad 16 MB of MEM
    //
    Resource->_MAX = 1;

    // Padding for I/O
    //
    Resource++;
    Resource->Hdr            = LargeResourceHdr;
    Resource->Type           = ASLRV_SPC_TYPE_IO;
    Resource->GFlags.GFLAGS  = 0x0;
    Resource->TFlags.TFLAGS  = 0;
    Resource->_MIN           = 0;
    Resource->_LEN           = RsvdPcieKiloIo * 0x400;
    //
    // Pad 4K of IO
    //
    Resource->_MAX = 1;

    // Terminate the entries.
    //
    Resource++;
    Resource->Hdr.HDR = ASLV_END_TAG_HDR;

    *HpcState = EFI_HPC_STATE_INITIALIZED | EFI_HPC_STATE_ENABLED;

    return Status;
}
#endif

/**
    This function  is a ready to boot event function ,it will did it
    when ready to boot

    @param Event 
    @param Context 

    @retval VOID

**/
VOID 
CRBReadyToBoot(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
	//
	// Test code for PERFORMANCE_MEASUREMENTS_SUPPORT.
	//    Let you know the accuracy of measurement time.
	//
    PERF_START (NULL,"CRB_PERFORMANCE_ONE_SECOND", NULL, 0);
    PERF_CODE (
    		gBS->Stall(1000000);
    );
    PERF_END (NULL,"CRB_PERFORMANCE_ONE_SECOND", NULL, 0);
    
    // Close Event and don't run it again
    pBS->CloseEvent(Event);
}


/**
    This function call back after EFI_ACPI_SDT_PROTOCOL is installed.

    @param Event
    @param Context

    @retval VOID

**/
VOID
CrbAcpiSdtCallBack (
	IN EFI_EVENT Event,
	IN VOID *Context
	)
{
    
    EFI_STATUS                  Status;
    EFI_PHYSICAL_ADDRESS        Dsdtaddr = 0;
    UINT64                      SystemMemoryAslAddr = 0;
    
    Status = LibGetDsdt(&Dsdtaddr, EFI_ACPI_TABLE_VERSION_ALL);
    if (!EFI_ERROR(Status)) {
        SystemMemoryAslAddr = (UINT64)gSystemMemoryAsl;
        DEBUG(( DEBUG_INFO, "  Crbdxe: SystemMemoryAslAddr = %x  \n",SystemMemoryAslAddr));
        UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "CRBR", SystemMemoryAslAddr);
    }
    DEBUG(( DEBUG_INFO, "  Crbdxe: Update ACPI table done. \n"));  
	gBS->CloseEvent(Event);
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
