/* $NoKeywords:$ */
/**
 * @file
 *
 * NBIO Common Library. This library is a home for common functions and routines
 * meant to reduce code size and encourage code sharing.
 *
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
#include  <Library/NbioUtilLib.h>
#include  <Library/SmnAccessLib.h>
#include  <Library/FabricResourceManagerLib.h>
#include  <Library/BaseLib.h>
#include  <Protocol/FabricResourceManagerServicesProtocol.h>

#include  "Filecode.h"
#define FILECODE LIBRARY_NBIOUTILLIB_NBIOUTILLIB_FILECODE
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
 * This function assigns MMIO for a non-pci device.
 *
 *
 * @param[in]  GnbHandle       Silicon handle to assign
 * @param[in]  MmioBarLow      Address of low byte
 * @param[in]  MmioBarHigh     Address of high byte
 * @param[in]  MemorySize      Size of the allocated bar required
 * @param[in]  Enable          Set enable bit in BAR
 * @param[in]  LockSettings    If the allocated memory range should be locked or not
 * @param[in]  Above4G         If MMIO above the 4G boundary should be allocated
 */
VOID
NonPCIBarInit (
  IN       GNB_HANDLE   *GnbHandle,
  IN       UINT32       MmioBarLow,
  IN       UINT32       MmioBarHigh,
  IN       UINT32       MemorySize,
  IN       BOOLEAN      Enable,
  IN       BOOLEAN      LockSettings,
  IN       BOOLEAN      Above4G
  )
{
  EFI_STATUS             Status;
  FABRIC_TARGET          MmioTarget;
  FABRIC_MMIO_ATTRIBUTE  Attributes;
  UINT64                 MmioBase, Length;
  UINT32                 BarLow, BarHigh;

  BarLow = 0;
  BarHigh = 0;
  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Begin to allocate bars for SMN low %x high %x, size %x\n", __FUNCTION__, MmioBarLow, MmioBarHigh, MemorySize);

  ///
  /// See if the given BAR have already been assigned
  ///
  SmnRegisterRead (GnbHandle->Address.Address.Bus, MmioBarHigh, &BarHigh);
  SmnRegisterRead (GnbHandle->Address.Address.Bus, MmioBarLow, &BarLow);

  if (BarLow == 0 && BarHigh == 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Bars have not been assigned, attempting to allocate MMIO \n", __FUNCTION__);
    ///
    /// Assign bars:
    /// Allocate a chunk of MMIO first
    ///
    Length = MemorySize;
    MmioTarget.TgtType = TARGET_PCI_BUS;
    MmioTarget.SocketNum = GnbHandle->SocketId;
    MmioTarget.PciBusNum = (UINT16) GnbHandle->Address.Address.Bus;
    Attributes.ReadEnable = 1;
    Attributes.WriteEnable = 1;
    Attributes.NonPosted = 0;
    MmioBase = 0;
    if (Above4G) {
      Attributes.MmioType = NON_PCI_DEVICE_ABOVE_4G;
    }
    else {
      Attributes.MmioType = NON_PCI_DEVICE_BELOW_4G;
    }

    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : FabricAllocateMmio : Socket %d , RB # %d\n", __FUNCTION__, MmioTarget.SocketNum, MmioTarget.RbNum);
    Status = FabricAllocateMmio (&MmioBase, &Length, ALIGN_1M, MmioTarget, &Attributes);
    ASSERT (Status == EFI_SUCCESS );
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Allocate MMIO Fail\n", __FUNCTION__);
      return;
    } else {
      IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Allocate MMIO @0x%lx\n", __FUNCTION__, MmioBase);
    }
  }
  else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Bars have already been assigned!\n", __FUNCTION__);
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : End\n", __FUNCTION__);
    return;
  }

  ///
  /// Write the assigned memory address registers to SMN
  ///
  BarHigh = (UINT32) RShiftU64 (MmioBase, 32);

  if (Enable) {
    BarLow = (UINT32)(MmioBase | BIT0); /// Set enable bit
  }

  if (LockSettings) {
    BarLow = (UINT32)(MmioBase | BIT1); /// Set lock bit
  }


  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : BarLow = %x , BarHigh %x\n", __FUNCTION__, BarLow, BarHigh);

  SmnRegisterWrite (GnbHandle->Address.Address.Bus, MmioBarHigh, &BarHigh, 0);
  SmnRegisterWrite (GnbHandle->Address.Address.Bus, MmioBarLow, &BarLow, 0);

  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : End\n", __FUNCTION__);
  return;
}


