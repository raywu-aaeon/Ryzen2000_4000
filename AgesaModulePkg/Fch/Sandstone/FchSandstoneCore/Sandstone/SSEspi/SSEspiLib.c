/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch ESPI controller
 *
 * Init ESPI features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
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
#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE FCH_SANDSTONE_FCHSANDSTONECORE_SANDSTONE_SSESPI_SSESPILIB_FILECODE

#define MAX_ESPI_RETRY     100000          // 100ms

#define SET_CONFIGURATION  0
#define GET_CONFIGURATION  1
#define IN_BAND_RESET      2
#define PC_MSG_DOWN_STREAM 4
#define VM_DOWN_STREAM     5
#define OOB_DOWN_STREAM    6

#define SLAVE_REG_ID           0x04
#define SLAVE_GENERAL_CAPCFG   0x08
#define SLAVE_PC_CAPCFG        0x10
#define SLAVE_VW_CAPCFG        0x20
#define SLAVE_OOB_CAPCFG       0x30
#define SLAVE_FA_CAPCFG        0x40
#define SLAVE_MEC1701_SCRATCH_REG 0x80      // This is a scratch register of MEC1701 eSPI and does nothing.

//ESPIx00
#define DNCMD_STATUS       BIT3

//ESPIx2C Master Capability
#define MASTER_FA_SUPPORT                   BIT0
#define MASTER_OOB_SUPPORT                  BIT1
#define MASTER_VW_SUPPORT                   BIT2
#define MASTER_PERIPHERAL_SUPPORT           BIT3

//ESPIx68  Slave0 Configuration
#define SLAVE_FA_ENABLE                     BIT0
#define SLAVE_OOB_ENABLE                    BIT1
#define SLAVE_VW_ENABLE                     BIT2
#define SLAVE_PC_ENABLE             BIT3

//SLAVE offset 0x08   SLAVE_GENERAL_CAPCFG
#define SLAVE_FA_SUPPORT                    BIT3
#define SLAVE_OOB_SUPPORT                   BIT2
#define SLAVE_VW_SUPPORT                    BIT1
#define SLAVE_PERIPHERAL_SUPPORT            BIT0

/// eSPIx00 eSPI Software Specific Register 0
typedef union {
  struct {
    UINT32      SWCommandType:3;
    UINT32      CommandStatus:1;
    UINT32      SlaveNSelect:2;
    UINT32      Reserved_7_6:2;
    UINT32      AddrByte0PCycTypeVWCntOOBCycType:8;
    UINT32      AddrByte0VWIdxOOBPktByte1:8;
    UINT32      VWDataOOBPktByte2:8;
  } Field;
  UINT32 Value;
} ESPIx00_DN_DXHDR0;

/// eSPIx04 eSPI Software Specific Register 1
typedef union {
  struct {
    UINT32      VWIdxOOBPktbyte3:8;
    UINT32      VWDataOOBByteCnt:8;
    UINT32      VWIdxOOBPktByte5:8;
    UINT32      VWDataOOBPktByte6:8;
  } Field;
  UINT32 Value;
} ESPIx04_DN_DXHDR1;

/// eSPIx2C eSPI Master Capability
typedef union {
  struct {
    UINT32      FlashAccessChannelSupport:1;
    UINT32      OOBMessageChannelSupport:1;
    UINT32      VWChannelSupport:1;
    UINT32      PChannelSupport:1;
    UINT32      MasterVersion:3;
    UINT32      FlashAccessChannelMaxPayload:3;
    UINT32      OOBMessageChannelMaxPayload:3;
    UINT32      OperatingMaxVWCount:6;
    UINT32      PChannelMaxPayloadSize:3;
    UINT32      NumberOfSlave:3;
    UINT32      OperatingSupportFreq:3;
    UINT32      IOMode:2;
    UINT32      AlertMode:1;
    UINT32      CRCCheck:1;
  } Field;
  UINT32 Value;
} ESPIx2C_MASTER_CAP;

/// eSPIx68 eSPI Slave N Configuration
typedef union {
  struct {
    UINT32      FlashAccessChannelEnable:1;
    UINT32      OOBMessageChannelEnable:1;
    UINT32      VWChannelEnable:1;
    UINT32      PChannelEnable:1;
    UINT32      OOBValidBitEnable:1;
    UINT32      Reserved_24_5:20;
    UINT32      OperatingFreq:3;
    UINT32      IOModeSelect:2;
    UINT32      AlertMode:1;
    UINT32      CRCCheckingEnable:1;
  } Field;
  UINT32 Value;
} ESPIx68_SLAVE0_CONFIG;

///
/// Slave Registers
///
/// Offset 04h: Device Identification
typedef union {
  struct {
    UINT32      RO_VersionID:8;
    UINT32      Reserved_31_8:24;
  } Field;
  UINT32 Value;
} ESPI_SL04_DEVICE_ID;

