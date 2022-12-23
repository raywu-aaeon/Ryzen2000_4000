/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD S3 save library
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
#include "AMD.h"
#include "Filecode.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdS3SaveLib.h"
#include "Library/IdsLib.h"
#include <Library/PciLib.h>

#define FILECODE LIBRARY_AMDS3SAVELIB_WOS3SAVE_AMDWOS3SAVELIB_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
AmdS3IoWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdIoWrite (Width, (UINT16) Address, Value, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3IoRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdIoRMW (Width, (UINT16) Address, Data, DataMask, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3IoPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdIoPoll (Width, (UINT16) Address, Data, DataMask, Delay, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3MemWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdMemWrite (Width, Address, Value, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3MemRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdMemRMW (Width, Address, Data, DataMask, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3MemPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  LibAmdMemPoll (Width, Address, Data, DataMask, Delay, StdHeader);

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3PciWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Value,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  switch (Width) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    PciWrite8 (PciAddress, *((UINT8 *) Value));
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    PciWrite16 (PciAddress, *((UINT16 *) Value));
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    PciWrite32 (PciAddress, *((UINT32 *) Value));
    break;
  default:
    IDS_ERROR_TRAP;
  }

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3PciRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  TempData;
  UINT32  TempMask;
  LibAmdGetDataFromPtr (Width, Data,  DataMask, &TempData, &TempMask);

  switch (Width) {
  case AccessWidth8:
  case AccessS3SaveWidth8:
    PciAndThenOr8 (PciAddress, (UINT8) (~TempMask), (UINT8) TempData);
    break;
  case AccessWidth16:
  case AccessS3SaveWidth16:
    PciAndThenOr16 (PciAddress, (UINT16) (~TempMask), (UINT16) TempData);
    break;
  case AccessWidth32:
  case AccessS3SaveWidth32:
    PciAndThenOr32 (PciAddress, (~TempMask), TempData);
    break;
  default:
    IDS_ERROR_TRAP;
  }

  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptIoWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptIoRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptIoPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptMemWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Value
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptMemRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptMemPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINT64        Address,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptPciWrite (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Value
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptPciRMW (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptPciPoll (
  IN       ACCESS_WIDTH  Width,
  IN       UINTN         PciAddress,
  IN       VOID          *Data,
  IN       VOID          *DataMask,
  IN       UINT64        Delay
  )
{
  return AGESA_SUCCESS;
}

AGESA_STATUS
AmdS3SaveScriptDispatch (
  IN       VOID          *EntryPoint,
  IN       VOID          *Context
  )
{
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


