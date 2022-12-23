//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//*************************************************************************
/** @file SbPei.c
    This file contains code for Template Southbridge initialization
    in the PEI stage

**/
//*************************************************************************

#include <PiPei.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

// Module specific Includes
#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <Sb.h>
#include "AmiCspLib.h"
#include <Hob.h>
#include <AmiChipsetIoLib.h>
#include <Guid/Rtc.h>
// Produced/used PPI interfaces
#include <Ppi/PciCfg2.h>
#include <Ppi/SbPpi.h>
#include <Ppi/CpuIo.h>
#include <Ppi/CspLibPpi.h>
#include <Ppi/SmmControl.h>
#if CAPSULE_SUPPORT
#include "AmiCspLib.h"
#endif
#if ATAPI_RECOVERY_SUPPORT
#include <Ppi/AtaController.h>
#endif

#include <Ppi/AmdFchInitPpi.h>
#include <Ppi/EndOfPeiPhase.h>
#include <Pci.h> //##<AAV> use the definition of MdePkg later.
#include <Library/AmdSocBaseLib.h>

#include <Ppi/SbPpi.h>
#include <Ppi/SbChipsetPpi.h>
#include <Library/AmdCapsuleLib.h>

// Portable Constants
AMI_SB_PCI_SSID_TABLE_STRUCT gDefaultSIdTbl[] = {SB_PCI_DEVICES_SSID_TABLE};

typedef struct {
    CHAR16*	        FchTypeStr;
    SOC_ID_STRUCT   SocId;
} FCH_SOC_ID;

FCH_SOC_ID CONST gFchSocIdTbl[] = {
    {L"Sandstone",      {F17_RV_RAW_ID, RV_FP5}},
    {L"Sandstone",      {F17_RV2_RAW_ID, RV_FP5}},
    {L"Sandstone",      {F17_PIC_RAW_ID, RV_FP5}},
    {L"Taishan",        {F17_ZP_RAW_ID, ZP_AM4}},
    {L"Kern",           {F15_BR_RAW_ID, BR_AM4}},
};

BOOLEAN gIsRtcValid = TRUE;

// Produced PPIs

// GUID Definitions

// Portable Constants

//----------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------
EFI_STATUS SBPEI_Board(EFI_FFS_FILE_HEADER*, EFI_PEI_SERVICES**);

VOID ProgramSbSsid (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI     *PciCfg
);

EFI_STATUS
SbEndOfFchCallBack(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
SbMasterBootModeCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
SbEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_STATUS
SbAgesaCallback(
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );


#if defined (XHCI_RECOVERY_PATH_MODE) && (XHCI_RECOVERY_PATH_MODE)
//EFI_GUID gXhciRecoveryFwGuid = XHCI_RECOVERY_FIRMWARE_GUID;
extern EFI_GUID  gAmiSbXhciRecoveryFirmwareFileGuid;
#endif


EFI_STATUS
UpdateBootMode(
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI  *PciCfg
    );

BOOLEAN
IsRecovery (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI  *PciCfg,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo
    );

#if ATAPI_RECOVERY_SUPPORT
EFI_STATUS
EFIAPI SBPEI_EnableAtaChannelForRecovery (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN PEI_ATA_CONTROLLER_PPI     *This,
  IN UINT8                      ChannelIndex
  );
#endif

#if     SMM_SUPPORT
EFI_STATUS
SBPEI_ActivateSMI (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_SMM_CONTROL_PPI *This,
    IN OUT INT8 *ArgumentBuffer OPTIONAL,
    IN OUT UINTN *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN Periodic OPTIONAL,
    IN UINTN ActivationInterval OPTIONAL
    );

EFI_STATUS
SBPEI_DeactivateSMI (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_SMM_CONTROL_PPI *This,
    IN BOOLEAN Periodic OPTIONAL
    );
#endif

EFI_STATUS SBPEI_Init_AfterMemInstalled (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                     *InvokePpi
);

#ifdef XHCI_Firmware_Support
#if XHCI_Firmware_Support
EFI_STATUS
sbFchRecoveryCallBack(
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );
#endif
#endif

BOOLEAN
SbGetCapsuleFlag (
  );

VOID SbWakeupTypeLib (
    VOID
);

VOID SbCheckPowerLoss (
    VOID
);

VOID SbAmdFchAmiPolicyPpiInstall (
    IN EFI_PEI_SERVICES         **PeiServices
);

VOID PeiInitRtc(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_CPU_IO_PPI           *CpuIo
);

//----------------------------------------------------------------------------
// Define everything related to RESET PPI here (function is defined at the end)
//----------------------------------------------------------------------------
#if SB_RESET_PPI_SUPPORT

#include <Ppi/Reset.h>
extern VOID SBLib_ResetSystem (IN EFI_RESET_TYPE ResetType);

EFI_STATUS SBPEI_ResetSystem (IN EFI_PEI_SERVICES **PeiServices);

EFI_GUID gPeiResetPpiGuid = EFI_PEI_RESET_PPI_GUID;

static  EFI_PEI_RESET_PPI mResetPpi =
    {
        SBPEI_ResetSystem
    };

#endif

#if SB_STALL_PPI_SUPPORT
#include <Ppi/Stall.h>

extern EFI_STATUS CountTime (IN UINTN DelayTime, IN UINT16 BaseAddr);

EFI_STATUS  SBPEI_Stall (IN EFI_PEI_SERVICES **PeiServices,
                        IN EFI_PEI_STALL_PPI *This, IN UINTN  Microseconds);

// Constants related to template Stall code
#define TIMER_RESOLUTION  1

static EFI_PEI_STALL_PPI mStallPpi =
    {
        TIMER_RESOLUTION,
        SBPEI_Stall
    };


#endif

// PPI interface definition

// PPI Definition
static  AMI_PEI_SBINIT_POLICY_PPI mAMIPEISBInitPolicyPpi =
    {
        TRUE
    };

static  AMI_PEI_SBINIT_POLICY_PPI mAtiPEISBInitPolicyPpi =
{
        TRUE
};

static EFI_PEI_PPI_DESCRIPTOR mBootModePpi[] =
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiMasterBootModePpiGuid,
    NULL
  };

static EFI_PEI_PPI_DESCRIPTOR mRecoveryModePpi[] =
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiBootInRecoveryModePpiGuid,
    NULL
  };
#if SMM_SUPPORT
static PEI_SMM_CONTROL_PPI mSmmControlPpi = {
    SBPEI_ActivateSMI,
    SBPEI_DeactivateSMI
};
#endif

#if ATAPI_RECOVERY_SUPPORT
static PEI_ATA_CONTROLLER_PPI mAtaControllerPpi =
{
    SBPEI_EnableAtaChannelForRecovery
};
#endif

AMI_GPIO_INIT_TABLE_STRUCT gAmiGpioInitTable[] =
{
    //  { GpioNo, GpioCfg}
    #include "SbGpio.h"
    {0xffff, 0xffff}, // End of the table.
};

