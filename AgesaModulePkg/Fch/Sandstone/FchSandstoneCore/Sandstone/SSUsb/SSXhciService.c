/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch Xhci controller
 *
 * Init Xhci Controller features (PEI phase).
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
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
*/
#include "FchPlatform.h"
#include "Filecode.h"
#include "GnbDxio.h"
#include <Library/NbioSmuV10Lib.h>

#define FILECODE FCH_SANDSTONE_FCHSANDSTONECORE_SANDSTONE_SSUSB_SSXHCISERVICE_FILECODE

#define MAX_RETRY_NUM   1500

/**
 * FchRVXhciProgramInternalRegStepOne - Program USB internal
 * registers Step One
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciProgramInternalRegStepOne (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

}

/**
 * FchRVXhciProgramInternalRegStepTwo - Program USB internal
 * registers Step Two
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciProgramInternalRegStepTwo (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

// 11. USB 3.0 PHY data sheet recommends to use fixed rx_eq value (x1 or x2 or x3 or x4) so we need to program the per port override register inside PHY.  Note bit[11:8] is set to 0xA (rx_eq = 0x2) as default for routing USB30 ports to a connector and different values may be added for connecting an on-board device.
//  Program USB3 PHY0 PHY INTERNAL LANE REGISTER (address = 0x16F0_4018) to 0x0000_0AC0.
  if (Controller == 1) {
    FchSmnRW (0, FCH_SS_USB30_PHY0_INTERNAL_LANE, 0x00, 0x00000AC0, LocalCfgPtr->StdHeader);
  }
}


/**
 * FchRVXhciProgramInternalRegStepThree - Program USB internal
 * registers Step Three
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciProgramInternalRegStepThree (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

// 13, Program USB IP internal registers:
//        Program GUCTL1 (address=0x16C0C11C/0x16E0C11C) to 0x6010_6008 (from 0x2010_0008; bit[30] and bit[14:13] to be changed from 0 to 1).
//        Program GDMAHLRATIO (address=0x16C0C624/0x16E0C624) to 0x1F1F_0101 (from 0x1F1F_1F1F).
  FchSmnRW (0, (FCH_SS_USB_GUCTL1 + Controller * 0x200000), 0x00, 0x60106008, LocalCfgPtr->StdHeader);
  FchSmnRW (0, (FCH_SS_USB_GDMAHLRATIO + Controller * 0x200000), 0x00, 0x1F1F0101, LocalCfgPtr->StdHeader);
//14, Program USB IP internal registers (pending characterization results):
//        The registers are per-port registers.  Only the ones for port 0 and port 3 may need to be programmed after silicon characterizations as port 0 and port 3 are connected to an internal RFMUX that does not have a flat frequency response.  The silicon characterization will determine whether any of the registers needs to be programmed and what values need to be programmed.  Leave all the registers at defaults for now.
//        Program port0 and port 3 LCSR_TX_DEEMPHY_1 (address=0x16C0D064/0x16C0D1E4) for CP13.

//        Program port0 and port 3 LCSR_TX_DEEMPHY_2 (address=0x16C0D068/0x16C0D1E8) for CP14.

//        Program port0 and port 3 LCSR_TX_DEEMPHY_3 (address=0x16C0D06C/0x16C0D1EC) for CP16.

//        Program port0 and port 3 LLINKDBGCNTTRIG (address=0x16C0D05C/0x16C0D1DC) for CP7 and CP15.

}

/**
 * FchRVXhciPlatformPortDisable - Platform/Customer Based Host
 * configuration
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciPlatformPortDisable (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  //
  // Platform option
  //

}

/**
 * FchRVXhciPlatformOverCurrentMap - Platform/Customer Based
 * Host configuration
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciPlatformOverCurrentMap (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

}

/**
 * FchRVXhciPlatformConfiguration - Platform/Customer Based Host
 * configuration
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciPlatformConfiguration (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  FchRVXhciPlatformPortDisable (Controller, FchDataPtr);

  FchRVXhciPlatformOverCurrentMap (Controller, FchDataPtr);
}

/**
 * FchRVXhciInitBootProgram - Config Xhci controller during
 * Power-On
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciInitBootProgram (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  //1, Wait until USB rsmu_hard_resetb is cleared by SMU FW
  //FCH_DEADLOOP();
  //2, Program USB SMU assist Power State Control register, SMU_FW_assist_D_state bit (0x16D8_001C[8]/0x16F8_001C[8]) to 1 to select USB SMU assist Power State Control register for controller power management.
  FchSmnRW (0, (FCH_SS_USB_SMU_ASSIST_POWER_STS_CNTL + Controller * 0x200000), ~ (UINT32) BIT8, BIT8, LocalCfgPtr->StdHeader);
  //3, Program USB USB31 PHY PHY 0/Lane 0~3 registers, rx_los_threshold bits (0x16D6_C014[10:8]/0x16D6_C414[10:8]/0x16D6_C814[10:8]/0x16D6_CC14[10:8]) to 3'h3 from the default 3'h0.
  if (Controller == 0) {
    FchSmnRW (0, FCH_SS_USB31_PHY0_LANEPARACTL5, ~ (UINT32) (0x7 << 8), (UINT32) (0x3 << 8), LocalCfgPtr->StdHeader);
    FchSmnRW (0, FCH_SS_USB31_PHY1_LANEPARACTL5, ~ (UINT32) (0x7 << 8), (UINT32) (0x3 << 8), LocalCfgPtr->StdHeader);
    FchSmnRW (0, FCH_SS_USB31_PHY2_LANEPARACTL5, ~ (UINT32) (0x7 << 8), (UINT32) (0x3 << 8), LocalCfgPtr->StdHeader);
    FchSmnRW (0, FCH_SS_USB31_PHY3_LANEPARACTL5, ~ (UINT32) (0x7 << 8), (UINT32) (0x3 << 8), LocalCfgPtr->StdHeader);
  }
  //4.  Program USB_S5_RESET = 1
  FchSmnRW (0, (FCH_SS_USB_RESET + Controller * 0x200000), ~ ((UINT32) FCH_SS_USB_S5_RESET), FCH_SS_USB_S5_RESET, LocalCfgPtr->StdHeader);
  //    Program USB_SOFT_CONTROLLER_RESET = 1, USB_SOFT_PHY_RESET = 1
  FchSmnRW (0, (FCH_SS_USB_RESET + Controller * 0x200000), ~ ((UINT32) (FCH_SS_USB_CONTROLLER_RESET + FCH_SS_USB_PHY_RESET)), (FCH_SS_USB_CONTROLLER_RESET + FCH_SS_USB_PHY_RESET), LocalCfgPtr->StdHeader);
  //5.  Wait for 300us
  FchStall (300, LocalCfgPtr->StdHeader);
// 6.   Platform/Customer based host configuration: If there's needed to program USB container register to change USB features or mode, do in this step. Following are some examples:
// a.   To change USB port numbers, program Port Control (0x16D8_0130), and Port Disable Write Once (0x16D8_0128) and/or Port Disable Read Write (0x16D8_012C)
// b.   To program over current mapping, program Overcurrent Map register (0x16D8_0120 or 0x16D8_0120)
// c.   To enable SMI/NMI (0x16D8_0118)
  FchRVXhciPlatformConfiguration (Controller, FchDataPtr);
  //7.  Program internal registers
  FchRVXhciProgramInternalRegStepOne (Controller, FchDataPtr);
  //8.  Program USB_S5_RESET = 0
  FchSmnRW (0, (FCH_SS_USB_RESET + Controller * 0x200000), ~ ((UINT32) FCH_SS_USB_S5_RESET), 0, LocalCfgPtr->StdHeader);
  //9.  Program USB_SOFT_PHY_RESET = 0
  FchSmnRW (0, (FCH_SS_USB_RESET + Controller * 0x200000), ~ ((UINT32) (FCH_SS_USB_PHY_RESET)), 0, LocalCfgPtr->StdHeader);
  //10.  Wait at least 200us
  FchStall (200, LocalCfgPtr->StdHeader);
  //11. USB 3.0 PHY data sheet recommends to use fixed rx_eq value (x1 or x2 or x3 or x4) so we need to program the per port override register inside PHY.  Note bit[11:8] is set to 0xA (rx_eq = 0x2) as default for routing USB30 ports to a connector and different values may be added for connecting an on-board device.
  //Program USB3 PHY0 PHY INTERNAL LANE REGISTER (address = 0x16F0_4018) to 0x0000_0AC0.
  FchRVXhciProgramInternalRegStepTwo (Controller, FchDataPtr);
  //12. Program USB_SOFT_CONTROLLER_RESET = 0
  FchSmnRW (0, (FCH_SS_USB_RESET + Controller * 0x200000), ~ ((UINT32) (FCH_SS_USB_CONTROLLER_RESET)), 0, LocalCfgPtr->StdHeader);
  //13/14. Program internal registers
  FchRVXhciProgramInternalRegStepThree (Controller, FchDataPtr);
}

VOID
FchRVXhci0InitBootProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitBootProgram (0, FchDataPtr);
}

VOID
FchRVXhci1InitBootProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitBootProgram (1, FchDataPtr);
}
/**
 * FchRVXhciInitS3ExitProgram - Config Xhci controller during S3
 * Exit
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciInitS3ExitProgram (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  //UINT32                      Retry;
  //UINT32                      Pgfsm_RegData;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  // Program Host Power and Clock Control register, RO_PCMLRX_REG_CTRL[0] bit (0x0018_010C[6]) to 1'b0 to switch PHY ref_clk source to USB ref_clk from CGPLL.
  FchSmnRW (0, (FCH_SS_USB_POWER_CLK_CONTROL + Controller * 0x200000), ~(UINT32)BIT6, 0x00, LocalCfgPtr->StdHeader);

  //PLAT-22948
  // To restores PGFSM state which is lost by not being in S5 power
  //a.  program USB PGFSM to 'Power Down'
  //b.  Poll USB PGFSM Status to wait for 'Power is Off'
  //FchSmnRW (0, (FCH_SS_USB_RSMU_PGFSM_CNTL + Controller * 0x80), 0x00, PGFSM_SELECT_0 + PGFSM_CMD_POWER_DOWN + PGFSM_SOFTWARE_CONTROL, LocalCfgPtr->StdHeader);
  //for (Retry = 0; Retry < MAX_RETRY_NUM; Retry++) {
  //  FchSmnRW (0, (FCH_SS_USB_RSMU_PGFSM_CNTL + Controller * 0x80), 0x00, PGFSM_SELECT_0 + PGFSM_CMD_POWER_READ + PGFSM_SOFTWARE_CONTROL, LocalCfgPtr->StdHeader);  // read Status register 0x00
  //  FchSmnRead (0, (FCH_SS_USB_RSMU_PGFSM_RD_DATA + Controller * 0x80), &Pgfsm_RegData, LocalCfgPtr->StdHeader);
  //  if ((Pgfsm_RegData & PGFSM_STATUS_PWR_STS) == PGFSM_STATUS_PWR_OFF) {
  //    break;
  //  }
  //  FchStall (1, LocalCfgPtr->StdHeader);
  //}
  //ASSERT (Retry < MAX_RETRY_NUM);
  // Disables PGFSM Override Register in USB Container Registers by programming the values as below:
  //    PGFSM_OVERRIDE_COLDRESETB       = 1'b1
  //    PGFSM_OVERRIDE_HARDRESETB       = 1'b1
  //    PGFSM_OVERRIDE_DS               = 1'b0
  //    PGFSM_OVERRIDE_SD               = 1'b0
  //    PGFSM_OVERRIDE_ISOB             = 1'b1
  //    PGFSM_OVERRIDE_SCAN_ISOB        = 1'b1
  //    PGFSM_OVERRIDE_MOTHER_SLEEP     = 1'b0
  //    PGFSM_OVERRIDE_DAUGHTER_SLEEP   = 1'b0
  //FchSmnRW (0, (FCH_SS_USB_PGFSM_OVERRIDE + Controller * 0x200000), 0x00, 0x33, LocalCfgPtr->StdHeader);

  // to inform SMU of S3 exit

}

/**
 * FchRVXhciInitPgfsm - Config Xhci controller PGFSM during init
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciInitPgfsm (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  // Disables PGFSM Override Register in USB Container Registers by programming the values as below:
  //    PGFSM_OVERRIDE_COLDRESETB       = 1'b1
  //    PGFSM_OVERRIDE_HARDRESETB       = 1'b1
  //    PGFSM_OVERRIDE_DS               = 1'b0
  //    PGFSM_OVERRIDE_SD               = 1'b0
  //    PGFSM_OVERRIDE_ISOB             = 1'b1
  //    PGFSM_OVERRIDE_SCAN_ISOB        = 1'b1
  //    PGFSM_OVERRIDE_MOTHER_SLEEP     = 1'b0
  //    PGFSM_OVERRIDE_DAUGHTER_SLEEP   = 1'b0
  FchSmnRW (0, (FCH_SS_USB_PGFSM_OVERRIDE + Controller * 0x200000), 0x00, 0x33, LocalCfgPtr->StdHeader);

  // Program Host Power and Clock Control register, RO_PCMLRX_REG_CTRL[0] bit (0x0018_010C[6]) to 1'b0 to switch PHY ref_clk source to USB ref_clk from CGPLL.
  FchSmnRW (0, (FCH_SS_USB_POWER_CLK_CONTROL + Controller * 0x200000), ~(UINT32)BIT6, 0x00, LocalCfgPtr->StdHeader);

}

VOID
FchRVXhci0InitS3ExitProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitS3ExitProgram (0, FchDataPtr);
}

VOID
FchRVXhci1InitS3ExitProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitS3ExitProgram (1, FchDataPtr);
}

/**
 * FchRVXhciInitS3EntryProgram - Config Xhci controller before
 * entering S3
 *
 *
 * @param[in] Controller XHCI controller number.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchRVXhciInitS3EntryProgram (
  IN  UINT8    Controller,
  IN  VOID     *FchDataPtr
  )
{
  UINT32                      Retry;
  UINT32                      CurrentPowerState;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  //  2.	Read USB Current Power State register, Current_power_state bits (0x16D8_0108[9:8]/0x16F8_0108[9:8]) and wait until the read value is 2'b11 (D3 state).  The step may take up to 150ms.
  for (Retry = 0; Retry < MAX_RETRY_NUM; Retry++) {
    FchSmnRead (0, FCH_SS_USB_CURRENT_PWR_STS + Controller * 0x200000, &CurrentPowerState, LocalCfgPtr->StdHeader);
    if ((CurrentPowerState & (BIT8 + BIT9)) == (BIT8 + BIT9)) {
      break;
    }
    FchStall (100, NULL);
  }

  // 3.	Program Host Power and Clock Control register, RO_PCMLRX_REG_CTRL[0] bit (0x16D8_010C[6]/0x16F8_010C[6]) to 1'b1 to switch PHY ref_clk source to RO clock.
  FchSmnRW (0, (FCH_SS_USB_POWER_CLK_CONTROL + Controller * 0x200000), 0xFFFFFFFF, BIT6, LocalCfgPtr->StdHeader);
}

VOID
FchRVXhci0InitS3EntryProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitS3EntryProgram (0, FchDataPtr);
}

VOID
FchRVXhci1InitS3EntryProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciInitS3EntryProgram (1, FchDataPtr);
}

/**
 * FchRVXhciInitSsid - Update Xhci SSID
 *
 *
 * @param[in] DieBusNum  IOCH bus number on current Die.
 * @param[in] Ssid       The SSID value to be updated
 *
 */
