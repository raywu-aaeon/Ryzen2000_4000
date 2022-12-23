/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch LPC controller
 *
 * Init LPC Controller features.
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

#define FILECODE PROC_FCH_SANDSTONE_SSSPI_SSLPCRESETSERVICE_FILECODE
#define SPI_BASE 0xFEC10000ul

VOID
FchSetQualModePei (
  IN       UINT32      SpiQualMode,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  );

/**
 * FchInitSandstoneResetLpcPciTable - Lpc (Spi) device registers
 * initial during the power on stage.
 *
 *
 *
 *
 */
REG8_MASK FchInitSandstoneResetLpcPciTable[] =
{
  //
  // LPC Device (Bus 0, Dev 20, Func 3)
  //
  {0x00, LPC_BUS_DEV_FUN, 0},

  {FCH_LPC_REG48, 0x00, BIT0 + BIT1 + BIT2},
  //
  // Set 0xBA [6:5] = 11 improve SPI timing margin. (SPI Prefetch enhancement)
  //
  {FCH_LPC_REGBA, 0x9F, BIT5 + BIT6},
  // Force EC_PortActive to 1 to fix possible IR non function issue when NO_EC_SUPPORT is defined
  {FCH_LPC_REGA4, 0xFE, BIT0},
  //PLAT-21251 {FCH_LPC_REGD3, 0xFF, BIT7},
  {0xFF, 0xFF, 0xFF},
};

/**
 * FchInitResetLpcProgram - Config Lpc controller during Power-On
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitResetLpcProgram (
  IN       VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK      *LocalCfgPtr;
  AMD_CONFIG_PARAMS         *StdHeader;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG6C, AccessWidth32, 0xFFFFFF00, 0, StdHeader);

  ProgramPciByteTable ( (REG8_MASK*) (&FchInitSandstoneResetLpcPciTable[0]), sizeof (FchInitSandstoneResetLpcPciTable) / sizeof (REG8_MASK), StdHeader);

  if ( LocalCfgPtr->Spi.LpcClk1 ) {
    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 1, AccessWidth8, 0xBF, 0x40, StdHeader);
  } else {
    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 1, AccessWidth8, 0xBF, 0, StdHeader);
  }
  if ( LocalCfgPtr->LegacyFree ) {
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, 00, 0x0003C000, StdHeader);
  } else {
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, 00, 0xFF03FFD5, StdHeader);
  }
//  if ( LocalCfgPtr->Spi.LpcClk0 ) {
//    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 1, AccessWidth8, 0xDF, 0x20, StdHeader);
//  } else {
//    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, 00, 0, StdHeader);
//    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG48), AccessWidth32, 0xFF00, 0, StdHeader);
//    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 1, AccessWidth8, 0xDF, 0, StdHeader);
//  }
  if ( LocalCfgPtr->Spi.LpcClkRunEn ) {  //PLAT-21251 
    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 3, AccessWidth8, 0x7F, 0x80, StdHeader);
  } else {
    RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGD0 + 3, AccessWidth8, 0x7F, 0, StdHeader);
  }
}

/**
 * FchPlatformSpiQeCheck - Platform SPI Qual Enable
 *
 *
 *
 * @param[in] FchDataPtr  - FchData Pointer.
 *
 */
BOOLEAN
FchPlatformSpiQeCheck (
  IN       VOID     *FchDataPtr
  )
{
  UINTN RomSigStartingAddr;
  UINT8 Value8;
  FCH_RESET_DATA_BLOCK      *LocalCfgPtr;
  AMD_CONFIG_PARAMS         *StdHeader;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  if ((LocalCfgPtr->Mode == FCH_SPI_MODE_QUAL_122) || (LocalCfgPtr->Mode == FCH_SPI_MODE_QUAL_144)) {
    FchConfigureSpiControllerDummyCycle ();
  }

  if (LocalCfgPtr->QeEnabled) {
    return TRUE;
  }
  if ((LocalCfgPtr->Mode == FCH_SPI_MODE_QUAL_114) || (LocalCfgPtr->Mode == FCH_SPI_MODE_QUAL_144)) {
    if (FchPlatformSpiQe (FchDataPtr)) {
      return TRUE;
    }
  }

  GetRomSigPtr (&RomSigStartingAddr, StdHeader);
  Value8 = *(UINT8*) (UINTN) (RomSigStartingAddr + 0x43);
  if ((Value8 > 1) && (Value8 < 8) && (LocalCfgPtr->Mode == 0)) {
    LocalCfgPtr->Mode = Value8;
    Value8 = *(UINT8*) (UINTN) (RomSigStartingAddr + 0x44);
    LocalCfgPtr->FastSpeed = Value8 + 1;
    FchConfigureSpiControllerDummyCycle ();
    return TRUE;
  }
  return FALSE;
}
/**
 * FchSetQualModePei - Set SPI Qual Mode
 *
 *
 *
 * @param[in] SpiQualMode- Spi Qual Mode.
 * @param[in] StdHeader  - Standard Header.
 *
 */
VOID
FchSetQualModePei (
  IN       UINT32      SpiQualMode,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  UINT32 SpiMode;

  SpiMode = ACPIMMIO32 (SPI_BASE + FCH_SPI_MMIO_REG00);
  if ((SpiMode & (BIT18 + BIT29 + BIT30)) != ((SpiQualMode & 1) << 18) + ((SpiQualMode & 6) << 28)) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG00, AccessWidth32, ~(UINT32) ( BIT18 + BIT29 + BIT30), ((SpiQualMode & 1) << 18) + ((SpiQualMode & 6) << 28));
  }
}

