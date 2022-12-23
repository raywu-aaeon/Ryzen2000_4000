//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


//*************************************************************************
/** @file EcLib.h
    This file platform library for EC access which the AmdCpmOemTable.c applied.
    in the AMD CPM common code.  AMD should remove the IBV library in
    the common code.

**/
//*************************************************************************

#ifndef  _CPM_AMI_TEMP_EC_LIB_H   //To Avoid this header get compiled twice
#define  _CPM_AMI_TEMP_EC_LIB_H


/**
	This function provide the EC ram read.
	determine board layout. for the AMD CPM reference code AmdCpmOemTable.c.

    @param Index Index of EC RAM

    @retval UINT8 read a byte data
**/
UINT8
EcRead(
  IN UINT8  Index
  );

#endif // _CPM_AMI_TEMP_EC_LIB_H

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
