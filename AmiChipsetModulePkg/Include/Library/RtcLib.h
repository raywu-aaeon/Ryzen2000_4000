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
/** @file RtcLib.h
    This header file contains the RtcLib.h definition.

**/
//*************************************************************************

#ifndef RTCLIB_H_
#define RTCLIB_H_

/**
    Read the RTC value at the given Index.

    @param Index RTC Index


    @retval Value RTC Value read from the provided Index

    @note  Here is the control flow of this function:
              1. Read port 0x70 (RTC Index Register) to get bit 7.
                 Bit 7 is the NMI bit-it should not be changed.
              2. Set Index with the NMI bit setting.
              3. Output 0x70 with the Index.
              4. Read 0x71 for Data.
              5. Return the Data.
**/
UINT8
ReadRtcIndex (
  IN UINT8 Index
  );


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
VOID
WriteRtcIndex(
  IN UINT8 Index,
  IN UINT8 Value
  );

#endif /* RTCLIB_H_ */

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
