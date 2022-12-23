//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file TaishanPcdsLib.c
    This file contains code for TaishanPcdsLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

// AMI Header
#include <Token.h>
#include <Sb.h>
#include <Library/SbPolicy.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#define SB_SD_AUTO    0xFF

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
  The constructor function initialize the TaishanPcdsLib Library

  @param  IsPei         check caller is in pei.

  @retval EFI_SUCCESS   returns EFI_SUCCESS.

**/

EFI_STATUS
EFIAPI
UpdateTaishanPcds (
  IN  BOOLEAN    IsPei
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    CHAR16                  	*FchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);

    // Check Hardware Identification
    if (StrCmp(L"Taishan", FchTypeStr) == 0) {
        SB_SETUP_DATA               SbSetupData;

        //
        // Get SETUP DATA parameters
        //
        GetSbSetupData(NULL, &SbSetupData, IsPei);

        if (!SbSetupData.AmdSafeDefault) {

            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"<< SB AmiFchInitHookLib UPDATE Taishan PCDs >>\n"));

            //========================================
            //
            //    Taishan
            //
            //========================================

            //Dynamic PCDs
            if (IsPei) {
                //#### AVA9 : PI0060 AutoMode is unused. check AMD later ###if (SbSetupData.SpiAutoMode != SB_SD_AUTO) PcdSet8S( PcdResetAutoMode, SbSetupData.SpiAutoMode);//|0x00|UINT8|0x0003F00E
                //### TBD ###PcdSet8S( PcdResetWriteSpeed, SbSetupData);//|0x03|UINT8|0x0003F00C
                //### TBD ###PcdSet8S( PcdResetCg2Pll, SbSetupData);//|0x00|UINT8|0x0003F010
                if (SbSetupData.SpiFastSpeed != SB_SD_AUTO) PcdSet8S( PcdResetFastSpeed, SbSetupData.SpiFastSpeed);//|0x00|UINT8|0x0003F00B
                if (SbSetupData.SpiMode != SB_SD_AUTO) PcdSet8S( PcdResetMode, SbSetupData.SpiMode);//|0x00|UINT8|0x0003F00D
                if (SbSetupData.SpiBurstWrite != SB_SD_AUTO) PcdSet8S( PcdResetBurstWrite, SbSetupData.SpiBurstWrite);//|0x00|UINT8|0x0003F00F
                if (SbSetupData.SpiSpeed != SB_SD_AUTO) PcdSet8S( PcdResetSpiSpeed, SbSetupData.SpiSpeed);//|0x02|UINT8|0x0003F011
                if (SbSetupData.SPI100_Enable != SB_SD_AUTO) PcdSet8S( PcdResetSPI100Enable, SbSetupData.SPI100_Enable);//|0x01|UINT8|0x0003F012
            }

            //### AMI SETUP ###PcdSet8S (PcdAbClockGating, SbSetupData.Ab.AbClockGating);
            //### NO SETUP ###PcdSet8S (PcdALinkClkGateOff, SbSetupData.Ab.ALinkClkGateOff);
            //### NO SETUP ###PcdSet8S (PcdBLinkClkGateOff, SbSetupData.Ab.BLinkClkGateOff);
            //### NO SETUP ###PcdSetBoolS (PcdSbgMemoryPowerSaving, SbSetupData.Ab.SbgMemoryPowerSaving);
            //### NO SETUP ###PcdSetBoolS (PcdSbgClockGating, SbSetupData.Ab.SbgClockGating);
            //### NO SETUP ###PcdSetBoolS (PcdXdmaDmaWrite16ByteMode, SbSetupData.Ab.XdmaDmaWrite16ByteMode);
            //### NO SETUP ###PcdSetBoolS (PcdXdmaMemoryPowerSaving, SbSetupData.Ab.XdmaMemoryPowerSaving);
            //### NO SETUP ###PcdSet8S (PcdXdmaPendingNprThreshold, SbSetupData.Ab.XdmaPendingNprThreshold);
            //### NO SETUP ###PcdSetBoolS (PcdXdmaDncplOrderDis, SbSetupData.Ab.XdmaDncplOrderDis);
            //### NO SETUP ###PcdSet8S (PcdGppClockRequest0, SbSetupData.Ab.GppClockRequest0);
            //### NO SETUP ###PcdSet8S (PcdGppClockRequest1, SbSetupData.Ab.GppClockRequest1);
            //### NO SETUP ###PcdSet8S (PcdGppClockRequest2, SbSetupData.Ab.GppClockRequest2);
            //### NO SETUP ###PcdSet8S (PcdGppClockRequest3, SbSetupData.Ab.GppClockRequest3);
            //### NO SETUP ###PcdSet8S (PcdSltGfxClockRequest0, SbSetupData.Ab.SltGfxClockRequest0);
            //### NO SETUP ###PcdSet8S (PcdSltGfxClockRequest1, SbSetupData.Ab.SltGfxClockRequest1);
            //### NO SETUP ###PcdSetBoolS (PcdSdphostBypassDataPack, SbSetupData.Ab.SdphostBypassDataPack);
            //### NO SETUP ###PcdSetBoolS (PcdSdphostDisNpmwrProtect, SbSetupData.Ab.SdphostDisNpmwrProtect);

            //### by CBS ###PcdSet8S (PcdSataClass, SbSetupData.Sata.SataClass);
			if (SbSetupData.SataAggrLinkPmCap != SB_SD_AUTO) PcdSet8S( PcdSataAggrLinkPmCap, SbSetupData.SataAggrLinkPmCap);//|0x01|UINT8|0x0003F108
			if (SbSetupData.SataPortMultCap != SB_SD_AUTO) PcdSet8S( PcdSataPortMultCap, SbSetupData.SataPortMultCap);//|0x01|UINT8|0x0003F109
			if (SbSetupData.SataClkAutoOff != SB_SD_AUTO) PcdSet8S( PcdSataClkAutoOff, SbSetupData.SataClkAutoOff);//|0x01|UINT8|0x0003F10A
			if (SbSetupData.SataPscCap != SB_SD_AUTO) PcdSet8S( PcdSataPscCap, SbSetupData.SataPscCap);//|0x01|UINT8|0x0003F10B
			if (SbSetupData.SataSscCap != SB_SD_AUTO) PcdSet8S( PcdSataSscCap, SbSetupData.SataSscCap);//|0x01|UINT8|0x0003F10C
			if (SbSetupData.SataFisBasedSwitching != SB_SD_AUTO) PcdSet8S( PcdSataFisBasedSwitching, SbSetupData.SataFisBasedSwitching);//|0x01|UINT8|0x0003F10E
			if (SbSetupData.SataCccSupport != SB_SD_AUTO) PcdSet8S( PcdSataCccSupport, SbSetupData.SataCccSupport);//|0x00|UINT8|0x0003F10F
			if (SbSetupData.SataMsiCapability != SB_SD_AUTO) PcdSet8S( PcdSataMsiCapability, SbSetupData.SataMsiCapability);//|0x00|UINT8|0x0003F110
			if (SbSetupData.SataTargetSupport8Device != SB_SD_AUTO) PcdSet8S (PcdSataTargetSupport8Device, SbSetupData.SataTargetSupport8Device);//|0x00|UINT8|0x0003F111
			if (SbSetupData.SataAhciEnclosureManagement != SB_SD_AUTO) PcdSet8S( PcdSataAhciEnclosureManagement, SbSetupData.SataAhciEnclosureManagement);//|0x00|UINT8|0x0003F112
			if (SbSetupData.SataDisableGenericMode != SB_SD_AUTO) PcdSet8S( PcdSataDisableGenericMode, SbSetupData.SataDisableGenericMode);//|0x00|UINT8|0x0003F113
			if (SbSetupData.SataPhyPllShutDown != SB_SD_AUTO) PcdSet8S( PcdSataPhyPllShutDown, SbSetupData.SataPhyPllShutDown);//|0x00|UINT8|0x0003F114


            if (SbSetupData.SataPortMode0 != SB_SD_AUTO) PcdSet8S (PcdSataModePort0, SbSetupData.SataPortMode0);
            if (SbSetupData.SataPortMode1 != SB_SD_AUTO) PcdSet8S (PcdSataModePort1, SbSetupData.SataPortMode1);
            if (SbSetupData.SataPortMode2 != SB_SD_AUTO) PcdSet8S (PcdSataModePort2, SbSetupData.SataPortMode2);
            if (SbSetupData.SataPortMode3 != SB_SD_AUTO) PcdSet8S (PcdSataModePort3, SbSetupData.SataPortMode3);
            if (SbSetupData.SataPortMode4 != SB_SD_AUTO) PcdSet8S (PcdSataModePort4, SbSetupData.SataPortMode4);
            if (SbSetupData.SataPortMode5 != SB_SD_AUTO) PcdSet8S (PcdSataModePort5, SbSetupData.SataPortMode5);
            if (SbSetupData.SataPortMode6 != SB_SD_AUTO) PcdSet8S (PcdSataModePort6, SbSetupData.SataPortMode6);
            if (SbSetupData.SataPortMode7 != SB_SD_AUTO) PcdSet8S (PcdSataModePort7, SbSetupData.SataPortMode7);
            if (SbSetupData.SataEspPort0 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort0, SbSetupData.SataEspPort0);
            if (SbSetupData.SataEspPort1 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort1, SbSetupData.SataEspPort1);
            if (SbSetupData.SataEspPort2 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort2, SbSetupData.SataEspPort2);
            if (SbSetupData.SataEspPort3 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort3, SbSetupData.SataEspPort3);
            if (SbSetupData.SataEspPort4 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort4, SbSetupData.SataEspPort4);
            if (SbSetupData.SataEspPort5 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort5, SbSetupData.SataEspPort5);
            if (SbSetupData.SataEspPort6 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort6, SbSetupData.SataEspPort6);
            if (SbSetupData.SataEspPort7 != SB_SD_AUTO) PcdSet8S (PcdSataEspPort7, SbSetupData.SataEspPort7);

			if (SbSetupData.SataPower0 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort0, SbSetupData.SataPower0);
			if (SbSetupData.SataPower1 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort1, SbSetupData.SataPower1);
			if (SbSetupData.SataPower2 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort2, SbSetupData.SataPower2);
			if (SbSetupData.SataPower3 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort3, SbSetupData.SataPower3);
			if (SbSetupData.SataPower4 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort4, SbSetupData.SataPower4);
			if (SbSetupData.SataPower5 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort5, SbSetupData.SataPower5);
			if (SbSetupData.SataPower6 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort6, SbSetupData.SataPower6);
			if (SbSetupData.SataPower7 != SB_SD_AUTO) PcdSet8S (PcdSataPortPowerPort7, SbSetupData.SataPower7);

			if (SbSetupData.SataHotRemoveEnh != SB_SD_AUTO) PcdSet8S (PcdSataHotRemovalEnhPort, SbSetupData.SataHotRemoveEnh);

            if (SbSetupData.SataTargetSupport8Device != SB_SD_AUTO) PcdSet8S (PcdSataTargetSupport8Device, SbSetupData.SataTargetSupport8Device);
            if (SbSetupData.SataAhciEnclosureManagement != SB_SD_AUTO) PcdSet8S (PcdSataAhciEnclosureManagement, SbSetupData.SataAhciEnclosureManagement);
            //### NO SETUP ###PcdSetBoolS (PcdSataMsiEnable, SbSetupData.Sata.SataMsiEnable);
            //### by CBS ###PcdSetBoolS (PcdSataRasSupport, SbSetupData.Sata.SataRasSupport);
            //### by CBS ###PcdSetBoolS (PcdSataAhciDisPrefetchFunction, SbSetupData.Sata.SataAhciDisPrefetchFunction);
            //### by CBS ###PcdSetBoolS (PcdSataDevSlpPort0, SbSetupData.Sata.SataDevSlpPort0);
            //### by CBS ###PcdSetBoolS (PcdSataDevSlpPort1, SbSetupData.Sata.SataDevSlpPort1);
            //### by CBS ###PcdSet8S (PcdSataDevSlpPort0Num, SbSetupData.Sata.SataDevSlpPort0Num);
            //### by CBS ###PcdSet8S (PcdSataDevSlpPort1Num, SbSetupData.Sata.SataDevSlpPort1Num);

            if (SbSetupData.HpetTimer != SB_SD_AUTO) PcdSetBoolS (PcdHpetEnable, SbSetupData.HpetTimer);
            if (SbSetupData.HpetMsiDis != SB_SD_AUTO) PcdSetBoolS (PcdHpetMsiDis, SbSetupData.HpetMsiDis);
            //SbSetupData.Hpet.HpetBase                = 0xFED00000;

            if (SbSetupData.SpreadSpectrum != SB_SD_AUTO) PcdSetBoolS (PcdSpreadSpectrum, SbSetupData.SpreadSpectrum);
            //SbSetupData.HwAcpi.WatchDogTimerBase     = 0xFEB00000;
            //### by CBS ###PcdSet8S (PcdPwrFailShadow, SbSetupData.HwAcpi.PwrFailShadow);
            //### NO SETUP ###PcdSet8S (PcdStressResetMode, SbSetupData.HwAcpi.StressResetMode);
            //### NO SETUP ###PcdSetBoolS (PcdNoClearThermalTripSts, SbSetupData.HwAcpi.NoClearThermalTripSts);
            if (SbSetupData.SdbEnable != SB_SD_AUTO) PcdSetBoolS (PcdSerialDebugBusEnable, SbSetupData.SdbEnable);
            //### NO SETUP ###PcdSet8S (PcdTimerTickTrack, SbSetupData.Gcpu.TimerTickTrack);
            //### NO SETUP ###PcdSet8S (PcdClockInterruptTag, SbSetupData.Gcpu.ClockInterruptTag);

            //### by CBS ###PcdSet8S (PcdSdConfig, SbSetupData.Sd.SdConfig);
            //### AMI SETUP ###PcdSetBoolS (PcdSdClockMultiplier, SbSetupData.Sd.SdClockMultiplier);
            //### NO SETUP ###PcdSet8S (PcdSdDbgConfig, SbSetupData.Sd.SdDbgConfig);

            //### NO SETUP ###PcdSetBoolS (PcdEmmcEnable, SbSetupData.Emmc.EmmcEnable);
            //### NO SETUP ###PcdSet8S (PcdEmmcBusSpeedMode, SbSetupData.Emmc.BusSpeedMode);
            //### NO SETUP ###PcdSet8S (PcdEmmcBusWidth, SbSetupData.Emmc.BusWidth);
            //### NO SETUP ###PcdSet8S (PcdEmmcRetuneMode, SbSetupData.Emmc.RetuneMode);
            //### NO SETUP ###PcdSetBoolS (PcdEmmcClockMultiplier, SbSetupData.Emmc.ClockMultiplier);

			if (SbSetupData.GpioAcpiEnabled != SB_SD_AUTO) {
				SB_DEVENMAP		FchDevEnMap;
				FchDevEnMap.FchDeviceEnableMap = 0;
				FchDevEnMap.GIOE = SbSetupData.GpioAcpiEnabled;
				//==================================
				//Chipset-> South Bridge->  I2C Configuration
				//==================================
				FchDevEnMap.IC0E = SbSetupData.I2C0Enable;
				FchDevEnMap.IC1E = SbSetupData.I2C1Enable;
				FchDevEnMap.IC2E = SbSetupData.I2C2Enable;
				FchDevEnMap.IC3E = SbSetupData.I2C3Enable;

				//==================================
				//Chipset-> South Bridge->  UART Configuration
				//==================================
				FchDevEnMap.UT0E = SbSetupData.Uart0Enable;
				FchDevEnMap.UT1E = SbSetupData.Uart1Enable;
				PcdSet32S(FchRTDeviceEnableMap, FchDevEnMap.FchDeviceEnableMap);
			}
			//### AMD PI0060 NO PCD ###{
			//### AMD PI0060 NO PCD ###	SB_DEVD3MAP		FchDevD3Map;
			//### AMD PI0060 NO PCD ###	FchDevD3Map.FchDeviceD3ColdMap = PcdGet32(FchRTDeviceD3ColdMap);
			//### AMD PI0060 NO PCD ###	if (SbSetupData.I2C0D3 != SB_SD_AUTO) FchDevD3Map.IC0D = SbSetupData.I2C0D3;
			//### AMD PI0060 NO PCD ###	if (SbSetupData.I2C1D3 != SB_SD_AUTO) FchDevD3Map.IC1D = SbSetupData.I2C1D3;
			//### AMD PI0060 NO PCD ###	if (SbSetupData.I2C2D3 != SB_SD_AUTO) FchDevD3Map.IC2D = SbSetupData.I2C2D3;
			//### AMD PI0060 NO PCD ###	if (SbSetupData.I2C3D3 != SB_SD_AUTO) FchDevD3Map.IC3D = SbSetupData.I2C3D3;
            //### AMD PI0060 NO PCD ###
			//### AMD PI0060 NO PCD ###	if (SbSetupData.UART0D3 != SB_SD_AUTO) FchDevD3Map.UT0D = SbSetupData.UART0D3;
			//### AMD PI0060 NO PCD ###	if (SbSetupData.UART1D3 != SB_SD_AUTO) FchDevD3Map.UT1D = SbSetupData.UART1D3;
            //### AMD PI0060 NO PCD ###
			//### AMD PI0060 NO PCD ###	if (SbSetupData.SATAD3 != SB_SD_AUTO) FchDevD3Map.ST_D = SbSetupData.SATAD3; //SATA
			//### AMD PI0060 NO PCD ###	if (SbSetupData.EHCID3 != SB_SD_AUTO) FchDevD3Map.EHCD = SbSetupData.EHCID3; //EHCI
			//### AMD PI0060 NO PCD ###	if (SbSetupData.XHCID3 != SB_SD_AUTO) FchDevD3Map.XHCD = SbSetupData.XHCID3; //XHCI
			//### AMD PI0060 NO PCD ###	if (SbSetupData.SDD3 != SB_SD_AUTO) FchDevD3Map.SD_D = SbSetupData.SDD3;   //SD controller
			//### AMD PI0060 NO PCD ###	if (SbSetupData.S0I3 != SB_SD_AUTO) FchDevD3Map.S03D = SbSetupData.S0I3;   //S0I3 flag
            //### AMD PI0060 NO PCD ###
			//### AMD PI0060 NO PCD ###	PcdSet32S(FchRTDeviceD3ColdMap, FchDevD3Map.FchDeviceD3ColdMap);
			//### AMD PI0060 NO PCD ###}
        } else Status = EFI_NOT_READY;
    }

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
