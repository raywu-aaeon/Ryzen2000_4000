/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <AmdCpmBase.h>
#include <AmdCpmBaseIo.h>
#include CPM_PPI_DEFINITION (AmdCpmTablePpi)

#define GPIO_BASE                       0x100
#define SMI_BASE                        0x200
#define PMIO_BASE                       0x300
#define PMIO2_BASE                      0x400
#define RAM_BASE                        0x500
#define CMOSRAM_BASE                    0x600
#define CMOS_BASE                       0x700
#define ACPI_BASE                       0x800
#define IOMUX_BASE                      0xD00
#define MISC_BASE                       0xE00
#define GPIO_BANK_BASE                  0x1500

#define AMD_SMIREG_EVENT_ENABLE         0x04
#define AMD_SMIREG_SCITRIG              0x08
#define AMD_SMIREG_SCILEVEL             0x0C
#define AMD_SMIREG_SMISCIEN             0x14
#define AMD_SMIREG_SWSCIEN              0x18
#define AMD_SMIREG_SWSCIDATA            0x1C
#define AMD_SMIREG_SCIS0EN              0x20
#define AMD_SMIREG_SCIMAP0              0x40
#define AMD_SMIREG_SMITRIG              0x98
#define AMD_SMIREG_SMICONTROL0          0xA0
#define AMD_SMICONTROL_MASK             0x03
#define AMD_GEVENT_SCIMASK              0xE0    // And Mask ~ 0x1F

#define IO_DELAY_PORT                   0xDE
#define MAX_TIMER                       0xFFFFFFFFul
#define ELAPSED_TIME_UNIT               28
#define ELAPSED_TIME_DIVIDER            100

#define SB_SATA_BUS                     0x00
#define SB_SATA_DEVICE                  0x11
#define SB_SATA_FUNCTION                0x00

#define ZP_BRIDGE_BUS                   0x00
#define ZP_BRIDGE_DEVICE                0x08
#define ZP_BRIDGE_FUNCTION              0x01
#define ZP_SATA_DEVICE                  0x00
#define ZP_SATA_FUNCTION                0x02

#define RV_BRIDGE_BUS                   0x00
#define RV_BRIDGE_DEVICE                0x08
#define RV_BRIDGE_FUNCTION              0x02
#define RV_SATA_DEVICE                  0x00
#define RV_SATA_FUNCTION                0x00

#define PtGpioFun                       0x02
#define PtTempBus                       0x1F

#define FchSmnGpio                      0x02D02500
#define FchSmnIomux                     0x02D01D00
#define FchSmnMisc                      0x02D01E00
#define FchSmnMisc2                     0x02D02300

#define FCH_LPC_BUS                     0
#define FCH_LPC_DEV                     20
#define FCH_LPC_FUNC                    3
#define FCH_LPC_REG4A                   0x4A        // IO/Mem Port Decode Enable Register 6- RW

AMD_CPM_SATA_MODE_MASK  SataModeMask[] = {
  {0x7800, 0x01},           // IDE
  {0x7801, 0x02},           // AHCI
  {0x7802, 0x04},           // RAID
  {0x7803, 0x04},           // RAID5
  {0x7804, 0x08},           // AMD AHCI
  {0x7805, 0x04},           // Dot Hill RAID
  {0x780A, 0x04},           // 3rd Party RAID
  {0x4390, 0x01},           // IDE
  {0x4391, 0x02},           // AHCI
  {0x4392, 0x04},           // RAID
  {0x4393, 0x04},           // RAID5
  {0x4394, 0x08},           // AMD AHCI
  {0x7900, 0x01},           // IDE
  {0x7901, 0x02},           // AHCI
  {0x7902, 0x04},           // RAID
  {0x7903, 0x04},           // RAID5
  {0x7904, 0x08},           // AMD AHCI
  {0x7905, 0x04},           // Dot Hill RAID
  {0x790A, 0x04},           // 3rd Party RAID
  {0xFFFF, 0xFF},           //EOT
};

PCIE_BRIDGE_NAME FchPcieBridgeName[] = {
  {0, 21, 0, 0x30, AMD_CPM_FCH_PCIE_GPP0_NAME},
  {0, 21, 1, 0x31, AMD_CPM_FCH_PCIE_GPP1_NAME},
  {0, 21, 2, 0x32, AMD_CPM_FCH_PCIE_GPP2_NAME},
  {0, 21, 3, 0x33, AMD_CPM_FCH_PCIE_GPP3_NAME},
  0
};

UINT8 FchGeventGpioMappingTable[] = {
  0x7E,         // GEVENT0 => GPIO126
  0x81,         // GEVENT1 => GPIO129
  0x03,         // GEVENT2 => GPIO3
  0x16,         // GEVENT3 => GPIO22
  0x04,         // GEVENT4 => GPIO4
  0x15,         // GEVENT5 => GPIO21
  0x0E,         // GEVENT6 => GPIO14
  0x05,         // GEVENT7 => GPIO5
  0x02,         // GEVENT8 => GPIO2
  0x20,         // GEVENT9 => GPIO32
  0x06,         // GEVENT10 => GPIO6
  0x07,         // GEVENT11 => GPIO7
  0x10,         // GEVENT12 => GPIO16
  0x11,         // GEVENT13 => GPIO17
  0x12,         // GEVENT14 => GPIO18
  0x18,         // GEVENT15 => GPIO24
  0x17,         // GEVENT16 => GPIO23
  0x19,         // GEVENT17 => GPIO25
  0x0B,         // GEVENT18 => GPIO11
  0x01,         // GEVENT19 => GPIO1
  0x0F,         // GEVENT20 => GPIO15
  0x0D,         // GEVENT21 => GPIO13
  0x09          // GEVENT22 => GPIO9
};

UINT8 FchGeventGpioMappingTable2[] = {
  0x41,         // GEVENT0 => GPIO65
  0x42,         // GEVENT1 => GPIO66
  0x03,         // GEVENT2 => GPIO3
  0x16,         // GEVENT3 => GPIO22
  0x04,         // GEVENT4 => GPIO4
  0x15,         // GEVENT5 => GPIO21
  0x0E,         // GEVENT6 => GPIO14
  0x05,         // GEVENT7 => GPIO5
  0x02,         // GEVENT8 => GPIO2
  0x44,         // GEVENT9 => GPIO68
  0x06,         // GEVENT10 => GPIO6
  0x07,         // GEVENT11 => GPIO7
  0x10,         // GEVENT12 => GPIO16
  0x11,         // GEVENT13 => GPIO17
  0x12,         // GEVENT14 => GPIO18
  0x18,         // GEVENT15 => GPIO24
  0x17,         // GEVENT16 => GPIO23
  0x45,         // GEVENT17 => GPIO69
  0x0B,         // GEVENT18 => GPIO11
  0x01,         // GEVENT19 => GPIO1
  0x0F,         // GEVENT20 => GPIO15
  0x0D,         // GEVENT21 => GPIO13
  0x09,         // GEVENT22 => GPIO9
  0x08          // GEVENT23 => GPIO8
};

UINT8 FchGeventGpioMappingTableZP[] = {
  0x59,         // GEVENT0 => GPIO89
  0x5A,         // GEVENT1 => GPIO90
  0x03,         // GEVENT2 => GPIO3
  0x16,         // GEVENT3 => GPIO22
  0x04,         // GEVENT4 => GPIO4
  0x15,         // GEVENT5 => GPIO21
  0x5B,         // GEVENT6 => GPIO91
  0x05,         // GEVENT7 => GPIO5
  0x02,         // GEVENT8 => GPIO2
  0x56,         // GEVENT9 => GPIO86
  0x06,         // GEVENT10 => GPIO6
  0x4C,         // GEVENT11 => GPIO7      // ZP & SSP & MTS = GPIO76
  0x10,         // GEVENT12 => GPIO16
  0x11,         // GEVENT13 => GPIO17
  0x12,         // GEVENT14 => GPIO18
  0x18,         // GEVENT15 => GPIO24
  0x17,         // GEVENT16 => GPIO23
  0x81,         // GEVENT17 => GPIO129
  0x54,         // GEVENT18 => GPIO84
  0x01,         // GEVENT19 => GPIO1
  0x28,         // GEVENT20 => GPIO40
  0x00,         // GEVENT21 => GPIO0
  0x09,         // GEVENT22 => GPIO9
  0x08          // GEVENT23 => GPIO8
};

