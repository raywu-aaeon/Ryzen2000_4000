//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//**********************************************************************
/** @file SataController.c
    Initialize and provide a protocol for the SATA controller.


**/
//**********************************************************************

// Module specific Includes
#include "IdeController.h"

#define FCH_SATA_BRIDGE(reg) SB_PCI_CFG_ADDRESS(0, 8, 2, reg)

CHAR16  *gIdeDriverName     = L"AMI SATA Controller Driver";
CHAR16  *gIdeControllerName = L"AMD SB700 SATA Controller";

extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *gPciRootBridgeIo;
extern EFI_S3_SAVE_STATE_PROTOCOL       *gBootScriptSave;


static PCI_STD_DEVICE   gPciData;

BOOLEAN STATIC	gIsRavenFch = TRUE;
UINT8	CONST 	gFixedSataBridgeBus = FIXED_SATA_BUS_SANDSTONE;
UINT8	STATIC	gSataBridgeBus = FIXED_SATA_BUS_SANDSTONE;

//**********************************************************************
/**
**/
//**********************************************************************
BOOLEAN IsAHCI(VOID)
{
    if ((gPciData.Header.ClassCode[1] == AMDSB_CLASS_CODE_AHCI) && \
        ((gPciData.Header.DeviceId == FCH_SATA_AHCI_DID) || (gPciData.Header.DeviceId == FCH_SATA_AMDAHCI_DID) )) {
        return TRUE;
    }else return FALSE;
}

/**

    @param VOID

        BOOLEAN
    @retval TRUE is Raid controller
    @retval FALSE not a Raid controller

**/

BOOLEAN IsRAID(VOID)
{
    BOOLEAN     IsRaid = FALSE;
#ifdef AMD_SB_RAID_IDE_BUS_SUPPORT
    if ((gPciData.Header.ClassCode[1] == PCI_CL_MASS_STOR_SCL_RAID) && \
        ((gPciData.Header.DeviceId == FCH_SATA_RAID_DID) || \
        (gPciData.Header.DeviceId == FCH_SATA_RAID5_DID) || \
        (gPciData.Header.DeviceId == RAID_FC_DEVID))) {
        IsRaid = TRUE;
    }
#endif
    return IsRaid;
}

/**
    return the current the MAX Channels for SATA controller.

    @param VOID

    @retval UINT8 Number of MAX CHANNELS


**/

UINT8
GetMaxChannels(VOID)
{
    if(IsAHCI() || IsRAID()) return CONTROLLER_MAX_CHANNELS_AHCI;
    else return CONTROLLER_MAX_CHANNELS;
}

//**********************************************************************
/**
    Check for the desired IDE controller.


    @param PciIo Pointer the PCI IO prococol


    @retval EFI_SUCCESS Is PATA controller
    @retval EFI_ERROR not PATA controller

    @note
  This routine is specific to South Bridge. If multiple IDE controllers
  are not handled by the same IDE controller driver, then this routine is
  not needed.

**/
//**********************************************************************
EFI_STATUS
IdeControllerCheck (
  IN EFI_PCI_IO_PROTOCOL   *PciIo
  )
{
    EFI_STATUS      Status;
    //
    // Now further check the PCI header: Base class (offset 0x0B) and
    // Sub Class (offset 0x0A). This controller should be an SATA controller
    //
    Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof (gPciData),
                          &gPciData
                          );
    if (EFI_ERROR (Status)) return Status;

    Status = EFI_UNSUPPORTED;
    if ((gPciData.Header.ClassCode[2] == PCI_CL_MASS_STOR) && \
        (gPciData.Header.VendorId == FCH_SATA_VID)) {

        if ((gPciData.Header.ClassCode[1] == PCI_CL_MASS_STOR_SCL_IDE) && \
            (gPciData.Header.DeviceId == FCH_SATA_DID) \
            || (gPciData.Header.DeviceId == FCH_SATA_AHCI_DID) // For ide2ahci
            ) {
            Status = EFI_SUCCESS;
        }
        if (IsAHCI()) Status = EFI_SUCCESS;
        if (IsRAID()) Status = EFI_SUCCESS;
    }

    return Status;
}

