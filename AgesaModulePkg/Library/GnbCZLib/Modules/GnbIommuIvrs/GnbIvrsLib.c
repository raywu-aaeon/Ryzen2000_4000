/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe ALIB
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
*****************************************************************************
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbPcie.h"
#include  "GnbIommu.h"
#include  "GnbFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbIommuIvrs.h"
#include  "GnbIvrsLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBIOMMUIVRS_GNBIVRSLIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Create IVHDR entry for device range
 *
 *
 * @param[in]  StartRange      Address of start range
 * @param[in]  EndRange        Address of end range
 * @param[in]  DataSetting     Data setting
 * @param[in]  Ivhd            Pointer to IVHD entry
 * @param[in]  StdHeader       Standard configuration header
 *
 */
VOID
GnbIvhdAddDeviceRangeEntry (
  IN       PCI_ADDR             StartRange,
  IN       PCI_ADDR             EndRange,
  IN       UINT8                DataSetting,
  IN       IVRS_IVHD_ENTRY      *Ivhd,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  IVHD_GENERIC_ENTRY  *Entry;
  Entry = (IVHD_GENERIC_ENTRY *) ((UINT8 *) Ivhd + Ivhd->Length);
  Entry->Type = IvhdEntryStartRange;
  Entry->DeviceId = DEVICE_ID (StartRange);
  Entry->DataSetting = DataSetting;
  Ivhd->Length += sizeof (IVHD_GENERIC_ENTRY);
  Entry = (IVHD_GENERIC_ENTRY *) ((UINT8 *) Ivhd + Ivhd->Length);
  Entry->Type = IvhdEntryEndRange;
  Entry->DeviceId = DEVICE_ID (EndRange);
  Ivhd->Length += sizeof (IVHD_GENERIC_ENTRY);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Create IVHDR entry for aliased range
 *
 *
 * @param[in]  StartRange      Address of start range
 * @param[in]  EndRange        Address of end range
 * @param[in]  Alias           Address of alias requestor ID for range
 * @param[in]  DataSetting     Data setting
 * @param[in]  Ivhd            Pointer to IVHD entry
 * @param[in]  StdHeader       Standard configuration header
 *
 */
VOID
GnbIvhdAddDeviceAliasRangeEntry (
  IN       PCI_ADDR             StartRange,
  IN       PCI_ADDR             EndRange,
  IN       PCI_ADDR             Alias,
  IN       UINT8                DataSetting,
  IN       IVRS_IVHD_ENTRY      *Ivhd,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  IVHD_ALIAS_ENTRY    *RangeEntry;
  IVHD_GENERIC_ENTRY  *Entry;
  UINT16              Offset;
  Offset = (Ivhd->Length + 0x7) & (~ 0x7);
  RangeEntry = (IVHD_ALIAS_ENTRY *) ((UINT8 *) Ivhd + Offset);
  RangeEntry->Type = IvhdEntryAliasStartRange;
  RangeEntry->DeviceId = DEVICE_ID (StartRange);
  RangeEntry->AliasDeviceId = DEVICE_ID (Alias);
  RangeEntry->DataSetting = DataSetting;
  Ivhd->Length = sizeof (IVHD_ALIAS_ENTRY) + Offset;
  Entry = (IVHD_GENERIC_ENTRY *) ((UINT8 *) Ivhd + Ivhd->Length);
  Entry->Type = IvhdEntryEndRange;
  Entry->DeviceId = DEVICE_ID (EndRange);
  Ivhd->Length += sizeof (IVHD_GENERIC_ENTRY);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Create IVHDR entry for special device
 *
 *
 * @param[in]  SpecialDevice   Special device Type
 * @param[in]  Device          Address of requestor ID for special device
 * @param[in]  Id              Apic ID/ Hpet ID
 * @param[in]  DataSetting     Data setting
 * @param[in]  Ivhd            Pointer to IVHD entry
 * @param[in]  StdHeader       Standard configuration header
 *
 */
VOID
GnbIvhdAddSpecialDeviceEntry (
  IN       IVHD_SPECIAL_DEVICE  SpecialDevice,
  IN       PCI_ADDR             Device,
  IN       UINT8                Id,
  IN       UINT8                DataSetting,
  IN       IVRS_IVHD_ENTRY      *Ivhd,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  IVHD_SPECIAL_ENTRY  *SpecialEntry;
  UINT16               Offset;
  Offset = (Ivhd->Length + 0x7) & (~ 0x7);
  SpecialEntry = (IVHD_SPECIAL_ENTRY *) ((UINT8 *) Ivhd + Offset);
  SpecialEntry->Type = IvhdEntrySpecialDevice;
  SpecialEntry->AliasDeviceId = DEVICE_ID (Device);
  SpecialEntry->Variety = (UINT8) SpecialDevice;
  SpecialEntry->Handle = Id;
  SpecialEntry->DataSetting = DataSetting;
  Ivhd->Length = sizeof (IVHD_SPECIAL_ENTRY) + Offset;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Create IVMD entry
 *
 *
 * @param[in]  Type            Root type for IVMD (IvrsIvmdBlock or IvrsIvmdrBlock)
 * @param[in]  StartDevice     Device ID of start device range
 *                             Use 0x0000 for ALL
 * @param[in]  EndDevice       Device ID of end device range
 *                             Use 0xFFFF for ALL
 *                             Use == StartDevice for specific device
 * @param[in]  BlockAddress    Address of memory block to be excluded
 * @param[in]  BlockLength     Length of memory block go be excluded
 * @param[in]  Ivmd            Pointer to IVMD entry
 * @param[in]  StdHeader       Standard configuration header
 *
 */
VOID
GnbIvmdAddEntry (
  IN       IVRS_BLOCK_TYPE      Type,
  IN       UINT16               StartDevice,
  IN       UINT16               EndDevice,
  IN       UINT64               BlockAddress,
  IN       UINT64               BlockLength,
  IN       IVRS_IVMD_ENTRY      *Ivmd,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  Ivmd->Flags = IVMD_FLAG_EXCLUSION_RANGE;
  Ivmd->Length = sizeof (IVRS_IVMD_ENTRY);
  Ivmd->DeviceId = StartDevice;
  Ivmd->AuxiliaryData = 0x0;
  Ivmd->Reserved = 0x0000000000000000;
  Ivmd->BlockStart = BlockAddress;
  Ivmd->BlockLength = BlockLength;
  if (Type == IvrsIvmdBlock) {
    if (StartDevice == EndDevice) {
      Ivmd->Type = IvrsIvmdBlockSingle;
    } else if ((StartDevice == 0x0000) && (EndDevice == 0xFFFF)) {
      Ivmd->Type = IvrsIvmdBlock;
    } else {
      Ivmd->Type = IvrsIvmdBlockRange;
      Ivmd->AuxiliaryData = EndDevice;
    }
  } else {
    if (StartDevice == EndDevice) {
      Ivmd->Type = IvrsIvmdrBlockSingle;
    } else {
      Ivmd->Type = IvrsIvmdrBlock;
    }
  }
}


