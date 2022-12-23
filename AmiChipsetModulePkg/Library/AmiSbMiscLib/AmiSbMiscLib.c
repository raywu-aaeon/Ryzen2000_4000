//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiSbMiscLib.c
    South Bridge Miscellaneous functions Library implementation

*/

#include <Library/AmiSbMiscLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Sb.h>
#include <Library/PcdLib.h>
#include <AmiChipsetIoLib.h>
#include <Library/AmiFchIoAccessLib.h>
#include <Pi/PiMultiPhase.h>
#include <Library/DebugLib.h>

EFI_STATUS
EFIAPI
AmdWarmReset (
  IN EFI_RESET_TYPE  ResetType
  );

#define FCH_N_OF_SMI_CTRL_REG 10

struct {
	UINT32 Reg;
	UINT32 Mask;
} CONST SmiControl[FCH_N_OF_SMI_CTRL_REG] = {
     //Refer 55570 PPR (AMD Family 17h Model 10h, Revision A0 Processors )section 16.2.6 SMI Registers - Raven
	 // Reg		mask
     {0xA0,		0x00000000},
     {0xA4,		0x00FC0000},
     {0xA8,		0x3033C300},
     {0xAC,		0x3FC30030},
     {0xB0,		0x0300FF00},
     {0xB4,		0x00C3F000},
     {0xB8,		0xFFFFFFFF},
     {0xBC,		0xFFFFFFFF},
     {0xC0,		0x000FF3FF},
     {0xC4,		0xFCFCFCF0},
};

/**
    This function read for PMIO two bytes. 

    @param  UINT8  Index

    @retval UINT16 Data

**/

UINT16
ReadPmio16 (
  IN       UINT8        Index
  )
{
  UINT8    bTemp;

  IoWrite8 (FCH_IOMAP_REGCD6, Index);
  bTemp = IoRead8 (FCH_IOMAP_REGCD7);
  IoWrite8 (FCH_IOMAP_REGCD6, Index + 1);
  return (UINT16) ((IoRead8 (FCH_IOMAP_REGCD7) << 8) + bTemp);
}

/**
    This function Shuts the system down (S5)

    @param VOID

    @retval VOID

**/
VOID SbLibShutdown (
    VOID
)
{
    UINT16          AcpiGpeBase;
    UINT32          Gpe0Enable;
    UINT16          AcpiPm1StsBase;
    UINT16          AcpiPm1CntBase;
    UINT16          PmCntl;
    UINT16          PwrSts;

    // Disable all GPE0 Event
    AcpiGpeBase = ReadPmio16(FCH_PMIOA_REG68); 
    AcpiGpeBase += 4; //Get enable base
    Gpe0Enable  = 0;
    IoWrite32 (AcpiGpeBase, Gpe0Enable);

    // Clear Power Button status.
    AcpiPm1StsBase = ReadPmio16(FCH_PMIOA_REG60);
    PwrSts  = BIT8 | BIT15; //Clear WakeStatus with PwrBtnStatus
    IoWrite16 (AcpiPm1StsBase, PwrSts);
    
    // Transform system into S5 sleep state
    AcpiPm1CntBase = ReadPmio16(FCH_PMIOA_REG62);
    PmCntl  = IoRead16 (AcpiPm1CntBase);
    PmCntl &= ~(BIT12 + BIT11 + BIT10);
    PmCntl |= 5 << 10;
    PmCntl |= BIT13;    //SLP_EN
    
    IoWrite16(AcpiPm1CntBase, (UINT16)PmCntl);

    IoWrite8(0x80,0x05);
//EIP-555169
//  CpuDeadLoop(); //halt at this,never come here!
    
}

/**
    This function is the extended reset call interface function
    provided by SB.

    @param ResetType - The extended type of reset to be generated

    @retval SYSTEM RESET
**/

VOID SbLibExtResetSystem (
    IN SB_EXT_RESET_TYPE  ResetType
)
{
/**  CHIPSET SPECIFIC PORTING REQUIRED 
    switch (ResetType) {
      case SbResetFull:
      case SbResetGlobal:
      case SbResetGlobalWithEc:
  
        break;
  
      default:
        return;
    }
  
    // We should never get this far
    EFI_DEADLOOP();
**/
}

#if (SB_RESET_PPI_SUPPORT == 1) || (defined(CSLIB_WARM_RESET_SUPPORTED) && (CSLIB_WARM_RESET_SUPPORTED == 1))//SB_RESET_PPI_SUPPORT (AMD platform : SecSMIFlash.c use this library in DXE)

/**
    This function will program Lpc/eMMC pins

    @param eMMC_en - True to eMMC, False to LPC

    @retval VOID

**/
VOID
ProgramLpcEmmcPins (
  IN       BOOLEAN   eMMC_en
  )
{
  // reference AMD Agesa code "AgesaModulePkg\Fch\Sandstone\FchSandstoneCore\Common\FchPeLib.c"
  if (eMMC_en) {
	WRITE_MEM8(0xFED80D15, 1); 
	WRITE_MEM8(0xFED80D16, 1); 
	WRITE_MEM8(0xFED80D20, 1); 
	WRITE_MEM8(0xFED80D44, 1); 
	WRITE_MEM8(0xFED80D46, 1); 
	WRITE_MEM8(0xFED80D68, 1); 
	WRITE_MEM8(0xFED80D69, 1); 
	WRITE_MEM8(0xFED80D6A, 1); 
	WRITE_MEM8(0xFED80D6B, 1); 
	WRITE_MEM8(0xFED80D4A, 1); 
	WRITE_MEM8(0xFED80D58, 1); 
	WRITE_MEM8(0xFED80D4B, 1); 
	WRITE_MEM8(0xFED80D57, 1); 
	WRITE_MEM8(0xFED80D6D, 1); 
	WRITE_MEM8(0xFED80D1F, 1); 
  } else {
	WRITE_MEM8(0xFED80D15, 0);
	WRITE_MEM8(0xFED80D20, 0); 
    //ACPIMMIO8 (0xFED80D44) = 0;
    //ACPIMMIO8 (0xFED80D46) = 0;
	WRITE_MEM8(0xFED80D68, 0); 
	WRITE_MEM8(0xFED80D69, 0);
	WRITE_MEM8(0xFED80D6A, 0); 
	WRITE_MEM8(0xFED80D6B, 0); 
	WRITE_MEM8(0xFED80D4A, 0); 
	WRITE_MEM8(0xFED80D58, 0); 
	WRITE_MEM8(0xFED80D4B, 0); 
	WRITE_MEM8(0xFED80D57, 0); 
	WRITE_MEM8(0xFED80D6D, 0); 
	WRITE_MEM8(0xFED80D1F, 0); 
  }
}

