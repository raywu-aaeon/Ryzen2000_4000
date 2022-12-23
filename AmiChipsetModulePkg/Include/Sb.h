//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file Sb.h
    This file contains the definions for Sourthbridge

**/
//**********************************************************************

#ifndef  _SB_H   //To Avoid this header get compiled twice
#define  _SB_H

#include <Token.h>
#include <Uefi.h>
#include <Protocol/PciRootBridgeIo.h>

#if defined WDT_SUPPORT && WDT_SUPPORT == 1
#include <IndustryStandard/Acpi30.h>
#include <IndustryStandard/WatchdogResourceTable.h>
#endif

//======================================================================================
// SECTION : Reference code header definition.
//
//!!!!!	Start on AMD-Summit. To support two FCH in one BIOS.
//!!!!!	Please use the exact token definition for each FCH chip and separate different FCH porting to another library/instance.
//!!!!!		For example :
//!!!!!		To use SANDSTONE_FCH_USB_XHCI_DID instead of FCH_USB_XHCI_DID in C coding.
//!!!!!		To use FchTaishan.dec or FchKern.dec in INF and separate it to different INF.
//!!!!!		To include different header TSFch.h/KernFch.h.
//!!!!!
//!!!!!	It is not recommended that to use unclear token definition.
//!!!!!	AMI will use macro to improve the unclear token to check current FCH chip.
//!!!!!		For example :
//!!!!!		when you use FCH_SATA1_BUS the macro will help you to get correct bus number for Kern or Taishan.
//!!!!!		There is a limitation for this implement. Such macros can't be use outside function routine such as global variable.
//!!!!!		Otherwise the "error C2099: initializer is not a constant" will occur.
//======================================================================================
#if SB_DEVICE_REGS_RC_DEFINITION_SUPPORT
#include SB_DEVICE_REGS_RC_DEFINITION_HEADER
#endif

UINTN
CspGetPciExpressBaseAddress (
  VOID
  );

#define SB_AMD_PCI_ADDR_BDF(Bus,Device,Function)   \
  ((((0) & 0xfff) | (((Function) & 0x07) << 12) | (((Device) & 0x1f) << 15) | (((Bus) & 0xff) << 20)) >> 12)
//======================================================================================
//   Porting required : redefine the token of Fch.h to KernFch.h/TSFch.h
//     five steps porting notes for AMD-CSP.
//		 Step 1 : undefine the token in the Fch.h (SB_DEVICE_REGS_RC_DEFINITION_HEADER)
//======================================================================================
#ifdef USB1_EHCI_BUS_DEV_FUN 
#undef USB1_EHCI_BUS_DEV_FUN
#endif
#ifdef USB2_EHCI_BUS_DEV_FUN 
#undef USB2_EHCI_BUS_DEV_FUN
#endif
#ifdef USB3_EHCI_BUS_DEV_FUN 
#undef USB3_EHCI_BUS_DEV_FUN
#endif
#ifdef FCH_EHCI1_BUS
#undef FCH_EHCI1_BUS
#endif
#ifdef FCH_EHCI1_DEV
#undef FCH_EHCI1_DEV
#endif
#ifdef FCH_EHCI1_FUNC
#undef FCH_EHCI1_FUNC
#endif
#ifdef FCH_EHCI2_BUS
#undef FCH_EHCI2_BUS
#endif
#ifdef FCH_EHCI2_DEV
#undef FCH_EHCI2_DEV
#endif
#ifdef FCH_EHCI2_FUNC
#undef FCH_EHCI2_FUNC
#endif
#ifdef FCH_EHCI3_BUS
#undef FCH_EHCI3_BUS
#endif
#ifdef FCH_EHCI3_DEV
#undef FCH_EHCI3_DEV
#endif
#ifdef FCH_EHCI3_FUNC
#undef FCH_EHCI3_FUNC
#endif
#ifdef FCH_XHCI_BUS
#undef FCH_XHCI_BUS
#endif
#ifdef FCH_XHCI_DEV
#undef FCH_XHCI_DEV
#endif
#ifdef FCH_XHCI_FUNC
#undef FCH_XHCI_FUNC
#endif
#ifdef FCH_USB_XHCI_DID
#undef FCH_USB_XHCI_DID
#endif
#ifdef FCH_SATA1_BUS
#undef FCH_SATA1_BUS
#endif
#ifdef FCH_SATA1_DEV
#undef FCH_SATA1_DEV
#endif
#ifdef FCH_SATA1_FUNC
#undef FCH_SATA1_FUNC
#endif
#ifdef SATA_BUS_DEV_FUN
#undef SATA_BUS_DEV_FUN
#endif
#ifdef FCH_SATA_AHCI_DID
#undef FCH_SATA_AHCI_DID
#endif
#ifdef FCH_SATA_AMDAHCI_DID
#undef FCH_SATA_AMDAHCI_DID
#endif
#ifdef FCH_SATA_DID
#undef FCH_SATA_DID
#endif
#ifdef FCH_SMBUS_DID
#undef FCH_SMBUS_DID
#endif
#ifdef FCH_LPC_DID
#undef FCH_LPC_DID
#endif
#ifdef FCH_SD_DID
#undef FCH_SD_DID
#endif

