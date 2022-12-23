/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH Function Support Definition
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 311507 $   @e \$Date: 2015-01-21 14:57:51 -0800 (Wed, 21 Jan 2015) $
 *
 */
/*;********************************************************************************
;
; Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
;
; AMD is granting You permission to use this software and documentation (if
; any) (collectively, the "Software") pursuant to the terms and conditions of
; the Software License Agreement included with the Software. If You do not have
; a copy of the Software License Agreement, contact Your AMD representative for
; a copy.
;
; You agree that You will not reverse engineer or decompile the Software, in
; whole or in part, except as allowed by applicable law.
;
; WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
; KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
; BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
; ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
; INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
; ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
; ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
; warranties, so the above exclusion may not apply to You, but only to the
; extent required by law.
;
; LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
; APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
; LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
; CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
; OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
; ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
; INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
; LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
; FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
; INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
; PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
; You for all damages, losses, and causes of action (whether in contract, tort
; (including negligence) or otherwise) exceed the amount of $50 USD. You agree
; to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
; and their respective licensors, directors, officers, employees, affiliates or
; agents from and against any and all loss, damage, liability and other
; expenses (including reasonable attorneys' fees), resulting from Your
; possession or use of the Software or violation of the terms and conditions of
; this Agreement.
;
; U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
; Software and related documentation are "commercial items", as that term is
; defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
; software" and "commercial computer software documentation", as such terms are
; used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
; respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
; 227.7202-1 through 227.7202-4, as applicable, the commercial computer
; software and commercial computer software documentation are being licensed to
; U.S. Government end users: (a) only as commercial items, and (b) with only
; those rights as are granted to all other end users pursuant to the terms and
; conditions set forth in this Agreement. Unpublished rights are reserved under
; the copyright laws of the United States.
;
; EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
; laws and regulations, as well as the import/export control laws and
; regulations of other countries as applicable. You further agree You will not
; export, re-export, or transfer, directly or indirectly, any product,
; technical data, software or source code received from AMD under this license,
; or the direct product of such technical data or software to any country for
; which the United States or any other applicable government requires an export
; license or other governmental approval without first obtaining such licenses
; or approvals, or in violation of any applicable laws or regulations of the
; United States or the country where the technical data or software was
; obtained. You acknowledges the technical data and software received will not,
; in the absence of authorization from U.S. or local law and regulations as
; applicable, be used by or exported, re-exported or transferred to: (i) any
; sanctioned or embargoed country, or to nationals or residents of such
; countries; (ii) any restricted end-user as identified on any applicable
; government end-user list; or (iii) any party where the end-use involves
; nuclear, chemical/biological weapons, rocket systems, or unmanned air
; vehicles.  For the most current Country Group listings, or for additional
; information about the EAR or Your obligations under those regulations, please
; refer to the website of the U.S. Bureau of Industry and Security at
; http://www.bis.doc.gov/.
;******************************************************************************
;*/
#ifndef _FCH_COMMON_CFG_H_
#define _FCH_COMMON_CFG_H_

#pragma pack (push, 1)

//-----------------------------------------------------------------------------
//                     FCH DEFINITIONS AND MACROS
//-----------------------------------------------------------------------------

//
// FCH Component Data Structure Definitions
//

/// PCI_ADDRESS - PCI access structure
#define PCI_ADDRESS(bus, dev, func, reg) \
                   (UINT32) ( (((UINT32)bus) << 24) + (((UINT32)dev) << 19) + (((UINT32)func) << 16) + ((UINT32)reg) )

#define CPUID_FMF        0x80000001ul  // Family Model Features information

#include <FchImc.h>
#include <FchPT.h>
#include <FchXgbe.h>
#include <FchBiosRamUsage.h>

///
///  - Byte Register R/W structure
///
typedef struct _REG8_MASK {
  UINT8                 RegIndex;                       /// RegIndex - Reserved
  UINT8                 AndMask;                        /// AndMask - Reserved
  UINT8                 OrMask;                         /// OrMask - Reserved
} REG8_MASK;


///
/// PCIE Reset Block
///
typedef enum {
  NbBlock,                                              ///< Reset for NB PCIE
  FchBlock                                              ///< Reset for FCH GPP
} RESET_BLOCK;

///
/// PCIE Reset Operation
///
typedef enum {
  DeassertReset,                                        ///< DeassertRese - Deassert reset
  AssertReset                                           ///< AssertReset - Assert reset
} RESET_OP;

///
/// SPI SEMAPHORE ID
///
typedef enum {
 clear_all_ownerships,
 acquire_bios_ownership,
 release_bios_ownership,
 acquire_driver_ownership,
 release_driver_ownership,
 check_bios_ownership,
 check_driver_ownership
} SPI_SEMAPHORE_ID;

///
/// Raven 2 Dual Source
///
typedef enum {
    Raven2Bx,
    Raven2DSPCO,
    Raven2DSRV1,
    Raven2_Unknown
} RAVEN2_TYPE;

#define SPI_SEMAPHORE_ADDR 0xFEC100FCul
#define DriverOwnership BIT4
#define BiosOwnership BIT3
#define SpiTurn BIT0
#define fingerprint_timeout 500 // milli second
#define bios_timeout 1000 // milli second


///
/// Fch Run Time Parameters
///
typedef struct {
  UINT32                PcieMmioBase;                              ///< PcieMmioBase
  UINT32                FchDeviceEnableMap;                        ///< FchDeviceEnableMap
  UINT32                FchDeviceD3ColdMap;                        ///< FchDeviceD3ColdMap
  UINT16                XHCI_PMx04_XhciFwRomAddr_Rom;              ///< XHCI_PMx04_XhciFwRomAddr_Rom
  UINT32                XHCI_PMx08_xHCI_Firmware_Addr_1_Rom;       ///< XHCI_PMx08_xHCI_Firmware_Addr_1_Ram
  UINT16                XHCI_PMx04_XhciFwRomAddr_Ram;              ///< XHCI_PMx04_XhciFwRomAddr_Rom
  UINT32                XHCI_PMx08_xHCI_Firmware_Addr_1_Ram;       ///< XHCI_PMx08_xHCI_Firmware_Addr_1_Ram
  UINT8                 SataDevSlpPort0S5Pin;                      ///< SataDevSlpPort0S5Pin - Reserved
  UINT8                 SataDevSlpPort1S5Pin;                      ///< SataDevSlpPort1S5Pin - Reserved
  UINT16                Al2AhbLegacyUartIoEnable;                  ///< Al2Ahb Legacy Uart Io Enable
  UINT32                ReservedDWord1;                            ///<  - Reserved
  UINT32                ReservedDWord2;                            ///<  - Reserved
  UINT32                ReservedDWord3;                            ///<  - Reserved
  UINT32                ReservedDWord4;                            ///<  - Reserved
  UINT32                ReservedDWord5;                            ///<  - Reserved
                                                                   /// USB Type C mail box buffer from 0x30 lenghth 0x30
  UINT32                ReservedDWord10;                            ///<  - Reserved
  UINT32                ReservedDWord11;                            ///<  - Reserved
  UINT32                ReservedDWord12;                            ///<  - Reserved
  UINT32                ReservedDWord13;                            ///<  - Reserved
  UINT32                ReservedDWord14;                            ///<  - Reserved
  UINT32                ReservedDWord15;                            ///<  - Reserved
  UINT32                ReservedDWord16;                            ///<  - Reserved
  UINT32                ReservedDWord17;                            ///<  - Reserved
  UINT32                ReservedDWord18;                            ///<  - Reserved
  UINT32                ReservedDWord19;                            ///<  - Reserved
  UINT32                ReservedDWord20;                            ///<  - Reserved
  UINT32                ReservedDWord21;                            ///<  - Reserved
} FCH_RUNTIME;

///
/// SD structure
///
typedef struct {
  SD_MODE               SdConfig;                       ///< SD Mode configuration
                                                        ///   @li <b>00</b> - Disabled
                                                        ///   @li <b>00</b> - AMDA
                                                        ///   @li <b>01</b> - DMA
                                                        ///   @li <b>10</b> - PIO
                                                        ///
  UINT8                 SdSpeed;                        ///< SD Speed
                                                        ///   @li <b>0</b> - Low speed
                                                        ///   @li <b>1</b> - High speed
                                                        ///
  UINT8                 SdBitWidth;                     ///< SD Bit Width
                                                        ///   @li <b>0</b> - 32BIT clear 23
                                                        ///   @li <b>1</b> - 64BIT, set 23,default
                                                        ///
  UINT32                SdSsid;                         ///< SD Subsystem ID
  SD_CLOCK_CONTROL      SdClockControl;                 ///< SD Clock Control
  BOOLEAN               SdClockMultiplier;              ///< SD Clock Multiplier enable/disable
  UINT8                 SdReTuningMode;                 ///< SD Re-tuning modes select
                                                        ///    @li <b>0</b> - mode 1
                                                        ///    @li <b>1</b> - mode 2
                                                        ///    @li <b>2</b> - mode 3
  UINT8                 SdHostControllerVersion;        ///< SD controller Version
                                                        ///    @li <b>1</b> - SD 2.0
                                                        ///    @li <b>2</b> - SD 3.0
  UINT8                 SdrCapabilities;                ///< SDR Capability mode select
                                                        ///    @li <b>00</b> - SDR25/15
                                                        ///    @li <b>01</b> - SDR50
                                                        ///    @li <b>11</b> - SDR104
  UINT8                 SdSlotType;                     ///< SDR Slot Type select
                                                        ///    @li <b>00</b> - Removable Card Slot
                                                        ///    @li <b>01</b> - Embedded Slot for One Device
                                                        ///    @li <b>10</b> - Shared Bus Slot
  BOOLEAN               SdForce18;                      ///< SD Force18
  UINT8                 SdDbgConfig;                       ///< SD Mode configuration
                                                        ///   @li <b>00</b> - Disabled
                                                        ///   @li <b>00</b> - AMDA
                                                        ///   @li <b>01</b> - DMA
                                                        ///   @li <b>10</b> - PIO
                                                        ///
} FCH_SD;