/**
    This function is the reset call interface function published
    by the reset PPI

    @param ResetType Type of reset to be generated

    @retval VOID

**/
VOID SBLib_ResetSystem (
    IN  EFI_RESET_TYPE  ResetType
)
{
	// The following token just to sync template.
	#ifndef COLD_RESET
	#define COLD_RESET SB_COLD_RESET
	#endif
	#ifndef FULL_RESET
	#define FULL_RESET SB_FULL_RESET
	#endif
	#ifndef RST_CPU
	#define RST_CPU SB_RST_CPU
	#endif

    // The following code is to generate cold reset using port 0xCF9
    UINT8 Data;
    UINT8 PwrRsrCfg;
    UINT16 AcpiPm1CntBase, PmCntl;
    
    Data = IoRead8(RESET_PORT);
    Data &= CLEAR_RESET_BITS;

    Data |= RST_CPU + COLD_RESET; //  AMD specific.

    switch (ResetType) {
      case EfiResetWarm:
        WRITE_IO8 (FCH_IOMAP_REGCD6, 0x10);
        PwrRsrCfg = READ_IO8 (FCH_IOMAP_REGCD7);
        PwrRsrCfg = PwrRsrCfg & 0xFD; //clear ToggleAllPwrGoodOnCf9
        WRITE_IO8 (FCH_IOMAP_REGCD7, PwrRsrCfg);
    	if (!EFI_ERROR(AmdWarmReset(ResetType))) return; // Return to Sleep SMI for capsule.
        break;

      case EfiResetCold:
        Data |= COLD_RESET;
        if (GetFchFullHardReset()){
            Data |= FULL_RESET;
        }
        #if defined(COLD_RESET_WITH_POWER_CYCLE)&&(COLD_RESET_WITH_POWER_CYCLE != 0)
        Data |= FULL_RESET;
        #endif
    	WRITE_IO8 (FCH_IOMAP_REGCD6, 0x10);
        PwrRsrCfg = READ_IO8 (FCH_IOMAP_REGCD7);
        PwrRsrCfg = PwrRsrCfg | BIT1; //set ToggleAllPwrGoodOnCf9
        WRITE_IO8 (FCH_IOMAP_REGCD7, PwrRsrCfg);
        break;

      case EfiResetShutdown:

        SbLibShutdown();
        return;

      default:
        SbLibExtResetSystem (ResetType);
        return;
    }

    // Disabled LPC EMMC pins
    WRITE_IO8 (FCH_IOMAP_REGCD6, FCH_PMIOA_REG62);
    AcpiPm1CntBase  = READ_IO8 (FCH_IOMAP_REGCD7);
    WRITE_IO8 (FCH_IOMAP_REGCD6, FCH_PMIOA_REG62 + 1);
    AcpiPm1CntBase |= (READ_IO8 (FCH_IOMAP_REGCD7) << 8);
    PmCntl = READ_IO16 (AcpiPm1CntBase);
    if (PmCntl & BIT0) {
      //FCH_DEADLOOP ();
      //ProgramLpcEmmcPins (FALSE);
    }
    
    while(1) IoWrite8(RESET_PORT, Data);
    //## template ##Data |= RST_CPU;
    //## template ##IoWrite8(RESET_PORT, Data);
  
    // We should never get this far
    CpuDeadLoop ();
}

#endif

/**
    This function determines if the system should boot with the
    default configuration. 

    @param PeiServices Pointer to the PEI services table
    @param ReadVariablePpi Pointer to the Read Variable#2 PPI
                           (The pointer can be used to read and 
                           enumerate existing NVRAM variables)

    @retval TRUE Firmware will boot with default configuration.

    @note  1. If boot with default configuration is detected, default
                 values for NVRAM variables are used.
              2. Normally we have to check RTC power status or CMOS clear
                 jumper status to determine whether the system should boot
                 with the default configuration.
**/
BOOLEAN SbIsDefaultConfigMode (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE2_PPI  *ReadVariablePpi )
{
#ifdef LOAD_DEFAULTS_IF_CMOS_BAD
  #if LOAD_DEFAULTS_IF_CMOS_BAD
	IoWrite8(CMOS_BANK1_INDEX, CMOS_BAD_CHECK_ADDRESS);
	if (IoRead8(CMOS_BANK1_DATA) ==0x55)  return TRUE;
  #endif
#endif
    return FALSE;
}

#if SB_STALL_PPI_SUPPORT

