//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiCmosLib.c
    South Bridge CMOS Library implementation

*/

#include <Library/AmiCmosLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <SbElinks.h>
#include <Guid/Rtc.h>
#include <Sb.h>
#include <Library/AmiSbMiscLib.h>
#include <Library/AmiFchIoAccessLib.h>

extern SB_RTC_PWR_VALID_CALLBACK SB_RTC_PWR_VALID_CALLBACK_LIST EndOfList;
SB_RTC_PWR_VALID_CALLBACK* SbRtcPwrValidCallbackList[] = { SB_RTC_PWR_VALID_CALLBACK_LIST NULL };


#if CMOS_MANAGER_SUPPORT
/**
    This function is used to access addresses in the CMOS
    register range (0x80-0xff), for PEI and DXE boot phases.

    @param PeiServices - PEI Services table pointer (NULL in DXE phase)
    @param AccessType - ReadType or WriteType to specify the
                          type of access
    @param CmosRegister - The CMOS register to access
    @param CmosParameterValue - Pointer to the data variable to be
                                accessed

    @retval EFI_STATUS (return value) 
            EFI_SUCCESS The access operation was successfully.
            Otherwise A valid EFI error code is returned.

    @note  This function is used when a translation from logical address
              to index port value is required.
**/

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES         **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE         AccessType,
    IN UINT16                   CmosRegister,
    IN OUT UINT8                *CmosParameterValue )
{
    if (CmosRegister < 0x80 || CmosRegister > 0xff)
        return EFI_INVALID_PARAMETER;

    IoWrite8( CMOS_BANK1_INDEX, (UINT8)(CmosRegister-0x80));

    if (AccessType == ReadType) {
        *CmosParameterValue = IoRead8( CMOS_BANK1_DATA );
    }
    else {
        IoWrite8( CMOS_BANK1_DATA, *CmosParameterValue );
    }

    return EFI_SUCCESS;
}

/**
    This function is checked CMOS battery is good or not.

    @param PeiServices - PEI Services table pointer (NULL in DXE phase)

    @retval BOOLEAN  
            TRUE The CMOS is battery is good.
            FALSE The CMOS is battery is bad.
**/
BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES     **PeiServices )
{
	BOOLEAN                 RtcPwrValid = TRUE;
#if !EXTERNAL_RTC_SUPPORT
  	UINT8	Buffer;
  	//
    // AMD FCH no specific status to check CMOS battery. We use "CMOS_USES_STANDARD_BATTERY_TEST".
    // But change FCH VRT sample rate may required. (RTC battery monitor circuit)
  	//		On Raven-Mandolin the VRT bit only be represented when CMOS clear pin (J28 2-3 short)
  	//

	// PM_Reg 59: VRT_T2 set to 4ms x 0x10 value(0x10) AMD recommend.
  	Buffer = AmdFchMmioRead8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59);
	AmdFchMmioWrite8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59, 0x10);

    IoWrite8( CMOS_BANK0_INDEX, CMOS_RTC_STATUS_REGISTER + CMOS_NMI_BIT_VALUE );
	if ((IoRead8( CMOS_BANK0_DATA ) & 0x80) == 0) RtcPwrValid = FALSE;

	// PM_Reg 59: VRT_T2 set to default value(0xff)
	AmdFchMmioWrite8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59, Buffer);
#endif
    return RtcPwrValid;
}

#endif  // #if CMOS_MANAGER_SUPPORT


/**
    This function reads one byte from CMOS register addressed by Index

    @param Index - CMOS Index

    @return The value is read by the index.

**/
UINT8 ReadCmos(
    IN UINT8 Index
)
{
    UINT8       NMI = IoRead8(0x70) & 0x80;   //Read bit 7 (NMI setting).
    UINT8       volatile Value;
    UINT8       Reg;
//------------------
    if(Index<0x80) Reg=0x70;
    else Reg=0x72;

    IoWrite8(Reg, Index | NMI);
    Value = IoRead8(Reg+1);               //Read register.

    return (UINT8)Value;
}

/**
    This function writes value to CMOS register addressed by Index

    @param Index - CMOS register index
    @param Value - Value to write

    @retval VOID

**/
VOID WriteCmos(
    IN UINT8 Index, 
    IN UINT8 Value
)
{
    UINT8       NMI = IoRead8(0x70) & 0x80;   //Read bit 7 (NMI setting).
    UINT8       Reg;
//------------------
    if(Index<0x80) Reg=0x70;
    else Reg=0x72;

    IoWrite8(Reg, Index | NMI);
    IoWrite8(Reg+1, Value);                  //Write Register.
}