// PPI that are installed
static EFI_PEI_PPI_DESCRIPTOR mPpiList[] = {
    // PPIs will be install after AMD SB init.
#if SMM_SUPPORT
    {EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gPeiSmmControlPpiGuid,
    &mSmmControlPpi},
#endif

#if ATAPI_RECOVERY_SUPPORT
    {EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gPeiAtaControllerPpiGuid,
    &mAtaControllerPpi},
#endif

    {(EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmiPeiSbInitPolicyGuid,
    &mAMIPEISBInitPolicyPpi}
};

static EFI_PEI_PPI_DESCRIPTOR mPpiList2[] = {
    {(EFI_PEI_PPI_DESCRIPTOR_PPI
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiStallPpiGuid,
    &mStallPpi}
};

static EFI_PEI_NOTIFY_DESCRIPTOR  NotifyList[] =
{
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK),
    &gEfiPeiMasterBootModePpiGuid,
    SbMasterBootModeCallback},
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK),
    &gEfiEndOfPeiSignalPpiGuid,
    SbEndOfPeiCallback},
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gAmdFchInitPpiGuid,
    SbEndOfFchCallBack}
};

static EFI_PEI_NOTIFY_DESCRIPTOR MemInstalledNotifyList[] = {
    { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
      EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST, \
      &gEfiPeiMemoryDiscoveredPpiGuid, SBPEI_Init_AfterMemInstalled },
};

//=============================================================================
// Function Definition
//=============================================================================
/**
    This function determines if the system is resuming from an S3
    sleep state.

    @param VOID


    @retval TRUE It is an S3 Resume
    @retval FALSE It is not an S3 Resume

**/
BOOLEAN SbSocIsS3(VOID)
{
    return (SbGetSleepType() == BOOT_ON_S3_RESUME) ? TRUE : FALSE;
}


/**
    This function is the entry point for this PEI. This function
    initializes the chipset SB

    @param FfsHeader Pointer to the FFS file header
    @param PeiServices Pointer to the PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  This function should initialize South Bridge for memory detection.
              Install AMI_PEI_SBINIT_POLICY_PPI to indicate that SB Init PEIM
              is installed
              Following things can be done at this point:
                  - Enabling top of 4GB decode for full flash ROM
                  - Programming South Bridge ports to enable access to South
                      Bridge and other I/O bridge access

**/
EFI_STATUS
EFIAPI
SbPeiInit (
  IN EFI_PEI_FILE_HANDLE   FileHandle,	
  IN CONST EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS                  Status;
    UINTN                       i;
#if defined CREATE_CMOS_BAD_HOB && CREATE_CMOS_BAD_HOB != 0
    UINT16                      HobSize = sizeof(CMOS_BAD_HOB);
    CMOS_BAD_HOB                *CmosBadHob;
#endif

    DEBUG ((DEBUG_INFO|DEBUG_INIT|DEBUG_CHIPSET, "AMI SB PEIM start\n"));

    // Check Hardware Identification
    for (i = 0; i < sizeof(gFchSocIdTbl)/sizeof(FCH_SOC_ID); i++) {
        if (SocHardwareIdentificationCheck (&gFchSocIdTbl[i].SocId)) {
            UINTN	Size = StrSize(gFchSocIdTbl[i].FchTypeStr);

            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"    <SbPei> : The FCH of this platform is %s\n", gFchSocIdTbl[i].FchTypeStr));

            PcdSetPtrS(AmiPcdSbFchTypeString, &Size, gFchSocIdTbl[i].FchTypeStr);
            break;
        }
    }
    
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
        if (!SbSocIsS3()){
            SbSmnRw (0, 0x16D8012C, 0, 0); //XHCI 0 Port 
            SbSmnRw (0, 0x16F8012C, 0, 0); //XHCI 1 Port 
        }  
#endif  


    gIsRtcValid = SbIsRtcPwrValid();
#if defined CREATE_CMOS_BAD_HOB && CREATE_CMOS_BAD_HOB != 0
      Status = (*PeiServices)->CreateHob( PeiServices,
                                          EFI_HOB_TYPE_GUID_EXTENSION,
                                          HobSize,
                                          &CmosBadHob);
      if(!EFI_ERROR(Status)) {
        CmosBadHob->Header.Name = gAmiCmosBadHobGuid;
        CmosBadHob->Health = gIsRtcValid;
      }   
#endif

    SbCheckPowerLoss();

    SbWakeupTypeLib();

    SBPEI_Board(FileHandle, PeiServices);

    Status = (**PeiServices).NotifyPpi (PeiServices, &NotifyList[0]);
    ASSERT_PEI_ERROR (PeiServices, Status);

    {
        UINT8 DebBuf;
        UINT32 TpmEnableReg;
        
        EFI_GUID                        SetupGuid = SETUP_GUID;
        EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable = NULL;
        UINTN                           VariableSize;
        SETUP_DATA                      SetupData;
        EFI_STATUS                      VariableStatus;
        UINT8                           TpmDecode = 0;
        
        
        //  Enable FCH ACPI MMIO
        //  The reason why coding here is SMBUS PPI should be available before AmdInitEarly.
        //  But the SMBUS PEIM will read SMBUS base from FCH ACPI MMIO.
        //  We should remove if AMD-FCH has generic solution.
        IoWrite8(PM_IO_INDEX,FCH_PMIOA_REG04);
        DebBuf = IoRead8(PM_IO_DATA) | BIT01;
        IoWrite8(PM_IO_DATA, DebBuf);
    
        //
        // TPM related decode.
        //
        VariableStatus = (*PeiServices)->LocatePpi(
                             PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL,
                             &ReadOnlyVariable );
        
        if (!EFI_ERROR(VariableStatus)) {
            VariableSize = sizeof(SETUP_DATA);
            VariableStatus = ReadOnlyVariable->GetVariable(ReadOnlyVariable, L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);
            if (!EFI_ERROR(VariableStatus)) {
                // If support TPM, check fTPMSwitch to decide to decode TPM or not
                if (SetupData.TpmSupport == 1) {
                    switch (SetupData.fTPMSwitch) {
                    case 0: //fTPM
                        TpmDecode = 0;
                        break;
                    case 1: //dTPM LPC
                    case 2: //dTPM SPI
                        TpmDecode = 1;
                        break;
                    default: // Do nothing
                        break;
                    }
                }
            }
        }
        // Enable/Disable TPM related decode.
        if (TpmDecode == 0) {
            TpmEnableReg = READ_PCI32_SB(FCH_LPC_REG7C);
            TpmEnableReg &= ~(UINT32)( BIT0 + BIT2 ); // Clear BIT0,2
            WRITE_PCI32_SB(FCH_LPC_REG7C, TpmEnableReg);        
        } else {
            TpmEnableReg = READ_PCI32_SB(FCH_LPC_REG7C);
            TpmEnableReg |= ( BIT0 + BIT2 ); // Set BIT0,2
            WRITE_PCI32_SB(FCH_LPC_REG7C, TpmEnableReg); 
        }
    
    }