/// Offset 08h: General Capabilities and Configurations
typedef union {
  struct {
    UINT32      RO_PCSupported:1;
    UINT32      RO_VWSupported:1;
    UINT32      RO_OOBMsgSupported:1;
    UINT32      RO_FASupported:1;
    UINT32      Reserved_7_3:4;
    UINT32      Reserved_11_8:4;
    UINT32      RO_MaxWaitStateAllowed:4;
    UINT32      RO_MaxFreqSupported:3;
    UINT32      RO_OpenDrainAlertSupported:1;
    UINT32      OperatingFreq:3;
    UINT32      OpenDrainAlertSelect:1;
    UINT32      RO_IOModeSupported:2;
    UINT32      IOModeSelect:2;
    UINT32      AlertMode:1;
    UINT32      Reserved_29:1;
    UINT32      ResponseModifierEn:1;
    UINT32      CRCCheckingEn:1;
  } Field;
  UINT32 Value;
} ESPI_SL08_SLAVE_GENERAL_CAPCFG;

/// Offset 10h: Channel 0 Capabilities and Configurations
typedef union {
  struct {
    UINT32      PCEn:1;
    UINT32      RO_PCReady:1;
    UINT32      BusMasterEn:1;
    UINT32      Reserved_3:1;
    UINT32      RO_PCMaxPayloadSizeSupported:3;
    UINT32      Reserved_7:1;
    UINT32      PCMaxPayloadSizeSelected:3;
    UINT32      Reserved_11:1;
    UINT32      PCMaxReadRequestSize:3;
    UINT32      Reserved_31_15:17;
  } Field;
  UINT32 Value;
} ESPI_SL10_SLAVE_PC_CAPCFG;

/// Offset 20h: Channel 1 Capabilities and Configurations
typedef union {
  struct {
    UINT32      VWEn:1;
    UINT32      RO_VWReady:1;
    UINT32      Reserved_7_2:6;
    UINT32      RO_MaxVWCntSupported:6;
    UINT32      Reserved_15_14:2;
    UINT32      OpMaxVWCnt:6;
    UINT32      Reserved_31_22:10;
  } Field;
  UINT32 Value;
} ESPI_SL20_SLAVE_VW_CAPCFG;

/// Offset 30h: Channel 2 Capabilities and Configurations
typedef union {
  struct {
    UINT32      OOBEn:1;
    UINT32      RO_OOBReady:1;
    UINT32      Reserved_3_2:2;
    UINT32      RO_MsgChMaxPayloadSizeSupported:3;
    UINT32      Reserved_7:1;
    UINT32      MsgChMaxPayloadSizeSelected:3;
    UINT32      Reserved_31_11:21;
  } Field;
  UINT32 Value;
} ESPI_SL30_SLAVE_OOB_CAPCFG;

/// Offset 40h: Channel 2 Capabilities and Configurations
typedef union {
  struct {
    UINT32      FAEn:1;
    UINT32      RO_FAReady:1;
    UINT32      FlashBlockEraseSize:3;
    UINT32      RO_ChMaxPayloadSizeSupported:3;
    UINT32      ChMaxPayloadSizeSelected:3;
    UINT32      RO_FlashSharingMode:1;
    UINT32      ChMaxReadReqSize:3;
    UINT32      Reserved_31_15:17;
  } Field;
  UINT32 Value;
} ESPI_SL40_SLAVE_FA_CAPCFG;


UINT32 getESPIBase ()
{
  UINT32 base;
  ReadPci ((LPC_BUS_DEV_FUN << 16) + 0xA0, AccessWidth32, &base, NULL);
  base &= 0xFFFFFFC0;
  base += 0x00010000;

  // eSPI Master Capability
  if ( ACPIMMIO32 (base + 0x2C) == 0 || ACPIMMIO32 (base + 0x2C) == 0xFFFFFFFF) {
    ASSERT (FALSE);
  }

  return base;
}
/*
void wait4stClear ()
{
    while(eSPIx00.Field.CommandStatus) {
        IoWrite16(0x80, 0xE291); // delay
        IoRead8(0x404);          // delay
    }
}
*/
VOID
wait4stClear (
  IN  UINT32     EspiBase
  )
{
  UINT32 Retry;

  for ( Retry = 0; Retry < MAX_ESPI_RETRY; Retry++ ) {
    if ( (ACPIMMIO32 (EspiBase + 0x00) & DNCMD_STATUS) == 0 ) {
      break;
    }
    //FchStall (2, NULL);
    IoWrite16(0x80, 0xE291); // delay
  }
}
/*
void eSPI_InBandRst (UINT32 slave)
{
    eSPIx00.Field.CommandStatus = 0;
    wait4stClear();
    eSPIx00.Field.SlaveNSelect = slave;
    eSPIx68.Field.OperatingFreq = 0;
    eSPIx00.Field.SWCommandType = IN_BAND_RESET;
    eSPIx00.Field.CommandStatus = 1;
    wait4stClear();
}
*/
VOID
SSeSPI_InBandRst  (
  IN  UINT32     EspiBase
  )
{
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, 0x00);
  wait4stClear (EspiBase);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)(BIT4 + BIT5), 0x00);
  RwMem (EspiBase + 0x68, AccessWidth32, 0xF1FFFFFF, 0x00);              // [27:25] CLK_FREQ_SEL
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFFFFFFF8, IN_BAND_RESET);     // [2:0] DNCMD_TYPE
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, BIT3);
  wait4stClear (EspiBase);
}