/**
 * FchInitResetSpi - Config Spi controller during Power-On
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitResetSpi (
  IN       VOID     *FchDataPtr
  )
{
  BOOLEAN                   SpiQeCheck;
  UINT32                    SpiModeByte;
  FCH_RESET_DATA_BLOCK      *LocalCfgPtr;
  AMD_CONFIG_PARAMS         *StdHeader;

  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  AGESA_TESTPOINT (TpFchInitResetSpi, NULL);
  //
  // Set Spi ROM Base Address
  //
  RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGA0, AccessWidth32, 0x001F, SPI_BASE, StdHeader);

  RwMem (SPI_BASE + FCH_SPI_MMIO_REG00, AccessWidth32, 0xFFFFFFFF, (BIT19 + BIT24 + BIT25 + BIT26));
  RwMem (SPI_BASE + FCH_SPI_MMIO_REG0C, AccessWidth32, 0xFFC0FFFF, 0 );

  //Set SPI100 Enable
  RwMem (SPI_BASE + FCH_SPI_MMIO_REG20, AccessWidth8, 0xFE, (UINT8) ((LocalCfgPtr->SPI100_Enable) << 0));

  //
  //  Spi Pad Initial
  //  UINT32                SPI100_RX_Timing_Config_Register_38;                 ///< SPI100_RX_Timing_Config_Register_38
  //UINT16                SPI100_RX_Timing_Config_Register_3C;                 ///< SPI100_RX_Timing_Config_Register_3C
  //UINT8                 SpiProtectEn0_1d_34;                  ///

  //RwMem (SPI_BASE + FCH_SPI_MMIO_REG38, AccessWidth32, 0, LocalCfgPtr->SPI100_RX_Timing_Config_Register_38);
  //RwMem (SPI_BASE + FCH_SPI_MMIO_REG3C, AccessWidth16, 0, LocalCfgPtr->SPI100_RX_Timing_Config_Register_3C);
  // RwMem (SPI_BASE + FCH_SPI_MMIO_REG1D, AccessWidth8, 0xE7, (UINT8) ((LocalCfgPtr->SpiProtectEn0_1d_34) << 3));

  //
  //  Spi Mode Initial
  //
  SpiQeCheck = FchPlatformSpiQeCheck (FchDataPtr);
  if (LocalCfgPtr->SpiSpeed) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG22, AccessWidth32, ~((UINT32) (0xF << 12)), ((LocalCfgPtr->SpiSpeed - 1 ) << 12));
  }

  if (LocalCfgPtr->FastSpeed) {
    RwMem (SPI_BASE + FCH_SPI_MMIO_REG22, AccessWidth32, ~((UINT32) (0xF << 8)), ((LocalCfgPtr->FastSpeed - 1 ) << 8));
  }

  RwMem (SPI_BASE + FCH_SPI_MMIO_REG1C, AccessWidth32, ~(UINT32) (BIT10), ((LocalCfgPtr->BurstWrite) << 10));

  RwMem (SPI_BASE + FCH_SPI_MMIO_REG2C, AccessWidth32, ~(UINT32) (BIT14), (1 << 14)); //ENH433556:Enabling SPI Performance enhancement

  RwMem (SPI_BASE + FCH_SPI_MMIO_REG2C, AccessWidth32, ~(UINT32) (BIT15), 0); //ENH457313:  SPI Mem 0x2C[15] needs to be cleared in Carrizo

  SpiModeByte = LocalCfgPtr->Mode;
  if (LocalCfgPtr->Mode) {
    if ((SpiModeByte == FCH_SPI_MODE_QUAL_114) || (SpiModeByte == FCH_SPI_MODE_QUAL_144)) {
      if (SpiQeCheck) {
        FchSetQualModePei (SpiModeByte, StdHeader);
      }
    } else {
      //if (SpiQeCheck) {
        RwMem (SPI_BASE + FCH_SPI_MMIO_REG00, AccessWidth32, ~(UINT32) ( BIT18 + BIT29 + BIT30), ((LocalCfgPtr->Mode & 1) << 18) + ((LocalCfgPtr->Mode & 6) << 28));
      //}
    }
  } else {
    if (SpiQeCheck) {
      //RwMem (SPI_BASE + FCH_SPI_MMIO_REG0C, AccessWidth32, ~(UINT32) (BIT13 + BIT12), ((FCH_SPI_SPEED_33M - 1 ) << 12));
      //RwMem (SPI_BASE + FCH_SPI_MMIO_REG0C, AccessWidth32, ~(UINT32) (BIT15 + BIT14), ((FCH_SPI_SPEED_66M - 1 ) << 14));
      SpiModeByte = FCH_SPI_MODE_QUAL_144;
      //FchSetQualModePei (SpiModeByte, StdHeader);
    }
  }
  // PLAT-20087 
  // PrefetchEnSPIFromHost (LPC PCI Cfg 0xB8[24]=1) --> leave it as H/W default, no need to touch
  // HostHitSoonEn (SPI Mem 0x2C[13]=0) --> leave it as H/W default, no need to touch
  // HostWillHitEn (SPI Mem 0x2C[12]=1) --> leave it as H/W default, no need to touch
  // LPC PCI Configuration Register 0xDC[0]  (default=0) is used as chicken bit.
  // Software need to set this bit to 1 before remove the software patch to verify the ECO.
  RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGDC, AccessWidth16, 0xFFFF, BIT0, StdHeader);

  // Enable SPI Prefetch for USB, set LPC cfg 0xBA bit 7 to 1.
  RwPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGBA, AccessWidth16, 0xFFFF, BIT7, StdHeader);
}