UINT8 FchGeventGpioMappingTableRV[] = {
  0x59,         // GEVENT0 => GPIO89
  0x5A,         // GEVENT1 => GPIO90
  0x03,         // GEVENT2 => GPIO3
  0x16,         // GEVENT3 => GPIO22
  0x04,         // GEVENT4 => GPIO4
  0x15,         // GEVENT5 => GPIO21
  0x5B,         // GEVENT6 => GPIO91
  0x05,         // GEVENT7 => GPIO5
  0x02,         // GEVENT8 => GPIO2
  0x56,         // GEVENT9 => GPIO86
  0x06,         // GEVENT10 => GPIO6
  0x07,         // GEVENT11 => GPIO7
  0x10,         // GEVENT12 => GPIO16
  0x11,         // GEVENT13 => GPIO17
  0x12,         // GEVENT14 => GPIO18
  0x18,         // GEVENT15 => GPIO24
  0x17,         // GEVENT16 => GPIO23
  0x81,         // GEVENT17 => GPIO129
  0x54,         // GEVENT18 => GPIO84
  0x01,         // GEVENT19 => GPIO1
  0x28,         // GEVENT20 => GPIO40
  0x00,         // GEVENT21 => GPIO0
  0x09,         // GEVENT22 => GPIO9
  0x08          // GEVENT23 => GPIO8
};

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of FCH GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number
 *
 * @retval    The State of GPIO Pin
 *
 */
UINT8
CpmFchGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   Value;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  Value = 0;
  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
  case CPM_FCH_REVISION_ID_KB:
    Value = ((CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + GPIO_BASE + Pin)) & 0x80) == 0x80);
    break;
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    Value = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + GPIO_BANK_BASE + (Pin << 2) + 2)) & 0x01;
    break;
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Pin = GPIO%d, PinStatus = 0x%02X\n", __FUNCTION__, Pin, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of KBC GPIO Pin on reference board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number
 *
 * @retval    The State of GPIO Pin
 *
 */
UINT8
CpmKbcGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   Data;
  UINT8                   PinNum;
  EFI_STATUS              Status;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  PinNum              = (UINT8) Pin;
  if (MainTablePtr->KbcSupport) {
    Status = CommonFunctionPtr->KbcRead (0x60, 0xA1, &PinNum, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Pin = GPIO%d\n", __FUNCTION__, Pin));
      CPM_DEADLOOP ();
    }
  } else {
    Data = 0xFF;
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Pin = GPIO%d, PinStatus = %X\n", __FUNCTION__, Pin, (Data >> 7)));
  return ((Data & 0x80) == 0x80);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of ECRAM GPIO Pin on reference board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number
 *
 * @retval    The State of GPIO Pin
 *
 */
UINT8
CpmEcRamGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   Data;
  UINT8                   PinNum;
  UINT8                   Offset;
  EFI_STATUS              Status;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  PinNum              = (UINT8)Pin;
  Offset              = CFG_CPM_ECRAM_GPIO_OFFSET + 1 + (PinNum >> 3);
  if (MainTablePtr->EcSupport) {
    Status = CommonFunctionPtr->KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Pin = GPIO%d\n", __FUNCTION__, Pin));
      CPM_DEADLOOP ();
    }
  } else {
    Data = 0xFF;
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Pin = GPIO%d, PinStatus = %X\n", __FUNCTION__, Pin, ((Data >> (PinNum & 0x07)) & 0x01)));
  return ((Data >> (PinNum & 0x07)) & 0x01);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of Promontory GPIO Pin on reference board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number
 *
 * @retval    The State of GPIO Pin
 *
 */
UINT8
CpmPtGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT32                  BridgeAddress;
  UINT32                  DeviceAddress;
  UINT32                  PtGpioMmio;
  UINT8                   Bus;
  UINT8                   BusSec;
  UINT8                   BridgeCommand;
  UINT8                   DeviceCommand;
  UINT8                   Data;

  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr      = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  BridgeAddress     = (UINT32)MainTablePtr->PtBrMemIoBaseAddr;

  Data = 0;
  if (BridgeAddress != 0) {
    Bus = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x19);              // PT Bridge Offset 0x19
    BusSec = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x1A);           // PT Bridge Offset 0x1A

    if (Bus != 0xFF) {
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x19, PtTempBus);      // PT Bridge Offset 0x19
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x1A, PtTempBus);      // PT Bridge Offset 0x1A
      DeviceAddress = (UINT32)(MainTablePtr->PcieMemIoBaseAddr + (PtTempBus << 20) + (PtGpioFun << 12));

      BridgeCommand = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x04);  // PT Bridge Offset 0x04
      DeviceCommand = CommonFunctionPtr->MmioRead8 (DeviceAddress + 0x04);  // PT GPIO Device Offset 0x04

      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x04, 0x07);           // PT Bridge Offset 0x04
      CommonFunctionPtr->MmioWrite8 (DeviceAddress + 0x04, 0x06);           // PT GPIO Device Offset 0x04

      PtGpioMmio = CommonFunctionPtr->MmioRead32 (DeviceAddress + 0x40) & ~(UINT32)BIT2;    // PT GPIO Device Offset 0x40

      Data = CommonFunctionPtr->MmioRead8 (PtGpioMmio);                                     // PT GPIO MMIO Offset 0x00
      if ((Data & (UINT8)(1 << Pin)) == (UINT8)(1 << Pin)) {
        CommonFunctionPtr->MmioWrite8 (PtGpioMmio, (Data & ~(UINT8)(1 << Pin)));            // PT GPIO MMIO Offset 0x00
      }

      Data = (CommonFunctionPtr->MmioRead8 (PtGpioMmio + 0x04) & (UINT8)(1 << Pin)) >> Pin; // PT GPIO MMIO Offset 0x04

      CommonFunctionPtr->MmioWrite8 (DeviceAddress + 0x04, DeviceCommand);  // PT GPIO Device Offset 0x04
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x04, BridgeCommand);  // PT Bridge Offset 0x04
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x19, Bus);            // PT Bridge Offset 0x19
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x1A, BusSec);         // PT Bridge Offset 0x1A
    }
  }

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-BridgeAddress = 0x%08X Pin = 0x%04X Data = 0x%02X\n", __FUNCTION__, BridgeAddress, Pin, Data));
  return Data;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Multi Socket/Die FCH GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Socket  The Socket Number.
 * @param[in] Die     The Die Number.
 * @param[in] Bridge  The Bridge Number.
 * @param[in] Pin     The GPIO Pin Number.
 *
 * @retval            The State of GPIO Pin.
 *
 */
UINT8
CpmSmnGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT16                      Pin
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   Value;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  Value = 0;

  Value = CommonFunctionPtr->SmnRead8 (This, Socket, Die, Bridge, (UINT32) FchSmnGpio, (UINT32) ((Pin << 2) + 2)) & 0x01;
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Socket = 0x%04X Die = 0x%04X Bridge = 0x%04X", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " Pin = GPIO%d PinStatus = %X\n", Pin, Value));
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 *                      [0x0000: 0x00FF]: FCH GPIO Pin
 *                      [0x0100: 0x01FF]: KBC GPIO Pin on Reference Board
 *                      [0x0200: 0x02FF]: ECRAM GPIO Pin on Reference Board
 *                      [0x0300: 0x03FF]: Promontory GPIO Pin
 * For Multi Socket/Die FCH GPIO Pin
 *                      BIT[15]:          Multi Socket Number
 *                      BIT[14:13]:       Multi Die Number
 *                      BIT[12:11]:       Multi Bridge Number
 *                      BIT[10:8]:        Keep it "0"
 *                      BIT[7:0]:         GPIO Pin Number
 *                      [0x0200: 0x07FF]: Reserved
 *
 * @retval    The State of GPIO Pin
 *
 */
