/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH DXE Driver
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *******************************************************************************
 */
#include "FchDxe.h"

extern EFI_GUID gFchResetDataHobGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern FCH_DATA_BLOCK InitEnvCfgDefault;
//
// Private Function Declaration
//
VOID
InvokeFchInitMid (
  IN       EFI_EVENT        Event,
  IN       VOID             *Context
  )
{
  FCH_DATA_BLOCK        *FchPolicy;
  AGESA_STATUS          AgesaStatus;

  DEBUG ((DEBUG_INFO, "[FchInitMid] Fch Init - After PCI Scan ...Start\n"));
  FchPolicy = (FCH_DATA_BLOCK*) Context;
  AgesaStatus = FchInitMid (FchPolicy);
  DEBUG ((DEBUG_INFO, "[FchInitMid] Fch Init - After PCI Scan ...Complete\n"));

  gBS->CloseEvent (Event);
}

VOID
InvokeFchInitLate (
  IN       EFI_EVENT        Event,
  IN       VOID             *Context
  )
{
  FCH_DATA_BLOCK        *FchPolicy;
  AGESA_STATUS          AgesaStatus;

  DEBUG ((DEBUG_INFO, "[FchInitLate] Fch Init - Before Boot ...Start\n"));
  FchPolicy = (FCH_DATA_BLOCK*) Context;
  AgesaStatus = FchInitLate (FchPolicy);
  DEBUG ((DEBUG_INFO, "[FchInitLate] Fch Init - Before Boot ...Complete\n"));

  gBS->CloseEvent (Event);
}