VOID
FchRVXhciInitSsid (
  IN  UINT32   DieBusNum,
  IN  UINT32   Ssid
  )
{
  FchSmnRW (DieBusNum, FCH_SS_USB_SMN_PCICFG + 0x4C, 0x00, Ssid, NULL);
  FchSmnRW (DieBusNum, FCH_SS_USB1_SMN_PCICFG + 0x4C, 0x00, Ssid, NULL);
}

/**
 * FchRVXhci0DisablePort - Disable Xhci0 ports
 *
 *
 * @param[in] USB3DisableMap Bitmap to disable USB3 ports.
 * @param[in] USB2DisableMap Bitmap to disable USB2 ports.
 *
 */
BOOLEAN
FchRVXhci0DisablePort (
  IN  UINT32   USB3DisableMap,
  IN  UINT32   USB2DisableMap
  )
{
  UINT32 PortDisableMap;
  UINT32 PortDisableReg;

  PortDisableMap = ((USB3DisableMap & 0xFFFF) << 16) + (USB2DisableMap & 0xFFFF);
  FchSmnRead (0, FCH_SS_USB_PORT_DISABLE0, &PortDisableReg, NULL);

  PortDisableMap |= PortDisableReg;

  //
  // Return TRUE if port already disabled.
  //
  if (PortDisableMap == PortDisableReg) {
    return TRUE;
  }

  FchSmnRW (0, FCH_SS_USB_PORT_DISABLE0, 0x00, PortDisableMap, NULL);
  return TRUE;
}