///
/// CODEC_ENTRY - Fch HD Audio OEM Codec structure
///
typedef struct _CODEC_ENTRY {
  UINT8                 Nid;                            /// Nid - Reserved
  UINT32                Byte40;                         /// Byte40 - Reserved
} CODEC_ENTRY;

///
/// CODEC_TBL_LIST - Fch HD Audio Codec table list
///
typedef struct _CODEC_TBL_LIST {
  UINT32                CodecId;                        /// CodecID - Codec ID
  CODEC_ENTRY*          CodecTablePtr;                  /// CodecTablePtr - Codec table pointer
} CODEC_TBL_LIST;

///
/// AZALIA_PIN - HID Azalia or GPIO define structure.
///
typedef struct _AZALIA_PIN {
  UINT8                 AzaliaSdin0;                    ///< AzaliaSdin0
                                                        ///   @par
                                                        ///   @li <b>00</b> - GPIO PIN
                                                        ///   @li <b>10</b> - As a Azalia SDIN pin

  UINT8                 AzaliaSdin1;                    ///< AzaliaSdin1
                                                        ///   @par
                                                        /// SDIN1 is define at BIT2 & BIT3
                                                        ///   @li <b>00</b> - GPIO PIN
                                                        ///   @li <b>10</b> - As a Azalia SDIN pin

  UINT8                 AzaliaSdin2;                    ///< AzaliaSdin2
                                                        ///   @par
                                                        /// SDIN2 is define at BIT4 & BIT5
                                                        ///   @li <b>00</b> - GPIO PIN
                                                        ///   @li <b>10</b> - As a Azalia SDIN pin

  UINT8                 AzaliaSdin3;                    ///< AzaliaSdin3
                                                        ///   @par
                                                        /// SDIN3 is define at BIT6 & BIT7
                                                        ///   @li <b>00</b> - GPIO PIN
                                                        ///   @li <b>10</b> - As a Azalia SDIN pin
} AZALIA_PIN;

///
/// Azalia structure
///
typedef struct {
  HDA_CONFIG            AzaliaEnable;                   ///< AzaliaEnable       - Azalia function configuration
  BOOLEAN               AzaliaMsiEnable;                ///< AzaliaMsiEnable    - Azalia MSI capability
  UINT32                AzaliaSsid;                     ///< AzaliaSsid         - Azalia Subsystem ID
  UINT8                 AzaliaPinCfg;                   ///< AzaliaPinCfg       - Azalia Controller SDIN pin Configuration
                                                        ///  @par
                                                        ///  @li <b>0</b>       - disable
                                                        ///  @li <b>1</b>       - enable

  UINT8                 AzaliaFrontPanel;               ///< AzaliaFrontPanel   - Azalia Controller Front Panel Configuration
                                                        ///   @par
                                                        /// Support Front Panel configuration
                                                        ///   @li <b>0</b>      - Auto
                                                        ///   @li <b>1</b>      - disable
                                                        ///   @li <b>2</b>      - enable

  UINT8                 FrontPanelDetected;             ///< FrontPanelDetected - Force Azalia Controller Front Panel Configuration
                                                        ///  @par
                                                        /// Force Front Panel configuration
                                                        ///  @li <b>0</b>       - Not Detected
                                                        ///  @li <b>1</b>       - Detected

  UINT8                 AzaliaSnoop;                    ///< AzaliaSnoop        - Azalia Controller Snoop feature Configuration
                                                        ///   @par
                                                        /// Azalia Controller Snoop feature Configuration
                                                        ///   @li <b>0</b>      - disable
                                                        ///   @li <b>1</b>      - enable

  UINT8                 AzaliaDummy;                    /// AzaliaDummy         - Reserved */

  AZALIA_PIN            AzaliaConfig;                   /// AzaliaConfig        - Azaliz Pin Configuration

///
/// AZOEMTBL - Azalia Controller OEM Codec Table Pointer
///
  CODEC_TBL_LIST        *AzaliaOemCodecTablePtr;        /// AzaliaOemCodecTablePtr - Oem Azalia Codec Table Pointer

///
/// AZOEMFPTBL - Azalia Controller Front Panel OEM Table Pointer
///
  VOID                  *AzaliaOemFpCodecTablePtr;      /// AzaliaOemFpCodecTablePtr - Oem Front Panel Codec Table Pointer
} FCH_AZALIA;

///
/// _SPI_DEVICE_PROFILE Spi Device Profile structure
///
typedef struct _SPI_DEVICE_PROFILE {
  UINT32                JEDEC_ID;                       /// JEDEC ID
  UINT32                RomSize;                        /// ROM Size
  UINT32                SectorSize;                     /// Sector Size
  UINT16                MaxNormalSpeed;                 /// Max Normal Speed
  UINT16                MaxFastSpeed;                   /// Max Fast Speed
  UINT16                MaxDualSpeed;                   /// Max Dual Speed
  UINT16                MaxQuadSpeed;                   /// Max Quad Speed
  UINT8                 QeReadRegister;                 /// QE Read Register
  UINT8                 QeWriteRegister;                /// QE Write Register
  UINT8                 QeOperateSize;                  /// QE Operate Size 1byte/2bytes
  UINT16                QeLocation;                     // QE Location in the register
} SPI_DEVICE_PROFILE;

///
/// _SPI_CONTROLLER_PROFILE Spi Device Profile structure
///
typedef struct _SPI_CONTROLLER_PROFILE {
//  UINT32                SPI_CONTROLLER_ID;                       /// SPI Controller ID
  UINT16                FifoSize;                       /// FIFO Size
  UINT16                MaxNormalSpeed;                 /// Max Normal Speed
  UINT16                MaxFastSpeed;                   /// Max Fast Speed
  UINT16                MaxDualSpeed;                   /// Max Dual Speed
  UINT16                MaxQuadSpeed;                   /// Max Quad Speed
} SPI_CONTROLLER_PROFILE;

///
/// SPI structure
///
typedef struct {
  BOOLEAN               LpcMsiEnable;                   ///< LPC MSI capability
  UINT32                LpcSsid;                        ///< LPC Subsystem ID
  UINT32                RomBaseAddress;                 ///< SpiRomBaseAddress
                                                        ///   @par
                                                        ///   SPI ROM BASE Address
                                                        ///
  UINT8                 SpiSpeed;                       ///< SpiSpeed - Spi Frequency
                                                        ///  @par
                                                        ///  SPI Speed [1.0] - the clock speed for non-fast read command
                                                        ///   @li <b>00</b> - 66Mhz
                                                        ///   @li <b>01</b> - 33Mhz
                                                        ///   @li <b>10</b> - 22Mhz
                                                        ///   @li <b>11</b> - 16.5Mhz
                                                        ///
  UINT8                 SpiFastSpeed;                   ///< FastSpeed  - Spi Fast Speed feature
                                                        ///  SPIFastSpeed [1.0] - the clock speed for Fast Speed Feature
                                                        ///   @li <b>00</b> - 66Mhz
                                                        ///   @li <b>01</b> - 33Mhz
                                                        ///   @li <b>10</b> - 22Mhz
                                                        ///   @li <b>11</b> - 16.5Mhz
                                                        ///
  UINT8                 WriteSpeed;                     ///< WriteSpeed - Spi Write Speed
                                                        /// @par
                                                        ///  WriteSpeed [1.0] - the clock speed for Spi write command
                                                        ///   @li <b>00</b> - 66Mhz
                                                        ///   @li <b>01</b> - 33Mhz
                                                        ///   @li <b>10</b> - 22Mhz
                                                        ///   @li <b>11</b> - 16.5Mhz
                                                        ///
  UINT8                 SpiMode;                        ///< SpiMode    - Spi Mode Setting
                                                        /// @par
                                                        ///  @li <b>101</b> - Qual-io 1-4-4
                                                        ///  @li <b>100</b> - Dual-io 1-2-2
                                                        ///  @li <b>011</b> - Qual-io 1-1-4
                                                        ///  @li <b>010</b> - Dual-io 1-1-2
                                                        ///  @li <b>111</b> - FastRead
                                                        ///  @li <b>110</b> - Normal
                                                        ///
  UINT8                 AutoMode;                       ///< AutoMode   - Spi Auto Mode
                                                        /// @par
                                                        ///  SPI Auto Mode
                                                        ///  @li <b>0</b> - Disabled
                                                        ///  @li <b>1</b> - Enabled
                                                        ///
  UINT8                 SpiBurstWrite;                  ///< SpiBurstWrite - Spi Burst Write Mode
                                                        /// @par
                                                        ///  SPI Burst Write
                                                        ///  @li <b>0</b> - Disabled
                                                        ///  @li <b>1</b> - Enabled
  BOOLEAN               LpcClk0;                        ///< Lclk0En - LPCCLK0
                                                        /// @par
                                                        ///  LPC Clock 0 mode
                                                        ///  @li <b>0</b> - forced to stop
                                                        ///  @li <b>1</b> - functioning with CLKRUN protocol
  BOOLEAN               LpcClk1;                        ///< Lclk1En - LPCCLK1
                                                        /// @par
                                                        ///  LPC Clock 1 mode
                                                        ///  @li <b>0</b> - forced to stop
                                                        ///  @li <b>1</b> - functioning with CLKRUN protocol
  BOOLEAN               LpcClkRunEn;                    ///< Lclk1En - LPCCLKRun
                                                        /// @par
                                                        ///  LPC Clock Run mode
                                                        ///  @li <b>0</b> - Disabled
                                                        ///  @li <b>1</b> - Enabled
//  UINT32                SPI100_RX_Timing_Config_Register_38;                 ///< SPI100_RX_Timing_Config_Register_38
//  UINT16                SPI100_RX_Timing_Config_Register_3C;                 ///< SPI100_RX_Timing_Config_Register_3C
//  UINT8                 SpiProtectEn0_1d_34;                  ///
  UINT8                 SPI100_Enable;                  ///< Spi 100 Enable
  SPI_DEVICE_PROFILE    SpiDeviceProfile;               ///< Spi Device Profile
} FCH_SPI;


