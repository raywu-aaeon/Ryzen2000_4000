/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH PEIM
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH PEIM
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
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
 */
#include "FchReset2.h"

UINT16
ReadPmio16 (
  IN       UINT8        Index
  )
{
  UINT8    bTemp;

  IoWrite8 (FCH_RESET_REGCD6, Index);
  bTemp = IoRead8 (FCH_RESET_REGCD7);
  IoWrite8 (FCH_RESET_REGCD6, Index + 1);
  return (UINT16) ((IoRead8 (FCH_RESET_REGCD7) << 8) + bTemp);
}

/*********************************************************************************
 * Name: FchPeiReset2
 *
 * Description
 *   Resets the entire platform.
 *
 * Input
 *   ResetType   - warm or cold
 *   ResetStatus - possible cause of reset
 *   DataSize    - Size of ResetData in bytes
 *   ResetData   - Optional Unicode string
 *  For details, see PiPeiCis.h
 *
 * Output
 *   none if the reset is successful
 *
 *********************************************************************************/
VOID
EFIAPI
FchPeiReset2 (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  UINT8      InitialData;
  UINT8      OutputData;
  UINT8      PwrRsrCfg;
  UINT16     AcpiGpeBase;
  UINT16     AcpiPm1StsBase;
  UINT16     AcpiPm1CntBase;
  UINT32     Gpe0Enable;
  UINT16     PmCntl;
  UINT16     PwrSts;

  DEBUG ((DEBUG_INFO, "[FchPeiReset2] FchPeiReset2 invoked:  ResetType = %d\n", ResetType));
  switch (ResetType) {
  case EfiResetWarm:
    InitialData = HARDSTARTSTATE;
    OutputData  = HARDRESET;
    IoWrite8 (FCH_RESET_REGCD6, 0x10);
    PwrRsrCfg = IoRead8 (FCH_RESET_REGCD7);
    PwrRsrCfg = PwrRsrCfg & 0xFD; //clear ToggleAllPwrGoodOnCf9
    IoWrite8 (FCH_RESET_REGCD7, PwrRsrCfg);
    break;

  case EfiResetCold:
    InitialData = HARDSTARTSTATE;
    OutputData  = HARDRESET;
    IoWrite8 (FCH_RESET_REGCD6, 0x10);
    PwrRsrCfg = IoRead8 (FCH_RESET_REGCD7);
    PwrRsrCfg = PwrRsrCfg | BIT1; //set ToggleAllPwrGoodOnCf9
    IoWrite8 (FCH_RESET_REGCD7, PwrRsrCfg);
    break;

  case EfiResetShutdown:
    // Disable all GPE0 Event
    AcpiGpeBase = ReadPmio16 (FCH_RESET_PMIOA_REG68);
    AcpiGpeBase += 4; //Get enable base
    Gpe0Enable  = 0;
    IoWrite32 (AcpiGpeBase, Gpe0Enable);

    // Clear Power Button status.
    AcpiPm1StsBase = ReadPmio16 (FCH_RESET_PMIOA_REG60);
    PwrSts  = BIT8 | BIT15; //Clear WakeStatus with PwrBtnStatus
    IoWrite16 (AcpiPm1StsBase, PwrSts);

    // Transform system into S5 sleep state
    AcpiPm1CntBase = ReadPmio16 (FCH_RESET_PMIOA_REG62);
    PmCntl  = IoRead16 (AcpiPm1CntBase);
    PmCntl  = (PmCntl & ~SLP_TYPE) | SUS_S5 | SLP_EN;
    IoWrite16 (AcpiPm1CntBase, PmCntl);
    FCH_DEADLOOP();
    return ;

  default:
    return ;
  }

  IoWrite8 (FCH_RESET_REGCF9, InitialData);
  IoWrite8 (FCH_RESET_REGCF9, OutputData);

  //
  // Given we should have reset getting here would be bad
  //
  FCH_DEADLOOP();
}

