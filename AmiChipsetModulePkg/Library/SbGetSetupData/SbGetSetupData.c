//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//**********************************************************************
/** @file SbGetSetupData.c
    Custom South Bridge setup data behavior implementation

**/
//**********************************************************************
//#include <PiPei.h>
//#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Token.h>
#include <Setup.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <SbElinks.h>

#include <Sb.h>
#include <Library/SbPolicy.h>

#include <AmiLib.h>
#include <AmiDxeLib.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

VOID SbSetupCallbacks (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

EFI_STATUS
EFIAPI
SbSetupVar (
  IN OUT SETUP_DATA        *SetupData
  );

VOID*
EFIAPI
SbGetService (
  VOID
  );

typedef VOID (SB_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);

// External Declaration(s)

extern SB_OEM_SETUP_CALLBACK SB_OEM_SETUP_CALLBACK_LIST EndOfList;
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)


// GUID Definition(s)

static EFI_GUID gSetupGuid = SETUP_GUID;

// Protocol/Ppi Definition(s)



// Function Definition(s)
extern SB_OEM_SETUP_CALLBACK SB_OEM_SETUP_CALLBACK_LIST EndOfList;
SB_OEM_SETUP_CALLBACK* SbOemSetupCallbackList[] = { SB_OEM_SETUP_CALLBACK_LIST NULL };

//---------------------------------------------------------------------------

/**
    This function calls registered callbacks for OEM/custom setup.

    @param Services Pointer to PeiServices or RuntimeServices
        structure
    @param SbSetupData Pointer to custom setup data to return
    @param SetupData Pointer to system setup data.
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/

VOID SbOemSetupCallbacks (
    IN VOID              *Services,
    IN OUT SB_SETUP_DATA *SbSetupData,
    IN SETUP_DATA        *SetupData,
    IN BOOLEAN           Pei )
{
  UINTN                     i;

  for (i = 0; SbOemSetupCallbackList[i] != NULL; i++)
    SbOemSetupCallbackList[i]( Services, SbSetupData, SetupData, Pei);

}


/**
    This function returns custom setup data from system SetupData
    variable

    @param Services Pointer to PeiServices or RuntimeServices
        structure
    @param SbSetupData Pointer to custom setup data to return
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID

    @note  PORTING REQUIRED
**/
VOID GetSbSetupData (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN BOOLEAN              Pei )
{
    EFI_STATUS                      Status;
    SETUP_DATA                      SetupData, *TempSetupData = NULL;

    // We are able to separate the library class to different instance in EDKII.
    // So we don't need the "Service" and "Pei" parameter.
    // But we pass them to "SbOemSetupCallbacks" for backward compatible.
    // and we made SbSetupVar for different instance (PEI/DXE).
    Status = SbSetupVar(&SetupData);

    // Porting Start
    // Update SB_SETUP_DATA according to the default values.

    // To use AMD-CRB safe default if NVRAM invalid.
    SbSetupData->AmdSafeDefault = TRUE;

    //==================================
    // AMD parameters by token
    //==================================

    //==================================
    // AMI definition
    //==================================
    SbSetupData->SataSelRaid5  = 0;


    SbSetupData->Xhci0PortEn[0] = 1;
    SbSetupData->Xhci0PortEn[1] = 1;
    SbSetupData->Xhci0PortEn[2] = 1;
    SbSetupData->Xhci0PortEn[3] = 1;
    SbSetupData->Xhci0PortEn[4] = 1;  //Type2 - Flavor2
    SbSetupData->Xhci0PortEn[5] = 1;  //Type2 - Flavor2
    
    SbSetupData->Xhci1PortEn[0] = 1;
    SbSetupData->Xhci1PortEn[1] = 1;

    SbSetupData->TpmDecode = 0;

    //### PCD fix at build ###SbSetupData->FchDevEnMap.FchDeviceEnableMap = 0;
    //### PCD fix at build ###SbSetupData->FchDevD3Map.FchDeviceD3ColdMap = 0x7FFFFFFE;

    if (!EFI_ERROR(Status)) {
        TempSetupData = &SetupData;
    }
    SbOemSetupCallbacks( SbGetService(), SbSetupData, TempSetupData, Pei );
}

