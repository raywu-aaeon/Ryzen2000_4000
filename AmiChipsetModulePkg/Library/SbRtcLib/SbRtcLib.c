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

//*************************************************************************
/** @file SbRtcLib.c
    This file contains code for SbRtcLib.c
    in the DXE stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/RtcLib.h>
#include <Guid/Rtc.h>

#include <Token.h>
// AMI Compatibility Header.
#include <Library/AmiSbMiscLib.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)


// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    Read the RTC value at the given Index.

    @param Index RTC Index

        UINT8 
    @retval Value RTC Value read from the provided Index

    @note  Here is the control flow of this function:
              1. Read port 0x70 (RTC Index Register) to get bit 7.
                 Bit 7 is the NMI bit-it should not be changed.
              2. Set Index with the NMI bit setting.
              3. Output 0x70 with the Index.
              4. Read 0x71 for Data.
              5. Return the Data.
**/
UINT8 ReadRtcIndex(
    IN UINT8 Index
)
{
    // Read bit 7 (NMI setting).
    UINT8               NMI;
    volatile UINT8      Value;
    BOOLEAN             IntState = GetInterruptState();


    DisableInterrupts();

    Index &= ~RTC_NMI_MASK;

    // Enable Alternate access mode, let port 70h can be readable.
//    SbLibEnableAltAccessMode (TRUE);

    NMI = IoRead8(RTC_INDEX_REG) & RTC_NMI_MASK;

    // Disable Alternate access mode.
//    SbLibEnableAltAccessMode (FALSE);

    IoWrite8(RTC_INDEX_REG, Index | NMI);
    Value = IoRead8(RTC_DATA_REG); // Read register.

    if (IntState) EnableInterrupts();

    if ((Index <= RTC_YEAR_REG) || (Index == ACPI_CENTURY_CMOS)) {
      // Do not call BcdToDecimal8() while the read back value is 
      // invalid and RTC power is failed.
      if ((Value < 0xA0) && ((Value & 0x0F) < 0x0A)) {
        Value = BcdToDecimal8(Value);
      }
    }
        

    return (UINT8)Value;
}

/**
    Write the RTC value at the given Index.

    @param Index RTC Index
    @param Value Value to be written

    @retval VOID

    @note  Here is the control flow of this function:
              1. Read port 0x70 (RTC Index Register) to get bit 7.
                 Bit 7 is the NMI bit-it should not be changed.
              2. Set Index with the NMI bit setting.
              3. Output 0x70 with the Index.
              4. Write the data to 0x71.
**/
VOID WriteRtcIndex(
    IN UINT8 Index,
    IN UINT8 Value
)
{
    // Read bit 7 (NMI setting).
    UINT8   NMI;
    BOOLEAN IntState = GetInterruptState();

    if ((Index <= RTC_YEAR_REG) || (Index == ACPI_CENTURY_CMOS))
        Value = DecimalToBcd8(Value);

    DisableInterrupts();

    Index &= ~RTC_NMI_MASK;

    // Enable Alternate access mode, let port 70h can be readable.
//    SbLibEnableAltAccessMode (TRUE);

    NMI = IoRead8(RTC_INDEX_REG) & RTC_NMI_MASK;

    // Disable Alternate access mode.
//    SbLibEnableAltAccessMode (FALSE);

    IoWrite8(RTC_INDEX_REG, Index | NMI);
    IoWrite8(RTC_DATA_REG, Value); // Write Register.

    if (IntState) EnableInterrupts();
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
