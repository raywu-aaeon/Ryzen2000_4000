/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH PEIM
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH PEIM
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
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
#include "FchPei.h"
#include "FchReset.h"
#include "FchReset2.h"
#include "FchStall.h"
#include <Library/FchPeiLib.h>
#define FILECODE UEFI_PEI_FCHPEI_FCHPEI_FILECODE

#include <Ppi/CpuIo.h>
#include <Ppi/Reset.h>
#include <Ppi/Reset2.h>
#include <Ppi/Stall.h>
#include <Ppi/MemoryDiscovered.h>

#include <Library/BaseMemoryLib.h>

extern EFI_GUID gFchResetDataHobGuid;
extern FCH_RESET_DATA_BLOCK   InitResetCfgDefault;

//
// Module globals
//
STATIC EFI_PEI_RESET_PPI mResetPpi = {
  FchPeiReset
};

STATIC EFI_PEI_RESET2_PPI mResetPpi2 = {
  FchPeiReset2
};

STATIC EFI_PEI_STALL_PPI mStallPpi = {
  FCH_STALL_RESOLUTION_USEC,
  FchPeiStall
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiListReset = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiResetPpiGuid,
  &mResetPpi
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiListReset2 = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiReset2PpiGuid,
  &mResetPpi2
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiListStall = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiStallPpiGuid,
  &mStallPpi
};

EFI_PEI_NOTIFY_DESCRIPTOR   mMemoryDicoverPpiCallback = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  FchMemoryDiscoveredPpiCallback
};

//Data init routine to setup default value
EFI_STATUS
EFIAPI
FchInitResetDataDefault (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  );

EFI_STATUS
EFIAPI
FchInitPcdResetData (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  );

//main routine for Fch PEI init work
EFI_STATUS
EFIAPI
FchInitPei (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  );

