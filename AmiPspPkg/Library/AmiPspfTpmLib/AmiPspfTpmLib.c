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

/** @file AmiPspfTpmLib.c
    This file contains code for AmiPspfTpmLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Uefi.h>
#include <Token.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspFtpmLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/TimerLib.h>
#include <Library/PciLib.h>
//Can't include AmdPspBaseLibV1.h due to the redefinition of GetPspBar1Addr/GetPspBar3Addr
//#include <Library/AmdPspBaseLibV1.h>

#define NBMSIC_SMN_BASE                     0x13B10000ul           ///< Define the SMN Base address for NB MISC register
#define MTS_NBMISC_SMN_BASE                 0x13E10000ul           ///< Define the SMN Base address for MTS NB MISC register
#define NB_SMN_INDEX_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xB8))  ///< PCI Addr of NB_SMN_INDEX_2
#define NB_SMN_DATA_2_PCI_ADDR (MAKE_SBDFO (0, 0, 0, 0, 0xBC))  ///< PCI Addr of NB_SMN_DATA_2
#define NBMSIC_PSP_BASE_ADDR_LO_OFFSET      0x2E0                  ///< Define the offset of PSP_BASE_ADDR_LO in NB MISC block

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
// [Fam15 only]
BOOLEAN
CheckPspDevicePresentV1 (
  VOID
  );

// [Fam15 only]
UINT32
PspLibPciReadPspConfig (
  IN UINT16 Offset
  );
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
 *  Execute a TPM command
 *
 * @param[in]    CommandBuffer              Point to the TPM command buffer
 * @param[in]    CommandSize                Size of the TPM command buffer
 * @param[in]    ResponseBuffer             Point to the TPM response buffer
 * @param[in]    ResponseSize               Size of the TPM response buffer
 *
 * @return       EFI_SUCCESS                Command executed successfully
 * @return       EFI_UNSUPPORTED            Device unsupported
 * @return       EFI_TIMEOUT                Command fail due the time out
 * @return       EFI_DEVICE_ERROR           Command fail due the error status set
 * @return       EFI_BUFFER_TOO_SMALL       Response buffer too small to hold the response
 *
 */
EFI_STATUS
iTpmExecuteCommand (
  IN       VOID                 *CommandBuffer,
  IN       UINT32               CommandSize,
  IN OUT   VOID                 *ResponseBuffer,
  IN OUT   UINT32               *ResponseSize
  )
{
    EFI_STATUS  Status;

    Status = FtpmExecuteCommand(CommandBuffer, CommandSize, ResponseBuffer, ResponseSize);
    MicroSecondDelay(50); //For S3/S4 long run TPM error
    return  Status;

}

/**
  Provide function call to get fTPM MMIO address.

  @retval UINT32     Return the fTPM MMIO address.
  @retval EFI_STATUS Return the EFI  Status.

**/
EFI_STATUS
AmiGetFtpmMmioBase(
  IN OUT   UINT32 *PspMmio
)
{
    SOC_ID_STRUCT       SocId;
    UINT32              Value32;
    UINTN               PciAddress;
    UINT32              SmnBase;
    BOOLEAN             Result;
    TPM2_CONTROL_AREA   *FtpmControlArea = NULL;

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;

    DEBUG ((DEBUG_INFO, " AmiGetFtpmMmioBase Entry \n"));

    if (SocHardwareIdentificationCheck (&SocId))
    {
        // The below code is copied from AmdPspBaseLibV2/GetPspMmioBase()
        *PspMmio = 0;

        SmnBase = NBMSIC_SMN_BASE;
        if (SocFamilyIdentificationCheck (F17_MTS_RAW_ID)) {
          SmnBase = MTS_NBMISC_SMN_BASE;
        }

        PciAddress = NB_SMN_INDEX_2_PCI_ADDR;
        Value32 = SmnBase + NBMSIC_PSP_BASE_ADDR_LO_OFFSET;
        PciWrite32 (PciAddress, Value32);
        PciAddress = NB_SMN_DATA_2_PCI_ADDR;
        Value32 = PciRead32 (PciAddress);
        //Mask out the lower bits
        Value32 &= 0xFFF00000;

        if (Value32 == 0) {
          return (FALSE);
        }

        *PspMmio = Value32;
        return EFI_SUCCESS;
        // The above code is copied from AmdPspBaseLibV2/GetPspMmioBase()
    }
    else
    {
        Result = GetFtpmControlAreaV2(&FtpmControlArea);

        DEBUG ((DEBUG_INFO, " GetFtpmControlAreaV2 Result = %x \n", Result));
        DEBUG ((DEBUG_INFO, " GetFtpmControlAreaV2 address = %x \n", FtpmControlArea));

        *PspMmio = (UINT32)FtpmControlArea;

        if (Result == TRUE)
            return EFI_SUCCESS;
        else
            return EFI_UNSUPPORTED;
    }

}