#if AMD_SB_SIO_PME_BASE_WORKAROUND //1 //###defined(SIO_SUPPORT) && SIO_SUPPORT
    // AVA9 : AMD FCH reference code has provided PcdAmdFchCfgSioPmeBaseAddress Pcd to override.
    // Remove the workaround.
#endif

#if SB_STALL_PPI_SUPPORT
    Status = (*PeiServices)->InstallPpi(PeiServices, &mPpiList2[0]); //Install Stall PPi
    ASSERT_PEI_ERROR(PeiServices, Status);
#endif

    // Due to the workaround of AMD reference source (Disabling the RTC Daylight Saving Time Feature v2.0) (FchInitResetHwAcpi)
    // the setting about "DISABLE_DAYLIGHT_SAVINGS" move to (SbEndOfFchCallBack)

    //Supply Ppi to hook GPIO program in CPM table. SbGpio.h
    SbAmdFchAmiPolicyPpiInstall(PeiServices);

    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "End of AMI SB PEIM  \n"));
    return EFI_SUCCESS;
}

/**
    This function programs SB PCI devices sub-vendor ID and
    sub-system ID.

    @param PeiServices Pointer to the PEI services table
    @param PciCfg Pointer to the PCI Configuration PPI

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  1. This routine only programs the PCI device in SB, hence, we
                 have to check the bus/device/function numbers whether they
                 are a SB PCI device or not.
              2. This routine is invoked by PEI phase.

**/

VOID ProgramSbSsid (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_PCI_CFG2_PPI      *PciCfg )
{
    EFI_STATUS                  	Status;
    AMI_PEI_SB_CUSTOM_PPI       	*SBPeiOemPpi;
    AMI_SB_PCI_SSID_TABLE_STRUCT 	volatile *SsidTblPtr = gDefaultSIdTbl;
    UINTN							i;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gAmiPeiSbCustomPpiGuid, \
                                        0, \
                                        NULL, \
                                        &SBPeiOemPpi );

    if (Status == EFI_SUCCESS) {
        if (SBPeiOemPpi->SsidTable != NULL) {
            SsidTblPtr = SBPeiOemPpi->SsidTable;
		#if defined(DYNAMIC_PCIE_SSID_SUPPORT) && (DYNAMIC_PCIE_SSID_SUPPORT == 1)
            // AVA9 : AGESAv9-FCH has provide SSID PCD. Previous implement is not required.
		#endif
        }
    }

    i = 0;
    while (SsidTblPtr[i].PciAddr != 0xffffffffffffffff) {
    	SB_FCH_DEV	SbFchDev = SsidTblPtr[i].PciAddr;
    	UINT32		Ssid = SsidTblPtr[i].Sid;
    	switch (SbFchDev) {
    	// Sandstone only.
    	case SB_FCH_DEV_SS_SATA_AHCI:
    		if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_SATA_AHCI:
			if (Ssid == -1) Ssid = (FCH_SATA_AHCI_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdSataAhciSsid, Ssid);
			break;

		case SB_FCH_DEV_SS_SATA_IDE:
			if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_SATA_IDE:
			if (Ssid == -1) Ssid = (FCH_SATA_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdSataIdeSsid, Ssid);
			break;

		case SB_FCH_DEV_SS_SMBUS:
			if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_SMBUS:
			if (Ssid == -1) Ssid = (FCH_SMBUS_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdSmbusSsid, Ssid);
			break;

		case SB_FCH_DEV_SS_LPC:
			if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_LPC:
			if (Ssid == -1) Ssid = (FCH_LPC_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdLpcSsid, Ssid);
			break;

		case SB_FCH_DEV_SS_XHCI1:
			if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_XHCI1:
			if (Ssid == -1) Ssid = (FCH_USB_XHCI_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdXhciSsid, Ssid);
			break;

		case SB_FCH_DEV_SS_SD:
			if (!CSP_IS_ZP_FCH_MACRO) break;
		case SB_FCH_DEV_SD:
			if (Ssid == -1) Ssid = (FCH_SD_DID << 16) + AMD_FCH_VID;
			PcdSet32S(PcdSdSsid, Ssid);
			break;

		default :
			break;
    	}

    	i++;
    }

}

/**
    This function can be used to program any SB regisater after
    PEI permantent memory be installed.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDescriptor Pointer to the descriptor for the
        notification event.
    @param InvokePpi Pointer to the PPI that was installed

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS SBPEI_Init_AfterMemInstalled (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
    IN VOID                         *InvokePpi )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_PEI_PCI_CFG2_PPI     	*PciCfg;
    EFI_BOOT_MODE           	BootMode;

    PciCfg = (*PeiServices)->PciCfg;

    PEI_PROGRESS_CODE (PeiServices, PEI_MEM_SB_INIT);

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    if (BootMode != BOOT_ON_S3_RESUME) {
        //
        // Program SB Devices' Subsystem Vendor ID & Subsystem ID
        //
        ProgramSbSsid( PeiServices, PciCfg );
    }

    return  Status;
}



/**
    This function determines if the previous shut down
    was caused by PwrButton.

    @param VOID

    @retval TRUE If it is Powerbutton Shutdown
    @retval FALSE if it is not a Powerbutton Shutdown

**/
BOOLEAN isPowerButtonShutdown(VOID)
{
    BOOLEAN     IsPwrButtonShutdown = FALSE;
    UINT8       PMxC4;

    // Select PMxC0 [S5/Reset Status] to be S5/Reset Status register.
    PMxC4 = READ_IO8_PMIO(FCH_PMIOA_REGC4);
    RW_IO8_PMIO(FCH_PMIOA_REGC4,0,BIT2);

    // BIT2: the previous shut down was caused by PwrButton.
    if (READ_IO8_PMIO(FCH_PMIOA_REGC0) & BIT2 ) IsPwrButtonShutdown = TRUE;

    // Restore value of PMxC4
    WRITE_IO8_PMIO(FCH_PMIOA_REGC4, PMxC4);

    return IsPwrButtonShutdown;
}

#if KBC_SUPPORT && Recovery_SUPPORT

#define KBC_IO_DATA             0x60    // Keyboard Controller Data Port
#define KBC_IO_STS              0x64    // Keyboard Controller Status Port

#define IO_DELAY_PORT           0xed    // Use for I/O delay

/**
    This function resets Keyboard controller for Ctrl-Home
    recovery function.

    @param PeiServices Pointer to the Pei Services function and
        data structure
    @param CpuIo Pointer to the CPU I/O PPI
    @param PciCfg Pointer to the PCI Configuration PPI

    @retval VOID

    @note  No porting required.
**/

VOID ResetKbc (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI *PciCfg )