/**
 * FchRVXhci1DisablePort - Disable Xhci1 ports
 *
 *
 * @param[in] USB3DisableMap Bitmap to disable USB3 ports.
 * @param[in] USB2DisableMap Bitmap to disable USB2 ports.
 *
 */
BOOLEAN
FchRVXhci1DisablePort (
  IN  UINT32   USB3DisableMap,
  IN  UINT32   USB2DisableMap
  )
{
  UINT32 PortDisableMap;
  UINT32 PortDisableReg;

  PortDisableMap = ((USB3DisableMap & 0xFFFF) << 16) + (USB2DisableMap & 0xFFFF);
  FchSmnRead (0, FCH_SS_USB_PORT_DISABLE0 + 0x200000, &PortDisableReg, NULL);

  PortDisableMap |= PortDisableReg;

  //
  // Return TRUE if port already disabled.
  //
  if (PortDisableMap == PortDisableReg) {
    return TRUE;
  }

  FchSmnRW (0, FCH_SS_USB_PORT_DISABLE0 + 0x200000, 0x00, PortDisableMap, NULL);
  return TRUE;
}

/**
 * FchRVXhci0OCmapping -  Xhci0 ports OC mapping
 *
 *
 * @param[in] Port           Usb Port.
 * @param[in] OCPin          Over Current Pin number.
 *
 */
BOOLEAN
FchRV0Xhci0OCmapping (
  IN  UINT8    Port,
  IN  UINT8    OCPin
  )
{
  UINT8        PortOffset;

  if ((Port > 3) || (OCPin > 5)) {
    return FALSE;
  }

  //USB2 Ports
  PortOffset = Port << 2;
  FchSmnRW (0, FCH_SS_USB_PORT_OCMAPPING0, ~(UINT32)(0xF << PortOffset), (UINT32)(OCPin << PortOffset), NULL);

  //USB3 Ports
  PortOffset = (Port << 2) + 16;
  FchSmnRW (0, FCH_SS_USB_PORT_OCMAPPING0, ~(UINT32)(0xF << PortOffset), (UINT32)(OCPin << PortOffset), NULL);

  return TRUE;
}

/**
 * FchRVXhci1OCmapping -  Xhci1 ports OC mapping
 *
 *
 * @param[in] Port           Usb Port.
 * @param[in] OCPin          Over Current Pin number.
 *
 */
BOOLEAN
FchRV0Xhci1OCmapping (
  IN  UINT8    Port,
  IN  UINT8    OCPin
  )
{
  UINT8        PortOffset;

  if ((Port > 1) || (OCPin > 5)) {
    return FALSE;
  }

  //USB2 Ports
  PortOffset = Port << 2;
  FchSmnRW (0, FCH_SS_USB_PORT_OCMAPPING0 + 0x200000, ~(UINT32)(0xF << PortOffset), (UINT32)(OCPin << PortOffset), NULL);

  //USB3 Ports
  PortOffset = (Port << 2) + 16;
  FchSmnRW (0, FCH_SS_USB_PORT_OCMAPPING0 + 0x200000, ~(UINT32)(0xF << PortOffset), (UINT32)(OCPin << PortOffset), NULL);

  return TRUE;
}

/**
 * FchRVXhciSmuService Request -  Xhci1 Service Request
 *
 *
 * @param[in] RequestId           Request ID.
 *
 */
BOOLEAN
FchRVXhciSmuService (
  IN  UINT32    RequestId
  )
{
  BOOLEAN status;
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];

  status = FALSE;
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, RequestId, SmuArg,0)) {
    status = TRUE;
  }

  return status;
}

/**
 * FchRVXhciSmuUsbConfigUpdate  -  Xhci Smu Usb Config Update
 *
 *
 * @param[in] RequestId           Request ID.
 *
 */