/*
UINT32 eSPI_GetConfiguration(UINT32 slave, UINT16 offset)
{
    wait4stClear();
    eSPIx00.Field.SlaveNSelect = slave;
    eSPIx00.Field.SWCommandType = GET_CONFIGURATION;
    eSPIx00.Field.AddrByte0PCycTypeVWCntOOBCycType = ((offset >> 8) & 0xFF);
    eSPIx00.Field.AddrByte0VWIdxOOBPktByte1 = (offset & 0xFF);
    eSPIx04.Value = 0;
    eSPIx00.Field.CommandStatus = 1;
    wait4stClear();
    return eSPIx04.Value;
}
*/
UINT32
SSeSPI_GetConfiguration  (
  IN  UINT32     EspiBase,
  IN  UINT32     RegAddr
  )
{
  wait4stClear (EspiBase);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32) (BIT4 + BIT5), 0x00);
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFFFFFFF8, GET_CONFIGURATION);     // [2:0] DNCMD_TYPE
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFF00FFFF, (RegAddr & 0xFF) << 16);
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFFFF00FF, RegAddr & 0xFF00);
  RwMem (EspiBase + 0x04, AccessWidth32, 0x00, 0x00);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, BIT3);
  wait4stClear (EspiBase);
  return ACPIMMIO32 (EspiBase + 0x04);
}

/*
void eSPI_SetConfiguration (UINT32 slave, UINT32 offset, UINT32 value)
{
    wait4stClear();
    eSPIx00.Field.SlaveNSelect = slave;
    eSPIx00.Field.SWCommandType = SET_CONFIGURATION;
    eSPIx00.Field.AddrByte0PCycTypeVWCntOOBCycType = ((offset >> 8) & 0xFF);
    eSPIx00.Field.AddrByte0VWIdxOOBPktByte1 = (offset & 0xFF);
    eSPIx04.Value = value;
    eSPIx00.Field.CommandStatus = 1;
    wait4stClear();
}
*/
VOID
SSeSPI_SetConfiguration  (
  IN  UINT32     EspiBase,
  IN  UINT32     RegAddr,
  IN  UINT32     Value
  )
{
  wait4stClear (EspiBase);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32) (BIT4 + BIT5), 0x00);
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFFFFFFF8, SET_CONFIGURATION);     // [2:0] DNCMD_TYPE
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFF00FFFF, (RegAddr & 0xFF) << 16);
  RwMem (EspiBase + 0x00, AccessWidth32, 0xFFFF00FF, RegAddr & 0xFF00);
  RwMem (EspiBase + 0x04, AccessWidth32, 0x00, Value);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, BIT3);
  wait4stClear (EspiBase);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SSeSPI_PltResetAssert - Assert PltReset#
 *
 *  STEP 1: Poll DN_TXHDR_0th.DNCMD_STATUS=0
 *  STEP 2: Program DN_TXHDR_0th=0x005
 *  STEP 3: Program DN_TXHDR_1=0x0                    // Not mentioned in the sequence as default is 0(but better program to 0 in case there was programming before)
 *  STEP 4: Program DN_TXHDR_2=0x0                    // Not mentioned in the sequence as default is 0(but better program to 0 in case there was programming before)
 *  STEP 5: Program DN_TXDATA_PORT=0x2003             // Assert PLTRST#
 *  STEP 6: Program DN_TXHDR_0=0x00D                  // Set Status bit and wait for HW to clear it.
 *
 *
 *  @param[in] EspiBase      ESPI MMIO base.
 */
VOID
SSeSPI_PltResetAssert (
  IN  UINT32     EspiBase
  )
{
  wait4stClear (EspiBase);
  RwMem (EspiBase + 0x00, AccessWidth32, 0x00, 0x05);
  RwMem (EspiBase + 0x04, AccessWidth32, 0x00, 0x00);
  RwMem (EspiBase + 0x08, AccessWidth32, 0x00, 0x00);
  RwMem (EspiBase + 0x0C, AccessWidth32, 0x00, 0x2003);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, BIT3);
  wait4stClear (EspiBase);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SSeSPI_PltResetDeassert - De-assert PltReset#
 *
 *  STEP 1: Poll DN_TXHDR_0th.DNCMD_STATUS=0
 *  STEP 2: Program DN_TXHDR_0th=0x005
 *  STEP 3: Program DN_TXHDR_1=0x0                    // Not mentioned in the sequence as default is 0(but better program to 0 in case there was programming before)
 *  STEP 4: Program DN_TXHDR_2=0x0                    // Not mentioned in the sequence as default is 0(but better program to 0 in case there was programming before)
 *  STEP 5: Program DN_TXDATA_PORT=0x2203             // De-assert PLTRST#
 *  STEP 6: Program DN_TXHDR_0=0x00D                  // Set Status bit and wait for HW to clear it.
 *
 *
 *  @param[in] EspiBase      ESPI MMIO base.
 */
VOID
SSeSPI_PltResetDeassert (
  IN  UINT32     EspiBase
  )
{
  wait4stClear (EspiBase);
  RwMem (EspiBase + 0x00, AccessWidth32, 0x00, 0x05);
  RwMem (EspiBase + 0x04, AccessWidth32, 0x00, 0x00);
  RwMem (EspiBase + 0x08, AccessWidth32, 0x00, 0x00);
  RwMem (EspiBase + 0x0C, AccessWidth32, 0x00, 0x2203);
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)BIT3, BIT3);
  wait4stClear (EspiBase);
}