/**
  Provide function call for AMI-TCG to get ftpm status.

  @retval TRUE   fTPM supported.

**/
EFI_STATUS
iTpmGetInfo(
  IN  UINTN *iTPMStatus)
{
    EFI_STATUS  Status;

    Status = EFI_SUCCESS;
    if (PcdGet8(PcdAmdPspSystemTpmConfig) == 1)
        return  Status;

    Status = EFI_UNSUPPORTED;
    return  Status;
}


/**
  Provide function call for AMI-TCG to get ftpm status.

  @retval TRUE   fTPM supported.

**/

EFI_STATUS
GetfTPMSupport(
  IN  UINTN* Info)
{
	BOOLEAN	    IsFtpmSupport = FALSE;
	EFI_STATUS  Status = EFI_UNSUPPORTED;

	if (PcdGet8(PcdAmdPspSystemTpmConfig) == 1) IsFtpmSupport = TRUE;

	if (TRUE == IsFtpmSupport)
	{
	    Status = EFI_SUCCESS;
	}

	return Status;
}


/**
  The constructor function initialize the PspfTPMSwitchLib Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/
#ifdef _AUTOGENH_B794DDF4_88F6_435b_BDA3_73A627B924B1
#include <Ppi/ReadOnlyVariable2.h>
#include <Setup.h>
#include <Ppi/AmdPspRecoveryDetectPpi.h>

EFI_STATUS
EFIAPI
PspfTPMSwitchLibConstructor (
  IN       EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS                  	Status = EFI_SUCCESS;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
	UINTN                          	VariableSize = sizeof(SETUP_DATA);
	SETUP_DATA                      SetupData;
	EFI_GUID                        gSetupGuid = SETUP_GUID;
	AMD_PSP_RECOVERY_DETECT_PPI     *AmdPspRecoveryPpi;

    Status = (*PeiServices)->LocatePpi(
                PeiServices,
                &gAmdPspRecoveryDetectPpiGuid,
                0, NULL,
                &AmdPspRecoveryPpi);
    if (Status == EFI_SUCCESS)
    {
        PcdSet8(PcdAmdPspSystemTpmConfig, 0);
        return Status;
    }

	Status = (*PeiServices)->LocatePpi(
				PeiServices,
				&gEfiPeiReadOnlyVariable2PpiGuid,
				0, NULL,
				&ReadOnlyVariable);
	ASSERT_EFI_ERROR(Status);
	if (EFI_ERROR(Status)) return Status;

	Status = ReadOnlyVariable->GetVariable(ReadOnlyVariable,
								L"Setup",
								&gSetupGuid,
								NULL,
								&VariableSize,
								&SetupData);
	ASSERT_EFI_ERROR(Status);

	//
	// Setup AGESA Pcd for fTPM function.
	//		Set default turn on.
	//
	PcdSet8(PcdAmdPspSystemTpmConfig, 1);

	// Turn off if user want dTPM. 
	if (SetupData.fTPMSwitch != 0) {
	    PcdSet8(PcdAmdPspSystemTpmConfig, 0);
	} else {
         // Turn off fTPM if TCG module disabled or used dTPM 1.2
	     if (SetupData.TpmSupport == 0 || SetupData.TpmSupport == 1 && SetupData.DeviceType == 0 ){
	         PcdSet8(PcdAmdPspSystemTpmConfig, 0);
	      }
	}
	return Status;
}
#endif

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
