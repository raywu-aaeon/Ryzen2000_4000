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

/** @file PerformanceMeasurementSmm.h
 *  PerformanceMeasurementSmm functions definitions.
 */

#ifndef __PerformanceMeasurementSmm__H__
#define __PerformanceMeasurementSmm__H__
#ifdef __cplusplus
extern "C" {
#endif

/// {F99AAEAA-B653-4cf8-B97A-6BD02B636016}
#define PM_GET_SMM_DATA_GUID {0xf99aaeaa, 0xb653, 0x4cf8, {0xb9, 0x7a, 0x6b, 0xd0, 0x2b, 0x63, 0x60, 0x16}}

#define DP_GAUGE_STRING_LENGTH  30
#define DATA_NAME_LENGTH        30
#define TEMP_HOST_LENGTH        40

typedef struct _PM_SMM_DATA_STRUCTURE{
    UINT32                          Signature;        
    UINT8                           *BufferAddress;
    UINTN                           RecordNumbers;
    DLINK                           LinkList;
} PM_SMM_DATA_STRUCTURE;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
