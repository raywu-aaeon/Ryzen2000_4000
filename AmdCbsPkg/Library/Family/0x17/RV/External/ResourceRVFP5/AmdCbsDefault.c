/*****************************************************************************
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
 **/


#include "AmdCbsVariable.h"

VOID
CbsWriteDefalutValue (
  IN UINT8 *IfrData
  )
{
  CBS_CONFIG *Setup_Config;

  Setup_Config = (CBS_CONFIG *)IfrData;
  Setup_Config->Header.NewRecordOffset = OFFSET_OF (CBS_CONFIG, Reserved);
  Setup_Config->CbsComboFlag = 254;                                     // Combo CBS
  Setup_Config->CbsCmnCpuGenWA05 = 0xFF;                                // RedirectForReturnDis
  Setup_Config->CbsCmnCpuL2TlbWayAlloc = 3;                             // L2 TLB Associativity
  Setup_Config->CbsCmnCpuPfeh = 3;                                      // Platform First Error Handling
  Setup_Config->CbsCmnCpuCpb = 1;                                       // Core Performance Boost
  Setup_Config->CbsCmnCpuGlobalCstateCtrl = 3;                          // Global C-state Control
  Setup_Config->CbsCmnCpuOcMode = 0;                                    // OC Mode
  Setup_Config->CbsCmnCpuStreamingStoresCtrl = 0xFF;                    // Streaming Stores Control
  Setup_Config->CbsCmnCpuEnIbs = 3;                                     // Enable IBS
  Setup_Config->CbsCpuLegalDisclaimer = 0;                              // Custom Core Pstates Legal Disclaimer
  Setup_Config->CbsCpuLegalDisclaimer1 = 0;                             // Custom Core Pstates Legal Disclaimer 1
  Setup_Config->CbsCpuPstCustomP0 = 2;                                  // Custom Pstate0
  Setup_Config->CbsCpuCofP0 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP0 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst0Fid = 16;                                     // Pstate0 FID
  Setup_Config->CbsCpuPst0Did = 8;                                      // Pstate0 DID
  Setup_Config->CbsCpuPst0Vid = 255;                                    // Pstate0 VID
  Setup_Config->CbsCpuPstCustomP1 = 2;                                  // Custom Pstate1
  Setup_Config->CbsCpuCofP1 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP1 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst1Fid = 16;                                     // Pstate1 FID
  Setup_Config->CbsCpuPst1Did = 8;                                      // Pstate1 DID
  Setup_Config->CbsCpuPst1Vid = 255;                                    // Pstate1 VID
  Setup_Config->CbsCpuPstCustomP2 = 2;                                  // Custom Pstate2
  Setup_Config->CbsCpuCofP2 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP2 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst2Fid = 16;                                     // Pstate2 FID
  Setup_Config->CbsCpuPst2Did = 8;                                      // Pstate2 DID
  Setup_Config->CbsCpuPst2Vid = 255;                                    // Pstate2 VID
  Setup_Config->CbsCpuPstCustomP3 = 2;                                  // Custom Pstate3
  Setup_Config->CbsCpuCofP3 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP3 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst3Fid = 16;                                     // Pstate3 FID
  Setup_Config->CbsCpuPst3Did = 8;                                      // Pstate3 DID
  Setup_Config->CbsCpuPst3Vid = 255;                                    // Pstate3 VID
  Setup_Config->CbsCpuPstCustomP4 = 2;                                  // Custom Pstate4
  Setup_Config->CbsCpuCofP4 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP4 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst4Fid = 16;                                     // Pstate4 FID
  Setup_Config->CbsCpuPst4Did = 8;                                      // Pstate4 DID
  Setup_Config->CbsCpuPst4Vid = 255;                                    // Pstate4 VID
  Setup_Config->CbsCpuPstCustomP5 = 2;                                  // Custom Pstate5
  Setup_Config->CbsCpuCofP5 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP5 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst5Fid = 16;                                     // Pstate5 FID
  Setup_Config->CbsCpuPst5Did = 8;                                      // Pstate5 DID
  Setup_Config->CbsCpuPst5Vid = 255;                                    // Pstate5 VID
  Setup_Config->CbsCpuPstCustomP6 = 2;                                  // Custom Pstate6
  Setup_Config->CbsCpuCofP6 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP6 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst6Fid = 16;                                     // Pstate6 FID
  Setup_Config->CbsCpuPst6Did = 8;                                      // Pstate6 DID
  Setup_Config->CbsCpuPst6Vid = 255;                                    // Pstate6 VID
  Setup_Config->CbsCpuPstCustomP7 = 2;                                  // Custom Pstate7
  Setup_Config->CbsCpuCofP7 = 0;                                        // Frequency (MHz)
  Setup_Config->CbsCpuVoltageP7 = 0;                                    // Voltage (uV)
  Setup_Config->CbsCpuPst7Fid = 16;                                     // Pstate7 FID
  Setup_Config->CbsCpuPst7Did = 8;                                      // Pstate7 DID
  Setup_Config->CbsCpuPst7Vid = 255;                                    // Pstate7 VID
  Setup_Config->CbsCpuRelaxedEdcThrottling = 3;                         // Relaxed EDC throttling
  Setup_Config->CbsCpuCoreThreadLegalDisclaimer = 0;                    // Core/Thread Enablement Legal Disclaimer
  Setup_Config->CbsCmnCpuGenDowncoreCtrl = 0;                           // Downcore control
  Setup_Config->CbsCmnCpuGenSmtEn = 0x1;                                // SMTEN
  Setup_Config->CbsDfCmnDramScrubTime = 0xFF;                           // DRAM scrub time
  Setup_Config->CbsDfCmnRedirScrubCtrl = 3;                             // Redirect scrubber control
  Setup_Config->CbsDfCmnSyncFloodProp = 3;                              // Disable DF sync flood propagation
  Setup_Config->CbsDfCmnGmiEncryption = 3;                              // GMI encryption control
  Setup_Config->CbsDfCmnXGmiEncryption = 3;                             // xGMI encryption control
  Setup_Config->CbsDfCmnCc6MemEncryption = 3;                           // CC6 memory region encryption
  Setup_Config->CbsDfCmnCc6AllocationScheme = 3;                        // Location of private memory regions
  Setup_Config->CbsDfCmnSysProbeFilter = 3;                             // System probe filter
  Setup_Config->CbsDfCmnMemIntlv = 7;                                   // Memory interleaving
  Setup_Config->CbsDfCmnMemIntlvSize = 7;                               // Memory interleaving size
  Setup_Config->CbsDfCmnChnlIntlvHash = 3;                              // Channel interleaving hash
  Setup_Config->CbsDfCmnCstateCtrl = 3;                                 // DF C-state control
  Setup_Config->CbsDfCmnxGmiDlwmCtrl = 3;                               // xGMI DLWM control
  Setup_Config->CbsDfCmnFreezeQueueError = 3;                           // Freeze DF module queues on error
  Setup_Config->CbsCmnMemTimingLegalDisclaimer = 0;                     // DRAM Timing Configuration Legal Disclaimer
  Setup_Config->CbsCmnMemTimingLegalDisclaimer1 = 0;                    // DRAM Timing Configuration Legal Disclaimer 1
  Setup_Config->CbsCmnMemOverclockDdr4 = 0xFF;                          // Overclock
  Setup_Config->CbsCmnMemSpeedDdr4 = 0xFF;                              // Memory Clock Speed
  Setup_Config->CbsCmnMemTimingTclDdr4 = 0xFF;                          // Tcl
  Setup_Config->CbsCmnMemTimingTrcdrdDdr4 = 0xFF;                       // Trcdrd
  Setup_Config->CbsCmnMemTimingTrcdwrDdr4 = 0xFF;                       // Trcdwr
  Setup_Config->CbsCmnMemTimingTrpDdr4 = 0xFF;                          // Trp
  Setup_Config->CbsCmnMemTimingTrasDdr4 = 0xFF;                         // Tras
  Setup_Config->CbsCmnMemTimingTrcCtrlDdr4 = 0;                         // Trc Ctrl
  Setup_Config->CbsCmnMemTimingTrcDdr4 = 0x39;                          // Trc
  Setup_Config->CbsCmnMemTimingTrrdSDdr4 = 0xFF;                        // TrrdS
  Setup_Config->CbsCmnMemTimingTrrdLDdr4 = 0xFF;                        // TrrdL
  Setup_Config->CbsCmnMemTimingTfawCtrlDdr4 = 0;                        // Tfaw Ctrl
  Setup_Config->CbsCmnMemTimingTfawDdr4 = 26;                           // Tfaw
  Setup_Config->CbsCmnMemTimingTwtrSDdr4 = 0xFF;                        // TwtrS
  Setup_Config->CbsCmnMemTimingTwtrLDdr4 = 0xFF;                        // TwtrL
  Setup_Config->CbsCmnMemTimingTwrCtrlDdr4 = 0;                         // Twr Ctrl
  Setup_Config->CbsCmnMemTimingTwrDdr4 = 18;                            // Twr
  Setup_Config->CbsCmnMemTimingTrcpageCtrlDdr4 = 0;                     // Trcpage Ctrl
  Setup_Config->CbsCmnMemTimingTrcpageDdr4 = 0;                         // Trcpage
  Setup_Config->CbsCmnMemTimingTrdrdScLCtrlDdr4 = 0;                    // TrdrdScL Ctrl
  Setup_Config->CbsCmnMemTimingTrdrdScLDdr4 = 3;                        // TrdrdScL
  Setup_Config->CbsCmnMemTimingTwrwrScLCtrlDdr4 = 0;                    // TwrwrScL Ctrl
  Setup_Config->CbsCmnMemTimingTwrwrScLDdr4 = 0x3;                      // TwrwrScL
  Setup_Config->CbsCmnMemTimingTrfcCtrlDdr4 = 0;                        // Trfc Ctrl
  Setup_Config->CbsCmnMemTimingTrfcDdr4 = 0x138;                        // Trfc
  Setup_Config->CbsCmnMemTimingTrfc2CtrlDdr4 = 0;                       // Trfc2 Ctrl
  Setup_Config->CbsCmnMemTimingTrfc2Ddr4 = 0xC0;                        // Trfc2
  Setup_Config->CbsCmnMemTimingTrfc4CtrlDdr4 = 0;                       // Trfc4 Ctrl
  Setup_Config->CbsCmnMemTimingTrfc4Ddr4 = 0x84;                        // Trfc4
  Setup_Config->CbsCmnMemOverclockFailCNT = 5;                          // Fail_CNT
  Setup_Config->CbsCmnMemCtrllerProcOdtDdr4 = 0xFF;                     // ProcODT
  Setup_Config->CbsCmnMemTimingTcwlDdr4 = 0xFF;                         // Tcwl
  Setup_Config->CbsCmnMemTimingTrtpDdr4 = 0xFF;                         // Trtp
  Setup_Config->CbsCmnMemTimingTckeDdr4 = 0xFF;                         // Tcke
  Setup_Config->CbsCmnMemTimingTrdrdScDdr4 = 0xFF;                      // TrdrdSc
  Setup_Config->CbsCmnMemTimingTrdrdSdDdr4 = 0xFF;                      // TrdrdSd
  Setup_Config->CbsCmnMemTimingTrdrdDdDdr4 = 0xFF;                      // TrdrdDd
  Setup_Config->CbsCmnMemTimingTwrwrScDdr4 = 0xFF;                      // TwrwrSc
  Setup_Config->CbsCmnMemTimingTwrwrSdDdr4 = 0xFF;                      // TwrwrSd
  Setup_Config->CbsCmnMemTimingTwrwrDdDdr4 = 0xFF;                      // TwrwrDd
  Setup_Config->CbsCmnMemTimingTrdwrDdr4 = 0xFF;                        // Trdwr
  Setup_Config->CbsCmnMemTimingTwrrdDdr4 = 0xFF;                        // Twrrd
  Setup_Config->CbsCmnMemCtrller2TModeDdr4 = 0xFF;                      // Cmd2T
  Setup_Config->CbsCmnMemGearDownModeDdr4 = 0xFF;                       // Gear Down Mode
  Setup_Config->CbsCmnMemDataMaskDdr4 = 0xFF;                           // Data Mask
  Setup_Config->CbsCmnMemCtrllerPwrDnEnDdr4 = 0xFF;                     // Power Down Enable
  Setup_Config->CbsCmnMemCadBusTimingCtlDdr4 = 0xFF;                    // CAD Bus Timing User Controls
  Setup_Config->CbsCmnMemAddrCmdSetupDdr4 = 0;                          // AddrCmdSetup
  Setup_Config->CbsCmnMemCsOdtSetupDdr4 = 0;                            // CsOdtSetup
  Setup_Config->CbsCmnMemCkeSetupDdr4 = 0;                              // CkeSetup
  Setup_Config->CbsCmnMemCadBusDrvStrenCtlDdr4 = 0xFF;                  // CAD Bus Drive Strength User Controls
  Setup_Config->CbsCmnMemCadBusClkDrvStrenDdr4 = 0xFF;                  // ClkDrvStren
  Setup_Config->CbsCmnMemCadBusAddrCmdDrvStrenDdr4 = 0xFF;              // AddrCmdDrvStren
  Setup_Config->CbsCmnMemCadBusCsOdtDrvStrenDdr4 = 0xFF;                // CsOdtDrvStren
  Setup_Config->CbsCmnMemCadBusCkeDrvStrenDdr4 = 0xFF;                  // CkeDrvStren
  Setup_Config->CbsCmnMemDataBusConfigCtlDdr4 = 0xFF;                   // Data Bus Configuration User Controls
  Setup_Config->CbsCmnMemCtrllerRttNomDdr4 = 0xFF;                      // RttNom
  Setup_Config->CbsCmnMemCtrllerRttWrDdr4 = 0xFF;                       // RttWr
  Setup_Config->CbsCmnMemCtrllerRttParkDdr4 = 0xFF;                     // RttPark
  Setup_Config->CbsCmnMemDataPoisoningDdr4 = 0xFF;                      // Data Poisoning
  Setup_Config->CbsCmnMemCtrllerDramEccSymbolSizeDdr4 = 0xFF;           // DRAM ECC Symbol Size
  Setup_Config->CbsCmnMemCtrllerDramEccEnDdr4 = 0xFF;                   // DRAM ECC Enable
  Setup_Config->CbsCmnMemTsmeDdr4 = 0xFF;                               // TSME
  Setup_Config->CbsCmnMemMappingBankInterleaveDdr4 = 0xFF;              // Chipselect Interleaving
  Setup_Config->CbsCmnMemCtrllerBankGroupSwapDdr4 = 0xFF;               // BankGroupSwap
  Setup_Config->CbsCmnMemCtrllerBankGroupSwapAltDdr4 = 0xFF;            // BankGroupSwapAlt
  Setup_Config->CbsCmnMemAddressHashBankDdr4 = 0xFF;                    // Address Hash Bank
  Setup_Config->CbsCmnMemAddressHashCsDdr4 = 0xFF;                      // Address Hash CS
  Setup_Config->CbsCmnMemMbistEn = 0xFF;                                // MBIST Enable
  Setup_Config->CbsCmnMemMbistSubTest = 0xFF;                           // MBIST Test Mode
  Setup_Config->CbsCmnMemMbistAggressors = 0xFF;                        // MBIST Aggressors
  Setup_Config->CbsCmnMemMbistPerBitSlaveDieReporting = 0xFF;           // MBIST Per Bit Slave Die Reporting
  Setup_Config->CbsCmnGnbSMUSystemConfig = 0xf;                         // System Configuration
  Setup_Config->CbsDbgGnbAudioIOs = 0xF;                                // Audio IOs
  Setup_Config->CbsCmnSystemTemperatureTracking = 0xF;                  // System Temperature Tracking
  Setup_Config->CbsCmnGnbGfxiGPU_CONTROL = 0xf;                         // Integrated Graphics Controller
  Setup_Config->CbsCmnGnbGfxUmaMode = 0xf;                              // UMA Mode
  Setup_Config->CbsCmnGnbGfxUmaVersion = 0xf;                           // UMA Version
  Setup_Config->CbsCmnGnbGfxDisplayResolution = 0xff;                   // Display Resulotuon
  Setup_Config->CbsCmnGnbGfxUmaFrameBufferSize = 0xffffffff;            // UMA Frame buffer Size
  Setup_Config->CbsCmnGnbGfxNbAzalia = 0xf;                             // NB Azalia
  Setup_Config->CbsCmnGnbNbIOMMU = 0xf;                                 // IOMMU
  Setup_Config->CbsCmnGnbPciePsppPolicy = 0xf;                          // PSPP Policy
  Setup_Config->CbsDbgFanCtl = 0;                                       // Fan Control
  Setup_Config->CbsDbgForcePwmCtl = 0;                                  // Force PWM Control
  Setup_Config->CbsDbgForcePwm = 0;                                     // Force PWM
  Setup_Config->CbsDbgFanTableCtl = 0;                                  // Fan Table Control
  Setup_Config->CbsDbgFanTableTempLow = 0;                              // Low Temperature
  Setup_Config->CbsDbgFanTableTempMed = 0;                              // Medium Temperature
  Setup_Config->CbsDbgFanTableTempHigh = 0;                             // High Temperature
  Setup_Config->CbsDbgFanTableTempCritical = 0;                         // Critical Temperature
  Setup_Config->CbsDbgFanTableTPwmLow = 0;                              // Low Pwm
  Setup_Config->CbsDbgFanTablePwmMed = 0;                               // Medium Pwm
  Setup_Config->CbsDbgFanTablePwmHigh = 0;                              // High Pwm
  Setup_Config->CbsDbgFanTableHyst = 0;                                 // Temperature Hysteresis
  Setup_Config->CbsDbgFanTablePwmFreq = 0;                              // Pwm Frequency
  Setup_Config->CbsDbgFanPolarity = 0;                                  // Fan Polarity
  Setup_Config->CbsCmnFchSataEnable = 0xf;                              // SATA Controller
  Setup_Config->CbsCmnFchSataClass = 0xf;                               // SATA Mode
  Setup_Config->CbsCmnFchSataRasSupport = 0xf;                          // Sata RAS Support
  Setup_Config->CbsCmnFchSataAhciDisPrefetchFunction = 0xf;             // Sata Disabled AHCI Prefetch Function
  Setup_Config->CbsDbgFchSataAggresiveDevSlpP0 = 0xF;                   // Aggresive SATA Device Sleep Port 0
  Setup_Config->CbsDbgFchSataAggresiveDevSlpP1 = 0xF;                   // Aggresive SATA Device Sleep Port 1
  Setup_Config->CbsCmnFchUsbXHCI0Enable = 0xf;                          // XHCI0 controller enable
  Setup_Config->CbsCmnFchUsbXHCI1Enable = 0xf;                          // XHCI1 controller enable
  Setup_Config->CbsCmnFchSystemPwrFailShadow = 3;                       // Ac Loss Control
  Setup_Config->CbsCmnFchI2C0Config = 0xf;                              // I2C 0 Enable
  Setup_Config->CbsCmnFchI2C1Config = 0xf;                              // I2C 1 Enable
  Setup_Config->CbsCmnFchI2C2Config = 0xf;                              // I2C 2 Enable
  Setup_Config->CbsCmnFchI2C3Config = 0xf;                              // I2C 3 Enable
  Setup_Config->CbsCmnFchI2C4Config = 0xf;                              // I2C 4 Enable
  Setup_Config->CbsCmnFchI2C5Config = 0xf;                              // I2C 5 Enable
  Setup_Config->CbsCmnFchUart0Config = 0xf;                             // Uart 0 Enable
  Setup_Config->CbsCmnFchUart0LegacyConfig = 0xf;                       // Uart 0 Legacy Options
  Setup_Config->CbsCmnFchUart1Config = 0xf;                             // Uart 1 Enable
  Setup_Config->CbsCmnFchUart1LegacyConfig = 0xf;                       // Uart 1 Legacy Options
  Setup_Config->CbsCmnFchUart2Config = 0xf;                             // Uart 2 Enable (no HW FC)
  Setup_Config->CbsCmnFchUart2LegacyConfig = 0xf;                       // Uart 2 Legacy Options
  Setup_Config->CbsCmnFchUart3Config = 0xf;                             // Uart 3 Enable (no HW FC)
  Setup_Config->CbsCmnFchUart3LegacyConfig = 0xf;                       // Uart 3 Legacy Options
  Setup_Config->CbsCmnFchEspiConfig = 0xf;                              // ESPI Enable
  Setup_Config->CbsCmnFchXgbe0Enable = 0xf;                             // XGBE0 enable
  Setup_Config->CbsCmnFchXgbe1Enable = 0xf;                             // XGBE1 enable
  Setup_Config->CbsDbgFchEmmcEnable = 0xf;                              // eMMC/SD Configure
  Setup_Config->CbsDbgFchEmmcDriverType = 0xf;                          // Driver Type
  Setup_Config->CbsDbgFchEmmcD3Support = 0xf;                           // D3 Cold Support
  Setup_Config->CbsDbgFchEmmcBoot = 0xf;                                // eMMC Boot
  Setup_Config->CbsCmnFchLpcClockRunEn = 0xf;                           // LPC Clock Run control
  Setup_Config->CbsCmnToggleAllPwrGoodOnCf9 = 2;                        // Toggle All PwrGood On Cf9
  Setup_Config->CbsCmnPTSataClass = 0xf;                                // PT SATA Mode
  Setup_Config->CbsDbgPTSataAggresiveDevSlpP0 = 0xF;                    // PT Aggresive SATA Device Sleep Port 0
  Setup_Config->CbsDbgPTSataAggresiveDevSlpP1 = 0xF;                    // PT Aggresive SATA Device Sleep Port 1
  Setup_Config->CbsCmnPTSataPort0Enable = 0xf;                          // PT SATA Port 0 Enable
  Setup_Config->CbsCmnPTSataPort1Enable = 0xf;                          // PT SATA Port 1 Enable
  Setup_Config->CbsCmnPTSataPort2Enable = 0xf;                          // PT SATA Port 2 Enable
  Setup_Config->CbsCmnPTSataPort3Enable = 0xf;                          // PT SATA Port 3 Enable
  Setup_Config->CbsCmnPTSataPort4Enable = 0xf;                          // PT SATA Port 4 Enable
  Setup_Config->CbsCmnPTSataPort5Enable = 0xf;                          // PT SATA Port 5 Enable
  Setup_Config->CbsCmnPTSataPort6Enable = 0xf;                          // PT SATA Port 6 Enable
  Setup_Config->CbsCmnPTSataPort7Enable = 0xf;                          // PT SATA Port 7 Enable
  Setup_Config->CbsDbgPTXhciGen1 = 0xF;                                 // PT XHCI GEN1
  Setup_Config->CbsDbgPTXhciGen2 = 0xF;                                 // PT XHCI GEN2
  Setup_Config->CbsDbgPTUsbEqualization4 = 0xF;                         // PT USB Equalization4
  Setup_Config->CbsDbgPTUsbRedriver = 0xF;                              // PT USB Redriver
  Setup_Config->CbsDbgPTUsb31P0 = 0xF;                                  // PT USB31 PORT0
  Setup_Config->CbsDbgPTUsb31P1 = 0xF;                                  // PT USB31 PORT1
  Setup_Config->CbsDbgPTUsb30P0 = 0xF;                                  // PT USB30 PORT0
  Setup_Config->CbsDbgPTUsb30P1 = 0xF;                                  // PT USB30 PORT1
  Setup_Config->CbsDbgPTUsb30P2 = 0xF;                                  // PT USB30 PORT2
  Setup_Config->CbsDbgPTUsb30P3 = 0xF;                                  // PT USB30 PORT3
  Setup_Config->CbsDbgPTUsb30P4 = 0xF;                                  // PT USB30 PORT4
  Setup_Config->CbsDbgPTUsb30P5 = 0xF;                                  // PT USB30 PORT5
  Setup_Config->CbsDbgPTUsb20P0 = 0xF;                                  // PT USB20 PORT0
  Setup_Config->CbsDbgPTUsb20P1 = 0xF;                                  // PT USB20 PORT1
  Setup_Config->CbsDbgPTUsb20P2 = 0xF;                                  // PT USB20 PORT2
  Setup_Config->CbsDbgPTUsb20P3 = 0xF;                                  // PT USB20 PORT3
  Setup_Config->CbsDbgPTUsb20P4 = 0xF;                                  // PT USB20 PORT4
  Setup_Config->CbsDbgPTUsb20P5 = 0xF;                                  // PT USB20 PORT5
  Setup_Config->CbsDbgPTProm2Usb31P0 = 0xF;                             // PT USB31 PORT0
  Setup_Config->CbsDbgPTProm2Usb31P1 = 0xF;                             // PT USB31 PORT1
  Setup_Config->CbsDbgPTProm2Usb30P0 = 0xF;                             // PT USB30 PORT0
  Setup_Config->CbsDbgPTProm2Usb30P1 = 0xF;                             // PT USB30 PORT1
  Setup_Config->CbsDbgPTProm2Usb20P0 = 0xF;                             // PT USB20 PORT0
  Setup_Config->CbsDbgPTProm2Usb20P1 = 0xF;                             // PT USB20 PORT1
  Setup_Config->CbsDbgPTProm2Usb20P2 = 0xF;                             // PT USB20 PORT2
  Setup_Config->CbsDbgPTProm2Usb20P3 = 0xF;                             // PT USB20 PORT3
  Setup_Config->CbsDbgPTProm2Usb20P4 = 0xF;                             // PT USB20 PORT4
  Setup_Config->CbsDbgPTProm2Usb20P5 = 0xF;                             // PT USB20 PORT5
  Setup_Config->CbsDbgPTProm1Usb31P0 = 0xF;                             // PT USB31 PORT0
  Setup_Config->CbsDbgPTProm1Usb31P1 = 0xF;                             // PT USB31 PORT1
  Setup_Config->CbsDbgPTProm1Usb30P0 = 0xF;                             // PT USB30 PORT0
  Setup_Config->CbsDbgPTProm1Usb20P0 = 0xF;                             // PT USB20 PORT0
  Setup_Config->CbsDbgPTProm1Usb20P1 = 0xF;                             // PT USB20 PORT1
  Setup_Config->CbsDbgPTProm1Usb20P2 = 0xF;                             // PT USB20 PORT2
  Setup_Config->CbsDbgPTProm1Usb20P3 = 0xF;                             // PT USB20 PORT3
  Setup_Config->CbsDbgPTProm1Usb20P4 = 0xF;                             // PT USB20 PORT4
  Setup_Config->CbsDbgPTProm1Usb20P5 = 0xF;                             // PT USB20 PORT5
  Setup_Config->CbsCmnPTPciePort0Enable = 0xf;                          // PT PCIE Port 0 Enable
  Setup_Config->CbsCmnPTPciePort1Enable = 0xf;                          // PT PCIE Port 1 Enable
  Setup_Config->CbsCmnPTPciePort2Enable = 0xf;                          // PT PCIE Port 2 Enable
  Setup_Config->CbsCmnPTPciePort3Enable = 0xf;                          // PT PCIE Port 3 Enable
  Setup_Config->CbsCmnPTPciePort4Enable = 0xf;                          // PT PCIE Port 4 Enable
  Setup_Config->CbsCmnPTPciePort5Enable = 0xf;                          // PT PCIE Port 5 Enable
  Setup_Config->CbsCmnPTPciePort6Enable = 0xf;                          // PT PCIE Port 6 Enable
  Setup_Config->CbsCmnPTPciePort7Enable = 0xf;                          // PT PCIE Port 7 Enable
  Setup_Config->Header.CbsVariableStructUniqueValue = 0xae574f83;

}

