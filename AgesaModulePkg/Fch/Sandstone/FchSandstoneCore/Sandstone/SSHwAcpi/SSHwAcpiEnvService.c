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
#define FILECODE PROC_FCH_SANDSTONE_SSHWACPI_SSHWACPIENVSERVICE_FILECODE

#define AMD_CPUID_APICID_LPC_BID    0x00000001ul  // Local APIC ID, Logical Processor Count, Brand ID

ACPI_REG_WRITE FchSandstoneInitEnvSpecificHwAcpiMmioTable[] =
{
  {00, 00, 0xB0, 0xAC},
  {PMIO_BASE >> 8,  FCH_PMIOA_REG00 + 2, 0xFB, BIT2},     //PLAT-12059 //hwemu                           // Set ASF SMBUS master function enabled here (temporary)
#ifdef ACPI_SLEEP_TRAP
  {SMI_BASE  >> 8,  FCH_SMI_REGB0, 0xF3, BIT2},                                                    // Set SLP_TYPE as SMI event
  {PMIO_BASE >> 8,  FCH_PMIOA_REGBE, 0xDF, 0x00},                                                  // Disabled SLP function for S1/S3/S4/S5
  {PMIO_BASE >> 8,  FCH_PMIOA_REG08 + 3, 0xFC, BIT1},                                              // Set S state transition disabled (BIT0) force ACPI to
                                                                                                   //  send SMI message when writing to SLP_TYP Acpi register. (BIT1)
  {SMI_BASE  >> 8,  FCH_SMI_REG98 + 3, 0x7F, 0x00},                                                // Enabled Global Smi ( BIT7 clear as 0 to enable )
#endif
  {PMIO_BASE >> 8,  FCH_PMIOA_REG80 + 1, 0xE7, BIT3 + BIT4},
  {0xFF, 0xFF, 0xFF, 0xFF},
};


/**
 * FchInitEnvHwAcpiMmioTable - Fch ACPI MMIO initial
 * during POST.
 *
 */
ACPI_REG_WRITE FchSandstoneInitEnvHwAcpiMmioTable[] =
{
  {00, 00, 0xB0, 0xAC},                                         /// Signature

  {PMIO_BASE >> 8, FCH_PMIOA_REGCC, 0xF8, 0x03},
  {PMIO_BASE >> 8, FCH_PMIOA_REG74, 0x00, BIT0 + BIT1 + BIT2 + BIT4},
  {PMIO_BASE >> 8, FCH_PMIOA_REG74 + 3, 0xDF, 0},
  {PMIO_BASE >> 8, FCH_PMIOA_REGBA, 0xF7, BIT3},
  {PMIO_BASE >> 8, FCH_PMIOA_REGBC, 0xFD, BIT1},

  {SMI_BASE >> 8, FCH_SMI_Gevent1, 0, 1},
  {SMI_BASE >> 8, FCH_SMI_Gevent3, 0, 3},
  {SMI_BASE >> 8, FCH_SMI_Gevent4, 0, 4},
  {SMI_BASE >> 8, FCH_SMI_Gevent5, 0, 5},
  {SMI_BASE >> 8, FCH_SMI_Gevent6, 0, 6},
  {SMI_BASE >> 8, FCH_SMI_Gevent23, 0, 23},
//  {SMI_BASE >> 8, FCH_SMI_xHC0Pme, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_xHC1Pme, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_Usbwakup0, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_Usbwakup1, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_Usbwakup2, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_Usbwakup3, 0, 11},
//  {SMI_BASE >> 8, FCH_SMI_IMCGevent0, 0, 12},
//  {SMI_BASE >> 8, FCH_SMI_FanThGevent, 0, 13},
//  {SMI_BASE >> 8, FCH_SMI_SBGppPme0, 0, 15},
//  {SMI_BASE >> 8, FCH_SMI_SBGppPme1, 0, 16},
//  {SMI_BASE >> 8, FCH_SMI_SBGppPme2, 0, 17},
//  {SMI_BASE >> 8, FCH_SMI_SBGppPme3, 0, 18},
//  {SMI_BASE >> 8, FCH_SMI_GecPme, 0, 19},
//  {SMI_BASE >> 8, FCH_SMI_CIRPme, 0, 28},
  {SMI_BASE >> 8, FCH_SMI_Gevent8, 0, 24},
//  {SMI_BASE >> 8, FCH_SMI_AzaliaPme, 0, 27},
  {SMI_BASE >> 8, FCH_SMI_SataGevent0, 0, 30},
  {SMI_BASE >> 8, FCH_SMI_SataGevent1, 0, 31},
  {SMI_BASE >> 8, FCH_SMI_REG08,  0xE7, 0},
  {SMI_BASE >> 8, FCH_SMI_REG0C + 2, 0xF7, BIT3},
  {SMI_BASE >> 8, FCH_SMI_SS_TWRN, 0, 9},
  {SMI_BASE >> 8, FCH_SMI_SS_XhcWake, 0, 11},
  {SMI_BASE >> 8, FCH_SMI_SS_FanThGevent, 0, 13},
  {SMI_BASE >> 8, FCH_SMI_SS_NbGppPme, 0, 16},
  {SMI_BASE >> 8, FCH_SMI_SS_NbGppHp, 0, 17},
  {0xFF, 0xFF, 0xFF, 0xFF},
};

