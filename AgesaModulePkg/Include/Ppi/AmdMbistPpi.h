/*****************************************************************************
 *
 * Copyright 2017 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 **/
#ifndef _AMD_MBIST_PPI_H_
#define _AMD_MBIST_PPI_H_


//----------------------------------------------------
//
//  AMD MBIST PEI Initialization Complete PPI
//
//-------------------------------------------------------

typedef struct _MBIST_TEST_STATUS {
  UINT8	ResultValid[MAX_MBIST_SUBTEST][MAX_CHANNELS_PER_DIE];
  UINT8	ErrorStatus[MAX_MBIST_SUBTEST][MAX_CHANNELS_PER_DIE];
} MBIST_TEST_STATUS;

//
// MBIST DATA EYE
//
typedef struct _MBIST_MARGIN {
  UINT8  PositiveEdge;
  UINT8  NegativeEdge;
} MBIST_MARGIN;

typedef struct _MBIST_DATA_EYE_MARGIN {
  MBIST_MARGIN  ReadDqDelay;    ///< Smallest Positive and Negative Read Dq Delay margin
  MBIST_MARGIN  ReadVref;       ///< Smallest Positive and Negative Read Vref delay
  MBIST_MARGIN  WriteDqDelay;   ///< Smallest Positive and Negative Write Dq Delay margin
  MBIST_MARGIN  WriteVref;      ///< Smallest Positive and Negative Write Vref delay
} MBIST_DATA_EYE_MARGIN;

typedef struct _MBIST_DATA_EYE_MARGIN_RECORD {
  BOOLEAN                IsDataEyeValid;    ///< Is Data Eye Record Valid
  MBIST_DATA_EYE_MARGIN  DataEyeMargin;     ///< DataEyeRecord
} MBIST_DATA_EYE_MARGIN_RECORD;

typedef struct _MBIST_DATA_EYE {
  MBIST_DATA_EYE_MARGIN_RECORD  MbistDataEyeRecord[MAX_CHANNELS_PER_DIE][MAX_CHIPSELECT_PER_CHANNEL];
} MBIST_DATA_EYE;
//
// PPI function Prototype
//
typedef EFI_STATUS (EFIAPI * PEI_GET_MBIST_TEST_RESULTS) (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN UINT32 *BufferSize,
  IN OUT MBIST_TEST_STATUS  *MbistTestResults
);

typedef EFI_STATUS (EFIAPI * PEI_GET_MBIST_DATA_EYE) (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN UINT32 *BufferSize,
  IN OUT MBIST_DATA_EYE  *MbistDataEye
);

typedef struct _AMD_MEMORY_MBIST_TEST_RESULTS_PPI {
  UINT32                        Revision;
  MBIST_TEST_STATUS             MbistTestStatus [MAX_SOCKETS][MAX_DIES_PER_SOCKET];
  MBIST_DATA_EYE                MbistDataEyeMargin[ MAX_SOCKETS][MAX_DIES_PER_SOCKET];
  PEI_GET_MBIST_TEST_RESULTS    GetMbistTestResults;
  PEI_GET_MBIST_DATA_EYE        GetMbistDataEyeMargin;
} AMD_MEMORY_MBIST_TEST_RESULTS_PPI;

// Current PPI revision
#define AMD_MBIST_PPI_REVISION   0x03

extern EFI_GUID gAmdMbistPeiPpiGuid;

#endif  //_AMD_MBIST_PPI_H_

