//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file CrbPei.c
    This file contains code for Chipset Reference Board
    Template initialization in the PEI stage

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <PiPei.h>
#include <Ppi/CrbInfo.h>
#include <Library/PeiServicesLib.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Sb.h>
#include <Gnb.h>

// Consumed PPIs
#include <Ppi/ReadOnlyVariable2.h>
#include <Ppi/SbPpi.h>
#include <Ppi/SbChipsetPpi.h>
#include <Ppi/GnbPpi.h>
#include <Ppi/Smbus2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

    
UINT8
CrbPeiGetChipsetVendorNo (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

UINT32
CrbPeiGetCpuId (
  IN  CONST AMI_PEI_CRBINFO_PPI  	*This
);

UINT32
CrbPeiGetNorthBridgePciId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

UINT32
CrbPeiGetSouthBridgePciId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

CHAR8*
CrbPeiGetProjectId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

UINT16
CrbPeiGetBiosRevision (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
);

EFI_STATUS
CrbPeiCallBack(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
CrbRecoveryCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
CrbEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);


// GUID Definition(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
CHAR8 CONST ProjectTag[5] = CONVERT_TO_STRING(CRB_PROJECT_TAG);
AMI_GPIO_INIT_TABLE_STRUCT Crb1GpioTable [] = {
    //using CPM's Gpio table
    {0xffff, 0xffff}, // End of the table.
};

AMI_GPIO_INIT_TABLE_STRUCT Crb2GpioTable [] = {
    {0xffff, 0xffff}, // End of the table.
};

// PPI Definition(s)
AMI_PEI_CRBINFO_PPI	gAmiCrbInforPpi = {
	CrbPeiGetChipsetVendorNo,
	CrbPeiGetCpuId,
	CrbPeiGetNorthBridgePciId,
	CrbPeiGetSouthBridgePciId,
	CrbPeiGetProjectId,
	CrbPeiGetBiosRevision,
};

static EFI_PEI_PPI_DESCRIPTOR gCrbPpiList[] =  {
		{
        (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
		&gAmiPeiCrbInfoPpiGuid,
		&gAmiCrbInforPpi
		}
	};
AMI_GPIO_INIT_PPI Crb1GpioInitPpi = {
    0,          //GPIO_BASE_ADDRESS,
    Crb1GpioTable,
    sizeof (Crb1GpioTable) / sizeof (AMI_GPIO_INIT_TABLE_STRUCT) - 1,
    TRUE        //InitDefaultGpioSetting
};

AMI_GPIO_INIT_PPI Crb2GpioInitPpi = {
    0,          //GPIO_BASE_ADDRESS,
    Crb2GpioTable,
    sizeof (Crb2GpioTable) / sizeof (AMI_GPIO_INIT_TABLE_STRUCT) - 1,
    FALSE       //InitDefaultGpioSetting
};

AMI_SB_PCI_SSID_TABLE_STRUCT Crb1SbSsidTable[] = { 
    CRB1_SB_PCI_DEVICES_SSID_TABLE
};

AMI_GNB_PCI_SSID_TABLE_STRUCT Crb1GnbSsidTable[] = { 
    CRB1_GNB_PCI_DEVICES_SSID_TABLE
};

AMI_SB_PCI_SSID_TABLE_STRUCT Crb2SbSsidTable[] = { 
    CRB2_SB_PCI_DEVICES_SSID_TABLE
};

AMI_GNB_PCI_SSID_TABLE_STRUCT Crb2GnbSsidTable[] = { 
    CRB2_GNB_PCI_DEVICES_SSID_TABLE
};

static AMI_PEI_SB_CUSTOM_PPI Crb1SbCustomPpi = {
    &Crb1GpioInitPpi,
    Crb1SbSsidTable
};

static AMI_PEI_GNB_CUSTOM_PPI Crb1GnbCustomPpi = {
    Crb1GnbSsidTable
};

static AMI_PEI_SB_CUSTOM_PPI Crb2SbCustomPpi = {
    &Crb2GpioInitPpi,
    Crb2SbSsidTable
};

static AMI_PEI_GNB_CUSTOM_PPI Crb2GnbCustomPpi = {
    Crb2GnbSsidTable
};

// PPI that are installed

static EFI_PEI_PPI_DESCRIPTOR Crb1CustomPpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gAmiPeiGnbCustomPpiGuid, &Crb1GnbCustomPpi },
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiSbCustomPpiGuid, &Crb1SbCustomPpi },
};