FCH_DATA_BLOCK*
FchInitDataBlock (
  IN OUT   FCH_DATA_BLOCK  *FchParams
  )
{
  EFI_STATUS                Status;
  EFI_HOB_GUID_TYPE         *FchHob;
  FCH_RESET_DATA_BLOCK      *FchResetParams;
  VOID                      *PcdDataPtr;
  UINT16                    IoEnable16;
  UINT16                    UartChannel;
  UINT8                     UartLegacy[4];

  //load default
  gBS->CopyMem (
         FchParams,
         &InitEnvCfgDefault,
         sizeof (FCH_DATA_BLOCK)
         );
  //find HOB and update with reset data block
  FchHob = GetFirstGuidHob (&gFchResetDataHobGuid);
  FchHob++;
  FchResetParams = (FCH_RESET_DATA_BLOCK *) ((UINTN)FchHob - sizeof (UINT32));
  //FchParams->FchResetDataBlock = FchResetParams;
  gBS->CopyMem (
         &FchParams->FchResetDataBlock,
         FchResetParams,
         sizeof (FCH_RESET_DATA_BLOCK)
         );

  FchParams->Usb.Xhci0Enable              = FchResetParams->FchReset.Xhci0Enable;
  FchParams->Usb.Xhci1Enable              = FchResetParams->FchReset.Xhci1Enable;
  FchParams->Spi.SpiFastSpeed             = FchResetParams->FastSpeed;
  FchParams->Spi.WriteSpeed               = FchResetParams->WriteSpeed;
  FchParams->Spi.SpiMode                  = FchResetParams->Mode;
  FchParams->Spi.SpiSpeed                 = FchResetParams->SpiSpeed;
  FchParams->Spi.AutoMode                 = FchResetParams->AutoMode;
  FchParams->Spi.SpiBurstWrite            = FchResetParams->BurstWrite;
  FchParams->Sata.SataMode.Sata6AhciCap   = (UINT8) FchResetParams->Sata6AhciCap;
  FchParams->Misc.Cg2Pll                  = FchResetParams->Cg2Pll;
  FchParams->Sata.SataMode.SataEnable     = FchResetParams->FchReset.SataEnable;
  FchParams->Sata.SataMode.SataSetMaxGen2 = FchResetParams->SataSetMaxGen2;
  FchParams->Sata.SataMode.SataClkMode    = FchResetParams->SataClkMode;
  FchParams->Sata.SataMode.SataModeReg    = FchResetParams->SataModeReg;
  FchParams->Sata.SataInternal100Spread   = (UINT8) FchResetParams->SataInternal100Spread;

  //FchParams->Promontory                   = FchResetParams->Promontory;
  gBS->CopyMem (
         &FchParams->Promontory,
         &FchResetParams->Promontory,
         sizeof (FCH_PT)
         );

  //Platform call out
  Status = FchPlatformPTDxeInit ((VOID *)&FchParams->Promontory);

  ASSERT_EFI_ERROR (Status);

  Status = FchPlatformOemDxeInit ((VOID *)FchParams);

  ASSERT_EFI_ERROR (Status);

  IDS_HOOK (IDS_HOOK_FCH_INIT_ENV, NULL, (VOID *)FchParams);

  //Dynamic PCDs
  FchParams->Ab.AbClockGating             = PcdGet8 (PcdAbClockGating);
  FchParams->Ab.ALinkClkGateOff           = PcdGet8 (PcdALinkClkGateOff);
  FchParams->Ab.BLinkClkGateOff           = PcdGet8 (PcdBLinkClkGateOff);
  FchParams->Ab.SbgMemoryPowerSaving      = PcdGetBool (PcdSbgMemoryPowerSaving);
  FchParams->Ab.SbgClockGating            = PcdGetBool (PcdSbgClockGating);
  FchParams->Ab.XdmaDmaWrite16ByteMode    = PcdGetBool (PcdXdmaDmaWrite16ByteMode);
  FchParams->Ab.XdmaMemoryPowerSaving     = PcdGetBool (PcdXdmaMemoryPowerSaving);
  FchParams->Ab.XdmaPendingNprThreshold   = PcdGet8 (PcdXdmaPendingNprThreshold);
  FchParams->Ab.XdmaDncplOrderDis         = PcdGetBool (PcdXdmaDncplOrderDis);
  FchParams->Ab.SdphostBypassDataPack     = PcdGetBool (PcdSdphostBypassDataPack);
  FchParams->Ab.SdphostDisNpmwrProtect    = PcdGetBool (PcdSdphostDisNpmwrProtect);
  FchParams->Ab.ResetCpuOnSyncFlood       = PcdGetBool (PcdResetCpuOnSyncFlood);

  FchParams->Sata.SataClass               = PcdGet8 (PcdSataClass);
  FchParams->Sata.SataAggrLinkPmCap       = PcdGet8 (PcdSataAggrLinkPmCap);
  FchParams->Sata.SataPortMultCap         = PcdGet8 (PcdSataPortMultCap);
  FchParams->Sata.SataPscCap              = PcdGet8 (PcdSataPscCap);
  FchParams->Sata.SataSscCap              = PcdGet8 (PcdSataSscCap);
  FchParams->Sata.SataClkAutoOff          = PcdGet8 (PcdSataClkAutoOff);
  FchParams->Sata.SataFisBasedSwitching   = PcdGet8 (PcdSataFisBasedSwitching);
  FchParams->Sata.SataCccSupport          = PcdGet8 (PcdSataCccSupport);
  FchParams->Sata.SataDisableGenericMode  = PcdGet8 (PcdSataDisableGenericMode);
  FchParams->Sata.SataPortMd.Port0        = PcdGet8 (PcdSataModePort0);
  FchParams->Sata.SataPortMd.Port1        = PcdGet8 (PcdSataModePort1);
  FchParams->Sata.SataEspPort.Port0       = PcdGet8 (PcdSataEspPort0);
  FchParams->Sata.SataEspPort.Port1       = PcdGet8 (PcdSataEspPort1);
  FchParams->Sata.SataPortPower.Port0     = PcdGet8 (PcdSataPortPowerPort0);
  FchParams->Sata.SataPortPower.Port1     = PcdGet8 (PcdSataPortPowerPort1);
  FchParams->Sata.SataTargetSupport8Device          = PcdGet8 (PcdSataTargetSupport8Device);
  FchParams->Sata.SataAhciEnclosureManagement       = PcdGet8 (PcdSataAhciEnclosureManagement);
  FchParams->Sata.SataMsiEnable           = PcdGetBool (PcdSataMsiEnable);
  FchParams->Sata.SataRasSupport          = PcdGetBool (PcdSataRasSupport);
  FchParams->Sata.SataAhciDisPrefetchFunction       = PcdGetBool (PcdSataAhciDisPrefetchFunction);
  FchParams->Sata.SataDevSlpPort0         = PcdGetBool (PcdSataDevSlpPort0);
  FchParams->Sata.SataDevSlpPort1         = PcdGetBool (PcdSataDevSlpPort1);
  FchParams->Sata.SataDevSlpPort0Num      = PcdGet8 (PcdSataDevSlpPort0Num);
  FchParams->Sata.SataDevSlpPort1Num      = PcdGet8 (PcdSataDevSlpPort1Num);
  FchParams->Sata.SataPhyPllShutDown      = PcdGet8 (PcdSataPhyPllShutDown);
  FchParams->Sata.SataSgpio0              = PcdGet8 (PcdSataSgpio0);
  FchParams->Sata.SataControllerAutoShutdown        = PcdGetBool (PcdSataControllerAutoShutdown);

  FchParams->Hpet.HpetEnable              = PcdGetBool (PcdHpetEnable);
  FchParams->Hpet.HpetMsiDis              = PcdGetBool (PcdHpetMsiDis);
  FchParams->Hpet.HpetBase                = 0xFED00000;

  FchParams->HwAcpi.SpreadSpectrum        = PcdGetBool (PcdSpreadSpectrum);
  FchParams->HwAcpi.WatchDogTimerBase     = 0xFEB00000;
  FchParams->Misc.NoneSioKbcSupport       = PcdGetBool (PcdNoneSioKbcSupport);
  FchParams->HwAcpi.PwrFailShadow         = PcdGet8 (PcdPwrFailShadow);
  FchParams->HwAcpi.StressResetMode       = PcdGet8 (PcdStressResetMode);
  FchParams->HwAcpi.NoClearThermalTripSts = PcdGetBool (PcdNoClearThermalTripSts);
  FchParams->HwAcpi.FchAoacProgramEnable  = PcdGetBool (PcdFchAoacInitEnable);
  FchParams->HwAcpi.OemProgrammingTablePtr     = PcdGetPtr (PcdOemProgrammingTablePtr);
  FchParams->Gpp.SerialDebugBusEnable     = PcdGetBool (PcdSerialDebugBusEnable);
  FchParams->Gcpu.TimerTickTrack          = PcdGet8 (PcdTimerTickTrack);
  FchParams->Gcpu.ClockInterruptTag       = PcdGet8 (PcdClockInterruptTag);
  FchParams->Misc.BpX48M0OutputEnable     = PcdGetBool (PcdBpX48M0OutputEnable);
  FchParams->Misc.BpX48M0S0i3Enable       = PcdGetBool (BpX48M0S0i3Enable);
  FchParams->Misc.NativePcieSupport       = PcdGetBool (PcdNativePcieSupport);
  FchParams->Misc.UsbDbgclkEn             = PcdGetBool (PcdUsbDbgclkEn);
  FchParams->Misc.FchCsSupport.FchModernStandby          = PcdGetBool (PcdFchMiscModernStanbyEnable);

//  FchParams->Sd.SdConfig                  = PcdGet8 (PcdSdConfig);
//  FchParams->Sd.SdClockMultiplier         = PcdGetBool (PcdSdClockMultiplier);
//  FchParams->Sd.SdDbgConfig               = PcdGet8 (PcdSdDbgConfig);

  FchParams->Emmc.EmmcEnable              = PcdGet8 (PcdEmmcEnable);
  FchParams->Emmc.EmmcDriverType          = PcdGet8 (PcdEmmcDriverType);
  FchParams->Emmc.EmmcBoot                = PcdGetBool (PcdEmmcBoot);
  FchParams->Emmc.EmmcAdma2Support        = PcdGetBool (PcdEmmcAdma2Support);
  FchParams->Emmc.EmmcAdmaSupport         = PcdGetBool (PcdEmmcAdmaSupport);
  FchParams->Emmc.EmmcSdmaSupport         = PcdGetBool (PcdEmmcSdmaSupport);
  FchParams->Emmc.EmmcA64bSupport         = PcdGetBool (PcdEmmcA64bSupport);
  FchParams->Emmc.EmmcD3Support           = PcdGetBool (PcdEmmcD3Support);

  FchParams->Xgbe.XgbeMdio0Enable         = PcdGetBool (PcdXgbeMdio0);
  FchParams->Xgbe.XgbeMdio1Enable         = PcdGetBool (PcdXgbeMdio1);
  FchParams->Xgbe.XgbeSfpEnable           = PcdGetBool (PcdXgbeSfp);
  FchParams->Xgbe.Port[0].XgbePortConfig  = PcdGetBool (PcdXgbePort0ConfigEn);
  if (FchParams->Xgbe.Port[0].XgbePortConfig) {
    PcdDataPtr = PcdGetPtr (PcdXgbePort0Table);
    gBS->CopyMem (
           &FchParams->Xgbe.Port[0],
           PcdDataPtr,
           sizeof (FCH_XGBE_PORT)
           );
  }
  FchParams->Xgbe.Port[0].XgbePortConfig  = PcdGetBool (PcdXgbePort0ConfigEn);
  FchParams->Xgbe.Mac[0].XgbePortMacAddressLow  = (UINT32) PcdGet64 (PcdXgbePort0MAC);
  FchParams->Xgbe.Mac[0].XgbePortMacAddressHigh = (UINT32) RShiftU64 (PcdGet64 (PcdXgbePort0MAC), 32);

  FchParams->Xgbe.Port[1].XgbePortConfig  = PcdGetBool (PcdXgbePort1ConfigEn);
  if (FchParams->Xgbe.Port[1].XgbePortConfig) {
    PcdDataPtr = PcdGetPtr (PcdXgbePort1Table);
    gBS->CopyMem (
           &FchParams->Xgbe.Port[1],
           PcdDataPtr,
           sizeof (FCH_XGBE_PORT)
           );
  }
  FchParams->Xgbe.Port[1].XgbePortConfig  = PcdGetBool (PcdXgbePort1ConfigEn);
  FchParams->Xgbe.Mac[1].XgbePortMacAddressLow  = (UINT32) PcdGet64 (PcdXgbePort1MAC);
  FchParams->Xgbe.Mac[1].XgbePortMacAddressHigh = (UINT32) RShiftU64 (PcdGet64 (PcdXgbePort1MAC), 32);

  FchParams->Xgbe.Port[2].XgbePortConfig  = PcdGetBool (PcdXgbePort2ConfigEn);
  if (FchParams->Xgbe.Port[2].XgbePortConfig) {
    PcdDataPtr = PcdGetPtr (PcdXgbePort2Table);
    gBS->CopyMem (
           &FchParams->Xgbe.Port[2],
           PcdDataPtr,
           sizeof (FCH_XGBE_PORT)
           );
  }
  FchParams->Xgbe.Port[2].XgbePortConfig  = PcdGetBool (PcdXgbePort2ConfigEn);
  FchParams->Xgbe.Mac[2].XgbePortMacAddressLow  = (UINT32) PcdGet64 (PcdXgbePort2MAC);
  FchParams->Xgbe.Mac[2].XgbePortMacAddressHigh = (UINT32) RShiftU64 (PcdGet64 (PcdXgbePort2MAC), 32);

  FchParams->Xgbe.Port[3].XgbePortConfig  = PcdGetBool (PcdXgbePort3ConfigEn);
  if (FchParams->Xgbe.Port[3].XgbePortConfig) {
    PcdDataPtr = PcdGetPtr (PcdXgbePort3Table);
    gBS->CopyMem (
           &FchParams->Xgbe.Port[3],
           PcdDataPtr,
           sizeof (FCH_XGBE_PORT)
           );
  }
  FchParams->Xgbe.Port[3].XgbePortConfig  = PcdGetBool (PcdXgbePort3ConfigEn);
  FchParams->Xgbe.Mac[3].XgbePortMacAddressLow  = (UINT32) PcdGet64 (PcdXgbePort3MAC);
  FchParams->Xgbe.Mac[3].XgbePortMacAddressHigh = (UINT32) RShiftU64 (PcdGet64 (PcdXgbePort3MAC), 32);

  FchParams->FchRunTime.FchDeviceEnableMap = PcdGet32 (FchRTDeviceEnableMap);
  if (FchParams->FchRunTime.FchDeviceEnableMap & BIT11) {
    UartLegacy[0] = PcdGet8 (FchUart0LegacyEnable);
  } else {
    UartLegacy[0] = 0;
  }
  if (FchParams->FchRunTime.FchDeviceEnableMap & BIT12) {
    UartLegacy[1] = PcdGet8 (FchUart1LegacyEnable);
  } else {
    UartLegacy[1] = 0;
  }
  if (FchParams->FchRunTime.FchDeviceEnableMap & BIT16) {
    UartLegacy[2] = PcdGet8 (FchUart2LegacyEnable);
  } else {
    UartLegacy[2] = 0;
  }
  if (FchParams->FchRunTime.FchDeviceEnableMap & BIT26) {
    UartLegacy[3] = PcdGet8 (FchUart3LegacyEnable);
  } else {
    UartLegacy[3] = 0;
  }

  IoEnable16 = 0;
  for (UartChannel = 0; UartChannel < 4; UartChannel++ ) {
    if (UartLegacy[UartChannel]) {
      IoEnable16 |= (BIT0 << (UartLegacy[UartChannel] - 1)) + (BIT4 << UartChannel) + (UartChannel << (8 + ((UartLegacy[UartChannel] - 1) * 2)));
    }
  }
  FchParams->FchRunTime.Al2AhbLegacyUartIoEnable = IoEnable16;
  FchParams->FchRunTime.FchDeviceD3ColdMap = PcdGet32 (FchRTD3ColdEnableMap);
  //PLAT-37310
  if (PcdGetBool (PcdAgesaTestPointEnable)) {
    FchParams->FchRunTime.FchDeviceEnableMap |= BIT1;
  } else {
    FchParams->FchRunTime.FchDeviceEnableMap &= ~ BIT1;
  }

  FchParams->Smbus.SmbusSsid              = PcdGet32 (PcdSmbusSsid);
  FchParams->Sata.SataAhciSsid            = PcdGet32 (PcdSataAhciSsid);
  FchParams->Sata.SataIdeSsid             = PcdGet32 (PcdSataIdeSsid);
  FchParams->Sata.SataRaid5Ssid           = PcdGet32 (PcdSataRaid5Ssid);
  FchParams->Sata.SataRaidSsid            = PcdGet32 (PcdSataRaidSsid);
  FchParams->Spi.LpcSsid                  = PcdGet32 (PcdLpcSsid);
  FchParams->Sd.SdSsid                    = PcdGet32 (PcdSdSsid);
  FchParams->Usb.XhciSsid                 = PcdGet32 (PcdXhciSsid);

  //Set EMMC runtime enable bit 28
  if (FchParams->Emmc.EmmcEnable) {
    FchParams->FchRunTime.FchDeviceEnableMap |= BIT28;
  }

  //Set Runtime Spi enable bit 0
  if (PcdGetBool (PcdSpiConfig)) {
    FchParams->FchRunTime.FchDeviceEnableMap |= BIT0;
  }

  //<Embedded_Override_Start>
  //Set Runtime Spi enable bit 2
  if (PcdGetBool (PcdSpiCustomConfig)) {
    FchParams->FchRunTime.FchDeviceEnableMap |= BIT2;
  }
  //<Embedded_Override_End>
  
  //Update bit 29 for AMD UART Driver/AMD Serial Driver 
  if (PcdGet8 (FchUartDriverType) == 1) {
    FchParams->FchRunTime.FchDeviceEnableMap &= ~BIT29;
  } else {
    FchParams->FchRunTime.FchDeviceEnableMap |= BIT29;
  }
  
  FchParams->FchRunTime.PcieMmioBase       = (UINT32) PcdGet64 (PcdPciExpressBaseAddress);
  FchParams->HwAcpi.FchSxEntryXhciPmeEn    = PcdGetBool (PcdFchSxEntryXhciPmeEnWA);

  return FchParams;
}