{
    volatile UINT8      KbcSts = 0;
    volatile UINT8      Buffer8;
    UINT32              TimeOut = 0x100;

    // Reset KBC
    if (CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ) != 0xff) {
        // Clear KBC buffer
        do {
            // cppcheck-suppress unreadVariable
            Buffer8 = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_DATA );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            TimeOut--;
        } while ((KbcSts & 3) && (TimeOut != 0));


        // Send BAT command
        CpuIo->IoWrite8( PeiServices, CpuIo, KBC_IO_STS, 0xaa ); // 0x64

        // IBFree
        for (TimeOut = 0; TimeOut < 0x1000; TimeOut++) {
            CpuIo->IoWrite8( PeiServices, CpuIo, IO_DELAY_PORT, KbcSts );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            if ((KbcSts & 2) == 0) break;
        }

        // OBFree
        for (TimeOut = 0; TimeOut < 0x500; TimeOut++) {
            CpuIo->IoWrite8( PeiServices, CpuIo, IO_DELAY_PORT, KbcSts );
            KbcSts = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
            if (KbcSts & 1) break;
        }

        // Get result if needed
        if (KbcSts & 1)
            // cppcheck-suppress unreadVariable
            Buffer8 = CpuIo->IoRead8( PeiServices, CpuIo, KBC_IO_DATA );
    }

    // Clear KBC status buffer.
    KbcSts = CpuIo->IoRead8 ( PeiServices, CpuIo, KBC_IO_STS ); // 0x64
}
#endif

/**
    This function determines the boot mode of the system.  After
    the correct boot mode has been determined, the PEI Service
    function SetBootMode is called and then the
    MasterBootModePpi is installed

    @param PeiServices Pointer to the Pei Services data structure
    @param CpuIo Pointer to the CPU I/O PPI
    @param PciCfg Pointer to the PCI Config PPI

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
UpdateBootMode(
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_CPU_IO_PPI   *CpuIo,
    IN EFI_PEI_PCI_CFG2_PPI  *PciCfg
    )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    EFI_BOOT_MODE       AmdBootMode, SbBootMode;

    // EFI_PEI_MASTER_BOOT_MODE_PEIM_PPI will be handle by AMD reference code
    //   (BOOT_ON_S4_RESUME/BOOT_ON_S3_RESUME/BOOT_WITH_FULL_CONFIGURATION).
    // We handle recovery mode and other exception.
    Status = (*PeiServices)->GetBootMode (PeiServices, &AmdBootMode);
    if (EFI_ERROR(Status)) SbBootMode = BOOT_WITH_FULL_CONFIGURATION;

    SbBootMode = AmdBootMode;
    if (SbBootMode == BOOT_ON_S4_RESUME || SbBootMode == BOOT_ON_S3_RESUME)
    {
        // the previous shut down was caused by PwrButton not sleep.
        if (isPowerButtonShutdown()) SbBootMode = BOOT_WITH_FULL_CONFIGURATION;
    }

    // Returns 0 if no S3 resume detected returns -1 if this is an S3 boot
    if (SbBootMode != BOOT_ON_S3_RESUME)
    {
        #if KBC_SUPPORT && Recovery_SUPPORT
        ResetKbc(PeiServices,  CpuIo, PciCfg);
        #endif
    }

//#if defined (FLASH_UPDATE_BOOT_SUPPORTED) && (FLASH_UPDATE_BOOT_SUPPORTED)
    if (SbGetCapsuleFlag() && AmdCapsuleGetStatus()) {
    	SbBootMode = BOOT_ON_FLASH_UPDATE;
    }
//#endif

#if CAPSULE_SUPPORT
    if(!EFI_ERROR(CheckIfCapsuleAvailable()))
        SbBootMode = BOOT_ON_FLASH_UPDATE;
#endif

#if FORCE_RECOVERY
    SbBootMode = BOOT_IN_RECOVERY_MODE;
#endif //FORCE_RECOVERY

    if(SbBootMode != BOOT_ON_S4_RESUME && SbBootMode != BOOT_ON_S3_RESUME
    	#if defined(CAPSULE_RESET_MODE) && CAPSULE_RESET_MODE == 0
    		&& SbBootMode != BOOT_ON_FLASH_UPDATE /* AVA9 : Append BOOT_ON_FLASH_UPDATE in the following condition due to AgesaV9 has different behavior. The AmdCcxXvPei will detect wake up type.*/
		#endif
			){
        RESET_IO16_PM(ACPI_IOREG_PM1_CNTL, 0x1C01); // Clear the SLP_TYP and SCI_EN of PmControl
    }

    //
    // Update recovery boot mode
    //
    if (SbBootMode != BOOT_ON_S3_RESUME && SbBootMode != BOOT_ON_FLASH_UPDATE) {
        if (IsRecovery(PeiServices, PciCfg, CpuIo)) {
        	SbBootMode = BOOT_IN_RECOVERY_MODE;
        }
    }

    // Set the system BootMode
    if (AmdBootMode != SbBootMode) {
        Status = (*PeiServices)->SetBootMode(PeiServices, SbBootMode);
        ASSERT_PEI_ERROR (PeiServices, Status);
    }

/*    DEBUG_CODE (
        switch (SbBootMode) {
            case BOOT_ON_FLASH_UPDATE:
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_ON_FLASH_UPDATE \n"));
                break;
            case BOOT_IN_RECOVERY_MODE:
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_IN_RECOVERY_MODE \n"));
                break;
            case BOOT_ON_S3_RESUME:
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_ON_S3_RESUME \n"));
                break;
            case BOOT_ON_S4_RESUME:
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_ON_S4_RESUME \n"));
                break;
            case BOOT_ON_S5_RESUME:
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_ON_S5_RESUME \n"));
                break;
            default :
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Boot mode is BOOT_WITH_FULL_CONFIGURATION \n"));
                break;
        }
    )
*/
    // Let everyone know that boot mode has been determined by installing the
    //  MasterBootMode PPI
    (*PeiServices)->InstallPpi(PeiServices, mBootModePpi);

    return Status;
}

//----------------------------------------------------------------------------


#if SB_RESET_PPI_SUPPORT