UINT8
CpmGetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin
  )
{
  UINT16  Select;
  UINT16  PinNum;
  UINT8   Value;

  Select = Pin >> 8;
  PinNum = Pin & 0xFF;
  Value = 0;
  switch (Select) {
  case 0:
    Value = CpmFchGetGpio (This, PinNum);
    break;
  case 1:
    Value = CpmKbcGetGpio (This, PinNum);
    break;
  case 2:
    Value = CpmEcRamGetGpio (This, PinNum);
    break;
  case 3:
    Value = CpmPtGetGpio (This, PinNum);
    break;
  default:
    Value = CpmSmnGetGpio (This, (UINT16) ((Pin & 0x8000) >> 15), (UINT16) ((Pin & 0x6000) >> 13), (UINT16) ((Pin & 0x1800) >> 11), PinNum);
    break;
  }
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set FCH GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 * @param[in] Value   The Setting of GPIO Pin. See Definition of AMD_CPM_GPIO_SETTING
 *
 */
VOID
CpmFchSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_GPIO_SETTING    GpioPin;
  UINT8                   temp;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-Pin = GPIO%d, Value = 0x%04X\n", Pin, Value));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  GpioPin.Raw = Value;

  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
  case CPM_FCH_REVISION_ID_KB:
    temp = CommonFunctionPtr->MmioRead8 ((UINT32) (MainTablePtr->AcpiMemIoBaseAddr + GPIO_BASE + Pin));
    if (GpioPin.Gpio.PresetEn) {
      temp = (temp & 0xE3) | 0x08;
      if (GpioPin.Gpio.Sticky) {
        temp |= 0x04;
      }
      if (GpioPin.Gpio.PullUp) {
        temp &= 0xF7;
      }
      if (GpioPin.Gpio.PullDown) {
        temp |= 0x10;
      }
    }
    if (GpioPin.Gpio.SetEnB == 0) {
      if (GpioPin.Gpio.OutEnB == 0) {
        temp &= 0x9F;
        if (GpioPin.Gpio.Out) {
          temp |= 0x40;
        }
      } else {
        temp |= 0x20;
      }
    }
    CommonFunctionPtr->MmioWrite8 ((UINT32) (MainTablePtr->AcpiMemIoBaseAddr + GPIO_BASE + Pin), temp);
    break;
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    temp = CommonFunctionPtr->MmioRead8 ((UINT32) (MainTablePtr->AcpiMemIoBaseAddr + GPIO_BANK_BASE + (Pin << 2) + 2));
    if (GpioPin.Gpio.PresetEn) {
      temp = temp & 0xC7;
      if (GpioPin.Gpio.PullUpSel) {
        temp |= 0x08;
      }
      if (GpioPin.Gpio.PullUp) {
        temp |= 0x10;
      }
      if (GpioPin.Gpio.PullDown) {
        temp |= 0x20;
      }
    }
    if (GpioPin.Gpio.SetEnB == 0) {
      if (GpioPin.Gpio.OutEnB == 0) {
        temp |= 0x80;
        if (GpioPin.Gpio.Out) {
          temp |= 0x40;
        } else {
          temp &= 0xBF;
        }
      } else {
        temp &= 0x7F;
      }
    }
    CommonFunctionPtr->MmioWrite8 ((UINT32) (MainTablePtr->AcpiMemIoBaseAddr + GPIO_BANK_BASE + (Pin << 2) + 2), temp);
    break;
  }

  if (GpioPin.Gpio.IoMuxEn) {
    CommonFunctionPtr->MmioWrite8 ((UINT32) (MainTablePtr->AcpiMemIoBaseAddr + IOMUX_BASE + Pin), (UINT8) GpioPin.Gpio.IoMux);
  }
}


/*---------------------------------------------------------------------------------------*/
/**
 * Set KBC GPIO Pin on Reference Board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 * @param[in] Value   The Setting of GPIO Pin. 0: Low. 1: High
 *
 */
VOID
CpmKbcSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   PinNum;
  EFI_STATUS              Status;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-Pin = GPIO%d, Value = 0x%04X\n", Pin, Value));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  PinNum              = (UINT8) (Pin & 0x7F) | (Value == 1 ? 0x80: 0);
  if (MainTablePtr->KbcSupport) {
    Status = CommonFunctionPtr->KbcWrite (0x60, 0xAF, &PinNum);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Pin = GPIO%d Value = 0x%04X\n", __FUNCTION__, Pin, Value));
      CPM_DEADLOOP ();
    }
    DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Pin = GPIO%d, Value = 0x%04X\n", __FUNCTION__, Pin, Value));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set ECRAM GPIO Pin on Reference Board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 * @param[in] Value   The Setting of GPIO Pin. 0: Low. 1: High
 *
 */
VOID
CpmEcRamSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   PinNum;
  UINT8                   Offset;
  UINT8                   Data;
  UINT8                   Mask;
  EFI_STATUS              Status;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-Pin = GPIO%d, Value = 0x%04X\n", Pin, Value));
  Status = EFI_SUCCESS;
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  PinNum              = (UINT8)Pin;
  Offset              = CFG_CPM_ECRAM_GPIO_OFFSET + 1 + (PinNum >> 3);
  Mask                = 0x01 << (PinNum & 0x07);
  if (MainTablePtr->EcSupport) {
    Status = CpmKbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Data);
    if (EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Pin = GPIO%d Value = 0x%04X\n", __FUNCTION__, Pin, Value));
      CPM_DEADLOOP ();
    }
    Data = (Data & (0xFF ^ Mask)) | (((UINT8)Value & 0x01) << (PinNum & 0x07));
    Status = CpmEcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Data);
    DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-Pin = GPIO%d, Value = 0x%04X\n", __FUNCTION__, Pin, Value));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set Promontory GPIO Pin on Reference Board
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 * @param[in] Value   The Setting of GPIO Pin. 0: Low. 1: High
 *
 */
VOID
CpmPtSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT32                  BridgeAddress;
  UINT32                  DeviceAddress;
  UINT32                  PtGpioMmio;
  UINT8                   Bus;
  UINT8                   BusSec;
  UINT8                   BridgeCommand;
  UINT8                   DeviceCommand;
  UINT8                   Data;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-Pin = GPIO%d, Value = 0x%04X\n", Pin, Value));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  BridgeAddress       = (UINT32)MainTablePtr->PtBrMemIoBaseAddr;

  if (BridgeAddress != 0) {
    Bus = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x19);              // PT Bridge Offset 0x19
    BusSec = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x1A);           // PT Bridge Offset 0x1A

    if (Bus != 0xFF) {
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x19, PtTempBus);      // PT Bridge Offset 0x19
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x1A, PtTempBus);      // PT Bridge Offset 0x1A
      DeviceAddress = (UINT32)(MainTablePtr->PcieMemIoBaseAddr + (PtTempBus << 20) + (PtGpioFun << 12));

      BridgeCommand = CommonFunctionPtr->MmioRead8 (BridgeAddress + 0x04);  // PT Bridge Offset 0x04
      DeviceCommand = CommonFunctionPtr->MmioRead8 (DeviceAddress + 0x04);  // PT GPIO Device Offset 0x04

      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x04, 0x07);           // PT Bridge Offset 0x04
      CommonFunctionPtr->MmioWrite8 (DeviceAddress + 0x04, 0x06);           // PT GPIO Device Offset 0x04

      PtGpioMmio = CommonFunctionPtr->MmioRead32 (DeviceAddress + 0x40) & ~(UINT32)BIT2;  // PT GPIO Device Offset 0x40

      Data = CommonFunctionPtr->MmioRead8 (PtGpioMmio);                                   // PT GPIO MMIO Offset 0x00
      if ((Data & (UINT8)(1 << Pin)) != (UINT8)(1 << Pin)) {
        CommonFunctionPtr->MmioWrite8 (PtGpioMmio, (Data | (UINT8)(1 << Pin)));           // PT GPIO MMIO Offset 0x00
      }

      Data = CommonFunctionPtr->MmioRead8 (PtGpioMmio + 0x08) & ~(UINT8)(1 << Pin);       // PT GPIO MMIO Offset 0x08
      CommonFunctionPtr->MmioWrite8 ((PtGpioMmio + 0x08), (Data | (UINT8)(Value << Pin)));// PT GPIO MMIO Offset 0x08

      CommonFunctionPtr->MmioWrite8 (DeviceAddress + 0x04, DeviceCommand);  // PT GPIO Device Offset 0x04
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x04, BridgeCommand);  // PT Bridge Offset 0x04
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x19, Bus);            // PT Bridge Offset 0x19
      CommonFunctionPtr->MmioWrite8 (BridgeAddress + 0x1A, BusSec);         // PT Bridge Offset 0x1A
    }
    DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-BridgeAddress = 0x%08X Pin = GPIO%d, Value = 0x%04X\n", __FUNCTION__, BridgeAddress, Pin, Value));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set Multi Socket/Die FCH GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Socket  The Socket Number.
 * @param[in] Die     The Die Number.
 * @param[in] Bridge  The Bridge Number.
 * @param[in] Pin     The GPIO Pin Number.
 * @param[in] Value   The Setting of GPIO Pin. See Definition of AMD_CPM_GPIO_SETTING
 *
 */
