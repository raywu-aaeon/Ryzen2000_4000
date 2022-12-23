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
*/


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "FchPlatform.h"
#include  "Filecode.h"
#define FILECODE PROC_FCH_SANDSTONE_SSSATA_SSSATASERVICE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
UINT8  NumOfSataPorts = SANDSTONE_SATA_PORT_NUM;

/**
 * FchInitMidProgramSataRegs - Sata Control register setting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitMidProgramSataRegs (
  IN  UINT32   DieBusNum,
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

}

/**
 * FchInitLateProgramSataRegs - Sata Control register setting
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitLateProgramSataRegs (
  IN  UINT32   DieBusNum,
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  FchSSSataShutdownUnconnectedSataPortClock (0, FchDataPtr);

  FchSSSataInitMMC (0, FchDataPtr);
}

/**
 * FchSataSetDeviceNumMsi - Program Sata controller support
 * device number cap & MSI cap
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchSataSetDeviceNumMsi (
  IN  UINT32   DieBusNum,
  IN  VOID     *FchDataPtr
  )
{
  // Leave as default for BU....
}


/**
 * FchSataDriveDetection - Sata drive detection
 *
 *   - Sata Ide & Sata Ide to Ahci only
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 * @param[in] *Bar5Ptr Sata BAR5 base address.
 *
 */
VOID
FchSataDriveDetection (
  IN  VOID       *FchDataPtr,
  IN  UINT32     *Bar5Ptr
  )
{
  UINT32       SataBarInfo;
  UINT8        PortNumByte;
  UINT8        SataPortType;
  UINT16       IoBaseWord;
  UINT32       SataLoopVarDWord;
  UINT32       SataBusNum;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  SataBusNum = SataGetBusCNumber (0, StdHeader);
  if ((SataBusNum == 0) || (SataBusNum == 0xFF00)) {
    return;
  }

  // For H/W emulator, support only Port 0
  for ( PortNumByte = 0; PortNumByte < NumOfSataPorts; PortNumByte++ ) {

    ReadMem (*Bar5Ptr + FCH_SATA_BAR5_REG128 + PortNumByte * 0x80, AccessWidth32, &SataBarInfo);

    if ( ( SataBarInfo & 0x0F ) == 0x03 ) {
      if ( PortNumByte & BIT0 ) {
        //
        //this port belongs to secondary channel
        //
        ReadPci (((UINT32) ((SataBusNum + SANDSTONE_SATA_DEV_FUN) << 16) + FCH_SATA_REG18), AccessWidth16, &IoBaseWord, StdHeader);
      } else {
        //
        //this port belongs to primary channel
        //
        ReadPci (((UINT32) ((SataBusNum + SANDSTONE_SATA_DEV_FUN) << 16) + FCH_SATA_REG10), AccessWidth16, &IoBaseWord, StdHeader);
      }

      //
      //if legacy ide mode, then the bar registers don't contain the correct values. So we need to hardcode them
      //
      if ( LocalCfgPtr->Sata.SataClass == SataLegacyIde ) {
        IoBaseWord = ( (0x170) | ((UINT16) ( (~((UINT8) (PortNumByte & BIT0) << 7)) & 0x80 )) );
      }

      if ( PortNumByte & BIT1 ) {
        //
        //this port is slave
        //
        SataPortType = 0xB0;
      } else {
        //
        //this port is master
        //
        SataPortType = 0xA0;
      }

      IoBaseWord &= 0xFFF8;
      LibAmdIoWrite (AccessWidth8, IoBaseWord + 6, &SataPortType, StdHeader);

      //
      //Wait in loop for 30s for the drive to become ready
      //
      for ( SataLoopVarDWord = 0; SataLoopVarDWord < 300000; SataLoopVarDWord++ ) {
        LibAmdIoRead (AccessWidth8, IoBaseWord + 7, &SataPortType, StdHeader);
        if ( (SataPortType & 0x88) == 0 ) {
          break;
        }
        FchStall (100, StdHeader);
      }
    }
  }
}