///
/// IDE structure
///
typedef struct {
  BOOLEAN               IdeEnable;                      ///< IDE function switch
  BOOLEAN               IdeMsiEnable;                   ///< IDE MSI capability
  UINT32                IdeSsid;                        ///< IDE controller Subsystem ID
} FCH_IDE;

///
/// IR Structure
///
typedef struct {
  IR_CONFIG             IrConfig;                       ///< IrConfig
  UINT8                 IrPinControl;                   ///< IrPinControl
} FCH_IR;


///
/// PCI Bridge Structure
///
typedef struct {
  BOOLEAN               PcibMsiEnable;                  ///< PCI-PCI Bridge MSI capability
  UINT32                PcibSsid;                       ///< PCI-PCI Bridge Subsystem ID
  UINT8                 PciClks;                        ///< 33MHz PCICLK0/1/2/3 Enable, bits [0:3] used
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  UINT16                PcibClkStopOverride;            ///< PCIB_CLK_Stop Override
  BOOLEAN               PcibClockRun;                   ///< Enable the auto clkrun functionality
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
} FCH_PCIB;


///
/// - SATA Phy setting structure
///
typedef struct _SATA_PHY_SETTING {
  UINT16                PhyCoreControlWord;             /// PhyCoreControlWord - Reserved
  UINT32                PhyFineTuneDword;               /// PhyFineTuneDword - Reserved
} SATA_PHY_SETTING;

///
/// SATA main setting structure
///
typedef struct _SATA_ST {
  UINT8                 SataModeReg;                    ///< SataModeReg - Sata Controller Mode
  BOOLEAN               SataEnable;                     ///< SataEnable - Sata Controller Function
                                                        ///   @par
                                                        /// Sata Controller
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  UINT8                 Sata6AhciCap;                   ///< Sata6AhciCap - Reserved */
  BOOLEAN               SataSetMaxGen2;                 ///< SataSetMaxGen2 - Set Sata Max Gen2 mode
                                                        ///   @par
                                                        /// Sata Controller Set to Max Gen2 mode
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  BOOLEAN               IdeEnable;                      ///< IdeEnable - Hidden IDE
                                                        ///  @par
                                                        /// Sata IDE Controller Combined Mode
                                                        ///   Enable -  SATA controller has control over Port0 through Port3,
                                                        ///     IDE controller has control over Port4 and Port7.
                                                        ///   Disable - SATA controller has full control of all 8 Ports
                                                        ///     when operating in non-IDE mode.
                                                        ///  @li <b>0</b> - enable
                                                        ///  @li <b>1</b> - disable
                                                        ///
  UINT8                 SataClkMode;                    /// SataClkMode - Reserved
} SATA_ST;

///
/// SATA_PORT_ST - SATA PORT structure
///
typedef struct _SATA_PORT_ST {
  UINT8                 SataPortReg;                    ///< SATA Port bit map - bits[0:7] for ports 0 ~ 7
                                                        ///  @li <b>0</b> - disable
                                                        ///  @li <b>1</b> - enable
                                                        ///
  BOOLEAN               Port0;                          ///< PORT0 - 0:disable, 1:enable
  BOOLEAN               Port1;                          ///< PORT1 - 0:disable, 1:enable
  BOOLEAN               Port2;                          ///< PORT2 - 0:disable, 1:enable
  BOOLEAN               Port3;                          ///< PORT3 - 0:disable, 1:enable
  BOOLEAN               Port4;                          ///< PORT4 - 0:disable, 1:enable
  BOOLEAN               Port5;                          ///< PORT5 - 0:disable, 1:enable
  BOOLEAN               Port6;                          ///< PORT6 - 0:disable, 1:enable
  BOOLEAN               Port7;                          ///< PORT7 - 0:disable, 1:enable
} SATA_PORT_ST;

///
///< _SATA_PORT_MD - Force Each PORT to GEN1/GEN2 mode
///
typedef struct _SATA_PORT_MD {
  UINT16                SataPortMode;                   ///< SATA Port GEN1/GEN2 mode bit map - bits [0:15] for ports 0 ~ 7
  UINT8                 Port0;                          ///< PORT0 - set BIT0 to GEN1, BIT1 - PORT0 set to GEN2
  UINT8                 Port1;                          ///< PORT1 - set BIT2 to GEN1, BIT3 - PORT1 set to GEN2
  UINT8                 Port2;                          ///< PORT2 - set BIT4 to GEN1, BIT5 - PORT2 set to GEN2
  UINT8                 Port3;                          ///< PORT3 - set BIT6 to GEN1, BIT7 - PORT3 set to GEN2
  UINT8                 Port4;                          ///< PORT4 - set BIT8 to GEN1, BIT9 - PORT4 set to GEN2
  UINT8                 Port5;                          ///< PORT5 - set BIT10 to GEN1, BIT11 - PORT5 set to GEN2
  UINT8                 Port6;                          ///< PORT6 - set BIT12 to GEN1, BIT13 - PORT6 set to GEN2
  UINT8                 Port7;                          ///< PORT7 - set BIT14 to GEN1, BIT15 - PORT7 set to GEN2
} SATA_PORT_MD;
///
/// SATA structure
///
typedef struct {
  BOOLEAN               SataMsiEnable;                  ///< SATA MSI capability
  UINT32                SataIdeSsid;                    ///< SATA IDE mode SSID
  UINT32                SataRaidSsid;                   ///< SATA RAID mode SSID
  UINT32                SataRaid5Ssid;                  ///< SATA RAID 5 mode SSID
  UINT32                SataAhciSsid;                   ///< SATA AHCI mode SSID

  SATA_ST               SataMode;                       /// SataMode - Reserved
  SATA_CLASS            SataClass;                      ///< SataClass - SATA Controller mode [2:0]
  UINT8                 SataIdeMode;                    ///< SataIdeMode - Sata IDE Controller mode
                                                        ///  @par
                                                        ///   @li <b>0</b> - Legacy IDE mode
                                                        ///   @li <b>1</b> - Native IDE mode
                                                        ///
  UINT8                 SataDisUnusedIdePChannel;       ///< SataDisUnusedIdePChannel-Disable Unused IDE Primary Channel
                                                        ///  @par
                                                        ///   @li <b>0</b> - Channel Enable
                                                        ///   @li <b>1</b> - Channel Disable
                                                        ///
  UINT8                 SataDisUnusedIdeSChannel;       ///< SataDisUnusedIdeSChannel - Disable Unused IDE Secondary Channel
                                                        ///   @par
                                                        ///    @li <b>0</b> - Channel Enable
                                                        ///    @li <b>1</b> - Channel Disable
                                                        ///
  UINT8                 IdeDisUnusedIdePChannel;        ///< IdeDisUnusedIdePChannel-Disable Unused IDE Primary Channel
                                                        ///   @par
                                                        ///    @li <b>0</b> - Channel Enable
                                                        ///    @li <b>1</b> - Channel Disable
                                                        ///
  UINT8                 IdeDisUnusedIdeSChannel;        ///< IdeDisUnusedIdeSChannel-Disable Unused IDE Secondary Channel
                                                        ///   @par
                                                        ///    @li <b>0</b> - Channel Enable
                                                        ///    @li <b>1</b> - Channel Disable
                                                        ///
  UINT8                 SataOptionReserved;             /// SataOptionReserved - Reserved

  SATA_PORT_ST          SataEspPort;                    ///<  SataEspPort - SATA port is external accessible on a signal only connector (eSATA:)

  SATA_PORT_ST          SataPortPower;                  ///<  SataPortPower - Port Power configuration

  SATA_PORT_MD          SataPortMd;                     ///<  SataPortMd - Port Mode

  UINT8                 SataAggrLinkPmCap;              /// SataAggrLinkPmCap - 0:OFF   1:ON
  UINT8                 SataPortMultCap;                /// SataPortMultCap - 0:OFF   1:ON
  UINT8                 SataClkAutoOff;                 /// SataClkAutoOff - AutoClockOff 0:Disabled, 1:Enabled
  UINT8                 SataPscCap;                     /// SataPscCap 1:Enable PSC, 0:Disable PSC capability
  UINT8                 BiosOsHandOff;                  /// BiosOsHandOff - Reserved
  UINT8                 SataFisBasedSwitching;          /// SataFisBasedSwitching - Reserved
  UINT8                 SataCccSupport;                 /// SataCccSupport - Reserved
  UINT8                 SataSscCap;                     /// SataSscCap - 1:Enable, 0:Disable SSC capability
  UINT8                 SataMsiCapability;              /// SataMsiCapability 0:Hidden 1:Visible
  UINT8                 SataForceRaid;                  /// SataForceRaid   0:No function 1:Force RAID
  UINT8                 SataInternal100Spread;          /// SataInternal100Spread - Reserved
  UINT8                 SataDebugDummy;                 /// SataDebugDummy - Reserved
  UINT8                 SataTargetSupport8Device;       /// SataTargetSupport8Device - Reserved
  UINT8                 SataDisableGenericMode;         /// SataDisableGenericMode - Reserved
  BOOLEAN               SataAhciEnclosureManagement;    /// SataAhciEnclosureManagement - Reserved
  UINT8                 SataSgpio0;                     /// SataSgpio0 - Reserved
  UINT8                 SataSgpio1;                     /// SataSgpio1 - Reserved
  UINT8                 SataPhyPllShutDown;             /// SataPhyPllShutDown - Reserved
  BOOLEAN               SataHotRemovalEnh;              /// SataHotRemovalEnh - Reserved

  SATA_PORT_ST          SataHotRemovalEnhPort;          ///<  SataHotRemovalEnhPort - Hot Remove

  BOOLEAN               SataOobDetectionEnh;            /// SataOobDetectionEnh - TRUE
  BOOLEAN               SataPowerSavingEnh;             /// SataPowerSavingEnh - TRUE
  UINT8                 SataMemoryPowerSaving;          /// SataMemoryPowerSaving - 0-3 Default [3]
  BOOLEAN               SataRasSupport;                 /// SataRasSupport - Support RAS function TRUE: Enable FALSE: Disable
  BOOLEAN               SataAhciDisPrefetchFunction;    /// SataAhciDisPrefetchFunction - Disable AHCI Prefetch Function Support
  BOOLEAN               SataDevSlpPort0;                /// SataDevSlpPort0 - Reserved
  BOOLEAN               SataDevSlpPort1;                /// SataDevSlpPort1 - Reserved
//  UINT8                 SataDevSlpPort0S5Pin;           /// SataDevSlpPort0S5Pin - Reserved
//  UINT8                 SataDevSlpPort1S5Pin;           /// SataDevSlpPort1S5Pin - Reserved
  UINT32                TempMmio;                       /// TempMmio - Reserved
  UINT8                 SataDevSlpPort0Num;             /// SataDevSlpPort0Num - Reserved
  UINT8                 SataDevSlpPort1Num;             /// SataDevSlpPort1Num - Reserved
  BOOLEAN               SataControllerAutoShutdown;     /// SataControllerAutoShutdown
} FCH_SATA;