VOID
CpmSmnSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Socket,
  IN       UINT16                      Die,
  IN       UINT16                      Bridge,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_GPIO_SETTING    GpioPin;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   temp;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start", __FUNCTION__));
  DEBUG((DEBUG_INFO, "-Socket = 0x%04X, Die = 0x%04X, Pin = GPIO%d, Value = 0x%04X\n", Socket, Die, Pin, Value));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  GpioPin.Raw = Value;

  temp = CommonFunctionPtr->SmnRead8 (This, Socket, Die, Bridge, (UINT32) FchSmnGpio, (UINT32) ((Pin << 2) + 2));
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-SmnRead8 (0x%04X, 0x%04X, 0x%04X,", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " 0x%08X, 0x%08X) = 0x%02X\n", (UINT32) FchSmnGpio, (UINT32) ((Pin << 2) + 2), temp));
  if (GpioPin.Gpio.PresetEn) {
    temp = temp & 0xC7;
    if (GpioPin.Gpio.PullUpSel) {
      temp |= 0x08;
    }
    if (GpioPin.Gpio.PullUp) {
      temp |= 0x10;
    }
    if (GpioPin.Gpio.PullDown) {
      temp |= 0x20;
    }
  }
  if (GpioPin.Gpio.SetEnB == 0) {
    if (GpioPin.Gpio.OutEnB == 0) {
      temp |= 0x80;
      if (GpioPin.Gpio.Out) {
        temp |= 0x40;
      } else {
        temp &= 0xBF;
      }
    } else {
      temp &= 0x7F;
    }
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-SmnWrite8 (0x%04X, 0x%04X, 0x%04X,", __FUNCTION__, Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " 0x%08X, 0x%08X, 0x%02X)\n", (UINT32) FchSmnGpio, (UINT32) ((Pin << 2) + 2), temp));
  CommonFunctionPtr->SmnWrite8 (This, Socket, Die, Bridge, (UINT32) FchSmnGpio, (UINT32) ((Pin << 2) + 2), temp);

  if (GpioPin.Gpio.IoMuxEn) {
    DEBUG((DEBUG_INFO, "  LIB-FCH-%a-GpioPin.Gpio.IoMuxEn = 0x%02X, GpioPin.Gpio.IoMux = 0x%02X\n", __FUNCTION__, (UINT8) GpioPin.Gpio.IoMuxEn, (UINT8) GpioPin.Gpio.IoMux));
    DEBUG((DEBUG_INFO, "  LIB-FCH-%a-SmnWrite8 (0x%04X, 0x%04X, 0x%04X,", __FUNCTION__, Socket, Die, Bridge));
    DEBUG((DEBUG_INFO, " 0x%08X, 0x%08X, 0x%02X)\n", (UINT32) FchSmnIomux, (UINT32) Pin, (UINT8) GpioPin.Gpio.IoMux));
    CommonFunctionPtr->SmnWrite8 (This, Socket, Die, Bridge, (UINT32) FchSmnIomux, (UINT32) Pin, (UINT8) GpioPin.Gpio.IoMux);
  }

}


/*---------------------------------------------------------------------------------------*/
/**
 * Set GPIO Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GPIO Pin Number.
 *                      [0x0000: 0x00FF]: FCH GPIO Pin
 *                      [0x0100: 0x01FF]: KBC GPIO Pin on Reference Board
 *                      [0x0200: 0x02FF]: ECRAM GPIO Pin on Reference Board
 *                      [0x0300: 0x03FF]: Promontory GPIO Pin
 * For Multi Socket/Die FCH GPIO Pin
 *                      BIT[15]:          Multi Socket Number
 *                      BIT[14:13]:       Multi Die Number
 *                      BIT[12:11]:       Multi Bridge Number
 *                      BIT[10:8]:        Keep it "0"
 *                      BIT[7:0]:         GPIO Pin Number
 *                      [0x0200: 0x07FF]: Reserved
 * @param[in] Value   The Setting of GPIO Pin.
 *
 */
VOID
CpmSetGpio (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  UINT16  Select;
  UINT16  PinNum;

  Select = Pin >> 8;
  PinNum = Pin & 0xFF;

  switch (Select) {
  case 0:
    CpmFchSetGpio (This, PinNum, Value);
    break;
  case 1:
    CpmKbcSetGpio (This, PinNum, Value);
    break;
  case 2:
    CpmEcRamSetGpio (This, PinNum, Value);
    break;
  case 3:
    CpmPtSetGpio (This, PinNum, Value);
    break;
  default:
    CpmSmnSetGpio (This, (UINT16) ((Pin & 0x8000) >> 15), (UINT16) ((Pin & 0x6000) >> 13), (UINT16) ((Pin & 0x1800) >> 11), PinNum, Value);
    break;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the State of GEVENT Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GEVENT Pin Number.
 *
 * @retval    The State of GEVENT Pin
 *
 */
UINT8
CpmGetGevent (
  IN       VOID                        *This,
  IN       UINT8                       Pin
  )
{
  UINT8   Value;
  Value = 0;
  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
  case CPM_FCH_REVISION_ID_KB:
    Value = CpmGetGpio (This, Pin + 0x60);
    break;
  case CPM_FCH_REVISION_ID_ML:
    Value = 0;
    if (Pin <= 22) {
      Value = CpmGetGpio (This, FchGeventGpioMappingTable[Pin]);
    }
    break;
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
    Value = 0;
    if (Pin <= 23) {
      Value = CpmGetGpio (This, FchGeventGpioMappingTable2[Pin]);
    }
    break;
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    Value = 0;
    if (Pin <= 23) {
      Value = CpmGetGpio (This, FchGeventGpioMappingTableZP[Pin]);
    }
    break;
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
    Value = 0;
    if (Pin <= 23) {
      Value = CpmGetGpio (This, FchGeventGpioMappingTableRV[Pin]);
    }
    break;
  }
  return Value;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set the State of GEVENT Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GEVENT Pin Number.
 * @param[in] Value   The Setting of GEVENT Pin. See Definition of AMD_CPM_GEVENT_SETTING
 *
 */
VOID
CpmSetGevent (
  IN       VOID                        *This,
  IN       UINT16                      Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_GEVENT_SETTING  GeventPin;
  UINT32                  andMask32;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT16                  SciMap;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  GeventPin.Raw = Value;

  if (Pin < 0x40) {
    SciMap = GeventPin.Gevent.SciMap;
    andMask32 = ~(1 << SciMap);

    //EventEnable: 0-Disable, 1-Enable.
    if (GeventPin.Gevent.EventEnable) {
      if (GeventPin.Gevent.SciTrigAuto) {
        //SciTrig: 0-Falling Edge, 1-Rising Edge.
        CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCITRIG),
                                                andMask32,
                                                (CommonFunctionPtr->GetGevent (This, (UINT8) Pin) ? 0 : 1) << SciMap);
      } else {
        //SciTrig: 0-Falling Edge, 1-Rising Edge.
        CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCITRIG),
                                                andMask32,
                                                GeventPin.Gevent.SciTrig << SciMap);
      }

      //SciLevl: 0-Edge trigger, 1-Level Trigger.
      CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCILEVEL),
                                              andMask32,
                                              GeventPin.Gevent.SciLevl << SciMap);

      //SmiSciEn: 0-Not send SMI, 1-Send SMI
      CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SMISCIEN),
                                              andMask32,
                                              GeventPin.Gevent.SmiSciEn << SciMap);

      //SciS0En: 0-Disable, 1-Enable
      CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCIS0EN),
                                              andMask32,
                                              GeventPin.Gevent.SciS0En << SciMap);

      //SciMap: 00000b ~ 11111b.
      CommonFunctionPtr->MmioAndThenOr8 (     (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCIMAP0 + Pin),
                                              (UINT8)AMD_GEVENT_SCIMASK,
                                              (UINT8)GeventPin.Gevent.SciMap);

      if (Pin < 24) {
        //SmiTrig: 0-Active Low, 1-Active High.
        CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SMITRIG),
                                                ~(1 << Pin),
                                                GeventPin.Gevent.SmiTrig << Pin);
      }

      //SmiControl: 0-Disable, 1-SMI, 2-NMI, 3-IRQ13
      CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SMICONTROL0 + Pin / 4),
                                              ~(AMD_SMICONTROL_MASK << ((Pin & 0x3) * 2)),
                                              GeventPin.Gevent.SmiControl << ((Pin & 0x3) * 2));
    }
  } else if ((Pin & 0xFF00) == 0x0100) {
    CommonFunctionPtr->MmioWrite16 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + GPIO_BANK_BASE + ((Pin & 0xFF) << 2)), Value);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set SMI Control for GEVENT Pin
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GEVENT Pin Number.
 * @param[in] Value   The Setting of GEVENT Pin. See Definition of AMD_CPM_GEVENT_SETTING
 *
 */