/**
    This function delays for the number of micro seconds passed in

    @param DelayTime Number of microseconds(us) to delay
    @param BaseAddr The I/O base address of the ACPI registers

    @retval EFI_STATUS based on errors that occurred while waiting
                       for time to expire.

**/
EFI_STATUS CountTime (
    IN  UINTN   DelayTime,
    IN  UINT16  BaseAddr // only needs to be 16 bit for I/O address
)
{
    // The following code is to generate delay for specified amount
    //    of micro seconds using ACPI timer.
    UINTN       TicksNeeded;
    UINT32      TimerValue, NewTimerValue;
    UINTN       OverFlow;
    UINTN       TheRest, EndValue;


    // Set up timer to point to the ACPI Timer register
    BaseAddr += ACPI_IOREG_PM1_TMR;           // *** PORTING NEEDED

    // There are 3.58 ticks per us, so we have to convert the number of us passed
    //  in to the number of ticks that need to pass before the timer has expired
    // Convert us to Ticks, don't loose significant figures or as few as possible
    //  do integer math in ticks/tens of ns and then divide by 100 to get ticks
    //  per us
    OverFlow = 0;

    TheRest = TicksNeeded = (DelayTime * 358) / 100;

    // 32 bits corresponds to approz 71 mins  no delay should be that long
    // otherwise
    // Get the number of times the counter will have to overflow to delay as long
    // as needed
    if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
        // compiler error when NUM_BITS_IN_ACPI_TIMER=32
        //#### OverFlow = TicksNeeded / (1 << NUM_BITS_IN_ACPI_TIMER);
        //#### TheRest = TicksNeeded % (1 << NUM_BITS_IN_ACPI_TIMER);
    }
    //Enable ACPI MMIO Space
    //Get ACPI MMIO Base Address

    // read ACPI Timer
    TimerValue = AmdFchMmioRead32 (AMD_FCH_MMIO, BaseAddr);

    // need to adjust the values based off of the start time
    EndValue = TheRest + TimerValue;

    // check for overflow on addition.  possibly a problem
    if (EndValue < TimerValue) {
      OverFlow++;
    }
    // here make sure that EndValue is less than the max value
    // of the counter
    else if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
      // compiler error when NUM_BITS_IN_ACPI_TIMER=32
      //### OverFlow += EndValue / (1 << NUM_BITS_IN_ACPI_TIMER);
      //### EndValue = EndValue % (1 << NUM_BITS_IN_ACPI_TIMER);
    }

    // let the timer wrap around as many times as calculated
    while (OverFlow) {
        // read timer amd look to see if the new value read is less than
        // the current timer value.  if this happens the timer overflowed
        NewTimerValue = AmdFchMmioRead32 (AMD_FCH_MMIO, BaseAddr);

        if (NewTimerValue < TimerValue)
          OverFlow--;

        TimerValue = NewTimerValue;
    }


    // now wait for the correct number of ticks that need to occur after
    //  all the needed overflows
    while (EndValue > TimerValue) {
        NewTimerValue = AmdFchMmioRead32 (AMD_FCH_MMIO, BaseAddr);
        // check to see if the timer overflowed.  if it did then
        // the time has elapsed. Because EndValue should be greater than TimerValue
        if (NewTimerValue < TimerValue)
            break;

        TimerValue = NewTimerValue;
    }

    return EFI_SUCCESS;
}

#endif

// End Generic Flash part porting hooks

/**
    This function returns SMI state
              
    @param VOID

    @retval TRUE SMI enabled, FALSE - otherwise

    @note  This function must work at runtime. Do not use boot time services/protocols

**/
BOOLEAN SbLib_GetSmiState(
    VOID
)
{
    BOOLEAN     IsSmiEn=FALSE;
#if SMM_SUPPORT
    UINT8   Buffer;
    Buffer = AmdFchMmioRead8(AMD_FCH_SMI_MMIO, FCH_SMI_REG98+3);   //EIP36094+
    if (!(Buffer & BIT7)) IsSmiEn = TRUE; // Yes, Global was enabled.
#endif // #if SMM_SUPPORT
    return IsSmiEn;
}

/**
    This function disables SMI
              
    @param VOID

    @retval VOID

    @note  This function should be used ONLY in critical parts of code
           This function must work at runtime. Do not use boot time services/protocols

**/
VOID SbLib_SmiDisable(
    VOID
)
{
#if SMM_SUPPORT
    // Disable SMICmdPort
    AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, FCH_SMI_REGB2, ~BIT6, 0);  //EIP36094+
    // Disable Global SMI
    AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, FCH_SMI_REG98+3, ~BIT7, BIT7);  //EIP36094+
#endif
}

/**
    This function enables SMI
              
    @param VOID

    @retval VOID

    @note  This function should be used ONLY in critical parts of code
           This function must work at runtime. Do not use boot time services/protocols

**/
VOID SbLib_SmiEnable(
    VOID
)
{
#if SMM_SUPPORT
    // Enable SMICmdPort
    AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, FCH_SMI_REGB2, ~BIT6, BIT6); //EIP36094+
    // Enable Global SMI
    AmdFchMmioAndThenOr8(AMD_FCH_SMI_MMIO, FCH_SMI_REG98+3, ~BIT7, 0); //EIP36094+
#endif // #if SMM_SUPPORT
}

/**
    This function is PM Specific function to check and Report to
    the System Status Code - CMOS Battery and Power Supply Power 
    loss/failure.

    @param VOID

    @retval VOID

**/
VOID CspLibCheckPowerLoss(
    VOID
)
{
#if  AMI_CSP_DXE_SUPPORT
    SB_POWER_LOSS_DATA  SbPwrLossData;

    SbPwrLossData.PowerLossData = PcdGet16(AmiPcdSbPwrLossData) & PcdGet16(AmiPcdSbPwrLossDataMask);
    
    if(SbPwrLossData.PwrOkFail) ERROR_CODE(0x00,  EFI_ERROR_MAJOR);

    //-------------------------------------------------------
    //this bit means it was a power loss on CPU VRM well 
    // during S0 or S1, cleared by writing 0 to it
    if(SbPwrLossData.CpuPwrFail) ERROR_CODE(0x01,  EFI_ERROR_MAJOR);

    //-------------------------------------------------------
    //this bit means that S4 signal assertion was not long 
    //enough, cleared by writing 1 to it
    if(SbPwrLossData.SlpS4Fail) ERROR_CODE(0x02,  EFI_ERROR_MINOR);

    //-------------------------------------------------------
    //this bit means that a power was shut down because of 
    //CPU Power Trip, cleared by writing 1 to it
    if(SbPwrLossData.ThermTripSts) ERROR_CODE(GENERIC_CPU_THERMAL_ERROR, EFI_ERROR_MAJOR);
    
    //-------------------------------------------------------
    //this bit means that RESET# was active 
    //cleared by writing 1 to it
    if(SbPwrLossData.ResetSts) ERROR_CODE(0x04,  EFI_ERROR_MINOR);

    //-------------------------------------------------------
    //this bit means that Battery Bad or was removed
    //cleared by writing 1 to it
    if(SbPwrLossData.PwrFail) ERROR_CODE(0x05,  EFI_ERROR_MAJOR);

    if(SbPwrLossData.RtcLostPower){
        #if defined(SB_BAD_BATTERY_ERR_CODE_SUPPORT) && (SB_BAD_BATTERY_ERR_CODE_SUPPORT != 0)
        ERROR_CODE(DXE_SB_BAD_BATTERY,  EFI_ERROR_MAJOR);
        #endif
    }
#endif
}

