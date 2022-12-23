/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmVariable.h>
#include <Library/IoLib.h>

#include <AmdSoc.h>
#include <AmdCbsConfig.h>
#include <AmdCbsVariableRVAM4.h>
#include <Features/Aod/Include/AodRuntimeLib.h>


EFI_SMM_SYSTEM_TABLE2                 *gSmst;

extern EFI_GUID  gCbsSystemConfigurationGuid;
extern EFI_GUID  gEfiSmmVariableProtocolGuid;
CBS_CONFIG       *gCbsConfig          = NULL;
BOOLEAN          gCbsConfigBuffered   = FALSE;

BOOLEAN
AodFamilyIdentify (
  )
{
  UINT32     EAX_Reg;
  UINT32     EBX_Reg;
  UINT32     ECX_Reg;
  UINT32     EDX_Reg;
  UINT64     SocFamilyID;

  AsmCpuid (
      0x80000001,
      &EAX_Reg,
      &EBX_Reg,
      &ECX_Reg,
      &EDX_Reg
      );
  SocFamilyID = EAX_Reg & RAW_FAMILY_ID_MASK;
  if (SocFamilyID == F17_RV_RAW_ID) {
    return TRUE;
  }
  return FALSE;
}



EFI_STATUS
UpdateAmdCbsVariables (
  IN AodMemoryBufferStruct *AodMemBuffer
  )
{
  EFI_STATUS                 Status;
  UINTN                      VarSize;
  CBS_CONFIG                 CbsConfig;
  UINT32                     Attributes;
  EFI_SMM_VARIABLE_PROTOCOL  *SmmVariable;

  Status = EFI_SUCCESS;
  VarSize = sizeof(CBS_CONFIG);
  IoWrite8 (0x80, 0xE0);

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmVariableProtocolGuid,
                    NULL,
                    (VOID **)&SmmVariable
                    );

  if (EFI_ERROR (Status)) {
    IoWrite8 (0x80, 0xF1);
    return Status;
  }
  Status = SmmVariable->SmmGetVariable (CBS_SYSTEM_CONFIGURATION_NAME, &gCbsSystemConfigurationGuid, &Attributes, &VarSize, &CbsConfig);
  if (EFI_ERROR (Status)) {
    IoWrite8 (0x80, 0xF2);
    return Status;
  }
  if (gCbsConfig == NULL) {
    Status = gSmst->SmmAllocatePool (EfiRuntimeServicesData, VarSize, &gCbsConfig);
    if (EFI_ERROR (Status)) {
    IoWrite8 (0x80, 0xF3);
      return Status;
    }
    ZeroMem (gCbsConfig, VarSize);
  }

  if (gCbsConfigBuffered == FALSE) {
    CopyMem (gCbsConfig, &CbsConfig, VarSize);
  }

  if (AodMemBuffer->Command == COMMAND_BUFFER_START) {
    gCbsConfigBuffered = TRUE;
  } if (AodMemBuffer->Command == COMMAND_BUFFER_END) {
    gCbsConfigBuffered = FALSE;
  }

  if (AodMemBuffer->Command == SET_MEMORY_CLOCK) {
    UINT8 MemFreqIndex = 0xFF;
    Status = GetMemFreqIndexByClk (AodMemBuffer->MemClkFreq, &MemFreqIndex);
    if (Status == EFI_SUCCESS) {
      gCbsConfig->CbsCmnMemSpeedDdr4 = (UINT8) MemFreqIndex;
    }
  } else if (AodMemBuffer->Command == SET_TCL) {
    gCbsConfig->CbsCmnMemTimingTclDdr4 = AodMemBuffer->Tcl;
  } else if (AodMemBuffer->Command == SET_TRCDRD) {
    gCbsConfig->CbsCmnMemTimingTrcdrdDdr4 = AodMemBuffer->Trcdrd;
  } else if (AodMemBuffer->Command == SET_TRCDWR) {
    gCbsConfig->CbsCmnMemTimingTrcdwrDdr4 = AodMemBuffer->Trcdwr;
  } else if (AodMemBuffer->Command == SET_TRAS) {
    gCbsConfig->CbsCmnMemTimingTrasDdr4 = AodMemBuffer->Tras;
  } else if (AodMemBuffer->Command == SET_TRP) {
    gCbsConfig->CbsCmnMemTimingTrpDdr4 = AodMemBuffer->Trp;
  } else if (AodMemBuffer->Command == SET_PROC_ODT) {
    gCbsConfig->CbsCmnMemCtrllerProcOdtDdr4 = (UINT8) AodMemBuffer->procODT;
  } else if (AodMemBuffer->Command == SET_TRCPAGE) {
    gCbsConfig->CbsCmnMemTimingTrcpageCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrcpageDdr4 = AodMemBuffer->Trcpage;
  } else if (AodMemBuffer->Command == SET_TRC) {
    gCbsConfig->CbsCmnMemTimingTrcCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrcDdr4 = AodMemBuffer->Trc;
  } else if (AodMemBuffer->Command == SET_TRFC) {
    gCbsConfig->CbsCmnMemTimingTrfcCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrfcDdr4 = AodMemBuffer->Trfc;
  } else if (AodMemBuffer->Command == SET_TRFC2) {
    gCbsConfig->CbsCmnMemTimingTrfc2CtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrfc2Ddr4 = AodMemBuffer->Trfc2;
  } else if (AodMemBuffer->Command == SET_TRFC4) {
    gCbsConfig->CbsCmnMemTimingTrfc4CtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrfc4Ddr4 = AodMemBuffer->Trfc4;
  } else if (AodMemBuffer->Command== SET_TFAW) {
    gCbsConfig->CbsCmnMemTimingTfawCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTfawDdr4 = AodMemBuffer->Tfaw;
  } else if (AodMemBuffer->Command == SET_TRRDS) {
    gCbsConfig->CbsCmnMemTimingTrrdSDdr4 = AodMemBuffer->TrrdS;
  } else if (AodMemBuffer->Command == SET_TRRDL) {
    gCbsConfig->CbsCmnMemTimingTrrdLDdr4 = AodMemBuffer->TrrdL;
  } else if (AodMemBuffer->Command == SET_TWR) {
    gCbsConfig->CbsCmnMemTimingTwrCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTwrDdr4 = AodMemBuffer->Twr;
  } else if (AodMemBuffer->Command == SET_TWTRS) {
    gCbsConfig->CbsCmnMemTimingTwtrSDdr4 = AodMemBuffer->TwtrS;
  } else if (AodMemBuffer->Command == SET_TWTRL) {
    gCbsConfig->CbsCmnMemTimingTwtrLDdr4 = AodMemBuffer->TwtrL;
  } else if (AodMemBuffer->Command == SET_TCKE) {
    gCbsConfig->CbsCmnMemTimingTckeDdr4 = AodMemBuffer->TCke;
  } else if (AodMemBuffer->Command == SET_TCWL) {
    gCbsConfig->CbsCmnMemTimingTcwlDdr4 = AodMemBuffer->Tcwl;
  } else if (AodMemBuffer->Command == SET_TRTP) {
    gCbsConfig->CbsCmnMemTimingTrtpDdr4 = AodMemBuffer->Trtp;
  } else if (AodMemBuffer->Command == SET_TRDRDSC) {
    gCbsConfig->CbsCmnMemTimingTrdrdScDdr4 = AodMemBuffer->TrdrdSc;
  } else if (AodMemBuffer->Command == SET_TRDRDSCL) {
    gCbsConfig->CbsCmnMemTimingTrdrdScLCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTrdrdScLDdr4 = AodMemBuffer->TrdrdScL;
  } else if (AodMemBuffer->Command == SET_TRDRDSD) {
    gCbsConfig->CbsCmnMemTimingTrdrdSdDdr4 = AodMemBuffer->TrdrdSd;
  } else if (AodMemBuffer->Command == SET_TRDRDDD) {
    gCbsConfig->CbsCmnMemTimingTrdrdDdDdr4 = AodMemBuffer->TrdrdDd;
  } else if (AodMemBuffer->Command == SET_TWRWRSC) {
    gCbsConfig->CbsCmnMemTimingTwrwrScDdr4 = AodMemBuffer->TwrwrSc;
  } else if (AodMemBuffer->Command == SET_TWRWRSCL) {
    gCbsConfig->CbsCmnMemTimingTwrwrScLCtrlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemTimingTwrwrScLDdr4 = AodMemBuffer->TwrwrScL;
  } else if (AodMemBuffer->Command == SET_TWRWRSD) {
    gCbsConfig->CbsCmnMemTimingTwrwrSdDdr4 = AodMemBuffer->TwrwrSd;
  } else if (AodMemBuffer->Command == SET_TWRWRDD) {
    gCbsConfig->CbsCmnMemTimingTwrwrDdDdr4 = AodMemBuffer->TwrwrDd;
  } else if (AodMemBuffer->Command == SET_TRDWR) {
    gCbsConfig->CbsCmnMemTimingTrdwrDdr4 = AodMemBuffer->Trdwr;
  } else if (AodMemBuffer->Command == SET_TWRRD) {
    gCbsConfig->CbsCmnMemTimingTwrrdDdr4 = AodMemBuffer->Twrrd;
  } else if (AodMemBuffer->Command == SET_GEAR_DOWN_EN) {
    gCbsConfig->CbsCmnMemGearDownModeDdr4 = AodMemBuffer->GearDownEn;
  } else if (AodMemBuffer->Command == SET_CMD_2T) {
    gCbsConfig->CbsCmnMemCtrller2TModeDdr4 = AodMemBuffer->Cmd2t;
  } else if (AodMemBuffer->Command == SET_RTT_NOM) {
    gCbsConfig->CbsCmnMemDataBusConfigCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCtrllerRttNomDdr4 = AodMemBuffer->RttNom;
  } else if (AodMemBuffer->Command == SET_RTT_WR) {
    gCbsConfig->CbsCmnMemDataBusConfigCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCtrllerRttWrDdr4 = AodMemBuffer->RttWR;
  } else if (AodMemBuffer->Command == SET_RTT_PARK) {
    gCbsConfig->CbsCmnMemDataBusConfigCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCtrllerRttParkDdr4 = AodMemBuffer->RttPark;
  } else if (AodMemBuffer->Command == SET_POWER_DOWN_EN) {
    gCbsConfig->CbsCmnMemCtrllerPwrDnEnDdr4 = AodMemBuffer->PowerDownEn;
  } else if (AodMemBuffer->Command == SET_SMT_EN) {
    gCbsConfig->CbsCmnCpuOcMode = 5;
    gCbsConfig->CbsCmnCpuGenSmtEn = AodMemBuffer->SmtEnabled;
  } else if (AodMemBuffer->Command == SW_DOWNCORE_CONFIG) {
    if (AodMemBuffer->DownCore.DownCoreConfig.IsBitmap == 0) {
      if (AodMemBuffer->DownCore.ActiveCoreNum == 3) {
        gCbsConfig->CbsCmnCpuOcMode = 5;
        gCbsConfig->CbsCmnCpuGenDowncoreCtrl = 4;  // THREE
      } else if (AodMemBuffer->DownCore.ActiveCoreNum == 2) {
        gCbsConfig->CbsCmnCpuOcMode = 5;
        gCbsConfig->CbsCmnCpuGenDowncoreCtrl = 3;  // TWO
      } else if (AodMemBuffer->DownCore.ActiveCoreNum == 1) {
        gCbsConfig->CbsCmnCpuOcMode = 5;
        gCbsConfig->CbsCmnCpuGenDowncoreCtrl = 1;  // ONE
      } else if (AodMemBuffer->DownCore.ActiveCoreNum == 0xFF) {
        gCbsConfig->CbsCmnCpuOcMode = 0;
        gCbsConfig->CbsCmnCpuGenDowncoreCtrl = 0;  // No core disabled, change back to Auto
      } else {
        // Should not be here
        Status = EFI_UNSUPPORTED;
      }
    } else {
      // bit map downcore config is not supported for RV yet
    }
  } else if (AodMemBuffer->Command == SET_EDC_TROTTLER_CONTROL) {
    // Token set to 1: the threshold will be set to 0xD
    // Any value other than 1, the threshold will be set to 0xB
    gCbsConfig->CbsCpuRelaxedEdcThrottling = AodMemBuffer->EdcThrottlerCtrl;
  }  else if (AodMemBuffer->Command == SET_ADDR_CMD_SETUP) {
    gCbsConfig->CbsCmnMemCadBusTimingCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemAddrCmdSetupDdr4 = AodMemBuffer->AddrCmdSetup;
  } else if (AodMemBuffer->Command == SET_CS_ODT_SETUP) {
    gCbsConfig->CbsCmnMemCadBusTimingCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCsOdtSetupDdr4 = AodMemBuffer->CsOdtSetup;
  } else if (AodMemBuffer->Command == SET_CKE_SETUP) {
    gCbsConfig->CbsCmnMemCadBusTimingCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCkeSetupDdr4 = AodMemBuffer->CkeSetup;
  } else if (AodMemBuffer->Command == SET_CAD_BUS_CLK_DRV_STREN) {
    gCbsConfig->CbsCmnMemCadBusDrvStrenCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCadBusClkDrvStrenDdr4 = AodMemBuffer->CadBusClkDrvStren;
  } else if (AodMemBuffer->Command == SET_CAD_BUS_ADDR_DRV_STREN) {
    gCbsConfig->CbsCmnMemCadBusDrvStrenCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCadBusAddrCmdDrvStrenDdr4 = AodMemBuffer->CadBusAddrDrvStren;
  } else if (AodMemBuffer->Command == SET_CAD_BUS_CS_ODT_CMD_DRV_STREN) {
    gCbsConfig->CbsCmnMemCadBusDrvStrenCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCadBusCsOdtDrvStrenDdr4 = AodMemBuffer->CadBusCsOdtCmdDrvStren;
  } else if (AodMemBuffer->Command == SET_CAD_BUS_CKE_DRV_STREN) {
    gCbsConfig->CbsCmnMemCadBusDrvStrenCtlDdr4 = 1;  // Manual
    gCbsConfig->CbsCmnMemCadBusCkeDrvStrenDdr4 = AodMemBuffer->CadBusCkeDrvStren;
  } else if (AodMemBuffer->Command == SET_CLDO_VDDP) {
    gCbsConfig->CbsCmnCLDO_VDDPCtl = 1;  // Manual
    gCbsConfig->CbsCmnCLDOVDDPvoltage = AodMemBuffer->CldoVddp;
  } else if (AodMemBuffer->Command == SET_INTERLEAVE_MODE) {
    gCbsConfig->CbsDfCmnMemIntlv = (UINT8) AodMemBuffer->MemInterleavingMode;
  } else if (AodMemBuffer->Command == SET_INTERLEAVE_SIZE) {
    gCbsConfig->CbsDfCmnMemIntlvSize = (UINT8) AodMemBuffer->InterleavingSize;
  } else if (AodMemBuffer->Command == SET_FCLK_OC_MODE) {
    gCbsConfig->CbsCmnGnbFclkOcFlag = (UINT8) AodMemBuffer->FclkOcMode;
  } else if (AodMemBuffer->Command == SET_SOC_VID) {
    gCbsConfig->CbsCmnGnbSocOverclockVid = (UINT8) AodMemBuffer->VddcrSocVid;
  }
  
  IoWrite8 (0x80, 0xF4);

  if (gCbsConfigBuffered == FALSE) {
    IoWrite8 (0x80, 0xF7);
    gCbsConfig->CbsCmnMemOverclockDdr4 = 1;
    Status = SmmVariable->SmmSetVariable (CBS_SYSTEM_CONFIGURATION_NAME, &gCbsSystemConfigurationGuid, Attributes, VarSize, gCbsConfig);
    if (Status == EFI_SUCCESS) {
      IoWrite8 (0x80, 0xF8);
    }
  }

  return Status;
}