/*********************************************************************************
 * Name: FchPeiInit
 *
 * Description:
 *               > Update boot mode
 *               > Install Reset PPI
 *               > Install SMBUS PPI
 *               > Install Stall PPI
 *
 * Input
 *   FfsHeader   : pointer to the firmware file system header
 *   PeiServices : pointer to the PEI service table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
FchPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                Status;
  EFI_PEI_RESET_PPI         *PeiReset;
  EFI_PEI_RESET2_PPI        *PeiReset2;
  EFI_PEI_STALL_PPI         *PeiStall;
  EFI_HOB_GUID_TYPE         *FchHob;

  FCH_PEI_PRIVATE           *FchPrivate;
  EFI_PEI_PPI_DESCRIPTOR    *PpiListFchInit;
  FCH_RESET_DATA_BLOCK      *FchParams;

  AGESA_TESTPOINT (TpFchPeiEntry, NULL);
  //
  // Check SOC ID
  //


  //
  // Check Fch HW ID
  //

  // Create Fch GUID HOB to save FCH_RESET_DATA_BLOCK
  Status = (*PeiServices)->CreateHob (
                             PeiServices,
                             EFI_HOB_TYPE_GUID_EXTENSION,
                             sizeof (EFI_HOB_GUID_TYPE) + sizeof (FCH_RESET_DATA_BLOCK),
                             &FchHob
                             );

  ASSERT_EFI_ERROR (Status);
  CopyMem (&FchHob->Name, &gFchResetDataHobGuid, sizeof (EFI_GUID));
  FchHob++;
  FchParams = (FCH_RESET_DATA_BLOCK *)FchHob;
  //load default to Fch data structure
  Status = FchInitResetDataDefault (FchParams);

  //Init FCH_PEI_PRIVATE
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (FCH_PEI_PRIVATE),
                             &FchPrivate
                             );
  ASSERT_EFI_ERROR ( Status);

  FchPrivate->Signature                    = FCH_PEI_PRIVATE_DATA_SIGNATURE;
  FchPrivate->StdHdr.AltImageBasePtr       = (UINT32) PeiServices;
  FchPrivate->FchInitPpi.Revision          = AMD_FCH_INIT_PPI_REV;
  FchPrivate->FchInitPpi.FchResetData      = (VOID*) FchParams;
  FchPrivate->FchInitPpi.PtResetData       = (VOID*) &(FchParams->Promontory);
  FchPrivate->FchInitPpi.FpFchXhciRecovery = FchInitXhciOnRecovery;
  FchPrivate->FchInitPpi.FpFchEhciRecovery = FchInitEhciOnRecovery;
  FchPrivate->FchInitPpi.FpFchSataRecovery = FchInitSataOnRecovery;
  FchPrivate->FchInitPpi.FpFchGppRecovery  = FchInitGppOnRecovery;
  FchPrivate->FchInitPpi.FpFchEmmcRecovery = FchInitEmmcOnRecovery;

  //platform/OEM update 6.5
  //AgesaFchOemCallout (FchParams);
  //Do the real init tasks
  DEBUG ((DEBUG_INFO, "[FchInitPei] Fch Pei Init ...Start.\n"));
  Status = FchInitPei (FchParams);
  DEBUG ((DEBUG_INFO, "[FchInitPei] Fch Pei Init ...Complete.\n"));
  //
  // Update the boot mode
  //
  Status = FchUpdateBootMode ((EFI_PEI_SERVICES **)PeiServices);
  ASSERT_EFI_ERROR (Status);


  //
  // publish other PPIs
  //
  // Reset PPI
  // check to see if an instance is already installed
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gEfiPeiResetPpiGuid,
                             0,
                             NULL,
                             &PeiReset
                             );

  if (EFI_NOT_FOUND == Status) {
    // No instance currently installed, install our own
    Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               &mPpiListReset
                               );

    ASSERT_EFI_ERROR ( Status);
  }

  // Reset2 PPI
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gEfiPeiReset2PpiGuid,
                             0,
                             NULL,
                             &PeiReset2
                             );

  if (EFI_NOT_FOUND == Status) {
    // No instance currently installed, install our own
    Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               &mPpiListReset2
                               );

    ASSERT_EFI_ERROR ( Status);
  }

  // Stall PPI
  // check to see if an instance is already installed
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gEfiPeiStallPpiGuid,
                             0,
                             NULL,
                             &PeiStall
                             );

  if (EFI_NOT_FOUND == Status) {
    // There is no instance currently installed, install our own
    Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               &mPpiListStall
                               );

    ASSERT_EFI_ERROR ( Status);
  }

  // Allocate memory for the PPI descriptor
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_PEI_PPI_DESCRIPTOR),
                             &PpiListFchInit
                             );
  ASSERT_EFI_ERROR ( Status);

  PpiListFchInit->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  PpiListFchInit->Guid  = &gAmdFchInitPpiGuid;
  PpiListFchInit->Ppi   = &FchPrivate->FchInitPpi;

  Status = (*PeiServices)->InstallPpi (
                             PeiServices,
                             PpiListFchInit
                             );
  ASSERT_EFI_ERROR ( Status);

  Status = (*PeiServices)->NotifyPpi (PeiServices, &mMemoryDicoverPpiCallback);
  ASSERT_EFI_ERROR ( Status);

  AGESA_TESTPOINT (TpFchPeiExit, NULL);
  return Status;
}
/*********************************************************************************
 * Name: FchInitResetDataDefault
 *
 * Description:
 *               load Default value of FCH_RESET_DATA_BLOCK
 *
 * Input
 *   FchParams   : pointer to FCH_RESET_DATA_BLOCK
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
FchInitResetDataDefault (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  )
{
  EFI_STATUS                Status;
  *FchParams = InitResetCfgDefault;

  //Platform call out
  Status = FchPlatformPTPeiInit ((VOID *)&FchParams->Promontory);

  ASSERT_EFI_ERROR (Status);

  Status = FchPlatformOemPeiInit ((VOID *)FchParams);

  ASSERT_EFI_ERROR (Status);

  IDS_HOOK(IDS_HOOK_FCH_INIT_RESET, NULL, (VOID *)FchParams);

  FchInitPcdResetData (FchParams);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FchInitPcdResetData (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  )
{
  FchParams->FchBldCfg.CfgSmbus0BaseAddress = PcdGet16 (PcdAmdFchCfgSmbus0BaseAddress);
  FchParams->FchBldCfg.CfgSioPmeBaseAddress = PcdGet16 (PcdAmdFchCfgSioPmeBaseAddress);
  FchParams->FchBldCfg.CfgAcpiPm1EvtBlkAddr = PcdGet16 (PcdAmdFchCfgAcpiPm1EvtBlkAddr);
  FchParams->FchBldCfg.CfgAcpiPm1CntBlkAddr = PcdGet16 (PcdAmdFchCfgAcpiPm1CntBlkAddr);
  FchParams->FchBldCfg.CfgAcpiPmTmrBlkAddr  = PcdGet16 (PcdAmdFchCfgAcpiPmTmrBlkAddr);
  FchParams->FchBldCfg.CfgCpuControlBlkAddr = PcdGet16 (PcdAmdFchCfgCpuControlBlkAddr);
  FchParams->FchBldCfg.CfgAcpiGpe0BlkAddr   = PcdGet16 (PcdAmdFchCfgAcpiGpe0BlkAddr);
  FchParams->FchBldCfg.CfgSmiCmdPortAddr    = PcdGet16 (PcdAmdFchCfgSmiCmdPortAddr);
  //FchParams->FchBldCfg.CfgCpuControlBlkAddr = PcdGet16 (PcdAmdFchCfgCpuControlBlkAddr);

  //Dynamic PCDs
  FchParams->LegacyFree                    = PcdGetBool (PcdLegacyFree);
  //FchParams->EcKbd                         = PcdGetBool (PcdEcKbd);
  FchParams->FchOscout1ClkContinous        = PcdGetBool (PcdFchOscout1ClkContinous);
  FchParams->FchReset.SataEnable           = PcdGetBool (PcdSataEnable);
  if ((FchCheckFt5PackageType()) && (FchCheckRaven2Type() != Raven2_Unknown)){
    FchParams->FchReset.SataEnable = FALSE;
  }
  FchParams->SataSetMaxGen2                = PcdGetBool (PcdSataSetMaxGen2);
  FchParams->SataClkMode                   = PcdGet8 (PcdSataClkMode);
  FchParams->FchReset.Xhci0Enable          = PcdGetBool (PcdXhci0Enable);
  FchParams->FchReset.Xhci1Enable          = PcdGetBool (PcdXhci1Enable);
  FchParams->LpcClockDriveStrength         = PcdGet8 (PcdLpcClockDriveStrength);
  FchParams->LpcClockDriveStrengthRiseTime = PcdGet8 (PcdLpcClockDriveStrengthRiseTime);
  FchParams->LpcClockDriveStrengthFallTime = PcdGet8 (PcdLpcClockDriveStrengthFallTime);
//  FchParams->XhciECCDedErrRptEn            = PcdGetBool (PcdXhciECCDedErrRptEn);
  FchParams->Mode                          = PcdGet8 (PcdResetMode);
  FchParams->SpiSpeed                      = PcdGet8 (PcdResetSpiSpeed);
  FchParams->FastSpeed                     = PcdGet8 (PcdResetFastSpeed);
  FchParams->Spi.LpcClk0                   = PcdGetBool (PcdLpcClk0);
  FchParams->Spi.LpcClk1                   = PcdGetBool (PcdLpcClk1);
  FchParams->Spi.LpcClkRunEn               = PcdGetBool (PcdLpcClkRunEn);
  FchParams->EspiEnable                    = PcdGetBool (PcdEspiEnable);
  FchParams->EspiEc0Enable                 = PcdGetBool (PcdEspiEc0Enable);
  FchParams->EspiIo80Enable                = PcdGetBool (PcdEspiIo80Enable);
  FchParams->EspiKbc6064Enable             = PcdGetBool (PcdEspiKbc6064Enable);
  FchParams->Gpp.SerialDebugBusEnable      = PcdGetBool (PcdSerialDebugBusEnable);
  FchParams->WdtEnable                     = PcdGetBool (PcdFchWdtEnable);
  FchParams->Xhci0ForceGen1                = PcdGetBool (PcdXhci0ForceGen1);
  FchParams->Xhci1Disable31Port            = PcdGetBool (PcdXhci1Disable31Port);
  FchParams->OemUsbConfigurationTablePtr   = PcdGetPtr (PcdUsbOemConfigurationTable);
  FchParams->XhciUsb3PortDisable           = PcdGet32 (PcdXhciUsb3PortDisable);
  FchParams->XhciUsb2PortDisable           = PcdGet32 (PcdXhciUsb2PortDisable);
  FchParams->XhciOCpinSelect               = PcdGet32 (PcdXhciOcPinSelect);
  FchParams->UsbSparseModeEnable           = PcdGetBool (PcdUsbSparseModeEnable);
  FchParams->ToggleAllPwrGoodOnCf9         = PcdGetBool (PcdToggleAllPwrGoodOnCf9);
  FchParams->Emmc.EmmcEnable               = PcdGet8 (PcdEmmcEnable);
  FchParams->Espi.OperatingFreq            = PcdGet8 (PcdEspiOperatingFreq);
  FchParams->Espi.IoMode                   = PcdGet8 (PcdEspiIoMode);
  FchParams->Espi.Decode.Io[0].Enable      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[0].Enable;
  FchParams->Espi.Decode.Io[0].Base        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[0].Base;
  FchParams->Espi.Decode.Io[0].Size        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[0].Size;
  FchParams->Espi.Decode.Io[1].Enable      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[1].Enable;
  FchParams->Espi.Decode.Io[1].Base        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[1].Base;
  FchParams->Espi.Decode.Io[1].Size        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[1].Size;
  FchParams->Espi.Decode.Io[2].Enable      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[2].Enable;
  FchParams->Espi.Decode.Io[2].Base        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[2].Base;
  FchParams->Espi.Decode.Io[2].Size        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[2].Size;
  FchParams->Espi.Decode.Io[3].Enable      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[3].Enable;
  FchParams->Espi.Decode.Io[3].Base        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[3].Base;
  FchParams->Espi.Decode.Io[3].Size        = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Io[3].Size;
  FchParams->Espi.Decode.Mmio[0].Enable    = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[0].Enable;
  FchParams->Espi.Decode.Mmio[0].Base      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[0].Base;
  FchParams->Espi.Decode.Mmio[0].Size      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[0].Size;
  FchParams->Espi.Decode.Mmio[1].Enable    = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[1].Enable;
  FchParams->Espi.Decode.Mmio[1].Base      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[1].Base;
  FchParams->Espi.Decode.Mmio[1].Size      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[1].Size;
  FchParams->Espi.Decode.Mmio[2].Enable    = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[2].Enable;
  FchParams->Espi.Decode.Mmio[2].Base      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[2].Base;
  FchParams->Espi.Decode.Mmio[2].Size      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[2].Size;
  FchParams->Espi.Decode.Mmio[3].Enable    = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[3].Enable;
  FchParams->Espi.Decode.Mmio[3].Base      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[3].Base;
  FchParams->Espi.Decode.Mmio[3].Size      = ((FCH_ESPI_DECODE *)PcdGetPtr (PcdEspiIoMmioDecode))->Mmio[3].Size;
  FchParams->Emmc.EmmcEnable               = PcdGet8 (PcdEmmcEnable);
  FchParams->Emmc.EmmcBoot                 = PcdGetBool (PcdEmmcBoot);
  FchParams->Emmc.EmmcAdma2Support         = PcdGetBool (PcdEmmcAdma2Support);
  FchParams->Emmc.EmmcAdmaSupport          = PcdGetBool (PcdEmmcAdmaSupport);
  FchParams->Emmc.EmmcSdmaSupport          = PcdGetBool (PcdEmmcSdmaSupport);
  FchParams->Emmc.EmmcA64bSupport          = PcdGetBool (PcdEmmcA64bSupport);

  FchParams->Promontory.PromontoryUSB.PTXhciGen1  = PcdGet8 (PcdPTXhciGen1);
  FchParams->Promontory.PromontoryUSB.PTXhciGen2  = PcdGet8 (PcdPTXhciGen2);
  FchParams->Promontory.PromontoryUSB.PTAOAC      = PcdGet8 (PcdPTAOAC);
  FchParams->Promontory.PromontoryUSB.PTHW_LPM    = PcdGet8 (PcdPTHW_LPM);
  FchParams->Promontory.PromontoryUSB.PTDbC       = PcdGet8 (PcdPTDbC);
  FchParams->Promontory.PromontoryUSB.PTXHC_PME   = PcdGet8 (PcdPTXHC_PME);

  FchParams->Promontory.PromontorySATA.PTSataMode               = PcdGet8 (PcdPTSataMode);
  FchParams->Promontory.PromontorySATA.PTSataAggresiveDevSlpP0  = PcdGet8 (PcdPTSataAggresiveDevSlpP0);
  FchParams->Promontory.PromontorySATA.PTSataAggresiveDevSlpP1  = PcdGet8 (PcdPTSataAggresiveDevSlpP1);
  FchParams->Promontory.PromontorySATA.PTSataAggrLinkPmCap      = PcdGet8 (PcdPTSataAggrLinkPmCap);
  FchParams->Promontory.PromontorySATA.PTSataPscCap             = PcdGet8 (PcdPTSataPscCap);
  FchParams->Promontory.PromontorySATA.PTSataSscCap             = PcdGet8 (PcdPTSataSscCap);
  FchParams->Promontory.PromontorySATA.PTSataMsiCapability      = PcdGet8 (PcdPTSataMsiCapability);
  FchParams->Promontory.PromontorySATA.PTSataPortMdPort0        = PcdGet8 (PcdPTSataPortMdPort0);
  FchParams->Promontory.PromontorySATA.PTSataPortMdPort1        = PcdGet8 (PcdPTSataPortMdPort1);
  FchParams->Promontory.PromontorySATA.PTSataHotPlug            = PcdGet8 (PcdPTSataHotPlug);

  FchParams->Promontory.PromontoryUSB.Equalization4             = PcdGet8 (PcdPTUsbEqualization4);
  FchParams->Promontory.PromontoryUSB.Redriver                  = PcdGet8 (PcdPTUsbRedriver);

  FchParams->Promontory.PromontoryUSBPort.PTUsb31P0             = PcdGet8 (PcdPTUsb31P0);
  FchParams->Promontory.PromontoryUSBPort.PTUsb31P1             = PcdGet8 (PcdPTUsb31P1);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P0             = PcdGet8 (PcdPTUsb30P0);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P1             = PcdGet8 (PcdPTUsb30P1);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P2             = PcdGet8 (PcdPTUsb30P2);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P3             = PcdGet8 (PcdPTUsb30P3);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P4             = PcdGet8 (PcdPTUsb30P4);
  FchParams->Promontory.PromontoryUSBPort.PTUsb30P5             = PcdGet8 (PcdPTUsb30P5);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P0             = PcdGet8 (PcdPTUsb20P0);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P1             = PcdGet8 (PcdPTUsb20P1);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P2             = PcdGet8 (PcdPTUsb20P2);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P3             = PcdGet8 (PcdPTUsb20P3);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P4             = PcdGet8 (PcdPTUsb20P4);
  FchParams->Promontory.PromontoryUSBPort.PTUsb20P5             = PcdGet8 (PcdPTUsb20P5);

  FchParams->Promontory.PTUSBPortPROM2.PTUsb31P0                = PcdGet8 (PcdPTProm2Usb31P0);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb31P1                = PcdGet8 (PcdPTProm2Usb31P1);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb30P0                = PcdGet8 (PcdPTProm2Usb30P0);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb30P1                = PcdGet8 (PcdPTProm2Usb30P1);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P0                = PcdGet8 (PcdPTProm2Usb20P0);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P1                = PcdGet8 (PcdPTProm2Usb20P1);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P2                = PcdGet8 (PcdPTProm2Usb20P2);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P3                = PcdGet8 (PcdPTProm2Usb20P3);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P4                = PcdGet8 (PcdPTProm2Usb20P4);
  FchParams->Promontory.PTUSBPortPROM2.PTUsb20P5                = PcdGet8 (PcdPTProm2Usb20P5);

  FchParams->Promontory.PTUSBPortPROM1.PTUsb31P0                = PcdGet8 (PcdPTProm1Usb31P0);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb31P1                = PcdGet8 (PcdPTProm1Usb31P1);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb30P0                = PcdGet8 (PcdPTProm1Usb30P0);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P0                = PcdGet8 (PcdPTProm1Usb20P0);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P1                = PcdGet8 (PcdPTProm1Usb20P1);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P2                = PcdGet8 (PcdPTProm1Usb20P2);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P3                = PcdGet8 (PcdPTProm1Usb20P3);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P4                = PcdGet8 (PcdPTProm1Usb20P4);
  FchParams->Promontory.PTUSBPortPROM1.PTUsb20P5                = PcdGet8 (PcdPTProm1Usb20P5);

  FchParams->Promontory.PromontorySATAPort.PTSataPort0Enable    = PcdGet8 (PcdPTSataPort0Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort1Enable    = PcdGet8 (PcdPTSataPort1Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort2Enable    = PcdGet8 (PcdPTSataPort2Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort3Enable    = PcdGet8 (PcdPTSataPort3Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort4Enable    = PcdGet8 (PcdPTSataPort4Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort5Enable    = PcdGet8 (PcdPTSataPort5Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort6Enable    = PcdGet8 (PcdPTSataPort6Enable);
  FchParams->Promontory.PromontorySATAPort.PTSataPort7Enable    = PcdGet8 (PcdPTSataPort7Enable);

  FchParams->Promontory.PCIEPorts[0]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort0Enable);
  FchParams->Promontory.PCIEPorts[1]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort1Enable);
  FchParams->Promontory.PCIEPorts[2]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort2Enable);
  FchParams->Promontory.PCIEPorts[3]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort3Enable);
  FchParams->Promontory.PCIEPorts[4]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort4Enable);
  FchParams->Promontory.PCIEPorts[5]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort5Enable);
  FchParams->Promontory.PCIEPorts[6]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort6Enable);
  FchParams->Promontory.PCIEPorts[7]                            = (BOOLEAN)PcdGet8 (PcdPTPciePort7Enable);

  FchParams->Promontory.LPPTGPPClkForceOn[0]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk0ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[1]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk1ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[2]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk2ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[3]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk3ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[4]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk4ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[5]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk5ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[6]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk6ForceOn);
  FchParams->Promontory.LPPTGPPClkForceOn[7]                    = (BOOLEAN)PcdGet8 (PcdPTGppClk7ForceOn);

  FchParams->Promontory.PTUSBPortPRO460.PTUsb31P0               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb31P0);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb31P1               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb31P1);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb30P0               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb30P0);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb30P1               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb30P1);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb30P2               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb30P2);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb30P3               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb30P3);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P0               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P0);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P1               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P1);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P2               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P2);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P3               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P3);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P4               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P4);
  FchParams->Promontory.PTUSBPortPRO460.PTUsb20P5               = (BOOLEAN)PcdGet8 (PcdPTPro460Usb20P5);
  FchParams->Promontory.PromontoryUSB.XhciLockEnable            = PcdGet8 (PcdPTLock);

  return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: FchInitPei
 *
 * Description:
 *               Initialization for FCH controller
 *
 * Input
 *   FchParams   : pointer to FCH_RESET_DATA_BLOCK
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
FchInitPei (
  IN       FCH_RESET_DATA_BLOCK  *FchParams
  )
{
  FchInitReset (FchParams);

  return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: FchGetBootMode
 *
 * Description:
 *   This function determines whether the platform is resuming from an S state
 *   using the FCH ACPI registers
 *
 * Input:
 *   PeiServices : a pointer to the PEI service table pointer
 *   pFchPrivate  : pointer to the FCH PEI private data structure
 *
 * Output:
 *   EFI_BOOT_MODE : Boot mode from SB
 *
 *********************************************************************************/