///
/// Hpet structure
///
typedef struct {
  BOOLEAN               HpetEnable;                     ///< HPET function switch

  BOOLEAN               HpetMsiDis;                     ///< HpetMsiDis - South Bridge HPET MSI Configuration
                                                        ///   @par
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT32                HpetBase;                       ///< HpetBase
                                                        ///   @par
                                                        ///  HPET Base address
} FCH_HPET;


///
/// GCPU related parameters
///
typedef struct {
  UINT8                 AcDcMsg;                        ///< Send a message to CPU to indicate the power mode (AC vs battery)
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 TimerTickTrack;                 ///< Send a message to CPU to indicate the latest periodic timer interval
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 ClockInterruptTag;              ///< Mark the periodic timer interrupt
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 OhciTrafficHanding;             ///< Cause CPU to break out from C state when USB OHCI has pending traffic
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 EhciTrafficHanding;             ///< Cause CPU to break out from C state when USB EHCI has pending traffic
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 GcpuMsgCMultiCore;              ///< Track of CPU C state by monitoring each core's C state message
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable

  UINT8                 GcpuMsgCStage;                  ///< Enable the FCH C state coordination logic
                                                        ///   @li <b>1</b> - disable
                                                        ///   @li <b>0</b> - enable
} FCH_GCPU;


///
/// Timer
///
typedef struct {
  BOOLEAN               Enable;                         ///< Whether to register timer SMI in POST
  BOOLEAN               StartNow;                       ///< Whether to start the SMI immediately during registration
  UINT16                CycleDuration;                  ///< [14:0] - Actual cycle duration = CycleDuration + 1
} TIMER_SMI;

///
/// CS support
///
typedef struct {
  BOOLEAN               FchCsD3Cold;                    ///< FCH Cs D3 Cold function
  BOOLEAN               FchCsHwReduced;                 ///< FCH Cs hardware reduced ACPI flag
  BOOLEAN               FchCsPwrBtn;                    ///< FCH Cs Power Button function
  BOOLEAN               FchCsAcDc;                      ///< FCH Cs AcDc function
  BOOLEAN               AsfNfcEnable;                   ///< FCH Cs NFC function
  UINT8                 AsfNfcInterruptPin;             ///<    NFC Interrupt pin define
  UINT8                 AsfNfcRegPuPin;                 ///<    NFC RegPu pin define
  UINT8                 AsfNfcWakePin;                  ///<    NFC Wake Pin define
  UINT8                 PowerButtonGpe;                 ///<    GPE# used by Power Button device
  UINT8                 AcDcTimerGpe;                   ///<    GPE# used by Timer device
  BOOLEAN               FchModernStandby;               ///< FCH Modern Standby function
} FCH_CS;


///
/// MISC structure
///
typedef struct {
  BOOLEAN               NativePcieSupport;              /// PCIe NativePcieSupport - Debug function. 1:Enabled, 0:Disabled
  BOOLEAN               S3Resume;                       /// S3Resume - Flag of ACPI S3 Resume.
  BOOLEAN               RebootRequired;                 /// RebootRequired - Flag of Reboot system is required.
  UINT8                 FchVariant;                     /// FchVariant - FCH Variant value.
  UINT8                 Cg2Pll;                         ///< CG2 PLL - 0:disable, 1:enable
  TIMER_SMI             LongTimer;                      ///< Long Timer SMI
  TIMER_SMI             ShortTimer;                     ///< Short Timer SMI
  UINT32                FchCpuId;                       ///< Saving CpuId for FCH Module.
  BOOLEAN               NoneSioKbcSupport;              ///< NoneSioKbcSupport - No KBC/SIO controller ( Turn on Inchip KBC emulation function )
  BOOLEAN               BpX48M0OutputEnable;            ///< BpX48M0OutputEnable - BP_X48M0 Clock Output Enable.
  BOOLEAN               BpX48M0S0i3Enable;              ///< BpX48M0S0i3Enable - BP_X48M0 Clock Output Enable at S0i3 state.
  FCH_CS                FchCsSupport;                   ///< FCH Cs function structure
  BOOLEAN               UsbDbgclkEn;                    ///< UsbDbgclkEn - Usb DBGCLK Enable.
} FCH_MISC;


///
/// SMBus structure
///
typedef struct {
  UINT32                SmbusSsid;                      ///< SMBUS controller Subsystem ID
} FCH_SMBUS;


///
/// Acpi structure
///
typedef struct {
  UINT16                Smbus0BaseAddress;              ///< Smbus0BaseAddress
                                                        ///   @par
                                                        ///  Smbus BASE Address
                                                        ///
  UINT16                Smbus1BaseAddress;              ///< Smbus1BaseAddress
                                                        ///   @par
                                                        ///  Smbus1 (ASF) BASE Address
                                                        ///
  UINT16                SioPmeBaseAddress;              ///< SioPmeBaseAddress
                                                        ///   @par
                                                        ///  SIO PME BASE Address
                                                        ///
  UINT32                WatchDogTimerBase;              ///< WatchDogTimerBase
                                                        ///   @par
                                                        ///  Watch Dog Timer Address
                                                        ///
  UINT16                AcpiPm1EvtBlkAddr;              ///< AcpiPm1EvtBlkAddr
                                                        ///   @par
                                                        ///  ACPI PM1 event block Address
                                                        ///
  UINT16                AcpiPm1CntBlkAddr;              ///< AcpiPm1CntBlkAddr
                                                        ///   @par
                                                        ///  ACPI PM1 Control block Address
                                                        ///
  UINT16                AcpiPmTmrBlkAddr;               ///< AcpiPmTmrBlkAddr
                                                        ///   @par
                                                        ///  ACPI PM timer block Address
                                                        ///
  UINT16                CpuControlBlkAddr;              ///< CpuControlBlkAddr
                                                        ///   @par
                                                        ///  ACPI CPU control block Address
                                                        ///
  UINT16                AcpiGpe0BlkAddr;                ///< AcpiGpe0BlkAddr
                                                        ///   @par
                                                        ///  ACPI GPE0 block Address
                                                        ///
  UINT16                SmiCmdPortAddr;                 ///< SmiCmdPortAddr
                                                        ///   @par
                                                        ///  SMI command port Address
                                                        ///
  UINT16                AcpiPmaCntBlkAddr;              ///< AcpiPmaCntBlkAddr
                                                        ///   @par
                                                        ///  ACPI PMA Control block Address
                                                        ///
  BOOLEAN               AnyHt200MhzLink;                ///< AnyHt200MhzLink
                                                        ///   @par
                                                        ///  HT Link Speed on 200MHz option for each CPU specific LDTSTP# (Force enable)
                                                        ///
  BOOLEAN               SpreadSpectrum;                 ///< SpreadSpectrum
                                                        ///  @par
                                                        ///  Spread Spectrum function
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  POWER_FAIL            PwrFailShadow;                  ///< PwrFailShadow = PM_Reg: 5Bh [3:0]
                                                        ///  @par
                                                        ///   @li  <b>00</b> - Always off
                                                        ///   @li  <b>01</b> - Always on
                                                        ///   @li  <b>11</b> - Use previous
                                                        ///
  UINT8                 StressResetMode;                ///< StressResetMode 01-10
                                                        ///   @li  <b>00</b> - Disabed
                                                        ///   @li  <b>01</b> - Io Write 0x64 with 0xfe
                                                        ///   @li  <b>10</b> - Io Write 0xcf9 with 0x06
                                                        ///   @li  <b>11</b> - Io Write 0xcf9 with 0x0e
                                                        ///
  BOOLEAN               MtC1eEnable;                    /// MtC1eEnable - Enable MtC1e
  VOID*                 OemProgrammingTablePtr;         /// Pointer of ACPI OEM table
  UINT8                 SpreadSpectrumOptions;          /// SpreadSpectrumOptions - Spread Spectrum Option
  BOOLEAN               PwrDownDisp2ClkPcieR;           /// Power down DISP2_CLK and PCIE_RCLK_Output for power savings
  BOOLEAN               NoClearThermalTripSts;          /// Skip clearing ThermalTrip status
  BOOLEAN               FchAoacProgramEnable;           /// Enable/disable AOAC init programming
  BOOLEAN               FchSxEntryXhciPmeEn;            /// FchSxEntryXhciPmeEn, enable XHCI controller PME bit in Sx Entry
} FCH_ACPI;