/**
 * FchinitTSEspiSlave0Device - Config ESPI controller and device
 *
 *  // It recommends software to do device initialization
 *  sequence as below:
 *  // 1. Set Master SlaveN Configuration register
 *  (MMIO_reg0x68) Clock Frequency to 16.7Mhz, then send In-Band
 *  Reset.
 *  // 2. Get_Configuration to read Slave Device Capability
 *  Register.
 *  // 3. Set_Configuration to write Slave Device General
 *  Configuration Register, such as CRC, IO mode, Alert mode,
 *  Clock Frequency.
 *  // 4. Change Master SlaveN Configuration registers
 *  (MMIO_reg0x68), make sure Master SlaveN's configuration is
 *  same as device.
 *  // 5. Get_Configuration to read Slave Device's each channel
 *  Capablity Register.
 *  // 6. Set_Configuration to write Slave Device's each channel
 *  Configuration Register.
 *  // 7. Get_Configuration to read Slave Device's each channel
 *  ready bit, wait for each channel ready.
 *  // 8. Enable Master SlaveN Configuration registers
 *  (MMIO_reg0x68) to enable each channel's enable bit.
 *
 * @param[in] EspiBase ESPI MMIO base.
 *
 */
VOID
FchinitSSEspiSlave0Device (
  IN  VOID       *FchDataPtr,
  IN  UINT32     EspiBase
  )
{
  ESPIx2C_MASTER_CAP              MasterCapibility;
  ESPIx68_SLAVE0_CONFIG           Slave0Config;
  ESPI_SL08_SLAVE_GENERAL_CAPCFG  DeviceCapCfg;
  ESPI_SL10_SLAVE_PC_CAPCFG       SlavePCCapCfg;
  ESPI_SL20_SLAVE_VW_CAPCFG       SlaveVWCapCfg;
  ESPI_SL30_SLAVE_OOB_CAPCFG      SlaveOOBCapCfg;
  ESPI_SL40_SLAVE_FA_CAPCFG       SlaveFACapCfg;
  FCH_RESET_DATA_BLOCK            *LocalCfgPtr;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  //
  // 1, In-Band Reset
  //
  SSeSPI_InBandRst (EspiBase);

  // Use dedicated Alert# pin. Otherwise SPI_GetConfiguration will failed.
  // No effect if set it before In-Band Reset
  ACPIMMIO32 (EspiBase + 0x68) |= 0x40000000;

  //
  // 2 - 4, check and update Slave Device Capability and Slave0 configuration
  //
  MasterCapibility.Value = ACPIMMIO32 (EspiBase + 0x2C);
  DeviceCapCfg.Value     = SSeSPI_GetConfiguration (EspiBase, SLAVE_GENERAL_CAPCFG);
  Slave0Config.Value     = 0;
  //
  // Check support for each channel
  //
  if ( MasterCapibility.Field.FlashAccessChannelSupport && DeviceCapCfg.Field.RO_FASupported ) {
    Slave0Config.Field.FlashAccessChannelEnable = 1;
  }

  if ( MasterCapibility.Field.OOBMessageChannelSupport && DeviceCapCfg.Field.RO_OOBMsgSupported ) {
    Slave0Config.Field.OOBMessageChannelEnable = 1;
  }

  if ( MasterCapibility.Field.VWChannelSupport && DeviceCapCfg.Field.RO_VWSupported ) {
    Slave0Config.Field.VWChannelEnable = 1;
  }

  if ( MasterCapibility.Field.PChannelSupport && DeviceCapCfg.Field.RO_PCSupported ) {
    Slave0Config.Field.PChannelEnable = 1;
  }

  //Operating Support Frequency in FCH eSPI Registers
  //000b 16.7 MHz
  //001b 16.7 MHz, 33 MHz
  //011b 16.7 MHz, 33 MHz, 66 MHz

  //Operating Frequency in FCH eSPI Registers
  //000b 16.6 MHz.
  //001b 33 MHz.
  //010b 66 MHz.
  //111b-011b Reserved

  //General Capabilities and Configurations in eSPI Spec v1.0
  //Bits Frequency
  //000b 20 MHz
  //001b 25 MHz
  //010b 33 MHz
  //011b 50 MHz
  //100b 66 MHz
  //Others Reserved
  if ((MasterCapibility.Field.OperatingSupportFreq == 0x03) && (DeviceCapCfg.Field.RO_MaxFreqSupported == 0x04) && (LocalCfgPtr->Espi.OperatingFreq >= 0x02)){  //66MHz
    Slave0Config.Field.OperatingFreq = 0x02;
    DeviceCapCfg.Field.OperatingFreq = 0x04;
  }else if ((MasterCapibility.Field.OperatingSupportFreq >= 0x01) && (DeviceCapCfg.Field.RO_MaxFreqSupported >= 0x02) && (LocalCfgPtr->Espi.OperatingFreq >= 0x01)){  //33MHz
    Slave0Config.Field.OperatingFreq = 0x01;
    DeviceCapCfg.Field.OperatingFreq = 0x02;
  }else { //16.7MHz
    Slave0Config.Field.OperatingFreq = 0x00;
    DeviceCapCfg.Field.OperatingFreq = 0x00;
  }

  //
  // I/O Mode Select:
  //
  //
  //Operating Support Mode in FCH eSPI Registers
  //00b Single IO
  //01b Dual IO, Single IO
  //10b Quad IO, Dual IO, Single IO
  //11b Reserved

  //I/O Mode Support in eSPI Spec v1.0
  //00b Single I/O
  //01b Single and Dual I/O
  //10b Single and Quad I/O
  //11b Single, Dual and Quad I/O

  //I/O Mode Select in eSPI v1.0 and in FCH eSPI Registers
  //00b Single I/O
  //01b Dual I/O
  //10b Quad I/O
  //11b Reserved
  if ( (MasterCapibility.Field.IOMode == 2) && (DeviceCapCfg.Field.RO_IOModeSupported & BIT1) && (LocalCfgPtr->Espi.IoMode >= 0x02)) {
    // Quad Mode
    Slave0Config.Field.IOModeSelect = 0x02;
    DeviceCapCfg.Field.IOModeSelect = 0x02;
  } else if ( (MasterCapibility.Field.IOMode >= 1) && (DeviceCapCfg.Field.RO_IOModeSupported & BIT0) && (LocalCfgPtr->Espi.IoMode >= 0x01)) {
    // Dual Mode
    Slave0Config.Field.IOModeSelect = 0x01;
    DeviceCapCfg.Field.IOModeSelect = 0x01;
  } else {
    // single Mode
    Slave0Config.Field.IOModeSelect = 0x00;
    DeviceCapCfg.Field.IOModeSelect = 0x00;
  }

  //
  // Alert Mode
  //
  Slave0Config.Field.AlertMode = MasterCapibility.Field.AlertMode;
  DeviceCapCfg.Field.AlertMode = MasterCapibility.Field.AlertMode;

  //
  // CRC Checking
  //
  Slave0Config.Field.CRCCheckingEnable = MasterCapibility.Field.CRCCheck;
  DeviceCapCfg.Field.CRCCheckingEn     = MasterCapibility.Field.CRCCheck;

  //
  // update Device configuration and Slave0 configuration
  //
  SSeSPI_SetConfiguration (EspiBase, SLAVE_GENERAL_CAPCFG, DeviceCapCfg.Value);
  ACPIMMIO32 (EspiBase + 0x68) = (Slave0Config.Value & 0xFFFFFFF0);

  //
  // 5 - 8 Configure and enable channels
  //
  // FA Channel
  //
  if ( Slave0Config.Field.FlashAccessChannelEnable ) {
    SlaveFACapCfg.Value      = SSeSPI_GetConfiguration (EspiBase, SLAVE_FA_CAPCFG);
    SlaveFACapCfg.Field.FAEn = 1;
    SSeSPI_SetConfiguration (EspiBase, SLAVE_FA_CAPCFG, SlaveFACapCfg.Value);
    do {
      SlaveFACapCfg.Value = SSeSPI_GetConfiguration (EspiBase, SLAVE_FA_CAPCFG);
      IoWrite16(0x80, 0xE292); // delay
    } while (!SlaveFACapCfg.Field.RO_FAReady);
    ACPIMMIO32(EspiBase + 0x68) |= SLAVE_FA_ENABLE;
  }

  //
  // OOB Channel
  //
  if ( Slave0Config.Field.OOBMessageChannelEnable ) {
    SlaveOOBCapCfg.Value       = SSeSPI_GetConfiguration (EspiBase, SLAVE_OOB_CAPCFG);
    SlaveOOBCapCfg.Field.OOBEn = 1;
    SSeSPI_SetConfiguration (EspiBase, SLAVE_OOB_CAPCFG, SlaveOOBCapCfg.Value);
    do {
      SlaveOOBCapCfg.Value = SSeSPI_GetConfiguration (EspiBase, SLAVE_OOB_CAPCFG);
      IoWrite16 (0x80, 0xE292); // delay
    } while (!SlaveOOBCapCfg.Field.RO_OOBReady);
    ACPIMMIO32 (EspiBase + 0x68) |= SLAVE_OOB_ENABLE;
  }

  //
  // VW Channel
  //
  if ( Slave0Config.Field.VWChannelEnable ) {
    SlaveVWCapCfg.Value      = SSeSPI_GetConfiguration (EspiBase, SLAVE_VW_CAPCFG);
    SlaveVWCapCfg.Field.VWEn = 1;
    SSeSPI_SetConfiguration (EspiBase, SLAVE_VW_CAPCFG, SlaveVWCapCfg.Value);
    do {
      SlaveVWCapCfg.Value = SSeSPI_GetConfiguration (EspiBase, SLAVE_VW_CAPCFG);
      IoWrite16 (0x80, 0xE292); // delay
    } while (!SlaveVWCapCfg.Field.RO_VWReady);
    ACPIMMIO32 (EspiBase + 0x68) |= SLAVE_VW_ENABLE;
//<Embedded_Override_Start>
// Since below Power sequence is for VWChannel, it should be done only when VWChannel is enabled
#if ESPI_SIO_SUPPORT
  //De-assert PLTRST#
  SSeSPI_PltResetDeassert (EspiBase);
#endif 
  }
//<Embedded_Override_End>
  //
  // PC Channel
  //
  if ( Slave0Config.Field.PChannelEnable ) {
    SlavePCCapCfg.Value      = SSeSPI_GetConfiguration (EspiBase, SLAVE_PC_CAPCFG);
    SlavePCCapCfg.Field.PCEn = 1;
    SSeSPI_SetConfiguration (EspiBase, SLAVE_PC_CAPCFG, SlavePCCapCfg.Value);
    do {
      SlavePCCapCfg.Value = SSeSPI_GetConfiguration (EspiBase, SLAVE_PC_CAPCFG);
      IoWrite16 (0x80, 0xE292); // delay
    } while (!SlavePCCapCfg.Field.RO_PCReady);
    ACPIMMIO32 (EspiBase + 0x68) |= SLAVE_PC_ENABLE;
  }
}