/**
    Enable or disable Alternate Access Mode.

    @param Switch TRUE: Enable Alternate Access Mode
                  FALSE: Disable Alternate Access Mode

    @retval VOID
**/
VOID SwitchAlternateAccessMode (
    IN BOOLEAN      Switch
)
{
	// AMD : Port 70 NMI bit is readable. No required.
}

/**
    Read port 70h.

    @param VOID

    @return Data of port 70h.
**/
UINT8 ReadPort70h (
    VOID
)
{
  UINT8  Port70h;

  SwitchAlternateAccessMode (TRUE);

  Port70h = IoRead8(RTC_INDEX_REG);

  SwitchAlternateAccessMode (FALSE);

  return Port70h;
}

/**
    Check NMI bit

    @param VOID

    @retval TRUE  : NMI is enabled.
            FALSE : NMI is disabled.
**/
BOOLEAN SbCheckNmiStatus (
    VOID
)
{
  if (ReadPort70h() & RTC_NMI_MASK) {
    // NMI is disabled.
    return FALSE;
  } else {
    // NMI is Enabled.
    return TRUE;
  }

  return FALSE;
}

/**
    Enable / Disable NMI Bit

    @param Enable - TRUE  : Enable NMI
                    FALSE : Disable NMI

    @retval TRUE  : NMI is enabled
            FALSE : NMI is disabled
**/
BOOLEAN SbEnableDisableNmi (
    IN BOOLEAN      Enable
)
{
  BOOLEAN IntState = GetInterruptState();
  static UINT8   Data8;

  DisableInterrupts();

  Data8 = IoRead8 (CMOS_ADDR_PORT);

  if (Enable)
    Data8 &= ~RTC_NMI_MASK;
  else {
    Data8 |= RTC_NMI_MASK;
  }
  IoWrite8 (CMOS_ADDR_PORT, Data8);

  if (IntState) EnableInterrupts();

  return SbCheckNmiStatus();
}

/**
    Save / Restore NMI bit

    @param Save TRUE  : Save NMI
                FALSE : Restore NMI

    @retval VOID

**/
VOID SbSaveRestoreNmi (
    IN BOOLEAN      Save
)
{
  static  UINT8   NmiMask;
          BOOLEAN IntState = GetInterruptState();
          UINT8   Data8;

  DisableInterrupts();

  if (Save)
    // Save current NMI_EN.
    NmiMask = ReadPort70h() & RTC_NMI_MASK;
  else {
    Data8 = IoRead8 (CMOS_ADDR_PORT) & ~(RTC_NMI_MASK);
    IoWrite8 (CMOS_ADDR_PORT, Data8 | NmiMask);    
  }
  if (IntState) EnableInterrupts();
}

/**
    Check RTC power status

    @param VOID

    @retval TRUE:  Valid
            FALSE: Invalid

**/
BOOLEAN SbIsRtcPwrValid (
    VOID
)
{
  UINT32                  Index;
  BOOLEAN                 RtcPwrValid = TRUE;

#if !EXTERNAL_RTC_SUPPORT
  	UINT8	Buffer;
	// PM_Reg 59: VRT_T2 set to 4ms x 0x10 value(0x10) AMD recommend.
  	Buffer = AmdFchMmioRead8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59);
	AmdFchMmioWrite8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59, 0x10);
	// Add 5 ms delay for reading CMOS status.
	CountTime(5*1000, PM_BASE_ADDRESS);
    IoWrite8( CMOS_BANK0_INDEX, CMOS_RTC_STATUS_REGISTER + CMOS_NMI_BIT_VALUE );
	if ((IoRead8( CMOS_BANK0_DATA ) & 0x80) == 0) RtcPwrValid = FALSE;

	// PM_Reg 59: VRT_T2 set to default value(0xff)
	AmdFchMmioWrite8(AMD_FCH_PMIO_MMIO, FCH_PMIOA_REG59, Buffer);
#endif
  
  for (Index = 0; SbRtcPwrValidCallbackList[Index] != NULL; Index++) {
    RtcPwrValid = SbRtcPwrValidCallbackList[Index]();
  }
  
  return RtcPwrValid;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
