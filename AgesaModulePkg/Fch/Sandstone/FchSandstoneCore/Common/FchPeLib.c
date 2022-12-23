/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH IO access common routine
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*;********************************************************************************
;
; Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
;
; AMD is granting you permission to use this software and documentation (if
; any) (collectively, the "Materials") pursuant to the terms and conditions of
; the Software License Agreement included with the Materials.  If you do not
; have a copy of the Software License Agreement, contact your AMD
; representative for a copy.
;
; You agree that you will not reverse engineer or decompile the Materials, in
; whole or in part, except as allowed by applicable law.
;
; WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
; ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
; INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
; MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
; CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
; OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
; exclusion of implied warranties, so the above exclusion may not apply to
; You.
;
; LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
; NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
; INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
; THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
; liability to You for all damages, losses, and causes of action (whether in
; contract, tort (including negligence) or otherwise) exceed the amount of
; $100 USD. You agree to defend, indemnify and hold harmless AMD and its
; licensors, and any of their directors, officers, employees, affiliates or
; agents from and against any and all loss, damage, liability and other
; expenses (including reasonable attorneys' fees), resulting from Your use of
; the Materials or violation of the terms and conditions of this Agreement.
;
; U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
; "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
; subject to the restrictions as set forth in FAR 52.227-14 and
; DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
; Government constitutes acknowledgment of AMD's proprietary rights in them.
;
; EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
; stated in the Software License Agreement.
;******************************************************************************
;*/

#include <Library/BaseLib.h>
#include "FchPlatform.h"
#include "GnbDxio.h"
#include <Library/NbioSmuV10Lib.h>
#define FILECODE PROC_FCH_COMMON_FCHPELIB_FILECODE

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramPciByteTable - Program PCI register by table (8 bits data)
 *
 *
 *
 * @param[in] pPciByteTable    - Table data pointer
 * @param[in] dwTableSize      - Table length
 * @param[in] StdHeader
 *
 */
VOID
ProgramPciByteTable (
  IN       REG8_MASK           *pPciByteTable,
  IN       UINT16              dwTableSize,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8     i;
  UINT8     dbBusNo;
  UINT8     dbDevFnNo;
  UINTN     PciAddress;

  dbBusNo = pPciByteTable->RegIndex;
  dbDevFnNo = pPciByteTable->AndMask;
  pPciByteTable++;

  for ( i = 1; i < dwTableSize; i++ ) {
    if ( (pPciByteTable->RegIndex == 0xFF) && (pPciByteTable->AndMask == 0xFF) && (pPciByteTable->OrMask == 0xFF) ) {
      pPciByteTable++;
      dbBusNo = pPciByteTable->RegIndex;
      dbDevFnNo = pPciByteTable->AndMask;
      pPciByteTable++;
      i++;
    } else {
      PciAddress = (dbBusNo << 20) + (dbDevFnNo << 12) + pPciByteTable->RegIndex;
      PciAndThenOr8 (PciAddress, pPciByteTable->AndMask, pPciByteTable->OrMask);
      pPciByteTable++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramFchAcpiMmioTbl - Program FCH ACPI MMIO register by table (8 bits data)
 *
 *
 *
 * @param[in] pAcpiTbl   - Table data pointer
 * @param[in] StdHeader
 *
 */
VOID
ProgramFchAcpiMmioTbl (
  IN       ACPI_REG_WRITE      *pAcpiTbl,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8   i;
  UINT8   Or8;
  UINT8   Mask8;
  UINT32  ddtempVar;

  if (pAcpiTbl != NULL) {
    if ((pAcpiTbl->MmioReg == 0) && (pAcpiTbl->MmioBase == 0) && (pAcpiTbl->DataAndMask == 0xB0) && (pAcpiTbl->DataOrMask == 0xAC)) {
      // Signature Checking
      pAcpiTbl++;
      for ( i = 1; pAcpiTbl->MmioBase < 0x1D; i++ ) {
        ddtempVar = ACPI_MMIO_BASE | (pAcpiTbl->MmioBase) << 8 | pAcpiTbl->MmioReg;
        Or8 = pAcpiTbl->DataOrMask;
        Mask8 = ~pAcpiTbl->DataAndMask;
        LibAmdMemRMW (AccessWidth8, (UINT64) ddtempVar, &Or8, &Mask8, StdHeader);
        pAcpiTbl++;
      }
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramFchSciMapTbl - Program FCH SCI Map table (8 bits data)
 *
 *
 *
 * @param[in] pSciMapTbl   - Table data pointer
 * @param[in] FchResetDataBlock
 *
 */
VOID
ProgramFchSciMapTbl (
  IN       SCI_MAP_CONTROL  *pSciMapTbl,
  IN       FCH_RESET_DATA_BLOCK *FchResetDataBlock
  )
{
  AMD_CONFIG_PARAMS   *StdHeader;

  UINT32  ddtempVar;
  StdHeader = FchResetDataBlock->StdHeader;

  if (pSciMapTbl != NULL) {
    while (pSciMapTbl->InputPin != 0xFF) {
      if ((pSciMapTbl->InputPin >= 0x40) && (pSciMapTbl->InputPin < 0x80) && (pSciMapTbl->GpeMap < 0x20)) {
        ddtempVar = ACPI_MMIO_BASE | SMI_BASE | pSciMapTbl->InputPin;
        if (((pSciMapTbl->InputPin == FCH_SMI_xHC0Pme) && (FchResetDataBlock->FchReset.Xhci0Enable == 0)) || \
           ((pSciMapTbl->InputPin == FCH_SMI_xHC1Pme) && (FchResetDataBlock->FchReset.Xhci1Enable == 0))) {
        } else {
          LibAmdMemWrite (AccessWidth8, (UINT64) ddtempVar, &pSciMapTbl->GpeMap, StdHeader);
        }
      } else {
        //Assert Warning "SCI map is invalid"
      }
      pSciMapTbl++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramFchGpioTbl - Program FCH Gpio table (8 bits data)
 *
 *
 *
 * @param[in] pGpioTbl   - Table data pointer
 * @param[in] FchResetDataBlock
 *
 */
VOID
ProgramFchGpioTbl (
  IN       GPIO_CONTROL  *pGpioTbl,
  IN       FCH_RESET_DATA_BLOCK *FchResetDataBlock
  )
{
  AMD_CONFIG_PARAMS   *StdHeader;

  UINT32  ddtempVar;
  StdHeader = FchResetDataBlock->StdHeader;

  if (pGpioTbl != NULL) {
    while (pGpioTbl->GpioPin != 0xFF) {
      ddtempVar = ACPI_MMIO_BASE | IOMUX_BASE | pGpioTbl->GpioPin;
      LibAmdMemWrite (AccessWidth8, (UINT64) ddtempVar, &pGpioTbl->PinFunction, StdHeader);
      ddtempVar = ACPI_MMIO_BASE | GPIO_BASE | pGpioTbl->GpioPin;
      LibAmdMemWrite (AccessWidth8, (UINT64) ddtempVar, &pGpioTbl->CfgByte, StdHeader);
      pGpioTbl++;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramSataPhyTbl - Program FCH Sata Phy table (8 bits data)
 *
 *
 *
 * @param[in] pSataPhyTbl   - Table data pointer
 * @param[in] FchResetDataBlock
 *
 */
VOID
ProgramFchSataPhyTbl (
  IN       SATA_PHY_CONTROL  *pSataPhyTbl,
  IN       FCH_RESET_DATA_BLOCK *FchResetDataBlock
  )
{
  if (pSataPhyTbl != NULL) {
    while (pSataPhyTbl->PhyData != 0xFFFFFFFF) {
      //to be implemented
      pSataPhyTbl++;
    }
  }
}

/**
 * GetChipSysMode - Get Chip status
 *
 *
 * @param[in] Value - Return Chip strap status
 *   StrapStatus [15.0] - Hudson-2 chip Strap Status
 *    @li <b>0001</b> - Not USED FWH
 *    @li <b>0002</b> - Not USED LPC ROM
 *    @li <b>0004</b> - EC enabled
 *    @li <b>0008</b> - Reserved
 *    @li <b>0010</b> - Internal Clock mode
 * @param[in] StdHeader
 *
 */
VOID
GetChipSysMode (
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  LibAmdMemRead (AccessWidth8, (UINT64) (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG80), Value, StdHeader);
}

/**
 * IsImcEnabled - Is IMC Enabled
 * @retval  TRUE for IMC Enabled; FALSE for IMC Disabled
 */
BOOLEAN
IsImcEnabled (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8   dbSysConfig;
  GetChipSysMode (&dbSysConfig, StdHeader);
  if (dbSysConfig & ChipSysEcEnable) {
    return TRUE;
  } else {
    return FALSE;
  }
}


/**
 * GetEfuseStatue - Get Efuse status
 *
 *
 * @param[in] Value - Return Chip strap status
 * @param[in] StdHeader
 *
 */
VOID
GetEfuseStatus (
  IN       VOID                *Value,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8    Or8;
  UINT8    Mask8;

  Or8 = BIT5;
  Mask8 = BIT5;
  LibAmdMemRMW (AccessWidth8, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGC8), &Or8, &Mask8, StdHeader);
  LibAmdMemWrite (AccessWidth8, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGD8), Value, StdHeader);
  LibAmdMemRead (AccessWidth8, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGD8 + 1), Value, StdHeader);
  Or8 = 0;
  Mask8 = BIT5;
  LibAmdMemRMW (AccessWidth8, (UINT64) (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGC8), &Or8, &Mask8, StdHeader);
}

/*----------------------------------------------------------------------------------------*/
/**
 * SbSleepTrapControl - SB Sleep Trap Control
 *
 *
 *
 * @param[in] SleepTrap    - Whether sleep trap is enabled
 *
 */
VOID
SbSleepTrapControl (
  IN        BOOLEAN          SleepTrap
  )
{
  if (SleepTrap) {
    ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0) &= ~(BIT2 + BIT3);
    ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0) |= BIT2;

    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGBE) &= ~ (BIT5);
    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + 0xB) &= ~ (BIT0 + BIT1);
    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + 0xB) |= BIT1;
  } else {
    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGBE) |= BIT5;
    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + 0xB) &= ~ (BIT0 + BIT1);
    ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + 0xB) |= BIT0;

    ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0) &= ~(BIT2 + BIT3);
  }
}
/*----------------------------------------------------------------------------------------*/
/**
 * ProgramPMEDis - Program PMEDis
 *
 *
 *
 * @param[in] dbBusNo    - Die Bus Number
 * @param[in] PMEDis      - True to disable, False to enable
 *
 */
VOID
ProgramPMEDis (
  IN       UINT8     dbBusNo,
  IN       BOOLEAN   PMEDis
  )
{
  UINTN     PciAddress;

  PciAddress = (dbBusNo << 20) + 0x4C;
  if (PMEDis) { 
    PciAndThenOr8 (PciAddress, 0xEF, 0x10);
  }  else {
    PciAndThenOr8 (PciAddress, 0xEF, 0x00);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramLpcEmmcPins - Program Lpc/eMMC pins
 *
 *
 *
 * @param[in] eMMC_en      - True to eMMC, False to LPC
 *
 */
VOID
ProgramLpcEmmcPins (
  IN       BOOLEAN   eMMC_en
  )
{
  if (eMMC_en) {
    ACPIMMIO8 (0xFED80D15) = 1;
    ACPIMMIO8 (0xFED80D16) = 1;
    ACPIMMIO8 (0xFED80D20) = 1;
    ACPIMMIO8 (0xFED80D44) = 1;
    ACPIMMIO8 (0xFED80D46) = 1;
    ACPIMMIO8 (0xFED80D68) = 1;
    ACPIMMIO8 (0xFED80D69) = 1;
    ACPIMMIO8 (0xFED80D6A) = 1;
    ACPIMMIO8 (0xFED80D6B) = 1;
    ACPIMMIO8 (0xFED80D4A) = 1;
    ACPIMMIO8 (0xFED80D58) = 1;
    ACPIMMIO8 (0xFED80D4B) = 1;
    ACPIMMIO8 (0xFED80D57) = 1;
    ACPIMMIO8 (0xFED80D6D) = 1;
    //<Embedded_Override_Start>
    //ACPIMMIO8 (0xFED80D1F) = 1;
    //<Embedded_Override_End>
  } else {
    ACPIMMIO8 (0xFED80D15) = 0; 
    ACPIMMIO8 (0xFED80D20) = 0;
    //ACPIMMIO8 (0xFED80D44) = 0;
    //ACPIMMIO8 (0xFED80D46) = 0;
    ACPIMMIO8 (0xFED80D68) = 0;
    ACPIMMIO8 (0xFED80D69) = 0;
    ACPIMMIO8 (0xFED80D6A) = 0;
    ACPIMMIO8 (0xFED80D6B) = 0;
    ACPIMMIO8 (0xFED80D4A) = 0;
    ACPIMMIO8 (0xFED80D58) = 0;
    ACPIMMIO8 (0xFED80D4B) = 0;
    ACPIMMIO8 (0xFED80D57) = 0;
    ACPIMMIO8 (0xFED80D6D) = 0;
    //<Embedded_Override_Start>
    //ACPIMMIO8 (0xFED80D1F) = 0;
    //<Embedded_Override_End>
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * ProgramLpcSdPins - Program Lpc/SD pins
 *
 *
 *
 * @param[in] SD_en      - True to SD
 *
 */
VOID
ProgramLpcSdPins (
  IN       BOOLEAN   SD_en
  )
{
  if (SD_en) {
    ACPIMMIO8 (0xFED80D15) = 1;
    ACPIMMIO8 (0xFED80D16) = 1;
    ACPIMMIO8 (0xFED80D20) = 1;
    ACPIMMIO8 (0xFED80D44) = 1;
    ACPIMMIO8 (0xFED80D46) = 1;
    ACPIMMIO8 (0xFED80D68) = 1;
    ACPIMMIO8 (0xFED80D69) = 1;
    ACPIMMIO8 (0xFED80D6A) = 1;
    ACPIMMIO8 (0xFED80D6B) = 1;
    //<Embedded_Override_Start>
    //ACPIMMIO8 (0xFED80D1F) = 1;
    //<Embedded_Override_End>
  } else {
    ACPIMMIO8 (0xFED80D15) = 0; 
    ACPIMMIO8 (0xFED80D20) = 0;
    //ACPIMMIO8 (0xFED80D44) = 0;
    //ACPIMMIO8 (0xFED80D46) = 0;
    ACPIMMIO8 (0xFED80D68) = 0;
    ACPIMMIO8 (0xFED80D69) = 0;
    ACPIMMIO8 (0xFED80D6A) = 0;
    ACPIMMIO8 (0xFED80D6B) = 0;
    //<Embedded_Override_Start>
    //ACPIMMIO8 (0xFED80D1F) = 0;
    //<Embedded_Override_End>
  }
}
/*---------------------------------------------------------------------------------------*/
/**
 * Check RV OPN number
 *
 * @retval    TRUE    This is RV B4 part
 *            FALSE   This is not RV B4 part
 *
 */
BOOLEAN
FchCheckRvOpnB4 (
  )
{
  UINT32              RegisterData;
  UINT32              TempData32;

  TempData32 = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8));
  PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5C0);
  RegisterData = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xBC));
  PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), TempData32);

  TempData32 =  (RegisterData >> 30) & 0x3;

  if (TempData32 == 2) {
    return TRUE;
  } else if (TempData32 == 3) {
    return TRUE;
  }

  TempData32 = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8));
  PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D59C);
  RegisterData = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xBC));
  if (((RegisterData >> 16) & 0xFFFF) == 0xA6DA) {
    PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5A0);
    RegisterData = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xBC));
    if (RegisterData  == 0x0D83066C) {
      PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5A4);
      RegisterData = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xBC));
      if (RegisterData  == 0xD3D95469) {
        PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), 0x0005D5A8);
        RegisterData = PciRead32 (PCI_LIB_ADDRESS (0, 0, 0, 0xBC));
        if ((RegisterData & 0x7FF) == 0x428) {
          PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), TempData32);
          // OPN = ZM2300C4T2OFB
          return TRUE;
        }
      }
    }
  }
  PciWrite32 (PCI_LIB_ADDRESS (0, 0, 0, 0xB8), TempData32);

  return FALSE;
}

