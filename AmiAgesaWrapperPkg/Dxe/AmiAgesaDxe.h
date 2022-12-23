//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiAgesaDxe.h
    AMI DXE AGESA wrapper to build ACPI P-State tables.

**/
#ifndef _AMI_AGESA_DXE_H_
#define _AMI_AGESA_DXE_H_
#ifdef __cplusplus
extern "C" {
#endif

//
// Include files
//

#include <Token.h>


#define DIMM_SPD_DATA_LENGTH        512     // 512 Bytes SPD Data
#define DIMM_DEVICE_SLOT_COUNT      DIMM_SLOTS_PER_SCKT       // Dimm Slot depends on platform
#define DIMM_SPD_SERIAL_NO_LENGTH   4       // 4   Bytes Serial Number
#define DIMM_SPD_PART_NO_LENGTH     18      // 18  Bytes Part Number

// 16  Bytes Serial no Data
#define DIMM_HOB_SERIAL_NO_LENGTH   DIMM_SPD_SERIAL_NO_LENGTH * DIMM_DEVICE_SLOT_COUNT
// 512 Bytes * DIMM number Hob Data
#define DIMM_HOB_DATA_LENGTH        DIMM_SPD_DATA_LENGTH * DIMM_DEVICE_SLOT_COUNT

#define DIMM_SPD_SERIAL_NO_OFFSET_DDR4  0x145   // DDR4 SPD Serial Data Offset 325

#pragma pack (push, 1)
typedef struct {
    EFI_HOB_GUID_TYPE       Header;
    UINT8                   SPD_Serial[DIMM_HOB_SERIAL_NO_LENGTH];
    UINT8                   SPD_Data[DIMM_HOB_DATA_LENGTH];
    UINT8                   SPDUpdate;      // a flag to indicate if we need to set variable in DXE
} SPD_BYPASS_HOB;
#pragma pack (pop)

#define TOTAL_DIMM_SLOTS_IN_SYSTEM DIMM_SLOTS_PER_SCKT * NSOCKETS
#define MEMRESTORE_SERIAL_HOB_LENGTH TOTAL_DIMM_SLOTS_IN_SYSTEM * DIMM_SPD_SERIAL_NO_LENGTH

#pragma pack (push, 1)
typedef struct {
    EFI_HOB_GUID_TYPE       Header;
    UINT8                   SPD_Serial[MEMRESTORE_SERIAL_HOB_LENGTH];
    UINT8                   SPDUpdate;      // a flag to indicate if we need to set variable in DXE
} MEMRESTORE_SERIAL_HOB;

typedef struct {
     OUT   UINT32 Signature;           ///< "ASTR" for AMD Suspend-To-RAM
     OUT   UINT16 Version;             ///< S3 Params version number
  IN OUT   UINT32 Flags;               ///< Indicates operation
  IN OUT   UINT32 NvStorage;          ///< Pointer to memory critical save state data
  IN OUT   UINT32 NvStorageSize;       ///< Size in bytes of the NvStorage region
  IN OUT   UINT32 VolatileStorage;    ///< Pointer to remaining AMD save state data
  IN OUT   UINT32 VolatileStorageSize; ///< Size in bytes of the VolatileStorage region
} AMI_S3_PARAMS;

typedef struct {
    EFI_HOB_GUID_TYPE    Header;
    UINT8                Count;
    UINT32               Checksum;
    BOOLEAN              First;
    BOOLEAN              SaveMemContext;
    AMI_S3_PARAMS        MemContext;
} MEM_RESTORE_HOB;
#pragma pack (pop)

//
// Module entry point
//
EFI_STATUS
EFIAPI
AmiAgesaDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

extern EFI_GUID gAmiAgesaSpdByPassHobGuid;
extern EFI_GUID gAmiAgesaMemRestoreSerialHobGuid;
extern EFI_GUID gAmiAgesaMemRestoreGuid;
extern EFI_GUID gAmiAgesaAcpiSleepStateBackupGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif  
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
