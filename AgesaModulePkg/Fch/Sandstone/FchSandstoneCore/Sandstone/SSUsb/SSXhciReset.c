/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch Xhci controller
 *
 * Init Xhci Controller features (PEI phase).
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

#define FILECODE FCH_SANDSTONE_FCHSANDSTONECORE_SANDSTONE_SSUSB_SSXHCIRESET_FILECODE

VOID
FchInitRecoveryXhci (
  IN  VOID     *FchDataPtr
  );

/**
 * FchInitResetXhci - Config Xhci controller during Power-On
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitResetXhci (
  IN  VOID     *FchDataPtr
  )
{
  UINT8                       SleepType;
  FCH_RESET_DATA_BLOCK        *LocalCfgPtr;
  UINT32                      UsbId;

  UsbId = 0;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *)FchDataPtr;

  AGESA_TESTPOINT (TpFchInitResetUsb, NULL);

  SleepType = (ReadFchSleepType (LocalCfgPtr->StdHeader));

  if (LocalCfgPtr->FchReset.Xhci0Enable == FALSE) {
    FchSmnRW (0, FCH_SS_USB_NBIF_STRAP0, ~(UINT32) BIT28, 0, LocalCfgPtr->StdHeader);
    UsbId |= BIT0;
  }

  if (LocalCfgPtr->FchReset.Xhci1Enable == FALSE) {
    FchSmnRW (0, FCH_SS_USB1_NBIF_STRAP0, ~(UINT32) BIT28, 0, LocalCfgPtr->StdHeader);
    UsbId |= BIT1;
  }

  FchRVXhciSmuUsbPowerService (UsbId);

  if (LocalCfgPtr->FchReset.Xhci0Enable | LocalCfgPtr->FchReset.Xhci1Enable) {
    if (SleepType != ACPI_SLPTYP_S3) {
      //FchRVXhci0InitBootProgram (FchDataPtr);
      //FchRVXhci1InitBootProgram (FchDataPtr);
      FchRVUsb3InitBootProgram (FchDataPtr);
      //FchRVXhciSmuService (SMC_MSG_UsbInit);
    } else {
      //FchRVXhci0InitS3ExitProgram (FchDataPtr);
      //FchRVXhci1InitS3ExitProgram (FchDataPtr);
      FchRVUsb3InitS3ExitProgram (FchDataPtr);
      //FchRVXhciSmuService (SMC_MSG_UsbD3Exit);
    }
  }


}

/**
 * FchInitRecoveryLpc - Config Xhci controller during Crisis
 * Recovery
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitRecoveryXhci (
  IN  VOID     *FchDataPtr
  )
{
}