VOID
CpmSetSmiControl (
  IN       VOID                        *This,
  IN       UINT8                       Pin,
  IN       UINT16                      Value
  )
{
  AMD_CPM_GEVENT_SETTING  GeventPin;
  UINT32                  andMask32;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT16                  SciMap;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  GeventPin.Raw = Value;

  if (Pin < 0x40) {
    SciMap = GeventPin.Gevent.SciMap;
    andMask32 = ~(1 << Pin);

    //SmiControl: 0-Disable, 1-SMI, 2-NMI, 3-IRQ13
    CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SMICONTROL0 + Pin / 4),
                                            ~(AMD_SMICONTROL_MASK << ((Pin & 0x3) * 2)),
                                            GeventPin.Gevent.SmiControl << ((Pin & 0x3) * 2));
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set the way to set corresponding bit in Event Status
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GEVENT Pin Number.
 * @param[in] Value   The bit controls the way to set Event Status.
 *                      0: Active Low. 1: Active High
 *
 */
VOID
CpmSetGeventSciTrig (
  IN       VOID                        *This,
  IN       UINT8                       Pin,
  IN       UINT8                       Value
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT32                  andMask32;
  UINT8                   SciMap;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  SciMap = CommonFunctionPtr->GetSciMap (This, Pin);
  andMask32 = ~(1 << SciMap);
  CommonFunctionPtr->MmioAndThenOr32 (    (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SCITRIG),
                                          andMask32,
                                          Value << SciMap);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Trigger a GEVENT SCI interrupt
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Pin     The GEVENT Pin Number.
 *
 */
VOID
CpmSetGeventSci (
  IN       VOID                        *This,
  IN       UINT8                       Pin
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   SciMap;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  SciMap = CommonFunctionPtr->GetSciMap (This, Pin);
  CommonFunctionPtr->MmioOr32 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SWSCIEN), 1 << SciMap);
  CommonFunctionPtr->MmioWrite32 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SWSCIDATA), 1 << SciMap);
  CommonFunctionPtr->MmioWrite32 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SWSCIDATA), 0);
  CommonFunctionPtr->MmioWrite32 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + AMD_SMIREG_SWSCIEN), 0);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get FCH Revision Id
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The FCH Revision Id
 *
 */
UINT8
CpmGetFchRevisionId (
  IN       VOID                        *This
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   FchRevision;
  UINT8                   CpuRevision;
  UINT32                  Data;
  UINT8                   FchSmbusRevision;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start\n", __FUNCTION__));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  CpuRevision         = CommonFunctionPtr->GetCpuRevisionId (This);
  FchRevision         = CPM_FCH_REVISION_ID_DEFAULT;
  FchSmbusRevision    = 0;
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CpuRevision = 0x%02X\n", __FUNCTION__, CpuRevision));
  switch (CpuRevision) {
  case CPM_CPU_REVISION_ID_KB:
    FchRevision = CPM_FCH_REVISION_ID_KB;
    break;
  case CPM_CPU_REVISION_ID_ML:
    FchRevision = CPM_FCH_REVISION_ID_ML;
    break;
  case CPM_CPU_REVISION_ID_CZ:
    CommonFunctionPtr->CpuidRead (This, NULL, &Data);
    if (Data != 0x00000003) {
      FchRevision = CPM_FCH_REVISION_ID_CZ;
    } else {
      FchSmbusRevision = CommonFunctionPtr->PciRead8 (This, 0, 0x14, 0, 0x08);
      if ((FchSmbusRevision < 0x11) || (FchSmbusRevision > 0x16)) {
        FchRevision = CPM_FCH_REVISION_ID_CZ;
      }
    }
    break;
  case CPM_CPU_REVISION_ID_NL:
    FchRevision = CPM_FCH_REVISION_ID_NL;
    break;
  case CPM_CPU_REVISION_ID_AM:
    FchRevision = CPM_FCH_REVISION_ID_AM;
    break;
  case CPM_CPU_REVISION_ID_ST:
    CommonFunctionPtr->CpuidRead (This, NULL, &Data);
    if (Data != 0x00000003) {
      FchRevision = CPM_FCH_REVISION_ID_ST;
    }
    break;
  case CPM_CPU_REVISION_ID_BR:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_BR\n"));
    FchRevision = CPM_FCH_REVISION_ID_BR;
    break;
  case CPM_CPU_REVISION_ID_ZP:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_ZP\n"));
    FchRevision = CPM_FCH_REVISION_ID_ZP;
    break;
  case CPM_CPU_REVISION_ID_RV:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_RV\n"));
    FchRevision = CPM_FCH_REVISION_ID_RV;
    break;
  case CPM_CPU_REVISION_ID_RV2:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_RV2\n"));
    FchRevision = CPM_FCH_REVISION_ID_RV2;
    break;
  case CPM_CPU_REVISION_ID_SSP:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_SSP\n"));
    FchRevision = CPM_FCH_REVISION_ID_SSP;
    break;
  case CPM_CPU_REVISION_ID_MTS:
    DEBUG((DEBUG_INFO, "  case CPM_CPU_REVISION_ID_MTS\n"));
    FchRevision = CPM_FCH_REVISION_ID_MTS;
    break;
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End-FchRevision = 0x%02X\n", __FUNCTION__, FchRevision));
  return FchRevision;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get FCH Strap Setting
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The State of FCH Strap Pin
 *              BIT0: ImcEnableStrap: 0: Disable. 1: Enable
 *              BIT1: ClkGenStrap: 0: External. 1: Internal
 *              BIT2: S5+ Support: 0: Disable. 1: Enable
 *
 */
UINT32
CpmGetStrap (
  IN       VOID                        *This
  )
{
  UINT8                   StrapStatus;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT32                  StrapValue;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  StrapValue = 0;
  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
    StrapStatus = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x80));
    StrapValue |= ((StrapStatus & BIT2) >> 2) | ((StrapStatus & BIT4) >> 3);
    StrapStatus = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x82));
    StrapValue |= StrapStatus & BIT2;
    break;
  case CPM_FCH_REVISION_ID_KB:
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    StrapStatus = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x80));
    StrapValue |= (StrapStatus & BIT2) >> 2;
    StrapStatus = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x82));
    StrapValue |= StrapStatus & BIT1;
    break;
  }
  return StrapValue;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set FCH ClkReq
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Socket  CPU Socket Number
 * @param[in] Die     CPU Die Number
 * @param[in] Bridge  CPU Bridge Number
 * @param[in] Miscid  Select MISC or MISC2 clkreq mapping
 * @param[in] ClkId   PCIE Clock Pin Number
 * @param[in] ClkReq  ClkReq Mapping
 *
 */
