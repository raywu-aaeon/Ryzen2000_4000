/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch HwAcpi controller
 *
 * Init HwAcpi Controller features.
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
#define FILECODE PROC_FCH_SANDSTONE_SSHWACPI_SSHWACPILATESERVICE_FILECODE

/**
 * GcpuRelatedSetting - Program Gcpu C related function
 *
 *
 *
 * @param[in] FchDataPtr   Fch configuration structure pointer.
 *
 */
VOID
GcpuRelatedSetting (
  IN  VOID     *FchDataPtr
  )
{
  UINT8        FchAcDcMsg;
  UINT8        FchTimerTickTrack;
  UINT8        FchClockInterruptTag;
  UINT8        FchOhciTrafficHanding;
  UINT8        FchEhciTrafficHanding;
  UINT8        FchGcpuMsgCMultiCore;
  UINT8        FchGcpuMsgCStage;
  UINT32       Value;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  FchAcDcMsg = (UINT8) LocalCfgPtr->Gcpu.AcDcMsg;
  FchTimerTickTrack = (UINT8) LocalCfgPtr->Gcpu.TimerTickTrack;
  FchClockInterruptTag = (UINT8) LocalCfgPtr->Gcpu.ClockInterruptTag;
  FchOhciTrafficHanding = (UINT8) LocalCfgPtr->Gcpu.OhciTrafficHanding;
  FchEhciTrafficHanding = (UINT8) LocalCfgPtr->Gcpu.EhciTrafficHanding;
  FchGcpuMsgCMultiCore = (UINT8) LocalCfgPtr->Gcpu.GcpuMsgCMultiCore;
  FchGcpuMsgCStage = (UINT8) LocalCfgPtr->Gcpu.GcpuMsgCStage;

  ReadMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGA0, AccessWidth32, &Value);
  Value = Value & 0xC07F00A0;

  if ( FchAcDcMsg ) {
    Value = Value | BIT0;
  }

  if ( FchTimerTickTrack ) {
    Value = Value | BIT1;
  }

  if ( FchClockInterruptTag ) {
    Value = Value | BIT10;
  }

  if ( FchOhciTrafficHanding ) {
    Value = Value | BIT13;
  }

  if ( FchEhciTrafficHanding ) {
    Value = Value | BIT15;
  }

  if ( FchGcpuMsgCMultiCore ) {
    Value = Value | BIT23;
  }

  if ( FchGcpuMsgCStage ) {
    Value = (Value | (BIT6 + BIT4 + BIT3 + BIT2));
  }

  WriteMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGA0, AccessWidth32, &Value);
}

/**
 * MtC1eEnable - Program Mt C1E Enable Function
 *
 *
 *
 * @param[in] FchDataPtr
 *
 */
VOID
MtC1eEnable (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  if ( LocalCfgPtr->HwAcpi.MtC1eEnable ) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG7A, AccessWidth16, ~(UINT32) BIT15, BIT15);
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG7A, AccessWidth16, ~(UINT32) (BIT3 + BIT2 + BIT1 + BIT0), 0x01);
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG80, AccessWidth16, ~(UINT32) (BIT13 + BIT7), BIT13 + BIT7);
  }
}

/**
 * StressResetModeLate - Stress Reset Mode
 *
 *
 *
 * @param[in] FchDataPtr
 *
 */
VOID
StressResetModeLate (
  IN  VOID     *FchDataPtr
  )
{
  UINT8                  ResetValue;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  switch ( LocalCfgPtr->HwAcpi.StressResetMode ) {
  case 0:
    return;
  case 1:
    ResetValue = FCH_KBC_RESET_COMMAND;
    LibAmdIoWrite (AccessWidth8, FCH_KBDRST_BASE_IO, &ResetValue, StdHeader);
    break;
  case 2:
    ResetValue = FCH_PCI_RESET_COMMAND06;
    LibAmdIoWrite (AccessWidth8, FCH_PCIRST_BASE_IO, &ResetValue, StdHeader);
    break;
  case 3:
    ResetValue = FCH_PCI_RESET_COMMAND0E;
    LibAmdIoWrite (AccessWidth8, FCH_PCIRST_BASE_IO, &ResetValue, StdHeader);
    break;
  case 4:
    LocalCfgPtr->HwAcpi.StressResetMode = 3;
    return;
  default:
    //ASSERT (FALSE);
    return;
  }
  while (LocalCfgPtr->HwAcpi.StressResetMode) {
  }
}

/**
 * FchEventInitUsbGpe - Init Gevent that mapped to Usb Pme
 *
 *
 *
 * @param[in] FchDataPtr
 *
 */
VOID
FchEventInitUsbGpe (
  IN  VOID     *FchDataPtr
  )
{
  UINT8                  Usb0GpeNum;
  UINT8                  Usb1GpeNum;
  UINT32                 SciLevl32;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  Usb0GpeNum = ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_xHC0Pme);
  Usb1GpeNum = ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_xHC1Pme);
  SciLevl32 = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG0C);
  //
  // XHC0
  //
  if (Usb0GpeNum != 0) {
    Usb0GpeNum &= 0x1F;
    SciLevl32 |= (UINT32) (1 << Usb0GpeNum);
  }
  //
  // XHC1
  //
  if (Usb1GpeNum != 0) {
    Usb1GpeNum &= 0x1F;
    SciLevl32 |= (UINT32) (1 << Usb1GpeNum);
  }
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG0C) = SciLevl32;
}