/**
    Enable or disable SB common functions.

    @param SbDevType - The type of SB device, refer to SB_DEV_TYPE
    @param Enable - TRUE: Enable / FALSE: Disable

    @retval VOID

**/
VOID SbEnableDisableFunctions (
    IN SB_DEV_TYPE  SbDevType,
    IN BOOLEAN      Enable
)
{
	switch (SbDevType) {
	case SB_DEV_FUNCTION_0:
		// AMD not support.
		break;
	case SB_DEV_ADSP:
		// AMD not support.
		break;
	case SB_DEV_SATA1:
		//###RwMem (mInternalFchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REGDA, AccessWidth8, 0, FchSataMode); FchSataMode |= 0x01;
		if (Enable) {
			//###MmioOr8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGDA, BIT0);
			AmdFchMmioOr32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGDA, BIT0);
		} else {
			//###MmioAnd8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGDA, ~BIT0);
			AmdFchMmioAnd32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGDA, ~BIT0);
		}
		break;
	case SB_DEV_SMBUS:
		// AMD not support.
		break;

	case SB_DEV_EHCI1:
		//###RwMem (mInternalFchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REGEF, AccessWidth8, 0, UsbModeReg); UsbModeReg |= 0x02;
		if (Enable) {
			//###MmioOr8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, BIT1);
			AmdFchMmioOr32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, BIT1);
		} else {
			//###MmioAnd8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, ~BIT1);
			AmdFchMmioAnd32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, ~BIT1);
		}
		break;
	case SB_DEV_EHCI2:
		//###RwMem (mInternalFchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REGEF, AccessWidth8, 0, UsbModeReg); UsbModeReg |= 0x08;
		if (Enable) {
			//###MmioOr8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, BIT3);
			AmdFchMmioOr32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, BIT3);
		} else {
			//###MmioAnd8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, ~BIT3);
			AmdFchMmioAnd32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, ~BIT3);
		}
		break;
	case SB_DEV_EHCI3:
		//###RwMem (mInternalFchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REGEF, AccessWidth8, 0, UsbModeReg); UsbModeReg |= 0x20;
		if (Enable) {
			//###MmioOr8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, BIT5);
			AmdFchMmioOr32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, BIT5);
		} else {
			//###MmioAnd8 (FchMmio + PMIO_BASE + FCH_PMIOA_REGEF, ~BIT5);
			AmdFchMmioAnd32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGEF, ~BIT5);
		}
		break;
	case SB_DEV_LPC_BRIDGE:
		break;
	case SB_DEV_PCI_EX_PORT1:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT2:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT3:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT4:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT5:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT6:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT7:
		// AMD not support.
		break;
	case SB_DEV_PCI_EX_PORT8:
		// AMD not support.
		break;
	case SB_DEV_THERMAL:
		//### <AAV> : check AMD.
		break;
	case SB_DEV_SATA2:
		// AMD not support.
		break;
	case SB_DEV_XHCI:
		//### <AAV> : check AMD.
		break;
	case SB_DEV_LAN:
		// AMD not support.
		break;
	default:
		break;
	}
}

/**
    Save or Restore All Hardware SMIs

    @param Save TRUE  : Save all HW SMIs
                FALSE : Restore saved HW SMIs

    @retval VOID

**/
VOID SbSaveRestoreAllHwSmi (
    IN BOOLEAN      Save
)
{
  UINT32 i = 0;
  UINT32 static SaveData[FCH_N_OF_SMI_CTRL_REG];

  if (Save) {
    for (i = 0; i < FCH_N_OF_SMI_CTRL_REG; i++) {
    	if (SmiControl[i].Mask == 0xFFFFFFFF) continue; // all reserved
    	SaveData[i] = AmdFchMmioRead32(AMD_FCH_SMI_MMIO, SmiControl[i].Reg) & ~SmiControl[i].Mask;
    }
  } else {
    for (i = 0; i < FCH_N_OF_SMI_CTRL_REG; i++) {
    	if (SmiControl[i].Mask == 0xFFFFFFFF) continue; // all reserved
    	AmdFchMmioWrite32(AMD_FCH_SMI_MMIO,SmiControl[i].Reg,
    			(AmdFchMmioRead32(AMD_FCH_SMI_MMIO, SmiControl[i].Reg) & SmiControl[i].Mask) | SaveData[i]
    			);
    }
  }
}

/**
    Disable all HW SMIs

    @param VOID

    @retval VOID

**/
VOID SbDisableAllHwSmi (
    VOID
)
{
	UINT32 i = 0;

    for (i = 0; i < FCH_N_OF_SMI_CTRL_REG; i++) {
    	if (SmiControl[i].Mask == 0xFFFFFFFF) continue; // all reserved
    	AmdFchMmioWrite32(AMD_FCH_SMI_MMIO,SmiControl[i].Reg,
    			(AmdFchMmioRead32(AMD_FCH_SMI_MMIO, SmiControl[i].Reg) & SmiControl[i].Mask)
    			);
    }
}

/**
    Trigger SW SMI and adding extra I/O instructions around
    the SMI port write reduces the failure rate.

    @param SwSmi - The number of Software SMI

    @retval VOID

**/
VOID SbSwSmiTrigger (
    IN UINT8        SwSmi
)
{
  IoWrite8 (0x81, 0xEF);
  IoWrite8 (0x81, 0xEF);
  IoWrite8 (SW_SMI_IO_ADDRESS, SwSmi);
  IoWrite8 (0x81, 0xEF);
  IoWrite8 (0x81, 0xEF);
}

/**
    Trigger SW SMI and return the S/W SMI data from the S/W SMI data port.

    @param SwSmi The number of Software SMI
    @param Data Pointer to the data to be written to the S/W SMI data port.

    @return Data Pointer to the data read from the S/W SMI data port.

**/
VOID SbSwSmiIo (
    IN     UINT8    SwSmi,
    IN OUT UINT8    *Data
)
{
  IoWrite8 (SW_SMI_IO_ADDRESS + 1, *Data);
  SbSwSmiTrigger (SwSmi);
  *Data = IoRead8 (SW_SMI_IO_ADDRESS + 1);
}