#if defined SB_SETUP_SUPPORT && SB_SETUP_SUPPORT == 1
/**
    This function returns SB Chipset setup data from system SetupData
    variable

    @param Services Pointer to PeiServices or RuntimeServices
    @param SbSetupData Pointer to custom setup data to return
    @param SetupData Pointer to system setup data.
    @param Pei Pei flag. If TRUE we are in PEI phase

    @retval VOID
**/
VOID SbSetupCallbacks (
  IN VOID              *Services,
  IN OUT SB_SETUP_DATA *SbSetupData,
  IN SETUP_DATA        *SetupData,
  IN BOOLEAN           Pei )
{
    #define CSP_AMD_SB_SETUP_MACRO(option) (SbSetupData->option = SetupData->option)
    CHAR16    *FchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);

    // check if it is not Sandstone just return.
    if (!(StrCmp(L"Sandstone", FchTypeStr) == 0)) return;

    if (SetupData != NULL) {
        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"<< SbSetupCallbacks UPDATE Sandstone SETUP DATA >>\n"));

        SbSetupData->AmdSafeDefault = FALSE;
        // Porting Start
        // Update SB_SETUP_DATA according to the setup datas.
        //==================================
        //Chipset-> South Bridge-> SATA Configuration
        //==================================
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SataController);              // RVA9 - Check later: No C file reference
                                                             // this parameter wasn't passed into Pcd
                                                             // AGESA use PcdSataEnable(SataEnable); CBS

        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SataClass);                   // this parameter wasn't passed into Pcd; DXE; CBS
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SataIdeMode);                 // RVA9 - Check later:
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SataIdeCombinedMode);         // RVA9 - Check later:

        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SataSelRaid5);                // RVA9 - Check later:
        //==================================
        //Chipset-> South Bridge-> USB Configuration
        //==================================
    #if (!CONTROL_ALL_USB_METHOD)                                 // (EIP53061+)
        SbSetupData->Xhci0PortEn[0] = SetupData->Xhci0PortEn0;
        SbSetupData->Xhci0PortEn[1] = SetupData->Xhci0PortEn1;
        SbSetupData->Xhci0PortEn[2] = SetupData->Xhci0PortEn2;
        SbSetupData->Xhci0PortEn[3] = SetupData->Xhci0PortEn3;
        
        SbSetupData->Xhci0PortEn[4] = SetupData->Xhci0PortEn4;
        SbSetupData->Xhci0PortEn[5] = SetupData->Xhci0PortEn5;
        
        SbSetupData->Xhci1PortEn[0] = SetupData->Xhci1PortEn0;
        SbSetupData->Xhci1PortEn[1] = SetupData->Xhci1PortEn1;
    #else
        CSP_AMD_SB_SETUP_MACRO(UsbAllEnable); // AMI's setup item
    #endif

        //==================================
        //Chipset-> South Bridge-> IR Configuration
        //==================================
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(IrConfig); // RVA9 - Check later:

        //==================================
        //Chipset-> South Bridge->  SD(Secure Digital) Configuration
        //==================================
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(SdConfig); // DXE
        //### AMD0060 NO PCD ###SbSetupData->Sd.SdClockControl = (UINT32)SetupData->SdClockControl;
        //### AMD0060 NO PCD ###SbSetupData->Sd.SdSpeed = SetupData->SdSpeed; // AMD default 0 ?????
        //### AMD0060 NO PCD ###SbSetupData->Sd.SdBitWidth = SetupData->SdBitwidth; //  AMD default 0 ?????
        //### AMD0060 NO PCD ###SbSetupData->Sd.SdHostControllerVersion = SetupData->SdHostControllerVersion;
        //### AMD0060 NO PCD ###SbSetupData->Sd.SdForce18 = SetupData->SdForce18;
        //### PCD NO USE ###SbSetupData->Sd.SdDbgConfig = SetupData->SdDbgConfig;


        //### AMD0060 PCD-FchRTDeviceEnableMap. Fix at build ###
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(GpioAcpiEnabled); 
		//==================================
		//Chipset-> South Bridge->  I2C Configuration
		//==================================
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(I2C0Enable); 
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(I2C1Enable); 
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(I2C2Enable); 
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(I2C3Enable); 

		//==================================
		//Chipset-> South Bridge->  UART Configuration
		//==================================
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(Uart0Enable); 
        //### by CBS ###CSP_AMD_SB_SETUP_MACRO(Uart1Enable); 

        //==================================
        //Chipset-> South Bridge-> Power Saving
        //==================================
//#####if SB_POWER_SAVING_SUPPORT
        //### AMD0060 NO PCD ###SbSetupData->Ab.GppClockGating = SetupData->GppClockGating;
        CSP_AMD_SB_SETUP_MACRO(AbClockGating); // DXE
        //### AMD0060 NO PCD ###SbSetupData->Pcib.PcibClockRun = SetupData->PcibClockRun;
