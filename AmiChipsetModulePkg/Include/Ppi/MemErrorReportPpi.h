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

/** @file MemErrorReportPpi.h
    This header file contains NB protocol definitions and structure
    definitions.

**/

#ifndef FILE_PEI_NBINIT_POLICY_PPI_H_
#define FILE_PEI_NBINIT_POLICY_PPI_H_


//85226559-0def-48d8-a8c9-b746d6a4df01
#define AMI_MEMORY_ERROR_REPORT_PPI_GUID \
  { 0x85226559, 0x0def, 0x48d8, 0xa8, 0xc9, 0xb7, 0x46, 0xd6, 0xa4, 0xdf, 0x01 }

typedef struct _PEI_MEMORY_ERROR_REPORT_PPI PEI_MEMORY_ERROR_REPORT_PPI;

typedef
EFI_STATUS
(EFIAPI *PEI_AMI_MEMORY_ERROR_READ) (
  IN      EFI_PEI_SERVICES                      **PeiServices,  ///< Pointer to PeiServices
  IN struct _PEI_MEMORY_ERROR_REPORT_PPI        *This,          ///< Pointer to the PPI structure
  IN OUT  UINT32                                MemErrData     ///< Memory Error Data Buffer
);

#pragma pack (push, 1)
typedef struct _PEI_MEMORY_ERROR_REPORT_PPI {
    PEI_AMI_MEMORY_ERROR_READ           AmiMemoryErrorRead;
} PEI_MEMORY_ERROR_REPORT_PPI;
#pragma pack (pop)

EFI_STATUS
EFIAPI 
MemoryErrorRead (
  IN      EFI_PEI_SERVICES                      **PeiServices,  ///< Pointer to PeiServices
  IN struct _PEI_MEMORY_ERROR_REPORT_PPI        *This,          ///< Pointer to the PPI structure
  IN OUT  UINT32                                MemErrData     ///< Memroy Error Data Buffer
  );

#define MEMORY_SUCCESS          0x00000000
#define MEMORY_INVALID_TYPE     0x00000001  //Bit 0
#define MEMORY_INVALID_SPEED    0x00000002  //Bit 1
#define MEMORY_SPD_FAIL         0x00000004  //Bit 2
#define MEMORY_INVALID_SIZE     0x00000008  //Bit 3
#define MEMORY_MISMATCH         0x00000010  //Bit 4
#define NO_DIMM_FOUND           0x00000020  //Bit 5
#define MEMORY_NONE_USEFUL      0x00000040  //Bit 6
#define MEMORY_ERROR            0x00000080  //Bit 7

extern	EFI_GUID	gAmiMemoryErrorReportPpiGuid;

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