/**
 * FchSandstoneInitEnvHwAcpiPciTable - PCI device registers
 * initial during early POST.
 *
 */
REG8_MASK FchSandstoneInitEnvHwAcpiPciTable[] =
{
  //
  // SMBUS Device (Bus 0, Dev 20, Func 0)
  //
  {0x00, SMBUS_BUS_DEV_FUN, 0},
  {FCH_CFG_REG10, 0X00, (FCH_VERSION & 0xFF)},                ///Program the version information
  {FCH_CFG_REG11, 0X00, (FCH_VERSION >> 8)},
  {0xFF, 0xFF, 0xFF},
};

///
/// PCI_IRQ_REG_BLOCK- FCH PCI IRQ registers block
///
typedef struct _PCI_IRQ_REG_BLOCK {
  UINT8                PciIrqIndex;       // PciIrqIndex - selects which PCI interrupt to map
  UINT8                PciIrqData;        // PciIrqData  - Interrupt #
} PCI_IRQ_REG_BLOCK;

STATIC PCI_IRQ_REG_BLOCK FchInternalDeviceIrqForApicMode[] = {
    { (FCH_SS_IRQ_INTA | FCH_IRQ_IOAPIC), 0x10},
    { (FCH_SS_IRQ_INTB | FCH_IRQ_IOAPIC), 0x11},
    { (FCH_SS_IRQ_INTC | FCH_IRQ_IOAPIC), 0x12},
    { (FCH_SS_IRQ_INTD | FCH_IRQ_IOAPIC), 0x13},
    { (FCH_SS_IRQ_SD | FCH_IRQ_IOAPIC), 0x10},
    { (FCH_SS_IRQ_SDIO | FCH_IRQ_IOAPIC), 0x10},
//<Embedded_Override_Start>	
    { (FCH_SS_IRQ_EMMC | FCH_IRQ_IOAPIC), 0x7},
//<Embedded_Override_End>	
    { (FCH_SS_IRQ_GPIO | FCH_IRQ_IOAPIC), 0x7},
    { (FCH_SS_IRQ_UART0 | FCH_IRQ_IOAPIC), 0x3},
    { (FCH_SS_IRQ_UART1 | FCH_IRQ_IOAPIC), 0x4},
    { (FCH_SS_IRQ_UART2 | FCH_IRQ_IOAPIC), 0xf},
    { (FCH_SS_IRQ_UART3 | FCH_IRQ_IOAPIC), 0x5},
    { (FCH_SS_IRQ_I2C0 | FCH_IRQ_IOAPIC), 0xa},
    { (FCH_SS_IRQ_I2C1 | FCH_IRQ_IOAPIC), 0xb},
    { (FCH_SS_IRQ_I2C2 | FCH_IRQ_IOAPIC), 0xe},
    { (FCH_SS_IRQ_I2C3 | FCH_IRQ_IOAPIC), 0x6},
    { (FCH_SS_IRQ_I2C4 | FCH_IRQ_IOAPIC), 0xe},
    { (FCH_SS_IRQ_I2C5 | FCH_IRQ_IOAPIC), 0xf},
  };