VOID
CpmSetClkReq (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Miscid,
  IN       UINT8                       ClkId,
  IN       UINT8                       ClkReq
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   AndData;
  UINT8                   OrData;

  DEBUG((DEBUG_INFO, "  LIB-FCH-CpmSetClkReq-Start-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " Miscid = 0x%02X ClkId = 0x%02X ClkReq = 0x%02X\n", Miscid, ClkId, ClkReq));
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
    if (ClkId <= 9) {
      CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + (ClkId >> 1)),
                                          0x0F << (ClkId % 2 ? 0: 4),
                                          ClkReq << (ClkId % 2 ? 4: 0)
                                          );
    } else {
      switch (ClkId) {
      case CPM_CLKID_APU_CLK:
      case CPM_CLKID_DISP2_CLK:
      case CPM_CLKID_PCIE_RCLK_OUTPUT:
      case CPM_CLKID_DISP_CLK:
        CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x05),
                                        0xFE ^ (1 << ((ClkId & 0x7F) + 1)),
                                        0x01 | ((ClkReq ? 0 : 1) << ((ClkId & 0x7F) + 1))
                                        );
        break;
      case CPM_CLKID_PCIE_RCLK:
        CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x05),
                                        0xDF,
                                        ClkReq ? 0 : 0x20
                                        );
        break;
      case CPM_CLKID_CLOCK_BUFFER_BIAS:
        CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x06),
                                        0xFE,
                                        ClkReq ? 0 : 1
                                        );
        break;
      case CPM_CLKID_OSCOUT2_OUTOFF:
        CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x40),
                                        0x7F,
                                        ClkReq ? 0 : 0x80
                                        );
        break;
      }
    }
    break;
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_KB:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
    if (ClkId <= 3 || ClkId == 9) {
      AndData = ~(UINT8) (0x0F << ((ClkId & 1) * 4));
      OrData = (UINT8) ((ClkReq & 0x0F) << ((ClkId & 1) * 4));
      DEBUG((DEBUG_INFO, "  LIB-FCH-CpmSetClkReq-MmioAndThenOr8 (0x%08X, 0x%02X, 0x%02X)\n", (UINT32) (MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + (ClkId >> 1)), AndData, OrData));
      CommonFunctionPtr->MmioAndThenOr8 ( (UINT32) (MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + (ClkId >> 1)), AndData, OrData);
    } else if (ClkId == CPM_CLKID_PCIE_RCLK) {
      AndData = 0xDF;
      OrData = (UINT8) (ClkReq ? 0 : 0x20);
      DEBUG((DEBUG_INFO, "  LIB-FCH-CpmSetClkReq-MmioAndThenOr8 (0x%08X, 0x%02X, 0x%02X)\n", (UINT32) (MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x05), AndData, OrData));
      CommonFunctionPtr->MmioAndThenOr8 ( (UINT32) (MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x05), AndData, OrData);
    }
    break;
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
    if (ClkId <= 2) {
      CommonFunctionPtr->MmioAndThenOr8 ( (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + MISC_BASE + 0x00),
                                        0x03 << (ClkId * 2),
                                        (ClkReq == 0xFF ? 0x03 : ClkReq) << (ClkId * 2)
                                        );
    }
    break;
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    AndData = ~(UINT8) (0x03 << ((ClkId & 3) * 2));
    OrData = (UINT8) ((ClkReq == 0 ? 0: (ClkReq == 0xFF ? 3: 1)) << ((ClkId & 3) * 2));
    if (Miscid == 0x02) {
      DEBUG((DEBUG_INFO, "  LIB-FCH-CpmSetClkReq-SmnAndThenOr8 (0x%X, 0x%X, 0x%X,", Socket, Die, Bridge));
      DEBUG((DEBUG_INFO, " 0x%X, 0x%X, 0x%X, 0x%X)\n", FchSmnMisc2, (ClkId >> 2), AndData, OrData));
      CommonFunctionPtr->SmnAndThenOr8 (This, Socket, Die, Bridge, FchSmnMisc2, (ClkId >> 2), AndData, OrData);
    } else {
      DEBUG((DEBUG_INFO, "  LIB-FCH-CpmSetClkReq-SmnAndThenOr8 (0x%X, 0x%X, 0x%X,", Socket, Die, Bridge));
      DEBUG((DEBUG_INFO, " 0x%X, 0x%X, 0x%X, 0x%X)\n", FchSmnMisc, (ClkId >> 2), AndData, OrData));
      CommonFunctionPtr->SmnAndThenOr8 (This, Socket, Die, Bridge, FchSmnMisc, (ClkId >> 2), AndData, OrData);
    }
    break;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get FCH ClkReq
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Socket  CPU Socket Number
 * @param[in] Die     CPU Die Number
 * @param[in] Bridge  CPU Bridge Number
 * @param[in] Miscid  Select MISC or MISC2 clkreq mapping
 * @param[in] ClkId   PCIE Clock Pin Number
 *
 * @retval    ClkReq  ClkReq Mapping
 *
 */
UINT8
CpmGetClkReq (
  IN       VOID                        *This,
  IN       UINT8                       Socket,
  IN       UINT8                       Die,
  IN       UINT8                       Bridge,
  IN       UINT8                       Miscid,
  IN       UINT8                       ClkId
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   ClkReq = 0xFF;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  switch (((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb) {
  case CPM_FCH_REVISION_ID_DEFAULT:
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_KB:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
    ClkReq = 3;
    break;
  case CPM_FCH_REVISION_ID_ZP:
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    if (Miscid == 0x02) {
      ClkReq = (CommonFunctionPtr->SmnRead8 (This, Socket, Die, Bridge, FchSmnMisc2, (ClkId >> 2)) >> ((ClkId & 3) * 2)) & 3;
    } else {
      ClkReq = (CommonFunctionPtr->SmnRead8 (This, Socket, Die, Bridge, FchSmnMisc, (ClkId >> 2)) >> ((ClkId & 3) * 2)) & 3;
    }
    break;
  }
  DEBUG((DEBUG_INFO, "  LIB-FCH-CpmGetClkReq-End-Socket = 0x%02X Die = 0x%02X Bridge = 0x%02X", Socket, Die, Bridge));
  DEBUG((DEBUG_INFO, " Miscid = 0x%02X ClkId = 0x%02X ClkReq = 0x%02X\n", Miscid, ClkId, ClkReq));
  return ClkReq;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Add some delay in 1us/unit
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Delay   Delay in 1us/unit
 *
 */
VOID
CpmStall (
  IN       VOID                        *This,
  IN       UINT32                      Delay
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT16 timerAddr;
  UINT32 startTime;
  UINT32 elapsedTime;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  timerAddr = CommonFunctionPtr->MmioRead16 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO_BASE + 0x64));
  if ( timerAddr == 0 ) {
    Delay = Delay / 2;
    while ( Delay != 0 ) {
      CommonFunctionPtr->IoRead8 (IO_DELAY_PORT);
      Delay --;
    }
  } else {
    startTime = CommonFunctionPtr->IoRead32 (timerAddr);
    for ( ;; ) {
      elapsedTime = CommonFunctionPtr->IoRead32 (timerAddr);
      if ( elapsedTime < startTime ) {
        elapsedTime = elapsedTime + MAX_TIMER - startTime;
      } else {
        elapsedTime = elapsedTime - startTime;
      }
      if ((elapsedTime * ELAPSED_TIME_UNIT / ELAPSED_TIME_DIVIDER) > Delay) {
        break;
      }
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set Fan On
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Fan     Fan Number
 *
 */
VOID
CpmSetFanOn (
  IN       VOID                        *This,
  IN       UINT8                       Fan
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10), 0x07);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Set ProcHot
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Enable  Prochot Enable: 0: Disable. 1: Enable
 * @param[in] Fan     FanOut Pin Number
 * @param[in] Freq    Frequency for FanOut Pin
 *
 */
VOID
CpmSetProchot (
  IN       VOID                        *This,
  IN       UINT8                       Enable,
  IN       UINT8                       Fan,
  IN       UINT8                       Freq
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  if (Enable) {
    CommonFunctionPtr->MmioOr8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10 + 0x01), 0x04);            // SET FAN Active with high
    CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10 + 0x02), Freq);         // SET FAN Frequence
    CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10 + 0x03), 0x01);         // SET FAN Duty number
    CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10 + 0x04), 0x00);
    CommonFunctionPtr->MmioAndThenOr8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10), 0xF8, 0x06);      // SET FAN enabled as manually control
  } else {
    CommonFunctionPtr->MmioOr8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO2_BASE + Fan * 0x10), 0x07);                   // Disable FAN for PROCHOT
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Current SATA Mode
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The SATA Mode
 *              BIT0: IDE Mode
 *              BIT1: AHCI Mode
 *              BIT2: RAID Mode
 *              BIT3: AMD AHCI Mode
 *
 */