/**
    This function is the reset call interface function published
    by the reset PPI

    @param PeiServices Pointer to the PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SBPEI_ResetSystem (
    IN EFI_PEI_SERVICES **PeiServices
)
{

    SBLib_ResetSystem(SB_COLD_RESET);

    // We should never get this far
    return EFI_SUCCESS;
}

#endif


#if SB_STALL_PPI_SUPPORT

/**
    This function is used to stall the boot process (provides delay)
    for specified number of microseconds

    @param PeiServices Pointer to the PEI services table
    @param This Pointer to the Stall PPI
    @param MicroSeconds Time to wait for (in Micro seconds)

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SBPEI_Stall (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN EFI_PEI_STALL_PPI    *This,
    IN UINTN                MicroSeconds)
{
    EFI_STATUS              Status = EFI_UNSUPPORTED;

    // #### <AAV> to be check further ###
    // CPM will call Stall-PPI before AmdProccessInitPeim
    //	so the PM-IO didn't decode. we will get error.
    //  the PM-IO decoded will be handle by AMD reference.
    //  we didn't decode it here because of we don't want to change the register behavior.
    //  instead we use the IO delay when the PM-timer didn't get ready.
    if (IoRead16(PM_BASE_ADDRESS) == 0xFFFF) {
		UINTN                   uSec = 0;
		uSec = MicroSeconds / 4;
		while (uSec != 0) {
		    IoRead8(0x80);
			uSec--;
		}

		Status = EFI_SUCCESS;
    }

    if (EFI_ERROR(Status)) {
		// At this time no manipulation needed.  The value passed in is in
		//  MicroSeconds(us) and that is what the library function uses

		// Call Library function that is shared with Metronome
		//  Architecture Protocol

		Status = CountTime(MicroSeconds, PM_BASE_ADDRESS);
    }

    return Status;
}

#endif

#if ATAPI_RECOVERY_SUPPORT

#define     TEMP_BASE       0xF000
#define     TEMP_BASE2      0xE000

EFI_GUID gIdeRecoveryNativeModePpiGuid = PEI_IDE_RECOVERY_NATIVE_MODE_PPI_GUID;

PEI_IDE_RECOVERY_NATIVE_MODE_PPI IdeRecoveryNativeModePpi = {
   TEMP_BASE + 0x100,
   TEMP_BASE + 0x202,
   TEMP_BASE + 0x300,
   TEMP_BASE + 0x402
};

EFI_PEI_PPI_DESCRIPTOR IdeRecoveryNativeModePpiDescriptor = {
   (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
   &gIdeRecoveryNativeModePpiGuid,
   &IdeRecoveryNativeModePpi
};

/**
    This function is used to initialize the IDE ATA channel
    for BIOS recovery from ATA devices

    @param PeiServices Pointer to the PEI services table
    @param This Pointer to the PEI ATA Controller PPI
    @param ChannelMask Bit flag indicating which channel has to be
        enabled. The following is the bit definition:
        Bit0    IDE Primary
        Bit1    IDE Secondary
        Bit2    No SATA
        Bit3    SATA as Primary
        Bit4    SATA as Secondary

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS SBPEI_EnableAtaChannelForRecovery (
    IN EFI_PEI_SERVICES               **PeiServices,
    IN PEI_ATA_CONTROLLER_PPI         *This,
    IN UINT8                          ChannelMask
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32     TempSataBar5Add = TEMP_SATA_BAR5_ADDRESS;
    
    // Mem and IO space
    //
    SET_PCI8_SATA(FCH_SATA_REG04, BIT0+BIT1+BIT3);

    WRITE_PCI32_SATA(FCH_SATA_REG10, IdeRecoveryNativeModePpi.PCMDBarAddress);
    WRITE_PCI32_SATA(FCH_SATA_REG14, IdeRecoveryNativeModePpi.PCNLBarAddress &~ 2);
    WRITE_PCI32_SATA(FCH_SATA_REG18, IdeRecoveryNativeModePpi.SCMDBarAddress);
    WRITE_PCI32_SATA(FCH_SATA_REG1C, IdeRecoveryNativeModePpi.SCNLBarAddress &~ 2);

    // Below unused IO base, But some base register default is 0
    // that will cause legacy DMA controller fail.
    WRITE_PCI32_SATA(FCH_SATA_REG20, TEMP_BASE2 + 0x500); // fill temproary base

    WRITE_PCI32_SATA(FCH_SATA_REG24, TempSataBar5Add); // fill temproary  BAR5 base

    // Clear AHCI Enable during POST time. DE is investigating when/how to restore this bit before goes to OS boot.
    RW_MEM32 (TempSataBar5Add + FCH_SATA_BAR5_REG04,0,BIT31); 
      
    //-----------------------
    // Native IDE mode (SATA)
    //-----------------------
    RW_PCI32_SATA(FCH_SATA_REG40,BIT0,0); //SubclassCodeWriteEnable: 
    // BIT00 == SATA enable (HW : Default)
    
    WRITE_PCI32_SATA(FCH_SATA_REG08, 0x01018F40); //Program IDE Mode
     
    WRITE_PCI16_SATA(FCH_SATA_REG02, FCH_SATA_DID); // Program IDE mode DID

    RW_PCI32_SATA(FCH_SATA_REG40,0,BIT0); //SubclassCodeWriteDisable
    
    // Install PPI for native mode
    Status = (**PeiServices).InstallPpi (
                                        PeiServices,
                                        &IdeRecoveryNativeModePpiDescriptor);
    if (EFI_ERROR (Status)) return Status;

    return EFI_SUCCESS;
}

#endif //  ATAPI_RECOVERY_SUPPORT


#if     SMM_SUPPORT

/**
    This function is used to generate S/W SMI in the system. This
    call is mainly used during S3 resume to restore SMMBase

    @param PeiServices Pointer to the PEI services table
    @param This Pointer to the SMM Control PPI
    @param ArgumentBuffer Argument to be used to generate S/W SMI
    @param ArgumentBufferSize Size of the argument buffer
    @param Periodic Indicates the type of SMI invocation
    @param ActivationInterval If it is periodic invocation, this field
        indicates the period at which the SMI is generated

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SBPEI_ActivateSMI (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN PEI_SMM_CONTROL_PPI  *This,
    IN OUT INT8             *ArgumentBuffer OPTIONAL,
    IN OUT UINTN            *ArgumentBufferSize OPTIONAL,
    IN BOOLEAN              Periodic OPTIONAL,
    IN UINTN                ActivationInterval OPTIONAL
)
{
    UINT8       SmiCmd8;
    UINT16      SmiCmd16, Value16;

    if (Periodic || ((NULL != ArgumentBuffer) && (NULL == ArgumentBufferSize))) {
      return EFI_INVALID_PARAMETER;
    }
    if (NULL == ArgumentBuffer) {
        SmiCmd8 = 0xff;
        SmiCmd16 = 0xffff;
    } else {
        SmiCmd8 = ArgumentBuffer[0];
        SmiCmd16 = (ArgumentBuffer[1] << 8) + ArgumentBuffer[0];
    }

    // Enable ACPI MMIO space
    SET_IO8_PMIO(FCH_PMIOA_REG04, BIT1);

    // Making sure SW SMI port is SW_SMI_IO_ADDRESS
    Value16 = READ_MEM16(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
    while(Value16 != SW_SMI_IO_ADDRESS) {
        WRITE_MEM16(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A, SW_SMI_IO_ADDRESS);
        Value16 = READ_MEM16(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
    }

    // Enable CmdPort SMI
	RW_MMIO32_SMI(FCH_SMI_REGB0, BIT23 + BIT22, BIT22);

	//
	// Clear SmiEnB to enable SMI function
	//
	RESET_MMIO32_SMI(FCH_SMI_REG98, BIT31);

	//
	// Set the EOS Bit
	//
	SET_MMIO32_SMI(FCH_SMI_REG98, BIT28);

    // Trigger command port SMI
    if (*ArgumentBufferSize == 2) {
        IoWrite16 (SW_SMI_IO_ADDRESS, SmiCmd16);
    } else {
        IoWrite8 (SW_SMI_IO_ADDRESS, SmiCmd8);
    }

    return EFI_SUCCESS;
}

/**
    This function is used to clear the SMI and issue End-of-SMI

    @param PeiServices Pointer to the PEI services table
    @param This Pointer to the SMM Control PPI
    @param Periodic Indicates the type of SMI invocation to stop

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SBPEI_DeactivateSMI (
    IN EFI_PEI_SERVICES     **PeiServices,
    IN PEI_SMM_CONTROL_PPI  *This,
    IN BOOLEAN              Periodic OPTIONAL
)
{
    if (Periodic) {
      return EFI_INVALID_PARAMETER;
    }

    // Clear SmiCmdPort Status Bit
    WRITE_MMIO32_SMI(FCH_SMI_REG88, BIT11);

    // Set the EOS Bit
    SET_MMIO32_SMI(FCH_SMI_REG98, BIT28);

    return EFI_SUCCESS;
}
#endif

/**
    This function is used to call back after AMD SB init.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDesc 
    @param InvokePpi 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SbEndOfFchCallBack(
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
    EFI_STATUS          	Status = EFI_SUCCESS;
    EFI_PEI_PCI_CFG2_PPI 	*PciCfg = (*PeiServices)->PciCfg;
    EFI_PEI_CPU_IO_PPI      *CpuIo = (*PeiServices)->CpuIo;
    EFI_BOOT_MODE           BootMode;

    //
    // update boot mode
    //
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "updating boot mode....\n"));
    Status = UpdateBootMode(PeiServices, CpuIo, PciCfg);
    ASSERT_PEI_ERROR (PeiServices, Status);

    PeiInitRtc( PeiServices, CpuIo );

    Status = (*PeiServices)->NotifyPpi( PeiServices, MemInstalledNotifyList );
    ASSERT_PEI_ERROR ( PeiServices, Status );

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR (PeiServices, Status);

    // EIP310737 refer to (Chipset Template EIP311788)
    if (BootMode == BOOT_ON_S3_RESUME) {
        #if defined AMI_CSP_IO_PORT_CHECK && AMI_CSP_IO_PORT_CHECK
    	UINT8                       Index;
		UINT8                       IoPort[] = {0x26, 0x27, 0x2A, 0x2B};
        for(Index = 0; Index < sizeof(IoPort)/sizeof(UINT8); Index++) {
        	if (IoRead8 (IoPort[Index]) != 0xFF) {
                // Hang the system while the read value from IO Port 0x26,0x27,0x2A,0x2B is not 0xFF.
                // IO Port 0x26,0x27,0x2A,0x2B should not be occupied by any PCI controller.
                // It is for debug purpose and the system should not come to here.
                DEBUG ((DEBUG_ERROR, "Error!! IO Port 0x26,0x27,0x2A,0x2B is occupied by other PCI controller\n"));
                IoWrite8 (0x80, 0xEE);
                while (1);
            }
        }
        #endif
    }
    // End of EIP310737

#if defined (USBPEI_SUPPORT) && (USBPEI_SUPPORT)
#if defined (USB_PEI_KEYBOARD_SUPPORT) && (USB_PEI_KEYBOARD_SUPPORT)
#if defined (XHCI_Firmware_Support) && (XHCI_Firmware_Support)
    if (BootMode != BOOT_ON_S3_RESUME){
		// When Usb Pei was enabled and required keyboard function in Pei phase
		// We should always initialize XHCI in early stage.
		Status = sbFchRecoveryCallBack(PeiServices, NotifyDesc, InvokePpi);
		ASSERT_PEI_ERROR (PeiServices, Status);
    }
#endif //XHCI_Firmware_Support
#endif //USB_PEI_KEYBOARD_SUPPORT
#endif //USBPEI_SUPPORT

#if defined DISABLE_DAYLIGHT_SAVINGS && DISABLE_DAYLIGHT_SAVINGS != 0
    // PMx5F_x00 RTCEXT DltSavEnable
    WRITE_IO8_PMIO(FCH_PMIOA_REG5E, 0);
    SET_IO8_PMIO(FCH_PMIOA_REG5F, BIT0);
    // Enable The RTC register 72/73 0xB[0].
    WRITE_IO8_AMD_RTC(0xB, READ_IO8_AMD_RTC(0xB) | BIT0);
#endif

    //
    // Install the SB Init Policy PPI
    //
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Installing SB PEI services\n"));
    Status = (*PeiServices)->InstallPpi(PeiServices, &mPpiList[0]);
    ASSERT_PEI_ERROR (PeiServices, Status);

    return Status;
}

#if SUPPORT_RAID_DRIVER
/**
    This function provides SATA Port Information

    @param PeiServices Pointer to the PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

VOID DetectSataPortInfo (
    IN EFI_PEI_SERVICES     **PeiServices)
{
    EFI_STATUS          Status;
    UINT16              HobSize = sizeof(SATA_PRESENT_HOB);
    EFI_GUID            SataPresentHobGuid = AMI_SATA_PRESENT_HOB_GUID;
    SATA_PRESENT_HOB    *SataPresentHob;
    UINT8               SataPortStatus;
    UINT8               i;
	UINT8   			Value8;
	SB_SETUP_DATA       SbSetupData;

    Status = (*PeiServices)->CreateHob (PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        HobSize,
                                        &SataPresentHob);
    if(EFI_ERROR(Status)) return;

    SataPresentHob->EfiHobGuidType.Name = SataPresentHobGuid;

    for (i = 0; i < 4; i++) {
		SataPresentHob->SataInfo[i].ClassCode = 0;
		SataPresentHob->SataInfo[i].PresentPortBitMap = 0;
    }

	(*PeiServices)->SetMem((VOID *)&SbSetupData, sizeof (SB_SETUP_DATA), 0);
	GetSbSetupData( PeiServices, &SbSetupData, TRUE );
	
	if ((SbSetupData.Sata.SataClass == SataAhci) || (SbSetupData.Sata.SataClass == SataRaid)) { // AHCI or Raid mode
		if (SbSetupData.Sata.SataClass == SataAhci)
			SataPresentHob->SataInfo[0].ClassCode = AhciClassCode;
		else
			SataPresentHob->SataInfo[0].ClassCode = RaidClassCode;
		Value8 = READ_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0 + 0x03);
		Value8 |= 0x01;	//01: Select "det" for Port 0 to 5 
		WRITE_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0 + 0x03, Value8);
		SataPortStatus = READ_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0);
		SataPresentHob->SataInfo[0].PresentPortBitMap = (SATA_BUS_DEV_FUN << 16) | (SataPortStatus & 0x3F);
		SataPresentHob->ControllerCount = 1;
	} else {	//IDE mode
		SataPresentHob->SataInfo[0].ClassCode = IdeClassCode;
		Value8 = READ_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0 + 0x03);
		Value8 |= 0x01;	//01: Select "det" for Port 0 to 5 
		WRITE_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0 + 0x03, Value8);
		SataPortStatus = READ_MEM8(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REGF0);
		SataPresentHob->SataInfo[0].PresentPortBitMap = (SATA_BUS_DEV_FUN << 16) | (SataPortStatus & 0xF); // Port 0~3
		SataPresentHob->SataInfo[1].ClassCode = IdeClassCode;
		SataPresentHob->SataInfo[1].PresentPortBitMap = (IDE_BUS_DEV_FUN << 16) | (SataPortStatus & 0x3); // Port 4~5
		SataPresentHob->ControllerCount = 2;
	}
}
#endif

/**
    This function is used to call back after in latest PEI.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDesc 
    @param InvokePpi 

              
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SbMasterBootModeCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
	EFI_STATUS      	Status = EFI_SUCCESS;
	EFI_BOOT_MODE  		BootMode;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_PEI_ERROR (PeiServices, Status);

    if (BootMode == BOOT_IN_RECOVERY_MODE) {
    	//
    	// Chipset init porting
    	//
	#if XHCI_PEI_INIT_FOR_RECOVERY_SUPPORT
		// Notify Fch to initialize XHCI and so on...
		Status = sbFchRecoveryCallBack(PeiServices, NotifyDesc, InvokePpi);
		ASSERT_PEI_ERROR (PeiServices, Status);
	#endif //XHCI_PEI_INIT_FOR_RECOVERY_SUPPORT

		// Recovery Boot Mode PPI
		Status = (*PeiServices)->InstallPpi( PeiServices, mRecoveryModePpi );
		ASSERT_PEI_ERROR (PeiServices, Status);
    }

	return Status;
}

/**
    This function is used to call back after in latest PEI.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDesc
    @param InvokePpi


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SbEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    EFI_BOOT_MODE   SbBootMode;

    Status = (*PeiServices)->GetBootMode (PeiServices, &SbBootMode);
    ASSERT_PEI_ERROR (PeiServices, Status);

    if (SbBootMode == BOOT_ON_S3_RESUME) {

    }
#if CMOS_MANAGER_SUPPORT
    // PM_Reg 59: VRT_T2 set to default value(0xff)
    WRITE_MEM8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG59, 0xFF);
#endif

    // Setting 8254
    // program timer 1 as refresh timer
    IoWrite8(TIMER_CTRL,0x54);
    IoWrite8(TIMER_1_COUNT,0x12);
#if SUPPORT_RAID_DRIVER
    DetectSataPortInfo(PeiServices);
#endif

    return  EFI_SUCCESS;
}

#if defined (XHCI_RECOVERY_PATH_MODE) && (XHCI_RECOVERY_PATH_MODE)
/**
    This function is used to get the XHCI firmware start address.

    @param PeiServices Pointer to the PEI services table

        UINT32
    @retval SectionData XHCI firmware address

**/
UINT32
SbFchGetXhciImage (IN  EFI_PEI_SERVICES **PeiServices)
{
    EFI_STATUS                    	Status = EFI_NOT_FOUND;
    EFI_PEI_FV_HANDLE    			VolumeHandle;
    UINTN                         	Instance = 0;
    EFI_PEI_FILE_HANDLE           	FileHandle;
    EFI_FV_FILE_INFO				FileInfo;
    VOID							*SectionData;

    Status = PeiServicesFfsFindNextVolume(Instance, &VolumeHandle);
    // The XHCI firmware can't be load into memory otherwise XHCI recovery is invalid.
    // if PeiRamBoot on it might be loaded into memory. Find it in ROM directly.
    //		VolumeHandle = (EFI_PEI_FV_HANDLE)FV_BB_BASE;
    if (!EFI_ERROR(Status)) {
    	Status = PeiServicesFfsFindFileByName(&gAmiSbXhciRecoveryFirmwareFileGuid, VolumeHandle, &FileHandle);
    	//##if (!EFI_ERROR(Status)) {
    	//##	Status = PeiServicesFfsFindSectionData(EFI_SECTION_RAW, FileHandle, &SectionData);
    	//##}
    	if (!EFI_ERROR(Status)) {
    		Status = PeiServicesFfsGetFileInfo(FileHandle, &FileInfo);
    		if (!EFI_ERROR(Status)) {
    			SectionData = FileInfo.Buffer;
    		}
    	}
    }

	if (EFI_ERROR(Status)) SectionData = 0;

	DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "  XHCI firmware Status=%r, Addr=%X\n", Status, (UINT32)SectionData));

    return (UINT32)SectionData;
}
#endif

