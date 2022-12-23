/* $NoKeywords:$ */
/**
 * @file
 *
 * Agesa structures and definitions
 *
 * Contains AMD AGESA core interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
 * @e \$Revision: 317069 $   @e \$Date: 2015-04-20 11:25:50 -0700 (Mon, 20 Apr 2015) $
 */
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


#ifndef _FCHCOMMON_H_
#define _FCHCOMMON_H_

//-----------------------------------------------------------------------------
//                     FCH DEFINITIONS AND MACROS
//
//-----------------------------------------------------------------------------

/// Modes for eMMC controller
typedef enum {
  eMMC_Disable = 0,///< Disabled
  SdNormalSpeed,   ///< Normal Speed 12.5MB/s    25MHz   0x0 (v1.01)
  SdHighSpeed,     ///< High Speed   25MB/s      50MHz   0x01 (v2)          
  SdUhsiSdr50,     ///< UHSI-SDR50   50MB/s      100MHz  0x2 (v3.01)        
  SdUhsiDdr50,     ///< UHSI-DDR50   50MB/s      50MHz   0x2 (v3.01)        
  SdUhsiSdr104,    ///< UHSI-SDR104  100MB/s     200MHz  0x2 (v3.01)        
  EmmcBwComp,      ///< Backward Comp   25MB/s  25MHz   0x0 (v4.5)     
  EmmcHsSdr50,     ///< High Speed SDR  50MB/s  50MHz   0x1 (v4.5)     
  EmmcHsDdr100,    ///< High Speed DDR  100MB/s 50MHz   0x2 (v4.5)     
  EmmcHs200,       ///< HS200   200MB/s 200MHz  0x2 (v4.5)             
  EmmcHs400,       ///< HS400   400MB/s 200MHz  0x2 (v5)               
  EmmcHs300        ///< HS300   300MB/s 150MHz  0x2 (v5)               
} EMMC_MODE;

/// Configuration values for SdConfig
typedef enum {
  SdDisable = 0,                      ///< Disabled
  SdVer2,                             ///< Version 2.0
  SdVer3,                             ///< Version 3.0
  SdV3SDR50,                          ///< V3 SdSDR50
  SdV3SDR104,                         ///< V3 SdSDR104
  SdV3DDR50,                          ///< V3 SdDDR50
  SdDump                              ///< SD DUMP, don't touch SD
} SD_MODE;

/// Configuration values for SdClockControl
typedef enum {
  Sd50MhzTraceCableLengthWithinSixInches = 4,           ///< 50Mhz, default
  Sd40MhzTraceCableLengthSix2ElevenInches = 6,          ///< 40Mhz
  Sd25MhzTraceCableLengthEleven2TwentyfourInches = 7,   ///< 25Mhz
} SD_CLOCK_CONTROL;

/// Configuration values for AzaliaController
typedef enum {
  AzAuto = 0,                         ///< Auto - Detect Azalia controller automatically
  AzDisable,                          ///< Diable - Disable Azalia controller
  AzEnable                            ///< Enable - Enable Azalia controller
} HDA_CONFIG;

/// Configuration values for IrConfig
typedef enum {
  IrDisable  = 0,                     ///< Disable
  IrRxTx0    = 1,                     ///< Rx and Tx0
  IrRxTx1    = 2,                     ///< Rx and Tx1
  IrRxTx0Tx1 = 3                      ///< Rx and both Tx0,Tx1
} IR_CONFIG;

/// Configuration values for SataClass
typedef enum {
  SataNativeIde = 0,                  ///< Native IDE mode
  SataRaid,                           ///< RAID mode
  SataAhci,                           ///< AHCI mode
  SataLegacyIde,                      ///< Legacy IDE mode
  SataIde2Ahci,                       ///< IDE->AHCI mode
  SataAhci7804,                       ///< AHCI mode as 7804 ID (AMD driver)
  SataIde2Ahci7804                    ///< IDE->AHCI mode as 7804 ID (AMD driver)
} SATA_CLASS;

/// Configuration values for BLDCFG_FCH_GPP_LINK_CONFIG
typedef enum {
  PortA4       = 0,                   ///< 4:0:0:0
  PortA2B2     = 2,                   ///< 2:2:0:0
  PortA2B1C1   = 3,                   ///< 2:1:1:0
  PortA1B1C1D1 = 4                    ///< 1:1:1:1
} GPP_LINKMODE;