BOOLEAN
FchRVXhciSmuUsbConfigUpdate (
  IN  UINT32    smn_register,
  IN  UINT32    smn_mask,
  IN  UINT32    smn_data,
  IN  UINT32    smn_group
  )
{
  BOOLEAN status;
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];
// BIOSSMC_MSG_UsbConfigUpdate               0x38
  status = FALSE;
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  SmuArg[0] = smn_register;
  SmuArg[1] = smn_mask;
  SmuArg[2] = smn_data;
  SmuArg[3] = smn_group;
  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, 0x38, SmuArg,0)) {
    status = TRUE;
  }

  return status;
}

BOOLEAN
FchRVXhciSmuUsbCmdTrap (
  IN  VOID     *FchDataPtr
  )
{
  BOOLEAN         status;
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];
  UINT32          VidDid;
  UINT32          XhciBar0;
  FCH_DATA_BLOCK  *LocalCfgPtr;
  LocalCfgPtr = (FCH_DATA_BLOCK *)FchDataPtr;

//#define BIOSSMC_MSG_SetupUSB31ControllerTrap      0x39
  status = FALSE;
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);

  //Init Arg
  SmuArg[0] = 0x00;
  SmuArg[1] = 0x00;
  SmuArg[2] = 0x00;

  if ((LocalCfgPtr->Usb.Usb0Bar != 0) || (LocalCfgPtr->Usb.Usb1Bar != 0)) {
    if (LocalCfgPtr->Usb.Usb0Bar != 0xFFFFFFFF) {
      SmuArg[0] = LocalCfgPtr->Usb.Usb0Bar;
    }
    if (LocalCfgPtr->Usb.Usb1Bar != 0xFFFFFFFF) {
      SmuArg[1] = LocalCfgPtr->Usb.Usb1Bar;
    }
  } else {
    //USB0
    FchSmnRead (0, FCH_SS_USB_SMN_PCICFG + 0x00, &VidDid, NULL);
    if (VidDid != 0xFFFFFFFF) {
      FchSmnRead (0, FCH_SS_USB_SMN_PCICFG + 0x10, &XhciBar0, NULL);
      XhciBar0 &= 0xFFFFFFF0;
      SmuArg[0] = XhciBar0;
    }
    //USB1
    FchSmnRead (0, FCH_SS_USB1_SMN_PCICFG + 0x00, &VidDid, NULL);
    if (VidDid != 0xFFFFFFFF) {
      FchSmnRead (0, FCH_SS_USB1_SMN_PCICFG + 0x10, &XhciBar0, NULL);
      XhciBar0 &= 0xFFFFFFF0;
      SmuArg[1] = XhciBar0;
    }
  }

  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, 0x39, SmuArg,0)) {
    status = TRUE;
  }

  return status;
}

/**
 * FchRVXhciController0ForceGen1  -  Xhci Controller0 Force Gen1
 *
 *
 *
 */
VOID
FchRVXhciController0ForceGen1 (
  IN  VOID     *FchDataPtr
  )
{
  UINT8                       Port;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  //FCH_DEADLOOP ();
  FchRVXhciSmuUsbConfigUpdate (0x16D80130, 0xf << (16), 0xf << (16), 0x01000001);

  for (Port = 0; Port < 4; Port++) {
    FchRVXhciSmuUsbConfigUpdate (0x16C0D024 + Port * 0x80, 1 << (10), 1 << (10), 0x01000003);
  }
}

/**
 * FchRVXhci1Disable31Port  -  Xhci Disable 3.1Port
 *
 *
 *
 */
VOID
FchRVXhci1Disable31Port (
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  FchRVXhciSmuUsbConfigUpdate (0x16F80128, 0x1 << (16), 0x1 << (16), 0x01000001);
}

/**
 * FchRVXhciSmuUsbPowerService  -  Xhci1 Usb Power Service
 *
 *
 * @param[in] RequestId           Request ID.
 *
 */
BOOLEAN
FchRVXhciSmuUsbPowerService (
  IN  UINT32    UsbId
  )
{
  BOOLEAN status;
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];
#define BIOSSMC_MSG_UsbxHciControllerPoweredOff 0x44

//Argument of the message should be like this:
//bit 16 == Usb Controller ID <-- 0 for USB0 and 1 for USB1
//bit 0 == Power Status <-- 1 for Disabled / Powered Off and 0 for enabled
  status = FALSE;
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
  SmuArg[0] = UsbId;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, BIOSSMC_MSG_UsbxHciControllerPoweredOff, SmuArg,0)) {
    status = TRUE;
  }

  return status;
}

/**
 * FchRVUsbOemUsb20PhyConfigure  -  USB 2.0 PHY Platform
 * Configurationb
 *
 *
 *
 */
VOID
FchRVUsbOemUsb20PhyConfigure (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    Port;
  UINT32   DW0_Index;
  UINT32   DW1_Mask0;
  UINT32   DW1_Mask1;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;

  //Controller0
  DW0_Index    = 0x16D1C000;
  DW1_Mask0    = 0xF3BF7007;
  DW1_Mask1    = 0x0000000F;
  DW3_Op_Group = 0x01000001;
  for (Port = 0; Port < 4; Port++) {
    //Param0
    DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[Port].COMPDSTUNE & 0x07) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].SQRXTUNE & 0x07) << 12) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXFSLSTUNE & 0x0F) << 16) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXPREEMPAMPTUNE & 0x03) << 20) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXPREEMPPULSETUNE & 0x01) << 23) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXRISETUNE & 0x03) << 24) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXVREFTUNE & 0x0F) << 28));
    FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x400 * Port, DW1_Mask0, DW2_Data, DW3_Op_Group);

    //Param1
    DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXHSXVTUNE & 0x03) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXRESTUNE & 0x03) << 2));
    FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x400 * Port + 0x04, DW1_Mask1, DW2_Data, DW3_Op_Group);
  }

  //Controller1
  // Port0 Common PHY
  DW0_Index    = 0x16F0C000;
  DW1_Mask0    = 0x03FFDFCF;
  DW3_Op_Group = 0x01000001;
  DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXVREFTUNE & 0x0F) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXRISETUNE & 0x03) << 6) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXRESTUNE & 0x03) << 8) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXPREEMPAMPTUNE & 0x03) << 10) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXPREEMPPULSETUNE & 0x01) << 12) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXHSXVTUNE & 0x03) << 14) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].TXFSLSTUNE & 0x0F) << 16) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].SQRXTUNE & 0x07) << 20) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[4].COMPDSTUNE & 0x07) << 23));
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask0, DW2_Data, DW3_Op_Group);

  //Port1
  DW0_Index    = 0x16F1C000;
  DW1_Mask0    = 0xF3BF7007;
  DW1_Mask1    = 0x0000000F;
  DW3_Op_Group = 0x01000001;
  //Param0
  DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[5].COMPDSTUNE & 0x07) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].SQRXTUNE & 0x07) << 12) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXFSLSTUNE & 0x0F) << 16) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXPREEMPAMPTUNE & 0x03) << 20) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXPREEMPPULSETUNE & 0x01) << 23) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXRISETUNE & 0x03) << 24) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXVREFTUNE & 0x0F) << 28));
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask0, DW2_Data, DW3_Op_Group);

  //Param1
  DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXHSXVTUNE & 0x03) +
               ((FchUsbOemPlatformTable->Usb20PhyPort[5].TXRESTUNE & 0x03) << 2));
  FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x04, DW1_Mask1, DW2_Data, DW3_Op_Group);
}