#ifdef XHCI_Firmware_Support
#if XHCI_Firmware_Support
/**
    This function is used to call back recovery MODE init.

    @param PeiServices Pointer to the PEI services table
    @param NotifyDesc 
    @param InvokePpi 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
sbFchRecoveryCallBack(
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
    EFI_STATUS         Status = EFI_SUCCESS;
    AMD_FCH_INIT_PPI    *fchInitPpi = InvokePpi;
    
    if (fchInitPpi->Revision >= 0x1){
    	UINT32		XhciRomAddress = XHCI_FIRMWARE_BASE;
#if defined (XHCI_RECOVERY_PATH_MODE) && (XHCI_RECOVERY_PATH_MODE)
    	XhciRomAddress = SbFchGetXhciImage(PeiServices);
#endif
        if (XhciRomAddress != 0) {
        	fchInitPpi->FpFchXhciRecovery(fchInitPpi, XhciRomAddress);
        	Status = CountTime(1000*1000, PM_BASE_ADDRESS);
        }
    }

    return Status;
}
#endif
#endif
/**
    Setup the wake type in PCD.
    @param

    @retval VOID

    @note
**/
VOID
SbWakeupTypeLib (
  VOID
  )
{
	SB_WAKEUP_TYPE	SbWakeType;
	UINT16	Pm1Status = READ_IO16_PM(SB_ACPI_PM1_STS);
	UINT16	Pm1En = READ_IO16_PM(SB_ACPI_PM1_EN);
	UINT32	Gpe0Status = READ_MMIO32_SMI(0);
	UINT32	Gpe0En = READ_MMIO32_SMI(0x4);


	if (SbCheckAfterG3()) SbWakeType = SbWakeupTypeAcPowerRestored;
	else if (Pm1Status & BIT15) {
		// Power button
		if (Pm1Status & Pm1En & BIT8) {
			SbWakeType = SbWakeupTypePowerSwitch;
		} else if (Pm1Status & Pm1En & BIT10) {
			SbWakeType = SbWakeupTypeApmTimer;
		} else if (Gpe0Status & Gpe0En) {
			SbWakeType = SbWakeupTypePciPme;
		} else SbWakeType = SbWakeupTypeOther; // don't know what the type is. Let's assign "Other".
	} else SbWakeType = SbWakeupTypeUnknown; // not sure what's is.

	// AMD demo board no on chip lan layout. The SbWakeupTypeLanRemote is not support so far...
	// SbWakeupTypeModemRing.....

	PcdSet8S(AmiPcdSbWakeType, SbWakeType);
}