/// Configuration values for FchPowerFail
typedef enum {
  AlwaysOff   = 0,                    ///< Always power off after power resumes
  AlwaysOn    = 1,                    ///< Always power on after power resumes
  UsePrevious = 3,                    ///< Resume to same setting when power fails
} POWER_FAIL;


/// Configuration values for SATA Link Speed
typedef enum {
  Gen1   = 1,                         ///< SATA port GEN1 speed
  Gen2   = 2,                         ///< SATA port GEN2 speed
  Gen3   = 3,                         ///< SATA port GEN3 speed
} SATA_SPEED;


/// Configuration values for GPIO function
typedef enum {
  Function0   = 0,                    ///< GPIO Function 1
  Function1   = 1,                    ///< GPIO Function 1
  Function2   = 2,                    ///< GPIO Function 2
  Function3   = 3,                    ///< GPIO Function 3
} GPIO_FUN;

/// Configuration values for memory phy voltage (VDDR)
#define  VOLT0_95   0                 ///< VDDR 0.95V
#define  VOLT1_05   1                 ///< VDDR 1.05V
#define  MAX_VDDR   2                 ///< Maxmum value for this enum definition

/// Configuration values for GPIO_CFG
typedef enum {
  OwnedByEc   = 1 << 0,               ///< This bit can only be written by EC
  OwnedByHost = 1 << 1,               ///< This bit can only be written by host (BIOS)
  Sticky      = 1 << 2,               ///< If set, [6:3] are sticky
  PullUpB     = 1 << 3,               ///< 0: Pullup enable; 1: Pullup disabled
  PullDown    = 1 << 4,               ///< 0: Pulldown disabled; 1: Pulldown enable
  GpioOutEnB  = 1 << 5,               ///< 0: Output enable; 1: Output disable
  GpioOut     = 1 << 6,               ///< Output state when GpioOutEnB is 0
  GpioIn      = 1 << 7,               ///< This bit is read only - current pin state
} CFG_BYTE;

/// Configuration values for GPIO_CFG2
typedef enum {
  DrvStrengthSel_4mA = 0 << 1,               ///< 18:17 DrvStrengthSel.
  DrvStrengthSel_8mA = 1 << 1,               ///< 18:17 DrvStrengthSel.
  DrvStrengthSel_12mA = 2 << 1,              ///< 18:17 DrvStrengthSel.
  DrvStrengthSel_16mA = 3 << 1,              ///< 18:17 DrvStrengthSel.
  PullUpSel_8K     = 1 << 3,                 ///< 19 PullUpSel. Read-write. 0=4 K pull-up is selected. 1=8 K pull-up is selected.
  PullUpEnable    = 1 << 4,                  ///< 20 PullUpEnable. Read-write. 0=Pull-up is disabled on the pin. 1=Pull-up is enabled on the pin.
  PullDownEnable  = 1 << 5,                  ///< 21 PullDownEnable. Read-write. 0=Pull-down is disabled on the pin. 1=Pull-down is enabled on thepin.
  OutputValue     = 1 << 6,                  ///< 22 OutputValue. Read-write. 0=low. 1=high.
  OutputEnable      = 1 << 7,                ///< 23 OutputEnable. Read-write. 0=Output is disabled on the pin. 1=Output is enabled on the pin.
} CFG2_BYTE;

/// FCH GPIO CONTROL
typedef struct {
  IN         UINT8        GpioPin;               ///< Gpio Pin, valid range: 0-67, 128-150, 160-228
  IN         GPIO_FUN     PinFunction;           ///< Multi-function selection
  IN         CFG_BYTE     CfgByte;               ///< GPIO Register value
} GPIO_CONTROL;

///
/// FCH SCI MAP CONTROL
///
typedef struct {
  IN         UINT8        InputPin;              ///< Input Pin, valid range 0-63
  IN         UINT8        GpeMap;                ///< Gpe Map, valid range 0-31
} SCI_MAP_CONTROL;

///
/// FCH SATA PHY CONTROL
///
typedef struct {
  IN         BOOLEAN      CommonPhy;             ///< Common PHY or not
                                                 ///<   @li <b>FALSE</b> - Only applied to specified port
                                                 ///<   @li <b>TRUE</b>  - Apply to all SATA ports
  IN         SATA_SPEED   Gen;                   ///< SATA speed
  IN         UINT8        Port;                  ///< Port number, valid range: 0-7
  IN         UINT32       PhyData;               ///< SATA PHY data, valid range: 0-0xFFFFFFFF
} SATA_PHY_CONTROL;

