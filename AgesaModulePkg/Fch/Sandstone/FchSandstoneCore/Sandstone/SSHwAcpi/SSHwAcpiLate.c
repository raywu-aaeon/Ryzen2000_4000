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
#include "FchPlatform.h"
#include "Filecode.h"
#include "FchAoacLinkListData.h"
#include "GnbDxio.h"
#include <Library/NbioSmuV10Lib.h>
#define FILECODE PROC_FCH_SANDSTONE_SSHWACPI_SSHWACPILATE_FILECODE

#define AMD_CPUID_APICID_LPC_BID    0x00000001ul  // Local APIC ID, Logical Processor Count, Brand ID

extern VOID  HpetInit                          (IN VOID  *FchDataPtr);
extern VOID  GcpuRelatedSetting              (IN VOID  *FchDataPtr);
extern VOID  StressResetModeLate               (IN VOID  *FchDataPtr);
VOID
FchInitLateHwAcpiP (
  IN  VOID     *FchDataPtr
  );

VOID
FchInitLateXgbe (
  IN  VOID     *FchDataPtr
  );

VOID
FchInitLateClkGatingCntrl (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

//For ClkGatingCntrl registers, these are not used by current logic and so they can be set to 0 (to enable localized clock gating):
//VWClkGatingDis              [4]
//OBFFBlkClkGatingDis         [6]
//FusionCBlkClkGatingDis      [7]
//CStateBlkClkGatingDis       [8]
//HwThrotBlkClkGatingDis      [9]
  ACPIMMIO16 (ACPI_MMIO_BASE + MISC_BASE + 0xFC) &= ~(UINT16) (BIT4 | BIT6 | BIT7 | BIT8 | BIT9);
//These can be enabled after POST (before handing control to OS).  However, if BIOS or SW should need to access them during run time, it should enable the corresponding bit back before access
//MIscRegBlkClkGatingDis      [0] This bis is removed because it causes PLAT-32424.
//PmioRegBlkClkGatingDis      [1] This bit causes power button hang smi hang at UEFI shell. Remove it from the list.
//Pmio2RegBlkClkGatingDis     [2] This bit causes fan settings don't work. Remove it from the list. (PLAT-34357)
//Smbus0ClkGatingDis          [5] Remove Smbus0ClkGatingDis from the list, which causes reset hang.
//BiosRamBlkClkGatingDis      [10]
//PLAT-43673  ACPIMMIO16 (ACPI_MMIO_BASE + MISC_BASE + 0xFC) &= ~(UINT16) (BIT10);

}

VOID
FchInitLateShortenResetTiming (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x12) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x16) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x1c) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x1e) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x26) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x22) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x20) &= ~(UINT16) (0x3ff);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x14) &= ~(UINT16) (0x3ff);
//t1   FCHPwrGoodTmr              PMIO 0x12[10:0]              0x14
//t19 PGPwrGoodAssertionTmr       PMIO 0x16[10:0]              0x08
//t6   PllRstBTmr                 PMIO 0x1C[10:0]              0x01
//t7   PllLockTmr                 PMIO 0x1E[10:0]              0x04
//t9   CpuPwrGoodTmr              PMIO 0x26[10:0]              0x08
//t11 CpuRstBTmr                  PMIO 0x22[10:0]              0x28
//t10  PciRstBTmr                 PMIO 0x20[10:0]              0x20
//t18  PGPwrGoodToAllEnTmr        PMIO 0x14[10:0]              0x10
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x12) |= (UINT16) (0x14);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x16) |= (UINT16) (0x08);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x1c) |= (UINT16) (0x01);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x1e) |= (UINT16) (0x04);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x26) |= (UINT16) (0x08);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x22) |= (UINT16) (0x28);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x20) |= (UINT16) (0x20);
  ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + 0x14) |= (UINT16) (0x10);
}