/**
    This function is PM Specific function to check and save CMOS
    Battery and Power Supply Power loss/failure in AmiPcdSbPwrLossData.

    @param VOID

    @retval VOID

**/
VOID SbCheckPowerLoss (
    VOID
)
{
    SB_POWER_LOSS_DATA  SbPwrLossData;

    SbPwrLossData.PowerLossData = 0;

    // There is no such power failure bits in AMD-FCH. Only FCH_PMIOA_REGC0 bit2 is available for FourSecondPwrBtn.
    // We will check later if there are any update on AMD-PPR. The following contains keep chipset template.
    if(!gIsRtcValid) SbPwrLossData.RtcLostPower = 1;
    /**** PORTING REQUIRED ****
    GEN_PMCON2_REG  pm2;
    GEN_PMCON3_REG  pm3;
    RTC_REG_D       RegD;

    //b00|d00|f1f|reg 0xa2
    pm2.GEN_PMCON2=*((UINT8*)PCIE_CFG_ADDR(0,0x1f,0,0xa2));
    //b00|d00|f1f|reg 0xa4
    pm3.GEN_PMCON3=*((UINT8*)PCIE_CFG_ADDR(0,0x1f,0,0xa4));

    //Read RTC Power Register
    RegD.REG_D = ReadRtcIndex(RTC_REG_D_INDEX);

    //Set the correct Code # here
    //Clear Power Failure/Status bits
    //-------------------------------------------------------
    //this bit means it was a power loss during S0 or S1,
    //cleared by writing 1 to it
    if(pm2.PwrOkFail) SbPwrLossData.PwrOkFail = 1;

    //-------------------------------------------------------
    //this bit means it was a power loss on CPU VRM well
    // during S0 or S1, cleared by writing 0 to it
    if(pm2.CpuPwrFail) SbPwrLossData.CpuPwrFail = 1;

    //-------------------------------------------------------
    //this bit means that S4 signal assertion was not long
    //enough, cleared by writing 1 to it
    if(pm2.SlpS4Fail) SbPwrLossData.SlpS4Fail = 1;

    //-------------------------------------------------------
    //this bit means that a power was shut down because of
    //CPU Power Trip, cleared by writing 1 to it
    if(pm2.ThermTripSts) SbPwrLossData.ThermTripSts = 1;

    //-------------------------------------------------------
    //this bit means that RESET# was active
    //cleared by writing 1 to it
    if(pm2.ResetSts) SbPwrLossData.ResetSts = 1;

    //-------------------------------------------------------
    //this bit means that Battery Bad or was removed
    //cleared by writing 1 to it
    if(pm3.PwrFail) SbPwrLossData.PwrFail = 1;

    //-------------------------------------------------------
    //this bit means that RTC Battery Bad or was removed
    //cleared by writing 0 to it
    if(pm3.RtcPwrFail) SbPwrLossData.RtcLostPower = 1;

    if(RegD.DataValid==0) SbPwrLossData.RtcLostPower = 1;

    **** PORTING REQUIRED ****/

    PcdSet16S(AmiPcdSbPwrLossData, SbPwrLossData.PowerLossData);
}