static EFI_PEI_PPI_DESCRIPTOR Crb2CustomPpi[] = {
    { EFI_PEI_PPI_DESCRIPTOR_PPI, \
      &gAmiPeiGnbCustomPpiGuid, &Crb2GnbCustomPpi },
    { EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gAmiPeiSbCustomPpiGuid, &Crb2SbCustomPpi },
};

EFI_STATUS
CrbPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

// PPI that are notified
static EFI_PEI_NOTIFY_DESCRIPTOR  CrbNotifyList[] =
{
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK),
    &gEfiPeiBootInRecoveryModePpiGuid,
    CrbRecoveryCallback},
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK),
    &gEfiEndOfPeiSignalPpiGuid,
    CrbEndOfPeiCallback},
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmiPeiSbInitPolicyGuid,
    CrbPeiCallback}
};

// External Declaration(s)

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
CrbPeiGetChipsetVendorNo (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
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
CrbPeiGetCpuId (
  IN  CONST AMI_PEI_CRBINFO_PPI  	*This
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
CrbPeiGetNorthBridgePciId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
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
CrbPeiGetSouthBridgePciId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
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
CrbPeiGetProjectId (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
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
CrbPeiGetBiosRevision (
  IN  CONST AMI_PEI_CRBINFO_PPI  *This
  )
{
	return (CRB_PROJECT_MAJOR_VERSION << 8) | CRB_PROJECT_MINOR_VERSION;
}


/**
On Board TPM releated decode
**/
VOID
CrbOnBoardTpmInit ( VOID
  )
{

    UINT32 Addr  = 0;
// Set AGPIO76 As SPI_TPM_CS_L
    RW_MEM8(ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG76, 0x01,0); //SPI_TPM_CS_L
// Set RouteTpm2Spi.
    RW_PCI32_SB(FCH_LPC_REGA0,BIT3,0);
// Set TPM Decode
    RW_PCI32_SB(FCH_LPC_REG7C,BIT0 + BIT2 +BIT7,0);
    Addr = READ_PCI32_SB(FCH_LPC_REGA0);
    Addr &= 0xFFFFFF00; // Raven Spi_eSpi_BaseAddr is [31:8]. Refer to (PPR)for AMD Family 17h Model 10h, Revision A0 Processors Volume 3 of 3.
    RW_MEM8(Addr + FCH_SPI_MMIO_REG22, BIT0,0xF);

}

/**
On Board Lpc TPM GPIO setting
**/
VOID
CrbOnBoardLpcTpmGpioSetting ( VOID )
{
    // Set IOMUXx057 to AGPIO87
    RW_MEM8(ACPI_MMIO_BASE + IOMUX_BASE + 0x57, 0x02,0);
    // Set interrupt pin to PCD
    PcdSet32(PcdAmiTpm2CurrentIrqNum, (UINT32)0x57);
    
    //0x0 = Active-High: This interrupt is sampled when the signal is high, or true.
    //0x1 = Active-Low: This interrupt is sampled when the signal is low, or false.
    //0x2 = Active-Both: This interrupt is sampled on both rising and falling edges. Interrupt mode must be set to Edge-triggered.
    //0x3 = Reserved (do not use)
    PcdSet32(PcdAmiTpm2CurrentIrqActiveLevel, 0);//ActiveHigh

}

/**
On Board Spi TPM GPIO setting
**/
VOID
CrbOnBoardSpiTpmGpioSetting ( VOID )
{
    // Set IOMUXx08B [UART0_INTR_AGPIO139] to AGPIO139
    RW_MEM8(ACPI_MMIO_BASE + IOMUX_BASE + 0x8B, 0x01,0);
    // Set interrupt pin to PCD
    PcdSet32(PcdAmiTpm2CurrentIrqNum, (UINT32)0x8B);
    
    //0x0 = Active-High: This interrupt is sampled when the signal is high, or true.
    //0x1 = Active-Low: This interrupt is sampled when the signal is low, or false.
    //0x2 = Active-Both: This interrupt is sampled on both rising and falling edges. Interrupt mode must be set to Edge-triggered.
    //0x3 = Reserved (do not use)
    PcdSet32(PcdAmiTpm2CurrentIrqActiveLevel, 1);//Active-Low

}
/**
    This function is the entry point for CRB PEIM.
    It initializes the chipset CRB in PEI phase.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_STATUS EFI_SUCCESS

    @note  This routine is called very early, prior to SBPEI and NBPEI.
**/
EFI_STATUS
EFIAPI
CrbPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

#if CRB_CUSTOM_PPI_SUPPORT
	Status = (*PeiServices)->InstallPpi( PeiServices, Crb1CustomPpi );
	ASSERT_EFI_ERROR(Status);
#endif

    Status = (**PeiServices).NotifyPpi (PeiServices, &CrbNotifyList[0]);
    
    Status = PeiServicesInstallPpi(gCrbPpiList);


    {
        EFI_GUID        				SetupGuid = SETUP_GUID;
        EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable;
        UINTN                           VariableSize;
        SETUP_DATA                      SetupData;

        Status = PeiServicesLocatePpi(&gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable);
        ASSERT_EFI_ERROR(Status);

        VariableSize = sizeof(SETUP_DATA);
        Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);
        if (!EFI_ERROR(Status)) {
#if CRB_ONBOARD_TPM_SUPPORT
    #if defined(TCG2Support) && (TCG2Support != 0)
        // if turn on TPM and select TPM 1.2
        if (SetupData.TpmSupport == 1 ) {
            // 1 means SPI TPM.
             if (SetupData.fTPMSwitch == 2 ) CrbOnBoardTpmInit();
            // 0 means leave default - LPC TPM.
        } 
    #endif
#endif  //CRB_ONBOARD_TPM_SUPPORT
//#if defined(CRB_WHCK_DEBUG_CAPABILITY_TEST) && (CRB_WHCK_DEBUG_CAPABILITY_TEST == 1)
//		// This is a workaround for WHCK-Debug Capability test (EHCI).
//		// Due to CRB hardware limitation.
//		// The default capable of EHCI Debug port is port2 on Gardenia. But Gardenia does not have port2 layout.
//		//		The following workaround to change Gardenia layout. But it will cause some other side effect.
//		if (SetupData.CrbWhckEhciDebugPort) {
//#if defined (EHCI_DEBUG_PORT_SELECT) && (EHCI_DEBUG_PORT_SELECT != 0)
//		    UINT32			DebugPortSel = EHCI_DEBUG_PORT_SELECT; // 0: Disable \ 1: Port1 \ 2: Port2 \ 3: Port3 \ 4: Port4
//			UINTN	        Address;
//
//			Address = PCI_LIB_ADDRESS(0, (PCI_EHCI_DEV_FUNC_NUMBER >> 3), (PCI_EHCI_DEV_FUNC_NUMBER & 3), 0);
//			if (PciRead32(Address) != 0xFFFFFFFF) {
//				Address = PCI_LIB_ADDRESS(0, (PCI_EHCI_DEV_FUNC_NUMBER >> 3), (PCI_EHCI_DEV_FUNC_NUMBER & 3), 0x90);
//				DebugPortSel--; // 0 base data
//				DebugPortSel &= (BIT0 + BIT1);
//				DebugPortSel <<= 16; // BIT[16:17] of 0x90
//				PciAndThenOr32(Address, ~(BIT16 + BIT17), DebugPortSel);
//				// HubMuxDbgEn enable
//				PciAndThenOr32(Address, ~BIT18, BIT18);
//			}
//#endif
//		}
//#endif

        }
        

 //   if (SetupData.CrbSdConnector) {
 //       // Set AGPIO17 high to select FCH-SD
 //      RW_MEM8(ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG17, 0x02,0); //GPIo Function 2
 //       RW_MEM32(ACPI_MMIO_BASE + GPIO_BANK0_BASE + FCH_GPIO_REG17*4, BIT23+BIT22,0); //set output high
 //   }
    
    }


    return Status;
}

/**
    This function is called at end of PEI phase. It disables the
    ROM cache to avoid the problem with flash.


    @param PeiServices Pointer to PeiServices
    @param NotifyDesc Pointer to NotifyDesc
    @param InvokePpi 

    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
CrbPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{

    EFI_STATUS                         	Status;
    SETUP_DATA                         	SetupData;
    UINTN                              	VariableSize;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    EFI_GUID                           	SetupGuid= SETUP_GUID;

    Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gEfiPeiReadOnlyVariable2PpiGuid,
        0, NULL,
        &ReadOnlyVariable
    );
    ASSERT_PEI_ERROR(PeiServices, Status);

    VariableSize = sizeof(SETUP_DATA);
    Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &SetupGuid,
                                           NULL, &VariableSize, &SetupData);
    if (!EFI_ERROR(Status)) {
#if CRB_ONBOARD_TPM_SUPPORT
    #if defined(TCG2Support) && (TCG2Support != 0)
        if (SetupData.TpmSupport == 1 ) {
            if (SetupData.fTPMSwitch == 2 ) {
        	    // switch to Spi interface
            	CrbOnBoardTpmInit();
            }

        } 
    #endif
#endif  //CRB_ONBOARD_TPM_SUPPORT
        }
        

    //porting feature enable/disable here.
    // smi_reg hard coding
/*
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x02, 0x11);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x08, 0x04);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x09, 0x40);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x0a, 0x20);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x0d, 0x88);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x0e, 0x09);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x3c, 0x3c);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x47, 0x07);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x49, 0x09);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4a, 0x0a);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4b, 0x0b);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4c, 0x0c);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4d, 0x0d);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4e, 0x0e);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x4f, 0x0f);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x50, 0x10);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x51, 0x11);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x52, 0x12);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x53, 0x13);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x54, 0x14);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x55, 0x15);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x56, 0x16);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x57, 0x17);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x58, 0x18);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x59, 0x18);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x5a, 0x18);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x5b, 0x18);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x67, 0x1a);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x70, 0x02);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x78, 0x18);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x79, 0x18);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x98, 0xdb);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0x99, 0x77);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0xc5, 0x00);
    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0xc9, 0x00);

    WRITE_MEM8(SB_MMIO_BASE + SMI_BASE + 0xf0, 0x00);
*/

    return  EFI_SUCCESS;
}


