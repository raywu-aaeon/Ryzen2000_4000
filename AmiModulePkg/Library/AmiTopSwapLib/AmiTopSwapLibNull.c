//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiTopSwapLibNull.c
	Null Lib implementation of AmiTopSwapLib library class.

**/

/**
  Null Lib stub which is expected to return whether top swap is set or not

  @retval TRUE  Top swap is set
  @retval FALSE Top swap is not set
**/
BOOLEAN AmiIsTopSwapOn(VOID)
{
	return FALSE;
}

/**
  Null Lib stub which is expected to set top swap on or off depending on input 

  @param On Set On to TRUE to enable top swap, set On to FALSE to disable top swap

**/
VOID AmiSetTopSwap(IN BOOLEAN On)
{
	return;
}