//======================================================================================
//		Step 2 : include the header in the different type FCH (xxxxxxFch.h)
//======================================================================================
#include <../AgesaModulePkg/Fch/Sandstone/FchSandstoneCore/Sandstone/SSFch.h>
//======================================================================================
//		Step 3 : A macro to check Fch type
//======================================================================================
//#####define CSP_IS_SANDSTONE_FCH_MACRO ((StrCmp(L"Taishan", (CHAR16*)PcdGetPtr(PcdSbFchTypeString)) == 0)?TRUE:FALSE) // User INFs will be effected by this case. (required modify PCD section)
#define CSP_IS_SANDSTONE_FCH_MACRO TRUE // RVA9 (*(volatile UINT32*)PCIEX_BASE_ADDRESS == SOC_ZPID) // User can't use it in runtime by this case. (virtual address change)
#define CSP_IS_ZP_FCH_MACRO TRUE // RVA9 (*(volatile UINT32*)PCIEX_BASE_ADDRESS == SOC_ZPID) // User can't use it in runtime by this case. (virtual address change)

//======================================================================================
//		Step 4 : redefine the token in the Fch.h (if some token has defined in TSFch.h/KernFch.h. Please use it.)
//======================================================================================

// ((CSP_IS_SANDSTONE_FCH_MACRO) ? Sandstone : other)
#define FCH_XHCI_BUS 			FIXED_XHCI_BUS_SANDSTONE
#define FCH_XHCI_DEV 			0
#define FCH_XHCI_FUNC 			0
#define FCH_USB_XHCI_DID		SANDSTONE_FCH_USB_XHCI_DID
#define FCH_SATA1_BUS			FIXED_SATA_BUS_SANDSTONE
#define FCH_SATA1_DEV			SANDSTONE_SATA_DEV
#define FCH_SATA1_FUNC			SANDSTONE_SATA_FUN
#define SATA_BUS_DEV_FUN 		AMD_PCI_ADDR_BDF(FCH_SATA1_BUS, FCH_SATA1_DEV, FCH_SATA1_FUNC)
#define FCH_SATA_AHCI_DID 		SANDSTONE_FCH_SATA_AHCI_DID
#define FCH_SATA_AMDAHCI_DID	SANDSTONE_FCH_SATA_AMDAHCI_DID
#define FCH_SATA_DID 			SANDSTONE_FCH_SATA_DID
#define FCH_SMBUS_DID 			SANDSTONE_FCH_SMBUS_DID
#define FCH_LPC_DID 			SANDSTONE_FCH_LPC_DID
#define FCH_SD_DID 				SANDSTONE_FCH_SD_DID
//======================================================================================
//		End of Section
//======================================================================================