///
/// HWM temp parameter structure
///
typedef struct _FCH_HWM_TEMP_PAR {
  UINT16                At;                             ///< At
  UINT16                Ct;                             ///< Ct
  UINT8                 Mode;                           ///< Mode BIT0:HiRatio BIT1:HiCurrent
} FCH_HWM_TEMP_PAR;

///
/// HWM Current structure
///
typedef struct _FCH_HWM_CUR {
  UINT16                FanSpeed[5];                    ///< FanSpeed    - fan Speed
  UINT16                Temperature[5];                 ///< Temperature - temperature
  UINT16                Voltage[8];                     ///< Voltage     - voltage
} FCH_HWM_CUR;

///
/// HWM fan control structure
///
typedef struct _FCH_HWM_FAN_CTR {
  UINT8                 InputControlReg00;              /// Fan Input Control register, PM2 offset [0:4]0
  UINT8                 ControlReg01;                   /// Fan control register, PM2 offset [0:4]1
  UINT8                 FreqReg02;                      /// Fan frequency register, PM2 offset [0:4]2
  UINT8                 LowDutyReg03;                   /// Low Duty register, PM2 offset [0:4]3
  UINT8                 MedDutyReg04;                   /// Med Duty register, PM2 offset [0:4]4
  UINT8                 MultiplierReg05;                /// Multiplier register, PM2 offset [0:4]5
  UINT16                LowTempReg06;                   /// Low Temp register, PM2 offset [0:4]6
  UINT16                MedTempReg08;                   /// Med Temp register, PM2 offset [0:4]8
  UINT16                HighTempReg0A;                  /// High Temp register, PM2 offset [0:4]A
  UINT8                 LinearRangeReg0C;               /// Linear Range register, PM2 offset [0:4]C
  UINT8                 LinearHoldCountReg0D;           /// Linear Hold Count register, PM2 offset [0:4]D
} FCH_HWM_FAN_CTR;

///
/// Hwm structure
///
typedef struct _FCH_HWM {
  UINT8                 HwMonitorEnable;                ///< HwMonitorEnable
  UINT32                HwmControl;                     ///< hwmControl
                                                        ///   @par
                                                        ///  HWM control configuration
                                                        ///   @li <b>0</b> - HWM is Enabled
                                                        ///   @li <b>1</b> - IMC is Enabled
                                                        ///
  UINT8                 FanSampleFreqDiv;               ///< Sampling rate of Fan Speed
                                                        ///   @li <b>00</b> - Base(22.5KHz)
                                                        ///   @li <b>01</b> - Base(22.5KHz)/2
                                                        ///   @li <b>10</b> - Base(22.5KHz)/4
                                                        ///   @li <b>11</b> - Base(22.5KHz)/8
                                                        ///
  UINT8                 HwmFchtsiAutoPoll;              ///< TSI Auto Polling
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  UINT8                 HwmFchtsiAutoPollStarted;       ///< HwmSbtsiAutoPollStarted
  UINT8                 FanLinearEnhanceEn;             ///< FanLinearEnhanceEn
  UINT8                 FanLinearHoldFix;               ///< FanLinearHoldFix
  UINT8                 FanLinearRangeOutLimit;         ///< FanLinearRangeOutLimit
  UINT16                HwmCalibrationFactor;           /// Calibration Factor
  FCH_HWM_CUR           HwmCurrent;                     /// HWM Current structure
  FCH_HWM_CUR           HwmCurrentRaw;                  /// HWM Current Raw structure
  FCH_HWM_TEMP_PAR      HwmTempPar[5];                  /// HWM Temp parameter structure
  FCH_HWM_FAN_CTR       HwmFanControl[5];               /// HWM Fan Control structure
  FCH_HWM_FAN_CTR       HwmFanControlCooked[5];               /// HWM Fan Control structure
} FCH_HWM;


///
/// Gec structure
///
typedef struct {
  BOOLEAN               GecEnable;                      ///< GecEnable - GEC function switch
  UINT8                 GecPhyStatus;                   /// GEC PHY Status
  UINT8                 GecPowerPolicy;                 /// GEC Power Policy
                                                        ///   @li <b>00</b> - GEC is powered down in S3 and S5
                                                        ///   @li <b>01</b> - GEC is powered down only in S5
                                                        ///   @li <b>10</b> - GEC is powered down only in S3
                                                        ///   @li <b>11</b> - GEC is never powered down
                                                        ///
  UINT8                 GecDebugBus;                    /// GEC Debug Bus
                                                        ///   @li <b>0</b> - disable
                                                        ///   @li <b>1</b> - enable
                                                        ///
  UINT32                GecShadowRomBase;               ///< GecShadowRomBase
                                                        ///   @par
                                                        ///  GEC (NIC) SHADOWROM BASE Address
                                                        ///
  VOID                  *PtrDynamicGecRomAddress;       /// Pointer of Dynamic GEC ROM Address
} FCH_GEC;


///
/// _ABTblEntry - AB link register table R/W structure
///
typedef struct _AB_TBL_ENTRY {
  UINT8                 RegType;                        /// RegType  : AB Register Type (ABCFG, AXCFG and so on)
  UINT32                RegIndex;                       /// RegIndex : AB Register Index
  UINT32                RegMask;                        /// RegMask  : AB Register Mask
  UINT32                RegData;                        /// RegData  : AB Register Data
} AB_TBL_ENTRY;

///
/// AB structure
///
typedef struct {
  BOOLEAN               AbMsiEnable;                    ///< ABlink MSI capability
  UINT8                 ALinkClkGateOff;                /// Alink Clock Gate-Off function - 0:disable, 1:enable *KR
  UINT8                 BLinkClkGateOff;                /// Blink Clock Gate-Off function - 0:disable, 1:enable *KR
  UINT8                 GppClockRequest0;               /// GPP Clock Request.
  UINT8                 GppClockRequest1;               /// GPP Clock Request.
  UINT8                 GppClockRequest2;               /// GPP Clock Request.
  UINT8                 GppClockRequest3;               /// GPP Clock Request.
  UINT8                 GfxClockRequest;                /// GPP Clock Request.
  UINT8                 AbClockGating;                  /// AB Clock Gating - 0:disable, 1:enable *KR *CZ
  UINT8                 GppClockGating;                 /// GPP Clock Gating - 0:disable, 1:enable
  UINT8                 UmiL1TimerOverride;             /// UMI L1 inactivity timer overwrite value
  UINT8                 UmiLinkWidth;                   /// UMI Link Width
  UINT8                 UmiDynamicSpeedChange;          /// UMI Dynamic Speed Change - 0:disable, 1:enable
  UINT8                 PcieRefClockOverClocking;       /// PCIe Ref Clock OverClocking value
  UINT8                 UmiGppTxDriverStrength;         /// UMI GPP TX Driver Strength
  BOOLEAN               NbSbGen2;                       /// UMI link Gen2 - 0:Gen1, 1:Gen2
  UINT8                 PcieOrderRule;                  /// PCIe Order Rule - 0:disable, 1:enable *KR AB Posted Pass Non-Posted
  UINT8                 SlowSpeedAbLinkClock;           /// Slow Speed AB Link Clock - 0:disable, 1:enable *KR
  BOOLEAN               ResetCpuOnSyncFlood;            /// Reset Cpu On Sync Flood - 0:disable, 1:enable *KR
  BOOLEAN               AbDmaMemoryWrtie3264B;          /// AB DMA Memory Write 32/64 BYTE Support *KR only
  BOOLEAN               AbMemoryPowerSaving;            /// AB Memory Power Saving *KR *CZ
  BOOLEAN               SbgDmaMemoryWrtie3264ByteCount; /// SBG DMA Memory Write 32/64 BYTE Count Support *KR only
  BOOLEAN               SbgMemoryPowerSaving;           /// SBG Memory Power Saving *KR *CZ
  BOOLEAN               SbgClockGating;                 /// SBG Clock Gate *CZ
  BOOLEAN               XdmaDmaWrite16ByteMode;         /// XDMA DMA Write 16 byte mode *CZ
  BOOLEAN               XdmaMemoryPowerSaving;          /// XDMA memory power saving *CZ
  UINT8                 XdmaPendingNprThreshold;        /// XDMA PENDING NPR THRESHOLD *CZ
  BOOLEAN               XdmaDncplOrderDis;              /// XDMA DNCPL ORDER DIS *CZ
  UINT8                 SltGfxClockRequest0;            /// GPP Clock Request.
  UINT8                 SltGfxClockRequest1;            /// GPP Clock Request.
  BOOLEAN               SdphostBypassDataPack;          /// SdphostBypassDataPack
  BOOLEAN               SdphostDisNpmwrProtect;         /// Disable NPMWR interleaving protection
} FCH_AB;