/**
 * FchRV2UsbOemUsb20PhyConfigure  -  USB 2.0 PHY Platform
 * Configurationb
 *
 *
 *
 */
VOID
FchRV2UsbOemUsb20PhyConfigure (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    Port;
  UINT32   DW0_Index;
  UINT32   DW1_Mask0;
  UINT32   DW1_Mask1;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;

  //Controller0 Port0 - 5
  DW0_Index    = 0x16D1C000;
  DW1_Mask0    = 0xF3BF7007;
  DW1_Mask1    = 0x0000000F;
  DW3_Op_Group = 0x01000001;
  for (Port = 0; Port < 6; Port++) {
    //Param0
    DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[Port].COMPDSTUNE & 0x07) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].SQRXTUNE & 0x07) << 12) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXFSLSTUNE & 0x0F) << 16) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXPREEMPAMPTUNE & 0x03) << 20) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXPREEMPPULSETUNE & 0x01) << 23) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXRISETUNE & 0x03) << 24) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXVREFTUNE & 0x0F) << 28));
    FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x400 * Port, DW1_Mask0, DW2_Data, DW3_Op_Group);

    //Param1
    DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXHSXVTUNE & 0x03) +
                 ((FchUsbOemPlatformTable->Usb20PhyPort[Port].TXRESTUNE & 0x03) << 2));
    FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x400 * Port + 0x04, DW1_Mask1, DW2_Data, DW3_Op_Group);
  }
}


/**
 * FchRV2UsbOemUsb31PhyConfigure  -  USB 3.1 PHY Platform
 * Configuration
 *
 *
 *
 */
VOID
FchRV2UsbOemUsb31PhyConfigure (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8                         Port;
  UINT32                        DW0_Index;
  UINT32                        DW1_Mask;
  UINT32                        DW2_Data;
  UINT32                        DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;
  FCH_USB31_PHY                 Usb31PhyFt5;
  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;
  if (FchUsbOemPlatformTable->Usb31Phy.Usb31PhyEnable == 0x00){
      return;
  }
  IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2UsbOemUsb31PhyConfigure Started!\n");
  if (FchCheckFt5PackageType()){  //FT5
    LibAmdMemCopy(&Usb31PhyFt5, &(FchUsbOemPlatformTable->Usb31Phy), sizeof(FCH_USB31_PHY), NULL);
    //USB port 1 in FP5 map to XHCI port 3
    LibAmdMemCopy(&(FchUsbOemPlatformTable->Usb31Phy.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[3]), &(Usb31PhyFt5.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[1]), sizeof(USB_31_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN), NULL);
    //USB port [3:2] in FP5 map to XHCI port [2:1]
    LibAmdMemCopy(&(FchUsbOemPlatformTable->Usb31Phy.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[1]), &(Usb31PhyFt5.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[2]), sizeof(USB_31_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN) * 2, NULL);
  }
  DW0_Index    = FCH_SS_USB0_RAWLANE0_DIG_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN;
  DW1_Mask     = 0x0000001F;
  DW3_Op_Group = 0x01000002;
  for (Port = 0; Port < 4; Port++) {
      DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb31Phy.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[Port].RX_EQ_DELTA_IQ_OVRD_VAL & 0xF) +
                          ((FchUsbOemPlatformTable->Usb31Phy.PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[Port].RX_EQ_DELTA_IQ_OVRD_EN & 0x1) << 4));
      FchRVXhciSmuUsbConfigUpdate (DW0_Index + 0x400 * Port, DW1_Mask, DW2_Data, DW3_Op_Group);
      IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2UsbOemUsb31PhyConfigure through UsbConfigUpdate Message with %x, %x, %x, %x\n", DW0_Index + 0x400 * Port, DW1_Mask, DW2_Data, DW3_Op_Group);
  }
  DW0_Index    = FCH_SS_USB0_SUP_DIG_LVL_OVRD_IN;
  DW1_Mask     = 0x000003FF;
  DW3_Op_Group = 0x01000002;
  DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN.RX_VREF_CTRL & 0x1F) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN.RX_VREF_CTRL_EN & 0x1) << 5) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN.TX_VBOOST_LVL & 0x7) << 6) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN.TX_VBOOST_LVL_EN & 0x1) << 9));
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
  IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2UsbOemUsb31PhyConfigure through UsbConfigUpdate Message with %x, %x, %x, %x\n", DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
  DW0_Index    = FCH_SS_USB0_SUPX_DIG_LVL_OVRD_IN;
  DW1_Mask     = 0x000003FF;
  DW3_Op_Group = 0x01000002;
  DW2_Data = (UINT32) ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN_X.RX_VREF_CTRL & 0x1F) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN_X.RX_VREF_CTRL_EN & 0x1) << 5) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN_X.TX_VBOOST_LVL & 0x7) << 6) +
                    ((FchUsbOemPlatformTable->Usb31Phy.LVL_OVRD_IN_X.TX_VBOOST_LVL_EN & 0x1) << 9));
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
  IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2UsbOemUsb31PhyConfigure through UsbConfigUpdate Message with %x, %x, %x, %x\n", DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
}
/**
 * FchRVUsbOemDeviceRemovable  -  Device Removable
 *
 *
 *
 */
VOID
FchRVUsbOemDeviceRemovable (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    Usb2Dr;
  UINT8    Usb3Dr;
  UINT32   DW0_Index;
  UINT32   DW1_Mask;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;

  //Controller0
  DW0_Index    = 0x16D80114;
  DW1_Mask     = 0xFFFFFFFF;
  DW3_Op_Group = 0x01000001;
  Usb2Dr       = FchUsbOemPlatformTable->DeviceRemovable & 0x0F;           // RV bit[3:0] port0 - port3 -> Controller0
  Usb3Dr       = Usb2Dr;
  DW2_Data     = (UINT32)((Usb3Dr << 16) + Usb2Dr);
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);

  //Controller1
  DW0_Index    = 0x16F80114;
  DW1_Mask     = 0xFFFFFFFF;
  DW3_Op_Group = 0x01000001;
  Usb2Dr       = (FchUsbOemPlatformTable->DeviceRemovable >> 4) & 0x03;    // RV bit[5:4] port4/5 -> controller1
  Usb3Dr       = Usb2Dr;
  DW2_Data     = (UINT32)((Usb3Dr << 16) + Usb2Dr);
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
}

