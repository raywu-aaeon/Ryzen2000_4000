/* $NoKeywords:$ */
/**
 * @file
 *
 * Base Fabric MMIO map manager Lib implementation for UNB
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include "Library/BaseLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdS3SaveLib.h"
#include "Library/FabricResourceManagerLib.h"
#include <Library/PciLib.h>
#include "FabricResourceManagerUnbLib.h"

#define FILECODE LIBRARY_FABRICRESOURCEMANAGERUNBLIB_FABRICRESOURCEMANAGERUNBLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
STATIC CONST UINT16 ROMDATA MmioBaseLowRegOffset[MMIO_REG_PAIR_NUM] = {0x80, 0x88, 0x90, 0x98, 0xA0, 0xA8, 0xB0, 0xB8, 0x1A0, 0x1A8, 0x1B0, 0x1B8};
STATIC CONST UINT16 ROMDATA MmioLimitLowRegOffset[MMIO_REG_PAIR_NUM] = {0x84, 0x8C, 0x94, 0x9C, 0xA4, 0xAC, 0xB4, 0xBC, 0x1A4, 0x1AC, 0x1B4, 0x1BC};
STATIC CONST UINT16 ROMDATA MmioBaseLimitHiRegOffset[MMIO_REG_PAIR_NUM] = {0x180, 0x184, 0x188, 0x18C, 0x190, 0x194, 0x198, 0x19C, 0x1C0, 0x1C4, 0x1C8, 0x1CC};

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * BSC entry point for for adding MMIO map
 *
 * program MMIO base/limit registers
 *
 * @param[in, out]    BaseAddress        Starting address of the requested MMIO range.
 * @param[in, out]    Length             Length of the requested MMIO range.
 * @param[in]         Alignment          Alignment bit map.
 * @param[in]         Target             PCI bus number of the requestor.
 * @param[in, out]    Attributes         Attributes of the requested MMIO range indicating whether
 *                                       it is readable/writable/posted/secured/s3saved.
 *
 * @retval            EFI_STATUS         EFI_OUT_OF_RESOURCES - The requested range could not be added because there are not
 *                                                              enough mapping resources.
 *                                       EFI_NOT_FOUND        - One or more input parameters are invalid. For example, the
 *                                                              PciBusNumber does not correspond to any device in the system.
 *                                       EFI_WRITE_PROTECTED  - Locked
 *                                       EFI_SUCCESS          - Adding MMIO map succeeds
 */