//
// To support multi-FCH in BIOS code. The enum type use to identify which FCH device in the code.
//		Example : we use this type in SB_PCI_DEVICES_SSID_TABLE to identify which device's ssid.
//
typedef enum {
	// All FCH chip
	SB_FCH_DEV_NULL,
	SB_FCH_DEV_SATA_AHCI,
	SB_FCH_DEV_SATA_RAID,
	SB_FCH_DEV_SATA_RAID5,
	SB_FCH_DEV_SATA_IDE,
	SB_FCH_DEV_SMBUS,
	SB_FCH_DEV_LPC,
	SB_FCH_DEV_XHCI1,
	SB_FCH_DEV_SD,
	// Sandstone
	SB_FCH_DEV_SS_NULL,
	SB_FCH_DEV_SS_SATA_AHCI,
	SB_FCH_DEV_SS_SATA_IDE,
	SB_FCH_DEV_SS_SMBUS,
	SB_FCH_DEV_SS_LPC,
	SB_FCH_DEV_SS_XHCI1,
	SB_FCH_DEV_SS_SD,
	// Taishan
	SB_FCH_DEV_TS_NULL,
	SB_FCH_DEV_TS_SATA_AHCI,
	SB_FCH_DEV_TS_SATA_RAID,
	SB_FCH_DEV_TS_SATA_RAID5,
	SB_FCH_DEV_TS_SATA_IDE,
	SB_FCH_DEV_TS_SMBUS,
	SB_FCH_DEV_TS_LPC,
	SB_FCH_DEV_TS_XHCI1,
	SB_FCH_DEV_TS_SD,
	// Kern
	SB_FCH_DEV_KE_NULL,
	SB_FCH_DEV_KE_SATA_AHCI,
	SB_FCH_DEV_KE_SATA_RAID,
	SB_FCH_DEV_KE_SATA_RAID5,
	SB_FCH_DEV_KE_SATA_IDE,
	SB_FCH_DEV_KE_SMBUS,
	SB_FCH_DEV_KE_LPC,
	SB_FCH_DEV_KE_EHCI1,
	SB_FCH_DEV_KE_XHCI1,
	SB_FCH_DEV_KE_SD,
	SB_FCH_DEV_MAX,
	// comment : current only EHCI is KE only in table.
} SB_FCH_DEV;


#define SB_PCI_CFG_ADDRESS(bus,dev,func,reg)    \
    (UINT64) ((((UINT8)bus << 24)+((UINT8)dev << 16)+((UINT8)func << 8)+((UINT8)(reg))) & 0xffffffff)

#define SB_PCIE_CFG_ADDRESS(bus,dev,func,reg) \
    ((VOID*)(UINTN)(CspGetPciExpressBaseAddress() + ((UINT8)(bus & 0xff) << 20) + ((UINT8)(dev & 0x1f) << 15) + ((UINT8)(func & 0x07) << 12) + (reg & 0xfff)))

//###//## <AAV> The reason is this macro was removed from AmiCspLib.h in AptioV some code which from Aptio4 needs this definition.
//###//##		find the proper solution later.
//####define CSP_PCI_CFG_ADDRESS(bus,dev,func,reg)   \
//### ((UINT64) ( (((UINTN)bus) <<   24) +   (((UINTN)dev)   << 16) + (((UINTN)func) << 8)   +   ((UINTN)reg) ))& 0x00000000ffffffff

//
// 8259 Hardware definitions
//
#define LEGACY_MODE_BASE_VECTOR_MASTER                    0x08
#define LEGACY_MODE_BASE_VECTOR_SLAVE                     0x10
#define LEGACY_8259_CONTROL_REGISTER_MASTER               0x20
#define LEGACY_8259_MASK_REGISTER_MASTER                  0x21
#define LEGACY_8259_CONTROL_REGISTER_SLAVE                0xA0
#define LEGACY_8259_MASK_REGISTER_SLAVE                   0xA1
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER  0x4D0
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE   0x4D1
#define LEGACY_8259_EOI                                   0x20

#define RTC_IO_INDEX                0x70    // RTC I/O Index Port
#define RTC_IO_DATA                 0x71    // RTC I/O Data Port
#define CMOS_ADDR_PORT              0x70
#define CMOS_DATA_PORT              0x71
#define CMOS_IO_EXT_INDEX           0x72    // CMOS I/O Extended Index Port
#define CMOS_IO_EXT_DATA            0x73    // CMOS I/O Extended Data Port
#define PIRQ_IO_INDEX               0xC00   // PCI Interrupt I/O Index Port
#define PIRQ_IO_DATA                0xC01   // PCI Interrupt I/O Data Port
#define BIOSRAM_INDEX_PORT          0xCD4
#define BIOSRAM_DATA_PORT           0xCD5
#define PM_IO_INDEX                 0xCD6
#define PM_IO_DATA                  0xCD7
#define NUM_BITS_IN_ACPI_TIMER      32      // Programmed to 24 not 32
// This is the maximum possible bits in the timer.  Currently this is 32 according to the spec
#define MAX_ACPI_TIMER_BITS         32

// Cpu I/O space defines
#define TIMER_CTRL              0x43
#define TIMER_0_COUNT           0x40
#define TIMER_1_COUNT           0x41

#define AMI_CSP_RESET_GUID \
 {0x308DD02C, 0x092B, 0x4123, 0xA2, 0xAF, 0x3E, 0xF4, 0x44, 0x0A, 0x6B, 0x4A}

