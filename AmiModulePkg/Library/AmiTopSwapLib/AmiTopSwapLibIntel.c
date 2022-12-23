//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiTopSwapLibIntel.c
	Implementation of AmiTopSwapLib library class for Intel chipset.

**/

#include <Library/AmiCspFlashLib.h>

/**
  Null Lib stub which is expected to return whether top swap is set or not

  @retval TRUE  Top swap is set
  @retval FALSE Top swap is not set
**/
BOOLEAN AmiIsTopSwapOn(VOID)
{
	return IsTopSwapOn();
}

/**
  Null Lib stub which is expected to set top swap on or off depending on input 

  @param On Set On to TRUE to enable top swap, set On to FALSE to disable top swap

**/
VOID AmiSetTopSwap(IN BOOLEAN On)
{
	SetTopSwap(On);
}