/**
 * PCIE_CAP_ID - PCIe Cap ID
 *
 */
#define  PCIE_CAP_ID    0x10

///
/// FCH_GPP_PORT_CONFIG - Fch GPP port config structure
///
typedef struct {
  BOOLEAN               PortPresent;                    ///< Port connection
                                                        ///  @par
                                                        ///  @li <b>0</b> - Port doesn't have slot. No need to train the link
                                                        ///  @li <b>1</b> - Port connection defined and needs to be trained
                                                        ///
  BOOLEAN               PortDetected;                   ///< Link training status
                                                        ///  @par
                                                        ///  @li <b>0</b> - EP not detected
                                                        ///  @li <b>1</b> - EP detected
                                                        ///
  BOOLEAN               PortIsGen2;                     ///< Port link speed configuration
                                                        ///  @par
                                                        ///  @li <b>00</b> - Auto
                                                        ///  @li <b>01</b> - Forced GEN1
                                                        ///  @li <b>10</b> - Forced GEN2
                                                        ///  @li <b>11</b> - Reserved
                                                        ///
  BOOLEAN               PortHotPlug;                    ///< Support hot plug?
                                                        ///  @par
                                                        ///  @li <b>0</b> - No support
                                                        ///  @li <b>1</b> - support
                                                        ///
  UINT8                 PortMisc;                       ///  PortMisc - Reserved
} FCH_GPP_PORT_CONFIG;

///
/// GPP structure
///
typedef struct {
  FCH_GPP_PORT_CONFIG   PortCfg[4];                     /// GPP port configuration structure
  GPP_LINKMODE          GppLinkConfig;                  ///< GppLinkConfig - PCIE_GPP_Enable[3:0]
                                                        ///  @li  <b>0000</b> - Port ABCD -> 4:0:0:0
                                                        ///  @li  <b>0010</b> - Port ABCD -> 2:2:0:0
                                                        ///  @li  <b>0011</b> - Port ABCD -> 2:1:1:0
                                                        ///  @li  <b>0100</b> - Port ABCD -> 1:1:1:1
                                                        ///
  BOOLEAN               GppFunctionEnable;              ///< GPP Function - 0:disable, 1:enable
  BOOLEAN               GppToggleReset;                 ///< Toggle GPP core reset
  UINT8                 GppHotPlugGeventNum;            ///< Hotplug GEVENT # - valid value 0-31
  UINT8                 GppFoundGfxDev;                 ///< Gpp Found Gfx Device
                                                        ///  @li   <b>0</b> - Not found
                                                        ///  @li   <b>1</b> - Found
                                                        ///
  BOOLEAN               GppGen2;                        ///< GPP Gen2 - 0:disable, 1:enable
  UINT8                 GppGen2Strap;                   ///< GPP Gen2 Strap - 0:disable, 1:enable, FCH itself uses this
  BOOLEAN               GppMemWrImprove;                ///< GPP Memory Write Improve - 0:disable, 1:enable
  BOOLEAN               GppUnhidePorts;                 ///< GPP Unhide Ports - 0:disable, 1:enable
  UINT8                 GppPortAspm;                    ///< GppPortAspm - ASPM state for all GPP ports
                                                        ///  @li   <b>01</b> - Disabled
                                                        ///  @li   <b>01</b> - L0s
                                                        ///  @li   <b>10</b> - L1
                                                        ///  @li   <b>11</b> - L0s + L1
                                                        ///
  BOOLEAN               GppLaneReversal;                ///< GPP Lane Reversal - 0:disable, 1:enable
  BOOLEAN               GppPhyPllPowerDown;             ///< GPP PHY PLL Power Down - 0:disable, 1:enable
  BOOLEAN               GppDynamicPowerSaving;          ///< GPP Dynamic Power Saving - 0:disable, 1:enable
  BOOLEAN               PcieAer;                        ///< PcieAer - Advanced Error Report: 0/1-disable/enable
  BOOLEAN               PcieRas;                        ///< PCIe RAS - 0:disable, 1:enable
  BOOLEAN               PcieCompliance;                 ///< PCIe Compliance - 0:disable, 1:enable
  BOOLEAN               PcieSoftwareDownGrade;          ///< PCIe Software Down Grade
  BOOLEAN               UmiPhyPllPowerDown;             ///< UMI PHY PLL Power Down - 0:disable, 1:enable
  BOOLEAN               SerialDebugBusEnable;           ///< Serial Debug Bus Enable
  UINT8                 GppHardwareDownGrade;           ///< GppHardwareDownGrade - Gpp HW Down Grade function 0:Disable, 1-4: portA-D
  UINT8                 GppL1ImmediateAck;              ///< GppL1ImmediateAck - Gpp L1 Immediate ACK 0: enable, 1: disable
  BOOLEAN               NewGppAlgorithm;                ///< NewGppAlgorithm - New GPP procedure
  UINT8                 HotPlugPortsStatus;             ///< HotPlugPortsStatus - Save Hot-Plug Ports Status
  UINT8                 FailPortsStatus;                ///< FailPortsStatus - Save Failure Ports Status
  UINT8                 GppPortMinPollingTime;          ///< GppPortMinPollingTime - Min. Polling time for Gpp Port Training
  BOOLEAN               IsCapsuleMode;                  ///< IsCapsuleMode - Support Capsule Mode in FCH
} FCH_GPP;


///
/// FCH USB3 Debug Sturcture
///
typedef struct {
  BOOLEAN               ServiceIntervalEnable;      ///< Service Interval Enable
  BOOLEAN               BandwidthExpandEnable;      ///< Bandwidth Expand Enable
  BOOLEAN               AoacEnable;                 ///< Aoac Enable
  BOOLEAN               HwLpmEnable;                ///< HwLpm Enable
  BOOLEAN               DbcEnable;                  ///< DBC Enable
  BOOLEAN               MiscPlusEnable;             ///< Misc Plus Enable
  BOOLEAN               EcoFixEnable;               ///< Eco Fix Enable
  BOOLEAN               SsifEnable;                 ///< SSIF Enable
  BOOLEAN               U2ifEnable;                 ///< U2IF Enable
  BOOLEAN               FseEnable;                  ///< FSE Enable
  BOOLEAN               XhcPmeEnable;               ///< Xhc Pme Enable
} USB3_DEBUG;

///
/// FCH IoMux Sturcture
///
typedef struct {
  UINT8         CbsDbgFchSmbusI2c2Egpio;                          ///< SMBUS/I2C_2/EGPIO_113_114
  UINT8         CbsDbgFchAsfI2c3Egpio;                            ///< ASF/I2C_3/EGPIO_019_020
} FCH_IOMUX;

///
/// FCH USB sturcture
///
typedef struct {
  BOOLEAN               Ohci1Enable;                    ///< OHCI1 controller enable
  BOOLEAN               Ohci2Enable;                    ///< OHCI2 controller enable
  BOOLEAN               Ohci3Enable;                    ///< OHCI3 controller enable
  BOOLEAN               Ohci4Enable;                    ///< OHCI4 controller enable
  BOOLEAN               Ehci1Enable;                    ///< EHCI1 controller enable
  BOOLEAN               Ehci2Enable;                    ///< EHCI2 controller enable
  BOOLEAN               Ehci3Enable;                    ///< EHCI3 controller enable
  BOOLEAN               Xhci0Enable;                    ///< XHCI0 controller enable
  BOOLEAN               Xhci1Enable;                    ///< XHCI1 controller enable
  BOOLEAN               UsbMsiEnable;                   ///< USB MSI capability
  UINT32                OhciSsid;                       ///< OHCI SSID
  UINT32                Ohci4Ssid;                      ///< OHCI 4 SSID
  UINT32                EhciSsid;                       ///< EHCI SSID
  UINT32                XhciSsid;                       ///< XHCI SSID
  BOOLEAN               UsbPhyPowerDown;                ///< USB PHY Power Down - 0:disable, 1:enable
  UINT32                UserDefineXhciRomAddr;          ///< XHCI ROM address define by platform BIOS
  UINT8                 Ehci1Phy[5];                    ///< EHCI1 USB PHY Driving Strength value table
  UINT8                 Ehci2Phy[5];                    ///< EHCI2 USB PHY Driving Strength value table
  UINT8                 Ehci3Phy[4];                    ///< EHCI3 USB PHY Driving Strength value table
  UINT8                 Xhci20Phy[4];                   ///< XHCI USB 2.0 PHY Driving Strength value table
  UINT8                 Ehci1DebugPortSel;              ///< DebugPortSel for Ehci1 Hub
                                                        ///  @li   <b>000</b> - Disable
                                                        ///  @li   <b>001</b> - HubDownStreamPort0
                                                        ///  @li   <b>010</b> - HubDownStreamPort1
                                                        ///  @li   <b>011</b> - HubDownStreamPort2
                                                        ///  @li   <b>100</b> - HubDownStreamPort3
  UINT8                 Ehci2DebugPortSel;              ///< DebugPortSel for Ehci2 Hub
                                                        ///  @li   <b>000</b> - Disable
                                                        ///  @li   <b>001</b> - HubDownStreamPort0
                                                        ///  @li   <b>010</b> - HubDownStreamPort1
                                                        ///  @li   <b>011</b> - HubDownStreamPort2
                                                        ///  @li   <b>100</b> - HubDownStreamPort3
  UINT8                 Ehci3DebugPortSel;              ///< DebugPortSel for Ehci3 Hub
                                                        ///  @li   <b>000</b> - Disable
                                                        ///  @li   <b>001</b> - HubDownStreamPort0
                                                        ///  @li   <b>010</b> - HubDownStreamPort1
                                                        ///  @li   <b>011</b> - HubDownStreamPort2
                                                        ///  @li   <b>100</b> - HubDownStreamPort3
  BOOLEAN               SsicEnable;                     ///< SSIC controller enable
  UINT32                SsicSsid;                       ///< SSIC SSID
  UINT32                Usb0Bar;                        ///< Controller0 BAR
  UINT32                Usb1Bar;                        ///< Controller1 BAR
} FCH_USB;

