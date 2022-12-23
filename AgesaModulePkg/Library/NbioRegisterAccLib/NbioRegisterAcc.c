/* $NoKeywords:$ */
/**
 * @file
 *
 * NBIO Register Access Methods.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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
#include  <Library/BaseLib.h>
#include  <AGESA.h>
#include  "Gnb.h"
#include  "NbioRegisterTypes.h"
#include  <Library/AmdBaseLib.h>
#include  <Library/IdsLib.h>
#include  <Library/GnbPcieConfigLib.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/NbioRegisterAccLib.h>
#include  <Library/NbioHandleLib.h>
#include  <Filecode.h>
#define FILECODE LIBRARY_NBIOREGISTERACCLIB_NBIOREGISTERACC_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#undef GNB_TRACE_ENABLE
#define GNB_IGNORED_PARAM             0xFF
#define ORB_WRITE_ENABLE              0//0x100
#define IOMMU_L1_WRITE_ENABLE         0x80000000ul
#define IOMMU_L2_WRITE_ENABLE         0x100


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
NbioRegisterWriteDump (
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
  IN       UINT32              Value
  );


/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to read all register spaces.
 *
 *
 *
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset, but PortDevice
 * @param[out] Value             Return value
 * @param[in] Flags              Flags - BIT0 indicates S3 save/restore
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
NbioRegisterRead (
  IN       GNB_HANDLE          *GnbHandle,
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
     OUT   VOID                *Value,
  IN       UINT32              Flags
  )
{
  ACCESS_WIDTH  Width;
  PCI_ADDR      GnbPciAddress;
//  UINT64        GmmBase;

  GnbPciAddress = NbioGetHostPciAddress (GnbHandle);
  Width = (Flags == GNB_REG_ACC_FLAG_S3SAVE) ? AccessS3SaveWidth32 : AccessWidth32;

  GNB_DEBUG_CODE (
  IDS_HDT_CONSOLE (NB_MISC, "  R READ Space 0x%x  Address 0x%04x\n",
      RegisterSpaceType,
      Address
    );
  );

  switch (RegisterSpaceType) {
  case TYPE_D0F0:
    GnbLibPciRead (
      GnbPciAddress.AddressValue | Address,
      Width,
      Value,
      NULL
    );
    break;

  case TYPE_SMN:
    {
      UINT64  TempData;
      GnbLibPciIndirectRead (
        GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
        (Address & (~0x3ull)),
        Width,
        &TempData,
        NULL
      );
      if ((Address & 0x3) != 0) {
        //Non aligned access allowed to fuse block
        GnbLibPciIndirectRead (
          GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
          (Address & (~0x3ull)) + 4,
          Width,
          ((UINT32 *) &TempData) + 1,
          NULL
        );
      }
      *((UINT32*) Value) = (UINT32) RShiftU64 (TempData, ((Address & 0x3) * 8));
      break;
    }

  default:
    ASSERT (FALSE);
    break;
  }
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write all register spaces.
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset, but PortDevice
 * @param[out] Value             The value to write
 * @param[in] Flags              Flags - BIT0 indicates S3 save/restore
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
NbioRegisterWrite (
  IN       GNB_HANDLE          *GnbHandle,
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
  IN       VOID                *Value,
  IN       UINT32              Flags
  )
{

  ACCESS_WIDTH    Width;
  PCI_ADDR        GnbPciAddress;
//  UINT64          GmmBase;

  GnbPciAddress = NbioGetHostPciAddress (GnbHandle);
  Width = (Flags == GNB_REG_ACC_FLAG_S3SAVE) ? AccessS3SaveWidth32 : AccessWidth32;

  GNB_DEBUG_CODE (
    NbioRegisterWriteDump (RegisterSpaceType, Address, *((UINT32*)Value));
  );

  switch (RegisterSpaceType) {
  case TYPE_D0F0:
    GnbLibPciWrite (
      GnbPciAddress.AddressValue | Address,
      Width,
      Value,
      NULL
    );
    break;

  case TYPE_SMN:
    //SMU, access D0F0xBC_x[FFFFFFFF:00000000]
    GnbLibPciIndirectWrite (
      GnbPciAddress.AddressValue | D0F0xB8_ADDRESS,
      Address,
      Width,
      Value,
      NULL
    );
    break;

  default:
    ASSERT (FALSE);
    break;
  }

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to Read/Modify/Write all register spaces.
 *
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset, but PortDevice
 * @param[in] Mask               And Mask
 * @param[in] Value              Or value
 * @param[in] Flags              Flags - BIT0 indicates S3 save/restore
 * @retval    VOID
 */
VOID
NbioRegisterRMW (
  IN       GNB_HANDLE          *GnbHandle,
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
  IN       UINT32              Mask,
  IN       UINT32              Value,
  IN       UINT32              Flags
  )
{
  UINT32  Data;
  NbioRegisterRead (GnbHandle, RegisterSpaceType, Address, &Data, Flags);
  Data = (Data & Mask) | Value;
  NbioRegisterWrite (GnbHandle, RegisterSpaceType, Address, &Data, Flags);
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to dump all write register spaces.
 *
 *
 *
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset
 * @param[in] Value              The value to write
 */
VOID
NbioRegisterWriteDump (
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
  IN       UINT32              Value
  )
{
  IDS_HDT_CONSOLE (NB_MISC, "  R WRITE Space %a  Address 0x%04x, Value 0x%04x\n",
    (RegisterSpaceType == TYPE_D0F0) ? "TYPE_D0F0" : (
    (RegisterSpaceType == TYPE_SMN) ? "TYPE_SMN" : (
    (RegisterSpaceType == TYPE_D0F0xBC) ? "TYPE_D0F0xBC" : "Invalid")),
    Address,
    Value
  );
}