/**
 * FchRV2UsbOemDeviceRemovable  -  Device Removable
 *
 *
 *
 */
VOID
FchRV2UsbOemDeviceRemovable (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    Usb2Dr;
  UINT8    Usb3Dr;
  UINT8    Usb3DrFt5;
  UINT32   DW0_Index;
  UINT32   DW1_Mask;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;

  //Controller0
  DW0_Index    = 0x16D80114;
  DW1_Mask     = 0xFFFFFFFF;
  DW3_Op_Group = 0x01000001;
  Usb2Dr       = FchUsbOemPlatformTable->DeviceRemovable & 0x3F;           // RV2 bit[5:0] USB2 port0 - port5
  Usb3Dr       = Usb2Dr & 0x0F;                                            // USB3 port0 - port3
  if (FchCheckFt5PackageType()){  //FT5
    Usb3DrFt5 = Usb3Dr;
    //USB port 1 in FP5 map to XHCI port 3
    Usb3Dr &= (~BIT3);
    Usb3Dr |= ((Usb3DrFt5 & BIT1) << 2);
    //USB port [3:2] in FP5 map to XHCI port [2:1]
    Usb3Dr &= (~(BIT2 | BIT1));
    Usb3Dr |= ((Usb3DrFt5 & (BIT3 | BIT2)) >> 1);
  }
  DW2_Data     = (UINT32)((Usb3Dr << 16) + Usb2Dr);
  FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
}


/**
 * FchRVUsbOemPortForceGen1  -  Port Force Gen1
 *
 *
 *
 */
VOID
FchRVUsbOemPortForceGen1 (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    Port;
  UINT8    UsbPortForceGen1;
  UINT8    UsbPortForceGen1Ft5;
  UINT32   DW0_Index;
  UINT32   DW1_Mask;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;
  UsbPortForceGen1  = FchUsbOemPlatformTable->Usb3PortForceGen1;
  UsbPortForceGen1 &= 0xF;
  if (FchCheckFt5PackageType()){  //FT5
    UsbPortForceGen1Ft5 = UsbPortForceGen1;
    //USB port 1 in FP5 map to XHCI port 3
    UsbPortForceGen1 &= (~BIT3);
    UsbPortForceGen1 |= ((UsbPortForceGen1Ft5 & BIT1) << 2);
    //USB port [3:2] in FP5 map to XHCI port [2:1]
    UsbPortForceGen1 &= (~(BIT2 | BIT1));
    UsbPortForceGen1 |= ((UsbPortForceGen1Ft5 & (BIT3 | BIT2)) >> 1);
  }

  if (UsbPortForceGen1 != 0) {
    //Controller0 Port Control
    DW0_Index    = 0x16D80130;
    DW1_Mask     = 0xf << 16;
    DW2_Data     = (UINT32) (UsbPortForceGen1 << 16);
    DW3_Op_Group = 0x01000001;
    FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);

    for (Port = 0; Port < 4; Port++) {
      if (UsbPortForceGen1 & (1 << Port)) {
        FchRVXhciSmuUsbConfigUpdate (0x16C0D024 + Port * 0x80, 1 << (10), 1 << (10), 0x01000003);
      }
    }
  }
}

/**
 * FchRVUsbOemU3RxDetWA  - U3 RxDet Workaround (USB0 and USB1)
 *
 *
 *
 */
VOID
FchRVUsbOemU3RxDetWA (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    U3RxDetWAEnable;
  UINT8    U3RxDetWAPortMap;
  UINT32   DW0_Index;
  UINT32   DW1_Mask;
  UINT32   DW2_Data;
  UINT32   DW3_Op_Group;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;
  U3RxDetWAEnable  = FchUsbOemPlatformTable->U3RxDetWAEnable;
  U3RxDetWAPortMap = FchUsbOemPlatformTable->U3RxDetWAPortMap;

  if (U3RxDetWAEnable != 0) {
    DW0_Index    = 0x00;
    DW1_Mask     = 0x00;
    DW2_Data     = 0x00;

    //Controller0 Port Control
    if (U3RxDetWAPortMap & 0xF ) {
      DW3_Op_Group = (UINT32) (U3RxDetWAPortMap & 0xF) ;
      DW3_Op_Group |= 0x81000000;
      FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
    }

    //Controller1 Port Control
    if (U3RxDetWAPortMap & BIT4 ) {
      DW3_Op_Group = 0x81100001 ;
      FchRVXhciSmuUsbConfigUpdate (DW0_Index, DW1_Mask, DW2_Data, DW3_Op_Group);
    }
  }
}

/**
 * FchRVUsbOemU0inU3WA  - U0-in-D3 Workaround (USB0 only)
 *
 *
 *
 */
VOID
FchRVUsbOemU0inU3WA (
  IN  VOID     *PlatformConfigureTable
  )
{
  FchRVXhciSmuUsbConfigUpdate (0x00, 0x00, 0x00, 0x8200000F);
}

/**
 * FchRVUsbOemEarlyDebug - Early Debug-select Setup (USB0 and
 * USB1)
 *
 *
 *
 */
VOID
FchRVUsbOemEarlyDebug (
  IN  VOID     *PlatformConfigureTable
  )
{
  UINT8    EarlyDebugSelectEnable;
  FCH_RV_USB_OEM_PLATFORM_TABLE *FchUsbOemPlatformTable;

  FchUsbOemPlatformTable  = (FCH_RV_USB_OEM_PLATFORM_TABLE *)PlatformConfigureTable;
  EarlyDebugSelectEnable  = FchUsbOemPlatformTable->EarlyDebugSelectEnable;

  if (EarlyDebugSelectEnable != 0) {
    FchRVXhciSmuUsbConfigUpdate (0x00, 0x00, 0x00, 0xA0000000);
    FchRVXhciSmuUsbConfigUpdate (0x00, 0x00, 0x00, 0xA0100000);
  }
}

/**
 * FchRVXhciDisablePort  -  Xhci Disable Port Control
 *
 *
 *
 */
VOID
FchRVXhciDisablePort (
  IN  VOID     *FchDataPtr
  )
{
  UINT32                      Usb3PortDisable;
  UINT32                      Usb2PortDisable;
  UINT32                      UsbPortDisable;

  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  Usb3PortDisable = LocalCfgPtr->XhciUsb3PortDisable;
  Usb2PortDisable = LocalCfgPtr->XhciUsb2PortDisable;

  // Port0-3 : Controller0
  UsbPortDisable = (Usb2PortDisable & 0x0F) + ((Usb3PortDisable & 0xF) << 16);
  FchRVXhciSmuUsbConfigUpdate (0x16D80128, 0x000F000F, UsbPortDisable, 0x01000001);

  // Usb3 Port4: Controller1
  // Usb2 Port4/5: Controller1
  Usb3PortDisable = Usb3PortDisable >> 4;
  Usb2PortDisable = Usb2PortDisable >> 4;
  UsbPortDisable = (Usb2PortDisable & 0x03) + ((Usb3PortDisable & 0x1) << 16);
  FchRVXhciSmuUsbConfigUpdate (0x16F80128, 0x000F000F, UsbPortDisable, 0x01000001);
}