///
/// FCH Component Data Structure in InitReset stage
///
typedef struct {
  IN       BOOLEAN      UmiGen2;             ///< Enable Gen2 data rate of UMI
                                             ///<   @li <b>FALSE</b> - Disable Gen2
                                             ///<   @li <b>TRUE</b>  - Enable Gen2

  IN       BOOLEAN      SataEnable;          ///< SATA controller function
                                             ///<   @li <b>FALSE</b> - SATA controller is disabled
                                             ///<   @li <b>TRUE</b> - SATA controller is enabled

  IN       BOOLEAN      IdeEnable;           ///< SATA IDE controller mode enabled/disabled
                                             ///<   @li <b>FALSE</b> - IDE controller is disabled
                                             ///<   @li <b>TRUE</b> - IDE controller is enabled

  IN       BOOLEAN      GppEnable;           ///< Master switch of GPP function
                                             ///<   @li <b>FALSE</b> - GPP disabled
                                             ///<   @li <b>TRUE</b> - GPP enabled

  IN       BOOLEAN      Xhci0Enable;         ///< XHCI0 controller function
                                             ///<   @li <b>FALSE</b> - XHCI0 controller disabled
                                             ///<   @li <b>TRUE</b> - XHCI0 controller enabled

  IN       BOOLEAN      Xhci1Enable;         ///< XHCI1 controller function
                                             ///<   @li <b>FALSE</b> - XHCI1 controller disabled
                                             ///<   @li <b>TRUE</b> - XHCI1 controller enabled
} FCH_RESET_INTERFACE;


///
/// FCH Component Data Structure from InitEnv stage
///
typedef struct {
  IN       SD_MODE      SdConfig;            ///< Secure Digital (SD) controller mode
  IN       HDA_CONFIG   AzaliaController;    ///< Azalia HD Audio Controller

  IN       IR_CONFIG    IrConfig;            ///< Infrared (IR) Configuration
  IN       BOOLEAN      UmiGen2;             ///< Enable Gen2 data rate of UMI
                                             ///<   @li <b>FALSE</b> - Disable Gen2
                                             ///<   @li <b>TRUE</b>  - Enable Gen2

  IN       SATA_CLASS   SataClass;           ///< SATA controller mode
  IN       BOOLEAN      SataEnable;          ///< SATA controller function
                                             ///<   @li <b>FALSE</b> - SATA controller is disabled
                                             ///<   @li <b>TRUE</b> - SATA controller is enabled

  IN       BOOLEAN      IdeEnable;           ///< SATA IDE controller mode enabled/disabled
                                             ///<   @li <b>FALSE</b> - IDE controller is disabled
                                             ///<   @li <b>TRUE</b> - IDE controller is enabled

  IN       BOOLEAN      SataIdeMode;         ///< Native mode of SATA IDE controller
                                             ///<   @li <b>FALSE</b> - Legacy IDE mode
                                             ///<   @li <b>TRUE</b> - Native IDE mode

  IN       BOOLEAN      Ohci1Enable;         ///< OHCI controller #1 Function
                                             ///<   @li <b>FALSE</b> - OHCI1 is disabled
                                             ///<   @li <b>TRUE</b> - OHCI1 is enabled

  IN       BOOLEAN      Ohci2Enable;         ///< OHCI controller #2 Function
                                             ///<   @li <b>FALSE</b> - OHCI2 is disabled
                                             ///<   @li <b>TRUE</b> - OHCI2 is enabled

  IN       BOOLEAN      Ohci3Enable;         ///< OHCI controller #3 Function
                                             ///<   @li <b>FALSE</b> - OHCI3 is disabled
                                             ///<   @li <b>TRUE</b> - OHCI3 is enabled

  IN       BOOLEAN      Ohci4Enable;         ///< OHCI controller #4 Function
                                             ///<   @li <b>FALSE</b> - OHCI4 is disabled
                                             ///<   @li <b>TRUE</b> - OHCI4 is enabled

  IN       BOOLEAN      GppEnable;           ///< Master switch of GPP function
                                             ///<   @li <b>FALSE</b> - GPP disabled
                                             ///<   @li <b>TRUE</b> - GPP enabled

  IN       POWER_FAIL   FchPowerFail;        ///< FCH power failure option
} FCH_INTERFACE;

#endif // _FCHCOMMON_H_

