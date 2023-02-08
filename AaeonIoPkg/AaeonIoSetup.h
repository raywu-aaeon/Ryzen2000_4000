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

//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <xxx.H>
//
// Description: GUID or structure Of Setup related Routines.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _AAEONIO_SETUP_H_
#define _AAEONIO_SETUP_H_
#ifdef __cplusplus
extern "C" {
#endif


void AaeonHHMCommon(
//tag20120326>function declare and definition parameter type is not matched
//    IN      UINTN   RegData,
    IN      UINT64   RegData,
//tag20120326<
    IN      UINT8   Func,
    IN      UINT16  StrToken,
    IN      UINT8   RefValue,
    EFI_HII_HANDLE    hiiHandle
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

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