EFI_STATUS
CrbEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS                          Status;
    SETUP_DATA                          SetupData;
    UINTN                               VariableSize;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable;
    EFI_GUID                            SetupGuid= SETUP_GUID;

    Status = (*PeiServices)->LocatePpi(
        PeiServices,
        &gEfiPeiReadOnlyVariable2PpiGuid,
        0, NULL,
        &ReadOnlyVariable
    );
    ASSERT_PEI_ERROR(PeiServices, Status);

    VariableSize = sizeof(SETUP_DATA);
    Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &SetupGuid,
                                           NULL, &VariableSize, &SetupData);
    if (!EFI_ERROR(Status)) {
#if CRB_ONBOARD_TPM_SUPPORT
    #if defined(TCG2Support) && (TCG2Support != 0)
        if (SetupData.TpmSupport == 1 ) {
            if (SetupData.fTPMSwitch == 2 ) {
                CrbOnBoardSpiTpmGpioSetting();
            }
            if (SetupData.fTPMSwitch == 1 ) {
                CrbOnBoardLpcTpmGpioSetting();
                // Clear SerialIrqConfig
                WRITE_MEM16(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG54, 0);
            }
        } 
    #endif
#endif  //CRB_ONBOARD_TPM_SUPPORT
    }
    return  Status;
}

EFI_STATUS
CrbRecoveryCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
//#if CRB_XHCI_RECOVERY_WORKAROUND 
//    EFI_PEI_PCI_CFG2_PPI       	*PciCfg;
//    EFI_PEI_CPU_IO_PPI          *CpuIo;
//    UINT32 VidDid =0; //VerdID DeviceId
//        
//    // Get pointer to the PCI config PPI
//    PciCfg = (*PeiServices)->PciCfg;
//    CpuIo = (*PeiServices)->CpuIo;
    

//This workaround only for the Gardenia Rev B
//use afudos xx.rom /p /b /n /recovery . the usb3.0 key image can't be loaded
//   VidDid = READ_PCI32_XHCI0(0x00);
//   if (VidDid !=0xFFFFFFFF) {
//      IoWrite8(0x80,0x06);//checkpoint
//      IoWrite8(0xcf9,0x06);// have a cf9 reset
//      EFI_DEADLOOP();
//   }
//#endif //CRB_XHCI_RECOVERY_WORKAROUND
    return  EFI_SUCCESS;
}