typedef struct {
  UINT32                DW0;                                       ///< SMN Index
  UINT32                DW1;                                       ///< Mask
  UINT32                DW2;                                       ///< Data
  UINT32                DW3;                                       ///< Opcode/Group
} FCH_USB_CONFIGURE_ENTRY;

typedef struct {
  UINT8                    COMPDSTUNE;                             ///< COMPDSTUNE
  UINT8                    SQRXTUNE;                               ///< SQRXTUNE
  UINT8                    TXFSLSTUNE;                             ///< TXFSLSTUNE
  UINT8                    TXPREEMPAMPTUNE;                        ///< TXPREEMPAMPTUNE
  UINT8                    TXPREEMPPULSETUNE;                      ///< TXPREEMPPULSETUNE
  UINT8                    TXRISETUNE;                             ///< TXRISETUNE
  UINT8                    TXVREFTUNE;                             ///< TXVREFTUNE
  UINT8                    TXHSXVTUNE;                             ///< TXHSXVTUNE
  UINT8                    TXRESTUNE;                              ///< TXRESTUNE
} FCH_USB20_PHY;

typedef struct {
  UINT8                                  RX_EQ_DELTA_IQ_OVRD_VAL; ///< bit 0 to 3
  UINT8                                   RX_EQ_DELTA_IQ_OVRD_EN; ///< bit 4
} USB_31_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN;
typedef struct {
  UINT8                                             RX_VREF_CTRL; ///< bit 0 to 4
  UINT8                                          RX_VREF_CTRL_EN; ///< bit 5
  UINT8                                            TX_VBOOST_LVL; ///< BIT 6 to 8
  UINT8                                         TX_VBOOST_LVL_EN; ///< BIT 9
} USB_31_LVL_OVRD_IN;
typedef struct {
  UINT8                                             RX_VREF_CTRL; ///< bit 0 to 4
  UINT8                                          RX_VREF_CTRL_EN; ///< bit 5
  UINT8                                            TX_VBOOST_LVL; ///< BIT 6 to 8
  UINT8                                         TX_VBOOST_LVL_EN; ///< BIT 9
} USB_31_LVL_OVRD_IN_X;
typedef struct {
  UINT8                                   Usb31PhyEnable;
  USB_31_PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN    PCS_XF_RX_EQ_DELTA_IQ_OVRD_IN[4];
  USB_31_LVL_OVRD_IN                      LVL_OVRD_IN;
  USB_31_LVL_OVRD_IN_X                    LVL_OVRD_IN_X;
} FCH_USB31_PHY;
typedef struct {
  UINT8                         Version_Major;                     ///< USB IP version
  UINT8                         Version_Minor;                     ///< USB IP version
  UINT8                         TableLength;                       ///< TableLength
  UINT8                         Reserved0;
  FCH_USB20_PHY                 Usb20PhyPort[6];                   ///< USB 2.0 Driving Strength
  //FCH_XHCI_PHY                  Usb30PhyPort[5];                   ///< USB 3.0 Driving Strength
  UINT8                         DeviceRemovable;                   ///< Device Removable: bit0 - Port0, bit1 - Port1, etc.
  UINT8                         Usb3PortForceGen1;                 ///< Force USB3 port to gen1, bit0 - controller0 Port0, bit1 - Port1, etc.
  UINT8                         U3RxDetWAEnable;                   ///< U3 RxDet Workaround
  UINT8                         U3RxDetWAPortMap;                  ///< bit[3:0]-Usb0 Port[3:0], bit4 - Usb1 Port0
  UINT8                         EarlyDebugSelectEnable;            ///< Enable Early Debug-select Setup
  FCH_USB31_PHY                 Usb31Phy;                          ///< USB 3.1 Driving Strength
  UINT8                         Reserved1[4];
} FCH_RV_USB_OEM_PLATFORM_TABLE;


/// Emmc Config bit maps
typedef union {
  struct {                                                         ///<
    UINT64                  Spec_Ver :8;                           ///< [0:7]Spec version
    UINT64                  Sdr50_Sup :1;                          ///< [8] SDR50 Sup
    UINT64                  Sdr100_Sup :1;                         ///< [9] SDR100 Sup
    UINT64                  Ddr50_Sup :1;                          ///< [10] DDR50 Sup
    UINT64                  Force18 :1;                            ///< [11]Force 1.8V
    UINT64                  Force33 :1;                            ///< [12]Force 3.3V
    UINT64                  ReTuningMode :2;                       ///< [13:14] AdvisoryNonfatalErrMask
    UINT64                  Sdr50Tune :1;                          ///< [15]Sdr50 Tune
    UINT64                  WpCdTie :2;                            ///< [16:17] WP_TIE, CD_TIE
    UINT64                  Sdr50DriverStrength :2;                ///< [18:19] WP_TIE, CD_TIE
    UINT64                  Ddr50DriverStrength :2;                ///< [20:21] WP_TIE, CD_TIE
    UINT64                  SlotType :2;                           ///< [22:23] WP_TIE, CD_TIE
    UINT64                  BaseFre :8;                            ///< [24:31] Base Frequence
    UINT64                  DownSpeed :2;                          ///< [32:33] Down Speed
    UINT64                  Reserved_63_34 :30;                     ///< Unused bits
  } Field;                                                            ///<
//  UINT64 Value;                                                       ///<
} EMMC_CONFIG_BIT_MAP;

//Spec version SDR50 Sup SDR100 Sup DDR50 Sup Force 1.8V Force 3.3V Re-Tuning Mode SDR50-tune WP_TIE CD_TIE BaseFreq down speed


///
/// FCH EMMC sturcture
///
typedef struct {
  UINT8                 EmmcEnable;                     ///< eMMC/SD Configure
                                                        ///  @li   <b>0000</b> - Disabled
                                                        ///  @li   <b>0001</b> - Normal Speed 12.5MB/s 25MHz (v1.01) pll clock 63MHz (over flow, only for test, actual 100MHz)
                                                        ///  @li   <b>0010</b> - High Speed 25MB/s 50MHz (v2) pll clock 400MHz
                                                        ///  @li   <b>0011</b> - UHSI-SDR50 50MB/s 100MHz (v3.01) pll clock 400MHz
                                                        ///  @li   <b>0100</b> - UHSI-DDR50 50MB/s 50MHz (v3.01)
                                                        ///  @li   <b>0101</b> - UHSI-SDR104 100MB/s 200MHz (v3.01)
                                                        ///  @li   <b>0110</b> - Backward Comp 25MB/s 25MHz (v4.5)
                                                        ///  @li   <b>0111</b> - High Speed SDR 50MB/s 50MHz (v4.5)
                                                        ///  @li   <b>1000</b> - High Speed DDR 100MB/s 50MHz (v4.5)
                                                        ///  @li   <b>1001</b> - HS200 200MB/s 200MHz (v4.5)
                                                        ///  @li   <b>1010</b> - HS400 400MB/s 200MHz (v5)
                                                        ///  @li   <b>1011</b> - HS300 300MB/s 150MHz (v5)
  BOOLEAN               EmmcDriverType;                 ///< Enable eMMC as PnP0D40, False:AMDI0040, True:PnP0D40
  BOOLEAN               EmmcBoot;                       ///< eMMC boot, 0:Disabled, 1:Enabled
  BOOLEAN               EmmcAdma2Support;               ///< Emmc Adma2 Support, 0:Disabled, 1:Enabled
  BOOLEAN               EmmcAdmaSupport;                ///< Emmc Adma  Support, 0:Disabled, 1:Enabled
  BOOLEAN               EmmcSdmaSupport;                ///< Emmc Sdma  Support, 0:Disabled, 1:Enabled
  BOOLEAN               EmmcA64bSupport;                ///< Emmc A64b  Support, 0:Disabled, 1:Enabled
  BOOLEAN               EmmcD3Support;                  ///< Emmc D3  Support, 0:Disabled, 1:Enabled
} FCH_EMMC;