STATIC PCI_IRQ_REG_BLOCK FchInternalDeviceIrqForVWMode[] = {
    { (FCH_SS_IRQ_INTA | FCH_IRQ_IOAPIC), 0x10},
    { (FCH_SS_IRQ_INTB | FCH_IRQ_IOAPIC), 0x11},
    { (FCH_SS_IRQ_INTC | FCH_IRQ_IOAPIC), 0x12},
    { (FCH_SS_IRQ_INTD | FCH_IRQ_IOAPIC), 0x13},
    { (FCH_SS_IRQ_SD | FCH_IRQ_IOAPIC), 0x10},
    { (FCH_SS_IRQ_SDIO | FCH_IRQ_IOAPIC), 0x10},
//<Embedded_Override_Start>
    { (FCH_SS_IRQ_EMMC | FCH_IRQ_IOAPIC), 0x7},
//<Embedded_Override_End>
    { (FCH_SS_IRQ_GPIO | FCH_IRQ_IOAPIC), 0x7},
    { (FCH_SS_IRQ_UART0 | FCH_IRQ_IOAPIC), 0x3},
    { (FCH_SS_IRQ_UART1 | FCH_IRQ_IOAPIC), 0x4},
    { (FCH_SS_IRQ_UART2 | FCH_IRQ_IOAPIC), 0xf},
    { (FCH_SS_IRQ_UART3 | FCH_IRQ_IOAPIC), 0x5},
    { (FCH_SS_IRQ_I2C0 | FCH_IRQ_IOAPIC), 0xa},
    { (FCH_SS_IRQ_I2C1 | FCH_IRQ_IOAPIC), 0xb},
    { (FCH_SS_IRQ_I2C2 | FCH_IRQ_IOAPIC), 0xe},
    { (FCH_SS_IRQ_I2C3 | FCH_IRQ_IOAPIC), 0x6},
    { (FCH_SS_IRQ_I2C4 | FCH_IRQ_IOAPIC), 0xe},
    { (FCH_SS_IRQ_I2C5 | FCH_IRQ_IOAPIC), 0xf},
  };
#define NUM_OF_DEVICE_FOR_APICIRQ  sizeof (FchInternalDeviceIrqForApicMode) / sizeof (PCI_IRQ_REG_BLOCK)
#define VW_SRCACTIVELOW  0xFFCEF8ul

VOID
ClearThermalTripSts (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  if (LocalCfgPtr->HwAcpi.NoClearThermalTripSts == FALSE) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGC0, AccessWidth8, 0, BIT0);
  }
}

/**
 * ProgramEnvPFchAcpiMmio - Config HwAcpi MMIO registers
 *   Acpi S3 resume won't execute this procedure (POST only)
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramEnvPFchAcpiMmio (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  ProgramFchAcpiMmioTbl ((ACPI_REG_WRITE*) (&FchSandstoneInitEnvHwAcpiMmioTable[0]), StdHeader);

  ClearThermalTripSts (FchDataPtr);
}

/**
 * ProgramFchEnvHwAcpiPciReg - Config HwAcpi PCI controller
 * before PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramFchEnvHwAcpiPciReg (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  //Early post initialization of pci config space
  //
  ProgramPciByteTable ((REG8_MASK*) (&FchSandstoneInitEnvHwAcpiPciTable[0]), sizeof (FchSandstoneInitEnvHwAcpiPciTable) / sizeof (REG8_MASK), StdHeader);

  if ( LocalCfgPtr->Smbus.SmbusSsid != NULL ) {
    RwPci ((SMBUS_BUS_DEV_FUN << 16) + FCH_CFG_REG2C, AccessWidth32, 0x00, LocalCfgPtr->Smbus.SmbusSsid, StdHeader);
  }
  if ( LocalCfgPtr->Misc.NoneSioKbcSupport ) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGED, AccessWidth8, ~(UINT32) (BIT1), BIT1);
  } else {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGED, AccessWidth8, ~(UINT32) (BIT1), 0);
  }
  ProgramPcieNativeMode (FchDataPtr);
}

/**
 * FchVgaInit - Config VGA CODEC
 *
 * @param[in] VOID empty
 *
 */
