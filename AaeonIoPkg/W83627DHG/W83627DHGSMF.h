//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
//<AMI_FHDR_START>
//
// Name:  <W83627DHGSMF.h>
//
// Description: GUID or structure Of Setup related Routines.
//              SMF register save for S3
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _W83627DHGSMF_H
#define _W83627DHGSMF_H
#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <AmiLib.h>
#include <Setup.h>
#include <AmiDxeLib.h>
#include <Protocol/BootScriptSave.h>
//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

UINT8 DXE_SMF_SIO_BootScript_Table[] = {
//neccessary initialized reg
0x0E,0x0F,0x49,0x4A,0x4E,
//Fan Mode Select Register
0x04,0x12,0x62,
//Bootsave for SYSOUT FAN
0x01,0x05,0x07,0x08,0x0A,0x0C,
//Bootsave for CUPOUT FAN0
0x03,0x06,0x07,0x09,0x0B,0x0D,0x67,0x68,
//Bootsave for AXUOUT FAN
0x11,0x13,0x14,0x15,0x16,0x17,
//Bootsave for CUPOUT FAN1
0x61,0x63,0x64,0x65,0x66,0x69,0x6A
};
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