UINT32
FchGetOpnSpare (
  )
{
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];

  //#define BIOSSMC_MSG_GetOpnSpareFuse 0x51
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, 0x51, SmuArg,0)) {
    return SmuArg[0];
  }

  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function Checks Picasso
 *
 *   NOTE:
 *
 * @param[in] StdHeader
 *
 */
BOOLEAN
FchCheckPicasso (
  )
{
  CPUID_DATA CpuId;
  UINT8 Family;
  UINT8 ExtFamily;
  UINT8 Model;
  UINT8 ExtModel;
  UINT8 Stepping;
  RAVEN2_TYPE Raven2Type;

  AsmCpuid (
      0x80000001,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  //PICASSO 0x00810F80
  Family    = (UINT8) (CpuId.EAX_Reg >> 8) & 0xF;   // bit 11:8
  ExtFamily = (UINT8) (CpuId.EAX_Reg >> 20) & 0xFF; // bit 27:20
  Model     = (UINT8) (CpuId.EAX_Reg >> 4) & 0xF;   // bit 7:4
  ExtModel  = (UINT8) (CpuId.EAX_Reg >> 16) & 0xF;  // bit 19:16
  Stepping  = (UINT8) (CpuId.EAX_Reg >> 0) & 0xF;   // bit 3:0

  if ((Family == 0xF) && (ExtFamily == 0x08) && (ExtModel == 0x1) && (Model == 0x8)) {
    Raven2Type = FchCheckRaven2Type();
    if ((Raven2Type == Raven2Bx) || (Raven2Type == Raven2DSRV1) || (Raven2Type == Raven2DSPCO)) {
      return FALSE;
    }
    return TRUE;
  } else {
    return FALSE;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function Checks Raven2 with different Source
 *
 *   NOTE:
 *
 * @param[in] StdHeader
 *
 */
RAVEN2_TYPE
FchCheckRaven2Type(
  )
{
  CPUID_DATA    CpuId;
  UINT8         Family;
  UINT8         ExtFamily;
  UINT8         Model;
  UINT8         ExtModel;
  UINT8         Stepping;
  UINT32        OpnSpareID;
  BOOLEAN       IsRaven2;

  AsmCpuid (
      0x80000001,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  Family    = (UINT8) (CpuId.EAX_Reg >> 8) & 0xF;   // bit 11:8
  ExtFamily = (UINT8) (CpuId.EAX_Reg >> 20) & 0xFF; // bit 27:20
  Model     = (UINT8) (CpuId.EAX_Reg >> 4) & 0xF;   // bit 7:4
  ExtModel  = (UINT8) (CpuId.EAX_Reg >> 16) & 0xF;  // bit 19:16
  Stepping  = (UINT8) (CpuId.EAX_Reg >> 0) & 0xF;   // bit 3:0

  OpnSpareID = FchGetOpnSpare();
  IsRaven2 = (BOOLEAN)((OpnSpareID >> 30) & BIT0);

  if ((Family == 0xF) && (ExtFamily == 0x08) && (ExtModel == 0x2)) {
      return Raven2Bx;
  } else if (IsRaven2) {
      if((Family == 0xF) && (ExtFamily == 0x08) && (ExtModel == 0x1) && (Model == 0x8)) {
          return Raven2DSPCO;
      } else if ((Family == 0xF) && (ExtFamily == 0x08) && (ExtModel == 0x1) && (Model == 0x1)) {
          return Raven2DSRV1;
      }
  }
  return Raven2_Unknown;
}

/**
 *
 *
 *   This function Checks AM4 PackageType 
 *
 *   NOTE:  
 *
 * @param[in] StdHeader
 *
 */
BOOLEAN
FchCheckAm4PackageType (
  )
{
  CPUID_DATA CpuId;
  UINT8 PkgType;
  AsmCpuid (
      0x80000001,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  PkgType = (UINT8) (CpuId.EBX_Reg >> 28) & 0xF;   // bit 31:28
  if (PkgType == 0x02) {
    return TRUE;
  } else {
    return FALSE;
  }
}
/**
 *
 *
 *   This function Checks FT5 PackageType 
 *
 *   NOTE:  
 *
 *
 */
BOOLEAN
FchCheckFt5PackageType (
  )
{
  UINT32              OpnPkgId;
  OpnPkgId =  (PcdGet32 (PcdGetRVFamilyOPN) >> 16) & 0xF;
  if (OpnPkgId == 3) {//FT5 Package
    return TRUE;
  } else {
    return FALSE;
  }
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function Amd Spi Semaphore Control 
 *
 *   NOTE:
 *
 * @param[in] Control ID
 *
 */
BOOLEAN
AmdSpiSemaphoreControl  (
  SPI_SEMAPHORE_ID SemaphoreId,
  UINTN TimeoutInMicrosecond
  )
{
  UINTN timercounter;
  UINT32   TempData32;
  TempData32 = 0xFFFFFF00;
  switch (SemaphoreId) {
  case clear_all_ownerships:
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) &= ~ (BiosOwnership | DriverOwnership);
    break;
  case acquire_bios_ownership:
    timercounter = TimeoutInMicrosecond / 30;
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) |= BiosOwnership;
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) &= ~ SpiTurn;
    do {
      if (TimeoutInMicrosecond) {
        if (timercounter == 0) {
          return FALSE;
        }
        FchStall (30, NULL);
        timercounter --;
      }
    } while (((ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & DriverOwnership) == DriverOwnership) && ((ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & SpiTurn) == 0));
    break;
  case release_bios_ownership:
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) &= ~ BiosOwnership;
    break;
  case acquire_driver_ownership:
    timercounter = TimeoutInMicrosecond / 30;
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) |= DriverOwnership;
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) |= SpiTurn;
    do {
      if (TimeoutInMicrosecond) {
        if (timercounter == 0) {
          return FALSE;
        }
        FchStall (30, NULL);
        timercounter --;
      }
    } while (((ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & BiosOwnership) == BiosOwnership) && ((ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & SpiTurn) == SpiTurn));
    TempData32 = PciRead32 (PCI_LIB_ADDRESS (0, 20, 3, 0x6C));
    PciWrite32 (PCI_LIB_ADDRESS (0, 20, 3, 0x6C), 0);
    break;
  case release_driver_ownership:
    PciWrite32 (PCI_LIB_ADDRESS (0, 20, 3, 0x6C), TempData32);
    ACPIMMIO8 (SPI_SEMAPHORE_ADDR) &= ~ DriverOwnership;
    break;
  case check_bios_ownership:
    if (ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & BiosOwnership) {
      return TRUE;
    } else {
      return FALSE;
    }
    break;
  case check_driver_ownership:
    if (ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & DriverOwnership) {
      return TRUE;
    } else {
      return FALSE;
    }
    break;
  }
  return TRUE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * RestoreAmbaEmmc2D0 - Restore Amba Emmc 2 D0
 *
 *
 *
 *
 */
VOID
RestoreAmbaEmmc2D0
 (
  )
{
  FchAoacPowerOnDev (FCH_AOAC_AMBA, 1);
  FchAoacPowerOnDev (FCH_AOAC_EMMC, 1);
  FchAoacPowerOnDev (FCH_AOAC_SD1, 1);
  ACPIMMIO16 (ACPI_MMIO_BASE + MISC_BASE + 0xFC) |= 0xFFFF;
}

STATIC
EMMC_CONFIG_BIT_MAP EmmcConfigureTable[] = {
  //Emmc Configure Spec
  //version SDR50 Sup SDR100 Sup DDR50 Sup Force 1.8 Force 3.3 Re-Tuning Mode SDR50-tun WP_TIE CD_TIE SDR50 Drver strength DDR50 Driver strength Slot Type BaseFre down speed
  {{0,      0,        0,         0,        0,        0,        0,             0,        0,            0,                   0,                    0,        0x00,   0}},
  {{0x0,    0,        0,         0,        0,        0,        1,             0,        0,            1,                   1,                    0,        0x3f,   0}},
  {{0x1,    0,        0,         0,        0,        0,        1,             0,        0,            1,                   1,                    0,        0xC8,   3}},
  {{0x2,    1,        0,         0,        0,        0,        1,             0,        0,            1,                   1,                    0,        0xC8,   3}},
  {{0x2,    0,        0,         1,        0,        0,        1,             0,        0,            1,                   1,                    0,        0xC8,   3}},
  {{0x2,    1,        1,         1,        0,        0,        1,             0,        0,            1,                   1,                    0,        0xC8,   3}},
  {{0x0,    0,        0,         0,        1,        0,        0,             0,        3,            1,                   1,                    1,        0x3f,   0}},
  {{0x2,    0,        0,         0,        1,        0,        0,             0,        3,            1,                   1,                    1,        0xC8,   3}},
  {{0x2,    0,        0,         1,        1,        0,        0,             0,        3,            1,                   1,                    1,        0xC8,   3}},
  {{0x2,    1,        1,         0,        1,        0,        0,             0,        3,            1,                   1,                    1,        0xC8,   3}},
  {{0x2,    1,        1,         1,        1,        0,        0,             0,        3,            1,                   1,                    1,        0xC8,   3}},
  {{0x2,    1,        1,         1,        1,        0,        0,             0,        3,            1,                   1,                    1,        0x96,   2}}
};
VOID
FchEmmcOnRecovery (
  IN       VOID     *FchDataPtr
  )
{
  FCH_RESET_DATA_BLOCK   *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINT32                 EspiBase;
  LocalCfgPtr = (FCH_RESET_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  if ( LocalCfgPtr->Emmc.EmmcEnable ) {
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGE8, AccessWidth8, ~(UINT32) BIT4, BIT4);
    if ( LocalCfgPtr->Emmc.EmmcBoot ) {
    //Configure all IoMux and clear status here
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG44), AccessWidth32, 0, 0,StdHeader);
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG48), AccessWidth32, 0xFF00, 0,StdHeader);
    //<Embedded_Override_Start>
    RwPci (((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REG7C), AccessWidth32, 0, 0, StdHeader);
    if (PcdGetBool (PcdEspiIo80Enable))
    {
      //Need to route 80 IO port to eSPI instead of LPC
      ReadPci ((LPC_BUS_DEV_FUN << 16) + FCH_LPC_REGA0, AccessWidth32, &EspiBase, NULL);
      EspiBase &= 0xFFFFFFC0;
      EspiBase += 0x00010000;
      RwMem (EspiBase + 0x40, AccessWidth32, ~(UINT32)BIT2, BIT2);
    }
    //<Embedded_Override_End>
    }
    RwMem (FCH_EMMC_CFG_REGB0,  AccessWidth32, ~ (UINT32) (0xFF << 24), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Spec_Ver << 24));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 0) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50_Sup << 0));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 1) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr100_Sup << 1));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 2) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Ddr50_Sup << 2));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x01 << 17), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Force18 << 17));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x01 << 18), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Force33 << 18));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.ReTuningMode << 14));
    RwMem (FCH_EMMC_CFG_REGA8,  AccessWidth32, ~ (UINT32) (0x01 << 13), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50Tune << 13));
    RwMem (FCH_EMMC_CFG_REGD0,  AccessWidth32, ~ (UINT32) (0x03 << 26), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.WpCdTie << 26));
    RwMem (FCH_EMMC_CFG_REGFA,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Sdr50DriverStrength << 14));
    RwMem (FCH_EMMC_CFG_REGFE,  AccessWidth32, ~ (UINT32) (0x03 << 14), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.Ddr50DriverStrength << 14));
    RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x03 << 30), (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.SlotType << 30));
    RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0xFF << 8) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.BaseFre << 8));
    RwMem (FCH_EMMC_CFG_REG116, AccessWidth32, ~ (UINT32) (0x03 << 4) , (UINT32) (EmmcConfigureTable[LocalCfgPtr->Emmc.EmmcEnable].Field.DownSpeed << 4));
    if (!LocalCfgPtr->Emmc.EmmcAdma2Support ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 19) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcAdmaSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 20) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcSdmaSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 22) , 0);
    }
    if (!LocalCfgPtr->Emmc.EmmcA64bSupport ) {
      RwMem (FCH_EMMC_CFG_REGA4,  AccessWidth32, ~ (UINT32) (0x1 << 28) , 0);
    }
    //Configure eMMC pins
    ProgramLpcEmmcPins (TRUE);
  }
}
/*----------------------------------------------------------------------------------------*/
/**
 * ProgramXhciPmeEn - Program PME enable bit for XHCI controllers
 *
 *
 *
 */
VOID
ProgramXhciPmeEn (
  IN  VOID     *FchDataPtr
  )
{
  UINT32              Xhci0PmeMapping = 0, Xhci1PmeMapping = 0;
  FCH_DATA_BLOCK      *FchData;
  FchData = (FCH_DATA_BLOCK *)FchDataPtr;
  if (FchData->Usb.Xhci0Enable){
    Xhci0PmeMapping = ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_xHC0Pme);
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG04) |= (BIT0 << Xhci0PmeMapping);
  }
  if (FchData->Usb.Xhci1Enable){
    Xhci1PmeMapping = ACPIMMIO8 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_xHC1Pme);
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG04) |= (BIT0 << Xhci1PmeMapping);
  }
}