VOID
FchVgaInit (
  OUT VOID
  )
{
}

/**
 * ProgramSpecificFchInitEnvAcpiMmio - Config HwAcpi MMIO before
 * PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramSpecificFchInitEnvAcpiMmio (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  ProgramFchAcpiMmioTbl ((ACPI_REG_WRITE*) (&FchSandstoneInitEnvSpecificHwAcpiMmioTable[0]), StdHeader);
//  ACPIMMIO16 (FCH_AOACx88Shadow_Register_SRAM_Addr) = 0x17; //USB3
//  ACPIMMIO32 (FCH_AOACx8CShadow_Register_SRAM_Data) = 0x1C110300;
//  ACPIMMIO16 (FCH_AOACx88Shadow_Register_SRAM_Addr) = 0x12;  //USB2
//  ACPIMMIO32 (FCH_AOACx8CShadow_Register_SRAM_Data) = 0x05030320;
//  ACPIMMIO16 (FCH_AOACx88Shadow_Register_SRAM_Addr) = 0x0F;  //SATA
//  ACPIMMIO32 (FCH_AOACx8CShadow_Register_SRAM_Data) = 0x270F0200;
//  ACPIMMIO16 (FCH_AOACx88Shadow_Register_SRAM_Addr) = 0x18;  //SD
//  ACPIMMIO32 (FCH_AOACx8CShadow_Register_SRAM_Data) = 0x0D0B0280;


  //
  // Set LDTSTP# duration
  //
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG94, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG80 + 3, AccessWidth8, 0xFE, 0x20);
  //
  // LpcClk0DrivenZero & RTC Wake Mode Control
  //
  RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG6C + 2, AccessWidth8, 0x5F, 0xA0);
  //
  // Ac Loss Control
  //
  AcLossControl ((UINT8) LocalCfgPtr->HwAcpi.PwrFailShadow);
  //
  // FCH VGA Init
  //
  FchVgaInit ();

  //
  // Set ACPIMMIO by OEM Input table
  //
  ProgramFchAcpiMmioTbl ((ACPI_REG_WRITE *) (LocalCfgPtr->HwAcpi.OemProgrammingTablePtr), StdHeader);
}

/**
 * ValidateFchVariant - Validate FCH Variant
 *
 *
 *
 * @param[in] FchDataPtr
 *
 */
VOID
ValidateFchVariant (
  IN  VOID     *FchDataPtr
  )
{
}

/**
 * IsExternalClockMode - Is External Clock Mode?
 *
 *
 * @retval  TRUE or FALSE
 *
 */
BOOLEAN
IsExternalClockMode (
  IN  VOID     *FchDataPtr
  )
{
  UINT8    MISC80;
  ReadMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG80 + 2, AccessWidth8, &MISC80);
  return ( (BOOLEAN) ((MISC80 & BIT1) == 0) );
}