/**
 * FchinitEspiIoMux - Config ESPI controller
 *
 *
 *
 */
VOID
FchinitSSEspiIoMux ()
{
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x75, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x76, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x77, AccessWidth8, 0x00, 0x01);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x78, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x79, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x7A, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x7B, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x81, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x85, AccessWidth8, 0x00, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x1E, AccessWidth8, 0x00, 0x01); // ESPI_CS_L

  // To enable dedicated Alert pin. (ESPI_ALERT)
  // D14F3x78[3,2] = 00b;
  // D14F3x78[9,  LDRQ0_PU_EN] = 1b; Reset 0;
  // D14F3x78[10, LDRQ0_PD_EN] = 0b; Reset 1;
  RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG78), AccessWidth32, 0xFFFFF9F3, 0x00000200, NULL);
}

/**
 * EspiEc0DisableLpcDecoding - Config ESPI controller
 *
 *
 */
VOID
EspiEc0DisableLpcDecoding ()
{
  RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, ~(UINT32)(BIT30 + BIT29 + BIT23 + BIT3), 0x00, NULL);          // 60h/64h, 62h/66h, 6xxh
  RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG48), AccessWidth8, 0xFC, 0x00, NULL);                                      // 2E/2F, 4E/4F
}

/**
 * FchinitTSEspiEnableKbc6064 - Config ESPI controller
 *
 * @param[in] Enable Enable/disable ESPI 60h/64h decoding.
 */