EFI_BOOT_MODE
FchGetBootMode (
  IN       EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_PEI_CPU_IO_PPI  *CpuIo;
  UINT16              FchBootMode;
  UINTN               AcpiPm1Ctl;

  //
  // find the CpuIo protocol
  //
  CpuIo = (*PeiServices)->CpuIo;

  //
  // Check the FCH WAK_STS bit in the ACPI_PM1_CTL register
  //
  // get the address PM1_CTL register address
  AcpiPm1Ctl  = LibFchPmIoRead16 (PeiServices, FCH_PMIOA_REG62);

  // get the boot mode as seen by the south bridge
  FchBootMode = (CpuIo->IoRead16 (PeiServices, CpuIo, AcpiPm1Ctl) & ACPI_BM_MASK);

  // convert the boot mode to the EFI version
  if (ACPI_S3 == FchBootMode) {
    return (BOOT_ON_S3_RESUME);
  }
  if (ACPI_S4 == FchBootMode) {
    return (BOOT_ON_S4_RESUME);
  }
  if (ACPI_S5 == FchBootMode) {
    return (BOOT_ON_S5_RESUME);
  }
  // S0 or unsupported Sx mode
  return (BOOT_WITH_FULL_CONFIGURATION);
}


/*********************************************************************************
 * Name: FchUpdateBootMode
 *
 * Description:
 *   This function update the platform boot mode based on the information
 *   gathered from the south bridge.
 *   Note that we do not publish the BOOT_MODE PPI since the platform
 *   is responsible for deciding what the actual boot mode is.
 *
 * Input:
 *   PeiServices : a pointer to the PEI service table pointer
 *   pFchPrivate  : pointer to the FCH PEI private data structure
 *
 * Output:
 *
 *********************************************************************************/