/**
    Get data from S/W SMI I/O port and return the address of S/W SMI 
    I/O port.

    @param DataValue Pointer to the data buffer for receiving the S/W SMI
                     number read from S/W SMI I/O port.

    @return DataValue Pointer to the data buffer contained the S/W SMI
                      number read from S/W SMI I/O port.

**/
UINT16 SbGetSwSmi (
    IN OUT UINT32   *DataValue
)
{
  *DataValue = (UINT32)(IoRead8(SW_SMI_IO_ADDRESS));
  return SW_SMI_IO_ADDRESS;
}

/**
    Get Intel TCO2 Status address.(Intel Chipset Only)

    @param AcpiBaseAddr ACPI Base address, it is defined by PM_BASE_ADDRESS
                        normally.

    @return The address of TCO2 status register.
            0xFFFF - not supported.

**/
UINT16 SbGetTco2StsAddress (
    IN UINT16       AcpiBaseAddr
)
{
	// <AAV>  AMD not support.
  return 0xFFFF;
}

/**
    Get Intel TCO2 Control address. (Intel Chipset Only)

    @param AcpiBaseAddr ACPI Base address, it is defined by PM_BASE_ADDRESS
                        normally.

    @retval The address of TCO2 control register.
            0xFFFF - not supported.

**/
UINT16 SbGetTco2CntAddress (
    IN UINT16       AcpiBaseAddr
)
{
	// <AAV>  AMD not support.
  return 0xFFFF;
}

/**
    Set After G3 bit.

    @param Set
           TRUE  = Enable G3 Bit
           FALSE = Disable G3 Bit

    @retval VOID

**/
VOID SetAfterG3Bit (
    IN BOOLEAN      Set
)
{
	// Reference code : AcLossControl : AmdAgesaPkg/Proc/Fch/Common/FchLib.c
	if (Set) AmdFchMmioOr8(AMD_FCH_PMIO_MMIO,FCH_PMIOA_REG5B, BIT2);
	else AmdFchMmioAnd8(AMD_FCH_PMIO_MMIO,FCH_PMIOA_REG5B, ~BIT2);
}

/**
    Check After G3 bit.

    @param VOID

    @retval TRUE:  G3 bit is set
            FALSE: G3 bit is not set

**/
BOOLEAN SbCheckAfterG3 (
    VOID
)
{
    if (AmdFchMmioRead8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG5B) & 0x0F)
        return FALSE;
    else
        return TRUE;
}

/**
    Disable LPC Super I/O Devices

    @param SioType - The type of SIO device, refer to SB_LPC_SIO_TYPE.

    @retval VOID

**/
VOID SbDisableLpcDevices (
    IN SB_LPC_SIO_TYPE  SioType
)
{
  /** RVA9 - Sandstone has on-chip lan but CRB no layout. Check later **
  UINT32 Data32;

  Data32 = READ_PCI32_SB (FCH_LPC_REG44);
  switch (SioType) {
    case SbComA:
      Data32 &= ~BIT6;
      break;
    case SbComB:
      Data32 &= ~BIT7;
      break;
    case SbLpt:
      Data32 &= ~BIT0;
      break;
    case SbFdd:
      Data32 &= ~BIT26;
      break;
    case SbGameL:
      Data32 &= ~BIT28;
      break;
    case SbGameH:
      //### <AAV> AMD not support ###Data32 &= ~B_PCH_LPC_ENABLES_GAMEH_EN;
      break;
    case SbKbc:
      Data32 &= ~BIT29;
      break;
    case SbMc:
      Data32 &= ~BIT30;
      break;
    case SbCnf1:
      RESET_PCI32_SB(FCH_LPC_REG48, BIT0);
      break;
    case SbCnf2:
      RESET_PCI32_SB(FCH_LPC_REG48, BIT1);
      break;
    default:
      break;
  }
  WRITE_PCI32_SB (FCH_LPC_REG44, Data32);
  **/
}

/**
    Enable EHCI USB SMI

    @param VOID

    @retval VOID

**/
VOID SbEnableEhciSmi (
    VOID
)
{
	/* RVA9 - Sandstone no EHCI
	// Reference code :
	// ACPIMMIO32 (mInternalFchAcpiMmioBase + SMI_BASE + FCH_SMI_REGB0) |= BIT24;
	// ACPIMMIO32 (mInternalFchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REGED) |= (BIT4);
	AmdFchMmioOr32(AMD_FCH_SMI_MMIO, FCH_SMI_REGB0, BIT24);
	AmdFchMmioOr32(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGED, BIT4);
	*/
}

/**
    Disable EHCI USB SMI

    @param VOID

    @retval VOID

**/
VOID SbDisableEhciSmi (
    VOID
)
{
	/* RVA9 - Sandstone no EHCI
	AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, FCH_SMI_REGB0, ~BIT24, 0);
	AmdFchMmioAndThenOr32(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGED, ~BIT4, 0);
	*/
}