UINT8
CpmGetSataMode (
  IN      VOID                        *This
  )
{
  UINT8                   Mask;
  UINT16                  DeviceId;
  AMD_CPM_SATA_MODE_MASK  *TablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   FchRevision;
  UINT8                   BusNumber;

  Mask = 0;
  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  FchRevision       = CpmGetFchRevisionId (This);

  DeviceId = 0x7901;      // Default set to SATA AHCI Mode (MS Driver)
  if (FchRevision < CPM_FCH_REVISION_ID_ZP) {
    DeviceId = CommonFunctionPtr->PciRead16 (This, SB_SATA_BUS, SB_SATA_DEVICE, SB_SATA_FUNCTION, 0x02);
  } else if (FchRevision == CPM_FCH_REVISION_ID_ZP) {
    BusNumber = CommonFunctionPtr->PciRead8 (This, ZP_BRIDGE_BUS, ZP_BRIDGE_DEVICE, ZP_BRIDGE_FUNCTION, 0x19);
    DeviceId = CommonFunctionPtr->PciRead16 (This, BusNumber, ZP_SATA_DEVICE, ZP_SATA_FUNCTION, 0x02);
  } else if (FchRevision > CPM_FCH_REVISION_ID_ZP) {
    BusNumber = CommonFunctionPtr->PciRead8 (This, RV_BRIDGE_BUS, RV_BRIDGE_DEVICE, RV_BRIDGE_FUNCTION, 0x19);
    DeviceId = CommonFunctionPtr->PciRead16 (This, BusNumber, RV_SATA_DEVICE, RV_SATA_FUNCTION, 0x02);
  }

  TablePtr = &SataModeMask[0];
  while ( TablePtr->DeviceId != 0xFFFF ) {
    if ( TablePtr->DeviceId == DeviceId ) {
      Mask = TablePtr->Mask;
      break;
    }
    TablePtr ++;
  }
  return ( Mask );
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check whether the device is in FCH
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Device    The PCI Device Number
 * @param[in] Function  The PCI Function Number
 *
 * @retval    TRUE      The Device is in FCH
 *            FALSE     The Device is not in FCH
 *
 */
BOOLEAN
EFIAPI
CpmIsFchDevice (
  IN       VOID                        *This,
  IN       UINT8                       Device,
  IN       UINT8                       Function
  )
{
  if (Device <= 0x10) {
    return 0;
  } else {
    return 1;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get FCH PCIe Bridge Name in ASL Code
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Device    The PCI Device Number
 * @param[in] Function  The PCI Function Number
 *
 * @retval    PCIe Bridge Name in ASL code
 *
 */
UINT32
CpmGetFchPcieAslName (
  IN       VOID                       *This,
  IN       UINT8                      Device,
  IN       UINT8                      Function
  )
{
  PCIE_BRIDGE_NAME  *BridgeNamePtr;
  UINT32  Name;

  Name = 0;
  BridgeNamePtr = &FchPcieBridgeName[0];
  while (BridgeNamePtr->Device != 0) {
    if (BridgeNamePtr->Device == Device && BridgeNamePtr->Function == Function) {
      switch (BridgeNamePtr->NameId) {
      case 0x30:
        Name = PcdGet32 (FchPcieGpp0AslName);
        break;
      case 0x31:
        Name = PcdGet32 (FchPcieGpp1AslName);
        break;
      case 0x32:
        Name = PcdGet32 (FchPcieGpp2AslName);
        break;
      case 0x33:
        Name = PcdGet32 (FchPcieGpp3AslName);
        break;
      }
      if (!Name) {
        Name = BridgeNamePtr->Name;
      }
      break;
    }
    BridgeNamePtr ++;
  }
  return Name;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get the Mapping Bit Number of GEVENT pin in Event Status
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] GeventPin GEVENT Pin Number
 *
 * @retval    SCI Mapping Bit Number
 *
 */
UINT8
CpmGetSciMap (
  IN       VOID                        *This,
  IN       UINT8                       GeventPin
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  return CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + SMI_BASE + 0x40 + GeventPin));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Current Boot Mode
 *
 *
 * @retval    Boot Mode
 *
 */
UINT8
CpmGetBootMode (
  )
{
  UINT16                  Address;
  UINT16                  Value;

  if (PcdGet8 (CpmBootModeOverride) & BIT7) {
    Value = (UINT16)PcdGet8 (CpmBootModeOverride);
    Value &= 0x7F;
    Value <<= 10;
  } else {
    CpmIoWrite8 (0xCD6, 0x63);
    Address = (UINT16)CpmIoRead8 (0xCD7);
    CpmIoWrite8 (0xCD6, 0x62);
    Address = Address * 0x100 + (UINT16)CpmIoRead8 (0xCD7);
    Value = CpmIoRead16 (Address) & 0x1C00;
  }

  return (UINT8) (Value >> 10);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check whether it is a RTC wake up
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    TRUE      RTC wake up
 *            FALSE     Not RTC wake up
 *
 */
BOOLEAN
EFIAPI
CpmIsRtcWakeup (
  IN       VOID                        *This
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  UINT8                   Status;
  UINT8                   Enable;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  Status = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + ACPI_BASE + 0x01));
  Enable = CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + ACPI_BASE + 0x03));
  if ((Status & BIT2) && (Enable & BIT2)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read RTC register
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Index     The index of RTC register
 *
 * @retval    RTC register value
 *
 */
UINT8
EFIAPI
CpmGetRtc (
  IN       VOID                        *This,
  IN       UINT8                       Index
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  return CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + CMOS_BASE + Index));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write RTC register
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Index     The index of RTC register
 * @param[in] Value     The value of RTC register
 *
 */
VOID
EFIAPI
CpmSetRtc (
  IN       VOID                        *This,
  IN       UINT8                       Index,
  IN       UINT8                       Value
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + CMOS_BASE + Index), Value);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read ACPI register
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Index     The index of ACPI register
 *
 * @retval    RTC register value
 *
 */
UINT8
EFIAPI
CpmGetAcpi (
  IN       VOID                        *This,
  IN       UINT8                       Index
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  return CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + ACPI_BASE + Index));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write ACPI register
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Index     The index of ACPI register
 * @param[in] Value     The value of ACPI register
 *
 */
VOID
EFIAPI
CpmSetAcpi (
  IN       VOID                        *This,
  IN       UINT8                       Index,
  IN       UINT8                       Value
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  CommonFunctionPtr->MmioWrite8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + ACPI_BASE + Index), Value);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Read the data from Save Context Area
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Offset    The offset of data to read
 *
 * @retval    RTC register value
 *
 */