EFI_STATUS
FchUpdateBootMode (
  IN       EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_BOOT_MODE  BootMode;
  EFI_BOOT_MODE  FchBootMode;

  // Get FCH Boot mode
  FchBootMode = FchGetBootMode (PeiServices);

  // Get the platform boot mode
  (*PeiServices)->GetBootMode (
                    PeiServices,
                    &BootMode
                    );

  // Update boot mode if we are more important than the platform
  if ((BOOT_IN_RECOVERY_MODE != BootMode) && (BOOT_ON_FLASH_UPDATE != BootMode) && (BOOT_WITH_FULL_CONFIGURATION != FchBootMode)) {
    // Set Sx boot mode
    (*PeiServices)->SetBootMode (
                      PeiServices,
                      FchBootMode
                      );
  }
  return (EFI_SUCCESS);
}

EFI_STATUS
EFIAPI
FchMemoryDiscoveredPpiCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
  EFI_HOB_GUID_TYPE         *FchHob;
  FCH_RESET_DATA_BLOCK      *FchResetParams;
  AMD_FCH_INIT_PPI          *FchInitPpi;
  EFI_STATUS                Status;

  Status = EFI_SUCCESS;

  FchHob = GetFirstGuidHob (&gFchResetDataHobGuid);
  FchHob++;
  FchResetParams = (FCH_RESET_DATA_BLOCK *)FchHob;

  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdFchInitPpiGuid,
                             0,
                             NULL,
                             &FchInitPpi
                             );
  ASSERT_EFI_ERROR ( Status);

  FchInitPpi->FchResetData      = (VOID*) FchResetParams;
  FchInitPpi->PtResetData       = (VOID*) &(FchResetParams->Promontory);
  return Status;
}

