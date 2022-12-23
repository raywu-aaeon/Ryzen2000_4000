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
 *  USD. You agree to defend, indemnify and hold harmless AMD and its
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


//This file is auto generated, don't edit it manually

#include <Base.h>
#include <Library/DebugLib.h>
#include "AmdCbsVariable.h"
#include <Library/PcdLib.h>

VOID
CbsSetAgesaPcds (
  IN       VOID *CbsVariable
  )
{
  CBS_CONFIG *Setup_Config;

  if (CbsVariable == NULL) {
    ASSERT (FALSE);
    return;
  }
  Setup_Config = (CBS_CONFIG *) CbsVariable;
  if (Setup_Config->CbsCmnCpuGenWA05 != 0xFF) {
    PcdSet8 (PcdAmdRedirectForReturnDis, Setup_Config->CbsCmnCpuGenWA05);
  }

  if (Setup_Config->CbsCmnCpuCpb != 1) {
    PcdSet8 (PcdAmdCpbMode, Setup_Config->CbsCmnCpuCpb);
  }

  if (Setup_Config->CbsCmnCpuGlobalCstateCtrl != 3) {
    PcdSet8 (PcdAmdCStateMode, Setup_Config->CbsCmnCpuGlobalCstateCtrl);
  }

  if (Setup_Config->CbsCmnCpuStreamingStoresCtrl != 0xFF) {
    PcdSet8 (PcdAmdStreamingStoresCtrl, Setup_Config->CbsCmnCpuStreamingStoresCtrl);
  }

  if (Setup_Config->CbsCpuPstCustomP0 != 2) {
    PcdSet8 (PcdAmdCcxP0Setting, Setup_Config->CbsCpuPstCustomP0);
  }

  //Check Display Condition CbsCpuPstCustomP0=Custom
  if ((Setup_Config->CbsCpuPstCustomP0 == 0x1)) {
    PcdSet8 (PcdAmdCcxP0Fid, Setup_Config->CbsCpuPst0Fid);
  }

  //Check Display Condition CbsCpuPstCustomP0=Custom
  if ((Setup_Config->CbsCpuPstCustomP0 == 0x1)) {
    PcdSet8 (PcdAmdCcxP0Did, Setup_Config->CbsCpuPst0Did);
  }

  //Check Display Condition CbsCpuPstCustomP0=Custom
  if ((Setup_Config->CbsCpuPstCustomP0 == 0x1)) {
    PcdSet8 (PcdAmdCcxP0Vid, Setup_Config->CbsCpuPst0Vid);
  }

  if (Setup_Config->CbsCmnCpuGenDowncoreCtrl != 0) {
    PcdSet8 (PcdAmdDownCoreMode, Setup_Config->CbsCmnCpuGenDowncoreCtrl);
  }

  if (Setup_Config->CbsCmnCpuGenSmtEn != 0x1) {
    PcdSet8 (PcdAmdSmtMode, Setup_Config->CbsCmnCpuGenSmtEn);
  }

  if (Setup_Config->CbsDfCmnDramScrubTime != 0xFF) {
    PcdSet8 (PcdAmdFabricDramScrubTime, Setup_Config->CbsDfCmnDramScrubTime);
  }

  if (Setup_Config->CbsDbgGnbAudioIOs != 0xF) {
    PcdSet8 (PcdAmdNbioAudioSelect, Setup_Config->CbsDbgGnbAudioIOs);
  }

  if (Setup_Config->CbsCmnGnbGfxiGPU_CONTROL != 0xf) {
    PcdSet8 (PcdCfgIgpuContorl, Setup_Config->CbsCmnGnbGfxiGPU_CONTROL);
  }

  //Check Display Condition CbsCmnGnbGfxiGPU_CONTROL=Auto|CbsCmnGnbGfxiGPU_CONTROL=Forces
  if (((Setup_Config->CbsCmnGnbGfxiGPU_CONTROL == 0x0)) ||((Setup_Config->CbsCmnGnbGfxiGPU_CONTROL == 0x2))) {
    if (Setup_Config->CbsCmnGnbGfxNbAzalia != 0xf) {
      PcdSetBool (PcdCfgAzaliaEnable, Setup_Config->CbsCmnGnbGfxNbAzalia);
    }
  }

  if (Setup_Config->CbsCmnGnbNbIOMMU != 0xf) {
    PcdSetBool (PcdCfgIommuSupport, Setup_Config->CbsCmnGnbNbIOMMU);
  }

  if (Setup_Config->CbsCmnGnbPciePsppPolicy != 0xf) {
    PcdSet8 (PcdPsppPolicy, Setup_Config->CbsCmnGnbPciePsppPolicy);
  }

  if (Setup_Config->CbsCmnFchSataEnable != 0xf) {
    PcdSetBool (PcdSataEnable, Setup_Config->CbsCmnFchSataEnable);
  }

  //Check Display Condition CbsCmnFchSataEnable=Enabled
  if ((Setup_Config->CbsCmnFchSataEnable == 0x1)) {
    if (Setup_Config->CbsCmnFchSataClass != 0xf) {
      PcdSet8 (PcdSataClass, Setup_Config->CbsCmnFchSataClass);
    }
  }

  if (Setup_Config->CbsCmnFchSataRasSupport != 0xf) {
    PcdSetBool (PcdSataRasSupport, Setup_Config->CbsCmnFchSataRasSupport);
  }

  if (Setup_Config->CbsCmnFchSataAhciDisPrefetchFunction != 0xf) {
    PcdSetBool (PcdSataAhciDisPrefetchFunction, Setup_Config->CbsCmnFchSataAhciDisPrefetchFunction);
  }

  if (Setup_Config->CbsDbgFchSataAggresiveDevSlpP0 != 0xF) {
    PcdSetBool (PcdSataDevSlpPort0, Setup_Config->CbsDbgFchSataAggresiveDevSlpP0);
  }

  if (Setup_Config->CbsDbgFchSataAggresiveDevSlpP1 != 0xF) {
    PcdSetBool (PcdSataDevSlpPort1, Setup_Config->CbsDbgFchSataAggresiveDevSlpP1);
  }

  if (Setup_Config->CbsCmnFchUsbXHCI0Enable != 0xf) {
    PcdSetBool (PcdXhci0Enable, Setup_Config->CbsCmnFchUsbXHCI0Enable);
  }

  //Check Display Condition CbsComboFlag=1|CbsComboFlag=2
  if (((Setup_Config->CbsComboFlag == 0x1)) ||((Setup_Config->CbsComboFlag == 0x2))) {
    if (Setup_Config->CbsCmnFchUsbXHCI1Enable != 0xf) {
      PcdSetBool (PcdXhci1Enable, Setup_Config->CbsCmnFchUsbXHCI1Enable);
    }
  }

  PcdSet8 (PcdPwrFailShadow, Setup_Config->CbsCmnFchSystemPwrFailShadow);

  //Check Display Condition CbsCmnFchUart0Config = Enabled
  if ((Setup_Config->CbsCmnFchUart0Config == 0x1)) {
    if (Setup_Config->CbsCmnFchUart0LegacyConfig != 0xf) {
      PcdSet8 (FchUart0LegacyEnable, Setup_Config->CbsCmnFchUart0LegacyConfig);
    }
  }

  //Check Display Condition CbsCmnFchUart1Config = Enabled
  if ((Setup_Config->CbsCmnFchUart1Config == 0x1)) {
    if (Setup_Config->CbsCmnFchUart1LegacyConfig != 0xf) {
      PcdSet8 (FchUart1LegacyEnable, Setup_Config->CbsCmnFchUart1LegacyConfig);
    }
  }

  //Check Display Condition CbsCmnFchUart2Config = Enabled
  if ((Setup_Config->CbsCmnFchUart2Config == 0x1)) {
    if (Setup_Config->CbsCmnFchUart2LegacyConfig != 0xf) {
      PcdSet8 (FchUart2LegacyEnable, Setup_Config->CbsCmnFchUart2LegacyConfig);
    }
  }

  //Check Display Condition CbsCmnFchUart3Config = Enabled
  if ((Setup_Config->CbsCmnFchUart3Config == 0x1)) {
    if (Setup_Config->CbsCmnFchUart3LegacyConfig != 0xf) {
      PcdSet8 (FchUart3LegacyEnable, Setup_Config->CbsCmnFchUart3LegacyConfig);
    }
  }

  if (Setup_Config->CbsCmnFchEspiConfig != 0xf) {
    PcdSetBool (PcdEspiEnable, Setup_Config->CbsCmnFchEspiConfig);
  }

  if (Setup_Config->CbsCmnFchXgbe0Enable != 0xf) {
    PcdSetBool (PcdXgbePort0ConfigEn, Setup_Config->CbsCmnFchXgbe0Enable);
  }

  if (Setup_Config->CbsCmnFchXgbe1Enable != 0xf) {
    PcdSetBool (PcdXgbePort1ConfigEn, Setup_Config->CbsCmnFchXgbe1Enable);
  }

  if (Setup_Config->CbsDbgFchEmmcEnable != 0xf) {
    PcdSet8 (PcdEmmcEnable, Setup_Config->CbsDbgFchEmmcEnable);
  }

  if (Setup_Config->CbsDbgFchEmmcDriverType != 0xf) {
    PcdSet8 (PcdEmmcDriverType, Setup_Config->CbsDbgFchEmmcDriverType);
  }

  if (Setup_Config->CbsDbgFchEmmcD3Support != 0xf) {
    PcdSetBool (PcdEmmcD3Support, Setup_Config->CbsDbgFchEmmcD3Support);
  }

  if (Setup_Config->CbsDbgFchEmmcBoot != 0xf) {
    PcdSetBool (PcdEmmcBoot, Setup_Config->CbsDbgFchEmmcBoot);
  }

  if (Setup_Config->CbsCmnFchLpcClockRunEn != 0xf) {
    PcdSetBool (PcdLpcClkRunEn, Setup_Config->CbsCmnFchLpcClockRunEn);
  }

  if (Setup_Config->CbsCmnToggleAllPwrGoodOnCf9 != 2) {
    PcdSetBool (PcdToggleAllPwrGoodOnCf9, Setup_Config->CbsCmnToggleAllPwrGoodOnCf9);
  }

  if (Setup_Config->CbsCmnPTSataClass != 0xf) {
    PcdSet8 (PcdPTSataMode, Setup_Config->CbsCmnPTSataClass);
  }

  if (Setup_Config->CbsDbgPTSataAggresiveDevSlpP0 != 0xF) {
    PcdSet8 (PcdPTSataAggresiveDevSlpP0, Setup_Config->CbsDbgPTSataAggresiveDevSlpP0);
  }

  if (Setup_Config->CbsDbgPTSataAggresiveDevSlpP1 != 0xF) {
    PcdSet8 (PcdPTSataAggresiveDevSlpP1, Setup_Config->CbsDbgPTSataAggresiveDevSlpP1);
  }

  if (Setup_Config->CbsCmnPTSataPort0Enable != 0xf) {
    PcdSet8 (PcdPTSataPort0Enable, Setup_Config->CbsCmnPTSataPort0Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort1Enable != 0xf) {
    PcdSet8 (PcdPTSataPort1Enable, Setup_Config->CbsCmnPTSataPort1Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort2Enable != 0xf) {
    PcdSet8 (PcdPTSataPort2Enable, Setup_Config->CbsCmnPTSataPort2Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort3Enable != 0xf) {
    PcdSet8 (PcdPTSataPort3Enable, Setup_Config->CbsCmnPTSataPort3Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort4Enable != 0xf) {
    PcdSet8 (PcdPTSataPort4Enable, Setup_Config->CbsCmnPTSataPort4Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort5Enable != 0xf) {
    PcdSet8 (PcdPTSataPort5Enable, Setup_Config->CbsCmnPTSataPort5Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort6Enable != 0xf) {
    PcdSet8 (PcdPTSataPort6Enable, Setup_Config->CbsCmnPTSataPort6Enable);
  }

  if (Setup_Config->CbsCmnPTSataPort7Enable != 0xf) {
    PcdSet8 (PcdPTSataPort7Enable, Setup_Config->CbsCmnPTSataPort7Enable);
  }

  if (Setup_Config->CbsDbgPTXhciGen1 != 0xF) {
    PcdSet8 (PcdPTXhciGen1, Setup_Config->CbsDbgPTXhciGen1);
  }

  if (Setup_Config->CbsDbgPTXhciGen2 != 0xF) {
    PcdSet8 (PcdPTXhciGen2, Setup_Config->CbsDbgPTXhciGen2);
  }

  if (Setup_Config->CbsDbgPTUsbEqualization4 != 0xF) {
    PcdSet8 (PcdPTUsbEqualization4, Setup_Config->CbsDbgPTUsbEqualization4);
  }

  if (Setup_Config->CbsDbgPTUsbRedriver != 0xF) {
    PcdSet8 (PcdPTUsbRedriver, Setup_Config->CbsDbgPTUsbRedriver);
  }

  if (Setup_Config->CbsDbgPTUsb31P0 != 0xF) {
    PcdSet8 (PcdPTUsb31P0, Setup_Config->CbsDbgPTUsb31P0);
  }

  if (Setup_Config->CbsDbgPTUsb31P1 != 0xF) {
    PcdSet8 (PcdPTUsb31P1, Setup_Config->CbsDbgPTUsb31P1);
  }

  if (Setup_Config->CbsDbgPTUsb30P0 != 0xF) {
    PcdSet8 (PcdPTUsb30P0, Setup_Config->CbsDbgPTUsb30P0);
  }

  if (Setup_Config->CbsDbgPTUsb30P1 != 0xF) {
    PcdSet8 (PcdPTUsb30P1, Setup_Config->CbsDbgPTUsb30P1);
  }

  if (Setup_Config->CbsDbgPTUsb30P2 != 0xF) {
    PcdSet8 (PcdPTUsb30P2, Setup_Config->CbsDbgPTUsb30P2);
  }

  if (Setup_Config->CbsDbgPTUsb30P3 != 0xF) {
    PcdSet8 (PcdPTUsb30P3, Setup_Config->CbsDbgPTUsb30P3);
  }

  if (Setup_Config->CbsDbgPTUsb30P4 != 0xF) {
    PcdSet8 (PcdPTUsb30P4, Setup_Config->CbsDbgPTUsb30P4);
  }

  if (Setup_Config->CbsDbgPTUsb30P5 != 0xF) {
    PcdSet8 (PcdPTUsb30P5, Setup_Config->CbsDbgPTUsb30P5);
  }

  if (Setup_Config->CbsDbgPTUsb20P0 != 0xF) {
    PcdSet8 (PcdPTUsb20P0, Setup_Config->CbsDbgPTUsb20P0);
  }

  if (Setup_Config->CbsDbgPTUsb20P1 != 0xF) {
    PcdSet8 (PcdPTUsb20P1, Setup_Config->CbsDbgPTUsb20P1);
  }

  if (Setup_Config->CbsDbgPTUsb20P2 != 0xF) {
    PcdSet8 (PcdPTUsb20P2, Setup_Config->CbsDbgPTUsb20P2);
  }

  if (Setup_Config->CbsDbgPTUsb20P3 != 0xF) {
    PcdSet8 (PcdPTUsb20P3, Setup_Config->CbsDbgPTUsb20P3);
  }

  if (Setup_Config->CbsDbgPTUsb20P4 != 0xF) {
    PcdSet8 (PcdPTUsb20P4, Setup_Config->CbsDbgPTUsb20P4);
  }

  if (Setup_Config->CbsDbgPTUsb20P5 != 0xF) {
    PcdSet8 (PcdPTUsb20P5, Setup_Config->CbsDbgPTUsb20P5);
  }

  if (Setup_Config->CbsDbgPTProm2Usb31P0 != 0xF) {
    PcdSet8 (PcdPTProm2Usb31P0, Setup_Config->CbsDbgPTProm2Usb31P0);
  }

  if (Setup_Config->CbsDbgPTProm2Usb31P1 != 0xF) {
    PcdSet8 (PcdPTProm2Usb31P1, Setup_Config->CbsDbgPTProm2Usb31P1);
  }

  if (Setup_Config->CbsDbgPTProm2Usb30P0 != 0xF) {
    PcdSet8 (PcdPTProm2Usb30P0, Setup_Config->CbsDbgPTProm2Usb30P0);
  }

  if (Setup_Config->CbsDbgPTProm2Usb30P1 != 0xF) {
    PcdSet8 (PcdPTProm2Usb30P1, Setup_Config->CbsDbgPTProm2Usb30P1);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P0 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P0, Setup_Config->CbsDbgPTProm2Usb20P0);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P1 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P1, Setup_Config->CbsDbgPTProm2Usb20P1);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P2 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P2, Setup_Config->CbsDbgPTProm2Usb20P2);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P3 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P3, Setup_Config->CbsDbgPTProm2Usb20P3);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P4 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P4, Setup_Config->CbsDbgPTProm2Usb20P4);
  }

  if (Setup_Config->CbsDbgPTProm2Usb20P5 != 0xF) {
    PcdSet8 (PcdPTProm2Usb20P5, Setup_Config->CbsDbgPTProm2Usb20P5);
  }

  if (Setup_Config->CbsDbgPTProm1Usb31P0 != 0xF) {
    PcdSet8 (PcdPTProm1Usb31P0, Setup_Config->CbsDbgPTProm1Usb31P0);
  }

  if (Setup_Config->CbsDbgPTProm1Usb31P1 != 0xF) {
    PcdSet8 (PcdPTProm1Usb31P1, Setup_Config->CbsDbgPTProm1Usb31P1);
  }

  if (Setup_Config->CbsDbgPTProm1Usb30P0 != 0xF) {
    PcdSet8 (PcdPTProm1Usb30P0, Setup_Config->CbsDbgPTProm1Usb30P0);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P0 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P0, Setup_Config->CbsDbgPTProm1Usb20P0);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P1 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P1, Setup_Config->CbsDbgPTProm1Usb20P1);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P2 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P2, Setup_Config->CbsDbgPTProm1Usb20P2);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P3 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P3, Setup_Config->CbsDbgPTProm1Usb20P3);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P4 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P4, Setup_Config->CbsDbgPTProm1Usb20P4);
  }

  if (Setup_Config->CbsDbgPTProm1Usb20P5 != 0xF) {
    PcdSet8 (PcdPTProm1Usb20P5, Setup_Config->CbsDbgPTProm1Usb20P5);
  }

  if (Setup_Config->CbsCmnPTPciePort0Enable != 0xf) {
    PcdSet8 (PcdPTPciePort0Enable, Setup_Config->CbsCmnPTPciePort0Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort1Enable != 0xf) {
    PcdSet8 (PcdPTPciePort1Enable, Setup_Config->CbsCmnPTPciePort1Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort2Enable != 0xf) {
    PcdSet8 (PcdPTPciePort2Enable, Setup_Config->CbsCmnPTPciePort2Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort3Enable != 0xf) {
    PcdSet8 (PcdPTPciePort3Enable, Setup_Config->CbsCmnPTPciePort3Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort4Enable != 0xf) {
    PcdSet8 (PcdPTPciePort4Enable, Setup_Config->CbsCmnPTPciePort4Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort5Enable != 0xf) {
    PcdSet8 (PcdPTPciePort5Enable, Setup_Config->CbsCmnPTPciePort5Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort6Enable != 0xf) {
    PcdSet8 (PcdPTPciePort6Enable, Setup_Config->CbsCmnPTPciePort6Enable);
  }

  if (Setup_Config->CbsCmnPTPciePort7Enable != 0xf) {
    PcdSet8 (PcdPTPciePort7Enable, Setup_Config->CbsCmnPTPciePort7Enable);
  }


}