/**
    This function is used to Install FchAmiPolicyPpi, and used to hook GPIO 
    program to CPM.

    @param PeiServices Pointer to the PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

VOID
SbAmdFchAmiPolicyPpiInstall(
  IN  EFI_PEI_SERVICES                **PeiServices
  ) 
{   
    EFI_STATUS         Status = EFI_SUCCESS;
    AMI_PEI_SB_CUSTOM_PPI          *SBPeiOemPpi;
    
    AMD_FCH_AMI_POLICY_PPI      *SbPolicy;
    EFI_PEI_PPI_DESCRIPTOR      *PpiList;

    Status = (*PeiServices)->AllocatePool (PeiServices, \
                        sizeof(EFI_PEI_PPI_DESCRIPTOR),
                        &PpiList
                        );
    ASSERT_PEI_ERROR (PeiServices, Status);

    Status = (*PeiServices)->AllocatePool (PeiServices, \
                        sizeof(AMD_FCH_AMI_POLICY_PPI),
                        &SbPolicy
                        );
    ASSERT_PEI_ERROR (PeiServices, Status);

    PpiList->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI \
                                | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    PpiList->Guid = &gAmdFchAmiPolicyPpiGuid;
    PpiList->Ppi = SbPolicy;
    
    SbPolicy->AmiPeiSbCustomPpi = NULL;
    SbPolicy->DefaultGpioTbl = gAmiGpioInitTable;
    
    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                    &gAmiPeiSbCustomPpiGuid, \
                                    0, \
                                    NULL, \
                                    &SBPeiOemPpi );
    if (Status == EFI_SUCCESS) {
        SbPolicy->AmiPeiSbCustomPpi = SBPeiOemPpi;
    }
    Status = (*PeiServices)->InstallPpi (PeiServices, PpiList); 
}

/**
    This function initializes SB RTC related registers

    @param PeiServices - Pointer to the PEI services table
    @param CpuIo       - Pointer to the CPU I/O PPI

    @retval VOID
**/
VOID PeiInitRtc(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_CPU_IO_PPI           *CpuIo
)
{
#if !EXTERNAL_RTC_SUPPORT
    RTC_REG_A           RegA;
    RTC_REG_B           RegB;

    RegA.REG_A = ReadCmos(RTC_REG_A_INDEX);
    RegB.REG_B = ReadCmos(RTC_REG_B_INDEX);

    //
    // Initialize RTC while RTC power is lost, divisor setting is invalid or
    // Update Cycle Inhibit bit is set.
    //
    if ((gIsRtcValid == FALSE) || (RegA.Divisor != 2) || (RegB.Set == 1)) {
      WriteCmos(RTC_DAY_OF_MONTH_REG, 0xFF);
      WriteCmos(RTC_HOURS_REG, 0xFF);
      WriteCmos(RTC_REG_B_INDEX, 0x82);
      WriteCmos(RTC_REG_A_INDEX, 0x26);
      ReadCmos(RTC_REG_C_INDEX);
      WriteCmos(RTC_REG_B_INDEX, 0x02);
      WriteCmos(RTC_SECONDS_ALARM_REG, 0x00);
      WriteCmos(RTC_MINUTES_ALARM_REG, 0x00);
      WriteCmos(RTC_HOURS_ALARM_REG, 0x00);
    }
    /** PORTING REQUIRED *****/
    //
    // Clear Date Alarm bits in Register 0Dh[5:0].
    //
    {
      UINT8        Buffer8;

      Buffer8 = (ReadCmos(RTC_REG_D_INDEX) & 0x40);
      WriteCmos(RTC_REG_D_INDEX, Buffer8);
    }
#endif
}

