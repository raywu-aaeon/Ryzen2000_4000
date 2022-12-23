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

/** @file SbPolicy.h
    South Bridge setup data header file, define all the South
    Bridge setup items and a structures in this file. 

    @note  The context of the SB_SETUP_DATA may be able to copy from
           SB.SD directly 

*/


#ifndef  _AMI_SB_POLICY_H   //To Avoid this header get compiled twice
#define  _AMI_SB_POLICY_H

typedef struct  _SB_SETUP_DATA  SB_SETUP_DATA;

#pragma pack(push, 1)

///
/// FchDeviceEnableMap
///
typedef union _SB_DEVENMAP {
    UINT32  FchDeviceEnableMap;
    struct {
        UINT32  Reserved0   :   5;
        UINT32  IC0E    :   1;
        UINT32  IC1E    :   1;
        UINT32  IC2E    :   1;
        UINT32  IC3E   :   1;
        UINT32  Reserved1   :   2;
        UINT32  UT0E    :   1;
        UINT32  UT1E    :   1;
        UINT32  GIOE    :   1;
        UINT32  Reserved2   :   18;
    };
} SB_DEVENMAP;

//
//FchDeviceD3ColdMap
//
typedef union _SB_DEVD3MAP {
    UINT32  FchDeviceD3ColdMap;
    struct {
        UINT32  Reserved0   :   5;
        UINT32  IC0D    :   1;      //I2C0, 5
        UINT32  IC1D    :   1;
        UINT32  IC2D    :   1;
        UINT32  IC3D    :   1;      //I2C3, 8
        UINT32  IC4D    :   1;
        UINT32  IC5D    :   1;      
        UINT32  UT0D    :   1;      //UART0, 11
        UINT32  UT1D    :   1;      //UART1, 12
        UINT32  Reserved1   :   2;

        UINT32  ST_D    :   1;       //SATA, 15
        UINT32  UT2D    :   1;       //UART2, 16
        UINT32  Reserved2   :   1;
        UINT32  EHCD    :   1;       //EHCI, 18
        UINT32  Reserved3   :   4;
        UINT32  XHCD    :   1;       //XCHI, 23
        UINT32  SD_D    :   1;       //SD,   24
        UINT32  Reserved4   :   1;
        UINT32  UT3D    :   1;       //UART3, 26
        UINT32  Reserved5   :   1;
        UINT32  EMD3    :   1;       //EMMC D3  28
        UINT32  Reserved6   :   2;
        UINT32  S03D    :   1;      //S0I3 flag, 31
    };
} SB_DEVD3MAP;

