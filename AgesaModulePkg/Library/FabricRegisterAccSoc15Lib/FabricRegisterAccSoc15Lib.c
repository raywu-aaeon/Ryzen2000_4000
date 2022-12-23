/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Register Access Methods.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: Fabric
 * @e \$Revision$   @e \$Date$
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
#include <AGESA.h>
#include <Ids.h>
#include <Library/AmdBaseLib.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/PciLib.h>
#include <Library/AmdS3SaveLib.h>
#include "FabricRegisterAccSoc15Lib.h"
#include <Filecode.h>

#define FILECODE LIBRARY_FABRICREGISTERACCSOC15LIB_FABRICREGISTERACCSOC15LIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT32
FabricRegisterAccGetPciDeviceNumberOfDie (
  IN       UINTN Socket,
  IN       UINTN Die
  );

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to read a register.
 *
 * @param[in] Socket             Processor socket to read from
 * @param[in] Die                Die number on Socket to read from
 * @param[in] Function           Function number to read from
 * @param[in] Offset             Register to read
 * @param[in] Instance           Instance ID of the target fabric device
 * @retval    Current value of the target register
 */
UINT32
FabricRegisterAccRead (
  IN       UINTN  Socket,
  IN       UINTN  Die,
  IN       UINTN  Function,
  IN       UINTN  Offset,
  IN       UINTN  Instance
  )
{
  UINT32                               RegisterValue;
  PCI_ADDR                             PciAddr;
  FABRIC_IND_CFG_ACCESS_ADDR_REGISTER  FICAA3;

  ASSERT (Socket < 2);
  ASSERT (Die < 4);
  ASSERT (Function < 8);
  ASSERT (Offset < 0x400);
  ASSERT ((Offset & 3) == 0);
  ASSERT (Instance <= FABRIC_REG_ACC_BC);

  PciAddr.AddressValue = 0;
  PciAddr.Address.Device = FabricRegisterAccGetPciDeviceNumberOfDie (Socket, Die);
  if (Instance == FABRIC_REG_ACC_BC) {
    PciAddr.Address.Function = (UINT32) Function;
    PciAddr.Address.Register = (UINT32) Offset;
    RegisterValue = PciRead32 (PciAddr.AddressValue);
  } else {
    PciAddr.Address.Function = FICAA3_FUNC;
    PciAddr.Address.Register = FICAA3_REG;
    FICAA3.Value = 0;
    FICAA3.Field.CfgRegInstAccEn = 1;
    FICAA3.Field.IndCfgAccRegNum = ((UINT32) Offset) >> 2;
    FICAA3.Field.IndCfgAccFuncNum = (UINT32) Function;
    FICAA3.Field.CfgRegInstID = (UINT32) Instance;
    PciWrite32 (PciAddr.AddressValue, FICAA3.Value);

    PciAddr.Address.Function = FICAD3_LO_FUNC;
    PciAddr.Address.Register = FICAD3_LO_REG;
    RegisterValue = PciRead32 (PciAddr.AddressValue);
  }
  return RegisterValue;
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write a register.
 *
 * @param[in] Socket             Processor socket to read from
 * @param[in] Die                Die number on Socket to read from
 * @param[in] Function           Function number to read from
 * @param[in] Offset             Register to read
 * @param[in] Instance           Instance ID of the target fabric device
 * @param[in] Value              Value to write
 * @param[in] LogForS3           Whether or not this write should be logged for playback on S3
 */
VOID
FabricRegisterAccWrite (
  IN       UINTN    Socket,
  IN       UINTN    Die,
  IN       UINTN    Function,
  IN       UINTN    Offset,
  IN       UINTN    Instance,
  IN       UINT32   Value,
  IN       BOOLEAN  LogForS3
  )
{
  UINT32                               RegisterValue;
  PCI_ADDR                             PciAddr;
  FABRIC_IND_CFG_ACCESS_ADDR_REGISTER  FICAA3;

  ASSERT (Socket < 2);
  ASSERT (Die < 4);
  ASSERT (Function < 8);
  ASSERT (Offset < 0x400);
  ASSERT ((Offset & 3) == 0);
  ASSERT (Instance <= FABRIC_REG_ACC_BC);

  RegisterValue = Value;
  PciAddr.AddressValue = 0;
  PciAddr.Address.Device = FabricRegisterAccGetPciDeviceNumberOfDie (Socket, Die);
  if (Instance == FABRIC_REG_ACC_BC) {
    PciAddr.Address.Function = (UINT32) Function;
    PciAddr.Address.Register = (UINT32) Offset;
    PciWrite32 (PciAddr.AddressValue, RegisterValue);
    if (LogForS3) {
      AmdS3SaveScriptPciWrite (AccessWidth32, PciAddr.AddressValue, &RegisterValue);
    }
  } else {
    PciAddr.Address.Function = FICAA3_FUNC;
    PciAddr.Address.Register = FICAA3_REG;
    FICAA3.Value = 0;
    FICAA3.Field.CfgRegInstAccEn = 1;
    FICAA3.Field.IndCfgAccRegNum = ((UINT32) Offset) >> 2;
    FICAA3.Field.IndCfgAccFuncNum = (UINT32) Function;
    FICAA3.Field.CfgRegInstID = (UINT32) Instance;
    PciWrite32 (PciAddr.AddressValue, FICAA3.Value);
    if (LogForS3) {
      AmdS3SaveScriptPciWrite (AccessWidth32, PciAddr.AddressValue, &FICAA3.Value);
    }

    PciAddr.Address.Function = FICAD3_LO_FUNC;
    PciAddr.Address.Register = FICAD3_LO_REG;
    PciWrite32 (PciAddr.AddressValue, RegisterValue);
    if (LogForS3) {
      AmdS3SaveScriptPciWrite (AccessWidth32, PciAddr.AddressValue, &RegisterValue);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write a register.
 *
 * @param[in] Socket             Processor socket to read from
 * @param[in] Die                Die number on Socket to read from
 * @param[in] Function           Function number to read from
 * @param[in] Offset             Register to read
 * @param[in] Instance           Instance ID of the target fabric device
 * @param[in] NandValue          Value to NAND with the current register value
 * @param[in] OrValue            Value to OR with the current register value
 * @param[in] LogForS3           Whether or not this write should be logged for playback on S3
 * @retval    Value written to target register if interested
 */
UINT32
FabricRegisterAccRMW (
  IN       UINTN    Socket,
  IN       UINTN    Die,
  IN       UINTN    Function,
  IN       UINTN    Offset,
  IN       UINTN    Instance,
  IN       UINT32   NandValue,
  IN       UINT32   OrValue,
  IN       BOOLEAN  LogForS3
  )
{
  UINT32  RegisterValue;

  ASSERT (Socket < 2);
  ASSERT (Die < 4);
  ASSERT (Function < 8);
  ASSERT (Offset < 0x400);
  ASSERT ((Offset & 3) == 0);
  ASSERT (Instance <= FABRIC_REG_ACC_BC);

  RegisterValue = (FabricRegisterAccRead (Socket, Die, Function, Offset, Instance) & ~NandValue) | OrValue;
  FabricRegisterAccWrite (Socket, Die, Function, Offset, Instance, RegisterValue, LogForS3);
  return RegisterValue;
}

UINT32
FabricRegisterAccGetPciDeviceNumberOfDie (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  return (UINT32) (((((UINT32) Socket) << 2) | (UINT32) Die) + 0x18);
}