//**********************************************************************
/**
    Initialize the given IDE Controller


    @param PciIo Pointer the PCI IO prococol


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note
  Identify the IDE controller to be Initialized and do the initialization.


**/
//**********************************************************************
EFI_STATUS
InitIdeController (
  IN EFI_PCI_IO_PROTOCOL    *PciIo
  )
{
    EFI_STATUS  Status;
    UINT64      Attr;

    //
    // Enable the Controller
    //
    Status = PciIo->Attributes(PciIo,
                               EfiPciIoAttributeOperationSupported,
                               0,&Attr
                                );

    if (!EFI_ERROR (Status)) {
        Attr &= (EFI_PCI_IO_ATTRIBUTE_MEMORY | EFI_PCI_IO_ATTRIBUTE_IO \
                | EFI_PCI_IO_ATTRIBUTE_BUS_MASTER);

        Status = PciIo->Attributes( PciIo,
                                    EfiPciIoAttributeOperationSet,
                                    Attr,
                                    NULL
                                    );
		if (!EFI_ERROR (Status)) {
			UINT32	Delay = 0;
			UINT64	GlobalControl = 0x1;

			// Perform HBA reset.
			Status = PciIo->Mem.Write(PciIo, EfiPciIoWidthUint32, PCI_ABAR_INDEX, HBA_GHC, BIT0, &GlobalControl);
			if (EFI_ERROR (Status)) return EFI_DEVICE_ERROR;

			// After issuing HBA reset software should wait till GHC.HR bit get cleared
			// by HBA.
			DEBUG((DEBUG_INFO,"\n <SB.SataController> HBA Reset Issued.\n"));
			for(Delay = 100; Delay > 0 ; Delay--) {
				// RV2BU : not sure the performance whether be effected by PollMem. Check it after bring up stage.
				Status = PciIo->PollMem(PciIo, EfiPciIoWidthUint32, PCI_ABAR_INDEX, HBA_GHC, BIT0, 0, 10000, &GlobalControl);
				if (!EFI_ERROR (Status)) {
					DEBUG((DEBUG_INFO,"\n <SB.SataController> HBA Reset Success!! \n"));
					break;
				}
			}

			// If HBA has not cleared GHC.HR to 0 with in 1 second then HBA is in
			// hung or locked state.
			if( !Delay && (GlobalControl & BIT0)) {
				DEBUG((DEBUG_ERROR,"\n <SB.SataController> HBA Reset Failed \n"));
				ASSERT(FALSE);
				return EFI_DEVICE_ERROR;
			}
		}
    }

    return Status;
}