/**
    Check power button pressed.

    @param VOID

    @retval TRUE:  Pressed
            FALSE: No Pressed

**/
BOOLEAN IsPowerButtonPressed (
    VOID
)
{  
  UINT16 PmBase;

  PmBase    = PcdGet16 (AmiPcdAcpiIoPortBaseAddress);

  if (IoRead16 (PmBase + ACPI_IOREG_PM1_STS) & BIT8) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
    Enable PCI PME bit.

    @param PciAddress The address got from PCI_LIB_ADDRESS macro in
                      PciLib.h
        #define PCI_LIB_ADDRESS(Bus,Device,Function,Register) \
        (((Register) & 0xfff) | (((Function) & 0x07) << 12) | \
        (((Device) & 0x1f) << 15) | (((Bus) & 0xff) << 20))

    @retval VOID

**/
VOID SbEnablePciPme (
    IN UINTN        PciAddress
)
{
  UINT16 CapPtr;
  UINTN  PcieBaseAddress;
  UINTN  PcieAddress;
  
  PcieBaseAddress = CspGetPciExpressBaseAddress();
  if (PciAddress >= PcieBaseAddress) {
    PciAddress -= PcieBaseAddress;
  } else {
    ASSERT (PciAddress < 0x10000000);
  }

  PcieAddress = CSP_PCIE_CFG_ADDRESS(
                  (PciAddress >> 20) & 0xFF,
                  (PciAddress >> 15) & 0x1F,
                  (PciAddress >> 12) & 0x07,
                  0);  
  
  CapPtr = FindCapPtr (PcieAddress, 0x01);
  // CapPtr is found
  if (CapPtr != 0) {
    // Set PMEE.
    MmioOr16 (PcieAddress + CapPtr + 4, BIT8);
  }
}

/**
    Disable PCI PME bit.

    @param PciAddress The address got from PCI_LIB_ADDRESS macro in
                      PciLib.h
        #define PCI_LIB_ADDRESS(Bus,Device,Function,Register) \
        (((Register) & 0xfff) | (((Function) & 0x07) << 12) | \
        (((Device) & 0x1f) << 15) | (((Bus) & 0xff) << 20))

    @retval VOID

**/
VOID SbDisablePciPme (
    IN UINTN        PciAddress
)
{
  UINT16 CapPtr;
  UINTN  PcieBaseAddress;
  UINTN  PcieAddress;
  
  PcieBaseAddress = CspGetPciExpressBaseAddress();
  if (PciAddress >= PcieBaseAddress) {
    PciAddress -= PcieBaseAddress;
  } else {
    ASSERT (PciAddress < 0x10000000);
  }

  PcieAddress = CSP_PCIE_CFG_ADDRESS(
                  (PciAddress >> 20) & 0xFF,
                  (PciAddress >> 15) & 0x1F,
                  (PciAddress >> 12) & 0x07,
                  0);  
  
  CapPtr = FindCapPtr (PcieAddress, 0x01);
  // CapPtr is found
  if (CapPtr != 0) {
    // Disable PMEE.
    MmioAnd16 (PcieAddress + CapPtr + 4, ~BIT8);
    // Clear PMES
    MmioWrite16 (PcieAddress + CapPtr + 4, BIT15);
  }
}

/**
    Program the related registers for WOL enabled.

    @param VOID

    @retval VOID

**/
VOID SbEnableWolPmConfg (
    VOID
)
{
  /** PORTING REQUIRED **/
}

/**
    Program the related registers for WOL disabled.

    @param VOID

    @retval VOID

**/
VOID SbDisableWolPmConfg (
    VOID
)
{
  /** PORTING REQUIRED **/
}

/**
    Get I/O Trap Info

    @param TrappedIoData Pointer to a 32bit data buffer for receiving the
                         data of I/O trap information.

    @return TrappedIoData Pointer to a 32bit data buffer contained the
                          data of I/O trap information.
            I/O Trap address

**/
UINT16 SbGetIoTrapInfo (
    IN OUT UINT32   *TrappedIoData 
)
{
	//
	// AMD South bridge doesn't support the register to get the date from trapped IO.
	//	Instead to get information from SMM data area.
	// REFERENCE :
	//		Preliminary BIOS and Kernel Developer¡¦s Guide (BKDG) for AMD Family 16h Models 30h-3Fh Processors
	// Section :
	//		2.4.8.2.5 SMM Save State
	// 		SMMFEC0 SMM IO Trap Offset
	//
	return  0xFFFF;
}

/**
    Get ACPI Base Address

    @param VOID

    @return The address of ACPI Base.

**/
UINT16 SbGetAcpiBaseAddress (
    VOID
)
{
  return PcdGet16 (AmiPcdAcpiIoPortBaseAddress);
}

/**
    Get PM1 Control Register Offset

    @param VOID

    @return The offset of PM1 Control Register

**/
UINT16 SbGetPm1CntOffset (
    VOID
)
{
	return SbGetAcpiBaseAddress() + ACPI_IOREG_PM1_CNTL;
}

/**
    Get Intel RCBB Address (Intel Chipset Only)

    @param VOID

    @return The address of RCRB

**/
UINT32 SbGetRcrbAddress (
    VOID
)
{
  return 0;//###<AAV> AMD not support ##PcdGet32 (PcdRcrbBaseAddress);
}

/**
    Get South Bridge Miscellaneous BIT Status

    @param SbMiscType   Please check SB_MISC_TYPE for the details
    @param BitStatus    The value of the Miscellaneous BIT

    @retval EFI_UNSUPPORTED   This Miscellaneous BIT is not supported
    @retval EFI_SUCCESS       Success to get the value of the Miscellaneous BIT

**/
EFI_STATUS SbGetMiscBitStatus(
    IN SB_MISC_TYPE         SbMiscType,
    IN OUT UINT8            *BitStatus
)
{
	EFI_STATUS	Status = EFI_UNSUPPORTED;
    // Please check the datasheet of the chipset for the register to know
    // how to program the value of the Miscellaneous BIT indicated by SbMiscType.
    // If the type is not supported by the chip, please return EFI_UNSUPPORTED.
    switch (SbMiscType) {
      case CPU_THERMAL_TRIP_STATUS:
    	  break;

      case AFTERG3_EN:
    	  if (AmdFchMmioRead8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG5B) & BIT2) {
    		  *BitStatus = 1;
    	  } else {
    		  *BitStatus = 0;
    	  }
    	  Status = EFI_SUCCESS;

      case PWR_FLR:
		  #ifndef FCH_PMxC0_ResetStatus_Mask // Next AMD AGESA reference code will provide this token. define it here for the moment.
				#define FCH_PMxC0_ResetStatus_Mask       0x3fff0000ul // Next AMD AGESA reference code will provide this token. define it here for the moment.
		  #endif
    	  // Refer to AMD-CZ reference code (FchInitResetPowerG3Reset). It might be rolled in CZL.
    	  if (AmdFchMmioRead32(AMD_FCH_PMIO_MMIO, 0xC0) & FCH_PMxC0_ResetStatus_Mask) {
    		  *BitStatus = 1;
    	  } else {
    		  *BitStatus = 0;
    	  }
    	  Status = EFI_SUCCESS;
    	  break;

      default: 
    	  break;
    }

    return Status;
}