UINT8
EFIAPI
CpmGetSaveContext (
  IN       VOID                        *This,
  IN       UINT8                       Offset
  )
{
  AMD_CPM_MAIN_TABLE          *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION     *CommonFunctionPtr;
  AMD_CPM_SAVE_CONTEXT_TABLE  *SaveContextTablePtr;
  UINT8                       Data;
  UINT32                      Address;
  UINT8                       Flag;

  Data = 0;
  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  SaveContextTablePtr = CommonFunctionPtr->GetTablePtr (This, CPM_SIGNATURE_SAVE_CONTEXT);
  if (SaveContextTablePtr) {
    Flag = Offset & 0x80;
    Offset = Offset & 0x7F;
    if (Flag && (Offset < sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT))) {
      Address = (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x100 * SaveContextTablePtr->BufferType + SaveContextTablePtr->BufferOffset);
      Data = CommonFunctionPtr->MmioRead8 (Address + (UINT32)Offset);
    } else if (Offset < SaveContextTablePtr->BufferSize - sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT)) {
      Address = (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x100 * SaveContextTablePtr->BufferType + SaveContextTablePtr->BufferOffset + sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT));
      Data = CommonFunctionPtr->MmioRead8 (Address + (UINT32)Offset);
    } else {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Offset = 0x%02X\n", __FUNCTION__, Offset));
      CPM_DEADLOOP ();
    }
  }
  return Data;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Write the data to Save Context Area
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Offset    The offset of data to read
 * @param[in] Data      The data to write
 *
 */
VOID
EFIAPI
CpmSetSaveContext (
  IN       VOID                        *This,
  IN       UINT8                       Offset,
  IN       UINT8                       Data
  )
{
  AMD_CPM_MAIN_TABLE          *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION     *CommonFunctionPtr;
  AMD_CPM_SAVE_CONTEXT_TABLE  *SaveContextTablePtr;
  UINT32                      Address;
  UINT8                       Flag;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  SaveContextTablePtr = CommonFunctionPtr->GetTablePtr (This, CPM_SIGNATURE_SAVE_CONTEXT);
  if (SaveContextTablePtr) {
    Flag = Offset & 0x80;
    Offset = Offset & 0x7F;
    if (Flag && (Offset < sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT))) {
      Address = (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x100 * SaveContextTablePtr->BufferType + SaveContextTablePtr->BufferOffset);
      CommonFunctionPtr->MmioWrite8 (Address + (UINT32)Offset, Data);
    } else if (!Flag && (Offset < SaveContextTablePtr->BufferSize - sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT))) {
      Address = (UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x100 * SaveContextTablePtr->BufferType + SaveContextTablePtr->BufferOffset + sizeof (AMD_CPM_PREDEFINED_SAVE_CONTEXT));
      CommonFunctionPtr->MmioWrite8 (Address + (UINT32)Offset, Data);
    } else {
      DEBUG((DEBUG_INFO, "  LIB-FCH-%a-CPM_DEADLOOP-Offset = 0x%02X Data = 0x%02X\n", __FUNCTION__, Offset, Data));
      CPM_DEADLOOP ();
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get ACPI SMI Command register
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    ACPI SMI Command register offset
 */
UINT16
CpmGetAcpiSmiCmd (
  IN       VOID                        *This
  )
{
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;

  CommonFunctionPtr   = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  MainTablePtr        = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;

  return CommonFunctionPtr->MmioRead16 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + PMIO_BASE + 0x6A));
}


/*---------------------------------------------------------------------------------------*/
/**
 * Register CPM Common FCH Function
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 *
 */
VOID
EFIAPI
CpmRegisterFch (
  IN       VOID                        *This
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT8                   Data[4];
  UINT8                   FchRevision;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-Start\n", __FUNCTION__));
  MainTablePtr = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  FchRevision = CpmGetFchRevisionId (This);
  ((AMD_CPM_TABLE_PPI*)This)->ChipId.Sb = FchRevision;

  switch (FchRevision) {
  case CPM_FCH_REVISION_ID_DEFAULT:
  case CPM_FCH_REVISION_ID_KB:
    CommonFunctionPtr->IoWrite8 (0xCD6, 0x24);
    Data[0] = CommonFunctionPtr->IoRead8 (0xCD7);
    if (!(Data[0] & BIT0)) {
      CommonFunctionPtr->IoWrite8 (0xCD7, Data[0] | BIT0);
    }
    if (!MainTablePtr->AcpiMemIoBaseAddr) {
      CommonFunctionPtr->IoWrite8 (0xCD6, 0x25);
      Data[1] = CommonFunctionPtr->IoRead8 (0xCD7);
      CommonFunctionPtr->IoWrite8 (0xCD6, 0x26);
      Data[2] = CommonFunctionPtr->IoRead8 (0xCD7);
      CommonFunctionPtr->IoWrite8 (0xCD6, 0x27);
      Data[3] = CommonFunctionPtr->IoRead8 (0xCD7);
      MainTablePtr->AcpiMemIoBaseAddr = (Data[3] << 24) + (Data[2] << 16) + (Data[1] << 8);
    }
    break;
  case CPM_FCH_REVISION_ID_ML:
  case CPM_FCH_REVISION_ID_CZ:
  case CPM_FCH_REVISION_ID_NL:
  case CPM_FCH_REVISION_ID_AM:
  case CPM_FCH_REVISION_ID_ST:
  case CPM_FCH_REVISION_ID_BR:
  case CPM_FCH_REVISION_ID_ZP:
    MainTablePtr->AcpiMemIoBaseAddr = 0xFED80000;
    break;
  case CPM_FCH_REVISION_ID_RV:
  case CPM_FCH_REVISION_ID_RV2:
    MainTablePtr->AcpiMemIoBaseAddr = 0xFED80000;
    // Turn on/off IO port 80 decoding for LPC - Register 0x48, bit 21
    CommonFunctionPtr->PciAndThenOr8( This,
                                      FCH_LPC_BUS,
                                      FCH_LPC_DEV,
                                      FCH_LPC_FUNC,
                                      FCH_LPC_REG4A,
                                      0xDF,                                   // AND data
                                      PcdGet8 (PcdIoPort80LpcDecodeEn) << 5); // OR data
    break;
  case CPM_FCH_REVISION_ID_SSP:
  case CPM_FCH_REVISION_ID_MTS:
    MainTablePtr->AcpiMemIoBaseAddr = 0xFED80000;
    break;
  }

  CommonFunctionPtr->GetGpio          = CpmGetGpio;
  CommonFunctionPtr->SetGpio          = CpmSetGpio;
  CommonFunctionPtr->GetGevent        = CpmGetGevent;
  CommonFunctionPtr->SetGevent        = CpmSetGevent;
  CommonFunctionPtr->SetSmiControl    = CpmSetSmiControl;
  CommonFunctionPtr->SetGeventSciTrig = CpmSetGeventSciTrig;
  CommonFunctionPtr->SetGeventSci     = CpmSetGeventSci;
  CommonFunctionPtr->GetStrap         = CpmGetStrap;
  CommonFunctionPtr->SetClkReq        = CpmSetClkReq;
  CommonFunctionPtr->GetClkReq        = CpmGetClkReq;
  CommonFunctionPtr->Stall            = CpmStall;
  CommonFunctionPtr->SetFanOn         = CpmSetFanOn;
  CommonFunctionPtr->SetProchot       = CpmSetProchot;
  CommonFunctionPtr->GetSataMode      = CpmGetSataMode;
  CommonFunctionPtr->IsFchDevice      = CpmIsFchDevice;
  CommonFunctionPtr->GetSciMap        = CpmGetSciMap;
  CommonFunctionPtr->GetFchPcieAslName  = CpmGetFchPcieAslName;
  CommonFunctionPtr->GetBootMode      = CpmGetBootMode;
  CommonFunctionPtr->IsRtcWakeup      = CpmIsRtcWakeup;
  CommonFunctionPtr->GetRtc           = CpmGetRtc;
  CommonFunctionPtr->SetRtc           = CpmSetRtc;
  CommonFunctionPtr->GetAcpi          = CpmGetAcpi;
  CommonFunctionPtr->SetAcpi          = CpmSetAcpi;
  CommonFunctionPtr->GetSaveContext   = CpmGetSaveContext;
  CommonFunctionPtr->SetSaveContext   = CpmSetSaveContext;
  CommonFunctionPtr->GetAcpiSmiCmd    = CpmGetAcpiSmiCmd;

  DEBUG((DEBUG_INFO, "  LIB-FCH-%a-End\n", __FUNCTION__));
  return;
}
