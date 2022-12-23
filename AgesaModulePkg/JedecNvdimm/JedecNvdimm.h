/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimm.h
 * 
 * 
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */

/** @file JedecNvdimm.h
    Header file for JedecNvdimm Driver

**/

#ifndef _JEDEC_NVDIMM_H_
#define _JEDEC_NVDIMM_H_

//---------------------------------------------------------------------------

#include <Library/DebugLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/IoLib.h>

#define PM_TMR_BLK_ADDRESS  0x808
#define PM_BASE_ADDRESS     0x800
#define EFI_ACPI_TABLE_VERSION_X        (EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0 | EFI_ACPI_TABLE_VERSION_4_0)

#define INPUT_DATA_SIZE     0x100   // TODO: largest size of input?
#define OUTPUT_DATA_SIZE    0x100   // TODO: largest size of output?

#define JEDEC_NVDIMM_SMM_PROTOCOL_GUID \
    {0x7b7a8cad, 0xab14, 0x45cf, {0x8e, 0xeb, 0xe2, 0x30, 0xb2, 0xa, 0x12, 0x68}}

#pragma pack (1)

typedef struct _DSM_ACPI_SMM_DATA {
    UINT32  FunctionIndex;                  // Function Index 0 - 31
    UINT32  InputDataSize;                  // Size of input data
    UINT8   InputData[INPUT_DATA_SIZE];     // Input data (bytes)
    UINT32  OutputDataSize;                 // Size of output data
    UINT8   OutputData[OUTPUT_DATA_SIZE];   // Output data (bytes)
    UINT16  NfitDeviceHandle;               // NFIT Device Handle
    UINT32  NvdimmBitMap;                   // NVDIMM Bitmap
} DSM_ACPI_SMM_DATA;

/**
    Structure to keep SMM timeout data.
 */
typedef struct {
    UINTN  OverFlow;
    UINTN  EndValue;
    UINTN  OldTimerValue;
} SMM_TIMEOUT;

/**
    Defines ACPI timer width in bits
 */
#define NUM_BITS_IN_ACPI_TIMER      32

///< Buffer for each NVDIMM, keep SPD data for ACPI NFIT table
typedef struct {
    UINT16    DataValid;                ///< 0x55aa --> data valid in this entry
    UINT8     Socket;                   ///< Socket
    UINT8     Channel;                  ///< Channel
    UINT8     Dimm;                     ///< Dimm
    UINT16    NvdimmIndex;              ///< Dimm index
    UINT16    Handle;                   ///< TYPE17->Handle
    UINT16    Spd192;                   ///< 
    UINT16    Spd194;                   ///< 
    UINT16    Spd196;                   ///< 
    UINT16    Spd198;                   ///< High byte reserved, set to 0
    UINT16    Spd320;                   ///< 
    UINT16    Spd322;                   ///< High byte reserved, set to 0
    UINT16    Spd323;                   ///< 
    UINT8     SerialNumber[4];          ///< SPD 325 ~ 328
    UINT16    Spd349;                   ///< High byte reserved, set to 0
    UINT16    Reserved;                 ///< Reserved
} NVDIMM_SPD_INFO;

typedef struct _JEDEC_NVDIMM_SMM_PROTOCOL  JEDEC_NVDIMM_SMM_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *READ_MEM_ERROR_COUNTERS)(
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    OUT UINT8                           *DramEccErrorCount,
    OUT UINT8                           *DramThresholdEccCount
);

typedef
EFI_STATUS
(EFIAPI *SET_MEM_ERROR_COUNTERS)(
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN UINT8                            DramEccErrorCount,
    IN UINT8                            DramThresholdEccCount
);

typedef
EFI_STATUS
(EFIAPI *INCREMENT_MEM_ERROR_COUNTERS)(
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN BOOLEAN                          IncDramEccErrorCount,
    IN BOOLEAN                          IncDramThresholdEccCount
);

typedef
EFI_STATUS
(EFIAPI *PERFORM_NVDIMM_PURGE)(
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm
);

struct _JEDEC_NVDIMM_SMM_PROTOCOL {
    READ_MEM_ERROR_COUNTERS         ReadMemoryErrorCounters;
    SET_MEM_ERROR_COUNTERS          SetMemoryErrorCounters;
    INCREMENT_MEM_ERROR_COUNTERS    IncrementMemErrorCounters;
    PERFORM_NVDIMM_PURGE            PerformNvdimmPurge;
};

#pragma pack ()

EFI_STATUS
EFIAPI
ReadMemoryErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    OUT UINT8                           *DramEccErrorCount,
    OUT UINT8                           *DramThresholdEccCount
);

EFI_STATUS
EFIAPI
SetMemoryErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN UINT8                            DramEccErrorCount,
    IN UINT8                            DramThresholdEccCount
);

EFI_STATUS
EFIAPI
IncrementMemErrorCounters (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm,
    IN BOOLEAN                          IncDramEccErrorCount,
    IN BOOLEAN                          IncDramThresholdEccCount
);

EFI_STATUS
EFIAPI
PerformNvdimmPurge (
    IN CONST JEDEC_NVDIMM_SMM_PROTOCOL  *This,
    IN UINT8                            Socket,
    IN UINT8                            Channel,
    IN UINT8                            Dimm
);

#endif  // JEDEC_NVDIMM_H