/**
    Program South Bridge Miscellaneous BIT

    @param SbMiscType   Please check SB_MISC_TYPE for the details
    @param Set          Set/Clear the value of the Miscellaneous BIT

    @retval EFI_UNSUPPORTED   This Miscellaneous BIT is not supported
    @retval EFI_SUCCESS       Success to Set/Clear the value of the Miscellaneous BIT

**/
EFI_STATUS SbProgramMiscBit(
    IN SB_MISC_TYPE         SbMiscType,
    IN BOOLEAN              Set
)
{
	EFI_STATUS	Status = EFI_UNSUPPORTED;
    // Please check the datasheet of the chipset for the register to know
    // how to program the value of the Miscellaneous BIT indicated by SbMiscType.
    // If the type is not supported by the chip, please return EFI_UNSUPPORTED.
    switch (SbMiscType) {
      case CPU_THERMAL_TRIP_STATUS:
    	  break;

      case AFTERG3_EN:
    	  SetAfterG3Bit(Set);
    	  Status = EFI_SUCCESS;

      case PWR_FLR:
    	  // Clear whole status (Set to Clear). Refer to AMD-CZ reference code (FchInitResetPowerG3Reset). It might be rolled in CZL.
    	  if (Set) {
    		  AmdFchMmioOr32(AMD_FCH_PMIO_MMIO, 0xC0, FCH_PMxC0_ResetStatus_Mask);
    	  }
    	  Status = EFI_SUCCESS;
    	  break;

      default: 
    	  break;
    }

    return Status;
}

/**
    Check if any USB port is routed to XHCI controller

    @param VOID

    @return TRUE  There is
    @return FALSE There is not

**/
BOOLEAN SbIsXhciRouting ( 
    VOID 
)
{
	// Raven only XHCI.
	// RVA9 :  To check if XHCI disable ??
    return  TRUE;
}

/**
    Get the Mac Address of the LAN inside the chipset

    @param  MacAddress        Pointer to the buffer used to store the Mac Address

    @retval EFI_UNSUPPORTED   This function is not supported
    @retval EFI_SUCCESS       Success to get the Mac Address

**/
EFI_STATUS SbGetChipLanMacAddress ( 
    IN OUT UINT8            *MacAddress
)
{
/**** PORTING REQUIRED ****
    Please check the datasheet of the chipset for the register to know
    how to get the Mac Address of the LAN inside the chipset.
    For Intel chip, you also can get MAC address from Gbe Region of 
    the flash.
    If it is not supported by the chip or there is no LAN inside the 
    chip, please return EFI_UNSUPPORTED.
**** PORTING REQUIRED ****/
	// RVA9 : Raven has OnChips Lan but Mandolin/Tambourine CRB no hardware layout. Check later.
    return EFI_UNSUPPORTED;
}

/**
    Get Bus/Dev/Func of SbDevType

    @param SbDevType - The type of SB device, refer to SB_DEV_TYPE

    @retval 0xFFFFFFFF        This function is not supported
    @retval Not 0xFFFFFFFF    Bus[31:24]/Dev[23:16]/Func[15:8] of SbDevType

**/
UINTN SbGetPciBusDevFunc ( 
    IN SB_DEV_TYPE  SbDevType
)
{
    switch (SbDevType) {
	case SB_DEV_SATA1 :
		return 0xFFFFFFFF; // RVA9 : The device of AMD Sandstone is behind bridge.
	case SB_DEV_SMBUS :
		return CSP_PCI_CFG_ADDRESS(0, 0x14, 0, 0);
	case SB_DEV_AZALIA :
		return 0xFFFFFFFF;
	case SB_DEV_EHCI2 :
		return 0xFFFFFFFF;
	case SB_DEV_LPC_BRIDGE :
	case SB_DEV_EHCI1 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT1 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT2 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT3 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT4 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT5 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT6 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT7 :
		return 0xFFFFFFFF;
	case SB_DEV_PCI_EX_PORT8 :
		return 0xFFFFFFFF;
	case SB_DEV_THERMAL :
		return 0xFFFFFFFF;
	case SB_DEV_SATA2 :
		return 0xFFFFFFFF;
	case SB_DEV_XHCI :
		return 0xFFFFFFFF; // RVA9 : The device of AMD Sandstone is behind bridge.
	case SB_DEV_LAN :
		return 0xFFFFFFFF; // RVA9 : The device of AMD Sandstone is behind bridge.
	// Above is standard enum both Intel/AMD.
	// The following is AMD only.
	//    Porting required for AMD : Don't touch above. Just append list below.
	case SB_DEV_EHCI3 :
		return 0xFFFFFFFF;

      default:
        return 0xFFFFFFFF;
    }
}

