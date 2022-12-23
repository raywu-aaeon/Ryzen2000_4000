/* $NoKeywords:$ */
/**
 * @file
 *
 *
 * AMD Ccx Microcode Patch Library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 312770 $   @e \$Date: 2015-02-11 13:24:42 +0800 (Wed, 11 Feb 2015) $
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
 **/

#ifndef _CCX_MICROCODE_PATCH_LIB_H_
#define _CCX_MICROCODE_PATCH_LIB_H_
#include "cpuRegisters.h"
#pragma pack (push, 1)

#define MSR_PATCH_LEVEL  0x0000008Bul
#define MSR_PATCH_LOADER 0xC0010020ul
#define AMD_CPUID_FMF    0x80000001ul

/// Microcode patch field definitions
typedef struct {
  UINT32   DateCode;                   ///< Date of patch creation
  UINT32   PatchID;                    ///< Patch level
  UINT16   MicrocodePatchDataID;       ///< Internal use only
  UINT8    MicrocodePatchDataLength;   ///< Internal use only
  UINT8    InitializationFlag;         ///< Internal use only
  UINT32   MicrocodePatchDataChecksum; ///< Doubleword sum of data block
  UINT32   Chipset1DeviceID;           ///< Device ID of 1st Chipset device to match
  UINT32   Chipset2DeviceID;           ///< Device ID of 2nd Chipset device to match
  UINT16   ProcessorRevisionID;        ///< Equivalent ID
  UINT8    Chipset1RevisionID;         ///< Revision level of 1st Chipset device to match
  UINT8    Chipset2RevisionID;         ///< Revision level of 2nd Chipset device to match
  UINT8    BiosApiRevision;            ///< BIOS INT 15 API revision required
  UINT8    Reserved1[3];               ///< Reserved
  UINT32   MatchRegister0;             ///< Internal use only
  UINT32   MatchRegister1;             ///< Internal use only
  UINT32   MatchRegister2;             ///< Internal use only
  UINT32   MatchRegister3;             ///< Internal use only
  UINT32   MatchRegister4;             ///< Internal use only
  UINT32   MatchRegister5;             ///< Internal use only
  UINT32   MatchRegister6;             ///< Internal use only
  UINT32   MatchRegister7;             ///< Internal use only
  UINT8    PatchDataBlock[896];        ///< Raw patch data
  UINT8    Reserved2[896];             ///< Reserved
  UINT8    X86CodePresent;             ///< Boolean to determine if executable code exists
  UINT8    X86CodeEntry[191];          ///< Code to execute if X86CodePresent != 0
} MICROCODE_PATCH;

/// Patch Loader Register
typedef struct {
  UINT64 PatchBase:32;                ///< Linear address of patch header address block
  UINT64 SBZ:32;                      ///< Should be zero
} PATCH_LOADER_MSR;

/// Patch Loader
typedef union {
  UINT64           RawData;           ///< Raw Data
  PATCH_LOADER_MSR BitFields;         ///< BitFields
} PATCH_LOADER;



/* -----------------------------------------------------------------------------*/
/**
 *  Update microcode patch in current processor.
 *
 *  Then reads the patch id, and compare it to the expected, in the Microprocessor
 *  patch block.
 *
 *  @param[in,out] UcodePatchAddr        - The selected UcodePatch address, return 0 if not found
 *  @param[in] StdHeader                 - Config handle for library and services.
 *
 *  @retval    TRUE   - Patch Loaded Successfully.
 *  @retval    FALSE  - Patch Did Not Get Loaded.
 *
 */
BOOLEAN
LoadMicrocodePatch (
  IN OUT   UINT64            *UcodePatchAddr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

#pragma pack (pop)
#endif // _CCX_MICROCODE_PATCH_LIB_H_