/**
 * ProgramFchEnvClkCntl - Config MISC Clock control
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramFchEnvClkCntl (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // MISC 0x4C BIT17 to turn off USB3 refclk in S3/S5
  //
  RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40 + 2, AccessWidth8, 0xFD, BIT1);

  //
  // PLAT-21132 [RV FP5] Turn Off ISP_24M and USB_DBGCLK
  //
  RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG41, AccessWidth8, 0xFF, BIT5);
  // PLAT-22769 USB_DBGCLK_EnB CBS Option
  if (LocalCfgPtr->Misc.UsbDbgclkEn) {
    RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG42, AccessWidth8, 0xFB, 0);
  } else {
    RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG42, AccessWidth8, 0xFF, BIT2);
  }

  //
  // BP_X48M0
  //
  if ( LocalCfgPtr->Misc.BpX48M0OutputEnable ) {
    RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40, AccessWidth8, 0xFB, BIT2);
    if ( LocalCfgPtr->Misc.BpX48M0S0i3Enable ) {
      RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40, AccessWidth8, 0xFE, BIT0);
    } else {
      RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40, AccessWidth8, 0xFE, 0);
    }
  } else {
    RwMem (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40, AccessWidth8, 0xFB, 0);
  }
}

/**
 * ProgramFchEnvSpreadSpectrum - Config SpreadSpectrum before
 * PCI emulation
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramFchEnvSpreadSpectrum (
  IN  VOID     *FchDataPtr
  )
{
  UINT8                  FchSpreadSpectrum;
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  FchSpreadSpectrum = LocalCfgPtr->HwAcpi.SpreadSpectrum;

  //
  // new sequence for SSC programming
  //
  //Step 1 - If it is  Master die (SP4/SP3/SP3r2 socket 0 master die and AM4): (48M refclk)
  //  Misc_Reg x10[1:0] (refclk_div[1:0]) value from 2'b00 to 2'b00 (no change)
  //  Misc_Reg x10[12:4] (FCW0_int[8:0]) value from 9'h000 to 9'h000 (no change)
  //  Misc_Reg x34[31:23] (FCW1_int[8:0]) value from 9'h000 to 9'h0000 (no change)
  //  Misc_Reg x14[23:8] (FCW1_frac[8:0]) value from 16'h0000 to 16'h0000 (no change)
  //  Misc_Reg x18[31:16] (FCW_slew_frac[15:0]) value from 16'h0000 to 16'h0000 (no change)
  //  Misc_Reg x1C[16:13] (gp_coarse_mant[3:0]) value from 16'h0000 to 16'h0004
  //  Misc_Reg x1C[20:17](gp_coarse_exp[3:0]) value from 2'b00 to 2'b11
  //  Misc_Reg x1C[27:26] (gi_coarse_mant[1:0]) value from 2'b00 to 2'b11
  //  Misc_Reg x1C[12:9] (gi_coarse_exp[3:0]) value from 4'b0000 to  4'b0001
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x10, ~(UINT32)(0x3 << 0), (UINT32)(0 << 0), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x10, ~(UINT32)(0x1FF << 4), (UINT32)(0 << 4), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x34, ~(UINT32)(0x1FF << 23), (UINT32)(0 << 23), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x14, ~(UINT32)(0xFFFF << 8), (UINT32)(0 << 8), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x18, ~(UINT32)(0xFFFF << 16), (UINT32)(0 << 16), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x1C, ~(UINT32)(0xF << 13), (UINT32)(4 << 13), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x1C, ~(UINT32)(0xF << 17), (UINT32)(3 << 17), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x1C, ~(UINT32)(0x3 << 26), (UINT32)(3 << 26), StdHeader);
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x1C, ~(UINT32)(0xF << 9), (UINT32)(1 << 9), StdHeader);

  //
  //Step 2 - Misc_Reg x40[25] (FBDIV_LoadEN for loading register) value from 1'b0 to 1'b1
  //
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT25, BIT25, StdHeader);

  //
  //Step 3 - Misc_ Reg x40[30]=1 (cfg_update_req)
  //
  FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT30, BIT30, StdHeader);

  if ( FchSpreadSpectrum ) {
    //
    //Step 7 - If SSC needs to be enabled (only for SP4/SP3/SP3r2 socket 0 master die and AM4-single die, 48M refclk)
    //For SSC enable: (follow-up after CGPLL setting changes)
    //  Misc_x40[29]=1 (don't need to do this)
    //  Misc_ Reg x10[29]=1 (CORE_CGPLL_fracn_en)
    //  Misc_ Reg x08[0]=1 (CORE_CGPLL_ssc_en)
    //  Misc_ Reg x40[30]=1 (cfg_update_req)
    //FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT29, BIT29, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x10, ~(UINT32) BIT29, BIT29, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x08, ~(UINT32) BIT0, BIT0, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT30, BIT30, StdHeader);
  } else {
    //
    //Step 8 - If SSC needs to be disabled
    //For SSC disable:
    //  Misc_x40[29]=1 (don't need to do this)
    //  Misc_ Reg x10[29]=1 (CORE_CGPLL_fracn_en)
    //  Misc_ Reg x08[0]=0 (CORE_CGPLL_ssc_en)
    //  Misc_ Reg x40[30]=1 (cfg_update_req)
    //FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT29, BIT29, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x10, ~(UINT32) BIT29, BIT29, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x08, ~(UINT32) BIT0, 0, StdHeader);
    FchSmnRW (0, FCH_SS_SMN_MISC_BASE + 0x40, ~(UINT32) BIT30, BIT30, StdHeader);
  }
}


/**
 * TurnOffCG2
 *
 *
 * @retval  VOID
 *
 */
