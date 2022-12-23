/* $NoKeywords:$ */
/**
 * @file
 *
 * Fch SATA controller Library
 *
 * SATA Library
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
#define FILECODE PROC_FCH_SANDSTONE_SSSATA_SSSATALIB_FILECODE

#define MAX_RETRY_NUM   100
#define SATA_PORT_DETECTION_MAX_TRY 10

UINT32
SataGetBusCNumber (
  IN  UINT32              DieBusNum,
  IN  AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 SataBusNum;
  ReadPci ((((DieBusNum * 0x100 + SANDSTONE_BUSBPORT_BUS_DEV_FUN) << 16) + FCH_SATA_REG18), AccessWidth32, &SataBusNum, StdHeader);
  SataBusNum &= 0xFF00;
  return SataBusNum;
}

UINT32
SataSetBusCTempNumber (
  IN  AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 SataBusNum;
  SataBusNum = 0x00121200;
  WritePci (((SANDSTONE_BUSBPORT_BUS_DEV_FUN << 16) + FCH_SATA_REG18), AccessWidth32, &SataBusNum, StdHeader);
  SataBusNum &= 0xFF00;
  return SataBusNum;
}

UINT32
SataEnableBusCMmioDecode (
  IN  AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 OldBusCPortCmdReg;
  UINT32 NewBusCPortCmdReg;
  ReadPci (((SANDSTONE_BUSBPORT_BUS_DEV_FUN << 16) + FCH_SATA_REG04), AccessWidth32, &OldBusCPortCmdReg, StdHeader);
  NewBusCPortCmdReg = OldBusCPortCmdReg | 0x06;
  WritePci (((SANDSTONE_BUSBPORT_BUS_DEV_FUN << 16) + FCH_SATA_REG04), AccessWidth32, &NewBusCPortCmdReg, StdHeader);
  return OldBusCPortCmdReg;
}

VOID
SataRestoreBusCMmioDecode (
  IN  UINT32              SavedCmdReg,
  IN  AMD_CONFIG_PARAMS   *StdHeader
  )
{
  WritePci (((SANDSTONE_BUSBPORT_BUS_DEV_FUN << 16) + FCH_SATA_REG04), AccessWidth32, &SavedCmdReg, StdHeader);
}

VOID
SataBar5setting (
  IN  VOID       *FchDataPtr,
  IN  UINT32     SataBusNum,
  IN  UINT32     *Bar5Ptr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  //Get BAR5 value
  //
  ReadPci ((((SataBusNum + SANDSTONE_SATA_DEV_FUN) << 16) + FCH_SATA_REG24), AccessWidth32, Bar5Ptr, StdHeader);

  //
  //Assign temporary BAR if is not already assigned
  //
  if ( (*Bar5Ptr == 0) || (*Bar5Ptr == - 1) ) {
    //
    //assign temporary BAR5
    //
    if ( (LocalCfgPtr->Sata.TempMmio == 0) || (LocalCfgPtr->Sata.TempMmio == - 1) ) {
      *Bar5Ptr = 0xFEC01000;
    } else {
      *Bar5Ptr = LocalCfgPtr->Sata.TempMmio;
    }
    WritePci ((((SataBusNum + SANDSTONE_SATA_DEV_FUN) << 16) + FCH_SATA_REG24), AccessWidth32, Bar5Ptr, StdHeader);
  }

  //
  //Clear Bits 9:0
  //
  *Bar5Ptr = *Bar5Ptr & 0xFFFFFC00;
}

VOID
SataEnableWriteAccess (
  IN  UINT32              DieBusNum,
  IN  VOID                *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, 0xFFFFFFFE, BIT0, LocalCfgPtr->StdHeader);
}

VOID
SataDisableWriteAccess (
  IN  UINT32              DieBusNum,
  IN  VOID                *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, 0xFFFFFFFE, 0, LocalCfgPtr->StdHeader);
}

/**
 * FchSSSataInitPortOffline - Put Sata Port in Offline mode
 *
 *
 * @param[in] DieBusNum  IOCH bus number on current Die.
 * @param[in] PortNum   Sata Port to put in offline.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitPortOffline (
  IN  UINT32   DieBusNum,
  IN  UINT32   PortNum,
  IN  VOID     *FchDataPtr
  )
{
  UINT32                      Retry;
  UINT32                      PortStatus;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNum * 0x80, 0xFFFFFFF0, 0x4, LocalCfgPtr->StdHeader);

  for (Retry = 0; Retry < MAX_RETRY_NUM; Retry++) {
    FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG128 + PortNum * 0x80, &PortStatus, LocalCfgPtr->StdHeader);
    if ((PortStatus & 0x0F) == 0x4) {
      break;
    }
    FchStall (10, LocalCfgPtr->StdHeader);
  }
}

/**
 * FchSSSataInitPortActive - Put Sata Port back to active from
 * Offline mode
 *
 *
 * @param[in] DieBusNum  IOCH bus number on current Die.
 * @param[in] PortNum   Sata Port to put in offline.
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitPortActive (
  IN  UINT32   DieBusNum,
  IN  UINT32   PortNum,
  IN  VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32) (BIT16 << PortNum), 0, LocalCfgPtr->StdHeader);
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNum * 0x80, 0xFFFFFFF0, 0x1, LocalCfgPtr->StdHeader);
  FchStall (1000, LocalCfgPtr->StdHeader);
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNum * 0x80, 0xFFFFFFF0, 0x0, LocalCfgPtr->StdHeader);
}

/**
 * FchSSSataInitEnableErr - Enable Error reporting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitEnableErr (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  UINT32                 PortNum;
  BOOLEAN                FchD2HFifoParityErr;
  BOOLEAN                FchH2DFifoParityErr;
  BOOLEAN                FchContextMemoryParityErr;
  BOOLEAN                FchSataRasSupport;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  FchSataRasSupport = LocalCfgPtr->Sata.SataRasSupport;
  FchD2HFifoParityErr = TRUE;          //Optional
  FchH2DFifoParityErr = TRUE;          //Optional
  FchContextMemoryParityErr = TRUE;    //Optional

  if ( FchSataRasSupport ) {
    //
    // (Optional) Enable Report D2H FIFO Parity Error to System for each port.
    //
    if ( FchD2HFifoParityErr ) {
      for ( PortNum = 0; PortNum < SANDSTONE_SATA_PORT_NUM; PortNum++ ) {
        FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + PortNum * 0x20 + 0x88, ~(UINT32)BIT4, BIT4, StdHeader);
      }
    }

    //
    // (Optional) Enable Report H2D FIFO Parity Error to System for each port
    //
    if ( FchH2DFifoParityErr ) {
      for ( PortNum = 0; PortNum < SANDSTONE_SATA_PORT_NUM; PortNum++ ) {
        FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + PortNum * 0x20 + 0x88, ~(UINT32)BIT5, BIT5, StdHeader);
      }
    }

    //
    // (Optional) Enable Report Context Memory Parity Error to System for each port
    //
    if ( FchContextMemoryParityErr ) {
      for ( PortNum = 0; PortNum < SANDSTONE_SATA_PORT_NUM; PortNum++ ) {
        FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + PortNum * 0x20 + 0x88, ~(UINT32)BIT6, BIT6, StdHeader);
      }
    }
  }
  //
  //Clear error status
  //
  for ( PortNum = 0; PortNum < SANDSTONE_SATA_PORT_NUM; PortNum++ ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG130 + PortNum * 0x80, 0xFFFFFFFF, 0xFFFFFFFF, StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG110 + PortNum * 0x80, 0xFFFFFFFF, 0x00, StdHeader);
  }
}

/**
 * FchSSSataInitEsata - Enable eSATA port
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitEsata (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // SATA ESP port setting
  // These config bits are set for SATA driver to identify which ports are external SATA ports and need to
  // support hotplug. If a port is set as an external SATA port and need to support hotplug, then driver will
  // not enable power management (HIPM & DIPM) for these ports.
  //
  if ( LocalCfgPtr->Sata.SataEspPort.SataPortReg != 0 ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF8, ~(LocalCfgPtr->Sata.SataEspPort.SataPortReg), 0, StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF8, 0xFF00FFFF, (LocalCfgPtr->Sata.SataEspPort.SataPortReg << 16), StdHeader);
    //
    // External SATA Port Indication Registers
    // If any of the ports was programmed as an external port, HCAP.SXS should also be set
    //
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGFC, ~(UINT32) (BIT20), BIT20, StdHeader);
    //
    // Enable  eSATA PHY power-saving when no device presented.
    //
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x10, ~(UINT32) (BIT29), BIT29, StdHeader);
  } else {
    //
    // External SATA Port Indication Registers
    // If any of the ports was programmed as an external port, HCAP.SXS should also be set (Clear for no ESP port)
    //
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF8, 0xFF00FF00, 0x00, StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGFC, ~(UINT32) (BIT20), 0x00, StdHeader);
  }
}

/**
 * FchSSSataInitDevSlp - init DevSlp configuration
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitDevSlp (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  UINT8                  PortNumByte;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // 1, Enable the DEVLSP related GPIO pad and put the it into open-drain mode
  // 2, Enable the capability bit for DevSlp support
  // 3, Program CFG_PxCMD2.DSP bit for the port which will support DEVSLP.
  // 4, Program PortX_DEVSLP_MAP to route any two ports to external PAD.
  //
  PortNumByte = LocalCfgPtr->Sata.SataDevSlpPort0Num;
  if ( LocalCfgPtr->Sata.SataDevSlpPort0 ) {
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG05, AccessWidth8, 0, 0x01);
    RwMem (ACPI_MMIO_BASE + GPIO_BANK0_BASE + FCH_GPIO_014_BP_AGPIO5, AccessWidth32, ~(UINT32) (BIT20 + BIT21 + BIT22 + BIT23), BIT23);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, 0xFFFFFFEF, BIT4 + (BIT8 << PortNumByte), StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x8C, 0xFFFF8FFF, (UINT32) (PortNumByte << 12), StdHeader);
  } else {
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG05, AccessWidth8, 0, 0x00);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, ~(UINT32) (BIT8 << PortNumByte), 0x00, StdHeader);
    if ( !LocalCfgPtr->Sata.SataDevSlpPort1 ) {
      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, 0xFFFFFFEF, 0x00, StdHeader);
    }
  }

  PortNumByte = LocalCfgPtr->Sata.SataDevSlpPort1Num;
  if ( LocalCfgPtr->Sata.SataDevSlpPort1 ) {
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG06, AccessWidth8, 0, 0x01);
    RwMem (ACPI_MMIO_BASE + GPIO_BANK0_BASE + FCH_GPIO_018_BP_AGPIO6, AccessWidth32, ~(UINT32) (BIT20 + BIT21 + BIT22 + BIT23), BIT23);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, 0xFFFFFFEF, BIT4 + (BIT8 << PortNumByte), StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0xAC, 0xFFFF8FFF, (UINT32) (PortNumByte << 12), StdHeader);
  } else {
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG06, AccessWidth8, 0, 0x00);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, ~(UINT32) (BIT8 << PortNumByte), 0x00, StdHeader);
    if ( !LocalCfgPtr->Sata.SataDevSlpPort0 ) {
      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF4, 0xFFFFFFEF, 0x00, StdHeader);
    }
  }
}

/**
 * FchSSSataInitMpssMap - Program Mechanical Presence Switch
 * State Mapping.
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitMpssMap (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  UINT32                 PortNum;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  for (PortNum = 0; PortNum < SANDSTONE_SATA_PORT_NUM; PortNum++) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + PortNum * 0x20 + 0x8C, 0xFFFFF8FF, (UINT32) (PortNum << 8), StdHeader);
  }
}

/**
 * FchSSSataInitRsmuCtrl - Sata Rsmu Control register setting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitRsmuCtrl (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // SATA controller operates in maximum Gen2
  //
  if ( LocalCfgPtr->Sata.SataMode.SataSetMaxGen2 ) {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT2, BIT2, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT2, 0x00, StdHeader);
  }

  //
  // Sata Target Support 8 devices function
  //
  if ( LocalCfgPtr->Sata.SataTargetSupport8Device ) {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT3, BIT3, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT3, 0x00, StdHeader);
  }

  //
  // Sata Generic Mode setting
  //
  if ( LocalCfgPtr->Sata.SataDisableGenericMode ) {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT1, BIT1, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT1, 0x00, StdHeader);
  }

  //
  // OOB Detection Enhancement
  //
  if ( LocalCfgPtr->Sata.SataOobDetectionEnh ) {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT24, BIT24, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT24, 0x00, StdHeader);
  }
  // PLAT-23811 
  FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL4, ~(UINT32) (BIT8 | BIT9), 0x00, StdHeader);
}

/**
 * FchSSSataInitCtrlReg - Sata Rsmu Control register setting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitCtrlReg (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  UINT32       AndMaskDword;
  UINT32       OrMaskDword;
  UINT8        FchSataAggrLinkPmCap;
  UINT8        FchSataPortMultCap;
  UINT8        FchSataPscCap;
  UINT8        FchSataSscCap;
  UINT8        FchSataFisBasedSwitching;
  UINT8        FchSataCccSupport;
  UINT8        FchSataAhciEnclosureManagement;
  BOOLEAN      FchSataMsiEnable;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  RAVEN2_TYPE            Raven2Type;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  FchSataAggrLinkPmCap = (UINT8) LocalCfgPtr->Sata.SataAggrLinkPmCap;
  FchSataPortMultCap = (UINT8) LocalCfgPtr->Sata.SataPortMultCap;
  FchSataPscCap = (UINT8) LocalCfgPtr->Sata.SataPscCap;
  FchSataSscCap = (UINT8) LocalCfgPtr->Sata.SataSscCap;
  FchSataFisBasedSwitching = (UINT8) LocalCfgPtr->Sata.SataFisBasedSwitching;
  FchSataCccSupport = (UINT8) LocalCfgPtr->Sata.SataCccSupport;
  FchSataAhciEnclosureManagement = (UINT8) LocalCfgPtr->Sata.SataAhciEnclosureManagement;
  FchSataMsiEnable = LocalCfgPtr->Sata.SataMsiEnable;

  AndMaskDword = 0;
  OrMaskDword = 0;

  if ( !FchSataPortMultCap ) {
    AndMaskDword |= BIT12;
  }

  if ( FchSataFisBasedSwitching ) {
    OrMaskDword |= BIT10;
  } else {
    AndMaskDword |= BIT10;
  }

  if ( FchSataAggrLinkPmCap ) {
    OrMaskDword |= BIT11;
  } else {
    AndMaskDword |= BIT11;
  }

  if ( FchSataPscCap ) {
    OrMaskDword |= BIT1;
  } else {
    AndMaskDword |= BIT1;
  }

  if ( FchSataSscCap ) {
    OrMaskDword |= BIT26;
  } else {
    AndMaskDword |= BIT26;
  }

  //
  // Disabling CCC (Command Completion Coalescing) support.
  //
  if ( FchSataCccSupport ) {
    OrMaskDword |= BIT19;
  } else {
    AndMaskDword |= BIT19;
  }

  if ( FchSataAhciEnclosureManagement ) {
    OrMaskDword |= BIT27;
  } else {
    AndMaskDword |= BIT27;
  }

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGFC, ~AndMaskDword, OrMaskDword, StdHeader);

  if ( FchSataFisBasedSwitching ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF8, 0x00FFFFFF, 0xFF000000, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGF8, 0x00FFFFFF, 0x00, StdHeader);
  }

  if ( LocalCfgPtr->Sata.BiosOsHandOff == 1 ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG24, ~(UINT32) BIT0, BIT0, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG24, ~(UINT32) BIT0, 0x00, StdHeader);
  }

  // UBSS460961
  // Program sata_slor :: 0x0C[31:28] = 0xF>
  // Program sata_slor :: 0x0C[6:5] = 0x3>
  // Program sata_slor :: 0x0C[3] = 0x1>
  // Program sata_slor :: 0x0C[1] = 0x1>
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x0C, ~(UINT32)BIT23, 0xF000006A, StdHeader);
  //
  // BIT2 : Enable dynamic blink clock gating
  // BIT14: Enable BlcClkGated gating
  // BIT15: Enable PciClkGated gating
  // BIT25
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x10, ~(UINT32) (BIT2 + BIT14 + BIT15 + BIT25), BIT2 + BIT14 + BIT15 + BIT25, StdHeader);

  // Program sata_slor :: 0x14[8:5] = 0xF
  // Program sata_slor :: 0x14[30] = 1
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x14, ~(UINT32) (BIT5 + BIT6 + BIT7 + BIT8 + BIT30), BIT5 + BIT6 + BIT7 + BIT8 + BIT30, StdHeader);
  //
  // Disable Prefetch In Ahci Mode
  //
  if ( LocalCfgPtr->Sata.SataAhciDisPrefetchFunction ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32)BIT13, BIT13, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32)BIT13, 0x00, StdHeader);
  }

  //
  // MSI Capability could be disabled by setting register nBIF1:RCC_DEV0_EPF2_STRAP3.STRAP_MSI_EN_DEV0_F2 to 0.
  //
  if ( FchSataMsiEnable ) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_NBIF_STRAP3, ~(UINT32)BIT18, BIT18, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_NBIF_STRAP3, ~(UINT32)BIT18, 0x00, StdHeader);
  }

  //
  // Clear No Soft Reset bit in PMCR
  //
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_NBIF_STRAP2, ~(UINT32)BIT7, 0, StdHeader);

  //
  // Shutdown ports
  //
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, 0xFF00FFFF, (LocalCfgPtr->Sata.SataPortPower.SataPortReg << 16), StdHeader);

  //
  // Mark PHY_Ownedby_Sata
  //
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x200, ~(UINT32)BIT0, BIT0, StdHeader);

  //
  // Set Revision ID to 0x61
  //
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_NBIF_STRAP0, 0xFF00FFFF, 0x00160000, StdHeader);

  //
  // RV2 to reset PHY
  //
  Raven2Type = FchCheckRaven2Type();
  if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32)BIT3, BIT3, StdHeader);
    FchStall (100, StdHeader);
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32)BIT3, 0, StdHeader);
    FchStall (5000, StdHeader);
  }

  //UBTS610116
  // Program sata_slor :: 0x04[22] = 0x1>
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x04, ~(UINT32) (BIT22), BIT22, StdHeader);
}

/**
 * FchSSSataInitMMC - Sata MSI MMC setting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataInitMMC (
  IN  UINT32   DieBusNum,
  IN VOID      *FchDataPtr
  )
{
  UINT32                 SataPciMmc;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  if ( LocalCfgPtr->Sata.SataMsiEnable ) {
    //
    // Get Sata PCI MSI.MMC setting
    //
    FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_PCICFG + 0xA0, &SataPciMmc, StdHeader);

    //
    // Sata MMC programming
    //
    // nBif MMC at bit[19:17], SATA_Rsmux0A MMC bits at [26:24]
    SataPciMmc = (SataPciMmc & 0x000E0000) << 7;
    FchSmnRW (DieBusNum, FCH_SS_SATA_EVENT_SELECT, 0xF8FFFFFF, SataPciMmc, StdHeader);
  }
}

/**
 * FchSSSataSetPortGenMode - Set Sata port mode (each) for
 * Gen1/Gen2/Gen3
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataSetPortGenMode (
  IN  UINT32   DieBusNum,
  IN  VOID     *FchDataPtr
  )
{
  UINT8        PortNumByte;
  UINT8        PortModeByte;
  UINT16       SataPortMode;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  SataPortMode = (UINT16)LocalCfgPtr->Sata.SataPortMd.SataPortMode;
  PortNumByte = 0;

  while ( PortNumByte < SANDSTONE_SATA_PORT_NUM ) {
    PortModeByte = (UINT8) (SataPortMode & 3);
    if ( (PortModeByte == BIT0) || (PortModeByte == BIT1) ) {
      if ( PortModeByte == BIT0 ) {
        //
        // set GEN 1
        //
        FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNumByte * 0x80, 0xFFFFFF0F, 0x10, StdHeader);
      }

      if ( PortModeByte == BIT1 ) {
        //
        // set GEN2 (default is GEN3)
        //
        FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNumByte * 0x80, 0xFFFFFF0F, 0x20, StdHeader);
      }

      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNumByte * 0x80, 0xFFFFFFFF, 0x01, StdHeader);
    }

    SataPortMode >>= 2;
    PortNumByte ++;
  }

  FchStall (1000, StdHeader);
  SataPortMode = (UINT16)LocalCfgPtr->Sata.SataPortMd.SataPortMode;
  PortNumByte = 0;

  while ( PortNumByte < SANDSTONE_SATA_PORT_NUM ) {
    PortModeByte = (UINT8) (SataPortMode & 3);

    if ( (PortModeByte == BIT0) || (PortModeByte == BIT1) ) {
      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG12C + PortNumByte * 0x80, 0xFFFFFFFE, 0x00, StdHeader);
    }

    PortNumByte ++;
    SataPortMode >>= 2;
  }
}

/**
 * FchSSSataShutdownUnconnectedSataPortClock - Shutdown
 * unconnected Sata port clock
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataShutdownUnconnectedSataPortClock (
  IN  UINT32     DieBusNum,
  IN  VOID       *FchDataPtr
  )
{
  UINT8                  PortNumByte;
  UINT8                  PortSataStatusByte;
  UINT8                  NumOfPorts;
  UINT8                  FchSataClkAutoOff;
  UINT32                 PortStatusDword;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT8                  SaveLocation;
  RAVEN2_TYPE            Raven2Type;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  FchSataClkAutoOff = (UINT8) LocalCfgPtr->Sata.SataClkAutoOff;
  Raven2Type = FchCheckRaven2Type();

  NumOfPorts = 0;
  //
  // Enable SATA auto clock control by default
  //
  if ( FchSataClkAutoOff ) {
    if ((ReadFchSleepType (StdHeader) != ACPI_SLPTYP_S3)) {
      for ( PortNumByte = 0; PortNumByte < SANDSTONE_SATA_PORT_NUM; PortNumByte++ ) {
        FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG128 + PortNumByte * 0x80, &PortStatusDword, StdHeader);
        PortSataStatusByte = (UINT8)(PortStatusDword & 0xFF);
        //
        // Shutdown the clock for the port and do the necessary port reporting changes.
        // Error port status should be 1 not 3
        //
        if ( ((PortSataStatusByte & 0x0F) != 0x03) && (! ((LocalCfgPtr->Sata.SataEspPort.SataPortReg) & (1 << PortNumByte))) ) {
          if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO) || (FchCheckPicasso())) {
            FchSSSataInitPortOffline (DieBusNum, PortNumByte, FchDataPtr);
          }
          FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, ~(UINT32)(BIT16 << PortNumByte), (BIT16 << PortNumByte), StdHeader);
          FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, ~(UINT32)(1 << PortNumByte), 00, StdHeader);
        }
      }                                            ///end of for (PortNumByte=0;PortNumByte<6;PortNumByte++)
      SaveLocation = 0;
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG72, &SaveLocation, StdHeader);

      FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, &PortStatusDword, StdHeader);
      PortSataStatusByte = (UINT8)((PortStatusDword >> 0x10) & 0xFF);
      SaveLocation = 1;
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG73, &PortSataStatusByte, StdHeader);
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG72, &SaveLocation, StdHeader);

      FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, &PortStatusDword, StdHeader);
      PortSataStatusByte = (UINT8)(PortStatusDword & 0xFF);
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG73, &PortSataStatusByte, StdHeader);
    } else {
      SaveLocation = 0;
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG72, &SaveLocation, StdHeader);
      LibAmdIoRead (AccessWidth8, FCH_IOMAP_REG73, &PortSataStatusByte, StdHeader);
      if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO) || (FchCheckPicasso())) {
        for ( PortNumByte = 0; PortNumByte < SANDSTONE_SATA_PORT_NUM; PortNumByte++ ) {
          if (PortSataStatusByte & (1 << PortNumByte)) {
            FchSSSataInitPortOffline (DieBusNum, PortNumByte, FchDataPtr);
          }
        }
      }
      PortStatusDword = (UINT32)PortSataStatusByte << 0x10;
      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_SLOR + 0x00, 0xFF00FFFF, PortStatusDword, StdHeader);

      SaveLocation = 1;
      LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REG72, &SaveLocation, StdHeader);
      LibAmdIoRead (AccessWidth8, FCH_IOMAP_REG73, &PortSataStatusByte, StdHeader);

      FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, 0xFFFFFF00, (UINT32)PortSataStatusByte, StdHeader);
    }
  }

  FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, &PortStatusDword, StdHeader);
  PortSataStatusByte = (UINT8)(PortStatusDword & 0xFF);

  //
  //if all ports are in disabled state, report at least one port
  //
  if ( (PortSataStatusByte & 0xFF) == 0) {
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, 0xFFFFFF00, 0x01, StdHeader);
  }

  FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG0C, &PortStatusDword, StdHeader);
  PortSataStatusByte = (UINT8)(PortStatusDword & 0xFF);

  for (PortNumByte = 0; PortNumByte < SANDSTONE_SATA_PORT_NUM; PortNumByte ++) {
    if (PortSataStatusByte & (1 << PortNumByte)) {
      NumOfPorts++;
    }
  }

  if ( NumOfPorts == 0) {
    NumOfPorts = 0x01;
  }

  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG00, 0xFFFFFFE0, (UINT32)(NumOfPorts - 1), StdHeader);
}

VOID
FchSSSataAutoShutdownController (
  IN  UINT32     DieBusNum,
  IN  VOID       *FchDataPtr
  )
{
  UINT8                  PortNumByte;
  UINT8                  PortSataStatusByte;
  UINT8                  PortDetectionRetry;
  UINT32                 PortStatusDword;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  if (ReadFchSleepType (StdHeader) != ACPI_SLPTYP_S3) {
    if ((LocalCfgPtr->Sata.SataControllerAutoShutdown) && (LocalCfgPtr->Sata.SataEspPort.SataPortReg == 0)) {
      if (LocalCfgPtr->Sata.SataDevSlpPort0 || LocalCfgPtr->Sata.SataDevSlpPort1) {
        // DevSlp device need more time to exit DevSlp mode
        FchStall (150000, StdHeader);
      }

      PortDetectionRetry = 0;
      do {
        for ( PortNumByte = 0; PortNumByte < SANDSTONE_SATA_PORT_NUM; PortNumByte++ ) {
          FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG128 + PortNumByte * 0x80, &PortStatusDword, StdHeader);
          PortSataStatusByte = (UINT8)(PortStatusDword & 0xFF);
          if ((PortSataStatusByte & 0x0F) == 0x03) {
            return;                         // do not hide/shut Sata if detect device
          }
        }
        FchStall (10000, StdHeader);        //delay 10ms for each detection attempt
        PortDetectionRetry++;
      } while (PortDetectionRetry < SATA_PORT_DETECTION_MAX_TRY);
      FchSSSataDisableSata (0, FchDataPtr);
      LocalCfgPtr->Sata.SataMode.SataEnable = 0;
    }
  }
}

VOID
FchSSSataDisableSata (
  IN  UINT32     DieBusNum,
  IN  VOID       *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  RAVEN2_TYPE            Raven2Type;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  if (LocalCfgPtr->Xgbe.Port[0].XgbePortConfig || LocalCfgPtr->Xgbe.Port[1].XgbePortConfig) {
    FchSmnRW (DieBusNum, FCH_RCC_DEV1_PORT_STRAP0, ~(UINT32) BIT31, BIT31, StdHeader); //PLAT-15054, dummy Function 0
    FchSmnRW (DieBusNum, 0x10135000ul, ~(UINT32) BIT28, 0, StdHeader); //RCC_STRAP:RCC_DEV1_EPF0_STRAP0
    FchSmnRW (DieBusNum, 0x10135034ul, 0xFF000000, 0x00130000, StdHeader); //RCC_STRAP:RCC_DEV1_EPF0_STRAP13
    FchSmnRW (DieBusNum, 0x10135010ul, 0x807FFFFF, 0, StdHeader); //RCC_STRAP:RCC_DEV1_EPF0_STRAP4
    FchSmnRW (DieBusNum, 0x1013500Cul, ~(UINT32) (BIT18 + BIT20 + BIT25), BIT25, StdHeader); //RCC_STRAP:RCC_DEV1_EPF0_STRAP3
    FchSmnRW (DieBusNum, 0x1013A044ul, ~(UINT32) (BIT0 + BIT1), (BIT0 + BIT1), StdHeader); //RCC_STRAP:
    FchSmnRW (DieBusNum, 0x10135000ul, 0xFFFF0000, 0x145A, StdHeader);
  } else {
    FchSmnRW (DieBusNum, FCH_IOHC_Bridge_CNTL_INST8, 0xFFFFFFFF, 5, StdHeader); //PLAT-15054, disable parent bridge to avoid PCI SCAN hang
    FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_NBIF_STRAP0, ~(UINT32)BIT28, 0, StdHeader);
  }


  Raven2Type = FchCheckRaven2Type();
  if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO) || (FchCheckPicasso())) {
    FchRVXhciSmuService (SMC_MSG_DisableSataController);
  } else {
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, 0xfffffffe, BIT0, NULL);
    FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32)BIT11, BIT11, NULL);
  }
}
/**
 * sataSetIrqIntResource - Config SATA IRQ/INT# resource
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 * @param[in] StdHeader
 *
 */