//#####endif

        //### AMD0060 NO PCD ###SbSetupData->Ab.PcieOrderRule = SetupData->SbPcieOrderRule;
        //### AMD0060 NO PCD ###SbSetupData->Ab.UmiL1TimerOverride = SetupData->L1TimerOverwrite;
        //### AMD0060 NO PCD ###SbSetupData->Ab.UmiGppTxDriverStrength = SetupData->SbAlinkGppTxDriverStrength;

        //==================================
        //Chipset-> South Bridge-> SATA Debug Configuration
        //==================================

        //###SbSetupData->Sata.SataEspPort.SataPortReg = 0;
        CSP_AMD_SB_SETUP_MACRO(SataEspPort0); // DXE
        CSP_AMD_SB_SETUP_MACRO(SataEspPort1); // DXE
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort2); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort3); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort4); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort5); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort6); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataEspPort7); // No reference

        //####SbSetupData->Sata.SataPortPower.SataPortReg = 0;
        CSP_AMD_SB_SETUP_MACRO(SataPower0); // DXE
        CSP_AMD_SB_SETUP_MACRO(SataPower1); // DXE
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower2); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower3); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower4); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower5); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower6); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPower7); // No reference

        //####SbSetupData->Sata.SataPortMd.SataPortMode = 0;
        CSP_AMD_SB_SETUP_MACRO(SataPortMode0); // DXE
        CSP_AMD_SB_SETUP_MACRO(SataPortMode1); // DXE
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode2); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode3); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode4); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode5); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode6); // No reference
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(SataPortMode7); // No reference

        //### AMD0060 NO PCD ###SbSetupData->Sata.SataHotRemovalEnh = SetupData->SataHotRemoveEnh;
        //### AMD0060 NO PCD ###CSP_AMD_SB_SETUP_MACRO(Sata6AhciCap);          	        // DXE
        //### AMD0060 NO PCD ###CSP_AMD_SB_SETUP_MACRO(SataInternal100Spread);          // DXE
        CSP_AMD_SB_SETUP_MACRO(SataMaxGen2Cap); //  PcdSataSetMaxGen2 : refer to AMD. Sandstone is TRUE. Bristo is FALSE.  // PEI
        CSP_AMD_SB_SETUP_MACRO(SataClkMode);                    // PEI

        CSP_AMD_SB_SETUP_MACRO(SataAggrLinkPmCap);              // DXE
        CSP_AMD_SB_SETUP_MACRO(SataPortMultCap);                // DXE
        CSP_AMD_SB_SETUP_MACRO(SataClkAutoOff);                 // DXE
        CSP_AMD_SB_SETUP_MACRO(SataPscCap);                     // DXE
        CSP_AMD_SB_SETUP_MACRO(SataFisBasedSwitching);          // DXE
        CSP_AMD_SB_SETUP_MACRO(SataCccSupport);                 // DXE
        CSP_AMD_SB_SETUP_MACRO(SataSscCap);                     // DXE
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(SataMsiCapability);              // DXE

        CSP_AMD_SB_SETUP_MACRO(SataTargetSupport8Device);       // DXE
        CSP_AMD_SB_SETUP_MACRO(SataDisableGenericMode);         // DXE
        CSP_AMD_SB_SETUP_MACRO(SataAhciEnclosureManagement);    // DXE
        CSP_AMD_SB_SETUP_MACRO(SataSgpio0);                     // RVA9 - Check later:
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(SataSgpio1);                     // RVA9 - Check later:

        CSP_AMD_SB_SETUP_MACRO(SataPhyPllShutDown);             // DXE

        //==================================
        //Chipset-> South Bridge->SB  FUSION Debug Configuration
        //==================================
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(AcdcChangeMessageDelivery);      // RVA9 - Check later:
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(TimerTickTracking);              // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(ClockInterruptTag);              // DXE
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(EhciTrafficHanding);             // RVA9 - Check later:
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(FusionMessageCMultiCore);        // RVA9 - Check later:
        //### RVA9 ####CSP_AMD_SB_SETUP_MACRO(FusionMessageCState);            // RVA9 - Check later:

        //==================================
        //Chipset-> South Bridge->SB  SPI Debug Configuration
        //==================================
        //#### AVA9 : PI0060 AutoMode is unused. check AMD later ###CSP_AMD_SB_SETUP_MACRO(SpiAutoMode);
        //#### AVA9 : PI0060 AutoMode is unused. check AMD later ###if(SbSetupData->SpiAutoMode == 0){
            CSP_AMD_SB_SETUP_MACRO(SpiMode);                    // PEI(PcdResetMode)/DXE(No PCD)
            //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(SPI100_Enable);              // RVA9 - Check later:
            CSP_AMD_SB_SETUP_MACRO(SpiSpeed);                   // PEI(PcdResetSpiSpeed)/DXE(No PCD)
            CSP_AMD_SB_SETUP_MACRO(SpiFastSpeed);               // PEI(PcdResetFastSpeed)/DXE(No PCD)
            //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(SpiBurstWrite);              // DXE(No PCD)
        //#### AVA9 : PI0060 AutoMode is unused. check AMD later ###}

       //==================================
        //Chipset-> South Bridge-> SB  Device D3 Debug Configuration
        //==================================
        //
        // !!! AVA9 : The following item related to "FchRTDeviceEnableMap" fix at build time in CPM. !!!
        //
        CSP_AMD_SB_SETUP_MACRO(I2C0D3);                         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(I2C1D3);                         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(I2C2D3);                         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(I2C3D3);                         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(I2C4D3);                         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(I2C5D3);                         // RVA9 - Check later:
        
        CSP_AMD_SB_SETUP_MACRO(UART0D3);                        // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(UART1D3);                        // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(UART2D3);                        // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(UART3D3);                        // RVA9 - Check later:
        
        CSP_AMD_SB_SETUP_MACRO(SATAD3); //SATA                  // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(EHCID3); //EHCI                  // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(XHCID3); //XHCI                  // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(SDD3);   //SD controller         // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(S0I3);   //S0I3 flag             // RVA9 - Check later:


        //==================================
        //Chipset-> South Bridge->SB  MSIC Debug Configuration
        //==================================
        CSP_AMD_SB_SETUP_MACRO(SdbEnable);                       // PEI/DXE

        //####SbSetupData->MobilePowerSavings = SetupData.MobilePowerSavings;
        CSP_AMD_SB_SETUP_MACRO(SpreadSpectrum);                  // DXE
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(SpreadSpectrumOptions);           // RVA9 - Check later:

#if HPET_SUPPORT
        CSP_AMD_SB_SETUP_MACRO(HpetTimer);                       // DXE
        CSP_AMD_SB_SETUP_MACRO(HpetMsiDis);                      // DXE
#else
        SbSetupData->HpetTimer = 0;                              // DXE
#endif

        CSP_AMD_SB_SETUP_MACRO(NativePcieSupport);               // RVA9 - Check later:

        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(UsbPhyPowerDown);//### AMD0060 related PCD is unavailable check later. // RVA9 - Check later:

        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(PcibClkStopOverride);//### AMD0060 NO available PCD for this. // RVA9 - Check later:

        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(UsbMsi);//### AMD0060 NO available PCD for this. // RVA9 - Check later:
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(LpcMsi);//### AMD0060 NO available PCD for this. // RVA9 - Check later:
        //### NO PCD ###CSP_AMD_SB_SETUP_MACRO(PcibMsi);//### AMD0060 NO available PCD for this. // RVA9 - Check later:
        //### AMD0060 NO available PCD for this. #### SbSetupData->Ab.AbMsiEnable = SetupData->AbMsi;
        CSP_AMD_SB_SETUP_MACRO(SBPowerState);                    // RVA9 - Check later:
        //### AMD0060 NO available PCD for this. #### SbSetupData->HwAcpi.MtC1eEnable = SetupData->SbMtC1eEnable; // RVA9 - Check later:
        //### AMD0060 NO available PCD for this. #### SbSetupData->Misc.FchCsSupport.FchCsHwReduced = SetupData->FchCsHwReduced; //  AMD default 0 // RVA9 - Check later:

        //==================================
        // Advanced IDE form
        //==================================
    #if SHOW_IDE_MODE_SETUP // RVA9 - Check later:
        CSP_AMD_SB_SETUP_MACRO(PataMasterPioMode);
        CSP_AMD_SB_SETUP_MACRO(PataSlavePioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata0PioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata1PioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata2PioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata3PioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata4PioMode);
        CSP_AMD_SB_SETUP_MACRO(Sata5PioMode);
        CSP_AMD_SB_SETUP_MACRO(PataMasterDmaMode);
        CSP_AMD_SB_SETUP_MACRO(PataSlaveDmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata0DmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata1DmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata2DmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata3DmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata4DmaMode);
        CSP_AMD_SB_SETUP_MACRO(Sata5DmaMode);
    #endif

        //==================================
        // Other modules
        //==================================
#if (( defined(TCG_SUPPORT) && (TCG_SUPPORT!=0) ) || ( defined(TCG2Support) && (TCG2Support!=0) ))
    // If support TPM, check fTPMSwitch to decide to decode TPM or not
    if (SetupData->TpmSupport == 1) {
        switch (SetupData->fTPMSwitch) {
        case 0: //fTPM
            SbSetupData->TpmDecode = 0;
            break;
        case 1: //dTPM LPC
        case 2: //dTPM SPI
            SbSetupData->TpmDecode = 1;
            break;
        default: // Do nothing
            break;
        }
    } else { // If not support TPM, do not decode TPM.
        SbSetupData->TpmDecode = 0;
    }
    // Porting End
#endif
    }
}

#endif


