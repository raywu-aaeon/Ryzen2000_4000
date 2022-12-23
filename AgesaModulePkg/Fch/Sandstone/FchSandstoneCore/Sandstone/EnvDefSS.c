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
 * @e \$Revision: 312904 $   @e \$Date: 2015-02-11 12:19:11 -0800 (Wed, 11 Feb 2015) $
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
 * Default FCH interface settings at InitEnv phase.
 *----------------------------------------------------------------------------------------
 */
CONST FCH_INTERFACE FchInterfaceDefault = {
  SdVer3,              // SdConfig
  AzEnable,            // AzaliaControl
  IrRxTx0Tx1,          // IrConfig
  TRUE,                // UmiGen2
  0,                   // SataClass
  TRUE,                // SataEnable
  TRUE,                // IdeEnable
  TRUE,                // SataIdeMode
  TRUE,                // Ohci1Enable
  TRUE,                // Ohci2Enable
  TRUE,                // Ohci3Enable
  TRUE,                // Ohci4Enable
  TRUE,                // GppEnable
  AlwaysOff            // FchPowerFail
};


/*----------------------------------------------------------------
 *  InitEnv Phase Data Block Default (Failsafe)
 *----------------------------------------------------------------
 */
FCH_DATA_BLOCK   InitEnvCfgDefault = {
  {
    0xF8000000,              ///< PcieMmioBase
    0,                       ///< FchDeviceEnableMap
    0,                       ///< FchDeviceD3ColdMap //D3Cold of XHCI is enabled BIT23
    0,                       ///< XhciRomSourceBase
    0,                       ///< XhciRomTargetBase
    0,                       ///< XhciRamSourceBase
    0,                       ///< XhciRamTargetBase
    0,                       ///< SataDevSlpPort0S5Pin - Reserved
    0,                       ///< SataDevSlpPort1S5Pin - Reserved
  },
  NULL,                      // StdHeader

  {                          // FCH_ACPI
    0xB00,                   // Smbus0BaseAddress
    0xB20,                   // Smbus1BaseAddress
    0xE00,                   // SioPmeBaseAddress
    0xFEC000F0,              // WatchDogTimerBase
    0x400,                   // AcpiPm1EvtBlkAddr
    0x404,                   // AcpiPm1CntBlkAddr
    0x408,                   // AcpiPmTmrBlkAddr
    0x410,                   // CpuControlBlkAddr
    0x420,                   // AcpiGpe0BlkAddr
    0x00B0,                  // SmiCmdPortAddr
    0xFE00,                  // AcpiPmaCntBlkAddr
    TRUE,                    // AnyHt200MhzLink
    TRUE,                    // SpreadSpectrum
    UsePrevious,             // PwrFailShadow
    0,                       // StressResetMode
    FALSE,                   // MtC1eEnable
    NULL,                    // OemProgrammingTablePtr
    1,                       // SpreadSpectrumOptions
    FALSE,                   // PwrDownDisp2ClkPcieR
    FALSE,                   // NoClearThermalTripSts
    FALSE,                   // FchAoacProgramEnable
    FALSE,                   // FchSxEntryXhciPmeEn
  },

  {                          // FCH_AB
    FALSE,                   // AbMsiEnable
    1,                       // ALinkClkGateOff
    1,                       // BLinkClkGateOff
    3,                       // GPP Clock Request.
    3,                       // GPP Clock Request.
    3,                       // GPP Clock Request.
    3,                       // GPP Clock Request.
    1,                       // GPP Clock Request.
    1,                       // AbClockGating
    0,                       // GppClockGating
    0,                       // UmiL1TimerOverride
    0,                       // UmiLinkWidth
    0,                       // UmiDynamicSpeedChange
    0,                       // PcieRefClockOverClocking
    0,                       // UmiGppTxDriverStrength
    FALSE,                   // NbSbGen2
    0,                       // FchPcieOrderRule
    0,                       // SlowSpeedAbLinkClock
    FALSE,                    // ResetCpuOnSyncFlood
    TRUE,                    // AbDmaMemoryWrtie3264B
    TRUE,                    // AbMemoryPowerSaving
    FALSE,                   // SbgDmaMemoryWrtie3264ByteCount
    TRUE,                    // SbgMemoryPowerSaving
    TRUE,                    // SBG Clock Gate
    FALSE,                   // XDMA DMA Write 16 byte mode
    FALSE,                   // XDMA memory power saving
    0,                       // XDMA PENDING NPR THRESHOLD
    FALSE,                   // XDMA DNCPL ORDER DIS
    3,                       // SLT GFX Clock Request.
    3,                       // SLT GFX Clock Request.
    FALSE,                   // SdphostBypassDataPack
    FALSE,                   // SdphostDisNpmwrProtect
  },

  {                          // FCH_GPP
    {                        // Array of FCH_GPP_PORT_CONFIG       PortCfg[4]
      {
        FALSE,               // PortPresent
        FALSE,               // PortDetected
        FALSE,               // PortIsGen2
        FALSE,               // PortHotPlug
        0,                   // PortMisc
      },
      {
        FALSE,               // PortPresent
        FALSE,               // PortDetected
        FALSE,               // PortIsGen2
        FALSE,               // PortHotPlug
        0,                   // PortMisc
      },
      {
        FALSE,               // PortPresent
        FALSE,               // PortDetected
        FALSE,               // PortIsGen2
        FALSE,               // PortHotPlug
        0,                   // PortMisc
      },
      {
        FALSE,               // PortPresent
        FALSE,               // PortDetected
        FALSE,               // PortIsGen2
        FALSE,               // PortHotPlug
        0,                   // PortMisc
      },
    },
    PortA1B1C1D1,            // GppLinkConfig
    FALSE,                   // GppFunctionEnable
    FALSE,                   // GppToggleReset
    0,                       // GppHotPlugGeventNum
    0,                       // GppFoundGfxDev
    FALSE,                   // GppGen2
    0,                       // GppGen2Strap
    FALSE,                   // GppMemWrImprove
    FALSE,                   // GppUnhidePorts
    0,                       // GppPortAspm
    FALSE,                   // GppLaneReversal
    FALSE,                   // GppPhyPllPowerDown
    FALSE,                   // GppDynamicPowerSaving
    FALSE,                   // PcieAer
    FALSE,                   // PcieRas
    FALSE,                   // PcieCompliance
    FALSE,                   // PcieSoftwareDownGrade
    FALSE,                   // UmiPhyPllPowerDown
    FALSE,                   // SerialDebugBusEnable
    0,                       // GppHardwareDownGrade
    0,                       // GppL1ImmediateAck
    FALSE,                   // NewGppAlgorithm
    0,                       // HotPlugPortsStatus
    0,                       // FailPortsStatus
    40,                      // GppPortMinPollingTime
    FALSE,                   // IsCapsuleMode
  },

  {                          // FCH_USB
    TRUE,                    // Ohci1Enable
    TRUE,                    // Ohci2Enable
    TRUE,                    // Ohci3Enable
    TRUE,                    // Ohci4Enable
    TRUE,                    // Ehci1Enable
    TRUE,                    // Ehci2Enable
    TRUE,                    // Ehci3Enable
    FALSE,                   // Xhci0Enable
    FALSE,                   // Xhci1Enable
    FALSE,                   // UsbMsiEnable
    0,                       // OhciSsid
    0,                       // Ohci4Ssid
    0,                       // EhciSsid
    0,                       // XhciSsid
    FALSE,                   // UsbPhyPowerDown
    0,                       // UserDefineXhciRomAddr
    {0x21, 0x21, 0x21, 0x21, 0x22},      // Ehci18Phy
    {0x22, 0x22, 0x22, 0x21, 0x21},      // Ehci19Phy
    {0x21, 0x21, 0x21, 0x21},            // Ehci22Phy
    {0x24, 0x24, 0x21, 0x21},            // Xhci20Phy
    0,                                   // Ehci1DebugPortSel
    0,                                   // Ehci2DebugPortSel
    0,                                   // Ehci3DebugPortSel
    TRUE,                    // SsicEnable
    0,                       // SsicSsid
    0,                       // Usb0Bar
    0,                       // Usb1Bar
  },

  {                          // FCH_SATA
    FALSE,                   // SataMsiEnable
    0x00000000,              // SataIdeSsid
    0x00000000,              // SataRaidSsid
    0x00000000,              // SataRaid5Ssid
    0x00000000,              // SataAhciSsid
    {                        // SATA_ST
      0,                     // SataModeReg
      TRUE,                  // SataEnable
      0,                     // Sata6AhciCap
      TRUE,                  // SataSetMaxGen2
      FALSE,                 // IdeEnable
      01,                    // SataClkMode
    },
    SataAhci,                // SataClass
    0,                       // SataIdeMode
    0,                       // SataDisUnusedIdePChannel
    0,                       // SataDisUnusedIdeSChannel
    0,                       // IdeDisUnusedIdePChannel
    0,                       // IdeDisUnusedIdeSChannel
    0,                       // SataOptionReserved
    {                        // SATA_PORT_ST
      0,                     // SataPortReg
      FALSE,                  // Port0
      FALSE,                  // Port1
      FALSE,                  // Port2
      FALSE,                  // Port3
      FALSE,                  // Port4
      FALSE,                  // Port5
      FALSE,                  // Port6
      FALSE,                  // Port7
    },
    {                        // SATA_PORT_ST
      0,                     // SataPortReg
      FALSE,                 // Port0
      FALSE,                 // Port1
      FALSE,                 // Port2
      FALSE,                 // Port3
      FALSE,                 // Port4
      FALSE,                 // Port5
      FALSE,                 // Port6
      FALSE,                 // Port7
    },
    {                        // SATA_PORT_MD
      0,                     // SataPortMode
      0,                     // Port0
      0,                     // Port1
      0,                     // Port2
      0,                     // Port3
      0,                     // Port4
      0,                     // Port5
      0,                     // Port6
      0,                     // Port7
    },
    1,                       // SataAggrLinkPmCap
    1,                       // SataPortMultCap
    1,                       // SataClkAutoOff
    1,                       // SataPscCap
    0,                       // BiosOsHandOff
    1,                       // SataFisBasedSwitching
    0,                       // SataCccSupport
    1,                       // SataSscCap
    0,                       // SataMsiCapability
    0,                       // SataForceRaid
    0,                       // SataInternal100Spread
    0,                       // SataDebugDummy
    0,                       // SataTargetSupport8Device
    0,                       // SataDisableGenericMode
    FALSE,                   // SataAhciEnclosureManagement
    0,                       // SataSgpio0
    0,                       // SataSgpio1
    0,                       // SataPhyPllShutDown
    FALSE,                   // SataHotRemovalEnh
    {                        // SATA_PORT_ST
      0,                     // SataPortReg
      FALSE,                 // Port0
      FALSE,                 // Port1
      FALSE,                 // Port2
      FALSE,                 // Port3
      FALSE,                 // Port4
      FALSE,                 // Port5
      FALSE,                 // Port6
      FALSE,                 // Port7
    },
    FALSE,                   // SataOobDetectionEnh
    FALSE,                   // SataPowerSavingEnh
    0,                       // SataMemoryPowerSaving
    FALSE,                   // SataRasSupport
    TRUE,                    // SataAhciDisPrefetchFunction
    FALSE,                   // SataDevSlpPort0
    FALSE,                   // SataDevSlpPort1
    0,                       // TempMmio
    0,                       // SataDevSlpPort0Num
    0,                       // SataDevSlpPort1Num
    FALSE,                   // SataControllerAutoShutdown
  },

  {                          // FCH_SMBUS
    0x00000000               // SmbusSsid
  },

  {                          // FCH_IDE
    TRUE,                    // IdeEnable
    FALSE,                   // IdeMsiEnable
    0x00000000               // IdeSsid
  },

  {                          // FCH_AZALIA
    AzDisable,               // AzaliaEnable
    FALSE,                   // AzaliaMsiEnable
    0x00000000,              // AzaliaSsid
    0,                       // AzaliaPinCfg
    0,                       // AzaliaFrontPanel
    0,                       // FrontPanelDetected
    0,                       // AzaliaSnoop
    0,                       // AzaliaDummy
    {                        // AZALIA_PIN
      0,                     // AzaliaSdin0
      0,                     // AzaliaSdin1
      0,                     // AzaliaSdin2
      0,                     // AzaliaSdin3
    },
    NULL,                    // *AzaliaOemCodecTablePtr
    NULL,                    // *AzaliaOemFpCodecTablePtr
  },

  {                          // FCH_SPI
    FALSE,                   // LpcMsiEnable
    0x00000000,              // LpcSsid
    0,                       // RomBaseAddress
    0,                       // Speed
    0,                       // FastSpeed
    0,                       // WriteSpeed
    0,                       // Mode
    0,                       // AutoMode
    0,                       // BurstWrite
    TRUE,                    // LpcClk0
    TRUE,                    // LpcClk1
    0,                       // SPI100_Enable
    {0}                      // SpiDeviceProfile
  },

  {                          // FCH_PCIB
    FALSE,                   // PcibMsiEnable
    0x00000000,              // PcibSsid
    0x0F,                    // PciClks
    0,                       // PcibClkStopOverride
    FALSE,                   // PcibClockRun
  },

  {                          // FCH_GEC
    FALSE,                   // GecEnable
    0,                       // GecPhyStatus
    0,                       // GecPowerPolicy
    0,                       // GecDebugBus
    0xFED61000,              // GecShadowRomBase
    NULL,                    // *PtrDynamicGecRomAddress
  },

  {                          // FCH_SD
    SdDisable,               // SdConfig
    0,                       // Speed
    0,                       // BitWidth
    0x00000000,              // SdSsid
    Sd50MhzTraceCableLengthWithinSixInches,  // SdClockControl
    FALSE,
    0,
    1,
    3,
    0,                       // SdSlotType
    FALSE,                   // SdForce18
    0,                       // SdDbgConfig
  },

  {0},                       // FCH_HWM

  {0,                        // FCH_IR
   0x23,                     // IrPinControl
  },

  {                          // FCH_HPET
    TRUE,                    // HpetEnable
    TRUE,                    // HpetMsiDis
    0xFED00000               // HpetBase
  },

  {                          // FCH_GCPU
    0,                       // AcDcMsg
    0,                       // TimerTickTrack
    0,                       // ClockInterruptTag
    0,                       // OhciTrafficHanding
    0,                       // EhciTrafficHanding
    0,                       // GcpuMsgCMultiCore
    0,                       // GcpuMsgCStage
  },

  {0},                       // FCH_IMC

  {                          // FCH_MISC
    TRUE,                   // NativePcieSupport
    FALSE,                   // S3Resume
    FALSE,                   // RebootRequired
    0,                       // FchVariant
    0,                       // CG2PLL
    {                        // TIMER_SMI-LongTimer
      FALSE,                 // Enable
      FALSE,                 // StartNow
      1000                   // CycleDuration
    },
    {                        // TIMER_SMI-ShortTimer
      FALSE,                 // Enable
      FALSE,                 // StartNow
      0x7FFF                 // CycleDuration
    },
    0,                       // FchCpuId
    FALSE,                   // NoneSioKbcSupport
    TRUE,                    // BpX48M0OutputEnable
    FALSE,                   // BpX48M0S0i3Enable
    {0},                     // FchCsSupport
  },

  {0, 0},                    // FCH_IOMUX

  NULL,                      // PostOemGpioTable

  {                          // FCH_EMMC
    0   ,                    // EmmcEnable
    TRUE,                    // EmmcEnablePnP0D40
    FALSE,                   // EmmcBoot
    TRUE,                    // EmmcAdma2Support
    TRUE,                    // EmmcAdmaSupport
    TRUE,                    // EmmcSdmaSupport
    TRUE,                    // EmmcA64bSupport
    TRUE,                    // EmmcD3Support
  },

  {                          // FCH_XGBE
    {{0}, {0}, {0}, {0},},   // Port[4]
    FALSE,                   // XgbeMdio0Enable
    FALSE,                   // XgbeMdio1Enable
    FALSE,                   // XgbeSfpEnable
    0,                       // MaxPortNum
   },


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
  NULL                       // FchResetDataBlock
};