EFI_STATUS
EFIAPI
FchInitXhciOnRecovery (
  IN       AMD_FCH_INIT_PPI   *This,
  IN       UINT32             XhciRomAddress
  )
{
  FCH_PEI_PRIVATE           *FchPrivate;

  FchPrivate = FCH_PEI_PRIVATE_FROM_THIS (This);
  //FchXhciOnRecovery (*FchPrivate, XhciRomAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FchInitEhciOnRecovery (
  IN       AMD_FCH_INIT_PPI   *This,
  IN       UINT32             EhciTemporaryBarAddress
  )
{
  FCH_PEI_PRIVATE           *FchPrivate;

  FchPrivate = FCH_PEI_PRIVATE_FROM_THIS (This);
  //FchEhciOnRecovery (*FchPrivate, EhciTemporaryBarAddress);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FchInitSataOnRecovery (
  IN       AMD_FCH_INIT_PPI   *This,
  IN       UINT32             SataBar0,
  IN       UINT32             SataBar5
  )
{
  FCH_PEI_PRIVATE           *FchPrivate;

  FchPrivate = FCH_PEI_PRIVATE_FROM_THIS (This);
  //FchSataOnRecovery (*FchPrivate, SataBar0, SataBar5 );
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FchInitGppOnRecovery (
  IN       AMD_FCH_INIT_PPI   *This,
  IN       FCH_GPP_R          *FchGpp
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FchInitEmmcOnRecovery (
  IN       AMD_FCH_INIT_PPI   *This
  )
{
  FCH_PEI_PRIVATE           *FchPrivate;

  FchPrivate = FCH_PEI_PRIVATE_FROM_THIS (This);
  FchEmmcOnRecovery (FchPrivate->FchInitPpi.FchResetData);
  return EFI_SUCCESS;
}