EFI_STATUS
FabricAllocateMmio (
  IN OUT   UINT64 *BaseAddress,
  IN OUT   UINT64 *Length,
  IN       UINT64                 Alignment,
  IN       FABRIC_TARGET          Target,
  IN OUT   FABRIC_MMIO_ATTRIBUTE *Attributes
  )
{
  UINT8               i;
  UINT8               j;
  UINT8               UnusedMmioPair;
  UINT8               MmioPair;
  UINT8               ConfMapRange;
  PCI_ADDR            PciAddress;
  MMIO_BASE_LOW       MmioBaseLow;
  MMIO_LIMIT_LOW      MmioLimitLow;
  MMIO_BASE_LIMIT_HI  MmioBaseLimitHi;
  MMIO_RANGE          MmioRange[MMIO_REG_PAIR_NUM];
  MMIO_RANGE          MmioRangeTemp;
  MMIO_RANGE          NewMmioRange;
  MMIO_RANGE          FragmentMmioRange;
  CONFIGURATION_MAP   ConfMapRegister;
  BOOLEAN             Overlap;
  BOOLEAN             NewMmioIncluded;

  UnusedMmioPair = 0;
  // FragmentMMioRange is used for record the MMIO range which is splitted by overriding.
  FragmentMmioRange.Attribute.ReadEnable = 0;
  FragmentMmioRange.Attribute.WriteEnable = 0;
  FragmentMmioRange.Base = 0;
  FragmentMmioRange.Limit = MMIO_ALIGN;

  PciAddress.AddressValue = MAKE_SBDFO (0, 0, 0x18, FUNC_1, MmioBaseLowRegOffset[0]);
  IDS_HDT_CONSOLE (MAIN_FLOW, "MMIO map configuration before merging:\n");
  IDS_HDT_CONSOLE (MAIN_FLOW, "    Base                 Limit               NP RE WE Lock DstNode DstLink DstSubLink\n");
  for (MmioPair = 0; MmioPair < MMIO_REG_PAIR_NUM; MmioPair++) {
    // MMIO base low
    PciAddress.Address.Register = MmioBaseLowRegOffset[MmioPair];
    *((UINT32 *) &MmioBaseLow)  = PciRead32 (PciAddress.AddressValue);
    // MMIO limit low
    PciAddress.Address.Register = MmioLimitLowRegOffset[MmioPair];
    *((UINT32 *) &MmioLimitLow) = PciRead32 (PciAddress.AddressValue);
    // MMIO base/limit high
    PciAddress.Address.Register = MmioBaseLimitHiRegOffset[MmioPair];
    *((UINT32 *) &MmioBaseLimitHi) = PciRead32 (PciAddress.AddressValue);
    // get MMIO info
    MmioRange[MmioPair].Base = LShiftU64 (MmioBaseLow.MmioBase, 16) | LShiftU64 (((UINT64) MmioBaseLimitHi.MmioBase), 40);
    MmioRange[MmioPair].Limit = (LShiftU64 (MmioLimitLow.MmioLimit, 16) | LShiftU64 (((UINT64) MmioBaseLimitHi.MmioLimit), 40)) + MMIO_ALIGN;
    MmioRange[MmioPair].Attribute.NonPosted   = (UINT8) MmioLimitLow.NP;
    MmioRange[MmioPair].Attribute.ReadEnable = (UINT8) MmioBaseLow.RE;
    MmioRange[MmioPair].Attribute.WriteEnable = (UINT8) MmioBaseLow.WE;
    MmioRange[MmioPair].Destination.DstNode = MmioLimitLow.DstNode;
    MmioRange[MmioPair].Destination.DstLink = MmioLimitLow.DstLink;
    MmioRange[MmioPair].Destination.DstSubLink = MmioLimitLow.DstSubLink;
    MmioRange[MmioPair].RangeNum = MmioPair;
    MmioRange[MmioPair].Modified = FALSE;
    if ((MmioRange[MmioPair].Attribute.ReadEnable == 0) && (MmioRange[MmioPair].Attribute.WriteEnable == 0)) {
      UnusedMmioPair++;
    }
    IDS_HDT_CONSOLE (MAIN_FLOW, " %02d ", MmioPair);
    IDS_HDT_CONSOLE (MAIN_FLOW, "%08x%08x    %08x%08x", RShiftU64 (MmioRange[MmioPair].Base, 32) & 0xFFFFFFFF,
                                                         MmioRange[MmioPair].Base & 0xFFFFFFFF,
                                                        RShiftU64 (MmioRange[MmioPair].Limit, 32) & 0xFFFFFFFF,
                                                         MmioRange[MmioPair].Limit & 0xFFFFFFFF);
    IDS_HDT_CONSOLE (MAIN_FLOW, "    %s  %s  %s",     MmioRange[MmioPair].Attribute.NonPosted ? "Y" : "N",
                                                      MmioRange[MmioPair].Attribute.ReadEnable ? "Y" : "N",
                                                      MmioRange[MmioPair].Attribute.WriteEnable ? "Y" : "N");
    IDS_HDT_CONSOLE (MAIN_FLOW, "    %02d      %02d      %02d\n", MmioRange[MmioPair].Destination.DstNode,
                                                                  MmioRange[MmioPair].Destination.DstLink,
                                                                  MmioRange[MmioPair].Destination.DstSubLink);
  }

  // parse requirement
  NewMmioRange.Base = *BaseAddress;
  NewMmioRange.Limit = *BaseAddress + *Length;
  NewMmioRange.Attribute.ReadEnable  = Attributes->ReadEnable;
  NewMmioRange.Attribute.WriteEnable = Attributes->WriteEnable;
  NewMmioRange.Attribute.NonPosted   = Attributes->NonPosted;
  IDS_HDT_CONSOLE (MAIN_FLOW, "req %08x%08x    %08x%08x\n", RShiftU64 (NewMmioRange.Base, 32) & 0xFFFFFFFF,
                                                         NewMmioRange.Base & 0xFFFFFFFF,
                                                        RShiftU64 (NewMmioRange.Limit, 32) & 0xFFFFFFFF,
                                                         NewMmioRange.Limit & 0xFFFFFFFF);
  for (ConfMapRange = 0; ConfMapRange < CONF_MAP_NUM; ConfMapRange++) {
    PciAddress.Address.Register = (CONF_MAP_RANGE_0 + ConfMapRange * 4);
    *((UINT32 *) &ConfMapRegister) = PciRead32 (PciAddress.AddressValue);
    if ((ConfMapRegister.BusNumBase <= Target.PciBusNum) &&
        (ConfMapRegister.BusNumLimit >= Target.PciBusNum)) {
      NewMmioRange.Destination.DstNode = ConfMapRegister.DstNode;
      NewMmioRange.Destination.DstLink = ConfMapRegister.DstLink;
      NewMmioRange.Destination.DstSubLink = ConfMapRegister.DstSubLink;
      break;
    }
  }

  if (ConfMapRange == CONF_MAP_NUM) {
    // PciBusNumber doesn't belong to any node
    IDS_HDT_CONSOLE (MAIN_FLOW, " [ERROR] PciBusNumber doesn't belong to any node.\n");
    return EFI_NOT_FOUND;
  }

  // sort by base address
  //    range0, range1, range2, non used, non used...
  for (i = 0; i < (MMIO_REG_PAIR_NUM - 1); i++) {
    for (j = 0; j < (MMIO_REG_PAIR_NUM - i - 1); j++) {
      if (((MmioRange[j].Base > MmioRange[j + 1].Base) && ((MmioRange[j + 1].Attribute.ReadEnable != 0) || (MmioRange[j + 1].Attribute.WriteEnable != 0))) ||
          (((MmioRange[j].Attribute.ReadEnable == 0) && (MmioRange[j].Attribute.WriteEnable == 0)) &&
          ((MmioRange[j + 1].Attribute.ReadEnable != 0) || (MmioRange[j + 1].Attribute.WriteEnable != 0)))) {
        MmioRangeTemp = MmioRange[j];
        MmioRange[j] = MmioRange[j + 1];
        MmioRange[j + 1] = MmioRangeTemp;
      }
    }
  }

  // merge the request to current setting
  Overlap = FALSE;
  NewMmioIncluded = FALSE;
  for (MmioPair = 0; MmioPair < MMIO_REG_PAIR_NUM; MmioPair++) {
    if (MmioRange[MmioPair].Attribute.ReadEnable != 0 || MmioRange[MmioPair].Attribute.WriteEnable != 0) {
      if (((NewMmioRange.Base <= MmioRange[MmioPair].Base) && (NewMmioRange.Limit >= MmioRange[MmioPair].Base)) ||
          ((MmioRange[MmioPair].Base <= NewMmioRange.Base) && (MmioRange[MmioPair].Limit > NewMmioRange.Base))) {
        if ((NewMmioRange.Attribute.NonPosted == MmioRange[MmioPair].Attribute.NonPosted) &&
            (NewMmioRange.Attribute.ReadEnable == MmioRange[MmioPair].Attribute.ReadEnable) &&
            (NewMmioRange.Attribute.WriteEnable == MmioRange[MmioPair].Attribute.WriteEnable) &&
            (NewMmioRange.Destination.DstNode == MmioRange[MmioPair].Destination.DstNode) &&
            (NewMmioRange.Destination.DstLink == MmioRange[MmioPair].Destination.DstLink) &&
            (NewMmioRange.Destination.DstSubLink == MmioRange[MmioPair].Destination.DstSubLink)) {

//  Original sorted MMIO register pair defined ranges:
//                                          ____________            ________          ____________
//                                          |          |            |      |          |          |
//                                        base0      limit0       base1  limit1     base2      limit2
//  Requested MMIO range:
//    case 1:
//     ((NewMmioRange.Base <= MmioRange[MmioPair].Base) && (NewMmioRange.Limit >= MmioRange[MmioPair].Base))
//                                                              __________
//                                                              |        |
//                                                         new base   new limit
//                                                              ____________________
//                                                              |                  |
//                                                         new base             new limit
//    case 2:
//    ((MmioRange[MmioPair].Base <= NewMmioRange.Base) && (MmioRange[MmioPair].Limit >= NewMmioRange.Base))
//                                                                                       ____________
//                                                                                       |          |
//                                                                                   new base   new limit

          MmioRange[MmioPair].Base = (MmioRange[MmioPair].Base <= NewMmioRange.Base) ? MmioRange[MmioPair].Base : NewMmioRange.Base;
          MmioRange[MmioPair].Modified = TRUE;
          for (i = 1; NewMmioRange.Limit >= MmioRange[MmioPair + i].Base; i++) {
            if ((NewMmioRange.Attribute.NonPosted == MmioRange[MmioPair + i].Attribute.NonPosted) &&
                (NewMmioRange.Attribute.ReadEnable == MmioRange[MmioPair + i].Attribute.ReadEnable) &&
                (NewMmioRange.Attribute.WriteEnable == MmioRange[MmioPair + i].Attribute.WriteEnable) &&
                (NewMmioRange.Destination.DstNode == MmioRange[MmioPair + i].Destination.DstNode) &&
                (NewMmioRange.Destination.DstLink == MmioRange[MmioPair + i].Destination.DstLink) &&
                (NewMmioRange.Destination.DstSubLink == MmioRange[MmioPair + i].Destination.DstSubLink)) {
              MmioRange[MmioPair].Limit = MmioRange[MmioPair + i].Limit;
              MmioRange[MmioPair + i].Base = 0;
              MmioRange[MmioPair + i].Limit = MMIO_ALIGN;
              MmioRange[MmioPair + i].Attribute.ReadEnable = 0;
              MmioRange[MmioPair + i].Attribute.WriteEnable = 0;
              MmioRange[MmioPair + i].Modified = TRUE;
              UnusedMmioPair++;
            } else if (MmioRange[MmioPair + i].Attribute.ReadEnable != 0 || MmioRange[MmioPair + i].Attribute.WriteEnable != 0) {
              // Overlapped MMIO regions with different attributes
              MmioRange[MmioPair].Limit = (MmioRange[MmioPair].Limit >= NewMmioRange.Limit) ? MmioRange[MmioPair].Limit : NewMmioRange.Limit;
              NewMmioIncluded = TRUE;
              Overlap = TRUE;
              break;
            }
          }
          MmioRange[MmioPair].Limit = (MmioRange[MmioPair + i - 1].Limit >= NewMmioRange.Limit) ? MmioRange[MmioPair + i - 1].Limit : NewMmioRange.Limit;
          break;
        } else {
          // Overlapped MMIO regions with different attributes
          Overlap = TRUE;
          break;
        }
      }
    } else {

//  Original sorted MMIO register pair defined ranges:
//                                          ____________            ________          ____________
//                                          |          |            |      |          |          |
//                                        base0      limit0       base1  limit1     base2      limit2
//  Requested MMIO range:
//    case 3:
//     No overlapping area with the original ranges
//                    ____________
//                    |          |
//                new base   new limit
//                                                                                                        ______________
//                                                                                                        |            |
//                                                                                                    new base     new limit

      MmioRange[MmioPair].Base = NewMmioRange.Base;
      MmioRange[MmioPair].Limit = NewMmioRange.Limit;
      MmioRange[MmioPair].Attribute.ReadEnable = NewMmioRange.Attribute.ReadEnable;
      MmioRange[MmioPair].Attribute.WriteEnable = NewMmioRange.Attribute.WriteEnable;
      MmioRange[MmioPair].Attribute.NonPosted = NewMmioRange.Attribute.NonPosted;
      MmioRange[MmioPair].Destination = NewMmioRange.Destination;
      MmioRange[MmioPair].Modified = TRUE;

      break;
    }
  }

  if (MmioPair == MMIO_REG_PAIR_NUM) {
    IDS_HDT_CONSOLE (MAIN_FLOW, " [ERROR] Not enough MMIO register pairs to hold the request.\n");
    return EFI_OUT_OF_RESOURCES;
  }

  if (Overlap) {
    // Overlapped MMIO regions with different attributes
    IDS_HDT_CONSOLE (MAIN_FLOW, " [ERROR] Overlapped MMIO regions with different attributes.\n");
    return EFI_OUT_OF_RESOURCES;
  }
  // write back MMIO base/limit
  IDS_HDT_CONSOLE (MAIN_FLOW, "MMIO map configuration after merging:\n");
  IDS_HDT_CONSOLE (MAIN_FLOW, "    Base                 Limit               NP RE WE Lock DstNode DstLink DstSubLink\n");

  PciAddress.AddressValue = MAKE_SBDFO (0, 0, 0x18, FUNC_1, 0);
  for (MmioPair = 0; MmioPair < MMIO_REG_PAIR_NUM; MmioPair++) {
    IDS_HDT_CONSOLE (MAIN_FLOW, " %02d ", MmioPair);
    IDS_HDT_CONSOLE (MAIN_FLOW, "%08x%08x    %08x%08x", RShiftU64 (MmioRange[MmioPair].Base, 32) & 0xFFFFFFFF,
                                                         MmioRange[MmioPair].Base & 0xFFFFFFFF,
                                                        RShiftU64 (MmioRange[MmioPair].Limit, 32) & 0xFFFFFFFF,
                                                         MmioRange[MmioPair].Limit & 0xFFFFFFFF);
    IDS_HDT_CONSOLE (MAIN_FLOW, "    %s  %s  %s",     MmioRange[MmioPair].Attribute.NonPosted ? "Y" : "N",
                                                      MmioRange[MmioPair].Attribute.ReadEnable ? "Y" : "N",
                                                      MmioRange[MmioPair].Attribute.WriteEnable ? "Y" : "N");
    IDS_HDT_CONSOLE (MAIN_FLOW, "    %02d      %02d      %02d\n", MmioRange[MmioPair].Destination.DstNode,
                                                                  MmioRange[MmioPair].Destination.DstLink,
                                                                  MmioRange[MmioPair].Destination.DstSubLink);
    if (MmioRange[MmioPair].Modified) {
      // MMIO base low
      PciAddress.Address.Register = MmioBaseLowRegOffset[MmioRange[MmioPair].RangeNum];
      *((UINT32 *) &MmioBaseLow) = PciRead32 (PciAddress.AddressValue);
      if (MmioBaseLow.Lock == 1) {
        IDS_HDT_CONSOLE (MAIN_FLOW, " [ERROR] MMIO register pair locked.\n");
        return EFI_WRITE_PROTECTED;
      }
      // Disable RE/WE before changing the address range
      MmioBaseLow.RE = 0;
      MmioBaseLow.WE = 0;
      AmdS3PciWrite (AccessWidth32, PciAddress.AddressValue, &MmioBaseLow, NULL);

      IDS_HDT_CONSOLE (MAIN_FLOW, " Reconfiguring offset %X\n", MmioBaseLowRegOffset[MmioRange[MmioPair].RangeNum]);
      MmioBaseLow.MmioBase = (UINT32) RShiftU64 (MmioRange[MmioPair].Base, 16) & 0xFFFFFFul;
      MmioBaseLow.RE = MmioRange[MmioPair].Attribute.ReadEnable;
      MmioBaseLow.WE = MmioRange[MmioPair].Attribute.WriteEnable;
      AmdS3PciWrite (AccessWidth32, PciAddress.AddressValue, &MmioBaseLow, NULL);

      // MMIO limit low
      IDS_HDT_CONSOLE (MAIN_FLOW, " Reconfiguring offset %X\n", MmioLimitLowRegOffset[MmioRange[MmioPair].RangeNum]);
      PciAddress.Address.Register = MmioLimitLowRegOffset[MmioRange[MmioPair].RangeNum];
      *((UINT32 *) &MmioLimitLow) = PciRead32 (PciAddress.AddressValue);
      MmioLimitLow.MmioLimit = (UINT32) RShiftU64 ((MmioRange[MmioPair].Limit - 1), 16) & 0xFFFFFFul;
      MmioLimitLow.NP = MmioRange[MmioPair].Attribute.NonPosted;
      MmioLimitLow.DstNode = MmioRange[MmioPair].Destination.DstNode;
      MmioLimitLow.DstLink = MmioRange[MmioPair].Destination.DstLink;
      MmioLimitLow.DstSubLink = MmioRange[MmioPair].Destination.DstSubLink;
      AmdS3PciWrite (AccessWidth32, PciAddress.AddressValue, &MmioLimitLow, NULL);

      // MMIO base/limit high
      IDS_HDT_CONSOLE (MAIN_FLOW, " Reconfiguring offset %X\n", MmioBaseLimitHiRegOffset[MmioRange[MmioPair].RangeNum]);
      PciAddress.Address.Register = MmioBaseLimitHiRegOffset[MmioRange[MmioPair].RangeNum];
      *((UINT32 *) &MmioBaseLimitHi) = PciRead32 (PciAddress.AddressValue);
      MmioBaseLimitHi.MmioBase = (UINT32) RShiftU64 (MmioRange[MmioPair].Base, 40) & 0xFFul;
      MmioBaseLimitHi.MmioLimit = (UINT32) RShiftU64 ((MmioRange[MmioPair].Limit - 1), 40) & 0xFFul;
      AmdS3PciWrite (AccessWidth32, PciAddress.AddressValue, &MmioBaseLimitHi, NULL);
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
FabricAllocateIo (
  IN OUT   UINT32 *BaseAddress,
  IN OUT   UINT32 *Length,
  IN       FABRIC_TARGET          Target
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
FabricGetAvailableResource (
  IN       FABRIC_RESOURCE_FOR_EACH_RB    *ResourceForEachRb
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
FabricReallocateResourceForEachRb (
  IN       FABRIC_RESOURCE_FOR_EACH_RB    *ResourceSizeForEachRb,
  IN       FABRIC_ADDR_SPACE_SIZE          *SpaceStatus
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
FabricResourceRestoreDefault (
  )
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
FabricEnableVgaMmio (
  IN       FABRIC_TARGET          Target
  )
{
  return EFI_UNSUPPORTED;
}