///
/// FCH GBE sturcture
///
typedef struct {
  BOOLEAN               Gbe0Enable;                     ///< Gbe controller0 enable/disable
  BOOLEAN               Gbe1Enable;                     ///< Gbe controller1 enable/disable
  UINT32                Gbe0MacAddress0Low;             ///< Gbe0 MAC Address0 Low
  UINT32                Gbe0MacAddress0High;            ///< Gbe0 MAC Address0 High
  UINT32                Gbe0MacAddress1Low;             ///< Gbe0 MAC Address1 Low
  UINT32                Gbe0MacAddress1High;            ///< Gbe0 MAC Address1 High
  UINT32                Gbe1MacAddress0Low;             ///< Gbe1 MAC Address0 Low
  UINT32                Gbe1MacAddress0High;            ///< Gbe1 MAC Address0 High
  UINT32                Gbe1MacAddress1Low;             ///< Gbe1 MAC Address1 Low
  UINT32                Gbe1MacAddress1High;            ///< Gbe1 MAC Address1 High
} FCH_GBE;


///
/// FCH ESPI IO decode sturcture
///
typedef struct {
  BOOLEAN               Enable;                         ///< eSPI IO decode enable: 0:disable, 1:enable
  UINT16                Base;                           ///< IO base: support 4Eh/4Fh 62h/66h or 600h-6FFh
  UINT8                 Size;                           ///< IO size: 0:1 byte, 1:2 byte, etc.
} FCH_ESPI_IO_DECODE;

///
/// FCH ESPI MMIO decode sturcture
///
typedef struct {
  BOOLEAN               Enable;                         ///< eSPI MMIO decode enable: 0:disable, 1:enable
  UINT32                Base;                           ///< MMIO base
  UINT16                Size;                           ///< MMIO size
} FCH_ESPI_MMIO_DECODE;

///
/// FCH ESPI IO/MMIO decode sturcture
///
typedef struct {
  FCH_ESPI_IO_DECODE    Io[4];                          ///< IO
  FCH_ESPI_MMIO_DECODE  Mmio[4];                        ///< MMIO size
} FCH_ESPI_DECODE;

///
/// FCH ESPI sturcture
///
typedef struct {
  UINT8                 OperatingFreq;                  ///< ESPI Operating Frequency  - 0:16.7MHz, 1:33MHz, 2:66MHz
  UINT8                 IoMode;                         ///< ESPI IO Mode  - 0:Single IO, 1:Dual IO, 2:Quad IO
  FCH_ESPI_DECODE       Decode;
} FCH_ESPI;


/// Private: FCH_DATA_BLOCK_RESET
typedef struct _FCH_RESET_DATA_BLOCK {
  AMD_CONFIG_PARAMS     *StdHeader;                     ///< Header structure
  FCH_RESET_INTERFACE   FchReset;                       ///< Reset interface

  UINT8                 FastSpeed;                      ///< SPI FastSpeed: 1-66MHz, 2-33MHz, 3-22MHz, 4-16.5MHz, 5-100Mhz
  UINT8                 WriteSpeed;                     ///< SPI Write Speed: 1-66MHz, 2-33MHz, 3-22MHz, 4-16.5MHz, 5-100Mhz
  UINT8                 Mode;                           ///< SPI Mode
                                                        ///  @li   <b>101</b> - Qual-io 1-4-4
                                                        ///  @li   <b>100</b> - Dual-io 1-2-2
                                                        ///  @li   <b>011</b> - Qual-io 1-1-4
                                                        ///  @li   <b>010</b> - Dual-io 1-1-2
                                                        ///  @li   <b>111</b> - FastRead
                                                        ///  @li   <b>110</b> - Normal
                                                        ///
  UINT8                 AutoMode;                       ///< SPI Auto Mode - 0:disable, 1:enable
  UINT8                 BurstWrite;                     ///< SPI Burst Write - 0:disable, 1:enable
  BOOLEAN               Sata6AhciCap;                   ///< SATA 6 AHCI Capability - TRUE:enable, FALSE:disable
  UINT8                 Cg2Pll;                         ///< CG2 PLL - 0:disable, 1:enable
  BOOLEAN               EcKbd;                          ///< EC KBD - 0:disable, 1:enable
  BOOLEAN               LegacyFree;                     ///< Legacy Free - 0:disable, 1:enable
  BOOLEAN               SataSetMaxGen2;                 ///< SATA enable maximum GEN2
  UINT8                 SataClkMode;                    ///< SATA reference clock selector and divider
  UINT8                 SataModeReg;                    ///< Output: SATAConfig PMIO:0xDA
  BOOLEAN               SataInternal100Spread;          ///< SATA internal 100MHz spread ON/OFF
  UINT8                 SpiSpeed;                       ///< SPI NormSpeed: 1-66MHz, 2-33MHz, 3-22MHz, 4-16.5MHz, 5-100Mhz
//  UINT32                SPI100_RX_Timing_Config_Register_38;                 ///< SPI100_RX_Timing_Config_Register_38
//  UINT16                SPI100_RX_Timing_Config_Register_3C;                 ///< SPI100_RX_Timing_Config_Register_3C
//  UINT8                 SpiProtectEn0_1d_34;                  ///
  UINT8                 SPI100_Enable;                  ///
  BOOLEAN               EcChannel0;                     ///< Enable EC channel 0
  FCH_GPP               Gpp;                            ///< GPP subsystem
  FCH_SPI               Spi;                            ///< SPI subsystem
  BOOLEAN               QeEnabled;                      /// Quad Mode Enabled
  BOOLEAN               FchOscout1ClkContinous;         ///< FCH OSCOUT1_CLK Continous
  UINT8                 LpcClockDriveStrength;          ///< Lpc Clock Drive Strength
  UINT8                 LpcClockDriveStrengthRiseTime;  ///< Lpc Clock Drive Strength Rise Time
  UINT8                 LpcClockDriveStrengthFallTime;  ///< Lpc Clock Drive Strength Fall Time
  FCH_PT                Promontory;                     ///< Promontory structure
  VOID*                 EarlyOemGpioTable;              /// Pointer of Early OEM GPIO table
//  VOID*                 OemSpiDeviceTable;              /// Pointer of OEM Spi Device table
  FCH_PLATFORM_POLICY   FchBldCfg;                      /// Build Options
  UINT8                 XhciECCDedErrRptEn;             /// USB3 ECC SMI control
  BOOLEAN               EspiEnable;                     ///< ESPI controller - 0:disable, 1:enable
  BOOLEAN               EspiIo80Enable;                 ///< ESPI 80h Port - 0:disable, 1:enable
  BOOLEAN               EspiKbc6064Enable;              ///< ESPI 60h/65h  - 0:disable, 1:enable
  BOOLEAN               EspiEc0Enable;                  ///< ESPI EC  - 0:disable, 1:enable
  BOOLEAN               WdtEnable;                      ///< enable FCH WatchDog Timer (WDT)
  BOOLEAN               Xhci0ForceGen1;                 ///< Xhci0 Force Gen1
  BOOLEAN               Xhci1Disable31Port;             ///< Xhci1 Disable 31Port
  BOOLEAN               ToggleAllPwrGoodOnCf9;          ///< Toggle All PwrGood On Cf9
  VOID*                 OemUsbConfigurationTablePtr;    /// Pointer of ACPI OEM table
  VOID*                 OemResetProgrammingTablePtr;    /// Pointer of ACPI OEM table
  UINT32                XhciUsb3PortDisable;            ///< XHCI Usb3 Port Disable, Bit0-3 - Port0-3
  UINT32                XhciUsb2PortDisable;            ///< XHCI Usb2 Port Disable, Bit0-3 - Port0-3
  UINT32                XhciOCpinSelect;                ///< XHCI OverCurrent OC Pin, [3:0] - Port0, [7:4] Port1, etc.
  FCH_EMMC              Emmc;                           ///< EMMC structure
  FCH_ESPI              Espi;                           ///< ESPI structure
  BOOLEAN               UsbSparseModeEnable;            ///< XHCI Sparse Control Transaction Enable
} FCH_RESET_DATA_BLOCK;


/// Private: FCH_DATA_BLOCK
typedef struct _FCH_DATA_BLOCK {
  FCH_RUNTIME           FchRunTime;                     ///< FCH Run Time Parameters
  AMD_CONFIG_PARAMS     *StdHeader;                     ///< Header structure

  FCH_ACPI              HwAcpi;                         ///< ACPI structure
  FCH_AB                Ab;                             ///< AB structure
  FCH_GPP               Gpp;                            ///< GPP structure
  FCH_USB               Usb;                            ///< USB structure
  FCH_SATA              Sata;                           ///< SATA structure
  FCH_SMBUS             Smbus;                          ///< SMBus structure
  FCH_IDE               Ide;                            ///< IDE structure
  FCH_AZALIA            Azalia;                         ///< Azalia structure
  FCH_SPI               Spi;                            ///< SPI structure
  FCH_PCIB              Pcib;                           ///< PCIB structure
  FCH_GEC               Gec;                            ///< GEC structure
  FCH_SD                Sd;                             ///< SD structure
  FCH_HWM               Hwm;                            ///< Hardware Moniter structure
  FCH_IR                Ir;                             ///< IR structure
  FCH_HPET              Hpet;                           ///< HPET structure
  FCH_GCPU              Gcpu;                           ///< GCPU structure
  FCH_IMC               Imc;                            ///< IMC structure
  FCH_MISC              Misc;                           ///< MISC structure
  FCH_IOMUX             IoMux;                          ///< MISC structure
  VOID*                 PostOemGpioTable;               /// Pointer of Post OEM GPIO table
  FCH_EMMC              Emmc;                           ///< EMMC structure
  FCH_XGBE              Xgbe;                           ///< XGBE structure
  FCH_PT                Promontory;                     ///< Promontory structure
  FCH_RESET_DATA_BLOCK  FchResetDataBlock;             ///< Reset data structure
} FCH_DATA_BLOCK;

#pragma pack (pop)

#endif

