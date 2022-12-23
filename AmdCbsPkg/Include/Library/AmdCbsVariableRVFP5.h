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
 ***************************************************************************/


#ifndef _AMD_CBS_VARIABLE_H_
#define _AMD_CBS_VARIABLE_H_

#pragma pack(push,1)

typedef struct _CBS_VARIABLE_HEADER
{
  UINT32 CbsVariableStructUniqueValue;                                 ///< Will be different if CBS varialbe structure changes
  UINT32 NewRecordOffset;                                         ///< Record the offset of reserved region start, which also the offset of the new record
  UINT8  Reserved[24];                                            ///< Reserved for future use
} CBS_VARIABLE_HEADER;


typedef struct _CBS_CONFIG {
  CBS_VARIABLE_HEADER  Header;                                    ///< Variable header
  UINT8         CbsComboFlag;                                     ///< Combo CBS
  UINT8         CbsCmnCpuGenWA05;                                 ///< RedirectForReturnDis
  UINT8         CbsCmnCpuL2TlbWayAlloc;                           ///< L2 TLB Associativity
  UINT8         CbsCmnCpuPfeh;                                    ///< Platform First Error Handling
  UINT8         CbsCmnCpuCpb;                                     ///< Core Performance Boost
  UINT8         CbsCmnCpuGlobalCstateCtrl;                        ///< Global C-state Control
  UINT8         CbsCmnCpuOcMode;                                  ///< OC Mode
  UINT8         CbsCmnCpuStreamingStoresCtrl;                     ///< Streaming Stores Control
  UINT8         CbsCmnCpuEnIbs;                                   ///< Enable IBS
  UINT8         CbsCpuLegalDisclaimer;                            ///< Custom Core Pstates Legal Disclaimer
  UINT8         CbsCpuLegalDisclaimer1;                           ///< Custom Core Pstates Legal Disclaimer 1
  UINT8         CbsCpuPstCustomP0;                                ///< Custom Pstate0
  UINT32        CbsCpuCofP0;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP0;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst0Fid;                                    ///<   Pstate0 FID
  UINT8         CbsCpuPst0Did;                                    ///<   Pstate0 DID
  UINT8         CbsCpuPst0Vid;                                    ///<   Pstate0 VID
  UINT8         CbsCpuPstCustomP1;                                ///< Custom Pstate1
  UINT32        CbsCpuCofP1;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP1;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst1Fid;                                    ///<   Pstate1 FID
  UINT8         CbsCpuPst1Did;                                    ///<   Pstate1 DID
  UINT8         CbsCpuPst1Vid;                                    ///<   Pstate1 VID
  UINT8         CbsCpuPstCustomP2;                                ///< Custom Pstate2
  UINT32        CbsCpuCofP2;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP2;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst2Fid;                                    ///<   Pstate2 FID
  UINT8         CbsCpuPst2Did;                                    ///<   Pstate2 DID
  UINT8         CbsCpuPst2Vid;                                    ///<   Pstate2 VID
  UINT8         CbsCpuPstCustomP3;                                ///< Custom Pstate3
  UINT32        CbsCpuCofP3;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP3;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst3Fid;                                    ///<   Pstate3 FID
  UINT8         CbsCpuPst3Did;                                    ///<   Pstate3 DID
  UINT8         CbsCpuPst3Vid;                                    ///<   Pstate3 VID
  UINT8         CbsCpuPstCustomP4;                                ///< Custom Pstate4
  UINT32        CbsCpuCofP4;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP4;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst4Fid;                                    ///<   Pstate4 FID
  UINT8         CbsCpuPst4Did;                                    ///<   Pstate4 DID
  UINT8         CbsCpuPst4Vid;                                    ///<   Pstate4 VID
  UINT8         CbsCpuPstCustomP5;                                ///< Custom Pstate5
  UINT32        CbsCpuCofP5;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP5;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst5Fid;                                    ///<   Pstate5 FID
  UINT8         CbsCpuPst5Did;                                    ///<   Pstate5 DID
  UINT8         CbsCpuPst5Vid;                                    ///<   Pstate5 VID
  UINT8         CbsCpuPstCustomP6;                                ///< Custom Pstate6
  UINT32        CbsCpuCofP6;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP6;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst6Fid;                                    ///<   Pstate6 FID
  UINT8         CbsCpuPst6Did;                                    ///<   Pstate6 DID
  UINT8         CbsCpuPst6Vid;                                    ///<   Pstate6 VID
  UINT8         CbsCpuPstCustomP7;                                ///< Custom Pstate7
  UINT32        CbsCpuCofP7;                                      ///<   Frequency (MHz)
  UINT32        CbsCpuVoltageP7;                                  ///<   Voltage (uV)
  UINT8         CbsCpuPst7Fid;                                    ///<   Pstate7 FID
  UINT8         CbsCpuPst7Did;                                    ///<   Pstate7 DID
  UINT8         CbsCpuPst7Vid;                                    ///<   Pstate7 VID
  UINT8         CbsCpuRelaxedEdcThrottling;                       ///< Relaxed EDC throttling
  UINT8         CbsCpuCoreThreadLegalDisclaimer;                  ///< Core/Thread Enablement Legal Disclaimer
  UINT8         CbsCmnCpuGenDowncoreCtrl;                         ///< Downcore control
  UINT8         CbsCmnCpuGenSmtEn;                                ///< SMTEN
  UINT8         CbsDfCmnDramScrubTime;                            ///< DRAM scrub time
  UINT8         CbsDfCmnRedirScrubCtrl;                           ///< Redirect scrubber control
  UINT8         CbsDfCmnSyncFloodProp;                            ///< Disable DF sync flood propagation
  UINT8         CbsDfCmnGmiEncryption;                            ///< GMI encryption control
  UINT8         CbsDfCmnXGmiEncryption;                           ///< xGMI encryption control
  UINT8         CbsDfCmnCc6MemEncryption;                         ///< CC6 memory region encryption
  UINT8         CbsDfCmnCc6AllocationScheme;                      ///< Location of private memory regions
  UINT8         CbsDfCmnSysProbeFilter;                           ///< System probe filter
  UINT8         CbsDfCmnMemIntlv;                                 ///< Memory interleaving
  UINT8         CbsDfCmnMemIntlvSize;                             ///< Memory interleaving size
  UINT8         CbsDfCmnChnlIntlvHash;                            ///< Channel interleaving hash
  UINT8         CbsDfCmnCstateCtrl;                               ///< DF C-state control
  UINT8         CbsDfCmnxGmiDlwmCtrl;                             ///< xGMI DLWM control
  UINT8         CbsDfCmnFreezeQueueError;                         ///< Freeze DF module queues on error
  UINT8         CbsCmnMemTimingLegalDisclaimer;                   ///< DRAM Timing Configuration Legal Disclaimer
  UINT8         CbsCmnMemTimingLegalDisclaimer1;                  ///< DRAM Timing Configuration Legal Disclaimer 1
  UINT8         CbsCmnMemOverclockDdr4;                           ///< Overclock
  UINT8         CbsCmnMemSpeedDdr4;                               ///< Memory Clock Speed
  UINT8         CbsCmnMemTimingTclDdr4;                           ///< Tcl
  UINT8         CbsCmnMemTimingTrcdrdDdr4;                        ///< Trcdrd
  UINT8         CbsCmnMemTimingTrcdwrDdr4;                        ///< Trcdwr
  UINT8         CbsCmnMemTimingTrpDdr4;                           ///< Trp
  UINT8         CbsCmnMemTimingTrasDdr4;                          ///< Tras
  UINT8         CbsCmnMemTimingTrcCtrlDdr4;                       ///< Trc Ctrl
  UINT8         CbsCmnMemTimingTrcDdr4;                           ///< Trc
  UINT8         CbsCmnMemTimingTrrdSDdr4;                         ///< Trrds
  UINT8         CbsCmnMemTimingTrrdLDdr4;                         ///< TrrdL
  UINT8         CbsCmnMemTimingTfawCtrlDdr4;                      ///< Tfaw Ctrl
  UINT8         CbsCmnMemTimingTfawDdr4;                          ///< Tfaw
  UINT8         CbsCmnMemTimingTwtrSDdr4;                         ///< TwtrS
  UINT8         CbsCmnMemTimingTwtrLDdr4;                         ///< TwtrL
  UINT8         CbsCmnMemTimingTwrCtrlDdr4;                       ///< Twr Ctrl
  UINT8         CbsCmnMemTimingTwrDdr4;                           ///< Twr
  UINT8         CbsCmnMemTimingTrcpageCtrlDdr4;                   ///< Trcpage Ctrl
  UINT16        CbsCmnMemTimingTrcpageDdr4;                       ///< Trcpage
  UINT8         CbsCmnMemTimingTrdrdScLCtrlDdr4;                  ///< TrdrdScL Ctrl
  UINT8         CbsCmnMemTimingTrdrdScLDdr4;                      ///< TrdrdScL
  UINT8         CbsCmnMemTimingTwrwrScLCtrlDdr4;                  ///< TwrwrScL Ctrl
  UINT8         CbsCmnMemTimingTwrwrScLDdr4;                      ///< TwrwrScL
  UINT8         CbsCmnMemTimingTrfcCtrlDdr4;                      ///< Trfc Ctrl
  UINT16        CbsCmnMemTimingTrfcDdr4;                          ///< Trfc
  UINT8         CbsCmnMemTimingTrfc2CtrlDdr4;                     ///< Trfc2 Ctrl
  UINT16        CbsCmnMemTimingTrfc2Ddr4;                         ///< Trfc2
  UINT8         CbsCmnMemTimingTrfc4CtrlDdr4;                     ///< Trfc4 Ctrl
  UINT16        CbsCmnMemTimingTrfc4Ddr4;                         ///< Trfc4
  UINT8         CbsCmnMemOverclockFailCNT;                        ///< Fail_CNT
  UINT8         CbsCmnMemCtrllerProcOdtDdr4;                      ///< ProcODT
  UINT8         CbsCmnMemTimingTcwlDdr4;                          ///< Tcwl
  UINT8         CbsCmnMemTimingTrtpDdr4;                          ///< Trtp
  UINT8         CbsCmnMemDataPoisoningDdr4;                       ///< Data Poisoning
  UINT8         CbsCmnMemTsmeDdr4;                                ///< TSME
  UINT8         CbsCmnMemMappingBankInterleaveDdr4;               ///< Chipselect Interleaving
  UINT8         CbsCmnMemCtrllerBankGroupSwapDdr4;                ///< BankGroupSwap
  UINT8         CbsCmnMemAddressHashBankDdr4;                     ///< Address Hash Bank
  UINT8         CbsCmnMemAddressHashCsDdr4;                       ///< Address Hash CS
  UINT8         CbsCmnMemMbistEn;                                 ///< MBIST Enable
  UINT8         CbsCmnMemMbistSubTest;                            ///< MBIST Test Mode
  UINT8         CbsCmnMemMbistAggressors;                         ///< MBIST Aggressors
  UINT8         CbsCmnMemMbistPerBitSlaveDieReporting;            ///< MBIST Per Bit Slave Die Reporting
  UINT8         CbsCmnGnbSMUSystemConfig;                         ///< System Configuration
  UINT8         CbsDbgGnbAudioIOs;                                ///< Audio IOs
  UINT8         CbsCmnGnbGfxiGPU_CONTROL;                         ///< Integrated Graphics Controller
  UINT8         CbsCmnGnbGfxUmaMode;                              ///< UMA Mode
  UINT8         CbsCmnGnbGfxUmaVersion;                           ///< UMA Version
  UINT8         CbsCmnGnbGfxDisplayResolution;                    ///< Display Resulotuon
  UINT32        CbsCmnGnbGfxUmaFrameBufferSize;                   ///< UMA Frame buffer Size
  UINT8         CbsCmnGnbGfxNbAzalia;                             ///< NB Azalia
  UINT8         CbsCmnGnbNbIOMMU;                                 ///< IOMMU
  UINT8         CbsCmnGnbPciePsppPolicy;                          ///< PSPP Policy
  UINT8         CbsDbgFanCtl;                                     ///< Fan Control
  UINT8         CbsDbgForcePwmCtl;                                ///< Force PWM Control
  UINT8         CbsDbgForcePwm;                                   ///< Force PWM
  UINT8         CbsDbgFanTableCtl;                                ///< Fan Table Control
  UINT8         CbsDbgFanTableTempLow;                            ///< Low Temperature
  UINT8         CbsDbgFanTableTempMed;                            ///< Medium Temperature
  UINT8         CbsDbgFanTableTempHigh;                           ///< High Temperature
  UINT8         CbsDbgFanTableTempCritical;                       ///< Critical Temperature
  UINT8         CbsDbgFanTableTPwmLow;                            ///< Low Pwm
  UINT8         CbsDbgFanTablePwmMed;                             ///< Medium Pwm
  UINT8         CbsDbgFanTablePwmHigh;                            ///< High Pwm
  UINT8         CbsDbgFanTableHyst;                               ///< Temperature Hysteresis
  UINT8         CbsDbgFanTablePwmFreq;                            ///< Pwm Frequency
  UINT8         CbsDbgFanPolarity;                                ///< Fan Polarity
  UINT8         CbsCmnFchSataEnable;                              ///< SATA Controller
  UINT8         CbsCmnFchSataClass;                               ///< SATA Mode
  UINT8         CbsCmnFchSataRasSupport;                          ///< Sata RAS Support
  UINT8         CbsCmnFchSataAhciDisPrefetchFunction;             ///< Sata Disabled AHCI Prefetch Function
  UINT8         CbsDbgFchSataAggresiveDevSlpP0;                   ///< Aggresive SATA Device Sleep Port 0
  UINT8         CbsDbgFchSataAggresiveDevSlpP1;                   ///< Aggresive SATA Device Sleep Port 1
  UINT8         CbsCmnFchUsbXHCI0Enable;                          ///< XHCI0 controller enable
  UINT8         CbsCmnFchUsbXHCI1Enable;                          ///< XHCI1 controller enable
  UINT8         CbsCmnFchSdConfig_RsvDeleted;                     ///< SD Configuration Mode
  UINT8         CbsCmnFchSystemPwrFailShadow;                     ///< Ac Loss Control
  UINT8         CbsCmnFchI2C0Config;                              ///< I2C 0 Enable
  UINT8         CbsCmnFchI2C1Config;                              ///< I2C 1 Enable
  UINT8         CbsCmnFchI2C2Config;                              ///< I2C 2 Enable
  UINT8         CbsCmnFchI2C3Config;                              ///< I2C 3 Enable
  UINT8         CbsCmnFchI2C4Config;                              ///< I2C 4 Enable
  UINT8         CbsCmnFchI2C5Config;                              ///< I2C 5 Enable
  UINT8         CbsCmnFchUart0Config;                             ///< Uart 0 Enable
  UINT8         CbsCmnFchUart0LegacyConfig;                       ///< Uart 0 Legacy Options
  UINT8         CbsCmnFchUart1Config;                             ///< Uart 1 Enable
  UINT8         CbsCmnFchUart1LegacyConfig;                       ///< Uart 1 Legacy Options
  UINT8         CbsCmnFchUart2Config;                             ///< Uart 2 Enable (no HW FC)
  UINT8         CbsCmnFchUart2LegacyConfig;                       ///< Uart 2 Legacy Options
  UINT8         CbsCmnFchUart3Config;                             ///< Uart 3 Enable (no HW FC)
  UINT8         CbsCmnFchUart3LegacyConfig;                       ///< Uart 3 Legacy Options
  UINT8         CbsCmnFchEspiConfig;                              ///< ESPI Enable
  UINT8         CbsDbgFchEmmcEnable;                              ///< eMMC/SD Configure
  UINT8         CbsDbgFchEmmcDriverType;                          ///< Driver Type
  UINT8         CbsDbgFchEmmcD3Support;                           ///< D3 Cold Support
  UINT8         CbsDbgFchEmmcBoot;                                ///< eMMC Boot 
  UINT8         CbsCmnFchLpcClockRunEn;                           ///< LPC Clock Run control
  UINT8         CbsCmnPTSataClass;                                ///< PT SATA Mode
  UINT8         CbsDbgPTSataAggresiveDevSlpP0;                    ///< PT Aggresive SATA Device Sleep Port 0
  UINT8         CbsDbgPTSataAggresiveDevSlpP1;                    ///< PT Aggresive SATA Device Sleep Port 1
  UINT8         CbsCmnPTSataPort0Enable;                          ///< PT SATA Port 0 Enable
  UINT8         CbsCmnPTSataPort1Enable;                          ///< PT SATA Port 1 Enable
  UINT8         CbsCmnPTSataPort2Enable;                          ///< PT SATA Port 2 Enable
  UINT8         CbsCmnPTSataPort3Enable;                          ///< PT SATA Port 3 Enable
  UINT8         CbsCmnPTSataPort4Enable;                          ///< PT SATA Port 4 Enable
  UINT8         CbsCmnPTSataPort5Enable;                          ///< PT SATA Port 5 Enable
  UINT8         CbsCmnPTSataPort6Enable;                          ///< PT SATA Port 6 Enable
  UINT8         CbsCmnPTSataPort7Enable;                          ///< PT SATA Port 7 Enable
  UINT8         CbsDbgPTXhciGen1;                                 ///< PT XHCI GEN1
  UINT8         CbsDbgPTXhciGen2;                                 ///< PT XHCI GEN2
  UINT8         CbsDbgPTUsbEqualization4;                         ///< PT USB Equalization4
  UINT8         CbsDbgPTUsbRedriver;                              ///< PT USB Redriver
  UINT8         CbsDbgPTUsb31P0;                                  ///< PT USB31 PORT0
  UINT8         CbsDbgPTUsb31P1;                                  ///< PT USB31 PORT1
  UINT8         CbsDbgPTUsb30P0;                                  ///< PT USB30 PORT0
  UINT8         CbsDbgPTUsb30P1;                                  ///< PT USB30 PORT1
  UINT8         CbsDbgPTUsb30P2;                                  ///< PT USB30 PORT2
  UINT8         CbsDbgPTUsb30P3;                                  ///< PT USB30 PORT3
  UINT8         CbsDbgPTUsb30P4;                                  ///< PT USB30 PORT4
  UINT8         CbsDbgPTUsb30P5;                                  ///< PT USB30 PORT5
  UINT8         CbsDbgPTUsb20P0;                                  ///< PT USB20 PORT0
  UINT8         CbsDbgPTUsb20P1;                                  ///< PT USB20 PORT1
  UINT8         CbsDbgPTUsb20P2;                                  ///< PT USB20 PORT2
  UINT8         CbsDbgPTUsb20P3;                                  ///< PT USB20 PORT3
  UINT8         CbsDbgPTUsb20P4;                                  ///< PT USB20 PORT4
  UINT8         CbsDbgPTUsb20P5;                                  ///< PT USB20 PORT5
  UINT8         CbsDbgPTProm2Usb31P0;                             ///< PT USB31 PORT0
  UINT8         CbsDbgPTProm2Usb31P1;                             ///< PT USB31 PORT1
  UINT8         CbsDbgPTProm2Usb30P0;                             ///< PT USB30 PORT0
  UINT8         CbsDbgPTProm2Usb30P1;                             ///< PT USB30 PORT1
  UINT8         CbsDbgPTProm2Usb20P0;                             ///< PT USB20 PORT0
  UINT8         CbsDbgPTProm2Usb20P1;                             ///< PT USB20 PORT1
  UINT8         CbsDbgPTProm2Usb20P2;                             ///< PT USB20 PORT2
  UINT8         CbsDbgPTProm2Usb20P3;                             ///< PT USB20 PORT3
  UINT8         CbsDbgPTProm2Usb20P4;                             ///< PT USB20 PORT4
  UINT8         CbsDbgPTProm2Usb20P5;                             ///< PT USB20 PORT5
  UINT8         CbsDbgPTProm1Usb31P0;                             ///< PT USB31 PORT0
  UINT8         CbsDbgPTProm1Usb31P1;                             ///< PT USB31 PORT1
  UINT8         CbsDbgPTProm1Usb30P0;                             ///< PT USB30 PORT0
  UINT8         CbsDbgPTProm1Usb20P0;                             ///< PT USB20 PORT0
  UINT8         CbsDbgPTProm1Usb20P1;                             ///< PT USB20 PORT1
  UINT8         CbsDbgPTProm1Usb20P2;                             ///< PT USB20 PORT2
  UINT8         CbsDbgPTProm1Usb20P3;                             ///< PT USB20 PORT3
  UINT8         CbsDbgPTProm1Usb20P4;                             ///< PT USB20 PORT4
  UINT8         CbsDbgPTProm1Usb20P5;                             ///< PT USB20 PORT5
  UINT8         CbsCmnPTPciePort0Enable;                          ///< PT PCIE Port 0 Enable
  UINT8         CbsCmnPTPciePort1Enable;                          ///< PT PCIE Port 1 Enable
  UINT8         CbsCmnPTPciePort2Enable;                          ///< PT PCIE Port 2 Enable
  UINT8         CbsCmnPTPciePort3Enable;                          ///< PT PCIE Port 3 Enable
  UINT8         CbsCmnPTPciePort4Enable;                          ///< PT PCIE Port 4 Enable
  UINT8         CbsCmnPTPciePort5Enable;                          ///< PT PCIE Port 5 Enable
  UINT8         CbsCmnPTPciePort6Enable;                          ///< PT PCIE Port 6 Enable
  UINT8         CbsCmnPTPciePort7Enable;                          ///< PT PCIE Port 7 Enable
  UINT8         CbsCmnMemCtrllerDramEccEnDdr4;                    ///< DRAM ECC Enable
  UINT8         CbsCmnMemCtrllerDramEccSymbolSizeDdr4;            ///< DRAM ECC Symbol Size
  UINT8         CbsCmnToggleAllPwrGoodOnCf9;                      ///< Toggle All PwrGood On Cf9
  UINT8         CbsCmnMemCtrllerRttParkDdr4;                      ///< RttPark
  UINT8         CbsCmnMemTimingTwrrdDdr4;                         ///< Twrrd
  UINT8         CbsCmnMemTimingTrdrdScDdr4;                       ///< TrdrdSc
  UINT8         CbsCmnMemCkeSetupDdr4;                            ///< CkeSetup
  UINT8         CbsCmnMemCsOdtSetupDdr4;                          ///< CsOdtSetup
  UINT8         CbsCmnMemCtrllerBankGroupSwapAltDdr4;             ///< BankGroupSwapAlt
  UINT8         CbsCmnMemCtrllerRttWrDdr4;                        ///< RttWr
  UINT8         CbsCmnMemCadBusClkDrvStrenDdr4;                   ///< ClkDrvStren
  UINT8         CbsCmnMemCadBusTimingCtlDdr4;                     ///< CAD Bus Timing User Controls
  UINT8         CbsCmnMemAddrCmdSetupDdr4;                        ///< AddrCmdSetup
  UINT8         CbsCmnMemCtrllerPwrDnEnDdr4;                      ///< Power Down Enable
  UINT8         CbsCmnMemCtrllerRttNomDdr4;                       ///< RttNom
  UINT8         CbsCmnMemCtrller2TModeDdr4;                       ///< Cmd2T
  UINT8         CbsCmnMemCadBusCkeDrvStrenDdr4;                   ///< CkeDrvStren
  UINT8         CbsCmnMemTimingTrdrdSdDdr4;                       ///< TrdrdSd
  UINT8         CbsCmnMemTimingTwrwrSdDdr4;                       ///< TwrwrSd
  UINT8         CbsCmnMemTimingTrdrdDdDdr4;                       ///< TrdrdDd
  UINT8         CbsCmnMemTimingTwrwrDdDdr4;                       ///< TwrwrDd
  UINT8         CbsCmnMemCadBusDrvStrenCtlDdr4;                   ///< CAD Bus Drive Strength User Controls
  UINT8         CbsCmnMemGearDownModeDdr4;                        ///< Gear Down Mode
  UINT8         CbsCmnMemTimingTrdwrDdr4;                         ///< Trdwr
  UINT8         CbsCmnMemDataBusConfigCtlDdr4;                    ///< Data Bus Configuration User Controls
  UINT8         CbsCmnMemCadBusCsOdtDrvStrenDdr4;                 ///< CsOdtDrvStren
  UINT8         CbsCmnMemTimingTckeDdr4;                          ///< Tcke
  UINT8         CbsCmnMemTimingTwrwrScDdr4;                       ///< TwrwrSc
  UINT8         CbsCmnMemCadBusAddrCmdDrvStrenDdr4;               ///< AddrCmdDrvStren
  UINT32        CbsCmnSystemTemperatureTracking;                  ///< System Temperature Tracking
  UINT8         CbsCmnMemDataMaskDdr4;                            ///< Data Mask
  UINT8         CbsCmnFchXgbe0Enable;                             ///< XGBE0 enable
  UINT8         CbsCmnFchXgbe1Enable;                             ///< XGBE1 enable
  UINT8         CbsCmnMemDisMemErrInj;                            ///< Disable Memory Error Injection
  UINT8         CbsCmnFchUartDriverType;                          ///< Uart Driver Type
  UINT8         CbsCmnSpdSmbusVoltage;                            ///< SMBUS SPD Voltage
  UINT8         CbsDfCmnUmaAbove4G;                               ///< UMA Above 4G
  UINT8         CbsCmnSocRpmcControl;                             ///< RPMC Control

  UINT8         Reserved[983];                                   ///< Reserved for option growth
} CBS_CONFIG;


///CbsVariableStructUniqueValue 0x4c1d976c 

#pragma pack(pop)


#endif // _AMD_CBS_VARIABLE_H_