VOID
TurnOffCG2 (
  OUT VOID
  )
{
}

/**
 * BackUpCG2
 *
 *
 * @retval  VOID
 *
 */
VOID
BackUpCG2 (
  OUT VOID
  )
{
}

/**
 * HpetInit - Program Fch HPET function
 *
 *
 *
 * @param[in] FchDataPtr         Fch configuration structure pointer.
 *
 */
VOID
HpetInit (
  IN  VOID     *FchDataPtr
  )
{
  DESCRIPTION_HEADER   *HpetTable;
  BOOLEAN              FchHpetTimer;
  BOOLEAN              FchHpetMsiDis;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  FchHpetTimer = LocalCfgPtr->Hpet.HpetEnable;
  FchHpetMsiDis = LocalCfgPtr->Hpet.HpetMsiDis;

  HpetTable = NULL;
  if ( FchHpetTimer == TRUE ) {
    //
    //Program the HPET BAR address
    //
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG00, AccessWidth8, 0xFF, BIT6);

    //
    //Enabling decoding of HPET MMIO
    //Enable HPET MSI support
    //Enable High Precision Event Timer (also called Multimedia Timer) interrupt
    //
    if ( FchHpetMsiDis == FALSE ) {
      RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG00, AccessWidth32, ~(UINT32) BIT29, BIT29);
#ifdef FCH_TIMER_TICK_INTERVAL_WA
      RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG00, AccessWidth32, ~(UINT32) BIT29, 0);
#endif
    } else {
      RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG00, AccessWidth32, ~(UINT32) BIT29, 0);
    }

  } else {
    if ( ! (LocalCfgPtr->Misc.S3Resume) ) {
      HpetTable = (DESCRIPTION_HEADER*) AcpiLocateTable ('TEPH');
    }
    if ( HpetTable != NULL ) {
      HpetTable->Signature = 'HPET';
    } else {
    }
  }
}

