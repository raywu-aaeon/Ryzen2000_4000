//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

/** @file PspNcbUpdate.h

**/
//**********************************************************************
#ifndef _PSP_NCB_UPDATE_H_
#define _PSP_NCB_UPDATE_H_
#ifdef __cplusplus
extern "C" {
#endif

#define RETURN_ERR 1

#pragma pack(1)

typedef struct _PSP_UPDATE_BLOCK_TABLE_STRUCT {
	UINT32 StartAddress;
	UINT32 EndAddress;
	UINT32 BlockOffset;
} PSP_UPDATE_BLOCK_TABLE_STRUCT;

#pragma pack()

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
