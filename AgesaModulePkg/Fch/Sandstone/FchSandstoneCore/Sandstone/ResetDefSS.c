/* $NoKeywords:$ */
/**
 * @file
 *
 * Graphics Controller family specific service procedure
 *
 *
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
*
*/


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "FchPlatform.h"
#include  "Filecode.h"
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */



/*----------------------------------------------------------------------------------------
 * Default FCH interface settings at InitReset phase.
 *----------------------------------------------------------------------------------------
 */
CONST FCH_RESET_INTERFACE ROMDATA FchResetInterfaceDefault = {
  TRUE,                // UmiGen2
  TRUE,                // SataEnable
  TRUE,                // IdeEnable
  TRUE,                // GppEnable
  TRUE,                // Xhci0Enable
  TRUE                 // Xhci1Enable
};


/*----------------------------------------------------------------
 *  InitReset Phase Data Block Default (Failsafe)
 *----------------------------------------------------------------
 */
FCH_RESET_DATA_BLOCK   InitResetCfgDefault = {
  NULL,                  // StdHeader
  { TRUE,
    TRUE,
    FALSE,
    FALSE,
    TRUE,
    TRUE
    },                   // FchReset

  0,                     // FastSpeed
  3,                     // WriteSpeed
  0,                     // Mode
  0,                     // AutoMode
  0,                     // BurstWrite
  FALSE,                 // SataIdeCombMdPriSecOpt
  0,                     // Cg2Pll
  FALSE,                 // EcKbd
  FALSE,                 // LegacyFree
  FALSE,                 // SataSetMaxGen2
  1,                     // SataClkMode
  0,                     // SataModeReg
  FALSE,                 // SataInternal100Spread
  2,                     // SpiSpeed
//  0xFCFCFCFC,                     // 38
//  0x88FC,                     // 3c
//  0,                     // 1d_34
  1,                     // 20_0
  FALSE,                 // EcChannel0

  {                      // FCH_GPP
    {                    // Array of FCH_GPP_PORT_CONFIG       PortCfg[4]
      {
        FALSE,           // PortPresent
        FALSE,           // PortDetected
        FALSE,           // PortIsGen2
        FALSE,           // PortHotPlug
        0,               // PortMisc
      },
      {
        FALSE,           // PortPresent
        FALSE,           // PortDetected
        FALSE,           // PortIsGen2
        FALSE,           // PortHotPlug
        0,               // PortMisc
      },
      {
        FALSE,           // PortPresent
        FALSE,           // PortDetected
        FALSE,           // PortIsGen2
        FALSE,           // PortHotPlug
        0,               // PortMisc
      },
      {
        FALSE,           // PortPresent
        FALSE,           // PortDetected
        FALSE,           // PortIsGen2
        FALSE,           // PortHotPlug
        0,               // PortMisc
      },
    },
    PortA1B1C1D1,        // GppLinkConfig
    FALSE,               // GppFunctionEnable
    FALSE,               // GppToggleReset
    0,                   // GppHotPlugGeventNum
    0,                   // GppFoundGfxDev
    FALSE,               // GppGen2
    0,                   // GppGen2Strap
    FALSE,               // GppMemWrImprove
    FALSE,               // GppUnhidePorts
    0,                   // GppPortAspm
    FALSE,               // GppLaneReversal
    FALSE,               // GppPhyPllPowerDown
    FALSE,               // GppDynamicPowerSaving
    FALSE,               // PcieAer
    FALSE,               // PcieRas
    FALSE,               // PcieCompliance
    FALSE,               // PcieSoftwareDownGrade
    FALSE,               // UmiPhyPllPowerDown
    FALSE,               // SerialDebugBusEnable
    0,                   // GppHardwareDownGrade
    0,                   // GppL1ImmediateAck
    FALSE,               // NewGppAlgorithm
    0,                   // HotPlugPortsStatus
    0,                   // FailPortsStatus
    40,                  // GppPortMinPollingTime
    FALSE,               // IsCapsuleMode
  },
  {                      // FCH_SPI
    FALSE,               // LpcMsiEnable
    0x00000000,          // LpcSsid
    0,                   // RomBaseAddress
    0,                   // Speed
    0,                   // FastSpeed
    0,                   // WriteSpeed
    0,                   // Mode
    0,                   // AutoMode
    0,                   // BurstWrite
    TRUE,                // LpcClk0
    TRUE,                // LpcClk1
    TRUE,                // LpcClkRunEn
    0,                   // SPI100_Enable
    {0}                  // SpiDeviceProfile
  },
  FALSE,                 // QeEnabled
  FALSE,                 // FCH OSCOUT1_CLK Continous
  8,                     // LpcClockDriveStrength
  8,                     // LpcClockDriveStrengthRiseTime
  8,                     // LpcClockDriveStrengthFallTime
  {                      // FCH_PT
    {1, 1, 0, 1, 1, 1, 0, 0, 1},// FCH_PT_USB
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},// FCH_PT_SATA
    {1, 1, 1, 1, 1, 1, 1, 1},// FCH_PT_SATA port
    {1, 1},// FCH_PT_PCIE
    {0xFF, 0x00, 0x00, 0x00,0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000000000000000},// FCH_PT_ADDR
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},// FCH_PT_USBPort for PROM 3/4/5/6/7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},      // FCH_PT_USBPort for PRO 460
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},            // FCH_PT_USBPort for PROM 2/8/9
    {1, 1, 1, 1, 1, 1, 1, 1, 1},               // FCH_PT_USBPort for PROM 1
    {                      // PT USB TX
      {                     // Array of USB31[2] Tx setting
        {0x0F,0x0F,0x01,0x01,0x04,0x03,0x00,0x01,0x04,0x01},         // USB31PCS_B1 Tx setting
        {0x0F,0x0F,0x01,0x01,0x04,0x04,0x00,0x01,0x04,0x01},         // USB31PCS_B2 Tx setting
      },
      {                     // Array of USB30[3] Tx setting
        {0x0F,0x01,0x04},                                            // USB30PCS_P0 Tx setting
        {0x0F,0x01,0x08},                                            // USB30PCS_P1 Tx setting
        {0x0F,0x01,0x04},                                            // USB30PCS_P2 Tx setting
        {0x0F,0x01,0x08},                                            // USB30PCS_P3 Tx setting
        {0x0F,0x01,0x04},                                            // USB30PCS_P4 Tx setting
        {0x0F,0x01,0x08},                                            // USB30PCS_P5 Tx setting
      },
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[0]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[5]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[13][11]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[12][10]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[2][6]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[3][7]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[4][8]
      5,                                                 // PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[1][9]
   },
   {                      // LP-PT USB TX
      {                     // Array of USB31[2] Tx setting
        {0x0F,0x0F,0x01,0x01,0x04,0x03,0x00,0x01,0x04,0x01},         // LP-PT USB31PCS_B1 Tx setting
        {0x0F,0x0F,0x01,0x01,0x04,0x03,0x00,0x01,0x04,0x01},         // LP-PT USB31PCS_B2 Tx setting
      },
      {                     // Array of USB30[3] Tx setting
        {0x0F,0x01,0x04},                                            // LP-PT USB30PCS_P0 Tx setting
        {0x0F,0x01,0x0C},                                            // LP-PT USB30PCS_P1 Tx setting
        {0x0F,0x01,0x04},                                            // LP-PT USB30PCS_P2 Tx setting
        {0x0F,0x01,0x0C},                                            // LP-PT USB30PCS_P3 Tx setting
        {0x0F,0x01,0x04},                                            // LP-PT USB30PCS_P4 Tx setting
        {0x0F,0x01,0x0C},                                            // LP-PT USB30PCS_P5 Tx setting
      },
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[0]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[5]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[13][11]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[12][10]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[2][6]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[3][7]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[4][8]
      7,                                                 // LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[1][9]
    },
    {                      // PT SATA TX
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port0 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port1 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port2 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port3 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port4 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port5 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port6 TX SETTINGS
      {0x00,0x04,0x08,0x00,0x01,0x01,0x00,0x02,0x03},             // SATA Port7 TX SETTINGS
    },
    {1, 1, 1, 1, 1, 1, 1, 1},// Enable/Disable PCIE Switch Downstream Ports
    {0, 0, 0, 0, 0, 0, 0, 0},// Enable/Disable LP PT GPP Clock Force On
    {0, 0x00, 0x00000000},   // SSP data Structure to get PT root port
    {                        // PTSvidSsid
      {0x1B21,0x1142},                                            // XHCI_SVID XHCI_SSID
      {0x1B21,0x1062},                                            // AHCI_SVID AHCI_SSID
      {0x1B21,0x0201},                                            // PCIE_SVID PCIE_SSID
      {0x1B21,0x3306},                                            // PCIE_DSP0_SVID PCIE_DSP0_SSID
      {0x1B21,0x3306},                                            // PCIE_DSP1_SVID PCIE_DSP1_SSID
      {0x1B21,0x3306},                                            // PCIE_DSP2_SVID PCIE_DSP2_SSID
      {0x1B21,0x3306},                                            // PCIE_DSP3_SVID PCIE_DSP3_SSID
      {0x1B21,0x3306},                                            // PCIE_DSP4_SVID PCIE_DSP4_SSID
    },
  },
  NULL,                  // EarlyOemGpioTable
  {0},                   // FchBldCfg
  0,                     // USB3 ECC SMI control
  FALSE,                 // EspiEnable
  FALSE,                 // EspiIo80Enable
  FALSE,                 // EspiKbc6064Enable
  FALSE,                 // EspiEc0Enable
  FALSE,                 // WdtEnable
  FALSE,                 // Xhci0ForceGen1
  FALSE,                 // Xhci1Disable31Port
  TRUE,                  // ToggleAllPwrGoodOnCf9
  NULL,                  // OemUsbConfigurationTablePtr
  NULL,                  // OemResetProgrammingTablePtr
  0x00,                  //  XhciUsb3PortDisable
  0x00,                  //  XhciUsb2PortDisable
  0xFFFFFFFF,            //  XhciOCpinSelect
  {0},                   //  EMMC structure
  {//ESPI
    0,                   //  OperatingFreq
    0,                   //  IoMode
    {
      {
        {
          TRUE,          //  IoRange0Enable
          0x4F,          //  IoRange0Base
          0x00,          //  IoRange0Size
        },
        {
          TRUE,          //  IoRange1Enable
          0x4E,          //  IoRange1Base
          0x00,          //  IoRange1Size
        },
        {
          TRUE,          //  IoRange2Enable
          0x600,         //  IoRange2Base
          0xFF,          //  IoRange2Size
        },
        {
          TRUE,          //  IoRange3Enable
          0x4C,          //  IoRange3Base
          0x00,          //  IoRange3Size
        }
      },
      {
        {
          FALSE,         //  MmioRange0Enable
          0x00000000,    //  MmioRange0Base
          0x0000,        //  MmioRange0Size
        },
        {
          FALSE,         //  MmioRange1Enable
          0x00000000,    //  MmioRange1Base
          0x0000,        //  MmioRange1Size
        },
        {
          FALSE,         //  MmioRange2Enable
          0x00000000,    //  MmioRange2Base
          0x0000,        //  MmioRange2Size
        },
        {
          FALSE,         //  MmioRange3Enable
          0x00000000,    //  MmioRange3Base
          0x0000,        //  MmioRange3Size
        }
      }
    }
  },
  TRUE,                  //  UsbSparseModeEnable
};