/**
 * ProgramPcieNativeMode - Config Pcie Native Mode
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramPcieNativeMode (
  IN  VOID     *FchDataPtr
  )
{
  UINT8        FchNativepciesupport;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  FchNativepciesupport = (UINT8) LocalCfgPtr->Misc.NativePcieSupport;

  //
  // PCIE Native setting
  //
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGBA + 1, AccessWidth8, ~(UINT32) BIT6, 0);
  if ( FchNativepciesupport == 1) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG74 + 3, AccessWidth8, ~(UINT32) (BIT3 + BIT1 + BIT0), BIT3 + BIT0);
  } else {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG74 + 3, AccessWidth8, ~(UINT32) (BIT3 + BIT1 + BIT0), BIT3);
  }
}

/**
 * PciIntVwInit - Config Pci Interrupt routing for VW mode
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
PciIntVwInit (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT8                  i;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  for (i = 0; i < NUM_OF_DEVICE_FOR_APICIRQ; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC00, &FchInternalDeviceIrqForVWMode[i].PciIrqIndex, StdHeader);
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC01, &FchInternalDeviceIrqForVWMode[i].PciIrqData, StdHeader);
  }

  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGA8, AccessWidth32, 0, BIT31 + VW_SRCACTIVELOW );

}

/**
 * FchInternalDeviceIrqInit - Config Fch internal Device Interrupt routing
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInternalDeviceIrqInit (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT8                  i;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  for (i = 0; i < NUM_OF_DEVICE_FOR_APICIRQ; i++) {
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC00, &FchInternalDeviceIrqForApicMode[i].PciIrqIndex, StdHeader);
    LibAmdIoWrite (AccessWidth8, FCH_IOMAP_REGC01, &FchInternalDeviceIrqForApicMode[i].PciIrqData, StdHeader);
  }
}

/**
 * FchAl2ahbInit - Config Fch AL2AHB init
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchAl2ahbInit (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //
  // Enable Clock Gating
  //
  RwMem (AH2ALB_BASE + 0x10, AccessWidth8, 0xFF, BIT1);
  RwMem (AH2ALB_BASE + 0x30, AccessWidth8, 0xFF, BIT1);
}
/**
 * FchI2cUartInit - Config Fch AMBA I2C Uart init
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchI2cUartInit (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT32                 FchDeviceEnMap;
  RAVEN2_TYPE            Raven2Type;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  FchDeviceEnMap = LocalCfgPtr->FchRunTime.FchDeviceEnableMap;

  //
  // I2C0
  //
  if ( FchDeviceEnMap & BIT5 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C0, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x91, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x92, AccessWidth8, 0, 0x0);
  } else {
    //FchAoacPowerOnDev (FCH_AOAC_I2C0, 0);
  }

  //
  // I2C1
  //
  if ( FchDeviceEnMap & BIT6 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C1, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x93, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x94, AccessWidth8, 0, 0x0);
  } else {
    //FchAoacPowerOnDev (FCH_AOAC_I2C1, 0);
  }

  //
  // I2C2
  //
  if ( FchDeviceEnMap & BIT7 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C2, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x71, AccessWidth8, 0, 0x1);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x72, AccessWidth8, 0, 0x1);
  } else {
    FchAoacPowerOnDev (FCH_AOAC_I2C2, 0);
  }
  //
  // I2C3
  //
  if ( FchDeviceEnMap & BIT8 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C3, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x13, AccessWidth8, 0, 0x1);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x14, AccessWidth8, 0, 0x1);
  } else {
    FchAoacPowerOnDev (FCH_AOAC_I2C3, 0);
  }

  //
  // I2C4
  //
  if ( FchDeviceEnMap & BIT9 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C4, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x95, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x96, AccessWidth8, 0, 0x0);
  } else {
    //FchAoacPowerOnDev (FCH_AOAC_I2C4, 0);
  }

  //
  // I2C5
  //
  if ( FchDeviceEnMap & BIT10 ) {
    FchAoacPowerOnDev (FCH_AOAC_I2C5, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x97, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x98, AccessWidth8, 0, 0x0);
  } else {
    //FchAoacPowerOnDev (FCH_AOAC_I2C5, 0);
  }

  //
  // UART0
  //
  // PLAT-16714 
  // PLAT-18015 Register setting when EGPIO140 & 141 using as UART function
  // Set pin to input
  if ( FchDeviceEnMap & BIT11 ) {
    FchAoacPowerOnDev (FCH_AOAC_UART0, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x87, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x88, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x89, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8A, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8B, AccessWidth8, 0, 0x0);

    ACPIMMIO32 (FCH_AGPIOx87_UART0_CTS_L_UART2_RXD_EGPIO135) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx88_UART0_RXD_EGPIO136) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx89_UART0_RTS_L_UART2_TXD_EGPIO137) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8A_UART0_TXD_EGPIO138) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8B_UART0_INTR_AGPIO139) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
  } else {
    FchAoacPowerOnDev (FCH_AOAC_UART0, 0);
  }

  //
  // UART1
  //
  if ( FchDeviceEnMap & BIT12 ) {
    FchAoacPowerOnDev (FCH_AOAC_UART1, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8C, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8D, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8E, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8F, AccessWidth8, 0, 0x0);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x90, AccessWidth8, 0, 0x0);
 
    ACPIMMIO32 (FCH_AGPIOx8C_UART1_CTS_L_UART3_TXD_EGPIO140) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8D_UART1_RXD_EGPIO141) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8E_UART1_RTS_L_UART3_RXD_EGPIO142) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8F_UART1_TXD_EGPIO143) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx90_UART1_INTR_AGPIO144) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
  } else {
    FchAoacPowerOnDev (FCH_AOAC_UART1, 0);
  }

  //
  // UART2
  //
  if ( FchDeviceEnMap & BIT16 ) {
    FchAoacPowerOnDev (FCH_AOAC_UART2, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x87, AccessWidth8, 0, 0x1);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x89, AccessWidth8, 0, 0x1);
 
    ACPIMMIO32 (FCH_AGPIOx87_UART0_CTS_L_UART2_RXD_EGPIO135) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx89_UART0_RTS_L_UART2_TXD_EGPIO137) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
  } else {
    FchAoacPowerOnDev (FCH_AOAC_UART2, 0);
  }
  //
  // UART3
  //
  if ( FchDeviceEnMap & BIT26 ) {
    FchAoacPowerOnDev (FCH_AOAC_UART3, 1);
    // IOMUX
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8C, AccessWidth8, 0, 0x1);
    RwMem (ACPI_MMIO_BASE + IOMUX_BASE + 0x8E, AccessWidth8, 0, 0x1);
 
    ACPIMMIO32 (FCH_AGPIOx8C_UART1_CTS_L_UART3_TXD_EGPIO140) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
    ACPIMMIO32 (FCH_AGPIOx8E_UART1_RTS_L_UART3_RXD_EGPIO142) &= ~ FCH_AGPIO_OUTPUT_ENABLE;
  } else {
    FchAoacPowerOnDev (FCH_AOAC_UART3, 0);
  }
  //PLAT-24227
  if (!LocalCfgPtr->Misc.S3Resume) {
    Raven2Type = FchCheckRaven2Type();
    if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
      //PLAT-35474 
      //LocalCfgPtr->FchRunTime.FchDeviceEnableMap |= BIT4;  //Normal I2C0&1
    }
  }
}

/**
 * ProgramFchEnvAoacInit - AOAC configuration
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
ProgramFchEnvAoacInit (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  //if ( LocalCfgPtr->Emmc.EmmcEnable  ) {                                                 //check if EMMC is on
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x88, AccessWidth16, 0, 0x001C);
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x8C, AccessWidth32, 0, 0x06050380);
  //}
  if (LocalCfgPtr->HwAcpi.FchAoacProgramEnable) {
    //
    //Program AOAC shadow SRAM to allocate space for each of the controllers
    //
    //AB
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x88, AccessWidth16, 0, 0x0001);
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x8C, AccessWidth32, 0, 0x39260100);

    //ACPISMBUS
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x88, AccessWidth16, 0, 0x0002);
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x8C, AccessWidth32, 0, 0x16130180);

    //LPC
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x88, AccessWidth16, 0, 0x0004);
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x8C, AccessWidth32, 0, 0x5C410200);

    //ESPI
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x88, AccessWidth16, 0, 0x001B);
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x8C, AccessWidth32, 0, 0x13100300);

    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x90, AccessWidth32, 0, 0x00000016);

    if ( ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (FCH_AOAC_ESPI << 1)) & BIT3  ) { //check if ESPI is on
      RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x90, AccessWidth32, ~ (UINT32) (1 << 27) , (UINT32) (1 << 27));
    }

    if (LocalCfgPtr->Misc.FchCsSupport.FchModernStandby == FALSE) { //check if Modern Stanby is off
      RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x90, AccessWidth32, ~ (UINT32) (1 << 28) , (UINT32) (1 << 28));
    }

    //EMMC

    //Set these two bits to enable store/restore of HPET and ACPI PM timer automatically.
    RwMem (ACPI_MMIO_BASE + AOAC_BASE + 0x9C, AccessWidth32, 0, BIT0 + BIT1);

    //Start Shadow Timer
    //ShdwSysCtrl.ShdwSysCntRun = 1
    //ShdwSysCtrl.Cnt48M100Run = 1
    RwMem (ACPI_MMIO_BASE + 0x1100 + 0x10, AccessWidth32, 0, BIT0 + BIT3);
  }
}