/**
 * FchRV2XhciDisablePort  -  Xhci Disable Port Control
 *
 *
 *
 */
VOID
FchRV2XhciDisablePort (
  IN  VOID     *FchDataPtr
  )
{
  UINT32                      Usb3PortDisable;
  UINT32                      Usb2PortDisable;
  UINT32                      UsbPortDisable;
  UINT32                      Usb3PortDisFt5;

  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  Usb3PortDisable = LocalCfgPtr->XhciUsb3PortDisable;
  Usb2PortDisable = LocalCfgPtr->XhciUsb2PortDisable;
  if (FchCheckFt5PackageType()){  //FT5
    Usb3PortDisFt5 = LocalCfgPtr->XhciUsb3PortDisable;
    //USB port 1 in FP5 map to XHCI port 3
    Usb3PortDisable &= (~BIT3);
    Usb3PortDisable |= ((Usb3PortDisFt5 & BIT1) << 2);
    //USB port [3:2] in FP5 map to XHCI port [2:1]
    Usb3PortDisable &= (~(BIT2 | BIT1));
    Usb3PortDisable |= ((Usb3PortDisFt5 & (BIT3 | BIT2)) >> 1);
  }

  // Port0-5 : Controller0 USB2
  // Port0-3 : Controller0 USB3
  UsbPortDisable = (Usb2PortDisable & 0x3F) + ((Usb3PortDisable & 0xF) << 16);
  FchRVXhciSmuUsbConfigUpdate (0x16D80128, 0x000F003F, UsbPortDisable, 0x01000001);
}

/**
 * FchRVXhciOverCurrent  -  Xhci OC Pin Mapping
 *
 *
 *
 */
VOID
FchRVXhciOverCurrent (
  IN  VOID     *FchDataPtr
  )
{
  UINT32    OverCurrentMap;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  //Controller0
  OverCurrentMap = LocalCfgPtr->XhciOCpinSelect;
  OverCurrentMap = OverCurrentMap & 0xFFFF;
  OverCurrentMap = OverCurrentMap + (OverCurrentMap << 16);
  FchRVXhciSmuUsbConfigUpdate (0x16D80120, 0xFFFFFFFF, OverCurrentMap, 0x01000001);

  //Controller1
  OverCurrentMap = LocalCfgPtr->XhciOCpinSelect;
  OverCurrentMap = OverCurrentMap >> 16;
  OverCurrentMap = (OverCurrentMap & 0xFF) + ((OverCurrentMap & 0xF) << 8);
  FchRVXhciSmuUsbConfigUpdate (0x16F80120, 0x00000FFF, OverCurrentMap, 0x01000001);
}


/**
 * FchRV2XhciOverCurrent  -  Xhci OC Pin Mapping
 *
 *
 *
 */
VOID
FchRV2XhciOverCurrent (
  IN  VOID     *FchDataPtr
  )
{
  UINT32    OverCurrentMap;
  UINT32                      Usb3PortOcFt5;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  OverCurrentMap = LocalCfgPtr->XhciOCpinSelect;
  OverCurrentMap = OverCurrentMap & 0xFFFFFF;
  OverCurrentMap = OverCurrentMap + ((OverCurrentMap & 0xFF) << 24);
  if (FchCheckFt5PackageType()){  //FT5
    Usb3PortOcFt5 = LocalCfgPtr->XhciOCpinSelect;
    //USB3.1 port 2 in FP5 map to XHCI port 1
    OverCurrentMap &= 0xF0000000;
    OverCurrentMap |= ((Usb3PortOcFt5 & 0x00000F00) << 20);
  }
  FchRVXhciSmuUsbConfigUpdate (0x16D80120, 0xFFFFFFFF, OverCurrentMap, 0x01000001);

  OverCurrentMap = LocalCfgPtr->XhciOCpinSelect;
  OverCurrentMap = (OverCurrentMap & 0xFF00) >> 8;
  if (FchCheckFt5PackageType()){  //FT5
    Usb3PortOcFt5 = LocalCfgPtr->XhciOCpinSelect;
    //USB3.1 port [3,1] in FP5 map to XHCI port [2,3]
    OverCurrentMap &= 0x000000FF;
    OverCurrentMap |= (Usb3PortOcFt5 & 0x000000F0);
    OverCurrentMap |= ((Usb3PortOcFt5 & 0x0000F000) >> 12);
  }
  FchRVXhciSmuUsbConfigUpdate (0x16D80124, 0x000000FF, OverCurrentMap, 0x01000001);

}

/**
 * FchRVXhciSparseMode  -  XHCI Sparse Control Transaction Enable
 *
 *
 *
 */
VOID
FchRVXhciSparseMode(
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  if (LocalCfgPtr->UsbSparseModeEnable) {
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB_GUCTL, BIT17, BIT17, 0x01000003);
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB1_GUCTL, BIT17, BIT17, 0x01000003);
    IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRVXhciSparseMode Enabled\n");
  } else {
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB_GUCTL, BIT17, 0, 0x01000003);
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB1_GUCTL, BIT17, 0, 0x01000003);
    IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRVXhciSparseMode Disabled\n");
  }
}
/**
 * FchRV2XhciSparseMode  -  XHCI Sparse Control Transaction Enable
 *
 *
 *
 */
VOID
FchRV2XhciSparseMode(
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  if (LocalCfgPtr->UsbSparseModeEnable) {
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB_GUCTL, BIT17, BIT17, 0x01000003);
    IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2XhciSparseMode Enabled\n");
  } else {
    FchRVXhciSmuUsbConfigUpdate (FCH_SS_USB_GUCTL, BIT17, 0, 0x01000003);
    IDS_HDT_CONSOLE (FCH_TRACE, "[FCH]FchRV2XhciSparseMode Disabled\n");
  }
}
/**
 * FchRVXhciDowngradeIssueFix  -  Fix sowngrande-to-USB 2.0
 * issue when Gen2 force Gen1
 *
 *
 *
 */
VOID
FchRVXhciDowngradeIssueFix (
  IN  VOID     *FchDataPtr
  )
{
  //Port0
  FchRVXhciSmuUsbConfigUpdate (0x16D2C19C, 0x0000FFFF, 0x000001FF, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2C1AC, 0x0000FFFF, 0x00000080, 0x01000002);

  //Port1
  FchRVXhciSmuUsbConfigUpdate (0x16D2C59C, 0x0000FFFF, 0x000001FF, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2C5AC, 0x0000FFFF, 0x00000080, 0x01000002);

  //Port2
  FchRVXhciSmuUsbConfigUpdate (0x16D2C99C, 0x0000FFFF, 0x000001FF, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2C9AC, 0x0000FFFF, 0x00000080, 0x01000002);

  //Port3
  FchRVXhciSmuUsbConfigUpdate (0x16D2CD9C, 0x0000FFFF, 0x000001FF, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2CDAC, 0x0000FFFF, 0x00000080, 0x01000002);
}