VOID
FchinitSSEspiEnableKbc6064 (
  IN  BOOLEAN     Enable
  )
{
  UINT32     EspiBase;

  EspiBase = getESPIBase ();

  if ( Enable ) {
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, ~(UINT32)BIT29, 0x00, NULL);          // disable LPC 60h/64h
    RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT1, BIT1);                                                // 60h/64h
  } else {
    RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT1, 0x00);                                                // 60h/64h
  }

}
/**
 * FchinitTSEspiTimer - Config ESPI controller
 *
 *
 *
 * @param[in] EspiBase ESPI MMIO base.
 *
 */
VOID
FchinitSSEspiTimer (
  IN  UINT32     EspiBase
  )
{
  // eSPIx30 [29:24, WaitStateCounter]     = 00h,
  //         [23:8,  WatchDogCounter]      = 0FFFh,
  //         [6:4,   Glb_Alink_Idle_Timer] = 111b - 2048 clocks
  RwMem (EspiBase + 0x30, AccessWidth32, 0xFF00008F, 0x000FFF70);
  RwMem (EspiBase + 0x30, AccessWidth32, ~(UINT32)BIT0, BIT0);                            // WDG_EN
  RwMem (EspiBase + 0x30, AccessWidth32, ~(UINT32)BIT1, BIT1);                            // WAIT_CHKEN.
}