VOID
SataSetIrqIntResource (
  IN  VOID                 *FchDataPtr,
  IN  AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8                  ValueByte;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  //
  // IRQ14/IRQ15 come from IDE or SATA
  //
  ValueByte = 0x08;
  LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC00, &ValueByte, StdHeader);
  LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGC01, &ValueByte, StdHeader);
  ValueByte = ValueByte & 0x0F;
  ValueByte = ValueByte | 0xF0;
  LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC01, &ValueByte, StdHeader);
}

/**
 * FchSSSataGpioInitial - Sata GPIO function Procedure
 *
 *   - Private function
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSSSataGpioInitial (
  IN  UINT32     DieBusNum,
  IN  VOID       *FchDataPtr
  )
{
  UINT32       FchSataBarRegDword;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  //1.Set SGPIO PAD
  //GPIOx00024 0000_0000h 9 AGPIO9_SGPIO_DATAOUT_MDIO1_SCL
  //GPIOx00028 0000_0000h 10 S0A3_GPIO_AGPIO10_SGPIO_CLK_MDIO0_SCL
  //GPIOx0005C 0000_0000h 23 AGPIO23_SGPIO_LOAD_MDIO1_SDA
  //GPIOx000A0 0000_0000h 40 AGPIO40_SGPIO_DATAIN_MDIO0_SDA
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + FCH_GPIO_REG09, 0x00, 0x01, NULL);
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + FCH_GPIO_REG10, 0x00, 0x02, NULL);
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + FCH_GPIO_REG23, 0x00, 0x01, NULL);
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + FCH_GPIO_REG40, 0x00, 0x01, NULL);
  //Set GPIOx024[20] = 1, make SPIO_DATA_OUT pull up enable
  //Set GPIOx028[20] = 1, make SGPIO_CLK pull up enable
  //Set GPIOx05C[20] = 1, make SGPIO_LOAD pull up enable
  //Set GPIOx0A0[20] = 1, make SGPIO_DATAIN pull up enable
  FchSmnRW (DieBusNum, FCH_SS_SMN_GPIO_BASE + 0x24, ~(UINT32) BIT20, BIT20, NULL);
  FchSmnRW (DieBusNum, FCH_SS_SMN_GPIO_BASE + 0x28, ~(UINT32) BIT20, BIT20, NULL);
  FchSmnRW (DieBusNum, FCH_SS_SMN_GPIO_BASE + 0x5C, ~(UINT32) BIT20, BIT20, NULL);
  FchSmnRW (DieBusNum, FCH_SS_SMN_GPIO_BASE + 0xA0, ~(UINT32) BIT20, BIT20, NULL);

  //2.Support 8 device on 1 SGPIO stream
  //set SPIO_TgtSpt8dev = 0x1, support 8 device on 1 SGPIO stream
  FchSmnRW (DieBusNum, FCH_SS_SATA_MISC_CONTROL, ~(UINT32) BIT3, BIT3, NULL);

  //3.Enable SGPIO in Enclosure Management set
  //Program sata_ahci :: FCh[27] =1
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REGFC, ~(UINT32) BIT27, BIT27, NULL);

  //4.Set SGPIO enable
  // Programe  sata_ahci::506h = 0
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + 0x506, 0x00, 0x00, NULL);
  // Programe sata_ahci::507h=0
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + 0x507, 0x00, 0x00, NULL);
  // Programe sata_ahci::508h=1
  FchSmnRW8 (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + 0x508, 0x00, 0x01, NULL);
  // Programe sata_ahci::50Ch[23] = 1
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + 0x50C, ~(UINT32) BIT23, BIT23, NULL);
  // Programe Sata_ahci::20h[8] = 1
  FchSmnRW (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG20, ~(UINT32) (BIT8), BIT8, NULL);
  do {
    FchSmnRead (DieBusNum, FCH_SS_SMN_SATA_CONTROL_BAR5 + FCH_SATA_BAR5_REG20, &FchSataBarRegDword, NULL);
  } while ( FchSataBarRegDword & BIT8);
}