#define RESET_PORT              0x0CF9
#define CLEAR_RESET_BITS        0x0F1
#define SB_COLD_RESET              0x02    // Set bit 1 for cold reset
#define SB_RST_CPU                 0x04    // Setting this bit triggers a reset of the CPU
#define SB_FULL_RESET              0x08    // Place system in S5 state for 3 to 5 seconds

#if defined WDT_SUPPORT && WDT_SUPPORT == 1
// WDRT Watchdog Resource Table
#define WDRT_SIG 0x54524457  //"WDRT" Watchdog Resource Table
#endif

typedef enum _SB_RESET_TYPE
{
    HardReset = 0,
    SoftReset,
    ShutDown,
    FullReset = 0x80,
} SB_RESET_TYPE;


//----------------------------------------------------------------------;
//   AMD SB700 ACPI Power Management I/O Registers                      ;
//----------------------------------------------------------------------;
#define ACPI_IOREG_PM1_STS      0x00    // Power Management 1 Status Register
#define ACPI_IOREG_PM1_EN       0x02    // Power Management 1 Enables Register
#define ACPI_IOREG_PM1_CNTL     0x04    // Power Management 1 Control Register
#define ACPI_IOREG_PM1_TMR      0x08    // Power Management 1 Timer Register
#define ACPI_IOREG_PROC_CNTL    0x10    // Processor Control register
#define ACPI_IOREG_PLVL2        0x14    // Processor Level 2 Register
#define ACPI_IOREG_PLVL3        0x15    // Processor Level 3 Register
#define ACPI_IOREG_PLVL4        0x16    // Processor Level 4 Register
#define ACPI_IOREG_CPUPS        0x17    // Processor Performance Setting Register
#define ACPI_IOREG_PM2_CNTL     0xFF    // Power Management 2 Control Register
#define ACPI_IOREG_GPE0_STS     0x20    // General Purpose Event 0 Status Register
#define ACPI_IOREG_GPE0_EN      0x24    // General Purpose Event 0 Enable Register

//----------------------------------------------------------------------;
//   AMD SB700 Power Management I/O Registers                           ;
//----------------------------------------------------------------------;
#define PM_IOREG_SMIWAKEN3      0x04    // SMI WakeUp Event Enable 3 Register
#define PM_IOREG_SMIWAKSTS3     0x07    // SMI WakeUp Event Status 3 Register
#define PM_IOREG_ACPICNTL       0x0E    // ACPI Control Register
#define PM_IOREG_ACPISTS        0x0F    // ACPI Status Register
#define PM_IOREG_ACPIEN         0x10    // ACPI Enable Register
#define PM_IOREG_SWPCIRST       0x55    // Software PCI Reset Register
#define PM_IOREG_MISCEN1        0x66    // Misc. Enable #1 Register
#define PM_IOREG_MISCEN2        0x67    // Misc. Enable #2 Register
#define PM_IOREG_MISCEN3        0x68    // Misc. Enable #3 Register
#define PM_IOREG_CF9RST         0x85    // CF9 Reset Register

//----------------------------------------------------------------------;
#define SB_REG_VID          0x00    // Vendor ID Register
#define SB_REG_DID          0x02    // Device ID Register
#define SB_REG_PCICMD       0x04    // PCI Command Register
#define SB_REG_PCISTS       0x06    // PCI Status Register
#define SB_REG_RID          0x08    // Revision ID Register
#define SB_REG_SCC          0x0A    // Sub Class Code Register
#define SB_REG_BCC          0x0B    // Base Class Code Register
#define SB_REG_MLT          0x0D    // Primary Master Latnecy Timer
#define SB_REG_HDR          0x0E    // Header Type Register
#define SB_REG_SVID         0x2C    // Sub-System Vendor ID Register

//----------------------------------------------------------------------;
//  AMD SB700 PATA PCI Register Equates (D14h:F1)                       ;
//----------------------------------------------------------------------;
#define IDE_REG_PIOTIM      0x40    // PIO Timing Register
#define IDE_REG_MDMATMD     0x44    // Multi-Words DMA Timing Modes Register
#define IDE_REG_PIOCNTL     0x48    // PIO Control Register
#define IDE_REG_PIOMODE     0x4A    // PIO Mode Register
#define IDE_REG_UDMACNTL    0x54    // Ultra DMA Control Register
#define IDE_REG_UDMAMODE    0x56    // Ultra DMA Mode Register