//**********************************************************************
/**
    This function is used to set appropriate UDMA timing on SATA
    controller according supported UDMA modes


    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param PciIo - Pointer to PciIo protocol opened by SATA controller driver
    @param Modes - The UDMA mode collection supported by IDE device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitSetUdmaTiming (
  IN  UINT8                       Channel,
  IN  UINT8                       Device,
  IN  EFI_PCI_IO_PROTOCOL         *PciIo,
  IN  EFI_ATA_COLLECTIVE_MODE     *Modes
  )
{
    EFI_STATUS  Status;
    UINT64      Attr;
    UINTN       Buffer;
    UINT32      UdmaMode;
    UINT32      MWDma;

    UdmaMode = (Modes->UdmaMode.Valid) ? \
                        Modes->UdmaMode.Mode:0xFF;
    MWDma = (Modes->MultiWordDmaMode.Valid) ? \
                        Modes->MultiWordDmaMode.Mode:0xFF;

    Status=PciIo->Attributes(   PciIo,
                                EfiPciIoAttributeOperationSupported,
                                0,&Attr
                                );
    if (!EFI_ERROR (Status)) {

        Attr&=(EFI_PCI_IO_ATTRIBUTE_BUS_MASTER);

        Status=PciIo->Attributes(   PciIo,
                                    EfiPciIoAttributeOperationSet,
                                    Attr,
                                    NULL);
    }
    // Enable DMA capable bit in Bus Master Status Register
    Status = PciIo->Io.Read (
            PciIo,
            EfiPciIoWidthUint8,
            4,                              // BarIndex
            Channel == 0 ? 2 : 0xA,         // Offset
            1,                              // Count
            &Buffer);

    if ((UdmaMode != 0xff) ||  (MWDma != 0xff)) {
        Buffer |= (Device == 0 ? 0x20 : 0x40); // Master/Slave
    }
    else {
        Buffer &= (Device == 0 ? 0xDF : 0xBF); // Master/Slave
    }

    Status = PciIo->Io.Write(
            PciIo,
            EfiPciIoWidthUint8,
            4,                              // BarIndex
            Channel == 0 ? 2 : 0xA,         // Offset
            1,                              // Count
            &Buffer);

    return Status;
}


//**********************************************************************
/**
    This function is used to set appropriate PIO timing on Ide
    controller according supported PIO modes


    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param PciIo - Pointer to PciIo protocol opened by Ide controller driver
    @param IdentifyData - The identify struct submitted by IDE device
    @param Modes - The PIO mode collection supported by IDE device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitSetPioTiming (
  IN  UINT8                       Channel,
  IN  UINT8                       Device,
  IN  EFI_PCI_IO_PROTOCOL         *PciIo,
  IN  EFI_IDENTIFY_DATA           *IdentifyData,
  IN  EFI_ATA_COLLECTIVE_MODE     *Modes
  )
{
    ASSERT (IdentifyData);
    return EFI_SUCCESS;
}

//**********************************************************************
/**
    User manual select the Ide Mode


    @param SetupData BIOS Setup data
    @param Channel IDE channel number (  based, either 0 or 1)
    @param Device IDE device number
    @param SupportedModes Modes collection supported by IDE device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
UserIdeMode(
  IN SB_SETUP_DATA                  *SetupData,
  IN  UINT8                         Channel,
  IN  UINT8                         Device,
  IN OUT EFI_ATA_COLLECTIVE_MODE    **SupportedModes
  )
{
#if SHOW_IDE_MODE_SETUP
    UINT8 selChannel;
    // [channel][device]
    UINT8 UserDMA[2][2] = {
        // [0][x] Sata
        {SetupData->Sata0DmaMode, SetupData->Sata2DmaMode},
        // [1][x] Sata
        {SetupData->Sata1DmaMode, SetupData->Sata3DmaMode},
    };
    UINT8 UserPIO[2][2] = {
        // [0][x] Sata
        {SetupData->Sata0PioMode, SetupData->Sata2PioMode},
        // [1][x] Sata
        {SetupData->Sata1PioMode, SetupData->Sata3PioMode},
    };

    selChannel = Channel;
    //
    // User DMA mode
    //
    if(UserDMA[selChannel][Device]) {
        // non-zero User select. set default off
        (*SupportedModes)->UdmaMode.Valid = \
        (*SupportedModes)->SingleWordDmaMode.Valid = \
        (*SupportedModes)->MultiWordDmaMode.Valid = FALSE;

        // alos set it 0xFF, because IdeBus.c use 0xFF.
        (*SupportedModes)->UdmaMode.Mode = \
        (*SupportedModes)->SingleWordDmaMode.Mode = \
        (*SupportedModes)->MultiWordDmaMode.Mode = 0xFF;

    }
    switch(UserDMA[selChannel][Device]) {
        // for AUTO
        case 0:
        break;
        // for SWDmaMode 0,1,2 >> SB700 not support ??
        case 1:case 2:case 3:
            (*SupportedModes)->SingleWordDmaMode.Valid = TRUE;
            (*SupportedModes)->SingleWordDmaMode.Mode = \
                                    UserDMA[selChannel][Device]-1;
        break;
        // for MWDmaMode 0,1,2
        case 4:case 5:case 6:
            (*SupportedModes)->MultiWordDmaMode.Valid = TRUE;
            (*SupportedModes)->MultiWordDmaMode.Mode = \
                                    UserDMA[selChannel][Device]-4;
        break;
        // for UDmaMode 0,1,2,3,4,5,6
        case 7:case 8:case 9:case 10:case 11:case 12:case 13:
            (*SupportedModes)->UdmaMode.Valid = TRUE;
            (*SupportedModes)->UdmaMode.Mode = \
                                    UserDMA[selChannel][Device]-7;
        break;
        default:
        break;
    }
    //
    // User PIO mode
    //
    if(UserPIO[selChannel][Device]) {
        (*SupportedModes)->PioMode.Valid = TRUE;
        (*SupportedModes)->PioMode.Mode = \
                                    UserPIO[selChannel][Device]-1;
    }

#endif
    return EFI_SUCCESS;
}

//**********************************************************************
/**
    Pci Io CallBack Script Save

    @param VOID

    @retval VOID

**/
//**********************************************************************
VOID
PciIoCallBackScriptSave(VOID)
{
    UINTN                           Buffer,i;
    //
    // Pci io protocol call back boot script table
    //
	struct {
		union {
			UINT64                  Address;
			struct {
				UINT64 CONST 	Reg : 8;
				UINT64 CONST 	Fun : 8;
				UINT64 CONST	Dev : 8;
				UINT64 			Bus : 8;
				UINT64 CONST 	Reserved : 32;
			} Addr;
		};
		EFI_BOOT_SCRIPT_WIDTH   Width;
	} SizeOfScriptTbl, ScriptTbl[] = {
		// Save NBIO Internal Br1 for SATA Bus and resource
        {FCH_SATA_BRIDGE(0x10),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x14),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x18),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x1C),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x20),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x24),  EfiBootScriptWidthUint32},
        {FCH_SATA_BRIDGE(0x04),  EfiBootScriptWidthUint8},

		// Save SATA controller.
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x10),  EfiBootScriptWidthUint32},
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x14),  EfiBootScriptWidthUint32},
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x18),  EfiBootScriptWidthUint32},
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x1C),  EfiBootScriptWidthUint32},
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x20),  EfiBootScriptWidthUint32},
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x24),  EfiBootScriptWidthUint32},
		{SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x04),  EfiBootScriptWidthUint8}
    };
    UINTN CONST gPciCB_ScriptSize = sizeof(ScriptTbl) / sizeof(SizeOfScriptTbl);

    if (gIsRavenFch) {
	#if defined(PCI_FIXED_BUS_ASSIGNMENT) && (PCI_FIXED_BUS_ASSIGNMENT == 1)
	#else
        
        gPciRootBridgeIo->Pci.Read(
                        gPciRootBridgeIo,
                        EfiBootScriptWidthUint16,
                        FCH_SATA_BRIDGE(0x00),
                        1,
                        &Buffer);        
        if ((UINT16)Buffer != AMD_FCH_VID ){
            return;
        }
            
        gPciRootBridgeIo->Pci.Read(
                        gPciRootBridgeIo,
                        EfiBootScriptWidthUint32,
                        FCH_SATA_BRIDGE(0x18),
                        1,
                        &Buffer);
        gSataBridgeBus = (UINT8)(Buffer >> 8);
	#endif
    }

    for (i = 0; i < gPciCB_ScriptSize; i++) {
    	if (gSataBridgeBus != gFixedSataBridgeBus && ScriptTbl[i].Addr.Bus == gFixedSataBridgeBus) {
    		ScriptTbl[i].Addr.Bus = gSataBridgeBus;
    	}

    	
        gPciRootBridgeIo->Pci.Read(
                        gPciRootBridgeIo,
                        EfiBootScriptWidthUint16,
                        SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0),
                        1,
                        &Buffer);
						
        if ((UINT16)Buffer == AMD_FCH_VID){
    	    // check SATA controller 
            gPciRootBridgeIo->Pci.Read(
                            gPciRootBridgeIo,
                            ScriptTbl[i].Width,
                            ScriptTbl[i].Address,
                            1,
                            &Buffer);
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                            CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                            ScriptTbl[i].Width,
                            ScriptTbl[i].Address,
                            1,
                            &Buffer);
        }
    }

}