/**
 * FchinitTSEspiEc0 - Config ESPI controller
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchinitSSEspiEc0 (
  IN  VOID     *FchDataPtr
  )
{
  UINT32     EspiBase;

  EspiBase = getESPIBase ();

  EspiEc0DisableLpcDecoding ();

  //6.1 eSPI Control Register Initialization
  //  1  Enable PCI Bus Watch Dog Timer
  //  2  Enable eSPI Bus Wait State Control Timer
  //  3  Enable eSPI clock gating function if neeed.
  //  4  Set each SlaveN Error Interrupt Enable.
  //  5  Set eSPI Controller ERROR interrupt Mapping, default is SMI.
  //  6  Set eSPI error protection bit if needed.
  //  7  Set each SlaveN Register command interrupt Enable.
  //  8  Set eSPI Register Command interrupt Mapping, default is SMI.
  //  9  Set each SlaveN IO Range, MMIO Range and decoding enable.
  //  10 Enable eSPI subtractive decoding if needed
  //  11 Assign IRQ0~IRQ23 to each SlaveN by setting each SlaveN IRQ Mask bit, IRQ plority.
  //  12 Enable Configurable Virtual Wire Index/Data Received Register.
  //  13 Set eSPI Bus Master Enable.

  //  eSPIx00[5:4, SlaveNSelect] = 00b - Slave 0 selected.
  //  Make sure the following operation is for slave 0
  RwMem (EspiBase + 0x00, AccessWidth32, ~(UINT32)(BIT4 + BIT5), 0x00);                   // Select Slave0

  FchinitSSEspiTimer (EspiBase);                                                            // 1 - 2

  //FchinitEspiClockGating (0, EspiBase);                                                 // 3
  //FchinitEspiErrCmdInterrupt (0, EspiBase);                                             // 4 - 8
  //FchinitEspiDecoding (0, EspiBase);                                                    // 9 - 10
  FchinitSSEspiIoDecode(FchDataPtr);
  FchinitSSEspiMmioDecode(FchDataPtr);
  RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT1, BIT1);                            // 60h/64h
//<Embedded_Override_Start>
#if ESPI_SIO_SUPPORT
  RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT0, BIT0); // 2E/2Fh
#endif
//<Embedded_Override_End>
  // CRCCheckingEnable/AlertMode; OOBValidBitEnable/PChannelEnable/VWChannelEnable/OOBMessageChannelEnable
  //RwMem (EspiBase + 0x68, AccessWidth32, 0x00, 0xC000001E);
  //FchinitEspiVWIrq (0, EspiBase);                                                       // 11 - 12
  RwMem (EspiBase + 0xA4, AccessWidth32, 0x00, 0x00040506);
  RwMem (EspiBase + 0xA8, AccessWidth32, 0x00, 0x00000007);
  RwMem (EspiBase + 0xAC, AccessWidth32, 0x00, 0x00001002);

  RwMem (EspiBase + 0x34, AccessWidth32, ~(UINT32)BIT1, BIT1);                            // BUS_MASTER_EN

  RwMem (EspiBase + 0x6C, AccessWidth32, 0x00, 0xFFFFFFFF);                               // Enable interrupt at last - CZ

  FchinitSSEspiSlave0Device (FchDataPtr, EspiBase);
}

VOID
FchinitSSEspiEnableIo80 (
  IN  BOOLEAN     Enable
  )
{
  UINT32       EspiBase;
  
  EspiBase = getESPIBase();
  if (Enable){
    RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT2, BIT2);                            // Enable 80 IO decode
  }else{
    RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT2, 0x00);                            // Disable 80 IO decode  
  }
}

/**
 * FchinitSSEspiIoDecode - Config ESPI controller
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 */
VOID
FchinitSSEspiIoDecode (
    IN  VOID       *FchDataPtr
  )
{
  UINT32                          EspiBase;
  FCH_RESET_DATA_BLOCK            *LocalCfgPtr;
  UINT32                          Slave0DecodeEnBitMap = 0; // BIT8 - IO Range 0, BIT9 - IO Range 1, BIT10 - IO Range 2, BIT11 - IO Range 3
  UINT32                          Slave0IoBaseReg0 = 0;
  UINT32                          Slave0IoBaseReg1 = 0;
  UINT32                          Slave0IoSize = 0;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  EspiBase = getESPIBase ();

  if (LocalCfgPtr->Espi.Decode.Io[0].Enable){
    Slave0IoBaseReg0 &= 0xFFFF0000;
    Slave0IoBaseReg0 |= LocalCfgPtr->Espi.Decode.Io[0].Base;        // IO range
    Slave0IoSize &= 0xFFFFFF00;
    Slave0IoSize |= LocalCfgPtr->Espi.Decode.Io[0].Size;            // IO range size
    Slave0DecodeEnBitMap |= BIT8;                                   // Enable IO range 0
  }else{
    Slave0DecodeEnBitMap &= (~BIT8);                                // Disable IO range 0
  }
  if (LocalCfgPtr->Espi.Decode.Io[1].Enable){
    Slave0IoBaseReg0 &= 0x0000FFFF;
    Slave0IoBaseReg0 |= ((UINT32)(LocalCfgPtr->Espi.Decode.Io[1].Base) << 16);// IO range
    Slave0IoSize &= 0xFFFF00FF;
    Slave0IoSize |= ((UINT32)(LocalCfgPtr->Espi.Decode.Io[1].Size) << 8);    // IO range size
    Slave0DecodeEnBitMap |= BIT9;                                           // Enable IO range 1
  }else{
    Slave0DecodeEnBitMap &= (~BIT9);                                        // Disable IO range 1
  }

  if (LocalCfgPtr->Espi.Decode.Io[2].Enable){
    Slave0IoBaseReg1 &= 0xFFFF0000;
    Slave0IoBaseReg1 |= LocalCfgPtr->Espi.Decode.Io[2].Base;                // IO range
    Slave0IoSize &= 0xFF00FFFF;
    Slave0IoSize |= ((UINT32)(LocalCfgPtr->Espi.Decode.Io[2].Size) << 16);  // IO range size
    Slave0DecodeEnBitMap |= BIT10;                                          // Enable IO range 2
  }else{
    Slave0DecodeEnBitMap &= (~BIT10);                                       // Disable IO range 2
  }

  if (LocalCfgPtr->Espi.Decode.Io[3].Enable){
    Slave0IoBaseReg1 &= 0x0000FFFF;
    Slave0IoBaseReg1 |= ((UINT32)(LocalCfgPtr->Espi.Decode.Io[3].Base) << 16);// IO range
    Slave0IoSize &= 0x00FFFFFF;
    Slave0IoSize |= ((UINT32)(LocalCfgPtr->Espi.Decode.Io[3].Size) << 24);   // IO range size
    Slave0DecodeEnBitMap |= BIT11;                                          // Enable IO range 3
  }else{
    Slave0DecodeEnBitMap &= (~BIT11);                                       // Disable IO range 3
  }

  RwMem (EspiBase + 0x44, AccessWidth32, 0x00000000, Slave0IoBaseReg0);                   // IO range
  RwMem (EspiBase + 0x48, AccessWidth32, 0x00000000, Slave0IoBaseReg1);                   // IO range
  RwMem (EspiBase + 0x4C, AccessWidth32, 0x00000000, Slave0IoSize);                       // IO range size
  RwMem (EspiBase + 0x40, AccessWidth32, 0xFFFFF0FF, Slave0DecodeEnBitMap);               // Enable IO range
}