//----------------------------------------------------------------------;
// AMD SB700 PCI Bus/Device/Function/Register Number Macros             ;
//----------------------------------------------------------------------;
#define SB_REG(Reg)         SB_PCI_CFG_ADDRESS(FCH_LPC_BUS,FCH_LPC_DEV,FCH_LPC_FUNC,Reg)
#define SMBUS_REG(Reg)      SB_PCI_CFG_ADDRESS(FCH_ISA_BUS,FCH_ISA_DEV,FCH_ISA_FUNC,Reg)
#define IDE_REG(Reg)        SB_PCI_CFG_ADDRESS(FCH_IDE_BUS,FCH_IDE_DEV,FCH_IDE_FUNC,Reg)
#define SATA_REG(Reg)       SB_PCI_CFG_ADDRESS(FCH_SATA1_BUS,FCH_SATA1_DEV,FCH_SATA1_FUNC,Reg)

#define USB1_EHCI_REG(Reg)   SB_PCI_CFG_ADDRESS(FCH_EHCI1_BUS,FCH_EHCI1_DEV,FCH_EHCI1_FUNC,Reg)
#define USB2_EHCI_REG(Reg)   SB_PCI_CFG_ADDRESS(FCH_EHCI2_BUS,FCH_EHCI2_DEV,FCH_EHCI2_FUNC,Reg)
#define USB3_EHCI_REG(Reg)   SB_PCI_CFG_ADDRESS(FCH_EHCI3_BUS,FCH_EHCI3_DEV,FCH_EHCI3_FUNC,Reg)

#define USB_XHCI0_REG(Reg)   SB_PCI_CFG_ADDRESS(FCH_XHCI_BUS,FCH_XHCI_DEV,FCH_XHCI_FUNC,Reg)
#define USB_XHCI1_REG(Reg)   SB_PCI_CFG_ADDRESS(FCH_XHCI1_BUS,FCH_XHCI1_DEV,FCH_XHCI1_FUNC,Reg)
#define PCIBR_REG(Reg)      SB_PCI_CFG_ADDRESS(FCH_PCI_BUS,FCH_PCI_DEV,FCH_PCI_FUNC,Reg)

#define SD_REG(Reg)   SB_PCI_CFG_ADDRESS(SD_PCI_BUS,SD_PCI_DEV,SD_PCI_FUNC,Reg)


#define MAX_AHCI_CHANNEL            6


#define RAID_FC_DEVID       0x4394  // SATA + FC enable mode Device ID
#define USB20_REG_LEGEXTCAP 0xA0    // USB Legacy Support Extended Capability Register
#define USB20_REG_LEGCTLSTS 0xA4    // USB Legacy Support Control/Status Register


//----------------------------------------------------------------------;
// AMD FCH PCI Bus/Device/Function Number Macros                      	;
//----------------------------------------------------------------------;
#define LPC_BUS FCH_LPC_BUS
#define LPC_DEVICE FCH_LPC_DEV
#define LPC_FUNC FCH_LPC_FUNC

/*
#if defined WDT_SUPPORT && WDT_SUPPORT == 1
// WDRT Watchdog Resource Table
#pragma pack (push, 1)
//======================================================
//  WDRT Watchdog Resource Table
//======================================================
typedef struct {
	ACPI_HDR 	Header; 
	GAS_30		ControlRegAddr;
	GAS_30		CountRegAddr;
	UINT16      PciDeviceID;            
	UINT16      PciVendorID;        
	UINT8       PciBusNumber;       
	UINT8       PciDeviceNumber;      
	UINT8       PciFunctionNumber;
	UINT8       PciSegment;
	UINT16		MaxCount;
	UINT8		Units;
}WDRT;
#pragma pack (pop)
#endif*/

//
// EIP182488 Generic routines support in AMD SbCspLib
//		Porting notes for AMD-CSP : Don't remove the following item just comment it if it is not supported on your chip.
//#####define SB_PCIE_BUS                   NONE
//#####define SB_PCIE_DEV                   NONE
//#####define SB_PCIE1_FUN                  NONE
//#####define SB_PCIE2_FUN                  NONE
//#####define SB_PCIE3_FUN                  NONE
//#####define SB_PCIE4_FUN                  NONE
//#####define SB_PCIE5_FUN                  NONE
//#####define SB_PCIE6_FUN                  NONE
//#####define SB_PCIE7_FUN                  NONE
//#####define SB_PCIE8_FUN                  NONE