//**********************************************************************
/**
    Ready To Boot CallBackScriptSave

    @param VOID

    @retval VOID

**/
//**********************************************************************
VOID
ReadyToBootCallBackScriptSave(VOID)
{
    UINTN                           Buffer,i;
    //
    // ready to boot call back boot script table
    //
    BOOT_SCRIPT_PCI_REGISTER_SAVE ScriptTbl[] = {
        {FCH_SATA_BRIDGE(0x04),  EfiBootScriptWidthUint8}, //EIP372041 : PciBus behavior change for DMA attack. This is for HDD-PW-S3 issue.
        {SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0x4), EfiBootScriptWidthUint8}
    };
    UINTN CONST gReadyToBootCB_ScriptSize = \
                    sizeof(ScriptTbl)/  \
                    sizeof(BOOT_SCRIPT_PCI_REGISTER_SAVE);

    gPciRootBridgeIo->Pci.Read(
                    gPciRootBridgeIo,
                    EfiBootScriptWidthUint16,
                    SB_PCI_CFG_ADDRESS(gSataBridgeBus, 0, 0, 0),
                    1,
                    &Buffer);
    if ((UINT16)Buffer == AMD_FCH_VID){
        // check SATA controller 
        for (i = 0; i < gReadyToBootCB_ScriptSize; i++) {
            gPciRootBridgeIo->Pci.Read(
                        gPciRootBridgeIo,
                        ScriptTbl[i].Width,
                        ScriptTbl[i].Address,
                        1,
                        &Buffer);
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                        CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                        ScriptTbl[i].Width,
                        ScriptTbl[i].Address,
                        1,
                        &Buffer);
        }
    }
}