/**
 * FchinitSSEspiMmioDecode - Config ESPI controller
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 */
VOID
FchinitSSEspiMmioDecode (
    IN  VOID       *FchDataPtr
  )
{
  UINT32                          EspiBase;
  FCH_RESET_DATA_BLOCK            *LocalCfgPtr;
  UINT32                          Slave0DecodeEnBitMap = 0; // BIT12 - MMIO Range 0, BIT13 - MMIO Range 1, BIT14 - MMIO Range 2, BIT15 - MMIO Range 3
  UINT32                          Slave0MmioBaseReg0 = 0;
  UINT32                          Slave0MmioBaseReg1 = 0;
  UINT32                          Slave0MmioBaseReg2 = 0;
  UINT32                          Slave0MmioBaseReg3 = 0;
  UINT32                          Slave0MmioSizeReg0 = 0;
  UINT32                          Slave0MmioSizeReg1 = 0;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  EspiBase = getESPIBase ();

  if (LocalCfgPtr->Espi.Decode.Mmio[0].Enable){
    Slave0MmioBaseReg0 = LocalCfgPtr->Espi.Decode.Mmio[0].Base;       // MMIO range
    Slave0MmioSizeReg0 &= 0xFFFF0000;
    Slave0MmioSizeReg0 |= LocalCfgPtr->Espi.Decode.Mmio[0].Size;      // MMIO range size
    Slave0DecodeEnBitMap |= BIT12;                                    // Enable MMIO range 0
  }else{
    Slave0DecodeEnBitMap &= (~BIT12);                                 // Disable MMIO range 0
  }

  if (LocalCfgPtr->Espi.Decode.Mmio[1].Enable){
    Slave0MmioBaseReg1 = LocalCfgPtr->Espi.Decode.Mmio[1].Base;                   // MMIO range
    Slave0MmioSizeReg0 &= 0x0000FFFF;
    Slave0MmioSizeReg0 |= ((UINT32)(LocalCfgPtr->Espi.Decode.Mmio[1].Size) << 16);// MMIO range size
    Slave0DecodeEnBitMap |= BIT13;                                               // Enable MMIO range 1
  }else{
    Slave0DecodeEnBitMap &= (~BIT13);                                            // Disable MMIO range 1
  }

  if (LocalCfgPtr->Espi.Decode.Mmio[2].Enable){
    Slave0MmioBaseReg2 = LocalCfgPtr->Espi.Decode.Mmio[2].Base;                  // MMIO range
    Slave0MmioSizeReg1 &= 0xFFFF0000;
    Slave0MmioSizeReg1 |= LocalCfgPtr->Espi.Decode.Mmio[2].Size;                 // MMIO range size
    Slave0DecodeEnBitMap |= BIT14;                                               // Enable MMIO range 2
  }else{
    Slave0DecodeEnBitMap &= (~BIT14);                                            // Disable MMIO range 2
  }

  if (LocalCfgPtr->Espi.Decode.Mmio[3].Enable){
    Slave0MmioBaseReg3 = LocalCfgPtr->Espi.Decode.Mmio[3].Base;                   // MMIO range
    Slave0MmioSizeReg1 &= 0x0000FFFF;
    Slave0MmioSizeReg1 |= ((UINT32)(LocalCfgPtr->Espi.Decode.Mmio[3].Size) << 16);// MMIO range size
    Slave0DecodeEnBitMap |= BIT15;                                               // Enable MMIO range 3
  }else{
    Slave0DecodeEnBitMap &= (~BIT15);                                            // Disable MMIO range 3
  }

  RwMem (EspiBase + 0x50, AccessWidth32, 0x00000000, Slave0MmioBaseReg0);                   // MMIO range
  RwMem (EspiBase + 0x54, AccessWidth32, 0x00000000, Slave0MmioBaseReg1);                   // MMIO range
  RwMem (EspiBase + 0x58, AccessWidth32, 0x00000000, Slave0MmioBaseReg2);                   // MMIO range
  RwMem (EspiBase + 0x5C, AccessWidth32, 0x00000000, Slave0MmioBaseReg3);                   // MMIO range
  RwMem (EspiBase + 0x60, AccessWidth32, 0x00000000, Slave0MmioSizeReg0);                   // MMIO range
  RwMem (EspiBase + 0x64, AccessWidth32, 0x00000000, Slave0MmioSizeReg1);                   // MMIO range size
  RwMem (EspiBase + 0x40, AccessWidth32, 0xFFFF0FFF, Slave0DecodeEnBitMap);                 // Enable MMIO range
}