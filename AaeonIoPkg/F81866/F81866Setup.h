//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866Setup.h>
//
// Description: GUID or structure Of Setup related Routines.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _F81866_SETUP_H_
#define _F81866_SETUP_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <SioSetup.h>

#ifdef VFRCOMPILE
//----------------------------------------------------------------------
// Constants, Macros and Type Definitions
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//                        Below is for SD files                         
//----------------------------------------------------------------------
#pragma pack(1)

LDX_XV_DATA(FDC)

LDX_XV_DATA(COMA)

LDX_XV_DATA(COMB)

LDX_XV_DATA(COMC)

LDX_XV_DATA(COMD)

LDX_XV_DATA(COME)

LDX_XV_DATA(COMF)

LDX_XV_DATA(LPT)

#pragma pack()

#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F81866_SETUP_H_
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