/**
 * FchRVXhciPhug1Update  -  set PHUG1 to 3 to improve margin in
 * JTOL test.
 *
 *
 *
 */
VOID
FchRVXhciPhug1Update (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciSmuUsbConfigUpdate (0x16D2415C, 0x00007000, 0x00003000, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2455C, 0x00007000, 0x00003000, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D2495C, 0x00007000, 0x00003000, 0x01000002);
  FchRVXhciSmuUsbConfigUpdate (0x16D24D5C, 0x00007000, 0x00003000, 0x01000002);
}

/**
 * FchRVXhciOemConfigure  -  Xhci Platform Configurationb
 *
 *
 *
 */
VOID
FchRVXhciOemConfigure (
  IN  VOID     *PlatformConfigureTable
  )
{
  RAVEN2_TYPE            Raven2Type;

  Raven2Type = FchCheckRaven2Type();
  if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
    FchRV2UsbOemUsb20PhyConfigure (PlatformConfigureTable);
    FchRV2UsbOemUsb31PhyConfigure (PlatformConfigureTable);
    FchRV2UsbOemDeviceRemovable (PlatformConfigureTable);
  } else {
    FchRVUsbOemUsb20PhyConfigure (PlatformConfigureTable);
    FchRVUsbOemDeviceRemovable (PlatformConfigureTable);
  }

  FchRVUsbOemPortForceGen1 (PlatformConfigureTable);
  FchRVUsbOemU3RxDetWA (PlatformConfigureTable);
  FchRVUsbOemEarlyDebug (PlatformConfigureTable);
}

/**
 * FchRVXhciPassParameter  -  Xhci Pass Parameters
 *
 *
 *
 */
VOID
FchRVXhciPassParameter (
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK          *LocalCfgPtr;
  FCH_RV_USB_OEM_PLATFORM_TABLE *PlatformUsbConfigureTable;
  RAVEN2_TYPE                   Raven2Type;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;
  PlatformUsbConfigureTable = (FCH_RV_USB_OEM_PLATFORM_TABLE *)(LocalCfgPtr->OemUsbConfigurationTablePtr);
  Raven2Type = FchCheckRaven2Type();

  // PLAT-26776
  {
    UINT8   PkgType;
    UINT32  RegEbx;
    AsmCpuid (0x80000001, NULL, &RegEbx, NULL, NULL);
    PkgType = (UINT8) (RegEbx >> 28);
    if (PkgType == 0x02) {               // AM4
      if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
        //RV2
        LocalCfgPtr->Xhci0ForceGen1 = TRUE;

        //disable USB2.0 port0/5)
        LocalCfgPtr->XhciUsb2PortDisable |= 0x00000021;
      } else {
        //RV1
        LocalCfgPtr->Xhci0ForceGen1 = TRUE;

        //disable controller0 port0 (SS/HS)
        //disable controller1 port1 (HS)
        LocalCfgPtr->XhciUsb3PortDisable |= 0x00000001;
        LocalCfgPtr->XhciUsb2PortDisable |= 0x00000021;
        //hide controller1 port1
        FchRVXhciSmuUsbConfigUpdate (0x16F80130, 0x0000000F, 0x00000001, 0x01000001);
      }
    }
  }

  if (LocalCfgPtr->Xhci0ForceGen1) {
    FchRVXhciController0ForceGen1 (LocalCfgPtr);
  }
  if (LocalCfgPtr->Xhci1Disable31Port) {
    LocalCfgPtr->XhciUsb3PortDisable |= 0x00000010;
  }

  Raven2Type = FchCheckRaven2Type();
  if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
    //RV2
    FchRV2XhciDisablePort (LocalCfgPtr);
      FchRV2XhciOverCurrent (LocalCfgPtr);
	 FchRV2XhciSparseMode (LocalCfgPtr);
  } else {
    FchRVXhciDisablePort (LocalCfgPtr);
    FchRVXhciOverCurrent (LocalCfgPtr);
    FchRVXhciSparseMode (LocalCfgPtr);
  }

  if ((PlatformUsbConfigureTable->Version_Major == 0x0D)  && (PlatformUsbConfigureTable->Version_Minor == 0x00)) {            //RV USB D.0
    FchRVXhciOemConfigure (PlatformUsbConfigureTable);
  }

  //
  // U0-in-D3 workaround is required by default so the message with opcode 0x82 must be sent.
  //
  FchRVUsbOemU0inU3WA (PlatformUsbConfigureTable);

  FchRVXhciDowngradeIssueFix (LocalCfgPtr);

  FchRVXhciPhug1Update (LocalCfgPtr);
}

VOID
FchRVInitRfmux (
  IN  VOID     *FchDataPtr
  )
{
  RwMem (0xFEDC6700, AccessWidth32, 0x000000FF, BIT16 + BIT8);
  RwMem (0xFEDC6704, AccessWidth32, 0x00, 0x9393);
  RwMem (0xFEDC6708, AccessWidth32, 0x00, 0x0303);
  RwMem (0xFEDC670C, AccessWidth32, 0x00, 0x00);

  RwMem (0xFEDC6710, AccessWidth32, 0x000000FF, BIT16 + BIT8);
  RwMem (0xFEDC6714, AccessWidth32, 0x00, 0x9393);
  RwMem (0xFEDC6718, AccessWidth32, 0x00, 0x0303);
  RwMem (0xFEDC671C, AccessWidth32, 0x00, 0x00);
}

VOID
FchRVClearRfmux (
  IN  VOID     *FchDataPtr
  )
{
  RwMem (0xFEDC6700, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC6704, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC6708, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC670C, AccessWidth32, 0x00, 0x00);

  RwMem (0xFEDC6710, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC6714, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC6718, AccessWidth32, 0x00, 0x00);
  RwMem (0xFEDC671C, AccessWidth32, 0x00, 0x00);
}

VOID
FchRVUsb3InitS3EntryProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVXhciSmuService (SMC_MSG_UsbD3Entry);
  FchRVXhciInitS3EntryProgram (0, FchDataPtr);
  FchRVXhciInitS3EntryProgram (1, FchDataPtr);
  FchRVClearRfmux (FchDataPtr);
}

VOID
FchRVUsb3InitS3ExitProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVInitRfmux (FchDataPtr);
  FchRVXhciInitS3ExitProgram (0, FchDataPtr);
  FchRVXhciInitS3ExitProgram (1, FchDataPtr);
  FchRVXhciPassParameter (FchDataPtr);
  FchRVXhciSmuService (SMC_MSG_UsbD3Exit);
}

VOID
FchRVUsb3InitBootProgram (
  IN  VOID     *FchDataPtr
  )
{
  FchRVInitRfmux (FchDataPtr);
  FchRVXhciInitPgfsm (0, FchDataPtr);
  FchRVXhciInitPgfsm (1, FchDataPtr);
  FchRVXhciPassParameter (FchDataPtr);
  FchRVXhciSmuService (SMC_MSG_UsbInit);
}