//#####define SB_PCIE_MAX_PORTS             NONE
#define SB_USB_MAX_PHYSICAL_PORTS     8
#define SB_SATA_MAX_PORTS             MAX_AHCI_CHANNEL
//#####define SB_HDA_DEV                    FCH_AZALIA_DEV
//#####define SB_HDA_FUN                    FCH_AZALIA_FUNC
//#####define R_SB_HDA_COMMAND              FCH_AZ_REG04
//#####define B_SB_HDA_COMMAND_MSE          BIT1
//#####define B_SB_HDA_COMMAND_BME          BIT2
//#####define R_SB_HDA_STATESTS             FCH_AZ_BAR_REG0E // Intel : R_HDA_STATESTS
//#####define R_SB_HDA_HDBARU               FCH_AZ_REG14
//#####define R_SB_HDA_HDBARL               FCH_AZ_REG10
//#####define R_SB_HDA_IC                   FCH_AZ_BAR_REG60
//#####define R_SB_HDA_IR                   FCH_AZ_BAR_REG64
//#####define R_SB_HDA_IRS                  FCH_AZ_BAR_REG68
//#####define B_SB_HDA_IRS_IRV              BIT1
//#####define B_SB_HDA_IRS_ICB              BIT0
//#####define V_SB_HDA_HDBAR_SIZE           (1 << 14)
//#####define SB_HDA_MAX_LOOP_TIME          NONE
//#####define SB_HDA_MAX_SID_NUMBER         NONE

//######define SB_SATA_BUS                   FCH_SATA1_BUS		// The SATA of AMD-Sandstone is behind bridge. Hard to define.
#define SB_SATA_DEV                   FCH_SATA1_DEV
#define SB_SATA_FUN                   FCH_SATA1_FUNC
#define R_SB_SATA_PI                  0x0C // BKDG : 3.30.3.3.1 Generic Host Control Registers - SATAx0C Ports Implemented (PI)
//#####define R_SB_SATA_IDETIM              NONE
//#####define R_SB_SATA_PCS                 NONE
//#####define R_SB_SATA_SIRI                NONE
//#####define R_SB_SATA_STRD                NONE
#define R_SB_SATA_COMMAND             0x04
#define R_SB_SATA_ABAR                0x24
#define R_SB_SATA_AHCI_PI             0x0C // BKDG : 3.30.3.3.1 Generic Host Control Registers - SATAx0C Ports Implemented (PI)
#define R_SB_SATA_AHCI_CAP            0x00
#define R_SB_SATA_AHCI_P0CMD          0x118

//#####define SB_LAN_DEV                    NONE
//#####define SB_LAN_FUN                    NONE

//#####define SB_PMC_BUS                    NONE
//#####define SB_PMC_DEV                    NONE
//#####define SB_PMC_FUN                    NONE

//#####define SB_REG_GEN_PMCON_3            NONE
#define SB_ACPI_PM1_STS               ACPI_IOREG_PM1_STS
#define B_SB_ACPI_PM1_STS_WAK         0x8000
#define SB_ACPI_PM1_EN                ACPI_IOREG_PM1_EN
#define SB_ACPI_PM1_CNTL              ACPI_IOREG_PM1_CNTL
#define B_SB_ACPI_PM1_CNTL_SLP_TYP    (7 << 10)
#define V_SB_ACPI_PM1_CNT_S0          (0 << 10) ///< ON (S0)
//#####define V_SB_ACPI_PM1_CNT_S1          0x00000400 ///< Puts CPU in S1 state (S1) // AMD not support
#define V_SB_ACPI_PM1_CNT_S3          (3 << 10) ///< Suspend-to-RAM (S3)
#define V_SB_ACPI_PM1_CNT_S4          (4 << 10) ///< Suspend-to-Disk (S4)
#define V_SB_ACPI_PM1_CNT_S5          (5 << 10) ///< Soft Off (S5)
#define SB_ACPI_GPE0_STS              ACPI_IOREG_GPE0_STS
#define SB_ACPI_GPE0_EN               ACPI_IOREG_GPE0_EN
//#####define SB_ACPI_ALTGP_SMI_STS         NONE

#define R_SB_LPC_GEN1_DEC             0x64
#define R_SB_LPC_GEN2_DEC             0x64
#define R_SB_LPC_GEN3_DEC             0x90
//#######define R_SB_LPC_GEN4_DEC             NONE
//#######define B_SB_LPC_GENX_DEC_EN          NONE // Enable of AMD is different register. Unable to define
//#######define B_SB_LPC_GENX_DEC_BASE        NONE // Bits of AMD is different register. Unable to define
//#######define B_SB_LPC_GENX_DEC_MASK        NONE // Bits of AMD is different register. Unable to define

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