/**
 * FchInitLateHwAcpi - Prepare HwAcpi controller to boot to OS.
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitLateHwAcpi (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;

  AGESA_TESTPOINT (TpFchInitLateHwAcpi, NULL);

  GcpuRelatedSetting (LocalCfgPtr);

  // Mt C1E Enable
  MtC1eEnable (LocalCfgPtr);

  if (LocalCfgPtr->Gpp.SerialDebugBusEnable == TRUE ) {
    RwMem (ACPI_MMIO_BASE + SERIAL_DEBUG_BASE +  FCH_SDB_REG00, AccessWidth8, 0xFF, 0x05);
  }

  StressResetModeLate (LocalCfgPtr);
  SbSleepTrapControl (TRUE);

  FchInternalDeviceIrqInit (FchDataPtr);

  FchEventInitUsbGpe (FchDataPtr);
  // UART Legacy IO Enable Support

  FchI2cUartInitLate (FchDataPtr);

  //
  FchInitLateXgbe (FchDataPtr);
  
  //PLAT-29579 
  if (FchCheckPicasso ()) {
    FchInitLateClkGatingCntrl (FchDataPtr);
  }
  //PLAT-30090 PLAT-60361
  if ((FchCheckPicasso ()) \
    ||((FchCheckRaven2Type () == Raven2DSPCO) && (FchCheckAm4PackageType() == FALSE)) \
    ||((FchCheckRaven2Type () == Raven2Bx) && (FchCheckAm4PackageType() == FALSE))) {
    if (LocalCfgPtr->Misc.FchCsSupport.FchModernStandby) {
      FchInitLateShortenResetTiming (FchDataPtr);
    }
  }

}
VOID
FchInitLateHwAcpiP (
  IN  VOID     *FchDataPtr
  )
{
  UINT16                  FchSmiData;
  UINT8                   SwSmiCmdAddress;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  FchSmiData = (FCH_SMI_DATA_POST_LATE << 8) | FCH_AOAC_SW_VALUE;
  SwSmiCmdAddress = ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
  LibAmdIoWrite (AccessWidth16, SwSmiCmdAddress, &FchSmiData, LocalCfgPtr->StdHeader);
}
VOID
FchI2cUartInitLate (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  AMD_CONFIG_PARAMS      *StdHeader;
  UINTN                  iUartLegacyChannel;
  UINTN                  i;
  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;
  StdHeader = LocalCfgPtr->StdHeader;
  if ( LocalCfgPtr->FchRunTime.Al2AhbLegacyUartIoEnable ) {
    ACPIMMIO16 (FCH_AL2AHBx20_LEGACY_UART_IO_ENABLE) = LocalCfgPtr->FchRunTime.Al2AhbLegacyUartIoEnable;
    if (TRUE) {
      for (i = 0; i < 4; i++) {
        if ( LocalCfgPtr->FchRunTime.Al2AhbLegacyUartIoEnable & (BIT0 << i)) {
          iUartLegacyChannel = (LocalCfgPtr->FchRunTime.Al2AhbLegacyUartIoEnable >> (8 + i * 2)) & 3;
          switch  (iUartLegacyChannel) {
            case 0:
              ACPIMMIO16 (0xFEDC9008) &= 0xFF3E;
              RwPci ((SMBUS_BUS_DEV_FUN << 16) + 0xFC, AccessWidth32, ~ (UINT32) (BIT28), (UINT32) (BIT28), StdHeader);
              break;
            case 1:
              ACPIMMIO16 (0xFEDCA008) &= 0xFF3E;
              RwPci ((SMBUS_BUS_DEV_FUN << 16) + 0xFC, AccessWidth32, ~ (UINT32) (BIT29), (UINT32) (BIT29), StdHeader);
              break;
            case 2:
              ACPIMMIO16 (0xFEDCE008) &= 0xFF3E;
              RwPci ((SMBUS_BUS_DEV_FUN << 16) + 0xFC, AccessWidth32, ~ (UINT32) (BIT30), (UINT32) (BIT30), StdHeader);
              break;
            case 3:
              ACPIMMIO16 (0xFEDCF008) &= 0xFF3E;
              RwPci ((SMBUS_BUS_DEV_FUN << 16) + 0xFC, AccessWidth32, ~ (UINT32) (BIT31), (UINT32) (BIT31), StdHeader);
              break;
          }
        }
      }
    }
  }
}

VOID
FchInitLateXgbe (
  IN  VOID     *FchDataPtr
  )
{
  FCH_DATA_BLOCK         *LocalCfgPtr;
  PCI_ADDR        NbioPciAddress;
  UINT32          SmuArg[6];

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;


  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
//<Embedded_Override_Start>  
#if 0  /* Disable SMC_MSG_PowerGateXgbe for R1000 . No need to power off XGBE  */
  if (NbioSmuServiceRequestV10 (NbioPciAddress, 0x3E, SmuArg,0)) {
  }
#endif
//<Embedded_Override_End>
}