#if defined(AMI_COMPATIBILITY_PKG_VERSION)&&(AMI_COMPATIBILITY_PKG_VERSION > 18)
#if KBC_SUPPORT
/**
    This function detects if the Ctrl + Home key press has been made.
    Is function is only included if KBC_SUPPORT is enabled.  It enables
    the keyboard checks for the Ctrl + Home key press and then disables
    the keyboard

        
    @param PeiServices pointer to the PeiServices Table

    @retval TRUE - Ctrl + Home was pressed
            FALSE - Ctrl + Home not detected

    @note  Please make sure the following items have been done before
           calling IsCtrlHomePressed.
           - The decode of Port 60/64 has been enabled.
           - KBC controller has been enabled in SIO/EC device.
  
**/
BOOLEAN IsCtrlHomePressed (
    EFI_PEI_SERVICES **PeiServices
)
{
  UINT8               Index;
  UINT8               KeyValue = 0;
  UINT8               KeyScan = 0;
  UINT8               LoopCount = CTRL_HOME_CHECK_LOOP;
  UINT8               KbcSts;
  UINT8               KbcSts1;
  UINT8               KbcSts2;
  BOOLEAN             KbcIBF = TRUE;
  BOOLEAN             KbcIBF1 = TRUE;
  UINT8               KbcRes;

  //
  // Enable KBD
  //
  KbcSts = IoRead8 (0x64);
  //
  // Check KeyBoard Presence
  //
  if (KbcSts != 0xFF) {
    //
    // Save the Sys Bit for later use
    //
    KbcRes = KbcSts & 0x04;
    IoWrite8 (0x64, 0x60);  
    //
    // Wait for Input Buffer Empty
    //
    while(KbcIBF) {
      KbcIBF = FALSE;
      KbcSts1 = IoRead8 (0x64);
      if ((KbcSts1 & 0x02) == 0x02) {
        KbcIBF = TRUE;
      }
    }
    //
    // Keyboard enable, Mouse disable
    //
    IoWrite8 (0x60, KbcRes | 0x61);          
    //  
    // Wait for Input Buffer Empty
    //
    while(KbcIBF1) {
      KbcIBF1 = FALSE;
      KbcSts2 = IoRead8 (0x64);
      if ((KbcSts2 & 0x02) == 0x02) {
        KbcIBF1 = TRUE;
      }
    } 
  }  
  //
  // Loop for Key scan
  //
  for (Index = 0 ; Index < LoopCount ; Index++) {
    //
    // Wait at least for 6ms
    //
    CountTime(6000, PM_BASE_ADDRESS);
    //
    // Read Key stroke
    //
    if (IoRead8 (0x64) & 0x01) {
      KeyValue = IoRead8 (0x60);
    }
    //
    // Check for valid key
    //
    if (KeyValue == 0x1d) {
      //
      // Set BIT0 if it is CTRL key
      //
      KeyScan |= (1 << 0);
    }
    
    if (KeyValue == 0x47) {
      //
      // Set BIT1 if it is HOME key
      //
      KeyScan |= (1 << 1);
    }
    //
    // Check for CTRL_HOME Combination
    //
    if ((KeyScan & 0x03) == 0x03) {
      //
      // Disable KeyBoard Controller
      //
      IoWrite8 (0x64, 0x60);
      IoWrite8 (0x60, 0x30);
      return TRUE;
    }
  } // for (Index = 0 ; Index < LoopCount ; Index++)
  //
  // Disable KeyBoard Controller
  //
  IoWrite8 (0x64, 0x60);
  IoWrite8 (0x60, 0x30);
  //
  // No valid key is pressed
  //
  return FALSE;
}
#endif        // KBC_SUPPORT
#endif        // AMI_COMPATIBILITY_PKG_VERSION

/**
    Get South Bridge Information Data

    @param SB_INFO_DATA     Pointer to the SB Information Data.

    @retval VOID

**/
VOID GetSbInfoData ( 
    IN OUT SB_INFO_DATA    *SbInfoData
)
{
    SbInfoData->ChipVendor = CHIPSET_VENDOR;
    SbInfoData->Stepping = 0; // TBD
    SbInfoData->PciePortNum = 7; // RVA9 : No enough info
    SbInfoData->SataPortNum = 8; // RVA9 : No enough info
    SbInfoData->UsbPhysicalPortNum = 3; // RVA9 : I think this depend on board.
    // RVA9 : No enough info
    // 		Reference : PPR - 55570 Rev 0.39 - Sep 9, 2016
    //					InterLock : JANUARY 2017 V1.2
	// Supports an Integrated FCH, with no support for discrete FCH.
	//    USB2: one port.
	//    USB3: 2 ports at 5 Gbps.
	//    USB3.1:
	//        2 Ports at 10 Gbps with USBc altmode and USB Power Delivery 2.0 support.
	//        2 Ports at 10 Gbps.
    SbInfoData->Usb2PortNum = 1;
    SbInfoData->Usb3PortNum = 4 + 2;
}

/**
    Use this function to know if it is warm boot or not.

    @param VOID

    @retval TRUE It is warm boot.

**/
BOOLEAN SbIsWarmBoot (
    VOID
)
{
    /**** PORTING REQUIRED ****
    // Please check the datasheet of the chipset for the register to know
    // how to check warm boot status.
    // If it is not supported by the chip, please return FALSE.
    **** PORTING REQUIRED ****/
	//Here¡¦s the logic to determine Warm Boot through PMxC0.
	//#define S5_WARM_BOOT_BIT (BIT18 | BIT19 | BIT20 | BIT22 | BIT25 | BIT26 | BIT27)
	UINT32	CONST 	WarmBootBits = (BIT18 | BIT19 | BIT20 | BIT22 | BIT25 | BIT26 | BIT27);
	UINT32		  	WarmBootReg = AmdFchMmioRead32 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REGC0);
	BOOLEAN			IsWarmBoot = FALSE;

	if ((WarmBootReg & WarmBootBits) == WarmBootBits) IsWarmBoot = TRUE;

    return IsWarmBoot;
}

/**
    Use this function to know Sleep Type value.

    @param VOID

    @retval UINT32  BOOT_ON_S3_RESUME/BOOT_ON_S4_RESUME/BOOT_ON_S5_RESUME/0: S3 Resume/S4 Resume/S5 Resume/Not a wakeup.

**/
UINT32 SbGetSleepType ( 
    VOID
)
{
	UINT16      Pm1Cnt;
	//
	// make sure the decoder of PM1_STS and PM1_CNTL.
	//
    AmdFchMmioWrite16 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG60, PM_BASE_ADDRESS + SB_ACPI_PM1_STS);
    AmdFchMmioWrite16 (AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG62, PM_BASE_ADDRESS + SB_ACPI_PM1_CNTL);

    // Check WAK_STS bit
    if (IoRead16(PM_BASE_ADDRESS + SB_ACPI_PM1_STS) & B_SB_ACPI_PM1_STS_WAK)
    {
        Pm1Cnt = IoRead16(PM_BASE_ADDRESS + SB_ACPI_PM1_CNTL) & B_SB_ACPI_PM1_CNTL_SLP_TYP;
        // Check the sleep type
        if (Pm1Cnt == V_SB_ACPI_PM1_CNT_S3) return BOOT_ON_S3_RESUME;
        if (Pm1Cnt == V_SB_ACPI_PM1_CNT_S4) return BOOT_ON_S4_RESUME;
        if (Pm1Cnt == V_SB_ACPI_PM1_CNT_S5) return BOOT_ON_S5_RESUME;
    }
    return 0; // Not a wakeup
}

/**
    This function is the reset call interface function published
    by the reset

    @param VOID


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
RETURN_STATUS
EFIAPI
AmiSbMiscLibConstructor (
  )
{
	return 0;
}