//
// Driver Global Data
//

/*********************************************************************************
 * Name: FchDxeInit
 *
 * Description
 *   Entry point of the AMD FCH DXE driver
 *   Perform the configuration init, resource reservation, early post init
 *   and install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
FchDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  FCH_DXE_PRIVATE     *FchPrivate;
  EFI_STATUS          Status;
  EFI_HANDLE          Handle;
  FCH_DATA_BLOCK      *FchDataBlock;
  EFI_EVENT           PciIoEvent;
  VOID                *Registration;

  AGESA_TESTPOINT (TpFchDxeEntry, NULL);
  //
  // Initialize EFI library
  //

  //
  // Initialize the configuration structure and private data area
  //
  // Allocate memory for the private data
  Status = gBS->AllocatePool (
                  EfiACPIMemoryNVS,
                  sizeof (FCH_DXE_PRIVATE),
                  &FchPrivate
                  );

  ASSERT_EFI_ERROR (Status);

  Status = gBS->AllocatePool (
                  EfiACPIMemoryNVS,
                  sizeof (FCH_DATA_BLOCK),
                  &FchDataBlock
                  );

  ASSERT_EFI_ERROR (Status);

  FchDataBlock = FchInitDataBlock (FchDataBlock);
  // Initialize the private data structure
  FchPrivate->Signature = FCH_DXE_PRIVATE_DATA_SIGNATURE;
  // Initialize the FCHInit protocol
  FchPrivate->FchInit.Revision             = FCH_INIT_REV;
  FchPrivate->FchInit.FchRev               = FCH_VERSION;
  FchPrivate->FchInit.FchPolicy            = (VOID*) FchDataBlock;
  FchPrivate->FchInit.FchPtPolicy          = (VOID*) &(FchDataBlock->Promontory);
  FchPrivate->FchInit.FpUsbPortDisable2    = FchUsbDisablePort;
  FchPrivate->FchInit.FpUsbOverCurrent2    = FchUsbOvercurrentControl;

  //
  // Publish the FCHInit protocol
  //
  Handle = ImageHandle;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gFchInitProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &FchPrivate->FchInit
                  );

  if (EFI_ERROR (Status)) {
    return (Status);
  }

  //
  // Enviroment Init Entry
  //
  DEBUG ((DEBUG_INFO, "[FchInitEnv] Fch Init - Before PCI Scan ...Start\n"));
  Status = FchInitEnv (FchDataBlock);
  DEBUG ((DEBUG_INFO, "[FchInitPei] Fch Init - Before PCI Scan ...complete\n"));

  //
  // Register the event handling function for FchInitMid to be launched after
  // PciIo protocol
  //
  Status = gBS->CreateEventEx (
             EVT_NOTIFY_SIGNAL,
             TPL_NOTIFY,
             InvokeFchInitMid,
             FchPrivate->FchInit.FchPolicy,
             NULL,
             &PciIoEvent
             );

  Status = gBS->RegisterProtocolNotify (
              &gEfiPciIoProtocolGuid,
              PciIoEvent,
              &Registration
              );

  //
  // Register the event handling function for FchInitLate to be launched after
  // Ready to Boot
  //
  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             InvokeFchInitLate,
             FchPrivate->FchInit.FchPolicy,
             &FchPrivate->EventReadyToBoot
             );

  //
  // Install gFchInitDonePolicyProtocolGuid to signal Platform
  //
  Handle = ImageHandle;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gFchInitDonePolicyProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );

  AGESA_TESTPOINT (TpFchDxeExit, NULL);
  return (Status);
}

EFI_STATUS
EFIAPI
FchUsbDisablePort (
  IN       CONST FCH_INIT_PROTOCOL   *This,
  IN       UINT8                     Socket,
  IN       UINT32                    USB3DisableMap,
  IN       UINT32                    USB2DisableMap
  )
{
  UINT32   Xhci0USB3DisableMap;
  UINT32   Xhci0USB2DisableMap;
  UINT32   Xhci1USB3DisableMap;
  UINT32   Xhci1USB2DisableMap;

  Xhci0USB3DisableMap = USB3DisableMap & 0x0F;          //bit0-3: controller0 port0-3
  Xhci0USB2DisableMap = USB2DisableMap & 0x0F;          //bit0-3: controller0 port0-3
  Xhci1USB3DisableMap = (USB3DisableMap >> 4) & 0x01;   //bit4:   controller1 port0
  Xhci1USB2DisableMap = (USB2DisableMap >> 4) & 0x03;   //bit4/5: controller0 port0/1

  if (FchRVXhci0DisablePort (Xhci0USB3DisableMap, Xhci0USB2DisableMap)) {
    if (FchRVXhci1DisablePort (Xhci1USB3DisableMap, Xhci1USB2DisableMap)) {
      return EFI_SUCCESS;
    } else {
      return EFI_UNSUPPORTED;
    }
  } else {
    return EFI_UNSUPPORTED;
  }
}

EFI_STATUS
EFIAPI
FchUsbOvercurrentControl (
  IN       CONST FCH_INIT_PROTOCOL   *This,
  IN       UINT8                     Socket,
  IN       UINT8                     Port,
  IN       UINT8                     OCPin
  )
{
  if (Port < 4) {
    // Port0-3 : Xhci0
    if (FchRV0Xhci0OCmapping (Port, OCPin)) {
      return EFI_SUCCESS;
    } else {
      return EFI_UNSUPPORTED;
    }
  } else {
    // Port4-5 : Xhci1
    if (FchRV0Xhci1OCmapping (Port - 4, OCPin)) {
      return EFI_SUCCESS;
    } else {
      return EFI_UNSUPPORTED;
    }
  }
}


