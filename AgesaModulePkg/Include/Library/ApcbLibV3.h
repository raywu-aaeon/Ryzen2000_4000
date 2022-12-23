/* $NoKeywords:$ */
/**
 * @file
 *
 * ApcbLibV3.h
 *
 * AGESA PSP Customization Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem)
 * @e \$Revision: 192403 $ @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
 *
 **/
/*****************************************************************************
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
*
*/

#ifndef _APCB_LIB_V3_H_
#define _APCB_LIB_V3_H_

#include "Porting.h"
#include <Addendum/Apcb/Inc/SSP/ApcbMemDdrPostPackageRepair.h>

#define INVALID_PRIORITY_LEVEL        0xFF
#define INVALID_BIOS_DIR_ENTRY        0xFF
#define INVALID_BINARY_INSTANCE       0xFF
#define INVALID_TYPE_INSTANCE         0xFF

typedef struct {
  UINT8                   PriorityLevel;
  UINT8                   BiosDirEntry;
  UINT8                   BinaryInstance;
  UINT8                   TypeInstance;
} PRIORITY_INSTANCE_MAPPING;

UINT8
ApcbCalcCheckSum (
  IN       VOID             *ApcbPtr,
  IN       UINT32           Length
  );

VOID *
GetApcbShadowCopy (
  IN OUT  UINT32  *Size
  );

VOID
SetApcbShadowCopy (
  IN      VOID * ApcbShadowAddress
  );

BOOLEAN
ApcbAcquireMutex (
  );

VOID
ApcbReleaseMutex (
  );

VOID
ApcbSetPurpose (
  IN       UINT8         Purpose
  );

UINT8
ApcbGetPurpose (
  VOID
  );

VOID
ApcbSetPriorityLevel (
  IN       UINT8         PriorityLevel
  );

BOOLEAN
ApcbGetBool (
  IN       UINT32        ApcbToken,
      OUT  BOOLEAN       *Value
  );

BOOLEAN
ApcbSetBool (
  IN       UINT32        ApcbToken,
  IN       BOOLEAN       Value
  );

BOOLEAN
ApcbGet8 (
  IN       UINT32        ApcbToken,
      OUT  UINT8         *Value
  );

BOOLEAN
ApcbSet8 (
  IN       UINT32        ApcbToken,
  IN       UINT8         Value
  );

BOOLEAN
ApcbGet16 (
  IN       UINT32        ApcbToken,
      OUT  UINT16        *Value
  );

BOOLEAN
ApcbSet16 (
  IN       UINT32        ApcbToken,
  IN       UINT16        Value
  );

BOOLEAN
ApcbGet32 (
  IN       UINT32        ApcbToken,
      OUT  UINT32        *Value
  );

BOOLEAN
ApcbSet32 (
  IN       UINT32        ApcbToken,
  IN       UINT32        Value
  );

BOOLEAN
ApcbGetType (
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
      OUT  UINT8         **DataBuf,
      OUT  UINT32        *DataSize
  );

BOOLEAN
ApcbSetType (
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
  IN       UINT8         *DataBuf,
  IN       UINT32        DataSize
  );

BOOLEAN
ApcbPurgeAllTokens (
  VOID
  );

BOOLEAN
ApcbPurgeAllTypes (
  VOID
  );

BOOLEAN
ApcbEnumerateTokens (
  VOID
  );

EFI_STATUS
AmdPspWriteBackApcbShadowCopy (
  VOID
  );

EFI_STATUS
ApcbGetDramPostPkgRepairEntries (
  IN OUT   APCB_DPPRCL_REPAIR_ENTRY **pApcbDppRepairEntries,
  IN OUT   UINT32                   *SizeInByte
  );

EFI_STATUS
ApcbClearDramPostPkgRepairEntry (
  VOID
  );

EFI_STATUS
ApcbAddDramPostPkgRepairEntry (
  IN       APCB_DPPRCL_REPAIR_ENTRY *Entry
  );

EFI_STATUS
ApcbRemoveDramPostPkgRepairEntry (
  IN       APCB_DPPRCL_REPAIR_ENTRY *Entry
  );

BOOLEAN
ApcbV2GetConfigToken (
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

BOOLEAN
ApcbV2SetConfigToken (
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  );

#endif


