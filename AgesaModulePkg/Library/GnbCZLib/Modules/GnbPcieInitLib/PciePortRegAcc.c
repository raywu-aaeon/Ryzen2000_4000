/* $NoKeywords:$ */
/**
 * @file
 *
 * Supporting services to access PCIe port indirect register
 * space.
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
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "PciePortRegAcc.h"
#include  "GnbCommonLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIEINITLIB_PCIEPORTREGACC_FILECODE
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
 * Read PCIe port indirect register.
 *
 * Support for unify register access through index/data pair on PCIe port
 *
 * @param[in]  Engine      Pointer to Engine descriptor for this port
 * @param[in]  Address     Register address
 * @param[in]  Pcie        Pointer to internal configuration data area
 * @retval                 Register Value
 */

UINT32
PciePortRegisterRead (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      UINT32                Address,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32  Value;
  GnbLibPciWrite (Engine->Type.Port.Address.AddressValue | 0xE0, AccessWidth32, &Address, GnbLibGetHeader (Pcie));
  GnbLibPciRead (Engine->Type.Port.Address.AddressValue | 0xE4, AccessWidth32, &Value, GnbLibGetHeader (Pcie));
  return Value;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Write PCIe Port Indirect register.
 *
 * Support for unify register access through index/data pair on GNB
 *
 * @param[in]  Engine      Pointer to Engine descriptor for this port
 * @param[in]  Address     Register address
 * @param[in]  Value       New register value
 * @param[in]  S3Save      Save for S3 flag
 * @param[in]  Pcie        Pointer to internal configuration data area
 */
VOID
PciePortRegisterWrite (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      UINT32                Address,
  IN      UINT32                Value,
  IN      BOOLEAN               S3Save,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  ASSERT (S3Save == TRUE || S3Save == FALSE);

  IDS_HDT_CONSOLE (PCIE_PORTREG_TRACE, "    *WR PCIEIND_P (%d:%d:%d):0x%04x = 0x%08x\n",
    Engine->Type.Port.Address.Address.Bus,
    Engine->Type.Port.Address.Address.Device,
    Engine->Type.Port.Address.Address.Function,
    Address,
    Value
    );
  GnbLibPciWrite (Engine->Type.Port.Address.AddressValue | 0xE0, S3Save ? AccessS3SaveWidth32 : AccessWidth32, &Address, GnbLibGetHeader (Pcie));
  GnbLibPciWrite (Engine->Type.Port.Address.AddressValue | 0xE4, S3Save ? AccessS3SaveWidth32 : AccessWidth32, &Value, GnbLibGetHeader (Pcie));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Write PCIe Port Indirect register field.
 *
 * Support for unify register access through index/data pair on GNB
 *
 * @param[in]  Engine      Pointer to Engine descriptor for this port
 * @param[in]  Address     Register address
 * @param[in]  FieldOffset Field offset
 * @param[in]  FieldWidth  Field width
 * @param[in]  S3Save      Save for S3 flag
 * @param[in]  Value       New register value
 * @param[in]  Pcie        Pointer to internal configuration data area
 */

VOID
PciePortRegisterWriteField (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      UINT32                Address,
  IN      UINT8                 FieldOffset,
  IN      UINT8                 FieldWidth,
  IN      UINT32                Value,
  IN      BOOLEAN               S3Save,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32  Data;
  UINT32  Mask;
  Data = PciePortRegisterRead (Engine, Address, Pcie);
  Mask = (1 << FieldWidth) - 1;
  Value &= Mask;
  Data &= (~(Mask << FieldOffset));
  PciePortRegisterWrite (Engine, Address, Data | (Value << FieldOffset), S3Save, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Write PCIe Port Indirect register field.
 *
 * Support for unify register access through index/data pair on GNB
 *
 * @param[in]  Engine      Pointer to Engine descriptor for this port
 * @param[in]  Address     Register address
 * @param[in]  FieldOffset Field offset
 * @param[in]  FieldWidth  Field width
 * @param[in]  Pcie        Pointer to internal configuration data area
 * @retval                 Register Field Value.
 */

UINT32
PciePortRegisterReadField (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      UINT32                Address,
  IN      UINT8                 FieldOffset,
  IN      UINT8                 FieldWidth,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32  Value;
  Value = PciePortRegisterRead (Engine, Address, Pcie);
  Value = (Value >> FieldOffset) & ((1 << FieldWidth) - 1);
  return  Value;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Read/Modify/Write PCIe port register.
 *
 * Support for unify register access through index/data pair on GNB
 *
 * @param[in]  Engine      Pointer to Engine descriptor for this port
 * @param[in]  Address     Register address
 * @param[in]  AndMask     Value & (~AndMask)
 * @param[in]  OrMask      Value | OrMask
 * @param[in]  S3Save      Save register for S3 (True/False)
 * @param[in]  Pcie        Pointer to global PCIe configuration
 */

VOID
PciePortRegisterRMW (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      UINT32                Address,
  IN      UINT32                AndMask,
  IN      UINT32                OrMask,
  IN      BOOLEAN               S3Save,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32  Value;
  Value = PciePortRegisterRead (Engine, Address, Pcie);
  Value = (Value & (~AndMask)) | OrMask;
  PciePortRegisterWrite (Engine, Address, Value, S3Save, Pcie);
}