typedef struct _SB_SETUP_DATA
{
///////////////////////////////////////////
// AMI definition
    // SB Setup header
    CHAR8   *SbPolicySignature;
    UINTN   SbPolicyVersion;
    
    UINT8   SataSelRaid5;

    UINT8   Xhci0PortEn[6];
    UINT8   Xhci1PortEn[2];
    // Disable/Enable all usb controller
    UINT8   UsbAllEnable;

    UINT8   TpmDecode;

    UINT8   PataMasterPioMode;
    UINT8   PataSlavePioMode;
    UINT8   Sata0PioMode;
    UINT8   Sata1PioMode;
    UINT8   Sata2PioMode;
    UINT8   Sata3PioMode;
    UINT8   Sata4PioMode;
    UINT8   Sata5PioMode;
    UINT8   PataMasterDmaMode;
    UINT8   PataSlaveDmaMode;
    UINT8   Sata0DmaMode;
    UINT8   Sata1DmaMode;
    UINT8   Sata2DmaMode;
    UINT8   Sata3DmaMode;
    UINT8   Sata4DmaMode;
    UINT8   Sata5DmaMode;

    BOOLEAN AmdSafeDefault;
// AMI definition
///////////////////////////////////////////

///////////////////////////////////////////
// The SETUP item related to AMD-FCH-PCDs

	//==================================
	//Chipset-> South Bridge-> SATA Configuration
	//==================================
	UINT8   SataController;
	UINT8   SataClass;
	//#### move up ###UINT8   SataSelRaid5 ; //0:Raid 1:Raid5
	UINT8   SataIdeMode;
	UINT8   SataIdeCombinedMode;

	//==================================
	//Chipset-> South Bridge-> USB Configuration
	//==================================
	UINT8   Xhci0Enable;
	UINT8   Xhci1Enable;
	
	UINT8   Usb1Ehci;

	//### move up ###UINT8   Usb0PortEn0;
	//### move up ###UINT8   Usb0PortEn1;


	//### move up ###UINT8   Usb0HubPortEn0;
	//### move up ###UINT8   Usb0HubPortEn1;
	//### move up ###UINT8   Usb0HubPortEn2;
	//### move up ###UINT8   Usb0HubPortEn3;


	//### move up ###UINT8   Xhci0PortEn0;
	//### move up ###UINT8   Xhci0PortEn1;
	//### move up ###UINT8   Xhci0PortEn2;
	//### move up ###UINT8   Xhci0PortEn3;

	// Disable/Enable all usb controller
	//### move up ###UINT8   UsbAllEnable;       // (EIP52642+)

	//Chipset-> South Bridge-> IR Configuration
	//==================================
	UINT8   IrConfig;

	//==================================
	//Chipset-> South Bridge->  SD(Secure Digital) Configuration
	//==================================
	UINT8   SdConfig;
	UINT8   SdClockControl;
	UINT8   SdSpeed;
	UINT8   SdBitwidth;
	UINT8   SdHostControllerVersion;
	UINT8   SdForce18;
	UINT8   SdDbgConfig;

	//==================================
	//Chipset-> South Bridge-> I2C Configuration
	//==================================

	UINT8   GpioAcpiEnabled;
	UINT8   I2C0Enable;
	UINT8   I2C1Enable;
	UINT8   I2C2Enable;
	UINT8   I2C3Enable;

	//==================================
	//Chipset-> South Bridge-> UART Configuration
	//==================================

	UINT8   Uart0Enable;
	UINT8   Uart1Enable;

	//==================================
	//Chipset-> South Bridge-> Power Saving
	//==================================
//#####if SB_POWER_SAVING_SUPPORT
	UINT8   GppClockGating;
	UINT8   AbClockGating;
	UINT8   PcibClockRun;
//#####endif

	UINT8   SbPcieOrderRule;
	UINT8   L1TimerOverwrite;
	UINT8   SbAlinkGppTxDriverStrength;

	//==================================
	//Chipset-> South Bridge-> SATA Debug Configuration
	//==================================
	UINT8   SataEspPort0;    // SATA ESATA Port maping
	UINT8   SataEspPort1;    // SATA ESATA Port maping
	UINT8   SataEspPort2;    // SATA ESATA Port maping
	UINT8   SataEspPort3;    // SATA ESATA Port maping
	UINT8   SataEspPort4;    // SATA ESATA Port maping
	UINT8   SataEspPort5;    // SATA ESATA Port maping
	UINT8   SataEspPort6;    // SATA ESATA Port maping
	UINT8   SataEspPort7;    // SATA ESATA Port maping

	UINT8   SataPower0;     // SATA Port Power control
	UINT8   SataPower1;     // SATA Port Power control
	UINT8   SataPower2;     // SATA Port Power control
	UINT8   SataPower3;     // SATA Port Power control
	UINT8   SataPower4;     // SATA Port Power control
	UINT8   SataPower5;     // SATA Port Power control
	UINT8   SataPower6;     // SATA Port Power control
	UINT8   SataPower7;     // SATA Port Power control

	UINT8   SataPortMode0;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode1;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode2;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode3;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode4;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode5;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode6;  // SataPortMode:12;     //11:0
	UINT8   SataPortMode7;  // SataPortMode:12;     //11:0

	//####    UINT8   SataHotRemoveEnhPort0;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort1;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort2;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort3;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort4;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort5;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort6;     // SATA Hot removable port
	//####    UINT8   SataHotRemoveEnhPort7;     // SATA Hot removable port
	UINT8   SataHotRemoveEnh;     // SATA Hot removable Enable

	UINT8   Sata6AhciCap;     // Sata 6 AHCI Support
	UINT8   SataInternal100Spread;     //Int. Clk Differential Spread
	UINT8   SataMaxGen2Cap;
	UINT8   SataClkMode;


	UINT8   SataAggrLinkPmCap; //SataAggrLinkPmCap:1;  //16, 0:OFF   1:ON
	UINT8   SataPortMultCap;   //SataPortMultCap:1;    //17, 0:OFF   1:ON
	UINT8   SataClkAutoOff;    //SataClkAutoOff:1;     //18, AutoClockOff 0:Disabled, 1:Enabled
	UINT8   SataPscCap;   //SataPscCap:1;          //19, 0:Enable PSC capability, 1:Disable PSC capability
	UINT8   SataFisBasedSwitching; //SataFisBasedSwitching  //21
	UINT8   SataCccSupport;     // SataCccSupport //22
	UINT8   SataSscCap;       // SataSscCap:1;   //23, 0:Enable SSC capability, 1:Disable SSC capability
	UINT8   SataMsiCapability;       // SataMsiCapability 24  0:Hidden 1:Visible

	UINT8   SataTargetSupport8Device ;
	UINT8   SataDisableGenericMode ;
	UINT8   SataAhciEnclosureManagement ;
	UINT8   SataSgpio0 ;
	UINT8   SataSgpio1 ;

	UINT8   SataPhyPllShutDown;


	//==================================
	//Chipset-> South Bridge->SB  FUSION Debug Configuration
	//==================================
	UINT8   AcdcChangeMessageDelivery;
	UINT8   TimerTickTracking;
	UINT8   ClockInterruptTag;
	UINT8   EhciTrafficHanding;
	UINT8   FusionMessageCMultiCore;
	UINT8   FusionMessageCState;

	//==================================
	//Chipset-> South Bridge->SB  SPI Debug Configuration
	//==================================
	UINT8   SpiAutoMode;
	UINT8   SpiMode;
	UINT8   SpiSpeed;
	UINT8   SpiFastSpeed;
	UINT8   SPI100_Enable;
	UINT8   SpiBurstWrite;

	//==================================
	//Chipset-> South Bridge-> SB Device D3 Debug Configuration
	//==================================

	UINT8   I2C0D3;
	UINT8   I2C1D3;
	UINT8   I2C2D3;
	UINT8   I2C3D3;
	UINT8   I2C4D3;
	UINT8   I2C5D3;
	
	UINT8   UART0D3;
	UINT8   UART1D3;
	UINT8   UART2D3;
	UINT8   UART3D3;
	
	UINT8   SATAD3;
	UINT8   EHCID3;
	UINT8   XHCID3;
	UINT8   SDD3;
	UINT8   S0I3;

	//==================================
	//Chipset-> South Bridge->SB  MSIC Debug Configuration
	//==================================
	UINT8   MobilePowerSavings;
	UINT8   SpreadSpectrum;
	//#####if HPET_SUPPORT
	UINT8   HpetTimer;
	UINT8   HpetMsiDis;
	//#####endif

	UINT8   NativePcieSupport;

	UINT8   UsbPhyPowerDown;

	UINT16  PcibClkStopOverride;

	UINT8   UsbMsi;
	UINT8   LpcMsi;
	UINT8   PcibMsi;
	UINT8   AbMsi;
	UINT8   SbMtC1eEnable;
	UINT8   SpreadSpectrumOptions;

	UINT8   SBPowerState;

	UINT8   SdbEnable;
	UINT8   FchCsHwReduced;

//
///////////////////////////////////////////
}SB_SETUP_DATA;

#pragma pack(pop)

//### Keep commented for sync template. (It is not required to put typedef here)
//###typedef VOID (SB_OEM_SETUP_CALLBACK) (
//###    IN VOID                 *Services,
//###    IN OUT SB_SETUP_DATA    *SbSetupData,
//###    IN SETUP_DATA           *SetupData,
//###    IN BOOLEAN              Pei
//###);

VOID GetSbSetupData(
    IN VOID                 *Service,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN BOOLEAN              Pei
);

#endif

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
